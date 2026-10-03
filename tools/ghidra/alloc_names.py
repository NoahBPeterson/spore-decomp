# @runtime PyGhidra
# Recover class names from EA named allocations:  p = alloc(size, ..., "NS/ClassName"); Class::Class(p)
# For each reference to a "NS/Name" string: find the next CALL after the alloc call in the same function
# whose callee stores a .rdata pointer into [ecx] early on (a constructor writing its vtable).
# Output: <out.tsv> rows: tag, ctor_addr, vtable_addr, alloc_site
import re
args = getScriptArgs()
prog = currentProgram
listing, fm, rm, mem = prog.getListing(), prog.getFunctionManager(), prog.getReferenceManager(), prog.getMemory()
rdata = mem.getBlock(".rdata")
pat = re.compile(r"^[A-Za-z][A-Za-z0-9]*/[A-Za-z_][A-Za-z0-9_:]*$")

def vtable_store(func):
    """Return the first .rdata immediate stored to [reg] (offset 0) in the first ~40 instructions."""
    if func is None:
        return None
    ins = listing.getInstructionAt(func.getEntryPoint())
    for _ in range(40):
        if ins is None:
            return None
        if ins.getMnemonicString() == "MOV" and ins.getNumOperands() == 2:
            dst = ins.getDefaultOperandRepresentation(0)
            if dst.startswith("dword ptr [") and "+" not in dst and "-" not in dst:
                for o in ins.getOpObjects(1):
                    if hasattr(o, "getUnsignedValue"):
                        a = prog.getAddressFactory().getDefaultAddressSpace().getAddress(o.getUnsignedValue() & 0xFFFFFFFF)
                        if rdata.contains(a):
                            return a
        if ins.getFlowType().isTerminal():
            return None
        ins = ins.getNext()
    return None

rows = 0
with open(args[0], "w") as out:
    for d in listing.getDefinedData(True):
        v = d.getValue()
        if not isinstance(v, str) and not (hasattr(v, "toString") and d.hasStringValue()):
            continue
        s = str(v)
        if not pat.match(s):
            continue
        for r in rm.getReferencesTo(d.getAddress()):
            site = r.getFromAddress()
            fn = fm.getFunctionContaining(site)
            if fn is None:
                continue
            ins = listing.getInstructionAt(site)
            calls_seen = 0
            found = None
            for _ in range(30):
                ins = ins.getNext() if ins else None
                if ins is None or not fn.getBody().contains(ins.getAddress()):
                    break
                if ins.getFlowType().isCall():
                    calls_seen += 1
                    if calls_seen == 1:
                        continue  # the allocation call itself
                    flows = ins.getFlows()
                    if flows:
                        callee = fm.getFunctionAt(flows[0])
                        vt = vtable_store(callee)
                        if vt is not None:
                            found = (callee.getEntryPoint(), vt)
                    break
            out.write("%s\t%s\t%s\t%s\n" % (s, found[0] if found else "", found[1] if found else "", site))
            rows += 1
println("alloc_names: %d sites" % rows)
