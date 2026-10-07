#!/usr/bin/env python3
"""Differential equivalence test: ORIGINAL function (from the binary) vs OUR compiled function.

usage: equiv.py <slice-id> [<va> ...] [--flags "..."] [--inputs N] [--seed S] [--json out.json]
                [--min-valid K] [--min-cov C] [--ulp U] [--strict-calls] [--budget N] [--time-limit S] [-v]

Default VAs: the slice's nonmatching.txt. Our function is compiled (into work/difftest/obj/, never
match/), its relocations are resolved to the ORIGINAL's addresses (tools/difftest/resolve.py), and
both versions run under Unicorn on the same random inputs; every observable (return registers,
callee-saved registers, esp, x87/SSE result, every written byte of .data/heap/input buffers/caller
stack, the import-call trace and the depth-1 call trace) must agree.

Verdicts: PASS (>= K valid inputs, no mismatch, original coverage >= C), WEAK (no mismatch, below a
threshold), FAIL (a mismatch; the first one is printed), UNSUPPORTED (unresolved reference, symbol
not found, compile error, or almost every input discarded). See docs/equivalence.md.
"""
import argparse, glob, json, math, os, random, struct, sys, time, zlib

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import capstone                                    # noqa: E402
try:
    os.nice(10)                                    # yield the CPU to interactive work
except OSError:
    pass
import numpy as np                                 # noqa: E402
from capstone import x86_const as CX               # noqa: E402
from unicorn import UC_HOOK_CODE, UC_HOOK_BLOCK, UC_HOOK_MEM_READ    # noqa: E402
from unicorn.x86_const import *                    # noqa: E402,F401,F403

import slice as S                                  # noqa: E402
import resolve as R                                # noqa: E402
import sig as SIG                                  # noqa: E402
import machine as M                                # noqa: E402
from coff import Coff                              # noqa: E402

DEFAULT_INPUTS = 400
DEFAULT_K = 200
DEFAULT_C = 60.0
DEFAULT_BUDGET = 10_000_000
START_BUDGET = 100_000
BUDGET_PROBES = 3
FAIL_DIR = os.path.join(S.ROOT, "work", "difftest", "fail_inputs")

_md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
_md.detail = True

CS2UC = {}
for _n in ("EAX", "EBX", "ECX", "EDX", "ESI", "EDI", "EBP", "ESP"):
    CS2UC[getattr(CX, "X86_REG_" + _n)] = globals()["UC_X86_REG_" + _n]

_ctx = {}


def context():
    """Image, symbol database, resolver and machine, built once per process."""
    if not _ctx:
        img = R.Image()
        db = R.SymbolDB(img)
        _ctx.update(img=img, db=db, res=R.Resolver(img, db), m=M.Machine(img), arity={}, ecxuse={})
    return _ctx


# ====================================================================== preparation

class Target:
    pass


def unsupported(t, reason, **kw):
    t.verdict = "UNSUPPORTED"
    t.reason = reason
    for k, v in kw.items():
        setattr(t, k, v)
    return t


def prepare(sid, va, flags_override=None, log=print, src=None):
    ctx = context()
    img = ctx["img"]
    t = Target()
    t.sid, t.va = sid, va
    t.verdict = None
    t.unresolved, t.eh_unresolved, t.conflicts, t.methods = [], [], [], {}
    t.flags, t.flags_how = S.choose_flags(sid, va, flags_override)
    src = src or S.source_path(sid)
    t.src = src
    if not os.path.exists(src):
        return unsupported(t, "no source %s" % src)
    t.orig_lo, t.orig_hi = img.func_extent(va)
    obj, clog = S.compile_obj(src, t.flags)
    if obj is None and t.flags_how not in ("override", "default"):
        log("  compile failed with %s flags %s; retrying with defaults" % (t.flags_how, " ".join(t.flags)))
        t.flags, t.flags_how = list(S.DEFAULT_FLAGS), "default(after %s failed)" % t.flags_how
        obj, clog = S.compile_obj(src, t.flags)
    if obj is None:
        return unsupported(t, "compile failed: " + clog.strip().splitlines()[-1][:200] if clog.strip() else "compile failed")
    t.obj = obj
    coff = t.coff = Coff(obj)
    sym, how = S.find_symbol(coff, sid, va, src, t.orig_hi - t.orig_lo)
    if isinstance(sym, list):
        sym, how = best_by_size(coff, sym, t.orig_hi - t.orig_lo), how + " -> closest size"
    if sym is None:
        return unsupported(t, "our symbol not found: " + how)
    t.sym, t.sym_how = sym, how
    fsym = coff.by_name[sym]
    t.fsym = fsym
    annots = R.source_annotations([src] + glob.glob(os.path.join(S.slice_dir(sid), "*.h")))
    res = ctx["res"].resolve(coff, fsym, va, annots)
    t.res = res
    t.unresolved, t.eh_unresolved, t.conflicts = res.unresolved, res.eh_unresolved, res.conflicts
    t.methods = {}
    for nm, h in res.method.items():
        k = h.split("(")[0]
        t.methods[k] = t.methods.get(k, 0) + 1
    if res.unresolved:
        return unsupported(t, "%d unresolved reference(s): %s" % (len(res.unresolved), ", ".join(res.unresolved[:5])))
    # signature / argument layout
    try:
        t.sig = SIG.parse(sym)
    except SIG.SigError as e:
        t.sig = None
        t.sig_error = str(e)
    analyse_original(t)
    build_layout(t)
    return t


def best_by_size(coff, names, n0):
    best = None
    for nm in names:
        _s, a, b = coff.func_extent(coff.by_name[nm])
        d = abs((b - a) - n0)
        if best is None or d < best[0]:
            best = (d, nm)
    return best[1]


def analyse_original(t):
    """Recursive-descent disassembly of the original: instruction set (coverage denominator),
    callee-pop size, ECX/EDX use at entry, immediate dictionary for input generation."""
    img = context()["img"]
    lo, hi = t.orig_lo, t.orig_hi
    code = img.read(lo, hi - lo)
    relset = set(img.reloc_positions(lo, hi - lo))

    def rd(a, n):
        return code[a - lo:a - lo + n]

    def tt(a):
        if a in relset and lo <= a <= hi - 4:
            return struct.unpack_from("<I", code, a - lo)[0]
        return None
    insns, tables = R.recursive_descent(rd, lo, hi, t.va, tt)
    t.orig_insns = insns
    pops = set()
    consts = set()
    for a, ins in insns.items():
        if ins.id == CX.X86_INS_RET:
            pops.add(ins.operands[0].imm if ins.operands else 0)
        for op in ins.operands:
            if op.type == CX.X86_OP_IMM:
                v = op.imm & 0xFFFFFFFF
                if not any(a <= p < a + ins.size for p in relset):
                    consts.add(v)
    t.callee_pop = max(pops) if pops else 0
    t.pop_variants = sorted(pops)
    t.dict = sorted(consts | {(c + 1) & 0xFFFFFFFF for c in consts if c < 0x10000} |
                    {(c - 1) & 0xFFFFFFFF for c in consts if 0 < c < 0x10000})[:4096]
    t.entry_reads = entry_reads(insns, t.va)


def entry_reads(insns, entry):
    """Registers among ecx/edx/eax read before written along the entry path (first 40 insns)."""
    read, written = set(), set()
    a = entry
    names = {CX.X86_REG_ECX: "ecx", CX.X86_REG_CX: "ecx", CX.X86_REG_CL: "ecx", CX.X86_REG_CH: "ecx",
             CX.X86_REG_EDX: "edx", CX.X86_REG_DX: "edx", CX.X86_REG_DL: "edx", CX.X86_REG_DH: "edx",
             CX.X86_REG_EAX: "eax", CX.X86_REG_AX: "eax", CX.X86_REG_AL: "eax", CX.X86_REG_AH: "eax"}
    for _ in range(40):
        ins = insns.get(a)
        if ins is None:
            break
        try:
            r, w = ins.regs_access()
        except capstone.CsError:
            break
        if ins.id == CX.X86_INS_XOR and len(ins.operands) == 2 and ins.operands[0].type == CX.X86_OP_REG \
                and ins.operands[1].type == CX.X86_OP_REG and ins.operands[0].reg == ins.operands[1].reg:
            r = []
        if ins.id == CX.X86_INS_PUSH:
            r = []          # 'push ecx' is MSVC's 4-byte stack allocation / a save, not a use
        for x in r:
            n = names.get(x)
            if n and n not in written:
                read.add(n)
        for x in w:
            n = names.get(x)
            if n:
                written.add(n)
        if ins.group(capstone.CS_GRP_JUMP) or ins.group(capstone.CS_GRP_CALL) or ins.group(capstone.CS_GRP_RET):
            break
        a += ins.size
    return read


