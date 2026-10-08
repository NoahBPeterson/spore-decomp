// slice s00eb73f0 -- camera controller (spline-based "pull back"/zoom transition):
//   0x00eb73f0  builds the position/zoom/orientation Hermite tracks for the current transition
//   0x00eb7b30  message handler (target position, orientation, zoom messages)
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), same module as s00eb4420.
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

// One float vector (EASTL-like: begin, end, cap, allocator) -- 0x14 bytes.
struct FloatVec {
    float* mpBegin;
    float* mpEnd;
    char   pad[0x0c];
    void resize(unsigned n);          // 0x004afc80
    float& operator[](int i) { return mpBegin[i]; }
};
struct Vec3Vec {
    Vec3* mpBegin;
    Vec3* mpEnd;
    char  pad[0x0c];
    void resize(int n);               // 0x00473810
    Vec3& operator[](int i) { return mpBegin[i]; }
};
struct QuatVec {
    Quat* mpBegin;
    Quat* mpEnd;
    char  pad[0x0c];
    void resize(unsigned n);          // 0x00b15a20
    Quat& operator[](int i) { return mpBegin[i]; }
};
// Hermite tracks: times, values, tangents.
struct Track1 {
    FloatVec t, v, s;
    void Clear();                     // 0x0069d090
    void ComputeSlopes();             // 0x0069a4c0
};
struct Track3 {
    FloatVec t;
    Vec3Vec  v, s;
    void Clear();                     // 0x0069d100
    void ComputeTangents();           // 0x0069a750
};
struct TrackQ {
    FloatVec t;
    QuatVec  v, s;
    void Clear();                     // 0x0069d150
    void ComputeTangents();           // 0x0069ac00
};

struct Grid { float Scale(); };       // 0x00f987f0 (thiscall, float result)
Grid*  __cdecl DebugDrawGrid();       // 0x00f48aa0
#pragma intrinsic(acos, fabs)

extern Vec3 gZeroVec;                 // 0x016c7284
extern Quat gZeroQuat;                // 0x016c7290
extern float gAxisX;                  // 0x015a9424
extern float gAxisY;                  // 0x015a9428
extern float gAxisZ;                  // 0x015a942c
extern Vec3  gAltAxis;                // 0x015a940c
extern float gTwo;                   // 0x015a93f8
extern float gMaxVal;               // 0x015a93fc

Vec3* __cdecl RotateTowards(Vec3* out, const Vec3* a, const Vec3* b, float t);          // 0x00b0fd00
void __cdecl Quat_Blend(Quat* out, Vec3* a, Vec3* b, Quat* q, Vec3* v);                 // 0x00eb5c00

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
static inline float Dot3(const Vec3& a, const Vec3& b)
{
    return a.x * b.x + (a.y * b.y + a.z * b.z);
}
static inline float Deg2Rad(float d) { return d * 0.017453292f; }

struct CamBlend {
    char  pad00[0x14];
    int   mMode;                 // +0x14
    char  pad18[0x30 - 0x18];
    float mLo;                   // +0x30
    float mHi;                   // +0x34
    char  pad38[0x78 - 0x38];
    char  mbDone;                // +0x78
    char  pad79[0x8c - 0x79];
    Vec3  mDirA;                 // +0x8c
    Vec3  mDirB;                 // +0x98
    char  pada4[0xf0 - 0xa4];
    float mZoomA;                // +0xf0
    float mZoomB;                // +0xf4
    char  padf8[0x140 - 0xf8];
    Quat  mQ1;                   // +0x140
    Quat  mQ2;                   // +0x150
    char  pad160[0x178 - 0x160];
    Vec3  mUp;                   // +0x178
    char  pad184[0x1b0 - 0x184];
    Track1 mTrZoom;              // +0x1b0
    Track1 mTrFov;               // +0x1ec
    Track3 mTrDir;               // +0x228
    TrackQ mTrQuat;              // +0x264
    char  pad2a0[0x2e8 - 0x2a0];
    float mThreshold;            // +0x2e8
    float mMinAngle;             // +0x2ec

    void Build();                // @ 0x00eb73f0
};

