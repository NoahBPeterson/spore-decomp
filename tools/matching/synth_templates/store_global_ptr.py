# Store of a 32-bit value into a global: "mov dword ptr [g], imm32 ; ret". /O2 leaf function.
# Mostly installs a function pointer / vtable / object address into a global (imm32 has an
# image base relocation); otherwise a plain constant store. Source: `g = &x;` or `g = 0x...;`.
import os, pefile
PATTERN = "mov dword ptr [A], A ; ret "
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
    d, v = A[0], A[1]
    if (va + 6) in _relocs():
        src = ("extern void* g_%08x;\nextern char g_%08x;\n"
               "void FUN_%08x() { g_%08x = &g_%08x; }" % (d, v, va, d, v))
    else:
        src = ("extern unsigned int g_%08x;\n"
               "void FUN_%08x() { g_%08x = 0x%08xu; }" % (d, va, d, v))
    return src, "?FUN_%08x@@YAXXZ" % va
