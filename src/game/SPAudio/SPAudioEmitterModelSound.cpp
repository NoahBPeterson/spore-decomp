// src/game/SPAudio/SPAudioEmitterModelSound.cpp -- migrated from slice(s) s00a37dd0, s00a36d60 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioEmitterModelSound.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/IPrimitive.h"
#include "EA/Audio/ResponseCurve.h"
#include "EA/Audio/Sound.h"
#include "SP/Audio/cEAPDVoiceManager.h"
#include <math.h>

// ---- items of slice s00a36d60 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cEmitterModelSound {
    float ComputeGainAttenuation(void* a, void* b, void* c, void* d);
};
// ---- items of slice s00a36d60 end

// ---- items of slice s00a37dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float f_01485720;        // 0x1485720  1.0f
extern float f_013f11c0;        // 0x13f11c0  1e-6
extern float f_013eb1bc;        // 0x13eb1bc -1.0f
extern float f_013ef548;        // 0x13ef548
extern char  g_014533fc;        // 0x14533fc vtable
extern char  g_014533b0;        // 0x14533b0 vtable
extern char  g_014533a8;        // 0x14533a8 vtable
extern char  g_01453e60;        // 0x1453e60 vtable
extern char  g_013ef094;        // 0x13ef094 vtable
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef unsigned __int64 u64;
#define VFN(p, off) ((*(void***)(p))[(off) / 4])
float __cdecl fabsf(float);                       // CRT fabsf
void  __cdecl opDelete(void* p);                  // 0xf47380 operator delete
inline void* operator new(unsigned int, void* p) { return p; }  // placement new
void* __cdecl GetSystemAT();              // 0xa206f0 EA::Audio::GetSystemAT
namespace EA {
namespace Audio {
class ResponseCurve_s00a3_7dd0 { public:
    ResponseCurve_s00a3_7dd0();                                       // 0xa1aa50
    bool  InitFromConfiguration(void* cfg, u32 key);       // 0xa1a9d0
    float GetOutputValue(float x);                         // 0xa1a110
};
}
}
namespace SP {
namespace Audio {
class cEmitterModelSound_s00a3_7dd0 { public:
    char pad[0x1000];

    bool Init();                    // 0xa37f20
    bool Shutdown();                // 0xa37fe0
    bool SetPaused(char b);         // 0xa38030
    bool Start(u32 a, u32 b);       // 0xa38080  (double dt arg)
    bool Stop();                    // 0xa381d0
    void SetFlags(u32 v);           // 0xa38290
    void SetConfiguration(void* cfg); // 0xa382c0
    bool SetProperty(int id, float v, u32 a); // 0xa38310
    bool SetData(u32 a, u32 b, u32 c);        // 0xa383b0
    void ReadTuningValues();        // 0xa383f0
    int  ShouldTick();              // 0xa38490
    void Tick(u32 a, float dt);     // 0xa384d0
    bool CreateEmitter(u32 key, void* p, void** out); // 0xa38900
    bool Create(u32 a, u32 b);      // 0xa38a50
    ~cEmitterModelSound_s00a3_7dd0();          // 0xa38b30
    cEmitterModelSound_s00a3_7dd0();           // 0xa38c70
};  // namespace SP::Audio
}
}
// ---- items of slice s00a37dd0 end

// @ 0x00a37b70
float cEmitterModelSound::ComputeGainAttenuation(void*, void*, void*, void*)
{
    return 1.0f;
}

// @ 0x00a37f20
namespace SP { namespace Audio {
bool cEmitterModelSound_s00a3_7dd0::Init()
{
    char* self = (char*)this;
    *(volatile u32*)(self + 0x30) |= 1;
    ((void(__thiscall*)(void*))VFN(self, 0x44))(self);
    return true;
}
}}  // namespace SP::Audio

