// src/game/SPAudio/SPAudioObjectTrixie.cpp -- migrated from slice(s) s00a40cd0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioObjectTrixie.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/ResponseCurve.h"
#include "EA/Audio/Sound.h"
#include "EA/Variant.h"
#include "SP/Audio/cAudioPreferences.h"

// unnamed retail callees and globals (address in the comment)
extern int s_trixie, DAT_0166ef44, DAT_0166ef24, DAT_0166ef28, DAT_0166ef14, DAT_0166ef18;
extern int DAT_01667bac, DAT_01667bad;
extern int DAT_0166ef2c, DAT_0166ef30, DAT_0166ef0c, DAT_0166ef10, DAT_0166ef1c, DAT_0166ef20;
extern int DAT_0166ef3c, DAT_0166ef40, DAT_0166ef04, DAT_0166ef08, DAT_0166ef34, DAT_0166ef38;
extern char DAT_01409070[], DAT_01453aac[], DAT_01453a40[], DAT_01453aa4[], DAT_01453b84[];
extern char DAT_01453b7c[], DAT_01453b90[];

// ---- items of slice s00a40cd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void operator delete(void*);
void operator delete[](void*);
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(pad_, __COUNTER__)();
#define VP4  VP VP VP VP
#define VP8  VP4 VP4
#define VP16 VP8 VP8
namespace EA {
int* ConvertToString16(int* out, int str, int len);              // 0x0093c5a0
}
namespace EA {
namespace Audio {
namespace Eapd {
struct Trixie;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void Read(Trixie* self);                                         // 0x00a40a00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   pd_new(int klass);                                         // 0x00a49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* getbytes(int size, const char* tag);                       // 0x00a49610
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   outlet_new(int self, int a, int b);                        // 0x00a49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int*  gensym(void* out, const char* name);                       // 0x00a675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   class_new(int a, int b, void* ctor, void* dtor, int size, int x, int y, int z);  // 0x00a48ea0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  class_addmethod(int klass, void* fn, int a, int b, int c, int d);                 // 0x00a48a80
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
namespace Debug {
struct EapdObj {
    VP16 VP8 VP4 VP VP                          // slots 0..29
    virtual char Slot30(void* desc, int str, int a, int b);   // +0x78
};
}
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
namespace Debug {
EapdObj* ObjectError();                          // 0x008de1a0
}
}
}
}
extern int s_trixie, DAT_0166ef44, DAT_0166ef24, DAT_0166ef28, DAT_0166ef14, DAT_0166ef18;
extern int DAT_01667bac, DAT_01667bad;
extern int DAT_0166ef2c, DAT_0166ef30, DAT_0166ef0c, DAT_0166ef10, DAT_0166ef1c, DAT_0166ef20;
extern int DAT_0166ef3c, DAT_0166ef40, DAT_0166ef04, DAT_0166ef08, DAT_0166ef34, DAT_0166ef38;
extern char DAT_01409070[], DAT_01453aac[], DAT_01453a40[], DAT_01453aa4[], DAT_01453b84[];
extern char DAT_01453b7c[], DAT_01453b90[];
void FUN_00a3f090(void);
void FUN_00a3fdc0(void);
// ---- items of slice s00a40cd0 end

// @ 0x00a40cd0
void trixie_use(int self, int unused, int str)
{
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

// @ 0x00a40dd0
int trixie_new(int a, int b, int arg3, int arg4)
{
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

// @ 0x00a40e80
int SP_Audio_Trixie_Register()
{
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
