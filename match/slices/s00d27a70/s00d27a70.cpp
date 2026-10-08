// slice s00d27a70 -- creature-stage cameras:
//   0x00d27a70  SP::cCreatureCamera::ApplyPlayerDeltas(bool)  (PDB candidate): moves the camera
//               position along the player-delta direction, clipped against nearby objects, or applies
//               the pending pitch / yaw / zoom deltas about the anchor
//   0x00d28300  free-look camera update(float dt): keyboard-driven distance / yaw / pitch / pan
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no EH frame: the fixed vector has an inline dtor; a 1 KB array local gets no cookie)
#include <math.h>
#include "types.h"

#pragma intrinsic(sqrt, fabs, sin, cos)

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// SSE clamp helper from the original headers (maxss then minss).
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
};
inline Vec3 operator-(const Vec3& a, const Vec3& b)
{
    Vec3 r(a.x - b.x, a.y - b.y, a.z - b.z);
    return r;
}
struct Quat { float x, y, z, w; };

void  __cdecl operator_delete__(void* p) throw();                   // 0x00f47380
Vec3* __cdecl normalized_safe(Vec3* out, const Vec3* in);           // 0x00449c20
void  __cdecl RotateAroundAxis(Vec3* out, const Vec3* v, const Vec3* axis, float angle);   // 0x00d21d10

extern bool  g_158275d;       // 0x0158275d
extern float g_169de9c;       // 0x0169de9c
extern float g_169dea0;       // 0x0169dea0
extern float g_169dea4;       // 0x0169dea4
extern float kEpsilon;        // 0x0147a31c  (1.5258789e-05)

// ---- collaborators --------------------------------------------------------------------------
struct IRayWorld {
    PV8 PV2
    virtual int RayCast(const Vec3* from, const Vec3* to, float* tOut, void* filter);   // 0x28
};
struct IModelManager {
    PV4 PV2 PV
    virtual IRayWorld* GetWorld(uint32_t id);                       // 0x1c
};
IModelManager* __cdecl ModelManager();                              // 0x0067dd80

struct cPlanetModel {
    Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* in);    // 0x00b815a0
    Vec3* SnapToSurface(Vec3* out, const Vec3* in, int flag);       // 0x00b82b40
    Quat* SurfaceOrientation(Quat* out, const Vec3* in, const Quat* prev);   // 0x00b7f1f0
};
cPlanetModel* __cdecl PlanetModel();                                // 0x00b3d350

struct cSpatialQuery {
    int QueryNear(const Vec3* pos, float radius, int flags, void* outHits);                          // 0x00b7a1d0
    int QueryNearBlocked(const Vec3* from, const Vec3* tmp, float radius, void* outHits, int flag);  // 0x00b7a4a0
};
cSpatialQuery* __cdecl SpatialQuery();                              // 0x00b3d3c0

struct cAvatarBody {
    PV8 PV8 PV8 PV4 PV
    virtual float GetMinDistance();                                 // 0x74
};
struct cAvatar { char pad[0xc0]; cAvatarBody mBody; };
struct cNounManager { cAvatar* GetAvatar(); };                      // 0x00b1fdb0
cNounManager* __cdecl NounManager();                                // 0x00b3d300

struct HitObject {
    char  pad00[0x38];
    Vec3  mCenter;      // +0x38
    float m44;          // +0x44
    char  pad48[4];
    float m4c;          // +0x4c
    char  pad50[0x88 - 0x50];
    int   mType;        // +0x88
};
bool __cdecl RayHitsObject(const Vec3* origin, const Vec3* dir, const Vec3* center, const Vec3* centerUnit,
                           float a, float b, float* tOut, float* out2);       // 0x00698fa0

// eastl::fixed_vector<HitObject*, 256> with its overflow cookie word in front of the inline storage
struct HitVec {
    HitObject** mpBegin;
    HitObject** mpEnd;
    HitObject** mpCap;
    int         mAlloc0, mAlloc1;
    int         mCookie;
    HitObject*  mBuf[256];
    HitVec() { mCookie = 0; mpBegin = mBuf; mpEnd = mBuf; mpCap = mBuf + 256; }
    ~HitVec() { if (mpBegin && ((int*)mpBegin)[-1] != 0) operator_delete__(mpBegin); }
};

