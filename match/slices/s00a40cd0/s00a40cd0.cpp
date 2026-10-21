// Slice s00a40cd0: SP::Audio trixie plugin object, SP::Audio::cAudioPreferences
// configuration accessors, EAPd proxy objects, and SP::Audio::cSound overrides
// (0xa40cd0-0xa41b60).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.  Callees outside the slice are
// masked relocations, so they are declared with the right calling convention only.
#include "types.h"

void* operator new(unsigned int, const char*, int, int, int, int);
void* operator new(unsigned int);
void operator delete(void*);
void operator delete[](void*);

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(pad_, __COUNTER__)();
#define VP4  VP VP VP VP
#define VP8  VP4 VP4
#define VP16 VP8 VP8

// ---- shared types -----------------------------------------------------------

// EA's Variant: a tagged union, only the header is modelled here.
struct Variant {
    int mTypeId;               // +0x00
    int mFlags;                // +0x04
    void SetFloat(const float* x);        // 0x00428060  Variant::operator=<float>
    void SetUInt(const unsigned* x);      // 0x00427fd0  Variant::operator=<unsigned int>
    void SetBool(const unsigned char* x); // Variant::operator=<bool>
    void Destruct(int free);              // 0x0093db80  Variant::Destruct
};

// An EA property object; GetFloat/GetUInt/GetBool are __thiscall members.
struct Property {
    char pad0[0x12];
    short mType;                          // +0x12
    float*          GetFloat();           // 0x0041ea70
    unsigned*       GetUInt();            // 0x0041ea00
    unsigned char*  GetBool();            // 0x0041e920
};

// The global application preference list.
struct cPropertyList {
    VP VP VP VP VP
    virtual void SetProperty(unsigned key, Variant* value);       // +0x14
    VP VP VP
    virtual bool GetProperty(unsigned key, Property** out);       // +0x24
};

extern cPropertyList* sPrefs;             // 0x015fd91c
extern unsigned char  kFloatZero[4];      // 0x01485378  (0.0f)

// ---- external callees (masked relocations) ----------------------------------

namespace SP { namespace EditorUtils {
void PlayEditorSound(unsigned a, unsigned b, float c, int d);     // 0x00435f40
}}

void  SetGlobalProperty(int key, float value);
int*  AudioSystem();                                              // 0x0067cb00

