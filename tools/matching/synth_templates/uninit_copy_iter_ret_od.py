# /Od uninitialized_copy returning an iterator struct by hidden pointer:
#   for (; first != last; ++first, ++dest) new (dest) T(*first); return R(dest);
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov eax, dword ptr [ebp + N] ; mov dword ptr [ebp - N], eax ; jmp +N ; mov ecx, dword ptr [ebp + N] ; add ecx, N ; mov dword ptr [ebp + N], ecx ; mov edx, dword ptr [ebp - N] ; add edx, N ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp + N] ; xor ecx, ecx ; cmp eax, dword ptr [ebp + N] ; setne cl ; movzx edx, cl ; test edx, edx ; je +N ; mov eax, dword ptr [ebp - N] ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], ecx ; cmp dword ptr [ebp - N], N ; je +N ; mov edx, dword ptr [ebp + N] ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp - N] ; push eax ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov dword ptr [ebp - N], eax ; jmp +N ; mov dword ptr [ebp - N], N ; jmp +N ; mov ecx, dword ptr [ebp + N] ; mov edx, dword ptr [ebp - N] ; mov dword ptr [ecx], edx ; mov eax, dword ptr [ebp + N] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "inline void* operator new(unsigned int, void* p) { return p; }\n"
def emit(va, A, N):
    size = N[4]
    d = dict(S="S_%08x" % va, R="R_%08x" % va, v=va, z=size, L=("int " + ", ".join("u%d" % i for i in range((N[0] - 0x14) // 4)) + ";") if N[0] > 0x14 else "")
    src = ("struct %(S)s { char d[0x%(z)x]; %(S)s(const %(S)s&); };\n"
           "struct %(R)s { %(S)s* p; %(R)s(%(S)s* q) { %(L)s p = q; } };\n"
           "inline bool Ne_%(v)08x(%(S)s* a, %(S)s* b) { return a != b; }\n"
           "inline S_%(v)08x& Dr_%(v)08x(%(S)s* p) { %(S)s* q = p; return *q; }\n"
           "inline void* Pv_%(v)08x(%(S)s* p) { void* r = p; return r; }\n"
           "inline void Cn_%(v)08x(%(S)s* p, %(S)s* f) { ::new (Pv_%(v)08x(p)) %(S)s(Dr_%(v)08x(f)); }\n"
           "%(R)s FUN_%(v)08x(%(S)s* first, %(S)s* last, %(S)s* dest) {\n"
           "    %(S)s* d = dest;\n"
           "    for (; Ne_%(v)08x(first, last); ++first, ++d) Cn_%(v)08x(d, first);\n"
           "    return %(R)s(d);\n}\n") % d
    return src, "?FUN_%08x@@YA?AU%s@@PAU%s@@00@Z" % (va, d["R"], d["S"])
