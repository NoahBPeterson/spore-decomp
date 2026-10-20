// nSPCreatureAnim spine / jiggle solver helpers (0x009b4e00-0x009b5c50).
// Object file <SporeApp>/CreatureAnim.obj.
//
// The class walks an array of "bone" records (stride 0x468) hung off +0x384;
// each record has local offsets at +0x10c, a transform at +0x118..0x344, a
// world position at +0x344, an attached offset at +0x350, two signed linked
// indices at +0x1f8/+0x1fc, a child span at +0x204/+0x208 and a bit set at
// +0x1b8.  QuaternionVectorTransform is imported from checkerlib.
//
// Offsets follow the retail image.  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <stddef.h>
#include <math.h>
#pragma intrinsic(fabs)
#pragma intrinsic(sqrt)

extern const float g_13eb960;  // 0.01f            0x013eb960
extern const float g_13f4fd0;  // 4294967296.0f    0x013f4fd0
extern const float g_13f18c8;  // 1e-06f           0x013f18c8
extern const float g_14471fc;  // 0.0f (or small)  0x014471fc
extern const float g_1550b04;  // int  0x01550b04 (global gate)
extern const float g_1550d3c;  // float 0x01550d3c
extern const float g_1550d40;  // float 0x01550d40
extern const float g_1550d44;  // float 0x01550d44
extern const float g_1550d48;  // float 0x01550d48

void* __cdecl FUN_0099c1a0(void* out, void* quat, void* pos);   // 0x0099c1a0 QuaternionVectorTransform
int  __cdecl FUN_009b4d90();                                     // 0x009b4d90
void __cdecl FUN_009b3090(unsigned int tag, int n);              // 0x009b3090
void __cdecl FUN_009dfc40(int* p);                               // 0x009dfc40 AnimA dtor
void __cdecl FUN_009dfd30(int* p);                               // 0x009dfd30 AnimC dtor
double __cdecl FUN_009f9c60(void* p);                            // 0x009f9c60
bool __cdecl nSPCreatureAnim_ShouldJiggle(void* p);              // ShouldJiggle

namespace nSPCreatureAnim {

struct Bone {                       // stride 0x468; only the used fields are modelled
    unsigned char pad0[0x10c];
    float mOffsetX;                 // +0x10c
    float mOffsetY;                 // +0x110
    float mOffsetZ;                 // +0x114
    unsigned char pad1[0x2c];       // +0x118 .. 0x144
    float mParentOffX;              // +0x144
    float mParentOffY;              // +0x148
    float mParentOffZ;              // +0x14c
    unsigned char mFlags150;        // +0x150
    unsigned char pad2[0x3];        // +0x151 .. 0x154
    unsigned char mFlags154;        // +0x154
    unsigned char pad3[0x1b8 - 0x155];
    unsigned char mBitset[0x1f8 - 0x1b8];
    int mPrevIndex;                 // +0x1f8
    int mNextIndex;                 // +0x1fc
    int mChildFirst;                // +0x204
    int mChildCount;                // +0x208
    unsigned char pad4[0x344 - 0x20c];
    float mHasTransform;            // +0x30c  (unused placeholder)
    unsigned char pad5[0x344 - 0x310];
    float mPosX;                    // +0x344
    float mPosY;                    // +0x348
    float mPosZ;                    // +0x34c
    float mAttX;                    // +0x350
    float mAttY;                    // +0x354
    float mAttZ;                    // +0x358
    unsigned char pad6[0x368 - 0x35c];
    float mLen;                     // +0x368
    float mScale;                   // +0x36c
    unsigned char mJiggle;          // +0x370
    unsigned char pad7[0x3];
    float mAvgSegLen;               // +0x374
};

struct AnimA_ { int d[0]; };
struct AnimC_ { int d[0]; };

struct Solver {
    unsigned char pad0[0x10c];
    float mOffsetX;                 // +0x10c
    float mOffsetY;                 // +0x110
    float mOffsetZ;                 // +0x114
    unsigned char pad1[0x2c];       // +0x118 .. 0x144
    float mParentOffX;              // +0x144
    float mParentOffY;              // +0x148
    float mParentOffZ;              // +0x14c
    unsigned char mFlags150;        // +0x150
    unsigned char pad2[0x3];
    unsigned char mFlags154;        // +0x154
    unsigned char pad3[0x1f8 - 0x155];
    int mPrevIndex;                 // +0x1f8
    int mNextIndex;                 // +0x1fc
    unsigned char pad4[0x344 - 0x200];
    float mPosX;                    // +0x344
    float mPosY;                    // +0x348
    float mPosZ;                    // +0x34c
    float mAttX;                    // +0x350
    float mAttY;                    // +0x354
    float mAttZ;                    // +0x358
    float mVX;                      // +0x358?  (see ForceAdd)
    unsigned char pad5[0x368 - 0x360];
    float mSizeA;                   // +0x368
    float mSizeB;                   // +0x36c
    unsigned char mJiggle;          // +0x370
    unsigned char pad6[0x3];
    float mAvgSegLen;               // +0x374
    unsigned char pad7[0x384 - 0x378];
    Bone* mBones;                   // +0x384
    Bone* mBonesEnd;                // +0x388
    unsigned char pad8[0x3ac - 0x38c];
    int mRootIndex;                 // +0x3ac
    unsigned char pad9[0x3c8 - 0x3b0];
    int mUseDirect;                 // +0x3c8
    int* mOrderPairs;               // +0x3cc (pairs of {Bone*, int})
    int* mOrderPairsEnd;            // +0x3d0
    unsigned char pad10[0x3e0 - 0x3d4];
    int mFlaggedCount;              // +0x3e0

