// Slice s00a36d60 - SP::Audio / EA::Audio emitters, Swarm sound effect, audio primitives.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// MSVC interlocked intrinsics (declared manually; no <intrin.h> in this env).
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedDecrement(volatile long*);

// ---------------------------------------------------------------------------
// External callees (addresses are the original's; targets are masked relocs)
// ---------------------------------------------------------------------------
struct AudioSystem;    // EA::Audio::System (vtable)
struct EapdSystem;     // EA::Audio::Eapd::ISystem
struct SASystem;       // SP::Audio::cSystem

AudioSystem* GetSystemAT();                 // 0x00a206f0
EapdSystem*  EapdGetSingletonPtr();         // 0x00a67c60
SASystem*    SPGetSystem();                 // 0x00a421f0
void __cdecl operator_delete(void*);        // 0x00f47380
void* __cdecl operator_new_swarm(u32, const char*, int, int, int, int); // 0x00f473a0
void FUN_00572020(void*, int);              // 0x00572020
void FUN_009fbc50(void* p, float x, float y, float z); // 0x009fbc50

// EASTL-style small vector of refcounted elements (inline buffer at +0x18).
struct IPrimVec {
    void* mpBegin;   // +0x00
    void* mpEnd;     // +0x04
    void* mpCapacity;// +0x08
    void* m0c;       // +0x0c
    void* m10;       // +0x10
    void* m14;       // +0x14
    u8    mBuf[0x28];// +0x18
    void  push_back(const void* v);          // 0x00a36ce0
    void  erase(void* first, void* last);    // 0x00e25bd0
};

// ResponseCurve (EA::Audio) - 0x364 bytes.
struct ResponseCurve {
    u8   mData[0x364];
    void  Ctor();                                   // 0x00a1aa50
    void  SetResponseCurveData(const void*, int);   // 0x00a1a590
    float GetOutputValue(float in);                 // 0x00a1a110
};

// Refcounted primitive interface (matches the aggregate/element vtable shape).
struct IPrimitive {
    virtual void  v00();                 // +0x00 AddRef
    virtual int   v04();                 // +0x04 Release
    virtual void  v08();
    virtual void* v0c(u32);
    virtual bool  v10();
    virtual void  v14();
    virtual void  v18();
    virtual float v1c();
    virtual bool  v20(int);
    virtual void  v24(int);
    virtual void  v28(float value, int mod);
    virtual void  v2c(int);
    virtual int   v30();
    virtual void  v34();
    virtual void  v38();
};

// ---------------------------------------------------------------------------
// Group A: a PrimitiveAggregate-derived game class (PAggX) and a
// PrimitiveResponse-derived game class (PRespX).  Real PDB names unknown;
// layouts match EA::Audio::PrimitiveAggregate / PrimitiveResponse.
// ---------------------------------------------------------------------------
extern "C" char  g_aggX_base0;    // 0x01453140
extern "C" char  g_aggX_base1;    // 0x01453124
extern "C" char  g_aggX_base2;    // 0x01453120
extern "C" char  g_pa_agg_vtbl;   // 0x014426a0  (PA_Agg base)
extern "C" char  g_gme_refcount;  // 0x013ef094  (GmeRefCount base)
extern "C" char  g_gme_editor;    // 0x013eb938  (Editor::cEditorResource base)
extern "C" float g_aggX_default;  // 0x01553084
extern "C" float g_prX_default;   // 0x015530bc
extern "C" char  g_prX_data[];    // 0x01452330
extern "C" char  g_prX_base0;     // 0x014531cc
extern "C" char  g_prX_base1;     // 0x014531c8

struct PAggX {
    void*    vtbl0;      // +0x00
    void*    vtbl1;      // +0x04
    void*    vtbl2;      // +0x08
    int      mRefCount;  // +0x0c
    IPrimVec mVec;       // +0x10  (0x40 bytes -> ends at +0x50)
    bool  mbDirty;    // +0x50
    u8    pad51[3];
    u32   mMethod;    // +0x54
    int   mModify;    // +0x58
    u32   m5c;        // +0x5c
    float mValue;     // +0x60
    bool  mb64;       // +0x64
    u8    pad65[3];
    int   m68;        // +0x68

    PAggX(int arg);
    bool  UpdatePrimitives();       // 0xa36e10
};

// RAII temporary holding one refcounted pointer (AddRef on construction, Release on destruction).
struct IPrimAutoRef {
    IPrimitive* mpObject;
    IPrimAutoRef(IPrimitive* p) : mpObject(p) { if (p) p->v00(); }
    ~IPrimAutoRef() { if (mpObject) mpObject->v04(); }
};

