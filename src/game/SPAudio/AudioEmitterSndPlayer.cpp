template<class HsT> __forceinline HsT hs_cp(HsT x) { HsT r = x; return r; }
// src/game/SPAudio/AudioEmitterSndPlayer.cpp -- migrated from slice(s) s00a12f90, s00a12260, s00a114a0, s00a102e0 by tools/migrate/rewrite.py
// Object file: SPAudio/AudioEmitterSndPlayer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/ResponseCurve.h"
#include "EA/Audio/VoiceContainer.h"
#include "rw/audio/core/PlugIn.h"
#include "rw/audio/core/System.h"
#include <math.h>
#include "EA/Audio/Group.h"
#include "EA/Audio/ResourceVoiceTemplate.h"

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
struct ResponseCurve_s00a1_02e0 {
    void InitFromConfiguration(void*, unsigned);  // 0x00a1a9d0 (ResponseCurve::InitFromConfiguration)
    void ApplySetting(unsigned, int);
};
struct VoiceContainer_s00a1_02e0 {
    void SetValue(int);
    void Reconnect();  // 0x00a34c90 (VoiceContainer::Reconnect)
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
struct BitGetter {
    uint8_t* mpBitBuffer;   // 0x00
    uint32_t mBitPosition;  // 0x04
    uint32_t GetBits(uint32_t n);
};
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

// ---- items of slice s00a114a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PlugIn {
    void Send(int, void*);                   // 0x112ccc0 (vtable slot 1 dispatch)
    void GetParam(int, double*);             // 0x112cca0
};
namespace EA {
namespace Audio {
class ResourceDeviceDriver_s00a1_14a0 { public:
    static bool KeyToText(uint8_t* key, char* text, uint32_t* size);   // 0xa10f70
};
}
}
namespace EA {
namespace Audio {
struct VoiceContainer_s00a1_14a0 {
    void CommitBoundProperties();            // 0xa33dc0
    bool Connect();                          // 0xa34bf0
    bool SetProperty(uint32_t, float);       // 0xa33ee0
    bool GetProperty(uint32_t, float*);      // 0xa33fd0
};
}
}
struct LockGuard {
    LockGuard()  { if (g_16e61a8) ((SysGlobal*)g_16e61a8)->DoA(); }
    ~LockGuard() { if (g_16e61a8) ((SysGlobal*)g_16e61a8)->DoB(); }
};
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
struct EmitterSndPlayer_s00a1_14a0 {
    uint8_t m[0xde0];

    __forceinline void** Vt() { return (void**)*(void**)&m[0]; }

    uint32_t SetFlag(uint32_t mask, char flag);            // 0xa10fe0
    EmitterSndPlayer_s00a1_14a0* q11350();                            // 0xa11350

    bool Start(double t);                                  // 0xa114a0
    bool SetProperty(uint32_t key, float value, bool force);   // 0xa116f0
    bool GetProperty(uint32_t key, float* value);          // 0xa11a60
    void UpdateParameters(float f, bool force);            // 0xa11f50
    bool ParseResource();                                  // 0xa12120
};
struct EmitterSndPlayer2 {
    uint8_t m[0xde0];

    void Tick(int unused, float v);                        // 0xa11e10
};
struct LockGuardQ {
    __forceinline LockGuardQ() { ((EmitterSndPlayer_s00a1_14a0*)this)->q11350(); }
    __forceinline ~LockGuardQ() { if (g_16e61a8) ((SysGlobal*)g_16e61a8)->DoB(); }
};
// ---- items of slice s00a114a0 end

// ---- items of slice s00a12260 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(sqrt, atan2)
static __forceinline float Sqrt(float x) { return (float)sqrt((double)x); }
static __forceinline float Atan2(float y, float x) { return (float)atan2((double)y, (double)x); }
int* FUN_00a11310(int* first, int* last, int* dest);            // 12-byte element copy
void FUN_00f47380(void* p);                      // operator delete
struct SysGlobal_s00a1_2260 {
    void Lock();                                 // 0x112c600
    void Unlock();                               // 0x112c620
    bool Check(const void* id);                  // 0x112c640
    void Apply(const void* key);                 // 0xa28a20
    unsigned char pad[0xe0];
    void* fE0;                                   // +0xe0 (current voice/play handle)
};
struct PlugIn_s00a1_2260 {
    void Send(int, void*);                       // 0x112ccc0
};
struct VoiceContainer {
    void Ctor();                                 // 0xa34760
    void DtorTail();                             // 0xa34620
    bool Disconnect();                           // 0xa34890
    void Destroy();                              // 0xa343e0
    void MaskPluginBindings(const uint32_t* props, int count);   // 0xa340b0
    bool Reconnect();                            // 0xa34c90
    void CommitBoundProperties();                // 0xa33dc0
    bool SetProperty(uint32_t, float);           // 0xa33ee0
};
struct ResponseCurve {
    void Ctor();                                 // 0xa1aa50
};
struct LockGuard_s00a1_2260 {
    LockGuard_s00a1_2260()  { if (g_16e61a8) ((SysGlobal_s00a1_2260*)g_16e61a8)->Lock(); }
    ~LockGuard_s00a1_2260() { if (g_16e61a8) ((SysGlobal_s00a1_2260*)g_16e61a8)->Unlock(); }
};
struct EmitterSndPlayer_s00a1_2260 {
    uint8_t m[0xde0];

