// s00d9fb20 -- a mixed text-layout / ambience block of the retail image.
//
//   * three EASTL instantiations over EA::Text::GlyphLayoutInfo (0x20-byte element):
//       00d9fb20  eastl::vector<GlyphLayoutInfo, "Simulator" allocator>::insert(pos, n, value)
//       00d9fd00  introsort_loop over a 1-dword element with a 12-byte (3 float) predicate
//       00d9fe20  unguarded_partition over GlyphLayoutInfo with a function-pointer predicate
//   * six SP gameplay / ambience methods whose primary types are not in the dev PDB.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-   (VC9 / VS2008 SP1, the game's main toolset)
//
// Everything outside this slice is a relocation (referenced by address only), so a helper's exact
// name does not matter; the by-value GlyphLayoutInfo (8 dwords: int + 7 floats) and the by-value
// 12-byte predicate are what fix the argument marshalling.

typedef unsigned int u32;

void* EAAllocate(unsigned int size, const char* name, int flags, int debugFlags, const char* file,
                 int line);                                        // 0x00f473a0
void __cdecl EastlFree(void* p);                                   // 0x00f47380

#define EASTL_FILE                                                            \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ------------------------------------------------------------------ EASTL element + helpers
struct GlyphLayoutInfo {
    int   i0;                        // +0x00
    float f1, f2, f3, f4, f5, f6, f7; // +0x04 .. +0x1c
};

struct Cmp3 { float a, b, c; };      // 12-byte by-value sort predicate

// 0x00d9d8d0 uninitialized_copy_n-style copy that writes the advanced destination back through an
// out parameter (retail call sites push five dwords).
extern "C" void  FUN_00d9d8d0(void** out, GlyphLayoutInfo* a, GlyphLayoutInfo* b, GlyphLayoutInfo* c,
                              GlyphLayoutInfo* d);
// 0x00d9d940 uninitialized_fill_n of n 0x20-byte elements from one source (four dwords).
extern "C" void  FUN_00d9d940(GlyphLayoutInfo* dst, unsigned n, const GlyphLayoutInfo* src,
                              GlyphLayoutInfo* pos);
// 0x00d9db30 uninitialized_copy of [first,last) to dst, returning the advanced destination.
extern "C" GlyphLayoutInfo* FUN_00d9db30(GlyphLayoutInfo* first, GlyphLayoutInfo* last,
                                         GlyphLayoutInfo* dst);
// lib_eatext eastl::copy_backward_impl / fill_imp instantiations for GlyphLayoutInfo.
extern "C" GlyphLayoutInfo* FUN_00898f90(GlyphLayoutInfo* first, GlyphLayoutInfo* last,
                                         GlyphLayoutInfo* dst);
extern "C" void  FUN_00898520(GlyphLayoutInfo* first, GlyphLayoutInfo* last,
                             const GlyphLayoutInfo* value);
// 0x00d9b840 median-of-three selector; returns a pointer to the median element. The 12-byte predicate
// is passed twice by value.
extern "C" void** FUN_00d9b840(void** first, void** mid, void** last, Cmp3 c1, Cmp3 c2);
// 0x00d9f660 unguarded partition about *pivot, returning the cut.
extern "C" void** FUN_00d9f660(void** first, void** last, void* pivot);
// 0x00d9f6f0 final insertion sort / partial_sort over [first,last) with the 12-byte predicate.
extern "C" void  FUN_00d9f6f0(void** first, void** last, void** last2, Cmp3 cmp);

// ------------------------------------------------------------------ 0x00d9fb20
struct GlyphVec {
    GlyphLayoutInfo* mpBegin;    // +0x00
    GlyphLayoutInfo* mpEnd;      // +0x04
    GlyphLayoutInfo* mpCap;      // +0x08
    GlyphLayoutInfo* mpInline;   // +0x10
    void insert(GlyphLayoutInfo* position, unsigned n, const GlyphLayoutInfo* value);
};