// View of the PAggX object through its second base subobject (+4).
struct AggSub {
    void*    vtbl;       // +0x00 (object+0x04)
    u8       pad1[8];
    IPrimVec mVec;       // +0x0c (object+0x10) 0x40 bytes -> +0x4c
    bool  mbDirty;    // +0x4c (object+0x50)
    u8    pad3[7];
    int   mModify;    // +0x54 (object+0x58)

    void  PushBack(IPrimitive* p);  // 0xa36e80
};

struct PRespX {
    void*         vtbl0;      // +0x00
    void*         vtbl1;      // +0x04
    int           mRefCount;  // +0x08
    ResponseCurve mCurve;     // +0x0c
    IPrimitive*   mpPrimitive;// +0x370
    bool          mbDirty;    // +0x374
    u8            pad375[3];
    int           mModify;    // +0x378
    float         mValue;     // +0x37c
    u8            pad380[4];
    bool          mb384;      // +0x384
    u8            pad385[3];
    int           m388;       // +0x388

    PRespX(int arg);
    bool  Reconfigure();                              // 0xa36f70
    void  OnConfigurePrimitive(void* p);              // 0xa36fd0
    void  SetModificationSource(float value, int mod); // 0xa37000
    void  SetPrimitive(IPrimitive* p);                // 0xa37080
    ~PRespX();                                        // 0xa370d0
};

// ---- PAggX::PAggX @ 0x00a36d60 -------------------------------------------
PAggX::PAggX(int arg)
{
    vtbl1 = &g_pa_agg_vtbl;
    vtbl2 = &g_gme_refcount;
    mRefCount = 0;
    vtbl0 = &g_aggX_base0;
    vtbl1 = &g_aggX_base1;
    vtbl2 = &g_aggX_base2;
    void** buf = (void**)((char*)&mVec + 0x18);
    mVec.m10 = buf;
    mVec.mpEnd = buf;
    mVec.mpBegin = buf;
    mVec.mpCapacity = buf + 0xa;         // +0x28 bytes
    mbDirty = true;
    mMethod = 0xd256aaba;
    mModify = 0;
    m5c = 0;
    mValue = g_aggX_default;
    mb64 = false;
    m68 = arg;
    mVec.erase(mVec.mpBegin, mVec.mpEnd);
}

// ---- PAggX::UpdatePrimitives @ 0x00a36e10 --------------------------------
bool PAggX::UpdatePrimitives()
{
    void** end = (void**)mVec.mpEnd;
    for (void** it = (void**)mVec.mpBegin; it != end; ++it) {
        IPrimitive* e = (IPrimitive*)*it;
        int a = ((int (__thiscall*)(void*))((*(void***)e)[0x30 / 4]))(e);
        int b = ((int (__thiscall*)(void*))((*(void***)this)[0x30 / 4]))(this);
        if (a == b)
            e->v14();
    }
    mVec.erase(mVec.mpBegin, mVec.mpEnd);
    return true;
}

// ---- AggSub::PushBack @ 0x00a36e80 ---------------------------------------
void AggSub::PushBack(IPrimitive* p)
{
    if (p)
        p->v00();
    mVec.push_back((const void*)&p);
    if (p)
        p->v04();
    --mModify;
    mbDirty = true;
}

// ---- PRespX::Reconfigure @ 0x00a36f70 ------------------------------------
bool PRespX::Reconfigure()
{
    if (mpPrimitive) {
        int a = ((int (__thiscall*)(void*))((*(void***)mpPrimitive)[0x30 / 4]))(mpPrimitive);
        int b = ((int (__thiscall*)(void*))((*(void***)this)[0x30 / 4]))(this);
        if (a == b)
            mpPrimitive->v14();
        IPrimitive* p = mpPrimitive;
        if (p) {
            mpPrimitive = 0;
            p->v04();
        }
    }
    return true;
}

// ---- PRespX::OnConfigurePrimitive @ 0x00a36fd0 ---------------------------
void PRespX::OnConfigurePrimitive(void* p)
{
    if (mpPrimitive)
        mpPrimitive->v24((int)p);
    if (mModify == (int)p)
        mbDirty = false;
}

