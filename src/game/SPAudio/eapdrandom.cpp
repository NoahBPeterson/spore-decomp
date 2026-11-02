// src/game/SPAudio/eapdrandom.cpp -- migrated from slice(s) s00a5e0f0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdrandom.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"

// ---- items of slice s00a5e0f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_object;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outlet;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outconnect {         // 8
    t_outconnect* oc_next;    // +0
    t_outlet*     oc_to;      // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outlet {             // 0x1c
    t_object*     o_owner;        // +0x00
    t_outlet*     o_next;         // +0x04
    t_outconnect* o_connections;  // +0x08
    t_symbol      o_symfrom;      // +0x0c
    t_symbol      o_symto;        // +0x14
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern int gOutletCount;                    // 0x167545c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol gFloatSymbol;               // 0x16758c4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spFloatRandomClass;         // 0x16756c4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* pd_new(t_class* c);                                                // 0xa49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  outlet_float(void* to, float f);                                   // 0xa49570
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* floatinlet_new(void* owner, void* dest);                           // 0xa49a00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* outlet_new(void* owner, t_symbol s);                              // 0xa49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct RandomLinearCongruential {
    char pad[0x2c];
    unsigned RandomUint32Uniform();            // 0x9360b0
    unsigned RandomUint32UniformN(unsigned n); // 0xa68fb0
    void     SetSeed(unsigned seed);           // 0x936090
    float    NextFloat();                      // 0xa69020 (thiscall)
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern RandomLinearCongruential sSystemRandom;   // 0x16756fc
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
__forceinline void outlet_cnt(t_outlet* lst, float v)
{
    if (++gOutletCount < 1000) {
        t_outconnect* oc;
        for (oc = lst->o_connections; oc; oc = oc->oc_next)
            outlet_float(oc->oc_to, v);
    }
    gOutletCount--;
}
}
}
}
// ---- items of slice s00a5e0f0 end

// @ 0x00a5ed40
namespace EA { namespace Audio { namespace Eapd {
void* frandom_new(float f)
{
    char* x = (char*)pd_new(spFloatRandomClass);
    if (x) {
        *(float*)(x + 0x28) = f;
        (*(RandomLinearCongruential*)(x + 0x2c)).SetSeed(sSystemRandom.RandomUint32Uniform());
        floatinlet_new(x, x + 0x28);
        outlet_new(x, gFloatSymbol);
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5eda0
namespace EA { namespace Audio { namespace Eapd {
void random_bang(char* x)
{
    if (*(float*)(x + 0x28) < 0.0f)
        *(float*)(x + 0x28) = 0.0f;
    int      n = (int)*(float*)(x + 0x28);
    unsigned r = (*(RandomLinearCongruential*)(x + 0x2c)).RandomUint32UniformN(n);
    float    v = (float)r;
    t_outlet* o = *(t_outlet**)(x + 0xc);
    outlet_cnt(o, v);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ee30
namespace EA { namespace Audio { namespace Eapd {
void frandom_bang(char* x)
{
    if (*(float*)(x + 0x28) < 0.0f)
        *(float*)(x + 0x28) = 0.0f;
    float v = *(float*)(x + 0x28) * (*(RandomLinearCongruential*)(x + 0x2c)).NextFloat();
    t_outlet* o = *(t_outlet**)(x + 0xc);
    outlet_cnt(o, v);
}
}}}  // namespace EA::Audio::Eapd
