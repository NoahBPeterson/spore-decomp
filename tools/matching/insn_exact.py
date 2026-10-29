#!/usr/bin/env python3
"""insn_exact.py: is our compiled function INSTRUCTION-EXACT with the original?

usage: insn_exact.py <src.cpp> <va-hex>[,<va-hex>...] [more vas...] [--flags "..."] [--json out.json]
                     [--cases [--names opcodes.json] [--show N]] [--trace]
  --cases compares a switch function case by case (jump-table ranges paired by the table indices they serve);
  registers/slots read before they are written in a case must rename consistently across all cases.

Instruction-exact means the same instruction sequence up to a consistent renaming of registers and stack slots:
  - same number of instructions, same mnemonics, same operand kinds; encodings may differ (disp8/disp32, the short
    `mov eax, [mem]` form);
  - registers: dataflow-consistent renaming. The map starts as the identity at entry (arguments arrive in the same
    registers), every write rebinds the written pair, every read must agree with the current binding. Registers that
    carry a value into a call (written since the last call and not yet read) and eax/edx at a return must map to
    themselves, so a calling-convention difference is a mismatch, not a rename;
  - stack slots: offsets are taken relative to the entry esp. Incoming arguments must match exactly; locals are
    renamed like registers. The frame-size immediates of the prologue/epilogue may differ;
  - relocated operands (calls, globals, literals) are resolved to original addresses with the equivalence harness's
    resolver (tools/difftest/resolve.py) and must equal the original's operand; an operand it cannot resolve is
    counted as unverified (reported, not a mismatch);
  - branches must target the corresponding instruction.
Known approximations: the register/slot map flows along the linear instruction order (a block entered by a jump
inherits the fall-through state); partial-register writes rebind the whole register.

Exit 0 iff every target is INSN-EXACT. Byte-exactness (chk.py, run_all.py) is a stricter, separate check.
"""
import argparse, json, os, re, struct, sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(ROOT, "tools", "difftest"))
import capstone                                     # noqa: E402
from capstone import x86_const as X                 # noqa: E402
import slice as S                                   # noqa: E402
import resolve as R                                 # noqa: E402
from coff import Coff                               # noqa: E402

REL_DIR32, REL_REL32 = 0x06, 0x14
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True

FAM = {}
for fam, parts in (("eax", ("eax", "ax", "al", "ah")), ("ecx", ("ecx", "cx", "cl", "ch")),
                   ("edx", ("edx", "dx", "dl", "dh")), ("ebx", ("ebx", "bx", "bl", "bh")),
                   ("esi", ("esi", "si")), ("edi", ("edi", "di")), ("ebp", ("ebp", "bp")), ("esp", ("esp", "sp"))):
    for k, p in enumerate(parts):
        FAM[p] = (fam, ("32", "16", "lo8", "hi8")[k])
GPR = ("eax", "ecx", "edx", "ebx", "esi", "edi", "ebp")
CALLER_SAVED = ("eax", "ecx", "edx")
CALLEE_SAVED = ("ebx", "esi", "edi", "ebp")


class Mismatch(Exception):
    pass


# ---- disassembly of the two sides ------------------------------------------------------------------------------
def code_end(insns, lo, hi):
    """Jump tables live after the code (MSVC): stop at the lowest table address an indirect jmp/movzx names."""
    end = hi
    for i in insns:
        if i.mnemonic in ("jmp", "movzx", "mov") and len(i.operands) and any(
                o.type == X.X86_OP_MEM and o.mem.index and o.mem.base == 0 for o in i.operands):
            for o in i.operands:
                if o.type == X.X86_OP_MEM and lo < o.mem.disp < end:
                    end = o.mem.disp
    return end


def disasm(code, base, hi=None):
    out = []
    for i in md.disasm(code, base):
        if hi is not None and i.address >= hi:
            break
        out.append(i)
    return out


class Side:
    """One side's instruction list plus how to read its relocated operands and callee stack pops."""

    def __init__(self, name, insns, base):
        self.name, self.insns, self.base = name, insns, base
        self.index = {i.address: k for k, i in enumerate(insns)}


