#!/usr/bin/env python3
"""Register-renaming + scheduling equivalence checker for two x86-32 functions (A = retail, B = ours).

ACCEPT means: the two functions have the same CFG (blocks in the same layout order, the same successors), and a
bijection pi between the instructions of each pair of corresponding blocks such that
  * each instruction and its image have the same operation and operand shape, registers abstracted (a renameable
    register operand is "the j-th distinct register family of this instruction", with its part: l8/h8/16/32/xmm);
    implicit registers, fixed registers (esp, st(i), segments), immediates and scales must be equal;
    relocated fields are symbols, compared through one global bijection; branch targets are block indices;
  * the def-use graph is the same under pi: for every use slot of every instruction (register families, the flag
    groups CF / OSZAP / DF, the x87 state FPU, MXCSR, esp), the set of definitions that reach it in A maps under pi
    onto the set that reaches the corresponding slot in B. Definitions are computed per program from its own
    physical registers (global reaching definitions), so a renaming may differ per live range (a "web"), and a
    reordering is accepted only when every use still sees the same producer. Entry values are pinned: "eax at
    entry" in A corresponds only to "eax at entry" in B;
  * memory operations (any memory operand, push/pop, call, ret, string ops) keep their relative order in each block;
  * pinned uses model the ABI: every ret reads the registers of the chosen level, every call reads and writes the
    registers of the chosen calling model, so each of those registers carries the same producer in both programs.
Partial-register writes are read-modify-write of the family, partial writes of a flag group read the group, zero
idioms (xor r,r / sub r,r / pxor/xorps x,x) read nothing. Indirect jumps (switch tables) are rejected. Relocated
fields are symbols matched through one bijection (consistency only: which retail address a name stands for is not
known here, as in the fingerprint gate).

Levels: 1 = ABI outputs (ret reads eax, esp, ebx, esi, edi, ebp, FPU; --ret64 adds edx);
        2 = all registers (ret reads every GPR, FPU and xmm0-7; every call reads every GPR and xmm0-7).
Call models (the k-th call of A is paired with the k-th call of B, and both get the same pinned slots):
  std   non-LTCG MSVC: a call reads esp, FPU, MXCSR, DF and its argument registers from the callee's decorated name
        on B's side (thiscall ecx, fastcall ecx+edx, cdecl/stdcall none, _chkstk/_alloca_probe eax, indirect calls
        ecx+edx, unknown names eax+ecx+edx); it writes eax, ecx, edx, xmm0-7, flags, FPU, MXCSR, preserves ebx..ebp.
  ltcg  a call reads every GPR and may write every GPR but esp (an unknown custom convention).
"""
import sys
import capstone
from capstone import x86_const as X

MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
MD.detail = True

GPR = ["eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"]
FAM = {}
for f, l8, h8, w in (("eax", "al", "ah", "ax"), ("ecx", "cl", "ch", "cx"), ("edx", "dl", "dh", "dx"),
                     ("ebx", "bl", "bh", "bx")):
    FAM.update({f: (f, "32"), l8: (f, "l8"), h8: (f, "h8"), w: (f, "16")})
for f, w in (("esi", "si"), ("edi", "di"), ("ebp", "bp"), ("esp", "sp")):
    FAM.update({f: (f, "32"), w: (f, "16")})
for k in range(8):
    FAM["xmm%d" % k] = ("xmm%d" % k, "xmm")
RENAMEABLE = {"eax", "ecx", "edx", "ebx", "esi", "edi", "ebp"} | {"xmm%d" % k for k in range(8)}
XMM = ["xmm%d" % k for k in range(8)]
STATUS = ["CF", "PF", "AF", "ZF", "SF", "OF"]


def _bits(prefix, names):
    return sum(getattr(X, "X86_EFLAGS_%s_%s" % (prefix, n), 0) for n in names)


