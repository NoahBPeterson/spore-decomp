// src/game/SPTerrain/SPWeatherManager.cpp -- migrated from slice(s) s00ff3190, s00fc7430, s00fc6640, s00fc3000, s00fc2080, s00fc31f0 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPWeatherManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <intrin.h>
#include "SP/cWeatherManager.h"
#include "EA/Swarm/cIEffectsWorld.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Swarm/cIVisualEffect.h"
#include "SP/cViewer.h"
#include <xmmintrin.h>

// unnamed retail callees and globals (address in the comment)
extern const int      kDefaultInt32Value;    // 0x015d1160
extern const uint32_t kDefaultUInt32Value;   // 0x015d1164
extern const float    kDefaultFloatValue;    // 0x015d1168
extern float g_weatherFloat_15b16fc;
extern float g_weatherFloat_15b1700;
extern float g_weatherFloat_15b1704;
extern float g_weatherFloat_15b1708;
extern float g_weatherFloat_15b170c;
extern float g_weatherFloat_15b1718;

// ---- items of slice s00fc31f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const int      kDefaultInt32Value;    // 0x015d1160
extern const uint32_t kDefaultUInt32Value;   // 0x015d1164
extern const float    kDefaultFloatValue;    // 0x015d1168
struct Vector3 { float x, y, z; };
typedef Vector3 ColorRGB;
struct Property {
    void*    mpData;      // +0x00 (array data, or the inline value itself)
    uint32_t pad04[3];
    uint16_t mnFlags;     // +0x10 (0x30 = array / external data)
    uint16_t mnType;      // +0x12

    void* GetValuePtr()                                         // 0x00446ff0
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
    int* GetValueInt32()                                        // 0x0041e990
    {
        if (mnType == 9 || mnType == 0x10)
            return (int*)GetValuePtr();
        return (int*)&kDefaultInt32Value;
    }
    uint32_t* GetValueUInt32()                                  // 0x0041ea00
    {
        if (mnType == 10 || mnType == 0x10)
            return (uint32_t*)GetValuePtr();
        return (uint32_t*)&kDefaultUInt32Value;
    }
    float* GetValueFloat()                                      // 0x0041ea70
    {
        if (mnType == 13 || mnType == 0x10)
            return (float*)GetValuePtr();
        return (float*)&kDefaultFloatValue;
    }
};
class cPropertyListBase { public: int GetModificationCount(); };   // 0x006237a0
class cPropertyList_s00fc_31f0 {
public:
    virtual ~cPropertyList_s00fc_31f0();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void SetProperty(uint32_t id, const Property* p);            // 0x14 0x006a2e20
    virtual int  RemoveProperty(uint32_t id);                            // 0x18 0x006a2ef0
    virtual bool HasProperty(uint32_t id) const;                         // 0x1c 0x006a2470
    virtual bool GetPropertyAlt(uint32_t id, Property*& result) const;   // 0x20
    virtual bool GetProperty(uint32_t id, Property*& result) const;      // 0x24
    virtual Property* GetPropertyObject(uint32_t id) const;              // 0x28

    uint32_t pad04[11];
    cPropertyListBase* mpParent;   // +0x30
    int mnModificationCount;       // +0x34

    int GetModificationCount()
    {
        return mnModificationCount + (mpParent ? mpParent->GetModificationCount() : 0);
    }
};
bool GetPropertyAsVector3(cPropertyList_s00fc_31f0* list, uint32_t id, Vector3& value);   // 0x006a1110
extern float g_weatherFloat_15b16fc;
extern float g_weatherFloat_15b1700;
extern float g_weatherFloat_15b1704;
extern float g_weatherFloat_15b1708;
extern float g_weatherFloat_15b170c;
extern float g_weatherFloat_15b1718;
namespace SP {
class cWeatherManager_s00fc_31f0 {
public:
    void UpdateProperties();  // 0x00fc31f0 (SP::cWeatherManager::UpdateProperties)

    uint32_t pad00[14];
    uint32_t mLowAtmoEffectID;            // +0x38
    uint32_t mMidAtmoEffectID;            // +0x3c
    uint32_t mHighAtmoEffectID;           // +0x40
    uint32_t mCurrentAmbientID;           // +0x44
    uint32_t mLoopBoxAtmoEffectID;        // +0x48
    uint32_t mLoopBoxGroundEffectID;      // +0x4c
    uint32_t mCurrentStormLoopboxID;      // +0x50
    uint32_t mColdStormLoopboxID;         // +0x54
    uint32_t mWarmStormLoopboxID;         // +0x58
    uint32_t mHotStormLoopboxID;          // +0x5c
    uint32_t mIceAmbientEffectID;         // +0x60
    uint32_t mColdAmbientEffectID;        // +0x64
    uint32_t mAmbientLoopboxID;           // +0x68
    uint32_t mHotAmbientEffectID;         // +0x6c
    uint32_t mLavaAmbientEffectID;        // +0x70
    uint32_t mCurrentStormEffectID;       // +0x74
    uint32_t mColdStormEffectID;          // +0x78
    uint32_t mWarmStormEffectID;          // +0x7c
    uint32_t mHotStormEffectID;           // +0x80
    uint32_t mCurrentLocalStormEffectID;  // +0x84
    uint32_t mColdLocalStormEffectID;     // +0x88
    uint32_t mWarmLocalStormEffectID;     // +0x8c
    uint32_t mHotLocalStormEffectID;      // +0x90
    int      field_94;                    // +0x94
    uint32_t mRainRampMS;                 // +0x98
    float    mRainDarkness;               // +0x9c
    int      field_A0;                    // +0xa0
    uint32_t mEvaporationEffectID;        // +0xa4
    uint32_t mFreezeEffectID;             // +0xa8
    uint32_t padAC[21];                   // +0xac
    ColorRGB mIceCloudColor;              // +0x100
    ColorRGB mColdCloudColor;             // +0x10c
    ColorRGB mWarmCloudColor;             // +0x118
    ColorRGB mHotCloudColor;              // +0x124
    ColorRGB mLavaCloudColor;             // +0x130
    uint32_t pad13C[19];                  // +0x13c
    cPropertyList_s00fc_31f0* mpPropList;            // +0x188
    int      mPropOpCount;                // +0x18c
    float    mAtmoTempChange;             // +0x190
    float    mCloudTrailDecay;            // +0x194
    float    mWriteForceDecay;            // +0x198
    int      mMaxNumStorms;               // +0x19c
};  // namespace SP
}
// ---- items of slice s00fc31f0 end

