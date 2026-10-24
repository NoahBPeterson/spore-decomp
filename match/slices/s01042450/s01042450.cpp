// Slice s01042450 (module SPAppModeSpace.obj): the polar/spherical conversion and curve helpers that
// sit at the tail of the space app-mode block, plus the ArcStep steering step.
#include <math.h>
#include <xmmintrin.h>
#include "types.h"

struct Vec3f { float x, y, z; };

extern Vec3f g_DefaultVec;              // 0x016dfaf8
extern float* OrthogonalVector(float* a, float* b);   // 0x006985b0, cdecl
// 0x01042570 / 0x010426a0: scalar spring/approach helpers (cdecl)
extern void ApproachScalar(float* value, float* velocity, float target, float a, float b, float dt);
extern void ApproachVector(float* value, float* velocity, float* target, float a, float b, float dt);

// ---------------------------------------------------------------- singleton accessors
// cSPSimulatorSpaceGame (the high-LOD space simulator): the player-inventory object hangs off +0x40
// (see its 4-byte accessor 0x00a1ad60).  The inventory's +0x74c byte is read by FUN_01042450.
struct cSPSimulatorSpaceGameInv {
    uint8_t mPad0[0x74c];
    char    mReadyFlag;                     // +0x74c
};
struct cSPSimulatorSpaceGame {
    uint8_t mPad0[0x40];
    cSPSimulatorSpaceGameInv* mpInventory;  // +0x40
    cSPSimulatorSpaceGameInv* GetPlayerInventory();      // 0x00a1ad60
};
cSPSimulatorSpaceGame* GetUFOSimulator();                // 0x00ffbe50

struct cGameTimeManager {
    uint8_t mPad0[0x48];
    uint8_t mFlags48;                       // +0x48 (bit 0 = paused)
};
cGameTimeManager* GameTimeManager();                     // 0x00b3d380

// ---------------------------------------------------------------- curve payloads
// 8-byte keyed curve: +0x00 element array (or the inline key), +0x08 element count (heap form only),
// +0x10 flags (mask 0x30 selects the heap form), +0x12 inline element count.
struct CurveKey { float mTime; float mValue; };
struct Curve {
    union {
        const CurveKey* mpKeys;             // +0x00 (heap)
        CurveKey        mInlineKey;         // +0x00 (inline)
    };
    int      mnCount;                       // +0x08
    uint32_t mu0c;                          // +0x0c
    uint16_t mwFlags;                       // +0x10
    uint16_t mwInlineCount;                 // +0x12
};
// 16-byte sampled curve (4 floats per sample, FUN_01043310 picks one component).
struct CurveSample {
    const float* mpSamples;                 // +0x00 (heap; 4 floats per sample)
    float        mf04;                      // +0x04
    int          mnCount;                   // +0x08
    uint32_t     mu0c;                      // +0x0c
    uint16_t     mwFlags;                   // +0x10
    uint16_t     mwInlineCount;             // +0x12
};
// Object whose virtual slot +0x28 hands out the curve for a normalised time.
struct CurveOwner {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual const Curve* GetCurve(float t); // +0x28
};

extern float g_fStationaryVelocity[3];  // 0x016dfaf8 (zeroed velocity written on arrival)
struct RandomLinearCongruential {
    double RandomDoubleUniform();                   // 0x009360d0
};
extern RandomLinearCongruential sMathRandom;    // 0x01601760
extern "C" float* normalized_safe(float* out, const float* v);   // 0x00449c20

#define EPS_DIST 1.5258789e-05f                 // 0x1499ce8 = 2^-16
#define EPS_SQ   1e-08f                         // 0x13ec4b8

// min/max on two lvalues: MSVC keeps both in memory and selects between their addresses.
inline float minf(float a, float b) { return a > b ? b : a; }
inline float maxf(float a, float b) { return a < b ? b : a; }

