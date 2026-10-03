# Free-list pop with refill: do { p=head; if(p){head=*p;return p;} } while(pool.refill(0,0)); return 0;
PATTERN = 'mov eax, dword ptr [A] ; test eax, eax ; jne +N ; push eax ; push eax ; mov ecx, A ; call EXT ; test al, al ; jne +N ; xor eax, eax ; ret  ; mov ecx, dword ptr [eax] ; mov dword ptr [A], ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Pool { bool Refill(int, int); };
"""
def emit(va, A, N):
    head, pool = A[0], A[1]
    src = ("extern Pool g_%08x;\nextern void** g_%08x;\n"
           "void** FUN_%08x() {\n  do {\n    void** p = g_%08x;\n    if (p) { g_%08x = (void**)*p; return p; }\n"
           "  } while (g_%08x.Refill(0, 0));\n  return 0;\n}" % (pool, head, va, head, head, pool))
    return src, "?FUN_%08x@@YAPAPAXXZ" % va
