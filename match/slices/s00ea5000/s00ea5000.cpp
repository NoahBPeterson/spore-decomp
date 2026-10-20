// SP::Audio gonzago accessor primitives (slice 0xea5000..0xea6340).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GR-
#include "types.h"
#include <stddef.h>
#include <math.h>

typedef unsigned int  u32;

// ---------------------------------------------------------------------------
// external data
// ---------------------------------------------------------------------------
extern "C" char g_vt_013eb384;    // 0x013eb384  ??_7GB1@@6B@
extern "C" char g_vt_013ef094;    // 0x013ef094  ??_7GmeRefCount@@6B@
extern "C" char g_vt_0148734c;    // 0x0148734c
extern "C" char g_vt_0148737c;    // 0x0148737c
extern "C" char g_vt_0148738c;    // 0x0148738c
extern "C" char g_vt_014873d4;    // 0x014873d4
extern "C" char g_vt_0148741c;    // 0x0148741c
extern "C" char g_vt_01487628;    // 0x01487628
extern "C" char g_vt_01487a48;    // 0x01487a48
extern "C" char g_flt_01485720;   // 0x01485720  (1.0f)
extern "C" char g_flt_01486110;   // 0x01486110  (5.0f)
extern "C" char g_flt_01487370;   // 0x01487370  (10.0f)
extern "C" char g_flt_01485378;   // 0x01485378  (0.0f)
extern "C" char g_flt_013eb1bc;   // 0x013eb1bc  (-1.0f)
extern "C" char g_flt_01487378;   // 0x01487378  (FLT_MAX)
extern "C" char g_emptyString16;  // 0x01667bac  eastl::gEmptyString16
extern "C" char g_d_015e4ef0;     // 0x015e4ef0
extern "C" char g_d_015e4eca;     // 0x015e4eca
extern "C" char g_d_01654c05;     // 0x01654c05
extern "C" char g_flt_016c6adc;   // 0x016c6adc
extern "C" char g_flt_016c6ae0;   // 0x016c6ae0
extern "C" char g_flt_016c6ae4;   // 0x016c6ae4

// ---------------------------------------------------------------------------
// external callees
// ---------------------------------------------------------------------------
void __cdecl operator_delete(void* p);        // 0x00f47380  ??3@YAXPAX@Z

int   GetSetting3();                          // 0x00401030
float FUN_0040ae50(float v);                  // 0x0040ae50
u32   FUN_00576550(float h);                  // 0x00576550
void* SP_App();                               // 0x0067dd10
void* SP_EffectsManager();                    // 0x0067ddd0
void* SP_AudioSystem();                       // 0x0067cb00
void* SP_PlanetModel();                       // 0x00b3d350
void* SP_MessageServer();                     // 0x0067dcc0
void* SP_NounManager();                       // 0x00b3d300
void* SP_RelationshipManager();               // 0x00b3d2c0
void* SP_RelationshipManager2();              // 0x00b3d3c0
u32   SP_GetCurrentGameMode();                // 0x00b5b800
void* FUN_01021230();                         // 0x01021230
void* FUN_01021260();                         // 0x01021260
void* FUN_01021300();                         // 0x01021300
void* SP_TimeOfDayInstance();                 // 0x00bc30b0
struct FUN_00e28a00_t { float FUN_00e28a00(); };   // 0x00e28a00
#define FUN_00e28a00(p) (((FUN_00e28a00_t*)(p))->FUN_00e28a00())
struct RelMgr2 { float FUN_00d00a10(void* a, void* b, int c); };  // 0x00d00a10
#define FUN_00d00a10(self,a,b,c) (((RelMgr2*)(self))->FUN_00d00a10(a,b,c))
struct RelMgr { int FUN_00b79e50(void* obj, float f, int one); };   // 0x00b79e50
#define FUN_00b79e50(self,obj,f,one) (((RelMgr*)(self))->FUN_00b79e50(obj,f,one))

