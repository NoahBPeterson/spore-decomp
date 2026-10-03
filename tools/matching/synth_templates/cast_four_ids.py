# thiscall "return this if id is one of 4 constants else 0" (interface cast), /O2
PATTERN = 'mov edx, dword ptr [esp + N] ; cmp edx, A ; mov eax, ecx ; jg +N ; je +N ; cmp edx, A ; je +N ; cmp edx, A ; jne +N ; ret N ; cmp edx, A ; je +N ; xor eax, eax ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    import os, pefile, struct
    global _pe
    if '_pe' not in globals():
        root = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', '..'))
        _pe = pefile.PE(os.path.join(root, "work/SporeApp.analysis.bin"), fast_load=True)
    code = _pe.get_data(va - _pe.OPTIONAL_HEADER.ImageBase, 48)
    ids = [struct.unpack("<I", code[o+2:o+6])[0] for o in range(len(code)-5)
           if code[o] == 0x81 and code[o+1] == 0xfa][:4]
    cond = " ".join("case (int)0x%xu: return this;" % v for v in ids)
    src = ("struct C_%08x { void* F(int id); };\n"
           "void* C_%08x::F(int id) { switch (id) { %s } return 0; }") % (va, va, cond)
    return src, "?F@C_%08x@@QAEPAXH@Z" % va
