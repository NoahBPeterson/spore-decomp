// Spore 0x00a5a590 slice -- EA::Audio::Eapd "select"/"route"/"pack"/"unpack"/"trigger"
// message objects (a small Pd-style message toolkit).
//
// Reconstructed from the retail disassembly. The object records are allocated by pd_new and
// each class only appends the few fields below, so keep the offsets in sync.

#include <string.h>

typedef unsigned char byte;

namespace EA {
namespace Audio {
namespace Eapd {

// ---------------------------------------------------------------------------
// runtime types
// ---------------------------------------------------------------------------

struct t_symbol {               // 0x08, passed by value in the message API
    const char* name;           // +0x00
    int hash;                   // +0x04
};

struct Atom {                   // 0x0c
    int type;                   // +0x00
    union {
        float f;                // +0x04
        int i;
        t_symbol sym;           // +0x04
    };
};

struct t_class;

// an outlet fans a message out to every destination bound to it
struct Dest {                   // 0x08
    Dest* next;                 // +0x00
    void* outlet;               // +0x04
};

struct Outlet {                 // 0x0c
    char pad[8];
    Dest* dests;                // +0x08
};

// one route/select key (float or symbol) plus the outlet it forwards to
struct RouteElement {           // 0x0c
    union {
        float key;              // +0x00
        t_symbol sym;           // +0x00
    };
    void* outlet;               // +0x08
};

// one unpack/trigger socket: the atom type it accepts plus its outlet
struct OutElem {                // 0x08
    int type;                   // +0x00
    void* outlet;               // +0x04
};

struct RouteObj {               // 0x38
    char pad0[0x28];
    int mode;                   // +0x28  (type of the first argument: 1 = float keys)
    int count;                  // +0x2c
    RouteElement* elems;        // +0x30
    void* outlet;               // +0x34
};

struct PackObj {                // 0x34
    char pad0[0x0c];
    void* outlet;               // +0x0c
    char pad1[0x18];
    int count;                  // +0x28
    Atom* atoms;                // +0x2c
    Atom* atoms2;               // +0x30
};

struct UnpackObj {              // 0x30
    char pad0[0x28];
    int count;                  // +0x28
    OutElem* outs;              // +0x2c
};

struct TriggerObj {             // 0x30
    char pad0[0x28];
    int count;                  // +0x28
    OutElem* outs;              // +0x2c
};

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------

extern t_symbol gListSymbol;        // 0x016758ac
extern t_symbol gBangSymbol;        // 0x016758b4
extern t_symbol gSymbolSymbol;      // 0x01675894
extern t_symbol gEmptySymbol;       // 0x0167589c
extern t_symbol gFloatSymbol;       // 0x016758c4
extern t_symbol gAnythingSymbol;    // 0x016758cc
extern int gOutletCount;            // 0x0167545c

extern t_class* gSelectClass;       // 0x0167565c
extern t_class* gSelect2Class;      // 0x01675660
extern t_class* spRouteClass;       // 0x01675668
extern t_class* gPackClass;         // 0x0167566c
extern t_class* spUnpackClass;      // 0x0167563c
extern t_class* spTriggerClass;     // 0x01675638

// ---------------------------------------------------------------------------
// external runtime helpers
// ---------------------------------------------------------------------------

t_symbol* __cdecl gensym(t_symbol* buf, const char* name);              // 0x00a675f0
t_class* __cdecl class_new(t_symbol name, void* newfn, void* freefn, int size, int flags,
                           int type);                                   // 0x00a48e50
t_class* __cdecl class_new(t_symbol name, void* newfn, void* freefn, int size, int flags,
                           int type, int arg);                          // 0x00a48ea0
byte __cdecl class_addcreator(void* fn, t_symbol name, int type, int arg);  // 0x00a48e00
byte __cdecl class_addbang(t_class* c, void* fn);                       // 0x00a47f10
byte __cdecl class_doaddfloat(t_class* c, void* fn);                    // 0x00a47f30
byte __cdecl class_addsymbol(t_class* c, void* fn);                     // 0x00a47f50
byte __cdecl class_addlist(t_class* c, void* fn);                       // 0x00a47f70
byte __cdecl class_addanything(t_class* c, void* fn);                   // 0x00a47f90
void* __cdecl pd_new(t_class* c);                                       // 0x00a49390
void* __cdecl outlet_new(void* obj, t_symbol s);                        // 0x00a49d30
void* __cdecl floatinlet_new(void* obj, void* dst);                     // 0x00a49a00
void* __cdecl symbolinlet_new(void* obj, void* dst);                    // 0x00a49ab0
void __cdecl outlet_bang(void* outlet);                                 // 0x00a49da0
void __cdecl outlet_symbol(void* outlet, t_symbol s);                   // 0x00a49df0
void __cdecl outlet_list(void* outlet, t_symbol s, int argc, Atom* argv);   // 0x00a49e40
void __cdecl outlet_anything(void* outlet, t_symbol s, int argc, Atom* argv);  // 0x00a49eb0
void __cdecl outlet_float(void* outlet, float f);                       // 0x00a49570
void __cdecl obj_list(void* obj, t_symbol s, int argc, Atom* argv);     // 0x00a49b40
void* __cdecl getbytes(int size, const char* tag);                      // 0x00a49610
void __cdecl freebytes(void* p, int size);                              // 0x00a49650
float __cdecl atom_getfloat(Atom* a);                                   // 0x00a46760
t_symbol* __cdecl atom_getsymbol(t_symbol* buf, Atom* a);               // 0x00a46790
float __cdecl atom_getfloat_at(int i, int argc, Atom* argv);            // 0x00a468f0
t_symbol* __cdecl atom_getsymbol_at(t_symbol* buf, int i, int argc, Atom* argv);  // 0x00a46950

void route_free(RouteObj* obj);     // 0x00a5a960

// handlers owned by neighbouring slices
void sel1_float();                  // 0x00a5a280
void sel1_symbol();                 // 0x00a5a2f0
void sel2_float();                  // 0x00a5a330
void sel2_symbol();                 // 0x00a5a3c0
void* select_new(t_symbol* s, int argc, Atom* argv);                    // 0x00a5a410
void route_anything(RouteObj* obj, t_symbol s, int argc, Atom* argv);   // 0x00a5a690
void* unpack_new(t_symbol* s, int argc, Atom* argv);                    // 0x00a5aeb0

// ---------------------------------------------------------------------------
// select: registered by the dsp setup below, one class per key flavour
// ---------------------------------------------------------------------------

// @ 0x00a5a590
byte select_setup()
{
    t_symbol sym;
    gSelectClass = class_new(*gensym(&sym, "select"), 0, 0, 0x3c, 0, 0);
    byte ok = (byte)((gSelectClass != 0) & 1);
    ok &= class_doaddfloat(gSelectClass, (void*)sel1_float);
    ok &= class_addsymbol(gSelectClass, (void*)sel1_symbol);
    gSelect2Class = class_new(*gensym(&sym, "select"), 0, (void*)route_free, 0x38, 0, 0);
    byte ok2 = (byte)((gSelect2Class != 0) & 1);
    ok &= ok2;
    ok &= class_doaddfloat(gSelect2Class, (void*)sel2_float);
    ok &= class_addsymbol(gSelect2Class, (void*)sel2_symbol);
    ok &= class_addcreator((void*)select_new, *gensym(&sym, "select"), 9, 0);
    ok &= class_addcreator((void*)select_new, *gensym(&sym, "sel"), 9, 0);
    return ok;
}

// ---------------------------------------------------------------------------
// route: match the first element of an incoming list against the keys
// ---------------------------------------------------------------------------

// @ 0x00a5a730
void route_list(RouteObj* obj, t_symbol s, int argc, Atom* argv)
{
    if (obj->mode == 1) {
        if (argc == 0)
            return;
        float key = atom_getfloat(argv);
        RouteElement* e = obj->elems;
        int n = obj->count;
        while (n-- != 0) {
            if (e->key == key) {
                if (argc > 1 && argv[1].type == 2) {
                    outlet_anything(e->outlet, argv[1].sym, argc - 2, argv + 2);
                    return;
                }
                outlet_list(e->outlet, gListSymbol, argc - 1, argv + 1);
                return;
            }
            e++;
        }
    } else if (argc < 2) {
        if (argc == 0) {
            RouteElement* e = obj->elems;
            int n = obj->count;
            while (n-- != 0) {
                if (e->sym.name == gBangSymbol.name) {
                    outlet_bang(e->outlet);
                    return;
                }
                e++;
            }
        } else if (argv->type == 1) {
            RouteElement* e = obj->elems;
            int n = obj->count;
            while (n-- != 0) {
                if (e->sym.name == gFloatSymbol.name) {
                    float f = argv->f;
                    void* out = e->outlet;
                    gOutletCount++;
                    if (gOutletCount < 1000) {
                        for (Dest* d = ((Outlet*)out)->dests; d != 0; d = d->next)
                            outlet_float(d->outlet, f);
                    }
                    gOutletCount--;
                    return;
                }
                e++;
            }
        } else {
            RouteElement* e = obj->elems;
            int n = obj->count;
            while (n-- != 0) {
                if (e->sym.name == gSymbolSymbol.name) {
                    outlet_symbol(e->outlet, argv->sym);
                    return;
                }
                e++;
            }
        }
    } else {
        RouteElement* e = obj->elems;
        int n = obj->count;
        while (n-- != 0) {
            if (e->sym.name == gListSymbol.name) {
                if (argc > 0 && argv->type == 2) {
                    outlet_anything(e->outlet, argv->sym, argc - 1, argv + 1);
                    return;
                }
                outlet_list(e->outlet, gListSymbol, argc, argv);
                return;
            }
            e++;
        }
    }
    outlet_list(obj->outlet, gListSymbol, argc, argv);
}

// @ 0x00a5a960
void route_free(RouteObj* obj)
{
    freebytes(obj->elems, obj->count * sizeof(RouteElement));
}

// @ 0x00a5a980
void* route_new(t_symbol* s, int argc, Atom* argv)
{
    RouteObj* obj = (RouteObj*)pd_new(spRouteClass);
    if (obj == 0)
        return 0;
    Atom def[1];
    if (argc == 0) {
        argc = 1;
        argv = def;
        def[0].type = 1;
        def[0].f = 0.0f;
    }
    obj->mode = argv->type;
    obj->count = argc;
    obj->elems = (RouteElement*)getbytes(argc * sizeof(RouteElement), "EAPd/t_routeelement");
    for (int i = 0; i < argc; i++) {
        RouteElement* e = &obj->elems[i];
        e->outlet = outlet_new(obj, gListSymbol);
        if (obj->mode == 1) {
            e->key = atom_getfloat_at(i, argc, argv);
        } else {
            t_symbol tmp;
            e->sym = *atom_getsymbol_at(&tmp, i, argc, argv);
        }
    }
    obj->outlet = outlet_new(obj, gListSymbol);
    return obj;
}

// @ 0x00a5aa70
byte route_setup()
{
    t_symbol sym;
    spRouteClass = class_new(*gensym(&sym, "route"), (void*)route_new, (void*)route_free, 0x38, 0,
                             9, 0);
    byte ok = (byte)((spRouteClass != 0) & 1);
    ok &= class_addlist(spRouteClass, (void*)route_list);
    ok &= class_addanything(spRouteClass, (void*)route_anything);
    return ok;
}

// ---------------------------------------------------------------------------
// pack: gather the inlets back into one list
// ---------------------------------------------------------------------------

// @ 0x00a5aae0
void* pack_new(t_symbol* s, int argc, Atom* argv)
{
    PackObj* obj = (PackObj*)pd_new(gPackClass);
    if (obj == 0)
        return 0;
    Atom def[2];
    if (argc == 0) {
        argc = 2;
        argv = def;
        def[0].type = 1;
        def[0].f = 0.0f;
        def[1].type = 1;
        def[1].f = 0.0f;
    }
    obj->count = argc;
    obj->atoms = (Atom*)getbytes(argc * sizeof(Atom), "EAPd/t_pack_atoms");
    obj->atoms2 = (Atom*)getbytes(argc * sizeof(Atom), "EAPd/t_pack_atoms");
    Atom* a = obj->atoms;
    for (int i = 0; i < argc; i++) {
        if (argv[i].type == 1) {
            a[i] = argv[i];
            if (i != 0)
                floatinlet_new(obj, &a[i].f);
        } else if (argv[i].type == 2) {
            if (argv[i].sym.name[0] == 's' || argv[i].sym.name[0] == 'S') {
                a[i].type = 2;
                a[i].sym = gSymbolSymbol;
                if (i != 0)
                    symbolinlet_new(obj, &a[i].sym);
            } else {
                a[i].type = 1;
                a[i].f = 0.0f;
                if (i != 0)
                    floatinlet_new(obj, &a[i].f);
            }
        }
    }
    obj->outlet = outlet_new(obj, gListSymbol);
    return obj;
}

// @ 0x00a5ac40
void pack_bang(PackObj* obj)
{
    int alloc = 0;
    Atom* list = obj->atoms2;
    int size = obj->count * sizeof(Atom);
    if (list == 0) {
        list = (Atom*)getbytes(size, "EAPd/t_pack_atoms");
        alloc = 1;
    } else {
        obj->atoms2 = 0;
    }
    memcpy(list, obj->atoms, size);
    outlet_list(obj->outlet, gListSymbol, obj->count, list);
    if (alloc)
        freebytes(list, size);
    else
        obj->atoms2 = list;
}

// @ 0x00a5acc0
void pack_float(PackObj* obj, float f)
{
    Atom* a = obj->atoms;
    if (a->type == 1) {
        a->f = f;
        pack_bang(obj);
    }
}

// @ 0x00a5ace0
void pack_symbol(PackObj* obj, t_symbol s)
{
    Atom* a = obj->atoms;
    if (a->type == 2) {
        a->sym = s;
        pack_bang(obj);
    }
}

// @ 0x00a5ad10
void pack_list(PackObj* obj, t_symbol s, int argc, Atom* argv)
{
    obj_list(obj, s, argc, argv);
}

// @ 0x00a5ad40
void pack_anything(PackObj* obj, t_symbol s, int argc, Atom* argv)
{
    int size = (argc * 3 + 3) * 4;
    Atom* list = (Atom*)getbytes(size, "EAPd/t_pack_atoms");
    for (int i = 0; i < argc; i++)
        list[i + 1] = argv[i];
    list[0].type = 2;
    list[0].sym = s;
    obj_list(obj, gListSymbol, argc + 1, list);
    freebytes(list, size);
}

// @ 0x00a5add0
void pack_free(PackObj* obj)
{
    freebytes(obj->atoms, obj->count * sizeof(Atom));
    freebytes(obj->atoms2, obj->count * sizeof(Atom));
}

// @ 0x00a5ae10
byte pack_setup()
{
    t_symbol sym;
    gPackClass = class_new(*gensym(&sym, "pack"), (void*)pack_new, (void*)pack_free, 0x34, 0, 9,
                           0);
    byte ok = (byte)((gPackClass != 0) & 1);
    ok &= class_addbang(gPackClass, (void*)pack_bang);
    ok &= class_doaddfloat(gPackClass, (void*)pack_float);
    ok &= class_addsymbol(gPackClass, (void*)pack_symbol);
    ok &= class_addlist(gPackClass, (void*)pack_list);
    ok &= class_addanything(gPackClass, (void*)pack_anything);
    return ok;
}

// ---------------------------------------------------------------------------
// unpack: fan a list out over typed outlets
// ---------------------------------------------------------------------------

// @ 0x00a5afa0
void unpack_list(UnpackObj* obj, t_symbol s, int argc, Atom* argv)
{
    if (argc > obj->count)
        argc = obj->count;
    OutElem* e = &obj->outs[argc - 1];
    int n = argc;
    Atom* a = &argv[argc - 1];
    while (n != 0) {
        n--;
        if (e->type == a->type) {
            if (e->type == 1) {
                float f = a->f;
                void* out = e->outlet;
                gOutletCount++;
                if (gOutletCount < 1000) {
                    for (Dest* d = ((Outlet*)out)->dests; d != 0; d = d->next)
                        outlet_float(d->outlet, f);
                }
                gOutletCount--;
            } else if (e->type == 2) {
                outlet_symbol(e->outlet, a->sym);
            }
        }
        e--;
        a--;
    }
}

// @ 0x00a5b070
void unpack_anything(UnpackObj* obj, t_symbol s, int argc, Atom* argv)
{
    int size = (argc * 3 + 3) * 4;
    Atom* list = (Atom*)getbytes(size, "EAPd/t_unpack_atoms");
    for (int i = 0; i < argc; i++)
        list[i + 1] = argv[i];
    list[0].type = 2;
    list[0].sym = s;
    unpack_list(obj, gListSymbol, argc + 1, list);
    freebytes(list, size);
}

// @ 0x00a5b100
void unpack_free(UnpackObj* obj)
{
    freebytes(obj->outs, obj->count * sizeof(OutElem));
}

// @ 0x00a5b120
byte unpack_setup()
{
    t_symbol sym;
    spUnpackClass = class_new(*gensym(&sym, "unpack"), (void*)unpack_new, (void*)unpack_free,
                              0x30, 0, 9, 0);
    byte ok = (byte)((spUnpackClass != 0) & 1);
    ok &= class_addlist(spUnpackClass, (void*)unpack_list);
    ok &= class_addanything(spUnpackClass, (void*)unpack_anything);
    return ok;
}

// ---------------------------------------------------------------------------
// trigger: send everything to every socket, rightmost first
// ---------------------------------------------------------------------------

// @ 0x00a5b190
void* trigger_new(t_symbol* s, int argc, Atom* argv)
{
    TriggerObj* obj = (TriggerObj*)pd_new(spTriggerClass);
    if (obj == 0)
        return 0;
    Atom def[2];
    if (argc == 0) {
        argc = 2;
        argv = def;
        def[0].type = 2;
        def[0].sym = gBangSymbol;
        def[1] = def[0];
    }
    obj->count = argc;
    obj->outs = (OutElem*)getbytes(argc * sizeof(OutElem), "EAPd/t_triggerout");
    for (int i = 0; i < argc; i++) {
        char c = argv[i].type == 2 ? argv[i].sym.name[0] : (argv[i].type == 1 ? 'f' : 0);
        int type;
        t_symbol sym;
        switch (c) {
        case 'a':
        case 'A':
            type = 4;
            sym = gAnythingSymbol;
            break;
        case 'b':
        case 'B':
            type = 0;
            sym = gBangSymbol;
            break;
        case 'f':
        case 'F':
            type = 1;
            sym = gFloatSymbol;
            break;
        case 'l':
        case 'L':
            type = 3;
            sym = gListSymbol;
            break;
        case 's':
        case 'S':
            type = 2;
            sym = gSymbolSymbol;
            break;
        default:
            type = 1;
            sym = gFloatSymbol;
            break;
        }
        obj->outs[i].type = type;
        obj->outs[i].outlet = outlet_new(obj, sym);
    }
    return obj;
}

// @ 0x00a5b330
void trigger_list(TriggerObj* obj, t_symbol s, int argc, Atom* argv)
{
    int n = obj->count;
    OutElem* e = &obj->outs[n - 1];
    while (n != 0) {
        n--;
        if (e->type == 1) {
            float f = argc != 0 ? atom_getfloat(argv) : 0.0f;
            void* out = e->outlet;
            gOutletCount++;
            if (gOutletCount < 1000) {
                for (Dest* d = ((Outlet*)out)->dests; d != 0; d = d->next)
                    outlet_float(d->outlet, f);
            }
            gOutletCount--;
        } else if (e->type == 0) {
            outlet_bang(e->outlet);
        } else if (e->type == 2) {
            if (argc == 0) {
                outlet_symbol(e->outlet, gEmptySymbol);
            } else {
                t_symbol tmp;
                outlet_symbol(e->outlet, *atom_getsymbol(&tmp, argv));
            }
        } else {
            outlet_list(e->outlet, gListSymbol, argc, argv);
        }
        e--;
    }
}

// @ 0x00a5b450
void trigger_anything(TriggerObj* obj, t_symbol s, int argc, Atom* argv)
{
    int n = obj->count;
    OutElem* e = &obj->outs[n - 1];
    while (n != 0) {
        n--;
        if (e->type == 0)
            outlet_bang(e->outlet);
        else if (e->type == 4)
            outlet_anything(e->outlet, s, argc, argv);
        e--;
    }
}

// @ 0x00a5b4b0
void trigger_bang(TriggerObj* obj)
{
    trigger_list(obj, gListSymbol, 0, 0);
}

// @ 0x00a5b4d0
void trigger_float(TriggerObj* obj, float f)
{
    Atom a;
    a.type = 1;
    a.f = f;
    trigger_list(obj, gListSymbol, 1, &a);
}

} // namespace Eapd
} // namespace Audio
} // namespace EA
