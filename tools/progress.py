#!/usr/bin/env python3
"""Print Spore decompilation progress as terminal tables. Standalone: run from any shell.

  .venv/bin/python tools/progress.py            # coverage + components
  .venv/bin/python tools/progress.py --groups    # also live opencode wave groups
  .venv/bin/python tools/progress.py --plot [out.png]  # chart of progress over time (default work/progress.png;
                                                       # one point per committed docs/STATUS.md and one per day of
                                                       # --plot runs, kept in docs/progress_history.json; needs matplotlib)
                                                       # below it, one bar per module (docs/modules.md) split into byte-exact /
                                                       # equivalent / partial / no source; per-module shares go into the history too
  .venv/bin/python tools/progress.py --no-refresh # reuse docs/STATUS.md-derived cache? (still recomputes)

Coverage is computed with the exact logic of tools/status.py (reused via runpy), so numbers
match docs/STATUS.md. --groups reads work/opencode/groups/*.json + match/slices manifests, and
uses the opencode service for cost/active if it is reachable (otherwise shows "-").
"""
import base64, collections, contextlib, glob, io, json, os, re, runpy, subprocess, sys, urllib.parse, urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
W = lambda *p: os.path.join(ROOT, *p)

# Byte-exact counts that were verified but never written to manifest.txt (so the
# manifest scan misses them). b007: GLM's per-slice re-check found 33 byte-exact, of
# which 3 are in a manifest (s00680c30); the other 30 were never banked.
EXTRA_EXACT = {"b007": 30}
# b008/b009 were created from the 10 b007 slices GLM never started, so those slice
# IDs appear in two batches; the manifests are DeepSeek's, not GLM's. Do not let b007
# claim slices it shares with those batches.
CLAIM_EXCLUDE = {"b007": {"b008", "b009"}}
# Slices that Claude workflows (cl1_*, op1_*) later reworked: opencode models are credited with
# their manifest/nonmatching counts frozen at the last pre-Claude commit, not with Claude's edits.
# bfs4 was never committed before Claude resumed it, so its DeepSeek output is not recoverable
# per slice; BATCH_FROZEN pins its total to the 178 byte-exact shown before the handoff.
try:
    CLAUDE_BASELINE = json.load(open(W("work/claude/opencode_baseline.json")))["slices"]
except (OSError, ValueError, KeyError):
    CLAUDE_BASELINE = {}
BATCH_FROZEN = {"bfs4": (178, None, 625)}  # (exact, equiv unknown, accounted)
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
GB_MB = GB / 2**20
def pctb(items):
    return pct(mb(items), GB_MB)
rows = [
    ("Byte-exact: free functions",        len(byte_exact & KF), pct(len(byte_exact & KF), G), mb(byte_exact & KF), pctb(byte_exact & KF)),
    ("Byte-exact: classes/templates",     len(byte_exact & KC), pct(len(byte_exact & KC), G), mb(byte_exact & KC), pctb(byte_exact & KC)),
    ("Byte-exact: globals/other code",    len(byte_exact & KG), pct(len(byte_exact & KG), G), mb(byte_exact & KG), pctb(byte_exact & KG)),
    ("BYTE-EXACT TOTAL",                  len(byte_exact),       pct(len(byte_exact), G),       mb(byte_exact),       pctb(byte_exact)),
    ("Equivalent (compilable, not exact)",len(equiv),            pct(len(equiv), G),            mb(equiv),            pctb(equiv)),
    ("Partial (incomplete)",              len(part),             pct(len(part), G),             mb(part),             pctb(part)),
    ("No source yet",                     len(nosrc),            pct(len(nosrc), G),            mb(nosrc),            pctb(nosrc)),
    ("TOTAL WITH COMPILABLE SOURCE",      len(exact_total),      pct(len(exact_total), G),      mb(exact_total),      pctb(exact_total)),
    ("Game functions (denominator)",      G,                     "100.00%",                     GB_MB,                "100.00%"),
]
print("Spore decompilation progress")
print()
print(table(["Tier", "Functions", "% count", "MB", "% size"],
            [(a, human(b), c, "%.2f" % d, e) for a, b, c, d, e in rows],
            aligns=["<", ">", ">", ">", ">"]))

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

