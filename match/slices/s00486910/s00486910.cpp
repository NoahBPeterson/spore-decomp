// Slice s00486910: SP::cSPEditorLimbJoint tree/validity helpers.
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
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPBoundingBox { cSPVector3 mMin, mMax; };

Vector3T operator-(const Vector3T& a, const Vector3T& b);    // @ 0x41db10
Vector3T operator+(const Vector3T& a, const Vector3T& b);    // @ 0x41dc10
Vector3T operator*(const Vector3T& v, const float& s);       // @ 0x41dca0
bool operator!=(const Vector3T& a, const Vector3T& b);       // @ 0x41dd30
float VectorLength(const Vector3T& v);                       // @ 0x40ae50
cSPVector3 normalized_safe(const Vector3T& v);               // @ 0x449c20

inline const float& Max(const float& a, const float& b) { return (a > b) ? a : b; }
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float Abs(float x) { float r = (float)fabs(x); return r; }

inline float SignOf(float v)
{
    float s;
    if (v < -0.001f) s = -1.0f;
    else if (v > 0.001f) s = 1.0f;
    else s = 0.0f;
    return s;
}

// ---- EASTL-style vector ----
template<class T> struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator[2];   // +0x14
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    bool empty() const;                          // @ 0x526430
    void push_back(const T& v);                  // @ 0x454860
    void eraseOne(T* it);                        // @ 0x48c720
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

struct cSPEditorModel {
    char pad0[0x38];
    float mScale;                               // +0x38
    float mX3c;                                 // +0x3c
    float mX40;                                 // +0x40
    float mX44;                                 // +0x44
    float GetScale();                           // @ 0x4adaa0
    float F_7f9410();                           // @ 0x7f9410
    float F_4adb00();                           // @ 0x4adb00
    float F_4adb40();                           // @ 0x4adb40
    cSPEditorBlock* FindNearestFlag7Block(const cSPVector3& pos);   // @ 0x4ac480
};

struct cSPEditorBlock {
    virtual void _v0();
    virtual int Release();
    char pad0[0x28 - 4];
    cSPEditorModel* mEditorModel;               // +0x28
    char pad1[0x48 - 0x2c];
    cSPVector3 mPosition;                       // +0x48
    char pad2[0x33c - 0x54];
    cSPEditorBlock* mLink33c;                   // +0x33c
    char pad3[0xdc8 - 0x340];
    bitset<60> mFlags;                          // +0xdc8

    bool IsLimbPart();                                                   // @ 0x435c80
    void SetFlag(int index, bool value);                                 // @ 0x435a10
    float GetRadius();                                                   // @ 0x43f250
    void RefreshLinks(cSPEditorBlock* e);                                // @ 0x438700
    void RefreshLinked(cSPEditorBlock* e);                               // @ 0x438a40
    bool Check(cSPEditorBlock* self, cSPVector3 pos, cSPVector3* out,
               bool* flag, float f, int i);                              // @ 0x4974e0
    void F_43f5b0(cSPVector3* out, cSPVector3 pos, cSPEditorLimbJoint* invalid); // @ 0x43f5b0
};

float GetExactSkinRadius(cSPEditorBlock* block);                 // @ 0x4a5bd0
cSPVector3 GetSkinTip(cSPEditorBlock* block);                    // @ 0x4a5d10
int F_493640(cSPVector3* pos, float f0, float fa, float fb, int i);  // @ 0x493640

struct cSPEditorLimbJoint {
    cSPEditorBlock* mJointBlock;                // +0x00
    cSPEditorLimbJoint* mUpperJoint;            // +0x04
    vector<cSPEditorLimbJoint*> mLowerJoints;   // +0x08
    cSPVector3 mTargetPosition;                 // +0x1c
    cSPVector3 mOriginalPosition;               // +0x28
    cSPVector3 mPositionAtCreation;             // +0x34
    cSPVector3 mTargetOffset;                   // +0x40
    cSPVector3 mOriginalOffset;                 // +0x4c
    cSPVector3 mCreationOffset;                 // +0x58

