# eastl-like vector copy ctor: n=(src.end-src.begin)/sizeof(T); begin=n?alloc(&alloc,n*sizeof(T),4,0):0;
# end=begin; cap=begin+n; end=uninitialized_copy(src.begin,src.end,begin) -- in an /Od /Ob1 module.
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp + N] ; mov ecx, dword ptr [ebp + N] ; mov eax, dword ptr [eax + N] ; sub eax, dword ptr [ecx] ; cdq  ; mov ecx, N ; idiv ecx ; mov dword ptr [ebp - N], eax ; cmp dword ptr [ebp - N], N ; je +N ; push N ; push N ; mov edx, dword ptr [ebp - N] ; imul edx, edx, N ; push edx ; mov eax, dword ptr [ebp - N] ; add eax, N ; push eax ; call EXT ; add esp, N ; mov dword ptr [ebp - N], eax ; jmp +N ; mov dword ptr [ebp - N], N ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [ebp - N] ; mov dword ptr [ecx], edx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [ecx] ; mov dword ptr [eax + N], edx ; mov eax, dword ptr [ebp - N] ; imul eax, eax, N ; mov ecx, dword ptr [ebp - N] ; add eax, dword ptr [ecx] ; mov edx, dword ptr [ebp - N] ; mov dword ptr [edx + N], eax ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax] ; push ecx ; mov edx, dword ptr [ebp + N] ; mov eax, dword ptr [edx + N] ; push eax ; mov ecx, dword ptr [ebp + N] ; mov edx, dword ptr [ecx] ; push edx ; call EXT ; add esp, N ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ecx + N], eax ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    size = N[5]
    pd = N[0] - 16
    PADS = ("char pad[%d]; char q[32];" % (pd - 32)) if pd > 64 else ("char pad[%d];" % pd)
    t = "T_%08x" % va
    v = "V_%08x" % va
    src = ("struct %s { char d[%d]; };\n"
           "void* AL_%08x(void* a, unsigned n, unsigned al, unsigned fl);\n"
           "%s* UC_%08x(%s* f, %s* l, %s* d);\n"
           "struct %s {\n  %s *b, *e, *c; char al;\n"
           "  %s(const %s& o);\n};\n"
           "%s::%s(const %s& o) {\n"
           "    int n = (o.e - o.b);\n    %s\n"
           "    b = n ? (%s*)AL_%08x(&al, n * sizeof(%s), 4, 0) : 0;\n"
           "    e = b; c = b + n;\n"
           "    e = UC_%08x(o.b, o.e, b);\n}\n") % (
           t, size, va, t, va, t, t, t, v, t, v, v, v, v, v, PADS, t, va, t, va)
    return src, "??0%s@@QAE@ABU0@@Z" % v
