# 15-dword descriptor built on the stack and rep-movsd'd into a global (shape-equivalent form of a dynamic initializer).
PATTERN = 'sub esp, N ; push esi ; push edi ; xor eax, eax ; mov ecx, N ; lea esi, [esp + N] ; mov edi, A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], N ; rep movsd dword ptr es:[edi], dword ptr [esi] ; pop edi ; pop esi ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct S15 { const char *name; unsigned id; unsigned size; unsigned u0, u1, u2; unsigned z0, z1; void *f[7]; };
""" 
def emit(va, A, N):
    dest, name, ident = A[0], A[1], A[2]
    fns = A[3:10]
    size = N[-2]
    decl = "".join("void fn_%08x();" % f for f in sorted(set(fns)))
    src = """extern S15 g_%08x;
extern "C" { %s }
void FUN_%08x() {
  S15 s;
  s.name = (const char*)0x%x; s.id = 0x%x;
  s.z0 = 0; s.z1 = 0;
%s
  s.size = 0x%x;
  g_%08x = s;
}""" % (dest, decl, va, name, ident,
        "\n".join("  s.f[%d] = (void*)fn_%08x;" % (i, f) for i, f in enumerate(fns)), size, dest)
    return src, "?FUN_%08x@@YAXXZ" % va