// @ 0x00a37fe0
namespace SP { namespace Audio {
bool cEmitterModelSound_s00a3_7dd0::Shutdown()
{
    char* self = (char*)this;
    if (!(*(u8*)(self + 0x30) & 1)) return false;

    void* p;
    if (*(void**)(self + 0xc) != 0) {
        if ((p = *(void**)(self + 0xc)) != 0) {
            *(void**)(self + 0xc) = 0;
            ((void(__thiscall*)(void*))VFN(p, 4))(p);
        }
    }
    if (*(void**)(self + 0x10) != 0) {
        if ((p = *(void**)(self + 0x10)) != 0) {
            *(void**)(self + 0x10) = 0;
            ((void(__thiscall*)(void*))VFN(p, 4))(p);
        }
    }
    *(u32*)(self + 0x30) &= ~1u;
    return true;
}
}}  // namespace SP::Audio

// @ 0x00a38030
namespace SP { namespace Audio {
bool cEmitterModelSound_s00a3_7dd0::SetPaused(char b)
{
    char* self = (char*)this;
    char c = *(char*)(self + 0x1c);
    if (b != 0) {
        if (c != 0) { *(char*)(self + 0x1c) = b; return true; }
    } else {
        if (c == 0) { *(char*)(self + 0x1c) = b; return true; }
    }
    void* e;
    if ((e = *(void**)(self + 0xc)) != 0)
        ((void(__thiscall*)(void*, char))VFN(e, 0x1c))(e, b);
    if ((e = *(void**)(self + 0x10)) != 0)
        ((void(__thiscall*)(void*, char))VFN(e, 0x1c))(e, b);
    *(char*)(self + 0x1c) = b;
    return true;
}
}}  // namespace SP::Audio

// @ 0x00a38080
namespace SP { namespace Audio {
bool cEmitterModelSound_s00a3_7dd0::Start(u32 a, u32 b)
{
    char* self = (char*)this;
    double dt;
    *(u64*)&dt = ((u64)b << 32) | a;
    if (*(u8*)(self + 0x30) & 0x40) {
        char r = 1;
        void* e1 = *(void**)(self + 0xc);
        if (e1) r = ((bool(__thiscall*)(void*, u32, u32))VFN(e1, 0x14))(e1, a, b);
        void* e2 = *(void**)(self + 0x10);
        if (e2) {
            if (((bool(__thiscall*)(void*, u32, u32))VFN(e2, 0x14))(e2, a, b) && r) return true;
            r = 0;
        }
        return r != 0;
    }
    *(u32*)(self + 0x30) |= 0x40;
    char* edi = self - 4;
    void* at = GetSystemAT();
    if (at) {
        ((void(__thiscall*)(void*, void*))VFN(at, 0x70))(at, edi);
        *(u32*)(edi + 0x34) |= 2;
    }
    ((void(__thiscall*)(void*))VFN(edi, 0))(edi);
    // zero the two emitter lerp states
    char* e = self;
    *(float*)(e + 0xde8) = 0.0f;
    *(float*)(e + 0xde4) = 0.0f;
    *(float*)(e + 0xdec) = 0.0f;
    *(float*)(e + 0xdf4) = 0.0f;
    *(float*)(e + 0xdf0) = 0.0f;
    *(float*)(e + 0xdf8) = 0.0f;
    *(float*)(e + 0xe00) = 0.0f;
    *(float*)(e + 0xdfc) = 0.0f;
    *(float*)(e + 0xe04) = 0.0f;
    *(float*)(e + 0xe0c) = 0.0f;
    *(float*)(e + 0xe08) = 0.0f;
    *(float*)(e + 0xe10) = 0.0f;
    float c = f_013ef548;
    ((void(__thiscall*)(void*, float, float))VFN(edi, 8))(edi, c, c);

    void* e1 = *(void**)(self + 0xc);
    if (e1 && !((bool(__thiscall*)(void*, u32, u32))VFN(e1, 0x14))(e1, a, b)) return false;
    void* e2 = *(void**)(self + 0x10);
    if (e2 && !((bool(__thiscall*)(void*, u32, u32))VFN(e2, 0x14))(e2, a, b)) return false;
    return true;
}
}}  // namespace SP::Audio

