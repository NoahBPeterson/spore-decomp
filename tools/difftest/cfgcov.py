"""Branch (edge) coverage model for equiv.py: the static control-flow edges of one function and the
facts that make some of them unreachable under the harness.

Edges counted (both builds, each function on its own):
- every conditional jump (jcc, jecxz, loop*): the taken edge (src -> target) and the not-taken edge
  (src -> next instruction);
- every jump-table dispatch (jmp [table + reg*4]): one edge per distinct table target.
Unconditional jumps, calls and fall-throughs are not edges: when every edge above is covered by valid
runs, every instruction reachable from the entry has run, except code that is only reachable through
an edge listed as unreachable (below).

Unreachable edges are never dropped silently: `Cfg.unreachable(...)` returns {edge: reason}, and
equiv.py prints and stores each reason. Reasons:
- "infeasible": an x87 status-word branch (fcom/fucom/ftst + fnstsw ax + test/and/cmp/xor ah + jcc, or
  sahf + jcc) whose condition no comparison outcome (less, equal, greater, unordered) can produce;
- "nan-only": the same pattern where only the unordered (NaN) outcome takes the edge; the harness
  generates no NaN/Inf inputs without --nan (with --nan such edges are required);
- "blocked": only reachable past a call site that never returned: in every run that reached it, it stopped
  at an unmodelled import (its return value is unknown), a C++ throw or a pure virtual call. Handler stops
  that depend on the input (a huge malloc or memcpy) never block;
- "via": only reachable through another unreachable edge (its reason is named).
"""
import capstone
from capstone import x86_const as X

_TERM = (X.X86_INS_RET, X.X86_INS_RETF, X.X86_INS_INT3, X.X86_INS_HLT, X.X86_INS_UD2)


def fmt_edge(e):
    return "%08x->%08x" % e


# jump-table entries read per dispatch (the walk stops at the first entry outside the function); the
# Module System interpreter 0x49fa10 has 2356, so the old 2048 cut its last 115 cases from the CFG
MAX_TABLE = 8192


