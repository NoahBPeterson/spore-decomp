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
stale and shows again. task.py <va> checks live: it fetches claims.txt fresh and asks GitHub for open pull requests
(drafts too) that name the address, so a claim made minutes ago still shows.

For a function that is not byte-exact yet, task.py <va> also prints every earlier version of its note from git history
and the closed, unmerged pull requests titled with its address (one public GitHub search, cached a day in work/).

--category WORD (with --list): only functions whose note starts with that word and a colon (regalloc, schedule, frame,
inline, layout, data, other: why the function still differs, see AGENTS.md step 6).

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


def equivalent():
    """{va: (level, layer)} of the functions proven behaviourally equivalent (equivalent.txt + equivalent/<va>.json,
    tools/contrib/prove.py). They are not byte-exact, so they stay open, but --list shows them last."""
    import json
    out = {}
    for f in glob.glob(os.path.join(ROOT, "match", "slices", "*", "equivalent.txt")) + \
            glob.glob(os.path.join(ROOT, "src", "game", "**", "equivalent.txt"), recursive=True):
        for line in open(f):
            p = line.split("#", 1)[0].split()
            if len(p) >= 3:
                va = int(p[2], 16)
                b = os.path.join(os.path.dirname(f), "equivalent", "%08x.json" % va)
                try:
                    d = json.load(open(b))
                    out[va] = (d.get("level", "?"), d.get("layer", "?"))
                except (OSError, ValueError):
                    out[va] = ("?", "no bundle")
    return out


def status(ident, va):
    d = S.slice_dir(ident)
    if any(r[2] == va for r in S.manifest_rows(ident)):
        return "byte-exact", ""
    eq = equivalent().get(va)
    if eq:
        return "proven equivalent (%s, %s), not byte-exact yet" % eq, "a byte-exact match still counts; see its note below"
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


def library_functions():
    """Addresses rebuilt from published library sources, outside the matching queue."""
    out = set()
    with open(os.path.join(ROOT, "symbols", "lib_names.txt")) as stream:
        for line in stream:
            fields = line.split("#", 1)[0].split()
            if fields:
                out.add(int(fields[0], 16))
    return out


def open_work(max_size):
    import run_all as R
    done = {r[2] for r in R.read_rows(R.manifests() + sorted(glob.glob(os.path.join(ROOT, "src", "game", "**", "manifest.txt"),
                                                                  recursive=True)), "")}
    lib = library_functions()
    rows = []
    # partial.txt rows too (an incomplete or placeholder body: it needs real source first), marked as such; they
    # used to be in neither queue, so incomplete functions were invisible to --list
    for name, partial in (("nonmatching.txt", False), ("partial.txt", True)):
        for f in glob.glob(os.path.join(ROOT, "match", "slices", "*", name)) + \
                glob.glob(os.path.join(ROOT, "src", "game", "**", name), recursive=True):
            for va, diff, reason in S.read_rows(f):
                fp = fingerprints().get(va)
                if fp and fp["size"] <= max_size and va not in done and va not in lib:
                    rows.append((fp["size"], va, "-" if partial else diff, os.path.relpath(os.path.dirname(f), ROOT),
                                 ("PARTIAL, needs source: " + (reason or "")) if partial else reason, partial))
    # a function listed by both its slice and its migrated module: show it once, at the src/game copy (task.locate's
    # choice); a complete (nonmatching) note wins over a partial one
    best = {}
    for r in rows:
        b = best.get(r[1])
        if b is None or (b[5] and not r[5]) or (b[5] == r[5] and r[3].startswith("src" + os.sep)):
            best[r[1]] = r
    return [r[:5] for r in best.values()]


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
    lib = library_functions()
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


NOTE_PATHS = ("match/slices/*/nonmatching.txt", "match/slices/*/partial.txt",
              "src/game/**/nonmatching.txt", "src/game/**/partial.txt")
# The first word of a note, when it is one of these followed by a colon, says why the function still differs (AGENTS.md).
CATEGORIES = ("regalloc", "schedule", "frame", "inline", "layout", "data", "other")


