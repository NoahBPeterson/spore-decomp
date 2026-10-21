// Slice s00a56460 - EA::Audio::Eapd (Pure Data port) math objects:
// atan / atan2 / sqrt / log / exp / abs / clip constructors, the atan2 and clip
// perform bodies, and clip_setup.
// The reference function table has no boundary after atan_new (0xa56490), sqrt_new,
// log_new, exp_new or abs_new, so those VAs are bounded over <new>+<float> and cannot
// be byte-exact as two separate C++ functions.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

namespace EA { namespace Audio { namespace Eapd {

struct t_class;
struct t_outlet;
struct t_outconnect {         // 8
    t_outconnect* oc_next;    // +0
    t_outlet*     oc_to;      // +4
};
struct t_outlet {             // 0x1c
    void*         o_owner;        // +0x00
    t_outlet*     o_next;         // +0x04
    t_outconnect* o_connections;  // +0x08
};

struct t_symbol {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};

extern t_symbol gFloatSymbol;    // 0x16758c4
extern int      gOutletCount;    // 0x167545c

extern t_class* spAtanClass;     // 0x167559c
extern t_class* spAtan2Class;    // 0x1675588
extern t_class* spSqrtClass;     // 0x16755e0
extern t_class* spLogClass;      // 0x16755c4
extern t_class* spExpClass;      // 0x16755ac
extern t_class* spAbsClass;      // 0x167557c
extern t_class* spClipClass;     // 0x1675578

void*     pd_new(t_class* c);                                          // 0xa49390
void*     floatinlet_new(void* owner, void* dest);                     // 0xa49a00
void*     outlet_new(void* owner, t_symbol s);                         // 0xa49d30
void      outlet_float(void* to, float f);                             // 0xa49570
t_symbol* gensym(t_symbol* out, const char* s);                        // 0xa675f0
t_class*  class_new8(t_symbol name, void* newmethod, void* freemethod,
                     int size, int flags, int a1, int a2, int a3);     // 0xa48f00
bool      class_doaddfloat(t_class* c, void* fn);                      // 0xa47f30

// Sends `v` out of the outlet list `lst`, guarded by the outlet-nesting counter.
__forceinline void outlet_cnt(t_outlet* lst, float v)
{
    if (++gOutletCount < 1000) {
        t_outconnect* oc;
        for (oc = lst->o_connections; oc; oc = oc->oc_next)
            outlet_float(oc->oc_to, v);
    }
    gOutletCount--;
}

// @ 0x00a56460  EA::Audio::Eapd::atan_new
void* atan_new()
{
    void* x = pd_new(spAtanClass);
    if (x) {
        outlet_new(x, gFloatSymbol);
    }
    return x;
}

// @ 0x00a564f0  EA::Audio::Eapd::atan2_new
void* atan2_new()
{
    void* x = pd_new(spAtan2Class);
    if (x) {
        floatinlet_new(x, (char*)x + 0x28);
        *(float*)((char*)x + 0x28) = 0.0f;
        outlet_new(x, gFloatSymbol);
    }
    return x;
}

// @ 0x00a56540  EA::Audio::Eapd::atan2_float
void atan2_float(void* x, float f)
{
    float r;
    if (f == 0.0f && *(float*)((char*)x + 0x28) == 0.0f)
        r = 0.0f;
    else
        r = (float)atan2((double)f, (double)*(float*)((char*)x + 0x28));
    outlet_cnt(*(t_outlet**)((char*)x + 0xc), r);
}

// @ 0x00a565d0  EA::Audio::Eapd::sqrt_new
void* sqrt_new()
{
    void* x = pd_new(spSqrtClass);
    if (x) {
        outlet_new(x, gFloatSymbol);
    }
    return x;
}

// @ 0x00a56670  EA::Audio::Eapd::log_new
void* log_new()
{
    void* x = pd_new(spLogClass);
    if (x) {
        outlet_new(x, gFloatSymbol);
    }
    return x;
}

// @ 0x00a56720  EA::Audio::Eapd::exp_new
void* exp_new()
{
    void* x = pd_new(spExpClass);
    if (x) {
        outlet_new(x, gFloatSymbol);
    }
    return x;
}

// @ 0x00a567e0  EA::Audio::Eapd::abs_new
void* abs_new()
{
    void* x = pd_new(spAbsClass);
    if (x) {
        outlet_new(x, gFloatSymbol);
    }
    return x;
}

// @ 0x00a56870  EA::Audio::Eapd::clip_new
void* clip_new(float f1, float f2)
{
    void* x = pd_new(spClipClass);
    if (x) {
        floatinlet_new(x, (char*)x + 0x28);
        floatinlet_new(x, (char*)x + 0x2c);
        outlet_new(x, gFloatSymbol);
        *(float*)((char*)x + 0x28) = f1;
        *(float*)((char*)x + 0x2c) = f2;
    }
    return x;
}

// @ 0x00a568d0  EA::Audio::Eapd::clip_float
void clip_float(void* x, float f)
{
    float lo = *(float*)((char*)x + 0x28);
    float r;
    if (lo > f) {
        r = lo;
    } else {
        float hi = *(float*)((char*)x + 0x2c);
        if (f > hi) r = hi;
        else r = f;
    }
    outlet_cnt(*(t_outlet**)((char*)x + 0xc), r);
}

// @ 0x00a56950  EA::Audio::Eapd::clip_setup
bool clip_setup()
{
    t_symbol  s;
    t_symbol* sym = gensym(&s, "clip");
    bool ok = (spClipClass = class_new8(*sym, (void*)clip_new, 0, 0x30, 0, 5, 5, 0)) != 0;
    ok &= class_doaddfloat(spClipClass, (void*)clip_float);
    return ok;
}

} } }
