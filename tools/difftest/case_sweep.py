#!/usr/bin/env python3
"""case_sweep.py: run the equivalence harness over a switch function one case at a time; resumable.

usage: case_sweep.py <src.cpp> <va-hex> --selector 'this+OFF&MASK' [--jobs 8] [--inputs 100] [--min-valid 50]
                     [--time-limit 150] [--only OPCODES] [--redo VERDICT,...] [--names opcodes.json] [--out f.json]
                     [--status] [--nice 10]

equiv.py on a whole switch function never gets past the dispatch: the selector is soup, and a jump table entry is not a
comparison steering can solve. This driver runs equiv.py once per case with `--pin <selector>=<the case's selector
values>` (its table indices plus the dispatch bias), so every run enters that case and the operands stay random.

Per case it records equiv's numbers (valid inputs, mismatches, the first mismatch) and the case's own edge coverage:
the original's edges reachable from the case's table target without passing the dispatch again (shared tails
included), minus the edges equiv reports statically unreachable. Case verdicts:
  FAIL       a mismatch on some input (equiv's comparison: calls and arguments, memory writes, registers, result);
  PASS       no mismatch, >= --min-valid valid inputs, every required edge of the case covered;
  WEAK       no mismatch, too few valid inputs or missed case edges (both counts are recorded);
  UNREACHED  no run reached the case's table edge (the pin did not take);
  ERROR      equiv.py produced no result (its output tail is recorded).
The shared exit (the most common jmp target of the original: result flags, *error, epilogue) is not required per
case, since a case that always returns true can never take its "false" edges; --status reports its coverage
across the whole sweep. Coverage is judged on the original's side only; ours is recorded (covered edge count) but not required.

Resumable: results go to --out (default work/difftest/cases/<module>_<va>.json), rewritten atomically after every
case. A case is skipped when its stored key matches (--accept-older-harness: its code_key, the same without the harness
sources): the harness sources (tools/difftest/*.py), the options, our
prologue up to the dispatch, and our case's own code (its region of our function, normalised for position, plus the
code of every function of our object it calls). An edit to one case of the source re-runs that case (and any case
sharing the edited code), not all of them. Killing the sweep (SIGTERM/SIGINT/SIGHUP) kills its equiv.py runs too and
loses only the cases in flight (a SIGKILL of the driver leaves them running: kill its process group instead); equiv.py's own result
cache (work/difftest/equiv_cache) also survives. Runs are niced (--nice, default 10) so other work keeps priority, and
equiv.py's machine-wide CPU slots (DIFFTEST_MAX_PROCS) still apply. --status prints the summary of --out and exits.

The functions the source defines with a `// @ 0x<va>` marker (other than the tested one) are passed as --transparent:
our object runs its own copies of them, so the original's call to one is replaced by the calls it makes.
"""
import argparse, datetime, fcntl, glob, hashlib, json, os, re, signal, struct, subprocess, sys, tempfile, threading, time
from concurrent.futures import ThreadPoolExecutor, as_completed

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(ROOT, "tools", "matching"))
from capstone import x86_const as X                 # noqa: E402
import slice as S                                   # noqa: E402
import resolve as R                                 # noqa: E402
from coff import Coff                               # noqa: E402
from cfgcov import MAX_TABLE                        # noqa: E402
import insn_exact as IE                             # noqa: E402

EQUIV = os.path.join(HERE, "equiv.py")
REL_REL32 = 0x14
TERM = ("ret", "retf", "int3", "hlt", "ud2")


def harness_hash():
    h = hashlib.sha1()
    for f in sorted(glob.glob(os.path.join(HERE, "*.py"))):
        h.update(open(f, "rb").read())
    return h.hexdigest()


# ---------------------------------------------------------------- regions

def is_jcc(i):
    return i.group(X.X86_GRP_JUMP) and i.mnemonic not in ("jmp", "ljmp") and i.operands[0].type == X.X86_OP_IMM


