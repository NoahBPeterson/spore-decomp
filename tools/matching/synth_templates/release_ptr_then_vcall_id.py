# "T* p = *pp; if (p) { *pp = 0; p->Release(); } sink->vfn(TYPE_ID, pp, 0); return true;"
# /O2 cdecl free function (e.g. intrusive_ptr reset followed by a virtual
# serializer/factory call with a constant type-id hash), returns bool true.
PATTERN = "push esi ; mov esi, dword ptr [esp + N] ; mov ecx, dword ptr [esi] ; test ecx, ecx ; je +N ; mov dword ptr [esi], N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; push N ; push esi ; push A ; call edx ; mov al, N ; pop esi ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct VObj {\n" +
           "".join("    virtual void v%d() = 0;\n" % i for i in range(64)) +
           "};\n"
           "struct VSink {\n" +
           "".join("    virtual void s%d(unsigned int id, VObj** p, int z) = 0;\n" % i for i in range(256)) +
           "};\n")
def emit(va, A, N):
    # N: [esp+0xc], 0, rel_off, [esp+8], call_off, push z, (id if < 8 hex digits), al
    rel, call, z = N[2] // 4, N[4] // 4, N[5]
    tid = A[0] if A else N[6]
    src = ("bool FUN_%08x(VSink* s, VObj** pp) {\n"
           "    VObj* p = *pp;\n    if (p) { *pp = 0; p->v%d(); }\n"
           "    s->s%d(0x%08xu, pp, %d);\n    return true;\n}") % (va, rel, call, tid, z)
    return src, "?FUN_%08x@@YA_NPAUVSink@@PAPAUVObj@@@Z" % va