# ---- comparison ----------------------------------------------------------------------------------------------
class Checker:
    def __init__(self, orig, ours, img, reloc_target, callee_pop_orig, callee_pop_ours, frames, live=None,
                 target_key=None, depth=(0, 0), global_slots=(set(), set()), pro_slots=(set(), set())):
        self.o, self.u, self.img = orig, ours, img
        self.live = live                        # case mode: function-wide renaming shared by all cases (Live)
        self.target_key = target_key            # case mode: (side, address) -> comparable branch-target key
        self.gs_o, self.gs_u = global_slots     # slots some code reads before writing (values crossing a case edge)
        self.ps_o, self.ps_u = pro_slots        # slots the prologue writes (params, types, i, result...)
        self.snap = {}                          # case mode: instruction index -> register map at a branch target
        self.exits = []                         # case mode: (target key, register map) of jumps leaving the range
        self.reloc_target = reloc_target        # ours: (insn, operand-offset) -> resolved original VA | "?" | None
        self.pop_o, self.pop_u = callee_pop_orig, callee_pop_ours
        self.frame_o, self.frame_u = frames
        self.fwd, self.inv = ({f: f for f in GPR}, {f: f for f in GPR}) if live is None else ({}, {})
        self.sfwd, self.sinv = {}, {}           # slot (offset from entry esp) maps, locals only
        self.pending = {}                       # orig family -> ours family written since last call, not yet read
        self.depth_o, self.depth_u = depth      # bytes pushed below the entry esp (positive)
        self.unverified = 0
        self.unverified_syms = set()
        self.last_eax_imm = {}
        self.clob_o, self.clob_u = set(), set()     # callee-saved registers written and not restored

    # registers
    def reg(self, r_o, r_u, write, where):
        fo, po = FAM.get(r_o, (r_o, None))
        fu, pu = FAM.get(r_u, (r_u, None))
        if fo not in GPR and fo != "esp" or fu not in GPR and fu != "esp":
            if r_o != r_u:
                raise Mismatch("%s: register %s vs %s" % (where, r_o, r_u))
            return
        if po != pu:
            raise Mismatch("%s: register part %s vs %s" % (where, r_o, r_u))
        if fo == "esp" or fu == "esp":
            if fo != fu:
                raise Mismatch("%s: esp vs %s" % (where, r_o if fu == "esp" else r_u))
            return
        if write:
            old = self.fwd.get(fo)
            if old is not None:
                self.inv.pop(old, None)
            oldo = self.inv.get(fu)
            if oldo is not None:
                self.fwd.pop(oldo, None)
            self.fwd[fo], self.inv[fu] = fu, fo
            self.pending[fo] = fu
        else:
            if fo not in self.fwd and self.inv.get(fu) is None and self.live is not None:
                self.live.bind("reg", fo, fu, where)
                self.fwd[fo], self.inv[fu] = fu, fo
            if self.fwd.get(fo) != fu:
                raise Mismatch("%s: reads %s / %s but %s is bound to %s" % (where, r_o, r_u, r_o, self.fwd.get(fo)))
            self.pending.pop(fo, None)

    # stack slots (offset from the entry esp; negative = locals)
    def slot(self, k_o, k_u, write, where):
        if k_o >= 0 or k_u >= 0:
            # an incoming argument (or the return address): the same on both sides, relative to the frame top
            ao = k_o if k_o >= 0 else None
            au = k_u if k_u >= 0 else None
            if ao != au:
                raise Mismatch("%s: argument slot %+d vs %+d" % (where, k_o, k_u))
            return
        if self.live is not None:
            if write:                                   # a new value: case-local renaming (slot reuse)
                self._rebind_slot(k_o, k_u)
            elif k_o in self.sfwd or k_u in self.sinv:
                if self.sfwd.get(k_o) != k_u:
                    raise Mismatch("%s: slot %+d is bound to %s here, ours uses %+d" % (where, k_o,
                                   fmt(self.sfwd.get(k_o)), k_u))
            else:                                       # a value from outside this case
                if k_o in self.gs_o or k_u in self.gs_u:    # function-wide: prologue-built or read by the exit
                    self.live.bind("slot", k_o, k_u, where)
                self.sfwd[k_o], self.sinv[k_u] = k_u, k_o   # else carried along a jump into a shared tail
            return
        if write or k_o not in self.sfwd:
            if not write and self.sinv.get(k_u, k_o) != k_o:
                raise Mismatch("%s: slot %+d / %+d but %+d is bound to %+d" % (where, k_o, k_u, k_u, self.sinv[k_u]))
            old = self.sfwd.get(k_o)
            if old is not None:
                self.sinv.pop(old, None)
            oldo = self.sinv.get(k_u)
            if oldo is not None:
                self.sfwd.pop(oldo, None)
            self.sfwd[k_o], self.sinv[k_u] = k_u, k_o
        elif self.sfwd[k_o] != k_u:
            raise Mismatch("%s: slot %+d is bound to %+d, ours uses %+d" % (where, k_o, self.sfwd[k_o], k_u))

    def state(self):
        return (self.depth_o, self.depth_u, dict(self.fwd), dict(self.inv), dict(self.sfwd), dict(self.sinv),
                set(self.clob_o), set(self.clob_u))

    def restore(self, st):
        (self.depth_o, self.depth_u, fwd, inv, sfwd, sinv, co, cu) = st
        self.fwd, self.inv, self.sfwd, self.sinv = dict(fwd), dict(inv), dict(sfwd), dict(sinv)
        self.clob_o, self.clob_u = set(co), set(cu)
        self.pending = {}

    def _rebind_slot(self, k_o, k_u):
        old = self.sfwd.get(k_o)
        if old is not None:
            self.sinv.pop(old, None)
        oldo = self.sinv.get(k_u)
        if oldo is not None:
            self.sfwd.pop(oldo, None)
        self.sfwd[k_o], self.sinv[k_u] = k_u, k_o

    def publish(self, where):
        """Leaving the case: values it left in slots that other code reads must be where that code expects them."""
        for k_o, k_u in self.sfwd.items():
            if k_o in self.gs_o or k_u in self.gs_u:
                self.live.bind("slot", k_o, k_u, where + " (leaving the case)")

    def mem(self, io, iu, mo, mu, access, where):
        if mo.segment != mu.segment or mo.scale != mu.scale:
            raise Mismatch("%s: memory operand form" % where)
        bo, bu = io.reg_name(mo.base) if mo.base else None, iu.reg_name(mu.base) if mu.base else None
        xo, xu = io.reg_name(mo.index) if mo.index else None, iu.reg_name(mu.index) if mu.index else None
        if (bo is None) != (bu is None) or (xo is None) != (xu is None):
            raise Mismatch("%s: memory operand registers" % where)
        if xo:
            self.reg(xo, xu, False, where)
        if bo == "esp" or bu == "esp":
            if bo != bu:
                raise Mismatch("%s: esp-relative vs %s-relative" % (where, bu if bo == "esp" else bo))
            k_o, k_u = mo.disp - self.depth_o, mu.disp - self.depth_u
            if xo:      # an indexed local array: the base slot is what is renamed
                self.slot(k_o, k_u, False, where)
            elif access == "lea":
                # address taken: an out-argument (a new local) unless it is a prologue-built object
                self.slot(k_o, k_u, self.live is not None and k_o not in self.ps_o and k_u not in self.ps_u
                          and k_o not in self.sfwd, where)
            else:
                self.slot(k_o, k_u, bool(access & capstone.CS_AC_WRITE) and not access & capstone.CS_AC_READ, where)
            return
        if bo:
            self.reg(bo, bu, False, where)
        self.value(io, iu, mo.disp, mu.disp, iu.disp_offset if hasattr(iu, "disp_offset") else None, where,
                   o_reloc=self.img.reloc_positions(io.address + io.disp_offset, 1) if io.disp_offset else [])

    def value(self, io, iu, vo, vu, uoff, where, o_reloc):
        """An immediate or displacement: relocated on our side -> compare the resolved address."""
        tgt = self.reloc_target(iu, uoff) if uoff else None
        if tgt is None:
            if o_reloc:
                raise Mismatch("%s: original operand %#x is an address, ours is the constant %#x" % (where, vo, vu))
            if (vo & 0xFFFFFFFF) != (vu & 0xFFFFFFFF):
                raise Mismatch("%s: constant %#x vs %#x" % (where, vo & 0xFFFFFFFF, vu & 0xFFFFFFFF))
            return
        if tgt == "?":
            self.unverified += 1
            return
        if isinstance(tgt, tuple):              # ("const", bytes): the original's operand must hold that value
            if self.img.read(vo & 0xFFFFFFFF, len(tgt[1])) != tgt[1]:
                raise Mismatch("%s: constant at %#x is not %s" % (where, vo & 0xFFFFFFFF, tgt[1][::-1].hex()))
            return
        if (tgt & 0xFFFFFFFF) != (vo & 0xFFFFFFFF):
            raise Mismatch("%s: address %#x vs ours resolved to %#x" % (where, vo & 0xFFFFFFFF, tgt & 0xFFFFFFFF))

    def esp_effect(self, i, side):
        """Bytes this instruction pushes (positive) below the entry esp."""
        m, ops = i.mnemonic, i.operands
        if m == "push":
            return 4
        if m == "pop":
            return -4
        if m in ("sub", "add") and len(ops) == 2 and ops[0].type == X.X86_OP_REG and i.reg_name(ops[0].reg) == "esp" \
                and ops[1].type == X.X86_OP_IMM:
            return ops[1].imm if m == "sub" else -ops[1].imm
        return 0

    def run(self):
        O, U = self.o.insns, self.u.insns
        if len(O) != len(U):
            n = min(len(O), len(U))
        else:
            n = len(O)
        self.at = {}                            # instruction index -> state recorded by a branch to it
        for k in range(n):
            io, iu = O[k], U[k]
            if k and (O[k - 1].mnemonic in ("jmp", "ret") or O[k - 1].mnemonic.startswith("ret")) and k in self.at:
                self.restore(self.at[k])
            where = "#%d %x/%x %s %s | %s %s" % (k, io.address, iu.address - self.u.base, io.mnemonic, io.op_str,
                                                iu.mnemonic, iu.op_str)
            if self.target_key is not None:
                self.snap[k] = dict(self.fwd)
            if os.environ.get("INSN_EXACT_TRACE") or "--trace" in sys.argv:
                print("   %4d d=%5d/%5d  %-40s | %s" % (k, self.depth_o, self.depth_u, io.mnemonic + " " + io.op_str,
                                                     iu.mnemonic + " " + iu.op_str))
            self.step(k, io, iu, where)
        if len(O) != len(U):
            raise Mismatch("instruction count %d vs %d (first %d compared equal)" % (len(O), len(U), n))

    def step(self, k, io, iu, where):
        if io.mnemonic != iu.mnemonic:
            raise Mismatch("%s: mnemonic" % where)
        m = io.mnemonic
        oo, uu = io.operands, iu.operands
        if len(oo) != len(uu) or any(a.type != b.type or a.size != b.size for a, b in zip(oo, uu)):
            raise Mismatch("%s: operand kinds" % where)
        # frame allocation: `mov eax, N; call __chkstk` or `sub esp, N` at entry, `add esp, N` on the way out
        frame_imm = m in ("sub", "add") and len(oo) == 2 and oo[0].type == X.X86_OP_REG and \
            io.reg_name(oo[0].reg) == "esp" and oo[1].type == X.X86_OP_IMM and \
            oo[1].imm == self.frame_o and uu[1].imm == self.frame_u
        chk_imm = k == 0 and m == "mov" and oo[0].type == X.X86_OP_REG and io.reg_name(oo[0].reg) == "eax" and \
            oo[1].type == X.X86_OP_IMM and oo[1].imm == self.frame_o and uu[1].imm == self.frame_u
        # branches: the targets must be corresponding instructions (or the same resolved function)
        if m.startswith("j") or m in ("call", "loop"):
            if oo and oo[0].type == X.X86_OP_IMM:
                to = oo[0].imm
                uoff = iu.imm_offset if hasattr(iu, "imm_offset") and iu.imm_offset else iu.size - 4
                tgt = self.reloc_target(iu, uoff)
                if tgt is None:                              # an internal jump in ours
                    if self.target_key:
                        ko, ku = self.target_key("o", to), self.target_key("u", uu[0].imm)
                        if ko != ku:
                            raise Mismatch("%s: branch target %s vs %s" % (where, ko, ku))
                        if ko[0] == "here":
                            self.at.setdefault(ko[1], self.state())
                        if ko[0] != "here":
                            self.exits.append((ko, dict(self.fwd)))
                            if m == "jmp" or True:
                                self.publish(where)
                    else:
                        ko, ku = self.o.index.get(to), self.u.index.get(uu[0].imm)
                        if ko is None or ko != ku:
                            raise Mismatch("%s: branch target #%s vs #%s" % (where, ko, ku))
                        self.at.setdefault(ko, self.state())
                elif tgt == "?":
                    self.unverified += 1
                elif tgt != to:
                    raise Mismatch("%s: call target %#x vs ours resolved to %#x" % (where, to, tgt))
                if m == "call":
                    self.call(io, iu, to, tgt if isinstance(tgt, int) else None, where)
                return
        # saving / restoring a callee-saved register: which one each side uses is a register choice
        if m in ("push", "pop") and len(oo) == 1 and oo[0].type == X.X86_OP_REG:
            ro, ru = io.reg_name(oo[0].reg), iu.reg_name(uu[0].reg)
            if ro in CALLEE_SAVED and ru in CALLEE_SAVED:
                if m == "push" and ro not in self.clob_o and ru not in self.clob_u:
                    self.depth_o += 4; self.depth_u += 4
                    return
                if m == "pop":
                    self.clob_o.discard(ro); self.clob_u.discard(ru)
                    self.reg(ro, ru, True, where); self.pending.pop(ro, None)
                    self.depth_o -= 4; self.depth_u -= 4
                    return
        # zeroing idioms (xor r, r / sub r, r) only write their register
        if m in ("xor", "sub") and len(oo) == 2 and all(o.type == X.X86_OP_REG for o in oo) and oo[0].reg == oo[1].reg:
            if uu[0].reg != uu[1].reg:
                raise Mismatch("%s: zeroing idiom vs a two-register operation" % where)
            self.reg(io.reg_name(oo[0].reg), iu.reg_name(uu[0].reg), True, where)
            return
        # operands; reads before writes
        writes = []
        for a, b in zip(oo, uu):
            if a.type == X.X86_OP_REG:
                ro, ru = io.reg_name(a.reg), iu.reg_name(b.reg)
                if a.access & capstone.CS_AC_READ:
                    self.reg(ro, ru, False, where)
                if a.access & capstone.CS_AC_WRITE:
                    writes.append((ro, ru))
            elif a.type == X.X86_OP_IMM:
                if not (frame_imm or chk_imm):
                    self.value(io, iu, a.imm, b.imm, iu.imm_offset if iu.imm_offset else None, where,
                               o_reloc=self.img.reloc_positions(io.address + io.imm_offset, 1) if io.imm_offset else [])
            elif a.type == X.X86_OP_MEM:
                self.mem(io, iu, a.mem, b.mem, a.access if m != "lea" else "lea", where)
            else:
                if io.op_str != iu.op_str:
                    raise Mismatch("%s: operand %s vs %s" % (where, io.op_str, iu.op_str))
        # implicit registers are the same physical ones on both sides (same mnemonic)
        try:
            rr, ww = io.regs_access()
            ex = {o.reg for o in oo if o.type == X.X86_OP_REG}
            ex |= {r for o in oo if o.type == X.X86_OP_MEM for r in (o.mem.base, o.mem.index) if r}
            for r in rr:
                nm = io.reg_name(r)
                if r not in ex and nm in FAM and FAM[nm][0] in GPR:
                    self.reg(nm, nm, False, where + " (implicit)")
            for r in ww:
                nm = io.reg_name(r)
                if r not in ex and nm in FAM and FAM[nm][0] in GPR:
                    writes.append((nm, nm))
        except capstone.CsError:
            pass
        for ro, ru in writes:
            self.reg(ro, ru, True, where)
            if FAM.get(ro, ("", ""))[0] in CALLEE_SAVED:
                self.clob_o.add(FAM[ro][0])
            if FAM.get(ru, ("", ""))[0] in CALLEE_SAVED:
                self.clob_u.add(FAM[ru][0])
        if m == "ret" and self.live is not None:
            self.publish(where)
        if m == "ret":
            if self.clob_o or self.clob_u:
                raise Mismatch("%s: callee-saved registers not restored: orig %s, ours %s"
                               % (where, sorted(self.clob_o), sorted(self.clob_u)))
            for f in ("eax", "edx"):
                if f in self.pending and self.pending[f] != f:
                    raise Mismatch("%s: return value in %s vs %s" % (where, f, self.pending[f]))
        self.depth_o += self.esp_effect(io, "o")
        self.depth_u += self.esp_effect(iu, "u")
        if chk_imm:
            self.last_eax_imm = (self.frame_o, self.frame_u)

    def call(self, io, iu, to, tu, where):
        # values flowing into the call in caller-saved registers must be in the same registers
        for fo, fu in list(self.pending.items()):
            if fo in CALLER_SAVED and fo != fu:
                raise Mismatch("%s: argument register %s vs %s" % (where, fo, fu))
        self.pending.clear()
        if self.last_eax_imm and to is not None and self.depth_o == 0:
            # __chkstk: allocates eax bytes
            self.depth_o += self.last_eax_imm[0]
            self.depth_u += self.last_eax_imm[1]
            self.last_eax_imm = ()
            return
        po = self.pop_o(to)
        self.depth_o -= po
        # our callee unresolved: the calls are aligned, so it is taken to pop what the original's callee pops
        self.depth_u -= self.pop_u(iu, tu) if tu is not None else po
        # the call returns in eax:edx; ecx/edx otherwise hold garbage on both sides
        for f in ("eax", "edx"):
            self.reg(f, f, True, where + " (return)")
        self.pending.clear()


