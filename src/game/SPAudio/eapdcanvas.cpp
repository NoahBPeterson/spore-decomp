// src/game/SPAudio/eapdcanvas.cpp -- migrated from slice(s) s00a4a500, s00a49670, s00a4b3a0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdcanvas.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern uint32_t gHashXSymbol;           // 0x016758bc
extern uint32_t gSymbolArg2;            // 0x016758c0
extern uint32_t gpCanvasClass;          // 0x01675490
extern uint32_t gEmptySymbol;           // 0x0167589c
extern uint32_t gSymbol5;               // 0x016758a0
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

// ---- items of slice s00a4b3a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSymPair {                       // gensym() result, also the FUN_00a477a0 out pair
    uint32_t a;
    uint32_t b;
};
struct cPdInfo {
    uint8_t pad00[8];
    uint32_t mA8;                       // +0x08
    uint32_t mAc;                       // +0x0c
};
struct cPdObj {
    uint8_t pad00[0x2c];
    cPdObj* mpNext;                     // +0x2c
    uint8_t pad30[0x74 - 0x30];
    cPdInfo* mpInfo;                    // +0x74
};
struct cCanvas {
    uint8_t pad00[0x2c];
    cPdObj* mpObj;                      // +0x2c
    uint8_t pad30[0x78 - 0x30];
    uint32_t mFlags;                    // +0x78
    uint8_t pad7c[0x80 - 0x7c];
    uint32_t mHelperResult;             // +0x80
};
struct cAtom {
    uint8_t pad00[0x24];
    int32_t mType;                      // +0x24 (2 symbol, 7 digit arg, 8 gensym'd symbol)
    uint32_t mW0;                       // +0x28
    uint32_t mW1;                       // +0x2c (char* for a symbol)
};
struct cCanvasFactory {
    uint32_t FUN_00a643b0(cCanvas* c, void (*fn)());     // 0x00a643b0 (thiscall, 2 args)
};
extern uint32_t gHashXSymbol;           // 0x016758bc
extern uint32_t gSymbolArg2;            // 0x016758c0
extern uint32_t gpCanvasClass;          // 0x01675490
extern uint32_t gEmptySymbol;           // 0x0167589c
extern uint32_t gSymbol5;               // 0x016758a0
cPdObj* pd_findbyclass(uint32_t a, uint32_t b, uint32_t c);   // 0x00a671f0
void pd_popsym(cCanvas* c);                                    // 0x00a49500
void canvas_resortinlets(cCanvas* c);                          // 0x00a4d4d0
void canvas_resortoutlets(cCanvas* c);                         // 0x00a4d6a0
void canvas_rename(cCanvas* c, uint32_t a, uint32_t b, uint32_t emptySym, uint32_t sym5);   // 0x00a4ae50
void canvas_objfor(cPdObj* o, cCanvas* c, int argc, cAtom* av);   // 0x00a4f590
cSymPair* gensym(cSymPair* out, const char* s);                // 0x00a675f0
void FUN_00a477a0(uint32_t a, uint32_t b, uint32_t c, uint32_t d, int e, cSymPair* out);   // 0x00a477a0
cCanvasFactory* FUN_00a67ce0();                                // 0x00a67ce0
void FUN_00a4a6b0();                                           // 0x00a4a6b0 (callback)
// ---- items of slice s00a4b3a0 end

