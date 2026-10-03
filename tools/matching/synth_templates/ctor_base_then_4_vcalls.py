# Ctor-like: call base init, then 4 virtual calls (same slot) with constant args.
PATTERN = 'push esi ; mov esi, ecx ; call EXT ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; push A ; mov ecx, esi ; call edx ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; push A ; mov ecx, esi ; call edx ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; push A ; mov ecx, esi ; call edx ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; push A ; mov ecx, esi ; call edx ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """typedef void (__thiscall *VFn)(void*, unsigned);
#define VCALL(o, off, a) ((VFn)(*(void***)(o))[(off)/4])((o), (a))
"""
def emit(va, A, N):
    off = N[0]
    lines = "".join("    VCALL(self, 0x%x, 0x%x);\n" % (off, a) for a in A[:4])
    src = "void __fastcall ext_%08x(void*);\nvoid __fastcall FUN_%08x(void* self) {\n    ext_%08x(self);\n%s}" % (va, va, va, lines)
    return src, "?FUN_%08x@@YIXPAX@Z" % va