struct TerrainMapSet;
struct Viewer;
struct NounManager;
struct AutoRef;
struct AutoRef { void* mp; AutoRef(void* p); };          // 0x00572660
struct NounManager { void* GetAvatar(); };               // 0x00b1fdb0
struct TerrainMapSet { float GetHeightAt(); };           // 0x00f927c0
struct Viewer { void GetCameraLocationInfo(float*, float*, float*, int); };  // 0x007c3d30
struct FixupDummy {};

// ---------------------------------------------------------------------------
// raw vtable helpers
// ---------------------------------------------------------------------------
namespace vt {
    template <class R, class A>
    inline R call1(void* p, int byteoff, A a) {
        return ((R (__thiscall*)(void*, A))(*(void***)p)[byteoff / 4])(p, a);
    }
    template <class R, class A, class B>
    inline R call2(void* p, int byteoff, A a, B b) {
        return ((R (__thiscall*)(void*, A, B))(*(void***)p)[byteoff / 4])(p, a, b);
    }
    template <class R, class A, class B, class C>
    inline R call3(void* p, int byteoff, A a, B b, C c) {
        return ((R (__thiscall*)(void*, A, B, C))(*(void***)p)[byteoff / 4])(p, a, b, c);
    }
    template <class R>
    inline R call0(void* p, int byteoff) {
        return ((R (__thiscall*)(void*))(*(void***)p)[byteoff / 4])(p);
    }
}

// ---------------------------------------------------------------------------
// structures (fields only; virtual slots are called through vt:: helpers)
// ---------------------------------------------------------------------------
struct Prim {
    void* v0;       // 0x00
    void* v4;       // 0x04
    void* v8;       // 0x08
    int   refc;     // 0x0c
    char  mbDirty;  // 0x10
    float mValue;   // 0x14
    void* mpConfig; // 0x18
    int   m1c;      // 0x1c
    int   m20;      // 0x20
    int   m24;      // 0x24
    int   m28;      // 0x28
    int   m2c;      // 0x2c
    float m30;      // 0x30
    int   m34;      // 0x34
    float m38;      // 0x38
    float m3c;      // 0x3c
    float m40;      // 0x40
    float m44;      // 0x44

    bool Init();                              // 0x00a16f60
    void BaseUpdate(float dt, u32 id);        // 0x00a16ed0
    bool BaseShutdown();                      // 0x00a16e70
    void SetValue(float v);                   // slot 13 (+0x34)

    void* ScalarDeletingDtor(unsigned char flags);        // 0xea5350
    bool MsgShutdown();                                   // 0xea5650
    bool Init0();                                         // 0xea53f0
    bool Init1();                                         // 0xea54f0
    bool Init2();                                         // 0xea56a0
    void ConfigParam();                                   // 0xea5700
    void Update0(float dt, u32 id);                       // 0xea5510
    void Update1(float dt, u32 id);                       // 0xea5720
    void Update2(float dt, u32 id);                       // 0xea58c0
    void Update3(float dt, u32 id);                       // 0xea5a60
    void Update4(float dt, u32 id);                       // 0xea5bc0
    void Update5(float dt, u32 id);                       // 0xea5d60
    void Update6(float dt, u32 id);                       // 0xea5e40
    void Update7(float dt, u32 id);                       // 0xea5f20
    void Update8(float dt, u32 id);                       // 0xea5fe0
    void Update9(float dt, u32 id);                       // 0xea60a0
    void Update10(float dt, u32 id);                      // 0xea6230
    void Update11(float dt, u32 id);                      // 0xea6340
    Prim* Ctor0();                                        // 0xea55b0
    Prim* Ctor1();                                        // 0xea5830
    Prim* Ctor2();                                        // 0xea59b0
    void Ctor3();                                         // 0xea53d0 -> SetValue wrapper
    bool HandleMsg(u32 msg, float* pv);                   // 0xea57c0
};

struct MixModeManager {
    void Shutdown();                     // 0x00ea9c70
    void UpdateSounds(float t);          // 0x00ea9880
};

struct MixHolder {
    void* v0;               // 0x00
    void* v4;               // 0x04
    int   m08;              // 0x08
    MixModeManager* mMix;   // 0x0c
    void Shutdown();              // 0x00ea5380
    void UpdateSounds(float t);   // 0x00ea53b0
};