def history(va):
    """Every version of the function's nonmatching.txt / partial.txt note, oldest first:
    [(date, short commit, pull request number or None, differing bytes, note text)].  A move with unchanged text
    (a migration) is listed once.  [] without git history (shallow clone)."""
    r = subprocess.run(["git", "log", "-i", "-G", "^%08x" % va, "--reverse", "--date=short",
                        "--format=tformat:C %h %ad %s", "-p", "--unified=0", "--no-renames", "--", *NOTE_PATHS],
                       cwd=ROOT, capture_output=True, text=True)
    out, head = [], None
    row = re.compile(r"\+%08x\s+(\S*)\s*(.*)" % va, re.I)
    for line in r.stdout.splitlines():
        if line.startswith("C "):
            head = line.split(" ", 3)
            continue
        m = row.match(line)
        if m and head and not (out and out[-1][3:] == (m.group(1), m.group(2).strip())):
            pr = re.search(r"\(#(\d+)\)\s*$", head[3] if len(head) > 3 else "")
            out.append((head[2], head[1], int(pr.group(1)) if pr else None, m.group(1), m.group(2).strip()))
    return out


def closed_attempts(va):
    """Closed, unmerged pull requests titled with the address: [(number, author, closed 'YYYY-MM-DD', title)].
    Their source was not merged (code merges only with a byte-exact function), so this is where the closest earlier
    attempt can be read.  Asks GitHub's public search once, cached a day in work/; [] when offline."""
    cache = os.path.join(ROOT, "work", "task_closed_%08x.json" % va)
    if os.path.exists(cache) and time.time() - os.path.getmtime(cache) < 86400:
        try:
            return [tuple(x) for x in json.load(open(cache))]
        except (OSError, ValueError):
            pass
    url = ("https://api.github.com/search/issues?per_page=20&q=repo:NoahBPeterson/spore-decomp+is:pr+is:closed"
           "+is:unmerged+in:title+0x%08x" % va)
    try:
        req = urllib.request.Request(url, headers={"Accept": "application/vnd.github+json", "User-Agent": "task.py"})
        with urllib.request.urlopen(req, timeout=10) as r:
            items = json.load(r).get("items", [])
    except Exception:
        return []
    out = [(i["number"], i["user"]["login"], (i.get("closed_at") or "")[:10], i["title"]) for i in items
           if ("%08x" % va) in i["title"].lower()]
    out.sort()
    try:
        os.makedirs(os.path.dirname(cache), exist_ok=True)
        json.dump(out, open(cache, "w"))
    except OSError:
        pass
    return out


def category(reason):
    m = re.match(r"\s*([a-z]+):", reason or "")
    return m.group(1) if m and m.group(1) in CATEGORIES else None


def ndiff(diff):
    """the differing-byte count of a nonmatching row ('12', '~12', '12?'), or None; 0 is a placeholder (305 rows
    such as 'havok-equivalent' were never measured), so it counts as unknown"""
    m = re.fullmatch(r"~?(\d+)\??", str(diff or "").strip())
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


def claims(max_age=600):
    """va -> [(pr number, author, last update 'YYYY-MM-DD'), ...] from claims.txt (oldest pull request first);
    cached max_age seconds in work/claims.txt (0: always fetch).  None when claims.txt could not be read at all
    (offline, no cached copy); {} when it was read and nobody claims anything."""
    cache = os.path.join(ROOT, "work", "claims.txt")
    text = None
    if not (os.path.exists(cache) and time.time() - os.path.getmtime(cache) < max_age):
        for attempt in (1, 2):
            try:
                with urllib.request.urlopen(CLAIMS_URL, timeout=10 * attempt) as r:
                    text = r.read().decode("utf-8", "replace")
                os.makedirs(os.path.dirname(cache), exist_ok=True)
                open(cache, "w", encoding="utf-8").write(text)
                break
            except Exception:
                text = None
    if text is None and os.path.exists(cache):
        text = open(cache, encoding="utf-8").read()
    if text is None:
        return None
    out = {}
    for line in text.splitlines():
        p = line.split()
        if len(p) >= 4 and p[0].startswith("0x") and p[1].startswith("#"):
            out.setdefault(int(p[0], 16), []).append((int(p[1][1:]), p[2], p[3]))
    return {va: sorted(c) for va, c in out.items()}


