// Slice s00a5f070: EA::Audio::Eapd (EA's embedded Pure Data) - the timing objects
// metro, delay, line, timer and the front half of pipe (PD's x_time.c / x_interface
// pipe object), 0xa5f070-0xa5ff36.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
//
// 16/25 VAs are byte-exact (manifest.txt).  The remaining 9 are in
// partial.txt (decompiled, semantically faithful, cl-schedule residue) and
// nonmatching.txt (the analyser's 216-byte metro_free+metro_new merge at
// 0xa5f460).
//
// Equivalence gate (default inputs): PASS for every scored VA except the two
// allocators line_new (0xa5f9f0) and timer_new (0xa5fce0), which read their
// class global (spLineClass/spTimerClass) -- null in the harness, so all
// inputs fault(read) and are reported UNSUPPORTED.
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

struct t_class;
typedef t_class* t_pd;

// t_symbol is passed by value (hash, name); symbols compare by their first word only.
struct t_symbol {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};

struct t_atom {
    int a_type;                 // +0
    union {
        float    w_float;       // +4
        t_symbol w_symbol;      // +4
    } a_w;
};

struct t_outlet;
struct t_outconnect {         // 8
    t_outconnect* oc_next;    // +0
    t_outlet*     oc_to;      // +4
};

struct t_outlet {             // 0x1c
    void*         o_owner;        // +0x00
    t_outlet*     o_next;         // +0x04
    t_outconnect* o_connections;  // +0x08
    t_symbol      o_symfrom;      // +0x0c
    t_symbol      o_symto;        // +0x14
};

// ---------------------------------------------------------------- globals
extern int       gOutletCount;             // 0x167545c
extern t_symbol  gFloatSymbol;             // 0x16758c4
extern t_symbol  gBangSymbol;              // 0x16758b4
extern t_class*  spDelayClass;             // 0x1675800
extern t_class*  spMetroClass;             // 0x16757f4
extern t_class*  spLineClass;              // 0x16757f8
extern t_class*  spTimerClass;             // 0x16757f0
extern t_symbol  gSymbolSymbol;            // 0x1675894

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
bool class_addcreator(void* fn, t_symbol name, int a1, int a2);          // 0xa48e00
bool class_addmethod1(t_class* c, void* fn, t_symbol name, int a1);      // 0xa48a30
bool class_addmethod2(t_class* c, void* fn, t_symbol name, int a1, int a2);  // 0xa48a80

void* pd_new(t_class* c);                                                // 0xa49390
void* clock_new(void* pd, void* fn);                                     // 0xa49080
void  clock_unset(void* c);                                              // 0xa490b0
void  clock_pause(void* c);                                              // 0xa49170
void  clock_unpause(void* c);                                            // 0xa491a0
bool  clock_ispaused(void* c);                                           // 0xa491d0
void  clock_delay(void* c, float f);                                     // 0xa491e0
double clock_getlogicaltime();                                           // 0xa49210
double clock_gettimesince(double t);                                     // 0xa49220
double clock_getlogicaltimeafter(float t);                               // 0xa49240
void  clock_free(void* c);                                              // 0xa49260

void* outlet_new(void* owner, t_symbol name);                            // 0xa49d30
void  outlet_float(void* o, float f);                                    // 0xa49570
void  outlet_bang(void* o);                                              // 0xa49da0
void  outlet_symbol(void* o, t_symbol a, t_symbol b);                    // 0xa49df0
void* inlet_new(void* owner, void* dest, t_symbol a, t_symbol b);        // 0xa49740
void* floatinlet_new(void* owner, void* dest);                           // 0xa49a00

void* memcpy(void* dst, const void* src, unsigned n);

// forward: shared methods reused across the timing objects, and objects from
// the sibling spin/timer slices.
void* metro_new(float f);                       // 0xa5f460 (freemethod)
void  metro_stop(char* x);                      // 0xa5f3f0
void  metro_tick(char* x);                      // 0xa5f300
void  metro_float(char* x, float f);            // 0xa5f340
void  spin_bang(char* x);                       // 0xa5efd0
void  spin_stop(char* x);                       // 0xa5f000
void  spin_float(char* x, float f);             // 0xa5f030
void  timer_start(char* x);                     // 0xa5fbf0

