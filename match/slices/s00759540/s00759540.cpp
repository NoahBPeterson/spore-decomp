// Slice s00759540 (batch w2g3, slice 17).
// SP::`anonymous namespace'::cMorphDrawImpl region.  Several functions are EASTL
// vector instantiations (stride 0x14 and 0x50); the rest are small intrusive and
// mesh-cache helpers.  Built /O2 /arch:SSE with /EHsc.
#include "../../include/types.h"
#include <intrin.h>

// --- intrusive refcount base -------------------------------------------------
struct RCObj { void* vptr; long refcount; };
static inline void RCAddRef(RCObj* p) { if (p) _InterlockedIncrement(&p->refcount); }
static inline void RCRelease(RCObj* p) {
    if (p && _InterlockedExchangeAdd(&p->refcount, -1) == 1) {
        _InterlockedExchange(&p->refcount, 1);
        ((void (__thiscall*)(RCObj*, int))p->vptr)(p, 1);
    }
}
struct RCArray { RCObj** mBegin; RCObj** mEnd; RCObj** mCap; void DoInsertValue(RCObj** end, RCObj** src); };

// --- element / vector layouts ------------------------------------------------
struct Elem14 { int* begin; int* end; int* cap; int a, b; };   // stride 0x14
struct Elem50 { Elem14 e[4]; };                                 // stride 0x50
struct Sub14  { int* begin; int* end; int* cap; int u1, u2; };// stride 0x14 (mesh-cache node part)
struct Node58 { void* vt; long refcount; Sub14 s[4]; };         // 0x58 mesh-cache node
struct VecP   { void** mBegin; void** mEnd; void** mCap; int x, y; };
struct VecI   { int*   mBegin; int*   mEnd; int*   mCap; int x, y; };

struct Elem14Vec {
    Elem14* mBegin; Elem14* mEnd; Elem14* mCap; int x, y;
    void InsertN(void* pos, unsigned n, void* val);
    void ResizeN(unsigned n);
    void EraseN(void* first, void* last);   // 0x007594F0 (declared only)
};
struct Elem50Vec {
    Elem50* mBegin; Elem50* mEnd; Elem50* mCap; int x, y;
    Elem50* EraseN(Elem50* first, Elem50* last);
    void InsertN(Elem50* pos, unsigned n, Elem50* val);
    void ResizeN(unsigned n);
};
struct MeshCacheEntry { void Dispatch(int* param_2, int param_3); };
struct WeightObj { int Weight(); };

// --- original callees (relocations masked by the checker) --------------------
extern "C" void* __cdecl FUN_00f473a0(unsigned size, const char* name, int, int, const char* file, int line);
extern "C" void  __cdecl FUN_00f47380(void* p);
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned n);

// Elem14 (stride 0x14) primitives
extern "C" void  __fastcall FUN_0050d440(void* self, void* src);          // copy-ctor
extern "C" void  __cdecl FUN_00758950(void* dst, unsigned n, void* src);  // uninit fill_n
extern "C" void  __cdecl FUN_00758860(void** out, void* first, void* last, void* dest); // uninit copy
extern "C" void  __cdecl FUN_00758b20(void* first, void* last, void* destEnd);          // move_backward
extern "C" void  __cdecl FUN_00758f40(void* first, void* last, void* src);              // fill

// Elem50 (stride 0x50) primitives
extern "C" void* __fastcall FUN_00758b60(void* self, void* src);          // copy-ctor
extern "C" void  __cdecl FUN_00758c90(void** out, void* first, void* last, void* dest); // uninit copy
extern "C" void  __cdecl FUN_00758d10(void* dst, unsigned n, void* src);  // uninit fill_n
extern "C" void  __cdecl FUN_00758d90(void* first, void* last, void* out);// uninit copy
extern "C" void* __cdecl FUN_00758e20(void* first, void* last, void* dest);             // assign copy
extern "C" void  __cdecl FUN_00758e80(void* first, void* last, void* destEnd);          // assign backward
extern "C" void  __cdecl FUN_00758f70(void* first, void* last, void* src);              // assign fill
extern "C" void* __cdecl FUN_00759790(void* first, void* last, void* out);// destruct range
extern "C" void  __fastcall FUN_00759420(void* self);                     // dtor