// ---- PRespX::SetModificationSource @ 0x00a37000 --------------------------
void PRespX::SetModificationSource(float value, int mod)
{
    if (mModify == mod)
        return;
    mModify = mod;
    if (!mpPrimitive)
        return;
    mpPrimitive->v28(value, mod);
    if (!mbDirty && !mpPrimitive->v20(0))
        return;
    float f = mpPrimitive->v1c();
    mValue = mCurve.GetOutputValue(f);
    --mModify;
    mbDirty = true;
}

// ---- PRespX::SetPrimitive @ 0x00a37080 -----------------------------------
void PRespX::SetPrimitive(IPrimitive* p)
{
    IPrimitive* old = mpPrimitive;
    if (p != old) {
        if (p)
            p->v00();
        mpPrimitive = p;
        if (old)
            old->v04();
    }
    --mModify;
    mbDirty = true;
}

// ---- PRespX::~PRespX @ 0x00a370d0 ----------------------------------------
PRespX::~PRespX()
{
    vtbl0 = &g_prX_base0;
    vtbl1 = &g_prX_base1;
    if (mpPrimitive)
        mpPrimitive->v04();
    void* buf = *(void**)((char*)this + 0xc);
    if (buf && buf != *(void**)((char*)this + 0x1c))
        operator_delete(buf);
    vtbl1 = &g_gme_refcount;
    vtbl0 = &g_gme_editor;
}

// ---- PRespX::PRespX @ 0x00a37160 -----------------------------------------
PRespX::PRespX(int arg)
{
    vtbl1 = &g_gme_refcount;
    mRefCount = 0;
    mCurve.Ctor();
    vtbl0 = &g_prX_base0;
    vtbl1 = &g_prX_base1;
    mpPrimitive = 0;
    mbDirty = true;
    mModify = 0;
    mValue = g_prX_default;
    mb384 = false;
    m388 = arg;
    mCurve.SetResponseCurveData(g_prX_data, 2);
}

// ---------------------------------------------------------------------------
// SP::Audio emitter helpers
// ---------------------------------------------------------------------------
// ---- SetSoundGain @ 0x00a37240 -------------------------------------------
void SetSoundGain(void* handle, float gain)
{
    AudioSystem* s = GetSystemAT();
    if (!s)
        return;
    ((void (__thiscall*)(void*, u32))((*(void***)s)[0x38 / 4]))(s, 0x347536f);
    ((void (__thiscall*)(void*, u32, void*))((*(void***)s)[0x40 / 4]))(s, 0x3475385, handle);
    ((void (__thiscall*)(void*, u32, float))((*(void***)s)[0x3c / 4]))(s, 0x34753a4, gain);
    ((void (__thiscall*)(void*))((*(void***)s)[0x58 / 4]))(s);
}

// ---- PauseSound @ 0x00a37290 ---------------------------------------------
void PauseSound(void* a, int b)
{
    AudioSystem* s = GetSystemAT();
    if (!s)
        return;
    ((void (__thiscall*)(void*, u32))((*(void***)s)[0x38 / 4]))(s, 0x42c8c77);
    ((void (__thiscall*)(void*, u32, void*))((*(void***)s)[0x40 / 4]))(s, 0x3475385, a);
    ((void (__thiscall*)(void*, u32, int))((*(void***)s)[0x40 / 4]))(s, 0x42c8c8b, b);
    ((void (__thiscall*)(void*))((*(void***)s)[0x58 / 4]))(s);
}

// ---------------------------------------------------------------------------
// EA::Swarm::cSoundEffect-like component (size 0x34)
// ---------------------------------------------------------------------------
extern "C" char  g_se_vtbl0;   // 0x01453254
extern "C" char  g_se_vtbl1;   // 0x014599e8
extern "C" float g_se_one;     // 0x01485720

struct SoundEffect {
    void* vtbl0;      // +0x00
    void* vtbl1;      // +0x04
    int   m8;         // +0x08
    void* m0c;        // +0x0c
    float m10;        // +0x10
    float m14;        // +0x14
    float m18;        // +0x18
    bool  b1c;        // +0x1c
    bool  b1d;        // +0x1d
    bool  b1e;        // +0x1e
    bool  b1f;        // +0x1f
    void* m20;        // +0x20
    float m24;        // +0x24
    float m28;        // +0x28
    float m2c;        // +0x2c
    float m30;        // +0x30

    void Activate(int a);                       // 0xa372e0
    bool SetFloatParams(int which, float* val, int x); // 0xa37320
    void Pause(bool p);                         // 0xa37400
    void Stop(int a);                           // 0xa37420
    void ApplyEffect(float dt, int x, void* ctx); // 0xa37480
    void SetLocation(void* t, void* loc);       // 0xa376f0
};

