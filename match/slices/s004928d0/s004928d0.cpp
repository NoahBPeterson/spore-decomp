// Slice s004928d0 (batch w1g0, slice 89), 0x004928d0..0x0049363b.
// /Od editor-region code.

#include <math.h>
#include "types.h"

struct Vector3 {
    float x, y, z;
    float operator[](int i) const { return (&x)[i]; }
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

struct BoundingBox {
    Vector3 mn;
    Vector3 mx;
};

struct cSPEditorBlock {
    char pad0[0x48];
    Vector3 position;                     // 0x48
    char pad1[0x33c - 0x54];
    void* tracker;                        // 0x33c
    BoundingBox* GetBBox(BoundingBox* out, int a, int b, int c);
};

Vector3* Vector3_Sub(Vector3* out, const Vector3* a, const Vector3* b);

extern float g_492de0_limit;

// @ 0x00492de0
bool FUN_00492de0(cSPEditorBlock* p) {
    cSPEditorBlock* t1 = (cSPEditorBlock*)p->tracker;
    if (t1 == 0)
        return false;
    cSPEditorBlock* t2 = (cSPEditorBlock*)p->tracker;
    BoundingBox bb;
    t2->GetBBox(&bb, 0, 0, 0);
    float dz = bb.mx[2] - p->position[2];
    float ad = (float)fabs(dz);
    if (g_492de0_limit > ad)
        return true;
    return false;
}

// @ 0x004935f0
struct S935 {
    Vector3 a;
    Vector3 b;
    Vector3 Sub() const;
};

Vector3 S935::Sub() const {
    Vector3 p30;
    Vector3* t29 = Vector3_Sub(&p30, &b, &a);
    return *t29;
}

// ---- large functions: reconstructed skeletons (partial) ---------------------
float FUN_00492e70_proto(int p, float* a, float* b, int* c, float d, char e);

// @ 0x004928d0
void FUN_004928d0(cSPEditorBlock* p, int a, int b, int c) {
    if (p == 0)
        return;
    BoundingBox bb;
    p->GetBBox(&bb, 0, 0, 0);
    (void)a;
    (void)b;
    (void)c;
}

// @ 0x00492e70
float FUN_00492e70(int p, float* a, float* b, int* c, float d, char e) {
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)e;
    if (p == 0)
        return -1.0f;
    return -1.0f;
}

// @ 0x004934d0
void FUN_004934d0(int p) {
    (void)p;
}
