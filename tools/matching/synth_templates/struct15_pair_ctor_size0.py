# Two 60-byte property descriptors (first offset 0, second nonzero) built via ctor temp and rep-movsd'd into globals.
# Same shape as prop_desc_three_stack_copy but two blocks; operands re-decoded from function bytes.
# Operands are re-decoded from the function bytes, since A/N operand order alone is ambiguous.
import os, re
import pefile, capstone
PATTERN = 'sub esp, N ; push esi ; push edi ; xor eax, eax ; mov edx, A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], eax ; mov ecx, N ; lea esi, [esp + N] ; mov edi, A ; rep movsd dword ptr es:[edi], dword ptr [esi] ; mov ecx, N ; lea esi, [esp + N] ; mov edi, A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], N ; rep movsd dword ptr es:[edi], dword ptr [esi] ; pop edi ; pop esi ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """typedef void (__cdecl *fp)();
struct T { const char* name; unsigned hash; int off; int p3, p4, p5; int z0, z1; fp f[7];
  T(const char* n, unsigned h, int o, fp f0, fp a, fp b, fp c, fp d, fp e, fp ff)
    : name(n), hash(h), z0(0), z1(0) { f[0]=f0; f[1]=a; f[2]=b; f[3]=c; f[4]=d; f[5]=e; f[6]=ff; off = o; } };
"""
_pe = pefile.PE(os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../../work/SporeApp.analysis.bin"), fast_load=True)
_md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
def _blocks(va):
    code = _pe.get_data(va - _pe.OPTIONAL_HEADER.ImageBase, 400)
    blocks, cur, f0, dest = [], {}, None, None
    for i in _md.disasm(code, va):
        o = i.op_str
        if i.mnemonic == "ret": break
        m = re.match(r"edx, (0x[0-9a-f]+)$", o) if i.mnemonic == "mov" else None
        if m: f0 = int(m.group(1), 16); continue
        m = re.match(r"edi, (0x[0-9a-f]+)$", o) if i.mnemonic == "mov" else None
        if m: dest = int(m.group(1), 16); continue
        m = re.match(r"dword ptr \[esp \+ (0x[0-9a-f]+|\d+)\], (.*)$", o) if i.mnemonic == "mov" else None
        if m:
            cur[int(m.group(1), 0)] = m.group(2); continue
        if i.mnemonic == "movs" or i.mnemonic.startswith("rep"):
            blocks.append((dest, cur)); cur = {}
    return f0, blocks
def emit(va, A, N):
    f0, blocks = _blocks(va)
    decls, stmts, seen = [], [], set()
    def ext(kind, a):
        if (kind, a) in seen: return
        seen.add((kind, a))
        decls.append({"s": "extern const char s_%08x[];", "f": "extern void __cdecl fn_%08x();", "g": "extern T g_%08x;", "a": "extern void __cdecl fa_%08x();"}[kind] % a)
    ext("f", f0)
    # Tie-break: cl keeps in a register the constant used most, last one wins a tie. f0 must win, so
    # one use of any competing address is spelled as an integer literal (not CSE'd with the symbol).
    from collections import Counter
    cnt = Counter(int(cur[k], 0) for _, cur in blocks for k in (0x2c, 0x30, 0x34, 0x38, 0x3c, 0x40))
    lit = {x for x, c in cnt.items() if c >= len(blocks)}
    for dest, cur in blocks:
        name = int(cur[8], 0); h = int(cur[0xc], 0)
        off = 0 if cur[0x10] == "eax" else int(cur[0x10], 0)
        fs = [int(cur[k], 0) for k in (0x2c, 0x30, 0x34, 0x38, 0x3c, 0x40)]
        ext("s", name); ext("g", dest)
        for x in fs: ext("f", x)
        args = []
        for j, x in enumerate(fs):
            if x in fs[:j]:
                ext("a", x); args.append("fa_%08x" % x)
            elif x in lit:
                lit.discard(x); args.append("(fp)0x%x" % x)
            else:
                args.append("fn_%08x" % x)
        stmts.append("  g_%08x = T(s_%08x, 0x%Xu, %d, fn_%08x, %s);" % (
            dest, name, h, off, f0, ", ".join(args)))
    src = "%s\nvoid FUN_%08x() {\n%s\n}" % ("\n".join(decls), va, "\n".join(stmts))
    return src, "?FUN_%08x@@YAXXZ" % va
