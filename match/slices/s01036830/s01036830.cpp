// Slice s01036830 -- SP::cSPSpaceGfx space-effect start/stop/transform helpers plus the
// space-stage shutdown path and the alliance-graph rebuild.
//
//  01036830  cSPSpaceGfx::SetEffectEnabled        (start/stop the ambience effect set)
//  01036940  cSPSpaceGfx::UpdateSpaceColor        (sample the space tint from the color table)
//  01036af0  cSPSpaceGfx::UpdateAllianceGraph     (refresh the alliance map from the colony map)
//  01036c20  cSPSimulatorSpaceGame::SolarContextFinishActivate (solar/LOD context switch)
//  01036d30  cSPSpaceGfx::SetEffectTransform      (place a visual effect at a position)
//  01036e20  cSPSpaceGfx::FindSpaceStation        (locate the first matching space object)
//  01036fc0  eastl::rbtree<...>::DoNukeSubtree
//  01037030  cSPSpaceGfx::~cSPSpaceGfx
//  010372b0  cSPSpaceGfx::ShutdownForGame
//  01037700  cSPSpaceGfx::AllianceGraphCreate
//  01037760  SP::AllianceGraphUpdate
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

struct Vec3 { float x, y, z; };

// Row-major 3x3 basis.  The copy constructor is out of line in retail (0x0041cb40, ret 4).
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& src);              // 0x0041cb40
};

// The effect transform handed to cIVisualEffect::SetTransform.
struct Transform {
    uint16_t mFlags;                          // +0x00
    uint16_t mnChangeCount;                   // +0x02
    Vec3     mPosition;                       // +0x04
    float    mfScale;                         // +0x10
    Matrix3  mOrientation;                    // +0x14
};

namespace EA { namespace Swarm {
class cIVisualEffect {
public:
    virtual int  AddRef();                             // +0x00
    virtual int  Release();                            // +0x04
    virtual bool Start(int flags);                     // +0x08
    virtual bool Stop(int flags);                      // +0x0c
    virtual void _v10();                               // +0x10
    virtual void SetTransform(const ::Transform& xform); // +0x14
};

// Effects world: slot 0x18 applies a named effect, slot 0x7c tears down.
class cIEffectsWorld {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14();
    virtual void ApplyByName(void* name);              // +0x18
    virtual void _v1c();
    virtual void _v7c();
};
}}

class cIVisualEffectBig {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual bool _v10b();                              // +0x10
    virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40();
    virtual void Apply(int a, void* p, int b);         // +0x44
};

// The effect manager service (SP::EffectsManager).
struct cEffectsManager {
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4c();
    virtual void ReleaseEffect(uint32_t id);           // +0x50
};

// map node used by the colony-model map (eastl::rbtree<SP::cPlanet*, EA::AutoRefCount<SP::cMWModel> >).
struct ColonyNode {
    ColonyNode* mpLeft;      // +0x00
    ColonyNode* mpRight;     // +0x04
    ColonyNode* mpParent;    // +0x08
    uint8_t     mbColor;     // +0x0c
    uint8_t     pad0d[3];
    uint32_t    mu10;        // +0x10
    void*       mpData;      // +0x14  EA::AutoRefCount<SP::cMWModel> payload
};

struct RBNode;

struct ColonyMap {
    uint32_t mu00;       // +0x00
    void*    mpHead;     // +0x04
    void*    mpBegin;    // +0x08
    void*    mpRoot;     // +0x0c
    uint8_t  mb10;       // +0x10
    uint8_t  pad11[3];
    void*    mp14;       // +0x14
    void DoNukeSubtree(RBNode* pNode);   // 0x01036fc0
};

// ---------------------------------------------------------------------------------------------
// SP::cSPSpaceGfx (retail layout; the dev PDB tail is shifted, so the extra retail members are
// named by role/offset).
class cSPSpaceGfx {
public:
    // base cGonzagoSubsystem: IUnknown32 (AddRef/Release/QueryInterface) + cIGonzagoSubsystem vtable.
    virtual int  AddRef();                             // +0x00 (slot 1)
    virtual int  Release();                            // +0x04 (slot 2)
    virtual ~cSPSpaceGfx();                            // 0x01037030

    // cGonzagoSubsystem base data (vptr + 0x18 bytes of base state).
    uint8_t mBaseData[0x18];                           // +0x04

    void SetEffectEnabled(char enable);                // 0x01036830
    void UpdateSpaceColor(float x, float y, float z);  // 0x01036940
    void SetEffectTransform(Vec3 position);            // 0x01036d30
    void ShutdownForGame();                            // 0x010372b0
    void AllianceGraphCreate();                        // 0x01037700

