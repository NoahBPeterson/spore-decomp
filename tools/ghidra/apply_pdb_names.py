# @runtime PyGhidra
# Apply dev-build PDB names to retail functions.
# Args: <matches.json> <high-confidence methods, comma-separated>
#   high-confidence matches -> function renamed (template-aware namespace split via SymbolPath);
#                              a previous non-default name is kept in the plate comment
#   other matches           -> plate comment "PDB candidate (<method>): <name>" only
import json
from ghidra.app.util import SymbolPath
from ghidra.program.model.symbol import SourceType
from ghidra.program.model.listing import CodeUnit

args = getScriptArgs()
m = json.load(open(args[0]))
high = set(args[1].split(","))
prog = currentProgram
fm, st = prog.getFunctionManager(), prog.getSymbolTable()
sp = prog.getAddressFactory().getDefaultAddressSpace()
named = commented = errors = 0
cache = {}

def namespace_for(path):
    if path is None:
        return prog.getGlobalNamespace()
    key = path.getPath()
    if key in cache:
        return cache[key]
    parent = namespace_for(path.getParent())
    name = path.getName().replace(" ", "_")[:2000]
    ns = st.getNamespace(name, parent) or st.createNameSpace(parent, name, SourceType.IMPORTED)
    cache[key] = ns
    return ns

for r, v in m.items():
    f = fm.getFunctionAt(sp.getAddress(int(r, 16)))
    if f is None:
        continue
    try:
        if v["how"] in high:
            old = f.getName(True)
            p = SymbolPath(v["name"])
            ns = namespace_for(p.getParent())
            if not f.getName().startswith("FUN_") and old != v["name"]:
                prev = f.getComment() or ""
                f.setComment((prev + "\n" if prev else "") + "Previous name: " + old)
            f.setParentNamespace(ns)
            f.setName(p.getName().replace(" ", "_")[:2000], SourceType.IMPORTED)
            named += 1
        else:
            prev = f.getComment() or ""
            if "PDB candidate" not in prev:
                f.setComment((prev + "\n" if prev else "") + "PDB candidate (%s): %s" % (v["how"], v["name"]))
                commented += 1
    except Exception as e:
        errors += 1
println("apply_pdb_names: named %d, candidate comments %d, errors %d" % (named, commented, errors))
