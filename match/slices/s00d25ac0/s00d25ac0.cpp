// FUN_00d266c0 (0x00d266c0): builds a cSPTransform from a translation (flags |= 4, modification
// count + 1, scale 1, identity rotation), accumulates it onto the target transform and stores the
// result back into the target.
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }

struct Vector3 {  // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
};

struct cSPVector3 : Vector3 {};

struct Matrix3 {  // rw::math::fpu::Matrix33Template<float,0>, size 0x24
    Vector3 xAxis;  // +0x00
    Vector3 yAxis;  // +0x0c
    Vector3 zAxis;  // +0x18
    Matrix3() {}
    Matrix3(const Matrix3& other);  // 0x0041cb40 (out of line copy ctor)
};

extern const Matrix3 kIdentityMatrix;  // 0x0169df20

struct cSPTransform {  // size 0x38
    uint16_t mFlags;              // +0x00
    uint16_t mModificationCount;  // +0x02
    cSPVector3 mTranslation;      // +0x04
    float mScale;                 // +0x10
    Matrix3 mRotation;            // +0x14
    cSPTransform& operator=(const cSPTransform& other);  // 0x00537dc0
    void Accumulate(const cSPTransform& other);          // 0x0040ccb0 (Modifier::Accumulate)
};

void BuildTransformFromTranslation(cSPTransform* pTarget, const cSPVector3* pTranslation) {
    cSPTransform t;
    t.mModificationCount = 0;
    t.mFlags = 0;
    t.mScale = 1.0f;
    new (&t.mRotation) Matrix3(kIdentityMatrix);
    t.mTranslation = *pTranslation;
    t.mFlags = t.mFlags | 4;
    t.mModificationCount = t.mModificationCount + 1;
    cSPTransform out;
    out.mFlags = t.mFlags;
    out.mModificationCount = t.mModificationCount;
    out.mTranslation = t.mTranslation;
    out.mScale = t.mScale;
    new (&out.mRotation) Matrix3(t.mRotation);
    out.Accumulate(*pTarget);
    *pTarget = out;
}
