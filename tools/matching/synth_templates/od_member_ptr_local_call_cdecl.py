# /Od cdecl f(int a, C* c): local member-function pointer (8 bytes, MI class) to a thiscall member, invoked on c.
#   void (C::*pmf)(int) = &C::target; (c->*pmf)(a);
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], A ; mov dword ptr [ebp - N], N ; mov eax, dword ptr [ebp - N] ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp + N] ; push edx ; mov ecx, dword ptr [ebp + N] ; add ecx, dword ptr [ebp - N] ; call dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    t = "%08x" % va
    tgt = "%08x" % A[0]
    src = ("struct B1_%s { int x; }; struct B2_%s { int y; };\n"
           "struct C_%s : B1_%s, B2_%s { void FUN_%s(int a); };\n"
           "void __cdecl FUN_%s(int a, C_%s* c) {\n"
           "  void (C_%s::*pmf)(int) = &C_%s::FUN_%s;\n  (c->*pmf)(a);\n}") % (
           t, t, t, t, t, tgt, t, t, t, t, tgt)
    return src, "?FUN_%s@@YAXHPAUC_%s@@@Z" % (t, t)
