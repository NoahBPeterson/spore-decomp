#!/usr/bin/env python3
"""Print Spore decompilation progress as terminal tables. Standalone: run from any shell.

  .venv/bin/python tools/progress.py            # coverage + components
  .venv/bin/python tools/progress.py --groups    # also live opencode wave groups
  .venv/bin/python tools/progress.py --plot [out.png]  # chart of progress over time (default work/progress.png;
                                                       # one point per committed docs/STATUS.md and one per day of
                                                       # --plot runs, kept in docs/progress_history.json; needs matplotlib)
                                                       # below it, one bar per module (docs/modules.md) split into byte-exact /
                                                       # equivalent / partial / no source; per-module shares go into the history too
  .venv/bin/python tools/progress.py --treemap [out.png]  # one box per dev-build object, split by verdict, area = bytes
                                                          # (default work/treemap.png)
  .venv/bin/python tools/progress.py --no-refresh # reuse docs/STATUS.md-derived cache? (still recomputes)

Coverage is computed with the exact logic of tools/status.py (reused via runpy), so numbers
match docs/STATUS.md. --groups reads work/opencode/groups/*.json + match/slices manifests, and
uses the opencode service for cost/active if it is reachable (otherwise shows "-").
"""
import base64, collections, contextlib, glob, io, json, os, re, runpy, subprocess, sys, urllib.parse, urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
W = lambda *p: os.path.join(ROOT, *p)

# Slices that Claude workflows (cl1_*, op1_*) later reworked: opencode models are credited with
# their manifest/nonmatching counts frozen at the last pre-Claude commit, not with Claude's edits.
# bfs4 was never committed before Claude resumed it, so its DeepSeek output is not recoverable
# per slice; BATCH_FROZEN pins its total to the 178 byte-exact shown before the handoff.
try:
    CLAUDE_BASELINE = json.load(open(W("work/claude/opencode_baseline.json")))["slices"]
except (OSError, ValueError, KeyError):
    CLAUDE_BASELINE = {}
BATCH_FROZEN = {"bfs4": (178, None, 625)}  # (exact, equiv unknown, accounted)
# ---- who produced each function (per-model table; tools/attribution.py credits the commit that first added a row) ----
NO_MODEL_PATTERN = "(no model) pattern templates (tools/synth generator)"
NO_MODEL_CLONES = "(no model) clones of identical functions"
NO_MODEL_UNKNOWN = "(model not recorded) Claude workflows of Oct 2-7, library imports"
NO_MODEL = {NO_MODEL_PATTERN, NO_MODEL_CLONES, NO_MODEL_UNKNOWN}
CLAUDE_KEY = {"claude-sonnet-5-5": "sonnet-5.5", "claude-opus-5-5": "opus-5.5", "claude-haiku-5-5": "haiku-5.5"}
# commit-subject tag -> opencode batches (session title "spore-<batch>-<k>") when the names differ
WAVE_BATCHES = {"DeepSeek-v4.1-flash": ["b006"], "b008/b009:": ["b008", "b009"], "gold2/gold3": ["gold2g0", "gold3g0"],
                "g4-cherry": ["gold4g0"], "Round": ["mig2"], "fix2/fix3:": ["fix2", "fix3"]}
# waves with no opencode sessions on record: the model their commit subject names
TAG_MODEL = {"cl1": "sonnet-5.5", "cl2": "sonnet-5.5", "Sonnet": "sonnet-5.5", "Tier-3": "sonnet-5.5", "Migration": "sonnet-5.5",
             "op1_big": "opus-5.5", "op2_big": "opus-5.5", "op3": "opus-5.5", "fix1": "opus-5.5", "unsup1": "opus-5.5",
             "unsup1b": "opus-5.5", "Fix": "opus-5.5", "hk1": "haiku-5.5", "hk2": "haiku-5.5",
             "b007": "cheaperinference/glm-5.3-flash"}
for _t in ("gold0", "gold1", "gold2", "gold3", "gold4", "gold5", "gold6", "gold7", "part1", "fix24", "dec1", "dec2", "spcg1",
           "bfs0", "bfs1", "bfs2", "bfs3", "w4g2", "rck1", "rck2", "rw0", "fix0", "fix2", "fix3"):
    TAG_MODEL.setdefault(_t, "cheaperinference/deepseek-v4.1-flash")   # opencode waves whose sessions are gone
for _w in ("w1g", "w2g", "w3g"):
    for _k in range(8):
        TAG_MODEL.setdefault("%s%d" % (_w, _k), "cheaperinference/deepseek-v4.1-flash")
for _k in range(7, 19):
    TAG_MODEL.setdefault("mig%d" % _k, "sonnet-5.5")      # module landings mig7-mig18: Sonnet subagents (work/claude/mig*_prompts)
for _k in range(19, 30):
    TAG_MODEL.setdefault("mig%d" % _k, "cheaperinference/deepseek-v4.1-flash")      # mig19 on: opencode sessions
try:   # slices written by Claude subagents (scan of the surviving transcripts: work/claude/agent_slice_models.json)
    AGENT_SLICES = json.load(open(W("work/claude/agent_slice_models.json")))
except (OSError, ValueError):
    AGENT_SLICES = {}
sys.path.insert(0, W("tools"))
_slice_batches = collections.defaultdict(set)
for _bf in glob.glob(os.path.join(ROOT, "work/batches", "*.json")):
    _bn = os.path.basename(_bf)[:-5]
    try:
        _recs = json.load(open(_bf))
    except (OSError, ValueError):
        continue  # a batch file being (re)written by another process; skip it
    for _rec in _recs if isinstance(_recs, list) else []:
        # Tolerate other batch shapes: {"id": ...}, {"slice": ...} or a bare slice-id string.
        _sid = _rec if isinstance(_rec, str) else (_rec.get("id") or _rec.get("slice")) if isinstance(_rec, dict) else None
        if _sid:
            _slice_batches[_sid].add(_bn)

def table(headers, rows, aligns=None):
    cols = len(headers)
    aligns = aligns or ["<"] * cols
    data = [[str(c) for c in r] for r in rows]
    w = [len(headers[i]) for i in range(cols)]
    for r in data:
        for i, c in enumerate(r):
            w[i] = max(w[i], len(c))

    def fmt(cells):
        return "  ".join(cells[i].rjust(w[i]) if aligns[i] == ">" else cells[i].ljust(w[i])
                         for i in range(cols))

    out = [fmt(list(headers)), "  ".join("-" * w[i] for i in range(cols))]
    out += [fmt(r) for r in data]
    return "\n".join(out)

def human(n):
    return f"{n:,}"

# ---- coverage, reusing status.py's logic exactly ----
buf = io.StringIO()
with contextlib.redirect_stdout(buf):
    ns = runpy.run_path(W("tools", "status.py"))
funcs = ns["funcs"]; game = ns["game"]; G = ns["G"]; GB = ns["GB"]
byte_exact = ns["byte_exact"]; equiv = ns["equiv"]; part = ns["part"]; nosrc = ns["nosrc"]
KF, KC, KG = ns["KF"], ns["KC"], ns["KG"]
pct = ns["pct"]
migrated = ns["mig_comp"]; mig_exact = ns["mig_exact"]; mig_equiv = ns["mig_equiv"]; mig_part = ns["mig_part"]
mig_verbatim = ns["mig_verbatim"]
closed = ns["closed"]; objects = ns["objects"]; intervals = ns["intervals"]; module_of = ns["module_of"]

def mb(items):
    return sum(funcs[a]["size"] for a in items) / 2**20

exact_total = byte_exact | equiv

# ---- equivalence verdicts of the compilable-but-not-exact functions, from the latest sweep ----
# docs/equiv_verdicts.json is written by tools/difftest/verdicts.py from the merged harness's results (2026-10-29 on).
# A FAIL is a mismatch, so that function is NOT equivalent; only a PASS (every branch exercised on both builds) counts
# as shown equivalent. A function the sweep has no result for is "not tested yet".
VERDICT_CATS = (("pass", "Equivalent: test PASS (every branch ran)"),
                ("weak", "Probably equivalent: WEAK (some branch never ran)"),
                ("inputs", "Untestable: random inputs invalid"),
                ("harness", "Untestable: harness limit or symbol not found"),
                ("untested", "Not tested yet by the new harness"),
                ("fail", "NOT equivalent: test FAIL (a mismatch)"))
_VMAP = {"pass": "pass", "comdat": "pass", "weak": "weak", "fail": "fail", "comdatdiff": "fail", "inputs": "inputs",
         "harness": "harness", "funclet": "harness"}


