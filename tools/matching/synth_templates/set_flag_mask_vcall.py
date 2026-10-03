# void f(uint mask, bool on): vcall slot with (field | mask) or (field & ~mask)
PATTERN = 'cmp byte ptr [esp + N], N ; mov eax, dword ptr [ecx + N] ; je +N ; or eax, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; push eax ; mov eax, dword ptr [edx + N] ; call eax ; ret N ; mov edx, dword ptr [esp + N] ; not edx ; and eax, edx ; mov edx, dword ptr [ecx] ; push eax ; mov eax, dword ptr [edx + N] ; call eax ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    f, v = N[2], N[4]
    k = v // 4
    s = "struct C_%08x {\n" % va
    for i in range(k + 1):
        s += "  virtual void s%d(unsigned);\n" % i
    if f // 4 - 1 > 0:
        s += "  unsigned pad[%d];\n" % (f // 4 - 1)
    s += "  unsigned fld;\n  void f_%08x(unsigned m, bool on);\n};\n" % va
    s += ("void C_%08x::f_%08x(unsigned m, bool on) {\n  unsigned x = fld; if (on) x |= m; else x &= ~m; s%d(x);\n}\n" % (va, va, k))
    return s, "?f_%08x@C_%08x@@QAEXI_N@Z" % (va, va)
