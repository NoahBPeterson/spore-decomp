// Slice s00d25ac0 -- SP::cCreatureCamera input/camera helpers.
//   0x00d25ac0  cCreatureCamera::OnMouseMove(float,float,int)
//   0x00d25ca0  cCreatureCamera::UpdateCamera(float)
//   0x00d25e00  cCreatureCamera::FUN_00d25e00()
//   0x00d25e10  cCreatureCamera::UpdateAvatarAlpha()
//   0x00d26030  cCreatureCamera::FUN_00d26030()
//   0x00d263d0  cCreatureCamera::SetCameraMode(int)
//   0x00d265c0  rotateTransform(cSPTransformOps*,int,float)
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <math.h>
#include "types.h"

#ifndef nullptr
#define nullptr 0
#endif

#pragma intrinsic(fabs)

struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };
struct Matrix3 { float m[9]; void Assign(const Matrix3& src); };

// cTransform: +0x00 flags(word), +0x02 modcount(word), +0x04 translation, +0x10 scale, +0x14 rotation
struct cTransform {
    uint16_t mFlags;              // +0x00
    uint16_t mModificationCount;  // +0x02
    Vec3     mTranslation;        // +0x04
    float    mScale;              // +0x10
    Matrix3  mRotation;           // +0x14
};

// cLocalInputState: embedded at camera +0x2bc (>= 0x58 bytes).
struct cLocalInputState {
    uint8_t pad00[0x2c];
    float   mKeys7;               // +0x2c
    float   mModifiers;           // +0x30
    uint8_t pad34[0x50 - 0x34];
    int     mMouseDownModifiers;  // +0x50
    int     mMouseWheelDelta;     // +0x54
    void OnMouseWheel(float, float, int);   // 0x00697b20
};

class cGameNounManager;
cGameNounManager* __cdecl NounManager();                    // 0x00b3d300
struct cGameNounManager {
    void* GetAvatar();                                       // 0x00b1fdb0
};

struct IPlanetTerrain;
struct cPlanetModel;
cPlanetModel* __cdecl PlanetModel();                        // 0x00b3d350
struct cPlanetModel {
    uint8_t pad00[0x24];
    IPlanetTerrain* mpISphere;                               // +0x24
    float GetRadiusAt(const Vec3* v);                        // 0x00b7ef70
    float GetWaterHeight();                                  // 0x00b7e390
    float SurfaceDistance(const Vec3* a, const Vec3* b);     // 0x00b82e80
    void* FUN_00b82060(const void* a, const void* b, const void* c); // 0x00b82060
};

// Object stored at cCreatureModeStrategy +0x64.
struct cCreatureModeState {
    uint8_t pad00[0x54];
    uint8_t mb54;                    // +0x54
    uint8_t pad55[0xc0 - 0x55];
    uint8_t mbC0;                    // +0xc0
};

struct cCreatureModeStrategy {
    uint8_t pad00[0x64];
    cCreatureModeState* mpState;     // +0x64
    static cCreatureModeStrategy* Instance();                // 0x00d38840
};

// Avatar sub-object reached through avatar +0xc0; GetRadius at vtable slot 0x74.
struct IAvatarSub {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28();
    virtual float GetRadius();                               // +0x74
};

// Visual object pointed to by avatar +0xb54; alpha at +0x80.
struct cAvatarVisual {
    uint8_t pad00[0x80];
    float   mAlpha;                                          // +0x80
};

// Game avatar noun.
struct cGameAvatar {
    uint8_t pad00[0xc0];
    IAvatarSub*   mpSub;                                     // +0xc0
    uint8_t padC4[0x135 - 0xc4];
    uint8_t mb135;                                            // +0x135
    uint8_t pad136[0xb54 - 0x136];
    cAvatarVisual* mpVisual;                                  // +0xb54
    uint32_t mFlagsB58;                                       // +0xb58
};