def _load_verdicts():
    """(VA -> verdicts.py category, sweep time) from docs/equiv_verdicts.json; ({}, None) without it."""
    try:
        doc = json.load(open(W("docs", "equiv_verdicts.json")))
    except (OSError, ValueError):
        return {}, None
    return {int(va, 16): r.get("category") for va, r in doc.get("rows", {}).items()}, doc.get("when")


VERDICT_OF, VERDICT_WHEN = _load_verdicts()
equiv_by = collections.defaultdict(set)
for _a in equiv:
    equiv_by[_VMAP.get(VERDICT_OF.get(_a), "untested")].add(_a)
GB_MB = GB / 2**20
def pctb(items):
    return pct(mb(items), GB_MB)
rows = [
    ("Byte-exact: free functions",        len(byte_exact & KF), pct(len(byte_exact & KF), G), mb(byte_exact & KF), pctb(byte_exact & KF)),
    ("Byte-exact: classes/templates",     len(byte_exact & KC), pct(len(byte_exact & KC), G), mb(byte_exact & KC), pctb(byte_exact & KC)),
    ("Byte-exact: globals/other code",    len(byte_exact & KG), pct(len(byte_exact & KG), G), mb(byte_exact & KG), pctb(byte_exact & KG)),
    ("BYTE-EXACT TOTAL",                  len(byte_exact),       pct(len(byte_exact), G),       mb(byte_exact),       pctb(byte_exact)),
] + [("  " + lab, len(equiv_by[k]), pct(len(equiv_by[k]), G), mb(equiv_by[k]), pctb(equiv_by[k])) for k, lab in VERDICT_CATS] + [
    ("COMPILABLE, NOT EXACT (sum of the above)", len(equiv), pct(len(equiv), G),            mb(equiv),            pctb(equiv)),
    ("Partial (incomplete)",              len(part),             pct(len(part), G),             mb(part),             pctb(part)),
    ("No source yet",                     len(nosrc),            pct(len(nosrc), G),            mb(nosrc),            pctb(nosrc)),
    ("TOTAL WITH COMPILABLE SOURCE",      len(exact_total),      pct(len(exact_total), G),      mb(exact_total),      pctb(exact_total)),
    ("SHOWN CORRECT (byte-exact + PASS)", len(byte_exact | equiv_by["pass"]), pct(len(byte_exact | equiv_by["pass"]), G),
     mb(byte_exact | equiv_by["pass"]), pctb(byte_exact | equiv_by["pass"])),
    ("Game functions (denominator)",      G,                     "100.00%",                     GB_MB,                "100.00%"),
]
print("Spore decompilation progress")
print()
print(table(["Tier", "Functions", "% count", "MB", "% size"],
            [(a, human(b), c, "%.2f" % d, e) for a, b, c, d, e in rows],
            aligns=["<", ">", ">", ">", ">"]))
print("Verdicts: %s" % ("the equivalence sweep at %s (tools/difftest/verdicts.py -> docs/equiv_verdicts.json)" % VERDICT_WHEN
                        if VERDICT_WHEN else "none yet (run tools/difftest/verdicts.py --from <sweep dir>)"))

# ---- components ----
comp = ns["comp_rows"]()  # markdown rows: | name | funcs | exact (pct) | exact% by size | src (pct) | MB | src% |
crows = []
for line in comp:
    p = [x.strip() for x in line.strip().strip("|").split("|")]
    name, nfuncs, ex, exby, src, size, srcby = p
    crows.append((name, ex, exby, src, srcby, size))
print()
print(table(["Component", "Byte-exact", "(by size)", "With compilable source", "(by size)", "Code size"],
            crows, aligns=["<", ">", ">", ">", ">", ">"]))

# ---- migration into src/game (Phase B): per object file, denominators are retail address intervals ----
def migration_table():
    """One row per object file with a module TU. 'In interval' counts every retail game function in
    the object's address intervals (tools/migrate/intervals.py), not modmap labels; 'upper' adds the
    unassigned functions in the bounding gaps (where the object may really end). An interval is
    closed when every function in it has compilable source in a module TU."""
    print()
    print("Moving source out of match/slices into one .cpp per object file (src/game, Phase B)")
    print()
    print("  Migrated so far: %s functions with compilable source = %s of all game functions (%s by size), misfiled ones" % (
        human(len(migrated)), pct(len(migrated), G), pct(mb(migrated), GB_MB)))
    print("  included (the table's TOTAL counts only functions inside their object's ranges);")
    print("  of those, %s are verbatim slice text (compile and match, not yet on the canonical classes)." % human(len(mig_verbatim)))
    print("  Finished objects: %s functions sit in retail code ranges that are completely migrated (%s by size)." % (
        human(len(closed)), pct(mb(closed), GB_MB)))
    if not objects:
        print("  (no .cpp under src/game yet)")
        return
    if intervals is None:
        print("  (work/migrate/modmap.json missing: per-object sizes not computed)")
    print()
    rows = []
    tot = collections.Counter()
    for obj, o in sorted(objects.items()):
        all_tu = set(a for a, m in module_of.items() if m == obj) & game
        in_tu = all_tu & o["members"] if o["intervals"] else all_tu
        misfiled = len(all_tu - in_tu)          # in this .cpp but inside another object's ranges
        ex, eq, pa = len(in_tu & mig_exact), len(in_tu & mig_equiv), len(in_tu & mig_part)
        done = ex + eq
        vb = len(in_tu & mig_verbatim)
        n = o["in_interval"]
        rows.append((obj + ".cpp", human(n), "+%d" % (o["upper"] - n), human(done), "%d / %d" % (ex, eq), human(vb), human(pa),
                     human(o["holes"]), pct(done, n) if n else "-", "%d of %d" % (o["closed"], o["intervals"]),
                     human(misfiled) if misfiled else ""))
        for k in ("intervals", "in_interval", "upper", "holes", "closed"):
            tot[k] += o[k]
        tot["ex"] += ex; tot["eq"] += eq; tot["pa"] += pa; tot["vb"] += vb; tot["mf"] += misfiled
    n = tot["in_interval"]; done = tot["ex"] + tot["eq"]
    rows.append(("TOTAL", human(n), "+%d" % (tot["upper"] - n), human(done), "%d / %d" % (tot["ex"], tot["eq"]), human(tot["vb"]),
                 human(tot["pa"]), human(tot["holes"]), pct(done, n) if n else "-", "%d of %d" % (tot["closed"], tot["intervals"]),
                 human(tot["mf"]) if tot["mf"] else ""))
    print(table(["Object file", "Size (functions)", "maybe more", "Migrated", "exact / equiv", "of which verbatim", "Partial", "Remaining", "Done", "Ranges finished", "Misfiled"],
                rows, aligns=["<", ">", ">", ">", ">", ">", ">", ">", ">", ">", ">"]))
    print()
    print("  Size = retail functions in the address ranges that belong to this object (dev order is kept in retail, so an")
    print("  object is one contiguous range, or two or three when retail split it). 'maybe more' = unassigned functions next")
    print("  to those ranges that could also be the object's: its true size is between Size and Size + maybe more.")
    print("  Migrated = functions now in the .cpp with byte-exact or equivalent source; 'of which verbatim' = still the")
    print("  slice's text with renamed stubs, not on the canonical classes. Partial = in the .cpp but incomplete, not")
    print("  counted. Remaining = functions in the ranges still without compilable source in the .cpp.")
    print("  Ranges finished = address ranges with nothing remaining; a finished object is the linkable unit.")
    print("  Misfiled = functions in this .cpp whose address lies in another object's ranges (not counted above).")

migration_table()

