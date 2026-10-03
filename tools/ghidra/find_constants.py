# @runtime PyGhidra
# Find functions whose instructions use given scalar constants.
# Args: <hex const> [<hex const> ...]
from ghidra.program.model.scalar import Scalar

wanted = set(int(a, 16) for a in getScriptArgs())
fm = currentProgram.getFunctionManager()
hits = {}
for ins in currentProgram.getListing().getInstructions(True):
    for i in range(ins.getNumOperands()):
        for o in ins.getOpObjects(i):
            if isinstance(o, Scalar) and (o.getUnsignedValue() & 0xFFFFFFFF) in wanted:
                fn = fm.getFunctionContaining(ins.getAddress())
                key = (o.getUnsignedValue() & 0xFFFFFFFF, str(fn.getEntryPoint()) if fn else "nofunc")
                hits.setdefault(key, []).append(str(ins.getAddress()))
for (c, fn), sites in sorted(hits.items()):
    println("CONST %08x in %s at %s" % (c, fn, ",".join(sites[:5])))
