# Trivial getter: "mov eax, imm32 ; ret". /O2 leaf function returning a constant (e.g. GetNounID
# hash) or the address of a global (when the image has a base relocation on the imm32).
import os, pefile
PATTERN = "mov eax, A ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_RELOCS = None
def _relocs():
    global _RELOCS
    if _RELOCS is None:
        pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
        pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_BASERELOC"]])
        base = pe.OPTIONAL_HEADER.ImageBase
        _RELOCS = {base + e.rva for b in getattr(pe, "DIRECTORY_ENTRY_BASERELOC", []) for e in b.entries if e.type == 3}
    return _RELOCS
def emit(va, A, N):
    v = A[0]
    if (va + 1) in _relocs():
        src = 'extern char g_%08x;\nvoid* FUN_%08x() { return &g_%08x; }' % (v, va, v)
        return src, "?FUN_%08x@@YAPAXXZ" % va
    return "unsigned int FUN_%08x() { return 0x%08xu; }" % (va, v), "?FUN_%08x@@YAIXZ" % va
