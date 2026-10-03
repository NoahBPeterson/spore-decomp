# Three 15-dword descriptors built on the stack and rep-movsd'd into globals (shape-equivalent dynamic initializer).
PATTERN = 'sub esp, N ; push esi ; push edi ; xor eax, eax ; mov edx, A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], N ; mov ecx, N ; lea esi, [esp + N] ; mov edi, A ; rep movsd dword ptr es:[edi], dword ptr [esi] ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], N ; mov ecx, N ; lea esi, [esp + N] ; mov edi, A ; rep movsd dword ptr es:[edi], dword ptr [esi] ; mov ecx, N ; lea esi, [esp + N] ; mov edi, A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], N ; rep movsd dword ptr es:[edi], dword ptr [esi] ; pop edi ; pop esi ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct S15 { const char *name; unsigned id; unsigned size; unsigned u0, u1, u2; unsigned z0, z1; void *f[7]; };
"""
def emit(va, A, N):
    sh = A[0]
    blocks = [(A[1], A[2], A[3:9], A[9], N[13]),
              (A[10], A[11], A[12:18], A[18], N[28]),
              (A[20], A[21], A[22:28], A[19], N[-2])]
    uniq = []
    def nm(f):
        n = "fn_%08x_%d" % (f, len(uniq)); uniq.append(n); return n
    names = [[nm(f) for f in b[2]] for b in blocks]
    decl = "".join("void %s();" % n for n in reversed(uniq)) + "void fn_%08x();" % sh
    def blk(i, b):
        name, ident, fns, dest, size = b
        return """  s.name = (const char*)0x%x; s.id = 0x%x;
  s.z0 = 0; s.z1 = 0;
  s.f[0] = (void*)fn_%08x;
%s
  s.size = 0x%x;
  g_%08x = s;
""" % (name, ident, sh, "\n".join("  s.f[%d] = (void*)%s;" % (j + 1, n) for j, n in enumerate(names[i])), size, dest)
    gd = "".join("extern S15 g_%08x;" % b[3] for b in blocks)
    src = """%s
extern "C" { %s }
void FUN_%08x() {
  S15 s;
%s}""" % (gd, decl, va, "".join(blk(i, b) for i, b in enumerate(blocks)))
    return src, "?FUN_%08x@@YAXXZ" % va
