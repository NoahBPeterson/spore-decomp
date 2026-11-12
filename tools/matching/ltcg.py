#!/usr/bin/env python3
"""ltcg: build one function the way RenderWare 4's core was built, with /GL and link /LTCG, against stub callees.

Under link /LTCG the compiler's back end sees every /GL object at once, so a function's code depends on facts
about its callees: which memory each one touches, which scratch registers its code writes, and its calling
convention (a callee nothing outside the /GL set reaches gets register arguments). A stub file supplies those
facts without the callees' real bodies. The rules and the stub generator (`ltcgstub.py stubs`, which reads the
facts from the original executable) are in c2scope / vs2005-cpp, docs/c2/ltcg.md.

A function is built this way when its bookkeeping directory (the one holding its manifest.txt / nonmatching.txt)
has `ltcg/<va>.cpp`, for example match/slices/s011efb60/ltcg/011efeb0.cpp. That file holds the stubs, and
`#pragma comment(linker, "/EXPORT:<decorated name>")` for the target when the original has the standard calling
convention (something outside the /GL set calls it). The function's own source file and the stub file are compiled
with the row's flags plus /GL, linked into a throw-away DLL with /LTCG, and the function is cut out of the DLL: its
bytes, and as its relocations the DLL's base relocations inside it plus every rel32 call/jump that leaves it (the
same offsets the retail fingerprint masks). tools/ci/fingerprint.check then gives the usual verdict.

  .venv/bin/python tools/matching/ltcg.py 0x011efeb0        # build and print the verdict (check.py does this too)
"""
import os, re, shutil, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path[:0] = [os.path.join(ROOT, "tools", "difftest"), os.path.join(ROOT, "tools", "matching")]
import slice as S           # noqa: E402

LINK_ARGS = ["/nologo", "/DLL", "/NOENTRY", "/LTCG", "/NODEFAULTLIB", "/FORCE:UNRESOLVED", "/OPT:NOREF", "/OPT:NOICF"]
# warnings every stub link prints: unresolved calleesum_*/ltcgstub_* externs (/FORCE:UNRESOLVED), no entry point
QUIET = ("LNK4088", "LNK2001", "LNK2019", "LNK4001", "Creating library", "Generating code", "Finished generating")


def stubs_file(ident, va):
    """The function's stub file, or None (an ordinary function)."""
    d = S.slice_dir(ident)
    p = os.path.join(d, "ltcg", "%08x.cpp" % va) if d else None
    return p if p and os.path.isfile(p) else None


def _link(args, vc71):
    """Run the linker of the row's compiler (2003 for /vc71, 2008 otherwise) on args."""
    tc = os.path.join(ROOT, "work", "toolchain")
    exe = os.path.join(tc, "vc71tk", "bin", "link.exe") if vc71 else os.path.join(tc, "vc9sp1", "VC", "bin", "link.exe")
    if S.NATIVE:
        env = dict(os.environ, PATH=os.path.dirname(exe) + os.pathsep + os.environ.get("PATH", ""))
        return subprocess.run([exe, *args], capture_output=True, text=True, env=env)
    env = dict(os.environ, WINEPREFIX=os.environ.get("CL_WINEPREFIX", os.path.join(tc, "wineprefix")), WINEDEBUG="-all",
               WINEPATH=S.winpath(os.path.dirname(exe)))
    # output through a file, as cl.sh does: wine's services inherit stdio and would hold a pipe open
    with tempfile.TemporaryFile("w+") as f:
        rc = subprocess.run(["wine", exe, *args], stdin=subprocess.DEVNULL, stdout=f, stderr=subprocess.STDOUT, env=env).returncode
        f.seek(0)
        return subprocess.CompletedProcess(args, rc, f.read(), "")


def _compile(src, flags, out):
    r = S.cl_run(["/nologo", "/c", *S.resolve_include_flags(flags), "/GL", S.INCLUDE, "/Fo" + S.winpath(out), S.winpath(src)])
    return r.returncode == 0 and os.path.exists(out), r.stdout + r.stderr


