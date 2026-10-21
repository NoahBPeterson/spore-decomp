// Slice s00a114a0 (gold2 batch).  EA::Audio::EmitterSndPlayer sample-player methods,
// MSVC 2008 SP1 32-bit, flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
//   0xa114a0  Start(double)                       (vtable slot 5)
//   0xa116f0  SetProperty(uint,float,bool)        (vtable slot 11)
//   0xa11a60  GetProperty(uint,float*)            (vtable slot 12)
//   0xa11e10  Tick(int,float)                     (secondary interface, object+4)
//   0xa11f50  UpdateParameters(float,bool)        (vtable slot 0x70)
//   0xa12120  ParseResource()
#include "types.h"

// =====================================================================================
// Callees / globals defined in other translation units.
// =====================================================================================
extern "C" __declspec(dllimport) char* __cdecl strncpy(char*, const char*, unsigned);

void* __cdecl f_00a206f0_GetSystemAT();      // EA::Audio::GetSystemAT
extern void* g_16e61a8;                      // rw::audio::core::System singleton

// rw::audio::core::System -- only used through explicit vtable slots here.
struct RwSystem {
    void IsCommandComplete(int, float);      // 0x112ccf0
};

// audio system singleton support object (Lock/Unlock live on it)
struct SysGlobal {
    bool Check(void*);
    void DoA();                              // 0x112c600 (Lock)
    void DoB();                              // 0x112c620 (Unlock)
};

// rw::audio::core::PlugIn -- the sample-playback voice plug-in objects stored in the
// EmitterSndPlayer plugin slots.  All methods are resolved out of line.
struct PlugIn {
    void Send(int, void*);                   // 0x112ccc0 (vtable slot 1 dispatch)
    void GetParam(int, double*);             // 0x112cca0
};

// rw::audio::core::BitGetter -- little-endian bit reader (see slice s00a102e0).
struct BitGetter {
    uint8_t* mpBitBuffer;                    // 0x00
    uint32_t mBitPosition;                   // 0x04
    uint32_t GetBits(uint32_t n);            // 0xa10ef0
};

namespace EA { namespace Audio {
class ResourceDeviceDriver { public:
    static bool KeyToText(uint8_t* key, char* text, uint32_t* size);   // 0xa10f70
};
struct VoiceContainer {
    void CommitBoundProperties();            // 0xa33dc0
    bool Connect();                          // 0xa34bf0
    bool SetProperty(uint32_t, float);       // 0xa33ee0
    bool GetProperty(uint32_t, float*);      // 0xa33fd0
};
}} // namespace EA::Audio

// =====================================================================================
// Lock guard objects.  Both bodies are inlined at the call site; their only purpose in
// the original code is to bracket a critical section and to install an /EHsc try level.
// =====================================================================================
struct LockGuard {
    LockGuard()  { if (g_16e61a8) ((SysGlobal*)g_16e61a8)->DoA(); }
    ~LockGuard() { if (g_16e61a8) ((SysGlobal*)g_16e61a8)->DoB(); }
};

// =====================================================================================
// float classification helpers (inlined at the call sites).
// =====================================================================================
union FloatBits { float f; uint32_t i; };

static __forceinline bool IsZeroOrNormal(float f) {
    FloatBits u; u.f = f;
    return (u.i & 0x7fffffff) == 0 ||
           ((u.i - 0x800000u) & 0x7f800000u) < 0x7f000000u;
}
static __forceinline bool IsDenormal(float f) {
    FloatBits u; u.f = f;
    return ((u.i & 0x7fffffff) - 1u) < 0x7fffffu;
}

// =====================================================================================
// EA::Audio::EmitterSndPlayer
//   +0x000 vtable,  +0x378/+0x37c resource pointers,  +0x388 mbIsStreamed,
//   +0x38c VoiceContainer,  +0xcf0..0xcf8 resource key,  +0xd08,  +0xd0c,  +0xd14,
//   +0xd18 (double start time),  +0xd24/+0xd25,  +0xd28/+0xd29,  +0xd2a dirty flag,
//   +0xd2c wet level, +0xd30 position, +0xd34, +0xd38..0xd50, +0xd54 seek time,
//   +0xd58 sample length, +0xd5c codec, +0xd60..0xd74 plugins, +0xd80 system,
//   +0xd84 flags A, +0xd88 flags B, +0xd8c BitGetter, +0xd98..0xdc8 voice desc.
// =====================================================================================
struct EmitterSndPlayer {
    uint8_t m[0xde0];