def region(insns, start, stop, table_of):
    """Addresses reachable from start (fall-through, jcc both ways, direct jmp, nested jump tables), never through
    the dispatch `stop`. insns: {addr: insn}. table_of(insn) -> [targets] of an indirect table jmp."""
    seen, work = set(), [start]
    while work:
        a = work.pop()
        if a in seen or a not in insns or a == stop:
            continue
        seen.add(a)
        i = insns[a]
        nxt = a + i.size
        if i.mnemonic in TERM:
            continue
        if i.mnemonic == "jmp":
            op = i.operands[0]
            if op.type == X.X86_OP_IMM:
                work.append(op.imm & 0xFFFFFFFF)
            elif op.type == X.X86_OP_MEM and op.mem.index and op.mem.scale == 4:
                work.extend(table_of(i))
            continue
        if is_jcc(i):
            work.append(i.operands[0].imm & 0xFFFFFFFF)
        work.append(nxt)
    return seen


def region_edges(insns, reg, table_of):
    """The harness's edge model (cfgcov.Cfg) restricted to a region: jcc taken/fall, one edge per table target."""
    out = set()
    for a in reg:
        i = insns[a]
        if is_jcc(i):
            out.add((a, i.operands[0].imm & 0xFFFFFFFF))
            out.add((a, a + i.size))
        elif i.mnemonic == "jmp" and i.operands[0].type == X.X86_OP_MEM and i.operands[0].mem.index:
            for t in table_of(i):
                out.add((a, t))
    return out


# ---------------------------------------------------------------- the two sides