// @ 0x00a381d0
namespace SP { namespace Audio {
bool cEmitterModelSound_s00a3_7dd0::Stop()
{
    char* self = (char*)this;
    if (!(*(u8*)(self + 0x30) & 0x40)) return false;
    void* e;
    if ((e = *(void**)(self + 0xc)) != 0) {
        ((void(__thiscall*)(void*))VFN(e, 0x18))(e);
        e = *(void**)(self + 0xc);
        ((void(__thiscall*)(void*, u32))VFN(e, 0x38))(e, 0);
    }
    if ((e = *(void**)(self + 0x10)) != 0) {
        ((void(__thiscall*)(void*))VFN(e, 0x18))(e);
        e = *(void**)(self + 0x10);
        ((void(__thiscall*)(void*, u32))VFN(e, 0x38))(e, 0);
    }
    if (*(void**)(self + 0x14) != 0) {
        void* at = GetSystemAT();
        ((void(__thiscall*)(void*, u32, void*, u32, u32, u32))VFN(at, 0x128))
            (at, 0x3a129ee, *(void**)(self + 0x14), 0, 0, 0);
    }
    if (*(void**)(self + 0x18) != 0) {
        void* at = GetSystemAT();
        ((void(__thiscall*)(void*, u32, void*, u32, u32, u32))VFN(at, 0x128))
            (at, 0x3a129ee, *(void**)(self + 0x18), 0, 0, 0);
    }
    *(u32*)(self + 0x30) &= ~0x40u;
    char* edi = self - 4;
    if (*(u8*)(self + 0x30) & 2) {
        *(u32*)(edi + 0x34) &= ~2u;
        void* at = GetSystemAT();
        ((void(__thiscall*)(void*, void*))VFN(at, 0x74))(at, edi);
    }
    ((void(__thiscall*)(void*))VFN(edi, 4))(edi);
    return true;
}
}}  // namespace SP::Audio

// @ 0x00a38290
namespace SP { namespace Audio {
void cEmitterModelSound_s00a3_7dd0::SetFlags(u32 v)
{
    char* self = (char*)this;
    *(u32*)(self + 0x2c) = v;
    void* e;
    if ((e = *(void**)(self + 0xc)) != 0)
        ((void(__thiscall*)(void*, u32))VFN(e, 0x24))(e, v);
    if ((e = *(void**)(self + 0x10)) != 0)
        ((void(__thiscall*)(void*, u32))VFN(e, 0x24))(e, v);
}
}}  // namespace SP::Audio

// @ 0x00a382c0
namespace SP { namespace Audio {
void cEmitterModelSound_s00a3_7dd0::SetConfiguration(void* cfg)
{
    char* self = (char*)this;
    void* old = *(void**)(self + 0x34);
    if (cfg != old) {
        if (cfg) ((void(__thiscall*)(void*))VFN(cfg, 0))(cfg);
        *(void**)(self + 0x34) = cfg;
        if (old) ((void(__thiscall*)(void*))VFN(old, 4))(old);
    }
    void* e;
    if ((e = *(void**)(self + 0xc)) != 0)
        ((void(__thiscall*)(void*, void*))VFN(e, 0x38))(e, cfg);
    if ((e = *(void**)(self + 0x10)) != 0)
        ((void(__thiscall*)(void*, void*))VFN(e, 0x38))(e, cfg);
}
}}  // namespace SP::Audio

// @ 0x00a38310
namespace SP { namespace Audio {
bool cEmitterModelSound_s00a3_7dd0::SetProperty(int id, float v, u32 a)
{
    char* self = (char*)this;
    switch (id) {
    case 0x25df0108: *(float*)(self + 0x3c) = v; return true;
    case 0x26341ede: *(float*)(self + 0x38) = v; return true;
    case 0x71bc3009: *(float*)(self + 0x40) = v; return true;
    }
    void* e;
    if ((e = *(void**)(self + 0xc)) != 0)
        ((bool(__thiscall*)(void*, int, float, u32))VFN(e, 0x2c))(e, id, v, a);
    if ((e = *(void**)(self + 0x10)) != 0)
        ((bool(__thiscall*)(void*, int, float, u32))VFN(e, 0x2c))(e, id, v, a);
    return true;
}
}}  // namespace SP::Audio

