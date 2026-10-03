# sort_heap-style loop over u32* with a by-value struct predicate; calls out-of-line adjust_heap (cdecl, 6 args)
PATTERN = 'mov ecx, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esp + N] ; mov eax, ecx ; sub eax, edi ; sar eax, N ; cmp eax, N ; jle +N ; push ebx ; mov ebx, N ; push esi ; lea esi, [ecx - N] ; sub ebx, edi ; mov edx, dword ptr [edi] ; mov ecx, dword ptr [esi] ; mov dword ptr [esi], edx ; mov edx, dword ptr [esp + N] ; push edx ; push ecx ; push N ; dec eax ; push eax ; push N ; push edi ; call EXT ; sub esi, N ; lea eax, [ebx + esi] ; sar eax, N ; add esp, N ; cmp eax, N ; jg +N ; pop esi ; pop ebx ; pop edi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """typedef unsigned int u32;
struct SynthPred { void* p; };
void synth_adjust_heap(u32* first, int hole, int count, int zero, u32 v, SynthPred pr);
"""
def emit(va, A, N):
    return ("void FUN_%08x(u32* first, u32* last, SynthPred pr) {\n"
            "    for (; 1 < last - first; --last) {\n"
            "        u32 v = last[-1];\n        last[-1] = *first;\n"
            "        synth_adjust_heap(first, 0, (int)(last - first) - 1, 0, v, pr);\n    }\n}" % va,
            "?FUN_%08x@@YAXPAI0USynthPred@@@Z" % va)
