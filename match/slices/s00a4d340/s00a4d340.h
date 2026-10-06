// Shared declarations for the EA::Audio::Eapd (Pure Data) graph/canvas slice.
#pragma once
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

struct t_class;
struct t_glist;
struct t_rtext;
struct t_symbol;
struct t_inlet;
struct t_outlet;

struct t_gobj {
    t_class* g_pd;      // +0x00
    t_gobj*  g_next;    // +0x04
};

struct t_text {        // t_object
    t_gobj  te_g;       // +0x00
    uint32_t pad08[3];  // binbuf, outlet, inlet
    int16_t te_xpix;    // +0x14
    int16_t te_ypix;    // +0x16
    uint32_t pad18[4];
};

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

struct t_widgetbehavior {
    void (*w_getrectfn)(t_gobj*, t_glist*, int*, int*, int*, int*);   // +0x00
    void (*w_displacefn)(t_gobj*, t_glist*, int, int);                // +0x04
    void (*w_selectfn)(t_gobj*, t_glist*, int);                       // +0x08
    void (*w_activatefn)(t_gobj*, t_glist*, int);                     // +0x0c
    void (*w_deletefn)(t_gobj*, t_glist*);                            // +0x10
    void (*w_visfn)(t_gobj*, t_glist*, int);                          // +0x14
    int  (*w_clickfn)(t_gobj*, t_glist*, int, int, int, int, int, int); // +0x18
};

extern t_widgetbehavior text_widgetbehavior;   // 0x1554364
extern t_widgetbehavior graph_widgetbehavior;  // 0x1554348
extern t_class* gpVinletClass;                 // 0x167582c
extern t_class* gpVoutletClass;                // 0x1675830
extern t_class* gpCanvasClass;                 // 0x1675490
extern t_symbol* gEmptySymbol;
extern t_symbol* gInletSym;                    // 0x16758a0

// externals
t_text* pd_checkobject(t_class** x);
void    pd_free(void* x);
void*   getbytes(int n, const char* tag);
void    freebytes(void* p, int n);
int     glist_isvisible(t_glist* x);
int     glist_istoplevel(t_glist* x);
void    gobj_vis(t_gobj* x, t_glist* parent, int flag);
void    gobj_getrect(t_gobj* x, t_glist* g, int* x1, int* y1, int* x2, int* y2);
int     gobj_click(t_gobj* x, t_glist* g, int xpix, int ypix, int shift, int alt, int dbl, int doit);
void    gobj_delete(t_gobj* x, t_glist* g);
void    canvas_fixlinesfor(t_glist* parent, t_glist* x);
void    canvas_deletelinesforio(t_glist* parent, t_glist* x, t_inlet* i, t_outlet* o);
void    canvas_drawredrect(t_glist* x, int doit);
int     canvas_showtext(t_glist* x);
int     canvas_hitbox(t_glist* x, t_gobj* y, int xpos, int ypos, int* x1, int* y1, int* x2, int* y2);
void    canvas_setcursor(t_glist* x, unsigned int cursornum);
void    inlet_free(t_inlet* x);
void    outlet_free(t_outlet* x);
t_inlet*  inlet_new(t_glist* owner, t_class** dest, t_symbol* s1, t_symbol* s2, t_symbol* e, t_symbol* f);
t_outlet* outlet_new(t_glist* owner, t_symbol* s, t_symbol* c);
t_inlet*  FUN_00a617b0(t_gobj* y);
void    FUN_00a4a1e0(t_glist* x, t_inlet* i);
void    FUN_00a4a220(t_glist* x, t_outlet* o);
t_rtext* glist_findrtext(t_glist* x, t_text* y);
void    FUN_00a4ee20(t_rtext* rtext);
void    rtext_new(t_glist* x, t_text* ob);
void    rtext_select(t_rtext* r, int state);
const char* rtext_gettag(t_rtext* r);
void    sys_gui(const char* fmt, ...);
int     text_shouldvis(t_text* x, t_glist* g);
int     FUN_00a4c710(t_glist* x, t_gobj* y);
void    FUN_00a4d090(t_glist* x, t_gobj* y);
void    FUN_00a514d0(t_gobj* y, t_glist* x, const char* tag);
void    glist_eraseiofor(t_glist* x, t_gobj* y, const char* tag);
void    FUN_00a47fb0(t_class* c, void* wb);
void    graph_graphrect(t_gobj* z, t_glist* glist, int* xp1, int* yp1, int* xp2, int* yp2);
extern "C" int sprintf(char*, const char*, ...);

}}}
