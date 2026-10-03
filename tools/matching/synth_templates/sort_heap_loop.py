# for (; (last-first) > 1; --last) pop(first,last,pred);  element size from N
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, esi ; sub edi, ebx ; mov eax, A ; imul edi ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; cmp eax, N ; jle +N ; mov ecx, dword ptr [esp + N] ; push ecx ; push esi ; push ebx ; call EXT ; sub edi, N ; mov eax, A ; imul edi ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; add esp, N ; sub esi, N ; cmp eax, N ; jg +N ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    sz = N[6]
    # pred must be a by-value struct (forces reload of arg from stack each iteration)
    return ("struct E%08x { char p[%d]; };\nstruct P%08x { int v; };\nvoid cb%08x(E%08x*, E%08x*, P%08x);\n"
            "void FUN_%08x(E%08x* first, E%08x* last, P%08x pred) {\n"
            "  for (; last - first > 1; --last) cb%08x(first, last, pred);\n}"
            % (va, sz, va, va, va, va, va, va, va, va, va, va)), "?FUN_%08x@@YAXPAUE%08x@@0UP%08x@@@Z" % (va, va, va)
