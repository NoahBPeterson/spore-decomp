"""Layer 3 (tools/equiv/LAYERS.md): DDEC, STOKE's data-driven equivalence checker, for functions with loops.

DDEC (Sharma, Schkufza, Churchill, Aiken, "Data-driven equivalence checking", OOPSLA 2013) runs both programs on
testcases, picks matching cutpoints (loop heads) in the two control-flow graphs, learns a simulation invariant at
each from the states seen there (linear equalities between the two programs' registers, memory equality, ...), and
proves with Z3 that the invariants are inductive and imply equal outputs. A `proved` here is that SMT proof; the
testcases only guide the search. DDEC never produces counterexamples, so `refuted` comes only from a concrete run
(unicorn) of the two functions from the function entry that ends in a different observable state.

How a function becomes STOKE input (fully automatic):
  1. Relocations. Our relocated fields are paired with retail's in field order through one bijection (a symbol, or
     a DLL address, stands for exactly one retail address; data symbols keep their offsets), and rewritten to the
     retail values; both functions are placed at the retail address. Call targets thus become retail addresses on
     both sides; data addresses are moved by DATA_SHIFT on both sides (offsets kept), so that testcase memory
     never overlaps STOKE's own process image.
  2. Translation 32-bit -> x86-64 (STOKE's ISA). Every instruction keeps its operand size. Every memory operand
     keeps its 32-bit registers, i.e. x64asm emits the 0x67 address-size prefix and the address is computed mod
     2^32 exactly as on the 32-bit machine (absolute operands use %r11d = 0 as base). push/pop/leave become
     lea/mov on %esp (lea leaves the flags alone, like push/pop).
  3. Calls split the function into segments: segment 0 runs from the entry, segment k from the instruction after
     the k-th call (calls are paired by address order). A call is an exit of its segment: it pushes a per-call-site
     return token (the same in both programs; return addresses are compared modulo relocation), puts the callee's
     address (or the computed target of an indirect call) in %r8d and returns. A ret puts 0 in %r8d after popping
     its return address and N bytes; a jump out of the function (tail call) puts its target in %r8d.
     Each segment is checked from "both states equal" (every GPR, %r8, memory; xmm0-7 when used) to equal
     outputs at every exit: every GPR, %r8d and all of memory (the stack too). DF is not modelled by STOKE; no
     accepted instruction reads or writes it (string instructions, std/cld, pushf/popf are rejected). Callees are uninterpreted:
     equal inputs give equal outputs, so equal states after a call follow from equal states before it, which is
     why every register is compared at a call exit at both levels. At a ret or tail exit the level decides:
     L1 overwrites ecx (and edx unless meta "ret64") and xmm0-7 with constants in both programs before comparing,
     L2 compares them. Status flags are never compared: they are not defined at segment entries either, so code
     that reads a flag it did not set cannot be proved. Composing the segments gives the whole function.
  4. Testcases come from unicorn: random registers (also the code's own immediates) and lazily mapped,
     pointer-rich memory; both functions run from the same state, and only states where both reach an exit cleanly,
     with all memory inside [SAFE_LO, SAFE_HI) and in few ranges, are kept (the STOKE sandbox maps testcase memory
     at its own addresses and crashes on the null page or on hundreds of segments).
  5. STOKE runs in Docker (tools/equiv/ddec/Dockerfile); one container per call, segments in parallel inside it.

Hints (the bundle's "hints"): per segment its entry offsets in both functions, the DDEC cutpoints (basic-block ids,
as STOKE numbers them) and the learned invariants exactly as STOKE prints them, grouped by antecedent and with
duplicate equalities (k * an equality already present) removed; the reduced set is rechecked before it is
returned. With hints, STOKE learns nothing (patch 3-ddec-hints.patch, DDEC_HINTS): it checks exactly those
cutpoints and invariants and fails if they do not prove the segment.

Options: eq_only=True (the default) sets DDEC_EQ_ONLY=1, which restricts the learner to the DDEC paper's
invariants (linear equalities and memory equality). Sound either way: every candidate is still SMT-checked; it only
makes learning faster and keeps hints in the form the recheck parser accepts.

Assumptions beyond LAYERS.md: callees do not hand arithmetic flags back to their caller; the relocation pairing in
field order is the bijection (a reordering of relocated instructions gives `unknown`, never a wrong proof).
Unsupported (-> unknown): x87, string instructions, segment overrides, indirect jumps with an index register
(switch tables), instructions x64asm cannot encode in 64-bit mode.

Build the image once:  docker build --platform linux/amd64 -t spore-stoke-ddec:98d8a0f-1 tools/equiv/ddec
Requires: docker, and unicorn in the Python environment (pip install unicorn).
"""
import json
import os
import random
import re
import shutil
import struct
import subprocess
import tempfile
import time
import uuid

import capstone
from capstone import x86_const as X

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
DOCKER_IMAGE = os.environ.get("DDEC_IMAGE", "spore-stoke-ddec:98d8a0f-1")
if shutil.which("docker") is None:
    # optional layer (LAYERS.md): prove.py skips it with this message when Docker is not installed
    raise ImportError("Docker not found; DDEC is optional (build: docker build --platform linux/amd64 -t %s "
                      "tools/equiv/ddec)" % DOCKER_IMAGE)
STOKE_VERSION = "98d8a0f+ddec-hints-1"
BUILD_CMD = "docker build --platform linux/amd64 -t %s tools/equiv/ddec" % DOCKER_IMAGE

STACK = 0x20000800          # esp at a segment's entry in the testcases
HEAP = 0x30000000           # pointer-valued memory points into [HEAP, HEAP + 0x10000)
TOKEN = 0x7EC0DE00          # return token of call site k: TOKEN + k
DATA_SHIFT = 0x40000000     # relocated data addresses are moved by this on both sides
SAFE_LO, SAFE_HI = 0x10000000, 0xF0000000   # testcase memory must lie here (STOKE maps it at these addresses)
GPR32 = ["eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"]

