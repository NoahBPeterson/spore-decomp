// src/game/SPAudio/SPAudioPreferences.cpp -- migrated from slice(s) s00a40cd0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioPreferences.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/ResponseCurve.h"
#include "EA/Audio/Sound.h"
#include "EA/Variant.h"
#include "SP/Audio/cAudioPreferences.h"

// ---- items of slice s00a40cd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(pad_, __COUNTER__)();
struct Variant_s00a4_0cd0 {
    int mTypeId;               // +0x00
    int mFlags;                // +0x04
    void SetFloat(const float* x);        // 0x00428060  Variant::operator=<float>
    void SetUInt(const unsigned* x);      // 0x00427fd0  Variant::operator=<unsigned int>
    void SetBool(const unsigned char* x); // Variant::operator=<bool>
    void Destruct(int free);              // 0x0093db80  Variant::Destruct
};
struct Property {
    char pad0[0x12];
    short mType;                          // +0x12
    float*          GetFloat();           // 0x0041ea70
    unsigned*       GetUInt();            // 0x0041ea00
    unsigned char*  GetBool();            // 0x0041e920
};
struct cPropertyList_s00a4_0cd0 {
    VP VP VP VP VP
    virtual void SetProperty(unsigned key, Variant_s00a4_0cd0* value);       // +0x14 0x006a2e20
    VP VP VP
    virtual bool GetProperty(unsigned key, Property** out);       // +0x24
};
extern cPropertyList_s00a4_0cd0* sPrefs;             // 0x015fd91c
namespace SP {
namespace EditorUtils {
void PlayEditorSound(unsigned a, unsigned b, float c, int d);     // 0x00435f40
}
}
void  SetGlobalProperty(int key, float value);
int*  AudioSystem();                                              // 0x0067cb00
namespace EA {
namespace Audio {
int* GetSystemAT();                                              // 0x00a206f0
}
}
namespace SP {
namespace Audio {
struct cAudioPreferences_s00a4_0cd0 {
    static int  Init();                                     // 0x00a41010
    static bool __stdcall GetVolume(unsigned key, float* out);        // 0x00a411b0
    static int  GetSpeakerMode();                           // 0x00a41200
    static int  GetSoundQuality();                          // 0x00a41240
    static unsigned char IsMuted();                         // 0x00a41280
    static void __stdcall SetVolume(unsigned key, float value);       // 0x00a412c0
    static void __stdcall SetSpeakerMode(unsigned mode);              // 0x00a41410
    static void __stdcall SetSoundQuality(int quality);               // 0x00a41500
    static void __stdcall Mute(unsigned char m);                      // 0x00a415f0
};
}  // namespace SP::Audio
}
// ---- items of slice s00a40cd0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern cPropertyList_s00a4_0cd0* sPrefs;             // 0x015fd91c

// @ 0x00a41010
namespace SP { namespace Audio {
int cAudioPreferences_s00a4_0cd0::Init()
{
    int* sys = EA::Audio::GetSystemAT();
    cPropertyList_s00a4_0cd0* p = sPrefs;
    if (sys && p) {
        Property* prop;
        if (p->GetProperty(0xADED51D5, &prop) && prop->mType == 0xD)
            SP::EditorUtils::PlayEditorSound(0x419c2c6e, 0x25df0108, *prop->GetFloat(), 1);
        if (p->GetProperty(0x8BDD39EC, &prop) && prop->mType == 0xD)
            SP::EditorUtils::PlayEditorSound(0x48d40dfa, 0x25df0108, *prop->GetFloat(), 1);
        if (p->GetProperty(0x09A0474A, &prop) && prop->mType == 0xD)
            SP::EditorUtils::PlayEditorSound(0x18af3b80, 0x25df0108, *prop->GetFloat(), 1);
        if (p->GetProperty(0x3AF239C4, &prop) && prop->mType == 0xD) {
            float v = *prop->GetFloat();
            SP::EditorUtils::PlayEditorSound(0xeafa4162, 0x25df0108, v, 1);
            SP::EditorUtils::PlayEditorSound(0x3db1ffe5, 0x25df0108, v, 1);
            SP::EditorUtils::PlayEditorSound(0x19c4e8ab, 0x25df0108, v, 1);
        }
    }
    return 1;
}
}}  // namespace SP::Audio

// @ 0x00a411b0
namespace SP { namespace Audio {
bool __stdcall cAudioPreferences_s00a4_0cd0::GetVolume(unsigned key, float* out)
{
    cPropertyList_s00a4_0cd0* p = sPrefs;
    if (!p) return false;
    Property* prop;
    if (!p->GetProperty(key, &prop)) return false;
    if (prop->mType != 0xD) return false;
    *out = *prop->GetFloat();
    return true;
}
}}  // namespace SP::Audio

// @ 0x00a41200
namespace SP { namespace Audio {
int cAudioPreferences_s00a4_0cd0::GetSpeakerMode()
{
    int result = 0;
    cPropertyList_s00a4_0cd0* p = sPrefs;
    if (p) {
        Property* prop;
        if (p->GetProperty(0x49D4C74D, &prop) && prop->mType == 0xA)
            result = *prop->GetUInt();
    }
    return result;
}
}}  // namespace SP::Audio

