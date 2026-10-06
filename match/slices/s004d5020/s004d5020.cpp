// Slice s004d5020: SP::cSpeciesProfile::Update (15337 bytes, /Od).
// Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
// Rebuilds the species profile from an editor rig: resets the stats, reads the
// animated-creature asset name/description, walks every rig block (cost, mass,
// stealth/sprint, bounding volume, per-capability counts/levels, mouth/grasper/
// foot/fruit index lists), derives the capability levels, the social/attack
// scores (weighted by the global ability table), and finally queues every
// global ability whose property-list requirements the profile satisfies.
// Retail field offsets differ from the 2008 PDB layout, so fields are named by
// offset (PDB names in comments where the role is clear).
#include "types.h"
#pragma pack(push, 4)

struct Vector2 {
    float x, y;
    float& operator[](int i) { return (&x)[i]; }
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) { x = a; y = b; z = c; }
    float& operator[](int i) { return (&x)[i]; }
};

struct Matrix3 { float m[9]; };

// cdecl Vector3 helpers (sret first).
Vector3 V3MulScalar(const Vector3& v, const float& s);             // 0x0041DCA0  v * s
Vector3 V3Sub(const Vector3& a, const Vector3& b);                  // 0x0041DB10  a - b
Vector3 V3Add(const Vector3& a, const Vector3& b);                  // 0x0041DC10  a + b
Vector3 V3ScalarMul(const float& s, const Vector3& v);              // 0x0041DE40  s * v
Vector3 V3MulMatrix(const Vector3& v, const Matrix3& m);            // 0x0041DAF0  m * v
Vector3 V3Negate(const Vector3& v);                                 // 0x00422020  -v
Vector3 V3Min(const Vector3& a, const Vector3& b);                  // 0x0041C0C0
Vector3 V3Max(const Vector3& a, const Vector3& b);                  // 0x0041BFB0
float   V3Length(const Vector3& v);                                 // 0x0040AE50

template<class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
template<class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }

inline float ClampF(float v, float lo, float hi)
{
    // maxss / minss
    v = (v > lo) ? v : lo;
    v = (v < hi) ? v : hi;
    return v;
}

// Rounding float->int (cvtss2si, current MXCSR rounding); asm helper as in the original.
inline int RoundToInt(float f)
{
    int r;
    __asm {
        cvtss2si eax, f
        mov r, eax
    }
    return r;
}

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

struct cAssetMetadata {
    const wchar_t* GetName();              // 0x00414E10
    const wchar_t* GetDescription();       // 0x005508C0
    uint64_t GetAssetKey();                // 0x005508A0
};

struct ResourceObject {
    virtual int AddRef();
    virtual int Release();
};

struct ResourceObjectPtr {
    ResourceObject* mpObject;
    ResourceObjectPtr() { mpObject = 0; }
    ~ResourceObjectPtr() { if (mpObject) mpObject->Release(); }
    ResourceObject** AsParam()
    {
        if (mpObject) {
            ResourceObject* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};

struct IResourceManager {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual bool GetResource(const ResourceKey& key, ResourceObject** ppOut,
                             int a, int b, int c, int d);              // slot 3
};
IResourceManager* GetManager();                                         // 0x0067DCD0
cAssetMetadata* GetAssetMetadata(ResourceObjectPtr* p);                  // 0x00421F60

struct PropertyList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool HasProperty(uint32_t id);                              // slot 7
};

struct PropertyListSource {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual PropertyList* GetPropertyList(uint32_t instanceID, uint32_t groupID);  // slot 22
};
PropertyListSource* GetPropertyListSource();                           // 0x00401010
void* PropertyManager();                                                // 0x0067DE30

namespace SP { namespace cTribeTool {
int GetTutorialToolPrice(PropertyList* pProp, uint32_t id, int flags);  // 0x004E1C30
} }
bool GetBoolProperty(PropertyList* p, uint32_t id, bool* pOut);         // 0x00407190
bool TryGetIntProperty(PropertyList* p, uint32_t id, int* pOut);        // 0x00410370
float GetPropertyFloat(PropertyList* p, uint32_t id, float def);        // 0x004E1C70 GetPropertyT<float>
bool GetPropertyAsUint32Array(PropertyList* p, uint32_t id, int* pCount, uint32_t** ppData);  // 0x006A0840
bool GetPropertyAsVector2Array(PropertyList* p, uint32_t id, int* pCount, Vector2** ppData);  // 0x006A0920
bool GetPropertyAsVector2(PropertyList* p, uint32_t id, Vector2* pOut); // 0x006A10C0

struct cCreatureAbility {
    uint32_t pad0[2];
    int mType;                    // +0x08
    uint32_t pad0c[(0x110 - 0x0c) / 4];
    float mWeight;                // +0x110
    uint32_t pad114[(0x130 - 0x114) / 4];
    PropertyList* mpPropList;     // +0x130
};

template<class T> struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
};