// ---- SoundEffect::Activate @ 0x00a372e0 ----------------------------------
void SoundEffect::Activate(int)
{
    if (!b1f) {
        m24 = 0.0f;
        m28 = 0.0f;
        m30 = g_se_one;
        b1e = true;
        b1f = true;
    }
}

// ---- SoundEffect::SetFloatParams @ 0x00a37320 ----------------------------
bool SoundEffect::SetFloatParams(int which, float* val, int)
{
    if (which == 1) {
        if (!m20)
            return true;
        AudioSystem* s = GetSystemAT();
        if (!s)
            return true;
        ((void (__thiscall*)(void*, u32))((*(void***)s)[0x38 / 4]))(s, 0x3475376);
        ((void (__thiscall*)(void*, u32, void*))((*(void***)s)[0x40 / 4]))(s, 0x3475385, m20);
        ((void (__thiscall*)(void*, u32, int))((*(void***)s)[0x40 / 4]))(s, 0x34753a7, 0x70e47545);
        ((void (__thiscall*)(void*, u32, float))((*(void***)s)[0x3c / 4]))(s, 0x34753aa, *val);
        ((void (__thiscall*)(void*))((*(void***)s)[0x58 / 4]))(s);
        return true;
    }
    if (which == 0xf) {
        m2c = *val;
        return true;
    }
    if (which != 0x15)
        return false;
    if (!m20)
        return true;
    AudioSystem* s = GetSystemAT();
    if (!s)
        return true;
    ((void (__thiscall*)(void*, u32))((*(void***)s)[0x38 / 4]))(s, 0x3475376);
    ((void (__thiscall*)(void*, u32, void*))((*(void***)s)[0x40 / 4]))(s, 0x3475385, m20);
    ((void (__thiscall*)(void*, u32, int))((*(void***)s)[0x40 / 4]))(s, 0x34753a7, 0xc57f4567);
    ((void (__thiscall*)(void*, u32, float))((*(void***)s)[0x3c / 4]))(s, 0x34753aa, *val);
    ((void (__thiscall*)(void*))((*(void***)s)[0x58 / 4]))(s);
    return true;
}

// ---- SoundEffect::Pause @ 0x00a37400 -------------------------------------
void SoundEffect::Pause(bool p)
{
    if (m20)
        PauseSound(m20, p == 0);
}

// ---- SoundEffect::Stop @ 0x00a37420 --------------------------------------
void SoundEffect::Stop(int a)
{
    if (b1f) {
        b1f = false;
        if (((*(u32*)((char*)m0c + 8) >> 3) & 1) && m20)
            FUN_00572020(m20, a == 1);
        void* h = m20;
        AudioSystem* s = GetSystemAT();
        if (s)
            ((void (__thiscall*)(void*, void*))((*(void***)s)[0x2c / 4]))(s, h);
        m20 = 0;
    }
}

// ---- SoundEffect::ApplyEffect @ 0x00a37480 -------------------------------
void SoundEffect::ApplyEffect(float dt, int, void* ctx)
{
    m24 = m24 + dt;
    AudioSystem* s = GetSystemAT();
    if (b1e && b1c) {
        b1e = false;
        if (!s)
            return;
        void* d = m0c;
        if ((*(u32*)((char*)d + 8) >> 4) & 1)
            m20 = *(void**)((char*)d + 0x18);
        else
            m20 = ((void* (__thiscall*)(void*))((*(void***)s)[0x24 / 4]))(s);
        ((void (__thiscall*)(void*, u32))((*(void***)s)[0x38 / 4]))(s, 0x3475365);
        ((void (__thiscall*)(void*, u32, void*))((*(void***)s)[0x40 / 4]))(s, 0x3475381, *(void**)((char*)d + 0x10));
        ((void (__thiscall*)(void*, u32, void*))((*(void***)s)[0x40 / 4]))(s, 0x3475385, m20);
        ((void (__thiscall*)(void*, u32, int))((*(void***)s)[0x40 / 4]))(s, 0x3475389, *(u8*)((char*)d + 8) & 1);
        ((void (__thiscall*)(void*, u32, u32))((*(void***)s)[0x40 / 4]))(s, 0x347538c, (*(u32*)((char*)d + 8) >> 1) & 1);
        ((void (__thiscall*)(void*, u32, float))((*(void***)s)[0x3c / 4]))(s, 0x3475391, m10);
        ((void (__thiscall*)(void*, u32, float))((*(void***)s)[0x3c / 4]))(s, 0x3475395, m14);
        ((void (__thiscall*)(void*, u32, float))((*(void***)s)[0x3c / 4]))(s, 0x3475398, m18);
        ((void (__thiscall*)(void*))((*(void***)s)[0x58 / 4]))(s);
        return;
    }
    if (!b1f)
        return;
    if (b1d && *(float*)((char*)m0c + 0x1c) > 0.0f && m24 > m28) {
        m28 = *(float*)((char*)m0c + 0x1c) + m24;
        FUN_009fbc50(m20, m10, m14, m18);
        b1d = false;
    }
    if (m30 != m2c) {
        float v = m2c;
        m30 = v;
        SetSoundGain(m20, v);
    }
    ((int*)ctx)[0xb] += 1;
    if (s) {
        if (!((bool (__thiscall*)(void*, void*))((*(void***)s)[0x28 / 4]))(s, m20)) {
            ((void (__thiscall*)(void*, int))((*(void***)this)[0xc / 4]))(this, 1);
        }
    }
    if (*(float*)((char*)m0c + 0x20) > 0.0f && *(float*)((char*)m0c + 0x20) < m24) {
        ((void (__thiscall*)(void*, int))((*(void***)this)[0xc / 4]))(this, 1);
    }
}

