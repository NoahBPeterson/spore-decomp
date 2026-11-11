// src/game/SPGonzago/_at_01030000.cpp -- migrated from slice(s) s010377f0, s01033de0, s01030b10 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_01030000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureCitizen.h"

// unnamed retail callees and globals (address in the comment)
extern const float _HK_REAL_ZERO;                           // 0x01485378 (0.0f)
#include <math.h>
#include "SP/cSPCreatureBase.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPTimer.h"
#include "EA/Variant.h"
#include "SP/cSolarSystem.h"
#include "SP/cCivData.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cSpaceTradeRouteManager.h"
#include "SP/cStarManager.h"
#include "SP/cTerrainSphere.h"
#include "SP/cTradeRouteData.h"
#include "SP/cVarListSerializer.h"

// ---- items of slice s01030b10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Inventory;
struct Sim { Inventory* GetPlayerInventory(); };             // 0x00a1ad60
Sim*   GetUFOSimulator();                                    // 0x00ffbe50
extern const float _HK_REAL_ZERO;                           // 0x01485378 (0.0f)
struct PropertyBlock;
template <class T> struct AutoRefCount {
    T* mpObject;                                            // +0x00
    T** AsPropertyParam()
    {
        T* p = mpObject;
        if (p) {
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};
struct PropertyBlock {
    virtual void v00();                                     // +0x00
    virtual void Release();                                 // +0x04
};
template <class T> struct SPVector {
    T* mpBegin;                                             // +0x00
    T* mpEnd;                                               // +0x04
    T* mpCapacity;                                          // +0x08
    void reserve(unsigned n);                               // 0x004e0880
};
void GetPropertyAsFloatArray(void* prop, unsigned id, int* count, float** values); // 0x006a08b0
struct EconomyTuning {
    char pad00[8];                                          // +0x00
    AutoRefCount<PropertyBlock> mProperties;                // +0x08
    SPVector<unsigned> mValues;                             // +0x0c
    void Init();                                            // 0x01030b10
    int  ComputeAmount(float amount, float* out);           // 0x01030b70
};
struct PropertyObject;
struct InvSub {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
    virtual float GetValue();                              // +0x58
};
struct Inventory {
    char pad00[0x508];
    InvSub mSub;                                            // +0x508
    char pad50c[0x540 - 0x50c];
    float mField540;                                        // +0x540
};
struct SpaceObject {
    char pad00[0x508];
    InvSub mSub;                                            // +0x508
    char pad50c[0x540 - 0x50c];
    float mField540;                                        // +0x540
    char pad544[0x714 - 0x544];
    int mType714;                                           // +0x714
};
struct NounVector {
    void* mpUnused;                                         // +0x00
    SpaceObject** mpBegin;                                  // +0x04
    SpaceObject** mpEnd;                                    // +0x08
};
bool FUN_00cd7d10(PropertyObject* object);
bool FUN_00d3d420(PropertyObject* object);
bool FUN_00ad48b0(PropertyObject* object);
bool FUN_00b1e500(PropertyObject* object);
typedef bool (*NounFilter)(PropertyObject*);
struct TerrainSphere {
    bool Check();                                           // 0x00c75650
};
struct GameNounManager {
    NounVector* GetGameDataVector(NounFilter f1, NounFilter f2, NounFilter f3,
                                  NounFilter f4, unsigned id);     // 0x00b21340
    TerrainSphere* GetCurrentTerrainSphere();               // 0x00f67d90
};
GameNounManager* NounManager();                              // 0x00b3d300
int   FUN_0102f820(float value);                             // 0x0102f820
void* GetPlayerEmpire();                                     // 0x01021300
int   FUN_00c30cb0(void* empire);                            // 0x00c30cb0
inline int RoundUp(float value)
{
    int truncated = (int)value;
    return ((float)truncated < value) ? truncated + 1 : truncated;
}
// ---- items of slice s01030b10 end

// ---- items of slice s01033de0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
struct Vec3 { float x, y, z; };
#define G_FACTOR_TABLE   ((float*)0x016df330)      // +0x000 4 per-behaviour float factors
#define G_TUNE_VARIANTS  ((TuningVariant*)0x016df3d8)  // +0x000 4 tuning variants, 0x14 bytes each
#define G_LAST_ANIM_POS  ((float*)0x015b7ca0)      // +0x000 Vec3 of the last animation position
#define G_REAL_ZERO      ((float*)0x01485378)      // _HK_REAL_ZERO
#define G_STR_15B79B8    ((void*)0x015b79b8)
#define G_STR_15B7844    ((void*)0x015b7844)
#define G_VT_ITRACERBASE ((uint32_t)0x013eb938)
void  operator_delete_array(void* p);                                        // 0x00f47380
void* FUN_01021260();                                                        // 0x01021260
void* GetUniverseContext();                                                  // 0x01021080
int   GetTerraformPlanetType(float value);                                   // 0x00fc1fd0
void* GetCurrentGameMode();                                                  // 0x00b5b800
float FUN_01043150(void* ptr, float value);                                  // 0x01043150
struct Iface {                                  // reference-counted interface (+0x00 vtable)
    PV(0)
    virtual void pv1();                         // +0x04  Release
    virtual void pv2(int value);                // +0x08
    virtual void pv3(int value);                // +0x0c
    virtual bool pv4();                         // +0x10
};
struct AppView {                                // SP::App()
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    virtual uint32_t pv20();                    // +0x50
};
AppView* SP_App();                              // 0x0067dd10
struct ObjA0 {                                  // object looked up at +0xa0
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32)
    virtual void pv33(void* name, uint32_t value);   // +0x84
};
struct TuningVariant {                          // EA::Variant, 0x14 bytes
    uint8_t mPad00[0x14];
    void Set(uint32_t value);                   // 0x00542b80
};
struct TuningSource {                           // object pointed at by +0x13c
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool pv9(uint32_t key, void** out); // +0x24
    virtual uint32_t pv10(uint32_t value);      // +0x28
};
struct Loco {                                   // locomotion sub-object
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual Vec3* pv11();                       // +0x2c  GetPosition
    PV(12) PV(13)
    virtual void pv14(const Vec3* pos);         // +0x38
    void FUN_c41d60(void* str);                 // 0x00c41d60
    void FUN_c41d90(void* str);                 // 0x00c41d90
};
struct Queryable {                              // object returned by the behaviour's vt+0x58 slot
    PV(0) PV(1)
    virtual Queryable* pv2(uint32_t tag);       // +0x08
    PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19) PV(20)
    virtual void pv21();                        // +0x54
    PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31)
    PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41)
    PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
    virtual void pv50(int value);               // +0xc8
    uint8_t mPad04_to_c0[0xc0 - 0x04];
    Loco    mLoco;                              // +0xc0 (embedded sub-object)
    uint8_t mPadC4[0x130 - 0xc4];
    uint8_t mFlag130;                           // +0x130
};
struct Viewer {                                 // cViewer helper sub-object (0x007c4000)
    uint32_t mVt;
    void FUN_007c4000();
};
struct BigThing {                               // object removed by FUN_010347a0 (vtbl 0x013eb938)
    uint32_t mVt;                               // +0x000
    Viewer   mSub004;                           // +0x004
    uint8_t  mPad08[0x178 - 0x08];
    Viewer   mSub178;                           // +0x178
    uint8_t  mPad17C[0x2ec - 0x17c];
    Viewer   mSub2EC;                           // +0x2ec

