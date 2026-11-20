#include "types.h"

// ---------------------------------------------------------------------------
// SP::cPlayer::UpdatePlayerCaptureProgressDecay -- 0x00c7ada0
//
// Walks the capture progress list (+0x1214 begin / +0x1218 end, stride 0x28),
// decaying each eastl::pair<unsigned, SP::cGonzagoTimer> entry: read the
// timer's elapsed milliseconds, scale them to seconds and compare against the
// space-combat tuning's capture decay time.  Entries that have outlived it are
// announced through the star/banner path, destroyed and erased from the list.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
// ---------------------------------------------------------------------------

struct cTimerElem {                    // eastl::pair<unsigned, SP::cGonzagoTimer>, stride 0x28
    uint32_t mKey;                     // +0x00
    uint32_t mPad04;                   // +0x04
    uint32_t mTimerVtable;             // +0x08
    uint32_t mRefCount;                // +0x0c
    uint32_t mElapsedLo;               // +0x10
    uint32_t mElapsedHi;               // +0x14
    uint32_t mBaseLo;                  // +0x18
    uint32_t mBaseHi;                  // +0x1c
    uint8_t  mbRunning;                // +0x20
    uint8_t  mPad21[0x03];             // +0x21
    uint32_t mFn;                      // +0x24
};

struct cSPTimerView {                  // SP::cGonzagoTimer timer part of an entry
    uint64_t GetElapsedTime();         // 0x00bc3190
};

struct cTuningView {                   // space-combat tuning object
    int32_t GetCaptureDecayTimeS();    // 0x01029c80
};

struct cBannerHost {                   // object returned by StarManager
    int32_t GetBannerValue();          // 0x00ba6d80
};

struct cGonzagoTimer { void Dtor(); };                                  // 0x00b638b0
uint8_t* eastlCopyImpl(void* dst, void* src, void* last);              // 0x00c771e0

void*    __stdcall StarManager(uint32_t handle);                       // 0x00b3d2a0
void*    GetSpaceCombatTuning();                                       // 0x01029940
void     FUN_00c8c9d0(int32_t value);                                  // 0x00c8c9d0

namespace SP {

struct cPlayer {
    uint8_t    mPad0000[0x1214];       // +0x0000
    cTimerElem* mCaptureBegin;         // +0x1214
    cTimerElem* mCaptureEnd;           // +0x1218

    // 0x00c7ada0  decay the capture progress list
    void UpdatePlayerCaptureProgressDecay();
};

} // namespace SP

// @ 0x00c7ada0
void SP::cPlayer::UpdatePlayerCaptureProgressDecay()
{
    cTimerElem* begin = mCaptureBegin;
    if (begin == mCaptureEnd)
        return;

    do {
        cSPTimerView* timer = (cSPTimerView*)((char*)begin + 8);
        uint64_t elapsed = timer->GetElapsedTime();
        float    seconds = (float)elapsed * 0.001f;

        cTuningView* tuning = (cTuningView*)GetSpaceCombatTuning();
        int32_t decayTime = tuning->GetCaptureDecayTimeS();

        // Has the entry outlived the decay time?  The negated `>` is the retail
        // spelling: cl lowers it to `fild decayTime; fld seconds; fcompi st(1); jbe`
        // (a `<=' here makes it load seconds first and branch with `jae`).
        if (!(seconds > (float)decayTime))
            return;

        uint32_t handle = begin->mKey;
        int32_t  value  = ((cBannerHost*)StarManager(handle))->GetBannerValue();
        FUN_00c8c9d0(value);

        if ((cTimerElem*)((char*)begin + 0x28) < mCaptureEnd)
            eastlCopyImpl((char*)begin + 0x28, mCaptureEnd, begin);

        mCaptureEnd = (cTimerElem*)((char*)mCaptureEnd - 0x28);
        ((cGonzagoTimer*)((char*)mCaptureEnd + 8))->Dtor();
    } while (begin != mCaptureEnd);
}