// ---- CreateSoundEffect (operator new) @ 0x00a37680 -----------------------
SoundEffect* CreateSoundEffect(void* arg)
{
    SoundEffect* p = (SoundEffect*)operator_new_swarm(0x34, "Swarm", 0, 0, 0, 0);
    if (p) {
        p->m8 = 0;
        p->vtbl1 = &g_gme_refcount;
        p->m24 = 0.0f;
        p->m28 = 0.0f;
        float one = g_se_one;
        p->b1c = false;
        p->b1e = false;
        p->b1f = false;
        p->m20 = 0;
        p->vtbl0 = &g_se_vtbl0;
        p->vtbl1 = &g_se_vtbl1;
        p->m0c = arg;
        p->b1d = true;
        p->m2c = one;
        p->m30 = one;
        return p;
    }
    return 0;
}

// ---- SoundEffect::SetLocation @ 0x00a376f0 -------------------------------
struct Matrix3 { float f0,f1,f2,f3,f4,f5,f6,f7,f8; void Assign(const void*); }; // 0x0041cb40
struct cTransform {                                   // 0x38 bytes
    u16    w0;                                        // +0x00
    u16    w2;                                        // +0x02
    float  x;                                         // +0x04
    float  y;                                         // +0x08
    float  z;                                         // +0x0c
    float  w10;                                       // +0x10
    Matrix3 mat;                                      // +0x14
    void PreTransformBy(const void*);                 // 0x00537f40
};

void SoundEffect::SetLocation(void* t, void* loc)
{
    u8* src = (u8*)loc;
    cTransform m;
    m.w0  = *(u16*)(src + 0);
    m.x   = *(float*)(src + 4);
    m.y   = *(float*)(src + 8);
    m.z   = *(float*)(src + 0xc);
    m.w10 = *(float*)(src + 0x10);
    m.w2  = *(u16*)(src + 2);
    m.mat.Assign(src + 0x14);
    m.PreTransformBy(t);
    if (m.x != m10 || m.y != m14 || m.z != m18)
        b1d = true;
    m10 = m.x;
    m14 = m.y;
    m18 = m.z;
    b1c = true;
}

// ---------------------------------------------------------------------------
// SP::Audio::cEmitterEAPD  (complete object size 0x38)
//   +0 ITickable vtable, +4 IEmitter vtable, +8 refcount vtable, +0xc refcount
//   +0x10 Key (0xc), +0x1c mhInstance, +0x20 mpPatchResource, +0x24 mId,
//   +0x28 mGroupId, +0x2c mFlags, +0x30 mConfiguration, +0x34 mbPaused
// ---------------------------------------------------------------------------
extern "C" char  g_eapdTick_vtbl;   // 0x01453344
extern "C" char  g_eapdEmit_vtbl;   // 0x014532f8
extern "C" char  g_eapdRC_vtbl;     // 0x014532f0
extern "C" char  g_sound_vtbl;      // 0x0144934c
extern "C" char  g_eapdSound_vtbl1; // 0x01453e60
extern "C" u32   g_eapd_alloc;      // 0x0166e4a0
extern "C" char  g_eapd_allocCore;  // 0x0166e490