_MDI = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
_MDI.detail = True
_MDA = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
_MDA.syntax = capstone.CS_OPT_SYNTAX_ATT


class Unsupported(Exception):
    pass


# ----------------------------------------------------------------------------------------------------------------
# 1. relocations: one bijection, both functions placed at the retail address

def _rel32_fields(code, base):
    out = set()
    for i in _MDI.disasm(code, base):
        b = i.bytes
        if (b[0] in (0xE8, 0xE9) and i.size == 5) or (b[0] == 0x0F and 0x80 <= b[1] <= 0x8F and i.size == 6):
            out.add(i.address - base + i.size - 4)
    return out


def resolve(retail, ours):
    """-> (retail code, our code with relocated fields rewritten to the retail values they pair with, base)."""
    base = retail.va
    ra, oa = sorted(retail.relocs), sorted(ours.relocs)
    if len(ra) != len(oa):
        raise Unsupported("retail has %d relocated fields, ours %d" % (len(ra), len(oa)))
    rrel = _rel32_fields(retail.code, base)
    orel = _rel32_fields(ours.code, ours.va)
    fwd, back, data = {}, {}, []
    code = bytearray(ours.code)
    rcode = bytearray(retail.code)
    for a, b in zip(ra, oa):
        rt, ot = retail.relocs[a], ours.relocs[b]
        v = rt[1]
        r_is_rel = a in rrel
        if ot[0] == "sym":
            _, name, typ, addend = ot
            o_is_rel = typ == 0x14
            if o_is_rel and addend not in (0, 0xFFFFFFFC):
                raise Unsupported("REL32 relocation with addend %#x" % addend)
            if typ not in (0x06, 0x14):
                raise Unsupported("relocation type %#x" % typ)
            key, sbase = ("sym", name), (v if o_is_rel else (v - addend) & 0xFFFFFFFF)
        else:
            o_is_rel = b in orel
            key, sbase = ("abs", ot[1]), v
            if not o_is_rel:
                data.append((ot[1], v))
        if r_is_rel != o_is_rel:
            raise Unsupported("relocated field %d: a call/jump target on one side, data on the other" % len(fwd))
        if fwd.get(key, sbase) != sbase or back.get(sbase, key) != key:
            raise Unsupported("relocations do not pair one-to-one in field order")
        fwd[key], back[sbase] = sbase, key
        if o_is_rel:
            struct.pack_into("<I", code, b, (v - (base + b + 4)) & 0xFFFFFFFF)
        else:   # data addresses move by DATA_SHIFT on both sides (distances kept), away from STOKE's own memory
            struct.pack_into("<I", code, b, (v + DATA_SHIFT) & 0xFFFFFFFF)
            struct.pack_into("<I", rcode, a, (v + DATA_SHIFT) & 0xFFFFFFFF)
    for i, (o1, r1) in enumerate(data):          # DLL data addresses: nearby fields must keep their distance
        for o2, r2 in data[i + 1:]:
            if (abs(o1 - o2) < 0x10000 or abs(r1 - r2) < 0x10000) and (o1 - o2) != (r1 - r2):
                raise Unsupported("data relocations do not keep their offsets")
    return bytes(rcode), bytes(code), base


# ----------------------------------------------------------------------------------------------------------------
# 2. decoding, control flow, segments

class Fn:
    def __init__(self, code, base, side):
        self.code, self.base, self.side = code, base, side
        self.ins = {}
        for i in _MDI.disasm(code, base):
            self.ins[i.address] = i
        self.end = base + len(code)

    def inside(self, a):
        return self.base <= a < self.end

    def kind(self, i):
        m = i.mnemonic
        if m == "call":
            return "call"
        if m in ("ret", "retn"):
            return "ret"
        if m == "jmp":
            op = i.operands[0]
            if op.type == X.X86_OP_IMM:
                return "jmp" if self.inside(op.imm) else "tail"
            return "tailind"
        if i.group(capstone.CS_GRP_JUMP):
            return "jcc"
        if m in ("int3", "hlt", "ud2", "int"):
            return "trap"
        return "seq"

    def succ(self, a):
        """successors inside the function; calls, rets and tail jumps have none (they are exits)."""
        i = self.ins.get(a)
        if i is None:
            raise Unsupported("%s: no instruction at +%#x" % (self.side, a - self.base))
        k = self.kind(i)
        nxt = a + i.size
        if k in ("call", "ret", "tail", "tailind"):
            return []
        if k == "trap":
            raise Unsupported("%s: reachable %s at +%#x" % (self.side, i.mnemonic, a - self.base))
        if k == "jmp":
            return [i.operands[0].imm]
        out = [nxt]
        if k == "jcc":
            t = i.operands[0].imm
            if not self.inside(t):
                raise Unsupported("%s: conditional jump out of the function" % self.side)
            out.append(t)
        for s in out:
            if not self.inside(s):
                raise Unsupported("%s: falls off the end at +%#x" % (self.side, a - self.base))
        return out

    def reach(self, start):
        seen, todo = set(), [start]
        while todo:
            a = todo.pop()
            if a in seen:
                continue
            seen.add(a)
            todo.extend(self.succ(a))
        return seen

    def segments(self):
        """-> [entry addresses]: the function entry, then the instruction after each call (address order)."""
        allr, todo, calls = set(), [self.base], []
        while todo:
            a = todo.pop()
            if a in allr:
                continue
            r = self.reach(a)
            allr |= r
            for x in r:
                if self.kind(self.ins[x]) == "call":
                    calls.append(x)
                    n = x + self.ins[x].size
                    if n in self.ins and self.kind(self.ins[n]) != "trap" and n not in allr:
                        todo.append(n)
        calls = sorted(set(calls))
        ents = [self.base]
        for c in calls:
            n = c + self.ins[c].size
            ok = n in self.ins and self.inside(n) and self.kind(self.ins[n]) != "trap"
            ents.append(n if ok else None)        # None: the call does not return here (padding follows)
        return ents, calls