namespace EA {
int* ConvertToString16(int* out, int str, int len);              // 0x0093c5a0

namespace VariantNS {}
namespace Audio {

int* GetSystemAT();                                              // 0x00a206f0

class Sound { public:
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

namespace Eapd {
struct Trixie;
void Read(Trixie* self);                                         // 0x00a40a00

int   pd_new(int klass);                                         // 0x00a49390
void* getbytes(int size, const char* tag);                       // 0x00a49610
int   outlet_new(int self, int a, int b);                        // 0x00a49d30
int*  gensym(void* out, const char* name);                       // 0x00a675f0
int   class_new(int a, int b, void* ctor, void* dtor, int size, int x, int y, int z);  // 0x00a48ea0
void  class_addmethod(int klass, void* fn, int a, int b, int c, int d);                 // 0x00a48a80

namespace Debug {
struct EapdObj {
    VP16 VP8 VP4 VP VP                          // slots 0..29
    virtual char Slot30(void* desc, int str, int a, int b);   // +0x78
};
EapdObj* ObjectError();                          // 0x008de1a0
}

namespace ISystem {
int* GetSingletonPtr();                          // 0x00a67c60
}
}

class ResponseCurve { public:
    void InitFromConfiguration(void* ps, unsigned key);   // 0x00a1a9d0
};

}}  // namespace EA::Audio

namespace SP { namespace Audio {
int* SPGetSystem();                              // 0x00a421f0
}}

namespace SP {
struct cLocalLightInfo {
    void Dtor(int value);                        // 0x009276c0
};
extern void* DAT_016c8b44;
}

// ---- trixie plugin ----------------------------------------------------------

// @ 0x00a40cd0
void trixie_use(int self, int unused, int str) {
    EA::Audio::Eapd::Debug::EapdObj* obj = EA::Audio::Eapd::Debug::ObjectError();
    if (!obj) return;
    int desc[3];
    desc[0] = 0;
    desc[1] = 0;
    desc[2] = 0;
    int s16[2];
    int* s = EA::ConvertToString16(s16, str, -1);
    char ok = obj->Slot30(desc, *s, 0, 0);
    if (s16[0] != 0 && (2 < ((s16[1] - s16[0]) & 0xfffffffe))) operator delete[]((void*)s16[0]);
    if (ok) {
        if (desc[2] == 0 || desc[2] == -1) desc[2] = 0x21407ee;
        if (desc[1] == 0 || desc[1] == -1) desc[1] = 0x330a65e;
        int* t = *(int**)(self + 0x28);
        t[0] = desc[0];
        t[1] = desc[1];
        t[2] = desc[2];
        EA::Audio::Eapd::Read(*(EA::Audio::Eapd::Trixie**)(self + 0x28));
    }
}

extern int s_trixie, DAT_0166ef44, DAT_0166ef24, DAT_0166ef28, DAT_0166ef14, DAT_0166ef18;
extern int DAT_01667bac, DAT_01667bad;

// @ 0x00a40dd0
int trixie_new(int a, int b, int arg3, int arg4) {
    int self = EA::Audio::Eapd::pd_new(DAT_0166ef44);
    int* p = (int*)EA::Audio::Eapd::getbytes(0x34, "EAPd/Trixie");
    *(int**)(self + 0x28) = p;
    if (p != 0) {
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        p[3] = self;
        int base = (int)&DAT_01667bac;
        p[4] = base;
        p[5] = base;
        p[6] = 0x1667bad;
        p[8] = 0;
        p[9] = 0;
        p[10] = 0;
    } else {
        p = 0;
    }
    int u3 = DAT_0166ef28;
    int u4 = DAT_0166ef24;
    *(int**)(self + 0x28) = p;
    u3 = EA::Audio::Eapd::outlet_new(self, u4, u3);
    *(int*)(self + 0x2c) = u3;
    u4 = DAT_0166ef14;
    u3 = EA::Audio::Eapd::outlet_new(self, u4, DAT_0166ef18);
    *(int*)(self + 0x30) = u3;
    if (arg3 == 1) {
        trixie_use(self, *(int*)(arg4 + 4), *(int*)(arg4 + 8));
    }
    return self;
}

extern int DAT_0166ef2c, DAT_0166ef30, DAT_0166ef0c, DAT_0166ef10, DAT_0166ef1c, DAT_0166ef20;
extern int DAT_0166ef3c, DAT_0166ef40, DAT_0166ef04, DAT_0166ef08, DAT_0166ef34, DAT_0166ef38;
extern char DAT_01409070[], DAT_01453aac[], DAT_01453a40[], DAT_01453aa4[], DAT_01453b84[];
extern char DAT_01453b7c[], DAT_01453b90[];

void FUN_00a3f090(void);
void FUN_00a3fdc0(void);

// @ 0x00a40e80
int SP_Audio_Trixie_Register() {
    int buf[2];
    int* g;
    g = EA::Audio::Eapd::gensym(buf, DAT_01409070);
    DAT_0166ef2c = g[0];
    DAT_0166ef30 = g[1];
    g = EA::Audio::Eapd::gensym(buf, DAT_01453b90);
    DAT_0166ef0c = g[0];
    DAT_0166ef10 = g[1];
    g = EA::Audio::Eapd::gensym(buf, DAT_01453aac);
    DAT_0166ef1c = g[0];
    DAT_0166ef20 = g[1];
    g = EA::Audio::Eapd::gensym(buf, DAT_01453a40);
    DAT_0166ef3c = g[0];
    DAT_0166ef40 = g[1];
    g = EA::Audio::Eapd::gensym(buf, DAT_01409070);
    DAT_0166ef24 = g[0];
    DAT_0166ef28 = g[1];
    g = EA::Audio::Eapd::gensym(buf, DAT_01453aa4);
    DAT_0166ef14 = g[0];
    DAT_0166ef18 = g[1];
    g = EA::Audio::Eapd::gensym(buf, DAT_01453b84);
    DAT_0166ef04 = g[0];
    DAT_0166ef08 = g[1];
    g = EA::Audio::Eapd::gensym(buf, DAT_01453b7c);
    DAT_0166ef34 = g[0];
    DAT_0166ef38 = g[1];
    DAT_0166ef44 = EA::Audio::Eapd::class_new(DAT_0166ef0c, DAT_0166ef10,
                                              (void*)trixie_new, (void*)FUN_00a3fdc0,
                                              0x38, 0, 9, 0);
    EA::Audio::Eapd::class_addmethod(DAT_0166ef44, (void*)FUN_00a3f090,
                                     DAT_0166ef1c, DAT_0166ef20, 9, 0);
    EA::Audio::Eapd::class_addmethod(DAT_0166ef44, (void*)trixie_use,
                                     DAT_0166ef3c, DAT_0166ef40, 2, 0);
    return 1;
}

// ---- cAudioPreferences ------------------------------------------------------

namespace SP { namespace Audio {

class cAudioPreferences { public:
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

// @ 0x00a41010
int cAudioPreferences::Init() {
    int* sys = EA::Audio::GetSystemAT();
    cPropertyList* p = sPrefs;
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

// @ 0x00a411b0
bool __stdcall cAudioPreferences::GetVolume(unsigned key, float* out) {
    cPropertyList* p = sPrefs;
    if (!p) return false;
    Property* prop;
    if (!p->GetProperty(key, &prop)) return false;
    if (prop->mType != 0xD) return false;
    *out = *prop->GetFloat();
    return true;
}

// @ 0x00a41200
int cAudioPreferences::GetSpeakerMode() {
    int result = 0;
    cPropertyList* p = sPrefs;
    if (p) {
        Property* prop;
        if (p->GetProperty(0x49D4C74D, &prop) && prop->mType == 0xA)
            result = *prop->GetUInt();
    }
    return result;
}

// @ 0x00a41240
int cAudioPreferences::GetSoundQuality() {
    int result = 3;
    cPropertyList* p = sPrefs;
    if (p) {
        Property* prop;
        if (p->GetProperty(0x7D8ED666, &prop) && prop->mType == 0xA)
            result = *prop->GetUInt();
    }
    return result;
}

// @ 0x00a41280
unsigned char cAudioPreferences::IsMuted() {
    unsigned char result = 0;
    cPropertyList* p = sPrefs;
    if (p) {
        Property* prop;
        if (p->GetProperty(0x899EB157, &prop) && prop->mType == 1)
            result = *prop->GetBool();
    }
    return result;
}

// @ 0x00a412c0
void __stdcall cAudioPreferences::SetVolume(unsigned key, float value) {
    cPropertyList* p = sPrefs;
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
    Variant v;
    v.mTypeId = 0;
    v.mFlags = 0;
    v.SetFloat(&value);
    p->SetProperty(key, &v);
    if (v.mFlags & 4) v.Destruct(0);
}

// @ 0x00a41410
void __stdcall cAudioPreferences::SetSpeakerMode(unsigned mode) {
    unsigned cur = 0;
    cPropertyList* p = sPrefs;
    if (p) {
        Property* prop;
        if (p->GetProperty(0x49D4C74D, &prop) && prop->mType == 0xA)
            cur = *prop->GetUInt();
    }
    if (cur != mode && (mode == 2 || (3 < mode && mode < 6)) && sPrefs) {
        Variant v;
        v.mTypeId = 0;
        v.mFlags = 0;
        v.SetUInt(&mode);
        p->SetProperty(0x49D4C74D, &v);
        if (v.mFlags & 4) v.Destruct(0);
        int* sys = AudioSystem();
        if (sys) ((void(**)(int*))(*((int**)sys)))[3]((int*)sys);
    }
}

// @ 0x00a41500
void __stdcall cAudioPreferences::SetSoundQuality(int quality) {
    int cur = 3;
    cPropertyList* p = sPrefs;
    if (p) {
        Property* prop;
        if (p->GetProperty(0x7D8ED666, &prop) && prop->mType == 0xA)
            cur = *prop->GetUInt();
    }
    if (cur != quality && sPrefs) {
        Variant v;
        v.mTypeId = 0;
        v.mFlags = 0;
        unsigned q = (unsigned)quality;
        v.SetUInt(&q);
        p->SetProperty(0x7D8ED666, &v);
        if (v.mFlags & 4) v.Destruct(0);
        SetGlobalProperty(0x6df5822d, (float)(unsigned)quality);
    }
}

// @ 0x00a415f0
void __stdcall cAudioPreferences::Mute(unsigned char m) {
    unsigned char cur = 0;
    cPropertyList* p = sPrefs;
    if (p) {
        Property* prop;
        if (p->GetProperty(0x899EB157, &prop) && prop->mType == 1)
            cur = *prop->GetBool();
    }
    if (cur != m && sPrefs) {
        Variant v;
        v.mTypeId = 0;
        v.mFlags = 0;
        v.SetBool(&m);
        p->SetProperty(0x899EB157, &v);
        if (v.mFlags & 4) v.Destruct(0);
        SetGlobalProperty(0x899eb157, (float)m);
    }
}

}}  // namespace SP::Audio

// ---- EAPd proxy objects -----------------------------------------------------

// @ 0x00a416e0
int __stdcall FUN_00a416e0(int* p, unsigned n) {
    if (p != 0) {
        if (n >= 1) {
            *p = 0x22d2c83;
        } else {
            return 0;
        }
    }
    return 1;
}

extern char PTR_AddRef_01453c30[];
extern int  DAT_0166ef48;

char FUN_008dde10(void);
char FUN_008dde50(int a, int b, int c, int d);
void FUN_008ddff0(void);

struct AddRefObj {
    virtual void AddRef();                    // +0x00
    virtual void Release();                   // +0x04
    void CTor();                              // 0x008ddff0  (thiscall ctor)
    void Dtor();                              // 0x00a41710
};
struct FactoryObj {
    VP VP VP VP VP VP VP VP VP
    virtual char Create(int key, int* obj, int a, int b);   // +0x24
    char Run(int key, int* out, int a, int b);              // 0x00a417b0
};

// @ 0x00a41710
void AddRefObj::Dtor() {
    *(int*)this = (int)PTR_AddRef_01453c30;
    if (*(int*)((char*)this + 0x14) != 0) {
        int* s = EA::Audio::GetSystemAT();
        if (s) ((void(**)(int*))*((int**)s))[0xC0 / 4]((int*)s);
        int* e = EA::Audio::Eapd::ISystem::GetSingletonPtr();
        if (e) ((void(**)(int*, int))(*((int**)e)))[0x50 / 4]((int*)e, *(int*)((char*)this + 0x14));
        s = EA::Audio::GetSystemAT();
        if (s) ((void(**)(int*))*((int**)s))[0xC4 / 4]((int*)s);
    }
    ((EA::Audio::Sound*)this)->Dtor_8dde10();
}

// @ 0x00a417b0
char FactoryObj::Run(int key, int* out, int a, int b) {
    if (out == 0) return 0;
    char result;
    AddRefObj* obj = (AddRefObj*)operator new(0x20, "Audio", 0, 0, 0, 0);
    if (obj == 0) {
        obj = 0;
    } else {
        obj->CTor();
        *(int*)obj = (int)PTR_AddRef_01453c30;
    }
    if (obj != 0) obj->AddRef();
    result = 0;
    if (obj != 0) {
        if (key == 0) {
            result = 1;
        } else {
            result = Create(key, (int*)obj, a, b);
            if (result == 0) goto done;
        }
        *out = (int)obj;
        obj->AddRef();
    }
done:
    if (obj != 0) obj->Release();
    return result;
}

// @ 0x00a418b0
unsigned char __stdcall FUN_00a418b0(int a, int self, int c, int d) {
    int saved = *(int*)(self + 0x14);
    unsigned char result = 0;
    *(int*)(self + 0x14) = 0;
    char ok = FUN_008dde50(a, self, c, d);
    if (ok) {
        int* s = EA::Audio::GetSystemAT();
        if (s) ((void(**)(int*))*((int**)s))[0xC0 / 4]((int*)s);
        int* e = EA::Audio::Eapd::ISystem::GetSingletonPtr();
        result = 0;
        if (e)
            result = (unsigned char)((int(__thiscall*)(int*, int, int, int))(*((int**)e))[0x4C / 4])((int*)e, *(int*)(self + 0x14), *(int*)(self + 0x18), self + 0x1c);
        s = EA::Audio::GetSystemAT();
        if (s) ((void(**)(int*))*((int**)s))[0xC4 / 4]((int*)s);
    }
    if (saved != 0) ((SP::cLocalLightInfo*)SP::DAT_016c8b44)->Dtor(saved);
    return result;
}

// ---- cSound overrides -------------------------------------------------------

namespace SP { namespace Audio {

struct SubObj {
    VP VP VP
    virtual void Slot3(unsigned a, int b, int c);      // +0x0c
};

class cSound { public:
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

struct cPropertySet {
    VP VP VP VP VP VP
    virtual bool Has(unsigned key);                    // +0x18
    VP VP
    virtual void Set(unsigned key, void* out);         // +0x24
};

}}

// @ 0x00a419a0
bool SP::Audio::cSound::Init() {
    *(int*)((char*)this + 0x1dec) = 6;
    if (((EA::Audio::Sound*)this)->Init_1b730()) return true;
    return false;
}

// @ 0x00a419c0
bool SP::Audio::cSound::Start(double v) {
    int* s = SP::Audio::SPGetSystem();
    int id = ((int(__thiscall*)(int*))(*((int**)s))[0x210 / 4])(s);
    *(int*)((char*)this + 0x2ba0) = id;
    if (((EA::Audio::Sound*)this)->Start_1b8a0(v)) return true;
    return false;
}

// @ 0x00a41a00
void SP::Audio::cSound::StopThunk(int a, char flags) {
    if (flags && *(char*)((char*)this + 0x2ba5)) flags = 0;
    ((EA::Audio::Sound*)this)->Stop(a, flags);
}

// @ 0x00a41a20
void SP::Audio::cSound::SetPropertyInternal(int key, float value, int arg) {
    if (key != 0x771119f4) {
        ((EA::Audio::Sound*)this)->SetPropertyInternal(key, value, arg);
        return;
    }
    *(unsigned char*)((char*)this + 0x2ba4) = (unsigned char)(value != 0.0f);
}

// @ 0x00a41a70
void SP::Audio::cSound::TickInternal(int a, float b, int c) {
    ((EA::Audio::Sound*)this)->TickInternal(a, b, c);
    if (((EA::Audio::Sound*)this)->BeginTick()) {
        int* s = SP::Audio::SPGetSystem();
        int id = ((int(__thiscall*)(int*))(*((int**)s))[0x210 / 4])(s);
        if (id == *(int*)((char*)this + 0x2ba0) || *(char*)((char*)this + 0x2ba4) != 0) {
            if (((EA::Audio::Sound*)this)->Check_ef6410()) {
                if (this->Slot8(5, 0)) {
                    this->Slot7(0, 5, -1.0f, 1);
                }
            }
        } else {
            if (!((EA::Audio::Sound*)this)->Check_ef6410()) {
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
unsigned char SP::Audio::cSound::ConfigureSound() {
    if (!((EA::Audio::Sound*)this)->ConfigureSound()) return 0;
    char* ps = (char*)this + 0xe4;
    ((SP::Audio::cPropertySet*)ps)->Set(0x771119f4, (char*)this + 0x2ba4);
    ((SP::Audio::cPropertySet*)ps)->Set(0x6dbb22a, (char*)this + 0x2ba5);
    if (((SP::Audio::cPropertySet*)ps)->Has(0x64b25f16)) {
        ((EA::Audio::ResponseCurve*)((char*)this + 0x1e10))->InitFromConfiguration(ps, 0x64b25f16);
        *(int*)((char*)this + 0xce4) |= 0x80000;
    }
    if (((SP::Audio::cPropertySet*)ps)->Has(0xbc2614d9)) {
        ((EA::Audio::ResponseCurve*)((char*)this + 0x24d8))->InitFromConfiguration(ps, 0xbc2614d9);
        *(int*)((char*)this + 0xce4) |= 0x100000;
    }
    if (((SP::Audio::cPropertySet*)ps)->Has(0xf70e571c)) {
        ((EA::Audio::ResponseCurve*)((char*)this + 0x283c))->InitFromConfiguration(ps, 0xf70e571c);
        *(int*)((char*)this + 0xce4) |= 0x200000;
    }
    ((EA::Audio::ResponseCurve*)((char*)this + 0x2174))->InitFromConfiguration(ps, 0x1e4db1eb);
    return 1;
}
