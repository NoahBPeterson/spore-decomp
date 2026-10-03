# Dynamic initializer of a global list node: id=FNVHash(name,seed,1); next=head; head=&g; vptr; 3 uninit floats copied; atexit(dtor).
# Shape-equivalent (explicit stores in compiler order); uninitialized locals produce the esp-relative movss copies.
PATTERN = 'sub esp, N ; push N ; push A ; push A ; call EXT ; movss xmm0, dword ptr [esp + N] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [esp + N] ; mov dword ptr [A], eax ; mov eax, dword ptr [A] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [esp + N] ; push A ; mov dword ptr [A], eax ; mov dword ptr [A], A ; mov dword ptr [A], A ; movss dword ptr [A], xmm0 ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = '''extern "C" unsigned int __cdecl FNVHash_ext(const char*, unsigned int, int);
extern "C" int __cdecl atexit(void (__cdecl*)(void));
struct Node { const void* vt; unsigned id; Node* next; float a, b, c; };
'''
def emit(va, A, N):
    g = "g_%08x" % A[9]
    h = "g_%08x" % A[4]
    d = "dtor_%08x" % A[6]
    src = ("extern Node %s; extern Node* %s; extern const char vt_%08x[]; void __cdecl %s(void);\n"
           "void FUN_%08x() { float v[3]; %s.id = FNVHash_ext(\"n%08x\", 0x%X, 1); %s.a = v[0]; %s.b = v[1]; "
           "%s.next = %s; %s = &%s; %s.vt = vt_%08x; %s.c = v[2]; atexit(%s); }"
           % (g, h, A[11], d, va, g, va, A[0], g, g, g, h, h, g, g, A[11], g, d))
    return src, "?FUN_%08x@@YAXXZ" % va
