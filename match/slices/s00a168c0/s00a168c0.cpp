// Slice s00a168c0 - EA::Audio primitives, response curves, resource configuration.
// Real names come from the 2008 dev-build PDB where known (docs/matching.md).
#include "types.h"
#include <intrin.h>
#include <string.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---------------------------------------------------------------------------
// Generic helpers / external callees
// ---------------------------------------------------------------------------
struct SystemAT;                       // EA::Audio::System (huge vtable)
struct Server;                         // EA::Messaging::Server
struct TimerManager;                   // rw::audio::core::TimerManager

struct TimerManager;

SystemAT* GetSystemAT();               // 0x00a206f0
Server*   GetServer();                 // 0x00883860
void      FUN_00a16870(void*, int);
void      FUN_00a161c0(void*);
int       FUN_00899480(void*, void*);
void*     FUN_006abeb0(u32 size);
struct FixedAllocatorBase { bool AddCore(int, int); };   // 0x00926650
void      __cdecl op_delete(void*);      // 0x00f47380

struct TimerManager {
    bool AddTimer(void* key, void* cb, void* obj, const char* name, int a, int b);
};

extern "C" void* g_freeList_6d900;
extern "C" void* g_freeList_6d948;
extern "C" char  g_alloc_166d8f0;
extern "C" char  g_alloc_166d938;

// ---------------------------------------------------------------------------
// Primitive element interface (shape of the aggregate element vtable)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// EA::Audio::PrimitiveAggregate
// ---------------------------------------------------------------------------
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

// ---- PrimitiveAggregate::QueryInterface @ 0x00a16aa0 ----------------------
void* PAgg::QueryInterface(u32 id)
{
    if (id != 0xee3f516e && id != 0x4bc808e5) {
        if (id == 0x4e73a43a && this != 0)
            return (char*)this + 4;
        return 0;
    }
    return this;
}

// ---- PrimitiveAggregate::SetEnabled @ 0x00a16a40 --------------------------
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

// ---- PrimitiveAggregate::OnConfigurePrimitive @ 0x00a16b40 ----------------
void PAgg::OnConfigurePrimitive(void* p)
{
    void** it = mpBegin;
    void** end = mpEnd;
    while (it != end) {
        ((IPrimitive*)*it)->v24((int)p);
        ++it;
    }
    if (mModify == (int)p)
        mbDirty = false;
}

// ---- PrimitiveAggregate::RemoveElement @ 0x00a16b80 -----------------------
// NOTE: this method's 'this' is the IPrimitiveAggregate subobject (object+4).
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

// ---- PrimitiveAggregate::PushBack @ 0x00a16e20 ----------------------------
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

// ---- PrimitiveAggregate::UpdateValueFromChildren @ 0x00a16bc0 -------------
bool PAgg::UpdateValueFromChildren()
{
    if (mpBegin != mpEnd)
        mValue = CalculateAggregate();
    return true;
}

// ---- PrimitiveAggregate::SetModificationSource @ 0x00a16be0 ---------------
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

// ---- PrimitiveAggregate::UpdatePrimitives @ 0x00a16da0 --------------------
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

// ---- PrimitiveAggregate::Destroy @ 0x00a16ca0 -----------------------------
extern "C" char paVtbl0, paVtbl1, paVtbl2, paBaseVtbl0, paBaseVtbl1, paBaseVtbl2;
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

// ---------------------------------------------------------------------------
// EA::Audio::PrimitiveBase (vtable lives in .data; 'this' at object+0)
// ---------------------------------------------------------------------------
struct PrimBase {
    void* vtbl0;    // +0x00
    void* vtbl1;    // +0x04
    void* vtbl2;    // +0x08
    void* m0c;      // +0x0c
    bool  mbDirty;  // +0x10
    u8    pad11[3];
    void* m14;      // +0x14
    void* mpConfig; // +0x18
    void* m1c;      // +0x1c
    int   m20;      // +0x20

    bool  Shutdown();                                   // 00a16e70
    bool  GetDirty(int);                                // 00a16eb0
    void  ClearDirty(int);                              // 00a16ec0
    bool  HandleMessage(int id, void* arg);             // 00a16f00
    bool  Init();                                       // 00a16f60
};

