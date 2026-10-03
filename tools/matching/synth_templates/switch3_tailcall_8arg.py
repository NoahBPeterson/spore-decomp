# cdecl bool f(a0..a6, idx) with 8 int-sized args: switch on p->elems[idx].type (p = arg2,
# elems at p+8, 32-byte elements, type at +8) for cases 7/8/9, each tail-calling a same-signature
# function with the identical argument list; default returns false. Plain /O2: the tail calls
# write the loaded args (idx, p) back to their stack slots before the jmp.
import os, struct
PATTERN = "mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [edx + N] ; mov eax, ecx ; shl eax, N ; mov eax, dword ptr [esi + eax + N] ; sub eax, N ; pop esi ; je +N ; sub eax, N ; je +N ; sub eax, N ; je +N ; xor al, al ; ret  ; mov dword ptr [esp + N], ecx ; mov dword ptr [esp + N], edx ; jmp EXT ; mov dword ptr [esp + N], ecx ; mov dword ptr [esp + N], edx ; jmp EXT ; mov dword ptr [esp + N], ecx ; mov dword ptr [esp + N], edx ; jmp EXT"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct SwElem { int a; int b; int type; int pad[5]; };
struct SwArr { int x; int y; SwElem* elems; };
"""
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_img = None
def _targets(va):
    # jmp rel32 at offsets 0x30, 0x3d, 0x4a (cases 9, 8, 7)
    global _img
    if _img is None:
        import pefile
        _img = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
    base = _img.OPTIONAL_HEADER.ImageBase
    code = _img.get_data(va - base, 0x4f)
    out = []
    for off in (0x30, 0x3d, 0x4a):
        assert code[off] == 0xE9
        out.append((va + off + 5 + struct.unpack_from("<i", code, off + 1)[0]) & 0xffffffff)
    return out

def emit(va, A, N):
    idx_slot, p_slot, elems_off, shift, type_off, c0, d1, d2 = N[:8]
    assert (idx_slot, p_slot, elems_off, shift, type_off) == (0x20, 0xc, 8, 5, 8)
    t9, t8, t7 = _targets(va)
    sig = "(int,int,SwArr*,int,int,int,int,int)"
    decl = "".join("bool FUN_%08x%s;\n" % (t, sig) for t in sorted({t7, t8, t9}))
    call = "(a0,a1,p,a3,a4,a5,a6,idx)"
    src = decl + (
        "bool FUN_%08x(int a0,int a1,SwArr* p,int a3,int a4,int a5,int a6,int idx) {\n"
        "  switch (p->elems[idx].type) {\n"
        "  case %d: return FUN_%08x%s;\n"
        "  case %d: return FUN_%08x%s;\n"
        "  case %d: return FUN_%08x%s;\n"
        "  }\n  return false;\n}\n") % (va, c0, t7, call, c0 + d1, t8, call, c0 + d1 + d2, t9, call)
    return src, "?FUN_%08x@@YA_NHHPAUSwArr@@HHHHH@Z" % va
