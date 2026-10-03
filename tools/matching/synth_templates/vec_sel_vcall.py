# Bounds-checked pointer-vector element (selected index) -> null if out of range -> tail virtual call.
PATTERN = 'mov eax, dword ptr [ecx + N] ; test eax, eax ; jl +N ; mov edx, dword ptr [ecx + N] ; sub edx, dword ptr [ecx + N] ; sar edx, N ; cmp eax, edx ; jge +N ; mov ecx, dword ptr [ecx + N] ; mov eax, dword ptr [ecx + eax*N] ; jmp +N ; xor eax, eax ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; jmp eax'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""
def emit(va, A, N):
    sel, vbeg, off = N[0], N[2], N[-1]
    slot = off // 4
    pads = "".join("virtual void p%d(); " % i for i in range(slot))
    s = ("struct O_@@ { " + pads + "virtual void f(); };\n"
         "struct V_@@ { O_@@** b; O_@@** e; O_@@** c;\n"
         "  int size() const { return (int)(e - b); }\n"
         "  O_@@* const& operator[](int i) const { return b[i]; } };\n"
         "struct C_@@ { char pad0[" + str(vbeg) + "]; V_@@ v; char pad1[" + str(sel - vbeg - 12) + "]; int sel;\n"
         "  O_@@* get() const { return (sel >= 0 && sel < v.size()) ? v[sel] : 0; }\n"
         "  void m() { get()->f(); } };\n"
         "void __fastcall FUN_@@(C_@@* t) { t->m(); }\n")
    return s.replace("@@", "%08x" % va), "?FUN_%08x@@YIXPAUC_%08x@@@Z" % (va, va)
