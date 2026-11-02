// src/game/SPAudio/eapdtext.cpp -- migrated from slice(s) s00a50150, s00a510e0, s00a4f1e0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdtext.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00a4f1e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gpTextClass;           // 0x16754f0 the "comment" text class
extern void* gpNewestObject;        // 0x16753f4 last object created by an eval
extern void* gpObjTextPd;           // 0x16753e8 eval target used by canvas_objtext
extern void* gpTextInletClass;      // 0x167582c
extern void* gpTextOutletClass;     // 0x1675830
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef signed short   i16;
typedef signed int     i32;
struct Glist;                       // opaque canvas/glist
struct t_symbol {
    u32         mHash;              // +0x00
    const char* mpName;             // +0x04
};
struct t_atom_s00a4_f1e0 {
    u32 a_type;                     // +0x00
    union {
        float    a_float;           // +0x04
        i32      a_int;             // +0x04
        t_symbol a_symbol;          // +0x04 hash, +0x08 name
    } a_w;
};
struct Text {
    void*  pClass;                  // +0x00 class pointer
    void*  te_outlet;               // +0x04
    void*  te_binbuf;               // +0x08
    u32    pad0c;                   // +0x0c
    u32    pad10;                   // +0x10
    i16    te_xpix;                 // +0x14
    i16    te_ypix;                 // +0x16
    i16    te_w;                    // +0x18
    char   pad1a[2];                // +0x1a
    u32    te_flags;                // +0x1c
    u32    pad20;                   // +0x20
    u32    pad24;                   // +0x24
    void*  te_pd;                   // +0x28 receiver object
    void*  te_msgout;               // +0x2c
    void*  te_glist;                // +0x30
    void*  te_clock;                // +0x34
};
struct Gatom {
    void*  pClass;                  // +0x00 class pointer
    void*  te_outlet;               // +0x04
    void*  te_binbuf;               // +0x08
    u32    pad0c;                   // +0x0c
    u32    pad10;                   // +0x10
    i16    te_xpix;                 // +0x14
    i16    te_ypix;                 // +0x16
    i16    te_w;                    // +0x18
    char   pad1a[2];                // +0x1a
    u32    te_flags;                // +0x1c
    u32    pad20;                   // +0x20
    u32    pad24;                   // +0x24
    t_atom_s00a4_f1e0 a_atom;                  // +0x28
    void*  a_glist;                 // +0x34
    u32    pad38;                   // +0x38
    float  a_max;                   // +0x3c
    float  a_min;                   // +0x40
    char   pad44[0x18];             // +0x44
    u8     a_dirty;                 // +0x5c
    char   pad5d[0x27];             // +0x5d
    u8     a_grabbed;               // +0x84

    void clipfloat(float f);        // (0x00a4ff10)
};
extern t_symbol gEmptySymbol;       // 0x167589c
void*     pd_new(void* cls);                                            // 0x00a49390
void*     binbuf_new_s00a4_f1e0(void);                                             // 0x00a46c20
void      binbuf_clear(void* b);                                        // 0x00a46c80
void      binbuf_add(void* b, int argc, t_atom_s00a4_f1e0* argv);                  // 0x00a471a0
void      binbuf_addsemi(void* b);                                      // 0x00a47540
void      binbuf_addtext(void* b, int argc, t_atom_s00a4_f1e0* argv);              // 0x00a47570
void      binbuf_eval(void* b, void* target, int argc, t_atom_s00a4_f1e0* argv);   // 0x00a478b0
void      binbuf_gettextbuf(void* b, char* buf, int n);                 // 0x00a47780
float     atom_getfloat_at(int n, int argc, t_atom_s00a4_f1e0* argv);              // 0x00a468f0
int       atom_getint_at(int n, int argc, t_atom_s00a4_f1e0* argv);                // 0x00a46920
float     atom_getfloat(t_atom_s00a4_f1e0* a);                                     // 0x00a46760
t_symbol* atom_getsymbol(t_symbol* out, t_atom_s00a4_f1e0* a);                     // 0x00a46790
void      glist_add(void* gl, void* obj);                               // 0x00a4d340
void*     glist_getcanvas(void* gl);                                    // 0x00a4d410
void      glist_retext(void* gl, void* obj);                            // 0x00a4d3e0
void      glist_noselect(void* gl);                                     // 0x00a4d1d0
void      glist_select(void* gl, void* obj);                            // 0x00a4c740
int       glist_isvisible(void* gl);                                    // 0x00a4ab40
void*     glist_findrtext(void* gl, void* obj);                         // 0x00a4efb0
void*     rtext_gettag(void* rtext);                                    // 0x00a4e990
void      canvas_startmotion(void* gl);                                 // 0x00a4d230
int       canvas_getlastxy(void* gl, int* x, int* y);                   // 0x00a4cfb0
void      canvas_resortinlets(void* gl);                                // 0x00a4d4d0
void      canvas_resortoutlets(void* gl);                               // 0x00a4d6a0
void      pd_pushsym(void);                                             // 0x00a4a470
void      pd_popsym(void);                                              // 0x00a4a480
void      canvas_getargs(int* argc, int* argv);                         // 0x00a4a500
void*     pd_checkobject(void* cls);                                    // 0x00a4a1c0
void      pd_vmess(void* target, t_symbol s, const char* fmt, ...);     // 0x00a487f0
t_symbol* gensym(t_symbol* buf, const char* name);                      // 0x00a675f0
void      outlet_symbol(void* o, t_symbol s);                           // 0x00a49df0
void      clock_free(void* c);                                          // 0x00a49260
void      clock_delay(void* c, float f);                                // 0x00a491e0
void      gatom_bang(Gatom* x);                                         // 0x00a4fdb0 (other slice)
void      sys_gui(void* a, void* b, void* c);                           // 0x00c2e4e0
int       FUN_011838a0(void* p);                                        // 0x011838a0
void      FUN_00a4c690(void* obj, void* gl, int f);                     // 0x00a4c690
double    iat_floor(double d);                                          // 0x011e0906
char*     strncpy_imp(char* d, const char* s, int n);                   // msvcr90 strncpy
static t_symbol gGensymScratch;     // per-call name scratch, as in Pd's gensym
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

