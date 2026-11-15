"""slice.find_symbol: which compiled function check.py compares with a retail address.
Run: .venv/bin/python -m pytest tools/difftest/test_find_symbol.py"""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import slice as SL

RAID = "?Execute@cCommandRaidCheat@@QAEXPAUcArguments@@@Z"
SPACE = "?Execute@cCommandSpace@nSpaceCheats@SP@@QAEXPAVcArguments_s0102_5840@ArgScript@EA@@@Z"


class FakeCoff:
    def __init__(self, names):
        self.f = {n: n for n in names}

    def functions(self):
        return self.f

    def func_extent(self, f):
        return 0, 0, 100


def _patch(monkeypatch, recorded, addrs, markers):
    monkeypatch.setattr(SL, "manifest_rows", lambda sid: [])
    monkeypatch.setattr(SL, "marker_names", lambda src, va: list(markers))
    monkeypatch.setattr(SL, "slice_symbol_name", lambda sid, va: None)
    monkeypatch.setattr(SL, "landed_symbol_name", lambda va: recorded)
    monkeypatch.setattr(SL, "_landed_addrs", addrs)


def test_recorded_name_of_another_address_loses_to_the_marker(monkeypatch):
    # issue #340: the record gave 0x01025840 the raid cheat's name, which is also recorded for 0x010251e0, and both
    # functions are in the object; the marker names cCommandSpace::Execute
    _patch(monkeypatch, RAID, {RAID: {0x01025840, 0x010251e0}}, ["cCommandSpace::Execute"])
    sym, how = SL.find_symbol(FakeCoff([RAID, SPACE]), "SPSpaceCheats", 0x01025840, "x.cpp")
    assert sym == SPACE, (sym, how)


def test_recorded_name_bound_to_one_address_still_wins(monkeypatch):
    # a record that disagrees with a loosely written marker but names only this address is kept (operators, renamed
    # classes and template constructors are spelled differently in markers)
    _patch(monkeypatch, RAID, {RAID: {0x01025840}}, ["cCommandSpace::Execute"])
    sym, how = SL.find_symbol(FakeCoff([RAID, SPACE]), "SPSpaceCheats", 0x01025840, "x.cpp")
    assert sym == RAID and how.startswith("symbols/slices"), (sym, how)


def test_provenance_names_the_landed_record(monkeypatch):
    _patch(monkeypatch, SPACE, {SPACE: {0x01025840}}, ["cCommandSpace::Execute"])
    sym, how = SL.find_symbol(FakeCoff([RAID, SPACE]), "SPSpaceCheats", 0x01025840, "x.cpp")
    assert sym == SPACE and "SPSpaceCheats.txt" not in how, (sym, how)