    __forceinline void** Vt() { return (void**)*(void**)&m[0]; }

    uint32_t SetFlag(uint32_t mask, char flag);            // 0xa10fe0
    EmitterSndPlayer* q11350();                            // 0xa11350

    bool Start(double t);                                  // 0xa114a0
    bool SetProperty(uint32_t key, float value, bool force);   // 0xa116f0
    bool GetProperty(uint32_t key, float* value);          // 0xa11a60
    void UpdateParameters(float f, bool force);            // 0xa11f50
    bool ParseResource();                                  // 0xa12120
};

// Second (non-polymorphic) base subobject of EmitterSndPlayer, living at +4.
struct EmitterSndPlayer2 {
    uint8_t m[0xde0];

    void Tick(int unused, float v);                        // 0xa11e10
};

// guard used by GetProperty.  The object is empty (no stack storage); its address is
// irrelevant -- q11350 only touches the global singleton -- so locking is expressed as
// a member call reinterpret_cast'ing 'this' back to EmitterSndPlayer*.
struct LockGuardQ {
    __forceinline LockGuardQ() { ((EmitterSndPlayer*)this)->q11350(); }
    __forceinline ~LockGuardQ() { if (g_16e61a8) ((SysGlobal*)g_16e61a8)->DoB(); }
};

// @ 0x00A114A0
bool EmitterSndPlayer::Start(double t) {
    void* sys = f_00a206f0_GetSystemAT();
    if (!sys) return false;

    *(uint32_t*)(m + 0xd84) &= ~0x80;
    bool wasSet = (*(uint32_t*)(m + 0xd84) & 0x20) == 0x20;
    if (wasSet) {
        LockGuard guard;
        ((PlugIn*)*(void**)(m + 0xd6c))->Send(1, 0);
    }

    *(double*)(m + 0xd18) = t;
    if (!(*(uint32_t*)(m + 0xd84) & 2)) {
        ((void(__thiscall*)(void*, void*))((void**)*(void**)sys)[0x70 / 4])(sys, m + 4);
        *(uint32_t*)(m + 0xd84) |= 2;
    }

    if (*(char*)(m + 0x388)) {
        struct Key3 { uint32_t a, b, c; };
        Key3 key = *(Key3*)(m + 0xcf0);
        key.b = 0x1eef63a;
        uint32_t n = 0x32;
        EA::Audio::ResourceDeviceDriver::KeyToText((uint8_t*)&key, (char*)(m + 0xdcc), &n);
    }

    *(float*)(m + 0xdc0) = 0.0f;
    *(uint32_t*)(m + 0xdb4) = *(uint32_t*)(m + 0xdc8);
    *(void**)(m + 0xdb0) = *(char*)(m + 0x388) ? (void*)(m + 0xdcc) : (void*)0;
    *(double*)(m + 0xd98) = *(double*)(m + 0xd18);
    *(double*)(m + 0xda0) = 0.0;
    *(uint32_t*)(m + 0xdbc) = *(uint32_t*)(m + 0xd14);
    *(double*)(m + 0xda8) = (double)*(float*)(m + 0xd5c);
    {
        uint8_t* p = *(uint8_t**)(m + 0x37c);
        *(void**)(m + 0xdb8) = p ? *(void**)(p + 0x14) : (void*)0;
    }

    if (!wasSet) {
        *(uint32_t*)(m + 0xd84) |= 0x20;
        ((EA::Audio::VoiceContainer*)(m + 0x38c))->CommitBoundProperties();
        ((void(__thiscall*)(void*, float, int))Vt()[0x70 / 4])(this, 0.0f, 1);
        ((void(__thiscall*)(void*, int, int, int, int, int))((void**)*(void**)sys)[0x128 / 4])(
            sys, 0x617208b, *(int*)(m + 0xd0c), *(int*)(m + 0xcf0), 0, 0);
        ((EA::Audio::VoiceContainer*)(m + 0x38c))->Connect();
    }

    ((void(__thiscall*)(void*))Vt()[0])(this);

    {
        LockGuard guard;
        ((PlugIn*)*(void**)(m + 0xd6c))->Send(5, m + 0xd98);
    }

    *(char*)(m + 0xd2a) = 0;
    return true;
}