// ---- items of slice s00a50150 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class_s00a5_0150;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gobj_s00a5_0150;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_glist_s00a5_0150;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol_s00a5_0150 {
    void* s_name;    // +0
    void* s_thing;   // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct sympair {
    void* name;      // +0
    void* thing;     // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class_s00a5_0150 {
    void* c_name;         // +0
    void* c_helpname;     // +4
    void* c_helpdir;      // +8
    char  pad0[0x10 - 0xc];
    void* c_filetypes;    // +0x10
    void* c_filedefault;  // +0x14
    unsigned c_size;      // +0x18
    void* c_methods;      // +0x1c
    int   c_nmethod;      // +0x20
    void* c_freemethod;   // +0x24
    void* c_bangmethod;   // +0x28
    void* c_floatmethod;  // +0x2c
    void* c_symbolmethod; // +0x30
    void* c_listmethod;   // +0x34
    void* c_anymethod;    // +0x38
    void* c_wb;           // +0x3c
    void* c_savefn;       // +0x40
    void* c_propertiesfn; // +0x44
    char  c_gobj;         // +0x48
    char  c_patchable;    // +0x49
    char  c_firstin;      // +0x4a
    t_class_s00a5_0150* c_next;      // +0x4c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gobj_s00a5_0150 {
    t_class_s00a5_0150* g_pd;    // +0
    t_gobj_s00a5_0150*  g_next;  // +4
    char pad[0x24 - 8];
    void*    o_save;  // +0x24
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom_s00a5_0150 {
    int   a_type;    // +0
    float a_w;       // +4
    float a_w2;      // +8
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_glist_s00a5_0150 {
    t_gobj_s00a5_0150   g_gobj;          // +0
    void*    g_pd;            // +0x24   (t_glist's own gobj pd pointer reused here)
    void*    gl_list;         // +0x28
    t_glist_s00a5_0150* gl_owner;        // +0x2c
    char pad3[0x60 - 0x30];
    void*    gl_editor;       // +0x60
    void*    gl_name_a;       // +0x64
    void*    gl_name_b;       // +0x68
    char pad7[0x74 - 0x6c];
    void*    gl_symtag;       // +0x74
    unsigned gl_flags;        // +0x78
    char pad8[0x80 - 0x7c];
    void*    gl_bind;         // +0x80
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gatom_s00a5_0150 {
    void*    g_pd;           // +0
    void*    g_next;         // +4
    void*    a_binbuf;       // +8     binbuf for the current editor text
    void*    a_inlet;        // +0xc
    void*    a_outlet;       // +0x10
    short    a_x1;           // +0x14
    short    a_y1;           // +0x16
    short    a_w;            // +0x18   width/height in chars
    unsigned a_flags;        // +0x1c
    char     pad2[0x28 - 0x20];
    int      a_type;         // +0x28   1=float 2=symbol 3=int
    sympair  a_value;        // +0x2c   value: float word, or a (name,thing) symbol pair
    void*    a_canvas;       // +0x34
    float    a_saved_value;  // +0x38
    float    a_lower;        // +0x3c
    float    a_upper;        // +0x40
    t_symbol_s00a5_0150 a_rcv_sym;      // +0x44   (stored as two words: name,thing)
    t_symbol_s00a5_0150 a_rcv_lab;      // +0x4c
    t_symbol_s00a5_0150 a_snd_sym;      // +0x54
    char     a_text[0x84 - 0x5c]; // +0x5c   in-place editor text buffer
    char     a_shift;        // +0x84
    char     a_where;        // +0x85
    t_symbol_s00a5_0150 a_send;         // +0x88
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_0150 gEmptySymbol_s00a5_0150;    // 0x167589c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_0150 gSymSymbol;      // 0x1675894
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_0150 gFloatSymbol;    // 0x16758c4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern void*    gSymSymbolThing; // 0x1675898
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern void*    gFloatSymbolThing;// 0x16758c8
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern void*    gEmptyThing;     // 0x16758a0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class_s00a5_0150* gpGatomClass;    // 0x16754f4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class_s00a5_0150* gpCanvasClass_s00a5_0150;   // 0x1675490
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern void*    gAtomWidgetBehavior; // 0x1554364 (text/atom widgetbehavior, compared in text_shouldvis)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   strlen_i(const char* s);                                                       // inlined
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   sprintf_i(char* d, const char* fmt, ...);                                      // inlined (msvcr90 sprintf)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
double atof_i(const char* s);                                                        // inlined (msvcr90 atof)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* gensym(t_symbol_s00a5_0150* out, const char* s);                                          // 0xa675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* pd_new(t_class_s00a5_0150* c);                                                            // 0xa49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* binbuf_new_s00a5_0150();                                                                  // 0xa46c20
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  binbuf_clear(void* b);                                                         // 0xa46c80
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  binbuf_addv(void* b, const char* fmt, ...);                                    // 0xa47220
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  FUN_00a471a0(void* b, int n, ...);                                             // 0xa471a0 (binbuf_add atoms)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  FUN_00a47350(void* b, void* s);                                                // 0xa47350 (binbuf_add one atom)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* gatom_unescapit(void* a, void* b);                                             // 0xa4fc50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* gatom_escapit(void* a, void* b);                                               // 0xa4fba0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  gatom_float(int g, float v);                                                   // 0xa4fe90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  gatom_bang(int g);                                                             // (called)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  gatom_retext(int g);                                                           // (called)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  message_click(int x, float a, float b, float c, float d, float e);             // 0xa4f950
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  glist_grab(t_glist_s00a5_0150* g, void* o, void* fn, void* keyfn, int x, int y);          // 0xa4dfb0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  glist_noselect(t_glist_s00a5_0150* g);                                                    // 0xa4d1d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   glist_isvisible(t_glist_s00a5_0150* g);                                                   // 0xa4ab40
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_glist_s00a5_0150* glist_getcanvas_s00a5_0150(t_glist_s00a5_0150* g);                                                // 0xa4d410
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  glist_add(t_glist_s00a5_0150* g, void* o);                                                // 0xa4d340
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  gobj_vis(void* o, t_glist_s00a5_0150* g, int vis);                                        // 0xa4d3e0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  canvas_deletelinesforio(t_glist_s00a5_0150* g, void* a, void* b, void* c);                // 0xa4b2f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  canvas_getlastxy(t_glist_s00a5_0150* g, int* x, int* y);                                  // 0xa4cfb0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  canvas_startmotion(t_glist_s00a5_0150* g);                                                // 0xa4d230
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  canvas_select(t_glist_s00a5_0150* g, void* o);                                            // 0xa4c740
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_bind(void* obj, void* a, void* b);                                          // 0xa67620
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_vmess(void* obj, void* sel_a, void* sel_b, const char* fmt, ...);           // 0xa487f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* zgetfn(void* obj, void* sel_a, void* sel_b);                                   // 0xa488d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* FUN_00a48890(void* obj, void* a, void* b);                                     // (zgetfn variant)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* outlet_new(void* o, void* a, void* b);                                         // 0xa49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* inlet_new(void* o, void* a, void* b, void* c, void* d, void* e);               // 0xa49740
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  inlet_free(void* o);                                                           // 0xa49f20
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  outlet_free(void* o);                                                          // 0xa49f20
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* canvas_realizedollar(void** out, void* env, void* a3, const char* s);          // 0xa4a550
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   obj_ninlets(t_gobj_s00a5_0150* o);                                                        // 0xa4a0d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   obj_noutlets(t_gobj_s00a5_0150* o);                                                       // 0xa4a0b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   atom_getint_at(int i, int n, t_atom_s00a5_0150* a);                                       // 0xa46920
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
float atom_getfloat_at(int i, int n, t_atom_s00a5_0150* a);                                     // 0xa468f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* FUN_00a46950(void* out, int i, int n, t_atom_s00a5_0150* a);                              // 0xa46950
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
short FUN_011e0810(float v);                                                         // 0x11e0810
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  gfxstub_new(void* key, void* arg, const char* s);                              // 0xa4c470
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  gfxstub_deleteforkey(void* key);                                               // 0xa4c170
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  sys_vgui_sym(unsigned a, unsigned b, unsigned c);                              // 0xa671b0 (sel/obj form)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* glist_findrtext(t_glist_s00a5_0150* g, void* o);                                          // 0xa4efb0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   rtext_width(void* r);                                                          // 0xa4efd0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   rtext_height(void* r);                                                         // 0xa4f010
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  rtext_activate(void* r, int v);                                                // 0xa4f130
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   text_xpix(void* o, t_glist_s00a5_0150* g);                                                // 0xa4d920
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   text_ypix(void* o, t_glist_s00a5_0150* g);                                                // 0xa4d9c0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   sys_fontextra(int f);                                                          // 0xa4d310
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* canvas_gettext(t_glist_s00a5_0150* g);                                                    // 0xa4ab90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   canvas_isopen(t_glist_s00a5_0150* g);                                                     // 0xa4ad50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   canvas_istable(t_glist_s00a5_0150* g);                                                    // 0xa4ad60
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  canvas_symbolatom(void* a, void* b, void* c, void* d, void* e, void* f);       // forward
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  FUN_00a50600(int g, int type, void* canvas, void* o, int argc, void* atoms);   // canvas_atom
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* FUN_00a4fce0(void);                                                            // key handler
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* FUN_00a4fff0(void);                                                            // motion handler
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  gatom_key(int g, float v);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gSavetoStr[];   // 0x1454bd0 "saveto"
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gRestoreStr[];  // 0x14546b0 "restore"
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gHashXStr[];    // 0x1454858 "#X"
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gObjStr[];      // 0x14546a4 "obj"
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gMsgStr[];      // 0x14546a0 "msg"
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gTextStr[];     // 0x1408a0c "text"
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gSemicolonStr[];// 0x13fb1c0 ";"
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gSymbolatomStr[];   // 0x1454688 "symbolatom"
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gFloatatomStr[];    // 0x1454694 "floatatom"
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gIntatomStr[];      // 0x1454bc0 "intatom"
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gSsiiStr[];         // 0x1454bc8 "ssii"
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gSsiiifffsssStr[];  // 0x1454bb4 "ssiiifffsss"
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gClickStr[];        // 0x145465c "click"
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gFffffStr[];        // 0x1454bac "fffff"
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gDotsStr[];         // 0x1454b78 "%s..."
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gEditmodeStr[];     // 0x1454b1c "editmode"
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gIStr[];            // 0x1433620 "i"
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const char gGatomDialogFmt[];  // 0x1454b80
}
}
}
// ---- items of slice s00a50150 end

