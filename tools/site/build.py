#!/usr/bin/env python3
"""Build the public progress site (static HTML, no dependencies) into _site/.

  python3 tools/site/build.py [--out _site] [--prs prs.json] [--repo owner/name]

Numbers follow tools/ci/progress.py exactly: a function is byte-exact when a manifest row lists it and it is not in
tools/ci/known_failures.txt; totals are every retail function with a fingerprint. History is recomputed from git
(the last commit on main of each day), so it needs the full history (actions/checkout fetch-depth: 0). Merged pull
requests come from --prs (gh pr list --state merged --json number,author,mergedAt,mergeCommit,body).

Public-site rules: byte-exact counts only (no equivalence results), and no function names, symbol names or code.
Module names are EA's top-level directory names, already public as the folders under src/game/.
"""
import argparse, bisect, collections, datetime, glob, gzip, html, json, os, re, subprocess

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
BANDS = [(0, 63), (64, 255), (256, 1023), (1024, 4095), (4096, 1 << 30)]
MANIFEST_RE = re.compile(r"^(match/manifest\.txt|match/clones\.txt|match/slices/[^/]+/manifest\.txt|match/synth/[^/]+\.manifest|"
                         r"src/game/.+/manifest\.txt)$")


def git(*a, inp=None):
    return subprocess.run(["git", *a], cwd=ROOT, capture_output=True, text=True, input=inp, check=True).stdout


def rows_vas(text):
    out = set()
    for line in text.splitlines():
        p = line.split("#", 1)[0].split()
        if len(p) >= 3:
            try:
                out.add(int(p[2], 16))
            except ValueError:
                pass
    return out


def known_vas(text):
    return {int(l.split()[0], 16) for l in text.splitlines() if l.strip() and not l.startswith("#")}


def current(fps):
    vas = set()
    for path in glob.glob(os.path.join(ROOT, "match", "**", "*"), recursive=True) + \
            glob.glob(os.path.join(ROOT, "src", "game", "**", "manifest.txt"), recursive=True):
        rel = os.path.relpath(path, ROOT).replace(os.sep, "/")
        if MANIFEST_RE.match(rel) and os.path.isfile(path):
            vas |= rows_vas(open(path, errors="replace").read())
    known = known_vas(open(os.path.join(ROOT, "tools", "ci", "known_failures.txt")).read())
    return (vas - known) & set(fps)


class BlobCache:
    """byte-exact VAs at a commit, reading each manifest blob once across all commits"""
    def __init__(self):
        self.vas = {}

    def at(self, commit, fps):
        tree = git("ls-tree", "-r", commit, "--", "match", "src/game", "tools/ci/known_failures.txt")
        want, known_blob = [], None
        for line in tree.splitlines():
            meta, path = line.split("\t", 1)
            sha = meta.split()[2]
            if path == "tools/ci/known_failures.txt":
                known_blob = sha
            elif MANIFEST_RE.match(path):
                want.append(sha)
        need = [s for s in set(want) | ({known_blob} if known_blob else set()) if s not in self.vas]
        if need:
            out = subprocess.run(["git", "cat-file", "--batch"], cwd=ROOT, capture_output=True,
                                 input="\n".join(need).encode() + b"\n", check=True).stdout
            i = 0
            for sha in need:
                hdr_end = out.index(b"\n", i)
                size = int(out[i:hdr_end].split()[2])
                body = out[hdr_end + 1:hdr_end + 1 + size].decode("utf-8", "replace")
                self.vas[sha] = ("K", known_vas(body)) if sha == known_blob else ("M", rows_vas(body))
                i = hdr_end + 1 + size + 1
        done = set()
        for s in want:
            done |= self.vas[s][1]
        if known_blob:
            done -= self.vas[known_blob][1]
        return done & set(fps)


def history(fps):
    """[(date, functions, bytes)] for the last first-parent commit on main of each day"""
    log = git("log", "--first-parent", "--format=%H %cI", "HEAD").split("\n")
    last = {}
    for line in log:
        if line.strip():
            sha, when = line.split()
            day = datetime.datetime.fromisoformat(when).astimezone(datetime.timezone.utc).date().isoformat()
            last.setdefault(day, sha)          # log is newest first
    cache, pts = BlobCache(), []
    for day in sorted(last):
        done = cache.at(last[day], fps)
        if done:
            pts.append((day, len(done), sum(fps[v] for v in done)))
    return pts


