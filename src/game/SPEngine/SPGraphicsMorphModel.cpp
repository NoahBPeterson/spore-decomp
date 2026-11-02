// src/game/SPEngine/SPGraphicsMorphModel.cpp -- migrated from slice(s) s007571a0, s0075a550, s00759540, s00758240 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsMorphModel.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int  __cdecl FUN_00732220(void* a, void* b, void* c);
extern "C" void* __cdecl operator_new_graph(unsigned size);
extern "C" void  __cdecl FUN_00757ff0_stub(void* self, void* a, void* b);
#include <intrin.h>
#include "SP/cJob.h"
#include "SP/cPropertyList.h"
#include <stddef.h>

// ---- items of slice s00758240 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RCObj { void* vptr; long refcount; };
extern const char g_EASTLAllocFile[];                                       // 0x013ebb38 (EASTL/allocator.h)
extern float g_f140da1c;                                                    // 0x0140da1c (FLT_MAX)
extern float g_f13f51ac;                                                    // 0x013f51ac (-FLT_MAX)
extern float g_f162f028;                                                    // 0x0162f028
extern float g_f162f02c;                                                    // 0x0162f02c
extern float g_f162f030;                                                    // 0x0162f030
extern float g_f1485720;                                                    // 0x01485720
extern "C" void* __cdecl operator_new_graph6(unsigned size, const char* name, int, int, int, int); // 0x00f473a0
extern const char g_GraphicsTag[];                                                          // 0x013EB8A4
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned n);
extern "C" void  __cdecl FUN_0047c800(void** out, void* first, void* last, void* dest, void* tag);
extern "C" void  __cdecl FUN_00729c60(void* self, void* out, void* flag);
extern "C" void  __cdecl FUN_00762d70(int n, void* p);
extern "C" void  __cdecl FUN_00738e90(int n, void* p, int a, int b);
extern "C" void  __cdecl FUN_0072fff0(void* in, void* out);
extern char g_0140da88[];   // 0x0140da88
extern char g_0140da84[];   // 0x0140da84
extern char g_013ef094[];   // 0x013ef094
extern float g_f162f0e8;   // 0x0162f0e8
struct RCObj_s0075_8240 { void* vptr; long refcount; };
static inline void RCAddRef_s0075_8240(RCObj_s0075_8240* p) {
    if (p) _InterlockedIncrement(&p->refcount);
}
static inline void RCRelease(RCObj_s0075_8240* p) {
    if (p && _InterlockedExchangeAdd(&p->refcount, -1) == 1) {
        *((long*)&p->refcount) = 1;
        ((void (__thiscall*)(RCObj_s0075_8240*, int))p->vptr)(p, 1);
    }
}
struct RCArray_s0075_8240 {
    RCObj_s0075_8240** mBegin;
    RCObj_s0075_8240** mEnd;
    RCObj_s0075_8240** mCap;
    void Init(int n, void* src);
    void DoInsertValue(RCObj_s0075_8240** end, RCObj_s0075_8240** src);
};
template<class T> T* xcopy(const T* f, const T* l, T* o) { while (f != l) *o++ = *f++; return o; }
void* __cdecl EAAlloc(unsigned size, const char* name, int, int, const char* file, int line); // 0xf473a0
void  __cdecl operator_delete_arr(void* p);                                 // 0xf47380 operator delete[]
__declspec(dllimport) void __cdecl memmove(void*, const void*, unsigned);   // msvcr90!memmove
struct M3_s0075_8240 {
    float m[9];
    void Assign(const M3_s0075_8240* src);                      // 0x0041cb40
};
extern M3_s0075_8240    g_m3_162f16c_s0075_8240;                                                  // 0x0162f16c
struct At6 {
    RCObj_s0075_8240* p;
    int a, b, c, d, e;
    __declspec(noinline) At6& operator=(const At6& o);
};
struct C582b0 {
    char pad[0x20];
    bool Build(void* arg, void** out);
};
struct Ctor7ff0 { void* Ctor(void* a2, At6* a3); };
struct At6Guard { At6 v; ~At6Guard() { RCRelease(v.p); } };
struct RefVectorDtor { void Destroy(); };   // 0x0041eb80 (thiscall dtor)
struct Holder841 {
    void* vt0;
    void* vt1;
    void* p08;
    RCArray_s0075_8240 vec;
    void* p18;
    Holder841* Ctor(int* src);   // 0x007583e0
    void Dtor();                 // 0x00758540
};
__declspec(noinline) Holder841* __cdecl FUN_007585c0(int* src);
struct C58480 { char pad[0xc]; int* mBegin; int* mEnd; bool Update(float* bounds, float* w); };
struct IntVec {
    int* mBegin; int* mEnd; int* mCap;
    void resize(int n);                          // 0x004afc80 (SpVector<float>::resize)
    void clear(int n);                           // 0x004cd3c0 (vector<int>::clear)
    void Init(int n, void* alloc);               // 0x004aa350
    int* DoInit(unsigned n, int* first, int* last);  // 0x00758630
    void Insert(int* pos, unsigned n, int* val);
};
struct Elem14 {
                int* begin; int* end; int* cap; int a, b;
                void Init(int n, void* src);             // 0x00733070
                void Clear(int);                         // 0x00758ee0
                int* DoInit(unsigned n, int* first, int* last);  // 0x00758630
                Elem14* OpAssign(Elem14* o); };