// ---- PrimitiveBase::Shutdown @ 0x00a16e70 -------------------------------
bool PrimBase::Shutdown()
{
    Server* s = GetServer();
    if (s != 0) {
        void* payload = this ? (char*)this + 4 : 0;
        ((void (__thiscall*)(void*, void*, u32, int))((*(void***)s)[0x2c / 4]))(
            s, payload, 0x2b0c259u, 0xffffd8f1);
    }
    return true;
}

// ---- PrimitiveBase::GetDirty @ 0x00a16eb0 --------------------------------
bool PrimBase::GetDirty(int)
{
    return mbDirty;
}

// ---- PrimitiveBase::ClearDirty @ 0x00a16ec0 ------------------------------
void PrimBase::ClearDirty(int arg)
{
    if (m20 == arg)
        mbDirty = false;
}

// ---- PrimitiveBase::HandleMessage @ 0x00a16f00 --------------------------
bool PrimBase::HandleMessage(int id, void* arg)
{
    if (id == 0x2b0c259) {
        char* obj = (char*)this - 4;
        int other = *(int*)((char*)arg + 0x18);
        int mine = ((int (__thiscall*)(void*))((*(void***)obj)[0x18 / 4]))(obj);
        if (other == mine)
            ((IPrimitive*)obj)->v38();
    }
    return true;
}

// ---- PrimitiveBase::Init @ 0x00a16f60 -----------------------------------
bool PrimBase::Init()
{
    Server* s = GetServer();
    if (s != 0) {
        void* payload = this ? (char*)this + 4 : 0;
        ((void (__thiscall*)(void*, void*, u32))((*(void***)s)[0x20 / 4]))(
            s, payload, 0x2b0c259u);
    }
    SystemAT* sys = GetSystemAT();
    if (mpConfig != 0) {
        IPrimitive* cfg = (IPrimitive*)mpConfig;
        mpConfig = 0;
        cfg->v04();
    }
    void* r = ((void* (__thiscall*)(void*, void*, u32))((*(void***)this)[0x18 / 4]))(
        this, &mpConfig, 0x21407ee);
    IPrimitive* self = (IPrimitive*)this;
    ((void (__thiscall*)(void*, void*))((*(void***)sys)[0x14 / 4]))(sys, r);
    self->v38();
    return true;
}

// ---------------------------------------------------------------------------
// AutoRefCount<T>::AsPPTypeParam
// ---------------------------------------------------------------------------
struct AutoRefCount {
    void* mp;
    AutoRefCount* AsPPTypeParam();   // 00a16f40
};

// ---- AutoRefCount<T>::AsPPTypeParam @ 0x00a16f40 --------------------------
AutoRefCount* AutoRefCount::AsPPTypeParam()
{
    void* p = mp;
    if (p != 0) {
        mp = 0;
        ((IPrimitive*)p)->v04();
    }
    return this;
}

// ---------------------------------------------------------------------------
// EA::Audio primitive with a value/refcount (vtable 0x1452270)
// ---------------------------------------------------------------------------
struct PB {
    void* vtbl0;    // +0x00
    int   m4;       // +0x04
    float mValue;   // +0x08
    bool  mbDirty;  // +0x0c
    u8    pad0d[3];
    int   mModify;  // +0x10
    int   mRefCount; // +0x14
    void* mpConfig; // +0x18

    void  SetValue(float v);              // 00a16fd0
    bool  Commit();                       // 00a16ff0
    bool  GetDirty(int);                  // 00a17000
    void  ClearDirty(int);                // 00a17010
    void  SetEnabled(bool b);             // 00a17030
    int   Release();                      // 00a17070
    PB*   ctor(void* arg);                // 00a17100
    void* Destroy(u8 flags);              // 00a17130
};

extern "C" float g_pbDefault;
extern "C" char  pbVtbl, pbBaseVtbl;

// ---- PB::SetValue @ 0x00a16fd0 ------------------------------------------
void PB::SetValue(float v)
{
    if (v != mValue) {
        --mModify;
        mbDirty = true;
        mValue = v;
    }
}

// ---- PB::Commit @ 0x00a16ff0 --------------------------------------------
bool PB::Commit()
{
    ((void (__thiscall*)(void*, int))((*(void***)this)[0x2c / 4]))(this, 0);
    return true;
}

// ---- PB::GetDirty @ 0x00a17000 ------------------------------------------
bool PB::GetDirty(int)
{
    return mbDirty;
}

// ---- PB::ClearDirty @ 0x00a17010 ----------------------------------------
void PB::ClearDirty(int arg)
{
    if (mModify == arg)
        mbDirty = false;
}