# ---- breadth-first coverage from the program entry point ----
def bfs_table():
    """Per call-depth level from the entry point: how many reachable game functions have source."""
    bf = W("work", "bfs_rank.json")
    if not os.path.exists(bf):
        return None
    try:
        data = json.load(open(bf))
    except Exception:
        return None
    rank = {int(k, 16): d for k, d in data.get("rank", {}).items()}
    per = collections.defaultdict(lambda: [0, 0, 0, 0])  # game funcs, byte-exact, equiv, partial
    for va, d in rank.items():
        if va not in game:
            continue
        t = per[d]
        t[0] += 1
        if va in byte_exact:
            t[1] += 1
        elif va in equiv:
            t[2] += 1
        elif va in part:
            t[3] += 1
    if not per:
        return None
    maxd = max(per)
    rows = []
    done_levels = total_levels = 0
    frontier = None       # first level with reachable game code that is not fully decompiled
    deepest_any = None    # deepest level with any decompiled game code
    for d in range(maxd + 1):
        tot, ex, eq, pa = per.get(d, [0, 0, 0, 0])
        src = ex + eq
        if tot:
            total_levels += 1
            if src == tot:
                done_levels += 1
            elif frontier is None:
                frontier = d
        if src:
            deepest_any = d
        rows.append((str(d), human(tot), human(ex), human(eq), human(pa), human(tot - src),
                     ("%.0f%%" % (100.0 * src / tot)) if tot else "-"))
    head = ("BFS coverage from the entry point (%s; root %s, %d levels)"
            % (os.path.relpath(bf, ROOT), data.get("root", "?"), maxd + 1))
    body = table(["Level", "Funcs", "Byte-exact", "Equivalent", "Partial", "No source", "Source%"],
                 rows, aligns=["<", ">", ">", ">", ">", ">", ">"])
    summary = ("Levels fully decompiled: %d / %d; frontier (first level not fully decompiled): %s; "
               "deepest level with source: %s"
               % (done_levels, total_levels, frontier if frontier is not None else "-",
                  deepest_any if deepest_any is not None else "-"))
    return head + "\n" + body + "\n" + summary

_bt = bfs_table()
if _bt:
    print()
    print(_bt)

# ---- per-model efficiency (needs the opencode service for live token/cost) ----
def _svc_sessions():
    try:
        u = re.search(r"http://[0-9.:]+", subprocess.run(["opencode", "service", "status"],
                    capture_output=True, text=True, timeout=10).stdout).group(0)
        pw = json.load(open(os.path.expanduser("~/.config/opencode/service.json")))["password"]
        H = {"Authorization": "Basic " + base64.b64encode(("opencode:" + pw).encode()).decode()}
        loc = "location%5Bdirectory%5D=" + urllib.parse.quote(ROOT)
        r = urllib.request.Request(u + "/api/session?limit=500&" + loc, headers=H)
        return json.loads(urllib.request.urlopen(r, timeout=25).read()).get("data", [])
    except Exception:
        return None

# a manifest row ("slices/<id>/<id>.cpp sym va ...") or a nonmatching row ("<va> ..."), not a note line
ROW_RE = re.compile(r"^(?:slices/\S+\s+\S+\s+(?:0x)?[0-9a-fA-F]{6,8}\b|[0-9a-fA-F]{6,8}(?:\s|$))")


def _db_batch_models():
    """{(batch, "provider/model"): sums} from opencode's database, per assistant message: every session (the HTTP
    API returns at most 500, so older batches fell out of the table once the shared service held more), and each
    call billed to the model that served it (a session switched mid-wave, gold5 to OpenRouter at 06:46, kept
    only its last model at session level). The database is several GB (every message carries its tool output), so
    per-session sums are cached in work/opencode/model_usage_cache.json and only sessions whose time_updated
    changed are read again. None when the database cannot be read."""
    import sqlite3
    path = os.path.expanduser("~/.local/share/opencode/opencode.db")
    if not os.path.exists(path):
        return None
    cpath = W("work", "opencode", "model_usage_cache.json")
    try:
        cache = json.load(open(cpath))
    except (OSError, ValueError):
        cache = {}
    try:
        db = sqlite3.connect("file:%s?mode=ro" % path, uri=True, timeout=10)
        sess = db.execute("select id, title, time_updated from session_v2 where title like 'spore-%' and directory = ?",
                          (ROOT,)).fetchall()
        stale = [sid for sid, _t, upd in sess if (cache.get(sid) or {}).get("updated") != upd]
        fresh = {sid: [] for sid in stale}
        for k in range(0, len(stale), 200):
            chunk = stale[k:k + 200]
            for row in db.execute(
                    "select session_id, json_extract(data,'$.model.providerID'), json_extract(data,'$.model.id'), "
                    "sum(coalesce(json_extract(data,'$.cost'),0)), sum(coalesce(json_extract(data,'$.tokens.input'),0)), "
                    "sum(coalesce(json_extract(data,'$.tokens.cache.read'),0)), sum(coalesce(json_extract(data,'$.tokens.output'),0)), "
                    "sum(coalesce(json_extract(data,'$.tokens.reasoning'),0)), count(*) from session_message "
                    "where type = 'assistant' and session_id in (%s) group by 1, 2, 3" % ",".join("?" * len(chunk)), chunk):
                fresh[row[0]].append(list(row[1:]))
    except sqlite3.Error:
        return None
    upd = {sid: (title, u) for sid, title, u in sess}
    for sid, rows in fresh.items():
        cache[sid] = {"title": upd[sid][0], "updated": upd[sid][1], "rows": rows}
    if fresh:
        tmp = cpath + ".tmp"
        json.dump(cache, open(tmp, "w"))
        os.replace(tmp, cpath)
    # usage caches copied from other machines (work/opencode/model_usage_cache_<host>.json, e.g. the Runpod pod
    # that ran gold6..fix24 on 2026-10-23/24): their sessions are in that machine's opencode database, not this one
    for other in sorted(glob.glob(W("work", "opencode", "model_usage_cache_*.json"))):
        try:
            oc = json.load(open(other))
        except (OSError, ValueError):
            continue
        for sid, v in oc.items():
            if sid not in upd and isinstance(v, dict) and v.get("rows") is not None:
                upd[sid] = (v.get("title", ""), v.get("updated"))
                cache[sid] = v
    bm = collections.defaultdict(lambda: {"cost": 0.0, "inp": 0, "cr": 0, "out": 0, "rea": 0, "n": 0})
    for sid, (title, _u) in upd.items():
        batch = title.split("-")[1] if "-" in title else title
        for prov, mid, cost, inp, cr, out, rea, n in cache[sid]["rows"]:
            a = bm[(batch, "%s/%s" % (prov, re.sub(r"-c\d+$", "", mid or "")))]
            a["cost"] += cost; a["inp"] += inp; a["cr"] += cr; a["out"] += out; a["rea"] += rea; a["n"] += n
    return bm


def model_table():
    bm = _db_batch_models()
    if bm is None:
        bm = _api_batch_models()
        if bm is None:
            return "(opencode database and service unavailable)"
    calls = collections.Counter()
    for (batch, key), a in bm.items():
        calls[batch] += a["n"]

    return _model_rows(bm, calls)


def _api_batch_models():
    """Fallback: session-level sums from the HTTP API (at most 500 sessions; a session counts under its last model)."""
    ss = _svc_sessions()
    if ss is None:
        return None
    bm = collections.defaultdict(lambda: {"cost": 0.0, "inp": 0, "cr": 0, "out": 0, "rea": 0, "n": 0})
    for s in ss:
        t = s.get("title") or ""
        if not t.startswith("spore-"):
            continue
        batch = t.split("-")[1] if "-" in t else t
        m = s.get("model") or {}
        # cache-namespace aliases (deepseek-v4.1-flash-c06 etc.) are the same model
        key = "%s/%s" % (m.get("providerID"), re.sub(r"-c\d+$", "", m.get("id") or ""))
        tk = s.get("tokens") or {}; c = tk.get("cache") or {}
        a = bm[(batch, key)]
        a["cost"] += s.get("cost", 0) or 0; a["inp"] += tk.get("input", 0) or 0
        a["cr"] += c.get("read", 0) or 0; a["out"] += tk.get("output", 0) or 0
        a["rea"] += tk.get("reasoning", 0) or 0; a["n"] += 1
    return bm


