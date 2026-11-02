// src/game/SPAudio/eapdlist.cpp -- migrated from slice(s) s00a5d3c0, s00a5c460 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdlist.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <malloc.h>
#include <windows.h>

// ---- items of slice s00a5c460 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char byte;
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol {
    int a;                              // 0x00
    int b;                              // 0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom {                         // 12 bytes
    int a_type;                         // 0x00
    t_symbol s;                         // 0x04
};
}
}
}
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
struct t_alist {
    t_class* cls;                       // 0x00
    int count;                          // 0x04
    t_atom* atoms;                      // 0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_alist_obj {
    int pad00[3];                       // 0x00
    void* outlet;                       // 0x0c
    int pad10[6];                       // 0x10
    t_alist a;                          // 0x28
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
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
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_list_trim {
    int pad00;                          // 0x00
    int pad04;                          // 0x04
    int pad08;                          // 0x08
    void* outlet;                       // 0x0c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_list_message {
    int pad00;                          // 0x00
    int pad04;                          // 0x04
    int pad08;                          // 0x08
    void* outlet;                       // 0x0c
    int pad10[6];                       // 0x10
    t_symbol sel;                       // 0x28
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol* gensym(t_symbol* out, const char* name);                    // 0x00a675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class* class_new(t_symbol name, void* newfn, void* freefn, int size,
                   int flags, int nargs, int arg);                     // 0x00a48ea0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class* class_new(t_symbol name, void* newfn, void* freefn, int size,
                   int flags, int nargs);                              // 0x00a48e50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
byte class_addlist(t_class* cls, void* fn);                            // 0x00a47f70
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
byte class_addanything(t_class* cls, void* fn);                        // 0x00a47f90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void class_sethelpsymbol(t_class* cls, t_symbol name);                 // 0x00a47fc0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* pd_new(t_class* cls);                                           // 0x00a49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* outlet_new(void* obj, t_symbol sel);                            // 0x00a49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void outlet_list(void* outlet, t_symbol sel, int argc, t_atom* argv); // 0x00a49e40
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void outlet_anything(void* outlet, t_symbol sel, int argc, t_atom* argv); // 0x00a49eb0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* inlet_new(void* obj, void* target, t_symbol a, t_symbol b);      // 0x00a49740
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* floatinlet_new(void* obj, float* p);                            // 0x00a49a00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* symbolinlet_new(void* obj, t_symbol* p);                        // 0x00a49ab0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* getbytes(int size, const char* name);                           // 0x00a49610
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void freebytes(void* p, int size);                                    // 0x00a49650
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void list_prepend_free(t_alist_obj* self);                                // 0x00a5cf20
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void list_trim_list();                                                // 0x00a5d230
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void vinlet_anything();                                               // 0x00a614e0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* list_append_class;                                    // 0x01675684
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* list_split_class;                                     // 0x01675688
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* list_trim_class;                                      // 0x0167568c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spAlistClass;                                         // 0x01675690
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* list_prepend_class;                                   // 0x01675694
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spListMessageClass;                                   // 0x01675698
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol gEmptySymbol;                                         // 0x0167589c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol gListSymbol;                                          // 0x016758ac
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol gAnythingSymbol;                                      // 0x016758cc
}
}
}
// ---- items of slice s00a5c460 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace EA { namespace Audio { namespace Eapd { void alist_anything(t_alist* self, t_symbol sel, int argc, t_atom* argv); }}}  // 0x00a5c8e0 (stays in the slice: not this object's)

// ---- items of slice s00a5d3c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol_s00a5_d3c0 {
    const char* s_name;     // +0x00
    void* s_thing;          // +0x04
};
}
}
}
using EA::Audio::Eapd::t_symbol_s00a5_d3c0;
t_symbol_s00a5_d3c0* gensym(t_symbol_s00a5_d3c0* s, const char* name);
void* class_new(const char* name, void* thing, void* newmethod, void* freemethod,
                int size, int flags, int type, ...);
int class_addlist(void* c, void* fn);
int class_sethelpsymbol(void* c, const char* name, void* thing);
int class_addcreator(void* fn, const char* name, void* thing, int type, int extra);
void* g_listTrimClass_167568c;
void* g_listMessageClass_1675698;
void* g_newestObject_16753f4;
t_symbol_s00a5_d3c0 g_emptySymbol_167589c;         // "" symbol
t_symbol_s00a5_d3c0 g_listSymbol_16758ac;          // "list"
void* list_append_new(int n, int flag, int ac, void* av);
void* list_prepend_new(int n, int flag, int ac, void* av);
void* list_split_new(float f);
void* list_trim_new();
void* list_message_new(const char* name, void* thing);
void* list_message_ctor(t_symbol_s00a5_d3c0* s);
void list_message_list(void* x, t_symbol_s00a5_d3c0* s, int ac, void* av);
float atom_getfloat_at(int i, int ac, void* av);
byte alist_setup();
byte list_append_setup();
byte list_prepend_setup();
byte list_split_setup();
byte list_trim_setup();
byte list_message_setup();
void* list_new(void* x, int n, int flag, int ac, void* av);
// ---- items of slice s00a5d3c0 end