    bool UpdateLength(bool b);                                          // @ 0x486910
    bool IsValid();                                                     // @ 0x486d40
    bool Fix(cSPEditorLimbJoint* invalid);                              // @ 0x486e70
    void F_486f50(cSPVector3 pos);                                      // @ 0x486f50
    void AddLowerJoint(cSPEditorLimbJoint* child);                      // @ 0x487040
    void RemoveLowerJoint(cSPEditorLimbJoint* child);                   // @ 0x487090
    void F_487140(cSPEditorLimbJoint* child);                           // @ 0x487140
    void F_487290(cSPEditorLimbJoint* child);                           // @ 0x487290
    float GetLength();                                                  // @ 0x4873d0
    int Sign(bool recurse);                                             // @ 0x4874c0
    int SignFromBlock(bool recurse);                                    // @ 0x4876b0
    void SetTargetPosition(cSPVector3 pos);                             // @ 0x485930
    void Move(cSPVector3 delta, bool relative);                         // @ 0x485960
    void Translate(cSPVector3 delta);                                   // @ 0x485af0
    void F_485b90(cSPVector3* out);                                     // @ 0x485b90
};

// @ 0x486910
bool cSPEditorLimbJoint::UpdateLength(bool b)
{
    bool changed = false;
    if (!mJointBlock->mEditorModel) return changed;
    float scale = 0.99f;
    float f0 = mJointBlock->mEditorModel->GetScale() * scale;
    if (mJointBlock->mFlags.test(0x2d))
        f0 = mJointBlock->mEditorModel->F_7f9410() * scale;
    float fa = mJointBlock->mEditorModel->F_4adb00() * scale;
    float fb = mJointBlock->mEditorModel->F_4adb40() * scale;
    float radius = mJointBlock->GetRadius();
    float margin = 0.05f;
    cSPVector3 pos = mTargetPosition;
    if (!b && mUpperJoint) {
        cSPEditorBlock* nearest = mJointBlock->mEditorModel->FindNearestFlag7Block(pos);
        if (nearest) {
            cSPVector3 tip = GetSkinTip(nearest);
            cSPVector3 dir = pos - tip;
            cSPVector3 ndir = normalized_safe(dir);
            float r = GetExactSkinRadius(nearest);
            cSPVector3 p2 = tip + ndir * r;
            float dist = VectorLength(pos - p2);
            if (dist < radius + margin) {
                pos = p2 + ndir * (radius + margin);
                changed = true;
            }
        }
    }
    cSPVector3 top;
    F_485b90(&top);
    if (top.z > pos.z) { pos = top; changed = true; }
    if (!b) {
        if (F_493640(&pos, f0, fa, fb, 0) != 3) changed = true;
    }
    mTargetPosition = pos;
    return changed;
}

// @ 0x486d40
bool cSPEditorLimbJoint::IsValid()
{
    bool changed = false;
    float len = GetLength();
    cSPVector3 out;
    bool flag;
    if (mJointBlock->Check(mJointBlock, mTargetPosition, &out, &flag, 1.0f, 0)) {
        if (mUpperJoint == 0 || mUpperJoint->GetLength() == 0.0f) {
            mTargetPosition = out;
            mJointBlock->SetFlag(0xf, true);
            changed = true;
        }
    }
    if (!changed) {
        if (mJointBlock->mFlags.test(0xf))
            mJointBlock->SetFlag(0xf, false);
    }
    return changed;
}

// @ 0x486e70
bool cSPEditorLimbJoint::Fix(cSPEditorLimbJoint* invalid)
{
    bool changed = false;
    if (invalid && mUpperJoint) {
        if (!mJointBlock->IsLimbPart()) {
            cSPVector3 out;
            mJointBlock->F_43f5b0(&out, mTargetPosition, invalid);
            if (out != mTargetPosition) {
                SetTargetPosition(out);
                changed = true;
            }
        }
    }
    return changed;
}

