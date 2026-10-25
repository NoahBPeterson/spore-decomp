// w1g1 slice s004f2d40 -- editor validity table accessors.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------------------
// Shared engine types (layouts and names from the dev PDB).
// ---------------------------------------------------------------------------

struct cSPVector3 { float x, y, z; };
struct cSPMatrix3 { cSPVector3 r[3]; };

cSPVector3 operator+(const cSPVector3& a, const cSPVector3& b);   // 0x0041dc10
cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b);   // 0x0041db10
cSPVector3 operator*(const cSPVector3& a, const float& s);        // 0x0041dca0
cSPMatrix3 operator*(const cSPMatrix3& a, const cSPMatrix3& b);   // 0x0041de20
float       VectorLength(const cSPVector3& v);                    // 0x0040ae50

struct Transform {
    uint16_t mFlags;                 // +0x00
    uint16_t mModificationCount;     // +0x02
    cSPVector3 mTranslation;         // +0x04
    float mScale;                    // +0x10
    cSPMatrix3 mRotation;            // +0x14
    Transform();                     // 0x00409930
    void SetTranslation(const cSPVector3& v)
    {
        mTranslation = v;
        mFlags |= 4;
        mModificationCount++;
    }
    void SetRotation(const cSPMatrix3& m)
    {
        mRotation = m;
        mFlags |= 2;
        mModificationCount++;
    }
    void SetScale(float s)
    {
        mScale = s;
        mModificationCount++;
    }
};

struct cSPBoundingBox {
    cSPVector3 mMin;                 // +0x00
    cSPVector3 mMax;                 // +0x0c
    void Reset();                    // 0x00409c00
    void Scale(float s);             // 0x0044ad00
    bool Intersects(const cSPBoundingBox& other) const;  // 0x00490330
    void Transform(const Transform& t);                  // 0x00409dd0
};

struct cSPColorRGB { cSPVector3 mColor; };

// SP::cSerializedEditorBlock, 0x1d8 bytes.
struct cSerializedEditorBlock {
    uint32_t mGroup;                 // +0x000
    uint32_t mInstance;              // +0x004
    uint32_t mParentIndex;           // +0x008
    uint32_t mSymmetricIndex;        // +0x00c
    float mUniformScale;             // +0x010
    cSPVector3 mPosition;            // +0x014
    cSPVector3 mPinningDirection;    // +0x020
    cSPVector3 mPinningOrigin;       // +0x02c
    cSPMatrix3 mBaseOrientation;     // +0x038
    cSPMatrix3 mUserOrientation;     // +0x05c
    uint8_t mIsSnapped;              // +0x080
    uint8_t mReserved1;              // +0x081
    uint8_t mReserved2;              // +0x082
    uint8_t mReserved3;              // +0x083
    uint32_t mLimbType;              // +0x084
    float mMuscleScale;              // +0x088
    float mBaseJointScale;           // +0x08c
    uint32_t mNumHandles;            // +0x090
    float mHandlePositions[8];       // +0x094
    uint32_t mHandleAnimations[8];   // +0x0b4
    uint32_t mNumPaintRegions;       // +0x0d4
    int32_t mPaintRegions[8];        // +0x0d8
    uint32_t mPaintIDs[8];           // +0x0f8
    cSPColorRGB mPaintColor1s[8];    // +0x118
    cSPColorRGB mPaintColor2s[8];    // +0x178
};

struct LimbVec {
    cSerializedEditorBlock* mpBegin;
    cSerializedEditorBlock* mpEnd;
    cSerializedEditorBlock& operator[](int i) { return mpBegin[i]; }
    const cSerializedEditorBlock& operator[](int i) const { return mpBegin[i]; }
    int size() const
    {
        return (int)((const char*)mpEnd - (const char*)mpBegin) / (int)sizeof(cSerializedEditorBlock);
    }
};

struct Model {
    uint8_t pad0[0x98];
    LimbVec mLimbs;                  // +0x98
};

struct PropertyList;                 // opaque here; only passed through
void GetBoolProperty(PropertyList* pl, uint32_t id, bool& dst);   // 0x00407190

namespace SP {
bool GetPropertyAsVector3(const PropertyList* pl, uint32_t id, cSPVector3* out);  // 0x006a1110
}

// Entry-owner vtable: +0x54 = bounding box from limb part positions, +0x58 = property list.
struct EntryOwner {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual void v6();  virtual void v7();
    virtual void v8();  virtual void v9();  virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20();
    virtual void GetBoundingBoxFromParts(uint32_t instance, uint32_t group,
                                         const float* positions, uint32_t count,
                                         cSPBoundingBox* bbox, cSPVector3* max);  // +0x54
    virtual PropertyList* GetPropertyList(uint32_t instance, uint32_t group);      // +0x58
};

