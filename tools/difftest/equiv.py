#!/usr/bin/env python3
"""Differential equivalence test: ORIGINAL function (from the binary) vs OUR compiled function.

usage: equiv.py <slice-id> [<va> ...] [--flags "..."] [--inputs N] [--seed S] [--json out.json]
                [--min-valid K] [--gate edges|insns] [--no-steer] [--ulp U] [--strict-calls]
                [--budget N] [--time-limit S] [--fp-tol] [--fp-realistic]
                [--call-regs [--call-regs-strict]] [-v]

Default VAs: the slice's nonmatching.txt. Our function is compiled (into work/difftest/obj/, never
match/), its relocations are resolved to the ORIGINAL's addresses (tools/difftest/resolve.py), and
both versions run under Unicorn on the same generated inputs; every observable (return registers,
callee-saved registers, esp, x87/SSE result, every written byte of .data/heap/input buffers/caller
stack, the import-call trace and the depth-1 call trace) must agree.

Coverage is BRANCH (edge) coverage on BOTH builds (tools/difftest/cfgcov.py): every conditional jump's
taken and not-taken edge and every jump-table target of the original function and of ours, counted over
valid inputs. An edge the harness cannot reach is listed with its reason in the JSON ("edges" ->
side -> "unreachable") and in the printed result, never dropped silently: statically infeasible x87
status-word branches, NaN-only branches (without --nan), edges only reachable past a call that never
returned (an unmodelled import, a C++ throw or a pure virtual call stopped every run that reached it),
and edges only reachable through such edges. Instruction coverage of the original is still reported.

Inputs are random "pointer soup" plus steering (tools/difftest/steer.py; --no-steer turns it off):
the constants compared before branches (both builds, +-1 / +-1 ulp) join the dictionary; uncovered
branches are replayed with the compare instrumented and the compared input location (argument, entry
register, pool field, .data global, malloc result) is set to the other operand (input-to-state);
mutation prefers inputs that reach uncovered branches; covered compares get boundary probes; fault
repair redirects bad pointers, small-ifies garbage indices and, as a last resort, maps input memory
at the faulting address. A run that stops in `_purecall` is resampled the same way instead of being
discarded: the dword that carried the vtable pointer (an argument, a pool object's vtable field or an
image .data global) and, when that is not the input's, the vtable slot itself get input soup, and the
first resample that gets past the pure call is kept.

Verdicts:
  PASS        no mismatch, >= K valid inputs (--min-valid, default 200) and every edge of BOTH builds
              covered except the listed unreachable ones;
  WEAK        no mismatch, but too few valid inputs or missed edges; the reason names the side(s) and
              how many edges each misses;
  PASS-FP / WEAK-FP  (--fp-tol only) PASS / WEAK where every mismatching input differed only by float rounding
              (judged against the original at 64-bit precision) or was out of float range; stats in the reason;
  FAIL        a mismatch (the first one is printed, its input saved for --replay). A pointer to our own
              copy of a constant/vtable/code label where the original stores the image's address is
              tolerated (with a note) only when the bytes at both are identical; otherwise it is a FAIL
              whose detail names the differing dwords;
  UNSUPPORTED unresolved reference, symbol not found, compile error, or almost every input discarded.
--gate insns restores the legacy gate (original's instruction coverage >= --min-cov, default 60%).
--call-regs is a diagnostic for a FAIL: it captures the whole live register file (eax ebx ecx edx esi edi ebp
esp, xmm0-3) at every recorded call site (depth-1 calls, imports, fake calls) and reports the first difference
that no tolerance explains (an address inside the function's own stack frame, the same pooled constant, our own
copy of a block with identical bytes, --ulp), with the call index, its callee and both values, in the result's
"call_regs" and the printed reason. It never changes a verdict; --call-regs-strict makes such a difference a
mismatch (only for an input whose every other observable agrees, and only at a call pair whose callee and
arguments agree).
"""
import argparse, collections, glob, json, math, os, random, re, struct, sys, time, zlib

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import capstone                                    # noqa: E402
try:
    os.nice(10)                                    # yield the CPU to interactive work
except OSError:
    pass
import numpy as np                                 # noqa: E402
from capstone import x86_const as CX               # noqa: E402
from unicorn import UcError, UC_HOOK_CODE, UC_HOOK_BLOCK, UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE, UC_PROT_READ, UC_PROT_WRITE    # noqa: E402
from unicorn.x86_const import *                    # noqa: E402,F401,F403

import slice as S                                  # noqa: E402
import resolve as R
import resaudit as RA                              # noqa: E402
import regfacts as RF                                # noqa: E402
import cfgcov as CF                                # noqa: E402
import steer as ST                                 # noqa: E402
import invariants as INV                           # noqa: E402
import sig as SIG                                  # noqa: E402
import machine as M                                # noqa: E402
from coff import Coff                              # noqa: E402

DEFAULT_INPUTS = 400
DEFAULT_K = 200
DEFAULT_C = 60.0                  # legacy --gate insns only
DEFAULT_BUDGET = 10_000_000
START_BUDGET = 100_000
BUDGET_PROBES = 3
FAIL_DIR = os.environ.get("DIFFTEST_FAIL_DIR") or os.path.join(S.ROOT, "work", "difftest", "fail_inputs")
# Regression inputs: every input that ever made a row mismatch is kept (one file per distinct input) and run first
# by every later run of that row, so a FAIL once found is re-checked forever, whatever the seed or the steering
# does. Per row and per --pin set (a pinned case's inputs carry its selector). --no-regress / DIFFTEST_NO_REGRESS=1
# turns it off; the file names enter the result cache key, so a new regression input invalidates cached verdicts.
REGRESS_DIR = os.environ.get("DIFFTEST_REGRESS_DIR") or os.path.join(S.ROOT, "work", "difftest", "regress")


def regress_dir(sid, va, opts):
    import hashlib
    pins = sorted(getattr(opts, "pin", None) or [])
    sub = hashlib.sha1(json.dumps(pins).encode()).hexdigest()[:12] if pins else "nopin"
    return os.path.join(REGRESS_DIR, "%s_%08x" % (sid, va), sub)


def regress_inputs(sid, va, opts):
    """[(file name, Input)] of the row's regression inputs, oldest first."""
    if getattr(opts, "no_regress", False) or os.environ.get("DIFFTEST_NO_REGRESS"):
        return []
    import pickle
    d = regress_dir(sid, va, opts)
    out = []
    try:
        names = sorted(os.listdir(d), key=lambda f: os.path.getmtime(os.path.join(d, f)))
    except OSError:
        return []
    for f in names:
        if not f.endswith(".pkl"):
            continue
        try:
            inp = Input()
            inp.__dict__.update(pickle.load(open(os.path.join(d, f), "rb")))
            inp.__dict__.setdefault("pagegen", 1)
            inp.origin = "regress"
            out.append((f, inp))
        except Exception:       # noqa: BLE001 - an unreadable file (older harness) is skipped, never fatal
            continue
    return out


def save_regress(sid, va, opts, inp):
    """Keep a mismatching input (content-addressed: the same input is stored once). -> path or None."""
    if getattr(opts, "no_regress", False) or os.environ.get("DIFFTEST_NO_REGRESS"):
        return None
    import hashlib, pickle
    blob = pickle.dumps(dict(inp.__dict__, pagegen=inp.pagegen, origin="regress"))
    d = regress_dir(sid, va, opts)
    pth = os.path.join(d, hashlib.sha1(blob).hexdigest()[:16] + ".pkl")
    try:
        os.makedirs(d, exist_ok=True)
        if not os.path.exists(pth):
            tmp = pth + ".%d.part" % os.getpid()
            open(tmp, "wb").write(blob)
            os.replace(tmp, pth)
        return pth
    except OSError:
        return None

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
        _ctx.update(img=img, db=db, res=R.Resolver(img, db), m=machine_hooks(M.Machine(img)), arity={}, ecxuse={})
    return _ctx


def machine_hooks(m):
    """Input-controlled allocation failure: the k-th malloc/operator new of a run returns NULL when k is
    in the input's alloc_fail (the null-check branches after `new` are edges like any other)."""
    h = m.handlers.get("malloc")
    if h is not None and h["fn"] is not None and not getattr(m, "_alloc_wrapped", False):
        inner = h["fn"]

        def malloc(m_, a, esp):
            k = m_.alloc_count
            m_.alloc_count += 1
            if k in m_.alloc_fail:
                return 0
            p = inner(m_, a, esp)
            if m_.alloc_log is not None:
                m_.alloc_log.append((k, p))
            return p
        h["fn"] = malloc
        m._alloc_wrapped = True
    m.alloc_fail, m.alloc_count, m.alloc_log = (), 0, None
    return m


# ====================================================================== preparation

class Target:
    pass


_RES_NAMES = None


def _norm_sym(n):
    """Comparable identity of a symbol name: keep the mangled name (it carries the class, the arity and the
    cv-qualifiers) but drop a leading `_` so cdecl names line up across the two builds. None for anything
    that is not a string (an unresolved slot)."""
    return n.lstrip("_") if isinstance(n, str) else None


def _res_name_table():
    """{image va: name} for every function the relink defined at an address (resolve_map `defined_at`)."""
    global _RES_NAMES
    if _RES_NAMES is None:
        out = {}
        try:
            rm = json.load(open(os.path.join(S.ROOT, "work", "relink", "resolve_map.json")))
            for a, v in (rm.get("defined_at") or {}).items():
                nm = v[0] if isinstance(v, (list, tuple)) else v
                if nm:
                    out[int(a, 16)] = nm
        except (OSError, ValueError, KeyError):
            pass
        _RES_NAMES = out
    return _RES_NAMES


_VT_MATCH = None


def _vtable_match_table():
    """{by_orig: {orig vtable va: (mangled name, slot count)}} from work/relink/resolve_map.json, or None.
    The relink matched those tables by content, so an address difference between our copy and the image's is
    link-time bookkeeping; what the harness has to check is the call graph (see Comparer._vtable_match)."""
    global _VT_MATCH
    if _VT_MATCH is None:
        try:
            p = os.path.join(S.ROOT, "work", "relink", "resolve_map.json")
            rm = json.load(open(p))
            by_orig = {}
            for name, e in (rm.get("vtables") or {}).items():
                orig = e.get("orig") or []
                if len(orig) == 1:
                    by_orig[int(orig[0], 16)] = (name, int(e.get("slots") or 0))
            _VT_MATCH = {"by_orig": by_orig} if by_orig else {}
        except (OSError, ValueError, KeyError):
            _VT_MATCH = {}
    return _VT_MATCH


def unsupported(t, reason, **kw):
    t.verdict = "UNSUPPORTED"
    t.reason = reason
    for k, v in kw.items():
        setattr(t, k, v)
    return t


def modelled_symbols(t):
    """r.models of the resolver (agent B's model bindings; absent before that landed). Each entry is
    {"symbol", "kind", "addr", "size"}; kind "model-data"/"model-stub" is a harness model, "orig-code" is
    the original's own code at that address and is evidence, not a model."""
    ms = getattr(t, "models", None)
    if ms is None:
        ms = getattr(getattr(t, "res", None), "models", None)
    out = []
    for m in ms or ():
        sym, kind = (m.get("symbol"), m.get("kind")) if isinstance(m, dict) else \
            (getattr(m, "symbol", None), getattr(m, "kind", None))
        out.append({"symbol": sym, "kind": kind})
    return out


def describe_invariants(invs):
    """Human form of a row's input-object invariants for the JSON ('face::count in [1..4]'), or None."""
    txt = INV.describe(invs)
    return txt or None


def model_note(ms):
    """'; N modelled symbol(s)' for the reason (only model-* kinds are models), or ''."""
    n = sum(1 for m in ms if str(m.get("kind") or "").startswith("model"))
    return "; %d modelled symbol(s)" % n if n else ""


def model_capped(v, ms):
    """A verdict that rests on a harness model can be no better than WEAK: a model proves the row runnable,
    never that our code is equivalent. A FAIL is already stronger evidence and is left alone."""
    if any(str(m.get("kind") or "").startswith("model") for m in ms):
        if v == "PASS":
            return "WEAK"
        if v == "PASS-FP":
            return "WEAK-FP"
    return v


def prepare(sid, va, flags_override=None, log=print, src=None):
    ctx = context()
    img = ctx["img"]
    t = Target()
    t.sid, t.va = sid, va
    t.verdict = None
    t.unresolved, t.eh_unresolved, t.conflicts, t.methods = [], [], [], {}
    t.flags, t.flags_how = S.choose_flags(sid, va, flags_override)
    # an override of only include/define options (`--flags "/Isrc/game/include"`, a flags-less manifest row) is an addition
    # to the defaults, not a replacement: alone it compiled without /O2 /MD /Gy /EHsc /TP and every callee read unresolved
    # (mig14 SPGraphicsLightingManager: bogus "34 unresolved reference(s)" UNSUPPORTED)
    if flags_override and t.flags and all(f.startswith(("/I", "-I", "/D", "-D")) for f in t.flags):
        t.flags, t.flags_how = list(S.DEFAULT_FLAGS) + [f for f in t.flags if f not in S.DEFAULT_FLAGS], t.flags_how + "+defaults"
    src = src or S.source_path(sid)
    t.src = src
    # a module TU (src/game/<dir>/<Stem>.cpp) includes `game/types.h` and the canonical headers: without /Isrc/game/include
    # (an agent passing the slice's flags, or none) the compile failed C1083 and the row read UNSUPPORTED (mig10 papercut)
    if os.path.normpath(src).replace(os.sep, "/").split("/src/game/")[-1] != os.path.normpath(src) or \
            os.path.normpath(src).replace(os.sep, "/").startswith("src/game/"):
        if not any(f.replace("\\", "/").rstrip("/").endswith("src/game/include") for f in t.flags if f.startswith("/I")):
            t.flags = list(t.flags) + ["/Isrc/game/include"]
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
    annots = R.source_annotations([src] + glob.glob(os.path.join(S.slice_dir(sid), "*.h")) + S.sibling_headers(src))
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
    if not sym.startswith("?"):
        # extern "C": the symbol carries no types; read the C declaration from our source
        cname = sym[1:] if sym[:1] in "_@" else sym
        cname = cname.split("@")[0]
        hdrs = [src] + glob.glob(os.path.join(os.path.dirname(src), "*.h"))
        try:
            cs = SIG.parse_c_decl(cname, [open(h, encoding="utf-8", errors="replace").read() for h in hdrs],
                                  [open(h, encoding="utf-8", errors="replace").read() for h in include_headers()])
            pops = sum(n for _k, n in cs.params if n) if cs.params else 0
            stdn = int(sym.rsplit("@", 1)[1]) // 4 if "@" in sym[1:] and sym.rsplit("@", 1)[1].isdigit() else None
            if stdn is None or (stdn == pops and not any(k == "struct" for k, _n in cs.params)):
                t.sig, t.sig_how = cs, "C declaration"
        except (SIG.SigError, OSError) as e:
            t.sig_error = getattr(t, "sig_error", "") + "; C declaration: %s" % e
    analyse_original(t)
    build_layout(t)
    return t


_include_headers = []


def include_headers():
    """Headers under match/include (typedefs for C declarations), listed once per process."""
    if not _include_headers:
        for d, _sub, files in os.walk(os.path.join(S.ROOT, "match", "include")):
            _include_headers.extend(os.path.join(d, f) for f in files if f.endswith((".h", ".hpp")))
        _include_headers.append(os.devnull)
    return [h for h in _include_headers if h != os.devnull]


def best_by_size(coff, names, n0):
    best = None
    for nm in names:
        _s, a, b = coff.func_extent(coff.by_name[nm])
        d = abs((b - a) - n0)
        if best is None or d < best[0]:
            best = (d, nm)
    return best[1]


def _audit_copy(t, name, ova):
    """The local copies our symbol `name` (a local copy of the original's ova) itself calls, paired by the resolution
    audit against the original function at ova: [] when either side is unavailable."""
    img = context()["img"]
    table = t.coff.syms.values() if isinstance(t.coff.syms, dict) else t.coff.syms
    syms = [s for s in table if getattr(s, "name", None) == name and getattr(s, "defined", False)]
    if not syms:
        return []
    try:
        lo, hi = img.func_extent(ova)
        code = img.read(lo, hi - lo)
        insns, _tables = R.recursive_descent(lambda a, n: code[a - lo:a - lo + n], lo, hi, ova,
                                             lambda a: struct.unpack_from("<I", code, a - lo)[0] if lo <= a <= hi - 4 else None)
        return RA.audit(t.coff, syms[0], t.res, insns, img).get("local_copy", [])
    except Exception:
        return []


def analyse_original(t):
    """Recursive-descent disassembly of the original: instruction set (coverage denominator),
    callee-pop size, ECX/EDX use at entry, immediate dictionary for input generation."""
    img = context()["img"]
    lo, hi = t.orig_lo, t.orig_hi
    code = img.read(lo, hi - lo)
    relset = set(img.reloc_positions(lo, hi - lo))

    def rd(a, n):
        return code[a - lo:a - lo + n]

    norel = not img.relocs      # mount&blade.exe has no .reloc: a jump table is any in-function dword run of
                                # in-function targets (MSVC puts it after the body); without this the
                                # original's switch bodies were missing from its CFG, coverage and call sites

    def tt(a):
        if (norel or a in relset) and lo <= a <= hi - 4:
            return struct.unpack_from("<I", code, a - lo)[0]
        return None
    insns, tables = R.recursive_descent(rd, lo, hi, t.va, tt)
    t.orig_insns = insns
    t.orig_cfg = CF.Cfg(insns, t.va, lo, hi, tt)
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
    # A tail call (`jmp` to another function, the stack balanced back to the entry state) returns through the
    # target's `ret N`: those arguments are popped by it (ui_widgets_c 0x48bda0 has no ret of its own and ends in
    # `jmp 0x488720`, whose `ret 0x10` pops the four arguments it was handed; read as 0, every run was
    # "orig-abi-broken").
    for a, ins in insns.items():
        if ins.id == CX.X86_INS_JMP and ins.operands and ins.operands[0].type == CX.X86_OP_IMM:
            tgt = ins.operands[0].imm & 0xFFFFFFFF
            if lo <= tgt < hi or not img.in_text(tgt):
                continue
            try:
                tlo, thi = img.func_extent(tgt)
                if tlo != tgt:
                    continue
                tcode = img.read(tlo, thi - tlo)
                tins, _ = R.recursive_descent(lambda x, k: tcode[x - tlo:x - tlo + k], tlo, thi, tgt, lambda x: None)
            except Exception:
                continue
            pops |= {i.operands[0].imm if i.operands else 0 for i in tins.values() if i.id == CX.X86_INS_RET}
    t.callee_pop = max(pops) if pops else 0
    t.pop_variants = sorted(pops)
    ordered = [insns[a] for a in sorted(insns)]
    t.orig_regs_written = RF.regs_written(ordered)   # registers the original never writes are compared
    t.orig_returns_eax = RF.returns_eax(ordered)     # a void declaration may hide an eax return
    t.dict = sorted(consts | {(c + 1) & 0xFFFFFFFF for c in consts if c < 0x10000} |
                    {(c - 1) & 0xFFFFFFFF for c in consts if 0 < c < 0x10000})[:4096]
    t.entry_reads = entry_reads(insns, t.va)


ALL_FAM = {CX.X86_REG_ECX: "ecx", CX.X86_REG_CX: "ecx", CX.X86_REG_CL: "ecx", CX.X86_REG_CH: "ecx",
           CX.X86_REG_EDX: "edx", CX.X86_REG_DX: "edx", CX.X86_REG_DL: "edx", CX.X86_REG_DH: "edx",
           CX.X86_REG_EAX: "eax", CX.X86_REG_AX: "eax", CX.X86_REG_AL: "eax", CX.X86_REG_AH: "eax",
           CX.X86_REG_EBX: "ebx", CX.X86_REG_BX: "ebx", CX.X86_REG_BL: "ebx", CX.X86_REG_BH: "ebx",
           CX.X86_REG_ESI: "esi", CX.X86_REG_SI: "esi", CX.X86_REG_EDI: "edi", CX.X86_REG_DI: "edi",
           CX.X86_REG_EBP: "ebp", CX.X86_REG_BP: "ebp"}


def entry_reads(insns, entry, regs=("ecx", "edx", "eax"), follow_jcc=False):
    """Registers among `regs` read before written along the entry path (first 40 insns). follow_jcc: continue
    along the fall-through of a conditional jump (a read behind an early `je` still reads the argument)."""
    read, written = set(), set()
    order = []
    a = entry
    names = {k: v for k, v in ALL_FAM.items() if v in regs}
    for _ in range(40):
        ins = insns.get(a)
        if ins is None:
            break
        try:
            r, w = ins.regs_access()
        except capstone.CsError:
            break
        ops = ins.operands
        if ins.id in (CX.X86_INS_XOR, CX.X86_INS_SUB, CX.X86_INS_SBB) and len(ops) == 2 \
                and ops[0].type == CX.X86_OP_REG and ops[1].type == CX.X86_OP_REG and ops[0].reg == ops[1].reg:
            r = []          # zeroing (or carry-mask) idiom: the old value is not used
        if len(ops) == 2 and ops[0].type == CX.X86_OP_REG and ops[1].type == CX.X86_OP_IMM and \
                ((ins.id == CX.X86_INS_OR and ops[1].imm & 0xFFFFFFFF == 0xFFFFFFFF) or
                 (ins.id == CX.X86_INS_AND and ops[1].imm == 0)):
            r = []          # 'or eax,-1' / 'and eax,0': constant result
        if ins.id == CX.X86_INS_PUSH:
            r = []          # 'push ecx' is MSVC's 4-byte stack allocation / a save, not a use
        if len(ops) == 2 and ops[0].type == CX.X86_OP_REG and (
                (ins.id == CX.X86_INS_LEA and ops[1].type == CX.X86_OP_MEM and not ops[1].mem.disp
                 and not ops[1].mem.index and ops[1].mem.base == ops[0].reg) or
                (ins.id == CX.X86_INS_MOV and ops[1].type == CX.X86_OP_REG and ops[1].reg == ops[0].reg)):
            r = []          # 'lea ecx,[ecx]' / 'mov ecx,ecx': MSVC's alignment nop, not a use
                            # (static_init 0x548360 read ecx as an argument only through this nop)
        for x in r:
            n = names.get(x)
            if n and n not in written:
                if n not in read:
                    order.append(n)
                read.add(n)
        for x in w:
            n = names.get(x)
            if n:
                written.add(n)
        if ins.group(capstone.CS_GRP_JUMP) or ins.group(capstone.CS_GRP_CALL) or ins.group(capstone.CS_GRP_RET):
            if not (follow_jcc and ins.group(capstone.CS_GRP_JUMP) and ins.id != CX.X86_INS_JMP):
                break
        a += ins.size
    entry_reads.order = order           # first-read order of the last call (reg_map pairs arguments by it)
    return read


GPR32 = {CX.X86_REG_EAX: "eax", CX.X86_REG_EBX: "ebx", CX.X86_REG_ECX: "ecx", CX.X86_REG_EDX: "edx",
         CX.X86_REG_ESI: "esi", CX.X86_REG_EDI: "edi", CX.X86_REG_EBP: "ebp", CX.X86_REG_ESP: "esp"}


def reg_arg_use(insns, entry, reg, limit=40):
    """How the original uses the argument our declaration does not pass: (kind, address, instruction).
    'pointer' = the original addresses memory through it, 'int' = it is compared/masked/scaled, 'unknown' =
    copied around only. Follows fall-through (a conditional branch still runs one way) and `mov r32, reg`
    copies, so a this pointer parked in esi still counts; stops at jmp/ret."""
    aliases, int_ev, a = {reg}, None, entry
    for _ in range(limit):
        ins = insns.get(a)
        if ins is None:
            break
        ops, text = ins.operands, "%s %s" % (ins.mnemonic, ins.op_str)
        for op in ops:                      # memory addressed through the register: a pointer
            if op.type == CX.X86_OP_MEM:
                for rr in (op.mem.base, op.mem.index):
                    if GPR32.get(rr) in aliases:
                        return "pointer", a, text
        try:
            rd, wr = ins.regs_access()
        except capstone.CsError:
            break
        reads = {GPR32.get(x) for x in rd} & aliases
        writes = {GPR32.get(x) for x in wr} & aliases
        zeroed = ins.id in (CX.X86_INS_XOR, CX.X86_INS_SUB, CX.X86_INS_SBB) and len(ops) == 2 and \
            ops[0].type == CX.X86_OP_REG and ops[1].type == CX.X86_OP_REG and ops[0].reg == ops[1].reg
        if zeroed:
            reads = set()                   # 'xor eax,eax': the entry value is dead, not an integer argument
        if reads and int_ev is None and ins.id in (
                CX.X86_INS_CMP, CX.X86_INS_TEST, CX.X86_INS_AND, CX.X86_INS_OR, CX.X86_INS_IMUL,
                CX.X86_INS_SHL, CX.X86_INS_SHR, CX.X86_INS_SAR, CX.X86_INS_MOVZX, CX.X86_INS_MOVSX):
            int_ev = (a, text)              # compare/mask/scale of the value: an integer argument
                                            # (bare add/sub is left ambiguous: it is also pointer arithmetic)
        if writes and not reads:
            aliases -= writes               # overwritten: the entry value cannot be used after this
            if not aliases:
                break
        elif ins.id == CX.X86_INS_MOV and len(ops) == 2 and ops[0].type == CX.X86_OP_REG \
                and ops[1].type == CX.X86_OP_REG and GPR32.get(ops[1].reg) in aliases:
            aliases.add(GPR32[ops[0].reg])  # a copy keeps the value live in the destination
        if ins.group(capstone.CS_GRP_CALL):
            aliases -= {"eax", "ecx", "edx"}    # caller-saved: the callee clobbers them
            if not aliases:
                break
        if ins.group(capstone.CS_GRP_RET) or ins.id in (CX.X86_INS_JMP, CX.X86_INS_RET):
            break
        a += ins.size
    if int_ev:
        return "int", int_ev[0], int_ev[1]
    return "unknown", entry, "copied only"