// @ 0x00a4f1e0
void glist_text(Glist* gl, t_symbol s, int argc, t_atom_s00a4_f1e0* argv)
{
    (void)s;
    t_atom_s00a4_f1e0 a;
    t_symbol scratch;
    int ypos;
    int xpos;
    Text* x = (Text*)pd_new(gpTextClass);
    if (x == 0)
        return;
    x->te_flags &= 0xfffffffc;
    x->te_w = 0;
    x->te_binbuf = binbuf_new_s00a4_f1e0();
    if (argc > 1)
    {
        x->te_xpix = (i16)atom_getfloat_at(0, argc, argv);
        x->te_ypix = (i16)atom_getfloat_at(1, argc, argv);
        if (argc > 2)
        {
            binbuf_addtext(x->te_binbuf, argc - 2, argv + 2);
            glist_add(gl, x);
            return;
        }
        a.a_type = 2;
        a.a_w.a_symbol = *gensym(&scratch, "comment");
        binbuf_addtext(x->te_binbuf, 1, &a);
        glist_add(gl, x);
        return;
    }
    {
        t_symbol* sp = gensym(&scratch, "editmode");
        pd_vmess(glist_getcanvas(gl), *sp, "i", 1);
    }
    a.a_type = 2;
    a.a_w.a_symbol = *gensym(&scratch, "comment");
    glist_noselect(gl);
    canvas_getlastxy(gl, &xpos, &ypos);
    x->te_xpix = (i16)(xpos - 1);
    x->te_ypix = (i16)(ypos - 1);
    binbuf_addtext(x->te_binbuf, 1, &a);
    glist_add(gl, x);
    glist_noselect(gl);
    glist_select(gl, x);
    canvas_startmotion(glist_getcanvas(gl));
}

// @ 0x00a4f380
void canvas_objtext(Glist* gl, void* b, i16 xpix, i16 ypix, int created)
{
    Text* x = 0;
    gpNewestObject = 0;
    pd_pushsym();
    int argc = 0;
    t_atom_s00a4_f1e0* argv = 0;
    canvas_getargs(&argc, (int*)&argv);
    binbuf_eval(b, gpObjTextPd, argc, argv);
    if (FUN_011838a0(b) != 0)
    {
        if (gpNewestObject != 0)
            x = (Text*)pd_checkobject(gpNewestObject);
        if (x == 0)
        {
            char buf[1000];
            binbuf_gettextbuf(b, buf, 1000);
        }
    }
    if (x == 0)
        x = (Text*)pd_new(gpTextClass);
    x->te_xpix = xpix;
    x->te_binbuf = b;
    x->te_ypix = ypix;
    x->te_w = 0;
    x->te_flags = (x->te_flags & 0xfffffffd) | 1;
    glist_add(gl, x);
    if (created)
    {
        glist_select(gl, x);
        FUN_00a4c690(x, gl, 1);
    }
    if (x->pClass == gpTextInletClass)
        canvas_resortinlets(glist_getcanvas(gl));
    if (x->pClass == gpTextOutletClass)
        canvas_resortoutlets(glist_getcanvas(gl));
    pd_popsym();
}

// @ 0x00a4f4b0
void canvas_obj(Glist* gl, t_symbol s, int argc, t_atom_s00a4_f1e0* argv)
{
    (void)s;
    void* b = binbuf_new_s00a4_f1e0();
    if (argc >= 2)
    {
        binbuf_addtext(b, argc - 2, argv + 2);
        canvas_objtext(gl, b,
                       (i16)atom_getint_at(0, argc, argv),
                       (i16)atom_getint_at(1, argc, argv), 0);
        return;
    }
    if (argc == 1 && argv[0].a_type == 2)
        binbuf_addtext(b, 1, argv);
    {
        t_symbol sym = *gensym(&gGensymScratch, "editmode");
        pd_vmess(gl, sym, "i", 1);
    }
    glist_noselect(gl);
    int lx = 0, ly = 0;
    canvas_getlastxy(gl, &lx, &ly);
    canvas_objtext(gl, b, (i16)lx, (i16)ly, 1);
    canvas_startmotion(glist_getcanvas(gl));
}