    float DistX(int i0, int i1, float k);
    float DistY(int i0, int i1, float k);
    float SqX(float k, int i0, int i1);
    float SqY(float k, int i0, int i1);
    float SegmentLengthSum(Bone* b);
    float AverageSegment();
    void  MarkDeepBones();
    int   IsDeeperRatio(Bone** a, Bone** b);
    int   FindMinIndex(int* from, int* to);
    void  SortRange(int* a, int* b);
    void  SortFlaggedRuns();
    void  ShutdownAnims();
    void  UpdateAvgSegLen();
    void  BuildOrderPairs();
    float SegmentLengthSum2(Bone* b);
};

}  // namespace nSPCreatureAnim

using nSPCreatureAnim::Solver;
using nSPCreatureAnim::Bone;

static inline float fsq(float v) { return v * v; }

// @ 0x009b4e00
void Bone_ComputeSegment(Solver* self, Solver* other)
{
    float* a = (float*)FUN_0099c1a0((void*)0, (char*)self + 0x118, (char*)self + 0x344);
    float ax = a[0] + self->mOffsetX;
    float ay = a[1] + self->mOffsetY;
    float az = a[2] + self->mOffsetZ;
    float* b = (float*)FUN_0099c1a0((void*)0, (char*)other + 0x118, (char*)other + 0x344);
    float bx = b[0] + other->mOffsetX;
    float by = b[1] + other->mOffsetY;
    float bz = b[2] + other->mOffsetZ;
    self->mPosX = bx - ax;
    self->mPosY = by - ay;
    self->mPosZ = bz - az;
}

// @ 0x009b4ef0
void Solver_UpdateSegment(Solver* self, void* unk, Solver* a)
{
    int n = FUN_009b4d90();
    int i = (int)(char*)a->mBones + 0x444;
    (void)i;
}

// @ 0x009b5080
float Solver::DistX(int i0, int i1, float k)
{
    Solver* self = this;
    Bone* a = (Bone*)((char*)self->mBones + i0 * 0x468);
    Bone* b = (Bone*)((char*)self->mBones + i1 * 0x468);
    float d = a->mOffsetZ - b->mOffsetZ;
    float dx = a->mOffsetX - b->mOffsetX;
    return k * (dx * dx * k);
}