// ---- items of slice s00fc2080 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_terraBlendTable[];   // 0x149150c
extern void*    g_terraWeatherTable[]; // 0x149152c
extern int      g_terraRefVtbl0;       // 0x1491590
extern int      g_terraRefVtbl4;       // 0x149158c
extern int      g_gmeRefCountVtbl;     // 0x13ef094
class SpTerraConfig {
public:
    char     pad00[0x68];
    void*    mpWeather;      // +0x68
    char     pad6c[0x140 - 0x6c];
    uint32_t mTerraClass;    // +0x140
    char     pad144[0x148 - 0x144];
    uint32_t mBlendIndex;    // +0x148
    uint32_t mBlendPending;  // +0x14c
    void     SetBlendIndex(uint32_t idx);   // 0xfc2f10
    void     SetWeather(uint32_t idx);      // 0xfc2f30
    uint32_t GetTerraClass();               // 0xfc2f50
};
class SpTerraBounds {
public:
    char  pad00[0xc];
    float mA[3];    // +0x0c
    float mB[3];    // +0x18
    void  CopyCorners(uint32_t* out);   // 0xfc2ee0
};
struct GmeRefCount {
    void** mpVtbl;   // +0x00
    int    mRefs;    // +0x04
};
class SpTerraRefOwner {
public:
    void* mpVtbl0;   // +0x00
    void* mpVtbl4;   // +0x04
    char  pad08[0x30 - 0x08];
    void* mpRefA;    // +0x30
    void* mpRefB;    // +0x34
    ~SpTerraRefOwner();   // 0xfc2f90
};
class SpTerraFill {
public:
    void Zero3(float* out, uint32_t tag);   // 0xfc2ec0
};
// ---- items of slice s00fc2080 end

// ---- items of slice s00fc3000 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gKeyJetA;                   // 0x015b16e8
extern uint32_t gKeyJetB;                   // 0x015b16ec
extern uint32_t gKeyPresA;                  // 0x015b16f0
extern uint32_t gKeyPresB;                  // 0x015b16f4
extern uint32_t gKeyMapA;                   // 0x015b16d8
extern uint32_t gKeyMapB;                   // 0x015b16dc
struct RefCounted {
    virtual ~RefCounted();                 // +0x00 vtable
    int mnRefCount;                        // +0x04
    inline void AddRef() { ++mnRefCount; }
    inline void Release() {
        int n = mnRefCount - 1;
        mnRefCount = mnRefCount - 1;
        if (n == 0) {
            mnRefCount = 1;
            delete this;
        }
    }
};
struct cIMap {                             // size 0x4
    void** vftable;
};
struct RefCountTemplate {                  // size 0x8 (int refcount)
    void** vftable;
    int mRefCount;
};
struct cMapBase : cIMap, RefCountTemplate {  // size 0xc
};
struct cBoundingBox {                      // +0xc..+0x27, 0x1c bytes
    uint32_t words[7];
};
struct cTerrainMapSet : RefCounted {       // size 0x5c
    RefCounted* mMaps[11];                 // +0x8  (AutoRefCount<cTerrainMapBase>[11])
    char pad34[0x5c - 0x34];
};
struct cJetStreamMap : cMapBase {          // size 0x38
    cBoundingBox mBoundingBox;             // +0x0c
    uint32_t mMapIdLo;                     // +0x28
    uint32_t mMapIdHi;                     // +0x2c
    RefCounted* mTerrainMapSet;            // +0x30 (AutoRefCount<SP::cTerrainMapSet>)
    RefCounted* mMap;                      // +0x34

    bool SetValues(RefCounted* p, uint32_t keyLo, uint32_t keyHi);   // 0xfc3000
    bool SetValuesPressure(RefCounted* p, uint32_t keyLo, uint32_t keyHi); // 0xfc3150
    ~cJetStreamMap();                                                // 0xfc30f0
};
static __forceinline void AssignRef(RefCounted*& slot, RefCounted* p)
{
    if (p != slot) {
        RefCounted* const old = slot;
        if (p)
            p->AddRef();
        slot = p;
        if (old)
            old->Release();
    }
}
static void AssignRefOutOfLine(RefCounted*& slot, RefCounted* p);
void AssignRefOutOfLine(RefCounted*& slot, RefCounted* p)
{
    if (p != slot) {
        RefCounted* const old = slot;
        if (p)
            p->AddRef();
        slot = p;
        if (old)
            old->Release();
    }
}
// ---- items of slice s00fc3000 end

