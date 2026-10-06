// Slice s00eb4420: 0x00EB4420, a per-frame transform builder for a (creature/vehicle) view that
// switches on a camera/placement mode (+0x14, 0..4), computing an orientation quaternion and
// writing a cSPTransform (also stored at +0x174).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct Matrix3 { float m[3][3]; };

struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vec3     mOffset;
    float    mScale;
    Matrix3  mRotation;

    cSPTransform& operator=(const cSPTransform& other);   // 0x00537DC0
    void Rotate(float angle);                             // 0x006B9050
    void RotateY(float angle);                            // 0x004099B0
    void PreRotateX(float angle);                         // 0x005A2D90

    void SetOffset(float x, float y, float z) {
        mOffset.x = x; mOffset.y = y; mOffset.z = z;
        mFlags |= 4; mModificationCount++;
    }
    void AddOffset(const Vec3& v) {
        mOffset.x += v.x; mOffset.y += v.y; mOffset.z += v.z;
        mFlags |= 4; mModificationCount++;
    }
    // offset += rotation * (v * scale)
    void PreTranslate(float vx, float vy, float vz) {
        float x = mScale * vx;
        float y = mScale * vy;
        float z = mScale * vz;
        mOffset.x = (mRotation.m[2][0] * z + mRotation.m[1][0] * y + x * mRotation.m[0][0]) + mOffset.x;
        mOffset.y = (mRotation.m[0][1] * x + mRotation.m[2][1] * z + mRotation.m[1][1] * y) + mOffset.y;
        mOffset.z = (mRotation.m[0][2] * x + mRotation.m[2][2] * z + mRotation.m[1][2] * y) + mOffset.z;
        mFlags |= 4; mModificationCount++;
    }
    void SetRotation(const Matrix3* m) {
        mRotation = *m;
        mFlags |= 2; mModificationCount++;
    }
};

struct cTerrainMapSet {
    char  _pad[0x34];
    float mRadius, mMaxHeight, mWaterHeight;
    float GetHeightAt(const Vec3* pos);       // SP::cTerrainMapSet::GetHeightAt 0x00F927C0
};
struct IMapSetProvider { virtual void v0(); virtual void v1(); virtual void v2(); virtual cTerrainMapSet* GetMapSet(); };
struct cPlanetModel { char _pad[0x24]; IMapSetProvider* mpTerrain; };
cPlanetModel* PlanetModel();                                   // 0x00B3D350

Matrix3* __cdecl MatrixFromQuat(Matrix3* out, const Quat* q);  // 0x004A9B40
Vec3*    __cdecl normalized_safe(Vec3* out, const Vec3* in);   // SP::normalized_safe 0x00449C20
Quat*    __cdecl QuaternionFromFacingAndUp(Quat* out, const Vec3* facing, const Vec3* up);  // 0x0069B600
void     __cdecl Vector3_Normalize(Vec3* out, const Vec3* in); // 0x00436CE0
char     __cdecl Vector3Equal(const Vec3* a, const Vec3* b);   // 0x004232C0
float    __stdcall DistSq(float, float, float, float, float, float);   // 0x00EB3220
extern Vec3 gAxes[3];                                          // 0x015A940C

struct cView {
    char    _pad00[0x14];
    int     mMode;                 // +0x14
    float   mF18, mF1C, mF20;
    char    _pad24[0x8];
    float   mF2C, mF30, mF34;
    char    _pad38[0x8];
    float   mF40, mF44, mF48;
    char    _pad4c[0x8];
    Vec3    mPos;                  // +0x54
    Vec3    mTarget;               // +0x60
    char    _pad6c[0xc];
    bool    mbPlanet;              // +0x78
    char    _pad79[0xf0 - 0x79];
    float   mDistance;             // +0xf0
    char    _padf4[0x109 - 0xf4];
    bool    mbKeepFacing;          // +0x109
    bool    mbSnapOrient;          // +0x10a
    char    _pad10b;
    float   mF10C;                 // +0x10c
    char    _pad110[0x8];
    Vec3    mFacing;               // +0x118
    Vec3    mUp;                   // +0x124
    Quat    mQuatA;                // +0x130
    Quat    mQuatB;                // +0x140
    Quat    mQuatC;                // +0x150
    char    _pad160[0x1a0 - 0x160];   // cSPTransform at +0x174 (overlaps mAltFacing, see mTransform())
    Vec3    mAltFacing;            // +0x1a0
    float   mF1AC;                 // +0x1ac
    char    _pad1b0[0x2dc - 0x1b0];
    Vec3    mAnchor;               // +0x2dc

