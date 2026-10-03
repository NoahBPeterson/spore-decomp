# __thiscall(this, S* s) -> int: r = this->P(s); big stack buffer b; b.G(this, name, desc); return b.H(s) + r.
PATTERN = 'sub esp, N ; push ebx ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; push edi ; mov esi, ecx ; call EXT ; push A ; push A ; push esi ; lea ecx, [esp + N] ; mov ebx, eax ; call EXT ; push edi ; lea ecx, [esp + N] ; call EXT ; pop edi ; pop esi ; add eax, ebx ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ''
def emit(va, A, N):
    n = "%08x" % va
    size = N[0]
    return ('''struct Buf_%s { unsigned int d[%d]; void G(void *o, unsigned a, unsigned b); int H(void *s); };
struct C_%s { int P(void *s); int W(void *s); };
int C_%s::W(void *s) {
    int r = P(s);
    Buf_%s b;
    b.G(this, 0x%x, 0x%x);
    return b.H(s) + r;
}''' % (n, size // 4, n, n, n, A[1], A[0])), "?W@C_%s@@QAEHPAX@Z" % n
