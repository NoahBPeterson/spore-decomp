#!/usr/bin/env python3
"""Template synthesis for high-frequency small-function patterns.

usage: synth.py <template-name> [--limit N]
Each template: pattern (normalized, from patterns.py), flags, a prelude, and a per-instance
emitter getting A (absolute addresses in operand order) and N (immediates in operand order).
All instances compile in one TU (match/synth/<name>.cpp); each is verified with cmpobj logic;
verified ones go to match/synth/<name>.manifest (manifest format, read by run_all).
"""
import argparse, json, os, re, subprocess, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pefile, capstone
from cmpobj import parse_coff, REL_SIZES
from card import load_funcs, bounds

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
IMAGE = os.path.join(ROOT, "work/SporeApp.analysis.bin")
pe = pefile.PE(IMAGE, fast_load=True)
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

def operands(va, code):
    A, N = [], []
    for i in md.disasm(code, va):
        if i.mnemonic.startswith("j") or i.mnemonic == "call":
            continue
        for m in re.finditer(r"0x[0-9a-f]+|\b\d+\b", i.op_str):
            v = int(m.group(0), 0)
            (A if len(m.group(0)) >= 8 and m.group(0).startswith("0x") and v >= 0x400000 else N).append(v)
    return A, N

def g(a): return "g_%08x" % a


def _image_end():
    return pe.OPTIONAL_HEADER.ImageBase + max(x.VirtualAddress + max(x.Misc_VirtualSize, x.SizeOfRawData) for x in pe.sections)


def constify(src, A):
    """A value that operands() takes for an address (8 hex digits, >= 0x400000) but that lies outside the image is a
    plain constant: the retail code holds it with no relocation.  Templates declare every A value as a global
    (`extern const wchar_t g_01a80d26[];`, or several in one `extern char g_a[], g_b[];`), so the compiled code carried a
    relocation where retail has fixed bytes, and only the loose relocation mask accepted it (tools/ci/fingerprint.py
    fails it).  Drop such declarators and write the constant, typed as declared: `g_01a80d26` -> `((const wchar_t*)0x01a80d26)`."""
    end = _image_end()
    decl = re.compile(r"extern\s+((?:const\s+)?[A-Za-z_][\w:]*(?:\s+const)?)\s+([^;()]*?);[ \t]*\n?")
    for a in sorted(set(A)):
        if a < end:
            continue
        name, ty = g(a), None
        # every declaration of the name goes (a whole generated file repeats it per instance), then every use
        while True:
            for m in decl.finditer(src):
                parts = [x.strip() for x in m.group(2).split(",")]
                hit = [x for x in parts if re.fullmatch(r"(\*\s*)*%s\s*(\[\s*\])?" % name, x)]
                if hit:
                    break
            else:
                break
            ty = ty or m.group(1).strip() + "".join("*" for _ in range(hit[0].count("*")))
            rest = [x for x in parts if x not in hit]
            src = src[:m.start()] + (("extern %s %s;\n" % (m.group(1).strip(), ", ".join(rest))) if rest else "") + src[m.end():]
        if ty:
            src = re.sub(r"&\s*\b%s\b|\b%s\b" % (name, name), "((%s*)0x%08x)" % (ty, a), src)
    return src


def constify_existing(name):
    """constify() on an already generated match/synth/<name>.cpp (for a template whose pattern is no longer in
    work/patterns.json, so it cannot be regenerated)"""
    path = os.path.join(ROOT, "match/synth/%s.cpp" % name)
    src = open(path).read()
    A = [int(h, 16) for h in re.findall(r"\bg_([0-9a-f]{8})\b", src)]
    out = constify(src, A)
    open(path, "w").write(out)
    print("%s: %s" % (name, "rewritten" if out != src else "unchanged"))


TEMPLATES = {}
def template(name, pattern, flags, prelude, emit):
    TEMPLATES[name] = dict(pattern=pattern, flags=flags, prelude=prelude, emit=emit)