class Plan:
    """Both builds' switch: selector values per case, the original's required edges, our case code hashes."""

    def __init__(self, src, va, flags):
        obj, log = S.compile_obj(src, flags)
        if not obj:
            sys.exit("compile failed: " + (log or "")[-600:])
        self.coff = coff = Coff(obj)
        img = R.Image()
        lo, hi = img.func_extent(va)
        sym, _how = S.find_symbol(coff, os.path.basename(src).rsplit(".", 1)[0], va, src, hi - lo)
        if isinstance(sym, list):
            sym = sym[0]
        sym = sym or IE.marker_symbol(coff, src, va)
        if sym is None:
            sys.exit("%08x: our symbol not found" % va)
        fs = coff.by_name[sym]
        sec, ulo, uhi = coff.func_extent(fs)
        self.sec, self.secno = sec, fs.secno
        oi = IE.disasm(img.read(lo, hi - lo), lo)
        end = IE.code_end(oi, lo, hi)
        oi = [i for i in oi if i.address < end]
        ui = IE.disasm(bytes(sec.data[ulo:uhi]), ulo)
        ko, bias_o, last_o = IE.dispatch(oi)
        ku, bias_u, last_u = IE.dispatch(ui)
        if ko is None or ku is None:
            sys.exit("%08x: no switch dispatch found" % va)
        if (bias_o, last_o) != (bias_u, last_u):
            sys.exit("%08x: dispatch differs: bias/last %s vs %s" % (va, (bias_o, last_o), (bias_u, last_u)))
        self.bias = IE.bias_inv(bias_o)
        d = open(obj, "rb").read()
        symptr = struct.unpack_from("<I", d, 8)[0]
        relocs = {off: (si, typ) for off, si, typ in sec.relocs}
        self.relocs = relocs

        def sym_value(si):
            return struct.unpack_from("<I", d, symptr + 18 * si + 8)[0]

        def our_table(i):
            roff = i.address + i.disp_offset
            if roff not in relocs:
                return []
            si, _t = relocs[roff]
            tsec = struct.unpack_from("<h", d, symptr + 18 * si + 12)[0] - 1
            tval = sym_value(si) + struct.unpack_from("<I", sec.data, roff)[0]
            tdata = coff.sections[tsec].data
            trel = {off: si2 for off, si2, _t in coff.sections[tsec].relocs}
            out = []
            for k in range(MAX_TABLE):
                o = tval + 4 * k
                if o not in trel or o + 4 > len(tdata):
                    break
                out.append(sym_value(trel[o]) + struct.unpack_from("<I", tdata, o)[0])
            return out

        def orig_table(i):
            t, out = i.operands[0].mem.disp & 0xFFFFFFFF, []
            for k in range(MAX_TABLE):
                v = img.u32(t + 4 * k) if lo <= t + 4 * k < hi else None
                if v is None or not lo <= v < hi:
                    break
                out.append(v)
            return out

        self.oi = {i.address: i for i in oi}
        self.ui = {i.address: i for i in ui}
        jo, ju = oi[ko], ui[ku]
        tab_o = orig_table(jo)[:last_o + 1]
        tab_u = our_table(ju)[:last_u + 1]
        self.dispatch_o = jo.address
        self.default_o = None
        for j in oi[max(0, ko - 3):ko]:
            if j.mnemonic == "ja":
                self.default_o = j.operands[0].imm & 0xFFFFFFFF
        cache_o, cache_u = {}, {}

        def tab_o_of(i):
            return cache_o.setdefault(i.address, sorted(set(orig_table(i))))

        def tab_u_of(i):
            return cache_u.setdefault(i.address, sorted(set(our_table(i))))

        # our local functions (calls into this object): their code joins the hash of every case that calls them
        self.local_code = {}
        self.pro_hash = self.code_hash(region(self.ui, ui[0].address, ju.address, tab_u_of), ulo)
        # the shared exit (the most common jmp target: result flags, *error, epilogue) is judged across the
        # sweep, not per case: a case that always returns true can never take its "false" edges
        from collections import Counter
        jm = Counter(i.operands[0].imm & 0xFFFFFFFF for i in oi if i.mnemonic == "jmp" and i.operands
                     and i.operands[0].type == X.X86_OP_IMM)
        self.exit_o = jm.most_common(1)[0][0] if jm else None
        tail = region_edges(self.oi, region(self.oi, self.exit_o, jo.address, tab_o_of), tab_o_of) \
            if self.exit_o is not None else set()
        groups = {}
        for k, t in enumerate(tab_o):
            if t != self.default_o:
                groups.setdefault(t, []).append(k)
        self.cases = []
        for t, ks in sorted(groups.items(), key=lambda kv: kv[1][0]):
            tu = {tab_u[k] for k in ks if k < len(tab_u)}
            reg_o = region(self.oi, t, jo.address, tab_o_of)
            edges = region_edges(self.oi, reg_o, tab_o_of)
            req = (edges - tail) | {(jo.address, t)}
            reg_u = set()
            for x in tu:
                reg_u |= region(self.ui, x, ju.address, tab_u_of)
            self.cases.append({"indices": ks, "values": [k + self.bias for k in ks], "orig_target": t,
                               "ours_targets": sorted(tu), "orig_insns": len(reg_o), "ours_insns": len(reg_u),
                               "required": sorted(req), "tail": sorted(edges & tail), "hash": self.code_hash(reg_u, ulo)})

    def code_hash(self, addrs, base):
        """Position-independent hash of our instructions at addrs: branch targets as their rank in the region,
        relocated fields by symbol name, plus the code of every local function called."""
        order = sorted(addrs)
        rank = {a: n for n, a in enumerate(order)}
        h = hashlib.sha1()
        for a in order:
            i = self.ui[a]
            names = []
            for off in range(i.size):
                r = self.relocs.get(a + off)
                if r:
                    nm = self.coff.syms[r[0]].name if r[0] in self.coff.syms else str(r[0])
                    names.append(nm)
                    if r[1] == REL_REL32:
                        h.update(self.local_hash(r[0]).encode())
            if (i.mnemonic == "jmp" or is_jcc(i)) and i.operands[0].type == X.X86_OP_IMM and not names:
                t = i.operands[0].imm & 0xFFFFFFFF
                h.update(("%s L%s|" % (i.mnemonic, rank.get(t, "out%x" % (t - base)))).encode())
            elif i.mnemonic == "call" and names:
                h.update(("call %s|" % names).encode())
            else:
                h.update(bytes(i.bytes) + repr(names).encode() + b"|")
        return h.hexdigest()

    def local_hash(self, si, depth=0):
        """Hash of a called symbol's code when our object defines it (its section bytes and relocation names)."""
        s = self.coff.syms.get(si)
        if s is None or not s.defined or s.secno <= 0 or s.secno == self.secno or depth > 8:
            return ""
        if si in self.local_code:
            return self.local_code[si]
        self.local_code[si] = "(recursive)"
        sec = self.coff.sections[s.secno - 1]
        h = hashlib.sha1(bytes(sec.data))
        for off, si2, typ in sec.relocs:
            nm = self.coff.syms[si2].name if si2 in self.coff.syms else str(si2)
            h.update(("%x %s %d|" % (off, nm, typ)).encode())
            if typ == REL_REL32:
                h.update(self.local_hash(si2, depth + 1).encode())
        self.local_code[si] = h.hexdigest()
        return self.local_code[si]


