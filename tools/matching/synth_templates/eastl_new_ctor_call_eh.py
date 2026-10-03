# Factory "return new(\"Name\",0,0,0,0) T;" with an out-of-line ctor that may throw, in a /GS- module:
# full old-style EH frame (push -1; push handler; fs:[0] chain), ctor via call (result returned in eax),
# __fastcall/thiscall with an unused ecx (only the allocation slot is spilled).
PATTERN = 'push -N ; push A ; mov eax, dword ptr fs:[N] ; push eax ; mov dword ptr fs:[N], esp ; push ecx ; push N ; push N ; push N ; push N ; push A ; push N ; call EXT ; add esp, N ; mov dword ptr [esp], eax ; mov dword ptr [esp + N], N ; test eax, eax ; je +N ; mov ecx, eax ; call EXT ; mov ecx, dword ptr [esp + N] ; mov dword ptr fs:[N], ecx ; add esp, N ; ret  ; mov ecx, dword ptr [esp + N] ; xor eax, eax ; mov dword ptr fs:[N], ecx ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* operator new(size_t, const char*, int, unsigned, const char*, int);\n"
           "void operator delete(void*, const char*, int, unsigned, const char*, int);\n")

def emit(va, A, N):
    t = "T_%08x" % va
    src = ("extern const char s_%08x[];\n"
           "struct %s { %s(); char d[%d]; };\n"
           "void* __fastcall FUN_%08x(void*) { return new(s_%08x, 0, 0u, (const char*)0, 0) %s; }"
           % (A[1], t, t, N[7], va, A[1], t))
    return src, "?FUN_%08x@@YIPAXPAX@Z" % va