# ----------------------------------------------------------------------------------------------------------------
# 3. translation to STOKE's x86-64 AT&T syntax

_UNSUPPORTED_PREFIX = ("f", "rep", "stos", "lods", "scas", "cmps", "ins", "outs", "lock", "std", "cld", "pushf",
                       "popf", "sahf", "lahf", "int", "cpuid", "rdtsc", "wait")
_SHIFTS = ("shl", "shr", "sar", "sal", "rol", "ror", "rcl", "rcr")


def _att(i):
    t = next(_MDA.disasm(i.bytes, i.address))
    return t.mnemonic, t.op_str


def _fix_mem(op_str):
    """AT&T operands from capstone: give absolute memory operands a zero base register (%r11d)."""
    if "%fs:" in op_str or "%gs:" in op_str or "%es:" in op_str or "%ss:" in op_str or "%ds:" in op_str \
            or "%cs:" in op_str:
        raise Unsupported("segment override")
    parts = [p.strip() for p in _split_ops(op_str)]
    out = []
    for p in parts:
        if re.fullmatch(r"-?0x[0-9a-f]+|-?\d+", p):          # a bare number in AT&T is an absolute address
            out.append("%s(%%r11d)" % hex(int(p, 0) & 0xFFFFFFFF))
        elif re.fullmatch(r"-?(0x[0-9a-f]+|\d+)?\(,%e\w\w,\d\)", p):
            out.append(p)                                    # index-only: fine with addr32
        else:
            out.append(p)
    return out


def _split_ops(s):
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur)
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return out


def _hex_imms(m, ops):
    """capstone prints small immediates in decimal ($4, $-1); x64asm wants hex. Negative ones are masked to the
    operand size given by the mnemonic's suffix (the encoding may differ, the value does not)."""
    bits = {"b": 8, "w": 16, "l": 32}.get(m[-1:], 32)
    out = []
    for o in ops:
        mm = re.fullmatch(r"\$(-?)(0x[0-9a-f]+|\d+)", o)
        if mm:
            v = int(mm.group(2), 0)
            v = (-v if mm.group(1) else v) & ((1 << bits) - 1)
            o = "$%s" % hex(v)
        out.append(o)
    return out


def _uses_abs(ops):
    return any("(%r11d)" in o for o in ops)


def _uses_xmm(fn):
    return any("xmm" in i.op_str for i in fn.ins.values())


def translate(fn, entry, sites, level, ret64, xmm, label):
    """One segment: the code reachable from `entry` (calls/rets/tail jumps are exits), as STOKE assembly."""
    reach = sorted(fn.reach(entry))
    targets = set()
    for a in reach:
        i = fn.ins[a]
        if fn.kind(i) in ("jmp", "jcc"):
            targets.add(i.operands[0].imm)
    L = lambda a: ".L%s_%x" % (label, a - fn.base)
    out = [".%s:" % label]
    if reach[0] != entry:
        out.append("  jmpq %s" % L(entry))
    def clobber():
        c = []
        if level == "L1":
            c.append("  movl $0x0, %ecx")
            if not ret64:
                c.append("  movl $0x0, %edx")
            if xmm:
                c += ["  xorps %%xmm%d, %%xmm%d" % (k, k) for k in range(8)]
        return c
    for a in reach:
        i = fn.ins[a]
        if a in targets or (a == entry and reach[0] != entry):
            out.append("%s:" % L(a))
        k = fn.kind(i)
        m, ops_s = _att(i)
        ops = _hex_imms(m, _fix_mem(ops_s)) if ops_s and k not in ("call", "jmp", "jcc", "tail") else []
        T = []
        pre = ["  movl $0x0, %r11d"] if _uses_abs(ops) else []
        if k == "call":
            site = sites.index(a)
            op = i.operands[0]
            if op.type == X.X86_OP_IMM:
                tgt = ["  movl $%s, %%r8d" % hex(op.imm & 0xFFFFFFFF)]
            else:
                iops = _fix_mem(ops_s.lstrip("*"))
                pre = ["  movl $0x0, %r11d"] if _uses_abs(iops) else []
                tgt = ["  movl %s, %%r8d" % iops[0]]
            # the target is read before the return token is pushed (it may use esp)
            T = pre + tgt + ["  leal -0x4(%esp), %esp", "  movl $%s, (%%esp)" % hex(TOKEN + site), "  retq"]
        elif k == "ret":
            n = i.operands[0].imm if i.operands else 0
            T = clobber() + ["  leal %s(%%esp), %%esp" % hex(4 + n), "  movl $0x0, %r8d", "  retq"]
        elif k == "tail":
            T = clobber() + ["  movl $%s, %%r8d" % hex(i.operands[0].imm & 0xFFFFFFFF), "  retq"]
        elif k == "tailind":
            mo = i.operands[0]
            if mo.type == X.X86_OP_MEM and mo.mem.index != 0:
                raise Unsupported("indirect jump through a table (switch)")
            iops = _fix_mem(ops_s.lstrip("*"))
            pre = ["  movl $0x0, %r11d"] if _uses_abs(iops) else []
            T = pre + ["  movl %s, %%r8d" % iops[0]] + clobber() + ["  retq"]
        elif k in ("jmp", "jcc"):
            T = ["  %s %s" % ("jmpq" if k == "jmp" else m, L(i.operands[0].imm))]
        elif m.startswith(_UNSUPPORTED_PREFIX) and not m.startswith(("movsb", "movsw", "movsl", "movss", "movsd",
                                                                     "movsx")):
            raise Unsupported("%s: %s is not supported" % (fn.side, m))
        elif m.startswith("movs") and m in ("movsb", "movsw", "movsl", "movsd") and not ops:
            raise Unsupported("string move")
        elif m in ("pushl", "push", "pushw"):
            if m == "pushw":
                raise Unsupported("16-bit push")
            src = ops[0]
            if src.startswith("$"):
                T = ["  leal -0x4(%esp), %esp", "  movl %s, (%%esp)" % src]
            elif src.startswith("%") and src != "%esp":
                T = ["  leal -0x4(%esp), %esp", "  movl %s, (%%esp)" % src]
            elif src == "%esp":
                T = ["  movl %esp, %r9d", "  leal -0x4(%esp), %esp", "  movl %r9d, (%esp)"]
            else:
                T = pre + ["  movl %s, %%r9d" % src, "  leal -0x4(%esp), %esp", "  movl %r9d, (%esp)"]
        elif m in ("popl", "pop"):
            dst = ops[0]
            if dst == "%esp":
                T = ["  movl (%esp), %esp"]
            elif dst.startswith("%"):
                T = ["  movl (%%esp), %s" % dst, "  leal 0x4(%esp), %esp"]
            else:      # pop to memory: the address uses esp after the increment
                T = ["  movl (%esp), %r9d", "  leal 0x4(%esp), %esp"] + pre + ["  movl %%r9d, %s" % dst]
        elif m in ("leave", "leavel"):
            T = ["  movl %ebp, %esp", "  movl (%esp), %ebp", "  leal 0x4(%esp), %esp"]
        elif m.startswith("nop"):
            T = ["  nop"]
        elif m == "bswapl":
            T = ["  bswap %s" % ops[0]]
        elif m in ("cltd", "cdq"):
            T = ["  cltd"]
        elif m in ("cwtl", "cwde"):
            T = ["  cwtl"]
        elif m.rstrip("bwl") in _SHIFTS and len(ops) == 1:
            T = ["  %s $0x1, %s" % (m, ops[0])]
        elif "%st" in ops_s or m.startswith("f"):
            raise Unsupported("x87")
        else:
            T = pre + ["  %s %s" % (m, ", ".join(ops))] if ops else ["  %s" % m]
        out += T
    return "\n".join(out) + "\n"


