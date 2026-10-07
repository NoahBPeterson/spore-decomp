// Slice s00f64290: one function
//   0x00F64290  SP::cDistGrid::SetupEffect   (3541 bytes, __thiscall, ret 0x1c)
// Dev-build symbol (SPTerrainDistributeEffect.obj):
//   ?SetupEffect@cDistGrid@SP@@QAEXABUcCellEffectInfo@2@PAVcIVisualEffect@Swarm@EA@@ABUcCell@2@HHHH@Z
// Configures one terrain-distribute cell effect: source transform (cell direction * height,
// scaled to the level's cell size), subdivision window, subdiv owner and distribute ID, then
// the resource overrides / height ranges / size scales for the cell's distribute type
// (a single type, or the 9-type "mixed" mode that packs every type present in the cell).
// Retail layout of cDistGrid differs from the 2008 PDB after +0x34 (+0x10 bytes), and the
// retail cTypeInfo is 0x40 bytes (PDB 0x38).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no EH frame although a local has a dtor).
#include "types.h"

namespace rw { namespace math {
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
inline Vector3 operator*(const Vector3& v, float s) {
    Vector3 r;
    r.x = v.x * s;
    r.y = v.y * s;
    r.z = v.z * s;
    return r;
}
struct Matrix3 {
    float m[3][3];
    Matrix3() {}
    Matrix3(const Matrix3& other);   // 0x0041CB40 (out of line)
};
extern Vector3 ZERO;                 // 0x016C9638 (Vector3::ZERO)
extern Matrix3 IDENTITY;             // 0x016C9614 (Matrix3::IDENTITY)
}}
using rw::math::Vector3;
using rw::math::Matrix3;

void* __cdecl operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                           const char* file, int line);   // 0x00F473A0

namespace EA {

namespace COM {
struct __declspec(novtable) IUnknown32 {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual void* AsInterface(uint32_t id) = 0;
};
}

template <class T> struct RefCountTemplate {
    RefCountTemplate() : mRefCount(0) {}
    virtual ~RefCountTemplate() {}
    T mRefCount;
};

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (p) p->AddRef(); }   // 0x00572660 when not inlined
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

namespace Swarm {

struct cTransform {                  // 0x38
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3  mTranslation;
    float    mScale;
    Matrix3  mRotation;

    cTransform() : mFlags(0), mModificationCount(0), mTranslation(rw::math::ZERO), mScale(1.0f),
                   mRotation(rw::math::IDENTITY) {}
    float GetScale() const { return mScale; }
    void SetTranslation(const Vector3& v) { mTranslation = v; mFlags |= 4; ++mModificationCount; }
    void SetScale(float s) { mScale = s; mFlags |= 1; ++mModificationCount; }
};

struct cUnknownBase : public COM::IUnknown32, public RefCountTemplate<int> {
};

struct cResourceOverride {           // 0x10
    uint64_t mID;
    uint32_t mSet;
    uint32_t mPad;
};

struct cResourceOverridesParam : public cUnknownBase {
    int mNumOverrides;               // +0x0c
    cResourceOverride mOverrides[1]; // +0x10
    static cResourceOverridesParam* Create(int count);   // 0x00A7A960
    virtual int AddRef();
    virtual int Release();
    virtual void* AsInterface(uint32_t id);
};

enum tSourceType { kSourceTerrainSphere = 6 };

struct cSubdivOwner : public cUnknownBase {   // 0x14
    tSourceType  mSourceType;        // +0x0c
    cTransform*  mSourceTransform;   // +0x10
    cSubdivOwner(tSourceType type, cTransform* transform)
        : mSourceType(type), mSourceTransform(transform) {}
    virtual int AddRef();            // 0x00C6A960 (shared Object::AddRef)
    virtual int Release();           // 0x007B86E0
    virtual void* AsInterface(uint32_t id);  // 0x00630030
};

struct cSubdivWindow {               // 0x18
    Vector3 mOffset;
    Vector3 mScale;
};

class cIVisualEffect {
public:
    enum tFloatParamType { kParamHeightRange = 16, kParamSubdivWindow = 17, kParamDistributeSizeScale = 20 };
    enum tIntParamType { kParamDistributeID = 4 };
    enum tUnknownParamType { kParamResourceOverrides = 3, kParamSubdivOwner = 4 };