// vector / container services
extern "C" void  __fastcall FUN_00758ee0(void* self, int n);              // int-vector resize
extern "C" void  __fastcall FUN_004cd3c0(void* self, int n);              // int-vector resize
extern "C" void  __fastcall FUN_0041ee90(void* self, int n);              // ptr-vector resize
extern "C" void* __fastcall FUN_00733070(void* self, int n, void* alloc); // ptr-vector init
extern "C" void  __cdecl FUN_00762d70(int n, void* p);                    // free range
extern "C" void  __cdecl FUN_0047c800(void** out, void* first, void* last, void* dest, void* tag);
extern "C" void  __cdecl FUN_00738e90(void* a, void* b, void* c, void* d);
extern "C" char  __cdecl FUN_00758fc0(void* src, void* dst, void* a, void* b);
extern "C" void  __fastcall FUN_006ec4a0(void* self, void* end, void* src);
extern "C" void  __fastcall FUN_004558a0(void* self, void* end, void* src);

// mesh-cache / D3D helpers
extern "C" void* __cdecl FUN_0067dd70(void);
extern "C" int   __cdecl FUN_0071ddc0(void* self, int a, int b, int c, int d);
extern "C" void* __cdecl FUN_007580a0(void* self);
extern "C" int*  __fastcall FUN_011edcf0(void* self, int a);
extern "C" void  __cdecl FUN_0072ace0(void* a, int b, int c, void* t, int d, int e);
extern "C" void  __cdecl FUN_0072b630(void* a, int b, void* c, void* d, int e, int f, int g, int h, int i);
extern "C" void  __cdecl FUN_00777bf0(void);
extern "C" void  __cdecl FUN_00777c10(void);
extern "C" char  __fastcall FUN_006a25a0(void* self, void* arg);
extern "C" void  __cdecl FUN_00729c60(void* self, void* out, void* flag);
extern "C" int*  __cdecl FUN_00b41ea0(void* beg, void* end, void* key, unsigned char flag);
extern "C" void  __cdecl SetShaderData(void* shader);
extern "C" void  __cdecl FUN_007789d0(void* p);
extern "C" void  __cdecl FUN_011f2bc0(void* p);
extern "C" void  __cdecl FUN_011f9710(void* p);

// --- data --------------------------------------------------------------------
extern const char g_Tag[];      // 0x013eb8a4
extern const char g_File[];     // 0x013ebb38 (EASTL/allocator.h)
extern char g_013ef094[];       // 0x013ef094
extern char g_013eb8d0[];       // 0x013eb8d0
extern char g_0140dab0[];       // 0x0140dab0
extern char g_0140daac[];       // 0x0140daac
extern void* g_p15fd918;        // 0x015fd918
extern float g_f140da1c, g_f13f51ac;

struct C59e80 {
    void* vt;            // +0x00
    void* vt2;           // +0x04
    void* p08;           // +0x08
    VecP  v0c;           // +0x0c
    WeightObj** mBegin;  // +0x20
    WeightObj** mEnd;    // +0x24
    void** mCap20;       // +0x28
    int   mX20;          // +0x2c
    int   mY20;          // +0x30
    Elem14Vec v34;       // +0x34
    Elem50Vec v48;       // +0x48
    VecI  v5c;           // +0x5c
    int Sum();
    bool CopyTo(RCArray* out);
    void Iterate();
    bool F59ff0(RCArray* out);
    bool Bounds(unsigned* bounds, unsigned* flag);
};

