// Slice s0073e410 (0x0073e410-0x0073f2e0): SP::cModelInstance mesh/dispatch helpers.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar floats, EH frames).
#include "types.h"
#include <intrin.h>

// External callees (masked relocations).
extern "C" void  FUN_01201660();          // 0x1201660
extern "C" void  FUN_012016d0();          // 0x12016d0
extern "C" void  FUN_0073a6e0();          // 0x73a6e0
extern "C" void  FUN_006c1c80();          // 0x6c1c80
extern "C" void  FUN_007c5490();          // 0x7c5490
extern "C" void  FUN_01200940();          // 0x1200940
extern "C" void  FUN_00730210(int, int);  // 0x730210
extern "C" void  FUN_0072fff0(int, int);  // 0x72fff0
extern "C" void  FUN_0073bab0(void*);     // 0x73bab0
extern "C" void  FUN_00777bf0();          // 0x777bf0
extern "C" void  FUN_00777ae0();          // 0x777ae0
extern "C" void  FUN_007789d0();          // 0x7789d0
extern "C" void  FUN_00777c10();          // 0x777c10
extern "C" void  FUN_011f9710();          // 0x11f9710
extern "C" int   FUN_011f2bc0();          // 0x11f2bc0
void __cdecl Matrix3_Assign(void* dst, const void* src);   // 0x41cb40
void __cdecl SetShaderData();                              // 0x777b50
void __cdecl CompiledState_Dispatch();                     // 0x11ee580

// ---------------------------------------------------------------------------
// 16-byte-aligned Vector3 / AABB (used by the bounding-box overlap test).
// ---------------------------------------------------------------------------
struct Vec3A { float x, y, z, w; };
struct AABB  { Vec3A mn, mx; };

struct BBoxTest {
    AABB box;
    bool Test(const AABB* other);   // 0x73f110
};

// ---------------------------------------------------------------------------
// Refcounted object with the vtable at +0 and the refcount at +4.
// ---------------------------------------------------------------------------
struct RC {
    virtual void v0(int mode);
    virtual void v1();
    volatile int mnRefCount;         // +0x4
};

// Array element stride 0xc4, refcounted pointer at +0xc.
struct RCItem {
    char pad0[0xc];
    RC*  mpObject;                   // +0xc
    char pad10[0xb4];
};

