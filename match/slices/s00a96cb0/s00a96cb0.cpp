// Slice s00a96cb0 (gold7): EA Swarm particle-emitter spawn family.
//
// Four __thiscall methods (ret 4) of one emitter class, all taking a single float dt.
//
// Emitter layout (retail offsets):
//   +0x00 vtable, +0x14 list sentinel (head), +0x18 list tail, +0x1c live count
//   +0x20 cEmitterDesc* mDesc
//   +0x40 double mAccum          (age accumulator)
//   +0x48 int    mStep           (spawn step counter)
//   +0x50 double mSpawnRate      (per-unit spawn rate)
//   +0x58 float  mCarry          (fractional spawn carry)
//   +0x5c/60/64 float base velocity x/y/z
//   +0x68 float  mInitialDelay
//   +0x6c/70/74 float bounds min x/y/z
//   +0x78/7c/80 float bounds max x/y/z
//   +0x98/9c/a0 float mOrigin x/y/z, +0xa4 float mScale, +0x14c float mRateScale
//
// Particle node (18 dwords): +0x00 next, +0x04 prev, +0x08 age, +0x0c life,
//   +0x10/14/18 pos x/y/z, +0x1c/20/24 vel x/y/z.
//
// Nodes come from a fixed-size pool: free-list head gParticleFreeList (0x0167888c),
// allocator object gParticleAlloc (0x0167887c, FixedAllocatorBase::AddCore 0x00926650);
// FUN_00a94b90 re-randomises a recycled node.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef uint32_t u32;
typedef uint8_t  u8;

// ------------------------------------------------------------------ global pool
extern int* gParticleFreeList;                         // 0x0167888c  free-list head

struct cEmitter;

struct cParticleNode {
    cParticleNode* mpNext;                             // +0x00
    cParticleNode* mpPrev;                             // +0x04
    float mAge;                                        // +0x08
    float mLife;                                       // +0x0c
    float mPosX, mPosY, mPosZ;                         // +0x10..0x18
    float mVelX, mVelY, mVelZ;                         // +0x1c..0x24
};

struct cEmitterDesc {
    char  pad00[0x08];
    u32   mFlags;                                      // +0x08
    float mField0c;                                    // +0x0c
    float mSpawnRate;                                  // +0x10
    float mSpawnRateLimit;                             // +0x14
    char  pad18[0x08];
    float mField20;                                    // +0x20
    float mField24;                                    // +0x24
    char  pad28[0x38];
    float* mpCurve;                                    // +0x60  float curve samples
    float* mCurveEnd;                                  // +0x64  curve end pointer
    char  pad68[0x0c];
    float mField74;                                    // +0x74
    unsigned short mLoopCount;                         // +0x78
    char  pad7a[0x02];
    float mField7c;                                    // +0x7c
    char  pad80[0x88];
    float mField108;                                   // +0x108
};

struct cEmitter {
    void* mpField00;                                   // +0x00
    void* mpVtbl;                                      // +0x04  sub-object vtable
    char  pad08[0x0c];
    void* mpListHead;                                  // +0x14
    void* mpListTail;                                  // +0x18
    int   mListCount;                                  // +0x1c
    cEmitterDesc* mDesc;                               // +0x20
    char  pad24[0x1c];
    double mAccum;                                     // +0x40
    int   mStep;                                       // +0x48
    char  pad4c[0x04];
    double mSpawnRate;                                 // +0x50
    float mCarry;                                      // +0x58
    float mVelX;                                       // +0x5c
    float mVelY;                                       // +0x60
    float mVelZ;                                       // +0x64
    float mInitialDelay;                               // +0x68
    float mMinX;                                       // +0x6c
    float mMinY;                                       // +0x70
    float mMinZ;                                       // +0x74
    float mMaxX;                                       // +0x78
    float mMaxY;                                       // +0x7c
    float mMaxZ;                                       // +0x80
    char  pad84[0x14];
    float mOriginX;                                    // +0x98
    float mOriginY;                                    // +0x9c
    float mOriginZ;                                    // +0xa0
    float mScale;                                      // +0xa4
    char  pada8[0x5c];
    float mField104;                                   // +0x104
    float mField108;                                   // +0x108
    float mField10c;                                   // +0x10c
    char  pad110[0x3c];
    float mRateScale;                                  // +0x14c

    void SpawnA(float dt);                             // 0x00a96cb0
    void SpawnB(float dt);                             // 0x00a97290
    void SpawnC(float dt);                             // 0x00a975e0
    void Update(float dt);                             // 0x00a97830
};