// ---- items of slice s00fc6640 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" const float g_013eb8c8;   // 0x013eb8c8  (phase step / freeze threshold)
extern "C" const float g_0141b034;   // 0x0141b034
extern "C" const float g_014471ec;   // 0x014471ec
extern "C" const float g_01486f6c;   // 0x01486f6c
extern "C" const float g_014914fc;   // 0x014914fc
extern "C" const float g_01491508;   // 0x01491508  (0.95f, storm threshold)
extern void* g_vtbl_013eb384;   // 0x013eb384
extern void* g_vtbl_014915f4;   // 0x014915f4
extern void* g_vtbl_01491604;   // 0x01491604
extern void* g_propList_015fd918;   // 0x015fd918
class cRefObj_s00fc6640 {
public:
    virtual void vf00();
    virtual void vf04();
    virtual void vf08(int arg);   // 0x08
    virtual void vf0c(int arg);   // 0x0c
    virtual bool vf10();          // 0x10  is-alive test
    virtual void vf14();
    virtual void vf18(void* record);   // 0x18  apply a motion record
    virtual void vf1c();
    virtual void vf20();
    virtual void vf24();
    virtual void vf28();
    virtual void vf2c();
    virtual void vf30();
    virtual void vf34();
    virtual void vf38(void* camInfo, float t, void* outList, void* modelMask);   // 0x38 collect visible effects
    virtual void vf3c();
    virtual void vf40();
    virtual void vf44(int a, void* p, int b);   // 0x44
    virtual void vf48(int a, void* p, int b);   // 0x48
    virtual void vf4c();
    virtual void vf50();
    virtual void vf54();
    virtual void vf58();
    virtual void vf5c();
    virtual void vf60();
    virtual void vf64();
    virtual void vf68();
    virtual void vf6c();
    virtual void vf70();
    virtual void vf74();
    virtual void vf78();
    virtual void vf7c();
    virtual void vf80();
    virtual void vf84();
    virtual void vf88();
    virtual void vf8c();
    virtual void vf90();
    virtual void vf94();
    virtual void vf98(int a, int b);   // 0x98
    virtual void vf9c();
    virtual void vfA0();
    virtual void vfA4();
    virtual void vfA8();
    virtual void vfAC();
    virtual void vfB0();
    virtual void vfB4();
    virtual void vfB8();
    virtual void vfBC();
    virtual void vfC0();
    virtual void vfC4();
    virtual void vfC8();
    virtual void vfCC(int a, float value);   // 0xcc
    virtual void vfD0();                     // 0xd0
    virtual void vfD4();                     // 0xd4
};
class cEffectFactory_s00fc6640 {
public:
    virtual void vf00();   // 0x00
    virtual void vf04();   // 0x04
    virtual bool vf08(uint32_t id, int arg, cRefObj_s00fc6640** outEffect);   // 0x08
    virtual void vf0c();   // 0x0c
    virtual void vf10();   // 0x10
};
class cViewer_s00fc6640 {
public:
    void GetCameraLocationInfo(void* out, void* a, void* b, void* c);   // 0x007c3d30
};
class cPropTpl_s00fc6640 {
public:
    int32_t  mModCount;     // +0x00
    void*    mpList;        // +0x04
    void*    mListVtbl;     // +0x08
    int32_t  mPropertyID;   // +0x0c

    void BindB(void* pList);   // 0x007e6720
};
class cPropTplC_s00fc6640 {
public:
    uint8_t  mCount;        // +0x00
    uint8_t  m1, m2, m3;    // +0x01..+0x03
    void*    mpList;        // +0x04
    void*    mListVtbl;     // +0x08
    int32_t  mPropertyID;   // +0x0c

    void BindC(void* pList);   // 0x00dea7b0
};
class cVec170_s00fc6640 {
public:
    cRefObj_s00fc6640** mpBegin;      // +0x00
    cRefObj_s00fc6640** mpEnd;        // +0x04
    cRefObj_s00fc6640** mpCapacity;   // +0x08

    void Deallocate(cRefObj_s00fc6640** pBegin, cRefObj_s00fc6640** pEnd);   // 0x00533500
    void Insert(cRefObj_s00fc6640** where, cRefObj_s00fc6640** value);      // 0x00a0a360
};
class cWeatherManager_s00fc6640 {
public:
    cWeatherManager_s00fc6640();
    void UpdateStormPhase(int32_t dt);   // 0x00fc6950
    void ResetEffects();      // 0x00fc6d10
    void UpdateStateMachine(float x, float y, float z, int32_t arg4);   // 0x00fc6f00

    void*    mpVtbl0;          // +0x000
    int32_t  mRefCount;        // +0x004
    void*    mpVtbl8;          // +0x008
    cEffectFactory_s00fc6640* mp0C;   // +0x00c
    void*    mp10;             // +0x010
    void*    mp14;             // +0x014
    void*    mp18;             // +0x018
    void*    mp1C;             // +0x01c
    void*    mp20;             // +0x020
    void*    mp24;             // +0x024
    void*    mp28;             // +0x028
    cRefObj_s00fc6640* mp2C;   // +0x02c  current storm effect
    void*    mp30;             // +0x030
    void*    mp34;             // +0x034
    void*    mp38;             // +0x038
    void*    mp3C;             // +0x03c
    void*    mp40;             // +0x040
    uint32_t m44;              // +0x044
    int32_t  mID48, mID4C, mID50, mID54, mID58, mID5C, mID60, mID64;   // +0x048..+0x064
    int32_t  mID68, mID6C, mID70, mID74, mID78, mID7C;                 // +0x068..+0x07c
    int32_t  mID80, mID84, mID88, mID8C;                              // +0x080..+0x08c
    int32_t  mID90;            // +0x090
    uint32_t mStormTimer;      // +0x094  elapsed time in the current storm phase
    uint32_t mStormDuration;   // +0x098  duration of the current storm phase
    float    mFreezeID;        // +0x09c
    uint32_t mA0;              // +0x0a0
    uint32_t mA4;              // +0x0a4
    uint32_t mA8;              // +0x0a8
    uint8_t  mAC;              // +0x0ac
    uint8_t  mAD;              // +0x0ad
    uint8_t  mAE;              // +0x0ae
    uint8_t  mAF;              // +0x0af
    cPropTpl_s00fc6640 mPropB; // +0x0b0
    uint8_t  mC0Count;         // +0x0c0
    uint8_t  mC1, mC2, mC3;    // +0x0c1..+0x0c3
    void*    mpC4List;         // +0x0c4
    void*    mpC8Vtbl;         // +0x0c8
    int32_t  mCCID;            // +0x0cc
    uint32_t mD0;                     // +0x0d0
    cRefObj_s00fc6640* mD4;           // +0x0d4  effects renderer
    cRefObj_s00fc6640* mD8;           // +0x0d8  effect slot list
    cViewer_s00fc6640* mDC;           // +0x0dc  viewer
    uint32_t mE0, mE4, mE8;           // +0x0e0..+0x0e8
    float    mEC, mF0, mF4, mF8, mFC;                // +0x0ec..+0x0fc
    float    m100, m104, m108, m10C, m110, m114, m118, m11C, m120;  // +0x100..+0x120
    float    m124, m128, m12C, m130, m134, m138;     // +0x124..+0x138
    int32_t  m13C, m140, m144;                       // +0x13c..+0x144
    int32_t  m148, m14C;                             // +0x148..+0x14c
    int32_t  m150, m154, m158, m15C;                 // +0x150..+0x15c
    uint32_t m160;                                   // +0x160
    int32_t  m164, m168;                             // +0x164..+0x168
    uint8_t  m16C;                                   // +0x16c
    uint8_t  m16D;                                   // +0x16d
    uint8_t  m16E, m16F;                             // +0x16e..+0x16f
    cVec170_s00fc6640 mEffects;                      // +0x170
    uint32_t m17C;                                   // +0x17c
    uint32_t m180;                                   // +0x180
    uint32_t mRndSeed;                               // +0x184 (RandomLinearCongruential)
    uint32_t mRndStoredSeed;                         // +0x188
    int32_t  m18C;                                   // +0x18c
    float    m190, m194, m198;                       // +0x190..+0x198
    int32_t  m19C;                                   // +0x19c
};
class cRandom_s00fc6640 {
public:
    uint32_t mSeed;        // +0x00
    uint32_t mStoredSeed;  // +0x04