struct RayFilter { int a, b, c, d, e; char kind; char flag; };

// ---- cCreatureCamera (retail offsets) ---------------------------------------------------------
namespace SP {

class cCreatureCamera {
public:
    char  pad00[0x48];
    Vec3  m48;
    char  pad54[0xa0 - 0x54];
    Vec3  mA0;
    char  padac[0xec - 0xac];
    float mEC, mF0, mF4;
    float mF8, mFC, m100;
    char  pad104[0x108 - 0x104];
    Vec3  mP1;
    Vec3  mAnchor;       // +0x114
    char  pad120[0x13c - 0x120];
    Vec3  mCamPos;       // +0x13c
    char  pad148[0x174 - 0x148];
    float m174, m178, m17c;
    char  pad180[0x2b0 - 0x180];
    bool  mb2b0;

    float GetPitch(float a, float b);                       // 0x00d21810
    void  ApplyPlayerDeltas(bool flag);                     // @ 0x00d27a70
};

// @ 0x00d27a70
void cCreatureCamera::ApplyPlayerDeltas(bool flag)
{
    if (mb2b0) {
        Vec3 d = mP1 - mA0;
        float lenSq = d.x * d.x + d.z * d.z + d.y * d.y;
        HitVec hits;
        float len = (float)sqrt((double)lenSq);
        float inv = 1.0f / (float)sqrt((double)(lenSq + 1e-8f));
        Vec3 dir;
        dir.x = d.x * inv;
        dir.y = d.y * inv;
        dir.z = d.z * inv;
        if (g_158275d) {
            IRayWorld* world = ModelManager()->GetWorld(0x3fbae24);
            RayFilter filter = { 0, 0, 0, 0, 0, 4, 0 };
            float t;
            if (world->RayCast(&mA0, &mP1, &t, &filter) && t > kEpsilon) {
                float k = t * len - 1.0f;
                mP1.x = mA0.x + dir.x * k;
                mP1.y = mA0.y + dir.y * k;
                mP1.z = mA0.z + dir.z * k;
            } else {
                Vec3 tmp;
                PlanetModel()->DirectionToSurfacePosition(&tmp, &mP1);
                SpatialQuery()->QueryNearBlocked(&mA0, &tmp, 1.0f, &hits, 0);
            }
        } else {
            SpatialQuery()->QueryNear(&mP1, 1.0f, 0x18, &hits);
        }
        int n = (int)(hits.mpEnd - hits.mpBegin);
        if (n <= 0) {
            g_169de9c = mF8;
            g_169dea4 = mFC;
            g_169dea0 = m100;
        } else if (!g_158275d) {
            mP1 = mCamPos;
            m174 = g_169de9c; mF8 = g_169de9c;
            m178 = g_169dea4; mFC = g_169dea4;
            m17c = g_169dea0; m100 = g_169dea0;
        } else {
            float minT = len;
            for (int i = 0; i < n; ++i) {
                HitObject* o = hits.mpBegin[i];
                if ((1 << (o->mType & 31)) & 8) {
                    const Vec3& c = o->mCenter;
                    float cinv = 1.0f / (float)sqrt((double)(c.x * c.x + c.y * c.y + c.z * c.z + 1e-8f));
                    Vec3 cu;
                    cu.x = c.x * cinv; cu.y = c.y * cinv; cu.z = c.z * cinv;
                    float t, out2;
                    if (RayHitsObject(&mA0, &dir, &o->mCenter, &cu, o->m44, o->m4c, &t, &out2) &&
                        t > 0.0f && minT > t)
                        minT = t;
                }
            }
            cAvatar* avatar = NounManager()->GetAvatar();
            if (avatar) {
                float v = minT;
                float lo = avatar->mBody.GetMinDistance();
                float hi = m17c;
                v = Clamp(v, lo, hi);
                mP1.x = mA0.x + dir.x * v;
                mP1.y = mA0.y + dir.y * v;
                mP1.z = mA0.z + dir.z * v;
            }
        }
        m48 = mP1;
        mCamPos = mP1;
        return;
    }

    if (fabs(mEC) > kEpsilon) {
        float inv = 1.0f / (float)sqrt((double)(mAnchor.x * mAnchor.x + mAnchor.y * mAnchor.y + mAnchor.z * mAnchor.z + 1e-8f));
        Vec3 n;
        n.x = mAnchor.x * inv; n.y = mAnchor.y * inv; n.z = mAnchor.z * inv;
        Vec3 d;
        d.x = mAnchor.x - mCamPos.x;
        d.y = mAnchor.y - mCamPos.y;
        d.z = mAnchor.z - mCamPos.z;
        Vec3 r;
        RotateAroundAxis(&r, &d, &n, mEC);
        mCamPos.x = mAnchor.x - r.x;
        mCamPos.y = mAnchor.y - r.y;
        mCamPos.z = mAnchor.z - r.z;
    }
    if (fabs(mF0) > kEpsilon) {
        float p = mF0 + mFC;
        Vec3 d;
        d.x = mAnchor.x - mCamPos.x;
        d.y = mAnchor.y - mCamPos.y;
        d.z = mAnchor.z - mCamPos.z;
        float len = (float)sqrt((double)(d.z * d.z + (d.y * d.y + d.x * d.x)));
        if (fabs(p - GetPitch(p, len)) < kEpsilon) {
            Vec3 c;
            c.x = d.y * mCamPos.z - d.z * mCamPos.y;
            c.y = d.z * mCamPos.x - mCamPos.z * d.x;
            c.z = mCamPos.y * d.x - d.y * mCamPos.x;
            Vec3 nrm;
            normalized_safe(&nrm, &c);
            Vec3 r;
            RotateAroundAxis(&r, &d, &nrm, -mF0);
            mCamPos.x = mAnchor.x - r.x;
            mCamPos.y = mAnchor.y - r.y;
            mCamPos.z = mAnchor.z - r.z;
        }
    }
    if (flag) {
        float zoom = mF4;
        if (fabs(zoom) > kEpsilon) {
            Vec3 d;
            d.x = mAnchor.x - mCamPos.x;
            d.y = mAnchor.y - mCamPos.y;
            d.z = mAnchor.z - mCamPos.z;
            float len = (float)sqrt((double)(d.z * d.z + (d.y * d.y + d.x * d.x)));
            if (len > kEpsilon) {
                float scale = (zoom + len) / len;
                mCamPos.x = mAnchor.x - d.x * scale;
                mCamPos.y = mAnchor.y - d.y * scale;
                mCamPos.z = mAnchor.z - d.z * scale;
            }
        }
    }
}

}   // namespace SP


