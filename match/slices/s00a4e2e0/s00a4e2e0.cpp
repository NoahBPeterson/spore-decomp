// Slice s00a4e2e0: EA::Audio::Eapd (EA's embedded Pure Data 0.4x) text (g_text.c),
// graph object glue (g_graph.c) and guiconnect (g_guiconnect.c).
//
// Original: SporeApp.exe, MSVC 2008 SP1, x86 (32-bit).
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
//
// The module is C-style: every function is a plain __cdecl function that takes
// the object as its first parameter.  Layouts (t_gtext/t_glist/t_gobj/t_editor/
// t_rtext) come from the sibling slices s00a4c300 / s00a4d340 / s00a510e0 and
// match the offsets this disassembly touches.
#include "types.h"
#include <stdio.h>
#include <string.h>

namespace EA { namespace Audio { namespace Eapd {

struct t_class;
struct t_binbuf;
struct t_gobj;
struct t_glist;
struct t_rtext;
struct t_atom;
struct t_symbol;

// t_symbol is a by-value pair: symbol hash, name pointer.
struct t_symbol {
    uint32_t    s_hash;    // +0
    void*       s_name;    // +4
};

struct t_atom {
    int      a_type;
    t_symbol a_w;
};

struct t_editor {
    uint32_t     pad00[3];
    t_rtext*     e_rtextlist;    // +0x0c  list of live t_rtext items
    uint32_t     pad10;
    t_rtext*     e_textedfor;    // +0x14
    uint32_t     pad18[14];
    unsigned     e_flags;        // +0x50: bit 0x10 = textdirty
};

struct t_gobj {
    t_class* g_pd;      // +0x00
    t_gobj*  g_next;    // +0x04
};

// t_text (t_object), extended with the fields g_text.c uses.
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

// t_glist, followed by the graph extension (graph objects are t_glist-derived).
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

enum { GL_GOPRECT = 0x01, GL_ISGRAPH = 0x100 };

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

struct t_guiconnect {
    t_class*  gc_pd;        // +0x00
    uint32_t  pad04[9];
    t_glist*  gc_target;    // +0x28
    t_symbol  gc_symA;      // +0x2c  (hash, name)
    t_guiconnect* gc_prev;  // +0x34
    t_guiconnect* gc_next;  // +0x38
};

struct t_linetraverser {
    uint32_t pad00[0x44 / 4];
    int      tr_lx1;        // +0x44
    int      tr_ly1;        // +0x48
    int      tr_lx2;        // +0x4c
    int      tr_ly2;        // +0x50
    uint32_t pad54[2];      // +0x54
};

// ---------------------------------------------------------------- globals
extern t_class*        spGuiconnectClass;   // 0x16754e8
extern t_guiconnect*   guiconnectlist;      // 0x16754e4
extern t_rtext*        rtext_entered;       // 0x16754ec
extern t_symbol        gEmptySymbol;        // 0x167589c
extern t_glist*        gpEditingCanvas;     // 0x1675470
extern t_class*        gpCanvasClass;       // 0x1675490

// The class's widget behaviour, holding the inherited g_text.c entry points.
extern int g_text_widgetbehavior[];  // 0x1554364

// ---------------------------------------------------------------- externals
t_symbol* gensym(t_symbol* out, const char* s);                        // 0xa675f0
t_class*  class_new(t_symbol name, void* newmethod, void* freemethod,
                    int size, int flags, int a1);                      // 0xa48e50
bool      class_addanything(t_class* c, void* fn);                     // 0xa47f90
bool      class_addmethod(t_class* c, void* fn, t_symbol name, void* a1); // 0xa48a30
void*     pd_new(t_class* c);                                          // 0xa49390
void*     pd_findbyclass(uint32_t a, void* b, t_class* c);             // 0xa671f0
void      pd_bind(void* x, t_symbol s);                                // 0xa67620
void      pd_free(void* x);                                            // 0xa493d0
void      pd_typedmess(void* x, t_symbol s, int argc, t_atom* argv);   // 0xa48100
void*     getbytes(int n, const char* tag);                            // 0xa49610
void      freebytes(void* p, int n);                                   // 0xa49650
void      sys_vgui(unsigned int a, unsigned int b, unsigned int c);     // 0xa671b0
void      binbuf_gettext(t_binbuf* b, void* a, void* c);               // 0xa47080
t_glist*  glist_getcanvas(t_glist* x);                                 // 0xa4d410
int       glist_isvisible(t_glist* x);                                 // 0xa4ab40
int       glist_istoplevel(t_glist* x);                                // 0xa4ab70
int       canvas_showtext(t_glist* x);                                 // 0xa4add0
void      canvas_create_editor(t_glist* x, int flag);                  // 0xa4aac0
void      canvas_drawredrect(t_glist* x, int doit);                    // 0xa4a9a0
void      canvas_fixlinesfor(t_glist* parent, t_gobj* x);              // 0xa4b1c0
void      glist_delete(t_glist* x, t_gobj* y);                         // 0xa4de50
void      gobj_vis(t_gobj* x, t_glist* parent, int flag);              // 0xa4c6d0
void      gobj_getrect(t_gobj* x, t_glist* g, int*, int*, int*, int*); // 0xa4c630
void      graph_getrect(t_gobj* x, t_glist* g, int*, int*, int*, int*); // 0xa4daf0
void      graph_graphrect(t_gobj* x, t_glist* g, int*, int*, int*, int*); // 0xa4da60
void      linetraverser_start(t_linetraverser* tr, t_glist* x);        // 0xa4a640
t_gobj*   linetraverser_next(t_linetraverser* tr);                     // 0xa4af60
void      glist_eraseiofor(t_glist* x, t_text* o, const char* tag);    // 0xa51450
void      glist_drawiofor(t_glist* x, t_text* o, int firsttime,
                          const char* tag, int x1, int y1, int x2, int y2); // 0xa510e0
void      SetSerializer(const char* fmt, ...);                         // 0xc2e4e0
int*      glist_isselected(t_glist* x, t_gobj* y);                      // 0xa4c710
int       glist_getfont(t_glist* x);                                    // 0xa4ab90
int       sys_fontwidth(int font);                                      // 0xa4d2e0
int       sys_fontheight(int font);                                     // 0xa4d310
int       sys_fontweight(int font, const char* color);                  // 0xa4d2b0
int       text_xpix(t_text* x, t_glist* g);                             // 0xa4d920
int       text_ypix(t_text* x, t_glist* g);                             // 0xa4d9c0
void      text_drawborder(t_text* x, t_glist* g, const char* tag,
                          int w, int h, int firsttime);                 // 0xa51240
void*     resizebytes(void* p, int oldsz, int newsz, const char* tag);   // 0xa49670
int*      binbuf_getvec(t_binbuf* b);                                   // 0x011922c0
int       binbuf_getnatom(t_binbuf* b);                                 // 0x011838a0

// -------------------------------------------------------------------------
// Helpers: the graph widget keeps its own flag word and canvas at +0x78/+0x2c
// of the graph object (which is itself a t_glist).
// -------------------------------------------------------------------------
static inline t_glist* glist_canvas(t_gobj* x)
{
    return ((t_text*)x)->te_glist;   // +0x28
}

static inline uint32_t gobj_flags(t_gobj* x)
{
    return ((t_glist*)x)->gl_flags;  // +0x78
}

// -------------------------------------------------------------------------
// Forward declarations in call order.
// -------------------------------------------------------------------------
void graph_objvis(t_gobj* z, int flag);                                  // 0xa4e2e0
void graph_vis(t_gobj* x, t_glist* glist, int selected);                 // 0xa4e390
void graph_delete(t_glist* x, t_glist* glist);                           // 0xa4e520
void glist_redraw(t_glist* x);                                           // 0xa4e560
void graph_displace(t_gobj* x, t_glist* glist, int dx, int dy);          // 0xa4e660
void* guiconnect_new(t_glist* target, t_symbol s);                     // 0xa4e6c0
void guiconnect_unlink(void* x);                                         // 0xa4e750
void guiconnect_notarget(t_guiconnect* gc);                              // 0xa4e780
void guiconnect_signoff(t_guiconnect* gc);                               // 0xa4e7a0
void guiconnect_anything(t_guiconnect* gc, t_symbol s, int argc, t_atom* argv); // 0xa4e7e0
char g_guiconnect_setup();                                               // 0xa4e810
t_rtext* rtext_new(t_glist* x, t_text* ob);                              // 0xa4e8a0
void rtext_free(t_rtext* x);                                             // 0xa4e920
const char* rtext_gettag(t_rtext* x);                                    // 0xa4e990
void rtext_senditup(t_rtext* x, int action, int* pWidth, int* pHeight,
                    int* pCursor);                                        // 0xa4e9c0
void rtext_retext(t_rtext* x);                                           // 0xa4ee20
__declspec(noinline)
t_rtext* glist_findrtext(t_glist* x, t_text* y);                         // 0xa4efb0
int rtext_width(t_rtext* x);                                             // 0xa4efd0
int rtext_height(t_rtext* x);                                            // 0xa4f010
void rtext_draw(t_rtext* x);                                             // 0xa4f050
void rtext_erase(t_rtext* x);                                            // 0xa4f080
void rtext_displace(t_rtext* x, int dx, int dy);                         // 0xa4f0b0
void rtext_select(t_rtext* x, int state);                                // 0xa4f0e0
void rtext_activate(t_rtext* x, int state);                              // 0xa4f130

// =========================================================================
// 0x00A4E2E0  EA::Audio::Eapd::graph_objvis
// -------------------------------------------------------------------------
// Draws the "graph on parent" rectangle: every sub-object that falls inside
// the graph's rect gets its own dotted outline.
// =========================================================================
// @ 0x00a4e2e0
void graph_objvis(t_gobj* z, int flag)
{
    t_glist* x = (t_glist*)z;
    int gx1, gy1, gx2, gy2;
    int x1, y1, x2, y2;

    graph_graphrect(z, x->gl_owner, &gx1, &gy1, &gx2, &gy2);
    for (t_gobj* y = x->gl_list; y; y = y->g_next) {
        gobj_getrect(y, x->gl_owner, &x1, &y1, &x2, &y2);
        if (x1 >= gx1 && x1 <= gx2 && x2 >= gx1 && x2 <= gx2 &&
            y1 >= gy1 && y1 <= gy2 && y2 >= gy1 && y2 <= gy2)
            gobj_vis(y, x->gl_owner, flag);
    }
}

// =========================================================================
// 0x00A4E390  EA::Audio::Eapd::graph_vis
// =========================================================================
// @ 0x00a4e390
void graph_vis(t_gobj* z, t_glist* glist, int vis)
{
    t_glist* x = (t_glist*)z;
    char tag[52];
    int x1, y1, x2, y2;

    if (!(x->gl_flags & GL_ISGRAPH)) {
        ((void (*)(t_gobj*, t_glist*, int))g_text_widgetbehavior[5])(z, glist, vis);
        return;
    }
    sprintf(tag, "graph%lx", x);
    if (vis == 0) {
        rtext_erase(glist_findrtext(glist, (t_text*)z));
        glist_eraseiofor(glist, (t_text*)z, tag);
        SetSerializer(".x%lx.c delete %s\n", glist_getcanvas(x->gl_owner), tag);
        if (!(x->gl_flags & GL_GOPRECT)) {
            graph_objvis(z, 0);
            canvas_create_editor(x, 0);
            return;
        }
    } else {
        graph_getrect(z, glist, &x1, &y1, &x2, &y2);
        if (!(x->gl_flags & GL_GOPRECT)) {
            SetSerializer(".x%lx.c create polygon %d %d %d %d %d %d %d %d %d %d"
                          " -tags %s -fill white -outline black \n",
                          glist_getcanvas(x->gl_owner),
                          x1, y1, x1, y2, x2, y2, x2, y1, x1, y1, tag);
            canvas_create_editor(x, 1);
            graph_objvis(z, 1);
        } else {
            SetSerializer(".x%lx.c create polygon %d %d %d %d %d %d %d %d %d %d"
                          " -tags %s -fill gray -outline black \n",
                          glist_getcanvas(x->gl_owner),
                          x1, y1, x1, y2, x2, y2, x2, y1, x1, y1, tag);
        }
        if (canvas_showtext(x))
            rtext_draw(glist_findrtext(glist, (t_text*)z));
        glist_drawiofor(glist, (t_text*)z, 1, tag, x1, y1, x2, y2);
    }
}

// =========================================================================
// 0x00A4E520  EA::Audio::Eapd::graph_delete
// =========================================================================
// @ 0x00a4e520
void graph_delete(t_glist* x, t_glist* glist)
{
    ((void (*)(t_glist*, t_glist*))g_text_widgetbehavior[4])(x, glist);
    while (x->gl_list)
        glist_delete(x, x->gl_list);
}

// =========================================================================
// 0x00A4E560  EA::Audio::Eapd::glist_redraw
// =========================================================================
// @ 0x00a4e560
void glist_redraw(t_glist* x)
{
    t_linetraverser t;

    if (!glist_isvisible(x))
        return;
    if (glist_istoplevel(x)) {
        for (t_gobj* y = x->gl_list; y; y = y->g_next) {
            gobj_vis(y, x, 0);
            gobj_vis(y, x, 1);
        }
        linetraverser_start(&t, x);
        for (t_gobj* y = linetraverser_next(&t); y; y = linetraverser_next(&t))
            SetSerializer(".x%lx.c coords l%lx %d %d %d %d\n", glist_getcanvas(x), y,
                          t.tr_lx1, t.tr_ly1, t.tr_lx2, t.tr_ly2);
        canvas_drawredrect(x, 0);
        if (x->gl_flags & 0x80)
            canvas_drawredrect(x, 1);
    }
    if (x->gl_owner && glist_isvisible(x->gl_owner)) {
        graph_vis((t_gobj*)x, x->gl_owner, 0);
        graph_vis((t_gobj*)x, x->gl_owner, 1);
    }
}

// =========================================================================
// 0x00A4E660  EA::Audio::Eapd::graph_displace
// =========================================================================
// @ 0x00a4e660
void graph_displace(t_gobj* x, t_glist* glist, int dx, int dy)
{
    if (!(gobj_flags(x) & GL_ISGRAPH)) {
        ((void (*)(t_gobj*, t_glist*, int, int))g_text_widgetbehavior[1])(x, glist, dx, dy);
        return;
    }
    t_text* t = (t_text*)x;
    t->te_xpix = (int16_t)(t->te_xpix + (int16_t)dx);
    t->te_ypix = (int16_t)(t->te_ypix + (int16_t)dy);
    glist_redraw((t_glist*)x);
    canvas_fixlinesfor(glist_getcanvas(glist), x);
}

// =========================================================================
// 0x00A4E6C0  EA::Audio::Eapd::guiconnect_new
// =========================================================================
// @ 0x00a4e6c0
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

// =========================================================================
// 0x00A4E750  guiconnect_listunlink (class free method)
// =========================================================================
// @ 0x00a4e750
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

// =========================================================================
// 0x00A4E780  EA::Audio::Eapd::guiconnect_notarget
// =========================================================================
// @ 0x00a4e780
void guiconnect_notarget(t_guiconnect* gc)
{
    gc->gc_target = 0;
    if (gc->gc_symA.s_hash == gEmptySymbol.s_hash)
        pd_free(gc);
}

// =========================================================================
// 0x00A4E7A0  EA::Audio::Eapd::guiconnect_signoff
// =========================================================================
// @ 0x00a4e7a0
void guiconnect_signoff(t_guiconnect* gc)
{
    if (gc->gc_target == 0) {
        sys_vgui((unsigned)(size_t)gc, gc->gc_symA.s_hash, (unsigned)(size_t)gc->gc_symA.s_name);
        gc->gc_symA = gEmptySymbol;
        pd_free(gc);
    }
}

// =========================================================================
// 0x00A4E7E0  guiconnect_anything
// =========================================================================
// @ 0x00a4e7e0
void guiconnect_anything(t_guiconnect* gc, t_symbol s, int argc, t_atom* argv)
{
    if (gc->gc_target)
        pd_typedmess(gc->gc_target, s, argc, argv);
}

// =========================================================================
// 0x00A4E810  EA::Audio::Eapd::g_guiconnect_setup
// =========================================================================
// @ 0x00a4e810
char g_guiconnect_setup()
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

// =========================================================================
// 0x00A4E8A0  EA::Audio::Eapd::rtext_new
// =========================================================================
// @ 0x00a4e8a0
t_rtext* rtext_new(t_glist* x, t_text* ob)
{
    t_rtext* rt = (t_rtext*)getbytes(100, "EAPd/t_rtext");
    t_rtext* next;

    rt->rt_ypix = -1;
    rt->rt_owner = ob;
    rt->rt_glist = x;
    next = x->gl_editor->e_rtextlist;
    rt->rt_height = 0;
    rt->rt_width = 0;
    rt->rt_active = 0;
    rt->rt_selectto = 0;
    rt->rt_selectfrom = 0;
    rt->rt_next = next;
    binbuf_gettext(ob->te_binbuf, &rt->rt_buf, &rt->rt_bufsize);
    x->gl_editor->e_rtextlist = rt;
    sprintf(rt->rt_tag, ".x%lx.t%lx", (unsigned)(size_t)glist_getcanvas(rt->rt_glist),
            (unsigned)(size_t)rt);
    return rt;
}

// =========================================================================
// 0x00A4E920  EA::Audio::Eapd::rtext_free
// =========================================================================
// @ 0x00a4e920
void rtext_free(t_rtext* x)
{
    if (x->rt_glist->gl_editor->e_textedfor == x)
        x->rt_glist->gl_editor->e_textedfor = 0;
    if (x->rt_glist->gl_editor->e_rtextlist == x) {
        x->rt_glist->gl_editor->e_rtextlist = x->rt_next;
    } else {
        t_rtext* o = x->rt_glist->gl_editor->e_rtextlist;
        while (o && o->rt_next != x)
            o = o->rt_next;
        if (o)
            o->rt_next = x->rt_next;
    }
    if (rtext_entered == x)
        rtext_entered = 0;
    freebytes(x->rt_buf, x->rt_bufsize);
    freebytes(x, 100);
}

// =========================================================================
// 0x00A4E990  EA::Audio::Eapd::rtext_gettag
// =========================================================================
// @ 0x00a4e990
const char* rtext_gettag(t_rtext* x)
{
    return x->rt_tag;
}

// =========================================================================
// 0x00A4E9A0  small helper: copy a width/height pair out of the scratch block
// =========================================================================
// @ 0x00a4e9a0
void rtext_measures(int* pIn, int* pA, int* pB)
{
    *pA = pIn[0];
    *pB = pIn[1];
}

// =========================================================================
// 0x00A4E9C0  EA::Audio::Eapd::rtext_senditup
// -------------------------------------------------------------------------
// Lays the text out into lines (honouring the object's wrap width), then
// sends it to Tk.  action 0 = measure only, 1 = draw, 2 = draw and update
// the selection/caret.  widthp/heightp are in/out: they carry the current
// caret position in and the computed box size out.
// =========================================================================
// @ 0x00a4e9c0
void rtext_senditup(t_rtext* x, int action, int* widthp, int* heightp, int* cursorp)
{
    int nleft = 0;          // characters written to the flattened buffer
    int nlines = 0;         // lines emitted so far
    int maxline = 0;        // widest line, in characters
    int selstart = 0;       // selection start, in flattened-buffer chars
    int selend = 0;         // selection end, in flattened-buffer chars
    int wrapwidth = (short)x->rt_owner->te_width;
    int font, fontwidth, fontheight;
    int xpos, ypos;
    int newwidth, newheight;
    char smallbuf[200];
    char* buf;
    t_glist* canvas = glist_getcanvas(x->rt_glist);
    t_text* ob = x->rt_owner;

    if (wrapwidth == 0)
        wrapwidth = 60;
    if (ob->g_pd == gpCanvasClass &&
        (((t_glist*)ob)->gl_flags & GL_ISGRAPH) &&
        (((t_glist*)ob)->gl_flags & 0x80))
        font = glist_getfont((t_glist*)ob);
    else
        font = glist_getfont(x->rt_glist);
    fontwidth = sys_fontwidth(font);
    fontheight = sys_fontheight(font);

    int wrapcol = (fontwidth / 2 + *widthp) / fontwidth;
    int cursorline = *heightp / fontheight;

    if (x->rt_bufsize < 100)
        buf = smallbuf;
    else
        buf = (char*)getbytes(x->rt_bufsize * 2 + 1, "EAPd/char");

    if (x->rt_bufsize > 0) {
        int i = 0;
        int hit = 0;
        while (i < x->rt_bufsize) {
            int remaining = x->rt_bufsize - i;
            int limit = remaining < wrapwidth ? remaining : wrapwidth;
            char* p = x->rt_buf + i;
            int ncopy = 0;
            int nl = 1;
            if (remaining <= wrapwidth) {
                while (ncopy < limit && p[ncopy] != '\n')
                    ncopy++;
                nl = 0;
            } else {
                while (ncopy < limit && p[ncopy] != '\n')
                    ncopy++;
                if (ncopy == limit) {
                    /* wrap at the last space in the window */
                    int j = ncopy;
                    while (j > 0) {
                        j--;
                        ncopy--;
                        if (p[j] == ' ')
                            break;
                    }
                    if (ncopy < 0)
                        ncopy = limit;
                }
            }
            if (nlines == cursorline) {
                *cursorp = (wrapcol < 0 ? 0 : (ncopy < wrapcol ? ncopy : wrapcol)) + i;
                hit = 1;
            }
            strncpy(buf + nleft, p, ncopy);
            if (selstart == 0 && i <= x->rt_selectfrom && x->rt_selectfrom < i + ncopy + nl)
                selstart = x->rt_selectfrom - i + nleft;
            if (i <= x->rt_selectto && x->rt_selectto < i + ncopy + nl)
                selend = x->rt_selectto - i + nleft;
            nleft += ncopy;
            i += ncopy + nl;
            if (i < x->rt_bufsize)
                buf[nleft++] = '\n';
            if ((int)ncopy > (int)maxline)
                maxline = ncopy;
            nlines++;
        }
        if (!hit)
            *cursorp = nleft;
    } else {
        *cursorp = nleft;
    }

    xpos = text_xpix(ob, x->rt_glist);
    ypos = text_ypix(ob, x->rt_glist);
    if (nlines < 1)
        nlines = 1;
    if ((short)x->rt_owner->te_width == 0 && maxline < 3) {
        int pad = 3 - maxline;
        memset(buf + nleft, ' ', pad);
        nleft += pad;
        maxline += pad;
    }
    newwidth = fontwidth * maxline + 2;
    newheight = fontheight * nlines + 4;

    if (action == 1) {
        const char* color = glist_isselected(x->rt_glist, (t_gobj*)x->rt_glist) ? "blue" : "black";
        int fontid = sys_fontweight(font, color);
        SetSerializer("pdtk_text_new .x%lx.c %s %f %f {%.*s} %d %s\n",
                      canvas, x->rt_tag,
                      (double)((float)xpos + 1.0f), (double)((float)ypos + 2.0f),
                      nleft, buf, fontid);
    } else if (action == 2) {
        SetSerializer("pdtk_text_set .x%lx.c %s {%.*s}\n",
                      canvas, x->rt_tag, nleft, buf);
        if (newwidth != x->rt_width || newheight != x->rt_height)
            text_drawborder(ob, x->rt_glist, x->rt_tag, newwidth, newheight, 0);
        if (x->rt_active) {
            if (selstart < selend) {
                SetSerializer(".x%lx.c select from %s %d\n", canvas, x->rt_tag, selstart);
                SetSerializer(".x%lx.c select to %s %d\n", canvas, x->rt_tag, selend - 1);
                SetSerializer(".x%lx.c focus \"\"\n", canvas);
            } else {
                SetSerializer(".x%lx.c select clear\n", canvas);
                SetSerializer(".x%lx.c icursor %s %d\n", canvas, x->rt_tag, selstart);
                SetSerializer(".x%lx.c focus %s\n", canvas, x->rt_tag);
            }
        }
    }
    x->rt_width = newwidth;
    x->rt_height = newheight;
    *widthp = newwidth;
    *heightp = newheight;
    if (buf != smallbuf)
        freebytes(buf, x->rt_bufsize * 2 + 1);
}

// =========================================================================
// 0x00A4EE20  EA::Audio::Eapd::rtext_retext
// -------------------------------------------------------------------------
// Re-reads the object's text.  If the object is a message box whose text is
// longer than the box, the text is shortened in a way that keeps the tail
// readable: ".NNNN" indices are shifted, everything else gets a leading
// +/- sign or a '>' marker.
// =========================================================================
// @ 0x00a4ee20
void rtext_retext(t_rtext* x)
{
    int dummyh = 0;
    int dummyc = 0;
    int dummyw = 0;
    t_text* ob = x->rt_owner;
    int len;

    freebytes(x->rt_buf, x->rt_bufsize);
    binbuf_gettext(ob->te_binbuf, &x->rt_buf, &x->rt_bufsize);
    if ((short)ob->te_width < 1 || (ob->te_type & 3) != 3 ||
        x->rt_bufsize <= (short)ob->te_width)
        goto done;

    len = x->rt_bufsize;
    {
        int* atoms = binbuf_getvec(ob->te_binbuf);
        int natom = binbuf_getnatom(ob->te_binbuf);
        int limit = len - (short)ob->te_width;

        if (natom == 1 && atoms[0] == 1) {
            /* A single float: keep only a signed mantissa. */
            char* p = x->rt_buf;
            char* end = p + len;
            while (p < end && *p != '.')
                p++;
            if (p < end) {
                char* q = p + 1;
                while (q < end && *q >= '0' && *q <= '9')
                    q++;
                if ((int)(q - 1 - p) < limit) {
                    x->rt_buf[0] = (0.0f < (float)atoms[1]) ? '+' : '-';
                    x->rt_buf = (char*)resizebytes(x->rt_buf, len, 1, "EAPd/char");
                    len = 1;
                } else {
                    char* dst = q - limit;
                    char* src = q;
                    while (src < end)
                        *dst++ = *src++;
                    x->rt_buf = (char*)resizebytes(x->rt_buf, len,
                                                   (short)ob->te_width, "EAPd/char");
                    len = (short)ob->te_width;
                }
            }
        } else if ((short)ob->te_width < len) {
            x->rt_buf[(short)ob->te_width - 1] = '>';
            x->rt_buf = (char*)resizebytes(x->rt_buf, len,
                                           (short)ob->te_width, "EAPd/char");
            len = (short)ob->te_width;
        }
        x->rt_bufsize = len;
    }
done:
    rtext_senditup(x, 2, &dummyw, &dummyh, &dummyc);
}

// =========================================================================
// 0x00A4EFB0  EA::Audio::Eapd::glist_findrtext
// =========================================================================
// @ 0x00a4efb0
__declspec(noinline) t_rtext* glist_findrtext(t_glist* x, t_text* y)
{
    t_rtext* rt = x->gl_editor->e_rtextlist;
    while (rt && rt->rt_owner != y)
        rt = rt->rt_next;
    return rt;
}

// =========================================================================
// 0x00A4EFD0  EA::Audio::Eapd::rtext_width
// =========================================================================
// @ 0x00a4efd0
int rtext_width(t_rtext* x)
{
    int w = 0;
    int h = 0;
    int c = 0;
    rtext_senditup(x, 0, &w, &h, &c);
    return w;
}

// =========================================================================
// 0x00A4F010  EA::Audio::Eapd::rtext_height
// =========================================================================
// @ 0x00a4f010
int rtext_height(t_rtext* x)
{
    int w = 0;
    int h = 0;
    int c = 0;
    rtext_senditup(x, 0, &w, &h, &c);
    return h;
}

// =========================================================================
// 0x00A4F050  EA::Audio::Eapd::rtext_draw
// =========================================================================
// @ 0x00a4f050
void rtext_draw(t_rtext* x)
{
    int w = 0;
    int h = 0;
    int c = 0;
    rtext_senditup(x, 1, &w, &h, &c);
}

// =========================================================================
// 0x00A4F080  EA::Audio::Eapd::rtext_erase
// =========================================================================
// @ 0x00a4f080
void rtext_erase(t_rtext* x)
{
    SetSerializer(".x%lx.c delete %s\n", glist_getcanvas(x->rt_glist), x->rt_tag);
}

// =========================================================================
// 0x00A4F0B0  EA::Audio::Eapd::rtext_displace
// =========================================================================
// @ 0x00a4f0b0
void rtext_displace(t_rtext* x, int dx, int dy)
{
    SetSerializer(".x%lx.c move %s %d %d\n", glist_getcanvas(x->rt_glist),
                  x->rt_tag, dx, dy);
}

// =========================================================================
// 0x00A4F0E0  EA::Audio::Eapd::rtext_select
// =========================================================================
// @ 0x00a4f0e0
void rtext_select(t_rtext* x, int state)
{
    t_glist* canvas = glist_getcanvas(x->rt_glist);
    SetSerializer(".x%lx.c itemconfigure %s -fill %s\n", canvas, x->rt_tag,
                  state ? "blue" : "black");
    gpEditingCanvas = canvas;
}

// =========================================================================
// 0x00A4F130  EA::Audio::Eapd::rtext_activate
// =========================================================================
// @ 0x00a4f130
void rtext_activate(t_rtext* x, int state)
{
    int w = 0;
    int h = 0;
    t_glist* canvas;
    t_glist* gl = x->rt_glist;

    canvas = glist_getcanvas(gl);
    if (state) {
        SetSerializer(".x%lx.c focus %s\n", canvas, x->rt_tag);
        gl->gl_editor->e_textedfor = x;
        gl->gl_editor->e_flags &= 0xffffffef;
        x->rt_selectfrom = 0;
        x->rt_xpix = 0;
        x->rt_selectto = x->rt_bufsize;
        x->rt_active = 1;
    } else {
        SetSerializer("selection clear .x%lx.c\n", canvas);
        SetSerializer(".x%lx.c focus \"\"\n", canvas);
        if (gl->gl_editor->e_textedfor == x)
            gl->gl_editor->e_textedfor = 0;
        x->rt_active = 0;
    }
    rtext_senditup(x, 2, &w, &h, &h);
}

} } }  // namespace EA::Audio::Eapd
