// src/game/SPAudio/eapdobject.cpp -- migrated from slice(s) s00a49670 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdobject.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stdio.h>
#include <string.h>

// ---- items of slice s00a49670 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct t_object;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_inlet;
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
struct t_outconnect;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef t_class* t_pd;
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
inline bool operator==(const t_symbol& a, const t_symbol& b) { return a.mHash == b.mHash; }
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom {           // 12 bytes
    int a_type;
    union {
        float    w_float;
        t_symbol w_symbol;
    } a_w;
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_methodentry {
    t_symbol me_name;     // +0
    void*    me_fun;      // +8
    int      me_arg[6];   // +0xc
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class {
    char pad00[0x1c];
    t_methodentry* c_methods;                        // +0x1c
    int            c_nmethod;                        // +0x20
    char pad24[4];
    void (*c_bangmethod)(t_pd* x);                   // +0x28
    void (*c_floatmethod)(t_pd* x, float f);         // +0x2c
    void (*c_symbolmethod)(t_pd* x, t_symbol s);     // +0x30
    char pad34[0x49 - 0x34];
    char c_isobject;                                 // +0x49 (pd_checkobject)
    char c_firstin;                                  // +0x4a (first inlet is the object)
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gobj {
    t_class* g_pd;        // +0x00
    t_gobj*  g_next;      // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_object : t_gobj {
    void*     te_binbuf;  // +0x08
    t_outlet* te_outlet;  // +0x0c
    t_inlet*  te_inlet;   // +0x10
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_inlet {              // 0x28
    t_class*  i_pd;           // +0x00
    t_inlet*  i_next;         // +0x04
    t_object* i_owner;        // +0x08
    t_pd*     i_dest;         // +0x0c
    t_symbol  i_symfrom;      // +0x10
    union {
        t_symbol i_symto;     // +0x18 (message inlet)
        void*    i_destp;     // +0x18 (float/symbol inlet destination)
    } u;
    t_symbol  i_symempty;     // +0x20
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outconnect {         // 8
    t_outconnect* oc_next;    // +0
    t_inlet*      oc_to;      // +4
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
extern t_class* spOtherinletClass;     // 0x1675448 (4th inlet class)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spInletClass;          // 0x1675450
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spSymbolinletClass;    // 0x1675454
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spFloatinletClass;     // 0x1675458
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern int gObjCount;                  // 0x167544c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern int gOutletCount;               // 0x167545c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol gSymbolSymbol;         // 0x1675894
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol gEmptySymbol;          // 0x167589c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol gListSymbol;           // 0x16758ac
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol gBangSymbol;           // 0x16758b4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol gFloatSymbol;          // 0x16758c4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* getbytes(int n, const char* tag);                          // 0xa49610
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  freebytes(void* p, int n);                                 // 0xa49650
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* pd_new(t_class* c);                                        // 0xa49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_bang(void* x);                                          // 0xa49560
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  outlet_float(void* x, float f);                            // 0xa49570
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_symbol(void* x, t_symbol s);                            // 0xa49590
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_list(void* x, t_symbol s, int argc, t_atom* argv);      // 0xa495b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_typedmess(void* x, t_symbol s, int argc, t_atom* argv); // 0xa48100
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_vmess(void* x, t_symbol s, const char* fmt, ...);       // 0xa487f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol* gensym(t_symbol* out, const char* s);                  // 0xa675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class* class_new(t_symbol name, void* newmethod, void* freemethod, int size, int flags, int a1);  // 0xa48e50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addbang(t_class* c, void* fn);                        // 0xa47f10
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_doaddfloat(t_class* c, void* fn);                     // 0xa47f30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addsymbol(t_class* c, void* fn);                      // 0xa47f50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addlist(t_class* c, void* fn);                        // 0xa47f70
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addanything(t_class* c, void* fn);                    // 0xa47f90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
static void inlet_bang(t_inlet* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
static void inlet_float(t_inlet* x, float f);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
static void inlet_symbol(t_inlet* x, t_symbol s);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
static void inlet_list(t_inlet* x, t_symbol s, int argc, t_atom* argv);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
static void inlet_anything(t_inlet* x, t_symbol s, int argc, t_atom* argv);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
static void floatinlet_float(t_inlet* x, float f);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
static void symbolinlet_symbol(t_inlet* x, t_symbol s);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void inlet_symbol(t_inlet* x, t_symbol s)
{
    if (x->i_symfrom == gSymbolSymbol)
        pd_vmess(x->i_dest, x->u.i_symto, "s", s);
    else if (x->i_symfrom == gEmptySymbol)
        pd_symbol(x->i_dest, s);
}
}
}
}
// ---- items of slice s00a49670 end

// @ 0x00a49740
namespace EA { namespace Audio { namespace Eapd {
t_inlet* inlet_new(t_object* owner, t_pd* dest, t_symbol s1, t_symbol s2)
{
    t_inlet* x = (t_inlet*)pd_new(spInletClass);
    if (x) {
        t_inlet* i2;
        x->i_owner = owner;
        x->i_dest = dest;
        x->u.i_symto = s2;
        x->i_symfrom = s1;
        x->i_next = 0;
        if ((i2 = owner->te_inlet)) {
            for (; i2->i_next; i2 = i2->i_next)
                ;
            i2->i_next = x;
        } else {
            owner->te_inlet = x;
        }
        x->i_symempty = gEmptySymbol;
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a497d0
namespace EA { namespace Audio { namespace Eapd {
void inlet_bang(t_inlet* x)
{
    if (x->i_symfrom == gBangSymbol)
        pd_vmess(x->i_dest, x->u.i_symto, "");
    else if (x->i_symfrom == gEmptySymbol)
        pd_bang(x->i_dest);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49810
namespace EA { namespace Audio { namespace Eapd {
void inlet_float(t_inlet* x, float f)
{
    if (x->i_symfrom == gFloatSymbol)
        pd_vmess(x->i_dest, x->u.i_symto, "f", (double)f);
    else if (x->i_symfrom == gEmptySymbol)
        outlet_float(x->i_dest, f);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a498c0
namespace EA { namespace Audio { namespace Eapd {
void inlet_list(t_inlet* x, t_symbol s, int argc, t_atom* argv)
{
    t_symbol from = x->i_symfrom;

    if (from == gListSymbol || from == gFloatSymbol || from == gSymbolSymbol)
        pd_typedmess(x->i_dest, x->u.i_symto, argc, argv);
    else if (from == gEmptySymbol)
        pd_list(x->i_dest, s, argc, argv);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49930
namespace EA { namespace Audio { namespace Eapd {
void inlet_anything(t_inlet* x, t_symbol s, int argc, t_atom* argv)
{
    if (x->i_symfrom == s)
        pd_typedmess(x->i_dest, x->u.i_symto, argc, argv);
    else if (x->i_symfrom == gEmptySymbol)
        pd_typedmess(x->i_dest, s, argc, argv);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49990
namespace EA { namespace Audio { namespace Eapd {
void inlet_free(t_inlet* x)
{
    t_inlet* i = x->i_owner->te_inlet;

    if (i == x) {
        x->i_owner->te_inlet = x->i_next;
    } else if (i) {
        while (i->i_next != x) {
            i = i->i_next;
            if (!i) {
                freebytes(x, 0x28);
                return;
            }
        }
        i->i_next = x->i_next;
    }
    freebytes(x, 0x28);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a499e0
namespace EA { namespace Audio { namespace Eapd {
void floatinlet_float(t_inlet* x, float f)
{
    *(float*)x->u.i_destp = f;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49a00
namespace EA { namespace Audio { namespace Eapd {
t_inlet* floatinlet_new(t_object* owner, float* dest)
{
    t_inlet* x = (t_inlet*)pd_new(spFloatinletClass);
    if (x) {
        t_inlet* i2;
        x->i_owner = owner;
        x->i_dest = 0;
        x->i_symfrom = gFloatSymbol;
        x->u.i_destp = dest;
        x->i_next = 0;
        if ((i2 = owner->te_inlet)) {
            for (; i2->i_next; i2 = i2->i_next)
                ;
            i2->i_next = x;
        } else {
            owner->te_inlet = x;
        }
        x->i_symempty = gEmptySymbol;
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49a90
namespace EA { namespace Audio { namespace Eapd {
void symbolinlet_symbol(t_inlet* x, t_symbol s)
{
    t_symbol* p = (t_symbol*)x->u.i_destp;
    *p = s;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49ab0
namespace EA { namespace Audio { namespace Eapd {
t_inlet* symbolinlet_new(t_object* owner, t_symbol* dest)
{
    t_inlet* x = (t_inlet*)pd_new(spSymbolinletClass);
    if (x) {
        t_inlet* i2;
        x->i_owner = owner;
        x->i_dest = 0;
        x->i_symfrom = gSymbolSymbol;
        x->u.i_destp = dest;
        x->i_next = 0;
        if ((i2 = owner->te_inlet)) {
            for (; i2->i_next; i2 = i2->i_next)
                ;
            i2->i_next = x;
        } else {
            owner->te_inlet = x;
        }
        x->i_symempty = gEmptySymbol;
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49b40
namespace EA { namespace Audio { namespace Eapd {
void obj_list(t_object* x, t_symbol s, int argc, t_atom* argv)
{
    t_inlet* i = x->te_inlet;

    if (argc) {
        if (i) {
            int n = argc - 1;
            t_atom* ap = argv + 1;
            do {
                if (!(n--))
                    break;
                if (ap->a_type == 1)
                    outlet_float(i, ap->a_w.w_float);
                else
                    pd_symbol(i, ap->a_w.w_symbol);
                i = i->i_next;
                ap++;
            } while (i);
        }
        if (argv->a_type == 1)
            outlet_float(x, argv->a_w.w_float);
        else
            pd_symbol(x, argv->a_w.w_symbol);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49be0
namespace EA {
namespace Audio {
namespace Eapd {
bool obj_init()
{
    t_symbol s;
    bool ok;

    spInletClass = class_new(*gensym(&s, "inlet"), 0, 0, 0x28, 1, 0);
    ok = spInletClass != 0;
    ok &= class_addbang(spInletClass, (void*)inlet_bang);
    ok &= class_doaddfloat(spInletClass, (void*)inlet_float);
    ok &= class_addsymbol(spInletClass, (void*)inlet_symbol);
    ok &= class_addlist(spInletClass, (void*)inlet_list);
    ok &= class_addanything(spInletClass, (void*)inlet_anything);
    spFloatinletClass = class_new(*gensym(&s, "inlet"), 0, 0, 0x28, 1, 0);
    ok &= spFloatinletClass != 0;
    ok &= class_doaddfloat(spFloatinletClass, (void*)floatinlet_float);
    spSymbolinletClass = class_new(*gensym(&s, "inlet"), 0, 0, 0x28, 1, 0);
    ok &= spSymbolinletClass != 0;
    ok &= class_addsymbol(spSymbolinletClass, (void*)symbolinlet_symbol);
    return ok;
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a49d00
namespace EA { namespace Audio { namespace Eapd {
void FUN_00a49d00()
{
    gObjCount++;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49d10
namespace EA { namespace Audio { namespace Eapd {
void FUN_00a49d10(t_outlet* x, t_symbol s)
{
    if (x) {
        x->o_symto.mHash = s.mHash;
        x->o_symto.mpName = s.mpName;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49d30
namespace EA { namespace Audio { namespace Eapd {
t_outlet* outlet_new(t_object* owner, t_symbol s)
{
    t_outlet* o = (t_outlet*)getbytes(0x1c, "EAPd/t_outlet");
    t_outlet* o2;

    o->o_owner = owner;
    o->o_next = 0;
    if ((o2 = owner->te_outlet)) {
        for (; o2->o_next; o2 = o2->o_next)
            ;
        o2->o_next = o;
    } else {
        owner->te_outlet = o;
    }
    o->o_connections = 0;
    o->o_symfrom = s;
    o->o_symto = gEmptySymbol;
    return o;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49da0
namespace EA { namespace Audio { namespace Eapd {
void outlet_bang(t_outlet* x)
{
    if (++gOutletCount < 1000) {
        t_outconnect* oc;
        for (oc = x->o_connections; oc; oc = oc->oc_next)
            pd_bang(oc->oc_to);
    }
    gOutletCount--;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49df0
namespace EA { namespace Audio { namespace Eapd {
void outlet_symbol(t_outlet* x, t_symbol s)
{
    if (++gOutletCount < 1000) {
        t_outconnect* oc;
        for (oc = x->o_connections; oc; oc = oc->oc_next)
            pd_symbol(oc->oc_to, s);
    }
    gOutletCount--;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49e40
namespace EA { namespace Audio { namespace Eapd {
void outlet_list(t_outlet* x, t_symbol s, int argc, t_atom* argv)
{
    if (++gOutletCount < 1000) {
        t_outconnect* oc;
        for (oc = x->o_connections; oc; oc = oc->oc_next)
            pd_list(oc->oc_to, s, argc, argv);
    }
    gOutletCount--;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49eb0
namespace EA { namespace Audio { namespace Eapd {
void outlet_anything(t_outlet* x, t_symbol s, int argc, t_atom* argv)
{
    if (++gOutletCount < 1000) {
        t_outconnect* oc;
        for (oc = x->o_connections; oc; oc = oc->oc_next)
            pd_typedmess(oc->oc_to, s, argc, argv);
    }
    gOutletCount--;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49f20
namespace EA { namespace Audio { namespace Eapd {
void outlet_free(t_outlet* x)
{
    t_outlet* o = x->o_owner->te_outlet;

    if (o == x) {
        x->o_owner->te_outlet = x->o_next;
    } else if (o) {
        while (o->o_next != x) {
            o = o->o_next;
            if (!o) {
                freebytes(x, 0x1c);
                return;
            }
        }
        o->o_next = x->o_next;
    }
    freebytes(x, 0x1c);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49f70
namespace EA { namespace Audio { namespace Eapd {
t_outconnect* obj_connect(t_object* source, int outno, t_object* sink, int inno)
{
    t_outlet* o = source->te_outlet;
    t_inlet* i;

    if (!o)
        return 0;
    while (outno) {
        o = o->o_next;
        outno--;
        if (!o)
            return 0;
    }
    if (!o)
        return 0;
    if (sink->g_pd->c_firstin) {
        if (!inno) {
            i = (t_inlet*)sink;
            goto add;
        }
        inno--;
    }
    i = sink->te_inlet;
    if (!i)
        return 0;
    while (inno) {
        i = i->i_next;
        inno--;
        if (!i)
            return 0;
    }
    if (!i)
        return 0;
add:
    {
        t_outconnect* oc = (t_outconnect*)getbytes(8, "EAPd/t_outconnect");
        t_outconnect* oc2;
        oc->oc_next = 0;
        oc->oc_to = i;
        if ((oc2 = o->o_connections)) {
            while (oc2->oc_next)
                oc2 = oc2->oc_next;
            oc2->oc_next = oc;
        } else {
            o->o_connections = oc;
        }
        return oc;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a010
namespace EA { namespace Audio { namespace Eapd {
void obj_disconnect(t_object* source, int outno, t_object* sink, int inno)
{
    t_outlet* o = source->te_outlet;
    t_inlet* i;

    if (o) {
        for (; outno; outno--) {
            if (!o)
                return;
            o = o->o_next;
        }
    }
    if (sink->g_pd->c_firstin) {
        if (!inno) {
            i = (t_inlet*)sink;
            goto remove;
        }
        inno--;
    }
    i = sink->te_inlet;
    if (!i)
        return;
    while (inno) {
        i = i->i_next;
        inno--;
        if (!i)
            return;
    }
    if (!i)
        return;
remove:
    {
        t_outconnect* oc = o->o_connections;
        t_outconnect* oc2;
        if (!oc)
            return;
        if ((oc2 = oc->oc_next)->oc_to == i) {
            o->o_connections = oc2->oc_next;
            freebytes(oc2, 8);
            return;
        }
        while (oc2) {
            if (oc2->oc_to == i) {
                oc->oc_next = oc2->oc_next;
                freebytes(oc2, 8);
                return;
            }
            oc = oc2;
            oc2 = oc2->oc_next;
        }
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a0b0
namespace EA { namespace Audio { namespace Eapd {
int obj_noutlets(t_object* x)
{
    t_outlet* o = x->te_outlet;
    int n = 0;

    for (; o; o = o->o_next)
        n++;
    return n;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a0d0
namespace EA { namespace Audio { namespace Eapd {
int obj_ninlets(t_object* x)
{
    int n = 0;
    t_inlet* i;

    for (i = x->te_inlet; i; i = i->i_next)
        n++;
    if (x->g_pd->c_firstin)
        n++;
    return n;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a100
namespace EA { namespace Audio { namespace Eapd {
void* FUN_00a4a100(t_object* x, t_outlet** out, int which)
{
    t_outlet* o = x->te_outlet;

    while (which) {
        which--;
        if (!o)
            break;
        o = o->o_next;
    }
    *out = o;
    return o ? o->o_connections : 0;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a130
namespace EA { namespace Audio { namespace Eapd {
t_outconnect* FUN_00a4a130(t_outconnect* oc, t_object** sink, t_inlet** inlet, int* inno)
{
    t_inlet* i = oc->oc_to;

    if (i->i_pd != spInletClass && i->i_pd != spOtherinletClass &&
        i->i_pd != spFloatinletClass && i->i_pd != spSymbolinletClass) {
        *inno = 0;
        *inlet = 0;
        *sink = (t_object*)i;
        return oc->oc_next;
    }
    {
        t_object* o = i->i_owner;
        int n = o->g_pd->c_firstin;
        t_inlet* i2;
        for (i2 = o->te_inlet; i2 && i2 != i; i2 = i2->i_next)
            n++;
        *inno = n;
        *sink = o;
        *inlet = i;
    }
    return oc->oc_next;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a1c0
namespace EA { namespace Audio { namespace Eapd {
t_object* pd_checkobject(t_pd* x)
{
    return (*x)->c_isobject ? (t_object*)x : 0;
}
}}}  // namespace EA::Audio::Eapd