class Live:
    """Function-wide renaming (case mode): registers and slots that carry a value into a case, and slots any case
    shares with the prologue/epilogue, must be renamed the same way in every case."""

    def __init__(self):
        self.f, self.i = {}, {}
        self.new = []

    def begin(self):
        self.new = []

    def rollback(self):
        for kind, a, b in self.new:
            self.f.pop((kind, a), None)
            self.i.pop((kind, b), None)
        self.new = []

    def bind(self, kind, a, b, where):
        fa, ib = self.f.get((kind, a)), self.i.get((kind, b))
        if fa is None and ib is None:
            self.f[(kind, a)], self.i[(kind, b)] = b, a
            self.new.append((kind, a, b))
        elif fa != b or ib != a:
            raise Mismatch("%s: function-wide %s %s / %s, but elsewhere %s is %s and %s is %s"
                           % (where, kind, fmt(a), fmt(b), fmt(a), fmt(fa), fmt(b), fmt(ib)))


def fmt(v):
    return "%+d" % v if isinstance(v, int) else str(v)


def live_in_slots(insns, depth, pro=frozenset()):
    """Slots (offset from the entry esp) a range reads before it writes them: values crossing into the range."""
    seen_w, out, d = set(), set(), depth
    for i in insns:
        for o in i.operands:
            if o.type == X.X86_OP_MEM and o.mem.base and i.reg_name(o.mem.base) == "esp":
                k = o.mem.disp - d
                if k >= 0:
                    continue
                if i.mnemonic == "lea" and not o.mem.index and k not in pro:
                    seen_w.add(k)
                elif i.mnemonic == "lea" or o.mem.index or o.access & capstone.CS_AC_READ:
                    if k not in seen_w:
                        out.add(k)
                elif o.access & capstone.CS_AC_WRITE:
                    seen_w.add(k)
        m = i.mnemonic
        if m == "push":
            d += 4
        elif m == "pop":
            d -= 4
        elif m in ("add", "sub") and i.op_str.startswith("esp, ") and len(i.operands) == 2 and \
                i.operands[1].type == X.X86_OP_IMM:
            d += i.operands[1].imm if m == "sub" else -i.operands[1].imm
        elif m in ("jmp", "ret"):
            d = depth
    return out


