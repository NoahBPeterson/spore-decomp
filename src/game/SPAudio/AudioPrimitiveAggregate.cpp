// src/game/SPAudio/AudioPrimitiveAggregate.cpp -- migrated from slice(s) s00a35d20, s00a168c0 by tools/migrate/rewrite.py
// Object file: SPAudio/AudioPrimitiveAggregate.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/IPrimitive.h"
#include "EA/Audio/PrimitiveAggregate.h"
#include "EA/Audio/ResponseCurve.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* g_freeList_6d900;
extern "C" char  g_alloc_166d8f0;
extern "C" char paVtbl0, paVtbl1, paVtbl2, paBaseVtbl0, paBaseVtbl1, paBaseVtbl2;
extern "C" float g_aggDefault;     // 0x01552ba0
#include <intrin.h>
#include <string.h>

// ---- items of slice s00a168c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
struct SystemAT;                       // EA::Audio::System (huge vtable)
SystemAT* GetSystemAT();               // 0x00a206f0
int       FUN_00899480(void*, void*);
void*     FUN_006abeb0(u32 size);
struct FixedAllocatorBase { bool AddCore(int, int); };   // 0x00926650
void      __cdecl op_delete(void*);      // 0x00f47380
extern "C" void* g_freeList_6d900;
extern "C" char  g_alloc_166d8f0;
struct IPrimitive {
    virtual void  v00();
    virtual int   v04();                 // AddRef
    virtual void  v08();                 // Release
    virtual void* v0c(u32);
    virtual bool  v10();
    virtual void  v14();
    virtual void  v18();
    virtual void  v1c();
    virtual bool  v20(int);
    virtual void  v24(int);
    virtual void  v28(float value, int mod);   // SetModificationSource(value, mod)
    virtual void  v2c(int);
    virtual int   v30();
    virtual void  v34();
    virtual void  v38();
};
struct PAgg {
    void*  vtbl0;      // +0x00
    void*  vtbl1;      // +0x04
    void*  vtbl2;      // +0x08
    int    mRefCount;  // +0x0c
    void** mpBegin;    // +0x10
    void** mpEnd;      // +0x14
    void** mpCapacity; // +0x18
    void*  m1c;        // +0x1c
    void*  m20;        // +0x20
    void*  m24;        // +0x24
    u8     mBuf[0x28]; // +0x28
    bool   mbDirty;    // +0x50
    u8     pad51[3];
    u32    mMethod;    // +0x54
    int    mModify;    // +0x58
    u32    m5c;        // +0x5c
    float  mValue;     // +0x60
    bool   mb64;       // +0x64
    u8     pad65[3];
    int    m68;        // +0x68

    void*  QueryInterface(u32 id);              // 00a16aa0
    void   SetEnabled(bool b);                  // 00a16a40
    void   OnConfigurePrimitive(void* p);       // 00a16b40
    bool   RemoveElement(IPrimitive* p);        // 00a16b80
    bool   UpdateValueFromChildren();           // 00a16bc0
    void   SetModificationSource(float value, int mod); // 00a16be0
    void*  Destroy(u8 flags);                   // 00a16ca0
    bool   UpdatePrimitives();                  // 00a16da0
    float  CalculateAggregate();
};
struct Agg {
    void*  vtbl;       // +0x00 (object+0x04)
    u8     pad0[8];
    void** mpBegin;    // +0x0c (object+0x10)
    void** mpEnd;      // +0x10 (object+0x14)
    void** mpCapacity; // +0x14 (object+0x18)
    u8     pad1[0x34];
    bool   mbDirty;    // +0x4c (object+0x50)
    u8     pad2[3];
    int    m50;        // +0x50 (object+0x54)
    int    mModify;    // +0x54 (object+0x58)

