// Slice s0048a4e0: SP::cSPEditorLimbStructure joint-tree walkers (UI state, symmetry, target positions).
// Module flags: /Od /Ob1 /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---- rw::math / cSP math types ----
struct Vector3T {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v);                                        // @ 0x4098a0 (out of line)
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
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
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
    void push_back(const T& value);                          // @ 0x454860
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
    char pad0[0x33c - 4];
    AutoRefCount<cSPEditorBlock> mParentBlock;  // +0x33c
    vector<AutoRefCount<cSPEditorBlock> > mSymmetricBlocks;   // +0x340
    char pad1[0x3e0 - 0x354];
    int mUIState;                               // +0x3e0

    int GetUIState() const { return mUIState; }
    bool IsLimbPart();                                       // @ 0x435c80
    int CalculateSymmetrySign();                             // @ 0x44f240
    void SetModelBasedOnSymmetrySign(int sign, bool a, bool b, bool c, int d);   // @ 0x439110
    void UpdateLimbModel();                                  // @ 0x449ce0
};

void GetSymmetricBlocks(cSPEditorBlock* block, vector<AutoRefCount<cSPEditorBlock> >& out);         // @ 0x48c8d0
namespace EditorUtils {
void SetSymmetricBlocksUIState(cSPEditorBlock* block, vector<AutoRefCount<cSPEditorBlock> >& blocks, bool b);  // @ 0x4a7f30
}