class Cfg:
    """Static edges of one function. insns: {addr: capstone insn} (recursive descent from entry);
    table_target(a) -> branch target stored in the dword at a (a relocated table entry) or None."""

    def __init__(self, insns, entry, lo, hi, table_target):
        self.insns, self.entry, self.lo, self.hi = insns, entry, lo, hi
        self.edges = {}          # (src, dst) -> "taken" | "fall" | "table"
        self.branch_end = {}     # address after a branch -> (src, kind, fallthrough)
        self.succ = {}           # addr -> [(dst, edge or None, call-site or None)]
        self.cmp_before = {}     # jcc addr -> the flag-setting insn before it (steering)
        prev = {}
        for a, ins in insns.items():
            prev[a + ins.size] = a
        for a in sorted(insns):
            ins = insns[a]
            nxt = a + ins.size
            if ins.id in _TERM:
                self.succ[a] = []
            elif ins.id == X.X86_INS_JMP:
                op = ins.operands[0]
                if op.type == X.X86_OP_IMM:
                    tgt = op.imm & 0xFFFFFFFF
                    self.succ[a] = [(tgt, None, None)] if lo <= tgt < hi else []
                elif op.type == X.X86_OP_MEM and op.mem.index != 0 and op.mem.scale == 4:
                    tbl = op.mem.disp & 0xFFFFFFFF
                    tg = []
                    for k in range(MAX_TABLE):
                        t = table_target(tbl + 4 * k)
                        if t is None or not lo <= t < hi:
                            break
                        if t not in tg:
                            tg.append(t)
                    self.succ[a] = []
                    for t in tg:
                        self.edges[(a, t)] = "table"
                        self.succ[a].append((t, (a, t), None))
                    if tg:
                        self.branch_end[nxt] = (a, "table", None)
                else:
                    self.succ[a] = []
            elif ins.group(capstone.CS_GRP_JUMP):
                op = ins.operands[0]
                if op.type != X.X86_OP_IMM:
                    self.succ[a] = [(nxt, None, None)]
                    continue
                tgt = op.imm & 0xFFFFFFFF
                self.edges[(a, tgt)] = "taken"
                if tgt != nxt:
                    self.edges[(a, nxt)] = "fall"
                self.branch_end[nxt] = (a, "jcc", nxt)
                self.succ[a] = [(tgt, (a, tgt), None)]      # a target outside the function ends the walk there
                if tgt != nxt:
                    self.succ[a].append((nxt, (a, nxt), None))
                p = prev.get(a)
                for _ in range(4):          # nearest flag writer (skipping movs/x87 that do not touch flags)
                    if p is None:
                        break
                    pi = insns[p]
                    if _writes_flags(pi):
                        self.cmp_before[a] = pi
                        break
                    p = prev.get(p)
            elif ins.id == X.X86_INS_CALL:
                self.succ[a] = [(nxt, None, a)]
            else:
                self.succ[a] = [(nxt, None, None)]
        self.prev = prev

    # ------------------------------------------------------------------ static facts
    def x87_facts(self):
        """{edge: 'infeasible' | 'nan-only'} for x87 status-word branches."""
        out = {}
        for (src, dst), kind in self.edges.items():
            if kind == "table":
                continue
            res = x87_branch(self.insns, self.prev, src)
            if res is None:
                continue
            taken, fall = res
            nxt = src + self.insns[src].size
            cats = (taken | fall) if dst == nxt and kind == "taken" else (taken if kind == "taken" else fall)
            if cats & {"lt", "eq", "gt"}:
                continue
            out[(src, dst)] = "nan-only" if "un" in cats else "infeasible"
        return out

    def reachable(self, cut_edges, blocked_calls):
        """Edges reachable from the entry when cut_edges are removed and nothing runs past a call
        site in blocked_calls."""
        seen, got = set(), set()
        work = [self.entry]
        while work:
            a = work.pop()
            if a in seen or a not in self.succ:
                continue
            seen.add(a)
            for dst, e, call in self.succ[a]:
                if e is not None:
                    if e in cut_edges:
                        continue
                    got.add(e)
                if call is not None and call in blocked_calls:
                    continue
                work.append(dst)
        return got

    def unreachable(self, covered, blocked_calls, nan=False):
        """{edge: reason} for uncovered edges the harness cannot reach (see the module docstring).
        blocked_calls: {call-site addr: description}."""
        why = {}
        for e, k in self.x87_facts().items():
            if k == "infeasible":
                why[e] = "infeasible: no x87 comparison outcome takes this branch"
            elif not nan:
                why[e] = "nan-only: only an unordered (NaN) x87 comparison takes this branch (no NaN inputs without --nan)"
        base = set(why)
        reach = self.reachable(base, set(blocked_calls))
        for e in self.edges:
            if e in why or e in reach:
                continue
            # which cut explains it? the blocked call or excluded edge closest before it
            r = None
            if len(blocked_calls) + len(base) > 24:
                why[e] = "blocked/via: only reachable past a blocked call or an unreachable edge"
                continue
            for c, desc in sorted(blocked_calls.items()):
                if e not in self.reachable(base, set(blocked_calls) - {c}):
                    continue
                r = "blocked: only reachable past call @%08x (%s)" % (c, desc)
                break
            if r is None:
                for x in sorted(base):
                    if e in self.reachable(base - {x}, set(blocked_calls)):
                        r = "via: only reachable through unreachable edge %s (%s)" % (fmt_edge(x), why[x].split(":")[0])
                        break
            why[e] = r or "via: only reachable through unreachable edges/calls"
        return {e: r for e, r in why.items() if e not in covered}


def _writes_flags(ins):
    try:
        _r, w = ins.regs_access()
    except capstone.CsError:
        return True
    return X.X86_REG_EFLAGS in w


# ---------------------------------------------------------------------- x87 status-word branches

# C0/C2/C3 in AH (status word bits 8, 10, 14) after fcom/fucom/ftst/ficom for each outcome
_CATS = {"lt": 0x01, "eq": 0x40, "gt": 0x00, "un": 0x45}
_UNKNOWN = (0x80, 0x20, 0x10, 0x08)       # B and TOP: not determined by the comparison
_FCMP = {"fcom", "fcomp", "fcompp", "fucom", "fucomp", "fucompp", "ftst", "ficom", "ficomp"}


def _parity(v):
    return bin(v & 0xFF).count("1") % 2 == 0