def module_of(fps):
    d = json.load(open(os.path.join(ROOT, "tools", "site", "modules.json")))
    starts = [int(r[0], 16) for r in d["runs"]]
    def mod(va):
        i = bisect.bisect_right(starts, va) - 1
        return d["modules"][d["runs"][i][1]] if i >= 0 else d["modules"][0]
    return {va: mod(va) for va in fps}


def model_field(body):
    m = re.search(r"##\s*Model or tool\s*\n(.*?)(?:\n##|\Z)", body or "", re.S)
    text = re.sub(r"<!--.*?-->", "", m.group(1), flags=re.S).strip() if m else ""
    if text:
        return text.splitlines()[0].strip(" -*`")
    # no template section: a model named anywhere in the description ("Written by an AI agent (opencode, DeepSeek V4.1 Flash)")
    k = re.search(r"\b(Claude [A-Z][a-z]+ [\d.]+|(?:Claude )?(?:Opus|Sonnet|Haiku|Fable) [\d.]+|DeepSeek[ -][\w.]+(?: Flash| Pro)?|"
                  r"GPT-[\w.]+|Gemini [\w.]+(?: Pro| Flash)?|GLM-[\w.]+|Kimi[ -][\w.]+|Qwen[\w.-]*|by hand)\b", body or "", re.I)
    return k.group(1) if k else ""


def pr_credits(prs_path, fps):
    if not prs_path or not os.path.exists(prs_path):
        return []
    out = []
    for p in json.load(open(prs_path)):
        sha = (p.get("mergeCommit") or {}).get("oid")
        if not sha:
            continue
        try:
            diff = git("diff", "%s^" % sha, sha, "--unified=0", "--", "match", "src/game")
        except subprocess.CalledProcessError:
            continue
        added, removed, path = set(), set(), ""
        for line in diff.splitlines():
            if line.startswith("+++ "):
                path = line[6:] if line.startswith("+++ b/") else ""
            elif MANIFEST_RE.match(path or ""):
                if line.startswith("+") and not line.startswith("+++"):
                    added |= rows_vas(line[1:])
                elif line.startswith("-") and not line.startswith("---"):
                    removed |= rows_vas(line[1:])
        new = (added - removed) & set(fps)
        out.append({"n": p["number"], "who": (p.get("author") or {}).get("login", "?"), "when": (p.get("mergedAt") or "")[:10],
                    "f": len(new), "b": sum(fps[v] for v in new), "model": model_field(p.get("body"))[:48]})
    return sorted(out, key=lambda r: -r["n"])


# ---------------------------------------------------------------- rendering

E = html.escape
fmt = lambda n: format(n, ",")


def pct(a, b):
    return 100.0 * a / b if b else 0.0


def kb(b):
    return "%.2f MB" % (b / 1048576) if b >= 1048576 else "%d KB" % round(b / 1024) if b >= 10240 else fmt(b) + " B"


