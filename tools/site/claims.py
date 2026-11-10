#!/usr/bin/env python3
"""Write claims.txt: every function address that an open pull request works on, one claim per line.

A pull request claims the functions it names: addresses in its title, `// @ 0x...` markers it adds, and the
manifest.txt / nonmatching.txt / partial.txt lines it adds or removes. tools/contrib/task.py reads the published file
(the `claims` branch, written by .github/workflows/claims.yml) to hide functions somebody is already working on.

  python3 tools/site/claims.py --repo OWNER/NAME --out claims.txt      # needs gh and GH_TOKEN

Standard library only.
"""
import argparse, datetime, json, re, subprocess

ADDR = re.compile(r"0x([0-9a-fA-F]{6,8})\b")
MANIFEST_ROW = re.compile(r"^[+-]\S+\s+\S+\s+([0-9a-fA-F]{8})\b")      # source  symbol  va  [flags]
NOTE_ROW = re.compile(r"^[+-]([0-9a-fA-F]{8})\b")                       # va  diff  reason
MARKER = re.compile(r"^\+\s*//\s*@\s*0x0*([0-9a-fA-F]+)\b")


def gh(*args):
    return subprocess.run(["gh", *args], capture_output=True, text=True, check=True).stdout


def addresses(title, diff):
    out = {int(m, 16) for m in ADDR.findall(title)}
    path = ""
    for line in diff.splitlines():
        if line.startswith("diff --git "):
            path = line.split(" b/", 1)[-1]
            continue
        if line.startswith(("+++", "---")):
            continue
        name = path.rsplit("/", 1)[-1]
        m = (MANIFEST_ROW.match(line) if name == "manifest.txt" else
             NOTE_ROW.match(line) if name in ("nonmatching.txt", "partial.txt") else MARKER.match(line))
        if m:
            out.add(int(m.group(1), 16))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--repo", required=True)
    ap.add_argument("--out", default="claims.txt")
    a = ap.parse_args()
    prs = json.loads(gh("pr", "list", "--repo", a.repo, "--state", "open", "--limit", "1000",
                        "--json", "number,author,title,updatedAt"))
    rows = []
    for p in prs:
        diff = gh("pr", "diff", str(p["number"]), "--repo", a.repo)
        for va in addresses(p["title"], diff):
            rows.append((va, p["number"], (p.get("author") or {}).get("login") or "?", p["updatedAt"][:10]))
    rows.sort()
    now = datetime.datetime.now(datetime.timezone.utc).strftime("%Y-%m-%d %H:%M UTC")
    with open(a.out, "w", encoding="utf-8", newline="\n") as f:
        f.write("# Functions in open pull requests (claims). Generated %s from %d open pull requests.\n" % (now, len(prs)))
        f.write("# A claim lasts while its pull request is open; tools/contrib/task.py treats one with no update for 7 days as stale.\n")
        f.write("# address    pr     author                 last update\n")
        for va, n, who, upd in rows:
            f.write("0x%08x  #%-5d %-22s %s\n" % (va, n, who, upd))
    print("%s: %d claims from %d open pull requests" % (a.out, len(rows), len(prs)))


if __name__ == "__main__":
    main()