// object sizes / field offsets: metro 0x34, delay 0x30, line 0x70, timer 0x38

// ============================================================ delay object
// @ 0x00a5f070  EA::Audio::Eapd::delay_doaddfloat
void delay_doaddfloat(char* x, float f)
{
    if (!clock_ispaused(*(void**)(x + 0x28))) {
        float t = f;
        if (0.0f > f)
            t = 0.0f;
        if (!clock_ispaused(*(void**)(x + 0x28)))
            *(float*)(x + 0x2c) = t;
        if (!clock_ispaused(*(void**)(x + 0x28)))
            clock_delay(*(void**)(x + 0x28), *(float*)(x + 0x2c));
    }
}

// @ 0x00a5f0e0  EA::Audio::Eapd::delay_pause
void delay_pause(char* x, float f)
{
    if (f != 0.0f) {
        clock_pause(*(void**)(x + 0x28));
        return;
    }
    clock_unpause(*(void**)(x + 0x28));
}

// @ 0x00a5f120  EA::Audio::Eapd::delay_new
void* delay_new(float f)
{
    char* x = (char*)pd_new(spDelayClass);
    if (x) {
        *(void**)(x + 0x28) = clock_new(x, (void*)0xa59db0);
        t_symbol sym;
        t_symbol sym2;
        t_symbol* s = gensym(&sym, "bang");
        outlet_new(x, *s);
        t_symbol* s2 = gensym(&sym, "ft1");
        t_symbol* s3 = gensym(&sym2, "float");
        inlet_new(x, x, *s3, *s2);
    }
    if (x) {
        float t = f;
        if (0.0f > f)
            t = 0.0f;
        if (!clock_ispaused(*(void**)(x + 0x28)))
            *(float*)(x + 0x2c) = t;
    }
    return x;
}

// @ 0x00a5f1e0  EA::Audio::Eapd::delay_setup
bool delay_setup()
{
    t_symbol sym;
    t_symbol* s = gensym(&sym, "delay");
    spDelayClass = class_new6(*s, (void*)delay_new, (void*)metro_new,
                              0x30, 0, 5);
    bool ok = spDelayClass != 0;
    t_symbol sym2;
    t_symbol* s2 = gensym(&sym2, "del");
    ok &= class_addcreator((void*)delay_new, *s2, 5, 0);
    ok &= class_addbang(spDelayClass, (void*)spin_bang);
    t_symbol sym3;
    t_symbol* s3 = gensym(&sym3, "stop");
    ok &= class_addmethod1(spDelayClass, (void*)spin_stop, *s3, 0);
    t_symbol sym4;
    t_symbol* s4 = gensym(&sym4, "ft1");
    ok &= class_addmethod2(spDelayClass, (void*)spin_float, *s4, 1, 0);
    ok &= class_doaddfloat(spDelayClass, (void*)delay_doaddfloat);
    t_symbol sym5;
    t_symbol* s5 = gensym(&sym5, "pause");
    ok &= class_addmethod2(spDelayClass, (void*)delay_pause, *s5, 1, 0);
    return ok;
}

// ============================================================ metro object
// @ 0x00a5f300  EA::Audio::Eapd::metro_tick
void metro_tick(char* x)
{
    *(int*)(x + 0x30) = 0;
    outlet_bang(*(void**)(x + 0xc));
    if (*(int*)(x + 0x30) == 0)
        clock_delay(*(void**)(x + 0x28), *(float*)(x + 0x2c));
}

// @ 0x00a5f340  EA::Audio::Eapd::metro_float
void metro_float(char* x, float f)
{
    if (clock_ispaused(*(void**)(x + 0x28)))
        return;
    if (f != 0.0f) {
        *(int*)(x + 0x30) = 0;
        outlet_bang(*(void**)(x + 0xc));
        if (*(int*)(x + 0x30) == 0)
            clock_delay(*(void**)(x + 0x28), *(float*)(x + 0x2c));
        *(int*)(x + 0x30) = 1;
        return;
    }
    clock_unset(*(void**)(x + 0x28));
    *(int*)(x + 0x30) = 1;
}

