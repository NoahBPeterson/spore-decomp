# @runtime PyGhidra
# For each address: list references to it (code refs -> containing function; data refs -> address,
# plus the start of the vtable-ish pointer run that contains it).
# Args: <out.txt> <hex addr> [...]
args = getScriptArgs()
prog = currentProgram
space = prog.getAddressFactory().getDefaultAddressSpace()
fm, rm, mem = prog.getFunctionManager(), prog.getReferenceManager(), prog.getMemory()
with open(args[0], "w") as fh:
    for a in " ".join(args[1:]).split():
        addr = space.getAddress(int(a, 16))
        fh.write("== %s\n" % addr)
        for r in rm.getReferencesTo(addr):
            src = r.getFromAddress()
            fn = fm.getFunctionContaining(src)
            if fn:
                fh.write("  code %s in %s @ %s\n" % (r.getReferenceType(), fn.getName(), src))
            else:
                # walk back over consecutive code pointers to find a vtable start
                start = src
                while True:
                    prev = start.subtract(4)
                    try:
                        v = mem.getInt(prev) & 0xFFFFFFFF
                    except Exception:
                        break
                    if fm.getFunctionAt(space.getAddress(v)) is None:
                        break
                    start = prev
                fh.write("  data %s @ %s (slot %d of table @ %s)\n" % (r.getReferenceType(), src,
                         src.subtract(start) // 4, start))
