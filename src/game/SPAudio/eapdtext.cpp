// src/game/SPAudio/eapdtext.cpp -- migrated from slice(s) s00a510e0, s00a4f1e0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdtext.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00a4f1e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol {               // by-value pair: hash at +0, name pointer at +4
    uint32_t    mHash;
    const char* mpName;
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_connection {
    t_connection* oc_next;      // +0
    void*         oc_to;        // +4: inlet the connection feeds
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outlet {
    uint32_t       pad00[2];
    t_connection*  o_connections;   // +0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gatom {
    uint32_t  pad00[3];         // te_g, te_binbuf
    t_outlet* a_outlet;         // +0x0c (te_outlet)
    uint32_t  pad10[6];         // +0x10 .. +0x27
    int       a_type;           // +0x28: 1 = float atom, 2 = symbol atom
    union {                     // +0x2c
        float    a_float;
        t_symbol a_symbol;      // +0x2c hash, +0x30 name
    };
    uint8_t   pad34[0x4c - 0x34];
    t_symbol* a_symfrom;        // +0x4c
    uint32_t  pad50;            // +0x50
    t_symbol* a_symto;          // +0x54
    uint8_t   pad58[0x88 - 0x58];
    uint32_t  a_sendA;          // +0x88
    uint32_t  a_sendB;          // +0x8c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern int gBangDepth;
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
void outlet_float(void* to, float f);                              // 0x00a49570
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void outlet_symbol(t_outlet* o, t_symbol s);                       // 0x00a49df0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void pd_send_float(uint32_t a, uint32_t b, float f);               // 0x00a67230
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void pd_send_symbol(uint32_t a, uint32_t b, t_symbol s);           // 0x00a67250
}
}
}
// ---- items of slice s00a4f1e0 end