struct cEAPDVoiceMgr {
    void UnregisterInstanceGroup(u32 id);   // 0x00a46150
};

struct cEmitterEAPD {
    void* vtbl0;        // +0x00 ITickable
    void* vtbl1;        // +0x04 IEmitter
    void* vtbl2;        // +0x08 refcount
    int   mRefCount;    // +0x0c
    u32   mKey[3];      // +0x10
    u32   mhInstance;   // +0x1c
    void* mpPatch;      // +0x20
    u32   mId;          // +0x24
    u32   mGroupId;     // +0x28
    u32   mFlags;       // +0x2c
    u32   mConfig;      // +0x30
    u8    mPaused;      // +0x34

    cEmitterEAPD();                     // 0xa37b10
    u32  SetPropertyInternal(int a, float f); // 0xa379d0
    bool GetProperty(int key, float* out); // 0xa37930
    void Tick(int a, int b);            // 0xa37860
    ~cEmitterEAPD();                    // 0xa37c40
    bool Load();                        // 0xa37cc0
};

// View through the IEmitter subobject (object+4).
struct EmitterSub {
    void* vtbl;       // +0x00 (object+0x04)
    void* vtblRC;     // +0x04 (object+0x08)
    u8    pad08[0x10];// +0x08..+0x17
    u32   mKey18;     // +0x18 (object+0x1c) mhInstance
    void* mpPatch;    // +0x1c (object+0x20)
    u32   mId;        // +0x20 (object+0x24)
    u32   mGroupId;   // +0x24 (object+0x28)
    u32   mFlags;     // +0x28 (object+0x2c)
    u32   mConfig;    // +0x2c (object+0x30)
    u8    mPaused;    // +0x30 (object+0x34)

    cEmitterEAPD* Outer() { return (cEmitterEAPD*)((char*)this - 4); }
    bool  Start(int a, int b);        // 0xa377b0
    bool  Stop();                     // 0xa37820
    bool  Pause(bool p);              // 0xa378e0
    bool  Shutdown();                 // 0xa37b90
    bool  SetProperty(int key, float value, int extra); // 0xa37960
    bool  SetPropertyEx(int a, int b, int c);           // 0xa37a10
};

// ---- cEmitterEAPD::cEmitterEAPD @ 0x00a37b10 -----------------------------
cEmitterEAPD::cEmitterEAPD()
{
    vtbl0 = &g_sound_vtbl;
    vtbl1 = &g_eapdSound_vtbl1;
    vtbl2 = &g_gme_refcount;
    _InterlockedExchange((volatile long*)&mRefCount, 0);
    vtbl0 = &g_eapdTick_vtbl;
    vtbl1 = &g_eapdEmit_vtbl;
    vtbl2 = &g_eapdRC_vtbl;
    mKey[0] = 0; mKey[1] = 0; mKey[2] = 0;
    mhInstance = 0;
    mpPatch = 0;
    mId = 0;
    mGroupId = 0;
    mFlags = 0;
    mConfig = 0;
    mPaused = 0;
}

// ---- EmitterSub::Start @ 0x00a377b0 --------------------------------------
bool EmitterSub::Start(int, int)
{
    if (!(mFlags & 0x40)) {
        EapdSystem* e = EapdGetSingletonPtr();
        if (e) {
            ((void (__thiscall*)(void*, u32, u32, float))((*(void***)e)[0x38 / 4]))(
                e, mKey18, 0x411cb4f7, 1.0f);
            ((void (__thiscall*)(void*, u32, int))((*(void***)e)[0x30 / 4]))(
                e, mKey18, mPaused);
        }
        AudioSystem* s = GetSystemAT();
        if (s) {
            cEmitterEAPD* o = Outer();
            ((void (__thiscall*)(void*, void*))((*(void***)s)[0x70 / 4]))(s, o);
            o->mFlags |= 2;
        }
        cEmitterEAPD* o2 = Outer();
        ((void (__thiscall*)(void*))((*(void***)o2)[0 / 4]))(o2);
        o2->mFlags |= 0x40;
    }
    return true;
}

// ---- EmitterSub::Stop @ 0x00a37820 ---------------------------------------
bool EmitterSub::Stop()
{
    if (!(mFlags & 0x40))
        return false;
    EapdSystem* e = EapdGetSingletonPtr();
    if (e) {
        ((void (__thiscall*)(void*, u32, u32, float))((*(void***)e)[0x38 / 4]))(
            e, mKey18, 0x411cb4f7, 0.0f);
    }
    *(volatile u32*)&mFlags |= 0x80;
    *(volatile u32*)&mFlags &= ~0x40;
    return true;
}

