// Slice s00fc31f0: SP::cWeatherManager::UpdateProperties (0x00fc31f0).
// /O2 /arch:SSE /fp:fast module.
//
// Re-reads the weather tuning property list whenever its modification count
// changes: effect ids, storm/loop-box ids, rain/fog floats (some into members,
// some into file-scope globals) and five cloud colours via GetPropertyAsVector3.
// Every value follows the same pattern: HasProperty(id) (vtable +0x1c), then
// *GetPropertyObject(id)->GetValueT() (vtable +0x28, inline Property getter).
// Retail layout from ModAPI Terrain/cWeatherManager.h.
#include "types.h"

// ---------------------------------------------------------------- properties
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

class cPropertyList {
public:
    virtual ~cPropertyList();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void SetProperty(uint32_t id, const Property* p);            // 0x14
    virtual int  RemoveProperty(uint32_t id);                            // 0x18
    virtual bool HasProperty(uint32_t id) const;                         // 0x1c
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

bool GetPropertyAsVector3(cPropertyList* list, uint32_t id, Vector3& value);   // 0x006a1110

// Weather tuning globals.
extern float g_weatherFloat_15b16fc;
extern float g_weatherFloat_15b1700;
extern float g_weatherFloat_15b1704;
extern float g_weatherFloat_15b1708;
extern float g_weatherFloat_15b170c;
extern float g_weatherFloat_15b1718;

namespace SP {

class cWeatherManager {
public:
    void UpdateProperties();

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
    cPropertyList* mpPropList;            // +0x188
    int      mPropOpCount;                // +0x18c
    float    mAtmoTempChange;             // +0x190
    float    mCloudTrailDecay;            // +0x194
    float    mWriteForceDecay;            // +0x198
    int      mMaxNumStorms;               // +0x19c
};

// @ 0xfc31f0
void cWeatherManager::UpdateProperties()
{
    cPropertyList* propList = mpPropList;
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

} // namespace SP