// @ 0x00a4f590
void canvas_objfor(Glist* gl, Text* x, int argc, t_atom_s00a4_f1e0* argv)
{
    x->te_w = 0;
    x->te_flags = (x->te_flags & 0xfffffffd) | 1;
    x->te_binbuf = binbuf_new_s00a4_f1e0();
    x->te_xpix = (i16)atom_getfloat_at(0, argc, argv);
    x->te_ypix = (i16)atom_getfloat_at(1, argc, argv);
    if (argc > 2)
        binbuf_addtext(x->te_binbuf, argc - 2, argv + 2);
    glist_add(gl, x);
}

// @ 0x00a4f670
void messresponder_symbol(Text* x, t_symbol s)
{
    outlet_symbol(x->te_outlet, s);
}

// @ 0x00a4f6f0
void message_bang(Text* x)
{
    binbuf_eval(x->te_binbuf, (void*)&x->te_pd, 0, 0);
}

// @ 0x00a4f710
void message_float(Text* x, float f)
{
    t_atom_s00a4_f1e0 a;
    a.a_type = 1;
    a.a_w.a_float = f;
    binbuf_eval(x->te_binbuf, (void*)&x->te_pd, 1, &a);
}

// @ 0x00a4f750
void message_symbol(Text* x, t_symbol s)
{
    t_atom_s00a4_f1e0 a;
    a.a_type = 2;
    a.a_w.a_symbol = s;
    binbuf_eval(x->te_binbuf, (void*)&x->te_pd, 1, &a);
}

// @ 0x00a4f790
void message_list(Text* x, t_symbol s, int argc, t_atom_s00a4_f1e0* argv)
{
    (void)s;
    binbuf_eval(x->te_binbuf, (void*)&x->te_pd, argc, argv);
}

// @ 0x00a4f7b0
void message_set(Text* x, t_symbol s, u32 p4, int argc, t_atom_s00a4_f1e0* argv)
{
    (void)s; (void)p4;
    binbuf_clear(x->te_binbuf);
    binbuf_add(x->te_binbuf, argc, argv);
    glist_retext(x->te_glist, x);
}

// @ 0x00a4f810
void message_add2(Text* x, t_symbol s, int argc, t_atom_s00a4_f1e0* argv)
{
    (void)s;
    binbuf_add(x->te_binbuf, argc, argv);
    binbuf_addsemi(x->te_binbuf);
    glist_retext(x->te_glist, x);
}

// @ 0x00a4f880
void message_addcomma(Text* x)
{
    binbuf_add(x->te_binbuf, 0, 0);
    binbuf_addsemi(x->te_binbuf);
    glist_retext(x->te_glist, x);
}

// @ 0x00a4f8b0
void message_adddollar(Text* x, float f)
{
    t_atom_s00a4_f1e0 a;
    i32 i = (i32)f;
    if (i < 0)
        i = 0;
    a.a_type = 7;
    a.a_w.a_int = i;
    binbuf_add(x->te_binbuf, 1, &a);
    glist_retext(x->te_glist, x);
}

// @ 0x00a4f900
void message_adddollsym(Text* x, t_symbol s)
{
    t_atom_s00a4_f1e0 a;
    a.a_type = 8;
    a.a_w.a_symbol = s;
    binbuf_add(x->te_binbuf, 1, &a);
    glist_retext(x->te_glist, x);
}

// @ 0x00a4f950
void message_click(Text* x)
{
    t_atom_s00a4_f1e0 a;
    a.a_type = 1;
    a.a_w.a_float = 0.0f;
    binbuf_eval(x->te_binbuf, (void*)&x->te_pd, 1, &a);
    if (!glist_isvisible(x->te_glist))
        return;
    sys_gui((void*)".x%lx.c itemconfigure %sR -width 5\n",
            glist_getcanvas(x->te_glist),
            rtext_gettag(glist_findrtext(x->te_glist, x)));
    clock_delay(x->te_clock, 120.0f);
}

// @ 0x00a4f9e0
void message_tick(Text* x)
{
    if (!glist_isvisible(x->te_glist))
        return;
    sys_gui((void*)".x%lx.c itemconfigure %sR -width 1\n",
            glist_getcanvas(x->te_glist),
            rtext_gettag(glist_findrtext(x->te_glist, x)));
}

// @ 0x00a4fa30
void clock_free_msg(Text* x)
{
    clock_free(x->te_clock);
}

// @ 0x00a4fba0
t_symbol gatom_escapit(u32 w0, const char* name)
{
    t_symbol r;
    r.mHash = w0;
    r.mpName = name;
    if (w0 == gEmptySymbol.mHash)
    {
        r = *gensym(&gGensymScratch, "-");
        return r;
    }
    char c = *name;
    if (c == '-')
    {
        char buf[1000];
        buf[0] = '-';
        strncpy_imp(buf + 1, name, 999);
        buf[999] = 0;
        r = *gensym(&gGensymScratch, buf);
        return r;
    }
    if (c != '$')
        return r;
    {
        char buf[1000];
        strncpy_imp(buf, name, 1000);
        buf[999] = 0;
        buf[0] = '#';
        r = *gensym(&gGensymScratch, buf);
    }
    return r;
}

// @ 0x00a4fc50
t_symbol gatom_unescapit(u32 w0, const char* name)
{
    t_symbol r;
    r.mHash = w0;
    r.mpName = name;
    char c = *name;
    if (c == '-')
    {
        r = *gensym(&gGensymScratch, name + 1);
        return r;
    }
    if (c == '#')
    {
        char buf[1000];
        strncpy_imp(buf, name, 1000);
        buf[999] = 0;
        buf[0] = '$';
        r = *gensym(&gGensymScratch, buf);
    }
    return r;
}

// @ 0x00a4fce0
void FUN_00a4fce0(Gatom* x)
{
    glist_retext(x->a_glist, x);
}

// @ 0x00a4fd00
void gatom_retext(Gatom* x, int flag)
{
    binbuf_clear(x->te_binbuf);
    binbuf_add(x->te_binbuf, 1, &x->a_atom);
    if (flag != 0 && glist_isvisible(x->a_glist) != 0)
        sys_gui((void*)x, x->a_glist, (void*)FUN_00a4fce0);
}

// @ 0x00a4fd50
void gatom_set(Gatom* x, t_symbol s, int argc, t_atom_s00a4_f1e0* argv)
{
    (void)s;
    if (argc == 0)
        return;
    if (x->a_atom.a_type == 1)
    {
        x->a_atom.a_w.a_float = atom_getfloat(argv);
        x->a_dirty = 0;
        return;
    }
    if (x->a_atom.a_type == 2)
    {
        t_symbol buf;
        x->a_atom.a_w.a_symbol = *atom_getsymbol(&buf, argv);
    }
    x->a_dirty = 0;
}

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

