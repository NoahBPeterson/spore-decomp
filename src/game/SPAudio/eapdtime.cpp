// src/game/SPAudio/eapdtime.cpp -- migrated from slice(s) s00a5fff0, s00a5f070, s00a5e0f0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdtime.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"

// ---- items of slice s00a5e0f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
bool  clock_ispaused(void* clock);                                       // 0xa491d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  clock_delay(void* clock, float f);                                 // 0xa491e0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  clock_unset(void* clock);                                          // 0xa490b0
}
}
}
// ---- items of slice s00a5e0f0 end

// ---- items of slice s00a5f070 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
extern t_class*  spDelayClass;             // 0x1675800
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class*  spMetroClass;             // 0x16757f4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class*  spLineClass;              // 0x16757f8
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class*  spTimerClass;             // 0x16757f0
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
t_class*  class_new6(t_symbol name, void* newmethod, void* freemethod,
                     int size, int flags, int a1);                        // 0xa48e50
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
t_class*  class_new8(t_symbol name, void* newmethod, void* freemethod,
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
bool class_addbang(t_class* c, void* fn);                                // 0xa47f10
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addcreator(void* fn, t_symbol name, int a1, int a2);          // 0xa48e00
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
bool class_addmethod2(t_class* c, void* fn, t_symbol name, int a1, int a2);  // 0xa48a80
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
void* clock_new(void* pd, void* fn);                                     // 0xa49080
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  clock_pause(void* c);                                              // 0xa49170
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  clock_unpause(void* c);                                            // 0xa491a0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
double clock_getlogicaltime();                                           // 0xa49210
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
double clock_gettimesince(double t);                                     // 0xa49220
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
double clock_getlogicaltimeafter(float t);                               // 0xa49240
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  clock_free(void* c);                                              // 0xa49260
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
void  outlet_float(void* o, float f);                                    // 0xa49570
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
void  outlet_symbol(void* o, t_symbol a, t_symbol b);                    // 0xa49df0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* inlet_new(void* owner, void* dest, t_symbol a, t_symbol b);        // 0xa49740
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
void* memcpy(void* dst, const void* src, unsigned n);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* metro_new(float f);                       // 0xa5f460 (freemethod)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  metro_stop(char* x);                      // 0xa5f3f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  metro_tick(char* x);                      // 0xa5f300
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  metro_float(char* x, float f);            // 0xa5f340
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  spin_bang(char* x);                       // 0xa5efd0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  spin_stop(char* x);                       // 0xa5f000
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  spin_float(char* x, float f);             // 0xa5f030
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  timer_start(char* x);                     // 0xa5fbf0
}
}
}
// ---- items of slice s00a5f070 end

// ---- items of slice s00a5fff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
void   pipe_tick(void* x);                                               // 0xa5ff10
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool delay_setup();                                                      // 0xa5f1e0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool metro_setup();                                                      // 0xa5f540
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool line_setup();                                                       // 0xa5fae0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool timer_setup();                                                      // 0xa5fd70
}
}
}
// ---- items of slice s00a5fff0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace EA { namespace Audio { namespace Eapd { bool pipe_setup(); }}}  // 0x00a60390 (stays in the slice: not this object's)

