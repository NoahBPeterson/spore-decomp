# __thiscall member returning a 3-int POD by value built from three dword fields (offsets arbitrary).
PATTERN = 'mov edx, dword ptr [ecx + N] ; mov eax, dword ptr [esp + N] ; mov dword ptr [eax], edx ; mov edx, dword ptr [ecx + N] ; mov ecx, dword ptr [ecx + N] ; mov dword ptr [eax + N], edx ; mov dword ptr [eax + N], ecx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct W3 { int x, y, z; };\n"

def emit(va, A, N):
    o = [N[0], 0, 0]
    o[N[4] // 4] = N[2]
    o[N[5] // 4] = N[3]
    c = "C_%08x" % va
    order = [0] + [N[4] // 4, N[5] // 4]
    body = "".join("r.%s = *(const int*)(p + 0x%x); " % ("xyz"[k], o[k]) for k in order)
    src = ("struct %s { char pad[0x4]; W3 Get(); };\n"
           "W3 %s::Get() { const char* p = (const char*)this; W3 r; %sreturn r; }" % (c, c, body))
    return src, "?Get@%s@@QAE?AUW3@@XZ" % c