// @ 0x009b5100
float Solver::DistY(int i0, int i1, float k)
{
    Solver* self = this;
    Bone* a = (Bone*)((char*)self->mBones + i0 * 0x468);
    Bone* b = (Bone*)((char*)self->mBones + i1 * 0x468);
    float d = a->mOffsetZ - b->mOffsetZ;
    float dy = a->mOffsetY - b->mOffsetY;
    return k * (dy * dy * k);
}

// @ 0x009b5180
float Solver::SqX(float k, int i0, int i1)
{
    Solver* self = this;
    Bone* a = (Bone*)((char*)self->mBones + i0 * 0x468);
    Bone* b = (Bone*)((char*)self->mBones + i1 * 0x468);
    float d = a->mOffsetX - b->mOffsetX;
    return k * (d * d * k);
}

// @ 0x009b51c0
float Solver::SqY(float k, int i0, int i1)
{
    Solver* self = this;
    Bone* a = (Bone*)((char*)self->mBones + i0 * 0x468);
    Bone* b = (Bone*)((char*)self->mBones + i1 * 0x468);
    float d = a->mOffsetY - b->mOffsetY;
    return k * (d * d * k);
}

// @ 0x009b5200
float Solver::SegmentLengthSum(Bone* bone)
{
    Solver* self = this;
    float accum = 0.0f;
    float best = 0.01f;
    if (bone->mPrevIndex != bone->mChildFirst) {
        float* b0 = (float*)((char*)self->mBones + bone->mPrevIndex * 0x468 + 0x344);
        accum = sqrtf(fsq(b0[0]) + fsq(b0[1]) + fsq(b0[2]));
        int prev = bone->mPrevIndex;
        int cur = bone->mNextIndex;
        while (cur != bone->mChildFirst) {
            float* p0 = (float*)((char*)self->mBones + cur * 0x468 + 0x344);
            float* p1 = (float*)((char*)self->mBones + prev * 0x468 + 0x350);
            float dx = p0[0] - p1[0];
            float dy = p0[1] - p1[1];
            float dz = p0[2] - p1[2];
            accum = sqrtf(fsq(dx) + fsq(dy) + fsq(dz)) + accum;
            prev = cur;
            cur = *(int*)((char*)self->mBones + cur * 0x468 + 0x1fc);
        }
        float* p1 = (float*)((char*)self->mBones + prev * 0x468 + 0x350);
        accum = sqrtf(fsq(p1[0]) + fsq(p1[1]) + fsq(p1[2])) + accum;
        if (0.01f < accum)
            return accum;
    }
    (void)best;
    return best;
}

// @ 0x009b5360
float Solver::AverageSegment()
{
    Solver* self = this;
    int count = (int)((self->mBonesEnd - self->mBones) / 0x468);
    float accum = 0.0f;
    int used = 0;
    if (count != 0) {
        Bone* b = self->mBones;
        do {
            if ((b->mFlags154 & 4) != 0) {
                accum = SegmentLengthSum2(b) + accum;
                ++used;
            }
            b = (Bone*)((char*)b + 0x468);
        } while (--count != 0);
        if (used != 0)
            accum = accum / (float)used;
    }
    return accum;
}

// @ 0x009b53f0
void Bone_AddScaledVectors(float* out, Bone* b, float k)
{
    if ((b->mFlags150 & 8) != 0) {
        out[0] = b->mPosX * k - b->mParentOffX * k;
        out[1] = b->mPosY * k - b->mParentOffY * k;
        out[2] = b->mPosZ * k - b->mParentOffZ * k;
    } else {
        out[0] = b->mPosX * k;
        out[1] = b->mPosY * k;
        out[2] = b->mPosZ * k;
    }
}