// @ 0x00a5f3c0  EA::Audio::Eapd::metro_bang
void metro_bang(char* x)
{
    if (!clock_ispaused(*(void**)(x + 0x28)))
        metro_float(x, 1.0f);
}

// @ 0x00a5f3f0  EA::Audio::Eapd::metro_stop
void metro_stop(char* x)
{
    if (!clock_ispaused(*(void**)(x + 0x28)))
        metro_float(x, 0.0f);
}

// @ 0x00a5f420  EA::Audio::Eapd::metro_ft1
void metro_ft1(char* x, float f)
{
    if (f < 1.0f)
        f = 1.0f;
    if (!clock_ispaused(*(void**)(x + 0x28)))
        *(float*)(x + 0x2c) = f;
}

// @ 0x00a5f460  EA::Audio::Eapd::metro_free
void metro_free(char* x)
{
    clock_free(*(void**)(x + 0x28));
}

// (metro_new follows metro_free in the original region; the analysis merges both
//  into a single 216-byte function at 0xa5f460 -- see nonmatching.txt)
// @ 0x00a5f470  EA::Audio::Eapd::metro_new
void* metro_new(float f)
{
    char* x = (char*)pd_new(spMetroClass);
    if (x) {
        *(int*)(x + 0x30) = 0;
        *(void**)(x + 0x28) = clock_new(x, (void*)metro_tick);
        t_symbol sym;
        t_symbol* s = gensym(&sym, "bang");
        outlet_new(x, *s);
        t_symbol sym2;
        t_symbol* s2 = gensym(&sym2, "ft1");
        t_symbol* s3 = gensym(&sym, "float");
        inlet_new(x, x, *s3, *s2);
        float t = f;
        if (1.0f > f)
            t = 1.0f;
        if (!clock_ispaused(*(void**)(x + 0x28)))
            *(float*)(x + 0x2c) = t;
    }
    return x;
}

// @ 0x00a5f540  EA::Audio::Eapd::metro_setup
bool metro_setup()
{
    t_symbol sym;
    t_symbol* s = gensym(&sym, "metro");
    spMetroClass = class_new7(*s, (void*)metro_new, (void*)metro_stop,
                              0x34, 0, 5, 0);
    bool ok = spMetroClass != 0;
    ok &= class_addbang(spMetroClass, (void*)metro_bang);
    t_symbol sym2;
    t_symbol* s2 = gensym(&sym2, "stop");
    ok &= class_addmethod1(spMetroClass, (void*)metro_stop, *s2, 0);
    t_symbol sym3;
    t_symbol* s3 = gensym(&sym3, "ft1");
    ok &= class_addmethod2(spMetroClass, (void*)metro_ft1, *s3, 1, 0);
    ok &= class_doaddfloat(spMetroClass, (void*)metro_float);
    t_symbol sym4;
    t_symbol* s4 = gensym(&sym4, "pause");
    ok &= class_addmethod2(spMetroClass, (void*)delay_pause, *s4, 1, 0);
    return ok;
}

// ============================================================= line object
// @ 0x00a5f630  EA::Audio::Eapd::line_tick
void line_tick(char* x)
{
    double time = clock_getlogicaltime();
    double linediff = -clock_gettimesince(*(double*)(x + 0x38));
    t_outlet* lst = *(t_outlet**)(x + 0x2c);
    gOutletCount++;
    if (linediff < 1e-09) {
        float val = *(float*)(x + 0x40);
        if (gOutletCount < 1000) {
            t_outconnect* oc = lst->o_connections;
            while (oc) {
                outlet_float(oc->oc_to, val);
                oc = oc->oc_next;
            }
        }
        gOutletCount--;
        outlet_bang(*(void**)(x + 0x30));
        return;
    }
    float  f1  = *(float*)(x + 0x50);
    double t0  = *(double*)(x + 0x48);
    float  f2  = *(float*)(x + 0x40);
    double inc = *(double*)(x + 0x60);
    if (gOutletCount < 1000) {
        t_outconnect* oc = lst->o_connections;
        while (oc) {
            outlet_float(oc->oc_to, (float)(f1 + (time - t0) * (f2 - f1) * inc));
            oc = oc->oc_next;
        }
    }
    gOutletCount--;
    if (*(float*)(x + 0x58) <= linediff)
        linediff = *(float*)(x + 0x58);
    clock_delay(*(void**)(x + 0x28), (float)linediff);
}

