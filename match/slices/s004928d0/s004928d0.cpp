// Slice s004928d0 (batch w1g0, slice 89), 0x004928d0..0x0049363b.
// /Od editor-region code.
// Flags for 0x00492e70: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /GS- /Oi

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

// ---- 0x00492e70 support types (shared /Od editor-region flavours; see slices s004974e0/s0049efc0) --------
struct Vec3O {                                   // rw::math::fpu::Vector3Template<float,0>: out-of-line copy ctor
    float v[3];
    Vec3O(const Vec3O& o);                       // 0x004098a0
    float& operator[](int i) { return v[i]; }
    float operator[](int i) const { return v[i]; }
};
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& src) { Assign(&src); }
    void Assign(const Matrix3* src);             // 0x0041cb40
};
struct Vec3W {                                  // Vector3 with inline movss copy + writable operator[]
    float x, y, z;
    Vec3W() {}
    Vec3W(const Vec3W& o) : x(o.x), y(o.y), z(o.z) {}
    float& operator[](int i) { return (&x)[i]; }
    float operator[](int i) const { return (&x)[i]; }
};
struct Vec3P { float x, y, z; };                 // plain POD triple (integer-register copies)

Vec3W* Vec_Sub(Vec3W* out, const Vec3W* a, const Vec3W* b);     // 0x0041db10
Vec3W* Vec_Sub(Vec3W* out, const Vec3O* a, const Vec3W* b);
Vec3W* Vec_Add(Vec3W* out, const Vec3W* a, const Vec3W* b);     // 0x0041dc10
Vec3W* Vec_MulMat(Vec3W* out, const Vec3W* v, const Matrix3* m);   // 0x0041daf0
Matrix3* Mat_Inverse(Matrix3* out, const Matrix3* m);                    // 0x0041ded0
float VectorLength(Vec3W* v);                                          // 0x0040ae50

struct cSPEditorBlock2;
struct BBox2 { Vec3P mn, mx; };                  // 24 bytes
struct cSPEditorBlock2 {
    char pad0[0x48];
    Vec3W position;                            // +0x48
    char pad54[0x60 - 0x54];
    Matrix3 rotation;                            // +0x60 (36 bytes)
    char pad1[0x33c - 0x84];
    cSPEditorBlock2* parent;                     // +0x33c
    char pad2[0xdc8 - 0x340];
    uint32_t bits[2];                            // +0xdc8 bitset<60>
    bool TestBit(unsigned i) const {
        if (i < 0x3c) {
            uint32_t w = bits[i >> 5];
            return (w & (1u << (i % 32))) != 0;
        }
        return false;
    }
    BBox2* GetBBox(BBox2* out, int a, int b, int c);                     // 0x0044ae00
    void FUN_0043d240(Vec3W* out, int a);                              // 0x0043d240 (ret 8)
    int  FUN_0044e800();                                                 // 0x0044e800
    int  FUN_0044d9e0(Vec3W pos, float radius);                        // 0x0044d9e0 (ret 0x10)
    bool FUN_00438440(cSPEditorBlock2* other, int flag);                 // 0x00438440 (ret 8)
};

// 0x004928d0 (cdecl): compute the snapped position/orientation for snap index `idx`
void Snap_004928d0(cSPEditorBlock2* blk, Vec3W pos, Matrix3 rot, Vec3W* outPos, Matrix3* outRot, int idx);

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


// @ 0x00492e70  (cdecl) find the best snap of block p against its parent block: returns the snap
// distance (-1.0f when none), writes the snapped position/orientation and the snap index.
float FUN_00492e70(cSPEditorBlock2* p, Vec3W* outPos, Matrix3* outRot, int* outIdx, float scale, char flag) {
    cSPEditorBlock2* t1 = p->parent;
    if (t1 != 0) {
    cSPEditorBlock2* t2 = p->parent;
    cSPEditorBlock2* blk = t2;
    Vec3O pos(*(const Vec3O*)&p->position);
    Matrix3 rot(p->rotation);
    BBox2 bb;
    blk->GetBBox(&bb, 0, 0, 0);
    Vec3W center;
    blk->FUN_0043d240(&center, 0);
    Vec3O a(*(const Vec3O*)&bb.mn);
    Vec3O b(*(const Vec3O*)&bb.mx);
    float dx = b[0] - a[0];
    float dy = b[1] - a[1];
    float len = (float)sqrt(dy * dy + dx * dx);
    float scaled = len * 0.08f * scale;

    Matrix3 invRot;
    Vec3W tSub, tMul;
    Vec3W vl(*Vec_MulMat(&tMul, Vec_Sub(&tSub, &pos, &blk->position), Mat_Inverse(&invRot, &blk->rotation)));
    float ex = vl[0] - center[0];
    float ey = vl[1] - center[1];
    float dist = (float)sqrt(ey * ey + ex * ex);

    Vec3W best(*(Vec3W*)&pos);
    float bestD = -1.0f;
    if (flag && scaled > dist) {
        vl[0] = center[0];
        vl[1] = center[1];
        Vec3W tMul2, tAdd;
        best = *Vec_Add(&tAdd, Vec_MulMat(&tMul2, &vl, &blk->rotation), &blk->position);
        bestD = dist;
    }

    float second = -1.0f;
    Vec3W cand(*(Vec3W*)&pos);
    Matrix3 candRot(rot);
    int n = blk->FUN_0044e800();
    if (n > 0) {
        int idx = blk->FUN_0044d9e0(*(Vec3W*)&pos, scaled * 0.25f);
        if (idx != -1) {
            Snap_004928d0(blk, *(Vec3W*)&pos, rot, &cand, &candRot, idx);
            Vec3W tDiff;
            Vec3W diff(*Vec_Sub(&tDiff, (Vec3W*)&pos, &cand));
            second = VectorLength(&diff);
            *outIdx = idx;
        }
    }

    if (p->TestBit(0x1c) && bestD != -1.0f && p->FUN_00438440(p->parent, 0x1c)) {
        *(Vec3P*)outPos = *(Vec3P*)&best;
        *outIdx = -1;
        return bestD;
    }
    if (p->FUN_00438440(p->parent, 0x1d) && p->TestBit(0x1d) && second != -1.0f) {
        *(Vec3P*)outPos = *(Vec3P*)&cand;
        *outRot = candRot;
        return second;
    }
    return -1.0f;
    }
    return -1.0f;
}

// @ 0x004934d0
void FUN_004934d0(int p) {
    (void)p;
}
