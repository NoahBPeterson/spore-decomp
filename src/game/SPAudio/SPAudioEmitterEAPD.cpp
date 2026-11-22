// src/game/SPAudio/SPAudioEmitterEAPD.cpp -- migrated from slice(s) s00a37dd0, s00a36d60 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioEmitterEAPD.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include <intrin.h>
#include "game/types.h"
#include "EA/Audio/ITickable.h"
#include "EA/Audio/IEmitter.h"
#include "EA/RefCountTemplate.h"
#include "EA/Audio/IPrimitive.h"
#include "EA/Audio/ResponseCurve.h"
#include "EA/Audio/Sound.h"
#include "SP/Audio/cEAPDVoiceManager.h"
#include <math.h>

// unnamed retail callees and globals (address in the comment)
extern "C" char  g_gme_refcount;  // 0x013ef094  (GmeRefCount base)
extern "C" float g_se_one;     // 0x01485720
extern "C" char  g_eapdTick_vtbl;   // 0x01453344
extern "C" char  g_eapdEmit_vtbl;   // 0x014532f8
extern "C" char  g_eapdRC_vtbl;     // 0x014532f0

// ---- items of slice s00a36d60 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
struct AudioSystem;    // EA::Audio::System (vtable)
struct EapdSystem;     // EA::Audio::Eapd::ISystem
struct SASystem;       // SP::Audio::cSystem
AudioSystem* GetSystemAT();                 // 0x00a206f0
EapdSystem*  EapdGetSingletonPtr();         // 0x00a67c60
SASystem*    SPGetSystem();                 // 0x00a421f0
void FUN_00572020(void*, int);              // 0x00572020
extern "C" char  g_gme_refcount;  // 0x013ef094  (GmeRefCount base)
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
extern "C" char  g_eapdTick_vtbl;   // 0x01453344
extern "C" char  g_eapdEmit_vtbl;   // 0x014532f8
extern "C" char  g_eapdRC_vtbl;     // 0x014532f0
struct cEAPDVoiceMgr {
    void UnregisterInstanceGroup(u32 id);   // 0x00a46150
};
struct EmitterOwnedRef {
    void* mpObject;
    ~EmitterOwnedRef() {
        if (mpObject)
            ((void (__thiscall*)(void*))((*(void***)mpObject)[1]))(mpObject);
    }
};
struct cEmitterEAPD : EA::Audio::ITickable, EA::Audio::IEmitter, EA::RefCountTemplate<int> {
    u32   mKey[3];      // +0x10
    u32   mhInstance;   // +0x1c
    EmitterOwnedRef mpPatch; // +0x20
    u32   mId;          // +0x24
    u32   mGroupId;     // +0x28
    u32   mFlags;       // +0x2c
    EmitterOwnedRef mConfig; // +0x30
    u8    mPaused;      // +0x34

    cEmitterEAPD();                     // 0xa37b10
    u32  SetPropertyInternal(int a, float f); // 0xa379d0
    bool GetProperty(int key, float* out); // 0xa37930
    void Tick(int a, int b);            // 0xa37860
    ~cEmitterEAPD();                    // 0xa37c40
    bool Load();                        // 0xa37cc0
};
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
// ---- items of slice s00a36d60 end

// ---- items of slice s00a37dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char  g_0155332c;        // 0x155332c RB key base
extern char  g_01553330;        // 0x1553330 RB loop end sentinel
extern char  g_01553334;        // 0x1553334 RB loop head
extern float f_01485720;        // 0x1485720  1.0f
typedef unsigned short u16;
#define VFN(p, off) ((*(void***)(p))[(off) / 4])
void* __cdecl GetSingletonPtr();          // 0xa67c60 EA::Audio::Eapd::ISystem::GetSingletonPtr
char* __cdecl FUN_00a37ae0();             // 0xa37ae0
void* __cdecl FUN_005727e0();             // 0x5727e0
void* __cdecl RBTreeIncrement(void* n);   // 0x921580
void* __cdecl SPGetSystem_s00a3_7dd0();              // 0xa421f0 SP::Audio::SPGetSystem
void* __cdecl GetSystemAT_s00a3_7dd0();              // 0xa206f0 EA::Audio::GetSystemAT
struct EAPDLoad { bool Load(); };                          // 0xa37cc0 cEmitterEAPD::Load
struct SysA { void Do439b0(); };                           // 0xa439b0
struct SysB { void Do466b0(void* c, void* p); };           // 0xa466b0
// ---- items of slice s00a37dd0 end

// @ 0x00a377b0
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

