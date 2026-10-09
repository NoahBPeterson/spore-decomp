// Slice s00441440: the single function in this slice is
//   SP::cSPEditorBlock::BuildBlock   (0x00441440, 23469 bytes, thiscall, ret 0x20)
//
// The editor rigblock (ModAPI: Editors::EditorRigblock) initialiser. It (re)binds the
// block's model world / model / property list, reads ~60 "model*" properties from the
// part's property list into the block (boolean attribute bitset, scales, snap and pinning
// settings, nine ResourceKey lists, capabilities), creates the ball connector, socket
// connector model, rotation ring / rotation ball handles and per-bone deform handles,
// and records the "effect" / "csnap" bone transforms.
//
// Module flags: editor /Od region, `/Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast` (no /EHsc).
// Layout: retail offsets (they match the ModAPI EditorRigblock header, not the 2008 PDB).
// Property IDs are FNV hashes; their names (from SporeModder-FX's registry) are in the
// comments. Callees whose purpose is unknown keep a Sub_<va> name.
//
// Bookkeeping: nonmatching.txt (complete, not byte-exact).
#include "types.h"
#include <stddef.h>
#include <math.h>
#pragma intrinsic(fabs)

#define S441_CAT2(a, b) a##b
#define S441_CAT(a, b) S441_CAT2(a, b)
#define CHECK_OFFSET(T, m, off) \
    typedef char S441_CAT(check_offset_, __LINE__)[(offsetof(T, m) == (off)) ? 1 : -1]

void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);

// ---------------------------------------------------------------- math
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    float& operator[](int i) { return (&x)[i]; }
};

// rw::math::Matrix33Template<float,0>
struct Matrix33 {
    float m[9];
};

// cSPMatrix3
struct Matrix3 {
    Vector3 m[3];
    Matrix3() {}
    Matrix3(const Matrix33& other);  // 0x0041cb40
};

struct BoundingBox {
    Vector3 mMin;
    Vector3 mMax;
    BoundingBox();  // 0x00409c00
};

Vector3 operator*(const Vector3& v, const float& s);           // 0x0041dca0
Vector3 operator*(const float& s, const Vector3& v);           // 0x0041de40
Vector3 operator-(const Vector3& a, const Vector3& b);         // 0x0041db10
Vector3 operator+(const Vector3& a, const Vector3& b);         // 0x0041dc10
float VectorLength(const Vector3& v);                          // 0x0040ae50
Matrix33 Matrix33FromEulerXYZ(const Vector3& eulerRadians);    // 0x00453920

extern const Vector3 kVector3Zero;      // 0x015d255c
extern const Matrix3 kMatrix3Identity;  // 0x015d2428

inline float Abs(float x) { return (float)fabs(x); }

// maxss then minss, with SSE NaN semantics (a NaN input yields lo).
inline float Clamp(float x, float lo, float hi)
{
    float t = x;
    t = (t > lo) ? t : lo;
    t = (t < hi) ? t : hi;
    return t;
}

// cSPTransform (0x38 bytes)
struct Transform {
    uint16_t mFlags;        // +0x00
    uint16_t mChangeCount;  // +0x02
    Vector3 mOffset;        // +0x04
    float mScale;           // +0x10
    Matrix3 mRotation;      // +0x14

    Transform();                                  // 0x00409930
    Transform& operator=(const Transform& other); // 0x00537dc0
    void Accumulate(const Transform& other);      // 0x0040ccb0
    void AccumulateScaled(const Transform& other);// 0x0040cd80

    void SetOffset(const Vector3& offset)
    {
        mOffset = offset;
        mFlags |= 4;
        mChangeCount++;
    }
    void SetRotation(const Matrix3& rotation)
    {
        mRotation = rotation;
        mFlags |= 2;
        mChangeCount++;
    }
};

// RenderWare::cMDBoneTransform (0x30 bytes)
struct BoneTransform {
    float m[12];
};
void BoneTransformToTransform(const BoneTransform* src, Transform* dst);  // 0x00732270

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

// ---------------------------------------------------------------- EASTL-style containers
template <int N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];

    __forceinline bool test(uint32_t n) const
    {
        if (n < N)
            return (mWord[n >> 5] & (1u << (n % 32))) != 0;
        return false;
    }
    __forceinline void set(uint32_t n, bool value)
    {
        if (n < N) {
            if (value)
                mWord[n >> 5] |= 1u << (n % 32);
            else
                mWord[n >> 5] &= ~(1u << (n % 32));
        }
    }
};

// eastl::fixed_vector<T, N>: three pointers, the overflow allocator, then the inline buffer.
template <class T, int N>
struct fixed_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    uint32_t mBuffer[(N * sizeof(T)) / 4];

    fixed_vector() {}
    explicit fixed_vector(unsigned int n);  // out of line (0x0041d0c0 / 0x0041d510)
    ~fixed_vector()
    {
        for (T* p = mpBegin; p < mpEnd; ++p)
            p->~T();
        DoFree();
    }
    void DoFree();  // out of line (0x004c0b80 / 0x00428130)

    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const;               // out of line (0x00526430, ICF-shared)
    T& operator[](int i) { return mpBegin[i]; }
    T* erase(T* first, T* last);      // out of line
    void resize(unsigned int n);      // out of line
    void push_back(const T& value);   // out of line
    void clear() { erase(mpBegin, mpEnd); }
};

template <class T>
struct AutoRefCount {
    T* mpObject;

    AutoRefCount& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// eastl::fixed_string<char, 32>
struct FixedString32 {
    uint32_t mData[13];
    FixedString32& operator=(const char* p);  // 0x00453690
};

// ---------------------------------------------------------------- properties
struct Property {
    void* mpData;        // +0x00 (array data, or the inline value itself)
    uint32_t pad04;
    int mnItemCount;     // +0x08
    uint32_t pad0c;
    uint16_t mnFlags;    // +0x10 (0x30 = array)
    uint16_t mnType;     // +0x12

    void* GetValuePtr();     // 0x00446ff0
    int* GetValueInt32();    // 0x0041e990

    int GetItemCount()
    {
        if (mnFlags & 0x30)
            return mnItemCount;
        else if (mnType != 0)
            return 1;
        return 0;
    }
    void* GetItems()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
};

extern const bool kDefaultBoolValue;    // 0x015d115d
extern const float kDefaultFloatValue;  // 0x015d1168
const ResourceKey* GetDefaultKeyValue();   // 0x006bb640
const Vector3* GetDefaultVector3Value();   // 0x006bb5e0

__forceinline const bool* GetValueBool(Property* p)
{
    return (p->mnType == 1 || p->mnType == 0x10) ? (const bool*)p->GetValuePtr() : &kDefaultBoolValue;
}
__forceinline const float* GetValueFloat(Property* p)
{
    return (p->mnType == 0xd || p->mnType == 0x10) ? (const float*)p->GetValuePtr() : &kDefaultFloatValue;
}
__forceinline const ResourceKey* GetValueKey(Property* p)
{
    return (p->mnType == 0x20 || p->mnType == 0x10) ? (const ResourceKey*)p->GetValuePtr() : GetDefaultKeyValue();
}
__forceinline const Vector3* GetValueVector3(Property* p)
{
    return (p->mnType == 0x31 || p->mnType == 0x10) ? (const Vector3*)p->GetValuePtr() : GetDefaultVector3Value();
}

class cPropertyList {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void SetProperty(uint32_t id, const Property* p);
    virtual int RemoveProperty(uint32_t id);
    virtual bool HasProperty(uint32_t id);                       // 0x1c
    virtual bool GetPropertyAlt(uint32_t id, Property*& result); // 0x20
    virtual bool GetProperty(uint32_t id, Property*& result);    // 0x24
    virtual Property* GetPropertyObject(uint32_t id);            // 0x28
};

bool GetBoolProperty(cPropertyList* list, uint32_t id, bool& value);              // 0x00407190
bool GetFloatProperty(cPropertyList* list, uint32_t id, float& value);            // 0x0040cf10
bool TryGetUIntProperty(cPropertyList* list, uint32_t id, uint32_t& value);       // 0x00410370
bool GetPropertyAsKey(cPropertyList* list, uint32_t id, ResourceKey& value);      // 0x006a1250
bool GetPropertyAsKeyInstance(cPropertyList* list, uint32_t id, uint32_t& value); // 0x006a12a0
bool GetPropertyAsVector3(cPropertyList* list, uint32_t id, Vector3& value);      // 0x006a1110
bool GetPropertyAsChar8Ptr(cPropertyList* list, uint32_t id, const char*& value); // 0x006a1450

inline bool GetIntProperty(cPropertyList* list, uint32_t id, int& value)
{
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 9) {
        value = *prop->GetValueInt32();
        return true;
    }
    return false;
}

// Loads a ResourceKey-array property into one of the block's key lists; returns the count.
template <int N>
inline void CopyKeys(fixed_vector<ResourceKey, N>& dst, int count, const ResourceKey* keys)
{
    dst.resize(count);
    for (int i = 0; i < count; i++)
        dst[i] = keys[i];
}

