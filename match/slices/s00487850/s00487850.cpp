// Slice s00487850: SP::cSPEditorLimbJoint direction / up-vector helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
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
struct Matrix33T {
    Vector3T xAxis, yAxis, zAxis;
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

Vector3T operator-(const Vector3T& v);                        // @ 0x422020 (negate)
Vector3T operator-(const Vector3T& a, const Vector3T& b);    // @ 0x41db10
Vector3T operator+(const Vector3T& a, const Vector3T& b);    // @ 0x41dc10
Vector3T operator*(const Vector3T& v, const float& s);       // @ 0x41dca0
cSPVector3 Normalize(const Vector3T& v);                     // @ 0x436ce0
cSPVector3 Cross(const Vector3T& a, const Vector3T& b);      // @ 0x44e460
float Dot3(const Vector3T& v);                               // @ 0x4885d0

// global direction constants (retail addresses)
extern cSPVector3 DAT_015d5db8;                              // @ 0x15d5db8
extern cSPVector3 DAT_015d5e00;                              // @ 0x15d5e00
extern float DAT_015d5f68;                                   // @ 0x15d5f68
extern float DAT_015d5f6c;                                   // @ 0x15d5f6c
extern float DAT_015d5f70;                                   // @ 0x15d5f70

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
    char pad3[0x33c - 0x84];
    cSPEditorBlock* mLink33c;                   // +0x33c
    char pad4[0xdc8 - 0x340];
    bitset<60> mFlags;                          // +0xdc8
    bool F_44c030();                            // @ 0x44c030
    cSPVector3 F_43e080();                      // @ 0x43e080
};

struct cSPEditorLimbJoint {
    cSPEditorBlock* mJointBlock;                // +0x00
    cSPEditorLimbJoint* mUpperJoint;            // +0x04
    vector<cSPEditorLimbJoint*> mLowerJoints;   // +0x08
    cSPVector3 mTargetPosition;                 // +0x1c
    cSPVector3 mOriginalPosition;               // +0x28
    cSPVector3 mPositionAtCreation;             // +0x34

    cSPEditorLimbJoint* FindFirstLimbLowerJoint();      // @ 0x487850
    cSPVector3 GetLowerDirection(int mode);             // @ 0x4878e0
    cSPVector3 GetUpperDirection(int mode);             // @ 0x487e90
    cSPVector3 GetUpVector(bool b);                     // @ 0x488100
    int Sign(bool recurse);                             // @ 0x4874c0 (slice 76)
};

// @ 0x487850
cSPEditorLimbJoint* cSPEditorLimbJoint::FindFirstLimbLowerJoint()
{
    if (!mLowerJoints.empty()) {
        for (int i = 0, n = mLowerJoints.size(); i < n; i++) {
            if (mLowerJoints[i]->mJointBlock->F_44c030())
                return mLowerJoints[i];
        }
    }
    return 0;
}

// @ 0x4878e0
cSPVector3 cSPEditorLimbJoint::GetLowerDirection(int mode)
{
    if (mLowerJoints.empty()) {
        if (mJointBlock->mFlags.test(0xb))
            return mJointBlock->mPosition + mJointBlock->F_43e080();
        if (mode == 1) return mOriginalPosition + DAT_015d5db8 * 0.1f;
        if (mode == 3) return mPositionAtCreation + DAT_015d5db8 * 0.1f;
        if (mode == 2) return mJointBlock->mPosition + DAT_015d5db8 * 0.1f;
        if (mode == 0) return mTargetPosition + DAT_015d5db8 * 0.1f;
    } else {
        cSPEditorLimbJoint* p = FindFirstLimbLowerJoint();
        if (p) {
            if (mode == 1) return p->mOriginalPosition;
            if (mode == 3) return p->mPositionAtCreation;
            if (mode == 2) return p->mJointBlock->mPosition;
            if (mode == 0) return p->mTargetPosition;
        }
    }
    if (mode == 1) return mOriginalPosition;
    if (mode == 3) return mPositionAtCreation;
    if (mode == 2) return mJointBlock->mPosition;
    if (mode == 0) return mTargetPosition;
    cSPVector3 d;
    d.x = DAT_015d5f68; d.y = DAT_015d5f6c; d.z = DAT_015d5f70;
    return d;
}

// @ 0x487e90
cSPVector3 cSPEditorLimbJoint::GetUpperDirection(int mode)
{
    if (mUpperJoint == 0) {
        if (mJointBlock->mLink33c == 0) return mJointBlock->mPosition;
        else return mJointBlock->mLink33c->mPosition;
    }
    if (mode == 1) return mUpperJoint->mOriginalPosition;
    if (mode == 3) return mUpperJoint->mPositionAtCreation;
    if (mode == 0) return mUpperJoint->mTargetPosition;
    if (mode == 2) {
        if (mUpperJoint->mJointBlock->mFlags.test(0x1f))
            return mUpperJoint->mJointBlock->mPosition;
        else return mJointBlock->mPosition;
    }
    cSPVector3 d;
    d.x = DAT_015d5f68; d.y = DAT_015d5f6c; d.z = DAT_015d5f70;
    return d;
}

// @ 0x488100
cSPVector3 cSPEditorLimbJoint::GetUpVector(bool b)
{
    if (mUpperJoint == 0 && mLowerJoints.empty())
        return -mJointBlock->mOrientation.xAxis;

    if (mUpperJoint != 0 && !mLowerJoints.empty()) {
        cSPVector3 upper = mUpperJoint->mTargetPosition;
        cSPVector3 mine = mTargetPosition;
        cSPVector3 lower = mLowerJoints[0]->mTargetPosition;
        cSPVector3 a = mine - upper;
        cSPVector3 c = lower - mine;
        cSPVector3 cross = Cross(c, a);
        float len2 = cross.x * cross.x + cross.y * cross.y + cross.z * cross.z;
        if (len2 > 1.5258789e-05f)
            return Normalize(cross);
    }

    if (mUpperJoint != 0) {
        if (b) return mUpperJoint->GetUpVector(true);
        if (mLowerJoints.empty()) {
            cSPVector3 mine = mTargetPosition;
            cSPVector3 upper = mUpperJoint->mTargetPosition;
            cSPVector3 a = mine - upper;
            cSPVector3 cross = Cross(a, DAT_015d5db8);
            float len2 = cross.x * cross.x + cross.y * cross.y + cross.z * cross.z;
            if (len2 < 1.5258789e-05f) {
                cSPVector3 cross2 = Cross(a, DAT_015d5e00);
                float d = Dot3(cross2);
                if (d < 1.5258789e-05f)
                    return -DAT_015d5e00;
                return Normalize(cross2);
            }
            return Normalize(cross);
        }
    }

    int sign = Sign(false);
    if (sign == 0) return -DAT_015d5e00;
    for (int i = 0, n = mLowerJoints.size(); i < n; i++) {
        if (mLowerJoints[i]->Sign(false) == 0)
            return -DAT_015d5e00;
    }
    return mLowerJoints[0]->GetUpVector(false);
}

// @ 0x4885d0
float Dot3(const Vector3T& v)
{
    return (v.x * v.x + v.y * v.y) + v.z * v.z;
}

}  // namespace SP
