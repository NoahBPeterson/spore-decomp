// src/game/SPEngine/_at_00700000.cpp -- migrated from slice(s) s006ffe00 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_00700000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <xmmintrin.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include <new>
#include <intrin.h>

// ---- items of slice s006ffe00 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_011e073e(void* p, int a, unsigned size);
void  __cdecl FUN_00f47410(int a);
void  __cdecl FUN_00762a00(int a);
void  __cdecl FUN_00762a30(int a);
void  __cdecl FUN_00761130(int a);
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
void* __cdecl operator_new(unsigned size, int align, int flags, const char* name,
                           int a, int b, int c, int d);           // 0x00f473d0
void* __cdecl FUN_006df700(void* a, void* b, void* c);            // 0x006df700 CopyRefPtr
void  __stdcall FUN_0059c410(void* a, void* b);                   // 0x0059c410 ReleaseAutoRefRange
struct SpCellRecord {
    int     m00[3];     // +0x00
    __m128  m10;        // +0x10  (16-byte aligned -> 4-byte hole at +0x0c)
    int     m20[6];     // +0x20
    uint8_t m38[4];     // +0x38
    int     m3c[3];     // +0x3c  (8-byte hole at +0x48)
    __m128  m50;        // +0x50
    __m128  m60;        // +0x60
    __m128  m70;        // +0x70
    __m128  m80;        // +0x80
    int     m90[3];     // +0x90  (4-byte tail pad to +0xa0)
    SpCellRecord(const SpCellRecord& o);
};
struct CellAccessor {
    char pad[8];
    int  f8;   // +0x08
    int  fc;   // +0x0c
    int Get(int* out);
};
struct CellArray {
    void*         vt;      // +0x00
    int           f04;     // +0x04
    SpCellRecord* data;    // +0x08
    unsigned      count;   // +0x0c
    CellArray(const SpCellRecord* src, unsigned n);
    void* Destroy(unsigned flags);
};
typedef void (__thiscall* ThiscallVoid)(void*);
struct BoolVec {
    unsigned char* begin;   // +0x00
    unsigned char* end;     // +0x04
    unsigned char* cap;     // +0x08
    int            f0c;     // +0x0c
    int            f10;     // +0x10
    int            f14;     // +0x14
    unsigned char  buf[16]; // +0x18
};
struct Vec3p {
    void* begin;   // +0x00
    void* end;     // +0x04
    void* cap;     // +0x08
};
struct Vec3f {
    float x, y, z;
};
class IObject {
public:
    virtual void f0();
    virtual void Release();       // vtable + 0x04
};
class RefObj {
public:
    virtual void OnZero(int n);   // vtable + 0x00
    volatile int mCount;          // +0x04
};
class AutoRef {
public:
    RefObj* mp;
    AutoRef() {}
    AutoRef(RefObj* p) : mp(p) {}
    ~AutoRef() {
        if (mp != 0) {
            int n = mp->mCount - 1;
            mp->mCount = n;
            if (n == 0) {
                mp->mCount = 1;
                mp->OnZero(1);
            }
        }
    }
};
struct CellRec7c {
    unsigned char m00[0x74];  // +0x00
    IObject*      mpObj;      // +0x74
    RefObj*       mpRef;      // +0x78
    void Assign(const CellRec7c& o);
};
struct Elem8 { int a, b; };
static void ErasePtrRange(BoolVec& v) {
    int* first = (int*)v.begin;
    int* last = (int*)v.end;
    memcpy(first, last, (char*)v.end - (char*)last);
    v.end = (unsigned char*)((int*)v.end - (last - first));
}
static void Erase8Range(Vec3p& v) {
    Elem8* first = (Elem8*)v.begin;
    Elem8* last = (Elem8*)v.end;
    Elem8* dst = first;
    Elem8* src = last;
    Elem8* stop = (Elem8*)v.end;
    while (src != stop) {
        *dst = *src;
        ++src;
        ++dst;
    }
    v.end = (char*)((Elem8*)v.end - (last - (Elem8*)v.begin));
}
struct cCellList {
    void*          vt;        // 0x000
    volatile long  f004;      // 0x004
    int            f008;      // 0x008
    int            f00c;      // 0x00c
    int            f010;      // 0x010
    int            f014;      // 0x014
    BoolVec        v018;      // 0x018
    BoolVec        v040;      // 0x040
    BoolVec        v068;      // 0x068
    BoolVec        v090;      // 0x090
    BoolVec        v0b8;      // 0x0b8
    Vec3p          v0e0;      // 0x0e0  (8-byte elements)
    int            pad0ec[2]; // 0x0ec
    Vec3p          v0f4;      // 0x0f4
    int            pad100[2]; // 0x100
    Vec3p          v108;      // 0x108  (0x7c-byte elements)
    int            pad114[2]; // 0x114
    Vec3f          mMin;      // 0x11c
    Vec3f          mMax;      // 0x128
    float          f134;
    IObject*       f138;
    IObject*       f13c;
    cCellList* Construct();
    void Clear();
    ~cCellList();
};
struct Vec4b {
    int* begin;   // +0x00
    int* end;     // +0x04
    int* cap;     // +0x08
    void PushBack(const int* v);
    void Grow(void* pos, const void* v);
};
static void FreeVecBuf(void* p) {
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        EASTL_allocator_deallocate(p);
}
// ---- items of slice s006ffe00 end