def abi_fix(reg, kind, addr, text):
    """The concrete declaration change for a register argument: which register and which type."""
    what = {"pointer": "a pointer (the original addresses memory through it at %08x: %s)" % (addr, text),
            "int": "an integer (the original does arithmetic/compare on it at %08x: %s)" % (addr, text),
            "unknown": "a value (the original copies it at %08x: %s)" % (addr, text)}[kind]
    how = {"ecx": "make it a thiscall member (this arrives in ecx) or __fastcall with that first parameter",
           "edx": "declare it __fastcall with that pointer as the second parameter (the first would be in ecx)",
           "eax": "no MSVC declaration passes an argument in eax (an LTCG-only register argument; run with --ignore-abi)"}[reg]
    return "%s in %s: %s" % (what, reg, how)


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
        t.ret_width = getattr(sg, "ret_width", None)
        t.conv = conv
    else:
        n = t.callee_pop // 4 if t.callee_pop else 6
        kinds = ["soup"] * n
        t.ret_kind = "unknown"
        t.conv = "stdcall?" if t.callee_pop else "cdecl?"
        notes.append("no parsed signature: %d soup stack dwords" % n)
    t.abi_mismatch = None
    declared = set(regk)
    for r in ("ecx", "edx", "eax"):
        if r in t.entry_reads and r not in regk:
            regk[r] = "soup"
            notes.append("original reads %s at entry (register argument?)" % r)
            if sg is not None and sg.params is not None:
                kind, at, text = reg_arg_use(t.orig_insns, t.va, r)
                t.abi_mismatch = "original reads %s at entry but our declaration passes nothing there " \
                                 "(custom/LTCG register ABI?); fix: pass %s" % (r, abi_fix(r, kind, at, text))
    # A file-static helper on both sides with cl-chosen register conventions (the interpreter's validators: the
    # original takes the value pointer in eax / ecx / edi, our copy in another register): when each side reads
    # exactly one undeclared register at entry, the input's value goes into both (reg_map), so the two builds
    # receive the same argument the way each of them expects it.
    t.reg_map = None
    try:
        allr = ("eax", "ecx", "edx", "ebx", "esi", "edi", "ebp")
        entry_reads(t.orig_insns, t.va, allr, follow_jcc=True)
        o_x = [r for r in entry_reads.order if r not in declared]
        u_ins = RA.our_insns(t.coff, t.fsym)[0]
        u_x = []
        if u_ins:
            entry_reads(u_ins, t.fsym.value, allr, follow_jcc=True)
            u_x = [r for r in entry_reads.order if r not in declared]
    except Exception:           # noqa: BLE001 - the analysis is an aid: without it the row is judged as before
        o_x = u_x = []
    if o_x and len(o_x) == len(u_x) and len(o_x) <= 3:
        # paired in first-read order (check_string_arg 0x49cda0: the original reads the type in ecx then the
        # value in esi, ours eax then edx)
        pairs = []
        for ro, ru in zip(o_x, u_x):
            kind, _at, _text = reg_arg_use(t.orig_insns, t.va, ro)
            regk[ro] = "ptr" if kind == "pointer" else "soup"
            if ro != ru:
                pairs.append((ro, ru))
        t.reg_map = pairs or None
        t.abi_mismatch = None
        notes.append("register arguments: the original reads %s at entry, ours %s; each value goes into both"
                     % ("/".join(o_x), "/".join(u_x)))
    t.void_hides_eax = False
    if t.ret_kind == "void" and getattr(t, "orig_returns_eax", False):
        # Seven hybrid defects (2026-10-12) were `void` declarations of functions whose original
        # hands a value back in eax (hidden return pointer, `return this`, popped node, copy end);
        # LTCG callers use it. Compare eax as an unknown-kind return and say why.
        t.ret_kind = "unknown"
        t.void_hides_eax = True
        notes.append("declared void but the original writes eax before every ret: eax compared (callers may use it)")
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
        n.alloc_fail = tuple(getattr(self, "alloc_fail", ()))
        n.extra = dict(getattr(self, "extra", {}))
        n.forced = dict(getattr(self, "forced", {}))
        return n


NSLOTS = M.POOL_SIZE // M.SLOT
FORCE_SHARE = 0.25     # share of fresh inputs that force one branch-feeding callee's result (Runner._on_forced)
FAULT_EDGE_RUNS = 50   # faulting inputs per row whose edges are recorded (each also runs our build once)
# Image functions whose callers are stubbed by default (Runner._on_stubbed): lookups that end the game when a name is
# not registered, because a test starts with empty managers. Mount & Blade lists its resource-manager lookups here
# (they call mb_error -> exit); Spore has none identified yet (2026-10-29 port).
STUB_LOOKUPS = []
HOT_SLOTS = 8          # slots 0..7 hold the argument / `this` objects


class InputGen:
    """Random inputs ('pointer soup' objects + typed arguments) and their mutations."""

    def __init__(self, t, alias=0.0, nan=False, code=(), fp_real=False, layout=0.0):
        self.t = t
        # layout-driven `this` objects (tools/difftest/layout_inputs.py): a share of fresh inputs get a consistent
        # object of the function's dev-PDB class (vectors over real arrays, empty lists/maps, typed pointers)
        self.layout_p, self.layout_cls = layout, None
        if layout and t.reg_kinds.get("ecx") == "this":
            import layout_inputs
            self.layout_cls = layout_inputs.class_of(t.va if isinstance(t.va, int) else int(str(t.va), 16),
                                                     getattr(t, "sym", None))
            t.layout_notes.append("layout inputs: %s" % (self.layout_cls or "no dev-PDB class found"))
        self.alias = alias
        self.fp_real = fp_real      # --fp-realistic: float fields are finite magnitudes in [1e-3, 1e5]
        self.nan = nan
        # Generated values never point into real code (image .text, our object's code): a soup
        # "method pointer" taken from the original's immediates (a jump target inside the function
        # itself) would otherwise run part of the original on the wrong frame. Such values are
        # moved to the unmapped upper half (bit 31 flipped), where a call becomes a fake method.
        self.code = list(code)
        self.dic = [self.fin(v) for v in (t.dict or [0])]
        self.specials = SPECIAL_F if nan else SPECIAL_F[:8]
        self.invs = []                              # input-object invariants (invariants.py), set by Runner
        self.slot_cache = {}

    def fin(self, v):
        """Unless --nan: never produce a dword whose float32 reading is NaN/Inf (clears the top
        exponent bit), since NaN comparisons are not preserved across equivalent spellings."""
        if not self.nan and (v >> 23) & 0xFF == 0xFF:
            v &= 0xFF7FFFFF
        for lo, hi in self.code:
            if lo <= v < hi:
                return v ^ 0x80000000
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
        if k == "rand" and self.fp_real and rng.random() < 0.5:
            return f2u(self.freal(rng))
        if k == "float" and self.fp_real:
            return f2u(self.freal(rng))
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

    @staticmethod
    def freal(rng):
        """--fp-realistic float: exact 0/+-1 (10%) or +-10^U(-3, 5), the magnitudes of camera/transform data."""
        if rng.random() < 0.1:
            return rng.choice((0.0, 1.0, -1.0))
        return rng.choice((-1.0, 1.0)) * 10.0 ** rng.uniform(-3, 5)

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
        for lo, hi in self.code:
            w[(w >= lo) & (w < hi)] ^= np.uint32(0x80000000)
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
        if kind == "rand" and self.fp_real:
            w = rng.integers(0, 1 << 32, n, dtype=np.int64)
            sel = rng.random(n) < 0.5
            return np.where(sel, self._freal_n(rng, n), w)
        if kind == "float" and self.fp_real:
            return self._freal_n(rng, n)
        if kind == "float":
            r = rng.random(n)
            f = np.where(r < 0.6, rng.uniform(-4, 4, n),
                         np.where(r < 0.85, rng.uniform(-1000, 1000, n), rng.choice(SPECIAL_F[:8], n)))
            return f.astype(np.float32).view(np.uint32).astype(np.int64)
        if kind == "dict":
            return np.array(self.dic, dtype=np.int64)[rng.integers(0, len(self.dic), n)]
        return rng.integers(0, 1 << 32, n, dtype=np.int64)

    def _freal_n(self, rng, n):
        mag = 10.0 ** rng.uniform(-3, 5, n)
        f = np.where(rng.random(n) < 0.5, -mag, mag)
        f = np.where(rng.random(n) < 0.1, rng.choice([0.0, 1.0, -1.0], n), f)
        return f.astype(np.float32).view(np.uint32).astype(np.int64)

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
        if k == "float" and self.fp_real:
            return f2u(self.freal(rng))
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
        for r in ("ebx", "esi", "edi", "ebp"):          # a register argument outside eax/ecx/edx (reg_map)
            k = self.t.reg_kinds.get(r)
            if k:
                inp.regs[r] = self.scalar(k, rng, inp.profile, 1)
        inp.xmm = []
        for _ in range(8):
            v = 0
            for j in range(4):
                v |= f2u(rng.uniform(-10, 10)) << (32 * j)
            inp.xmm.append(v)
        inp.overrides = {}
        if self.layout_cls and rng.random() < self.layout_p:
            import layout_inputs
            this = M.POOL_BASE + M.SLOT * 1
            inp.regs["ecx"] = this
            over = layout_inputs.build_this(rng, self.fin, self.layout_cls, this, M.POOL_BASE, M.SLOT)
            inp.pool_over.update(over)
            inp.touched = sorted(set(a & ~0xFFF for a in over))
            inp.origin = "layout"
        inp.alloc_fail = ()
        inp.extra = {}
        inp.forced = {}
        cands = getattr(self, "force_cands", ())
        if cands and rng.random() < FORCE_SHARE:
            inp.forced[rng.choice(cands)] = rng.choice((0, 1))
        for h in getattr(self, "hints", ()):            # --hint: soft pins, fresh inputs only
            h(self, inp, rng)
        if self.invs:
            INV.enforce(self.invs, self, inp, rng)      # keep the object's length field within its array
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
                r = rng.choice(["eax", "ecx", "edx"] + [x for x in ("ebx", "esi", "edi", "ebp")
                                                         if self.t.reg_kinds.get(x)])
                k = self.t.reg_kinds.get(r)
                if k:
                    inp.regs[r] = self.scalar(k, rng, inp.profile, {"ecx": 1, "edx": 7, "eax": 6}.get(r, 1))
        if self.invs:
            # a mutation can drop the length field back out of range (or swap the object pointer): put the
            # governed fields back in range so the mutant stays a usable input rather than being discarded.
            INV.enforce(self.invs, self, inp, rng)
        return inp


PROFILE_KW = {k: tuple(zip(*v)) for k, v in PROFILES.items()}


# ====================================================================== running

REGS = {"eax": UC_X86_REG_EAX, "ecx": UC_X86_REG_ECX, "edx": UC_X86_REG_EDX, "ebx": UC_X86_REG_EBX,
        "esi": UC_X86_REG_ESI, "edi": UC_X86_REG_EDI, "ebp": UC_X86_REG_EBP}
CALLEE_SENTINEL = {UC_X86_REG_EBX: 0x0BB0BB00, UC_X86_REG_ESI: 0x05150515, UC_X86_REG_EDI: 0x0D1D0D1D,
                   UC_X86_REG_EBP: 0x0E0B0E0B}
STACK_FILL = b"\xcc"
STACK_END = M.STACK_TOP + 0x1000           # end of the stack mapping (one guard-free page above the top)

# --call-regs: the whole live register file at a call site (the GPRs the trace already compares, plus the
# first four xmm registers). NEVER compared by default: a call is compared through its callee, this/edx and
# stack arguments, so intermediate register state that reaches no call, store or return is invisible.
# Values that are not data: MSVC's uninitialised-stack fills and the sentinels a build leaves in a register that
# never carried an input. A register difference against one of these is a dead value, not a divergence.
FILL_PATTERNS = frozenset((0xCCCCCCCC, 0xCDCDCDCD, 0xDDDDDDDD, 0xFDFDFDFD, 0x0BB0BB00, 0x0D1D0D1D,
                           0xBAADF00D, 0xFEEEFEEE, 0xABABABAB, 0xDEADBEEF))

# ---------------------------------------------------------------------- unobserved memory
# A dword that NEITHER build wrote during the run says nothing about equivalence: its two values are
# whatever the machine happened to hold (MSVC's uninitialised-stack fill, a frame slot the two compilers
# place differently, a pool page one side materialised and the other never touched). `--uninit-mem`
# (default ON) drops those dwords from the memory comparison, but only when the ORIGINAL's value is
# recognisably such a leftover - one of FILL_PATTERNS, a byte/word broadcast of one, or a fill pattern
# with only its low 16 bits perturbed (the `cls_map` 0x4d99d0 / `config` 0x4bd4d0 evidence: an
# uninitialised stack byte copied into an object field). Anything else stays a real mismatch, and a
# dword OUR side wrote is never excused, so a genuine difference cannot hide behind this.
# The bytes that are evidence of an MSVC *stack fill* specifically: 0xCC is what cl stamps over the
# uninitialised frame, and these are the four bytes the fill-pattern dwords are made of. A byte that
# merely happens to be the low byte of a sentinel dword (0x00 from 0x0BB0BB00, 0x0D from 0xBAADF00D) is
# NOT evidence of anything: treating 0x00 that way excused "the original zeroes a dword our build never
# stores", which is one of the commonest real divergences (see the ticket in docs/Papercuts.md).
FILL_BYTES = frozenset((0xCC, 0xCD, 0xDD, 0xFD))


def unobserved_fill(v, base):
    """v (the original's value) is a fill/sentinel leftover: v itself is one of FILL_PATTERNS (a dword a
    build stamped), or `v` differs from the bytes it had when the run started (`base`, the input the run
    was handed) in exactly ONE byte, and that byte is an MSVC stack-fill byte (0xCC/0xCD/0xDD/0xFD). That second case is the `cls_map`/`config`
    evidence: `movb 0xf(%esp),%cl; movb %cl,0x44(%esi)` copies ONE uninitialised stack byte (0xCC) over
    the low byte of a float the input/argument already carried, so the dword shares its other bytes with
    `base` and only the 0xCC bytes are new. A dword OUR build wrote is refused by the caller before this
    is consulted, so a real difference cannot pass through here."""
    if v in FILL_PATTERNS:
        return True
    try:
        b = struct.pack("<I", base & 0xFFFFFFFF)
    except (struct.error, TypeError):
        return False
    n = struct.pack("<I", v & 0xFFFFFFFF)
    if n == b:
        return False                    # unchanged: no fill byte was introduced
    diff = [(x, y) for x, y in zip(n, b) if x != y]
    if len(diff) != 1:
        return False                    # a partial copy moves ONE byte (0xCC over a frame byte)
    return diff[0][0] in FILL_BYTES


class MemWrites:
    """Per-run record of every dword at least one build wrote (see the unobserved-memory rule above).

    One bytearray of flags per region page, kept on the Runner (`write_flags_reg`), 0 = the run never
    wrote that dword, 1 = it did. Required for the pool (which the machine maps lazily and never diffs)
    and harmless everywhere else, so a write the hook misses only makes the harness compare MORE dwords -
    it can never hide a difference.
    """

    def __init__(self, r):
        self.r = r
        self.on = bool(getattr(r.opts, "uninit_mem", True))
        self.h = None

    def start(self):
        if not self.on or self.h is not None:
            return
        uc = self.r.m.uc
        self.h = [uc.hook_add(UC_HOOK_MEM_WRITE, self._on_write, begin=lo, end=hi - 1)
                  for lo, hi in self._spans()]

    def close(self):
        for h in self.h or ():
            self.r.m.uc.hook_del(h)
        self.h = None

    def _spans(self):
        out = [(M.POOL_BASE, M.POOL_BASE + M.POOL_SIZE)]
        for _nm, lo, hi in self.r.m.writable:
            out.append((lo, hi))
        for base, size in getattr(self.r, "mapped_extra", ()) or ():
            out.append((base, base + size))
        return out

    def _on_write(self, uc, access, address, size, value, _):
        self.mark(address, max(int(size), 1))

    @property
    def own_dwords(self):
        """Dwords the code itself stored (emulated stores), excluding harness-side handler writes."""
        s = getattr(self, "_own", None)
        if s is None:
            s = self._own = set()
        return s

    @property
    def dwords(self):
        """The set of dword addresses THIS run wrote so far (per-run: cleared by reset()). Filled by the
        emulated-store hook and by `mark` (Machine.write: an import handler's or the input setup's write).
        The class-3 rule subtracts these from what the ORIG pass wrote before it excuses a dword as stub
        scaffold, so a dword our own pass writes is never excused."""
        s = getattr(self, "_dwords", None)
        if s is None:
            s = self._dwords = set()
        return s

    def mark(self, addr, nbytes, via_import=False):
        """Flag the dwords [addr, addr+nbytes) as written by this run. `via_import` marks a write the
        harness performed on the program's behalf (an import handler's buffer fill, the input setup):
        it still counts as "this run wrote it" for the unobserved-memory rule (a dword a handler wrote is
        not a leftover), but NOT as a store the code itself made, which is the set the stub-scratch trim
        subtracts (a stub's own buffer must remain excusable)."""
        if self.on:
            self.r.mark_written(addr, nbytes)
            d = self.dwords.update(range(addr & ~3, (addr + max(int(nbytes), 1) + 3) & ~3, 4))
            if not via_import:
                self.own_dwords.update(range(addr & ~3, (addr + max(int(nbytes), 1) + 3) & ~3, 4))
            return d
        return None

    def reset(self):
        """Forget this run's per-dword write set. The region flag tables are Runner.reset_writes' job, and
        that method calls this one, so this must not call back into it."""
        self._dwords = set()
        self._own = set()


CALL_XMM = ("xmm0", "xmm1", "xmm2", "xmm3")
CALL_REG_IDS = {"eax": UC_X86_REG_EAX, "ebx": UC_X86_REG_EBX, "ecx": UC_X86_REG_ECX, "edx": UC_X86_REG_EDX,
                "esi": UC_X86_REG_ESI, "edi": UC_X86_REG_EDI, "ebp": UC_X86_REG_EBP, "esp": UC_X86_REG_ESP}
CALL_XMM_IDS = {"xmm%d" % k: UC_X86_REG_XMM0 + k for k in range(len(CALL_XMM))}


def call_reg_snapshot(uc):
    """The register file at a call site (--call-regs): {name: int}, xmm as the full 128-bit value."""
    snap = {r: uc.reg_read(i) for r, i in CALL_REG_IDS.items()}
    snap.update({r: uc.reg_read(i) for r, i in CALL_XMM_IDS.items()})
    return snap


class ImportTrace(list):
    """machine.py records one import call as (name, args) and appends it here. With --call-regs the register
    file at that call is captured in the same order: the append happens inside machine's import hook, so the
    values are the ones at the stub entry."""

    def __init__(self, uc, regs):
        super().__init__()
        self.uc, self.regs = uc, regs

    def append(self, ent):
        list.append(self, ent)
        self.regs.append(call_reg_snapshot(self.uc))