// @ 0x00a383b0
namespace SP { namespace Audio {
bool cEmitterModelSound_s00a3_7dd0::SetData(u32 a, u32 b, u32 c)
{
    char* self = (char*)this;
    void* e;
    if ((e = *(void**)(self + 0xc)) != 0)
        ((bool(__thiscall*)(void*, u32, u32, u32))VFN(e, 0x34))(e, a, b, c);
    if ((e = *(void**)(self + 0x10)) != 0)
        ((bool(__thiscall*)(void*, u32, u32, u32))VFN(e, 0x34))(e, a, b, c);
    return true;
}
}}  // namespace SP::Audio

// @ 0x00a383f0
namespace SP { namespace Audio {
void cEmitterModelSound_s00a3_7dd0::ReadTuningValues()
{
    char* self = (char*)this;
    void* cfg = *(void**)(self + 0x34);
    ((EA::Audio::ResponseCurve_s00a3_7dd0*)(self + 0x54))->InitFromConfiguration(cfg, 0x1e344549);
    cfg = *(void**)(self + 0x34);
    ((EA::Audio::ResponseCurve_s00a3_7dd0*)(self + 0x3b8))->InitFromConfiguration(cfg, 0x578422ba);
    cfg = *(void**)(self + 0x34);
    ((EA::Audio::ResponseCurve_s00a3_7dd0*)(self + 0x71c))->InitFromConfiguration(cfg, 0x1e34454a);
    cfg = *(void**)(self + 0x34);
    ((EA::Audio::ResponseCurve_s00a3_7dd0*)(self + 0xa80))->InitFromConfiguration(cfg, 0x578422b9);

    void* c = *(void**)(self + 0x34);
    ((void(__thiscall*)(void*, u32, void*))VFN(c, 0x30))(c, 0x5b1939b1, self + 0x44);
    c = *(void**)(self + 0x34);
    ((void(__thiscall*)(void*, u32, void*))VFN(c, 0x30))(c, 0x2c4f23d4, self + 0x48);
    c = *(void**)(self + 0x34);
    ((void(__thiscall*)(void*, u32, void*))VFN(c, 0x30))(c, 0x5b1939b2, self + 0x4c);
    c = *(void**)(self + 0x34);
    ((void(__thiscall*)(void*, u32, void*))VFN(c, 0x30))(c, 0x2c4f23d7, self + 0x50);
}
}}  // namespace SP::Audio

// @ 0x00a38490
namespace SP { namespace Audio {
int cEmitterModelSound_s00a3_7dd0::ShouldTick()
{
    char* self = (char*)this;
    void* e = *(void**)(self + 0xc);
    if (e != 0) {
        if (!((char(__thiscall*)(void*))VFN(e, 0x48))(e)) return 0;
    }
    e = *(void**)(self + 0x10);
    if (e != 0) {
        if (!((char(__thiscall*)(void*))VFN(e, 0x48))(e)) return 0;
    }
    return 1;
}
}}  // namespace SP::Audio

