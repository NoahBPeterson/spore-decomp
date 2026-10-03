# Scalar deleting dtor of a class with two polymorphic bases (second at +off): dtor body calls
# ext(this) (cdecl), clears a global pointer if it equals this, then base vptrs reset, delete this.
PATTERN = 'push esi ; mov esi, ecx ; push esi ; mov dword ptr [esi], A ; mov dword ptr [esi + N], A ; call EXT ; add esp, N ; cmp dword ptr [A], esi ; jne +N ; mov dword ptr [A], N ; test byte ptr [esp + N], N ; mov dword ptr [esi + N], A ; mov dword ptr [esi], A ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    off = N[0]
    gl = "g_%08x" % A[2]
    c = "C_%08x" % va
    pad = ("char pad[%d]; " % (off - 4)) if off > 4 else ""
    src = ("struct X_%s { virtual ~X_%s() {} %s};\n"
           "struct Y_%s { virtual ~Y_%s() {} };\n"
           "struct %s;\nextern %s* %s;\nvoid __cdecl ext_%s(%s*);\n"
           "struct %s : X_%s, Y_%s { %s(); virtual ~%s() { ext_%s(this); if (%s == this) %s = 0; } };\n"
           "%s::%s() {}" % (c, c, pad, c, c, c, c, gl, c, c, c, c, c, c, c, c, gl, gl, c, c))
    return src, "??_G%s@@UAEPAXI@Z" % c
