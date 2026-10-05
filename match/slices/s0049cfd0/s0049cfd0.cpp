// Slice s0049cfd0: SP editor transform/scale helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---- math types ----
struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Matrix33T {
    Vector3T xAxis, yAxis, zAxis;
    Matrix33T() {}
    Matrix33T(const Matrix33T& m) : xAxis(m.xAxis), yAxis(m.yAxis), zAxis(m.zAxis) {}
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
    cSPVector3& operator=(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPMatrix3 : Matrix33T {
    cSPMatrix3() {}
    cSPMatrix3(const Matrix33T& m) : Matrix33T(m) {}
};
struct cSPTransform {
    unsigned short mFlags;
    unsigned short mModificationCount;
    cSPVector3 mTranslation;
    float mScale;
    cSPMatrix3 mRotation;
    void TransformVector(cSPVector3* out);   // @ 0x49d640
};

struct cSPEditorBlock {
    virtual void _v0();
    char pad0[0x1e0 - 4];
    float mMinUniformScale;                  // +0x1e0
    float mMaxUniformScale;                  // +0x1e4
    void SetUniformScale(float v, int flag); // @ 0x440090
};

// ---- helpers ----
cSPVector3 operator*(const cSPVector3& v, const cSPMatrix3& m);   // @ 0x41daf0
void ScaleVector(cSPVector3* v, const float& s);                  // @ 0x41dba0

// @ 0x49d640
void cSPTransform::TransformVector(cSPVector3* out)
{
    if (mFlags & 2) {
        *out = *out * mRotation;
    }
    ScaleVector(out, mScale);
}

// @ 0x49dca0
float ClampAndSetScale(cSPEditorBlock* block, float value, bool clamp)
{
    if (clamp) {
        float tmp = block->mMinUniformScale;
        if (tmp > value) value = block->mMinUniformScale;
        float t14 = block->mMaxUniformScale;
        if (value > t14) value = block->mMaxUniformScale;
    }
    block->SetUniformScale(value, 0);
    return value;
}

// ---- remaining slice functions (not yet reconstructed) ----
// @ 0x49cfd0
void FUN_49cfd0(cSPEditorBlock* block) { (void)block; }

// @ 0x49d1f0
void FUN_49d1f0(cSPEditorBlock* block, float scale, bool a, bool b) { (void)block; (void)scale; (void)a; (void)b; }

// @ 0x49d390
void FUN_49d390(cSPEditorBlock* block) { (void)block; }

// @ 0x49d550
void FUN_49d550(cSPEditorBlock* block) { (void)block; }

// @ 0x49dd20
bool FUN_49dd20(cSPEditorBlock* block, void* param, bool b) { (void)block; (void)param; (void)b; return false; }

// @ 0x49d6b0
void FUN_49d6b0(cSPEditorBlock* block) { (void)block; }