// @ 0x00a5efd0
namespace EA { namespace Audio { namespace Eapd {
void spin_bang(char* x)
{
    if (!clock_ispaused(*(void**)(x + 0x28)))
        clock_delay(*(void**)(x + 0x28), *(float*)(x + 0x2c));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f000
namespace EA { namespace Audio { namespace Eapd {
void spin_stop(char* x)
{
    if (!clock_ispaused(*(void**)(x + 0x28)))
        clock_unset(*(void**)(x + 0x28));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f030
namespace EA { namespace Audio { namespace Eapd {
void spin_float(char* x, float f)
{
    if (f < 0.0f)
        f = 0.0f;
    if (!clock_ispaused(*(void**)(x + 0x28)))
        *(float*)(x + 0x2c) = f;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f070
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f0e0
namespace EA { namespace Audio { namespace Eapd {
void delay_pause(char* x, float f)
{
    if (f != 0.0f) {
        clock_pause(*(void**)(x + 0x28));
        return;
    }
    clock_unpause(*(void**)(x + 0x28));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f120
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f1e0
namespace EA { namespace Audio { namespace Eapd {
bool delay_setup()
{
    t_symbol sym;
    spDelayClass = class_new6(*gensym(&sym, "delay"), (void*)delay_new, (void*)metro_new,
                              0x30, 0, 5);
    bool ok = spDelayClass != 0;
    ok &= class_addcreator((void*)delay_new, *gensym(&sym, "del"), 5, 0);
    ok &= class_addbang(spDelayClass, (void*)spin_bang);
    ok &= class_addmethod1(spDelayClass, (void*)spin_stop, *gensym(&sym, "stop"), 0);
    ok &= class_addmethod2(spDelayClass, (void*)spin_float, *gensym(&sym, "ft1"), 1, 0);
    ok &= class_doaddfloat(spDelayClass, (void*)delay_doaddfloat);
    ok &= class_addmethod2(spDelayClass, (void*)delay_pause, *gensym(&sym, "pause"), 1, 0);
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f300
namespace EA { namespace Audio { namespace Eapd {
void metro_tick(char* x)
{
    *(int*)(x + 0x30) = 0;
    outlet_bang(*(void**)(x + 0xc));
    if (*(int*)(x + 0x30) == 0)
        clock_delay(*(void**)(x + 0x28), *(float*)(x + 0x2c));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f340
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f3c0
namespace EA { namespace Audio { namespace Eapd {
void metro_bang(char* x)
{
    if (!clock_ispaused(*(void**)(x + 0x28)))
        metro_float(x, 1.0f);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f3f0
namespace EA { namespace Audio { namespace Eapd {
void metro_stop(char* x)
{
    if (!clock_ispaused(*(void**)(x + 0x28)))
        metro_float(x, 0.0f);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f420
namespace EA { namespace Audio { namespace Eapd {
void metro_ft1(char* x, float f)
{
    if (f < 1.0f)
        f = 1.0f;
    if (!clock_ispaused(*(void**)(x + 0x28)))
        *(float*)(x + 0x2c) = f;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f460
namespace EA { namespace Audio { namespace Eapd {
void metro_free(char* x)
{
    clock_free(*(void**)(x + 0x28));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f540
namespace EA { namespace Audio { namespace Eapd {
bool metro_setup()
{
    t_symbol sym;
    spMetroClass = class_new7(*gensym(&sym, "metro"), (void*)metro_new, (void*)metro_stop,
                              0x34, 0, 5, 0);
    bool ok = spMetroClass != 0;
    ok &= class_addbang(spMetroClass, (void*)metro_bang);
    ok &= class_addmethod1(spMetroClass, (void*)metro_stop, *gensym(&sym, "stop"), 0);
    ok &= class_addmethod2(spMetroClass, (void*)metro_ft1, *gensym(&sym, "ft1"), 1, 0);
    ok &= class_doaddfloat(spMetroClass, (void*)metro_float);
    ok &= class_addmethod2(spMetroClass, (void*)delay_pause, *gensym(&sym, "pause"), 1, 0);
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f630
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f750
namespace EA { namespace Audio { namespace Eapd {
void line_float(char* x, float f)
{
    if (clock_ispaused(*(void**)(x + 0x28)))
        return;
    double now = clock_getlogicaltime();
    if (*(int*)(x + 0x54) != 0 && *(float*)(x + 0x68) > 0.0f) {
        float v;
        if (now > *(double*)(x + 0x38))
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f8b0
namespace EA { namespace Audio { namespace Eapd {
void line_ft1(char* x, float f)
{
    if (clock_ispaused(*(void**)(x + 0x28)))
        return;
    *(float*)(x + 0x68) = f;
    *(int*)(x + 0x54) = 1;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f8e0
namespace EA { namespace Audio { namespace Eapd {
void line_stop(char* x)
{
    if (clock_ispaused(*(void**)(x + 0x28)))
        return;
    *(float*)(x + 0x40) = *(float*)(x + 0x50);
    clock_unset(*(void**)(x + 0x28));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f910
namespace EA { namespace Audio { namespace Eapd {
void line_set(char* x, float f)
{
    if (clock_ispaused(*(void**)(x + 0x28)))
        return;
    clock_unset(*(void**)(x + 0x28));
    *(float*)(x + 0x50) = f;
    *(float*)(x + 0x40) = f;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f950
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5f9f0
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5fae0
namespace EA { namespace Audio { namespace Eapd {
bool line_setup()
{
    t_symbol sym;
    spLineClass = class_new8(*gensym(&sym, "line"), (void*)line_new, (void*)metro_new,
                             0x70, 0, 5, 5, 0);
    bool ok = spLineClass != 0;
    ok &= class_addmethod2(spLineClass, (void*)line_ft1, *gensym(&sym, "ft1"), 1, 0);
    ok &= class_addmethod1(spLineClass, (void*)line_stop, *gensym(&sym, "stop"), 0);
    ok &= class_addmethod2(spLineClass, (void*)line_set, *gensym(&sym, "set"), 1, 0);
    ok &= class_doaddfloat(spLineClass, (void*)line_float);
    ok &= class_addmethod2(spLineClass, (void*)line_pause, *gensym(&sym, "pause"), 1, 0);
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5fc10
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5fc80
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5fce0
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5fd70
namespace EA { namespace Audio { namespace Eapd {
bool timer_setup()
{
    t_symbol sym;
    spTimerClass = class_new7(*gensym(&sym, "timer"), (void*)timer_new, (void*)0, 0x38, 0, 5, 0);
    bool ok = spTimerClass != 0;
    ok &= class_addbang(spTimerClass, (void*)timer_bang);
    ok &= class_addmethod1(spTimerClass, (void*)timer_start, *gensym(&sym, "bang2"), 0);
    ok &= class_addmethod2(spTimerClass, (void*)timer_pause, *gensym(&sym, "pause"), 1, 0);
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5fe20
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ff10
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5fff0
namespace EA { namespace Audio { namespace Eapd {
void pipe_flush(void* x)
{
    while (*(int*)((char*)x + 0x48) != 0)
        pipe_tick(x);
    clock_unset(*(void**)((char*)x + 0x50));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a60020
namespace EA { namespace Audio { namespace Eapd {
void pipe_clear(char* x)
{
    clock_unset(*(void**)(x + 0x50));
    while (*(void**)(x + 0x48) != 0) {
        char* e = *(char**)(x + 0x48);
        *(void**)(x + 0x48) = *(void**)e;
        *(void**)e = *(void**)(x + 0x4c);
        *(char**)(x + 0x4c) = e;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a60050
namespace EA { namespace Audio { namespace Eapd {
void pipe_pause(char* x, float f)
{
    if (0.0f != f) {
        if (!clock_ispaused(*(void**)(x + 0x50))) {
            *(double*)(x + 0x38) = clock_gettimesince(*(double*)(x + 0x38));
            clock_pause(*(void**)(x + 0x50));
        }
        return;
    }
    if (clock_ispaused(*(void**)(x + 0x50))) {
        *(double*)(x + 0x38) = clock_getlogicaltimeafter(-(float)*(double*)(x + 0x38));
        clock_unpause(*(void**)(x + 0x50));
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a600d0
namespace EA { namespace Audio { namespace Eapd {
void pipe_free(char* x)
{
    if (*(void**)(x + 0x40) != 0)
        freebytes(*(void**)(x + 0x40), *(int*)(x + 0x28) << 4);
    if (*(void**)(x + 0x44) != 0) {
        int k = *(int*)(x + 0x28);
        k--;
        int sz = k * 3;
        sz = sz * 4 + 0x14;
        freebytes(*(void**)(x + 0x44), sz * *(int*)(x + 0x2c));
    }
    if (*(void**)(x + 0x50) != 0)
        clock_free(*(void**)(x + 0x50));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a60470
namespace EA {
namespace Audio {
namespace Eapd {
bool x_time_setup()
{
    bool ok = delay_setup() & 1;
    ok &= metro_setup();
    ok &= line_setup();
    ok &= timer_setup();
    ok = pipe_setup() & ok;
    return ok;
}
}
}
}  // namespace EA::Audio::Eapd
