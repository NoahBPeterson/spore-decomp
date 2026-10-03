# cdecl f(S* p, void* a, int* o1, S** o2): p && p->vslot9(a,&p) && type==K && (flags&0x10)
# then out params from flags&0x30. Real syntax shape recovered; K = N[0] (word compare imm).
PATTERN = 'mov ecx, dword ptr [esp + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov eax, dword ptr [eax + N] ; lea edx, [esp + N] ; push edx ; mov edx, dword ptr [esp + N] ; push edx ; call eax ; test al, al ; je +N ; mov ecx, dword ptr [esp + N] ; cmp word ptr [ecx + N], N ; jne +N ; movzx eax, word ptr [ecx + N] ; test al, N ; je +N ; test al, N ; je +N ; mov eax, dword ptr [ecx + N] ; jmp +N ; mov eax, N ; mov edx, dword ptr [esp + N] ; mov dword ptr [edx], eax ; test byte ptr [ecx + N], N ; je +N ; mov eax, dword ptr [ecx] ; mov ecx, dword ptr [esp + N] ; mov dword ptr [ecx], eax ; mov al, N ; ret  ; movzx eax, word ptr [ecx + N] ; neg eax ; sbb eax, eax ; and eax, ecx ; mov ecx, dword ptr [esp + N] ; mov dword ptr [ecx], eax ; mov al, N ; ret  ; xor al, al ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct S {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
  virtual bool v9(void* a, S** b);
  int f4; int f8; int fc; unsigned short flags; unsigned short type;
};
"""
def emit(va, A, N):
    return ("bool FUN_%08x(S* p, void* a, int* o1, S** o2) {\n"
            "  if (p && p->v9(a, &p) && p->type == %d && (p->flags & 0x10)) {\n"
            "    *o1 = (p->flags & 0x30) ? p->f8 : 1;\n"
            "    *o2 = (p->flags & 0x30) ? *(S**)p : (p->type ? p : 0);\n"
            "    return true;\n  }\n  return false;\n}" % (va, N[6]),
            "?FUN_%08x@@YA_NPAUS@@PAXPAHPAPAU1@@Z" % va)