// @ 0x00d9fb20
void GlyphVec::insert(GlyphLayoutInfo* position, unsigned n, const GlyphLayoutInfo* value)
{
    if (n > (u32)(mpCap - mpEnd)) {
        u32 count = (u32)(mpEnd - mpBegin);
        u32 newCap = count * 2;
        if (count == 0)
            newCap = 1;
        u32 want = count + n;
        if (newCap <= want)
            newCap = want;
        GlyphLayoutInfo* buf;
        if (newCap == 0)
            buf = 0;
        else
            buf = (GlyphLayoutInfo*)EAAllocate(newCap << 5, "Simulator", 0, 0, EASTL_FILE, 0xd1);
        GlyphLayoutInfo* p = FUN_00d9db30(mpBegin, position, buf);
        FUN_00d9d940(p, n, value, position);
        GlyphLayoutInfo* newEnd = FUN_00d9db30(position, mpEnd, (GlyphLayoutInfo*)((char*)buf + (n << 5)));
        GlyphLayoutInfo* old = mpBegin;
        if (old != 0 && old != mpInline)
            EastlFree(old);
        mpBegin = buf;
        mpEnd = newEnd;
        mpCap = (GlyphLayoutInfo*)((char*)buf + (newCap << 5));
        return;
    }
    if (n == 0)
        return;
    GlyphLayoutInfo temp = *value;
    GlyphLayoutInfo* oldEnd = mpEnd;
    unsigned nExtra = (unsigned)(mpEnd - position);
    if (n < nExtra) {
        unsigned nb = n << 5;
        FUN_00d9d8d0((void**)&value, (GlyphLayoutInfo*)((char*)mpEnd - nb), mpEnd, mpEnd, position);
        mpEnd = (GlyphLayoutInfo*)((char*)mpEnd + nb);
        FUN_00898f90(position, (GlyphLayoutInfo*)((char*)oldEnd - nb), oldEnd);
        FUN_00898520(position, (GlyphLayoutInfo*)((char*)position + nb), &temp);
        return;
    }
    unsigned diff = n - nExtra;
    FUN_00d9d940(mpEnd, diff, &temp, position);
    mpEnd = (GlyphLayoutInfo*)((char*)mpEnd + (diff << 5));
    FUN_00d9d8d0((void**)&position, position, oldEnd, mpEnd, position);
    mpEnd = (GlyphLayoutInfo*)((char*)mpEnd + (nExtra << 5));
    FUN_00898520(position, oldEnd, &temp);
}

// ------------------------------------------------------------------ 0x00d9fd00
// @ 0x00d9fd00
void __cdecl FUN_00d9fd00(void** first, void** last, int depth, Cmp3 cmp)
{
    while (((int)((char*)last - (char*)first) & ~3) > 0x70 && depth > 0) {
        void* pivot = *FUN_00d9b840(
            first, first + ((((char*)last - (char*)first) >> 2) / 2), last - 1, cmp, cmp);
        void** cut = (void**)FUN_00d9f660(first, last, pivot);
        --depth;
        FUN_00d9fd00(cut, last, depth, cmp);
        last = cut;
    }
    if (depth == 0)
        FUN_00d9f6f0(first, last, last, cmp);
}

// ------------------------------------------------------------------ 0x00d9fe20
typedef bool (__cdecl* GlyphPred)(const GlyphLayoutInfo&, const GlyphLayoutInfo&);

// @ 0x00d9fe20
GlyphLayoutInfo* __cdecl FUN_00d9fe20(GlyphLayoutInfo* first, GlyphLayoutInfo* last,
                                      GlyphLayoutInfo pivot, GlyphPred pred)
{
    while (pred(*first, pivot))
        ++first;
    for (;;) {
        --last;
        while (pred(pivot, *last))
            --last;
        if (first >= last)
            return first;
        GlyphLayoutInfo tmp = *first;
        *first = *last;
        *last = tmp;
        ++first;
    }
}

// ------------------------------------------------------------------ external game code
extern "C" int*  EA_Audio_GetSystemAT();          // 0x00a206f0
extern "C" int*  SP_MessageServer();              // 0x0067dcc0
extern "C" void  FUN_00e31160(int);               // 0x00e31160
extern "C" void* FUN_0067cac0(u32, int);          // 0x0067cac0
extern "C" int*  FUN_00b3d310(void*);             // 0x00b3d310
extern "C" void  FUN_00d9cf70(int);               // 0x00d9cf70
extern "C" void  FUN_00db4a20(int*);              // 0x00db4a20
extern "C" void* FUN_00b6f4f0(void*, void*, void*, void*);  // 0x00b6f4f0

// 0x15935a8 holds a pointer (pool begin) and 0x15935ac the pool end; the object 0x15935a8 also
// carries the pool manager vtable exercised by the calls below.
extern "C" char* gPoolBase;                       // [0x15935a8]
extern "C" char* gPoolEnd;                        // [0x15935ac]
extern "C" float gDAT_1485378;                    // 0.0f
extern "C" float gDAT_158137c;                    // clamp upper bound

