// src/game/SPGonzago/_at_00cc0000.cpp -- migrated from slice(s) s00ccfc20, s00ccece0, s00ccdd70, s00cc22c0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00cc0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cDefaultAoEArea.h"
#include "SP/cEffectInfo.h"
#include "SP/cEmpire.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cPlanet.h"
#include "SP/cSPSwatch.h"

// ---- items of slice s00cc22c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
class IRefCounted {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};
class cEffectInfo : public IRefCounted {
public:
    uint8_t mPad14[0x10];
};
class cSpatialObjectView : public IRefCounted {
public:
    cSpatialObjectView();
    ~cSpatialObjectView();
    void SetObject(void* pObject);                  // 0x24
    int UpdateState();
    void HandleSimulationUpdate(int a, int b);
    void CreateEffect(uint32_t id, int a);          // wrapper over the effect list

    uint8_t mPad04[0x10];           // 0x04
    void* mpObject;                 // 0x14
    uint8_t mPad18[0x1c];           // 0x18
    cEffectInfo* mpEffectInfo;      // 0x34
    uint8_t mFlag38;                // 0x38
    uint8_t mFlag39;                // 0x39
    uint8_t mFlag3a;                // 0x3a
    uint8_t mFlag3b;                // 0x3b
    uint8_t mFlag3c;                // 0x3c
    uint8_t mFlag3d;                // 0x3d
    uint8_t mPad3e[0x02];           // 0x3e
    int mViewState;                 // 0x40
};
class cDefaultBeamProjectileView : public cSpatialObjectView {
public:
    cDefaultBeamProjectileView();
    bool mbLoadingModel;            // 0x44
    bool mbAnimationsStarted;       // 0x45
};
void* operator_new(size_t nSize, const char* pName, int a, int b, int c, int d);
void* operator_new(size_t nSize, const char* pName, int a);
void* operator_new(size_t nSize, const char* pName, int a, int b);
uint32_t GetTrailEffectId();
void CreateEffectRef(uint32_t id, int a, uint32_t group);
void SetEffectScale(uint32_t id, uint32_t fScaleBits);
// ---- items of slice s00cc22c0 end

