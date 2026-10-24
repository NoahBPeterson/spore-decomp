// checkerlib 4x4 Gauss-Jordan solver (A x = B in place, partial pivoting, B = numRhs 4-vectors).
// Built /O2 /arch:SSE.  cl itself unrolls the simple loops by four.
#include <math.h>
#pragma intrinsic(fabs)
#pragma intrinsic(sin, cos)

namespace checkerlib
{
class vector_4 { public: float x, y, z, w; };
class matrix_4x4
{
public:
    float el[16];
};

inline void SwapF(float& a, float& b) { float t = a; a = b; b = t; }

// @ 0x009e6040
// returns false when the matrix is singular.
bool LinearSolveInPlace(matrix_4x4& m, vector_4* bv, int numRhs)
{
    float* a = m.el;
    float* b = (float*)bv;
    const int N = 4;

    for (int k = 0; k < N; ++k)
    {
        // pivot search over column k
        float best = 1.1754944e-38f;
        int piv = N;
        for (int i = k; i < N; ++i)
        {
            float v = (float)fabs(a[i * 4 + k]);
            if (best < v) { best = v; piv = i; }
        }
        if (piv >= N)
            return false;

        if (piv != k)
        {
            for (int j = k; j < N; ++j)
                SwapF(a[piv * 4 + j], a[k * 4 + j]);
            for (int j = 0; j < numRhs; ++j)
                SwapF(b[j * 4 + piv], b[j * 4 + k]);
        }

        float p = a[k * 4 + k];
        if (fabs(p) < 1e-6)
            return false;
        float inv = 1.0f / p;

        // scale the pivot row
        for (int j = k + 1; j < N; ++j)
            a[k * 4 + j] = inv * a[k * 4 + j];
        for (int j = 0; j < numRhs; ++j)
            b[j * 4 + k] = inv * b[j * 4 + k];

        // eliminate below
        for (int r = k + 1; r < N; ++r)
        {
            float f = a[r * 4 + k];
            for (int c = k + 1; c < N; ++c)
                a[r * 4 + c] = a[r * 4 + c] - a[k * 4 + c] * f;
            for (int c = 0; c < numRhs; ++c)
                b[c * 4 + r] = b[c * 4 + r] - b[c * 4 + k] * f;
        }
    }

    // back substitution
    for (int i = N - 1; i >= 0; --i)
    {
        for (int jj = N - 1; jj > i; --jj)
        {
            for (int j = 0; j < numRhs; ++j)
                b[j * 4 + i] = b[j * 4 + i] - b[j * 4 + jj] * a[i * 4 + jj];
        }
    }
    return true;
}

class matrix_3x3
{
public:
    float el[9];

    // (defined below, 0x009e5f50)
    // Post-multiply by a rotation about the Y axis: this = this * Ry(angle).
    void ConcatenateYRotation(float angle);
};

// @ 0x009e5f50
void matrix_3x3::ConcatenateYRotation(float angle)
{
    float s = (float)sin(angle);
    float c = (float)cos(angle);
    float m0 = el[0];
    float m1 = el[1];
    float m2 = el[2];

    el[0] = m0 * c + el[6] * s;
    el[6] = el[6] * c - m0 * s;
    el[1] = m1 * c + el[7] * s;
    el[2] = m2 * c + el[8] * s;
    el[7] = el[7] * c - m1 * s;
    el[8] = el[8] * c - m2 * s;
}
} // namespace checkerlib

// ======================================================================
// gold7 batch: the SPORE creature-animation IK cluster
// ======================================================================

extern float g_zero;                                    // 0x013eb1bc
extern const float g_negOne;                            // 0x013eb1bc (-1.0f)
extern const float HK_REAL_ONE;                         // 0x01485720
extern const float g_IKConst70;                         // 0x01470f1c
extern const float g_IKConst84;                         // 0x014853e0
extern const float g_IKConst1c;                         // 0x013ef61c

// ---- goal state record used by the Chebyshev-merge helpers -----------
// byte0 = flags (low 3 bits = kind), byte1 = pad, byte2 = cached index
// (0xff = none), byte3 = count.
struct GoalState {
    unsigned char mFlags;                               // +0x00
    unsigned char mPad01;                               // +0x01
    unsigned char mIndex;                               // +0x02
    unsigned char mCount;                               // +0x03

    void Reset();                                       // 0x009e6740
    void MergeThisBIdx(unsigned childIdx);              // 0x009e6750
    void MergeChild(unsigned childState, unsigned childIdx); // 0x009e67c0
};

// @ 0x009e6740
// GoalState::Reset(): kind 4, no cached index.
void GoalState::Reset()
{
    mFlags = 4;
    mPad01 = 0;
    mIndex = 0xff;
    mCount = 0xff;
}

