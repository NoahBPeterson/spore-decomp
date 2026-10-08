// Slice s00a187f0: EA::Audio::FactoryConfiguration::AddLegacyPropertyTypes (0x00a18d90, 2152 bytes).
// Fills the legacy property-type map (name hash -> Variant type id, bit 31 = array flag)
// at this+0x40 with the audio resource property names.
#include "types.h"

namespace EA { namespace Hash {
uint32_t FNV1_String8(const char* s, uint32_t seed, int lowercase);   // 0x00932E80
}}

struct PropertyTypeMap {
    uint32_t& operator[](const uint32_t& key);   // 0x00643A40 eastl::map<uint,uint>::operator[]
};

namespace EA { namespace Audio {
struct FactoryConfiguration {
    char pad[0x40];
    PropertyTypeMap mLegacyTypes;   // +0x40
    void AddLegacyPropertyTypes();
};

#define H(s) EA::Hash::FNV1_String8(s, 0x811c9dc5, 1)

void FactoryConfiguration::AddLegacyPropertyTypes()
{
    mLegacyTypes[H("parent")] = 0x20;
    mLegacyTypes[H("gain")] = 0xd;
    mLegacyTypes[H("pan")] = 0xd;
    mLegacyTypes[H("pitch")] = 0xd;
    mLegacyTypes[H("mindistance")] = 0xd;
    mLegacyTypes[H("maxdistance")] = 0xd;
    mLegacyTypes[H("rolloff")] = 0xd;
    mLegacyTypes[H("streambuffersize")] = 0xa;
    mLegacyTypes[H("streambufferreadsize")] = 0xa;
    mLegacyTypes[H("is3d")] = 1;
    mLegacyTypes[H("islooped")] = 1;
    mLegacyTypes[H("samples")] = 0x80000020;
    mLegacyTypes[H("fadein")] = 0xd;
    mLegacyTypes[H("fadeout")] = 0xd;
    mLegacyTypes[H("priority")] = 0xd;
    mLegacyTypes[H("autoduck")] = 1;
    mLegacyTypes[H("duckcurve")] = 0x8000000d;
    mLegacyTypes[H("ducks")] = 1;
    mLegacyTypes[H("attenuation")] = 0x8000000d;
    mLegacyTypes[H("primitives")] = 0x80000013;
    mLegacyTypes[H("soundtype")] = 0x20;
    mLegacyTypes[H("enable")] = 0xd;
    mLegacyTypes[H("startdelay")] = 0xd;
    mLegacyTypes[H("showmindistance")] = 1;
    mLegacyTypes[H("footcurvenumlegstogain")] = 0x8000000d;
    mLegacyTypes[H("footcurveveltogain")] = 0x8000000d;
    mLegacyTypes[H("footcurvelentohipass")] = 0x8000000d;
    mLegacyTypes[H("footcurvemasstopitch")] = 0x8000000d;
    mLegacyTypes[H("footcurvefootsizetopitch")] = 0x8000000d;
    mLegacyTypes[H("footcurvemasstohipass")] = 0x8000000d;
    mLegacyTypes[H("footcurvemasstogain")] = 0x8000000d;
    mLegacyTypes[H("footcurvefootsizetogain")] = 0x8000000d;
    mLegacyTypes[H("footcurvefootsizetohipass")] = 0x8000000d;
    mLegacyTypes[H("atmospheric")] = 0x8000000d;
    mLegacyTypes[H("polyphony")] = 0xa;
    mLegacyTypes[H("streampoolguid")] = 0x20;
    mLegacyTypes[H("probability")] = 0xd;
    mLegacyTypes[H("dspchain")] = 0x80000013;
    mLegacyTypes[H("syms")] = 0x80000013;
    mLegacyTypes[H("dacoutputmode")] = 0x13;
    mLegacyTypes[H("ignorecontext")] = 1;
    mLegacyTypes[H("voicetemplate")] = 0x20;
    mLegacyTypes[H("foottype")] = 0x13;
    mLegacyTypes[H("mouthtype")] = 0x13;
    mLegacyTypes[H("weapontype")] = 0x13;
    mLegacyTypes[H("time")] = 0xd;
    mLegacyTypes[H("wetlevel")] = 0x8000000d;
    mLegacyTypes[H("reverbtime")] = 0xd;
    mLegacyTypes[H("reverbspacesize")] = 0xd;
    mLegacyTypes[H("timeinvariantpitch")] = 0xd;
    mLegacyTypes[H("listeneroffset")] = 0x8000000d;
}
}}
