# @runtime PyGhidra
# Label retail globals from tools/xmatch/globals.py output (dev PDB names) and vtables from
# match.py's <out>_vtables.json. Existing user-defined labels are kept; the PDB name is added as a comment.
# Args: <pdb_globals.json> [<vtables.json>]
import json
from ghidra.program.model.symbol import SourceType
from ghidra.program.model.listing import CodeUnit

args = getScriptArgs()
st = currentProgram.getSymbolTable()
listing = currentProgram.getListing()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()


def label(va, name, note):
    a = space.getAddress(int(va, 16))
    s = st.getPrimarySymbol(a)
    if s is not None and s.getSource() == SourceType.USER_DEFINED and not s.getName().startswith(("DAT_", "PTR_")):
        cu = listing.getCodeUnitAt(a)
        if cu is not None:
            cu.setComment(CodeUnit.EOL_COMMENT, "PDB (%s): %s" % (note, name))
        return 0
    st.createLabel(a, name[:2000], SourceType.IMPORTED).setPrimary()
    return 1


tx = currentProgram.startTransaction("apply pdb globals")
n = kept = 0
try:
    for va, g in json.load(open(args[0])).items():
        if label(va, g["name"], "global, %d votes" % g["votes"]): n += 1
        else: kept += 1
    if len(args) > 1:
        for va, v in json.load(open(args[1])).items():
            if label(va, v["name"], "vtable"): n += 1
            else: kept += 1
finally:
    currentProgram.endTransaction(tx, True)
println("apply_pdb_globals: labeled %d, kept existing user labels %d" % (n, kept))