struct HandlerSub {
    void* vtbl;     // 0x00
    char  pad[0x30];
    float f34;      // 0x34
    float f38;      // 0x38
    float f3c;      // 0x3c
    float f40;      // 0x40
    bool Handle(u32 msg, float* pv);   // 0xea57c0
};

struct PlanetModel {
    char  pad24[0x24];
    void* m24;                          // 0x24
    float GetWaterHeight();             // 0x00b7e390
    bool  CheckAbove(float h);          // 0x00b7e3e0
    float FUN_00b7e430(float h, int o); // 0x00b7e430
    bool  FUN_00b7ec40();               // 0x00b7ec40
    float* FUN_00b81630(void* out, const float* dir);  // 0x00b81630
};

struct MapInfo {
    char  pad34[0x34];
    float f34;
    float f38;
    float f3c;
    float f40;
    float f44;
};

struct TimeOfDay {
    char  pad24[0x24];
    float m24;                          // 0x24
    float FUN_00bc2b30(const float* pos);// 0x00bc2b30
};

struct Terraforming {
    float FUN_00c70a20();   // 0x00c70a20
    void* FUN_00c70fb0();   // 0x00c70fb0
    float FUN_00c709d0();   // 0x00c709d0
};

struct Prim;
__forceinline void SetValueDispatch(Prim* p, float v) {
    ((void (__thiscall*)(Prim*, float))((*(void***)p)[0x34 / 4]))(p, v);
}

// ===========================================================================
// @ 0x00ea5000
// ===========================================================================
u32 __stdcall GetSurfaceTypeAt(float height)
{
    if (*(char*)(GetSetting3() + 0x1c) != 0)
        return 0;
    void* app = SP_App();
    if (vt::call0<u32>(app, 0x38) == 0xdbdba1 && *(void**)&g_d_015e4ef0 != 0)
        return FUN_00576550(height);

    PlanetModel* planet = (PlanetModel*)SP_PlanetModel();
    if (planet == 0)
        return 0;
    void* obj = *(void**)((char*)SP_PlanetModel() + 0x24);
    if (obj == 0)
        return 0;

    void* effect = vt::call2<void*, u32, int>(SP_EffectsManager(), 0x8c, (u32)0x107ae878, 0);
    if (effect != 0) {
        vt::call0<void>(effect, 0x0);
        float v = vt::call1<float>(effect, 0x20, height);
        if (v == 0.0f) {
            vt::call0<void>(effect, 0x4);
            return 0;
        }
    }

    if (planet->CheckAbove(height)) {
        float d = FUN_0040ae50(height) - planet->GetWaterHeight();
        if (d > 0.5f) {
            if (effect != 0)
                vt::call0<void>(effect, 0x4);
            return 0x7fd0653au;
        }
        Terraforming* tf = (Terraforming*)FUN_01021260();
        if (tf != 0) {
            tf->FUN_00c70a20();
            bool low = (0.2f <= tf->FUN_00c70a20()) || (tf->FUN_00c70fb0() != 0) ? false : true;
            bool high = (tf->FUN_00c70a20() <= 0.8f) || (tf->FUN_00c70fb0() != 0) ? false : true;
            if (low) {
                if (effect != 0)
                    vt::call0<void>(effect, 0x4);
                return 4;
            }
            if (high) {
                if (effect != 0)
                    vt::call0<void>(effect, 0x4);
                return 5;
            }
        }
        float h = planet->FUN_00b7e430(height, 1);
        if (h > 0.0f) {
            if (h > 1.0f) {
                if (effect != 0)
                    vt::call0<void>(effect, 0x4);
                return 1;
            }
            if (effect != 0)
                vt::call0<void>(effect, 0x4);
            return 2;
        }
    }

    {
        MapInfo* info = vt::call0<MapInfo*>(obj, 0xc);
        float h = (info->f44 + info->f3c) * info->f38 + info->f34;
        TerrainMapSet* set = vt::call1<TerrainMapSet*, float>(obj, 0xc, h);
        float gh = set->GetHeightAt();
        if (h > gh) {
            if (effect != 0)
                vt::call0<void>(effect, 0x4);
            return 0x2fe99727u;
        }
    }

    void* pa = vt::call2<void*, u32, int>(SP_EffectsManager(), 0x8c, (u32)0x2c9c762, 0);
    AutoRef ra(pa);
    void* pb = vt::call2<void*, u32, int>(SP_EffectsManager(), 0x8c, (u32)0x1c8a626, 0);
    AutoRef rb(pb);
    if (ra.mp != 0 && rb.mp != 0) {
        float x = vt::call1<float>(ra.mp, 0x20, height);
        if (x == 1.0f) {
            float y = vt::call1<float>(rb.mp, 0x20, height);
            if (y == 1.0f) {
                vt::call0<void>(rb.mp, 0x4);
                vt::call0<void>(ra.mp, 0x4);
                if (effect != 0)
                    vt::call0<void>(effect, 0x4);
                return 3;
            }
        }
    }
    if (rb.mp != 0)
        vt::call0<void>(rb.mp, 0x4);
    if (ra.mp != 0)
        vt::call0<void>(ra.mp, 0x4);
    if (effect != 0)
        vt::call0<void>(effect, 0x4);
    return 0;
}

