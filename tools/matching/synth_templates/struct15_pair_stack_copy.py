# NOTE: fns repeated across the two blocks (other than slot 0) get a distinct alias symbol in block 2, because
# cl would otherwise hoist the wrong repeated constant into edx (original hoists only slot 0). Relocs are masked.
# Two back-to-back 15-dword descriptors built on the stack, rep-movsd'd into globals (shape-equivalent dynamic initializer).
PATTERN = 'sub esp, N ; push esi ; push edi ; xor eax, eax ; mov edx, A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], N ; mov ecx, N ; lea esi, [esp + N] ; mov edi, A ; rep movsd dword ptr es:[edi], dword ptr [esi] ; mov ecx, N ; lea esi, [esp + N] ; mov edi, A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], N ; rep movsd dword ptr es:[edi], dword ptr [esi] ; pop edi ; pop esi ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct S15 { const char *name; unsigned id; unsigned size; unsigned u0, u1, u2; unsigned z0, z1; void *f[7]; };
"""
def emit(va, A, N):
    sh = A[0]
    b1 = (A[1], A[2], A[3:9], A[9], N[13])
    b2 = (A[11], A[12], A[13:19], A[10], N[-2])
    order = []
    for f in [sh] + list(b1[2]) + list(b2[2]):
        if f not in order: order.append(f)
    alias = set(f for f in b2[2] if f in b1[2] and f != sh)
    decl = "".join("void fn_%08x();" % f for f in order) + "".join("void fn_%08x_b();" % f for f in sorted(alias))
    def blk(b):
        name, ident, fns, dest, size = b
        nm = lambda f: "fn_%08x_b" % f if (b is b2 and f in alias) else "fn_%08x" % f
        return """  s.name = (const char*)0x%x; s.id = 0x%x;
  s.z0 = 0; s.z1 = 0;
  s.f[0] = (void*)fn_%08x;
%s
  s.size = 0x%x;
  g_%08x = s;
""" % (name, ident, sh, "\n".join("  s.f[%d] = (void*)%s;" % (i + 1, nm(f)) for i, f in enumerate(fns)), size, dest)
    src = """extern S15 g_%08x; extern S15 g_%08x;
extern "C" { %s }
void FUN_%08x() {
  S15 s;
%s%s}""" % (b1[3], b2[3], decl, va, blk(b1), blk(b2))
    return src, "?FUN_%08x@@YAXXZ" % va