struct cSPTransformOps {
    void* Assign(const void* src);                           // 0x00537dc0
};

// rotateTransform helpers.
struct cXform      { void PreRotateX(float angle); };                       // 0x005a2d90
namespace EA { namespace Swarm { struct cTransform { void PreRotateY(float angle); }; } } // 0x004099b0
struct cTransformCompose { void ComposeTransforms(const void* src); };       // 0x0040ccb0

void  Matrix3_Assign_dummy();                              // unused
void* FUN_008d3110();                                        // 0x008d3110
void* FUN_0067cab0(int v);                                   // 0x0067cab0
void  FUN_00801930(void* obj);                               // 0x00801930
void  FUN_00b7f1f0(void* dst, const void* a, const void* b); // 0x00b7f1f0
void  FUN_00d20880_f(void* self, void* a, void* b);          // 0x00d20880
void  GetCursorPosition(int* x, int* y);                     // 0x008d2f30

// globals
extern float g_169deb0;   extern float g_169deb4;   extern float g_169deb8;
extern float g_169de90;   extern float g_169de94;   extern float g_169de98;
extern float g_169dea8;
extern Matrix3 g_169df20;
extern float g_169df44;   extern float g_169df48;   extern float g_169df4c;
extern float g_169df50;   extern float g_169df54;   extern float g_169df58;
extern float g_147a304;
extern float g_147a334;
extern float g_13eb8c8;
extern float g_15827f0;
extern float g_1485720;
extern uint8_t g_1582786;
extern uint8_t g_169defc;

namespace SP {

class cCreatureCamera {
public:
    void UpdateCamera(float dt);                    // 0x00d25ca0
    void OnMouseMove(float f1, float f2, int i3);   // 0x00d25ac0
    void FUN_00d25e00();                            // 0x00d25e00
    void UpdateAvatarAlpha();                       // 0x00d25e10
    void FUN_00d26030();                            // 0x00d26030
    void SetCameraMode(int mode);                   // 0x00d263d0
    void FUN_00d21bc0(float, float, float);         // 0x00d21bc0
    void UpdateCamera_Free();                       // 0x00d21d90

    uint8_t pad00[0x10];
    bool    mbEnableInput;              // +0x10
    Vec2    mInputConst;               // +0x14
    uint8_t pad1c[0x38 - 0x1c];
    Vec3    mReferenceHeading;         // +0x38
    uint8_t pad44[0x48 - 0x44];
    Vec3    mV48;                      // +0x48
    Vec3    mV54;                      // +0x54
    Vec4    mV60;                      // +0x60
    Vec3    mV70;                      // +0x70
    Vec3    mV7c;                      // +0x7c
    Vec3    mV88;                      // +0x88
    Vec3    mV94;                      // +0x94
    Vec3    mVa0;                      // +0xa0
    Vec3    mVac;                      // +0xac
    Vec3    mVb8;                      // +0xb8
    Vec3    mVc4;                      // +0xc4
    uint8_t padD0[0xec - 0xd0];
    float   mFieldEC;                  // +0xec
    uint8_t padF0[0xf8 - 0xf0];
    float   mFieldF8;                  // +0xf8
    float   mFieldFC;                  // +0xfc
    float   mField100;                 // +0x100
    uint8_t pad104[0x108 - 0x104];
    Vec3    mV108;                     // +0x108
    Vec3    mV114;                     // +0x114
    Vec3    mV120;                     // +0x120
    uint8_t pad12c[0x13c - 0x12c];
    Vec3    mV13C;                     // +0x13c
    Vec3    mV148;                     // +0x148
    Vec4    mV154;                     // +0x154
    uint8_t pad164[0x174 - 0x164];
    float   mF174;                     // +0x174
    float   mF178;                     // +0x178
    float   mF17C;                     // +0x17c
    float   mF180;                     // +0x180
    float   mF184;                     // +0x184
    float   mF188;                     // +0x188
    uint8_t pad18c[0x19c - 0x18c];
    bool    mb19C;                     // +0x19c
    uint8_t pad19d[0x1c8 - 0x19d];
    Vec3    mV1C8;                     // +0x1c8
    Vec4    mV1D4;                     // +0x1d4
    float   mF1E4;                     // +0x1e4
    int     mI1E8;                     // +0x1e8
    int     mI1EC;                     // +0x1ec
    uint8_t pad1f0[0x1f8 - 0x1f0];
    float   mMouseSensitivityX;        // +0x1f8
    float   mMouseSensitivityY;        // +0x1fc
    uint8_t pad200[0x208 - 0x200];
    Vec2    mPitchLimits;             // +0x208
    float   mMinCameraPhi;             // +0x210
    uint8_t pad214[0x220 - 0x214];
    float   mInitialDistance;          // +0x220
    uint8_t pad224[0x258 - 0x224];
    float   mInterpolateAnchorMultiplier; // +0x258
    float   mField25C;                 // +0x25c
    cTransform mCameraToWorld;         // +0x260
    uint8_t pad298[0x2b8 - 0x298];
    float   mLftMouseDownDuration;     // +0x2b8
    cLocalInputState mLocalInputState; // +0x2bc
    bool    mb314;                     // +0x314
};

} // namespace SP

