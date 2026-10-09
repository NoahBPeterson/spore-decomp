// Slice s00ab3370 -- one function, @ 0x00ab3370 (17,323 bytes).
//
// EA::Swarm ribbon effect: stream the ribbon's quads into a vertex stream.
// (The previous symbol guess "hkSimulation_integrateStep" was wrong: param_1 is an
// EA::Swarm::cRibbonEffect -- mDesc at +0x14 is a cRibbonDescription whose curve
// vectors match the dev-PDB member order -- and param_2 is the vertex stream that
// hands out a locked buffer.)
//
// Layout notes (retail differs from the 2008 dev PDB):
//   * every eastl::vector in the retail description is 0x14 bytes, so the dev
//     offsets shift (mOffsetCurve 0x14, mWidthCurve 0x28, mTaper 0x3c, mFade 0x40,
//     mColorCurve 0x48, ..., mEndEdgeAlphaCurve 0xd4, mNumSegments 0xe8,
//     mSegmentLength 0xec);
//   * the effect keeps its position history at +0x134 (a fixed_vector), the right-
//     vector history at +0x53c, the per-history decay at +0x570 and the emit colour
//     map at +0x6dc.
//
// Per segment i the function samples the ribbon at i and i+1 (sample i is carried
// over from the previous iteration), builds two edge points and a centre point per
// sample (camera-facing when description flag 3 is set, otherwise along x / the
// right vector / z), packs ARGB colours and emits two quads through FUN_00ab3100.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (inline fsqrt; /fp:precise calls _CIsqrt).
// COMPLETE, behaviourally equivalent; not byte-exact (17 KB, register allocation
// and stack-slot assignment differ).
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

namespace EA { namespace Swarm {

struct Vector3 { float x, y, z; };
struct Vector4 { float x, y, z, w; };

// retail eastl::vector<T, sp_vector_allocator>: 0x14 bytes
template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    void* mAllocator[2];
    __forceinline uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};

struct cRibbonDescription {
    void*            vftable;            // +0x00
    int              mRefCount;          // +0x04
    uint32_t         mFlags;             // +0x08  eastl::bitset<14>
    float            mRibbonLifetime[2]; // +0x0c
    SpVector<float>   mOffsetCurve;       // +0x14
    SpVector<float>   mWidthCurve;        // +0x28
    float            mTaper;             // +0x3c
    float            mFade;              // +0x40
    float            mAlphaDecay;        // +0x44
    SpVector<Vector3> mColorCurve;        // +0x48
    SpVector<float>   mAlphaCurve;        // +0x5c
    SpVector<Vector3> mLengthColorCurve;  // +0x70
    SpVector<float>   mLengthAlphaCurve;  // +0x84
    SpVector<Vector3> mEdgeColorCurve;    // +0x98
    SpVector<float>   mEdgeAlphaCurve;    // +0xac
    SpVector<float>   mStartEdgeAlphaCurve; // +0xc0
    SpVector<float>   mEndEdgeAlphaCurve; // +0xd4
    int              mNumSegments;       // +0xe8
    float            mSegmentLength;     // +0xec

