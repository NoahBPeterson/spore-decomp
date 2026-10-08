// Slice 12: nSPSkinner paint-renderer helpers and the big render-job entry.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
//
// PARTIAL: the functions here pass Vector2/Vector3 structs by value through hand-built /Od stack
// temporaries and recurse into a 2012-byte render body; only entry skeletons are recorded.
#include "types.h"

// @ 0x00523690 -- PARTIAL skeleton (612-byte /Od body not reconstructed)
void FUN_00523690(void* self) { (void)self; }
// 0x00523900 -- ProcessHit-style hit record builder: derives a surface direction from the mode byte
// (case 3 stored vector, 4/6 matrix-rotated, 5 cross of tri normal and region axis, 7 midpoint frame),
// optionally negates it, then fills the output record.
struct cSPVector3R9 {
    float x, y, z;
    cSPVector3R9() {}
};
struct cSPVector39 {
    float x, y, z;
    cSPVector39() {}
    cSPVector39(const cSPVector3R9& o) : x(o.x), y(o.y), z(o.z) {}
    cSPVector39(const cSPVector39& o) : x(o.x), y(o.y), z(o.z) {}
    void operator=(const cSPVector3R9& o) { x = o.x; y = o.y; z = o.z; }
    void Assign(const cSPVector3R9& o);                      // 0x004098a0
};
struct cSPVector3C9 {
    float x, y, z;
    cSPVector3C9(const cSPVector3R9& o) : x(o.x), y(o.y), z(o.z) {}
    void Assign(const cSPVector3R9& o);                      // 0x004098a0
};
struct Mat39 { float m[9]; };
struct Vec3Pod { float x, y, z; };

cSPVector3R9 MulMat9(const cSPVector39& v, const Mat39& m);             // 0x0041daf0
cSPVector3R9 MulScalar9(const cSPVector39& v, const float& s);             // 0x0041dca0
cSPVector3R9 AddVec9(const cSPVector39& a, const cSPVector39& b);      // 0x0041dc10
cSPVector3R9 SubVec9(const cSPVector39& a, const cSPVector39& b);      // 0x0041db10
void MulAssign9(cSPVector39* a, const cSPVector39* b);                   // 0x0041dba0
void AddAssign9(cSPVector39* a, const cSPVector39* b);                   // 0x0041ddb0
cSPVector3R9 Cross9(const cSPVector39& a, const cSPVector39& b);         // 0x0044e460
cSPVector3R9 Normalize9(const cSPVector3R9& v);                          // 0x00436ce0
cSPVector3R9 Negate9(const cSPVector39& v);                              // 0x00422020
extern float kHalf9;                                                     // 0x01471064 (0.5f)
extern float kZero9;                                                     // 0x01485378 (0.0f)
extern float kScale9;                                                    // 0x013f1cac

struct Vector2 {
    float x, y;
    Vector2& operator=(const Vector2& o);                    // 0x0051fb60
};
struct cMeshPos9 {
    uint32_t tri;
    Vector2 uv;
    cMeshPos9(const cMeshPos9& o) : tri(o.tri) { uv = o.uv; }
};

struct Prim9 {                                   // 0x8c bytes
    uint32_t pad0[0x14 / 4];
    cSPVector39 vA;                              // +0x14
    cSPVector39 vB;                              // +0x20
    uint32_t pad2c;                              // +0x2c
    Mat39 rot;                                   // +0x30 (also holds the +0x3c axis vector)
};
struct Mesh9 {
    uint32_t pad0[0x190 / 4];
    uint32_t* mPacked;                           // +0x190
    cSPVector3R9 GetTriNormal(uint32_t tri);                  // 0x005121c0
    cSPVector3R9 GetPosition(cMeshPos9 p);                    // 0x0050c490
};
struct Tables9 {
    uint32_t pad0[0x98 / 4];
    char* mPrims;                                // +0x98
};
struct Pal9 {
    uint32_t pad0[8 / 4];
    Tables9* mTables;                            // +0x8
    uint32_t pad1[0x14 / 4];
    uint8_t* mByteMap;                           // +0x20
};
struct Param9 {
    uint32_t pad0[0x1c / 4];
    uint32_t mFlags;                             // +0x1c
    uint32_t pad20[(0x2c - 0x20) / 4];
    uint16_t pad2c;
    uint8_t mMode;                               // +0x2e
    uint8_t mSub;                                // +0x2f
    uint32_t pad30[(0x3c - 0x30) / 4];
    cSPVector39 mDir;                            // +0x3c
    uint32_t pad48[(0x58 - 0x48) / 4];           // +0x48 blob
    float mRngA0;                                // +0x58
    float mRngA1;                                // +0x5c
    float mRngB0;                                // +0x60
    float mRngB1;                                // +0x64
};
struct Sink9 {
    void Set(void* p);                           // 0x004535d0 AutoRefCount::operator=
};
struct HitRec9 {
    uint32_t posRaw[3];                          // +0x0
    Vec3Pod dir;                                 // +0xc
    float f18;                                   // +0x18
    uint32_t i1c;                                // +0x1c
    int i20;                                     // +0x20
    int i24;                                     // +0x24
    uint32_t i28;                                // +0x28
    Sink9 ref;                                   // +0x2c
    uint32_t i30;                                // +0x30
};
struct Ctx9 {
    uint32_t pad0[0x10 / 4];
    Mesh9* mMesh;                                // +0x10
    uint32_t pad14[(0x20 - 0x14) / 4];
    Pal9* mPal;                                  // +0x20
    uint32_t pad24[(0x54 - 0x24) / 4];
    uint32_t mSeed;                              // +0x54

