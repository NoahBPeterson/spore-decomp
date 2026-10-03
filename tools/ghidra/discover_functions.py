# @runtime PyGhidra
# Create functions Ghidra's auto-analysis missed:
#  1. targets of absolute pointers into .text (relocations: vtables, callbacks, jump tables excluded)
#  2. 16-byte-aligned starts directly after int3 (0xCC) padding
# Only creates a function where the bytes are undefined or already code not owned by a function.
import jpype
from ghidra.program.flatapi import FlatProgramAPI
from ghidra.app.cmd.disassemble import DisassembleCommand
from ghidra.app.cmd.function import CreateFunctionCmd

prog = currentProgram
flat = FlatProgramAPI(prog, monitor)
mem, fm, listing = prog.getMemory(), prog.getFunctionManager(), prog.getListing()
text = mem.getBlock(".text")
lo, hi = text.getStart(), text.getEnd()
space = prog.getAddressFactory().getDefaultAddressSpace()
A = lambda v: space.getAddress(v)

def try_create(addr):
    if fm.getFunctionContaining(addr) is not None:
        return False
    ins = listing.getInstructionAt(addr)
    if ins is None:
        if listing.getDefinedDataContaining(addr) is not None:
            return False
        if listing.getInstructionContaining(addr) is not None:
            return False  # middle of an existing instruction
        DisassembleCommand(addr, None, True).applyTo(prog, monitor)
        if listing.getInstructionAt(addr) is None:
            return False
    return CreateFunctionCmd(addr).applyTo(prog, monitor)

cands = set()
for r in prog.getRelocationTable().getRelocations():
    try:
        v = mem.getInt(r.getAddress()) & 0xFFFFFFFF
    except Exception:
        continue
    a = A(v)
    if text.contains(a):
        cands.add(v)

jdata = jpype.JByte[int(text.getSize())]
text.getBytes(lo, jdata)
data = bytes(b & 0xFF for b in jdata)
base = lo.getOffset()
for i in range(16, len(data) - 1, 16):
    if data[i - 1] == 0xCC and data[i] != 0xCC:
        cands.add(base + i)

created = 0
for v in sorted(cands):
    if monitor.isCancelled():
        break
    if try_create(A(v)):
        created += 1
println("candidates=%d created=%d total_functions=%d" % (len(cands), created, fm.getFunctionCount()))
