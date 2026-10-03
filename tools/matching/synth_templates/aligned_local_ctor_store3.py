# The arg is a by-value one-int struct (zero-initialized aggregate): that gives xor eax,eax; push eax
# instead of push 0 (a plain int/ptr/bool 0 arg folds to push 0).
# Function that constructs an unused 16-byte-aligned stack object (extern ctor, one arg 0) then stores
# three globals (name string ptr, fn ptr, data ptr): hkClass-style type registration glue.
#   push ebp; mov ebp,esp; and esp,-16; sub esp,S; xor eax,eax; push eax; lea ecx,[esp+4]; call ctor; 3 stores
PATTERN = 'push ebp ; mov ebp, esp ; and esp, A ; sub esp, N ; xor eax, eax ; push eax ; lea ecx, [esp + N] ; call EXT ; mov dword ptr [A], A ; mov dword ptr [A], A ; mov dword ptr [A], A ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """typedef unsigned int u32;
extern u32 sA[], sB[], sC[];
struct Flag0 { int x; };
"""
def emit(va, A, N):
    S = N[0]
    return ("""struct __declspec(align(16)) L%08x { u32 b[%d]; L%08x(Flag0); };
extern u32 *g1_%08x, *g2_%08x, *g3_%08x;
void FUN_%08x() { Flag0 z = {0}; L%08x l(z); g1_%08x = sA; g2_%08x = sB; g3_%08x = sC; }""" % (va, S//4, va, va, va, va, va, va, va, va, va),
            "?FUN_%08x@@YAXXZ" % va)