struct X;                                          // opaque gameplay object
struct Poly {                                      // object with a virtual at vtable +0x84
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
    virtual void a20(); virtual void a24(); virtual void a28(); virtual void a2c();
    virtual void a30(); virtual void a34(); virtual void a38(); virtual void a3c();
    virtual void a40(); virtual void a44(); virtual void a48(); virtual void a4c();
    virtual void a50(); virtual void a54(); virtual void a58(); virtual void a5c();
    virtual void a60(); virtual void a64(); virtual void a68(); virtual void a6c();
    virtual void a70(); virtual void a74(); virtual void a78(); virtual void a7c();
    virtual void a80(); virtual void a84(int, int, int);
};
struct Rel {                                       // object with a virtual release at vtable +4
    virtual void v0();
    virtual void v4();
    virtual void v8();
};
struct VObj {                                      // object with a virtual query at vtable +0xc
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual void* p3(u32);
};
struct AT {                                        // EA::Audio::GetSystemAT object
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(int);
    virtual void v3c(int, float); virtual void v40(int, int);
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54(); virtual void v58();
};
struct MS {                                        // SP::MessageServer object
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1c();
    virtual void m20(); virtual void m24(); virtual void m28();
    virtual void m2c(void*, int, int);
};
struct VecErase { void erase(void*, void*); };

struct X {
    void  FUN_00bc9b60();
    void  FUN_00c0ba10();
    void  FUN_00bcb430();
    void  FUN_00c17350(int, int);
    void  FUN_00bcafe0(int);
    void  FUN_00bc98f0(int, int);
    void  FUN_00b453a0();
    void  FUN_0067c8c0();
    void  FUN_00d9ff00();
    void  FUN_00da0070(int*);
    void  FUN_00da0120(int*);
    bool  FUN_00c232d0();
    X*    FUN_00d9eb70(int);
    void  FUN_00d9ebc0(u32);
};

// ------------------------------------------------------------------ 0x00d9ff00
// @ 0x00d9ff00
void X::FUN_00d9ff00()
{
    char* self = (char*)this;
    if (*(int*)(self + 0xc) != 0 && *(float*)(self + 0x5c) > gDAT_1485378) {
        const float* p = (const float*)(self + 0x5c);
        if (*(float*)(self + 0x5c) < gDAT_158137c)
            p = &gDAT_158137c;
        *(float*)(*(int*)(self + 0xc) + 0x2cc) = *p;
    }
    ((VecErase*)(self + 0x8c))->erase(*(void**)(self + 0x8c), *(void**)(self + 0x90));
    Rel* r = *(Rel**)(self + 8);
    if (r != 0) {
        *(void**)(self + 8) = 0;
        r->v4();
    }
    r = *(Rel**)(self + 0xc);
    if (r != 0) {
        *(void**)(self + 0xc) = 0;
        r->v4();
    }
    r = *(Rel**)(self + 0xe4);
    if (r != 0) {
        *(void**)(self + 0xe4) = 0;
        r->v4();
    }
    AT* at = (AT*)EA_Audio_GetSystemAT();
    if (at != 0) {
        at->v38(0x3cdd1a9);
        at->v40(0x34753a7, 0x1c0ea007);
        at->v3c(0x34753aa, 1.0f);
        at->v58();
    }
    at = (AT*)EA_Audio_GetSystemAT();
    if (at != 0) {
        at->v38(0x3cdd1a9);
        at->v40(0x34753a7, 0x203e9874);
        at->v3c(0x34753aa, 0.0f);
        at->v58();
    }
    MS* ms = (MS*)SP_MessageServer();
    ms->m2c(this, 0x41638ca, 0xffffd8f1);
    if (*(int*)(self + 0xe8) != 0)
        FUN_00e31160(0);
    ((X*)FUN_0067cac0(0xe807e90c, 1))->FUN_0067c8c0();
}