// =============================================================================================
// @ 0x00d28300  free-look camera update(float dt)
// =============================================================================================
extern float kDeg2Rad;        // 0x0147a304
extern Vec3  gDefaultDir;     // 0x0169deb0
extern float gRotAxisX;       // 0x0169df5c
extern float gRotAxisY;       // 0x0169df60
extern float gRotAxisZ;       // 0x0169df64

bool __cdecl IsGameRunning();                                         // 0x00805180
Quat* __cdecl QuatMultiply(Quat* out, const Quat* a, const Quat* b);  // 0x007dcb00
Vec3* __cdecl QuatRotate(Vec3* out, const Vec3* v, const Quat* q);    // 0x0059aed0

struct cGameInputManager {
    PV4 PV2
    virtual bool IsKeyDown(int key);                                  // 0x18
};
cGameInputManager* __cdecl GameInputManager();                        // 0x00b3d250

struct ITerrain {
    PV8 PV4 PV2
    virtual void ProjectPosition(Vec3& pos, int mode, Vec3 dir);      // 0x38
};
ITerrain* __cdecl GetTerrain();                                       // 0x00b3d240

template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

class cFreeCamera {
public:
    char  pad00[0x1c];
    float mDeltaTime;            // +0x1c
    char  pad20[0x180 - 0x20];
    float mYaw;                  // +0x180
    float mPitch;                // +0x184
    float mDistance;             // +0x188
    float mRollAngle;            // +0x18c
    char  pad190[4];
    float mDistance2;            // +0x194
    char  pad198[0x1ac - 0x198];
    Vec3  mPos;                  // +0x1ac
    Quat  mOrient;               // +0x1b8
    Vec3  mAnchor;               // +0x1c8
    Quat  mRot;                  // +0x1d4
    char  pad1e4[0x208 - 0x1e4];
    float mMinPitch, mMaxPitch, mMinDistance;   // +0x208, +0x20c, +0x210
    char  pad214[0x254 - 0x214];
    float mSpeed;                // +0x254