// @ 0x009b54a0
void Solver::BuildOrderPairs()
{
    Solver* self = this;
    Bone* b = (Bone*)((char*)self->mBones + self->mRootIndex * 0x468);
    int idx = 0;
    while (b->mPrevIndex != 0) {
        Bone* cur = b;
        *(Bone**)((char*)self->mOrderPairs + idx * 8) = cur;
        *(int*)((char*)self->mOrderPairs + idx * 8 + 4) = 0;
        b = (Bone*)((char*)self->mBones + cur->mNextIndex * 0x468);
        ++idx;
    }
    idx = idx * 4;
    for (;;) {
        *(Bone**)((char*)self->mOrderPairs + idx * 2) = b;
        unsigned int n = (unsigned int)b->mChildCount;
        Bone* c = (Bone*)((char*)self->mBones + b->mChildFirst * 0x468);
        int found = 0;
        if (n != 0) {
            do {
                if ((c->mFlags150 & 8) != 0 && c != b)
                    break;
                ++found;
                c = (Bone*)((char*)c + 0x468);
            } while ((unsigned int)found < n);
        }
        if ((unsigned int)found == n || c == 0)
            return;
        b = c;
        idx += 4;
    }
}

// @ 0x009b5580
void Solver::MarkDeepBones()
{
    Solver* self = this;
    float f = (self->mSizeA / self->mSizeB - 1.0f) * g_1550d48 + g_1550d44;
    if (f <= g_1550d40)
        f = g_1550d40;
    if (g_1550d3c < f)
        f = g_1550d3c;
    float limit = f * self->mSizeB;
    unsigned int count = (unsigned int)((int)((char*)self->mOrderPairsEnd - (char*)self->mOrderPairs) >> 3);
    unsigned int i = 0;
    if (3 < (int)count) {
        int* p = self->mOrderPairs;
        do {
            Bone* b0 = *(Bone**)((char*)p + 0);
            if (b0->mOffsetZ - b0->mParentOffZ < limit) {
                *(unsigned char*)((char*)p + 4) = 1;
                self->mFlaggedCount = self->mFlaggedCount + 1;
            }
            Bone* b1 = *(Bone**)((char*)p + 8);
            if (b1->mOffsetZ - b1->mParentOffZ < limit) {
                *(unsigned char*)((char*)p + 12) = 1;
                self->mFlaggedCount = self->mFlaggedCount + 1;
            }
            Bone* b2 = *(Bone**)((char*)p + 16);
            if (b2->mOffsetZ - b2->mParentOffZ < limit) {
                *(unsigned char*)((char*)p + 20) = 1;
                self->mFlaggedCount = self->mFlaggedCount + 1;
            }
            Bone* b3 = *(Bone**)((char*)p + 24);
            if (b3->mOffsetZ - b3->mParentOffZ < limit) {
                *(unsigned char*)((char*)p + 28) = 1;
                self->mFlaggedCount = self->mFlaggedCount + 1;
            }
            p = (int*)((char*)p + 32);
            i = i + 4;
        } while (i < count - 3);
    }
    for (; i < count; ++i) {
        Bone* b0 = *(Bone**)((char*)self->mOrderPairs + i * 8);
        if (b0->mOffsetZ - b0->mParentOffZ < limit) {
            *(unsigned char*)((char*)self->mOrderPairs + i * 8 + 4) = 1;
            self->mFlaggedCount = self->mFlaggedCount + 1;
        }
    }
}

// @ 0x009b5700
int Solver::IsDeeperRatio(Bone** a, Bone** b)
{
    Solver* self = this;
    float denom = self->mSizeA;
    float* pDenom = (float*)&g_14471fc;
    if (1e-06f <= denom)
        pDenom = &denom;
    int result = 1;
    if (a != b) {
        Bone* ba = *a;
        Bone* bb = *b;
        float dx = ba->mOffsetX - bb->mOffsetX;
        float dy = ba->mOffsetY - bb->mOffsetY;
        float absdz = fabsf(ba->mOffsetZ - bb->mOffsetZ);
        float len = sqrtf(fsq(dx) + fsq(dy));
        float* pLen = (float*)&g_14471fc;
        if (1e-06f <= len)
            pLen = &len;
        if (self->mSizeB / *pDenom < absdz / *pLen)
            return 1;
        result = 0;
    }
    return result;
}

