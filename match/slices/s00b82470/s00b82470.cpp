// Slice s00b82470 -- SP::cPlanetModel surface projection / snapping family.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//   RayCast / Project / DirectionToSurfacePosition / ToSurface are the per-mode kernels; the
//   Project* entry points pick a kernel (or the radial terrain ray-cast) based on game mode and
//   snap options. Members, helper names and layouts from the retail disassembly + the 2008 PDB.
#include "types.h"

#pragma warning(disable: 4100)

struct Vec3 { float x, y, z; };
struct hkWorld;

// The simulator-global mode block returned by 0x00b3d310; +0x20 is the current game mode.
struct SimMode { char pad[0x20]; int mMode; };
SimMode* __cdecl GetSim();                                  // 0x00b3d310
extern SimMode* g_sim;                                      // 0x0167eae8

extern Vec3 kFallback;                                      // 0x016881f0 (fallback/invalid point)
extern hkWorld* gWorld;                                     // 0x0167ecd0
extern float kProjRange;                                    // 0x0145c12c (2000.0f)
extern float kEps;                                          // 0x013ec4b8 (1e-8)
extern float kPoolStep;                                     // 0x013ec478 (0.05f)
extern float kDefaultHeight;                                // 0x01465414 (500.0f)
extern float kTiny;                                         // 0x013eb960 (0.01f)
extern float kTwo;                                          // 0x01470f1c (2.0f)
extern float kFive;                                         // 0x01486110 (5.0f)
extern float kOne;                                          // 0x01485720 (1.0f)
extern float kHalf;                                         // 0x01471064 (0.5f)
extern float kHeightScale;                                  // 0x0140d4f8 (1/32768)

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);

struct cPlanetModel;

// float -> int floor using the module's cvtss2si + cmovb inline helper.
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

struct cTerrainMapBase {
    char       pad0[8];
    int        mDim;          // +0x08
    char       padc[4];
    uint16_t*  mpData;        // +0x10
};

struct cTerrainMapSet {
    char  pad0[0x34];
    float mRadius;            // +0x34
    float mMaxHeight;         // +0x38
    float mWaterHeight;       // +0x3c
    float __thiscall GetHeightAt(const Vec3* pos);            // 0x00f927c0 (ret 4)
};

struct cITerrainSphere {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual cTerrainMapSet* GetMapSet();                      // +0xc
};

struct SnapOpt {
    virtual void f();
    bool on;                                                  // +0x04
    SnapOpt() : on(true) {}
};

struct RadialRay {                                            // 24 bytes
    Vec3  pos;                                                // +0x00 (w at +0x0c)
    float pad0;
    float h0;                                                 // +0x10
    float h1;                                                 // +0x14
};

struct ProjRay {                                              // 40 bytes
    Vec3         pos;                                         // +0x00 at +0x0c
    float        pad0;
    Vec3         dir;                                         // +0x10
    float        pad1;
    float        h0;                                          // +0x20
    uint32_t     tail;                                        // +0x24 (float maxT or SnapOpt*)
};

struct RayHitResult {
    int    status;                                            // +0x00
    char   pad04[0xc];
    Vec3   pos;                                               // +0x10
    float  w;                                                 // +0x1c
    void*  normalOut;                                         // +0x20
    void*  distOut;                                           // +0x24
    void*  userData;                                          // +0x28
    void*  entity;                                            // +0x2c
};

void __cdecl FUN_00b65b10(const RadialRay* ray, hkWorld* world, void* obj, bool useWorld,
                          uint32_t filterInfo, RayHitResult* out);        // 0x00b65b10
void __cdecl FUN_00b672e0(const ProjRay* ray, cPlanetModel* self, hkWorld* world,
                          RayHitResult* out);                             // 0x00b672e0
bool __cdecl IntersectRaySphere(const Vec3& origin, const Vec3& direction, const Vec3& center,
                                float radius, float* pDistance);          // 0x005a9c40

struct cPlanetModel {
    char  pad00[0x20];
    void* mpSphere;                                           // +0x20
    cITerrainSphere* mpISphere;                               // +0x24
    char  pad28[0xf0 - 0x28];
    uint8_t mFlagF0;                                          // +0xf0

