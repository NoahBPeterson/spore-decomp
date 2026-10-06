// Slice s00780b70: the per-frame update of the shadow-map system, a thiscall method on the
// cShadowWorld secondary-base subobject at cShadowWorld+8 (`this`; the world is `this - 8`).
// It polls the app properties, rebuilds the render shadow when they change, then samples the
// distance curves, steers the light direction toward the target, positions the shadow camera(s)
// and refreshes the shader constants.  Retail layout (differs from the 2008 dev PDB).
// Module: /O2 /MD /Gy /EHsc /TP /arch:SSE.
#include "types.h"
#include <math.h>
#pragma intrinsic(sqrt, fabs, tan)

struct Vec3 { float x, y, z; };

// A 3x3 matrix whose copy constructor is the out-of-line Matrix3::Assign (0x41cb40).
struct Mat33 {
    float m[9];
    Mat33(const Mat33& o);                                    // @ 0x41cb40
};
struct Mat44 { float m[16]; };

// The properties list: the modification counter lives behind a tracker pointer at +0x30.
struct cModTracker {
    int GetModificationCount();                               // @ 0x6237a0
};
struct cPropertyList {
    char pad00[0x30];
    cModTracker* mpTracker;                                   // +0x30
    int mLocalVersion;                                        // +0x34
    bool GetDescription(uint32_t key);                        // @ 0x6a25a0
    __forceinline int GetVersion() { return (mpTracker ? mpTracker->GetModificationCount() : 0) + mLocalVersion; }
};
extern cPropertyList* g_AppProperties;                        // @ 0x15fd918

// One viewer of the convolution shadow renderer (stride 0x174).
struct cViewer {
    char pad00[0x40];
    Mat44 mViewMatrix;                                        // +0x40
    char pad80[0xc0 - 0x80];
    Mat44 mProjMatrix;                                        // +0xc0
    char pad100[0x174 - 0x100];
    void SetTransform(const void* xform);                     // @ 0x7c4d00
    void SetNear(float n);                                    // @ 0x7c4ba0
    void SetFar(float f);                                     // @ 0x7c4bc0
    void SetViewAngleY(float a);                              // @ 0x7c53d0
    void SetViewWindow(float w, float h);                     // @ 0x7c5440
    void GetViewWindow(float* w, float* h);                   // @ 0x7c40c0
    void SetViewScale(float w, float h);                      // @ 0x7c4b00
    void ProjectPoint(Vec3* out, const Vec3* p);              // @ 0x7c4180
    void SetViewShift(float x, float y);                      // @ 0x7c4ad0
};

struct cRenderConvolutionShadow {
    char pad00[0xc];
    cViewer mViewers[3];                                      // +0x0c
    char pad468[4];
    bool mUseConvolution;                                     // +0x46c
    int mNumViewers;                                          // +0x470
    int mFrame;                                               // +0x474
    bool mSliced;                                             // +0x478
};

struct IShadowManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual void SetRenderShadow(cRenderConvolutionShadow* rs, int param, int flags);   // 0x4c
};
IShadowManager* GetShadowManager();                           // @ 0x67dd50

struct cShadowWorld {
    void Cleanup();                                           // @ 0x7806a0
    void Update();                                            // @ 0x780ab0
    void RefreshShadowMaterial();                             // @ 0x77f640
    void SetLightingWorld();                                  // @ 0x77f6a0
};

float SampleCurve(int size, const float* curve, float t);     // @ 0x77eef0
float Clamp01(float v);                                       // @ 0x5a6e00
void  Transpose(Mat44* out, const Mat44* in);                 // @ 0x6ffdc0 (cdecl, returns out)
void  ReportError(int code, int a, int b);                    // @ 0x777ae0

extern const float g_FovToTan;                                // @ 0x153a108
extern const float g_DotToStrength;                           // @ 0x153a2f0
extern const float g_BiasScale;                               // @ 0x1633bc4
extern const Vec3  g_CameraBase;                              // @ 0x1633bd0
extern const Vec3  g_AxisUp;                                  // @ 0x153a124
extern const Mat33 g_IdentityRot;                             // @ 0x1633d14
extern const bool  g_UseViewWindow;                           // @ 0x153a2ec

// The shadow camera transform, built inline and then oriented by 0x6bac90.
struct cShadowXform {
    uint16_t mFlags;                                          // +0x00
    uint16_t mModCount;                                       // +0x02
    Vec3 mTranslation;                                        // +0x04
    float mScale;                                             // +0x10
    Mat33 mRotation;                                          // +0x14
    uint32_t pad38[2];
    __forceinline cShadowXform(const Vec3& t, const Mat33& r) : mFlags(0), mModCount(0), mTranslation(t), mScale(1.0f), mRotation(r) {}
    void LookAlong(const Vec3& up, const Vec3& dir);          // @ 0x6bac90
};