// @ 0x00eb73f0
void CamBlend::Build()
{
    Grid* grid = DebugDrawGrid();
    if (!grid) return;
    float zoomMid = (mZoomA + mZoomB) * 0.5f;
    float mid = (mLo + mHi) * 0.5f;
    static float sMin = -Deg2Rad(85.0f);

    float d = Dot3(mDirA, mDirB);
    d = Clamp(d, -1.0f, 1.0f);
    float scale = grid->Scale();
    float ang = (float)fabs((float)acos((double)d) * scale);
    float lo = mMinAngle;
    ang = Clamp(ang, lo, gMaxVal);
    float t = (ang - lo) / (gMaxVal - lo);
    t = ((3.0f - t * 2.0f) * t) * t;
    if (t == 0.0f) {
        mMode = 4;
        mbDone = 1;
        return;
    }
    float zoomDelta = (mThreshold - zoomMid) * t;
    float midBlend = (sMin - mid) * t + mid;

    mTrZoom.Clear();
    mTrZoom.t.resize(3);
    mTrZoom.t[0] = 0.0f; mTrZoom.t[1] = 0.5f; mTrZoom.t[2] = 1.0f;
    mTrZoom.v.resize(3);
    mTrZoom.v[0] = mZoomA;
    mTrZoom.v[1] = zoomDelta + zoomMid;
    mTrZoom.v[2] = mZoomB;
    mTrZoom.s.resize(3);
    mTrZoom.s[0] = 0.0f; mTrZoom.s[2] = 0.0f;
    mTrZoom.ComputeSlopes();

    mTrFov.Clear();
    mTrFov.t.resize(5);
    mTrFov.t[0] = 0.0f; mTrFov.t[1] = 0.15f; mTrFov.t[2] = 0.5f; mTrFov.t[3] = 0.85f; mTrFov.t[4] = 1.0f;
    mTrFov.v.resize(5);
    mTrFov.v[0] = mLo;
    mTrFov.v[1] = (midBlend - mLo) * 0.7f + mLo;
    mTrFov.v[2] = midBlend;
    mTrFov.v[3] = (midBlend - mHi) * 0.7f + mHi;
    mTrFov.v[4] = mHi;
    mTrFov.s.resize(5);
    mTrFov.s[0] = 0.0f; mTrFov.s[4] = 0.0f;
    mTrFov.ComputeSlopes();

    mTrDir.Clear();
    mTrDir.t.resize(3);
    mTrDir.t[0] = 0.0f; mTrDir.t[1] = 0.5f; mTrDir.t[2] = 1.0f;
    mTrDir.v.resize(3);
    mTrDir.v[0] = mDirA;
    Vec3 tmp;
    mTrDir.v[1] = *RotateTowards(&tmp, &mDirA, &mDirB, 0.5f);
    mTrDir.v[2] = mDirB;
    mTrDir.s.resize(3);
    mTrDir.s[0] = gZeroVec;
    mTrDir.s[2] = gZeroVec;
    mTrDir.ComputeTangents();
    {
        float k = gTwo;
        Vec3& m = mTrDir.s[1];
        m.y = m.y * k; m.x = k * m.x; m.z = m.z * k;
    }

    if (mQ1.w * mQ2.w + mQ1.z * mQ2.z + mQ1.y * mQ2.y + mQ2.x * mQ1.x < 0.0f) {
        mQ2.x = -mQ2.x; mQ2.y = -mQ2.y; mQ2.z = -mQ2.z; mQ2.w = -mQ2.w;
    }
    tmp = mUp;
    Quat qb;
    Quat_Blend(&qb, &mTrDir.v[0], &mTrDir.v[1], &mQ1, &tmp);
    if (mQ1.y * qb.y + mQ1.z * qb.z + mQ1.w * qb.w + qb.x * mQ1.x < 0.0f) {
        qb.x = -qb.x; qb.y = -qb.y; qb.z = -qb.z; qb.w = -qb.w;
    }

    mTrQuat.Clear();
    mTrQuat.t.resize(3);
    mTrQuat.t[0] = 0.0f; mTrQuat.t[1] = 0.5f; mTrQuat.t[2] = 1.0f;
    mTrQuat.v.resize(3);
    mTrQuat.v[0] = mQ1;
    mTrQuat.v[1] = qb;
    mTrQuat.v[2] = mQ2;
    mTrQuat.s.resize(3);
    mTrQuat.s[0] = gZeroQuat;
    mTrQuat.s[2] = gZeroQuat;
    mTrQuat.ComputeTangents();
    {
        Quat& m = mTrQuat.s[1];
        float k = gTwo;
        float y = m.y * k, z = m.z * k, w = m.w * k;
        m.x = m.x * k; m.y = y; m.z = z; m.w = w;
    }
}