static inline float ClampF(float v, float lo, float hi)
{
    float r;
    __asm {
        movss xmm0, v
        maxss xmm0, lo
        minss xmm0, hi
        movss r, xmm0
    }
    return r;
}

// @ 0x01042aa0
void ArcStep(float* pos, float* dir, float* target, float* centre, float* params,
             float p6, float p7, float dt)
{
    if (dt != 0.0f) {
        float dy = target[1] - pos[1];
        float dz = target[2] - pos[2];
        float dx = target[0] - pos[0];
        if ((dy * dy + dx * dx) + dz * dz < 1.5258789e-05f) {
            pos[0] = target[0];
            pos[1] = target[1];
            pos[2] = target[2];
            dir[0] = g_DefaultVec.x;
            dir[1] = g_DefaultVec.y;
            dir[2] = g_DefaultVec.z;
            return;
        }
        float tx = target[0] - centre[0];
        float py = pos[1] - centre[1];
        float ty = target[1] - centre[1];
        float pz = pos[2] - centre[2];
        float px = pos[0] - centre[0];
        float r2 = (px * px + pz * pz) + py * py;
        float tz = target[2] - centre[2];
        float r = sqrtf(r2);
        float dirY = dir[1];
        float inv = 1.0f / r;
        float nz = pz * inv;
        float ny = py * inv;
        float nx = inv * px;
        float d = (ny * dirY + nz * dir[2]) + dir[0] * nx;
        float perpX = dir[0] - nx * d;
        float perpY = dirY - ny * d;
        float perpZ = dir[2] - nz * d;
        float tr = sqrtf(ty * ty + (tz * tz + tx * tx));
        float t2 = ty * ty + (tz * tz + tx * tx);
        float s = 0.0f;
        ApproachScalar(&s, &d, tr - r, p6, params[0] * p7, dt);
        float newZ = nz * s + pos[2];
        float newY = ny * s + pos[1];
        float newX = nx * s + pos[0];
        pos[0] = newX;
        pos[2] = newZ;
        pos[1] = newY;
        float len = sqrtf(newX * newX + (newY * newY + newZ * newZ));
        volatile float i1v = 1.0f / sqrtf(r2 + 1e-08f);
        float i1 = i1v;
        volatile float i2v = 1.0f / sqrtf(t2 + 1e-08f);
        float i2 = i2v;
        float c = ((i2 * tx) * (i1 * px) + (tz * i2) * (pz * i1)) + (ty * i2) * (py * i1);
        c = ClampF(c, -1.0f, 1.0f);
        float ang = acosf(c);
        float* m = &tr;
        if (r <= tr) m = &r;
        float dot = ((tx - px) * nx + (tz - pz) * nz) + (ty - py) * ny;
        float qx = (tx - px) - dot * nx;
        float qz = (tz - pz) - nz * dot;
        float qy = (ty - py) - ny * dot;
        float arc = *m * ang;
        float ql = sqrtf(qy * qy + (qz * qz + qx * qx));
        float pl = sqrtf(perpY * perpY + (perpZ * perpZ + perpX * perpX));
        float ox, oy, oz;
        if (ql > 1.5258789e-05f) {
            float k = arc / ql;
            ox = qx * k; oy = qy * k; oz = qz * k;
        } else if (pl > 1.5258789e-05f) {
            float k = arc / pl;
            ox = perpX * k; oy = perpY * k; oz = perpZ * k;
        } else {
            float* o = OrthogonalVector(&qx, &nx);
            ox = o[0] * arc; oy = o[1] * arc; oz = o[2] * arc;
        }
        float v[3] = { g_DefaultVec.x, g_DefaultVec.y, g_DefaultVec.z };
        float off[3] = { ox, oy, oz };
        float vel[3] = { perpX, perpY, perpZ };
        ApproachVector(v, vel, off, p6, params[1] * p7, dt);
        v[2] = v[2] + pos[2];
        v[1] = v[1] + pos[1];
        v[0] = v[0] + pos[0];
        float f = 1.0f / sqrtf((v[0] * v[0] + (v[1] * v[1] + v[2] * v[2])) + 1e-08f);
        pos[0] = (v[0] * f) * len;
        pos[1] = (v[1] * f) * len;
        pos[2] = (v[2] * f) * len;
        dir[0] = nx * d + vel[0];
        dir[1] = ny * d + vel[1];
        dir[2] = nz * d + vel[2];
    }
}