    // AutoRefCount<EA::Swarm::cIVisualEffect> galaxy effects
    void* mpGalaxyCrossfadeEffect;                     // +0x1c
    void* mpGalaxyEffect;                              // +0x20
    void* mpGalaxyScreenEffect;                        // +0x24
    void* mpGalaxyAmbienceEffect;                      // +0x28
    void* mpGalaxyBackgroundGalaxies;                  // +0x2c
    void* mpTravelLineEffect;                          // +0x30
    void* mpSporepediaPlotPathEffect;                  // +0x34
    void* mpTravelLineStar;                            // +0x38
    ColonyMap mColonyModelMap;                         // +0x3c
    uint8_t pad54[4];                                  // +0x54
    bool  mbAllianceMapVisible;                        // +0x58
    bool  mbColonyMapIsDirty;                          // +0x59
    uint8_t pad5a[2];                                  // +0x5a
    void* mpPlanetScreenEffect;                        // +0x5c
    void* mpLavaPlanetScreenEffect;                    // +0x60
    void* mpSkyboxEffect;                              // +0x64
    void* mpSolarScreenEffect;                         // +0x68
    void* mpSolarClouds;                               // +0x6c
    void* mpSolarLoopbox;                              // +0x70
    void* mpSolarBackgroundEffect;                     // +0x74
    void* mpSolarBackgroundDustEffect;                 // +0x78
    void* mpPlanetBackgroundEffect;                    // +0x7c
    void* mpPlanetBackgroundDustEffect;                // +0x80
    void* mpSolarComets;                               // +0x84
    void* mpMeaningOfLifeEffect;                       // +0x88
    void* mpRingEffect;                                // +0x8c
    void* mpSolarEffectsWorld;                         // +0x90
    void* mpTrailEffectsWorld;                         // +0x94
    void* mpPtolemaicEffectsWorld;                     // +0x98
    void* mpPtolemaicEffectsRenderer;                  // +0x9c
    void* mpSolarBackgroundEffectsWorld;               // +0xa0
    void* mpSolarBackgroundRenderer;                   // +0xa4
    void* mpEffectA8;                                  // +0xa8
    void* mpGalaxyEffectsWorld;                        // +0xac
    void* mpMoneyEffectPlanet;                         // +0xb0
    void* mpMoneyEffectUFO;                            // +0xb4
    void* mpEffectB8;                                  // +0xb8
    void* mpEffectBC;                                  // +0xbc
    void* mpEffectC0;                                  // +0xc0
    void* mpEffectC4;                                  // +0xc4
    uint8_t mTimerC8[0x38];                            // +0xc8  SP::cGonzagoTimer
    bool  mb100;                                       // +0x100
    uint8_t pad101[0x0f];                              // +0x101
    Vec3  mSpaceColor;                                 // +0x110
    Vec3  mPrevColor;                                  // +0x11c
    int   mn128;                                       // +0x128
    uint8_t pad12c[0x10];                              // +0x12c
    void* mp13c;                                       // +0x13c
};

// ---------------------------------------------------------------------------------------------
// free functions
extern "C" void* FUN_01021230();                       // 0x01021230  effect owner (this)
extern "C" Vec3* FUN_00c8b360(void* p);                 // 0x00c8b360  return &p->mPosition
void* GetSpaceGfx();                                   // 0x00b3d470  SP::cSPSpaceGfx::Get()
void* GetSpaceGfx2();                                  // 0x00b3d240
cEffectsManager* EffectsManagerPtr();                  // 0x0067ddd0  SP::EffectsManager()
void* SpaceApp();                                      // 0x0067dd10  SP::App
void* GetResourceManager();                            // 0x0067dcd0  EA::ResourceMan::GetManager
void* RBTreeIncrement(void* pNode);                    // 0x00921580
void* operator_delete_array(void* p);                  // 0x00f47380
void Matrix3Assign(Matrix3& dst, const void* src);     // 0x0041cb40
float FUN_01036610(uint32_t param);                    // 0x01036610
void  FUN_010367e0(void* p, int flag);                 // 0x010367e0
void  TimerOwnerDtor(void* p);                         // 0x00af1430  ?Dtor@TimerOwner
void  FUN_01036c8b(void* p);                           // (placeholder, unused)
void  FUN_007c3ba0(void* p);                           // 0x007c3ba0
void  SetViewAngle(float angle);                       // 0x007c5350  cViewer::SetViewAngle
void  FUN_007c46f0(void* a, void* b);                  // 0x007c46f0
int   FUN_00c6ff90(void* p);                           // 0x00c6ff90

// shared constants
extern const float kOne;              // 0x01485720  1.0f
extern const float kColorScale;       // 0x013eecd4  1/255
extern const float kHalfRange;        // 0x013ec5b4
float kFullRange;                      // 0x013f999c  (placeholder)
extern const Matrix3 kIdentityMatrix;  // 0x016df384

// 0x0136df3a8 area: effect color defaults
extern const float kGalaxyOffsetA; // 0x016df3a8
extern const float kGalaxyOffsetB; // 0x016df3ac
extern const float kGalaxyOffsetC; // 0x016df3b0
extern const float kThresh144;     // 0x014998fc  144.0f
extern const float kThresh500;     // 0x01465544  500.0f
extern const float kPickA;  // 0x016df344
extern const float kPickB;  // 0x016df348
extern const float kPickC;  // 0x016df34c
extern const float kE2029;  // 0x013eecd4
extern const float k0_0005; // 0x013f999c

// resource key used by UpdateSpaceColor
struct ResourceManKey {
    uint32_t mId;        // +0x00
    uint32_t mType;      // +0x04
    uint32_t mOwner;     // +0x08
};