struct Elem50 { Elem14 a; Elem14 b; Elem14 c; IntVec d; Elem50* Ctor(int* src); };
struct Sub9100 { void f(); };
struct C591f0 {
    char pad[0xc];
    Sub9100* mp0c;
    At6 m10;
    bool Get(At6* out);
};
struct C59210 { char pad[0xc]; RCObj_s0075_8240** mBegin; RCObj_s0075_8240** mEnd; bool CopyTo(RCArray_s0075_8240* out); };
struct Big140 { char pad[0x140]; };
struct Val38 {                     // 0x38-byte prefix copied into the value ctor
    unsigned short w00, w02;
    float f04, f08, f0c, f10;
    M3_s0075_8240 m14;
};
struct Val7e20_s0075_8240 {
    unsigned short w00, w02;
    float f04, f08, f0c, f10;
    M3_s0075_8240 m14;
    unsigned short w38, w3a;
    float f3c, f40, f44, f48;
    M3_s0075_8240 m4c;
    int i70;
    void* p74;
    void* p78;
    Val7e20_s0075_8240* Ctor(Val38* src, void* a2, void* a3);   // 0x00757e20
    void Dtor();                                     // 0x0041f2d0
};
struct Elem7cVec {
    void* mb; void* me; void* mc; int a0c; int a10;
    void push_back(const void* v);                   // 0x0041f650
};
struct Obj140b {
    int* Ctor();                                     // 0x007004d0
};
struct RefVec5 {
    void* mb; void* me; void* mc; int a0c; int a10;
    void Destroy();                                  // 0x0041eb80
};
struct C59420 { Elem14 a; Elem14 b; Elem14 c; IntVec d; };
// ---- items of slice s00758240 end

// ---- items of slice s00759540 begin (TODO(rewrite): local stubs, replace by canonical classes)

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

// ---- items of slice s007571a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl SP_MaterialManager();
extern "C" int   __cdecl FUN_0071ddc0(void* self, int a, int b, int c, int d);
extern int g_vtbl_13ef094[];
extern float g_f162f028, g_f162f02c, g_f162f030, g_f1485720;
extern int g_vtbl_140da78[];
extern int g_vtbl_140da74[];
struct RCObj;
struct M3 { float m[9]; };
extern M3 g_m3_162f16c;
extern "C" void __cdecl M3Assign(M3* dst, const M3* src);
struct Val7e20 {
    uint16_t w00;      // +0
    uint16_t w02;      // +2
    float f04, f08, f0c, f10;   // +4,+8,+c,+10
    M3 m14;            // +0x14
    uint16_t w38, w3a; // +0x38
    float f3c, f40, f44, f48;   // +0x3c..+0x48
    M3 m4c;            // +0x4c
    int   i70;         // +0x70
    RCObj* p74;        // +0x74
    RCObj* p78;        // +0x78
    Val7e20* Ctor(Val7e20* src, RCObj* a2, RCObj* a3);
};
struct Val7ff0 {
    int*   vptr0;  // +0x00
    int*   vptr4;  // +0x04
    int*   p08;    // +0x08
    RCObj* p0c;    // +0x0c
    RCObj* p10;    // +0x10
    int    f14, f18, f1c, f20, f24;   // +0x14..+0x24
    Val7ff0* Ctor(RCObj* a2, int* a3);
};
struct C0755b { void* vptr; char pad[0x10]; };
// ---- items of slice s007571a0 end