# ----------------------------------------------------------------------------------------------------------------
# 4. testcases (unicorn) and concrete refutation

_CONSTS = []     # immediates of the two functions being tested (set by prove): compared-against values


def _consts(*fns):
    out = set()
    for fn in fns:
        for i in fn.ins.values():
            if i.mnemonic in ("cmp", "test", "sub", "and", "mov") and len(i.operands) == 2 \
                    and i.operands[1].type == X.X86_OP_IMM:
                v = i.operands[1].imm & 0xFFFFFFFF
                out.update({v, (v + 1) & 0xFFFFFFFF, (v - 1) & 0xFFFFFFFF})
    return sorted(out)


_SMALL = [0, 1, 2, 3, 4, 7, 8, 15, 16, 0x40, 0x80, 0x100, 0xFFFFFFFF]


def _mix(x):
    """splitmix64 finaliser: a fast deterministic hash."""
    x = (x + 0x9E3779B97F4A7C15) & _M64
    x = ((x ^ (x >> 30)) * 0xBF58476D1CE4E5B9) & _M64
    x = ((x ^ (x >> 27)) * 0x94D049BB133111EB) & _M64
    return x ^ (x >> 31)


def _content(seed, addr):
    """Deterministic initial memory: dword at addr (4-aligned) -> value. A third pointers into HEAP, some code
    constants, some small numbers, the rest random."""
    h = _mix((seed << 32) ^ addr)
    x, v = h & 0xFF, h >> 32
    if x < 90:
        return HEAP + ((v & 0xFFF) << 4)
    if x < 128 and _CONSTS:
        return _CONSTS[v % len(_CONSTS)]
    if x < 180:
        return _SMALL[v % len(_SMALL)] if v & 0x100 else v & 0xFF
    return v & 0xFFFFFFFF


def _regval(r):
    x = r.random()
    if x < 0.4:
        return HEAP + (r.randrange(0x1000) << 4)
    if x < 0.5 and _CONSTS:
        return r.choice(_CONSTS)
    if x < 0.7:
        return r.choice([0, 1, 2, 3, 4, 8, 16, 0x40, 0x100, r.randrange(0x10000)])
    return r.getrandbits(32)


