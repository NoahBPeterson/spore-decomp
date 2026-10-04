# @runtime PyGhidra
# Decompile functions by address to a C file.
# Args: <out.c> <hex addr> [<hex addr> ...]
from ghidra.app.decompiler import DecompInterface, DecompileOptions
from ghidra.program.flatapi import FlatProgramAPI

args = getScriptArgs()
flat = FlatProgramAPI(currentProgram, monitor)
di = DecompInterface()
opts = DecompileOptions()
opts.grabFromProgram(currentProgram)
di.setOptions(opts)
di.openProgram(currentProgram)
with open(args[0], "w") as fh:
    space = currentProgram.getAddressFactory().getDefaultAddressSpace()
    for a in " ".join(args[1:]).split():
        f = flat.getFunctionContaining(space.getAddress(int(a, 16)))
        if f is None:
            fh.write("/* no function at %s */\n" % a)
            continue
        res = di.decompileFunction(f, 120, monitor)
        fh.write("/* ==== %s @ %s ==== */\n" % (f.getName(), f.getEntryPoint()))
        fh.write(res.getDecompiledFunction().getC() if res.decompileCompleted() else
                 "/* decompile failed: %s */\n" % res.getErrorMessage())
println("wrote %s" % args[0])
