// Slice s00b498d0 -- 0x00b498d0: creature locomotion "socialise / avoid" action callback.
//
// The claimed VA 0x00b498d0 is a free __cdecl function of 0x180 bytes (the decomp index records size
// 384).  The next function start the harness knows about is 0x00b4a720, so bounds() spans
// 0x00b498d0..0x00b4a71c (3661 bytes) and also covers 0x00b49a50 (0xccd bytes), a second routine that
// Ghidra leaves as LAB_00b49a50 and that is only ever referenced from tables / passed as an "action"
// id to FUN_00c426e0 / FUN_00c43fe0 / FUN_00c42140.  Only the claimed function is reconstructed here;
// its own 0x180 bytes are the target.  chk.py's n0 therefore stays 3661 and reports the size penalty,
// while run_all.py --manifest (which measures the symbol's own bytes) reports MATCH.
//
// Registered as a locomotion-strategy action by
//   Simulator::cCreatureBase::CreateLocomotionStrategy (0x00c06500)
//     -> FUN_00c43fe0(loco, &FUN_00b498d0)   when GetSim()->m_20 == 0 || GetSim()->m_20 == 2
// Sibling actions of the same strategy (0x00b49730, 0x00b493e0, 0x00b4c730) are registered when
// ((this->m_b58 >> 9) & 1) and GetCurrentGameMode() == &g_Mode_1654c05.
//
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

struct V3 { float x, y, z; };

// ------------------------------------------------------------------ the creature component (class C)
// Returned by GetComponent(0xce9f6639); the same object sits at ctx+0x80.  Slot 46 (+0xb8) is the
// interface cast, slot 29 (+0x74) the radius and slot 11 (+0x2c) the facing direction.
struct C {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual const V3* GetDirection();           // slot 11  (+0x2c)
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28();
    virtual float GetRadius();                  // slot 29  (+0x74)
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
    virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
    virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45();
    virtual C* GetComponent(uint32_t id);       // slot 46  (+0xb8)
    virtual void s47();

    int  FUN_00c0c2f0();                        // 0x00c0c2f0 (this->[0xeac])
    bool Flag388();                             // 0x00c0c0e0  ?Flag388@C@@QAE_NXZ

    char     pad04[0xb58 - 0x04];
    uint32_t m_b58;                             // +0xb58  bit 9 = "strategy active" flag
    char     padb5c[0xf90 - 0xb5c];
    char     m_f90;                             // +0xf90
};

// Inline bit probe.  cl folds `(x >> 9) & 1` written inline into `test dword [mem], 0x200`, but the
// original keeps the load/shr/test sequence, which this helper reproduces.
__forceinline bool BitTest(const uint32_t* f, int n) { return ((*f >> n) & 1) != 0; }

// The strategy context handed to the callback; +0x80 holds the creature.
struct ActionCtx {
    char pad00[0x80];
    C*   m_creature;                            // +0x80
};

// Objects returned by the sphere query.
struct Found {
    char    pad00[0x34];
    uint8_t m_34;                               // +0x34  bit 0: dead / already ignored
    char    pad35[0x44 - 0x35];
    float   m_44;                               // +0x44  radius
    char    pad48[0x88 - 0x48];
    int     m_88;                               // +0x88  object class
};

// Fixed-capacity vector with inline storage (0x18-byte header + N elements).
template<class T, int N> struct FixedVector {
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator[2];
    int      mBufferHeader;
    T        mBuffer[N];

    __forceinline FixedVector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + N), mBufferHeader(0) {}
    __forceinline ~FixedVector() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin); }
};

// ------------------------------------------------------------------ helpers
struct Sim { char pad20[0x20]; int m_20; };
Sim* GetSim();                                  // 0x00b3d310

struct ObjectFinder {
    void Query(const V3* dir, void* out, uint32_t mask, float radius, int flag, const V3* p);   // 0x00b79c30
};
ObjectFinder* GetObjectFinder();                // 0x00b3d3c0

void* GetCurrentGameMode();                     // 0x00b5b800
extern char g_Mode_1654c05;                     // 0x01654c05

void FUN_00b48f20(ActionCtx* ctx, float a, void* b, float c);   // 0x00b48f20

// @ 0x00b498d0
void FUN_00b498d0(ActionCtx* param_1)
{
    C* c;
    if (param_1->m_creature != 0) {
        c = param_1->m_creature->GetComponent(0xce9f6639);
        if (c != 0) {
            if (c->m_f90 == 0) return;
            if (c->FUN_00c0c2f0() < 2) return;
        }
    } else {
        c = 0;
    }

    if (GetSim()->m_20 != 0
        || BitTest(&c->m_b58, 9)
        || c->Flag388()
        || GetCurrentGameMode() == &g_Mode_1654c05)
    {
        uint32_t slot;                                  // placeholder for the f temp slot
        float f = param_1->m_creature->GetRadius();
        float hi = f + 2.0f;
        float lo = f * 1.5f;
        (void)slot;
        float* p = &hi;
        if (lo <= hi) p = &lo;

        FixedVector<Found*, 256> list;
        ObjectFinder* finder = GetObjectFinder();
        finder->Query(param_1->m_creature->GetDirection(), &list, 0x1f, *p, 0, 0);

        for (Found** it = list.mpBegin; it != list.mpEnd; ++it) {
            Found* o = *it;
            if (o->m_88 == 3 && (o->m_34 & 1)) continue;
            FUN_00b48f20(param_1, hi, (char*)o + 0x38, o->m_44);
        }
    }
}
