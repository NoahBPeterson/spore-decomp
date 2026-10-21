// src/game/SPAudio/SPAudioEmitterSndPlayer.cpp -- migrated from slice(s) s00a38e40 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioEmitterSndPlayer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/Command.h"
#include "EA/Audio/IConfiguration.h"
#include "EA/ResourceMan/Key.h"
#include "EA/Audio/ResponseCurve.h"
#include "rw/audio/core/System.h"
#include "EA/Audio/VoiceContainer.h"
#include "SP/Audio/cEventModifier.h"
#include "SP/Audio/cEventModifierPrimitive.h"
#include <ctype.h>
#include <string.h>

// ---- items of slice s00a38e40 begin (TODO(rewrite): local stubs, replace by canonical classes)
void operator delete(void*) throw();     // 0x00f47380
void operator delete[](void*);           // 0x00f47380
void operator delete(void*, const char*, int, int, int, int);
void operator delete(void*, const char*, int, int, const char*, int);
inline void operator delete(void*, void*) {}
namespace EA {
namespace Audio {
struct ResponseCurve_s00a3_8e40 {
    void* mpData;        // +0
    char pad4[0xc];      // +4..+0xf
    void* mpInline;      // +0x10
    char pad14[0x350];   // +0x14..+0x363
    ResponseCurve_s00a3_8e40();                          // 0x00a1aa50
    long double GetOutputValue(float x);      // 0x00a1a110
    ~ResponseCurve_s00a3_8e40() { if (mpData && mpData != mpInline) operator delete[](mpData); }
};
}
}
namespace EA {
namespace Audio {
class EmitterSndPlayer { public:
    char pad0[0x10];
    ResponseCurve_s00a3_8e40 mAttenuationCurve;   // +0x10..+0x373
    char pad374[0x18];                 // +0x374..+0x38b
    char pad38c[0x984];                // +0x38c..+0xd0f
    int md10;                          // +0xd10
    char padd14[0xec];                 // +0xd14..+0xdff
    bool CreateVoice();                        // 0x00a13300
    bool GetProperty(uint32_t key, float* out);   // 0x00a11a60
    void Reset();                              // 0x00a124a0
};
}
}
namespace EA {
namespace Audio {
struct VoiceContainer_s00a3_8e40 {
    void* FindPlugin(uint32_t id);   // 0x00a34230
};
}
}
namespace rw {
namespace audio {
namespace core {
struct System_s00a3_8e40 {
    void IsCommandComplete(int cmd, float v);   // 0x0112ccf0
    void GetLevel(int a, float* out);           // 0x0112cc80
};
}
}
}
struct AudioLockObj {
    void Lock();     // 0x0112c600
    void Unlock();   // 0x0112c620
};
extern AudioLockObj* gAudioLockObj;   // 0x016e61a8
namespace SP {
namespace Audio {
using namespace EA;
}
}
namespace SP {
namespace Audio {
using namespace EA::Audio;
}
}
namespace SP {
namespace Audio {
class cEmitterSndPlayer : public EmitterSndPlayer { public:
    void* mpE00;   // +0xe00
    float mE04;    // +0xe04

    long double ComputeGainAttenuation(float a, float b, float c, float d);
    bool CreateVoice();
    void Reset();
    void SetCommandComplete(float t);
    bool GetProperty(uint32_t key, float* out);
};
}
}
    void operator delete[](void*); // 0x00f47380
    void operator delete(void*); // 0x00f47380
// ---- items of slice s00a38e40 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern AudioLockObj* gAudioLockObj;   // 0x016e61a8

// @ 0x00a38e40
namespace SP { namespace Audio {
long double cEmitterSndPlayer::ComputeGainAttenuation(float a, float b, float c, float d)
{
    if (c <= a) {
        if (b != 0.0f) {
            if (d < a) return 0.0L;
            return mAttenuationCurve.GetOutputValue((a - c) / (d - c));
        }
    }
    return 1.0L;
}
}}  // namespace SP::Audio

// @ 0x00a38ea0
namespace SP { namespace Audio {
bool cEmitterSndPlayer::CreateVoice()
{
    if (!EmitterSndPlayer::CreateVoice()) return false;
    void* p = ((VoiceContainer_s00a3_8e40*)((char*)this + 0x38c))->FindPlugin(0x56754d31);
    mpE00 = p;
    return true;
}
}}  // namespace SP::Audio

// @ 0x00a38ed0
namespace SP { namespace Audio {
void cEmitterSndPlayer::Reset()
{
    mpE00 = 0;
    EmitterSndPlayer::Reset();
}
}}  // namespace SP::Audio

// @ 0x00a38ee0
namespace SP { namespace Audio {
void cEmitterSndPlayer::SetCommandComplete(float t)
{
    rw::audio::core::System_s00a3_8e40* s = (rw::audio::core::System_s00a3_8e40*)mpE00;
    if (s) {
        int v;
        if (mE04 > t) v = 1;
        else v = 0;
        s->IsCommandComplete(0x12, (float)v);
    }
}
}}  // namespace SP::Audio

// @ 0x00a38fe0
namespace SP { namespace Audio {
bool cEmitterSndPlayer::GetProperty(uint32_t key, float* out)
{
    if (key != 0x6fa19f04) return EmitterSndPlayer::GetProperty(key, out);
    if (mpE00) {
        if (gAudioLockObj) gAudioLockObj->Lock();
        rw::audio::core::System_s00a3_8e40* s = (rw::audio::core::System_s00a3_8e40*)mpE00;
        if (md10 == 1) {
            s->GetLevel(1, out);
        } else {
            float a, b;
            s->GetLevel(0, &a);
            s->GetLevel(2, &b);
            *out = (b + a) * 0.5f;
        }
        if (gAudioLockObj) gAudioLockObj->Unlock();
    }
    return true;
}
}}  // namespace SP::Audio