// @ 0x00a41240
namespace SP { namespace Audio {
int cAudioPreferences_s00a4_0cd0::GetSoundQuality()
{
    int result = 3;
    cPropertyList_s00a4_0cd0* p = sPrefs;
    if (p) {
        Property* prop;
        if (p->GetProperty(0x7D8ED666, &prop) && prop->mType == 0xA)
            result = *prop->GetUInt();
    }
    return result;
}
}}  // namespace SP::Audio

// @ 0x00a41280
namespace SP { namespace Audio {
unsigned char cAudioPreferences_s00a4_0cd0::IsMuted()
{
    unsigned char result = 0;
    cPropertyList_s00a4_0cd0* p = sPrefs;
    if (p) {
        Property* prop;
        if (p->GetProperty(0x899EB157, &prop) && prop->mType == 1)
            result = *prop->GetBool();
    }
    return result;
}
}}  // namespace SP::Audio

// @ 0x00a412c0
namespace SP { namespace Audio {
void __stdcall cAudioPreferences_s00a4_0cd0::SetVolume(unsigned key, float value)
{
    cPropertyList_s00a4_0cd0* p = sPrefs;
    if (!p) return;
    if (key == 0x8BDD39EC) {
        SP::EditorUtils::PlayEditorSound(0x48d40dfa, 0x25df0108, value, 1);
    } else if (key == 0x09A0474A) {
        SP::EditorUtils::PlayEditorSound(0x18af3b80, 0x25df0108, value, 1);
    } else if (key == 0x3AF239C4) {
        SP::EditorUtils::PlayEditorSound(0xeafa4162, 0x25df0108, value, 1);
        SP::EditorUtils::PlayEditorSound(0x3db1ffe5, 0x25df0108, value, 1);
        SP::EditorUtils::PlayEditorSound(0x19c4e8ab, 0x25df0108, value, 1);
    } else if (key == 0xADED51D5) {
        SP::EditorUtils::PlayEditorSound(0x419c2c6e, 0x25df0108, value, 1);
    }
    Variant_s00a4_0cd0 v;
    v.mTypeId = 0;
    v.mFlags = 0;
    v.SetFloat(&value);
    p->SetProperty(key, &v);
    if (v.mFlags & 4) v.Destruct(0);
}
}}  // namespace SP::Audio

// @ 0x00a41410
namespace SP { namespace Audio {
void __stdcall cAudioPreferences_s00a4_0cd0::SetSpeakerMode(unsigned mode)
{
    unsigned cur = 0;
    cPropertyList_s00a4_0cd0* p = sPrefs;
    if (p) {
        Property* prop;
        if (p->GetProperty(0x49D4C74D, &prop) && prop->mType == 0xA)
            cur = *prop->GetUInt();
    }
    if (cur != mode && (mode == 2 || (3 < mode && mode < 6)) && sPrefs) {
        Variant_s00a4_0cd0 v;
        v.mTypeId = 0;
        v.mFlags = 0;
        v.SetUInt(&mode);
        p->SetProperty(0x49D4C74D, &v);
        if (v.mFlags & 4) v.Destruct(0);
        int* sys = AudioSystem();
        if (sys) ((void(**)(int*))(*((int**)sys)))[3]((int*)sys);
    }
}
}}  // namespace SP::Audio

// @ 0x00a41500
namespace SP { namespace Audio {
void __stdcall cAudioPreferences_s00a4_0cd0::SetSoundQuality(int quality)
{
    int cur = 3;
    cPropertyList_s00a4_0cd0* p = sPrefs;
    if (p) {
        Property* prop;
        if (p->GetProperty(0x7D8ED666, &prop) && prop->mType == 0xA)
            cur = *prop->GetUInt();
    }
    if (cur != quality && sPrefs) {
        Variant_s00a4_0cd0 v;
        v.mTypeId = 0;
        v.mFlags = 0;
        unsigned q = (unsigned)quality;
        v.SetUInt(&q);
        p->SetProperty(0x7D8ED666, &v);
        if (v.mFlags & 4) v.Destruct(0);
        SetGlobalProperty(0x6df5822d, (float)(unsigned)quality);
    }
}
}}  // namespace SP::Audio

// @ 0x00a415f0
namespace SP { namespace Audio {
void __stdcall cAudioPreferences_s00a4_0cd0::Mute(unsigned char m)
{
    unsigned char cur = 0;
    cPropertyList_s00a4_0cd0* p = sPrefs;
    if (p) {
        Property* prop;
        if (p->GetProperty(0x899EB157, &prop) && prop->mType == 1)
            cur = *prop->GetBool();
    }
    if (cur != m && sPrefs) {
        Variant_s00a4_0cd0 v;
        v.mTypeId = 0;
        v.mFlags = 0;
        v.SetBool(&m);
        p->SetProperty(0x899EB157, &v);
        if (v.mFlags & 4) v.Destruct(0);
        SetGlobalProperty(0x899eb157, (float)m);
    }
}
}}  // namespace SP::Audio