// ---------------------------------------------------------------- model world
class IUnknown32 {
public:
    virtual int AddRef();
    virtual int Release();
};

class IModelWorld;

// Graphics::Model
struct cMWModel {
    IModelWorld* mpWorld;                 // +0x00
    bitset<32> mFlags;                    // +0x04
    Transform mTransform;                 // +0x08
    int mnRefCount;                       // +0x40
    bitset<64> mGroupFlags;               // +0x44
    float mColor[4];                      // +0x4c
    bool field_5C;                        // +0x5c
    uint8_t mCollisionMode;               // +0x5d
    uint8_t pad5e[2];
    int field_60;                         // +0x60
    AutoRefCount<IUnknown32> mpOwner;     // +0x64
    uint32_t pad68[2];
    BoundingBox mDefaultBBox;             // +0x70
    uint32_t pad88[2];
    cPropertyList* mpPropList;            // +0x90

    int AddRef() { return ++mnRefCount; }
    int Release();                        // 0x0040f360
    void SetVisible(bool visible);        // 0x00437f70
};
CHECK_OFFSET(cMWModel, mnRefCount, 0x40);
CHECK_OFFSET(cMWModel, mCollisionMode, 0x5d);
CHECK_OFFSET(cMWModel, mpOwner, 0x64);
CHECK_OFFSET(cMWModel, mDefaultBBox, 0x70);
CHECK_OFFSET(cMWModel, mpPropList, 0x90);

class IModelWorld {
public:
    virtual int AddRef();                                                     // 0x00
    virtual int Release();                                                    // 0x04
    virtual void v08();
    virtual cMWModel* CreateModel(uint32_t instanceID, uint32_t groupID, int flags);  // 0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual void StallUntilLoaded(cMWModel* model);                           // 0x58
    virtual void v5c(); virtual void v60(); virtual void v64();
    virtual int GetNumAnimations(cMWModel* model, int animationGroup);        // 0x68
    virtual int GetAnimationIDs(cMWModel* model, uint32_t* dst, int animationGroup);  // 0x6c
    virtual void AnimAction(cMWModel* model, uint32_t animID, int arg3, float arg4, int animationGroup);  // 0x70
    virtual void v74(); virtual void v78(); virtual void v7c(); virtual void v80();
    virtual int GetNumBones(cMWModel* model);                                 // 0x84
    virtual int GetPoseTransforms(cMWModel* model, BoneTransform* dst, bool original);  // 0x88
    virtual int GetBoneTransforms(cMWModel* model, BoneTransform* dst);       // 0x8c
    virtual int GetBoneIDs(cMWModel* model, uint32_t* dst);                   // 0x90
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual void va4(); virtual void va8(); virtual void vac(); virtual void vb0();
    virtual void vb4(); virtual void vb8(); virtual void vbc(); virtual void vc0();
    virtual void vc4(); virtual void vc8(); virtual void vcc(); virtual void vd0();
    virtual void SetExternalEffectsTransform(cMWModel* model, const Transform* t, uint32_t instanceID);  // 0xd4
    virtual void vd8(); virtual void vdc();
    virtual void ReleaseTransformedHull(int* hull);                           // 0xe0
    virtual void ve4();
    virtual int GetDeformationHandles(cMWModel* model, void* dst, int count); // 0xe8
    virtual void vec(); virtual void vf0(); virtual void vf4(); virtual void vf8();
    virtual void vfc(); virtual void v100(); virtual void v104();
    virtual Transform* GetMeshTransform(cMWModel* model);                     // 0x108
    virtual void v10c(); virtual void v110(); virtual void v114(); virtual void v118();
    virtual void v11c(); virtual void v120(); virtual void v124(); virtual void v128();
    virtual void v12c(); virtual void v130(); virtual void v134(); virtual void v138();
    virtual void v13c(); virtual void v140(); virtual void v144(); virtual void v148();
    virtual void v14c(); virtual void v150(); virtual void v154(); virtual void v158();
    virtual void v15c(); virtual void v160(); virtual void v164(); virtual void v168();
    virtual bool SetInWorld(cMWModel* model, bool inWorld);                   // 0x16c
};

class IModelManager {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual int GetGroupFlag(uint32_t groupID, int arg);  // 0x28
};
namespace SP { IModelManager* ModelManager(); }  // 0x0067dd80

// Returned by 0x00401010: the editor's property-list source.
class IBlockPropertySource {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual cPropertyList* GetPropertyList(uint32_t instanceID, uint32_t groupID);  // 0x58
    virtual void v5c(); virtual void v60(); virtual void v64(); virtual void v68();
    virtual float GetPropertyListFloat(cPropertyList* list);                      // 0x6c
};
IBlockPropertySource* BlockPropertySource();  // 0x00401010

extern const uint32_t kEditorModelGroupID;  // 0x015d22e8

// ---------------------------------------------------------------- editor handles
namespace SP {
class cSPEditorBlock;

class cSPEditorHandle {
public:
    virtual int AddRef();          // 0x00
    virtual int Release();         // 0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18();
    virtual void Dispose();        // 0x1c
    virtual void SetScale(float scale);  // 0x20
};

class cSPEditorHandleBallConnector : public cSPEditorHandle {
public:
    uint32_t mData[(0x50 - 4) / 4];
    cSPEditorHandleBallConnector();   // 0x0047f4b0
    void Init(cSPEditorBlock* block); // 0x0047f720
};

class cSPEditorHandleRotationBall : public cSPEditorHandle {
public:
    uint32_t pad04[(0x5d - 4) / 4];
    uint8_t pad58[5];
    bool mIsHidden;                   // +0x5d
    uint8_t pad5e[6];
    cSPEditorHandleRotationBall();    // 0x00482f90
    void Init(IModelManager* modelMgr, cSPEditorBlock* block, Vector3 offset, bool fullInit);  // 0x00483350
};

// IModelWorld::GetDeformationHandles element (0x5c bytes)
struct MorphHandleInfo {
    uint32_t mAnimID;
    Transform mTransform;
    uint32_t mData[8];
};

class cSPEditorHandleDeform : public cSPEditorHandle {
public:
    uint32_t pad04[(0x180 - 4) / 4];
    float mDefaultWeight;             // +0x180
    uint32_t pad184[(0x1d8 - 0x184) / 4];
    cSPEditorHandleDeform();          // 0x0047fa30
    void Init(IModelManager* modelMgr, cSPEditorBlock* block, MorphHandleInfo* info, bool fullInit);  // 0x00480030
};

// Object at +0x378 (0x4c bytes); its member at +4 is a refcounted interface.
class cSPEditorBlockHelper378 {
public:
    uint32_t mField0;
    IUnknown32* mpObject;
    uint32_t mData[(0x4c - 8) / 4];

