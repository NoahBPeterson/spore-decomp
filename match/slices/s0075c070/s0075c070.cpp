// Slice s0075c070: SP::cMultiBlender serialization/rebuild helpers.
// Optimized /O2, SSE (/arch:SSE2) with 16-byte aligned frames.
// 0075c070 (RebuildBlend: per-node inverse-transform product, matrix stack, matrix-to-quaternion)
// and 0075ca60 (UpdateBlend: weighted blend + additive quaternion layers) are complete scalar
// reconstructions of what the original does with 4-wide SSE (see nonmatching.txt).
#include "types.h"

namespace rw { namespace oldanimation {
struct Node { float m[16]; };
}}

// One animation key: quaternion (x y z w), translation (x y z), then format-dependent data.
struct Pose { float q[4]; float p[3]; };

// Per-animation interpolator (stride mInterpolatorStride inside cMultiBlender::mInterpolators).
struct Interp {
    Pose* GetNode(int node);                                   // 0x011fda50 (thiscall, ret 4)
};
struct InterpInit { Interp* mpInterp; int mPad[3]; };

void __cdecl BlendNodes(Pose* dst, Pose* src, Pose* b, unsigned fmt, float w);        // 0x011ff680
void __cdecl SetIdentityNodes(void* dst, void* fmt, unsigned count, int stride);       // 0x0075a980
void __cdecl InitInterpolator(InterpInit* ii, unsigned numNodes, unsigned fmt, int z); // 0x011fe0d0
void __cdecl MatrixToQuat(float* outQuat, const float* m4x4, const float* zero4);      // 0x0075ad80
extern "C" void* __cdecl MemCopy(void* d, const void* s, unsigned n);                  // 0x011e0744

namespace SP {

using namespace rw::oldanimation;

class cMultiBlender {
public:
    char pad00[0x08];
    void* m_owner;                  // +0x08
    union { unsigned int u; unsigned char b[4]; } m_format; // +0x0c (byte 1 = key format)
    int m_strideFlags;              // +0x10
    unsigned int m_numNodes;        // +0x14
    unsigned int m_bufferValid;     // +0x18
    unsigned int m_maxNumQuats;     // +0x1c
    void* m_BlendCallBack;          // +0x20
    float* mWeights;                // +0x24
    bool* mAnimating;               // +0x28
    bool* mBlending;                // +0x2c
    char* mInterpolators;           // +0x30
    char* mPoseKeys;                // +0x34
    int mMaxAnims;                  // +0x38
    unsigned int mInterpolatorStride;// +0x3c
    int mNumAnims;                  // +0x40
    float mTotalWeight;             // +0x44
    int mFirstBlend;                // +0x48
    int mFirstAdd;                  // +0x4c
    bool mLooping;                  // +0x50

    // @ 0x0075c070  (thiscall, 2 args, ret 8)
    void RebuildBlend(int param2, int* param3);

    // @ 0x0075c9d0  (__cdecl, 7 args, EH frame) -- complete but not byte-exact
    // @ 0x0075ca60  (thiscall, 0 args)
    void UpdateBlend();

