# this->a->vfn(*conv(arg,1)) stored into this->b->field
PATTERN = 'push esi ; mov esi, ecx ; mov ecx, dword ptr [esp + N] ; push N ; call EXT ; mov ecx, dword ptr [esi + N] ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [eax] ; mov edx, dword ptr [edx + N] ; push eax ; call edx ; mov ecx, dword ptr [esi + N] ; mov edx, dword ptr [ecx + N] ; mov dword ptr [edx + N], eax ; pop esi ; ret N'
FLAGS = ["/O2", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Arg { unsigned* conv(int); };
struct Tgt { virtual void v0(); };
"""
def emit(va, A, N):
    # N: 8, 1, off_a, vtbl, off_b, off_c, off_field, 4
    _, one, oa, vt, ob, oc, of = N[:7]
    pads = "".join("virtual void p%d(); " % k for k in range(vt // 4))
    s = """struct T%(v)08x { char p[%(of)d]; unsigned f; };
struct U%(v)08x { char p[%(oc)d]; T%(v)08x* t; };
struct I%(v)08x { %(pads)svirtual unsigned call(unsigned); };
struct S%(v)08x {
  char p0[%(oa)d]; I%(v)08x* a; char p1[%(pb)d]; U%(v)08x* b;
  void FUN_%(v)08x(Arg* x);
};
void S%(v)08x::FUN_%(v)08x(Arg* x) { unsigned* v = x->conv(%(one)d); b->t->f = a->call(*v); }
""" % dict(v=va, of=of, oc=oc, oa=oa, pb=ob - oa - 4, one=one, pads=pads)
    return s, "?FUN_%08x@S%08x@@QAEXPAUArg@@@Z" % (va, va)
