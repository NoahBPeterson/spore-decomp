"""Concolic input steering for equiv.py: z3 solves the branches local input-to-state cannot.

steer.py's input-to-state ("Redqueen") changes ONE input location per candidate, to the value a compare saw on
the other side. Conditions that need several locations at once are out of its reach: check_party 0x49d160
passes only when the id is below the table count AND PartyMgr::index_of 0x48ad00 finds it in its id table AND
the record it lands on has type 1 - three dwords in three places, each compare reached only once the previous
one passes. This module traces one run of the ORIGINAL instruction by instruction and keeps, next to the
concrete state unicorn computes, a z3 expression for every register and memory byte that depends on the input
(pool bytes, image .data bytes, argument bytes). Every conditional jump whose flags depend on the input adds a
path constraint. To push a run across a decision, the constraints before it plus the negation of it are solved
and the model is written back into the input (steer.set_loc), and the new input is traced again: a few such
generations walk a chain of decisions.

Soundness is the comparison's business, not this module's: every candidate is an ordinary Input that both
builds run and that is compared like any other. Precision is the only thing that can be lost, and is lost on
purpose where modelling would be expensive: an instruction outside the modelled set makes everything it writes
concrete again (its register outputs, and through the memory-write hook every byte it stores), a symbolic
memory address is pinned to its concrete value (a path constraint), and a branch whose flags come from an
unmodelled instruction adds no constraint.

Modelled: mov movzx movsx lea add sub inc dec neg and or xor not shl/sal shr sar (immediate or cl count) imul
(2 and 3 operands) cdq cmp test jcc setcc cmovcc push pop xchg; partial registers; byte-precise memory.
"""
import os, struct

import capstone
from capstone import x86_const as X
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
import unicorn.x86_const as U

import machine as M

try:
    import z3
except ImportError:             # the harness runs without it; concolic steering is then simply off
    z3 = None

_md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
_md.detail = True

FULL = {"eax": U.UC_X86_REG_EAX, "ebx": U.UC_X86_REG_EBX, "ecx": U.UC_X86_REG_ECX, "edx": U.UC_X86_REG_EDX,
        "esi": U.UC_X86_REG_ESI, "edi": U.UC_X86_REG_EDI, "ebp": U.UC_X86_REG_EBP, "esp": U.UC_X86_REG_ESP}
# partial register -> (full register, low bit, width)
PART = {}
for f in ("eax", "ebx", "ecx", "edx"):
    c = f[1]
    PART[f] = (f, 0, 32)
    PART[c + "x"] = (f, 0, 16)
    PART[c + "l"] = (f, 0, 8)
    PART[c + "h"] = (f, 8, 8)
for f in ("esi", "edi", "ebp", "esp"):
    PART[f] = (f, 0, 32)
    PART[f[1:]] = (f, 0, 16)
EFL = {"cf": 0, "pf": 2, "zf": 6, "sf": 7, "of": 11}
CC = ("e", "ne", "b", "ae", "be", "a", "l", "ge", "le", "g", "s", "ns")
MAX_STEPS = 400000              # instructions traced per run (the interpreter's get_operand loop is ~2-5k)
MAX_PATH = 4000                 # symbolic branches kept per run


def cc_of(mnemonic):
    """'jge' / 'setge' / 'cmovge' -> 'ge' (aliases folded), or None."""
    for p in ("cmov", "set", "j"):
        if mnemonic.startswith(p):
            c = mnemonic[len(p):]
            c = {"z": "e", "nz": "ne", "c": "b", "nae": "b", "nc": "ae", "nb": "ae", "na": "be", "nbe": "a",
                 "nge": "l", "nl": "ge", "ng": "le", "nle": "g"}.get(c, c)
            return c if c in CC else None
    return None