# ---------------------------------------------------------------- running

def fmt_edge(e):
    return "%08x->%08x" % e


def judge(case, r, min_valid):
    """Case verdict and coverage from one equiv.py JSON row."""
    cov = set(r.get("edges", {}).get("orig", {}).get("covered_edges", []))
    unr = {u["edge"] for u in r.get("edges", {}).get("orig", {}).get("unreachable", [])}
    req = [fmt_edge(tuple(e)) for e in case["required"]]
    need = [e for e in req if e not in unr]
    missed = [e for e in need if e not in cov]
    valid, mism = r.get("valid", 0), r.get("mismatches", 0)
    entry = fmt_edge((case["dispatch"], case["orig_target"]))
    if mism:
        v = "FAIL"
    elif entry not in cov:
        v = "UNREACHED"
    elif valid >= min_valid and not missed:
        v = "PASS"
    else:
        v = "WEAK"
    tail = [fmt_edge(tuple(e)) for e in case["tail"]]
    return {"verdict": v, "valid": valid, "inputs": r.get("inputs", 0), "mismatches": mism,
            "discarded": r.get("discarded", {}), "edges_required": len(need), "edges_covered": len(need) - len(missed),
            "edges_unreachable": len(req) - len(need), "missed": missed[:24],
            "tail_covered": sorted(e for e in tail if e in cov), "tail_edges": len(tail),
            "ours_edges_covered": r.get("edges", {}).get("ours", {}).get("covered", 0),
            "equiv_verdict": r.get("verdict"), "first_mismatch": r.get("first_mismatch"),
            "reason": (r.get("reason") or "")[:600]}


CHILDREN = set()                # running equiv.py processes: killed with the sweep (see stop())
CHILDREN_LOCK = threading.Lock()
STOPPING = threading.Event()


def stop(signum, _frame):
    """SIGTERM/SIGINT/SIGHUP: kill the equiv.py runs in flight (they would run on as orphans) and exit; the
    results file already holds every finished case."""
    STOPPING.set()
    with CHILDREN_LOCK:
        for p in list(CHILDREN):
            try:
                os.killpg(p.pid, signal.SIGKILL)
            except OSError:
                pass
    os._exit(128 + signum)


def code_key(opt_key, pro_hash, case_hash):
    """The case's key without the harness: the options, our prologue and our case code. A result whose code_key
    matches was measured on the code as it is now, whatever harness version ran it (see --accept-older-harness)."""
    return hashlib.sha1(("code:" + opt_key + pro_hash + case_hash).encode()).hexdigest()


def current(r, c, accept_older_harness):
    """Is stored result r valid for case c? Same full key, or (--accept-older-harness) the same code_key."""
    if r.get("key") == c["key"]:
        return True
    return bool(accept_older_harness and r.get("code_key") and r.get("code_key") == c["code_key"])


