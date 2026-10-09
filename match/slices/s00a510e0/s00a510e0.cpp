// Slice s00a510e0 - EA::Audio::Eapd (Pure Data): g_text.c (borders, setto, vis), gatom, setup chain.
#include "s00a510e0.h"

namespace EA { namespace Audio { namespace Eapd {

struct t_widgetbehavior {
    void (*w_getrectfn)(t_gobj*, t_glist*, int*, int*, int*, int*);
    void (*w_displacefn)(t_gobj*, t_glist*, int, int);
    void (*w_selectfn)(t_gobj*, t_glist*, int);
    void (*w_activatefn)(t_gobj*, t_glist*, int);
    void (*w_deletefn)(t_gobj*, t_glist*);
    void (*w_visfn)(t_gobj*, t_glist*, int);
    int  (*w_clickfn)(t_gobj*, t_glist*, int, int, int, int, int, int);
};

struct t_gatom {
    t_text   a_text;         // +0x00
    uint32_t pad28[3];
    t_glist* a_glist;        // +0x34
    uint32_t pad38[3];
    t_symbol a_label;        // +0x44
    uint8_t  pad4c[0x85 - 0x4c];
    char     a_wherelabel;   // +0x85
};

// @ 0xa510e0
void glist_drawiofor(t_glist* glist, t_text* ob, int firsttime, const char* tag,
                     int x1, int y1, int x2, int y2)
{
    int n = obj_noutlets(ob);
    int nplus = (n == 1 ? 1 : n - 1);
    int i;
    int width = x2 - x1;
    for (i = 0; i < n; i++) {
        int onset = x1 + (width - 7) * i / nplus;
        if (firsttime)
            sys_gui(".x%lx.c create rectangle %d %d %d %d -tags %so%d\n", glist_getcanvas(glist),
                    onset, y2 - 1, onset + 7, y2, tag, i);
        else
            sys_gui(".x%lx.c coords %so%d %d %d %d %d\n", glist_getcanvas(glist), tag, i,
                    onset, y2 - 1, onset + 7, y2);
    }
    n = obj_ninlets(ob);
    nplus = (n == 1 ? 1 : n - 1);
    for (i = 0; i < n; i++) {
        int onset = x1 + (width - 7) * i / nplus;
        if (firsttime)
            sys_gui(".x%lx.c create rectangle %d %d %d %d -tags %si%d\n", glist_getcanvas(glist),
                    onset, y1, onset + 7, y1 + 1, tag, i);
        else
            sys_gui(".x%lx.c coords %si%d %d %d %d %d\n", glist_getcanvas(glist), tag, i,
                    onset, y1, onset + 7, y1 + 1);
    }
}

// @ 0xa51240
void text_drawborder(t_text* x, t_glist* glist, const char* tag, int width2, int height2, int firsttime)
{
    t_text* ob;
    int x1, y1, x2, y2;
    text_getrect(x, glist, &x1, &y1, &x2, &y2);
    if (x->te_type == T_OBJECT) {
        const char* pattern = (x->te_g.g_pd == gpTextClass ? "-" : "\"\"");
        if (firsttime)
            sys_gui(".x%lx.c create line %d %d %d %d %d %d %d %d %d %d -dash %s -tags %sR\n",
                    glist_getcanvas(glist), x1, y1, x2, y1, x2, y2, x1, y2, x1, y1, pattern, tag);
        else {
            sys_gui(".x%lx.c coords %sR %d %d %d %d %d %d %d %d %d %d\n", glist_getcanvas(glist), tag,
                    x1, y1, x2, y1, x2, y2, x1, y2, x1, y1);
            sys_gui(".x%lx.c itemconfigure %sR -dash %s\n", glist_getcanvas(glist), tag, pattern);
        }
    }
    else if (x->te_type == T_MESSAGE) {
        int corner = x2 + 4;
        if (firsttime)
            sys_gui(".x%lx.c create line %d %d %d %d %d %d %d %d %d %d %d %d %d %d -tags %sR\n",
                    glist_getcanvas(glist), x1, y1, corner, y1, x2, y1 + 4, x2, y2 - 4, corner, y2, x1, y2, x1, y1, tag);
        else
            sys_gui(".x%lx.c coords %sR %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
                    glist_getcanvas(glist), tag, x1, y1, corner, y1, x2, y1 + 4, x2, y2 - 4, corner, y2, x1, y2, x1, y1);
    }
    else if (x->te_type == T_ATOM) {
        const char* fmt;
        if (firsttime)
            fmt = ".x%lx.c create line %d %d %d %d %d %d %d %d %d %d %d %d -tags %sR\n";
        else
            fmt = ".x%lx.c coords %sR %d %d %d %d %d %d %d %d %d %d %d %d\n";
        if (firsttime)
            sys_gui(fmt, glist_getcanvas(glist), x1, y1, x2 - 4, y1, x2, y1 + 4, x2, y2, x1, y2, x1, y1, tag);
        else
            sys_gui(fmt, glist_getcanvas(glist), tag, x1, y1, x2 - 4, y1, x2, y1 + 4, x2, y2, x1, y2, x1, y1);
    }
    if ((ob = pd_checkobject(&x->te_g.g_pd)))
        glist_drawiofor(glist, ob, firsttime, tag, x1, y1, x2, y2);
}

// @ 0xa51450
void glist_eraseiofor(t_glist* glist, t_text* ob, const char* tag)
{
    int i, n = obj_noutlets(ob);
    for (i = 0; i < n; i++)
        sys_gui(".x%lx.c delete %so%d\n", glist_getcanvas(glist), tag, i);
    n = obj_ninlets(ob);
    for (i = 0; i < n; i++)
        sys_gui(".x%lx.c delete %si%d\n", glist_getcanvas(glist), tag, i);
}

// @ 0xa514d0
void text_eraseborder(t_text* x, t_glist* glist, const char* tag)
{
    if (x->te_type != T_TEXT) {
        sys_gui(".x%lx.c delete %sR\n", glist_getcanvas(glist), tag);
        glist_eraseiofor(glist, x, tag);
    }
}

// @ 0xa51510
void text_setto(t_text* x, t_glist* glist, const char* buf, int bufsize)
{
    if (x->te_type == T_OBJECT) {
        t_binbuf* b = binbuf_new();
        int natom1, natom2;
        t_atom *vec1, *vec2;
        binbuf_text(b, buf, bufsize);
        natom1 = binbuf_getnatom(x->te_binbuf);
        vec1 = binbuf_getvec(x->te_binbuf);
        natom2 = binbuf_getnatom(b);
        vec2 = binbuf_getvec(b);
        if (natom1 >= 1 && natom2 >= 1 && vec1[0].a_type == 2 && !strcmp(vec1[0].a_w.mpName, "pd") &&
            vec2[0].a_type == 2 && !strcmp(vec2[0].a_w.mpName, "pd")) {
            t_symbol tmp;
            t_symbol* s = gensym(&tmp, "rename");
            pd_typedmess(x, *s, natom2 - 1, vec2 + 1);
            binbuf_free(x->te_binbuf);
            x->te_binbuf = b;
        }
        else {
            int xwas = x->te_xpix, ywas = x->te_ypix;
            glist_delete(glist, &x->te_g);
            canvas_objtext(xwas, ywas, 0, b);
            canvas_restoreconnections(glist_getcanvas(glist));
        }
        if (natom2 >= 1 && vec2[0].a_type == 2 && !strcmp(vec2[0].a_w.mpName, "pd"))
            canvas_updatewindowlist();
    }
    else
        binbuf_text(x->te_binbuf, buf, bufsize);
}

// @ 0xa516e0
bool g_text_setup()
{
    t_symbol tmp;
    t_symbol* s;
    bool ok = true;
    s = gensym(&tmp, "text");
    gpTextClass = class_new(*s, 0, 0, 0x28, 0xb, 0);
    ok &= (gpTextClass != 0);
    s = gensym(&tmp, "message");
    spMessageClass = class_new(*s, 0, (void*)FUN_00a4fa30, 0x38, 3, 0);
    ok &= (spMessageClass != 0);
    ok &= class_addbang(spMessageClass, (void*)message_bang);
    ok &= class_doaddfloat(spMessageClass, (void*)message_float);
    ok &= class_addsymbol(spMessageClass, (void*)message_symbol);
    ok &= class_addlist(spMessageClass, (void*)message_list);
    ok &= class_addanything(spMessageClass, (void*)message_list);
    s = gensym(&tmp, "click");
    ok &= class_addalias(spMessageClass, (void*)message_click, *s, 1, 1, 1, 1, 1, 0);
    s = gensym(&tmp, "set");
    ok &= class_addmethod(spMessageClass, (void*)FUN_00a4f7b0, *s, 9, 0);
    s = gensym(&tmp, "add");
    ok &= class_addmethod(spMessageClass, (void*)FUN_00a4f810, *s, 9, 0);
    s = gensym(&tmp, "add2");
    ok &= class_addmethod(spMessageClass, (void*)LAB_00a4f7e0, *s, 9, 0);
    s = gensym(&tmp, "addcomma");
    ok &= class_addmethod(spMessageClass, (void*)LAB_00a4f840, *s, 0);
    s = gensym(&tmp, "addsemi");
    ok &= class_addmethod(spMessageClass, (void*)message_addcomma, *s, 0);
    s = gensym(&tmp, "adddollar");
    ok &= class_addmethod(spMessageClass, (void*)message_adddollar, *s, 1, 0);
    s = gensym(&tmp, "adddollsym");
    ok &= class_addmethod(spMessageClass, (void*)message_adddollsym, *s, 2, 0);
    s = gensym(&tmp, "messresponder");
    spMessresponderClass = class_new(*s, 0, 0, 0x28, 1, 0);
    ok &= (spMessresponderClass != 0);
    ok &= class_addbang(spMessresponderClass, (void*)messresponder_bang);
    ok &= class_doaddfloat(spMessresponderClass, (void*)messresponder_float);
    ok &= class_addsymbol(spMessresponderClass, (void*)messresponder_symbol);
    ok &= class_addlist(spMessresponderClass, (void*)messresponder_list);
    ok &= class_addanything(spMessresponderClass, (void*)messresponder_anything);
    s = gensym(&tmp, "gatom");
    spGatomClass = class_new(*s, 0, (void*)gatom_free, 0x90, 0xb, 0);
    ok &= (spGatomClass != 0);
    ok &= class_addbang(spGatomClass, (void*)gatom_bang);
    ok &= class_doaddfloat(spGatomClass, (void*)gatom_float);
    ok &= class_addsymbol(spGatomClass, (void*)gatom_symbol);
    s = gensym(&tmp, "set");
    ok &= class_addmethod(spGatomClass, (void*)gatom_set, *s, 9, 0);
    s = gensym(&tmp, "click");
    ok &= class_addalias(spGatomClass, (void*)gatom_click, *s, 1, 1, 1, 1, 1, 0);
    s = gensym(&tmp, "param");
    ok &= class_addmethod(spGatomClass, (void*)gatom_param, *s, 9, 0);
    class_setwidget(spGatomClass, &gatom_widgetbehavior);
    new_anything(spGatomClass, (void*)gatom_properties);
    return ok;
}

// @ 0xa51ae0
static void gatom_getwherelabel(t_gatom* x, t_glist* glist, int* xp, int* yp)
{
    int x1, y1, x2, y2;
    text_getrect(&x->a_text, glist, &x1, &y1, &x2, &y2);
    if (x->a_wherelabel == 0) {
        *xp = x1 - 3 - (int)strlen(canvas_realizedollar(x->a_glist, x->a_label).mpName) * sys_fontwidth(glist_getfont(glist));
        *yp = y1 + 2;
    }
    else if (x->a_wherelabel == 1) {
        *xp = x2 + 2;
        *yp = y1 + 2;
    }
    else if (x->a_wherelabel == 2) {
        *xp = x1 - 1;
        *yp = y1 - 1 - sys_fontheight(glist_getfont(glist));
    }
    else {
        *xp = x1 - 1;
        *yp = y2 + 3;
    }
}

// @ 0xa51bd0
void text_displace(t_text* x, t_glist* glist, int dx, int dy)
{
    x->te_xpix += dx;
    x->te_ypix += dy;
    if (glist_isvisible(glist)) {
        t_rtext* y = glist_findrtext(glist, x);
        rtext_displace(y, dx, dy);
        text_drawborder(x, glist, rtext_gettag(y), rtext_width(y), rtext_height(y), 0);
        canvas_fixlinesfor(glist_getcanvas(glist), x);
    }
}

static __forceinline int text_shouldvis(t_text* x, t_glist* glist)
{
    if (!glist->gl_havewindow) {
        if (x->te_g.g_pd != gpCanvasClass) {
            if (x->te_g.g_pd->c_wb != &text_widgetbehavior)
                goto out;
        }
        else {
            if (((t_glist*)x)->gl_isgraph)
                goto out;
        }
        if (!glist->gl_goprect)
            return 0;
        if (x->te_type == T_OBJECT)
            return 0;
    }
out:
    return 1;
}

// @ 0xa51c60
void text_select(t_text* x, t_glist* glist, int state)
{
    t_rtext* y = glist_findrtext(glist, x);
    rtext_select(y, state);
    if (glist_isvisible(glist) && text_shouldvis(x, glist))
        sys_gui(".x%lx.c itemconfigure %sR -fill %s\n", glist, rtext_gettag(y), (state ? "blue" : "black"));
}

// @ 0xa51cf0
void text_vis(t_text* x, t_glist* glist, int vis)
{
    if (vis) {
        if (text_shouldvis(x, glist)) {
            t_rtext* y = glist_findrtext(glist, x);
            if (x->te_type == T_ATOM)
                glist_retext(glist, x);
            text_drawborder(x, glist, rtext_gettag(y), rtext_width(y), rtext_height(y), 1);
            rtext_draw(y);
        }
    }
    else {
        if (text_shouldvis(x, glist)) {
            t_rtext* y = glist_findrtext(glist, x);
            text_eraseborder(x, glist, rtext_gettag(y));
            rtext_erase(y);
        }
    }
}

// @ 0xa51e20
void gatom_displace(t_gobj* z, t_glist* glist, int dx, int dy)
{
    text_displace((t_text*)z, glist, dx, dy);
    sys_gui(".x%lx.c move %lx.l %d %d\n", glist_getcanvas(glist), z, dx, dy);
}

// @ 0xa51e60
void gatom_vis(t_gobj* z, t_glist* glist, int vis)
{
    t_gatom* x = (t_gatom*)z;
    text_vis((t_text*)z, glist, vis);
    if (*x->a_label.mpName) {
        if (vis) {
            int x1, y1;
            t_symbol tmp;
            gatom_getwherelabel(x, glist, &x1, &y1);
            const char* name = canvas_realizedollar(x->a_glist, x->a_label).mpName;
            sys_gui("pdtk_text_new .x%lx.c %lx.l %f %f {%s} %d %s\n", glist_getcanvas(glist), x,
                    (double)x1, (double)y1, name,
                    sys_hostfontsize(glist_getfont(glist)), "black");
        }
        else
            sys_gui(".x%lx.c delete %lx.l\n", glist_getcanvas(glist), x);
    }
    if (!vis)
        sys_unqueuegui(x);
}

// @ 0xa51f40
bool graphics_objects_init()
{
    bool ok = true;
    ok &= g_canvas_setup();
    ok &= g_guiconnect_setup();
    ok &= FUN_00a618a0();
    ok &= g_text_setup();
    ok &= g_function_setup();
    ok &= g_bng_setup();
    ok &= g_toggle_setup();
    ok &= g_hslider_setup();
    ok &= g_vslider_setup();
    return ok;
}

// @ 0xa51f90
bool control_objects_init()
{
    bool ok = true;
    ok &= x_acoustics_setup();
    ok &= thunk_FUN_00a5ebe0();
    ok &= FUN_00a5c7c0();
    ok &= FUN_00a60470();
    ok &= x_arithmetic_setup();
    ok &= FUN_00a5da10();
    ok &= x_random_setup();
    ok &= FUN_00a4c610();
    ok &= FUN_00a5d5a0();
    ok &= x_input_setup();
    ok &= x_thisinstance_setup();
    ok &= FUN_00a598d0();
    ok &= FUN_00a5eb20();
    ok &= FUN_00a62e90();
    ok &= x_menu_setup();
    return ok;
}

// @ 0xa52000
bool audio_objects_init()
{
    bool ok = true;
    ok &= a_play_setup();
    ok &= a_group_setup();
    ok &= a_control_setup();
    return ok;
}

static inline float expf_(float x) { return (float)exp((double)x); }

// @ 0xa52020
double mtof(float f)
{
    if (f <= -1500)
        return 0;
    else if (f > 1499) {
        double r = mtof(1499);
        return r;
    }
    else
        return expf_(0.0577622650f * f) * 8.17579891564f;
}

}}}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct EA {
    void gpTextClass(...); // 0x016754f0
};
}