// eastl::vector stubs (out-of-line members are the shared instances).
struct UIntVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void push_back(const uint32_t& v);                                  // 0x00454860
    uint32_t* erase(uint32_t* first, uint32_t* last);                   // 0x004769B0
    UIntVector& operator=(const UIntVector& x);                         // 0x0050D4E0
    void clear() { erase(mpBegin, mpEnd); }
};

struct cSPTransform {
    uint16_t mFlags;
    uint16_t mnChanges;
    Vector3 mOffset;
    float mScale;
    Matrix3 mRotation;
    cSPTransform();                                                     // 0x00409930
    void SetOffset(const Vector3& v) { mOffset = v; mFlags |= 4; mnChanges++; }
    void SetRotation(const Matrix3& m) { mRotation = m; mFlags |= 2; mnChanges++; }
};

struct TransformVector {
    cSPTransform* mpBegin;
    cSPTransform* mpEnd;
    cSPTransform* mpCapacity;
    void push_back(const cSPTransform& v);                              // 0x0041E460
    cSPTransform* erase(cSPTransform* first, cSPTransform* last);       // 0x004238C0
    void clear() { erase(mpBegin, mpEnd); }
};

struct AbilityVector {
    AutoRefCount<cCreatureAbility>* mpBegin;
    AutoRefCount<cCreatureAbility>* mpEnd;
    AutoRefCount<cCreatureAbility>* mpCapacity;
    uint32_t mAllocator;
    AutoRefCount<cCreatureAbility>* erase(AutoRefCount<cCreatureAbility>* first,
                                          AutoRefCount<cCreatureAbility>* last);   // 0x004247F0
    void clear() { erase(mpBegin, mpEnd); }
    uint32_t size() { return (uint32_t)(mpEnd - mpBegin); }
    AutoRefCount<cCreatureAbility>& operator[](uint32_t i) { return mpBegin[i]; }
};

struct AbilityPtrVector {
    cCreatureAbility** mpBegin;
    cCreatureAbility** mpEnd;
    cCreatureAbility** begin() { return mpBegin; }
    cCreatureAbility** end() { return mpEnd; }
};
extern AbilityPtrVector gCreatureAbilities;   // 0x015D9780

// Tuning globals.
extern float gFoodPerVolume;      // 0x0150C904 (1000.0)
extern float gHealthPerLevel;     // 0x0150C8AC (50.0)
extern float gMaxHealthBonus;     // 0x0150C8B0 (500.0)

// Per-capability accumulator (value of the capsInfos fixed_hash_map).
struct PartLayout {
    uint32_t mCount;     // +0x00
    uint32_t mSum;       // +0x04
    uint32_t mMax;       // +0x08
    float mScale;        // +0x0C
    float mWeight;       // +0x10
};

struct CapsNode;
struct CapsMap {
    uint32_t mHashPad;               // +0x00
    CapsNode** mpBucketArray;        // +0x04
    uint32_t mnBucketCount;          // +0x08
    uint32_t mnElementCount;         // +0x0C
    PartLayout& operator[](const uint32_t& key);                         // 0x004E0400
    void DoFreeNodes(CapsNode** pBuckets, uint32_t n);                   // 0x004E3010
    void clear() { DoFreeNodes(mpBucketArray, mnBucketCount); mnElementCount = 0; }
};

struct WString {
    void assign(const wchar_t* first, const wchar_t* last);              // 0x00423650
    WString& operator=(const wchar_t* p)
    {
        const wchar_t* pEnd = p;
        while (*pEnd) ++pEnd;
        assign(p, p + (pEnd - p));
        return *this;
    }
    uint32_t pad[4];
};

// Editor rig block (0x8c bytes).
struct RigBlock {
    uint16_t pad0[3];
    int16_t mSymmetryIndex;   // +0x06
    uint32_t pad8;
    uint16_t mCapStart;       // +0x0C
    uint16_t padE;
    uint8_t mCapCount;        // +0x10
    uint8_t pad11[3];
    Vector3 mBoundsMin;       // +0x14
    Vector3 mBoundsMax;       // +0x20
    float mScale;             // +0x2C
    Matrix3 mRotation;        // +0x30
    Vector3 mPosition;        // +0x54
    uint32_t pad60[3];
    float mMass;              // +0x6C
    uint32_t pad70[4];
    uint32_t mFootType;       // +0x80
    uint32_t mGroupID;        // +0x84
    uint32_t mInstanceID;     // +0x88
};

struct ColorSet { uint32_t v[9]; };