struct ResourceManager {
    virtual void _v00(); virtual void _v04(); virtual void _v08();
    virtual bool Find(ResourceManKey* pKey, void** ppOut,
                      uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // +0x0c
};

// A loaded texture/resource with colored data.
struct ColorResource {
    uint8_t pad00[0x1c];
    int   mWidth;        // +0x1c
    int   mHeight;       // +0x20
    uint8_t* mpData;     // +0x28
};

// ---------------------------------------------------------------------------------------------
// 01036830
// @ 0x01036830
void cSPSpaceGfx::SetEffectEnabled(char enable)
{
    if (enable == 0) {
        ((EA::Swarm::cIVisualEffect*)mpGalaxyEffectsWorld)->Stop(2);
        if (mpGalaxyCrossfadeEffect != 0)
            ((EA::Swarm::cIVisualEffect*)mpGalaxyCrossfadeEffect)->Stop(1);
        return;
    }
    ((EA::Swarm::cIVisualEffect*)mpGalaxyEffectsWorld)->Stop(0);
    ((EA::Swarm::cIVisualEffect*)mpGalaxyScreenEffect)->Start(1);
    ((EA::Swarm::cIVisualEffect*)mpGalaxyBackgroundGalaxies)->Start(0);
    if (mpGalaxyCrossfadeEffect != 0)
        ((EA::Swarm::cIVisualEffect*)mpGalaxyCrossfadeEffect)->Start(0);

    Transform xform;
    xform.mFlags = 0;
    xform.mnChangeCount = 0;
    xform.mPosition.x = kGalaxyOffsetA;
    xform.mPosition.y = kGalaxyOffsetB;
    xform.mPosition.z = kGalaxyOffsetC;
    xform.mfScale = kOne;
    Matrix3Assign(xform.mOrientation, &kIdentityMatrix);

    void* pOwner = FUN_01021230();    Vec3* pPos = FUN_00c8b360(pOwner);
    xform.mPosition = *pPos;
    xform.mFlags |= 4;
    xform.mnChangeCount++;
    ((EA::Swarm::cIVisualEffect*)mpPlanetBackgroundDustEffect)->SetTransform(xform);
}

// @ 0x01036940
void cSPSpaceGfx::UpdateSpaceColor(float x, float y, float z)
{
    if (mpPlanetBackgroundDustEffect == 0 && mpMeaningOfLifeEffect == 0)
        return;

    ResourceManKey key;
    key.mId = 0xafa8deb9;
    key.mType = 0x3e421ed;
    key.mOwner = 0;
    void* pRes = 0;
    ResourceManager* pMgr = (ResourceManager*)GetResourceManager();
    if (pRes != 0) {
        pRes = 0;
        ((EA::Swarm::cIVisualEffect*)0)->Release();
    }
    if (!pMgr->Find(&key, &pRes, 0, 0, 0, 0)) {
        if (pRes != 0)
            ((EA::Swarm::cIVisualEffect*)pRes)->Release();
        return;
    }

    ColorResource* pColor = (ColorResource*)pRes;
    mPrevColor = mSpaceColor;

    int width  = pColor->mWidth;      // +0x1c
    int height = pColor->mHeight;     // +0x20
    uint8_t* pData = pColor->mpData;  // +0x28
    int xi = (int)((x + 1000.0f) * (float)width  * 0.0005f);
    int yi = (int)((z + 1000.0f) * (float)height * 0.0005f);
    uint8_t* pPixel = pData + (yi * width + xi) * 4;
    mSpaceColor.x = (float)pPixel[2] * kColorScale;
    mSpaceColor.y = (float)pPixel[1] * kColorScale;
    mSpaceColor.z = (float)pPixel[0] * kColorScale;
    mn128 = 0;

    if (mpMeaningOfLifeEffect != 0) {
        if (((cIVisualEffectBig*)mpMeaningOfLifeEffect)->_v10b())
            ((cIVisualEffectBig*)mpMeaningOfLifeEffect)->Apply(5, &mSpaceColor, 3);
    }

    if (pRes != 0)
        ((EA::Swarm::cIVisualEffect*)pRes)->Release();
}

// ---------------------------------------------------------------------------------------------
// interfaces used by the effect-refresh / solar-context paths
struct cEffectByName {                                  // slots 0x10 / 0x18 / 0x40
    virtual void _v00();
    virtual int  _v04release();                        // +0x04
    virtual void _v08start(int flags);                 // +0x08
    virtual void _v0c();
    virtual bool _v10b();                              // +0x10
    virtual void _v14SetTransform(void* xform);        // +0x14
    virtual void ApplyByName(void* name);              // +0x18
    virtual void _v1c(); virtual void _v20(); virtual void _v24(); virtual void _v28();
    virtual void _v2c(); virtual void _v30(); virtual void _v34(); virtual void _v38();
    virtual void _v3c();
    virtual void SetEffectIndexed(int a, void* b);     // +0x40
};

struct cEffectByKey {                                  // slot 0x2c -> returns a Vector3
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28();
    virtual Vec3* GetPosition();                       // +0x2c
};

struct cEffect34 {                                     // slot 0x2c -> Vector3
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28();
    virtual Vec3* GetPosition(int index);              // +0x2c
};

// Effects-time state at singleton +0xb8/0xbc/0xc0
struct cEffectC0 {
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30();
    void* mp34;                                        // +0x34
};

// @ 0x01036af0
void FUN_01036af0()
{
    cSPSpaceGfx* pGfx = (cSPSpaceGfx*)GetSpaceGfx();
    if (pGfx->mpEffectB8 == 0)
        return;

    if (!((cEffectByName*)pGfx->mpEffectB8)->_v10b()) {
        if (pGfx->mpEffectB8 != 0) {
            void* p = pGfx->mpEffectB8;
            pGfx->mpEffectB8 = 0;
            ((cEffectByName*)p)->_v04release();
        }
        pGfx->mpEffectBC = 0;
        if (pGfx->mpEffectC0 != 0) {
            void* p = pGfx->mpEffectC0;
            pGfx->mpEffectC0 = 0;
            ((cEffectByName*)p)->_v04release();
        }
        return;
    }

    Transform xform;
    xform.mFlags = 0;
    xform.mnChangeCount = 0;
    xform.mPosition.x = kGalaxyOffsetA;
    xform.mPosition.y = kGalaxyOffsetB;
    xform.mPosition.z = kGalaxyOffsetC;
    xform.mfScale = kOne;
    Matrix3Assign(xform.mOrientation, &kIdentityMatrix);

    Vec3* pPos = ((cEffectByKey*)pGfx->mpEffectBC)->GetPosition();
    xform.mPosition = *pPos;
    xform.mFlags |= 4;
    xform.mnChangeCount++;
    ((cEffectByName*)pGfx->mpEffectB8)->ApplyByName(&xform);

    void* pC0 = pGfx->mpEffectC0;
    void* pB8 = pGfx->mpEffectB8;
    Vec3* pPos2 = ((cEffect34*)((cEffectC0*)pC0)->mp34)->GetPosition(1);
    ((cEffectByName*)pB8)->SetEffectIndexed(9, pPos2);
}

// ---------------------------------------------------------------------------------------------
// SP::cSPSimulatorSpaceGame -- the solar/LOD context switch member used by 01036c20.
class cSPSimulatorSpaceGame {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4c();
    virtual void _v50(); virtual void _v54(); virtual void _v58();
    void SolarContextFinishActivate(float value, char active);  // 0x01036c20
    int   mpSelectedBuilding;                          // +0x5c
    uint8_t pad60[0x1c];                               // +0x60
    void* mpHighLODPlanetSim;                          // +0x7c
    uint8_t pad80[0x24];                               // +0x80
    void* mpCivTransitionMiniGame;                     // +0xa4
};

struct cIVisualEffectHost {
    virtual void _v00();
    virtual int  _v04release();                        // +0x04
    virtual void _v08();
    virtual int  _v0cstop(int arg);                    // +0x0c
};

struct cMiniGame {                                     // slot 0x08 takes (int,int,void**)
    virtual void _v00(); virtual void _v04();
    virtual void Switch(int a, int b, void** ppOut);    // +0x08
};

// Register a timer/sound event by name; slot 0x10 tears down, 0x44 emits.
struct cGonzagoTimerHost {
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual int  _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40();
    virtual void Emit(int a, void* b, int c);          // +0x44
};

// @ 0x01036c20
void cSPSimulatorSpaceGame::SolarContextFinishActivate(float value, char active)
{
    int context;
    if (value < kThresh144)
        context = 0;
    else if (value < kThresh500)
        context = 1;
    else
        context = 2;

    if (mpSelectedBuilding == context)
        return;

    if (!active)
        goto set;

    {
        void* pHighLOD = mpHighLODPlanetSim;
        if (pHighLOD != 0) {
            ((cIVisualEffectHost*)pHighLOD)->_v0cstop(0);
            pHighLOD = mpHighLODPlanetSim;
            if (pHighLOD != 0) {
                mpHighLODPlanetSim = 0;
                ((cIVisualEffectHost*)pHighLOD)->_v04release();
            }
        }
        cMiniGame* pMini = (cMiniGame*)mpCivTransitionMiniGame;
        cSPSpaceGfx* pGfx = (cSPSpaceGfx*)GetSpaceGfx();
        void** ppSlot = &pGfx->mpPlanetBackgroundEffect;   // singleton +0x7c

        if (context == 0) {
            if (*ppSlot != 0) {
                void* p = *ppSlot;
                *ppSlot = 0;
                ((cIVisualEffectHost*)p)->_v04release();
            }
            pMini->Switch(0x3eac08d, 0, ppSlot);
            mpSelectedBuilding = 0;
            return;
        }
        if (context == 1) {
            if (*ppSlot != 0) {
                void* p = *ppSlot;
                *ppSlot = 0;
                ((cIVisualEffectHost*)p)->_v04release();
            }
            pMini->Switch(0x3eac08a, 0, ppSlot);
            mpSelectedBuilding = 1;
            return;
        }
        if (*ppSlot != 0) {
            void* p = *ppSlot;
            *ppSlot = 0;
            ((cIVisualEffectHost*)p)->_v04release();
        }
        pMini->Switch(0x3eac086, 0, ppSlot);
    }
set:
    mpSelectedBuilding = context;
}

// @ 0x01036d30
void cSPSpaceGfx::SetEffectTransform(Vec3 position)
{
    if (mpPlanetBackgroundDustEffect == 0)
        return;

    if (!((cEffectByName*)mpPlanetBackgroundDustEffect)->_v10b()) {
        ((cEffectByName*)mpPlanetBackgroundDustEffect)->_v08start(0);
        UpdateSpaceColor(position.x, position.y, position.z);
    }

    Transform xform;
    xform.mFlags = 0;
    xform.mnChangeCount = 0;
    xform.mPosition.x = kGalaxyOffsetA;
    xform.mPosition.y = kGalaxyOffsetB;
    xform.mPosition.z = kGalaxyOffsetC;
    xform.mfScale = kOne;
    Matrix3Assign(xform.mOrientation, &kIdentityMatrix);

    xform.mPosition = position;
    xform.mFlags |= 4;
    xform.mnChangeCount++;
    ((cEffectByName*)mpPlanetBackgroundDustEffect)->_v14SetTransform(&xform);
}

// ---------------------------------------------------------------------------------------------
// The find-space-station search (01036e20).
struct cFound {
    virtual void _v00(); virtual void _v04(); virtual void _v08();
    virtual void* FindName(uint32_t name);             // +0x0c
};

struct cSearchElem {
    uint8_t pad00[0x64];
    cFound* mp64;                                      // +0x64
};

struct cSearchSource {                                 // FUN_00b3d240 result
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30();
    virtual void Collect(cSearchElem*** ppBegin, cSearchElem*** ppEnd, int a, int b); // +0x34
    virtual void GetProbe(Vec3* pOut, int a, Vec3 in); // +0x38
    virtual void _v3c(); virtual void _v40(); virtual void _v44(); virtual void _v48();
    virtual void _v4c(); virtual void _v50(); virtual void _v54(); virtual void _v58();
    virtual void _v5c(); virtual void _v60(); virtual void _v64(); virtual void _v68();
    virtual void _v6c();
    virtual cSearchSource* GetInner();                 // +0x70
};

// @ 0x01036e20
int FUN_01036e20()
{
    cSearchSource* pSource = (cSearchSource*)GetSpaceGfx2();
    Vec3 probe;
    probe.x = kPickA;
    probe.y = kPickB;
    probe.z = kPickC;
    pSource->GetProbe(&probe, 0, probe);               // slot 0x38

    if (probe.x != kPickA || probe.y != kPickB || probe.z != kPickC)
        return 0;

    uint8_t scratch1[64];
    uint8_t scratch2[32];
    FUN_007c46f0(scratch2, scratch1);

    cSearchSource* pSource2 = (cSearchSource*)GetSpaceGfx2();
    cSearchSource* pInner = pSource2->GetInner();

    cSearchElem** pBegin = 0;
    cSearchElem** pEnd = 0;
    cSearchElem** pCap = 0;
    uint8_t flags[8];
    flags[0] = 0;
    flags[1] = 1;
    pInner->Collect(&pBegin, &pEnd, 0, 0);

    cSearchElem** pIt = pBegin;
    if (pBegin != pEnd) {
        do {
            cSearchElem* pElem = *pIt;
            cFound* pFound = pElem->mp64;
            if (pFound != 0) {
                void* pObj = pFound->FindName(0x3275872);
                if (pObj != 0 && FUN_00c6ff90(pObj) == 2) {
                    if (pBegin != 0 && pBegin != pCap)
                        operator_delete_array(pBegin);
                    return (int)pObj;
                }
            }
            ++pIt;
        } while (pIt != pEnd);
    }

    if (pBegin != 0 && pBegin != pCap)
        operator_delete_array(pBegin);
    return 0;
}

// ---------------------------------------------------------------------------------------------
// The colony-model map node value refcount holder (EA::AutoRefCount<SP::cMWModel>).
struct cMWModel {
    PV16 PV16 PV16 PV16 PV16 PV8 PV4
    uint32_t mu04;                                     // +0x04
    uint8_t  pad08[0x38];                              // +0x08
    int  mRefCount;                                    // +0x40
    virtual void Destroy(int flags);                   // +0x170
};

struct RBNode {
    RBNode*  mpLeft;      // +0x00
    RBNode*  mpRight;     // +0x04
    RBNode*  mpParent;    // +0x08
    uint8_t  mbColor;     // +0x0c
    uint8_t  pad0d[3];    // +0x0d
    uint32_t mu10;        // +0x10
    cMWModel* mpValue;    // +0x14  AutoRefCount<SP::cMWModel>
};

// @ 0x01036fc0
void ColonyMap::DoNukeSubtree(RBNode* pNode)
{
    while (pNode != 0) {
        DoNukeSubtree(pNode->mpLeft);
        cMWModel* pValue = pNode->mpValue;
        RBNode* pRight = pNode->mpRight;
        if (pValue != 0) {
            if (pValue->mRefCount > 1) {
                pValue->mRefCount--;
            } else {
                pValue->Destroy((pValue->mu04 >> 31) & 1);
            }
        }
        operator_delete_array(pNode);
        pNode = pRight;
    }
}

// ---------------------------------------------------------------------------------------------
// 01037030 -- cSPSpaceGfx destructor, then 010372b0 -- ShutdownForGame,
// 01037700 -- AllianceGraphCreate, 01037760 -- AllianceGraphUpdate.
//
// @ 0x01037030
cSPSpaceGfx::~cSPSpaceGfx()
{
    if (mp13c != 0)
        ((cEffectByName*)mp13c)->_v04release();
    TimerOwnerDtor(mTimerC8);
    if (mpEffectC4 != 0) ((cEffectByName*)mpEffectC4)->_v04release();
    if (mpEffectC0 != 0) ((cEffectByName*)mpEffectC0)->_v04release();
    if (mpEffectB8 != 0) ((cEffectByName*)mpEffectB8)->_v04release();
    if (mpMoneyEffectUFO != 0) ((cEffectByName*)mpMoneyEffectUFO)->_v04release();
    if (mpMoneyEffectPlanet != 0) ((cEffectByName*)mpMoneyEffectPlanet)->_v04release();
    if (mpGalaxyEffectsWorld != 0) ((cEffectByName*)mpGalaxyEffectsWorld)->_v04release();
    if (mpGalaxyEffectsWorld != 0) ((cEffectByName*)mpGalaxyEffectsWorld)->_v04release();
    if (mpSolarBackgroundRenderer != 0) ((cEffectByName*)mpSolarBackgroundRenderer)->_v04release();
    if (mpSolarBackgroundEffectsWorld != 0) ((cEffectByName*)mpSolarBackgroundEffectsWorld)->_v04release();
    if (mpPtolemaicEffectsRenderer != 0) ((cEffectByName*)mpPtolemaicEffectsRenderer)->_v04release();
    if (mpPtolemaicEffectsWorld != 0) ((cEffectByName*)mpPtolemaicEffectsWorld)->_v04release();
    if (mpTrailEffectsWorld != 0) ((cEffectByName*)mpTrailEffectsWorld)->_v04release();
    if (mpSolarEffectsWorld != 0) ((cEffectByName*)mpSolarEffectsWorld)->_v04release();
    if (mpRingEffect != 0) ((cEffectByName*)mpRingEffect)->_v04release();
    if (mpMeaningOfLifeEffect != 0) ((cEffectByName*)mpMeaningOfLifeEffect)->_v04release();
    if (mpSolarComets != 0) ((cEffectByName*)mpSolarComets)->_v04release();
    if (mpPlanetBackgroundDustEffect != 0) ((cEffectByName*)mpPlanetBackgroundDustEffect)->_v04release();
    if (mpPlanetBackgroundEffect != 0) ((cEffectByName*)mpPlanetBackgroundEffect)->_v04release();
    if (mpSolarBackgroundDustEffect != 0) ((cEffectByName*)mpSolarBackgroundDustEffect)->_v04release();
    if (mpSolarBackgroundEffect != 0) ((cEffectByName*)mpSolarBackgroundEffect)->_v04release();
    if (mpSolarLoopbox != 0) ((cEffectByName*)mpSolarLoopbox)->_v04release();
    if (mpSolarClouds != 0) ((cEffectByName*)mpSolarClouds)->_v04release();
    if (mpSolarScreenEffect != 0) ((cEffectByName*)mpSolarScreenEffect)->_v04release();
    if (mpSkyboxEffect != 0) ((cEffectByName*)mpSkyboxEffect)->_v04release();
    if (mpLavaPlanetScreenEffect != 0) ((cEffectByName*)mpLavaPlanetScreenEffect)->_v04release();
    if (mpPlanetScreenEffect != 0) ((cEffectByName*)mpPlanetScreenEffect)->_v04release();
    mColonyModelMap.DoNukeSubtree((RBNode*)mColonyModelMap.mpRoot);
    if (mpSporepediaPlotPathEffect != 0) ((cEffectByName*)mpSporepediaPlotPathEffect)->_v04release();
    if (mpTravelLineEffect != 0) ((cEffectByName*)mpTravelLineEffect)->_v04release();
    if (mpGalaxyBackgroundGalaxies != 0) ((cEffectByName*)mpGalaxyBackgroundGalaxies)->_v04release();
    if (mpGalaxyAmbienceEffect != 0) ((cEffectByName*)mpGalaxyAmbienceEffect)->_v04release();
    if (mpGalaxyScreenEffect != 0) ((cEffectByName*)mpGalaxyScreenEffect)->_v04release();
    if (mpGalaxyEffect != 0) ((cEffectByName*)mpGalaxyEffect)->_v04release();
    if (mpGalaxyCrossfadeEffect != 0) ((cEffectByName*)mpGalaxyCrossfadeEffect)->_v04release();
}

// ---------------------------------------------------------------------------------------------
// A wide effect interface reachable at slot 0x7c and slot 0x16c.
struct cEffectFull {
    virtual void _v00(); virtual void _v04(); virtual void _v08();
    virtual void _v0cStop(int arg);                    // +0x0c
    PV16 PV8 PV2 PV                                     // slots 4..30
    virtual void _v7c();                               // +0x7c
    PV16 PV16 PV16 PV8 PV2 PV                           // slots 32..90
    virtual void _v16c(int arg);                       // +0x16c
};

// The effects manager (already declared) and SP::App.
struct cApp {
    PV16 PV4
    virtual void* GetSubSystem();                      // +0x50
};

struct cViewer {
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18();
    virtual void SetViewAngle(float angle);            // (method, 0x007c5350)
};

struct cModelNodeValue {
    uint8_t pad00[0x58];
    float   mf58;                                      // +0x58
};

extern const float kViewAngle;                         // 0x014998d4

struct cSubSys {
    PV4 PV2
    virtual void* GetViewer();                         // +0x1c
};

// @ 0x010372b0
void cSPSpaceGfx::ShutdownForGame()
{
    if (!mb100)
        return;
    mb100 = false;

    if (mp13c != 0) {
        void* p = mp13c;
        mp13c = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpSolarClouds != 0)
        ((cEffectFull*)mpSolarClouds)->_v0cStop(1);
    if (mpSolarClouds != 0) {
        void* p = mpSolarClouds;
        mpSolarClouds = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpGalaxyCrossfadeEffect != 0)
        ((cEffectFull*)mpGalaxyCrossfadeEffect)->_v0cStop(1);
    if (mpGalaxyCrossfadeEffect != 0) {
        void* p = mpGalaxyCrossfadeEffect;
        mpGalaxyCrossfadeEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpGalaxyEffect != 0)
        ((cEffectFull*)mpGalaxyEffect)->_v0cStop(1);
    if (mpGalaxyEffect != 0) {
        void* p = mpGalaxyEffect;
        mpGalaxyEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpGalaxyAmbienceEffect != 0)
        ((cEffectFull*)mpGalaxyAmbienceEffect)->_v0cStop(1);
    if (mpGalaxyAmbienceEffect != 0) {
        void* p = mpGalaxyAmbienceEffect;
        mpGalaxyAmbienceEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpPlanetBackgroundEffect != 0)
        ((cEffectFull*)mpPlanetBackgroundEffect)->_v0cStop(1);
    if (mpPlanetBackgroundEffect != 0) {
        void* p = mpPlanetBackgroundEffect;
        mpPlanetBackgroundEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpPlanetBackgroundDustEffect != 0)
        ((cEffectFull*)mpPlanetBackgroundDustEffect)->_v0cStop(1);
    if (mpPlanetBackgroundDustEffect != 0) {
        void* p = mpPlanetBackgroundDustEffect;
        mpPlanetBackgroundDustEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpRingEffect != 0)
        ((cEffectFull*)mpRingEffect)->_v0cStop(1);
    if (mpRingEffect != 0) {
        void* p = mpRingEffect;
        mpRingEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpSolarComets != 0)
        ((cEffectFull*)mpSolarComets)->_v0cStop(1);
    if (mpSolarComets != 0) {
        void* p = mpSolarComets;
        mpSolarComets = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpMeaningOfLifeEffect != 0)
        ((cEffectFull*)mpMeaningOfLifeEffect)->_v0cStop(1);
    if (mpMeaningOfLifeEffect != 0) {
        void* p = mpMeaningOfLifeEffect;
        mpMeaningOfLifeEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpTravelLineEffect != 0)
        ((cEffectFull*)mpTravelLineEffect)->_v0cStop(1);
    if (mpTravelLineEffect != 0) {
        void* p = mpTravelLineEffect;
        mpTravelLineEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }
    mpTravelLineStar = 0;
    if (mpSporepediaPlotPathEffect != 0)
        ((cEffectFull*)mpSporepediaPlotPathEffect)->_v0cStop(1);
    if (mpSporepediaPlotPathEffect != 0) {
        void* p = mpSporepediaPlotPathEffect;
        mpSporepediaPlotPathEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }

    ((cEffectFull*)mpGalaxyEffectsWorld)->_v0cStop(2);
    ((cEffectFull*)mpPtolemaicEffectsWorld)->_v0cStop(2);
    ((cEffectFull*)mpTrailEffectsWorld)->_v0cStop(2);
    ((cEffectFull*)mpPtolemaicEffectsRenderer)->_v0cStop(2);
    ((cEffectFull*)mpSolarBackgroundRenderer)->_v0cStop(2);
    ((cEffectFull*)mpMoneyEffectPlanet)->_v0cStop(2);

    EffectsManagerPtr()->ReleaseEffect(0x17f40c9);
    if (mpGalaxyEffectsWorld != 0) { void* p = mpGalaxyEffectsWorld; mpGalaxyEffectsWorld = 0; ((cEffectByName*)p)->_v04release(); }
    EffectsManagerPtr()->ReleaseEffect(0x17f40c7);
    if (mpTrailEffectsWorld != 0) { void* p = mpTrailEffectsWorld; mpTrailEffectsWorld = 0; ((cEffectByName*)p)->_v04release(); }
    EffectsManagerPtr()->ReleaseEffect(0x17f40c8);
    if (mpPtolemaicEffectsWorld != 0) { void* p = mpPtolemaicEffectsWorld; mpPtolemaicEffectsWorld = 0; ((cEffectByName*)p)->_v04release(); }
    EffectsManagerPtr()->ReleaseEffect(0x26f8fcb);
    if (mpPtolemaicEffectsRenderer != 0) { void* p = mpPtolemaicEffectsRenderer; mpPtolemaicEffectsRenderer = 0; ((cEffectByName*)p)->_v04release(); }
    EffectsManagerPtr()->ReleaseEffect(0x284e479);
    if (mpSolarBackgroundRenderer != 0) { void* p = mpSolarBackgroundRenderer; mpSolarBackgroundRenderer = 0; ((cEffectByName*)p)->_v04release(); }
    EffectsManagerPtr()->ReleaseEffect(0x67247e6);
    if (mpMoneyEffectPlanet != 0) { void* p = mpMoneyEffectPlanet; mpMoneyEffectPlanet = 0; ((cEffectByName*)p)->_v04release(); }

    if (mpSolarBackgroundEffectsWorld != 0) {
        ((cEffectFull*)mpSolarBackgroundEffectsWorld)->_v7c();
        if (mpSolarBackgroundEffectsWorld != 0) {
            void* p = mpSolarBackgroundEffectsWorld;
            mpSolarBackgroundEffectsWorld = 0;
            ((cEffectByName*)p)->_v04release();
        }
    }
    if (mpGalaxyEffectsWorld != 0) {
        ((cEffectFull*)mpGalaxyEffectsWorld)->_v7c();
        if (mpGalaxyEffectsWorld != 0) {
            void* p = mpGalaxyEffectsWorld;
            mpGalaxyEffectsWorld = 0;
            ((cEffectByName*)p)->_v04release();
        }
    }
    if (mpMoneyEffectUFO != 0) {
        ((cEffectFull*)mpMoneyEffectUFO)->_v7c();
        if (mpMoneyEffectUFO != 0) {
            void* p = mpMoneyEffectUFO;
            mpMoneyEffectUFO = 0;
            ((cEffectByName*)p)->_v04release();
        }
    }

    {
        cSPSpaceGfx* pGfx = (cSPSpaceGfx*)GetSpaceGfx();
        RBNode* pNode = (RBNode*)pGfx->mColonyModelMap.mpBegin;
        while (pNode != (RBNode*)&pGfx->mColonyModelMap.mpHead) {
            ((cEffectFull*)pNode->mpValue)->_v16c(0);
            pNode = (RBNode*)RBTreeIncrement(pNode);
        }
    }

    {
        mColonyModelMap.DoNukeSubtree((RBNode*)mColonyModelMap.mpRoot);
        void* pHead = (void*)&mColonyModelMap.mpHead;
        mColonyModelMap.mpRoot = 0;
        mColonyModelMap.mb10 = 0;
        mColonyModelMap.mp14 = 0;
        mColonyModelMap.mpBegin = pHead;
        mColonyModelMap.mpHead = pHead;
    }

    if (SpaceApp() != 0) {
        cApp* pApp = (cApp*)SpaceApp();
        cSubSys* pSub = (cSubSys*)pApp->GetSubSystem();
        ((cViewer*)pSub->GetViewer())->SetViewAngle(kViewAngle);
    }

    FUN_007c3ba0((void*)0x15b7844);
    FUN_007c3ba0((void*)0x15b79b8);
    FUN_007c3ba0((void*)0x15b7b2c);
}

// @ 0x01037700
void cSPSpaceGfx::AllianceGraphCreate()
{
    RBNode* pNode = (RBNode*)mColonyModelMap.mpBegin;
    RBNode* pHead = (RBNode*)&mColonyModelMap.mpHead;
    while (pNode != pHead) {
        ((cEffectFull*)pNode->mpValue)->_v16c(0);
        pNode = (RBNode*)RBTreeIncrement(pNode);
    }

    mColonyModelMap.DoNukeSubtree((RBNode*)mColonyModelMap.mpRoot);
    void* head = (void*)&mColonyModelMap.mpHead;
    mColonyModelMap.mpRoot = 0;
    mColonyModelMap.mb10 = 0;
    mColonyModelMap.mp14 = 0;
    mColonyModelMap.mpBegin = head;
    mColonyModelMap.mpHead = head;
}

// @ 0x01037760
void AllianceGraphUpdate(uint32_t param)
{
    float t = FUN_01036610(param);
    if (t <= 0.0f) {
        FUN_010367e0(GetSpaceGfx(), 0);
        return;
    }
    FUN_010367e0(GetSpaceGfx(), 1);
    cSPSpaceGfx* pGfx = (cSPSpaceGfx*)GetSpaceGfx();
    if (pGfx->mbColonyMapIsDirty)
        pGfx->AllianceGraphCreate();

    RBNode* pNode = (RBNode*)((cSPSpaceGfx*)GetSpaceGfx())->mColonyModelMap.mpBegin;
    RBNode* pHead = (RBNode*)&((cSPSpaceGfx*)GetSpaceGfx())->mColonyModelMap.mpHead;
    if (pNode == pHead)
        return;
    do {
        ((cModelNodeValue*)pNode->mpValue)->mf58 = t;
        pNode = (RBNode*)RBTreeIncrement(pNode);
        pHead = (RBNode*)&((cSPSpaceGfx*)GetSpaceGfx())->mColonyModelMap.mpHead;
    } while (pNode != pHead);
}