F_TEST = _bits("TEST", STATUS + ["DF"])
F_WR = {n: _bits("MODIFY", [n]) | _bits("SET", [n]) | _bits("RESET", [n]) | _bits("UNDEFINED", [n]) for n in STATUS + ["DF"]}
IMPLICIT_MEM = ("push", "pop", "call", "ret", "leave", "enter", "movs", "stos", "lods", "cmps", "scas", "pushal",
                "popal", "pushfd", "popfd", "pushf", "popf")
SHIFTS = ("shl", "shr", "sar", "sal", "rol", "ror", "rcl", "rcr", "shld", "shrd")
FULL_XMM = ("movaps", "movups", "movapd", "movupd", "movdqa", "movdqu", "movd", "movq")


CANON_TEST = False      # optional peephole: test r32, imm<0x80 == test r8, imm
STD_SAFE = None         # callable(retail callee va) -> True when the standard call model is sound (facts.py)


class Reject(Exception):
    pass


class Ins:
    __slots__ = ("addr", "off", "size", "text", "mnem", "shape", "uses", "defs", "mem", "kind", "target", "rd")


def _mnem_full(i):
    return i.mnemonic


def decode(code, base, relocs, model, level, ret64):
    """-> list of Ins. relocs: {field offset in code: symbol token} (4-byte fields)."""
    out = []
    for i in MD.disasm(code, base):
        out.append(_one(i, base, relocs))
    if sum(x.size for x in out) != len(code):
        raise Reject("disassembly stops at +%#x (data in code?)" % sum(x.size for x in out))
    lo, hi = base, base + len(code)
    for x in out:
        _retmodel(x, model, level, ret64, lo, hi)
    return out