def open_prs(va):
    """Open pull requests (drafts too) that name the address in their title or body, asked live from GitHub's public
    search: [(number, author, last update 'YYYY-MM-DD', title)]. This covers a pull request opened in the last few
    minutes, before claims.txt lists it. None when GitHub could not be asked (offline, rate limit)."""
    url = ("https://api.github.com/search/issues?per_page=30&q=repo:NoahBPeterson/spore-decomp+is:pr+is:open"
           "+0x%08x+OR+%08x" % (va, va))
    try:
        req = urllib.request.Request(url, headers={"Accept": "application/vnd.github+json", "User-Agent": "task.py"})
        with urllib.request.urlopen(req, timeout=10) as r:
            items = json.load(r).get("items", [])
    except Exception:
        return None
    return sorted((i["number"], i["user"]["login"], (i.get("updated_at") or "")[:10], i["title"]) for i in items
                  if ("%08x" % va) in (i["title"] + " " + (i.get("body") or "")).lower())


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
    ap.add_argument("--category", choices=CATEGORIES, help="with --list: only notes that start with this word")
    ap.add_argument("--show-equivalent", action="store_true",
                    help="with --list: also list functions already proven equivalent (tools/contrib/prove.py)")
    a = ap.parse_args()
    if a.list:
        skip, have = blocked(), marked()
        # left out: sources that do not compile on a clean clone (blocked.txt). Functions with no source yet are listed
        # too (0 tries when nobody has started them); task.py <va> says where to write them.
        work = open_work(a.max_size)
        seen = {r[1] for r in work}
        rows = [r for r in work + [r for r in never_tried(a.max_size) if r[1] not in seen] if r[1] not in skip]
        if a.category:
            rows = [r for r in rows if category(r[4]) == a.category]
        eqv = equivalent()
        neq = sum(1 for r in rows if r[1] in eqv)
        if not a.show_equivalent:
            rows = [r for r in rows if r[1] not in eqv]
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
        live = {va for va, c in (cl or {}).items() if not stale(c)}
        hidden = sum(1 for r in rows if r[1] in live)
        if not a.show_claimed:
            rows = [r for r in rows if r[1] not in live]
        order = {"tries": "fewest tries first, then by size band, in your own order within a band",
                 "diff": "fewest differing bytes first", "size": "smallest first"}[a.by]
        print("%d functions to work on, up to %d bytes, %s (source not byte-exact yet, or no source yet):"
              % (len(rows), a.max_size, order))
        if cl is None:
            print("(claims.txt could not be read: functions in open pull requests are not hidden)")
        elif hidden and not a.show_claimed:
            print("(%d more are in open pull requests and hidden; --show-claimed lists them)" % hidden)
        if neq and not a.show_equivalent:
            print("(%d more are proven equivalent already and hidden; --show-equivalent lists them)" % neq)
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
    # live claim check: a fresh claims.txt (pull requests that change the function) plus GitHub's search for open pull
    # requests naming the address (catches a draft opened minutes ago, before claims.txt lists it)
    cl, prs = claims(max_age=0), open_prs(va)
    listed = (cl or {}).get(va, [])
    for c in listed:
        print("claimed    %s #%d by %s (last update %s)%s" % (
            "STALE claim:" if stale(c) else "already in open pull request", c[0], c[1], c[2],
            "" if stale(c) else ": unless that is yours, pick another function"))
    for n, who, upd, title in prs or []:
        if n not in {c[0] for c in listed}:
            print("claimed    open pull request #%d by %s names this address (last update %s): unless that is yours, "
                  "pick another function\n           %s" % (n, who, upd, title[:100]))
    if cl is None and prs is None:
        print("claimed    COULD NOT CHECK (offline?): look for this address in the open pull requests before starting")
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
    if st != "byte-exact":
        hist = history(va)
        if len(hist) > 1:
            print("earlier notes (oldest first; the last is the current one):")
            for date, sha, pr, diff, text in hist:
                print("  %s %-9s %4s  %s" % (date, "#%d" % pr if pr else sha, diff if ndiff(diff) else "-", text[:600]))
        att = closed_attempts(va)
        if att:
            print("closed attempts (not merged; their source is the closest earlier try, read it before starting over):")
            for num, who, when, title in att:
                print("  #%d by %s, closed %s: %s\n      https://github.com/NoahBPeterson/spore-decomp/pull/%d/files"
                      % (num, who, when, title[:90], num))
    incs = re.findall(r'(?m)^\s*#\s*include\s*([<"][^">]+[">])', open(src, errors="replace").read())
    print("includes   %s" % (" ".join(incs) or "none"))
    print("\n----- current source -----\n%s\n--------------------------\n" % body(src, va))
    print("next: edit the function in %s (any other function, header, constructor or class layout may change too),\n"
          "      then: .venv/bin/python tools/contrib/check.py 0x%08x\n"
          "      Rules and the full loop: AGENTS.md" % (os.path.relpath(src, ROOT), va))
    return 0


if __name__ == "__main__":
    sys.exit(main())