def _run(fn, entry, regs, seed, exits, limit=3000):
    """-> (ok, end_address, final regs, touched chunk set, written {addr: byte})."""
    import unicorn as U
    from unicorn import x86_const as UX
    uc = U.Uc(U.UC_ARCH_X86, U.UC_MODE_32)
    cbase = fn.base & ~0xFFF
    csize = ((fn.end + 0xFFF) & ~0xFFF) - cbase
    uc.mem_map(cbase, csize)
    uc.mem_write(fn.base, fn.code)
    touched, writes, state = set(), {}, {"n": 0, "bad": None, "end": None, "pages": 0}

    def unmapped(uc_, access, addr, size, value, _):
        for pg in {addr & ~0xFFF, (addr + size - 1) & ~0xFFF}:
            if cbase <= pg < cbase + csize:
                state["bad"] = "code page"
                return False
            try:
                uc_.mem_map(pg, 0x1000)
            except U.UcError:
                continue
            state["pages"] += 1
            if state["pages"] > 16:
                state["bad"] = "too much memory"
                return False
            uc_.mem_write(pg, b"".join(struct.pack("<I", _content(seed, pg + 4 * k)) for k in range(1024)))
        return True

    def mem(uc_, access, addr, size, value, _):
        if cbase <= addr < cbase + csize:
            state["bad"] = "code page access"
            uc_.emu_stop()
            return
        for c in range(addr & ~7, addr + size, 8):
            touched.add(c)
        if access == U.UC_MEM_WRITE:
            for k in range(size):
                writes[addr + k] = (value >> (8 * k)) & 0xFF

    def code(uc_, addr, size, _):
        state["end"] = addr
        uc_.emu_stop()

    uc.hook_add(U.UC_HOOK_MEM_UNMAPPED, unmapped)
    uc.hook_add(U.UC_HOOK_MEM_READ | U.UC_HOOK_MEM_WRITE, mem)
    for x in exits:          # every way out of a segment is an exit address (calls, rets, tail jumps)
        uc.hook_add(U.UC_HOOK_CODE, code, begin=x, end=x)
    names = [UX.UC_X86_REG_EAX, UX.UC_X86_REG_ECX, UX.UC_X86_REG_EDX, UX.UC_X86_REG_EBX, UX.UC_X86_REG_ESP,
             UX.UC_X86_REG_EBP, UX.UC_X86_REG_ESI, UX.UC_X86_REG_EDI]
    for n, v in zip(names, regs["gpr"]):
        uc.reg_write(n, v)
    uc.reg_write(UX.UC_X86_REG_EFLAGS, regs["eflags"])
    try:
        uc.emu_start(entry, 0xFFFFFFFF, count=limit)
    except U.UcError as e:
        return False, None, None, touched, writes, str(e)
    if state["bad"] or state["end"] is None:
        return False, None, None, touched, writes, state["bad"] or "instruction limit"
    final = [uc.reg_read(n) for n in names]
    return True, state["end"], final, touched, writes, None


def _exit_sig(fn, end, final, level, ret64, sites):
    """What a caller can observe at this exit, for the concrete refutation check."""
    i = fn.ins.get(end)
    k = fn.kind(i) if i is not None else "outside"
    if k == "call":
        return ("call", sites.index(end), final[4])
    if k == "ret":
        names = ["eax", "ebx", "esp", "ebp", "esi", "edi"] + (["edx"] if ret64 or level == "L2" else []) + \
            (["ecx"] if level == "L2" else [])
        return ("ret", i.operands[0].imm if i.operands else 0,
                tuple((n, final[GPR32.index(n)]) for n in names))
    return (k, end - fn.base if i is not None else None, final[4])


def testcases(rf, of, rent, oent, rexits, oexits, n, seed0, refute, level, ret64, rsites, osites):
    """-> (list of initial states, refutation text or None)."""
    out, refuted = [], None
    tries = 0
    while len(out) < n and tries < n * 6:
        seed = seed0 * 1000003 + tries
        tries += 1
        r = random.Random(seed)
        gpr = [_regval(r) for _ in range(8)]
        gpr[4] = STACK
        eflags = 0x202 | (r.getrandbits(1)) | (r.getrandbits(1) << 2) | (r.getrandbits(1) << 6) | \
            (r.getrandbits(1) << 7) | (r.getrandbits(1) << 11)
        regs = {"gpr": gpr, "eflags": eflags}
        a = _run(rf, rent, regs, seed, rexits)
        b = _run(of, oent, regs, seed, oexits)
        if not (a[0] and b[0]):
            continue
        touched = a[3] | b[3]
        if any(not (SAFE_LO <= c < SAFE_HI) for c in touched):
            continue                  # memory the STOKE sandbox cannot map (null page, STOKE's own image)
        if len(_ranges(touched)) > 24:
            continue
        out.append({"seed": seed, "regs": regs, "touched": touched})
        if refute and refuted is None:
            sa = _exit_sig(rf, a[1], a[2], level, ret64, rsites)
            sb = _exit_sig(of, b[1], b[2], level, ret64, osites)
            esp = min(a[2][4], b[2][4])
            wa = {k: v for k, v in a[4].items() if k >= esp}
            wb = {k: v for k, v in b[4].items() if k >= esp}
            fa = {k: wa.get(k, _byte(seed, k)) for k in set(wa) | set(wb)}
            fb = {k: wb.get(k, _byte(seed, k)) for k in set(wa) | set(wb)}
            if sa[0] != sb[0] or sa[1] != sb[1]:
                refuted = "from the same entry state retail leaves through %s, ours through %s" % (sa[0], sb[0])
            elif sa != sb:
                regs = [x[0] for x, y in zip(sa[2], sb[2]) if x != y] if sa[0] == "ret" else ["esp"]
                refuted = "from the same entry state the two %s exits differ in %s" % (sa[0], ", ".join(regs))
            elif fa != fb:
                diff = sorted(k for k in fa if fa[k] != fb[k])
                refuted = "from the same entry state the memory at %d byte(s) differs at the %s exit" % (
                    len(diff), sa[0])
    return out, refuted


def _byte(seed, a):
    return (_content(seed, a & ~3) >> (8 * (a & 3))) & 0xFF


def _hexq(v):
    return " ".join("%02x" % ((v >> (8 * i)) & 0xFF) for i in range(7, -1, -1))


