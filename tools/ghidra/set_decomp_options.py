# @runtime PyGhidra
# Persist decompiler options in the program. NaN operations stays at Ghidra's default "Compare": with our
# patched decompiler (tools/ghidra/patches/nan-exact.patch) that mode only drops NaN tests when exact and
# otherwise rewrites to the exact C compare (e.g. NAN(a)||NAN(b)||a<b -> !(b<=a)).
from ghidra.app.decompiler import DecompileOptions
opts = currentProgram.getOptions("Decompiler")
opts.setEnum("Analysis.NaN operations", DecompileOptions.NanIgnoreEnum.valueOf("Compare"))
println("set_decomp_options: NaN operations = %s" % opts.getEnum("Analysis.NaN operations", DecompileOptions.NanIgnoreEnum.valueOf("Compare")))
