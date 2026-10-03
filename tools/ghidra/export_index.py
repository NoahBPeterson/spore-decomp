# @runtime PyGhidra
# Export a function index and string index for the whole program.
# Args: <out_dir>
import os
from ghidra.program.model.data import StringDataInstance

out = getScriptArgs()[0]
prog = currentProgram
fm, rm, listing = prog.getFunctionManager(), prog.getReferenceManager(), prog.getListing()

with open(os.path.join(out, "functions.csv"), "w") as fh:
    fh.write("address,name,size,callers,callees,thunk\n")
    for f in fm.getFunctions(True):
        callers = len(f.getCallingFunctions(monitor))
        callees = len(f.getCalledFunctions(monitor))
        fh.write("%s,%s,%d,%d,%d,%d\n" % (f.getEntryPoint(), f.getName(), f.getBody().getNumAddresses(),
                                          callers, callees, int(f.isThunk())))

with open(os.path.join(out, "strings.tsv"), "w") as fh:
    fh.write("address\txref_functions\tvalue\n")
    for d in listing.getDefinedData(True):
        sdi = StringDataInstance.getStringDataInstance(d)
        if sdi is None or sdi == StringDataInstance.NULL_INSTANCE:
            continue
        s = sdi.getStringValue()
        if s is None:
            continue
        funcs = set()
        for r in rm.getReferencesTo(d.getAddress()):
            fn = fm.getFunctionContaining(r.getFromAddress())
            funcs.add(str(fn.getEntryPoint()) if fn else str(r.getFromAddress()))
        fh.write("%s\t%s\t%s\n" % (d.getAddress(), ";".join(sorted(funcs)),
                                   s.replace("\t", "\\t").replace("\n", "\\n").replace("\r", "\\r")))
println("index exported: %d functions" % fm.getFunctionCount())