// ===========================================================================
// @ 0x00ea5350
// ===========================================================================
void* Prim::ScalarDeletingDtor(unsigned char flags)
{
    this->v0 = &g_vt_0148734c;
    this->v4 = &g_vt_013ef094;
    if ((flags & 1) != 0)
        operator_delete(this);
    return this;
}

// ===========================================================================
// @ 0x00ea5380
// ===========================================================================
void MixHolder::Shutdown()
{
    if (mMix != 0) {
        mMix->Shutdown();
        MixModeManager* p = mMix;
        if (p != 0) {
            mMix = 0;
            vt::call0<void>(p, 0xc);
        }
    }
}

// ===========================================================================
// @ 0x00ea53b0
// ===========================================================================
void MixHolder::UpdateSounds(float t)
{
    if (mMix != 0)
        mMix->UpdateSounds(t);
}

// ===========================================================================
// @ 0x00ea53d0
// ===========================================================================
void Prim::SetValue(float v)
{
    float value = v;
    if (value != this->mValue) {
        --this->m20;
        this->mbDirty = 1;
        this->mValue = value;
    }
}

// ===========================================================================
// @ 0x00ea53f0
// ===========================================================================
bool Prim::Init0()
{
    if (!this->Init())
        return false;
    float* f = (float*)&this->m24;
    f[3] = 0.0f;    // 0x30
    f[2] = 0.0f;    // 0x2c
    f[4] = 0.0f;    // 0x34
    f[1] = 0.0f;    // 0x28
    f[0] = 0.0f;    // 0x24
    return true;
}

// ===========================================================================
// @ 0x00ea5420
// ===========================================================================
bool FUN_00ea5420(void* self)
{
    char c = vt::call0<char>((char*)self + 0x34, 0x58);
    return c == 0;
}

// ===========================================================================
// @ 0x00ea5440
// ===========================================================================
void* __cdecl FUN_00ea5440(void** range, const float* pos, bool (__cdecl* filter)(void*))
{
    void** it = (void**)*range;
    void** end = (void**)range[1];
    float bestDist = *(float*)&g_flt_01487378;
    int best = 0;
    if (it == end)
        return (void*)best;
    do {
        void* p = *it;
        if (filter(p)) {
            float* v = vt::call0<float*>((char*)p + 0x34, 0x2c);
            float dy = v[1] - pos[1];
            float dx = v[0] - pos[0];
            float dz = v[2] - pos[2];
            float d = dx * dx + dy * dy + dz * dz;
            if (bestDist > d) {
                best = (int)p;
                bestDist = d;
            }
        }
        ++it;
    } while (it != end);
    return (void*)best;
}

// ===========================================================================
// @ 0x00ea54f0
// ===========================================================================
bool Prim::Init1()
{
    if (!this->Init())
        return false;
    *(char*)&this->m24 = 1;
    *(float*)&this->m28 = 0.0f;
    return true;
}