    Vec3* RayCast(Vec3* out, const Vec3* from, const Vec3* dir);          // 0x00b82060 (ret 0xc)
    Vec3* Project(Vec3* out, const Vec3* from, const Vec3* dir);          // 0x00b82110 (ret 0xc)
    Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* dir);         // 0x00b815a0 (ret 8)
    Vec3* ToSurface(Vec3* out, const Vec3* in);                           // 0x00b81630 (ret 8)
    Vec3* ToSurface2(Vec3* out, const Vec3* in);                          // 0x00b816f0 (ret 8)
    float GetRadiusAt(const Vec3* pos);                                   // 0x00b7ef70 (ret 4)
    float GetRadiusX2();                                                  // 0x00b7e500 (ret 0)
    void  FUN_00b7f060(Vec3* out, const Vec3* pos, float* dist);          // 0x00b7f060 (ret 0xc)

    Vec3* ProjectRay(Vec3* out, const Vec3* from, const Vec3* dir, float maxT);
    Vec3* ProjectOpt(Vec3* out, const Vec3* from, const Vec3* dir, SnapOpt* opt);
    Vec3* SnapB(Vec3* out, const Vec3* in, char flag);
    Vec3* SnapA(Vec3* out, const Vec3* in, char flag);
    Vec3* SnapDispatch(Vec3* out, const Vec3* in, char flag);
    Vec3* ProjectToSurface(Vec3* out, const Vec3* in, char a, char b, char c, char d);
    float SurfaceDistance(const Vec3* p, const Vec3* dir);
    int   ClassifyPoint(const Vec3* dir);
    float SampleTerrainHeight(const Vec3* dir);
};

// @ 0x00b82470
Vec3* cPlanetModel::ProjectRay(Vec3* out, const Vec3* from, const Vec3* dir, float maxT)
{
    if (GetSim()->mMode != 0) {
        RayCast(out, from, dir);
        return out;
    }
    Vec3 p;
    RayCast(&p, from, dir);
    if (p.x != kFallback.x || p.y != kFallback.y || p.z != kFallback.z) {
        Vec3 d;
        d.x = from->x - p.x;
        d.y = from->y - p.y;
        d.z = from->z - p.z;
        float dist = (float)sqrt((double)(d.z * d.z + d.x * d.x + d.y * d.y));

        ProjRay ray;
        ray.pos.x = from->x;
        ray.pos.y = from->y;
        ray.pos.z = from->z;
        ray.pad0 = 0.0f;
        ray.dir.x = dir->x;
        ray.dir.y = dir->y;
        ray.dir.z = dir->z;
        ray.pad1 = 0.0f;
        ray.h0 = dist;
        *(float*)&ray.tail = maxT;

        RayHitResult hit;
        FUN_00b672e0(&ray, this, gWorld, &hit);
        p = hit.pos;
    }
    out->x = p.x;
    out->y = p.y;
    out->z = p.z;
    return out;
}

// @ 0x00b82620
Vec3* cPlanetModel::ProjectOpt(Vec3* out, const Vec3* from, const Vec3* dir, SnapOpt* opt)
{
    if (GetSim()->mMode != 0) {
        Project(out, from, dir);
        return out;
    }
    Vec3 p;
    RayCast(&p, from, dir);
    float span = kProjRange;
    float waterProbe = 0.0f;
    if (p.x != kFallback.x || p.y != kFallback.y || p.z != kFallback.z) {
        span = (float)sqrt((double)((from->z - p.z) * (from->z - p.z) +
                                    (from->y - p.y) * (from->y - p.y)) +
                           (from->x - p.x) * (from->x - p.x));
        waterProbe = span;
    }

    ProjRay ray;
    ray.pos.x = from->x;
    ray.pos.y = from->y;
    ray.pos.z = from->z;
    ray.pad0 = 0.0f;
    ray.dir.x = dir->x;
    ray.dir.y = dir->y;
    ray.dir.z = dir->z;
    ray.pad1 = 0.0f;
    ray.h0 = span;
    ray.tail = (uint32_t)opt;

    RayHitResult hit;
    FUN_00b672e0(&ray, this, gWorld, &hit);
    if (hit.status != 0)
        p = hit.pos;

    if (mpISphere == 0) {
        waterProbe = 0.0f;
    } else {
        cTerrainMapSet* m = mpISphere->GetMapSet();
        waterProbe = m->mWaterHeight * m->mMaxHeight + m->mRadius;
    }
    float fx = from->x;
    if (waterProbe * waterProbe <= (from->y * from->y + from->z * from->z) + fx * fx &&
        IntersectRaySphere(*from, *dir, kFallback, waterProbe, &waterProbe)) {
        float ny = from->y + dir->y * waterProbe;
        float nz = from->z + dir->z * waterProbe;
        float nx = fx + dir->x * waterProbe;
        if ((p.x == kFallback.x && p.y == kFallback.y && p.z == kFallback.z) ||
            (((nz - from->z) * (nz - from->z) + (ny - from->y) * (ny - from->y)) +
             (nx - from->x) * (nx - from->x) <
             ((kFallback.z - from->z) * (kFallback.z - from->z) +
              (kFallback.y - from->y) * (kFallback.y - from->y)) +
                 (kFallback.x - from->x) * (kFallback.x - from->x))) {
            out->x = nx;
            out->y = ny;
            out->z = nz;
            return out;
        }
    }
    out->x = p.x;
    out->y = p.y;
    out->z = p.z;
    return out;
}