Vector3T operator-(const Vector3T& a, const Vector3T& b);                 // @ 0x41db10
Vector3T operator/(const Vector3T& v, const float& s);                    // @ 0x453880
Vector3T operator*(const float& s, const Vector3T& v);                    // @ 0x41de40
Vector3T operator*(const Vector3T& v, const float& s);                    // @ 0x41dca0
cSPVector3 Normalize(const Vector3T& v);                                  // @ 0x436ce0
Vector3T normalized_safe(const Vector3T& v);                              // @ 0x449c20
inline float Dot(const Vector3T& a, const Vector3T& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

struct cSPEditorLimbJoint {
    cSPEditorBlock* mJointBlock;                // +0x00
    cSPEditorLimbJoint* mUpperJoint;            // +0x04
    vector<cSPEditorLimbJoint*> mLowerJoints;   // +0x08
    cSPVector3 mTargetPosition;                 // +0x1c
    cSPVector3 mOriginalPosition;               // +0x28
    cSPVector3 mPositionAtCreation;             // +0x34
    int mJointType;                             // +0x40
    void* mSkin;                                // +0x44

    cSPEditorLimbJoint* FindInvalidJoint(bool b);            // @ 0x4874c0
    bool UpdateLength(bool b);                               // @ 0x486910
    bool IsValid();                                          // @ 0x486d40
    bool Fix(cSPEditorLimbJoint* invalid);                   // @ 0x486e70
    float GetLength();                                       // @ 0x4873d0
    void MoveTarget(Vector3T pos);                           // @ 0x486f50
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

    void UpdateLimbModels(cSPEditorLimbJoint* joint);
    void SetUIState(int state);
    void SetUIState(cSPEditorLimbJoint* joint, int state);
    void SetJointTarget(cSPEditorLimbJoint* joint, cSPVector3 pos);
    void AdjustJoint(cSPEditorLimbJoint* joint, cSPEditorLimbJoint* anchor, cSPEditorLimbJoint* skip, bool flattenX);
    void UpdateSymmetryModels(cSPEditorLimbJoint* joint, bool a, bool b);
    void UpdateSymmetryModels(bool a, bool b);
    bool AreJointsValid(vector<cSPEditorLimbJoint*>* joints);
    bool FixJoints(vector<cSPEditorLimbJoint*>* joints);
    bool FixJoint(cSPEditorLimbJoint* joint);
    bool UpdateLengths(vector<cSPEditorLimbJoint*>* joints);
    void FixZeroLengthJoints(cSPEditorLimbJoint* joint);
    void CollectLimbJoints(vector<cSPEditorLimbJoint*>* out);
    void CollectLimbJoints(cSPEditorLimbJoint* joint, vector<cSPEditorLimbJoint*>* out);
    cSPEditorLimbJoint* FindJoint(cSPEditorBlock* block);
    cSPEditorLimbJoint* FindJoint(cSPEditorBlock* block, cSPEditorLimbJoint* joint);
    cSPEditorLimbJoint* FindInvalidJoint();                  // @ 0x488b30
};

// @ 0x48a4e0
void cSPEditorLimbStructure::UpdateLimbModels(cSPEditorLimbJoint* joint)
{
    if (joint) {
        if (joint->mJointBlock) joint->mJointBlock->UpdateLimbModel();
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
            UpdateLimbModels(joint->mLowerJoints.mpBegin[i]);
    }
}

// @ 0x48a560
void cSPEditorLimbStructure::SetUIState(int state)
{
    SetUIState(mBaseJoint, state);
}

// @ 0x48a580
void cSPEditorLimbStructure::SetUIState(cSPEditorLimbJoint* joint, int state)
{
    if (joint) {
        if (joint->mJointBlock->GetUIState() != state) {
            vector<AutoRefCount<cSPEditorBlock> > blocks;
            GetSymmetricBlocks(joint->mJointBlock, blocks);
            EditorUtils::SetSymmetricBlocksUIState(joint->mJointBlock, blocks, true);
        }
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
            SetUIState(joint->mLowerJoints.mpBegin[i], state);
    }
}

// @ 0x48a650
void cSPEditorLimbStructure::SetJointTarget(cSPEditorLimbJoint* joint, cSPVector3 pos)
{
    if (joint) {
        joint->mTargetPosition = pos;
        AdjustJoint(joint, joint, 0, true);
    }
}

// @ 0x48a690
void cSPEditorLimbStructure::AdjustJoint(cSPEditorLimbJoint* joint, cSPEditorLimbJoint* anchor,
                                         cSPEditorLimbJoint* skip, bool flattenX)
{
    if (joint) {
        if (joint != anchor && joint != mBaseJoint) {
            cSPVector3 anchorTarget = anchor->mTargetPosition;
            bool flatten = flattenX && Abs(joint->mTargetPosition[0]) < 0.001f;
            if (joint->mJointBlock == mEndBlock) flatten = false;
            cSPVector3 baseTarget = mBaseJoint->mTargetPosition;
            cSPVector3 target = anchorTarget;
            cSPVector3 axis = anchor->mPositionAtCreation - mBaseJoint->mPositionAtCreation;
            float axisLen = VectorLength(axis) + 1e-12f;
            cSPVector3 axisDir = axis / axisLen;
            cSPVector3 rel = joint->mPositionAtCreation - mBaseJoint->mPositionAtCreation;
            float along = Dot(axisDir, rel);
            cSPVector3 proj = along * axisDir;
            float projLen = VectorLength(proj) + 1e-12f;
            float side = Dot(axisDir, normalized_safe(proj));
            if (side < 0.0f) projLen *= -1.0f;
            cSPVector3 perp = joint->mPositionAtCreation - (mBaseJoint->mPositionAtCreation + proj);
            if (flatten) {
                baseTarget[0] = 0.0f;
                target[0] = 0.0f;
                perp[0] = 0.0f;
            }
            cSPVector3 dir = target - baseTarget;
            float dirLen = VectorLength(dir) + 1e-12f;
            float ratio = dirLen / axisLen;
            dir = Normalize(dir);
            float weight = 1.0f;
            cSPVector3 newPos = dir * projLen * ratio + perp * weight + baseTarget;
            Vector3T delta(newPos - joint->mTargetPosition);
            joint->mTargetPosition = newPos;
            for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++) {
                cSPEditorLimbJoint* child = joint->mLowerJoints.mpBegin[i];
                if (child != skip)
                    child->MoveTarget(child->mTargetPosition + delta);
            }
        }
        AdjustJoint(joint->mUpperJoint, anchor, joint, true);
    }
}

