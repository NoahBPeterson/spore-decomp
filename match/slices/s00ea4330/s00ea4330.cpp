// Slice s00ea4330 -- SP::Audio::cCityMusicViewer (partial).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {
namespace Audio {

struct IEventModifier {
    void*          mpVtable0;                                // +0x00
    volatile void* mpVtable4;                                // +0x04
    uint32_t       mPad08;                                   // +0x08
    IEventModifier();
};

// @ 0x00ea4fd0
IEventModifier::IEventModifier()
{
    mpVtable4 = (void*)0x013ef094;
    mPad08 = 0;
    mpVtable0 = (void*)0x0148734c;
    mpVtable4 = (void*)0x01487348;
}

} // namespace Audio
} // namespace SP
