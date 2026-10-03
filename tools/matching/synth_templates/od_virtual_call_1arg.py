# /Od cdecl wrapper calling virtual slot (vtable offset N[3]) of arg1 with arg2:
#   void f(C* p, int a) { p->vfn(a); }
PATTERN = 'push ebp ; mov ebp, esp ; mov eax, dword ptr [ebp + N] ; push eax ; mov ecx, dword ptr [ebp + N] ; mov edx, dword ptr [ecx] ; mov ecx, dword ptr [ebp + N] ; mov eax, dword ptr [edx + N] ; call eax ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    t = "%08x" % va
    idx = N[3] // 4
    cls = "C_" + t
    body = "".join("virtual void v%d(int);\n" % i for i in range(idx)) + "virtual void v%d(int);" % idx
    src = "struct %s { %s };\nvoid FUN_%s(%s* p, int a) { p->v%d(a); }" % (cls, body, t, cls, idx)
    return src, "?FUN_%s@@YAXPAU%s@@H@Z" % (t, cls)