CSS = """
:root{--bg:#f7f5f0;--panel:#fffdf8;--ink:#1d2228;--muted:#5d6670;--line:#e3ddd2;--done:#2f7d5b;--done2:#9cc9b2;
--todo:#e9e3d8;--accent:#b5562b;--code:#f0ece4}
@media (prefers-color-scheme:dark){:root:not([data-theme=light]){--bg:#14171b;--panel:#1b1f24;--ink:#e8e6e1;--muted:#9aa3ad;
--line:#2c3239;--done:#4fb487;--done2:#2b6a4f;--todo:#2a2f36;--accent:#e08a5c;--code:#22272e}}
*{box-sizing:border-box}html{-webkit-text-size-adjust:100%}
body{margin:0;background:var(--bg);color:var(--ink);font:16px/1.55 system-ui,-apple-system,"Segoe UI",sans-serif}
a{color:var(--accent)}main,header,footer{max-width:960px;margin:0 auto;padding:0 16px}
header{display:flex;flex-wrap:wrap;align-items:baseline;gap:8px 24px;padding-top:28px;padding-bottom:8px}
header .brand{font-weight:700;font-size:20px;color:var(--ink);text-decoration:none;letter-spacing:.2px}
header nav{display:flex;gap:18px;flex-wrap:wrap}header nav a{color:var(--muted);text-decoration:none}
header nav a[aria-current=page]{color:var(--ink);border-bottom:2px solid var(--accent)}
h1{font-size:clamp(28px,5vw,40px);line-height:1.15;margin:28px 0 8px}h2{font-size:20px;margin:40px 0 12px}
.lede{color:var(--muted);max-width:680px;margin:0 0 24px}
.panel{background:var(--panel);border:1px solid var(--line);border-radius:10px;padding:20px}
.hero{display:grid;grid-template-columns:repeat(auto-fit,minmax(200px,1fr));gap:16px;margin:8px 0 16px}
.stat b{display:block;font-size:34px;line-height:1.1;font-variant-numeric:tabular-nums}.stat span{color:var(--muted);font-size:14px}
.bar{display:flex;height:14px;border-radius:7px;overflow:hidden;background:var(--todo)}.bar i{display:block;background:var(--done)}
.legend{display:flex;gap:16px;flex-wrap:wrap;font-size:13px;color:var(--muted);margin-top:8px}
.legend i{display:inline-block;width:10px;height:10px;border-radius:2px;margin-right:6px;vertical-align:-1px}
table{width:100%;border-collapse:collapse;font-size:14px;font-variant-numeric:tabular-nums}
th,td{text-align:right;padding:7px 8px;border-bottom:1px solid var(--line);white-space:nowrap}
th:first-child,td:first-child{text-align:left}th{color:var(--muted);font-weight:600}
.scroll{overflow-x:auto}.mod td.barcell{width:45%;min-width:120px}.mod .bar{height:10px}
svg text{fill:var(--muted);font-size:11px}.chart{width:100%;height:auto;display:block}
pre{background:var(--code);border-radius:8px;padding:14px;overflow-x:auto;font-size:13px;line-height:1.5}
code{font-family:ui-monospace,SFMono-Regular,Menlo,monospace}p code,li code{background:var(--code);padding:1px 5px;border-radius:4px;font-size:.9em}
.note{color:var(--muted);font-size:13px}footer{color:var(--muted);font-size:13px;padding-top:32px;padding-bottom:40px}
ol li,ul li{margin:6px 0}
"""


def page(title, here, body, meta):
    nav = "".join('<a href="%s"%s>%s</a>' % (f, ' aria-current="page"' if f == here else "", n)
                  for f, n in (("index.html", "Progress"), ("join.html", "Join"), ("how.html", "How it works")))
    return """<!doctype html><html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>%s</title><meta name="description" content="Rebuilding Spore's SporeApp.exe as C++ that compiles to exactly the retail machine code.">
<style>%s</style></head><body>
<header><a class="brand" href="index.html">spore-decomp</a><nav>%s<a href="https://github.com/%s">GitHub</a></nav></header>
<main>%s</main>
<footer>Generated %s from commit <a href="https://github.com/%s/commit/%s"><code>%s</code></a>.
A fan preservation project, not affiliated with or endorsed by Electronic Arts or Maxis. This site and the repository
contain no game code or data.</footer></body></html>""" % (E(title), CSS, nav, E(meta["repo"]), body, meta["when"], E(meta["repo"]),
                                                       meta["sha"], meta["sha"][:9])


