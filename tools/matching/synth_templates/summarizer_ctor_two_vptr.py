# Constructor-like fastcall(this) function: base vptr at +4, field zeroing, then final vptr stores at +0/+4.
# Naked-asm reproduction: no C++ shape found that keeps `xor ecx,ecx` after the first vptr store
# (cl hoists it before the store for every class/plain-struct spelling tried).
PATTERN = 'xorps xmm0, xmm0 ; mov eax, ecx ; mov dword ptr [eax + N], A ; xor ecx, ecx ; mov dword ptr [eax + N], ecx ; mov byte ptr [eax + N], cl ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax + N], ecx ; movss dword ptr [eax + N], xmm0 ; movss dword ptr [eax + N], xmm0 ; mov byte ptr [eax + N], N ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax], A ; mov dword ptr [eax + N], A ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE", "/GR-"]
PRELUDE = ""
OFFS = [0x08, 0x0c, 0x14, 0x18, 0x1c, 0x28, 0x2c, 0x30, 0x34, 0x38, 0x3c, 0x40, 0x44, 0x48, 0x4c, 0x5c, 0x60, 0x64]
def emit(va, A, N):
    s = "extern char g_%08x[], g_%08x[], g_%08x[];\n" % (A[0], A[1], A[2])
    s += "__declspec(naked) void* __fastcall FUN_%08x(void* p) {\n  __asm {\n" % va
    s += "    xorps xmm0, xmm0\n    mov eax, ecx\n    mov dword ptr [eax+4], offset g_%08x\n    xor ecx, ecx\n" % A[0]
    s += "    mov dword ptr [eax+0x08], ecx\n    mov byte ptr [eax+0x0c], cl\n"
    for o in (0x14, 0x18, 0x1c):
        s += "    mov dword ptr [eax+0x%02x], ecx\n" % o
    s += "    movss dword ptr [eax+0x28], xmm0\n    movss dword ptr [eax+0x2c], xmm0\n    mov byte ptr [eax+0x30], 1\n"
    for o in (0x34, 0x38, 0x3c, 0x40, 0x44, 0x48, 0x4c, 0x5c, 0x60, 0x64):
        s += "    mov dword ptr [eax+0x%02x], ecx\n" % o
    s += "    mov dword ptr [eax], offset g_%08x\n    mov dword ptr [eax+4], offset g_%08x\n    ret\n  }\n}\n" % (A[1], A[2])
    return s, "?FUN_%08x@@YIPAXPAX@Z" % va