// ---------------------------------------------------------------------------------------------
// Curve / spherical helpers (all cdecl, ret only).
// ---------------------------------------------------------------------------------------------

// @ 0x01042450
bool FUN_01042450(void)
{
    cGameTimeManager* time = GameTimeManager();
    if ((time->mFlags48 & 1) == 0) {
        cSPSimulatorSpaceGameInv* inv = GetUFOSimulator()->GetPlayerInventory();
        if (inv->mReadyFlag != 0) {
            return true;
        }
    }
    return false;
}

// Spatial -> spherical: radius, azimuth (atan2 y/x), polar (acos z/r).
// @ 0x01042480
void FUN_01042480(float* pOut, const float* pIn)
{
    pOut[0] = sqrtf(pIn[0] * pIn[0] + pIn[1] * pIn[1] + pIn[2] * pIn[2]);
    pOut[1] = atan2f(pIn[1], pIn[0]);
    pOut[2] = acosf(pIn[2] / pOut[0]);
}

// Spherical -> spatial: (azimuth y, polar z, radius x).
// @ 0x010424c0
void FUN_010424c0(float* pOut, const float* pIn)
{
    double x = pIn[0];
    double y = pIn[1];
    double z = pIn[2];
    pOut[0] = (float)(cos(y) * sin(z) * x);
    pOut[1] = (float)(sin(y) * sin(z) * x);
    pOut[2] = (float)(cos(z) * x);
}

// Scalar approach-to-target step with arrival damping.
// @ 0x01042500
void FUN_01042500(float* pValue, float target, float rate, float dt)
{
    if (fabsf(*pValue - target) < EPS_DIST) {
        *pValue = target;
        return;
    }
    float fOld = *pValue;
    float step = rate * dt;
    if (fOld > target) {
        *pValue = fOld - step;
        float* pKeep = (*pValue < target) ? &target : pValue;
        *pValue = *pKeep;
    }
    else {
        *pValue = fOld + step;
        float* pKeep = (*pValue > target) ? &target : pValue;
        *pValue = *pKeep;
    }
}

// Scalar velocity approach with max speed / max acceleration and arrival damping.
// @ 0x01042570
void FUN_01042570(float* pPosition, float* pVelocity, float target, float maxSpeed, float maxAccel, float dt)
{
    if (dt != 0.0f) {
        float fOld = *pPosition;
        float fDist = fabsf(target - fOld);
        if (fDist < EPS_DIST) {
            *pPosition = target;
            *pVelocity = 0.0f;
            return;
        }
        float inv = 1.0f / dt;
        float fTime = fDist * inv;
        float fBrake = sqrtf(fDist * maxAccel);
        fTime = minf(fTime, fBrake);
        fTime = minf(fTime, maxSpeed);
        float fDesired = fTime;
        if (target <= fOld) {
            fDesired = -fDesired;
        }
        float fAccel = (fDesired - *pVelocity) * inv;
        if (fAccel < -maxAccel) {
            fAccel = -maxAccel;
        }
        if (fAccel > maxAccel) {
            fAccel = maxAccel;
        }
        float fNewVelocity = fAccel * dt + *pVelocity;
        if (fNewVelocity < -maxSpeed) {
            fNewVelocity = -maxSpeed;
        }
        if (fNewVelocity > maxSpeed) {
            fNewVelocity = maxSpeed;
        }
        *pVelocity = fNewVelocity;
        *pPosition = fNewVelocity * dt + *pPosition;
    }
}

