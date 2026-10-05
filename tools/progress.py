#!/usr/bin/env python3
"""Print Spore decompilation progress as terminal tables. Standalone: run from any shell.

  .venv/bin/python tools/progress.py            # coverage + components
  .venv/bin/python tools/progress.py --groups    # also live opencode wave groups
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
_slice_batches = collections.defaultdict(set)
for _bf in glob.glob(os.path.join(ROOT, "work/batches", "*.json")):
    _bn = os.path.basename(_bf)[:-5]
    for _rec in json.load(open(_bf)):
        _slice_batches[_rec["id"]].add(_bn)

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
comp = ns["comp_rows"]()  # markdown rows: | name | funcs | src (pct) | MB | src% |
crows = []
for line in comp:
    p = [x.strip() for x in line.strip().strip("|").split("|")]
    name, nfuncs, src, size, srcby = p[0], p[1], p[2], p[3], p[4]
    crows.append((name, src, size, srcby))
print()
print(table(["Component", "With compilable source", "Code size", "With source (by size)"],
            crows, aligns=["<", ">", ">", ">"]))

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

def model_table():
    ss = _svc_sessions()
    if ss is None:
        return "(opencode service unavailable - start it and re-run)"
    bm = collections.defaultdict(lambda: {"cost": 0.0, "inp": 0, "cr": 0, "out": 0, "rea": 0, "n": 0})
    for s in ss:
        t = s.get("title") or ""
        if not t.startswith("spore-"):
            continue
        batch = t.split("-")[1] if "-" in t else t
        m = s.get("model") or {}
        key = "%s/%s" % (m.get("providerID"), m.get("id"))
        tk = s.get("tokens") or {}; c = tk.get("cache") or {}
        a = bm[(batch, key)]
        a["cost"] += s.get("cost", 0) or 0; a["inp"] += tk.get("input", 0) or 0
        a["cr"] += c.get("read", 0) or 0; a["out"] += tk.get("output", 0) or 0
        a["rea"] += tk.get("reasoning", 0) or 0; a["n"] += 1
    dominant = {}
    for (batch, key), a in bm.items():
        if batch not in dominant or a["cost"] > bm[(batch, dominant[batch])]["cost"]:
            dominant[batch] = key

    def batch_exact(batch):
        bf = W("work/batches", batch + ".json"); n = 0
        exclude = CLAIM_EXCLUDE.get(batch, set())
        if os.path.exists(bf):
            for rec in json.load(open(bf)):
                if _slice_batches[rec["id"]] & exclude:
                    continue  # shared slice actually produced by another model's batch
                p = W("match/slices", rec["id"], "manifest.txt")
                if os.path.exists(p):
                    n += sum(1 for l in open(p) if l.strip() and not l.lstrip().startswith("#"))
        return n + EXTRA_EXACT.get(batch, 0)

    agg = collections.defaultdict(lambda: {"cost": 0.0, "inp": 0, "cr": 0, "out": 0, "rea": 0, "exact": 0, "batches": 0})
    for batch, key in dominant.items():
        a = bm[(batch, key)]; g = agg[key]
        for k in ("cost", "inp", "cr", "out", "rea"):
            g[k] += a[k]
        g["exact"] += batch_exact(batch); g["batches"] += 1
    rows = []
    for key, g in sorted(agg.items(), key=lambda x: -x[1]["cost"]):
        ex = g["exact"]; inp = g["inp"] + g["cr"]; gen = g["out"] + g["rea"]
        rows.append((key, g["batches"], human(ex), "$%.2f" % g["cost"],
                     "$%.4f" % (g["cost"] / ex) if ex else "-",
                     "%.2f" % (inp / ex / 1e6) if ex else "-",
                     "%.1f" % (gen / ex / 1e3) if ex else "-",
                     ("%.0f%%" % (100 * g["cr"] / inp)) if inp else "-"))
    if not rows:
        return "(no spore-* sessions found)"
    return table(["Model (provider/id)", "Batches", "Exact fns", "Cost", "$/fn",
                  "In-tok/fn (M)", "Gen-tok/fn (k)", "cache%"],
                 rows, aligns=["<", ">", ">", ">", ">", ">", ">", ">"])

print()
print("Per-model efficiency (byte-exact functions; costs are opencode estimates, not billed)")
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
    rows = []
    tot = collections.Counter()
    for gf in sorted(glob.glob(W("work/opencode/groups", "*.json"))):
        g = json.load(open(gf)); name = os.path.basename(gf)[:-5]
        batch = json.load(open(W("work/batches", g["batch"] + ".json")))
        account = exact = tot_funcs = 0; cost = 0.0; act = 0
        for k, sid in g.get("sessions", {}).items():
            if sid in sess_cost: cost += sess_cost[sid]
            if sid in active: act += 1
        for a, b in g["ranges"]:
            for i in range(a, b + 1):
                sid = batch[i]["id"]; tot_funcs += len(batch[i]["vas"])
                for f, isok in (("manifest.txt", 1), ("nonmatching.txt", 0), ("partial.txt", 0)):
                    p = W("match/slices", sid, f)
                    if os.path.exists(p):
                        n = sum(1 for l in open(p) if l.strip() and not l.lstrip().startswith("#"))
                        account += n; exact += n * isok
        launched = len(g.get("sessions", {})); nranges = len(g["ranges"])
        if account == 0 and launched == 0:
            continue
        rows.append((name, "%d/%d" % (account, tot_funcs), str(exact), "$%.2f" % cost, str(act), "%d/%d" % (launched, nranges)))
        tot["account"] += account; tot["tot"] += tot_funcs; tot["exact"] += exact; tot["cost"] += cost; tot["active"] += act
    if not rows:
        return None
    rows.append(("TOTAL", "%d/%d" % (tot["account"], tot["tot"]), str(tot["exact"]), "$%.2f" % tot["cost"], str(tot["active"]), ""))
    return table(["Group", "Accounted", "Exact", "Cost", "Active", "Launched"], rows,
                 aligns=["<", ">", ">", ">", ">", ">"])

if "--groups" in sys.argv:
    t = groups_table()
    print()
    if t: print(t)
    else: print("(no live wave groups found)")

print()
print("Generated by tools/progress.py (coverage logic shared with tools/status.py).")