def read_map(path):
    """{decorated name: va} of the functions in a link map."""
    out = {}
    for line in open(path, encoding="latin-1"):
        m = re.match(r"\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+f\s", line)
        if m:
            out.setdefault(m.group(1), int(m.group(2), 16))
    return out


def cut(dll, va, size):
    """(bytes, relocated offsets) of the `size` bytes at va in the DLL."""
    import pefile, capstone
    pe = pefile.PE(dll)
    base = pe.OPTIONAL_HEADER.ImageBase
    data = pe.get_data(va - base, size)
    rel = set()
    for blk in getattr(pe, "DIRECTORY_ENTRY_BASERELOC", []):
        for e in blk.entries:
            if e.type == 3 and va <= e.rva + base < va + size:              # IMAGE_REL_BASED_HIGHLOW
                rel |= {e.rva + base - va + k for k in range(4)}
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    for i in md.disasm(data, va):
        if (i.mnemonic == "call" or i.mnemonic.startswith("j")) and i.size >= 5 and re.fullmatch(r"0x[0-9a-f]+", i.op_str):
            t = int(i.op_str, 16)
            if not va < t < va + size:                                       # leaves the function (or its own start)
                o = i.address + i.size - 4 - va
                rel |= {o, o + 1, o + 2, o + 3}
    return data, rel


def build(src, flags, stubs, sym, size, keep=None):
    """/GL-compile src and stubs, link /LTCG, cut out `sym` (decorated name) at the retail size.
    -> (bytes, rel, log); bytes None on failure."""
    d = keep or tempfile.mkdtemp(prefix="ltcg_", dir=os.path.join(ROOT, "work"))
    os.makedirs(d, exist_ok=True)
    objs, log = [], ""
    for k, s in enumerate((src, stubs)):
        o = os.path.join(d, "%d_%s.obj" % (k, os.path.splitext(os.path.basename(s))[0]))
        ok, out = _compile(s, flags, o)
        log += out
        if not ok:
            return None, None, "COMPILE FAILED (%s)\n%s" % (os.path.relpath(s, ROOT), log.strip()[-3000:])
        objs.append(o)
    dll = os.path.join(d, "ltcg.dll")
    r = _link(LINK_ARGS + ["/MAP:" + S.winpath(dll[:-4] + ".map"), "/OUT:" + S.winpath(dll)] + [S.winpath(o) for o in objs],
              "/vc71" in flags)
    log += "\n".join(l for l in r.stdout.splitlines() if l.strip() and not any(q in l for q in QUIET))
    try:
        if not os.path.exists(dll):
            return None, None, "LINK FAILED\n" + log.strip()[-3000:]
        va = read_map(dll[:-4] + ".map").get(sym)
        if va is None:
            return None, None, "%s is not in the /LTCG image (inlined everywhere, or not exported and removed?)\n%s" % (sym, log)
        data, rel = cut(dll, va, size)
        return data, rel, log
    finally:
        if not keep:
            shutil.rmtree(d, ignore_errors=True)


def main():
    import argparse
    sys.path[:0] = [os.path.join(ROOT, "tools", "contrib"), os.path.join(ROOT, "tools", "ci")]
    import task as T, fingerprint as F
    from coff import Coff
    ap = argparse.ArgumentParser()
    ap.add_argument("va")
    ap.add_argument("--keep", help="keep the objects, map and DLL in this directory")
    a = ap.parse_args()
    va = int(a.va, 16)
    fp = T.fingerprint(va)
    src, ident = T.locate(va)
    stubs = stubs_file(ident, va)
    if not (fp and src and stubs):
        sys.exit("0x%08x: needs a fingerprint, a source marker and ltcg/%08x.cpp" % (va, va))
    flags, _ = S.choose_flags(ident, va, None)
    obj, log = S.compile_obj(src, flags)
    if not obj:
        sys.exit(log)
    sym, why = S.find_symbol(Coff(obj), ident, va, src, orig_size=fp["size"])
    data, rel, log = build(src, flags, stubs, sym, fp["size"], a.keep)
    if data is None:
        sys.exit(log)
    print(F.check(fp, data, rel))


if __name__ == "__main__":
    main()
