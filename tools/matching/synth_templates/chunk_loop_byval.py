# Loop: while (((l - f) & -S) > S) { ext(f, l, x); l -= S; } with x a 4-byte struct passed by value
# (forces the per-iteration reload of the third arg from the stack). S in {4,8,32} from the and-mask.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, esi ; sub edi, ebx ; mov eax, edi ; and eax, A ; cmp eax, N ; jle +N ; lea esp, [esp] ; mov ecx, dword ptr [esp + N] ; push ecx ; push esi ; push ebx ; call EXT ; sub edi, N ; mov edx, edi ; and edx, A ; add esp, N ; sub esi, N ; cmp edx, N ; jg +N ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct P4 { int v; };\n"
def emit(va, A, N):
    s = (1 << 32) - A[0]
    return ("void ext_%08x(char*, char*, P4);\n"
            "void FUN_%08x(char* f, char* l, P4 x) {\n"
            "  while (((l - f) & -%d) > %d) { ext_%08x(f, l, x); l -= %d; }\n}" % (va, va, s, s, va, s)), \
           "?FUN_%08x@@YAXPAD0UP4@@@Z" % va
