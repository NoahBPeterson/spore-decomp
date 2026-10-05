// Slice s0049de30: SP editor block transform helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

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
struct cSPEditorBlock {
    virtual void _v0();
    char pad0[0x48 - 4];
    cSPVector3 mPosition;                        // +0x48
};

// ---- helpers ----
void FUN_4942b0(cSPEditorBlock* block, float* out, uint32_t scale, cSPVector3 pos, int a, int b);  // @ 0x4942b0
cSPMatrix3 FUN_49e880(cSPEditorBlock* block, cSPMatrix3 m);                                       // @ 0x49e880

// @ 0x49ec40
void FUN_49ec40(cSPEditorBlock* block, float* out, uint32_t scale, cSPMatrix3* mat, bool flag)
{
    if (flag) {
        FUN_4942b0(block, out, scale, block->mPosition, 1, 0);
        *mat = FUN_49e880(block, *mat);
    }
    out[0] = 0.0f;
}

// @ 0x49de30
void FUN_49de30(cSPEditorBlock* block) { (void)block; }

// @ 0x49e6a0
void SetBlockScale(cSPEditorBlock* block, float scale, bool a, bool b) { (void)block; (void)scale; (void)a; (void)b; }

// @ 0x49e880
cSPMatrix3 FUN_49e880(cSPEditorBlock* block, cSPMatrix3 m) { (void)block; return m; }