# ---- driver --------------------------------------------------------------------------------------------------
def frame_size(insns):
    """Bytes the prologue allocates: `mov eax, N; call __chkstk` at entry, or the first `sub esp, N` before any
    call or branch (an SEH prologue pushes and loads fs:[0] first)."""
    for k, i in enumerate(insns[:12]):
        if i.mnemonic == "mov" and i.op_str.startswith("eax, ") and k + 1 < len(insns) and insns[k + 1].mnemonic == "call" \
                and k == 0:
            try:
                return int(i.op_str[5:], 0)
            except ValueError:
                return 0
        if i.mnemonic == "sub" and i.op_str.startswith("esp, "):
            try:
                return int(i.op_str[5:], 0)
            except ValueError:
                return 0
        if i.mnemonic == "call" or i.mnemonic.startswith("j"):
            break
    return 0


def dispatch(insns):
    """Index of the switch's indirect jump `jmp [reg*4 + table]` and (bias, last index) from the add/cmp before it."""
    for k, i in enumerate(insns):
        if i.mnemonic == "jmp" and i.operands and i.operands[0].type == X.X86_OP_MEM and i.operands[0].mem.scale == 4 \
                and i.operands[0].mem.index:
            bias = last = None
            for j in insns[max(0, k - 6):k]:
                if j.mnemonic == "add" and len(j.operands) == 2 and j.operands[1].type == X.X86_OP_IMM:
                    bias = j.operands[1].imm
                if j.mnemonic == "cmp" and len(j.operands) == 2 and j.operands[1].type == X.X86_OP_IMM:
                    last = j.operands[1].imm
            return k, bias, last
    return None, None, None