def _model_rows(bm, calls):
    agg = collections.defaultdict(lambda: {"cost": 0.0, "inp": 0, "cr": 0, "out": 0,
                                            "rea": 0, "exact": 0, "equiv": 0, "batches": 0})
    for (batch, key), a in bm.items():
        g = agg[key]
        for k in ("cost", "inp", "cr", "out", "rea"):
            g[k] += a[k]
        g["batches"] += 1
    # Functions: every byte-exact / equivalent function counted above, credited to the wave whose commit first added
    # its row (tools/attribution.py), then to that wave's model(s) by share of model calls (2026-10-24: the old
    # per-batch manifest count credited ~13k of 61k byte-exact functions and missed the pod's waves entirely).
    import attribution as _att
    att = _att.build()
    by_batch = collections.defaultdict(lambda: collections.Counter())
    for (batch, key), a in bm.items():
        by_batch[batch][key] += a["n"]
    def shares_for(tag, slice_id):
        if tag in ("synth", "Pattern", "Tier-1", "Tier-2"):
            return {NO_MODEL_PATTERN: 1.0}
        if tag == "clones":
            return {NO_MODEL_CLONES: 1.0}
        for cand in WAVE_BATCHES.get(tag, [tag, tag + "g0"]):
            c = by_batch.get(cand)
            if c:
                tot = sum(c.values())
                return {k: n / tot for k, n in c.items()}
        if tag in TAG_MODEL:
            return {TAG_MODEL[tag]: 1.0}
        am = AGENT_SLICES.get(slice_id)
        if am:
            tot = sum(am.values())
            return {CLAUDE_KEY.get(k, k): n / tot for k, n in am.items()}
        return {NO_MODEL_UNKNOWN: 1.0}
    for kind, cur in (("exact", byte_exact), ("equiv", equiv)):
        src = att["exact" if kind == "exact" else "equiv"]
        for va in cur:
            e = src.get("%08x" % va)
            tag, sl = (e[1], e[2] if len(e) > 2 else "") if e else ("?", "")
            for key, sh in shares_for(tag, sl).items():
                agg[key][kind] += sh
    rows = []
    try:
        cr_json = json.load(open(W("work/claude/model_efficiency.json")))
    except (OSError, ValueError):
        cr_json = {}
    claude_keys = set(CLAUDE_KEY.values())
    for key, g in sorted(agg.items(), key=lambda x: -x[1]["cost"]):
        ex, eq = int(round(g["exact"])), int(round(g["equiv"])); comp = ex + eq
        if key in NO_MODEL:
            rows.append((key, "-", human(ex), human(eq), "-", "-", "-", "-", "-", "-"))
            continue
        cost, inp, cr, nb, label = g["cost"], g["inp"] + g["cr"], g["cr"], g["batches"], key
        if key in claude_keys:
            # Claude: NOMINAL API-rate cost from a cached transcript scan (subscription => $0 marginal)
            c = cr_json.get(key, {})
            cost, inp, cr, nb, label = c.get("cost", 0), c.get("inp", 0) + c.get("cr", 0), c.get("cr", 0), c.get("batches", 0), key + " (API-rate est.)"
        per = lambda d: ("$%.4f" % (cost / d)) if d and cost else "-"
        rows.append((label, nb, human(ex), human(eq), "$%.2f" % cost, per(ex), per(eq), per(comp),
                     "%.2f" % (inp / ex / 1e6) if ex and inp else "-", ("%.0f%%" % (100 * cr / inp)) if inp else "-"))
    rows.sort(key=lambda r: (r[4] == "-", -float(r[4].lstrip("$") or 0) if r[4] != "-" else -int(r[2].replace(",", ""))))
    if not rows:
        return "(no spore-* sessions found)"
    return table(["Model (provider/id)", "Batches", "Exact fns", "Equiv fns", "Cost",
                  "$/exact", "$/equiv", "$/compilable", "In-tok/exact (M)", "cache%"],
                 rows, aligns=["<", ">", ">", ">", ">", ">", ">", ">", ">", ">"])

print()
print("Per-model efficiency (opencode rows: opencode cost estimates, not billed. Claude rows marked "
      "API-rate est.: NOMINAL list-price estimate from a cached transcript scan — a subscription makes "
      "their marginal cost $0. $/exact and $/equiv each divide the model's WHOLE cost, so they are not "
      "additive - use $/compilable for all-in)")
print(model_table())

# ---- live wave groups (optional) ----
def groups_table():
    import collections
    def svc():
        try:
            u = re.search(r"http://[0-9.:]+", subprocess.run(["opencode", "service", "status"],
                        capture_output=True, text=True, timeout=10).stdout).group(0)
            pw = json.load(open(os.path.expanduser("~/.config/opencode/service.json")))["password"]
            H = {"Authorization": "Basic " + base64.b64encode(("opencode:" + pw).encode()).decode()}
            return u, H
        except Exception:
            return None, None
    url, H = svc()
    sess_cost = {}
    active = set()
    if url:
        try:
            loc = "location%5Bdirectory%5D=" + urllib.parse.quote(ROOT)
            r = urllib.request.Request(url + "/api/session?limit=500&" + loc, headers=H)
            for s in json.loads(urllib.request.urlopen(r, timeout=20).read()).get("data", []):
                sess_cost[s["id"]] = s.get("cost", 0) or 0
            r = urllib.request.Request(url + "/api/session/active?" + loc, headers=H)
            d = json.loads(urllib.request.urlopen(r, timeout=20).read()).get("data", {})
            if isinstance(d, dict): active = set(d.keys())
        except Exception:
            pass
    sess_time = {}
    try:
        import sqlite3
        db = subprocess.run(["opencode", "debug", "paths", "db"], capture_output=True, text=True, timeout=10).stdout.strip()
        con = sqlite3.connect(db)
        for sid, tc in con.execute("select id, time_created from session_v2"):
            sess_time[sid] = tc or 0
    except Exception:
        pass
    def nlines(p):
        return sum(1 for l in open(p) if l.strip() and not l.lstrip().startswith("#")) if os.path.exists(p) else 0
    rows = []
    tot = collections.Counter()
    # OpenCode groups, alphabetical by group file name.
    for gf in sorted(glob.glob(W("work/opencode/groups", "*.json"))):
        g = json.load(open(gf)); name = os.path.basename(gf)[:-5]
        batch = json.load(open(W("work/batches", g["batch"] + ".json")))
        account = exact = equiv = tot_funcs = 0; cost = 0.0; act = 0
        for k, sid in g.get("sessions", {}).items():
            if sid in sess_cost: cost += sess_cost[sid]
            if sid in active: act += 1
        for a, b in g["ranges"]:
            for i in range(a, b + 1):
                sid = batch[i]["id"]; tot_funcs += len(batch[i]["vas"])
                if sid in CLAUDE_BASELINE:  # reworked by Claude: show the pre-Claude state
                    b_ex, b_eq = CLAUDE_BASELINE[sid]
                    account += b_ex + b_eq; exact += b_ex; equiv += b_eq
                    continue
                n_ex = nlines(W("match/slices", sid, "manifest.txt"))
                n_eq = nlines(W("match/slices", sid, "nonmatching.txt"))
                n_pa = nlines(W("match/slices", sid, "partial.txt"))
                account += n_ex + n_eq + n_pa; exact += n_ex; equiv += n_eq
        launched = len(g.get("sessions", {})); nranges = len(g["ranges"])
        if account == 0 and launched == 0:
            continue
        if g["batch"] in BATCH_FROZEN:
            exact, account = BATCH_FROZEN[g["batch"]][0], BATCH_FROZEN[g["batch"]][2]
        model = g.get("model", "?")
        model = model.split("/")[-1] if isinstance(model, str) else "?"
        ts = min([sess_time[sid] for sid in g.get("sessions", {}).values() if sid in sess_time], default=0) or int(os.path.getmtime(gf) * 1000)
        rows.append((ts, (name, model, "%d/%d" % (account, tot_funcs), str(exact), str(equiv), "$%.2f" % cost, str(act), "%d/%d" % (launched, nranges))))
        tot["account"] += account; tot["tot"] += tot_funcs; tot["exact"] += exact; tot["equiv"] += equiv
        tot["cost"] += cost; tot["active"] += act
    # Claude-only workflow groups (work/claude/groups.json), in launch order. Counted per assigned VA,
    # so a slice's earlier OpenCode work is not credited here. Cost is subscription usage, not $.
    try:
        cgroups = json.load(open(W("work/claude/groups.json")))
    except (OSError, ValueError):
        cgroups = []
    hexva = re.compile(r"^(?:0x)?([0-9a-fA-F]{8})$")
    for g in cgroups:
        try:
            batch = json.load(open(W("work/batches", g["batch"] + ".json")))
        except (OSError, ValueError):
            continue
        account = exact = equiv = tot_funcs = 0
        for rec in batch:
            mine = {v.lower() for v in rec["vas"]}; tot_funcs += len(mine)
            seen = {}
            for f in ("manifest.txt", "nonmatching.txt", "partial.txt"):
                p = W("match/slices", rec["id"], f)
                if not os.path.exists(p):
                    continue
                for l in open(p):
                    for tok in l.split()[:3]:
                        m = hexva.match(tok)
                        if m and m.group(1).lower() in mine:
                            seen.setdefault(m.group(1).lower(), f)
            account += len(seen)
            exact += sum(1 for f in seen.values() if f == "manifest.txt")
            equiv += sum(1 for f in seen.values() if f == "nonmatching.txt")
        started, done = set(), set()
        try:
            for l in open(g["journal"]):
                e = json.loads(l)
                if not str(e.get("label", "")).startswith(g["batch"] + "[") and e.get("agentId") not in started:
                    continue
                if e.get("type") == "started": started.add(e.get("agentId"))
                elif e.get("type") == "result": done.add(e.get("agentId"))
        except (OSError, ValueError):
            pass
        act = len(started - done)
        try:
            jts = int(os.path.getmtime(g["journal"]) * 1000)
        except OSError:
            jts = 0
        rows.append((jts, (g["name"], g["model"].split("/")[-1], "%d/%d" % (account, tot_funcs), str(exact), str(equiv), "-", str(act), "%d/%d" % (len(started), g.get("units", 0)))))
        tot["account"] += account; tot["tot"] += tot_funcs; tot["exact"] += exact; tot["equiv"] += equiv; tot["active"] += act
    if not rows:
        return None
    rows.sort(key=lambda x: x[0])          # chronological by launch/creation time
    rows = [r for _, r in rows]
    rows.append(("TOTAL", "", "%d/%d" % (tot["account"], tot["tot"]), str(tot["exact"]), str(tot["equiv"]), "$%.2f" % tot["cost"], str(tot["active"]), ""))
    return table(["Group", "Model", "Accounted", "Exact", "Equiv", "Cost", "Active", "Launched"], rows,
                 aligns=["<", "<", ">", ">", ">", ">", ">", ">"])

