# @runtime PyGhidra
# Apply work/index/boundary_fix.json: delete false function starts, create missing ones, then
# recompute bodies of functions around deleted starts (they were truncated by the false split).
# Args: <boundary_fix.json>
import json
from ghidra.app.cmd.function import CreateFunctionCmd

prog = currentProgram
fm, listing = prog.getFunctionManager(), prog.getListing()
sp = prog.getAddressFactory().getDefaultAddressSpace()
fx = json.load(open(getScriptArgs()[0]))
deleted = created = fixed = 0
for a in fx["delete"]:
    addr = sp.getAddress(int(a, 16))
    if fm.getFunctionAt(addr) is not None:
        fm.removeFunction(addr); deleted += 1
for a in fx["create"]:
    addr = sp.getAddress(int(a, 16))
    if fm.getFunctionAt(addr) is None and CreateFunctionCmd(addr).applyTo(prog, monitor):
        created += 1
# re-derive bodies: the function preceding each deleted start may now extend over it
seen = set()
for a in fx["delete"]:
    addr = sp.getAddress(int(a, 16))
    it = fm.getFunctions(addr, False)
    f = it.next() if it.hasNext() else None
    if f is not None and f.getEntryPoint() not in seen:
        seen.add(f.getEntryPoint())
        if CreateFunctionCmd.fixupFunctionBody(prog, f, monitor):
            fixed += 1
println("apply_boundaries: deleted %d, created %d, bodies fixed %d, total %d" % (deleted, created, fixed, fm.getFunctionCount()))