// @ 0x00A116F0
bool EmitterSndPlayer::SetProperty(uint32_t key, float value, bool force) {
    if (!(IsZeroOrNormal(value) || IsDenormal(value))) return false;

    {
        LockGuard guard;
        switch (key) {
        case 0x3593710u:                                    // effective gain
            *(uint32_t*)(m + 0xd88) |= 0x20;
            *(float*)(m + 0xd4c) = value;
            if (!force) ((void(__thiscall*)(void*, void*))Vt()[0x68 / 4])(this, m + 0xd38);
            break;
        case 0x2406a047u:                                   // max distance
            *(uint32_t*)(m + 0xd88) |= 0x40;
            *(float*)(m + 0xd44) = value;
            if (!force) ((void(__thiscall*)(void*, void*))Vt()[0x68 / 4])(this, m + 0xd38);
            break;
        case 0x50c5d65u:                                    // min distance
            *(uint32_t*)(m + 0xd84) |= 0x40;
            *(float*)(m + 0xd40) = value;
            if (!force) ((void(__thiscall*)(void*, void*))Vt()[0x68 / 4])(this, m + 0xd38);
            break;
        case 0x50c5d66u:                                    // gain
            *(uint32_t*)(m + 0xd84) |= 0x40;
            *(float*)(m + 0xd3c) = value;
            if (!force) ((void(__thiscall*)(void*, void*))Vt()[0x68 / 4])(this, m + 0xd38);
            break;
        case 0x50c5d67u:                                    // rolloff
            *(uint32_t*)(m + 0xd84) |= 0x40;
            *(float*)(m + 0xd38) = value;
            if (!force) ((void(__thiscall*)(void*, void*))Vt()[0x68 / 4])(this, m + 0xd38);
            break;
        case 0xf616b72u:                                    // gain attenuation
            *(uint32_t*)(m + 0xd88) |= 0x10;
            *(float*)(m + 0xd48) = value;
            if (!force) ((void(__thiscall*)(void*, void*))Vt()[0x68 / 4])(this, m + 0xd38);
            break;
        case 0x12d2a4d4u:                                   // loop flag
            SetFlag(4, value != 0.0f);
            break;
        case 0x14f9bdf6u:                                   // codec
            *(float*)(m + 0xd5c) = value;
            break;
        case 0x25df0108u:                                   // position
            *(uint32_t*)(m + 0xd88) |= 1;
            *(float*)(m + 0xd30) = value;
            if (!force) ((void(__thiscall*)(void*, float))Vt()[0x64 / 4])(this, value);
            break;
        case 0x49eb68dbu:                                   // gain * position
            *(uint32_t*)(m + 0xd88) |= 0x100;
            *(float*)(m + 0xd34) = value;
            if (!force)
                ((EA::Audio::VoiceContainer*)(m + 0x38c))->SetProperty(
                    0x49eb68dbu, *(float*)(m + 0xd30) * value);
            break;
        case 0x6dd08218u:                                   // (no-op)
            break;
        case 0x6df5822du:                                   // (int) value
            ((void(__thiscall*)(void*, int))Vt()[0x7c / 4])(this, (int)value);
            break;
        case 0x71bc3009u:                                   // wet level
            *(uint32_t*)(m + 0xd88) |= 4;
            *(float*)(m + 0xd2c) = value;
            if (!force) {
                float x = (*(int*)(m + 0xd24) < 2) ? value
                                                    : *(float*)(m + 0xd58) * value;
                ((void(__thiscall*)(void*, float))Vt()[0x60 / 4])(this, x);
            }
            break;
        case 0x82beafe0u:                                   // sample length
            *(uint32_t*)(m + 0xd88) |= 8;
            *(float*)(m + 0xd58) = value;
            if (!force) ((void(__thiscall*)(void*, float))Vt()[0x6c / 4])(this, value);
            break;
        default:
            return ((EA::Audio::VoiceContainer*)(m + 0x38c))->SetProperty(key, value);
        }
    }
    return true;
}

