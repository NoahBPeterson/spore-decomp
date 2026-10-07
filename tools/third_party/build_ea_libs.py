#!/usr/bin/env python3
"""Build EA middleware from local clones with Spore's compiler and find byte-exact matches in Spore.

usage: build_ea_libs.py {eathread,b5rw,b5more} [--match] [--emit]
  eathread  EAThread (github.com/BurnoutDecomp/EAThread, a fork of electronicarts/EAThread)
            cloned at work/ext/gh_EAThread
  b5rw      BurnoutDecomp reconstructions of RenderWare 4 (vendor/renderware/src) and EATech
            (src/SDKs/EATech/{eathread,rwcore,rw}) from github.com/BurnoutDecomp/b5-decomp,
            sparse-cloned at work/ext/gh_b5
  b5more    the rest of b5-decomp's PC-buildable RenderWare/EATech code, emitted with the same lib_b5rw
            tag: src/vendor/renderware (collision, physics), src/SDKs/EATech/{Apt,AptGlobals.cpp,
            AptRenderLinkStubs.cpp,eajobs,rwcollision,rwmovie,include (Apt, NFSMix, Nicotine, rw, snd)}
            and src/GameShared/GameClasses/RenderWare (minus console-only PS3/ and x360/ subdirs), plus
            b5rw's directories again. These sources are C++11/17, so they are copied to work/oss/b5more_src
            and text-rewritten by downlevel_cxx11() (nested namespaces, enum class, using-aliases,
            constexpr, =default/=delete, hex floats, ...) and compiled with compat/cxx11_compat.h
            force-included; files failing with C2719 (over-aligned by-value parameters) are retried with
            alignas disabled. The sparse checkout must also hold the headers these include:
            src/GameShared/GameClasses/{Core,Development/Log,Graphics,System/Resource},
            src/SDKs/{RenderEngineClub,Packages/Apt} and src/pc/gcm/renderengine.
            libresolve's "unique" also covers short generic bodies folded by /OPT:ICF whose b5 name is a
            coincidence, so b5more --emit filters (see GENERIC_NAME/NOT_IN_SPORE) and re-checks each row
            with cmpobj.py before appending.
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
from concurrent.futures import ThreadPoolExecutor

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


def compile_all(srcs, inc, out, rel_to, extra=(), jobs=6, quiet=False):
    os.makedirs(out, exist_ok=True)

    def one(s):
        obj = os.path.join(out, os.path.relpath(s, rel_to).replace("/", "_")[:-4] + ".obj")
        r = subprocess.run([W("tools/matching/cl.sh"), "/nologo", "/c", *FLAGS, *DEFS, *extra,
                            *("/I" + win(i) for i in inc), "/Fo" + win(obj), win(s)], capture_output=True, text=True)
        if r.returncode == 0 and os.path.exists(obj):
            return None
        return s, next((l.strip() for l in (r.stdout + r.stderr).splitlines() if "error" in l), "?")
    with ThreadPoolExecutor(jobs) as ex:
        fails = [f for f in ex.map(one, srcs) if f]
    if not quiet:
        print("compiled %d / %d -> %s" % (len(srcs) - len(fails), len(srcs), os.path.relpath(out, ROOT)))
        for f, e in fails:
            print("  FAIL %s: %s" % (os.path.relpath(f, rel_to), e[-140:]))
    return [f for f, _ in fails]


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


B5MORE_DIRS = ["src/vendor/renderware/collision", "src/vendor/renderware/physics", "src/SDKs/EATech/Apt",
               "src/SDKs/EATech/AptGlobals.cpp", "src/SDKs/EATech/AptRenderLinkStubs.cpp", "src/SDKs/EATech/eajobs",
               "src/SDKs/EATech/rwcollision", "src/SDKs/EATech/rwmovie", "src/SDKs/EATech/include",
               "src/GameShared/GameClasses/RenderWare",
               # b5rw's directories again: the rewrite rescues files plain b5rw cannot compile
               "src/SDKs/EATech/eathread", "src/SDKs/EATech/rwcore", "src/SDKs/EATech/rw", "vendor/renderware/src"]
CONSOLE_DIRS = ("/PS3/", "/ps3/", "/x360/", "/X360/", "/xenon/")
ATTRIBUTE = re.compile(r"\[\[(?:fallthrough|nodiscard|maybe_unused|noreturn|likely|unlikely)[^\]]*\]\]")
USING_ALIAS = re.compile(r"(?<![\w>])using\s+(\w+)\s*=\s*([^;]+);")
HEX_FLOAT = re.compile(r"\b(0[xX][0-9a-fA-F]*\.?[0-9a-fA-F]*[pP][+-]?\d+)([fFlL]?)")
NESTED_NS = re.compile(r"namespace\s+(\w+(?:::\w+)+)\s*\{")


def _skip_to_brace_match(t, i):
    """Index of the '}' closing the '{' at t[i], skipping comments, string and char literals."""
    depth, n = 0, len(t)
    while i < n:
        c = t[i]
        if t.startswith("//", i):
            i = t.find("\n", i)
            i = n if i < 0 else i
            continue
        if t.startswith("/*", i):
            i = t.find("*/", i) + 2
            continue
        if c in "\"'":
            j = i + 1
            while j < n and t[j] != c:
                j += 2 if t[j] == "\\" else 1
            i = j + 1
            continue
        depth += {"{": 1, "}": -1}.get(c, 0)
        if depth == 0 and c == "}":
            return i
        i += 1
    return -1


def downlevel_cxx11(t):
    """Text-rewrite the C++11/17 syntax the b5-decomp sources use into what VS2008 accepts (with
    compat/cxx11_compat.h covering alignas/static_assert/final/noexcept/alignof by macro)."""
    t = ATTRIBUTE.sub("", t)
    t = HEX_FLOAT.sub(lambda m: repr(float.fromhex(m.group(1))) + m.group(2), t)
    t = re.sub(r"(~\w+\s*\(\s*\))\s*override\b", r"\1", t)  # VS2008 rejects override on destructors
    t = re.sub(r"\benum\s+(?:class|struct)\b", "enum", t)
    t = re.sub(r"(\benum\s+\w+)\s*:\s*[\w:]+\s*;", r"\1;", t)  # opaque enum declaration
    t = USING_ALIAS.sub(lambda m: "typedef %s;" % (m.group(2).replace("(*)", "(*%s)" % m.group(1), 1)
                        if "(*)" in m.group(2) else "%s %s" % (m.group(2).strip(), m.group(1))), t)
    t = re.sub(r"\b(?:static\s+)?(?:inline\s+)?constexpr\b(?=\s+[\w:]+\s+\w+\s*=)",
               lambda m: "static const" if "static" in m.group(0) else "const", t)
    t = re.sub(r"\bconstexpr\b", "inline", t)
    t = re.sub(r"\(\s*\)((?:\s*(?:const|override))*)\s*=\s*default\s*;", r"()\1 {}", t)
    t = re.sub(r"([;{}\n])([^;{}\n]*\([^()]+\)[^;{}\n]*?)=\s*default\s*;", r"\1/* \2= default */", t)
    t = re.sub(r"=\s*delete\s*;", ";", t)
    t = re.sub(r"(\b[A-Za-z_]\w*)\{\}(?=\s*[,{)])", r"\1()", t)  # member{} in init lists
    t = re.sub(r"\breturn\s+([A-Za-z_][\w:]*)\s*\{([^{};]*)\}\s*;", r"{ \1 b5_ret_ = {\2}; return b5_ret_; }", t)
    while True:
        m = NESTED_NS.search(t)
        if not m:
            return t
        parts = m.group(1).split("::")
        close = _skip_to_brace_match(t, m.end() - 1)
        if close < 0:
            return t
        t = (t[:m.start()] + " ".join("namespace %s {" % p for p in parts) + t[m.end():close]
             + "}" * len(parts) + t[close + 1:])


def build_b5more():
    b5 = W("work/ext/gh_b5")
    work = W("work/oss/b5more_src")
    out = W("work/oss/b5more_obj")
    for d in (work, out):
        shutil.rmtree(d, ignore_errors=True)
    for d in ("src", "vendor/renderware"):
        shutil.copytree(os.path.join(b5, d), os.path.join(work, d))
    for p in glob.glob(os.path.join(work, "**", "*.*"), recursive=True):
        if os.path.splitext(p)[1] in (".h", ".hpp", ".cpp", ".inl", ".c"):
            t = open(p, encoding="latin-1").read()
            n = downlevel_cxx11(t)
            if n != t:
                open(p, "w", encoding="latin-1").write(n)
    inc = [os.path.join(COMPAT, "include"), os.path.join(work, "vendor/renderware/include"), os.path.join(work, "src"),
           os.path.join(work, "src/SDKs/EATech/include"), os.path.join(work, "src/SDKs/EATech"), EABASE, COREALLOC]
    extra = ["/FI" + win(os.path.join(COMPAT, "cxx11_compat.h"))]
    counts = []
    for d in B5MORE_DIRS:
        p = os.path.join(work, d)
        srcs = [p] if p.endswith(".cpp") else glob.glob(os.path.join(p, "**", "*.cpp"), recursive=True)
        srcs = sorted(s for s in srcs if "embed_check" not in s and not any(c in s for c in CONSOLE_DIRS))
        print("== %s" % d)
        fails = compile_all(srcs, inc, out, work, extra)
        # VS2008 cannot pass __declspec(align(16)) types by value (C2719): retry without alignas
        fixed = len(fails) - len(compile_all(fails, inc, out, work, extra + ["/DB5_NO_ALIGNAS"], quiet=True))
        if fixed:
            print("  (+%d more compiled with alignas disabled)" % fixed)
        counts.append((d, len(srcs) - len(fails) + fixed, len(srcs)))
    print("summary: " + ", ".join("%s %d/%d" % c for c in counts))
    return out


def match(target, objdir):
    img = W("work/SporeApp.analysis.bin")
    out = W("work/oss/%s_matches.csv" % target)
    subprocess.run([sys.executable, W("tools/matching/libmatch.py"), img, W("work/oss/%s_raw.csv" % target), objdir], check=True)
    subprocess.run([sys.executable, W("tools/matching/libresolve.py"), img, out, objdir], check=True)
    return out


# b5more --emit drops: compiler-generated/STL bodies (identical across libraries, so /OPT:ICF folds
# Spore's own copies into them), Apt (Spore has none of its strings), Criterion's Cgs* game classes and addresses that already carry
# a name in symbols/pdb_names.json or a symbols/slices claim. Every kept row is re-checked with cmpobj.
GENERIC_NAME = re.compile(r"^\?\?_[GE]|DeletingDestructor@|@std@@|^__unwindfunclet|^__ehhandler|^__catch")
NOT_IN_SPORE = re.compile(r"Apt|DOGMA|Cgs")  # matched against name + obj: Apt, Criterion's own game classes


def named_elsewhere():
    named = set(int(k, 16) for k in __import__("json").load(open(W("symbols/pdb_names.json"))))
    for p in glob.glob(W("symbols/slices/*.txt")):
        for line in open(p):
            f = line.split()
            if f and re.fullmatch(r"[0-9a-f]{8}", f[0]):
                named.add(int(f[0], 16))
    return named


def emit(target, csv_path, strict=False):
    listed = set()
    lib_names = W("symbols/lib_names.txt")
    for line in open(lib_names):
        p = line.split("#", 1)[0].split()
        if p:
            listed.add(int(p[0], 16))
    named = named_elsewhere() if strict else set()
    objdir = os.path.join(os.path.dirname(csv_path), os.path.basename(csv_path).replace("_matches.csv", "_obj"))
    rows, seen = [], set()
    for r in csv.DictReader(open(csv_path)):
        va = int(r["va"], 16)
        if r["status"] != "unique" or va in listed or va in seen:
            continue
        if strict:
            why = ("generic" if GENERIC_NAME.search(r["name"]) else "not-in-spore" if NOT_IN_SPORE.search(r["name"] + r["obj"])
                   else "named-elsewhere" if va in named else None)
            if not why:
                ok = subprocess.run([sys.executable, W("tools/matching/cmpobj.py"), W("work/SporeApp.analysis.bin"),
                                     os.path.join(objdir, r["obj"]), r["name"], r["va"], "--len", r["len"], "--quiet"],
                                    capture_output=True).returncode == 0
                why = None if ok else "cmpobj-mismatch"
            if why:
                print("  skip %s %s (%s)" % (r["va"], r["name"], why))
                continue
        seen.add(va)
        rows.append("%08x lib_%s::%s  # lib %s byte-exact from %s" % (va, target, r["name"], r["obj"], LABEL[target]))
    with open(lib_names, "a") as f:
        for line in sorted(rows):
            f.write(line + "\n")
    print("appended %d lib_%s entries to symbols/lib_names.txt" % (len(rows), target))


if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("target", choices=["eathread", "b5rw", "b5more"])
    ap.add_argument("--match", action="store_true")
    ap.add_argument("--emit", action="store_true")
    a = ap.parse_args()
    objdir = {"eathread": build_eathread, "b5rw": build_b5rw, "b5more": build_b5more}[a.target]()
    tag = "b5rw" if a.target == "b5more" else a.target
    if a.match or a.emit:
        out = match(a.target, objdir)
        if a.emit:
            emit(tag, out, strict=a.target == "b5more")