    cSPEditorBlockHelper378();  // 0x004e8f70
    ~cSPEditorBlockHelper378()
    {
        if (mpObject)
            mpObject->Release();
    }
    void Shutdown();            // 0x004ae250
};

// ModAPI UnkEditorRigblockStruct1 (+0xdd0)
struct cSPEditorBlockOwnerLink {
    uint32_t mData[0x38 / 4];
    void SetOwner(cSPEditorBlock* block);  // 0x00433a80
};

struct CapabilityLevel {
    bool mIsVariableLevel;
    int mMinLevel;
    int mMaxLevel;
    int mDefaultLevel;
};

struct Capability {
    uint32_t mPropertyID;
    CapabilityLevel mLevel;
    Capability() : mPropertyID(0), mLevel() {}
};

// Static table of the 91 capability properties (0x0150c050).
struct CapabilityPropertyDesc {
    uint32_t mPropertyID;
    uint32_t mUnk4;
    bool mIsVariableLevel;
};
extern const CapabilityPropertyDesc kCapabilityProperties[0x5b];

class RefCountVTemplate {
public:
    virtual int AddRef();
    virtual int Release();
    int mnRefCount;
};

// Boolean attribute indices (bitset at +0xdc8), named after the property that sets them.
enum {
    kAttrOrientToSurfaces = 0x00,
    kAttrOrientWhenSnapped = 0x04,
    kAttrUseDummyBlocks = 0x05,
    kAttrIsVertebra = 0x07,
    kAttrIsPlantRoot = 0x08,
    kAttr09 = 0x09,
    kAttrUseSkin = 0x0a,
    kAttrHasBallAndSocket = 0x0b,
    kAttr0C = 0x0c,
    kAttrHasLeftFile = 0x0d,
    kAttrOnSymmetryPlane = 0x0f,
    kAttrRemainUpright = 0x11,
    kAttrMoveBottomEdgeToSurface = 0x12,
    kAttrPointForward = 0x13,
    kAttrIsNullBlock = 0x14,
    kAttrUseHullForBBox = 0x15,
    kAttrStayAboveGround = 0x16,
    kAttrHasSnapDownTo = 0x17,
    kAttrHideDeformHandles = 0x18,
    kAttrHideRotationHandles = 0x19,
    kAttrHasAlignLateralWith = 0x1a,
    kAttrHasAlignHeightWith = 0x1b,
    kAttrSnapToParentCenter = 0x1c,
    kAttrSnapToParentSnapVectors = 0x1d,
    kAttrSnapToCenterOfEditor = 0x1e,
    kAttrHasBallConnector = 0x1f,
    kAttrHasSocketConnector = 0x20,
    kAttrCellAllowOnTopOfBody = 0x21,
    kAttrPreferToBeOnPlaneOfSymmetry = 0x22,
    kAttrCanBeParentless = 0x23,
    kAttrBoundsCheckOnlyForDelete = 0x24,
    kAttrHasRotationBallHandle = 0x26,
    kAttrHasEffectBone = 0x27,
    kAttrActLikeFinOnPlaneOfSymmetry = 0x28,
    kAttrWarpCursorToPinPoint = 0x29,
    kAttrActsLikeGrasper = 0x2c,
    kAttrActsLikeFoot = 0x2d,
    kAttrUseHullForPicking = 0x2e,
    kAttrForcePinningAgainstType = 0x2f,
    kAttrAllowAsymmetricalRotationOnPlaneOfSymmetry = 0x30,
    kAttrCircularTopAlignment = 0x31,
    kAttrRemainUprightOnTop = 0x32,
    kAttrIsAllowedOutOfBounds = 0x33,
    kAttrDoNotFlipOnPlaneOfSymmetry = 0x34,
    kAttrHasAlignXYWith = 0x35,
    kAttrHasCSnapBone = 0x36,
    kAttrAllowTopBehaviors = 0x37,
    kAttrCellApplyBehaviorToUserRotation = 0x38,
    kAttrStartAsymmetric = 0x3b
};

class cSPEditorBlock : public RefCountVTemplate, public IUnknown32 {
public:
    AutoRefCount<cPropertyList> mpPropList;          // +0x0c
    AutoRefCount<cMWModel> mpModel;                  // +0x10
    AutoRefCount<cMWModel> mpEffectsMaskModel;       // +0x14
    AutoRefCount<IModelWorld> mpModelWorld;          // +0x18
    uint32_t mInstanceID;                            // +0x1c
    uint32_t mGroupID;                               // +0x20
    int mBlockPack;                                  // +0x24
    void* mpEditorModel;                             // +0x28
    bool mIsFullInit;                                // +0x2c
    uint8_t pad2d[3];
    float field_30;                                  // +0x30
    bool mIsVisible;                                 // +0x34
    uint8_t pad35[3];
    uint32_t mUIState[4];                            // +0x38
    Vector3 mPosition;                               // +0x48
    Vector3 mHistoryPosition;                        // +0x54
    Matrix3 mTotalOrientation;                       // +0x60
    Matrix3 mOtherOrientations[5];                   // +0x84
    Vector3 mSurfaceNormal;                          // +0x138
    Vector3 mReplacePartDisplacement;                // +0x144
    int mSnapType;                                   // +0x150
    AutoRefCount<cSPEditorHandle> mAxisHandles[3];   // +0x154
    AutoRefCount<cSPEditorHandleRotationBall> mpRotationBallHandle;  // +0x160
    uint32_t mRotationRingHandleAnimID;              // +0x164
    uint32_t mVertebraAnimID;                        // +0x168
    float mRotationRingHandleCurrentUnscaledRadius;  // +0x16c
    uint32_t mTimer[6];                              // +0x170
    cSPEditorBlock* mpClonedFrom;                    // +0x188
    uint32_t pad18c[6];
    int mTransformedHull;                            // +0x1a4
    bool field_1A8;                                  // +0x1a8
    bool field_1A9;                                  // +0x1a9
    uint8_t pad1aa[2];
    int field_1AC;                                   // +0x1ac
    uint32_t pad1b0[4];
    int mSymmetryType;                               // +0x1c0 (PDB setter: SetBaseJointScale)
    int field_1C4;                                   // +0x1c4
    int field_1C8;                                   // +0x1c8
    int mLimbType;                                   // +0x1cc
    float mMuscleScale;                              // +0x1d0
    float mBaseMuscleScale;                          // +0x1d4
    float mSize;                                     // +0x1d8
    float mSize2;                                    // +0x1dc
    float mModelMinScale;                            // +0x1e0
    float mModelMaxScale;                            // +0x1e4
    Vector3 mModelDefaultMouseOffset;                // +0x1e8
    Matrix3 mModelEditorInitialRotation;             // +0x1f4
    float mModelMinBallConnectorScale;               // +0x218
    float mModelMaxBallConnectorScale;               // +0x21c
    float mModelSymmetrySnapDelta;                   // +0x220
    float field_224;                                 // +0x224
    float mModelReplaceSnapDelta;                    // +0x228
    float mModelSymmetryRotationSnapAngle;           // +0x22c
    bool field_230;                                  // +0x230
    uint8_t pad231[3];
    uint32_t field_234[5];                           // +0x234
    int mModelNumberOfSnapAxes;                      // +0x248
    Transform mEffectsBoneTransform1;                // +0x24c
    Transform mEffectsBoneTransform2;                // +0x284
    int mEffectsBoneIndex;                           // +0x2bc
    Transform mCSnapBoneTransform1;                  // +0x2c0
    Transform mCSnapBoneTransform2;                  // +0x2f8
    int mCSnapBoneIndex;                             // +0x330
    uint32_t pad334[2];
    AutoRefCount<cSPEditorBlock> mpParent;           // +0x33c
    uint32_t mChildren[0x38 / 4];                    // +0x340
    cSPEditorBlockHelper378* mpHelper378;            // +0x378
    uint32_t pad37c[9];
    Vector3 mTriangleDirection;                      // +0x3a0
    Vector3 mTrianglePickOrigin;                     // +0x3ac
    int mPickingType;                                // +0x3b8
    int mModelForcePinningType;                      // +0x3bc
    uint32_t mModelPinningTypeGroup;                 // +0x3c0
    int field_3C4;                                   // +0x3c4
    bool mModelPinningAntiAliased;                   // +0x3c8
    uint8_t pad3c9[3];
    Vector3 field_3CC;                               // +0x3cc
    uint32_t pad3d8[4];
    uint8_t pad3e8[4];
    AutoRefCount<cSPEditorHandleBallConnector> mpBallConnectorHandle;  // +0x3ec
    AutoRefCount<cMWModel> mpSocketConnectorModel;   // +0x3f0
    Vector3 mModelMinSocketConnectorOffset;          // +0x3f4
    Vector3 mModelMaxSocketConnectorOffset;          // +0x400
    Vector3 mSocketConnectorOffset;                  // +0x40c
    Vector3 mModelRotationBallHandleOffset;          // +0x418
    Vector3 mModelPaletteRotation;                   // +0x424
    int mDeformAnimIndex;                            // +0x430
    uint32_t mDeformAnimID;                          // +0x434
    uint32_t pad438[6];
    float mModelBottomEdgeDistanceAdjustment;        // +0x450
    float mModelScale;                               // +0x454
    uint32_t mModelMinMuscleFile;                    // +0x458
    uint32_t mModelMaxMuscleFile;                    // +0x45c
    FixedString32 mModelSoundScale;                  // +0x460
    FixedString32 mModelSoundRotation;               // +0x494
    uint32_t mPaints[(0x5e4 - 0x4c8) / 4];           // +0x4c8
    uint32_t mModelPrice;                            // +0x5e4
    uint32_t mModelComplexityScore;                  // +0x5e8
    uint32_t mModelRunTimeBoneCount;                 // +0x5ec
    uint32_t mModelBakeLevel;                        // +0x5f0
    float field_5F4;                                 // +0x5f4
    ResourceKey mModelRigBlockType;                  // +0x5f8
    uint32_t mModelShowoffAnimation;                 // +0x604
    uint32_t mModelShowoffEffect;                    // +0x608
    uint32_t pad60c[(0x6cc - 0x60c) / 4];
    fixed_vector<AutoRefCount<cSPEditorHandleDeform>, 8> mMorphHandles;  // +0x6cc
    fixed_vector<float, 8> mMorphHandleWeights;      // +0x704
    fixed_vector<uint32_t, 8> mMorphHandleChannels;  // +0x73c
    fixed_vector<ResourceKey, 8> mModelSnapDownTo;   // +0x774
    fixed_vector<ResourceKey, 8> mModelSnapToParentTypes;  // +0x7ec
    fixed_vector<ResourceKey, 8> mModelStayAbove;    // +0x864
    fixed_vector<ResourceKey, 8> mModelAlignLateralWith;   // +0x8dc
    fixed_vector<ResourceKey, 8> mModelAlignHeightWith;    // +0x954
    fixed_vector<ResourceKey, 8> mModelAlignXYWith;  // +0x9cc
    fixed_vector<ResourceKey, 8> mModelTypesToInteractWith;  // +0xa44
    fixed_vector<ResourceKey, 8> mModelTypesToSnapReplace;   // +0xabc
    fixed_vector<ResourceKey, 16> mModelTypesNotToInteractWith;  // +0xb34
    fixed_vector<Capability, 20> mCapabilities;      // +0xc0c
    uint32_t mFootType;                              // +0xdb4
    uint32_t mMouthType;                             // +0xdb8
    uint32_t mWeaponType;                            // +0xdbc
    uint32_t padDC0[2];
    bitset<60> mBooleanAttributes;                   // +0xdc8
    cSPEditorBlockOwnerLink mOwnerLink;              // +0xdd0