// externs implemented elsewhere (retail addresses)
struct FixedAllocatorBase {
    bool AddCore(void* a, u32 b);                     // 0x00926650
};
extern FixedAllocatorBase gParticleAlloc;             // 0x0167887c
struct NodeOps {
    void Reset(cParticleNode* node);                  // 0x00a94b90 (this = emitter)
};
struct ListOps {
    void Clear();                                     // 0x00a96c00 (this = emitter)
};
struct cRandomGlobal {
    double RandomDouble();                            // 0x009360d0 (this = &gRandomGlobal)
};
extern cRandomGlobal gRandomGlobal;                   // 0x016778dc
extern "C" float sqrtf(float);                         // inlines to fsqrt under /fp:fast

// grows the pool until a node is available, then pops it off the free list
static __forceinline cParticleNode* PopNode()
{
    cParticleNode* node;
    while ((node = (cParticleNode*)gParticleFreeList) == 0) {
        if (!gParticleAlloc.AddCore(0, 0))
            break;   // AddCore is __thiscall: ecx = &gParticleAlloc
    }
    if (node) {
        gParticleFreeList = (int*)node->mpNext;
        node->mpPrev = 0;
        node->mpNext = 0;
    }
    return node;
}

// ================================================================================
// @ 0x00a97830
void cEmitter::Update(float dt)
{
    if (mInitialDelay > 0.0f) {
        dt = mInitialDelay - dt;
        mInitialDelay = dt;
        if (dt > 0.0f)
            return;
        dt = -dt;
    }
    float limit = mDesc->mSpawnRateLimit;
    if (limit > 0.01 && (limit = limit - 0.01f) < dt)
        dt = limit;
    u32 flags = mDesc->mFlags;
    if (((flags >> 1) & 1) != 0) {
        SpawnC(dt);
    } else if ((flags & 1) != 0) {
        SpawnB(dt);
    } else {
        SpawnA(dt);
    }
}

// ================================================================================
// @ 0x00a975e0
void cEmitter::SpawnC(float dt)
{
    double acc = dt * mSpawnRate + mAccum;
    mAccum = acc;
    if ((float)mStep <= (float)acc) {
        float want = (float)(mDesc->mpCurve[0] * mRateScale);
        int count = (int)want;
        if ((float)count < want)
            count += 1;
        for (count = count - mListCount; count > 0; --count) {
            cParticleNode* node = PopNode();
            if (!node)
                break;
            ((NodeOps*)this)->Reset(node);
            float age = node->mAge + dt;
            node->mAge = age;
            if (node->mLife <= age) {
                node->mpNext = (cParticleNode*)gParticleFreeList;
                gParticleFreeList = (int*)node;
            } else {
                float oldVx = node->mVelX;
                float oldVy = node->mVelY;
                float oldVz = node->mVelZ;
                float nvx = oldVx + mVelX * dt;
                float nvy = oldVy + mVelY * dt;
                float nvz = oldVz + mVelZ * dt;
                node->mVelX = nvx;
                node->mVelY = nvy;
                node->mVelZ = nvz;
                float damp = 1.0f - mDesc->mField108 * dt;
                nvx *= damp;
                nvy *= damp;
                nvz *= damp;
                node->mVelX = nvx;
                node->mVelY = nvy;
                node->mVelZ = nvz;
                float half = dt * 0.5f;
                node->mPosX += (nvx + oldVx) * half;
                node->mPosY += (nvy + oldVy) * half;
                node->mPosZ += (nvz + oldVz) * half;
                cParticleNode* oldTail = (cParticleNode*)mpListTail;
                node->mpPrev = oldTail;
                node->mpNext = (cParticleNode*)&mpListHead;
                mpListTail = node;
                oldTail->mpNext = node;
                ++mListCount;
                if (node->mPosX < mMinX) mMinX = node->mPosX;
                if (mMaxX <= node->mPosX && node->mPosX != mMaxX) mMaxX = node->mPosX;
                if (node->mPosY < mMinY) mMinY = node->mPosY;
                if (mMaxY <= node->mPosY && node->mPosY != mMaxY) mMaxY = node->mPosY;
                if (node->mPosZ < mMinZ) mMinZ = node->mPosZ;
                if (mMaxZ <= node->mPosZ && node->mPosZ != mMaxZ) mMaxZ = node->mPosZ;
            }
        }
    }
}