// @ 0x009b57b0
int Solver::FindMinIndex(int* from, int* to)
{
    Solver* self = this;
    int* base = self->mOrderPairs;
    unsigned int n = (unsigned int)(to - base) >> 3;
    unsigned int i = (unsigned int)((from - base) >> 3) + 1;
    if (i <= n) {
        unsigned int rem = (n - i) + 1;
        if (3 < rem) {
            while (rem > 3) {
                int* p = (int*)(base + i * 8);
                if (*(float*)(*(int*)(p - 4) + 0x114) <= *(float*)(*from + 0x114) &&
                    *(float*)(*from + 0x114) != *(float*)(*(int*)(p - 4) + 0x114))
                    from = p - 4;
                if (*(float*)(*(int*)(p - 2) + 0x114) <= *(float*)(*from + 0x114) &&
                    *(float*)(*from + 0x114) != *(float*)(*(int*)(p - 2) + 0x114))
                    from = p - 2;
                if (*(float*)(*(int*)(p + 0) + 0x114) <= *(float*)(*from + 0x114) &&
                    *(float*)(*from + 0x114) != *(float*)(*(int*)(p + 0) + 0x114))
                    from = p;
                if (*(float*)(*(int*)(p + 2) + 0x114) <= *(float*)(*from + 0x114) &&
                    *(float*)(*from + 0x114) != *(float*)(*(int*)(p + 2) + 0x114))
                    from = p + 2;
                p = p + 8;
                i += 4;
                rem -= 4;
            }
        }
        while (i <= n) {
            int* p = (int*)((char*)base + i * 8);
            if (*(float*)(*(int*)(p + 0) + 0x114) <= *(float*)(*from + 0x114) &&
                *(float*)(*from + 0x114) != *(float*)(*(int*)(p + 0) + 0x114))
                from = p;
            i += 1;
        }
    }
    return (int)((from - base) >> 3);
}

// @ 0x009b58b0
void Solver::SortRange(int* a, int* b)
{
    Solver* self = this;
    (void)self;
    if (3 < ((int)b - (int)a >> 3) + 1) {
        int ok = self->IsDeeperRatio((Bone**)a, (Bone**)b);
        if (ok == 0) {
            FUN_009b3090(0x74667370, 1);
            FUN_009b3090(0x74667370, 1);
            return;
        }
    }
    self->FindMinIndex(a, b);
    FUN_009b3090(0x74667370, 1);
}

// @ 0x009b5930
void Solver::SortFlaggedRuns()
{
    Solver* self = this;
    unsigned int n = (unsigned int)((int)((char*)self->mOrderPairsEnd - (char*)self->mOrderPairs) >> 3);
    int first = 0;
    int last = 0;
    if (self->mFlaggedCount == 0) {
        self->SortRange(self->mOrderPairs, (int*)((char*)self->mOrderPairs - 8 + n * 8));
        return;
    }
    unsigned int i = 0;
    if (n != 0) {
        do {
            char flag = *(char*)((char*)self->mOrderPairs + 4 + i * 8);
            int cur = (int)((char*)self->mOrderPairs + i * 8);
            if (flag != 0 && last == 0)
                last = cur;
            if (first == 0) {
                first = cur;
            }
            if ((first != 0 && last != 0) && (flag == 0 || i == n - 1)) {
                self->SortRange((int*)first, (int*)last);
                last = 0;
                first = 0;
            }
            ++i;
        } while (i < n);
    }
}