// ---- items of slice s00ccdd70 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
typedef unsigned char u8;
template <class R> inline R V0(void* o, int off) { return ((R (__thiscall *)(void*))(*(void***)o)[off / 4])(o); }
template <class R, class A> inline R V1(void* o, int off, A a) { return ((R (__thiscall *)(void*, A))(*(void***)o)[off / 4])(o, a); }
template <class R, class A, class B> inline R V2(void* o, int off, A a, B b) { return ((R (__thiscall *)(void*, A, B))(*(void***)o)[off / 4])(o, a, b); }
template <class R, class A, class B, class C> inline R V3(void* o, int off, A a, B b, C c) { return ((R (__thiscall *)(void*, A, B, C))(*(void***)o)[off / 4])(o, a, b, c); }
struct Server { };
Server* GetServer();                                                 // 0x883860
int  __stdcall GetPauseGateCount(u32 gate);                          // 0x00b320d0 (ret 4)
void __cdecl EndBanMode(int on);                                     // 0x00dd1840 (ret 4)
void __cdecl ToggleBanningContent(int on);                           // 0x00dd17f0 (ret 4)
void __cdecl FUN_00e09a50(int on);                                   // 0x00e09a50 (ret 4)
void __cdecl FUN_00e099d0(int on);                                   // 0x00e099d0 (ret 4)
void __cdecl RemoveHandler(void* h, u32 a, u32 b, u32 c, u32 d);     // 0x00571db0 (ret 0x14)
struct TerrainCursor                                                 // the hovered terrain cursor
{
    void SetMode(int mode);                                          // 0x00b2fba0 (ret 4)
};
TerrainCursor* __cdecl GetGameTerrainCursor();                       // 0x00b30d70
struct CameraCtl                                                     // SP::cTerrainCameraController
{
    char pad00[0x390];
    u8   mMode390;                                                   // +0x390
    void SetToggle(bool on);                                         // 0x00b0f950 (ret 4)
};
CameraCtl* __cdecl GetCameraCtl();                                   // 0x00b3d280
struct TcRefObj                                                      // refcounted helper (+0x5c, +0xc0)
{
    virtual void AddRef();                                           // +0x00
    virtual void Release();                                          // +0x04
    virtual void Slot8();                                            // +0x08
    virtual void Release3();                                         // +0x0c
    void Reset();                                                    // 0x00d12fc0
};
struct Stopwatch                                                     // EA::Stopwatch at +0xa8
{
    u32 mStart;                                                      // +0x00
    u32 mStop;                                                       // +0x04
    u32 mDelta;                                                      // +0x08
    u32 mPad;                                                        // +0x0c
    void Restart();                                                  // 0x00571e80
};
struct TcTerrain                                                     // the planet view at +0x40
{
    bool TerrainHasKey(u32 key);                                     // 0x00cd4460 (ret 4)
};
struct Citizen                                                       // SP::cSPCreatureCitizen
{
    void* GiveOrder(void* a, void* b, void* c);                      // 0x00c275b0 (ret 0xc)
};
u32 g_msgToken169b1c4;                                               // 0x0169b1c4
class cSPUITCCCursorStrategy
{
public:
    void RegisterCursors();                                          // 0x00cce610 (PDB candidate: ctor)
    void FUN_00cce5b0();                                             // 0x00cce5b0
    void FUN_00cce5e0();                                             // 0x00cce5e0
    void FUN_00cce940();                                             // 0x00cce940
    void FUN_00ccea10(void* obj, bool flag);                         // 0x00ccea10 (ret 8)
    u32  FUN_00cceae0(void* obj, u32 mode, void* arg3);              // 0x00cceae0 (ret 0xc)
    u32  FUN_00ccebd0(void* obj, int flag, void* arg3);              // 0x00ccebd0 (ret 0xc)
    void FUN_00ccec20(u32 flag);                                     // 0x00ccec20 (ret 4)
    u32  FUN_00cceca0(void* a, void* b);                             // 0x00cceca0 (ret 8)

    char       pad00[0x40];
    TcTerrain* mpTerrain;                                            // +0x40
    void*      mpHandler;                                            // +0x44
    u32        mH48;                                                 // +0x48
    u32        mH4c;                                                 // +0x4c
    u32        mH50;                                                 // +0x50
    u32        mH54;                                                 // +0x54
    u32        mPad58;                                               // +0x58
    TcRefObj*  mpRef5c;                                              // +0x5c
    char       pad60[0xa0 - 0x60];
    u32        mMode;                                                // +0xa0
    char       padA4[0xa8 - 0xa4];
    Stopwatch  mStop;                                                // +0xa8
    char       padB8[0xc0 - 0xb8];
    TcRefObj*  mpRefC0;                                              // +0xc0
};
// ---- items of slice s00ccdd70 end

// ---- items of slice s00ccece0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
extern float g_169b264, g_169b268, g_169b26c;                     // 0x0169b264..
extern char  g_169b240[];                                         // 0x0169b240
#pragma intrinsic(_InterlockedExchange)
#define VSLOT(n) virtual void vslot##n()
struct Vec3 { float x, y, z; };
struct Mat33 {
    float m[9];
    void Ctor(const void* src);                                   // 0x0041cb40
};
struct SelRecord {
    unsigned short flags;                                         // +0x00
    unsigned short count;                                         // +0x02
    float x, y, z;                                                // +0x04
    float scale;                                                  // +0x10
    Mat33 mat;                                                    // +0x14
};
struct SelCursor {
    virtual void v0();
    virtual void Release();                                       // +0x04
    virtual void v2(int);                                         // +0x08
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void Submit(SelRecord* rec);                          // +0x18
};
struct IEffectsManager {
VSLOT(0);
VSLOT(1);
VSLOT(2);
VSLOT(3);
VSLOT(4);
VSLOT(5);
VSLOT(6);
VSLOT(7);
VSLOT(8);
VSLOT(9);
VSLOT(10);
    virtual char CreateCursor(u32 id, int z, SelCursor** out);    // +0x2c
};
IEffectsManager* EffectsManager();                                // 0x0067ddd0
struct IPlanetModel {
    void  F_00b81630(Vec3* out, void* a);                         // 0x00b81630
    Vec3* F_00b7e3b0(Vec3* out, const Vec3* in);                  // 0x00b7e3b0
};
IPlanetModel* PlanetModel();                                      // 0x00b3d350
void F_006985b0(Vec3* up, const Vec3* facing);                    // 0x006985b0
void F_0069b440(float* mat, const Vec3* up, const Vec3* facing);  // 0x0069b440
// ---- items of slice s00ccece0 end