// ---- EmitterSub::Pause @ 0x00a378e0 --------------------------------------
bool EmitterSub::Pause(bool p)
{
    bool ok = false;
    mPaused = p;
    if ((mFlags & 0x40) != 0) {
        EapdSystem* e = EapdGetSingletonPtr();
        if (e != 0) {
            ok = ((bool (__thiscall*)(void*, u32, u32))((*(void***)e)[0x30 / 4]))(
                e, mKey18, mPaused);
        }
    }
    return ok;
}

// ---- cEmitterEAPD::SetPropertyInternal @ 0x00a379d0 ----------------------
u32 cEmitterEAPD::SetPropertyInternal(int a, float f)
{
    EapdSystem* e = EapdGetSingletonPtr();
    if (e) {
        if (((bool (__thiscall*)(void*, u32, int, float))((*(void***)e)[0x38 / 4]))(
                e, mhInstance, a, f))
            return 1;
    }
    return 0;
}

// ---- EmitterSub::SetProperty @ 0x00a37960 --------------------------------
bool EmitterSub::SetProperty(int key, float value, int extra)
{
    cEmitterEAPD* o = (cEmitterEAPD*)((char*)this - 4);
    if (((bool (__thiscall*)(void*, int, float))((*(void***)o)[0xc / 4]))(o, key, value))
        return true;
    if (key == 0xf616b72 || key == 0x3593710)
        return false;
    AudioSystem* s = GetSystemAT();
    return ((bool (__thiscall*)(void*, u32, int, float, int))((*(void***)s)[0xac / 4]))(
        s, mGroupId, key, value, extra);
}

// ---- EmitterSub::SetPropertyEx @ 0x00a37a10 ------------------------------
bool EmitterSub::SetPropertyEx(int a, int b, int c)
{
    EapdSystem* e = EapdGetSingletonPtr();
    if (e == 0)
        return true;
    if (!((bool (__thiscall*)(void*, u32, int, int))((*(void***)e)[0x34 / 4]))(
            e, mKey18, a, b)) {
        AudioSystem* s = GetSystemAT();
        ((void (__thiscall*)(void*, u32, int, int, int))((*(void***)s)[0xa8 / 4]))(
            s, mGroupId, a, b, c);
    }
    return true;
}

// ---- cEmitterEAPD::Tick @ 0x00a37860 (this = complete object) ------------
void cEmitterEAPD::Tick(int, int)
{
    u32 f = mFlags;
    if (f & 0x80) {
        if (f & 2) {
            mFlags = f & 0xfffffffd;
            AudioSystem* s = GetSystemAT();
            if (s)
                ((void (__thiscall*)(void*, void*))((*(void***)s)[0x74 / 4]))(s, this);
        }
        ((void (__thiscall*)(void*))((*(void***)this)[4 / 4]))(this);
        return;
    }
    EapdSystem* e = EapdGetSingletonPtr();
    if (e) {
        if (!((bool (__thiscall*)(void*, u32))((*(void***)e)[0x2c / 4]))(e, mhInstance)) {
            AudioSystem* s = GetSystemAT();
            ((void (__thiscall*)(void*, u32, u32, int, int, int))((*(void***)s)[0x128 / 4]))(
                s, 0x3a0fd6e, mId, 0, 0, 0);
            void* sub = (char*)this + 4;
            ((void (__thiscall*)(void*))((*(void***)sub)[0x18 / 4]))(sub);
        }
    }
}

// ---- cEmitterEAPD::GetProperty @ 0x00a37930 ------------------------------
bool cEmitterEAPD::GetProperty(int key, float* out)
{
    if (key != (int)0xc2d1f579)
        return false;
    *out = g_se_one;
    return true;
}

// ---- cEmitterEAPD::Load @ 0x00a37cc0 -------------------------------------
bool cEmitterEAPD::Load()
{
    void* local = 0;
    AudioSystem* s = GetSystemAT();
    if (local) {
        void* t = local;
        local = 0;
        ((void (__thiscall*)(void*))((*(void***)t)[0 / 4]))(t);
    }
    bool ok = ((bool (__thiscall*)(void*, void*, void**))((*(void***)s)[0x18c / 4]))(
        s, &mKey[0], &local);
    if (ok) {
        void* old = mpPatch;
        void* cur = local;
        if (cur != old) {
            if (cur)
                ((void (__thiscall*)(void*))((*(void***)cur)[0 / 4]))(cur);
            mpPatch = cur;
            if (old)
                ((void (__thiscall*)(void*))((*(void***)old)[4 / 4]))(old);
        }
        if (local)
            ((void (__thiscall*)(void*))((*(void***)local)[4 / 4]))(local);
        return true;
    }
    if (local)
        ((void (__thiscall*)(void*))((*(void***)local)[4 / 4]))(local);
    return false;
}

