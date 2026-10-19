// src/game/SPEngine/SPGraphicsMorphModel.cpp -- migrated from slice(s) s0075a550, s00759540, s00758240 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsMorphModel.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int  __cdecl FUN_00732220(void* a, void* b, void* c);
extern "C" void* __cdecl operator_new_graph(unsigned size);
extern "C" void  __cdecl FUN_00757ff0_stub(void* self, void* a, void* b);
#include <intrin.h>

// ---- items of slice s00758240 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RCObj { void* vptr; long refcount; };
static inline void RCRelease(RCObj* p) {
    if (p && _InterlockedExchangeAdd(&p->refcount, -1) == 1) {
        *((long*)&p->refcount) = 1;
        ((void (__thiscall*)(RCObj*, int))p->vptr)(p, 1);
    }
}
extern "C" int  __cdecl FUN_00732220(void* a, void* b, void* c);
extern "C" void* __cdecl operator_new_graph(unsigned size);
extern "C" void  __cdecl FUN_00757ff0_stub(void* self, void* a, void* b);
struct At6 {
    RCObj* p;
    int a, b, c, d, e;
    __declspec(noinline) At6& operator=(const At6& o);
};
struct C582b0 {
    char pad[0x20];
    bool Build(void* arg, At6* tmp, void** out);
};
// ---- items of slice s00758240 end

// ---- items of slice s00759540 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_00729c60(void* self, void* out, void* flag);
extern "C" void  __cdecl FUN_00777bf0(void);
extern "C" void  __cdecl FUN_00777c10(void);
extern "C" void  __cdecl FUN_007789d0(void* p);
extern "C" void  __cdecl FUN_011f2bc0(void* p);
extern "C" void  __cdecl FUN_011f9710(void* p);
extern "C" void  __cdecl SetShaderData(void* p);
extern "C" int   __cdecl FUN_00b41ea0(void* a, void* b, void* c, unsigned char d);
static inline void RCAddRef(RCObj* p) { if (p) _InterlockedIncrement(&p->refcount); }
struct RCArray { RCObj** mBegin; RCObj** mEnd; RCObj** mCap; void DoInsertValue(RCObj** end, RCObj** src); };
struct WeightObj { int Weight(); };
struct C59e80 {
    char pad[0x20];
    WeightObj** mBegin;   // +0x20
    WeightObj** mEnd;     // +0x24
    int Sum();
    bool CopyTo(RCArray* out);
    void Iterate();
    void* F59ff0(void* a, void* b);
    bool Bounds(unsigned* bounds, unsigned* flag);
};
struct MeshCacheEntry { void Dispatch(int* param_2, int param_3); };
// ---- items of slice s00759540 end

// ---- items of slice s0075a550 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_00759c80(void* p);
struct RawVec { void* mBegin; void* mEnd; void* mCap; };
struct ClassX {
    void* vt0; void* vt1;
    char pad08[0xc - 8];
    RawVec vec0;        // +0xc
    char pad1[0x20 - 0x18];
    RawVec vec20;       // +0x20
    char pad2[0x34 - 0x2c];
    RawVec vec34;       // +0x34
    char pad3[0x48 - 0x40];
    char sub48[0x14];   // +0x48
    void* p5c;          // +0x5c
    void Dtor();
    void* New70();
};
// ---- items of slice s0075a550 end

// @ 0x007582b0
bool C582b0::Build(void* arg, At6* tmp, void** out)
{
    if (!FUN_00732220(tmp, (char*)this + 0x20, arg)) return false;
    void* p = operator_new_graph(0x28);
    if (p) { FUN_00757ff0_stub(p, this, tmp); }
    *out = p;
    (*(void (__thiscall**)(void*))*(void**)p)(p);
    RCRelease(tmp->p);
    return true;
}

// @ 0x00759e80
int C59e80::Sum()
{
    int n = (int)(mEnd - mBegin);
    int total = 0;
    for (int i = 0; i < n; ++i) total += mBegin[i]->Weight();
    return total;
}

// @ 0x00759ec0
void MeshCacheEntry::Dispatch(int* param_2, int param_3)
{
    int* param_1 = (int*)this;
    int n = (param_1[1] - *param_1) >> 2;
    for (int i = 0; i < n; ++i) {
        int local_8 = *(int*)(*param_1 + i * 4);
        int local_c = *(int*)(param_1[10] + i * 4);
        int iVar1 = *(int*)(param_1[0xf] + i * 4);
        int iVar4 = *(int*)(param_1[5] + i * 4);
        int local_14 = 0;
        int local_10 = iVar1;
        if (param_2 != 0) {
            int* end = (int*)param_2[1];
            int* it = (int*)FUN_00b41ea0((void*)*param_2, end, &local_10, *(unsigned char*)(param_2 + 5));
            if (it == end || iVar1 < *it || it == it + 2) it = end;
            if (it != end) local_14 = it[1];
        }
        FUN_00777bf0();
        if (iVar4 != 0) {
            SetShaderData(*(void**)(iVar4 + 4));
            FUN_011f2bc0(*(void**)(iVar4 + 4));
        }
        if (local_14 != 0) FUN_007789d0((void*)local_14);
        if (param_3 != 0) FUN_007789d0((void*)param_3);
        if (local_c != 0) { FUN_011f2bc0((void*)local_c); }
        if (local_8 != 0) FUN_011f9710((void*)local_8);
        FUN_00777c10();
    }
}

// @ 0x00759ff0
void* C59e80::F59ff0(void* a, void* b)
{ (void)a; (void)b; return 0; }

// @ 0x0075a140
void* __cdecl FUN_0075a140(void* a)
{ (void)a; return 0; }

// @ 0x0075a260
void __fastcall FUN_0075a260(C59e80* self)
{ (void)self; }

// @ 0x0075a420
bool C59e80::Bounds(unsigned* bounds, unsigned* flag)
{
    C59e80* self = this;
    if (bounds) {
        bounds[0] = 0x7f7fffff; bounds[1] = 0x7f7fffff; bounds[2] = 0x7f7fffff;
        bounds[3] = 0xff7fffff; bounds[4] = 0xff7fffff; bounds[5] = 0xff7fffff;
    }
    if (flag) *flag = 0;
    self->Iterate();
    int n = (int)(self->mEnd - self->mBegin);
    for (int i = 0; i < n; ++i)
        FUN_00729c60((void*)self->mBegin[i], bounds, flag);
    return true;
}

// @ 0x0075a4e0
bool C59e80::CopyTo(RCArray* out)
{
    Iterate();
    int n = (int)(mEnd - mBegin);
    for (int i = 0; i < n; ++i) {
        RCObj** src = (RCObj**)&mBegin[i];
        if (out->mEnd < out->mCap) {
            RCObj** slot = out->mEnd;
            out->mEnd = slot + 1;
            if (slot) {
                RCObj* v = *src;
                *slot = v;
                if (v) RCAddRef(v);
            }
        } else {
            out->DoInsertValue(out->mEnd, src);
        }
    }
    return true;
}

// @ 0x0075a620
void* ClassX::New70()
{
    void* p = operator_new_graph(0x70);
    if (p) FUN_00759c80(p);
    return p;
}
