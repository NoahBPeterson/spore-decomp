// Shared declarations for slice s00a4b3a0 (EA::Audio::Eapd / Pure Data canvas + gfxstub externals).
// Callees are external (relocated) in the original; PDB names where known.
#pragma once
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

struct t_class;
struct t_glist;
struct t_symbol;
struct t_atom;
struct t_object;

// A Pd selector symbol: a name hash plus the interned name string.
struct t_symbol {
    uint32_t    s_hash;         // +0x00
    const char* s_name;         // +0x04
};

// A Pd atom (t_atom: selector type + a word of payload).
struct t_atom {
    int32_t  a_type;            // +0x00
    uint32_t a_w;               // +0x04
    uint32_t a_pad;             // +0x08
};

struct t_gobj {
    t_class* g_pd;              // +0x00
    t_gobj*  g_next;            // +0x04
};

struct t_text {                 // t_object
    t_gobj    te_g;             // +0x00
    uint32_t  pad08[3];         // +0x08..0x14
    int16_t   te_xpix;          // +0x14
    int16_t   te_ypix;          // +0x16
    uint32_t  pad18[4];
};

struct t_editor {
    uint32_t pad00[3];
    void*    e_textedfor;       // +0x0c
    uint32_t pad10[2];
    t_gobj*  e_grab;            // +0x18
    uint32_t pad1c[8];
};

// The Pd canvas (t_glist) as used by the Spore Eapd build.
struct t_glist {
    t_text    gl_obj;           // +0x00
    t_gobj*   gl_list;          // +0x28
    t_glist*  gl_owner;         // +0x2c
    int       gl_pixwidth;      // +0x30
    int       gl_pixheight;     // +0x34
    float     gl_x1;            // +0x38
    float     gl_y1;            // +0x3c
    float     gl_x2;            // +0x40
    float     gl_y2;            // +0x44
    int       gl_screenx1;      // +0x48
    int       gl_screeny1;      // +0x4c
    int       gl_screenx2;      // +0x50
    int       gl_screeny2;      // +0x54
    int       gl_xmargin;       // +0x58
    int       gl_ymargin;       // +0x5c
    t_editor* gl_editor;        // +0x60
    uint32_t  pad64[5];         // +0x64..0x78
    unsigned  gl_havewindow : 1;    // +0x78
    unsigned  gl_mapped : 1;
    unsigned  gl_dirty : 1;
    unsigned  gl_loading : 1;
    unsigned  gl_willvis : 1;
    unsigned  gl_edit : 1;
    unsigned  gl_isdeleting : 1;
    unsigned  gl_goprect : 1;
    unsigned  gl_isgraph : 1;
    unsigned  gl_hidetext : 1;
    uint32_t  pad7c;            // +0x7c
    void*     gl_loadbangcallback;  // +0x80
};

// One linked-list node of the gfxstub registry (selector 8, sym, owner, next).
struct t_gfxstub {
    uint32_t      pad00[2];     // +0x00
    void*         gs_owner;     // +0x08
    uint32_t      pad0c;        // +0x0c
    uint32_t      pad10;        // +0x10
    t_gfxstub*    gs_next;      // +0x14
};

// external Pd / Eapd entry points
int   pd_new(t_class* cls);                                     // 0x00A49390
void  pd_free(void* x);                                         // 0x00A493D0
void  pd_pushsym(void* x);                                      // 0x00A49490
void  pd_popsym(void* x);                                       // 0x00A49500
void  outlet_new(t_glist* owner, t_symbol* s, ...);             // 0x00A49D30
void  pd_bind(void* x, ...);                                    // 0x00A67620
void  pd_typedmess(t_class** c, t_symbol* s, int argc, t_atom* argv, void* extra); // 0x00A48100
void  sys_vgui(unsigned int a, unsigned int b, unsigned int c);  // 0x00A671B0
void  sys_gui(const char* fmt, ...);                            // 0x00A2E4E0 (ILayoutElement::SetSerializer)
t_symbol* gensym(t_symbol* out, const char* name);              // 0x00A675F0
void* pd_findbyclass(...);                                      // 0x00A671F0
void  canvas_rename(t_glist* c, void* x, const char* name,
                    t_symbol* s1, t_symbol* s2);                // 0x00A4AE50
void  canvas_setbounds(int x1, int y1, int x2, int y2);         // 0x00A4B750
void  canvas_relocate(int flags, void* obj, const char* geom, int originY, const char* geom2); // 0x00A4B830
void  canvas_map(t_glist* c, float flag);                       // 0x00A4B630
void  canvas_drawlines(t_glist* c);                             // 0x00A4B140
void  gobj_displace(t_gobj* x, ...);                            // 0x00A4C650
void  gobj_vis(t_gobj* x, t_glist* parent, int flag);           // 0x00A4C6D0
void  FUN_00a4c670(t_gobj* x, t_glist* parent, int flag);       // 0x00A4C670
t_glist* glist_getcanvas(t_glist* x);                           // 0x00A4D410
int   pd_checkobject(t_class** x);                              // 0x00A4A1C0
int   canvas_new(int a, t_symbol* s, t_symbol* c, int n, void* argv); // 0x00A4B8C0
void  gfxstub_deleteforkey(void* key);                          // 0x00A4C170
void  stub_get_ext_d2i(void* obj);                              // 0x00A4C1E0
void  canvas_rename_method(t_glist* c, void* s, t_atom* argv, int unused); // 0x00A4B540
int   binbuf_realizedollsym(unsigned int a, unsigned int b, void* c, void* d, int e, t_symbol* out); // 0x00A477A0
int   atom_getint_at(int idx, int argc, t_atom* argv);          // 0x00A46920
t_symbol* atom_getsymbol_at(int idx, int argc, t_atom* argv, t_symbol* out); // 0x00A46950
void  class_new(t_symbol* s, void* a, void* b, void* c);        // 0x00A476E0
extern "C" int sprintf(char*, const char*, ...);
extern t_glist* gCurrentCanvas;
extern "C" int sscanf(const char*, const char*, ...);
void  gfxstub_anything(void* x, t_symbol* s, int argc, t_atom* argv, void* extra); // 0x00A4C200
void  stub_gfxstub(void* x);                                    // 0x00A4C230
void  stub_vgui(void* x);                                       // 0x00A4C2E0
void  openpanel_bang(void* x);                                  // 0x00A4C2C0

extern t_symbol* gEmptySymbol;              // 0x0167589C
extern t_symbol* gSymbolSymbol;             // 0x01675894
extern uint32_t  gSymbolSymbolData;         // 0x01675898
extern t_gfxstub* gGfxstubList;             // 0x01675494  (head of the gfxstub list)
extern uint32_t  gGfxstubDataA0;            // 0x016758A0
extern t_class*  gpCanvasClass;             // 0x01675490
extern uint32_t  gCanvasClassData8C0;       // 0x016758C0
extern uint32_t  gCanvasClassData8BC;       // 0x016758BC
extern t_class*  gpOpenpanelClass;          // 0x01675498

}}} // namespace EA::Audio::Eapd