def _one(i, base, relocs):
    x = Ins()
    x.addr, x.off, x.size, x.mnem = i.address, i.address - base, i.size, i.mnemonic
    x.text = "%s %s" % (i.mnemonic, i.op_str)
    x.target = None
    prefix = tuple(p for p in i.prefix if p)
    fields = {}
    for o, n in ((i.disp_offset, i.disp_size), (i.imm_offset, i.imm_size)):
        if o and n == 4 and (x.off + o) in relocs:
            tok = relocs[x.off + o]
            if 0x64 in i.prefix and o == i.disp_offset and tok[0] == "abs" and tok[1] < 0x1000:
                continue      # fs:[0] (the SEH chain head): the retail mask covers it, an object has no relocation
            fields[o] = tok
    local = []           # renameable families in order of first appearance

    def reg(r):
        nm = i.reg_name(r)
        if nm in FAM and FAM[nm][0] in RENAMEABLE:
            f, part = FAM[nm]
            if f not in local:
                local.append(f)
            return ("R", local.index(f), part), f, part
        return ("P", nm), None, None

    shape = [i.mnemonic, prefix]
    acc = {}             # family -> set of 'r'/'w'/'pw' (partial write)
    fixed_r, fixed_w = set(), set()
    has_mem = False
    mem_size = 0
    narrow = None
    if CANON_TEST and i.mnemonic == "test" and len(i.operands) == 2 and i.operands[0].type == X.X86_OP_REG and \
            i.operands[1].type == X.X86_OP_IMM and 0 <= i.operands[1].imm < 0x80 and \
            i.reg_name(i.operands[0].reg) in ("eax", "ecx", "edx", "ebx", "al", "cl", "dl", "bl"):
        # test r32, imm (imm < 0x80) sets every flag as test r8low, imm does (ZF, PF from the low byte, SF = 0,
        # CF = OF = 0, AF undefined in both): compare both as the byte form
        narrow = True
    for op in i.operands:
        if op.type == X.X86_OP_REG:
            tok, f, part = reg(op.reg)
            if narrow:
                tok = (tok[0], tok[1], "l8")
            shape.append(("reg", tok, 1 if narrow else op.size))
            nm = i.reg_name(op.reg)
            if f:
                s = acc.setdefault(f, set())
                if op.access & 1:
                    s.add("r")
                if op.access & 2:
                    full_x = part == "xmm" and op.access == 2 and (i.mnemonic in FULL_XMM or (
                        i.mnemonic in ("movss", "movsd") and any(o.type == X.X86_OP_MEM for o in i.operands)))
                    s.add("w" if (part == "32" or full_x) else "pw")   # movss/movsd from memory zero the rest
            else:
                (fixed_r.add(nm) if op.access & 1 else None)
                (fixed_w.add(nm) if op.access & 2 else None)
        elif op.type == X.X86_OP_IMM:
            if i.imm_offset in fields:
                shape.append(("sym", fields[i.imm_offset]))
            else:
                shape.append(("imm", op.imm & 0xffffffff, 1 if narrow else op.size))
        elif op.type == X.X86_OP_MEM:
            m = op.mem
            has_mem = True
            mem_size = op.size
            b = reg(m.base)[0] if m.base else None
            ix = reg(m.index)[0] if m.index else None
            for r in (m.base, m.index):
                if r:
                    nm = i.reg_name(r)
                    if nm in FAM and FAM[nm][0] in RENAMEABLE:
                        acc.setdefault(FAM[nm][0], set()).add("r")
                    else:
                        fixed_r.add(nm)
            disp = ("sym", fields[i.disp_offset]) if i.disp_offset in fields else ("imm", m.disp & 0xffffffff)
            seg = i.reg_name(m.segment) if m.segment else None
            shape.append(("mem", seg, b, ix, m.scale, disp, op.size, op.access))
        else:
            raise Reject("unknown operand type at %#x" % x.addr)
    # implicit registers: those capstone reports beyond the explicit operands
    rr, ww = i.regs_access()
    imp = []
    explicit = set()
    for op in i.operands:
        if op.type == X.X86_OP_REG:
            explicit.add(i.reg_name(op.reg))
        elif op.type == X.X86_OP_MEM:
            explicit |= {i.reg_name(r) for r in (op.mem.base, op.mem.index, op.mem.segment) if r}
    for r, mode in [(r, "r") for r in rr] + [(r, "w") for r in ww]:
        nm = i.reg_name(r)
        if nm in ("eflags", "eip", "flags") or nm in explicit:
            continue
        if nm in FAM:
            f, part = FAM[nm]
            if f in local:                      # explicit: merge an implicit access into the explicit slot
                s = acc.setdefault(f, set())
                s.add("r" if mode == "r" else ("w" if part in ("32", "xmm") else "pw"))
                shape.append(("impx", nm, mode))
                continue
            if f in RENAMEABLE:
                imp.append((nm, mode))
            else:
                (fixed_r if mode == "r" else fixed_w).add(nm)
        else:
            (fixed_r if mode == "r" else fixed_w).add(nm)
    shape.append(("imp", tuple(sorted(set(imp)))))
    shape.append(("fixed", tuple(sorted(fixed_r)), tuple(sorted(fixed_w))))
    mn = i.mnemonic
    # zero idioms read nothing
    if mn in ("xor", "sub", "pxor", "xorps", "xorpd") and len(i.operands) == 2 and \
            all(o.type == X.X86_OP_REG for o in i.operands) and i.operands[0].reg == i.operands[1].reg:
        f = FAM.get(i.reg_name(i.operands[0].reg), (None,))[0]
        if f in acc and FAM[i.reg_name(i.operands[0].reg)][1] in ("32", "xmm"):
            acc[f] = {"w"}
    uses, defs = [], []
    for j, f in enumerate(local):
        s = acc.get(f, set())
        if "r" in s or "pw" in s:
            uses.append((("e", j), f))
        if "w" in s or "pw" in s:
            defs.append((("e", j), f))
    for nm, mode in sorted(set(imp)):
        f, part = FAM[nm]
        key = ("i", f)
        if mode == "r" and (key, f) not in uses:
            uses.append((key, f))
        if mode == "w":
            if (key, f) not in defs:
                defs.append((key, f))
            if part not in ("32",) and (key, f) not in uses:
                uses.append((key, f))
    for nm in sorted(fixed_r):
        f = FAM.get(nm, (nm,))[0]
        uses.append((("f", f), _fixres(f)))
    for nm in sorted(fixed_w):
        f = FAM.get(nm, (nm,))[0]
        defs.append((("f", f), _fixres(f)))
        if nm in FAM and FAM[nm][1] != "32" and (("f", f), f) not in uses:
            uses.append((("f", f), _fixres(f)))
    # flags, in three groups that instructions write as a whole or not at all: CF, OSZAP (OF SF ZF AF PF), DF
    ef = i.eflags
    hasx = any(f.startswith("xmm") for f in local) or any(n.startswith("xmm") for n, _ in imp)
    string = mn.rstrip("bwdq") in ("movs", "stos", "lods", "cmps", "scas") and not hasx
    if mn.startswith("f"):        # x87: capstone's field holds FPU flags here
        rd = {"CF", "ZF", "PF"} if mn.startswith("fcmov") else set()
        wr = set(STATUS) if mn in ("fcomi", "fcomip", "fucomi", "fucomip") else set()
    elif hasx:                    # SSE: only the comis family touches EFLAGS
        rd = set()
        wr = set(STATUS) if mn in ("comiss", "ucomiss", "comisd", "ucomisd") else set()
    else:
        rd = {n for n in STATUS if ef & _bits("TEST", [n])}
        wr = {n for n in STATUS + ["DF"] if ef & F_WR[n]}
        if string:
            rd.add("DF")
        if mn in ("pushfd", "pushf", "lahf"):
            rd |= set(STATUS) | {"DF"}
        if mn in ("popfd", "popf"):
            wr = set(STATUS) | {"DF"}
        if mn == "sahf":
            wr = set(STATUS) - {"OF"}
        if mn in SHIFTS and not (len(i.operands) >= 2 and i.operands[-1].type == X.X86_OP_IMM and i.operands[-1].imm & 31):
            rd |= wr              # a count of 0 (cl, or an immediate 0) leaves the flags alone
    for g, names in (("CF", {"CF"}), ("OSZAP", {"OF", "SF", "ZF", "AF", "PF"}), ("DF", {"DF"})):
        w = wr & names
        r = bool(rd & names) or bool(w and w != names)      # a partial group write keeps the rest: read-modify-write
        if r:
            uses.append((("F", g), g))
        if w:
            defs.append((("F", g), g))
    # x87 state and MXCSR
    x87 = (mn.startswith("f") and not mn.startswith(("fxsave", "fxrstor"))) or any(n.startswith("st") for n in fixed_r | fixed_w)
    if x87 or mn in ("emms",):
        uses.append((("FPU",), "FPU"))
        defs.append((("FPU",), "FPU"))
    if hasx or mn == "stmxcsr":
        uses.append((("MX",), "MXCSR"))
    if mn == "ldmxcsr":
        defs.append((("MX",), "MXCSR"))
    x.mem = (has_mem and mn not in ("lea", "nop") and not mn.startswith("prefetch")) or string or \
        mn in IMPLICIT_MEM or mn.startswith(("push", "pop", "ret"))
    # control flow
    x.kind = "other"
    if mn == "ret" or mn == "retn":
        x.kind = "ret"
    elif mn == "call":
        x.kind = "call"
    elif mn == "jmp" or (mn.startswith("j") and mn != "jmp") or mn in ("loop", "loope", "loopne", "jecxz"):
        x.kind = "jmp" if mn == "jmp" else "jcc"
    elif mn in ("int3", "ud2", "int", "hlt"):
        x.kind = "trap"
    if x.kind in ("jmp", "jcc", "call"):
        op = i.operands[0]
        if op.type == X.X86_OP_IMM:
            field = x.size - 4 if x.size >= 5 else None
            tok = relocs.get(x.off + field) if field is not None else None
            x.target = ("sym", tok) if tok is not None else ("abs", op.imm & 0xffffffff)
            shape = [s for s in shape if not (isinstance(s, tuple) and s and s[0] in ("imm", "sym"))]
        elif x.kind != "call":
            raise Reject("indirect jump at +%#x (%s): switch tables are not handled" % (x.off, x.text))
    x.shape = shape
    x.uses, x.defs = uses, defs
    return x


