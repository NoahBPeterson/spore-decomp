// Slice 12: nSPSkinner paint-renderer helpers and the big render-job entry.
// Unoptimized editor module: flags /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// @ 0x00523690 -- render-job teardown (defined below, after the object layout)
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
struct cMeshPos9 {                                           // POD: tri + uv
    uint32_t tri;
    Vector2 uv;
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
    void Lookup(void* src, int b, int* outTri, Vector2* outUV, int d, int e);   // 0x0050bff0
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
    uint32_t pad24[(0x3c - 0x24) / 4];
    void*  mCtx3c;                               // +0x3c  cleared by FUN_00525f40
    void*  mHitBase;                             // +0x40  HitRec9 base (record at -0x38)
    uint32_t pad44[(0x54 - 0x44) / 4];
    uint32_t mSeed;                              // +0x54

    float NextRandom();                          // 0x005169d0
    void BuildHit(HitRec9* out, Param9* p, cMeshPos9 pos, uint32_t seed);
};

unsigned FUN_00520110(Pal9* p, unsigned v);                          // 0x00520110
void FUN_0051fb90(uint8_t mode, void* blob, cMeshPos9 pos, Param9* p, Pal9* pal, Mesh9* mesh, cSPVector39* out);
void FUN_00520140(cSPVector39* n, cSPVector39* d, Vec3Pod* outA, Vec3Pod* outB);   // 0x00520140

// ---------------------------------------------------------------------------
// Callees of the render-job teardown at 0x00523690 and its two helpers.
// Declared __fastcall so the implicit ecx `this` matches the original thiscall;
// pairs of stack arguments arrive as a small by-value block.
// ---------------------------------------------------------------------------
struct Pair9 { void* a; void* b; };
// FixedAllocatorBase::Init's 8 stack words: blockSize, arg, count, arg, arg,
// allocFn, freeFn, arg.
struct InitArgs9 {
    uint32_t blockSize; uint32_t w1; uint32_t count; uint32_t w3; uint32_t w4;
    void*    allocFn;   void*    freeFn; uint32_t w7;
};

int  __fastcall ContinueJob(void* job);                   // 0x0068f970  cJob::ContinueJob
bool __fastcall CancelJob(void* job, Pair9 pad);          // 0x00692400  SP::cJob::Cancel
void __fastcall SkinJob_Clear(void* slot);                // 0x0051aaa0  SkinJob::FUN_0051aaa0
void __fastcall VectorIF_erase(void* self, Pair9 range);  // 0x00530c80  VectorIF::erase
void __fastcall FUN_005266f0(void* self, Pair9 range);    // 0x005266f0
void __fastcall FUN_009265b0(void* alloc);                // 0x009265b0
bool __fastcall FixedAllocatorBase_Init(void* alloc, InitArgs9 a);   // 0x009266b0
void __fastcall FUN_005123b0(void* p);                    // 0x005123b0
void __fastcall FUN_00507230(void* self, Pair9 range);    // 0x00507230
void __fastcall FUN_005066d0(void* p);                    // 0x005066d0
void __fastcall FUN_00525f40(void* p);                    // 0x00525f40 (ecx = p, no stack args)
void FUN_0050bff0(void* src, int b, int* outTri, Vector2* outUV, int d,
                  int e);                                 // 0x0050bff0 (Mesh9::Lookup, 6 stack args)

extern void* gFixedAlloc_s00523690;                       // 0x015de2a0
void* FUN_00541600(unsigned size, void* p);               // 0x00541600
void  FUN_00541660(void* p, void* q);                     // 0x00541660

// The render-job object (0x100+ bytes) touched by the teardown.
struct CtxSub9 {                                             // sub-object at ctx+0x3c
    uint32_t m00;
    void*    m04;                                        // +0x04
    void*    m08;                                        // +0x08
    uint32_t m0c;                                        // +0x0c
};
struct CtxBody9 {                                            // object at job+0x0c
    uint8_t  pad00[0x08];
    void*    m08;                                        // +0x08
    void*    m0c;                                        // +0x0c
    uint8_t  pad10[0x3c - 0x10];
    CtxSub9  m3c;                                        // +0x3c
};
struct SkinJob9 {
    uint8_t  pad00[0x0c];
    void*    mCtx;                                       // +0x0c  CtxBody9*
    uint8_t  pad10[0x18 - 0x10];
    void*    m18;                                        // +0x18
    uint8_t  pad1c[0x3c - 0x1c];
    void*    m3c[2];                                     // +0x3c / +0x40  (range erased by 0x5266f0)
    uint8_t  pad44[0x50 - 0x44];
    uint32_t m50;                                        // +0x50
    uint32_t m54;                                        // +0x54
    uint32_t m58;                                        // +0x58
    uint32_t m5c;                                        // +0x5c
    uint8_t  m60;                                        // +0x60
    uint8_t  m61;                                        // +0x61
    uint8_t  m62;                                        // +0x62
    uint8_t  pad63;
    uint32_t m64;                                        // +0x64
    uint8_t  pad68[0x94 - 0x68];
    void*    m94[2];                                     // +0x94 / +0x98  (VectorIF range)
    uint8_t  pad9c[0xec - 0x9c];
    uint32_t mec;                                        // +0xec
    void*    mf0;                                        // +0xf0  ref-counted, vcall +0xc(1), +4 release
    uint8_t  padf4[0xf8 - 0xf4];
    void*    mf8;                                        // +0xf8  cJob
    void*    mfc;                                        // +0xfc  cJob
};