    void SetSeed(int32_t seed);   // 0x00936090
};
// ---- items of slice s00fc6640 end

// ---- items of slice s00fc7430 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct WeatherGrid {
  char   mPad00[8];      // +0x00
  int    mWidth;         // +0x08
  char   mPad0c[4];      // +0x0c
  float* mpData;         // +0x10
};
struct WeatherCell {
  char         mPad00[0x1c];   // +0x00
  WeatherGrid* mpGrid;         // +0x1c
};
struct RefGrid {
  virtual void vfn0(int a);
  volatile int mRefCount;   // +0x04
  int    mWidth;       // +0x08
  char   mPad0c[4];    // +0x0c
  float* mpData;       // +0x10
};
struct PtrVector {
  void* mBegin;                 // +0x00
  void* mEnd;                   // +0x04
  void* mCap;                   // +0x08
  void push_back(void** item);  // 0x00a7f430
};
struct PropWatcher {
  int  mMode;          // +0x00
  char mPad04[0x0c];   // +0x04
  bool Check();        // 0x007e66a0
};
struct WeatherWatched {
  unsigned char mFlag;         // +0x00
  char          mPad01[0x13];  // +0x01
  void FUN_00dea730();         // 0x00dea730
};
namespace SP {
  struct Vec3 { float x, y, z; };
}
struct XformMsg {
  unsigned short mFlags;      // +0x00
  unsigned short mCount;      // +0x02
  SP::Vec3       mPos;        // +0x04
  float          mW;          // +0x10
  unsigned       mMatrix[9];  // +0x14
  XformMsg();                 // 0x00434040
};
struct WeatherScalars {
  char  mPad00[0x18];    // +0x00
  float mField18;        // +0x18
  char  mPad1c[0x10];    // +0x1c
  float mField2c;        // +0x2c
  float mField30;        // +0x30
  float FUN_00fb8a00();  // 0x00fb8a00
  float FUN_00fb7b90();  // 0x00fb7b90
  float FUN_00fd9400();  // 0x00fd9400
};
struct TerrainEditorObj {
  char mPad00[4];        // +0x00
  bool FUN_00f678a0();   // 0x00f678a0
};
struct WeatherMgr {
  void**         mpVtable;        // +0x00
  void*          mpField04;       // +0x04
  int            mField08;        // +0x08
  void*          mpStream;        // +0x0c
  char           mPad10[0x64];    // +0x10
  void*          mpField74;       // +0x74
  char           mPad78[0x34];    // +0x78
  unsigned char  mFlagAC;         // +0xac
  unsigned char  mFlagAD;         // +0xad
  char           mPadAE[2];       // +0xae
  PropWatcher    mWatcher;        // +0xb0
  WeatherWatched mWatched;        // +0xc0
  void*          mpD4;            // +0xd4
  void*          mpD8;            // +0xd8
  int            mDC;             // +0xdc
  void*          mpE0;            // +0xe0
  WeatherScalars* mpE4;           // +0xe4
  WeatherCell*   mpE8;            // +0xe8
  float          mEC;             // +0xec
  float          mF0;             // +0xf0
  float          mF4;             // +0xf4
  float          mF8;             // +0xf8
  float          mFC;             // +0xfc
  char           mPad100[0x50];   // +0x100
  int            m150;            // +0x150
  int            m154;            // +0x154
  char           mPad158[8];      // +0x158
  unsigned       mCount160;       // +0x160
  RefGrid*       mp164;           // +0x164
  int            mIndex168;       // +0x168
  char           mPad16c[1];      // +0x16c
  unsigned char  mFlag16D;        // +0x16d
  char           mPad16e[2];      // +0x16e
  PtrVector      mVec170;         // +0x170
  char           mPad17c[0x18];   // +0x17c
  float          mField194;       // +0x194
  float          mField198;       // +0x198

  bool Shutdown();             // 0x00fc7950
  void UpdateEffects(int a);   // 0x00fc7b30
  void FUN_00fc7430();         // 0x00fc7430
  void FUN_00fc6d10();         // 0x00fc6d10
  void FUN_00fc5de0();         // 0x00fc5de0
  void FUN_00fc5f80();         // 0x00fc5f80
  void FUN_00fc3f30();         // 0x00fc3f30
  void FUN_00fc6950(int a);    // 0x00fc6950
  int  GetTerraClass();        // 0x00fc2f50
};
typedef void (__thiscall* WFn0)(void*);
typedef void (__thiscall* WFn1)(void*, int);
typedef void (__thiscall* WFn3)(void*, int, int, int);
typedef void (__thiscall* WFn1P)(void*, void*);
typedef void (__thiscall* WFn1C)(void*, const char*);
typedef void (__thiscall* WFn3A)(void*, int, void*, int);
typedef void (__thiscall* WFnPA)(void*, void*, int, int);
typedef int  (__thiscall* WFnI0)(void*);
typedef bool (__thiscall* WFnRead)(void*, void*, int, void**);
#define WVT(p) (*(void***)(p))
float* FUN_00df5f50(float* out, float* range);          // 0x00df5f50
void   FUN_00aa7fa0(int a, int b);                      // 0x00aa7fa0
void   SetCloudGlobal(int a, int b);                    // 0x00f58230
void*  FUN_0067de20();                                  // SP::CheatManager
void*  FUN_0067dd80();                                  // SP::ModelManager
void*  FUN_0067dcc0();                                  // MessageServer
void*  FUN_00f48a70();                                  // SP::TerrainEditor
namespace SP {
  Vec3* normalized_safe(Vec3* out, const Vec3* in);     // 0x00449c20
}
// ---- items of slice s00fc7430 end