using namespace SP;

// @ 0x00d25e00
void cCreatureCamera::FUN_00d25e00()
{
    UpdateCamera(mFieldFC);
}

// @ 0x00d25ca0
void cCreatureCamera::UpdateCamera(float dt)
{
    UpdateCamera_Free();
    g_1582786 = g_169defc;

    float zero = 0.0f;
    mFieldF8  = zero;
    mF174     = zero;
    mFieldEC  = zero;

    mV48.x = mVa0.x - mVb8.x;
    mV48.y = mVa0.y - mVb8.y;
    mV48.z = mVa0.z - mVb8.z;

    mV13C = mV48;
    mReferenceHeading = mVb8;
    mV60 = mV1D4;
    mV154 = mV1D4;

    mFieldFC = dt * g_147a304;
    mF178    = mFieldFC;

    mFieldF8 = g_169de94 * g_147a304;
    mF174    = mFieldF8;

    mField100 = g_169de98;
    mF17C     = mField100;
}

// @ 0x00d25ac0
void cCreatureCamera::OnMouseMove(float f1, float f2, int i3)
{
    float savedKeys = mLocalInputState.mKeys7;
    float savedMods = mLocalInputState.mModifiers;

    mLocalInputState.OnMouseWheel(f1, f2, i3);

    if (mb314) {
        mInputConst.x += (float)fabs(mLocalInputState.mKeys7 - savedKeys);
        mInputConst.y += (float)fabs(mLocalInputState.mModifiers - savedMods);
    }

    if (mbEnableInput && mb314) {
        int cx, cy;
        GetCursorPosition(&cx, &cy);

        float dx = -((float)(cx - mLocalInputState.mMouseDownModifiers) * mMouseSensitivityX);
        float dy =  ((float)(cy - mLocalInputState.mMouseWheelDelta)  * mMouseSensitivityY);

        void* obj = FUN_008d3110();
        void* sub = ((void*(__fastcall*)(void*, int, int))(*(void***)obj)[5])(obj, 2, 0);
        ((void(__fastcall*)(void*, int, int, int))(*(void***)sub)[6])(
            sub, mLocalInputState.mMouseDownModifiers, mLocalInputState.mMouseWheelDelta, 0);

        if (mI1EC == 2) {
            float ny = mF184 + dy;
            FUN_00d21bc0(mF180 + dx, ny, mF188);
            mF184 = ny;
            return;
        }

        mF174 += dx;
        float v = mF178 + dy;
        if (v < mPitchLimits.x)
            v = mPitchLimits.x;
        if (v > mPitchLimits.y)
            v = mPitchLimits.y;
        mF178 = v;
    }
}

