#!/usr/bin/env python3
"""Shape-only functions (#458, decision 2026-11-19): generated matches whose borrowed source names other functions'
targets. They are not counted as byte-exact; match/shape_only.txt lists them as open work.

A clone (match/clones.txt) compiles a twin's source: the bytes match because addresses are masked. When the clone's
retail addresses are the twin's (targets.same_targets) the source is honest for both and the row stays. When they
differ (the clone calls other functions or reads other globals: a template instance for another type, a sibling of
the same shape) the source does not describe it, and the row moves to match/shape_only.txt. A generated synth row
(match/synth/*.manifest) moves when the target audit finds a name in it pointing elsewhere (--synth-audit).

match/shape_only.txt is not a manifest: nothing reads its rows as matches. Each line:
    <va>  <twin va or ->  <source the row borrowed>  <symbol>  # why
tools/contrib/task.py lists these functions as open work, naming the twin to start from. Writing real source for one
(a manifest row of a slice or a src/game module) makes it byte-exact and new (tools/site/build.py credits it); this
script then drops its shape_only.txt line.

usage: shape_only.py [--synth-audit LOG]   (rewrites match/clones.txt, match/synth/*.manifest, match/shape_only.txt)
       shape_only.py --check               (exit 1 if a clones.txt row should move; changes nothing)
"""
import argparse, glob, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools", "ci"))
import targets as TG     # noqa: E402

CLONES = os.path.join(ROOT, "match", "clones.txt")
LIST = os.path.join(ROOT, "match", "shape_only.txt")
HEADER = ("# Shape-only functions: generated matches whose borrowed source names other functions' targets (#458).\n"
          "# Not byte-exact, not counted; open work (tools/contrib/task.py). Written by tools/ci/shape_only.py.\n"
          "# va  twin  borrowed-source  symbol  # why\n")
VA = re.compile(r"[0-9a-fA-F]{8}")


def fingerprints():
    with open(os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl"), "rt") as f:
        return {int(d["va"], 16): d for d in map(json.loads, f)}


def row(line):
    """(src, sym, va) of a manifest-format line, or None"""
    p = line.split("#", 1)[0].split()
    return (p[0], p[1], int(p[2], 16)) if len(p) >= 3 and VA.fullmatch(p[2]) else None


def written_vas():
    """functions with a manifest row of written source: a slice, a src/game module, match/manifest.txt"""
    out = set()
    for m in glob.glob(os.path.join(ROOT, "match", "slices", "*", "manifest.txt")) + [os.path.join(ROOT, "match", "manifest.txt")] + \
            glob.glob(os.path.join(ROOT, "src", "game", "**", "manifest.txt"), recursive=True):
        if os.path.exists(m):
            out |= {r[2] for r in map(row, open(m, errors="replace")) if r}
    return out


def read_list():
    """{va: line} of match/shape_only.txt"""
    if not os.path.exists(LIST):
        return {}
    return {int(l.split()[0], 16): l for l in open(LIST) if l.strip() and not l.startswith("#")}


def listed():
    """the shape-only functions (for counting: tools/site/build.py, tools/contrib/task.py)"""
    return set(read_list())


def split_clones(fps, keep_out):
    """(clones.txt lines to keep, {va: shape_only line}); rows for functions already matched by written source are
    dropped (they add nothing)"""
    kept, moved = [], {}
    for line in open(CLONES):
        r = row(line)
        if not r:
            kept.append(line)
            continue
        src, sym, va = r
        m = re.search(r"# clone of ([0-9a-f]{8})", line)
        if va in keep_out:
            continue
        twin = int(m.group(1), 16) if m else None
        if twin is not None and TG.same_targets(fps, twin, va):
            kept.append(line)
        else:
            moved[va] = "%08x  %s  %s  %s  # clone: %s\n" % (
                va, "%08x" % twin if twin is not None else "-", src, sym,
                "its addresses differ from the twin's" if twin is not None else "no twin recorded")
    return kept, moved


def synth_bad(log):
    """synth VAs with a disagreeing relocation in a target_audit.py log run over the synth manifests only"""
    return {int(m.group(1), 16) for m in (re.match(r"([0-9a-f]{8}) \+\d+\s+disagree\b", l) for l in open(log)) if m}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--synth-audit", help="target_audit.py output over match/synth/*.manifest")
    ap.add_argument("--check", action="store_true")
    a = ap.parse_args()
    fps, written = fingerprints(), written_vas()
    old = {va: l for va, l in read_list().items() if va not in written}   # written source replaced it: drop
    moved = {}
    if a.synth_audit:
        bad = synth_bad(a.synth_audit)
        for m in sorted(glob.glob(os.path.join(ROOT, "match", "synth", "*.manifest"))):
            lines, keep = open(m).readlines(), []
            for line in lines:
                r = row(line)
                if r and r[2] in bad and r[2] not in written:
                    moved[r[2]] = "%08x  -  %s  %s  # synth (%s): a name points elsewhere than retail\n" % (
                        r[2], r[0], r[1], os.path.basename(m)[:-len(".manifest")])
                else:
                    keep.append(line)
            if len(keep) != len(lines) and not a.check:
                open(m, "w").write("".join(keep))
    synth = set()
    for m in glob.glob(os.path.join(ROOT, "match", "synth", "*.manifest")):
        synth |= {r[2] for r in map(row, open(m)) if r}
    kept, cm = split_clones(fps, written | (synth - set(moved)))
    moved.update(cm)
    for r in filter(None, map(row, kept)):     # an honest clone still matches a function whose synth row moved
        moved.pop(r[2], None)
    if a.check:
        print("%d clones.txt rows would move to shape_only.txt" % len(cm))
        return 1 if cm else 0
    open(CLONES, "w").write("".join(kept))
    allrows = {**old, **moved}
    open(LIST, "w").write(HEADER + "".join(allrows[v] for v in sorted(allrows)))
    print("clones.txt: %d rows kept; shape_only.txt: %d functions (%d new this run)"
          % (sum(1 for l in kept if row(l)), len(allrows), len(set(moved) - set(old))))
    return 0


if __name__ == "__main__":
    sys.exit(main())