// @ 0x00757e20
Val7e20* Val7e20::Ctor(Val7e20* src, RCObj* a2, RCObj* a3)
{
    this->w02 = 0;
    this->w00 = 0;
    this->f04 = g_f162f028;
    this->f08 = g_f162f02c;
    this->f0c = g_f162f030;
    this->f10 = g_f1485720;
    M3Assign(&this->m14, &g_m3_162f16c);
    this->w38 = src->w00;
    this->w3a = src->w02;
    this->f3c = src->f04;
    this->f40 = src->f08;
    this->f44 = src->f0c;
    this->f48 = src->f10;
    M3Assign(&this->m4c, &src->m14);
    this->i70 = -1;
    this->p74 = a2;
    if (a2) ((void (__thiscall*)(RCObj*))a2->vptr)(a2);
    this->p78 = a3;
    if (a3) ++a3->refcount;
    return this;
}

// @ 0x00757ff0
Val7ff0* Val7ff0::Ctor(RCObj* a2, int* a3)
{
    this->vptr4 = g_vtbl_13ef094;
    this->p08 = 0;
    this->vptr0 = g_vtbl_140da78;
    this->vptr4 = g_vtbl_140da74;
    this->p0c = a2;
    if (a2) ((void (__thiscall*)(RCObj*))((void**)a2->vptr)[0])(a2);
    RCObj* r = (RCObj*)a3[0];
    this->p10 = r;
    if (r) _InterlockedIncrement(&r->refcount);
    this->f14 = a3[1];
    this->f18 = a3[2];
    this->f1c = a3[3];
    this->f20 = a3[4];
    this->f24 = a3[5];
    return this;
}

// @ 0x007580a0
C0755b* __cdecl FUN_007580a0(C0755b* self)
{
    void* mm = SP_MaterialManager();
    int idx = FUN_0071ddc0(self, 0x15, 0, 6, 0xe);
    if (idx < 0) return 0;
    char* base = *(char**)((char*)self + 8);
    char* e = base + idx * 0x20;
    RCObj* p1 = *(RCObj**)(e + 0x1c);
    void** p2 = *(void***)(e + 0x14);
    int v = *(int*)(e + 0x10);
    if (p1) ((void (__thiscall*)(RCObj*))((void**)p1->vptr)[0])(p1);
    if (v) {
        int r = (*(int (__thiscall**)(void*, void*))(*(int*)mm + 0x28))(mm, *p2);
        if (r) {
            int out = *(int*)(r + 4);
            if (p1) ((void (__thiscall*)(RCObj*))((void**)p1->vptr)[1])(p1);
            return (C0755b*)out;
        }
    }
    if (p1) ((void (__thiscall*)(RCObj*))((void**)p1->vptr)[1])(p1);
    return 0;
}

// @ 0x00758240
At6& At6::operator=(const At6& o)
{
    RCObj_s0075_8240* op = o.p;
    RCObj_s0075_8240* old = p;
    if (op != old) {
        RCAddRef_s0075_8240(op);
        p = op;
        RCRelease(old);
    }
    a = o.a; b = o.b; c = o.c; d = o.d; e = o.e;
    return *this;
}

// @ 0x007582b0
bool C582b0::Build(void* arg, void** out)
{
    At6Guard g;
    g.v.p = 0; g.v.a = -1; g.v.b = -1; g.v.c = 0; g.v.d = -1; g.v.e = 0;
    if (!FUN_00732220(&g.v, (char*)this + 0x20, arg))
        return false;
    void* p = EAAlloc(0x28, "Graphics", 0, 0, 0, 0);
    if (p)
        p = ((Ctor7ff0*)p)->Ctor(this, &g.v);
    *out = p;
    void** vt = *(void***)p;
    ((void (__thiscall*)(void*))vt[0])(p);
    return true;
}