// ---- items of slice s00ff3190 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
typedef unsigned int  u32;
typedef unsigned char u8;
struct CubeSample { float u, v; int face; };// argument block for SampleBilinear
struct cCubeImage
{
    void* mpVtbl;                        // +0x00
    int   mRefCount;                     // +0x04
    int   mSize;                         // +0x08
    u8    pad0c[0x10 - 0x0c];
    u8*   mpData;                        // +0x10
    float SampleBilinear(const CubeSample* pCoord);   // 0xf8de70 (ret 4)
};
struct ImageModifier
{
    void*       mpVtbl0;             // +0x00
    void*       mpVtbl1;             // +0x04
    u32         mField08;            // +0x08
    float       mMinX;               // +0x0c
    float       mMinY;               // +0x10
    float       mMinZ;               // +0x14
    float       mMaxX;               // +0x18
    float       mMaxY;               // +0x1c
    float       mMaxZ;               // +0x20
    u32         mField24;            // +0x24
    cCubeImage* mpImage;             // +0x28
    float       mAdd;                // +0x2c
    float       mScale;              // +0x30
    float       mThreshold;          // +0x34
};
// ---- items of slice s00ff3190 end

// @ 0x00fc2ec0
void SpTerraFill::Zero3(float* out, uint32_t tag)
{
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    (void)tag;
}

// @ 0x00fc2ee0
void SpTerraBounds::CopyCorners(uint32_t* out)
{
    out[3] = ((uint32_t*)&mB)[0];
    out[4] = ((uint32_t*)&mB)[1];
    out[5] = ((uint32_t*)&mB)[2];
    out[0] = ((uint32_t*)&mA)[0];
    out[1] = ((uint32_t*)&mA)[1];
    out[2] = ((uint32_t*)&mA)[2];
}

// @ 0x00fc2f10
void SpTerraConfig::SetBlendIndex(uint32_t idx)
{
    mBlendIndex = g_terraBlendTable[idx];
    mBlendPending = 0;
}

// @ 0x00fc2f30
void SpTerraConfig::SetWeather(uint32_t idx)
{
    mpWeather = g_terraWeatherTable[idx];
}

// @ 0x00fc2f50
uint32_t SpTerraConfig::GetTerraClass()
{
    uint32_t c = mTerraClass;
    uint32_t r = 1;
    if (c == 0 || c == 3 || c == 6)
        r = 0;
    else if (c == 2 || c == 5 || c == 8)
        r = 2;
    return r;
}

// @ 0x00fc2f90
SpTerraRefOwner::~SpTerraRefOwner()
{
    mpVtbl0 = (void*)&g_terraRefVtbl0;
    mpVtbl4 = (void*)&g_terraRefVtbl4;
    GmeRefCount* p = (GmeRefCount*)mpRefB;
    if (p != 0) {
        int n = p->mRefs - 1;
        p->mRefs = n;
        if (n == 0) {
            p->mRefs = 1;
            ((void (__thiscall*)(GmeRefCount*, int))(*(void***)p)[0])(p, 1);
        }
    }
    p = (GmeRefCount*)mpRefA;
    if (p != 0) {
        int n = p->mRefs - 1;
        p->mRefs = n;
        if (n == 0) {
            p->mRefs = 1;
            ((void (__thiscall*)(GmeRefCount*, int))(*(void***)p)[0])(p, 1);
        }
    }
    mpVtbl4 = (void*)&g_gmeRefCountVtbl;
}

// @ 0x00fc3000
bool cJetStreamMap::SetValues(RefCounted* p, uint32_t keyLo, uint32_t keyHi)
{
    AssignRef(mTerrainMapSet, (cTerrainMapSet*)p);
    mMapIdLo = keyLo;
    mMapIdHi = keyHi;
    if (keyLo == gKeyJetA && keyHi == gKeyJetB) {
        RefCounted* sub = ((cTerrainMapSet*)mTerrainMapSet)->mMaps[5];
        AssignRef(mMap, sub);
    } else if (keyLo == gKeyPresA && keyHi == gKeyPresB) {
        RefCounted* sub = ((cTerrainMapSet*)mTerrainMapSet)->mMaps[6];
        AssignRefOutOfLine(mMap, sub);
    } else {
        if (mMap) {
            RefCounted* old = mMap;
            mMap = 0;
            old->Release();
        }
    }
    return true;
}

// @ 0x00fc30f0
cJetStreamMap::~cJetStreamMap()
{
    // restore the two base vtables first (the original stores them before touching the members)
    *(void***)this = (void**)0x014915c4;                        // cIMap vftable
    *((void***)this + 1) = (void**)0x014915c0;                  // RefCountTemplate vftable
    _ReadWriteBarrier();
    if (mMap) {
        RefCounted* p = mMap;
        p->Release();
    }
    if (mTerrainMapSet) {
        RefCounted* p = mTerrainMapSet;
        p->Release();
    }
    *((void***)this + 1) = (void**)0x013ef094;                  // ??_7GmeRefCount@@6B@
}

// @ 0x00fc3150
bool cJetStreamMap::SetValuesPressure(RefCounted* p, uint32_t keyLo, uint32_t keyHi)
{
    AssignRef(mTerrainMapSet, (cTerrainMapSet*)p);
    mMapIdLo = keyLo;
    mMapIdHi = keyHi;
    if (keyLo == gKeyMapA && keyHi == gKeyMapB) {
        RefCounted* sub = ((cTerrainMapSet*)mTerrainMapSet)->mMaps[4];
        AssignRef(mMap, sub);
    } else {
        if (mMap) {
            RefCounted* old = mMap;
            mMap = 0;
            old->Release();
        }
    }
    return true;
}

