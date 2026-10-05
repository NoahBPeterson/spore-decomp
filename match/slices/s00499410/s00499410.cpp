// Slice s00499410 (batch w1g0, slice 97), 0x00499410..0x0049a0be.
// /Od editor-region code. 0049a030 is a small reconstructed ray/plane helper;
// the others are large skeletons.

#include "types.h"

struct Vector3 { float x, y, z; };
struct Plane { float a, b, c, d; };

extern Vector3 g_15d64d8;
extern Vector3 g_15d6324;

void PlaneFromPointNormal(Plane* out, const Vector3* p, const Vector3* n);   // 0x44e510
bool IntersectRayPlane(const Vector3* o, const Vector3* d, const Plane* p, float* t); // 0x44e640
Vector3* Vector3_Scale(Vector3* out, const float* s, const Vector3* v);      // 0x41de40
Vector3* VectorAdd(Vector3* out, const Vector3* a, const Vector3* b);        // 0x41dc10

// @ 0x0049a030
bool FUN_0049a030(Vector3 origin, Vector3 dir, Vector3* out) {
    Plane p;
    PlaneFromPointNormal(&p, &g_15d64d8, &g_15d6324);
    float t;
    if (!IntersectRayPlane(&origin, &dir, &p, &t))
        return false;
    Vector3 sv;
    Vector3_Scale(&sv, &t, &dir);
    Vector3 r;
    VectorAdd(&r, &origin, &sv);
    *out = r;
    return true;
}

// @ 0x00499410
int FUN_00499410(void* p, void* a, void* b) {
    (void)p; (void)a; (void)b;
    return 0;
}

// @ 0x00499b40
void FUN_00499b40(void* p, void* a, void* b, void* c) {
    (void)p; (void)a; (void)b; (void)c;
}

// @ 0x00499f10
void FUN_00499f10(void* p, void* a, void* b) {
    (void)p; (void)a; (void)b;
}

// @ 0x0049a0c0
void FUN_0049a0c0(void* p, void* a, void* b) {
    (void)p; (void)a; (void)b;
}