// @ 0x009e6750
// GoalState::MergeThisBIdx(unsigned childIdx): fold a direct child id in.
void GoalState::MergeThisBIdx(unsigned childIdx)
{
    switch ((mFlags & 7) - 1)
    {
    case 2:
        mFlags = (unsigned char)((mFlags & 0xf9) | 0x11);
        ++mCount;
        mIndex = 0xff;
        break;
    case 0:
        mFlags |= 0x10;
        ++mCount;
        break;
    case 1:
        mFlags = (unsigned char)((mFlags & 0xf9) | 0x11);
        mCount = 2;
        mIndex = 0xff;
        break;
    case 3:
        mFlags = 0x10;
        mCount = (unsigned char)childIdx;
        mIndex = 0xff;
        break;
    }
}

// @ 0x009e67c0
// GoalState::MergeChild(unsigned childState, unsigned childIdx): fold a child
// goal's packed state (low 3 bits = kind, top byte = count) into this goal.
void GoalState::MergeChild(unsigned childState, unsigned childIdx)
{
    if (((unsigned char)childState & 7) == 4)
        return;

    switch (mFlags & 7)
    {
    case 3:
        if (childIdx != mIndex)
        {
            mFlags = (unsigned char)((mFlags & 0xf9) | 1);
            mIndex = 0xff;
        }
        // fall through to the shared tail
    case 1:
        switch ((unsigned char)childState & 7)
        {
        case 1:
        case 3:
            mCount = (unsigned char)(mCount + (childState >> 24));
            return;
        case 0:
        case 2:
            ++mCount;
            return;
        }
        return;
    case 0:
        mFlags = (unsigned char)((mFlags & 0xf9) | 1);
        mIndex = 0xff;
        mCount = 1;
        switch ((unsigned char)childState & 7)
        {
        case 1:
        case 3:
            mCount = (unsigned char)((childState >> 24) + 1);
            return;
        case 0:
        case 2:
            mCount = 2;
            return;
        }
        return;
    case 2:
        mCount = 1;
        if (childIdx == mIndex)
            mFlags = (unsigned char)((mFlags & 0xfb) | 3);
        else
        {
            mFlags = (unsigned char)((mFlags & 0xf9) | 1);
            mIndex = 0xff;
        }
        switch ((unsigned char)childState & 7)
        {
        case 1:
        case 3:
            mCount = (unsigned char)((childState >> 24) + 1);
            return;
        case 0:
        case 2:
            mCount = 2;
            return;
        }
        return;
    case 4:
        mCount = (unsigned char)(childState >> 24);
        mFlags = (unsigned char)((childState & 1) | 2);
        mIndex = (unsigned char)childIdx;
        return;
    default:
        return;
    }
}

// ---- the objects the IK code walks ---------------------------------
// Every creature-bone record exposes a "dirty / recompute" byte at +0x234;
// the two aim blocks sit at +0x1b0 apart.
struct IkBone {
    unsigned char pad00[0x210];
    float mBoneRadius;                                  // +0x210
    unsigned char pad214[0x234 - 0x214];
    unsigned char mDirty;                               // +0x234
};

// The constraint record: two bone pointers (aim/target) plus derived poses.
struct IkBonePair {
    IkBone*       mAim;                                 // +0x000
    IkBone*       mTarget;                              // +0x004
    IkBone*       mAimSub;                              // +0x008  = mAim + 0x1b0
    IkBone*       mTargetSub;                           // +0x00c  = mTarget + 0x1b0 (Construct)
                                                        //           or arg5 (ConstructEx)
    float         mWeight;                              // +0x010
    float         mBoneALength;                         // +0x014  = mAim->mBoneRadius
    float         mBoneBLength;                         // +0x018  = mTarget->mBoneRadius
    float         mPosA[3];                             // +0x01c
    float         mPosB[3];                             // +0x028
    float         mPosC[3];                             // +0x034
    float         mPosD[3];                             // +0x040
    float         mPosE[3];                             // +0x04c
    float         mPosF[3];                             // +0x058
    float         mPosG[3];                             // +0x064
    float         mPosH[3];                             // +0x070
    float         mPosI[3];                             // +0x07c
    float         mRadiiCacheA;                         // +0x088
    float         mCachedALength;                       // +0x08c  = mAim->mBoneRadius
    float         mCachedBLength;                       // +0x090  = mTarget->mBoneRadius
    unsigned      mMode;                                // +0x094
    float         mCoef98;                              // +0x098
    float         mCoef9c;                              // +0x09c
    float         mCoefA0;                              // +0x0a0
    float         mCoefA4;                              // +0x0a4
    float         mCoefA8;                              // +0x0a8
    float         mCoefAc;                              // +0x0ac
    float         mCoefB0;                              // +0x0b0
    float         mCoefB4;                              // +0x0b4
    float         mCoefB8;                              // +0x0b8
    float         mCoefBc;                              // +0x0bc
    float         mCoefC0;                              // +0x0c0
    float         mCoefC4;                              // +0x0c4
    unsigned char pad0c8[(0x0cc - 0x0c8)];
    unsigned      mCC;                                  // +0x0cc
    unsigned      mD0;                                  // +0x0d0
    unsigned      mD4;                                  // +0x0d4
    unsigned char padD8[(0x108 - 0x0d8)];
    unsigned      m108;                                 // +0x108