    __forceinline bool test(int bit) const { return ((mFlags >> bit) & 1) != 0; }
};

struct cGlobalParams {
    char    pad0[0x68];
    Vector3 mCameraAxis;                 // +0x68 (row of the camera orientation)
};

class cIMap {
public:
    virtual void v00() = 0;
    virtual void v01() = 0;
    virtual void v02() = 0;
    virtual void v03() = 0;
    virtual void v04() = 0;
    virtual void v05() = 0;
    virtual bool Contains(const Vector3& pos) = 0;      // slot 6 (+0x18)
    virtual void v07() = 0;
    virtual void v08() = 0;
    virtual void v09() = 0;
    virtual void v10() = 0;
    virtual Vector4 GetColor(const Vector3& pos) = 0;   // slot 11 (+0x2c)
};

// param_2: the vertex stream the quads are written into
class cIRibbonStream {
public:
    virtual int  Lock(int numQuads, char** ppBuffer, int* pStride) = 0; // slot 0
    virtual void v01() = 0;
    virtual void Unlock() = 0;                                           // slot 2
};

struct cTransform {
    uint16_t mFlags;        // +0x00
    uint16_t mModificationCount;
    Vector3  mTranslation;  // +0x04
    float    mScale;        // +0x10
    float    mRotation[3][3]; // +0x14
};

class cRibbonEffect {
public:
    char                mPad0[0x12];
    bool                mBufferFull;        // +0x12
    char                mPad13;
    cRibbonDescription* mDesc;              // +0x14
    void*               mRenderer;          // +0x18
    cGlobalParams*      mGlobalParams;      // +0x1c
    double              mOverallTime;       // +0x20
    float               mAge;               // +0x28
    float               mLife;              // +0x2c
    float               mInvLife;           // +0x30
    float               mMaxWidth;          // +0x34
    int                 mNumSegments;       // +0x38
    float               mOffsetCurveSlip;   // +0x3c
    char                mPad40[0x64 - 0x40];
    Vector3             mLocation;          // +0x64
    Vector3             mRight;             // +0x70
    cTransform          mSourceTransform;   // +0x7c
    cTransform          mRigidTransform;    // +0xb4
    char                mPadEC[0xfc - 0xec];
    float               mCurrentAlphaScale; // +0xfc
    float               mCurrentSizeScale;  // +0x100
    char                mPad104[0x11c - 0x104];
    Vector3             mColorScale;        // +0x11c
    char                mPad128[0x134 - 0x128];
    SpVector<Vector3>   mPositionHistory;   // +0x134 (fixed_vector)
    char                mPad148[0x53c - 0x148];
    SpVector<Vector3>   mRightHistory;      // +0x53c
    char                mPad550[0x570 - 0x550];
    SpVector<float>     mPositionHistoryDecay; // +0x570
    char                mPad584[0x6dc - 0x584];
    cIMap*              mEmitColorMap;      // +0x6dc

    // FUN_00ab3100: writes one quad (4 vertices: position, uv, colour) and
    // returns the buffer advanced by 4 * stride.
    char* AddQuad(char* buffer, int segment, int stride, float v,
                  Vector3 p1, Vector3 p0, Vector3 p2, Vector3 p3,
                  uint32_t c1, uint32_t c0, uint32_t c2, uint32_t c3);
};

typedef char check_desc[(sizeof(cRibbonDescription) == 0xf0) ? 1 : -1];
typedef char check_hist[(sizeof(SpVector<float>) == 0x14) ? 1 : -1];

// 0x006e6df0: v / sqrt(|v|^2 + 1e-8)
Vector3 Normalize(const Vector3& v);

} } // namespace EA::Swarm

using namespace EA::Swarm;

namespace {

__forceinline float Lerp(float a, float b, float f) { return (b - a) * f + a; }
__forceinline Vector3 Lerp(const Vector3& a, const Vector3& b, float f)
{
    Vector3 r;
    r.x = a.x + (b.x - a.x) * f;
    r.y = a.y + (b.y - a.y) * f;
    r.z = a.z + (b.z - a.z) * f;
    return r;
}

// Sample a key array at f = index + fraction (no bounds check, as the original).
template <class T> __forceinline T SampleAt(const T* data, float f)
{
    int i = (int)f;
    float frac = f - (float)i;
    if (frac > 0.0f)
        return Lerp(data[i], data[i + 1], frac);
    return data[i];
}

// Evaluate a description curve with `last` = size() - 1 keys spaced over [0,1].
template <class T> __forceinline T EvalCurve(const SpVector<T>& curve, uint32_t last, float t)
{
    if (last == 0)
        return curve.mpBegin[0];
    return SampleAt(curve.mpBegin, (float)last * t);
}

__forceinline float Clamp01(float v)
{
    float r;
    _mm_store_ss(&r, _mm_min_ss(_mm_max_ss(_mm_setzero_ps(), _mm_set_ss(v)), _mm_set_ss(1.0f)));
    return r;
}

__forceinline uint8_t UnitToByte(float v)
{
    __m128 k = _mm_set_ss(255.0f);
    return (uint8_t)_mm_cvtss_si32(_mm_min_ss(_mm_mul_ss(_mm_max_ss(_mm_setzero_ps(), _mm_set_ss(v)), k), k));
}

__forceinline uint32_t PackColor(const Vector3& c, float a)
{
    uint8_t r = UnitToByte(c.x);
    uint8_t g = UnitToByte(c.y);
    uint8_t b = UnitToByte(c.z);
    uint8_t al = UnitToByte(a);
    return ((((uint32_t)al << 8 | r) << 8 | g) << 8) | b;
}

__forceinline Vector3 Mul(const Vector3& a, const Vector3& b)
{
    Vector3 r; r.x = a.x * b.x; r.y = a.y * b.y; r.z = a.z * b.z; return r;
}
__forceinline Vector3 Scale(const Vector3& a, float s)
{
    Vector3 r; r.x = a.x * s; r.y = a.y * s; r.z = a.z * s; return r;
}
__forceinline Vector3 Make(float x, float y, float z)
{
    Vector3 r; r.x = x; r.y = y; r.z = z; return r;
}
__forceinline Vector3 Cross(const Vector3& a, const Vector3& b)
{
    Vector3 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    return r;
}
// inline normalise (same formula as 0x006e6df0)
__forceinline Vector3 Normalized(const Vector3& v)
{
    float inv = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + 1e-8f);
    return Scale(v, inv);
}

