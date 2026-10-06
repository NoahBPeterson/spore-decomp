#!/usr/bin/env python3
"""Build EA middleware from local clones with Spore's compiler and find byte-exact matches in Spore.

usage: build_ea_libs.py {eathread,b5rw} [--match] [--emit]
  eathread  EAThread (github.com/BurnoutDecomp/EAThread, a fork of electronicarts/EAThread)
            cloned at work/ext/gh_EAThread
  b5rw      BurnoutDecomp reconstructions of RenderWare 4 (vendor/renderware/src) and EATech
            (src/SDKs/EATech/{eathread,rwcore,rw}) from github.com/BurnoutDecomp/b5-decomp,
            sparse-cloned at work/ext/gh_b5
  --match   run tools/matching/libmatch.py + libresolve.py against work/SporeApp.analysis.bin
  --emit    append the uniquely placed matches to symbols/lib_names.txt as lib_<target>:: entries
            (skipping addresses already listed), so tools/status.py treats them as third-party

Both compile against the ~2010 EABase and coreallocator from the EAWebKit bundle
(work/ext/EAWebKitSupportPackages, see THIRD_PARTY.md) through tools/third_party/compat, which
supplies the newer EABase macros and VS2008 stand-ins for C++11 headers. Nothing is fetched or
committed from the upstream projects: sources stay in work/ (git-ignored), and the small source
patches below are applied to copies under work/oss.
"""
import argparse, csv, glob, os, re, shutil, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
W = lambda *p: os.path.join(ROOT, *p)
win = lambda p: "Z:" + os.path.abspath(p).replace("/", "\\")
COMPAT = W("tools/third_party/compat")
PKG = W("work/ext/EAWebKitSupportPackages")
EABASE = os.path.join(PKG, "EABaseEAWebKit/local/include/Common")
COREALLOC = os.path.join(PKG, "coreallocatorEAWebKit/local/include")
FLAGS = ["/O2", "/MD", "/GS-", "/GR-", "/TP"]
DEFS = ["/FI" + win(os.path.join(COMPAT, "eabase_compat.h")), "/DWIN32", "/D_WIN32", "/DNDEBUG",
        "/D_WIN32_WINNT=0x0501", "/DWINVER=0x0501"]
LABEL = {"eathread": "EA EAThread (BSD; BurnoutDecomp fork)",
         "b5rw": "BurnoutDecomp RenderWare/EATech reconstruction (license assumed EA-style BSD, see THIRD_PARTY.md)"}

# VS2008 has no `auto` type deduction: three declarations around recent Win32 APIs in EAThread's PC code.
EATHREAD_PATCHES = [("auto opResult = ::SetThreadAffinityMask", "DWORD_PTR opResult = ::SetThreadAffinityMask"),
                    ("auto pSetThreadDescription = (SetThreadDescription)",
                     "SetThreadDescription pSetThreadDescription = (SetThreadDescription)"),
                    ("auto result = SetThreadPriorityBoost", "BOOL result = SetThreadPriorityBoost")]


def strip_make_thread(header_text):
    """Remove EAThread's C++14 MakeThread lambda helper (not needed, not compilable with VS2008)."""
    i = header_text.find("template <typename F>\n\t\tauto MakeThread")
    if i < 0:
        return header_text
    k, depth = header_text.index("{", i), 0
    while True:
        depth += {"{": 1, "}": -1}.get(header_text[k], 0)
        if depth == 0 and header_text[k] == "}":
            break
        k += 1
    return header_text[:i] + "// MakeThread (C++14) removed for VS2008 by tools/third_party/build_ea_libs.py\n" + header_text[k + 1:]


def compile_all(srcs, inc, out, rel_to):
    os.makedirs(out, exist_ok=True)
    ok, fails = 0, []
    for s in srcs:
        obj = os.path.join(out, os.path.relpath(s, rel_to).replace("/", "_")[:-4] + ".obj")
        r = subprocess.run([W("tools/matching/cl.sh"), "/nologo", "/c", *FLAGS, *DEFS, *("/I" + win(i) for i in inc),
                            "/Fo" + win(obj), win(s)], capture_output=True, text=True)
        if r.returncode == 0 and os.path.exists(obj):
            ok += 1
        else:
            fails.append((os.path.relpath(s, rel_to), next((l.strip() for l in (r.stdout + r.stderr).splitlines() if "error" in l), "?")))
    print("compiled %d / %d -> %s" % (ok, len(srcs), os.path.relpath(out, ROOT)))
    for f, e in fails:
        print("  FAIL %s: %s" % (f, e[-140:]))