// ---- items of slice s00ccfc20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl rt_del_array(void*);                                       // 0xf47380
void*  GetGameTerrainCursor_s00cc_fc20();                 // 0x00b30d70
void*  FUN_00b3d240();                         // 0x00b3d240
void*  FUN_00b3d300();                         // 0x00b3d300  SP::NounManager
void*  FUN_00435e90();                         // 0x00435e90  GetRecorderState
void   FUN_00435ed0(void*, uint32_t);          // 0x00435ed0  KillSetiEffects
uint32_t FUN_00ccefb0(void*, void*);           // 0x00ccefb0  GetTribeCursorID
void*  FUN_0067cab0();                         // 0x0067cab0
void   FUN_00b69990(void*);                    // 0x00b69990
void*  FUN_00ac80d0(void*, uint32_t);          // 0x00ac80d0
unsigned char g_ccff40Gate;                    // 0x01686af0
void*  FUN_008013c0(void*);                                 // 0x008013c0 (thiscall)
unsigned char FUN_00801bb0(void*, uint32_t);                // 0x00801bb0 (thiscall)
void*  FUN_00bfc5f0(void*);                                 // 0x00bfc5f0 (thiscall)
struct StackVec {
    void**  mpBegin;    // +0x00
    void**  mpEnd;      // +0x04
    void**  mpCap;      // +0x08
    void*   mX0c;       // +0x0c
    void*   mX10;       // +0x10
    void*   mX14;       // +0x14
    void*   mBuf[16];   // +0x18
    void init()
    {
        mX14    = 0;
        mpBegin = &mBuf[0];
        mpEnd   = &mBuf[0];
        mpCap   = &mBuf[16];
    }
};
struct CInput {
    void F_ccfc20(void* arg);                            // 0x00ccfc20
    void F_ccfcf0(void* vec, int key, void* a, void* b); // 0x00ccfcf0
    void F_cd07c0(void* a, void* b, void* c);            // 0x00cd07c0
    int  F_cd0830(void* arg);                            // 0x00cd0830
    void F_cd0950();                                     // 0x00cd0950
    void F_cd02d0(void* pos);                            // 0x00cd02d0
    int  F_cd0660(void* flags, void* pos, void* c);      // 0x00cd0660
};
struct CMgr { int M_e9b0(void* vec, int key, void* a, void* b); };
// ---- items of slice s00ccfc20 end

// @ 0x00cc28c0
cDefaultBeamProjectileView::cDefaultBeamProjectileView()
{
    mpEffectInfo = nullptr;         // 0x34
    mFlag38 = 0;
    mFlag39 = 0;
    mFlag3a = 0;
    mFlag3b = 0;
    mFlag3c = 0;
    mFlag3d = 0;
}

// @ 0x00cc28f0
cSpatialObjectView* MakeFlakProjectileView(void* pObject)
{
    cSpatialObjectView* pView =
        (cSpatialObjectView*)operator_new(0x34, "Simulator/cFlakProjectileView", 0, 0, 0, 0);
    if (pView == nullptr)
        pView = nullptr;
    else
        pView->SetObject(nullptr);

    pView->SetObject(pObject);

    void* pData = nullptr;
    if (pObject != nullptr)
        pData = ((IRefCounted*)pObject)->Query((const void*)0x240e3b7);

    if (*(void**)((uint8_t*)pData + 0x518) != nullptr) {
        uint32_t nEffectId = GetTrailEffectId();
        CreateEffectRef(nEffectId, 0, 0);
    }
    SetEffectScale(0, 0x45000000u);
    return pView;
}