// ---------------------------------------------------------------------------------------------
// Message handler. `this` is the IMessageHandler subobject at camera+4 (offsets below are
// relative to that subobject; Build() above uses the camera's own offsets, +4).
// ---------------------------------------------------------------------------------------------
float  __cdecl VectorLength(const Vec3* v);                                  // 0x0040ae50
Vec3*  __cdecl normalized_safe(Vec3* out, const Vec3* in);                   // 0x00449c20
char   __cdecl Vector3Equal(const Vec3* a, const Vec3* b);                   // 0x004232c0
Quat*  __cdecl QuaternionFromFacingAndUp(Quat* out, const Vec3* f, const Vec3* up);  // 0x0069b600
Quat*  __cdecl QuaternionFromMatrix33(Quat* out, const void* m, float eps);  // 0x00472b80
float* __cdecl QuatToMatrixRow(float* out, const Quat* q);                   // 0x007d9a50
struct QuatCopy { float x, y, z, w; QuatCopy& Assign(const Quat& q); };      // 0x00572600 (thiscall operator=)

enum {
    kMsgTargetPos      = 0x101b534,
    kMsgTargetPosSnap  = 0x101b537,
    kMsgOrientA        = 0x101b543,
    kMsgInitialZoom    = 0x101d445,
    kMsgZoom           = 0x101d4c7,
    kMsgOrientAll      = 0x101d51f,
    kMsgOrientB        = 0x101d576,
    kMsgDist1          = 0x109d174,
    kMsgDistFC_A       = 0x109d1aa,
    kMsgDist100_A      = 0x109d1af,
    kMsgDistAll        = 0x109d352,
    kMsgDistFC_B       = 0x109d372,
    kMsgDist100_B      = 0x109d375,
};

struct CamMsg {
    char  pad00[0x10];
    int   mMode;                 // +0x10
    float mF14, mF18, mF1C;
    char  pad20[0x28 - 0x20];
    float mF28, mF2C, mF30;
    char  pad34[0x3c - 0x34];
    float mF3C, mF40, mF44;
    char  pad48[0x50 - 0x48];
    Vec3  mCur;                  // +0x50
    Vec3  mTarget;               // +0x5c
    Vec3  mPrev;                 // +0x68
    char  mbDone;                // +0x74
    char  pad75[0x88 - 0x75];
    Vec3  mDirCur;               // +0x88
    Vec3  mDirTarget;            // +0x94
    Vec3  mDirPrev;              // +0xa0
    char  padac[0xc0 - 0xac];
    float mLenC0, mLenC4, mLenC8;
    char  padcc[0xd4 - 0xcc];
    float mD4, mD8, mDC;
    char  pade0[0xe8 - 0xe0];
    float mZoomE8, mZoomEC, mZoomF0;
    char  padf4[0xfc - 0xf4];
    float mFC;
    float m100;
    char  pad104[0x107 - 0x104];
    char  mbSnap;                // +0x107
    char  pad108[0x114 - 0x108];
    float mUpX, mUpY, mUpZ;      // +0x114
    char  pad120[0x12c - 0x120];
    QuatCopy mQSaved;            // +0x12c
    QuatCopy mQ1;                // +0x13c
    Quat  mQOut;                 // +0x14c
    char  pad15c[0x184 - 0x15c];
    float mMat[9];               // +0x184

    bool HandleMessage(uint32_t id, void* data);   // @ 0x00eb7b30
};

static inline Vec3 MakeVec3(float x, float y, float z)
{
    Vec3 v;
    v.x = x; v.y = y; v.z = z;
    return v;
}

