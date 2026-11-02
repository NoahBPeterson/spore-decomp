// src/game/SPAudio/eapdcore.cpp -- migrated from slice(s) s00a488d0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdcore.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

namespace EA { namespace Audio { namespace Eapd { class _class; } } }
namespace EA { namespace Audio { namespace Eapd { class _outlet; } } }

// ---- items of slice s00a488d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct t_gobj;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol {
    void* s_name;    // +0
    void* s_thing;   // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class {
    void* c_name;         // +0
    void* c_helpname;     // +4
    void* c_helpdir;      // +8
    char  pad0[0x10 - 0xc];
    void* c_filetypes;    // +0x10
    void* c_filedefault;  // +0x14
    unsigned c_size;      // +0x18
    void* c_methods;      // +0x1c
    int   c_nmethod;      // +0x20
    void* c_freemethod;   // +0x24
    void* c_bangmethod;   // +0x28
    void* c_floatmethod;  // +0x2c
    void* c_symbolmethod; // +0x30
    void* c_listmethod;   // +0x34
    void* c_anymethod;    // +0x38
    void* c_wb;           // +0x3c
    void* c_savefn;       // +0x40
    void* c_propertiesfn; // +0x44
    char  c_gobj;         // +0x48
    char  c_patchable;    // +0x49
    char  c_firstin;      // +0x4a
    t_class* c_next;      // +0x4c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gobj {
    t_class* g_pd;    // +0
    t_gobj*  g_next;  // +4
    char pad[0x24 - 8];
    void*    o_save;  // +0x24
    char pad2[0x49 - 0x28];
    char     o_flags; // +0x49
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_sysstack {         // 0x10-byte node
    t_gobj*     s_what;     // +0
    t_symbol*   s_sym_a;    // +4
    t_symbol*   s_sym_b;    // +8
    t_sysstack* s_next;     // +0xc
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol    gSysSym;         // 0x16758bc / c0   (sys_gui selector)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol    gAnythingSym;    // 0x167589c / a0   ("anything")
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol    gListSym2;       // 0x16758ac / b0   ("list", used by pd_list)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_sysstack* s_stack;        // 0x1675444  (sys_register_loader / pd_pushsym list head)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  free_save_list(void* p);                                                 // 0xa49f20
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  free_gop_list(void* p);                                                  // 0xa49990
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  class_freemethod(void* o);                                               // 0xa46c50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  sys_gui_acquire(void* obj, void* sel_a, void* sel_b);                    // 0xa671b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  sys_gui_release(void* obj, void* sel_a, void* sel_b);                    // 0xa67620
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* getbytes(int n, const char* tag);                                        // 0xa49610
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  freebytes(void* p, int n);                                               // 0xa49650
}
}
}
// ---- items of slice s00a488d0 end

// @ 0x00a49390
namespace EA { namespace Audio { namespace Eapd {
void* pd_new(t_class* c)
{
    const char* tag = (const char*)c->c_helpname;
    t_gobj* o = (t_gobj*)getbytes(c->c_size, tag);
    o->g_pd = c;
    if (c->c_patchable) {
        *(void**)((char*)o + 0x10) = 0;
        *(void**)((char*)o + 0x0c) = 0;
        *(void**)((char*)o + 0x20) = gAnythingSym.s_name;
        *(void**)((char*)o + 0x24) = gAnythingSym.s_thing;
    }
    return o;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a493d0
namespace EA { namespace Audio { namespace Eapd {
void pd_free(t_gobj* o)
{
    t_class* c = o->g_pd;
    if (c->c_freemethod)
        ((void (*)(void*))c->c_freemethod)(o);
    if (c->c_patchable) {
        void* p;
        while ((p = *(void**)((char*)o + 0x0c)) != 0) {
            free_save_list(p);
            if (!*(void**)((char*)o + 0x0c))
                break;
        }
        while ((p = *(void**)((char*)o + 0x10)) != 0) {
            free_gop_list(p);
            if (!*(void**)((char*)o + 0x10))
                break;
        }
        if (*(void**)((char*)o + 8))
            class_freemethod(*(void**)((char*)o + 8));
    }
    if (c->c_size)
        freebytes(o, c->c_size);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49450
namespace EA { namespace Audio { namespace Eapd {
bool sys_register_loader(void* a, void* b)
{
    t_sysstack* s = s_stack;
    s->s_sym_a = (t_symbol*)a;
    s->s_sym_b = (t_symbol*)b;
    t_sysstack* r = s->s_next;
    while (r) {
        if (r->s_sym_a == (t_symbol*)a)
            return true;
        r = r->s_next;
    }
    return false;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49490
namespace EA { namespace Audio { namespace Eapd {
void pd_pushsym(t_gobj* x)
{
    if (s_stack)
        sys_gui_acquire(*(void**)s_stack, gSysSym.s_name, gSysSym.s_thing);
    sys_gui_release(x, gSysSym.s_name, gSysSym.s_thing);
    t_sysstack* s = (t_sysstack*)getbytes(0x10, "sysstack");
    t_sysstack* next = s_stack;
    s->s_what = x;
    s->s_next = next;
    s->s_sym_a = (t_symbol*)gAnythingSym.s_name;
    s->s_sym_b = (t_symbol*)gAnythingSym.s_thing;
    s_stack = s;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49500
namespace EA {
namespace Audio {
namespace Eapd {
void pd_popsym(_class ** x)
{
    t_sysstack* s = s_stack;
    s_stack = s->s_next;
    freebytes(s, 0x10);
    sys_gui_acquire(x, gSysSym.s_name, gSysSym.s_thing);
    if (s_stack)
        sys_gui_release(*(void**)s_stack, gSysSym.s_name, gSysSym.s_thing);
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a49560
namespace EA {
namespace Audio {
namespace Eapd {
void pd_bang(_class ** x)
{
    t_class* c = *(t_class**)x;
    typedef void (*Fn)(void*);
    ((Fn)c->c_bangmethod)(x);
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a49570
namespace EA {
namespace Audio {
namespace Eapd {
void outlet_float(_outlet * x, float f)
{
    void* c = *(void**)x;
    typedef void (*Fn)(void*, float);
    ((Fn)(*(void**)((char*)c + 0x2c)))(x, f);
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a49590
namespace EA { namespace Audio { namespace Eapd {
void pd_symbol(t_gobj* x, t_symbol s)
{
    void* c = *(void**)x;
    typedef void (*Fn)(void*, t_symbol);
    ((Fn)(*(void**)((char*)c + 0x30)))(x, s);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a495b0
namespace EA { namespace Audio { namespace Eapd {
void pd_list(t_gobj* x, int a1, int a2, int n, void* argv)
{
    void* c = *(void**)x;
    typedef void (*Fn)(void*, void*, void*, int, void*);
    ((Fn)(*(void**)((char*)c + 0x34)))(x, gListSym2.s_name, gListSym2.s_thing, n, argv);
}
}}}  // namespace EA::Audio::Eapd
