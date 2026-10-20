// Slice s00a5c460 -- EAPd audio control externals: the value/change holders and the
// list append / prepend / split / trim / message classes.  These are classic Pd-style
// class-setup entry points (class_new + class_add* callbacks), so the code is plain
// cdecl with the EAPd t_symbol passed by value (two dwords).

#include <malloc.h>

typedef unsigned char byte;

extern int gOutletCount;                                              // 0x0167545c

namespace EA { namespace Audio { namespace Eapd {

// ---------------------------------------------------------------- basic types
struct t_symbol {
    int a;                              // 0x00
    int b;                              // 0x04
};

struct t_atom {                         // 12 bytes
    int a_type;                         // 0x00
    t_symbol s;                         // 0x04
};

struct t_class;

struct t_outlet {                       // element of an outlet list
    t_outlet* next;                     // 0x00
    void* target;                       // 0x04
};

struct t_outletlist {
    int pad0;                           // 0x00
    int pad1;                           // 0x04
    t_outlet* first;                    // 0x08
};

// ---------------------------------------------------------------- object types
struct t_change {
    int pad00;                          // 0x00
    int pad04;                          // 0x04
    int pad08;                          // 0x08
    t_outletlist* outlets;              // 0x0c
    int pad10[6];                       // 0x10
    float value;                        // 0x28
};

struct t_vcommon {
    int pad0;                           // 0x00
    int refs;                           // 0x04
    float value;                        // 0x08
};

struct t_value {
    int pad00;                          // 0x00
    int pad04;                          // 0x04
    int pad08;                          // 0x08
    t_outletlist* outlets;              // 0x0c
    int pad10[6];                       // 0x10
    t_symbol key;                       // 0x28
    float* value;                       // 0x30
};

// t_alist is the small "class + array" block embedded at object+0x28; the setup helpers
// (alist_list / alist_anything) are handed a pointer to it, not to the surrounding object.
struct t_alist {
    t_class* cls;                       // 0x00
    int count;                          // 0x04
    t_atom* atoms;                      // 0x08
};

struct t_alist_obj {
    int pad00[3];                       // 0x00
    void* outlet;                       // 0x0c
    int pad10[6];                       // 0x10
    t_alist a;                          // 0x28
};

struct t_list_split {
    int pad00;                          // 0x00
    int pad04;                          // 0x04
    int pad08;                          // 0x08
    void* outlet;                       // 0x0c
    int pad10[6];                       // 0x10
    float split;                        // 0x28
    void* outlet1;                      // 0x2c
    void* outlet2;                      // 0x30
    void* outlet3;                      // 0x34
};

struct t_list_trim {
    int pad00;                          // 0x00
    int pad04;                          // 0x04
    int pad08;                          // 0x08
    void* outlet;                       // 0x0c
};

struct t_list_message {
    int pad00;                          // 0x00
    int pad04;                          // 0x04
    int pad08;                          // 0x08
    void* outlet;                       // 0x0c
    int pad10[6];                       // 0x10
    t_symbol sel;                       // 0x28
};

// ---------------------------------------------------------------- externals
t_symbol* gensym(t_symbol* out, const char* name);                    // 0x00a675f0
t_class* class_new(t_symbol name, void* newfn, void* freefn, int size,
                   int flags, int nargs, int arg);                     // 0x00a48ea0
t_class* class_new(t_symbol name, void* newfn, void* freefn, int size,
                   int flags, int nargs);                              // 0x00a48e50
byte class_addbang(t_class* cls, void* fn);                            // 0x00a47f10
byte class_doaddfloat(t_class* cls, void* fn);                         // 0x00a47f30
byte class_addlist(t_class* cls, void* fn);                            // 0x00a47f70
byte class_addanything(t_class* cls, void* fn);                        // 0x00a47f90
byte class_addmethod(t_class* cls, void* fn, t_symbol sel, int nargs, int arg); // 0x00a48a80
byte class_addcreator(void* fn, t_symbol sel, int nargs, int arg);     // 0x00a48e00
void class_sethelpsymbol(t_class* cls, t_symbol name);                 // 0x00a47fc0
void* pd_new(t_class* cls);                                           // 0x00a49390
void pd_free(void* obj);                                              // 0x00a493d0
void* pd_findbyclass(int a, int b, t_class* cls);                      // 0x00a671f0
bool pd_bind(void* obj, t_symbol key);                                // 0x00a67620
void* outlet_new(void* obj, t_symbol sel);                            // 0x00a49d30
void outlet_float(void* target, float v);                             // 0x00a49570
void outlet_list(void* outlet, t_symbol sel, int argc, t_atom* argv); // 0x00a49e40
void outlet_anything(void* outlet, t_symbol sel, int argc, t_atom* argv); // 0x00a49eb0
void* inlet_new(void* obj, void* target, t_symbol a, t_symbol b);      // 0x00a49740
void* floatinlet_new(void* obj, float* p);                            // 0x00a49a00
void* symbolinlet_new(void* obj, t_symbol* p);                        // 0x00a49ab0
void* getbytes(int size, const char* name);                           // 0x00a49610
void freebytes(void* p, int size);                                    // 0x00a49650
void sys_vgui(void* a, int b, int c);                                 // 0x00a671b0

// handlers that live outside this slice
void list_prepend_free(t_alist_obj* self);                                // 0x00a5cf20
void change_new();                                                    // 0x00a5c3c0
void change_bang();                                                   // 0x00a5c400
void list_trim_list();                                                // 0x00a5d230
void vinlet_anything();                                               // 0x00a614e0
byte pdint_setup();                                                   // 0x00a59a10
byte pdfloat_setup();                                                 // 0x00a59bb0
byte pdsymbol_setup();                                                // 0x00a59cf0
byte bang_setup();                                                    // 0x00a59dc0
byte send_setup();                                                    // 0x00a59f30
byte forward_setup();                                                 // 0x00a5a0a0
byte receive_setup();                                                 // 0x00a5a1b0
byte select_setup();                                                  // 0x00a5a590
byte route_setup();                                                   // 0x00a5aa70
byte pack_setup();                                                    // 0x00a5ae10
byte unpack_setup();                                                  // 0x00a5b120
byte trigger_setup();                                                 // 0x00a5b550
byte spigot_setup();                                                  // 0x00a5b7b0
byte gate_setup();                                                    // 0x00a5baa0
byte switch_setup();                                                  // 0x00a5bcf0
byte moses_setup();                                                   // 0x00a5be50
byte until_setup();                                                   // 0x00a5bfb0
byte makefilename_setup();                                            // 0x00a5c150
byte swap_setup();                                                    // 0x00a5c320

extern t_class* spChangeClass;                                        // 0x01675650
extern t_class* spValueClass;                                         // 0x01675634
extern t_class* spVcommonClass;                                       // 0x01675680
extern t_class* list_append_class;                                    // 0x01675684
extern t_class* list_split_class;                                     // 0x01675688
extern t_class* list_trim_class;                                      // 0x0167568c
extern t_class* spAlistClass;                                         // 0x01675690
extern t_class* list_prepend_class;                                   // 0x01675694
extern t_class* spListMessageClass;                                   // 0x01675698
extern t_symbol gEmptySymbol;                                         // 0x0167589c
extern t_symbol gListSymbol;                                          // 0x016758ac
extern t_symbol gFloatSymbol;                                         // 0x016758c4
extern t_symbol gAnythingSymbol;                                      // 0x016758cc


// ---------------------------------------------------------------- change
// 0x00a5c460 -- float handler: store the new value and forward it to every outlet.
// @ 0x00a5c460
void change_float(t_change* self, float v)
{
    if (v != self->value) {
        self->value = v;
        t_outletlist* list = self->outlets;
        gOutletCount++;
        if (gOutletCount < 1000) {
            for (t_outlet* o = list->first; o != 0; o = o->next)
                outlet_float(o->target, v);
        }
        gOutletCount--;
    }
}

// @ 0x00a5c4c0
void change_set(t_change* self, float v)
{
    self->value = v;
}

// @ 0x00a5c4d0
byte change_setup()
{
    t_symbol tmp;
    t_symbol* s = gensym(&tmp, "change");
    spChangeClass = class_new(*s, (void*)change_new, 0, 0x2c, 0, 5, 0);
    byte ok = (spChangeClass != 0) & 1;
    ok = ok & class_addbang(spChangeClass, (void*)change_bang);
    ok = ok & class_doaddfloat(spChangeClass, (void*)change_float);
    s = gensym(&tmp, "set");
    ok = ok & class_addmethod(spChangeClass, (void*)change_set, *s, 5, 0);
    return ok;
}

// ---------------------------------------------------------------- value
// @ 0x00a5c570
float* value_get(t_symbol key)
{
    t_vcommon* p = (t_vcommon*)pd_findbyclass(key.a, key.b, spVcommonClass);
    if (p == 0) {
        p = (t_vcommon*)pd_new(spVcommonClass);
        p->value = 0.0f;
        p->refs = 0;
        pd_bind(p, key);
    }
    p->refs++;
    return &p->value;
}

// @ 0x00a5c5d0
t_value* value_new(t_symbol key)
{
    t_value* v = (t_value*)pd_new(spValueClass);
    if (v != 0) {
        v->key = key;
        v->value = value_get(key);
        outlet_new(v, gFloatSymbol);
    }
    return v;
}

// @ 0x00a5c620
void value_bang(t_value* self)
{
    float v = *self->value;
    t_outletlist* list = self->outlets;
    gOutletCount++;
    if (gOutletCount < 1000) {
        for (t_outlet* o = list->first; o != 0; o = o->next)
            outlet_float(o->target, v);
    }
    gOutletCount--;
}

// @ 0x00a5c680
void value_float(t_value* self, float v)
{
    *self->value = v;
}

// @ 0x00a5c6a0
void value_free(t_value* self)
{
    int a = self->key.a;
    int b = self->key.b;
    t_vcommon* p = (t_vcommon*)pd_findbyclass(a, b, spVcommonClass);
    if (p != 0) {
        if (--p->refs == 0) {
            sys_vgui(p, a, b);
            pd_free(p);
        }
    }
}

// @ 0x00a5c6f0
byte value_setup()
{
    t_symbol tmp;
    t_symbol* s = gensym(&tmp, "value");
    spValueClass = class_new(*s, (void*)value_new, (void*)value_free, 0x34, 0, 6, 0);
    byte ok = (spValueClass != 0) & 1;
    s = gensym(&tmp, "float");
    ok = ok & class_addcreator((void*)value_new, *s, 6, 0);
    ok = ok & class_addbang(spValueClass, (void*)value_bang);
    ok = ok & class_doaddfloat(spValueClass, (void*)value_float);
    s = gensym(&tmp, "value");
    spVcommonClass = class_new(*s, 0, 0, 0xc, 1, 0);
    ok = ok & (spVcommonClass != 0);
    return ok;
}

// @ 0x00a5c7c0
byte x_connective_setup()
{
    byte ok = pdint_setup() & 1;
    ok = ok & pdfloat_setup();
    ok = ok & pdsymbol_setup();
    ok = ok & bang_setup();
    ok = ok & send_setup();
    ok = ok & forward_setup();
    ok = ok & receive_setup();
    ok = ok & select_setup();
    ok = ok & route_setup();
    ok = ok & pack_setup();
    ok = ok & unpack_setup();
    ok = ok & trigger_setup();
    ok = ok & spigot_setup();
    ok = ok & gate_setup();
    ok = ok & switch_setup();
    ok = ok & moses_setup();
    ok = ok & until_setup();
    ok = ok & makefilename_setup();
    ok = ok & swap_setup();
    ok = ok & change_setup();
    ok = ok & value_setup();
    return ok;
}

// ---------------------------------------------------------------- alist
// @ 0x00a5c860
void alist_list(t_alist* self, t_symbol sel, int argc, t_atom* argv)
{
    if (self->atoms != 0)
        freebytes(self->atoms, self->count * sizeof(t_atom));
    self->atoms = (t_atom*)getbytes(argc * sizeof(t_atom), "EAPd/t_list_atoms");
    if (self->atoms == 0) {
        self->count = 0;
        return;
    }
    self->count = argc;
    if (argc <= 0)
        return;
    t_atom* dst = self->atoms;
    for (int i = 0; i < argc; ++i)
        dst[i] = argv[i];
}

// @ 0x00a5c8e0
void alist_anything(t_alist* self, t_symbol sel, int argc, t_atom* argv)
{
    if (self->atoms != 0)
        freebytes(self->atoms, self->count * sizeof(t_atom));
    self->atoms = (t_atom*)getbytes((argc + 1) * sizeof(t_atom), "EAPd/t_list_atoms");
    if (self->atoms == 0) {
        self->count = 0;
        return;
    }
    self->count = argc + 1;
    self->atoms[0].a_type = 2;
    self->atoms[0].s = sel;
    if (argc <= 0)
        return;
    for (int i = 0; i < argc; ++i)
        self->atoms[i + 1] = argv[i];
}

// @ 0x00a5c980
byte alist_setup()
{
    t_symbol tmp;
    t_symbol* s = gensym(&tmp, "list inlet");
    spAlistClass = class_new(*s, 0, 0, 0xc, 0, 0);
    byte ok = (spAlistClass != 0) & 1;
    ok = ok & class_addlist(spAlistClass, (void*)alist_list);
    ok = ok & class_addanything(spAlistClass, (void*)alist_anything);
    return ok;
}

// ---------------------------------------------------------------- list append
// @ 0x00a5c9e0
t_alist_obj* list_append_new(void* a, void* b, int argc, t_atom* argv)
{
    t_alist_obj* x = (t_alist_obj*)pd_new(list_append_class);
    if (x != 0) {
        t_alist* a = &x->a;
        a->count = 0;
        a->atoms = 0;
        a->cls = spAlistClass;
        alist_list(a, gListSymbol, argc, argv);
        outlet_new(x, gListSymbol);
        inlet_new(x, a, gEmptySymbol, gEmptySymbol);
    }
    return x;
}

// @ 0x00a5ca60
void list_append_list(t_alist_obj* self, t_symbol sel, int argc, t_atom* argv)
{
    int n = self->a.count + argc;
    int bytes = n * sizeof(t_atom);
    t_atom* buf;
    if (n < 100)
        buf = (t_atom*)_alloca(bytes);
    else
        buf = (t_atom*)getbytes(bytes, "EAPd/t_list_atoms");
    for (int i = 0; i < argc; ++i)
        buf[i] = argv[i];
    for (int i = 0; i < self->a.count; ++i)
        buf[argc + i] = self->a.atoms[i];
    outlet_list(self->outlet, gListSymbol, n, buf);
    if (n >= 100)
        freebytes(buf, bytes);
}

// @ 0x00a5cb40
void list_append_anything(t_alist_obj* self, t_symbol sel, int argc, t_atom* argv)
{
    int n = self->a.count + 1 + argc;
    int bytes = n * sizeof(t_atom);
    t_atom* buf;
    if (n < 100)
        buf = (t_atom*)_alloca(bytes);
    else
        buf = (t_atom*)getbytes(bytes, "EAPd/t_list_atoms");
    buf[0].a_type = 2;
    buf[0].s = sel;
    for (int i = 0; i < argc; ++i)
        buf[i + 1] = argv[i];
    for (int i = 0; i < self->a.count; ++i)
        buf[argc + 1 + i] = self->a.atoms[i];
    outlet_list(self->outlet, gListSymbol, n, buf);
    if (n >= 100)
        freebytes(buf, bytes);
}

// @ 0x00a5cc30
byte list_append_setup()
{
    t_symbol tmp;
    t_symbol* s = gensym(&tmp, "list append");
    list_append_class = class_new(*s, (void*)list_append_new, (void*)list_prepend_free,
                                  0x34, 0, 9, 0);
    byte ok = (list_append_class != 0) & 1;
    ok = ok & class_addlist(list_append_class, (void*)list_append_list);
    ok = ok & class_addanything(list_append_class, (void*)list_append_anything);
    class_sethelpsymbol(list_append_class, gListSymbol);
    return ok;
}

// ---------------------------------------------------------------- list prepend
// @ 0x00a5ccb0
t_alist_obj* list_prepend_new(void* a, void* b, int argc, t_atom* argv)
{
    t_alist_obj* x = (t_alist_obj*)pd_new(list_prepend_class);
    if (x != 0) {
        t_alist* a = &x->a;
        a->count = 0;
        a->atoms = 0;
        a->cls = spAlistClass;
        alist_list(a, gListSymbol, argc, argv);
        outlet_new(x, gListSymbol);
        inlet_new(x, a, gEmptySymbol, gEmptySymbol);
    }
    return x;
}

// @ 0x00a5cd30
void list_prepend_list(t_alist_obj* self, t_symbol sel, int argc, t_atom* argv)
{
    int n = self->a.count + argc;
    int bytes = n * sizeof(t_atom);
    t_atom* buf;
    if (n < 100)
        buf = (t_atom*)_alloca(bytes);
    else
        buf = (t_atom*)getbytes(bytes, "EAPd/t_list_atoms");
    for (int i = 0; i < self->a.count; ++i)
        buf[i] = self->a.atoms[i];
    for (int i = 0; i < argc; ++i)
        buf[self->a.count + i] = argv[i];
    outlet_list(self->outlet, gListSymbol, n, buf);
    if (n >= 100)
        freebytes(buf, bytes);
}

// @ 0x00a5ce20
void list_prepend_anything(t_alist_obj* self, t_symbol sel, int argc, t_atom* argv)
{
    int n = self->a.count + 1 + argc;
    int bytes = n * sizeof(t_atom);
    t_atom* buf;
    if (n < 100)
        buf = (t_atom*)_alloca(bytes);
    else
        buf = (t_atom*)getbytes(bytes, "EAPd/t_list_atoms");
    for (int i = 0; i < self->a.count; ++i)
        buf[i] = self->a.atoms[i];
    buf[self->a.count].a_type = 2;
    buf[self->a.count].s = sel;
    for (int i = 0; i < argc; ++i)
        buf[self->a.count + 1 + i] = argv[i];
    outlet_list(self->outlet, gListSymbol, n, buf);
    if (n >= 100)
        freebytes(buf, bytes);
}

// @ 0x00a5cf20
void list_prepend_free(t_alist_obj* self)
{
    if (self->a.atoms != 0)
        freebytes(self->a.atoms, self->a.count * sizeof(t_atom));
}

// @ 0x00a5cf40
byte list_prepend_setup()
{
    t_symbol tmp;
    t_symbol* s = gensym(&tmp, "list prepend");
    list_prepend_class = class_new(*s, (void*)list_prepend_new, (void*)list_prepend_free,
                                   0x34, 0, 9, 0);
    byte ok = (list_prepend_class != 0) & 1;
    ok = ok & class_addlist(list_prepend_class, (void*)list_prepend_list);
    ok = ok & class_addanything(list_prepend_class, (void*)list_prepend_anything);
    class_sethelpsymbol(list_prepend_class, gListSymbol);
    return ok;
}

// ---------------------------------------------------------------- list split
// @ 0x00a5cfc0
t_list_split* list_split_new(float split)
{
    t_list_split* x = (t_list_split*)pd_new(list_split_class);
    if (x != 0) {
        x->outlet1 = outlet_new(x, gListSymbol);
        x->outlet2 = outlet_new(x, gListSymbol);
        x->outlet3 = outlet_new(x, gListSymbol);
        floatinlet_new(x, &x->split);
        x->split = split;
    }
    return x;
}

// @ 0x00a5d040
void list_split_list(t_list_split* self, t_symbol sel, int argc, t_atom* argv)
{
    if (self != 0) {
        int i = (int)self->split;
        if (i < 0)
            i = 0;
        if (argc >= i) {
            outlet_list(self->outlet2, gListSymbol, argc - i, argv + i);
            outlet_list(self->outlet1, gListSymbol, i, argv);
        } else {
            outlet_list(self->outlet3, gListSymbol, argc, argv);
        }
    }
}

// @ 0x00a5d0d0
void list_split_anything(t_list_split* self, t_symbol sel, int argc, t_atom* argv)
{
    int n = argc + 1;
    int bytes = n * sizeof(t_atom);
    t_atom* buf;
    if (n < 100)
        buf = (t_atom*)_alloca(bytes);
    else
        buf = (t_atom*)getbytes(bytes, "EAPd/t_list_atoms");
    buf[0].a_type = 2;
    buf[0].s = sel;
    for (int i = 0; i < argc; ++i)
        buf[i + 1] = argv[i];
    list_split_list(self, gListSymbol, n, buf);
    if (n >= 100)
        freebytes(buf, bytes);
}

// @ 0x00a5d180
byte list_split_setup()
{
    t_symbol tmp;
    t_symbol* s = gensym(&tmp, "list split");
    list_split_class = class_new(*s, (void*)list_split_new, 0, 0x38, 0, 5, 0);
    byte ok = (list_split_class != 0) & 1;
    ok = ok & class_addlist(list_split_class, (void*)list_split_list);
    ok = ok & class_addanything(list_split_class, (void*)list_split_anything);
    class_sethelpsymbol(list_split_class, gListSymbol);
    return ok;
}

// ---------------------------------------------------------------- list trim
// @ 0x00a5d200
t_list_trim* list_trim_new()
{
    t_list_trim* x = (t_list_trim*)pd_new(list_trim_class);
    if (x != 0)
        outlet_new(x, gListSymbol);
    return x;
}

// @ 0x00a5d290
byte list_trim_setup()
{
    t_symbol tmp;
    t_symbol* s = gensym(&tmp, "list trim");
    list_trim_class = class_new(*s, (void*)list_trim_new, 0, 0x28, 0, 0);
    byte ok = (list_trim_class != 0) & 1;
    ok = ok & class_addlist(list_trim_class, (void*)list_trim_list);
    ok = ok & class_addanything(list_trim_class, (void*)vinlet_anything);
    class_sethelpsymbol(list_trim_class, gListSymbol);
    return ok;
}

// ---------------------------------------------------------------- list message
// @ 0x00a5d310
t_list_message* list_message_new(t_symbol sel)
{
    t_list_message* x = (t_list_message*)pd_new(spListMessageClass);
    if (x != 0) {
        x->sel = sel;
        symbolinlet_new(x, &x->sel);
        outlet_new(x, gAnythingSymbol);
    }
    return x;
}

// @ 0x00a5d360
void list_message_list(t_list_message* self, t_symbol sel, int argc, t_atom* argv)
{
    if (gEmptySymbol.a != self->sel.a) {
        outlet_anything(self->outlet, self->sel, argc, argv);
    } else if (argc > 0 && argv[0].a_type == 2) {
        outlet_anything(self->outlet, argv[0].s, argc - 1, argv + 1);
    }
}

}}} // namespace EA::Audio::Eapd