// @ 0x00a5f750  EA::Audio::Eapd::line_float
void line_float(char* x, float f)
{
    if (clock_ispaused(*(void**)(x + 0x28)))
        return;
    double now = clock_getlogicaltime();
    if (*(int*)(x + 0x54) != 0 && *(float*)(x + 0x68) > 0.0f) {
        float v;
        if (now <= *(double*)(x + 0x38))
            v = *(float*)(x + 0x40);
        else
            v = (*(float*)(x + 0x40) - *(float*)(x + 0x50)) *
                (float)(now - *(double*)(x + 0x48)) *
                (float)*(double*)(x + 0x60) + *(float*)(x + 0x50);
        *(float*)(x + 0x50) = v;
        *(double*)(x + 0x48) = now;
        *(double*)(x + 0x38) = clock_getlogicaltimeafter(*(float*)(x + 0x68));
        *(float*)(x + 0x40) = f;
        line_tick(x);
        *(int*)(x + 0x54) = 0;
        *(double*)(x + 0x60) = 1.0 / (*(double*)(x + 0x38) - now);
        float a = *(float*)(x + 0x58);
        float b = *(float*)(x + 0x68);
        if (b < a)
            a = b;
        clock_delay(*(void**)(x + 0x28), a);
        *(int*)(x + 0x54) = 0;
        return;
    }
    clock_unset(*(void**)(x + 0x28));
    *(float*)(x + 0x50) = f;
    *(float*)(x + 0x40) = f;
    gOutletCount++;
    if (gOutletCount < 1000) {
        t_outconnect* oc = *(t_outconnect**)(*(char**)(x + 0x2c) + 8);
        while (oc) {
            outlet_float(oc->oc_to, f);
            oc = oc->oc_next;
        }
    }
    gOutletCount--;
    *(int*)(x + 0x54) = 0;
}

// @ 0x00a5f8b0  EA::Audio::Eapd::line_ft1
void line_ft1(char* x, float f)
{
    if (clock_ispaused(*(void**)(x + 0x28)))
        return;
    *(float*)(x + 0x68) = f;
    *(int*)(x + 0x54) = 1;
}

// @ 0x00a5f8e0  EA::Audio::Eapd::line_stop
void line_stop(char* x)
{
    if (clock_ispaused(*(void**)(x + 0x28)))
        return;
    *(float*)(x + 0x40) = *(float*)(x + 0x50);
    clock_unset(*(void**)(x + 0x28));
}

// @ 0x00a5f910  EA::Audio::Eapd::line_set
void line_set(char* x, float f)
{
    if (clock_ispaused(*(void**)(x + 0x28)))
        return;
    clock_unset(*(void**)(x + 0x28));
    *(float*)(x + 0x50) = f;
    *(float*)(x + 0x40) = f;
}

// @ 0x00a5f950  EA::Audio::Eapd::line_pause
void line_pause(char* x, float f)
{
    if (f != 0.0f) {
        if (clock_ispaused(*(void**)(x + 0x28)))
            return;
        clock_pause(*(void**)(x + 0x28));
        *(double*)(x + 0x38) = -clock_gettimesince(*(double*)(x + 0x38));
        *(double*)(x + 0x48) = -clock_gettimesince(*(double*)(x + 0x48));
        return;
    }
    if (clock_ispaused(*(void**)(x + 0x28))) {
        *(double*)(x + 0x38) =
            clock_getlogicaltimeafter((float)*(double*)(x + 0x38));
        *(double*)(x + 0x48) =
            clock_getlogicaltimeafter((float)*(double*)(x + 0x48));
        clock_unpause(*(void**)(x + 0x28));
    }
}