// ---- PB::SetEnabled @ 0x00a17030 ----------------------------------------
void PB::SetEnabled(bool b)
{
    SystemAT* s = GetSystemAT();
    void** vt = *(void***)s;
    if (b) {
        ((void (__thiscall*)(void*, void*))vt[0x19c / 4])(s, this);
        return;
    }
    ((void (__thiscall*)(void*, void*))vt[0x1a0 / 4])(s, this);
}

// ---- PB::Release @ 0x00a17070 -------------------------------------------
int PB::Release()
{
    if (mRefCount > 1) {
        --mRefCount;
        return mRefCount;
    }
    ((void (__thiscall*)(void*, int))((*(void***)this)[0x08 / 4]))(this, 1);
    return 0;
}

// ---- PB::PB @ 0x00a17100 ------------------------------------------------
PB* PB::ctor(void* arg)
{
    float v = g_pbDefault;
    m4 = 0;
    mModify = 0;
    mRefCount = 0;
    vtbl0 = &pbVtbl;
    mValue = v;
    mbDirty = true;
    mpConfig = arg;
    return this;
}

// ---- PB::Destroy @ 0x00a17130 -------------------------------------------
void* PB::Destroy(u8 flags)
{
    vtbl0 = &pbBaseVtbl;
    if (flags & 1) {
        vtbl0 = g_freeList_6d948;
        g_freeList_6d948 = this;
    }
    return this;
}

// ---------------------------------------------------------------------------
// Response-curve primitive (vtable 0x14522fc)
// ---------------------------------------------------------------------------
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

extern "C" char prVtbl0;      // 0x014522fc
extern "C" char prVtbl1;      // 0x014522f8
extern "C" char prBaseVtbl0;  // 0x013eb938
extern "C" char prBaseVtbl1;  // 0x013ef094
extern "C" float g_prDefault;      // 0x01552c48
extern "C" void* g_prDefaultData;

// ---- PResp::GetDirty @ 0x00a17160 ---------------------------------------
bool PResp::GetDirty(int)
{
    return mbDirty;
}

// ---- PResp::SetEnabled @ 0x00a17170 -------------------------------------
void PResp::SetEnabled(bool b)
{
    if (b) {
        SystemAT* s = GetSystemAT();
        ((void (__thiscall*)(void*, void*))((*(void***)s)[0x19c / 4]))(s, this);
        mb384 = true;
        return;
    }
    if (mb384) {
        SystemAT* s = GetSystemAT();
        ((void (__thiscall*)(void*, void*))((*(void***)s)[0x1a0 / 4]))(s, this);
        mb384 = false;
    }
}

// ---- PResp::RecomputeValue @ 0x00a17250 ---------------------------------
bool PResp::RecomputeValue()
{
    IPrimitive* p = (IPrimitive*)mpPrimitive;
    if (p != 0) {
        float v = (float)((float (__thiscall*)(void*))((*(void***)p)[0x1c / 4]))(p);
        mValue = mCurve.GetOutputValue(v);
    }
    return true;
}

// ---- PResp::Reconfigure @ 0x00a17280 ------------------------------------
bool PResp::Reconfigure()
{
    ((void (__thiscall*)(void*, int))((*(void***)this)[0x2c / 4]))(this, 0);
    IPrimitive* p = (IPrimitive*)mpPrimitive;
    if (p != 0) {
        int a = ((int (__thiscall*)(void*))((*(void***)this)[0x30 / 4]))(this);
        int b = ((int (__thiscall*)(void*))((*(void***)p)[0x30 / 4]))(p);
        if (b == a)
            ((void (__thiscall*)(void*))((*(void***)mpPrimitive)[0x14 / 4]))(mpPrimitive);
        IPrimitive* q = (IPrimitive*)mpPrimitive;
        if (q != 0) {
            mpPrimitive = 0;
            q->v04();
        }
    }
    return true;
}

// ---- PResp::SetModificationSource @ 0x00a172e0 --------------------------
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

// ---- PResp::Destroy @ 0x00a17360 ----------------------------------------
// @ 0x00a17360
void PResp::Destroy()
{
    vtbl0 = &prVtbl0;
    vtbl1 = &prVtbl1;
    IPrimitive* p = (IPrimitive*)mpPrimitive;
    if (p != 0)
        p->v04();
    void* buf = *(void**)((char*)this + 0xc);
    if (buf != 0 && buf != *(void**)((char*)this + 0x1c))
        op_delete(buf);
    vtbl1 = &prBaseVtbl1;
    vtbl0 = &prBaseVtbl0;
}

