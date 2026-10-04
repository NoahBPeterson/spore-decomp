#!/usr/bin/env python3
"""Extract ordered function tables from both builds for sequence matching (used by match.py).

usage: tables.py <dev features.json> <retail features.json> <out.json>
- xcu: the C++ dynamic-initializer table (__xc_a..__xc_z), in link order. Dev from work/xmatch/dev_xcu.json,
  retail read from the analysis image (0x013CC80C-0x013EB098).
- vt: vtables. Dev: PDB publics ??_7<class>@@6B@, slots read from the image until the next public or a
  non-function dword. Retail (built /GR-, no RTTI): maximal runs of >=2 dwords in .rdata/.data that are
  all known function starts, where the run is referenced as an immediate from code (a vptr store).
Output: {"dev_xcu": [va..], "ret_xcu": [va..], "dev_vt": {va: {"name", "slots"}}, "ret_vt": {va: slots}}
"""
import bisect, json, os, re, struct, sys
import pefile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
W = lambda *p: os.path.join(ROOT, *p)


def image(path):
    pe = pefile.PE(path, fast_load=True)
    base = pe.OPTIONAL_HEADER.ImageBase
    img = pe.get_memory_mapped_image()
    secs = {s.Name.rstrip(b"\0").decode(): (base + s.VirtualAddress, base + s.VirtualAddress + s.Misc_VirtualSize)
            for s in pe.sections}
    return base, img, secs


def main(devf, retf, outp):
    dev, ret = json.load(open(devf)), json.load(open(retf))
    out = {"dev_xcu": json.load(open(W("work/xmatch/dev_xcu.json")))}

    # retail xcu
    base, img, secs = image(W("work/SporeApp.analysis.bin"))
    xs = []
    for a in range(0x013CC80C, 0x013EB098, 4):
        v = struct.unpack_from("<I", img, a - base)[0]
        if v:
            xs.append("%08x" % v)
    out["ret_xcu"] = xs

    # retail vtables: runs of function-start pointers, referenced from code
    rstarts = set(int(k, 16) for k in ret)
    tlo, thi = secs[".text"]
    # code-referenced data addresses: scan .text for 4-byte little-endian values pointing at a run start
    text = img[tlo - base:thi - base]
    runs = {}
    for sec in (".rdata", ".data"):
        lo, hi = secs[sec]
        a = lo
        while a + 4 <= hi:
            v = struct.unpack_from("<I", img, a - base)[0]
            if v in rstarts:
                s = a
                slots = []
                while a + 4 <= hi:
                    v = struct.unpack_from("<I", img, a - base)[0]
                    if v not in rstarts:
                        break
                    slots.append("%08x" % v)
                    a += 4
                runs[s] = slots
            else:
                a += 4
    # keep runs whose start (or an interior position, for MI secondary vtables) is an immediate in code
    starts = {}
    for s, slots in runs.items():
        for i in range(len(slots)):
            starts[s + 4 * i] = (s, i)
    hit = {}
    want = {struct.pack("<I", va): va for va in starts}
    for i in range(len(text) - 3):
        w = text[i:i + 4]
        va = want.get(w)
        if va is not None:
            hit[va] = True
    vt = {}
    for s, slots in runs.items():
        cuts = sorted(i for i in range(len(slots)) if (s + 4 * i) in hit)
        for n, i in enumerate(cuts):
            j = cuts[n + 1] if n + 1 < len(cuts) else len(slots)
            if j - i >= 1:
                vt["%08x" % (s + 4 * i)] = slots[i:j]
    out["ret_vt"] = vt

    # dev vtables
    base, img, secs = image(W("work/devbuild/SporeBin/SporeApp.exe"))
    syms = json.load(open(W("work/devbuild/symbols.json")))
    dstarts = set(int(k, 16) for k in dev)
    thunks = {int(k, 16): v for k, v in syms["thunks"].items()}
    tlo, thi = secs[".text"]
    pubs = sorted(set(p["va"] for p in syms["publics"]) | set(g["va"] for g in syms["globals"]))
    dvt = {}
    for p in syms["publics"]:
        if not p["name"].startswith("??_7"):
            continue
        a = p["va"]
        nxt = pubs[bisect.bisect_right(pubs, a)] if bisect.bisect_right(pubs, a) < len(pubs) else a + 4096
        slots = []
        while a < nxt and a + 4 <= base + len(img):
            v = struct.unpack_from("<I", img, a - base)[0]
            v = thunks.get(v, v)
            if not (tlo <= v < thi):  # slots into library code (no S_GPROC) are kept as placeholders
                break
            slots.append("%08x" % v)
            a += 4
        if slots:
            dvt["%08x" % p["va"]] = {"name": p["name"], "slots": slots}
    out["dev_vt"] = dvt
    json.dump(out, open(outp, "w"))
    print("xcu dev %d ret %d; vtables dev %d ret %d" % (len(out["dev_xcu"]), len(xs), len(dvt), len(vt)))


if __name__ == "__main__":
    main(*sys.argv[1:4])