    bool   RemoveElement(IPrimitive* p);        // 00a16b80
    bool   PushBack(IPrimitive* p);             // 00a16e20
};
extern "C" char paVtbl0, paVtbl1, paVtbl2, paBaseVtbl0, paBaseVtbl1, paBaseVtbl2;
extern "C" float g_aggDefault;     // 0x01552ba0
struct PA_Prim { virtual void p0() {} virtual int p1() { return 0; } };
struct PA_Agg  { virtual void a0() {} };
struct PA_RC   { virtual void r0() {} int mRefCount; PA_RC() { mRefCount = 0; } };
struct PAggC : PA_Prim, PA_Agg, PA_RC {
    char*  mpBegin;      // +0x10
    char*  mpEnd;        // +0x14
    char*  mpCapacity;   // +0x18
    void*  m1c;
    void*  m20;
    void*  m24;
    u8     mBuf[0x28];   // +0x28
    bool   mbDirty;      // +0x50
    u8     pad51[3];
    u32    mMethod;      // +0x54
    int    mModify;      // +0x58
    u32    m5c;          // +0x5c
    float  mValue;       // +0x60
    bool   mb64;         // +0x64
    u8     pad65[3];
    int    m68;          // +0x68

    PAggC(int arg);
};
// ---- items of slice s00a168c0 end

