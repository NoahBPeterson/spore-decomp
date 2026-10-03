# void S::f(Obj* a) { P* p = S.p; p->vN(*a->get(1)); int v = ext(); S.q->r->fieldX = v; (S.q->r+Y)->callee(S.q->r->fieldX); }
PATTERN = 'push esi ; mov esi, ecx ; mov ecx, dword ptr [esp + N] ; push N ; call EXT ; mov ecx, dword ptr [esi + N] ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [eax] ; mov edx, dword ptr [edx + N] ; push eax ; call edx ; call EXT ; mov ecx, dword ptr [esi + N] ; mov edx, dword ptr [ecx + N] ; mov dword ptr [edx + N], eax ; mov eax, dword ptr [esi + N] ; mov eax, dword ptr [eax + N] ; mov ecx, dword ptr [eax + N] ; pop esi ; mov dword ptr [esp + N], ecx ; lea ecx, [eax + N] ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""
def emit(va, A, N):
    t = "%08x" % va
    k = N[3] // 4
    virts = " ".join("virtual void v%d(int);" % i for i in range(k + 1))
    src = ("struct O_T { int* get(int); };\n"
           "struct P_T { VIRTS };\n"
           "struct Sub_T { void callee(int); };\n"
           "struct R_T { char pad[YY]; Sub_T sub; };\n"
           "struct Q_T { int pad; R_T* r; };\n"
           "int ext_T();\n"
           "struct S_T { int pad; P_T* p; int pad2; Q_T* q; void FUN_T(O_T* a); };\n"
           "void S_T::FUN_T(O_T* a) {\n"
           "  int* t = a->get(1); P_T* pp = p; pp->vK(*t);\n"
           "  *(int*)((char*)q->r + XX) = ext_T();\n"
           "  ((Sub_T*)((char*)q->r + YY))->callee(*(int*)((char*)q->r + XX));\n"
           "}")
    src = src.replace("VIRTS", virts).replace("vK", "v%d" % k).replace("YY", str(N[11])).replace("XX", str(N[6])).replace("_T", "_" + t)
    return src, "?FUN_%s@S_%s@@QAEXPAUO_%s@@@Z" % (t, t, t)
