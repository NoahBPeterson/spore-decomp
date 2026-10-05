// Slice s0048b370: SP::cSPEditorLimbStructure foot/hand + length helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T { Vector3T xAxis, yAxis, zAxis; };
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

template<class T> struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator[2];
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    bool empty() const;                          // @ 0x526430
};

template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) return (mWord[i >> 5] & (1u << (i % 32))) != 0;
        return false;
    }
};

namespace SP {

struct cSPEditorBlock;
struct cSPEditorLimbJoint;

struct cSPEditorBlock {
    virtual void _v0();
    virtual int Release();
    char pad0[0x28 - 4];
    void* mEditorModel;                         // +0x28
    char pad1[0x48 - 0x2c];
    cSPVector3 mPosition;                       // +0x48
    char pad2[0x60 - 0x54];
    Matrix33T mOrientation;                     // +0x60
    char pad3[0x218 - 0x84];
    float mMinScale;                            // +0x218
    float mMaxScale;                            // +0x21c
    char pad4[0x33c - 0x220];
    cSPEditorBlock* mLink33c;                   // +0x33c
    char pad5[0x3ec - 0x340];
    void* mField3ec;                            // +0x3ec
    void* mField3f0;                            // +0x3f0
    char pad6[0xc0c - 0x3f4];
    vector<void*> mVec0c0c;                     // +0xc0c
    char pad7[0xdc8 - 0xc20];
    bitset<60> mFlags;                          // +0xdc8
    void F_451360();                            // @ 0x451360
    void F_451330(cSPVector3 v);                // @ 0x451330
    void F_448e90(cSPVector3* v, int i);        // @ 0x448e90
    void F_43eb50(float f);                     // @ 0x43eb50
    void F_4860b0(float a, float b);            // @ 0x4860b0
    bool IsLimbPart();                          // @ 0x435c80
};

struct cSPEditorLimbJoint {
    cSPEditorBlock* mJointBlock;                // +0x00
    cSPEditorLimbJoint* mUpperJoint;            // +0x04
    vector<cSPEditorLimbJoint*> mLowerJoints;   // +0x08
    cSPVector3 mTargetPosition;                 // +0x1c
    cSPVector3 mOriginalPosition;               // +0x28
    cSPVector3 mPositionAtCreation;             // +0x34
    float mField40;                             // +0x40

    void F_485b90(cSPVector3* out);             // @ 0x485b90
    float F_485eb0();                           // @ 0x485eb0
    bool UpdateLength(bool b);                  // @ 0x486910
};

struct cSPEditorLimbStructure {
    vector<cSPEditorBlock*> mPileList;          // +0x00
    cSPEditorBlock* mBaseBlock;                 // +0x14
    cSPEditorLimbJoint* mBaseJoint;             // +0x18
    cSPEditorBlock* mLastBone;                  // +0x1c
    cSPEditorBlock* mEndBlock;                  // +0x20
    float mLimbOriginalScale;                   // +0x24
    float mSymmetrySign;                        // +0x28
    vector<cSPEditorLimbJoint*> mFeet;          // +0x2c
    vector<cSPEditorLimbJoint*> mHands;         // +0x40

