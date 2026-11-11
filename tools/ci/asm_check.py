#!/usr/bin/env python3
"""List the inline assembly a pull request adds: `__asm` / `_asm` blocks, `_emit` / `__emit`, `__declspec(naked)`.

usage: asm_check.py BASE_REF HEAD_REF
       prints each added line (file:line) that contains inline assembly in the contribution paths; exit 1 if any.

Since 2026-11-11 no inline assembly is merged without a maintainer's explicit approval: the byte-match workflow fails
on any such line unless the pull request carries the `asm-approved` label, which only maintainers can set.  A
contributor who thinks a short helper is the only faithful spelling asks for it in the pull request body
(`asm-override: <why>`, AGENTS.md).  Comments are ignored.
"""
import re, subprocess, sys

ALLOWED = ("src/game/", "match/slices/", "match/include/")
SOURCE = (".cpp", ".cc", ".c", ".h", ".hpp", ".inl")
ASM = re.compile(r"\b__?asm\b|\b__?emit\b|__declspec\s*\(\s*naked\s*\)")


def strip_comment(line, in_block):
    out, i = "", 0
    while i < len(line):
        if in_block:
            j = line.find("*/", i)
            if j < 0:
                return out, True
            i, in_block = j + 2, False
        elif line.startswith("//", i):
            break
        elif line.startswith("/*", i):
            in_block, i = True, i + 2
        else:
            out += line[i]; i += 1
    return out, in_block


def main():
    base, head = sys.argv[1], sys.argv[2]
    mb = subprocess.run(["git", "merge-base", base, head], capture_output=True, text=True, check=True).stdout.strip()
    diff = subprocess.run(["git", "diff", "-U0", "--no-renames", mb, head, "--", *ALLOWED], capture_output=True,
                          text=True, check=True).stdout
    hits, path, line_no, in_block = [], None, 0, False
    for l in diff.split("\n"):
        if l.startswith("+++ "):
            path = l[6:] if l.startswith("+++ b/") and l.endswith(SOURCE) else None; in_block = False
        elif l.startswith("@@"):
            m = re.search(r"\+(\d+)", l); line_no = int(m.group(1)) if m else 0
        elif l.startswith("+") and path:
            code, in_block = strip_comment(l[1:], in_block)
            if ASM.search(code):
                hits.append("%s:%d: %s" % (path, line_no, l[1:].strip()))
            line_no += 1
    for h in hits:
        print(h)
    return 1 if hits else 0


if __name__ == "__main__":
    sys.exit(main())
