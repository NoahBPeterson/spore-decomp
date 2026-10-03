# Like serializable_write_scope_local_init but the buffer helper gets this-N (secondary-base adjust).
# Store order between vptr load and call eax is the same open puzzle.
PATTERN = 'sub esp, N ; push esi ; mov esi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; push edi ; mov edi, ecx ; mov ecx, esi ; call edx ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; mov dword ptr [esp + N], A ; call eax ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; push eax ; call EXT ; add esp, N ; push A ; push A ; add edi, -N ; push edi ; lea ecx, [esp + N] ; call EXT ; push esi ; lea ecx, [esp + N] ; call EXT ; pop edi ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = '''
struct R { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void *v6(); };
struct S { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual R *v8(); };
void __cdecl FUN_0093aa70(void *r, void *b, int one, int zero);
'''
def emit(va, A, N):
    n = "%08x" % va
    size = N[0]
    return ('''struct Buf_%s { unsigned int d[%d]; void G(void *o, unsigned a, unsigned b); void H(S *s); };
struct C_%s { void W(S *s); };
void C_%s::W(S *s) {
    Buf_%s b; unsigned int key;
    R *r = s->v8();
    key = 0x%x;
    void *t = r->v6();
    FUN_0093aa70(t, (void*)&key, 1, 0);
    b.G((char*)this - %d, 0x%x, 0x%x);
    b.H(s);
}''' % (n, (size - 4) // 4, n, n, n, A[0], N[9], A[2], A[1])), "?W@C_%s@@QAEXPAUS@@@Z" % n
