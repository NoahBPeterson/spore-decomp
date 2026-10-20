// Slice s00a5e0f0: EA::Audio::Eapd (EA's embedded Pure Data) - x_arithmetic.c style
// multi-input objects: poly, bag, random/frandom, print and the spin/clock objects.
// (0xa5e0f0-0xa5f061)
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

struct t_class;
typedef t_class* t_pd;

// t_symbol is passed by value (hash, name); symbols compare by their first word only.
struct t_symbol {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};
inline bool operator==(const t_symbol& a, const t_symbol& b) { return a.mHash == b.mHash; }

struct t_atom {
    int a_type;
    union {
        float    w_float;
        t_symbol w_symbol;
    } a_w;
};

struct t_object;
struct t_inlet;
struct t_outlet;

struct t_outconnect {         // 8
    t_outconnect* oc_next;    // +0
    t_outlet*     oc_to;      // +4
};

struct t_outlet {             // 0x1c
    t_object*     o_owner;        // +0x00
    t_outlet*     o_next;         // +0x04
    t_outconnect* o_connections;  // +0x08
    t_symbol      o_symfrom;      // +0x0c
    t_symbol      o_symto;        // +0x14
};

struct t_bagelem {            // 8
    t_bagelem* be_next;       // +0
    float      be_value;      // +4
};

// ---------------------------------------------------------------- globals
extern int gOutletCount;                    // 0x167545c
extern t_symbol gEmptySymbol;               // 0x167589c
extern t_symbol gFloatSymbol;               // 0x16758c4
extern t_class* spPolyClass;                // 0x16756ac
extern t_class* spBagClass;                 // 0x16756b4
extern t_class* spPrintClass;               // 0x16756bc
extern t_class* spRandomClass;              // 0x16756c0
extern t_class* spFloatRandomClass;         // 0x16756c4
extern void*    spSpinClass;                // 0x16756c8
extern void*    spFloatSpinClass;           // 0x16756cc
extern t_class* spDelayClass;               // 0x16756d0
extern t_class* spLineClass;                // 0x16756d4
extern t_class* spTimerClass;               // 0x16756d8

// --------------------------------------------------------------- callees
t_symbol* gensym(t_symbol* out, const char* s);                          // 0xa675f0
t_class*  class_new6(t_symbol name, void* newmethod, void* freemethod,
                    int size, int flags, int a1);                        // 0xa48e50
t_class*  class_new7(t_symbol name, void* newmethod, void* freemethod,
                     int size, int flags, int a1, int a2);               // 0xa48ea0
t_class*  class_new8(t_symbol name, void* newmethod, void* freemethod,
                     int size, int flags, int a1, int a2, int a3);       // 0xa48f00
bool class_doaddfloat(t_class* c, void* fn);                             // 0xa47f30
bool class_addbang(t_class* c, void* fn);                                // 0xa47f10
bool class_addsymbol(t_class* c, void* fn);                              // 0xa47f50
bool class_addlist(t_class* c, void* fn);                                // 0xa47f70
bool class_addanything(t_class* c, void* fn);                            // 0xa47f90
bool class_addmethod1(t_class* c, void* fn, t_symbol name, int a1);      // 0xa48a30
bool class_addmethod2(t_class* c, void* fn, t_symbol name, int a1, int a2);  // 0xa48a80
void class_sethelpsymbol(t_class* c, t_symbol name);                     // 0xa47fc0
void* pd_new(t_class* c);                                                // 0xa49390
void  outlet_float(void* to, float f);                                   // 0xa49570
void* floatinlet_new(void* owner, void* dest);                           // 0xa49a00
void* outlet_new(void* owner, t_symbol s);                              // 0xa49d30
bool  clock_ispaused(void* clock);                                       // 0xa491d0
void  clock_delay(void* clock, float f);                                 // 0xa491e0
void  clock_unset(void* clock);                                          // 0xa490b0
void* getbytes(int n, const char* tag);                                  // 0xa49610
void  freebytes(void* p, int n);                                         // 0xa49650

// EA system random stream (EA::Random::RandomLinearCongruential, 0x30 bytes).
struct RandomLinearCongruential {
    char pad[0x2c];
    unsigned RandomUint32Uniform();            // 0x9360b0
    unsigned RandomUint32UniformN(unsigned n); // 0xa68fb0
    void     SetSeed(unsigned seed);           // 0x936090
    float    NextFloat();                      // 0xa69020 (thiscall)
};
extern RandomLinearCongruential sSystemRandom;   // 0x16756fc

// EA::Thread
unsigned GetThreadTime();                        // 0x94d340

