# Two 60-byte descriptors built on the stack and rep-movsd'd into globals (shape-equivalent dynamic initializer).
#   { name, hash, size, <3 uninit>, 0, 0, f[7] }; size stored last, f[6] hoisted into edx.
# Operands re-decoded from function bytes.
import os, re
import pefile, capstone
PATTERN = 'sub esp, N ; push esi ; push edi ; xor eax, eax ; mov edx, A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], N ; mov ecx, N ; lea esi, [esp + N] ; mov edi, A ; rep movsd dword ptr es:[edi], dword ptr [esi] ; mov ecx, N ; lea esi, [esp + N] ; mov edi, A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], N ; rep movsd dword ptr es:[edi], dword ptr [esi] ; pop edi ; pop esi ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """typedef void (__cdecl *fp)();
struct T { const char* name; unsigned hash; int off; int p3, p4, p5; int z0, z1; fp f[7];
  T(const char* n, unsigned h, int o, fp a, fp b, fp c, fp d, fp e, fp ff, fp g)
    : name(n), hash(h), z0(0), z1(0) { f[0]=a; f[1]=b; f[2]=c; f[3]=d; f[4]=e; f[5]=ff; f[6]=g; off = o; } };
"""
_pe = pefile.PE(os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../../work/SporeApp.analysis.bin"), fast_load=True)
_md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
def _blocks(va):
    code = _pe.get_data(va - _pe.OPTIONAL_HEADER.ImageBase, 400)
    blocks, cur, dest = [], {}, None
    for i in _md.disasm(code, va):
        o = i.op_str
        if i.mnemonic == "ret": break
        m = re.match(r"edi, (0x[0-9a-f]+)$", o) if i.mnemonic == "mov" else None
        if m: dest = int(m.group(1), 16); continue
        m = re.match(r"edx, (0x[0-9a-f]+)$", o) if i.mnemonic == "mov" else None
        if m: cur["edx"] = int(m.group(1), 16); continue
        m = re.match(r"dword ptr \[esp \+ (0x[0-9a-f]+|\d+)\], (.*)$", o) if i.mnemonic == "mov" else None
        if m:
            cur[int(m.group(1), 0)] = m.group(2); continue
        if i.mnemonic == "movs" or i.mnemonic.startswith("rep"):
            blocks.append((dest, cur)); cur = {k: v for k, v in cur.items() if k == "edx"}
    return blocks
def emit(va, A, N):
    blocks = _blocks(va)
    edx = blocks[0][1]["edx"]
    decls, stmts, seen = [], [], set()
    def ext(kind, a):
        if (kind, a) in seen: return
        seen.add((kind, a))
        decls.append({"s": "extern const char s_%08x[];", "f": "extern void __cdecl fn_%08x();", "g": "extern T g_%08x;"}[kind] % a)
    for dest, cur in blocks:
        name = int(cur[8], 0); h = int(cur[0xc], 0)
        size = int(cur[0x10], 0)
        fs = [int(cur[k], 0) for k in (0x28, 0x2c, 0x30, 0x34, 0x38, 0x3c, 0x40)] if 0x40 in cur and cur[0x40] != "edx" else [int(cur[k], 0) for k in (0x28, 0x2c, 0x30, 0x34, 0x38, 0x3c)] + [edx]
        ext("s", name); ext("g", dest)
        for x in fs: ext("f", x)
        stmts.append("  g_%08x = T(s_%08x, 0x%Xu, %d, %s);" % (dest, name, h, size, ", ".join("fn_%08x" % x for x in fs)))
    src = "%s\nvoid FUN_%08x() {\n%s\n}" % ("\n".join(decls), va, "\n".join(stmts))
    return src, "?FUN_%08x@@YAXXZ" % va
