# void C::f(bool b){ m_b = b; if (m_p) m_p->vfn(1, b)?? } -> store byte, null-check member ptr, virtual call slot with (1, flag)
PATTERN = "mov eax, dword ptr [esp + N] ; mov byte ptr [ecx + N], al ; mov ecx, dword ptr [ecx + N] ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; push eax ; mov eax, dword ptr [edx + N] ; push N ; call eax ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    foff, poff, slot, one = N[1], N[2], N[3] // 4, N[4]
    s = "struct T_%08x { " % va
    s += "".join("virtual void v%d(int,int){} " % i for i in range(slot))
    s += "virtual void vt(int a,int b){} };\n"
    s += "struct C_%08x {\n  virtual void c0();\n" % va
    s += "  char pad0[%d]; char f; char pad1[%d]; T_%08x* p;\n" % (foff - 4, poff - foff - 1, va)
    s += "  void fn(int b);\n};\n"
    s += "void C_%08x::fn(int b) { f = (char)b; if (p) p->vt(%d, b); }\n" % (va, one)
    return s.replace("vt(", "v%d(" % slot) if False else s.replace("vt", "v%d" % slot), "?fn@C_%08x@@QAEXH@Z" % va