    void* FUN_010347a0(uint8_t del);
};
struct AgentRefChunk;                           // blocks of the agent reference table
struct AgentRefEntry {                          // 8-byte entry inside a block
    void*    mAgent;                            // +0x00
    uint32_t mType;                             // +0x04
};
struct AgentRefChunk {
    uint32_t      mCount;                       // +0x00
    AgentRefEntry mEntries[1];                  // +0x04
};
struct AgentRef {                               // argument of RemoveAgent
    AgentRefChunk** mChunks;                    // +0x00
};
struct RemoveArgs {                             // 0x18-byte argument block of cInteraction::RemoveAgent
    void*    mRef;                              // +0x00
    uint32_t mIndex;                            // +0x04
    int32_t  mA;                                // +0x08
    int32_t  mB;                                // +0x0c
    int32_t  mC;                                // +0x10
    int32_t  mD;                                // +0x14
};
struct View {                                   // helper subject of FUN_01034680
    bool FUN_c71540();                          // 0x00c71540
    int  FUN_c70880();                          // 0x00c70880
};
struct TerraformSource {                        // object returned by FUN_01021260()
    float FUN_c70a20();                         // 0x00c70a20
};
struct IfaceBank {                              // interface bank used by FUN_01034950's subject
    uint8_t  mPad00[0x60];
    Iface*   mIface60;                          // +0x60
    Iface*   mIface64;                          // +0x64
    Iface*   mIface68;                          // +0x68
    Iface*   mIface6C;                          // +0x6c
    Iface*   mIface70;                          // +0x70
    Iface*   mIface74;                          // +0x74
    Iface*   mIface78;                          // +0x78
    Iface*   mIface7C;                          // +0x7c
    Iface*   mIface80;                          // +0x80
    Iface*   mIface84;                          // +0x84
    Iface*   mIface88;                          // +0x88
    Iface*   mIface8C;                          // +0x8c
    Iface*   mIface90;                          // +0x90
    Iface*   mIface94;                          // +0x94
    Iface*   mIface98;                          // +0x98
    uint8_t  mPad9C[0x110 - 0x9c];
    Vec3     mVec110;                           // +0x110
};
struct Gfx94 {                                  // object stored at behaviour+0x94
    PV(0) PV(1) PV(2)
    virtual void pv3(int value);                // +0x0c
    PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
    virtual void pv15(float radius, float height, void* out);    // +0x3c
};
struct cSolarSystem {                           // SP::cSolarSystem (partial view)
    uint8_t mPad00[0x10];
    void**  mPlanetsBegin;                      // +0x10
    void**  mPlanetsEnd;                        // +0x14

