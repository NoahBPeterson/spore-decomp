// Slice s00cf8d70 -- SP::cCivModeStrategy helpers (partial).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {

struct cSPUIGlobalUI {
    void ShowOptionWindows(char show);                       // 0x00e042d0
};

struct cCivUIRoot {
    uint32_t        mPad00[0x64 / 4];                        // +0x00 .. +0x63
    cSPUIGlobalUI*  mpGlobalUI;                              // +0x64
};

struct cCivTrackRoot {
    uint32_t mPad00[0x80 / 4];                               // +0x00 .. +0x7f
    void*    mpTracked;                                      // +0x80
};

struct cCivModeStrategy {
    uint32_t       mPad00[0xe8 / 4];                         // +0x00 .. +0xe7
    cCivTrackRoot* mpTrackRoot;                              // +0xe8
    cCivUIRoot*    mpUIRoot;                                 // +0xec

    void ShowOptionWindows();
    bool HasActiveTrack();
};

struct cRangeOut {
    void*    mpFunc;                                         // +0x00
    uint32_t mArg;                                           // +0x04
};

bool __cdecl FUN_00d09660(void* track);                      // 0x00d09660
void __cdecl ForEachNode(cRangeOut* out, uint32_t* first, uint32_t* last,
                         void (__fastcall* fn)(void*), uint32_t extra);

// @ 0x00cf8e00
void cCivModeStrategy::ShowOptionWindows()
{
    mpUIRoot->mpGlobalUI->ShowOptionWindows(1);
}

// @ 0x00cf94b0
bool cCivModeStrategy::HasActiveTrack()
{
    if (mpTrackRoot && mpTrackRoot->mpTracked) {
        if (FUN_00d09660(mpTrackRoot->mpTracked))
            return true;
    }
    return false;
}

// @ 0x00cf94e0
void __cdecl ForEachNode(cRangeOut* out, uint32_t* first, uint32_t* last,
                         void (__fastcall* fn)(void*), uint32_t extra)
{
    for (; first != last; ++first)
        fn((void*)(*first + extra));
    out->mpFunc = (void*)fn;
    out->mArg = extra;
}

} // namespace SP
