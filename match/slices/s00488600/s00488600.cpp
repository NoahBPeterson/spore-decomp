// Slice s00488600: SP::cSPEditorLimbJoint / SP::cSPEditorLimbStructure (limb skeleton built over editor blocks).
// Module flags: /Od /Ob1 /arch:SSE /fp:fast.
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---- rw::math / cSP math types ----
struct Vector3T {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T {                              // rw::math::fpu::Matrix33Template<float,0>
    Vector3T xAxis, yAxis, zAxis;
};
struct cSPMatrix3 : Matrix33T {
    static const cSPMatrix3 IDENTITY;           // @ 0x15d5908
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPBoundingBox {
    cSPVector3 mMin, mMax;
    bool IsEmpty() const { return mMin[0] > mMax[0]; }
};

Vector3T operator*(const Vector3T& v, const Matrix33T& m);   // @ 0x41daf0
Vector3T operator-(const Vector3T& v);                       // @ 0x422020
Vector3T operator+(const Vector3T& a, const Vector3T& b);    // @ 0x41dc10
Vector3T& operator+=(Vector3T& a, const Vector3T& b);        // @ 0x41ddb0
float VectorLength(const Vector3T& v);                       // @ 0x40ae50
inline float Length(const Vector3T& v) { return VectorLength(v); }

inline const float& Max(const float& a, const float& b) { return (a > b) ? a : b; }
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float Abs(float x) { float r = (float)fabs(x); return r; }

struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    cSPVector3 mTranslation;
    float mScale;
    cSPMatrix3 mRotation;
    cSPTransform();                                          // @ 0x409930
    const cSPMatrix3& GetRotation() const { return mRotation; }
    void SetRotation(const cSPMatrix3& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
    void PreRotate(const Vector3T& axis, float angle);       // @ 0x6baba0
};

// ---- EASTL-style containers ----
template<class T> struct AutoRefCount {
    T* mpObject;
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// Layout helper: the AutoRefCount vector's inline constructor reserves one unused /Od slot.
template<class T> struct CtorSlots { static void Reserve() {} static void ReserveClear() {} };
template<class T> struct AutoRefCount;
template<class T> struct CtorSlots<AutoRefCount<T> > { static void Reserve() { ScratchSlots<1>(); } static void ReserveClear() { ScratchSlots<3>(); } };

template<class T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) { CtorSlots<T>::Reserve(); }
    ~VectorBase();                                           // @ 0x425990 (shared)
};
template<class T> struct vector : VectorBase<T> {
    vector() {}
    ~vector() { DoDestroyValues(mpBegin, mpEnd); ScratchSlots<3>(); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    T* erase(T* first, T* last);                             // @ 0x4769b0 / 0x454280
    void clear() { erase(mpBegin, mpEnd); ScratchSlots<4>(); CtorSlots<T>::ReserveClear(); }
    bool empty() const;                                      // @ 0x526430
    void DoDestroyValues(T* first, T* last) { for (; first < last; ++first) first->~T(); }
};

template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

namespace SP {

struct cSPEditorBlock {
    virtual void _v0();
    virtual int Release();
    char pad0[0x48 - 4];
    cSPVector3 mPosition;                       // +0x48
    char pad1[0x33c - 0x54];
    AutoRefCount<cSPEditorBlock> mParentBlock;  // +0x33c
    char pad2[0xdc8 - 0x340];
    bitset<60> mFlags;                          // +0xdc8

    const cSPVector3& GetPosition() const { return mPosition; }
    cSPEditorBlock* GetParent() const { return mParentBlock; }
    bool IsLimbPart();                                       // @ 0x435c80
    int CalculateSymmetrySign();                             // @ 0x44f240
    void SetSymmetrySign(int sign);                          // @ 0x44e980
    int GetSymmetryCount();                                  // @ 0x44f220
};

cSPEditorBlock* GetLimbRoot(cSPEditorBlock* block);                                       // @ 0x4a5e10
Vector3T Normalize(const Vector3T& v);                                                    // @ 0x436ce0
cSPVector3 Cross(const Vector3T& a, const Vector3T& b);                                   // @ 0x44e460
cSPMatrix3 MatrixFromAxes(const Vector3T& forward, const Vector3T& side);                 // @ 0x4a89e0
cSPVector3 Mirror(const Vector3T& v);                                                     // @ 0x4a8f40
Vector3T operator-(const Vector3T& a, const Vector3T& b);                                 // @ 0x41db10

struct cMatrix3Init : cSPMatrix3 {
    cMatrix3Init(float, float, float, float, float, float, float, float, float);         // @ 0x432c50
    cMatrix3Init(const cMatrix3Init&);
};

struct cSPEditorLimbStructure;
void BuildPileList(cSPEditorBlock* block, cSPEditorLimbStructure* limb, int depth);       // @ 0x48c790

struct cSPEditorLimbJoint {
    cSPEditorBlock* mJointBlock;                // +0x00
    cSPEditorLimbJoint* mUpperJoint;            // +0x04
    vector<cSPEditorLimbJoint*> mLowerJoints;   // +0x08
    cSPVector3 mTargetPosition;                 // +0x1c
    cSPVector3 mOriginalPosition;               // +0x28
    cSPVector3 mPositionAtCreation;             // +0x34
    int mJointType;                             // +0x40
    void* mSkin;                                // +0x44

    cSPMatrix3 GetOrientation(int mode);
    cSPVector3 GetLowerDirection(int i);                     // @ 0x4878e0
    cSPVector3 GetUpperDirection(int i);                     // @ 0x487e90
    cSPVector3 GetUpVector(bool b);                          // @ 0x488100
    cSPEditorLimbJoint* FindInvalidJoint(bool b);            // @ 0x4874c0
};

struct cSPEditorLimbStructure {
    vector<AutoRefCount<cSPEditorBlock> > mPileList;    // +0x00
    cSPEditorBlock* mBaseBlock;                 // +0x14
    cSPEditorLimbJoint* mBaseJoint;             // +0x18
    cSPEditorBlock* mLastBone;                  // +0x1c
    cSPEditorBlock* mEndBlock;                  // +0x20
    float mLimbOriginalScale;                   // +0x24
    float mSymmetrySign;                        // +0x28
    vector<cSPEditorLimbJoint*> mFeet;          // +0x2c
    vector<cSPEditorLimbJoint*> mHands;         // +0x40

    cSPEditorLimbStructure();
    ~cSPEditorLimbStructure();
    void Clear();
    void UpdateSymmetry();
    cSPEditorLimbJoint* FindInvalidJoint();
    void DeleteJoint(cSPEditorLimbJoint* joint);
    void UpdateTargetPositions(bool relative);
    void UpdateTargetPositions(cSPEditorLimbJoint* joint, bool relative);
    void MoveToBlock(cSPEditorBlock* block);
    void Translate(cSPEditorLimbJoint* joint, cSPVector3 delta);
    void RelocateTargets(cSPEditorLimbJoint* joint, cSPEditorLimbJoint* anchor);
    void Refresh(bool relative);
    void Init(cSPEditorBlock* block, bool isBase, bool b);
    void MirrorOriginal(cSPEditorLimbJoint* joint, float f);
    void MirrorCreation(cSPEditorLimbJoint* joint, float f);
    void CollectBlocks(cSPEditorBlock* block);               // @ 0x489900
    void SortPileList();                                     // @ 0x489bc0
    cSPEditorLimbJoint* FindJoint(cSPEditorBlock* block);    // @ 0x48b2c0
    cSPEditorLimbJoint* BuildJoints(cSPEditorBlock* block, cSPEditorLimbJoint* upper, bool b); // @ 0x48c0f0
};

// @ 0x488600
cSPMatrix3 cSPEditorLimbJoint::GetOrientation(int mode)
{
    cSPVector3 pos = (mode == 2) ? mJointBlock->mPosition : mTargetPosition;
    cSPVector3 dir;
    if (!mLowerJoints.empty()) {
        cSPVector3 lower = GetLowerDirection(0);
        dir = lower - pos;
    } else {
        cSPVector3 upper = GetUpperDirection(0);
        cSPVector3 p = pos;
        dir = p - upper;
    }
    if (dir.x * dir.x + dir.y * dir.y + dir.z * dir.z > 1.5258789e-05f) {
        dir = Normalize(dir);
        cSPVector3 up = GetUpVector(true);
        cSPVector3 side = Cross(dir, up);
        return MatrixFromAxes(dir, side);
    } else {
        return cMatrix3Init(-1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    }
}

// @ 0x488850
cSPEditorLimbStructure::cSPEditorLimbStructure()
    : mBaseBlock(0), mBaseJoint(0), mLastBone(0), mEndBlock(0)
{
}

// @ 0x488900
cSPEditorLimbStructure::~cSPEditorLimbStructure()
{
}

// @ 0x488980
void cSPEditorLimbStructure::Clear()
{
    DeleteJoint(mBaseJoint);
    mBaseJoint = 0;
    mFeet.clear();
    mHands.clear();
    mPileList.clear();
    mBaseBlock = 0;
    mLastBone = 0;
    mEndBlock = 0;
}

// @ 0x488a50
void cSPEditorLimbStructure::UpdateSymmetry()
{
    BuildPileList(mBaseBlock, this, 0);
    mBaseBlock->SetSymmetrySign(mBaseBlock->CalculateSymmetrySign());
    for (int i = 0, n = mPileList.size(); i < n; i++)
        mPileList[i]->SetSymmetrySign(mPileList[i]->CalculateSymmetrySign());
    if (mEndBlock) mSymmetrySign = (float)mEndBlock->GetSymmetryCount();
    else mSymmetrySign = (float)mBaseBlock->GetSymmetryCount();
}

// @ 0x488b30
cSPEditorLimbJoint* cSPEditorLimbStructure::FindInvalidJoint()
{
    cSPEditorLimbJoint* result = mBaseJoint->FindInvalidJoint(true);
    if (!result) {
        for (int i = 0, n = mFeet.size(); i < n; i++) {
            cSPEditorLimbJoint* j = mFeet[i]->FindInvalidJoint(true);
            if (j) { result = j; break; }
        }
        if (!result) {
            for (int i = 0, n = mHands.size(); i < n; i++) {
                cSPEditorLimbJoint* j = mHands[i]->FindInvalidJoint(true);
                if (j) { result = j; break; }
            }
        }
    }
    return result;
}

// @ 0x488c30
void cSPEditorLimbStructure::DeleteJoint(cSPEditorLimbJoint* joint)
{
    if (joint) {
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
            DeleteJoint(joint->mLowerJoints.mpBegin[i]);
        delete joint;
    }
}

// @ 0x488d00
void cSPEditorLimbStructure::UpdateTargetPositions(bool relative)
{
    UpdateTargetPositions(mBaseJoint, relative);
}

// @ 0x488d30
void cSPEditorLimbStructure::UpdateTargetPositions(cSPEditorLimbJoint* joint, bool relative)
{
    if (joint && joint->mJointBlock) {
        if (joint != mBaseJoint && relative) {
            cSPVector3 d = joint->mOriginalPosition - mBaseJoint->mOriginalPosition;
            joint->mTargetPosition = mBaseJoint->mJointBlock->GetPosition() + d;
        } else {
            joint->mTargetPosition = joint->mJointBlock->mPosition;
        }
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
            UpdateTargetPositions(joint->mLowerJoints.mpBegin[i], true);
    }
}

// @ 0x488e80
void cSPEditorLimbStructure::MoveToBlock(cSPEditorBlock* block)
{
    cSPEditorLimbJoint* joint = FindJoint(block);
    if (joint) {
        cSPVector3 d = block->mPosition - joint->mOriginalPosition;
        Translate(joint, d);
    }
}

// @ 0x488f20
void cSPEditorLimbStructure::Translate(cSPEditorLimbJoint* joint, cSPVector3 delta)
{
    if (joint && joint->mJointBlock) {
        joint->mOriginalPosition += delta;
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
            Translate(joint->mLowerJoints[i], delta);
    }
}

// @ 0x488fe0
void cSPEditorLimbStructure::RelocateTargets(cSPEditorLimbJoint* joint, cSPEditorLimbJoint* anchor)
{
    if (joint) {
        if (joint != anchor) {
            cSPVector3 d = joint->mOriginalPosition - anchor->mOriginalPosition;
            joint->mTargetPosition = anchor->mTargetPosition + d;
        }
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
            RelocateTargets(joint->mLowerJoints.mpBegin[i], anchor);
    }
}

// @ 0x4890e0
void cSPEditorLimbStructure::Refresh(bool relative)
{
    UpdateTargetPositions(mBaseJoint, relative);
    cSPVector3 d = mBaseJoint->mJointBlock->GetPosition() - mBaseJoint->mOriginalPosition;
    Translate(mBaseJoint, d);
    UpdateSymmetry();
}

// @ 0x4891a0
void cSPEditorLimbStructure::Init(cSPEditorBlock* block, bool isBase, bool b)
{
    if (block) {
        if (!isBase) {
            if (block->mFlags.test(0x2d) && block->IsLimbPart()) {
                cSPEditorBlock* p = block->GetParent();
                while (p && p->IsLimbPart() && p->GetParent() && p->GetParent()->IsLimbPart() &&
                       (p->mFlags.test(0xb) || p->mFlags.test(8)))
                    p = p->GetParent();
                mBaseBlock = p;
            } else {
                mBaseBlock = GetLimbRoot(block);
            }
        } else {
            mBaseBlock = block;
        }
        CollectBlocks(block);
        mPileList.clear();
        BuildPileList(mBaseBlock, this, 0);
        SortPileList();
        DeleteJoint(mBaseJoint);
        mBaseJoint = BuildJoints(mBaseBlock, 0, b);
        UpdateSymmetry();
    } else {
        mBaseBlock = 0;
    }
}

// @ 0x4893f0
void cSPEditorLimbStructure::MirrorOriginal(cSPEditorLimbJoint* joint, float f)
{
    if (!joint->mJointBlock->IsLimbPart()) {
        cSPVector3 m = Mirror(joint->mOriginalPosition);
        joint->mOriginalPosition = m;
    }
    for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
        MirrorOriginal(joint->mLowerJoints.mpBegin[i], f);
}

// @ 0x489490
void cSPEditorLimbStructure::MirrorCreation(cSPEditorLimbJoint* joint, float f)
{
    if (!joint->mJointBlock->IsLimbPart()) {
        cSPVector3 m = Mirror(joint->mPositionAtCreation);
        joint->mPositionAtCreation = m;
    }
    for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
        MirrorCreation(joint->mLowerJoints.mpBegin[i], f);
}

}  // namespace SP
