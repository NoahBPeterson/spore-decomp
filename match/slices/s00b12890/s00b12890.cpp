// Slice s00b12890 (batch gold1) — SP::cTerrainCameraController constructor + camera helpers.
// Module "Spore" (VS2008 SP1). Compiled /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
// Types/offsets follow the retail disassembly (2008 PDB layout shifted +0x30 after the
// spline members; cLocalInputState sits at +0x31c).

#include "types.h"
#include <math.h>
#include <string.h>

struct Vector3 { float x, y, z; };
struct cSPQuaternion { float x, y, z, w; };
struct cSPMatrix3 { float m[9]; };

// SP::cTerrainCameraController::cInterpolationData<T>
template<class T> struct Interp
{
    bool  targetChanged;   // +0
    bool  targetMoving;    // +1
    float currentTime;     // +4
    float targetTime;      // +8
    T     start;           // +0xc
    T     current;
    T     end;
    T     target;
    T     velocity;
    T     targetVelocity;
    void  Set3(float, float, float);          // out-of-line helper, ecx = this  (@0xf4f5a0)
    void  Set4(float, float, float, float);   // out-of-line helper, ecx = this  (@0xf4fe50)
    void  Reset2(int, bool);                  // out-of-line helper, ecx = this  (@0xf4ff00)
};

// SP::cHermiteSplineInterpolation<T> (retail: three 0x14-byte SpVectors = 0x3c)
template<class T> struct SpVector { T* begin; T* end; T* cap; uint32_t extra[2]; };
template<class T> struct Spline
{
    SpVector<float> times;
    SpVector<T>     points;
    SpVector<T>     slopes;
};

struct cSPTransform
{
    uint16_t mFlags;             // +0
    uint16_t mModificationCount; // +2
    Vector3  mTranslation;       // +4
    float    mScale;             // +0x10
    cSPMatrix3 mRotation;        // +0x14
    void AssignRotation(const void* m);          // rw Matrix3::Assign          @0x41cb40
    void PreRotateX(float a);                    // EA::Swarm::cTransform       @0x5a2d90
    void RotateY(float a);                       // Transform_RotateY           @0x4099b0
};

// cLocalInputState: 0x4c bytes in retail; only two trailing flags are touched here.
struct cLocalInputState
{
    uint8_t data[0x48];
    bool    flag364;
    bool    flag365;
    uint8_t pad[2];
    void    Init();     // out-of-line init @0x697960
};

struct cTerrainCameraController
{
    void*    vptr0;                 // +0x00
    void*    vptr1;                 // +0x04
    void*    vptr2;                 // +0x08
    uint32_t m0c;                   // +0x0c
    bool     m10;                   // +0x10
    bool     m11, m12, m13, m14, m15, m16, m17;   // +0x11..0x17
    Interp<float>         mCameraAnchorRadius;        // +0x18
    Interp<Vector3>       mCameraAnchorDirection;     // +0x3c
    Interp<cSPQuaternion> mCameraAnchorOrientation;   // +0x90
    Interp<float>         mCameraDistance;            // +0xfc
    Interp<float>         mCameraPitch;               // +0x120
    Interp<float>         mCameraYaw;                 // +0x144
    bool     mBallisticMotion;      // +0x168
    bool     mAltZoomMode;          // +0x169
    uint8_t  pad_16a[2];
    Spline<float>         mDistanceSpline;      // +0x16c
    Spline<float>         mPitchSpline;         // +0x1a8
    Spline<Vector3>       mDirectionSpline;     // +0x1e4
    Spline<cSPQuaternion> mOrientationSpline;   // +0x220
    float f25c, f260, f264, f268, f26c, f270, f274, f278;   // +0x25c..+0x278
    float f27c, f280, f284, f288, f28c;                     // +0x27c..+0x28c
    float f290, f294, f298, f29c, f2a0, f2a4, f2a8, f2ac;   // +0x290..+0x2ac
    float f2b0, f2b4;                                       // +0x2b0,+0x2b4
    uint8_t pad_2b8[0x14];          // +0x2b8..+0x2cc
    cSPTransform mCameraToWorld;    // +0x2cc
    bool     mTransformNeedsUpdating;  // +0x304
    uint8_t  pad_305[3];
    uint32_t mCameraZoomProgramID; // +0x308
    void*    mConfig;              // +0x30c
    float    mNearClip;            // +0x310
    float    mFarClip;             // +0x314
    bool     mMouseMovedThisFrame; // +0x318
    bool     mIgnoreMouseMiddleButton; // +0x319
    bool     m31a;
    bool     mForceUpdate;         // +0x31b
    cLocalInputState mLocalInputState;  // +0x31c
    float    f368, f36c, f370, f374, f378, f37c, f380;  // +0x368..+0x380
    uint32_t m384;                 // +0x384
    float    f388, f38c;           // +0x388,+0x38c
    bool     m390;                 // +0x390

