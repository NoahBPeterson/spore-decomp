# /Od member: ext(p, this); p->field = this->vfn_k();
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; push eax ; mov ecx, dword ptr [ebp + N] ; push ecx ; call EXT ; add esp, N ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [edx] ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [eax + N] ; call edx ; mov ecx, dword ptr [ebp + N] ; mov dword ptr [ecx + N], eax ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    vt = N[6] // 4
    mo = N[8]
    s = "struct O_%08x { int pad[%d]; int v; };\n" % (va, mo // 4)
    s += "void ext_%08x(O_%08x*, void*);\n" % (va, va)
    s += "struct C_%08x {\n" % va
    for i in range(vt):
        s += "  virtual void v%d();\n" % i
    s += "  virtual int vf();\n  void f(O_%08x* p);\n};\n" % va
    s += "void C_%08x::f(O_%08x* p) { ext_%08x(p, this); p->v = vf(); }\n" % (va, va, va)
    return s, "?f@C_%08x@@QAEXPAUO_%08x@@@Z" % (va, va)
