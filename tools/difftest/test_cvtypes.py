"""cvtypes.py (CodeView layouts of a /Z7 compile) and equiv.TypedInputs on a small compiled sample.

Run: .venv/bin/python -m pytest -q tools/difftest/test_cvtypes.py
"""
import os, random, struct, sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
import pytest  # noqa: E402
import cvtypes as CV  # noqa: E402
import slice as S  # noqa: E402
from coff import Coff  # noqa: E402

SAMPLE = r"""
#include <vector>
#include <string>
namespace ns {
struct Inner { int a; float b; };
enum Color { RED = 3, GREEN = 7 };
struct Base { virtual ~Base(); int base_x; };
struct Other { virtual void f(); short s; };
struct Fwd;
struct Str { int pos; char* buf; int cap; int len; };
template<class T> struct vec { T* first; T* last; T* end; };
class Thing : public Base, public Other {
public:
    char name[8];
    const char* label;
    Inner inner;
    Inner* next;
    Color color;
    bool flag;
    double d;
    std::vector<Inner> items;
    std::string str;
    int arr[3];
    unsigned bits : 3;
    union { int u_i; float u_f; };
    Fwd* opaque;
    Str rs;
    vec<int> iv;
    unsigned char uc;
    int method(Thing* other, const Inner& r, int k);
};
int Thing::method(Thing* other, const Inner& r, int k) { return other->base_x + r.a + k + base_x; }
}
"""
METHOD = "?method@Thing@ns@@QAEHPAV12@ABUInner@2@H@Z"


@pytest.fixture(scope="module")
def sample():
    d = os.path.join(ROOT, "work", "difftest", "mut")
    os.makedirs(d, exist_ok=True)
    src = os.path.join(d, "cvtypes_sample.cpp")
    if not os.path.exists(src) or open(src).read() != SAMPLE:
        open(src, "w").write(SAMPLE)
    obj, log = S.compile_obj(src, list(S.DEFAULT_FLAGS) + ["/EHsc", "/Z7"])
    assert obj, log
    tt, procs = CV.load(Coff(obj))
    return tt, procs


def by_name(tt, name):
    ti = tt.defined[name]
    return ti, {f.name: f for f in tt.layout(ti)}, tt.layout(ti)


def test_function_types(sample):
    tt, procs = sample
    assert METHOD in procs
    f = tt.func(procs[METHOD])
    assert tt.name(f["cls"]) == "ns::Thing"
    assert tt.name(tt.pointee(f["this"])) == "ns::Thing"
    kinds = [tt.scalar(a) for a in f["args"]]
    assert kinds[0][0] == "ptr_class" and tt.name(kinds[0][2]) == "ns::Thing"
    assert kinds[1][0] == "ptr_class" and tt.name(kinds[1][2]) == "ns::Inner"     # a reference is a pointer
    assert kinds[2] == ("int", 4, True)


def test_layout(sample):
    tt, _ = sample
    ti, fs, lay = by_name(tt, "ns::Thing")
    offs = [f.off for f in lay]
    assert offs == sorted(offs) and len(set(offs)) == len(offs)
    assert lay[0].off == 0 and lay[0].kind == "vfptr" and lay[0].target[0] == "??_7Thing@ns@@6B@"
    assert fs["base_x"].off == 4 and fs["base_x"].kind == "int"
    v2 = [f for f in lay if f.kind == "vfptr" and f.off == 8]
    assert v2 and v2[0].target[0] == "??_7Thing@ns@@6BOther@ns@@@" and "??_7Other@ns@@6B@" in v2[0].target
    assert fs["s"].off == 12 and (fs["s"].kind, fs["s"].size) == ("int", 2)
    assert (fs["name"].kind, fs["name"].off, fs["name"].size) == ("chars", 16, 8)
    assert fs["label"].kind == "ptr_char"
    assert fs["a"].kind == "int" and fs["b"].kind == "float" and fs["b"].off == fs["a"].off + 4  # embedded Inner
    assert fs["next"].kind == "ptr_class" and tt.name(fs["next"].target) == "ns::Inner"
    assert fs["color"].kind == "enum" and sorted(fs["color"].target) == [3, 7]
    assert fs["flag"].kind == "bool" and fs["flag"].size == 1
    assert fs["d"].kind == "double"
    assert fs["_Myfirst"].kind == "vector" and tt.name(fs["_Myfirst"].target) == "ns::Inner"
    assert "_Mylast" not in fs and "_Myend" not in fs
    strs = [f for f in lay if f.kind == "stdstring"]
    assert len(strs) == 1 and strs[0].size == 24
    assert [f.kind for f in lay if f.name.startswith("arr[")] == ["int"] * 3
    assert "bits" not in fs and "u_f" not in fs                         # bitfields stay soup
    assert fs["u_i"].kind == "int"                                      # a union: its first member
    assert fs["opaque"].kind == "ptr_other"                            # an undefined class: unknown size
    assert [f.kind for f in lay if f.off == fs["opaque"].off + 4] == ["rglstring"]
    assert fs["first"].kind == "vector" and fs["first"].target == 0x74  # vec<int>: an int element
    assert fs["uc"].kind == "int" and fs["uc"].size == 1 and fs["uc"].target is False


