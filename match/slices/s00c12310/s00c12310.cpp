// Slice s00c12310: SP::cSPCreatureBase::InterruptAnimation (0x00c12310, 218 bytes)
// and FUN_00c12410 (0x00c12410, target-selection scan).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <float.h>

// Named constant pool entries. The original references these as data-section
// relocations rather than immediate literals.
float gNegOne = -1.0f;
float gFLTMax = 3.4028234663852886e+38f;
float gOne = 1.0f;
float gZeroPointTwo = 0.2f;
float gEpsilon = 1.52587890625e-05f;

struct cTarget;
class cSPCreatureBase;

// Animation object held by a creature at +0xb54. Only the vtable slots used by
// InterruptAnimation are named; the rest are placeholders.
class cAnimCreature
{
public:
    virtual void a00(); virtual void a04();
    virtual uint32_t GetLength(uint32_t id, int a);          // +0x08 (raw float bits)
    virtual void  SetLength(uint32_t bits, int a);            // +0x0c
    virtual void  a10();
    virtual void  SetPause(uint32_t bits, float a);           // +0x14
    virtual void  a18(uint32_t bits);                         // +0x18
    virtual void  a1c(); virtual void  a20(); virtual void  a24(); virtual void  a28();
    virtual void  a2c(); virtual void  a30(); virtual void  a34(); virtual void  a38();
    virtual void  a3c(uint32_t bits, int a);                  // +0x3c
    virtual void  a40(uint32_t bits, uint32_t id);            // +0x40
};

// Global animation manager (0x15fcc6c), slot +0x40 resolves an animation id.
class cAnimationManager
{
public:
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1c();
    virtual void m20(); virtual void m24(); virtual void m28(); virtual void m2c();
    virtual void m30(); virtual void m34(); virtual void m38(); virtual void m3c();
    virtual void* GetAnimation(uint32_t id);                 // +0x40
};

cAnimationManager* AnimationManager();                       // 0x0067cb20
void ResolveAnimation(void* self, uint32_t id, uint32_t* out); // 0x00c0c5b0 (cdecl)
void FUN_00c10250(void* self, uint32_t bits, int arg2, void* handle); // 0x00c10250 (cdecl)
float FUN_00d38a30(int mode, cSPCreatureBase* self);          // 0x00d38a30 (cdecl)

// A 0x10-byte entry in the creature's target-slot array at +0xc28.
struct TargetSlot
{
    char  pad0[4];
    float mValue;                                            // +0x04
    char  pad8[8];
};

// A target record returned by the creature's vtable slot +0xb4.
struct cTarget
{
    char  pad0[8];
    int   mType;                                             // +0x08
    int   mState;                                            // +0x0c
    char  pad10[0x3c - 0x10];
    float mScore;                                            // +0x3c
    char  pad40[0xa8 - 0x40];
    float mRadiusA;                                          // +0xa8
    char  padAC[0xf4 - 0xac];
    float mRadiusB;                                          // +0xf4
    char  padF8[0x104 - 0xf8];
    float mMaxRange;                                         // +0x104
    char  pad108[0x114 - 0x108];
    bool  mFlag114;                                          // +0x114

    float GetTimeToReach(int flags);                         // 0x004d3d70
};

class cSPCreatureBase
{
public:
    uint32_t vptr;                                           // +0x00
    char     pad04[0xb54 - 0x04];
    cAnimCreature* mpAnimCreature;                           // +0xb54
    uint32_t mFlags;                                         // +0xb58
    char     padB5C[0xc28 - 0xb5c];
    TargetSlot* mTargetSlots;                                // +0xc28
    char     padC2C[0xe58 - 0xc2c];
    float    mMaxDistance;                                   // +0xe58
    char     padE5C[0xe88 - 0xe5c];
    uint32_t mAnimLength;                                    // +0xe88 (raw float bits)
    int      mCurrentAnim;                                   // +0xe8c

    uint32_t InterruptAnimation(uint32_t animID, int arg2, char arg3);
    uint32_t FUN_00c12410(const uint32_t* pMask, float range, char a3,
                          char a4, char a5, char a6, char a7);
};

