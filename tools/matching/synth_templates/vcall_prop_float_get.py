# thiscall float getter: this->obj->vfn9(id, &prop); if ok && prop->type==0xd, value = *Ext()
PATTERN = 'sub esp, N ; mov ecx, dword ptr [ecx] ; xorps xmm0, xmm0 ; movss dword ptr [esp], xmm0 ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov eax, dword ptr [eax + N] ; lea edx, [esp + N] ; push edx ; push A ; call eax ; test al, al ; je +N ; mov ecx, dword ptr [esp + N] ; cmp word ptr [ecx + N], N ; jne +N ; call EXT ; movss xmm0, dword ptr [eax] ; movss dword ptr [esp], xmm0 ; fld dword ptr [esp] ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = """struct Prop { char pad[0x12]; unsigned short type; };
struct Obj { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
  virtual bool Get(unsigned id, Prop** out); };
float* ext_0041ea70();
"""
def emit(va, A, N):
    return ("struct C_%08x { Obj* o; float F() { float r = 0.0f; if (o) { Prop* p; if (o->Get(0x%xu, &p) && p->type == 0xd) r = *ext_0041ea70(); } return r; } };\n"
            "float (C_%08x::*p_%08x)() = &C_%08x::F;" % (va, A[0], va, va, va)), "?F@C_%08x@@QAEMXZ" % va