def parse_status_md(md):
    """Byte-exact and compilable shares from one committed docs/STATUS.md. The table changed
    shape over time: sum the 'byte-exact' rows (not library/upstream ones), take the 'Total with
    compilable source' row (or exact + equivalent/behavioral rows), and the share-by-size column
    when it exists. -> dict or None."""
    rows = []
    for line in md.splitlines():
        if not line.startswith("|") or line.startswith("|---"):
            continue
        cells = [c.strip().strip("*") for c in line.strip("|").split("|")]
        rows.append(cells)
        if len(rows) > 1 and not rows[-1][0]:
            break
    if not rows:
        return None
    head = [h.lower() for h in rows[0]]
    size_col = next((i for i, h in enumerate(head) if "by size" in h), None)
    num = lambda s: float(re.sub(r"[^0-9.]", "", s.split("(")[0]) or "nan")
    denom = exact = comp = None
    exact_sz = comp_sz = None
    mig = mig_sz = None
    eq = 0
    for r in rows[1:]:
        lab = r[0].lower()
        if len(r) < 2 or not re.match(r"^[\d,]+$", r[1].replace(" ", "")):
            continue
        n = num(r[1])
        if lab.startswith("migrated") or "still only in match/slices" in lab:
            # Phase B rows (status.py): only the total counts; its sub-rows repeat the tier words.
            if "total with compilable source" in lab:
                mig = n
                if size_col is not None: mig_sz = num(r[size_col])
            continue
        if "denominator" in lab or lab.startswith("total functions"):
            denom = n
        elif "total with compilable source" in lab:
            comp = n
            if size_col is not None: comp_sz = num(r[size_col])
        elif "byte-exact" in lab and not any(k in lab for k in ("library", "upstream", "total")):
            exact = (exact or 0) + n
            if size_col is not None: exact_sz = (exact_sz or 0) + num(r[size_col])
        elif ("equivalent" in lab or "behavioral" in lab) and "total" not in lab:
            eq += n
    if not denom or exact is None:
        return None
    if comp is None:
        comp = exact + eq
    return {"exact": 100.0 * exact / denom, "comp": 100.0 * comp / denom, "exact_sz": exact_sz, "comp_sz": comp_sz,
            "mig": (100.0 * mig / denom) if mig is not None else None, "mig_sz": mig_sz}


SOUND_DIRS = ("cmn", "plugins", "mix", "decoders", "ealayer30", "ealayer31")   # EA's sound library: one bar


def module_counts():
    """Top-level module (docs/modules.md) -> Counter of n / exact / equiv / part / none / bytes over game functions.
    work/migrate/modmap.json assigns each retail function to the dev build's object file; game functions it does not
    list are split into four rows: globals' initializers/destructors and compiler stubs (status.py's "globals, other
    code"), and code by what its gap in the module map (modmap "gaps": unassigned runs with the object before and
    after) says: one object on both sides, one directory on both sides, or between modules."""
    import bisect
    try:
        M = json.load(open(W("work", "migrate", "modmap.json")))
    except (OSError, ValueError):
        return {}
    mm = M["functions"]
    gaps = sorted((int(g["lo"], 16), int(g["hi"], 16), g.get("before"), g.get("after")) for g in M.get("gaps", []))
    los = [g[0] for g in gaps]

    def unassigned_row(a):
        if a in KG:
            return "(no module: initializers, stubs)"
        i = bisect.bisect_right(los, a) - 1
        if i >= 0 and gaps[i][0] <= a <= gaps[i][1]:
            b, af = gaps[i][2], gaps[i][3]
            if b and b == af:
                return "(no module: code, object known)"
            if b and af and b.split("/")[0] == af.split("/")[0]:
                return "(no module: code, directory known)"
        return "(no module: code between modules)"
    out = collections.defaultdict(collections.Counter)
    seen = set()
    for v, m in mm.items():
        a = int(v, 16)
        if a not in game:
            continue
        mod = (m or {}).get("module") or ""
        top = mod.split("/")[0] if "/" in mod else (mod or "(not in module map)")
        out["EA sound library" if top in SOUND_DIRS else top].update(_tier_of(a))
        seen.add(a)
    for a in game - seen:
        out[unassigned_row(a)].update(_tier_of(a))
    return out


def _tier_of(a):
    k = "exact" if a in byte_exact else "equiv" if a in equiv else "part" if a in part else "none"
    out = {"n": 1, k: 1, "bytes": funcs[a]["size"]}
    if k == "equiv":   # plus its sweep verdict (VERDICT_CATS), for the per-module bars
        out["v_" + _VMAP.get(VERDICT_OF.get(a), "untested")] = 1
    return out