def build_layout(t):
    """t.stack_kinds: kind per stack dword; t.reg_kinds: {reg: kind}; t.ret_kind."""
    sg = t.sig
    notes = []
    kinds = []
    regk = {}
    if sg is not None and sg.params is not None:
        conv = sg.conv
        if sg.member:
            regk["ecx"] = "this"
        if sg.ret == "hidden":
            kinds.append("retptr")
        for k, n in sg.params:
            if k == "struct":
                kinds.append(("struct", None))
            elif k in ("void", "varargs"):
                continue
            else:
                kinds.extend([k] * n if k not in ("double", "i64") else [k + "_lo", k + "_hi"])
        if conv == "fastcall":
            # first two dword-sized args go in ecx, edx
            for reg in ("ecx", "edx"):
                for i, k in enumerate(kinds):
                    if isinstance(k, str) and k in ("int", "ptr", "small", "bool", "unknown"):
                        regk[reg] = kinds.pop(i)
                        break
        nstruct = sum(1 for k in kinds if isinstance(k, tuple))
        known = sum(1 for k in kinds if not isinstance(k, tuple))
        pop_dw = t.callee_pop // 4
        if nstruct:
            if t.callee_pop and nstruct == 1 and pop_dw > known:
                each = pop_dw - known
            else:
                each = 3
                notes.append("by-value struct size unknown: assumed 3 dwords")
            out = []
            for k in kinds:
                out.extend(["soup"] * each if isinstance(k, tuple) else [k])
            kinds = out
        if t.callee_pop and len(kinds) != pop_dw and conv in ("stdcall", "thiscall", "fastcall"):
            notes.append("signature gives %d stack dwords, original pops %d" % (len(kinds), pop_dw))
            kinds = (kinds + ["soup"] * pop_dw)[:pop_dw]
        t.ret_kind = sg.ret
        t.conv = conv
    else:
        n = t.callee_pop // 4 if t.callee_pop else 6
        kinds = ["soup"] * n
        t.ret_kind = "unknown"
        t.conv = "stdcall?" if t.callee_pop else "cdecl?"
        notes.append("no parsed signature: %d soup stack dwords" % n)
    t.abi_mismatch = None
    for r in ("ecx", "edx", "eax"):
        if r in t.entry_reads and r not in regk:
            regk[r] = "soup"
            notes.append("original reads %s at entry (register argument?)" % r)
            if sg is not None and sg.params is not None:
                t.abi_mismatch = "original reads %s at entry but our declaration passes nothing there " \
                                 "(custom/LTCG register ABI?)" % r
    t.stack_kinds = kinds
    t.reg_kinds = regk
    t.layout_notes = notes


# ====================================================================== inputs

PROFILES = {
    "mixed":    (("ptr", 30), ("zero", 20), ("small", 15), ("float", 20), ("dict", 5), ("rand", 10)),
    "floaty":   (("ptr", 15), ("zero", 10), ("small", 5), ("float", 65), ("dict", 2), ("rand", 3)),
    "zeroish":  (("ptr", 20), ("zero", 60), ("small", 10), ("float", 5), ("dict", 5)),
    "pointery": (("ptr", 60), ("zero", 20), ("small", 10), ("float", 5), ("dict", 5)),
    "smallint": (("ptr", 20), ("zero", 30), ("small", 40), ("float", 5), ("dict", 5)),
}
SPECIAL_F = [0.0, -0.0, 1.0, -1.0, 0.5, 2.0, 1e-30, 1e30, float("inf"), float("-inf"), float("nan")]


def f2u(x):
    return struct.unpack("<I", struct.pack("<f", x))[0]


class Input:
    """One test input. Input objects live in the lazily materialised pool: the content of every
    4 KB pool page is a pure function of (seed, profile, page) plus `pool_over` edits, so both
    runs see identical bytes wherever they look. Pointers inside generated pages lead to random
    64 KB slots (distinct objects; aliasing only by chance or with --alias). `overrides` are image
    .data dwords set for this input by fault repair. `pagegen` selects the page generator
    (1: the original per-dword Python one, kept so older saved inputs replay identically)."""

    pagegen = 2

    def copy(self):
        n = Input()
        n.seed, n.profile, n.args, n.pad = self.seed, self.profile, list(self.args), list(self.pad)
        n.pool_over, n.regs, n.xmm, n.overrides = dict(self.pool_over), dict(self.regs), list(self.xmm), dict(self.overrides)
        n.origin, n.touched = self.origin, list(self.touched)
        n.pagegen = self.pagegen
        return n


NSLOTS = M.POOL_SIZE // M.SLOT
HOT_SLOTS = 8          # slots 0..7 hold the argument / `this` objects