// @ 0x00700290
SpCellRecord::SpCellRecord(const SpCellRecord& o)
{
    m00[0] = o.m00[0]; m00[1] = o.m00[1]; m00[2] = o.m00[2];
    m10 = o.m10;
    m20[0] = o.m20[0]; m20[1] = o.m20[1]; m20[2] = o.m20[2];
    m20[3] = o.m20[3]; m20[4] = o.m20[4]; m20[5] = o.m20[5];
    m38[0] = o.m38[0]; m38[1] = o.m38[1]; m38[2] = o.m38[2]; m38[3] = o.m38[3];
    m3c[0] = o.m3c[0]; m3c[1] = o.m3c[1]; m3c[2] = o.m3c[2];
    m50 = o.m50; m60 = o.m60; m70 = o.m70; m80 = o.m80;
    m90[0] = o.m90[0]; m90[1] = o.m90[1]; m90[2] = o.m90[2];
}

// @ 0x00700360
int CellAccessor::Get(int* out)
{
    if (out)
        *out = fc;
    return f8;
}

// @ 0x007003a0
CellArray::CellArray(const SpCellRecord* src, unsigned n)
{
    f04 = 0;
    vt = (void*)0x140c460;
    unsigned __int64 sz = (unsigned __int64)n * 0xa0u;
    unsigned size = (unsigned)sz | (unsigned)-(int)((sz >> 32) != 0);
    data = (SpCellRecord*)operator_new(size, 0x10, 0, "Graphics", 0, 0, 0, 0);
    count = n;
    FUN_011e073e(data, 0, n * 0xa0);
    for (unsigned i = 0; i < n; i++)
        new (&data[i]) SpCellRecord(src[i]);
}

// @ 0x00700450
void* CellArray::Destroy(unsigned flags)
{
    vt = (void*)0x140c460;
    EASTL_allocator_deallocate(data);
    vt = (void*)0x13ef094;
    if (flags & 1)
        EASTL_allocator_deallocate(this);
    return this;
}

// @ 0x007004d0
cCellList* cCellList::Construct()
{
    vt = (void*)0x13ebcdc;
    _InterlockedExchange(&f004, 0);
    f008 = 0;
    f00c = 0;
    f010 = 0;
    f014 = 0;
    vt = (void*)0x140c464;

    v018.f14 = 0;
    v018.begin = v018.buf;
    v018.end = v018.begin;
    v018.cap = v018.begin + 16;

    v040.f14 = 0;
    v040.begin = v040.buf;
    v040.end = v040.begin;
    v040.cap = v040.begin + 16;

    v068.f14 = 0;
    v068.begin = v068.buf;
    v068.end = v068.begin;
    v068.cap = v068.begin + 16;

    v090.f14 = 0;
    v090.begin = v090.buf;
    v090.end = v090.begin;
    v090.cap = v090.begin + 16;

    v0b8.f14 = 0;
    v0b8.begin = v0b8.buf;
    v0b8.end = v0b8.begin;
    v0b8.cap = v0b8.begin + 16;

    v0e0.begin = 0;
    v0e0.end = 0;
    v0e0.cap = 0;
    v0f4.begin = 0;
    v0f4.end = 0;
    v0f4.cap = 0;
    v108.begin = 0;
    v108.end = 0;
    v108.cap = 0;

    Vec3f mn;
    mn.x = FLT_MAX;
    mn.y = FLT_MAX;
    mn.z = FLT_MAX;
    mMin = mn;
    Vec3f mx;
    mx.x = -FLT_MAX;
    mx.y = -FLT_MAX;
    mx.z = -FLT_MAX;
    mMax = mx;
    f134 = 1.0f;
    f138 = 0;
    f13c = 0;
    return this;
}