    cTerrainCameraController* Construct(void* p);
    void FUN_00b12dd0(float* pos, int p3, bool b4);
    void FUN_00b134a0();
    void FUN_00b13790(void* out);
};

// ---- out-of-line symbols (addresses in comments; relocations are masked in byte diffs) ----
extern "C" {
    int  VT_13eb384[], VT_13ef094[], VT_145cf88[], VT_145cf78[], VT_14667ec[];
    extern const int G_167bd14[9];
    float G_167bbf8, G_167bbfc, G_167bc00;
    float G_167bd44, G_167bd48, G_167bd4c;
    float G_167bd60, G_167bd64, G_167bd68;
    int   G_167bd6c;
    float G_1567de4, G_1567de8, G_1567dec;
    float G_1567df0, G_1567df4, G_1567df8, G_1567dfc;
    char  G_1567da4;
}

struct cTerrainSphere;
cTerrainSphere* GetActiveTerrainSphere();               // 0x00f48aa0
struct cTerrainMapSet;
struct cTerrainSphere
{
    float GetRadius();                                  // 0x00f987f0
    cTerrainMapSet* GetTerrainMap();                    // vfn [vtbl+0xc]
    cSPQuaternion* GetSurfaceOrientation(cSPQuaternion* out, const Vector3* dir); // vfn [vtbl+0x10c]
};
struct cTerrainMapSet
{
    float GetHeightAt(const float* pos);                // 0x00f927c0
};
struct cSpring3f { void Set(const Vector3* v, bool b); };   // 0x00b0fae0
struct Basis3 { void* Build(void* out); };                  // 0x006b9440
void Matrix3FromQuaternion(cSPMatrix3* out, const float* q); // 0x0059c190
void FUN_00b118a0(cTerrainCameraController* self);          // 0x00b118a0
cSPQuaternion* FUN_007dcb00(cSPQuaternion* out, const cSPQuaternion* in, const cSPQuaternion* rot); // 0x007dcb00
cSPQuaternion* BuildSurfaceOrientation(cSPQuaternion* out, const Vector3* dir, cSPQuaternion* q);    // cTerrainSphere::BuildSurfaceOrientation
void XForm2_PreRotateX(cSPTransform* t, uint32_t angle);    // 0x006ba940
void XForm2_PreRotateY(cSPTransform* t, float angle);       // 0x006baa70
void Modifier_Accumulate(cSPTransform* a, const cSPTransform* b);  // 0x0040ccb0
void cSPTransform_Assign(cSPTransform* dst, const cSPTransform* src); // 0x00537dc0