// @ 0x00c12310
uint32_t cSPCreatureBase::InterruptAnimation(uint32_t animID, int arg2, char arg3)
{
    uint32_t length = 0;
    if (!mpAnimCreature)
        goto done;

    uint32_t layerID = animID;
    ResolveAnimation(this, animID, &layerID);
    uint32_t resolvedID = layerID;
    void* handle = AnimationManager()->GetAnimation(resolvedID);
    if (!handle)
        return 0;

    length = mpAnimCreature->GetLength(resolvedID, 0);
    mpAnimCreature->SetLength(length, 1);
    if (arg3)
        mpAnimCreature->SetPause(length, 0.0f);
    mpAnimCreature->a18(length);
    mpAnimCreature->a40(length, animID);
    mpAnimCreature->a3c(length, 0);

    FUN_00c10250(this, length, arg2, handle);
    if (*(char*)((char*)handle + 0x1c) != 1)
        mAnimLength = length;
done:
    return length;
}

// @ 0x00c12410
uint32_t cSPCreatureBase::FUN_00c12410(const uint32_t* pMask, float range,
                                        char a3, char a4, char a5, char a6, char a7)
{
    uint32_t offset;
    float    scale;
    float    bestDist;
    uint32_t bestIndex;
    bool     flags;
    float    limit;
    float    dist;
    float    zero;
    uint32_t count;
    float    bestScore;

    if (a4 == 0 && mCurrentAnim != -1)
        return 0xffffffff;

    scale = FUN_00d38a30(0, this);
    count = ((uint32_t (__thiscall*)(cSPCreatureBase*))
             ((*(void***)(void*)this)[0xb0 / 4]))(this);
    bestScore = gNegOne;
    bestIndex = 0xffffffff;
    bestDist = gFLTMax;

    if (count > 0) {
        offset = 0;
        uint32_t i = 0;
        do {
            TargetSlot* slot = (TargetSlot*)((char*)mTargetSlots + offset);
            cTarget* target = ((cTarget* (__thiscall*)(cSPCreatureBase*, uint32_t))
                               ((*(void***)(void*)this)[0xb4 / 4]))(this, i);

            if (pMask) {
                uint32_t type = (uint32_t)target->mType;
                if (type >= 0x58)
                    goto next;
                bool hit = (pMask[type >> 5] & (1u << (type & 31))) != 0;
                if (!hit)
                    goto next;
            }
            if (target->mState != 1)
                goto next;
            if (target->mFlag114)
                goto next;
            if (0.0f >= target->mMaxRange)
                goto maxRangePass;
            if (!(mMaxDistance >= target->mMaxRange))
                goto next;
        maxRangePass:
            if (a3 != 0)
                goto a3Pass;
            if (!(slot->mValue >= gOne))
                goto next;
        a3Pass:
            if (a6 != 0)
                goto a6Pass;
            if (!((target->mRadiusB + target->mRadiusA) * scale >= range))
                goto next;
        a6Pass:

            if (a5 == 0) {
                limit = gZeroPointTwo;
                limit += range;
                flags = ((mFlags >> 9) & 1) != 0;
                float reach = target->GetTimeToReach(flags);
                if (limit < reach)
                    goto next;
            }

            float score = target->mScore;
            if (score > 0.0f || target->mType == 0x20) {
                zero = 0.0f;
                dist = range - (target->mRadiusB + target->mRadiusA) * scale;
                float* pClamped = &zero;
                if (!(zero > dist))
                    pClamped = &dist;
                float clamped = *pClamped;

                if (a7 != 0) {
                    if (bestDist > clamped)
                        goto update;
                    if (!(gEpsilon > clamped - bestDist))
                        goto next;
                    if (!(score > bestScore))
                        goto next;
                } else {
                    if (!(score > bestScore))
                        goto next;
                }
            update:
                bestDist = clamped;
                bestIndex = i;
                bestScore = score;
            }

        next:
            offset += 0x10;
            i++;
        } while (i < count);
    }

    return bestIndex;
}
