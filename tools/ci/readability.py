#!/usr/bin/env python3
"""Readability counters for a pull request: the machine-shaped spots in source that matches retail's bytes.

usage: tools/ci/readability.py BASE_REF HEAD_REF [--json OUT]
       prints the counts before and after per category and one line per function whose count changed; exit 1 if a
       function that exists on the base branch now has more (the workflow only turns that into a warning).
       tools/ci/readability.py --count FILE...   prints each file's counts.

Byte-exact source can still read like the machine code it came from. More matching functions matter far more than
fewer of these, so nothing fails on them (decision 2026-11-20; widened from byte offsets alone on 2026-11-28, after lifted code showed that source with
few offsets can still be machine-shaped), but a pull request that lowers them counts as a
cleanup: the "Require a new byte-exact function" step accepts it in place of a new match (every function that matched
before must still match), and the site credits each function it lowers as "made readable".

What counts, outside comments and string literals (each is one point):
  offsets  raw pointer arithmetic where the code should name a member: a pointer cast applied to `name + N`
           (`*(int*)(p + 4)`, `*(int*)((char*)(int)p + 4)`, `(Foo*)(self + 0x10)`), a pointer cast of a name indexed
           by a literal (`((int*)p)[3]`), a byte view of `this` (`(char*)this`), a byte offset from a global's address
           (`(char*)&g_1483f74 + 0x126c`).
  casts    C-style casts to a built-in or pointer type (not `(void)x`), and reinterpret_cast: `(int)x`, `(unsigned char*)p`,
           `(Foo*)p`. Real types make most of them unnecessary.
  names    placeholder names by address or by tool: FUN_/DAT_/sub_/LAB_/PTR_/off_/g_<address>, lift2il's stand-in
           types (`C_00a8c440`, `il2c_vc0`), tidy64's `VObject` and calls of placeholder virtuals (`->Unk_0C()`, lift2il's `->s12()`), address-suffixed stand-in classes
           (`cExpression_s0083_d3d0`).
  locals   machine variable names: lift2il's `t1001`, `v_l16`, `edx_unused`; Ghidra's `param_1`, `local_10`,
           `iVar1`, `uStack_8`, `in_ECX`, `extraout_EAX`, `unaff_ESI`.
  protos   functions declared without parameter types: `void FUN_00abcdef(...);`.

A function's source runs from its `// @ 0x<address>` marker to the next marker; what comes before the first marker
(includes, declarations) is the file's preamble. A pull request is a cleanup when the total over the changed files
falls and no function or preamble that existed before rises. Functions are compared with themselves across files, so
moving a function from a lifted file into its hand-written home and deleting the lifted file is fine.
Macros and helper functions that hide these are not seen; review catches those, and renaming `t1001` to `x1001` is
not a cleanup.
"""
import json, re, subprocess, sys

ALLOWED = ("src/game/", "match/slices/", "match/include/")
EXTS = (".cpp", ".h", ".hpp", ".inl", ".c")