def _fixres(f):
    if f.startswith("st") or f in ("fpsw", "fpcw", "fpsr", "fpcr"):
        return "FPU"
    return f


CALL_ALL = ["eax", "ecx", "edx", "ebx", "esi", "edi", "ebp", "esp"]


def conv_reads(tok):
    """The registers a call can read as arguments, from the callee's decorated name (the object side's relocation).
    None when unknown: the caller then assumes eax, ecx and edx."""
    if tok is None:
        return ["ecx", "edx"]                           # an indirect call: thiscall or fastcall at most
    if not (isinstance(tok, tuple) and tok[0] == "sym"):
        return None
    nm = tok[1]
    if nm.startswith("__imp_"):
        nm = nm[6:]
    if nm.startswith(("__chkstk", "__alloca_probe", "__ftol", "__CI", "__ftoui", "__dtoui", "__ultod")):
        return ["eax"] if nm.startswith(("__chkstk", "__alloca_probe")) else []
    if nm.startswith("@"):
        return ["ecx", "edx"]                           # __fastcall
    if nm.startswith("?"):
        import re
        m = re.search(r"@@(?:[QRUVABEFIJMN][A-D]|[CDKLSTYZ])([AEGI])", nm)
        if not m:
            return None
        return {"A": [], "E": ["ecx"], "G": [], "I": ["ecx", "edx"]}[m.group(1)]
    if nm.startswith("_"):
        return []                                       # C __cdecl or __stdcall
    return None


