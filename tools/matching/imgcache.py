#!/usr/bin/env python3
"""Cached facts about the analysis image, so tools don't re-parse it on every run.

pefile needs ~1.6 s to parse the 379k base relocations and ~2.5 s for a full parse (imports),
which every chk.py / run_all.py / card.py call used to pay. These are derived once per image
(keyed by size + mtime) into work/cache/ and then load in milliseconds.

  relocs()   sorted array('I') of RVAs of HIGHLOW (type 3) base relocations
  imports()  {IAT VA: "dll!name"}
Writes are atomic (temp file + rename), so concurrent tools never read a partial cache.
usage: imgcache.py [--rebuild]   (prints what it built)
"""
import array, json, os, struct, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
IMAGE = os.path.join(ROOT, "work", "SporeApp.analysis.bin")
CACHE = os.path.join(ROOT, "work", "cache")


def _key(image):
    st = os.stat(image)
    return "%d_%d" % (st.st_size, int(st.st_mtime))


def _atomic_write(path, data):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    fd, tmp = tempfile.mkstemp(dir=os.path.dirname(path), prefix=".tmp")
    with os.fdopen(fd, "wb") as f:
        f.write(data)
    os.replace(tmp, path)


def _parse_relocs(image):
    """Walk the .reloc directory directly (no pefile): blocks of (page RVA, size, u16 entries)."""
    import pefile
    pe = pefile.PE(image, fast_load=True)
    d = pe.OPTIONAL_HEADER.DATA_DIRECTORY[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_BASERELOC"]]
    raw = pe.get_data(d.VirtualAddress, d.Size)
    out, o = [], 0
    while o + 8 <= len(raw):
        page, size = struct.unpack_from("<II", raw, o)
        if size < 8:
            break
        ents = struct.unpack_from("<%dH" % ((size - 8) // 2), raw, o + 8)
        out.extend(page + (e & 0xFFF) for e in ents if e >> 12 == 3)
        o += size
    out.sort()
    return array.array("I", out)


def relocs(image=IMAGE):
    path = os.path.join(CACHE, "relocs_%s.u32" % _key(image))
    a = array.array("I")
    try:
        with open(path, "rb") as f:
            a.frombytes(f.read())
        return a
    except OSError:
        pass
    a = _parse_relocs(image)
    _atomic_write(path, a.tobytes())
    return a


def imports(image=IMAGE):
    path = os.path.join(CACHE, "imports_%s.json" % _key(image))
    try:
        with open(path) as f:
            return {int(k): v for k, v in json.load(f).items()}
    except (OSError, ValueError):
        pass
    import pefile
    pe = pefile.PE(image, fast_load=True)
    pe.parse_data_directories([pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"]])
    m = {}
    for e in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
        for i in e.imports:
            m[i.address] = "%s!%s" % (e.dll.decode().lower().replace(".dll", ""),
                                      i.name.decode() if i.name else "ord%d" % i.ordinal)
    _atomic_write(path, json.dumps(m).encode())
    return m


if __name__ == "__main__":
    if "--rebuild" in sys.argv:
        for f in os.listdir(CACHE) if os.path.isdir(CACHE) else []:
            if f.startswith(("relocs_", "imports_")):
                os.remove(os.path.join(CACHE, f))
    print("relocs:", len(relocs()), "imports:", len(imports()))