_NUM = r"(?:0[xX][0-9a-fA-F]+|\d+)[uUlL]*"
_TYPE = r"(?:const\s+|volatile\s+|unsigned\s+|signed\s+|struct\s+|class\s+)*[A-Za-z_][\w:]*(?:\s*<[^<>()]*>)?(?:\s*const)?"
_PTR = r"(?:\s*\*\s*(?:const\s*)?)+"
_CAST = r"\(\s*" + _TYPE + _PTR + r"\)"
_SCALAR = r"(?:const\s+)?(?:unsigned\s+|signed\s+)?(?:__int64|int|char|short|long|float|double|bool|void|u?int(?:8|16|32|64)_t|uintptr_t|intptr_t|u8|u16|u32|u64|s8|s16|s32|BYTE|WORD|DWORD|UINT|uint|ulong32)"
_ANYCAST = r"\(\s*(?:" + _SCALAR + r"\s*\**|" + _TYPE + _PTR + r")\s*\)\s*"
_BYTECAST = r"(?:\(\s*(?:const\s+)?(?:unsigned\s+|signed\s+)?(?:char|uint8_t|int8_t|BYTE|byte|u8)\s*\*\s*\)\s*)"
OFFSETS = [
    # (T*)(x + N), (T*)((char*)x + N), (T*)((char*)(int)x + N), (T*)(x->y + N)
    re.compile(_CAST + r"\s*\(\s*(?:" + _ANYCAST + r")*\(?\s*[A-Za-z_][\w.>\-]*\s*\)?\s*[+-]\s*" + _NUM + r"\s*\)"),
    # ((T*)x)[N]
    re.compile(r"\(\s*" + _CAST + r"\s*[A-Za-z_]\w*\s*\)\s*\[\s*" + _NUM + r"\s*\]"),
    # (char*)this, reinterpret_cast<char*>(this)
    re.compile(_BYTECAST + r"\(?\s*this\b"),
    re.compile(r"reinterpret_cast\s*<\s*(?:const\s+)?(?:unsigned\s+)?(?:char|uint8_t|BYTE)\s*\*\s*>\s*\(\s*this\s*\)"),
    # (char*)&g_1483f74 + 0x126c
    re.compile(_BYTECAST + r"&\s*[A-Za-z_][\w:]*\s*[+-]\s*" + _NUM),
]
CATEGORIES = {
    "offsets": OFFSETS,
    # a cast is followed by its operand; `(int)` in a declaration such as `void f(int)` is not
    "casts": [re.compile(r"(?<![\w)\]])\((?!\s*void\s*\))\s*(?:" + _SCALAR + r"\s*\**|" + _TYPE + _PTR + r")\s*\)\s*(?=[\w(&*!~\-\"'])"),
              re.compile(r"\breinterpret_cast\s*<")],
    "names": [re.compile(r"\b(?:FUN|DAT|sub|LAB|PTR|off|g|unk|UNK)_[0-9A-Fa-f]{6,8}\b"),
              re.compile(r"\bC_[0-9a-f]{8}\b"), re.compile(r"\bil2c_\w+"),
              re.compile(r"\bVObject\d*\b"), re.compile(r"(?:->|\.)\s*(?:Unk_[0-9A-F]{2,3}|s\d{1,3})\s*\("),
              re.compile(r"\b[A-Za-z]\w*_s[0-9a-f]{4}_[0-9a-f]{4}\b")],
    "locals": [re.compile(r"\bt1\d{3}\b"), re.compile(r"\bv_l\d+\w*"), re.compile(r"\bedx_unused\b"),
               re.compile(r"\bparam_\d+\b"), re.compile(r"\blocal_[0-9a-f]+\b"),
               re.compile(r"\b(?:[a-z]{1,3})Var\d+\b"), re.compile(r"\b[a-z]{0,3}Stack_?[0-9a-f]+\b"),
               re.compile(r"\b(?:in|extraout|unaff)_[A-Z]\w*")],
    "protos": [re.compile(r"\b[A-Za-z_]\w*\s*\(\s*\.\.\.\s*\)\s*;")],
}
_STRIP = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)


def _strip(text):
    return _STRIP.sub(lambda m: " " if m.group(0)[0] in "/" else '""', text)


def counts(text, stripped=False):
    t = text if stripped else _strip(text)
    return {k: sum(len(p.findall(t)) for p in ps) for k, ps in CATEGORIES.items()}


def count(text):
    return sum(counts(text).values())


def count_offsets(text):
    return counts(text)["offsets"]


_MARKER = re.compile(r"^[ \t]*//[ \t]*@[ \t]*0x([0-9a-fA-F]{6,8})\b", re.M)


def per_function(text, total=True):
    """{address: count in that function's source} for every function marker in `text` (the preamble before the
    first marker belongs to no function). total=False gives {address: {category: n}}."""
    out = {}
    ms = list(_MARKER.finditer(text))
    for i, m in enumerate(ms):
        end = ms[i + 1].start() if i + 1 < len(ms) else len(text)
        va = int(m.group(1), 16)
        c = counts(text[m.end():end])
        prev = out.get(va) or {k: 0 for k in CATEGORIES}
        out[va] = {k: prev[k] + c[k] for k in c}
    return {v: sum(c.values()) for v, c in out.items()} if total else out


