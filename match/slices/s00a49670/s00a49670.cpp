// Slice s00a49670: EA::Audio::Eapd (EA's embedded Pure Data) - g_canvas.c object glue:
// resizebytes, inlet/outlet creation + methods, obj_connect/obj_disconnect, obj_init,
// glist_doupdatewindowlist / canvas_updatewindowlist and the canvas environment accessors.
// (0xa49670-0xa4a4f1)
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <stdio.h>
#include <string.h>

namespace EA { namespace Audio { namespace Eapd {

struct t_class;
struct t_object;
struct t_inlet;
struct t_outlet;
struct t_outconnect;
struct t_glist;
typedef t_class* t_pd;

// t_symbol is passed by value (hash, name); symbols compare by their first word only.
struct t_symbol {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};
inline bool operator==(const t_symbol& a, const t_symbol& b) { return a.mHash == b.mHash; }

struct t_atom {           // 12 bytes
    int a_type;
    union {
        float    w_float;
        t_symbol w_symbol;
    } a_w;
};

struct t_methodentry {
    t_symbol me_name;     // +0
    void*    me_fun;      // +8
    int      me_arg[6];   // +0xc
};

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

struct t_gobj {
    t_class* g_pd;        // +0x00
    t_gobj*  g_next;      // +0x04
};

struct t_object : t_gobj {
    void*     te_binbuf;  // +0x08
    t_outlet* te_outlet;  // +0x0c
    t_inlet*  te_inlet;   // +0x10
};

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

struct t_outconnect {         // 8
    t_outconnect* oc_next;    // +0
    t_inlet*      oc_to;      // +4
};

struct t_outlet {             // 0x1c
    t_object*     o_owner;        // +0x00
    t_outlet*     o_next;         // +0x04
    t_outconnect* o_connections;  // +0x08
    t_symbol      o_symfrom;      // +0x0c
    t_symbol      o_symto;        // +0x14
};

struct t_canvasenv {
    char pad00[0x10];
    void* ce_dollarzero;   // +0x10
};

struct t_glist {
    t_object  gl_obj;         // +0x00
    char      pad14[0x14];    // +0x14
    t_gobj*   gl_list;        // +0x28
    t_glist*  gl_owner;       // +0x2c
    char      pad30[0x38];    // +0x30
    const char* gl_name;      // +0x68
    void*     gl_x6c;         // +0x6c
    t_glist*  gl_nextwin;     // +0x70
    t_canvasenv* gl_env;      // +0x74
    unsigned  gl_havewindow : 1;   // +0x78
    void*     gl_instance;    // +0x7c
};

// EAPd allocator: vtable +4 = Alloc(size, tag) (thiscall, ret 8), +0xc = Free(ptr).
struct EapdAllocator {
    virtual void  Slot0();
    virtual void* Alloc(unsigned size, unsigned tag);
    virtual void  Slot2();
    virtual void  Free(void* p);
};

// ------------------------------------------------------------------ globals
extern t_class* spOtherinletClass;     // 0x1675448 (4th inlet class)
extern t_class* spInletClass;          // 0x1675450
extern t_class* spSymbolinletClass;    // 0x1675454
extern t_class* spFloatinletClass;     // 0x1675458
extern int gObjCount;                  // 0x167544c
extern int gOutletCount;               // 0x167545c
extern t_glist* gpCanvasList;          // 0x1675464
extern t_symbol gSymNewFile;           // 0x1675474
extern t_symbol gSymNewFile2;          // 0x167547c
extern t_symbol gSymbolSymbol;         // 0x1675894
extern t_symbol gEmptySymbol;          // 0x167589c
extern t_symbol gListSymbol;           // 0x16758ac
extern t_symbol gBangSymbol;           // 0x16758b4
extern t_symbol gHashXSymbol;          // 0x16758bc
extern t_symbol gFloatSymbol;          // 0x16758c4
extern t_class* gpCanvasClass;         // 0x1675490

// ------------------------------------------------------------------ callees
void* getbytes(int n, const char* tag);                          // 0xa49610
void  freebytes(void* p, int n);                                 // 0xa49650
void* pd_new(t_class* c);                                        // 0xa49390
void  pd_bang(void* x);                                          // 0xa49560
void  outlet_float(void* x, float f);                            // 0xa49570
void  pd_symbol(void* x, t_symbol s);                            // 0xa49590
void  pd_list(void* x, t_symbol s, int argc, t_atom* argv);      // 0xa495b0
void  pd_typedmess(void* x, t_symbol s, int argc, t_atom* argv); // 0xa48100
void  pd_vmess(void* x, t_symbol s, const char* fmt, ...);       // 0xa487f0
EapdAllocator* System_GetAllocator();                            // 0xa67cb0
t_symbol* gensym(t_symbol* out, const char* s);                  // 0xa675f0
t_class* class_new(t_symbol name, void* newmethod, void* freemethod, int size, int flags, int a1);  // 0xa48e50
bool class_addbang(t_class* c, void* fn);                        // 0xa47f10
bool class_doaddfloat(t_class* c, void* fn);                     // 0xa47f30
bool class_addsymbol(t_class* c, void* fn);                      // 0xa47f50
bool class_addlist(t_class* c, void* fn);                        // 0xa47f70
bool class_addanything(t_class* c, void* fn);                    // 0xa47f90
t_pd* pd_findbyclass(t_symbol s, t_class* c);                    // 0xa671f0
void  sys_gui(const char* cmd);                                  // 0xc2e4e0

// ------------------------------------------------------------------ helpers
static void inlet_bang(t_inlet* x);
static void inlet_float(t_inlet* x, float f);
static void inlet_symbol(t_inlet* x, t_symbol s);
static void inlet_list(t_inlet* x, t_symbol s, int argc, t_atom* argv);
static void inlet_anything(t_inlet* x, t_symbol s, int argc, t_atom* argv);
static void floatinlet_float(t_inlet* x, float f);
static void symbolinlet_symbol(t_inlet* x, t_symbol s);

// @ 0x00a49670  EA::Audio::Eapd::resizebytes
void* resizebytes(void* ptr, uint32_t oldsize, uint32_t newsize, uint32_t tag)
{
    void* newp;

    if (newsize < 1)
        newsize = 1;
    if (oldsize < 1)
        oldsize = 1;
    if (newsize == oldsize)
        return ptr;
    uint32_t n = newsize;
    if (n < 1)
        n = 1;
    EapdAllocator* a = System_GetAllocator();
    newp = a->Alloc(n, tag);
    if (!newp)
        return 0;
    memset(newp, 0, n);
    if (!newp)
        return 0;
    if (newsize > oldsize) {
        memcpy(newp, ptr, oldsize);
        memset((char*)newp + oldsize, 0, newsize - oldsize);
    } else {
        memcpy(newp, ptr, newsize);
    }
    System_GetAllocator()->Free(ptr);
    return newp;
}

// @ 0x00a49720
void FUN_00a49720(t_inlet* x, t_symbol s)
{
    if (x) {
        x->i_symempty.mHash = s.mHash;
        x->i_symempty.mpName = s.mpName;
    }
}

// @ 0x00a49740  EA::Audio::Eapd::inlet_new
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

// @ 0x00a497d0  inlet bang method
void inlet_bang(t_inlet* x)
{
    if (x->i_symfrom == gBangSymbol)
        pd_vmess(x->i_dest, x->u.i_symto, "");
    else if (x->i_symfrom == gEmptySymbol)
        pd_bang(x->i_dest);
}

// @ 0x00a49810  inlet float method
void inlet_float(t_inlet* x, float f)
{
    if (x->i_symfrom == gFloatSymbol)
        pd_vmess(x->i_dest, x->u.i_symto, "f", (double)f);
    else if (x->i_symfrom == gEmptySymbol)
        outlet_float(x->i_dest, f);
}

// (0xa49860) inlet symbol method - registered by obj_init, not a function start in the image.
void inlet_symbol(t_inlet* x, t_symbol s)
{
    if (x->i_symfrom == gSymbolSymbol)
        pd_vmess(x->i_dest, x->u.i_symto, "s", s);
    else if (x->i_symfrom == gEmptySymbol)
        pd_symbol(x->i_dest, s);
}

// @ 0x00a498c0  EA::Audio::Eapd::inlet_list
void inlet_list(t_inlet* x, t_symbol s, int argc, t_atom* argv)
{
    t_symbol from = x->i_symfrom;

    if (from == gListSymbol || from == gFloatSymbol || from == gSymbolSymbol)
        pd_typedmess(x->i_dest, x->u.i_symto, argc, argv);
    else if (from == gEmptySymbol)
        pd_list(x->i_dest, s, argc, argv);
}

// @ 0x00a49930  EA::Audio::Eapd::inlet_anything
void inlet_anything(t_inlet* x, t_symbol s, int argc, t_atom* argv)
{
    if (x->i_symfrom == s)
        pd_typedmess(x->i_dest, x->u.i_symto, argc, argv);
    else if (x->i_symfrom == gEmptySymbol)
        pd_typedmess(x->i_dest, s, argc, argv);
}

// @ 0x00a49990  EA::Audio::Eapd::inlet_free
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

// @ 0x00a499e0  float inlet method
void floatinlet_float(t_inlet* x, float f)
{
    *(float*)x->u.i_destp = f;
}

// @ 0x00a49a00  EA::Audio::Eapd::floatinlet_new
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

// @ 0x00a49a90  symbol inlet method
void symbolinlet_symbol(t_inlet* x, t_symbol s)
{
    t_symbol* p = (t_symbol*)x->u.i_destp;
    *p = s;
}

// @ 0x00a49ab0  EA::Audio::Eapd::symbolinlet_new
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

// @ 0x00a49b40  EA::Audio::Eapd::obj_list
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

// @ 0x00a49be0  EA::Audio::Eapd::obj_init
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

// @ 0x00a49d00
void FUN_00a49d00()
{
    gObjCount++;
}

// @ 0x00a49d10
void FUN_00a49d10(t_outlet* x, t_symbol s)
{
    if (x) {
        x->o_symto.mHash = s.mHash;
        x->o_symto.mpName = s.mpName;
    }
}

// @ 0x00a49d30  EA::Audio::Eapd::outlet_new
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

// @ 0x00a49da0  EA::Audio::Eapd::outlet_bang
void outlet_bang(t_outlet* x)
{
    if (++gOutletCount < 1000) {
        t_outconnect* oc;
        for (oc = x->o_connections; oc; oc = oc->oc_next)
            pd_bang(oc->oc_to);
    }
    gOutletCount--;
}

// @ 0x00a49df0  EA::Audio::Eapd::outlet_symbol
void outlet_symbol(t_outlet* x, t_symbol s)
{
    if (++gOutletCount < 1000) {
        t_outconnect* oc;
        for (oc = x->o_connections; oc; oc = oc->oc_next)
            pd_symbol(oc->oc_to, s);
    }
    gOutletCount--;
}

// @ 0x00a49e40  EA::Audio::Eapd::outlet_list
void outlet_list(t_outlet* x, t_symbol s, int argc, t_atom* argv)
{
    if (++gOutletCount < 1000) {
        t_outconnect* oc;
        for (oc = x->o_connections; oc; oc = oc->oc_next)
            pd_list(oc->oc_to, s, argc, argv);
    }
    gOutletCount--;
}

// @ 0x00a49eb0  EA::Audio::Eapd::outlet_anything
void outlet_anything(t_outlet* x, t_symbol s, int argc, t_atom* argv)
{
    if (++gOutletCount < 1000) {
        t_outconnect* oc;
        for (oc = x->o_connections; oc; oc = oc->oc_next)
            pd_typedmess(oc->oc_to, s, argc, argv);
    }
    gOutletCount--;
}

// @ 0x00a49f20  EA::Audio::Eapd::outlet_free
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

// @ 0x00a49f70  EA::Audio::Eapd::obj_connect
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

// @ 0x00a4a010  EA::Audio::Eapd::obj_disconnect
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

// @ 0x00a4a0b0  EA::Audio::Eapd::obj_noutlets
int obj_noutlets(t_object* x)
{
    int n = 0;
    t_outlet* o;

    for (o = x->te_outlet; o; o = o->o_next)
        n++;
    return n;
}

// @ 0x00a4a0d0  EA::Audio::Eapd::obj_ninlets
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

// @ 0x00a4a100
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

// @ 0x00a4a130
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

// @ 0x00a4a1c0  EA::Audio::Eapd::pd_checkobject
t_object* pd_checkobject(t_pd* x)
{
    return (*x)->c_isobject ? (t_object*)x : 0;
}

// @ 0x00a4a1e0  move an inlet to the front of the owner's inlet list
void FUN_00a4a1e0(t_object* x, t_inlet* i)
{
    t_inlet* i2 = x->te_inlet;

    if (i2 == i || !i2)
        return;
    while (i2->i_next != i) {
        i2 = i2->i_next;
        if (!i2)
            return;
    }
    i2->i_next = i->i_next;
    i->i_next = x->te_inlet;
    x->te_inlet = i;
}

// @ 0x00a4a220  move an outlet to the front of the owner's outlet list
void FUN_00a4a220(t_object* x, t_outlet* o)
{
    t_outlet* o2 = x->te_outlet;

    if (o2 == o || !o2)
        return;
    while (o2->o_next != o) {
        o2 = o2->o_next;
        if (!o2)
            return;
    }
    o2->o_next = o->o_next;
    o->o_next = x->te_outlet;
    x->te_outlet = o;
}

// @ 0x00a4a260  EA::Audio::Eapd::glist_doupdatewindowlist
void glist_doupdatewindowlist(t_glist* x, char* buf)
{
    char local[1024];

    if (x->gl_havewindow) {
        if (strlen(buf) + strlen(x->gl_name) + 100 <= 1024) {
            sprintf(local, "{%s .x%lx} ", x->gl_name, x);
            strcat(buf, local);
        }
    }
    {
        t_gobj* g;
        for (g = x->gl_list; g; g = g->g_next) {
            if (g->g_pd == gpCanvasClass)
                glist_doupdatewindowlist((t_glist*)g, buf);
        }
    }
}

// @ 0x00a4a320  EA::Audio::Eapd::canvas_updatewindowlist
void canvas_updatewindowlist()
{
    char buf[1024];
    t_glist* g;

    memcpy(buf, "pdtk_updatewindowlist {", 24);
    for (g = gpCanvasList; g; g = g->gl_nextwin) {
        if (g)
            glist_doupdatewindowlist(g, buf);
    }
    strcat(buf, "}\n");
    sys_gui(buf);
}

// @ 0x00a4a3c0  remove a window from gpCanvasList
void __fastcall FUN_00a4a3c0(int unused, t_glist* x)
{
    t_glist* g;
    t_glist* p;

    if (x == gpCanvasList) {
        gpCanvasList = x->gl_nextwin;
        return;
    }
    p = gpCanvasList;
    g = p->gl_nextwin;
    while (g != x) {
        p = g;
        g = g->gl_nextwin;
    }
    p->gl_nextwin = x->gl_nextwin;
}

// @ 0x00a4a3f0
void FUN_00a4a3f0(t_symbol s)
{
    gSymNewFile2 = s;
}

// @ 0x00a4a410
void FUN_00a4a410(t_symbol s)
{
    gSymNewFile = s;
}

// @ 0x00a4a430  EA::Audio::Eapd::canvas_getcurrent
t_glist* canvas_getcurrent()
{
    return (t_glist*)pd_findbyclass(gHashXSymbol, gpCanvasClass);
}

// @ 0x00a4a450  EA::Audio::Eapd::canvas_getcurrentinstance
void* canvas_getcurrentinstance()
{
    t_glist* x = (t_glist*)pd_findbyclass(gHashXSymbol, gpCanvasClass);
    return x->gl_instance;
}

// @ 0x00a4a490  EA::Audio::Eapd::canvas_getenv
t_canvasenv* canvas_getenv(t_glist* x)
{
    while (!x->gl_env)
        x = x->gl_owner;
    return x->gl_env;
}

// @ 0x00a4a4b0  EA::Audio::Eapd::canvas_getdollarzero
void* canvas_getdollarzero()
{
    t_glist* x = (t_glist*)pd_findbyclass(gHashXSymbol, gpCanvasClass);
    t_canvasenv* env;

    if (x == 0) {
        env = 0;
    } else {
        while (!x->gl_env)
            x = x->gl_owner;
        env = x->gl_env;
    }
    if (env == 0) {
        return 0;
    }
    return env->ce_dollarzero;
}

}}}
