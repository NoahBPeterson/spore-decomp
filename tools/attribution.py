#!/usr/bin/env python3
"""attribution.py [--refresh] — which commit (and so which wave) first produced each function counted as byte-exact
or equivalent today.

One `git log --reverse -p` pass over every bookkeeping file (slice and src/game manifest.txt / nonmatching.txt,
match/manifest.txt, match/synth/*.manifest, match/clones.txt) records, per VA, the first commit that added a
manifest row (byte-exact) and the first that added a nonmatching row (equivalent). Migration and class-key commits
rewrite rows later, so "first added" credits the wave that did the work, not the one that moved it. The commit's
subject tag ("gold6: ...", "bfs2: ...") names the wave; tools/progress.py maps waves to models.

Output (cached, rebuilt when HEAD moves or with --refresh): work/attribution.json =
  {"head": sha, "exact": {va: [commit, tag, slice]}, "equiv": {va: [commit, tag, slice]}} (slice "" outside match/slices)
Run directly it prints functions per tag for today's exact and equivalent sets.
"""
import collections, json, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUT = os.path.join(ROOT, "work", "attribution.json")
PATHS = ["match/slices/*/manifest.txt", "match/slices/*/nonmatching.txt", "src/game/**/manifest.txt",
         "src/game/**/nonmatching.txt", "match/manifest.txt", "match/synth/*.manifest", "match/clones.txt"]
HEX = re.compile(r"(?:0x)?([0-9a-fA-F]{5,8})$")


def tag_of(subject):
    m = re.match(r"([A-Za-z0-9_.\-]+):", subject)
    return m.group(1) if m else subject.split()[0] if subject.split() else "?"


def build():
    head = subprocess.run(["git", "-C", ROOT, "rev-parse", "HEAD"], capture_output=True, text=True).stdout.strip()
    try:
        old = json.load(open(OUT))
        if old.get("head") == head:
            return old
    except (OSError, ValueError):
        pass
    p = subprocess.Popen(["git", "-C", ROOT, "log", "--reverse", "-p", "--no-renames", "-U0", "--format=@@C %h %s",
                          "--"] + [":(glob)" + x for x in PATHS], stdout=subprocess.PIPE, text=True, errors="replace")
    exact, equiv = {}, {}
    commit = tag = None
    kind = None
    slice_id = ""
    for line in p.stdout:
        if line.startswith("@@C "):
            _, commit, subj = (line.rstrip("\n").split(" ", 2) + [""])[:3]
            tag = tag_of(subj)
            continue
        if line.startswith("+++ "):
            f = line[6:].strip() if line.startswith("+++ b/") else ""
            m_sl = re.match(r"match/slices/(s[0-9a-f]{8})/", f)
            slice_id = m_sl.group(1) if m_sl else ""
            kind = ("exact_va3" if f.endswith(("manifest.txt", ".manifest", "clones.txt")) else
                    "equiv_va1" if f.endswith("nonmatching.txt") else None)
            if f.startswith("match/synth/"):
                kind = "synth"
            elif f.endswith("clones.txt"):
                kind = "clones"
            continue
        if not line.startswith("+") or line.startswith("+++") or kind is None:
            continue
        parts = line[1:].split("#", 1)[0].split()
        if kind in ("exact_va3", "synth", "clones"):
            if len(parts) < 3:
                continue
            m = HEX.match(parts[2])
            if m:
                va = m.group(1).lower().zfill(8)
                exact.setdefault(va, [commit, "synth" if kind == "synth" else "clones" if kind == "clones" else tag, slice_id])
        else:
            if not parts:
                continue
            m = HEX.match(parts[0])
            if m:
                equiv.setdefault(m.group(1).lower().zfill(8), [commit, tag, slice_id])
    p.wait()
    data = {"head": head, "exact": exact, "equiv": equiv}
    tmp = OUT + ".tmp"
    json.dump(data, open(tmp, "w"))
    os.replace(tmp, OUT)
    return data


def current_sets():
    """Today's exact and equivalent VA sets, as tools/status.py counts them (8-hex strings)."""
    import runpy, io, contextlib
    with contextlib.redirect_stdout(io.StringIO()):
        ns = runpy.run_path(os.path.join(ROOT, "tools", "status.py"))
    exact = {"%08x" % v for v in ns["exact"] | ns.get("synth", set()) | ns.get("clones", set())}
    equiv = {"%08x" % v for v in ns["nonmatching"]} - exact
    return exact, equiv


if __name__ == "__main__":
    if "--refresh" in sys.argv and os.path.exists(OUT):
        os.remove(OUT)
    d = build()
    ex, eq = current_sets()
    for name, cur, src in (("byte-exact", ex, d["exact"]), ("equivalent", eq, d["equiv"])):
        c = collections.Counter(src[v][1] if v in src else "(no commit adds a row)" for v in cur)
        print("%s: %d functions" % (name, len(cur)))
        for t, n in c.most_common():
            print("  %7d  %s" % (n, t))