def line_chart(pts, total_f, total_b):
    if len(pts) < 2:
        return ""
    W, H, L, R, T, B = 900, 260, 44, 130, 14, 30
    d0 = datetime.date.fromisoformat(pts[0][0]); d1 = datetime.date.fromisoformat(pts[-1][0])
    span = max(1, (d1 - d0).days)
    x = lambda d: L + (W - L - R) * (datetime.date.fromisoformat(d) - d0).days / span
    y = lambda p: T + (H - T - B) * (1 - p / 100.0)
    g = []
    for p in (0, 25, 50, 75, 100):
        g.append('<line x1="%d" x2="%d" y1="%.1f" y2="%.1f" stroke="var(--line)"/><text x="%d" y="%.1f" text-anchor="end">%d%%</text>'
                 % (L, W - R, y(p), y(p), L - 6, y(p) + 4, p))
    ticks, step = [], max(1, span // 6)
    for k in range(0, span + 1, step):
        dd = d0 + datetime.timedelta(days=k)
        ticks.append('<text x="%.1f" y="%d" text-anchor="middle">%s</text>' % (x(dd.isoformat()), H - 8, dd.strftime("%b %-d")))
    def series(vals, color, label, dash=""):
        path = " ".join("%s%.1f,%.1f" % ("M" if i == 0 else "L", x(d), y(v)) for i, (d, v) in enumerate(vals))
        lx, ly = x(vals[-1][0]), y(vals[-1][1])
        return ('<path d="%s" fill="none" stroke="%s" stroke-width="2.5" %s/>' % (path, color, dash) +
                '<circle cx="%.1f" cy="%.1f" r="3.5" fill="%s"/>' % (lx, ly, color) +
                '<text x="%.1f" y="%.1f" style="fill:%s;font-weight:600">%.1f%% %s</text>' % (lx + 8, ly + 4, color, vals[-1][1], label))
    sf = [(d, pct(f, total_f)) for d, f, b in pts]
    sb = [(d, pct(b, total_b)) for d, f, b in pts]
    return ('<svg class="chart" viewBox="0 0 %d %d" role="img" aria-label="Byte-exact share over time">%s%s%s%s</svg>'
            % (W, H, "".join(g), "".join(ticks), series(sf, "var(--done2)", "of functions", 'stroke-dasharray="5 4"'),
               series(sb, "var(--done)", "of bytes")))


def build(out, prs_path, repo):
    fps = {int(d["va"], 16): d["size"] for d in map(json.loads, gzip.open(os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl.gz"), "rt"))}
    done = current(fps)
    tf, tb = len(fps), sum(fps.values())
    df, db = len(done), sum(fps[v] for v in done)
    meta = {"repo": repo, "sha": git("rev-parse", "HEAD").strip(),
            "when": datetime.datetime.now(datetime.timezone.utc).strftime("%Y-%m-%d %H:%M UTC")}
    hist = history(fps)
    mods = collections.defaultdict(lambda: [0, 0, 0, 0])
    for va, m in module_of(fps).items():
        r = mods[m]; r[0] += 1; r[1] += fps[va]
        if va in done:
            r[2] += 1; r[3] += fps[va]
    prs = pr_credits(prs_path, fps)

    # --- progress page
    b = ['<h1>Spore, rebuilt byte for byte</h1><p class="lede">Every function of Spore\'s <code>SporeApp.exe</code> (2008, PC) '
         'rewritten as readable C++ that compiles, with the original compilers, to exactly the machine code that shipped. '
         'Almost right counts as zero.</p>']
    b.append('<div class="panel"><div class="hero">'
             '<div class="stat"><b>%.1f%%</b><span>of the code, by bytes</span></div>'
             '<div class="stat"><b>%s</b><span>of %s functions byte-exact</span></div>'
             '<div class="stat"><b>%s</b><span>of %s rebuilt</span></div></div>'
             '<div class="bar" aria-hidden="true"><i style="width:%.2f%%"></i></div>'
             '<div class="legend"><span><i style="background:var(--done)"></i>byte-exact</span>'
             '<span><i style="background:var(--todo)"></i>not yet</span></div></div>'
             % (pct(db, tb), fmt(df), fmt(tf), kb(db), kb(tb), pct(db, tb)))
    b.append('<p class="note">Bytes are the honest measure: most of what remains is in large functions. Every count here '
             'is checked against retail fingerprints by the pull-request check; nothing is counted on trust.</p>')
    if len(hist) >= 2:
        b.append('<h2>Over time</h2><div class="panel">%s</div><p class="note">Byte-exact share at the end of each day '
                 '(solid: bytes, dashed: functions).</p>' % line_chart(hist, tf, tb))
    b.append('<h2>By function size</h2><div class="panel scroll"><table><tr><th>size</th><th>functions done</th><th>of</th>'
             '<th>bytes done</th><th>share</th></tr>')
    for lo, hi in BANDS:
        allv = [v for v, s in fps.items() if lo <= s <= hi]
        d = [v for v in allv if v in done]
        nb, dbb = sum(fps[v] for v in allv), sum(fps[v] for v in d)
        b.append('<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%.0f%%</td></tr>' % (
            "%d-%d bytes" % (lo, hi) if hi < 1 << 30 else "%d+ bytes" % lo, fmt(len(d)), fmt(len(allv)), kb(dbb), pct(dbb, nb)))
    b.append('</table></div>')
    b.append('<h2>By module</h2><div class="panel scroll"><table class="mod"><tr><th>module</th><th>byte-exact (bytes)</th>'
             '<th></th><th>functions</th><th>code</th></tr>')
    for m, (n, nb, d, dbb) in sorted(mods.items(), key=lambda kv: (kv[0] == "Not yet attributed", -kv[1][1])):
        b.append('<tr><td>%s</td><td class="barcell"><div class="bar"><i style="width:%.2f%%"></i></div></td><td>%.0f%%</td>'
                 '<td>%s / %s</td><td>%s</td></tr>' % (E(m), pct(dbb, nb), pct(dbb, nb), fmt(d), fmt(n), kb(nb)))
    b.append('</table></div><p class="note">Modules are EA\'s own top-level source directories from the development '
             'build. "Not yet attributed" is code whose module is not known yet.</p>')
    if prs:
        who = collections.defaultdict(lambda: [0, 0, 0])
        for p in prs:
            w = who[p["who"]]; w[0] += 1; w[1] += p["f"]; w[2] += p["b"]
        b.append('<h2>Contributors</h2><div class="panel scroll"><table><tr><th>contributor</th><th>pull requests</th>'
                 '<th>functions</th><th>bytes</th></tr>')
        for k, (n, f, by) in sorted(who.items(), key=lambda kv: (-kv[1][2], kv[0])):
            b.append('<tr><td><a href="https://github.com/%s">%s</a></td><td>%d</td><td>%s</td><td>%s</td></tr>'
                     % (E(k), E(k), n, fmt(f), fmt(by)))
        b.append('</table></div><h2>Recent pull requests</h2><div class="panel scroll"><table><tr><th>pull request</th>'
                 '<th>merged</th><th>by</th><th>functions</th><th>bytes</th><th>model or tool</th></tr>')
        for p in prs[:25]:
            b.append('<tr><td><a href="https://github.com/%s/pull/%d">#%d</a></td><td>%s</td><td>%s</td><td>%s</td>'
                     '<td>%s</td><td style="text-align:left">%s</td></tr>' % (E(repo), p["n"], p["n"], p["when"], E(p["who"]),
                                                                          fmt(p["f"]), fmt(p["b"]), E(p["model"] or "")))
        b.append('</table></div><p class="note">Counted from pull requests merged since contributions opened '
                 '(November 2026). Most earlier work was done by the maintainer\'s own agent runs.</p>')
    b.append('<h2>Help</h2><p>Hundreds of functions are only a few bytes from a match. <a href="join.html">Start here</a>.</p>')

    join = """<h1>Join</h1><p class="lede">Pick a function whose C++ is already written but compiles a few bytes off,
change the source until the bytes are identical, and open a pull request. People and AI agents are both welcome;
the check is the same for everyone.</p>
<h2>You need</h2><ul><li>macOS or Linux (on Windows, WSL), Python 3.10+, Wine and <code>msitools</code></li>
<li>Your own copy of Spore (Steam), to build a local analysis image that shows instruction diffs. It never leaves your machine.</li></ul>
<h2>Set up and start</h2>
<pre><code>git clone https://github.com/%(repo)s && cd %(name)s
python3 -m venv .venv && .venv/bin/pip install pefile capstone pycryptodome
sh tools/ci/setup_toolchain.sh        # the original compilers, from Microsoft's installers, hash-checked
.venv/bin/python tools/contrib/make_image.py "&lt;Spore&gt;/SporeBin/SporeApp.exe"   # must print IMAGE OK

.venv/bin/python tools/contrib/task.py --list        # fewest tries first, your own order; claimed ones hidden
.venv/bin/python tools/contrib/task.py 0x00ee9260    # one function: file, flags, note, source
.venv/bin/python tools/contrib/check.py 0x00ee9260   # MATCH, or an instruction diff</code></pre>
<p>Open a draft pull request early, titled with the function's address: that claims it, and it drops out of
everyone else's list within minutes. On <code>MATCH</code>, <code>check.py</code> updates the bookkeeping files itself;
mark the pull request ready, using the template. The Byte-match check runs on it automatically.</p>
<h2>Using an AI agent?</h2><p>Point it at the repository and tell it to read
<a href="https://github.com/%(repo)s/blob/main/AGENTS.md"><code>AGENTS.md</code></a> first. It has everything an agent
needs: the loop, the rules, and where the known compiler tricks are written down.</p>
<h2>The rules, briefly</h2><ul>
<li>Only <code>src/game/</code>, <code>match/slices/</code> and <code>match/include/</code> change in a contribution.</li>
<li>Real C++: no assembly transcriptions or raw bytes (a short <code>__asm</code> helper is fine where the original used one), no constants disguised as addresses of made-up globals.</li>
<li>Never commit game files or anything derived from them.</li>
<li>Stuck? Move on to another function. Only pull requests that add at least one new byte-exact function are merged; a closer attempt or a better note for another function can ride along with one that does.</li></ul>""" % {"repo": E(repo), "name": E(repo.split("/")[-1])}

    how = """<h1>How it works</h1>
<h2>What "byte-exact" means</h2><p>Spore's executable was built in 2008 with Visual C++ 2008 SP1 (and the Visual
C++ Toolkit 2003 for its Havok and RenderWare code). This project rewrites each function as C++ and compiles it with
those same compilers and options. A function counts only when its compiled bytes are identical to the shipped
function's, apart from the addresses the linker fills in. Close does not count.</p>
<h2>How a match is checked without the game</h2><p>The repository contains no game code. For each retail function it
keeps a <em>fingerprint</em>: its size, which byte positions hold addresses, and a SHA-256 hash of the remaining
bytes. Every pull request runs the <strong>Byte-match check</strong> on GitHub, which compiles every function the change
can affect and compares it with its fingerprint. It fails if anything that matched before stops matching.</p>
<h2>Why bother</h2><p>Byte-exact source is the strongest proof that a decompilation is right: it is the program, not
an approximation of it. It is the foundation for preserving the game, understanding it, and eventually building it for
other platforms.</p>
<h2>What is not here</h2><p>No game code, data or assets. Contributors use their own copy of the game locally to see
instruction diffs; nothing derived from it is ever committed. The open-source libraries the game links (jpeg, libpng,
OpenSSL, and EA's published EASTL and EAWebKit) are rebuilt from their published sources rather than decompiled.</p>
<p>Source, tools and every rule: <a href="https://github.com/%s">github.com/%s</a>.</p>""" % (E(repo), E(repo))

    os.makedirs(out, exist_ok=True)
    for name, title, body in (("index.html", "spore-decomp: progress", "".join(b)), ("join.html", "spore-decomp: join", join),
                              ("how.html", "spore-decomp: how it works", how)):
        open(os.path.join(out, name), "w", encoding="utf-8").write(page(title, name, body, meta))
    open(os.path.join(out, ".nojekyll"), "w").close()
    print("%s: %d/%d functions, %.1f%% of bytes, %d history points, %d modules, %d merged PRs"
          % (out, df, tf, pct(db, tb), len(hist), len(mods), len(prs)))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=os.path.join(ROOT, "_site"))
    ap.add_argument("--prs")
    ap.add_argument("--repo", default="NoahBPeterson/spore-decomp")
    a = ap.parse_args()
    build(a.out, a.prs, a.repo)


if __name__ == "__main__":
    main()
