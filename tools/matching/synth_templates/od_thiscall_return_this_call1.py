# /Od thiscall wrapper: calls external member with its one arg, returns this; frame has unused locals.
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp + N] ; push eax ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    size = N[0]
    pad = (size - 4) // 4
    src = ("struct S%08x { void *Callee(void *); void *W(void *a); };\n"
           "void *S%08x::W(void *a) { int loc[%d]; Callee(a); return this; }\n" % (va, va, pad))
    return src, "?W@S%08x@@QAEPAXPAX@Z" % va