// @ 0x007583e0
Holder841* Holder841::Ctor(int* src)
{
    vt1 = &g_013ef094;
    p08 = 0;
    vt0 = &g_0140da88;
    vt1 = &g_0140da84;
    vec.Init((src[1] - src[0]) >> 2, src + 3);
    FUN_0047c800((void**)&src, (void*)src[0], (void*)src[1], vec.mBegin, src);
    vec.mEnd = (RCObj_s0075_8240**)src;
    return this;
}

// @ 0x00758480
bool C58480::Update(float* bounds, float* w)
{
    if (bounds) {
        bounds[0] = g_f140da1c;
        bounds[1] = g_f140da1c;
        bounds[2] = g_f140da1c;
        bounds[3] = g_f13f51ac;
        bounds[4] = g_f13f51ac;
        bounds[5] = g_f13f51ac;
    }
    if (w)
        *w = 0.0f;
    int n = (int)((char*)mEnd - (char*)mBegin) >> 2;
    for (int i = 0; i < n; ++i)
        FUN_00729c60((void*)mBegin[i], bounds, w);
    return true;
}

// @ 0x00758540
void Holder841::Dtor()
{
    vt0 = &g_0140da88;
    vt1 = &g_0140da84;
    ((RefVectorDtor*)((char*)this + 0xc))->Destroy();
    vt1 = &g_013ef094;
}

// @ 0x007585c0
Holder841* __cdecl FUN_007585c0(int* src)
{
    Holder841* p = (Holder841*)operator_new_graph6(0x20, g_GraphicsTag, 0, 0, 0, 0);
    if (p) return p->Ctor(src);
    return 0;
}

// @ 0x00758680
void IntVec::Insert(int* pos, unsigned n, int* val)
{
    unsigned free = ((unsigned)((char*)mCap - (char*)mEnd)) >> 2;
    if (n <= free) {
        if (n != 0) {
            int v = *val;
            int* const end = mEnd;
            unsigned tail = (unsigned)(end - pos);
            if (n < tail) {
                int* src = end - n;
                memcpy(end, src, n * 4);
                mEnd += n;
                memmove(end - (src - pos), pos, (unsigned)(src - pos) * 4);
                for (int* q = pos; q != pos + n; ++q)
                    *q = v;
            } else {
                unsigned extra = n - tail;
                for (unsigned i = 0; i < extra; ++i)
                    end[i] = v;
                mEnd += extra;
                mEnd = (int*)memcpy(mEnd, pos, (unsigned)(end - pos) * 4) + tail;
                for (int* r = pos; r != end; ++r)
                    *r = v;
            }
        }
    } else {
        unsigned old = (unsigned)(mEnd - mBegin);
        unsigned newcap = old * 2;
        if (old == 0)
            newcap = 1;
        if (newcap <= old + n)
            newcap = old + n;
        int* nb = newcap ? (int*)EAAlloc(newcap * 4, "Graphics", 0, 0, g_EASTLAllocFile, 0xd1) : 0;
        int* pe = (int*)memcpy(nb, mBegin, (unsigned)(pos - mBegin) * 4) + (pos - mBegin);
        for (unsigned i = 0; i < n; ++i)
            pe[i] = *val;
        int* ne = (int*)memcpy(pe + n, pos, (unsigned)(mEnd - pos) * 4) + (mEnd - pos);
        if (mBegin && ((int*)mBegin)[-1] != 0)
            operator_delete_arr(mBegin);
        mBegin = nb;
        mEnd = ne;
        mCap = nb + newcap;
    }
}

// @ 0x00758860
int* __cdecl FUN_00758860(int* out, int* first, int* last)
{
    *out = (int)first;
    for (; first != last; first += 5) {
        int* b = (int*)*out;
        if (b) {
            int n = (int)((char*)first[1] - (char*)*first) >> 2;
            int* nb = n ? (int*)operator_new_graph(n * 4) : 0;
            b[0] = (int)nb; b[1] = (int)nb; b[2] = (int)(nb + n);
            b[1] = (int)xcopy((int*)*first, (int*)first[1], nb);
        }
        *out += 0x14;
    }
    return out;
}

