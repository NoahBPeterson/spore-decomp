// src/game/SPAudio/AudioPrimitiveAggregate.cpp -- migrated from slice(s) s00a168c0 by tools/migrate/rewrite.py
// Object file: SPAudio/AudioPrimitiveAggregate.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/IPrimitive.h"
#include "EA/Audio/PrimitiveAggregate.h"
#include "EA/Audio/ResponseCurve.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* g_freeList_6d900;
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
void      __cdecl op_delete(void*);      // 0x00f47380
extern "C" void* g_freeList_6d900;
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
extern "C" char paVtbl0, paVtbl1, paVtbl2, paBaseVtbl0, paBaseVtbl1, paBaseVtbl2;
struct ResponseCurve {
    u8   mData[0x360];
    int  mnSize;
    float GetOutputValue(float in);          // 00a1a110
    void  SetResponseCurveData(void*, int);  // 00a1a590
};
struct PResp {
    void* vtbl0;          // +0x00
    void* vtbl1;          // +0x04
    int   mRefCount;      // +0x08
    ResponseCurve mCurve; // +0x0c
    void* mpPrimitive;    // +0x370
    bool  mbDirty;        // +0x374
    u8    pad375[3];
    int   mModify;        // +0x378
    float mValue;         // +0x37c
    u8    pad380[4];
    bool  mb384;          // +0x384
    u8    pad385[3];
    int   m388;           // +0x388

    bool  GetDirty(int);                 // 00a17160
    void  SetEnabled(bool b);            // 00a17170
    bool  RecomputeValue();              // 00a17250
    bool  Reconfigure();                 // 00a17280
    void  SetModificationSource(float value, int mod); // 00a172e0
    void  Destroy();                     // 00a17360 (destructor body, no flags)
};
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
void PResp::SetModificationSource(float value, int mod)
{
    if (mod != 0 && mModify == mod)
        return;
    IPrimitive* p = (IPrimitive*)mpPrimitive;
    mModify = mod;
    if (p == 0)
        return;
    p->v28(value, mod);
    if (p->v20(0)) {
        float v = (float)((float (__thiscall*)(void*))((*(void***)p)[0x1c / 4]))(p);
        mValue = mCurve.GetOutputValue(v);
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
    m68 = arg;
    char* last = mpEnd;
    char* first = mpBegin;
    memcpy(first, last, mpEnd - last);
    mpEnd -= ((last - first) >> 2) * 4;
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
