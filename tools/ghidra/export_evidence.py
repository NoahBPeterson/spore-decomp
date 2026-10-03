# @runtime PyGhidra
# Export per-function start evidence: address, number of code refs from other functions, data refs.
# Args: <out.csv>
prog = currentProgram
text = prog.getMemory().getBlock('.text')
fm, rm = prog.getFunctionManager(), prog.getReferenceManager()
with open(getScriptArgs()[0], "w") as fh:
    fh.write("address,code_refs,data_refs,is_thunk\n")
    for f in fm.getFunctions(True):
        ep = f.getEntryPoint()
        c = d = 0
        for r in rm.getReferencesTo(ep):
            src = fm.getFunctionContaining(r.getFromAddress())
            if r.getReferenceType().isData():
                if not text.contains(r.getFromAddress()):
                    d += 1
            elif r.getReferenceType().isCall():
                c += 1
        fh.write("%08x,%d,%d,%d\n" % (ep.getOffset(), c, d, int(f.isThunk())))
println("evidence exported")