// @ 0x00eb7b30
bool CamMsg::HandleMessage(uint32_t id, void* data)
{
    float* p = (float*)data;
    switch (id) {
    case kMsgTargetPos: {
        mTarget = *(Vec3*)p;
        if (mbSnap) {
            mZoomE8 = mZoomEC;
            mPrev = mCur;
        }
        int mode = mMode;
        if (mode == 1) {
            if (!DebugDrawGrid()) {
                mMode = 4;
                mbDone = 1;
                return true;
            }
            float lenT = VectorLength(&mTarget);
            mLenC8 = lenT;
            float lenC = VectorLength(&mCur);
            mLenC4 = lenC;
            mLenC0 = lenC;
            float inv = 1.0f / lenT;
            mDirTarget.x = mTarget.x * inv;
            mDirTarget.y = mTarget.y * inv;
            mDirTarget.z = mTarget.z * inv;
            float inv2 = 1.0f / mLenC4;
            mDirCur.x = inv2 * mCur.x;
            mDirCur.y = mCur.y * inv2;
            mDirCur.z = mCur.z * inv2;
            mDirPrev = mDirCur;
            ((CamBlend*)((char*)this - 4))->Build();
            return true;
        }
        if (mode == 2) {
            Quat q;
            mQ1.Assign(*QuaternionFromMatrix33(&q, mMat, 0.0f));
            *(Quat*)&mQSaved = *(Quat*)&mQ1;
            Vec3 neg = MakeVec3(-mTarget.x, -mTarget.y, -mTarget.z);
            Vec3 f;
            normalized_safe(&f, &neg);
            if (Vector3Equal(&f, &gZeroVec))
                f = MakeVec3(1.0f, 0.0f, 0.0f);
            Vec3 ax = MakeVec3(gAxisX, gAxisY, gAxisZ);
            if ((float)fabs(mUpZ * gAxisZ + mUpY * gAxisY + mUpX * gAxisX) - 1.0f < 0.01f)
                ax = gAltAxis;
            Vec3 c = MakeVec3(f.z * ax.y - f.y * ax.z, ax.z * f.x - f.z * ax.x, f.y * ax.x - ax.y * f.x);
            Vec3 r;
            normalized_safe(&r, &c);
            c = MakeVec3(r.z * f.y - r.y * f.z, f.z * r.x - r.z * f.x, r.y * f.x - f.y * r.x);
            Vec3 u;
            Vec3 up = *normalized_safe(&u, &c);
            Quat qo;
            mQOut = *QuaternionFromFacingAndUp(&qo, &f, &up);
            return true;
        }
        if (mode == 3) {
            mCur.x = mTarget.x; mPrev.x = mTarget.x;
            mCur.y = mTarget.y; mPrev.y = mTarget.y;
            mCur.z = mTarget.z; mPrev.z = mTarget.z;
        }
        return true;
    }
    case kMsgTargetPosSnap: {
        Vec3 v = *(Vec3*)p;
        mTarget = v;
        mCur = v;
        mPrev = v;
        float z = mZoomF0;
        mZoomEC = z;
        mZoomE8 = z;
        int mode = mMode;
        if (mode == 1 || mode == 2 || mode == 3) {
            mMode = 4;
            mbDone = 1;
        }
        return true;
    }
    case kMsgOrientA:
    case kMsgOrientB: {
        float q4[4] = { p[0], p[1], p[2], p[3] };
        float m9[9];
        float* r = QuatToMatrixRow(m9, (Quat*)q4);
        mF30 = -r[0];
        mF1C = -r[2];
        mF44 = -r[1];
        if (mbSnap) {
            mF28 = mF2C;
            mF14 = mF18;
            mF3C = mF40;
        }
        return true;
    }
    case kMsgOrientAll: {
        float q4[4] = { p[0], p[1], p[2], p[3] };
        float m9[9];
        float* r = QuatToMatrixRow(m9, (Quat*)q4);
        float x = -r[0], z = -r[2], y = -r[1];
        mF30 = x; mF2C = x; mF28 = x;
        mF1C = z; mF18 = z; mF14 = z;
        mF44 = y; mF40 = y; mF3C = y;
        return true;
    }
    case kMsgInitialZoom: {
        float z = p[0];
        mZoomEC = z;
        mZoomE8 = mZoomEC;
        mZoomF0 = z;
        return true;
    }
    case kMsgZoom:
        mZoomF0 = p[0];
        if (mbSnap) mZoomE8 = mZoomEC;
        return true;
    case kMsgDist1:
        mDC = p[0];
        if (mbSnap) mD4 = mD8;
        return true;
    case kMsgDistAll: {
        float z = p[0];
        mDC = z; mD8 = z; mD4 = z;
        return true;
    }
    case kMsgDistFC_A:
    case kMsgDistFC_B:
        mFC = p[0];
        return true;
    case kMsgDist100_A:
    case kMsgDist100_B:
        m100 = p[0];
        return true;
    }
    return false;
}