// ---- items of slice s00a510e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct t_binbuf;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_widgetbehavior;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symret : t_symbol {
    t_symret() {}
    t_symret(const t_symret& o) { mHash = o.mHash; mpName = o.mpName; }
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom {           // 12 bytes: type, symbol {hash, name}
    int      a_type;
    t_symbol a_w;
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class {
    uint32_t          pad00[15];
    t_widgetbehavior* c_wb;   // +0x3c
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
struct t_text {        // t_object
    t_gobj    te_g;       // +0x00
    t_binbuf* te_binbuf;  // +0x08
    uint32_t  pad0c[2];   // outlet, inlet
    int16_t   te_xpix;    // +0x14
    int16_t   te_ypix;    // +0x16
    int       te_width;   // +0x18
    unsigned  te_type : 2; // +0x1c
    unsigned  pad1c : 30;
    uint32_t  pad20[2];
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
enum { T_TEXT = 0, T_OBJECT = 1, T_MESSAGE = 2, T_ATOM = 3 };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_editor {
    uint32_t pad00[3];
    void*    e_textedfor;   // +0x0c
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
    uint32_t  pad30[2];
    float     gl_x1;         // +0x38
    float     gl_y1;         // +0x3c
    float     gl_x2;         // +0x40
    float     gl_y2;         // +0x44
    uint32_t  pad48[6];
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
extern t_widgetbehavior text_widgetbehavior;   // 0x1554364
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* gpTextClass;   // 0x016754f0
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
t_text* pd_checkobject(t_class** x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     obj_noutlets(t_text* x);        // 0xa4a0b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     obj_ninlets(t_text* x);         // 0xa4a0d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_glist* glist_getcanvas(t_glist* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    glist_delete(t_glist* x, t_gobj* y);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    glist_retext(t_glist* x, t_text* y);
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
t_rtext* glist_findrtext(t_glist* x, t_text* y);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    canvas_fixlinesfor(t_glist* canvas, t_text* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    canvas_restoreconnections(t_glist* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    canvas_updatewindowlist();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    canvas_objtext(int xpix, int ypix, int selected, t_binbuf* b);   // 0xa4f380 (register convention)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    text_getrect(t_text* x, t_glist* glist, int* x1, int* y1, int* x2, int* y2);   // 0xa50ae0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symret canvas_realizedollar(t_glist* x, t_symbol s);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     glist_getfont(t_glist* x);      // 0xa4ab90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     sys_fontwidth(int font);        // 0xa4d2e0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     sys_fontheight(int font);       // 0xa4d310
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     sys_hostfontsize(int font);     // 0xa4d2b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    rtext_displace(t_rtext* x, int dx, int dy);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     rtext_height(t_rtext* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     rtext_width(t_rtext* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
const char* rtext_gettag(t_rtext* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    rtext_select(t_rtext* x, int state);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    rtext_draw(t_rtext* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    rtext_erase(t_rtext* x);
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
void    sys_unqueuegui(void* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_binbuf* binbuf_new();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    binbuf_free(t_binbuf* b);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    binbuf_text(t_binbuf* b, const char* text, int size);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     binbuf_getnatom(t_binbuf* b);   // 0x11838a0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_atom* binbuf_getvec(t_binbuf* b);     // 0x11922c0
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
void    pd_typedmess(t_text* x, t_symbol s, int argc, t_atom* argv);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern "C" int strcmp(const char*, const char*);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern "C" unsigned int strlen(const char*);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_widgetbehavior {
    void (*w_getrectfn)(t_gobj*, t_glist*, int*, int*, int*, int*);
    void (*w_displacefn)(t_gobj*, t_glist*, int, int);
    void (*w_selectfn)(t_gobj*, t_glist*, int);
    void (*w_activatefn)(t_gobj*, t_glist*, int);
    void (*w_deletefn)(t_gobj*, t_glist*);
    void (*w_visfn)(t_gobj*, t_glist*, int);
    int  (*w_clickfn)(t_gobj*, t_glist*, int, int, int, int, int, int);
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gatom_s00a5_10e0 {
    t_text   a_text;         // +0x00
    uint32_t pad28[3];
    t_glist* a_glist;        // +0x34
    uint32_t pad38[3];
    t_symbol a_label;        // +0x44
    uint8_t  pad4c[0x85 - 0x4c];
    char     a_wherelabel;   // +0x85
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
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
}
}
}
// ---- items of slice s00a510e0 end

// @ 0x00a4fdb0
namespace EA { namespace Audio { namespace Eapd {
void gatom_bang(t_gatom* x)
{
    if (x->a_type == 1) {
        t_outlet* o = x->a_outlet;
        if (o) {
            float f = x->a_float;
            if (++gBangDepth < 1000) {
                for (t_connection* c = o->o_connections; c; c = c->oc_next)
                    outlet_float(c->oc_to, f);
            }
            --gBangDepth;
        }
        if (gEmptySymbol != x->a_symto && x->a_symto != x->a_symfrom)
            pd_send_float(x->a_sendA, x->a_sendB, x->a_float);
    } else if (x->a_type == 2) {
        if (x->a_outlet)
            outlet_symbol(x->a_outlet, x->a_symbol);
        if (gEmptySymbol != x->a_symto && x->a_symto != x->a_symfrom)
            pd_send_symbol(x->a_sendA, x->a_sendB, x->a_symbol);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a510e0
namespace EA { namespace Audio { namespace Eapd {
void glist_drawiofor(t_glist* glist, t_text* ob, int firsttime, const char* tag, int x1, int y1, int x2, int y2)
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a51240
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a51450
namespace EA { namespace Audio { namespace Eapd {
void glist_eraseiofor(t_glist* glist, t_text* ob, const char* tag)
{
    int i, n = obj_noutlets(ob);
    for (i = 0; i < n; i++)
        sys_gui(".x%lx.c delete %so%d\n", glist_getcanvas(glist), tag, i);
    n = obj_ninlets(ob);
    for (i = 0; i < n; i++)
        sys_gui(".x%lx.c delete %si%d\n", glist_getcanvas(glist), tag, i);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a514d0
namespace EA { namespace Audio { namespace Eapd {
void text_eraseborder(t_text* x, t_glist* glist, const char* tag)
{
    if (x->te_type != T_TEXT) {
        sys_gui(".x%lx.c delete %sR\n", glist_getcanvas(glist), tag);
        glist_eraseiofor(glist, x, tag);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a51510
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a51ae0
namespace EA { namespace Audio { namespace Eapd {
static void gatom_getwherelabel(t_gatom_s00a5_10e0* x, t_glist* glist, int* xp, int* yp)
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a51bd0
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a51c60
namespace EA { namespace Audio { namespace Eapd {
void text_select(t_text* x, t_glist* glist, int state)
{
    t_rtext* y = glist_findrtext(glist, x);
    rtext_select(y, state);
    if (glist_isvisible(glist) && text_shouldvis(x, glist))
        sys_gui(".x%lx.c itemconfigure %sR -fill %s\n", glist, rtext_gettag(y), (state ? "blue" : "black"));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a51cf0
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a51e20
namespace EA { namespace Audio { namespace Eapd {
void gatom_displace(t_gobj* z, t_glist* glist, int dx, int dy)
{
    text_displace((t_text*)z, glist, dx, dy);
    sys_gui(".x%lx.c move %lx.l %d %d\n", glist_getcanvas(glist), z, dx, dy);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a51e60
namespace EA { namespace Audio { namespace Eapd {
void gatom_vis(t_gobj* z, t_glist* glist, int vis)
{
    t_gatom_s00a5_10e0* x = (t_gatom_s00a5_10e0*)z;
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
}}}  // namespace EA::Audio::Eapd