def plot_history(path):
    """PNG of progress over time: one point per committed docs/STATUS.md plus the live numbers."""
    import datetime
    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.dates as mdates
    import matplotlib.pyplot as plt
    log = subprocess.run(["git", "-C", ROOT, "log", "--format=%H %cI", "--", "docs/STATUS.md"],
                         capture_output=True, text=True).stdout.split("\n")
    pts = []
    for line in log:
        if not line.strip():
            continue
        sha, when = line.split()
        md = subprocess.run(["git", "-C", ROOT, "show", sha + ":docs/STATUS.md"], capture_output=True, text=True).stdout
        p = parse_status_md(md)
        if p:
            pts.append((datetime.datetime.fromisoformat(when), p))
    now = datetime.datetime.now().astimezone()
    live = {"exact": 100.0 * len(byte_exact) / G, "comp": 100.0 * len(exact_total) / G,
            "exact_sz": pctb_f(byte_exact), "comp_sz": pctb_f(exact_total),
            "mig": 100.0 * len(migrated) / G, "mig_sz": pctb_f(migrated)}
    if VERDICT_WHEN:   # the compilable-not-exact share split by the latest sweep's verdicts (saved with the day's point)
        live["v"] = {k + sfx: (100.0 * len(equiv_by[k]) / G if not sfx else pctb_f(equiv_by[k]))
                     for k, _l in VERDICT_CATS for sfx in ("", "_sz")}
        live["v_when"] = VERDICT_WHEN
    # One saved point per day (docs/progress_history.json): each run overwrites today's entry with
    # its live numbers, so a day keeps its latest figure and earlier days stay on the chart.
    hist_path = W("docs", "progress_history.json")
    try:
        hist = json.load(open(hist_path))
    except (OSError, ValueError):
        hist = {}
    today = now.date().isoformat()
    mods = module_counts()
    hist[today] = dict(live, when=now.isoformat(timespec="seconds"),
                       modules={m: {"n": c["n"], "exact": 100.0 * c["exact"] / c["n"],
                                    "comp": 100.0 * (c["exact"] + c["equiv"]) / c["n"]} for m, c in mods.items()})
    with open(hist_path, "w") as f:
        json.dump(dict(sorted(hist.items())), f, indent=1)
        f.write("\n")
    # A day with a saved point drops its committed-STATUS.md points: a commit can carry a stale STATUS.md (78294a25,
    # 2026-10-24, committed the 2026-10-19 copy and drew a 4-point dip), and the saved point is the day's real figure.
    pts = [(t, p) for t, p in pts if t.astimezone(now.tzinfo).date().isoformat() not in hist]
    for day, p in hist.items():
        if day != today:      # today is the live point below
            pts.append((datetime.datetime.fromisoformat(p["when"]), p))
    pts.append((now, live))
    pts.sort(key=lambda t: t[0])

    BLUE, ORANGE, GREEN = "#2a78d6", "#eb6834", "#2e9e5b"   # dataviz reference palette, slots 1-3
    INK, MUTED, GRID = "#1f2328", "#59636e", "#e6e8eb"
    order = sorted(mods, key=lambda m: (m.startswith("("), -mods[m]["n"]))   # modules by size, then the "(no module: ...)" rows
    H = 10.3 + (0.6 + 0.3 * len(order) if order else 0)
    fig = plt.figure(figsize=(12, H), dpi=150)
    fig.patch.set_facecolor("white")
    gs = fig.add_gridspec(3 if order else 2, 2, height_ratios=[4.6, 4.8] + ([H - 10.3] if order else []))
    axes = [fig.add_subplot(gs[0, 0])]
    axes.append(fig.add_subplot(gs[0, 1], sharey=axes[0], sharex=axes[0]))
    plt.setp(axes[1].get_yticklabels(), visible=False)
    TC_LINE = {"pass": "#009E73", "fail": "#D55E00"}   # the PASS / FAIL colours of the evidence bands
    GREEN = "#7a7a7a"   # migrated: grey here, so the PASS line keeps the green
    panels = (("Share of functions", "exact", "comp", "mig"), ("Share of code size", "exact_sz", "comp_sz", "mig_sz"))
    for ax, (title, ke, kc, km) in zip(axes, panels):
        for key, color, label in ((kc, ORANGE, "Compilable (byte-exact + compiles, not exact)"), (ke, BLUE, "Byte-exact"),
                                  (km, GREEN, "Migrated into src/game module TUs")):
            xs = [t for t, p in pts if p.get(key) is not None]
            ys = [p[key] for t, p in pts if p.get(key) is not None]
            if not xs:
                continue
            ax.plot(xs, ys, color=color, lw=2, marker="o", ms=4, label=label, solid_capstyle="round")
            ax.annotate("%.1f%%" % ys[-1], (xs[-1], ys[-1]), xytext=(6, 0), textcoords="offset points",
                        va="center", fontsize=9, color=INK)
        # Spliced in from the first equivalence sweep on (points that carry verdicts): byte-exact + PASS branches up
        # from the byte-exact line, compilable - FAIL branches down from the compilable line, each starting at the
        # last point before verdicts existed.
        sfx = ke[len("exact"):]
        for base, sign, k, color, label in ((ke, 1, "pass", TC_LINE["pass"], "Shown correct (byte-exact + test PASS)"),
                                            (kc, -1, "fail", TC_LINE["fail"], "Compilable minus test FAIL")):
            vx = [(t, p) for t, p in pts if p.get(base) is not None and (p.get("v") or {}).get(k + sfx) is not None]
            if not vx:
                continue
            prior = [(t, p) for t, p in pts if t < vx[0][0] and p.get(base) is not None]
            xs = [t for t, _p in prior[-1:]] + [t for t, _p in vx]
            ys = [p[base] for _t, p in prior[-1:]] + [p[base] + sign * p["v"][k + sfx] for _t, p in vx]
            ax.plot(xs, ys, color=color, lw=2, ls="--", marker="o", ms=4, markevery=list(range(len(prior[-1:]), len(xs))),
                    label=label, solid_capstyle="round")
            ax.annotate("%.1f%%" % ys[-1], (xs[-1], ys[-1]), xytext=(6, 0), textcoords="offset points",
                        va="center", fontsize=9, color=color)
        ax.set_title(title, loc="left", fontsize=11, color=INK)
        ax.set_ylim(0, 100)
        ax.yaxis.set_major_formatter(matplotlib.ticker.PercentFormatter(decimals=0))
        ax.grid(axis="y", color=GRID, lw=1)
        ax.set_axisbelow(True)
        for s in ("top", "right", "left"):
            ax.spines[s].set_visible(False)
        ax.spines["bottom"].set_color(GRID)
        ax.tick_params(colors=MUTED, labelsize=9, length=0)
        ax.xaxis.set_major_locator(mdates.DayLocator())
        ax.xaxis.set_major_formatter(mdates.DateFormatter("%b %d"))
        ax.tick_params(axis="x", labelrotation=45)   # one label per day overlaps when horizontal
        plt.setp(ax.get_xticklabels(), ha="right", rotation_mode="anchor")
        ax.margins(x=0.08)
    axes[0].legend(loc="center right", bbox_to_anchor=(1.0, 0.42), frameon=False, fontsize=9, labelcolor=INK)
    # Every game function, 100%: byte-exact at the bottom, equivalent (PASS) above it, then the other verdicts of the
    # compilable-not-exact functions, then partial / no source. A day before the first sweep (or a committed
    # STATUS.md point) has no verdicts, so its whole compilable-not-exact share is "not tested yet".
    TC = dict((k, c) for k, _l, c in TREE_CATS)
    LAYERS = [("exact", "Byte-exact", TC["byte-exact"]), ("pass", dict(VERDICT_CATS)["pass"], TC["pass"]),
              ("weak", dict(VERDICT_CATS)["weak"], TC["weak"]), ("fail", dict(VERDICT_CATS)["fail"], TC["fail"]),
              ("inputs", dict(VERDICT_CATS)["inputs"], TC["inputs"]), ("harness", dict(VERDICT_CATS)["harness"], TC["harness"]),
              ("untested", "Compiles, not tested yet by the new harness", TC["untested"]),
              ("rest", "Partial or no source", "#e6e8eb")]
    for col, (title, sfx) in enumerate((("All game functions, by evidence", ""), ("... by code size", "_sz"))):
        ax = fig.add_subplot(gs[1, col], sharex=axes[0])
        sp = [(t, p) for t, p in pts if p.get("exact" + sfx) is not None and p.get("comp" + sfx) is not None]
        xs = [t for t, _p in sp]
        ys = {k: [] for k, _l, _c in LAYERS}
        for _t, p in sp:
            v = p.get("v") or {}
            known = 0.0
            for k, _l, _c in LAYERS[1:-2]:
                ys[k].append(v.get(k + sfx, 0.0))
                known += ys[k][-1]
            ys["exact"].append(p["exact" + sfx])
            ys["untested"].append(max(0.0, p["comp" + sfx] - p["exact" + sfx] - known))
            ys["rest"].append(max(0.0, 100.0 - p["comp" + sfx]))
        keys = [k for k, _l, _c in LAYERS if any(y > 0 for y in ys[k])]
        # steps, not slopes: a value holds until the next point (interpolating drew the first sweep's verdicts as a
        # wedge growing from the previous --plot day)
        for i in range(len(xs) - 1, 0, -1):
            xs.insert(i, xs[i] - datetime.timedelta(seconds=1))
            for k in ys:
                ys[k].insert(i, ys[k][i - 1])
        if xs:   # the last point (now) holds for a day and a half, or a step chart would give it no width
            xs.append(xs[-1] + datetime.timedelta(hours=36))
            for k in ys:
                ys[k].append(ys[k][-1])
        if xs:
            ax.stackplot(xs, [ys[k] for k in keys], colors=[c for k, _l, c in LAYERS if k in keys],
                         labels=[l for k, l, _c in LAYERS if k in keys], edgecolor="white", linewidth=0.6)
            base = 0.0
            for k in keys:
                y = ys[k][-1]
                if y >= 2.5:
                    ax.annotate("%.1f%%" % y, (xs[-1], base + y / 2), xytext=(6, 0), textcoords="offset points",
                                va="center", fontsize=8.5, color=INK)
                base += y
        ax.set_title(title, loc="left", fontsize=11, color=INK)
        ax.set_ylim(0, 100)
        ax.yaxis.set_major_formatter(matplotlib.ticker.PercentFormatter(decimals=0))
        for sp_ in ("top", "right", "left"):
            ax.spines[sp_].set_visible(False)
        ax.spines["bottom"].set_color(GRID)
        ax.tick_params(colors=MUTED, labelsize=9, length=0)
        ax.tick_params(axis="x", labelrotation=45)
        plt.setp(ax.get_xticklabels(), ha="right", rotation_mode="anchor")
        if col:
            plt.setp(ax.get_yticklabels(), visible=False)
    if order:
        # per module, now: each bar is 100% of the module's functions, split by tier (docs/modules.md)
        bx = fig.add_subplot(gs[2, :])
        PARTIAL, NONE = "#f6c7a9", "#e6e8eb"
        y = list(range(len(order)))[::-1]
        left = [0.0] * len(order)
        for key, color, label in ([("exact", TC["byte-exact"], "Byte-exact")] +
                                  [("v_" + k, TC[k], l) for k, l, _c in LAYERS[1:-1]] +
                                  [("part", TC["partial"], "Partial"), ("none", NONE, "No source yet")]):
            w = [100.0 * mods[m][key] / mods[m]["n"] for m in order]
            bx.barh(y, w, left=left, color=color, height=0.7, label=label)
            left = [l + x for l, x in zip(left, w)]
        for yy, m in zip(y, order):
            c = mods[m]
            bx.text(101, yy, "%s functions, %.1f MB   exact %.0f%%, PASS %.0f%%, FAIL %.0f%%" % (
                "{:,}".format(c["n"]), c["bytes"] / 2**20, 100.0 * c["exact"] / c["n"],
                100.0 * c["v_pass"] / c["n"], 100.0 * c["v_fail"] / c["n"]), va="center", fontsize=8, color=MUTED)
        bx.set_yticks(y)
        bx.set_yticklabels(order, fontsize=9, color=INK)
        bx.set_xlim(0, 140)
        bx.set_xticks([0, 25, 50, 75, 100])
        bx.xaxis.set_major_formatter(matplotlib.ticker.PercentFormatter(decimals=0))
        for sp in ("top", "right", "left"):
            bx.spines[sp].set_visible(False)
        bx.spines["bottom"].set_color(GRID)
        bx.tick_params(colors=MUTED, labelsize=9, length=0)
        bx.set_title("By module, now (same colours as above)", loc="left", fontsize=11, color=INK)
    fig.suptitle("Spore decompilation progress (game functions; third-party libraries excluded)",
                 x=0.01, ha="left", fontsize=12, color=INK)
    fig.text(0.01, 0.01, "One point per committed docs/STATUS.md, one per day of --plot runs (latest run that day), plus now.\nEquivalent = complete compilable source, "
             "not yet byte-identical. Size shares only exist in later snapshots; the migrated line starts with Phase B "
             "(Oct 2026).\nEvidence bands: verdicts of the merged equivalence harness (tools/difftest/verdicts.py, first "
             "sweep 2026-10-29); a FAIL is a mismatch, so not equivalent. Days before it count as not tested.",
             fontsize=8, color=MUTED)
    from matplotlib.patches import Patch
    leg = [Patch(fc=c, label=l) for k, l, c in LAYERS]
    if order:
        leg = leg[:-1] + [Patch(fc=TC["partial"], label="Partial source"), Patch(fc="#e6e8eb", label="No source yet (evidence bands: partial too)")]
    fig.legend(handles=leg, loc="lower left", bbox_to_anchor=(0.01, 0.5 / H), ncol=3, frameon=False, fontsize=8.5,
               labelcolor=INK, title="Evidence bands and module bars (bottom to top / left to right):",
               title_fontsize=8.5, alignment="left")
    fig.tight_layout(rect=(0, 1.35 / H, 1, 1 - 0.23 / H))   # room for the two-line footnote and the title (inches / H)
    fig.savefig(path)
    print("wrote %s (%d snapshots)" % (os.path.relpath(path, ROOT), len(pts)))