def _memtext(lo, data):
    hi = lo + len(data)
    s = "[ %08x %08x - %08x %08x ]\n[ %d valid rows shown ]\n" % (hi >> 32, hi & 0xFFFFFFFF, lo >> 32,
                                                                  lo & 0xFFFFFFFF, len(data) // 8)
    rows = []
    for r in range(len(data) // 8 - 1, -1, -1):
        a = lo + 8 * r
        rows.append("%08x %08x   %s  %s " % (a >> 32, a & 0xFFFFFFFF, "v " * 8,
                                             " ".join("%02x" % data[8 * r + j] for j in range(7, -1, -1))))
    return s + "\n" + "\n".join(rows)


_FLAGS = ["%cf", "%1", "%pf", "%0", "%af", "%0", "%zf", "%sf", "%tf", "%if", "%df", "%of", "%iopl[0]", "%iopl[1]",
          "%nt", "%0", "%rf", "%vm", "%ac", "%vif", "%vip", "%id"]
_GPS = ["%rax", "%rcx", "%rdx", "%rbx", "%rsp", "%rbp", "%rsi", "%rdi", "%r8", "%r9", "%r10", "%r11", "%r12",
        "%r13", "%r14", "%r15"]


def _ranges(chunks, gap=0x100):
    """8-byte chunks -> merged [lo, hi) ranges (gaps up to `gap` bytes are filled in)."""
    out = []
    for c in sorted(chunks):
        if out and c <= out[-1][1] + gap:
            out[-1][1] = max(out[-1][1], c + 8)
        else:
            out.append([c, c + 8])
    return out


def stoke_testcase(tc, xmm):
    seed = tc["seed"]
    r = random.Random(seed ^ 0xABCDEF)
    g = list(tc["regs"]["gpr"]) + [r.getrandbits(32)] + [0] * 7
    s = "SIGNAL 0 [normal exit]\n\n" + "\n".join("%-8s %s" % (n, _hexq(v)) for n, v in zip(_GPS, g)) + "\n\n"
    ymm = []
    for k in range(16):
        v = [r.getrandbits(8) if (xmm and k < 8 and j >= 16) else 0 for j in range(32)]
        ymm.append("%-8s %s" % ("%%ymm%d" % k, " ".join("%02x" % b for b in v)))
    s += "\n".join(ymm) + "\n\n"
    ef = tc["regs"]["eflags"]
    bit = {"%cf": 0, "%pf": 2, "%af": 4, "%zf": 6, "%sf": 7, "%if": 9, "%df": 10, "%of": 11}
    s += "\n".join("%-8s %d " % (f, (1 if f == "%1" else ((ef >> bit[f]) & 1) if f in bit else 0))
                   for f in _FLAGS) + "\n\n"
    ranges = _ranges(set(tc["touched"]) | set(range(STACK - 0x200, STACK + 0x200, 8)))
    mems = []
    for lo, hi in ranges:
        mems.append((lo, bytes(_byte(seed, a) for a in range(lo, hi))))
    stack = [m for m in mems if m[0] <= STACK < m[0] + len(m[1])]
    rest = [m for m in mems if m not in stack]
    heap = rest[0] if rest else (0, b"")
    data = rest[1] if len(rest) > 1 else (0, b"")
    more = rest[2:]
    s += _memtext(*stack[0]) + "\n\n" + _memtext(*heap) + "\n\n" + _memtext(*data) + "\n\n"
    s += "%d more segment(s)\n" % len(more)
    for m in more:
        s += "\n" + _memtext(*m) + "\n"
    return s


def _blank_testcase():
    tc = {"seed": 1, "regs": {"gpr": [0, 0, 0, 0, STACK, 0, 0, 0], "eflags": 0x202}, "touched": set()}
    return stoke_testcase(tc, False)


# ----------------------------------------------------------------------------------------------------------------
# 5. running STOKE

def _image_ok():
    try:
        p = subprocess.run(["docker", "image", "inspect", DOCKER_IMAGE], capture_output=True, timeout=60)
        return p.returncode == 0
    except (OSError, subprocess.TimeoutExpired):
        return False


def _run_stoke(job, segs, timeout, eq_only, xmm):
    """segs: list of (name, hints_file_or_None). Runs all in one container, in parallel. -> {name: (rc, log)}"""
    di = "{ %rax %rcx %rdx %rbx %rsp %rbp %rsi %rdi %r8" + (" %xmm0 %xmm1 %xmm2 %xmm3 %xmm4 %xmm5 %xmm6 %xmm7"
                                                                if xmm else "") + " }"
    lo = "{ %eax %ecx %edx %ebx %esp %ebp %esi %edi %r8d" + (" %xmm0 %xmm1 %xmm2 %xmm3 %xmm4 %xmm5 %xmm6 %xmm7"
                                                                 if xmm else "") + " }"
    lines = ["#!/bin/bash", "cd /job"]
    per = max(5, int(timeout))
    for name, hint in segs:
        env = ("DDEC_EQ_ONLY=1 " if eq_only else "") + ("DDEC_HINTS=/job/%s " % hint if hint else "")
        ntc = sum(1 for ln in open(os.path.join(job, name + ".tc")) if ln.startswith("Testcase "))
        lines.append(
            "( %s timeout -s KILL %d stoke_debug_verify --target %s_t.s --rewrite %s_r.s --strategy ddec "
            "--testcases %s.tc --training_set '{ 0 ... %d }' --def_in '%s' --live_out '%s' --heap_out --stack_out "
            "--alias_strategy flat --max_jumps 4096 > %s.log 2>&1; echo $? > %s.rc ) &"
            % (env, per, name, name, name, max(0, ntc - 1), di, lo, name, name))
    lines.append("wait")
    open(os.path.join(job, "run.sh"), "w").write("\n".join(lines) + "\n")
    cname = "ddec_" + uuid.uuid4().hex[:12]
    cmd = ["docker", "run", "--rm", "--name", cname, "--platform", "linux/amd64", "-v", "%s:/job" % job,
           DOCKER_IMAGE, "bash", "/job/run.sh"]
    try:
        subprocess.run(cmd, capture_output=True, timeout=timeout + 60)
    except subprocess.TimeoutExpired:
        subprocess.run(["docker", "kill", cname], capture_output=True)
    finally:
        subprocess.run(["docker", "rm", "-f", cname], capture_output=True)
    res = {}
    for name, _ in segs:
        try:
            rc = int(open(os.path.join(job, name + ".rc")).read().strip() or -1)
        except (OSError, ValueError):
            rc = -1
        try:
            log = open(os.path.join(job, name + ".log"), errors="replace").read()
        except OSError:
            log = ""
        res[name] = (rc, log)
    return res


def _verdict(rc, log):
    if "Equivalent: yes" in log and rc == 0:
        return True, ""
    if rc in (137, 124):
        return False, "timeout"
    for pat in ("DDEC_HINTS: [^\n]*do not check", "DDEC_HINTS: [^\n]*error[^\n]*", "Error[^\n]*\n[^\n]*\n[^\n]*",
                "Could not find any viable cutpoints", "Unsupported instruction[^\n]*", "Could not remove failed"):
        m = re.search(pat, log)
        if m:
            return False, " ".join(m.group(0).split())[:160]
    if "Equivalent: no" in log:
        return False, "not proven"
    return False, "verifier rc=%s" % rc


def _summary(log):
    """The cutpoints and invariants of the last SUMMARY (the proof), intermediate cutpoints only."""
    i = log.rfind("****   SUMMARY   ****")
    if i < 0:
        return None
    blk = log[i:].split("\nEquivalent")[0].split("\n")
    cuts = []
    for ln in blk:
        m = re.match(r"Cutpoint \d+ at blocks ([0-9a-f]+) / ([0-9a-f]+)$", ln)
        if m:
            cuts.append({"at": [int(m.group(1), 16), int(m.group(2), 16)], "lines": []})
        elif ln.startswith("    ") and cuts:
            cuts[-1]["lines"].append(ln.strip())
    return cuts[1:-1]


# ----------------------------------------------------------------------------------------------------------------
# 6. hints: compact form of the printed invariants

_M64 = (1 << 64) - 1


def _parse_eq(s):
    m = re.fullmatch(r"(.+) = 0x([0-9a-f]+)", s)
    if not m:
        return None
    terms = {}
    for t in m.group(1).split(" + "):
        mm = re.fullmatch(r"(-)?(?:([0-9a-f]+)\*)?(%\w+'?)", t)
        if not mm:
            return None
        c = int(mm.group(2), 16) if mm.group(2) else 1
        terms[mm.group(3)] = (-c if mm.group(1) else c) & _M64
    return terms, int(m.group(2), 16)


def _implied(e, by, only_k=None):
    """e = k * by (mod 2^64) for some k (or for k = only_k)."""
    (te, ce), (tb, cb) = e, by
    if set(te) != set(tb):
        return False
    piv = next((v for v in tb if tb[v] & 1), None)
    if piv is None:
        return False
    k = te[piv] * pow(tb[piv], -1, 1 << 64) & _M64
    if only_k is not None and k not in (1, only_k):
        return False
    return all(te[v] == (k * tb[v]) & _M64 for v in tb) and ce == (k * cb) & _M64


def compact(lines, reduce=1):
    """printed invariant lines -> {antecedent: [consequents]} ('' for lines that are not implications).
    reduce=0 keeps every line; 1 drops exact duplicates, negated duplicates (-1 * an equality already kept) and
    everything else under an antecedent that implies false; 2 also drops every k * (a kept equality). Fewer
    hypotheses can make Z3 slower, so the caller rechecks a reduced set before trusting it."""
    groups = {}
    for ln in lines:
        if ln.startswith("( ") and ln.endswith(" )") and " => " in ln:
            a, c = ln[2:-2].split(" => ", 1)
        else:
            a, c = "", ln
        groups.setdefault(a, [])
        if c not in groups[a]:
            groups[a].append(c)
    if reduce:
        for a, cs in groups.items():
            if "false" in cs:            # the antecedent is impossible; the rest follows from it
                groups[a] = ["false"]
                continue
            kept, eqs = [], []
            order = sorted(cs, key=lambda c: (0 if _parse_eq(c) is None else 1, len(c)))
            for c in order:
                e = _parse_eq(c)
                if e is not None and any(_implied(e, b, None if reduce >= 2 else _M64) for b in eqs):
                    continue
                if e is not None:
                    eqs.append(e)
                kept.append(c)
            groups[a] = [c for c in cs if c in kept]
    return groups


def expand(groups):
    out = []
    for a, cs in groups.items():
        for c in cs:
            out.append("( %s => %s )" % (a, c) if a else c)
    return out


def _hint_text(cuts):
    s = []
    for n, c in enumerate(cuts):
        s.append("Cutpoint %d at blocks %x / %x" % (n + 1, c["at"][0], c["at"][1]))
        s += ["    " + ln for ln in expand(c["inv"])]
    return "\n".join(s) + "\n"


# ----------------------------------------------------------------------------------------------------------------
# 7. the layer

def _result(status, t0, detail, hints=None):
    return {"status": status, "seconds": round(time.time() - t0, 1), "detail": detail, "hints": hints or {}}


def prove(retail, ours, level, hints=None, timeout=600.0, eq_only=True, ntc=64, keep=False):
    t0 = time.time()
    if level not in ("L1", "L2"):
        raise ValueError(level)
    ret64 = bool(ours.meta.get("ret64") or retail.meta.get("ret64"))
    try:
        rcode, ocode, base = resolve(retail, ours)
        rf, of = Fn(rcode, base, "retail"), Fn(ocode, base, "ours")
        rents, rsites = rf.segments()
        oents, osites = of.segments()
        if len(rsites) != len(osites):
            raise Unsupported("retail makes %d calls, ours %d" % (len(rsites), len(osites)))
        xmm = _uses_xmm(rf) or _uses_xmm(of)
        segs = []
        for k, (re_, oe) in enumerate(zip(rents, oents)):
            if (re_ is None) != (oe is None):
                raise Unsupported("call %d returns on one side only" % k)
            if re_ is None:
                continue
            segs.append((k, re_, oe, translate(rf, re_, rsites, level, ret64, xmm, "t%d" % k),
                         translate(of, oe, osites, level, ret64, xmm, "r%d" % k)))
        for t in (rcode, ocode):
            for k in range(len(rsites)):
                if struct.pack("<I", TOKEN + k) in t:
                    raise Unsupported("return token constant appears in the code")
    except Unsupported as e:
        return _result("unknown", t0, "ddec: unsupported: %s" % e)
    except capstone.CsError as e:
        return _result("unknown", t0, "ddec: decode error %s" % e)
    if not _image_ok():
        return _result("unknown", t0, "ddec: docker image %s missing; build it: %s" % (DOCKER_IMAGE, BUILD_CMD))

    at = [[re_ - base, oe - base] for _, re_, oe, _, _ in segs]
    if hints is not None:
        hs = hints.get("segs") if isinstance(hints, dict) else None
        if not isinstance(hs, list) or len(hs) != len(segs) or [h.get("at") for h in hs] != at \
                or hints.get("level") != level:
            return _result("unknown", t0, "ddec: hints do not fit this function (segments or level differ)")

    work = os.path.join(ROOT, "work", "equiv_tmp")
    os.makedirs(work, exist_ok=True)
    job = tempfile.mkdtemp(prefix="ddec_%08x_" % retail.va, dir=work)
    os.chmod(job, 0o777)
    try:
        refuted = None
        names = []
        _CONSTS[:] = _consts(rf, of)
        for idx, (k, re_, oe, ts, rs) in enumerate(segs):
            name = "seg%d" % k
            names.append(name)
            open(os.path.join(job, name + "_t.s"), "w").write(ts)
            open(os.path.join(job, name + "_r.s"), "w").write(rs)
            if hints is not None:
                open(os.path.join(job, name + ".tc"), "w").write("Testcase 0:\n\n" + _blank_testcase())
                open(os.path.join(job, name + ".hints"), "w").write(_hint_text(hints["segs"][idx]["cuts"]))
                continue
            rex = set(rsites) | {a for a, i in rf.ins.items() if rf.kind(i) in ("ret", "tail", "tailind")}
            oex = set(osites) | {a for a, i in of.ins.items() if of.kind(i) in ("ret", "tail", "tailind")}
            tcs, ref = testcases(rf, of, re_, oe, rex, oex, ntc, 7919 * (k + 1), k == 0, level, ret64,
                                 rsites, osites)
            if ref and refuted is None:
                refuted = "segment %d: %s" % (k, ref)
            if not tcs:
                tcs = []
            body = [stoke_testcase(tc, xmm) for tc in tcs] or [_blank_testcase()]
            open(os.path.join(job, name + ".tc"), "w").write(
                "\n\n".join("Testcase %d:\n\n%s" % (n, b) for n, b in enumerate(body)))
        _CONSTS[:] = []
        if refuted:
            return _result("refuted", t0, "ddec (concrete run): " + refuted)
        left = timeout - (time.time() - t0)
        if left <= 5:
            return _result("unknown", t0, "ddec: timeout before running STOKE")
        res = _run_stoke(job, [(n, (n + ".hints") if hints is not None else None) for n in names], left,
                         eq_only, xmm)
        fails = []
        out_segs = []
        for name, (k, re_, oe, _, _) in zip(names, segs):
            ok, why = _verdict(*res[name])
            if not ok:
                fails.append("%s: %s" % (name, why))
                continue
            cuts = _summary(res[name][1])
            out_segs.append({"at": [re_ - base, oe - base], "cuts": cuts or []})
        if fails:
            what = "hinted recheck failed" if hints is not None else "not proved"
            return _result("unknown", t0, "ddec: %s; %s" % (what, "; ".join(fails)))
        ncut = sum(len(s["cuts"]) for s in out_segs)
        if hints is not None:
            return _result("proved", t0, "ddec: %d segment(s) rechecked from hints (%d loop cutpoint(s)), %s" % (
                len(segs), ncut, level), hints)
        detail = "ddec: %d segment(s) proved, %d loop cutpoint(s), %s, %.1f s" % (len(segs), ncut, level,
                                                                                 time.time() - t0)
        learn_s = time.time() - t0

        def hints_at(red):
            segs_h = []
            for sh, name in zip(out_segs, names):
                cuts = _summary(res[name][1]) or []
                segs_h.append({"at": sh["at"], "cuts": [{"at": c["at"], "inv": compact(c["lines"], red)}
                                                        for c in cuts]})
            return {"v": 1, "level": level, "eq_only": eq_only, "segs": segs_h}

        budget = 2048 + len(retail.code) - 400        # the bundle's other fields take about 400 bytes
        newh = hints_at(1)
        if ncut:
            # a reduced invariant set is only returned after it rechecked; a recheck gets a bounded time
            tries = [1, 2] if len(json.dumps(newh)) > budget else [1]
            for red in tries:
                cand = hints_at(red)
                left = timeout - (time.time() - t0)
                cap = min(left, max(60.0, 3 * learn_s))
                chk = prove(retail, ours, level, cand, timeout=cap) if cap > 10 else None
                if chk is not None and chk["status"] == "proved":
                    newh = cand
                    detail += "; hints (%d bytes) recheck in %.1f s" % (len(json.dumps(cand)), chk["seconds"])
                    break
                detail += "; reduction %d did not recheck (%s)" % (red, chk["detail"][:80] if chk else "no time")
            else:
                newh = hints_at(0)
                detail += "; full invariants kept as hints, unchecked (%d bytes)" % len(json.dumps(newh))
        return _result("proved", t0, detail, newh)
    finally:
        if keep:
            print("ddec: job kept in", job)
        else:
            shutil.rmtree(job, ignore_errors=True)
