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

// ---- 0x004928d0 support types (retail layout: position +0x48, orientation +0x60) ----
struct Vec3N { float x, y, z; };                 // plain triple

struct Blk {
    char pad0[0x48];
    Vec3N mPosition;                            // +0x48
    char pad1[0x60 - 0x54];
    Matrix3 mOrientation;                       // +0x60
    int Count();                                // 0x0044e800
    void GetBBox(void* out, int a, int b, int c);   // 0x0044ae00
    void Corner(Vec3N* out, int a);             // 0x0043d240 (ret 8)
    void GetBounds(Vec3N* out, unsigned index); // 0x0044d8f0 (ret 8)
};

Vec3N g_v492b24;                                // 0x015d6324 dummy third argument
Vec3N* Cross(Vec3N* out, const Vec3N* a, const Vec3N* b);            // 0x0044e460
Vec3N* ProjPerp(Vec3N* out, const Vec3N* a, const Vec3N* b);         // 0x004909d0
void UpdateModel(void* obj);                    // 0x004ae250
Matrix3* BuildFrame(Matrix3* out, Vec3N v0, Vec3N v1, Vec3N v2, Vec3N v3, Vec3N v4);  // 0x004906e0

// @ 0x004928d0
void FUN_004928d0(Blk* p, Vec3W pos, Matrix3 rot, Vec3W* outPos, Matrix3* outRot, int idx) {
    void* bb[6];
    p->GetBBox(bb, 0, 0, 0);
    outPos->x = pos.x;
    outPos->y = pos.y;
    outPos->z = pos.z;
    *outRot = rot;
    int n = p->Count();

    if (idx == -1) {
        Vec3N corner;
        p->Corner(&corner, 0);
        Matrix3 inv;
        Mat_Inverse(&inv, &rot);
        Vec3W sub;
        Vec3W* r1 = Vec_Sub(&sub, (const Vec3W*)&p->mPosition, (const Vec3W*)&pos);
        Vec3W* r2 = Vec_MulMat((Vec3W*)0, r1, &inv);
        Vec3W term;
        term.x = corner.x;
        term.y = corner.y;
        term.z = r2->x;
        {
            Vec3W tgt;
            tgt.x = r2->x; tgt.y = r2->y; tgt.z = r2->z;
            tgt.x = corner.x;
            tgt.y = corner.y;
            term.x = tgt.x; term.y = tgt.y;
        }
        Vec3W* r3 = Vec_Add((Vec3W*)0, &term, (const Vec3W*)&p->mPosition);
        outPos->x = r3->x;
        outPos->y = r3->y;
        outPos->z = r3->z;
        return;
    }

    if (idx >= 0 && idx < n) {
        Matrix3 localRot;
        localRot.Assign(&rot);
        Vec3W sub;
        Vec3W* r1 = Vec_Sub(&sub, (const Vec3W*)&pos, (const Vec3W*)&p->mPosition);
        Vec3W rel; rel.x = r1->x; rel.y = r1->y; rel.z = r1->z;
        Matrix3 inv;
        Mat_Inverse(&inv, &localRot);
        Vec3W r2;
        {
            Vec3W* p2 = Vec_MulMat(&r2, &rel, &inv);
            (void)p2;
        }
        Vec3W snapped;
        p->GetBounds((Vec3N*)&snapped, (unsigned)idx);
        Vec3W rs;
        Vec3W* rr = Vec_Sub(&rs, &r2, &snapped);
        Vec3N e2l; e2l.x = rr->x; e2l.y = rr->y; e2l.z = rr->z;
        Vec3N cross;
        Cross(&cross, (const Vec3N*)&snapped, &g_v492b24);
        Vec3N proj;
        ProjPerp(&proj, &e2l, &cross);
        Vec3W sr;
        Vec3W* srr = Vec_Add(&sr, (const Vec3W*)&proj, (const Vec3W*)&snapped);
        Vec3N term; term.x = srr->x; term.y = srr->y; term.z = srr->z;
        term.z = snapped.z;
        Vec3W fr;
        Vec3W* frr = Vec_Add(&fr, (const Vec3W*)&term, (const Vec3W*)&p->mPosition);
        outPos->x = frr->x;
        outPos->y = frr->y;
        outPos->z = frr->z;

        Vec3W row3;
        row3.x = localRot.m[6]; row3.y = localRot.m[7]; row3.z = localRot.m[8];
        Vec3W l2;
        {
            Vec3W* pl = Vec_MulMat(&l2, &row3, &localRot);
            (void)pl;
        }
        Vec3N l3; l3.x = l2.x; l3.y = l2.y; l3.z = snapped.z;
        Matrix3 built;
        BuildFrame(&built, *(Vec3N*)&pos, *(Vec3N*)&rel, *(Vec3N*)&snapped, l3, *(Vec3N*)&l2);
        *outRot = built;
        UpdateModel(0);
    }
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
struct cSPEditorModel934 {
    bool UsingSymmetry();             // 0x004adc40
    void SetUsingSymmetry(bool v);    // 0x004adc20 (ret 4)
    unsigned GetBlockCount();         // 0x004accf0
    Blk* GetBlock(unsigned i);        // 0x004accb0
};
struct Blk934 {
    char pad0[0x48];
    Vec3N pos;                        // +0x48
    Vec3N historyPos;                 // +0x54
    void SetPosition934(const Vec3N* p, bool b);   // 0x00448e90 (ret 8)
};
Vec3N g_v492d64d8;                    // 0x015d64d8
bool Vector3_NotEqual(const Vec3N* a, const Vec3N* b);  // 0x0041dd30
bool BlockBlocked(Blk* b);                  // 0x004a7e60

// @ 0x004934d0
void FUN_004934d0(cSPEditorModel934* model, Vec3N pos, unsigned char flag) {
    if (Vector3_NotEqual(&pos, &g_v492d64d8)) {
        if (model != 0) {
            bool saved = model->UsingSymmetry();
            model->SetUsingSymmetry(false);
            int count = (int)model->GetBlockCount();
            for (int i = 0; i < count; i++) {
                Blk934* blk = (Blk934*)model->GetBlock(i);
                if (flag && !BlockBlocked((Blk*)blk))
                    continue;
                Vec3W r;
                Vec3W* p = Vec_Add(&r, (const Vec3W*)&blk->pos, (const Vec3W*)&pos);
                Vec3N p2; p2.x = p->x; p2.y = p->y; p2.z = p->z;
                blk->SetPosition934(&p2, true);
                blk->historyPos = blk->pos;
            }
            model->SetUsingSymmetry(saved);
        }
    }
}
