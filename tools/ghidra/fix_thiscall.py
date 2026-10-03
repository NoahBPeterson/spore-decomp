# @runtime PyGhidra
# For functions in GhidraClass namespaces: if the decompiler's inferred prototype takes its first
# input in ECX and nothing in EDX, commit __thiscall so the auto `this` gets the class struct type.
from ghidra.program.model.symbol import SymbolType
from ghidra.app.decompiler import DecompInterface

prog = currentProgram
di = DecompInterface(); di.openProgram(prog)
changed = skipped = 0
for f in prog.getFunctionManager().getFunctions(True):
    ns = f.getParentNamespace()
    if ns.isGlobal() or ns.getSymbol().getSymbolType() != SymbolType.CLASS:
        continue
    if f.getCallingConventionName() == "__thiscall":
        continue
    res = di.decompileFunction(f, 30, monitor)
    hf = res.getHighFunction() if res else None
    if hf is None:
        skipped += 1; continue
    proto = hf.getFunctionPrototype()
    regs = []
    for i in range(proto.getNumParams()):
        st = proto.getParam(i).getStorage()
        regs.append(st.getRegister().getName() if st.isRegisterStorage() else "stack")
    if regs and regs[0] == "ECX" and "EDX" not in regs:
        f.setCallingConvention("__thiscall")
        changed += 1
    else:
        skipped += 1
println("fix_thiscall: changed %d, skipped %d" % (changed, skipped))