// ---------------------------------------------------------------------------
// @ 0x00759540   eastl::vector<Elem14>::insert(pos, n, value)
// ---------------------------------------------------------------------------
void Elem14Vec::InsertN(void* posv, unsigned n, void* valv) {
    Elem14* pos = (Elem14*)posv;
    Elem14* val = (Elem14*)valv;
    unsigned freeN = (unsigned)((char*)mCap - (char*)mEnd) / 0x14;
    if (n > freeN) {
        unsigned old = (unsigned)((char*)mEnd - (char*)mBegin) / 0x14;
        unsigned newcap = old * 2;
        if (old == 0) newcap = 1;
        unsigned want = old + n;
        if (newcap <= want) newcap = want;
        Elem14* nb = newcap ? (Elem14*)FUN_00f473a0(newcap * 0x14, g_Tag, 0, 0, g_File, 0xd1) : 0;
        memcpy(nb, mBegin, (unsigned)((char*)pos - (char*)mBegin));
        Elem14* at = (Elem14*)((char*)nb + ((char*)pos - (char*)mBegin));
        FUN_00758950(at, n, val);
        memcpy((char*)at + n * 0x14, pos, (unsigned)((char*)mEnd - (char*)pos));
        Elem14* ne = (Elem14*)((char*)at + n * 0x14 + ((char*)mEnd - (char*)pos));
        if (mBegin && ((int*)mBegin)[-1] != 0)
            FUN_00f47380(mBegin);
        mBegin = nb;
        mEnd = ne;
        mCap = nb + newcap;
    } else if (n) {
        Elem14 temp;
        FUN_0050d440(&temp, val);
        Elem14* oldEnd = mEnd;
        unsigned after = (unsigned)((char*)oldEnd - (char*)pos) / 0x14;
        if (n < after) {
            Elem14* slot;
            FUN_00758860((void**)&slot, (Elem14*)((char*)oldEnd - n * 0x14), oldEnd, oldEnd);
            mEnd = (Elem14*)((char*)mEnd + n * 0x14);
            FUN_00758b20(pos, (Elem14*)((char*)oldEnd - n * 0x14), oldEnd);
            FUN_00758f40(pos, (Elem14*)((char*)pos + n * 0x14), &temp);
        } else {
            unsigned extra = n - after;
            FUN_00758950(oldEnd, extra, &temp);
            mEnd = (Elem14*)((char*)mEnd + extra * 0x14);
            Elem14* slot;
            FUN_00758860((void**)&slot, pos, oldEnd, mEnd);
            mEnd = (Elem14*)((char*)mEnd + after * 0x14);
            FUN_00758f40(pos, oldEnd, &temp);
        }
        if (temp.begin && ((int*)temp.begin)[-1] != 0)
            FUN_00f47380(temp.begin);
    }
}

// ---------------------------------------------------------------------------
// @ 0x007597d0
// ---------------------------------------------------------------------------
void Elem14Vec::ResizeN(unsigned n) {
    unsigned have = (unsigned)((int32_t)((char*)mEnd - (char*)mBegin) / 0x14);
    if (have > n) {
        EraseN((char*)mBegin + n * 0x14, mEnd);
    } else {
        Elem14 value = {};
        InsertN(mEnd, n - have, &value);
    }
}

// ---------------------------------------------------------------------------
// @ 0x007598f0   eastl::vector<Elem50>::erase(first, last)
// ---------------------------------------------------------------------------
Elem50* Elem50Vec::EraseN(Elem50* first, Elem50* last) {
    Elem50* p = (Elem50*)FUN_00758e20(last, mEnd, first);
    while (p < mEnd) {
        FUN_00759420(p);
        p = (Elem50*)((char*)p + 0x50);
    }
    mEnd = (Elem50*)((char*)mEnd + ((char*)last - (char*)first));
    return first;
}