def test_mangle():
    assert CV.mangle_class("rgl::mesh") == "mesh@rgl@@"
    assert CV.vtable_name("rgl::mesh") == "??_7mesh@rgl@@6B@"
    assert CV.vtable_name("D", "B") == "??_7D@@6BB@@@"
    assert CV.mangle_class("std::vector<int,std::allocator<int> >") is None
    assert CV.data_type("?g_game@@3PAVGame@@A") == ("ptr", "Game")
    assert CV.data_type("?g_x@@3UFoo@rgl@@A") == ("obj", "rgl::Foo")
    assert CV.data_type("?g@ns@@3PAUFoo@1@A") == ("ptr", "ns::Foo")        # a back reference
    assert CV.data_type("?g_n@@3HA") is None and CV.data_type("?g_v@@3V?$vector@H@std@@A") is None


class _Gen:
    """The parts of equiv.InputGen TypedInputs uses."""
    dic = [0, 1, 0x10]
    specials = [0.0, 1.0]

    def fin(self, v):
        return v

    def _scalar(self, k, rng, profile, hot=1):
        return struct.unpack("<I", struct.pack("<f", rng.uniform(-4, 4)))[0]


class _Inp:
    def __init__(self):
        import machine as M
        self.regs = {"ecx": M.POOL_BASE + M.SLOT}
        self.args = []
        self.pool_over = {}
        self.overrides = {}
        self.profile = "mixed"


def test_typed_objects(sample):
    import equiv
    import machine as M
    tt, procs = sample
    ti = tt.defined["ns::Thing"]
    vts = {"??_7Thing@ns@@6B@": 0x54a000, "??_7Other@ns@@6B@": 0x54a100}
    typed = equiv.TypedInputs(tt, ti, [], vts.get)
    fs = {f.name: f for f in tt.layout(ti)}
    base = M.POOL_BASE + M.SLOT
    seen_vec = 0
    for seed in range(40):
        inp = _Inp()
        assert typed.build(_Gen(), inp, random.Random(seed)) == 1
        po = inp.pool_over
        assert po[base] == 0x54a000                         # the original's vtable
        assert po[base + 8] == 0x54a100                     # the secondary base: its own class's vtable
        f, l, e = (po[base + fs["_Myfirst"].off + k] for k in (0, 4, 8))
        assert f <= l <= e
        if f:
            assert (l - f) % 8 == 0 and (l - f) // 8 <= 4  # sizeof(Inner) == 8
            seen_vec += f != l
        lab = po[base + fs["label"].off]
        if lab:
            s = b"".join(struct.pack("<I", po.get(a, 0)) for a in range(lab & ~3, (lab & ~3) + 16, 4))
            assert b"\0" in s[lab & 3:]
        assert po[base + fs["color"].off] in (3, 7) or po[base + fs["color"].off] < 9
        assert all(isinstance(v, int) and 0 <= v < 1 << 32 for v in po.values())
        assert all(a % 4 == 0 for a in po)
    assert seen_vec > 5


