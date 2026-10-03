# bool f(a,b): return (p1 && p1->vf(a,b)) || (p2 && p2->vf(a,b)); members at +c/+10, same virtual slot
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, ecx ; mov ecx, dword ptr [esi + N] ; push edi ; mov edi, dword ptr [esp + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; push edi ; push ebx ; call edx ; test al, al ; jne +N ; mov ecx, dword ptr [esi + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; push edi ; push ebx ; call edx ; test al, al ; je +N ; pop edi ; pop esi ; mov eax, N ; pop ebx ; ret N ; pop edi ; pop esi ; xor eax, eax ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    slot = N[3] // 4
    off1, off2 = N[1], N[4]
    vf = "\n".join("virtual void v%d() {}" % i for i in range(slot))
    src = """struct I_%08x { %s virtual bool vf(int, int) { return false; } };
struct C_%08x { char pad[%d]; I_%08x* p1; I_%08x* p2;
  int f(int a, int b); };
int C_%08x::f(int a, int b) { I_%08x* x; return ((x = p1) && x->vf(a, b)) || ((x = p2) && x->vf(a, b)); }
""" % (va, vf, va, off1, va, va, va, va)
    return src, "?f@C_%08x@@QAEHHH@Z" % va
