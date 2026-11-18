#include "game/types.h"
#include <intrin.h>

namespace EA {
namespace Audio {
struct ResponseCurve_s00a3_8e40 {
    void* mpData;        // +0
    char pad4[0xc];      // +4..+0xf
    void* mpInline;      // +0x10
    char pad14[0x350];   // +0x14..+0x363
    long double GetOutputValue(float x);      // 0x00a1a110
    ~ResponseCurve_s00a3_8e40() { if (mpData && mpData != mpInline) operator delete[](mpData); }
};
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
struct AudioLockGuard_s00a3 {
    AudioLockGuard_s00a3() { if (gAudioLockObj) gAudioLockObj->Lock(); }
    ~AudioLockGuard_s00a3() { if (gAudioLockObj) gAudioLockObj->Unlock(); }
};
namespace SP {
namespace Audio {
using namespace EA;
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

// Command id passed to rw::audio::core::System::IsCommandComplete by SetCommandComplete.
static const int kCommandIdSetCommandComplete = 0x12;

// Plugin id of the level-meter plugin looked up in the voice container by CreateVoice.
static const uint32_t kLevelMeterPluginId = 0x56754d31;

// @ 0x00a38e40
namespace SP { namespace Audio {
long double cEmitterSndPlayer::ComputeGainAttenuation(float a, float b, float c, float d)
{
    if (c <= a) {
        if (b != 0.0f) {
            if (a <= d) return 0.0L;
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
    mpE00 = ((VoiceContainer_s00a3_8e40*)((char*)this + 0x38c))->FindPlugin(kLevelMeterPluginId);
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
        s->IsCommandComplete(kCommandIdSetCommandComplete, (float)v);
    }
}
}}  // namespace SP::Audio

// @ 0x00a38fe0
namespace SP { namespace Audio {
bool cEmitterSndPlayer::GetProperty(uint32_t key, float* out)
{
    if (key != 0x6fa19f04) return EmitterSndPlayer::GetProperty(key, out);
    if (mpE00) {
        AudioLockGuard_s00a3 lock;
        if (md10 == 1) {
            ((rw::audio::core::System_s00a3_8e40*)mpE00)->GetLevel(1, out);
        } else {
            float a, b;
            ((rw::audio::core::System_s00a3_8e40*)mpE00)->GetLevel(0, &a);
            ((rw::audio::core::System_s00a3_8e40*)mpE00)->GetLevel(2, &b);
            *out = (b + a) * 0.5f;
        }
    }
    return true;
}
}}  // namespace SP::Audio