// ===========================================================================
// @ 0x00ea5510
// ===========================================================================
void Prim::Update0(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    void* app = SP_App();
    if (vt::call0<u32>(app, 0x38) != 0x1654c05)
        return;
    void* lu = FUN_01021230();
    if (lu == 0)
        return;
    void* avatar = ((NounManager*)*(void**)((char*)lu + 0x48))->GetAvatar();
    void* empire = FUN_01021300();
    void* owner = *(void**)((char*)empire + 0x84);
    bool isOwner = (avatar == owner);
    *(bool*)&this->m24 = isOwner;
    if (isOwner) {
        *(float*)&this->m28 = *(float*)&g_flt_01487370;
        return;
    }
    if (avatar == (void*)-1)
        return;
    if (SP_GetCurrentGameMode() == 0xdbdba1)
        return;
    if (SP_RelationshipManager() == 0)
        return;
    *(float*)&this->m28 = FUN_00d00a10(SP_RelationshipManager(), avatar, owner, 0);
}

// ===========================================================================
// @ 0x00ea55b0
// ===========================================================================
Prim* Prim::Ctor0()
{
    Prim* p = this;
    *(void* volatile*)&p->v4 = &g_vt_013eb384;
    *(void* volatile*)&p->v8 = &g_vt_013ef094;
    p->refc = 0;
    p->mValue = 0.0f;
    p->mbDirty = 1;
    p->mpConfig = 0;
    p->m1c = 0;
    p->m20 = 0;
    p->v0 = &g_vt_0148738c;
    p->v4 = &g_vt_0148737c;
    p->v8 = &g_vt_01487a48;
    p->m24 = (int)&g_emptyString16;
    p->m28 = (int)&g_emptyString16;
    p->m2c = (int)&g_emptyString16 + 1;
    p->m34 = 0;
    p->m44 = *(float*)&g_flt_01486110;
    return p;
}

// ===========================================================================
// @ 0x00ea5650
// ===========================================================================
bool Prim::MsgShutdown()
{
    void* srv = SP_MessageServer();
    if (srv != 0) {
        void* self = this ? (void*)((char*)this + 4) : 0;
        void** vtbl = *(void***)srv;
        ((void (__thiscall*)(void*, void*, u32, u32))vtbl[0x2c / 4])(
            srv, self, (u32)0x1959007, (u32)0xffffd8f1);
    }
    return this->BaseShutdown();
}

// ===========================================================================
// @ 0x00ea56a0
// ===========================================================================
bool Prim::Init2()
{
    if (!this->Init())
        return false;
    void* srv = SP_MessageServer();
    if (srv != 0) {
        void* self = this ? (void*)((char*)this + 4) : 0;
        void** vtbl = *(void***)srv;
        ((void (__thiscall*)(void*, void*, u32))vtbl[0x20 / 4])(srv, self, (u32)0x1959007);
    }
    float one = *(float*)&g_flt_01485720;
    this->m3c = one;
    this->m38 = one;
    this->m40 = 0.0f;
    return true;
}

// ===========================================================================
// @ 0x00ea5700
// ===========================================================================
void Prim::ConfigParam()
{
    if (this->mpConfig != 0)
        vt::call2<void, u32, void*>(this->mpConfig, 0x30, (u32)0x9e3669da, (char*)this + 0x44);
}

// ===========================================================================
// @ 0x00ea5720
// ===========================================================================
void Prim::Update1(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    if (this->m3c != this->m38) {
        float delta = this->m38 - this->m3c;
        float dir = *(float*)&g_flt_01485378 <= delta ? *(float*)&g_flt_01485720 : *(float*)&g_flt_013eb1bc;
        float ad = (float)fabs(delta);
        float step = this->m40 * dt;
        if (step > ad)
            step = ad;
        this->m3c = step * dir + this->m3c;
    }
    SetValueDispatch(this, this->m3c);
}

// ===========================================================================
// @ 0x00ea57c0
// ===========================================================================
bool HandlerSub::Handle(u32 msg, float* pv)
{
    if (msg == 0x1959007) {
        float v = *pv;
        float d = v - this->f38;
        this->f34 = v;
        float f = (float)fabs(d);
        if (this->f40 != 0.0f && !(f < 1e-6)) {
            this->f3c = f / this->f40;
            return true;
        }
        this->f38 = *pv;
    }
    return true;
}