// @ 0x00a384d0
namespace SP { namespace Audio {
void cEmitterModelSound_s00a3_7dd0::Tick(u32 a, float dt)
{
    char* self = (char*)this;
    if (*(u8*)(self + 0x20) != 0) return;

    if (*(void**)(self + 0x10) != 0) {
        float desired = ((EA::Audio::ResponseCurve_s00a3_7dd0*)(self + 0x58))->GetOutputValue(*(float*)(self + 0x3c));
        float time = *(float*)(self + 0x48);
        *(float*)(self + 0xde8) = desired;
        float d = fabsf(desired - *(float*)(self + 0xdec));
        if (time == 0.0f || d < f_013f11c0) {
            *(float*)(self + 0xdec) = desired;
        } else {
            *(float*)(self + 0xdf0) = d / time;
        }

        float des2 = ((EA::Audio::ResponseCurve_s00a3_7dd0*)(self + 0x3bc))->GetOutputValue(*(float*)(self + 0x3c));
        float time2 = *(float*)(self + 0x4c);
        *(float*)(self + 0xdf4) = des2;
        float d2 = fabsf(des2 - *(float*)(self + 0xdf8));
        if (time2 == 0.0f || d2 < f_013f11c0) {
            *(float*)(self + 0xdf8) = des2;
        } else {
            *(float*)(self + 0xdfc) = d2 / time2;
        }

        {
            float cur = *(float*)(self + 0xdec);
            float des = *(float*)(self + 0xde8);
            if (cur != des) {
                float delta = des - cur;
                float sign = (delta < 0.0f) ? f_013eb1bc : f_01485720;
                float step = *(float*)(self + 0xdf0) * dt;
                float ad = fabsf(delta);
                if (ad < step) step = ad;
                *(float*)(self + 0xdec) = step * sign + cur;
            }
        }
        {
            float cur = *(float*)(self + 0xdf8);
            float des = *(float*)(self + 0xdf4);
            if (cur != des) {
                float delta = des - cur;
                float sign = (delta < 0.0f) ? f_013eb1bc : f_01485720;
                float step = *(float*)(self + 0xdfc) * dt;
                float ad = fabsf(delta);
                if (ad < step) step = ad;
                *(float*)(self + 0xdf8) = step * sign + cur;
            }
        }
        void* e = *(void**)(self + 0x10);
        float arg1 = *(float*)(self + 0xdf8) * *(float*)(self + 0x44);
        float arg0 = *(float*)(self + 0xdec) * *(float*)(self + 0x40);
        ((void(__thiscall*)(void*, u32, float, u32))VFN(e, 0x2c))(e, 0x25df0108, arg0, 1);
        ((void(__thiscall*)(void*, u32, float, u32))VFN(e, 0x2c))(e, 0x71bc3009, arg1, 1);
    }

    if (*(void**)(self + 0x14) != 0) {
        float desired = ((EA::Audio::ResponseCurve_s00a3_7dd0*)(self + 0x720))->GetOutputValue(*(float*)(self + 0x3c));
        float time = *(float*)(self + 0x50);
        *(float*)(self + 0xe00) = desired;
        float d = fabsf(desired - *(float*)(self + 0xe04));
        if (time == 0.0f || d < f_013f11c0) {
            *(float*)(self + 0xe04) = desired;
        } else {
            *(float*)(self + 0xe08) = d / time;
        }

        float des2 = ((EA::Audio::ResponseCurve_s00a3_7dd0*)(self + 0xa84))->GetOutputValue(*(float*)(self + 0x3c));
        float time2 = *(float*)(self + 0x54);
        *(float*)(self + 0xe0c) = des2;
        float d2 = fabsf(des2 - *(float*)(self + 0xe10));
        if (time2 == 0.0f || d2 < f_013f11c0) {
            *(float*)(self + 0xe10) = des2;
        } else {
            *(float*)(self + 0xe14) = d2 / time2;
        }

        {
            float cur = *(float*)(self + 0xe04);
            float des = *(float*)(self + 0xe00);
            if (cur != des) {
                float delta = des - cur;
                float sign = (delta < 0.0f) ? f_013eb1bc : f_01485720;
                float step = *(float*)(self + 0xe08) * dt;
                float ad = fabsf(delta);
                if (ad < step) step = ad;
                *(float*)(self + 0xe04) = step * sign + cur;
            }
        }
        {
            float cur = *(float*)(self + 0xe10);
            float des = *(float*)(self + 0xe0c);
            if (cur != des) {
                float delta = des - cur;
                float sign = (delta < 0.0f) ? f_013eb1bc : f_01485720;
                float step = *(float*)(self + 0xe14) * dt;
                float ad = fabsf(delta);
                if (ad < step) step = ad;
                *(float*)(self + 0xe10) = step * sign + cur;
            }
        }
        void* e = *(void**)(self + 0x14);
        float arg1 = *(float*)(self + 0xe10) * *(float*)(self + 0x44);
        float arg0 = *(float*)(self + 0xe04) * *(float*)(self + 0x40);
        ((void(__thiscall*)(void*, u32, float, u32))VFN(e, 0x2c))(e, 0x25df0108, arg0, 1);
        ((void(__thiscall*)(void*, u32, float, u32))VFN(e, 0x2c))(e, 0x71bc3009, arg1, 1);
    }
}
}}  // namespace SP::Audio

