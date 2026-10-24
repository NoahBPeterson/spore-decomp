#!/usr/bin/env python3
"""List claims whose source is assembly transcription rather than C++.

usage: asm_audit.py [--all-rows] [--review] [slice-id | src/game/<module>.cpp ...]
       (default: every slice under match/slices and every module TU under src/game)
A function body (text from its `// @ 0x<VA>` marker to the next one, comments stripped) is a transcription when it
uses `_emit`, is `__declspec(naked)`, or has an `__asm` block longer than HELPER_MAX (8) instructions (2026-10-18:
the old ">3 blocks" rule missed single-block transcriptions claimed as byte-exact). Helper-sized blocks (cvtss2si,
maxss/minss clamps, fnstcw/fldcw, rdtsc) are EA's own inline-asm math helpers and are allowed; --review also lists
bodies with more than 3 such blocks or mostly such blocks, for a human look (they do not fail run_all).
By default only manifest (byte-exact) rows are checked; --all-rows also checks nonmatching.txt rows.
Output: "<slice-or-tu> <va> <kind> <reason>"; exit 1 if any.
run_all.py calls transcribed() and reports such rows as ASM instead of MATCH (docs/matching.md, "No assembly
transcription"). Tiny hand-written thunks may be legitimate but still need a human look.
"""
import glob, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
_MARK = re.compile(r"//\s*@\s*(?:0x)?([0-9a-fA-F]{6,8})")
_cache = {}


def _strip_comments(s):
    s = re.sub(r"/\*.*?\*/", "", s, flags=re.S)
    return re.sub(r"//[^\n]*", "", s)


def _asm_runs(code):
    """(asm instruction lines per __asm block or statement, code lines in total)."""
    all_lines = [l for l in code.splitlines() if l.strip()]
    lines = [l for l in all_lines if l.strip() not in ("{", "}", "};")]
    runs, depth, cur, opening = [], 0, None, False
    for l in all_lines:  # braces-only lines still move the depth
        if opening and l.strip().startswith("{"):  # `__asm` on its own line, `{` on the next
            opening, depth = False, l.count("{") - l.count("}")
            continue
        opening = False
        if re.search(r"\b_?_asm\b", l):
            rest = re.split(r"\b_?_asm\b", l, maxsplit=1)[1].strip().strip("{}").strip()
            depth = l.count("{") - l.count("}")
            cur = 1 if rest else 0
            if depth <= 0 and not rest:
                opening = True
            elif depth <= 0:
                runs.append(cur); cur = None
        elif depth > 0:
            depth += l.count("{") - l.count("}")
            if l.strip().strip("{}").strip():
                cur += 1
            if depth <= 0:
                runs.append(cur); cur = None
    if cur is not None:
        runs.append(cur)
    return runs, len(lines)


HELPER_MAX = 8  # an __asm block of up to 8 instructions is a helper (cvtss2si, maxss/minss clamp, fnstcw, rdtsc)


def why(body, review=False):
    """Reason string when a function body is an assembly transcription, else None. With review=True also report
    bodies that only use helper-sized blocks but many of them or mostly (they need a human look, not a demotion)."""
    code = _strip_comments(body)
    if re.search(r"\b_?_emit\b", code):
        return "_emit"
    if re.search(r"__declspec\s*\(\s*naked\s*\)", code):
        return "naked"
    runs, n = _asm_runs(code)
    if runs and max(runs) > HELPER_MAX:
        return "__asm block of %d instructions" % max(runs)
    if review and runs and (len(runs) > 3 or sum(runs) * 2 > n):
        return "review: %d helper-sized __asm blocks, %d asm of %d lines" % (len(runs), sum(runs), n)
    return None


def transcribed(src, review=False):
    """{va (8 hex): reason} for the transcribed functions of one source file (cached per path)."""
    src = os.path.abspath(src)
    key = (src, review)
    if key not in _cache:
        out = {}
        if os.path.isfile(src):   # some src/game "<obj>.cpp" names are directories of a split object
            parts = _MARK.split(open(src, errors="ignore").read())
            for i in range(1, len(parts), 2):
                r = why(parts[i + 1], review)
                if r:
                    out[parts[i].lower().zfill(8)] = r
        _cache[key] = out
    return _cache[key]


def _rows(path, manifest):
    if not os.path.exists(path):
        return set()
    out = set()
    for l in open(path, errors="ignore"):
        p = l.split("#", 1)[0].split()
        va = (p[2] if manifest else p[0]) if len(p) >= (3 if manifest else 1) else ""
        if re.fullmatch(r"(0x)?[0-9a-fA-F]{6,8}", va):
            out.add(va.lower().removeprefix("0x").zfill(8))
    return out


def main(argv):
    all_rows, review = "--all-rows" in argv, "--review" in argv
    args = [a for a in argv if a not in ("--all-rows", "--review")]
    units = []  # (label, [sources], bookkeeping dir)
    if not args:
        args = sorted(os.path.basename(d) for d in glob.glob(os.path.join(ROOT, "match/slices/*")))
        args += sorted(os.path.relpath(f, ROOT) for f in glob.glob(os.path.join(ROOT, "src/game/**/*.cpp"), recursive=True))
    for a in args:
        if a.endswith((".cpp", ".c")) and os.path.basename(os.path.dirname(os.path.abspath(os.path.join(ROOT, a)))).startswith("s") \
                and os.path.abspath(os.path.join(ROOT, a)).startswith(os.path.join(ROOT, "match", "slices") + os.sep):
            # a slice source: its bookkeeping is the slice directory. commit_slice.sh passes the .cpp path, which the
            # branch below took for a src/game TU (bookkeeping in <file minus .cpp>/), found no rows and always
            # passed: s00b0f270 committed two whole-function x87 transcriptions (fix24, 2026-10-24)
            f = os.path.abspath(os.path.join(ROOT, a))
            units.append((a, [f], os.path.dirname(f)))
        elif a.endswith(".cpp"):
            f = os.path.join(ROOT, a)
            units.append((a, [f], f[:-4]))
        else:
            d = os.path.join(ROOT, "match/slices", a)
            units.append((a, glob.glob(os.path.join(d, "*.cpp")), d))
    hits = 0
    for label, srcs, d in units:
        kinds = {va: "manifest" for va in _rows(os.path.join(d, "manifest.txt"), True)}
        if all_rows:
            for va in _rows(os.path.join(d, "nonmatching.txt"), False):
                kinds.setdefault(va, "nonmatching")
        for s in srcs:
            for va, r in sorted(transcribed(s, review).items()):
                if va in kinds:
                    print("%s %s %s %s" % (label, va, kinds[va], r))
                    hits += 1
    return 1 if hits else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
