# Lazy-init member getter: if(!p) Init(); if(!(p->flags&1)) Mgr()->vfn_0x34(p); return p->id;
PATTERN = 'push esi ; mov esi, ecx ; cmp dword ptr [esi + N], N ; jne +N ; call EXT ; mov esi, dword ptr [esi + N] ; test byte ptr [esi + N], N ; jne +N ; call EXT ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; push esi ; call eax ; mov eax, dword ptr [esi] ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Res { unsigned id; unsigned flags; };
struct Mgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
 virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
 virtual void v12(); virtual void v13(Res*); };
Mgr* GetMgr();
"""
def emit(va, A, N):
    off = N[0]
    return ("""struct C_%08x { char pad[%d]; Res* p; void Init(); unsigned get(); };
unsigned C_%08x::get() { if (!p) Init(); Res* r = p; if (!(r->flags & 1)) GetMgr()->v13(r); return r->id; }
""" % (va, off, va), "?get@C_%08x@@QAEIXZ" % va)