def regions(text, path):
    """{key: {category: n}}: each function by address, and this file's preamble."""
    ms = list(_MARKER.finditer(text))
    out = {("pre", path): counts(text[:ms[0].start()] if ms else text)}
    for va, c in per_function(text, total=False).items():
        out[("fn", va)] = c
    return out


def git(*args):
    return subprocess.run(["git", *args], capture_output=True, text=True, errors="replace")


def show(rev, path):
    r = git("show", "%s:%s" % (rev, path))
    return r.stdout if r.returncode == 0 else None


def wanted(path):
    return path.startswith(ALLOWED) and path.endswith(EXTS)


def _add(acc, reg):
    for k, c in reg.items():
        a = acc.setdefault(k, {x: 0 for x in CATEGORIES})
        for x in c:
            a[x] += c[x]


def compare(base, head):
    mb = git("merge-base", base, head).stdout.strip() or base
    out = git("diff", "--name-status", "-M", mb, head, "--", *ALLOWED).stdout.splitlines()
    before, after, files = {}, {}, []
    for line in out:
        parts = line.split("\t")
        st, paths = parts[0], parts[1:]
        old, new = paths[0], paths[-1]
        b = show(mb, old) if not st.startswith("A") and wanted(old) else None
        a = show(head, new) if not st.startswith("D") and wanted(new) else None
        if b is None and a is None:
            continue
        if b is not None:
            _add(before, regions(b, old))
        if a is not None:
            _add(after, regions(a, new))
        files.append({"path": new if a is not None else old, "before": count(b) if b else 0, "after": count(a) if a else 0,
                      "new": b is None})
    zero = {x: 0 for x in CATEGORIES}
    rows = []
    for k in sorted(set(before) | set(after), key=lambda k: (k[0], str(k[1]))):
        bt, at = sum(before.get(k, zero).values()), sum(after.get(k, zero).values())
        if bt != at:
            rows.append({"key": "0x%08x" % k[1] if k[0] == "fn" else "%s (declarations)" % k[1],
                         "before": bt, "after": at, "existed": k in before})
    increased = [r for r in rows if r["existed"] and r["after"] > r["before"]]
    cat_b = {x: sum(c[x] for c in before.values()) for x in CATEGORIES}
    cat_a = {x: sum(c[x] for c in after.values()) for x in CATEGORIES}
    tb, ta = sum(cat_b.values()), sum(cat_a.values())
    return {"files": files, "changed": rows, "increased": increased, "categories_before": cat_b,
            "categories_after": cat_a, "before": tb, "after": ta, "cleanup": ta < tb and not increased}


def main():
    args = sys.argv[1:]
    if args and args[0] == "--count":
        for f in args[1:]:
            c = counts(open(f, encoding="utf-8", errors="replace").read())
            print("%5d  %s  %s" % (sum(c.values()), " ".join("%s %d" % kv for kv in c.items()), f))
        return
    out = None
    if "--json" in args:
        i = args.index("--json"); out = args[i + 1]; del args[i:i + 2]
    if len(args) != 2:
        sys.exit(__doc__)
    r = compare(*args)
    if out:
        json.dump(r, open(out, "w"), indent=1)
    print("Readability counters in the changed files: %d before, %d after." % (r["before"], r["after"]))
    for x in CATEGORIES:
        if r["categories_before"][x] or r["categories_after"][x]:
            print("  %-8s %5d -> %d" % (x, r["categories_before"][x], r["categories_after"][x]))
    for c in r["changed"]:
        tag = "new" if not c["existed"] else ("MORE" if c["after"] > c["before"] else "fewer")
        print("  %-6s %4d -> %-4d %s" % (tag, c["before"], c["after"], c["key"]))
    sys.exit(1 if r["increased"] else 0)


if __name__ == "__main__":
    main()
