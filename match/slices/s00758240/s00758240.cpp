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
struct RCArray { RCObj** mBegin; RCObj** mEnd; RCObj** mCap; void DoInsertValue(RCObj** end, RCObj** src); };

template<class T> T* xcopy(const T* f, const T* l, T* o) { while (f != l) *o++ = *f++; return o; }
template<class T> T* xmove(T* f, T* l, T* o) { while (f != l) *o++ = *f++; return o; }

extern "C" void __cdecl FUN_00424430(void* end, void* src);
extern "C" int  __cdecl FUN_00732220(void* a, void* b, void* c);
extern "C" void* __cdecl operator_new_graph(unsigned size);
extern "C" void  __cdecl eastl_dealloc(void* p);
extern "C" void  __cdecl FUN_00733070(int n, void* src);
extern "C" void  __cdecl FUN_0047c800(int* a, int b, int c, int d, int* e);
extern "C" void  __cdecl FUN_004aa350(int n, void* src);
extern "C" void  __cdecl FUN_00729c60(void* self, void* out, void* flag);
extern "C" void  __cdecl FUN_00762d70(int n, void* p);
extern "C" void  __cdecl FUN_00758ee0(int);
extern "C" void  __cdecl FUN_004cd3c0(int);
extern "C" void  __cdecl FUN_00738e90(int n, void* p, int a, int b);
extern "C" void  __cdecl FUN_004afc80(unsigned n);
extern "C" void  __cdecl FUN_004b0a10(void* p, int n, void* v);
extern "C" void  __cdecl FUN_0072fff0(void* in, void* out);
extern "C" void* __cdecl FUN_007004d0(void);
extern "C" void  __cdecl FUN_0041f2d0(void* p);
extern "C" void  __cdecl FUN_0041eb80(void* p);
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
    bool Build(void* arg, At6* tmp, void** out);
};
bool C582b0::Build(void* arg, At6* tmp, void** out) {
    if (!FUN_00732220(tmp, (char*)this + 0x20, arg)) return false;
    void* p = operator_new_graph(0x28);
    if (p) { FUN_00757ff0_stub(p, this, tmp); }
    *out = p;
    (*(void (__thiscall**)(void*))*(void**)p)(p);
    RCRelease(tmp->p);
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x007583e0 / 0x00758540   0x28 holder with RefVector at +0xc
// ---------------------------------------------------------------------------
struct Holder841 {
    void* vt0;
    void* vt1;
    RCArray vec;
    void* p18;
    Holder841* Ctor(int* src);
    void Dtor();
};
Holder841* Holder841::Ctor(int* src) {
    vt0 = 0; vt1 = 0;
    FUN_00733070(src[1] - *src >> 2, src + 3);
    FUN_0047c800(src, *src, src[1], (int)vec.mBegin, src);
    p18 = src;
    return this;
}
void Holder841::Dtor() {
    FUN_0041eb80(&vec);
    vt1 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00758480
// ---------------------------------------------------------------------------
struct C58480 { char pad[0xc]; int* mBegin; int* mEnd; char pad2[0x10]; bool Update(void* a, void* b, void* c); };
bool C58480::Update(void* a, void* b, void* c) { (void)a; (void)b; (void)c; return true; }

// ---------------------------------------------------------------------------
// @ 0x007585c0
// ---------------------------------------------------------------------------
Holder841* __cdecl FUN_007585c0(int* src) {
    Holder841* p = (Holder841*)operator_new_graph(0x28);
    if (p) return p->Ctor(src);
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00758680   eastl::vector<int>::insert(pos, n, value)
// ---------------------------------------------------------------------------
struct IntVec {
    int* mBegin; int* mEnd; int* mCap;
    void Insert(int* pos, unsigned n, int* val);
};
void IntVec::Insert(int* pos, unsigned n, int* val) {
    unsigned mcap = (unsigned)(mCap - mBegin);
    if (n > mcap) {
        unsigned old = (unsigned)(mEnd - mBegin);
        unsigned newcap = old * 2;
        if (old == 0) newcap = 1;
        unsigned want = old + n;
        if (want >= newcap) newcap = want;
        int* nb = newcap ? (int*)operator_new_graph(newcap * 4) : 0;
        int* pe = xcopy(mBegin, pos, nb);
        for (unsigned i = 0; i < n; ++i) *pe++ = *val;
        pe = xcopy(pos, mEnd, pe);
        if (mBegin) eastl_dealloc(mBegin);
        mBegin = nb; mEnd = pe; mCap = nb + newcap;
    } else if (n) {
        if (n < (unsigned)(mEnd - pos)) {
            xcopy(mEnd - n, mEnd, mEnd);
            mEnd += n;
        } else {
            int* pe = mEnd;
            for (unsigned i = 0; i < n - (unsigned)(mEnd - pos); ++i) *pe++ = *val;
            mEnd = pe;
            xcopy(pos, mEnd - n, mEnd);
            mEnd += n;
        }
        for (int* q = pos; q != pos + n; ++q) *q = *val;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00758860   eastl::vector<Elem14> construct range
// ---------------------------------------------------------------------------
struct Elem14 { int* begin; int* end; int* cap; int a, b; Elem14* OpAssign(Elem14* o); };
int* __cdecl FUN_00758860(int* out, int* first, int* last) {
    *out = (int)first;
    for (; first != last; first += 5) {
        int* b = (int*)*out;
        if (b) {
            int n = (first[1] - *first) >> 2;
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
            int c = (src[1] - *src) >> 2;
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
        int have = (int)(end - begin);
        if (have < n) {
            Elem14 tmp;
            tmp.begin = (int*)operator_new_graph(n * 4);
            tmp.end = tmp.begin + n; tmp.cap = tmp.end;
            xcopy(o->begin, o->end, tmp.begin);
            if (begin) eastl_dealloc(begin);
            *this = tmp;
            return this;
        }
        if ((int)(end - begin) < n) {
            xcopy(o->begin, o->begin + have, begin);
            xcopy(o->begin + have, o->end, end);
            end = begin + n;
            return this;
        }
        xcopy(o->begin, o->end, begin);
        end = begin + n;
    }
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00758b60
// ---------------------------------------------------------------------------
struct Elem50 { Elem14 a; Elem14 b; Elem14 c; IntVec d; Elem50* Ctor(int* src); };
Elem50* Elem50::Ctor(int* src) {
    FUN_00733070(src[1] - *src >> 2, src + 3);
    a.end = xcopy((int*)*src, (int*)src[1], a.begin);
    FUN_00733070(src[6] - src[5] >> 2, src + 8);
    b.end = xcopy((int*)src[5], (int*)src[6], b.begin);
    FUN_00733070(src[0xb] - src[10] >> 2, src + 0xd);
    c.end = xcopy((int*)src[10], (int*)src[0xb], c.begin);
    FUN_004aa350(src[0x10] - src[0xf] >> 2, src + 0x12);
    d.mEnd = xcopy((int*)src[0xf], (int*)src[0x10], d.mBegin);
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
float g_f162f0e8;
char __cdecl FUN_00758fc0(unsigned* src, IntVec* dst, int a, int b) {
    int n = src ? (int)src[0] : 0;
    int* p = src ? (int*)src[1] : 0;
    int have = (int)(dst->mEnd - dst->mBegin);
    if (have < n) {
        FUN_004afc80(n);
        FUN_00738e90(n, p, a, b);
        dst->mEnd = xcopy((int*)dst->mBegin, (int*)dst->mEnd, (int*)dst->mBegin);
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00759100
// ---------------------------------------------------------------------------
struct C59100 {
    void* vt;
    char pad[0x8];
    char** mv0c;
    char pad2[0x20 - 0x10];
    char** mv20;
    char pad3[0x34 - 0x24];
    int     mBase34;
    char pad4[0x48 - 0x38];
    int*    mArr48;
    char pad5[0x5c - 0x4c];
    int*    mArr5c;
    void Iterate();
};
void C59100::Iterate() {
    int n = (int)(*(int*)((char*)this + 0x24) - *(int*)((char*)this + 0x20)) >> 2;
    for (int i = 0; i < n; ++i) {
        char* a = mv0c[i];
        char* b = mv20[i];
        (void)a; (void)b;
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
Big140* __cdecl FUN_00759280(void* param) {
    char tmp[0x50];
    *(int*)(tmp + 0) = 0; *(int*)(tmp + 4) = 0; *(int*)(tmp + 8) = 0;
    FUN_0072fff0(param, tmp);
    Big140* b = (Big140*)operator_new_graph(0x140);
    if (b) FUN_007004d0();
    FUN_007585c0((int*)tmp);
    FUN_0041f2d0(tmp);
    return b;
}

// ---------------------------------------------------------------------------
// @ 0x00759420   dtor freeing four vectors
// ---------------------------------------------------------------------------
struct C59420 { int* a; int* aend; Elem14 b; Elem14 c; IntVec d; };
void __fastcall FUN_00759420(C59420* self) {
    if (self->a != self->aend) {
        FUN_00762d70((int)(self->aend - self->a) >> 2, self->a);
        FUN_00758ee0(0); FUN_00758ee0(0); FUN_00758ee0(0); FUN_004cd3c0(0);
    }
    if (self->d.mBegin) eastl_dealloc(self->d.mBegin);
    if (self->c.begin) eastl_dealloc(self->c.begin);
    if (self->b.begin) eastl_dealloc(self->b.begin);
    if (self->a) eastl_dealloc(self->a);
}