// @ 0x00a5f9f0  EA::Audio::Eapd::line_new
void* line_new(float f0, float f1)
{
    char* x = (char*)pd_new(spLineClass);
    if (x) {
        *(float*)(x + 0x50) = f0;
        *(float*)(x + 0x40) = f0;
        *(double*)(x + 0x60) = 1.0;
        *(int*)(x + 0x54) = 0;
        *(void**)(x + 0x28) = clock_new(x, (void*)line_tick);
        double t = clock_getlogicaltime();
        *(double*)(x + 0x48) = t;
        *(double*)(x + 0x38) = t;
        if (f1 <= 0.0f)
            f1 = 20.0f;
        *(float*)(x + 0x58) = f1;
        *(void**)(x + 0x2c) = outlet_new(x, gFloatSymbol);
        *(void**)(x + 0x30) = outlet_new(x, gBangSymbol);
        t_symbol sym;
        t_symbol sym2;
        t_symbol* s = gensym(&sym, "ft1");
        t_symbol* s2 = gensym(&sym2, "float");
        inlet_new(x, x, *s2, *s);
        floatinlet_new(x, x + 0x58);
    }
    return x;
}

// @ 0x00a5fae0  EA::Audio::Eapd::line_setup
bool line_setup()
{
    t_symbol sym;
    t_symbol* s = gensym(&sym, "line");
    spLineClass = class_new8(*s, (void*)line_new, (void*)metro_new,
                             0x70, 0, 5, 5, 0);
    bool ok = spLineClass != 0;
    t_symbol sym2;
    t_symbol* s2 = gensym(&sym2, "ft1");
    ok &= class_addmethod2(spLineClass, (void*)line_ft1, *s2, 1, 0);
    t_symbol sym3;
    t_symbol* s3 = gensym(&sym3, "stop");
    ok &= class_addmethod1(spLineClass, (void*)line_stop, *s3, 0);
    t_symbol sym4;
    t_symbol* s4 = gensym(&sym4, "set");
    ok &= class_addmethod2(spLineClass, (void*)line_set, *s4, 1, 0);
    ok &= class_doaddfloat(spLineClass, (void*)line_float);
    t_symbol sym5;
    t_symbol* s5 = gensym(&sym5, "pause");
    ok &= class_addmethod2(spLineClass, (void*)line_pause, *s5, 1, 0);
    return ok;
}

// ============================================================ timer object
// @ 0x00a5fc10  EA::Audio::Eapd::timer_bang
void timer_bang(char* x)
{
    if (*(char*)(x + 0x30) != 0)
        return;
    float elapsed = (float)clock_gettimesince(*(double*)(x + 0x28));
    t_outlet* lst = *(t_outlet**)(x + 0xc);
    gOutletCount++;
    if (gOutletCount < 1000) {
        t_outconnect* oc = lst->o_connections;
        while (oc) {
            outlet_float(oc->oc_to, elapsed);
            oc = oc->oc_next;
        }
    }
    gOutletCount--;
}

// @ 0x00a5fc80  EA::Audio::Eapd::timer_pause
void timer_pause(char* x, float f)
{
    if (0.0f != f) {
        if (*(char*)(x + 0x30) == 0) {
            *(double*)(x + 0x28) = clock_gettimesince(*(double*)(x + 0x28));
            *(char*)(x + 0x30) = 1;
        }
        return;
    }
    if (*(char*)(x + 0x30) != 0) {
        *(double*)(x + 0x28) =
            clock_getlogicaltimeafter(-(float)*(double*)(x + 0x28));
        *(char*)(x + 0x30) = 0;
    }
}

