// slice s00a4a500 -- EA::Audio::Eapd (EA's embedded Pd 0.4x): g_canvas.c canvas/editor
//  helpers and the linetraverser. 31 functions.
// Layout follows symbols/pdb_names.json (EA::Audio::Eapd::*) and the Pd 0.4x source
// (g_canvas.c); only the fields these functions touch are declared, at their binary
// offsets. Callees, globals and vtable targets are masked relocations.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int uintptr_t;

namespace EA { namespace Audio { namespace Eapd {

// ---------------------------------------------------------------- Pd core types
struct t_class;
struct t_gobj;
struct t_glist;
struct t_symbol {
    void* s_name;    // +0
    void* s_thing;   // +4
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
// A gobj as laid out by EA's Eapd: t_object starts at +0 behind the gobj header.
struct t_gobj {
    t_class* g_pd;    // +0
    t_gobj*  g_next;  // +4
    char pad[0x24 - 8];
    void*    o_save;  // +0x24
};
struct t_object : t_gobj {
};
// atom slot: [0]=type code, [1]=payload word, [2]=payload word
struct t_atom {
    int   a_type;    // +0
    float a_w;       // +4
    void* a_w2;      // +8
};
// canvas / glist: only the fields these functions touch.
struct t_glist {
    t_gobj   g_gobj;          // +0
    void*    g_pd;            // +0x24   (t_glist's own gobj pd pointer reused here)
    void*    gl_list;         // +0x28   first gobj of the list
    t_glist* gl_owner;        // +0x2c   parent (canvas) OR next in a chain depending on flags
    char pad3[0x60 - 0x30];
    void*    gl_editor;       // +0x60   t_editor* (0 when not editing)
    void*    gl_name_a;       // +0x64   first word of the name t_symbol
    void*    gl_name_b;       // +0x68   second word of the name t_symbol
    char pad7[0x74 - 0x6c];
    void*    gl_symtag;       // +0x74   t_symbol* of the canvas (parent-chain target)
    unsigned gl_flags;        // +0x78
    char pad8[0x80 - 0x7c];
    void*    gl_bind;         // +0x80   guiconnect (editor window) handle
};
// t_editor, the +0x60 payload of an editing canvas.
struct t_editor {
    char pad[0xc];
    void* e_rtext;   // +0xc   rtext list head
};

// Line traverser state, laid out as the original's 0x5c-byte stack record.
struct t_linetraverser {
    t_glist* tr_canvas;    // +0
    t_object* tr_obj;      // +4
    int      tr_nout;      // +8
    int      tr_outno;     // +0xc
    void*    tr_oc;        // +0x10   (t_outconnect* chain cursor)
    void*    tr_oc2;       // +0x14
    t_object* tr_connected; // +0x18
    int      tr_inno;      // +0x1c
    int      tr_nin;       // +0x20
    int      tr_lx1;       // +0x24
    int      tr_ly1;       // +0x28
    int      tr_lx2;       // +0x2c
    int      tr_ly2;       // +0x30
    int      tr_fx1;       // +0x34
    int      tr_fy1;       // +0x38
    int      tr_fx2;       // +0x3c
    int      tr_fy2;       // +0x40
    int      tr_lx3;       // +0x44
    int      tr_ly3;       // +0x48
    int      tr_lx4;       // +0x4c
    int      tr_ly4;       // +0x50
    void*    tr_connline;  // +0x54   current t_outconnect*
    int      tr_walked;    // +0x58
};

// ---------------------------------------------------------------- globals (masked relocs)
extern t_symbol gEmptySymbol;    // 0x167589c  ("empty" name word; used as rename sentinel)
extern t_glist* gpEditingCanvas; // 0x1675470
extern t_glist* gpFocusCanvas;   // 0x1675484
extern t_symbol gLoadbangSym;    // 0x1675488/a  ("loadbang")
extern t_symbol gPauseSym;       // 0x1675468/c  ("pause")
extern void*    gSymPdMinus;     // 0x13ec47c   loadbang message text (empty string atom)
extern const char gNameDefault[4]; // 0x1454548 "Pd" (canvas default name)
extern const char gSp[2];          // 0x13ed024 " "
extern const char gOpenParen[4];   // 0x14544bc " ("
extern const char gCloseParen[4];  // 0x141c5ac ")"

// ---------------------------------------------------------------- externs (masked relocs)
int   strlen_i(const char* s);                                                      // inlined
char* strcpy_i(char* d, const char* s);                                             // inlined
char* strcat_i(char* d, const char* s);                                             // inlined
int   strcmp_i(const char* a, const char* b);                                       // inlined
int   sprintf_i(char* d, const char* fmt, ...);                                     // inlined (msvcr90 sprintf)
void* gensym(t_symbol* out, const char* s);                                          // 0xa675f0
void* pd_findbyclass(unsigned a, void* b, void* c);                                  // 0xa671f0
void  pd_vmess(void* obj, void* sel_a, void* sel_b, void* fmt, ...);                     // 0xa487f0
void  pd_typedmess(void* obj, void* sel_a, void* sel_b, int n, void* atoms);         // 0xa48100
void* zgetfn(void* obj, void* sel_a, void* sel_b);                                   // 0xa488d0
void  glist_noselect(t_glist* g);                                                    // 0xa4d1d0
t_glist* glist_getcanvas(t_glist* g);                                                // 0xa4d410
void  glist_delete(t_glist* g, t_gobj* o);                                           // 0xa4de50
void  pd_bind(void* obj, void* sel_a, void* sel_b);                                  // 0xa67620
bool  pd_checkobject(t_gobj* o);                                                     // 0xa4a1c0
void  pd_pushsym(void* x, ...);                                                      // 0xa49490
void  pd_popsym(void* x, ...);                                                       // 0xa49500
void  canvas_resortinlets(t_glist* g);                                               // 0xa4d4d0
void  canvas_resortoutlets(t_glist* g);                                              // 0xa4d6a0
void  canvas_removewindow(t_glist* g);                                               // 0xa4a3c0
void  canvas_noundo(t_glist* g);                                                     // 0xa4c7e0
void  canvas_setgraph(t_glist* g, int n);                                            // 0xa4ca40
void  gfxstub_deleteforkey(t_glist* g);                                              // 0xa4c170
void  guiconnect_notarget(void* c, void* target);                                    // 0xa4e780
void* guiconnect_new(void* sel_a, void* sel_b, void* target);                        // 0xa4e6c0
void* binbuf_new();                                                                  // 0xa46c20
void  binbuf_free(void* b);                                                          // 0xa46c50
void* getbytes(int n, const char* tag);                                              // 0xa49610
void  freebytes(void* p, int n);                                                     // 0xa49650
void  sys_gui_sym(void* sel_a, void* sel_b, unsigned obj);                           // 0xa671b0 (symbol-form sys_gui)
int   sys_gui(const char* fmt, ...);                                                // 0xc2e4e0 (printf-style)
float atom_getfloat_at(int i, int n, t_atom* a);                                     // 0xa468f0
int   atom_getint_at(int i, int n, t_atom* a);                                       // 0xa46920
void  atom_string(t_atom* a, char* buf, int n);                                      // 0xa469b0
void  rtext_new(t_glist* g, t_gobj* o);                                              // 0xa4e8a0
void  rtext_free(void* r);                                                           // 0xa4e920
void  obj_noutlets_ret();                                                            // placeholder
int   obj_noutlets(t_gobj* o);                                                       // 0xa4a0b0
int   obj_ninlets(t_gobj* o);                                                        // 0xa4a0d0
void* obj_outlet_connections(t_gobj* o, void* out, int n);                           // 0xa4a100
void* obj_connectioninfo(void* c, void* a, void* b, void* d);                        // 0xa4a130
void  obj_disconnect(void* a, void* b, void* c, void* d);                            // 0xa4a010
void  gobj_getrect(t_gobj* o, t_glist* g, int* x1, int* y1, int* x2, int* y2);       // 0xa4c630
void  canvas_getenv_ret();                                                           // placeholder
void* canvas_getenv(void* x);                                                        // 0xa4a490
void  canvas_realizedollar_ret();                                                    // placeholder
void* canvas_getargs_ret();                                                          // placeholder
void  pd_findbyclassret_ret();                                                       // placeholder
void  editor_new_ret();                                                              // placeholder
void  FUN_00a477a0(void* a, void* b, void* c, void* d, int n, void* out);            // 0xa477a0
void* FUN_00a67ce0();                                                                // 0xa67ce0 (gfxstub instance)
void  FUN_00a644e0(void* inst, void* key);                                           // 0xa644e0 (gfxstub_free)
void* FUN_00a643b0(void* inst, void* fn, void* key);                                 // 0xa643b0 (gfxstub_new)
void* FUN_011922c0(void* b);                                                         // 0x11922c0 (ASN1_STRING_type)
int   FUN_011838a0(void* b);                                                         // 0x11838a0 (iterator/pointer)
extern void* gSymClassHash;                                                          // 0x1675490
extern void* gCanvasClassA;                                                          // 0x16758c0
extern void* gCanvasClassB;                                                          // 0x16758bc

// ============================================================ canvas

// @ 0x00a4a500
void canvas_getargs(int* out1, int* out2)
{
    int* p = (int*)pd_findbyclass((unsigned)gSymClassHash, gCanvasClassA, gCanvasClassB);
    while (*(int*)((char*)p + 0x74) == 0)
        p = *(int**)((char*)p + 0x2c);
    int* q = *(int**)((char*)p + 0x74);
    *out1 = *(int*)((char*)q + 8);
    *out2 = *(int*)((char*)q + 0xc);
}

// @ 0x00a4a550
void* canvas_realizedollar(void** out, void* env, void* a3, const char* s)
{
    if (s[0] == '$' && s[1] >= '0' && s[1] <= '9') {
        int* e = (int*)canvas_getenv(env);
        pd_pushsym(env);
        t_symbol tmp;
        t_symbol* g = (t_symbol*)gensym(&tmp, s + 1);
        FUN_00a477a0((void*)g->s_name, (void*)g->s_thing,
                     *(void**)((char*)e + 8), *(void**)((char*)e + 0xc), 1, out);
        pd_popsym(env);
        return out;
    }
    out[0] = a3;
    out[1] = (void*)s;
    return out;
}

// @ 0x00a4a5d0
void* canvas_findtext(int* out, void* x)
{
    while (*(int*)((char*)x + 0x74) == 0)
        x = *(void**)((char*)x + 0x2c);
    int* p = *(int**)((char*)x + 0x74);
    int b = p[1];
    int a = p[0];
    out[1] = b;
    out[0] = a;
    return out;
}

// @ 0x00a4a600
void glist_getname(t_symbol* out, t_glist* g)
{
    out[0].s_name = *(void**)((char*)g + 0x64);
    out[0].s_thing = *(void**)((char*)g + 0x68);
}

// @ 0x00a4a620
int glist_getindex(t_glist* g, void* which)
{
    int n = 0;
    t_gobj* o = *(t_gobj**)((char*)g + 0x28);
    if (o == 0)
        return n;
    while (o != which) {
        o = o->g_next;
        ++n;
        if (o == 0)
            break;
    }
    return n;
}

// @ 0x00a4a640
void linetraverser_start(t_linetraverser* t, t_glist* g)
{
    t->tr_obj = 0;
    t->tr_canvas = g;
    t->tr_connline = 0;
    t->tr_nout = 0;
    t->tr_walked = 0;
}

// @ 0x00a4a660
void canvas_loadbang(t_glist* g)
{
    for (t_gobj* o = *(t_gobj**)((char*)g + 0x28); o != 0; o = o->g_next) {
        if (zgetfn(o, gLoadbangSym.s_name, gLoadbangSym.s_thing) != 0)
            pd_vmess(o, gLoadbangSym.s_name, gLoadbangSym.s_thing, (void*)0x13ec47c);
    }
}

// @ 0x00a4a6b0
int canvas_loadbanghandler(t_glist* g)
{
    t_glist* c = *(t_glist**)((char*)g + 0xc);
    if ((*(unsigned char*)((char*)c + 0x78) & 8) == 0) {
        canvas_loadbang(c);
        *(int*)((char*)c + 0x80) = 0;
        return 0;
    }
    return 1;
}

// @ 0x00a4a6e0
void canvas_pause(t_glist* g, float v)
{
    int atoms[3];
    atoms[0] = 1;
    *(float*)&atoms[1] = v;
    for (t_gobj* o = *(t_gobj**)((char*)g + 0x28); o != 0; o = o->g_next) {
        if (zgetfn(o, gPauseSym.s_name, gPauseSym.s_thing) != 0)
            pd_typedmess(o, gPauseSym.s_name, gPauseSym.s_thing, 1, atoms);
    }
}

// @ 0x00a4a750
void canvas_coords(t_glist* g, int a2, int a3, int argc, t_atom* argv)
{
    *(float*)((char*)g + 0x38) = atom_getfloat_at(0, argc, argv);
    *(float*)((char*)g + 0x3c) = atom_getfloat_at(1, argc, argv);
    *(float*)((char*)g + 0x40) = atom_getfloat_at(2, argc, argv);
    *(float*)((char*)g + 0x44) = atom_getfloat_at(3, argc, argv);
    *(int*)((char*)g + 0x30) = atom_getint_at(4, argc, argv);
    *(int*)((char*)g + 0x34) = atom_getint_at(5, argc, argv);
    if (argc > 7) {
        *(int*)((char*)g + 0x58) = atom_getint_at(7, argc, argv);
        *(int*)((char*)g + 0x5c) = atom_getint_at(8, argc, argv);
        canvas_setgraph(g, atom_getint_at(6, argc, argv));
        return;
    }
    canvas_setgraph(g, atom_getint_at(6, argc, argv));
}

// @ 0x00a4a800
int glist_isgraph(t_glist* g)
{
    return (int)((*(unsigned*)((char*)g + 0x78) >> 8) & 1);
}

// @ 0x00a4a810
void* canvas_makebindsym(t_symbol* out, void* a2, const char* name)
{
    char buf[1000];
    buf[0] = 'p'; buf[1] = 'd'; buf[2] = '-'; buf[3] = 0;
    strcat_i(buf, name);
    gensym(out, buf);
    return out;
}

// @ 0x00a4a870
void canvas_reflecttitle(t_glist* g)
{
    char buf[500];
    t_glist* c = g;
    while (*(t_symbol**)((char*)c + 0x74) == 0)
        c = *(t_glist**)((char*)c + 0x2c);
    t_symbol* name = *(t_symbol**)((char*)c + 0x74);
    if (*(int*)((char*)name + 8) == 0) {
        buf[0] = 0;
    } else {
        int n = *(int*)((char*)name + 8);
        strcpy_i(buf, gOpenParen);
        int i;
        for (i = 0; i < n; i++) {
            if (strlen_i(buf) > 0x1ef)
                break;
            if (i != 0)
                strcat_i(buf, gSp);
            atom_string((t_atom*)(*(char**)((char*)name + 0xc) + i * 0xc),
                        buf + strlen_i(buf), 500);
        }
        strcat_i(buf, gCloseParen);
    }
    t_glist* c2 = g;
    while (*(t_symbol**)((char*)c2 + 0x74) == 0)
        c2 = *(t_glist**)((char*)c2 + 0x2c);
    t_symbol* nm = *(t_symbol**)((char*)c2 + 0x74);
    unsigned titlech = (*(unsigned*)((char*)g + 0x78) & 4) ? 0x2a : 0x20;
    sys_gui("wm title .x%lx {%s%c%s - %s}\n",
             (unsigned)*(void**)((char*)g + 0x68),
             (char*)nm->s_name,
             titlech, buf, (char*)nm->s_thing);
}

// @ 0x00a4a9a0
void canvas_drawredrect(t_glist* g, int flag)
{
    if (flag != 0) {
        sys_gui(".x%lx.c create line            %d %d %d %d %d %d %d %d %d %d -fill #ff8080 -tags GOP\n",
                 (unsigned)glist_getcanvas(g),
                 *(int*)((char*)g + 0x58), *(int*)((char*)g + 0x5c),
                 *(int*)((char*)g + 0x30) + *(int*)((char*)g + 0x58),
                 *(int*)((char*)g + 0x34) + *(int*)((char*)g + 0x5c),
                 *(int*)((char*)g + 0x30) + *(int*)((char*)g + 0x58),
                 *(int*)((char*)g + 0x34),
                 *(int*)((char*)g + 0x30),
                 *(int*)((char*)g + 0x34) + *(int*)((char*)g + 0x5c),
                 *(int*)((char*)g + 0x30),
                 *(int*)((char*)g + 0x34));
        return;
    }
    sys_gui(".x%lx.c delete GOP\n", (unsigned)glist_getcanvas(g));
}

// @ 0x00a4aa00
void* editor_new(t_glist* glist)
{
    void* x = getbytes(0x54, "EAPd/t_editor");
    *(void**)((char*)x + 0x24) = binbuf_new();
    *(void**)((char*)x + 0x28) = binbuf_new();
    *(t_glist**)((char*)x + 0x30) = glist;
    if (*(unsigned char*)((char*)glist + 0x78) & 1) {
        char buf[40];
        t_symbol tmp;
        sprintf_i(buf, ".x%lx", (unsigned)glist);
        t_symbol* s = (t_symbol*)gensym(&tmp, buf);
        *(void**)((char*)x + 0x2c) = guiconnect_new(s->s_name, s->s_thing, glist);
    } else {
        *(void**)((char*)x + 0x2c) = 0;
    }
    return x;
}

// @ 0x00a4aa80
void editor_free(void* x, t_glist* glist)
{
    glist_noselect(glist);
    if (*(void**)((char*)x + 0x2c) != 0)
        guiconnect_notarget(*(void**)((char*)x + 0x2c), *(void**)((char*)x + 0x30));
    binbuf_free(*(void**)((char*)x + 0x24));
    binbuf_free(*(void**)((char*)x + 0x28));
    freebytes(x, 0x54);
}

// @ 0x00a4aac0
void canvas_create_editor(t_glist* g, int flag)
{
    if (flag == 0) {
        if (*(void**)((char*)g + 0x60) == 0)
            return;
        while (*(void**)(*(char**)((char*)g + 0x60) + 0xc) != 0)
            rtext_free(*(void**)(*(char**)((char*)g + 0x60) + 0xc));
        editor_free(*(void**)((char*)g + 0x60), g);
        *(void**)((char*)g + 0x60) = 0;
    } else {
        if (*(void**)((char*)g + 0x60) != 0)
            return;
        *(void**)((char*)g + 0x60) = editor_new(g);
        for (t_gobj* o = *(t_gobj**)((char*)g + 0x28); o != 0; o = o->g_next) {
            t_gobj* c = (t_gobj*)pd_checkobject(o);
            if (c != 0)
                rtext_new(g, c);
        }
    }
}

// @ 0x00a4ab40
int glist_isvisible(t_glist* g)
{
    if ((*(unsigned char*)((char*)g + 0x78) & 8) == 0) {
        int c = (int)glist_getcanvas(g);
        if ((*(unsigned char*)((char*)c + 0x78) & 2) != 0)
            return 1;
    }
    return 0;
}

// @ 0x00a4ab70
int glist_istoplevel(t_glist* g)
{
    unsigned f = *(unsigned*)((char*)g + 0x78);
    if ((f & 1) == 0 && (f & 0x100) != 0)
        return 0;
    return 1;
}

// @ 0x00a4ab90
void* canvas_gettext(t_glist* g)
{
    while (*(void**)((char*)g + 0x74) == 0)
        g = *(t_glist**)((char*)g + 0x2c);
    return *(void**)((char*)g + 0x6c);
}

// @ 0x00a4abb0
void canvas_free(t_glist* g)
{
    if (g == 0)
        return;
    if (*(void**)((char*)g + 0x80) != 0) {
        void* e = FUN_00a67ce0();
        FUN_00a644e0(e, *(void**)((char*)g + 0x80));
        *(void**)((char*)g + 0x80) = 0;
    }
    canvas_noundo(g);
    if (gpEditingCanvas == g)
        gpEditingCanvas = 0;
    if (gpFocusCanvas == g)
        gpFocusCanvas = 0;
    glist_noselect(g);
    if ((*(unsigned char*)((char*)g + 0x78) & 8) == 0)
        glist_getcanvas(g);
    while (*(void**)((char*)g + 0x28) != 0)
        glist_delete(g, *(t_gobj**)((char*)g + 0x28));
    if (*(void**)((char*)g + 0x60) != 0) {
        while (*(void**)(*(char**)((char*)g + 0x60) + 0xc) != 0)
            rtext_free(*(void**)(*(char**)((char*)g + 0x60) + 0xc));
        editor_free(*(void**)((char*)g + 0x60), g);
        *(void**)((char*)g + 0x60) = 0;
    }
    if (strcmp_i(*(const char**)((char*)g + 0x68), gNameDefault) != 0) {
        t_symbol tmp;
        t_symbol* s = (t_symbol*)canvas_makebindsym(&tmp, *(void**)((char*)g + 100), *(const char**)((char*)g + 0x68));
        sys_gui("windows unmappedcanvas %s\n", s->s_name);
    }
    if (*(void**)((char*)g + 0x74) != 0) {
        void* t = *(void**)((char*)g + 0x74);
        freebytes(*(void**)((char*)t + 0xc), *(int*)((char*)t + 8) * 0xc);
        freebytes(t, 0x14);
    }
    gfxstub_deleteforkey(g);
    if (*(void**)((char*)g + 0x2c) == 0)
        canvas_removewindow(g);
}

// @ 0x00a4ad10
void canvas_pop(t_glist* g)
{
    pd_popsym(g);
    canvas_resortinlets(g);
    canvas_resortoutlets(g);
    *(unsigned*)((char*)g + 0x78) &= ~8u;
    void* p = FUN_00a67ce0();
    *(void**)((char*)g + 0x80) = FUN_00a643b0(p, g, (void*)0x00a4a6b0);
}

// @ 0x00a4ad50
int canvas_isopen(t_glist* g)
{
    return *(int*)((char*)g + 0x74) != 0;
}

// @ 0x00a4ad60
int canvas_istable(t_glist* g)
{
    int* i1 = 0;
    if (*(void**)((char*)g + 8) != 0)
        i1 = (int*)FUN_011922c0(*(void**)((char*)g + 8));
    if (*(void**)((char*)g + 8) != 0) {
        int i2 = FUN_011838a0(*(void**)((char*)g + 8));
        if (i2 != 0 && *i1 == 2) {
            t_symbol tmp;
            t_symbol* s = (t_symbol*)gensym(&tmp, "table");
            if (i1[1] == (int)s->s_name)
                return 1;
        }
    }
    return 0;
}

// @ 0x00a4add0
int canvas_showtext(t_glist* g)
{
    int* i1 = 0;
    if (*(void**)((char*)g + 8) != 0)
        i1 = (int*)FUN_011922c0(*(void**)((char*)g + 8));
    if (*(void**)((char*)g + 8) != 0) {
        int i2 = FUN_011838a0(*(void**)((char*)g + 8));
        if (i2 != 0 && *i1 == 2) {
            t_symbol tmp;
            t_symbol* s = (t_symbol*)gensym(&tmp, "graph");
            if (i1[1] == (int)s->s_name)
                return 0;
        }
    }
    return 1;
}

// @ 0x00a4ae50
void canvas_rename(t_glist* g, void* name_a, const char* name_b, void* a4, void* a5)
{
    if (strcmp_i(*(const char**)((char*)g + 0x68), gNameDefault) != 0) {
        t_symbol tmp;
        t_symbol* s = (t_symbol*)canvas_makebindsym(&tmp, *(void**)((char*)g + 100), *(const char**)((char*)g + 0x68));
        sys_gui("windows map .x%lx %s\n", (unsigned)g, s->s_name);
    }
    *(void**)((char*)g + 100) = name_a;
    *(const char**)((char*)g + 0x68) = name_b;
    if (strcmp_i(name_b, gNameDefault) != 0) {
        t_symbol tmp;
        t_symbol* s = (t_symbol*)canvas_makebindsym(&tmp, name_a, name_b);
        pd_bind(g, s->s_name, s->s_thing);
    }
    if ((*(unsigned char*)((char*)g + 0x78) & 8) == 0 &&
        (*(unsigned char*)((char*)glist_getcanvas(g) + 0x78) & 2) != 0)
        canvas_reflecttitle(g);
    if (a4 != (void*)&gEmptySymbol) {
        t_glist* c = g;
        while (*(t_symbol**)((char*)c + 0x74) == 0)
            c = *(t_glist**)((char*)c + 0x2c);
        t_symbol* nm = *(t_symbol**)((char*)c + 0x74);
        nm->s_name = a4;
        nm->s_thing = a5;
    }
}

// ============================================================ linetraverser

// @ 0x00a4af60
void* linetraverser_next(t_linetraverser* t)
{
    void* conn = t->tr_connline;
    if (conn == 0) {
        for (;;) {
            if (t->tr_walked == t->tr_nout) {
                for (;;) {
                    t_gobj* o = t->tr_obj == 0
                        ? *(t_gobj**)((char*)t->tr_canvas + 0x28)
                        : t->tr_obj->g_next;
                    while (o != 0) {
                        t_gobj* c = (t_gobj*)pd_checkobject(o);
                        if (c != 0) { o = c; break; }
                        o = o->g_next;
                    }
                    if (o == 0)
                        return 0;
                    t->tr_obj = (t_object*)o;
                    t->tr_nout = obj_noutlets((t_gobj*)o);
                    t->tr_walked = 0;
                    if ((*(unsigned char*)((char*)t->tr_canvas + 0x78) & 8) == 0 &&
                        (*(unsigned char*)((char*)glist_getcanvas(t->tr_canvas) + 0x78) & 2) != 0) {
                        gobj_getrect((t_gobj*)o, t->tr_canvas,
                                     &t->tr_lx1, &t->tr_ly1, &t->tr_lx2, &t->tr_ly2);
                    } else {
                        t->tr_ly2 = 0; t->tr_lx2 = 0; t->tr_ly1 = 0; t->tr_lx1 = 0;
                    }
                    if (t->tr_nout != 0)
                        break;
                }
            }
            t->tr_walked = t->tr_walked + 1;
            conn = obj_outlet_connections((t_gobj*)t->tr_obj, &t->tr_oc2, t->tr_walked - 1);
            t->tr_outno = t->tr_walked - 1;
            if (conn != 0)
                break;
            t->tr_walked -= 1;
        }
    }
    void* oc = obj_connectioninfo(conn, &t->tr_oc, &t->tr_connected, &t->tr_nin);
    t->tr_connline = oc;
    t->tr_inno = obj_ninlets((t_gobj*)t->tr_oc);
    if ((*(unsigned char*)((char*)t->tr_canvas + 0x78) & 8) == 0 &&
        (*(unsigned char*)((char*)glist_getcanvas(t->tr_canvas) + 0x78) & 2) != 0) {
        int d1 = t->tr_nin == 1 ? 1 : t->tr_nin - 1;
        int d2 = t->tr_nout == 1 ? 1 : t->tr_nout - 1;
        gobj_getrect((t_gobj*)t->tr_connected, t->tr_canvas,
                     &t->tr_fx1, &t->tr_fy1, &t->tr_fx2, &t->tr_fy2);
        t->tr_ly4 = t->tr_ly2;
        t->tr_lx4 = ((t->tr_ly2 - t->tr_ly1 - 7) * t->tr_walked) / d2 + 3 + t->tr_ly1;
        t->tr_ly3 = t->tr_fy1;
        t->tr_lx3 = ((t->tr_fx2 - t->tr_fx1 - 7) * t->tr_nin) / d1 + 3 + t->tr_fx1;
    } else {
        t->tr_fy1 = 0; t->tr_fx1 = 0; t->tr_fy2 = 0; t->tr_fx2 = 0;
        t->tr_ly3 = 0; t->tr_lx3 = 0; t->tr_ly4 = 0; t->tr_lx4 = 0;
    }
    return conn;
}

// @ 0x00a4b140
void canvas_drawlines(t_glist* canvas)
{
    t_linetraverser t;
    char* p = (char*)&t;
    *(int*)(p + 0x00) = (int)canvas;
    t.tr_obj = 0; t.tr_nout = 0; t.tr_outno = 0; t.tr_oc = 0;
    t.tr_oc2 = 0; t.tr_connected = 0; t.tr_inno = 0; t.tr_nin = 0;
    t.tr_connline = 0; t.tr_walked = 0;
    int l = (int)linetraverser_next(&t);
    while (l != 0) {
        sys_gui(".x%lx.c create line %d %d %d %d -width %d -tags l%lx\n",
                 (unsigned)glist_getcanvas(canvas),
                 t.tr_lx1, t.tr_ly1, t.tr_lx2, t.tr_ly2, 1, l);
        l = (int)linetraverser_next(&t);
    }
}

// @ 0x00a4b1c0
void canvas_fixlinesfor(t_glist* canvas, void* obj)
{
    t_linetraverser t;
    char* p = (char*)&t;
    *(int*)(p + 0x00) = (int)canvas;
    t.tr_obj = 0; t.tr_nout = 0; t.tr_outno = 0; t.tr_oc = 0;
    t.tr_oc2 = 0; t.tr_connected = 0; t.tr_inno = 0; t.tr_nin = 0;
    t.tr_connline = 0; t.tr_walked = 0;
    int l = (int)linetraverser_next(&t);
    while (l != 0) {
        if (t.tr_obj == (t_object*)obj || t.tr_oc == (void*)obj) {
            sys_gui(".x%lx.c coords l%lx %d %d %d %d\n",
                     (unsigned)glist_getcanvas(canvas),
                     l, t.tr_lx1, t.tr_ly1, t.tr_lx2, t.tr_ly2);
        }
        l = (int)linetraverser_next(&t);
    }
}

// @ 0x00a4b250
void canvas_deletelinesfor(t_glist* canvas, void* obj)
{
    t_linetraverser t;
    char* p = (char*)&t;
    *(int*)(p + 0x00) = (int)canvas;
    t.tr_obj = 0; t.tr_nout = 0; t.tr_outno = 0; t.tr_oc = 0;
    t.tr_oc2 = 0; t.tr_connected = 0; t.tr_inno = 0; t.tr_nin = 0;
    t.tr_connline = 0; t.tr_walked = 0;
    int l = (int)linetraverser_next(&t);
    while (l != 0) {
        if (t.tr_obj == (t_object*)obj || t.tr_oc == obj) {
            if (*(void**)((char*)canvas + 0x60) != 0)
                sys_gui(".x%lx.c delete l%lx\n", (unsigned)glist_getcanvas(canvas), l);
            obj_disconnect((void*)t.tr_obj, (void*)t.tr_outno, t.tr_oc, (void*)t.tr_nin);
        }
        l = (int)linetraverser_next(&t);
    }
}

// @ 0x00a4b2f0
void canvas_deletelinesforio(t_glist* canvas, void* src, void* dst, void* ins)
{
    t_linetraverser t;
    char* p = (char*)&t;
    *(int*)(p + 0x00) = (int)canvas;
    t.tr_obj = 0; t.tr_nout = 0; t.tr_outno = 0; t.tr_oc = 0;
    t.tr_oc2 = 0; t.tr_connected = 0; t.tr_inno = 0; t.tr_nin = 0;
    t.tr_connline = 0; t.tr_walked = 0;
    int l = (int)linetraverser_next(&t);
    while (l != 0) {
        if ((t.tr_obj == (t_object*)src && t.tr_oc2 == ins) ||
            (t.tr_oc == src && t.tr_connected == (t_object*)dst)) {
            if (*(void**)((char*)canvas + 0x60) != 0)
                sys_gui(".x%lx.c delete l%lx\n", (unsigned)glist_getcanvas(canvas), l);
            obj_disconnect((void*)t.tr_obj, (void*)t.tr_outno, t.tr_oc, (void*)t.tr_nin);
        }
        l = (int)linetraverser_next(&t);
    }
}

}}} // namespace EA::Audio::Eapd
