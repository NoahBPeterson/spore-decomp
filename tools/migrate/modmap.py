#!/usr/bin/env python3
"""modmap: assign every retail function to the dev-build object file it was compiled in.

Phase B step 1 of docs/migration.md. Writes work/migrate/modmap.json:

  { "functions": { "<va hex>": {"module": "SPEngine/SPPropertyList.obj", "how": "anchor",
                                "confidence": 1.0, "name": "SP::cPropertyList::GetProperty",
                                "size": 123, "dev": "<dev va hex>" }, ... },
    "runs":      [ {"module": ..., "lo": "<va hex>", "hi": "<va hex>", "n": 57, "size": 9120,
                    "anchors": 12}, ... ],          # retail address order
    "gaps":      [ {"lo": ..., "hi": ..., "n": ..., "size": ..., "before": module, "after": module} ],
    "modules":   { "<module>": {"n": ..., "size": ..., "anchors": ..., "runs": ...}, ... },
    "conflicts": [ {"va": ..., "kept": ..., "kept_how": ..., "other": ..., "other_how": ...}, ... ],
    "stats":     { ... the metric printed at the end ... } }

Signals, each applied only to still-unassigned functions, in this order:

  anchor     symbols/pdb_names.json gives the retail function's dev counterpart (xmatch,
             docs/xmatch.md); work/devbuild/symbols.json gives that dev function's object file.
             A name present in more than one dev object is a COMDAT (template instantiation,
             inline member): the retail linker may have kept another copy, so those are
             `anchor-comdat` (confidence 0.5) and do not seed interpolation.  A lone anchor of
             module X between two anchors of module M is `anchor-sandwiched` (0.6): usually an
             inline member or instantiation the dev linker kept in X, or an xmatch error; M's
             interpolation runs across it and overrides it (`interp+override`, listed under
             "conflicts").
  interp     retail .text is module-major and link order is preserved inside an object, so
             every function between two consecutive unique anchors of the same module belongs
             to that module, provided the two dev counterparts are in ascending order too (no
             object is emitted in reverse: no chain of three or more same-module anchor pairs
             descends throughout).  Pairs out of order (a function moved within its file since
             2008, or a misnamed anchor) are not spanned; later signals may still claim them.
             The retail function count in the gap is also checked against the dev function
             count between the two counterparts; implausibly wide gaps are assigned at lower
             confidence (`interp-wide`, 0.6) so later signals can override them.
  then the optional signal modules tools/migrate/sig_<name>.py (SIGNALS below), each exposing
  `apply(ctx)`; see Ctx for what they get.  Missing modules are skipped.

Module keys are `<dir>/<obj>` (the last two path components of the PDB module path, e.g.
`UTFSpore_Win32/DatabasePackedFile.obj`, `Native Release/rwarena.obj`, `hkbase/hkClass.obj`).

usage: modmap.py [--out work/migrate/modmap.json] [--module SUBSTR] [--quiet]
                 [--signals a,b,c] [--holdout 0.2 [--seed N]]
  --module SUBSTR   after building, list the functions of every module whose key contains
                    SUBSTR (retail address order, with the signal and the slice status)
  --signals LIST    run only these signals (names as in SIGNALS; `anchor` is always first)
  --holdout F       precision estimate: hide a fraction F of the unique anchors, run the signals,
                    and report how many hidden anchors land in their true module (nothing written)
"""
import argparse, bisect, collections, glob, importlib, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
W = lambda *p: os.path.join(ROOT, *p)
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

# Signal order.  The first two are built in; the rest are tools/migrate/sig_<name>.py modules.
SIGNALS = ["anchor", "interp", "vtable", "callgraph", "gapsplit", "inst"]

# Gap plausibility for `interp`.  Retail (2024, VC9 LTCG) and dev (2008, VC7.1) differ in
# inlining, so counts, not sizes, are compared; a retail gap holding more than WIDE_FACTOR times
# the dev count (plus WIDE_SLACK) is `interp-wide`.
WIDE_FACTOR = 2.0
WIDE_SLACK = 4


def module_key(path):
    parts = re.split(r"[\\/]+", path.strip())
    parts = [p for p in parts if p and p != "."]
    return "/".join(parts[-2:]) if len(parts) >= 2 else parts[-1]