// @ 0x00a4fe90
void gatom_float(Gatom* x, float f)
{
    t_atom_s00a4_f1e0 a;
    a.a_type = 1;
    a.a_w.a_float = f;
    if (x->a_atom.a_type == 1)
    {
        x->a_atom.a_w.a_float = atom_getfloat(&a);
        x->a_dirty = 0;
        gatom_bang(x);
        return;
    }
    if (x->a_atom.a_type == 2)
    {
        t_symbol buf;
        x->a_atom.a_w.a_symbol = *atom_getsymbol(&buf, &a);
    }
    x->a_dirty = 0;
    gatom_bang(x);
}

// @ 0x00a4ff10
void Gatom::clipfloat(float f)
{
    float lo = a_min;                       // +0x40
    if (lo != 0.0f || a_max != 0.0f)        // +0x3c
    {
        if (f < lo)
            f = lo;
        if (f > a_max)
            f = a_max;
    }
    gatom_float(this, f);
}

// @ 0x00a4ff70
void gatom_symbol(Gatom* x, t_symbol s)
{
    t_atom_s00a4_f1e0 a;
    a.a_type = 2;
    a.a_w.a_symbol = s;
    if (x->a_atom.a_type == 1)
    {
        x->a_atom.a_w.a_float = atom_getfloat(&a);
        x->a_dirty = 0;
        gatom_bang(x);
        return;
    }
    if (x->a_atom.a_type == 2)
    {
        t_symbol buf;
        x->a_atom.a_w.a_symbol = *atom_getsymbol(&buf, &a);
    }
    x->a_dirty = 0;
    gatom_bang(x);
}

// @ 0x00a4fff0
void gatom_motion(Gatom* x, float dx, float dy)
{
    (void)dx;
    if (dy == 0.0f)
        return;
    if (x->a_atom.a_type != 1)
        return;
    float v;
    if (x->a_grabbed == 0)
    {
        v = x->a_atom.a_w.a_float - dy;
        float snapped = (float)iat_floor((double)(v * 100.0f + 0.5f)) * 0.01f;
        if (snapped < v + 0.0001f && v - 0.0001f < snapped)
            v = snapped;
        iat_floor((double)(v + 0.5f));
    }
    else
    {
        v = x->a_atom.a_w.a_float - dy * 0.01f;
        iat_floor((double)(v * 100.0f + 0.5f));
    }
    x->clipfloat(v);
}