    void ActivateGraphics(int flag);            // 0x00c86c70
    void FUN_c86390(float value);               // 0x00c86390
};
cSolarSystem* GetSolarSystem(void* star);       // 0x00c8b770 SP::cStar::GetSolarSystem
char FUN_00c8b800(void* star);                  // 0x00c8b800
#define G_PARTICLE_RADIUS ((*(float*)0x015b7730))
#define G_PARTICLE_COUNT  ((*(int32_t*)0x015b7734))
struct Behavior {                               // large behaviour/editor subject
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21)
    virtual Queryable* pv22();                  // +0x58

    uint32_t mVt4;                              // +0x04
    uint8_t  mPad08[0x60 - 0x08];
    Iface*   mIface60;                          // +0x60
    Iface*   mIface64;                          // +0x64
    Iface*   mIface68;                          // +0x68
    uint8_t  mPad6C[0x74 - 0x6c];
    int32_t  m74;                               // +0x74
    uint8_t  mPad78[0x90 - 0x78];
    Iface*   mIface90;                          // +0x90
    uint8_t  mPad94[0x98 - 0x94];
    int32_t  m98;                               // +0x98
    uint8_t  mPad9C[0xa0 - 0x9c];
    ObjA0*   mObjA0;                            // +0xa0
    uint8_t  mPadA4[0x130 - 0xa4];
    uint8_t  m130;                              // +0x130
    uint8_t  mPad131[0x13c - 0x131];
    TuningSource* mTuning13C;                   // +0x13c

    bool FUN_00abf640(int value);               // 0x00abf640
    void baseRemoveAgent(RemoveArgs args);      // 0x00abedb0

    int  FUN_01033f50();
    void FUN_01034260(int deathType);
    void FUN_01034950(int mode, int unused);
    void FUN_01034b90(void* star);

    bool   FUN_01033ea0(int value);
    void   RemoveAgent(AgentRef* ref, uint32_t index, int a2, int a3, int a4, int a5);
    void   FUN_010346e0();
    void   FUN_010347e0();
    void   FUN_01034810();
    void   FUN_01034840();
    void   FUN_01034880();
};
// ---- items of slice s01033de0 end

// ---- items of slice s010377f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cTerrainSphere {
public:
    void* mpVtable;                                             // 0x00
    void Reset();                                               // slot 0x0c
    void GenerateImpostor(uint32_t nModelId);                   // 0x00fa1650
};
class cTerrainEditor {
public:
    cTerrainSphere* GetCurrentTerrainSphere();                  // 0x00f67d90
};
void* cSPLivingUniverse_GetActivePlanet();                      // 0x01021260
cTerrainEditor* SP_TerrainEditor();                             // 0x00f48a70
// ---- items of slice s010377f0 end

// @ 0x01030b70
int EconomyTuning::ComputeAmount(float amount, float* out)
{
    int count = 0;
    float* values = 0;
    float factor = 0.0f;
    GetPropertyAsFloatArray(mProperties.mpObject, 0x5e90ecf, &count, &values);
    if (count > 0) {
        int index = FUN_0102f820(amount);
        int last = count - 1;
        factor = values[(index < last) ? index : last];
    }
    Inventory* inventory = GetUFOSimulator()->GetPlayerInventory();
    amount = inventory->mField540;
    amount = inventory->mSub.GetValue() - amount;
    GameNounManager* manager = NounManager();
    NounVector* nouns = manager->GetGameDataVector(
        FUN_00cd7d10, FUN_00d3d420, FUN_00ad48b0, FUN_00b1e500, 0x18ebadc);
    for (SpaceObject** object = nouns->mpBegin; object != nouns->mpEnd; ++object) {
        SpaceObject* noun = *object;
        if (noun->mType714 == 3) {
            float value = noun->mField540;
            amount = (noun->mSub.GetValue() - value) + amount;
        }
    }
    int result = RoundUp(amount * factor);
    if (factor > _HK_REAL_ZERO) {
        int empire = FUN_00c30cb0(GetPlayerEmpire());
        float limit = (float)((empire < result) ? empire : result) / factor;
        amount = (amount > limit) ? limit : amount;
        result = RoundUp(amount * factor);
    }
    if (out)
        *out = amount;
    return result;
}

