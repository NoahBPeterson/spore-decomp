// Slice s00c74d30 - SporeApp 0x00c74d30..0x00c75e30
// SP::cSPPlanetaryArtifact / cSPToolObject / player-war bookkeeping helpers.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
//
// NOTE: only the small helpers below were reconstructed within this pass; the
// remaining slice VAs are recorded as unreconstructed in partial.txt.
#include "types.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef int i32;

// ---- receiver types ----------------------------------------------------------

// Game-noun manager interface slice used by FUN_00c754e0.
struct cGameNounManager {
    i32   GetKind();                               // 0x00bb9ae0
    void* GetAvatar();                             // 0x00b1fdb0
};

struct cStarManager {                              // returned by SP::StarManager(avatar)
    void* GetEmpireByID();                         // 0x00ba9370
};

struct cEmpire {
    void  SetValue(i32 v);                         // 0x00c322f0
};

void* __cdecl FUN_00b3d2a0(void* avatar);          // 0x00b3d2a0 (SP::StarManager)

// ---- counter / stack helper ---------------------------------------------------
// Two adjacent counters live at 0x124c (current depth, clamped to [0,4]) and
// 0x1250 (accumulated count, only touched when the caller asks for it).
struct cDepthCounter {
    u8   mPad0000[0x124c];
    i32  mDepth;                                   // 0x124c
    i32  mTotal;                                   // 0x1250

    void Increment(bool countIt);                  // 0x00c755c0
    void Decrement(bool countIt);                  // 0x00c755f0
};

// @ 0x00c754e0
// If the noun is a level-5 object, hand its owning empire a zero value.
void __stdcall FUN_00c754e0(cGameNounManager* self)
{
    if (self->GetKind() == 5) {
        void* avatar = self->GetAvatar();
        cStarManager* stars = (cStarManager*)FUN_00b3d2a0(avatar);
        void* empire = stars->GetEmpireByID();
        if (empire)
            ((cEmpire*)empire)->SetValue(0);
    }
}

// @ 0x00c755c0
// Raises the depth counter, saturating at 5; also raises the total when asked.
void cDepthCounter::Increment(bool countIt)
{
    if (mDepth < 5) {
        mDepth = mDepth + 1;
        if (countIt)
            mTotal = mTotal + 1;
    }
}

// @ 0x00c755f0
// Lowers the depth counter, saturating at 0; also lowers the total when asked.
void cDepthCounter::Decrement(bool countIt)
{
    if (0 < mDepth) {
        mDepth = mDepth - 1;
        if (countIt)
            mTotal = mTotal - 1;
    }
}
