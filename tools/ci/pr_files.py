#!/usr/bin/env python3
"""Bring a pull request's files into a checkout of the base branch, for the byte-match check.

The check runs main's tools (pull_request_target: the workflow and tools/ never come from the pull request), so a
pull request cannot change what checks it.  Only contribution paths are taken from the pull request:
  src/game/**          sources, manifests, nonmatching/partial lists, headers
  match/slices/**      slices still being decompiled
  match/include/**     shared slice headers
Anything else (tools/, .github/, fingerprints, docs, ...) fails the check with a message for a maintainer.

usage: pr_files.py BASE_REF HEAD_REF [--changed-out FILE]
       copies the allowed changed files from HEAD_REF into the work tree, deletes the ones the pull request deleted,
       writes the changed paths to FILE, exit 1 if the pull request touches anything else
"""
import argparse, os, subprocess, sys

ALLOWED = ("src/game/", "match/slices/", "match/include/")


def git(*a):
    return subprocess.run(["git", *a], capture_output=True, text=True, check=True).stdout


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("base")
    ap.add_argument("head")
    ap.add_argument("--changed-out")
    a = ap.parse_args()
    mb = git("merge-base", a.base, a.head).strip()
    rows = [l.split("\t") for l in git("diff", "--name-status", "--no-renames", mb, a.head).splitlines() if l]
    bad = [p for _st, p in rows if not p.startswith(ALLOWED)]
    if bad:
        print("This pull request changes files outside the contribution paths (%s):" % ", ".join(ALLOWED))
        for p in bad:
            print("  " + p)
        print("A maintainer has to review changes to those; split them into their own pull request.")
        return 1
    for st, p in rows:
        if st == "D":
            if os.path.exists(p):
                os.remove(p)
        else:
            os.makedirs(os.path.dirname(p) or ".", exist_ok=True)
            data = subprocess.run(["git", "show", "%s:%s" % (a.head, p)], capture_output=True, check=True).stdout
            open(p, "wb").write(data)
    if a.changed_out:
        open(a.changed_out, "w").write("".join(p + "\n" for _st, p in rows))
    print("%d changed files taken from the pull request" % len(rows))
    return 0


if __name__ == "__main__":
    sys.exit(main())
