# cdecl f(obj, vec): n = (vec->end - vec->begin) / sizeof(T); obj->vf20()->vf18() -> write(.., &n, 1, 0);
# for each element: process(obj, &elem); then tail-call obj->vf1c().
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; mov ecx, dword ptr [edi + N] ; sub ecx, dword ptr [edi] ; mov eax, A ; imul ecx ; mov eax, dword ptr [ebx] ; sar edx, N ; mov esi, edx ; shr esi, N ; add esi, edx ; mov edx, dword ptr [eax + N] ; mov ecx, ebx ; call edx ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; mov dword ptr [esp + N], esi ; call eax ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; push eax ; call EXT ; mov esi, dword ptr [edi] ; mov edi, dword ptr [edi + N] ; add esp, N ; cmp esi, edi ; je +N ; push esi ; push ebx ; call EXT ; add esi, N ; add esp, N ; cmp esi, edi ; jne +N ; mov edx, dword ptr [ebx] ; mov eax, dword ptr [edx + N] ; pop edi ; pop esi ; mov ecx, ebx ; pop ebx ; jmp eax'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    size = N[-3]
    v = "%08x" % va
    vs = lambda n: "".join("virtual void x%d(); " % i for i in range(n))
    src = ("struct T_{v} {{ char d[{sz}]; }};\n"
           "struct V_{v} {{ T_{v}* b; T_{v}* e; }};\n"
           "struct St_{v} {{ {p6}virtual void* a6(); }};\n"
           "struct Ob_{v} {{ {p7}virtual void b7(); virtual St_{v}* b8(); }};\n"
           "void* __cdecl W_{v}(void*, void*, int, int);\n"
           "void __cdecl H_{v}(Ob_{v}*, T_{v}*);\n"
           "void FUN_{v}(Ob_{v}* o, V_{v}* vec) {{\n"
           "    int n, c = (int)(vec->e - vec->b);\n"
           "    St_{v}* s = o->b8();\n"
           "    void* x = (n = c, s->a6());\n"
           "    W_{v}(x, &n, 1, 0);\n"
           "    for (T_{v}* p = vec->b, *e = vec->e; p != e; ++p) H_{v}(o, p);\n"
           "    o->b7();\n}}\n").format(v=v, sz=size, p6=vs(6), p7=vs(7))
    return src, "?FUN_%s@@YAXPAUOb_%s@@PAUV_%s@@@Z" % (v, v, v)
