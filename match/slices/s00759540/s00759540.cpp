// Slice s00759540 (batch w2g3, slice 17).
// SP::`anonymous namespace'::cMorphDrawImpl region.  Several functions are EASTL
// vector instantiations (stride 0x14 and 0x50); the rest are small intrusive and
// mesh-cache helpers.  Built /O2 /arch:SSE with /EHsc.
#include "../../include/types.h"
#include <intrin.h>

struct RCObj { void* vptr; long refcount; };
static inline void RCAddRef(RCObj* p) { if (p) _InterlockedIncrement(&p->refcount); }
struct RCArray { RCObj** mBegin; RCObj** mEnd; RCObj** mCap; void DoInsertValue(RCObj** end, RCObj** src); };

extern "C" void* __cdecl operator_new_graph(unsigned size);
extern "C" void  __cdecl eastl_dealloc(void* p);
extern "C" void  __cdecl FUN_0050d440(void* p);
extern "C" void  __cdecl FUN_00758f40(void* a, void* b, void* c);
extern "C" void  __cdecl FUN_00759100_(void* self);
extern "C" void  __cdecl FUN_00729c60(void* self, void* out, void* flag);
extern "C" int   __cdecl FUN_0071dcc0(void* self);
extern "C" void  __cdecl FUN_00777bf0(void);
extern "C" void  __cdecl FUN_00777c10(void);
extern "C" void  __cdecl FUN_007789d0(void* p);
extern "C" void  __cdecl FUN_011f2bc0(void* p);
extern "C" void  __cdecl FUN_011f9710(void* p);
extern "C" void  __cdecl SetShaderData(void* p);
extern "C" void  __cdecl FUN_00759420(void* p);
extern "C" void  __cdecl FUN_007594f0(void* a, void* b);
extern "C" int   __cdecl FUN_00b41ea0(void* a, void* b, void* c, unsigned char d);
extern "C" void  __cdecl M3Assign(void* dst, const void* src);
extern float g_f140da1c, g_f13f51ac;

// Elem14 (stride 0x14): a small vector {begin,end,cap} + 2 words
struct Elem14 { int* begin; int* end; int* cap; int a, b; };

// ---------------------------------------------------------------------------
// @ 0x00759540   eastl::vector<Elem14>::insert(pos, n, value)
// ---------------------------------------------------------------------------
struct Elem14Vec {
    Elem14* mBegin; Elem14* mEnd; Elem14* mCap;
    void InsertN(void* pos, unsigned n, void* val);
    void ResizeN(unsigned n, void* val);
    int* RangeAssign(int* first, int* last);
    void F59950(void* first, void* last, void* out);
    void F59ba0(void* first, void* last);
};
void Elem14Vec::InsertN(void* pos, unsigned n, void* val) {
    unsigned cap = (unsigned)((char*)mCap - (char*)mBegin) / 0x14;
    if ((unsigned)(((char*)mEnd - (char*)mBegin) / 0x14) < n) {
        unsigned old = (unsigned)(((char*)mEnd - (char*)mBegin) / 0x14);
        unsigned newcap = old * 2;
        if (old == 0) newcap = 1;
        unsigned want = old + n;
        if (want < newcap) want = newcap;
        Elem14* nb = want ? (Elem14*)operator_new_graph(want * 0x14) : 0;
        unsigned sfx = (unsigned)((char*)pos - (char*)mBegin) / 0x14;
        // construct prefix, fill middle, construct suffix
        for (unsigned i = 0; i < sfx; ++i) nb[i] = mBegin[i];
        (void)val;
        for (unsigned i = 0; i < n; ++i) { Elem14* e = &nb[sfx + i]; e->begin = 0; e->end = 0; e->cap = 0; e->a = 0; e->b = 0; }
        for (unsigned i = sfx; i < old; ++i) nb[n + i] = mBegin[i];
        if (mBegin) eastl_dealloc(mBegin);
        mBegin = nb;
        mEnd = nb + n + (mEnd - mBegin);
        mCap = nb + want;
    } else if (n) {
        FUN_0050d440(val);
    }
}

