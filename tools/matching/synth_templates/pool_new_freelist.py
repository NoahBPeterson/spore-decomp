# Class operator new with a free-list pool: if (size == K) pop head of pool freelist (refilling via
# Pool::refill(0,0)) else forward to the generic allocator. Source shape: if (n==K){do{...}while(refill)} return alt(n).
PATTERN = 'mov eax, dword ptr [esp + N] ; cmp eax, N ; jne +N ; jmp +N ; lea ecx, [ecx] ; mov eax, dword ptr [A] ; test eax, eax ; jne +N ; push eax ; push eax ; mov ecx, A ; call EXT ; test al, al ; jne +N ; xor eax, eax ; ret  ; mov ecx, dword ptr [eax] ; mov dword ptr [A], ecx ; ret  ; mov dword ptr [esp + N], eax ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "void* __cdecl pool_alt(unsigned);\n"
def emit(va, A, N):
    head, pool = A[0], A[1]
    off = head - pool
    size = [n for n in N if n > 4][0] if len(N) > 1 and N[0] == 4 else N[1]
    pad = off // 4
    src = ("struct Pool_%08x { unsigned pad[%d]; void** head; bool __thiscall refill(int,int); };\n"
           "extern Pool_%08x g_%08x;\n"
           "void* __cdecl FUN_%08x(unsigned n) {\n"
           "  if (n == 0x%x) {\n    void** p;\n    do {\n      p = g_%08x.head;\n"
           "      if (p) { g_%08x.head = (void**)*p; return p; }\n"
           "    } while (g_%08x.refill(0,0));\n    return 0;\n  }\n  return pool_alt(n);\n}"
           ) % (va, pad, va, pool, va, size, pool, pool, pool)
    return src, "?FUN_%08x@@YAPAXI@Z" % va
