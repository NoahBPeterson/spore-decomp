#!/usr/bin/env python3
"""Compile the pinned third-party libraries with the era compiler (cl 15.00.30729.01 under wine).

usage: build_faithful.py [lib ...] [-j N] [--no-lib] [--outdir DIR] [--flags "<cl flags>"] [--only REGEX]
Reads third_party/manifest.json; sources come from work/third_party/src (run fetch.py first).
Objects go to work/third_party/obj/<lib>/ and, unless --no-lib, a static library to work/third_party/lib/<lib>.lib
(lib.exe from the same toolchain). --flags replaces the manifest cflags (experiments); --outdir redirects
objects (and disables .lib creation).
"""
import argparse, concurrent.futures as cf, glob, hashlib, json, os, re, shutil, subprocess, sys, time

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
TC = os.path.join(ROOT, "work", "toolchain", "vc9sp1")
WORK = os.path.join(ROOT, "work", "third_party")
SRC = os.path.join(WORK, "src")
CL = os.path.join(ROOT, "tools", "matching", "cl.sh")

def W(p):
    return "Z:" + os.path.abspath(p).replace("/", "\\")

def wine_env():
    env = dict(os.environ)
    env["WINEPREFIX"] = os.path.join(ROOT, "work", "toolchain", "wineprefix")
    env["WINEDEBUG"] = "-all"
    env["WINEPATH"] = W(os.path.join(TC, "VC", "bin"))
    env["LIB"] = ";".join(W(os.path.join(TC, d)) for d in ("VC/lib", "WinSDK/Lib"))
    return env

def load_manifest():
    return json.load(open(os.path.join(ROOT, "third_party", "manifest.json")))

# ---- per-library preparation (generated headers) -------------------------------------------------
def prepare_openssl(lib, srcdir, configure=None):
    """OpenSSL needs a generated crypto/opensslconf.h and include/openssl/*.h links.
    Work in a private copy so the pristine extraction stays untouched."""
    opts = configure if configure is not None else lib["build"]["configure_options"]
    undefs = lib["build"].get("opensslconf_undef", [])
    tag = hashlib.sha1((" ".join(opts) + "|" + " ".join(undefs)).encode()).hexdigest()[:8]
    dst = os.path.join(WORK, "build", lib["extract_dir"] + "-" + tag)
    if not os.path.exists(os.path.join(dst, "include", "openssl", "ssl.h")):
        shutil.rmtree(dst, ignore_errors=True)
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        shutil.copytree(srcdir, dst, symlinks=True)
        subprocess.run(["perl", "Configure", "VC-WIN32"] + opts, cwd=dst, check=True, stdout=subprocess.DEVNULL)
        conf = os.path.join(dst, "crypto", "opensslconf.h")
        txt = open(conf).read()
        for macro in undefs:  # e.g. BN_LLONG: Configure defines it for VC-WIN32, the original build did not
            txt, n = re.subn(r"^#\s*define %s\s*$" % re.escape(macro), "#undef %s" % macro, txt, flags=re.M)
            if n != 1:
                sys.exit("opensslconf.h: expected exactly one '#define %s'" % macro)
        open(conf, "w").write(txt)
        subprocess.run(["make", "links"], cwd=dst, check=True, stdout=subprocess.DEVNULL)
    return dst

def prepare_jpeg(lib, srcdir):
    """jconfig.h is not shipped in 6a: use the repo-provided one (manifest build.jconfig) via a private include dir."""
    inc = os.path.join(WORK, "build", lib["extract_dir"] + "-inc")
    os.makedirs(inc, exist_ok=True)
    shutil.copy(os.path.join(ROOT, lib["build"]["jconfig"]), os.path.join(inc, "jconfig.h"))
    return srcdir

PREPARE = {"openssl": prepare_openssl, "jpeg": prepare_jpeg}

# ---- source discovery / compile ------------------------------------------------------------------
def discover(lib, srcdir):
    b = lib["build"]
    files = []
    if "walk" in b:
        for d in b["walk"]:
            for root, _, fs in os.walk(os.path.join(srcdir, d)):
                files += [os.path.relpath(os.path.join(root, f), srcdir) for f in fs if f.endswith(".c")]
        ex = re.compile(b["exclude_re"])
        files = [f for f in files if not ex.search(f)]
    else:
        for g in b["globs"]:
            files += [os.path.relpath(f, srcdir) for f in glob.glob(os.path.join(srcdir, g))]
        skip = set(b.get("exclude_stems", []))
        files = [f for f in files if os.path.basename(f)[:-2] not in skip]
    return sorted(files)