// @ 0x00758950
void __cdecl FUN_00758950(Elem14* out, unsigned n, int* src)
{
    for (; n != 0; --n, out = (Elem14*)((char*)out + 0x14)) {
        if (out) {
            int c = (int)((char*)src[1] - (char*)*src) >> 2;
            int* nb = c ? (int*)operator_new_graph(c * 4) : 0;
            out->begin = nb; out->end = nb; out->cap = nb + c;
            out->end = xcopy((int*)*src, (int*)src[1], nb);
        }
    }
}

// @ 0x00758a10
Elem14* Elem14::OpAssign(Elem14* o)
{
    if (o != this) {
        int n = (int)(o->end - o->begin);
        if ((unsigned)(cap - begin) < (unsigned)n) {
            int* nb = DoInit((unsigned)n, o->begin, o->end);
            int* old = begin;
            if (old && old[-1] != 0)
                operator_delete_arr(old);
            begin = nb;
            cap = nb + n;
            end = nb + n;
            return this;
        }
        int have = (int)(end - begin);
        if ((unsigned)have < (unsigned)n) {
            memcpy(begin, o->begin, (unsigned)have * 4);
            int* src = o->begin + have;
            memcpy(end, src, (unsigned)((char*)o->end - (char*)src));
            end = begin + n;
            return this;
        }
        memcpy(begin, o->begin, (unsigned)n * 4);
        end = begin + n;
    }
    return this;
}

// @ 0x00758b60
Elem50* Elem50::Ctor(int* src)
{
    a.Init((src[1] - src[0]) >> 2, src + 3);
    a.end = (int*)memcpy(a.begin, (void*)src[0], src[1] - src[0]) + ((src[1] - src[0]) >> 2);
    b.Init((src[6] - src[5]) >> 2, src + 8);
    b.end = (int*)memcpy(b.begin, (void*)src[5], src[6] - src[5]) + ((src[6] - src[5]) >> 2);
    c.Init((src[0xb] - src[10]) >> 2, src + 0xd);
    c.end = (int*)memcpy(c.begin, (void*)src[10], src[0xb] - src[10]) + ((src[0xb] - src[10]) >> 2);
    d.Init((src[0x10] - src[0xf]) >> 2, src + 0x12);
    d.mEnd = (int*)memcpy(d.mBegin, (void*)src[0xf], src[0x10] - src[0xf]) + ((src[0x10] - src[0xf]) >> 2);
    return this;
}

// @ 0x00758e20
Elem50* __cdecl FUN_00758e20(Elem50* first, Elem50* last, Elem50* out)
{
    for (; first != last; first = (Elem50*)((char*)first + 0x50),
                       out = (Elem50*)((char*)out + 0x50)) {
        out->a.OpAssign(&first->a);
        out->b.OpAssign(&first->b);
        out->c.OpAssign(&first->c);
        out->d = first->d;
    }
    return out;
}

// @ 0x00758e80
Elem50* __cdecl FUN_00758e80(Elem50* first, Elem50* last, Elem50* out)
{
    while (last != first) {
        last = (Elem50*)((char*)last - 0x50);
        out = (Elem50*)((char*)out - 0x50);
        out->a.OpAssign(&last->a);
        out->b.OpAssign(&last->b);
        out->c.OpAssign(&last->c);
        out->d = last->d;
    }
    return out;
}

// @ 0x00758f70
void __cdecl FUN_00758f70(Elem50* first, Elem50* last, Elem50* out)
{
    for (; first != last; first = (Elem50*)((char*)first + 0x50)) {
        out->a.OpAssign(&first->a);
        out->b.OpAssign(&first->b);
        out->c.OpAssign(&first->c);
        out->d = first->d;
    }
}