// ===========================================================================
// @ 0x00ea5830
// ===========================================================================
Prim* Prim::Ctor1()
{
    Prim* p = this;
    *(void* volatile*)&p->v4 = &g_vt_013eb384;
    *(void* volatile*)&p->v8 = &g_vt_013ef094;
    p->refc = 0;
    p->mbDirty = 1;
    p->mValue = 0.0f;
    p->mpConfig = 0;
    p->m1c = 0;
    p->m20 = 0;
    p->v0 = &g_vt_014873d4;
    p->v4 = &g_vt_01487628;
    p->v8 = &g_vt_01487a48;
    p->m24 = (int)&g_emptyString16;
    p->m28 = (int)&g_emptyString16;
    p->m2c = (int)&g_emptyString16 + 1;
    p->m34 = 0;
    p->m38 = 0.0f;
    return p;
}

// ===========================================================================
// @ 0x00ea58c0
// ===========================================================================
void Prim::Update2(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    void* sub = vt::call0<void*>(SP_App(), 0x50);
    void* viewer = vt::call0<void*>(sub, 0x1c);
    if (viewer == 0)
        return;
    float pos[3];
    ((Viewer*)viewer)->GetCameraLocationInfo(pos, 0, 0, 0);
    TimeOfDay* tod = (TimeOfDay*)SP_TimeOfDayInstance();
    if (tod == 0)
        return;
    float dayLen = tod->m24;
    float f = tod->FUN_00bc2b30(pos);
    bool near_ = (this->m38 - f) < dayLen * 0.5f;
    if ((float)(u32)near_ != 0.0f) {
        SetValueDispatch(this, f);
        this->m38 = f;
        return;
    }
    this->m38 = f;
}

// ===========================================================================
// @ 0x00ea59b0
// ===========================================================================
Prim* Prim::Ctor2()
{
    Prim* p = this;
    *(void* volatile*)&p->v4 = &g_vt_013eb384;
    *(void* volatile*)&p->v8 = &g_vt_013ef094;
    p->refc = 0;
    p->mbDirty = 1;
    p->mValue = 0.0f;
    p->mpConfig = 0;
    p->m1c = 0;
    p->m20 = 0;
    p->v0 = &g_vt_0148741c;
    p->v4 = &g_vt_01487628;
    p->v8 = &g_vt_01487a48;
    p->m24 = (int)&g_emptyString16;
    p->m28 = (int)&g_emptyString16;
    p->m2c = (int)&g_emptyString16 + 1;
    p->m34 = 0;
    p->m38 = *(float*)&g_flt_016c6adc;
    p->m3c = *(float*)&g_flt_016c6ae0;
    p->m40 = *(float*)&g_flt_016c6ae4;
    return p;
}

// ===========================================================================
// @ 0x00ea5a60
// ===========================================================================
void Prim::Update3(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    void* s1 = vt::call0<void*>(SP_AudioSystem(), 0x24);
    float* p = vt::call0<float*>(s1, 0x24);
    if (p[0] != this->m38 || p[1] != this->m3c || p[2] != this->m40) {
        *(u32*)&this->m38 = *(u32*)&p[0];
        *(u32*)&this->m3c = *(u32*)&p[1];
        *(u32*)&this->m40 = *(u32*)&p[2];
        void* s2 = vt::call0<void*>(SP_AudioSystem(), 0x24);
        float f = vt::call0<float>(s2, 0x20);
        int n = 0;
        if (SP_RelationshipManager2() != 0)
            n = FUN_00b79e50(SP_RelationshipManager2(), p, f, 1);
        SetValueDispatch(this, (float)n);
    }
}