def objname(rel):
    return re.sub(r"\.c$", "", rel).replace("/", "_") + ".obj"

def compile_one(lib, srcdir, rel, outdir, cflags_override, includes, env):
    b = lib["build"]
    flags = cflags_override or b["cflags"]
    flags = b.get("per_file", {}).get(rel, {}).get("cflags", flags) if not cflags_override else flags
    inc = ["/I" + W(i) for i in includes + [os.path.join(srcdir, os.path.dirname(rel))]]
    out = os.path.join(outdir, objname(rel))
    cmd = [CL, "/nologo", "/c"] + flags.split() + inc + ["/Fo" + W(out), W(os.path.join(srcdir, rel))]
    r = subprocess.run(cmd, env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, cwd=srcdir)
    return rel, r.returncode == 0 and os.path.exists(out), r.stdout.decode("latin1")

def build_lib(name, lib, a, manifest):
    srcdir = os.path.join(SRC, lib["extract_dir"])
    if not os.path.isdir(srcdir):
        sys.exit("%s: %s missing; run tools/third_party/fetch.py" % (name, srcdir))
    prep = lib["build"].get("prepare")
    if prep:
        srcdir = PREPARE[prep](lib, srcdir, a.configure.split() if a.configure is not None else None) if prep == "openssl" else PREPARE[prep](lib, srcdir)
    includes = []
    for i in lib["build"].get("include_dirs", []):
        if i.startswith("@"):  # @<other lib>: its extracted source dir
            includes.append(os.path.join(SRC, manifest["libraries"][i[1:]]["extract_dir"]))
        elif i.startswith("build:"):
            includes.append(os.path.join(WORK, "build", i[6:].replace("{extract_dir}", lib["extract_dir"])))
        else:
            includes.append(os.path.join(srcdir, i))
    outdir = a.outdir or os.path.join(WORK, "obj", name)
    shutil.rmtree(outdir, ignore_errors=True)
    os.makedirs(outdir)
    files = discover(lib, srcdir)
    if a.only:
        files = [f for f in files if re.search(a.only, f)]
    env = wine_env()
    t0 = time.time()
    fails = []
    with cf.ThreadPoolExecutor(a.jobs) as ex:
        futs = [ex.submit(compile_one, lib, srcdir, f, outdir, a.flags, includes, env) for f in files]
        for fu in cf.as_completed(futs):
            rel, ok, log = fu.result()
            if not ok:
                fails.append((rel, log))
    objs = sorted(os.listdir(outdir))
    print("%s: %d/%d objects in %.0fs%s" % (name, len(objs), len(files), time.time() - t0,
          "" if not fails else " (%d failed)" % len(fails)))
    for rel, log in sorted(fails):
        errs = [l for l in log.splitlines() if "error" in l.lower()][:2]
        print("  FAIL %s: %s" % (rel, " | ".join(errs)))
    allowed = set(lib["build"].get("expected_failures", []))
    unexpected = [r for r, _ in fails if r not in allowed]
    if not a.outdir and not a.no_lib and objs:
        os.makedirs(os.path.join(WORK, "lib"), exist_ok=True)
        libpath = os.path.join(WORK, "lib", lib["build"].get("lib", name + ".lib"))
        rsp = os.path.join(WORK, "build", name + ".rsp")
        os.makedirs(os.path.dirname(rsp), exist_ok=True)
        open(rsp, "w").write("/NOLOGO\n/OUT:%s\n" % W(libpath) + "".join(W(os.path.join(outdir, o)) + "\n" for o in objs))
        if os.path.exists(libpath):
            os.remove(libpath)
        r = subprocess.run(["wine", os.path.join(TC, "VC", "bin", "lib.exe"), "@" + W(rsp)], env=env,
                           stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        print("  lib: %s (%s)" % (libpath, "ok" if os.path.exists(libpath) else "FAILED: " + r.stdout.decode("latin1")[:200]))
    return not unexpected

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("libs", nargs="*")
    ap.add_argument("-j", "--jobs", type=int, default=max(1, (os.cpu_count() or 4) - 2))
    ap.add_argument("--no-lib", action="store_true")
    ap.add_argument("--outdir")
    ap.add_argument("--flags")
    ap.add_argument("--only")
    ap.add_argument("--configure", help="OpenSSL: replace the manifest Configure options (experiments)")
    a = ap.parse_args()
    m = load_manifest()
    ok = True
    for name, lib in m["libraries"].items():
        if a.libs and name not in a.libs:
            continue
        ok &= build_lib(name, lib, a, m)
    sys.exit(0 if ok else 1)

if __name__ == "__main__":
    main()