// @ 0x00a38900
namespace SP { namespace Audio {
bool cEmitterModelSound_s00a3_7dd0::CreateEmitter(u32 key, void* p, void** out)
{
    char* self = (char*)this;
    if (p == 0) return false;
    void* sys = GetSystemAT();
    if (sys == 0) return false;

    void* local = 0;
    if (!((bool(__thiscall*)(void*, u32, void**))VFN(sys, 0x180))(sys, 0x1a527db, &local))
        return false;
    // fill descriptor {p, 0x1a527db, 0x21407ee}
    void* desc[3];
    desc[0] = p;
    desc[1] = (void*)0x1a527db;
    desc[2] = (void*)0x21407ee;
    void* ext = *(void**)(self + 0x38);
    ((void(__thiscall*)(void*, void**))VFN(local, 0x28))(local, desc);
    ((void(__thiscall*)(void*, void*))VFN(local, 0x38))(local, ext);
    ((void(__thiscall*)(void*, void*))VFN(local, 0x24))(local, p);
    if (!((bool(__thiscall*)(void*))VFN(local, 8))(local)) return false;
    if (!((bool(__thiscall*)(void*))VFN(local, 0x10))(local)) return false;
    u32 f = (*(u32*)(self + 0x34) & 0x100) == 0x100;
    ((void(__thiscall*)(void*, u32))VFN(local, 0x3c))(local, f);
    ((void(__thiscall*)(void*))VFN(local, 0))(local);
    *out = local;
    if (local) ((void(__thiscall*)(void*))VFN(local, 4))(local);
    return true;
}
}}  // namespace SP::Audio

// @ 0x00a38a50
namespace SP { namespace Audio {
bool cEmitterModelSound_s00a3_7dd0::Create(u32 a, u32 b)
{
    char* self = (char*)this;
    void* cfg = *(void**)(self + 0x34);
    u32 tmp = 0;
    if (!((bool(__thiscall*)(void*, u32, u32*))VFN(cfg, 0x4c))(cfg, 0x701ed91e, &tmp))
        return false;
    if (tmp == 0) return false;

    void* at = GetSystemAT();
    void* em;
    em = ((void*(__thiscall*)(void*))VFN(at, 0xb8))(at);
    *(void**)(self + 0x14) = em;
    void* old = *(void**)(self + 0xc);
    if (old) {
        *(void**)(self + 0xc) = 0;
        ((void(__thiscall*)(void*))VFN(old, 4))(old);
    }
    if (!CreateEmitter(a, *(void**)(self + 0x14), (void**)(self + 0xc)))
        return false;

    if (tmp == 2) {
        at = GetSystemAT();
        em = ((void*(__thiscall*)(void*))VFN(at, 0xb8))(at);
        *(void**)(self + 0x18) = em;
        old = *(void**)(self + 0x10);
        if (old) {
            *(void**)(self + 0x10) = 0;
            ((void(__thiscall*)(void*))VFN(old, 4))(old);
        }
        if (!CreateEmitter(a, *(void**)(self + 0x18), (void**)(self + 0x10)))
            return false;
    }
    return true;
}
}}  // namespace SP::Audio

