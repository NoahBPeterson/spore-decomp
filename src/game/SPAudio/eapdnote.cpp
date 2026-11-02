// src/game/SPAudio/eapdnote.cpp -- migrated from slice(s) s00a5e0f0, s00a5d3c0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdnote.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <windows.h>
#include "EA/Random/RandomLinearCongruential.h"

// ---- items of slice s00a5d3c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char byte;
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol {
    const char* s_name;     // +0x00
    void* s_thing;          // +0x04
};
}
}
}
using EA::Audio::Eapd::t_symbol;
t_symbol* gensym(t_symbol* s, const char* name);
void* class_new(const char* name, void* thing, void* newmethod, void* freemethod,
                int size, int flags, int type, ...);
int class_addmethod(void* c, void* fn, ...);
int class_doaddfloat(void* c, void* fn);
void* pd_new(void* c);
void* outlet_new(void* x, const char* type, void* sel);
void* floatinlet_new(void* x, void* val);
void outlet_float(void* outlet, float f);
void* getbytes(int size, const char* tag);
void* g_polyClass_16756ac;
void* g_stripnoteClass_16756b0;
void* g_makenoteClass_16756b8;
t_symbol g_floatSymbol_16758c4;         // "float"
int g_outletCount_167545c;
byte makenote_setup();
byte stripnote_setup();
void* makenote_new(float f1, float f2);
void makenote_free_all(void* x);
void makenote_float(void* x, float f);
void makenote_release_all(void* x);
void* stripnote_new();
void stripnote_float(void* x, float f);
void* poly_new(float f1, float f2);
// ---- items of slice s00a5d3c0 end

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
struct t_symbol_s00a5_e0f0 {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
inline bool operator==(const t_symbol_s00a5_e0f0& a, const t_symbol_s00a5_e0f0& b) { return a.mHash == b.mHash; }
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom {
    int a_type;
    union {
        float    w_float;
        t_symbol_s00a5_e0f0 w_symbol;
    } a_w;
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
    t_symbol_s00a5_e0f0      o_symfrom;      // +0x0c
    t_symbol_s00a5_e0f0      o_symto;        // +0x14
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_bagelem {            // 8
    t_bagelem* be_next;       // +0
    float      be_value;      // +4
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
extern t_symbol_s00a5_e0f0 gFloatSymbol;               // 0x16758c4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spPolyClass;                // 0x16756ac
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spBagClass;                 // 0x16756b4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol_s00a5_e0f0* gensym_s00a5_e0f0(t_symbol_s00a5_e0f0* out, const char* s);                          // 0xa675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class*  class_new6(t_symbol_s00a5_e0f0 name, void* newmethod, void* freemethod,
                    int size, int flags, int a1);                        // 0xa48e50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class*  class_new8(t_symbol_s00a5_e0f0 name, void* newmethod, void* freemethod,
                     int size, int flags, int a1, int a2, int a3);       // 0xa48f00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_doaddfloat(t_class* c, void* fn);                             // 0xa47f30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addmethod1(t_class* c, void* fn, t_symbol_s00a5_e0f0 name, int a1);      // 0xa48a30
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
void* outlet_new(void* owner, t_symbol_s00a5_e0f0 s);                              // 0xa49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* getbytes(int n, const char* tag);                                  // 0xa49610
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  freebytes(void* p, int n);                                         // 0xa49650
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool poly_setup();                               // 0xa5e7f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool bag_setup();                                // 0xa5ea70
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool makenote_setup();                           // 0xa5de00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool stripnote_setup();                          // 0xa5dfc0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* poly_new();                                // 0xa5e010
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* bag_new();                                 // 0xa5e8a0
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
namespace EA {
namespace Audio {
namespace Eapd {
struct t_poly {
    float g_value;   // +0
    int   g_pitch;   // +4
    int   g_voice;   // +8
};
}
}
}
// ---- items of slice s00a5e0f0 end

// @ 0x00a5de00
byte makenote_setup()
{
    t_symbol local;
    t_symbol* s = gensym(&local, "makenote");
    g_makenoteClass_16756b8 = class_new(s->s_name, s->s_thing, (void*)makenote_new,
                                        (void*)makenote_free_all, 0x3c, 0, 5, 5, 0);
    byte ok = g_makenoteClass_16756b8 != 0;
    byte b1 = class_doaddfloat(g_makenoteClass_16756b8, (void*)makenote_float);
    t_symbol* s2 = gensym(&local, "stop");
    byte b2 = class_addmethod(g_makenoteClass_16756b8, (void*)makenote_release_all,
                              (void*)s2->s_name, s2->s_thing, 0);
    t_symbol* s3 = gensym(&local, "clear");
    byte b3 = class_addmethod(g_makenoteClass_16756b8, (void*)makenote_free_all,
                              (void*)s3->s_name, s3->s_thing, 0);
    return (byte)(b3 & b2 & b1 & ok);
}

// @ 0x00a5deb0
void* stripnote_new()
{
    void* x = pd_new(g_stripnoteClass_16756b0);
    if (x != 0)
    {
        floatinlet_new(x, (char*)x + 0x28);
        *(void**)((char*)x + 0x2c) = outlet_new(x, g_floatSymbol_16758c4.s_name,
                                                g_floatSymbol_16758c4.s_thing);
        *(void**)((char*)x + 0x30) = outlet_new(x, g_floatSymbol_16758c4.s_name,
                                                g_floatSymbol_16758c4.s_thing);
    }
    return x;
}

// @ 0x00a5df10
void stripnote_float(void* x, float f)
{
    float velocity = *(float*)((char*)x + 0x28);
    if (velocity != 0.0f)
    {
        g_outletCount_167545c++;
        if (g_outletCount_167545c < 1000)
        {
            for (void** o = *(void***)(*(int*)((char*)x + 0x30) + 8); o != 0; o = (void**)*o)
                outlet_float(o[1], velocity);
        }
        if (g_outletCount_167545c < 1000)
        {
            for (void** o = *(void***)(*(int*)((char*)x + 0x2c) + 8); o != 0; o = (void**)*o)
                outlet_float(o[1], f);
        }
        g_outletCount_167545c--;
    }
}

// @ 0x00a5dfc0
byte stripnote_setup()
{
    t_symbol local;
    t_symbol* s = gensym(&local, "stripnote");
    g_stripnoteClass_16756b0 = class_new(s->s_name, s->s_thing, (void*)stripnote_new, 0, 0x34, 0, 0);
    byte ok = g_stripnoteClass_16756b0 != 0;
    byte added = class_doaddfloat(g_stripnoteClass_16756b0, (void*)stripnote_float);
    return (byte)(added & ok);
}

// @ 0x00a5e010
void* poly_new(float f1, float f2)
{
    int voices = (int)f1;
    void* x = pd_new(g_polyClass_16756ac);
    if (x != 0)
    {
        if (voices < 1)
            voices = 1;
        *(int*)((char*)x + 0x28) = voices;
        void** voice = (void**)getbytes(voices * 0xc, "EAPd/t_voice");
        *(void***)((char*)x + 0x2c) = voice;
        for (int i = voices; i != 0; --i)
        {
            *(float*)voice = 0.0f;
            voice[1] = 0;
            voice[2] = 0;
            voice += 3;
        }
        *(float*)((char*)x + 0x30) = 0.0f;
        *(int*)((char*)x + 0x40) = (f2 != 0.0f);
        floatinlet_new(x, (char*)x + 0x30);
        outlet_new(x, g_floatSymbol_16758c4.s_name, g_floatSymbol_16758c4.s_thing);
        *(void**)((char*)x + 0x34) = outlet_new(x, g_floatSymbol_16758c4.s_name,
                                                g_floatSymbol_16758c4.s_thing);
        *(void**)((char*)x + 0x38) = outlet_new(x, g_floatSymbol_16758c4.s_name,
                                                g_floatSymbol_16758c4.s_thing);
        *(int*)((char*)x + 0x3c) = 0;
    }
    return x;
}

// @ 0x00a5e0f0
namespace EA { namespace Audio { namespace Eapd {
void poly_doaddfloat(char* x, float f)
{
    static const float fOne = 1.0f;   // 0x1485720
    t_poly* pelts;
    int     nelt;
    float   sv;

    pelts = *(t_poly**)(x + 0x2c);
    nelt  = *(int*)(x + 0x28);
    sv    = *(float*)(x + 0x30);

    float  best  = 0.0f;
    float  bestf = 0.0f;
    t_poly* pb    = 0;
    t_poly* pf    = 0;
    int    bkey  = -1;
    int    fkey  = -1;

    if (sv > 0.0f) {
        if (0.0f < (float)nelt) {
            float   p = 0.0f;
            t_poly* pe = pelts;
            do {
                if (pe->g_pitch != 0) {
                    if ((unsigned)pe->g_voice < (unsigned)fkey) {
                        pf    = pe;
                        fkey  = pe->g_voice;
                        bestf = p;
                    }
                } else if ((unsigned)pe->g_voice < (unsigned)bkey) {
                    pb    = pe;
                    bkey  = pe->g_voice;
                    best  = p;
                }
                pe++;
                p += fOne;
            } while (p < (float)nelt);
        }
    } else {
        if (0.0f < (float)nelt) {
            float   p = 0.0f;
            t_poly* pe = pelts;
            do {
                if (pe->g_pitch != 0 && pe->g_value == f
                    && (unsigned)pe->g_voice < (unsigned)bkey) {
                    bkey = pe->g_voice;
                    pb   = pe;
                    best = p;
                }
                pe++;
                p += fOne;
            } while (p < (float)nelt);
        }
        if (pb) {
            t_outlet* o;
            pb->g_pitch = 0;
            pb->g_voice = *(int*)(x + 0x3c);
            (*(int*)(x + 0x3c))++;
            o = *(t_outlet**)(x + 0x38);
            outlet_cnt(o, 0.0f);
            o = *(t_outlet**)(x + 0x34);
            outlet_cnt(o, pb->g_value);
            o = *(t_outlet**)(x + 0xc);
            outlet_cnt(o, best + fOne);
            return;
        }
    }

    if (pb) {
        t_outlet* o = *(t_outlet**)(x + 0x38);
        outlet_cnt(o, sv);
        *(float*)pb = f;
        o = *(t_outlet**)(x + 0x34);
        outlet_cnt(o, f);
        o = *(t_outlet**)(x + 0xc);
        outlet_cnt(o, best + fOne);
        pb->g_pitch = 1;
        pb->g_voice = *(int*)(x + 0x3c);
        (*(int*)(x + 0x3c))++;
    } else if (pf) {
        if (*(int*)(x + 0x40) != 0) {
            t_outlet* o = *(t_outlet**)(x + 0x38);
            outlet_cnt(o, 0.0f);
            float pend = pf->g_value;
            o = *(t_outlet**)(x + 0x34);
            outlet_cnt(o, pend);
            o = *(t_outlet**)(x + 0xc);
            outlet_cnt(o, bestf + fOne);
            pf->g_value = f;
            o = *(t_outlet**)(x + 0x34);
            outlet_cnt(o, f);
            o = *(t_outlet**)(x + 0xc);
            outlet_cnt(o, bestf + fOne);
            pf->g_value = f;
            pf->g_voice = *(int*)(x + 0x3c);
            (*(int*)(x + 0x3c))++;
        }
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5e630
namespace EA { namespace Audio { namespace Eapd {
void poly_list(char* x, int argc, t_symbol_s00a5_e0f0 s, t_atom* argv)
{
    static const float fOne = 1.0f;   // 0x1485720
    t_poly* pelts;
    int     nelt;
    float   p;

    pelts = *(t_poly**)(x + 0x2c);
    nelt  = *(int*)(x + 0x28);
    p     = 0.0f;

    if (0.0f < (float)nelt) {
        t_poly* pe = pelts;
        do {
            if (pe->g_pitch != 0) {
                t_outlet* o = *(t_outlet**)(x + 0x38);
                outlet_cnt(o, 0.0f);
                float pend = pe->g_value;
                o = *(t_outlet**)(x + 0x34);
                outlet_cnt(o, pend);
                o = *(t_outlet**)(x + 0xc);
                outlet_cnt(o, p + fOne);
                pe->g_pitch = 0;
                pe->g_voice = *(int*)(x + 0x3c);
                (*(int*)(x + 0x3c))++;
            }
            p += fOne;
            pe++;
        } while (p < (float)nelt);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5e7a0
namespace EA { namespace Audio { namespace Eapd {
void poly_clear(char* x)
{
    if (*(int*)(x + 0x28) == 0)
        return;
    int     n  = *(int*)(x + 0x28);
    t_poly* pe = *(t_poly**)(x + 0x2c);
    do {
        n--;
        pe->g_voice = 0;
        pe->g_pitch = 0;
        pe++;
    } while (n != 0);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5e7d0
namespace EA { namespace Audio { namespace Eapd {
void poly_free(char* x)
{
    freebytes(*(void**)(x + 0x2c), *(int*)(x + 0x28) * 0xc);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5e7f0
namespace EA { namespace Audio { namespace Eapd {
bool poly_setup()
{
    t_symbol_s00a5_e0f0 s;
    t_symbol_s00a5_e0f0* sym;

    sym = gensym_s00a5_e0f0(&s, "poly");
    spPolyClass = class_new8(*sym, (void*)poly_new, (void*)poly_free, 0x44, 0, 5, 5, 0);
    bool ok = spPolyClass != 0;
    ok &= class_doaddfloat(spPolyClass, (void*)poly_doaddfloat);
    sym = gensym_s00a5_e0f0(&s, "stop");
    ok &= class_addmethod1(spPolyClass, (void*)poly_list, *sym, 0);
    sym = gensym_s00a5_e0f0(&s, "clear");
    ok &= class_addmethod1(spPolyClass, (void*)poly_clear, *sym, 0);
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5e8a0
namespace EA { namespace Audio { namespace Eapd {
void* bag_new()
{
    char* x = (char*)pd_new(spBagClass);
    if (x) {
        *(float*)(x + 0x28) = 0.0f;
        floatinlet_new(x, x + 0x28);
        outlet_new(x, gFloatSymbol);
        *(void**)(x + 0x2c) = 0;
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5e8f0
namespace EA { namespace Audio { namespace Eapd {
void bag_float(char* x, float f)
{
    if (*(float*)(x + 0x28) != 0.0f) {
        t_bagelem* el = (t_bagelem*)getbytes(8, "EAPd/t_bagelem");
        el->be_next  = 0;
        el->be_value = f;
        t_bagelem* p = *(t_bagelem**)(x + 0x2c);
        if (!p) {
            *(t_bagelem**)(x + 0x2c) = el;
        } else {
            t_bagelem* nxt;
            while ((nxt = p->be_next) != 0)
                p = nxt;
            p->be_next = el;
        }
    } else {
        t_bagelem* p = *(t_bagelem**)(x + 0x2c);
        if (!p)
            return;
        if (p->be_value == f) {
            *(t_bagelem**)(x + 0x2c) = p->be_next;
            freebytes(p, 8);
            return;
        }
        t_bagelem* prev = p;
        t_bagelem* q = p->be_next;
        while (q) {
            if (q->be_value == f) {
                prev->be_next = q->be_next;
                freebytes(q, 8);
                return;
            }
            prev = q;
            q = q->be_next;
        }
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5e9c0
namespace EA { namespace Audio { namespace Eapd {
void bag_flush(char* x)
{
    t_bagelem* el = *(t_bagelem**)(x + 0x2c);
    if (el) {
        do {
            float v = el->be_value;
            t_outlet* o = *(t_outlet**)(x + 0xc);
            outlet_cnt(o, v);
            *(t_bagelem**)(x + 0x2c) = el->be_next;
            freebytes(el, 8);
            el = *(t_bagelem**)(x + 0x2c);
        } while (el);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ea40
namespace EA { namespace Audio { namespace Eapd {
void bag_clear(char* x)
{
    t_bagelem* el = *(t_bagelem**)(x + 0x2c);
    while (el) {
        *(t_bagelem**)(x + 0x2c) = el->be_next;
        freebytes(el, 8);
        el = *(t_bagelem**)(x + 0x2c);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ea70
namespace EA { namespace Audio { namespace Eapd {
bool bag_setup()
{
    t_symbol_s00a5_e0f0 s;
    t_symbol_s00a5_e0f0* sym;

    sym = gensym_s00a5_e0f0(&s, "bag");
    spBagClass = class_new6(*sym, (void*)bag_new, (void*)bag_clear, 0x30, 0, 0);
    bool ok = spBagClass != 0;
    ok &= class_doaddfloat(spBagClass, (void*)bag_float);
    sym = gensym_s00a5_e0f0(&s, "flush");
    ok &= class_addmethod1(spBagClass, (void*)bag_flush, *sym, 0);
    sym = gensym_s00a5_e0f0(&s, "clear");
    ok &= class_addmethod1(spBagClass, (void*)bag_clear, *sym, 0);
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5eb20
namespace EA {
namespace Audio {
namespace Eapd {
bool x_note_setup()
{
    bool ok = makenote_setup() & 1;
    ok &= stripnote_setup();
    ok &= poly_setup();
    ok &= bag_setup();
    return ok;
}
}
}
}  // namespace EA::Audio::Eapd
