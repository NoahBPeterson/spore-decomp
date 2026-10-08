// slice s00e707d0: FUN_00e70e30 (0x00e70e30, 236 bytes): per-tick countdown of a timed-effect record.
// Two pool handles (+0x220, +0x22c) are validated through gspCellGame->mCells.GetSafe (thiscall, ret 4);
// a stale handle clears its timer. The main timer at +0x238 is decremented by dt and, when it goes
// negative, FUN_00e70cf0(self, arg) runs and the timer is reset to 0.25.
// Called only from FUN_00e7a0a0 (cdecl, three stack args: self, arg, dt).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef uint32_t uint32;

// gspCellGame (cCellGame*), global at 0x016b3c04; mCells (cObjectPool) is at +0x1c.
extern char* gspCellGame;

struct cObjectPool {
    // 0x00b721d0: handle -> element pointer, 0 when the handle is stale. thiscall, `ret 4`.
    uint32 GetSafe(uint32 handle);
};

// Owner of the timed-effect fields (owner type not identified; retail offsets from the asm).
struct cTimedHandles {
    uint32 pad000[0x21c / 4];
    float  mTimerA;      // +0x21c
    uint32 mHandleA;     // +0x220 (pool handle)
    float  mValueA;      // +0x224 (must be <= 0 for the update to run)
    float  mValueB;      // +0x228 (must be <= 0 for the update to run)
    uint32 mHandleB;     // +0x22c (pool handle)
    float  mTimerB;      // +0x230
    uint32 pad234;       // +0x234
    float  mTimerC;      // +0x238 (main countdown)
};

extern const float g_13eb8a0;     // 0.25f

// 0x00e70cf0 (cdecl, two stack args: self, arg).
void FUN_00e70cf0(cTimedHandles* self, uint32 arg);

// 0x00e70e30 (cdecl, `ret`, caller pops 3 args).
void FUN_00e70e30(cTimedHandles* p, uint32 arg, float dt)
{
    if (!(p->mValueA > 0.0f) && !(p->mValueB > 0.0f)) {
        if (p->mTimerA > 0.0f) {
            uint32 h = p->mHandleA;
            cObjectPool* pool = (cObjectPool*)(gspCellGame + 0x1c);
            uint32 r = pool->GetSafe(h);
            if (r != 0)
                return;
            p->mHandleA = r;
            p->mTimerA = 0.0f;
            p->mTimerC = 0.0f;
        }
        if (p->mTimerB > 0.0f) {
            uint32 h = p->mHandleB;
            cObjectPool* pool = (cObjectPool*)(gspCellGame + 0x1c);
            uint32 r = pool->GetSafe(h);
            if (r != 0)
                return;
            p->mHandleB = r;
            p->mTimerB = 0.0f;
            p->mTimerC = 0.0f;
        }
        if (p->mTimerC >= 0.0f) {
            p->mTimerC = p->mTimerC - dt;
            if (p->mTimerC < 0.0f) {
                FUN_00e70cf0(p, arg);
                p->mTimerC = g_13eb8a0;
            }
        }
    }
}