// ---------------------------------------------------------------------------
// @ 0x007597d0
// ---------------------------------------------------------------------------
void Elem14Vec::ResizeN(unsigned n, void* val) {
    unsigned have = (unsigned)(((char*)mEnd - (char*)mBegin) / 0x14);
    if (have > n)
        FUN_007594f0((char*)mBegin + n * 0x14, mEnd);
    else
        InsertN(mEnd, n - have, val);
}

// ---------------------------------------------------------------------------
// @ 0x007598f0   range copy / erase
// ---------------------------------------------------------------------------
int* Elem14Vec::RangeAssign(int* first, int* last) {
    (void)first; (void)last;
    return first;
}

// ---------------------------------------------------------------------------
// @ 0x00759e80   sum of element weights
// ---------------------------------------------------------------------------
struct WeightObj { int Weight(); };
struct C59e80 {
    char pad[0x20];
    WeightObj** mBegin;   // +0x20
    WeightObj** mEnd;     // +0x24
    int Sum();
    bool CopyTo(RCArray* out);
    void Iterate();
    void* F59ff0(void* a, void* b);
};
int C59e80::Sum() {
    int n = (int)(mEnd - mBegin);
    int total = 0;
    for (int i = 0; i < n; ++i) total += mBegin[i]->Weight();
    return total;
}

// ---------------------------------------------------------------------------
// @ 0x0075a4e0
// ---------------------------------------------------------------------------
bool C59e80::CopyTo(RCArray* out) {
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

// ---------------------------------------------------------------------------
// @ 0x00759950
// ---------------------------------------------------------------------------
void Elem14Vec::F59950(void* first, void* last, void* out) {
    (void)first; (void)last; (void)out;
}

// ---------------------------------------------------------------------------
// @ 0x00759ba0
// ---------------------------------------------------------------------------
void Elem14Vec::F59ba0(void* first, void* last) {
    (void)first; (void)last;
}

// ---------------------------------------------------------------------------
// @ 0x00759c80
// ---------------------------------------------------------------------------
void* __cdecl FUN_00759c80(void* a, void* b, void* c) { (void)a; (void)b; (void)c; return 0; }

// ---------------------------------------------------------------------------
// @ 0x00759ec0   cMorphDrawImpl::MeshCacheEntry::Dispatch
// ---------------------------------------------------------------------------
struct MeshCacheEntry { void Dispatch(int* param_2, int param_3); };
void MeshCacheEntry::Dispatch(int* param_2, int param_3) {
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

// ---------------------------------------------------------------------------
// @ 0x00759ff0
// ---------------------------------------------------------------------------
void* C59e80::F59ff0(void* a, void* b) { (void)a; (void)b; return 0; }

// ---------------------------------------------------------------------------
// @ 0x0075a140
// ---------------------------------------------------------------------------
void* __cdecl FUN_0075a140(void* a) { (void)a; return 0; }

// ---------------------------------------------------------------------------
// @ 0x0075a260   cMorphDrawImpl::Dispatch
// ---------------------------------------------------------------------------
void __fastcall FUN_0075a260(C59e80* self) { (void)self; }

// ---------------------------------------------------------------------------
// @ 0x0075a420
// ---------------------------------------------------------------------------
void __cdecl FUN_0075a420(C59e80* self, unsigned* bounds, unsigned* flag) {
    if (bounds) {
        bounds[0] = 0x7f7fffff; bounds[1] = 0x7f7fffff; bounds[2] = 0x7f7fffff;
        bounds[3] = 0xff7fffff; bounds[4] = 0xff7fffff; bounds[5] = 0xff7fffff;
    }
    if (flag) *flag = 0;
    self->Iterate();
    int n = (int)(self->mEnd - self->mBegin);
    for (int i = 0; i < n; ++i)
        FUN_00729c60((void*)self->mBegin[i], bounds, flag);
}