class Side:
    """One installed function (original or ours): entry, ranges, call-site hooks."""

    def __init__(self, name, entry, ranges, sites, cfg=None, span=None):
        self.name, self.entry, self.ranges, self.sites = name, entry, ranges, sites
        self.cfg, self.span = cfg, span         # edge model and [lo, hi) of the tested function itself
        self.edges = set()                      # edges covered by valid runs
        self.site_hits, self.site_returned, self.site_stops = {}, {}, {}

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
        # the relink's content-matched vtables (work/relink/resolve_map.json): an address difference between
        # our vtable and the image's is a link-time fact, so same_local_copy compares the SLOT TARGETS through
        # this match instead of raw bytes. Loaded once per process.
        self.vt_match = _vtable_match_table()
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
        # (section index, offset) -> defining symbol name, for the vtable-match rule's ours-side lookup
        self.r_syms_by_off = {((sy.secno or 0), sy.value): sy.name for sy in t.coff.syms.values()}
        self.our_insns = {}
        self.code_cache = {}      # image function start -> (sorted addrs, insns) for fake-call arity
        self.targets_cache = {}   # id(insns) -> addresses a branch/call in that code lands on (block starts)
        self.fakes = []
        self.orig = Side("orig", t.va, [(t.orig_lo, t.orig_hi)], self._sites_orig(), t.orig_cfg, (t.orig_lo, t.orig_hi))
        self.ours = Side("ours", obj["entry"], obj["code"], self._sites_ours(), self._cfg_ours(), obj["func_range"])
        for side in (self.orig, self.ours):
            side.cfg_static_unreachable = {e for e, k in side.cfg.x87_facts().items() if k == "infeasible" or not opts.nan}
        self.hooks = []
        self.cur = None
        self.calls = []
        # Original's instruction cap: starts low (random inputs often send a loop into the
        # billions) and rises to --budget if a probe shows a real input needs more; see run_function.
        self.budget = min(getattr(opts, "start_budget", opts.budget), opts.budget)
        for side in (self.orig, self.ours):
            for a, info in side.sites.items():
                self.hooks.append(m.uc.hook_add(UC_HOOK_CODE, self._on_site, user_data=(side, info), begin=a, end=a))
        # --transparent: image functions whose call is replaced in the depth-1 trace by the calls they make
        self.transparent = set(getattr(opts, "transparent", None) or ()) | set(getattr(opts, "transparent_auto", None) or ())
        self.tr_stack, self.tr_block = [], None
        for tva in sorted(self.transparent):
            lo, hi = self.img.func_extent(tva)
            code = self.img.read(lo, hi - lo)
            insns, _ = R.recursive_descent(lambda a, k, lo=lo, code=code: code[a - lo:a - lo + k], lo, hi, tva, lambda a: None)
            for a, ins in insns.items():
                if ins.id == CX.X86_INS_CALL or (ins.id == CX.X86_INS_JMP and not self._jmp_internal(ins, lo, hi)):
                    self.hooks.append(m.uc.hook_add(UC_HOOK_CODE, self._on_tsite, user_data=self._site_info(ins, self.img.read),
                                                    begin=a, end=a))
                    r = a + ins.size
                    self.hooks.append(m.uc.hook_add(UC_HOOK_CODE, self._on_tret, begin=r, end=r))
        # --stub (default STUB_LOOKUPS): image functions both builds call that return an input object instead of
        # running; see _on_stubbed
        self.stubbed = {}
        for sva in sorted(set(getattr(opts, "stub", None) or ()) - {t.va}):
            try:
                lo, hi = self.img.func_extent(sva)
                code = self.img.read(lo, hi - lo)
                insns, _ = R.recursive_descent(lambda a, k, lo=lo, code=code: code[a - lo:a - lo + k], lo, hi, sva,
                                               lambda a: None)
            except Exception:
                continue
            pops = {ins.operands[0].imm if ins.operands else 0 for ins in insns.values() if ins.id == CX.X86_INS_RET}
            if len(pops) != 1:
                continue                                # no single return convention: leave it running
            self.stubbed[sva] = pops.pop()
            self.hooks.append(m.uc.hook_add(UC_HOOK_CODE, self._on_stubbed, user_data=self.stubbed[sva],
                                            begin=sva, end=sva))
        # branch-feeding callees whose result an input may force (see _on_forced)
        self.cur_forced = {}
        self.forced_cands = []
        if getattr(opts, "force_results", True):
            # only callees our object calls too, at the same image address: a forced result the other build cannot
            # see (ours inlined the callee, or runs its own copy of it) is a difference the harness made
            # (inventory_panel 0x5134c0 inlines test_slot_flag 0x5126e0)
            ours_calls = None
            try:
                _ou, _rel, _data = RA.our_insns(t.coff, t.fsym)
                ours_calls = set()
                for _off, (_si, _typ) in _rel.items():
                    if _typ == RA.REL_REL32 and _si in t.res.addr:
                        ours_calls.add(t.res.addr[_si] & 0xFFFFFFFF)
            except Exception:
                ours_calls = None
            order = sorted(t.orig_insns)
            for k_, a_ in enumerate(order[:-2]):
                ins = t.orig_insns[a_]
                if ins.id != CX.X86_INS_CALL or ins.operands[0].type != CX.X86_OP_IMM:
                    continue
                tgt = ins.operands[0].imm & 0xFFFFFFFF
                nxt = t.orig_insns.get(a_ + ins.size)
                if nxt is None or not self.img.in_text(tgt) or tgt in self.transparent or tgt in self.stubbed:
                    continue
                tests_result = nxt.id == CX.X86_INS_TEST and nxt.op_str in ("al, al", "eax, eax") or \
                    nxt.id == CX.X86_INS_CMP and nxt.op_str.startswith(("eax, ", "al, "))
                if tests_result and tgt not in self.forced_cands and (ours_calls is None or tgt in ours_calls):
                    self.forced_cands.append(tgt)
            for tgt in self.forced_cands:
                self.hooks.append(m.uc.hook_add(UC_HOOK_CODE, self._on_forced, begin=tgt, end=tgt))
        self.blocks = set()
        self.run_blocks = set()
        self.fault_edges, self.fault_runs = {"orig": set(), "ours": set()}, []
        self.page_cache = {}
        code = [(a, a + n) for nm, a, n, ch in self.img.sections if ch & 0x20000000]
        self.gen = InputGen(t, opts.alias, opts.nan, code + list(obj["code"]), getattr(opts, "fp_realistic", False),
                           getattr(opts, "layout", 0.0))
        # Input-object invariants (class-2 harness artefacts): the length fields of the objects this row
        # walks, with the declared capacity of the array they index. Attached once per row; `--no-invariants`
        # leaves the list empty and the generator/comparison behave exactly as before.
        self.gen.invs = INV.specs_for(t.sid, t.va, not getattr(opts, "no_invariants", False))
        self.gen.force_cands = list(self.forced_cands)
        # --edge-scope: the original's edges this run is about (one case of a switch): the run continues past
        # --inputs and steers only for these; coverage is still reported for the whole function
        self.edge_scope = None
        if getattr(opts, "edge_scope", None):
            self.edge_scope = {tuple(int(x, 16) for x in e.split("->")) for e in json.load(open(opts.edge_scope))}
        self.gen.hints = [INV.hint(h) for h in (getattr(opts, "hint", None) or [])]
        if getattr(opts, "pin", None):                  # --pin: not an invariant of the type, never disabled
            self.gen.invs = self.gen.invs + [INV.pin_invariant(p) for p in opts.pin]
        self.cov_on = False
        self.cov_side = None
        self.prev_end = None
        self.run_edges = set()
        self.last_site = None
        self.run_sites = {}
        self.reads = None
        for side in (self.orig, self.ours):
            self.hooks.append(m.uc.hook_add(UC_HOOK_BLOCK, self._on_block, user_data=side,
                                            begin=side.span[0], end=side.span[1] - 1))
        nst = len(t.stack_kinds) + 4
        self.frame_dw = nst
        self.esp_entry = M.STACK_TOP - 0x2000 - 4 * (1 + nst)
        self.esp_entry &= ~0xF
        self.esp_entry -= 4         # as after a call from 16-aligned code
        self.args_hi = self.esp_entry + 4 * (1 + nst)
        # The function owns its incoming argument slots (callers never read them back, compilers
        # reuse them as scratch), so pointers into them count as stack pointers ("STK") like
        # pointers into the frame. The 4 padding dwords above them belong to the caller.
        self.stk_hi = self.esp_entry + 4 + 4 * len(t.stack_kinds)
        # read-only constants (image .rdata, our object's code/constants): pointers to byte-identical
        # contents compare equal (the same literal pooled at two addresses)
        self.ro = [(a, a + n) for nm, a, n, ch in self.img.sections if nm == ".rdata"]
        self.ro += [(lo, hi) for lo, hi in m.readonly if obj["map_lo"] <= lo < obj["map_hi"]]
        # --uninit-mem: which dwords each run wrote (see MemWrites). Keyed by page, entry: bytearray of
        # one flag per dword; a stack region is a single long buffer, a pool page only exists once mapped.
        self.writes = MemWrites(self)
        self.write_flags_reg = {}       # (label, base) -> (baseline, flags)
        self.region_of = self._region_map()
        self.writes.start()             # --uninit-mem: per-dword write flags for pool/.data/extras
        # the DYN dwords the ORIGINAL's code itself stored this pass (emulated stores; import handlers write
        # through Machine.write, which no hook sees): the class-3 baseline injects everything else
        self.heap_stores = set()
        self.hooks.append(m.uc.hook_add(UC_HOOK_MEM_WRITE, self._on_heap_store,
                                        begin=M.DYN_BASE, end=M.DYN_BASE + M.DYN_SIZE - 1))
        if self.writes.on:
            m.mark_written = self.mark_written     # machine.write() reports handler/input-setup writes here
        # --- class 3 (symmetric baseline): the pass that follows must start from the heap/misc/stub state
        # the first pass started from. `self.baseline` is that state, captured at the end of the ORIG pass
        # (its leftover heap, the image pages it wrote, and the stub scratch); `self.mapped_extra` lists the
        # extra regions currently mapped, so the pool/extra page input of a later run is restored exactly.
        self.baseline = None                    # {"heap": {page: bytes}, "img": {section: {page: bytes}},
                                                #  "extra": [[base, size]], "inp_extra": {base: size}}
        self.mapped_extra = []                  # [[base, size]] of the fault-repair regions now mapped
        self.injected = set()                   # class-3 heap pages written into the current pass
        self.trimmed = {}                       # (label, page) -> {dword addr: 0} dropped as stub scratch
        self.uncompared = {}                    # (label, page, dword addr) -> stub name: never compared
        self.runs = 0                           # passes run for the row (diagnostics)

    def _region_map(self):
        """[(lo, hi, label, is_page)] for every range the run can write and the comparison looks at.
        `is_page`: the range is addressed in 4 KB pages (pool / heap / misc / extra); otherwise the
        region is one buffer starting at `lo` (the stack, an image section, our object's data)."""
        t, m, obj = self.t, self.m, self.obj
        out = [(M.POOL_BASE, M.POOL_BASE + M.POOL_SIZE, "pool", True),
               (M.DYN_BASE, M.DYN_BASE + M.DYN_SIZE, "heap", True),
               (M.MISC_BASE, M.MISC_BASE + M.MISC_SIZE, "misc", True)]
        for nm, lo, hi in m.writable:
            out.append((lo, hi, ".data" if nm == ".data" else nm, False))
        for base, size in sorted(getattr(self, "mapped_extra", ()) or ()):
            out.append((base, base + size, "extra", True))
        out.append((M.STACK_TOP - M.STACK_SIZE - 0x1000, M.STACK_TOP + 0x1000, "stack", False))
        return out

    def _addr_region(self, addr):
        """(label, base, is_page) of the writable region `addr` falls in, or (None, None, False)."""
        for lo, hi, label, is_page in self.region_of:
            if lo <= addr < hi:
                return label, (addr & ~0xFFF if is_page else lo), is_page
        return None, None, False

    def write_flags(self, addr):
        """The write flags of the region page holding `addr`: a bytearray with one flag per dword, or
        None when the run is not allowed to say anything about that address."""
        if not self.writes.on:
            return None
        label, base, _is_page = self._addr_region(addr)
        if label is None:
            return None
        ent = self.write_flags_reg.get((label, base))
        if ent is None:
            n = (min(self._region_hi(label, base), base + 0x1000) - base) // 4
            ent = self.write_flags_reg[(label, base)] = (self._region_baseline(label, base), bytearray(n))
        return ent[1]

    def _region_hi(self, label, base):
        for lo, hi, lbl, is_page in self.region_of:
            if lbl == label and (lo == base or (is_page and base <= lo < base + 0x1000)):
                return hi
        return base + 0x1000

    def _region_baseline(self, label, base):
        """The bytes the run started from for one region page (used only to recognise a dword a run wrote
        before the flags existed - i.e. the input the pool hands the program). None when unknowable."""
        m = self.m
        if label == "pool":
            return m.pool_pages.get(base)
        if label in ("heap", "misc") or label == "extra":
            return None                     # DYN/misc are zeroed / restored between runs; extra is per run
        if label == "stack":
            return None
        try:
            return m.image_base_page(label, base)
        except (StopIteration, KeyError):
            return None

    def mark_written(self, addr, nbytes):
        """Flag the dwords [addr, addr+nbytes) as written by the current run (machine.write, the input
        setup, and the pool page loader all funnel here)."""
        w = self.writes
        if not w.on:
            return
        for page in range(addr & ~0xFFF, addr + max(int(nbytes), 1), 0x1000):
            f = self.write_flags(page)
            if f is None:
                continue
            k0, k1 = page + 0, page + 0x1000
            k0, k1 = max(addr, k0), min(addr + max(int(nbytes), 1), k1)
            for k in range((k0 - page) & ~3, k1 - page, 4):
                if (k >> 2) * 4 == k:
                    f[k >> 2] = 1

    def note_pool_page(self, page, data):
        """The lazy loader is about to hand the program `data` as pool page `page`: record it as that
        page's baseline, so a dword neither build wrote is recognisable as untouched."""
        if not self.writes.on:
            return
        base = page & ~0xFFF
        self.put_flags("pool", base, bytes(data), bytearray(len(data) // 4))

    def put_flags(self, label, base, baseline, flags, is_page=True):
        """Register the write flags of one region page/buffer and make its range addressable (pool and
        fault-repair `extra` pages only exist once the run has materialised them). A page the other side
        already wrote keeps its flags: the rule is "at least one side wrote it", so a later registration
        must not clear them."""
        old = self.write_flags_reg.get((label, base))
        if old is not None and len(old[1]) == len(flags):
            flags = bytearray(max(a, b) for a, b in zip(old[1], flags))
            baseline = baseline if baseline is not None else old[0]
        self.write_flags_reg[(label, base)] = (baseline, flags)
        if is_page:
            self.region_of = [(lo, hi, lbl, ip) for lo, hi, lbl, ip in self.region_of
                              if not (lbl == label and base <= lo < base + 0x1000)]
            self.region_of.append((base, base + 4 * len(flags), label, True))

    def reset_writes(self):
        """Start a fresh input: forget every write the previous input's two passes made. Called from
        run_side for the ORIGINAL pass only, so the rule sees writes from both sides of one input."""
        self.write_flags_reg = {}
        self.region_of = self._region_map()
        # The per-dword set is the OTHER half of the same rule (`MemWrites.dwords`, used by the stub-scratch
        # trim): it must cover the orig and ours passes of ONE input, not the whole row, or the trim would
        # subtract dwords written by some earlier input's ours pass (and it grew unboundedly).
        if getattr(self, "writes", None) is not None:
            self.writes.reset()

    # --- class 3: leftover scratch the original wrote through a do-nothing stub
    def slot_symbol(self, va):
        """Name of the symbol our object defines at `va`, or None. COMDATs (/Gy) make every function its own
        section, so the lookup is a scan by (section number, offset), not an index."""
        obj = self.obj
        if obj is None or not isinstance(va, int):
            return None
        for si, base in (obj.get("sec_addr") or {}).items():
            sec = self.t.coff.sections[si]
            if base <= va < base + len(sec.data):
                off = va - base
                best = None
                for sy in self.t.coff.syms.values():
                    if (sy.secno or 0) != si or sy.value != off:
                        continue
                    nm = sy.name or ""
                    if nm.startswith(".") or nm.startswith("$"):
                        continue            # a section symbol (.text, .debug$F), not the function
                    if nm.startswith(("?", "_", "@")) or nm[:1].isalpha():
                        best = nm
                        break
                return best
        return None

    def slot_is_undefined(self, va):
        """True when our slot target is a place our object does not define (an undefined external's slot, or an
        address with no COFF symbol): the virtual's body lives in another module's TU, so a single-row compile
        cannot see it. "Cannot tell", not "differs"."""
        obj = self.obj
        if obj is None or not isinstance(va, int):
            return True
        if va in (obj.get("map_lo"), 0):
            return True
        return self.slot_symbol(va) is None

    def res_name(self, va):
        """Name identity of a vtable slot target for the vtable-match rule: for an image address, the name the
        relink knows for it (resolve_map `defined_at`); for an address in OUR object, the symbol we define there.
        None when the address has neither (an unresolved or unnamed slot)."""
        tbl = _res_name_table()
        n = tbl.get(va)
        if n is not None:
            return _norm_sym(n)
        nm = self.slot_symbol(va)
        return _norm_sym(nm) if nm else None

    def page_of(self, addr):
        """(label, page) of the region a compared page address belongs to ('heap', 'misc', '.data', ...)."""
        for lo, hi, label, _page in self.region_of:
            if lo <= addr < hi:
                return label
        return None

    def _stub_spans(self, page):
        """[(lo, hi)] of the buffers the do-nothing stubs of this run were handed, clipped to `page`:
        the handler's declared span when it has one, else the whole page of the buffer argument (the
        same fallback _stub_only uses to attribute an address)."""
        out = []
        for name, args in list(getattr(self.m, "trace_imports", ()) or ()):
            h = self.m.handlers.get(name)
            if h is None or h.get("fn") is not None:
                continue                    # a real handler's writes are evidence, not scaffold
            span = h.get("span")
            for a in args:
                if not isinstance(a, int):
                    continue
                lo, hi = (a, a + span) if span else (a & ~0xFFF, (a & ~0xFFF) + 0x1000)
                lo, hi = max(lo, page), min(hi, page + 0x1000)
                if lo < hi:
                    out.append((lo, hi))
        return out

    def _trim_stub_scratch(self, side, pages, page, written, other=None, label="heap"):
        """Mark the dwords of one dirty page that ONE run wrote through a do-nothing stub and the other
        left alone.

        `written` is the dword set the excusal is attributed to (on OURS' pages the inherited ORIGINAL
        writes, on the ORIGINAL's pages its own pass's writes), `other` the set of the opposite pass
        (None on the orig pass, which runs first and cannot know ours' writes yet - safe, because any
        later ours-side write into the region still shows as a difference on ours' page). A differing
        dword is scaffold only when ALL of these hold; when in doubt the difference is kept:
        - `written` contains it (a dword this pass's attribution never wrote stays compared);
        - `other` does not (both passes wrote it: a joint product, never scaffold);
        - no buffer a do-nothing stub of this run was handed INTERSECTS `other` at the span containing
          the address (the other build stores into a stub buffer: the buffer is a joint product and
          every dword of it stays compared - the guard test test_equiv.py
          ::test_stub_scratch_never_excuses_a_dword_our_build_wrote is exactly this case);
        - `_stub_only` attributes the address to exactly one do-nothing stub.
        The value is replaced by the page baseline so the comparison sees nothing there; the count is
        reported in the verdict reason and every excused dword is named in `uncompared`."""
        if page not in pages:
            return
        if written is None:
            return
        spans = self._stub_spans(page)
        buf = bytearray(pages[page])
        base = self._region_baseline(label, page) or b"\0" * 0x1000
        n = 0
        for i in range(0, len(buf) - 3, 4):
            if buf[i:i + 4] == base[i:i + 4]:
                continue
            addr = page + i
            if addr not in written:
                continue        # a dword this pass's attribution did not write: the other pass's
                                # business, or a real difference - never scaffold
            if other is not None and addr in other:
                continue        # both passes wrote the address: a joint product
            if other is not None and any(not other.isdisjoint(range(lo, hi, 4))
                                         for lo, hi in spans if lo <= addr < hi):
                continue        # the other pass wrote inside this buffer: the whole buffer stays compared
            who = self._stub_only(addr)
            if not who:
                continue
            buf[i:i + 4] = base[i:i + 4]
            n += 1
            self.uncompared[(label, page, addr)] = who
        if n:
            pages[page] = bytes(buf)
            key = (label, page)
            self.trimmed[key] = n
            self.tolerated["stub-scratch"] = self.tolerated.get("stub-scratch", 0) + n

    def _stub_only(self, addr):
        """Name of the do-nothing import handler when EVERY import call this run recorded that reaches
        `addr` as a buffer argument is a stub (fn is None: sprintf, strcpy, ...), else None.

        `addr` must actually be inside a buffer the stub was handed (the previous form ignored it and
        excused any address in the run as soon as one stub with one int argument existed)."""
        m = self.m
        names = set()
        for name, args in list(getattr(m, "trace_imports", ()) or ()):
            h = m.handlers.get(name)
            if h is None or h.get("fn") is not None:
                continue                    # a real handler (memcpy, malloc, a modelled function): not a stub
            span = h.get("span")            # handlers are dicts: getattr(h, "span") was always None
            if span and any(isinstance(a, int) and a <= addr < a + span for a in args):
                names.add(name)
                break
            if span is None and any(isinstance(a, int) and (a & ~0xFFF) == (addr & ~0xFFF) for a in args):
                names.add(name)             # no declared buffer length: fall back to the same page
                break
        if len(names) != 1:
            return None
        return names.pop()

    def _stub_fence(self, addr):
        """Name of the do-nothing stub that "owns" a page no compared run wrote, else None. Only DYN and
        MISC pages, where a stub's only footprint is where its buffer happened to be; a pool/extra page
        that only our run touched is real evidence and stays compared."""
        r = getattr(self, "_lastref", None)
        if not r:
            return None
        region = self.page_of(addr)
        if region not in ("heap", "misc"):
            return None
        names = set()
        for name, args in list(getattr(self.m, "trace_imports", ()) or ()):
            h = self.m.handlers.get(name)
            if h is None or h.get("fn") is not None:
                continue
            for a in args:
                if isinstance(a, int) and ((a & ~0xFFF) == (addr & ~0xFFF)):
                    names.add(name)
        return names.pop() if len(names) == 1 else None

    def close(self):
        for h in self.hooks:
            self.m.uc.hook_del(h)
        self.hooks = []
        self.writes.close()

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

    def _cfg_ours(self):
        """Edge model of OUR tested function (its own COMDAT section, from its entry)."""
        m, obj, coff = self.m, self.obj, self.t.coff
        lo, hi = obj["func_range"]
        i = self.t.fsym.secno - 1
        a0 = obj["sec_addr"][i]
        relpos = {a0 + off for off, _si, typ in coff.sections[i].relocs if typ in (0x06,)}

        def rd(a, n):
            return m.read(a, min(n, hi - a))

        def tt(a):
            if a in relpos:
                v = m.u32(a)
                return v if lo <= v < hi else None
            return None
        insns, _tb = R.recursive_descent(rd, lo, hi, obj["entry"], tt)
        self.ours_func_insns = insns
        return CF.Cfg(insns, obj["entry"], lo, hi, tt)

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
    def _on_block(self, uc, address, size, side):
        if not self.cov_on or side is not self.cov_side:
            return
        self.run_blocks.add((address, size))
        pe = self.prev_end
        if pe is not None:
            br = side.cfg.branch_end.get(pe)
            if br is not None:
                src, kind, fall = br
                if kind == "jcc":
                    tgt = side.cfg.insns[src].operands[0].imm & 0xFFFFFFFF
                    self.run_edges.add((src, fall) if address == fall else (src, tgt))
                elif (src, address) in side.cfg.edges:
                    self.run_edges.add((src, address))
        self.prev_end = address + size

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

    def wild_eip(self, why):
        """The fault text names an eip inside an image function that is not one of its instructions (cached
        recursive descent per function), i.e. the run was executing garbage reached through a soup pointer."""
        import re
        m_ = re.search(r"eip=([0-9a-fA-F]{8})", str(why))
        if not m_:
            return False
        eip = int(m_.group(1), 16)
        if not self.img.in_text(eip):
            return False
        import bisect
        starts = getattr(self.img, "starts", None)
        if not starts:
            return False
        f = starts[max(0, bisect.bisect_right(starts, eip) - 1)]
        cache = self.__dict__.setdefault("_decoded", {})
        if f not in cache:
            try:
                lo, hi = self.img.func_extent(f)
                code = self.img.read(lo, hi - lo)
                insns, _ = R.recursive_descent(lambda x, k: code[x - lo:x - lo + k], lo, hi, f, lambda x: None)
                cache[f] = set(insns) if lo <= eip < hi else None
            except Exception:
                cache[f] = None
        return cache[f] is not None and eip not in cache[f]

    def _on_heap_store(self, uc, access, address, size, value, _):
        if self.cur is self.orig:
            self.heap_stores.update(range(address & ~3, (address + max(int(size), 1) + 3) & ~3, 4))

    def _on_site(self, uc, address, size, data):
        side, info = data
        if side is not self.cur:
            return
        if side.span[0] <= address < side.span[1]:
            self.last_site = address
            self.run_sites[address] = self.run_sites.get(address, 0) + 1
            # executing the tested function itself: every transparent call has returned. The esp test below
            # cannot see that when this call pushes arguments the transparent one did not (the original's
            # register-argument check_party 0x49d160, then set_lvalue's two pushes): the stale frame made
            # set_lvalue's inner report() calls depth 1 on the original's side only
            self.tr_stack.clear()
        tgt = self._eval_target(info["ins"])
        if tgt is None:
            return
        if side.inside(tgt) or M.STUB_BASE <= tgt < self.m.stub_end:
            return
        if self._thunk(tgt):
            return
        esp = uc.reg_read(UC_X86_REG_ESP)
        while self.tr_stack and esp >= self.tr_stack[-1]:
            self.tr_stack.pop()                         # transparent calls that already returned
        self.tr_block = None                            # (also after a transparent function's tail jump)
        if tgt in self.transparent:
            self.tr_stack.append(esp)
            return
        self._record_call(uc, tgt, info, esp)

    def _on_tsite(self, uc, address, size, info):
        """A call inside a --transparent function: recorded as depth 1 when every frame between the tested
        function and this call is transparent (not inside a recorded callee)."""
        if self.cur is None:
            return
        esp = uc.reg_read(UC_X86_REG_ESP)
        while self.tr_stack and esp >= self.tr_stack[-1]:
            self.tr_stack.pop()
        if not self.tr_stack or self.tr_block is not None:
            return
        tgt = self._eval_target(info["ins"])
        if tgt is None or self._thunk(tgt):
            return
        if tgt in self.transparent:
            self.tr_stack.append(esp)
            return
        self.tr_block = esp
        self._record_call(uc, tgt, info, esp)

    def _on_tret(self, uc, address, size, data):
        """Return address of a call inside a transparent function: the recorded callee has returned."""
        if self.tr_block is not None and uc.reg_read(UC_X86_REG_ESP) >= self.tr_block:
            self.tr_block = None

    def _record_call(self, uc, tgt, info, esp):
        try:
            words = struct.unpack("<8I", self.m.read(esp, 32))
        except Exception:
            words = (0,) * 8
        self.calls.append((tgt, uc.reg_read(UC_X86_REG_ECX), uc.reg_read(UC_X86_REG_EDX), words,
                           info["add_esp"], info["is_jmp"]))
        if self.opts.call_regs:
            self.call_regs.append(call_reg_snapshot(uc))

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

    def callee_arg_widths(self, va):
        """{stack argument index: bytes the callee reads of it} for arguments it only ever reads narrower than a
        dword (a char/short/bool parameter: tstring::push_back 0x42be70 reads `mov al, [esp+8]`). The caller's
        other bytes of that slot are whatever the register or stack slot held (ini_file::parse_line 0x4bd4d0
        stores the char into the low byte of its own `line` argument slot and pushes the whole dword), so they
        are not compared. Static and conservative: every path of the callee is walked with esp tracked through
        push/pop/sub/add and direct calls (their ret N), or every [ebp+8+4k] access of a `push ebp; mov ebp, esp`
        frame; an argument read as a dword or address-taken (lea) anywhere is full width, and anything the walk
        cannot follow (an indirect call/jmp, another esp write, paths joining at different esp) gives {}."""
        cache = self.__dict__.setdefault("_argw_cache", {})
        if va in cache:
            return cache[va]
        cache[va] = {}
        if not self.img.in_text(va):
            return {}
        try:
            lo, hi = self.img.func_extent(va)
            if lo != va:
                return {}
            code = self.img.read(lo, hi - lo)
            insns, _ = R.recursive_descent(lambda a, k: code[a - lo:a - lo + k], lo, hi, va, lambda a: None)
        except Exception:
            return {}
        seen = {}

        def note(off, size, full):
            if off >= 0:
                k = off // 4
                seen[k] = max(seen.get(k, 0), 4 if full or off % 4 else size)
        first = [insns[a] for a in sorted(insns)[:2]] if len(insns) >= 2 else []
        ebp_frame = len(first) == 2 and first[0].mnemonic == "push" and first[0].op_str == "ebp" and \
            first[1].mnemonic == "mov" and first[1].op_str == "ebp, esp"
        if ebp_frame:
            for i in insns.values():
                for o in i.operands:
                    if o.type == CX.X86_OP_MEM and o.mem.base == CX.X86_REG_EBP and not o.mem.index and o.mem.disp >= 8:
                        note(o.mem.disp - 8, o.size, i.id == CX.X86_INS_LEA)
        else:
            at, work = {}, [(va, 0)]                    # address -> esp delta when reached (esp - entry esp)
            while work:
                a, d = work.pop()
                while True:
                    if a in at:
                        if at[a] != d:
                            return {}
                        break
                    i = insns.get(a)
                    if i is None:
                        return {}
                    at[a] = d
                    for o in i.operands:
                        if o.type == CX.X86_OP_MEM and o.mem.base == CX.X86_REG_ESP and not o.mem.index:
                            note(o.mem.disp + d - 4, o.size, i.id == CX.X86_INS_LEA)
                    m_, nxt = i.mnemonic, a + i.size
                    if m_ == "ret":
                        break
                    if m_ == "push":
                        d -= 4
                    elif m_ == "pop":
                        if i.operands[0].type == CX.X86_OP_REG and i.operands[0].reg == CX.X86_REG_ESP:
                            return {}
                        d += 4
                    elif m_ in ("sub", "add") and i.operands[0].type == CX.X86_OP_REG and \
                            i.operands[0].reg == CX.X86_REG_ESP:
                        if i.operands[1].type != CX.X86_OP_IMM:
                            return {}
                        d += -i.operands[1].imm if m_ == "sub" else i.operands[1].imm
                    elif m_ == "call":
                        if i.operands[0].type != CX.X86_OP_IMM:
                            return {}
                        d += 4 * (self.callee_arity(i.operands[0].imm) or 0)
                    elif m_ == "jmp":
                        if i.operands[0].type != CX.X86_OP_IMM:
                            return {}
                        nxt = i.operands[0].imm
                        if not (lo <= nxt < hi):
                            break                       # tail call: the arguments go on to its callee
                    elif m_.startswith("j") or m_.startswith("loop"):
                        if i.operands[0].type == CX.X86_OP_IMM:
                            work.append((i.operands[0].imm, d))
                    elif i.operands and i.operands[0].type == CX.X86_OP_REG and \
                            i.operands[0].reg == CX.X86_REG_ESP and i.operands[0].access & capstone.CS_AC_WRITE:
                        return {}                       # mov/lea/and esp, ...: not tracked
                    a = nxt
        cache[va] = {k: w for k, w in seen.items() if w < 4}
        return cache[va]

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
        if any(o[nm] != o.get("entry_cs", {}).get(nm, CALLEE_SENTINEL[r]) for nm, r in M.CALLEE_SAVED):
            return False
        return o["esp"] == 4 + self.t.callee_pop

    def in_ro(self, v):
        return any(lo <= v < hi for lo, hi in self.ro)

    def norm_key(self, v):
        """Run-independent identity of a value for hashing: stack pointers -> 'STK', pointers to
        read-only constants -> their contents (C string, else 64 bytes)."""
        if in_stack_frame(v, self.stk_hi):
            return "STK"
        if self.in_ro(v):
            try:
                b = self.m.read(v, 64)
            except Exception:
                return v
            z = b.find(b"\0")
            return ("RO", b[:z] if z > 0 else b)
        return v

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
                    return struct.unpack_from("<I", code, a - lo)[0] \
                        if (a in rel or not self.img.relocs) and lo <= a <= hi - 4 else None
                insns, _ = R.recursive_descent(rd, lo, hi, f, tt)
                self.code_cache[f] = (sorted(insns), insns)
            return self.code_cache[f]
        return None

    def block_starts(self, addrs, insns):
        """Addresses a branch or call in this code can land on: the start of a basic block. `addrs[0]`
        (the function's entry in the image) is a block start too. Attributed here once per code blob."""
        key = id(insns)
        t = self.targets_cache.get(key)
        if t is None:
            t = {addrs[0]} if addrs else set()
            for ins in insns.values():
                if ins.id == CX.X86_INS_CALL or ins.group(capstone.CS_GRP_JUMP):
                    if ins.operands and ins.operands[0].type == CX.X86_OP_IMM:
                        t.add(ins.operands[0].imm & 0xFFFFFFFF)
            self.targets_cache[key] = t
        return t

    def site_arity(self, ret):
        """Stack dwords a call ending at `ret` passes: pushes (and 'sub esp,N' slots) walking back
        from the call to the previous call/branch/stack adjustment. None if not determinable.
        The walk stays inside the call's own basic block: the pushes of a loop's prologue (or of the
        funclet/parent function the site was inlined into) belong to a different path, and counting
        them fabricated 6 arguments for a 1-argument vtable call in a loop (write_soa 0x4e9640)."""
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
        starts = self.block_starts(addrs, insns)
        n = 0
        j = i - 1
        if addrs[i] not in starts:
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
                if addrs[j] in starts:
                    break                   # this instruction starts the block: earlier ones are another path
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
        if ar is None and ret == M.SENTINEL and esp == self.esp_entry:
            # a tail call through a pointer (`jmp [eax+0x68]` with the tested function's frame gone): the target
            # takes over the tested function's own arguments and returns to its caller (mission_3 0x48d7e0)
            ar = (len(self.t.stack_kinds), bool(self.t.callee_pop))
        if ar is None:
            return ("fake-arity", "no call site before %08x" % ret)
        n, pops = ar
        args = []
        for k in range(n):
            args.append(self.norm_key(m.u32(esp + 4 + 4 * k)))
        ecx = self.norm_key(uc.reg_read(UC_X86_REG_ECX))
        h = zlib.crc32(repr((target, ecx, args, getattr(self, "fake_salt", 0))).encode())
        k = h % 4
        eax = (0, 1, h % 9, M.POOL_BASE + M.SLOT * (HOT_SLOTS + (h >> 8) % (NSLOTS - HOT_SLOTS)))[k]
        if self._bool_result(ret):
            # the caller tests the return value as a flag (`test al,al`): a do-nothing method reports
            # "the check failed" (0), the answer that lets the caller's error path run instead of
            # sending it into work the method was supposed to do (cam_view 0x4eaa05: the model-record
            # check gates the clipboard copy, whose GlobalAlloc is not modelled)
            eax = 0
        self.fakes.append((target, n, ecx, tuple(args)))
        if self.opts.call_regs:
            self.fake_regs.append(call_reg_snapshot(uc))
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

    def _on_forced(self, uc, address, size, _):
        """Entry of a callee whose result this input forces (Input.forced {va: value}): return it without running
        the callee. The candidates are the image functions the original calls directly and whose result its next
        instruction tests (`call f; test al, al; jcc`): a branch on a predicate of game state the input cannot
        easily build (party_2 0x4b25c0 on 0x435740). Both builds call the same image function, and the depth-1
        trace still compares the call and its arguments, so the forced value is one more environment both are
        measured in: the callee treated as an uninterpreted function."""
        if self.cur is None or address not in self.cur_forced:
            return
        m = self.m
        esp = uc.reg_read(UC_X86_REG_ESP)
        try:
            ret = m.u32(esp)
        except Exception:
            return
        n = self.callee_arity(address) or 0
        uc.reg_write(UC_X86_REG_EAX, self.cur_forced[address] & 0xFFFFFFFF)
        uc.reg_write(UC_X86_REG_EDX, 0)
        uc.reg_write(UC_X86_REG_ESP, esp + 4 + 4 * n)
        uc.reg_write(UC_X86_REG_EIP, ret)

    def _on_stubbed(self, uc, address, size, pops):
        """Entry of a --stub function: return an input object without running it. These are the resource lookups
        that end the game when a name is missing (resmgr::get_object 0x419540 -> mb_error -> exit): a test's
        resource manager is empty, so every input that reached one ended at exit() (quest_log 0x4ee910: 30/30).
        Both builds call the same image function, so the depth-1 trace still compares the call and its
        arguments; the object returned is a pool slot chosen by (callee, this, arguments) like a fake call's,
        the same object on both sides."""
        if self.cur is None:
            return
        m = self.m
        esp = uc.reg_read(UC_X86_REG_ESP)
        try:
            ret = m.u32(esp)
        except Exception:
            return
        n = pops // 4 if pops else ((self.site_arity(ret) or (0, False))[0])
        try:
            args = [self.norm_key(m.u32(esp + 4 + 4 * k)) for k in range(n)]
        except Exception:
            return
        ecx = self.norm_key(uc.reg_read(UC_X86_REG_ECX))
        h = zlib.crc32(repr(("stub", address, ecx, args)).encode())
        self.fakes.append((address, n, ecx, tuple(args)))
        uc.reg_write(UC_X86_REG_EAX, M.POOL_BASE + M.SLOT * (HOT_SLOTS + (h >> 8) % (NSLOTS - HOT_SLOTS)))
        uc.reg_write(UC_X86_REG_ESP, esp + 4 + pops)
        uc.reg_write(UC_X86_REG_EIP, ret)

    def _bool_result(self, ret):
        """True if the first instruction after the call tests the return value against itself
        (`test al,al` / `test eax,eax`): a method used as a boolean predicate."""
        try:
            ins = next(_md.disasm(self.m.read(ret, 16), ret, 1))
        except Exception:
            return False
        if ins.id != CX.X86_INS_TEST or len(ins.operands) != 2:
            return False
        return all(op.type == CX.X86_OP_REG for op in ins.operands) and \
            ins.operands[0].reg == ins.operands[1].reg

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

    def uninit_copies(self, inp, max_steps=3_000_000):
        """Dword addresses whose content, at the end of the ORIGINAL's run of inp, is a plain copy of a stack slot
        below the entry esp that this run has not written since the slot last became live (an uninitialised local,
        whatever a returned callee's frame left there): the original's value there is
        indeterminate, so a different value in ours is not a difference. The class: a vector4 built by the
        3-argument constructor (w never set) and passed or stored by value (editor_ui 0x4f5fb0 copies its colour's
        w into the mesh; obj_tbl 0x499050 copies Frame3 rows' w). Copy-only taint: a value is tainted when
        loaded from such a slot (or from tainted memory) and moved unchanged by mov / push / pop / fld / fst(p), or
        shifted by a constant (inc / dec, add / sub of an immediate, lea reg, [reg + disp]: a leftover plus a constant
        is still indeterminate -- trigger_vec 0x4bf170 stores a D3D out-parameter the generated callee never wrote,
        minus 1), or, on the x87 stack, shifted by a memory operand (fadd / fsub / fsubr m32/m64); any other
        instruction (multiplies, compares, register-register x87 ops) makes what it writes untainted."""
        m, uc = self.m, self.m.uc
        lo_s, entry = M.STACK_TOP - M.STACK_SIZE, self.esp_entry
        written, tainted = set(), set()
        regt, fpu, pend, steps = {}, [], [False], [0]
        movs = [None]       # esi - edi of the string copy in progress: its writes take their source bytes' taint
        last_esp = [entry]
        cache = {}

        def src_taint(a, n):
            return all((b in tainted) or (lo_s <= b < entry and b not in written) for b in range(a, a + n))

        def ea(o):
            mm = o.mem
            a = mm.disp
            if mm.base:
                a += uc.reg_read(CS2UC[mm.base]) if mm.base in CS2UC else 0
            if mm.index:
                a += (uc.reg_read(CS2UC[mm.index]) if mm.index in CS2UC else 0) * mm.scale
            return a & 0xFFFFFFFF

        def full(r):
            return CX.X86_REG_EAX if r in (CX.X86_REG_AX, CX.X86_REG_AL) else r

        def on_code(uc_, address, size, _):
            steps[0] += 1
            if self.cur is not self.orig or steps[0] > max_steps:
                return
            ins = cache.get(address)
            if ins is None:
                try:
                    ins = cache[address] = next(_md.disasm(bytes(uc_.mem_read(address, size)), address))
                except Exception:
                    return
            ops, mn = ins.operands, ins.mnemonic
            if mn.startswith("rep "):
                mn = mn[4:]                 # capstone spells the prefix into the mnemonic ("rep movsd")
            pend[0] = False
            movs[0] = None
            esp_now = uc_.reg_read(UC_X86_REG_ESP)
            if esp_now > last_esp[0]:
                # the bytes esp just rose past belong to a frame that has returned: dead again, so a later read
                # of one (before this function writes it) is an uninitialised read
                for b in range(last_esp[0], min(esp_now, last_esp[0] + 0x10000)):
                    written.discard(b)
            last_esp[0] = esp_now
            try:
                if mn == "mov" and len(ops) == 2 and ops[0].size == 4:
                    d, sop = ops
                    if sop.type == CX.X86_OP_MEM:
                        t = src_taint(ea(sop), 4)
                    elif sop.type == CX.X86_OP_REG:
                        t = regt.get(sop.reg, False)
                    else:
                        t = False
                    if d.type == CX.X86_OP_REG:
                        regt[d.reg] = t
                    else:
                        pend[0] = t
                    return
                if mn.startswith("movs") and mn in ("movsd", "movsb", "movsw") and not ops or \
                        (mn in ("movsd", "movsb", "movsw") and all(o.type == CX.X86_OP_MEM for o in ops)):
                    # string copy: every written byte takes its own source byte's taint (the code hook can run
                    # once for a whole rep movs, so the taint is resolved per write from the esi - edi delta)
                    movs[0] = (uc_.reg_read(UC_X86_REG_ESI) - uc_.reg_read(UC_X86_REG_EDI)) & 0xFFFFFFFF
                    return
                if mn == "push" and ops:
                    o = ops[0]
                    pend[0] = (regt.get(o.reg, False) if o.type == CX.X86_OP_REG else
                               src_taint(ea(o), 4) if o.type == CX.X86_OP_MEM else False)
                    return
                if mn == "pop" and ops and ops[0].type == CX.X86_OP_REG:
                    regt[ops[0].reg] = src_taint(uc_.reg_read(UC_X86_REG_ESP), 4) and \
                        uc_.reg_read(UC_X86_REG_ESP) in tainted
                    return
                if mn in ("inc", "dec") and ops and ops[0].size == 4:
                    if ops[0].type == CX.X86_OP_REG:
                        return                                  # the register keeps its taint
                    if ops[0].type == CX.X86_OP_MEM:
                        pend[0] = src_taint(ea(ops[0]), 4)
                        return
                if mn in ("add", "sub") and len(ops) == 2 and ops[0].type == CX.X86_OP_REG and ops[0].size == 4 \
                        and ops[1].type == CX.X86_OP_IMM:
                    return                                      # reg +- constant keeps its taint
                if mn == "lea" and len(ops) == 2 and ops[0].type == CX.X86_OP_REG and ops[1].mem.base \
                        and not ops[1].mem.index:
                    regt[ops[0].reg] = regt.get(ops[1].mem.base, False)
                    return
                if mn == "fld" and ops and ops[0].type == CX.X86_OP_MEM and ops[0].size == 4:
                    fpu.append(src_taint(ea(ops[0]), 4))
                    return
                if mn in ("fadd", "fsub", "fsubr") and len(ops) == 1 and ops[0].type == CX.X86_OP_MEM \
                        and ops[0].size in (4, 8):
                    # st0 +- a memory operand: a leftover shifted by any amount is still indeterminate
                    # (note_window 0x50a1c0 adds 0.001 and a panel size to a local the original never sets)
                    if fpu:
                        fpu[-1] = fpu[-1] or src_taint(ea(ops[0]), ops[0].size)
                    return
                if mn in ("fst", "fstp") and ops and ops[0].type == CX.X86_OP_MEM and ops[0].size == 4:
                    pend[0] = fpu[-1] if fpu else False
                    if mn == "fstp" and fpu:
                        fpu.pop()
                    return
                # anything else: what it writes is untainted (registers here, memory through on_write)
                for r_ in ins.regs_access()[1]:
                    regt.pop(r_, None)
                    regt.pop(full(r_), None)
                if mn.startswith("f"):
                    fpu[:] = []                  # x87 stack effects not modelled: forget (untainted)
            except Exception:
                pend[0] = False

        def on_write(uc_, access, address, size, value, _):
            if self.cur is not self.orig:
                return
            for b in range(address, address + size):
                t_ = src_taint((b + movs[0]) & 0xFFFFFFFF, 1) if movs[0] is not None else pend[0]
                if lo_s <= b < entry + 0x1000:
                    written.add(b)
                if t_:
                    tainted.add(b)
                else:
                    tainted.discard(b)

        hs = [uc.hook_add(UC_HOOK_CODE, on_code), uc.hook_add(UC_HOOK_MEM_WRITE, on_write)]
        try:
            self.run_side(self.orig, inp)
        finally:
            for h in hs:
                uc.hook_del(h)
        if steps[0] > max_steps:
            return frozenset()
        # bytes, not dwords: a copy to an unaligned destination (cam widget + 0x1ac from a soup pointer) straddles
        # dwords, so the comparison excuses a dword whose differing bytes are all tainted (Comparer.uninit_excused)
        return frozenset(a for a in tainted if not (lo_s <= a < entry))

    def _traced_reads(self, inp):
        """[(address, dword)] of every 4-byte read the original makes from an input buffer, the
        argument area or image .data, in order (the last matching one is the most recent)."""
        m = self.m
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
        return reads

    def _put_dword(self, out, addr, val):
        """Store val into the input location at addr: a pool object field, an incoming argument slot,
        or an image .data dword (an override both sides start from). None for an address the input
        does not own (read-only constants/tables are not writable)."""
        if M.POOL_BASE <= addr < M.POOL_BASE + M.POOL_SIZE:
            if addr & 3:
                return None
            out.pool_over[addr] = val
        elif self.esp_entry + 4 <= addr < self.args_hi:
            k = (addr - self.esp_entry - 4) // 4
            if addr & 3:
                return None
            if k < len(out.args):
                out.args[k] = val
            else:
                out.pad[k - len(out.args)] = val
        elif self.m.in_image_writable(addr):
            out.overrides[addr] = val
        else:
            return None
        return out

    def _redirect(self, reads, out, val, newp, depth=0):
        """Store newp into the input dword that carried `val`. When that dword is not writable as one
        (a pool address that is not 4-aligned, a read-only table), follow the chain one level: the
        pointer that led to it is an input dword (cam_view 0x4eaa05: [this+0x188] -> unaligned soup
        address -> 0xd -> call [0xd+0x44])."""
        for addr, v in reversed(reads):
            if v != val:
                continue
            if val == 0 and self.m.in_image_writable(addr):
                continue            # a zero global is an empty container/NULL constant, not the input's
            r = self._put_dword(out, addr, newp)
            if r is not None:
                return r
            if depth < 2 and addr != val:
                r = self._redirect(reads, out, addr, newp, depth + 1)
                if r is not None:
                    return r
        return None

    def _reg_def(self, eip, reg, window=12):
        """The last instruction before eip (same straight-line block) that writes `reg`: the instruction
        that built the faulting address."""
        got = self._insns_around(eip - 1)
        if not got:
            return None
        addrs, insns = got
        import bisect
        i = bisect.bisect_left(addrs, eip) - 1
        j = i
        while j >= 0 and i - j < window:
            ins = insns[addrs[j]]
            if j + 1 >= len(addrs) or ins.address + ins.size != addrs[j + 1]:
                break
            try:
                _r, w = ins.regs_access()
            except capstone.CsError:
                w = []
            if reg in w:
                return ins
            if ins.group(capstone.CS_GRP_JUMP) or ins.group(capstone.CS_GRP_CALL) or ins.id == CX.X86_INS_RET:
                break
            j -= 1
        return None

    def scaled_factor(self, eip, reg):
        """The factor N>1 by which `imul reg, reg, N` / `shl reg, N` scaled reg just before eip, or
        None: an array index that the faulting access multiplied by its element size (cam_view
        0x4ea8fd: `imul eax,eax,0x1f8` then `mov ebp,[eax+ecx+0x3c]`)."""
        ins = self._reg_def(eip, reg)
        if ins is None:
            return None
        ops = ins.operands
        if ins.id == CX.X86_INS_IMUL and len(ops) == 3 and ops[0].type == CX.X86_OP_REG and \
                ops[0].reg == reg and ops[1].type == CX.X86_OP_REG and ops[1].reg == reg and \
                ops[2].type == CX.X86_OP_IMM and ops[2].imm > 1:
            return ops[2].imm & 0xFFFFFFFF
        if ins.id == CX.X86_INS_SHL and len(ops) == 2 and ops[0].type == CX.X86_OP_REG and \
                ops[0].reg == reg and ops[1].type == CX.X86_OP_IMM and 0 < ops[1].imm < 32:
            return 1 << ops[1].imm
        return None

    def repair(self, inp, fault, rng, attempt=0):
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
        reads = self._traced_reads(inp)

        # The faulting instruction's base register is the bad pointer V (exactly, if it was
        # loaded unchanged); otherwise fall back to "some value up to 64K below A".
        base_v = idx_v = None
        base_reg = None
        try:
            eip = fault_eip
            ins = next(_md.disasm(m.read(eip, 16), eip, 1))
            for op in ins.operands:
                if op.type == CX.X86_OP_MEM:
                    if op.mem.base and op.mem.base in CS2UC:
                        base_v = fault_regs.get(op.mem.base)
                        base_reg = op.mem.base
                    if op.mem.index and op.mem.index in CS2UC:
                        idx_v = fault_regs.get(op.mem.index)
                    break
        except Exception:
            base_v = idx_v = base_reg = None
        newp = M.POOL_BASE + M.SLOT * (HOT_SLOTS + rng.randrange(NSLOTS - HOT_SLOTS))
        out = inp.copy()

        def put(addr, val):
            return self._put_dword(out, addr, val)

        def mapped(v):
            return v is not None and (M.POOL_BASE <= v < M.POOL_BASE + M.POOL_SIZE or self.img.in_image(v) or
                                      M.DYN_BASE <= v < M.DYN_BASE + M.DYN_SIZE or
                                      M.STACK_TOP - M.STACK_SIZE <= v < STACK_END)
        # 0. a NULL(+offset) access after an allocation the input made fail, or after 8 repairs that did
        # not get past it: map the null page instead of redirecting yet another zero dword
        if kind in ("read", "write") and A < 0x10000 and (getattr(inp, "alloc_fail", ()) or attempt >= 8) \
                and 0 not in out.extra and self._mappable(0, M.SLOT) and not getattr(self.opts, "no_extra_map", False):
            out.extra[0] = M.SLOT
            return out
        # 1. the bad base pointer, loaded unchanged
        if base_v is not None and not mapped(base_v):
            r = self._redirect(reads, out, base_v, newp)
            if r is not None:
                return r
            for k, v in enumerate(out.args):
                if v == base_v:
                    out.args[k] = newp
                    return out
            for r, v in out.regs.items():
                if v == base_v:
                    out.regs[r] = newp
                    return out
        # 1c. the base register is an index the code scaled by the element size (`imul eax,eax,0x1f8`
        # before `mov [eax+ecx+0x3c]`): the dword it came from is a garbage array index, so resample it
        # small instead of writing a pointer into it and faulting the same way 24 times
        if base_v is not None and not mapped(base_v) and base_reg is not None and A >= 0x10000:
            mul = self.scaled_factor(fault_eip, base_reg)
            if mul:
                for addr, v in reversed(reads):
                    if (v * mul) & 0xFFFFFFFF == base_v:
                        if v == 0 and self.m.in_image_writable(addr):
                            continue    # an index of 0 is indistinguishable from a NULL global pointer
                        r = self._put_dword(out, addr, rng.randrange(4))
                        if r is not None:
                            return r
                for k, v in enumerate(out.args):
                    if (v * mul) & 0xFFFFFFFF == base_v:
                        out.args[k] = rng.randrange(4)
                        return out
        # 1b. a NULL that no input dword carried (an empty global container, a call that returned 0):
        # rewriting some zero .data dword would corrupt the program's own state (mesh_appear 0x4822ac:
        # the resmgr's empty registry vector), so map the null page and let the input soup decide
        if A < 0x10000 and 0 not in out.extra and \
                self._mappable(0, M.SLOT) and not getattr(self.opts, "no_extra_map", False):
            out.extra[0] = M.SLOT
            return out
        # 2. a good base with a garbage index: make the index small
        if idx_v is not None and (base_v is None or mapped(base_v)) and idx_v > 0x100:
            for addr, v in reversed(reads):
                if v == idx_v:
                    return put(addr, rng.randrange(4))
            for k, v in enumerate(out.args):
                if v == idx_v:
                    out.args[k] = rng.randrange(4)
                    return out
        # 3. a pointer loaded and then offset (lea/add) before the access: up to 64K below it
        ref = base_v if base_v is not None and not mapped(base_v) else A
        for addr, v in reversed(reads):
            if 0 <= (ref - v) & 0xFFFFFFFF < 0x10000:
                return put(addr, newp)
        for k, v in enumerate(out.args):
            if 0 <= (ref - v) & 0xFFFFFFFF < 0x10000:
                out.args[k] = newp
                return out
        for r, v in out.regs.items():
            if 0 <= (ref - v) & 0xFFFFFFFF < 0x10000:
                out.regs[r] = newp
                return out
        # 4. no traceable source (a computed or constant address): map input memory at the fault
        if kind in ("read", "write") and len(out.extra) < 4 and not getattr(self.opts, "no_extra_map", False):
            for base, size in ((A & ~(M.SLOT - 1), M.SLOT), (A & ~0xFFF, 0x1000)):
                if self._mappable(base, size):
                    out.extra[base] = size
                    return out
        return None

    def _call_before(self, ret):
        """The `call` instruction whose return address is ret, or None."""
        got = self._insns_around(ret - 1)
        if not got:
            return None
        addrs, insns = got
        import bisect
        i = bisect.bisect_left(addrs, ret) - 1
        if i < 0:
            return None
        ins = insns[addrs[i]]
        if ins.id != CX.X86_INS_CALL or ins.address + ins.size != ret:
            return None
        return ins

    def pure_call_site(self):
        """(vtable pointer, slot address, return address) of the indirect call the run stopped in
        _purecall from, or None. The pure-call stub is reached by one `call [reg(+disp)]` whose
        slot holds the stub: `reg` is the object's vtable pointer (or the object itself, for a
        function-pointer member), and the slot is the abstract method that was called."""
        m = self.m
        try:
            ret = m.u32(m.uc.reg_read(UC_X86_REG_ESP))
        except Exception:
            return None
        ins = self._call_before(ret)
        if ins is None or not ins.operands:
            return None
        op = ins.operands[0]
        if op.type != CX.X86_OP_MEM:
            return None
        regs = {cs: m.uc.reg_read(u) for cs, u in CS2UC.items()}
        base = regs.get(op.mem.base, 0) if op.mem.base else 0
        idx = regs.get(op.mem.index, 0) if op.mem.index else 0
        slot = (base + idx * op.mem.scale + op.mem.disp) & 0xFFFFFFFF
        return base, slot, ret

    def repair_heap(self, inp, why, rng):
        """The original ran the emulated heap out (64 MB): a size or element count it read from the input is a
        soup value no game state holds (mesh_hud 0x498420: 321 of 400 inputs; quest_log 0x4ee910: 37 of 100).
        Shrink the input dword that carried it: the most recent one the failed size is a small multiple of
        (an element count times its stride, or the byte size itself) or a few bytes more than (quest_log:
        a string length + 1), else the most recent large non-pointer
        value (a loop count over small allocations). Returns the repaired input or None."""
        mm = re.search(r"\((\d+) bytes\)", str(why))
        size = int(mm.group(1)) if mm else 0
        reads = self._traced_reads(inp)

        def pointer(v):
            return (M.POOL_BASE <= v < M.POOL_BASE + M.POOL_SIZE or self.img.in_image(v) or
                    M.DYN_BASE <= v < M.DYN_BASE + M.DYN_SIZE or M.STACK_TOP - M.STACK_SIZE <= v < STACK_END)
        pick = None
        for addr, v in reversed(reads):
            # the size is the value times a stride, or the value plus a small header/terminator (a string length
            # + 1); a soup value used as a length is often a pool address, so pointers are not excluded here
            if v >= 0x1000 and size and (size % v == 0 and size // v <= 0x1000 or 0 <= size - v <= 0x40):
                pick = addr
                break
        if pick is None:
            for addr, v in reversed(reads):
                if 0x10000 <= v and not pointer(v):
                    pick = addr
                    break
        if pick is None:
            return None
        return self._put_dword(inp.copy(), pick, rng.choice((0, 1, 2, 3, 4, 8, 16, rng.randrange(64))))

    def repair_pure(self, inp, rng):
        """The original stopped in _purecall: an indirect call read a vtable slot that is still the
        pure-call stub (an interface object the game would have initialised, or a slot the input
        never set). Resample, from the same input soup the rest of the arguments come from, the dword
        that carried the vtable pointer -- an argument slot, a pool object's vtable field or an image
        .data global -- and, when that dword is not the input's, the slot itself. Returns the
        resampled input or None; the caller keeps the first attempt that gets past the pure call."""
        site = self.pure_call_site()
        if site is None:
            return None
        vptr, slot, _ret = site
        reads = self._traced_reads(inp)
        out = inp.copy()
        newp = M.POOL_BASE + M.SLOT * (HOT_SLOTS + rng.randrange(NSLOTS - HOT_SLOTS))
        for addr, v in reversed(reads):         # the dword the vtable pointer was loaded from
            if v == vptr:
                r = self._put_dword(out, addr, newp)
                if r is not None:
                    return r
        for k, v in enumerate(out.args):        # ... or an argument/register that carried it
            if v == vptr:
                out.args[k] = newp
                return out
        for r, v in out.regs.items():
            if v == vptr:
                out.regs[r] = newp
                return out
        # the vtable pointer is a constant table (no input source): resample the slot that is still
        # the stub, when the input owns it (a pool object's vtable field, or an image .data table)
        return self._put_dword(out, slot, newp)

    def _mappable(self, base, size):
        """True if [base, base+size) is free address space outside the harness's own regions."""
        if base + size > M.TRAP_BASE or M.OBJ_BASE <= base + size and base < M.DYN_BASE + M.DYN_SIZE:
            return False
        for lo, hi, _p in self.m.uc.mem_regions():
            if base <= hi and lo < base + size:
                return False
        return True

    def note_sites(self, side, status, sites, last):
        """Call-site bookkeeping for 'blocked' edges: how often each depth-1 call site returned, and
        how often a run stopped at an unmodelled import (or a handler that cannot go on) inside it."""
        for a, n in sites.items():
            stopped = status[0] != "ok" and a == last
            side.site_hits[a] = side.site_hits.get(a, 0) + n
            side.site_returned[a] = side.site_returned.get(a, 0) + n - (1 if stopped else 0)
        if status[0] == "import" and last is not None and noreturn_stop(status[1]):
            nm = str(status[1]).split(":")[0]
            side.site_stops.setdefault(last, {})
            side.site_stops[last][nm] = side.site_stops[last].get(nm, 0) + 1

    def blocked_calls(self, side):
        """{call site: description} for sites that never returned and stopped at an unmodelled import, a
        C++ throw or a pure virtual call (never an input-dependent handler stop such as a huge malloc)."""
        out = {}
        for a, stops in side.site_stops.items():
            if side.site_returned.get(a, 0) == 0:
                out[a] = "never returned: stopped at %s in all %d runs that reached it" % (
                    "/".join("%s (%s)" % (n, NORETURN_WHY.get(n, "unmodelled import")) for n in sorted(stops)),
                    sum(stops.values()))
        return out

    # --- one run
    def run_side(self, side, inp):
        m, uc, t = self.m, self.m.uc, self.t
        self.cur_forced = getattr(inp, "forced", None) or {}
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
            self.note_pool_page(page, d)        # --uninit-mem: this page's baseline for the write flags
            return d
        m.take_dirty()              # DYN/MISC back to baseline (normally already clean)
        m.lazy = lazy
        if side is self.orig:
            self.reset_writes()     # a new input: the rule needs writes from BOTH passes, so only here
            self.heap_stores = set()
        if self.baseline is not None and side is self.ours:
            # (our pass only: the original's pass of the NEXT input used to be injected with this input's
            # leftover heap, so input N's original run started from input N-1's; a fresh replay of the same
            # input then agreed - add_point_light in the interpreter's case sweep, heap @50004bc0)
            # class 3: the second pass must start from the state the first pass started from. The heap
            # state that pass *left* is restored before the input is laid out, so a page the original's
            # run dirtied through a do-nothing stub holds the same bytes when our pass writes it (or, for
            # a page our pass never writes, the same leftover) -- and a page our pass never dirties is not
            # compared at all. The pool (lazy input) and the fault-repair regions are restored to the bytes
            # they started with, undoing exactly the pages the previous pass materialised.
            for p, data in self.baseline.get("heap", {}).items():
                m.uc.mem_write(p, data)
                self.injected.add(p)        # raw writes are not dirty-tracked: zeroed after this pass
            pages = self.baseline.get("extra")
            if pages is not None and getattr(inp, "extra", None) == self.baseline.get("inp_extra", {}):
                for base, data in pages.items():
                    try:
                        m.uc.mem_write(base, data)
                    except Exception:       # noqa: BLE001  the region is re-mapped just below in any case
                        pass
            for pg in getattr(self, "pool_pages", ()) or ():
                self.page_cache.pop(pg, None)
        m.pool_pages = dict(getattr(self, "pool_pages", ()) or {})
        m.pool_slots = []
        m.pool_entry = set()
        for a_, v_ in inp.overrides.items():
            m.write(a_, struct.pack("<I", v_))
        m.dyn_next = M.DYN_BASE
        m.dyn_sizes = {}
        m.rand_state = 1
        m.ui_seed, m.ui_calls = getattr(inp, "seed", 0) & 0xFFFFFFFF, 0     # user32 query answers (machine.ui_answer)
        m.alloc_fail, m.alloc_count = tuple(getattr(inp, "alloc_fail", ())), 0
        extra_init = {}
        self.mapped_extra = []
        for base, size in sorted(getattr(inp, "extra", {}).items()):
            # memory mapped at a faulting address by fault repair: input soup, compared like pool pages
            m.uc.mem_map(base, size, UC_PROT_READ | UC_PROT_WRITE)
            data = self.gen._slot_soup(inp, base)[:size]
            m.uc.mem_write(base, data)
            self.mapped_extra.append([base, size])
            for k in range(0, size, 0x1000):
                extra_init[base + k] = data[k:k + 0x1000]
                self.put_flags("extra", base + k, data[k:k + 0x1000], bytearray(len(data[k:k + 0x1000]) // 4))
        stk_lo = M.STACK_TOP - M.STACK_SIZE
        m.write(stk_lo, STACK_FILL * (STACK_END - stk_lo))
        frame = struct.pack("<I", M.SENTINEL) + struct.pack("<%dI" % (len(inp.args) + 4), *(inp.args + inp.pad))
        m.write(self.esp_entry, frame)
        regs = dict(CALLEE_SENTINEL)
        for r, v in inp.regs.items():
            regs[REGS[r]] = v
        for ro, ru in getattr(t, "reg_map", None) or ():
            # the same argument in both builds' registers (an input saved before the mapping carries only ours)
            v = inp.regs.get(ro, inp.regs.get(ru))
            if v is not None:
                regs[REGS[ro]] = regs[REGS[ru]] = v
        m.reset_cpu(regs, inp.xmm)
        uc.reg_write(UC_X86_REG_ESP, self.esp_entry)
        entry = {r: uc.reg_read(REGS[r]) for r in RF.GPR_SCRATCH}
        # callee-saved registers as this run starts: their sentinels, unless the input passes an argument in one
        # (reg_map: the original reads edi); the ABI check expects them back at these values
        self.entry_cs = {nm: uc.reg_read(r_) for nm, r_ in M.CALLEE_SAVED}
        for k in range(8):
            entry["xmm%d" % k] = uc.reg_read(UC_X86_REG_XMM0 + k)
        self.fakes, self.calls = [], []
        self.call_regs, self.fake_regs, self.import_regs = [], [], []
        m.trace_imports = ImportTrace(uc, self.import_regs) if self.opts.call_regs else []
        m.fake_handler = (getattr(self, "fake_override", None) or self.fake_call) if self.opts.fake_calls else None
        # salt the fake-call results with the input: the original and ours run the same input, so they still see
        # the same results, but different inputs see different ones. Unsalted, a call that depends only on `this`
        # (Init: `if (!ReadTuningValues()) return false;`) returned the same value for every input and the rest
        # of the function was never reached (2026-10-23)
        self.fake_salt = 0 if getattr(self.opts, "fixed_fakes", False) else inp.seed
        self.tr_stack, self.tr_block = [], None
        self.cur = side
        self.cov_on = True
        self.cov_side = side
        self.prev_end = None
        self.run_edges = set()
        self.last_site = None
        self.run_sites = {}
        self.run_blocks = set()
        budget = self.budget if side is self.orig else self.opts.budget * 4
        t0 = time.time()
        status = m.run(side.entry, None, budget, self.opts.run_seconds * (1 if side is self.orig else 4))
        self.cur = None
        self.cov_on = False
        if status[0] == "ok" and self.prev_end is not None:
            br = side.cfg.branch_end.get(self.prev_end)
            if br is not None and br[1] == "jcc":       # last block ended in a jcc taken out of the function
                src = br[0]
                self.run_edges.add((src, side.cfg.insns[src].operands[0].imm & 0xFFFFFFFF))
        o = {"status": status, "time": time.time() - t0, "fault": m.last_fault}
        o["edges"], o["blocks"] = self.run_edges, self.run_blocks
        o["sites"], o["last_site"] = self.run_sites, self.last_site
        self.note_sites(side, status, self.run_sites, self.last_site)
        o["eax"] = uc.reg_read(UC_X86_REG_EAX)
        o["edx"] = uc.reg_read(UC_X86_REG_EDX)
        o["ecx"] = uc.reg_read(UC_X86_REG_ECX)
        o["entry"] = entry
        o["entry_cs"] = dict(self.entry_cs)
        for k in range(1, 8):
            o["xmm%d" % k] = uc.reg_read(UC_X86_REG_XMM0 + k)
        for nm, r in M.CALLEE_SAVED:
            o[nm] = uc.reg_read(r)
        o["esp"] = (uc.reg_read(UC_X86_REG_ESP) - self.esp_entry) & 0xFFFFFFFF
        fpsw = uc.reg_read(UC_X86_REG_FPSW)
        top = (fpsw >> 11) & 7
        o["fpu_depth"] = (8 - top) % 8
        o["st0"] = uc.reg_read(UC_X86_REG_FP0 + top) if o["fpu_depth"] else None
        # fpcw is only *observed* here; the control word is *set* in machine.py's session-init stub
        # (default 0x007F, --fpcw). The mask drops the reserved bits 6-7 and 13-15 only; precision (bits
        # 8-9) and rounding (bits 10-11) are compared.
        o["fpcw"] = uc.reg_read(UC_X86_REG_FPCW) & 0x1F3F
        o["mxcsr"] = uc.reg_read(UC_X86_REG_MXCSR) & 0xFFC0
        o["xmm0"] = uc.reg_read(UC_X86_REG_XMM0)
        # memory after the run (and undo it)
        mem = m.take_image_dirty()      # only pages written during the run (machine.py write hooks)
        if extra_init:
            o["extra_init"] = extra_init
            mem["extra"] = {}
            for base, size in sorted(inp.extra.items()):
                data = m.read(base, size)
                for k in range(0, size, 0x1000):
                    mem["extra"][base + k] = data[k:k + 0x1000]
                m.uc.mem_unmap(base, size)
        o["pool_init"] = init = dict(m.pool_pages)
        entry = m.pool_entry
        mem["pool"] = m.unmap_pool()
        if side is self.orig:
            # pages to mutate: where each object was first accessed, plus every page written
            inp.touched = sorted(entry | {p for p, d in mem["pool"].items() if d != init[p]})
        o["dyn_hi"] = m.dyn_next
        # every dirty DYN page (also beyond dyn_next, reached through garbage indices) and every
        # dirty MISC page (TEB, TLS, scratch), restored to the baseline for the next run
        mem["heap"], misc = m.take_dirty(
            self.writes.dwords if getattr(self.writes, "on", False) else None)
        for p in sorted(self.injected):
            # the class-3 pages injected into this pass (run_side) go back to zeros, as take_dirty left every
            # page this pass wrote, so the next input's original run starts from a clean heap
            m.uc.mem_write(p, b"\0" * 0x1000)
        self.injected = set()
        if getattr(self.writes, "on", False):
            # snapshot the pass's write set: the other pass subtracts it to find dwords only ONE run wrote
            # through a do-nothing stub (Runner._trim_stub_scratch, Comparer.diff_bytes' stub fence)
            if side is self.orig:
                self.orig_wrote = set(self.writes.dwords)      # any write, incl. handler buffers
                self.orig_stores = set(self.writes.own_dwords)
            else:
                self.ours_wrote = set(self.writes.dwords)
                self.ours_stores = set(self.writes.own_dwords)
        # --uninit-mem: the original allocated through an import whose handler is a do-nothing stub and the
        # pages it wrote are scaffold for the *input's* benefit (a formatted text buffer, a container a
        # blocked walk fills). Our builds of that call are the same kind of stub, so a dword only the
        # original wrote is not evidence about our code; it is excused by name (`stub-scratch: N dword(s)
        # via sprintf`) and never silently dropped. A dword OUR pass wrote is still compared.
        if getattr(self.opts, "uninit_mem", True):
            # dwords each pass wrote, from the MemWrites registry (the emulated-store hook + Machine.write).
            # On the ORIG pass (which runs first) `ours_w` below is this pass's OWN stores -- writes were
            # reset at pass start -- and `other` is None: ours' writes are unknowable yet, and any later
            # ours-side write into an excused region still shows as a difference on ours' page. On the
            # OURS pass the pages carry the ORIGINAL's inherited leftovers, so the excusal is attributed
            # to orig's snapshot and contested against ours' own stores. (Machine has no written_dwords
            # method, so this used to be a `None` fallback and the trim never ran.)
            ours_w = set(self.writes.own_dwords) if getattr(self.writes, "on", False) else None
            orig_w = getattr(self, "orig_wrote", None)
            for page in sorted(mem["heap"]):
                self._trim_stub_scratch(side, mem["heap"], page,
                                        orig_w if side is self.ours else ours_w,
                                        other=ours_w if side is self.ours else None)
            for page in sorted(misc):
                self._trim_stub_scratch(side, misc, page,
                                        orig_w if side is self.ours else ours_w,
                                        other=ours_w if side is self.ours else None, label="misc")
        sp = M.SCRATCH & ~0xFFF
        if sp in misc:                                  # harness scratch (float results) is not compared
            pg = bytearray(misc[sp])
            pg[M.SCRATCH - sp:M.SCRATCH - sp + 16] = m.misc_base_page(sp)[M.SCRATCH - sp:M.SCRATCH - sp + 16]
            misc[sp] = bytes(pg)
        mem["misc"] = misc
        if side is self.orig:
            # class 3: capture what the ORIG pass left behind, so the OURS pass starts from it (heap pages
            # only, because only DYN is shared with the stub scratch the original writes through a do-nothing
            # import). `baseline` holds the bytes the second pass is injected with; `mem["heap"]` (above) is
            # what the comparison sees, and it is restored from the same bytes when the pass ends.
            # Only the pages of the original's allocations: a DYN page past its high-water mark (dyn_next)
            # is no heap block but memory a soup pointer reached (a GameData* of 0x53db0000 in the
            # interpreter's context_menu_add_item: the original's tstring::operator= wrote its buffer
            # into that "object", and injecting it made our pass's operator= see a string that already
            # had one). Those pages started as zeros for the original, so they start as zeros for ours.
            # And only what import handlers wrote there (the do-nothing stubs' scaffold this rule is for):
            # a dword the original's code itself stored starts as zeros for our pass, as it did for the
            # original's (change_screen_quit: our malloc got the original's deque map back, its block
            # slot already set, so our deque::push_back skipped the malloc the original made).
            hw = (o["dyn_hi"] + 0xFFF) & ~0xFFF
            stores = self.heap_stores
            heap = {}
            for pg, d in mem["heap"].items():
                if pg >= hw:
                    continue
                keep = bytearray(0x1000)
                for k in range(0, 0x1000, 4):
                    if pg + k not in stores:
                        keep[k:k + 4] = d[k:k + 4]
                if any(keep):
                    heap[pg] = bytes(keep)
            self.baseline = {
                "heap": heap,
                "extra": {k: v for k, v in mem.get("extra", {}).items()} if extra_init else None,
                "inp_extra": dict(getattr(inp, "extra", {})),
            }
        elif self.baseline is not None:
            self.runs += 1
        mem["stack"] = m.read(self.args_hi, STACK_END - self.args_hi)
        for (lo, hi), base in zip(self.obj["data_rw"], self.obj["rw_baseline"]):
            cur = m.read(lo, hi - lo)
            mem["ours_data"] = cur
            if cur != base:
                m.write(lo, base)
        o["mem"] = mem
        o["imports"] = list(m.trace_imports)
        o["fakes"] = list(self.fakes)
        o["calls"] = list(self.calls)
        if self.opts.call_regs:
            # index-aligned with the three traces above: the register file at each recorded call (copied: a
            # later ref run reuses the lists)
            o["call_regs"] = {"call": list(self.call_regs), "import": list(self.import_regs),
                              "fake": list(self.fake_regs)}
        return o


# ====================================================================== comparison

def in_stack_frame(v, hi):
    """v points into the function's own stack: its frame (below esp at entry), the return address
    slot or its incoming argument slots (hi = Runner.stk_hi)."""
    return M.STACK_TOP - M.STACK_SIZE <= v < hi


def norm_val(v, hi):
    return "STK" if isinstance(v, int) and in_stack_frame(v, hi) else v


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
        self.tolerated = {"stack-pointer": 0, "inline-calls": 0, "ulp": 0, "const-pointer": 0, "local-copy": 0,
                          "uninit-dword": 0, "stub-scratch": 0, "stale-return-address": 0}
        self.ro = runner.ro
        self.uninit_copy = frozenset()      # bytes excused for the input in hand (set by test_function)
        self.last_kind = None
        self._thr, self._thr_key = None, None      # --uninit-mem: the pool/extra baseline of the page in hand

    def stale_return_address(self, x, y):
        """Both values are return addresses of call sites inside the tested function (the original's in
        the image, ours in our copy). Code never stores one as data, so such a dword is a stale stack
        slot an uninitialised read copied out (the original Light::init 0x461480 copies an unset
        vector4 w into four fields; the stack below esp holds the return addresses of earlier calls,
        and those differ between the builds because the call sites do). Both sides must be one."""
        if x == y:
            return False
        sites = getattr(self, "_ret_sites", None)
        if sites is None:
            CALL = CX.X86_INS_CALL

            def rets(insns):
                return {a + ins.size for a, ins in (insns or {}).items() if ins.id == CALL}
            sites = self._ret_sites = (rets(self.r.t.orig_insns), rets(getattr(self.r, "ours_func_insns", None)))
        return x in sites[0] and y in sites[1]

    def uninit_excused(self, addr, ba, bb):
        """True when the dword at addr differs only in bytes the original copied from an uninitialised stack slot
        (Runner.uninit_copies): every differing byte is tainted."""
        if not self.uninit_copy:
            return False
        diff = [j for j in range(min(len(ba), len(bb))) if ba[j] != bb[j]]
        return bool(diff) and all((addr + j) in self.uninit_copy for j in diff)

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

    def our_section_end(self, y):
        """End of the section of OUR mapped object that contains y, else None."""
        obj, coff = self.r.obj, self.r.t.coff
        for i, a in obj["sec_addr"].items():
            n = len(coff.sections[i].data)
            if a <= y < a + n:
                return a + n
        return None

    def same_call_site(self, x, y):
        """x and y are the addresses stored right after a `call` in the original's and in our code: the
        same call site when both preceding calls target the same address and the instruction at the
        stored address is identical (the two builds may have drifted a few bytes apart)."""
        img, m = context()["img"], self.r.m
        try:
            ca, cb = img.read(x - 5, 5), m.read(y - 5, 5)
            if ca[0] != 0xE8 or cb[0] != 0xE8:
                return False
            ta = (x + struct.unpack_from("<i", ca, 1)[0]) & 0xFFFFFFFF
            tb = (y + struct.unpack_from("<i", cb, 1)[0]) & 0xFFFFFFFF
            return ta == tb and img.read(x, 8) == m.read(y, 8)
        except Exception:
            return False

    def _vtable_match(self, x, y):
        """x is the address the ORIGINAL stores, y the one OUR code stores, and BOTH are vtables the relink
        already matched by content (work/relink/resolve_map.json: `??_7X@@6B@ -> [orig va]`). An address
        difference there is a link-time fact, not a semantic one: what matters is the call graph - slot k of
        ours must resolve to the same original function as slot k of theirs.

        Returns None when either address is not a matched vtable (the caller then compares bytes, as before).
        Otherwise (True, note) when every slot we can resolve agrees, (False, note) naming the first slot whose
        target differs - and a slot whose target cannot be resolved counts as disagreement, so this can never
        hide a wrong call graph (item_rec 0x4ce870 has to keep failing for a real reason, not this one)."""
        rm = self.r.vt_match
        if not rm:
            return None
        ova = rm["by_orig"].get(x)
        if ova is None:
            return None
        name, nslots = ova
        m, img = self.r.m, context()["img"]
        obj = self.r.obj
        if not isinstance(y, int) or obj is None:
            return None
        lo0, hi0 = obj["map_lo"], obj["map_hi"]     # our mapped object's address range
        if not (lo0 <= y < hi0):
            return None                              # a vtable copy in the pool/heap: not this case
        bad = []
        agree = 0
        unverifiable = 0
        for k in range(nslots):
            ot = img.u32(x + 4 * k) if img.in_image(x + 4 * k) else None
            try:
                yt = m.u32(y + 4 * k)
            except Exception:
                bad.append("+0x%02x unreadable" % (4 * k))
                continue
            if ot is None:
                continue
            want = self.r.res_name(ot)        # the name the relink knows for the original's target
            have = self.r.res_name(yt)        # our slot's target, resolved the same way
            if want is not None and have is not None and want == have:
                agree += 1
                continue
            if yt == M.TRAP_BASE or (self.r.res_name(yt) is None and self.r.slot_is_undefined(yt)):
                # An unresolved slot: our object references a symbol no TU in a single-row compile defines (the
                # virtual's body lives in another module's TU, e.g. MainMenuScreen::create in cls_map.cpp). The
                # resolver parks it on the trap page. That is "cannot tell", not "differs" - the linked build has
                # the real body, the per-row compile cannot see it. Counted as unverifiable and said so.
                unverifiable += 1
                continue
            # Our slot target often has no COFF symbol: cl emits an inline virtual's body as an unnamed
            # one-instruction function in our own section (slot 4 `ret`, slot 5 `ret 4`, slot 7 `mov al,1;ret`),
            # and a compiler-generated deleting destructor is unnamed too. Name equality cannot judge those, so
            # fall back to the code itself: identical bytes (or bytes that differ only in a relocated operand,
            # which for these one-instruction bodies is the callee/constant they hold) means the same behaviour.
            same, how = self._vtable_body_equal(ot, yt)
            if same:
                agree += 1
                continue
            bad.append("+0x%02x %s vs %s (%s)" % (4 * k, want or "%08x" % ot, have or "%08x" % yt, how))
        if not bad:
            note = "%d/%d vtable slot(s) resolve to the same function as the image's %s" % (agree, nslots, name)
            if unverifiable:
                note += (" (%d slot(s) unverifiable: their bodies live in another module's TU, unresolved in a "
                         "single-row object)" % unverifiable)
            return True, note
        return False, ("vtable %s: %d/%d slot(s) agree, first difference %s" % (name, agree, nslots, bad[0]))

    def _vtable_body_equal(self, ot, yt):
        """Same behaviour for a vtable slot target, when name equality cannot decide: compare the first
        instructions of the original's target with ours, masking the bytes a relocation covers on either side
        (a one-instruction body like `ret 4` or `mov al,1; ret` holds no address; a longer body may hold one).
        Returns (True, how) or (False, why)."""
        img, m = context()["img"], self.r.m
        try:
            n = 16
            bo = img.read(ot, n)
            by = m.read(yt, n)
        except Exception:
            return False, "unreadable"
        if not bo or not by:
            return False, "unreadable"
        # A one-instruction tail call (`jmp <target>`) to the very function the original's slot holds is the same
        # behaviour: cl emits that thunk for a virtual whose body only forwards to a named function, while the
        # original inlined that function's own prologue into the slot. Narrow on purpose: only a bare jmp whose
        # target resolves to the original's slot target counts.
        if by[0] == 0xE9 and len(by) >= 5:
            disp = int.from_bytes(by[1:5], "little", signed=True)
            tgt = (yt + 5 + disp) & 0xFFFFFFFF
            if tgt == ot:
                return True, "tail call to the original's own slot target"
            if self.r.res_name(tgt) is not None and self.r.res_name(tgt) == self.r.res_name(ot):
                return True, "tail call to a function with the original slot target's name"
        k = 0
        while k < min(len(bo), len(by)):
            a, b = bo[k], by[k]
            if a == b:
                if a in (0xC3, 0xC2):        # ret / ret N: the body ends here and it matched
                    return True, "identical body (%d byte(s))" % (k + 1)
                if a in (0xCC,):             # int3 padding: the body ended before it
                    return True, "identical body (%d byte(s))" % k
                k += 1
                continue
            # a differing byte inside an instruction that carries an address: accept it when the instruction
            # boundaries still line up (the encodings are otherwise identical, so the opcode bytes matched above)
            return False, "bodies differ at +%d (%02x vs %02x)" % (k, a, b)
        return False, "bodies differ"

    def same_local_copy(self, x, y):
        """x is the address the ORIGINAL stores, y the one our code stores: an address in our own mapped
        object, where the linker kept its own copy of something the original keeps in the image
        (a literal/constant pool entry, a vtable, a code label our code stores - a return address left in
        an output buffer) or a copy our code built in the pool/heap. Not such an address -> None.
        Otherwise (equal, note): equal only when the bytes at both are identical - for an address inside
        the function under test, the same offset in our copy, or the return address of the same call.
        A differing block is reported with its first differing dwords: a real difference, never a pass."""
        obj = self.r.obj
        img = context()["img"]
        if obj is None or not isinstance(y, int) or not isinstance(x, int) or not img.in_image(x):
            return None
        if not (obj["map_lo"] <= y < obj["map_hi"] or M.POOL_BASE <= y < M.POOL_BASE + M.POOL_SIZE or
                M.DYN_BASE <= y < M.DYN_BASE + M.DYN_SIZE):
            return None
        m = self.r.m
        lo, hi = obj["func_range"]
        flo, fhi = self.r.t.orig_lo, self.r.t.orig_hi
        if lo <= y < hi and flo <= x < fhi:
            try:
                if y - obj["entry"] == x - flo:
                    # the same position in our copy of the function (a label, or a return address an
                    # image callee copied out of the caller's frame): the address differs by the base only
                    return True, "our copy of the function, +%#x from its entry" % (y - obj["entry"])
                if self.same_call_site(x, y):
                    return True, "the return address of the same call (image +%#x, ours +%#x)" % (
                        x - flo, y - obj["entry"])
                return False, "code at the image's +%#x / our +%#x differs: %s/%s" % (
                    x - flo, y - obj["entry"], img.read(x, 8).hex(), m.read(y, 8).hex())
            except Exception:
                return None
        vt = self._vtable_match(x, y)
        if vt is not None:
            return vt
        end = self.our_section_end(y)
        if end is not None:
            n = min(256, end - y)       # our copy's own extent in the object image
        elif M.POOL_BASE <= y < M.POOL_BASE + M.POOL_SIZE or M.DYN_BASE <= y < M.DYN_BASE + M.DYN_SIZE:
            n = 16                      # a copy our code built in the pool/heap: a fixed window, so no
        else:                           # difference inside the compared block can be skipped
            return None
        try:
            bx, by = img.read(x, n), m.read(y, n)
        except Exception:
            return None
        n = min(n, len(bx), len(by))        # a read can come back short (unmapped tail): never unpack past it
        if bx == by:
            return True, "%d byte(s) identical at the image's %08x" % (n, x)
        diffs = []
        for q in range(0, n - 3, 4):
            if bx[q:q + 4] != by[q:q + 4]:
                diffs.append("+%#x: %08x/%08x" % (q, struct.unpack_from("<I", bx, q)[0],
                                                   struct.unpack_from("<I", by, q)[0]))
                if len(diffs) >= 4:
                    break
        return False, "our copy at %08x vs the image's %08x differs (%s)" % (
            y, x, ", ".join(diffs) if diffs else "%d/%d bytes" % (len(bx), len(by)))

    def local_copy_equal(self, x, y):
        """same_local_copy, counting a tolerated difference (see the reason note)."""
        lc = self.same_local_copy(x, y)
        if lc and lc[0]:
            self.tolerated["local-copy"] += 1
            return True
        return False

    def caller_safe(self, t, reg, result):
        """True when no caller of the original can observe reg after the call (callerdeps.py, SAFE): every direct
        call site's paths overwrite it before reading it, up to two caller levels. Preserve mode: ours writes a
        scratch register the original leaves untouched (mission_3 0x48d650: cl keeps a dead `this`-derived value in
        ecx); result mode (result=True): the original's eax differs and no caller reads it. DEPENDS and UNKNOWN
        (pointer callers, indirect jmps) stay mismatches. Counted as tolerated 'caller-dead-<reg>'."""
        cache = self.__dict__.setdefault("_caller_safe", {})
        k = (t.va, reg, result)
        if k not in cache:
            try:
                import callerdeps as CD
                d = getattr(Comparer, "_deps", None) or CD.Deps(self.r.img)
                Comparer._deps = d
                cache[k] = d.check(t.va, {reg}, 2, result=result)["verdict"] == "SAFE"
            except Exception:
                cache[k] = False
        if cache[k]:
            nm = "caller-dead-" + reg
            self.tolerated[nm] = self.tolerated.get(nm, 0) + 1
        return cache[k]

    def compare(self, a, b, t):
        """-> None if equivalent, else (observable, orig, ours, detail). self.last_kind: triage hint."""
        self.last_kind = None
        rk = t.ret_kind
        if rk in ("int", "ptr", "hidden", "unknown", "small", "bool", "i64"):
            mask = {"bool": 0xFF, "small": 0xFFFF}.get(rk, 0xFFFFFFFF)
            if rk == "small":
                # a char return is al (the caller reads nothing else; ah is whatever the last write left)
                mask = 0xFF if getattr(t, "ret_width", None) == 1 else 0xFFFF
            ea, eb = a["eax"] & mask, b["eax"] & mask
            if ea != eb and not (in_stack_frame(ea, self.r.stk_hi) and in_stack_frame(eb, self.r.stk_hi)) \
                    and not (mask == 0xFFFFFFFF and (self.same_constant(ea, eb) or self.local_copy_equal(ea, eb))) \
                    and not self.caller_safe(t, "eax", True):
                return ("eax" if mask == 0xFFFFFFFF else "eax&%#x" % mask, "%08x" % ea, "%08x" % eb, "return value")
            if rk == "i64" and a["edx"] != b["edx"]:
                return ("edx", "%08x" % a["edx"], "%08x" % b["edx"], "64-bit return high half")
        for nm, _r in M.CALLEE_SAVED:
            if a[nm] != b[nm]:
                return (nm, "%08x" % a[nm], "%08x" % b[nm], "callee-saved register not preserved identically")
        # Registers the original never writes (statically) and left untouched on this run: ours
        # must leave them too. An LTCG caller may keep a live value in a register its callee is
        # known not to touch (InterpRamp 0x114e780 wrote xmm3: crackling audio, 2026-10-12).
        written = getattr(t, "orig_regs_written", None)
        if written is not None and "entry" in a and "entry" in b:
            cand = [r for r in RF.GPR_SCRATCH + RF.XMM if r not in written]
            if rk != "void":
                cand = [r for r in cand if r != "eax" and not (rk == "i64" and r == "edx")]
            if rk == "m128":
                cand = [r for r in cand if r != "xmm0"]
            for r in cand:
                if a[r] == a["entry"][r] and b[r] != b["entry"][r] and not self.caller_safe(t, r, False):
                    self.last_kind = "clobber"
                    return (r + " (untouched by the original)", "%x" % a["entry"][r], "%x" % b[r],
                            "ours writes a register the original never writes; an LTCG caller may keep a live value there")
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
        d = self.compare_calls(a["calls"], b["calls"])
        if d:
            return d
        d = self.compare_fakes(a["fakes"], b["fakes"])
        if d:
            return d
        if getattr(self.opts, "call_regs_strict", False):
            # --call-regs-strict: a live-register difference is a mismatch, not just a diagnostic. Only an input
            # that matched every other observable reaches here, so nothing that already passed can be weakened.
            rd = self.call_reg_diff(a, b)
            if rd and rd.get("reg") and rd.get("before_args"):
                # only at a pair whose callee and normalised arguments still agree: a difference at or past
                # the point where the trace itself diverges is explained by that divergence (an inlined call)
                return (rd["observable"], rd["orig"], rd["ours"], rd["detail"])
        return None

    def compare_fakes(self, fa, fb):
        """Calls through generated pointers (fake methods): same `this` and the same stack
        arguments, in order. cViewer::SetRaster 0x7c4be0 passed (rect, a, b) for (a, b, rect) and
        RegisterGameTexture (a, b, 0, 0) for (key0, key2, a, b); both PASSed before this."""
        for k in range(min(len(fa), len(fb))):
            ta, na, ea, aa = fa[k]
            tb, nb, eb, ab = fb[k]
            if ta != tb:
                return ("fake call #%d" % k, "%08x" % ta, "%08x" % tb, "different generated callee")
            if not self.veq(ea, eb):
                return ("fake call #%d this" % k, fmt_val(ea), fmt_val(eb), "ecx at a call through a generated pointer")
            for i in range(min(na, nb)):
                if not self.veq(aa[i], ab[i]):
                    return ("fake call #%d arg %d" % (k, i), fmt_val(aa[i]), fmt_val(ab[i]),
                            "stack argument of a call through a generated pointer (normalised)")
        return None

    # --- --call-regs: the live register file at every call site

    def reg_value_equal(self, x, y):
        """One register dword explained: the same value, two addresses inside the function's own stack frame,
        the same pooled read-only constant, our own copy of a block whose bytes are identical, or --ulp apart.
        Uses the NON-counting forms of same_constant/local_copy_equal: a diagnostic must not move the tolerated
        tallies or the note a verdict prints."""
        if x == y:
            return True
        if in_stack_frame(x, self.r.stk_hi) and in_stack_frame(y, self.r.stk_hi):
            return True
        if self.same_constant(x, y):
            return True
        lc = self.same_local_copy(x, y)
        if lc is not None and lc[0]:
            return True
        return bool(self.opts.ulp) and ulp_close(x, y, self.opts.ulp)

    def reg_equal(self, name, x, y):
        """A whole register; an xmm register dword by dword (an address can sit in one lane)."""
        if name not in CALL_XMM:
            return self.reg_value_equal(x, y)
        return all(self.reg_value_equal((x >> (32 * i)) & 0xFFFFFFFF, (y >> (32 * i)) & 0xFFFFFFFF)
                   for i in range(4))

    def reg_pair_class(self, name, x, y, callee, reads=()):
        """Why two live-register values differ, for the --call-regs diagnostic:
        'frame-size'  the callee is __chkstk and its argument IS the caller's frame size - our frame legitimately
                      differs (the esp-at-return comparison already covers what matters);
        'fill'        a build left an uninitialised-stack pattern / sentinel there: a dead value, no information;
        'address'     a stack, heap or pool address against something else: a pointer that never reaches the
                      compared observable state (only registers and declared arguments are compared here);
        'pool'        two different pool/heap addresses: allocation order differs;
        'value'       anything else - the two implementations computed different things. The interesting case."""
        if name == "eax" and callee and "chkstk" in callee.lower():
            return "frame-size"
        if name in (reads or ()):
            return "input"           # the callee reads this register at entry: an argument we do not declare
        lo, hi = M.POOL_BASE, M.POOL_BASE + M.POOL_SIZE
        is_pool = lambda v: lo <= v < hi or M.DYN_BASE <= v < M.DYN_BASE + M.DYN_SIZE or 0x50000000 <= v < 0x50080000
        is_stack = lambda v: in_stack_frame(v, self.r.stk_hi) or 0x7D000000 <= v < 0x7E000000
        if x in FILL_PATTERNS or y in FILL_PATTERNS:
            return "dead-fill"
        if is_stack(x) or is_stack(y):
            return "dead-address"
        if is_pool(x) or is_pool(y):
            return "dead-address"
        return "dead"                # internal state the callee never sees: the final-state comparison covers it

    def peq(self, x, y):
        """veq without the tallies (same_constant/local_copy_equal report), for the same reason."""
        if x == y:
            return True
        if not (isinstance(x, int) and isinstance(y, int)):
            return False
        lc = self.same_local_copy(x, y)
        return self.same_constant(x, y) or (lc is not None and lc[0])

    def trace_diff_index(self, kind, a, b):
        """Index of the first pair of `kind` ('call', 'import', 'fake') whose CALLEE, this/edx or normalised
        stack arguments differ, or None: the point where the compared part of the trace already diverges, so a
        register difference at or after it explains nothing. Non-counting (peq)."""
        if kind == "call":
            A, B = self.norm_calls(a["calls"]), self.norm_calls(b["calls"])
            for k in range(min(len(A), len(B))):
                (ta, ea, da), aa = A[k]
                (tb, eb, db), ab = B[k]
                if ta != tb or not self.peq(ea, eb) or not self.peq(da, db) or \
                        not all(self.peq(x, y) for x, y in zip(aa, ab[:len(aa)])):
                    return k
            return min(len(A), len(B)) if len(A) != len(B) else None
        if kind == "import":
            esp = self.r.stk_hi
            ia, ib = a["imports"], b["imports"]
            for k in range(min(len(ia), len(ib))):
                na, va = ia[k][0], tuple(norm_val(v, esp) for v in ia[k][1])
                nb, vb = ib[k][0], tuple(norm_val(v, esp) for v in ib[k][1])
                if na != nb or len(va) != len(vb) or not all(self.peq(x, y) for x, y in zip(va, vb)):
                    return k
            return min(len(ia), len(ib)) if len(ia) != len(ib) else None
        fa, fb = a["fakes"], b["fakes"]
        for k in range(min(len(fa), len(fb))):
            ta, na, ea, aa = fa[k]
            tb, nb, eb, ab = fb[k]
            if ta != tb or not self.peq(ea, eb) or not all(self.peq(x, y) for x, y in zip(aa[:na], ab[:nb])):
                return k
        return min(len(fa), len(fb)) if len(fa) != len(fb) else None

    def trace_callee(self, kind, a, b, k):
        """'<address> <symbol>' of the callee of pair k (both sides when they disagree)."""
        try:
            if kind == "import":
                na, nb = str(a["imports"][k][0]), str(b["imports"][k][0])
                return na if na == nb else "%s vs %s" % (na, nb)
            ta = a["calls"][k][0] if kind == "call" else a["fakes"][k][0]
            tb = b["calls"][k][0] if kind == "call" else b["fakes"][k][0]
        except (IndexError, KeyError):
            return "?"
        img = context()["img"]
        def lab(t):
            nm = img.names.get(t, "")
            return "%08x%s" % (t, " " + nm if nm else "")
        return lab(ta) if ta == tb else "%s vs %s" % (lab(ta), lab(tb))

    def call_reg_diff(self, a, b):
        """--call-regs: the first live-register difference at a call site that no tolerance explains, with the
        call it belongs to. Pairs are aligned by index inside each trace (depth-1 calls, then imports, then fake
        calls - the order the trace comparisons use) and within a trace in call order. None when the flag is off
        or every captured register agrees."""
        if not getattr(self.opts, "call_regs", False):
            return None
        ra, rb = a.get("call_regs") or {}, b.get("call_regs") or {}
        counted, compared = [], 0
        for kind in ("call", "import", "fake"):
            n = min(len(ra.get(kind) or ()), len(rb.get(kind) or ()))
            compared += n
            if n:
                counted.append("%d %s%s" % (n, kind, "" if n == 1 else "s"))
        benign = None
        for kind in ("call", "import", "fake"):
            sa, sb = ra.get(kind) or (), rb.get(kind) or ()
            for k in range(min(len(sa), len(sb))):
                if not sa[k] or not sb[k]:
                    continue
                callee = self.trace_callee(kind, a, b, k)
                try:                    # registers the callee itself reads at entry (entry_reads, first 400 bytes)
                    reads = set() if kind == "import" else self.r.callee_regs(
                        a["calls"][k][0] if kind == "call" else a["fakes"][k][0])
                except (IndexError, KeyError, TypeError):
                    reads = set()
                for nm in CALL_REGS + CALL_XMM:
                    x, y = sa[k].get(nm), sb[k].get(nm)
                    if x is None or y is None or self.reg_equal(nm, x, y):
                        continue
                    lo_x, lo_y = (x & 0xFFFFFFFF, y & 0xFFFFFFFF) if nm in CALL_XMM else (x, y)
                    cls = self.reg_pair_class(nm, lo_x, lo_y, callee, reads)
                    j = self.trace_diff_index(kind, a, b)
                    where = "depth-1" if kind == "call" else kind
                    rec = {"kind": kind, "index": k, "reg": nm, "orig": fmt_reg(nm, x), "ours": fmt_reg(nm, y),
                           "callee": callee, "compared": compared, "traces": ", ".join(counted) or "none",
                           "first_arg_diff": j, "before_args": j is None or k < j, "class": cls,
                           "semantic": cls == "input", "observable": "call #%d reg %s" % (k, nm)}
                    if cls == "input":
                        rec["detail"] = (("live register at a %s call whose callee and normalised this/edx/stack "
                                          "arguments agree: the two implementations computed different values "
                                          "before this call" % where) if (j is None or k < j) else
                                         ("live register at a %s call; the compared callee/arguments already differ "
                                          "at #%d" % (where, j)))
                        return rec
                    if benign is None:      # keep the first explicable difference, in case nothing better shows up
                        benign = rec
        if benign is not None:
            why = {"frame-size": "the argument IS the caller's frame size (our frame legitimately differs)",
                   "dead-fill": "an uninitialised-stack fill / sentinel in a register the callee never reads",
                   "dead-address": "a stack/heap/pool address in a register the callee never reads",
                   "dead": "a register the callee never reads (internal state; the final-state comparison covers it)"}[benign["class"]]
            benign["detail"] = "no semantic divergence at any call; first explicable difference: %s" % why
            return benign
        return {"kind": None, "reg": None, "compared": compared, "traces": ", ".join(counted) or "none",
                "semantic": False}

    def call_reg_note(self, d):
        """The one-line --call-regs diagnostic for the printed reason."""
        if not d:
            return ""
        if not d.get("reg"):
            return "call-regs: no unexplained register difference (%d call site(s) compared: %s)" % (
                d.get("compared", 0), d.get("traces", "none"))
        kind = {"call": "depth-1 call", "import": "import call", "fake": "fake call"}.get(d["kind"], d["kind"])
        return "call-regs: call #%d reg %s: orig %s ours %s (%s to %s, %d call site(s) compared: %s%s)" % (
            d["index"], d["reg"], d["orig"], d["ours"], kind, d["callee"], d["compared"], d["traces"],
            "" if d["before_args"] else "; the compared callee/arguments already differ at #%s" % d["first_arg_diff"])

    def compare_mem(self, a, b):
        ma, mb = a["mem"], b["mem"]
        esp = self.r.stk_hi
        for region in sorted(set(ma) | set(mb)):
            if region == "ours_data":
                continue
            self._lastref = b                       # the run whose values the page holds (see _stub_fence)
            xa, xb = ma.get(region), mb.get(region)
            if region in ("pool", "extra"):
                ik = "pool_init" if region == "pool" else "extra_init"
                xa, xb = xa or {}, xb or {}
                for page in sorted(set(xa) | set(xb)):
                    pa = xa.get(page) or a.get(ik, {}).get(page) or b.get(ik, {}).get(page)
                    pb = xb.get(page) or b.get(ik, {}).get(page) or a.get(ik, {}).get(page)
                    self._thr = a.get(ik, {}).get(page) or b.get(ik, {}).get(page) or pa
                    self._thr_key = (region, page, id(pa))
                    d = self.diff_bytes(pa, pb, page, region, esp)
                    if d:
                        return d
                continue
            if region == "heap" and a["dyn_hi"] != b["dyn_hi"]:
                return ("heap size", "%#x" % (a["dyn_hi"] - M.DYN_BASE), "%#x" % (b["dyn_hi"] - M.DYN_BASE),
                        "bytes allocated through malloc-like imports")
            if isinstance(xa, dict) or isinstance(xb, dict):
                xa, xb = xa or {}, xb or {}
                m = self.r.m
                if region == "heap":
                    def basepg(page):
                        return b"\0" * 0x1000
                elif region == "misc":
                    basepg = m.misc_base_page
                else:
                    def basepg(page, region=region):
                        return m.image_base_page(region, page)
                for page in sorted(set(xa) | set(xb)):
                    pa = xa.get(page) or basepg(page)
                    pb = xb.get(page) or basepg(page)
                    d = self.diff_bytes(pa, pb, page, region, esp)
                    if d:
                        return d
                continue
            if xa == xb:
                continue
            base_addr = {"stack": self.r.args_hi}[region]
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

    def unobserved(self, region, base_addr, xa, xb, thr):
        """--uninit-mem: the dwords of one compared block that NEITHER build wrote and whose original-side
        value is a fill/sentinel leftover. Returns (n_dropped, set of dropped dword offsets).

        Only the `pool`, `extra` (fault-repair mapped input), `heap` and `misc` regions are eligible: for
        the image's .data and our object's copies a difference can always be a global the function was
        supposed to write, and a baseline of zeros there would excuse a real missing store. In the eligible
        regions the dword must still be byte-identical to the bytes the run started from (`thr`), so a dword
        a build produced is never reached; and a dword OUR build wrote is refused outright (its flag is set)
        regardless of what it holds. Anything dropped is counted and named in `excused` so the reason can
        report it and nothing becomes invisible."""
        if not getattr(self.opts, "uninit_mem", True) or region not in ("pool", "extra", "heap", "misc"):
            return 0, frozenset()
        r = self.r
        if getattr(r, "write_flags_reg", None) is None:
            return 0, frozenset()
        drop = set()
        n = min(len(xa), len(xb)) // 4
        for k in range(n):
            q = 4 * k
            if q + 4 > len(thr):
                continue                    # no baseline of the page in hand: nothing to compare against
            t0 = struct.unpack_from("<I", thr, q)[0]
            x, y = struct.unpack_from("<I", xa, q)[0], struct.unpack_from("<I", xb, q)[0]
            if x == y:
                continue                    # not a difference in the first place
            addr = base_addr + q
            # The original's value must be a fill/sentinel leftover: either it is one of FILL_PATTERNS, or
            # it is the baseline with a fill byte copied over it (the `cls_map` case: the original copies an
            # uninitialised 0xCC stack byte into a float field the input already carried).
            if not unobserved_fill(x, t0):
                continue
            f = r.write_flags(addr)
            if f is None:
                continue
            if f[k] and y != t0:
                # OUR build wrote this dword and what it wrote is not the value the run started with: a
                # real difference, never a leftover. (A write that restored the baseline is a no-op, and a
                # dword our build never wrote cannot hold a value it produced.)
                continue
            if y != t0:
                # no flag (a region the hook does not cover) but our side still changed it: refuse too
                continue
            drop.add(q)
            r.uncompared[(region, addr)] = "fill 0x%08x" % x
        return len(drop), drop

    def diff_bytes(self, xa, xb, base_addr, region, esp):
        if xa == xb:
            return None
        n = min(len(xa), len(xb))
        thr = getattr(self, "_thr", None) if self._thr_key == (region, base_addr, id(xa)) else None
        stubs = getattr(self.r, "uncompared", None)
        # a page only the run whose values these bytes are wrote, and it wrote them through a do-nothing
        # import stub: that is where the stub's buffer happened to land, and the run that did not write it
        # reports the page as untouched (its baseline). The page says nothing about the code (see
        # Runner._stub_fence); the count is reported and each excused page is listed by name in the reason.
        if stubs is not None and not xa.startswith(b"\0" * 4096):
            who = self.r._stub_fence(base_addr)
            if who:
                # Excuse only the dwords the fence really covers: the page difference is dropped, but any
                # dword OUR code wrote is put back (it was a real store, not the stub's buffer), so the
                # whole-page excuse can no longer hide a value our build produced.
                buf = None
                ours = set(getattr(self.r, "ours_stores", ()) or ())
                for q in range(0, n - 3, 4):
                    if ours and (base_addr + q) in ours and xa[q:q + 4] != xb[q:q + 4]:
                        if buf is None:
                            buf = bytearray(xb)
                        continue
                    stubs[(region, base_addr, base_addr + q)] = who
                if buf is None:
                    self.tolerated["stub-scratch"] = self.tolerated.get("stub-scratch", 0) + n // 4
                    return None
                # fall through with the restored dwords compared below
                self.tolerated["stub-scratch"] = self.tolerated.get("stub-scratch", 0) + n // 4 - sum(
                    1 for q in range(0, n - 3, 4) if ours and (base_addr + q) in ours)
        dropped, drop = self.unobserved(region, base_addr, xa, xb, thr or b"")
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
            if stubs is not None and (region, base_addr, base_addr + k) in stubs:
                # class 3: neither pass but the original's do-nothing stub wrote this dword, and our pass
                # wrote neither it nor the page: leftover scaffold for the input (a formatted buffer), not
                # information about the code. Counted under the stub's name in the reason, never silently
                # dropped, and a dword our own pass wrote is never in this set.
                self.tolerated["stub-scratch"] = self.tolerated.get("stub-scratch", 0) + 1
                i = k + 4
                continue
            if self.uninit_excused(base_addr + k, xa[k:k + 4], xb[k:k + 4]):
                # the original's dword is a plain copy of a stack slot its run never wrote (Runner.uninit_copies):
                # its value is indeterminate, so ours may hold anything there
                self.tolerated["uninit-copy"] = self.tolerated.get("uninit-copy", 0) + 1
                i = k + 4
                continue
            if k in drop:
                # --uninit-mem: a fill/sentinel leftover neither build wrote: not information about the
                # code, so it is neither compared nor counted as search progress (its bytes are re-tested
                # on every 4-byte step, so a page of them cannot loop forever).
                self.tolerated["uninit-dword"] += 1
                i = k + 4
                continue
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
            if va is not None and self.local_copy_equal(va, vb):
                i = k + 4
                continue
            if va is not None and self.stale_return_address(va, vb):
                self.tolerated["stale-return-address"] += 1
                i = k + 4
                continue
            if va is not None and self.opts.ulp and ulp_close(va, vb, self.opts.ulp):
                self.tolerated["ulp"] += 1
                i = k + 4
                continue
            more, pairs = [], []
            ndrop = 0
            for q in range(k, n - 3, 4):
                if q in drop:
                    ndrop += 1
                    continue
                x, y = struct.unpack_from("<I", xa, q)[0], struct.unpack_from("<I", xb, q)[0]
                if x != y and not (in_stack_frame(x, esp) and in_stack_frame(y, esp)):
                    pairs.append((x, y))
                    if len(more) < 8:
                        more.append("%08x: %08x/%08x" % (base_addr + q, x, y))
                    if len(pairs) >= 64:
                        break
            if not pairs and not ndrop:
                break                           # nothing left in this block: not a difference either way
            if not pairs:
                self.tolerated["uninit-dword"] += ndrop
                i = k + 4
                continue
            self.last_kind = classify_pairs(pairs)
            block = ""
            # ours holds an address of its own copy where the original holds the image's (a constant, a
            # vtable, a code label, a copy our code built): same_local_copy already accepted every copy
            # whose bytes are identical, so say how the block differs - the FAIL then names bytes
            lc = self.same_local_copy(pairs[0][0], pairs[0][1]) if pairs else None
            if lc is not None and not lc[0]:
                self.last_kind = "local-address"
                block = "; " + lc[1]
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
                    "differing dwords (addr: orig/ours): " + ", ".join(more) + block + ulps)
        if len(xa) != len(xb):
            return ("memory %s" % region, "len %d" % len(xa), "len %d" % len(xb), "")
        return None

    def veq(self, x, y):
        """Normalised values equal, or two pointers to the same read-only constant."""
        if x == y:
            return True
        if isinstance(x, int) and isinstance(y, int):
            if self.same_constant(x, y):
                self.tolerated["const-pointer"] += 1
                return True
            if self.local_copy_equal(x, y):
                return True
        return False

    def seq_eq(self, xs, ys):
        return len(xs) == len(ys) and all(self.veq(x, y) for x, y in zip(xs, ys))

    def compare_imports(self, ia, ib):
        esp = self.r.stk_hi
        na = [(n, tuple(norm_val(v, esp) for v in args)) for n, args in ia]
        nb = [(n, tuple(norm_val(v, esp) for v in args)) for n, args in ib]
        if na == nb:
            return None
        for k in range(max(len(na), len(nb))):
            x = na[k] if k < len(na) else None
            y = nb[k] if k < len(nb) else None
            if x is None or y is None or x[0] != y[0] or not self.seq_eq(x[1], y[1]):
                return ("import call #%d" % k, fmt_call(x), fmt_call(y), "imports called (any depth), args normalised")
        return None

    def norm_calls(self, calls):
        out = []
        esp = self.r.stk_hi
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
            widths = self.r.callee_arg_widths(tgt) if n else {}
            out.append((ent, [norm_val(w & ((1 << 8 * widths[k]) - 1) if k in widths else w, esp)
                              for k, w in enumerate(words[:n])] if n else []))
        return out

    def compare_calls(self, ca, cb):
        A, B = self.norm_calls(ca), self.norm_calls(cb)

        def same(x, y):
            if x[0][0] != y[0][0] or not self.seq_eq(x[0][1:], y[0][1:]):
                return False
            n = min(len(x[1]), len(y[1]))
            return self.seq_eq(x[1][:n], y[1][:n])

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


# ====================================================================== --fp-tol

FPCW_REF = 0x037F        # 64-bit precision: approximates exact arithmetic for the reference run
FP_STORES = ("movss", "movaps", "movups", "movlps", "movhps", "movsd", "movapd", "movupd", "movlpd", "movhpd", "movq")
FP_BIG = 1e30            # a differing float above this (or Inf/NaN) in the original is "out of range"


def _f32(v):
    return struct.unpack("<f", struct.pack("<I", v))[0]


def _tiny(v):
    """Denormal bit pattern (exponent 0, mantissa != 0): also what small integers look like as floats."""
    return (v & 0x7F800000) == 0 and (v & 0x7FFFFFFF) != 0


def fp_ulp(x, bits=24):
    """Spacing of floats with `bits` significant bits at the magnitude of x."""
    if x == 0 or not math.isfinite(x):
        return 2.0 ** -149 if bits == 24 else 2.0 ** -1074
    return max(2.0 ** (math.frexp(x)[1] - bits), 2.0 ** -149 if bits == 24 else 2.0 ** -1074)


def fp_judge_value(fa, fb, fr, bits=24):
    """(verdict, ulps, ratio, detail) for one differing float: orig at the game's precision (fa), ours (fb)
    and the original at 64-bit precision (fr, the stand-in for the exact result).
    verdict: 'oor' (the original's result or the exact result is Inf/NaN/above 1e30: a range case),
    'real' (NaN/Inf in ours only, or ours is further from the reference than the original), 'ok'."""
    if not math.isfinite(fa) or abs(fa) > FP_BIG or not math.isfinite(fr) or abs(fr) > FP_BIG:
        return "oor", 0.0, None, ""
    if not math.isfinite(fb):
        return "inf", 0.0, None, "ours is %r, original %r (reference %r)" % (fb, fa, fr)
    eo, eu = abs(fa - fr), abs(fb - fr)
    ulp = fp_ulp(max(abs(fr), abs(fa), abs(fb)), bits)
    ratio = eu / eo if eo > 0 else None
    detail = "orig %r ours %r reference %r: err_orig %.3g err_ours %.3g (%.3g ulp)" % (fa, fb, fr, eo, eu, eu / ulp)
    ok = eu <= max(2 * eo, 4 * ulp)
    return ("ok" if ok else "real"), abs(fa - fb) / ulp, ratio, detail


class FpTol:
    """--fp-tol: judge an input where original and ours differ only in floating-point rounding. The original
    is re-run at 64-bit precision (the reference); a differing dword is a float only if both builds and the
    reference hold finite floats, and ours must be at most as far from the reference as twice the original
    (or 4 ulp). Everything else (integers, pointers, call traces, status) stays a real mismatch."""

    def __init__(self, runner, cmp_, opts):
        self.r, self.c, self.opts = runner, cmp_, opts
        self.cw = int(opts.fpcw, 16)
        self.n_fp = self.n_oor = self.n_floats = 0
        self.n_uninit = 0           # --uninit-mem: fill/sentinel dwords neither build wrote, not judged
        self.max_ulp = 0.0
        self.max_ratio = 0.0

    def stats(self, valid, mism):
        return {"compared": valid, "bit_identical": valid - self.n_fp - self.n_oor - mism, "fp_tolerable": self.n_fp,
                "fp_floats": self.n_floats, "max_ulp": round(self.max_ulp, 2), "max_err_ratio": round(self.max_ratio, 2),
                "out_of_range": self.n_oor, "real_mismatches": mism, "uninit_dwords": self.n_uninit}

    def ref_run(self, inp):
        m = self.r.m
        touched = list(inp.touched)
        m.set_fpcw(FPCW_REF)
        self.fstore = {}        # dword address -> the last write to it was an x87/SSE float store
        code, fvals = {}, set()

        def on_write(uc, access, address, size, value, _):
            pc = uc.reg_read(UC_X86_REG_EIP)
            f = code.get(pc)
            if f is None:
                try:
                    ins = next(_md.disasm(bytes(uc.mem_read(pc, 15)), pc))
                    f = ins.mnemonic.startswith("fst") or ins.mnemonic in FP_STORES
                except (StopIteration, Exception):      # noqa: BLE001
                    f = False
                code[pc] = f
            if size >= 4:
                # an integer store of a value an x87/SSE store wrote earlier is a copied float (spill, then mov to the result)
                v = value & 0xFFFFFFFF
                if f:
                    fvals.add(v)
                self.fstore[address & ~3] = f or v in fvals
        self.huge_in = False        # the run read a dword that is a float Inf/NaN/above 1e30
        self.denorm_in = False      # ... or a denormal float (also what small integers look like)

        def on_read(uc, access, address, size, value, _):
            if size == 4 and not (self.huge_in and self.denorm_in):
                try:
                    v = struct.unpack("<I", bytes(uc.mem_read(address, 4)))[0]
                except Exception:      # noqa: BLE001
                    return
                e = (v >> 23) & 0xFF
                if e >= 127 + 100:        # |x| >= 2^100 (1.27e30), Inf or NaN
                    self.huge_in = True
                elif e == 0 and v & 0x7FFFFF:
                    self.denorm_in = True
        h = m.uc.hook_add(UC_HOOK_MEM_WRITE, on_write)
        h2 = m.uc.hook_add(UC_HOOK_MEM_READ, on_read)
        try:
            return self.r.run_side(self.r.orig, inp)
        finally:
            m.uc.hook_del(h)
            m.uc.hook_del(h2)
            m.set_fpcw(self.cw)
            inp.touched = touched

    def page(self, res, others, region, page, ik):
        """The page of `region` as `res` left it (falling back to what it started with in `res` and the other
        runs, then to the baseline); None for a pool page no run touched."""
        m = self.r.m
        x = res["mem"].get(region) or {}
        p = x.get(page)
        for o in [res] + list(others):
            if p is None and ik and o is not None:
                p = o.get(ik, {}).get(page)
        if p is not None:
            return p
        if ik:
            return None
        if region == "heap":
            return b"\0" * 0x1000
        if region == "misc":
            return m.misc_base_page(page)
        return m.image_base_page(region, page)

    def dword_diffs(self, a, b, ref):
        """[(region, page|None, base_addr, dword index, va, vb, vr)] for every differing dword of a and b
        that is not already tolerated as a stack pointer / pooled constant."""
        out = []
        esp = self.r.stk_hi
        for region in sorted(set(a["mem"]) | set(b["mem"])):
            if region == "ours_data":
                continue
            xa, xb = a["mem"].get(region), b["mem"].get(region)
            if isinstance(xa, dict) or isinstance(xb, dict) or region in ("pool", "extra"):
                ik = "pool_init" if region == "pool" else "extra_init" if region == "extra" else None
                pages = sorted(set(xa or {}) | set(xb or {}))
                items = [(pg, self.page(a, (b, ref), region, pg, ik), self.page(b, (a, ref), region, pg, ik),
                          self.page(ref, (a, b), region, pg, ik) if ref else None, pg) for pg in pages]
            else:
                if xa == xb or xa is None or xb is None:
                    continue
                items = [(None, xa, xb, None, self.r.args_hi)]
            for pg, pa, pb, pr, base in items:
                if pa is None or pb is None:
                    continue
                n = min(len(pa), len(pb)) // 4
                wa = np.frombuffer(pa[:4 * n], "<u4")
                wb = np.frombuffer(pb[:4 * n], "<u4")
                wr = np.frombuffer(pr[:4 * n], "<u4") if pr is not None and len(pr) >= 4 * n else None
                thr = None
                if ik:                      # --uninit-mem: the bytes this page started the input with
                    thr = (a.get(ik, {}).get(pg) or b.get(ik, {}).get(pg) or pa) if ik in ("pool_init", "extra_init") else None
                for k in np.nonzero(wa != wb)[0]:
                    va, vb = int(wa[k]), int(wb[k])
                    if in_stack_frame(va, esp) and in_stack_frame(vb, esp):
                        continue
                    if self.c.same_constant(va, vb):
                        continue
                    if self.c.uninit_excused(base + 4 * int(k), struct.pack("<I", va), struct.pack("<I", vb)):
                        continue            # excused by compare() too (Runner.uninit_copies): not a float to judge
                    if thr is not None and k * 4 + 4 <= len(thr) and \
                            getattr(self.opts, "uninit_mem", True):
                        # --uninit-mem: a dword the original left as a fill/sentinel leftover (one of
                        # FILL_PATTERNS, or the input value with a fill byte copied over it) that ours
                        # holds at its baseline value is unobserved - not a float difference to judge.
                        # Ours holding a value of its own, or ours having changed the input value when the
                        # original only stored it back, stays a real mismatch.
                        t0 = int(np.frombuffer(thr[k * 4:k * 4 + 4], "<u4")[0])
                        if vb == t0 and unobserved_fill(va, t0):
                            f = self.r.write_flags(base + 4 * int(k))
                            if not (f is not None and f[k] and va == t0):
                                self.n_uninit += 1
                                self.r.uncompared[(region, base + 4 * int(k))] = "fill 0x%08x" % va
                                continue
                    out.append((region, pg, base, int(k), va, vb, int(wr[k]) if wr is not None else va))
        return out

    def judge(self, a, b, inp, t):
        """-> ('fp' | 'oor', None) when only float rounding differs, else ('real', mismatch tuple)."""
        ref = self.ref_run(inp)
        if ref["status"][0] != "ok":
            return "real", ("fp-tol", "-", "-", "reference run (original at 64-bit precision) did not complete: %s" % (ref["status"],))
        floats = []          # (label, fa, fb, fr, bits, edit): edit = (region, page, dword index, orig dword) | "st0" | None
        for_st0 = a["fpu_depth"] and a["fpu_depth"] == b["fpu_depth"] and a["st0"] != b["st0"]
        if for_st0:
            fa, fb = x87_to_float(a["st0"]), x87_to_float(b["st0"])
            fr = x87_to_float(ref["st0"]) if ref["fpu_depth"] == a["fpu_depth"] and ref["st0"] is not None else fa
            pc = (a["fpcw"] >> 8) & 3
            floats.append(("st0", fa, fb, fr, 24 if pc == 0 else 53, "st0"))
        for region, pg, base, k, va, vb, vr in self.dword_diffs(a, b, ref):
            addr = base + 4 * k
            lbl = "memory %s @%08x" % (region, addr)
            if _tiny(va) or _tiny(vr):
                if not self.fstore.get(addr):
                    continue            # small value not stored by an x87/SSE store: an integer, left to compare()
                floats.append((lbl, float("inf"), 0.0, 0.0, 24, (region, pg, k, va)))     # denormal result: range case
                continue
            floats.append((lbl, _f32(va), _f32(vb), _f32(vr), 24, (region, pg, k, va)))
        # float arguments of import calls (FSOUND_3D_Listener_SetAttributes takes the listener frame by value: 0x4f8c80
        # passes values 1 ulp apart): judged like memory, against the reference run's same call
        ia, ib, ir = a.get("imports") or [], b.get("imports") or [], ref.get("imports") or []
        if len(ia) == len(ib) == len(ir):
            for k, (x, y, z) in enumerate(zip(ia, ib, ir)):
                if x[0] != y[0] or x[0] != z[0] or len(x[1]) != len(y[1]) or len(x[1]) != len(z[1]):
                    continue
                for j, (va, vb, vr) in enumerate(zip(x[1], y[1], z[1])):
                    if va == vb or not all(isinstance(v, int) for v in (va, vb, vr)):
                        continue
                    if _tiny(va) or _tiny(vb) or _tiny(vr):
                        continue        # a small integer / pointer-ish value: left to compare()
                    floats.append(("import call #%d %s arg %d" % (k, x[0], j), _f32(va), _f32(vb), _f32(vr), 24,
                                   ("import", k, j, va)))
        results = []
        for lbl, fa, fb, fr, bits, edit in floats:
            v, ulps, ratio, detail = fp_judge_value(fa, fb, fr, bits)
            if v == "inf":
                # Inf/NaN only in ours: out of range if the run read a float Inf/NaN/>1e30 input (an intermediate
                # overflowed float range in one build and stayed finite in the other's 80-bit register), else real
                v = "oor" if self.huge_in else "real"
            if v == "real" and self.denorm_in and max(abs(fa), abs(fb)) < 1e-30:
                v = "oor"       # near-underflow results of denormal inputs: the inputs feeding it are range values
            results.append((lbl, v, ulps, ratio, detail, edit))
        # make the judged float differences invisible to the exact comparison; whatever it still finds is not a float
        sane = dict(b)
        sane["mem"] = {k: (dict(v) if isinstance(v, dict) else v) for k, v in b["mem"].items()}
        edits = {}
        for lbl, v, _u, _r, _d, edit in results:
            if v == "real":
                continue
            if edit == "st0":
                sane["st0"] = a["st0"]
            elif edit[0] == "import":
                _k, k_, j_, va_ = edit
                imps = [list(c) for c in (sane.get("imports") or [])]
                args_ = list(imps[k_][1])
                args_[j_] = va_
                imps[k_][1] = tuple(args_) if isinstance(sane["imports"][k_][1], tuple) else args_
                sane["imports"] = [tuple(c) if isinstance(sane["imports"][i_], tuple) else c for i_, c in enumerate(imps)]
            else:
                edits.setdefault(edit[:2], []).append(edit[2:])
        for (region, pg), lst in edits.items():
            if region not in sane["mem"]:
                # the baseline never snapshotted this region (e.g. our object's .data when the original's run wrote
                # nothing there), so compare() does not look at it: nothing to hide (KeyError: '.data', hud 0x4d5410)
                continue
            if pg is None:
                buf = bytearray(sane["mem"][region])
            else:
                buf = bytearray(self.page(b, (a,), region, pg, "pool_init" if region == "pool" else "extra_init" if region == "extra" else None))
            for k, va in lst:
                if 4 * k + 4 <= len(buf):    # the page compare() will look at can be shorter than the one the
                    struct.pack_into("<I", buf, 4 * k, va)   # dword index was computed from: skip the edit, never crash
                # (an unapplied edit only means compare() still sees a float difference: the safe direction)
            if pg is None:
                sane["mem"][region] = bytes(buf)
            else:
                sane["mem"][region][pg] = bytes(buf)
        d = self.c.compare(a, sane, t)
        bad = next(((l_, dt) for l_, v, _u, _r, dt, _e in results if v == "real"), None)
        if d and bad and d[0].startswith("memory"):
            return "real", (bad[0] + " (fp-tol)", "-", "-", bad[1])
        if d:
            return "real", d
        if any(v == "oor" for _l, v, *_r in results):
            # a range case (Inf/NaN/denormal/>1e30 in the original's own result): not judged either way
            self.n_oor += 1
            return "oor", None
        if a["edges"] != ref["edges"]:
            return "real", ("control flow", "-", "-", "the original takes a different path at 64-bit precision (precision-sensitive branch); not judged as rounding")
        if bad:
            return "real", (bad[0] + " (fp-tol)", "-", "-", bad[1])
        for_stats = [(u, r) for _l, _v, u, r, _d, _e in results]
        self.n_fp += 1
        self.n_floats += len(results)
        for ulps, ratio in for_stats:
            self.max_ulp = max(self.max_ulp, ulps)
            if ratio is not None:
                self.max_ratio = max(self.max_ratio, ratio)
        return "fp", None


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


def fmt_val(v):
    if isinstance(v, int):
        return "%08x" % v
    if isinstance(v, tuple) and v and v[0] == "RO":
        return "RO:" + repr(v[1][:24])
    return str(v)


def fmt_reg(name, v):
    """A captured register value: 8 hex digits for a GPR, 32 for an xmm register."""
    return "%032x" % v if name in CALL_XMM else "%08x" % v


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

MAX_PROCS = int(os.environ.get("DIFFTEST_MAX_PROCS", os.cpu_count() or 2))


def cpu_slot():
    """Hold one of MAX_PROCS machine-wide slots (flock'd files) while emulating, so concurrent
    checkers (batch shards, agents) use at most one core each (DIFFTEST_MAX_PROCS, default all). Blocks until a slot is free."""
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


CACHE_DIR = os.path.join(S.ROOT, "work", "difftest", "equiv_cache")
_UNKEYED_OPTS = ("json", "verbose", "vas", "slice", "replay")
_harness_hash = None


def _cache_key(t, out, opts):
    """Key of everything the emulation depends on: the harness sources, the compiled object (non-debug sections, their
    relocations by symbol name, the symbol table; .debug$S carries the object's own path), the resolution of our
    symbols into the original image, the parsed signature/layout and the options. Same key -> same verdict, so a row
    whose code a header refactor left unchanged is not re-emulated. DIFFTEST_NO_CACHE=1 disables it."""
    global _harness_hash
    if os.environ.get("DIFFTEST_NO_CACHE"):
        return None
    import hashlib
    if _harness_hash is None:
        h = hashlib.sha1()
        for f in sorted(glob.glob(os.path.join(os.path.dirname(os.path.abspath(__file__)), "*.py"))):
            h.update(open(f, "rb").read())
        _harness_hash = h.hexdigest()
    c = t.coff
    h = hashlib.sha1(_harness_hash.encode())
    for sec in c.sections:
        if sec.discard:
            continue
        h.update(repr((sec.name, sec.flags, sec.size)).encode())
        h.update(sec.data)
        h.update(repr([(r[0], c.syms[r[1]].name if r[1] in c.syms else r[1], r[2]) for r in sec.relocs]).encode())
    h.update(repr([(sy.name, sy.value, sy.secno, sy.cls) for _, sy in sorted(c.syms.items())]).encode())
    h.update(repr(sorted((c.syms[i].name if i in c.syms else str(i), a) for i, a in t.res.addr.items())).encode())
    keep = {k: v for k, v in out.items() if k not in ("seconds",)}
    h.update(json.dumps(keep, sort_keys=True, default=str).encode())
    h.update(json.dumps({k: v for k, v in sorted(vars(opts).items()) if k not in _UNKEYED_OPTS},
                        sort_keys=True, default=str).encode())
    return h.hexdigest()


def test_function(sid, va, opts, log=print):
    fd = cpu_slot()
    try:
        r = _test_function(sid, va, opts, log)
    finally:
        os.close(fd)
    key = r.pop("_cache_key", None)
    if key and not r.get("cached") and r.get("verdict") in ("PASS", "WEAK", "FAIL", "PASS-FP", "WEAK-FP"):
        try:
            os.makedirs(CACHE_DIR, exist_ok=True)
            tmp = os.path.join(CACHE_DIR, "%s.%d.part" % (key, os.getpid()))
            json.dump(r, open(tmp, "w"))
            os.replace(tmp, os.path.join(CACHE_DIR, key + ".json"))
        except OSError:
            pass
    _ledger(r)
    return r


def _ledger(r):
    """Append one line per function result to work/opencode/attempts.jsonl (never in git).
    Model attribution comes from $OPENCODE_LEDGER_MODEL (set by the wave runners); empty if unset.
    DIFFTEST_NO_LEDGER=1 (harness re-grades, self-tests) writes nothing."""
    if os.environ.get("DIFFTEST_NO_LEDGER"):
        return
    try:
        rec = {"t": int(time.time()), "slice": r.get("slice"), "va": r.get("va"),
               "verdict": r.get("verdict"), "seconds": r.get("seconds"),
               "coverage": (r.get("coverage") or {}).get("pct"), "all": (r.get("coverage") or {}).get("all"),
               "edges": {k: v.get("pct") for k, v in (r.get("edges") or {}).items()},
               "valid": r.get("valid"), "inputs": r.get("inputs"), "orig_size": r.get("orig_size"),
               "wave": os.environ.get("OPENCODE_LEDGER_WAVE", ""),
               "model": os.environ.get("OPENCODE_LEDGER_MODEL", "")}
        p = os.path.join(S.ROOT, "work", "opencode", "attempts.jsonl")
        os.makedirs(os.path.dirname(p), exist_ok=True)
        with open(p, "a") as f:
            f.write(json.dumps(rec) + "\n")
    except Exception:
        pass          # releases the flock


def _test_function(sid, va, opts, log=print):
    t0 = time.time()
    t = prepare(sid, va, opts.flags, log, getattr(opts, "src", None))
    models = modelled_symbols(t)
    out = {"slice": sid, "va": "%08x" % va, "flags": " ".join(t.flags), "flags_from": t.flags_how,
           "symbol": getattr(t, "sym", None), "symbol_from": getattr(t, "sym_how", None),
           "unresolved": t.unresolved, "eh_unresolved": t.eh_unresolved,
           "modelled": models,
           "resolution_conflicts": [{"symbol": c[0], "resolved": "%08x" % c[1], "method": c[2], "aligned": "%08x" % c[3]}
                                    for c in t.conflicts],
           "resolution_methods": t.methods}
    if t.verdict == "UNSUPPORTED":
        out.update(verdict="UNSUPPORTED", reason=t.reason + model_note(models), seconds=round(time.time() - t0, 1))
        return out
    # Resolution audit (resaudit.py): every mapped reference vs the original's operand at the paired instruction.
    # A disagreement means our build would call/read something other than what the original does there, so any
    # PASS or FAIL would be meaningless (three wave-1 FAILs were wrong mappings): report it instead of running.
    aud = RA.audit(t.coff, t.fsym, t.res, t.orig_insns, context()["img"])
    out["resolution_audit"] = {"disagree": aud["disagree"], "unverified": aud["unverified"],
                               "local_copy": aud["local_copy"], "same_code": aud["same_code"],
                               "agree": len(aud["agree"]), "paired_insns": aud["pairs"], "insns": aud["insns"]}
    audit_warning = None
    if aud["disagree"]:
        # The audit pairs operands positionally, so a shifted-but-equivalent instruction stream "disagrees" without
        # saying anything about behaviour. Keep it as evidence and let the emulator decide; --strict-audit restores
        # the veto for a caller that wants the static gate.
        audit_warning = RA.summary(aud)
        out["audit_warning"] = audit_warning
        out["audit_disagree"] = aud["disagree"]
        if getattr(opts, "strict_audit", False):
            out.update(verdict="UNSUPPORTED", reason=audit_warning, seconds=round(time.time() - t0, 1))
            return out
    out.update(signature=str(t.sig) if t.sig else "unparsed (%s)" % getattr(t, "sig_error", "?"),
               stack_args=len(t.stack_kinds), reg_args=t.reg_kinds, callee_pop=t.callee_pop,
               ret_kind=t.ret_kind, layout_notes=t.layout_notes, orig_size=t.orig_hi - t.orig_lo,
               void_hides_eax=t.void_hides_eax, orig_untouched_regs=sorted(r for r in RF.GPR_SCRATCH + RF.XMM
                                                                          if r not in t.orig_regs_written))
    if t.abi_mismatch and not opts.ignore_abi:
        out.update(verdict="UNSUPPORTED", reason=t.abi_mismatch, seconds=round(time.time() - t0, 1))
        return out
    # Automatic --transparent: an original function our object runs its OWN copy of (the audit pairs a local copy
    # with it at the call sites). The original's call to it is replaced in the call trace by the calls it makes,
    # as ours already is: without this, every row whose TU defines its callees (the interpreter 0x49fa10 with
    # report and its 18 validators) FAILed on the call boundary alone. Until 2026-10-29 only copies the source
    # also marks `// @ 0x<va>` qualified, which left camera.cpp's static copy of report (0x49cc60, commented but
    # unmarked) a call-boundary FAIL of set_lvalue 0x49d500. Transparency never hides a difference (the inner
    # calls, memory and registers are still compared), so the audit's pairing is enough.
    opts.transparent_auto = []
    if not getattr(opts, "no_auto_transparent", False) and aud.get("local_copy"):
        paired = {int(o, 16) for lc in aud["local_copy"] for o in lc.get("original", [])}
        # Nested copies: a copy's own callees can be copies too (camera.cpp's check_party copy of 0x49d160 calls its
        # report copy of 0x49cc60). Ours expands both, so the original must expand both: audit each paired copy
        # against its original and take the copies it pairs, a few levels deep.
        frontier = [(lc["symbol"], int(o, 16)) for lc in aud["local_copy"] for o in lc.get("original", [])]
        done = set()
        for _depth in range(3):
            nxt = []
            for nm, ova in frontier:
                if (nm, ova) in done or ova == va:
                    continue
                done.add((nm, ova))
                for lc2 in _audit_copy(t, nm, ova):
                    for o in lc2.get("original", []):
                        if int(o, 16) not in paired:
                            paired.add(int(o, 16))
                        nxt.append((lc2["symbol"], int(o, 16)))
            frontier = nxt
        opts.transparent_auto = sorted(paired - {va})
        if opts.transparent_auto:
            out["transparent_auto"] = ["%08x" % v for v in opts.transparent_auto]
    regress = regress_inputs(sid, va, opts)
    opts.regress_set = [f for f, _i in regress]      # keyed: a new regression input re-runs the row
    key = _cache_key(t, out, opts)
    if key:
        try:
            hit = json.load(open(os.path.join(CACHE_DIR, key + ".json")))
            hit.update(cached=True, seconds=round(time.time() - t0, 1), cached_seconds=hit.get("seconds"))
            log("  equiv cache hit (same object, resolution and options as an earlier run)")
            return hit
        except (OSError, ValueError):
            out["_cache_key"] = key
    runner = Runner(t, opts, log)
    cmp_ = Comparer(runner, opts)
    fpt = FpTol(runner, cmp_, opts) if getattr(opts, "fp_tol", False) else None
    rng_master = random.Random("%s:%08x:%d" % (sid, va, opts.seed))
    gen = runner.gen
    corpus = []
    valid, discarded, mism, first = 0, {}, 0, None
    sigs = collections.Counter()
    traps = {}
    repaired = 0
    faked = 0
    ran = 0
    ours_probe = 0
    probes = 0
    deadline = time.time() + opts.time_limit
    steer = ST.Steer(runner, gen, opts) if getattr(opts, "steer", True) else None
    hard = opts.inputs + (opts.extra_inputs if steer else 0)
    pass_at = None
    i = -1
    try:
        while True:
            i += 1
            if i >= hard:
                break
            if i >= opts.inputs and not (steer and corpus and edges_missing(runner) and steer.has_work()):
                break               # past --inputs only while steering still has uncovered branches to try
            # Early exits (--no-early: off). Neither changes what a verdict means, only how many inputs it took:
            # - PASS bar met: no mismatch, >= --min-valid valid inputs and every required edge of both builds
            #   covered; --early-margin more inputs still run (a value-only difference on a covered path) and then
            #   the row stops instead of finishing --inputs. Saved regression inputs always run first.
            # - nothing valid: --early-invalid inputs in and not one was valid. The row would end "only n/N inputs
            #   valid" (UNSUPPORTED) unless the rest of the stream turned it round, which the M&B sweep never saw.
            if getattr(opts, "early", True) and i >= len(regress) and getattr(opts, "gate", "edges") == "edges":
                if not mism and valid >= opts.min_valid and not edges_missing(runner):
                    if pass_at is None:
                        pass_at = i
                    if i >= pass_at + opts.early_margin:
                        out["early_exit"] = ("PASS bar met at input %d; stopped %d inputs later" %
                                             (pass_at, opts.early_margin))
                        break
                if not valid and i >= opts.early_invalid:
                    out["early_exit"] = "no valid input in the first %d" % i
                    break
            if time.time() > deadline:
                out["stopped_early"] = "time limit %ds after %d inputs" % (opts.time_limit, i)
                break
            ran += 1
            rng = random.Random(rng_master.getrandbits(64))
            inp = None
            if steer and corpus and i >= len(regress) and (i >= opts.inputs or rng.random() < opts.steer_share):
                inp = steer.next(rng, corpus)
            if inp is None and i < len(regress):
                inp = regress[i][1]
                inp.origin = "regress"
            if inp is None:
                if corpus and rng.random() < opts.mutate:
                    parent = steer.pick_parent(corpus, rng) if steer else \
                        corpus[-1 - min(int(rng.expovariate(0.15)), len(corpus) - 1)]
                    inp = gen.mutate(parent, rng, corpus)
                else:
                    inp = gen.fresh(rng)
            try:
                a = runner.run_side(runner.orig, inp)
                fixes = pure_fixes = heap_fixes = 0
                while time.time() < deadline:
                    st_ = a["status"]
                    if st_[0] == "fault" and a["fault"] and a["fault"][0] != "pool-limit" and fixes < opts.repairs:
                        fixes += 1
                        rep = runner.repair(inp, a["fault"], rng, fixes - 1)
                    elif st_[0] == "import" and M.is_heap_exhausted(st_[1]) and heap_fixes < 4 and opts.repairs:
                        heap_fixes += 1
                        rep = runner.repair_heap(inp, st_[1], rng)
                    elif st_[0] == "import" and str(st_[1]).split(":")[0] == "_purecall" and \
                            pure_fixes < opts.repairs:
                        # a random input drove a vtable call through a slot that is still the pure-call
                        # stub: resample the class pointer/vtable the input carried and keep the first
                        # attempt that gets past it instead of burning the input
                        pure_fixes += 1
                        rep = runner.repair_pure(inp, rng)
                    else:
                        break
                    if rep is None:
                        break
                    inp = rep
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
                if st == "import" and ours_probe < OURS_IMPORT_PROBES and \
                        not M.is_heap_exhausted(a["status"][1]):
                    # our side's call sites that stop at the same import (for its 'blocked' edges): run it,
                    # never compare. A heap-exhausted original is discarded by the caller, so probing our
                    # side along that path would only build a second partial run (and the probe is a copy
                    # of the discarded run's state, not of an accepted one).
                    ours_probe += 1
                    runner.run_side(runner.ours, inp)
            except UcError as e:
                # one input whose run trips the emulator (a hook reading unmapped memory: fake_call's argument
                # peek, save_state 0x4e9620) must not kill the row - discard it and carry on. Setup and compile
                # errors stay fatal above.
                discarded["fault(unmapped)"] = discarded.get("fault(unmapped)", 0) + 1
                if opts.verbose:
                    log("  discard input %d: UcError: %s" % (i, str(e)[:120]))
                continue
            if st != "ok":
                key = "wall-timeout" if st == "wall" else (st if st != "import" else "import:%s" % str(a["status"][1]).split(":")[0])
                if st == "fault" and a["fault"]:
                    key = "fault(%s)" % a["fault"][0]
                if st == "fault" and len(runner.fault_runs) < FAULT_EDGE_RUNS:
                    # the original faulted on this input even after the repairs: if ours faults too, the edges each
                    # took are evidence about paths no valid input can take (edge_report: "fault-only")
                    b_ = runner.run_side(runner.ours, inp)
                    runner.fault_runs.append(1)
                    if b_["status"][0] == "fault":
                        for nm_, side_, o_ in (("orig", runner.orig, a), ("ours", runner.ours, b_)):
                            runner.fault_edges[nm_] |= faulting_edges(side_, o_)
                if key in ("timeout", "wall", "wall-timeout"):
                    out["wall_timeout"] = out.get("wall_timeout", 0) + 1
                if st == "import" and M.is_heap_exhausted(a["status"][1]):
                    # the original ran the emulated heap out of address space: the end state is not
                    # comparable (the run did not finish), and the discarded input is not a difference.
                    key = "heap-exhausted"
                    out["heap_exhausted"] = out.get("heap_exhausted", 0) + 1
                if st == "budget" and runner.budget >= opts.budget:
                    # --budget is the row's instruction cap and the budget probe above could not get past it:
                    # the original was cut off mid-run, so its end state (heap, registers, memory) is a
                    # partial one and comparing it would report the truncation as a difference. The rows this
                    # matters for are the ones whose ORIGINAL stalls on a do-nothing import long enough to burn
                    # the whole cap (camera 0x49b630: cut off mid-malloc), so the count is reported and the row
                    # is not given a verdict at all - it must be re-run with a larger --budget instead.
                    key = "budget(cut-off)"
                    out["budget_cutoff"] = out.get("budget_cutoff", 0) + 1
                discarded[key] = discarded.get(key, 0) + 1
                if opts.verbose and st == "fault" and a["fault"]:
                    log("  discard input %d: fault %s" % (i, " ".join(
                        "%#x" % x if isinstance(x, int) else str(x) for x in a["fault"])))
                continue
            if not runner.abi_ok(a):
                # the original itself returned with clobbered callee-saved registers or a wrong esp:
                # a fake method popped the wrong number of bytes, or the input sent it through
                # non-code (e.g. a vtable pointer into .text). Says nothing about equivalence.
                key = "orig-abi-broken(fake)" if a["fakes"] else "orig-abi-broken"
                discarded[key] = discarded.get(key, 0) + 1
                continue
            if fixes or pure_fixes:
                repaired += 1
            # Input-object invariants, on the FINAL input (generation edits, steering and every fault repair
            # applied): an object whose length field is outside the declared capacity of the array the
            # function indexes cannot exist, so the two builds would be compared on out-of-array frame or
            # pool bytes - a property of their layouts, not of the code. Discard before comparing, and say
            # which field and how many inputs (never silent: the key, the count and the bound are reported).
            if gen.invs:
                bad = INV.check(gen.invs, gen, inp)
                if bad:
                    label, value, lo, hi, inv = bad
                    discarded["invalid-object"] = discarded.get("invalid-object", 0) + 1
                    out.setdefault("invalid_objects", {})
                    out["invalid_objects"][label] = out["invalid_objects"].get(label, 0) + 1
                    if "invalid_object_example" not in out:
                        out["invalid_object_example"] = "%s=%d outside [%d..%d]; %s" % (
                            label, value - (1 << 32) if value >= (1 << 31) else value, lo, hi, inv.why)
                    if opts.verbose:
                        log("  discard input %d: invalid object: %s=%#x outside [%d..%d]" % (i, label, value, lo, hi))
                    continue
            run_blocks = runner.run_blocks
            try:
                b = runner.run_side(runner.ours, inp)
            except UcError as e:
                discarded["fault(unmapped)"] = discarded.get("fault(unmapped)", 0) + 1
                if opts.verbose:
                    log("  discard input %d (ours): UcError: %s" % (i, str(e)[:120]))
                continue
            sb = b["status"]
            if sb[0] == "trap":
                traps[sb[1]] = traps.get(sb[1], 0) + 1
                discarded["ours-trap"] = discarded.get("ours-trap", 0) + 1
                continue
            if sb[0] == "budget" or (sb[0] == "import" and M.is_heap_exhausted(sb[1])):
                # our pass was cut off by the same cap (or ran the heap out of address space) while the
                # original returned normally: 'ours failed where the original succeeded' would read as a
                # real difference, but neither is: the pass did not finish. Both counters are reported and
                # the row gets no verdict (see the budget-cutoff/heap-exhausted chain below).
                if sb[0] == "budget":
                    key = "budget(cut-off-ours)"
                    out["cutoff_ours"] = out.get("cutoff_ours", 0) + 1
                else:
                    key = "heap-exhausted(ours)"
                    out["heap_exhausted_ours"] = out.get("heap_exhausted_ours", 0) + 1
                discarded[key] = discarded.get(key, 0) + 1
                continue
            if sb[0] == "fault" and runner.wild_eip(sb[1]):
                # our pass faulted executing *between* the instructions of an image function: it got there
                # through a soup code pointer (a misaligned soup vtable's slot, report 0x49cc60's call [edx+0x28]
                # into 0x435100), and whether such bytes fault depends on incidental register values, so the
                # original's run of the same garbage proves nothing either. Not information about the code.
                discarded["wild-code"] = discarded.get("wild-code", 0) + 1
                continue
            if b["fakes"] and sb[0] == "ok" and not runner.abi_ok(b):
                discarded["ours-abi-broken(fake)"] = discarded.get("ours-abi-broken(fake)", 0) + 1
                continue
            if a["fakes"] or b["fakes"]:
                fa, fb = {}, {}
                for tg, n, _e, _a in a["fakes"]:
                    fa.setdefault(tg, set()).add(n)
                for tg, n, _e, _a in b["fakes"]:
                    fb.setdefault(tg, set()).add(n)
                if any(len(v) > 1 for v in list(fa.values()) + list(fb.values())) or \
                        any(fa[k] != fb[k] for k in set(fa) & set(fb)):
                    discarded["fake-arity"] = discarded.get("fake-arity", 0) + 1
                    continue
                faked += 1
            valid += 1
            new = bool(run_blocks - runner.blocks) or bool(a["edges"] - runner.orig.edges) or \
                bool(sb[0] == "ok" and b["edges"] - runner.ours.edges)
            runner.blocks |= run_blocks
            runner.orig.edges |= a["edges"]
            if sb[0] == "ok":
                runner.ours.edges |= b["edges"]
            if new:
                corpus.append(inp)
            if steer:
                steer.note_valid(inp, {"orig": a["edges"], "ours": b["edges"] if sb[0] == "ok" else set()})
            cmp_.last_kind = None
            if sb[0] != "ok":
                d = ("execution", "returned normally", "%s: %s" % sb, "ours failed where the original succeeded")
            else:
                d = cmp_.compare(a, b, t)
                if d and fpt is not None:
                    kind_, d_ = fpt.judge(a, b, inp, t)
                    if kind_ == "real":
                        d = d_
                        if d_[0].endswith("(fp-tol)") or d_[0] in ("fp-tol", "control flow"):
                            cmp_.last_kind = None   # an fp judgement replaced the compared observable
                    else:
                        d = None
                if d and d[0].startswith("memory") and getattr(opts, "uninit_copy", True):
                    # the original may have copied an uninitialised local there: re-compare without those dwords
                    # (the original's run of this input is re-done once with copy taint; see uninit_copies)
                    u = runner.uninit_copies(inp)
                    if u:
                        cmp_.uninit_copy = u
                        try:
                            d2 = cmp_.compare(a, b, t)
                            if d2 and fpt is not None:
                                kind_, d2_ = fpt.judge(a, b, inp, t)
                                d2 = d2_ if kind_ == "real" else None
                        finally:
                            cmp_.uninit_copy = frozenset()
                        d = d2
            if d:
                mism += 1
                sigs[mismatch_sig(d)] += 1
                if getattr(inp, "origin", None) == "regress":
                    out["regress_failed"] = out.get("regress_failed", 0) + 1
                else:
                    save_regress(sid, va, opts, inp)
                if first is None and opts.call_regs:
                    # --call-regs: where the live register file at a call site first differs (independent of
                    # which observable the mismatch names, so a register difference can be the explanation)
                    out["call_regs"] = cmp_.call_reg_diff(a, b)
                if first is None:
                    first = {"input": i, "profile": inp.profile, "origin": inp.origin, "observable": d[0],
                             "kind": cmp_.last_kind or ("float-rounding" if d[0] == "st0" else "value"),
                             "orig": d[1], "ours": d[2], "detail": d[3], "args": ["%08x" % w for w in inp.args],
                             "regs": {k: "%08x" % v for k, v in inp.regs.items()},
                             "fake_calls": len(a["fakes"]), "repairs": fixes}
                    if getattr(inp, "alloc_fail", ()):
                        first["alloc_fail"] = list(inp.alloc_fail)      # these malloc/new calls returned NULL
                    if getattr(inp, "extra", {}):
                        first["mapped_at_fault"] = ["%08x+%x" % kv for kv in sorted(inp.extra.items())]
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
    if steer:
        out["steering"] = dict(steer.stats, constants=steer.n_consts, queued=steer.made)
    covered = set()
    for (ba, bs) in runner.blocks:
        for a in range(ba, ba + bs):
            if a in t.orig_insns:
                covered.add(a)
    total = len(t.orig_insns)
    cov = 100.0 * len(covered) / total if total else 0.0
    out["mismatch_sigs"] = dict(sigs.most_common(40))
    if gen.invs:
        out["input_invariants"] = describe_invariants(gen.invs)
    out["regress_inputs"] = len(regress)
    out.update(seed=opts.seed, inputs_planned=opts.inputs, extra_inputs=opts.extra_inputs if getattr(opts, "steer", True) else 0,
               gate=opts.gate, require_all=bool(getattr(opts, "require_all", False)),
               inputs=ran, valid=valid, discarded=discarded, mismatches=mism, first_mismatch=first,
               coverage={"covered_insns": len(covered), "total_insns": total, "pct": round(cov, 1),
                         "all": len(covered) >= total,
                         "missed": ["%08x" % a for a in sorted(set(t.orig_insns) - covered)][:64]},
               tolerated=cmp_.tolerated, ours_traps=traps)
    ecov = out["edges"] = {nm: edge_report(runner, side, opts) for nm, side in (("orig", runner.orig), ("ours", runner.ours))}
    if opts.ulp:
        out["ulp"] = opts.ulp
    if fpt is not None:
        out["fp_tol"] = fpt.stats(valid, mism)
    budget_cut = out.get("budget_cutoff", 0) + out.get("cutoff_ours", 0)
    cut_total = max(1, budget_cut + valid)
    # Every "the run was cut short" excuse is subordinate to a real difference: if the two builds already
    # disagreed on a comparable input, the row is a FAIL whatever else happened. (Before this, 16
    # heap-exhausted inputs turned agent_hud 0x4fba40's 200 real mismatches into "no verdict".)
    if out.get("stopped_early") and (not mism or not valid):
        # The input stream is deterministic (--inputs + --seed); the wall clock is not. A row cut short by the
        # row-level deadline must not report a verdict at all: on a loaded machine that turned FAILs into WEAKs
        # (16 of 82 rows in one sweep). Raise --time-limit or run fewer workers.
        v, why = "UNSUPPORTED", ("not a verdict: %s; the run was cut short by the wall-clock limit, everything "
                                 "measured so far is in this JSON" % out["stopped_early"])
    elif not mism and out.get("wall_timeout"):
        v, why = "UNSUPPORTED", ("not a verdict: %d input run(s) were cut by the per-run wall-clock cap (--run-seconds); "
                                 "raise it so the verdict depends only on --inputs and --seed" % out["wall_timeout"])
    elif not mism and not valid and budget_cut:
        # A *runaway* input (the budget probe already tried the full --budget) leaves a partial end state, so
        # comparing it would report the truncation as a difference (camera 0x49b630: cut off inside malloc, pool
        # high-water sentinels compared). One such input among hundreds of clean ones is a runaway to discard;
        # a row where they are >=5% of the runs has no comparable state at all and gets no verdict - re-run it
        # with a larger --budget. (resmgr 0x41aee0: 1 of 260, so it keeps its verdict.)
        v, why = "UNSUPPORTED", ("not a verdict: %d of %d input(s) were cut off by the --budget instruction cap "
                                 "(the end state compared would be a partial run). Raise --budget for this row"
                                 % (budget_cut, cut_total))
    elif not mism and not valid and (out.get("heap_exhausted", 0) + out.get("heap_exhausted_ours", 0)):
        # An input that ran the emulated heap out of address space leaves a partial end state on BOTH sides
        # in general (and on ours alone when only our pass exhausted it), so it is discarded rather than
        # compared. Same share rule as the instruction cap: one such input among hundreds is a runaway whose
        # end state is discarded; a row where they are >=5% of the runs has no comparable state at all.
        v, why = "UNSUPPORTED", ("not a verdict: %d input(s) ran the emulated heap out of address space "
                                 "(%d in the original's pass, %d in ours); neither run has a comparable end state"
                                 % (out.get("heap_exhausted", 0) + out.get("heap_exhausted_ours", 0),
                                    out.get("heap_exhausted", 0), out.get("heap_exhausted_ours", 0)))
    elif mism and first.get("kind") == "local-address":
        # our code stores the address of its own copy of an object/vtable/constant where the original
        # stores the image's: same_local_copy already accepted every copy whose bytes are identical, so
        # what is left is a real difference - the detail names the differing dwords of the block.
        v, why = "FAIL", ("%d/%d valid inputs mismatched; first: %s (our code stores the address of its own "
                          "copy where the original stores the image's; %s)" % (
                              mism, valid, first["observable"], first.get("detail") or "the copies differ"))
    elif mism:
        v, why = "FAIL", "%d/%d valid inputs mismatched; first: %s" % (mism, valid, first["observable"])
    elif traps:
        v, why = "UNSUPPORTED", "our code reached unresolved symbol(s) %s" % ", ".join(sorted(traps))
    elif valid < max(10, ran // 20):
        top = sorted(discarded.items(), key=lambda x: -x[1])[:3]
        v, why = "UNSUPPORTED", "only %d/%d inputs valid (discards: %s)" % (valid, ran, ", ".join("%s=%d" % x for x in top))
    elif getattr(opts, "gate", "edges") == "insns":
        # legacy gate (before 2026-10-21): instruction coverage of the original only
        if valid >= opts.min_valid and (len(covered) >= total if getattr(opts, "require_all", False) else cov >= opts.min_cov):
            v, why = "PASS", "%d valid inputs, %.1f%% coverage%s [legacy insns gate]" % (
                valid, cov, " (all insns)" if getattr(opts, "require_all", False) else "")
        else:
            need = "100%% (all insns)" if getattr(opts, "require_all", False) else "%.0f%%" % opts.min_cov
            v, why = "WEAK", "%d valid inputs (need %d), %.1f%% coverage (need %s) [legacy insns gate]" % (
                valid, opts.min_valid, cov, need)
    else:
        missed = [nm for nm in ("orig", "ours") if ecov[nm]["missed_n"]]
        edges_txt = "; ".join(edge_summary(nm, ecov[nm]) for nm in ("orig", "ours"))
        all_insns = len(covered) >= total or not getattr(opts, "require_all", False)
        if valid >= opts.min_valid and not missed and all_insns:
            v, why = "PASS", "%d valid inputs, all edges covered (%s), %.1f%% insns" % (valid, edges_txt, cov)
        else:
            need = []
            if valid < opts.min_valid:
                need.append("%d valid inputs (need %d)" % (valid, opts.min_valid))
            for nm in missed:
                need.append("%s misses %d edge(s)" % (nm, ecov[nm]["missed_n"]))
            if not all_insns:
                need.append("--require-all: %d original insns never ran" % (total - len(covered)))
            v, why = "WEAK", "%s; edges %s; %.1f%% insns" % (", ".join(need), edges_txt, cov)
    if cmp_.tolerated.get("local-copy") and v in ("PASS", "WEAK"):
        # our code stored the address of its own copy where the original stores the image's, and the
        # bytes at both were identical: an address difference only (the linker kept two copies)
        why += ("; note: %d address(es) of our own copy of the image's block differed in address only "
                "(the bytes matched)" % cmp_.tolerated["local-copy"])
    if cmp_.tolerated.get("stale-return-address") and v in ("PASS", "WEAK"):
        why += ("; note: %d dword(s) held a return address of the tested function on both sides (a stale stack "
                "slot copied out by an uninitialised read), not compared" % cmp_.tolerated["stale-return-address"])
    if (cmp_.tolerated.get("stub-scratch") or getattr(runner, "trimmed", None)) and \
            v in ("PASS", "WEAK", "FAIL", "PASS-FP", "WEAK-FP"):
        # class 3: dwords/pages that ONLY the original's run wrote, through an import whose handler is a
        # do-nothing stub (sprintf, strcpy, ...). Leftover scaffold for the input, not information about the
        # code; excused by name so nothing becomes invisible. Our pass wrote none of them. The dict is shared
        # with the class-1 (fill-leftover) rule, so only the stub names are counted here: an entry whose value
        # starts with "fill" belongs to that rule and is reported by it.
        byn = collections.Counter(nm for nm in (runner.uncompared or {}).values()
                                  if not str(nm).startswith("fill"))
        if cmp_.tolerated.get("stub-scratch"):
            why += "; note: %d dword(s) written only by the original's do-nothing stub(s) were not compared (%s)" % (
                cmp_.tolerated["stub-scratch"],
                ", ".join("%s: %d" % (k, n) for k, n in byn.most_common(3)) or "unnamed stub")
        if getattr(runner, "trimmed", None):
            why += "; %d page(s) trimmed" % len(runner.trimmed)
    if audit_warning and v in ("PASS", "WEAK"):
        why += "; audit advisory (positional pairing): " + audit_warning
    if fpt is not None and v in ("PASS", "WEAK") and fpt.n_fp + fpt.n_oor:
        fs = out["fp_tol"]
        v += "-FP"
        why += ("; fp-tol: %d compared, %d bit-identical, %d fp-tolerable (max %.3g ulp, max err ratio %.3g), "
                "%d out-of-range, %d real mismatches" % (fs["compared"], fs["bit_identical"], fs["fp_tolerable"],
                                                         fs["max_ulp"], fs["max_err_ratio"], fs["out_of_range"],
                                                         fs["real_mismatches"]))
    if v == "FAIL" and aud["local_copy"]:
        # our own copy of a callee ran where the original calls a real function: a call-trace FAIL may be that
        why += "; NOTE " + RA.summary(aud)
    if opts.call_regs and out.get("call_regs"):
        why += "; " + cmp_.call_reg_note(out["call_regs"])
    why += model_note(models)               # a run kept alive by a harness model: say so in the reason ...
    n_inv = discarded.get("invalid-object")
    if n_inv:
        # Never silent: a row that discarded inputs says how many, which field, and the bound it broke, so
        # a reader can tell that the verdict rests on fewer inputs and check the bound themselves.
        why += "; invalid-object: %d input(s) discarded (declared %s)%s" % (
            n_inv, describe_invariants(gen.invs), "; e.g. " + out["invalid_object_example"]
            if out.get("invalid_object_example") else "")
    v = model_capped(v, models)             # ... and never report PASS on modelled symbols
    out.update(verdict=v, reason=why, seconds=round(time.time() - t0, 1))
    return out


OURS_IMPORT_PROBES = 40


def mismatch_sig(d):
    """Run-independent signature of one mismatch for the JSON tally: the observable with addresses reduced to
    their low 12 bits (heap/pool bases differ per input, field offsets do not), plus the differing offsets."""
    import re as _re
    obs = _re.sub(r"@([0-9a-f]{5,8})", lambda m: "+" + m.group(1)[-3:], str(d[0]))
    offs = sorted({a[-3:] for a in _re.findall(r"([0-9a-f]{8}): [0-9a-f]{8}/", str(d[3]))})
    return obs + ((" [" + ",".join(offs[:8]) + "]") if offs else "")


NORETURN_WHY = {"_purecall": "pure virtual call", "_CxxThrowException": "C++ throw", "RaiseException": "C++ throw"}


def noreturn_stop(why):
    """A run stopped in an import that can never return to the function: no handler (unmodelled), a C++ throw,
    or a pure virtual call. Handler stops that depend on the input (a huge malloc/memcpy) are not."""
    why = str(why)
    return ":" not in why or why.split(":")[0] in NORETURN_WHY


def edges_missing(runner):
    scope = getattr(runner, "edge_scope", None)
    if scope is not None:           # --edge-scope: only the original's edges the run is about
        return bool(scope - runner.orig.edges - runner.orig.cfg_static_unreachable)
    return any(set(side.cfg.edges) - side.edges - side.cfg_static_unreachable for side in (runner.orig, runner.ours))


def faulting_edges(side, o):
    """The edges of run o (which faulted) into the block the fault happened in: the taken edge (src, dst) with
    dst <= fault eip and no branch of the function's CFG between dst and the fault. Only these say the path
    cannot complete; an edge taken earlier in a run that faulted later says nothing about itself."""
    mm = re.search(r"eip=([0-9a-f]{8})", str(o["status"][1]))
    if not mm:
        return set()
    eip = int(mm.group(1), 16)
    srcs = sorted({e[0] for e in side.cfg.edges})
    import bisect
    out = set()
    for e in o.get("edges", ()):
        if e[1] <= eip:
            k = bisect.bisect_left(srcs, e[1])
            if k == len(srcs) or srcs[k] >= eip:
                out.add(e)
    return out


def edge_report(runner, side, opts):
    """Edge coverage of one side: totals, the uncovered edges the harness cannot reach (each with its
    reason) and the remaining missed edges (which make the verdict WEAK)."""
    cfg = side.cfg
    allx = set(cfg.edges)
    cov = side.edges & allx
    unr = cfg.unreachable(cov, runner.blocked_calls(side), nan=opts.nan)
    # an edge into the faulting block of inputs on which BOTH builds fault, that no valid run took: the path
    # cannot complete -- the NULL-vector arm of `n = first ? (last - first) >> 2 : 0` that then reads
    # first[n - 1] (mission_4 0x48f480) -- so it is not coverage a valid input could add
    fo = getattr(runner, "fault_edges", {}).get("orig" if side is runner.orig else "ours", set())
    for e in allx - cov - set(unr):
        if e in fo:
            unr[e] = "leads straight to a fault in both builds (every input that took it)"
    missed = sorted(allx - cov - set(unr))
    req = len(allx) - len(unr)
    return {"total": len(allx), "covered": len(cov), "required": req,
            "pct": round(100.0 * len(cov) / req, 1) if req else 100.0,
            "unreachable": [{"edge": CF.fmt_edge(e), "reason": unr[e]} for e in sorted(unr)],
            "missed_n": len(missed), "missed": [CF.fmt_edge(e) for e in missed[:None if getattr(opts, "full_edges", False) else 64]],
            **({"covered_edges": [CF.fmt_edge(e) for e in sorted(cov)]} if getattr(opts, "full_edges", False) else {})}


def edge_summary(nm, r):
    s = "%s %d/%d" % (nm, r["covered"], r["required"])
    if r["unreachable"]:
        s += " (+%d unreachable)" % len(r["unreachable"])
    return s


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
            print("    import", fmt_call((ent[0], tuple(norm_val(v, runner.stk_hi) for v in ent[1]))))
    print("first difference:", cmp_.compare(a, b, t) if a["status"][0] == b["status"][0] == "ok" else "status differs")
    if opts.call_regs and a["status"][0] == b["status"][0] == "ok":
        crd = cmp_.call_reg_diff(a, b)
        if crd:
            print("  " + cmp_.call_reg_note(crd))
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
    ap.add_argument("--require-all", action="store_true",
                    help="a PASS also requires every original instruction to execute (legacy insns gate: instead of --min-cov)")
    ap.add_argument("--gate", choices=("edges", "insns"), default="edges",
                    help="edges (default): PASS needs every reachable branch edge covered on BOTH builds; "
                         "insns: the legacy gate (original's instruction coverage >= --min-cov)")
    ap.add_argument("--ulp", type=int, default=0)
    ap.add_argument("--strict-calls", action="store_true")
    ap.add_argument("--call-regs", action="store_true",
                    help="capture the full register file (eax ebx ecx edx esi edi ebp esp, xmm0-3) at every "
                         "recorded call site (depth-1 calls, imports, fake calls) and report the first difference "
                         "no tolerance explains: index, callee and values, in the result's 'call_regs' and the "
                         "reason. A diagnostic only - the verdict is unchanged")
    ap.add_argument("--call-regs-strict", action="store_true",
                    help="--call-regs, and a register difference is a mismatch instead of a diagnostic: an input "
                         "that matches every other observable but differs in a live register at a call pair whose "
                         "callee and arguments still agree FAILs")
    ap.add_argument("--strict-audit", action="store_true",
                    help="keep the old behaviour: a resolution-audit disagreement aborts with UNSUPPORTED. By default "
                         "the audit is advisory - the emulator runs anyway and the disagreement is recorded in the "
                         "result (66 rows were blocked by positional operand pairing alone)")
    ap.add_argument("--budget", type=int, default=DEFAULT_BUDGET, help="max instructions per original run (ours: 4x)")
    ap.add_argument("--start-budget", type=int, default=START_BUDGET,
                    help="initial cap; raised to --budget if one of the first %d capped inputs finishes under it" % BUDGET_PROBES)
    ap.add_argument("--time-limit", type=int, default=180, help="seconds per function")
    ap.add_argument("--run-seconds", type=float, default=0,
                    help="wall-clock cap per original run (ours: 4x). Default 0 = off: a wall-clock stop depends on "
                         "machine load, so with it on, any row that hits it reports no verdict (only --inputs and "
                         "--seed decide); the instruction budget (--budget) bounds every run deterministically")
    ap.add_argument("--max-mismatch", type=int, default=5)
    ap.add_argument("--no-fake-calls", dest="fake_calls", action="store_false",
                    help="discard inputs that call through a generated function pointer instead of emulating a do-nothing method")
    ap.add_argument("--transparent", type=lambda v: [int(x, 16) for x in v.split(",")], default=None,
                    help="comma-separated image function VAs (hex) whose calls the depth-1 call trace replaces by the "
                         "calls they make themselves (e.g. a vector deleting destructor one build inlined and the "
                         "other calls); arguments, memory, registers and imports are still compared")
    ap.add_argument("--stub", type=lambda v: [int(x, 16) for x in v.split(",") if x], default=STUB_LOOKUPS,
                    help="comma-separated image function VAs (hex) that return an input object instead of running "
                         "(default: the resource lookups that exit() on a missing name; '' for none)")
    ap.add_argument("--no-force-results", dest="force_results", action="store_false",
                    help="never force the result of a branch-feeding callee (Runner._on_forced)")
    ap.add_argument("--no-uninit-copy", dest="uninit_copy", action="store_false",
                    help="compare every dword, including those the original only copied from an uninitialised stack "
                         "slot (Runner.uninit_copies: a vector4's unset w passed by value)")
    ap.add_argument("--no-auto-transparent", action="store_true",
                    help="do not make the source's own marked functions transparent automatically (see transparent_auto)")
    ap.add_argument("--ignore-abi", action="store_true", help="run even if the original reads an undeclared register argument")
    ap.add_argument("--repairs", type=int, default=24, help="fault repairs per input (0 = off)")
    ap.add_argument("--nan", action="store_true", help="also generate NaN/Inf float bit patterns")
    ap.add_argument("--fpcw", default="%04X" % M.FPCW,
                    help="x87 control word both sides run under (hex; default %04X = 24-bit D3D device-thread state, "
                         "027F = CRT 53-bit state of worker threads)" % M.FPCW)
    ap.add_argument("--uninit-mem", dest="uninit_mem", action="store_true", default=True,
                    help="(default ON) drop from the memory comparison a dword that NEITHER build wrote "
                         "during the run when the original's value is one of MSVC's fill/sentinel leftovers "
                         "(0xCCCCCCCC, 0xCDCDCDCD, ... and their partial-copy variants) - an uninitialised "
                         "frame slot or a pool page one side materialised and the other never touched. A dword "
                         "our build wrote is never excused, and the count is reported ('uninit: N dword(s)')")
    ap.add_argument("--no-uninit-mem", dest="uninit_mem", action="store_false",
                    help="compare every dword, including fill/sentinel leftovers neither build wrote (the "
                         "pre-2026-10-27 behaviour: 6 rows of unrelated FAILs)")
    ap.add_argument("--fp-tol", action="store_true",
                    help="judge float-only mismatches against the original re-run at 64-bit precision (0x037F): "
                         "rounding-only differences give PASS-FP / WEAK-FP, Inf/NaN/>1e30 cases are counted as out-of-range")
    ap.add_argument("--fp-realistic", action="store_true",
                    help="generate float fields as finite magnitudes in [1e-3, 1e5] (both signs, plus 0/+-1) instead of random bit patterns")
    ap.add_argument("--no-invariants", action="store_true",
                    help="disable the input-object invariants (invariants.py): feed the raw pointer soup to every row, "
                         "including the rows that read a length field out of it and index an array whose capacity the "
                         "type declares (face::count over v[4], GFace::n over idx[4], Terrain::w/h over cell[251][251]). "
                         "With the invariants on those inputs are moved into range or discarded as 'invalid-object'")
    ap.add_argument("--pin", action="append", metavar="this+OFF[&MASK]=V1,V2,...",
                    help="hold an input field to a set of values (hex), e.g. a switch selector so one case of a dispatch "
                         "runs per invocation: this+0&0fffffff=3b. Inputs that cannot carry it are discarded as "
                         "invalid-object. Repeatable")
    ap.add_argument("--hint", action="append", metavar="this+OFF[&MASK]=V1,V2,...@P",
                    help="soft pin: in a share P (default 0.5) of fresh inputs set the field to one of the values "
                         "(hex); nothing is discarded. Repeatable")
    ap.add_argument("--edge-scope", metavar="FILE",
                    help="JSON list of the original's edges ('0049fafc->004ac670') the run is about: it continues past "
                         "--inputs and steers only while one of them is uncovered (a pinned switch case)")
    ap.add_argument("--no-regress", action="store_true",
                    help="do not run (or record) the row's regression inputs (work/difftest/regress: every input "
                         "that ever made the row mismatch, run first)")
    ap.add_argument("--full-edges", action="store_true",
                    help="JSON: every missed edge (not the first 64) and the covered edges of each side")
    ap.add_argument("--alias", type=float, default=0.0, help="probability that a generated pointer aliases an argument object")
    ap.add_argument("--fixed-fakes", action="store_true",
                    help="fake-call results depend only on the call (pre-2026-10-23 behaviour), not on the input")
    ap.add_argument("--layout", type=float, default=0.5,
                    help="share of fresh inputs whose `this` is built from the dev-PDB class layout (0 = off)")
    ap.add_argument("--mutate", type=float, default=0.6, help="share of inputs mutated from the coverage corpus")
    ap.add_argument("--no-steer", dest="steer", action="store_false",
                    help="no input steering (comparison constants, input-to-state replays, frontier-weighted parents)")
    ap.add_argument("--steer-share", type=float, default=0.35, help="share of inputs taken from the steering queue")
    ap.add_argument("--extra-inputs", type=int, default=DEFAULT_INPUTS,
                    help="inputs beyond --inputs, spent only on steering while an edge is still uncovered")
    ap.add_argument("--no-extra-map", action="store_true",
                    help="fault repair never maps input memory at an untraceable faulting address")
    ap.add_argument("--no-early", dest="early", action="store_false",
                    help="always run --inputs (no early stop once the PASS bar is met, or when nothing is valid)")
    ap.add_argument("--early-margin", type=int, default=50,
                    help="inputs still run after the PASS bar is met (no mismatch, --min-valid valid, every edge)")
    ap.add_argument("--early-invalid", type=int, default=150,
                    help="stop a row when this many inputs ran and none was valid")
    ap.add_argument("-v", "--verbose", action="store_true")
    ap.add_argument("--replay", help="re-run one saved failing input (first_mismatch.input_file) and print details")
    o = ap.parse_args(argv)
    if o.call_regs_strict:
        o.call_regs = True          # strict compares the same capture; capture is what costs the run
    return o


def main(argv=None):
    opts = parse_args(argv)
    context()["m"].set_fpcw(int(opts.fpcw, 16))
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
        try:
            r = test_function(sid, va, opts)
        except Exception as e:      # noqa: BLE001
            # an emulator error escaping a hook (unicorn UcError in fake_call, mig10 SPCheatManager 0x67ec70) killed the
            # whole multi-VA run; the row is UNSUPPORTED and the shared machine is rebuilt for the next VA
            r = {"slice": sid, "va": "%08x" % va, "verdict": "UNSUPPORTED",
                 "reason": "harness error: %s: %s" % (type(e).__name__, str(e)[:160])}
            ctx = context()
            ctx["m"] = machine_hooks(M.Machine(ctx["img"]))
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
        if r.get("edges"):
            print("    edges: %s" % "; ".join(edge_summary(nm, r["edges"][nm]) for nm in ("orig", "ours")))
            for nm in ("orig", "ours"):
                e = r["edges"][nm]
                if e["missed_n"]:
                    print("      %s missed: %s%s" % (nm, " ".join(e["missed"][:8]), " ..." if e["missed_n"] > 8 else ""))
                groups = {}
                for u in e["unreachable"]:
                    groups.setdefault(u["reason"], []).append(u["edge"])
                for why, es in groups.items():
                    print("      %s unreachable (%d): %s [%s%s]" % (nm, len(es), why, " ".join(es[:4]), " ..." if len(es) > 4 else ""))
        if r.get("fp_tol"):
            print("    fp-tol: %s" % r["fp_tol"])
        tol = {k: v for k, v in r["tolerated"].items() if v}
        if tol:
            print("    tolerated: %s" % tol)
    fm = r.get("first_mismatch")
    if fm:
        print("    first mismatch (input %d, %s, %s): %s\n      orig: %s\n      ours: %s\n      %s" % (
            fm["input"], fm["profile"], fm.get("kind", "?"), fm["observable"], fm["orig"], fm["ours"], fm["detail"]))
        if fm.get("input_file"):
            print("    replay: .venv/bin/python tools/difftest/equiv.py %s %s --replay %s -v" % (
                r.get("slice", "?"), r.get("va", "?"), fm["input_file"]))
    if r.get("resolution_conflicts"):
        print("    resolution conflicts: %s" % r["resolution_conflicts"][:3])


if __name__ == "__main__":
    sys.exit(main())