def _retmodel(x, model, level, ret64, lo, hi):
    """Pinned uses of rets and tail jumps (the ABI); calls are modelled in pairs by model_calls."""
    allg = CALL_ALL
    if x.kind in ("jmp", "jcc") and x.target and x.target[0] == "abs" and lo <= x.target[1] < hi:
        return
    if x.kind in ("jmp", "jcc") and x.target is not None:
        x.kind = "tail" if x.kind == "jmp" else "tailcc"
    if x.kind in ("ret", "tail", "tailcc"):
        if level == 2:
            reads = allg + XMM + ["FPU"]
        else:
            reads = ["eax", "esp", "ebx", "esi", "edi", "ebp", "FPU"] + (["edx"] if ret64 else [])
        if x.kind != "ret":       # a tail call also reads what a call can read
            reads = sorted(set(reads) | set(allg) | {"MXCSR"})
        _addpin(x, reads, [])


def model_calls(A, B, model, level):
    """The k-th call of A and of B (calls keep their order: they are memory operations in blocks in the same order)
    read and write the same pinned registers, from B's callee name when it has one."""
    ca = [x for x in A if x.kind == "call"]
    cb = [x for x in B if x.kind == "call"]
    if len(ca) != len(cb):
        raise Reject("%d calls in A, %d in B" % (len(ca), len(cb)))
    for a, b in zip(ca, cb):
        # the standard model (callee reads only its arguments) is sound only when the callee really kills
        # eax/ecx/edx; otherwise a caller may keep one of them across the call (same-file or /LTCG callers)
        unsafe = (STD_SAFE is not None and a.target is not None and a.target[0] == "abs"
                  and not STD_SAFE(a.target[1]))
        if model == "ltcg" or level == 2 or unsafe or a.target is None:
            reads = CALL_ALL + (XMM if level == 2 else [])
        else:
            tok = b.target[1] if b.target else None
            r = conv_reads(tok)
            reads = (["eax", "ecx", "edx"] if r is None else r) + ["esp"]
        allw = model == "ltcg" or unsafe or a.target is None
        writes = (["eax", "ecx", "edx", "ebx", "esi", "edi", "ebp"] if allw else ["eax", "ecx", "edx"]) + XMM
        for x in (a, b):
            _addpin(x, reads + ["FPU", "MXCSR", "DF"], writes + ["CF", "OSZAP", "DF", "FPU", "MXCSR"])


