// Slice s00758240 (batch w2g3, slice 16).
// Graphics / EASTL-heavy region.  Many functions are eastl::vector<int> and
// eastl::vector<0x50-byte element> template instantiations; the rest are small
// intrusive-pointer helpers.  Built /O2 /arch:SSE with /EHsc.
#include "../../include/types.h"
#include <intrin.h>

struct RCObj { void* vptr; long refcount; };
static inline void RCAddRef(RCObj* p) {
    if (p) _InterlockedIncrement(&p->refcount);
}
static inline void RCRelease(RCObj* p) {
    if (p && _InterlockedExchangeAdd(&p->refcount, -1) == 1) {
        *((long*)&p->refcount) = 1;
        ((void (__thiscall*)(RCObj*, int))p->vptr)(p, 1);
    }
}
struct RCArray { RCObj** mBegin; RCObj** mEnd; RCObj** mCap; void Init(int n, void* src); void DoInsertValue(RCObj** end, RCObj** src); };

template<class T> T* xcopy(const T* f, const T* l, T* o) { while (f != l) *o++ = *f++; return o; }
template<class T> T* xmove(T* f, T* l, T* o) { while (f != l) *o++ = *f++; return o; }

// ---- allocator / container primitives (original callees, relocations masked) --------------
void* __cdecl EAAlloc(unsigned size, const char* name, int, int, const char* file, int line); // 0xf473a0
void  __cdecl operator_delete_arr(void* p);                                 // 0xf47380 operator delete[]
__declspec(dllimport) void __cdecl memmove(void*, const void*, unsigned);   // msvcr90!memmove
extern const char g_EASTLAllocFile[];                                       // 0x013ebb38 (EASTL/allocator.h)
struct M3 {
    float m[9];
    void Assign(const M3* src);                      // 0x0041cb40
};
extern M3    g_m3_162f16c;                                                  // 0x0162f16c
extern float g_f140da1c;                                                    // 0x0140da1c (FLT_MAX)
extern float g_f13f51ac;                                                    // 0x013f51ac (-FLT_MAX)
extern float g_f162f028;                                                    // 0x0162f028
extern float g_f162f02c;                                                    // 0x0162f02c
extern float g_f162f030;                                                    // 0x0162f030
extern float g_f1485720;                                                    // 0x01485720

extern "C" void __cdecl FUN_00424430(void* end, void* src);
extern "C" char __cdecl FUN_00732220(void* a, void* b, void* c);
extern "C" void* __cdecl operator_new_graph(unsigned size);
extern "C" void* __cdecl operator_new_graph6(unsigned size, const char* name, int, int, int, int); // 0x00f473a0
extern const char g_GraphicsTag[];                                                          // 0x013EB8A4
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned n);
extern "C" void  __cdecl eastl_dealloc(void* p);
extern "C" void  __cdecl FUN_0047c800(void** out, void* first, void* last, void* dest, void* tag);
extern "C" void  __cdecl FUN_00729c60(void* self, void* out, void* flag);
extern "C" void  __cdecl FUN_00762d70(int n, void* p);
extern "C" void  __cdecl FUN_00738e90(int n, void* p, int a, int b);
extern "C" void  __cdecl FUN_004afc80(unsigned n);
extern "C" void  __cdecl FUN_004b0a10(void* p, int n, void* v);
extern "C" void  __cdecl FUN_0072fff0(void* in, void* out);
extern "C" void  __cdecl FUN_00757ff0_stub(void* self, void* a, void* b);

// ---------------------------------------------------------------------------
// @ 0x00758240   intrusive 6-dword assignment
// ---------------------------------------------------------------------------
struct At6 {
    RCObj* p;
    int a, b, c, d, e;
    __declspec(noinline) At6& operator=(const At6& o);
};
At6& At6::operator=(const At6& o) {
    RCObj* op = o.p;
    RCObj* old = p;
    if (op != old) {
        RCAddRef(op);
        p = op;
        RCRelease(old);
    }
    a = o.a; b = o.b; c = o.c; d = o.d; e = o.e;
    return *this;
}

// ---------------------------------------------------------------------------
// @ 0x007582b0
// ---------------------------------------------------------------------------
struct C582b0 {
    char pad[0x20];
    bool Build(void* arg, void** out);
};
struct Ctor7ff0 { void* Ctor(void* a2, At6* a3); };
struct At6Guard { At6 v; ~At6Guard() { RCRelease(v.p); } };