def run_case(a, case, key, transparent, slice_id):
    fd, js = tempfile.mkstemp(suffix=".json", prefix="case_sweep_")
    os.close(fd)
    pin = "%s=%s" % (a.selector, ",".join("%x" % v for v in case["values"]))
    cmd = [sys.executable, EQUIV, slice_id, "%x" % a.va, "--src", a.src, "--flags", " ".join(a.flag_list),
           "--pin", pin, "--full-edges", "--inputs", str(a.inputs), "--min-valid", str(a.min_valid),
           "--time-limit", str(a.time_limit), "--json", js]
    if transparent:
        cmd += ["--transparent", ",".join("%x" % v for v in transparent)]
    for x in a.pin or ():
        cmd += ["--pin", x]
    for x in a.hint or ():
        cmd += ["--hint", x]
    # the case's own edges: equiv stops steering (and stops) once these are covered
    sfd, scope = tempfile.mkstemp(suffix=".json", prefix="case_scope_")
    with os.fdopen(sfd, "w") as fh:
        json.dump([fmt_edge(tuple(e)) for e in case["required"]], fh)
    cmd += ["--edge-scope", scope]
    t0 = time.time()

    def child_setup():
        os.setsid()                 # its own process group: stop() kills equiv.py and anything it started
        if a.nice:
            os.nice(a.nice)
    try:
        if STOPPING.is_set():
            raise RuntimeError("stopping")
        p = subprocess.Popen(cmd, cwd=ROOT, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True,
                             preexec_fn=child_setup)
        with CHILDREN_LOCK:
            CHILDREN.add(p)
        try:
            stdout, _ = p.communicate(timeout=a.time_limit * 3 + 300)
        except subprocess.TimeoutExpired:
            os.killpg(p.pid, signal.SIGKILL)
            p.communicate()
            raise
        finally:
            with CHILDREN_LOCK:
                CHILDREN.discard(p)
        p.stdout_text = stdout or ""
        rows = json.load(open(js)) if os.path.getsize(js) else []
        row = rows[0] if isinstance(rows, list) and rows else (rows if isinstance(rows, dict) else None)
        if not row:
            tail = p.stdout_text.strip().splitlines()[-3:]
            res = {"verdict": "ERROR", "reason": " | ".join(tail)[:600]}
        else:
            res = judge(case, row, a.min_valid)
    except subprocess.TimeoutExpired:
        res = {"verdict": "ERROR", "reason": "driver timeout"}
    finally:
        for f_ in (js, scope):
            try:
                os.remove(f_)
            except OSError:
                pass
    res.update(key=key, seconds=round(time.time() - t0, 1), pin=pin,
               when=datetime.datetime.now().astimezone().isoformat(timespec="seconds"))
    return res