def _addpin(x, reads, writes):
    for r in reads:
        x.uses.append((("pin", r), r))
    for r in writes:
        if not any(res == r for _, res in x.defs):
            x.defs.append((("pin", r), r))


def blocks(ins, base, size):
    lo, hi = base, base + size
    starts = {ins[0].addr}
    addrs = {i.addr: k for k, i in enumerate(ins)}
    for k, i in enumerate(ins):
        if i.kind in ("jmp", "jcc"):
            t = i.target[1]
            if t not in addrs:
                raise Reject("branch at +%#x goes into the middle of an instruction" % i.off)
            starts.add(t)
        if i.kind in ("jmp", "jcc", "ret", "tail", "tailcc", "trap") and k + 1 < len(ins):
            starts.add(ins[k + 1].addr)
    st = sorted(starts)
    bidx = {a: n for n, a in enumerate(st)}
    bl = []
    for n, a in enumerate(st):
        e = st[n + 1] if n + 1 < len(st) else hi
        bl.append([k for k, i in enumerate(ins) if a <= i.addr < e])
    succ = []
    for n, b in enumerate(bl):
        last = ins[b[-1]]
        s = []
        if last.kind == "jcc" or last.kind == "tailcc":
            s.append(n + 1)
            if last.kind == "jcc":
                s.append(bidx[last.target[1]])
        elif last.kind == "jmp":
            s.append(bidx[last.target[1]])
        elif last.kind in ("ret", "tail", "trap"):
            pass
        elif n + 1 < len(bl):
            s.append(n + 1)
        succ.append(s)
    for i in ins:
        if i.kind in ("jmp", "jcc"):
            i.target = ("blk", bidx[i.target[1]])
    return bl, succ


def reaching(ins, bl, succ):
    """For each instruction, rd[slot] = frozenset of def ids reaching that use. Def ids: ('entry', res) or (k, slot)."""
    nb = len(bl)
    preds = [[] for _ in range(nb)]
    for n, s in enumerate(succ):
        for m in s:
            preds[m].append(n)
    allres = set()
    for i in ins:
        allres |= {r for _, r in i.uses} | {r for _, r in i.defs}
    entry = {r: frozenset([("entry", r)]) for r in allres}
    IN = [None] * nb
    OUT = [None] * nb

    def run(n, state, record):
        st = dict(state)
        for k in bl[n]:
            i = ins[k]
            if record:
                i.rd = {slot: st.get(r, frozenset()) for slot, r in i.uses}
            for slot, r in i.defs:
                st[r] = frozenset([(k, slot)])
        return st

    changed = True
    while changed:
        changed = False
        for n in range(nb):
            if n == 0:
                st = dict(entry)
            else:
                st = {}
            for p in preds[n]:
                if OUT[p] is not None:
                    for r, v in OUT[p].items():
                        st[r] = st.get(r, frozenset()) | v
            if n != 0 and not preds[n]:
                st = dict(entry)        # unreachable block (EH funclet): treat as an entry, pinned
            if st != IN[n] or OUT[n] is None:
                IN[n] = st
                o = run(n, st, False)
                if o != OUT[n]:
                    OUT[n] = o
                    changed = True
    for n in range(nb):
        run(n, IN[n], True)