// @ 0x00b12890
cTerrainCameraController* cTerrainCameraController::Construct(void* p)
{
    vptr1 = (void*)VT_13eb384;
    vptr2 = (void*)VT_13ef094;
    m0c = 0;
    vptr0 = (void*)VT_145cf88;
    vptr1 = (void*)VT_145cf78;
    vptr2 = (void*)VT_14667ec;
    m10 = true;
    m11 = m12 = m13 = m14 = m15 = m16 = m17 = false;
    mBallisticMotion = false;
    mAltZoomMode = false;

    mDistanceSpline.times.begin = 0; mDistanceSpline.times.end = 0; mDistanceSpline.times.cap = 0;
    mDistanceSpline.points.begin = 0; mDistanceSpline.points.end = 0; mDistanceSpline.points.cap = 0;
    mDistanceSpline.slopes.begin = 0; mDistanceSpline.slopes.end = 0; mDistanceSpline.slopes.cap = 0;
    mPitchSpline.times.begin = 0; mPitchSpline.times.end = 0; mPitchSpline.times.cap = 0;
    mPitchSpline.points.begin = 0; mPitchSpline.points.end = 0; mPitchSpline.points.cap = 0;
    mPitchSpline.slopes.begin = 0; mPitchSpline.slopes.end = 0; mPitchSpline.slopes.cap = 0;
    mDirectionSpline.times.begin = 0; mDirectionSpline.times.end = 0; mDirectionSpline.times.cap = 0;
    mDirectionSpline.points.begin = 0; mDirectionSpline.points.end = 0; mDirectionSpline.points.cap = 0;
    mDirectionSpline.slopes.begin = 0; mDirectionSpline.slopes.end = 0; mDirectionSpline.slopes.cap = 0;
    mOrientationSpline.times.begin = 0; mOrientationSpline.times.end = 0; mOrientationSpline.times.cap = 0;
    mOrientationSpline.points.begin = 0; mOrientationSpline.points.end = 0; mOrientationSpline.points.cap = 0;
    mOrientationSpline.slopes.begin = 0; mOrientationSpline.slopes.end = 0; mOrientationSpline.slopes.cap = 0;

    f260 = -1.0f;
    f278 = 0.1f; f27c = 0.1f; f280 = 0.1f; f284 = 0.1f; f288 = 0.1f;
    f290 = 0.52359879f;
    f294 = 10.0f;
    f298 = 0.034906585f;
    f25c = 0.0f;
    f264 = 0.0f; f268 = 0.0f; f26c = 0.0f; f270 = 0.0f;
    f274 = 5.0f;
    f28c = 0.0f;
    f29c = 0.0087266462f;
    f2a0 = 0.0082999999f;
    f2ac = 0.0f;
    f2a4 = 100.0f;
    f2b0 = 1.5707964f;
    f2a8 = 1500.0f;
    f2b4 = 5.0f;

    mCameraToWorld.mModificationCount = 0;
    mCameraToWorld.mFlags = 0;
    mCameraToWorld.mTranslation.x = G_167bbf8;
    mCameraToWorld.mTranslation.y = G_167bbfc;
    mCameraToWorld.mTranslation.z = G_167bc00;
    mCameraToWorld.mScale = 1.0f;
    mCameraToWorld.AssignRotation(G_167bd14);

    mTransformNeedsUpdating = true;
    mCameraZoomProgramID = 0;
    mConfig = p;
    if (p)
        ((void(__thiscall*)(void*))*(void**)p)(p);   // AddRef (vfn0)
    mNearClip = 1.0f;
    mFarClip = 10000.0f;
    mMouseMovedThisFrame = false;
    mIgnoreMouseMiddleButton = true;
    mForceUpdate = false;

    mLocalInputState.Init();

    f368 = 0.3f;
    f36c = 15.0f;
    f370 = 1.0f;
    f374 = 0.7f;
    f378 = 6.0f;
    f37c = 700.0f;
    f380 = 100.0f;
    mLocalInputState.flag364 = true;
    mLocalInputState.flag365 = true;
    m384 = 0x3e9;
    f388 = 0.0f;
    f38c = 0.0f;
    m390 = false;

    mCameraAnchorRadius.targetChanged = false;
    mCameraAnchorRadius.targetMoving = false;
    mCameraAnchorRadius.currentTime = 0.0f;
    mCameraAnchorRadius.targetTime = 0.0f;
    mCameraAnchorRadius.start = 0.0f;
    mCameraAnchorRadius.current = 0.0f;
    mCameraAnchorRadius.end = 0.0f;
    mCameraAnchorRadius.target = 0.0f;
    mCameraAnchorRadius.velocity = 0.0f;
    mCameraAnchorRadius.targetVelocity = 0.0f;

    mCameraAnchorDirection.Set3(G_1567de4, G_1567de8, G_1567dec);
    mCameraAnchorOrientation.Set4(G_1567df0, G_1567df4, G_1567df8, G_1567dfc);

    mCameraDistance.current = 1.0f;
    mCameraDistance.end = 1.0f;
    mCameraDistance.velocity = 1.0f;
    mCameraDistance.targetVelocity = 1.0f;
    mCameraDistance.targetChanged = false;
    mCameraDistance.targetMoving = false;
    mCameraDistance.targetTime = 0.0f;
    mCameraDistance.currentTime = 0.0f;
    mCameraDistance.target = 0.0f;
    mCameraDistance.start = 0.0f;

    mCameraPitch.targetChanged = false;
    mCameraPitch.targetMoving = false;
    mCameraPitch.targetTime = 0.0f;
    mCameraPitch.currentTime = 0.0f;
    mCameraPitch.start = 0.26179939f;
    mCameraPitch.current = 0.26179939f;
    mCameraPitch.end = 0.26179939f;
    mCameraPitch.target = 0.26179939f;
    mCameraPitch.velocity = 0.0f;
    mCameraPitch.targetVelocity = 0.0f;

    mCameraYaw.targetChanged = false;
    mCameraYaw.targetMoving = false;
    mCameraYaw.targetTime = 0.0f;
    mCameraYaw.currentTime = 0.0f;
    mCameraYaw.start = 0.0f;
    mCameraYaw.current = 0.0f;
    mCameraYaw.end = 0.0f;
    mCameraYaw.target = 0.0f;
    mCameraYaw.velocity = 0.0f;
    mCameraYaw.targetVelocity = 0.0f;
    return this;
}