// ---------------------------------------------------------------------------
// @ 0x0073f110  AABB overlap test (this <=> other).
// ---------------------------------------------------------------------------
bool BBoxTest::Test(const AABB* other)
{
    if (box.mn.x <= other->mx.x)
        if (other->mn.x <= box.mx.x)
            if (box.mn.y <= other->mx.y)
                if (other->mn.y <= box.mx.y)
                    if (box.mn.z <= other->mx.z)
                        if (other->mn.z <= box.mx.z)
                            return true;
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0073f2e0  release a range of refcounted items [first, last)  (__stdcall)
// ---------------------------------------------------------------------------
void __stdcall ReleaseRange(RCItem* first, RCItem* last)
{
    for (; first < last; ++first) {
        RC* p = first->mpObject;
        if (p) {
            int n = (p->mnRefCount += -1);
            if (n == 0) {
                p->mnRefCount = 1;
                _ReadWriteBarrier();
                p->v0(1);
            }
        }
    }
}

// ===========================================================================
// SP::cModelInstance (retail layout; offsets differ from the 2008 PDB)
// ===========================================================================
#include <xmmintrin.h>

struct V3 { float x, y, z; };
// 16-byte aligned Vector3 with PaddingForAlignment (built with _mm_set_ps(x, z, y, x))
struct __declspec(align(16)) V3A {
    float x, y, z, pad;
    V3A(const V3* p) { _mm_store_ps(&x, _mm_set_ps(p->x, p->z, p->y, p->x)); }
    void set(const V3& v) { x = v.x; y = v.y; z = v.z; }
};

// rw::math::fpu::Matrix33Template<float,0> (9 contiguous floats); copy ctor is the 0x41cb40 helper
struct Matrix33 {
    float m[9];
    Matrix33(const Matrix33& o);       // @0x41cb40 (thiscall, ret 4)
};

// cSPTransform (size 0x38)
struct cSPTransform {
    unsigned short mFlags;             // +0x00
    unsigned short mModificationCount; // +0x02
    float tx, ty, tz;                  // +0x04 mTranslation
    float mScale;                      // +0x10
    Matrix33 mRotation;                // +0x14
    cSPTransform(const cSPTransform& o)
        : mFlags(o.mFlags), mModificationCount(o.mModificationCount),
          tx(o.tx), ty(o.ty), tz(o.tz), mScale(o.mScale), mRotation(o.mRotation) {}
    cSPTransform& operator=(const cSPTransform& o);   // @0x537dc0
    void Invert();                                    // @0x40efa0
    void BackTransformPoint(void* p);                 // @0x4ff6d0 (thiscall, ret 4)
};

// ---------------------------------------------------------------------------
// @ 0x0073f000  PartTransform constructor (ret 0x10)
// @ 0x0073f1c0  PartTransform copy constructor (ret 4)
// ---------------------------------------------------------------------------
struct RCObj { void** vt; int mnRefCount; };       // refcount at +4, slot 0 = deleting dtor
struct PTBase {
    int mField0;                                   // +0x00
    union { int mField4; struct { char a, b; } mFlagBytes; };   // +0x04 (two bytes; copied as a dword)
    int mField8;                                   // +0x08
    RCObj* mpObject;                               // +0x0c (refcounted, refcount at +4)
    PTBase(int a1, RCObj* obj)
    {
        mField8 = a1;
        mField0 = 0;
        mFlagBytes.a = 0;
        mFlagBytes.b = 0;
        mpObject = obj;
        if (mpObject)
            mpObject->mnRefCount++;
    }
    PTBase(const PTBase& o)
    {
        mField0 = o.mField0;
        mField4 = o.mField4;
        mField8 = o.mField8;
        mpObject = o.mpObject;
        if (mpObject)
            mpObject->mnRefCount++;
    }
};
struct PartTransform : PTBase {
    cSPTransform mXf;                  // +0x10
    cSPTransform mXf2;                 // +0x48
    cSPTransform mInverse;             // +0x80
    int mTail0, mTail1, mTail2;        // +0xb8..+0xc0

    PartTransform(int a1, RCObj* obj, const cSPTransform* t1, const cSPTransform* t2);
    PartTransform(const PartTransform& o);
};

PartTransform::PartTransform(int a1, RCObj* obj, const cSPTransform* t1, const cSPTransform* t2)
    : PTBase(a1, obj), mXf(*t1), mXf2(*t2), mInverse(*t2)
{
    mTail0 = 0;
    mTail1 = 0;
    mTail2 = 0;
    mInverse = mXf;
    mInverse.Invert();
}

PartTransform::PartTransform(const PartTransform& o)
    : PTBase(o), mXf(o.mXf), mXf2(o.mXf2), mInverse(o.mInverse)
{
    mTail0 = o.mTail0;
    mTail1 = o.mTail1;
    mTail2 = o.mTail2;
}

// ---------------------------------------------------------------------------
// Objects reached through SP::cModelInstance
// ---------------------------------------------------------------------------
struct DynDrawElem { void* p0; void* p4; void** p8; };      // 12 bytes
struct ElemVec {
    DynDrawElem* begin;
    DynDrawElem* end;
    int size() const { return (int)(end - begin); }
};
struct DynDraw {
    char pad0[0xc];
    int f0c;                           // +0x0c
    char* f10;                         // +0x10 (stride-0x30 records)
    char pad14[0x3c];
    ElemVec mElems;                    // +0x50
};
struct Pair8 { unsigned a, b; };
struct CompiledState { void Dispatch(); };                  // rw::graphics::CompiledState::Dispatch @0x11ee580
struct ShaderDataObj {
    void Push();                                            // 0x7789d0 rw::graphics::ShaderDataState_Push
};
struct VertDesc {
    char pad0[0xc];
    unsigned short count;              // +0x0c
    char pad0e[2];
    unsigned flags;                    // +0x10
    char pad14[4];
    // +0x18: elements of 0xc bytes (kind at +4, id at +8)
    void FUN_11f2bc0();                // @0x11f2bc0
};
struct MeshCtx {                       // the object passed as arg 4 of DispatchMesh
    char pad0[0x44];
    ShaderDataObj* f44;                // +0x44
    char b48;                          // +0x48
    char pad49[3];
    int f4c;                           // +0x4c
    int refcount50;                    // +0x50
};
struct MeshDrawObj {                   // arg 1 of DispatchMesh
    char pad0[8];
    struct { char pad[0x14]; int primType; }* f08;   // +0x08
    char pad0c[0x18];
    VertDesc** f24;                   // +0x24
    void FUN_11f9710();                // @0x11f9710
};

extern "C" void  __cdecl PushShaderDataNull();                         // 0x777bf0
extern "C" void  __cdecl SetShaderDataC(CompiledState*);               // 0x777b50 SP::SetShaderData
extern "C" void  __cdecl ShaderSet(int slot, const void* data, int n); // 0x777ae0
extern "C" void  __cdecl ShaderEnd();                                  // 0x777c10
extern "C" int   __cdecl VertexDescriptor_AreEqual(const void*, const void*);   // 0x11f2e70
extern "C" int   __cdecl RayHelper_00729ad0(int);                      // placeholder (member below)

extern struct { char pad[0x3c]; struct { char pad[0x58]; int f58; }* f3c; }* g_AppProps;   // 0x15fd918
extern char  g_sh_62b870[];     // 0x162b870
extern char* g_sh_62e880;       // 0x162e880
extern int   g_sh_62e874;       // 0x162e874
extern char  g_sh_62e870[];     // 0x162e870
extern char  g_sh_5377cc[];     // 0x15377cc
extern char  g_sh_5379d8;       // 0x15379d8
extern int   g_primType;        // 0x16f85a8
extern const void* g_vertDesc;  // 0x16f65a0
extern unsigned g_softState;    // 0x16f9110

// hull-ish query object stored at this+0xec (slot 6 = bool Query(void*))
struct HullObj { void** vt; };
// resource-ish object at this+0xc4: slot 3 = QueryInterface(id)
struct IfaceObj { void** vt; };

struct cModelInstance {
    char pad0[0x1c];
    Pair8* v1c_begin;                  // +0x1c
    Pair8* v1c_end;                    // +0x20
    char pad24[0xc];
    void** v30_begin;                  // +0x30  (elements: object with CompiledState* at +4)
    void** v30_end;                    // +0x34
    char pad38[0xc];
    RCObj** v44_begin;                 // +0x44
    RCObj** v44_end;                   // +0x48
    char pad4c[0x78];
    IfaceObj* mpIface;                 // +0xc4
    char padc8[4];
    void* mpResource;                  // +0xcc
    void* mpD0;                        // +0xd0
    char padd4[0x18];
    HullObj* mpHull;                   // +0xec
    DynDraw* mpDynDraw;                // +0xf0

    bool GetMeshes(void* a);                                   // @0x73eb90
    bool RayCast(const V3* p0, const V3* p1, cSPTransform* xf, float* outT,
                 V3* outPos, V3* outNormal, int* outA, int* outB);   // @0x73e410
    void DispatchMesh(MeshDrawObj* obj, unsigned idx, int unused, MeshCtx* ctx);  // @0x73ede0
    void SetDrawTransform(const void* src, void* out);         // @0x73eca0
};

// ---------------------------------------------------------------------------
// @ 0x0073eb90  SP::cModelInstance::GetMeshes
// ---------------------------------------------------------------------------
extern "C" void  __cdecl FUN_007c5490b();                      // rw_AllocSerialized @0x7c5490
struct ElemRelease { void FUN_01200940(); };                    // @0x1200940 (thiscall)

bool cModelInstance::GetMeshes(void* a)
{
    if (mpHull) {
        int n = mpDynDraw->mElems.size();
        for (int i = 0; i < n; ++i) {
            DynDrawElem* e = &mpDynDraw->mElems.begin[i];
            if (e->p8) {
                if (e->p0) {
                    void** vt2 = *(void***)((char*)e->p0 + 4);
                    ((void (__thiscall*)(void*))vt2[3])(e->p0);
                    *e->p8 = e->p0;
                    ((ElemRelease*)e->p8)->FUN_01200940();
                } else {
                    FUN_007c5490b();
                }
            }
        }
        if (((bool (__thiscall*)(void*, void*))mpHull->vt[0x18 / 4])(mpHull, a))
            return true;
    }
    IfaceObj* i1 = mpIface;
    if (i1) {
        int r = ((int (__thiscall*)(void*, unsigned))i1->vt[0xc / 4])(i1, 0xe6bce5);
        if (r) {
            FUN_00730210(r, (int)a);
            return true;
        }
    }
    IfaceObj* i2 = mpIface;
    if (i2) {
        int r = ((int (__thiscall*)(void*, unsigned))i2->vt[0xc / 4])(i2, 0x2f4e681b);
        if (r) {
            FUN_0072fff0(r, (int)a);
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0073eca0  build the 4x4 draw matrix from a transform and make it the active world matrix
// ---------------------------------------------------------------------------
struct __declspec(align(16)) M44Raw { float m[16]; };
struct OutM : M44Raw { int type; };
extern unsigned g_dirty;           // 0x16f9528
extern int      g_xfType;          // 0x16f96a0
extern M44Raw*  g_xfPtr;           // 0x16fa380
extern M44Raw   g_xfLocal;         // 0x16fa4f0
struct DrawXfSrc {                 // layout of the source (a cSPTransform-like block)
    unsigned short flags; unsigned short pad2;
    V3 t;
    float s;
    float r[9];
};
struct DynDrawSink { void FUN_73bab0(void* m); };               // @0x73bab0 (thiscall, ret 4)

void cModelInstance::SetDrawTransform(const void* srcv, void* outv)
{
    const DrawXfSrc* p = (const DrawXfSrc*)srcv;
    OutM* out = (OutM*)outv;
    float s = p->s;
    out->m[0] = p->r[0] * s;
    out->m[1] = p->r[1] * s;
    out->m[2] = p->r[2] * s;
    out->m[4] = p->r[3] * s;
    out->m[5] = p->r[4] * s;
    out->m[6] = p->r[5] * s;
    out->m[8] = s * p->r[6];
    out->m[9] = p->r[7] * s;
    out->m[10] = p->r[8] * s;
    *(V3*)&out->m[12] = p->t;
    if (p->s == 1.0f && (p->flags & 6) == 0)
        out->type = 4;
    else if (p->s == 1.0f)
        out->type = 3;
    else
        out->type = 2;
    g_dirty |= 1;
    g_xfType = out->type;
    g_xfPtr = &g_xfLocal;
    g_xfLocal = *out;
    ((DynDrawSink*)mpDynDraw)->FUN_73bab0(out);
}

// ---------------------------------------------------------------------------
// @ 0x0073ede0  SP::cModelInstance::DispatchMesh
// ---------------------------------------------------------------------------
void cModelInstance::DispatchMesh(MeshDrawObj* obj, unsigned idx, int, MeshCtx* ctx)
{
    ctx->refcount50++;
    PushShaderDataNull();
    CompiledState* cs = 0;
    if (idx < (unsigned)(v30_end - v30_begin) && v30_begin[idx])
        cs = *(CompiledState**)((char*)v30_begin[idx] + 4);
    ShaderDataObj* sd = 0;
    if (idx < (unsigned)(v44_end - v44_begin))
        sd = (ShaderDataObj*)v44_begin[idx];
    if (cs) {
        SetShaderDataC(cs);
        cs->Dispatch();
    }
    VertDesc* vd = *obj->f24;
    if (((vd->flags >> 14) & 1) && !ctx->b48 && g_AppProps->f3c->f58 == 0) {
        if (ctx->f4c) {
            if (mpDynDraw->f0c == ctx->f4c)
                g_sh_62e880 = mpDynDraw->f10;
            else
                g_sh_62e880 = g_sh_62b870;
            if (v1c_begin == v1c_end) {
                g_sh_62e874 = ctx->f4c;
            } else {
                g_sh_62e880 = g_sh_62e880 + v1c_begin[idx].a * 0x30;
                g_sh_62e874 = v1c_begin[idx].b;
            }
            ShaderSet(4, g_sh_62e870, 1);
            ShaderSet(3, g_sh_5377cc, 0);
        }
    } else {
        ShaderSet(3, 0, 0);
        ShaderSet(4, 0, 0);
    }
    if (vd->flags & 4) {
        unsigned n = vd->count;
        unsigned i = 0;
        if (n) {
            char* e = (char*)vd + 0x18;
            do {
                if (*(int*)(e + 8) == 2) {
                    if (e[4] == 5 && g_sh_5379d8)
                        ShaderSet(0x22c, &g_sh_5379d8, 0);
                    break;
                }
                ++i;
                e += 0xc;
            } while (i < n);
        }
    }
    g_primType = obj->f08->primType;
    if (g_vertDesc == 0 || !VertexDescriptor_AreEqual(g_vertDesc, vd))
        g_softState |= 0x100000;
    g_vertDesc = vd;
    vd->FUN_11f2bc0();
    if (sd) sd->Push();
    if (ctx->f44) ctx->f44->Push();
    obj->FUN_11f9710();
    ShaderEnd();
}

// ---------------------------------------------------------------------------
// @ 0x0073e410  SP::cModelInstance::RayCast  (segment p0->p1 against the hull; 0x20 bytes of args)
// ---------------------------------------------------------------------------
struct HitRec {                        // stride 0xd0
    char pad0[0x10];
    V3 pos;                            // +0x10
    char pad1c[4];
    V3 dir;                            // +0x20
    char pad2c[0x14];
    float t;                           // +0x40
    char pad44[0x8c];
};
struct IdRec { char pad[0x58]; int id; char pad5c[4]; };   // stride 0x60
struct RayCache {
    char pad0[0x10];
    HitRec* hits;                      // +0x10
    int count;                         // +0x14
    char pad18[0xcc];
    IdRec* ids;                        // +0xe4
    int fE8;                           // +0xe8
    char padec[0x14];
    int f100;                          // +0x100
    void FUN_73a6e0(void* buf, int a, int b, const V3A* p0, const V3A* p1);   // @0x73a6e0
};
struct XfBuf { void* p; };
struct AllocObj { void** vt; };
struct ResObj { AllocObj* GetAllocator(); };                              // @0x7f54d0
struct IdLookup { int FUN_729ad0(int id); };                              // @0x729ad0
extern RayCache* g_rayCache;                                              // 0x162eaf0
extern "C" int   __cdecl FUN_01201660b(void* buf, int a, int b);          // @0x1201660
extern "C" void  __cdecl FUN_006c1c80b(void* buf, int v);                 // @0x6c1c80
extern "C" RayCache* __cdecl FUN_012016d0b(void* buf, int a, int b);      // @0x12016d0
extern "C" void  __stdcall ehvec_dtor(void* p, unsigned size, int cnt, void (__thiscall* d)(void*));  // 0x11e0b22
extern "C" void  __cdecl Elem8Dtor();                                      // 0xc2e4e0

struct __declspec(align(16)) Mat4L { float r0[4], r1[4], r2[4], t[4]; };
static const float kFltMax = 3.4028234663852886e+38f;

bool cModelInstance::RayCast(const V3* p0, const V3* p1, cSPTransform* xf, float* outT,
                             V3* outPos, V3* outNormal, int* outA, int* outB)
{
    if (!mpResource)
        return false;
    V3A a0(p0);
    V3A a1(p1);
    float scale = xf->mScale;
    Mat4L mat;
    bool needXform;
    if (scale == 1.0f) {
        mat.t[0] = xf->tx; mat.t[1] = xf->ty; mat.t[2] = xf->tz;
        mat.r0[0] = xf->mRotation.m[0] * scale; mat.r0[1] = xf->mRotation.m[1] * scale; mat.r0[2] = xf->mRotation.m[2] * scale;
        mat.r1[0] = xf->mRotation.m[3] * scale; mat.r1[1] = xf->mRotation.m[4] * scale; mat.r1[2] = xf->mRotation.m[5] * scale;
        mat.r2[0] = xf->mRotation.m[6] * scale; mat.r2[1] = xf->mRotation.m[7] * scale; mat.r2[2] = xf->mRotation.m[8] * scale;
        needXform = false;
    } else {
        needXform = true;
        xf->BackTransformPoint(&a0);
        xf->BackTransformPoint(&a1);
        mat.t[0] = 0; mat.t[1] = 0; mat.t[2] = 0; mat.t[3] = 0;
        mat.r2[0] = 0; mat.r2[1] = 0; mat.r2[2] = 1.0f; mat.r2[3] = 0;
        mat.r0[0] = 1.0f; mat.r0[1] = 0; mat.r0[2] = 0; mat.r0[3] = 0;
        mat.r1[0] = 0; mat.r1[1] = 1.0f; mat.r1[2] = 0; mat.r1[3] = 0;
    }
    needXform = scale != 1.0f;
    if (g_rayCache == 0) {
        char arr[32];
        char tmp[16];
        int r = FUN_01201660b(arr, 4, 4);
        FUN_006c1c80b(tmp, r);
        ehvec_dtor(arr, 8, 4, (void (__thiscall*)(void*))Elem8Dtor);
        g_rayCache = FUN_012016d0b(tmp, 4, 4);
    }
    RayCache* cache = g_rayCache;
    char buf[100];
    XfBuf xb;
    xb.p = buf;
    cache->FUN_73a6e0(&xb, 0, 1, &a0, &a1);
    cache->f100 = 2;
    float best = kFltMax;
    int bestId = -1;
    bool again;
    do {
        cache->count = 0;
        cache->fE8 = 0;
        AllocObj* al = ((ResObj*)mpResource)->GetAllocator();
        void** iface = *(void***)((char*)al + 0x20);
        int r = ((int (__thiscall*)(void*, RayCache*, Mat4L*))iface[0x14 / 4])(al, cache, &mat);
        cache = g_rayCache;
        again = (r == 0);
        for (int i = 0; i < cache->count; ++i) {
            HitRec* h = &cache->hits[i];
            if (best > h->t) {
                a1.set(h->pos);
                best = h->t;
                a0.set(h->dir);
                bestId = cache->ids[i].id;
            }
        }
    } while (cache->count != 0 && again);
    if (!(best < kFltMax))
        return false;
    if (outT)
        *outT = best;
    if (outPos) {
        outPos->x = a1.x; outPos->y = a1.y; outPos->z = a1.z;
        if (needXform) {
            if (xf->mFlags & 2) {
                float y = outPos->y, z = outPos->z, x = outPos->x;
                const float* r = xf->mRotation.m;
                outPos->x = (r[3] * y + r[6] * z) + x * r[0];
                outPos->y = (r[1] * x + r[4] * y) + r[7] * z;
                outPos->z = (r[2] * x + r[5] * y) + r[8] * z;
            }
            float s = xf->mScale;
            float z = outPos->z, x = outPos->x, y = outPos->y;
            outPos->y = s * y;
            outPos->z = z * s;
            outPos->x = x * s;
            outPos->x = x * s + xf->tx;
            outPos->y = xf->ty + s * y;
            outPos->z = xf->tz + z * s;
        }
    }
    if (outNormal) {
        outNormal->x = a0.x; outNormal->y = a0.y; outNormal->z = a0.z;
        if (needXform && (xf->mFlags & 2)) {
            float y = outNormal->y, z = outNormal->z, x = outNormal->x;
            const float* r = xf->mRotation.m;
            outNormal->x = (r[3] * y + r[6] * z) + r[0] * x;
            outNormal->y = (r[1] * x + r[4] * y) + r[7] * z;
            outNormal->z = (r[2] * x + r[5] * y) + r[8] * z;
        }
    }
    if (outA || outB) {
        int v;
        if (mpD0) {
            v = ((IdLookup*)mpD0)->FUN_729ad0(bestId);
        } else {
            v = -1;
            bestId = -1;
        }
        if (outA) *outA = v;
        if (outB) *outB = bestId;
    }
    return true;
}