// @ 0x00d25e10
void cCreatureCamera::UpdateAvatarAlpha()
{
    float k0 = g_169deb0;
    float k1 = g_169deb4;
    float k2 = g_169deb8;

    if (mCameraToWorld.mFlags & 2) {
        const Matrix3& r = mCameraToWorld.mRotation;
        k0 = r.m[6] * g_169deb8 + r.m[3] * g_169deb4 + r.m[0] * g_169deb0;
        k1 = r.m[7] * g_169deb8 + r.m[4] * g_169deb4 + r.m[1] * g_169deb0;
        k2 = r.m[8] * g_169deb8 + r.m[5] * g_169deb4 + r.m[2] * g_169deb0;
    }

    float px = mCameraToWorld.mTranslation.x + mCameraToWorld.mScale * k0;
    float py = mCameraToWorld.mTranslation.y + mCameraToWorld.mScale * k1;
    float pz = mCameraToWorld.mTranslation.z + mCameraToWorld.mScale * k2;

    cGameAvatar* avatar = (cGameAvatar*)NounManager()->GetAvatar();
    if (avatar == nullptr || avatar->mb135 == 0)
        return;

    float dx = px - mVa0.x;
    float dy = py - mVa0.y;
    float dz = pz - mVa0.z;

    float r1 = avatar->mpSub->GetRadius();
    float dist = (float)sqrt((dz * dz + dy * dy) + dx * dx) - r1;

    float r2 = avatar->mpSub->GetRadius();
    float denom = mMinCameraPhi - r2;
    float t = dist / denom;

    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    float out = (t <= g_147a334) ? 0.0f : g_1485720;
    avatar->mpVisual->mAlpha = out;

    if (out < g_1485720)
        avatar->mFlagsB58 |= 0x800;
    else
        avatar->mFlagsB58 &= ~0x800u;
}

// @ 0x00d263d0
void cCreatureCamera::SetCameraMode(int mode)
{
    mI1EC = mode;

    if (mode == 2) {
        uint8_t b = g_1582786;
        void* local[4];
        cPlanetModel* planet;
        g_169defc = b;
        g_1582786 = 0;
        planet = PlanetModel();
        FUN_00b7f1f0(local, &mV1C8, &mV1D4);
        FUN_00d20880_f(this, &mV1C8, local);
    } else {
        void* obj = FUN_0067cab0(1);
        FUN_00801930(obj);
        UpdateCamera_Free();
        g_1582786 = g_169defc;

        float zero = 0.0f;
        mFieldF8 = zero;
        mF174    = zero;
        mFieldEC = zero;

        mV48.x = mVa0.x - mVb8.x;
        mV48.y = mVa0.y - mVb8.y;
        mV48.z = mVa0.z - mVb8.z;

        mV13C.x = mV48.x;
        mV13C.y = mV48.y;
        mV13C.z = mV48.z;

        mReferenceHeading.x = mVb8.x;
        mReferenceHeading.y = mVb8.y;
        mReferenceHeading.z = mVb8.z;

        mV60.x = mV1D4.x;
        mV60.y = mV1D4.y;
        mV60.z = mV1D4.z;
        mV60.w = mV1D4.w;

        mV154.x = mV1D4.x;
        mV154.y = mV1D4.y;
        mV154.z = mV1D4.z;
        mV154.w = mV1D4.w;

        mFieldFC = g_169de90 * g_147a304;
        mF178    = g_169de90 * g_147a304;

        mFieldF8 = g_169de94 * g_147a304;
        mF174    = g_169de94 * g_147a304;

        mField100 = g_169de98;
        mF17C     = mField100;
    }

    cCreatureModeStrategy* s = cCreatureModeStrategy::Instance();
    cCreatureModeState* p = s->mpState;
    if (p != nullptr) {
        if (p->mb54 != 0)
            p->mbC0 = (uint8_t)(mI1EC != 2);
    }
}

