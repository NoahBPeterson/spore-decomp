// src/game/ealayer31/ealayer3core.cpp.cpp -- migrated from slice(s) s01149f70 by tools/migrate/rewrite.py
// Object file: ealayer31/ealayer3core.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/System.h"
#include <string.h>
#include <math.h>
#pragma function(memcpy)
#pragma function(memmove)
#pragma intrinsic(sqrtf)

// ---- items of slice s01149f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace audio {
namespace core {
extern int   EALayer3Core_InitCoeffs(void* self, int n); // 0x1146d20  EALayer3Core::InitCoeffs(int), defined below
}
}
}
namespace rw {
namespace audio {
namespace core {
// 0x1146ca0: the inherited base. It installs its own vftable and calls itself this constructor's first callee.
class CMpegBase {
public:
    virtual ~CMpegBase();                 // vftable at +0x00
    CMpegBase();                          // 0x1146ca0 (out of line, in its own translation unit)
    void AllocateSynth(int n);            // 0x1148cf0
};

class EALayer3Core;

class EALayer3Core : private CMpegBase {
public:
    friend CMpegBase::CMpegBase();
    virtual ~EALayer3Core();              // +0x00 (vftable)
    char mData[0x37c];                    // +0x04 .. +0x37f  (fields accessed by offset)

    EALayer3Core(int n);
    void SetMode();                                             // 01149fd0
    void AnalyzeStatistics(int a2, int a3);                     // 0114a160
    static void OnInterface(EALayer3Core* self, int a2);        // 0114a470
    void ResetSlot(int idx);                                    // 0114a4a0
    void Interpolate(int a2, int a3, float* a4, int a5);        // 0114a4c0
    int AdjustOffset(float* a2);                                // 0114a680
    void AppendSamples(int a2, int a3, int a4, int a5, int a6); // 0114a750
    void UpdateCorrelation(int a2, int a3, float a4, float* a5);// 0114a970
    void AddToOutput(int a2, int a3, int a4, int a5, int a6, int a7, char a8); // 0114aa40
    void ResetSlots();                                          // 0114ad10
    int  InitCoeffs(int n);                                     // 0x1146d20
    static int  SelectPath(EALayer3Core* self, int a2, int a3, int a4); // 0114ad50

    int   i32(int off) const { return *(const int*)((const char*)this + off); }
    int&  i32(int off) { return *(int*)((char*)this + off); }
    float  f32(int off) const { return *(const float*)((const char*)this + off); }
    float& f32(int off) { return *(float*)((char*)this + off); }
    unsigned char  u8(int off) const { return *(const unsigned char*)((const char*)this + off); }
    unsigned char& u8(int off) { return *(unsigned char*)((char*)this + off); }
};
}
}
}
// ---- items of slice s01149f70 end

// @ 0x01149f70
namespace rw { namespace audio { namespace core {
EALayer3Core::EALayer3Core(int n)
{
    *(void**)this = (void*)0x14ce590;
    // 0x1148cf0: CMpegBase::AllocateSynth(n), inherited from the base class
    AllocateSynth(n);
    // 0x1146d20: EALayer3Core::InitCoeffs(n)
    InitCoeffs(n);
}
}}}  // namespace rw::audio::core

// @ 0x01146d20
namespace rw { namespace audio { namespace core {
int EALayer3Core::InitCoeffs(int n)
{
    return ::rw::audio::core::EALayer3Core_InitCoeffs(this, n);
}
}}}  // namespace rw::audio::core
