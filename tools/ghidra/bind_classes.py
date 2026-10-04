# @runtime PyGhidra
# Make Ghidra's automatic `this` typing find imported class structs:
#  1. move every child category of /Spore (or the category given as arg, e.g. /DevPDB) to the root
#     (so /Spore/Resource/X -> /Resource/X); types already at the root win on name clashes
#  2. convert namespaces of named functions into GhidraClass where a struct of that name exists
from ghidra.program.model.data import CategoryPath
from ghidra.program.model.symbol import SymbolType
from ghidra.app.util import NamespaceUtils

prog = currentProgram
dtm = prog.getDataTypeManager()
root = dtm.getRootCategory()
args = getScriptArgs()
spore = dtm.getCategory(CategoryPath(args[0] if args else "/Spore"))
moved = 0
if spore is not None:
    for c in list(spore.getCategories()):
        if root.getCategory(c.getName()) is None:
            root.moveCategory(c, monitor); moved += 1
        else:
            dst = root.getCategory(c.getName())
            for dt in list(c.getDataTypes()):
                try:
                    dst.moveDataType(dt, None)
                except Exception:
                    pass
            moved += 1
    for dt in list(spore.getDataTypes()):
        try:
            root.moveDataType(dt, None)
        except Exception:
            pass

def struct_for(ns_path):
    cat = CategoryPath("/" + "/".join(ns_path[:-1])) if len(ns_path) > 1 else CategoryPath.ROOT
    c = dtm.getCategory(cat)
    if c is None:
        return None
    return c.getDataType(ns_path[-1])

converted = 0
st = prog.getSymbolTable()
seen = set()
for f in prog.getFunctionManager().getFunctions(True):
    ns = f.getParentNamespace()
    if ns.isGlobal() or ns.getID() in seen:
        continue
    seen.add(ns.getID())
    path = ns.getName(True).split("::")
    if path and path[0].startswith("lib_"):
        continue
    if ns.getSymbol().getSymbolType() == SymbolType.CLASS:
        continue
    if struct_for(path) is not None:
        try:
            NamespaceUtils.convertNamespaceToClass(ns)
            converted += 1
        except Exception:
            pass
println("bind_classes: moved %d categories, converted %d namespaces to classes" % (moved, converted))
