# /Od /Ob1 member: for (p = begin; p < end; p += stride) {} then call member(this)
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax] ; mov dword ptr [ebp - N], ecx ; jmp +N ; mov edx, dword ptr [ebp - N] ; add edx, N ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [ebp - N] ; cmp ecx, dword ptr [eax + N] ; jae +N ; jmp +N ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    stride = N[5]
    c = "R%08x" % va
    src = ("struct %s { unsigned begin_; unsigned end_; void Fin(); void F(); };\n"
           "void %s::F() {\n  unsigned p;\n  unsigned q[3];\n  for (p = begin_; p < end_; p += %d) {}\n  Fin();\n}\n") % (c, c, stride)
    return src, "?F@%s@@QAEXXZ" % c