// @ 0x00cce590
bool __cdecl FUN_00cce590()
{
    return GetPauseGateCount(0x64beb65) > 0;
}

// @ 0x00cce5b0
void cSPUITCCCursorStrategy::FUN_00cce5b0()
{
    if (mMode == 1) {
        mMode = 0;
        EndBanMode(1);
    } else {
        mMode = 1;
        ToggleBanningContent(1);
    }
}

// @ 0x00cce5e0
void cSPUITCCCursorStrategy::FUN_00cce5e0()
{
    if (mMode == 2) {
        mMode = 0;
        FUN_00e09a50(0);
    } else {
        mMode = 2;
        FUN_00e099d0(0);
    }
}

// @ 0x00cce940
void cSPUITCCCursorStrategy::FUN_00cce940()
{
    if (mpRef5c) {
        mpRef5c->Reset();
        if (mpRef5c) {
            TcRefObj* old = mpRef5c;
            mpRef5c = 0;
            old->Release3();
        }
    }
    if (mpHandler) {
        void* h = mpHandler;
        mpHandler = 0;
        RemoveHandler(h, mH48, mH4c, mH50, mH54);
    }
    g_msgToken169b1c4 = 0;
    V3<void>(GetServer(), 0x14, 0x706bf688, 0, 0);
}

// @ 0x00cce9b0
u32 __stdcall FUN_00cce9b0(void** vec, void* a, void* b, void* c)
{
    void** it = (void**)vec[0];
    void** end = (void**)vec[1];
    if (it == end)
        return 1;
    do {
        void* o = *it;
        Citizen* cit = o ? (Citizen*)V1<void*>(o, 0xb8, (void*)0x4f176642) : 0;
        cit->GiveOrder(a, b, c);
        ++it;
    } while (it != end);
    return 0;
}

// @ 0x00ccea10
void cSPUITCCCursorStrategy::FUN_00ccea10(void* obj, bool flag)
{
    if ((GetCameraCtl() != 0 && GetCameraCtl()->mMode390 != 0) || flag) {
        mStop.mStart = 0;
        mStop.mStop = 0;
        mStop.mDelta = 0;
        mStop.mPad = 0;
        if (mpRefC0) {
            TcRefObj* old = mpRefC0;
            mpRefC0 = 0;
            old->Release();
        }
    } else {
        mStop.Restart();
        if (obj != 0) {
            TcRefObj* old = mpRefC0;
            if (obj != old) {
                ((TcRefObj*)obj)->AddRef();
                mpRefC0 = (TcRefObj*)obj;
                if (old)
                    old->Release();
            }
            if (V0<void*>(obj, 0x20) == (void*)0x18c88e4 && ((u32*)obj)[0x8a] == 0x356eb8a) {
                old = mpRefC0;
                if (old) {
                    mpRefC0 = 0;
                    old->Release();
                }
            }
        }
    }
}

// @ 0x00ccebd0
u32 cSPUITCCCursorStrategy::FUN_00ccebd0(void* obj, int flag, void* arg3)
{
    if (flag == 0)
        GetGameTerrainCursor()->SetMode(0);
    TerrainCursor* cur = GetGameTerrainCursor();
    void* v = obj ? V1<void*>(obj, 0xc, (void*)0x1186577) : 0;
    V2<void>(cur, 0x9c, 0, v);
    return 0;
}

