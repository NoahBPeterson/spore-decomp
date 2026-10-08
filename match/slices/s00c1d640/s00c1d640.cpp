// Slice s00c1d640: creature AI, ability selection (picks the best usable attack/ability against a target).
// Optimized module: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// Stubs (offsets / vtable slots recovered from 0x00c1de20)
// ---------------------------------------------------------------------------
void operator_delete__(void* p);                                          // 0x00f47380

// SP::SimpleVector<unsigned int> (begin, end, capacity, allocator)
struct UIntVector {
    uint* mpBegin;
    uint* mpEnd;
    uint* mpCapacity;
    uint mAllocator[2];
    void DoInsertValue(uint* position, const uint& value);              // 0x004558a0 (ret 8)
    void push_back(const uint& v)
    {
        if (mpEnd < mpCapacity) {
            uint* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
    ~UIntVector()
    {
        if (mpBegin && ((int*)mpBegin)[-1])
            operator_delete__(mpBegin);
    }
};

// 88-bit set of ability ids
struct AbilityMask {
    uint w[3];
    bool test(uint id) const
    {
        if (id >= 0x58)
            return false;
        return (w[id >> 5] & (1u << (id & 0x1f))) != 0;
    }
};

// Ability tuning record (TuningObj)
struct Ability {
    char pad0[8];
    uint id;                    // +0x08
    int mKind;                  // +0x0c
    char pad10[0x2c];
    float f3c;                  // +0x3c
    char pad40[0x44];
    float f84;                  // +0x84
    char pad88[0x14];
    float f9c;                  // +0x9c
    char pada0[8];
    float fa8;                  // +0xa8
    char padac[0x48];
    float ff4;                  // +0xf4
    char padf8[8];
    float f100_pad;
    float f104;                 // +0x104  (cost)
    char pad108[0xc];
    unsigned char mbBusy;       // +0x114
    char pad115[0xb];
    int m120;                   // +0x120
    float GetBound(bool upper); // 0x004d3d70 (ret 4)
};

struct Entry { float f0; float f4; float f8; float fc; };               // 16-byte per-ability state

struct TypeObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual uint GetType();                                      // slot 8 (+0x20)
};
struct TypeHolder {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual TypeObj* Get();                                             // slot 3 (+0xc)
};

// Sub-object (secondary base) at +0xc0 of a creature
struct Body {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual const void* GetPos();                                       // slot 11 (+0x2c)
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28();
    virtual float GetRadius();                                          // slot 29 (+0x74)
    const void* GetBodyPos();                                           // 0x00c42de0
};

float DistanceBetweenBodies(const void* posA, float radiusA, const void* posB, float radiusB, bool clamp0);  // 0x00d99a60

struct Creature {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual Creature* Query(uint id);                                   // slot 23 (+0x5c)
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
    virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
    virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38();
    virtual void s39(); virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
    virtual uint GetAbilityCount();                                     // slot 44 (+0xb0)
    virtual Ability* GetAbility(uint index);                            // slot 45 (+0xb4)
    char pad04[0xbc];
    Body mBody;                                                         // +0xc0 (secondary base with vptr)
    char padc4[0xa94];
    uint mFlags;                                                        // +0xb58
    char padb5c[0x54];
    unsigned char mbNoBonus;                                            // +0xbb0
    char padbb1[0x77];
    Entry* mpEntries;                                                   // +0xc28
    char padc2c[0x22c];
    float mEnergy;                                                      // +0xe58
    char pade5c[0x20];
    TypeHolder* mpTypeHolder;                                           // +0xe7c
    char pade80[0xc];
    uint mActiveAbility;                                                // +0xe8c
    char pade90[0x7e0];
    uint mCooldownCount;                                                // +0x1670