class Ctx:
    """Everything a signal needs.

    retail        {va: size} for every retail function (work/xmatch/retail.json, 90,467)
    order         sorted retail VAs
    retail_feat   the raw retail.json rows: {va hex: {size, name, strs, imps, consts, vals,
                  calls: [callee va hex, ...]}} (direct calls only)
    dev           {dev va: (module, name, size, is_local)} for the 145,306 dev functions
    dev_by_module {module: sorted dev VAs}
    dev_name_mods {dev name: set(modules)}
    anchors       {retail va: {module, dev, name, how, comdat, sandwiched?}} (hidden ones removed
                  under --holdout)
    assign        {retail va: {module, how, confidence, name, dev}} -- the result so far
    conflicts     list of disagreements recorded by set()
    """

    def __init__(self):
        self.retail_feat = json.load(open(W("work/xmatch/retail.json")))
        self.retail = {int(k, 16): v["size"] for k, v in self.retail_feat.items()}
        self.order = sorted(self.retail)
        s = json.load(open(W("work/devbuild/symbols.json")))
        self.dev = {}
        self.dev_name_mods = collections.defaultdict(set)
        self.dev_by_module = collections.defaultdict(list)
        for f in s["functions"]:
            m = module_key(f["module"])
            self.dev[f["va"]] = (m, f["name"], f["size"], bool(f.get("local")))
            self.dev_name_mods[f["name"]].add(m)
            self.dev_by_module[m].append(f["va"])
        for v in self.dev_by_module.values():
            v.sort()
        self.anchors = {}
        for va_hex, e in json.load(open(W("symbols/pdb_names.json"))).items():
            dva = int(e["dev"], 16)
            if dva not in self.dev:
                continue
            m, dname, _sz, _loc = self.dev[dva]
            va = int(va_hex, 16)
            if va in self.retail:
                self.anchors[va] = dict(module=m, dev=dva, name=e.get("name") or dname, how=e.get("how"),
                                        comdat=len(self.dev_name_mods[dname]) > 1)
        self.assign = {}
        self.conflicts = []
        self.hidden = {}

    # -- helpers for signals ---------------------------------------------------------------
    def set(self, va, module, how, confidence, name=None, dev=None):
        """Assign `va`; a different existing assignment is kept unless its confidence is lower,
        and either way the disagreement is recorded."""
        prev = self.assign.get(va)
        if prev is None:
            self.assign[va] = dict(module=module, how=how, confidence=confidence, name=name, dev=dev)
            return True
        if prev["module"] == module:
            return False
        self.conflicts.append(dict(va="%08x" % va, name=prev.get("name"), kept=prev["module"],
                                   kept_how=prev["how"], other=module, other_how=how))
        if prev["confidence"] < confidence:
            self.assign[va] = dict(module=module, how=how + "+override", confidence=confidence,
                                   name=prev.get("name") or name, dev=prev.get("dev") or dev)
            return True
        return False

    def unassigned(self):
        return [va for va in self.order if va not in self.assign]

    def module_of(self, va):
        e = self.assign.get(va)
        return e["module"] if e else None

    def between(self, a, b):
        """Retail VAs strictly between a and b."""
        return self.order[bisect.bisect_right(self.order, a):bisect.bisect_left(self.order, b)]

    def dev_count_between(self, module, a, b):
        vas = self.dev_by_module[module]
        lo, hi = min(a, b), max(a, b)
        return bisect.bisect_left(vas, hi) - bisect.bisect_right(vas, lo)

    def runs(self):
        """Maximal address-ordered stretches assigned to one module (list of dicts with int VAs)."""
        runs = []
        prev_idx = None
        for idx, va in enumerate(self.order):
            e = self.assign.get(va)
            if e is None:
                continue
            if runs and runs[-1]["module"] == e["module"] and prev_idx == idx - 1:
                r = runs[-1]
            else:
                runs.append(dict(module=e["module"], lo=va, hi=va, n=0, size=0, anchors=0))
                r = runs[-1]
            r["hi"] = va
            r["n"] += 1
            r["size"] += self.retail[va]
            r["anchors"] += e["how"] in ("anchor", "anchor+override")
            prev_idx = idx
        return runs

    def gaps(self):
        """Unassigned stretches between runs (list of dicts with int VAs and the flanking modules)."""
        gaps = []
        cur = None
        last_mod = None
        for va in self.order:
            if va in self.assign:
                if cur:
                    cur["after"] = self.assign[va]["module"]
                    gaps.append(cur)
                    cur = None
                last_mod = self.assign[va]["module"]
                continue
            if cur is None:
                cur = dict(lo=va, hi=va, n=0, size=0, before=last_mod, after=None, vas=[])
            cur["hi"] = va
            cur["n"] += 1
            cur["size"] += self.retail[va]
            cur["vas"].append(va)
        if cur:
            gaps.append(cur)
        return gaps