// @ 0x00d265c0
void rotateTransform(cSPTransformOps* out, int axis, float angle)
{
    cTransform xf;
    xf.mFlags = 0;
    xf.mModificationCount = 0;
    xf.mTranslation.x = g_169deb0;
    xf.mTranslation.y = g_169deb4;
    xf.mTranslation.z = g_169deb8;
    xf.mScale = 1.0f;
    xf.mRotation.Assign(g_169df20);

    if (axis == 0)
        ((cXform*)&xf)->PreRotateX(-angle);
    else
        ((EA::Swarm::cTransform*)&xf)->PreRotateY(angle);

    cTransform copy;
    copy.mFlags = xf.mFlags;
    copy.mModificationCount = xf.mModificationCount;
    copy.mTranslation.x = xf.mTranslation.x;
    copy.mTranslation.y = xf.mTranslation.y;
    copy.mTranslation.z = xf.mTranslation.z;
    copy.mScale = xf.mScale;
    copy.mRotation.Assign(xf.mRotation);

    ((cTransformCompose*)&copy)->ComposeTransforms(out);
    out->Assign(&copy);
}

// @ 0x00d26030
void cCreatureCamera::FUN_00d26030()
{
    cPlanetModel* planet = PlanetModel();
    if (planet == 0 || planet->mpISphere == 0)
        return;

    float yv  = mV108.y;
    float xv  = mV108.x;
    float zv  = mV108.z;
    float kx  = g_169df54;
    float ky  = g_169df50;
    float kz  = g_169df58;

    float d = mInitialDistance;

    Vec3 a;
    a.x = d * g_169df44 + xv;
    a.y = d * g_169df48 + yv;
    a.z = d * g_169df4c + zv;

    float t = (float)tanf(mInterpolateAnchorMultiplier) * d;

    Vec3 b;
    b.x = kx * t + a.x;
    b.y = ky * t + a.y;
    b.z = kz * t + a.z;

    Vec3 c;
    c.x = a.x - kx * t;
    c.y = a.y - ky * t;
    c.z = a.z - kz * t;

    float rOrig = planet->GetRadiusAt(&mV108);
    float rA    = planet->GetRadiusAt(&a);
    float water = planet->GetWaterHeight();
    if (water > rA) rA = water;
    float rB = planet->GetRadiusAt(&b);
    if (water > rB) rB = water;
    float rC = planet->GetRadiusAt(&c);
    if (water > rC) rC = water;

    float* p2;
    float* p3;
    if (rC > rB) { p2 = &rC; p3 = &rB; }
    else         { p2 = &rB; p3 = &rC; }
    if (*p2 <= rOrig) { float* tmp = p2; p2 = &rOrig; p3 = tmp; }
    if (*p2 > *p3) p3 = p2;

    float t2 = (float)tanf(mField25C) * d + *p3 + g_15827f0;

    Vec3 delta;
    delta.x = xv - mV114.x;
    delta.y = yv - mV114.y;
    delta.z = zv - mV114.z;

    float mag2 = zv * zv + yv * yv + xv * xv;

    Vec3 res;
    planet->FUN_00b82060(&res, &mV114, &delta);

    if (mag2 < t2 * t2)
        goto clear;
    if (res.x == g_169deb0 && res.y == g_169deb4 && res.z == g_169deb8)
        return;

    {
        float ex = res.x - mV114.x;
        float ey = res.y - mV114.y;
        float ez = res.z - mV114.z;
        float emag = ez * ez + ey * ey + ex * ex;
        if (emag <= (delta.z * delta.z + delta.y * delta.y + delta.x * delta.x)) {
            if (planet->SurfaceDistance(&res, &delta) > g_13eb8c8 || mb19C) {
                mV108.x = res.x;
                mV108.y = res.y;
                mV108.z = res.z;
                mb19C = true;
                return;
            }
        }
    }
clear:
    mb19C = false;
}