// ===========================================================================
// @ 0x00ea5bc0
// ===========================================================================
void Prim::Update4(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    void* viewer = vt::call0<void*>(SP_App(), 0x58);
    PlanetModel* planet = (PlanetModel*)SP_PlanetModel();
    float dist = 0.0f;
    if (viewer != 0 && planet != 0) {
        if (planet->FUN_00b7ec40()) {
            float pos[3];
            ((Viewer*)viewer)->GetCameraLocationInfo(pos, 0, 0, 0);
            float invLen = (float)(1.0 / sqrt((double)pos[0] * pos[0]
                      + ((double)pos[1] * pos[1] + (double)pos[2] * pos[2])));
            float dir[3];
            dir[0] = invLen * pos[0];
            dir[1] = pos[1] * invLen;
            dir[2] = pos[2] * invLen;
            float* r = planet->FUN_00b81630(0, dir);
            dist = (float)sqrt(((double)(pos[2] - r[2]) * (pos[2] - r[2])
                    + (double)(pos[1] - r[1]) * (pos[1] - r[1]))
                    + (double)(pos[0] - r[0]) * (pos[0] - r[0]));
        }
    }
    SetValueDispatch(this, dist);
}

// ===========================================================================
// @ 0x00ea5d60
// ===========================================================================
void Prim::Update5(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    PlanetModel* planet = (PlanetModel*)SP_PlanetModel();
    float v;
    if (planet == 0 || planet->m24 == 0)
        v = 0.0f;
    else
        v = *(float*)&g_flt_01485720;
    SetValueDispatch(this, v);
}

// ===========================================================================
// @ 0x00ea5e40
// ===========================================================================
void Prim::Update6(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    PlanetModel* planet = (PlanetModel*)SP_PlanetModel();
    void* o = planet->m24;
    if (o != 0) {
        void** vtbl = *(void***)this;
        void* p = ((void* (__thiscall*)(void*))((*(void***)o)[0x10 / 4]))(o);
        ((void (__thiscall*)(Prim*, float))vtbl[0x34 / 4])(this, FUN_00e28a00(p));
    }
}

// ===========================================================================
// @ 0x00ea5f20
// ===========================================================================
void Prim::Update7(float dt, u32 id)
{
    Terraforming* tf = (Terraforming*)FUN_01021260();
    if (tf != 0) {
        void** vtbl = *(void***)this;
        float r = tf->FUN_00c709d0();
        ((void (__thiscall*)(Prim*, float))vtbl[0x34 / 4])(this, r);
    }
}

// ===========================================================================
// @ 0x00ea5fe0
// ===========================================================================
void Prim::Update8(float dt, u32 id)
{
    Terraforming* tf = (Terraforming*)FUN_01021260();
    if (tf != 0) {
        void** vtbl = *(void***)this;
        float r = tf->FUN_00c70a20();
        ((void (__thiscall*)(Prim*, float))vtbl[0x34 / 4])(this, r);
    }
}

// ===========================================================================
// @ 0x00ea60a0
// ===========================================================================
void Prim::Update9(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    void* viewer = vt::call0<void*>(SP_App(), 0x58);
    PlanetModel* planet = (PlanetModel*)SP_PlanetModel();
    float v = 0.0f;
    if (viewer != 0 && planet != 0) {
        if (planet->FUN_00b7ec40()) {
            float pos[3];
            ((Viewer*)viewer)->GetCameraLocationInfo(pos, 0, 0, 0);
            float invLen = (float)(1.0 / sqrt((double)pos[0] * pos[0]
                      + ((double)pos[1] * pos[1] + (double)pos[2] * pos[2])));
            float dir[3];
            dir[0] = invLen * pos[0];
            dir[1] = invLen * pos[1];
            dir[2] = pos[2] * invLen;
            float* r = planet->FUN_00b81630(0, dir);
            v = (float)sqrt(((double)r[0] * r[0] + (double)r[1] * r[1]) + (double)r[2] * r[2]);
        }
    }
    SetValueDispatch(this, v);
}

// ===========================================================================
// @ 0x00ea6230
// ===========================================================================
void Prim::Update10(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    void* nm = SP_NounManager();
    if (nm == 0)
        return;
    void* av = ((NounManager*)nm)->GetAvatar();
    if (av == 0)
        return;
    float* p = vt::call0<float*>((char*)av + 0xc0, 0x2c);
    float y = p[1];
    float z = p[2];
    float x = p[0];
    SetValueDispatch(this, (float)sqrt(((double)y * y + (double)z * z)
        + (double)x * x));
}

// ===========================================================================
// @ 0x00ea6340
// ===========================================================================
void Prim::Update11(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
}