    __forceinline void** Vt() { return (void**)*(void**)&m[0]; }

    bool q12260();                               // 0xa12260
    bool DestroyVoice();                         // 0xa124a0
    void UpdatePerformanceLevel(int level);      // 0xa12570
    bool Load();                                 // 0xa12640
    bool CommitPosition(void* pos);              // 0xa12770
    void q12ad0();                               // 0xa12ad0
    EmitterSndPlayer_s00a1_2260* ctor();                    // 0xa12d80
};
static __forceinline void** VtOf(void* p) { return *(void***)p; }
struct Elem12 { uint32_t a, b, c; };
struct Vec12 {
    char* mpBegin;      // +0
    char* mpEnd;        // +4
    char* mpCapacity;   // +8

    void DoInsertValue(char* pos, Elem12* value);    // 0xa12c90
};
struct AttenHelper {
    float q12c20(float a, float b, float c, float d);   // 0xa12c20
};
// ---- items of slice s00a12260 end

// ---- items of slice s00a12f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* DAT_016e61a8;                             // 0x016e61a8 System lock
typedef unsigned char  u8;
typedef unsigned int   u32;
void* __cdecl FUN_00a206f0();                          // 0x00a206f0 EA::Audio::GetSystemAT
void* __cdecl FUN_00a34cb0(void* a, void* b, void* c, void* d, void* e); // AddPropertyBinding
void* __cdecl FUN_00b85500(void* a, void* b);          // 0x00b85500 vector reset
void* __cdecl eastl_vec_erase(void* self, void* first, void* last);      // 0x009e0480
void* __cdecl eastl_vec_insert(void* pos, void* last, void* value);      // 0x011e0744
void* __cdecl eastl_push_4(void* pos, void* value);    // 0x00899480
void* __cdecl eastl_push_c(void* pos, void* value);    // 0x0060a600
void* __cdecl FUN_0112ce00();                          // 0x0112ce00 VoiceList::getOrCreate
void* __cdecl FUN_0112cd30(u32 id);                    // 0x0112cd30 NodeList::find
void  __cdecl FUN_0112c600();                          // 0x0112c600 System::Lock
void  __cdecl FUN_0112c620();                          // 0x0112c620 System::Unlock
void  __cdecl FUN_00a34d70(void* self, void* v);    // 0x00a34d70
void  __cdecl FUN_00a11350(void* self);             // 0x00a11350
bool  __cdecl VoiceContainer_Create(void* self, int flag); // 0x00a342c0
void* __cdecl FindPlugin(void* self, u32 id);       // 0x00a34230
namespace EA {
namespace Audio {
struct ResourceVoiceTemplate_s00a1_2f90 {
    void* mVtbl;             // +0x00
    char  pad04[0x10];
    void* mPluginBegin;      // +0x14
    void* mPluginEnd;        // +0x18
    char  pad1c[0x194 - 0x1c];
    void* mBindBegin;        // +0x194
    void* mBindEnd;          // +0x198

    bool ConstructVoice(int mode, void* voice);   // 0x00a12f90
};
}
}
namespace EA {
namespace Audio {
struct EmitterSndPlayer_s00a1_2f90 {
    char  pad000[0x374];
    void* mName;             // +0x374
    char  pad378[0x38c - 0x378];
    char  mVoice[0xd10 - 0x38c];   // +0x38c voice-data sub-object
    int   mStartTime;        // +0xd10
    char  padD14[0xd24 - 0xd14];
    int   mPitch;            // +0xd24
    char  padD28[0xd6c - 0xd28];
    void* mpPluginA;         // +0xd6c
    void* mpPluginB;         // +0xd70
    void* mpPluginC;         // +0xd74
    void* mpPluginD;         // +0xd78
    void* mpPluginE;         // +0xd80
    u32   mFlags;            // +0xd84

    bool CreateVoice();      // 0x00a13300
};
}
}
// ---- items of slice s00a12f90 end

// @ 0x00a10ef0
uint32_t BitGetter::GetBits(uint32_t n)
{
    uint32_t result = 0;
    if (n != 0) {
        do {
            uint32_t pos = mBitPosition;
            uint32_t avail = 8 - (pos & 7);
            uint32_t take = avail > n ? n : avail;
            uint8_t  b = mpBitBuffer[pos >> 3];
            result = ((b >> (8 - (pos & 7) - take)) & ((1u << take) - 1)) | (result << take);
            mBitPosition = pos + take;
            n -= take;
        } while (n != 0);
    }
    return result;
}

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
            ((ResponseCurve_s00a1_02e0*)(m + 0x10))->ApplySetting(value, 0);
        }
        return true;
    }
    void* sys = f_00a206f0_GetSystemAT();
    int r = ((int(__thiscall*)(void*, int))((void**)*(void**)sys)[0xf4 / 4])(sys, (int)value);
    ((VoiceContainer_s00a1_02e0*)(m + 0x38c))->SetValue(r);
    ((VoiceContainer_s00a1_02e0*)(m + 0x38c))->Reconnect();
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
        ((ResponseCurve_s00a1_02e0*)(m + 0x10))->InitFromConfiguration(c1, 0x1e4db1eb);
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