// @ 0x00A11A60
bool EmitterSndPlayer::GetProperty(uint32_t key, float* value) {
    switch (key) {
    case 0x49eb68dbu: *value = *(float*)(m + 0xd34); return true;
    case 0x3593710u:  *value = *(float*)(m + 0xd4c); return true;
    case 0x50c5d66u:  *value = *(float*)(m + 0xd3c); return true;
    case 0x50c5d65u:  *value = *(float*)(m + 0xd40); return true;
    case 0x50c5d67u:  *value = *(float*)(m + 0xd38); return true;
    case 0xf616b72u:  *value = *(float*)(m + 0xd48); return true;
    case 0x12d2a4d4u: *value = (*(uint32_t*)(m + 0xd84) & 4) ? 1.0f : 0.0f; return true;
    case 0x2406a047u: *value = *(float*)(m + 0xd44); return true;
    case 0x25df0108u: *value = *(float*)(m + 0xd30); return true;
    case 0x8f678117u: *value = *(float*)(m + 0xd68); return true;
    case 0x82beafe0u: *value = *(float*)(m + 0xd58); return true;
    case 0x6dd08218u: *value = (*(uint32_t*)(m + 0xd84) & 8) ? 1.0f : 0.0f; return true;
    case 0x71bc3009u: *value = *(float*)(m + 0xd2c); return true;
    case 0xba03d0cdu: *value = *(float*)(m + 0xd64); return true;
    case 0xc2d1f579u: *value = *(float*)(m + 0xd54); return true;
    case 0xd24d4affu: *value = *(float*)(m + 0xd60); return true;
    case 0x893f8476u:                                   // time-stretch ratio (from plug-in)
        if (*(void**)(m + 0xd6c)) {
            LockGuardQ guard;
            double d;
            ((PlugIn*)*(void**)(m + 0xd6c))->GetParam(1, &d);
            *value = (float)d;
        } else {
            *value = 0.0f;
        }
        return true;
    default:
        return ((EA::Audio::VoiceContainer*)(m + 0x38c))->GetProperty(key, value);
    }
}

// @ 0x00A11E10
void EmitterSndPlayer2::Tick(int, float v) {
    if (*(uint8_t*)(m + 0xd80) & 0x80) {
        ((void(__thiscall*)(void*))((void**)*(void**)(m - 4))[0x74 / 4])(m - 4);
        return;
    }
    bool bStreamedMode = (*(uint8_t*)(*(uint8_t**)(m + 0x388) + 0x47) == 2);
    if (!bStreamedMode) {
        bool nz;
        {
            LockGuard guard;
            float tmp[2];
            tmp[0] = *(float*)(m + 0xdc0);
            ((PlugIn*)*(void**)(m + 0xd68))->Send(2, tmp);
            nz = (tmp[1] != 0.0f);
        }
        if (!nz) {
            if (*(char*)(m + 0xd24) == 0 || *(char*)(m + 0xd25) != 0)
                ((void(__thiscall*)(void*, float, int))((void**)*(void**)(m - 4))[0x70 / 4])(
                    m - 4, v, 0);
            return;
        }
    }
    void* sys = f_00a206f0_GetSystemAT();
    ((void(__thiscall*)(void*, int, int, int, int, int))((void**)*(void**)sys)[0x128 / 4])(
        sys, 0x3a0fd6e, *(int*)(m + 0xd08), 0, 0, 0);
    ((void(__thiscall*)(void*))((void**)*(void**)(m - 4))[0x18 / 4])(m - 4);
}