// Vector (3D) velocity approach with arrival damping and steering.
// @ 0x010426a0
void FUN_010426a0(float* pPosition, float* pVelocity, const float* pTarget,
                  float maxSpeed, float maxAccel, float dt)
{
    if (dt == 0.0f) {
        return;
    }
    float dy = pTarget[1] - pPosition[1];
    float dz = pTarget[2] - pPosition[2];
    float dx = pTarget[0] - pPosition[0];
    float distSq = dz * dz + dy * dy + dx * dx;
    float dist = sqrtf(distSq);
    float vx = pVelocity[0];
    float vy = pVelocity[1];
    float vz = pVelocity[2];
    float speedSq = vx * vx + vy * vy + vz * vz;
    float speed = sqrtf(speedSq);
    if (dist <= EPS_DIST && speed <= EPS_DIST) {
        pPosition[0] = pTarget[0];
        pPosition[1] = pTarget[1];
        pPosition[2] = pTarget[2];
        pVelocity[0] = g_fStationaryVelocity[0];
        pVelocity[1] = g_fStationaryVelocity[1];
        pVelocity[2] = g_fStationaryVelocity[2];
        return;
    }
    float inv = 1.0f / dt;
    float fTime = dist * inv;
    float fBrake = sqrtf(dist * maxAccel + dist * maxAccel);
    if (fTime > fBrake) {
        fTime = fBrake;
    }
    if (fTime > maxSpeed) {
        fTime = maxSpeed;
    }
    float fDesired = fTime;
    bool bAligned = false;
    if (fDesired < maxSpeed && fDesired < speed) {
        bool bSteer;
        {
            float dirVel[3] = { vx, vy, vz };
            float dirDist[3] = { dx, dy, dz };
            float* pnVel = normalized_safe(dirVel, pVelocity);
            float* pnDist = normalized_safe(dirDist, dirDist);
            bSteer = 0.9f < pnDist[2] * pnVel[2] + pnDist[1] * pnVel[1] + pnDist[0] * pnVel[0];
        }
        if (bSteer) {
            bAligned = true;
        }
    }
    if (dist <= EPS_DIST) {
        float k = 1.0f / sqrtf(speedSq + EPS_SQ);
        dx = vx * k;
        dz = vz * k;
        dy = vy * k;
    }
    else {
        float k = 1.0f / sqrtf(distSq + EPS_SQ);
        dx = dx * k;
        dy = dy * k;
        dz = dz * k;
    }
    float cX = (dx * fDesired - vx) * inv;
    float cZ = (dz * fDesired - vz) * inv;
    float cY = (dy * fDesired - vy) * inv;
    float cLen = sqrtf(cY * cY + cX * cX + cZ * cZ);
    if (!bAligned && maxAccel < cLen) {
        maxAccel = maxAccel / cLen;
        cX = cX * maxAccel;
        cY = cY * maxAccel;
        cZ = cZ * maxAccel;
    }
    float newX = pVelocity[0] + cX * dt;
    float newY = pVelocity[1] + cY * dt;
    float newZ = pVelocity[2] + cZ * dt;
    pVelocity[0] = newX;
    pVelocity[1] = newY;
    pVelocity[2] = newZ;
    float newSpeed = sqrtf(newX * newX + newY * newY + newZ * newZ);
    if (maxSpeed < newSpeed) {
        maxSpeed = maxSpeed / newSpeed;
        pVelocity[0] = newX * maxSpeed;
        pVelocity[1] = newY * maxSpeed;
        pVelocity[2] = newZ * maxSpeed;
    }
    pPosition[0] = pPosition[0] + pVelocity[0] * dt;
    pPosition[1] = pVelocity[1] * dt + pPosition[1];
    pPosition[2] = pVelocity[2] * dt + pPosition[2];
}