def pctb_f(items):
    return 100.0 * sum(funcs[a]["size"] for a in items) / GB



# ---------------------------------------------------------------- treemap
# Ported from mountandblade-decomp's tools/progress.py (2026-10-29). Okabe-Ito colours (colour-blind safe), one hue per
# verdict. The verdicts are the latest equivalence sweep's (docs/equiv_verdicts.json, see VERDICT_CATS above).
TREE_CATS = (("byte-exact", "Byte-exact", "#0072B2"),                                  # blue
             ("pass", "Equivalent: test PASS (every branch ran)", "#009E73"),          # bluish green
             ("weak", "Probably equivalent: WEAK (some branch never ran)", "#E69F00"), # orange
             ("inputs", "Untestable: random inputs invalid", "#CC79A7"),               # reddish purple
             ("harness", "Untestable: harness limit or symbol not found", "#56B4E9"),  # sky blue
             ("untested", "Compiles, not tested yet by the new harness", "#F0E442"),   # yellow
             ("fail", "NOT equivalent: test FAIL (a mismatch)", "#D55E00"),            # vermillion
             ("partial", "Partial source", "#999999"),                                 # the only grey
             ("nosource", "No source yet", "#FFFFFF"))


UNPLACED = "Not placed in a source file yet"
_COMPONENTS = None


def _component_of(a):
    """symbols/components.json range component of a (Havok, RenderWare, ...), else "Spore code"."""
    global _COMPONENTS
    if _COMPONENTS is None:
        _COMPONENTS = [(n, [(int(lo, 16), int(hi, 16)) for lo, hi in r])
                       for n, r in json.load(open(W("symbols", "components.json"))).items()
                       if not n.startswith("_") and not isinstance(r, dict)]
    return next((n for n, rs in _COMPONENTS if any(lo <= a < hi for lo, hi in rs)), "Spore code")


def _tree_rows():
    """(group, box, va, bytes, category) for every game function. Group = top directory of the dev build's object
    (work/migrate/modmap.json), box = the object. A function the module map does not assign joins the object on both
    sides of its gap when there is one; the rest go under "Not placed in a source file yet", boxed by kind (globals'
    initializers and compiler stubs) or component (Havok, RenderWare, Spore code). Those cannot be migrated into
    src/game until the module map places them."""
    import bisect
    try:
        MM = json.load(open(W("work", "migrate", "modmap.json")))
    except (OSError, ValueError):
        MM = {"functions": {}, "gaps": []}
    mod = {int(v, 16): (m or {}).get("module") for v, m in MM["functions"].items()}
    gaps = sorted((int(g["lo"], 16), int(g["hi"], 16), g.get("before"), g.get("after")) for g in MM.get("gaps", []))
    los = [g[0] for g in gaps]
    rows = []
    for a in sorted(game):
        m = mod.get(a)
        if not m and a not in KG:
            i = bisect.bisect_right(los, a) - 1
            if i >= 0 and gaps[i][0] <= a <= gaps[i][1] and gaps[i][2] and gaps[i][2] == gaps[i][3]:
                m = gaps[i][2]
        if m:
            top = m.split("/")[0] if "/" in m else m
            group = "EA sound library" if top in SOUND_DIRS else top
            box = m.rsplit("/", 1)[-1].replace(".obj", "")
        elif a in KG:
            group, box = UNPLACED, "globals' initializers, compiler stubs"
        else:
            group, box = UNPLACED, _component_of(a)
        if a in byte_exact:
            cat = "byte-exact"
        elif a in equiv:
            cat = _VMAP.get(VERDICT_OF.get(a), "untested")
        elif a in part:
            cat = "partial"
        else:
            cat = "nosource"
        rows.append((group, box, a, funcs[a]["size"] or 1, cat))
    return rows


def _worst(row, side):
    s = sum(v for _, v in row)
    mx = max(v for _, v in row)
    mn = min(v for _, v in row)
    if s <= 0 or mn <= 0:
        return float("inf")
    return max(side * side * mx / (s * s), (s * s) / (side * side * mn))


def squarify(items, x, y, w, h):
    """Squarified treemap: [(key, weight)] -> [(key, (x, y, w, h))], areas proportional to weight."""
    items = sorted(((k, float(v)) for k, v in items if v > 0), key=lambda kv: -kv[1])
    tot = sum(v for _, v in items)
    if not tot or w <= 0 or h <= 0:
        return []
    items = [(k, v * w * h / tot) for k, v in items]
    out, i = [], 0
    while i < len(items):
        side = min(w, h)
        row, j = [items[i]], i + 1
        while j < len(items) and _worst(row, side) >= _worst(row + [items[j]], side):
            row.append(items[j])
            j += 1
        rsum = sum(v for _, v in row)
        if w >= h:                      # shorter side is the height: the row is a column of full height
            rw = rsum / h
            cy = y
            for k, v in row:
                rh = v / rw if rw else 0.0
                out.append((k, (x, cy, rw, rh)))
                cy += rh
            x, w = x + rw, w - rw
        else:                           # shorter side is the width: the row is a band of full width
            rh = rsum / w
            cx = x
            for k, v in row:
                rw = v / rh if rh else 0.0
                out.append((k, (cx, y, rw, rh)))
                cx += rw
            y, h = y + rh, h - rh
        i = j
    return out