// @ 0x00a50150
namespace EA { namespace Audio { namespace Eapd {
void gatom_key(int g, float v)
{
    t_gatom_s00a5_0150* x = (t_gatom_s00a5_0150*)g;
    int c = (int)v;
    char* s = x->a_text;
    int len = strlen_i(s);
    if (c == 0) {
        if (s[0] != '\0') {
            binbuf_clear(*(void**)((char*)g + 8));
            FUN_00a471a0(*(void**)((char*)g + 8), 1, (char*)g + 0x28);
            if (glist_isvisible(*(t_glist_s00a5_0150**)((char*)g + 0x34)))
                sys_vgui_sym((unsigned)g, *(unsigned*)((char*)g + 0x34), (unsigned)FUN_00a4fce0);
        }
    }
    else if (c != 0x20) {
        if (c == 8) {
            if (len > 0)
                x->a_text[len - 1] = 0;
        }
        else {
            if (c == 10) {
                if (x->a_type == 1) {
                    *(float*)&x->a_value = (float)atof_i(s);
                }
                else if (x->a_type == 2) {
                    t_symbol_s00a5_0150 tmp;
                    t_symbol_s00a5_0150* sy = (t_symbol_s00a5_0150*)gensym(&tmp, s);
                    x->a_value.name = sy->s_name;
                    x->a_value.thing = sy->s_thing;
                }
                gatom_bang(g);
                gatom_retext(1);
                s[0] = '\0';
                return;
            }
            if (len > 0x26)
                return;
            if (x->a_type != 2 &&
                ((c < 0x30 || c > 0x39) && c != 0x2e) &&
                (c != 0x2d && c != 0x65 && c != 0x45))
                return;
            x->a_text[len] = (char)c;
            x->a_text[len + 1] = 0;
        }
        char buf[44];
        char msg[44];
        sprintf_i(buf, gDotsStr, s);
        t_atom_s00a5_0150 a[3];
        a[0].a_type = 2;
        t_symbol_s00a5_0150 tmp2;
        t_symbol_s00a5_0150* sy = (t_symbol_s00a5_0150*)gensym(&tmp2, buf);
        a[1].a_type = (int)sy->s_name;
        a[2].a_type = (int)sy->s_thing;
        binbuf_clear(*(void**)((char*)g + 8));
        FUN_00a471a0(*(void**)((char*)g + 8), 1, a);
        gobj_vis((void*)g, *(t_glist_s00a5_0150**)((char*)g + 0x34), 2);
        (void)msg;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a502d0
namespace EA { namespace Audio { namespace Eapd {
void gatom_click(int g, float a, float b, float c, int d, float e)
{
    t_gatom_s00a5_0150* x = (t_gatom_s00a5_0150*)g;
    if (x->a_w == 1) {
        if (x->a_type == 1)
            gatom_float(g, (float)(*(float*)&x->a_value == 0.0f));
        return;
    }
    if (e != 0.0f) {
        if (x->a_type != 1)
            return;
        if (*(float*)&x->a_value != 0.0f) {
            *(float*)((char*)g + 0x38) = *(float*)&x->a_value;
            gatom_float(g, 0.0f);
            return;
        }
        gatom_float(g, *(float*)((char*)g + 0x38));
    }
    x->a_shift = (char)(int)c;
    x->a_text[0] = 0;
    glist_grab(*(t_glist_s00a5_0150**)((char*)g + 0x34), (void*)g, (void*)FUN_00a4fff0,
               (void*)gatom_key, (int)a, (int)b);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a503a0
namespace EA { namespace Audio { namespace Eapd {
void gatom_param(int g, void* a1, void* a2, int argc, t_atom_s00a5_0150* argv)
{
    t_gatom_s00a5_0150* x = (t_gatom_s00a5_0150*)g;
    float f0 = atom_getfloat_at(0, argc, argv);
    float f1 = atom_getfloat_at(1, argc, argv);
    float f2 = atom_getfloat_at(2, argc, argv);
    sympair s3 = *(sympair*)gatom_unescapit((void*)argv[3].a_type, (void*)(int)argv[3].a_w);
    float f4 = atom_getfloat_at(4, argc, argv);
    sympair s5 = *(sympair*)gatom_unescapit((void*)argv[5].a_type, (void*)(int)argv[5].a_w);
    sympair s6 = *(sympair*)gatom_unescapit((void*)argv[6].a_type, (void*)(int)argv[6].a_w);
    gobj_vis((void*)g, *(t_glist_s00a5_0150**)((char*)g + 0x34), 0);
    if (*(char*)s5.name == '\0') {
        if (**(char**)((char*)g + 0x50) != '\0')
            inlet_new((void*)g, (void*)g, gEmptySymbol_s00a5_0150.s_name, gEmptyThing,
                      gEmptySymbol_s00a5_0150.s_name, gEmptyThing);
    }
    else if (**(char**)((char*)g + 0x50) == '\0' && *(void**)((char*)g + 0x10) != 0) {
        canvas_deletelinesforio(*(t_glist_s00a5_0150**)((char*)g + 0x34), (void*)g,
                                *(void**)((char*)g + 0x10), 0);
        inlet_free(*(void**)((char*)g + 0x10));
    }
    if (*(char*)s6.name == '\0') {
        if (**(char**)((char*)g + 0x58) != '\0')
            outlet_new((void*)g, gEmptySymbol_s00a5_0150.s_name, gEmptyThing);
    }
    else if (**(char**)((char*)g + 0x58) == '\0' && *(void**)((char*)g + 0xc) != 0) {
        canvas_deletelinesforio(*(t_glist_s00a5_0150**)((char*)g + 0x34), (void*)g, 0,
                                *(void**)((char*)g + 0xc));
        outlet_free(*(void**)((char*)g + 0xc));
    }
    if (f2 <= f1) {
        f2 = 0.0f;
        f1 = 0.0f;
    }
    *(float*)((char*)g + 0x3c) = f2;
    *(float*)((char*)g + 0x40) = f1;
    if (f0 >= 0.0f) {
        if (f0 > 80.0f)
            f0 = 80.0f;
    }
    else {
        f0 = 4.0f;
    }
    *(short*)((char*)g + 0x18) = (short)(int)f0;
    *(unsigned char*)((char*)g + 0x85) = (unsigned char)(int)f4 & 3;
    *(int*)((char*)g + 0x44) = (int)s3.name;
    *(int*)((char*)g + 0x48) = (int)s3.thing;
    if (**(char**)((char*)g + 0x50) != '\0') {
        int out[2];
        canvas_realizedollar((void**)out, *(void**)((char*)g + 0x34),
                             *(void**)((char*)g + 0x4c), *(const char**)((char*)g + 0x50));
        sys_vgui_sym((unsigned)g, (unsigned)out[0], (unsigned)out[1]);
    }
    *(int*)((char*)g + 0x4c) = (int)s5.name;
    *(int*)((char*)g + 0x50) = (int)s5.thing;
    if (*(char*)s5.name != '\0') {
        int out[2];
        canvas_realizedollar((void**)out, *(void**)((char*)g + 0x34), s5.name,
                             (const char*)s5.thing);
        pd_bind((void*)g, (void*)out[0], (void*)out[1]);
    }
    *(int*)((char*)g + 0x54) = (int)s6.name;
    *(int*)((char*)g + 0x58) = (int)s6.thing;
    int out2[2];
    canvas_realizedollar((void**)out2, *(void**)((char*)g + 0x34), s6.name,
                         (const char*)s6.thing);
    *(int*)((char*)g + 0x88) = out2[0];
    *(int*)((char*)g + 0x8c) = out2[1];
    gobj_vis((void*)g, *(t_glist_s00a5_0150**)((char*)g + 0x34), 1);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a50600
namespace EA { namespace Audio { namespace Eapd {
void FUN_00a50600(int canvas, int type, void* a3, void* a4, int argc, t_atom_s00a5_0150* argv)
{
    t_gatom_s00a5_0150* x = (t_gatom_s00a5_0150*)pd_new(gpGatomClass);
    if (x == 0)
        return;
    *(unsigned*)((char*)x + 0x1c) |= 3;
    *(short*)((char*)x + 0x18) = 0;
    void* bb = binbuf_new_s00a5_0150();
    *(float*)((char*)x + 0x38) = 1.0f;
    *(void**)((char*)x + 8) = bb;
    *(int*)((char*)x + 0x34) = canvas;
    *(int*)((char*)x + 0x28) = type;
    *(float*)((char*)x + 0x40) = 0.0f;
    *(float*)((char*)x + 0x3c) = 0.0f;
    *(unsigned char*)((char*)x + 0x85) = 0;
    *(int*)((char*)x + 0x44) = (int)gEmptySymbol_s00a5_0150.s_name;
    *(int*)((char*)x + 0x48) = (int)gEmptyThing;
    *(int*)((char*)x + 0x4c) = (int)gEmptySymbol_s00a5_0150.s_name;
    *(int*)((char*)x + 0x50) = (int)gEmptyThing;
    *(int*)((char*)x + 0x88) = (int)gEmptySymbol_s00a5_0150.s_name;
    *(int*)((char*)x + 0x8c) = (int)gEmptyThing;
    *(int*)((char*)x + 0x54) = *(int*)((char*)x + 0x88);
    *(int*)((char*)x + 0x58) = *(int*)((char*)x + 0x8c);
    t_atom_s00a5_0150 init[3];
    if (type == 1) {
        *(float*)((char*)x + 0x2c) = 0.0f;
        *(short*)((char*)x + 0x18) = 5;
        init[0].a_type = 1;
        init[1].a_type = 0;
    }
    else {
        *(int*)((char*)x + 0x2c) = (int)gSymSymbol.s_name;
        *(int*)((char*)x + 0x30) = (int)gSymSymbolThing;
        *(short*)((char*)x + 0x18) = 10;
        init[0].a_type = 2;
        init[1].a_type = (int)gSymSymbol.s_name;
        init[2].a_type = (int)gSymSymbolThing;
    }
    FUN_00a471a0(bb, 1, init);
    if (argc > 1) {
        *(short*)((char*)x + 0x14) = (short)FUN_011e0810(atom_getfloat_at(0, argc, argv));
        *(short*)((char*)x + 0x16) = (short)FUN_011e0810(atom_getfloat_at(1, argc, argv));
        short w = (short)atom_getint_at(2, argc, argv);
        *(short*)((char*)x + 0x18) = w;
        if (w < 0 || w > 500)
            *(short*)((char*)x + 0x18) = 4;
        *(float*)((char*)x + 0x40) = atom_getfloat_at(3, argc, argv);
        *(float*)((char*)x + 0x3c) = atom_getfloat_at(4, argc, argv);
        *(unsigned char*)((char*)x + 0x85) = (unsigned char)(int)FUN_011e0810(
            atom_getfloat_at(5, argc, argv)) & 3;
        t_atom_s00a5_0150 abuf[10];
        {
            void* p = FUN_00a46950(abuf, 6, argc, argv);
            sympair s6 = *(sympair*)gatom_unescapit(*(void**)p, *(void**)((char*)p + 4));
            *(int*)((char*)x + 0x44) = (int)s6.name;
            *(int*)((char*)x + 0x48) = (int)s6.thing;
        }
        {
            void* p7 = FUN_00a46950(abuf, 7, argc, argv);
            sympair s7 = *(sympair*)gatom_unescapit(*(void**)p7, *(void**)((char*)p7 + 4));
            *(int*)((char*)x + 0x4c) = (int)s7.name;
            *(int*)((char*)x + 0x50) = (int)s7.thing;
            if (*(char*)s7.name != '\0') {
                int out[2];
                canvas_realizedollar((void**)out, *(void**)((char*)x + 0x34),
                                     s7.name, (const char*)s7.thing);
                pd_bind((void*)x, (void*)out[0], (void*)out[1]);
            }
        }
        {
            void* p8 = FUN_00a46950(abuf, 8, argc, argv);
            sympair s8 = *(sympair*)gatom_unescapit(*(void**)p8, *(void**)((char*)p8 + 4));
            *(int*)((char*)x + 0x54) = (int)s8.name;
            *(int*)((char*)x + 0x58) = (int)s8.thing;
            int out2[2];
            canvas_realizedollar((void**)out2, *(void**)((char*)x + 0x34), s8.name,
                                 (const char*)s8.thing);
            *(int*)((char*)x + 0x88) = out2[0];
            *(int*)((char*)x + 0x8c) = out2[1];
        }
        if (*(int*)((char*)x + 0x54) == (int)gEmptySymbol_s00a5_0150.s_name) {
            void* oa = (void*)gSymSymbol.s_name;
            void* ob = gSymSymbolThing;
            if (*(int*)((char*)x + 0x28) == 1) {
                oa = (void*)gFloatSymbol.s_name;
                ob = gFloatSymbolThing;
            }
            outlet_new((void*)x, oa, ob);
        }
        if (*(int*)((char*)x + 0x4c) == (int)gEmptySymbol_s00a5_0150.s_name)
            inlet_new((void*)x, (void*)x, gEmptySymbol_s00a5_0150.s_name, gEmptyThing,
                      gEmptySymbol_s00a5_0150.s_name, gEmptyThing);
        glist_add(*(t_glist_s00a5_0150**)((char*)x + 0x34), 0);
        return;
    }
    void* oa = (void*)gSymSymbol.s_name;
    void* ob = gSymSymbolThing;
    if (*(int*)((char*)x + 0x28) == 1) {
        oa = (void*)gFloatSymbol.s_name;
        ob = gFloatSymbolThing;
    }
    outlet_new((void*)x, oa, ob);
    inlet_new((void*)x, (void*)x, gEmptySymbol_s00a5_0150.s_name, gEmptyThing,
              gEmptySymbol_s00a5_0150.s_name, gEmptyThing);
    t_symbol_s00a5_0150 em;
    t_symbol_s00a5_0150* e = (t_symbol_s00a5_0150*)gensym(&em, gEditmodeStr);
    pd_vmess((void*)canvas, e->s_name, e->s_thing, gIStr, 1);
    glist_noselect((t_glist_s00a5_0150*)canvas);
    int lx[2], ly[2];
    canvas_getlastxy((t_glist_s00a5_0150*)canvas, lx, ly);
    *(short*)((char*)x + 0x14) = (short)lx[0];
    *(short*)((char*)x + 0x16) = (short)ly[0];
    glist_add((t_glist_s00a5_0150*)canvas, (void*)x);
    glist_noselect((t_glist_s00a5_0150*)canvas);
    canvas_select((t_glist_s00a5_0150*)canvas, (void*)x);
    canvas_startmotion(glist_getcanvas_s00a5_0150((t_glist_s00a5_0150*)canvas));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a509c0
namespace EA { namespace Audio { namespace Eapd {
void canvas_symbolatom(void* a1, void* a2, void* a3, void* a4, void* a5)
{
    FUN_00a50600((int)a1, 2, a2, a3, (int)a4, (t_atom_s00a5_0150*)a5);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a509f0
namespace EA { namespace Audio { namespace Eapd {
void gatom_free(int g)
{
    if (**(char**)((char*)g + 0x50) != '\0') {
        sympair out;
        sympair* r = (sympair*)canvas_realizedollar((void**)&out, *(void**)((char*)g + 0x34),
                             *(void**)((char*)g + 0x4c), *(const char**)((char*)g + 0x50));
        sys_vgui_sym((unsigned)g, (unsigned)r->name, (unsigned)r->thing);
    }
    gfxstub_deleteforkey((void*)g);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a50a40
namespace EA { namespace Audio { namespace Eapd {
void gatom_properties(int g)
{
    char buf[200];
    t_symbol_s00a5_0150 s1 = *(t_symbol_s00a5_0150*)gatom_escapit(*(void**)((char*)g + 0x54), *(void**)((char*)g + 0x58));
    t_symbol_s00a5_0150 s2 = *(t_symbol_s00a5_0150*)gatom_escapit(*(void**)((char*)g + 0x4c), *(void**)((char*)g + 0x50));
    t_symbol_s00a5_0150 s3 = *(t_symbol_s00a5_0150*)gatom_escapit(*(void**)((char*)g + 0x44), *(void**)((char*)g + 0x48));
    sprintf_i(buf, gGatomDialogFmt, (int)*(short*)((char*)g + 0x18),
              (double)*(float*)((char*)g + 0x40), (double)*(float*)((char*)g + 0x3c),
              (int)*(char*)((char*)g + 0x85), s3.s_thing, s2.s_thing, s1.s_thing);
    gfxstub_new((void*)g, (void*)g, buf);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a50ae0
namespace EA { namespace Audio { namespace Eapd {
void text_getrect(int t, t_glist_s00a5_0150* g, int* x1, int* y1, int* x2, int* y2)
{
    int w, h;
    unsigned fl = *(unsigned*)((char*)t + 0x1c) & 3;
    int extra = (fl == 0);
    if (fl == 3 && *(short*)((char*)t + 0x18) > 0) {
        void* tx = canvas_gettext(g);
        int fh = sys_fontheight((int)tx);
        int fe = sys_fontextra((int)tx);
        int n = *(short*)((char*)t + 0x18);
        if (n <= 0)
            n = 6;
        w = n * fh + 2;
        h = fe + 1;
    }
    else if (*(void**)((char*)g + 0x60) == 0 ||
             *(int*)(*(char*)((char*)g + 0x60) + 0xc) == 0) {
        w = 10;
        h = 10;
    }
    else {
        void* r = glist_findrtext(g, (void*)t);
        w = rtext_width(r);
        h = rtext_height(r) + extra * -2;
        int ni = obj_ninlets((t_gobj_s00a5_0150*)t);
        int a = ni * 0xe + -7;
        int no = obj_noutlets((t_gobj_s00a5_0150*)t);
        int b = no * 0xe + -7;
        if (w <= a)
            w = a;
        if (w <= b)
            w = b;
    }
    int px = text_xpix((void*)t, g);
    int py = text_ypix((void*)t, g);
    *x1 = px;
    *y1 = extra + py;
    *x2 = w + px;
    *y2 = h + py;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a50c20
namespace EA { namespace Audio { namespace Eapd {
void text_activate(int* t, t_glist_s00a5_0150* g, int v)
{
    void* r = glist_findrtext(g, t);
    if (*t != (int)gpGatomClass)
        rtext_activate(r, v);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a50c70
namespace EA { namespace Audio { namespace Eapd {
int text_shouldvis(int* t, t_glist_s00a5_0150* g)
{
    unsigned f = *(unsigned*)((char*)g + 0x78);
    if ((f & 1) != 0)
        goto one;
    if (*t == (int)gpCanvasClass_s00a5_0150) {
        if ((t[0x1e] & 0x100) != 0)
            goto one;
    }
    else {
        if (*(int*)(*t + 0x3c) != (int)gAtomWidgetBehavior)
            goto one;
    }
    if ((char)f >= 0)
        return 0;
    if (((unsigned char)t[7] & 3) != 1)
        goto one;
    return 0;
one:
    return 1;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a50cc0
namespace EA { namespace Audio { namespace Eapd {
int text_click(int t, void* g, int x, int y, int a5, int a6, void* a7, int sh)
{
    unsigned fl = *(unsigned*)((char*)t + 0x1c) & 3;
    if (fl == 1) {
        t_symbol_s00a5_0150 tmp;
        t_symbol_s00a5_0150* s = (t_symbol_s00a5_0150*)gensym(&tmp, gClickStr);
        if (zgetfn((void*)t, s->s_name, s->s_thing) == 0)
            return 0;
        if (sh != 0) {
            pd_vmess((void*)t, s->s_name, s->s_thing, gFffffStr,
                     (double)x, (double)y, (double)a5, 0, (double)a6);
            return 1;
        }
    }
    else if (fl == 3) {
        if (sh != 0)
            gatom_click(t, (float)x, (float)y, (float)a5, 0, (float)a6);
    }
    else {
        if (fl != 2)
            return 0;
        if (sh != 0) {
            message_click(t, (float)x, (float)y, (float)a5, 0, (float)a6);
            return 1;
        }
    }
    return 1;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a50e00
namespace EA { namespace Audio { namespace Eapd {
void text_save(int* t, void* b)
{
    unsigned fl = t[7] & 3;
    t_symbol_s00a5_0150 tmp;
    if (fl == 1) {
        t_symbol_s00a5_0150* s = (t_symbol_s00a5_0150*)gensym(&tmp, gSavetoStr);
        if (zgetfn((void*)t, s->s_name, s->s_thing) != 0) {
            if (*t != (int)gpCanvasClass_s00a5_0150) {
                goto dosaveto;
            }
            if (canvas_isopen((t_glist_s00a5_0150*)t) == 0) {
                if (canvas_istable((t_glist_s00a5_0150*)t) == 0) {
                    goto dosaveto;
                }
            }
        }
        t_symbol_s00a5_0150* o = (t_symbol_s00a5_0150*)gensym(&tmp, gObjStr);
        t_symbol_s00a5_0150* h = (t_symbol_s00a5_0150*)gensym(&tmp, gHashXStr);
        binbuf_addv(b, gSsiiStr, h->s_name, h->s_thing, o->s_name, o->s_thing,
                    (int)(short)t[5], (int)*(short*)((char*)t + 0x16));
        goto tail;
    dosaveto:
        {
            t_symbol_s00a5_0150* sv = (t_symbol_s00a5_0150*)gensym(&tmp, gSavetoStr);
            void* fn = FUN_00a48890(t, sv->s_name, sv->s_thing);
            void (*fp)(void*, void*) = (void (*)(void*, void*))fn;
            fp((void*)t, b);
        }
        {
            t_symbol_s00a5_0150* rs = (t_symbol_s00a5_0150*)gensym(&tmp, gRestoreStr);
            t_symbol_s00a5_0150* h = (t_symbol_s00a5_0150*)gensym(&tmp, gHashXStr);
            binbuf_addv(b, gSsiiStr, h->s_name, h->s_thing, rs->s_name, rs->s_thing,
                        (int)(short)t[5], (int)(short)*(short*)((char*)t + 0x16));
        }
        goto tail;
    }
    if (fl == 2) {
        t_symbol_s00a5_0150* m = (t_symbol_s00a5_0150*)gensym(&tmp, gMsgStr);
        t_symbol_s00a5_0150* h = (t_symbol_s00a5_0150*)gensym(&tmp, gHashXStr);
        binbuf_addv(b, gSsiiStr, h->s_name, h->s_thing, m->s_name, m->s_thing,
                    (int)(short)t[5], (int)(short)*(short*)((char*)t + 0x16));
        goto tail;
    }
    if (fl == 3) {
        t_symbol_s00a5_0150* nm;
        if (t[10] == 2)
            nm = (t_symbol_s00a5_0150*)gensym(&tmp, gSymbolatomStr);
        else if (t[10] == 1)
            nm = (t_symbol_s00a5_0150*)gensym(&tmp, gFloatatomStr);
        else
            nm = (t_symbol_s00a5_0150*)gensym(&tmp, gIntatomStr);
        t_symbol_s00a5_0150* h = (t_symbol_s00a5_0150*)gensym(&tmp, gHashXStr);
        t_symbol_s00a5_0150 s1 = *(t_symbol_s00a5_0150*)gatom_escapit(*(void**)((char*)t + 0x44), *(void**)((char*)t + 0x48));
        t_symbol_s00a5_0150 s2 = *(t_symbol_s00a5_0150*)gatom_escapit(*(void**)((char*)t + 0x4c), *(void**)((char*)t + 0x50));
        t_symbol_s00a5_0150 s3 = *(t_symbol_s00a5_0150*)gatom_escapit(*(void**)((char*)t + 0x54), *(void**)((char*)t + 0x58));
        binbuf_addv(b, gSsiiifffsssStr, h->s_name, h->s_thing, nm->s_name, nm->s_thing,
                    (int)(short)t[5], (int)*(short*)((char*)t + 0x16), (int)(short)t[6],
                    (double)*(float*)((char*)t + 0x40), (double)*(float*)((char*)t + 0x3c),
                    (double)(int)*(char*)((char*)t + 0x85),
                    s3.s_name, s3.s_thing, s2.s_name, s2.s_thing, s1.s_name, s1.s_thing);
        binbuf_addv(b, gSemicolonStr);
        return;
    }
    {
        t_symbol_s00a5_0150* tx = (t_symbol_s00a5_0150*)gensym(&tmp, gTextStr);
        t_symbol_s00a5_0150* h = (t_symbol_s00a5_0150*)gensym(&tmp, gHashXStr);
        binbuf_addv(b, gSsiiStr, h->s_name, h->s_thing, tx->s_name, tx->s_thing,
                    (int)(short)t[5], (int)*(short*)((char*)t + 0x16));
        goto tail;
    }
tail:
    FUN_00a47350(b, (void*)t[2]);
    binbuf_addv(b, gSemicolonStr);
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
