// src/game/SPAudio/eapdguistubs.cpp -- migrated from slice(s) s00a60ef0, s00a5fff0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdguistubs.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00a5fff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct t_atom {
    int a_type;                 // +0
    union {
        float    w_float;       // +4
        t_symbol w_symbol;      // +4
    } a_w;
};
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
    void*         o_owner;        // +0x00
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
extern int       gOutletCount;             // 0x167545c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol  gFloatSymbol;             // 0x16758c4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol  gBangSymbol;              // 0x16758b4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol  sGuiEmptySymbol;          // 0x167580c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class*  spToggleClass;            // 0x1675808
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class*  spBngClass;               // 0x1675828
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol* gensym(t_symbol* out, const char* s);                          // 0xa675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class*  class_new7(t_symbol name, void* newmethod, void* freemethod,
                     int size, int flags, int a1, int a2);               // 0xa48ea0
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
bool class_addbang(t_class* c, void* fn);                                // 0xa47f10
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addsymbol(t_class* c, void* fn);                              // 0xa47f50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addlist(t_class* c, void* fn);                                // 0xa47f70
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addanything(t_class* c, void* fn);                            // 0xa47f90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addmethod1(t_class* c, void* fn, t_symbol name, int a1);      // 0xa48a30
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
void* outlet_new(void* owner, t_symbol name);                            // 0xa49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  outlet_bang(void* o);                                              // 0xa49da0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  outlet_float(void* o, float f);                                    // 0xa49570
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_send_bang(int hash, int name);                                  // 0xa67210
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_send_float(int hash, int name, float f);                        // 0xa67230
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
float    atom_getfloat_at(int idx, int argc, t_atom* argv);              // 0xa468f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol* atom_getsymbol_at(t_symbol* out, int idx, int argc, t_atom* argv); // 0xa46950
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct Toggle {
    uint32_t  pad0[3];        // +0x00
    t_outlet* mpOutlet;       // +0x0c
    uint32_t  pad10[6];       // +0x10
    bool      mLoadbangFlag;  // +0x28
    t_symbol  mSym;           // +0x2c
    t_symbol  mSymTo;         // +0x34
    bool      mState;         // +0x3c
    float     mValue;         // +0x40
};
}
}
}
// ---- items of slice s00a5fff0 end

// ---- items of slice s00a60ef0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uint;
typedef unsigned char  byte;
namespace Eapd {
struct t_symbol_s00a6_0ef0 {                 // by-value pair
    uint        mHash;            // +0x00
    const char* mpName;           // +0x04
};
}
namespace Eapd {
struct t_class_s00a6_0ef0;                   // opaque
}
namespace Eapd {
struct t_atom_s00a6_0ef0 { uint a; uint b; };        // 8 bytes
}
namespace Eapd {
struct t_outlet_s00a6_0ef0;                  // opaque
}
namespace Eapd {
struct TX {                       // generic object with the common tail
    uint   mGobj[0x28 / 4];       // +0x00
    void*  mpA28;                 // +0x28
    void*  mpB2c;                 // +0x2c
    int    mC30;                  // +0x30
    int    mD34;                  // +0x34
    void*  mpE38;                 // +0x38
    int    mF3c;                  // +0x3c
};
}
namespace Eapd {
t_class_s00a6_0ef0* gpToggleClass;           // 0x01675808
}
namespace Eapd {
t_class_s00a6_0ef0* gpSliderClass;           // 0x01675824
}
namespace Eapd {
t_symbol_s00a6_0ef0 sGuiEmpty;               // 0x0167580c
}
namespace Eapd {
t_symbol_s00a6_0ef0 sHslider;                // 0x01675814
}
namespace Eapd {
t_symbol_s00a6_0ef0 sHsl;                    // 0x0167581c
}
namespace Eapd {
t_symbol_s00a6_0ef0 gFloatSymbol_s00a6_0ef0;            // 0x016758c4
}
namespace Eapd {
uint     gOutletCount_s00a6_0ef0;            // 0x0167545c
}
namespace Eapd {
const float kfOne    = 1.0f;      // 0x01485720
}
namespace Eapd {
const float kfHundred= 100.0f;    // 0x013ec4d0
}
namespace Eapd {
const float kf127    = 127.0f;    // 0x0140d204
}
namespace Eapd {
t_symbol_s00a6_0ef0* gensym(t_symbol_s00a6_0ef0* out, const char* s);                       // 0x00a675f0
}
namespace Eapd {
t_class_s00a6_0ef0*  class_new(t_symbol_s00a6_0ef0 name, void* newmethod, void* freemethod,
                    int size, int a5, int a6, int a7);                // 0x00a48ea0
}
namespace Eapd {
byte      class_addcreator(void* newmethod, t_symbol_s00a6_0ef0 name, int a3, int a4); // 0x00a48e00
}
namespace Eapd {
byte      class_addbang(t_class_s00a6_0ef0* c, void* fn);                        // 0x00a47f10
}
namespace Eapd {
byte      class_doaddfloat(t_class_s00a6_0ef0* c, void* fn);                     // 0x00a47f30
}
namespace Eapd {
bool      class_addmethod(t_class_s00a6_0ef0* c, void* fn, t_symbol_s00a6_0ef0 name, int a4);   // 0x00a48a30
}
namespace Eapd {
void*     pd_new(t_class_s00a6_0ef0* c);                                         // 0x00a49390
}
namespace Eapd {
void*     outlet_new(void* owner, t_symbol_s00a6_0ef0 s);                        // 0x00a49d30
}
namespace Eapd {
void      outlet_float(t_outlet_s00a6_0ef0* o, float f);                         // 0x00a49570
}
namespace Eapd {
int       atom_getint_at(int idx, int argc, t_atom_s00a6_0ef0* argv);            // 0x00a46920
}
namespace Eapd {
float     atom_getfloat_at(int idx, int argc, t_atom_s00a6_0ef0* argv);          // 0x00a468f0
}
namespace Eapd {
t_symbol_s00a6_0ef0* atom_getsymbol_at(t_symbol_s00a6_0ef0* out, int idx, int argc, t_atom_s00a6_0ef0* argv); // 0x00a46950
}
namespace Eapd {
void      pd_send_float(uint sym, uint a, float f);                   // 0x00a67230
}
namespace Eapd {
int*  toggle_new(t_symbol_s00a6_0ef0 s1, t_symbol_s00a6_0ef0 s2, int argc, t_atom_s00a6_0ef0* argv);   // 0x00a60ce0
}
namespace Eapd {
void  toggle_bang(void* x);                                           // 0x00a60e70
}
namespace Eapd {
void  toggle_float(void* x, float f);                                 // 0x00a60e90
}
namespace Eapd {
void  toggle_loadbang(void* x);                                       // 0x00a60ed0
}
namespace Eapd {
void* slider_new(t_symbol_s00a6_0ef0 s1, t_symbol_s00a6_0ef0 s2, int argc, t_atom_s00a6_0ef0* argv);   // 0x00a60fd0
}
// ---- items of slice s00a60ef0 end