// ================================================================================
// @ 0x00a97290
void cEmitter::SpawnB(float dt)
{
    float acc = dt * (float)mSpawnRate + (float)mAccum;
    mAccum = (double)acc;
    if ((float)mStep <= acc) {
        float want = (float)(mDesc->mpCurve[0] * mRateScale);
        int per = (int)want;
        if ((float)per < want)
            per += 1;
        if ((double)mStep <= mAccum) {
            do {
                if ((mDesc->mFlags >> 9) & 1)
                    ((ListOps*)this)->Clear();
                float frac = ((float)mAccum - (float)mStep) * mDesc->mField74;
                if (frac < mDesc->mSpawnRate) {
                    for (int i = 0; i < per; ++i) {
                        cParticleNode* node = PopNode();
                        ((NodeOps*)this)->Reset(node);
                        float age = node->mAge + frac;
                        node->mAge = age;
                        if (node->mLife <= age) {
                            node->mpNext = (cParticleNode*)gParticleFreeList;
                            gParticleFreeList = (int*)node;
                        } else {
                            float oldVx = node->mVelX;
                            float oldVy = node->mVelY;
                            float oldVz = node->mVelZ;
                            float nx = oldVx + mVelX * frac;
                            float ny = oldVy + mVelY * frac;
                            float nz = oldVz + mVelZ * frac;
                            float damp = 1.0f - mDesc->mField108 * frac;
                            nx *= damp;
                            ny *= damp;
                            nz *= damp;
                            node->mVelX = nx;
                            node->mVelY = ny;
                            node->mVelZ = nz;
                            float half = frac * 0.5f;
                            node->mPosX += (nx + oldVx) * half;
                            node->mPosY += (ny + oldVy) * half;
                            node->mPosZ += (nz + oldVz) * half;
                            cParticleNode* oldTail = (cParticleNode*)mpListTail;
                            node->mpPrev = oldTail;
                            node->mpNext = (cParticleNode*)&mpListHead;
                            mpListTail = node;
                            oldTail->mpNext = node;
                            ++mListCount;
                            if (node->mPosX < mMinX) mMinX = node->mPosX;
                            if (mMaxX <= node->mPosX && node->mPosX != mMaxX) mMaxX = node->mPosX;
                            if (node->mPosY < mMinY) mMinY = node->mPosY;
                            if (mMaxY <= node->mPosY && node->mPosY != mMaxY) mMaxY = node->mPosY;
                            if (node->mPosZ < mMinZ) mMinZ = node->mPosZ;
                            if (mMaxZ <= node->mPosZ && node->mPosZ != mMaxZ) mMaxZ = node->mPosZ;
                        }
                    }
                }
                ++mStep;
                cEmitterDesc* d = mDesc;
                if (d->mLoopCount != 0 && (int)d->mLoopCount <= mStep) {
                    if ((d->mFlags >> 0xa) & 1)
                        return;
                    ((void(__thiscall*)(void*, int))((void**)mpVtbl)[3])((char*)this + 4, 0);
                    return;
                }
                if (0.0f <= d->mField20) {
                    float lo = d->mField20;
                    float hi = d->mField24;
                    double r = gRandomGlobal.RandomDouble();
                    double v = r * (hi - lo) + lo;
                    if (v < hi && (v < lo))
                        v = lo;
                    mAccum = mAccum - v * mSpawnRate;
                    if (mAccum < (double)mStep) {
                        mInitialDelay = (float)(((double)mStep - mAccum) * d->mField74);
                        mAccum = (double)mStep;
                        return;
                    }
                }
                if (mAccum < (double)mStep)
                    return;
            } while (true);
        }
    }
}