// Keyed curve evaluation with linear interpolation.
// @ 0x01043150
float FUN_01043150(const Curve* pCurve, float t)
{
    int count;
    if ((pCurve->mwFlags & 0x30) != 0) {
        count = pCurve->mnCount;
        if (count <= 0) {
            return 0.0f;
        }
    }
    else {
        if (pCurve->mwInlineCount == 0) {
            return 0.0f;
        }
        count = 1;
    }
    const CurveKey* keys = (pCurve->mwFlags & 0x30)
                         ? pCurve->mpKeys
                         : (pCurve->mwInlineCount != 0 ? &pCurve->mInlineKey : 0);
    if (t < keys[0].mTime) {
        return keys[0].mValue;
    }
    for (int i = 1; i < count; i++) {
        if (!(keys[i].mTime < t)) {
            return keys[i - 1].mValue + (keys[i].mValue - keys[i - 1].mValue) *
                   ((t - keys[i - 1].mTime) / ((keys[i].mTime - keys[i - 1].mTime) + EPS_DIST));
        }
    }
    return keys[count - 1].mValue;
}

// Random keyed curve pick on the queried curve's normalised time.
// @ 0x010431e0
float FUN_010431e0(CurveOwner* pOwner, float t)
{
    if (pOwner == 0) {
        return 0.0f;
    }
    const Curve* pCurve = pOwner->GetCurve(t);
    int count;
    if ((pCurve->mwFlags & 0x30) != 0) {
        count = pCurve->mnCount;
        if (count <= 0) {
            return 0.0f;
        }
    }
    else {
        if (pCurve->mwInlineCount == 0) {
            return 0.0f;
        }
        count = 1;
    }
    const CurveKey* keys = (pCurve->mwFlags & 0x30)
                         ? pCurve->mpKeys
                         : (pCurve->mwInlineCount != 0 ? &pCurve->mInlineKey : 0);
    float fTotal = 0.0f;
    for (int i = 0; i < count; i++) {
        fTotal = keys[i].mTime + fTotal;
    }
    double fTarget = (double)fTotal * sMathRandom.RandomDoubleUniform();
    if (fTarget > (double)fTotal) {
        fTarget = (double)fTotal;
    }
    if (fTarget < 0.0) {
        fTarget = 0.0;
    }
    float fWeight = 0.0f;
    for (int i = 0; i < count; i++) {
        fWeight = keys[i].mTime + fWeight;
        if ((float)fTarget < fWeight) {
            return keys[i].mValue;
        }
    }
    return keys[0].mValue;
}

// Sampled (4 floats per sample) curve evaluation, one component, cdecl.  The retail
// function looks the curve up at the second argument but scales by the third, so the
// signature is (owner, lookup time, sample time, component).
// @ 0x01043310
float FUN_01043310(CurveOwner* pOwner, float tLookup, float tSample, int nComponent)
{
    if (pOwner == 0) {
        return 0.0f;
    }
    const CurveSample* pCurve = (const CurveSample*)pOwner->GetCurve(tLookup);
    int count;
    const float* pSamples;
    if ((pCurve->mwFlags & 0x30) != 0) {
        pSamples = pCurve->mpSamples;
        count = pCurve->mnCount;
        if (count <= 0) {
            return 0.0f;
        }
    }
    else {
        pSamples = (pCurve->mwInlineCount != 0) ? (const float*)&pCurve->mpSamples : 0;
        if (pCurve->mwInlineCount == 0) {
            return 0.0f;
        }
        count = 1;
    }
    float fScaled = (float)(count - 1) * tSample;
    if (count == 1) {
        return pSamples[nComponent];
    }
    if (fScaled < (float)(count - 1)) {
        // The retail build rounds the sample index to nearest and then floors it for
        // negatives (cvtss2si + cvtsi2ss + cmovb), not a plain truncation.
        int i = _mm_cvtss_si32(_mm_set_ss(fScaled));
        if (fScaled < (float)i) {
            i = i - 1;
        }
        return pSamples[nComponent + i * 4] +
               (fScaled - (float)i) * (pSamples[nComponent + (i + 1) * 4] - pSamples[nComponent + i * 4]);
    }
    return pSamples[nComponent + (count - 1) * 4];
}