    void Construct(IkBone* aim, IkBone* target, float weight, unsigned mode);      // 0x009e68f0
    void ConstructEx(IkBone* aim, IkBone* aimSub, float aLen, IkBone* target,
                     IkBone* targetSub, float bLen, float weight, unsigned mode); // 0x009e6a20
    void BuildCoefficients(float a, float b, float c, float d);                    // 0x009e6b40
};

// The 3x3 tilt-matrix record written by BuildOuterProduct (this = the matrix).
struct IkTiltMatrix {
    float         el[9];                                // +0x000 .. +0x020

    void BuildOuterProduct(const float* v, float a, float b);                      // 0x009e6cf0
};

// The per-creature IK scratch record cleared by ik_utils::Clear.
struct IkCreature {
    unsigned char pad00[0x18c];
    unsigned      m18c;                                 // +0x18c
    unsigned char pad190[0x1c8 - 0x190];
    float         m1c8;                                 // +0x1c8
    float         m1cc;                                 // +0x1cc
    float         m1d0;                                 // +0x1d0
    unsigned char pad1d4[0x1fc - 0x1d4];
    unsigned char m1fc;                                 // +0x1fc
    unsigned char m1fd;                                 // +0x1fd
    unsigned char pad1fe[0x224 - 0x1fe];
    unsigned      m224;                                 // +0x224
    unsigned      m228;                                 // +0x228
    unsigned      m22c;                                 // +0x22c
    unsigned      m230;                                 // +0x230
    unsigned char m234;                                 // +0x234
    unsigned char m235;                                 // +0x235
    unsigned      m238;                                 // +0x238
    float         m23c;                                 // +0x23c
    unsigned      m240;                                 // +0x240
    unsigned      m244;                                 // +0x244
    unsigned char pad248[0x264 - 0x248];
    float         m264;                                 // +0x264
    float         m268;                                 // +0x268
    float         m26c;                                 // +0x26c

    void ClearIkCache();                                // 0x009e6c60
};

// @ 0x009e68f0
void IkBonePair::Construct(IkBone* aim, IkBone* target, float weight, unsigned mode)
{
    mTarget = target;
    mAim = aim;
    mWeight = weight;
    mTargetSub = (IkBone*)((char*)target + 0x1b0);
    mAimSub = (IkBone*)((char*)aim + 0x1b0);
    mPosA[2] = 0.0f; mPosA[1] = 0.0f; mPosA[0] = 0.0f;
    mPosB[2] = 0.0f; mPosB[1] = 0.0f; mPosB[0] = 0.0f;
    mPosC[2] = 0.0f; mPosC[1] = 0.0f; mPosC[0] = 0.0f;
    mPosD[2] = 0.0f; mPosD[1] = 0.0f; mPosD[0] = 0.0f;
    mPosE[2] = 0.0f; mPosE[1] = 0.0f; mPosE[0] = 0.0f;
    mPosF[2] = 0.0f; mPosF[1] = 0.0f; mPosF[0] = 0.0f;
    mPosG[2] = 0.0f; mPosG[1] = 0.0f; mPosG[0] = 0.0f;
    mPosH[2] = 0.0f; mPosH[1] = 0.0f; mPosH[0] = 0.0f;
    mPosI[2] = 0.0f; mPosI[1] = 0.0f; mPosI[0] = 0.0f;

    mCachedALength = aim->mBoneRadius;
    mCachedBLength = target->mBoneRadius;
    mMode = mode;
    mBoneALength = mCachedALength;
    mCC = 0;
    mBoneBLength = mCachedBLength;
    mD0 = 0;
    mD4 = 0;
    m108 = 0;
    aim->mDirty = 1;
    target->mDirty = 1;
}