// @ 0x00a114a0
bool EmitterSndPlayer_s00a1_14a0::Start(double t)
{
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
        EA::Audio::ResourceDeviceDriver_s00a1_14a0::KeyToText((uint8_t*)&key, (char*)(m + 0xdcc), &n);
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
        ((EA::Audio::VoiceContainer_s00a1_14a0*)(m + 0x38c))->CommitBoundProperties();
        ((void(__thiscall*)(void*, float, int))Vt()[0x70 / 4])(this, 0.0f, 1);
        ((void(__thiscall*)(void*, int, int, int, int, int))((void**)*(void**)sys)[0x128 / 4])(
            sys, 0x617208b, *(int*)(m + 0xd0c), *(int*)(m + 0xcf0), 0, 0);
        ((EA::Audio::VoiceContainer_s00a1_14a0*)(m + 0x38c))->Connect();
    }

    ((void(__thiscall*)(void*))Vt()[0])(this);

    {
        LockGuard guard;
        ((PlugIn*)*(void**)(m + 0xd6c))->Send(5, m + 0xd98);
    }

    *(char*)(m + 0xd2a) = 0;
    return true;
}

// @ 0x00a116f0
bool EmitterSndPlayer_s00a1_14a0::SetProperty(uint32_t key, float value, bool force)
{
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
                ((EA::Audio::VoiceContainer_s00a1_14a0*)(m + 0x38c))->SetProperty(
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
            return ((EA::Audio::VoiceContainer_s00a1_14a0*)(m + 0x38c))->SetProperty(key, value);
        }
    }
    return true;
}

// @ 0x00a11a60
bool EmitterSndPlayer_s00a1_14a0::GetProperty(uint32_t key, float* value)
{
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
        return ((EA::Audio::VoiceContainer_s00a1_14a0*)(m + 0x38c))->GetProperty(key, value);
    }
}