struct EditorRig {
    uint32_t pad0[6];
    uint32_t mModelFlags;     // +0x18
    uint32_t pad1c[(0x38 - 0x1c) / 4];
    ColorSet mColors;         // +0x38
    uint32_t pad5c[(0x98 - 0x5c) / 4];
    RigBlock* mBlocksBegin;   // +0x98
    RigBlock* mBlocksEnd;     // +0x9C
    uint32_t padA0[3];
    uint32_t* mCaps;          // +0xAC
    uint32_t padB0[4];
    uint8_t* mCapLevels;      // +0xC0
};

namespace SP {
class cSpeciesProfile;
}
uint32_t GetCapLevel(SP::cSpeciesProfile* p, uint32_t cap);            // 0x004D35D0
int CountCap(SP::cSpeciesProfile* p, uint32_t cap);                    // 0x004D3640
int GetCapBonus(SP::cSpeciesProfile* p, uint32_t cap);                 // 0x004D3570
PartLayout* GetCapInfo(SP::cSpeciesProfile* p, uint32_t cap);          // 0x004D36A0
float BlendAttackScore(float food, float social, float cute, float numCute,
                       float eyeAvg, float footAvg, float grasperAvg);  // 0x004D3500

namespace SP {
class cSpeciesProfile {
public:
    bool Update(EditorRig* pRig);
    bool FillInProfileValues(cCreatureAbility* pAbility, PropertyList* pProp);   // 0x004D90A0
    void AddAbility(cCreatureAbility* pAbility);                                // 0x004E01D0
    void FinishUpdate();                                                        // 0x004D4AD0

    CapsMap capsInfos;                    // 0x000
    uint32_t pad010[(0x4e0 - 0x010) / 4];
    ColorSet mSkinColors;                 // 0x4E0
    ResourceKey animatedCreatureKey;      // 0x504
    uint32_t pad510[3];
    WString animatedCreatureName;         // 0x51C
    WString animatedCreatureDesc;         // 0x52C
    uint32_t creatureSeq;                 // 0x53C
    int costToMakeCreature;               // 0x540
    uint32_t pad544;
    float jumping_ability;                // 0x548
    float gliding_ability;                // 0x54C
    float flapping_ability;               // 0x550
    Vector3 mExtents;                     // 0x554
    Vector3 mBoundsMin;                   // 0x560
    float f56c;                           // 0x56C
    uint32_t pad570;
    float food_value;                     // 0x574
    bool mHasMass;                        // 0x578
    uint8_t pad579[3];
    uint32_t mModelFlags;                 // 0x57C
    uint64_t mAssetKey;                   // 0x580
    float f588;                           // 0x588
    float num_graspers;                   // 0x58C
    float num_mouths;                     // 0x590
    float num_ears;                       // 0x594
    float sum_cuteness_parts;             // 0x598
    float num_cuteness_parts;             // 0x59C
    float cuteness_stat_score;            // 0x5A0
    float social_stat_score;              // 0x5A4
    float attack_stat_score;              // 0x5A8
    float strongest_attack_score;         // 0x5AC
    float strongest_social_score;         // 0x5B0
    float meanLookingScore;               // 0x5B4
    float maxPartLevel;                   // 0x5B8
    float averagePartLevel;               // 0x5BC
    float stealth_time;                   // 0x5C0
    float sprint_time;                    // 0x5C4
    uint32_t pad5c8[3];
    uint32_t u5d4, u5d8, u5dc, u5e0, u5e4, u5e8, u5ec, u5f0, u5f4;   // 0x5D4..0x5F4
    uint32_t pad5f8;
    uint32_t u5fc, u600, u604, u608, u60c, u610, u614, u618, u61c;   // 0x5FC..0x61C
    uint32_t pad620[2];
    uint32_t u628, u62c, u630, u634, u638;                            // 0x628..0x638
    float f63c;                           // 0x63C
    float f640;                           // 0x640
    float f644;                           // 0x644
    uint32_t u648;                        // 0x648
    uint32_t u64c, u650, u654, u658, u65c, u660, u664, u668;          // 0x64C..0x668
    float f66c;                           // 0x66C
    uint32_t u670;                        // 0x670
    uint32_t u674, u678, u67c, u680, u684, u688, u68c, u690;          // 0x674..0x690
    uint32_t u694, u698, u69c, u6a0, u6a4, u6a8, u6ac;                // 0x694..0x6AC
    uint32_t pad6b0[2];
    TransformVector mFruitTransforms;     // 0x6B8
    uint32_t pad6c4[3];
    uint32_t mFootType;                   // 0x6D0
    AbilityVector mAbilities;             // 0x6D4
    uint32_t pad6e4[(0x73c - 0x6e4) / 4];
    AbilityVector mPassiveAbilities;      // 0x73C
    uint32_t pad74c[(0x7a4 - 0x74c) / 4];
    UIntVector mCombatAbilityIdxs;        // 0x7A4
    uint32_t pad7b0[(0x80c - 0x7b0) / 4];
    bool b80c;                            // 0x80C
    bool b80d;                            // 0x80D
    uint8_t pad80e[2];
    UIntVector mFruitIdxs;                // 0x810
    uint32_t pad81c[(0x878 - 0x81c) / 4];
    UIntVector mMouthIdxs;                // 0x878
    uint32_t pad884[(0x8e0 - 0x884) / 4];
    UIntVector mGrasperIdxs;              // 0x8E0
    uint32_t pad8ec[(0x948 - 0x8ec) / 4];
    UIntVector mMouthIdxsCopy;            // 0x948
    uint32_t pad954[(0x9b0 - 0x954) / 4];
    UIntVector mGrasperIdxsCopy;          // 0x9B0
};
}