def eflags_cc(fl, c):
    """Concrete value of condition c under EFLAGS fl."""
    bit = {k: (fl >> v) & 1 for k, v in EFL.items()}
    return {"e": bit["zf"], "ne": not bit["zf"], "b": bit["cf"], "ae": not bit["cf"],
            "be": bit["cf"] or bit["zf"], "a": not (bit["cf"] or bit["zf"]),
            "l": bit["sf"] != bit["of"], "ge": bit["sf"] == bit["of"],
            "le": bit["zf"] or bit["sf"] != bit["of"], "g": not bit["zf"] and bit["sf"] == bit["of"],
            "s": bit["sf"], "ns": not bit["sf"]}[c]


class Trace:
    """One traced run: symbolic state, path constraints and the input variables met."""

    def __init__(self, runner, steer, side):
        self.r, self.st, self.side = runner, steer, side
        self.m = runner.m
        self.uc = runner.m.uc
        self.regs = {}              # full register -> z3 BitVec(32) (absent: concrete)
        self.mem = {}               # address -> z3 BitVec(8), or None: overwritten with a concrete byte
        self.vars = {}              # address -> its input variable
        self.flags = None           # ("sub"|"logic"|"add", a, b, result, bits) of the last flag-setting op
        self.pending = None         # (reg results, mem stores, flags) of the instruction just hooked
        self.path = []              # [(z3 Bool as executed, eip, taken, cond-if-taken)]
        self.taken = {}             # jcc eip -> concrete direction of its LAST execution (symbolic or not)
        self.pins = []              # concretization constraints (symbolic addresses), in order with path
        self.steps = 0
        self.cache = {}

    # ---------------------------------------------------------------- values
    def var(self, a):
        v = self.vars.get(a)
        if v is None:
            v = self.vars[a] = z3.BitVec("m_%08x" % a, 8)
        return v

    def input_byte(self, a):
        return self.st.region(a) in ("pool", "data", "arg")

    def rd_reg(self, name):
        """(expr or None, concrete) of a (partial) register."""
        f, lo, w = PART[name]
        conc = (self.uc.reg_read(FULL[f]) >> lo) & ((1 << w) - 1)
        e = self.regs.get(f)
        if e is None:
            return None, conc
        return (z3.Extract(lo + w - 1, lo, e) if w != 32 else e), conc

    def wr_reg(self, name, e, out):
        f, lo, w = PART[name]
        if w == 32:
            out[f] = e
            return
        full = self.regs.get(f) if f not in out else out[f]
        if e is None and full is None:
            out[f] = None
            return
        cur = self.uc.reg_read(FULL[f])
        base = full if full is not None else z3.BitVecVal(cur, 32)
        val = e if e is not None else z3.BitVecVal((cur >> lo) & ((1 << w) - 1), w)
        parts = []
        if lo + w < 32:
            parts.append(z3.Extract(31, lo + w, base))
        parts.append(val)
        if lo > 0:
            parts.append(z3.Extract(lo - 1, 0, base))
        out[f] = z3.Concat(*parts) if len(parts) > 1 else parts[0]

    def rd_mem(self, a, n):
        bs, sym = [], False
        try:
            raw = self.st._peek(a, n)
        except Exception:
            raw = None
        for k in range(n):
            x = a + k
            if x in self.mem:
                e = self.mem[x]
                if e is None:
                    bs.append(z3.BitVecVal(raw[k] if raw else 0, 8))
                else:
                    bs.append(e)
                    sym = True
            elif self.input_byte(x):
                bs.append(self.var(x))
                sym = True
            else:
                bs.append(z3.BitVecVal(raw[k] if raw else 0, 8))
        if not sym:
            return None, int.from_bytes(raw, "little") if raw else 0
        return (z3.Concat(*reversed(bs)) if n > 1 else bs[0]), (int.from_bytes(raw, "little") if raw else 0)

    def ea(self, o):
        """Concrete effective address; a symbolic base/index is pinned to its value (a path constraint)."""
        mm = o.mem
        a = mm.disp
        for r_, sc in ((mm.base, 1), (mm.index, mm.scale)):
            if not r_:
                continue
            nm = _md.reg_name(r_)
            if nm not in PART:
                return None
            e, c = self.rd_reg(nm)
            if e is not None:
                self.pins.append((len(self.path), e == c))
            a += c * sc
        return a & 0xFFFFFFFF

    def opnd(self, o, bits):
        """(expr or None, concrete) of an operand at width bits."""
        if o.type == X.X86_OP_IMM:
            return None, o.imm & ((1 << bits) - 1)
        if o.type == X.X86_OP_REG:
            nm = _md.reg_name(o.reg)
            if nm not in PART:
                return None, 0
            return self.rd_reg(nm)
        if o.type == X.X86_OP_MEM:
            a = self.ea(o)
            if a is None:
                return None, 0
            return self.rd_mem(a, o.size)
        return None, 0

    @staticmethod
    def bv(e, c, bits):
        return e if e is not None else z3.BitVecVal(c, bits)

    # ---------------------------------------------------------------- stepping
    def on_code(self, uc, address, size, _):
        self.apply_pending()
        self.steps += 1
        if self.steps > MAX_STEPS or self.r.cur is not self.side:
            return
        try:
            ins = self.cache.get(address)
            if ins is None:
                code = bytes(uc.mem_read(address, size))
                ins = self.cache[address] = next(_md.disasm(code, address))
            self.step(ins)
        except Exception:
            self.concretize_written(None)

    def on_write(self, uc, access, address, size, value, _):
        for k in range(size):
            self.mem[address + k] = None
        if self.pending is not None and self.pending[1]:
            # this instruction's symbolic stores are re-applied after it (apply_pending)
            pass

    def apply_pending(self):
        p, self.pending = self.pending, None
        if p is None:
            return
        regs, stores, flags = p
        for f, e in regs.items():
            if e is None or (z3.is_bv_value(z3.simplify(e)) if e is not None else False):
                self.regs.pop(f, None)
            else:
                self.regs[f] = z3.simplify(e)
        for a, e in stores:
            n = e.size() // 8
            for k in range(n):
                self.mem[a + k] = z3.simplify(z3.Extract(8 * k + 7, 8 * k, e))
        if flags is not False:
            self.flags = flags

    def concretize_written(self, ins):
        """An instruction outside the model: what it writes is concrete from now on (its stores already are:
        on_write marks every byte it writes)."""
        regs, fl = {}, None
        if ins is not None:
            fl = False
            try:
                for r_ in ins.regs_access()[1]:
                    nm = _md.reg_name(r_)
                    if nm in PART:
                        regs[PART[nm][0]] = None
                    elif nm == "eflags":
                        fl = None
            except Exception:
                fl = None
        self.pending = (regs, [], fl)

    @staticmethod
    def writes_flags(ins):
        try:
            return any(_md.reg_name(r_) == "eflags" for r_ in ins.regs_access()[1])
        except Exception:
            return True

    def step(self, ins):
        mn = ins.mnemonic
        ops = ins.operands
        regs, stores = {}, []
        flags = False                                       # False: flags untouched

        def dst_write(o, e, bits):
            if o.type == X.X86_OP_REG:
                nm = _md.reg_name(o.reg)
                if nm in PART:
                    self.wr_reg(nm, e, regs)
            elif o.type == X.X86_OP_MEM:
                a = self.ea(o)
                if a is not None and e is not None:
                    stores.append((a, e))

        cc = cc_of(mn)
        if mn.startswith("j") and cc is not None:
            self.taken[ins.address] = bool(eflags_cc(self.uc.reg_read(U.UC_X86_REG_EFLAGS), cc))
            self.branch(ins, cc)
            self.pending = ({}, [], False)
            return
        if mn in ("mov", "movzx", "movsx", "movsxd"):
            bits = ops[0].size * 8
            e, c = self.opnd(ops[1], ops[1].size * 8)
            if e is not None and ops[1].size * 8 < bits:
                e = (z3.ZeroExt if mn == "movzx" else z3.SignExt)(bits - ops[1].size * 8, e)
            dst_write(ops[0], e, bits)
        elif mn == "lea":
            mm = ops[1].mem
            terms, sym = [z3.BitVecVal(mm.disp & 0xFFFFFFFF, 32)], False
            for r_, sc in ((mm.base, 1), (mm.index, mm.scale)):
                if r_:
                    nm = _md.reg_name(r_)
                    if nm not in PART:
                        raise ValueError(nm)
                    e, c = self.rd_reg(nm)
                    sym = sym or e is not None
                    terms.append(self.bv(e, c, 32) * sc)
            dst_write(ops[0], sum(terms[1:], terms[0]) if sym else None, 32)
        elif mn in ("add", "sub", "and", "or", "xor", "cmp", "test", "adc", "sbb"):
            bits = ops[0].size * 8
            a, ac = self.opnd(ops[0], bits)
            b, bc = self.opnd(ops[1], bits)
            if mn in ("adc", "sbb"):
                if a is not None or b is not None:
                    raise ValueError("carry chain")          # concretized below
                flags = None
            elif a is None and b is None and not (mn == "xor" and self.same(ops)):
                flags = None
                if mn not in ("cmp", "test"):
                    dst_write(ops[0], None, bits)
            else:
                if mn == "xor" and self.same(ops):
                    res, A, B = None, None, None
                    flags = None
                    dst_write(ops[0], None, bits)
                else:
                    A, B = self.bv(a, ac, bits), self.bv(b, bc, bits)
                    res = {"add": A + B, "sub": A - B, "cmp": A - B, "and": A & B, "test": A & B, "or": A | B,
                           "xor": A ^ B}[mn]
                    flags = ("sub" if mn in ("sub", "cmp") else "add" if mn == "add" else "logic", A, B, res, bits)
                    if mn not in ("cmp", "test"):
                        dst_write(ops[0], res, bits)
        elif mn in ("inc", "dec", "neg", "not"):
            bits = ops[0].size * 8
            a, ac = self.opnd(ops[0], bits)
            if a is None:
                dst_write(ops[0], None, bits)
                flags = None if mn != "not" else False
            else:
                res = {"inc": a + 1, "dec": a - 1, "neg": -a, "not": ~a}[mn]
                dst_write(ops[0], res, bits)
                if mn in ("inc", "dec"):
                    flags = ("add", a, z3.BitVecVal(1 if mn == "inc" else -1 & ((1 << bits) - 1), bits), res, bits)
                elif mn == "neg":
                    flags = ("sub", z3.BitVecVal(0, bits), a, res, bits)
        elif mn in ("shl", "sal", "shr", "sar"):
            bits = ops[0].size * 8
            a, ac = self.opnd(ops[0], bits)
            if len(ops) > 1:
                _e, n = self.opnd(ops[1], 8)
            else:
                n = 1
            n &= 31
            if a is None:
                dst_write(ops[0], None, bits)
                flags = None
            else:
                res = {"shl": a << n, "sal": a << n, "shr": z3.LShR(a, n), "sar": a >> n}[mn]
                dst_write(ops[0], res, bits)
                flags = ("logic", res, res, res, bits) if n else False
        elif mn == "imul" and len(ops) in (2, 3):
            bits = ops[0].size * 8
            if len(ops) == 2:
                a, ac = self.opnd(ops[0], bits)
                b, bc = self.opnd(ops[1], bits)
            else:
                a, ac = self.opnd(ops[1], bits)
                b, bc = self.opnd(ops[2], bits)
            if a is None and b is None:
                dst_write(ops[0], None, bits)
            else:
                dst_write(ops[0], self.bv(a, ac, bits) * self.bv(b, bc, bits), bits)
            flags = None
        elif mn == "cdq":
            e, c = self.rd_reg("eax")
            self.wr_reg("edx", None if e is None else z3.If(e < 0, z3.BitVecVal(-1 & 0xFFFFFFFF, 32),
                                                             z3.BitVecVal(0, 32)), regs)
        elif mn.startswith("set") and cc is not None:
            ce = self.cond(cc)
            dst_write(ops[0], None if ce is None else z3.If(ce, z3.BitVecVal(1, 8), z3.BitVecVal(0, 8)), 8)
        elif mn.startswith("cmov") and cc is not None:
            ce = self.cond(cc)
            a, ac = self.opnd(ops[0], 32)
            b, bc = self.opnd(ops[1], 32)
            fl = self.uc.reg_read(U.UC_X86_REG_EFLAGS)
            if ce is None:
                taken = eflags_cc(fl, cc)
                dst_write(ops[0], b if taken else a, 32)
            else:
                dst_write(ops[0], z3.If(ce, self.bv(b, bc, 32), self.bv(a, ac, 32)), 32)
        elif mn == "push":
            bits = ops[0].size * 8
            e, c = self.opnd(ops[0], bits)
            esp = self.uc.reg_read(U.UC_X86_REG_ESP)
            if e is not None:
                stores.append(((esp - ops[0].size) & 0xFFFFFFFF, e))
        elif mn == "pop":
            esp = self.uc.reg_read(U.UC_X86_REG_ESP)
            e, c = self.rd_mem(esp, ops[0].size)
            dst_write(ops[0], e, ops[0].size * 8)
        elif mn == "xchg":
            a, ac = self.opnd(ops[0], ops[0].size * 8)
            b, bc = self.opnd(ops[1], ops[1].size * 8)
            dst_write(ops[0], b, ops[0].size * 8)
            dst_write(ops[1], a, ops[1].size * 8)
        elif mn in ("call", "ret", "jmp", "nop", "leave", "int3"):
            if mn == "leave":
                regs["esp"] = None
                regs["ebp"] = None
            self.pending = (regs, [], False)
            return
        else:
            self.concretize_written(ins)
            return
        self.pending = (regs, stores, flags)

    @staticmethod
    def same(ops):
        return len(ops) == 2 and ops[0].type == ops[1].type == X.X86_OP_REG and ops[0].reg == ops[1].reg

    def cond(self, c):
        """z3 Bool for condition c from the lazily recorded flag op, or None when the flags are concrete."""
        f = self.flags
        if f is None:
            return None
        kind, A, B, R, bits = f
        z = R == 0
        s = R < 0
        if kind == "sub":
            t = {"e": A == B, "ne": A != B, "b": z3.ULT(A, B), "ae": z3.UGE(A, B), "be": z3.ULE(A, B),
                 "a": z3.UGT(A, B), "l": A < B, "ge": A >= B, "le": A <= B, "g": A > B, "s": s, "ns": z3.Not(s)}
        elif kind == "logic":
            t = {"e": z, "ne": z3.Not(z), "b": z3.BoolVal(False), "ae": z3.BoolVal(True), "be": z,
                 "a": z3.Not(z), "l": s, "ge": z3.Not(s), "le": z3.Or(z, s), "g": z3.And(z3.Not(z), z3.Not(s)),
                 "s": s, "ns": z3.Not(s)}
        else:                                               # add / inc / dec: only zero and sign are modelled
            t = {"e": z, "ne": z3.Not(z), "s": s, "ns": z3.Not(s)}
        return t.get(c)

    def branch(self, ins, c):
        ce = self.cond(c)
        if ce is None or len(self.path) >= MAX_PATH:
            return
        taken = bool(eflags_cc(self.uc.reg_read(U.UC_X86_REG_EFLAGS), c))
        self.path.append((ce if taken else z3.Not(ce), ins.address, taken, ce))