def build_eathread():
    src = W("work/ext/gh_EAThread")
    work = W("work/oss/eathread_src")
    shutil.rmtree(work, ignore_errors=True)
    shutil.copytree(os.path.join(src, "source"), os.path.join(work, "source"))
    os.makedirs(os.path.join(work, "include/eathread"), exist_ok=True)
    with open(os.path.join(src, "include/eathread/eathread_thread.h")) as f:
        hdr = strip_make_thread(f.read())
    with open(os.path.join(work, "include/eathread/eathread_thread.h"), "w") as f:
        f.write(hdr)
    for p in glob.glob(os.path.join(work, "source/pc/*.cpp")):
        t = open(p, encoding="latin-1").read()
        for a, b in EATHREAD_PATCHES:
            t = t.replace(a, b)
        open(p, "w", encoding="latin-1").write(t)
    srcs = sorted(glob.glob(os.path.join(work, "source/*.cpp")) + glob.glob(os.path.join(work, "source/pc/*.cpp")))
    srcs = [s for s in srcs if "win64" not in s and not s.endswith("deprecated.cpp")]
    inc = [os.path.join(work, "include"), os.path.join(COMPAT, "include"), os.path.join(src, "include"), EABASE]
    compile_all(srcs, inc, W("work/oss/eathread_obj"), work)
    return W("work/oss/eathread_obj")


def build_b5rw():
    b5 = W("work/ext/gh_b5")
    dirs = ["src/SDKs/EATech/eathread", "src/SDKs/EATech/rwcore", "src/SDKs/EATech/rw", "vendor/renderware/src"]
    srcs = sorted(s for d in dirs for s in glob.glob(os.path.join(b5, d, "**", "*.cpp"), recursive=True)
                  if "embed_check" not in s)
    inc = [os.path.join(COMPAT, "include"), os.path.join(b5, "vendor/renderware/include"), os.path.join(b5, "src"),
           os.path.join(b5, "src/SDKs/EATech/include"), os.path.join(b5, "src/SDKs/EATech"), EABASE, COREALLOC]
    compile_all(srcs, inc, W("work/oss/b5rw_obj"), b5)
    return W("work/oss/b5rw_obj")


def match(target, objdir):
    img = W("work/SporeApp.analysis.bin")
    out = W("work/oss/%s_matches.csv" % target)
    subprocess.run([sys.executable, W("tools/matching/libmatch.py"), img, W("work/oss/%s_raw.csv" % target), objdir], check=True)
    subprocess.run([sys.executable, W("tools/matching/libresolve.py"), img, out, objdir], check=True)
    return out


def emit(target, csv_path):
    listed = set()
    lib_names = W("symbols/lib_names.txt")
    for line in open(lib_names):
        p = line.split("#", 1)[0].split()
        if p:
            listed.add(int(p[0], 16))
    rows, seen = [], set()
    for r in csv.DictReader(open(csv_path)):
        va = int(r["va"], 16)
        if r["status"] != "unique" or va in listed or va in seen:
            continue
        seen.add(va)
        rows.append("%08x lib_%s::%s  # lib %s byte-exact from %s" % (va, target, r["name"], r["obj"], LABEL[target]))
    with open(lib_names, "a") as f:
        for line in sorted(rows):
            f.write(line + "\n")
    print("appended %d lib_%s entries to symbols/lib_names.txt" % (len(rows), target))


if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("target", choices=["eathread", "b5rw"])
    ap.add_argument("--match", action="store_true")
    ap.add_argument("--emit", action="store_true")
    a = ap.parse_args()
    objdir = build_eathread() if a.target == "eathread" else build_b5rw()
    if a.match or a.emit:
        out = match(a.target, objdir)
        if a.emit:
            emit(a.target, out)