    virtual int AddRef() = 0;                                        // 0x00
    virtual int Release() = 0;                                       // 0x04
    virtual void Start(int hardStart) = 0;                           // 0x08
    virtual int Stop(int hardStop) = 0;                              // 0x0c
    virtual int IsRunning() = 0;                                     // 0x10
    virtual void SetRigidTransform(const cTransform& t) = 0;         // 0x14
    virtual void SetSourceTransform(const cTransform& t) = 0;        // 0x18
    virtual void _v1c() = 0;
    virtual void _v20() = 0;
    virtual void _v24() = 0;
    virtual void _v28() = 0;
    virtual void _v2c() = 0;
    virtual void _v30() = 0;
    virtual void _v34() = 0;
    virtual void _v38() = 0;
    virtual void _v3c() = 0;
    virtual bool SetVectorParams(int param, const Vector3* data, int count) = 0;   // 0x40
    virtual bool SetFloatParams(int param, const float* data, int count) = 0;      // 0x44
    virtual bool SetIntParams(int param, const int* data, int count) = 0;          // 0x48
    virtual bool SetUnknownParam(int param, cUnknownBase* data) = 0;              // 0x4c
};

}  // namespace Swarm
}  // namespace EA

namespace SP {

using EA::Swarm::cIVisualEffect;
using EA::Swarm::cResourceOverridesParam;

struct cPropertyList;

struct cTerrainDistributeInfo : public EA::Swarm::cUnknownBase {
    struct cTypeInfo {               // 0x40 in retail
        cPropertyList* mProps;       // +0x00
        float    mMinEmitMap;        // +0x04
        float    mMaxEmitMap;        // +0x08
        float    mSpriteScale;       // +0x0c
        uint64_t mResourceIDs[5];    // +0x10
        uint32_t mUnknown38[2];      // +0x38
    };
    uint32_t  mPad0c;
    cTypeInfo mTypeInfo[9];          // +0x10
};

struct cCellEffectInfo {             // 0x10
    int   mEffectIndex;
    float mMinHeight;
    float mMaxHeight;
    char  mDistributeType;           // +0x0c
    char  mResourceType;             // +0x0d
    unsigned char mOverrideSet;      // +0x0e
};

struct cCell {                       // 0x18
    unsigned short mMinHeight;
    unsigned short mMaxHeight;       // +0x02
    unsigned short mTypeMask;        // +0x04
    short mActiveSlot;
    short mActiveChildren;
    Vector3 mDirection;              // +0x0c
};

enum { kNumDistTypes = 9, kNumResourceTypes = 5 };

class cDistGrid {
public:
    void SetupEffect(const cCellEffectInfo& info, cIVisualEffect* effect, const cCell& cell,
                     int level, int face, int x, int y);