    float NextRandom();                          // 0x005169d0
    void BuildHit(HitRec9* out, Param9* p, cMeshPos9 pos, uint32_t seed);
};

unsigned FUN_00520110(Pal9* p, unsigned v);                          // 0x00520110
void FUN_0051fb90(uint8_t mode, void* blob, cMeshPos9 pos, Param9* p, Pal9* pal, Mesh9* mesh, cSPVector39* out);
void FUN_00520140(cSPVector39* n, cSPVector39* d, Vec3Pod* outA, Vec3Pod* outB);   // 0x00520140

static inline unsigned UnpackIdx9(Pal9* p, unsigned v)
{
    if (v & 0x80000000u)
        return (unsigned)p->mByteMap[v & 0x7fffffffu];
    return v;
}
static inline const int& Max9(const int& a, const int& b) { return (a < b) ? b : a; }

// @ 0x00523900
void Ctx9::BuildHit(HitRec9* out, Param9* p, cMeshPos9 pos, uint32_t seed)
{
    mSeed = seed ^ 0x129c8901;
    Mesh9* mesh = mMesh;
    cSPVector3R9 nrm = mesh->GetTriNormal(pos.tri);
    cSPVector39 dir;
    switch (p->mMode) {
    case 0: case 1: case 2:
    default:
        FUN_0051fb90(p->mSub, (char*)p + 0x48, pos, p, mPal, mMesh, &dir);
        break;
    case 3:
        dir = p->mDir;
        break;
    case 4: {
        uint32_t v = (mesh->mPacked + pos.tri)[0] >> 16;
        Pal9* pal = mPal;
        Tables9* t = pal->mTables;
        Mat39* m = (Mat39*)(t->mPrims + FUN_00520110(pal, v) * 0x8c + 0x30);
        dir = MulMat9(p->mDir, *m);
        break;
    }
    case 5: {
        uint32_t v = (mesh->mPacked + pos.tri)[0] >> 16;
        Pal9* pal = mPal;
        Tables9* t = pal->mTables;
        char* e = t->mPrims + FUN_00520110(pal, v) * 0x8c + 0x30;
        cSPVector39 axis; axis.x = ((float*)(e + 0xc))[0]; axis.y = ((float*)(e + 0xc))[1]; axis.z = ((float*)(e + 0xc))[2];
        dir = Normalize9(Cross9(*(cSPVector39*)&nrm, axis));
        break;
    }
    case 6: {
        uint32_t v = ((mesh->mPacked + pos.tri)[0] >> 8) & 0xff;
        Pal9* pal = mPal;
        Tables9* t = pal->mTables;
        Mat39* m = (Mat39*)(t->mPrims + FUN_00520110(pal, v) * 0x8c + 0x30);
        dir = MulMat9(p->mDir, *m);
        break;
    }
    case 7: {
        uint32_t v = ((mesh->mPacked + pos.tri)[0] >> 8) & 0xff;
        unsigned idx = UnpackIdx9(mPal, v);
        Prim9* prim = (Prim9*)(mPal->mTables->mPrims + idx * 0x8c);
        float half = kHalf9;
        cSPVector3C9 c(MulScalar9(cSPVector39(AddVec9(prim->vA, prim->vB)), half));
        MulAssign9((cSPVector39*)&c, (cSPVector39*)((char*)prim + 0x2c));
        c.Assign(MulMat9(*(cSPVector39*)&c, prim->rot));
        AddAssign9((cSPVector39*)&c, (cSPVector39*)((char*)prim + 0x54));
        cSPVector39 d = SubVec9(mMesh->GetPosition(pos), *(cSPVector39*)&c);
        cSPVector39 axis(*(cSPVector39*)((char*)prim + 0x3c));
        dir = Normalize9(Cross9(d, axis));
        break;
    }
    }
    if (p->mFlags & 0x20)
        dir.Assign(Negate9(dir));
    Vec3Pod outA, outB;
    FUN_00520140((cSPVector39*)&nrm, &dir, &outA, &outB);
    out->posRaw[0] = *(uint32_t*)&pos.tri;
    out->posRaw[1] = ((uint32_t*)&pos)[1];
    out->posRaw[2] = ((uint32_t*)&pos)[2];
    out->dir = outA;
    out->f18 = kZero9;
    out->i1c = 0;
    out->i20 = -(int)(((p->mRngA1 - p->mRngA0) * NextRandom() + p->mRngA0) * kScale9);
    int b = (int)(((p->mRngB1 - p->mRngB0) * NextRandom() + p->mRngB0) * kScale9);
    out->i24 = Max9(1, b);
    out->i28 = seed;
    out->ref.Set(p);
    out->i30 = 0;
}

// @ 0x005240e0 -- PARTIAL skeleton (109 bytes: inline Vector2 stack temp + call)
void FUN_005240e0(void* self) { (void)self; }
// @ 0x00524150 -- PARTIAL skeleton (130 bytes: inline Vector2 stack temp + call)
void FUN_00524150(void* self) { (void)self; }