# ---- built-in signals ----------------------------------------------------------------------
def sig_anchor(ctx):
    uniq_all = sorted(va for va, a in ctx.anchors.items() if not a["comdat"])
    for i in range(1, len(uniq_all) - 1):
        p, c, n = ctx.anchors[uniq_all[i - 1]], ctx.anchors[uniq_all[i]], ctx.anchors[uniq_all[i + 1]]
        if p["module"] == n["module"] != c["module"]:
            c["sandwiched"] = True
    for va, a in ctx.anchors.items():
        if a.get("sandwiched"):
            ctx.set(va, a["module"], "anchor-sandwiched", 0.6, a["name"], a["dev"])
        elif a["comdat"]:
            ctx.set(va, a["module"], "anchor-comdat", 0.5, a["name"], a["dev"])
        else:
            ctx.set(va, a["module"], "anchor", 1.0, a["name"], a["dev"])


def sig_interp(ctx):
    uniq = sorted(va for va, a in ctx.anchors.items() if not a["comdat"] and not a.get("sandwiched"))
    pairs = collections.Counter()
    # Chains: maximal stretches of consecutive unique anchors in one module.  Link order inside
    # an object is preserved and ascending in both builds: no chain of three or more pairs
    # descends throughout; the five chains with a descending majority are scrambled (e.g. 4
    # ascending pairs against 5 in a ten-anchor chain), i.e. files reorganised since 2008 or
    # misnamed anchors.  So a pair is spanned only when its dev counterparts ascend as well.
    chains = []
    for i in range(len(uniq)):
        if chains and ctx.anchors[chains[-1][-1]]["module"] == ctx.anchors[uniq[i]]["module"]:
            chains[-1].append(uniq[i])
        else:
            chains.append([uniq[i]])
    chain_stats = collections.Counter()
    for chain in chains:
        signs = [ctx.anchors[chain[k + 1]]["dev"] - ctx.anchors[chain[k]]["dev"] for k in range(len(chain) - 1)]
        chain_stats["single-anchor" if not signs else ("in-order" if all(d > 0 for d in signs) else "scrambled")] += 1
        for k in range(len(chain) - 1):
            a, b = chain[k], chain[k + 1]
            A, B = ctx.anchors[a], ctx.anchors[b]
            between = ctx.between(a, b)
            if not between:
                pairs["adjacent"] += 1
                continue
            if signs[k] < 0:
                pairs["dev-order-against"] += 1
                continue
            pairs["spanned"] += 1
            ndev = ctx.dev_count_between(A["module"], A["dev"], B["dev"])
            wide = len(between) > WIDE_FACTOR * ndev + WIDE_SLACK
            how, conf = ("interp-wide", 0.6) if wide else ("interp", 0.9)
            pairs[how] += 1
            for va in between:
                ctx.set(va, A["module"], how, conf)
    pairs["different-module"] = len(chains) - 1
    ctx.pair_stats = dict(pairs)
    ctx.chain_stats = dict(chain_stats)


BUILTIN = {"anchor": sig_anchor, "interp": sig_interp}


def run_signals(ctx, names, quiet=False):
    for name in names:
        if name in BUILTIN:
            fn = BUILTIN[name]
        else:
            try:
                fn = importlib.import_module("sig_" + name).apply
            except ImportError:
                continue
        before = len(ctx.assign)
        fn(ctx)
        if not quiet:
            print("signal %-10s +%d" % (name, len(ctx.assign) - before))


def build(quiet=False, holdout=0.0, seed=1, signals=None):
    ctx = Ctx()
    if holdout:
        import random
        rnd = random.Random(seed)
        for va in sorted(ctx.anchors):
            if not ctx.anchors[va]["comdat"] and rnd.random() < holdout:
                ctx.hidden[va] = ctx.anchors[va]
        for va in ctx.hidden:
            del ctx.anchors[va]
    names = list(signals or SIGNALS)
    if names[0] != "anchor":
        names.insert(0, "anchor")
    run_signals(ctx, names, quiet)
    apply_overrides(ctx, quiet)
    return ctx, summarize(ctx)


OVERRIDES = W("tools", "migrate", "modmap_overrides.json")