    void F_48b370(cSPEditorBlock* block, float f);          // @ 0x48b370
    void SetFeetTargets(bool b);                            // @ 0x48bae0
    void SetHandsTargets(bool b);                           // @ 0x48bbb0
    float GetMaxDistanceFromBase();                         // @ 0x48bca0
    void UpdateFeetTargets();                               // @ 0x48bdd0
    bool UpdateLengths(cSPEditorLimbJoint* joint, bool b);  // @ 0x48be80
    void F_48bf40(bool b);                                  // @ 0x48bf40
    bool F_48bf70(cSPEditorLimbJoint* joint, bool b);       // @ 0x48bf70
    void F_48bfc0(cSPEditorLimbJoint* joint);               // @ 0x48bfc0
    void F_48c050(cSPEditorLimbJoint* joint);               // @ 0x48c050
    void SetJointTarget(cSPEditorLimbJoint* joint, cSPVector3 pos);  // @ 0x48a650
};

cSPEditorLimbJoint* FindJoint(cSPEditorBlock* block);        // @ 0x48b2c0

// @ 0x48b370
void cSPEditorLimbStructure::F_48b370(cSPEditorBlock* block, float f)
{
    // Best-effort reconstruction of the per-limb scale-range update.
    cSPEditorLimbJoint* joint = FindJoint(block);
    if (!joint) return;
    float lo = 1.0e-20f;
    float hi = 1.0e20f;
    bool flag = false;
    cSPEditorBlock* base = joint->mJointBlock;
    if (joint->mUpperJoint == 0) {
        lo = base->mMinScale;
        hi = base->mMaxScale;
    } else {
        for (int i = 0, n = joint->mUpperJoint->mLowerJoints.size(); i < n; i++) {
            cSPEditorBlock* b = joint->mUpperJoint->mLowerJoints[i]->mJointBlock;
            if (b->mField3ec) {
                if (b->mFlags.test(0x2d) || b->mFlags.test(0x2c)) flag = true;
                if (lo < b->mMinScale) lo = b->mMinScale;
                if (b->mMaxScale < hi) hi = b->mMaxScale;
            }
        }
    }
    float a = lo;
    float c = hi;
    float scaled = a;
    if (scaled < a) scaled = a;
    if (c < scaled) scaled = c;
    (void)flag;
    base->F_4860b0(scaled, f);
    base->F_43eb50(scaled);
}

// @ 0x48bae0
void cSPEditorLimbStructure::SetFeetTargets(bool b)
{
    for (int i = 0, n = mFeet.size(); i < n; i++) {
        cSPEditorLimbJoint* j = mFeet[i];
        cSPVector3 v;
        j->F_485b90(&v);
        j->mTargetPosition = v;
        if (b) j->mJointBlock->F_448e90(&j->mTargetPosition, 0);
    }
}

// @ 0x48bbb0
void cSPEditorLimbStructure::SetHandsTargets(bool b)
{
    for (int i = 0, n = mHands.size(); i < n; i++) {
        cSPEditorLimbJoint* j = mHands[i];
        float d = j->F_485eb0();
        if (d < 0.0f) {
            cSPVector3 v;
            j->F_485b90(&v);
            j->mTargetPosition = v;
            if (b) j->mJointBlock->F_448e90(&j->mTargetPosition, 0);
        }
    }
}

// @ 0x48bca0
float cSPEditorLimbStructure::GetMaxDistanceFromBase()
{
    float base = mBaseJoint->mField40;
    float best = 0.0f;
    for (int i = 0, n = mHands.size(); i < n; i++) {
        float d = base - mHands[i]->mField40;
        if (best < d) best = d;
    }
    for (int i = 0, n = mFeet.size(); i < n; i++) {
        float d = base - mFeet[i]->mField40;
        if (best < d) best = d;
    }
    return best;
}

// @ 0x48bdd0
void cSPEditorLimbStructure::UpdateFeetTargets()
{
    for (int i = 0, n = mFeet.size(); i < n; i++) {
        cSPEditorLimbJoint* j = mFeet[i];
        cSPVector3 v;
        j->F_485b90(&v);
        SetJointTarget(j, v);
    }
    SetFeetTargets(false);
    SetHandsTargets(false);
}

// @ 0x48be80
bool cSPEditorLimbStructure::UpdateLengths(cSPEditorLimbJoint* joint, bool b)
{
    bool result = false;
    if (joint != 0) {
        result = joint->UpdateLength(b);
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++) {
            bool r = UpdateLengths(joint->mLowerJoints[i], b);
            result = (r || result);
        }
    }
    return result;
}

// @ 0x48bf40
void cSPEditorLimbStructure::F_48bf40(bool b)
{
    UpdateLengths(mBaseJoint, b);
}

// @ 0x48bf70
bool cSPEditorLimbStructure::F_48bf70(cSPEditorLimbJoint* joint, bool b)
{
    bool result = UpdateLengths(joint, b);
    return result;
}

// @ 0x48bfc0
void cSPEditorLimbStructure::F_48bfc0(cSPEditorLimbJoint* joint)
{
    joint->mJointBlock->F_451360();
    for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
        F_48bfc0(joint->mLowerJoints[i]);
}

// @ 0x48c050
void cSPEditorLimbStructure::F_48c050(cSPEditorLimbJoint* joint)
{
    joint->mJointBlock->F_451330(joint->mJointBlock->mPosition);
    for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
        F_48c050(joint->mLowerJoints[i]);
}

}  // namespace SP
