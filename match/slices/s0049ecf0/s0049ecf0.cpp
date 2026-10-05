// Slice s0049ecf0: SP editor bone/limb helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
};
struct cSPEditorBlock {
    virtual void _v0();
};

// ---- helpers ----
struct cSomeTracker {
    void AddVector(const cSPVector3& v);       // @ 0x44d4f0
};

// @ 0x49ef80
void FUN_49ef80(cSomeTracker* self, cSPVector3* vecs)
{
    for (int i = 0; i < 3; i++) {
        self->AddVector(vecs[i]);
    }
    ScratchSlots<4>();
}

// @ 0x49ecf0
void FUN_49ecf0(cSPEditorBlock* block) { (void)block; }