def apply_overrides(ctx, quiet=False):
    """Hand-curated corrections after the signals (tools/migrate/modmap_overrides.json), each with
    evidence. `rename_in_range`: functions in [lo, hi] assigned to a module matching `module`
    (prefix) are re-labelled `to` (a retail-only object the dev PDB does not have, e.g. the second
    DatabasePackedFile family near 0x6bb000). The `how` keeps its signal plus "+override"."""
    if not os.path.exists(OVERRIDES):
        return
    ov = json.load(open(OVERRIDES))
    for e in ov.get("rename_in_range", []):
        lo, hi, n = int(e["lo"], 16), int(e["hi"], 16), 0
        for va, a in ctx.assign.items():
            if lo <= va <= hi and a["module"].startswith(e["module"]):
                a["module"] = e["to"]
                if not a["how"].endswith("+override"):
                    a["how"] += "+override"
                n += 1
        if not quiet:
            print("override: %s -> %s in %08x-%08x: %d functions" % (e["module"], e["to"], lo, hi, n))


def summarize(ctx):
    retail, assign = ctx.retail, ctx.assign
    runs = ctx.runs()
    gaps = ctx.gaps()
    total_n, total_size = len(retail), sum(retail.values())
    by_how = collections.defaultdict(lambda: dict(n=0, size=0))
    modules = collections.defaultdict(lambda: dict(n=0, size=0, anchors=0, runs=0))
    dirs = collections.Counter()
    for va, e in assign.items():
        by_how[e["how"]]["n"] += 1
        by_how[e["how"]]["size"] += retail[va]
        m = modules[e["module"]]
        m["n"] += 1
        m["size"] += retail[va]
        m["anchors"] += e["how"] in ("anchor", "anchor+override")
        dirs[e["module"].split("/")[0]] += retail[va]
    for r in runs:
        modules[r["module"]]["runs"] += 1
    assigned_size = sum(retail[va] for va in assign)
    stats = dict(
        retail_functions=total_n, retail_size=total_size,
        anchors_total=len(ctx.anchors) + len(ctx.hidden),
        anchors_unique=sum(1 for a in ctx.anchors.values() if not a["comdat"] and not a.get("sandwiched")),
        anchors_comdat=sum(1 for a in ctx.anchors.values() if a["comdat"]),
        anchors_sandwiched=sum(1 for a in ctx.anchors.values() if a.get("sandwiched")),
        assigned=len(assign), assigned_size=assigned_size,
        assigned_pct=round(100.0 * len(assign) / total_n, 1),
        assigned_size_pct=round(100.0 * assigned_size / total_size, 1),
        by_how={k: by_how[k] for k in sorted(by_how)},
        pairs=getattr(ctx, "pair_stats", {}), chains=getattr(ctx, "chain_stats", {}), conflicts=len(ctx.conflicts),
        modules=len(modules), runs=len(runs),
        gaps=len(gaps), gap_functions=sum(g["n"] for g in gaps), gap_size=sum(g["size"] for g in gaps),
        largest_gaps=[dict(lo="%08x" % g["lo"], hi="%08x" % g["hi"], n=g["n"], size=g["size"],
                           before=g["before"], after=g["after"])
                      for g in sorted(gaps, key=lambda g: -g["size"])[:10]],
        by_dir_size={k: v for k, v in dirs.most_common()},
    )
    out = dict(
        functions={"%08x" % va: dict(module=e["module"], how=e["how"], confidence=e["confidence"],
                                     name=e.get("name"), size=retail[va],
                                     dev=("%08x" % e["dev"]) if e.get("dev") else None)
                   for va, e in sorted(assign.items())},
        runs=[dict(module=r["module"], lo="%08x" % r["lo"], hi="%08x" % r["hi"], n=r["n"],
                   size=r["size"], anchors=r["anchors"]) for r in runs],
        gaps=[dict(lo="%08x" % g["lo"], hi="%08x" % g["hi"], n=g["n"], size=g["size"],
                   before=g["before"], after=g["after"]) for g in gaps],
        modules={k: v for k, v in sorted(modules.items(), key=lambda kv: -kv[1]["size"])},
        conflicts=ctx.conflicts,
        stats=stats,
    )
    if ctx.hidden:
        got = collections.Counter()
        for va, a in ctx.hidden.items():
            e = assign.get(va)
            if e is None:
                got[("missed", "-")] += 1
            else:
                got[("right" if e["module"] == a["module"] else "wrong", e["how"])] += 1
        n = len(ctx.hidden)
        rec = sum(v for (r, _h), v in got.items() if r != "missed")
        right = sum(v for (r, _h), v in got.items() if r == "right")
        per_how = {}
        for (r, h), v in got.items():
            if r != "missed":
                d = per_how.setdefault(h, dict(right=0, wrong=0))
                d[r] += v
        for h, d in per_how.items():
            d["precision"] = round(100.0 * d["right"] / max(d["right"] + d["wrong"], 1), 1)
        out["holdout"] = dict(hidden=n, recovered=rec, right=right,
                              precision=round(100.0 * right / max(rec, 1), 1), recall=round(100.0 * rec / n, 1),
                              missed=n - rec, by_how=per_how)
    return out


