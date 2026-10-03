# /Od thiscall wrapper that forwards 3 stack args plus an uninitialized byte local to an external thiscall:
#   push ebp; mov ebp,esp; sub esp,8; mov [ebp-8],ecx; movzx eax,byte [ebp-L]; push eax; <3 args>; call ext; ret 0xC/0x10
# ret 0x10 variants have an unused 4th int param and the byte at [ebp-2] (declared first of two chars, second used);
# ret 0xC variants have the byte at [ebp-4] (char u[4]).
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; movzx eax, byte ptr [ebp - N] ; push eax ; mov ecx, dword ptr [ebp + N] ; push ecx ; mov edx, dword ptr [ebp + N] ; push edx ; mov eax, dword ptr [ebp + N] ; push eax ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    ret = N[-1]
    loc = N[2]
    c = "C_%08x" % va
    if ret == 0x10 and loc == 2:
        params, body, sig = "int a, int b, int c, int d", "char v; char u; ext(a, b, c, u);", "HHHH"
    elif ret == 0xc and loc == 4:
        params, body, sig = "int a, int b, int c", "char u[4]; ext(a, b, c, u[0]);", "HHH"
    else:
        return "// unsupported", "?x@@YAXXZ"
    src = ("struct %s { void __thiscall ext(int, int, int, char); void __thiscall w(%s); };\n"
           "void %s::w(%s) { %s }\n") % (c, params, c, params, body)
    return src, "?w@%s@@QAEX%s@Z" % (c, sig)
