# Unoptimized (/Od /Ob1) __thiscall member returning a constant (e.g. a GetType/GetNounID hash) or
# the address of a global/string literal (when the image has a base relocation on the imm32):
#   push ebp; mov ebp,esp; push ecx; mov [ebp-4],ecx; mov eax,imm32; mov esp,ebp; pop ebp; ret
# The push ecx / spill is /Od saving `this` even though it is unused.
import os, pefile
PATTERN = "push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], ecx ; mov eax, A ; mov esp, ebp ; pop ebp ; ret "
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
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
    c = "C_%08x" % va
    if (va + 8) in _relocs():  # imm32 of mov eax at offset 7, operand at +8
        src = ("extern char g_%08x;\nstruct %s { void* Get(); };\nvoid* %s::Get() { return &g_%08x; }"
               % (v, c, c, v))
        return src, "?Get@%s@@QAEPAXXZ" % c
    src = "struct %s { unsigned int Get(); };\nunsigned int %s::Get() { return 0x%08xu; }" % (c, c, v)
    return src, "?Get@%s@@QAEIXZ" % c
