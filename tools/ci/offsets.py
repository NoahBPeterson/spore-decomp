#!/usr/bin/env python3
"""Byte offsets in a pull request: raw pointer arithmetic where the code should name a member.

usage: offsets.py BASE_REF HEAD_REF [--json OUT]
       prints a summary and one line per file whose count changed; exit 1 if a file that exists on the base branch
       now has more of them.

Readable source names members (`mpOSData = new (mem) Win32Clipboard(this);`), it does not cast and add a byte
offset (`*(void**)((char*)this + 8) = ...`). The code base still has tens of thousands of these, so instead of a
ban this is a ratchet over the files a pull request changes (decision 2026-11-20):
  - a file that exists on the base branch may not gain any (exit 1; a maintainer's `offsets-approved` label
    overrides it when there really is no member to name);
  - a new file that has some only gets a warning;
  - a pull request that lowers the total and raises no file counts as a cleanup, which the "Require a new
    byte-exact function" step accepts in place of a new match (every function that matched must still match).

What counts, outside comments and string literals:
  - a pointer cast applied to `name + N` / `name - N` with a literal N, dereferenced or not:
    `*(int*)(p + 4)`, `(Foo*)(self + 0x10)`, `*(void**)((char*)this + 8)`;
  - a pointer cast of a name indexed by a literal: `((int*)p)[3]`, `((void**)this)[2]`;
  - a byte-pointer view of `this`: `(char*)this`, `(unsigned char*)this`, `(uint8_t*)this`, `(BYTE*)this`, also
    through `reinterpret_cast`.
An offset from the address of a global (`(char*)&g_1483f74 + 0x126c`) does not count: AGENTS.md asks for that form
when one relocation covers two fields of a global. Macros and helper functions that hide an offset are not seen;
review catches those.
"""
import json, re, subprocess, sys

ALLOWED = ("src/game/", "match/slices/", "match/include/")
EXTS = (".cpp", ".h", ".hpp", ".inl", ".c")

_NUM = r"(?:0[xX][0-9a-fA-F]+|\d+)[uUlL]*"
_TYPE = r"(?:const\s+|volatile\s+|unsigned\s+|signed\s+|struct\s+|class\s+)*[A-Za-z_][\w:]*(?:\s*<[^<>()]*>)?(?:\s*const)?"
_PTR = r"(?:\s*\*\s*(?:const\s*)?)+"
_CAST = r"\(\s*" + _TYPE + _PTR + r"\)"
_BYTECAST = r"(?:\(\s*(?:const\s+)?(?:unsigned\s+|signed\s+)?(?:char|uint8_t|int8_t|BYTE|byte|u8)\s*\*\s*\)\s*)"
PATTERNS = [
    # (T*)(x + N), (T*)((char*)x + N), (T*)(x->y + N): the cast's operand is a parenthesised name +/- literal
    re.compile(_CAST + r"\s*\(\s*" + _BYTECAST + r"?\(?\s*[A-Za-z_][\w.>\-]*\s*\)?\s*[+-]\s*" + _NUM + r"\s*\)"),
    # ((T*)x)[N]
    re.compile(r"\(\s*" + _CAST + r"\s*[A-Za-z_]\w*\s*\)\s*\[\s*" + _NUM + r"\s*\]"),
    # (char*)this, reinterpret_cast<char*>(this)
    re.compile(_BYTECAST + r"\(?\s*this\b"),
    re.compile(r"reinterpret_cast\s*<\s*(?:const\s+)?(?:unsigned\s+)?(?:char|uint8_t|BYTE)\s*\*\s*>\s*\(\s*this\s*\)"),
]
_STRIP = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)


def count(text):
    text = _STRIP.sub(lambda m: " " if m.group(0)[0] in "/" else '""', text)
    return sum(len(p.findall(text)) for p in PATTERNS)


def git(*args):
    return subprocess.run(["git", *args], capture_output=True, text=True, errors="replace")


def file_count(rev, path):
    r = git("show", "%s:%s" % (rev, path))
    return count(r.stdout) if r.returncode == 0 else None


def wanted(path):
    return path.startswith(ALLOWED) and path.endswith(EXTS)


def compare(base, head):
    mb = git("merge-base", base, head).stdout.strip() or base
    out = git("diff", "--name-status", "-M", mb, head, "--", *ALLOWED).stdout.splitlines()
    files = []
    for line in out:
        parts = line.split("\t")
        st, paths = parts[0], parts[1:]
        old, new = (paths[0], paths[-1])
        if st.startswith("D") or not wanted(new):
            if st.startswith("D") and wanted(old):
                files.append({"path": old, "before": file_count(mb, old) or 0, "after": 0, "new": False})
            continue
        before = None if st.startswith("A") else file_count(mb, old)
        files.append({"path": new, "before": before or 0, "after": file_count(head, new) or 0,
                      "new": before is None})
    increased = [f for f in files if not f["new"] and f["after"] > f["before"]]
    new_with = [f for f in files if f["new"] and f["after"] > 0]
    before = sum(f["before"] for f in files)
    after = sum(f["after"] for f in files)
    return {"files": files, "increased": increased, "new_with": new_with, "before": before, "after": after,
            "cleanup": after < before and not increased}


def main():
    args = sys.argv[1:]
    out = None
    if "--json" in args:
        i = args.index("--json"); out = args[i + 1]; del args[i:i + 2]
    if len(args) != 2:
        sys.exit(__doc__)
    r = compare(*args)
    if out:
        json.dump(r, open(out, "w"), indent=1)
    print("Byte offsets in the changed files: %d before, %d after." % (r["before"], r["after"]))
    for f in r["files"]:
        if f["after"] != f["before"]:
            tag = "new file" if f["new"] else ("MORE" if f["after"] > f["before"] else "fewer")
            print("  %-8s %4d -> %-4d %s" % (tag, f["before"], f["after"], f["path"]))
    sys.exit(1 if r["increased"] else 0)


if __name__ == "__main__":
    main()