// @ 0x00b12dd0
void cTerrainCameraController::FUN_00b12dd0(float* pos, int p3, bool b4)
{
    cTerrainSphere* sph = GetActiveTerrainSphere();
    if (!sph)
        return;

    float radius = sph->GetRadius();
    cTerrainMapSet* map = sph->GetTerrainMap();
    float height = map->GetHeightAt(pos);

    float* chosen = (radius > height) ? &radius : &height;
    float dist = f2b4 + *chosen;

    Vector3 dir = { pos[0], pos[1], pos[2] };
    float len = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    float* pickedPtr = (len > dist) ? &len : &dist;
    float picked = *pickedPtr;

    Vector3 n;
    if (picked > 1.52587890625e-05f)
    {
        float inv = 1.0f / picked;
        n.x = dir.x * inv;
        n.y = dir.y * inv;
        n.z = dir.z * inv;
    }
    else
    {
        n.x = G_167bbf8;
        n.y = G_167bbfc;
        n.z = G_167bc00;
    }

    if (b4)
    {
        mCameraAnchorRadius.current = picked;
        mCameraAnchorRadius.end = picked;
        mCameraAnchorRadius.target = picked;
        mCameraAnchorRadius.start = picked;
        mCameraAnchorRadius.velocity = picked * 0.0f;
        mCameraAnchorRadius.targetVelocity = picked * 0.0f;
        mCameraAnchorRadius.targetChanged = false;
        mCameraAnchorRadius.targetMoving = false;
    }
    else if (picked != mCameraAnchorRadius.target)
    {
        mCameraAnchorRadius.target = picked;
        mCameraAnchorRadius.end = mCameraAnchorRadius.start;
        mCameraAnchorRadius.targetChanged = true;
    }

    ((cSpring3f*)((char*)this + 0x3c))->Set(&n, b4);
    mCameraAnchorOrientation.Reset2(p3, b4);
    if (b4)
    {
        FUN_00b118a0(this);
        mTransformNeedsUpdating = true;
    }
}

// @ 0x00b12f90  ?SlerpOrientation@@YAXPAUcSPQuaternion@@PBUVector3@@1PBU1@2@Z
void SlerpOrientation(cSPQuaternion* out, const Vector3* a, const Vector3* b,
                      const cSPQuaternion* q, const Vector3* c)
{
    float ax = a->x;
    if (ax == G_167bbf8 && a->y == G_167bbfc && a->z == G_167bc00)
    {
        cTerrainSphere* sph = GetActiveTerrainSphere();
        if (!sph)
        {
            out->x = G_1567df0; out->y = G_1567df4; out->z = G_1567df8; out->w = G_1567dfc;
            return;
        }
        cSPQuaternion tmp;
        cSPQuaternion* r = sph->GetSurfaceOrientation(&tmp, b);
        *out = *r;
        return;
    }

    float ifa = 1.0f / sqrtf(ax * ax + (a->y * a->y + a->z * a->z));
    float ux = ax * ifa;
    float uy = a->y * ifa;
    float uz = a->z * ifa;

    float bx = b->x, by = b->y, bz = b->z;
    float ib = 1.0f / sqrtf((bx * bx + by * by) + bz * bz);
    float sx = bx * ib + ux;
    float sz = bz * ib + uz;
    float sy = by * ib + uy;

    float l = sqrtf(sy * sy + (sz * sz + sx * sx));
    if (1.52587890625e-05f <= l)
    {
        float inv = 1.0f / l;
        sy *= inv;
        sz *= inv;
        sx *= inv;

        cSPQuaternion qq, qin;
        qq.x = sz * uy - sy * uz;
        qq.y = uz * sx - sz * ux;
        qq.z = sy * ux - sx * uy;
        qq.w = (sy * uy + sz * uz) + sx * ux;
        qin = qq;
        cSPQuaternion* r = FUN_007dcb00(&qin, &qq, q);
        *out = *r;
        if (G_1567da4 != 0 && GetActiveTerrainSphere() != 0)
        {
            cSPQuaternion* r2 = BuildSurfaceOrientation(&qq, b, out);
            *out = *r2;
        }
        return;
    }

    float dx = ax - c->x;
    float dz = a->z - c->z;
    float dy = a->y - c->y;
    float id = 1.0f / sqrtf(dy * dy + (dz * dz + dx * dx));
    float cx = (dy * id) * uz - (dz * id) * uy;
    float cy = (dz * id) * ux - uz * (id * dx);
    float cz = uy * (id * dx) - (dy * id) * ux;

    float xx = cz * uy - cy * uz;
    float yy = uz * cx - cz * ux;
    float zz = cy * ux - uy * cx;
    if (sqrtf(yy * yy + (zz * zz + xx * xx)) < 1.52587890625e-05f)
    {
        float t0 = uz * 0.0f;
        xx = uy * 0.0f - t0;
        float t1 = ux * 0.0f;
        yy = uz - t1;
        zz = t1 - uy;
        if (sqrtf(yy * yy + (zz * zz + xx * xx)) < 1.52587890625e-05f)
        {
            xx = uy - t0;
            yy = t0 - ux;
            zz = t1 - uy * 0.0f;
        }
    }
    float inl = 1.0f / sqrtf(zz * zz + (yy * yy + xx * xx));
    cSPQuaternion qv, qv2;
    qv.x = inl * xx; qv.y = yy * inl; qv.z = zz * inl;
    qv2 = qv;
    cSPQuaternion* r = FUN_007dcb00(&qv, &qv2, q);
    *out = *r;
}

