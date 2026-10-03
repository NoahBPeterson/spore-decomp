# @runtime PyGhidra
# Mass-decompile a slice of all functions.
# Args: <out_dir> <worker_index> <worker_count>
# Writes <out_dir>/c/<block>.c (one file per 64 KiB address block, functions in address order)
# and <out_dir>/index_<worker>.csv: address,name,bytes,status,lines
import os
from ghidra.app.decompiler import DecompInterface, DecompileOptions

out, wi, wn = getScriptArgs()[0], int(getScriptArgs()[1]), int(getScriptArgs()[2])
os.makedirs(os.path.join(out, "c"), exist_ok=True)
prog = currentProgram
di = DecompInterface()
opts = DecompileOptions()
opts.grabFromProgram(prog)
di.setOptions(opts)
di.toggleCCode(True)
di.toggleSyntaxTree(False)
di.setSimplificationStyle("decompile")
di.openProgram(prog)

funcs = [f for f in prog.getFunctionManager().getFunctions(True) if not f.isExternal()]
# contiguous slices keep each block file owned by one worker (blocks never split across workers)
blocks = sorted(set(f.getEntryPoint().getOffset() >> 16 for f in funcs))
mine = set(blocks[i] for i in range(len(blocks)) if i % wn == wi)
funcs = [f for f in funcs if (f.getEntryPoint().getOffset() >> 16) in mine]

idx = open(os.path.join(out, "index_%d.csv" % wi), "w")
cur_block, fh, n = None, None, 0
for f in funcs:
    if monitor.isCancelled():
        break
    ep = f.getEntryPoint().getOffset()
    blk = ep >> 16
    if blk != cur_block:
        if fh:
            fh.close()
        fh = open(os.path.join(out, "c", "%04x0000.c" % blk), "w")
        cur_block = blk
    status, lines = "ok", 0
    try:
        res = di.decompileFunction(f, 60, monitor)
        if res is not None and res.decompileCompleted():
            code = res.getDecompiledFunction().getC()
        else:
            status = "fail"
            code = "/* decompile failed: %s */\n" % (res.getErrorMessage() if res else "null")
    except Exception as e:
        status, code = "error", "/* exception: %s */\n" % e
    lines = code.count("\n")
    fh.write("/* ==== %s @ %08x ==== */\n%s\n" % (f.getName(True), ep, code))
    idx.write("%08x,%s,%d,%s,%d\n" % (ep, f.getName(True).replace(",", ";"), f.getBody().getNumAddresses(), status, lines))
    n += 1
    if n % 2000 == 0:
        idx.flush()
        println("worker %d: %d/%d" % (wi, n, len(funcs)))
if fh:
    fh.close()
idx.close()
println("worker %d done: %d functions" % (wi, n))
