// Shared declarations for the EA::Audio::Eapd (Pure Data) text / gatom / setup slice.
#pragma once
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

struct t_class;
struct t_glist;
struct t_rtext;
struct t_inlet;
struct t_outlet;
struct t_binbuf;
struct t_widgetbehavior;

// t_symbol is a by-value pair: hash, name pointer.
struct t_symbol {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};
// by-value return through a hidden pointer (non-POD)
struct t_symret : t_symbol {
    t_symret() {}
    t_symret(const t_symret& o) { mHash = o.mHash; mpName = o.mpName; }
};
struct t_atom {           // 12 bytes: type, symbol {hash, name}
    int      a_type;
    t_symbol a_w;
};

struct t_class {
    uint32_t          pad00[15];
    t_widgetbehavior* c_wb;   // +0x3c
};

struct t_gobj {
    t_class* g_pd;      // +0x00
    t_gobj*  g_next;    // +0x04
};

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
enum { T_TEXT = 0, T_OBJECT = 1, T_MESSAGE = 2, T_ATOM = 3 };

struct t_editor {
    uint32_t pad00[3];
    void*    e_textedfor;   // +0x0c
};

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

struct t_widgetbehavior;
extern t_widgetbehavior text_widgetbehavior;   // 0x1554364
extern t_widgetbehavior gatom_widgetbehavior;
extern t_class* gpTextClass;
extern t_class* gpCanvasClass;                 // 0x1675490
extern t_class* spMessageClass;
extern t_class* spMessresponderClass;
extern t_class* spGatomClass;

// externals
t_text* pd_checkobject(t_class** x);
int     obj_noutlets(t_text* x);        // 0xa4a0b0
int     obj_ninlets(t_text* x);         // 0xa4a0d0
t_glist* glist_getcanvas(t_glist* x);
void    glist_delete(t_glist* x, t_gobj* y);
void    glist_retext(t_glist* x, t_text* y);
int     glist_isvisible(t_glist* x);
t_rtext* glist_findrtext(t_glist* x, t_text* y);
void    canvas_fixlinesfor(t_glist* canvas, t_text* x);
void    canvas_restoreconnections(t_glist* x);
void    canvas_updatewindowlist();
void    canvas_objtext(int xpix, int ypix, int selected, t_binbuf* b);   // 0xa4f380 (register convention)
void    text_getrect(t_text* x, t_glist* glist, int* x1, int* y1, int* x2, int* y2);   // 0xa50ae0
t_symret canvas_realizedollar(t_glist* x, t_symbol s);
int     glist_getfont(t_glist* x);      // 0xa4ab90
int     sys_fontwidth(int font);        // 0xa4d2e0
int     sys_fontheight(int font);       // 0xa4d310
int     sys_hostfontsize(int font);     // 0xa4d2b0
void    rtext_displace(t_rtext* x, int dx, int dy);
int     rtext_height(t_rtext* x);
int     rtext_width(t_rtext* x);
const char* rtext_gettag(t_rtext* x);
void    rtext_select(t_rtext* x, int state);
void    rtext_draw(t_rtext* x);
void    rtext_erase(t_rtext* x);
void    sys_gui(const char* fmt, ...);
void    sys_unqueuegui(void* x);
t_binbuf* binbuf_new();
void    binbuf_free(t_binbuf* b);
void    binbuf_text(t_binbuf* b, const char* text, int size);
int     binbuf_getnatom(t_binbuf* b);   // 0x11838a0
t_atom* binbuf_getvec(t_binbuf* b);     // 0x11922c0
t_symbol* gensym(t_symbol* out, const char* s);
void    pd_typedmess(t_text* x, t_symbol s, int argc, t_atom* argv);
t_class* class_new(t_symbol name, void* newmethod, void* freemethod, int size, int flags, ...);
bool    class_addbang(t_class* c, void* fn);
bool    class_doaddfloat(t_class* c, void* fn);
bool    class_addsymbol(t_class* c, void* fn);
bool    class_addlist(t_class* c, void* fn);
bool    class_addanything(t_class* c, void* fn);
bool    class_addalias(t_class* c, void* fn, t_symbol name, ...);
bool    class_addmethod(t_class* c, void* fn, t_symbol name, ...);
void    class_setwidget(t_class* c, t_widgetbehavior* wb);    // 0xa47fb0
void    new_anything(t_class* c, void* fn);

// setup callees (other slices)
bool g_canvas_setup();
bool g_guiconnect_setup();
bool FUN_00a618a0();
bool g_function_setup();
bool g_bng_setup();
bool g_toggle_setup();
bool g_hslider_setup();
bool g_vslider_setup();
bool x_acoustics_setup();
bool thunk_FUN_00a5ebe0();
bool FUN_00a5c7c0();
bool FUN_00a60470();
bool x_arithmetic_setup();
bool FUN_00a5da10();
bool x_random_setup();
bool FUN_00a4c610();
bool FUN_00a5d5a0();
bool x_input_setup();
bool x_thisinstance_setup();
bool FUN_00a598d0();
bool FUN_00a5eb20();
bool FUN_00a62e90();
bool x_menu_setup();
bool a_play_setup();
bool a_group_setup();
bool a_control_setup();

// text/gatom/message methods defined elsewhere (addresses only)
void FUN_00a4fa30();
void message_bang();
void message_float();
void message_symbol();
void message_list();
void message_click();
void FUN_00a4f7b0();
void FUN_00a4f810();
void message_adddollar();
void message_adddollsym();
void message_addcomma();
void messresponder_symbol();
void messresponder_list();
void messresponder_anything();
void messresponder_bang();
void messresponder_float();
void gatom_free();
void gatom_bang();
void gatom_float();
void gatom_symbol();
void gatom_set();
void gatom_click();
void gatom_param();
void gatom_properties();
void LAB_00a4f7e0();
void LAB_00a4f840();

extern "C" int strcmp(const char*, const char*);
extern "C" unsigned int strlen(const char*);
extern "C" int sprintf(char*, const char*, ...);
extern "C" double exp(double);

}}}