using namespace SP;

extern "C" int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);
#pragma intrinsic(wcscmp)

// @ 0x004D5020  SP::cSpeciesProfile::Update
bool cSpeciesProfile::Update(EditorRig* pRig)
{
    if (!pRig)
        return false;

    // ---- reset ----
    mSkinColors = pRig->mColors;
    creatureSeq++;
    num_graspers = 0.0f;
    num_mouths = 0.0f;
    num_ears = 0.0f;
    cuteness_stat_score = 0.0f;
    social_stat_score = 0.0f;
    mHasMass = false;
    averagePartLevel = 0.0f;
    strongest_social_score = 0.0f;
    meanLookingScore = 0.0f;
    maxPartLevel = 0.0f;
    stealth_time = 0.0f;
    sprint_time = 0.0f;
    jumping_ability = 0.0f;
    gliding_ability = 0.0f;
    flapping_ability = 0.0f;
    f63c = 0.0f;
    costToMakeCreature = 0;
    f640 = 10.0f;
    f644 = 1000.0f;
    f66c = 0.0f;
    u670 = 0;
    u648 = 0;
    mFruitTransforms.clear();
    capsInfos.clear();
    b80c = false;
    b80d = false;
    mFruitIdxs.clear();
    mMouthIdxs.clear();
    mGrasperIdxs.clear();
    mMouthIdxsCopy.clear();
    mGrasperIdxsCopy.clear();
    mModelFlags = pRig->mModelFlags;
    mAssetKey = 0xFFFFFFFFFFFFFFFEull;

    // ---- animated creature asset name / description ----
    if (animatedCreatureKey.instanceID != 0) {
        ResourceKey key = animatedCreatureKey;
        key.typeID = 0x030BDEE3;
        ResourceObjectPtr pResource;
        if (GetManager()->GetResource(key, pResource.AsParam(), 0, 0, 0, 0)) {
            cAssetMetadata* pMetadata = GetAssetMetadata(&pResource);
            if (pMetadata) {
                const wchar_t* pName = pMetadata->GetName();
                const wchar_t* pDesc = pMetadata->GetDescription();
                if (wcscmp(pName, L"") != 0)
                    animatedCreatureName = pName;
                animatedCreatureDesc = pDesc;
                mAssetKey = pMetadata->GetAssetKey();
            }
        }
    }

    // ---- per-block pass ----
    const uint32_t kToolPriceProperty = 0x02166464;
    const uint32_t kStealthProperty = 0x03A289AC;
    const uint32_t kScaleProperty = 0x06838638;
    float stealthCount = 0.0f;
    float stealthSum = 0.0f;
    float totalVolume = 0.0f;
    Vector3 boundsMin = Vector3(3.402823466e+38F, 3.402823466e+38F, 3.402823466e+38F);
    Vector3 boundsMax = V3Negate(boundsMin);

    int numBlocks = (int)(pRig->mBlocksEnd - pRig->mBlocksBegin);
    int blockCount = numBlocks;
    for (int blockIdx = 0; blockIdx < blockCount; blockIdx++) {
        RigBlock* pBlock = pRig->mBlocksBegin + blockIdx;
        PropertyList* pProp = GetPropertyListSource()->GetPropertyList(pBlock->mInstanceID,
                                                                       pBlock->mGroupID);
        float blockScale = 1.0f;
        if (pProp) {
            if (pBlock->mSymmetryIndex == -1 || pBlock->mSymmetryIndex > blockIdx) {
                int price = SP::cTribeTool::GetTutorialToolPrice(pProp, kToolPriceProperty, 0);
                costToMakeCreature = costToMakeCreature + price;
            }
            bool bIgnore = false;
            if (GetBoolProperty(pProp, 0x040FB917, &bIgnore) && bIgnore)
                continue;
            if (!mHasMass) {
                const uint32_t kMassProperty = 0x0D8800EB;
                GetBoolProperty(pProp, kMassProperty, &mHasMass);
            }
            int stealth = 0;
            if (TryGetIntProperty(pProp, kStealthProperty, &stealth)) {
                float fStealth = (float)stealth;
                stealth_time = Max(stealth_time, fStealth);
                stealthCount += (stealth > 0) ? 1.0f : 0.0f;
                stealthSum = (float)stealth + stealthSum;
            }
            blockScale = GetPropertyFloat(pProp, kScaleProperty, 1.0f);
        }

        Vector3* pPosition = &pBlock->mPosition;
        float minScale = pBlock->mScale * blockScale;
        Vector3 scaledMin = V3MulScalar(pBlock->mBoundsMin, minScale);
        float maxScale = pBlock->mScale * blockScale;
        Vector3 scaledMax = V3MulScalar(pBlock->mBoundsMax, maxScale);
        Matrix3* pRotation = &pBlock->mRotation;
        float halfA = 0.5f;
        Vector3 halfExtents = V3ScalarMul(halfA, V3Sub(scaledMax, scaledMin));
        float halfB = 0.5f;
        Vector3 center = V3Add(*pPosition,
                               V3MulMatrix(V3ScalarMul(halfB, V3Add(scaledMax, scaledMin)),
                                           *pRotation));
        float radius = V3Length(halfExtents);
        Vector3 radiusVec(radius, radius, radius);
        Vector3 lo = V3Sub(center, radiusVec);
        boundsMin = V3Min(boundsMin, lo);
        Vector3 hi = V3Add(center, radiusVec);
        boundsMax = V3Max(boundsMax, hi);
        float volume = 8.0f * halfExtents[0] * halfExtents[1] * halfExtents[2];
        totalVolume += volume;

        int capCount = pBlock->mCapCount;
        uint32_t* pCaps = pRig->mCaps + pBlock->mCapStart;
        uint8_t* pLevels = pRig->mCapLevels + pBlock->mCapStart;
        for (int capIdx = 0; capIdx < capCount; capIdx++) {
            uint32_t cap = pCaps[capIdx];
            uint32_t level = pLevels[capIdx];
            if (level == 0)
                continue;
            PartLayout* pInfo = &capsInfos[cap];
            pInfo->mCount++;
            pInfo->mSum += level;
            pInfo->mMax = Max(pInfo->mMax, level);
            pInfo->mScale += pBlock->mMass;
            pInfo->mWeight += volume;
            switch (cap) {
            case 0x74757266: {   // fruit
                uint32_t idx = blockIdx;
                mFruitIdxs.push_back(idx);
                cSPTransform transform;
                transform.SetOffset(center);
                transform.SetRotation(*pRotation);
                mFruitTransforms.push_back(transform);
                break;
            }
            case 0x74756f6d: {   // mouth
                uint32_t idx = blockIdx;
                mMouthIdxs.push_back(idx);
                break;
            }
            case 0x70737267: {   // grasper
                uint32_t idx = blockIdx;
                mGrasperIdxs.push_back(idx);
                break;
            }
            case 0x746f6f66:     // foot
                if (mFootType == 0)
                    mFootType = pBlock->mFootType;
                break;
            }
        }
    }

    mMouthIdxsCopy = mMouthIdxs;
    mGrasperIdxsCopy = mGrasperIdxs;
    mExtents = V3Sub(boundsMax, boundsMin);
    mBoundsMin = boundsMin;
    float one = 1.0f;
    sprint_time = stealthSum / Max(stealthCount, one);
    food_value = gFoodPerVolume * totalVolume;

    // ---- capability counts and levels ----
    num_graspers = (float)CountCap(this, 0x746f6f66);
    num_mouths = (float)CountCap(this, 0x70737267);
    num_ears = (float)CountCap(this, 0x74756f6d);
    sum_cuteness_parts = (float)CountCap(this, 0x00726165);
    u610 = GetCapLevel(this, 0x706d756a);
    u600 = GetCapLevel(this, 0x64707363);
    u614 = GetCapLevel(this, 0x746e7073);
    u618 = GetCapLevel(this, 0x736e6573);
    u61c = GetCapLevel(this, 0x64696c67);
    u628 = GetCapLevel(this, 0x6b746174);
    u62c = GetCapLevel(this, 0x636f7374);
    u630 = GetCapLevel(this, 0x6d726174);
    u634 = GetCapLevel(this, 0x68746774);
    u638 = GetCapLevel(this, 0x68736674);
    u5f4 = GetCapLevel(this, 0x6c657473);
    u5fc = GetCapLevel(this, 0x6c6c6163);
    u608 = GetCapLevel(this, 0x6e726163);
    u60c = GetCapLevel(this, 0x62726568);
    uint32_t meanCap = 0x6e61656d;
    averagePartLevel = (float)capsInfos[meanCap].mSum;
    u5d4 = GetCapLevel(this, 0x65746962);
    u5dc = GetCapLevel(this, 0x74697073);
    u5d8 = GetCapLevel(this, 0x65677263);
    u5e0 = GetCapLevel(this, 0x6b727473);
    u5e4 = GetCapLevel(this, 0x61636f76);
    u5e8 = GetCapLevel(this, 0x636e6164);
    u5ec = GetCapLevel(this, 0x6d726863);
    u5f0 = GetCapLevel(this, 0x74736f70);

    u64c = GetCapLevel(this, 0x6c736d61);
    u678 = GetCapLevel(this, 0x6c6d6d61);
    if (u64c > 0)
        u678 = 0;
    if (u64c > 0 || u678 > 0)
        u5d8 = 0;

    u650 = GetCapLevel(this, 0x646c6261);
    u67c = GetCapLevel(this, 0x6c627061);
    if (u650 > 0)
        u67c = 0;
    if (u650 > 0 || u67c > 0)
        u5d4 = 0;

    u658 = GetCapLevel(this, 0x77736c61);
    u680 = GetCapLevel(this, 0x7a726661);
    if (u658 > 0)
        u680 = 0;
    if (u658 > 0 || u680 > 0)
        u5e0 = 0;

    u65c = GetCapLevel(this, 0x6e677061);
    u674 = GetCapLevel(this, 0x736d7361);
    if (u65c > 0)
        u674 = 0;
    if (u65c > 0 || u674 > 0)
        u5dc = 0;

    u654 = GetCapLevel(this, 0x68636861);
    u68c = GetCapLevel(this, 0x68637261);
    if (u654 > 0)
        u68c = 0;
    if (u68c > 0 || u654 > 0)
        u5ec = 0;

    u684 = GetCapLevel(this, 0x7a776761);
    u6a8 = GetCapLevel(this, 0x6e647361);
    if (u6a8 > 0)
        u684 = 0;
    if (u6a8 > 0 || u684 > 0)
        u5e8 = 0;

    u688 = GetCapLevel(this, 0x6e736861);
    u6a4 = GetCapLevel(this, 0x736e6961);
    if (u6a4 > 0)
        u688 = 0;
    if (u6a4 > 0 || u688 > 0)
        u5e4 = 0;

    u690 = GetCapLevel(this, 0x73707261);
    u6ac = GetCapLevel(this, 0x73706361);
    if (u6ac > 0)
        u690 = 0;
    if (u6ac > 0 || u690 > 0)
        u5f0 = 0;

    // ---- ability weights from the global ability table ----
    float w1e = 1.0f, w20 = 1.0f, w1f = 1.0f, w21 = 1.0f, w3d = 1.0f, w3e = 1.0f;
    float w41 = 1.0f, w42 = 1.0f, w48 = 1.0f, w49 = 1.0f, w4a = 1.0f, w4b = 1.0f;
    float w25 = 1.0f, w22 = 1.0f, w24 = 1.0f, w23 = 1.0f, w40 = 1.0f, w4c = 1.0f;
    float w4d = 1.0f, w4e = 1.0f, w4f = 1.0f, w54 = 1.0f, w55 = 1.0f, w56 = 1.0f;
    for (cCreatureAbility** it = gCreatureAbilities.begin(); it != gCreatureAbilities.end(); ++it) {
        cCreatureAbility* pAbility = *it;
        switch (pAbility->mType) {
        case 0x1e: w1e = pAbility->mWeight; break;
        case 0x1f: w1f = pAbility->mWeight; break;
        case 0x20: w20 = pAbility->mWeight; break;
        case 0x21: w21 = pAbility->mWeight; break;
        case 0x3d: w3d = pAbility->mWeight; break;
        case 0x3e: w3e = pAbility->mWeight; break;
        case 0x41: w41 = pAbility->mWeight; break;
        case 0x42: w42 = pAbility->mWeight; break;
        case 0x48: w48 = pAbility->mWeight; break;
        case 0x49: w49 = pAbility->mWeight; break;
        case 0x4a: w4a = pAbility->mWeight; break;
        case 0x4b: w4b = pAbility->mWeight; break;
        case 0x22: w22 = pAbility->mWeight; break;
        case 0x23: w23 = pAbility->mWeight; break;
        case 0x24: w24 = pAbility->mWeight; break;
        case 0x25: w25 = pAbility->mWeight; break;
        case 0x40: w40 = pAbility->mWeight; break;
        case 0x4c: w4c = pAbility->mWeight; break;
        case 0x4d: w4d = pAbility->mWeight; break;
        case 0x4e: w4e = pAbility->mWeight; break;
        case 0x4f: w4f = pAbility->mWeight; break;
        case 0x54: w54 = pAbility->mWeight; break;
        case 0x55: w55 = pAbility->mWeight; break;
        case 0x56: w56 = pAbility->mWeight; break;
        }
    }

    // ---- social score: weighted sum and strongest single term ----
    strongest_social_score = (float)u5d4 * w1e + (float)u5dc * w20 + (float)u5d8 * w1f
                           + (float)u5e0 * w21 + (float)u64c * w3d + (float)u650 * w3e
                           + (float)u658 * w41 + (float)u65c * w42 + (float)u674 * w48
                           + (float)u678 * w49 + (float)u67c * w4a + (float)u680 * w4b;
    float social[12];
    social[11] = (float)u680 * w4b;
    social[10] = (float)u67c * w4a;
    social[9] = (float)u678 * w49;
    social[8] = (float)u674 * w48;
    social[7] = (float)u65c * w42;
    social[6] = (float)u658 * w41;
    social[5] = (float)u650 * w3e;
    social[4] = (float)u64c * w3d;
    social[3] = (float)u5e0 * w21;
    social[2] = (float)u5d8 * w1f;
    social[1] = (float)u5dc * w20;
    social[0] = (float)u5d4 * w1e;
    meanLookingScore = Max(social[0], Max(social[1], Max(social[2], Max(social[3],
                       Max(social[4], Max(social[5], Max(social[6], Max(social[7],
                       Max(social[8], Max(social[9], Max(social[10], social[11])))))))))));

    // ---- attack score ----
    strongest_attack_score = (float)u5e4 * w25 + (float)u5e8 * w22 + (float)u5ec * w24
                           + (float)u5f0 * w23 + (float)u654 * w40 + (float)u684 * w4c
                           + (float)u688 * w4d + (float)u68c * w4e + (float)u690 * w4f
                           + (float)u6a4 * w54 + (float)u6a8 * w55 + (float)u6ac * w56;
    float attack[12];
    attack[11] = (float)u6ac * w56;
    attack[10] = (float)u6a8 * w55;
    attack[9] = (float)u6a4 * w54;
    attack[8] = (float)u690 * w4f;
    attack[7] = (float)u68c * w4e;
    attack[6] = (float)u688 * w4d;
    attack[5] = (float)u684 * w4c;
    attack[4] = (float)u654 * w40;
    attack[3] = (float)u5f0 * w23;
    attack[2] = (float)u5ec * w24;
    attack[1] = (float)u5e8 * w22;
    attack[0] = (float)u5e4 * w25;
    maxPartLevel = Max(attack[0], Max(attack[1], Max(attack[2], Max(attack[3],
                   Max(attack[4], Max(attack[5], Max(attack[6], Max(attack[7],
                   Max(attack[8], Max(attack[9], Max(attack[10], attack[11])))))))))));

    // ---- remaining levels and bonuses ----
    u660 = GetCapLevel(this, 0x61746261);
    u664 = GetCapLevel(this, 0x61777061);
    u668 = GetCapLevel(this, 0x73626161);
    u648 = GetCapLevel(this, 0x6e677361);
    f66c = (float)GetCapBonus(this, 0x67726861) + f66c;
    u670 = GetCapBonus(this, 0x6e626861) * 100 + u670;
    f644 = (float)(GetCapBonus(this, 0x74736561) * 500) + f644;
    f640 = (float)(GetCapBonus(this, 0x6e677261) * 5) + f640;
    u694 = GetCapLevel(this, 0x62707361);
    if (u694 > 0)
        u614 = 0;
    u698 = GetCapLevel(this, 0x72766861);
    if (u698 > 0)
        u61c = u698;
    u69c = GetCapLevel(this, 0x6c667361);
    if (u69c > 0)
        u5f4 = 0;
    u6a0 = GetCapLevel(this, 0x6a6d6a61);
    if (u6a0 > 0)
        u610 = u6a0;
    u604 = GetCapLevel(this, 0x6c616568);
    float healthBonus = (float)u604 * gHealthPerLevel;
    f56c = Min(healthBonus, gMaxHealthBonus);
    f56c = (float)u630 * gHealthPerLevel + f56c;
    f56c = (float)u670 + f56c;

    PartLayout* pEye = GetCapInfo(this, 0x00657965);
    PartLayout* pFoot = GetCapInfo(this, 0x746f6f66);
    PartLayout* pCute = GetCapInfo(this, 0x65747563);
    PartLayout* pGrasper = GetCapInfo(this, 0x70737267);
    num_cuteness_parts = (float)pEye->mCount;
    cuteness_stat_score = (float)pCute->mSum;
    social_stat_score = (float)pCute->mCount;
    float oneA = 1.0f;
    float eyeAvg = pEye->mScale / Max(num_cuteness_parts, oneA);
    float oneB = 1.0f;
    float footAvg = pFoot->mScale / Max(num_graspers, oneB);
    float oneC = 1.0f;
    float grasperAvg = pGrasper->mScale / Max(num_mouths, oneC);
    float attackScore = BlendAttackScore(food_value, social_stat_score, cuteness_stat_score,
                                         num_cuteness_parts, eyeAvg, footAvg, grasperAvg);
    attack_stat_score = ClampF(attackScore, 0.0f, 100.0f);

    // ---- rebuild the ability lists ----
    mAbilities.clear();
    mPassiveAbilities.clear();
    void* pPropManager = PropertyManager();
    (void)pPropManager;
    for (cCreatureAbility** it = gCreatureAbilities.begin(); it != gCreatureAbilities.end(); ++it) {
        cCreatureAbility* pAbility = *it;
        PropertyList* pProp = pAbility->mpPropList;
        if (pProp->HasProperty(0x90F4B6B5)) {
            if (FillInProfileValues(pAbility, pProp))
                AddAbility(pAbility);
            continue;
        }

        bool bAllowed = true;
        int numExcluded = 0;
        uint32_t* pExcluded = 0;
        if (GetPropertyAsUint32Array(pProp, 0x07352141, &numExcluded, &pExcluded) && numExcluded > 0) {
            for (int i = 0; bAllowed && i < numExcluded; i++) {
                if (GetCapLevel(this, pExcluded[i]) != 0) {
                    bAllowed = false;
                    break;
                }
            }
        }
        if (!bAllowed)
            continue;

        int numRequired = 0;
        uint32_t* pRequired = 0;
        if (!GetPropertyAsUint32Array(pProp, 0x04052A6B, &numRequired, &pRequired) || numRequired <= 0)
            continue;

        int numMaxRanges = 0;
        Vector2* pMaxRanges = 0;
        GetPropertyAsVector2Array(pProp, 0x04052A86, &numMaxRanges, &pMaxRanges);
        int numSumRanges = 0;
        Vector2* pSumRanges = 0;
        GetPropertyAsVector2Array(pProp, 0x04052B30, &numSumRanges, &pSumRanges);

        Vector2 socialRange;
        if (GetPropertyAsVector2(pProp, 0x04AC8D53, &socialRange))
            bAllowed &= (strongest_social_score >= socialRange[0]
                         && socialRange[1] >= strongest_social_score) ? 1 : 0;
        Vector2 attackRange;
        if (GetPropertyAsVector2(pProp, 0x04AC8D56, &attackRange))
            bAllowed &= (strongest_attack_score >= attackRange[0]
                         && attackRange[1] >= strongest_attack_score) ? 1 : 0;

        for (int i = 0; bAllowed && i < numRequired; i++) {
            PartLayout& info = capsInfos[pRequired[i]];
            if (i < numMaxRanges) {
                uint32_t lo = RoundToInt(pMaxRanges[i][0]);
                uint32_t hi = RoundToInt(pMaxRanges[i][1]);
                bAllowed &= (info.mMax >= lo && info.mMax <= hi) ? 1 : 0;
            }
            if (i < numSumRanges) {
                uint32_t lo = RoundToInt(pSumRanges[i][0]);
                uint32_t hi = RoundToInt(pSumRanges[i][1]);
                uint32_t sum = info.mSum;
                bAllowed &= (sum >= lo && sum <= hi) ? 1 : 0;
            }
        }
        if (bAllowed && FillInProfileValues(pAbility, pProp))
            AddAbility(pAbility);
    }

    FinishUpdate();

    // ---- indices of the combat abilities ----
    mCombatAbilityIdxs.clear();
    uint32_t numAbilities = mAbilities.size();
    for (uint32_t i = 0; i < numAbilities; i++) {
        if (mAbilities[i]->mType == 0x25 || mAbilities[i]->mType == 0x22
            || mAbilities[i]->mType == 0x24 || mAbilities[i]->mType == 0x23
            || mAbilities[i]->mType == 0x40 || mAbilities[i]->mType == 0x4c
            || mAbilities[i]->mType == 0x4d || mAbilities[i]->mType == 0x4e
            || mAbilities[i]->mType == 0x4f || mAbilities[i]->mType == 0x54
            || mAbilities[i]->mType == 0x55 || mAbilities[i]->mType == 0x56) {
            uint32_t idx = i;
            mCombatAbilityIdxs.push_back(idx);
        }
    }
    return true;
}

#pragma pack(pop)
