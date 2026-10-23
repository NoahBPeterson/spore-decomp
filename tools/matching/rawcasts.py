#!/usr/bin/env python3
"""rawcasts.py <file|dir>... [--total]  — count raw-offset field accesses in C++ source.

A raw-offset access is byte arithmetic on a char pointer, `(char*)p + 0x5fc`, the shape of
`*(u32*)((char*)p + 0x5fc)`: a field read or written without naming it. docs/matching.md ("Name every field you
touch") asks for named members instead; commit_slice.sh reports this count so a slice that adds casts is visible.
Prints "<count> <file>" per file (files with none are left out unless --all) and a total.
"""
import os, re, sys

CAST = re.compile(r"\(\s*(?:const\s+)?(?:unsigned\s+|signed\s+)?char\s*\*\s*\)\s*")
OFFSET = re.compile(r"\s*\+\s*(?:0x[0-9a-fA-F]+|\d+)\b")
MEMBER = re.compile(r"\w+(?:\s*(?:->|\.)\s*\w+)*")


def raw_offsets(src):
    """Count `(char*)<operand> + <constant>`, where the operand is a name (with ->/. members) or a balanced
    parenthesised expression of any depth."""
    n = 0
    for m in CAST.finditer(src):
        i = m.end()
        if i < len(src) and src[i] == "(":
            depth = 0
            while i < len(src):
                depth += {"(": 1, ")": -1}.get(src[i], 0)
                i += 1
                if depth == 0:
                    break
        else:
            mm = MEMBER.match(src, i)
            if not mm:
                continue
            i = mm.end()
        if OFFSET.match(src, i):
            n += 1
    return n


COMMENT = re.compile(r"//[^\n]*|/\*.*?\*/", re.S)


def count(path):
    src = COMMENT.sub("", open(path, errors="replace").read())
    return raw_offsets(src)


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    if not args:
        sys.exit(__doc__)
    files = []
    for a in args:
        if os.path.isdir(a):
            for d, _sub, fs in os.walk(a):
                files += [os.path.join(d, f) for f in fs if f.endswith((".cpp", ".c", ".h", ".hpp", ".inl"))]
        elif os.path.isfile(a):
            files.append(a)
    total = 0
    for f in sorted(files):
        n = count(f)
        total += n
        if n or "--all" in sys.argv:
            if "--total" not in sys.argv:
                print("%d %s" % (n, f))
    print("total %d in %d files" % (total, len(files)))


if __name__ == "__main__":
    main()
