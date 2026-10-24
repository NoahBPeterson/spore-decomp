// src/game/SPAudio/AudioEmitterSndPlayer.cpp -- migrated from slice(s) s00a102e0 by tools/migrate/rewrite.py
// Object file: SPAudio/AudioEmitterSndPlayer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/ResponseCurve.h"
#include "EA/Audio/VoiceContainer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) char* __cdecl strncpy(char*, const char*, unsigned);
extern float g_1473c70;
extern float g_1471064;
extern float g_1470f1c;
extern float g_1485720;
extern void* g_16e61a8;

// ---- items of slice s00a102e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) char* __cdecl strncpy(char*, const char*, unsigned);
void* __cdecl f_00a206f0_GetSystemAT();
struct ResponseCurve {
    void InitFromConfiguration(void*, unsigned);
    void ApplySetting(unsigned, int);
};
struct VoiceContainer {
    void SetValue(int);
    void Reconnect();
};
struct RwSystem {
    void IsCommandComplete(int, float);
};
struct SysGlobal {
    bool Check(void*);
    void DoA();
    void DoB();
};
extern float g_1473c70;
extern float g_1471064;
extern float g_1470f1c;
extern float g_1485720;
extern void* g_16e61a8;
struct EmitterSndPlayer {
    unsigned char m[0xdd0];

    __forceinline void** Vt() { return (void**)*(void**)&m[0]; }

    uint32_t SetFlag(uint32_t mask, char flag);  // 0xa10fe0
    bool     Init();                             // 0xa11010
    bool     q11050();                           // 0xa11050
    bool     q11080(char);                       // 0xa11080
    void     q110c0(const uint32_t*);            // 0xa110c0
    bool     SetData(uint32_t, uint32_t, uint32_t); // 0xa11100
    void     Tick();                             // 0xa11190
    bool     FinalStop(float);                   // 0xa111c0
    bool     q11210(float);                      // 0xa11210
    bool     q11270(float);                      // 0xa11270
    void     q112c0();                           // 0xa112c0
    EmitterSndPlayer* q11350();                  // 0xa11350
    void     q11370();                           // 0xa11370
    bool     Shutdown();                         // 0xa11380
    bool     Create();                           // 0xa113c0
};
// ---- items of slice s00a102e0 end

// @ 0x00a10f70
namespace EA {
namespace Audio
{
class ResourceDeviceDriver { public:
    static bool KeyToText(uint8_t* key, char* text, uint32_t* size);
};
bool ResourceDeviceDriver::KeyToText(uint8_t* key, char* text, uint32_t* size) {
    int n = 12;
    if (*size < 0x20) {
        *size = 0x20;
        return false;
    }
    strncpy(text, "resman:", 7);
    text += 7;
    do {
        uint8_t b = *key++;
        *text++ = (char)((b & 0xf) + 'A');
        *text++ = (char)((b >> 4) + 'A');
    } while (--n);
    *text = 0;
    *size = 0x20;
    return true;
}
}
}  // namespace EA

// @ 0x00a10fe0
uint32_t EmitterSndPlayer::SetFlag(uint32_t mask, char flag)
{
    uint32_t* p = (uint32_t*)(m + 0xd84);
    if (flag) *p |= mask;
    else      *p &= ~mask;
    return *p;
}

// @ 0x00a11010
bool EmitterSndPlayer::Init()
{
    uint32_t* flags = (uint32_t*)(m + 0xd84);
    if (*flags & 1) return false;
    *flags |= 1;
    void* sys = f_00a206f0_GetSystemAT();
    ((void(__thiscall*)(void*, void*, int, int))((void**)*(void**)sys)[0x184 / 4])(sys, m + 0xd24, 0, 0);
    return true;
}

// @ 0x00a11050
bool EmitterSndPlayer::q11050()
{
    if (!(*(uint32_t*)(m + 0xd84) & 0x10)) return false;
    ((void(__thiscall*)(void*))Vt()[0x5c / 4])(this);
    uint32_t f = *(uint32_t*)(m + 0xd84);
    f = (f & 0xffffffdf) | 0x80;
    *(uint32_t*)(m + 0xd84) = f;
    return true;
}

// @ 0x00a11080
bool EmitterSndPlayer::q11080(char v)
{
    if (*(char*)(m + 0xd28) != v) {
        *(char*)(m + 0xd29) = 1;
        *(char*)(m + 0xd28) = v;
    }
    return true;
}

// @ 0x00a110c0
void EmitterSndPlayer::q110c0(const uint32_t* p)
{
    *(uint32_t*)(m + 0xcf0) = p[0];
    *(uint32_t*)(m + 0xcf4) = p[1];
    *(uint32_t*)(m + 0xcf8) = p[2];
    *(uint32_t*)(m + 0xcf4) = 0x1a527db;
    *(char*)(m + 0xd2a) = 0;
}

// @ 0x00a11100
bool EmitterSndPlayer::SetData(uint32_t id, uint32_t value, uint32_t)
{
    if (id != 0x2fe09c83) {
        if (id == 0x6e3d22e0) {
            ((ResponseCurve*)(m + 0x10))->ApplySetting(value, 0);
        }
        return true;
    }
    void* sys = f_00a206f0_GetSystemAT();
    int r = ((int(__thiscall*)(void*, int))((void**)*(void**)sys)[0xf4 / 4])(sys, (int)value);
    ((VoiceContainer*)(m + 0x38c))->SetValue(r);
    ((VoiceContainer*)(m + 0x38c))->Reconnect();
    return true;
}

