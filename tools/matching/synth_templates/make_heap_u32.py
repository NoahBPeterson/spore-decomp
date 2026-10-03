# std::_Make_heap for 4-byte elements with a by-value pred: calls adjust_heap(first, hole, bottom, hole, val, pred)
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esp + N] ; sub edi, ebx ; sar edi, N ; cmp edi, N ; jl +N ; push esi ; lea esi, [edi - N] ; sar esi, N ; inc esi ; jmp +N ; lea ecx, [ecx] ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [ebx + esi*N - N] ; push eax ; dec esi ; push ecx ; push esi ; push edi ; push esi ; push ebx ; call EXT ; add esp, N ; test esi, esi ; jne +N ; pop esi ; pop edi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    return ("struct P_%08x { int x; };\n"
            "void adj_%08x(int*, int, int, int, int, P_%08x);\n"
            "void FUN_%08x(int* first, int* last, P_%08x pred) {\n"
            "  int bottom = last - first;\n"
            "  if (2 <= bottom) {\n"
            "    int hole = ((bottom - 2) >> 1) + 1;\n"
            "    do { --hole; adj_%08x(first, hole, bottom, hole, first[hole], pred); } while (hole != 0);\n"
            "  }\n}" % ((va,) * 6)), "?FUN_%08x@@YAXPAH0UP_%08x@@@Z" % (va, va)
