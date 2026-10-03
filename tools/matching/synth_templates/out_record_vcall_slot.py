# thiscall on a secondary-base subobject: fill an out record {vtbl const, this-4, 1, this->vslot()}.
PATTERN = 'push esi ; mov esi, dword ptr [esp + N] ; lea eax, [ecx - N] ; mov dword ptr [esi + N], eax ; mov dword ptr [esi], A ; mov dword ptr [esi + N], N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx + N] ; call eax ; mov dword ptr [esi + N], eax ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "struct OutRec { void* vt; void* self; int a; int b; };\n"
def emit(va, A, N):
    slot = N[5] // 4
    c = "C_%08x" % va
    virt = "".join("virtual void p%d(); " % i for i in range(slot))
    src = ("struct %s { %svirtual int v(); void f(OutRec* o); };\n"
           "void %s::f(OutRec* o) { o->self = (char*)this - 4; o->vt = (void*)0x%08xu; o->a = %d; o->b = v(); }"
           % (c, virt, c, A[0], N[4]))
    return src, "?f@%s@@QAEXPAUOutRec@@@Z" % c