    // callees (out of line, masked relocations)
    int  SetupBlend(void* a, void* b, void* c, int d, void* e); // 0x0075b2c0
    int  AllocSlot2();                                           // 0x0075a980
    Interp* GetInterp(int i) { return (Interp*)(mInterpolators + mInterpolatorStride * i); }
};

// @ 0x0075c070
// Reset the blend state, prime every interpolator, then convert the node matrices at `param2`
// (16 floats each, rows 0-2 rotation, row 3 translation) into pose keys at mPoseKeys. Each key is
// inverse(node) * (current matrix); `param3` is a pointer to per-node stack opcodes (& 3):
// 0 = current = node, 1 = pop current, 2 = push current then current = node, 3 = keep current.
void cMultiBlender::RebuildBlend(int param2, int* param3)
{
    mNumAnims = 0;
    mTotalWeight = 0.0f;
    mFirstBlend = mMaxAnims;
    mFirstAdd = mMaxAnims;
    mLooping = true;
    m_bufferValid = 0;
    for (int i = 0; i < mMaxAnims; i++) {
        InterpInit ii;
        ii.mpInterp = (Interp*)(mInterpolatorStride * i + (unsigned)mInterpolators);
        ii.mPad[0] = 0; ii.mPad[1] = 0; ii.mPad[2] = 0;
        InitInterpolator(&ii, m_numNodes, m_format.u, 0);
    }
    if (mPoseKeys == 0 || param2 == 0)
        return;

    int numNodes = (int)m_numNodes;
    __declspec(align(16)) float cur[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f };
    __declspec(align(16)) float stackBase[63 * 16];
    __declspec(align(16)) float zero4[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    float* sp = stackBase;
    if (numNodes <= 0)
        return;

    bool hasScale = m_format.b[1] >= 6;
    const float* S = (const float*)param2;
    for (int i = 0; i < numNodes; i++, S += 16) {
        float s0 = S[0], s1 = S[1], s2 = S[2];
        float s4 = S[4], s5 = S[5], s6 = S[6];
        float s8 = S[8], s9 = S[9], s10 = S[10];
        float t0 = S[12], t1 = S[13], t2 = S[14];
        float n0 = 0.0f - ((s0 * t0 + s1 * t1) + s2 * t2);
        float n1 = 0.0f - ((s4 * t0 + s5 * t1) + s6 * t2);
        float n2 = 0.0f - ((s8 * t0 + s9 * t1) + s10 * t2);

        __declspec(align(16)) float L[16];
        for (int c = 0; c < 4; c++) {
            L[c]      = (s0 * cur[c] + s4 * cur[4 + c]) + s8 * cur[8 + c];
            L[4 + c]  = (s1 * cur[c] + s5 * cur[4 + c]) + s9 * cur[8 + c];
            L[8 + c]  = (s2 * cur[c] + s6 * cur[4 + c]) + s10 * cur[8 + c];
            L[12 + c] = ((n0 * cur[c] + n1 * cur[4 + c]) + n2 * cur[8 + c]) + 1.0f * cur[12 + c];
        }
        __declspec(align(16)) float q[4];
        MatrixToQuat(q, L, zero4);

        float* dst = (float*)(m_strideFlags * i + mPoseKeys);
        dst[0] = q[0]; dst[1] = q[1]; dst[2] = q[2]; dst[3] = q[3];
        dst[4] = L[12]; dst[5] = L[13]; dst[6] = L[14];
        if (hasScale) {
            dst[7] = 1.0f; dst[8] = 1.0f; dst[9] = 1.0f;
        }

        unsigned op = *(unsigned*)(*param3 + i * 4) & 3;
        if (op == 2) {
            for (int k = 0; k < 16; k++) sp[k] = cur[k];
            sp += 16;
            op = 0;
        }
        if (op == 0) {
            for (int k = 0; k < 16; k++) cur[k] = S[k];
        } else if (op == 1) {
            for (int k = 0; k < 16; k++) cur[k] = sp[k - 16];
            sp -= 16;
        }
    }
}

// @ 0x0075c9d0
// __cdecl wrapper: p is a handle-to-pointer; if non-null it sets up the blend
// source, then always runs the big RebuildBlend(flag5, arg6). SEH state spans the
// first call (local object), hence the EH prolog. Behaviorally complete.
extern "C" int __cdecl cMultiBlender_RebuildWrapper(void** p, void* a, void* b, void* c,
                                                    int flag, void* d, void* e)
{
    cMultiBlender* obj = (cMultiBlender*)*p;
    if (obj != 0)
        obj->SetupBlend(a, b, c, flag != 0, e);
    obj->RebuildBlend(flag, (int*)d);
    return (int)obj;
}

// @ 0x0075ca60
// Blend the weighted animation layers into the output pose buffer, then apply the additive
// layers as quaternion deltas (conjugate/multiply) plus translation deltas.
void cMultiBlender::UpdateBlend() {
    int firstBlend = mFirstBlend;
    unsigned numNodes = m_numNodes;
    float baseWeight = 0.0f;
    if (firstBlend != mMaxAnims) {
        if (mTotalWeight >= 1.0f) {
            baseWeight = mWeights[firstBlend];
            MemCopy(m_owner, GetInterp(firstBlend)->GetNode(0), m_strideFlags * numNodes);
            firstBlend++;
            goto blend;
        }
        baseWeight = 1.0f - mTotalWeight;
    }
    if (mPoseKeys)
        MemCopy(m_owner, mPoseKeys, m_strideFlags * numNodes);
    else
        SetIdentityNodes(m_owner, &m_format, numNodes, m_strideFlags);
blend:
    Pose* dst = (Pose*)m_owner;
    for (unsigned n = 0; n < numNodes; n++) {
        int numAnims = mNumAnims;
        float total = baseWeight;
        for (int a = firstBlend; a < numAnims; a++) {
            if (mBlending[a]) {
                float w = mWeights[a];
                total = w + total;
                if (0.0f < w)
                    BlendNodes(dst, dst, GetInterp(a)->GetNode(n), m_format.u, w / total);
            }
        }
        for (int a = mFirstAdd; a < mNumAnims; a++) {
            if (!mBlending[a]) {
                Pose* k = (Pose*)(m_strideFlags * n + mPoseKeys);
                Pose* p = GetInterp(a)->GetNode(n);
                float p0 = p->q[0], p1 = p->q[1], p2 = p->q[2], p3 = p->q[3];
                float k0 = -k->q[0], k1 = -k->q[1], k2 = -k->q[2], k3 = k->q[3];
                float q0 = (k3 * p0 + p3 * k0) + (p2 * k1 - p1 * k2);
                float q1 = (p1 * k3 + p3 * k1) + (k2 * p0 - p2 * k0);
                float q2 = (p2 * k3 + p3 * k2) + (p1 * k0 - p0 * k1);
                float qw = p->q[3] * k->q[3] - ((p2 * k2 + p0 * k0) + p1 * k1);
                dst->p[0] = dst->p[0] + (p->p[0] - k->p[0]);
                dst->p[1] = (p->p[1] - k->p[1]) + dst->p[1];
                dst->p[2] = (p->p[2] - k->p[2]) + dst->p[2];
                float r1 = dst->q[1], r2 = dst->q[2], r0 = dst->q[0], r3 = dst->q[3];
                dst->q[0] = (r3 * q0 + qw * r0) + (r1 * q2 - r2 * q1);
                dst->q[1] = (r3 * q1 + r1 * qw) + (r2 * q0 - r0 * q2);
                dst->q[2] = (r3 * q2 + r2 * qw) + (r0 * q1 - r1 * q0);
                dst->q[3] = dst->q[3] * qw - ((r1 * q1 + r2 * q2) + r0 * q0);
            }
        }
        dst = (Pose*)((char*)dst + m_strideFlags);
    }
}

} // namespace SP