    cSPTransform& mTransformRef() { return *(cSPTransform*)((char*)this + 0x174); }
    // @ 0x00EB4420
    void UpdateTransform(cSPTransform* t);
};

static inline Vec3 Cross(const Vec3& a, const Vec3& b)
{
    Vec3 r = { a.z * b.y - a.y * b.z, a.x * b.z - a.z * b.x, a.y * b.x - a.x * b.y };
    return r;
}

// Snap the transform onto the planet surface (never below terrain/water) and look at mPos.
static __forceinline void ClampToPlanet(cView* v, cSPTransform* t)
{
    Vec3 pos = t->mOffset;
    float len = sqrtf(pos.y * pos.y + (pos.z * pos.z + pos.x * pos.x));
    Vec3 n;
    Vector3_Normalize(&n, &pos);
    cTerrainMapSet* ms = PlanetModel()->mpTerrain->GetMapSet();
    float h = ms->GetHeightAt(&pos);
    float wl = ms->mWaterHeight * ms->mMaxHeight + ms->mRadius;
    const float* pm = &h;
    if (h <= wl)
        pm = &wl;
    float f = *pm + 0.1f;
    if (len < f) {
        pos.x = n.x * f;
        pos.y = n.y * f;
        pos.z = n.z * f;
    }
    Vec3 up = n;
    Vec3 d = { v->mPos.x - pos.x, v->mPos.y - pos.y, v->mPos.z - pos.z };
    Vec3 fc;
    normalized_safe(&fc, &d);
    Quat q;
    Quat* qp = QuaternionFromFacingAndUp(&q, &fc, &up);
    Matrix3 tmp;
    t->mRotation = *MatrixFromQuat(&tmp, qp);
    t->mFlags |= 6;
    t->mOffset = pos;
    t->mModificationCount += 2;
}