// @ 0x00a11e10
void EmitterSndPlayer2::Tick(int, float v)
{
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

// @ 0x00a11f50
void EmitterSndPlayer_s00a1_14a0::UpdateParameters(float, bool force)
{
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
        ((EA::Audio::VoiceContainer_s00a1_14a0*)(m + 0x38c))->SetProperty(
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

// @ 0x00a12120
bool EmitterSndPlayer_s00a1_14a0::ParseResource()
{
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

// @ 0x00a12260
bool EmitterSndPlayer_s00a1_2260::q12260()
{
    if (*(char*)(m + 0xd2a) != 0) return true;   // already primed

    uint8_t* res = *(uint8_t**)(m + 0x378);
    if (res != 0 &&
        (*(uint32_t*)(res + 8)  != *(uint32_t*)(m + 0xcf0) ||
         *(uint32_t*)(res + 0xc)  != *(uint32_t*)(m + 0xcf4) ||
         *(uint32_t*)(res + 0x10) != *(uint32_t*)(m + 0xcf8))) {
        // loaded resource does not match the requested key
        if (*(uint32_t*)(m + 0xd84) & 0x20u) {
            *(uint32_t*)(m + 0xd84) &= ~0xa0u;
            {
                LockGuard_s00a1_2260 guard;
                ((PlugIn_s00a1_2260*)*(void**)(m + 0xd6c))->Send(1, 0);
                *(void**)(m + 0xcec) = ((SysGlobal_s00a1_2260*)g_16e61a8)->fE0;
            }
        } else if (((SysGlobal_s00a1_2260*)g_16e61a8)->Check(*(void**)(m + 0xcec))) {
            if (!((bool(__thiscall*)(void*))Vt()[0x4c / 4])(this))
                ((void(__thiscall*)(void*))Vt()[0x54 / 4])(this);
        }
        return false;
    }

    void** p378 = (void**)(m + 0x378);
    bool ok = true;

    if (*(void**)(m + 0x380) != 0) {
        if (!((bool(__thiscall*)(void*))VtOf(*(void**)(m + 0x380))[0x10 / 4])(
                *(void**)(m + 0x380))) {
            ok = false;
        } else {
            void* obj380 = *(void**)(m + 0x380);
            void* r378 = *p378;
            if (r378 != 0) {
                *p378 = 0;
                ((void(__thiscall*)(void*))VtOf(r378)[0x4 / 4])(r378);
            }
            if (!((bool(__thiscall*)(void*, void*))VtOf(obj380)[0x14 / 4])(obj380, p378))
                goto lab_12467;
            if (*(void**)(m + 0x380) != 0) {
                void* p = *(void**)(m + 0x380);
                *(void**)(m + 0x380) = 0;
                ((void(__thiscall*)(void*))VtOf(p)[0x4 / 4])(p);
            }
        }
    }

    if (*(void**)(m + 0x384) != 0) {
        if (!((bool(__thiscall*)(void*))VtOf(*(void**)(m + 0x384))[0x10 / 4])(
                *(void**)(m + 0x384)))
            return false;
        {
            void* obj384 = *(void**)(m + 0x384);
            void** p37c = (void**)(m + 0x37c);
            void* r37c = *p37c;
            if (r37c != 0) {
                *p37c = 0;
                ((void(__thiscall*)(void*))VtOf(r37c)[0x4 / 4])(r37c);
            }
            if (!((bool(__thiscall*)(void*, void*))VtOf(obj384)[0x14 / 4])(obj384, p37c))
                goto lab_12467;
        }
        if (*(void**)(m + 0x384) != 0) {
            void* p = *(void**)(m + 0x384);
            *(void**)(m + 0x384) = 0;
            ((void(__thiscall*)(void*))VtOf(p)[0x4 / 4])(p);
        }
    }

    if (!ok) return false;
    if (!((bool(__thiscall*)(void*))Vt()[0x50 / 4])(this)) return false;
    if ((*(uint32_t*)(m + 0xd84) & 0x10u) == 0) {
        if (((bool(__thiscall*)(void*))Vt()[0x58 / 4])(this)) return true;
        goto lab_12467;
    }
    return true;

lab_12467:
    ((void(__thiscall*)(void*))Vt()[0x54 / 4])(this);
    return false;
}

// @ 0x00a124a0
bool EmitterSndPlayer_s00a1_2260::DestroyVoice()
{
    LockGuard_s00a1_2260 guard;

    if (g_16e61a8)
        *(void**)(m + 0xcec) = ((SysGlobal_s00a1_2260*)g_16e61a8)->fE0;

    if (*(void**)(m + 0x394) != *(void**)(m + 0x398)) {
        VoiceContainer* vc = (VoiceContainer*)(m + 0x38c);
        vc->Disconnect();
        (*(PlugIn_s00a1_2260**)*(void**)(m + 0x390))->Send(1, 0);
        vc->Destroy();
    }

    *(uint32_t*)(m + 0xd84) &= ~0x10u;
    *(void**)(m + 0xd6c) = 0;
    *(void**)(m + 0xd70) = 0;
    *(void**)(m + 0xd74) = 0;
    *(void**)(m + 0xd78) = 0;
    *(void**)(m + 0xd80) = 0;
    return true;
}

// @ 0x00a12570
void EmitterSndPlayer_s00a1_2260::UpdatePerformanceLevel(int level)
{
    if (*(int*)(m + 0xd24) == level) return;

    void* data = 0;
    int size = 0;

    SysGlobal_s00a1_2260* sys = (SysGlobal_s00a1_2260*)f_00a206f0_GetSystemAT();
    ((void(__thiscall*)(void*, int, void**, int*))VtOf(sys)[0x184 / 4])(sys, 0, &data, &size);

    switch (level) {
    case 1:
        ((void(__thiscall*)(void*, unsigned, int*, void**))VtOf(*(void**)(m + 0x374))[0x48 / 4])(
            *(void**)(m + 0x374), 0xdf59188du, &size, &data);
        break;
    case 2:
        ((void(__thiscall*)(void*, unsigned, int*, void**))VtOf(*(void**)(m + 0x374))[0x48 / 4])(
            *(void**)(m + 0x374), 0xb5760a90u, &size, &data);
        break;
    }

    VoiceContainer* vc = (VoiceContainer*)(m + 0x38c);
    vc->MaskPluginBindings((const uint32_t*)data, size);
    if (*(int*)(m + 0xd24) == 1)
        vc->Reconnect();
    vc->CommitBoundProperties();
    *(int*)(m + 0xd24) = level;
}

// @ 0x00a12640
bool EmitterSndPlayer_s00a1_2260::Load()
{
    *(uint8_t*)(m + 0xd2a) = 0;

    void* sys = f_00a206f0_GetSystemAT();

    if (*(void**)(m + 0x378)) {
        void* p = *(void**)(m + 0x378);
        *(void**)(m + 0x378) = 0;
        ((void(__thiscall*)(void*))VtOf(p)[0x4 / 4])(p);
    }
    if (*(void**)(m + 0x380)) {
        void* p = *(void**)(m + 0x380);
        *(void**)(m + 0x380) = 0;
        ((void(__thiscall*)(void*))VtOf(p)[0x4 / 4])(p);
    }

    if (!((bool(__thiscall*)(void*, void*, void*, void*))VtOf(sys)[0x194 / 4])(
            sys, m + 0xcf0, m + 0x380, m + 0x378))
        return false;

    uint32_t key[3];
    key[1] = *(uint32_t*)(m + 0xcf4);
    key[0] = *(uint32_t*)(m + 0xcf0);
    key[2] = *(uint32_t*)(m + 0xcf8);
    key[1] = 0x1eef63a;
    void* sys2 = f_00a206f0_GetSystemAT();
    bool streamed =
        ((int(__thiscall*)(void*, void*))VtOf(sys2)[0x188 / 4])(sys2, key) != 0;
    *(uint8_t*)(m + 0x388) = streamed;
    if (!streamed) return true;

    {
        ((SysGlobal_s00a1_2260*)f_00a206f0_GetSystemAT())->Apply(key);
        key[1] = 0x42c9cbb;

        void* s4 = f_00a206f0_GetSystemAT();
        if (*(void**)(m + 0x37c)) {
            void* p = *(void**)(m + 0x37c);
            *(void**)(m + 0x37c) = 0;
            ((void(__thiscall*)(void*))VtOf(p)[0x4 / 4])(p);
        }
        if (*(void**)(m + 0x384)) {
            void* p = *(void**)(m + 0x384);
            *(void**)(m + 0x384) = 0;
            ((void(__thiscall*)(void*))VtOf(p)[0x4 / 4])(p);
        }
        ((bool(__thiscall*)(void*, void*, void*, void*))VtOf(s4)[0x194 / 4])(
            s4, key, m + 0x384, m + 0x37c);
    }
    return true;
}

// @ 0x00a12770
bool EmitterSndPlayer_s00a1_2260::CommitPosition(void* posv)
{
    float* pos = (float*)posv;

    const uint32_t keep = ~0x40u;
    *(uint32_t*)(m + 0xd88) &= ~0x30u;
    *(uint32_t*)(m + 0xd88) &= keep;
    *(uint32_t*)(m + 0xd84) &= keep;

    void* sys = f_00a206f0_GetSystemAT();
    if (!sys) return false;

    float lp[3];        // listener position
    float lr[3];        // rotated listener->source offset
    float lm[9];        // listener basis
    float dist;

    ((void(__thiscall*)(void*, int, float*, float*))VtOf(sys)[0x78 / 4])(
        sys, *(int*)(m + 0xd20), lp, lm);

    float dx = pos[0] - lp[0];
    float dy = pos[1] - lp[1];
    float dz = pos[2] - lp[2];

    lr[0] = dz * lm[6] + dy * lm[3] + dx * lm[0];
    lr[1] = dz * lm[7] + dy * lm[4] + dx * lm[1];
    lr[2] = dz * lm[8] + dy * lm[5] + dx * lm[2];

    dist = Sqrt(lr[0] * lr[0] + lr[1] * lr[1] + lr[2] * lr[2]);
    ((void(__thiscall*)(void*, float))Vt()[0x78 / 4])(this, dist);

    if (*(uint32_t*)(m + 0xd84) & 0x100u) {
        dist = ((float(__thiscall*)(void*, float, float, float, float))Vt()[0x40 / 4])(
            this, dist, *(float*)(m + 0xd44), *(float*)(m + 0xd48), *(float*)(m + 0xd4c));
        if (*(float*)(m + 0xd50) == dist)
            *(uint32_t*)(m + 0xd88) &= ~0x80u;
        else
            *(uint32_t*)(m + 0xd88) |= 0x80u;
        *(float*)(m + 0xd50) = dist;
    }

    ((void(__thiscall*)(void*, int, float*, float*))VtOf(sys)[0x78 / 4])(sys, 1, lp, lm);

    dx = pos[0] - lp[0];
    dy = pos[1] - lp[1];
    dz = pos[2] - lp[2];

    lr[0] = dy * lm[3] + dz * lm[6] + dx * lm[0];
    lr[1] = dy * lm[4] + dz * lm[7] + dx * lm[1];
    lr[2] = dy * lm[5] + dz * lm[8] + dx * lm[2];

    dist = Sqrt(lr[0] * lr[0] + lr[1] * lr[1] + lr[2] * lr[2]);

    float angle = Atan2(lr[0], lr[1]);
    if (!(angle >= 0.0f)) angle += *(float*)0x166d884;      // wrap to [0, 2pi)
    ((VoiceContainer*)(m + 0x38c))->SetProperty(0x4a77693au, angle * *(float*)0x1449310);

    float atten = *(float*)(m + 0xd48);
    ((VoiceContainer*)(m + 0x38c))->SetProperty(
        0x6eb7a717u, dist < atten ? dist / atten : 1.0f);

    if (*(int*)(m + 0xd10) > 1) {
        float eff = *(float*)(m + 0xd4c);
        if (atten != eff) {
            float v = eff;
            if (atten > dist) v = atten;
            else if (dist <= eff) v = dist;
            ((VoiceContainer*)(m + 0x38c))->SetProperty(
                0xce78d695u, 1.0f - (v - atten) / (eff - atten));
        }
    }

    return true;
}

// @ 0x00a12ad0
void EmitterSndPlayer_s00a1_2260::q12ad0()
{
    *(void**)(m + 0) = (void*)0x1449360;
    *(void**)(m + 4) = (void*)0x1453464;
    *(void**)(m + 8) = (void*)0x1449358;

    if (*(uint32_t*)(m + 0xd84) & 1u) {
        (*(void(__cdecl**)(void))0x1449378)();
        *(uint32_t*)(m + 0xd84) &= ~1u;
    }

    if (*(void**)(m + 0x378)) {
        void* p = *(void**)(m + 0x378);
        *(void**)(m + 0x378) = 0;
        ((void(__thiscall*)(void*))VtOf(p)[0x4 / 4])(p);
    }

    *(void**)(m + 0xdc8) = 0;

    {
        uint8_t* beg = *(uint8_t**)(m + 0xcfc);
        int32_t n = (int32_t)((uint32_t)(*(uint8_t**)(m + 0xd04) - beg) & 0xfffffffeu);
        if (n > 2 && beg) FUN_00f47380(beg);
    }

    ((VoiceContainer*)(m + 0x38c))->DtorTail();

    if (*(void**)(m + 0x384)) {
        void* p = *(void**)(m + 0x384);
        ((void(__thiscall*)(void*))VtOf(p)[0x4 / 4])(p);
    }
    if (*(void**)(m + 0x380)) {
        void* p = *(void**)(m + 0x380);
        ((void(__thiscall*)(void*))VtOf(p)[0x4 / 4])(p);
    }
    if (*(void**)(m + 0x37c)) {
        void* p = *(void**)(m + 0x37c);
        ((void(__thiscall*)(void*))VtOf(p)[0x4 / 4])(p);
    }
    if (*(void**)(m + 0x378)) {
        void* p = *(void**)(m + 0x378);
        ((void(__thiscall*)(void*))VtOf(p)[0x4 / 4])(p);
    }
    if (*(void**)(m + 0x374)) {
        void* p = *(void**)(m + 0x374);
        ((void(__thiscall*)(void*))VtOf(p)[0x4 / 4])(p);
    }

    {
        void* p = *(void**)(m + 0x10);
        if (p && p != *(void**)(m + 0x20)) FUN_00f47380(p);
    }

    *(void**)(m + 8) = (void*)0x13ef094;
}

// @ 0x00a12c20
float AttenHelper::q12c20(float a, float b, float c, float d)
{
    (void)d;
    if (c > a || b == 0.0f) return 1.0f;
    return 1.0f / ((a / c - 1.0f) * b + 1.0f);
}

// @ 0x00a12c90
void Vec12::DoInsertValue(char* pos, Elem12* value)
{
    char* end = mpEnd;
    if (end != mpCapacity) {
        // in-place insert: shift the tail one slot towards the end
        char* v = (char*)value;
        if (v >= pos && v < end) v += 12;

        if (end) {
            ((uint32_t*)end)[0] = ((uint32_t*)(end - 12))[0];
            ((uint32_t*)end)[1] = ((uint32_t*)(end - 12))[1];
            ((uint32_t*)end)[2] = ((uint32_t*)(end - 12))[2];
        }

        char* dst = mpEnd;
        char* src = mpEnd - 12;
        if (src != pos) {
            do {
                src -= 12;
                dst -= 12;
                ((uint32_t*)dst)[0] = ((uint32_t*)src)[0];
                ((uint32_t*)dst)[1] = ((uint32_t*)src)[1];
                ((uint32_t*)dst)[2] = ((uint32_t*)src)[2];
            } while (src != pos);
        }

        ((uint32_t*)pos)[0] = ((uint32_t*)v)[0];
        ((uint32_t*)pos)[1] = ((uint32_t*)v)[1];
        ((uint32_t*)pos)[2] = ((uint32_t*)v)[2];
        mpEnd += 12;
        return;
    }

    int n = (int)((end - mpBegin) / 12);
    int cap = n * 2;
    if (n == 0) cap = 1;

    char* p = (char*)FUN_00a11310((int*)mpBegin, (int*)pos, 0);
    if (p) {
        ((uint32_t*)p)[0] = value->a;
        ((uint32_t*)p)[1] = value->b;
        ((uint32_t*)p)[2] = value->c;
    }
    char* q = (char*)FUN_00a11310((int*)pos, hs_cp((int*)mpEnd), (int*)(p + 12));
    mpBegin = 0;
    mpEnd = q;
    mpCapacity = (char*)(cap * 12);
}

// @ 0x00a12d80
EmitterSndPlayer_s00a1_2260* EmitterSndPlayer_s00a1_2260::ctor()
{
    *(void**)(m + 0) = (void*)0x1453e60;
    *(void**)(m + 4) = (void*)0x144934c;
    *(void**)(m + 8) = (void*)0x13ef094;
    *(uint32_t*)(m + 0xc) = 0;
    *(void**)(m + 0) = (void*)0x1449360;
    *(void**)(m + 4) = (void*)0x1453464;
    *(void**)(m + 8) = (void*)0x1449358;

    ((ResponseCurve*)(m + 0x10))->Ctor();

    *(void**)(m + 0x374) = 0;
    *(void**)(m + 0x378) = 0;
    *(void**)(m + 0x37c) = 0;
    *(void**)(m + 0x380) = 0;
    *(void**)(m + 0x384) = 0;
    *(uint8_t*)(m + 0x388) = 0;

    ((VoiceContainer*)(m + 0x38c))->Ctor();

    *(void**)(m + 0xcec) = 0;
    *(void**)(m + 0xcf0) = 0;
    *(void**)(m + 0xcf4) = 0;
    *(void**)(m + 0xcf8) = 0;
    *(void**)(m + 0xcfc) = (void*)0x1667bac;
    *(void**)(m + 0xd00) = (void*)0x1667bac;
    *(void**)(m + 0xd04) = (void*)0x1667bae;
    *(double*)(m + 0xd18) = 0.0;
    *(float*)(m + 0xd2c) = 1.0f;
    *(float*)(m + 0xd30) = 1.0f;
    *(void**)(m + 0xd0c) = 0;
    *(uint32_t*)(m + 0xd14) = 0x2ea8fb98;
    *(void**)(m + 0xd20) = 0;
    *(int*)(m + 0xd24) = 2;
    *(uint8_t*)(m + 0xd28) = 0;
    *(uint8_t*)(m + 0xd29) = 0;
    *(uint8_t*)(m + 0xd2a) = 1;
    *(float*)(m + 0xd34) = 0.0f;
    *(float*)(m + 0xd38) = 0.0f;
    *(float*)(m + 0xd3c) = 0.0f;
    *(float*)(m + 0xd40) = 0.0f;
    *(float*)(m + 0xd44) = 1.0f;
    *(float*)(m + 0xd48) = 1.0f;
    *(float*)(m + 0xd50) = 1.0f;
    *(float*)(m + 0xd54) = 1.0f;
    *(float*)(m + 0xd58) = 1.0f;
    *(float*)(m + 0xd4c) = 10.0f;
    *(float*)(m + 0xd5c) = 0.0f;
    *(float*)(m + 0xd60) = -1.0f;
    *(float*)(m + 0xd64) = -1.0f;
    *(float*)(m + 0xd68) = -1.0f;
    *(void**)(m + 0xd6c) = 0;
    *(void**)(m + 0xd70) = 0;
    *(void**)(m + 0xd74) = 0;
    *(void**)(m + 0xd78) = 0;
    *(void**)(m + 0xd7c) = 0;
    *(void**)(m + 0xd80) = 0;
    *(void**)(m + 0xd84) = 0;
    *(void**)(m + 0xd88) = 0;
    *(void**)(m + 0xdc8) = 0;

    return this;
}

// @ 0x00a12f90
namespace EA { namespace Audio {
bool ResourceVoiceTemplate_s00a1_2f90::ConstructVoice(int mode, void* voice)
{
    char* p3 = (char*)voice;

    FUN_00b85500(*(void**)(p3 + 0x184), *(void**)(p3 + 0x188));
    eastl_vec_erase((void*)(p3 + 8), *(void**)(p3 + 8), *(void**)(p3 + 0xc));
    eastl_vec_insert(*(void**)(p3 + 0x8a0), *(void**)(p3 + 0x8a4), 0);
    eastl_vec_insert(*(void**)(p3 + 0x8cc), *(void**)(p3 + 0x8d0), 0);

    if (DAT_016e61a8 != 0)
        FUN_0112c600();                                   // System::Lock

    void* voiceObj = FUN_0112ce00();                      // VoiceList::getOrCreate
    if (voiceObj == 0) {
        if (DAT_016e61a8 != 0)
            FUN_0112c620();                               // System::Unlock
        return false;
    }

    bool one = (mode == 1);
    int n = (int)(((char*)mPluginEnd - (char*)mPluginBegin) / 0xc);
    for (int i = 0; i < n; ++i) {
        u32* plugin = (u32*)((char*)mPluginBegin + i * 0xc);

        if (plugin[0] == 0x53656e30)                      // 'Sen0'
            eastl_push_4(*(void**)(p3 + 0x8a0), (void*)plugin[2]);

        bool skip = false;
        if (plugin[0] == 0x506e3230) {                    // 'Pn20'
            if (one) {
                skip = true;
            } else {
                void* sys = FUN_00a206f0();
                mode = ((int (__thiscall*)(void*))(*(void***)sys)[0xbc / 4])(sys);
            }
        } else if (plugin[0] == 0x506e3231) {             // 'Pn21'
            void* sys = FUN_00a206f0();
            mode = ((int (__thiscall*)(void*))(*(void***)sys)[0xbc / 4])(sys);
        }

        if (skip)
            continue;

        void* node = FUN_0112cd30(plugin[0]);             // NodeList::find
        if (node == 0) {
            if (DAT_016e61a8 != 0)
                FUN_0112c620();
            return false;
        }

        // append a default PlugInConfig to the voice's config vector (stride 0xc)
        void* cfgEnd = *(void**)(p3 + 0xc);
        if (cfgEnd < *(void**)(p3 + 0x10)) {
            *(void**)(p3 + 0xc) = (char*)cfgEnd + 0xc;
            if (cfgEnd) {
                ((u32*)cfgEnd)[0] = 0;
                ((u32*)cfgEnd)[1] = 0;
                ((u32*)cfgEnd)[2] = 0;
            }
        } else {
            struct PlugInConfig { u32 a, b, c; } def = { 0, 0, 0 };
            eastl_vec_insert(cfgEnd, 0, &def);
        }

        eastl_push_c(*(void**)(p3 + 0x8cc), (void*)plugin[1]);

        u32* cfg = (u32*)((char*)*(void**)(p3 + 0xc) - 0xc);
        cfg[0] = 0;
        cfg[1] = (u32)node;
        cfg[2] = (plugin[0] == 0x44616330) ? (u8)(mode & 0xff) : 0;
    }

    int nb = (int)(((char*)mBindEnd - (char*)mBindBegin) / 0x18);
    for (int i = 0; i < nb; ++i) {
        u32* bind = (u32*)((char*)mBindBegin + i * 0x18);
        u32 pluginId = bind[3];
        if (pluginId == 0x506e3230 && !one)
            continue;
        void* opt = (bind[5] & 1) ? (void*)(bind + 2) : 0;
        FUN_00a34cb0((void*)bind[0], (void*)pluginId, (void*)bind[4], (void*)bind[1], opt);
    }

    if (DAT_016e61a8 != 0)
        FUN_0112c620();
    return true;
}
}}  // namespace EA::Audio

// @ 0x00a13300
namespace EA { namespace Audio {
bool EmitterSndPlayer_s00a1_2f90::CreateVoice()
{
    if (mName == 0)
        return false;
    if (!((char (__thiscall*)(void*, u32))(*(void***)mName)[0x18 / 4])(mName, 0x544e850b))
        return false;

    u32 name0[3] = { 0, 0, 0 };
    ((void (__thiscall*)(void*, u32, void*))(*(void***)mName)[0x34 / 4])(mName, 0x544e850b, name0);
    u32 key[2] = { 0x29e333b, 0x21407ee };

    void* handle = 0;
    void* sys = FUN_00a206f0();
    if (handle)
        ((void (__thiscall*)(void*))(*(void***)handle)[1])(handle);
    if (!((char (__thiscall*)(void*, void*, void*))(*(void***)sys)[0x18c / 4])(sys, key, &handle)) {
        if (handle)
            ((void (__thiscall*)(void*))(*(void***)handle)[1])(handle);
        return false;
    }

    mFlags |= 0x10;
    if (!((ResourceVoiceTemplate_s00a1_2f90*)mVoice)->ConstructVoice(mStartTime, mVoice)) {
        if (handle)
            ((void (__thiscall*)(void*))(*(void***)handle)[1])(handle);
        return false;
    }

    if (((char (__thiscall*)(void*, u32))(*(void***)mName)[0x18 / 4])(mName, 0x2fe09c83)) {
        void* p = ((void* (__thiscall*)(void*, u32))(*(void***)mName)[0x3c / 4])(mName, 0x2fe09c83);
        if (p) {
            void* sys2 = FUN_00a206f0();
            void* h = ((void* (__thiscall*)(void*, void*))(*(void***)sys2)[0xf0 / 4])(sys2, p);
            FUN_00a34d70(mVoice, h);
        }
    }

    if (*(void**)(mVoice + 8) == *(void**)(mVoice + 0xc)) {
        if (handle)
            ((void (__thiscall*)(void*))(*(void***)handle)[1])(handle);
        return false;
    }

    FUN_00a11350((char*)this + 0x13);
    VoiceContainer_Create(mVoice, 0);

    if (DAT_016e61a8 != 0)
        FUN_0112c620();                                   // System::Unlock

    ((void (__thiscall*)(void*, int))(*(void***)this)[0x7c / 4])(this, mPitch);

    mpPluginA = FindPlugin(mVoice, 0x536e5031);
    mpPluginB = FindPlugin(mVoice, 0x52737030);

    void* chain = *(void**)(mVoice + 4);
    if (chain) {
        int cnt = (int)(((char*)*(void**)(mVoice + 0xc) - (char*)*(void**)(mVoice + 8)) / 0xc);
        mpPluginC = *(void**)((char*)chain + cnt * 4 - 4);
    }

    mpPluginD = FindPlugin(mVoice, 0x54537430);
    mpPluginE = FindPlugin(mVoice, 0x50617530);

    bool ok = (mpPluginA != 0);
    if (handle)
        ((void (__thiscall*)(void*))(*(void***)handle)[1])(handle);
    return ok;
}
}}  // namespace EA::Audio