// ---------------------------------------------------------------------------
// @ 0x00759950   eastl::vector<Elem50>::insert(pos, n, value)
// ---------------------------------------------------------------------------
void Elem50Vec::InsertN(Elem50* pos, unsigned n, Elem50* val) {
    unsigned freeN = (unsigned)((char*)mCap - (char*)mEnd) / 0x50;
    if (n > freeN) {
        unsigned old = (unsigned)((char*)mEnd - (char*)mBegin) / 0x50;
        unsigned newcap = old * 2;
        if (old == 0) newcap = 1;
        unsigned want = old + n;
        if (newcap <= want) newcap = want;
        Elem50* nb = newcap ? (Elem50*)FUN_00f473a0(newcap * 0x50, g_Tag, 0, 0, g_File, 0xd1) : 0;
        unsigned pre = (unsigned)((char*)pos - (char*)mBegin) / 0x50;
        FUN_00758d90(mBegin, pos, nb);
        FUN_00759790(mBegin, pos, 0);
        FUN_00758d10(nb + pre, n, val);
        Elem50* ne = (Elem50*)((char*)nb + (pre + n) * 0x50 + ((char*)mEnd - (char*)pos));
        FUN_00758d90(pos, mEnd, (Elem50*)((char*)nb + (pre + n) * 0x50));
        FUN_00759790(pos, mEnd, 0);
        if (mBegin && ((int*)mBegin)[-1] != 0)
            FUN_00f47380(mBegin);
        mBegin = nb;
        mEnd = ne;
        mCap = nb + newcap;
    } else if (n) {
        Elem50 temp;
        FUN_00758b60(&temp, val);
        Elem50* oldEnd = mEnd;
        unsigned after = (unsigned)((char*)oldEnd - (char*)pos) / 0x50;
        if (n < after) {
            Elem50* slot;
            FUN_00758c90((void**)&slot, (Elem50*)((char*)oldEnd - n * 0x50), oldEnd, oldEnd);
            mEnd = (Elem50*)((char*)mEnd + n * 0x50);
            FUN_00758e80(pos, (Elem50*)((char*)oldEnd - n * 0x50), oldEnd);
            FUN_00758f70(pos, (Elem50*)((char*)pos + n * 0x50), &temp);
        } else {
            unsigned extra = n - after;
            FUN_00758d10(oldEnd, extra, &temp);
            mEnd = (Elem50*)((char*)mEnd + extra * 0x50);
            Elem50* slot;
            FUN_00758c90((void**)&slot, pos, oldEnd, mEnd);
            mEnd = (Elem50*)((char*)mEnd + after * 0x50);
            FUN_00758f70(pos, oldEnd, &temp);
        }
        FUN_00759420(&temp);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00759ba0   eastl::vector<Elem50>::resize(n)
// ---------------------------------------------------------------------------
void Elem50Vec::ResizeN(unsigned n) {
    unsigned have = (unsigned)((char*)mEnd - (char*)mBegin) / 0x50;
    if (have < n) {
        Elem50 value = {};
        InsertN(mEnd, n - have, &value);
        FUN_00759420(&value);
    } else {
        EraseN(mBegin + n, mEnd);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00759c80   cMorphDrawImpl mesh-cache constructor (ecx = this, ret 4)
// ---------------------------------------------------------------------------
void* __fastcall FUN_00759c80(void* self, int, int* src) {
    C59e80* p = (C59e80*)self;
    p->vt2 = g_013ef094;
    p->p08 = 0;
    p->vt = g_0140dab0;
    p->vt2 = g_0140daac;
    int n = (src[1] - src[0]) >> 2;
    FUN_00733070(&p->v0c, n, src + 3);
    void* out = 0;
    FUN_0047c800(&out, (void*)src[0], (void*)src[1], p->v0c.mBegin, 0);
    p->v0c.mEnd = (void**)out;
    p->mBegin = 0; p->mEnd = 0; p->mCap20 = 0;
    p->v34.mBegin = 0; p->v34.mEnd = 0; p->v34.mCap = 0;
    p->v48.mBegin = 0; p->v48.mEnd = 0; p->v48.mCap = 0;
    p->v5c.mBegin = 0; p->v5c.mEnd = 0; p->v5c.mCap = 0;
    FUN_0041ee90(&p->mBegin, n);
    p->v34.ResizeN(n);
    p->v48.ResizeN(n);
    FUN_004cd3c0(&p->v5c, n);
    for (int i = 0; i < n; ++i) {
        Node58* node = (Node58*)FUN_00f473a0(0x58, g_Tag, 0, 0, 0, 0);
        if (node) {
            node->vt = g_013ef094;
            node->refcount = 0;
            node->vt = g_013eb8d0;
            node->s[0].begin = 0; node->s[0].end = 0; node->s[0].cap = 0;
            node->s[1].begin = 0; node->s[1].end = 0; node->s[1].cap = 0;
            node->s[2].begin = 0; node->s[2].end = 0; node->s[2].cap = 0;
            node->s[3].begin = 0; node->s[3].end = 0; node->s[3].cap = 0;
        }
        Node58* old = (Node58*)p->v0c.mBegin[i];
        if (node != old) {
            if (node) RCAddRef((RCObj*)node);
            p->v0c.mBegin[i] = node;
            if (old) RCRelease((RCObj*)old);
        }
        FUN_00738e90(0, 0, p->v0c.mBegin[i], p->mBegin[i]);
        p->v5c.mBegin[i] = 0;
    }
    return p;
}

// ---------------------------------------------------------------------------
// @ 0x00759e80   sum of element weights
// ---------------------------------------------------------------------------
int C59e80::Sum() {
    int n = (int)(mEnd - mBegin);
    int total = 0;
    for (int i = 0; i < n; ++i) total += mBegin[i]->Weight();
    return total;
}

// ---------------------------------------------------------------------------
// @ 0x00759ec0   cMorphDrawImpl::MeshCacheEntry::Dispatch
// ---------------------------------------------------------------------------
void MeshCacheEntry::Dispatch(int* param_2, int param_3) {
    int* param_1 = (int*)this;
    int n = (param_1[1] - *param_1) >> 2;
    for (int i = 0; i < n; ++i) {
        int iVar1 = *(int*)(param_1[0xf] + i * 4);
        int local_8 = *(int*)(*param_1 + i * 4);
        int local_c = *(int*)(param_1[10] + i * 4);
        int iVar4 = *(int*)(param_1[5] + i * 4);
        int local_14 = 0;
        if (param_2 != 0) {
            int* end = (int*)param_2[1];
            int* it = (int*)FUN_00b41ea0((void*)*param_2, end, &iVar1, *(unsigned char*)(param_2 + 5));
            if (it != end && iVar1 >= *it && it != it + 2)
                local_14 = it[1];
        }
        FUN_00777bf0();
        if (iVar4 != 0) {
            SetShaderData(*(void**)(iVar4 + 4));
            FUN_011f2bc0(*(void**)(iVar4 + 4));
        }
        if (local_14 != 0) FUN_007789d0((void*)local_14);
        if (param_3 != 0) FUN_007789d0((void*)param_3);
        if (local_c != 0) FUN_011f2bc0((void*)local_c);
        if (local_8 != 0) FUN_011f9710((void*)local_8);
        FUN_00777c10();
    }
}

// ---------------------------------------------------------------------------
// @ 0x00759ff0   gather shader values into out
// ---------------------------------------------------------------------------
bool C59e80::F59ff0(RCArray* out) {
    void* mgr = FUN_0067dd70();
    int n = (int)((char*)v0c.mEnd - (char*)v0c.mBegin) / 4;
    for (int i = 0; i < n; ++i) {
        Node58* node = (Node58*)v0c.mBegin[i];
        int idx = FUN_0071ddc0(node, 0x15, 0, 6, 0xe);
        if (idx < 0) continue;
        unsigned char* d = (unsigned char*)node->s[0].begin + idx * 0x20;
        int count = *(int*)(d + 0x10);
        void* data = *(void**)(d + 0x14);
        unsigned short stride = *(unsigned short*)(d + 0x1a);
        void* ref = *(void**)(d + 0x1c);
        if (ref) ((void (__thiscall*)(void*))(*(void***)ref)[0])(ref);
        if (count > 0) {
            for (int k = 0; k < count; ++k) {
                int value = ((int (__thiscall*)(void*, void*))(*(void***)mgr)[10])(mgr, *(void**)data);
                if (out->mEnd < out->mCap) {
                    RCObj** slot = out->mEnd;
                    out->mEnd = slot + 1;
                    if (slot) *(int*)slot = value;
                } else {
                    out->DoInsertValue(out->mEnd, (RCObj**)&value);
                }
                data = (char*)data + stride;
            }
        }
        if (ref) ((void (__thiscall*)(void*))(*(void***)ref)[1])(ref);
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x0075a140   rebuild v0/v1/v2/v3 of a mesh-cache node
// ---------------------------------------------------------------------------
void __fastcall FUN_0075a140(Elem50* self, int, void* arg) {
    if (self->e[0].begin != self->e[0].end) {
        FUN_00762d70((int)(self->e[0].end - self->e[0].begin), self->e[0].begin);
        FUN_00758ee0(&self->e[0], 0);
        FUN_00758ee0(&self->e[2], 0);
        FUN_00758ee0(&self->e[1], 0);
        FUN_004cd3c0(&self->e[3], 0);
    }
    FUN_0072b630(arg, 0, &self->e[0], &self->e[1], 0, 0, 0, 0, -1);
    int n = (int)(self->e[0].end - self->e[0].begin);
    for (int i = 0; i < n; ++i) {
        void* a = (void*)self->e[1].begin[i];
        int value = **(int**)((char*)self->e[0].begin[i] + 0x24);
        int flag = -1;
        if (a && ((void**)a)[1] && (((char*)((void**)a)[1])[8] & 8)) {
            int* r = (int*)FUN_011edcf0((char*)((void**)a)[1], 0x20f);
            if (r) flag = *r;
        }
        if (self->e[2].end < self->e[2].cap) {
            int* slot = self->e[2].end;
            self->e[2].end = slot + 1;
            if (slot) *slot = value;
        } else {
            FUN_006ec4a0(&self->e[2], self->e[2].end, &value);
        }
        if (self->e[3].end < self->e[3].cap) {
            int* slot = self->e[3].end;
            self->e[3].end = slot + 1;
            if (slot) *slot = flag;
        } else {
            FUN_004558a0(&self->e[3], self->e[3].end, &flag);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x0075a260   cMorphDrawImpl::Dispatch
// ---------------------------------------------------------------------------
void __fastcall FUN_0075a260(C59e80* self, int, int* a1, int* a2, int a3) {
    if (!FUN_006a25a0(g_p15fd918, (void*)0x26edb8f))
        return;
    FUN_00777bf0();
    int uVar1 = *(int*)((char*)a2 + 0x44);
    int n = (int)((char*)self->v0c.mEnd - (char*)self->v0c.mBegin) / 4;
    for (int i = 0; i < n; ++i) {
        void* sh = FUN_007580a0(self->v0c.mBegin[i]);
        int sd = 0;
        if (sh && (((char*)sh)[8] & 8))
            sd = (int)FUN_011edcf0(sh, 0x200);
        char changed = FUN_00758fc0((void*)sd, (void*)&self->v34.mBegin[i],
                                    self->v0c.mBegin[i], (void*)self->mBegin[i]);
        if (!changed) {
            int* c = &self->v5c.mBegin[i];
            if (*c < 10) {
                (*c)++;
            } else {
                if (*c == 10) {
                    FUN_0075a140((Elem50*)&self->v48.mBegin[i], 0, (void*)self->mBegin[i]);
                    (*c)++;
                }
                int* t = (*(int*)((char*)a1 + 0x44) == *(int*)((char*)a1 + 0x48))
                             ? 0 : (int*)((char*)a1 + 0x58);
                ((MeshCacheEntry*)&self->v48.mBegin[i])->Dispatch(t, uVar1);
                continue;
            }
        } else {
            Elem50* q = (Elem50*)&self->v48.mBegin[i];
            if (q->e[0].begin != q->e[0].end) {
                FUN_00762d70((int)(q->e[0].end - q->e[0].begin), q->e[0].begin);
                FUN_00758ee0(&q->e[0], 0);
                FUN_00758ee0(&q->e[2], 0);
                FUN_00758ee0(&q->e[1], 0);
                FUN_004cd3c0(&q->e[3], 0);
            }
            self->v5c.mBegin[i] = 0;
        }
        int* t = ((*(int*)((char*)a1 + 0x48) - *(int*)((char*)a1 + 0x44)) & 0xfffffffc)
                     ? (int*)((char*)a1 + 0x58) : 0;
        FUN_0072ace0((void*)self->mBegin[i], a3, uVar1, t, 0, 0);
    }
    FUN_00777c10();
}

// ---------------------------------------------------------------------------
// @ 0x0075a420
// ---------------------------------------------------------------------------
bool C59e80::Bounds(unsigned* bounds, unsigned* flag) {
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