def prologue_slots(insns, frame):
    """Slots the prologue writes or takes the address of (offsets from the entry esp)."""
    out, d = set(), 0
    for k, i in enumerate(insns):
        for o in i.operands:
            if o.type == X.X86_OP_MEM and o.mem.base and i.reg_name(o.mem.base) == "esp":
                kk = o.mem.disp - d
                if kk < 0 and (i.mnemonic == "lea" or o.access & capstone.CS_AC_WRITE):
                    out.add(kk)
        m = i.mnemonic
        if m == "call" and k <= 2 and frame:
            d += frame
        elif m == "push":
            d += 4
        elif m == "pop":
            d -= 4
        elif m in ("sub", "add") and i.op_str.startswith("esp, ") and i.operands[1].type == X.X86_OP_IMM:
            d += i.operands[1].imm if m == "sub" else -i.operands[1].imm
        elif m == "ret":
            d = frame + 16 if frame else d
    return out


def prologue_depth(insns, frame):
    d = 0
    for k, i in enumerate(insns):
        m = i.mnemonic
        if m == "call" and k <= 2 and frame:
            d += frame
        elif m == "push":
            d += 4
        elif m == "pop":
            d -= 4
        elif m in ("sub", "add") and i.op_str.startswith("esp, ") and i.operands[1].type == X.X86_OP_IMM:
            d += i.operands[1].imm if m == "sub" else -i.operands[1].imm
        elif m == "ret":
            d = frame + 16 if frame else d      # an early return path; the dispatch path keeps the saved registers
    return d


