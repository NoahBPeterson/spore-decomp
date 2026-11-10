#!/usr/bin/env python3
"""task: everything you need to work on one function (a "context pack", printed).

  .venv/bin/python tools/contrib/task.py 0x00529690

Prints where the function lives (its source file and object), its status (byte-exact, complete but not yet byte-exact,
partial, or no source yet), the compiler flags it is checked with, its retail size, the headers its file includes, the
current source of the function, and what to do next.  Needs only the repo: no game files.

  --list [--max-size N] [--by tries|diff|size] [--seed TEXT] [--show-claimed]
      open work: functions with source that is not byte-exact yet, or no source yet. Default order: fewest tries
      first (quick wins nobody has fought with yet), then by size band (up to 16, 32, 64, 128, 256... bytes), and
      within a band in an order of your own: a shuffle seeded by your git identity (or --seed), so contributors
      starting at the same time do not all pick the same functions. --by diff: fewest differing bytes first;
      --by size: smallest first.
      Functions in an open pull request are hidden (claims.txt, below); --show-claimed lists them, marked.

Claims: https://raw.githubusercontent.com/NoahBPeterson/spore-decomp/claims/claims.txt lists every function an open
pull request works on (refreshed when a pull request changes, and every 30 minutes). Open a draft pull request early,
titled with the address, and your function drops out of everybody else's list. A claim with no update for 7 days is
stale and shows again.

"Tries" is how many times the function's nonmatching.txt note has been written or rewritten, counted from git history
(each failed attempt updates the note). It is an estimate: bulk tooling edits count too. A shallow clone has no
history, so tries are unknown and the list falls back to size order.
"""
import argparse, collections, datetime, glob, gzip, hashlib, json, os, re, subprocess, sys, time, urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path[:0] = [os.path.join(ROOT, "tools", "difftest"), os.path.join(ROOT, "tools", "matching"),
                os.path.join(ROOT, "tools", "ci")]
import slice as S       # noqa: E402

FP = os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl.gz")
_fps = None


def fingerprints():
    global _fps
    if _fps is None:
        _fps = {int(d["va"], 16): d for d in map(json.loads, gzip.open(FP, "rt"))}
    return _fps


def fingerprint(va):
    """One function's fingerprint without decoding all 90,000 (check.py and task.py <va> call this once per run)."""
    if _fps is not None:
        return _fps.get(va)
    key = '{"va":"%08x"' % va
    for line in gzip.open(FP, "rt"):
        if line.startswith(key):
            return json.loads(line)
    return None


def sources():
    out = []
    for d in (os.path.join(ROOT, "src", "game"), os.path.join(ROOT, "match", "slices")):
        out += [f for f in glob.glob(os.path.join(d, "**", "*.c*"), recursive=True) if os.path.isfile(f)]
    return out


def locate(va):
    """(source file, ident) carrying the line-start marker `// @ 0x<va>`; src/game first"""
    pat = re.compile(r"(?mi)^//\s*@\s*0x0*%x\b" % va)
    for f in sources():
        if pat.search(open(f, errors="replace").read()):
            rel = os.path.relpath(f, ROOT)
            if rel.startswith("src" + os.sep):
                stem = os.path.splitext(os.path.basename(f))[0]
                d = os.path.basename(os.path.dirname(f))
                return f, (stem if S.module_dir(stem) else "%s/%s" % (d, stem))
            return f, rel.split(os.sep)[2]
    # no marker: a manifest row still names the function's source (0x00475c60 has a row but no marker)
    import run_all as R
    for m in R.manifests() + sorted(glob.glob(os.path.join(ROOT, "src", "game", "**", "manifest.txt"), recursive=True)):
        for src, _sym, rva, _fl in R.read_rows([m], ""):
            if rva == va:
                # the object from the source path, not the manifest's directory (match/clones.txt lists slices too)
                f = os.path.normpath(os.path.join(ROOT, "match", src))
                rel = os.path.relpath(f, ROOT).split(os.sep)
                if rel[:2] == ["match", "slices"]:
                    return f, rel[2]
                if rel[:2] == ["src", "game"]:
                    stem = os.path.splitext(rel[-1])[0]
                    return f, (stem if S.module_dir(stem) else "%s/%s" % (rel[-2], stem))
    return None, None