// @ 0x00a11190
void EmitterSndPlayer::Tick()
{
    void* sys = f_00a206f0_GetSystemAT();
    ((void(__thiscall*)(void*, int, int, int, int, int))((void**)*(void**)sys)[0x128 / 4])(
        sys, 0x3a0fd6e, *(int*)(m + 0xd0c), 0, 0, 0);
    ((void(__thiscall*)(void*))Vt()[0x18 / 4])(this);
}

// @ 0x00a111c0
bool EmitterSndPlayer::FinalStop(float f)
{
    *(uint32_t*)(m + 0xd88) &= ~4;
    if (f < 0.0f || f > g_1473c70) return false;
    void* p = *(void**)(m + 0xd70);
    if (!p) return false;
    ((RwSystem*)p)->IsCommandComplete(0, f);
    return true;
}

// @ 0x00a11210
bool EmitterSndPlayer::q11210(float f)
{
    *(uint32_t*)(m + 0xd88) &= ~8;
    if (g_1471064 > f || f > g_1470f1c) return false;
    void* p = *(void**)(m + 0xd78);
    if (!p) return false;
    if (*(int*)(m + 0xd24) < 2) f = g_1485720;
    ((RwSystem*)p)->IsCommandComplete(0, f);
    return true;
}

// @ 0x00a11270
bool EmitterSndPlayer::q11270(float f)
{
    *(uint32_t*)(m + 0xd88) &= ~1;
    if (f < 0.0f || f > g_1485720) return false;
    void* p = *(void**)(m + 0xd74);
    if (!p) return false;
    ((RwSystem*)p)->IsCommandComplete(0, f);
    return true;
}

// @ 0x00a112c0
void EmitterSndPlayer::q112c0()
{
    if (!g_16e61a8) return;
    if (!((SysGlobal*)g_16e61a8)->Check(*(void**)(m + 0xcec))) return;
    if (*(uint32_t*)(m + 0xd84) & 2) {
        *(uint32_t*)(m + 0xd84) &= ~2;
        void* arg = m + 4;
        void* sys = f_00a206f0_GetSystemAT();
        ((void(__thiscall*)(void*, void*))((void**)*(void**)sys)[0x74 / 4])(sys, arg);
    }
    ((void(__thiscall*)(void*))Vt()[4 / 4])(this);
}

// @ 0x00a11310
void f_00a11310(const void* src, const void* end, void* dst)
{
    if (src == end) return;
    do {
        if (dst) {
            ((uint32_t*)dst)[0] = ((const uint32_t*)src)[0];
            ((uint32_t*)dst)[1] = ((const uint32_t*)src)[1];
            ((uint32_t*)dst)[2] = ((const uint32_t*)src)[2];
        }
        src = (const char*)src + 12;
        dst = (char*)dst + 12;
    } while (src != end);
}

// @ 0x00a11350
EmitterSndPlayer* EmitterSndPlayer::q11350()
{
    if (g_16e61a8) ((SysGlobal*)g_16e61a8)->DoA();
    return this;
}

// @ 0x00a11370
void EmitterSndPlayer::q11370()
{
    if (g_16e61a8) ((SysGlobal*)g_16e61a8)->DoB();
}

// @ 0x00a11380
bool EmitterSndPlayer::Shutdown()
{
    void* z = 0;
    if (*(uint32_t*)(m + 0xd84) & 1) {
        ((void(__thiscall*)(void*))Vt()[0x18 / 4])(this);
        *(uint32_t*)(m + 0xd84) &= ~1;
    }
    void* p = *(void**)(m + 0x378);
    if (p != z) {
        *(void**)(m + 0x378) = z;
        ((void(__thiscall*)(void*))((void**)*(void**)p)[4 / 4])(p);
    }
    *(void**)(m + 0xdc8) = z;
    return true;
}

// @ 0x00a113c0
bool EmitterSndPlayer::Create()
{
    if (*(uint32_t*)(m + 0xd84) & 0x20) return false;
    if (*(void**)(m + 0x374)) {
        void* cfg = *(void**)(m + 0x374);
        if (((bool(__thiscall*)(void*, int))((void**)*(void**)cfg)[0x18 / 4])(cfg, 0x79da6d74)) {
            uint32_t local[3] = {0, 0, 0};
            void* c = *(void**)(m + 0x374);
            ((void(__thiscall*)(void*, int, void*))((void**)*(void**)c)[0x34 / 4])(c, 0x79da6d74, local);
            *(uint32_t*)(m + 0xd14) = local[0];
        }
        void* c1 = *(void**)(m + 0x374);
        ((ResponseCurve*)(m + 0x10))->InitFromConfiguration(c1, 0x1e4db1eb);
        void* c2 = *(void**)(m + 0x374);
        ((void(__thiscall*)(void*, int, void*))((void**)*(void**)c2)[0x2c / 4])(c2, 0xed1f36d5, m + 0xd20);
        void* c3 = *(void**)(m + 0x374);
        uint32_t r;
        if (((bool(__thiscall*)(void*, int, void*))((void**)*(void**)c3)[0x24 / 4])(c3, 0x12d2a4d4, &r)) {
            SetFlag(4, (char)r);
        }
    }
    return ((((int(__thiscall*)(void*))Vt()[0x4c / 4])(this)) & 0xff) != 0;
}