// @ 0x00ccece0
void ShowSelection(void* pArg1, u32 id, int arg3, float f, char flag)
{
    SelCursor* L = 0;
    IEffectsManager* em = EffectsManager();
    if (L)
    {
        SelCursor* old = L;
        L = 0;
        old->Release();
    }
    if (em->CreateCursor(id, arg3, &L))
    {
        Vec3 vec;
        PlanetModel()->F_00b81630(&vec, pArg1);

        SelRecord rec;
        rec.count = 0;
        rec.scale = 1.0f;
        rec.flags = 0;
        rec.x = g_169b264;
        rec.y = g_169b268;
        rec.z = g_169b26c;
        rec.mat.Ctor(g_169b240);
        rec.flags |= 4;
        rec.count++;
        rec.x = vec.x;
        rec.y = vec.y;
        rec.z = vec.z;

        Vec3 facing;
        if (flag == 0)
        {
            double sum = (double)vec.x * vec.x + (double)vec.y * vec.y + (double)vec.z * vec.z + 1e-8f;
            float s = (float)(1.0 / sqrt(sum));
            facing.x = vec.x * s;
            facing.y = vec.y * s;
            facing.z = vec.z * s;
        }
        else
        {
            Vec3 tmp;
            Vec3* r = PlanetModel()->F_00b7e3b0(&tmp, &vec);
            facing.x = r->x;
            facing.y = r->y;
            facing.z = r->z;
        }

        Vec3 up;
        Mat33 m;
        F_006985b0(&up, &facing);
        F_0069b440(m.m, &up, &facing);
        rec.mat = m;
        rec.flags |= 2;
        rec.count++;
        if (f != 1.0f)
        {
            rec.count++;
            rec.scale = f;
        }
        L->Submit(&rec);
        L->v2(0);
    }
    if (L)
        L->Release();
}

// @ 0x00ccfc20
void CInput::F_ccfc20(void* arg)
{
    StackVec vec;
    vec.init();

    void* tc = GetGameTerrainCursor_s00cc_fc20();
    ((void(__thiscall*)(void*, void*)) (*(void***)tc)[0x5c / 4])(tc, &vec);

    for (void** it = vec.mpBegin; it != vec.mpEnd; ++it) {
        if (*it != 0) {
            void* t = ((void*(__thiscall*)(void*, uint32_t)) (*(void***)*it)[0xb8 / 4])(*it, 0x4f176642);
            if (t != 0)
                ((void(__thiscall*)(void*, void*)) (*(void***)t)[0xf0 / 4])(t, arg);
        }
    }
    for (void** it2 = vec.mpEnd; it2 < vec.mpCap; ++it2) {
        if (*it2 != 0)
            ((void(__thiscall*)(void*)) (*(void***)*it2)[0xc0 / 4])(*it2);
    }

    if (vec.mpBegin != 0 && ((int*)vec.mpBegin)[-1] != 0)
        rt_del_array(vec.mpBegin);
}

// @ 0x00ccfcf0
void CInput::F_ccfcf0(void* vec, int key, void* a, void* b)
{
    if (((CMgr*)this)->M_e9b0(vec, key, a, b) != 0)
        return;

    F_ccfc20((void*)key);

    switch (key) {
    case 0:  { FUN_00435ed0(FUN_00435e90(), 0xa1f51624); return; }
    case 1:  { FUN_00435ed0(FUN_00435e90(), 0xcfd23998); return; }
    case 2:  { FUN_00435ed0(FUN_00435e90(), 0x35988437); return; }
    case 5:  { FUN_00435ed0(FUN_00435e90(), 0x0cc04a90); return; }
    case 7:  { FUN_00435ed0(FUN_00435e90(), 0x0b14abee); return; }
    case 8:  case 15: { FUN_00435ed0(FUN_00435e90(), 0x53eb2296); return; }
    case 9:  case 21: { FUN_00435ed0(FUN_00435e90(), 0x2f154034); return; }
    case 10: { FUN_00435ed0(FUN_00435e90(), 0xf3991445); return; }
    case 11: { FUN_00435ed0(FUN_00435e90(), 0xbfc0a391); return; }
    case 12: { FUN_00435ed0(FUN_00435e90(), 0xebf31cbe); return; }
    case 13: { FUN_00435ed0(FUN_00435e90(), 0x3c9af58a); return; }
    case 14: { FUN_00435ed0(FUN_00435e90(), 0xebb53b1a); return; }
    case 20: { FUN_00435ed0(FUN_00435e90(), 0xc30c84c5); return; }
    case 24: { FUN_00435ed0(FUN_00435e90(), 0x76796a51); return; }
    case 25: { FUN_00435ed0(FUN_00435e90(), 0x92bcb575); return; }
    case 26: { FUN_00435ed0(FUN_00435e90(), 0xf1cc1ac4); return; }
    case 27: { FUN_00435ed0(FUN_00435e90(), 0x8a8e072b); }
    }
}