def status(ident, va):
    d = S.slice_dir(ident)
    if any(r[2] == va for r in S.manifest_rows(ident)):
        return "byte-exact", ""
    for name, label in (("nonmatching.txt", "complete, not byte-exact yet"), ("partial.txt", "partial")):
        for rva, diff, reason in S.read_rows(os.path.join(d, name)):
            if rva == va:
                return label, "%s byte(s) differ; note: %s" % (diff, reason) if diff else reason
    return "has source, not listed", ""


def body(src, va):
    """the source text from the marker to the end of the function's braces"""
    t = open(src, errors="replace").read()
    m = re.search(r"(?mi)^//\s*@\s*0x0*%x\b.*$" % va, t)
    i = t.find("{", m.end())
    depth, j = 0, i
    while j < len(t):
        depth += {"{": 1, "}": -1}.get(t[j], 0)
        if depth == 0:
            break
        j += 1
    return t[m.start():j + 1]


def open_work(max_size):
    import run_all as R
    done = {r[2] for r in R.read_rows(R.manifests() + sorted(glob.glob(os.path.join(ROOT, "src", "game", "**", "manifest.txt"),
                                                                  recursive=True)), "")}
    rows = []
    for f in glob.glob(os.path.join(ROOT, "match", "slices", "*", "nonmatching.txt")) + \
            glob.glob(os.path.join(ROOT, "src", "game", "**", "nonmatching.txt"), recursive=True):
        for va, diff, reason in S.read_rows(f):
            fp = fingerprints().get(va)
            if fp and fp["size"] <= max_size and va not in done:
                rows.append((fp["size"], va, diff, os.path.relpath(os.path.dirname(f), ROOT), reason))
    # a function listed by both its slice and its migrated module: show it once, at the src/game copy (task.locate's choice)
    best = {}
    for r in rows:
        if r[1] not in best or r[3].startswith("src" + os.sep):
            best[r[1]] = r
    return list(best.values())


def never_tried(max_size):
    """functions nobody has started: no manifest row, no nonmatching/partial line, not open-source library code
    (symbols/lib_names.txt). Same row shape as open_work."""
    import run_all as R
    done = {r[2] for r in R.read_rows(R.manifests() + sorted(glob.glob(os.path.join(ROOT, "src", "game", "**", "manifest.txt"),
                                                                  recursive=True)), "")}
    noted = set()
    for f in glob.glob(os.path.join(ROOT, "match", "slices", "*", "*.txt")) + \
            glob.glob(os.path.join(ROOT, "src", "game", "**", "*.txt"), recursive=True):
        if f.endswith(("nonmatching.txt", "partial.txt")):
            noted |= {r[0] for r in S.read_rows(f)}
    lib = set()
    for l in open(os.path.join(ROOT, "symbols", "lib_names.txt")):
        p = l.split("#", 1)[0].split()
        if p:
            lib.add(int(p[0], 16))
    return [(fp["size"], va, "", "", "") for va, fp in fingerprints().items()
            if fp["size"] <= max_size and va not in done and va not in noted and va not in lib]


def new_source_path(va):
    return "match/slices/s%08x/s%08x.cpp" % (va, va)


def tries():
    """{va: times its nonmatching.txt note was written or rewritten} from git history, cached per commit in work/;
    None when the history is not available (shallow clone, no git)"""
    def g(*a):
        return subprocess.run(["git", *a], cwd=ROOT, capture_output=True, text=True)
    head = g("rev-parse", "HEAD").stdout.strip()
    if not head or g("rev-parse", "--is-shallow-repository").stdout.strip() == "true":
        return None
    cache = os.path.join(ROOT, "work", "task_tries.json")
    try:
        c = json.load(open(cache))
        if c.get("head") == head:
            return {int(k, 16): v for k, v in c["tries"].items()}
    except (OSError, ValueError):
        pass
    log = g("log", "--format=tformat:C", "-p", "--unified=0", "--no-renames", "--",
            "match/slices/*/nonmatching.txt", "src/game/**/nonmatching.txt", "src/game/*/*/nonmatching.txt").stdout
    out, minus, plus = collections.Counter(), {}, {}
    row = re.compile(r"([+-])([0-9a-fA-F]{8})\s+\S*\s*(.*)")
    for line in log.splitlines() + ["C"]:
        if line == "C":
            for va, txt in plus.items():
                if minus.get(va) != txt:        # a new note, or its text changed (a move with the same text is not a try)
                    out[va] += 1
            minus, plus = {}, {}
            continue
        m = row.match(line)
        if m and not line.startswith(("+++", "---")):
            (plus if m.group(1) == "+" else minus)[int(m.group(2), 16)] = m.group(3).strip()
    try:
        os.makedirs(os.path.dirname(cache), exist_ok=True)
        json.dump({"head": head, "tries": {"%08x" % k: v for k, v in out.items()}}, open(cache, "w"))
    except OSError:
        pass
    return dict(out)