struct cShadowUpdater {
    void** mVtbl;                                             // +0x00 (slot 0x50: OnShadowsUpdated)
    bool mHasTarget;                                          // +0x04
    bool mEnabled;                                            // +0x05
    bool mUpdateEnabled;                                      // +0x06
    char pad07[5];
    bool mConvolution;                                        // +0x0c
    bool mFlagD;                                              // +0x0d
    char pad0e[2];
    int mUserParam;                                           // +0x10
    char pad14[0x2c];
    float mDepthBase;                                         // +0x40
    float mDepthScale;                                        // +0x44
    float mStrength;                                          // +0x48
    float mOne;                                               // +0x4c
    Vec3 mLightDir;                                           // +0x50
    float mLightBias;                                         // +0x5c
    float mFocusScaleA;                                       // +0x60
    float mFocusScaleB;                                       // +0x64
    float mShiftX;                                            // +0x68
    float mShiftY;                                            // +0x6c
    Mat44 mLightMatrix;                                       // +0x70
    float mViewMatrix[12];                                    // +0xb0
    char pade0[0x164 - 0xe0];
    Vec3 mShadowDirection;                                    // +0x164
    Vec3 mTargetShadowDirection;                              // +0x170
    Vec3 mTargetLocation;                                     // +0x17c
    Vec3 mTargetUp;                                           // +0x188
    Vec3 mViewerLocation;                                     // +0x194
    float mShadowScale;                                       // +0x1a0
    float mFocus;                                             // +0x1a4
    Vec3 mCameraOffset;                                       // +0x1a8
    cRenderConvolutionShadow* mRenderShadow;                  // +0x1b4
    int mCachedVersion;                                       // +0x1b8
    char pad1bc[4];
    float mRangeMin;                                          // +0x1c0
    float mRangeMax;                                          // +0x1c4
    float mFocusMin;                                          // +0x1c8
    float mFocusMax;                                          // +0x1cc
    float mCasterRadiusScale;                                 // +0x1d0
    char pad1d4[4];
    int mScaleCurveSize; float* mScaleCurve;                  // +0x1d4  (scale curve)
    int mStrengthCurveSize; float* mStrengthCurve;            // +0x1dc
    int mDepthCurveSize; float* mDepthCurve;                  // +0x1e4
    int mCasterCurveSize; float* mCasterCurve;                // +0x1ec
    int mFocusCurveSize; float* mFocusCurve;                  // +0x1f4
    float mLightBiasScale;                                    // +0x1fc
    float mLightDirScale;                                     // +0x200
    float mDotSnap;                                           // +0x204
    float mTargetSnap;                                        // +0x208
    char pad20c[4];
    float mShadowDirLerp;                                     // +0x210
    float mScaleSnap;                                         // +0x214
    int mManagerParam;                                        // +0x218

    __forceinline cShadowWorld* World() { return (cShadowWorld*)((char*)this - 8); }
    __forceinline void OnShadowsUpdated(int param) { ((void (__thiscall*)(cShadowUpdater*, int))mVtbl[0x50 / 4])(this, param); }
    void UpdateShadows();                                     // @ 0x780b70
};