    bool GetBooleanAttribute(int index) { return mBooleanAttributes.test(index); }

    bool BuildBlock(uint32_t instanceID, uint32_t groupID, IModelWorld* pWorld,
                    cSPEditorBlock* pParent, float field30, bool bInteractive,
                    bool bCreateModel, bool bModelFlag);

    // out-of-line callees (thiscall)
    void SetBooleanAttribute(int index, bool value);     // 0x00435a10
    void SetBaseJointScale(int value);                   // 0x0044e980 (writes +0x1c0)
    int GetBlockType(uint32_t instanceID);               // 0x0044e830
    bool Sub_44c5a0(int symmetryType);                   // 0x0044c5a0
    void SetScaleType(int limbType);                     // 0x0044f130 (writes +0x1cc)
    float GetDefaultScale();                             // 0x0044b5c0
    void ReleasePhysics();                               // 0x00451fe0
    void RebuildPhysics();                               // 0x00452040
    Vector3 Sub_4364a0();                                // 0x004364a0
    void SetPosition(Vector3 position, bool absolute);   // 0x004380a0
    void Sub_43ac40(int a, int b, int c);                // 0x0043ac40
    BoundingBox GetBBox(int mode, bool a, bool b);       // 0x0044ae00
    void CreateRotationRingHandle(int axis, uint32_t name, uint32_t allowHiddenProp,
                                  uint32_t axisProp, uint32_t rotationProp,
                                  uint32_t offsetProp, uint32_t scaleProp,
                                  uint32_t actLikeBallProp, uint32_t isHiddenProp,
                                  uint32_t unk);         // 0x004410d0
    void Sub_451e20(cSPEditorBlock* parent);             // 0x00451e20
    void SetMorphHandleWeight(int index, float weight, int a, int b, int c);  // 0x0043d690
    void Sub_43e2b0();                                   // 0x0043e2b0
    void InitializeHandleData(cPropertyList* propList);  // 0x00447150
    void Sub_43e0f0(int* animIndex);                     // 0x0043e0f0
    void Sub_448b80(int a);                              // 0x00448b80
    void Sub_449d40(BoundingBox* bbox);                  // 0x00449d40
    void CalculateSnapAxes();                            // 0x0044c690
    void Sub_4484f0();                                   // 0x004484f0
    void Sub_44b640(BoundingBox* bbox);                  // 0x0044b640
    void Sub_44b6b0();                                   // 0x0044b6b0
    void Sub_4485d0();                                   // 0x004485d0
    void Sub_44e7c0(int index);                          // 0x0044e7c0
};
CHECK_OFFSET(cSPEditorBlock, mpPropList, 0xc);
CHECK_OFFSET(cSPEditorBlock, mIsVisible, 0x34);
CHECK_OFFSET(cSPEditorBlock, mPosition, 0x48);
CHECK_OFFSET(cSPEditorBlock, mTotalOrientation, 0x60);
CHECK_OFFSET(cSPEditorBlock, mAxisHandles, 0x154);
CHECK_OFFSET(cSPEditorBlock, mpClonedFrom, 0x188);
CHECK_OFFSET(cSPEditorBlock, mTransformedHull, 0x1a4);
CHECK_OFFSET(cSPEditorBlock, mSymmetryType, 0x1c0);
CHECK_OFFSET(cSPEditorBlock, mModelEditorInitialRotation, 0x1f4);
CHECK_OFFSET(cSPEditorBlock, field_230, 0x230);
CHECK_OFFSET(cSPEditorBlock, mModelNumberOfSnapAxes, 0x248);
CHECK_OFFSET(cSPEditorBlock, mEffectsBoneIndex, 0x2bc);
CHECK_OFFSET(cSPEditorBlock, mCSnapBoneIndex, 0x330);
CHECK_OFFSET(cSPEditorBlock, mpParent, 0x33c);
CHECK_OFFSET(cSPEditorBlock, mpHelper378, 0x378);
CHECK_OFFSET(cSPEditorBlock, mTriangleDirection, 0x3a0);
CHECK_OFFSET(cSPEditorBlock, mPickingType, 0x3b8);
CHECK_OFFSET(cSPEditorBlock, mModelPinningAntiAliased, 0x3c8);
CHECK_OFFSET(cSPEditorBlock, field_3CC, 0x3cc);
CHECK_OFFSET(cSPEditorBlock, mpBallConnectorHandle, 0x3ec);
CHECK_OFFSET(cSPEditorBlock, mDeformAnimIndex, 0x430);
CHECK_OFFSET(cSPEditorBlock, mModelBottomEdgeDistanceAdjustment, 0x450);
CHECK_OFFSET(cSPEditorBlock, mModelSoundRotation, 0x494);
CHECK_OFFSET(cSPEditorBlock, mModelPrice, 0x5e4);
CHECK_OFFSET(cSPEditorBlock, mModelRigBlockType, 0x5f8);
CHECK_OFFSET(cSPEditorBlock, mMorphHandles, 0x6cc);
CHECK_OFFSET(cSPEditorBlock, mModelSnapDownTo, 0x774);
CHECK_OFFSET(cSPEditorBlock, mModelTypesNotToInteractWith, 0xb34);
CHECK_OFFSET(cSPEditorBlock, mCapabilities, 0xc0c);
CHECK_OFFSET(cSPEditorBlock, mFootType, 0xdb4);
CHECK_OFFSET(cSPEditorBlock, mBooleanAttributes, 0xdc8);
CHECK_OFFSET(cSPEditorBlock, mOwnerLink, 0xdd0);
}  // namespace SP

bool Sub_492de0(SP::cSPEditorBlock* block);  // 0x00492de0
float Sub_492e70(SP::cSPEditorBlock* block, Vector3* a, Vector3* b, int* index, float scale,
                 bool flag);                  // 0x00492e70