// ---------------------------------------------------------------------------
// @ 0x007582b0   build a 0x28 holder from a property lookup
// ---------------------------------------------------------------------------
bool C582b0::Build(void* arg, void** out) {
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

// ---------------------------------------------------------------------------
// 0x28 holder with RefVector at +0xc
// ---------------------------------------------------------------------------
struct RefVectorDtor { void Destroy(); };   // 0x0041eb80 (thiscall dtor)
struct Holder841 {
    void* vt0;
    void* vt1;
    void* p08;
    RCArray vec;
    void* p18;
    Holder841* Ctor(int* src);   // 0x007583e0
    void Dtor();                 // 0x00758540
};
__declspec(noinline) Holder841* __cdecl FUN_007585c0(int* src);
extern char g_0140da88[];   // 0x0140da88
extern char g_0140da84[];   // 0x0140da84
extern char g_013ef094[];   // 0x013ef094
// @ 0x007583e0
Holder841* Holder841::Ctor(int* src) {
    vt1 = &g_013ef094;
    p08 = 0;
    vt0 = &g_0140da88;
    vt1 = &g_0140da84;
    vec.Init((src[1] - src[0]) >> 2, src + 3);
    FUN_0047c800((void**)&src, (void*)src[0], (void*)src[1], vec.mBegin, src);
    vec.mEnd = (RCObj**)src;
    return this;
}
// @ 0x00758540
void Holder841::Dtor() {
    vt0 = &g_0140da88;
    vt1 = &g_0140da84;
    ((RefVectorDtor*)((char*)this + 0xc))->Destroy();
    vt1 = &g_013ef094;
}

// ---------------------------------------------------------------------------
// @ 0x00758480
// ---------------------------------------------------------------------------
struct C58480 { char pad[0xc]; int* mBegin; int* mEnd; bool Update(float* bounds, float* w); };

// ---------------------------------------------------------------------------
// @ 0x00758480   reset bounds / weight accumulator, then let each entry expand them
// ---------------------------------------------------------------------------
bool C58480::Update(float* bounds, float* w) {
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

// ---------------------------------------------------------------------------
// @ 0x007585c0
// ---------------------------------------------------------------------------
Holder841* __cdecl FUN_007585c0(int* src) {
    Holder841* p = (Holder841*)operator_new_graph6(0x20, g_GraphicsTag, 0, 0, 0, 0);
    if (p) return p->Ctor(src);
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00758680   eastl::vector<int>::insert(pos, n, value)
// ---------------------------------------------------------------------------
struct IntVec {
    int* mBegin; int* mEnd; int* mCap;
    void resize(int n);                          // 0x004afc80 (SpVector<float>::resize)
    void clear(int n);                           // 0x004cd3c0 (vector<int>::clear)
    void Init(int n, void* alloc);               // 0x004aa350
    int* DoInit(unsigned n, int* first, int* last);  // 0x00758630
    void Insert(int* pos, unsigned n, int* val);
};
void IntVec::Insert(int* pos, unsigned n, int* val) {
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

// ---------------------------------------------------------------------------
// @ 0x00758860   eastl::vector<Elem14> construct range
// ---------------------------------------------------------------------------
struct Elem14 {
                int* begin; int* end; int* cap; int a, b;
                void Init(int n, void* src);             // 0x00733070
                void Clear(int);                         // 0x00758ee0
                int* DoInit(unsigned n, int* first, int* last);  // 0x00758630
                Elem14* OpAssign(Elem14* o); };
int* __cdecl FUN_00758860(int* out, int* first, int* last) {
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

// ---------------------------------------------------------------------------
// @ 0x00758950
// ---------------------------------------------------------------------------
void __cdecl FUN_00758950(Elem14* out, unsigned n, int* src) {
    for (; n != 0; --n, out = (Elem14*)((char*)out + 0x14)) {
        if (out) {
            int c = (int)((char*)src[1] - (char*)*src) >> 2;
            int* nb = c ? (int*)operator_new_graph(c * 4) : 0;
            out->begin = nb; out->end = nb; out->cap = nb + c;
            out->end = xcopy((int*)*src, (int*)src[1], nb);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00758a10
// ---------------------------------------------------------------------------
Elem14* Elem14::OpAssign(Elem14* o) {
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

// ---------------------------------------------------------------------------
// @ 0x00758b60
// ---------------------------------------------------------------------------
struct Elem50 { Elem14 a; Elem14 b; Elem14 c; IntVec d; Elem50* Ctor(int* src); };
Elem50* Elem50::Ctor(int* src) {
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

// ---------------------------------------------------------------------------
// @ 0x00758e20 / 0x00758e80 / 0x00758f70
// ---------------------------------------------------------------------------
Elem50* __cdecl FUN_00758e20(Elem50* first, Elem50* last, Elem50* out) {
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
Elem50* __cdecl FUN_00758e80(Elem50* first, Elem50* last, Elem50* out) {
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
void __cdecl FUN_00758f70(Elem50* first, Elem50* last, Elem50* out) {
    for (; first != last; first = (Elem50*)((char*)first + 0x50)) {
        out->a.OpAssign(&first->a);
        out->b.OpAssign(&first->b);
        out->c.OpAssign(&first->c);
        out->d = first->d;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00758fc0
// ---------------------------------------------------------------------------
extern float g_f162f0e8;   // 0x0162f0e8
bool __cdecl FUN_00758fc0(unsigned* src, IntVec* dst, int a, int b) {
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

// ---------------------------------------------------------------------------
// @ 0x00759100
// ---------------------------------------------------------------------------
struct EmbeddedState { char pad[8]; int mFlags; int D3D9GetShaderData(int); };  // flags at +8
extern "C" EmbeddedState* __cdecl FUN_007580a0(void* self);                   // 0x007580a0
struct C59100 {
    int    m00;       // +0x00
    int    m04;
    int    m08;
    void** mv0c;      // +0x0c
    int    m10;
    int    m14;
    int    m18;
    int    m1c;
    void** mv20;      // +0x20
    int    m24;       // +0x24
    int    m28;
    int    m2c;
    int    m30;
    int*   mBase34;   // +0x34
    int    m38;
    int    m3c;
    int    m40;
    int    m44;
    int*   mArr48;    // +0x48
    int    m4c;
    int    m50;
    int    m54;
    int    m58;
    int*   mArr5c;    // +0x5c
    void Iterate();
};
void C59100::Iterate() {
    int n = (m24 - (int)mv20) >> 2;
    int off50 = 0;
    int dead14 = 0;
    for (int i = 0; i < n; ++i) {
        void* a = mv0c[i];
        void* b = mv20[i];
        EmbeddedState* st = (EmbeddedState*)FUN_007580a0(a);
        int sd = 0;
        if (st->mFlags & 8)
            sd = st->D3D9GetShaderData(0x200);
        if (FUN_00758fc0((unsigned*)sd, (IntVec*)(mBase34 + off50), (int)a, (int)b)) {
            Elem50* q = (Elem50*)(mArr48 + off50);
            if (q->a.begin != q->a.end) {
                FUN_00762d70((int)((char*)q->a.end - (char*)q->a.begin) >> 2, q->a.begin);
                q->a.Clear(0);
                q->c.Clear(0);
                q->b.Clear(0);
                q->d.clear(0);
            }
            mArr5c[i] = 0;
        }
        off50 += 0x50;
        dead14 += 0x14;
    }
}

// ---------------------------------------------------------------------------
// @ 0x007591f0
// ---------------------------------------------------------------------------
struct Sub9100 { void f(); };
struct C591f0 {
    char pad[0xc];
    Sub9100* mp0c;
    At6 m10;
    bool Get(At6* out);
};
bool C591f0::Get(At6* out) {
    mp0c->f();
    *out = m10;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00759210
// ---------------------------------------------------------------------------
struct C59210 { char pad[0xc]; RCObj** mBegin; RCObj** mEnd; bool CopyTo(RCArray* out); };
bool C59210::CopyTo(RCArray* out) {
    int n = (int)(mEnd - mBegin);
    for (int i = 0; i < n; ++i) {
        RCObj** src = &mBegin[i];
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
// @ 0x00759280
// ---------------------------------------------------------------------------
struct Big140 { char pad[0x140]; };
struct Val38 {                     // 0x38-byte prefix copied into the value ctor
    unsigned short w00, w02;
    float f04, f08, f0c, f10;
    M3 m14;
};
struct Val7e20 {
    unsigned short w00, w02;
    float f04, f08, f0c, f10;
    M3 m14;
    unsigned short w38, w3a;
    float f3c, f40, f44, f48;
    M3 m4c;
    int i70;
    void* p74;
    void* p78;
    Val7e20* Ctor(Val38* src, void* a2, void* a3);   // 0x00757e20
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

Big140* __cdecl FUN_00759280(void* param) {
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
    src.m14.Assign(&g_m3_162f16c);
    Val7e20 tmp;
    Val7e20* vt = tmp.Ctor(&src, param, (void*)0);
    ((Elem7cVec*)((char*)obj + 0x108))->push_back(vt);
    tmp.Dtor();
    rv.Destroy();
    return (Big140*)obj;
}

// ---------------------------------------------------------------------------
// @ 0x00759420   dtor freeing four vectors
// ---------------------------------------------------------------------------
struct C59420 { Elem14 a; Elem14 b; Elem14 c; IntVec d; };
void __fastcall FUN_00759420(C59420* self) {
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