// @ 0x009b59c0
void Solver::ShutdownAnims()
{
    Solver* self = this;
    int* p = (int*)((char*)self + 0x1220);
    FUN_009dfc40(p);
    p = (int*)((char*)self + 0x1220);
    int i = 0x17;
    do {
        p = (int*)((char*)p - 0xb4);
        FUN_009dfd30(p);
        --i;
    } while (-1 < i);
}

// @ 0x009b5a00
void Bone_ResetState(unsigned int* p)
{
    p[0] = 0; p[1] = 0; p[2] = 0; p[3] = 0;
    p[0x16] = 0; p[0x17] = 0; p[0x18] = 0; p[0x19] = 0; p[0x1a] = 0; p[0x1b] = 0;
    p[0x1c] = 0; p[0x1d] = 0; p[0x1e] = 0; p[0x1f] = 0; p[0x20] = 0; p[0x21] = 0;
    p[0x22] = 0; p[0x23] = 0; p[0x24] = 0; p[0x25] = 0; p[0x26] = 0; p[0x27] = 0;
    p[0x28] = 0; p[0x12] = 0; p[0x13] = 0; p[0x14] = 0;
    *(unsigned char*)((char*)p + 0x54) = 0;
    *(unsigned char*)((char*)p + 0x55) = 0;
    *(unsigned char*)((char*)p + 0x2a0) = 0;
    *(unsigned char*)((char*)p + 0x38) = 0;
    p[0x51] = 0;
}

// @ 0x009b5ab0
void Bone_IntegrateVelocity(unsigned int* p, float dt, float* accel, float* quat)
{
    if (!(0.0f < dt))
        return;
    float qx = accel[0];
    float qz = accel[2];
    float vy = accel[1];
    p[0x20] = (unsigned int)(vy * dt + (float)p[0x20]);
    p[0x21] = (unsigned int)((float)p[0x21] + qz * dt);
    p[0x1f] = (unsigned int)((float)p[0x1f] + qx * dt);
    p[0x22] = (unsigned int)(dt + (float)p[0x22]);
    float ax = (float)p[0x23];
    float ay = (float)p[0x24];
    float az = (float)p[0x25];
    float aw = (float)p[0x26];
    float bx = quat[0] * dt;
    float by = quat[1] * dt;
    float bz = quat[2] * dt;
    float bw = quat[3] * dt;
    if (0.0f <= (aw * bw + ax * bx) + ay * by + az * bz) {
        ax += bx; ay += by; az += bz; aw += bw;
    } else {
        ax -= bx; ay -= by; az -= bz; aw -= bw;
    }
    p[0x23] = *(unsigned int*)&ax;
    p[0x24] = *(unsigned int*)&ay;
    p[0x25] = *(unsigned int*)&az;
    p[0x26] = *(unsigned int*)&aw;
    p[0x27] = (unsigned int)(dt + (float)p[0x27]);
    unsigned int idx = *(unsigned int*)(((Bone*)p)->pad0 + 0x1f8) & 0x7fffffff;
    unsigned char* flag = (unsigned char*)(p[1] + 0x1b8 + (idx >> 2));
    *flag |= (unsigned char)(2 << ((idx * 2) & 7));
}

// @ 0x009b5c50
void Solver::UpdateAvgSegLen()
{
    Solver* self = this;
    int n = (int)((char*)self->mBonesEnd - (char*)self->mBones) / 0x468;
    if (0 < n) {
        int off = 0;
        do {
            Solver* b = (Solver*)((char*)self->mBones + off);
            b->mAvgSegLen = (float)FUN_009f9c60(b);
            if (*(int*)&g_1550b04 == 0)
                b->mJiggle = nSPCreatureAnim_ShouldJiggle(b) ? 1 : 0;
            if (b->mSizeA <= 0.001f && b->mSizeA != 0.001f)
                b->mJiggle = 0;
            off += 0x468;
            --n;
        } while (n != 0);
    }
}