// @ 0x00fc31f0
namespace SP {
void cWeatherManager_s00fc_31f0::UpdateProperties()
{
    cPropertyList_s00fc_31f0* propList = mpPropList;
    int count = propList->GetModificationCount();
    if (count == mPropOpCount)
        return;
    mPropOpCount = count;

    if (propList->HasProperty(0x037936cb))
        mLowAtmoEffectID = *mpPropList->GetPropertyObject(0x037936cb)->GetValueUInt32();
    if (mpPropList->HasProperty(0x037936cf))
        mMidAtmoEffectID = *mpPropList->GetPropertyObject(0x037936cf)->GetValueUInt32();
    if (mpPropList->HasProperty(0x037936d3))
        mHighAtmoEffectID = *mpPropList->GetPropertyObject(0x037936d3)->GetValueUInt32();
    if (mpPropList->HasProperty(0x039a7491))
        mLoopBoxAtmoEffectID = *mpPropList->GetPropertyObject(0x039a7491)->GetValueUInt32();
    if (mpPropList->HasProperty(0x039a73f3))
        mLoopBoxGroundEffectID = *mpPropList->GetPropertyObject(0x039a73f3)->GetValueUInt32();
    if (mpPropList->HasProperty(0x039fa312))
        mIceAmbientEffectID = *mpPropList->GetPropertyObject(0x039fa312)->GetValueUInt32();
    if (mpPropList->HasProperty(0x039fa31e))
        mColdAmbientEffectID = *mpPropList->GetPropertyObject(0x039fa31e)->GetValueUInt32();
    if (mpPropList->HasProperty(0x039fa32d))
        mHotAmbientEffectID = *mpPropList->GetPropertyObject(0x039fa32d)->GetValueUInt32();
    if (mpPropList->HasProperty(0x039fa331))
        mLavaAmbientEffectID = *mpPropList->GetPropertyObject(0x039fa331)->GetValueUInt32();
    if (mpPropList->HasProperty(0x03a0ed2a))
        mEvaporationEffectID = *mpPropList->GetPropertyObject(0x03a0ed2a)->GetValueUInt32();
    if (mpPropList->HasProperty(0x03a0ed39))
        mFreezeEffectID = *mpPropList->GetPropertyObject(0x03a0ed39)->GetValueUInt32();
    if (mpPropList->HasProperty(0x037d32f3))
        mColdStormEffectID = *mpPropList->GetPropertyObject(0x037d32f3)->GetValueUInt32();
    if (mpPropList->HasProperty(0x03a9006c))
        mWarmStormEffectID = *mpPropList->GetPropertyObject(0x03a9006c)->GetValueUInt32();
    if (mpPropList->HasProperty(0x03a9006f))
        mHotStormEffectID = *mpPropList->GetPropertyObject(0x03a9006f)->GetValueUInt32();
    if (mpPropList->HasProperty(0x055ab884))
        mColdLocalStormEffectID = *mpPropList->GetPropertyObject(0x055ab884)->GetValueUInt32();
    if (mpPropList->HasProperty(0x055ab88b))
        mWarmLocalStormEffectID = *mpPropList->GetPropertyObject(0x055ab88b)->GetValueUInt32();
    if (mpPropList->HasProperty(0x055ab88e))
        mHotLocalStormEffectID = *mpPropList->GetPropertyObject(0x055ab88e)->GetValueUInt32();
    if (mpPropList->HasProperty(0x0552c0ba))
        mColdStormLoopboxID = *mpPropList->GetPropertyObject(0x0552c0ba)->GetValueUInt32();
    if (mpPropList->HasProperty(0x0552c0bf))
        mWarmStormLoopboxID = *mpPropList->GetPropertyObject(0x0552c0bf)->GetValueUInt32();
    if (mpPropList->HasProperty(0x0552c0c2))
        mHotStormLoopboxID = *mpPropList->GetPropertyObject(0x0552c0c2)->GetValueUInt32();
    if (mpPropList->HasProperty(0x0653e806))
        mRainDarkness = *mpPropList->GetPropertyObject(0x0653e806)->GetValueFloat();
    if (mpPropList->HasProperty(0x0653e7f7))
        mRainRampMS = *mpPropList->GetPropertyObject(0x0653e7f7)->GetValueUInt32();
    if (mpPropList->HasProperty(0x0379371c))
        mAtmoTempChange = *mpPropList->GetPropertyObject(0x0379371c)->GetValueFloat();
    if (mpPropList->HasProperty(0x037af33c))
        mCloudTrailDecay = *mpPropList->GetPropertyObject(0x037af33c)->GetValueFloat();
    if (mpPropList->HasProperty(0x037ed1d8))
        mWriteForceDecay = *mpPropList->GetPropertyObject(0x037ed1d8)->GetValueFloat();
    if (mpPropList->HasProperty(0x037bf851))
        g_weatherFloat_15b1700 = *mpPropList->GetPropertyObject(0x037bf851)->GetValueFloat();
    if (mpPropList->HasProperty(0x037bf84b))
        g_weatherFloat_15b16fc = *mpPropList->GetPropertyObject(0x037bf84b)->GetValueFloat();
    if (mpPropList->HasProperty(0x037c0bfb))
        g_weatherFloat_15b1704 = *mpPropList->GetPropertyObject(0x037c0bfb)->GetValueFloat();
    if (mpPropList->HasProperty(0x037d2e70))
        g_weatherFloat_15b1708 = *mpPropList->GetPropertyObject(0x037d2e70)->GetValueFloat();
    if (mpPropList->HasProperty(0x037d2e83))
        g_weatherFloat_15b170c = *mpPropList->GetPropertyObject(0x037d2e83)->GetValueFloat();
    if (mpPropList->HasProperty(0x03965482))
        mMaxNumStorms = *mpPropList->GetPropertyObject(0x03965482)->GetValueInt32();
    if (mpPropList->HasProperty(0x03a77d75))
        g_weatherFloat_15b1718 = *mpPropList->GetPropertyObject(0x03a77d75)->GetValueFloat();
    if (mpPropList->HasProperty(0x060321d8))
        GetPropertyAsVector3(mpPropList, 0x060321d8, mIceCloudColor);
    if (mpPropList->HasProperty(0x060321e4))
        GetPropertyAsVector3(mpPropList, 0x060321e4, mColdCloudColor);
    if (mpPropList->HasProperty(0x060321e7))
        GetPropertyAsVector3(mpPropList, 0x060321e7, mWarmCloudColor);
    if (mpPropList->HasProperty(0x060321e9))
        GetPropertyAsVector3(mpPropList, 0x060321e9, mHotCloudColor);
    if (mpPropList->HasProperty(0x060321ee))
        GetPropertyAsVector3(mpPropList, 0x060321ee, mLavaCloudColor);
}
}  // namespace SP