// ------------------------------------------------------------------ 0x00da0070
// @ 0x00da0070
void X::FUN_00da0070(int* param_2)
{
    char* self = (char*)this;
    int mgr = *(int*)(*(int*)((char*)param_2 + 0xb4c) + 0x600);
    int* begin = *(int**)(self + 0x64);
    int* end = *(int**)(self + 0x68);
    int* it = begin;
    while (it != end) {
        if (*it == (int)param_2)
            break;
        ++it;
    }
    if (it != end)
        it = (int*)FUN_00b6f4f0(it + 1, end, it, &param_2);
    ((VecErase*)(self + 0x64))->erase(it, end);
    Poly* p = (Poly*)((VObj*)param_2)->p3(0x4f176642);
    if (p != 0) {
        X* c = (X*)p;
        if (c->FUN_00c232d0())
            ((X*)mgr)->FUN_00bc9b60();
    }
    if (*(int*)(self + 0x64) == *(int*)(self + 0x68))
        ((X*)mgr)->FUN_00bc9b60();
    *(int*)((char*)param_2 + 0xb58) &= 0xffffffdf;
    ((X*)FUN_00b3d310((char*)param_2 + 0xc0))->FUN_00b453a0();
}

// ------------------------------------------------------------------ 0x00da0120
// @ 0x00da0120
void X::FUN_00da0120(int* param_2)
{
    char* self = (char*)this;
    int mgr = *(int*)(*(int*)((char*)param_2 + 0xb4c) + 0x600);
    int* begin = *(int**)(self + 0x78);
    int* end = *(int**)(self + 0x7c);
    int* it = begin;
    while (it != end) {
        if (*it == (int)param_2)
            break;
        ++it;
    }
    if (it != end)
        it = (int*)FUN_00b6f4f0(it + 1, end, it, &param_2);
    ((VecErase*)(self + 0x78))->erase(it, end);
    if (*(int*)(self + 0x78) == *(int*)(self + 0x7c))
        ((X*)mgr)->FUN_00bc9b60();
    *(int*)((char*)param_2 + 0xb58) |= 0x20;
    ((X*)FUN_00b3d310((char*)param_2 + 0xc0))->FUN_00b453a0();
}

// ------------------------------------------------------------------ 0x00da05f0
// @ 0x00da05f0
int __cdecl FUN_00da05f0(int param_1)
{
    u32 uVar1 = *(u32*)(param_1 + 0x1a8) & 0xbfffffff;
    int* piVar2;
    if (uVar1 < (u32)((int)(gPoolEnd - gPoolBase) / 0x210) &&
        (piVar2 = (int*)(uVar1 * 0x210 + (int)gPoolBase), *piVar2 >= 0))
        piVar2 = piVar2 + 1;
    else
        piVar2 = 0;
    FUN_00d9cf70(piVar2[3]);
    ((X*)piVar2)->FUN_00d9ff00();
    ((X*)&gPoolBase)->FUN_00d9ebc0(*(u32*)(param_1 + 0x1a8) & 0xbfffffff);
    FUN_00db4a20((int*)param_1);
    return 1;
}

// ------------------------------------------------------------------ 0x00da0680
// @ 0x00da0680
void __cdecl FUN_00da0680(int* param_1)
{
    int eax = *(int*)(*(int*)((char*)param_1 + 0xb4c) + 0x600);
    if (eax != 0)
        ((X*)&gPoolBase)->FUN_00d9eb70(*(int*)(eax + 0x1a8))->FUN_00da0070(param_1);
    ((X*)param_1)->FUN_00c0ba10();
    ((X*)(*(int*)((char*)param_1 + 0xb4c) + 8))->FUN_00bc98f0(0x10000, 0);
    ((Poly*)param_1)->a84(0, 0, 0);
    ((X*)(*(int*)((char*)param_1 + 0xb4c)))->FUN_00bcb430();
}

// ------------------------------------------------------------------ 0x00da06f0
// @ 0x00da06f0
void __cdecl FUN_00da06f0(int* param_1)
{
    int eax = *(int*)(*(int*)((char*)param_1 + 0xb4c) + 0x600);
    if (eax != 0)
        ((X*)&gPoolBase)->FUN_00d9eb70(*(int*)(eax + 0x1a8))->FUN_00da0120(param_1);
    ((X*)((char*)param_1 + 0xfd0))->FUN_00b453a0();
    ((X*)param_1)->FUN_00c17350(0x950a2438, 0);
    ((X*)(*(int*)((char*)param_1 + 0xb4c) + 8))->FUN_00bc98f0(0, 0x200000);
    ((X*)(*(int*)((char*)param_1 + 0xb4c) + 8))->FUN_00bc98f0(0, 0x2000000);
    ((Poly*)param_1)->a84(0, 0, 0);
    ((X*)(*(int*)((char*)param_1 + 0xb4c)))->FUN_00bcb430();
}
