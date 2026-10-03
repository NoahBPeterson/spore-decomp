# @runtime PyGhidra
# Whole-program C export (types header + all function bodies) via Ghidra's CppExporter.
# Args: <out.c>
import java.io.File as File
from ghidra.app.util.exporter import CppExporter
from ghidra.app.util import Option
exp = CppExporter()
opts = exp.getOptions(None)
for o in opts:
    n = o.getName()
    if n == CppExporter.CREATE_HEADER_FILE:
        o.setValue(True)
    elif n == CppExporter.CREATE_C_FILE:
        o.setValue(True)
    elif n == CppExporter.USE_CPP_STYLE_COMMENTS:
        o.setValue(False)
    elif n == CppExporter.EMIT_TYPE_DEFINITONS:
        o.setValue(True)
    elif n == CppExporter.FUNCTION_TAG_EXCLUDE:
        pass
exp.setOptions(opts)
ok = exp.export(File(getScriptArgs()[0]), currentProgram, None, monitor)
println("export_cpp: %s" % ok)
