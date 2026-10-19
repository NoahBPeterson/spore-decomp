// src/game/SPAudio/eapdgraph.cpp -- migrated from slice(s) s00a4d340 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdgraph.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00a4d340 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct t_symbol;
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
struct t_text {        // t_object
    t_gobj  te_g;       // +0x00
    uint32_t pad08[3];  // binbuf, outlet, inlet
    int16_t te_xpix;    // +0x14
    int16_t te_ypix;    // +0x16
    uint32_t pad18[4];
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_editor {
    uint32_t pad00[3];
    void*    e_textedfor;   // +0x0c
    uint32_t pad10[2];
    t_gobj*  e_grab;        // +0x18
    void*    e_motionfn;    // +0x1c
    void*    e_keyfn;       // +0x20
    uint32_t pad24[4];
    int      e_xwas;        // +0x34
    int      e_ywas;        // +0x38
    uint32_t pad3c[5];
    unsigned e_onmotion : 3; // +0x50
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_glist {
    t_text    gl_obj;        // +0x00
    t_gobj*   gl_list;       // +0x28
    t_glist*  gl_owner;      // +0x2c
    int       gl_pixwidth;   // +0x30
    int       gl_pixheight;  // +0x34
    float     gl_x1;         // +0x38
    float     gl_y1;         // +0x3c
    float     gl_x2;         // +0x40
    float     gl_y2;         // +0x44
    int       gl_screenx1;   // +0x48
    int       gl_screeny1;   // +0x4c
    int       gl_screenx2;   // +0x50
    int       gl_screeny2;   // +0x54
    int       gl_xmargin;    // +0x58
    int       gl_ymargin;    // +0x5c
    t_editor* gl_editor;     // +0x60
    uint32_t  pad64[5];
    unsigned  gl_havewindow : 1;   // +0x78
    unsigned  gl_mapped : 1;
    unsigned  gl_dirty : 1;
    unsigned  gl_loading : 1;
    unsigned  gl_willvis : 1;
    unsigned  gl_edit : 1;
    unsigned  gl_isdeleting : 1;
    unsigned  gl_goprect : 1;
    unsigned  gl_isgraph : 1;
    unsigned  gl_hidetext : 1;
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_widgetbehavior {
    void (*w_getrectfn)(t_gobj*, t_glist*, int*, int*, int*, int*);   // +0x00
    void (*w_displacefn)(t_gobj*, t_glist*, int, int);                // +0x04
    void (*w_selectfn)(t_gobj*, t_glist*, int);                       // +0x08
    void (*w_activatefn)(t_gobj*, t_glist*, int);                     // +0x0c
    void (*w_deletefn)(t_gobj*, t_glist*);                            // +0x10
    void (*w_visfn)(t_gobj*, t_glist*, int);                          // +0x14
    int  (*w_clickfn)(t_gobj*, t_glist*, int, int, int, int, int, int); // +0x18
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_widgetbehavior text_widgetbehavior;   // 0x1554364
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_widgetbehavior graph_widgetbehavior;  // 0x1554348
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* gpVinletClass;                 // 0x167582c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* gpVoutletClass;                // 0x1675830
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* gpCanvasClass;                 // 0x1675490
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol* gEmptySymbol;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol* gInletSym;                    // 0x16758a0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_text* pd_checkobject(t_class** x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    pd_free(void* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*   getbytes(int n, const char* tag);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    freebytes(void* p, int n);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     glist_isvisible(t_glist* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     glist_istoplevel(t_glist* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    gobj_vis(t_gobj* x, t_glist* parent, int flag);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    gobj_getrect(t_gobj* x, t_glist* g, int* x1, int* y1, int* x2, int* y2);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     gobj_click(t_gobj* x, t_glist* g, int xpix, int ypix, int shift, int alt, int dbl, int doit);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    gobj_delete(t_gobj* x, t_glist* g);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    canvas_fixlinesfor(t_glist* parent, t_glist* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    canvas_deletelinesforio(t_glist* parent, t_glist* x, t_inlet* i, t_outlet* o);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     canvas_showtext(t_glist* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     canvas_hitbox(t_glist* x, t_gobj* y, int xpos, int ypos, int* x1, int* y1, int* x2, int* y2);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    canvas_setcursor(t_glist* x, unsigned int cursornum);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    inlet_free(t_inlet* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    outlet_free(t_outlet* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_inlet*  inlet_new(t_glist* owner, t_class** dest, t_symbol* s1, t_symbol* s2, t_symbol* e, t_symbol* f);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_outlet* outlet_new(t_glist* owner, t_symbol* s, t_symbol* c);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_inlet*  FUN_00a617b0(t_gobj* y);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    FUN_00a4a1e0(t_glist* x, t_inlet* i);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    FUN_00a4a220(t_glist* x, t_outlet* o);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_rtext* glist_findrtext(t_glist* x, t_text* y);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    rtext_select(t_rtext* r, int state);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
const char* rtext_gettag(t_rtext* r);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    sys_gui(const char* fmt, ...);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     text_shouldvis(t_text* x, t_glist* g);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     FUN_00a4c710(t_glist* x, t_gobj* y);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    FUN_00a4d090(t_glist* x, t_gobj* y);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    FUN_00a514d0(t_gobj* y, t_glist* x, const char* tag);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    glist_eraseiofor(t_glist* x, t_gobj* y, const char* tag);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    FUN_00a47fb0(t_class* c, void* wb);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    graph_graphrect(t_gobj* z, t_glist* glist, int* xp1, int* yp1, int* xp2, int* yp2);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern "C" int sprintf(char*, const char*, ...);
}
}
}
// ---- items of slice s00a4d340 end

// @ 0x00a4d410
namespace EA { namespace Audio { namespace Eapd {
__declspec(noinline) t_glist* glist_getcanvas(t_glist* x)
{
    while (x->gl_owner && !x->gl_havewindow && x->gl_isgraph)
        x = x->gl_owner;
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4d440
namespace EA { namespace Audio { namespace Eapd {
void canvas_rminlet(t_glist* x, t_inlet* i)
{
    t_glist* canvas = x->gl_owner;
    int redraw = (canvas && glist_isvisible(canvas) && !canvas->gl_isdeleting && glist_istoplevel(canvas));
    if (canvas)
        canvas_deletelinesforio(canvas, x, i, 0);
    if (redraw)
        gobj_vis((t_gobj*)x, x->gl_owner, 0);
    inlet_free(i);
    if (redraw) {
        gobj_vis((t_gobj*)x, x->gl_owner, 1);
        canvas_fixlinesfor(x->gl_owner, x);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4d4d0
namespace EA { namespace Audio { namespace Eapd {
void canvas_resortinlets(t_glist* x)
{
    int ninlets = 0, i, j, xmax;
    t_gobj *y, **vec, **vp, **maxp;
    if (x->gl_list) {
        for (y = x->gl_list; y; y = y->g_next)
            if (y->g_pd == gpVinletClass)
                ninlets++;
        if (ninlets < 2)
            return;
        vec = (t_gobj**)getbytes(ninlets * sizeof(*vec), "EAPd/t_gobj*");
        for (y = x->gl_list, vp = vec; y; y = y->g_next)
            if (y->g_pd == gpVinletClass)
                *vp++ = y;
        for (i = ninlets; i--;) {
            for (vp = vec, j = ninlets, xmax = -0x7fffffff, maxp = 0; j--; vp++) {
                int x1, y1, x2, y2;
                if (*vp) {
                    gobj_getrect(*vp, x, &x1, &y1, &x2, &y2);
                    if (x1 > xmax) {
                        maxp = vp;
                        xmax = x1;
                    }
                }
            }
            if (!maxp)
                break;
            y = *maxp;
            *maxp = 0;
            FUN_00a4a1e0(x, FUN_00a617b0(y));
        }
        freebytes(vec, ninlets * sizeof(*vec));
        if (x->gl_owner && glist_isvisible(x->gl_owner))
            canvas_fixlinesfor(x->gl_owner, x);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4d610
namespace EA { namespace Audio { namespace Eapd {
void canvas_rmoutlet(t_glist* x, t_outlet* o)
{
    t_glist* canvas = x->gl_owner;
    int redraw = (canvas && glist_isvisible(canvas) && !canvas->gl_isdeleting && glist_istoplevel(canvas));
    if (canvas)
        canvas_deletelinesforio(canvas, x, 0, o);
    if (redraw)
        gobj_vis((t_gobj*)x, x->gl_owner, 0);
    outlet_free(o);
    if (redraw) {
        gobj_vis((t_gobj*)x, x->gl_owner, 1);
        canvas_fixlinesfor(x->gl_owner, x);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4d6a0
namespace EA { namespace Audio { namespace Eapd {
void canvas_resortoutlets(t_glist* x)
{
    int noutlets = 0, i, j, xmax;
    t_gobj *y, **vec, **vp, **maxp;
    if (x->gl_list) {
        for (y = x->gl_list; y; y = y->g_next)
            if (y->g_pd == gpVoutletClass)
                noutlets++;
        if (noutlets < 2)
            return;
        vec = (t_gobj**)getbytes(noutlets * sizeof(*vec), "EAPd/t_gobj*");
        for (y = x->gl_list, vp = vec; y; y = y->g_next)
            if (y->g_pd == gpVoutletClass)
                *vp++ = y;
        for (i = noutlets; i--;) {
            for (vp = vec, j = noutlets, xmax = -0x7fffffff, maxp = 0; j--; vp++) {
                int x1, y1, x2, y2;
                if (*vp) {
                    gobj_getrect(*vp, x, &x1, &y1, &x2, &y2);
                    if (x1 > xmax) {
                        maxp = vp;
                        xmax = x1;
                    }
                }
            }
            if (!maxp)
                break;
            y = *maxp;
            *maxp = 0;
            FUN_00a4a220(x, (t_outlet*)FUN_00a617b0(y));
        }
        freebytes(vec, noutlets * sizeof(*vec));
        if (x->gl_owner && glist_isvisible(x->gl_owner))
            canvas_fixlinesfor(x->gl_owner, x);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4d7e0
namespace EA { namespace Audio { namespace Eapd {
float glist_xtopixels(t_glist* x, float xval)
{
    if (!x->gl_isgraph)
        return (xval - x->gl_x1) / (x->gl_x2 - x->gl_x1);
    else if (x->gl_havewindow)
        return (x->gl_screenx2 - x->gl_screenx1) * (xval - x->gl_x1) / (x->gl_x2 - x->gl_x1);
    else {
        int x1, y1, x2, y2;
        graph_graphrect((t_gobj*)x, x->gl_owner, &x1, &y1, &x2, &y2);
        return x1 + (x2 - x1) * (xval - x->gl_x1) / (x->gl_x2 - x->gl_x1);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4d880
namespace EA { namespace Audio { namespace Eapd {
float glist_ytopixels(t_glist* x, float yval)
{
    if (!x->gl_isgraph)
        return (yval - x->gl_y1) / (x->gl_y2 - x->gl_y1);
    else if (x->gl_havewindow)
        return (x->gl_screeny2 - x->gl_screeny1) * (yval - x->gl_y1) / (x->gl_y2 - x->gl_y1);
    else {
        int x1, y1, x2, y2;
        graph_graphrect((t_gobj*)x, x->gl_owner, &x1, &y1, &x2, &y2);
        return y1 + (y2 - y1) * (yval - x->gl_y1) / (x->gl_y2 - x->gl_y1);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4d920
namespace EA { namespace Audio { namespace Eapd {
int text_xpix(t_text* x, t_glist* glist)
{
    if (glist->gl_havewindow || !glist->gl_isgraph || !glist->gl_editor)
        return x->te_xpix;
    else if (glist->gl_goprect)
        return (int)(x->te_xpix + glist_xtopixels(glist, glist->gl_x1) - glist->gl_xmargin);
    else
        return (int)glist_xtopixels(glist, glist->gl_x1 + (glist->gl_x2 - glist->gl_x1) * x->te_xpix / (glist->gl_screenx2 - glist->gl_screenx1));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4d9c0
namespace EA { namespace Audio { namespace Eapd {
int text_ypix(t_text* x, t_glist* glist)
{
    if (glist->gl_havewindow || !glist->gl_isgraph || !glist->gl_editor)
        return x->te_ypix;
    else if (glist->gl_goprect)
        return (int)(x->te_ypix + glist_ytopixels(glist, glist->gl_y1) - glist->gl_ymargin);
    else
        return (int)glist_ytopixels(glist, glist->gl_y1 + (glist->gl_y2 - glist->gl_y1) * x->te_ypix / (glist->gl_screeny2 - glist->gl_screeny1));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4da60
namespace EA { namespace Audio { namespace Eapd {
void graph_graphrect(t_gobj* z, t_glist* glist, int* xp1, int* yp1, int* xp2, int* yp2)
{
    t_glist* x = (t_glist*)z;
    int x1 = text_xpix(&x->gl_obj, glist);
    int y1 = text_ypix(&x->gl_obj, glist);
    if (canvas_showtext(x)) {
        int hx1, hy1, hx2, hy2;
        text_widgetbehavior.w_getrectfn(z, glist, &hx1, &hy1, &hx2, &hy2);
        y1 += hy2 - hy1;
    }
    int w = x->gl_pixwidth;
    int h = x->gl_pixheight;
    int x2 = w + x1;
    int y2 = h + y1;
    *xp1 = x1;
    *yp1 = y1;
    *xp2 = x2;
    *yp2 = y2;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4daf0
namespace EA { namespace Audio { namespace Eapd {
void graph_getrect(t_gobj* z, t_glist* glist, int* xp1, int* yp1, int* xp2, int* yp2)
{
    t_glist* x = (t_glist*)z;
    int x1 = 0x7fffffff, y1 = 0x7fffffff, x2 = -0x7fffffff, y2 = -0x7fffffff;
    int hx1, hy1, hx2, hy2;
    if (x->gl_isgraph) {
        graph_graphrect(z, glist, &x1, &y1, &x2, &y2);
        if (canvas_showtext(x)) {
            text_widgetbehavior.w_getrectfn(z, glist, &hx1, &hy1, &hx2, &hy2);
            if (hx2 > x2)
                x2 = hx2;
            y1 = hy1;
        }
        if (!x->gl_goprect) {
            t_gobj* g;
            int hadwindow = x->gl_havewindow;
            x->gl_havewindow = 0;
            for (g = x->gl_list; g; g = g->g_next) {
                t_text* ob = pd_checkobject(&g->g_pd);
                if (ob && !text_shouldvis(ob, x))
                    continue;
                gobj_getrect(g, x, &hx1, &hy1, &hx2, &hy2);
                if (hx2 > x2)
                    x2 = hx2;
                if (hy2 > y2)
                    y2 = hy2;
            }
            x->gl_havewindow = hadwindow;
        }
        } else
        text_widgetbehavior.w_getrectfn(z, glist, &x1, &y1, &x2, &y2);
    *xp1 = x1;
    *yp1 = y1;
    *xp2 = x2;
    *yp2 = y2;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4dc60
namespace EA { namespace Audio { namespace Eapd {
void graph_select(t_gobj* z, t_glist* glist, int state)
{
    t_glist* x = (t_glist*)z;
    if (!x->gl_isgraph)
        text_widgetbehavior.w_selectfn(z, glist, state);
    else {
        t_rtext* y = glist_findrtext(glist, &x->gl_obj);
        if (canvas_showtext(x))
            rtext_select(y, state);
        sys_gui(".x%lx.c itemconfigure %sR -fill %s\n", glist, rtext_gettag(y), (state ? "blue" : "black"));
        sys_gui(".x%lx.c itemconfigure graph%lx -outline %s\n", glist_getcanvas(glist), x, (state ? "blue" : "black"));
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4dd10
namespace EA { namespace Audio { namespace Eapd {
void graph_activate(t_gobj* z, t_glist* glist, int state)
{
    t_glist* x = (t_glist*)z;
    if (canvas_showtext(x))
        text_widgetbehavior.w_activatefn(z, glist, state);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4dd40
namespace EA { namespace Audio { namespace Eapd {
int graph_click(t_gobj* z, t_glist* glist, int xpix, int ypix, int shift, int alt, int dbl, int doit)
{
    t_glist* x = (t_glist*)z;
    t_gobj* y;
    int clickreturned = 0;
    if (!x->gl_isgraph)
        return text_widgetbehavior.w_clickfn(z, glist, xpix, ypix, shift, alt, dbl, doit);
    else if (x->gl_havewindow)
        return 0;
    else {
        for (y = x->gl_list; y; y = y->g_next) {
            int x1, y1, x2, y2;
            if (canvas_hitbox(x, y, xpix, ypix, &x1, &y1, &x2, &y2) &&
                (clickreturned = gobj_click(y, x, xpix, ypix, shift, alt, 0, doit)))
                break;
        }
        if (!doit) {
            if (y)
                canvas_setcursor(glist_getcanvas(x), clickreturned);
            else
                canvas_setcursor(glist_getcanvas(x), 0);
        }
        return clickreturned;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4de30
namespace EA { namespace Audio { namespace Eapd {
bool graph_setup()
{
    FUN_00a47fb0(gpCanvasClass, &graph_widgetbehavior);
    return true;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4de50
namespace EA { namespace Audio { namespace Eapd {
void glist_delete(t_glist* x, t_gobj* y)
{
    t_glist* canvas = x;
    while (canvas->gl_owner && !canvas->gl_havewindow && canvas->gl_isgraph)
        canvas = canvas->gl_owner;
    int wasdeleting = canvas->gl_isdeleting;
    canvas->gl_isdeleting = 1;
    if (x->gl_editor) {
        if (x->gl_editor->e_grab == y)
            x->gl_editor->e_grab = 0;
        if (FUN_00a4c710(x, y))
            FUN_00a4d090(x, y);
        if (y->g_pd == gpCanvasClass) {
            t_glist* gl = (t_glist*)y;
            if (gl->gl_isgraph) {
                char buf[80];
                sprintf(buf, "graph%lx", y);
                glist_eraseiofor(x, y, buf);
            } else {
                FUN_00a514d0(y, x, rtext_gettag(glist_findrtext(x, (t_text*)y)));
            }
        }
    }
    if (x->gl_editor && glist_isvisible(x))
        gobj_vis(y, x, 0);
    gobj_delete(y, x);
    {
        t_gobj* g = x->gl_list;
        if (g == y)
            x->gl_list = y->g_next;
        else {
            for (; g; g = g->g_next)
                if (g->g_next == y) {
                    g->g_next = y->g_next;
                    break;
                }
        }
    }
    pd_free(y);
    canvas->gl_isdeleting = wasdeleting;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4df80
namespace EA { namespace Audio { namespace Eapd {
void glist_clear(t_glist* x)
{
    t_gobj* y;
    while ((y = x->gl_list))
        glist_delete(x, y);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4dfb0
namespace EA { namespace Audio { namespace Eapd {
void glist_grab(t_glist* x, t_gobj* y, void* motionfn, void* keyfn, int xpos, int ypos)
{
    t_glist* x2 = x;
    while (x2->gl_owner && !x2->gl_havewindow && x2->gl_isgraph)
        x2 = x2->gl_owner;
    if (motionfn)
        x2->gl_editor->e_onmotion = 4;
    else
        x2->gl_editor->e_onmotion = 0;
    x2->gl_editor->e_grab = y;
    x2->gl_editor->e_motionfn = motionfn;
    x2->gl_editor->e_keyfn = keyfn;
    x2->gl_editor->e_xwas = xpos;
    x2->gl_editor->e_ywas = ypos;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4e030
namespace EA { namespace Audio { namespace Eapd {
t_inlet* canvas_addinlet(t_glist* x, t_class** a, t_symbol* b, t_symbol* c)
{
    t_inlet* ip = inlet_new(x, a, b, c, gEmptySymbol, gInletSym);
    if (!x->gl_loading && x->gl_owner && glist_isvisible(x->gl_owner)) {
        gobj_vis((t_gobj*)x, x->gl_owner, 0);
        gobj_vis((t_gobj*)x, x->gl_owner, 1);
        canvas_fixlinesfor(x->gl_owner, x);
    }
    if (!x->gl_loading)
        canvas_resortinlets(x);
    return ip;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4e0b0
namespace EA { namespace Audio { namespace Eapd {
t_outlet* canvas_addoutlet(t_glist* x, t_class** a, t_symbol* b, t_symbol* c)
{
    t_outlet* op = outlet_new(x, b, c);
    if (!x->gl_loading && x->gl_owner && glist_isvisible(x->gl_owner)) {
        gobj_vis((t_gobj*)x, x->gl_owner, 0);
        gobj_vis((t_gobj*)x, x->gl_owner, 1);
        canvas_fixlinesfor(x->gl_owner, x);
    }
    if (!x->gl_loading)
        canvas_resortoutlets(x);
    return op;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4e120
namespace EA { namespace Audio { namespace Eapd {
float glist_pixelstox(t_glist* x, float xpix)
{
    if (!x->gl_isgraph)
        return x->gl_x1 + (x->gl_x2 - x->gl_x1) * xpix;
    else if (x->gl_havewindow)
        return x->gl_x1 + (x->gl_x2 - x->gl_x1) * xpix / (x->gl_screenx2 - x->gl_screenx1);
    else {
        int x1, y1, x2, y2;
        graph_graphrect((t_gobj*)x, x->gl_owner, &x1, &y1, &x2, &y2);
        return x->gl_x1 + (x->gl_x2 - x->gl_x1) * (xpix - x1) / (x2 - x1);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4e1c0
namespace EA { namespace Audio { namespace Eapd {
float glist_pixelstoy(t_glist* x, float ypix)
{
    if (!x->gl_isgraph)
        return x->gl_y1 + (x->gl_y2 - x->gl_y1) * ypix;
    else if (x->gl_havewindow)
        return x->gl_y1 + (x->gl_y2 - x->gl_y1) * ypix / (x->gl_screeny2 - x->gl_screeny1);
    else {
        int x1, y1, x2, y2;
        graph_graphrect((t_gobj*)x, x->gl_owner, &x1, &y1, &x2, &y2);
        return x->gl_y1 + (x->gl_y2 - x->gl_y1) * (ypix - y1) / (y2 - y1);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4e260
namespace EA { namespace Audio { namespace Eapd {
float glist_dpixtodx(t_glist* x, float dxpix)
{
    return (glist_pixelstox(x, 1) - glist_pixelstox(x, 0)) * dxpix;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4e2a0
namespace EA { namespace Audio { namespace Eapd {
float glist_dpixtody(t_glist* x, float dypix)
{
    return (glist_pixelstoy(x, 1) - glist_pixelstoy(x, 0)) * dypix;
}
}}}  // namespace EA::Audio::Eapd