// Ctx9 (already declared above) needs the members used by the two helpers.
// The two small helpers are methods on the same object as BuildHit.

// Job state mask: bit (ret & 31) of 0x3c (bits 2..5).  Materialised as a bool so
// the emitted code keeps the neg/sbb/neg zero-test sequence.
static inline bool JobStateBit(int r) { return ((1u << (r & 0x1f)) & 0x3cu) != 0; }

// @ 0x00523690 -- render-job teardown / cancel-on-demand.
void __fastcall FUN_00523690(SkinJob9* self)
{
    if (self->mf8 != 0) {
        void* j = self->mf8;
        if (JobStateBit(ContinueJob(j)))
            CancelJob(self->mf8, Pair9());
    }
    if (self->mfc != 0) {
        void* j = self->mfc;
        if (JobStateBit(ContinueJob(j)))
            CancelJob(self->mfc, Pair9());
    }
    if (self->m60 != 0) {
        SkinJob_Clear(self->m18);
        self->m60 = 0;
    }
    if (self->mf0 != 0) {
        (*(void (__thiscall**)(void*, int))(*(uint32_t*)self->mf0 + 0xc))(self->mf0, 1);
        if (self->mf0 != 0) {
            void* held = self->mf0;
            self->mf0 = 0;
            if (held != 0)
                (*(void (__thiscall**)(void*))(*(uint32_t*)held + 4))(held);
        }
    }
    Pair9 range94;
    range94.a = self->m94[0];
    range94.b = self->m94[1];
    VectorIF_erase(&self->m94, range94);
    self->mec = 0;
    Pair9 range3c;
    range3c.a = self->m3c[0];
    range3c.b = self->m3c[1];
    FUN_005266f0(&self->m3c, range3c);
    self->m50 = 0;
    self->m5c = 0;
    FUN_009265b0(&gFixedAlloc_s00523690);
    InitArgs9 init = { 0x50, 0, 0xc8, 0, 0, &FUN_00541600, &FUN_00541660, 0 };
    FixedAllocatorBase_Init(&gFixedAlloc_s00523690, init);
    CtxBody9* ctx = (CtxBody9*)self->mCtx;
    FUN_005123b0(ctx->m08);                              // ctx + 0x08
    FUN_005123b0(ctx->m0c);                              // ctx + 0x0c
    Pair9 subRange;
    subRange.a = ctx->m3c.m04;                           // sub + 0x04
    subRange.b = ctx->m3c.m08;                           // sub + 0x08
    FUN_00507230(&ctx->m3c, subRange);
    ctx->m3c.m0c = 0;                                    // sub + 0x0c
    FUN_005066d0(self->mCtx);
    self->m61 = 0;
    self->m62 = 0;
    self->m64 = 0;
}

// Arguments of the hit builder as a single by-value block, so the pointer
// parameters land on the stack exactly as the original thiscall does
// (p at [ebp+8], pos.tri at [ebp+0xc], seed at [ebp+0x18]).
struct HitBuildArgs9 {                                       // 0x14 bytes
    Param9*   p;                                             // +0x00
    cMeshPos9 pos;                                           // +0x04
    uint32_t  seed;                                          // +0x10
};

// @ 0x005240e0 -- build a hit record for one (tri, uv) mesh position.
void __fastcall FUN_005240e0(Ctx9* self, HitBuildArgs9 args)
{
    FUN_00525f40(&self->mCtx3c);
    HitRec9* out = (HitRec9*)((char*)self->mHitBase - 0x38);
    self->BuildHit(out, args.p, args.pos, args.seed);
}

// Caller-supplied blob forwarded to Mesh9::Lookup (its first dword also carries
// the Param9* handed on to the hit builder).
struct HitLookupArgs9 {                                      // 0x14 bytes
    Param9*  p;                                              // +0x00
    uint32_t src[3];                                         // +0x04  (opaque lookup input)
    uint32_t seed;                                           // +0x10
};

// @ 0x00524150 -- look up a mesh position for a parameter point, then build the hit.
void __fastcall FUN_00524150(Ctx9* self, HitLookupArgs9 args)
{
    int      tri = -1;
    Vector2  uv;                                             // filled by Lookup
    Mesh9*   mesh = self->mMesh;
    mesh->Lookup(&args.src, 0, &tri, &uv, 0, 0);
    if (tri != -1) {
        HitBuildArgs9 hb;
        hb.p = args.p;
        hb.pos.tri = (uint32_t)tri;
        hb.pos.uv = uv;
        hb.seed = args.seed;
        FUN_005240e0(self, hb);
    }
}

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

// @ 0x005240e0 and 0x00524150 are defined above (render-job hit helpers).