// @ 0x00700640
void Vec4b::PushBack(const int* v)
{
    int* old = end;
    if (old < cap) {
        end = old + 1;
        if (old)
            *old = *v;
    } else {
        Grow(old, v);
    }
}

// @ 0x007006d0
void cCellList::Clear()
{
    int n = (int)((char*)v018.end - (char*)v018.begin) >> 2;
    for (int i = 0; i < n; i++)
        FUN_00f47410(*(int*)(v018.begin + i * 4));
    ErasePtrRange(v018);

    n = (int)((char*)v068.end - (char*)v068.begin) >> 2;
    for (int i = 0; i < n; i++)
        FUN_00762a00(*(int*)(v068.begin + i * 4));
    ErasePtrRange(v068);

    n = (int)((char*)v040.end - (char*)v040.begin) >> 2;
    for (int i = 0; i < n; i++)
        FUN_00762a30(*(int*)(v040.begin + i * 4));
    ErasePtrRange(v040);

    n = (int)((char*)v090.end - (char*)v090.begin) >> 2;
    for (int i = 0; i < n; i++)
        FUN_00761130(*(int*)(v090.begin + i * 4));
    ErasePtrRange(v090);

    ErasePtrRange(v0b8);
    Erase8Range(v0e0);

    {
        int* first = (int*)v0f4.begin;
        int* last  = (int*)v0f4.end;
        void* range = FUN_006df700(last, last, first);
        FUN_0059c410(range, v0f4.end);
        v0f4.end = (char*)((int*)v0f4.end - (last - first));
    }

    {
        CellRec7c* first = (CellRec7c*)v108.begin;
        CellRec7c* last  = (CellRec7c*)v108.end;
        CellRec7c* stop  = last;
        CellRec7c* src   = last;
        while (src != stop) {
            first->Assign(*src);
            ++src;
            ++first;
        }
        for (CellRec7c* p = (CellRec7c*)v108.begin; p < stop; ++p) {
            {
                AutoRef tmp(p->mpRef);
                (void)tmp;
            }
            if (p->mpObj != 0)
                p->mpObj->Release();
        }
        v108.end = (char*)(stop - (last - (CellRec7c*)v108.begin));
    }

    Vec3f mn;
    mn.x = FLT_MAX;
    mn.y = FLT_MAX;
    mn.z = FLT_MAX;
    Vec3f mx;
    mx.x = -FLT_MAX;
    mx.y = -FLT_MAX;
    mx.z = -FLT_MAX;
    mMax = mx;
    mMin = mn;
    f134 = 1.0f;

    if (f138 != 0) {
        IObject* q = f138;
        f138 = 0;
        q->Release();
    }
    if (f13c != 0) {
        IObject* q = f13c;
        f13c = 0;
        q->Release();
    }
    _ReadWriteBarrier();
}

// @ 0x00700a30
cCellList::~cCellList()
{
    vt = (void*)0x140c464;
    Clear();
    if (f13c != 0) {
        IObject* q = f13c;
        q->Release();
    }
    if (f138 != 0) {
        IObject* q = f138;
        q->Release();
    }
    ((ThiscallVoid)0x41f270)((char*)this + 0x108);
    ((ThiscallVoid)0x41eb80)((char*)this + 0xf4);
    FreeVecBuf(v0e0.begin);
    FreeVecBuf(v0b8.begin);
    FreeVecBuf(v090.begin);
    FreeVecBuf(v068.begin);
    FreeVecBuf(v040.begin);
    FreeVecBuf(v018.begin);
    vt = (void*)0x13eb938;
}