EntryOwner* FUN_00401010();                                        // 0x00401010

// bitset<128> used for the editor-validity flag words.
struct ValidityBits {
    uint32_t w[4];
    uint32_t& DoGetWord(uint32_t i) { return w[i >> 5]; }
    uint32_t DoGetWord(uint32_t i) const { return w[i >> 5]; }
    __forceinline void set(uint32_t i, bool value)
    {
        if (i < 0x80) {
            if (value) DoGetWord(i) |= 1u << (i % 32);
            else       DoGetWord(i) &= ~(1u << (i % 32));
        }
    }
};

// Property ids.
static const uint32_t kModelHasBallConnector          = 0x4ff31eec;
static const uint32_t kModelHasSocketConnector        = 0x6ff31f12;
static const uint32_t kModelIsVertebra                = 0xafff3a14;
static const uint32_t kModelUseSkin                   = 0x9069c7c8;
static const uint32_t kModelMinSocketConnectorOffset  = 0x3061e2b3;
static const uint32_t kModelMaxSocketConnectorOffset  = 0x3061e2b8;
static const uint32_t kDeformBoneLength               = 0x9310d4c0;
static const uint32_t kModelCanBeParentless           = 0x8e31d974;
static const uint32_t kModelActsLikeFoot              = 0x4a33896;
static const uint32_t kModelActsLikeGrasper           = 0x4a3386d;

// Default socket-connector offset (read from 0x015dabac in the image).
extern const cSPVector3 gDefaultSocketOffset;

struct Entry { int a; int b; };
extern Entry g_150c920[];
extern int g_150c924[];

// ===========================================================================
// @ 0x004f3c40  (MATCH)
// Returns the first field of the i-th 8-byte global entry.
// ===========================================================================
int FUN_004f3c40(int i)
{
    return g_150c920[i].a;
}

// ===========================================================================
// @ 0x004f3b40  (complete; not byte-exact)
// Picks the entry with the largest metric among indices set in both bit masks
// (28 indices); 0x1c when none.
// ===========================================================================
struct Bits128 { uint32_t w[4]; };

int FUN_004f3b40(Bits128 a, Bits128 b)
{
    int best = -1;
    bool found = false;
    unsigned int i;
    int bestIdx;
    for (i = 0; i < 0x1c; i++) {
        bool inA = false;
        if (i < 0x80)
            inA = (a.w[i >> 5] & (1u << (i % 0x20))) != 0;
        if (inA) {
            bool inB = false;
            if (i < 0x80)
                inB = (b.w[i >> 5] & (1u << (i % 0x20))) != 0;
            if (inB) {
                int cand = g_150c924[i * 2];
                if (cand > best) {
                    best = cand;
                    bestIdx = i;
                    found = true;
                }
            }
        }
    }
    if (found)
        return bestIdx;
    return 0x1c;
}

// ===========================================================================
// @ 0x004f2d40
// Builds one limb/block bounding box, either a socket capsule, the fixed
// vertebra box, or the owner's part-derived box, then applies the block
// transform.
// ===========================================================================
void FUN_004f2d40(cSerializedEditorBlock* block, PropertyList* blockProps,
                  cSPBoundingBox* bbox, cSerializedEditorBlock* childBlock)
{
    bool hasBallConnector = false;
    GetBoolProperty(blockProps, kModelHasBallConnector, hasBallConnector);
    bool hasSocketConnector = false;
    GetBoolProperty(blockProps, kModelHasSocketConnector, hasSocketConnector);
    bool isVertebra = false;
    GetBoolProperty(blockProps, kModelIsVertebra, isVertebra);
    bool useSkin = false;
    GetBoolProperty(blockProps, kModelUseSkin, useSkin);
    bool connected = hasSocketConnector && hasBallConnector && useSkin;
    if (connected) {
        cSPVector3 minOffset = gDefaultSocketOffset;
        cSPVector3 maxOffset = gDefaultSocketOffset;
        SP::GetPropertyAsVector3(blockProps, kModelMinSocketConnectorOffset, &minOffset);
        SP::GetPropertyAsVector3(blockProps, kModelMaxSocketConnectorOffset, &maxOffset);
        float radius = (block->mBaseJointScale + childBlock->mBaseJointScale) * 0.5f;
        float boneLength = -1.0f;
        for (int i = 0; i < (int)block->mNumHandles; i++) {
            if (block->mHandleAnimations[i] == kDeformBoneLength)
                boneLength = block->mHandlePositions[i];
        }
        if (boneLength == -1.0f)
            boneLength = block->mHandlePositions[0];
        float length = VectorLength(minOffset + (maxOffset - minOffset) * boneLength);
        float w = radius * 0.06f;
        bbox->mMin.x = -w;
        bbox->mMin.y = -length;
        bbox->mMin.z = -w;
        bbox->mMax.x = w;
        bbox->mMax.y = 0.0f;
        bbox->mMax.z = w;
    } else if (isVertebra) {
        bbox->mMin.x = -0.19f;
        bbox->mMin.y = -0.07f;
        bbox->mMin.z = -0.35f;
        bbox->mMax.x = 0.19f;
        bbox->mMax.y = 0.07f;
        bbox->mMax.z = 0.03f;
    } else {
        FUN_00401010()->GetBoundingBoxFromParts(block->mInstance, block->mGroup,
                                                block->mHandlePositions, block->mNumHandles,
                                                bbox, &bbox->mMax);
    }
    Transform t;
    t.mTranslation = block->mPosition;
    t.mFlags |= 4;
    t.mModificationCount++;
    cSPMatrix3 blockTransform = block->mUserOrientation * block->mBaseOrientation;
    t.mRotation = blockTransform;
    t.mFlags |= 2;
    t.mModificationCount++;
    t.mScale = block->mUniformScale;
    t.mModificationCount++;
    bbox->Transform(t);
}

