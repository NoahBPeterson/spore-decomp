// Slice s00a60ef0 - EA::Audio::Eapd GUI externals (toggle / slider / inlet / outlet /
// menu / table), EA's embedded Pure Data.  /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast.
//
// Every object is a "pd" object: a t_gobj header (0..0x27), then per-class fields.
// Symbols are passed and returned *by value* as an (hash, char*) pair.
#include "types.h"

typedef unsigned int   uint;
typedef unsigned char  byte;
typedef unsigned short ushort;

namespace Eapd {

// ---------------------------------------------------------------------------
// Core types
// ---------------------------------------------------------------------------
struct t_symbol {                 // by-value pair
    uint        mHash;            // +0x00
    const char* mpName;           // +0x04
};

struct t_class;                   // opaque
struct t_atom { uint a; uint b; };        // 8 bytes
struct t_glist;                   // opaque canvas
struct t_inlet;                   // opaque
struct t_outlet;                  // opaque

// A pd object header; concrete objects extend this.
struct Tobj {
    uint mGobj[0x28 / 4];         // +0x00 .. +0x27
};
struct TX {                       // generic object with the common tail
    uint   mGobj[0x28 / 4];       // +0x00
    void*  mpA28;                 // +0x28
    void*  mpB2c;                 // +0x2c
    int    mC30;                  // +0x30
    int    mD34;                  // +0x34
    void*  mpE38;                 // +0x38
    int    mF3c;                  // +0x3c
};

// ---------------------------------------------------------------------------
// Globals (see nonmatching notes for addresses)
// ---------------------------------------------------------------------------
t_class* gpToggleClass;           // 0x01675808
t_class* gpSliderClass;           // 0x01675824
t_class* gpInletClass;            // 0x0167582c
t_class* gpOutletClass;           // 0x01675830
t_class* gpMenuClass;             // 0x01675834
t_class* gpTableClass;            // 0x01675838
t_class* gpRandWeightedClass;     // 0x0167583c
t_symbol sGuiEmpty;               // 0x0167580c
t_symbol sHslider;                // 0x01675814
t_symbol sHsl;                    // 0x0167581c
t_symbol gEmptySymbol;            // 0x0167589c
t_symbol gFloatSymbol;            // 0x016758c4
t_symbol gAnythingSymbol;         // 0x016758cc
t_symbol sHashA;                  // 0x01675848
t_symbol sRandWeighted;           // 0x01675854
uint     gOutletCount;            // 0x0167545c

const float kfOne    = 1.0f;      // 0x01485720
const float kfHundred= 100.0f;    // 0x013ec4d0
const float kf127    = 127.0f;    // 0x0140d204

// ---------------------------------------------------------------------------
// External helpers (defined elsewhere in the binary)
// ---------------------------------------------------------------------------
t_symbol* gensym(t_symbol* out, const char* s);                       // 0x00a675f0
t_class*  class_new(t_symbol name, void* newmethod, void* freemethod,
                    int size, int a5, int a6, int a7);                // 0x00a48ea0
byte      class_addcreator(void* newmethod, t_symbol name, int a3, int a4); // 0x00a48e00
byte      class_addbang(t_class* c, void* fn);                        // 0x00a47f10
byte      class_doaddfloat(t_class* c, void* fn);                     // 0x00a47f30
byte      class_addsymbol(t_class* c, void* fn);                      // 0x00a47f50
byte      class_addlist(t_class* c, void* fn);                        // 0x00a47f70
byte      class_addanything(t_class* c, void* fn);                    // 0x00a47f90
bool      class_addmethod_m(t_class* c, void* fn, t_symbol name, int a4, int a5); // 0x00a48a80 (trailing free method)
bool      class_addmethod(t_class* c, void* fn, t_symbol name, int a4);   // 0x00a48a30
bool      class_sethelpsymbol(t_class* c, t_symbol name);             // 0x00a47fc0
void*     pd_new(t_class* c);                                         // 0x00a49390
void*     outlet_new(void* owner, t_symbol s);                        // 0x00a49d30
void*     inlet_new(void* owner, void* owner2, t_symbol s, t_symbol s2,
                    t_symbol s3, t_symbol s4);                        // 0x00a49740
void*     canvas_getcurrent();                                        // 0x00a4a430
t_inlet*  canvas_addinlet(t_glist* g, void* owner, t_symbol s);          // 0x00a4e030
t_outlet* canvas_addoutlet(t_glist* g, void* owner, t_symbol s);         // 0x00a4e0b0
void      canvas_rminlet(t_glist* g, t_inlet* i);                     // 0x00a4d440
void      canvas_rmoutlet(t_glist* g, t_outlet* o);                   // 0x00a4d610
void      outlet_float(t_outlet* o, float f);                         // 0x00a49570
void      outlet_symbol(t_outlet* o, t_symbol s);                     // 0x00a49df0
void      outlet_bang(t_outlet* o);                                   // 0x00a49da0
void*     atom_vectorgensym(t_symbol* out, int argc, t_atom* argv);   // 0x00a46830
int       atom_getint_at(int idx, int argc, t_atom* argv);            // 0x00a46920
float     atom_getfloat_at(int idx, int argc, t_atom* argv);          // 0x00a468f0
t_symbol* atom_getsymbol_at(t_symbol* out, int idx, int argc, t_atom* argv); // 0x00a46950
void      inlet_setempty(t_inlet* i, t_symbol s);                     // 0x00a49720
void      outlet_setempty(t_outlet* o, t_symbol s);                   // 0x00a49d10
void*     getbytes(int n, const char* kind);                          // 0x00a49610
void      freebytes(void* p, int n);                                  // 0x00a49650
void      pd_send_float(uint sym, uint a, float f);                   // 0x00a67230
bool      pd_bind(void* x, t_symbol name);                            // 0x00a67620
void*     EapdBindRemove(t_symbol s);                                 // 0x00a671d0
void      sys_vgui(uint a, uint b, uint c);                           // 0x00a671b0
void*     pd_findbyclass(t_symbol name, t_symbol s2, t_class* c);     // 0x00a671f0
void      DoInsertValue(void* vec, void* val, int off);               // 0x011e0744
void      SetSeed(void* rng, uint seed);                              // 0x00936090
uint      GetRandomSeed();                                            // 0x00a5eca0

// forward decls of slice methods
int*  toggle_new(t_symbol s1, t_symbol s2, int argc, t_atom* argv);   // 0x00a60ce0
void  toggle_bang(void* x);                                           // 0x00a60e70
void  toggle_float(void* x, float f);                                 // 0x00a60e90
void  toggle_loadbang(void* x);                                       // 0x00a60ed0
void* slider_new(t_symbol s1, t_symbol s2, int argc, t_atom* argv);   // 0x00a60fd0
void* vinlet_new(int argc, t_atom* argv);                             // 0x00a613c0
void* voutlet_new(int argc, t_atom* argv);                            // 0x00a61610
void* menu_new(int argc, t_atom* argv);                               // 0x00a618c0
void  menu_free(TX* x);                                               // 0x00a619c0
int   menu_float(TX* x, float f);                                     // 0x00a619e0
bool  menu_list(TX* x, t_symbol s, int argc, t_atom* argv);           // 0x00a61ad0
bool  menu_append(TX* x, t_symbol s, int argc, t_atom* argv);         // 0x00a61b10
void  menu_clear(TX* x);                                              // 0x00a61b50
void* table_new(void* a, void* b, int argc, t_atom* argv);            // 0x00a61c20
void  table_free(void* x);                                            // 0x00a61e50
void  table_select(void* x, float f);                                 // 0x00a61ec0
void  table_float(void* x, float f);                                  // 0x00a61ee0

// Eapd methods referenced by setup, defined in other slices
void  vinlet_list(void* x, t_symbol s, int argc, t_atom* argv);       // 0x00a614b0
void  vinlet_anything(void* x, t_symbol s, int argc, t_atom* argv);   // 0x00a614e0
void  voutlet_list(void* x, t_symbol s, int argc, t_atom* argv);      // 0x00a61730
void  voutlet_anything(void* x, t_symbol s, int argc, t_atom* argv);  // 0x00a61760
void  inlet_bang_all(void* x);                                        // 0x00a59db0
void  inlet_symbol(void* x, t_symbol s);                              // 0x00a5a140

// ---------------------------------------------------------------------------
// 0x00a60ef0: EA::Audio::Eapd::g_toggle_setup
// ---------------------------------------------------------------------------
// @ 0x00a60ef0
byte g_toggle_setup(void)
{
    t_symbol s;
    t_symbol* p = gensym(&s, "empty");
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

// ---------------------------------------------------------------------------
// 0x00a60fd0: EA::Audio::Eapd::slider_new
// ---------------------------------------------------------------------------
// @ 0x00a60fd0
void* slider_new(t_symbol s1, t_symbol s2, int argc, t_atom* argv)
{
    TX* x = (TX*)pd_new(gpSliderClass);
    if (x == 0)
        return x;
    outlet_new(x, gFloatSymbol);
    *(float*)((char*)x + 0x40) = 0.0f;
    *(float*)((char*)x + 0x44) = kf127;
    *(byte*)((char*)x + 0x28) = 0;
    *(t_symbol*)((char*)x + 0x2c) = sGuiEmpty;
    *(t_symbol*)((char*)x + 0x34) = sGuiEmpty;
    *(float*)((char*)x + 0x3c) = 0.0f;
    if (argc < 0x12)
        return x;
    *(float*)((char*)x + 0x40) = atom_getfloat_at(2, argc, argv);
    *(float*)((char*)x + 0x44) = atom_getfloat_at(3, argc, argv);
    *(byte*)((char*)x + 0x28) = atom_getfloat_at(5, argc, argv) != 0.0f;
    *(t_symbol*)((char*)x + 0x2c) = *atom_getsymbol_at(&s1, 6, argc, argv);
    *(t_symbol*)((char*)x + 0x34) = *atom_getsymbol_at(&s2, 7, argc, argv);
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

// ---------------------------------------------------------------------------
// 0x00a61180: EA::Audio::Eapd::slider_float
// ---------------------------------------------------------------------------
// @ 0x00a61180
void slider_float(TX* x)
{
    float f = *(float*)((char*)x + 0x3c);
    void** p = (void**)(*(int*)((char*)x + 0xc) + 8);
    int n = ++*(int*)&gOutletCount;
    (void)n;
    if (gOutletCount < 1000) {
        for (void** o = (void**)*p; o != 0; o = (void**)*o)
            outlet_float((t_outlet*)o[1], f);
    }
    gOutletCount--;
    uint sym = *(uint*)((char*)x + 0x2c);
    if (sym != sGuiEmpty.mHash && sym != *(uint*)((char*)x + 0x34))
        pd_send_float(sym, *(uint*)((char*)x + 0x30), *(float*)((char*)x + 0x3c));
}

// ---------------------------------------------------------------------------
// 0x00a61200: slider float setter (clamped) -> slider_float
// ---------------------------------------------------------------------------
// @ 0x00a61200
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

// ---------------------------------------------------------------------------
// 0x00a61230: loadbang handler (tail-calls slider_float when flagged)
// ---------------------------------------------------------------------------
// @ 0x00a61250
byte g_hslider_setup(void)
{
    t_symbol s;
    t_symbol* p = gensym(&s, "empty");
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

// ---------------------------------------------------------------------------
// 0x00a613c0: EA::Audio::Eapd::vinlet_new
// ---------------------------------------------------------------------------
// @ 0x00a613c0
void* vinlet_new(int argc, t_atom* argv)
{
    t_symbol s;
    TX* x = (TX*)pd_new(gpInletClass);
    if (x != 0) {
        void* cur = canvas_getcurrent();
        *(void**)((char*)x + 0x28) = cur;
        *(void**)((char*)x + 0x2c) = canvas_addinlet((t_glist*)cur, x, gEmptySymbol);
        void* out = outlet_new(x, gEmptySymbol);
        if (argc != 0) {
            atom_vectorgensym(&s, argc, argv);
            inlet_setempty((t_inlet*)*(void**)((char*)x + 0x2c), s);
            outlet_setempty((t_outlet*)out, s);
        }
    }
    return x;
}

// ---------------------------------------------------------------------------
// 0x00a61460: EA::Audio::Eapd inlet float broadcaster
// ---------------------------------------------------------------------------
// @ 0x00a61460
void inlet_float_all(TX* x, float f)
{
    void* out = *(void**)((char*)x + 0xc);
    int n = ++gOutletCount;
    if (n < 1000) {
        void** p = (void**)*(void**)((char*)out + 8);
        while (p != 0) {
            outlet_float((t_outlet*)p[1], f);
            p = (void**)*p;
        }
    }
    gOutletCount--;
}

// ---------------------------------------------------------------------------
// 0x00a61510: EA::Audio::Eapd::vinlet_free
// ---------------------------------------------------------------------------
// @ 0x00a61510
void vinlet_free(TX* x)
{
    canvas_rminlet((t_glist*)*(void**)((char*)x + 0x28), (t_inlet*)*(void**)((char*)x + 0x2c));
}

// ---------------------------------------------------------------------------
// 0x00a61530: EA::Audio::Eapd::vinlet_setup
// ---------------------------------------------------------------------------
// @ 0x00a61530
byte vinlet_setup(void)
{
    t_symbol s;
    t_symbol* p = gensym(&s, "inlet");
    gpInletClass = class_new(*p, (void*)vinlet_new, (void*)vinlet_free, 0x30, 8, 9, 0);
    byte ok = gpInletClass != 0;
    ok &= 1;
    ok &= class_addbang(gpInletClass, (void*)inlet_bang_all);
    ok &= class_doaddfloat(gpInletClass, (void*)inlet_float_all);
    ok &= class_addsymbol(gpInletClass, (void*)inlet_symbol);
    ok &= class_addlist(gpInletClass, (void*)vinlet_list);
    ok &= class_addanything(gpInletClass, (void*)vinlet_anything);
    p = gensym(&s, "helpsym");
    class_sethelpsymbol(gpInletClass, *p);
    return ok;
}

// ---------------------------------------------------------------------------
// 0x00a61610: EA::Audio::Eapd::voutlet_new
// ---------------------------------------------------------------------------
// @ 0x00a61610
void* voutlet_new(int argc, t_atom* argv)
{
    TX* x = (TX*)pd_new(gpOutletClass);
    if (x != 0) {
        void* cur = canvas_getcurrent();
        *(void**)((char*)x + 0x28) = cur;
        *(void**)((char*)x + 0x2c) = canvas_addoutlet((t_glist*)cur, x, gEmptySymbol);
        void* in = inlet_new(x, x, gEmptySymbol, gEmptySymbol, gEmptySymbol, gEmptySymbol);
        if (argc != 0) {
            t_symbol s;
            atom_vectorgensym(&s, argc, argv);
            inlet_setempty((t_inlet*)in, s);
            outlet_setempty((t_outlet*)*(void**)((char*)x + 0x2c), s);
        }
    }
    return x;
}

// ---------------------------------------------------------------------------
// 0x00a616b0: EA::Audio::Eapd::voutlet_bang
// ---------------------------------------------------------------------------
// @ 0x00a616b0
void voutlet_bang(TX* x)
{
    outlet_bang((t_outlet*)*(void**)((char*)x + 0x2c));
}

// ---------------------------------------------------------------------------
// 0x00a61710: EA::Audio::Eapd::voutlet_symbol
// ---------------------------------------------------------------------------
// @ 0x00a61710
void voutlet_symbol(TX* x, t_symbol s)
{
    outlet_symbol((t_outlet*)*(void**)((char*)x + 0x2c), s);
}

// ---------------------------------------------------------------------------
// 0x00a61790: EA::Audio::Eapd::voutlet_free
// ---------------------------------------------------------------------------
// @ 0x00a61790
void voutlet_free(TX* x)
{
    canvas_rmoutlet((t_glist*)*(void**)((char*)x + 0x28), (t_outlet*)*(void**)((char*)x + 0x2c));
}

// ---------------------------------------------------------------------------
// 0x00a617c0: EA::Audio::Eapd::voutlet_setup
// ---------------------------------------------------------------------------
// @ 0x00a617c0
byte voutlet_setup(void)
{
    t_symbol s;
    t_symbol* p = gensym(&s, "outlet");
    gpOutletClass = class_new(*p, (void*)voutlet_new, (void*)voutlet_free, 0x30, 8, 9, 0);
    byte ok = gpOutletClass != 0;
    ok &= 1;
    ok &= class_addbang(gpOutletClass, (void*)voutlet_bang);
    ok &= class_doaddfloat(gpOutletClass, (void*)inlet_float_all);
    ok &= class_addsymbol(gpOutletClass, (void*)voutlet_symbol);
    ok &= class_addlist(gpOutletClass, (void*)voutlet_list);
    ok &= class_addanything(gpOutletClass, (void*)voutlet_anything);
    p = gensym(&s, "helpsym");
    class_sethelpsymbol(gpOutletClass, *p);
    return ok;
}

// ---------------------------------------------------------------------------
// 0x00a618a0: EA::Audio::Eapd::g_io_setup
// ---------------------------------------------------------------------------
// @ 0x00a618a0
byte g_io_setup(void)
{
    byte a = vinlet_setup();
    a &= 1;
    byte b = voutlet_setup();
    b &= a;
    return b;
}

// ---------------------------------------------------------------------------
// 0x00a618c0: EA::Audio::Eapd::menu_new
// ---------------------------------------------------------------------------
// @ 0x00a618c0
void* menu_new(int argc, t_atom* argv)
{
    TX* x = 0;
    int count = 0x20;
    if (argc > 1) {
        if (atom_getint_at(0, argc, argv) != 1)
            return 0;
        if (*(int*)((char*)argv + 0x18) != 1)
            return 0;
        count = (int)*(float*)((char*)argv + 0x1c);
        argc -= 3;
        argv = (t_atom*)((char*)argv + 0x24);
        if (count < 1)
            count = 0x20;
    }
    void* buf = getbytes(count * 0xc, "EAPd/t_menu_atoms");
    if (buf != 0) {
        x = (TX*)pd_new(gpMenuClass);
        if (x != 0) {
            *(void**)((char*)x + 0x28) = outlet_new(x, gAnythingSymbol);
            if (*(void**)((char*)x + 0x28) != 0) {
                *(void**)((char*)x + 0x2c) = outlet_new(x, gFloatSymbol);
                if (*(void**)((char*)x + 0x2c) != 0) {
                    *(int*)((char*)x + 0x30) = argc;
                    *(int*)((char*)x + 0x34) = count;
                    *(void**)((char*)x + 0x38) = buf;
                    int off = 0;
                    while (argc > 0) {
                        char* dst = (char*)*(void**)((char*)x + 0x38) + off;
                        *(uint*)(dst + 0) = *(uint*)((char*)argv + off + 0);
                        *(uint*)(dst + 4) = *(uint*)((char*)argv + off + 4);
                        *(uint*)(dst + 8) = *(uint*)((char*)argv + off + 8);
                        off += 0xc;
                        argc--;
                    }
                }
            }
        }
    }
    return x;
}

// ---------------------------------------------------------------------------
// 0x00a619c0: EA::Audio::Eapd::menu_free
// ---------------------------------------------------------------------------
// @ 0x00a619c0
void menu_free(TX* x)
{
    freebytes(*(void**)((char*)x + 0x38), *(int*)((char*)x + 0x34) * 0xc);
}

// ---------------------------------------------------------------------------
// 0x00a619e0: EA::Audio::Eapd::menu_float
// ---------------------------------------------------------------------------
// @ 0x00a619e0
int menu_float(TX* x, float f)
{
    int idx = (int)f;
    byte ok = 0;
    if (idx < 0)
        return ok;
    if (*(int*)((char*)x + 0x30) <= idx)
        return ok;
    void** o = (void**)*(void**)((char*)x + 0x2c);
    gOutletCount++;
    if (gOutletCount < 1000) {
        while (o != 0) {
            outlet_float((t_outlet*)o[1], (float)idx);
            o = (void**)*o;
        }
    }
    gOutletCount--;
    char* e = (char*)(*(int*)((char*)x + 0x38) + idx * 0xc);
    if (*(int*)e == 1) {
        float v = *(float*)(e + 4);
        void** s = (void**)*(void**)((char*)x + 0x28);
        gOutletCount++;
        if (gOutletCount < 1000) {
            while (s != 0) {
                outlet_float((t_outlet*)s[1], v);
                s = (void**)*s;
            }
        }
        gOutletCount--;
        return 1;
    }
    outlet_symbol((t_outlet*)*(void**)((char*)x + 0x28), *(t_symbol*)(e + 4));
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00a61ad0: EA::Audio::Eapd::menu_list
// ---------------------------------------------------------------------------
// @ 0x00a61ad0
bool menu_list(TX* x, t_symbol s, int argc, t_atom* argv)
{
    bool ok = false;
    if (*(int*)((char*)x + 0x34) > argc) {
        DoInsertValue(*(void**)((char*)x + 0x38), argv, argc * 0xc);
        *(int*)((char*)x + 0x30) = argc;
        ok = true;
    }
    return ok;
}

// ---------------------------------------------------------------------------
// 0x00a61b10: EA::Audio::Eapd::menu_append
// ---------------------------------------------------------------------------
// @ 0x00a61b10
bool menu_append(TX* x, t_symbol s, int argc, t_atom* argv)
{
    bool ok = false;
    if (argc == 1) {
        if (*(int*)((char*)x + 0x30) != *(int*)((char*)x + 0x34)) {
            int n = *(int*)((char*)x + 0x30);
            char* dst = (char*)(*(int*)((char*)x + 0x38) + n * 0xc);
            *(uint*)(dst + 0) = *(uint*)((char*)argv + 0);
            *(uint*)(dst + 4) = *(uint*)((char*)argv + 4);
            *(uint*)(dst + 8) = *(uint*)((char*)argv + 8);
            (*(int*)((char*)x + 0x30))++;
            ok = true;
        }
    }
    return ok;
}

// ---------------------------------------------------------------------------
// 0x00a61b50: EA::Audio::Eapd::menu_clear
// ---------------------------------------------------------------------------
// @ 0x00a61b50
void menu_clear(TX* x)
{
    *(int*)((char*)x + 0x30) = 0;
}

// ---------------------------------------------------------------------------
// 0x00a61b60: EA::Audio::Eapd::x_menu_setup
// ---------------------------------------------------------------------------
// @ 0x00a61b60
byte x_menu_setup(void)
{
    t_symbol s;
    t_symbol* p = gensym(&s, "menu");
    gpMenuClass = class_new(*p, (void*)menu_new, (void*)menu_free, 0x3c, 0, 9, 0);
    byte ok = gpMenuClass != 0;
    ok &= 1;
    ok &= class_doaddfloat(gpMenuClass, (void*)menu_float);
    ok &= class_addlist(gpMenuClass, (void*)menu_list);
    p = gensym(&s, "append");
    ok &= class_addmethod_m(gpMenuClass, (void*)menu_append, *p, 9, 0);
    p = gensym(&s, "clear");
    ok &= class_addmethod(gpMenuClass, (void*)menu_clear, *p, 0);
    return ok;
}

// ---------------------------------------------------------------------------
// 0x00a61c20: EA::Audio::Eapd::table_new
// ---------------------------------------------------------------------------
// @ 0x00a61c20
void* table_new(void* a1, void* a2, int argc, t_atom* argv)
{
    if (argc > 3)
        return 0;
    bool randW = (a1 == (void*)sRandWeighted.mHash);
    t_symbol sym7 = gEmptySymbol;
    int val1 = 1;
    int val2 = 1;
    t_symbol symC = gEmptySymbol;
    if (argc > 0) {
        if (*(int*)argv == 2) {
            sym7 = *(t_symbol*)((char*)argv + 8);
            symC = *(t_symbol*)((char*)argv + 4);
        }
        int k = (*(int*)argv == 2) ? 1 : 0;
        if (k < argc) {
            int* e = (int*)((char*)argv + k * 0xc);
            if (*e == 1) {
                float f = *(float*)((char*)argv + k * 0xc + 4);
                k++;
                if (f < kfOne)
                    f = kfOne;
                val1 = (int)f;
            }
            if (k < argc) {
                e = (int*)((char*)argv + k * 0xc);
                if (*e == 1) {
                    float f = *(float*)((char*)argv + k * 0xc + 4);
                    k++;
                    if (f < kfOne)
                        f = kfOne;
                    val2 = (int)f;
                }
                if (k < argc)
                    return 0;
            }
        }
    }
    if (sym7.mHash != gEmptySymbol.mHash) {
        if (pd_findbyclass(sym7, symC, gpTableClass) != 0)
            return 0;
    }
    if (val1 > val2)
        return 0;
    void* buf = getbytes(val2 * 0xc, "EAPd/t_table_atoms");
    if (buf == 0)
        return 0;
    char* p = (char*)buf;
    for (int i = val2; i > 0; i--) {
        *(int*)p = 1;
        *(float*)(p + 4) = 0.0f;
        p += 0xc;
    }
    t_class* cls = randW ? gpRandWeightedClass : gpTableClass;
    TX* x = (TX*)pd_new(cls);
    if (x == 0) {
        freebytes(buf, val2 * 4);
        return x;
    }
    if (outlet_new(x, gFloatSymbol) == 0) {
        freebytes(buf, val2 * 4);
        return x;
    }
    *(t_symbol*)((char*)x + 0x28) = sym7;
    *(t_symbol*)((char*)x + 0x2c) = symC;
    *(int*)((char*)x + 0x30) = val1;
    *(int*)((char*)x + 0x34) = val2;
    *(void**)((char*)x + 0x38) = buf;
    if (randW)
        SetSeed((char*)x + 0x3c, GetRandomSeed());
    if (sym7.mHash != gEmptySymbol.mHash)
        pd_bind(x, *(t_symbol*)((char*)x + 0x28));
    void* r = EapdBindRemove(sHashA);
    if (r != 0)
        sys_vgui((uint)r, sHashA.mHash, (uint)sHashA.mpName);
    pd_bind(x, sHashA);
    return x;
}

// ---------------------------------------------------------------------------
// 0x00a61e50: EA::Audio::Eapd::table_free
// ---------------------------------------------------------------------------
// @ 0x00a61e50
void table_free(TX* x)
{
    if (*(uint*)((char*)x + 0x28) != gEmptySymbol.mHash)
        sys_vgui((uint)x, *(uint*)((char*)x + 0x28), *(uint*)((char*)x + 0x2c));
    void* r = EapdBindRemove(sHashA);
    if (r == x)
        sys_vgui((uint)x, sHashA.mHash, (uint)sHashA.mpName);
    int n = *(int*)((char*)x + 0x34);
    void* buf = *(void**)((char*)x + 0x38);
    freebytes(buf, n * 4);
}

// ---------------------------------------------------------------------------
// 0x00a61ec0: EA::Audio::Eapd::table_select
// ---------------------------------------------------------------------------
// @ 0x00a61ec0
void table_select(TX* x, float f)
{
    int i = (int)f;
    if (1 <= i && *(int*)((char*)x + 0x34) >= i)
        *(int*)((char*)x + 0x30) = i;
}

// ---------------------------------------------------------------------------
// 0x00a61ee0: EA::Audio::Eapd::table_float
// ---------------------------------------------------------------------------
// @ 0x00a61ee0
void table_float(TX* x, float f)
{
    int i = (int)f;
    if (i < 0)
        return;
    if (i >= *(int*)((char*)x + 0x30))
        return;
    float v = *(float*)(*(int*)((char*)x + 0x38) + i * 0xc + 4);
    void* out = *(void**)((char*)x + 0xc);
    int n = ++gOutletCount;
    if (n < 1000) {
        void** p = (void**)*(void**)((char*)out + 8);
        while (p != 0) {
            outlet_float((t_outlet*)p[1], v);
            p = (void**)*p;
        }
    }
    gOutletCount--;
}

} // namespace Eapd