# Templates live in tools/matching/synth_templates/<name>.py, each defining:
#   PATTERN (str, exact normalized pattern from work/patterns.json), FLAGS (list), PRELUDE (str),
#   emit(va, A, N) -> (source_text, mangled_symbol)
import importlib.util, glob as _glob
for _f in sorted(_glob.glob(os.path.join(os.path.dirname(os.path.abspath(__file__)), "synth_templates", "*.py"))):
    _spec = importlib.util.spec_from_file_location("st_" + os.path.basename(_f)[:-3], _f)
    _m = importlib.util.module_from_spec(_spec); _spec.loader.exec_module(_m)
    template(os.path.basename(_f)[:-3], _m.PATTERN, _m.FLAGS, getattr(_m, "PRELUDE", ""), _m.emit)

def run(name, limit, vas=None):
    t = TEMPLATES[name]
    pats = json.load(open(os.path.join(ROOT, "work/patterns.json")))
    grp = next((p for p in pats if p["pattern"] == t["pattern"]), None)
    if grp is None:
        sys.exit("pattern not found in work/patterns.json")
    starts, _ = load_funcs()
    vas = [int(v, 16) for v in grp["vas"]][:limit]
    body, syms = [t["prelude"]], {}
    seen_defs = set()
    for va in vas:
        code = bounds(va, starts)
        A, N = operands(va, code)
        src, sym = t["emit"](va, A, N)
        src = constify(src, A)
        if sym in syms.values() or src in seen_defs:
            continue  # same global initialized twice can't be expressed in one TU; leave for agents
        seen_defs.add(src)
        body.append("// @ 0x%08x\n%s\n" % (va, src))
        syms[va] = sym
    path = os.path.join(ROOT, "match/synth/%s.cpp" % name)
    open(path, "w").write("// Generated by tools/matching/synth.py (template %s). Do not edit by hand.\n" % name + "\n".join(body))
    obj = os.path.join(ROOT, "work/match/synth_%s.obj" % name)
    w = lambda p: "Z:" + p.replace("/", "\\")
    r = subprocess.run([os.path.join(ROOT, "tools/matching/cl.sh"), "/nologo", "/c", *t["flags"],
                        "/I" + w(os.path.join(ROOT, "match/include")), "/Fo" + w(obj), w(path)],
                       capture_output=True, text=True)
    if r.returncode:
        sys.exit(r.stdout[-3000:])
    secs, osyms = parse_coff(obj)
    ok, bad = [], []
    for va, sym in syms.items():
        if sym not in osyms:
            bad.append((va, "symbol missing")); continue
        si, off = osyms[sym]
        orig = bounds(va, starts)
        mine = secs[si]["data"][off:off + len(orig)]
        mask = {v + k - off for v, _, ty in secs[si]["relocs"] for k in range(REL_SIZES.get(ty, 4))}
        if len(mine) == len(orig) and all(mine[i] == orig[i] for i in range(len(orig)) if i not in mask):
            ok.append(va)
        else:
            bad.append((va, "diff"))
    flags = " ".join(t["flags"])
    with open(os.path.join(ROOT, "match/synth/%s.manifest" % name), "w") as fh:
        fh.write("# Generated by tools/matching/synth.py; verified at generation time\n")
        for va in ok:
            fh.write("synth/%s.cpp  %s  %08x  %s\n" % (name, syms[va], va, flags))
    print("%s: %d instances, %d byte-exact, %d failed%s" % (name, len(syms), len(ok), len(bad),
          (" e.g. %08x %s" % bad[0]) if bad else ""))

if __name__ == "__main__":
    ap = argparse.ArgumentParser(); ap.add_argument("name"); ap.add_argument("--limit", type=int, default=100000)
    ap.add_argument("--constify-existing", action="store_true", help="only rewrite the generated file's out-of-image constants")
    a = ap.parse_args()
    if a.constify_existing:
        constify_existing(a.name); sys.exit(0)
    for n in (TEMPLATES if a.name == "all" else [a.name]):
        run(n, a.limit)
