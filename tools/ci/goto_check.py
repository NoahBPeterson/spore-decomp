#!/usr/bin/env python3
"""No new gotos: fail a pull request that raises any function's `goto` count.

usage: goto_check.py BASE_REF HEAD_REF
       prints each function (by its `// @ 0x<address>` marker) or file preamble whose goto count rose; exit 1 if any.

Since 2026-11-28 `goto` is not accepted in the contribution paths (the maintainer's call: "the closest thing to a red
line"). Existing gotos are being removed; until they are all gone this is a ratchet. Counts are per function, so
a function moved between files is compared with itself, removing gotos always passes, and nothing can add one: a new
match whose source has a goto fails, whatever produced it (a lifter's output included). There is no override label.
Rewrite the control flow (early return, break/continue, a loop, if/else); if no goto-free source matches, the
function stays non-matching. Comments and string literals are ignored.
"""
import os, re, subprocess, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

ALLOWED = ("src/game/", "match/slices/", "match/include/")
EXTS = (".cpp", ".cc", ".c", ".h", ".hpp", ".inl")
GOTO = re.compile(r"\bgoto\b")
_STRIP = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)
_MARKER = re.compile(r"^[ \t]*//[ \t]*@[ \t]*0x([0-9a-fA-F]{6,8})\b", re.M)


def regions(text, path):
    """{key: gotos}: each function by address (from its marker to the next), and the file's preamble."""
    ms = list(_MARKER.finditer(text))
    n = lambda t: len(GOTO.findall(_STRIP.sub(" ", t)))
    out = {("preamble", path): n(text[:ms[0].start()] if ms else text)}
    for i, m in enumerate(ms):
        end = ms[i + 1].start() if i + 1 < len(ms) else len(text)
        k = ("function", int(m.group(1), 16))
        out[k] = out.get(k, 0) + n(text[m.end():end])
    return out


def git(*a):
    return subprocess.run(["git", *a], capture_output=True, text=True, errors="replace")


def show(rev, path):
    r = git("show", "%s:%s" % (rev, path))
    return r.stdout if r.returncode == 0 else None


def compare(base, head):
    mb = git("merge-base", base, head).stdout.strip() or base
    before, after = {}, {}
    for line in git("diff", "--name-status", "-M", mb, head, "--", *ALLOWED).stdout.splitlines():
        st, *paths = line.split("\t")
        old, new = paths[0], paths[-1]
        for rev, p, acc, skip in ((mb, old, before, st.startswith("A")), (head, new, after, st.startswith("D"))):
            if skip or not p.endswith(EXTS):
                continue
            t = show(rev, p)
            if t is not None:
                for k, v in regions(t, p).items():
                    acc[k] = acc.get(k, 0) + v
    rose = [(k, before.get(k, 0), v) for k, v in after.items() if v > before.get(k, 0)]
    return rose, sum(before.values()), sum(after.values())


def main():
    rose, b, a = compare(sys.argv[1], sys.argv[2])
    for (kind, k), was, now in sorted(rose, key=lambda r: str(r[0])):
        where = "0x%08x" % k if kind == "function" else "%s (outside any function)" % k
        print("%s: %d goto%s, was %d" % (where, now, "" if now == 1 else "s", was))
    print("gotos in the changed files: %d before, %d after" % (b, a), file=sys.stderr)
    return 1 if rose else 0


if __name__ == "__main__":
    sys.exit(main())