// ---------------------------------------------------------------------------
// EA::Audio::ResourceConfiguration property getters
// ---------------------------------------------------------------------------
struct Variant {
    union {
        u32   u;
        void* p;
        float f;
        char  bytes[0x10];
    };
    u16 mFlags;    // +0x10
    u16 mTypeId;   // +0x12
};

struct Key { u32 a, b, c; };

typedef bool (__thiscall* GetPropertyFn)(void*, u32, Variant const*&);

struct RC {
    void* vtbl;   // +0x00 (IConfiguration)

    bool GetPropertyAsKey(u32 key, Key* out);                        // 00a174d0
    bool GetPropertyAsKeyInstance(u32 key, u32* out);                // 00a17520
    bool GetPropertyAsFloatArray(u32 key, u32* count, const void** arr);  // 00a17560
    bool GetPropertyAsUint32Array(u32 key, u32* count, const void** arr); // 00a175c0
    bool GetPropertyAsKeyArray(u32 key, u32* count, const void** arr);    // 00a17620

    bool GetProperty(u32 key, Variant const*& v)
    {
        GetPropertyFn f = *(GetPropertyFn*)((char*)(*(void**)this) + 0x20);
        return f(this, key, v);
    }
};

// ---- ResourceConfiguration::GetPropertyAsKey @ 0x00a174d0 ---------------
bool RC::GetPropertyAsKey(u32 key, Key* out)
{
    Variant const* v;
    if (GetProperty(key, v) && v->mTypeId == 0x20) {
        const void* src = (v->mFlags & 0x30) ? v->p : (const void*)v;
        *out = *(const Key*)src;
        return true;
    }
    return false;
}

// ---- ResourceConfiguration::GetPropertyAsKeyInstance @ 0x00a17520 ------
bool RC::GetPropertyAsKeyInstance(u32 key, u32* out)
{
    Variant const* v;
    if (GetProperty(key, v) && v->mTypeId == 0x20) {
        const void* src = (v->mFlags & 0x30) ? v->p : (const void*)v;
        u32 value = *(const u32*)src;
        *out = value;
        return true;
    }
    return false;
}

// ---- ResourceConfiguration::GetPropertyAsFloatArray @ 0x00a17560 -------
bool RC::GetPropertyAsFloatArray(u32 key, u32* count, const void** arr)
{
    Variant const* v;
    if (GetProperty(key, v) && v->mTypeId == 0x0d && (v->mFlags & 0x30)) {
        *count = *(const u32*)((const char*)v + 8);
        *arr = (v->mFlags & 0x30) ? v->p : (v->mTypeId ? (const void*)v : 0);
        return true;
    }
    return false;
}

// ---- ResourceConfiguration::GetPropertyAsUint32Array @ 0x00a175c0 ------
bool RC::GetPropertyAsUint32Array(u32 key, u32* count, const void** arr)
{
    Variant const* v;
    if (GetProperty(key, v) && v->mTypeId == 0x0a && (v->mFlags & 0x30)) {
        *count = *(const u32*)((const char*)v + 8);
        *arr = (v->mFlags & 0x30) ? v->p : (v->mTypeId ? (const void*)v : 0);
        return true;
    }
    return false;
}