def summary(results, total=None):
    from collections import Counter
    c = Counter(r.get("verdict") for r in results.values() if not r.get("stale"))
    s = ", ".join("%s %d" % kv for kv in sorted(c.items()))
    n_stale = sum(1 for r in results.values() if r.get("stale"))
    if n_stale:
        s += "; %d stale (an older build/harness, not yet re-run)" % n_stale
    if total is not None:
        s += "  (%d/%d cases recorded)" % (len(results), total)
    return s


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("va")
    ap.add_argument("--selector", help="the dispatch selector as an equiv.py --pin field: this+OFF&MASK")
    ap.add_argument("--pin", action="append", help="further equiv.py --pin fields for every case (repeatable): e.g. the "
                    "operand count and the operands' tag dwords, so the cases see realistic operands")
    ap.add_argument("--hint", action="append", help="equiv.py --hint soft pins for every case (repeatable)")
    ap.add_argument("--operand-hints", action="store_true",
                    help="Module System operands, softly: in half the fresh inputs each operand's high dword "
                         "this+0x14+8k is 0 or -1 (a plain constant), so 64-bit operand compares can be equal in "
                         "their high halves; the rest stays soup")
    ap.add_argument("--operands", action="store_true",
                    help="Module System operand record (Elem): count this+8 = 16, each operand's high dword "
                         "this+0x14+8k 0 or -1 (plain constants: a register/variable tag with a soup index only reaches get_operand's error report); the low dwords stay soup")
    ap.add_argument("--flags")
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--inputs", type=int, default=100)
    ap.add_argument("--min-valid", type=int, default=50)
    ap.add_argument("--time-limit", type=int, default=150, help="seconds per case (equiv.py --time-limit)")
    ap.add_argument("--only", help="comma-separated selector values (decimal) or case names: run just these cases")
    ap.add_argument("--redo", default="ERROR", help="re-run stored cases with these verdicts even if the key matches")
    ap.add_argument("--names", default=os.path.join(ROOT, "work", "match", "scratch_si_tools", "jt_names.json"),
                    help="json {selector value: name or [names]} for case labels")
    ap.add_argument("--accept-older-harness", action="store_true",
                    help="keep a stored result whose case code is unchanged even if the harness changed since it ran "
                         "(it is marked older_harness and counted apart in --status); re-run such cases with --only")
    ap.add_argument("--nice", type=int, default=10)
    ap.add_argument("--out")
    ap.add_argument("--status", action="store_true")
    a = ap.parse_args()
    a.va = int(a.va, 16)
    if a.operand_hints:
        a.hint = (a.hint or []) + ["this+%x=0,ffffffff@0.5" % (0x14 + 8 * k) for k in range(16)]
    if a.operands:
        a.pin = (a.pin or []) + ["this+8=10"] + ["this+%x=0,ffffffff" % (0x14 + 8 * k)
                                                 for k in range(16)]
    os.chdir(ROOT)
    a.src = os.path.relpath(os.path.abspath(a.src), ROOT)
    slice_id = os.path.basename(a.src).rsplit(".", 1)[0]
    out = a.out or os.path.join(ROOT, "work", "difftest", "cases", "%s_%08x.json" % (slice_id, a.va))
    os.makedirs(os.path.dirname(out), exist_ok=True)
    old = json.load(open(out)) if os.path.exists(out) else {}
    if a.status:
        res = old.get("cases", {})
        print(out)
        print(summary(res, old.get("total")))
        res = {k: v for k, v in res.items() if not v.get("stale")}
        n_old = sum(1 for v in res.values() if v.get("older_harness"))
        if n_old:
            print("%d of these were measured by an older harness on the same code (--accept-older-harness)" % n_old)
        tc = set()
        for r in res.values():
            tc.update(r.get("tail_covered", []))
        print("shared exit edges covered across the sweep: %d/%s" % (len(tc), old.get("tail_total", "?")))
        for nm, r in sorted(res.items(), key=lambda kv: kv[1].get("verdict", "")):
            if r.get("verdict") not in ("PASS",) and not r.get("stale"):
                print("  %-9s %-45s valid %3s  edges %s/%s  %s" % (r.get("verdict"), nm, r.get("valid"),
                      r.get("edges_covered"), r.get("edges_required"),
                      (r.get("first_mismatch") or {}).get("observable", "") if r.get("verdict") == "FAIL" else ""))
        return
    if not a.selector:
        sys.exit("--selector is required (e.g. 'this+0&0fffffff')")
    for sig in (signal.SIGTERM, signal.SIGINT, signal.SIGHUP):
        signal.signal(sig, stop)
    lock = open(out + ".lock", "w")
    try:
        fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
    except OSError:
        sys.exit("another case_sweep is writing %s" % out)
    flags = a.flags.split() if a.flags else list(S.DEFAULT_FLAGS)
    if a.src.replace(os.sep, "/").startswith("src/game/") and "/Isrc/game/include" not in flags:
        flags.append("/Isrc/game/include")
    a.flag_list = flags
    names = {}
    if a.names and os.path.exists(a.names):
        for k, v in json.load(open(a.names)).items():
            names[int(k)] = v[0] if isinstance(v, list) else v
    print("planning (compile, both jump tables, case regions) ...", flush=True)
    plan = Plan(a.src, a.va, flags)
    text = open(a.src, encoding="utf-8", errors="replace").read()
    transparent = sorted({int(x, 16) for x in re.findall(r"^// @ 0x([0-9a-fA-F]+)", text, re.M)} - {a.va})
    hh = harness_hash()
    opt_key = json.dumps([a.selector, flags, a.inputs, a.min_valid, a.time_limit, transparent, a.pin or []]
                         + ([a.hint] if a.hint else []))
    cases = {}
    for c in plan.cases:
        c["dispatch"] = plan.dispatch_o
        nm = "%d %s" % (c["values"][0], names.get(c["values"][0], "?"))
        c["key"] = hashlib.sha1((hh + opt_key + plan.pro_hash + c["hash"]).encode()).hexdigest()
        c["code_key"] = code_key(opt_key, plan.pro_hash, c["hash"])
        cases[nm] = c
    results = dict(old.get("cases", {}))
    redo = set(v for v in a.redo.split(",") if v)
    only = set(x.strip() for x in a.only.split(",")) if a.only else None
    todo = []
    for nm, c in cases.items():
        if only and not (str(c["values"][0]) in only or nm.split(" ", 1)[1] in only):
            continue
        r = results.get(nm)
        if r and current(r, c, a.accept_older_harness) and r.get("verdict") not in redo:
            continue
        todo.append(nm)
    for nm in list(results):           # a case the current build no longer has
        if nm not in cases:
            del results[nm]
        elif not current(results[nm], cases[nm], a.accept_older_harness):
            results[nm]["stale"] = True    # from an older build/harness/options: shown apart until re-run
        else:
            results[nm].pop("stale", None)
            results[nm]["older_harness"] = results[nm].get("key") != cases[nm]["key"]
    print("%d cases, %d selected, %d to run, %d jobs, nice %d -> %s" % (
        len(cases), len(cases) if not only else sum(1 for nm, c in cases.items() if str(c["values"][0]) in only
                                                    or nm.split(" ", 1)[1] in only),
        len(todo), a.jobs, a.nice, out), flush=True)
    wlock = threading.Lock()

    def save():
        doc = {"src": a.src, "va": "%08x" % a.va, "selector": a.selector, "total": len(cases), "exit": "%08x" % plan.exit_o,
               "tail_total": len({e for c in cases.values() for e in c["tail"]}) or None, "when": datetime.datetime.now().astimezone().isoformat(timespec="seconds"),
               "summary": summary(results), "cases": dict(sorted(results.items(), key=lambda kv: int(kv[0].split()[0])))}
        tmp = out + ".part"
        json.dump(doc, open(tmp, "w"), indent=1)
        os.replace(tmp, out)

    save()
    n = 0
    # the biggest cases first: they take longest, so the pool finishes evenly
    todo.sort(key=lambda nm: -cases[nm]["orig_insns"])
    with ThreadPoolExecutor(a.jobs) as ex:
        futs = {ex.submit(run_case, a, cases[nm], cases[nm]["key"], transparent, slice_id): nm for nm in todo}
        for f in as_completed(futs):
            nm = futs[f]
            try:
                r = f.result()
            except Exception as e:      # noqa: BLE001 - one broken case must not stop the sweep
                r = {"verdict": "ERROR", "reason": repr(e)[:600], "key": cases[nm]["key"]}
            r.update(code_key=cases[nm]["code_key"], older_harness=False)
            r.update(orig_target="%08x" % cases[nm]["orig_target"], values=cases[nm]["values"],
                     orig_insns=cases[nm]["orig_insns"], ours_insns=cases[nm]["ours_insns"])
            n += 1
            with wlock:
                results[nm] = r
                save()
            print("[%d/%d] %-9s %-42s valid %3s mism %s edges %s/%s %5.0fs" % (
                n, len(todo), r["verdict"], nm, r.get("valid"), r.get("mismatches"), r.get("edges_covered"),
                r.get("edges_required"), r.get("seconds", 0)), flush=True)
    print("done:", summary(results, len(cases)))


if __name__ == "__main__":
    main()
