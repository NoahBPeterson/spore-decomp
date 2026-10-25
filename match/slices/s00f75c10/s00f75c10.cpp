// Slice s00f75c10: attachment point update + pool allocation (0x00f75c10, 0x00f75fc0).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

struct Vec3 {
    float x;
    float y;
    float z;
};

// 0x38-byte transform: flags, translation, uniform scale, row-major 3x3.
struct Xform {
    uint32_t mFlags;                                        // +0x00
    Vec3     mPosition;                                     // +0x04
    float    mScale;                                        // +0x10
    float    mMatrix[9];                                    // +0x14
    void InverseTransformPoint(Vec3* point);                // 0x007cda70 (thiscall, ret 4)
};

struct AttachConfig {                                       // pointed to by owner+0x24
    char     pad00[8];
    uint32_t mFlags;                                        // +0x08
};

struct AttachTarget {                                       // pointed to by owner+0x198
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
    virtual void t10(); virtual void t14();
    virtual bool  Accept(Vec3* point);                      // +0x18
    virtual void  t1cdummy();
    virtual float GetRange(Vec3* point);                    // +0x20
};

struct RandomGlobal {
    double RandomDouble();                                  // 0x009360d0
};
extern RandomGlobal _sRandomGlobal;                         // 0x016778dc

namespace SP {
struct Vector2_s004d_f2d0 {
    float mData[2];
};
float RandomInRange(const Vector2_s004d_f2d0& range);       // 0x004df2d0
}

// Caller structure: the point lives at +0x10, an extra vector at +0x48 is cleared.
struct AttachPoint {
    char pad00[0x10];
    Vec3 mPosition;                                         // +0x10
    char pad1c[0x48 - 0x1c];
    Vec3 mField48;                                          // +0x48
};

struct AttachPointUpdater {
    char          pad00[0x24];
    AttachConfig* mpConfig;                                 // +0x24
    char          pad28[0xb0 - 0x28];
    Xform         mXformA;                                  // +0xb0
    Xform         mXformB;                                  // +0xe8
    char          pad120[0x16c - 0x120];
    float         mMinRange;                                // +0x16c
    float         mMaxRange;                                // +0x170
    char          pad174[0x198 - 0x174];
    AttachTarget* mpTarget;                                 // +0x198
    char          pad19c[0x1a1 - 0x19c];
    bool          mEnabled;                                 // +0x1a1
    char          pad1a2[0x1b4 - 0x1a2];
    float         mField1b4;                                // +0x1b4
    char          pad1b8[0x1c0 - 0x1b8];
    float         mField1c0;                                // +0x1c0
    bool UpdateAttachPoint(AttachPoint* io);                // 0x00f75c10
};

// @ 0x00f75c10
bool AttachPointUpdater::UpdateAttachPoint(AttachPoint* io)
{
    Vec3 pos;
    pos.x = io->mPosition.x;
    pos.y = io->mPosition.y;
    pos.z = io->mPosition.z;
    if (mEnabled) {
        if (mXformA.mFlags & 2) {
            Vec3 transformed;
            transformed.x = (mXformA.mMatrix[3] * pos.y + mXformA.mMatrix[6] * pos.z)
                            + mXformA.mMatrix[0] * pos.x;
            transformed.y = (mXformA.mMatrix[4] * pos.y + mXformA.mMatrix[7] * pos.z)
                            + mXformA.mMatrix[1] * pos.x;
            transformed.z = (mXformA.mMatrix[5] * pos.y + mXformA.mMatrix[8] * pos.z)
                            + mXformA.mMatrix[2] * pos.x;
            pos = transformed;
        }
        pos.x = mXformA.mScale * pos.x + mXformA.mPosition.x;
        pos.y = mXformA.mPosition.y + mXformA.mScale * pos.y;
        pos.z = mXformA.mPosition.z + mXformA.mScale * pos.z;
        if (mXformB.mFlags & 2) {
            Vec3 transformed;
            transformed.x = (mXformB.mMatrix[3] * pos.y + mXformB.mMatrix[6] * pos.z)
                            + mXformB.mMatrix[0] * pos.x;
            transformed.y = (mXformB.mMatrix[4] * pos.y + mXformB.mMatrix[7] * pos.z)
                            + mXformB.mMatrix[1] * pos.x;
            transformed.z = (mXformB.mMatrix[5] * pos.y + mXformB.mMatrix[8] * pos.z)
                            + mXformB.mMatrix[2] * pos.x;
            pos = transformed;
        }
        pos.x = mXformB.mPosition.x + mXformB.mScale * pos.x;
        pos.y = mXformB.mPosition.y + mXformB.mScale * pos.y;
        pos.z = mXformB.mPosition.z + mXformB.mScale * pos.z;
    }
    AttachTarget* target = mpTarget;
    if (!target)
        return false;
    if (!target->Accept(&pos))
        return false;
    float range = mpTarget->GetRange(&pos);
    unsigned flags = mpConfig->mFlags;
    bool bRangeCheck = ((flags >> 6) & 1) != 0;
    bool bRandomCheck = ((flags >> 7) & 1) != 0;
    if (bRangeCheck) {
        if (range < mMinRange)
            return false;
        if (range > mMaxRange)
            return false;
    } else if (bRandomCheck) {
        if (!(_sRandomGlobal.RandomDouble() < range))
            return false;
    }
    unsigned flags2 = mpConfig->mFlags;
    bool bOffset = ((flags2 >> 5) & 1) != 0;
    if (bOffset) {
        pos.z = range;
        SP::Vector2_s004d_f2d0 offset;
        offset.mData[0] = mField1b4;
        offset.mData[1] = mField1c0;
        pos.z = pos.z + SP::RandomInRange(offset);
    }
    Vec3 zero;
    zero.x = 0.0f;
    zero.y = 0.0f;
    zero.z = 0.0f;
    io->mField48 = zero;
    if (mEnabled) {
        mXformB.InverseTransformPoint(&pos);
        mXformA.InverseTransformPoint(&pos);
    }
    io->mPosition = pos;
    return true;
}

// ---------------------------------------------------------- pool allocation (0x00f75fc0)
//
// Fixed-size pool global (0x016c9b58) with its intrusive free-list head at +0x10
// (0x016c9b68).  Pops a node, growing the pool by one core block when empty.

struct PoolNode {
    PoolNode* mpNext;                                       // +0x00
    int       mField4;                                      // +0x04
};

struct PoolAllocator {
    uint32_t  mPad[4];
    PoolNode* mpFreeHead;                                   // +0x10 (0x016c9b68)
    bool AddCore(int a, int b);                             // 0x00926650
};
extern PoolAllocator sPool;                                 // 0x016c9b58

// @ 0x00f75fc0
PoolNode* AllocPoolNode()
{
    PoolNode* p;
    do {
        p = sPool.mpFreeHead;
        if (p)
            break;
    } while (sPool.AddCore(0, 0));
    if (!p)
        return 0;
    sPool.mpFreeHead = p->mpNext;
    p->mField4 = 0;
    p->mpNext = 0;
    return p;
}