class Checker:
    def __init__(self, A, B):
        self.A, self.B = A, B
        self.pi = {}           # A ins index -> B ins index
        self.sym = {}          # A symbol token -> B token
        self.symr = {}

    def mapdef(self, d):
        if d[0] == "entry":
            return d
        k, slot = d
        return (self.pi[k], slot) if k in self.pi else None

    def symok(self, a, b, commit):
        if a in self.sym or b in self.symr:
            return self.sym.get(a) == b and self.symr.get(b) == a
        if commit:
            self.sym[a], self.symr[b] = b, a
        return True

    def shape_eq(self, a, b, commit):
        if len(a.shape) != len(b.shape) or a.kind != b.kind:
            return False
        pend = []
        for s, t in zip(a.shape, b.shape):
            if isinstance(s, tuple) and s and s[0] == "sym":
                if not isinstance(t, tuple) or t[0] != "sym":
                    return False
                pend.append((s[1], t[1]))
            elif isinstance(s, tuple) and s and s[0] == "mem":
                if not (isinstance(t, tuple) and t[0] == "mem"):
                    return False
                if s[:5] != t[:5] or s[6:] != t[6:]:
                    return False
                if s[5][0] != t[5][0]:
                    return False
                if s[5][0] == "sym":
                    pend.append((s[5][1], t[5][1]))
                elif s[5] != t[5]:
                    return False
            elif s != t:
                return False
        ta, tb = a.target, b.target
        if (ta is None) != (tb is None):
            return False
        if ta is not None:
            if ta[0] != tb[0]:
                return False
            if ta[0] == "blk" and ta != tb:
                return False
            if ta[0] == "abs":
                return False                  # an unrelocated external target: not comparable
            if ta[0] == "sym":
                pend.append((ta[1], tb[1]))
        if not all(self.symok(x, y, False) for x, y in pend):
            return False
        # tentative: two pending pairs of this instruction must agree with each other
        if commit:
            for x, y in pend:
                self.symok(x, y, True)
        return True

    def uses_ok(self, a, b, final):
        """the reaching definitions of each use slot correspond. -> None or a reason"""
        ka = {s for s, _ in a.uses}
        kb = {s for s, _ in b.uses}
        if ka != kb:
            return "use slots differ (%s vs %s)" % (sorted(map(str, ka - kb)), sorted(map(str, kb - ka)))
        resa = dict(a.uses)
        for slot in ka:
            da, db = a.rd[slot], b.rd[slot]
            m = [self.mapdef(d) for d in da]
            if None in m:
                if final:
                    return "use %s has an unmapped definition" % (slot,)
                continue
            if frozenset(m) != db:
                return "operand %s (%s) reads a different producer: A %s, B %s" % (
                    self._slotname(slot, resa[slot]), resa[slot], self._defs(self.A, da), self._defs(self.B, db))
        return None

    def _slotname(self, slot, res):
        return {"e": "explicit reg #%s" % (slot[1],) if len(slot) > 1 else "", "i": "implicit", "pin": "ABI",
                "f": "fixed", "F": "flags", "FPU": "x87", "MX": "mxcsr"}.get(slot[0], str(slot))

    def _defs(self, P, ds):
        out = []
        for d in sorted(ds, key=str):
            if d[0] == "entry":
                out.append("entry")
            else:
                out.append("+%#x %s" % (P.ins[d[0]].off, P.ins[d[0]].text))
        return "{" + ", ".join(out) + "}"


class Prog:
    def __init__(self, code, base, relocs, model, level, ret64):
        self.code, self.base = code, base
        self.ins = decode(code, base, relocs, model, level, ret64)
        self.bl, self.succ = blocks(self.ins, base, len(code))

    def finish(self):
        reaching(self.ins, self.bl, self.succ)