// @ 0x00fc6640
cWeatherManager_s00fc6640::cWeatherManager_s00fc6640()
{
    const float kFreeze = g_013eb8c8;

    mRefCount = 0;
    *(void* volatile*)&mpVtbl8 = (void*)&g_vtbl_013eb384;
    *(void* volatile*)&mpVtbl0 = (void*)&g_vtbl_01491604;
    *(void* volatile*)&mpVtbl8 = (void*)&g_vtbl_014915f4;

    mp0C = 0;
    mp10 = 0;
    mp14 = 0;
    mp18 = 0;
    mp1C = 0;
    mp20 = 0;
    mp24 = 0;
    mp28 = 0;
    mp2C = 0;
    mp30 = 0;
    mp34 = 0;
    mp38 = 0;
    mp3C = 0;
    mp40 = 0;

    mID48 = 0;
    mID4C = 0;
    mID50 = 0;
    mID54 = 0;
    mID58 = 0;
    mID5C = 0;
    mID60 = 0;
    mID64 = 0;
    mID68 = 0;
    mID6C = 0;
    mID70 = 0;
    mID74 = 0;
    mID78 = 0;
    mID7C = 0;

    mID80 = 0;
    mID84 = 0;
    mID88 = 0;
    mID8C = 0;
    mID90 = 0;
    mStormTimer = 0;

    mStormDuration = 3000;
    mFreezeID = kFreeze;
    mA0 = 0;
    mA4 = 0;
    mA8 = 0;
    mAC = 0;
    mAD = 0;

    void* pList = g_propList_015fd918;

    cPropTpl_s00fc6640* propB = &mPropB;
    propB->mModCount = 2;
    propB->mpList = pList;
    if (pList != 0)
        ((cRefObj_s00fc6640*)pList)->vf00();
    propB->mListVtbl = (void*)0x3ffad0a;
    propB->mPropertyID = 0;
    if (pList != 0)
        propB->BindB(pList);

    pList = g_propList_015fd918;

    cPropTplC_s00fc6640* propC = (cPropTplC_s00fc6640*)&mC0Count;
    propC->mCount = 1;
    propC->mpList = pList;
    if (pList != 0)
        ((cRefObj_s00fc6640*)pList)->vf00();
    propC->mListVtbl = (void*)0x588bf6d;
    propC->mPropertyID = 0;
    if (pList != 0)
        propC->BindC(pList);

    const float kStormLevel = g_01491508;
    const float kZero = 0.0f;

    mD0 = 0;
    mD4 = 0;
    mD8 = 0;
    mDC = 0;
    mE0 = 0;
    mE4 = 0;
    mE8 = 0;

    mEC = kZero;
    mF0 = kZero;
    mF4 = kZero;
    mF8 = kZero;
    mFC = kZero;

    m100 = kStormLevel;
    m104 = kStormLevel;
    m108 = kStormLevel;
    m10C = kStormLevel;
    m110 = kStormLevel;
    m114 = kStormLevel;
    m118 = kStormLevel;
    m11C = kStormLevel;
    m120 = kStormLevel;

    m124 = g_0141b034;
    m128 = g_014471ec;
    m12C = g_01486f6c;
    m130 = g_013eb8c8;
    m134 = g_014914fc;
    m138 = kZero;

    _ReadWriteBarrier();
    m13C = 9;
    m140 = 9;

    _ReadWriteBarrier();
    m148 = 0;
    m14C = 0;
    _ReadWriteBarrier();
    m150 = 5;
    m154 = 5;
    _ReadWriteBarrier();
    m158 = 3;
    m15C = 3;
    m160 = 5;
    m164 = 0;
    m168 = 0;
    m16D = 0;
    _ReadWriteBarrier();
    mEffects.mpBegin = 0;
    mEffects.mpEnd = 0;
    mEffects.mpCapacity = 0;
    ((cRandom_s00fc6640*)&mRndSeed)->SetSeed(-1);

    const float kPhase = g_014914fc;

    mRndStoredSeed = 0;
    _ReadWriteBarrier();
    m19C = 5;
    m18C = -1;
    m190 = kPhase;
    m194 = kPhase;
    m198 = kPhase;
}

// @ 0x00fc7430
void WeatherMgr::FUN_00fc7430()
{
  WeatherGrid* a = mpE8->mpGrid;
  if (a != 0) {
    WeatherGrid* b = *(WeatherGrid**)0x16d7150;
    if (b != 0 && mFlagAC != 0) {
      float* src = a->mpData + a->mWidth * a->mWidth * mIndex168;
      int n = b->mWidth;
      float* dst = b->mpData + n * n * mIndex168;
      if ((unsigned)(((char*)mVec170.mEnd - (char*)mVec170.mBegin) >> 2) < mCount160) {
        float rnd[4];
        FUN_00df5f50(rnd, (float*)0x15b177c);
        SP::Vec3 nrm;
        SP::normalized_safe(&nrm, (const SP::Vec3*)rnd);
        void* obj = 0;
        if (((WFnRead)WVT(mpStream)[0x08 / 4])(mpStream, mpField74, 0, &obj)) {
          XformMsg msg;
          msg.mFlags = msg.mFlags | 4;
          msg.mCount = msg.mCount + 1;
          msg.mPos = nrm;
          ((WFn1P)WVT(obj)[0x18 / 4])(obj, &msg);
          ((WFn1)WVT(obj)[0x08 / 4])(obj, 0);
          int terra = GetTerraClass();
          ((WFn3A)WVT(obj)[0x48 / 4])(obj, 3, &terra, 1);
          mVec170.push_back(&obj);
        }
        if (obj != 0)
          ((WFn0)WVT(obj)[0x04 / 4])(obj);
      }
      if (n > 0) {
        for (int y = 0; y < n; ++y) {
          for (int x = 0; x < n; ++x) {
            float s = src[x];
            float v = dst[x] + mField194;
            dst[x] = v < s ? v : s;
          }
          src += n;
          dst += n;
        }
      }
    }
  }

  RefGrid* c = *(RefGrid**)0x16d714c;
  if (c != 0 && mp164 != 0) {
    int n = mp164->mWidth;
    float* pa = mp164->mpData + n * n * mIndex168 * 3;
    float* pb = c->mpData + c->mWidth * c->mWidth * mIndex168 * 3;
    if (n > 0) {
      for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
          float* ea = pa + x * 3;
          float* eb = pb + x * 3;
          eb[0] = (ea[0] - eb[0]) * mField198 + eb[0];
          eb[1] = (ea[1] - eb[1]) * mField198 + eb[1];
          eb[2] = (ea[2] - eb[2]) * mField198 + eb[2];
        }
        pa += n * 3;
        pb += n * 3;
      }
    }
  }

  mIndex168 = mIndex168 + 1;
  if (mIndex168 >= 6)
    mIndex168 = 0;
}

