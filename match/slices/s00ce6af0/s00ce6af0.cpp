// SP::cTribeTuningData::Init  @ 0x00ce6af0
//
// PARTIAL reconstruction. ~5741-byte __thiscall tuning initialiser (/O2 /MD /Gy
// /EHsc /TP).  It grabs the tribe/community property lists and then applies a
// long series (~200) of "read property by hash -> store into member" rules.
// The prologue/property-list wiring and a representative slice of the rules are
// reproduced; the bulk of the rule table is omitted.
//
//   void __thiscall cTribeTuningData::Init()

#pragma once
typedef unsigned char  uint8;
typedef unsigned int   uint32;
typedef unsigned __int64 uint64;

namespace SP { struct cPropertyList; }
template <class T> struct AutoRefCount { T* mpObject; };
struct cSPVector2 { float x, y; };

namespace SP
{

// Dev-PDB layout (retail may differ slightly); member names are real.
struct cTribeTuningData
{
    cSPVector2  kSizeLimits;                        // +0x000
    float       kChieftainScaleMultiplier;          // +0x008
    unsigned char pad_00c[0x7c - 0x0c];
    AutoRefCount<SP::cPropertyList> mpTribeTuningPropList;   // +0x07c
    AutoRefCount<SP::cPropertyList> mpTribePropList;         // +0x080
    AutoRefCount<SP::cPropertyList> mpCommunityEditorPropList;// +0x084
    AutoRefCount<SP::cPropertyList> mpTribeHitHutPropList;    // +0x088
    float       mEatFoodPerSecond;                  // +0x08c
    unsigned char pad_090[0xc0 - 0x90];
    uint64      mTimeBeforeBabyGrowsUp_ms;          // +0x0c0
    float       mGotoWaitTime;                      // +0x134
    float       mTribeHutLevel1Health;              // +0x138
    float       mTribeHutLevel3Health;              // +0x140
    float       mTribeToolHiDamage;                 // +0x144
    float       mTribeHutHiDamage;                  // +0x14c
    float       mTribeHutLoDamage;                  // +0x150
    unsigned char pad_154[0x160 - 0x154];
    int         mMatingTimer[15];                   // +0x160
    void Init();
};

} // namespace SP

// --- callees (masked relocations) ---
extern "C" int*  SP_PropertyManager(void);
extern "C" void* SP_NounManager_all(void);
extern "C" int   cTerrainEditor_GetCurrentTerrainSphere(void*);
extern "C" void  FUN_00b3d320(void);
extern "C" SP::cPropertyList* FUN_00b1daf0(void);
extern "C" uint32* EA_Hash_FNV1_String8(void);
extern "C" float* GetPropertyAsFloat(void);
extern "C" void  cPropertyList_vt0(SP::cPropertyList*);   // AddRef / Release slot

namespace SP
{

// @ 0x00ce6af0
void cTribeTuningData::Init()
{
    // --- property-list acquisition (faithful) ---
    int* mgr = SP_PropertyManager();
    (void)mgr;
    void* terrain = SP_NounManager_all();
    int sphere = cTerrainEditor_GetCurrentTerrainSphere(terrain);
    (void)sphere;

    FUN_00b3d320();

    // mpTribePropList = <fresh tribe property list>
    {
        cPropertyList* fresh = FUN_00b1daf0();
        cPropertyList* old   = mpTribePropList.mpObject;
        if (fresh != old)
        {
            if (fresh) cPropertyList_vt0(fresh);     // AddRef
            mpTribePropList.mpObject = fresh;
            if (old)   cPropertyList_vt0(old);       // Release
        }
    }

    // mpCommunityEditorPropList = mpTribePropList
    {
        cPropertyList* src = mpTribePropList.mpObject;
        cPropertyList* old = mpCommunityEditorPropList.mpObject;
        if (src != old)
        {
            if (src) cPropertyList_vt0(src);
            mpCommunityEditorPropList.mpObject = src;
            if (old) cPropertyList_vt0(old);
        }
    }

    // clear mpTribeHitHutPropList
    {
        cPropertyList* old = mpTribeHitHutPropList.mpObject;
        if (old)
        {
            mpTribeHitHutPropList.mpObject = 0;
            cPropertyList_vt0(old);
        }
    }

    // --- tuning rule table (partially reproduced) ---
    // Each rule is: look the hash up in mpTribePropList (vtable +0x24), verify the
    // property kind (short at +0x12), then store into `this`:
    //
    //   0x375418a  (kind 2)  -> mMatingTimer[6]        = FNV1_String8()
    //   0xb565559b (kind 13) -> mTribeHutLoDamage      = GetPropertyAsFloat()
    //   0x70adc7c2 (kind 13) -> mTreeSmackYield value  = round(*f * 1000)
    //   0x70adc7c3 (kind 13) -> mTimeBeforeBabyGrowsUp_ms = round(*f * 1000)
    //   0xe8c2bcae (kind 13) -> mGotoWaitTime          = *f
    //   0xdae22b88 (kind 13) -> mTribeHutLevel1Health  = *f
    //   ... ~200 further rules covering mTribeHutLevel3Health, mTribeToolHiDamage,
    //   mTribeHutHiDamage, mEatFoodPerSecond, mCarryBundleAmountMax_*, score and
    //   social thresholds, mGameSpeeds[4], repair delays, etc.
    //
    // Reproducing the whole table byte-for-byte requires enumerating every hash
    // and its kind; withheld, so the initialiser is incomplete.
    if (mpTribePropList.mpObject)
    {
        // initialise the scalar defaults the rules fall back to when absent
        mGotoWaitTime = 0.0f;
        mEatFoodPerSecond = 0.0f;
    }
}

} // namespace SP