def check(codeA, baseA, relA, codeB, baseB, relB, model="std", level=1, ret64=False, budget=200000):
    """-> (True, info) or (False, reason)"""
    try:
        A = Prog(codeA, baseA, relA, model, level, ret64)
        B = Prog(codeB, baseB, relB, model, level, ret64)
        model_calls(A.ins, B.ins, model, level)
        A.finish()
        B.finish()
    except Reject as e:
        return False, str(e)
    if len(A.bl) != len(B.bl):
        return False, "different number of basic blocks (%d vs %d)" % (len(A.bl), len(B.bl))
    if A.succ != B.succ:
        n = next(n for n in range(len(A.succ)) if A.succ[n] != B.succ[n])
        return False, "CFG differs at block %d (A +%#x successors %s, B +%#x successors %s)" % (
            n, A.ins[A.bl[n][0]].off, A.succ[n], B.ins[B.bl[n][0]].off, B.succ[n])
    C = Checker(A, B)
    steps = [0]
    reasons = []
    for n in range(len(A.bl)):
        ba, bb = A.bl[n], B.bl[n]
        if len(ba) != len(bb):
            return False, "block %d (A +%#x) has %d instructions, B %d" % (n, A.ins[ba[0]].off, len(ba), len(bb))
        mema = [k for k in ba if A.ins[k].mem]
        memb = [k for k in bb if B.ins[k].mem]
        if len(mema) != len(memb):
            return False, "block %d: %d memory operations in A, %d in B" % (n, len(mema), len(memb))
        memidx_a = {k: j for j, k in enumerate(mema)}
        memidx_b = {k: j for j, k in enumerate(memb)}
        used = set()
        best = [None]

        def dfs(p):
            steps[0] += 1
            if steps[0] > budget:
                raise Reject("search budget exhausted")
            if p == len(ba):
                return True
            ka = ba[p]
            a = A.ins[ka]
            for kb in bb:
                if kb in used:
                    continue
                b = B.ins[kb]
                if a.mem != b.mem or (a.mem and memidx_a[ka] != memidx_b[kb]):
                    continue
                saved = (dict(C.sym), dict(C.symr))
                if not C.shape_eq(a, b, True):
                    C.sym, C.symr = saved
                    if best[0] is None or best[0][0] < p:
                        best[0] = (p, "no instruction of B's block matches A +%#x %s" % (a.off, a.text))
                    continue
                C.pi[ka] = kb
                why = C.uses_ok(a, b, False)
                if why is None:
                    used.add(kb)
                    if dfs(p + 1):
                        return True
                    used.discard(kb)
                else:
                    if best[0] is None or best[0][0] <= p:
                        best[0] = (p, "A +%#x %s / B +%#x %s: %s" % (a.off, a.text, b.off, b.text, why))
                del C.pi[ka]
                C.sym, C.symr = saved
            if best[0] is None or best[0][0] < p:
                best[0] = (p, "no instruction of B's block matches A +%#x %s" % (a.off, a.text))
            return False

        try:
            ok = dfs(0)
        except Reject as e:
            return False, str(e)
        except RecursionError:
            return False, "block too long for the search"
        if not ok:
            return False, "block %d: %s" % (n, best[0][1] if best[0] else "no match")
    # final verification of every use, including uses reached across back edges
    for ka, kb in C.pi.items():
        why = C.uses_ok(A.ins[ka], B.ins[kb], True)
        if why:
            return False, "A +%#x %s / B +%#x %s: %s" % (A.ins[ka].off, A.ins[ka].text, B.ins[kb].off, B.ins[kb].text, why)
    moved = sum(1 for n in range(len(A.bl)) for p, ka in enumerate(A.bl[n]) if C.pi[ka] != B.bl[n][p])
    renamed = sum(1 for ka, kb in C.pi.items() if A.ins[ka].text != B.ins[kb].text and A.ins[ka].kind == "other")
    ident = all(A.ins[ka].text == B.ins[kb].text for ka, kb in C.pi.items() if A.ins[ka].kind == "other")
    return True, "%d instructions, %d blocks, %d moved, %d with other register names%s" % (
        len(A.ins), len(A.bl), moved, renamed, " (identical text)" if ident and not moved else "")


sys.setrecursionlimit(20000)

if __name__ == "__main__":
    print(__doc__)