def treemap(path):
    """Treemap of every game function: group -> dev-build object -> verdict, area = code bytes. Inside an object the
    functions are drawn as one block per verdict (88k single functions are too small to see). Object labels are
    measured and kept only where they fit (horizontal first, then rotated, then smaller), so none overlap."""
    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
    from matplotlib.collections import PatchCollection
    from matplotlib.patches import Patch, Rectangle
    INK, MUTED, SURFACE = "#0b0b0b", "#52514e", "#fcfcfb"
    rows = _tree_rows()
    colour = dict((k, c) for k, _l, c in TREE_CATS)
    label = dict((k, l) for k, l, _c in TREE_CATS)
    order = [k for k, _l, _c in TREE_CATS]
    counts = collections.Counter(r[4] for r in rows)
    size = collections.Counter()
    boxes = collections.defaultdict(collections.Counter)    # (group, box) -> category -> bytes
    gsz = collections.Counter()
    for g, b, _a, n, cat in rows:
        size[cat] += n
        boxes[(g, b)][cat] += n
        gsz[g] += n
    tot_b, tot_n = sum(size.values()) or 1, len(rows) or 1
    W_, H_ = 141.0, 100.0

    fig, ax = plt.subplots(figsize=(16.0, 11.2), dpi=150)
    fig.patch.set_facecolor(SURFACE)
    ax.set_facecolor(SURFACE)
    ax.set_xlim(0, W_)
    ax.set_ylim(0, H_)
    ax.set_xticks([])
    ax.set_yticks([])
    for sp in ax.spines.values():
        sp.set_visible(False)
    ax.set_position([0.012, 0.13, 0.976, 0.745])

    FS = 6.4
    cal = ax.text(0, 0, ("SPGonzago_0123456789_" * 4), fontsize=FS, color=INK)
    fig.canvas.draw()
    bb = cal.get_window_extent(fig.canvas.get_renderer())
    (cx0, cy0), (cx1, cy1) = ax.transData.inverted().transform([[bb.x0, bb.y0], [bb.x1, bb.y1]])
    line_h = abs(cy1 - cy0)
    cal.remove()

    fills, fcol, frames = [], [], []
    labels = []
    for g, (gx, gy, gw, gh) in squarify(list(gsz.items()), 0, 0, W_, H_):
        gx, gy, gw, gh = gx + 0.5, gy + 0.5, gw - 1.0, gh - 1.0
        if gw <= 1 or gh <= 1:
            continue
        ax.add_patch(Rectangle((gx, gy), gw, gh, fill=False, lw=1.5, ec=INK, zorder=5))
        if gw > 6 and gh > 2.5:
            fs_g = 10.5 if gw > 14 else 7
            gl = g if len(g) * fs_g * 0.105 < gw - 0.8 else g[:max(1, int((gw - 0.8) / (fs_g * 0.105)) - 1)] + "…"
            ax.text(gx + 0.4, gy + gh - 0.15, gl, ha="left", va="top", fontsize=fs_g, color=INK,
                    weight="bold", zorder=7, bbox=dict(boxstyle="square,pad=0.1", fc=SURFACE, ec="none"))
        strip = line_h + 0.75 if gw > 6 and gh > 2.5 else 0.1
        mine = {b: c for (gg, b), c in boxes.items() if gg == g}
        for b, (fx, fy, fw, fh) in squarify([(b, sum(c.values())) for b, c in mine.items()],
                                            gx + 0.35, gy + 0.35, gw - 0.7, gh - strip - 0.35):
            fx, fy, fw, fh = fx + 0.06, fy + 0.06, fw - 0.12, fh - 0.12
            if fw <= 0 or fh <= 0:
                continue
            frames.append(Rectangle((fx, fy), fw, fh))
            # verdict blocks in a fixed order (exact first), so the mix reads the same way in every box
            cx, cy, cw, ch = fx, fy, fw, fh
            cats = [(k, mine[b][k]) for k in order if mine[b][k]]
            tot = float(sum(v for _, v in cats))
            for k, v in cats:
                if cw >= ch:
                    d = cw * v / tot
                    fills.append(Rectangle((cx, cy), d, ch)); cx += d; cw -= d
                else:
                    d = ch * v / tot
                    fills.append(Rectangle((cx, cy + ch - d), cw, d)); ch -= d
                fcol.append(colour[k])
                tot -= v
            if fw > 1.2 and fh > 1.0:
                t = ax.text(fx + 0.2, fy + fh - 0.2, b, ha="left", va="top", fontsize=FS, color=INK, zorder=6,
                            bbox=dict(boxstyle="square,pad=0.1", fc=SURFACE, ec="none", alpha=0.85))
                labels.append((t, (fx, fy, fw, fh), b))
    ax.add_collection(PatchCollection(fills, facecolors=fcol, edgecolors="none", linewidths=0, zorder=2,
                                      antialiased=False))
    ax.add_collection(PatchCollection(frames, facecolors="none", edgecolors=MUTED, linewidths=0.3, zorder=4))

    def bbox_data(t):
        bb = t.get_window_extent(fig.canvas.get_renderer())
        (x0, y0), (x1, y1) = ax.transData.inverted().transform([[bb.x0, bb.y0], [bb.x1, bb.y1]])
        return min(x0, x1), min(y0, y1), max(x0, x1), max(y0, y1)

    def place(t, r, rot):
        """Rotate the label and put its measured box inside the cell; False when it cannot fit at this size."""
        t.set_rotation(rot)
        t.set_ha("left")
        t.set_va("top" if rot == 0 else "bottom")
        x0, y0, x1, y1 = bbox_data(t)
        fx, fy, fw, fh = r
        if x1 - x0 > fw - 0.4 or y1 - y0 > fh - 0.3:
            return False
        px, py = t.get_position()
        t.set_position((px + (fx + 0.2 - x0), py + (fy + fh - 0.2 - y1)))
        return True

    placed, pending = 0, labels
    for fsz in (FS, FS - 0.9, FS - 1.7, 4.0):
        for t, r, _nm in pending:
            t.set_fontsize(fsz)
            t.set_position((r[0] + 0.2, r[1] + r[3] - 0.2))
            t.set_rotation(0)
        fig.canvas.draw()
        rot, still = [], []
        for t, r, nm in pending:
            if place(t, r, 0):
                placed += 1
                continue
            t.set_position((r[0] + 0.2, r[1] + 0.25))
            rot.append((t, r, nm))
        fig.canvas.draw()
        for t, r, nm in rot:
            if place(t, r, 90):
                placed += 1
                continue
            t.set_rotation(0)
            still.append((t, r, nm))
        pending = still
    for t, _r, _nm in pending:
        t.remove()                      # nothing fits: the colours still carry the verdicts
    handles = [Patch(fc=colour[k], ec="#d8d6cf", lw=0.5,
                     label="%s - %s functions, %.1f%% of the code" % (label[k], human(counts[k]), 100.0 * size[k] / tot_b))
               for k in order if counts[k]]
    fig.legend(handles=handles, loc="lower left", bbox_to_anchor=(0.012, 0.004), frameon=False, fontsize=8.6,
               labelcolor=INK, ncol=2, handlelength=1.1, handleheight=0.9)
    fig.suptitle("Spore (SporeApp.exe): %s game functions, %.2f MB - area = code bytes, colour = verdict"
                 % (human(tot_n), tot_b / 2**20), x=0.012, ha="left", fontsize=12, color=INK)
    fig.text(0.012, 0.945, "Group (top directory of the dev build) -> object file -> one block per verdict; area = "
             "function size in bytes. Objects come from work/migrate/modmap.json; functions it does "
             "not place in an object (so not migratable yet) are grouped by kind.\nThird-party libraries (OpenSSL, libpng, zlib, libjpeg, CRT) are excluded, "
             "as in docs/STATUS.md. Verdicts: the equivalence sweep at %s (tools/difftest/verdicts.py)."
             % (VERDICT_WHEN or "- (none yet)"), fontsize=8.2, color=MUTED, va="top")
    fig.savefig(path, facecolor=SURFACE)
    print("wrote %s (%s functions in %d objects, %d labels)" % (os.path.relpath(path, ROOT), human(tot_n), len(boxes),
                                                               placed))


if "--groups" in sys.argv:
    t = groups_table()
    print()
    if t: print(t)
    else: print("(no live wave groups found)")

print()
print("Generated by tools/progress.py (coverage logic shared with tools/status.py).")

# Last on purpose: the plot path is the final line of output, whatever other flags are given.
if "--plot" in sys.argv:
    i = sys.argv.index("--plot")
    out = sys.argv[i + 1] if i + 1 < len(sys.argv) and not sys.argv[i + 1].startswith("--") else W("work", "progress.png")
    plot_history(out)
if "--treemap" in sys.argv:
    i = sys.argv.index("--treemap")
    out = sys.argv[i + 1] if i + 1 < len(sys.argv) and not sys.argv[i + 1].startswith("--") else W("work", "treemap.png")
    treemap(out)