    uint32_t mPad00[0x2c / 4];
    float    mHeightBase;                         // +0x2c
    float    mHeightRange16;                      // +0x30
    uint32_t mPad34[(0xa0 - 0x34) / 4];
    cTerrainDistributeInfo* mDistInfo;            // +0xa0 (AutoRefCount)
    uint32_t mPadA4;
    EA::Swarm::cTransform mSourceTransform;       // +0xa8
};

// @ 0x00f64290
void cDistGrid::SetupEffect(const cCellEffectInfo& info, cIVisualEffect* effect, const cCell& cell,
                            int level, int face, int x, int y)
{
    int levelSize = 1 << level;
    float invLevelSize = 1.0f / (float)levelSize;
    float cellSize = invLevelSize * 2.0f;

    // source transform: cell direction scaled to the cell's height, shrunk to the level
    EA::Swarm::cTransform transform;
    float height = (float)cell.mMaxHeight * mHeightRange16 + mHeightBase;
    transform.SetTranslation(cell.mDirection * height);
    transform.SetScale(transform.GetScale() * invLevelSize);
    effect->SetSourceTransform(transform);

    EA::Swarm::cSubdivWindow window;
    float center = (float)(levelSize - 1) * 0.5f;
    window.mOffset.x = ((float)x - center) * cellSize;
    window.mOffset.y = ((float)y - center) * cellSize;
    window.mOffset.z = (float)face;
    window.mScale.x = invLevelSize;
    window.mScale.y = invLevelSize;
    window.mScale.z = invLevelSize;
    effect->SetFloatParams(cIVisualEffect::kParamSubdivWindow, (const float*)&window, 6);

    effect->SetUnknownParam(cIVisualEffect::kParamSubdivOwner,
        new ("Swarm", 0, 0, 0, 0) EA::Swarm::cSubdivOwner(EA::Swarm::kSourceTerrainSphere, &mSourceTransform));

    int distID[2];
    int cellsPerFace = levelSize * levelSize;
    distID[0] = face * cellsPerFace + x + y * levelSize;
    distID[1] = cellsPerFace * 6;
    effect->SetIntParams(cIVisualEffect::kParamDistributeID, distID, 2);

    if (!mDistInfo || info.mDistributeType < 0)
        return;

    if (info.mDistributeType < kNumDistTypes) {
        const cTerrainDistributeInfo::cTypeInfo& typeInfo = mDistInfo->mTypeInfo[info.mDistributeType];

        if (info.mResourceType >= 0) {
        if (info.mResourceType == kNumResourceTypes) {
            EA::AutoRefCount<cResourceOverridesParam> overrides(cResourceOverridesParam::Create(kNumResourceTypes));
            overrides->mOverrides[0].mSet = info.mOverrideSet;
            overrides->mOverrides[0].mID = typeInfo.mResourceIDs[0];
            overrides->mOverrides[1].mSet = info.mOverrideSet + 1;
            overrides->mOverrides[1].mID = typeInfo.mResourceIDs[1];
            overrides->mOverrides[2].mSet = info.mOverrideSet + 2;
            overrides->mOverrides[2].mID = typeInfo.mResourceIDs[2];
            overrides->mOverrides[3].mSet = info.mOverrideSet + 3;
            overrides->mOverrides[3].mID = typeInfo.mResourceIDs[3];
            overrides->mOverrides[4].mSet = info.mOverrideSet + 4;
            overrides->mOverrides[4].mID = typeInfo.mResourceIDs[4];

            int set = info.mOverrideSet;
            float heights[12];
            heights[0] = typeInfo.mMinEmitMap;
            heights[1] = typeInfo.mMaxEmitMap;
            heights[2] = (float)set;
            heights[3] = typeInfo.mMinEmitMap;
            heights[4] = typeInfo.mMaxEmitMap;
            heights[5] = (float)(set + 1);
            heights[6] = typeInfo.mMinEmitMap;
            heights[7] = typeInfo.mMaxEmitMap;
            heights[8] = (float)(set + 2);
            heights[9] = typeInfo.mMinEmitMap;
            heights[10] = typeInfo.mMaxEmitMap;
            heights[11] = (float)(set + 3);
            float sizes[4];
            sizes[0] = typeInfo.mSpriteScale;
            sizes[1] = (float)(set + 2);
            sizes[2] = typeInfo.mSpriteScale;
            sizes[3] = (float)(set + 3);
            effect->SetUnknownParam(cIVisualEffect::kParamResourceOverrides, overrides);
            effect->SetFloatParams(cIVisualEffect::kParamHeightRange, heights, 12);
            effect->SetFloatParams(cIVisualEffect::kParamDistributeSizeScale, sizes, 4);
        } else {
            EA::AutoRefCount<cResourceOverridesParam> overrides(cResourceOverridesParam::Create(1));
            overrides->mOverrides[0].mSet = info.mOverrideSet;
            overrides->mOverrides[0].mID = typeInfo.mResourceIDs[info.mResourceType];

            float heights[3];
            heights[0] = typeInfo.mMinEmitMap;
            heights[1] = typeInfo.mMaxEmitMap;
            heights[2] = (float)info.mOverrideSet;
            effect->SetUnknownParam(cIVisualEffect::kParamResourceOverrides, overrides);
            effect->SetFloatParams(cIVisualEffect::kParamHeightRange, heights, 3);
            if (info.mResourceType >= 2) {
                float sizes[2];
                sizes[0] = typeInfo.mSpriteScale;
                sizes[1] = (float)info.mOverrideSet;
                effect->SetFloatParams(cIVisualEffect::kParamDistributeSizeScale, sizes, 2);
            }
        }
        } else {
            float heights[3];
            heights[0] = typeInfo.mMinEmitMap;
            heights[1] = typeInfo.mMaxEmitMap;
            heights[2] = (float)info.mOverrideSet;
            effect->SetFloatParams(cIVisualEffect::kParamHeightRange, heights, 3);
        }
        return;
    }

    // Mixed mode: every type present in the cell. Types come in 3 rows of 3; the types present
    // in a row are packed into slots row, row + 3, row + 6.
    // heights[slot][variant] = { min, max, set }, sizes[slot][pair] = { scale, set }
    float heights[9][4][3] = {
        { { 0, 0, 10 }, { 0, 0, 11 }, { 0, 0, 12 }, { 0, 0, 13 } },
        { { 0, 0, 20 }, { 0, 0, 21 }, { 0, 0, 22 }, { 0, 0, 23 } },
        { { 0, 0, 30 }, { 0, 0, 31 }, { 0, 0, 32 }, { 0, 0, 33 } },
        { { 0, 0, 40 }, { 0, 0, 41 }, { 0, 0, 42 }, { 0, 0, 43 } },
        { { 0, 0, 50 }, { 0, 0, 51 }, { 0, 0, 52 }, { 0, 0, 53 } },
        { { 0, 0, 60 }, { 0, 0, 61 }, { 0, 0, 62 }, { 0, 0, 63 } },
        { { 0, 0, 70 }, { 0, 0, 71 }, { 0, 0, 72 }, { 0, 0, 73 } },
        { { 0, 0, 80 }, { 0, 0, 81 }, { 0, 0, 82 }, { 0, 0, 83 } },
        { { 0, 0, 90 }, { 0, 0, 91 }, { 0, 0, 92 }, { 0, 0, 93 } },
    };
    float sizes[9][2][2] = {
        { { 0, 12 }, { 0, 13 } }, { { 0, 22 }, { 0, 23 } }, { { 0, 32 }, { 0, 33 } },
        { { 0, 42 }, { 0, 43 } }, { { 0, 52 }, { 0, 53 } }, { { 0, 62 }, { 0, 63 } },
        { { 0, 72 }, { 0, 73 } }, { { 0, 82 }, { 0, 83 } }, { { 0, 92 }, { 0, 93 } },
    };

    EA::AutoRefCount<cResourceOverridesParam> overrides(
        cResourceOverridesParam::Create(kNumDistTypes * kNumResourceTypes));
    for (int i = 0; i < kNumDistTypes; i++) {
        for (int j = 0; j < kNumResourceTypes; j++)
            overrides->mOverrides[i * kNumResourceTypes + j].mSet = (i + 1) * 10 + j;
    }

    int type = 0;
    for (int row = 0; row < 3; row++) {
        int slot = row;
        for (int i = 0; i < 3; i++, type++) {
            if (cell.mTypeMask & (1 << type)) {
                const cTerrainDistributeInfo::cTypeInfo& typeInfo = mDistInfo->mTypeInfo[type];
                for (int j = 0; j < kNumResourceTypes; j++) {
                    overrides->mOverrides[slot * kNumResourceTypes + j].mID = typeInfo.mResourceIDs[j];
                    overrides->mOverrides[slot * kNumResourceTypes + j].mSet = (slot + 1) * 10 + j;
                }
                sizes[slot][0][0] = typeInfo.mSpriteScale;
                sizes[slot][1][0] = typeInfo.mSpriteScale;
                for (int j = 0; j < 4; j++) {
                    heights[slot][j][0] = typeInfo.mMinEmitMap;
                    heights[slot][j][1] = typeInfo.mMaxEmitMap;
                }
                slot += 3;
            }
        }
    }

    effect->SetUnknownParam(cIVisualEffect::kParamResourceOverrides, overrides);
    effect->SetFloatParams(cIVisualEffect::kParamHeightRange, &heights[0][0][0], 9 * 4 * 3);
    effect->SetFloatParams(cIVisualEffect::kParamDistributeSizeScale, &sizes[0][0][0], 9 * 2 * 2);
}

}  // namespace SP