// @ 0x01034630
float FUN_01034630(int index, float value, char reuse)
{
    if (reuse != 0) {
        float cached = G_FACTOR_TABLE[index];
        if (cached != *G_REAL_ZERO) {
            return cached;
        }
    }
    return FUN_01043150((char*)G_TUNE_VARIANTS + index * 0x14, value);
}

// @ 0x01034680
int FUN_01034680(View* view)
{
    if (view->FUN_c71540()) {
        return 1;
    }
    int stage = view->FUN_c70880();
    return (stage == 1) ? 2 : 0;
}

// @ 0x010346b0
void __stdcall FUN_010346b0(float x, float y, float z)
{
    G_LAST_ANIM_POS[0] = x;
    G_LAST_ANIM_POS[1] = y;
    G_LAST_ANIM_POS[2] = z;
}

// @ 0x010347a0
void* BigThing::FUN_010347a0(uint8_t del)
{
    mSub2EC.FUN_007c4000();
    mSub178.FUN_007c4000();
    mSub004.FUN_007c4000();
    mVt = G_VT_ITRACERBASE;
    if ((del & 1) != 0) {
        operator_delete_array(this);
    }
    return this;
}

// @ 0x010347e0
void Behavior::FUN_010347e0()
{
    AppView* app = SP_App();
    ObjA0* obj = mObjA0;
    char* slot = *(char**)obj;
    slot += 0x84;
    uint32_t value = app->pv20();
    ((void (__thiscall*)(ObjA0*, void*, uint32_t))*(void**)slot)(obj, G_STR_15B79B8, value);
}

// @ 0x01034810
void Behavior::FUN_01034810()
{
    AppView* app = SP_App();
    ObjA0* obj = mObjA0;
    char* slot = *(char**)obj;
    slot += 0x84;
    uint32_t value = app->pv20();
    ((void (__thiscall*)(ObjA0*, void*, uint32_t))*(void**)slot)(obj, G_STR_15B7844, value);
}

// @ 0x01034840
void Behavior::FUN_01034840()
{
    if (mIface90 != 0) {
        mIface90->pv3(1);
        if (mIface90 != 0) {
            Iface* old = mIface90;
            mIface90 = 0;
            old->pv1();
        }
    }
}

// @ 0x01034880
void Behavior::FUN_01034880()
{
    if (FUN_01021260() == 0) {
        return;
    }
    if (GetUniverseContext() != 0) {
        return;
    }
    if (GetTerraformPlanetType(((TerraformSource*)FUN_01021260())->FUN_c70a20()) == 4) {
        mIface60->pv3(1);
        if (GetCurrentGameMode() == (void*)0x01654c10) {
            if (mIface68->pv4()) {
                return;
            }
            mIface68->pv2(0);
            return;
        }
        if (mIface64->pv4()) {
            return;
        }
        mIface64->pv2(0);
        return;
    }
    if (GetCurrentGameMode() == (void*)0x01654c10) {
        mIface68->pv3(1);
    } else {
        mIface64->pv3(1);
    }
    if (mIface60->pv4()) {
        return;
    }
    mIface60->pv2(0);
}

// @ 0x01034b90
void Behavior::FUN_01034b90(void* star)
{
    IfaceBank* self = (IfaceBank*)this;
    cSolarSystem* sys = GetSolarSystem(star);
    if (sys == 0) {
        return;
    }
    if (sys->mPlanetsBegin != sys->mPlanetsEnd) {
        // partial: planet-list present path (see note above).
        return;
    }
    if (FUN_00c8b800(star)) {
        return;
    }
    sys->ActivateGraphics(1);
    Vec3 buf;
    for (int i = 0; i < G_PARTICLE_COUNT; i++) {
        ((Gfx94*)self->mIface94)->pv15(G_PARTICLE_RADIUS, G_PARTICLE_RADIUS, &buf);
    }
    ((Gfx94*)self->mIface94)->pv3(0);
}

// @ 0x01037a20
void SP_CaptureImposterModel(void* pPlanet)
{
    if (pPlanet == 0)
        pPlanet = cSPLivingUniverse_GetActivePlanet();
    cTerrainSphere* pSphere = SP_TerrainEditor()->GetCurrentTerrainSphere();
    if (pPlanet != 0 && pSphere != 0) {
        ((void (__thiscall*)(cTerrainSphere*))((void**)pSphere->mpVtable)[0x0c / 4])(pSphere);
        pSphere->GenerateImpostor(0x29ffa8d);
    }
}