    void Update(float dt);       // @ 0x00d28300
};

// @ 0x00d28300
void cFreeCamera::Update(float dt)
{
    mDeltaTime = dt;
    cPlanetModel* pm = PlanetModel();
    if (!pm) return;
    if (!IsGameRunning()) return;

    if (GameInputManager()->IsKeyDown(0x16)) {
        Vec3 pos;
        GetTerrain()->ProjectPosition(pos, 1, gDefaultDir);
        if (pos.y * pos.y + pos.z * pos.z + pos.x * pos.x > 0.0f) {
            Vec3 d = pos - mAnchor;
            float s = mSpeed * mDistance2;
            Vec3 d2 = d;
            Quat buf;
            Vec3* n = normalized_safe((Vec3*)&buf, &d);
            Vec3 step;
            step.x = n->x * s; step.y = n->y * s; step.z = n->z * s;
            if (d2.x * d2.x + d2.z * d2.z + d2.y * d2.y > step.x * step.x + step.z * step.z + step.y * step.y) {
                d.x = mAnchor.x + step.x;
                d.y = mAnchor.y + step.y;
                d.z = mAnchor.z + step.z;
            } else {
                d.x = mAnchor.x + d2.x;
                d.y = mAnchor.y + d2.y;
                d.z = mAnchor.z + d2.z;
            }
            Vec3* p = pm->SnapToSurface((Vec3*)&buf, &d, 0);
            mPos = *p;
            Quat* q = pm->SurfaceOrientation(&buf, &d, &mOrient);
            mOrient = *q;
        }
    }

    cGameInputManager* gim = GameInputManager();
    if (!gim) return;
    float a = 0.0f, c = 0.0f, b = 0.0f, d = 0.0f;
    if (gim->IsKeyDown(0x10)) a = -1.0f;
    if (gim->IsKeyDown(0x11)) a = a + 1.0f;
    if (gim->IsKeyDown(1)) b = -1.0f;
    if (gim->IsKeyDown(2)) b = b + 1.0f;
    if (gim->IsKeyDown(3)) c = 1.0f;
    if (gim->IsKeyDown(4)) c = c - 1.0f;
    if (gim->IsKeyDown(0x12)) d = dt * -3.0f;
    float nd;
    if (gim->IsKeyDown(0x13)) nd = dt * 3.0f + d;
    else nd = d;
    float v = nd + mDistance;
    const float& r = Max(v, mMinDistance);
    mDistance = r;
    mDistance2 = r;
    mYaw = a * kDeg2Rad + mYaw;
    mPitch = Clamp(mPitch, mMinPitch, mMaxPitch);
    if (c != 0.0f || b != 0.0f) {
        float half = mRollAngle * 0.5f;
        float sn = (float)sin((double)half);
        Quat q;
        q.x = sn * gRotAxisX;
        q.y = sn * gRotAxisY;
        q.z = sn * gRotAxisZ;
        q.w = (float)cos((double)half);
        Quat qm;
        Vec3 dir;
        dir.x = c; dir.y = b; dir.z = 0.0f;
        Vec3 rot;
        Vec3* rp = QuatRotate(&rot, &dir, QuatMultiply(&qm, &mRot, &q));
        Vec3 rv = *rp;
        float s2 = mSpeed * mDistance2;
        Quat tmpq;
        Vec3* n = normalized_safe((Vec3*)&tmpq, &rv);
        float nx = n->x * s2, ny = n->y * s2, nz = n->z * s2;
        mPos.x = mAnchor.x - nx;
        mPos.y = mAnchor.y - ny;
        mPos.z = mAnchor.z - nz;
        Vec3* p = pm->SnapToSurface((Vec3*)&tmpq, &mPos, 0);
        mPos = *p;
        Quat* qo = pm->SurfaceOrientation(&tmpq, &mPos, &mOrient);
        mOrient = *qo;
    }
}