// ---- items of slice s00a35d20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_01453140;         // 0x1453140
extern char g_01453124;         // 0x1453124
extern char g_01453120;         // 0x1453120
extern char g_013ef094;         // 0x13ef094
extern char g_013eb938;         // 0x13eb938
extern char c_013ebb38[];       // 0x13ebb38 EASTL allocator.h path
extern char c_013f2150[];       // 0x13f2150 "EASTL"
#define VFN(p, off) ((*(void***)(p))[(off) / 4])
void   __fastcall DestroyAutoRefVec(void* self);                                    // 0x7c80c0
void   __cdecl    copyImpl(void* a, void* b, void* c);                              // 0x6782c0
void   __cdecl    fAC97A0(void* a, void* b, void* c);                               // 0xac97a0
void*  __cdecl    VecDoInsertValue(void* self, void* src, int nbytes);              // 0x11e0744
void*  __cdecl    EAAllocate(u32 size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
void   __cdecl    opDelete(void* p);                                                // 0xf47380
namespace EA {
namespace Audio {
class PrimitiveAggregate_s00a3_5d20 { public:
    char pad[0x100];

    float CalculateAggregate();     // 0xa367a0
    bool  ShouldUpdate(u32 b);      // 0xa36750
    void  SetParam(float value, int param_3); // 0xa36990
};
}
}
namespace EA {
namespace Audio {
static float ElemValue(void* base, int i)
{
    void* e = *(void**)((char*)base + i * 4);
    return ((float(__thiscall*)(void*))VFN(e, 0x1c))(e);
}
}
}
struct S106 {
    char pad[0x100];
    void pushPair(void** v);            // 0xa35ef0
    void dtor();                        // 0xa36a10
    void vecInsert(void** pos, void** value); // 0xa36ad0
    bool vecRemove(u32 key);            // 0xa36c80
};
// ---- items of slice s00a35d20 end

// @ 0x00a16a40
void PAgg::SetEnabled(bool b)
{
    if (b) {
        SystemAT* s = GetSystemAT();
        ((void (__thiscall*)(void*, void*))((*(void***)s)[0x19c / 4]))(s, this);
        mb64 = true;
        return;
    }
    if (mb64) {
        SystemAT* s = GetSystemAT();
        ((void (__thiscall*)(void*, void*))((*(void***)s)[0x1a0 / 4]))(s, this);
        mb64 = false;
    }
}

// @ 0x00a16ad0
void* FUN_00a16ad0(u32 size)
{
    if (size == 0x6c) {
        do {
            void* p = g_freeList_6d900;
            if (p != 0) {
                g_freeList_6d900 = *(void**)p;
                return p;
            }
        } while (((FixedAllocatorBase*)&g_alloc_166d8f0)->AddCore(0, 0));
        return 0;
    }
    return FUN_006abeb0(size);
}

// @ 0x00a16b80
bool Agg::RemoveElement(IPrimitive* p)
{
    void** it = mpBegin;
    while (it != mpEnd) {
        if (*it == (void*)p)
            break;
        ++it;
    }
    if (it == mpEnd)
        return false;
    *it = *(mpEnd - 1);
    --mpEnd;
    p->v04();
    mbDirty = true;
    return true;
}

// @ 0x00a16bc0
bool PAgg::UpdateValueFromChildren()
{
    if (mpBegin != mpEnd)
        mValue = CalculateAggregate();
    return true;
}

// @ 0x00a16be0
void PAgg::SetModificationSource(float value, int mod)
{
    if (mod != 0 && mModify == mod)
        return;
    bool dirty = mbDirty;
    void** begin = mpBegin;
    mModify = mod;
    void** end = mpEnd;
    for (void** it = begin; it != end; ++it) {
        IPrimitive* e = (IPrimitive*)*it;
        e->v28(value, mod);
        if (e->v20(0))
            dirty = true;
    }
    if (dirty) {
        mValue = CalculateAggregate();
        --mModify;
        mbDirty = true;
    }
}

// @ 0x00a16ca0
void* PAgg::Destroy(u8 flags)
{
    vtbl0 = &paVtbl0;
    vtbl1 = &paVtbl1;
    vtbl2 = &paVtbl2;
    _ReadWriteBarrier();
    void* p = (void*)mpBegin;
    if (p != 0 && p != m20)
        op_delete(p);
    vtbl2 = &paBaseVtbl2;
    vtbl1 = &paBaseVtbl1;
    vtbl0 = &paBaseVtbl0;
    if (flags & 1) {
        vtbl0 = g_freeList_6d900;
        g_freeList_6d900 = this;
    }
    return this;
}

// @ 0x00a16d00
PAggC::PAggC(int arg)
{
    mpBegin = mpEnd = (char*)(m20 = mBuf);
    mpCapacity = mpBegin + 0x28;
    mModify = 0;
    m5c = 0;
    mb64 = false;
    mbDirty = true;
    mMethod = 0xd256aaba;
    mValue = g_aggDefault;
    char* last = *(char* volatile*)&mpEnd;
    char* first = *(char* volatile*)&mpBegin;
    memcpy(first, last, mpEnd - last);
    mpEnd -= ((last - first) >> 2) * 4;
    m68 = arg;
}

// @ 0x00a16da0
bool PAgg::UpdatePrimitives()
{
    ((IPrimitive*)this)->v2c(0);
    for (void** it = mpBegin; it != mpEnd; ++it) {
        IPrimitive* e = (IPrimitive*)*it;
        int a = e->v30();
        if (a == ((IPrimitive*)this)->v30())
            e->v14();
        e->v04();
    }
    while (mpEnd != mpBegin)
        --mpEnd;
    return true;
}

// @ 0x00a16e20
bool Agg::PushBack(IPrimitive* p)
{
    p->v00();
    if (mpEnd < mpCapacity) {
        void** slot = mpEnd;
        mpEnd = slot + 1;
        if (slot) {
            *slot = p;
            --mModify;
            mbDirty = true;
            return true;
        }
    } else {
        FUN_00899480(mpEnd, &p);
    }
    --mModify;
    mbDirty = true;
    return true;
}

// @ 0x00a367a0
namespace EA { namespace Audio {
float PrimitiveAggregate_s00a3_5d20::CalculateAggregate()
{
    char* self = (char*)this;
    int n = (*(int*)(self + 0x14) - *(int*)(self + 0x10)) >> 2;
    if (n <= 0) return 0.0f;
    void* base = *(void**)(self + 0x10);
    if (n == 1) return ElemValue(base, 0);

    u32 mode = *(u32*)(self + 0x54);
    float acc = 0.0f;
    int i;

    if (mode == 0x467e1ea3) {                    // minimum
        acc = ElemValue(base, 0);
        for (i = 1; i < n; ++i) { float v = ElemValue(base, i); if (v < acc) acc = v; }
        return acc;
    }
    if (mode == 0x3e7e124d) {                    // maximum
        acc = ElemValue(base, 0);
        for (i = 1; i < n; ++i) { float v = ElemValue(base, i); if (acc < v) acc = v; }
        return acc;
    }
    if (mode == 0xd256aaba) {                    // product
        acc = ElemValue(base, 0);
        for (i = 1; i < n; ++i) acc *= ElemValue(base, i);
        return acc;
    }
    if (mode == 0xf524f3a6) {                    // average
        for (i = 0; i < n; ++i) acc += ElemValue(base, i);
        if (n > 1) acc = acc / (float)n;
        return acc;
    }
    if (mode == 0x1d3454e5) {                    // last
        return ElemValue(base, n - 1);
    }
    if (mode == 0x3b83da79) {                    // first
        return ElemValue(base, 0);
    }
    return acc;
}
}}  // namespace EA::Audio

// @ 0x00a36990
namespace EA { namespace Audio {
void PrimitiveAggregate_s00a3_5d20::SetParam(float value, int param_3)
{
    char* self = (char*)this;
    if (*(int*)(self + 0x58) == param_3) return;
    *(int*)(self + 0x58) = param_3;
    void** end = *(void***)(self + 0x14);
    void** begin = *(void***)(self + 0x10);
    u8 flag = *(u8*)(self + 0x50);
    for (; begin != end; ++begin) {
        void* e = *begin;
        ((void(__thiscall*)(void*, float, int))VFN(e, 0x28))(e, value, param_3);
        if (((bool(__thiscall*)(void*, int))VFN(e, 0x20))(e, 0)) flag = 1;
    }
    if (flag) {
        *(float*)(self + 0x60) = CalculateAggregate();
        --*(int*)(self + 0x58);
        *(u8*)(self + 0x50) = 1;
    }
}
}}  // namespace EA::Audio

// @ 0x00a36a10
void S106::dtor()
{
    char* self = (char*)this;
    *(void**)(self + 0) = &g_01453140;
    *(void**)(self + 4) = &g_01453124;
    *(void**)(self + 8) = &g_01453120;
    DestroyAutoRefVec(self + 0x10);
    *(void**)(self + 8) = &g_013ef094;
    *(void**)(self + 4) = &g_013eb938;
    *(void**)(self + 0) = &g_013eb938;
}

// @ 0x00a36ad0
void S106::vecInsert(void** pos, void** value)
{
    char* self = (char*)this;
    int* begin = *(int**)(self + 0);
    int* end = *(int**)(self + 4);
    int* cap = *(int**)(self + 8);
    if (end != cap) {
        int* src = (int*)value;
        if ((int*)pos <= src && src < end) src = src + 1;
        int* dest = end;
        if (dest) {
            int v = *(int*)(end - 1);
            *dest = v;
            if (v) ((void(__thiscall*)(void*))VFN((void*)v, 0))((void*)v);
        }
        fAC97A0(pos, end - 1, end);
        int* nv = *(int**)src;
        int* ov = *(int**)pos;
        if (nv != ov) {
            if (nv) ((void(__thiscall*)(void*))VFN((void*)nv, 0))((void*)nv);
            *(int**)pos = nv;
            if (ov) ((void(__thiscall*)(void*))VFN((void*)ov, 4))((void*)ov);
        }
        *(int**)(self + 4) = end + 1;
        return;
    }

    int count = (int)(end - begin);
    int newcap;
    if (count <= 0) newcap = 1;
    else newcap = count * 2;
    int* buf = 0;
    if (newcap != 0)
        buf = (int*)EAAllocate((u32)(newcap * 4), c_013f2150, 0, 0, c_013ebb38, 0xd1);
    int before = (int)((char*)pos - (char*)begin);
    void* r1 = VecDoInsertValue(buf, begin, before);
    int* mid = (int*)((char*)r1 + before);
    if (mid) {
        int v = *(int*)value;
        *mid = v;
        if (v) ((void(__thiscall*)(void*))VFN((void*)v, 0))((void*)v);
    }
    int after = (int)((char*)end - (char*)pos);
    void* r2 = VecDoInsertValue((char*)mid + 4, pos, after);
    int* newend = (int*)((char*)r2 + after);
    if (begin && begin != *(int**)(self + 0x10)) opDelete(begin);
    *(int**)(self + 4) = newend;
    *(int**)(self + 0) = buf;
    *(int**)(self + 8) = (int*)((char*)buf + newcap * 4);
}

// @ 0x00a36c80
bool S106::vecRemove(u32 key)
{
    char* self = (char*)this;
    u32* p = *(u32**)(self + 0xc);
    u32* end = *(u32**)(self + 0x10);
    while (p != end && *p != key) ++p;
    if (p == end) return false;
    if (p + 1 < end) copyImpl(p + 1, end, p);
    *(u32**)(self + 0x10) = end - 1;
    void* e = *(void**)(end - 1);
    if (e) ((void(__thiscall*)(void*))VFN(e, 4))(e);
    *(u8*)(self + 0x4c) = 1;
    return true;
}
