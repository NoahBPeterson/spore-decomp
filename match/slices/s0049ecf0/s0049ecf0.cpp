// Slice s0049ecf0: SP editor bone/limb helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---- math value types (rw::math::fpu instantiations; out-of-line copy ctors) ----
struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v);                 // @ 0x4098a0
};
struct Matrix33T {
    Vector3T xAxis, yAxis, zAxis;
    Matrix33T() {}
    Matrix33T(const Matrix33T& m);               // @ 0x41cb40
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) : Vector3T(v) {}
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPMatrix3 : Matrix33T {
    cSPMatrix3() {}
    cSPMatrix3(const cSPMatrix3& m) : Matrix33T(m) {}
    cSPMatrix3& operator=(const Matrix33T& m) { Matrix33T::operator=(m); return *this; }
};
template<typename T> struct LimbVec {
    T* b; T* e; T* c; int allocPair[2];
    LimbVec() { b = 0; e = 0; c = 0; }
    T* operator[](int i) { return b + i; }
};
struct cSPEditorBlock {
    virtual void _v0();
    char pad0[0x48 - 4];
    cSPVector3 mPosition;                        // +0x48
    char pad1[0xa8 - 0x54];
    cSPMatrix3 mTorsoMat;                        // +0xa8
    void SetPosition(const cSPVector3& v, bool b);   // @ 0x448e90
    void SetOrientation(const cSPMatrix3& m, bool b); // @ 0x449420
};

// ---- helpers ----
struct cSomeTracker {
    void AddVector(const cSPVector3& v);       // @ 0x44d4f0
};

Matrix33T M33_Transpose(const Matrix33T& m);                              // @ 0x41ded0
Matrix33T operator*(const Matrix33T& a, const Matrix33T& b);              // @ 0x41de20
Vector3T operator*(const cSPVector3& v, const Matrix33T& m);              // @ 0x41daf0
Vector3T operator-(const Vector3T& a, const Vector3T& b);                 // @ 0x41db10
Vector3T operator+(const Vector3T& a, const Vector3T& b);                 // @ 0x41dc10

// @ 0x49ef80
void FUN_49ef80(cSomeTracker* self, cSPVector3* vecs)
{
    for (int i = 0; i < 3; i++) {
        self->AddVector(vecs[i]);
    }
    ScratchSlots<4>();
}

// @ 0x49ecf0
void FUN_49ecf0(cSPEditorBlock* block, LimbVec<cSPEditorBlock*>* blocks,
                cSPVector3 pos, cSPMatrix3 mat)
{
    cSPMatrix3 savedTorso(block->mTorsoMat);
    cSPVector3 basePos(block->mPosition);
    cSPMatrix3 rot(block->mTorsoMat);
    cSPMatrix3 basis;
    rot = M33_Transpose(rot);
    basis = rot * mat;
    block->SetPosition(pos, true);
    block->SetOrientation(mat, true);
    int n = (int)(blocks->e - blocks->b);
    for (int i = 0; i < n; i++) {
        cSPVector3 offset;
        offset = (*(*blocks)[i])->mPosition - basePos;
        cSPVector3 childPos;
        childPos = basePos + offset * basis;
        cSPMatrix3 childMat;
        childMat = (*(*blocks)[i])->mTorsoMat * basis;
        (*(*blocks)[i])->SetOrientation(childMat, true);
        (*(*blocks)[i])->SetPosition(childPos, true);
    }
    (void)savedTorso;
}