// @ 0x00b82970
Vec3* cPlanetModel::SnapB(Vec3* out, const Vec3* in, char flag)
{
    if (GetSim()->mMode != 0) {
        DirectionToSurfacePosition(out, in);
        return out;
    }
    Vec3 local;
    DirectionToSurfacePosition(&local, in);
    float len2 = local.x * local.x + (local.z * local.z + local.y * local.y);
    float len = (float)sqrt((double)len2);

    Vec3 p;
    float h0, h1;
    if (flag == 0) {
        p = local;
        h0 = GetRadiusX2() - len;
        h1 = 0.0f;
    } else {
        p = *in;
        h0 = kPoolStep;
        h1 = len - (float)sqrt((double)(p.x * p.x + (in->y * in->y + in->z * in->z)));
    }

    RadialRay ray;
    ray.pos = p;
    ray.pad0 = 0.0f;
    ray.h0 = h0;
    ray.h1 = h1;

    RayHitResult hit;
    FUN_00b65b10(&ray, gWorld, 0, true, 6, &hit);
    if (hit.status != 0) {
        if (len2 < (hit.pos.y * hit.pos.y + hit.pos.z * hit.pos.z) + hit.pos.x * hit.pos.x) {
            out->x = hit.pos.x;
            out->y = hit.pos.y;
            out->z = hit.pos.z;
            return out;
        }
    }
    out->x = local.x;
    out->y = local.y;
    out->z = local.z;
    return out;
}

// @ 0x00b82b40
Vec3* cPlanetModel::SnapA(Vec3* out, const Vec3* in, char flag)
{
    if (GetSim()->mMode != 0) {
        ToSurface(out, in);
        return out;
    }
    Vec3 local;
    DirectionToSurfacePosition(&local, in);
    float len2 = (local.z * local.z + local.y * local.y) + local.x * local.x;
    float len = (float)sqrt((double)len2);
    float origLen2 = len2;

    Vec3 p;
    float h0, h1;
    if (flag == 0) {
        p = local;
        h0 = GetRadiusX2() - len;
        h1 = 0.0f;
    } else {
        p = *in;
        h0 = kPoolStep;
        h1 = len - (float)sqrt((double)(p.x * p.x + (in->y * in->y + in->z * in->z)));
    }

    RadialRay ray;
    ray.pos = p;
    ray.pad0 = 0.0f;
    ray.h0 = h0;
    ray.h1 = h1;

    RayHitResult hit;
    FUN_00b65b10(&ray, gWorld, 0, true, 6, &hit);
    if (hit.status != 0) {
        float hlen2 = (hit.pos.y * hit.pos.y + hit.pos.z * hit.pos.z) + hit.pos.x * hit.pos.x;
        if (hlen2 > len2)
            len2 = hlen2;
    }

    float water;
    if (mpISphere == 0) {
        water = 0.0f;
    } else {
        cTerrainMapSet* m = mpISphere->GetMapSet();
        water = m->mWaterHeight * m->mMaxHeight + m->mRadius;
    }
    if (water * water < len2) {
        len2 = (float)sqrt((double)len2);
    } else if (mpISphere == 0) {
        len2 = 0.0f;
    } else {
        cTerrainMapSet* m = mpISphere->GetMapSet();
        len2 = m->mWaterHeight * m->mMaxHeight + m->mRadius;
    }
    float inv = 1.0f / (float)sqrt((double)(origLen2 + kEps));
    out->x = (inv * local.x) * len2;
    out->y = (inv * local.y) * len2;
    out->z = (inv * local.z) * len2;
    return out;
}