// ================================================================================
// @ 0x00a96cb0
void cEmitter::SpawnA(float dt)
{
    float t = dt;
    if (dt <= 0.0f)
        return;
    u32 flags = mDesc->mFlags;
    float rateScale = mRateScale;
    if ((flags >> 4) & 1) {
        rateScale = mScale * rateScale;
    } else if ((flags >> 5) & 1) {
        rateScale = mScale * mScale * rateScale;
    } else if ((flags >> 6) & 1) {
        rateScale = mScale * mScale * mScale * rateScale;
    }
    float dx = mOriginX - mField104;
    float dy = mOriginY - mField108;
    float dz = mOriginZ - mField10c;
    float spread = mDesc->mField7c;
    if (0.0f < spread) {
        float dist = sqrtf(dz * dz + (dy * dy + dx * dx));
        rateScale = ((dist / dt) * spread + 1.0f) * rateScale;
    }
    bool repeat = false;
    do {
        float step = (dt <= (1.0f / 15.0f)) ? dt : (1.0f / 15.0f);
        int stepIdx = mStep + 1;
        double next = (double)step * mSpawnRate + mAccum;
        mAccum = next;
        float remain = dt;
        if ((float)stepIdx < (float)next) {
            mStep = stepIdx;
            if ((mDesc->mFlags >> 9) & 1)
                ((ListOps*)this)->Clear();
            cEmitterDesc* d = mDesc;
            if (d->mLoopCount == 0 || mStep != (int)d->mLoopCount) {
                if (0.0f <= d->mField20) {
                    repeat = true;
                    step = (float)((float)step - ((float)mAccum - (float)mStep) * d->mField74);
                    mAccum = (double)mStep;
                }
            } else {
                if (((d->mFlags >> 2) & 1) == 0) {
                    if ((d->mFlags >> 0xa) & 1)
                        return;
                    ((void(__thiscall*)(void*, int))((void**)mpVtbl)[3])((char*)this + 4, 0);
                    return;
                }
                mStep = (int)d->mLoopCount - 1;
                mAccum = (double)((float)d->mLoopCount - 1e-06f);
            }
        }
        cEmitterDesc* d = mDesc;
        int span = (d->mCurveEnd - d->mpCurve) - 1;
        float sample;
        if (span == 0) {
            sample = d->mpCurve[0];
        } else {
            float u = (float)span * ((float)mAccum - (float)mStep);
            int i = (int)u;
            float f = u - (float)i;
            if (f <= 0.0f) {
                sample = d->mpCurve[i];
            } else {
                float a = d->mpCurve[i];
                sample = (d->mpCurve[i + 1] - a) * f + a;
            }
        }
        float carry = (sample * step) * rateScale + mCarry;
        mCarry = carry;
        int count = (int)carry;
        if (carry < (float)count)
            count -= 1;
        mCarry = mCarry - (float)count;
        int i = 0;
        if (0 < count) {
            do {
                cParticleNode* node = PopNode();
                ((NodeOps*)this)->Reset(node);
                float frac = remain / t;
                node->mPosX -= dx * frac;
                node->mPosY -= dy * frac;
                node->mPosZ -= dz * frac;
                float age = node->mAge + remain;
                node->mAge = age;
                if (node->mLife <= age) {
                    node->mpNext = (cParticleNode*)gParticleFreeList;
                    gParticleFreeList = (int*)node;
                } else {
                    float oldVx = node->mVelX;
                    float oldVy = node->mVelY;
                    float oldVz = node->mVelZ;
                    float nx = oldVx + mVelX * remain;
                    float ny = oldVy + mVelY * remain;
                    float nz = oldVz + mVelZ * remain;
                    float damp = 1.0f - mDesc->mField108 * remain;
                    nx *= damp;
                    ny *= damp;
                    nz *= damp;
                    node->mVelX = nx;
                    node->mVelY = ny;
                    node->mVelZ = nz;
                    float half = remain * 0.5f;
                    node->mPosX += (nx + oldVx) * half;
                    node->mPosY += (ny + oldVy) * half;
                    node->mPosZ += (nz + oldVz) * half;
                    cParticleNode* oldTail = (cParticleNode*)mpListTail;
                    node->mpPrev = oldTail;
                    node->mpNext = (cParticleNode*)&mpListHead;
                    mpListTail = node;
                    oldTail->mpNext = node;
                    ++mListCount;
                    if (node->mPosX < mMinX) mMinX = node->mPosX;
                    if (mMaxX <= node->mPosX && node->mPosX != mMaxX) mMaxX = node->mPosX;
                    if (node->mPosY < mMinY) mMinY = node->mPosY;
                    if (mMaxY <= node->mPosY && node->mPosY != mMaxY) mMaxY = node->mPosY;
                    if (node->mPosZ < mMinZ) mMinZ = node->mPosZ;
                    if (mMaxZ <= node->mPosZ && node->mPosZ != mMaxZ) mMaxZ = node->mPosZ;
                }
                remain = remain - step / (float)count;
                ++i;
            } while (i < count);
            remain = dt;
        }
        dt = remain - step;
        if (repeat) {
            float lo = mDesc->mField20;
            float hi = mDesc->mField24;
            double r = gRandomGlobal.RandomDouble();
            double v = r * (hi - lo) + lo;
            if (v < hi) {
                float vv = (float)v;
                if (vv < lo)
                    vv = lo;
                dt = (float)((double)dt - (double)vv);
            } else {
                dt = (float)((double)dt - (double)hi);
            }
            if (dt < 0.0f) {
                mInitialDelay = -dt;
                return;
            }
        }
        if (dt <= 0.0f)
            return;
    } while (true);
}