// @ 0x00758fc0
bool __cdecl FUN_00758fc0(unsigned* src, IntVec* dst, int a, int b)
{
    int n = src ? (int)src[0] : 0;
    int* p = src ? (int*)src[1] : 0;
    int have = (int)(dst->mEnd - dst->mBegin);
    char flag = 0;
    if (n > have) {
        dst->resize(n);
        flag = 1;
    } else {
        for (int i = 0; i < n; ++i) {
            float d = ((float*)dst->mBegin)[i] - ((float*)p)[i];
            if (d < 0.0f)
                d = -d;
            if (d > g_f162f0e8) {
                flag = 1;
                break;
            }
        }
        if (n < have) {
            int j = n;
            float* q = (float*)dst->mBegin + n;
            for (; j < have; ++j, ++q) {
                if (*q != 0.0f) {
                    flag = 1;
                    break;
                }
            }
            volatile unsigned zero = 0;
            memcpy(dst->mBegin + n, dst->mEnd, zero);
            int bytes = (int)((char*)dst->mEnd - (char*)(dst->mBegin + n));
            dst->mEnd = (int*)((char*)dst->mEnd - ((bytes >> 2) << 2));
        }
        if (!flag)
            return 0;
    }
    FUN_00738e90(n, p, a, b);
    memcpy(dst->mBegin, p, n * 4);
    return flag;
}

// @ 0x007591f0
bool C591f0::Get(At6* out)
{
    mp0c->f();
    *out = m10;
    return true;
}

// @ 0x00759210
bool C59210::CopyTo(RCArray_s0075_8240* out)
{
    int n = (int)(mEnd - mBegin);
    for (int i = 0; i < n; ++i) {
        RCObj_s0075_8240** src = &mBegin[i];
        if (out->mEnd < out->mCap) {
            RCObj_s0075_8240** slot = out->mEnd;
            out->mEnd = slot + 1;
            if (slot) {
                RCObj_s0075_8240* v = *src;
                *slot = v;
                if (v) RCAddRef_s0075_8240(v);
            }
        } else {
            out->DoInsertValue(out->mEnd, src);
        }
    }
    return true;
}

// @ 0x00759280
Big140* __cdecl FUN_00759280(void* param)
{
    RefVec5 rv;
    rv.mb = 0; rv.me = 0; rv.mc = 0;
    FUN_0072fff0(param, &rv);
    int* obj = (int*)EAAlloc(0x140, "Graphics", 0, 0, 0, 0);
    if (obj)
        obj = ((Obj140b*)obj)->Ctor();
    void* holder = FUN_007585c0((int*)&rv);
    void* old = *(void**)((char*)obj + 0x138);
    if (holder != old) {
        if (holder) {
            void** vt = *(void***)holder;
            ((void (__thiscall*)(void*))vt[0])(holder);
        }
        *(void**)((char*)obj + 0x138) = holder;
        if (old) {
            void** vt = *(void***)old;
            ((void (__thiscall*)(void*))vt[1])(old);
        }
    }
    void* h = *(void**)((char*)obj + 0x138);
    ((void (__thiscall*)(void*, void*, void*))(*(void***)h)[5])
        (h, (char*)obj + 0x11c, (char*)obj + 0x134);
    Val38 src;
    src.w00 = 0;
    src.w02 = 0;
    src.f04 = g_f162f028;
    src.f08 = g_f162f02c;
    src.f0c = g_f162f030;
    src.f10 = g_f1485720;
    src.m14.Assign(&g_m3_162f16c_s0075_8240);
    Val7e20_s0075_8240 tmp;
    Val7e20_s0075_8240* vt = tmp.Ctor(&src, param, (void*)0);
    ((Elem7cVec*)((char*)obj + 0x108))->push_back(vt);
    tmp.Dtor();
    rv.Destroy();
    return (Big140*)obj;
}

// @ 0x00759420
void __fastcall FUN_00759420(C59420* self)
{
    if (self->a.begin != self->a.end) {
        FUN_00762d70((int)((char*)self->a.end - (char*)self->a.begin) >> 2, self->a.begin);
        self->a.Clear(0);
        self->c.Clear(0);
        self->b.Clear(0);
        self->d.clear(0);
    }
    if (self->d.mBegin && ((int*)self->d.mBegin)[-1] != 0)
        operator_delete_arr(self->d.mBegin);
    if (self->c.begin && ((int*)self->c.begin)[-1] != 0)
        operator_delete_arr(self->c.begin);
    if (self->b.begin && ((int*)self->b.begin)[-1] != 0)
        operator_delete_arr(self->b.begin);
    if (self->a.begin && ((int*)self->a.begin)[-1] != 0)
        operator_delete_arr(self->a.begin);
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