def ndiff(diff):
    """the differing-byte count of a nonmatching row ('12', '~12', '12?'), or None; 0 is a placeholder (305 rows
    such as 'havok-equivalent' were never measured), so it counts as unknown"""
    m = re.match(r"\D*(\d+)", str(diff or ""))
    return int(m.group(1)) or None if m else None


def blocked():
    """{va: reason} from tools/contrib/blocked.txt (tools/contrib/sweep_tasks.py --write-blocked)"""
    out, path = {}, os.path.join(ROOT, "tools", "contrib", "blocked.txt")
    if os.path.exists(path):
        for l in open(path, encoding="utf-8"):
            if l.strip() and not l.startswith("#"):
                va, _, why = l.partition(" ")
                out[int(va, 16)] = why.strip()
    return out


CLAIMS_URL = "https://raw.githubusercontent.com/NoahBPeterson/spore-decomp/claims/claims.txt"
STALE_DAYS = 7


def claims():
    """va -> [(pr number, author, last update 'YYYY-MM-DD'), ...] from claims.txt (oldest pull request first);
    cached 10 minutes in work/claims.txt.
    Offline: the cached copy, or nothing."""
    cache = os.path.join(ROOT, "work", "claims.txt")
    text = None
    if not (os.path.exists(cache) and time.time() - os.path.getmtime(cache) < 600):
        try:
            with urllib.request.urlopen(CLAIMS_URL, timeout=10) as r:
                text = r.read().decode("utf-8", "replace")
            os.makedirs(os.path.dirname(cache), exist_ok=True)
            open(cache, "w", encoding="utf-8").write(text)
        except Exception:
            text = None
    if text is None and os.path.exists(cache):
        text = open(cache, encoding="utf-8").read()
    out = {}
    for line in (text or "").splitlines():
        p = line.split()
        if len(p) >= 4 and p[0].startswith("0x") and p[1].startswith("#"):
            out.setdefault(int(p[0], 16), []).append((int(p[1][1:]), p[2], p[3]))
    return {va: sorted(c) for va, c in out.items()}


def stale(claim):
    """claim: one (pr, author, date), or a function's list of them (stale only when all are)"""
    if isinstance(claim, list):
        return all(stale(c) for c in claim)
    try:
        return (datetime.date.today() - datetime.date.fromisoformat(claim[2])).days > STALE_DAYS
    except ValueError:
        return False


def my_seed():
    """Your own list order: git identity (name + email), else the host name."""
    g = lambda k: subprocess.run(["git", "-C", ROOT, "config", k], capture_output=True, text=True).stdout.strip()
    return (g("user.name") + "|" + g("user.email")).strip("|") or os.environ.get("COMPUTERNAME") or os.uname().nodename


def size_band(size):
    b = 16
    while size > b:
        b *= 2
    return b