// @ 0x00ccff40
void FUN_00ccff40()
{
    if (g_ccff40Gate != 0)
        return;

    void* o  = FUN_00b3d240();
    void* ob = ((void*(__thiscall*)(void*)) (*(void***)o)[0x30 / 4])(o);
    uint32_t di = 0;
    if (ob != 0)
        di = (uint32_t)((void*(__thiscall*)(void*, uint32_t)) (*(void***)ob)[0xc / 4])(ob, 0x17f243b);

    uint32_t esi = 0x1002;
    switch (FUN_00ccefb0(ob, 0)) {
    case 0: case 1: break;
    case 2: esi = (uint32_t)((void*(__thiscall*)(void*)) FUN_008013c0)(FUN_0067cab0()); break;
    case 3: case 5: esi = 0x5ecbdffd; break;
    case 4: esi = 0xf212a38b; break;
    case 6: esi = 0xf6879190; break;
    case 7: esi = 0x03a204b0; break;
    case 8: esi = 0x0600cd69; break;
    case 9:  FUN_00b69990((void*)di); esi = 0x0525ff0f; break;
    case 10: case 11: case 12: FUN_00b69990((void*)di); esi = 0x03570021; break;
    case 13: FUN_00b69990((void*)di); esi = 0xf59ce677; break;
    case 14: FUN_00b69990(FUN_00ac80d0((void*)di, 0x1e4daae)); esi = 0x8b875bdc; break;
    case 15: FUN_00b69990(FUN_00ac80d0((void*)di, 0x1e4daae)); break;
    case 16: FUN_00b69990((void*)di); esi = 0x8b875bdc; break;
    case 17: FUN_00b69990((void*)di); esi = 0x03febe37; break;
    case 18: FUN_00b69990((void*)di); esi = 0x03febe38; break;
    case 19: FUN_00b69990((void*)di); esi = 0x063fe8d9; break;
    case 20: FUN_00b69990((void*)di); esi = 0x063fe8d7; break;
    case 21: FUN_00b69990((void*)di); esi = 0x063fe8d8; break;
    case 22: FUN_00b69990((void*)di); esi = 0x063fe8d5; break;
    case 23: FUN_00b69990((void*)di); esi = 0x063fe8d4; break;
    case 24: FUN_00b69990((void*)di); esi = 0x063fe8d6; break;
    case 25: FUN_00b69990((void*)di); esi = 0x03febe3b; break;
    case 26: FUN_00b69990((void*)di); esi = 0x03febe3d; break;
    case 27: case 28: case 29: case 35: case 36: case 37:
        esi = 0x03febe40; break;
    case 30: esi = 0x03febe51; break;
    case 31: esi = 0x03febe50; break;
    case 32: esi = 0x03febe52; break;
    case 33: esi = 0x03febe42; break;
    case 34: esi = 0x03febe3f; break;
    case 38: {
        void* o2 = ((void*(__thiscall*)(void*)) FUN_00bfc5f0)(FUN_00b3d300());
        FUN_00b69990(((void*(__thiscall*)(void*)) (*(void***)o2)[0xac / 4])(o2));
        break;
    }
    case 39: case 43: case 45: FUN_00b69990((void*)di); esi = 0x0525ff7d; break;
    case 40: FUN_00b69990((void*)di); esi = 0x03febe33; break;
    case 41: FUN_00b69990((void*)di); esi = 0xe382f00e; break;
    case 42: case 44: case 46: FUN_00b69990((void*)di); break;
    case 47: FUN_00b69990((void*)di); esi = 0x0648fbf1; break;
    }

    if ((uint32_t)((void*(__thiscall*)(void*)) FUN_008013c0)(FUN_0067cab0()) != esi)
        ((unsigned char(__thiscall*)(void*, uint32_t)) FUN_00801bb0)(FUN_0067cab0(), esi);
}
