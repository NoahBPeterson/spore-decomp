// EA::Audio::Eapd (EA's embedded Pure Data): g_editor / x_gui glue (0xa4c300-0xa4d310).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-. The Pd 0.4x sources (g_editor.c, x_gui.c, g_canvas.c)
// are the reference for names. Struct layouts are EA's: only the fields these functions touch are
// declared, at their binary offsets. Callees are masked relocations, declared with their
// cdecl signatures only.
#include "types.h"
#include <stdio.h>

namespace EA { namespace Audio { namespace Eapd {

// ---------------------------------------------------------------- Pd types
// t_symbol is passed by value as two words (name pointer, thing pointer).
struct t_symbol {
    void* s_name;
    void* s_thing;
};
struct t_class;
struct t_gobj;
struct t_glist;
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
struct t_class {
    char pad[0x3c];
    t_widgetbehavior* c_wb;   // +0x3c
};
struct t_gobj {
    t_class* g_pd;   // +0
    t_gobj* g_next;  // +4
};
struct t_selection {
    t_gobj* sel_what;   // +0
    t_selection* sel_next;   // +4
};
struct t_rtext;
struct t_binbuf;
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
struct t_object : t_gobj {
    char pad[0x1c - 8];
    unsigned te_type;   // +0x1c: low 2 bits are the object type (1 = T_OBJECT)
};
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
enum {
    GL_LOADING = 0x8,
    GL_GOPRECT = 0x80,
    GL_ISGRAPH = 0x100
};
struct t_linetraverser {
    t_glist* tr_x;      // +0
    t_object* tr_ob;    // +4
    int tr_nout;        // +8
    int tr_outno;       // +0xc
    t_object* tr_ob2;   // +0x10
    void* tr_outlet;    // +0x14
    void* tr_inlet;     // +0x18
    int tr_nin;         // +0x1c
    int tr_inno;        // +0x20
    char pad[0x5c - 0x24];
};
struct FontSpec {
    int fi_pointsize;
    int fi_width;
    int fi_height;
    int fi_c;
    int fi_d;
    int fi_e;
};
struct t_gfxstub {
    void* x_pd;           // +0
    unsigned x_owner;      // +4
    unsigned x_key;        // +8
    void* x_sym_a;        // +0xc
    void* x_sym_b;        // +0x10
    t_gfxstub* x_next;    // +0x14
};
struct t_savepanel {
    void* x_obj[10];
    void* x_s_a;   // +0x28
    void* x_s_b;   // +0x2c
};

// ---------------------------------------------------------------- externals
t_symbol* gensym(t_symbol* out, const char* s);
t_class* class_new(t_symbol name, void* newmethod, void* freemethod, int size, int flags, int a1, int a2);
t_class* class_new(t_symbol name, void* newmethod, void* freemethod, int size, int flags, int a1);
bool class_addbang(t_class* c, void* fn);
bool class_addsymbol(t_class* c, void* fn);
bool class_addanything(t_class* c, void* fn);
bool class_addmethod(t_class* c, void* fn, t_symbol name, int a1, int a2, int a3, int a4, int a5);
bool class_addmethod(t_class* c, void* fn, t_symbol name, int a1);
void* pd_new(t_class* c);
void pd_bind(void* x, t_symbol s);
void* outlet_new(void* x, t_symbol s);
void* inlet_new(void* x, void* dest, t_symbol s1, t_symbol s2);
void sys_gui(const char* fmt, ...);
void* getbytes(int n, const char* tag);
void freebytes(void* p, int n);
void binbuf_clear(t_binbuf* b);
void binbuf_addv(t_binbuf* b, const char* fmt, ...);
void binbuf_eval(t_binbuf* b, void* target, int argc, void* argv);
t_binbuf* binbuf_new();
void binbuf_free(t_binbuf* b);
void pd_pushsym(t_glist* x);
void pd_popsym(t_glist* x);
t_object* pd_checkobject(t_gobj* x);
int text_shouldvis(t_object* x, t_glist* glist);
int glist_isgraph(t_glist* x);
int glist_isvisible(t_glist* x);
t_glist* glist_getcanvas(t_glist* x);
void* glist_findrtext(t_glist* x, t_gobj* y);
void gobj_vis(t_glist* x, t_glist* glist, int flag);
void canvas_fixlinesfor(t_glist* x, t_gobj* y);
int canvas_getindex(t_glist* x, t_gobj* y);
void linetraverser_start(t_linetraverser* t, t_glist* x);
void* linetraverser_next(t_linetraverser* t);
void obj_disconnect(t_object* source, int outno, t_object* sink, int inno);
void* obj_connect(t_object* source, int outno, t_object* sink, int inno);
int obj_noutlets(t_object* x);   // 0xa4a0b0
int obj_ninlets(t_object* x);    // 0xa4a0d0
void glist_checkgraph(t_glist* x);   // 0xa4e560
double glist_dpixtody(t_glist* x, float f);   // 0xa4e2a0
double glist_dpixtodx(t_glist* x, float f);   // 0xa4e260
void rtext_gettext(void* rtext, char** buf, int* bufsize);   // 0xa4e9a0
void text_setto(t_gobj* x, t_glist* glist, char* buf, int bufsize);   // 0xa51510
void* openpanel_new();            // 0xa4c250
void openpanel_free(void* x);     // 0xa4c2e0
void openpanel_bang(void* x);     // 0xa4c2c0
void panel_symbol(void* x, void* s);   // 0xa5a140 (shared symbol method)
void gfxstub_anything(void* x);   // 0xa4c200
void gfxstub_free(void* x);       // 0xa4c230
void gfxstub_signoff(void* x);    // 0xa4c1f0
void gfxstub_cancel(void* x);     // 0xa4c1e0
void gfxstub_deleteforkey(void* key);   // 0xa4c170

// ---------------------------------------------------------------- globals
extern t_class* spOpenpanelClass;   // 0x1675498
extern t_class* spSavepanelClass;   // 0x167549c
extern t_gfxstub* gfxstub_list;     // 0x1675494
extern t_class* spGfxstubClass;     // 0x16754a0
extern t_class* gpCanvasClass;      // 0x1675490
extern t_class* gpTextClass;        // 0x16754f0
extern t_glist* canvas_last_glist;  // 0x16754a4
extern int canvas_last_glist_x;     // 0x16754c8
extern int canvas_last_glist_y;     // 0x16754cc
extern t_glist* canvas_undo_canvas;     // 0x16754b8
extern void (*canvas_undo_doit)(t_glist*, void*, int);   // 0x16754b0
extern void* canvas_undo_buf;           // 0x16754b4
extern const char* canvas_undo_name;    // 0x16754c0
extern int canvas_undo_whatnext;        // 0x16754c4
extern t_glist* canvas_whichfind;       // 0x16754ac
extern int canvas_apply_offset;         // 0x16754bc
extern t_binbuf* copy_binbuf;           // 0x16754d0
extern int canvas_cursorcanvas_unused;
extern t_glist* canvas_cursor_glist;    // 0x16754d8
extern unsigned canvas_cursor_index;    // 0x16754d4
extern int glist_deselecting;           // 0x16754dc
extern const char* cursorlist[7];       // 0x1554290
extern FontSpec sys_fontspec[6];        // 0x15542b8
extern t_symbol gEmptySymbol;           // 0x167589c
extern t_symbol gSymbolSymbol;          // 0x1675894

// 0xa4c300
bool openpanel_setup() {
    t_symbol tmp;
    t_symbol* s = gensym(&tmp, "openpanel");
    spOpenpanelClass = class_new(*s, (void*)openpanel_new, (void*)openpanel_free, 0x30, 0, 5, 0);
    bool ok = true;
    ok &= spOpenpanelClass != 0;
    ok &= class_addbang(spOpenpanelClass, (void*)openpanel_bang);
    ok &= class_addsymbol(spOpenpanelClass, (void*)panel_symbol);
    return ok;
}

void* savepanel_new();
void savepanel_bang(t_savepanel* x);

// 0xa4c370
void* savepanel_new() {
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

// 0xa4c3e0
void savepanel_bang(t_savepanel* x) {
    sys_gui("pdtk_savepanel %s\n", x->x_s_b);
}

// 0xa4c400
bool savepanel_setup() {
    t_symbol tmp;
    t_symbol* s = gensym(&tmp, "savepanel");
    spSavepanelClass = class_new(*s, (void*)savepanel_new, (void*)openpanel_free, 0x30, 0, 5, 0);
    bool ok = true;
    ok &= spSavepanelClass != 0;
    ok &= class_addbang(spSavepanelClass, (void*)savepanel_bang);
    ok &= class_addsymbol(spSavepanelClass, (void*)panel_symbol);
    return ok;
}

// 0xa4c470
void gfxstub_new(t_gobj* owner, void* key, const char* cmd) {
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

// 0xa4c560
bool gfxstub_setup() {
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

// 0xa4c610 (EA::Audio::Eapd::x_gui_setup)
bool x_gui_setup() {
    bool ok = true;
    ok &= gfxstub_setup();
    ok &= openpanel_setup();
    ok &= savepanel_setup();
    return ok;
}

// 0xa4c630
void gobj_getrect(t_gobj* x, t_glist* glist, int* x1, int* y1, int* x2, int* y2) {
    if (x->g_pd->c_wb && x->g_pd->c_wb->w_getrectfn)
        x->g_pd->c_wb->w_getrectfn(x, glist, x1, y1, x2, y2);
}

// 0xa4c6f0
int gobj_click(t_gobj* x, t_glist* glist, int xpos, int ypos, int shift, int alt, int dbl, int doit) {
    t_widgetbehavior* wb = x->g_pd->c_wb;
    if (wb && wb->w_clickfn) return wb->w_clickfn(x, glist, xpos, ypos, shift, alt, dbl, doit);
    return 0;
}

// 0xa4c710 (EA::Audio::Eapd::glist_isselected)
int glist_isselected(t_glist* x, t_gobj* y) {
    if (x->gl_editor) {
        for (t_selection* sel = x->gl_editor->e_selection; sel; sel = sel->sel_next)
            if (sel->sel_what == y) return 1;
    }
    return 0;
}

// 0xa4c740
void glist_select(t_glist* x, t_gobj* y) {
    if (x->gl_editor) {
        t_selection* sel = (t_selection*)getbytes(8, "EAPd/t_selection");
        if ((x->gl_editor->e_flags & 0x20) && x->gl_editor) {
            x->gl_editor->e_flags &= ~0x20u;
            sys_gui(".x%lx.c itemconfigure l%lx -fill black\n", x, x->gl_editor->e_selectline_tag);
        }
        if (x->gl_editor) {
            t_selection* s;
            for (s = x->gl_editor->e_selection; s && s->sel_what != y; s = s->sel_next) {}
        }
        sel->sel_next = x->gl_editor->e_selection;
        sel->sel_what = y;
        x->gl_editor->e_selection = sel;
        t_widgetbehavior* wb = y->g_pd->c_wb;
        if (wb && wb->w_selectfn) wb->w_selectfn(y, x, 1);
    }
}

// 0xa4c7e0
void canvas_noundo(t_glist* x) {
    if (!x || x == canvas_undo_canvas) {
        int had = 0;
        if (canvas_undo_doit && canvas_undo_buf) {
            canvas_undo_doit(canvas_undo_canvas, canvas_undo_buf, 0);
            had = 1;
        }
        canvas_undo_canvas = 0;
        canvas_undo_doit = 0;
        canvas_undo_buf = 0;
        canvas_undo_whatnext = 1;
        canvas_undo_name = "foo";
        if (had) sys_gui("pdtk_undomenu nobody no no\n");
    }
}

// 0xa4c860
void canvas_disconnect(t_glist* x, float index1, float outno, float index2, float inno) {
    t_linetraverser t;
    linetraverser_start(&t, x);
    void* oc = linetraverser_next(&t);
    if (oc) {
        for (;;) {
            int a = canvas_getindex(x, t.tr_ob);
            int b = canvas_getindex(x, t.tr_ob2);
            if ((float)a == index1 && (float)t.tr_outno == outno && (float)b == index2 &&
                (float)t.tr_inno == inno)
                break;
            oc = linetraverser_next(&t);
            if (!oc) return;
        }
        sys_gui(".x%lx.c delete l%lx\n", x, oc);
        obj_disconnect(t.tr_ob, t.tr_outno, t.tr_ob2, t.tr_inno);
    }
}

// 0xa4c940
void canvas_setcursor(t_glist* x, unsigned cursornum) {
    if (cursornum < 7 && (canvas_cursor_glist != x || canvas_cursor_index != cursornum)) {
        sys_gui(".x%lx configure -cursor %s\n", x, cursorlist[cursornum]);
        canvas_cursor_glist = x;
        canvas_cursor_index = cursornum;
    }
}

// 0xa4c990
int canvas_hitbox(t_glist* x, t_gobj* y, int xpos, int ypos, int* x1p, int* y1p, int* x2p, int* y2p) {
    int x1, y1, x2, y2;
    t_object* ob = pd_checkobject(y);
    if (ob && !text_shouldvis(ob, x)) return 0;
    if (y->g_pd->c_wb && y->g_pd->c_wb->w_getrectfn)
        y->g_pd->c_wb->w_getrectfn(y, x, &x1, &y1, &x2, &y2);
    if (xpos >= x1 && xpos <= x2 && ypos >= y1 && ypos <= y2) {
        *x1p = x1;
        *y1p = y1;
        *x2p = x2;
        *y2p = y2;
        return 1;
    }
    return 0;
}

// 0xa4ca40 (EA::Audio::Eapd::canvas_setgraph)
void canvas_setgraph(t_glist* x, int flag) {
    int isgraph = glist_isgraph(x);
    if (!flag) {
        if (!isgraph) return;
        if (x->gl_owner && !(x->gl_flags & GL_LOADING) && glist_isvisible(x->gl_owner))
            gobj_vis(x, x->gl_owner, 0);
        x->gl_flags &= ~GL_ISGRAPH;
        if (x->gl_owner && !(x->gl_flags & GL_LOADING) && glist_isvisible(x->gl_owner)) {
            gobj_vis(x, x->gl_owner, 1);
            canvas_fixlinesfor(x->gl_owner, x);
        }
    } else {
        if (isgraph) return;
        if (x->gl_pixwidth <= 0) x->gl_pixwidth = 200;
        if (x->gl_pixheight <= 0) x->gl_pixheight = 140;
        if (x->gl_owner && !(x->gl_flags & GL_LOADING) && glist_isvisible(x->gl_owner))
            gobj_vis(x, x->gl_owner, 0);
        x->gl_flags |= GL_ISGRAPH | GL_GOPRECT;
        if (glist_isvisible(x) && (x->gl_flags & GL_GOPRECT)) glist_checkgraph(x);
        if (x->gl_owner && !(x->gl_flags & GL_LOADING) && glist_isvisible(x->gl_owner)) {
            gobj_vis(x, x->gl_owner, 1);
            canvas_fixlinesfor(x->gl_owner, x);
        }
    }
}

// 0xa4cb50
void canvas_properties(t_glist* x) {
    char buf[200];
    if (glist_isgraph(x)) {
        sprintf(buf, "pdtk_canvas_dialog %%s %g %g %d %g %g %g %g %d %d %d %d\n", 0.0, 0.0, 1,
                x->gl_x1, x->gl_y1, x->gl_x2, x->gl_y2, x->gl_pixwidth,
                x->gl_pixheight, x->gl_xmargin, x->gl_ymargin);
    } else {
        sprintf(buf, "pdtk_canvas_dialog %%s %g %g %d %g %g %g %g %d %d %d %d\n", glist_dpixtodx(x, 1.0f),
                -glist_dpixtody(x, 1.0f), 0, 0.0, -1.0, 1.0, 1.0, x->gl_pixwidth, x->gl_pixheight,
                x->gl_xmargin, x->gl_ymargin);
    }
    gfxstub_new(x, x, buf);
}

inline int glist_getindex(t_glist* x, t_gobj* y) {
    int indx = 0;
    for (t_gobj* g = x->gl_list; g && g != y; g = g->g_next) indx++;
    return indx;
}

// 0xa4cc30
void canvas_stowconnections(t_glist* x) {
    t_gobj* selhead = 0;
    t_gobj* seltail = 0;
    t_gobj* nonhead = 0;
    t_gobj* nontail = 0;
    if (!x->gl_editor) return;
    t_gobj* y2;
    for (t_gobj* y = x->gl_list; y; y = y2) {
        y2 = y->g_next;
        if (glist_isselected(x, y)) {
            if (seltail) {
                seltail->g_next = y;
                seltail = y;
                y->g_next = 0;
            } else {
                selhead = seltail = y;
                y->g_next = 0;
            }
        } else {
            if (nontail) {
                nontail->g_next = y;
                nontail = y;
                y->g_next = 0;
            } else {
                nonhead = nontail = y;
                y->g_next = 0;
            }
        }
    }
    if (!nonhead) {
        x->gl_list = selhead;
    } else {
        x->gl_list = nonhead;
        nontail->g_next = selhead;
    }
    binbuf_clear(x->gl_editor->e_connectbuf);
    t_linetraverser t;
    linetraverser_start(&t, x);
    void* oc;
    while ((oc = linetraverser_next(&t)) != 0) {
        int s1 = glist_isselected(x, t.tr_ob);
        int s2 = glist_isselected(x, t.tr_ob2);
        if (s1 != s2) {
            t_symbol tmp1, tmp2;
            binbuf_addv(x->gl_editor->e_connectbuf, "ssiiii;", *gensym(&tmp2, "#X"), *gensym(&tmp1, "connect"),
                        glist_getindex(x, t.tr_ob), t.tr_outno, glist_getindex(x, t.tr_ob2), t.tr_inno);
        }
    }
}

// 0xa4ce00
void canvas_restoreconnections(t_glist* x) {
    pd_pushsym(x);
    binbuf_eval(x->gl_editor->e_connectbuf, 0, 0, 0);
    pd_popsym(x);
}

// 0xa4ce30 (EA::Audio::Eapd::canvas_connect)
void canvas_connect(t_glist* x, float fwhoout, float foutno, float fwhoin, float finno) {
    int whoout = (int)fwhoout;
    int whoin = (int)fwhoin;
    if (canvas_whichfind == x) {
        whoout += canvas_apply_offset;
        whoin += canvas_apply_offset;
    }
    t_gobj* sink = x->gl_list;
    t_gobj* src = sink;
    for (; whoout; src = src->g_next, whoout--)
        if (!src->g_next) return;
    for (; whoin; sink = sink->g_next, whoin--)
        if (!sink->g_next) return;
    t_object* objsrc = pd_checkobject(src);
    if (!objsrc) return;
    t_object* objsink = pd_checkobject(sink);
    if (!objsink) return;
    // if object creation failed, make dummy inlets or outlets as needed
    if (src->g_pd == gpTextClass && (objsrc->te_type & 3) == 1)
        while ((int)foutno >= obj_noutlets(objsrc)) outlet_new(objsrc, gEmptySymbol);
    if (sink->g_pd == gpTextClass && (objsink->te_type & 3) == 1)
        while ((int)finno >= obj_ninlets(objsink)) inlet_new(objsink, objsink, gEmptySymbol, gEmptySymbol);
    void* oc = obj_connect(objsrc, (int)foutno, objsink, (int)finno);
    if (oc && glist_isvisible(x)) {
        sys_gui(".x%lx.c create line %d %d %d %d -width %d -tags l%lx\n", glist_getcanvas(x), 0, 0, 0, 0, 1, oc);
        canvas_fixlinesfor(x, objsrc);
    }
}

// 0xa4cfb0 (EA::Audio::Eapd::canvas_howputnew helper: last click position for glist x)
bool canvas_getlastxy(t_glist* x, int* xp, int* yp) {
    bool ok = false;
    if (canvas_last_glist == x) {
        *xp = canvas_last_glist_x;
        *yp = canvas_last_glist_y;
        ok = true;
    } else {
        *yp = 0;
        *xp = 0;
    }
    return ok;
}

// 0xa4cff0
bool g_editor_setup() {
    t_symbol tmp;
    t_symbol* s = gensym(&tmp, "connect");
    bool ok = true;
    ok &= class_addmethod(gpCanvasClass, (void*)canvas_connect, *s, 1, 1, 1, 1, 0);
    s = gensym(&tmp, "disconnect");
    ok &= class_addmethod(gpCanvasClass, (void*)canvas_disconnect, *s, 1, 1, 1, 1, 0);
    copy_binbuf = binbuf_new();
    return ok;
}

// 0xa4d070
bool g_editor_free() {
    binbuf_free(copy_binbuf);
    return true;
}

// 0xa4d090 (EA::Audio::Eapd::glist_deselect)
void glist_deselect(t_glist* x, t_gobj* y) {
    if (glist_deselecting) return;
    glist_deselecting = 1;
    if (x->gl_editor) {
        t_rtext* z = 0;
        if (x->gl_editor->e_textedfor) {
            t_rtext* fuddy = (t_rtext*)glist_findrtext(x, y);
            if (x->gl_editor->e_textedfor == fuddy) {
                if (x->gl_editor->e_flags & 0x10) {
                    z = fuddy;
                    canvas_stowconnections(glist_getcanvas(x));
                }
                t_widgetbehavior* wb = y->g_pd->c_wb;
                if (wb && wb->w_activatefn) wb->w_activatefn(y, x, 0);
            }
        }
        t_selection* sel2 = x->gl_editor->e_selection;
        if (sel2->sel_what == y) {
            x->gl_editor->e_selection = x->gl_editor->e_selection->sel_next;
        } else {
            t_selection* prev;
            for (;;) {
                prev = sel2;
                sel2 = sel2->sel_next;
                if (!sel2) goto done;
                if (sel2->sel_what == y) {
                    prev->sel_next = sel2->sel_next;
                    break;
                }
            }
        }
        {
            t_widgetbehavior* wb = sel2->sel_what->g_pd->c_wb;
            if (wb && wb->w_selectfn) wb->w_selectfn(sel2->sel_what, x, 0);
            freebytes(sel2, 8);
        }
    done:
        if (z) {
            char* buf;
            int bufsize;
            rtext_gettext(z, &buf, &bufsize);
            text_setto(y, x, buf, bufsize);
            canvas_fixlinesfor(glist_getcanvas(x), y);
            x->gl_editor->e_textedfor = 0;
        }
    }
    glist_deselecting = 0;
}

// 0xa4d1d0
void glist_noselect(t_glist* x) {
    if (x->gl_editor) {
        while (x->gl_editor->e_selection) glist_deselect(x, x->gl_editor->e_selection->sel_what);
        if ((x->gl_editor->e_flags & 0x20) && x->gl_editor) {
            x->gl_editor->e_flags &= ~0x20u;
            sys_gui(".x%lx.c itemconfigure l%lx -fill black\n", x, x->gl_editor->e_selectline_tag);
        }
    }
}

// 0xa4d230
void canvas_startmotion(t_glist* x) {
    int xval, yval;
    if (!x->gl_editor) return;
    if (canvas_last_glist == x) {
        xval = canvas_last_glist_x;
        yval = canvas_last_glist_y;
    } else {
        xval = 0;
        yval = 0;
    }
    if (xval == 0 && yval == 0) return;
    x->gl_editor->e_flags = (x->gl_editor->e_flags & ~6u) | 1;
    x->gl_editor->e_xwas = xval;
    x->gl_editor->e_ywas = yval;
}

// Font table lookups: fields of the entry whose size range contains `fontsize`.
#define FONT_LOOKUP(name, field)                              \
    int name(int fontsize) {                                  \
        unsigned w = 0;                                       \
        FontSpec* p = sys_fontspec;                           \
        do {                                                  \
            if (fontsize < p[1].fi_pointsize) goto found;     \
            w++;                                              \
            p++;                                              \
        } while (w < 5);                                      \
        p = &sys_fontspec[5];                                 \
    found:                                                    \
        return p->field;                                      \
    }

// 0xa4d280
FONT_LOOKUP(sys_nearestfontsize, fi_pointsize)
// 0xa4d2b0
FONT_LOOKUP(sys_fontwidth, fi_c)
// 0xa4d2e0
FONT_LOOKUP(sys_fontheight, fi_d)
// 0xa4d310
FONT_LOOKUP(sys_fontextra, fi_e)

}}}