def run_cases(a, va, oi, ui, sec, ulo, relocs, d, symptr, reloc_target, img, pop_at, names):
    ko, bias_o, last_o = dispatch(oi)
    ku, bias_u, last_u = dispatch(ui)
    if ko is None or ku is None:
        print("%08x  no switch dispatch found" % va)
        return None
    # tables: the original's from the image, ours through the relocations of the table section
    jo = oi[ko]
    t_o = jo.operands[0].mem.disp
    n = last_o + 1
    tab_o = [img.u32(t_o + 4 * k) for k in range(n)]
    p = jo.address  # noqa
    ju = ui[ku]
    roff = ju.address + ju.disp_offset
    si, _typ = relocs[roff]
    tsec = struct.unpack_from("<h", d, symptr + 18 * si + 12)[0] - 1
    tval = struct.unpack_from("<I", d, symptr + 18 * si + 8)[0] + struct.unpack_from("<I", sec.data, roff)[0]
    coff_secs = a._coff.sections
    tdata = coff_secs[tsec].data
    trel = {off: si2 for off, si2, _t in coff_secs[tsec].relocs}
    tab_u = []
    for k in range(last_u + 1):
        o = tval + 4 * k
        tab_u.append(struct.unpack_from("<I", d, symptr + 18 * trel[o] + 8)[0] + struct.unpack_from("<I", tdata, o)[0])
    if (bias_o, last_o) != (bias_u, last_u):
        print("%08x  switch differs: bias/last %s vs %s" % (va, (bias_o, last_o), (bias_u, last_u)))
        return None
    # ranges: [code start, first case) is the prologue; each table target starts a range
    def ranges(insns, tab):
        starts = sorted(set(tab))
        keys = {}
        for k, t in enumerate(tab):
            keys.setdefault(t, set()).add(k)
        rs = [("pre", insns[0].address, starts[0])]
        for x, t in enumerate(starts):
            end = starts[x + 1] if x + 1 < len(starts) else insns[-1].address + insns[-1].size
            rs.append((frozenset(keys[t]), t, end))
        return rs
    R_o, R_u = ranges(oi, tab_o), ranges(ui, tab_u)
    by_o = {r[0]: r for r in R_o}
    by_u = {r[0]: r for r in R_u}
    import bisect
    st_o, st_u = [r[1] for r in R_o], [r[1] for r in R_u]
    idx_o = {i.address: k for k, i in enumerate(oi)}
    idx_u = {i.address: k for k, i in enumerate(ui)}

    def key_of(side, addr):
        R, st, idx = (R_o, st_o, idx_o) if side == "o" else (R_u, st_u, idx_u)
        x = bisect.bisect_right(st, addr) - 1
        if x < 0 or addr not in idx:
            return ("?", addr)
        rk, lo, _hi = R[x]
        return (rk, idx[addr] - idx[lo])

    from collections import Counter as _C
    def special(I, ja_k):
        jm = _C(i.operands[0].imm for i in I if i.mnemonic == "jmp" and i.operands and i.operands[0].type == X.X86_OP_IMM)
        exit_ = jm.most_common(1)[0][0] if jm else None
        dflt = None
        for j in I[max(0, ja_k - 3):ja_k]:
            if j.mnemonic == "ja" and j.operands[0].type == X.X86_OP_IMM:
                dflt = j.operands[0].imm
        return {exit_: "exit", dflt: "default"}
    spec = {"o": special(oi, ko), "u": special(ui, ku)}
    memo = {}
    reloc_u = set()
    for off_ in relocs:
        reloc_u.update(range(off_, off_ + 4))

    def block_key(side, addr, depth=0):
        """A jump leaving the case: what matters is the code it lands on, not where that code sits. The block from
        the target to its first jmp/ret, registers and stack offsets masked, addresses replaced by what they name."""
        if addr in spec[side] and spec[side][addr]:
            return (spec[side][addr],)
        mk = (side, addr, depth)
        if mk in memo:
            return memo[mk]
        I, idx = (oi, idx_o) if side == "o" else (ui, idx_u)
        if addr not in idx:
            return ("?",)
        out = []
        for i in I[idx[addr]:idx[addr] + 40]:
            t = i.mnemonic + " " + i.op_str
            t = re.sub(r"\b(e[abcd]x|e[sd]i|ebp|[abcd][lh]|[abcd]x|[sd]il?)\b", "r", t)
            t = re.sub(r"esp \+ (0x[0-9a-f]+|\d+)", "esp+S", t)
            relocated = (any(img.is_reloc(i.address + k) for k in range(i.size)) if side == "o"
                         else any(i.address + k in reloc_u for k in range(i.size)))
            if i.mnemonic.startswith("j") or i.mnemonic == "call" or relocated:
                t = re.sub(r"0x[0-9a-f]+|\b0\b", "A", t)
            out.append(t)
            if i.mnemonic in ("jmp", "ret"):
                if i.mnemonic == "jmp" and i.operands and i.operands[0].type == X.X86_OP_IMM:
                    tgt_ = i.operands[0].imm
                    out.append(spec[side].get(tgt_) or "elsewhere")
                break
        # order-insensitive: the target block's own scheduling is judged in its own case, strictly
        memo[mk] = tuple(sorted(out, key=repr))
        return memo[mk]

    def insns_of(side, r):
        I, idx = (oi, idx_o) if side == "o" else (ui, idx_u)
        _k, lo, hi = r
        return [i for i in I[idx[lo]:] if i.address < hi]

    fo, fu = frame_size(oi), frame_size(ui)
    dep_o = prologue_depth(oi[:ko], fo)
    dep_u = prologue_depth(ui[:ku], fu)
    # function-wide slots: anything a case reads before writing, or the prologue touches
    ps_o, ps_u = prologue_slots(oi[:ko], fo), prologue_slots(ui[:ku], fu)

    def exit_reads(I, idx, ex, dep):
        if ex is None or ex not in idx:
            return set()
        blk = []
        for i in I[idx[ex]:]:
            blk.append(i)
            if i.mnemonic in ("ret", "jmp"):
                break
        return live_in_slots(blk, dep, frozenset())
    ex_o = next((a_ for a_, n_ in spec["o"].items() if n_ == "exit"), None)
    ex_u = next((a_ for a_, n_ in spec["u"].items() if n_ == "exit"), None)
    gs_o = ps_o | exit_reads(oi, idx_o, ex_o, dep_o)
    gs_u = ps_u | exit_reads(ui, idx_u, ex_u, dep_u)
    live = Live()
    pop_u = lambda iu, tu: pop_at(tu) if tu else 0
    # the prologue, from function entry (identity registers) up to the dispatch jump
    pre = Checker(Side("orig", oi[:ko], oi[0].address), Side("ours", ui[:ku], 0), img, reloc_target, pop_at, pop_u,
                  (fo, fu))
    try:
        pre.run()
        pre_ok, pre_why = True, ""
        for f, u in pre.fwd.items():
            live.f[("reg", f)], live.i[("reg", u)] = u, f
        for ko_, ku_ in pre.sfwd.items():
            live.f[("slot", ko_)], live.i[("slot", ku_)] = ku_, ko_
    except Mismatch as e:
        pre_ok, pre_why = False, str(e)
    print("%08x  prologue %d insns: %s%s" % (va, ko, "INSN-EXACT" if pre_ok else "DIFF", ("\n    " + pre_why) if pre_why else ""))
    results = {}
    keys = sorted((k for k in by_o if k != "pre"), key=lambda k: by_o[k][1])
    for rk in keys:
        label = ",".join(sorted({names.get(k + bias_inv(bias_o), str(k + bias_inv(bias_o))) for k in rk}))[:60]
        if rk not in by_u:
            results[rk] = ("GROUPING", "ours does not give exactly these opcodes one shared body", label, 0)
            continue
        I_o, I_u = insns_of("o", by_o[rk]), insns_of("u", by_u[rk])
        cur = rk

        def tk(side, addr, cur=cur):
            if spec[side].get(addr):
                return (spec[side][addr],)
            kk = key_of(side, addr)
            return ("here", kk[1]) if kk[0] == cur else ("block", block_key(side, addr))
        ck = Checker(Side("orig", I_o, I_o[0].address), Side("ours", I_u, 0), img, reloc_target, pop_at, pop_u,
                     (fo, fu), live=live, target_key=tk, depth=(dep_o, dep_u), global_slots=(gs_o, gs_u),
                     pro_slots=(ps_o, ps_u))
        ck.o.index = {i.address: k for k, i in enumerate(I_o)}
        ck.u.index = {i.address: k for k, i in enumerate(I_u)}
        live.begin()
        try:
            ck.run()
            results[rk] = ("INSN-EXACT", "", label, len(I_o))
        except Mismatch as e:
            live.rollback()
            results[rk] = ("DIFF", str(e), label, len(I_o))
    return pre_ok, pre_why, results