// @ 0x009e6a20
void IkBonePair::ConstructEx(IkBone* aim, IkBone* aimSub, float aLen, IkBone* target,
                             IkBone* targetSub, float bLen, float weight, unsigned mode)
{
    mAim = aim;
    mTarget = target;
    mAimSub = aimSub;
    mWeight = weight;
    mTargetSub = targetSub;
    mPosA[2] = 0.0f; mPosA[1] = 0.0f; mPosA[0] = 0.0f;
    mPosB[2] = 0.0f; mPosB[1] = 0.0f; mPosB[0] = 0.0f;
    mPosC[2] = 0.0f; mPosC[1] = 0.0f; mPosC[0] = 0.0f;
    mPosD[2] = 0.0f; mPosD[1] = 0.0f; mPosD[0] = 0.0f;
    mPosE[2] = 0.0f; mPosE[1] = 0.0f; mPosE[0] = 0.0f;
    mPosF[2] = 0.0f; mPosF[1] = 0.0f; mPosF[0] = 0.0f;
    mPosG[2] = 0.0f; mPosG[1] = 0.0f; mPosG[0] = 0.0f;
    mPosH[2] = 0.0f; mPosH[1] = 0.0f; mPosH[0] = 0.0f;
    mPosI[2] = 0.0f; mPosI[1] = 0.0f; mPosI[0] = 0.0f;

    mMode = mode;
    mCC = 0;
    mD0 = 0;
    mD4 = 0;
    m108 = 0;
    mCachedALength = aLen;
    mCachedBLength = bLen;
    mBoneALength = mCachedALength;
    mBoneBLength = mCachedBLength;
    aim->mDirty = 1;
    target->mDirty = 1;
}

// @ 0x009e6b40
// Precompute the two-bone IK solver coefficients from four bone lengths
// (a/c = the paired lengths of the first chain, b/d = the second chain).
void IkBonePair::BuildCoefficients(float a, float b, float c, float d)
{
    mCoef98 = a - c;
    mCoef9c = HK_REAL_ONE / a;
    float f1 = g_negOne / ((a * c) * g_IKConst84);
    mCoefA4 = f1;
    mCoefAc = (f1 * (c - a)) * (c - a);
    mCoefA0 = a + c;
    mCoefB0 = b - d;
    float f2 = HK_REAL_ONE / ((b * d) * g_IKConst84);
    mCoefB8 = ((d - b) * f2) * g_IKConst70;
    mCoefB4 = f2;
    mCoefA8 = (f1 * (a + c)) * g_IKConst1c;
    mCoefBc = (f2 * (b + d)) * (b + d);
    mCoefC0 = b + d;
    mCoefC4 = HK_REAL_ONE / b;
}

// @ 0x009e6c60
// Clear the cached IK-solver scratch state on the creature.
void IkCreatureClear(IkCreature* obj)
{
    obj->m18c = 0;
    obj->m22c = 0xffffffff;
    obj->m230 = 0;
    obj->m224 = 0;
    obj->m228 = 0;
    obj->m234 = 0;
    obj->m240 = 0;
    obj->m244 = 0;
    obj->m235 = 0;
    obj->m23c = 0.0f;
    obj->m238 = 0;
    obj->m1fc = 0;
    obj->m1fd = 0;
    obj->m1c8 = 0.0f;
    obj->m1cc = 0.0f;
    obj->m1d0 = 0.0f;
    obj->m264 = 0.0f;
    obj->m268 = 0.0f;
    obj->m26c = 0.0f;
}

// @ 0x009e6cf0
// Build the 3x3 outer-product tilt matrix this = mix(I, v (x) v, a) plus the
// b-scaled off-diagonal terms; v must be a unit vector.
void IkTiltMatrix::BuildOuterProduct(const float* v, float a, float b)
{
    float fVar1 = v[1];
    float fVar2 = v[2];
    float fVar3 = v[0];

    el[0] = (HK_REAL_ONE - fVar3 * fVar3) * a + fVar3 * fVar3;
    float fVar4 = (HK_REAL_ONE - a) * fVar2;
    float fVar6 = ((HK_REAL_ONE - a) * fVar1) * fVar3;
    el[1] = fVar6 - fVar2 * b;
    float fVar5 = fVar4 * fVar3;
    el[2] = fVar1 * b + fVar5;
    el[3] = fVar2 * b + fVar6;
    fVar4 = fVar4 * fVar1;
    el[7] = fVar3 * b + fVar4;
    el[4] = (HK_REAL_ONE - fVar1 * fVar1) * a + fVar1 * fVar1;
    el[5] = fVar4 - fVar3 * b;
    el[6] = fVar5 - fVar1 * b;
    el[8] = (HK_REAL_ONE - fVar2 * fVar2) * a + fVar2 * fVar2;
}