// @ 0x48ad20
void cSPEditorLimbStructure::UpdateSymmetryModels(cSPEditorLimbJoint* joint, bool a, bool b)
{
    cSPEditorLimbJoint* invalid = joint->FindInvalidJoint(true);
    if (!joint->mJointBlock->IsLimbPart()) {
        vector<AutoRefCount<cSPEditorBlock> >& syms = joint->mJointBlock->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++) {
            int sign = syms[i]->CalculateSymmetrySign();
            syms[i]->SetModelBasedOnSymmetrySign(sign, b, a, true, 0);
        }
    }
    for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
        UpdateSymmetryModels(joint->mLowerJoints.mpBegin[i], false, false);
}

// @ 0x48ae30
void cSPEditorLimbStructure::UpdateSymmetryModels(bool a, bool b)
{
    UpdateSymmetryModels(mBaseJoint, a, b);
}

// @ 0x48ae60
bool cSPEditorLimbStructure::AreJointsValid(vector<cSPEditorLimbJoint*>* joints)
{
    bool changed = false;
    if (joints && !joints->empty()) {
        for (int i = 0, n = joints->size(); i < n; i++) {
            bool r = (*joints)[i]->IsValid();
            changed = r || changed;
        }
    }
    return changed;
}

// @ 0x48af00
bool cSPEditorLimbStructure::FixJoints(vector<cSPEditorLimbJoint*>* joints)
{
    bool changed = false;
    if (joints && !joints->empty()) {
        for (int i = 0, n = joints->size(); i < n; i++) {
            bool r = (*joints)[i]->Fix((*joints)[i]->FindInvalidJoint(false));
            changed = r || changed;
        }
    }
    return changed;
}

// @ 0x48afc0
bool cSPEditorLimbStructure::FixJoint(cSPEditorLimbJoint* joint)
{
    bool changed = false;
    if (joint) {
        changed = joint->Fix(joint->FindInvalidJoint(false));
        for (int y = 0, p11 = joint->mLowerJoints.size(); y < p11; y++) {
            bool r = FixJoint(joint->mLowerJoints[y]);
            changed = r || changed;
        }
    }
    return changed;
}

// @ 0x48b080
bool cSPEditorLimbStructure::UpdateLengths(vector<cSPEditorLimbJoint*>* joints)
{
    bool changed = false;
    if (joints && !joints->empty()) {
        for (int i = 0, n = joints->size(); i < n; i++) {
            bool r = (*joints)[i]->UpdateLength(false);
            changed = r || changed;
        }
    }
    return changed;
}

// @ 0x48b120
void cSPEditorLimbStructure::FixZeroLengthJoints(cSPEditorLimbJoint* joint)
{
    float len = joint->GetLength();
    if (len != 0.0f) {
        bool valid = joint->IsValid();
        if (!valid) joint->Fix(FindInvalidJoint());
    }
    for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
        FixZeroLengthJoints(joint->mLowerJoints.mpBegin[i]);
}

// @ 0x48b1e0
void cSPEditorLimbStructure::CollectLimbJoints(vector<cSPEditorLimbJoint*>* out)
{
    CollectLimbJoints(mBaseJoint, out);
}

// @ 0x48b200
void cSPEditorLimbStructure::CollectLimbJoints(cSPEditorLimbJoint* joint, vector<cSPEditorLimbJoint*>* out)
{
    if (joint->mJointBlock->IsLimbPart()) {
        out->push_back(joint);
        ScratchSlots<2>();
    } else {
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++) {
            if (joint->mLowerJoints[i]->mJointBlock->IsLimbPart())
                { out->push_back(joint->mLowerJoints.mpBegin[i]); ScratchSlots<2>(); }
            else
                CollectLimbJoints(joint->mLowerJoints.mpBegin[i], out);
        }
    }
}

// @ 0x48b2c0
cSPEditorLimbJoint* cSPEditorLimbStructure::FindJoint(cSPEditorBlock* block)
{
    return FindJoint(block, mBaseJoint);
}

// @ 0x48b2e0
cSPEditorLimbJoint* cSPEditorLimbStructure::FindJoint(cSPEditorBlock* block, cSPEditorLimbJoint* joint)
{
    if (!joint || joint->mJointBlock == block) return joint;
    else {
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++) {
            cSPEditorLimbJoint* found = FindJoint(block, joint->mLowerJoints[i]);
            if (found) return found;
        }
        return 0;
    }
}

}  // namespace SP