// @ 0x00a5fce0  EA::Audio::Eapd::timer_new
void* timer_new()
{
    char* x = (char*)pd_new(spTimerClass);
    if (x) {
        *(char*)(x + 0x30) = 0;
        *(double*)(x + 0x28) = (double)clock_getlogicaltime();
        t_symbol sym;
        t_symbol sym2;
        t_symbol* s = gensym(&sym, "float");
        outlet_new(x, *s);
        t_symbol* s2 = gensym(&sym, "bang2");
        t_symbol* s3 = gensym(&sym2, "bang");
        inlet_new(x, x, *s3, *s2);
    }
    return x;
}

// @ 0x00a5fd70  EA::Audio::Eapd::timer_setup
bool timer_setup()
{
    t_symbol sym;
    t_symbol* s = gensym(&sym, "timer");
    spTimerClass = class_new7(*s, (void*)timer_new, (void*)0, 0x38, 0, 5, 0);
    bool ok = spTimerClass != 0;
    ok &= class_addbang(spTimerClass, (void*)timer_bang);
    t_symbol sym2;
    t_symbol* s2 = gensym(&sym2, "bang2");
    ok &= class_addmethod1(spTimerClass, (void*)timer_start, *s2, 0);
    t_symbol sym3;
    t_symbol* s3 = gensym(&sym3, "pause");
    ok &= class_addmethod2(spTimerClass, (void*)timer_pause, *s3, 1, 0);
    return ok;
}

// ============================================================= pipe object
// @ 0x00a5fe20  EA::Audio::Eapd::pipe_list
void pipe_list(char* x, t_symbol s, int argc, t_atom* argv)
{
    char* q = *(char**)(x + 0x4c);
    if (!q)
        return;
    *(char**)(x + 0x4c) = *(char**)q;
    *(int*)q = 0;
    if (argc > *(int*)(x + 0x28))
        argc = *(int*)(x + 0x28);
    int i;
    for (i = 0; i < argc; i++) {
        memcpy(q + 8 + i * 0xc, (char*)argv + i * 0xc, 0xc);
    }
    for (; i < *(int*)(x + 0x28); i++) {
        memcpy(q + 8 + i * 0xc, *(char**)(x + 0x40) + i * 0x10, 0xc);
    }
    if (*(int*)(x + 0x48) == 0) {
        *(float*)(q + 4) = *(float*)(x + 0x30);
        clock_delay(*(void**)(x + 0x50), *(float*)(x + 0x30));
        *(char**)(x + 0x48) = q;
        *(double*)(x + 0x38) = (double)clock_getlogicaltime();
        return;
    }
    *(float*)(q + 4) = (float)clock_gettimesince(*(double*)(x + 0x38));
    char* p = *(char**)(x + 0x48);
    char* n = *(char**)p;
    while (n) {
        p = n;
        n = *(char**)n;
    }
    *(char**)p = q;
    *(double*)(x + 0x38) = (double)clock_getlogicaltime();
}

// @ 0x00a5ff10  EA::Audio::Eapd::pipe_tick
void pipe_tick(char* x)
{
    char* q = *(char**)(x + 0x48);
    *(char**)(x + 0x48) = *(char**)q;
    *(char**)q = *(char**)(x + 0x4c);
    int n = *(int*)(x + 0x28) - 1;
    *(char**)(x + 0x4c) = q;
    for (; n >= 0; n--) {
        char* e = q + (n * 3 + 3) * 4;
        int   kind = *(int*)(e - 4);
        if (kind == 1) {
            float v = *(float*)e;
            gOutletCount++;
            if (gOutletCount < 1000) {
                void* o = *(void**)(*(char**)(x + 0x40) + n * 0x10 + 0xc);
                t_outconnect* oc = *(t_outconnect**)((char*)o + 8);
                while (oc) {
                    outlet_float(oc->oc_to, v);
                    oc = oc->oc_next;
                }
            }
            gOutletCount--;
        } else if (kind == 2) {
            outlet_symbol(*(void**)(*(char**)(x + 0x40) + n * 0x10 + 0xc),
                          *(t_symbol*)e, *(t_symbol*)(e + 4));
        }
    }
    if (*(char**)(x + 0x48) != 0)
        clock_delay(*(void**)(x + 0x50), *(float*)(*(char**)(x + 0x48) + 4));
}

} } }  // namespace EA::Audio::Eapd