// @ 0x486f50
void cSPEditorLimbJoint::F_486f50(cSPVector3 pos)
{
    mTargetPosition = pos;
    cSPVector3 delta = mTargetPosition - mOriginalPosition;
    for (int i = 0, n = mLowerJoints.size(); i < n; i++)
        mLowerJoints[i]->Move(delta, false);
}

// @ 0x487040
void cSPEditorLimbJoint::AddLowerJoint(cSPEditorLimbJoint* child)
{
    if (child->mUpperJoint) child->mUpperJoint->RemoveLowerJoint(child);
    mLowerJoints.push_back(child);
    mJointBlock->RefreshLinks(child->mJointBlock);
    child->mUpperJoint = this;
    ScratchSlots<2>();
}

// @ 0x487090
void cSPEditorLimbJoint::RemoveLowerJoint(cSPEditorLimbJoint* child)
{
    cSPEditorLimbJoint** pEnd = mLowerJoints.end();
    cSPEditorLimbJoint** it = mLowerJoints.begin();
    while (it != pEnd && *it != child) ++it;
    if (it != mLowerJoints.end()) {
        mLowerJoints.eraseOne(it);
        if (child->mJointBlock->mLink33c)
            child->mJointBlock->mLink33c->RefreshLinked(child->mJointBlock);
        child->mUpperJoint = 0;
    }
}

// @ 0x487140
void cSPEditorLimbJoint::F_487140(cSPEditorLimbJoint* child)
{
    cSPEditorLimbJoint** pEnd = mLowerJoints.end();
    cSPEditorLimbJoint** it = mLowerJoints.begin();
    while (it != pEnd && *it != child) ++it;
    if (it != mLowerJoints.end()) {
        child->mTargetOffset = child->mTargetPosition - mTargetPosition;
        child->mOriginalOffset = child->mOriginalPosition - mOriginalPosition;
        child->mCreationOffset = child->mPositionAtCreation - mPositionAtCreation;
        mLowerJoints.eraseOne(it);
    }
}

// @ 0x487290
void cSPEditorLimbJoint::F_487290(cSPEditorLimbJoint* child)
{
    AddLowerJoint(child);
    cSPVector3 t1 = mTargetPosition + child->mTargetOffset;
    cSPVector3 t2 = mOriginalPosition + child->mOriginalOffset;
    child->Move(t1 - child->mTargetPosition, true);
    child->Translate(t2 + child->mOriginalPosition);
}

// @ 0x4873d0
float cSPEditorLimbJoint::GetLength()
{
    cSPEditorLimbJoint* p = mUpperJoint;
    if (!p) p = this;
    float a = (float)p->Sign(false);
    float av = p->mTargetPosition[0];
    if (Abs(av) < 0.001f) a = 0.0f;
    float b = (float)this->Sign(false);
    float bv = mTargetPosition[0];
    if (Abs(bv) < 0.001f) b = 0.0f;
    if (a != b && a != 0.0f) b = a;
    return b;
}

// @ 0x4874c0
int cSPEditorLimbJoint::Sign(bool recurse)
{
    float v = mTargetPosition[0];
    int sign = (int)SignOf(v);
    if (recurse && sign == 0 && !mLowerJoints.empty()) {
        cSPVector3 d = mLowerJoints[0]->mTargetPosition - mTargetPosition;
        sign = (int)SignOf(d[0]);
        if (sign == 0) {
            for (int i = 0, n = mLowerJoints.size(); i < n; i++) {
                int r = mLowerJoints[i]->Sign(recurse);
                if (r != 0) { sign = r; break; }
            }
        }
    }
    return sign;
}

// @ 0x4876b0
int cSPEditorLimbJoint::SignFromBlock(bool recurse)
{
    float v = mJointBlock->mPosition[0];
    int sign = (int)SignOf(v);
    if (recurse && sign == 0 && !mLowerJoints.empty()) {
        cSPVector3 d = mLowerJoints[0]->mJointBlock->mPosition - mJointBlock->mPosition;
        sign = (int)SignOf(d[0]);
    }
    return sign;
}

}  // namespace SP