def bias_inv(bias):
    return -bias if bias is not None else 0


def marker_symbol(coff, src, va):
    """The function defined after `// @ 0x<va>` in src, matched on its (qualified) name in the object. slice.py's
    marker parser stops at the first identifier, so `__declspec(noinline) char __fastcall f(...)` needs this."""
    lines = open(src, encoding="utf-8", errors="replace").read().split("\n")
    pat = re.compile(r"^// @ 0x0*%x\b" % va)
    for k, l in enumerate(lines):
        if pat.match(l):
            for d in lines[k + 1:k + 6]:
                if d.startswith("//") or "(" not in d:
                    continue
                head = re.sub(r"__declspec\([^)]*\)", "", d).split("(")[0]
                name = head.split()[-1] if head.split() else ""
                base = name.split("::")[-1].lstrip("*&")
                cands = [n for n in coff.functions() if n.startswith("?" + base + "@") or n == "_" + base]
                if "::" in name:
                    cls = name.split("::")[-2]
                    cands = [n for n in cands if ("@" + cls + "@") in n] or cands
                if cands:
                    return cands[0]
            return None
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("vas", nargs="+")
    ap.add_argument("--flags")
    ap.add_argument("--json")
    ap.add_argument("--cases", action="store_true", help="compare a switch function case by case")
    ap.add_argument("--names", help="json {opcode: name or [names]} for case labels")
    ap.add_argument("--show", type=int, default=0, help="print this many DIFF cases with their reasons")
    ap.add_argument("--trace", action="store_true", help="print both sides with their stack depths (also INSN_EXACT_TRACE=1)")
    a = ap.parse_args()
    vas = [int(v, 16) for x in a.vas for v in x.split(",") if v]
    flags = a.flags.split() if a.flags else list(S.DEFAULT_FLAGS)
    if a.src.replace(os.sep, "/").startswith("src/game/") and "/Isrc/game/include" not in flags:
        flags.append("/Isrc/game/include")
    os.chdir(ROOT)
    obj, log = S.compile_obj(a.src, flags)
    if not obj:
        sys.exit("compile failed: " + (log or "")[-600:])
    coff = Coff(obj)
    img = R.Image()
    db = R.SymbolDB(img)
    res_ = R.Resolver(img, db)
    annots = R.source_annotations([a.src] + S.sibling_headers(a.src))
    sid = os.path.basename(a.src).rsplit(".", 1)[0]

    pop_cache = {}

    def pop_at(va):
        """Bytes the original callee at va pops (ret N), following a jmp thunk."""
        if va in pop_cache:
            return pop_cache[va]
        r = 0
        try:
            lo, hi = img.func_extent(va)
            for i in disasm(img.read(lo, min(hi - lo, 0x20000)), lo):
                if i.mnemonic == "ret":
                    r = int(i.op_str, 0) if i.op_str else 0
                    break
                if i.mnemonic == "jmp" and i.address == lo and i.op_str.startswith("0x"):
                    r = pop_at(int(i.op_str, 16))
                    break
        except Exception:
            r = 0
        pop_cache[va] = r
        return r

    # functions defined in this object resolve through their own `// @ 0x<va>` markers (the resolver knows externals)
    local_va = {}
    for mva in sorted({int(x, 16) for x in re.findall(r"^// @ 0x([0-9a-f]+)", open(a.src, encoding="utf-8",
                                                                                   errors="replace").read(), re.M)}):
        nm = marker_symbol(coff, a.src, mva)
        if nm:
            local_va.setdefault(nm, mva)

    results, ok_all = {}, True
    for va in vas:
        lo, hi = img.func_extent(va)
        sym, how = S.find_symbol(coff, sid, va, a.src, hi - lo)
        if isinstance(sym, list):
            sym = sym[0]
        if sym is None:
            sym = marker_symbol(coff, a.src, va)
        if sym is None:
            frag = not re.search(r"^// @ 0x0*%x\b" % va, open(a.src, encoding="utf-8", errors="replace").read(), re.M)
            v_ = "FRAGMENT" if frag else "NO-SYMBOL"
            print("%08x  %-9s %s" % (va, v_, "no // @ marker: a code block inside another function" if frag else how))
            results["%08x" % va] = {"verdict": v_}
            ok_all = False
            continue
        fs = coff.by_name[sym]
        sec, ulo, uhi = coff.func_extent(fs)
        res = res_.resolve(coff, fs, va, annots)
        relocs = {off: (si, typ) for off, si, typ in sec.relocs}
        unres = set()

        def reloc_target(iu, off, sec=sec, relocs=relocs, res=res, unres=unres):
            if off is None:
                return None
            p = iu.address + off
            if p not in relocs:
                return None
            si, typ = relocs[p]
            stored = struct.unpack_from("<i", sec.data, p)[0]
            if si not in res.addr:
                nm = coff.syms[si].name if si in coff.syms else str(si)
                if nm in local_va:
                    return local_va[nm] if typ == REL_REL32 else (local_va[nm] + stored) & 0xFFFFFFFF
                m_ = re.match(r"^__(real|int64)@([0-9a-f]+)$", nm)
                if m_ and stored == 0:          # a float/int64 constant: its value is in the name
                    hx = m_.group(2)
                    return ("const", bytes.fromhex(hx)[::-1])
                unres.add(nm)
                return "?"
            if typ == REL_REL32:
                return (res.addr[si] + stored + 4) & 0xFFFFFFFF if stored not in (0, -4) else res.addr[si]
            return (res.addr[si] + stored) & 0xFFFFFFFF

        oi = disasm(img.read(lo, hi - lo), lo)
        end = code_end(oi, lo, hi)
        oi = [i for i in oi if i.address < end]
        ui = disasm(bytes(sec.data[ulo:uhi]), ulo)
        # (our jump tables are separate COMDAT sections: nothing to cut off on our side)
        if a.cases:
            a._coff = coff
            dd = open(obj, "rb").read()
            symptr = struct.unpack_from("<I", dd, 8)[0]
            names = {}
            if a.names:
                for k_, v_ in json.load(open(a.names)).items():
                    names[int(k_)] = v_[0] if isinstance(v_, list) else v_
            out = run_cases(a, va, oi, ui, sec, ulo, relocs, dd, symptr, reloc_target, img, pop_at, names)
            if out is None:
                ok_all = False
                continue
            pre_ok, pre_why, cres = out
            from collections import Counter
            cnt = Counter(v[0] for v in cres.values())
            ins = Counter()
            for v in cres.values():
                ins[v[0]] += v[3]
            tot = sum(ins.values()) or 1
            print("%08x  %d case bodies: %s" % (va, len(cres), ", ".join("%s %d" % kv for kv in sorted(cnt.items()))))
            print("          instructions in INSN-EXACT bodies: %d / %d (%.1f%%)" % (ins["INSN-EXACT"], tot, 100.0 * ins["INSN-EXACT"] / tot))
            shown = 0
            for rk, v in sorted(cres.items(), key=lambda kv: kv[1][3]):
                if v[0] != "INSN-EXACT" and shown < a.show:
                    shown += 1
                    print("   %-10s %-40s %4d insns  %s" % (v[0], v[2], v[3], v[1][:150]))
            results["%08x" % va] = {"prologue": "INSN-EXACT" if pre_ok else "DIFF", "prologue_why": pre_why,
                                    "cases": {v[2]: {"verdict": v[0], "why": v[1], "insns": v[3]} for v in cres.values()}}
            if cnt.get("INSN-EXACT", 0) != len(cres) or not pre_ok:
                ok_all = False
            continue
        ck = Checker(Side("orig", oi, lo), Side("ours", ui, 0), img, reloc_target, pop_at,
                     lambda iu, tu: pop_at(tu) if tu else 0, (frame_size(oi), frame_size(ui)))
        try:
            ck.run()
            verdict, why = "INSN-EXACT", ""
        except Mismatch as e:
            verdict, why = "DIFF", str(e)
            ok_all = False
        extra = " (%d operand(s) unverified, unresolved: %s)" % (ck.unverified, ", ".join(sorted(unres))[:120]) if ck.unverified else ""
        print("%08x %6d insns  %-10s %s%s%s" % (va, len(oi), verdict, sym[:60], extra, ("\n    " + why) if why else ""))
        results["%08x" % va] = {"verdict": verdict, "symbol": sym, "insns": len(oi), "ours": len(ui),
                                "unverified": ck.unverified, "unresolved": sorted(unres), "why": why}
    if a.json:
        json.dump(results, open(a.json, "w"), indent=1)
    return 0 if ok_all else 1


if __name__ == "__main__":
    sys.exit(main())