// @ 0x00A11F50
void EmitterSndPlayer::UpdateParameters(float, bool force) {
    if (!(*(uint32_t*)(m + 0xd84) & 0x20)) return;

    LockGuard guard;

    if (*(char*)(m + 0xd29)) {
        void* p = *(void**)(m + 0xd80);
        *(char*)(m + 0xd29) = 0;
        if (p) {
            float x = *(char*)(m + 0xd28) ? 1.0f : 0.0f;
            ((RwSystem*)p)->IsCommandComplete(0, x);
        }
    }

    if ((*(uint32_t*)(m + 0xd84) & 4) && (force || (*(uint32_t*)(m + 0xd84) & 0x40)))
        ((void(__thiscall*)(void*, void*))Vt()[0x68 / 4])(this, m + 0xd38);

    if ((*(uint32_t*)(m + 0xd88) & 0x100) || (*(uint32_t*)(m + 0xd88) & 1)) {
        *(volatile uint32_t*)(m + 0xd88) &= ~0x100;
        ((EA::Audio::VoiceContainer*)(m + 0x38c))->SetProperty(
            0x49eb68dbu, *(float*)(m + 0xd34) * *(float*)(m + 0xd30));
    }

    if (force || (*(uint32_t*)(m + 0xd88) & 0x81)) {
        if (*(uint32_t*)(m + 0xd84) & 0x100)
            *(float*)(m + 0xd54) = *(float*)(m + 0xd50) * *(float*)(m + 0xd30);
        else
            *(float*)(m + 0xd54) = *(float*)(m + 0xd30);
        ((void(__thiscall*)(void*, float))Vt()[0x64 / 4])(this, *(float*)(m + 0xd54));
    }

    if (force || (*(uint32_t*)(m + 0xd88) & 0xc)) {
        float x = (*(int*)(m + 0xd24) < 2) ? *(float*)(m + 0xd2c)
                                            : *(float*)(m + 0xd58) * *(float*)(m + 0xd2c);
        ((void(__thiscall*)(void*, float))Vt()[0x60 / 4])(this, x);
    }

    if (force || (*(uint32_t*)(m + 0xd88) & 8))
        ((void(__thiscall*)(void*, float))Vt()[0x6c / 4])(this, *(float*)(m + 0xd58));
}

// @ 0x00A12120
bool EmitterSndPlayer::ParseResource() {
    if (!*(void**)(m + 0x378)) return false;

    uint8_t* buf = *(uint8_t**)((uint8_t*)*(void**)(m + 0x378) + 0x14);
    BitGetter* bg = (BitGetter*)(m + 0xd8c);

    *(uint8_t**)(m + 0xdc8) = buf;
    bg->mpBitBuffer = buf;
    bg->mBitPosition = 0;

    bg->GetBits(4);
    *(float*)(m + 0xd64) = (float)(unsigned char)bg->GetBits(4);
    *(uint32_t*)(m + 0xd10) = (unsigned char)bg->GetBits(6) + 1;

    int sampleLen = (int)bg->GetBits(0x12);
    uint32_t x = bg->GetBits(2);
    *(float*)(m + 0xd68) = (float)x;

    if (bg->GetBits(1)) *(uint32_t*)(m + 0xd84) |= 8;
    else                *(uint32_t*)(m + 0xd84) &= ~8;

    *(float*)(m + 0xd60) = (float)((int)bg->GetBits(0x1d) / sampleLen);

    if (*(float*)(m + 0xd68) == 0.0f || *(char*)(m + 0x388)) {
        if (*(void**)(m + 0x378)) {
            void* sys = f_00a206f0_GetSystemAT();
            ((void(__thiscall*)(void*, void*))((void**)*(void**)sys)[0x198 / 4])(
                sys, *(void**)(m + 0x378));
        }
        if (*(void**)(m + 0x37c)) {
            void* sys = f_00a206f0_GetSystemAT();
            ((void(__thiscall*)(void*, void*))((void**)*(void**)sys)[0x198 / 4])(
                sys, *(void**)(m + 0x37c));
        }
        *(char*)(m + 0xd2a) = 1;
        return true;
    }

    ((void(__thiscall*)(void*))Vt()[0x54 / 4])(this);
    return false;
}