// @ 0x00a60aa0
namespace EA { namespace Audio { namespace Eapd {
void* bng_new(void* a, void* b, int argc, t_atom* argv)
{
    char* x = (char*)pd_new(spBngClass);
    if (x == 0)
        return x;

    outlet_new(x, gBangSymbol);
    *(char*)(x + 0x28) = 0;
    *(t_symbol*)(x + 0x2c) = sGuiEmptySymbol;
    *(t_symbol*)(x + 0x34) = sGuiEmptySymbol;

    if (argc == 0xe) {
        t_symbol  tmp;
        *(bool*)(x + 0x28) = 0.0f != atom_getfloat_at(3, 0xe, argv);
        t_symbol* ts = atom_getsymbol_at(&tmp, 4, 0xe, argv);
        *(t_symbol*)(x + 0x2c) = *ts;
        ts = atom_getsymbol_at(&tmp, 5, 0xe, argv);
        *(t_symbol*)(x + 0x34) = *ts;
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a60b70
namespace EA { namespace Audio { namespace Eapd {
void bng_any(char* x)
{
    outlet_bang(*(void**)(x + 0xc));
    if (*(int*)(x + 0x2c) != sGuiEmptySymbol.mHash
        && *(int*)(x + 0x2c) != *(int*)(x + 0x34))
        pd_send_bang(*(int*)(x + 0x2c), *(int*)(x + 0x30));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a60bb0
namespace EA { namespace Audio { namespace Eapd {
void bng_loadbang(char* x)
{
    if (*(char*)(x + 0x28) == 0)
        return;
    outlet_bang(*(void**)(x + 0xc));
    if (*(int*)(x + 0x2c) != sGuiEmptySymbol.mHash
        && *(int*)(x + 0x2c) != *(int*)(x + 0x34))
        pd_send_bang(*(int*)(x + 0x2c), *(int*)(x + 0x30));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a60bf0
namespace EA {
namespace Audio {
namespace Eapd {
bool g_bng_setup()
{
    t_symbol  s;
    t_symbol* sym;

    sym = gensym(&s, "empty");
    sGuiEmptySymbol = *sym;
    sym = gensym(&s, "bng");
    spBngClass = class_new7(*sym, (void*)bng_new, 0, 0x3c, 0, 9, 0);
    bool ok = spBngClass != 0;
    ok &= class_addbang(spBngClass, (void*)bng_any);
    ok &= class_doaddfloat(spBngClass, (void*)bng_any);
    ok &= class_addsymbol(spBngClass, (void*)bng_any);
    ok &= class_addlist(spBngClass, (void*)bng_any);
    ok &= class_addanything(spBngClass, (void*)bng_any);
    sym = gensym(&s, "loadbang");
    ok &= class_addmethod1(spBngClass, (void*)bng_loadbang, *sym, 0);
    return ok;
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a60ce0
namespace EA { namespace Audio { namespace Eapd {
void* toggle_new(void* a, void* b, int argc, t_atom* argv)
{
    char* x = (char*)pd_new(spToggleClass);
    if (x == 0)
        return x;

    outlet_new(x, gFloatSymbol);
    *(char*)(x + 0x28) = 0;
    *(t_symbol*)(x + 0x2c) = sGuiEmptySymbol;
    *(t_symbol*)(x + 0x34) = sGuiEmptySymbol;
    *(char*)(x + 0x3c)  = 0;
    *(float*)(x + 0x40) = 1.0f;

    if (argc == 0xe) {
        t_symbol  tmp;
        *(bool*)(x + 0x28) = 0.0f != atom_getfloat_at(1, 0xe, argv);
        t_symbol* ts = atom_getsymbol_at(&tmp, 2, 0xe, argv);
        *(t_symbol*)(x + 0x2c) = *ts;
        ts = atom_getsymbol_at(&tmp, 3, 0xe, argv);
        *(t_symbol*)(x + 0x34) = *ts;
        *(bool*)(x + 0x3c) = 0.0f != atom_getfloat_at(0xc, 0xe, argv);
        *(float*)(x + 0x40) = atom_getfloat_at(0xd, 0xe, argv);
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a60df0
namespace EA { namespace Audio { namespace Eapd {
void __fastcall toggle_output(Toggle* x)
{
    float v = x->mState ? x->mValue : 0.0f;

    if (++gOutletCount < 1000) {
        t_outlet* o = x->mpOutlet;
        for (t_outconnect* oc = o->o_connections; oc != 0; oc = oc->oc_next)
            outlet_float(oc->oc_to, v);
    }
    gOutletCount--;

    int sym = x->mSym.mHash;
    if (sym != sGuiEmptySymbol.mHash && sym != x->mSymTo.mHash)
        pd_send_float(sym, (int)x->mSym.mpName, v);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a60e70
namespace EA { namespace Audio { namespace Eapd {
void toggle_bang(char* x)
{
    *(char*)(x + 0x3c) = *(char*)(x + 0x3c) == 0;
    toggle_output((Toggle*)x);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a60e90
namespace EA { namespace Audio { namespace Eapd {
void toggle_float(char* x, float f)
{
    if (0.0f != f) {
        *(char*)(x + 0x3c)  = 1;
        *(float*)(x + 0x40) = f;
        toggle_output((Toggle*)x);
    } else {
        *(char*)(x + 0x3c) = 0;
        toggle_output((Toggle*)x);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a60ed0
namespace EA { namespace Audio { namespace Eapd {
void toggle_loadbang(char* x)
{
    if (*(char*)(x + 0x28) != 0)
        toggle_output((Toggle*)x);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a60ef0
namespace Eapd {
byte g_toggle_setup(void)
{
    t_symbol_s00a6_0ef0 s;
    t_symbol_s00a6_0ef0* p = gensym(&s, "empty");
    sGuiEmpty = *p;
    p = gensym(&s, "toggle");
    gpToggleClass = class_new(*p, (void*)toggle_new, 0, 0x44, 0, 9, 0);
    byte ok = gpToggleClass != 0;
    ok &= 1;
    p = gensym(&s, "tgl");
    ok &= class_addcreator((void*)toggle_new, *p, 9, 0);
    ok &= class_addbang(gpToggleClass, (void*)toggle_bang);
    ok &= class_doaddfloat(gpToggleClass, (void*)toggle_float);
    p = gensym(&s, "loadbang");
    ok &= class_addmethod(gpToggleClass, (void*)toggle_loadbang, *p, 0);
    return ok;
}
}  // namespace Eapd

// @ 0x00a60fd0
namespace Eapd {
void* slider_new(t_symbol_s00a6_0ef0 s1, t_symbol_s00a6_0ef0 s2, int argc, t_atom_s00a6_0ef0* argv)
{
    TX* x = (TX*)pd_new(gpSliderClass);
    if (x == 0)
        return x;
    outlet_new(x, gFloatSymbol_s00a6_0ef0);
    *(float*)((char*)x + 0x40) = 0.0f;
    *(float*)((char*)x + 0x44) = kf127;
    *(byte*)((char*)x + 0x28) = 0;
    *(t_symbol_s00a6_0ef0*)((char*)x + 0x2c) = sGuiEmpty;
    *(t_symbol_s00a6_0ef0*)((char*)x + 0x34) = sGuiEmpty;
    *(float*)((char*)x + 0x3c) = 0.0f;
    if (argc < 0x12)
        return x;
    *(float*)((char*)x + 0x40) = atom_getfloat_at(2, argc, argv);
    *(float*)((char*)x + 0x44) = atom_getfloat_at(3, argc, argv);
    *(byte*)((char*)x + 0x28) = atom_getfloat_at(5, argc, argv) != 0.0f;
    *(t_symbol_s00a6_0ef0*)((char*)x + 0x2c) = *atom_getsymbol_at(&s1, 6, argc, argv);
    *(t_symbol_s00a6_0ef0*)((char*)x + 0x34) = *atom_getsymbol_at(&s2, 7, argc, argv);
    float f = atom_getfloat_at(0x10, argc, argv);
    *(float*)((char*)x + 0x3c) = f;
    if (*(byte*)((char*)x + 0x28) != 0 && atom_getint_at(0x12, argc, argv) < 1) {
        int idx = (s1.mHash == sHslider.mHash || s1.mHash == sHsl.mHash) ? 0 : 1;
        float v = atom_getfloat_at(idx, argc, argv);
        float lo = *(float*)((char*)x + 0x40);
        float hi = *(float*)((char*)x + 0x44);
        *(float*)((char*)x + 0x3c) = (hi - lo) * *(float*)((char*)x + 0x3c)
                                     / ((v - kfOne) * kfHundred) + lo;
    }
    float a = *(float*)((char*)x + 0x40);
    float b = *(float*)((char*)x + 0x44);
    if (b < a) {
        *(float*)((char*)x + 0x40) = b;
        *(float*)((char*)x + 0x44) = a;
    }
    return x;
}
}  // namespace Eapd

// @ 0x00a61180
namespace Eapd {
void slider_float(TX* x)
{
    float f = *(float*)((char*)x + 0x3c);
    void** p = (void**)(*(int*)((char*)x + 0xc) + 8);
    int n = ++*(int*)&gOutletCount_s00a6_0ef0;
    (void)n;
    if (gOutletCount_s00a6_0ef0 < 1000) {
        for (void** o = (void**)*p; o != 0; o = (void**)*o)
            outlet_float((t_outlet_s00a6_0ef0*)o[1], f);
    }
    gOutletCount_s00a6_0ef0--;
    uint sym = *(uint*)((char*)x + 0x2c);
    if (sym != sGuiEmpty.mHash && sym != *(uint*)((char*)x + 0x34))
        pd_send_float(sym, *(uint*)((char*)x + 0x30), *(float*)((char*)x + 0x3c));
}
}  // namespace Eapd

// @ 0x00a61200
namespace Eapd {
void slider_setfloat(TX* x, float v)
{
    *(float*)((char*)x + 0x3c) = v;
    float lim = *(float*)((char*)x + 0x44);
    if (lim < v) {
        *(float*)((char*)x + 0x3c) = lim;
    } else {
        lim = *(float*)((char*)x + 0x40);
        if (v < lim)
            *(float*)((char*)x + 0x3c) = *(float*)((char*)x + 0x44);
    }
    slider_float(x);
}
}  // namespace Eapd

// @ 0x00a61250
namespace Eapd {
byte g_hslider_setup(void)
{
    t_symbol_s00a6_0ef0 s;
    t_symbol_s00a6_0ef0* p = gensym(&s, "empty");
    sGuiEmpty = *p;
    p = gensym(&s, "hslider");
    sHslider = *p;
    p = gensym(&s, "hsl");
    sHsl = *p;
    p = gensym(&s, "hslider");
    gpSliderClass = class_new(*p, (void*)slider_new, 0, 0x48, 0, 9, 0);
    byte ok = gpSliderClass != 0;
    ok &= 1;
    p = gensym(&s, "vslider");
    ok &= class_addcreator((void*)slider_new, *p, 9, 0);
    p = gensym(&s, "hsl");
    ok &= class_addcreator((void*)slider_new, *p, 9, 0);
    p = gensym(&s, "vsl");
    ok &= class_addcreator((void*)slider_new, *p, 9, 0);
    ok &= class_addbang(gpSliderClass, (void*)slider_float);
    ok &= class_doaddfloat(gpSliderClass, (void*)slider_setfloat);
    p = gensym(&s, "loadbang");
    ok &= class_addmethod(gpSliderClass, (void*)0x00a61230, *p, 0);
    return ok;
}
}  // namespace Eapd
