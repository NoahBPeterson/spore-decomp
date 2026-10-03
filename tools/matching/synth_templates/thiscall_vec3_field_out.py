# __thiscall member returning a Vector3 (3 floats) by value built from three consecutive float
# fields; x87 build (no SSE): hidden return pointer loaded to eax, fld/fstp pairs, ret 4.
PATTERN = 'mov eax, dword ptr [esp + N] ; fld dword ptr [ecx + N] ; fstp dword ptr [eax] ; fld dword ptr [ecx + N] ; fstp dword ptr [eax + N] ; fld dword ptr [ecx + N] ; fstp dword ptr [eax + N] ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct W3 { float x, y, z; };\n"

def emit(va, A, N):
    off = N[1]
    c = "C_%08x" % va
    src = ("#pragma pack(push, 1)\nstruct %s { char pad[0x%x]; float x, y, z; W3 Get(); };\n#pragma pack(pop)\n"
           "W3 %s::Get() { W3 r = {x, y, z}; return r; }" % (c, off, c))
    return src, "?Get@%s@@QAE?AUW3@@XZ" % c
