// src/game/SPAudio/eapdcanvas.cpp -- migrated from slice(s) s00a49670, s00a4b3a0 by tools/migrate/rewrite.py
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
    t_canvasenv* env;

    if (x == 0) {
        env = 0;
    } else {
        while (!x->gl_env)
            x = x->gl_owner;
        env = x->gl_env;
    }
    if (env == 0) {
        return 0;
    }
    return env->ce_dollarzero;
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