// @ 0x00a5c860
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c980
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c9e0
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ca60
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5cb40
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5cc30
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ccb0
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5cd30
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ce20
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5cf20
namespace EA { namespace Audio { namespace Eapd {
void list_prepend_free(t_alist_obj* self)
{
    if (self->a.atoms != 0)
        freebytes(self->a.atoms, self->a.count * sizeof(t_atom));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5cf40
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5cfc0
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5d040
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5d0d0
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5d180
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5d200
namespace EA { namespace Audio { namespace Eapd {
t_list_trim* list_trim_new()
{
    t_list_trim* x = (t_list_trim*)pd_new(list_trim_class);
    if (x != 0)
        outlet_new(x, gListSymbol);
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5d290
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5d310
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5d360
namespace EA { namespace Audio { namespace Eapd {
void list_message_list(t_list_message* self, t_symbol sel, int argc, t_atom* argv)
{
    if (gEmptySymbol.a != self->sel.a) {
        outlet_anything(self->outlet, self->sel, argc, argv);
    } else if (argc > 0 && argv[0].a_type == 2) {
        outlet_anything(self->outlet, argv[0].s, argc - 1, argv + 1);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5d3c0
byte list_message_setup()
{
    t_symbol_s00a5_d3c0 local;
    t_symbol_s00a5_d3c0* s = gensym(&local, "list message");
    g_listMessageClass_1675698 = class_new(s->s_name, s->s_thing, (void*)list_message_ctor,
                                           0, 0x30, 0, 6, 0);
    byte ok = g_listMessageClass_1675698 != 0;
    byte added = class_addlist(g_listMessageClass_1675698, (void*)list_message_list);
    class_sethelpsymbol(g_listTrimClass_167568c, g_listSymbol_16758ac.s_name,
                        g_listSymbol_16758ac.s_thing);
    return (byte)(added & ok);
}

// @ 0x00a5d430
void* list_new(void* x, int n, int flag, int ac, void* av)
{
    if (ac != 0 && *(int*)av == 2)
    {
        int selector = ((int*)av)[1];
        t_symbol_s00a5_d3c0 local;

        if (selector == (int)gensym(&local, "append")->s_name)
        {
            g_newestObject_16753f4 = list_append_new(n, flag, ac - 1, (char*)av + 0xc);
        }
        else if (selector == (int)gensym(&local, "prepend")->s_name)
        {
            g_newestObject_16753f4 = list_prepend_new(n, flag, ac - 1, (char*)av + 0xc);
        }
        else if (selector == (int)gensym(&local, "split")->s_name)
        {
            g_newestObject_16753f4 = list_split_new(atom_getfloat_at(1, ac, av));
        }
        else if (selector == (int)gensym(&local, "trim")->s_name)
        {
            g_newestObject_16753f4 = list_trim_new();
        }
        else if (selector == (int)gensym(&local, "message")->s_name)
        {
            t_symbol_s00a5_d3c0* args;
            if (ac > 1 && ((int*)av)[3] == 2)
                args = (t_symbol_s00a5_d3c0*)((char*)av + 0x10);
            else
                args = &g_emptySymbol_167589c;
            g_newestObject_16753f4 = list_message_new(args->s_name, args->s_thing);
        }
        else
        {
            g_newestObject_16753f4 = 0;
        }
        return g_newestObject_16753f4;
    }

    g_newestObject_16753f4 = list_append_new(n, flag, ac, av);
    return g_newestObject_16753f4;
}

// @ 0x00a5d5a0
namespace EA {
namespace Audio {
namespace Eapd {
bool x_list_setup()
{
    byte a = alist_setup();
    byte b = list_append_setup();
    byte c = list_prepend_setup();
    byte d = list_split_setup();
    byte e = list_trim_setup();
    byte f = list_message_setup();
    byte g = class_addcreator((void*)list_new, g_listSymbol_16758ac.s_name,
                              g_listSymbol_16758ac.s_thing, 9, 0);
    return (byte)(g & a & 1 & b & c & d & e & f);
}
}
}
}  // namespace EA::Audio::Eapd