def marked():
    """every va with a `// @ 0x...` marker in some source"""
    pat, out = re.compile(r"(?mi)^//\s*@\s*0x0*([0-9a-f]+)\b"), set()
    for f in sources():
        out.update(int(m.group(1), 16) for m in pat.finditer(open(f, errors="replace").read()))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("va", nargs="?")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--max-size", type=int, default=256)
    ap.add_argument("--by", choices=("tries", "diff", "size"), default="tries")
    ap.add_argument("--seed", help="your own shuffle within each band (default: your git name and email)")
    ap.add_argument("--show-claimed", action="store_true", help="also list functions in open pull requests")
    a = ap.parse_args()
    if a.list:
        skip, have = blocked(), marked()
        # left out: sources that do not compile on a clean clone (blocked.txt). Functions with no source yet are listed
        # too (0 tries when nobody has started them); task.py <va> says where to write them.
        work = open_work(a.max_size)
        seen = {r[1] for r in work}
        rows = [r for r in work + [r for r in never_tried(a.max_size) if r[1] not in seen] if r[1] not in skip]
        big = 1 << 30
        nd = lambda r: ndiff(r[2]) if ndiff(r[2]) is not None else big
        tr = tries() if a.by == "tries" else None
        if a.by == "tries" and tr is None:
            print("(no git history here, e.g. a shallow clone: tries unknown, so smallest first)")
        t = lambda r: tr.get(r[1], 0) if tr else 0
        seed = a.seed if a.seed is not None else my_seed()
        mine = lambda va: hashlib.sha1(("%s|%08x" % (seed, va)).encode()).hexdigest()
        key = {"tries": lambda r: (t(r), size_band(r[0]), mine(r[1])), "diff": lambda r: (nd(r), r[0], r[1]),
               "size": lambda r: (r[0], r[1])}[a.by]
        rows.sort(key=key)
        cl = claims()
        live = {va for va, c in cl.items() if not stale(c)}
        hidden = sum(1 for r in rows if r[1] in live)
        if not a.show_claimed:
            rows = [r for r in rows if r[1] not in live]
        order = {"tries": "fewest tries first, then by size band, in your own order within a band",
                 "diff": "fewest differing bytes first", "size": "smallest first"}[a.by]
        print("%d functions to work on, up to %d bytes, %s (source not byte-exact yet, or no source yet):"
              % (len(rows), a.max_size, order))
        if not cl:
            print("(claims.txt could not be read: functions in open pull requests are not hidden)")
        elif hidden and not a.show_claimed:
            print("(%d more are in open pull requests and hidden; --show-claimed lists them)" % hidden)
        print("  %-10s  %5s  %6s  %6s  %s" % ("function", "tries", "differ", "size", "where / last note"))
        for size, va, diff, where, reason in rows:
            n = ndiff(diff)
            if va not in have:
                where, reason = "no source yet", "write it in " + new_source_path(va) + (" (" + reason + ")" if reason else "")
            c = cl.get(va)
            if c:
                where = "%s %s  %s" % ("stale claim" if stale(c) else "in", ", ".join("#%d (%s)" % (x[0], x[1]) for x in c), where)
            print("  0x%08x  %5s  %6s  %6d  %s  %s" % (va, tr.get(va, 0) if tr else "?", n if n is not None else "-", size, where,
                                                      (reason or "")[:70]))
        return 0
    if not a.va:
        ap.error("give a function address, or --list")
    va = int(a.va, 16)
    fp = fingerprint(va)
    src, ident = locate(va)
    print("function   0x%08x" % va)
    for c in claims().get(va, []):
        print("claimed    %s #%d by %s (last update %s)%s" % (
            "STALE claim:" if stale(c) else "already in open pull request", c[0], c[1], c[2],
            "" if stale(c) else ": unless that is yours, pick another function"))
    print("retail     %s" % ("%d bytes (fingerprint: %d bytes are addresses, not compared)" %
                             (fp["size"], sum(n for _s, n in fp["mask"])) if fp else "no fingerprint: not a known function start"))
    if not src:
        p = new_source_path(va)
        print("source     none yet: no file has a `// @ 0x%08x` marker.\n"
              "next: create %s with the function, starting with the line `// @ 0x%08x`\n"
              "      (#include \"game/types.h\" and the class headers under src/game/include/ give you the types),\n"
              "      then: .venv/bin/python tools/contrib/check.py 0x%08x\n"
              "      With the analysis image, tools/matching/disasm.py work/SporeApp.analysis.bin 0x%08x prints the original."
              % (va, p, va, va, va))
        return 0
    st, note = status(ident, va)
    if va in blocked():
        print("blocked    its source does not compile on a clean clone yet (%s); this needs a maintainer, pick another"
              % blocked()[va])
    flags, how = S.choose_flags(ident, va)
    print("source     %s   (object %s)" % (os.path.relpath(src, ROOT), ident))
    print("status     %s%s" % (st, "\n           " + note[:300] if note else ""))
    print("flags      %s   (from %s)" % (" ".join(flags), how))
    incs = re.findall(r'(?m)^\s*#\s*include\s*([<"][^">]+[">])', open(src, errors="replace").read())
    print("includes   %s" % (" ".join(incs) or "none"))
    print("\n----- current source -----\n%s\n--------------------------\n" % body(src, va))
    print("next: edit the function in %s (any other function, header, constructor or class layout may change too),\n"
          "      then: .venv/bin/python tools/contrib/check.py 0x%08x\n"
          "      Rules and the full loop: AGENTS.md" % (os.path.relpath(src, ROOT), va))
    return 0


if __name__ == "__main__":
    sys.exit(main())
