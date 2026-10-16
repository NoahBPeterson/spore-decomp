"""callerdeps.py against the hybrid crashes it must flag (docs/hybrid.md). Run: .venv/bin/python -m pytest tools/difftest/test_callerdeps.py"""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pytest
from callerdeps import Deps


@pytest.fixture(scope="module")
def d():
    return Deps()


def test_interpramp_xmm3_kept_live_by_its_caller(d):
    assert d.check(0x114e780, {"xmm3"})["verdict"] == "DEPENDS"


@pytest.mark.parametrize("va", [0x99efa0, 0xe5c780])   # uninitialized_copy, rbtree::find
def test_eax_result_read_by_callers(d, va):
    assert d.check(va, {"eax"}, result=True)["verdict"] == "DEPENDS"


def test_pointer_only_callback_result_is_not_safe(d):   # Pool_AllocGlobal, an allocation callback
    assert d.check(0x928ad0, {"eax"}, result=True)["verdict"] == "UNKNOWN"
    assert d.check(0x928ad0, {"ecx"})["verdict"] == "SAFE"


def test_callee_saved_is_always_depends(d):
    assert d.check(0x9d3840, {"esi"})["verdict"] == "DEPENDS"


def test_caller_overwrites_ecx_first(d):   # 0x9d39c1 mov ecx, [esp+0xc] right after the call
    assert d.check(0x9d3840, {"ecx"})["verdict"] == "SAFE"


def test_untracked_register_is_never_safe(d):   # build.py reports x87 stack use as 'st'
    assert d.check(0x9d3840, {"st"})["verdict"] == "UNKNOWN"
