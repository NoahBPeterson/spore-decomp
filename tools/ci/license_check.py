#!/usr/bin/env python3
"""Third-party code in a pull request: copied upstream source, and matches of open-source library functions.

usage: license_check.py BASE_REF HEAD_REF --notices    added lines carrying a third-party copyright or license notice
       license_check.py BASE_REF HEAD_REF --oss        added manifest rows for open-source library functions
       prints one line per hit; exit 1 if any.

The open-source libraries Spore links (OpenSSL, zlib, libpng, libjpeg, expat, EA's published EASTL/EAText/EAWebKit
packages) are rebuilt by compiling their published sources, which tools/ci/setup_oss.sh downloads into work/ and
hash-checks (THIRD_PARTY.md). Their source is referenced from there, never copied into the repository: each keeps its
own license, and some (OpenSSL 0.9.8g: the OpenSSL and SSLeay licenses) cannot be combined with this project's
GPL-2.0. Decision 2026-11-20:
  --notices  fails a pull request that adds a line with a third-party copyright or license notice in the contribution
             paths (upstream source pasted in instead of #included from work/). No label overrides it; a maintainer
             changes the rule in a separate pull request if a file really has to be in the repository.
  --oss      lists rows a pull request adds for functions in the "Open-source libraries" module
             (tools/site/modules.json). The workflow fails on them unless a maintainer has put the `oss-reviewed` label
             on the pull request, after checking that each wrapper only #includes the published file from work/.
Comments count for --notices (a pasted license header is a comment); files already on main are not re-checked.
"""
import bisect, json, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ALLOWED = ("src/game/", "match/slices/", "match/include/")
LIBS = "Open-source libraries"
NOTICE = re.compile(
    r"copyright\s*(\(c\)|\xa9|[0-9]{4})|"
    r"all rights reserved|"
    r"general public license|"
    r"permission is hereby granted|"
    r"redistribution and use in source and binary forms|"
    r"licensed under the apache license|"
    r"spdx-license-identifier|"
    r"this product includes (software|cryptographic software) (developed|written) by|"
    r"eay@cryptsoft\.com|openssl project|independent jpeg group|jean-loup gailly|randers-pehrson",
    re.I)
MANIFEST = re.compile(r"(^|/)manifest\.txt$")


def added_lines(base, head):
    """(path, line number, text) for every line the pull request adds in the contribution paths"""
    mb = subprocess.run(["git", "merge-base", base, head], cwd=ROOT, capture_output=True, text=True,
                        check=True).stdout.strip()
    diff = subprocess.run(["git", "diff", "-U0", "--no-renames", mb, head, "--", *ALLOWED], cwd=ROOT,
                          capture_output=True, text=True, check=True, errors="replace").stdout
    path, n = None, 0
    for l in diff.split("\n"):
        if l.startswith("+++ "):
            path = l[6:] if l.startswith("+++ b/") else None
        elif l.startswith("@@"):
            m = re.search(r"\+(\d+)", l); n = int(m.group(1)) if m else 0
        elif l.startswith("+") and path:
            yield path, n, l[1:]
            n += 1


def oss_module():
    d = json.load(open(os.path.join(ROOT, "tools", "site", "modules.json")))
    starts = [int(r[0], 16) for r in d["runs"]]
    def is_oss(va):
        i = bisect.bisect_right(starts, va) - 1
        return i >= 0 and d["modules"][d["runs"][i][1]] == LIBS
    return is_oss


def main():
    if len(sys.argv) != 4 or sys.argv[3] not in ("--notices", "--oss"):
        sys.exit(__doc__)
    base, head, mode = sys.argv[1:]
    hits = []
    if mode == "--notices":
        for path, n, text in added_lines(base, head):
            if NOTICE.search(text):
                hits.append("%s:%d: %s" % (path, n, text.strip()[:160]))
    else:
        is_oss = oss_module()
        for path, n, text in added_lines(base, head):
            p = text.split("#", 1)[0].split()
            if not MANIFEST.search(path) or len(p) < 3:
                continue
            try:
                va = int(p[2], 16)
            except ValueError:
                continue
            if is_oss(va):
                hits.append("%s:%d: %08x %s" % (path, n, va, p[0]))
    for h in hits:
        print(h)
    return 1 if hits else 0


if __name__ == "__main__":
    sys.exit(main())