class InputGen:
    """Random inputs ('pointer soup' objects + typed arguments) and their mutations."""

    def __init__(self, t, alias=0.0, nan=False):
        self.t = t
        self.alias = alias
        self.nan = nan
        self.dic = [self.fin(v) for v in (t.dict or [0])]
        self.specials = SPECIAL_F if nan else SPECIAL_F[:8]
        self.slot_cache = {}

    def fin(self, v):
        """Unless --nan: never produce a dword whose float32 reading is NaN/Inf (clears the top
        exponent bit), since NaN comparisons are not preserved across equivalent spellings."""
        if not self.nan and (v >> 23) & 0xFF == 0xFF:
            return v & 0xFF7FFFFF
        return v

    def slot_ptr(self, rng):
        if self.alias and rng.random() < self.alias:
            slot = rng.randrange(HOT_SLOTS)
        else:
            slot = HOT_SLOTS + rng.randrange(NSLOTS - HOT_SLOTS)
        base = M.POOL_BASE + slot * M.SLOT
        return base if rng.random() < 0.7 else base + 4 * rng.randrange(64)

    def soup(self, rng, profile):
        return self.fin(self._soup(rng, profile))

    def _soup(self, rng, profile):
        kinds, weights = PROFILE_KW[profile]
        k = rng.choices(kinds, weights)[0]
        if k == "ptr":
            return self.slot_ptr(rng)
        if k == "zero":
            return 0
        if k == "small":
            return rng.randrange(9) if rng.random() < 0.9 else 0xFFFFFFFF
        if k == "float":
            r = rng.random()
            if r < 0.6:
                return f2u(rng.uniform(-4, 4))
            if r < 0.85:
                return f2u(rng.uniform(-1000, 1000))
            return f2u(rng.choice(SPECIAL_F[:8]))
        if k == "dict":
            return rng.choice(self.dic)
        return rng.getrandbits(32)

    def slot_pages(self, inp, slot):
        """{page: 4 KB} for the 16 pages of one 64 KB pool slot."""
        pages = range(slot, slot + M.SLOT, 0x1000)
        if inp.pagegen == 1:
            return {p: self.page_v1(inp, p) for p in pages}
        # Fault repair re-runs an input many times with a few pool_over edits: cache the soup.
        key = (inp.seed, inp.profile, slot)
        b = self.slot_cache.get(key)
        if b is None:
            if len(self.slot_cache) >= 512:
                self.slot_cache.clear()
            b = self.slot_cache[key] = self._slot_soup(inp, slot)
        over = [(a, v) for a, v in inp.pool_over.items() if slot <= a < slot + M.SLOT]
        if over:
            b = bytearray(b)
            for a, v in over:
                struct.pack_into("<I", b, a - slot, v)
            b = bytes(b)
        return {pg: b[pg - slot:pg - slot + 0x1000] for pg in pages}

    def _slot_soup(self, inp, slot):
        rng = np.random.default_rng([inp.seed, slot])
        kinds, weights = PROFILE_KW[inp.profile]
        p = np.array(weights, dtype=float)
        n_all = M.SLOT // 4
        k = rng.choice(len(kinds), n_all, p=p / p.sum())
        w = np.zeros(n_all, dtype=np.int64)
        for idx, kind in enumerate(kinds):
            sel = k == idx
            n = int(sel.sum())
            if n and kind != "zero":
                w[sel] = self._soup_n(rng, kind, n)
        w = w.astype(np.uint32)
        if not self.nan:
            w[((w >> 23) & 0xFF) == 0xFF] &= np.uint32(0xFF7FFFFF)
        return w.astype("<u4").tobytes()

    def _soup_n(self, rng, kind, n):
        """n dwords of one soup kind, with the same distributions as _soup."""
        if kind == "ptr":
            hot = rng.integers(0, HOT_SLOTS, n)
            cold = HOT_SLOTS + rng.integers(0, NSLOTS - HOT_SLOTS, n)
            slot = np.where(rng.random(n) < self.alias, hot, cold) if self.alias else cold
            off = np.where(rng.random(n) < 0.7, 0, 4 * rng.integers(0, 64, n))
            return M.POOL_BASE + slot * M.SLOT + off
        if kind == "small":
            return np.where(rng.random(n) < 0.9, rng.integers(0, 9, n), 0xFFFFFFFF)
        if kind == "float":
            r = rng.random(n)
            f = np.where(r < 0.6, rng.uniform(-4, 4, n),
                         np.where(r < 0.85, rng.uniform(-1000, 1000, n), rng.choice(SPECIAL_F[:8], n)))
            return f.astype(np.float32).view(np.uint32).astype(np.int64)
        if kind == "dict":
            return np.array(self.dic, dtype=np.int64)[rng.integers(0, len(self.dic), n)]
        return rng.integers(0, 1 << 32, n, dtype=np.int64)

    def page_v1(self, inp, page):
        rng = random.Random((inp.seed << 32) ^ page)
        words = [self.soup(rng, inp.profile) for _ in range(1024)]
        for a, v in inp.pool_over.items():
            if page <= a < page + 0x1000:
                words[(a - page) // 4] = v
        return struct.pack("<1024I", *words)

    def ptr(self, rng, hot):
        if rng.random() < 0.04:
            return 0
        return M.POOL_BASE + M.SLOT * hot

    def scalar(self, k, rng, profile, hot=1):
        return self.fin(self._scalar(k, rng, profile, hot))

    def _scalar(self, k, rng, profile, hot=1):
        if k in ("this", "ptr", "retptr"):
            return self.ptr(rng, hot)
        if k == "int":
            r = rng.random()
            if r < 0.4:
                return rng.randrange(9)
            if r < 0.65:
                return rng.choice(self.dic)
            if r < 0.7:
                return rng.choice([0xFFFFFFFF, 0x7FFFFFFF, 0x80000000])
            if r < 0.85:
                return rng.randrange(1000)
            return rng.getrandbits(32)
        if k == "small":
            return rng.randrange(256) if rng.random() < 0.7 else rng.choice(self.dic) & 0xFFFF
        if k == "bool":
            return rng.randrange(2)
        if k == "float":
            r = rng.random()
            if r < 0.5:
                return f2u(rng.uniform(-10, 10))
            if r < 0.8:
                return f2u(rng.choice(SPECIAL_F[:6]))
            if r < 0.95:
                return f2u(rng.uniform(-1000, 1000))
            return f2u(rng.choice(self.specials))
        return self.soup(rng, profile)

    def args(self, rng, profile):
        words, pending_hi = [], None
        for i, k in enumerate(self.t.stack_kinds):
            if k in ("double_lo", "i64_lo"):
                if k == "double_lo":
                    x = rng.uniform(-10, 10) if rng.random() < 0.7 else rng.choice(self.specials)
                    lo, hi = struct.unpack("<II", struct.pack("<d", x))
                else:
                    v = rng.choice([rng.randrange(9), rng.getrandbits(64), rng.choice(self.dic)])
                    lo, hi = v & 0xFFFFFFFF, (v >> 32) & 0xFFFFFFFF
                words.append(lo)
                pending_hi = hi
            elif k in ("double_hi", "i64_hi"):
                words.append(pending_hi if pending_hi is not None else 0)
                pending_hi = None
            else:
                words.append(self.scalar(k, rng, profile, hot=2 + i % (HOT_SLOTS - 2)))
        return words

    def fresh(self, rng):
        inp = Input()
        inp.seed = rng.getrandbits(32)
        inp.profile = rng.choice(list(PROFILES))
        inp.origin = "fresh"
        inp.pool_over = {}
        inp.touched = []
        inp.args = self.args(rng, inp.profile)
        inp.pad = [self.soup(rng, inp.profile) for _ in range(4)]
        inp.regs = {}
        for r in ("eax", "ecx", "edx"):
            k = self.t.reg_kinds.get(r)
            hot = {"ecx": 1, "edx": 7, "eax": 6}[r]
            inp.regs[r] = self.scalar(k, rng, inp.profile, hot) if k else self.soup(rng, inp.profile)
        inp.xmm = []
        for _ in range(8):
            v = 0
            for j in range(4):
                v |= f2u(rng.uniform(-10, 10)) << (32 * j)
            inp.xmm.append(v)
        inp.overrides = {}
        return inp

    def mutate(self, parent, rng, corpus):
        """Coverage-guided fuzzing step: 1-4 small edits of a corpus input."""
        inp = parent.copy()
        inp.origin = "mutant"
        kinds = self.t.stack_kinds
        for _ in range(rng.randint(1, 4)):
            op = rng.random()
            if op < 0.35 and inp.args:
                i = rng.randrange(len(inp.args))
                k = kinds[i] if i < len(kinds) else "soup"
                if isinstance(k, str) and k.endswith(("_lo", "_hi")):
                    k = "soup"
                r = rng.random()
                if k in ("int", "small", "soup") and r < 0.4:
                    inp.args[i] = self.fin((inp.args[i] + rng.choice([-1, 1, -2, 2, 8, -8, 16, 100])) & 0xFFFFFFFF)
                elif r < 0.6:
                    inp.args[i] = rng.choice(self.dic)
                else:
                    inp.args[i] = self.scalar(k, rng, inp.profile, hot=2 + i % (HOT_SLOTS - 2))
            elif op < 0.8 and inp.touched:
                page = rng.choice(inp.touched)
                j = page + 4 * rng.randrange(1024)
                for jj in range(j, min(page + 0x1000, j + 4 * rng.choice([1, 1, 2, 4, 16])), 4):
                    r = rng.random()
                    if r < 0.2:
                        inp.pool_over[jj] = rng.choice(self.dic)
                    elif r < 0.3 and jj in inp.pool_over:
                        inp.pool_over[jj] = self.fin((inp.pool_over[jj] + rng.choice([-1, 1, 2, -2, 4])) & 0xFFFFFFFF)
                    else:
                        inp.pool_over[jj] = self.soup(rng, rng.choice(list(PROFILES)))
            elif op < 0.88:
                inp.seed = rng.getrandbits(32)      # same args, new object contents
            elif op < 0.94 and len(corpus) > 1:
                other = rng.choice(corpus)
                inp.pool_over.update(other.pool_over)
            else:
                r = rng.choice(["eax", "ecx", "edx"])
                k = self.t.reg_kinds.get(r)
                if k:
                    inp.regs[r] = self.scalar(k, rng, inp.profile, {"ecx": 1, "edx": 7, "eax": 6}[r])
        return inp


PROFILE_KW = {k: tuple(zip(*v)) for k, v in PROFILES.items()}


# ====================================================================== running

REGS = {"eax": UC_X86_REG_EAX, "ecx": UC_X86_REG_ECX, "edx": UC_X86_REG_EDX}
CALLEE_SENTINEL = {UC_X86_REG_EBX: 0x0BB0BB00, UC_X86_REG_ESI: 0x05150515, UC_X86_REG_EDI: 0x0D1D0D1D,
                   UC_X86_REG_EBP: 0x0E0B0E0B}
STACK_FILL = b"\xcc"


class Side:
    """One installed function (original or ours): entry, ranges, call-site hooks."""

    def __init__(self, name, entry, ranges, sites):
        self.name, self.entry, self.ranges, self.sites = name, entry, ranges, sites

    def inside(self, a):
        return any(lo <= a < hi for lo, hi in self.ranges)


class Runner:
    def __init__(self, t, opts, log=print):
        self.t, self.opts, self.log = t, opts, log
        ctx = context()
        self.img, self.m = ctx["img"], ctx["m"]
        self.arity_cache = ctx["arity"]
        self.ecx_cache = ctx["ecxuse"]
        m = self.m
        self.thunk_targets = {}
        obj = m.load_object(t.coff, t.res, t.fsym)
        self.obj = obj
        self.decl_arity = {}      # callee VA -> stack dwords, from our declaration's mangled name
        self.decl_prefix = {}     # callee VA -> comparable leading stack dwords (before a by-value struct)
        for si, va_ in t.res.addr.items():
            try:
                sg = SIG.parse(t.coff.syms[si].name)
            except Exception:
                continue
            if sg.params is None:
                continue
            n_ = 1 if sg.ret == "hidden" else 0
            for k_, d_ in sg.params:      # dwords before the first by-value struct (its size and
                if k_ == "struct":        # padding bytes are unknown, so it is never compared)
                    break
                n_ += d_
            self.decl_prefix.setdefault(va_, n_)
            if sg.conv == "cdecl" and not sg.variadic and not any(k_ == "struct" for k_, _d in sg.params):
                self.decl_arity.setdefault(va_, n_)
        self.our_insns = {}
        self.code_cache = {}      # image function start -> (sorted addrs, insns) for fake-call arity
        self.fakes = []
        self.orig = Side("orig", t.va, [(t.orig_lo, t.orig_hi)], self._sites_orig())
        self.ours = Side("ours", obj["entry"], obj["code"], self._sites_ours())
        self.hooks = []
        self.cur = None
        self.calls = []
        # Original's instruction cap: starts low (random inputs often send a loop into the
        # billions) and rises to --budget if a probe shows a real input needs more; see run_function.
        self.budget = min(getattr(opts, "start_budget", opts.budget), opts.budget)
        for side in (self.orig, self.ours):
            for a, info in side.sites.items():
                self.hooks.append(m.uc.hook_add(UC_HOOK_CODE, self._on_site, user_data=(side, info), begin=a, end=a))
        self.blocks = set()
        self.run_blocks = set()
        self.page_cache = {}
        self.gen = InputGen(t, opts.alias, opts.nan)
        self.cov_on = False
        self.reads = None
        self.hooks.append(m.uc.hook_add(UC_HOOK_BLOCK, self._on_block, begin=t.orig_lo, end=t.orig_hi - 1))
        nst = len(t.stack_kinds) + 4
        self.frame_dw = nst
        self.esp_entry = M.STACK_TOP - 0x2000 - 4 * (1 + nst)
        self.esp_entry &= ~0xF
        self.esp_entry -= 4         # as after a call from 16-aligned code
        self.args_hi = self.esp_entry + 4 * (1 + nst)

    def close(self):
        for h in self.hooks:
            self.m.uc.hook_del(h)
        self.hooks = []

    # --- static site discovery
    def _site_info(self, ins, read_next):
        nxt = read_next(ins.address + ins.size, 6)
        add = 0
        if nxt[:2] == b"\x83\xc4":
            add = nxt[2] // 4
        elif nxt[:2] == b"\x81\xc4":
            add = struct.unpack_from("<I", nxt, 2)[0] // 4
        return {"ins": ins, "add_esp": add, "is_jmp": ins.id == CX.X86_INS_JMP}

    def _sites_orig(self):
        t = self.t
        sites = {}
        for a, ins in t.orig_insns.items():
            if ins.id == CX.X86_INS_CALL or (ins.id == CX.X86_INS_JMP and not self._jmp_internal(ins, t.orig_lo, t.orig_hi)):
                sites[a] = self._site_info(ins, self.img.read)
        return sites

    def _jmp_internal(self, ins, lo, hi):
        op = ins.operands[0]
        if op.type == CX.X86_OP_IMM:
            return lo <= (op.imm & 0xFFFFFFFF) < hi
        if op.type == CX.X86_OP_MEM and op.mem.index != 0:
            return True        # jump table
        return False

    def _sites_ours(self):
        m, obj, coff = self.m, self.obj, self.t.coff
        sites = {}
        for i, a0 in obj["sec_addr"].items():
            sec = coff.sections[i]
            if not sec.is_code:
                continue
            lo, hi = a0, a0 + len(sec.data)
            relpos = {a0 + off for off, _si, typ in sec.relocs if typ in (0x06,)}

            def rd(a, n, lo=lo, hi=hi):
                return m.read(a, min(n, hi - a))

            def tt(a, relpos=relpos, lo=lo, hi=hi):
                if a in relpos:
                    v = m.u32(a)
                    return v if lo <= v < hi else None
                return None
            starts = [a0 + s.value for s in coff.syms.values() if s.secno - 1 == i and s.is_func]
            for st in starts or [a0]:
                insns, _tb = R.recursive_descent(rd, lo, hi, st, tt)
                self.our_insns.update(insns)
                for a, ins in insns.items():
                    if ins.id == CX.X86_INS_CALL or (ins.id == CX.X86_INS_JMP and not self._jmp_internal(ins, lo, hi)):
                        sites[a] = self._site_info(ins, m.read)
        return sites

    # --- hooks
    def _on_block(self, uc, address, size, _):
        if self.cov_on:
            self.run_blocks.add((address, size))

    def _eval_target(self, ins):
        uc = self.m.uc
        op = ins.operands[0]
        if op.type == CX.X86_OP_IMM:
            return op.imm & 0xFFFFFFFF
        if op.type == CX.X86_OP_REG:
            return uc.reg_read(CS2UC[op.reg])
        if op.type == CX.X86_OP_MEM:
            mm = op.mem
            a = mm.disp
            if mm.base:
                a += uc.reg_read(CS2UC[mm.base])
            if mm.index:
                a += uc.reg_read(CS2UC[mm.index]) * mm.scale
            if mm.segment:
                return None
            try:
                return self.m.u32(a & 0xFFFFFFFF)
            except Exception:
                return None
        return None

    def _on_site(self, uc, address, size, data):
        side, info = data
        if side is not self.cur:
            return
        tgt = self._eval_target(info["ins"])
        if tgt is None:
            return
        if side.inside(tgt) or M.STUB_BASE <= tgt < self.m.stub_end:
            return
        if self._thunk(tgt):
            return
        esp = uc.reg_read(UC_X86_REG_ESP)
        try:
            words = struct.unpack("<8I", self.m.read(esp, 32))
        except Exception:
            words = (0,) * 8
        self.calls.append((tgt, uc.reg_read(UC_X86_REG_ECX), uc.reg_read(UC_X86_REG_EDX), words,
                           info["add_esp"], info["is_jmp"]))

    def _thunk(self, va):
        r = self.thunk_targets.get(va)
        if r is None:
            r = False
            if self.img.in_text(va):
                b = self.img.read(va, 2)
                r = b == b"\xff\x25"
            self.thunk_targets[va] = r
        return r

    # --- callee facts for call-trace normalisation
    def callee_arity(self, va):
        """Dwords the callee pops (ret N), or None for cdecl/unknown."""
        if va in self.arity_cache:
            return self.arity_cache[va]
        n = None
        if self.img.in_text(va):
            lo, hi = self.img.func_extent(va)
            if lo == va:
                code = self.img.read(lo, hi - lo)

                def rd(a, k):
                    return code[a - lo:a - lo + k]
                insns, _ = R.recursive_descent(rd, lo, hi, va, lambda a: None)
                pops = {ins.operands[0].imm if ins.operands else 0 for ins in insns.values() if ins.id == CX.X86_INS_RET}
                if pops and max(pops):
                    n = max(pops) // 4
        self.arity_cache[va] = n
        return n

    def callee_regs(self, va):
        if va in self.ecx_cache:
            return self.ecx_cache[va]
        r = set()
        if self.img.in_text(va):
            lo, hi = self.img.func_extent(va)
            if lo == va:
                code = self.img.read(lo, min(hi - lo, 400))
                insns = {}
                for ins in _md.disasm(code, lo):
                    insns[ins.address] = ins
                r = entry_reads(insns, va)
        self.ecx_cache[va] = r
        return r

    def abi_ok(self, o):
        """Callee-saved registers back at their sentinels and esp popped exactly the declared args."""
        if any(o[nm] != CALLEE_SENTINEL[r] for nm, r in M.CALLEE_SAVED):
            return False
        return o["esp"] == 4 + self.t.callee_pop

    # --- calls through generated function pointers ("fake methods")
    def _insns_around(self, site):
        """(sorted addresses, insns) of the code containing site."""
        if self.t.orig_lo <= site < self.t.orig_hi:
            key = "orig"
            if key not in self.code_cache:
                self.code_cache[key] = (sorted(self.t.orig_insns), self.t.orig_insns)
            return self.code_cache[key]
        if any(lo <= site < hi for lo, hi in self.obj["code"]):
            if "ours" not in self.code_cache:
                self.code_cache["ours"] = (sorted(self.our_insns), self.our_insns)
            return self.code_cache["ours"]
        if self.img.in_text(site):
            import bisect
            st = self.img.starts
            i = bisect.bisect_right(st, site) - 1
            if i < 0:
                return None
            f = st[i]
            if f not in self.code_cache:
                lo, hi = self.img.func_extent(f)
                code = self.img.read(lo, max(hi - lo, 1))
                rel = set(self.img.reloc_positions(lo, hi - lo))

                def rd(a, n, lo=lo, code=code):
                    return code[a - lo:a - lo + n]

                def tt(a, lo=lo, hi=hi, code=code, rel=rel):
                    return struct.unpack_from("<I", code, a - lo)[0] if a in rel and lo <= a <= hi - 4 else None
                insns, _ = R.recursive_descent(rd, lo, hi, f, tt)
                self.code_cache[f] = (sorted(insns), insns)
            return self.code_cache[f]
        return None

    def site_arity(self, ret):
        """Stack dwords a call ending at `ret` passes: pushes (and 'sub esp,N' slots) walking back
        from the call to the previous call/branch/stack adjustment. None if not determinable."""
        got = self._insns_around(ret - 1)
        if not got:
            return None
        addrs, insns = got
        import bisect
        i = bisect.bisect_left(addrs, ret) - 1
        if i < 0:
            return None
        call = insns[addrs[i]]
        if call.id != CX.X86_INS_CALL or call.address + call.size != ret:
            return None
        n = 0
        j = i - 1
        while j >= 0 and i - j < 40:
            ins = insns[addrs[j]]
            if ins.address + ins.size != addrs[j + 1]:
                break                       # gap: not a straight-line predecessor
            if ins.id == CX.X86_INS_PUSH:
                n += 1
            elif ins.id == CX.X86_INS_SUB and ins.operands[0].type == CX.X86_OP_REG and \
                    ins.operands[0].reg == CX.X86_REG_ESP and ins.operands[1].type == CX.X86_OP_IMM:
                if ins.operands[1].imm > 0x40:
                    break
                n += ins.operands[1].imm // 4
            elif ins.id in (CX.X86_INS_CALL, CX.X86_INS_RET, CX.X86_INS_POP, CX.X86_INS_ADD) or \
                    ins.group(capstone.CS_GRP_JUMP):
                if ins.id == CX.X86_INS_ADD and not (ins.operands[0].type == CX.X86_OP_REG and
                                                     ins.operands[0].reg == CX.X86_REG_ESP):
                    j -= 1
                    continue
                break
            else:
                try:
                    _r, w = ins.regs_access()
                except capstone.CsError:
                    w = []
                if CX.X86_REG_ESP in w and ins.id not in (CX.X86_INS_MOV,):
                    break
            j -= 1
        nxt = self.m.read(ret, 3)
        callee_pops = not (nxt[:2] == b"\x83\xc4" or nxt[:2] == b"\x81\xc4")
        return n, callee_pops

    def fake_call(self, target):
        m, uc = self.m, self.m.uc
        esp = uc.reg_read(UC_X86_REG_ESP)
        try:
            ret = m.u32(esp)
        except Exception:
            return None
        if self.img.in_text(target) or M.STUB_BASE <= target < m.stub_end:
            return None
        ar = self.site_arity(ret)
        if ar is None:
            return ("fake-arity", "no call site before %08x" % ret)
        n, pops = ar
        args = []
        for k in range(n):
            v = m.u32(esp + 4 + 4 * k)
            args.append("STK" if in_stack_frame(v, self.esp_entry) else v)
        ecx = uc.reg_read(UC_X86_REG_ECX)
        ecx = "STK" if in_stack_frame(ecx, self.esp_entry) else ecx
        h = zlib.crc32(repr((target, ecx, args)).encode())
        k = h % 4
        eax = (0, 1, h % 9, M.POOL_BASE + M.SLOT * (HOT_SLOTS + (h >> 8) % (NSLOTS - HOT_SLOTS)))[k]
        self.fakes.append((target, n))
        uc.reg_write(UC_X86_REG_EAX, eax)
        uc.reg_write(UC_X86_REG_EDX, 0)
        new_esp = esp + 4 + (4 * n if pops else 0)
        if self._returns_x87(ret):
            # the caller consumes st0 right after the call: return a float on the x87 stack
            m.write(M.SCRATCH + 8, struct.pack("<f", (0.0, 1.0, 0.5, float(h % 9))[(h >> 4) % 4]))
            m.write(new_esp - 4, struct.pack("<I", ret))
            uc.reg_write(UC_X86_REG_ESP, new_esp - 4)
            uc.reg_write(UC_X86_REG_EIP, M.FLD_RET_STUB)
            return True
        uc.reg_write(UC_X86_REG_ESP, new_esp)
        uc.reg_write(UC_X86_REG_EIP, ret)
        return True

    def _returns_x87(self, ret):
        """True if the code after the call reads an x87 register it did not push itself, i.e. it
        uses a float returned in st0 (the x87 stack is empty at every call in MSVC code)."""
        try:
            code = self.m.read(ret, 96)
        except Exception:
            return False
        depth = 0
        n = 0
        for ins in _md.disasm(code, ret):
            n += 1
            if n > 24 or ins.group(capstone.CS_GRP_JUMP) or ins.group(capstone.CS_GRP_CALL) or \
                    ins.group(capstone.CS_GRP_RET):
                return False
            mn = ins.mnemonic
            if not mn.startswith("f") or mn in ("fnstcw", "fldcw", "fnstsw", "fstsw", "fwait", "fnclex", "fninit"):
                continue
            sti = [op.reg - CX.X86_REG_ST0 for op in ins.operands
                   if op.type == CX.X86_OP_REG and CX.X86_REG_ST0 <= op.reg <= CX.X86_REG_ST7]
            hi = max(sti) if sti else 0
            if mn.startswith(("fld", "fild")) and mn not in ("fldcw", "fldenv"):
                need, delta = (hi + 1 if sti else 0), 1
            elif mn in ("fcompp", "fucompp"):
                need, delta = 2, -2
            elif mn.endswith("p") or mn in ("fstp", "fistp", "fisttp", "fbstp"):
                need, delta = max(hi + 1, 1), -1
            else:
                need, delta = max(hi + 1, 1), 0
            if need > depth:
                return True
            depth += delta
            if depth < 0:
                return True
        return False

    # --- fault repair
    def _on_read(self, uc, access, address, size, value, _):
        if size == 4:
            try:
                self.reads.append((address, self.m.u32(address)))
            except Exception:
                pass

    def repair(self, inp, fault, rng):
        """The original faulted at an unmapped address A. Find the dword the bad pointer V came from
        (the last 4-byte read from the input buffers, image .data or the argument area with
        0 <= A - V < 64K; else an argument/register holding such a V) and make it point into a
        fresh input buffer. Returns the repaired input or None."""
        kind, A, _sz = fault
        if kind not in ("read", "write", "read-prot", "write-prot"):
            return None
        m = self.m
        fault_eip = m.uc.reg_read(UC_X86_REG_EIP)
        fault_regs = {cs: m.uc.reg_read(u) for cs, u in CS2UC.items()}
        self.reads = []
        ranges = [(M.POOL_BASE, M.POOL_BASE + M.POOL_SIZE), (self.esp_entry, self.args_hi)]
        ranges += [(lo, hi) for _nm, lo, hi in m.writable]
        hs = [m.uc.hook_add(UC_HOOK_MEM_READ, self._on_read, begin=lo, end=hi - 1) for lo, hi in ranges]
        try:
            self.run_side(self.orig, inp)
        finally:
            for h in hs:
                m.uc.hook_del(h)
        reads, self.reads = self.reads, None

        # The faulting instruction's base register is the bad pointer V (exactly, if it was
        # loaded unchanged); otherwise fall back to "some value up to 64K below A".
        base_v = None
        try:
            eip = fault_eip
            ins = next(_md.disasm(m.read(eip, 16), eip, 1))
            for op in ins.operands:
                if op.type == CX.X86_OP_MEM and op.mem.base and op.mem.base in CS2UC:
                    base_v = fault_regs.get(op.mem.base)
                    break
        except Exception:
            base_v = None

        def near(v):
            if base_v is not None:
                return v == base_v
            return 0 <= (A - v) & 0xFFFFFFFF < 0x10000
        newp = M.POOL_BASE + M.SLOT * (HOT_SLOTS + rng.randrange(NSLOTS - HOT_SLOTS))
        out = inp.copy()
        for addr, v in reversed(reads):
            if not near(v):
                continue
            if M.POOL_BASE <= addr < M.POOL_BASE + M.POOL_SIZE:
                if addr & 3:
                    return None
                out.pool_over[addr] = newp
            elif self.esp_entry + 4 <= addr < self.args_hi:
                k = (addr - self.esp_entry - 4) // 4
                if addr & 3:
                    return None
                if k < len(out.args):
                    out.args[k] = newp
                else:
                    out.pad[k - len(out.args)] = newp
            else:
                out.overrides[addr] = newp
            return out
        for k, v in enumerate(out.args):
            if near(v):
                out.args[k] = newp
                return out
        for r, v in out.regs.items():
            if near(v):
                out.regs[r] = newp
                return out
        return None

    # --- one run
    def run_side(self, side, inp):
        m, uc, t = self.m, self.m.uc, self.t
        # memory: pool, dyn heap, stack, misc
        cache = self.page_cache
        if cache.get("inp") is not inp:
            cache.clear()
            cache["inp"] = inp

        def lazy(page, inp=inp, cache=cache):
            d = cache.get(page)
            if d is None:
                cache.update(self.gen.slot_pages(inp, page & ~(M.SLOT - 1)))
                d = cache[page]
            return d
        m.lazy = lazy
        m.pool_pages = {}
        m.pool_slots = []
        m.pool_entry = set()
        for a_, v_ in inp.overrides.items():
            m.write(a_, struct.pack("<I", v_))
        m.dyn_next = M.DYN_BASE
        m.dyn_sizes = {}
        m.rand_state = 1
        stk_lo = M.STACK_TOP - M.STACK_SIZE
        m.write(stk_lo, STACK_FILL * (M.STACK_TOP - stk_lo))
        m.write(M.MISC_BASE, m.misc_baseline)
        frame = struct.pack("<I", M.SENTINEL) + struct.pack("<%dI" % (len(inp.args) + 4), *(inp.args + inp.pad))
        m.write(self.esp_entry, frame)
        regs = dict(CALLEE_SENTINEL)
        for r, v in inp.regs.items():
            regs[REGS[r]] = v
        m.reset_cpu(regs, inp.xmm)
        uc.reg_write(UC_X86_REG_ESP, self.esp_entry)
        m.trace_imports = []
        m.fake_handler = (getattr(self, "fake_override", None) or self.fake_call) if self.opts.fake_calls else None
        self.fakes = []
        self.calls = []
        self.cur = side
        self.cov_on = side is self.orig
        self.run_blocks = set()
        budget = self.budget if side is self.orig else self.opts.budget * 4
        t0 = time.time()
        status = m.run(side.entry, None, budget, self.opts.run_seconds * (1 if side is self.orig else 4))
        self.cur = None
        self.cov_on = False
        o = {"status": status, "time": time.time() - t0, "fault": m.last_fault}
        o["eax"] = uc.reg_read(UC_X86_REG_EAX)
        o["edx"] = uc.reg_read(UC_X86_REG_EDX)
        for nm, r in M.CALLEE_SAVED:
            o[nm] = uc.reg_read(r)
        o["esp"] = (uc.reg_read(UC_X86_REG_ESP) - self.esp_entry) & 0xFFFFFFFF
        fpsw = uc.reg_read(UC_X86_REG_FPSW)
        top = (fpsw >> 11) & 7
        o["fpu_depth"] = (8 - top) % 8
        o["st0"] = uc.reg_read(UC_X86_REG_FP0 + top) if o["fpu_depth"] else None
        o["fpcw"] = uc.reg_read(UC_X86_REG_FPCW) & 0x1F3F
        o["mxcsr"] = uc.reg_read(UC_X86_REG_MXCSR) & 0xFFC0
        o["xmm0"] = uc.reg_read(UC_X86_REG_XMM0)
        # memory after the run (and undo it)
        mem = {}
        for nm, lo, hi in m.writable:
            base = m.image_baseline[nm]
            cur = m.read(lo, hi - lo)
            if cur != base:
                pages = {}
                for p in range(0, hi - lo, 0x1000):
                    if cur[p:p + 0x1000] != base[p:p + 0x1000]:
                        pages[lo + p] = cur[p:p + 0x1000]
                        m.write(lo + p, base[p:p + 0x1000])
                mem[nm] = pages
        o["pool_init"] = init = dict(m.pool_pages)
        entry = m.pool_entry
        mem["pool"] = m.unmap_pool()
        if side is self.orig:
            # pages to mutate: where each object was first accessed, plus every page written
            inp.touched = sorted(entry | {p for p, d in mem["pool"].items() if d != init[p]})
        o["dyn_hi"] = m.dyn_next
        mem["heap"] = m.read(M.DYN_BASE, m.dyn_next - M.DYN_BASE) if m.dyn_next > M.DYN_BASE else b""
        if m.dyn_next > M.DYN_BASE:
            m.write(M.DYN_BASE, b"\0" * (m.dyn_next - M.DYN_BASE))
        mem["stack"] = m.read(self.args_hi, M.STACK_TOP - self.args_hi)
        misc = bytearray(m.read(M.MISC_BASE, len(m.misc_baseline)))
        misc[M.SCRATCH - M.MISC_BASE:M.SCRATCH - M.MISC_BASE + 16] = b"\0" * 16   # harness scratch
        mem["misc"] = bytes(misc)
        for (lo, hi), base in zip(self.obj["data_rw"], self.obj["rw_baseline"]):
            cur = m.read(lo, hi - lo)
            mem["ours_data"] = cur
            if cur != base:
                m.write(lo, base)
        o["mem"] = mem
        o["imports"] = list(m.trace_imports)
        o["fakes"] = list(self.fakes)
        o["calls"] = list(self.calls)
        return o


# ====================================================================== comparison

def in_stack_frame(v, esp_entry):
    return M.STACK_TOP - M.STACK_SIZE <= v < esp_entry


def norm_val(v, esp_entry):
    return "STK" if in_stack_frame(v, esp_entry) else v


def ulp_close(a, b, ulp, bits=32):
    if bits == 32:
        fa, fb = struct.unpack("<f", struct.pack("<I", a))[0], struct.unpack("<f", struct.pack("<I", b))[0]
        ia, ib = a, b
    else:
        fa, fb = a, b
        ia, ib = a, b
    if math.isnan(fa) or math.isnan(fb):
        return math.isnan(fa) and math.isnan(fb)
    def key(i, bits):
        sign = 1 << (bits - 1)
        return (sign - (i & (sign - 1))) if i & sign else (i + sign)
    return abs(key(ia, bits) - key(ib, bits)) <= ulp


class Comparer:
    def __init__(self, runner, opts):
        self.r, self.opts = runner, opts
        self.tolerated = {"stack-pointer": 0, "inline-calls": 0, "ulp": 0, "const-pointer": 0}
        img = context()["img"]
        self.ro = [(a, a + n) for nm, a, n, ch in img.sections if nm == ".rdata"]
        obj = runner.obj
        if obj["map_hi"] > obj["map_lo"]:
            self.ro.append((obj["map_lo"], obj["map_hi"]))

    def same_constant(self, x, y):
        """Two different pointers into read-only data whose 64 bytes (or C strings) are identical:
        the same literal/constant pooled at different addresses."""
        if x == y or not any(lo <= x < hi for lo, hi in self.ro) or not any(lo <= y < hi for lo, hi in self.ro):
            return False
        m = self.r.m
        try:
            bx, by = m.read(x, 64), m.read(y, 64)
        except Exception:
            return False
        if bx == by:
            return True
        for wide in (False, True):
            step = 2 if wide else 1
            z = b"\0" * step
            ex = next((i for i in range(0, 64, step) if bx[i:i + step] == z), None)
            ey = next((i for i in range(0, 64, step) if by[i:i + step] == z), None)
            if ex is not None and ex == ey and ex > 0 and bx[:ex] == by[:ey]:
                return True
        return False

    def compare(self, a, b, t):
        """-> None if equivalent, else (observable, orig, ours, detail). self.last_kind: triage hint."""
        self.last_kind = None
        rk = t.ret_kind
        if rk in ("int", "ptr", "hidden", "unknown", "small", "bool", "i64"):
            mask = {"bool": 0xFF, "small": 0xFFFF}.get(rk, 0xFFFFFFFF)
            if rk == "small":
                mask = 0xFFFF
            ea, eb = a["eax"] & mask, b["eax"] & mask
            if ea != eb and not (in_stack_frame(ea, self.r.esp_entry) and in_stack_frame(eb, self.r.esp_entry)):
                return ("eax" if mask == 0xFFFFFFFF else "eax&%#x" % mask, "%08x" % ea, "%08x" % eb, "return value")
            if rk == "i64" and a["edx"] != b["edx"]:
                return ("edx", "%08x" % a["edx"], "%08x" % b["edx"], "64-bit return high half")
        for nm, _r in M.CALLEE_SAVED:
            if a[nm] != b[nm]:
                return (nm, "%08x" % a[nm], "%08x" % b[nm], "callee-saved register not preserved identically")
        if a["esp"] != b["esp"]:
            return ("esp", "+%#x" % a["esp"], "+%#x" % b["esp"], "esp after return (relative to entry)")
        if a["fpu_depth"] != b["fpu_depth"]:
            return ("x87 depth", a["fpu_depth"], b["fpu_depth"], "values left on the x87 stack")
        if a["fpu_depth"] and a["st0"] != b["st0"]:
            ok = False
            if self.opts.ulp:
                fa, fb = x87_to_float(a["st0"]), x87_to_float(b["st0"])
                ia = struct.unpack("<Q", struct.pack("<d", fa))[0]
                ib = struct.unpack("<Q", struct.pack("<d", fb))[0]
                ok = ulp_close(ia, ib, self.opts.ulp, 64)
                if ok:
                    self.tolerated["ulp"] += 1
            if not ok:
                return ("st0", fmt_x87(a["st0"]), fmt_x87(b["st0"]), "x87 result")
        if a["fpcw"] != b["fpcw"]:
            return ("fpcw", "%04x" % a["fpcw"], "%04x" % b["fpcw"], "x87 control word")
        if a["mxcsr"] != b["mxcsr"]:
            return ("mxcsr", "%08x" % a["mxcsr"], "%08x" % b["mxcsr"], "SSE control")
        if rk == "m128" and a["xmm0"] != b["xmm0"]:
            return ("xmm0", "%032x" % a["xmm0"], "%032x" % b["xmm0"], "SSE return")
        d = self.compare_mem(a, b)
        if d:
            return d
        d = self.compare_imports(a["imports"], b["imports"])
        if d:
            return d
        return self.compare_calls(a["calls"], b["calls"])

    def compare_mem(self, a, b):
        ma, mb = a["mem"], b["mem"]
        esp = self.r.esp_entry
        for region in sorted(set(ma) | set(mb)):
            if region == "ours_data":
                continue
            xa, xb = ma.get(region), mb.get(region)
            if region == "pool":
                for page in sorted(set(xa) | set(xb)):
                    pa = xa.get(page) or a["pool_init"].get(page) or b["pool_init"].get(page)
                    pb = xb.get(page) or b["pool_init"].get(page) or a["pool_init"].get(page)
                    d = self.diff_bytes(pa, pb, page, region, esp)
                    if d:
                        return d
                continue
            if isinstance(xa, dict) or isinstance(xb, dict):
                xa, xb = xa or {}, xb or {}
                base = self.r.m.image_baseline
                lo = dict((nm, l) for nm, l, h in self.r.m.writable)[region]
                for page in sorted(set(xa) | set(xb)):
                    pa = xa.get(page) or base[region][page - lo:page - lo + 0x1000]
                    pb = xb.get(page) or base[region][page - lo:page - lo + 0x1000]
                    d = self.diff_bytes(pa, pb, page, region, esp)
                    if d:
                        return d
                continue
            if xa == xb:
                continue
            if region == "heap":
                n = max(len(xa), len(xb))
                xa, xb = xa.ljust(n, b"\0"), xb.ljust(n, b"\0")
                if a["dyn_hi"] != b["dyn_hi"]:
                    return ("heap size", "%#x" % (a["dyn_hi"] - M.DYN_BASE), "%#x" % (b["dyn_hi"] - M.DYN_BASE),
                            "bytes allocated through malloc-like imports")
            base_addr = {"heap": M.DYN_BASE, "stack": self.r.args_hi, "misc": M.MISC_BASE}[region]
            d = self.diff_bytes(xa, xb, base_addr, region, esp)
            if d:
                return d
        od = mb.get("ours_data")
        if od is not None:
            for (lo, hi), base in zip(self.r.obj["data_rw"], self.r.obj["rw_baseline"]):
                if od != base:
                    i = next(k for k in range(len(od)) if od[k] != base[k])
                    return ("ours-private data", "-", "%08x" % (lo + i),
                            "OUR code wrote its own static data (a global the original keeps elsewhere)")
        return None

    def diff_bytes(self, xa, xb, base_addr, region, esp):
        if xa == xb:
            return None
        n = min(len(xa), len(xb))
        i = 0
        while i < n:
            # skip identical 256-byte chunks quickly
            if xa[i:i + 256] == xb[i:i + 256]:
                i += 256
                continue
            j = i
            while j < min(i + 256, n) and xa[j] == xb[j]:
                j += 1
            if j >= n:
                break
            if j >= i + 256:
                i += 256
                continue
            k = j & ~3
            va = struct.unpack_from("<I", xa, k)[0] if k + 4 <= n else None
            vb = struct.unpack_from("<I", xb, k)[0] if k + 4 <= n else None
            if va is not None and in_stack_frame(va, esp) and in_stack_frame(vb, esp):
                self.tolerated["stack-pointer"] += 1
                i = k + 4
                continue
            if va is not None and self.same_constant(va, vb):
                self.tolerated["const-pointer"] += 1
                i = k + 4
                continue
            if va is not None and self.opts.ulp and ulp_close(va, vb, self.opts.ulp):
                self.tolerated["ulp"] += 1
                i = k + 4
                continue
            more, pairs = [], []
            for q in range(k, n - 3, 4):
                x, y = struct.unpack_from("<I", xa, q)[0], struct.unpack_from("<I", xb, q)[0]
                if x != y and not (in_stack_frame(x, esp) and in_stack_frame(y, esp)):
                    pairs.append((x, y))
                    if len(more) < 8:
                        more.append("%08x: %08x/%08x" % (base_addr + q, x, y))
                    if len(pairs) >= 64:
                        break
            self.last_kind = classify_pairs(pairs)
            ol, oh = self.r.obj["map_lo"], self.r.obj["map_hi"]
            if pairs and (ol <= pairs[0][1] < oh) and not (ol <= pairs[0][0] < oh) and \
                    context()["img"].in_image(pairs[0][0]):
                self.last_kind = "local-address"
            ulps = ""
            if va is not None and vb is not None:
                fa = struct.unpack("<f", struct.pack("<I", va))[0]
                fb = struct.unpack("<f", struct.pack("<I", vb))[0]
                if math.isfinite(fa) and math.isfinite(fb):
                    def key(i):
                        return (0x80000000 - (i & 0x7FFFFFFF)) if i & 0x80000000 else (i + 0x80000000)
                    dist = abs(key(va) - key(vb))
                    if dist < 1 << 16:
                        ulps = " [as float32: %r vs %r, %d ulp apart]" % (fa, fb, dist)
            return ("memory %s @%08x" % (region, base_addr + k),
                    "%08x" % va if va is not None else xa[k:k + 4].hex(),
                    "%08x" % vb if vb is not None else xb[k:k + 4].hex(),
                    "differing dwords (addr: orig/ours): " + ", ".join(more) + ulps)
        if len(xa) != len(xb):
            return ("memory %s" % region, "len %d" % len(xa), "len %d" % len(xb), "")
        return None

    def compare_imports(self, ia, ib):
        esp = self.r.esp_entry
        na = [(n, tuple(norm_val(v, esp) for v in args)) for n, args in ia]
        nb = [(n, tuple(norm_val(v, esp) for v in args)) for n, args in ib]
        if na == nb:
            return None
        for k in range(max(len(na), len(nb))):
            x = na[k] if k < len(na) else None
            y = nb[k] if k < len(nb) else None
            if x != y:
                return ("import call #%d" % k, fmt_call(x), fmt_call(y), "imports called (any depth), args normalised")
        return None

    def norm_calls(self, calls):
        out = []
        esp = self.r.esp_entry
        for tgt, ecx, edx, words, add_esp, is_jmp in calls:
            n = self.r.callee_arity(tgt)
            if n is None:
                n = self.r.decl_arity.get(tgt)
            if n is None:
                n = add_esp
            if tgt in self.r.decl_prefix:
                n = min(n, self.r.decl_prefix[tgt])
            regs = self.r.callee_regs(tgt)
            ent = [tgt, norm_val(ecx, esp) if "ecx" in regs else "-", norm_val(edx, esp) if "edx" in regs else "-"]
            out.append((ent, [norm_val(w, esp) for w in words[:n]] if n else []))
        return out

    def compare_calls(self, ca, cb):
        A, B = self.norm_calls(ca), self.norm_calls(cb)

        def same(x, y):
            if x[0] != y[0]:
                return False
            n = min(len(x[1]), len(y[1]))
            return x[1][:n] == y[1][:n]

        def first_diff(A, B):
            for k in range(max(len(A), len(B))):
                x = A[k] if k < len(A) else None
                y = B[k] if k < len(B) else None
                if x is None or y is None or not same(x, y):
                    return k, x, y
            return None
        d = first_diff(A, B)
        if d is None:
            return None
        if not self.opts.strict_calls:
            ta, tb = {x[0][0] for x in A}, {x[0][0] for x in B}
            A2 = [x for x in A if x[0][0] in tb]
            B2 = [x for x in B if x[0][0] in ta]
            if first_diff(A2, B2) is None:
                self.tolerated["inline-calls"] += 1
                return None
            d = first_diff(A2, B2)
        k, x, y = d
        return ("call #%d (depth 1)" % k, fmt_tcall(x), fmt_tcall(y), "callee, this/edx and stack args (normalised)")


def classify_pairs(pairs):
    """Triage hint for differing dwords: float-rounding (all close finite floats), float-special
    (a NaN/Inf on one side), or value."""
    if not pairs:
        return None
    kinds = set()
    for x, y in pairs:
        fx, fy = struct.unpack("<f", struct.pack("<I", x))[0], struct.unpack("<f", struct.pack("<I", y))[0]
        if not math.isfinite(fx) or not math.isfinite(fy):
            kinds.add("float-special")
            continue
        kx = (0x80000000 - (x & 0x7FFFFFFF)) if x & 0x80000000 else (x + 0x80000000)
        ky = (0x80000000 - (y & 0x7FFFFFFF)) if y & 0x80000000 else (y + 0x80000000)
        kinds.add("float-rounding" if abs(kx - ky) <= 1024 else "value")
    if "value" in kinds:
        return "value"
    return "float-special" if "float-special" in kinds else "float-rounding"


def x87_to_float(v):
    if v is None:
        return None
    mant, exp = v
    sign = -1.0 if exp & 0x8000 else 1.0
    e = exp & 0x7FFF
    if e == 0x7FFF:
        return float("nan") if mant & 0x7FFFFFFFFFFFFFFF else sign * float("inf")
    if e == 0 and mant == 0:
        return sign * 0.0
    try:
        return sign * math.ldexp(mant, e - 16383 - 63)
    except OverflowError:
        return sign * float("inf")


def fmt_x87(v):
    return "%s (%04x:%016x)" % (repr(x87_to_float(v)), v[1], v[0]) if v else "-"


def fmt_call(x):
    if x is None:
        return "(none)"
    n, args = x
    return "%s(%s)" % (n, ", ".join(a if isinstance(a, str) else "%#x" % a for a in args))


def fmt_tcall(x):
    if x is None:
        return "(none)"
    (tgt, ecx, edx), args = x
    nm = context()["img"].names.get(tgt, "")
    return "%08x%s ecx=%s args=[%s]" % (tgt, " " + nm if nm else "", ecx if isinstance(ecx, str) else "%08x" % ecx,
                                         ", ".join(a if isinstance(a, str) else "%x" % a for a in args))


# ====================================================================== driver

MAX_PROCS = int(os.environ.get("DIFFTEST_MAX_PROCS", max(1, (os.cpu_count() or 2) // 2)))


def cpu_slot():
    """Hold one of MAX_PROCS machine-wide slots (flock'd files) while emulating, so concurrent
    checkers (batch shards, agents) use at most half the cores. Blocks until a slot is free."""
    import fcntl
    d = os.path.join("/tmp", "difftest-slots-%d" % os.getuid())
    os.makedirs(d, exist_ok=True)
    while True:
        for i in range(MAX_PROCS):
            fd = os.open(os.path.join(d, "slot%d" % i), os.O_CREAT | os.O_RDWR)
            try:
                fcntl.flock(fd, fcntl.LOCK_EX | fcntl.LOCK_NB)
                return fd
            except OSError:
                os.close(fd)
        time.sleep(0.5)


def test_function(sid, va, opts, log=print):
    fd = cpu_slot()
    try:
        return _test_function(sid, va, opts, log)
    finally:
        os.close(fd)          # releases the flock


def _test_function(sid, va, opts, log=print):
    t0 = time.time()
    t = prepare(sid, va, opts.flags, log, getattr(opts, "src", None))
    out = {"slice": sid, "va": "%08x" % va, "flags": " ".join(t.flags), "flags_from": t.flags_how,
           "symbol": getattr(t, "sym", None), "symbol_from": getattr(t, "sym_how", None),
           "unresolved": t.unresolved, "eh_unresolved": t.eh_unresolved,
           "resolution_conflicts": [{"symbol": c[0], "resolved": "%08x" % c[1], "method": c[2], "aligned": "%08x" % c[3]}
                                    for c in t.conflicts],
           "resolution_methods": t.methods}
    if t.verdict == "UNSUPPORTED":
        out.update(verdict="UNSUPPORTED", reason=t.reason, seconds=round(time.time() - t0, 1))
        return out
    out.update(signature=str(t.sig) if t.sig else "unparsed (%s)" % getattr(t, "sig_error", "?"),
               stack_args=len(t.stack_kinds), reg_args=t.reg_kinds, callee_pop=t.callee_pop,
               ret_kind=t.ret_kind, layout_notes=t.layout_notes, orig_size=t.orig_hi - t.orig_lo)
    if t.abi_mismatch and not opts.ignore_abi:
        out.update(verdict="UNSUPPORTED", reason=t.abi_mismatch, seconds=round(time.time() - t0, 1))
        return out
    runner = Runner(t, opts, log)
    cmp_ = Comparer(runner, opts)
    rng_master = random.Random("%s:%08x:%d" % (sid, va, opts.seed))
    gen = runner.gen
    corpus = []
    valid, discarded, mism, first = 0, {}, 0, None
    traps = {}
    repaired = 0
    faked = 0
    ran = 0
    probes = 0
    deadline = time.time() + opts.time_limit
    try:
        for i in range(opts.inputs):
            if time.time() > deadline:
                out["stopped_early"] = "time limit %ds after %d inputs" % (opts.time_limit, i)
                break
            ran += 1
            rng = random.Random(rng_master.getrandbits(64))
            if corpus and rng.random() < opts.mutate:
                inp = gen.mutate(corpus[-1 - min(int(rng.expovariate(0.15)), len(corpus) - 1)], rng, corpus)
            else:
                inp = gen.fresh(rng)
            a = runner.run_side(runner.orig, inp)
            fixes = 0
            while (a["status"][0] == "fault" and a["fault"] and a["fault"][0] != "pool-limit"
                   and fixes < opts.repairs and time.time() < deadline):
                rep = runner.repair(inp, a["fault"], rng)
                if rep is None:
                    break
                inp = rep
                fixes += 1
                a = runner.run_side(runner.orig, inp)
            if a["status"][0] == "budget" and runner.budget < opts.budget and probes < BUDGET_PROBES:
                # Runaway input, or a function whose real runs are long? Retry with the full cap.
                probes += 1
                low, runner.budget = runner.budget, opts.budget
                a2 = runner.run_side(runner.orig, inp)
                if a2["status"][0] == "budget":
                    runner.budget = low
                else:
                    a = a2
                    out["budget_raised"] = "input %d needed more than %d instructions" % (i, low)
            st = a["status"][0]
            if st != "ok":
                key = st if st != "import" else "import:%s" % str(a["status"][1]).split(":")[0]
                if st == "fault" and a["fault"]:
                    key = "fault(%s)" % a["fault"][0]
                discarded[key] = discarded.get(key, 0) + 1
                continue
            if not runner.abi_ok(a):
                # the original itself returned with clobbered callee-saved registers or a wrong esp:
                # a fake method popped the wrong number of bytes, or the input sent it through
                # non-code (e.g. a vtable pointer into .text). Says nothing about equivalence.
                key = "orig-abi-broken(fake)" if a["fakes"] else "orig-abi-broken"
                discarded[key] = discarded.get(key, 0) + 1
                continue
            if fixes:
                repaired += 1
            run_blocks = runner.run_blocks
            b = runner.run_side(runner.ours, inp)
            sb = b["status"]
            if sb[0] == "trap":
                traps[sb[1]] = traps.get(sb[1], 0) + 1
                discarded["ours-trap"] = discarded.get("ours-trap", 0) + 1
                continue
            if b["fakes"] and sb[0] == "ok" and not runner.abi_ok(b):
                discarded["ours-abi-broken(fake)"] = discarded.get("ours-abi-broken(fake)", 0) + 1
                continue
            if a["fakes"] or b["fakes"]:
                fa, fb = {}, {}
                for tg, n in a["fakes"]:
                    fa.setdefault(tg, set()).add(n)
                for tg, n in b["fakes"]:
                    fb.setdefault(tg, set()).add(n)
                if any(len(v) > 1 for v in list(fa.values()) + list(fb.values())) or \
                        any(fa[k] != fb[k] for k in set(fa) & set(fb)):
                    discarded["fake-arity"] = discarded.get("fake-arity", 0) + 1
                    continue
                faked += 1
            valid += 1
            if run_blocks - runner.blocks:
                runner.blocks |= run_blocks
                corpus.append(inp)
            if sb[0] != "ok":
                d = ("execution", "returned normally", "%s: %s" % sb, "ours failed where the original succeeded")
            else:
                d = cmp_.compare(a, b, t)
            if d:
                mism += 1
                if first is None:
                    first = {"input": i, "profile": inp.profile, "origin": inp.origin, "observable": d[0],
                             "kind": cmp_.last_kind or ("float-rounding" if d[0] == "st0" else "value"),
                             "orig": d[1], "ours": d[2], "detail": d[3], "args": ["%08x" % w for w in inp.args],
                             "regs": {k: "%08x" % v for k, v in inp.regs.items()},
                             "fake_calls": len(a["fakes"]), "repairs": fixes}
                    try:
                        import pickle
                        os.makedirs(FAIL_DIR, exist_ok=True)
                        pth = os.path.join(FAIL_DIR, "%s_%08x.pkl" % (sid, va))
                        with open(pth, "wb") as f:
                            pickle.dump(dict(inp.__dict__, pagegen=inp.pagegen), f)
                        first["input_file"] = os.path.relpath(pth, S.ROOT)
                    except OSError:
                        pass
                    if opts.verbose:
                        log("  MISMATCH input %d: %s orig=%s ours=%s (%s)" % (i, d[0], d[1], d[2], d[3]))
                if mism >= opts.max_mismatch:
                    break
    finally:
        runner.close()
    out["repaired_inputs"] = repaired
    out["inputs_with_fake_calls"] = faked
    out["corpus"] = len(corpus)
    covered = set()
    for (ba, bs) in runner.blocks:
        for a in range(ba, ba + bs):
            if a in t.orig_insns:
                covered.add(a)
    total = len(t.orig_insns)
    cov = 100.0 * len(covered) / total if total else 0.0
    out.update(inputs=ran, valid=valid, discarded=discarded, mismatches=mism, first_mismatch=first,
               coverage={"covered_insns": len(covered), "total_insns": total, "pct": round(cov, 1)},
               tolerated=cmp_.tolerated, ours_traps=traps)
    if opts.ulp:
        out["ulp"] = opts.ulp
    if mism and first.get("kind") == "local-address":
        v, why = "UNSUPPORTED", ("our code stores the address of its own copy of an object/vtable/constant "
                                 "where the original stores the image's (%s); map that symbol" % first["observable"])
    elif mism:
        v, why = "FAIL", "%d/%d valid inputs mismatched; first: %s" % (mism, valid, first["observable"])
    elif traps:
        v, why = "UNSUPPORTED", "our code reached unresolved symbol(s) %s" % ", ".join(sorted(traps))
    elif valid < max(10, ran // 20):
        top = sorted(discarded.items(), key=lambda x: -x[1])[:3]
        v, why = "UNSUPPORTED", "only %d/%d inputs valid (discards: %s)" % (valid, ran, ", ".join("%s=%d" % x for x in top))
    elif valid >= opts.min_valid and cov >= opts.min_cov:
        v, why = "PASS", "%d valid inputs, %.1f%% coverage" % (valid, cov)
    else:
        v, why = "WEAK", "%d valid inputs (need %d), %.1f%% coverage (need %.0f%%)" % (valid, opts.min_valid, cov, opts.min_cov)
    out.update(verdict=v, reason=why, seconds=round(time.time() - t0, 1))
    return out


def replay(sid, va, path, opts):
    """Run one saved input (from a FAIL) on both sides and print every observable."""
    import pickle
    t = prepare(sid, va, opts.flags, print, getattr(opts, "src", None))
    if t.verdict:
        print(t.verdict, t.reason)
        return 1
    runner = Runner(t, opts)
    inp = Input()
    inp.__dict__.update(pickle.load(open(path, "rb")))
    inp.__dict__.setdefault("pagegen", 1)       # saved before pagegen existed
    a = runner.run_side(runner.orig, inp)
    b = runner.run_side(runner.ours, inp)
    cmp_ = Comparer(runner, opts)
    print("args", ["%08x" % w for w in inp.args], "regs", {k: "%08x" % v for k, v in inp.regs.items()})
    for nm, o in (("orig", a), ("ours", b)):
        print("%s: %s eax=%08x edx=%08x ebx=%08x esi=%08x edi=%08x ebp=%08x esp=+%x x87=%d fakes=%d" % (
            nm, o["status"], o["eax"], o["edx"], o["ebx"], o["esi"], o["edi"], o["ebp"], o["esp"], o["fpu_depth"],
            len(o["fakes"])))
        for ent in cmp_.norm_calls(o["calls"])[:60]:
            print("    call", fmt_tcall(ent))
        for ent in o["imports"][:40]:
            print("    import", fmt_call((ent[0], tuple(norm_val(v, runner.esp_entry) for v in ent[1]))))
    print("first difference:", cmp_.compare(a, b, t) if a["status"][0] == b["status"][0] == "ok" else "status differs")
    runner.close()
    return 0


def parse_args(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[1])
    ap.add_argument("slice")
    ap.add_argument("vas", nargs="*")
    ap.add_argument("--flags")
    ap.add_argument("--src", help="test this source file instead of match/slices/<id>/<id>.cpp")
    ap.add_argument("--inputs", type=int, default=DEFAULT_INPUTS)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--json")
    ap.add_argument("--min-valid", type=int, default=DEFAULT_K)
    ap.add_argument("--min-cov", type=float, default=DEFAULT_C)
    ap.add_argument("--ulp", type=int, default=0)
    ap.add_argument("--strict-calls", action="store_true")
    ap.add_argument("--budget", type=int, default=DEFAULT_BUDGET, help="max instructions per original run (ours: 4x)")
    ap.add_argument("--start-budget", type=int, default=START_BUDGET,
                    help="initial cap; raised to --budget if one of the first %d capped inputs finishes under it" % BUDGET_PROBES)
    ap.add_argument("--time-limit", type=int, default=600, help="seconds per function")
    ap.add_argument("--run-seconds", type=float, default=10, help="wall-clock cap per original run (ours: 4x)")
    ap.add_argument("--max-mismatch", type=int, default=5)
    ap.add_argument("--no-fake-calls", dest="fake_calls", action="store_false",
                    help="discard inputs that call through a generated function pointer instead of emulating a do-nothing method")
    ap.add_argument("--ignore-abi", action="store_true", help="run even if the original reads an undeclared register argument")
    ap.add_argument("--repairs", type=int, default=24, help="fault repairs per input (0 = off)")
    ap.add_argument("--nan", action="store_true", help="also generate NaN/Inf float bit patterns")
    ap.add_argument("--alias", type=float, default=0.0, help="probability that a generated pointer aliases an argument object")
    ap.add_argument("--mutate", type=float, default=0.6, help="share of inputs mutated from the coverage corpus")
    ap.add_argument("-v", "--verbose", action="store_true")
    ap.add_argument("--replay", help="re-run one saved failing input (first_mismatch.input_file) and print details")
    return ap.parse_args(argv)


def main(argv=None):
    opts = parse_args(argv)
    sid = opts.slice
    if opts.vas:
        vas = [int(v, 16) for v in opts.vas]
    else:
        vas = [r[0] for r in S.read_rows(os.path.join(S.slice_dir(sid), "nonmatching.txt"))]
        if not vas:
            sys.exit("%s: no VAs given and nonmatching.txt is empty" % sid)
    if opts.replay:
        return replay(sid, vas[0], opts.replay, opts)
    results = []
    for va in vas:
        print("%s %08x ..." % (sid, va), flush=True)
        r = test_function(sid, va, opts)
        results.append(r)
        print_result(r)
    if opts.json:
        os.makedirs(os.path.dirname(os.path.abspath(opts.json)), exist_ok=True)
        json.dump(results, open(opts.json, "w"), indent=1)
    return 0 if all(r["verdict"] == "PASS" for r in results) else 1


def print_result(r):
    print("  %-11s %s" % (r["verdict"], r["reason"]))
    if "symbol" in r and r["symbol"]:
        print("    symbol %s (%s); flags %s (%s)" % (r["symbol"][:90], r["symbol_from"], r["flags"], r["flags_from"]))
    if "valid" in r:
        print("    inputs %d, valid %d, discarded %s, coverage %s%% (%d/%d insns), %.1fs" % (
            r["inputs"], r["valid"], r["discarded"] or "{}", r["coverage"]["pct"], r["coverage"]["covered_insns"],
            r["coverage"]["total_insns"], r["seconds"]))
        tol = {k: v for k, v in r["tolerated"].items() if v}
        if tol:
            print("    tolerated: %s" % tol)
    fm = r.get("first_mismatch")
    if fm:
        print("    first mismatch (input %d, %s, %s): %s\n      orig: %s\n      ours: %s\n      %s" % (
            fm["input"], fm["profile"], fm.get("kind", "?"), fm["observable"], fm["orig"], fm["ours"], fm["detail"]))
    if r.get("resolution_conflicts"):
        print("    resolution conflicts: %s" % r["resolution_conflicts"][:3])


if __name__ == "__main__":
    sys.exit(main())