    bool IsUpper() const { return (mFlags >> 9) & 1; }
    float F00c0ce80(int a, int b);                                      // 0x00c0ce80 (ret 8)
    uint ChooseAbility(AbilityMask* mask, Creature* target, float dist, bool flag);   // 0x00c1de20
};

float GetScale(int zero, Creature* c);                                  // 0x00d38a30 (cdecl)
const uint kCombatantTypeId = 0x018eb45e;
extern float gChargeScale;                                              // 0x01572058 (10.0)
extern float gBoundScale;                                               // 0x01572054 (1.5)

// @ 0x00c1de20
uint Creature::ChooseAbility(AbilityMask* mask, Creature* target, float dist, bool flag)
{
    uint best = (uint)-1;
    if (mActiveAbility != (uint)-1)
        return best;

    if (mask) {
        mask->w[2] &= 0xfffffdff;
        mask->w[0] &= 0xdfffffff;
    }
    float scale = GetScale(0, this);

    Creature* tc = target ? target->Query(0xd0036e08) : 0;
    bool nearTarget = false;
    if (tc) {
        TypeObj* owner;
        TypeHolder* holder = tc->mpTypeHolder;
        if (holder && (owner = holder->Get()) != 0 && owner->GetType() == kCombatantTypeId) {
        } else {
            owner = 0;
        }
        if ((void*)owner == (void*)this) {
            Body* tb = &tc->mBody;
            Body* mb = &mBody;
            float d = DistanceBetweenBodies(mb->GetPos(), mb->GetRadius(), tb->GetBodyPos(), tb->GetRadius(), true);
            if (dist < 5.0f || d < 5.0f)
                nearTarget = true;
        }
    }

    uint count = GetAbilityCount();
    float bestScore = 0.0f;
    bool bestReady = false;
    Ability* bestAbility = 0;
    float bestMargin = dist;
    UIntVector cands;
    cands.mpBegin = 0; cands.mpEnd = 0; cands.mpCapacity = 0;
    for (uint i = 0; i < count; ++i) {
        Entry* e = &mpEntries[i];
        Ability* a = GetAbility(i);
        if (mask && !mask->test(a->id))
            continue;
        if (tc) {
            if (!((tc->IsUpper() && a->id == 0x3d) || a->m120 == -1)) {
                if (tc->mCooldownCount > 0)
                    continue;
            }
        }
        if (a->mKind != 1 || a->mbBusy || !(mEnergy >= a->f104))
            continue;

        float lo = (a->ff4 + a->fa8) * scale;
        float hi = a->GetBound(IsUpper()) * scale;
        bool inRange = lo >= dist && dist >= hi;
        bool noBound = lo < 10.0f && a->GetBound(IsUpper()) == 0.0f;
        float score = (a->f84 + a->f3c) / a->f9c;
        bool ready = e->f4 >= 1.0f;
        uint id = a->id;
        switch (id) {
        case 0x1f:
            if (inRange && ready) score = gChargeScale * score;
            break;
        case 0x48:
            if (inRange && ready) score = 90.0f;
            break;
        case 0x4b:
            if (inRange && ready) score = 100.0f;
            else score = 0.0f;
            break;
        }
        if (!noBound && id != 0x1f)
            score = gBoundScale * score;

        float penalty = 0.0f;
        float margin = dist;
        if (!inRange) {
            float gap = 0.0f;
            float w = 1.0f;
            if (dist > lo) {
                gap = dist - lo;
                margin = lo;
            } else if (hi > dist) {
                gap = hi - dist;
                margin = hi;
                w = 0.5f;
            }
            float norm = mbNoBonus ? F00c0ce80(2, 1) + 10.0f : F00c0ce80(2, 0);
            penalty = gap / norm * w;
        }

        if ((noBound && !flag) || (inRange && ready) || (!nearTarget && !flag)) {
            score = score - penalty * score * 0.1f;
            if (score > bestScore || !bestAbility) {
                bestMargin = margin;
                bestScore = score;
                best = i;
                bestReady = ready;
                bestAbility = a;
            }
            cands.push_back(i);
        }
    }

    if (bestMargin == dist && !bestReady) {
        float top = 0.0f;
        int n = (int)(cands.mpEnd - cands.mpBegin);
        for (int j = 0; j < n; ++j) {
            uint idx = cands.mpBegin[j];
            Entry* e = &mpEntries[idx];
            Ability* a = GetAbility(idx);
            float lo = (a->ff4 + a->fa8) * scale;
            float hi = a->GetBound(IsUpper()) * scale;
            bool inRange = lo >= dist && dist >= hi;
            bool ready = e->f4 >= 1.0f;
            if (inRange && ready) {
                float extra = bestAbility ? bestAbility->f104 : 0.0f;
                if (mEnergy > a->f104 + extra) {
                    float s = (a->f84 + a->f3c) / a->f9c;
                    if (s > top) {
                        top = s;
                        best = idx;
                    }
                }
            }
        }
    }
    return best;
}

#define OFFCHK(T, m, o) typedef char offchk_##T##_##m[((unsigned)(unsigned long)&((T*)0)->m == (o)) ? 1 : -1]
OFFCHK(Ability, id, 0x8); OFFCHK(Ability, mKind, 0xc); OFFCHK(Ability, f3c, 0x3c); OFFCHK(Ability, f84, 0x84);
OFFCHK(Ability, f9c, 0x9c); OFFCHK(Ability, fa8, 0xa8); OFFCHK(Ability, ff4, 0xf4); OFFCHK(Ability, f104, 0x104);
OFFCHK(Ability, mbBusy, 0x114); OFFCHK(Ability, m120, 0x120);
OFFCHK(Creature, mBody, 0xc0); OFFCHK(Creature, mFlags, 0xb58); OFFCHK(Creature, mbNoBonus, 0xbb0);
OFFCHK(Creature, mpEntries, 0xc28); OFFCHK(Creature, mEnergy, 0xe58); OFFCHK(Creature, mpTypeHolder, 0xe7c);
OFFCHK(Creature, mActiveAbility, 0xe8c); OFFCHK(Creature, mCooldownCount, 0x1670);
