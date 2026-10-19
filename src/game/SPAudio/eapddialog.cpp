// src/game/SPAudio/eapddialog.cpp -- migrated from slice(s) s00a4c300 by tools/migrate/rewrite.py
// Object file: SPAudio/eapddialog.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

namespace EA { namespace Audio { namespace Eapd { class _class; } } }
#include <stdio.h>

// ---- items of slice s00a4c300 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol {
    void* s_name;
    void* s_thing;
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
struct t_widgetbehavior {
    void (*w_getrectfn)(t_gobj* x, t_glist* glist, int* x1, int* y1, int* x2, int* y2);   // +0
    void* w_displacefn;                                                                    // +4
    void (*w_selectfn)(t_gobj* x, t_glist* glist, int state);                              // +8
    void (*w_activatefn)(t_gobj* x, t_glist* glist, int state);                            // +0xc
    void* w_deletefn;                                                                      // +0x10
    void* w_visfn;                                                                         // +0x14
    int (*w_clickfn)(t_gobj* x, t_glist* glist, int xpos, int ypos, int shift, int alt,
                     int dbl, int doit);                                                   // +0x18
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class {
    char pad[0x3c];
    t_widgetbehavior* c_wb;   // +0x3c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gobj {
    t_class* g_pd;   // +0
    t_gobj* g_next;  // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_selection {
    t_gobj* sel_what;   // +0
    t_selection* sel_next;   // +4
};
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
struct t_binbuf;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_editor {
    char pad0[0x10];
    t_selection* e_selection;   // +0x10
    t_rtext* e_textedfor;       // +0x14
    char pad18[0x24 - 0x18];
    t_binbuf* e_connectbuf;     // +0x24
    char pad28[0x34 - 0x28];
    int e_xwas;                 // +0x34
    int e_ywas;                 // +0x38
    char pad3c[0x4c - 0x3c];
    unsigned e_selectline_tag;  // +0x4c
    unsigned e_flags;           // +0x50: bits 0-2 onmotion, 0x10 textdirty, 0x20 selectedline
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_glist : t_gobj {
    char pad8[0x28 - 8];
    t_gobj* gl_list;          // +0x28
    t_glist* gl_owner;        // +0x2c
    int gl_pixwidth;          // +0x30
    int gl_pixheight;         // +0x34
    float gl_x1, gl_y1, gl_x2, gl_y2;   // +0x38..+0x44
    char pad48[0x58 - 0x48];
    int gl_xmargin;           // +0x58
    int gl_ymargin;           // +0x5c
    t_editor* gl_editor;      // +0x60
    char pad64[0x78 - 0x64];
    unsigned gl_flags;        // +0x78
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gfxstub {
    void* x_pd;           // +0
    unsigned x_owner;      // +4
    unsigned x_key;        // +8
    void* x_sym_a;        // +0xc
    void* x_sym_b;        // +0x10
    t_gfxstub* x_next;    // +0x14
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_savepanel {
    void* x_obj[10];
    void* x_s_a;   // +0x28
    void* x_s_b;   // +0x2c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol* gensym(t_symbol* out, const char* s);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class* class_new(t_symbol name, void* newmethod, void* freemethod, int size, int flags, int a1, int a2);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class* class_new(t_symbol name, void* newmethod, void* freemethod, int size, int flags, int a1);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addbang(t_class* c, void* fn);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addsymbol(t_class* c, void* fn);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addanything(t_class* c, void* fn);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addmethod(t_class* c, void* fn, t_symbol name, int a1, int a2, int a3, int a4, int a5);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addmethod(t_class* c, void* fn, t_symbol name, int a1);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* pd_new(t_class* c);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void pd_bind(void* x, t_symbol s);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* outlet_new(void* x, t_symbol s);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void sys_gui(const char* fmt, ...);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* openpanel_new();            // 0xa4c250
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void openpanel_free(void* x);     // 0xa4c2e0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void openpanel_bang(void* x);     // 0xa4c2c0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void panel_symbol(void* x, void* s);   // 0xa5a140 (shared symbol method)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void gfxstub_anything(void* x);   // 0xa4c200
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void gfxstub_free(void* x);       // 0xa4c230
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void gfxstub_signoff(void* x);    // 0xa4c1f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void gfxstub_cancel(void* x);     // 0xa4c1e0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void gfxstub_deleteforkey(void* key);   // 0xa4c170
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spOpenpanelClass;   // 0x1675498
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spSavepanelClass;   // 0x167549c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_gfxstub* gfxstub_list;     // 0x1675494
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spGfxstubClass;     // 0x16754a0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol gSymbolSymbol;          // 0x1675894
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* savepanel_new();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void savepanel_bang(t_savepanel* x);
}
}
}
// ---- items of slice s00a4c300 end

// @ 0x00a4c300
namespace EA { namespace Audio { namespace Eapd {
bool openpanel_setup()
{
    t_symbol tmp;
    t_symbol* s = gensym(&tmp, "openpanel");
    spOpenpanelClass = class_new(*s, (void*)openpanel_new, (void*)openpanel_free, 0x30, 0, 5, 0);
    bool ok = true;
    ok &= spOpenpanelClass != 0;
    ok &= class_addbang(spOpenpanelClass, (void*)openpanel_bang);
    ok &= class_addsymbol(spOpenpanelClass, (void*)panel_symbol);
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4c370
namespace EA { namespace Audio { namespace Eapd {
void* savepanel_new()
{
    t_savepanel* x = (t_savepanel*)pd_new(spSavepanelClass);
    if (x) {
        char buf[52];
        sprintf(buf, "d%lx", x);
        t_symbol tmp;
        t_symbol* s = gensym(&tmp, buf);
        x->x_s_a = s->s_name;
        x->x_s_b = s->s_thing;
        pd_bind(x, *s);
        outlet_new(x, gSymbolSymbol);
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4c3e0
namespace EA { namespace Audio { namespace Eapd {
void savepanel_bang(t_savepanel* x)
{
    sys_gui("pdtk_savepanel %s\n", x->x_s_b);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4c400
namespace EA { namespace Audio { namespace Eapd {
bool savepanel_setup()
{
    t_symbol tmp;
    t_symbol* s = gensym(&tmp, "savepanel");
    spSavepanelClass = class_new(*s, (void*)savepanel_new, (void*)openpanel_free, 0x30, 0, 5, 0);
    bool ok = true;
    ok &= spSavepanelClass != 0;
    ok &= class_addbang(spSavepanelClass, (void*)savepanel_bang);
    ok &= class_addsymbol(spSavepanelClass, (void*)panel_symbol);
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4c470
namespace EA {
namespace Audio {
namespace Eapd {
void gfxstub_new(_class ** owner, void * key, char const * cmd)
{
    char buf1[80];
    char buf2[4000];
    for (t_gfxstub* x = gfxstub_list; x; x = x->x_next)
        if (x->x_key == (unsigned)key) gfxstub_deleteforkey(key);
    const char* p = cmd;
    const char* e = cmd + 1;
    char c;
    do {
        c = *p;
        p++;
    } while (c != 0);
    if ((unsigned)((p - e) + 0x32) <= 4000) {
        t_gfxstub* x = (t_gfxstub*)pd_new(spGfxstubClass);
        sprintf(buf1, ".gfxstub%lx", x);
        t_symbol tmp;
        t_symbol sym = *gensym(&tmp, buf1);
        pd_bind(x, sym);
        x->x_owner = (unsigned)owner;
        x->x_key = (unsigned)key;
        x->x_sym_a = sym.s_name;
        x->x_sym_b = sym.s_thing;
        x->x_next = gfxstub_list;
        gfxstub_list = x;
        sprintf(buf2, cmd, sym.s_thing);
        sys_gui(buf2);
    }
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a4c560
namespace EA { namespace Audio { namespace Eapd {
bool gfxstub_setup()
{
    t_symbol tmp;
    t_symbol* s = gensym(&tmp, "gfxstub");
    spGfxstubClass = class_new(*s, (void*)gfxstub_new, (void*)gfxstub_free, 0x18, 1, 0);
    bool ok = true;
    ok &= spGfxstubClass != 0;
    ok &= class_addanything(spGfxstubClass, (void*)gfxstub_anything);
    s = gensym(&tmp, "signoff");
    ok &= class_addmethod(spGfxstubClass, (void*)gfxstub_signoff, *s, 0);
    s = gensym(&tmp, "cancel");
    ok &= class_addmethod(spGfxstubClass, (void*)gfxstub_cancel, *s, 0);
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4c610
namespace EA {
namespace Audio {
namespace Eapd {
bool x_gui_setup()
{
    bool ok = true;
    ok &= gfxstub_setup();
    ok &= openpanel_setup();
    ok &= savepanel_setup();
    return ok;
}
}
}
}  // namespace EA::Audio::Eapd