// cTransform applied to a point: rotate (row vector * matrix) when the
// rotation flag is set, then scale and translate.
__forceinline void TransformPoint(const cTransform& xf, Vector3& p)
{
    if (xf.mFlags & 2) {
        Vector3 r;
        r.x = xf.mRotation[0][0] * p.x + xf.mRotation[1][0] * p.y + xf.mRotation[2][0] * p.z;
        r.y = xf.mRotation[0][1] * p.x + xf.mRotation[1][1] * p.y + xf.mRotation[2][1] * p.z;
        r.z = xf.mRotation[0][2] * p.x + xf.mRotation[1][2] * p.y + xf.mRotation[2][2] * p.z;
        p = r;
    }
    float s = xf.mScale;
    p.x = xf.mTranslation.x + s * p.x;
    p.y = xf.mTranslation.y + s * p.y;
    p.z = xf.mTranslation.z + s * p.z;
}

__forceinline float WrapUnit(float c)
{
    if (c < 0.0f)
        c += 1.0f;
    else if (c > 1.0f)
        c -= 1.0f;
    return c;
}

} // namespace

// @ 0x00ab3370
void cRibbonEffect_StreamQuads(cRibbonEffect* fx, cIRibbonStream* stream)
{
    if (fx->mPositionHistory.mpBegin == fx->mPositionHistory.mpEnd)
        return;
    if (fx->mNumSegments < 1)
        return;

    cRibbonDescription* desc = fx->mDesc;

    // index of the last key of every curve / history used below
    uint32_t nColor       = desc->mColorCurve.size() - 1;
    uint32_t nEdgeColor   = desc->mEdgeColorCurve.size() - 1;
    uint32_t nLenAlpha    = desc->mLengthAlphaCurve.size() - 1;
    uint32_t nLenColor    = desc->mLengthColorCurve.size() - 1;
    uint32_t nStartEdge   = desc->mStartEdgeAlphaCurve.size() - 1;
    uint32_t nEndEdge     = desc->mEndEdgeAlphaCurve.size() - 1;
    uint32_t nWidth       = desc->mWidthCurve.size() - 1;
    uint32_t nOffset      = desc->mOffsetCurve.size() - 1;
    uint32_t nAlpha       = desc->mAlphaCurve.size() - 1;
    uint32_t nEdgeAlpha   = desc->mEdgeAlphaCurve.size() - 1;
    uint32_t nHistory     = fx->mPositionHistory.size() - 1;
    uint32_t nRightHist   = fx->mRightHistory.size() - 1;

    Vector3 camAxis = fx->mGlobalParams->mCameraAxis;

    // distance from the emitter to the newest history point, in segment lengths
    const Vector3* hist0 = fx->mPositionHistory.mpBegin;
    float dx = fx->mLocation.x - hist0->x;
    float dy = fx->mLocation.y - hist0->y;
    float dz = fx->mLocation.z - hist0->z;
    float dist2 = dx * dx + dy * dy + dz * dz;

    bool alongRight   = desc->test(6);
    bool freshNormal  = desc->test(7);
    bool alongX       = desc->test(5);
    bool faceCamera   = desc->test(3);

    float headRatio = 0.0f;      // fraction of the ribbon between mLocation and history[0]
    float invHeadRatio = 0.0f;
    float headLen = sqrtf(dist2) * (1.0f / desc->mSegmentLength);
    if (!desc->test(0) && nHistory != 0) {
        headRatio = headLen / (float)nHistory;
        invHeadRatio = 1.0f / headRatio;
    }

    // whole-ribbon colour / alpha at the current age
    float t = fx->mAge * fx->mInvLife;
    Vector3 color = EvalCurve(desc->mColorCurve, nColor, t);
    color = Mul(fx->mColorScale, color);
    float alpha = EvalCurve(desc->mAlphaCurve, nAlpha, t) * fx->mCurrentAlphaScale;

    Vector3 edgeColor = color;
    if (desc->test(1)) {
        Vector3 ec = EvalCurve(desc->mEdgeColorCurve, nEdgeColor, t);
        edgeColor = Mul(fx->mColorScale, ec);
    }
    float edgeAlpha = alpha;
    if (desc->test(2))
        edgeAlpha = fx->mCurrentAlphaScale * EvalCurve(desc->mEdgeAlphaCurve, nEdgeAlpha, t);

    char* buffer;
    int stride;
    int numSegments = stream->Lock((int)(fx->mPositionHistory.size() - 1) * 2, &buffer, &stride) / 2;

    float invNumSegments = 1.0f / (float)numSegments;
    float segStep;
    if (!fx->mBufferFull) {
        if (numSegments > 1)
            segStep = 1.0f / (((float)numSegments + headLen) - 1.0f);
        else
            segStep = 1.0f;
    } else {
        segStep = invNumSegments;
    }
    float halfScale = fx->mRigidTransform.mScale * 0.5f;

    // state of sample i (carried over from the previous iteration)
    Vector3  pos0, right0, color0, edge0, widthVec0;
    float    decay0, offset0, width0, alpha0, edgeAlpha0, halfWidth0;
    // state of sample i+1
    Vector3  widthVec1;
    float    halfWidth1;
    // quad corners: a/b = first half (edge, centre), c/d = second half (edge, centre)
    Vector3  v0a, v0b, v1a, v1b, v0c, v0d, v1c, v1d;
    Vector3  side0, side1;   // camera-facing half-width vectors of the last sample

    for (int i = 0; i < numSegments; ++i) {
        if (i == 0) {
            float t0 = (float)i * invNumSegments;
            float c0 = WrapUnit((float)i * segStep - fx->mOffsetCurveSlip);

            float lenAlpha = EvalCurve(desc->mLengthAlphaCurve, nLenAlpha, c0);
            Vector3 lenColor = EvalCurve(desc->mLengthColorCurve, nLenColor, c0);
            edgeAlpha0 = lenAlpha * edgeAlpha;
            alpha0 = lenAlpha * alpha;
            color0 = Mul(color, lenColor);
            edge0 = Mul(edgeColor, lenColor);
            width0 = EvalCurve(desc->mWidthCurve, nWidth, c0) * fx->mCurrentSizeScale;
            offset0 = EvalCurve(desc->mOffsetCurve, nOffset, c0);

            if (headRatio > t0) {
                // between the emitter and the newest history point
                float f = t0 * invHeadRatio;
                const Vector3* h = fx->mPositionHistory.mpBegin;
                pos0 = Make(fx->mLocation.x + f * (h->x - fx->mLocation.x),
                            fx->mLocation.y + f * (h->y - fx->mLocation.y),
                            fx->mLocation.z + f * (h->z - fx->mLocation.z));
                const Vector3* r = fx->mRightHistory.mpBegin;
                right0 = Make(fx->mRight.x + (r->x - fx->mRight.x) * f,
                              fx->mRight.y + (r->y - fx->mRight.y) * f,
                              fx->mRight.z + (r->z - fx->mRight.z) * f);
                decay0 = (fx->mPositionHistoryDecay.mpBegin[0] - 1.0f) * f + 1.0f;
            } else {
                float d = t0 - headRatio;
                float f = (float)nHistory * d;
                pos0 = SampleAt(fx->mPositionHistory.mpBegin, f);
                right0 = SampleAt(fx->mRightHistory.mpBegin, (float)nRightHist * d);
                decay0 = SampleAt(fx->mPositionHistoryDecay.mpBegin, f);
            }

            TransformPoint(fx->mRigidTransform, pos0);

            if (fx->mEmitColorMap != 0 && fx->mEmitColorMap->Contains(pos0)) {
                Vector4 mc = fx->mEmitColorMap->GetColor(pos0);
                alpha0 = mc.w * alpha0;
                color0 = Make(mc.x * color0.x, mc.y * color0.y, mc.z * color0.z);
            }
        }

        // ---- sample i+1 ----
        float t1 = (float)(i + 1) * invNumSegments;
        float u1 = Clamp01((float)(i + 1) * segStep);
        float c1 = WrapUnit(u1 - fx->mOffsetCurveSlip);

        float lenAlpha1 = EvalCurve(desc->mLengthAlphaCurve, nLenAlpha, c1);
        Vector3 lenColor1 = EvalCurve(desc->mLengthColorCurve, nLenColor, c1);
        Vector3 color1 = Mul(color, lenColor1);
        Vector3 edge1 = Mul(edgeColor, lenColor1);
        float fade = 1.0f - desc->mFade * u1;
        float alpha1 = lenAlpha1 * alpha * fade;
        float edgeAlpha1 = lenAlpha1 * edgeAlpha * fade;
        float width1 = EvalCurve(desc->mWidthCurve, nWidth, c1) * fx->mCurrentSizeScale;
        float offset1 = EvalCurve(desc->mOffsetCurve, nOffset, c1);

        Vector3 pos1, right1;
        float decay1;
        if (headRatio > t1) {
            float f = u1 * invHeadRatio;
            const Vector3* h = fx->mPositionHistory.mpBegin;
            pos1 = Make((h->x - fx->mLocation.x) * f + fx->mLocation.x,
                        (h->y - fx->mLocation.y) * f + fx->mLocation.y,
                        (h->z - fx->mLocation.z) * f + fx->mLocation.z);
            const Vector3* r = fx->mRightHistory.mpBegin;
            right1 = Make((r->x - fx->mRight.x) * f + fx->mRight.x,
                          (r->y - fx->mRight.y) * f + fx->mRight.y,
                          (r->z - fx->mRight.z) * f + fx->mRight.z);
            decay1 = (fx->mPositionHistoryDecay.mpBegin[0] - 1.0f) * f + 1.0f;
        } else {
            float d = t1 - headRatio;
            float fHist = (float)nHistory;
            pos1 = SampleAt(fx->mPositionHistory.mpBegin, Clamp01(d) * fHist);
            right1 = SampleAt(fx->mRightHistory.mpBegin, (float)nRightHist * Clamp01(d));
            decay1 = SampleAt(fx->mPositionHistoryDecay.mpBegin, Clamp01(d) * fHist);
        }

        TransformPoint(fx->mRigidTransform, pos1);

        if (fx->mEmitColorMap != 0 && fx->mEmitColorMap->Contains(pos1)) {
            Vector4 mc = fx->mEmitColorMap->GetColor(pos1);
            alpha1 = mc.w * alpha1;
            color1 = Make(mc.x * color1.x, mc.y * color1.y, mc.z * color1.z);
        }

        // ---- half-width vectors (non camera-facing modes) ----
        if (i == 0) {
            halfWidth0 = width0 * halfScale;
            if (alongX)
                widthVec0 = Make(halfWidth0, 0.0f, 0.0f);
            else if (alongRight)
                widthVec0 = Scale(right0, halfWidth0);
            else
                widthVec0 = Make(0.0f, 0.0f, halfWidth0);
        } else {
            widthVec0 = widthVec1;
            halfWidth0 = halfWidth1;
        }
        // NB: the original tapers sample i+1 using sample i's width.
        halfWidth1 = (1.0f - u1 * desc->mTaper) * width0 * halfScale;
        if (alongX)
            widthVec1 = Make(halfWidth1, 0.0f, 0.0f);
        else if (alongRight)
            widthVec1 = Scale(right1, halfWidth1);
        else
            widthVec1 = Make(0.0f, 0.0f, halfWidth1);

        // ---- start / end fade of the edge alpha ----
        float edgeAlphaQuad0;
        if (i == 0) {
            alpha0 = EvalCurve(desc->mStartEdgeAlphaCurve, nStartEdge, t) * alpha0;
            edgeAlphaQuad0 = EvalCurve(desc->mStartEdgeAlphaCurve, nStartEdge, t) * edgeAlpha0;
        } else {
            edgeAlphaQuad0 = edgeAlpha0;
        }
        if (i == numSegments - 1) {
            alpha1 = EvalCurve(desc->mEndEdgeAlphaCurve, nEndEdge, t) * alpha1;
            edgeAlpha1 = EvalCurve(desc->mEndEdgeAlphaCurve, nEndEdge, t) * edgeAlpha1;
        }

        uint32_t colorQuad0 = PackColor(color0, decay0 * alpha0);
        uint32_t colorQuad1 = PackColor(color1, decay1 * alpha1);
        uint32_t edgeQuad0  = PackColor(edge0, decay0 * edgeAlphaQuad0);
        uint32_t edgeQuad1  = PackColor(edge1, decay1 * edgeAlpha1);

        // ---- first half: edge a, centre b ----
        if (faceCamera) {
            if (i == 0) {
                Vector3 d = Make(pos1.x - pos0.x, pos1.y - pos0.y, pos1.z - pos0.z);
                Vector3 n = Normalized(Cross(camAxis, d));
                Vector3 a = Scale(n, halfWidth0);
                Vector3 b = Scale(n, offset0);
                v0a = Make(pos0.x - a.x + b.x, pos0.y - a.y + b.y, pos0.z - a.z + b.z);
                v0b = Make(b.x + pos0.x, b.y + pos0.y, b.z + pos0.z);
                side0 = a;
            } else {
                v0b = v1b;
                v0a = v1a;
            }

            Vector3 dir = Normalized(Make(pos1.x - pos0.x, pos1.y - pos0.y, pos1.z - pos0.z));
            Vector3 n1;
            if (freshNormal) {
                n1 = Normalized(Cross(camAxis, dir));
            } else {
                // keep the previous side vector, made perpendicular to the direction
                Vector3 m = Normalized(Cross(dir, side0));
                n1 = Normalized(Cross(m, dir));
            }
            Vector3 a1 = Scale(n1, halfWidth1);
            Vector3 b1 = Scale(n1, offset1);
            v1a = Make(pos1.x - a1.x + b1.x, pos1.y - a1.y + b1.y, pos1.z - a1.z + b1.z);
            v1b = Make(pos1.x + b1.x, pos1.y + b1.y, pos1.z + b1.z);
            side0 = a1;
        } else {
            v0b = pos0;
            if (alongX)
                v0b = Make(pos0.x + offset0, pos0.y, pos0.z);
            if (alongRight) {
                Vector3 r0 = Scale(right0, offset0);
                Vector3 r1 = Scale(right1, offset1);
                v0a = Make(widthVec0.x + v0b.x + r0.x, v0b.y + widthVec0.y + r0.y, v0b.z + widthVec0.z + r0.z);
                v0b = Make(r0.x + v0b.x, v0b.y + r0.y, v0b.z + r0.z);
                v1b = Make(r1.x + pos1.x, pos1.y + r1.y, pos1.z + r1.z);
                v1a = Make(widthVec1.x + pos1.x + r1.x, widthVec1.y + pos1.y + r1.y, widthVec1.z + pos1.z + r1.z);
            } else {
                v0a = Make(widthVec0.x + v0b.x, v0b.y + widthVec0.y, v0b.z + widthVec0.z + offset0);
                v0b = Make(v0b.x, v0b.y, v0b.z + offset0);
                v1b = Make(pos1.x, pos1.y, pos1.z + offset1);
                v1a = Make(widthVec1.x + pos1.x, widthVec1.y + pos1.y, offset1 + (widthVec1.z + pos1.z));
            }
        }

        buffer = fx->AddQuad(buffer, i, stride, 0.0f, v0b, v0a, v1b, v1a,
                             colorQuad0, edgeQuad0, colorQuad1, edgeQuad1);

        // ---- second half: edge c, centre d ----
        if (faceCamera) {
            if (i == 0) {
                Vector3 d = Make(pos1.x - pos0.x, pos1.y - pos0.y, pos1.z - pos0.z);
                Vector3 n = Normalized(Cross(camAxis, d));
                Vector3 a = Scale(n, halfWidth0);
                Vector3 b = Scale(n, offset0);
                v0c = Make(pos0.x + a.x + b.x, pos0.y + a.y + b.y, pos0.z + a.z + b.z);
                v0d = Make(pos0.x + b.x, pos0.y + b.y, pos0.z + b.z);
                side1 = a;
            } else {
                v0c = v1c;
                v0d = v1d;
            }

            Vector3 dir = Normalized(Make(pos1.x - pos0.x, pos1.y - pos0.y, pos1.z - pos0.z));
            Vector3 n1;
            if (freshNormal) {
                n1 = Normalized(Cross(camAxis, dir));
            } else {
                Vector3 m = Normalized(Cross(dir, side1));
                Vector3 k = Cross(m, dir);
                n1 = Normalize(k);
            }
            Vector3 a1 = Scale(n1, halfWidth1);
            Vector3 b1 = Make(offset1 * n1.x, n1.y * offset1, n1.z * offset1);
            v1c = Make(pos1.x + a1.x + b1.x, a1.y + pos1.y + b1.y, a1.z + pos1.z + b1.z);
            v1d = Make(pos1.x + b1.x, pos1.y + b1.y, pos1.z + b1.z);
            side1 = a1;
        } else if (alongX) {
            v0c = Make(pos0.x - widthVec0.x + offset0, pos0.y - widthVec0.y, pos0.z - widthVec0.z);
            v0d = Make(pos0.x + offset0, pos0.y, pos0.z);
            v1d = Make(offset1 + pos1.x, pos1.y, pos1.z);
            v1c = Make(pos1.x - widthVec1.x + offset1, pos1.y - widthVec1.y, pos1.z - widthVec1.z);
        } else if (alongRight) {
            Vector3 r0 = Scale(right0, offset0);
            Vector3 r1 = Scale(right1, offset1);
            v0c = Make(pos0.x - widthVec0.x + r0.x, pos0.y - widthVec0.y + r0.y, pos0.z - widthVec0.z + r0.z);
            v0d = Make(r0.x + pos0.x, pos0.y + r0.y, pos0.z + r0.z);
            v1d = Make(r1.x + pos1.x, pos1.y + r1.y, pos1.z + r1.z);
            v1c = Make(pos1.x - widthVec1.x + r1.x, pos1.y - widthVec1.y + r1.y, pos1.z - widthVec1.z + r1.z);
        } else {
            v0c = Make(pos0.x - widthVec0.x, pos0.y - widthVec0.y, pos0.z - widthVec0.z + offset0);
            v0d = Make(pos0.x, pos0.y, pos0.z + offset0);
            v1d = Make(pos1.x, pos1.y, pos1.z + offset1);
            v1c = Make(pos1.x - widthVec1.x, pos1.y - widthVec1.y, pos1.z - widthVec1.z + offset1);
        }

        buffer = fx->AddQuad(buffer, i, stride, 0.5f, v0c, v0d, v1c, v1d,
                             edgeQuad0, colorQuad0, edgeQuad1, colorQuad1);

        // ---- sample i+1 becomes sample i ----
        color0 = color1;
        edge0 = edge1;
        alpha0 = alpha1;
        right0 = right1;
        edgeAlpha0 = edgeAlpha1;
        width0 = width1;
        offset0 = offset1;
        pos0 = pos1;
        decay0 = decay1;
    }

    stream->Unlock();
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
