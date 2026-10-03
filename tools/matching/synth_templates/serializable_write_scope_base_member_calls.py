# ISimulatorSerializable::Write: like serializable_write_scope_local_init, plus a call on this (base
# helper) and a call on the member at this+0x34, both taking the stream. UNSOLVED: the key store
# sits between the vptr-slot load and `call eax` in the original; every source order, volatile,
# temporaries and /O flag tried emits it right after the first vcall (15 diff bytes, all else matches).
PATTERN = 'sub esp, N ; push esi ; mov esi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; push edi ; mov edi, ecx ; mov ecx, esi ; call edx ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; mov dword ptr [esp + N], A ; call eax ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; push eax ; call EXT ; add esp, N ; push esi ; mov ecx, edi ; call EXT ; push esi ; lea ecx, [edi + N] ; call EXT ; push A ; push A ; push edi ; lea ecx, [esp + N] ; call EXT ; push esi ; lea ecx, [esp + N] ; call EXT ; pop edi ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = '''
struct R { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void *v6(); };
struct S { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual R *v8(); };
struct Sub { void X(S *s); };
void __cdecl FUN_0093aa70(void *r, void *b, int one, int zero);
'''
def emit(va, A, N):
    n = "%08x" % va
    size = N[0]
    return ('''struct Buf_%s { unsigned int d[%d]; void G(void *o, unsigned a, unsigned b); void H(S *s); };
struct C_%s { char pad[0x34]; Sub sub; void P(S *s); void W(S *s); };
void C_%s::W(S *s) {
    Buf_%s b; unsigned int key;
    R *r = s->v8();
    key = 0x%x;
    void *t = r->v6();
    FUN_0093aa70(t, (void*)&key, 1, 0);
    P(s);
    sub.X(s);
    b.G(this, 0x%x, 0x%x);
    b.H(s);
}''' % (n, (size - 4) // 4, n, n, n, A[0], A[2], A[1])), "?W@C_%s@@QAEXPAUS@@@Z" % n