_slice_log = None
# a manifest row ("slices/<id>/<id>.cpp sym va ...") or a nonmatching row ("<va> ..."), not a note line
ROW_RE = re.compile(r"^(?:slices/\S+\s+\S+\s+(?:0x)?[0-9a-fA-F]{6,8}\b|[0-9a-fA-F]{6,8}(?:\s|$))")


def commit_row_deltas(tag):
    """(exact, equivalent) rows net-added to match/slices/*/manifest.txt and nonmatching.txt by
    commits whose subject starts with "<tag>:", or None when there are no such commits."""
    global _slice_log
    if _slice_log is None:
        try:
            _slice_log = subprocess.run(["git", "-C", ROOT, "log", "--format=@%s", "-p", "-U0", "--no-renames", "--",
                                         "match/slices/*/manifest.txt", "match/slices/*/nonmatching.txt"],
                                        capture_output=True, text=True, check=True).stdout
        except (OSError, subprocess.CalledProcessError):
            _slice_log = ""
    out = _slice_log
    ex = eq = 0; mine = seen = False; cur = None
    for l in out.splitlines():
        if l.startswith("@") and not l.startswith("@@"):
            mine = l[1:].startswith(tag + ":"); seen |= mine
            continue
        if l.startswith("+++ ") or l.startswith("--- "):
            if l.startswith("+++ "):
                cur = "ex" if l.endswith("/manifest.txt") else "eq"
            continue
        if not mine or l[:1] not in "+-" or not ROW_RE.match(l[1:]):
            continue
        n = 1 if l[0] == "+" else -1
        if cur == "ex":
            ex += n
        else:
            eq += n
    return (ex, eq) if seen else None


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
    def batch_counts(batch):
        """(exact, equivalent) function counts from this batch's manifests, minus
        slices that actually belong to a different model's batch."""
        bf = W("work/batches", batch + ".json"); ex = eq = 0
        gf = W("work/opencode/groups", batch + ".json")
        if not os.path.exists(bf) and os.path.exists(gf):
            # opencode_sup titles sessions by group (gold3g0); the group names its batch
            bf = W("work/batches", json.load(open(gf))["batch"] + ".json")
        exclude = CLAIM_EXCLUDE.get(batch, set())
        recs = json.load(open(bf)) if os.path.exists(bf) else []
        tag = os.path.basename(bf)[:-5]
        if recs and not any(r.get("module") for r in recs):
            d = commit_row_deltas(tag)
            if d is not None:
                # waves that rework existing slices (dec2, gold3 after gold2): credit only the rows
                # their own "<tag>:" commits added, not every row the slices hold today
                return d[0] + EXTRA_EXACT.get(batch, 0), d[1]
        if recs:
            for rec in recs:
                if _slice_batches[rec["id"]] & exclude:
                    continue  # shared slice actually produced by another model's batch
                if rec["id"] in CLAUDE_BASELINE:
                    # later reworked by a Claude workflow: credit only what existed before
                    b_ex, b_eq = CLAUDE_BASELINE[rec["id"]]
                    ex += b_ex; eq += b_eq
                    continue
                if rec.get("module"):
                    # migration batch: credit the entry's VAs found in the module's bookkeeping, not the slice's
                    want = {v.lower() for v in rec["vas"]}
                    for fname, is_exact in (("manifest.txt", True), ("nonmatching.txt", False)):
                        p = W("src/game", rec["module"], fname)
                        if os.path.exists(p):
                            for l in open(p):
                                parts = l.split("#", 1)[0].split()
                                va = (parts[2] if is_exact and len(parts) > 2 else parts[0] if parts else "").lower()
                                if va in want:
                                    if is_exact: ex += 1
                                    else: eq += 1
                    continue
                for fname, is_exact in (("manifest.txt", True), ("nonmatching.txt", False)):
                    p = W("match/slices", rec["id"], fname)
                    if os.path.exists(p):
                        n = sum(1 for l in open(p) if ROW_RE.match(l))   # wrapped notes are not rows
                        if is_exact:
                            ex += n
                        else:
                            eq += n
        if batch in BATCH_FROZEN:  # equivalents stay as computed (an undercount for bfs4)
            ex = BATCH_FROZEN[batch][0]
        return ex + EXTRA_EXACT.get(batch, 0), eq

    agg = collections.defaultdict(lambda: {"cost": 0.0, "inp": 0, "cr": 0, "out": 0,
                                            "rea": 0, "exact": 0, "equiv": 0, "batches": 0})
    counts = {}
    for (batch, key), a in bm.items():
        # a batch served by several models (a mid-wave provider switch) splits its functions by share of model calls
        if batch not in counts:
            counts[batch] = batch_counts(batch)
        ex, eq = counts[batch]
        share = a["n"] / calls[batch] if calls[batch] else 0
        g = agg[key]
        for k in ("cost", "inp", "cr", "out", "rea"):
            g[k] += a[k]
        g["exact"] += ex * share; g["equiv"] += eq * share; g["batches"] += 1
    rows = []
    for key, g in sorted(agg.items(), key=lambda x: -x[1]["cost"]):
        ex, eq = g["exact"], g["equiv"]; comp = ex + eq
        inp = g["inp"] + g["cr"]
        per = lambda d: ("$%.4f" % (g["cost"] / d)) if d else "-"
        ex, eq = int(round(ex)), int(round(eq)); comp = ex + eq
        rows.append((key, g["batches"], human(ex), human(eq), "$%.2f" % g["cost"],
                     per(ex), per(eq), per(comp),
                     "%.2f" % (inp / ex / 1e6) if ex else "-",
                     ("%.0f%%" % (100 * g["cr"] / inp)) if inp else "-"))
    # Claude models: NOMINAL API-rate cost from a cached transcript scan (subscription => $0 marginal).
    try:
        cr_json = json.load(open(W("work/claude/model_efficiency.json")))
    except (OSError, ValueError):
        cr_json = {}
    for key, g in cr_json.items():
        ex, eq = g.get("exact", 0), g.get("equiv", 0); comp = ex + eq
        inp = g.get("inp", 0) + g.get("cr", 0)
        per = lambda d: ("$%.4f" % (g["cost"] / d)) if d else "-"
        rows.append((key + " (API-rate est.)", g.get("batches", 0), human(ex), human(eq), "$%.2f" % g.get("cost", 0),
                     per(ex), per(eq), per(comp),
                     "%.2f" % (inp / ex / 1e6) if ex else "-",
                     ("%.0f%%" % (100 * g.get("cr", 0) / inp)) if inp else "-"))
    rows.sort(key=lambda r: -float(r[4].lstrip("$") or 0))     # most expensive first
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
    return {"n": 1, k: 1, "bytes": funcs[a]["size"]}


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
    for day, p in hist.items():
        if day != today:      # today is the live point below
            pts.append((datetime.datetime.fromisoformat(p["when"]), p))
    pts.append((now, live))
    pts.sort(key=lambda t: t[0])

    BLUE, ORANGE, GREEN = "#2a78d6", "#eb6834", "#2e9e5b"   # dataviz reference palette, slots 1-3
    INK, MUTED, GRID = "#1f2328", "#59636e", "#e6e8eb"
    order = sorted(mods, key=lambda m: (m.startswith("("), -mods[m]["n"]))   # modules by size, then the "(no module: ...)" rows
    H = 4.6 + (0.6 + 0.3 * len(order) if order else 0)
    fig = plt.figure(figsize=(12, H), dpi=150)
    fig.patch.set_facecolor("white")
    gs = fig.add_gridspec(2 if order else 1, 2, height_ratios=[4.6, H - 4.6] if order else [1])
    axes = [fig.add_subplot(gs[0, 0])]
    axes.append(fig.add_subplot(gs[0, 1], sharey=axes[0], sharex=axes[0]))
    plt.setp(axes[1].get_yticklabels(), visible=False)
    panels = (("Share of functions", "exact", "comp", "mig"), ("Share of code size", "exact_sz", "comp_sz", "mig_sz"))
    for ax, (title, ke, kc, km) in zip(axes, panels):
        for key, color, label in ((kc, ORANGE, "Compilable (byte-exact + equivalent)"), (ke, BLUE, "Byte-exact"),
                                  (km, GREEN, "Migrated into src/game module TUs")):
            xs = [t for t, p in pts if p.get(key) is not None]
            ys = [p[key] for t, p in pts if p.get(key) is not None]
            if not xs:
                continue
            ax.plot(xs, ys, color=color, lw=2, marker="o", ms=4, label=label, solid_capstyle="round")
            ax.annotate("%.1f%%" % ys[-1], (xs[-1], ys[-1]), xytext=(6, 0), textcoords="offset points",
                        va="center", fontsize=9, color=INK)
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
    axes[0].legend(loc="upper left", frameon=False, fontsize=9, labelcolor=INK)
    if order:
        # per module, now: each bar is 100% of the module's functions, split by tier (docs/modules.md)
        bx = fig.add_subplot(gs[1, :])
        PARTIAL, NONE = "#f6c7a9", "#e6e8eb"
        y = list(range(len(order)))[::-1]
        left = [0.0] * len(order)
        for key, color, label in (("exact", BLUE, "Byte-exact"), ("equiv", ORANGE, "Equivalent (compilable, not exact)"),
                                  ("part", PARTIAL, "Partial"), ("none", NONE, "No source yet")):
            w = [100.0 * mods[m][key] / mods[m]["n"] for m in order]
            bx.barh(y, w, left=left, color=color, height=0.7, label=label)
            left = [l + x for l, x in zip(left, w)]
        for yy, m in zip(y, order):
            c = mods[m]
            bx.text(101, yy, "%s functions, %.1f MB   exact %.0f%%, compilable %.0f%%" % (
                "{:,}".format(c["n"]), c["bytes"] / 2**20, 100.0 * c["exact"] / c["n"],
                100.0 * (c["exact"] + c["equiv"]) / c["n"]), va="center", fontsize=8, color=MUTED)
        bx.set_yticks(y)
        bx.set_yticklabels(order, fontsize=9, color=INK)
        bx.set_xlim(0, 140)
        bx.set_xticks([0, 25, 50, 75, 100])
        bx.xaxis.set_major_formatter(matplotlib.ticker.PercentFormatter(decimals=0))
        bx.set_title("By module, now", loc="left",
                     fontsize=11, color=INK)
        for sp in ("top", "right", "left"):
            bx.spines[sp].set_visible(False)
        bx.spines["bottom"].set_color(GRID)
        bx.tick_params(colors=MUTED, labelsize=9, length=0)
        bx.legend(loc="lower right", bbox_to_anchor=(1.0, 1.0), frameon=False, fontsize=8, labelcolor=INK, ncol=4)
    fig.suptitle("Spore decompilation progress (game functions; third-party libraries excluded)",
                 x=0.01, ha="left", fontsize=12, color=INK)
    fig.text(0.01, 0.01, "One point per committed docs/STATUS.md, one per day of --plot runs (latest run that day), plus now.\nEquivalent = complete compilable source, "
             "not yet byte-identical. Size shares only exist in later snapshots; the migrated line starts with Phase B "
             "(Oct 2026).", fontsize=8, color=MUTED)
    fig.tight_layout(rect=(0, 0.32 / H, 1, 1 - 0.23 / H))   # room for the two-line footnote and the title (inches / H)
    fig.savefig(path)
    print("wrote %s (%d snapshots)" % (os.path.relpath(path, ROOT), len(pts)))


def pctb_f(items):
    return 100.0 * sum(funcs[a]["size"] for a in items) / GB


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
