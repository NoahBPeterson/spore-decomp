// Slice s00a12260 (gold2 batch).  EA::Audio::EmitterSndPlayer resource/voice plumbing
// (SPAudio/AudioEmitterSndPlayer.obj), MSVC 2008 SP1 32-bit.
// flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//   0xa12260  EmitterSndPlayer::q12260()             bool  (vtable slot 0x48-ish)
//   0xa124a0  EmitterSndPlayer::DestroyVoice()       bool
//   0xa12570  EmitterSndPlayer::UpdatePerformanceLevel(int)
//   0xa12640  EmitterSndPlayer::Load()               bool
//   0xa12770  EmitterSndPlayer::CommitPosition(void*) bool
//   0xa12ad0  EmitterSndPlayer::q12ad0()             (destructor body)
//   0xa12c20  AttenHelper::q12c20(float,float,float,float)
//   0xa12c90  Vec12::DoInsertValue(char*, Elem12*)
//   0xa12d80  EmitterSndPlayer::ctor()               EmitterSndPlayer*
#include "types.h"
#include <math.h>
#pragma intrinsic(sqrt, atan2)
static __forceinline float Sqrt(float x) { return (float)sqrt((double)x); }
static __forceinline float Atan2(float y, float x) { return (float)atan2((double)y, (double)x); }

// =====================================================================================
// Callees / globals defined in other translation units.
// =====================================================================================
void* __cdecl f_00a206f0_GetSystemAT();          // EA::Audio::GetSystemAT
extern void* g_16e61a8;                          // rw::audio::core::System singleton
int* FUN_00a11310(int* first, int* last, int* dest);            // 12-byte element copy
void FUN_00f47380(void* p);                      // operator delete
void* FUN_00f473a0(unsigned size, const char* tag, int a, int b, const char* file, unsigned line);

// generic refcounted resource object reached through its own vtable (slot 1 == release)
struct IObject {
    void Release();                              // vtable slot 1
};

// rw::audio::core::System
struct SysGlobal {
    void Lock();                                 // 0x112c600
    void Unlock();                               // 0x112c620
    bool Check(const void* id);                  // 0x112c640
    void Apply(const void* key);                 // 0xa28a20
    unsigned char pad[0xe0];
    void* fE0;                                   // +0xe0 (current voice/play handle)
};

// rw::audio::core::PlugIn
struct PlugIn {
    void Send(int, void*);                       // 0x112ccc0
};

// EA::Audio::VoiceContainer (lives at EmitterSndPlayer + 0x38c)
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

// EA::Audio::ResponseCurve (lives at EmitterSndPlayer + 0x10)
struct ResponseCurve {
    void Ctor();                                 // 0xa1aa50
};

// =====================================================================================
// Lock guard: body inlined at the call site; brackets a critical section and installs
// the /EHsc try level.
// =====================================================================================
struct LockGuard {
    LockGuard()  { if (g_16e61a8) ((SysGlobal*)g_16e61a8)->Lock(); }
    ~LockGuard() { if (g_16e61a8) ((SysGlobal*)g_16e61a8)->Unlock(); }
};

union FloatBits { float f; uint32_t i; };

// =====================================================================================
// EA::Audio::EmitterSndPlayer -- fields (see slice s00a114a0 header).
//   +0x374..+0x384 resource/plugin pointers, +0x388 mbIsStreamed, +0x38c VoiceContainer,
//   +0xcf0..0xcf8 resource key, +0xcfc/+0xd00/+0xd04 vector, +0xd24 performance level,
//   +0xd2a dirty flag, +0xd6c..+0xd80 plugins, +0xd84/+0xd88 flags.
// =====================================================================================
struct EmitterSndPlayer {
    uint8_t m[0xde0];

    __forceinline void** Vt() { return (void**)*(void**)&m[0]; }

    bool q12260();                               // 0xa12260
    bool DestroyVoice();                         // 0xa124a0
    void UpdatePerformanceLevel(int level);      // 0xa12570
    bool Load();                                 // 0xa12640
    bool CommitPosition(void* pos);              // 0xa12770
    void q12ad0();                               // 0xa12ad0
    EmitterSndPlayer* ctor();                    // 0xa12d80
};

// resource/plugin object: virtual slot 1 == release, slot 4 == bool(), slot 5 == bool(void*)
static __forceinline void** VtOf(void* p) { return *(void***)p; }

// =====================================================================================
// eastl-style vector with 12-byte elements.
// =====================================================================================
struct Elem12 { uint32_t a, b, c; };

struct Vec12 {
    char* mpBegin;      // +0
    char* mpEnd;        // +4
    char* mpCapacity;   // +8

    void DoInsertValue(char* pos, Elem12* value);    // 0xa12c90
};

// =====================================================================================
// 0xa12c20: distance-attenuation helper.  __thiscall with four float parameters;
// only the first three are used.
// =====================================================================================
struct AttenHelper {
    float q12c20(float a, float b, float c, float d);   // 0xa12c20
};

// @ 0x00A12260
bool EmitterSndPlayer::q12260() {
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
                LockGuard guard;
                ((PlugIn*)*(void**)(m + 0xd6c))->Send(1, 0);
                *(void**)(m + 0xcec) = ((SysGlobal*)g_16e61a8)->fE0;
            }
        } else if (((SysGlobal*)g_16e61a8)->Check(*(void**)(m + 0xcec))) {
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

// @ 0x00A124A0
bool EmitterSndPlayer::DestroyVoice() {
    LockGuard guard;

    if (g_16e61a8)
        *(void**)(m + 0xcec) = ((SysGlobal*)g_16e61a8)->fE0;

    if (*(void**)(m + 0x394) != *(void**)(m + 0x398)) {
        VoiceContainer* vc = (VoiceContainer*)(m + 0x38c);
        vc->Disconnect();
        (*(PlugIn**)*(void**)(m + 0x390))->Send(1, 0);
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

// @ 0x00A12570
void EmitterSndPlayer::UpdatePerformanceLevel(int level) {
    if (*(int*)(m + 0xd24) == level) return;

    void* data = 0;
    int size = 0;

    SysGlobal* sys = (SysGlobal*)f_00a206f0_GetSystemAT();
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

// @ 0x00A12640
bool EmitterSndPlayer::Load() {
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
        ((SysGlobal*)f_00a206f0_GetSystemAT())->Apply(key);
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

// @ 0x00A12770
bool EmitterSndPlayer::CommitPosition(void* posv) {
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

// @ 0x00A12AD0
void EmitterSndPlayer::q12ad0() {
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

// @ 0x00A12C20
float AttenHelper::q12c20(float a, float b, float c, float d) {
    (void)d;
    if (c > a || b == 0.0f) return 1.0f;
    return 1.0f / ((a / c - 1.0f) * b + 1.0f);
}

// @ 0x00A12C90
void Vec12::DoInsertValue(char* pos, Elem12* value) {
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
    char* q = (char*)FUN_00a11310((int*)pos, (int*)mpEnd, (int*)(p + 12));
    mpBegin = 0;
    mpEnd = q;
    mpCapacity = (char*)(cap * 12);
}

// @ 0x00A12D80
EmitterSndPlayer* EmitterSndPlayer::ctor() {
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
