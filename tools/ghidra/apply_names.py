# @runtime PyGhidra
# Apply symbols/names.txt: "addr name  # comment". Creates functions where missing for code addresses.
# Args: <names.txt>
from ghidra.program.model.symbol import SourceType
from ghidra.app.cmd.function import CreateFunctionCmd

prog = currentProgram
space = prog.getAddressFactory().getDefaultAddressSpace()
fm, st, mem = prog.getFunctionManager(), prog.getSymbolTable(), prog.getMemory()
text = mem.getBlock(".text")
n = 0
for line in open(getScriptArgs()[0]):
    line = line.split("#", 1)[0].strip()
    if not line:
        continue
    a, name = line.split()[:2]
    addr = space.getAddress(int(a, 16))
    ns, _, short = name.rpartition("::")
    namespace = prog.getGlobalNamespace()
    if ns:
        from ghidra.app.util import NamespaceUtils
        namespace = NamespaceUtils.createNamespaceHierarchy(ns, None, prog, SourceType.USER_DEFINED)
    if text.contains(addr):
        f = fm.getFunctionAt(addr)
        if f is None:
            CreateFunctionCmd(addr).applyTo(prog, monitor)
            f = fm.getFunctionAt(addr)
        if f is not None:
            f.setParentNamespace(namespace)
            f.setName(short, SourceType.USER_DEFINED)
            n += 1
            continue
    st.createLabel(addr, short, namespace, SourceType.USER_DEFINED)
    n += 1
println("applied %d names" % n)
