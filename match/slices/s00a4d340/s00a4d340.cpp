// Slice s00a4d340 - EA::Audio::Eapd (Pure Data) canvas / graph helpers.
#include "s00a4d340.h"

namespace EA { namespace Audio { namespace Eapd {

// @ 0xa4d340
void glist_add(t_glist* x, t_gobj* y)
{
    t_gobj* y2;
    y->g_next = 0;
    if (!(y2 = x->gl_list))
        x->gl_list = y;
    else {
        t_gobj* nx;
        for (; (nx = y2->g_next); y2 = nx)
            ;
        y2->g_next = y;
    }
    if (x->gl_editor) {
        t_text* ob = pd_checkobject(&y->g_pd);
        if (ob)
            rtext_new(x, ob);
        if (x->gl_editor && x->gl_isgraph && !x->gl_goprect && pd_checkobject(&y->g_pd)) {
            x->gl_goprect = 1;
            canvas_drawredrect(x, 1);
        }
    }
    if (glist_isvisible(x))
        gobj_vis(y, x, 1);
}

// @ 0xa4d3e0
void glist_retext(t_glist* x, t_text* y)
{
    if (x->gl_editor && x->gl_editor->e_textedfor) {
        t_rtext* rt = glist_findrtext(x, y);
        if (rt)
            FUN_00a4ee20(rt);
    }
}

// @ 0xa4d410
__declspec(noinline) t_glist* glist_getcanvas(t_glist* x)
{
    while (x->gl_owner && !x->gl_havewindow && x->gl_isgraph)
        x = x->gl_owner;
    return x;
}

// @ 0xa4d440
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

// @ 0xa4d4d0
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

// @ 0xa4d610
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

// @ 0xa4d6a0
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

// @ 0xa4d7e0
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

// @ 0xa4d880
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

// @ 0xa4d920
int text_xpix(t_text* x, t_glist* glist)
{
    if (glist->gl_havewindow || !glist->gl_isgraph || !glist->gl_editor)
        return x->te_xpix;
    else if (glist->gl_goprect)
        return (int)(x->te_xpix + glist_xtopixels(glist, glist->gl_x1) - glist->gl_xmargin);
    else
        return (int)glist_xtopixels(glist, glist->gl_x1 + (glist->gl_x2 - glist->gl_x1) * x->te_xpix / (glist->gl_screenx2 - glist->gl_screenx1));
}

// @ 0xa4d9c0
int text_ypix(t_text* x, t_glist* glist)
{
    if (glist->gl_havewindow || !glist->gl_isgraph || !glist->gl_editor)
        return x->te_ypix;
    else if (glist->gl_goprect)
        return (int)(x->te_ypix + glist_ytopixels(glist, glist->gl_y1) - glist->gl_ymargin);
    else
        return (int)glist_ytopixels(glist, glist->gl_y1 + (glist->gl_y2 - glist->gl_y1) * x->te_ypix / (glist->gl_screeny2 - glist->gl_screeny1));
}

// @ 0xa4da60
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

// @ 0xa4daf0
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

// @ 0xa4dc60
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

// @ 0xa4dd10
void graph_activate(t_gobj* z, t_glist* glist, int state)
{
    t_glist* x = (t_glist*)z;
    if (canvas_showtext(x))
        text_widgetbehavior.w_activatefn(z, glist, state);
}

// @ 0xa4dd40
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

// @ 0xa4de30
bool graph_setup()
{
    FUN_00a47fb0(gpCanvasClass, &graph_widgetbehavior);
    return true;
}

// @ 0xa4de50
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

// @ 0xa4df80
void glist_clear(t_glist* x)
{
    t_gobj* y;
    while ((y = x->gl_list))
        glist_delete(x, y);
}

// @ 0xa4dfb0
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

// @ 0xa4e030
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

// @ 0xa4e0b0
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

// @ 0xa4e120
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

// @ 0xa4e1c0
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

// @ 0xa4e260
float glist_dpixtodx(t_glist* x, float dxpix)
{
    return (glist_pixelstox(x, 1) - glist_pixelstox(x, 0)) * dxpix;
}

// @ 0xa4e2a0
float glist_dpixtody(t_glist* x, float dypix)
{
    return (glist_pixelstoy(x, 1) - glist_pixelstoy(x, 0)) * dypix;
}

}}}