// ===========================================================================
// @ 0x004f31c0
// Editor-validity test "intersecting end effectors". The shipped body is an
// early-out stub; the original full test follows it as (statically
// unreachable) source.
// ===========================================================================
bool FUN_004f31c0(Model* model, ValidityBits* flags)
{
    if (flags) flags->set(19, false);
    return true;

    LimbVec* pv = &model->mLimbs;
    int i = 0;
    int n = pv->size();
    for (; i < n; i++) {
        PropertyList* pl = FUN_00401010()->GetPropertyList((*pv)[i].mInstance, (*pv)[i].mGroup);
        if (!pl) {
            if (flags) flags->set(19, false);
            return false;
        }
        bool foot = false;
        bool grasper = false;
        GetBoolProperty(pl, kModelActsLikeFoot, foot);
        GetBoolProperty(pl, kModelActsLikeGrasper, grasper);
        if (!foot && !grasper)
            continue;
        cSPBoundingBox bb1, bb2;
        bb1.Reset();
        bb2.Reset();
        uint32_t idx = (*pv)[i].mSymmetricIndex;
        if (idx >= (uint32_t)n)
            continue;
        PropertyList* pl2 = FUN_00401010()->GetPropertyList((*pv)[idx].mInstance, (*pv)[idx].mGroup);
        if (!pl2) {
            if (flags) flags->set(19, false);
            return false;
        }
        FUN_004f2d40(&(*pv)[idx], pl2, &bb2, 0);
        FUN_004f2d40(&(*pv)[i], pl, &bb1, 0);
        bb1.Scale(1.2f);
        bb2.Scale(1.2f);
        if (bb2.Intersects(bb1)) {
            if (flags) flags->set(19, true);
            return false;
        }
    }
    return true;
}

// ===========================================================================
// @ 0x004f3650
// Editor-validity test "has floating parts". The shipped body is an early-out
// stub; the original full test follows it as (statically unreachable) source.
// ===========================================================================
bool FUN_004f3650(Model* model, ValidityBits* flags)
{
    if (flags) flags->set(13, false);
    return true;

    LimbVec* pv = &model->mLimbs;
    int i = 0;
    int n = pv->size();
    for (; i < n; i++) {
        PropertyList* pl = FUN_00401010()->GetPropertyList((*pv)[i].mInstance, (*pv)[i].mGroup);
        if (!pl) {
            if (flags) flags->set(13, false);
            return false;
        }
        bool canBeParentless = true;
        GetBoolProperty(pl, kModelCanBeParentless, canBeParentless);
        if (canBeParentless)
            continue;
        cSPBoundingBox bb1, bb2;
        bb1.Reset();
        bb2.Reset();
        uint32_t idx = (*pv)[i].mParentIndex;
        if (idx >= (uint32_t)n)
            continue;
        PropertyList* pl2 = FUN_00401010()->GetPropertyList((*pv)[idx].mInstance, (*pv)[idx].mGroup);
        if (!pl2) {
            if (flags) flags->set(13, false);
            return false;
        }
        FUN_004f2d40(&(*pv)[idx], pl2, &bb2, &(*pv)[i]);
        int parent = -1;
        for (int j = 0; j < n; j++) {
            if ((*pv)[j].mParentIndex == (uint32_t)i) {
                parent = j;
                break;
            }
        }
        cSerializedEditorBlock* parentBlock = (parent != -1) ? &(*pv)[parent] : 0;
        FUN_004f2d40(&(*pv)[i], pl, &bb1, parentBlock);
        bb1.Scale(1.2f);
        bb2.Scale(1.2f);
        if (!bb2.Intersects(bb1)) {
            if (flags) flags->set(13, true);
            return false;
        }
    }
    return true;
}
