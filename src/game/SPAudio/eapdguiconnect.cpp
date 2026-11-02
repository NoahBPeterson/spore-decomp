// src/game/SPAudio/eapdguiconnect.cpp -- migrated from slice(s) s00a4e2e0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdguiconnect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stdio.h>
#include <string.h>

// ---- items of slice s00a4e2e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct t_binbuf;
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
struct t_glist;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_rtext;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol {
    uint32_t    s_hash;    // +0
    void*       s_name;    // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom {
    int      a_type;
    t_symbol a_w;
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_editor {
    uint32_t     pad00[3];
    t_rtext*     e_rtextlist;    // +0x0c  list of live t_rtext items
    uint32_t     pad10;
    t_rtext*     e_textedfor;    // +0x14
    uint32_t     pad18[14];
    unsigned     e_flags;        // +0x50: bit 0x10 = textdirty
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gobj {
    t_class* g_pd;      // +0x00
    t_gobj*  g_next;    // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_text : t_gobj {
    t_binbuf* te_binbuf;    // +0x08
    void*     te_outlet;    // +0x0c
    void*     te_inlet;     // +0x10
    int16_t   te_xpix;      // +0x14
    int16_t   te_ypix;      // +0x16
    int16_t   te_width;     // +0x18
    int16_t   pad1a;        // +0x1a
    unsigned  te_type;      // +0x1c: low 2 bits
    t_glist*  te_owner;     // +0x24
    t_glist*  te_glist;     // +0x28
    char      te_tag[0x34]; // +0x2c
    void*     te_next;      // +0x60
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_glist {
    uint32_t  pad00[0x28 / 4];
    t_gobj*   gl_list;      // +0x28
    t_glist*  gl_owner;     // +0x2c
    uint32_t  pad30[2];
    float     gl_x1;        // +0x38
    float     gl_y1;        // +0x3c
    float     gl_x2;        // +0x40
    float     gl_y2;        // +0x44
    uint32_t  pad48[6];
    t_editor* gl_editor;    // +0x60
    uint32_t  pad64[5];
    uint32_t  gl_flags;     // +0x78: 0x100 = graph widget, 1 = "goprect"
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_rtext {
    char*     rt_buf;       // +0x00 shared string from binbuf_gettext
    int       rt_bufsize;   // +0x04
    int       rt_selectfrom;// +0x08
    int       rt_selectto;  // +0x0c
    int       rt_active;    // +0x10
    int       rt_xpix;      // +0x14
    int       rt_ypix;      // +0x18
    int       rt_width;     // +0x1c
    int       rt_height;    // +0x20
    t_text*   rt_owner;     // +0x24
    t_glist*  rt_glist;     // +0x28
    char      rt_tag[0x34]; // +0x2c
    t_rtext*  rt_next;      // +0x60
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_guiconnect {
    t_class*  gc_pd;        // +0x00
    uint32_t  pad04[9];
    t_glist*  gc_target;    // +0x28
    t_symbol  gc_symA;      // +0x2c  (hash, name)
    t_guiconnect* gc_prev;  // +0x34
    t_guiconnect* gc_next;  // +0x38
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class*        spGuiconnectClass;   // 0x16754e8
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_guiconnect*   guiconnectlist;      // 0x16754e4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol        gEmptySymbol;        // 0x167589c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol* gensym(t_symbol* out, const char* s);                        // 0xa675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class*  class_new(t_symbol name, void* newmethod, void* freemethod,
                    int size, int flags, int a1);                      // 0xa48e50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool      class_addanything(t_class* c, void* fn);                     // 0xa47f90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool      class_addmethod(t_class* c, void* fn, t_symbol name, void* a1); // 0xa48a30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*     pd_new(t_class* c);                                          // 0xa49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*     pd_findbyclass(uint32_t a, void* b, t_class* c);             // 0xa671f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void      pd_bind(void* x, t_symbol s);                                // 0xa67620
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void      pd_free(void* x);                                            // 0xa493d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void      pd_typedmess(void* x, t_symbol s, int argc, t_atom* argv);   // 0xa48100
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void      sys_vgui(unsigned int a, unsigned int b, unsigned int c);     // 0xa671b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* guiconnect_new(t_glist* target, t_symbol s);                     // 0xa4e6c0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void guiconnect_unlink(void* x);                                         // 0xa4e750
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void guiconnect_notarget(t_guiconnect* gc);                              // 0xa4e780
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void guiconnect_signoff(t_guiconnect* gc);                               // 0xa4e7a0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void guiconnect_anything(t_guiconnect* gc, t_symbol s, int argc, t_atom* argv); // 0xa4e7e0
}
}
}
// ---- items of slice s00a4e2e0 end

// @ 0x00a4e6c0
namespace EA { namespace Audio { namespace Eapd {
void* guiconnect_new(t_glist* target, t_symbol s)
{
    t_guiconnect* gc = (t_guiconnect*)pd_findbyclass(s.s_hash, s.s_name, spGuiconnectClass);

    if (gc) {
        gc->gc_target = target;
        return gc;
    }
    gc = (t_guiconnect*)pd_new(spGuiconnectClass);
    if (gc) {
        gc->gc_target = target;
        gc->gc_symA = s;
        pd_bind(gc, s);
        gc->gc_next = 0;
        gc->gc_prev = guiconnectlist;
        if (guiconnectlist)
            guiconnectlist->gc_next = gc;
        guiconnectlist = gc;
    }
    return gc;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4e750
namespace EA { namespace Audio { namespace Eapd {
void guiconnect_unlink(void* x)
{
    t_guiconnect* gc = (t_guiconnect*)x;

    if (guiconnectlist == gc)
        guiconnectlist = gc->gc_prev;
    if (gc->gc_next)
        gc->gc_next->gc_prev = gc->gc_prev;
    if (gc->gc_prev)
        gc->gc_prev->gc_next = gc->gc_next;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4e780
namespace EA { namespace Audio { namespace Eapd {
void guiconnect_notarget(t_guiconnect* gc)
{
    gc->gc_target = 0;
    if (gc->gc_symA.s_hash == gEmptySymbol.s_hash)
        pd_free(gc);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4e7a0
namespace EA { namespace Audio { namespace Eapd {
void guiconnect_signoff(t_guiconnect* gc)
{
    if (gc->gc_target == 0) {
        sys_vgui((unsigned)(size_t)gc, gc->gc_symA.s_hash, (unsigned)(size_t)gc->gc_symA.s_name);
        gc->gc_symA = gEmptySymbol;
        pd_free(gc);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4e7e0
namespace EA { namespace Audio { namespace Eapd {
void guiconnect_anything(t_guiconnect* gc, t_symbol s, int argc, t_atom* argv)
{
    if (gc->gc_target)
        pd_typedmess(gc->gc_target, s, argc, argv);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4e810
namespace EA {
namespace Audio {
namespace Eapd {
bool g_guiconnect_setup()
{
    t_symbol tmp;
    t_symbol* s;
    char ok;

    s = gensym(&tmp, "guiconnect");
    spGuiconnectClass = class_new(*s, 0, (void*)guiconnect_unlink, 0x3c, 1, 0);
    ok = (spGuiconnectClass != 0);
    ok &= class_addanything(spGuiconnectClass, (void*)guiconnect_anything);
    s = gensym(&tmp, "signoff");
    ok &= class_addmethod(spGuiconnectClass, (void*)guiconnect_signoff, *s, 0);
    guiconnectlist = 0;
    return ok;
}
}
}
}  // namespace EA::Audio::Eapd