// @ 0x00a38b30
namespace SP { namespace Audio {
cEmitterModelSound_s00a3_7dd0::~cEmitterModelSound_s00a3_7dd0()
{
    char* self = (char*)this;
    *(void**)(self + 0) = &g_014533fc;
    *(void**)(self + 4) = &g_014533b0;
    *(void**)(self + 8) = &g_014533a8;
    if (*(u32*)(self + 0x34) & 1) {
        void* p;
        if ((p = *(void**)(self + 0x10)) != 0) {
            *(void**)(self + 0x10) = 0;
            ((void(__thiscall*)(void*))VFN(p, 4))(p);
        }
        if ((p = *(void**)(self + 0x14)) != 0) {
            *(void**)(self + 0x14) = 0;
            ((void(__thiscall*)(void*))VFN(p, 4))(p);
        }
        *(u32*)(self + 0x34) &= ~1u;
    }
    // curve buffers
    void* b;
    b = *(void**)(self + 0xa84);
    if (b && b != *(void**)(self + 0xa94)) opDelete(b);
    b = *(void**)(self + 0x720);
    if (b && b != *(void**)(self + 0x730)) opDelete(b);
    b = *(void**)(self + 0x3bc);
    if (b && b != *(void**)(self + 0x3cc)) opDelete(b);
    b = *(void**)(self + 0x58);
    if (b && b != *(void**)(self + 0x68)) opDelete(b);
    void* p;
    p = *(void**)(self + 0x38);
    if (p) ((void(__thiscall*)(void*))VFN(p, 4))(p);
    p = *(void**)(self + 0x14);
    if (p) ((void(__thiscall*)(void*))VFN(p, 4))(p);
    p = *(void**)(self + 0x10);
    if (p) ((void(__thiscall*)(void*))VFN(p, 4))(p);
    *(void**)(self + 8) = &g_013ef094;
}
}}  // namespace SP::Audio

// @ 0x00a38c70
namespace SP { namespace Audio {
cEmitterModelSound_s00a3_7dd0::cEmitterModelSound_s00a3_7dd0()
{
    char* self = (char*)this;
    *(void**)(self + 4) = &g_01453e60;
    *(void**)(self + 8) = &g_013ef094;
    *(u32*)(self + 0xc) = 0;
    *(void**)(self + 0) = &g_014533fc;
    *(void**)(self + 4) = &g_014533b0;
    *(void**)(self + 8) = &g_014533a8;
    *(u32*)(self + 0x10) = 0;
    *(u32*)(self + 0x14) = 0;
    *(u32*)(self + 0x18) = 0;
    *(u32*)(self + 0x1c) = 0;
    *(u8*)(self + 0x20) = 0;
    *(u32*)(self + 0x24) = 0;
    *(u32*)(self + 0x28) = 0;
    *(u32*)(self + 0x2c) = 0;
    *(u32*)(self + 0x30) = 0;
    *(u32*)(self + 0x34) = 0;
    *(u32*)(self + 0x38) = 0;
    *(float*)(self + 0x3c) = 0.0f;
    *(float*)(self + 0x40) = f_01485720;
    *(float*)(self + 0x44) = f_01485720;
    *(float*)(self + 0x48) = 0.0f;
    *(float*)(self + 0x4c) = 0.0f;
    *(float*)(self + 0x50) = 0.0f;
    *(float*)(self + 0x54) = 0.0f;
    new ((void*)(self + 0x58)) EA::Audio::ResponseCurve_s00a3_7dd0();
    new ((void*)(self + 0x3bc)) EA::Audio::ResponseCurve_s00a3_7dd0();
    new ((void*)(self + 0x720)) EA::Audio::ResponseCurve_s00a3_7dd0();
    new ((void*)(self + 0xa84)) EA::Audio::ResponseCurve_s00a3_7dd0();
}
}}  // namespace SP::Audio