// Prints argc atoms from argv into buf (PD's "post" formatting helper).
void postargs(int argc, t_atom* argv, char* buf, int n);  // 0xa46bc0

bool poly_setup();                               // 0xa5e7f0
bool bag_setup();                                // 0xa5ea70
bool makenote_setup();                           // 0xa5de00
bool stripnote_setup();                          // 0xa5dfc0
bool x_random_setup();                           // 0xa5eea0
void* poly_new();                                // 0xa5e010
void* bag_new();                                 // 0xa5e8a0
void* print_new(t_symbol s);                      // 0xa5eb50
void  sys_gui(const char* cmd);                  // 0xc2e4e0

} } }  // namespace EA::Audio::Eapd

namespace EA { namespace Audio { namespace Eapd {

// Sends `v` out of the outlet list `lst`, guarded by the outlet-nesting counter
// (PD's outlet_float wrapper: bail out past 1000 nested sends).
__forceinline void outlet_cnt(t_outlet* lst, float v)
{
    if (++gOutletCount < 1000) {
        t_outconnect* oc;
        for (oc = lst->o_connections; oc; oc = oc->oc_next)
            outlet_float(oc->oc_to, v);
    }
    gOutletCount--;
}

// ============================================================ poly object
// x points at the t_object header (0x2c bytes) followed by the poly fields;
// the layout below uses the raw base pointer with explicit offsets.

// A poly voice.
struct t_poly {
    float g_value;   // +0
    int   g_pitch;   // +4
    int   g_voice;   // +8
};

// @ 0x00a5e0f0
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

// @ 0x00a5e630
void poly_list(char* x, int argc, t_symbol s, t_atom* argv)
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

// @ 0x00a5e7a0
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

// @ 0x00a5e7d0  EA::Audio::Eapd::poly_free
void poly_free(char* x)
{
    freebytes(*(void**)(x + 0x2c), *(int*)(x + 0x28) * 0xc);
}

// @ 0x00a5e7f0  EA::Audio::Eapd::poly_setup
bool poly_setup()
{
    t_symbol s;
    t_symbol* sym;

    sym = gensym(&s, "poly");
    spPolyClass = class_new8(*sym, (void*)poly_new, (void*)poly_free, 0x44, 0, 5, 5, 0);
    bool ok = spPolyClass != 0;
    ok &= class_doaddfloat(spPolyClass, (void*)poly_doaddfloat);
    sym = gensym(&s, "stop");
    ok &= class_addmethod1(spPolyClass, (void*)poly_list, *sym, 0);
    sym = gensym(&s, "clear");
    ok &= class_addmethod1(spPolyClass, (void*)poly_clear, *sym, 0);
    return ok;
}

// ============================================================= bag object
// @ 0x00a5e8a0  EA::Audio::Eapd::bag_new
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

// @ 0x00a5e8f0  EA::Audio::Eapd::bag_float
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

// @ 0x00a5e9c0
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

// @ 0x00a5ea40  EA::Audio::Eapd::bag_clear
void bag_clear(char* x)
{
    t_bagelem* el = *(t_bagelem**)(x + 0x2c);
    while (el) {
        *(t_bagelem**)(x + 0x2c) = el->be_next;
        freebytes(el, 8);
        el = *(t_bagelem**)(x + 0x2c);
    }
}

// @ 0x00a5ea70  EA::Audio::Eapd::bag_setup
bool bag_setup()
{
    t_symbol s;
    t_symbol* sym;

    sym = gensym(&s, "bag");
    spBagClass = class_new6(*sym, (void*)bag_new, (void*)bag_clear, 0x30, 0, 0);
    bool ok = spBagClass != 0;
    ok &= class_doaddfloat(spBagClass, (void*)bag_float);
    sym = gensym(&s, "flush");
    ok &= class_addmethod1(spBagClass, (void*)bag_flush, *sym, 0);
    sym = gensym(&s, "clear");
    ok &= class_addmethod1(spBagClass, (void*)bag_clear, *sym, 0);
    return ok;
}

// @ 0x00a5eb20  EA::Audio::Eapd::x_note_setup
bool x_note_setup()
{
    bool ok = makenote_setup() & 1;
    ok &= stripnote_setup();
    ok &= poly_setup();
    ok &= bag_setup();
    return ok;
}

// =========================================================== print object
// @ 0x00a5eb50  EA::Audio::Eapd::print_new
void* print_new(t_symbol s)
{
    char* x = (char*)pd_new(spPrintClass);
    if (x) {
        if (s.mpName[0] != '\0') {
            *(t_symbol*)(x + 0x28) = s;
        } else {
            t_symbol sym;
            *(t_symbol*)(x + 0x28) = *gensym(&sym, "print");
        }
    }
    return x;
}

// @ 0x00a5ebb0
void print_anything(char* x, t_symbol s, int argc, t_atom* argv)
{
    char buf[1000];
    postargs(argc, argv, buf, 1000);
}

// @ 0x00a5ebe0  EA::Audio::Eapd::print_setup
bool print_setup()
{
    t_symbol s;
    t_symbol* sym;

    sym = gensym(&s, "print");
    spPrintClass = class_new7(*sym, (void*)print_new, (void*)0, 0x30, 0, 6, 0);
    bool ok = spPrintClass != 0;
    ok &= class_addbang(spPrintClass, (void*)sys_gui);
    ok &= class_doaddfloat(spPrintClass, (void*)sys_gui);
    ok &= class_addsymbol(spPrintClass, (void*)sys_gui);
    ok &= class_addlist(spPrintClass, (void*)print_anything);
    ok &= class_addanything(spPrintClass, (void*)print_anything);
    return ok;
}

// ======================================================== random objects
// @ 0x00a5ec90  EA::Audio::Eapd::random_uniform
unsigned random_uniform(unsigned n)
{
    return sSystemRandom.RandomUint32UniformN(n);
}

// @ 0x00a5ecb0  EA::Audio::Eapd::random_seed
void random_seed(unsigned seed)
{
    sSystemRandom.SetSeed(seed);
}

// @ 0x00a5ecc0
void random_seed_method(char* x, t_symbol s, int argc, t_atom* argv)
{
    (*(RandomLinearCongruential*)(x + 0x2c)).SetSeed(*(unsigned*)((char*)argv + 4));
}

// @ 0x00a5ece0
void* random_new(float f)
{
    char* x = (char*)pd_new(spRandomClass);
    if (x) {
        *(float*)(x + 0x28) = f;
        (*(RandomLinearCongruential*)(x + 0x2c)).SetSeed(sSystemRandom.RandomUint32Uniform());
        floatinlet_new(x, x + 0x28);
        outlet_new(x, gFloatSymbol);
    }
    return x;
}

// @ 0x00a5ed40
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

// @ 0x00a5eda0
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

// @ 0x00a5ee30
void frandom_bang(char* x)
{
    if (*(float*)(x + 0x28) < 0.0f)
        *(float*)(x + 0x28) = 0.0f;
    float v = *(float*)(x + 0x28) * (*(RandomLinearCongruential*)(x + 0x2c)).NextFloat();
    t_outlet* o = *(t_outlet**)(x + 0xc);
    outlet_cnt(o, v);
}

// @ 0x00a5eea0  EA::Audio::Eapd::x_random_setup
bool x_random_setup()
{
    t_symbol s;
    t_symbol* sym;

    sym = gensym(&s, "random");
    spRandomClass = class_new7(*sym, (void*)random_new, (void*)0, 0x30, 0, 5, 0);
    bool ok = spRandomClass != 0;
    ok &= class_addbang(spRandomClass, (void*)random_bang);
    sym = gensym(&s, "seed");
    ok &= class_addmethod2(spRandomClass, (void*)random_seed_method, *sym, 1, 0);

    sym = gensym(&s, "frandom");
    spFloatRandomClass = class_new7(*sym, (void*)frandom_new, (void*)0, 0x30, 0, 5, 0);
    ok &= spFloatRandomClass != 0;
    ok &= class_addbang(spFloatRandomClass, (void*)frandom_bang);
    sym = gensym(&s, "seed");
    ok &= class_addmethod2(spFloatRandomClass, (void*)random_seed_method, *sym, 1, 0);
    sym = gensym(&s, "random");
    class_sethelpsymbol(spFloatRandomClass, *sym);

    random_seed(GetThreadTime());
    return ok;
}

// ======================================================== spin / timer objects
// @ 0x00a5efd0
void spin_bang(char* x)
{
    if (!clock_ispaused(*(void**)(x + 0x28)))
        clock_delay(*(void**)(x + 0x28), *(float*)(x + 0x2c));
}

// @ 0x00a5f000
void spin_stop(char* x)
{
    if (!clock_ispaused(*(void**)(x + 0x28)))
        clock_unset(*(void**)(x + 0x28));
}

// @ 0x00a5f030
void spin_float(char* x, float f)
{
    if (f < 0.0f)
        f = 0.0f;
    if (!clock_ispaused(*(void**)(x + 0x28)))
        *(float*)(x + 0x2c) = f;
}

} } }  // namespace EA::Audio::Eapd