// ---- EmitterSub::Shutdown @ 0x00a37b90 -----------------------------------
bool EmitterSub::Shutdown()
{
    if (mFlags & 1) {
        ((void (__thiscall*)(void*))((*(void***)this)[0x18 / 4]))(this);
        mFlags &= ~1u;
        EapdSystem* e = EapdGetSingletonPtr();
        if (e)
            ((void (__thiscall*)(void*, u32))((*(void***)e)[0x28 / 4]))(e, mKey18);
        SASystem* sys = SPGetSystem();
        if (*(void**)((char*)sys + 0x15bc80))
            ((cEAPDVoiceMgr*)*(void**)((char*)sys + 0x15bc80))->UnregisterInstanceGroup(mKey18);
        ((void (__thiscall*)(void*, u32))((*(void***)sys)[0x124 / 4]))(sys, mGroupId);
        mKey18 = 0;
        mGroupId = 0;
        if (mpPatch) {
            void* p = mpPatch;
            mpPatch = 0;
            ((void (__thiscall*)(void*))((*(void***)p)[4 / 4]))(p);
        }
    }
    return true;
}

// ---- EA::Audio::Sound::Release @ 0x00a37c10 ------------------------------
struct Sound { int Release(); };

int Sound::Release()
{
    char* base = (char*)this + 8;
    volatile long* rc = (volatile long*)(base + 4);
    int n = (int)_InterlockedDecrement(rc);
    if (n == 0) {
        _InterlockedExchange(rc, 1);
        if (base) {
            void** vt = *(void***)base;
            ((void (__thiscall*)(void*, int))vt[0])(base, 1);
        }
        return 0;
    }
    return n;
}

// ---- cEmitterEAPD::~cEmitterEAPD @ 0x00a37c40 ----------------------------
cEmitterEAPD::~cEmitterEAPD()
{
    vtbl0 = &g_eapdTick_vtbl;
    vtbl1 = &g_eapdEmit_vtbl;
    vtbl2 = &g_eapdRC_vtbl;
    ((EmitterSub*)((char*)this + 4))->Shutdown();
    if (mConfig) {
        void* c = (void*)mConfig;
        ((void (__thiscall*)(void*))((*(void***)c)[4 / 4]))(c);
    }
    if (mpPatch)
        ((void (__thiscall*)(void*))((*(void***)mpPatch)[4 / 4]))(mpPatch);
    vtbl2 = &g_gme_refcount;
}

// ---- cEmitterEAPD class allocator @ 0x00a37a70 ---------------------------
struct FixedAllocatorBase { bool AddCore(int, int); };   // 0x00926650
void* __cdecl FUN_006abeb0(int size);

void* __cdecl cEmitterEAPD_operator_new(u32 size)
{
    if (size == 0x38) {
        void* p;
        do {
            p = (void*)g_eapd_alloc;
            if (p) {
                g_eapd_alloc = *(u32*)p;
                return p;
            }
        } while (((FixedAllocatorBase*)&g_eapd_allocCore)->AddCore(0, 0));
        return 0;
    }
    return FUN_006abeb0((int)size);
}

// ---- cEmitterModelSound::ComputeGainAttenuation @ 0x00a37b70 ------------
struct cEmitterModelSound {
    float ComputeGainAttenuation(void* a, void* b, void* c, void* d);
};
float cEmitterModelSound::ComputeGainAttenuation(void*, void*, void*, void*)
{
    return 1.0f;
}

// --- equivalence checker address annotations -------------------------------
// 0x00a206f0 GetSystemAT, 0x00a67c60 EapdGetSingletonPtr, 0x00a421f0 SPGetSystem
// 0x00f47380 operator delete, 0x00f473a0 operator new, 0x00a36ce0 vector helper
// 0x00a46150 cEAPDVoiceManager::UnregisterInstanceGroup, 0x00a1aa50/0x00a1a590/0x00a1a110 ResponseCurve
// 0x00572020, 0x009fbc50, 0x0041cb40 Matrix3::Assign, 0x00537f40 cTransform::PreTransformBy
