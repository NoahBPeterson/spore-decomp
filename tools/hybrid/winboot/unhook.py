"""unhook.py IN OUT VA...|@FILE: copy a hybrid exe with the listed hooks switched off (the original's first five
bytes restored at each hooked VA, so the original function runs again; our spliced copy stays unreferenced)."""
import json, sys
import pefile
src, out, vas = sys.argv[1], sys.argv[2], []
for a in sys.argv[3:]:
    vas += [l.split()[0] for l in open(a[1:]) if l.strip()] if a.startswith("@") else [a]
pe = pefile.PE(src); orig = pefile.PE("work/SporeApp.analysis.bin", fast_load=True)
hooks = {h["va"]: h for h in json.load(open(src + ".hooks.json"))["hooks"]}
data = bytearray(pe.__data__)
n = 0
for v in vas:
    v = "%08x" % int(v, 16)
    if v not in hooks:
        print("not hooked:", v); continue
    rva = int(v, 16) - 0x400000
    off = pe.get_offset_from_rva(rva)
    assert data[off] == 0xE9, v
    data[off:off + 5] = orig.get_data(rva, 5)
    n += 1
open(out, "wb").write(data)
json.dump({"hooks": [h for k, h in hooks.items() if k not in {"%08x" % int(x, 16) for x in vas}]}, open(out + ".hooks.json", "w"))
print("unhooked %d -> %s" % (n, out))
