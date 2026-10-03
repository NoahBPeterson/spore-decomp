# @runtime PyGhidra
# Mark the real (pre-SteamStub) entry point and disassemble from it.
# Args: <oep_va hex>
from ghidra.program.flatapi import FlatProgramAPI
from ghidra.program.model.symbol import SourceType
from ghidra.app.cmd.disassemble import DisassembleCommand

flat = FlatProgramAPI(currentProgram, monitor)
oep = flat.toAddr(int(getScriptArgs()[0], 16))
DisassembleCommand(oep, None, True).applyTo(currentProgram, monitor)
f = flat.getFunctionAt(oep) or flat.createFunction(oep, "entry_oep")
f.setName("entry_oep", SourceType.USER_DEFINED)
currentProgram.getSymbolTable().addExternalEntryPoint(oep)
println("OEP set at %s" % oep)