// @ 0x00EB4420
void cView::UpdateTransform(cSPTransform* t)
{
    Matrix3 tmp1;
    Matrix3 tmp2;
    Matrix3 tmp3;
    Matrix3 tmp4;
    Matrix3 tmp5;
    Matrix3 tmp6;
    Quat qtmp1;
    Quat qtmp2;
    Quat qtmp3;
    Quat qtmp4;
    Vec3 vtmp1;
    Vec3 vtmp2;
    Vec3 vtmp3;
    Vec3 vtmp4;
    Vec3 vtmp5;
    Vec3 vtmp6;
    Vec3 vtmp7;
    switch (mMode) {
    case 0: {
        Matrix3 m = *MatrixFromQuat(&tmp1, &mQuatB);
        Vec3 v;
        if (mbPlanet == 1)
            v = *normalized_safe(&vtmp1, &mPos);
        else {
            v.x = m.m[2][0]; v.y = m.m[2][1]; v.z = m.m[2][2];
        }
        Vec3 c = mTransformRef().mOffset;
        Vec3 d = { mTarget.x - c.x, mTarget.y - c.y, mTarget.z - c.z };
        mFacing = *normalized_safe(&vtmp2, &d);
        d = Cross(mFacing, v);
        Vec3 n;
        normalized_safe(&n, &d);
        d = Cross(n, mFacing);
        v = *normalized_safe(&vtmp3, &d);
        Quat* q = QuaternionFromFacingAndUp(&qtmp1, &mFacing, &v);
        mQuatC = *q;
        if (mbSnapOrient) {
            mQuatB = *q;
            mQuatA = *q;
        }
        mF34 = 0; mF30 = 0; mF2C = 0; mF20 = 0; mF1C = 0; mF18 = 0; mF48 = 0; mF44 = 0; mF40 = 0;
        t->mRotation = *MatrixFromQuat(&tmp2, &mQuatB);
        t->mFlags |= 6;
        t->mModificationCount += 2;
        t->mOffset = c;
        mTransformRef() = *t;
        float s = mDistance;
        t->mFlags |= 4;
        t->mModificationCount++;
        t->mOffset.x = s * mFacing.x + c.x;
        t->mOffset.y = mFacing.y * s + c.y;
        t->mOffset.z = mFacing.z * s + c.z;
        return;
    }
    case 1: {
        if (!mbKeepFacing) {
            Vec3 up = mUp;
            mFacing = mAltFacing;
            Quat* q = QuaternionFromFacingAndUp(&qtmp2, &mFacing, &up);
            mQuatC = *q;
        }
        t->SetRotation(MatrixFromQuat(&tmp3, &mQuatB));
        t->RotateY(-mF1C);
        t->PreRotateX(mF30);
        t->Rotate(mF44);
        t->PreTranslate(0.0f, -mDistance, 0.0f);
        t->AddOffset(mPos);
        ClampToPlanet(this, t);
        mF20 = mF20 - mF10C;
        break;
    }
    case 2: {
        float s = mDistance - mF1AC;
        t->SetRotation(MatrixFromQuat(&tmp4, &mQuatB));
        t->PreTranslate(0.0f, s, 0.0f);
        break;
    }
    case 3: {
        Vec3 d = { mPos.x - mAnchor.x, mPos.y - mAnchor.y, mPos.z - mAnchor.z };
        mFacing = *normalized_safe(&vtmp4, &d);
        Vec3 u = mUp;
        if (fabsf((u.z * mFacing.z + mFacing.y * u.y) + mFacing.x * u.x) - 1.0f < 0.01f) {
            u = gAxes[2];
            if (fabsf(u.x * mFacing.x + (mFacing.z * u.z + mFacing.y * u.y)) - 1.0f < 0.01f)
                u = gAxes[1];
        }
        d = Cross(mFacing, u);
        Vec3 r;
        normalized_safe(&r, &d);
        d = Cross(r, mFacing);
        u = *normalized_safe(&vtmp5, &d);
        t->mOffset.x = mAnchor.x;
        t->mOffset.y = mAnchor.y;
        float z = mAnchor.z;
        t->mFlags |= 4;
        t->mModificationCount++;
        t->mOffset.z = z;
        Quat* q = QuaternionFromFacingAndUp(&qtmp3, &mFacing, &u);
        t->SetRotation(MatrixFromQuat(&tmp5, q));
        break;
    }
    case 4: {
        if (mbPlanet == 1 && !mbKeepFacing) {
            Vec3 v;
            normalized_safe(&v, &mPos);
            if (Vector3Equal(&mFacing, &gAxes[0]) &&
                fabsf((mFacing.x * v.x + (mFacing.z * v.z + mFacing.y * v.y)) - 1.0f) < 0.01f) {
                float ny = -gAxes[1].y;
                float nz = -gAxes[1].z;
                mFacing.x = -gAxes[1].x;
                mFacing.y = ny;
                mFacing.z = nz;
            }
            if (DistSq(mTarget.x, mTarget.y, mTarget.z, mPos.x, mPos.y, mPos.z) > 1.0f) {
                Vec3 d = { mTarget.x - mPos.x, mTarget.y - mPos.y, mTarget.z - mPos.z };
                mFacing = *normalized_safe(&vtmp6, &d);
            }
            Vec3 d = Cross(mFacing, v);
            Vec3 r;
            normalized_safe(&r, &d);
            d = Cross(v, r);
            mFacing = *normalized_safe(&vtmp7, &d);
            Quat* q = QuaternionFromFacingAndUp(&qtmp4, &mFacing, &v);
            mQuatC = *q;
            if (mbSnapOrient) {
                mQuatB = *q;
                mQuatA = *q;
            }
        }
        float dist = mDistance;
        if (dist == 0.0f && mbPlanet == 1)
            dist = 10.0f;
        t->SetRotation(MatrixFromQuat(&tmp6, &mQuatB));
        t->RotateY(-mF1C);
        t->PreRotateX(mF30);
        t->Rotate(mF44);
        t->PreTranslate(0.0f, -dist, 0.0f);
        t->AddOffset(mPos);
        mF20 = mF20 - mF10C;
        if (mbPlanet == 1)
            ClampToPlanet(this, t);
        break;
    }
    default:
        return;
    }
    mTransformRef() = *t;
}