// @ 0x00b134a0
void cTerrainCameraController::FUN_00b134a0()
{
    cSPTransform t;
    t.mTranslation.x = G_167bbf8;
    t.mTranslation.y = G_167bbfc;
    t.mModificationCount = 0;
    t.mTranslation.z = G_167bc00;
    t.mFlags = 0;
    t.mScale = 1.0f;
    t.AssignRotation(G_167bd14);
    t.mFlags |= 4;
    t.mModificationCount = (uint16_t)(t.mModificationCount + 1);

    float dt = -mCameraDistance.current;
    t.mTranslation.x += G_167bd44 * dt;
    t.mTranslation.y += G_167bd48 * dt;
    t.mTranslation.z += G_167bd4c * dt;

    XForm2_PreRotateX(&t, *(uint32_t*)&mCameraPitch.current ^ 0x80000000u);
    XForm2_PreRotateY(&t, mCameraYaw.current);

    if (mCameraAnchorOrientation.current.w < 1.0f)
    {
        cSPTransform q;
        q.mFlags = 0;
        q.mModificationCount = 0;
        q.mTranslation.x = G_167bbf8;
        q.mTranslation.y = G_167bbfc;
        q.mTranslation.z = G_167bc00;
        q.mScale = 1.0f;
        q.AssignRotation(G_167bd14);

        cSPMatrix3 m;
        Matrix3FromQuaternion(&m, &mCameraAnchorOrientation.current.x);
        q.mRotation = m;
        q.mFlags |= 2;
        q.mModificationCount = (uint16_t)(q.mModificationCount + 1);

        Modifier_Accumulate(&t, &q);
        cSPTransform_Assign(&t, &q);
    }

    if ((G_167bd6c & 1) == 0)
        G_167bd6c |= 1;
    G_167bd60 = mCameraAnchorRadius.current;
    t.mFlags |= 4;
    t.mModificationCount = (uint16_t)(t.mModificationCount + 1);
    G_167bd64 = mCameraAnchorDirection.current.y * G_167bd60;
    G_167bd68 = mCameraAnchorDirection.current.z * G_167bd60;
    G_167bd60 = G_167bd60 * mCameraAnchorDirection.current.x;
    t.mTranslation.x += G_167bd60;
    t.mTranslation.y += G_167bd64;
    t.mTranslation.z += G_167bd68;
    t.PreRotateX(f26c);
    t.RotateY(f270);
    cSPTransform_Assign(&mCameraToWorld, &t);
    mTransformNeedsUpdating = false;
}

// @ 0x00b13790
void cTerrainCameraController::FUN_00b13790(void* out)
{
    if (mTransformNeedsUpdating)
        FUN_00b134a0();
    struct Matrix64 { int d[16]; };
    Matrix64 local;
    Matrix64* src = (Matrix64*)((Basis3*)&mCameraToWorld)->Build(&local);
    *(Matrix64*)out = *src;
}