def _jcc_taken(mn, f):
    zf, sf, cf, of, pf = f["zf"], f["sf"], f["cf"], f["of"], f["pf"]
    table = {"je": zf, "jne": not zf, "jp": pf, "jnp": not pf, "jb": cf, "jae": not cf,
             "jbe": cf or zf, "ja": not cf and not zf, "js": sf, "jns": not sf, "jl": sf != of,
             "jge": sf == of, "jle": zf or sf != of, "jg": not zf and sf == of, "jo": of, "jno": not of}
    return table.get(mn)


def x87_branch(insns, prev, src):
    """For a jcc at src that tests the x87 condition codes: (set of outcomes taking it, set of
    outcomes falling through), outcomes in {lt, eq, gt, un}; None if the pattern is not recognised."""
    jcc = insns[src]
    mn = jcc.mnemonic
    if _jcc_taken(mn, {"zf": 0, "sf": 0, "cf": 0, "of": 0, "pf": 0}) is None:
        return None
    seq = []
    p = prev.get(src)
    found = False
    for _ in range(10):
        if p is None:
            return None
        ins = insns[p]
        if ins.mnemonic in ("fnstsw", "fstsw"):
            if not (ins.operands and ins.operands[0].type == X.X86_OP_REG and ins.operands[0].reg == X.X86_REG_AX):
                return None
            found = True
            break
        seq.append(ins)
        p = prev.get(p)
    if not found:
        return None
    # the comparison that set C0/C2/C3: the nearest x87 instruction before fnstsw
    q = prev.get(p)
    for _ in range(6):
        if q is None:
            return None
        ins = insns[q]
        if ins.mnemonic.startswith("f"):
            if ins.mnemonic not in _FCMP:
                return None
            break
        q = prev.get(q)
    else:
        return None
    seq.reverse()
    ops = []
    for ins in seq:
        o = ins.operands
        m = ins.mnemonic
        if m.startswith("f") and m not in ("fnstsw", "fstsw"):
            continue                                    # x87 ops leave EFLAGS and AH alone
        if m == "sahf":
            ops.append(("sahf", 0))
            continue
        if m in ("test", "and", "cmp", "xor", "or") and len(o) == 2 and o[0].type == X.X86_OP_REG \
                and o[1].type == X.X86_OP_IMM:
            imm = o[1].imm
            if o[0].reg == X.X86_REG_AH:
                ops.append((m, imm & 0xFF))
                continue
            if o[0].reg in (X.X86_REG_AX, X.X86_REG_EAX) and m == "test" and imm & 0xFF == 0 and imm >> 16 == 0:
                ops.append((m, (imm >> 8) & 0xFF))
                continue
            return None
        try:
            r, w = ins.regs_access()
        except capstone.CsError:
            return None
        if X.X86_REG_EFLAGS in w or any(x in w for x in (X.X86_REG_AH, X.X86_REG_AX, X.X86_REG_EAX)):
            return None
    if not ops:
        return None
    taken, fall = set(), set()
    for cat, bits in _CATS.items():
        for k in range(16):
            ah = bits
            for i, b in enumerate(_UNKNOWN):
                if k >> i & 1:
                    ah |= b
            f = None
            for op, imm in ops:
                if op == "sahf":
                    f = {"sf": bool(ah & 0x80), "zf": bool(ah & 0x40), "pf": bool(ah & 0x04), "cf": bool(ah & 1), "of": False}
                    continue
                if op == "test":
                    r = ah & imm
                    f = {"zf": r == 0, "sf": bool(r & 0x80), "pf": _parity(r), "cf": False, "of": False}
                    continue
                if op == "cmp":
                    r = (ah - imm) & 0xFF
                    sa, sb, sr = ah & 0x80, imm & 0x80, r & 0x80
                    f = {"zf": r == 0, "sf": bool(sr), "pf": _parity(r), "cf": ah < imm,
                         "of": bool(sa != sb and sr != sa)}
                    continue
                ah = {"and": ah & imm, "xor": ah ^ imm, "or": ah | imm}[op]
                f = {"zf": ah == 0, "sf": bool(ah & 0x80), "pf": _parity(ah), "cf": False, "of": False}
            if f is None:
                return None
            (taken if _jcc_taken(mn, f) else fall).add(cat)
    return taken, fall