// ---- ResourceConfiguration::GetPropertyAsKeyArray @ 0x00a17620 ---------
bool RC::GetPropertyAsKeyArray(u32 key, u32* count, const void** arr)
{
    Variant const* v;
    if (GetProperty(key, v) && v->mTypeId == 0x20 && (v->mFlags & 0x30)) {
        *count = *(const u32*)((const char*)v + 8);
        *arr = (v->mFlags & 0x30) ? v->p : (v->mTypeId ? (const void*)v : 0);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// Misc EA::Audio / Eapd helpers
// ---------------------------------------------------------------------------
// Eapd::sys_gui scalar deleting destructor, written out as a member so it has a name:
// the member dtor runs under EH state 0, then the inlined base dtor resets the vptr.
extern "C" char g_guiBaseVtbl;                    // 0x014bc0fc
struct GuiMember { ~GuiMember(); };               // 0x00c2e4e0
struct GuiBase {
    void* vtbl;
    u8    pad[0x20];
    ~GuiBase() { vtbl = &g_guiBaseVtbl; }
};
struct SysGui : GuiBase {
    GuiMember mMember;                            // +0x24
    __forceinline ~SysGui() {}
    void* ScalarDeletingDtor(unsigned flags);
};

// @ 0x00a168c0
void* SysGui::ScalarDeletingDtor(unsigned flags)
{
    this->~SysGui();
    if (flags & 1)
        op_delete(this);
    return this;
}

struct VuOwner {
    u8  pad0[0x60];
    TimerManager mTimers;        // +0x60
    u8  pad1[0xc0 - 0x61];
    float mGain;                 // +0xc0
};

struct VuMeter {
    u8      pad0[4];
    VuOwner* mOwner;             // +4
    u8      pad1[0x1c];
    u8      mTimerKey[0x18];     // +0x24
    int     m3c;
    int     m40;
    u8      pad2[4];
    float   mSlots[0x13 * 2];    // +0x48, stride 8
    float   mA[6];               // +0xe0
    u8      pad4[0x110 - 0xf8];
    float   mB[6];               // +0x110
    u8      pad5[0x158 - 0x128];
    bool    mb158;
    bool    mb159;
    void Reset();                // 00a161c0
};

// @ 0x00a16920
bool VuMeter_Init(VuMeter* p)
{
    FUN_00a16870(p, 0x48);
    p->mb159 = false;
    p->m3c = (int)(p->mOwner->mGain * 0.01f);
    float* slots = &p->mSlots[0];
    for (int i = 0x13; i != 0; --i) {
        slots[0] = 0.0f;
        slots += 2;
    }
    p->mb158 = false;
    p->Reset();
    p->m40 = 0;
    p->mA[0] = 0.0f; p->mB[0] = 0.0f;
    p->mA[1] = 0.0f; p->mB[1] = 0.0f;
    p->mA[2] = 0.0f; p->mB[2] = 0.0f;
    p->mA[3] = 0.0f; p->mB[3] = 0.0f;
    p->mA[4] = 0.0f; p->mB[4] = 0.0f;
    p->mA[5] = 0.0f; p->mB[5] = 0.0f;
    if (p->mOwner->mTimers.AddTimer(p->mTimerKey, (void*)0xa16290, p, "VuMeter", 1, 1))
        return false;
    p->mb159 = true;
    return true;
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

// @ 0x00a17090
void* FUN_00a17090(u32 size)
{
    if (size == 0x1c) {
        do {
            void* p = g_freeList_6d948;
            if (p != 0) {
                g_freeList_6d948 = *(void**)p;
                return p;
            }
        } while (((FixedAllocatorBase*)&g_alloc_166d938)->AddCore(0, 0));
        return 0;
    }
    return FUN_006abeb0(size);
}

// ---------------------------------------------------------------------------
// PrimitiveAggregate::PrimitiveAggregate @ 0x00a16d00 (real class layout)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// PResp::PResp @ 0x00a173f0 (real class layout with EH unwind states)
// ---------------------------------------------------------------------------
extern "C" char g_prData2[];       // 0x01452330

struct RespCurve {
    RespCurve();                                  // 0xa1aa50
    ~RespCurve();
    void SetResponseCurveData(const void*, int);  // 0xa1a590
    u8   mData[0x364];
};

struct PR_Prim { PR_Prim() {} virtual ~PR_Prim() {} virtual int p1() { return 0; } };
struct PR_RC   { PR_RC() { mRefCount = 0; } virtual ~PR_RC() {} int mRefCount; };

struct PR_Ref { void* p; PR_Ref() : p(0) {} ~PR_Ref() { if (p) ((IPrimitive*)p)->v08(); } };

struct PRespC : PR_Prim, PR_RC {
    RespCurve mCurve;         // +0xc
    PR_Ref mpPrimitive;       // +0x370
    bool  mbDirty;            // +0x374
    u8    pad375[3];
    int   mModify;            // +0x378
    float mValue;             // +0x37c
    u8    pad380[4];
    bool  mb384;              // +0x384
    u8    pad385[3];
    int   m388;               // +0x388

    PRespC(int arg);
};

// @ 0x00a173f0
PRespC::PRespC(int arg)
{
    float d = g_prDefault;
    mbDirty = true;
    mModify = 0;
    mValue = d;
    mb384 = false;
    m388 = arg;
    mCurve.SetResponseCurveData(g_prData2, 2);
}
// --- equivalence checker address annotations
    void AddCore(...); // 0x00926650

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