// ---- items of slice s00a49670 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct t_object;
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
struct t_outconnect;
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
typedef t_class* t_pd;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
inline bool operator==(const t_symbol& a, const t_symbol& b) { return a.mHash == b.mHash; }
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_methodentry {
    t_symbol me_name;     // +0
    void*    me_fun;      // +8
    int      me_arg[6];   // +0xc
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class {
    char pad00[0x1c];
    t_methodentry* c_methods;                        // +0x1c
    int            c_nmethod;                        // +0x20
    char pad24[4];
    void (*c_bangmethod)(t_pd* x);                   // +0x28
    void (*c_floatmethod)(t_pd* x, float f);         // +0x2c
    void (*c_symbolmethod)(t_pd* x, t_symbol s);     // +0x30
    char pad34[0x49 - 0x34];
    char c_isobject;                                 // +0x49 (pd_checkobject)
    char c_firstin;                                  // +0x4a (first inlet is the object)
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gobj {
    t_class* g_pd;        // +0x00
    t_gobj*  g_next;      // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_object : t_gobj {
    void*     te_binbuf;  // +0x08
    t_outlet* te_outlet;  // +0x0c
    t_inlet*  te_inlet;   // +0x10
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_inlet {              // 0x28
    t_class*  i_pd;           // +0x00
    t_inlet*  i_next;         // +0x04
    t_object* i_owner;        // +0x08
    t_pd*     i_dest;         // +0x0c
    t_symbol  i_symfrom;      // +0x10
    union {
        t_symbol i_symto;     // +0x18 (message inlet)
        void*    i_destp;     // +0x18 (float/symbol inlet destination)
    } u;
    t_symbol  i_symempty;     // +0x20
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outconnect {         // 8
    t_outconnect* oc_next;    // +0
    t_inlet*      oc_to;      // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outlet {             // 0x1c
    t_object*     o_owner;        // +0x00
    t_outlet*     o_next;         // +0x04
    t_outconnect* o_connections;  // +0x08
    t_symbol      o_symfrom;      // +0x0c
    t_symbol      o_symto;        // +0x14
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_canvasenv {
    char pad00[0x10];
    void* ce_dollarzero;   // +0x10
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_glist {
    t_object  gl_obj;         // +0x00
    char      pad14[0x14];    // +0x14
    t_gobj*   gl_list;        // +0x28
    t_glist*  gl_owner;       // +0x2c
    char      pad30[0x38];    // +0x30
    const char* gl_name;      // +0x68
    void*     gl_x6c;         // +0x6c
    t_glist*  gl_nextwin;     // +0x70
    t_canvasenv* gl_env;      // +0x74
    unsigned  gl_havewindow : 1;   // +0x78
    void*     gl_instance;    // +0x7c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_glist* gpCanvasList;          // 0x1675464
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol gSymNewFile;           // 0x1675474
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol gSymNewFile2;          // 0x167547c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol gHashXSymbol_s00a4_9670;          // 0x16758bc
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* gpCanvasClass_s00a4_9670;         // 0x1675490
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_pd* pd_findbyclass(t_symbol s, t_class* c);                    // 0xa671f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  sys_gui(const char* cmd);                                  // 0xc2e4e0
}
}
}
// ---- items of slice s00a49670 end

// ---- items of slice s00a4a500 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class_s00a4_a500;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gobj_s00a4_a500;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_glist_s00a4_a500;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol_s00a4_a500 {
    void* s_name;    // +0
    void* s_thing;   // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class_s00a4_a500 {
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
    t_class_s00a4_a500* c_next;      // +0x4c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gobj_s00a4_a500 {
    t_class_s00a4_a500* g_pd;    // +0
    t_gobj_s00a4_a500*  g_next;  // +4
    char pad[0x24 - 8];
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_object_s00a4_a500 : t_gobj_s00a4_a500 {
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom {
    int   a_type;    // +0
    float a_w;       // +4
    void* a_w2;      // +8
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_glist_s00a4_a500 {
    t_gobj_s00a4_a500   g_gobj;          // +0
    void*    g_pd;            // +0x24   (t_glist's own gobj pd pointer reused here)
    void*    gl_list;         // +0x28   first gobj of the list
    t_glist_s00a4_a500* gl_owner;        // +0x2c   parent (canvas) OR next in a chain depending on flags
    char pad3[0x60 - 0x30];
    void*    gl_editor;       // +0x60   t_editor* (0 when not editing)
    void*    gl_name_a;       // +0x64   first word of the name t_symbol
    void*    gl_name_b;       // +0x68   second word of the name t_symbol
    char pad6c[4];
    t_glist_s00a4_a500* gl_nextwin;     // +0x70   next root canvas
    void*    gl_symtag;       // +0x74   t_symbol* of the canvas (parent-chain target)
    unsigned gl_flags;        // +0x78
    char pad8[0x80 - 0x7c];
    void*    gl_bind;         // +0x80   guiconnect (editor window) handle
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_linetraverser {
    t_glist_s00a4_a500* tr_canvas;    // +0
    t_object_s00a4_a500* tr_obj;      // +4
    int      tr_nout;      // +8
    int      tr_outno;     // +0xc
    void*    tr_oc;        // +0x10   (t_outconnect* chain cursor)
    void*    tr_oc2;       // +0x14
    t_object_s00a4_a500* tr_connected; // +0x18
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
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
char* strcat_i(char* d, const char* s);                                             // inlined
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   sprintf_i(char* d, const char* fmt, ...);                                     // inlined (msvcr90 sprintf)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* gensym(t_symbol_s00a4_a500* out, const char* s);                                          // 0xa675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* pd_findbyclass(unsigned a, void* b, void* c);                                  // 0xa671f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_glist_s00a4_a500* glist_getcanvas(t_glist_s00a4_a500* g);                                                // 0xa4d410
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_gobj_s00a4_a500* pd_checkobject(t_gobj_s00a4_a500* o);                                                   // 0xa4a1c0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_pushsym(void* x, ...);                                                      // 0xa49490
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_popsym(void* x, ...);                                                       // 0xa49500
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  canvas_setgraph(t_glist_s00a4_a500* g, int n);                                            // 0xa4ca40
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* guiconnect_new(void* sel_a, void* sel_b, void* target);                        // 0xa4e6c0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* binbuf_new();                                                                  // 0xa46c20
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* getbytes(int n, const char* tag);                                              // 0xa49610
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
float atom_getfloat_at(int i, int n, t_atom* a);                                     // 0xa468f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   atom_getint_at(int i, int n, t_atom* a);                                       // 0xa46920
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   obj_noutlets(t_gobj_s00a4_a500* o);                                                       // 0xa4a0b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   obj_ninlets(t_gobj_s00a4_a500* o);                                                        // 0xa4a0d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* obj_outlet_connections(t_gobj_s00a4_a500* o, void* out, int n);                           // 0xa4a100
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* obj_connectioninfo(void* c, void* a, void* b, void* d);                        // 0xa4a130
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  gobj_getrect(t_gobj_s00a4_a500* o, t_glist_s00a4_a500* g, int* x1, int* y1, int* x2, int* y2);       // 0xa4c630
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* canvas_getenv(void* x);                                                        // 0xa4a490
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  FUN_00a477a0(void* a, void* b, void* c, void* d, int n, void* out);            // 0xa477a0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern void* gSymClassHash;                                                          // 0x1675490
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern void* gCanvasClassA;                                                          // 0x16758c0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern void* gCanvasClassB;                                                          // 0x16758bc
}
}
}
// ---- items of slice s00a4a500 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace EA { namespace Audio { namespace Eapd { void canvas_loadbang(t_glist_s00a4_a500* g); }}}  // 0x00a4a660 (stays in the slice: not this object's)

// @ 0x00a4a260
namespace EA { namespace Audio { namespace Eapd {
void glist_doupdatewindowlist(t_glist* x, char* buf)
{
    char local[1024];

    if (x->gl_havewindow) {
        if (strlen(buf) + strlen(x->gl_name) + 100 <= 1024) {
            sprintf(local, "{%s .x%lx} ", x->gl_name, x);
            strcat(buf, local);
        }
    }
    {
        t_gobj* g;
        for (g = x->gl_list; g; g = g->g_next) {
            if (g->g_pd == gpCanvasClass_s00a4_9670)
                glist_doupdatewindowlist((t_glist*)g, buf);
        }
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a320
namespace EA {
namespace Audio {
namespace Eapd {
void canvas_updatewindowlist()
{
    char buf[1024];
    t_glist* g;

    memcpy(buf, "pdtk_updatewindowlist {", 24);
    for (g = gpCanvasList; g; g = g->gl_nextwin) {
        if (g)
            glist_doupdatewindowlist(g, buf);
    }
    strcat(buf, "}\n");
    sys_gui(buf);
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a4a3f0
namespace EA { namespace Audio { namespace Eapd {
void FUN_00a4a3f0(t_symbol s)
{
    gSymNewFile2 = s;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a410
namespace EA { namespace Audio { namespace Eapd {
void FUN_00a4a410(t_symbol s)
{
    gSymNewFile = s;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a430
namespace EA { namespace Audio { namespace Eapd {
t_glist* canvas_getcurrent()
{
    return (t_glist*)pd_findbyclass(gHashXSymbol_s00a4_9670, gpCanvasClass_s00a4_9670);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a450
namespace EA { namespace Audio { namespace Eapd {
void* canvas_getcurrentinstance()
{
    t_glist* x = (t_glist*)pd_findbyclass(gHashXSymbol_s00a4_9670, gpCanvasClass_s00a4_9670);
    return x->gl_instance;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a490
namespace EA { namespace Audio { namespace Eapd {
t_canvasenv* canvas_getenv(t_glist* x)
{
    while (!x->gl_env)
        x = x->gl_owner;
    return x->gl_env;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a4b0
namespace EA { namespace Audio { namespace Eapd {
void* canvas_getdollarzero()
{
    t_glist* x = (t_glist*)pd_findbyclass(gHashXSymbol_s00a4_9670, gpCanvasClass_s00a4_9670);
    t_canvasenv* env = (x ? canvas_getenv(x) : 0);
    if (env)
        return env->ce_dollarzero;
    else
        return 0;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a500
namespace EA { namespace Audio { namespace Eapd {
void canvas_getargs(int* out1, int* out2)
{
    int* p = (int*)pd_findbyclass((unsigned)gSymClassHash, gCanvasClassA, gCanvasClassB);
    while (*(int*)((char*)p + 0x74) == 0)
        p = *(int**)((char*)p + 0x2c);
    int* q = *(int**)((char*)p + 0x74);
    *out1 = *(int*)((char*)q + 8);
    *out2 = *(int*)((char*)q + 0xc);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a550
namespace EA { namespace Audio { namespace Eapd {
void* canvas_realizedollar(void** out, void* env, void* a3, const char* s)
{
    if (s[0] == '$' && s[1] >= '0' && s[1] <= '9') {
        int* e = (int*)canvas_getenv(env);
        pd_pushsym(env);
        t_symbol_s00a4_a500 tmp;
        t_symbol_s00a4_a500* g = (t_symbol_s00a4_a500*)gensym(&tmp, s + 1);
        FUN_00a477a0((void*)g->s_name, (void*)g->s_thing,
                     *(void**)((char*)e + 8), *(void**)((char*)e + 0xc), 1, out);
        pd_popsym(env);
        return out;
    }
    out[0] = a3;
    out[1] = (void*)s;
    return out;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a5d0
namespace EA { namespace Audio { namespace Eapd {
void* canvas_findtext(int* __restrict out, void* x)
{
    while (((t_glist_s00a4_a500*)x)->gl_symtag == 0)
        x = ((t_glist_s00a4_a500*)x)->gl_owner;
    const t_symbol_s00a4_a500* p = (const t_symbol_s00a4_a500*)((t_glist_s00a4_a500*)x)->gl_symtag;
    t_symbol_s00a4_a500* result = (t_symbol_s00a4_a500*)out;
    *result = *p;
    return result;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a6b0
namespace EA { namespace Audio { namespace Eapd {
int canvas_loadbanghandler(t_glist_s00a4_a500* g)
{
    t_glist_s00a4_a500* c = *(t_glist_s00a4_a500**)((char*)g + 0xc);
    if ((*(unsigned char*)((char*)c + 0x78) & 8) == 0) {
        canvas_loadbang(c);
        int r = 0;
        *(void**)((char*)c + 0x80) = (void*)r;
        return r;
    }
    return 1;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a750
namespace EA { namespace Audio { namespace Eapd {
void canvas_coords(t_glist_s00a4_a500* g, int a2, int a3, int argc, t_atom* argv)
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a810
namespace EA { namespace Audio { namespace Eapd {
void* canvas_makebindsym(t_symbol_s00a4_a500* out, void* a2, const char* name)
{
    char buf[1000];
    buf[0] = 'p'; buf[1] = 'd'; buf[2] = '-'; buf[3] = 0;
    strcat_i(buf, name);
    gensym(out, buf);
    return out;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4aa00
namespace EA { namespace Audio { namespace Eapd {
static void* editor_new(t_glist_s00a4_a500* glist)
{
    void* x = getbytes(0x54, "EAPd/t_editor");
    *(void**)((char*)x + 0x24) = binbuf_new();
    *(void**)((char*)x + 0x28) = binbuf_new();
    *(t_glist_s00a4_a500**)((char*)x + 0x30) = glist;
    if (*(unsigned char*)((char*)glist + 0x78) & 1) {
        char buf[40];
        t_symbol_s00a4_a500 tmp;
        sprintf_i(buf, ".x%lx", (unsigned)glist);
        t_symbol_s00a4_a500* s = (t_symbol_s00a4_a500*)gensym(&tmp, buf);
        *(void**)((char*)x + 0x2c) = guiconnect_new(s->s_name, s->s_thing, glist);
    } else {
        *(void**)((char*)x + 0x2c) = 0;
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4af60
namespace EA { namespace Audio { namespace Eapd {
void* linetraverser_next(t_linetraverser* t)
{
    void* conn = t->tr_connline;
    if (conn == 0) {
        for (;;) {
            if (t->tr_walked == t->tr_nout) {
                for (;;) {
                    t_gobj_s00a4_a500* o = t->tr_obj == 0
                        ? *(t_gobj_s00a4_a500**)((char*)t->tr_canvas + 0x28)
                        : t->tr_obj->g_next;
                    while (o != 0) {
                        t_gobj_s00a4_a500* c = (t_gobj_s00a4_a500*)pd_checkobject(o);
                        if (c != 0) { o = c; break; }
                        o = o->g_next;
                    }
                    if (o == 0)
                        return 0;
                    t->tr_obj = (t_object_s00a4_a500*)o;
                    t->tr_nout = obj_noutlets((t_gobj_s00a4_a500*)o);
                    t->tr_walked = 0;
                    if ((*(unsigned char*)((char*)t->tr_canvas + 0x78) & 8) == 0 &&
                        (*(unsigned char*)((char*)glist_getcanvas(t->tr_canvas) + 0x78) & 2) != 0) {
                        gobj_getrect((t_gobj_s00a4_a500*)o, t->tr_canvas,
                                     &t->tr_lx1, &t->tr_ly1, &t->tr_lx2, &t->tr_ly2);
                    } else {
                        t->tr_ly2 = 0; t->tr_lx2 = 0; t->tr_ly1 = 0; t->tr_lx1 = 0;
                    }
                    if (t->tr_nout != 0)
                        break;
                }
            }
            t->tr_walked = t->tr_walked + 1;
            conn = obj_outlet_connections((t_gobj_s00a4_a500*)t->tr_obj, &t->tr_oc2, t->tr_walked - 1);
            t->tr_outno = t->tr_walked - 1;
            if (conn != 0)
                break;
            t->tr_walked -= 1;
        }
    }
    void* oc = obj_connectioninfo(conn, &t->tr_oc, &t->tr_connected, &t->tr_nin);
    t->tr_connline = oc;
    t->tr_inno = obj_ninlets((t_gobj_s00a4_a500*)t->tr_oc);
    if ((*(unsigned char*)((char*)t->tr_canvas + 0x78) & 8) == 0 &&
        (*(unsigned char*)((char*)glist_getcanvas(t->tr_canvas) + 0x78) & 2) != 0) {
        int d1 = t->tr_nin == 1 ? 1 : t->tr_nin - 1;
        int d2 = t->tr_nout == 1 ? 1 : t->tr_nout - 1;
        gobj_getrect((t_gobj_s00a4_a500*)t->tr_connected, t->tr_canvas,
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4b3a0
void FUN_00a4b3a0(cCanvas* c, int a2, int a3, int argc, cAtom* av)
{
    cSymPair local;

    if (argc > 3) {
        if (av->mType == 2 && ((const char*)av->mW1)[0] == '$') {
            const char* s = (const char*)av->mW1;
            if (s[1] >= '0' && s[1] <= '9') {
                const char* p = s + 2;
                bool bad = false;
                while (*p != 0) {
                    if (*p < '0' || '9' < *p) {
                        bad = true;
                        break;
                    }
                    ++p;
                }
                if (bad) {
                    av->mType = 8;
                    cSymPair* sp = gensym(&local, s + 1);
                    av->mW0 = sp->a;
                    av->mW1 = sp->b;
                } else {
                    av->mType = 7;
                    av->mW0 = (uint32_t)atoi(s + 1);
                }
            }
        }

        if (av->mType == 8) {
            cPdObj* o = pd_findbyclass(gHashXSymbol, gSymbolArg2, gpCanvasClass);
            while (o->mpInfo == 0)
                o = o->mpNext;
            cPdInfo* info = o->mpInfo;
            FUN_00a477a0(av->mW0, av->mW1, info->mA8, info->mAc, 1, &local);
            canvas_rename(c, local.a, local.b, gEmptySymbol, gSymbol5);
        } else if (av->mType == 2) {
            canvas_rename(c, av->mW0, av->mW1, gEmptySymbol, gSymbol5);
        }
    }

    pd_popsym(c);
    canvas_resortinlets(c);
    canvas_resortoutlets(c);
    c->mFlags &= 0xfffffff7u;
    cCanvasFactory* f = FUN_00a67ce0();
    c->mHelperResult = f->FUN_00a643b0(c, FUN_00a4a6b0);
    cPdObj* o2 = pd_findbyclass(gHashXSymbol, gSymbolArg2, gpCanvasClass);
    if (o2) {
        c->mpObj = o2;
        canvas_objfor(o2, c, argc, av);
    }
}