def test_abstract_vtable_replaced():
    """An abstract vtable (a _purecall slot) is replaced by a concrete one agreeing in every implemented slot."""
    import equiv
    P = 0x5363c8
    tables = {0x100: [0x1, 0x2, P, P], 0x200: [0x1, 0x2, 0x7, 0x8, 0x9], 0x300: [0x1, 0x5, 0x7, 0x8],
              0x400: [0x1, 0x2, 0x7, P], 0x500: [0x1, 0x2, 0x7, 0x8, 0x9]}
    typed = equiv.TypedInputs(None, None, [], {"??_7A@@6B@": 0x100, "??_7B@@6B@": 0x300}.get)
    typed.slots_of, typed.purecall, typed.known_vts = tables.get, P, sorted(tables)
    typed.rng = random.Random(1)
    assert typed.concrete(0x100) == [0x200]          # 0x300 overrides slot 1, 0x400 is abstract, 0x500 a duplicate
    assert typed.vtable(("??_7A@@6B@",)) == 0x200
    assert typed.vtable(("??_7X@@6B@", "??_7B@@6B@")) == 0x300 and typed.concrete(0x300) == []


TREE_SAMPLE = r"""
#include "eastl/map.h"
struct Item { unsigned id; float w; };
struct Holder {
    int a;
    eastl::map<unsigned int, bool> flags;
    eastl::map<unsigned int, Item> items;
    int b;
    int touch(unsigned k);
};
int Holder::touch(unsigned k) { eastl::map<unsigned int, Item>::node_type* n = 0; return a + b + (int)k + (n != 0); }
"""


@pytest.fixture(scope="module")
def tree_sample():
    d = os.path.join(ROOT, "work", "difftest", "mut")
    os.makedirs(d, exist_ok=True)
    src = os.path.join(d, "cvtypes_tree_sample.cpp")
    if not os.path.exists(src) or open(src).read() != TREE_SAMPLE:
        open(src, "w").write(TREE_SAMPLE)
    obj, log = S.compile_obj(src, list(S.DEFAULT_FLAGS) + ["/Z7", "/I" + os.path.join(ROOT, "src", "game", "include")])
    assert obj, log
    tt, _ = CV.load(Coff(obj))
    return tt


def test_rbtree_inputs(tree_sample):
    """An eastl::map member is an rbtree field; typed inputs build a well-formed red-black tree with ascending keys."""
    import equiv
    import machine as M
    tt = tree_sample
    ti = tt.defined["Holder"]
    lay = tt.layout(ti)
    trees = [f for f in lay if f.kind == "rbtree"]
    assert [f.off for f in trees] == [8, 0x24]          # map at +4 / +0x20: the anchor 4 bytes in
    assert not any(f.name in ("mAnchor", "mnSize", "mpNodeLeft") for f in lay)
    assert {f.name: f for f in lay}["b"].off == 0x3c
    typed = equiv.TypedInputs(tt, ti, [], {}.get)
    base = M.POOL_BASE + M.SLOT
    sizes = set()
    for seed in range(60):
        inp = _Inp()
        assert typed.build(_Gen(), inp, random.Random(seed)) == 1
        po = inp.pool_over
        for f in trees:
            anc = base + f.off
            right, left, root, n = po[anc], po[anc + 4], po[anc + 8], po[anc + 0x10]
            sizes.add(n)
            if n == 0:
                assert right == left == anc and root == 0
                continue
            assert po[root + 8] == anc and po[root + 0xc] & 0xff == 1   # the root: black, parent = anchor
            order, node = [], left                      # in-order walk, as eastl::RBTreeIncrement does
            while node != anc and len(order) <= n:
                order.append(node)
                if po.get(node, 0):
                    node = po[node]
                    while po.get(node + 4, 0):
                        node = po[node + 4]
                else:
                    p = po[node + 8]
                    while p != anc and node == po.get(p, 0):
                        node, p = p, po[p + 8]
                    node = p
            assert len(order) == n and order[-1] == right
            keys = [po[x + 0x10] for x in order]
            assert keys == sorted(keys) and len(set(keys)) == n
    assert sizes == {0, 1, 2, 3}