// @ 0x00a37820
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

// @ 0x00a37860
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

// @ 0x00a378e0
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

// @ 0x00a37930
bool cEmitterEAPD::GetProperty(int key, float* out)
{
    if (key != (int)0xc2d1f579)
        return false;
    *out = g_se_one;
    return true;
}

// @ 0x00a37960
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

// @ 0x00a379d0
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

// @ 0x00a37a10
bool EmitterSub::SetPropertyEx(int a, int b, int c)
{
    EapdSystem* e = EapdGetSingletonPtr();
    if (e != 0) {
        if (!((bool (__thiscall*)(void*, u32, int, int))((*(void***)e)[0x34 / 4]))(
                e, mKey18, a, b)) {
            AudioSystem* s = GetSystemAT();
            ((bool (__thiscall*)(void*, u32, int, int, int))((*(void***)s)[0xa8 / 4]))(
                s, mGroupId, a, b, c);
        }
        return true;
    }
    _ReadWriteBarrier();
    return true;
}

// @ 0x00a37b90
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
        _ReadWriteBarrier();
        if (mpPatch) {
            void* p = mpPatch;
            mpPatch = 0;
            ((void (__thiscall*)(void*))((*(void***)p)[4 / 4]))(p);
        }
    }
    return true;
}

// @ 0x00a37c40
cEmitterEAPD::~cEmitterEAPD()
{
    ((EmitterSub*)((char*)this + 4))->Shutdown();
}

// @ 0x00a37cc0
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
        void* old = mpPatch.mpObject;
        void* cur = local;
        if (cur != old) {
            if (cur)
                ((void (__thiscall*)(void*))((*(void***)cur)[0 / 4]))(cur);
            mpPatch.mpObject = cur;
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

// @ 0x00a37dd0
namespace SP { namespace Audio {
bool __fastcall FUN_00a37dd0(void* ctx)
{
    char* esi = (char*)ctx;
    void* sys = GetSingletonPtr();
    if (!sys) return false;
    if (*(u8*)(esi + 0x28) & 1) return false;

    char* ebx4 = esi - 4;
    if (!((EAPDLoad*)ebx4)->Load()) return false;

    void* s2 = GetSingletonPtr();
    if (s2) {
        void* ecx = *(void**)(esi + 0x1c);
        ecx = *(void**)((char*)ecx + 0x1c);
        void* edi = esi + 0x18;
        if (!((bool(__thiscall*)(void*, void*, void*))VFN(s2, 0x24))(s2, ecx, edi))
            return false;
    }

    if (*(void**)(esi + 0x2c) != 0) {
        void* c = *(void**)(esi + 0x2c);
        ((void(__thiscall*)(void*, void*, u32))VFN(c, 0xc))(c, &g_0155332c, 1);
        void* it = *(void**)&g_01553334;
        if (it != &g_01553330) {
            for (;;) {
                void* pv = *(void**)((char*)it + 0x10);
                void* cc = *(void**)(esi + 0x2c);
                void* local = 0;
                ((void(__thiscall*)(void*, void*, void**))VFN(cc, 0x1c))(cc, pv, &local);
                void* rec = local;
                u32 t = (u32)*(u16*)((char*)rec + 0x12);
                float val;
                if (t == 1) {
                    char* p = FUN_00a37ae0();
                    val = (*p == 0) ? 0.0f : f_01485720;
                } else {
                    if (t - 0xc != 0) {
                        it = RBTreeIncrement(it);
                        if (it == &g_01553330) break;
                        continue;
                    }
                    val = *(float*)FUN_005727e0();
                }
                ((void(__thiscall*)(void*, void*, float))VFN(ebx4, 0xc))(ebx4, pv, val);
                it = RBTreeIncrement(it);
                if (it == &g_01553330) break;
            }
        }
    }

    void* s3 = SPGetSystem_s00a3_7dd0();
    ((SysA*)s3)->Do439b0();
    *(u32*)(ebx4 + 0x2c) |= 1;

    void* s4 = SPGetSystem_s00a3_7dd0();
    void* edi = *(void**)((char*)s4 + 0x15bc80);
    *(void**)(esi + 0x24) = esi - 4;

    void* at = GetSystemAT_s00a3_7dd0();
    void* p = *(void**)(esi + 0x24);
    ((void(__thiscall*)(void*, void*))VFN(at, 0x120))(at, p);

    void* q = *(void**)(esi + 0x24);
    void* r = *(void**)(esi + 0x18);
    ((SysB*)edi)->Do466b0(r, q);
    return true;
}
}}  // namespace SP::Audio