// ---------------------------------------------------------------- the function
// @ 0x00441440
bool SP::cSPEditorBlock::BuildBlock(uint32_t instanceID, uint32_t groupID, IModelWorld* pWorld,
                                    cSPEditorBlock* pParent, float field30, bool bInteractive,
                                    bool bCreateModel, bool bModelFlag)
{
    bool result = true;
    IModelManager* modelMgr = ModelManager();

    field_30 = field30;
    mIsFullInit = (bInteractive && bCreateModel) ? true : false;
    field_230 = true;
    mInstanceID = instanceID;
    mGroupID = groupID;
    mIsVisible = true;

    if (mpHelper378) {
        mpHelper378->Shutdown();
        delete mpHelper378;
        mpHelper378 = 0;
    }
    if (bCreateModel)
        mpHelper378 = new ("Editor", 0, 0, 0, 0) cSPEditorBlockHelper378();

    if (pWorld) {
        mpModelWorld = pWorld;
    } else {
        if (mpModel) {
            mpModelWorld->SetExternalEffectsTransform(mpModel, 0, 0);
            mpModel->mpWorld->SetInWorld(mpModel, false);
        }
        if (mpEffectsMaskModel)
            mpEffectsMaskModel->mpWorld->SetInWorld(mpEffectsMaskModel, false);
    }

    if (!pParent) {
        if (mpClonedFrom)
            pParent = mpClonedFrom;
        else
            mIsFullInit = false;
    }

    if (mTransformedHull) {
        mpModelWorld->ReleaseTransformedHull(&mTransformedHull);
        mTransformedHull = 0;
    }

    ReleasePhysics();
    if (mpPropList)
        mpPropList = 0;

    if (!bCreateModel) {
        mpPropList = BlockPropertySource()->GetPropertyList(instanceID, groupID);
    } else {
        int flags = bModelFlag ? 0 : 4;
        mpModel = mpModelWorld->CreateModel(instanceID, groupID, flags | 2);
        if (mpModel) {
            mpModelWorld->StallUntilLoaded(mpModel);
            mpPropList = mpModel->mpPropList;
        }
    }

    if (!mpPropList)
        result = false;
    cPropertyList* propList = mpPropList;

    if (propList->HasProperty(0x9069c7c8))  // modelUseSkin
        SetBooleanAttribute(kAttrUseSkin, *GetValueBool(propList->GetPropertyObject(0x9069c7c8)));
    if (propList->HasProperty(0xafff3a14))  // modelIsVertebra
        SetBooleanAttribute(kAttrIsVertebra, *GetValueBool(propList->GetPropertyObject(0xafff3a14)));

    if (mSymmetryType == -2)
        SetBaseJointScale(-2);

    int unused = 0;
    int blockType = GetBlockType(mInstanceID);
    if (blockType == -2)
        blockType = mSymmetryType;
    if (blockType != mSymmetryType && blockType != 0 && mSymmetryType != 0) {
        if (mSymmetryType == 1 && !mpPropList->HasProperty(0x0f48eb09))  // modelLeftFile
            blockType = mSymmetryType;
        else if (mSymmetryType == -1 && !mpPropList->HasProperty(0x18c1dbe0))  // modelRightFile
            blockType = mSymmetryType;
    }
    if (blockType != 0 && mSymmetryType != 0 && blockType != mSymmetryType &&
        Sub_44c5a0(mSymmetryType)) {
        field_1C4 = -1;
        field_1C8 = -1;
    } else {
        field_1C4 = 1;
        field_1C8 = 1;
    }
    SetBooleanAttribute(kAttr09, true);
    if (mSymmetryType == 0 || Abs(mPosition[0]) < 0.001f)
        SetBooleanAttribute(kAttrOnSymmetryPlane, true);

    if (propList->HasProperty(0x8ffc9e66))  // modelSymmetrySnapDelta
        mModelSymmetrySnapDelta = *GetValueFloat(propList->GetPropertyObject(0x8ffc9e66));
    mModelReplaceSnapDelta = 0.4f;
    if (propList->HasProperty(0x049218c6))  // modelReplaceSnapDelta
        mModelReplaceSnapDelta = *GetValueFloat(propList->GetPropertyObject(0x049218c6));
    mModelSymmetryRotationSnapAngle = 0.5f;
    GetFloatProperty(propList, 0x046b02c5, mModelSymmetryRotationSnapAngle);  // modelSymmetryRotationSnapAngle

    if (propList->HasProperty(0x0f48eb09))  // modelLeftFile
        SetBooleanAttribute(kAttrHasLeftFile, true);
    if (!TryGetUIntProperty(propList, 0xe305aafb, (uint32_t&)mBlockPack))  // blockPack
        mBlockPack = 0;

    if (propList->HasProperty(0x105f54ff))  // modelMinMuscleFile
        mModelMinMuscleFile = GetValueKey(propList->GetPropertyObject(0x105f54ff))->instanceID;
    if (propList->HasProperty(0xf061e767))  // modelMaxMuscleFile
        mModelMaxMuscleFile = GetValueKey(propList->GetPropertyObject(0xf061e767))->instanceID;

    const char* soundScale = "creature_size";
    GetPropertyAsChar8Ptr(propList, 0x02784061, soundScale);  // modelSoundScale
    mModelSoundScale = soundScale;
    const char* soundRotation = "creature_rotate";
    GetPropertyAsChar8Ptr(propList, 0x027c3d61, soundRotation);  // modelSoundRotation
    mModelSoundRotation = soundRotation;

    bool modelHasBallConnector = false;
    GetBoolProperty(propList, 0x4ff31eec, modelHasBallConnector);
    SetBooleanAttribute(kAttrHasBallConnector, modelHasBallConnector);
    bool modelHasSocketConnector = false;
    GetBoolProperty(propList, 0x6ff31f12, modelHasSocketConnector);
    SetBooleanAttribute(kAttrHasSocketConnector, modelHasSocketConnector);
    if (modelHasSocketConnector && modelHasBallConnector)
        SetBooleanAttribute(kAttrHasBallAndSocket, true);

    bool modelOrientToSurfaces = false;
    GetBoolProperty(propList, 0x2ff325cd, modelOrientToSurfaces);
    SetBooleanAttribute(kAttrOrientToSurfaces, modelOrientToSurfaces);
    bool modelStayAboveGround = false;
    GetBoolProperty(propList, 0xec611fc7, modelStayAboveGround);
    SetBooleanAttribute(kAttrStayAboveGround, modelStayAboveGround);
    bool modelRemainUpright = false;
    GetBoolProperty(propList, 0x0201636b, modelRemainUpright);
    SetBooleanAttribute(kAttrRemainUpright, modelRemainUpright);
    bool modelMoveBottomEdgeToSurface = false;
    GetBoolProperty(propList, 0x657a035c, modelMoveBottomEdgeToSurface);
    SetBooleanAttribute(kAttrMoveBottomEdgeToSurface, modelMoveBottomEdgeToSurface);
    bool modelPointForward = false;
    GetBoolProperty(propList, 0x31b7b15b, modelPointForward);
    SetBooleanAttribute(kAttrPointForward, modelPointForward);
    bool modelOrientWhenSnapped = false;
    GetBoolProperty(propList, 0xb0032aed, modelOrientWhenSnapped);
    SetBooleanAttribute(kAttrOrientWhenSnapped, modelOrientWhenSnapped);
    bool modelIsNullBlock = false;
    GetBoolProperty(propList, 0x02437197, modelIsNullBlock);
    SetBooleanAttribute(kAttrIsNullBlock, modelIsNullBlock);
    bool modelUseHullForBBox = false;
    GetBoolProperty(propList, 0x51365d07, modelUseHullForBBox);
    SetBooleanAttribute(kAttrUseHullForBBox, modelUseHullForBBox);
    bool modelUseDummyBlocks = false;
    GetBoolProperty(propList, 0x023fa66c, modelUseDummyBlocks);
    SetBooleanAttribute(kAttrUseDummyBlocks, modelUseDummyBlocks);
    bool modelHasRotationBallHandle = false;
    GetBoolProperty(propList, 0xb07b21bd, modelHasRotationBallHandle);
    SetBooleanAttribute(kAttrHasRotationBallHandle, modelHasRotationBallHandle);
    bool modelIsPlantRoot = false;
    GetBoolProperty(propList, 0x0d8800eb, modelIsPlantRoot);
    SetBooleanAttribute(kAttrIsPlantRoot, modelIsPlantRoot);
    bool modelHideDeformHandles = false;
    GetBoolProperty(propList, 0x9416cea1, modelHideDeformHandles);
    SetBooleanAttribute(kAttrHideDeformHandles, modelHideDeformHandles);
    bool modelHideRotationHandles = false;
    GetBoolProperty(propList, 0x0493691f, modelHideRotationHandles);
    SetBooleanAttribute(kAttrHideRotationHandles, modelHideRotationHandles);
    bool modelCellApplyBehaviorToUserRotation = false;
    GetBoolProperty(propList, 0x0655296a, modelCellApplyBehaviorToUserRotation);
    SetBooleanAttribute(kAttrCellApplyBehaviorToUserRotation, modelCellApplyBehaviorToUserRotation);

    // modelPinningType: instance = pinning mode, group = pinning type group.
    ResourceKey pinningType;
    pinningType.instanceID = 0;
    pinningType.typeID = 0;
    pinningType.groupID = 0;
    if (propList->HasProperty(0x2e853adb)) {  // modelPinningType
        GetPropertyAsKey(propList, 0x2e853adb, pinningType);
    } else {
        pinningType.groupID = 0xb6f87eb0;     // PinningGeometry
        pinningType.instanceID = 0x5ef161f1;  // PinningNormal
    }
    if (pinningType.groupID == 0x9183dc9b &&  // PinningPhysics
        !propList->HasProperty(0x00f9efc0))   // modelMeshHull
        pinningType.groupID = 0xb6f87eb0;     // PinningGeometry
    mModelPinningTypeGroup = pinningType.groupID;
    mModelPinningAntiAliased = pinningType.instanceID == 0x17cfd48f;  // PinningAntiAliased

    uint32_t pinningAgainstType = 0;
    if (propList->HasProperty(0x04e2bf28)) {  // modelForcePinningAgainstType
        GetPropertyAsKeyInstance(propList, 0x04e2bf28, pinningAgainstType);
        if (pinningAgainstType != 0x2ca33bdb) {  // None
            SetBooleanAttribute(kAttrForcePinningAgainstType, true);
            switch (pinningAgainstType) {
            case 0x9183dc9b:  // PinningPhysics
                mModelForcePinningType = 2;
                break;
            case 0xb6f87eb0:  // PinningGeometry
                mModelForcePinningType = 4;
                break;
            default:
                SetBooleanAttribute(kAttrForcePinningAgainstType, false);
                break;
            }
        }
    }

    mModelScale = 1.0f;
    GetFloatProperty(propList, 0x00fba611, mModelScale);  // modelScale
    mModelShowoffAnimation = 0;
    GetPropertyAsKeyInstance(propList, 0x4f2f2a48, mModelShowoffAnimation);  // modelShowoffAnimation
    mModelShowoffEffect = 0;
    GetPropertyAsKeyInstance(propList, 0x06514c0b, mModelShowoffEffect);  // modelShowoffEffect
    mOwnerLink.SetOwner(this);

    mModelRigBlockType.instanceID = 0;
    mModelRigBlockType.groupID = 0;
    mModelRigBlockType.typeID = 0;
    if (propList->HasProperty(0x0186609d)) {  // modelRigBlockType
        GetPropertyAsKey(propList, 0x0186609d, mModelRigBlockType);
        if (mModelRigBlockType.groupID == 0xffffffff || mModelRigBlockType.groupID == 0x2ca33bdb)
            mModelRigBlockType.groupID = 0;
        if (mModelRigBlockType.instanceID == 0xffffffff || mModelRigBlockType.instanceID == 0x2ca33bdb)
            mModelRigBlockType.instanceID = 0;
        if (mModelRigBlockType.typeID == 0xffffffff || mModelRigBlockType.typeID == 0x2ca33bdb)
            mModelRigBlockType.typeID = 0;
    }

    bool modelSnapToParentCenter = false;
    GetBoolProperty(propList, 0x0213a120, modelSnapToParentCenter);
    SetBooleanAttribute(kAttrSnapToParentCenter, modelSnapToParentCenter);
    bool modelSnapToParentSnapVectors = false;
    GetBoolProperty(propList, 0xf87abea3, modelSnapToParentSnapVectors);
    SetBooleanAttribute(kAttrSnapToParentSnapVectors, modelSnapToParentSnapVectors);
    bool modelSnapToCenterOfEditor = false;
    GetBoolProperty(propList, 0xdafbe434, modelSnapToCenterOfEditor);
    SetBooleanAttribute(kAttrSnapToCenterOfEditor, modelSnapToCenterOfEditor);
    bool modelCellAllowOnTopOfBody = false;
    GetBoolProperty(propList, 0xd11cbf2e, modelCellAllowOnTopOfBody);
    SetBooleanAttribute(kAttrCellAllowOnTopOfBody, modelCellAllowOnTopOfBody);
    bool modelPreferToBeOnPlaneOfSymmetry = false;
    GetBoolProperty(propList, 0x5c5e51ec, modelPreferToBeOnPlaneOfSymmetry);
    SetBooleanAttribute(kAttrPreferToBeOnPlaneOfSymmetry, modelPreferToBeOnPlaneOfSymmetry);
    bool modelActLikeFinOnPlaneOfSymmetry = false;
    GetBoolProperty(propList, 0xfb23b7d1, modelActLikeFinOnPlaneOfSymmetry);
    SetBooleanAttribute(kAttrActLikeFinOnPlaneOfSymmetry, modelActLikeFinOnPlaneOfSymmetry);
    bool modelStartAsymmetric = false;
    GetBoolProperty(propList, 0x0750dcd1, modelStartAsymmetric);
    SetBooleanAttribute(kAttrStartAsymmetric, modelStartAsymmetric);
    bool modelCanBeParentless = false;
    GetBoolProperty(propList, 0x8e31d974, modelCanBeParentless);
    SetBooleanAttribute(kAttrCanBeParentless, modelCanBeParentless);
    bool modelWarpCursorToPinPoint = false;
    GetBoolProperty(propList, 0x0489164a, modelWarpCursorToPinPoint);
    SetBooleanAttribute(kAttrWarpCursorToPinPoint, modelWarpCursorToPinPoint);
    bool modelActsLikeFoot = false;
    GetBoolProperty(propList, 0x04a33896, modelActsLikeFoot);
    SetBooleanAttribute(kAttrActsLikeFoot, modelActsLikeFoot);
    bool modelAllowAsymmetricalRotationOnPlaneOfSymmetry = false;
    GetBoolProperty(propList, 0x04eb8e7a, modelAllowAsymmetricalRotationOnPlaneOfSymmetry);
    SetBooleanAttribute(kAttrAllowAsymmetricalRotationOnPlaneOfSymmetry,
                        modelAllowAsymmetricalRotationOnPlaneOfSymmetry);
    bool modelDoNotFlipBasedOnSurfaceNormalOnPlaneOfSymmetry = false;
    GetBoolProperty(propList, 0x05c08c60, modelDoNotFlipBasedOnSurfaceNormalOnPlaneOfSymmetry);
    SetBooleanAttribute(kAttrDoNotFlipOnPlaneOfSymmetry,
                        modelDoNotFlipBasedOnSurfaceNormalOnPlaneOfSymmetry);

    mModelNumberOfSnapAxes = -1;
    TryGetUIntProperty(propList, 0x04ece315, (uint32_t&)mModelNumberOfSnapAxes);  // modelNumberOfSnapAxes

    bool modelRemainUprightOnTop = false;
    GetBoolProperty(propList, 0x04ed8506, modelRemainUprightOnTop);
    SetBooleanAttribute(kAttrRemainUprightOnTop, modelRemainUprightOnTop);
    bool modelAllowTopBehaviors = false;
    GetBoolProperty(propList, 0x05f98a72, modelAllowTopBehaviors);
    SetBooleanAttribute(kAttrAllowTopBehaviors, modelAllowTopBehaviors);
    bool modelIsAllowedOutOfBounds = false;
    GetBoolProperty(propList, 0x0538a895, modelIsAllowedOutOfBounds);
    SetBooleanAttribute(kAttrIsAllowedOutOfBounds, modelIsAllowedOutOfBounds);
    bool modelCircularTopAlignment = false;
    GetBoolProperty(propList, 0x04ed4c40, modelCircularTopAlignment);
    SetBooleanAttribute(kAttrCircularTopAlignment, modelCircularTopAlignment);
    bool modelActsLikeGrasper = false;
    GetBoolProperty(propList, 0x04a3386d, modelActsLikeGrasper);
    SetBooleanAttribute(kAttrActsLikeGrasper, modelActsLikeGrasper);

    mModelDefaultMouseOffset = kVector3Zero;
    GetPropertyAsVector3(propList, 0x0520f199, mModelDefaultMouseOffset);  // modelDefaultMouseOffset
    mModelEditorInitialRotation = kMatrix3Identity;
    if (propList->HasProperty(0x05aee941)) {  // modelEditorInitialRotation
        Vector3 initialRotation;
        GetPropertyAsVector3(propList, 0x05aee941, initialRotation);
        float degToRad = 0.017453292f;
        initialRotation = initialRotation * degToRad;
        Matrix3 rotation(Matrix33FromEulerXYZ(initialRotation));
        mModelEditorInitialRotation = rotation;
    }

    mModelBottomEdgeDistanceAdjustment = 0.0f;
    if (propList->HasProperty(0x165f0e1e))  // modelBottomEdgeDistanceAdjustment
        GetFloatProperty(propList, 0x165f0e1e, mModelBottomEdgeDistanceAdjustment);

    bool modelBoundsCheckOnlyForDelete = false;
    GetBoolProperty(propList, 0x3701d675, modelBoundsCheckOnlyForDelete);
    SetBooleanAttribute(kAttrBoundsCheckOnlyForDelete, modelBoundsCheckOnlyForDelete);

    mModelMinScale = 0.2f;
    GetFloatProperty(propList, 0xf023ed73, mModelMinScale);  // modelMinScale
    mModelMaxScale = 3.0f;
    GetFloatProperty(propList, 0xf023ed79, mModelMaxScale);  // modelMaxScale
    float defaultScale = GetDefaultScale();
    mModelMinBallConnectorScale = 0.5f;
    GetFloatProperty(propList, 0xfe0926f6, mModelMinBallConnectorScale);  // modelMinBallConnectorScale
    mModelMaxBallConnectorScale = 2.0f;
    GetFloatProperty(propList, 0x21d55d8c, mModelMaxBallConnectorScale);  // modelMaxBallConnectorScale

    if (propList->HasProperty(0x0224fea2)) {  // modelPaletteRotation
        Vector3 paletteRotation = *GetValueVector3(propList->GetPropertyObject(0x0224fea2));
        mModelPaletteRotation = paletteRotation;
    }

    uint32_t modelPrice = 0;
    TryGetUIntProperty(propList, 0x02166464, modelPrice);  // modelPrice
    mModelPrice = modelPrice;
    mModelComplexityScore = 0;
    mModelRunTimeBoneCount = 0;
    mModelBakeLevel = 0;
    TryGetUIntProperty(propList, 0x3c652302, mModelComplexityScore);   // modelComplexityScore
    TryGetUIntProperty(propList, 0x51fa9dfa, mModelRunTimeBoneCount);  // modelRunTimeBoneCount
    TryGetUIntProperty(propList, 0x04460b63, mModelBakeLevel);         // modelBakeLevel
    field_5F4 = BlockPropertySource()->GetPropertyListFloat(propList);

    GetPropertyAsKeyInstance(propList, 0xdd94fb65, mFootType);    // foottype
    GetPropertyAsKeyInstance(propList, 0x0e40c402, mMouthType);   // mouthtype
    GetPropertyAsKeyInstance(propList, 0x2dc2a89d, mWeaponType);  // weapontype

    // ResourceKey lists
    mModelSnapDownTo.clear();
    {
        Property* prop = propList->GetPropertyObject(0x86e4091f);  // modelSnapDownTo
        int count = prop->GetItemCount();
        if (count > 0)
            SetBooleanAttribute(kAttrHasSnapDownTo, true);
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelSnapDownTo, count, keys);
    }
    mModelSnapToParentTypes.clear();
    if (propList->HasProperty(0xe3803d2a)) {  // modelSnapToParentTypes
        Property* prop = propList->GetPropertyObject(0xe3803d2a);
        int count = prop->GetItemCount();
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelSnapToParentTypes, count, keys);
    }
    mModelTypesToInteractWith.clear();
    if (propList->HasProperty(0x6ffded92)) {  // modelTypesToInteractWith
        Property* prop = propList->GetPropertyObject(0x6ffded92);
        int count = prop->GetItemCount();
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelTypesToInteractWith, count, keys);
    }
    mModelTypesNotToInteractWith.clear();
    if (propList->HasProperty(0x044dcd0a)) {  // modelTypesNotToInteractWith
        Property* prop = propList->GetPropertyObject(0x044dcd0a);
        int count = prop->GetItemCount();
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelTypesNotToInteractWith, count, keys);
    }
    mModelTypesToSnapReplace.clear();
    if (propList->HasProperty(0x048e2a2e)) {  // modelTypesToSnapReplace
        Property* prop = propList->GetPropertyObject(0x048e2a2e);
        int count = prop->GetItemCount();
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelTypesToSnapReplace, count, keys);
    }
    mModelAlignHeightWith.clear();
    if (propList->HasProperty(0xa3db17be)) {  // modelAlignHeightWith
        Property* prop = propList->GetPropertyObject(0xa3db17be);
        int count = prop->GetItemCount();
        if (count > 0)
            SetBooleanAttribute(kAttrHasAlignHeightWith, true);
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelAlignHeightWith, count, keys);
    }
    mModelAlignXYWith.clear();
    if (propList->HasProperty(0x05f57a28)) {  // modelAlignXYWith
        Property* prop = propList->GetPropertyObject(0x05f57a28);
        int count = prop->GetItemCount();
        if (count > 0)
            SetBooleanAttribute(kAttrHasAlignXYWith, true);
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelAlignXYWith, count, keys);
    }
    mModelAlignLateralWith.clear();
    if (propList->HasProperty(0x467ef4e0)) {  // modelAlignLateralWith
        Property* prop = propList->GetPropertyObject(0x467ef4e0);
        int count = prop->GetItemCount();
        if (count > 0)
            SetBooleanAttribute(kAttrHasAlignLateralWith, true);
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelAlignLateralWith, count, keys);
    }
    mModelStayAbove.clear();
    if (propList->HasProperty(0xee0fa2ce)) {  // modelStayAbove
        Property* prop = propList->GetPropertyObject(0xee0fa2ce);
        int count = prop->GetItemCount();
        if (count > 0)
            SetBooleanAttribute(kAttrStayAboveGround, true);
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelStayAbove, count, keys);
    }

    // Capabilities
    mCapabilities.clear();
    for (unsigned int i = 0; i < 0x5b; i++) {
        const CapabilityPropertyDesc* desc = &kCapabilityProperties[i];
        if (!propList->HasProperty(kCapabilityProperties[i].mPropertyID))
            continue;
        if (!desc->mIsVariableLevel) {
            Capability capability;
            capability.mPropertyID = kCapabilityProperties[i].mPropertyID;
            int level;  // left uninitialised when the property is missing or not an int
            GetIntProperty(propList, desc->mPropertyID, level);
            CapabilityLevel fixedLevel;
            fixedLevel.mIsVariableLevel = false;
            fixedLevel.mMinLevel = level;
            fixedLevel.mMaxLevel = level;
            fixedLevel.mDefaultLevel = -1;
            capability.mLevel = fixedLevel;
            mCapabilities.push_back(capability);
        } else {
            Capability capability;
            capability.mPropertyID = kCapabilityProperties[i].mPropertyID;
            Vector3 range;
            GetPropertyAsVector3(propList, desc->mPropertyID, range);
            CapabilityLevel variableLevel;
            variableLevel.mIsVariableLevel = true;
            variableLevel.mDefaultLevel = (int)range.x;
            variableLevel.mMinLevel = (int)range.y;
            variableLevel.mMaxLevel = (int)range.z;
            capability.mLevel = variableLevel;
            mCapabilities.push_back(capability);
        }
    }

    Vector3 rotationBallOffset(0.0f, -0.5f, 0.0f);
    if (propList->HasProperty(0xb07b21be)) {  // modelRotationBallHandleOffset
        Vector3 offset = *GetValueVector3(propList->GetPropertyObject(0xb07b21be));
        rotationBallOffset = offset;
    }
    mModelRotationBallHandleOffset = rotationBallOffset;

    Vector3 minSocketOffset(0.0f, 0.0f, 0.0f);
    Vector3 maxSocketOffset(0.0f, 0.0f, 0.0f);
    mBooleanAttributes.test(kAttrHasSocketConnector);  // result unused
    if (propList->HasProperty(0x3061e2b3)) {  // modelMinSocketConnectorOffset
        Vector3 offset = *GetValueVector3(propList->GetPropertyObject(0x3061e2b3));
        minSocketOffset = offset;
    }
    if (propList->HasProperty(0x3061e2b8)) {  // modelMaxSocketConnectorOffset
        Vector3 offset = *GetValueVector3(propList->GetPropertyObject(0x3061e2b8));
        maxSocketOffset = offset;
    } else {
        maxSocketOffset = minSocketOffset;
    }
    mModelMinSocketConnectorOffset = minSocketOffset;
    mModelMaxSocketConnectorOffset = maxSocketOffset;

    if (mLimbType == 3)
        SetScaleType(0);

    // Ball connector
    if (GetBooleanAttribute(kAttrHasBallConnector)) {
        if (mpBallConnectorHandle) {
            mpBallConnectorHandle->Dispose();
            mpBallConnectorHandle = 0;
        }
        if (bInteractive) {
            mpBallConnectorHandle = new ("Editor", 0, 0, 0, 0) cSPEditorHandleBallConnector();
            mpBallConnectorHandle->Init(this);
        }
        if (mpBallConnectorHandle)
            mpBallConnectorHandle->SetScale(mBaseMuscleScale);
    } else {
        mBooleanAttributes.set(kAttr0C, false);
    }

    // Socket connector
    if (GetBooleanAttribute(kAttrHasSocketConnector)) {
        if (mpSocketConnectorModel) {
            mpSocketConnectorModel->mpWorld->SetInWorld(mpSocketConnectorModel, false);
            mpSocketConnectorModel = 0;
        }
        mSocketConnectorOffset = mModelMinSocketConnectorOffset * mModelScale;
        mModelMinSocketConnectorOffset = mModelMinSocketConnectorOffset * mModelScale;
        mModelMaxSocketConnectorOffset = mModelMaxSocketConnectorOffset * mModelScale;
        if (bInteractive)
            mpSocketConnectorModel = mpModelWorld->CreateModel(0xcd09fa6a, kEditorModelGroupID, 0);  // ce_basic_socket
        if (mpSocketConnectorModel) {
            mpSocketConnectorModel->mpOwner = static_cast<IUnknown32*>(this);
            mpSocketConnectorModel->mGroupFlags.set(modelMgr->GetGroupFlag(0x4ff4af74, 0), true);
            mpSocketConnectorModel->SetVisible(false);
        }
    }

    if (GetBooleanAttribute(kAttrStayAboveGround) && mModelStayAbove.empty()) {
        mModelStayAbove.resize(1);
        mModelStayAbove[0].instanceID = 0x96b84350;  // ground
    }
    if (GetBooleanAttribute(kAttrUseDummyBlocks) && mpSocketConnectorModel)
        mpSocketConnectorModel->SetVisible(false);
    if (GetBooleanAttribute(kAttrHasBallAndSocket) && GetBooleanAttribute(kAttrUseSkin) && mpModel)
        mpModel->SetVisible(false);

    if (bInteractive && mpParent && !GetBooleanAttribute(kAttrIsVertebra) &&
        !GetBooleanAttribute(kAttrHasBallConnector)) {
        if (0.5f > VectorLength(mTriangleDirection))
            mTriangleDirection = Sub_4364a0();
    } else {
        mTriangleDirection = mTotalOrientation.m[1];
    }

    SetPosition(mPosition, false);
    field_3CC = mTotalOrientation.m[1];
    mEffectsBoneIndex = -1;
    mCSnapBoneIndex = -1;

    if (mpModel) {
        mpModel->mpOwner = static_cast<IUnknown32*>(this);
        mpModel->mTransform.SetOffset(mPosition);
        mpModel->mTransform.SetRotation(mTotalOrientation);
        mpModel->mGroupFlags.set(modelMgr->GetGroupFlag(0x9138fd8d, 0), true);
        mpModel->mFlags.set(1, false);

        bool modelOverrideBounds = false;
        GetBoolProperty(mpPropList, 0xd2435f2d, modelOverrideBounds);
        mpModel->mFlags.set(9, modelOverrideBounds);

        bool modelUseHullForPicking = false;
        GetBoolProperty(mpPropList, 0x350f8605, modelUseHullForPicking);
        if (modelUseHullForPicking) {
            SetBooleanAttribute(kAttrUseHullForPicking, true);
            mpModel->mFlags.set(8, true);
            mpModel->mCollisionMode = 2;
            mPickingType = 2;
        } else {
            mPickingType = 4;
        }

        if (GetBooleanAttribute(kAttrIsVertebra)) {
            mpModelWorld->StallUntilLoaded(mpModel);
            if (mpModelWorld && mpModelWorld->GetNumAnimations(mpModel, 0) == 1) {
                mpModelWorld->GetAnimationIDs(mpModel, &mVertebraAnimID, 0);
                if (mVertebraAnimID)
                    mpModelWorld->AnimAction(mpModel, mVertebraAnimID, 3, 0.0f, 0);
            }
            mpModel->mGroupFlags.set(modelMgr->GetGroupFlag(0x022fff11, 0), true);
            mpModel->mGroupFlags.set(modelMgr->GetGroupFlag(0x513cdfc1, 0), true);
            mpModel->mFlags.set(1, true);
            mpModel->mColor[3] = 0.0f;
        } else if (GetBooleanAttribute(kAttrHasBallAndSocket) && GetBooleanAttribute(kAttrUseSkin)) {
            mpModel->mFlags.set(1, true);
            mpModel->mColor[3] = 0.0f;
        }
        Sub_43ac40(0, 1, 1);
    }

    if (!mpPropList->HasProperty(0x8ffc9e66)) {  // modelSymmetrySnapDelta
        BoundingBox bbox = GetBBox(2, false, false);
        float delta = Clamp((bbox.mMax[0] - bbox.mMin[0]) * 0.3f, 0.01f, 0.13f);
        mModelSymmetrySnapDelta = delta;
    }
    BoundingBox bbox = GetBBox(2, false, false);
    float replaceDelta = Clamp((bbox.mMax[0] - bbox.mMin[0]) * mModelReplaceSnapDelta, 0.01f, 0.3f);
    field_224 = replaceDelta;

    // Rotation handles
    for (int i = 0; i < 3; i++) {
        if (mAxisHandles[i]) {
            mAxisHandles[i]->Dispose();
            mAxisHandles[i] = 0;
        }
    }
    bool createRotationHandles =
        (!GetBooleanAttribute(kAttrHideRotationHandles) && bInteractive) ? true : false;
    if (createRotationHandles) {
        CreateRotationRingHandle(0, 0x067489dc,  // xaxis
                                 0x04617bf6, 0x98d0ea44, 0x98d0ea45, 0x040cbd94, 0x041295c9,
                                 0x0420dc18, 0x04604b00, 0x04617d3d);
        CreateRotationRingHandle(1, 0x3bc16bcd,  // yaxis
                                 0x04617bf7, 0x98d0ea46, 0x98d0ea47, 0x040cbd95, 0x041295ca,
                                 0x0420dc19, 0x04604b01, 0x04617d3e);
        CreateRotationRingHandle(2, 0x01d369ee,  // zaxis
                                 0x04617bf8, 0x98d0ea48, 0x98d0ea49, 0x040cbd96, 0x041295cb,
                                 0x0420dc1a, 0x04604b02, 0x04617d3f);
    }
    if (createRotationHandles && GetBooleanAttribute(kAttrHasRotationBallHandle)) {
        if (mpRotationBallHandle) {
            mpRotationBallHandle->Dispose();
            mpRotationBallHandle = 0;
        }
        mpRotationBallHandle = new ("Editor", 0, 0, 0, 0) cSPEditorHandleRotationBall();
        mpRotationBallHandle->Init(modelMgr, this, mModelRotationBallHandleOffset, bInteractive);
        bool modelRotationBallHandleIsHidden = false;
        GetBoolProperty(mpPropList, 0x04604b03, modelRotationBallHandleIsHidden);
        mpRotationBallHandle->mIsHidden = modelRotationBallHandleIsHidden;
    }

    if (pParent)
        Sub_451e20(pParent);

    // Deform handles
    bool showDeformHandles = !GetBooleanAttribute(kAttrHideDeformHandles);
    MorphHandleInfo morphHandles[0x20];
    int numWeights = mMorphHandleWeights.size();
    int numMorphHandles = 0;
    if (mpModel)
        numMorphHandles = mpModelWorld->GetDeformationHandles(mpModel, morphHandles, 0x20);

    if (numWeights >= 1 && GetBooleanAttribute(kAttrHasBallAndSocket)) {
        int boneLengthIndex = 0;
        int numChannels = mMorphHandleChannels.size();
        for (int i = 0; i < numChannels; i++) {
            if (mMorphHandleChannels[i] == 0x9310d4c0) {  // DeformBoneLength
                boneLengthIndex = i;
                break;
            }
        }
        float& weight = mMorphHandleWeights[boneLengthIndex];
        mSocketConnectorOffset = mModelMinSocketConnectorOffset +
            weight * (mModelMaxSocketConnectorOffset - mModelMinSocketConnectorOffset);
    }

    int i = 0;
    int numHandles = mMorphHandles.size();
    for (; i < numHandles; i++) {
        if (mMorphHandles[i])
            mMorphHandles[i]->Dispose();
    }
    mMorphHandles.clear();
    mMorphHandles.resize(numMorphHandles);
    for (int h = 0; h < numMorphHandles; h++) {
        mMorphHandles[h] = new ("Editor", 0, 0, 0, 0) cSPEditorHandleDeform();
        cSPEditorHandleDeform* handle = mMorphHandles[h];
        handle->Init(modelMgr, this, &morphHandles[h], bInteractive);
        cSPEditorHandleDeform* created = mMorphHandles[h];
        SetMorphHandleWeight(h, created->mDefaultWeight, 0, 0, 1);
    }
    if (mMorphHandleWeights.empty())
        Sub_43e2b0();

    if (numMorphHandles > 0) {
        InitializeHandleData(propList);
        if (mpModelWorld && mpModel) {
            Sub_43e0f0(&mDeformAnimIndex);
            if (mDeformAnimIndex != -1) {
                uint32_t animIDs[0x20];
                mpModelWorld->GetAnimationIDs(mpModel, animIDs, 0);
                mDeformAnimID = animIDs[mDeformAnimIndex];
            }
        }
    }

    if (bInteractive) {
        Sub_448b80(0);
        BoundingBox modelBBox;
        Sub_449d40(&modelBBox);
        if (mpModel && mpModelWorld && mModelNumberOfSnapAxes > 0) {
            mpPropList->HasProperty(0x00f9efc0);  // modelMeshHull (result unused)
            RebuildPhysics();
            CalculateSnapAxes();
        }
        Sub_4484f0();
    }

    for (int w = 0; w < numMorphHandles; w++) {
        if (w < numWeights)
            SetMorphHandleWeight(w, mMorphHandleWeights[w], 0, 0, 1);
    }

    if (bInteractive && mpModel && mpModelWorld) {
        BoundingBox modelBBox2;
        Sub_449d40(&modelBBox2);
        RebuildPhysics();
        Sub_44b640(&mpModel->mDefaultBBox);
        Sub_44b6b0();
        Sub_4485d0();
    }

    field_1A9 = true;
    field_1AC = 0;

    int snapIndex = -2;
    if (bInteractive) {
        Vector3 snapA;
        Vector3 snapB;
        bool flag = Sub_492de0(this);
        float score = Sub_492e70(this, &snapA, &snapB, &snapIndex, 1.0f, flag);
        if (score > -1.0f)
            Sub_44e7c0(snapIndex);
    }

    // "effect" and "csnap" bones
    if (mpModel) {
        int numBones = mpModelWorld->GetNumBones(mpModel);
        fixed_vector<uint32_t, 64> boneIDs(numBones);
        fixed_vector<BoneTransform, 64> boneTransforms(numBones);
        const uint32_t kEffectBone = 0x80d91e9e;  // effect
        const uint32_t kCSnapBone = 0x2002c980;   // csnap
        mpModelWorld->GetBoneIDs(mpModel, boneIDs.mpBegin);
        for (int bone = 0; bone < numBones; bone++) {
            if (boneIDs[bone] == 0x80d91e9e || boneIDs[bone] == 0x2002c980) {
                Transform worldTransform;
                Transform poseTransform;
                fixed_vector<BoneTransform, 64> transforms(numBones);
                mpModelWorld->GetBoneTransforms(mpModel, transforms.mpBegin);
                BoneTransformToTransform(&transforms[bone], &worldTransform);
                mpModelWorld->GetPoseTransforms(mpModel, transforms.mpBegin, false);
                BoneTransformToTransform(&transforms[bone], &poseTransform);
                worldTransform.Accumulate(poseTransform);
                worldTransform.AccumulateScaled(*mpModelWorld->GetMeshTransform(mpModel));
                worldTransform.mScale = 1.0f;
                worldTransform.mChangeCount++;
                if (boneIDs[bone] == 0x80d91e9e) {
                    SetBooleanAttribute(kAttrHasEffectBone, true);
                    mEffectsBoneTransform1 = poseTransform;
                    mEffectsBoneTransform2 = worldTransform;
                    mEffectsBoneIndex = bone;
                } else if (boneIDs[bone] == 0x2002c980) {
                    SetBooleanAttribute(kAttrHasCSnapBone, true);
                    mCSnapBoneTransform1 = poseTransform;
                    mCSnapBoneTransform2 = worldTransform;
                    mCSnapBoneIndex = bone;
                }
            }
        }
    }

    return result;
}
// --- equivalence checker address annotations
    void operator delete(void*); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct SP {
    void erase(void*, void*); // 0x00530c80
};
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct UResourceKey {
    void erase();   // 0x0050f740 (equiv t2)
    void resize();   // 0x004548d0 (equiv t3)
};
struct VcSPEditorHandleDeform {
    void resize();   // 0x00421bf0 (equiv t2)
};
}