// @ 0x00fc7950
bool WeatherMgr::Shutdown()
{
  FUN_00fc6d10();
  if (mpStream != 0) {
    ((WFn0)WVT(mpStream)[0x34 / 4])(mpStream);
    ((WFn1)WVT(mpStream)[0x0c / 4])(mpStream, 2);
    ((WFn1)WVT(mpD8)[0x50 / 4])(mpD8, 0x3618bef);
    if (mpStream != 0) {
      void* p = mpStream;
      mpStream = 0;
      ((WFn0)WVT(p)[0x04 / 4])(p);
    }
  }
  ((WFn3)WVT(mpD8)[0x88 / 4])(mpD8, *(int*)0x15b16d8, *(int*)0x15b16dc, 0);
  ((WFn3)WVT(mpD8)[0x88 / 4])(mpD8, *(int*)0x15b16e8, *(int*)0x15b16ec, 0);
  ((WFn3)WVT(mpD8)[0x88 / 4])(mpD8, *(int*)0x15b16f0, *(int*)0x15b16f4, 0);
  FUN_00aa7fa0(6, 0);
  SetCloudGlobal(3, 0);
  void* cheat = FUN_0067de20();
  if (cheat != 0) {
    ((WFn1C)WVT(cheat)[0x1c / 4])(cheat, "weather");
    *(unsigned char*)0x16d70ec = 0;
  }
  void* model = FUN_0067dd80();
  ((WFn1)WVT(model)[0x18 / 4])(model, 0x611c912);
  ((WFn1)WVT(mpD4)[0x134 / 4])(mpD4, 0);
  if (mpD4 != 0) {
    void* p = mpD4;
    mpD4 = 0;
    ((WFn0)WVT(p)[0x04 / 4])(p);
  }
  mDC = 0;
  mpE4 = 0;
  mpE0 = 0;
  mpE8 = 0;
  mFlagAD = 0;
  mFlag16D = 0;
  if (mp164 != 0) {
    RefGrid* p = mp164;
    mp164 = 0;
    if (--p->mRefCount == 0) {
      p->mRefCount = 1;
      p->vfn0(1);
    }
  }
  if (*(RefGrid**)0x16d7150 != 0) {
    RefGrid* p = *(RefGrid**)0x16d7150;
    *(RefGrid**)0x16d7150 = 0;
    if (--p->mRefCount == 0) {
      p->mRefCount = 1;
      p->vfn0(1);
    }
  }
  if (*(RefGrid**)0x16d714c != 0) {
    RefGrid* p = *(RefGrid**)0x16d714c;
    *(RefGrid**)0x16d714c = 0;
    if (--p->mRefCount == 0) {
      p->mRefCount = 1;
      p->vfn0(1);
    }
  }
  void* server = FUN_0067dcc0();
  ((WFnPA)WVT(server)[0x2c / 4])(server, &mField08, 0xf62def, (int)0xffffd8f1);
  return true;
}

// @ 0x00fc7b30
void WeatherMgr::UpdateEffects(int arg)
{
  bool flag;
  if (mWatcher.Check() || mFlagAC == 0)
    flag = true;
  else
    flag = false;

  mWatched.FUN_00dea730();
  if (mpE4 != 0 && mFlagAD != 0 && mWatched.mFlag != 0) {
    if (((WFnI0)WVT(mpE0)[0x20 / 4])(mpE0) != 4) {
      void* terrain = FUN_00f48a70();
      if (!((TerrainEditorObj*)terrain)->FUN_00f678a0()) {
        if (flag) {
          FUN_00fc6d10();
          FUN_00fc5de0();
          flag = true;
        }
        float a = mpE4->FUN_00fb8a00();
        float b = mpE4->FUN_00fb7b90();
        float c = mpE4->FUN_00fd9400();
        if (a != mEC || b != mF0 || c != mF4 || flag) {
          mFC = mF0;
          mF8 = mEC;
          mEC = a;
          mF0 = b;
          mF4 = c;
          FUN_00fc3f30();
        }
        if (b == 0.0f)
          FUN_00fc6d10();
        else
          FUN_00fc5f80();
        if (mWatcher.mMode == 2)
          FUN_00fc7430();
        FUN_00fc6950(arg);
        mF8 = mEC;
        m150 = m154;
        mFC = mF0;
      }
    }
  }
}

// @ 0x00ff37c0
bool __fastcall FUN_00ff37c0(ImageModifier* ecx_this, void* edx, const float* p)
{
    if ((((ecx_this->mMinX <= p[0]) && (p[0] <= ecx_this->mMaxX)) &&
         ((ecx_this->mMinY <= p[1]) && (p[1] <= ecx_this->mMaxY))) &&
        (((ecx_this->mMinZ <= p[2]) && (p[2] <= ecx_this->mMaxZ)))) {
        return true;
    }
    return false;
}