// @ 0x00780b70
void cShadowUpdater::UpdateShadows()
{
    cPropertyList* props = g_AppProperties;
    bool enabled = props->GetDescription(0x276abef) && props->GetDescription(0x276abf0);
    if (enabled != mEnabled) {
        if (!enabled) {
            if (mRenderShadow != 0)
                World()->Cleanup();
        } else if (mRenderShadow == 0) {
            World()->Update();
        }
        mEnabled = enabled;
    }

    bool active;
    if (!mEnabled || !mHasTarget) {
        active = false;
    } else {
        active = true;
        World()->SetLightingWorld();
    }
    World()->RefreshShadowMaterial();

    if (!active || !mUpdateEnabled) {
        ReportError(0x223, 0, 0);
        return;
    }

    // Re-read the property flags whenever the property list was modified.
    props = g_AppProperties;
    if (mCachedVersion != props->GetVersion()) {
        mCachedVersion = props->GetVersion();
        bool convolution = props->GetDescription(0x276abf8);
        bool flagB = props->GetDescription(0x5879277);
        bool flagD = props->GetDescription(0x65a8c87);
        if (mConvolution != convolution || mRenderShadow->mUseConvolution != flagB || mFlagD != flagD) {
            World()->Cleanup();
            World()->Update();
            GetShadowManager()->SetRenderShadow(mRenderShadow, mManagerParam, 0);
        }
    }

    // Distance from the viewer to the shadow target, mapped through the curves.
    Vec3 toViewer;
    toViewer.x = mViewerLocation.x - mTargetLocation.x;
    toViewer.y = mViewerLocation.y - mTargetLocation.y;
    toViewer.z = mViewerLocation.z - mTargetLocation.z;
    float dist = (float)sqrt((double)(toViewer.z * toViewer.z + toViewer.y * toViewer.y + toViewer.x * toViewer.x));
    float u = (dist - mRangeMin) / (mRangeMax - mRangeMin);
    float t = 0.0f;
    if (0.0f <= u) t = u;
    if (1.0f <= t) t = 1.0f;

    float strength = SampleCurve(mStrengthCurveSize, mStrengthCurve, t);
    float scaleTarget = SampleCurve(mScaleCurveSize, mScaleCurve, t);
    if (mScaleSnap < fabs((double)(mShadowScale - scaleTarget)))
        mShadowScale = (float)scaleTarget;

    // Steer the shadow direction toward the target direction, then renormalise it.
    float lerp = mShadowDirLerp;
    float inv = 1.0f - lerp;
    float dx = mTargetShadowDirection.x * lerp + mShadowDirection.x * inv;
    float dy = mTargetShadowDirection.y * lerp + mShadowDirection.y * inv;
    float dz = mTargetShadowDirection.z * lerp + mShadowDirection.z * inv;
    mShadowDirection.x = dx;
    mShadowDirection.y = dy;
    mShadowDirection.z = dz;
    float invLen = 1.0f / (float)sqrt((double)(dz * dz + (dy * dy + dx * dx)));
    mShadowDirection.x = invLen * dx;
    mShadowDirection.y = invLen * dy;
    mShadowDirection.z = invLen * dz;

    float dot = (mShadowDirection.z * mTargetUp.z + mShadowDirection.y * mTargetUp.y) + mShadowDirection.x * mTargetUp.x;
    float s = (float)fabs((double)dot) * g_DotToStrength;
    float dotFactor = 0.0f;
    if (0.0f <= s) dotFactor = s;
    if (1.0f <= dotFactor) dotFactor = 1.0f;
    strength = dotFactor * strength;
    if (dot < mDotSnap)
        mShadowDirection = mTargetUp;

    float casterDist = SampleCurve(mCasterCurveSize, mCasterCurve, t);
    float camDist = SampleCurve(mDepthCurveSize, mDepthCurve, t);
    if (camDist - 0.01f < casterDist)
        casterDist = camDist - 0.01f;
    float nearLimit = dist;
    if (casterDist <= dist)
        nearLimit = casterDist;

    float angle = mShadowScale;
    double tanValue = tan((double)g_FovToTan * 0.0027777778 * angle);
    float window = (float)(tanValue * camDist);
    if (nearLimit <= window)
        nearLimit = window;
    float farSpan = camDist + casterDist;

    // Aim the camera so the target stays inside the window.
    float along = (mTargetUp.z * toViewer.y + mTargetUp.y * toViewer.z) + mTargetUp.x * toViewer.x;
    float perpSq = dist * dist - along * along;
    float perp = 0.0f;
    if (0.0f <= perpSq) perp = perpSq;
    float room = (float)((tanValue * camDist) * mCasterRadiusScale - sqrt((double)perp));
    float roomClamped = 0.0f;
    if (0.0f <= room) roomClamped = room;
    float invDist = 1.0f / (dist + 1e-06f);
    Vec3 aim;
    aim.x = (-(toViewer.x - mTargetUp.x * along) * roomClamped) * invDist;
    aim.y = (-(toViewer.y - mTargetUp.y * along) * roomClamped) * invDist;
    aim.z = (-(toViewer.z - mTargetUp.z * along) * roomClamped) * invDist;
    float aimDx = aim.x - mCameraOffset.x;
    float aimDy = aim.y - mCameraOffset.y;
    float aimDz = aim.z - mCameraOffset.z;
    if (mTargetSnap * mTargetSnap < (aimDz * aimDz + aimDy * aimDy) + aimDx * aimDx)
        mCameraOffset = aim;

    cRenderConvolutionShadow* rs = mRenderShadow;
    float bias = (((mShadowDirection.z * mCameraOffset.z + mShadowDirection.y * mCameraOffset.y)
                   + mCameraOffset.x * mShadowDirection.x)) * g_BiasScale;
    float nearA = bias + (camDist - casterDist);
    float farA = bias + farSpan;
    float nearB = bias + (camDist - nearLimit);
    float farB = bias + (nearLimit + camDist);
    float shiftX = 0.0f;
    float shiftY = 0.0f;

    if (!rs->mSliced || rs->mFrame % rs->mNumViewers == 0) {
        if (!mConvolution) {
            mFocus = 1.0f;
        } else {
            float lo = mFocusMin;
            if (mFocusMax <= lo) {
                mFocus = SampleCurve(mFocusCurveSize, mFocusCurve, t);
            } else {
                float f = Clamp01((dist - lo) / (mFocusMax - lo));
                mFocus = 1.0f / SampleCurve(mFocusCurveSize, mFocusCurve, f);
            }
        }
        float invFocus = 1.0f / mFocus;

        cShadowXform xform(g_CameraBase, g_IdentityRot);
        Vec3 negDir;
        negDir.x = -mShadowDirection.x;
        negDir.y = -mShadowDirection.y;
        negDir.z = -mShadowDirection.z;
        xform.LookAlong(g_AxisUp, negDir);
        xform.mFlags |= 4;
        xform.mModCount++;
        xform.mTranslation.x = ((mShadowDirection.x * camDist + mTargetLocation.x) + mCameraOffset.x) + xform.mTranslation.x;
        xform.mTranslation.y = (mCameraOffset.y + (mTargetLocation.y + mShadowDirection.y * camDist)) + xform.mTranslation.y;
        xform.mTranslation.z = (mCameraOffset.z + (mTargetLocation.z + mShadowDirection.z * camDist)) + xform.mTranslation.z;

        for (int i = 0; i < rs->mNumViewers; i++) {
            cViewer* v = &rs->mViewers[i];
            v->SetTransform(&xform);
            v->SetNear(bias + nearA);
            v->SetFar(bias + farA);
            if (!g_UseViewWindow)
                v->SetViewAngleY(angle);
            else
                v->SetViewWindow((float)(tanValue * camDist), (float)(tanValue * camDist));
            if (i == 0 && mFocus >= 1.5f) {
                float w, h;
                v->GetViewWindow(&w, &h);
                w = w * invFocus;
                h = h * invFocus;
                v->SetViewScale(w, h);
                float sx, sy;
                if (mCasterRadiusScale <= 0.0f) {
                    sx = 0.0f;
                    sy = 0.0f;
                } else {
                    Vec3 p0, p1, probe;
                    v->ProjectPoint(&p0, &mTargetLocation);
                    probe.x = mTargetLocation.x + mCameraOffset.x;
                    probe.y = mTargetLocation.y + mCameraOffset.y;
                    probe.z = mTargetLocation.z + mCameraOffset.z;
                    v->ProjectPoint(&p1, &probe);
                    shiftY = p0.y - p1.y;
                    shiftX = p0.x - p1.x;
                    sy = -(h * shiftY);
                    sx = -(w * shiftX);
                }
                v->SetViewShift(sx, sy);
            }
        }
        OnShadowsUpdated(mUserParam);
    }

    rs = mRenderShadow;
    if (!rs->mSliced || rs->mFrame % rs->mNumViewers == 1) {
        float farPlane = bias + (nearLimit + camDist);
        float nearPlane = nearB;
        Mat44 m = rs->mViewers[0].mProjMatrix;
        Mat44 tmp;
        Transpose(&tmp, &m);
        m = tmp;
        mLightMatrix = m;
        Mat44 m2 = rs->mViewers[0].mViewMatrix;
        Transpose(&tmp, &m2);
        m2 = tmp;
        for (int k = 0; k < 12; k++)
            mViewMatrix[k] = m2.m[k];

        mDepthBase = bias + nearPlane;
        mOne = 1.0f;
        mDepthScale = 1.0f / (farPlane - nearPlane);
        mStrength = strength;
        mFocusScaleA = 1.0f / mFocus;
        mFocusScaleB = 1.0f / mFocus;
        mShiftX = shiftX;
        mShiftY = shiftY;
    }
    mLightDir.x = mLightDirScale * mShadowDirection.x;
    mLightDir.y = mShadowDirection.y * mLightDirScale;
    mLightDir.z = mShadowDirection.z * mLightDirScale;
    mLightBias = -(mLightBiasScale * mLightDirScale);
}