class Concolic:
    def __init__(self, runner, steer):
        self.r, self.st = runner, steer

    def trace(self, side, inp):
        """Run inp on side with the tracer -> Trace (or None when z3 is missing)."""
        if z3 is None:
            return None
        t = Trace(self.r, self.st, side)
        uc = self.r.m.uc
        hooks = [uc.hook_add(UC_HOOK_CODE, t.on_code), uc.hook_add(UC_HOOK_MEM_WRITE, t.on_write)]
        try:
            t.status = self.r.run_side(side, inp)["status"]
        except Exception as e:
            t.status = ("error", repr(e))
        finally:
            for h in hooks:
                uc.hook_del(h)
        t.apply_pending()
        return t

    def flip(self, t, i, inp, timeout_ms=3000):
        """Input whose run keeps t.path[:i] and takes t.path[i] the other way, or None."""
        s = z3.Solver()
        s.set("timeout", timeout_ms)
        for k in range(i):
            s.add(t.path[k][0])
        for at, pin in t.pins:
            if at <= i:
                s.add(pin)
        s.add(z3.Not(t.path[i][0]))
        if s.check() != z3.sat:
            return None
        mdl = s.model()
        out = inp
        for d in mdl.decls():
            nm = d.name()
            if not nm.startswith("m_"):
                continue
            a = int(nm[2:], 16)
            v = mdl[d].as_long()
            nxt = self.st.set_loc(out, (a, 1), v, "int")
            if nxt is not None:
                out = nxt
        return out if out is not inp else None

    def steer(self, side, inp0, src, window=None, depth=4, width=6, max_traces=40):
        """Candidates that send the run the other way at branch src (a jcc of the tested function).

        window: [(first eip, end eip)] of the code whose decisions may be flipped (the callee a `call f; test al, al`
        branch depends on, and its callees), or None: src's own decisions. Beam search: from each input, every
        symbolic decision in the window is negated in turn (the path before it kept) and the solution traced;
        a solution under which src goes the other way is returned at once, the others that reach decisions not
        seen before are expanded at the next level (src's branch is checked concretely, so it may test a value
        the callee computed, such as `xor al, al` vs `mov al, 1`). Returns [] when src is never reached."""
        dbg = os.environ.get("DIFFTEST_STEER_DEBUG")
        t0 = self.trace(side, inp0)
        if t0 is None or src not in t0.taken:
            if dbg:
                print("  concolic %08x: %s" % (src, "no trace" if t0 is None else "src not reached (path %d, steps %d, status %s)"
                                               % (len(t0.path), t0.steps, getattr(t0, "status", "?"))), flush=True)
            return []
        base = t0.taken[src]

        def decisions(t):
            if window is None:
                # src's own decisions; when src is concrete on this path (is_between 0x49fb71 on an operation with
                # fewer than 3 operands compares stale frame slots), every earlier decision instead: a flip that
                # makes src depend on the input (the operand count) is expanded and src flipped one level down
                own = [k for k, p in enumerate(t.path) if p[1] == src]
                return own or list(range(len(t.path)))
            return [k for k, p in enumerate(t.path) if any(lo <= p[1] < hi for lo, hi in window)]
        level, seen, extra, n = [(inp0, t0)], {(p[1], p[2]) for p in t0.path}, [], 0
        if dbg:
            print("  concolic %08x: reached, %d symbolic decision(s) in the window, path %d" % (
                src, len(decisions(t0)), len(t0.path)), flush=True)
        for d in range(depth):
            nxt = []
            for inp, t in level:
                for k in reversed(decisions(t)[-24:]):
                    if n >= max_traces:
                        break
                    cand = self.flip(t, k, inp)
                    if cand is None:
                        continue
                    n += 1
                    t2 = self.trace(side, cand)
                    cand.origin = "steer"
                    if dbg:
                        print("  concolic d%d flip @%08x -> src %s (steps %d, path %d, status %s)" % (d, t.path[k][1], t2.taken.get(src), t2.steps, len(t2.path), getattr(t2, "status", "?")), flush=True)
                    if t2 is not None and src in t2.taken and t2.taken[src] != base:
                        return [cand] + extra[:7]
                    new = {(p[1], p[2]) for p in t2.path} - seen if t2 is not None else set()
                    if new:
                        seen |= new
                        nxt.append((cand, t2))
                        extra.append(cand)
            if not nxt or n >= max_traces:
                break
            level = nxt[:width]
        return extra[:8]