def report(out):
    s = out["stats"]
    print("retail functions %d (%.2f MB); anchors %d (unique %d, comdat %d, sandwiched %d)" % (
        s["retail_functions"], s["retail_size"] / 1e6, s["anchors_total"], s["anchors_unique"],
        s["anchors_comdat"], s["anchors_sandwiched"]))
    print("assigned %d functions = %.1f%% by count, %.1f%% by size; %d modules in %d runs; %d conflicts" % (
        s["assigned"], s["assigned_pct"], s["assigned_size_pct"], s["modules"], s["runs"], s["conflicts"]))
    for how, v in s["by_how"].items():
        print("  %-24s %6d fn  %8.2f KB" % (how, v["n"], v["size"] / 1e3))
    if s["pairs"]:
        print("anchor chains:", ", ".join("%s %d" % kv for kv in sorted(s["chains"].items())),
              "; pairs:", ", ".join("%s %d" % kv for kv in sorted(s["pairs"].items())))
    print("unassigned: %d gaps, %d functions, %.2f MB; largest:" % (s["gaps"], s["gap_functions"], s["gap_size"] / 1e6))
    for g in s["largest_gaps"][:5]:
        print("  %s-%s  %5d fn  %7.1f KB  between %s | %s" % (g["lo"], g["hi"], g["n"], g["size"] / 1e3,
                                                             g["before"], g["after"]))
    if out.get("holdout"):
        h = out["holdout"]
        print("hold-out: %d anchors hidden, %d recovered (recall %.1f%%), %d right (precision %.1f%%)" % (
            h["hidden"], h["recovered"], h["recall"], h["right"], h["precision"]))
        for how, d in sorted(h["by_how"].items()):
            print("  %-24s right %5d  wrong %4d  precision %5.1f%%" % (how, d["right"], d["wrong"], d["precision"]))
    print("assigned size by directory:")
    for d, sz in list(s["by_dir_size"].items())[:12]:
        print("  %-18s %8.1f KB" % (d, sz / 1e3))


def slice_status():
    """va -> 'exact' | 'equiv' | 'partial' from the slice bookkeeping files."""
    st = {}
    for kind, pat, col in (("partial", "match/slices/*/partial.txt", 0), ("equiv", "match/slices/*/nonmatching.txt", 0),
                           ("exact", "match/slices/*/manifest.txt", 2)):
        for f in glob.glob(W(pat)):
            for line in open(f):
                p = line.split("#", 1)[0].split()
                if len(p) <= col:
                    continue
                try:
                    va = int(p[col], 16)
                except ValueError:
                    continue
                st[va] = kind   # later kinds (exact) win
    return st


def list_module(out, substr):
    st = slice_status()
    mods = [m for m in out["modules"] if substr.lower() in m.lower()]
    for m in mods:
        rows = [(int(va, 16), e) for va, e in out["functions"].items() if e["module"] == m]
        rows.sort()
        c = collections.Counter(st.get(va, "none") for va, _ in rows)
        print("== %s: %d functions, %d bytes, %d runs; source: %s" % (
            m, len(rows), sum(e["size"] for _, e in rows), out["modules"][m]["runs"],
            ", ".join("%s %d" % kv for kv in sorted(c.items()))))
        for va, e in rows:
            print("  %08x %5d %-18s %-8s %s" % (va, e["size"], e["how"], st.get(va, "-"), e["name"] or ""))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--out", default=W("work/migrate/modmap.json"))
    ap.add_argument("--module", help="list the functions of modules whose key contains this substring")
    ap.add_argument("--quiet", action="store_true")
    ap.add_argument("--signals", help="comma-separated subset of %s" % ",".join(SIGNALS))
    ap.add_argument("--holdout", type=float, default=0.0,
                    help="hide this fraction of the unique anchors and report how the signals re-find them")
    ap.add_argument("--seed", type=int, default=1)
    a = ap.parse_args()
    signals = a.signals.split(",") if a.signals else None
    _ctx, out = build(quiet=a.quiet, holdout=a.holdout, seed=a.seed, signals=signals)
    if not a.quiet:
        report(out)
    if a.holdout:
        return
    from headers import dump_json_atomic   # concurrent rewrite.py runs read this file
    dump_json_atomic(out, a.out, indent=0)
    if not a.quiet:
        print("wrote", os.path.relpath(a.out, ROOT))
    if a.module:
        list_module(out, a.module)


if __name__ == "__main__":
    main()
