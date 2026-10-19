// src/game/SPAudio/SPAudioSound.cpp -- migrated from slice(s) s00a40cd0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioSound.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
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
#define VP4  VP VP VP VP
#define VP8  VP4 VP4
#define VP16 VP8 VP8
namespace EA {
namespace Audio {
struct Sound_s00a4_0cd0 {
    char ConfigureSound();                                       // 0x00a20060
    void TickInternal(int a, float b, int c);                    // 0x00a1c710
    void SetPropertyInternal(int key, float v, int arg);         // 0x00a1d9c0
    void Stop(int a, char flags);                                // 0x00a1bba0
    char BeginTick();                                            // 0x00a1af50
    char Init_1b730();                                           // 0x00a1b730
    char Start_1b8a0(double v);                                  // 0x00a1b8a0
    char Check_ef6410();                                         // 0x00ef6410
    void Dtor_8dde10();                                          // 0x008dde10
};
}
}
namespace EA {
namespace Audio {
struct ResponseCurve_s00a4_0cd0 {
    void InitFromConfiguration(void* ps, unsigned key);   // 0x00a1a9d0
};
}
}
namespace SP {
namespace Audio {
int* SPGetSystem();                              // 0x00a421f0
}
}
namespace SP {
namespace Audio {
struct SubObj {
    VP VP VP
    virtual void Slot3(unsigned a, int b, int c);      // +0x0c
};
}
}
namespace SP {
namespace Audio {
struct cSound {
    VP VP VP VP VP VP VP
    virtual char Slot7(int a, int b, float c, int d);  // +0x1c
    virtual char Slot8(int a, int b);                  // +0x20
    VP16 VP4 VP VP VP                                  // slots 9..31
    virtual void Slot32(int a, int b);                 // +0x80

    bool Init();                                       // 0x00a419a0
    bool Start(double v);                              // 0x00a419c0
    void StopThunk(int a, char flags);                 // 0x00a41a00
    void SetPropertyInternal(int key, float value, int arg);   // 0x00a41a20
    void TickInternal(int a, float b, int c);          // 0x00a41a70
    unsigned char ConfigureSound();                    // 0x00a41b60
};
}
}
namespace SP {
namespace Audio {
struct cPropertySet {
    VP VP VP VP VP VP
    virtual bool Has(unsigned key);                    // +0x18
    VP VP
    virtual void Set(unsigned key, void* out);         // +0x24
};
}
}
// ---- items of slice s00a40cd0 end

// @ 0x00a419a0
bool SP::Audio::cSound::Init()
{
    *(int*)((char*)this + 0x1dec) = 6;
    if (((EA::Audio::Sound_s00a4_0cd0*)this)->Init_1b730()) return true;
    return false;
}

// @ 0x00a419c0
bool SP::Audio::cSound::Start(double v)
{
    int* s = SP::Audio::SPGetSystem();
    int id = ((int(__thiscall*)(int*))(*((int**)s))[0x210 / 4])(s);
    *(int*)((char*)this + 0x2ba0) = id;
    if (((EA::Audio::Sound_s00a4_0cd0*)this)->Start_1b8a0(v)) return true;
    return false;
}

// @ 0x00a41a00
void SP::Audio::cSound::StopThunk(int a, char flags)
{
    if (flags && *(char*)((char*)this + 0x2ba5)) flags = 0;
    ((EA::Audio::Sound_s00a4_0cd0*)this)->Stop(a, flags);
}

// @ 0x00a41a20
void SP::Audio::cSound::SetPropertyInternal(int key, float value, int arg)
{
    if (key != 0x771119f4) {
        ((EA::Audio::Sound_s00a4_0cd0*)this)->SetPropertyInternal(key, value, arg);
        return;
    }
    *(unsigned char*)((char*)this + 0x2ba4) = (unsigned char)(value != 0.0f);
}

// @ 0x00a41a70
void SP::Audio::cSound::TickInternal(int a, float b, int c)
{
    ((EA::Audio::Sound_s00a4_0cd0*)this)->TickInternal(a, b, c);
    if (((EA::Audio::Sound_s00a4_0cd0*)this)->BeginTick()) {
        int* s = SP::Audio::SPGetSystem();
        int id = ((int(__thiscall*)(int*))(*((int**)s))[0x210 / 4])(s);
        if (id == *(int*)((char*)this + 0x2ba0) || *(char*)((char*)this + 0x2ba4) != 0) {
            if (((EA::Audio::Sound_s00a4_0cd0*)this)->Check_ef6410()) {
                if (this->Slot8(5, 0)) {
                    this->Slot7(0, 5, -1.0f, 1);
                }
            }
        } else {
            if (!((EA::Audio::Sound_s00a4_0cd0*)this)->Check_ef6410()) {
                ((SP::Audio::SubObj*)(void*)((char*)this + 4))->Slot3(0x25df0108, 0, 1);
                this->Slot32(3, 1);
                return;
            }
            if (!this->Slot8(5, 0)) {
                this->Slot7(1, 5, 0, 1);
                return;
            }
        }
    }
}

// @ 0x00a41b60
unsigned char SP::Audio::cSound::ConfigureSound()
{
    if (!((EA::Audio::Sound_s00a4_0cd0*)this)->ConfigureSound()) return 0;
    char* ps = (char*)this + 0xe4;
    ((SP::Audio::cPropertySet*)ps)->Set(0x771119f4, (char*)this + 0x2ba4);
    ((SP::Audio::cPropertySet*)ps)->Set(0x6dbb22a, (char*)this + 0x2ba5);
    if (((SP::Audio::cPropertySet*)ps)->Has(0x64b25f16)) {
        ((EA::Audio::ResponseCurve_s00a4_0cd0*)((char*)this + 0x1e10))->InitFromConfiguration(ps, 0x64b25f16);
        *(int*)((char*)this + 0xce4) |= 0x80000;
    }
    if (((SP::Audio::cPropertySet*)ps)->Has(0xbc2614d9)) {
        ((EA::Audio::ResponseCurve_s00a4_0cd0*)((char*)this + 0x24d8))->InitFromConfiguration(ps, 0xbc2614d9);
        *(int*)((char*)this + 0xce4) |= 0x100000;
    }
    if (((SP::Audio::cPropertySet*)ps)->Has(0xf70e571c)) {
        ((EA::Audio::ResponseCurve_s00a4_0cd0*)((char*)this + 0x283c))->InitFromConfiguration(ps, 0xf70e571c);
        *(int*)((char*)this + 0xce4) |= 0x200000;
    }
    ((EA::Audio::ResponseCurve_s00a4_0cd0*)((char*)this + 0x2174))->InitFromConfiguration(ps, 0x1e4db1eb);
    return 1;
}
