// slice s00a50150 -- EA::Audio::Eapd (EA's embedded Pd 0.4x): the gatom/text
//  widget behaviour (g_text.c / g_all_guis.c): gatom_key/click/param, canvas_atom
//  construction, canvas_symbolatom, gatom_free/properties, text_activate/
//  shouldvis/click/save and text_getrect. 12 functions.
// Layout follows symbols/pdb_names.json (EA::Audio::Eapd::*) and the Pd 0.4x
// source; only the fields these functions touch are declared, at their binary
// offsets. Callees, globals and vtable targets are masked relocations.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

// ---------------------------------------------------------------- Pd core types
struct t_class;
struct t_gobj;
struct t_glist;
struct t_symbol {
    void* s_name;    // +0
    void* s_thing;   // +4
};
// gatom_unescapit/escapit and the atom_get*symbol helpers return a symbol as a
// two-word (name, thing) pair; model that return shape explicitly.
struct sympair {
    void* name;      // +0
    void* thing;     // +4
};
struct t_class {
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
    t_class* c_next;      // +0x4c
};
struct t_gobj {
    t_class* g_pd;    // +0
    t_gobj*  g_next;  // +4
    char pad[0x24 - 8];
    void*    o_save;  // +0x24
};
// Inlet/outlet connection record (t_outconnect): only the next pointer matters here.
struct t_outconnect { t_outconnect* oc_next; };
// atom slot: [0]=type code, [1]=payload word, [2]=payload word
struct t_atom {
    int   a_type;    // +0
    float a_w;       // +4
    float a_w2;      // +8
};
// canvas / glist: only the fields these functions touch.
struct t_glist {
    t_gobj   g_gobj;          // +0
    void*    g_pd;            // +0x24   (t_glist's own gobj pd pointer reused here)
    void*    gl_list;         // +0x28
    t_glist* gl_owner;        // +0x2c
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
// The gatom struct (Pd t_gatom), fields at their binary offsets.
struct t_gatom {
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
    t_symbol a_rcv_sym;      // +0x44   (stored as two words: name,thing)
    t_symbol a_rcv_lab;      // +0x4c
    t_symbol a_snd_sym;      // +0x54
    char     a_text[0x84 - 0x5c]; // +0x5c   in-place editor text buffer
    char     a_shift;        // +0x84
    char     a_where;        // +0x85
    t_symbol a_send;         // +0x88
};

// ---------------------------------------------------------------- globals (masked relocs)
extern t_symbol gEmptySymbol;    // 0x167589c
extern t_symbol gSymSymbol;      // 0x1675894
extern t_symbol gFloatSymbol;    // 0x16758c4
extern void*    gSymSymbolThing; // 0x1675898
extern void*    gFloatSymbolThing;// 0x16758c8
extern void*    gEmptyThing;     // 0x16758a0
extern t_class* gpGatomClass;    // 0x16754f4
extern t_class* gpCanvasClass;   // 0x1675490
extern void*    gAtomWidgetBehavior; // 0x1554364 (text/atom widgetbehavior, compared in text_shouldvis)
extern void*    gTextWidgetBehavior; // (text_widgetbehavior)

// ---------------------------------------------------------------- externs (masked relocs)
int   strlen_i(const char* s);                                                       // inlined
int   strcmp_i(const char* a, const char* b);                                        // inlined
int   sprintf_i(char* d, const char* fmt, ...);                                      // inlined (msvcr90 sprintf)
double atof_i(const char* s);                                                        // inlined (msvcr90 atof)
void* gensym(t_symbol* out, const char* s);                                          // 0xa675f0
void* pd_new(t_class* c);                                                            // 0xa49390
void* binbuf_new();                                                                  // 0xa46c20
void  binbuf_clear(void* b);                                                         // 0xa46c80
void  binbuf_addv(void* b, const char* fmt, ...);                                    // 0xa47220
void  FUN_00a471a0(void* b, int n, ...);                                             // 0xa471a0 (binbuf_add atoms)
void  FUN_00a47350(void* b, void* s);                                                // 0xa47350 (binbuf_add one atom)
void* gatom_unescapit(void* a, void* b);                                             // 0xa4fc50
void* gatom_escapit(void* a, void* b);                                               // 0xa4fba0
void  gatom_float(int g, float v);                                                   // 0xa4fe90
void  gatom_bang(int g);                                                             // (called)
void  gatom_retext(int g);                                                           // (called)
void  message_click(int x, float a, float b, float c, float d, float e);             // 0xa4f950
void  glist_grab(t_glist* g, void* o, void* fn, void* keyfn, int x, int y);          // 0xa4dfb0
void  glist_noselect(t_glist* g);                                                    // 0xa4d1d0
int   glist_isvisible(t_glist* g);                                                   // 0xa4ab40
t_glist* glist_getcanvas(t_glist* g);                                                // 0xa4d410
void  glist_add(t_glist* g, void* o);                                                // 0xa4d340
void  gobj_vis(void* o, t_glist* g, int vis);                                        // 0xa4d3e0
void  obj_disconnect(void* a, void* b, void* c, void* d);                            // 0xa4a010
void  obj_connect(void* o1, int out, void* o2, int in);                              // (not used)
void  canvas_deletelinesforio(t_glist* g, void* a, void* b, void* c);                // 0xa4b2f0
void  canvas_getlastxy(t_glist* g, int* x, int* y);                                  // 0xa4cfb0
void  canvas_startmotion(t_glist* g);                                                // 0xa4d230
void  canvas_select(t_glist* g, void* o);                                            // 0xa4c740
void  pd_bind(void* obj, void* a, void* b);                                          // 0xa67620
void  pd_vmess(void* obj, void* sel_a, void* sel_b, const char* fmt, ...);           // 0xa487f0
void* zgetfn(void* obj, void* sel_a, void* sel_b);                                   // 0xa488d0
void* FUN_00a48890(void* obj, void* a, void* b);                                     // (zgetfn variant)
void* outlet_new(void* o, void* a, void* b);                                         // 0xa49d30
void* inlet_new(void* o, void* a, void* b, void* c, void* d, void* e);               // 0xa49740
void  inlet_free(void* o);                                                           // 0xa49f20
void  outlet_free(void* o);                                                          // 0xa49f20
void* canvas_realizedollar(void** out, void* env, void* a3, const char* s);          // 0xa4a550
int   obj_ninlets(t_gobj* o);                                                        // 0xa4a0d0
int   obj_noutlets(t_gobj* o);                                                       // 0xa4a0b0
int   atom_getint_at(int i, int n, t_atom* a);                                       // 0xa46920
float atom_getfloat_at(int i, int n, t_atom* a);                                     // 0xa468f0
void* FUN_00a46950(void* out, int i, int n, t_atom* a);                              // 0xa46950
short FUN_011e0810(float v);                                                         // 0x11e0810
void  gfxstub_new(void* key, void* arg, const char* s);                              // 0xa4c470
void  gfxstub_deleteforkey(void* key);                                               // 0xa4c170
void  sys_vgui_sym(unsigned a, unsigned b, unsigned c);                              // 0xa671b0 (sel/obj form)
void  outletv(void* o, void* a, void* b);                                            // (not used)
// eapd text helpers
void* glist_findrtext(t_glist* g, void* o);                                          // 0xa4efb0
int   rtext_width(void* r);                                                          // 0xa4efd0
int   rtext_height(void* r);                                                         // 0xa4f010
void  rtext_activate(void* r, int v);                                                // 0xa4f130
int   text_xpix(void* o, t_glist* g);                                                // 0xa4d920
int   text_ypix(void* o, t_glist* g);                                                // 0xa4d9c0
int   sys_fontheight(int f);                                                         // 0xa4d2e0
int   sys_fontextra(int f);                                                          // 0xa4d310
void* canvas_gettext(t_glist* g);                                                    // 0xa4ab90
int   canvas_isopen(t_glist* g);                                                     // 0xa4ad50
int   canvas_istable(t_glist* g);                                                    // 0xa4ad60
void  canvas_symbolatom(void* a, void* b, void* c, void* d, void* e, void* f);       // forward
void  FUN_00a50600(int g, int type, void* canvas, void* o, int argc, void* atoms);   // canvas_atom
void* FUN_00a4fce0(void);                                                            // key handler
void* FUN_00a4fff0(void);                                                            // motion handler
void  gatom_key(int g, float v);
extern const char gSavetoStr[];   // 0x1454bd0 "saveto"
extern const char gRestoreStr[];  // 0x14546b0 "restore"
extern const char gHashXStr[];    // 0x1454858 "#X"
extern const char gObjStr[];      // 0x14546a4 "obj"
extern const char gMsgStr[];      // 0x14546a0 "msg"
extern const char gTextStr[];     // 0x1408a0c "text"
extern const char gSemicolonStr[];// 0x13fb1c0 ";"
extern const char gSymbolatomStr[];   // 0x1454688 "symbolatom"
extern const char gFloatatomStr[];    // 0x1454694 "floatatom"
extern const char gIntatomStr[];      // 0x1454bc0 "intatom"
extern const char gSsiiStr[];         // 0x1454bc8 "ssii"
extern const char gSsiiifffsssStr[];  // 0x1454bb4 "ssiiifffsss"
extern const char gClickStr[];        // 0x145465c "click"
extern const char gFffffStr[];        // 0x1454bac "fffff"
extern const char gDotsStr[];         // 0x1454b78 "%s..."
extern const char gEditmodeStr[];     // 0x1454b1c "editmode"
extern const char gIStr[];            // 0x1433620 "i"
extern const char gGatomDialogFmt[];  // 0x1454b80

// ============================================================ gatom behaviour

// @ 0x00a50150
void gatom_key(int g, float v)
{
    t_gatom* x = (t_gatom*)g;
    int c = (int)v;
    char* s = x->a_text;
    int len = strlen_i(s);
    if (c == 0) {
        if (s[0] != '\0') {
            binbuf_clear(*(void**)((char*)g + 8));
            FUN_00a471a0(*(void**)((char*)g + 8), 1, (char*)g + 0x28);
            if (glist_isvisible(*(t_glist**)((char*)g + 0x34)))
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
                    t_symbol tmp;
                    t_symbol* sy = (t_symbol*)gensym(&tmp, s);
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
        t_atom a[3];
        a[0].a_type = 2;
        t_symbol tmp2;
        t_symbol* sy = (t_symbol*)gensym(&tmp2, buf);
        a[1].a_type = (int)sy->s_name;
        a[2].a_type = (int)sy->s_thing;
        binbuf_clear(*(void**)((char*)g + 8));
        FUN_00a471a0(*(void**)((char*)g + 8), 1, a);
        gobj_vis((void*)g, *(t_glist**)((char*)g + 0x34), 2);
        (void)msg;
    }
}

// @ 0x00a502d0
void gatom_click(int g, float a, float b, float c, int d, float e)
{
    t_gatom* x = (t_gatom*)g;
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
    glist_grab(*(t_glist**)((char*)g + 0x34), (void*)g, (void*)FUN_00a4fff0,
               (void*)gatom_key, (int)a, (int)b);
}

// @ 0x00a503a0
void gatom_param(int g, void* a1, void* a2, int argc, t_atom* argv)
{
    t_gatom* x = (t_gatom*)g;
    float f0 = atom_getfloat_at(0, argc, argv);
    float f1 = atom_getfloat_at(1, argc, argv);
    float f2 = atom_getfloat_at(2, argc, argv);
    sympair s3 = *(sympair*)gatom_unescapit((void*)argv[3].a_type, (void*)(int)argv[3].a_w);
    float f4 = atom_getfloat_at(4, argc, argv);
    sympair s5 = *(sympair*)gatom_unescapit((void*)argv[5].a_type, (void*)(int)argv[5].a_w);
    sympair s6 = *(sympair*)gatom_unescapit((void*)argv[6].a_type, (void*)(int)argv[6].a_w);
    gobj_vis((void*)g, *(t_glist**)((char*)g + 0x34), 0);
    if (*(char*)s5.name == '\0') {
        if (**(char**)((char*)g + 0x50) != '\0')
            inlet_new((void*)g, (void*)g, gEmptySymbol.s_name, gEmptyThing,
                      gEmptySymbol.s_name, gEmptyThing);
    }
    else if (**(char**)((char*)g + 0x50) == '\0' && *(void**)((char*)g + 0x10) != 0) {
        canvas_deletelinesforio(*(t_glist**)((char*)g + 0x34), (void*)g,
                                *(void**)((char*)g + 0x10), 0);
        inlet_free(*(void**)((char*)g + 0x10));
    }
    if (*(char*)s6.name == '\0') {
        if (**(char**)((char*)g + 0x58) != '\0')
            outlet_new((void*)g, gEmptySymbol.s_name, gEmptyThing);
    }
    else if (**(char**)((char*)g + 0x58) == '\0' && *(void**)((char*)g + 0xc) != 0) {
        canvas_deletelinesforio(*(t_glist**)((char*)g + 0x34), (void*)g, 0,
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
    gobj_vis((void*)g, *(t_glist**)((char*)g + 0x34), 1);
}

// @ 0x00a50600
void FUN_00a50600(int canvas, int type, void* a3, void* a4, int argc, t_atom* argv)
{
    t_gatom* x = (t_gatom*)pd_new(gpGatomClass);
    if (x == 0)
        return;
    *(unsigned*)((char*)x + 0x1c) |= 3;
    *(short*)((char*)x + 0x18) = 0;
    void* bb = binbuf_new();
    *(float*)((char*)x + 0x38) = 1.0f;
    *(void**)((char*)x + 8) = bb;
    *(int*)((char*)x + 0x34) = canvas;
    *(int*)((char*)x + 0x28) = type;
    *(float*)((char*)x + 0x40) = 0.0f;
    *(float*)((char*)x + 0x3c) = 0.0f;
    *(unsigned char*)((char*)x + 0x85) = 0;
    *(int*)((char*)x + 0x44) = (int)gEmptySymbol.s_name;
    *(int*)((char*)x + 0x48) = (int)gEmptyThing;
    *(int*)((char*)x + 0x4c) = (int)gEmptySymbol.s_name;
    *(int*)((char*)x + 0x50) = (int)gEmptyThing;
    *(int*)((char*)x + 0x88) = (int)gEmptySymbol.s_name;
    *(int*)((char*)x + 0x8c) = (int)gEmptyThing;
    *(int*)((char*)x + 0x54) = *(int*)((char*)x + 0x88);
    *(int*)((char*)x + 0x58) = *(int*)((char*)x + 0x8c);
    t_atom init[3];
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
        t_atom abuf[10];
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
        if (*(int*)((char*)x + 0x54) == (int)gEmptySymbol.s_name) {
            void* oa = (void*)gSymSymbol.s_name;
            void* ob = gSymSymbolThing;
            if (*(int*)((char*)x + 0x28) == 1) {
                oa = (void*)gFloatSymbol.s_name;
                ob = gFloatSymbolThing;
            }
            outlet_new((void*)x, oa, ob);
        }
        if (*(int*)((char*)x + 0x4c) == (int)gEmptySymbol.s_name)
            inlet_new((void*)x, (void*)x, gEmptySymbol.s_name, gEmptyThing,
                      gEmptySymbol.s_name, gEmptyThing);
        glist_add(*(t_glist**)((char*)x + 0x34), 0);
        return;
    }
    void* oa = (void*)gSymSymbol.s_name;
    void* ob = gSymSymbolThing;
    if (*(int*)((char*)x + 0x28) == 1) {
        oa = (void*)gFloatSymbol.s_name;
        ob = gFloatSymbolThing;
    }
    outlet_new((void*)x, oa, ob);
    inlet_new((void*)x, (void*)x, gEmptySymbol.s_name, gEmptyThing,
              gEmptySymbol.s_name, gEmptyThing);
    t_symbol em;
    t_symbol* e = (t_symbol*)gensym(&em, gEditmodeStr);
    pd_vmess((void*)canvas, e->s_name, e->s_thing, gIStr, 1);
    glist_noselect((t_glist*)canvas);
    int lx[2], ly[2];
    canvas_getlastxy((t_glist*)canvas, lx, ly);
    *(short*)((char*)x + 0x14) = (short)lx[0];
    *(short*)((char*)x + 0x16) = (short)ly[0];
    glist_add((t_glist*)canvas, (void*)x);
    glist_noselect((t_glist*)canvas);
    canvas_select((t_glist*)canvas, (void*)x);
    canvas_startmotion(glist_getcanvas((t_glist*)canvas));
}

// ============================================================ canvas helpers

// @ 0x00a509c0
void canvas_symbolatom(void* a1, void* a2, void* a3, void* a4, void* a5)
{
    FUN_00a50600((int)a1, 2, a2, a3, (int)a4, (t_atom*)a5);
}

// @ 0x00a509f0
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

// @ 0x00a50a40
void gatom_properties(int g)
{
    char buf[200];
    t_symbol s1 = *(t_symbol*)gatom_escapit(*(void**)((char*)g + 0x54), *(void**)((char*)g + 0x58));
    t_symbol s2 = *(t_symbol*)gatom_escapit(*(void**)((char*)g + 0x4c), *(void**)((char*)g + 0x50));
    t_symbol s3 = *(t_symbol*)gatom_escapit(*(void**)((char*)g + 0x44), *(void**)((char*)g + 0x48));
    sprintf_i(buf, gGatomDialogFmt, (int)*(short*)((char*)g + 0x18),
              (double)*(float*)((char*)g + 0x40), (double)*(float*)((char*)g + 0x3c),
              (int)*(char*)((char*)g + 0x85), s3.s_thing, s2.s_thing, s1.s_thing);
    gfxstub_new((void*)g, (void*)g, buf);
}

// @ 0x00a50ae0
void text_getrect(int t, t_glist* g, int* x1, int* y1, int* x2, int* y2)
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
        int ni = obj_ninlets((t_gobj*)t);
        int a = ni * 0xe + -7;
        int no = obj_noutlets((t_gobj*)t);
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

// @ 0x00a50c20
void text_activate(int* t, t_glist* g, int v)
{
    void* r = glist_findrtext(g, t);
    if (*t != (int)gpGatomClass)
        rtext_activate(r, v);
}

// @ 0x00a50c70
int text_shouldvis(int* t, t_glist* g)
{
    unsigned f = *(unsigned*)((char*)g + 0x78);
    if ((f & 1) != 0)
        return 1;
    if (*t == (int)gpCanvasClass) {
        if ((t[0x1e] & 0x100) != 0)
            return 1;
    }
    else {
        if (*(int*)(*t + 0x3c) != (int)gAtomWidgetBehavior)
            return 1;
    }
    if ((char)f >= 0)
        return 0;
    if (((unsigned char)t[7] & 3) != 1)
        return 1;
    return 0;
}

// @ 0x00a50cc0
int text_click(int t, void* g, int x, int y, int a5, int a6, void* a7, int sh)
{
    unsigned fl = *(unsigned*)((char*)t + 0x1c) & 3;
    if (fl == 1) {
        t_symbol tmp;
        t_symbol* s = (t_symbol*)gensym(&tmp, gClickStr);
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

// @ 0x00a50e00
void text_save(int* t, void* b)
{
    unsigned fl = t[7] & 3;
    t_symbol tmp;
    if (fl == 1) {
        t_symbol* s = (t_symbol*)gensym(&tmp, gSavetoStr);
        if (zgetfn((void*)t, s->s_name, s->s_thing) != 0) {
            if (*t != (int)gpCanvasClass) {
                goto dosaveto;
            }
            if (canvas_isopen((t_glist*)t) == 0) {
                if (canvas_istable((t_glist*)t) == 0) {
                    goto dosaveto;
                }
            }
        }
        t_symbol* o = (t_symbol*)gensym(&tmp, gObjStr);
        t_symbol* h = (t_symbol*)gensym(&tmp, gHashXStr);
        binbuf_addv(b, gSsiiStr, h->s_name, h->s_thing, o->s_name, o->s_thing,
                    (int)(short)t[5], (int)*(short*)((char*)t + 0x16));
        goto tail;
    dosaveto:
        {
            t_symbol* sv = (t_symbol*)gensym(&tmp, gSavetoStr);
            void* fn = FUN_00a48890(t, sv->s_name, sv->s_thing);
            void (*fp)(void*, void*) = (void (*)(void*, void*))fn;
            fp((void*)t, b);
        }
        {
            t_symbol* rs = (t_symbol*)gensym(&tmp, gRestoreStr);
            t_symbol* h = (t_symbol*)gensym(&tmp, gHashXStr);
            binbuf_addv(b, gSsiiStr, h->s_name, h->s_thing, rs->s_name, rs->s_thing,
                        (int)(short)t[5], (int)(short)*(short*)((char*)t + 0x16));
        }
        goto tail;
    }
    if (fl == 2) {
        t_symbol* m = (t_symbol*)gensym(&tmp, gMsgStr);
        t_symbol* h = (t_symbol*)gensym(&tmp, gHashXStr);
        binbuf_addv(b, gSsiiStr, h->s_name, h->s_thing, m->s_name, m->s_thing,
                    (int)(short)t[5], (int)(short)*(short*)((char*)t + 0x16));
        goto tail;
    }
    if (fl == 3) {
        t_symbol* nm;
        if (t[10] == 2)
            nm = (t_symbol*)gensym(&tmp, gSymbolatomStr);
        else if (t[10] == 1)
            nm = (t_symbol*)gensym(&tmp, gFloatatomStr);
        else
            nm = (t_symbol*)gensym(&tmp, gIntatomStr);
        t_symbol* h = (t_symbol*)gensym(&tmp, gHashXStr);
        t_symbol s1 = *(t_symbol*)gatom_escapit(*(void**)((char*)t + 0x44), *(void**)((char*)t + 0x48));
        t_symbol s2 = *(t_symbol*)gatom_escapit(*(void**)((char*)t + 0x4c), *(void**)((char*)t + 0x50));
        t_symbol s3 = *(t_symbol*)gatom_escapit(*(void**)((char*)t + 0x54), *(void**)((char*)t + 0x58));
        binbuf_addv(b, gSsiiifffsssStr, h->s_name, h->s_thing, nm->s_name, nm->s_thing,
                    (int)(short)t[5], (int)*(short*)((char*)t + 0x16), (int)(short)t[6],
                    (double)*(float*)((char*)t + 0x40), (double)*(float*)((char*)t + 0x3c),
                    (double)(int)*(char*)((char*)t + 0x85),
                    s3.s_name, s3.s_thing, s2.s_name, s2.s_thing, s1.s_name, s1.s_thing);
        binbuf_addv(b, gSemicolonStr);
        return;
    }
    {
        t_symbol* tx = (t_symbol*)gensym(&tmp, gTextStr);
        t_symbol* h = (t_symbol*)gensym(&tmp, gHashXStr);
        binbuf_addv(b, gSsiiStr, h->s_name, h->s_thing, tx->s_name, tx->s_thing,
                    (int)(short)t[5], (int)*(short*)((char*)t + 0x16));
        goto tail;
    }
tail:
    FUN_00a47350(b, (void*)t[2]);
    binbuf_addv(b, gSemicolonStr);
}

}}}  // namespace EA::Audio::Eapd