// @ 0x00b82dc0
Vec3* cPlanetModel::SnapDispatch(Vec3* out, const Vec3* in, char flag)
{
    if (mFlagF0 != 0) {
        SnapA(out, in, flag);
        return out;
    }
    SnapB(out, in, flag);
    return out;
}

// @ 0x00b82df0
Vec3* cPlanetModel::ProjectToSurface(Vec3* out, const Vec3* in, char a, char b, char c, char d)
{
    if (a != 0) {
        if (b != 0)
            SnapA(out, in, d);
        else if (c != 0)
            SnapDispatch(out, in, d);
        else
            SnapB(out, in, d);
    } else {
        if (b != 0)
            ToSurface(out, in);
        else if (c != 0)
            ToSurface2(out, in);
        else
            DirectionToSurfacePosition(out, in);
    }
    return out;
}

// @ 0x00b82e80
float cPlanetModel::SurfaceDistance(const Vec3* p, const Vec3* dir)
{
    float ux = dir->x;
    float uy = dir->y;
    float uz = dir->z;
    float inv = 1.0f / (float)sqrt((double)(ux * ux + uy * uy + uz * uz));

    Vec3 q;
    q.x = p->x + ux * inv;
    q.y = p->y + inv * uy;
    q.z = p->z + inv * uz;

    float r = GetRadiusAt(&q);
    float inv2 = 1.0f / (float)sqrt((double)(q.x * q.x + (q.y * q.y + q.z * q.z)) + kEps);
    float rx = (q.z * inv2) * r;
    float ry = (q.y * inv2) * r;
    float rz = (inv2 * q.x) * r;
    return (float)sqrt((double)(rx * rx + (ry * ry + rz * rz))) -
           (float)sqrt((double)(p->x * p->x + (p->y * p->y + p->z * p->z)));
}

// @ 0x00b82fc0
int cPlanetModel::ClassifyPoint(const Vec3* dir)
{
    cTerrainMapSet* m = mpISphere->GetMapSet();
    if (mpISphere != 0 && m != 0) {
        float h = m->GetHeightAt(dir);
        float f = m->mWaterHeight * m->mMaxHeight + m->mRadius - h;
        if (f > 0.0f && f > kTiny) {
            if (f < kTwo) {
                float dist = 0.0f;
                Vec3 tmp;
                FUN_00b7f060(&tmp, dir, &dist);
                if (dist < kFive)
                    return 3;
            }
            return 2;
        }
    }
    float dist = 0.0f;
    Vec3 tmp;
    FUN_00b7f060(&tmp, dir, &dist);
    if (dist > kFive)
        return 1;
    return 0;
}

// @ 0x00b830b0
float cPlanetModel::SampleTerrainHeight(const Vec3* dir)
{
    if (mpISphere == 0)
        return kDefaultHeight;

    cTerrainMapSet* m = mpISphere->GetMapSet();
    int dim = (*(cTerrainMapBase**)((char*)m + 8))->mDim;
    uint16_t* data = (*(cTerrainMapBase**)((char*)m + 8))->mpData;

    float x = dir->x;
    float y = dir->y;
    float z = dir->z;
    float ax = (float)fabs((double)x);
    float ay = (float)fabs((double)y);
    float az = (float)fabs((double)z);

    float u, v;
    int face;
    if (az >= ax && az >= ay) {
        u = (x / z + kOne) * kHalf;
        v = (y / az + kOne) * kHalf;
        face = (z < 0.0f) ? 1 : 0;
    } else if (ay >= ax) {
        u = (z / y + kOne) * kHalf;
        v = (x / ay + kOne) * kHalf;
        face = (y < 0.0f) ? 5 : 4;
    } else {
        u = (y / x + kOne) * kHalf;
        v = (z / ax + kOne) * kHalf;
        face = (x < 0.0f) ? 3 : 2;
    }

    int cu = FloorToInt((float)dim * u);
    if (dim - 1 < cu)
        cu = dim - 1;
    int cv = FloorToInt((float)dim * v);
    if (dim - 1 < cv)
        cv = dim - 1;

    int raw = (int)data[(face * dim + cv) * dim + cu];
    return (float)(raw - 0x8000) * kHeightScale * m->mMaxHeight + m->mRadius;
}
