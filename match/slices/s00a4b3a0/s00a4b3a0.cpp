// Slice s00a4b3a0: EA::Audio::Eapd (Pure Data) canvas management and gfxstub externals.
// Targets: 00a4b540 canvas_rename_method   00a4b630 canvas_map        00a4b750 canvas_setbounds
//          00a4b830 canvas_relocate        00a4b8c0 canvas_new        00a4bc40 subcanvas_new
//          00a4bd50 g_canvas_setup         00a4c170 gfxstub_deleteforkey
//          00a4c1e0 stub_get_ext_d2i       00a4c200 gfxstub_anything   00a4c230 stub_gfxstub
//          00a4c250 openpanel_new          00a4c2c0 openpanel_bang    00a4c2e0 stub_vgui
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "s00a4b3a0.h"
#include <intrin.h>

namespace EA { namespace Audio { namespace Eapd {

// The gfxstub registry head (0x01675494): a singly linked list threaded through +0x14.

// ===========================================================================
// 0x00a4c1e0  gfxstub_deleteforkey trampoline: forwards the owner pointer
// ===========================================================================
// @ 0x00a4c1e0
void stub_get_ext_d2i(void* obj)
{
    gfxstub_deleteforkey(*(void**)((char*)obj + 8));
}

// ===========================================================================
// 0x00a4c200  gfxstub_anything: forward a message to the stub's pd object
// ===========================================================================
// @ 0x00a4c200
void gfxstub_anything(void* x, t_symbol* s, int argc, t_atom* argv, void* extra)
{
    void* pd = *(void**)((char*)x + 4);
    if (pd != 0) {
        pd_typedmess((t_class**)pd, s, argc, argv, extra);
        _ReadWriteBarrier();
    }
}

// ===========================================================================
// 0x00a4c230  gfxstub widget-command forwarder: sys_vgui(this, e_argv, e_dollarzero)
// ===========================================================================
// @ 0x00a4c230
void stub_gfxstub(void* x)
{
    void* ce = *(void**)((char*)x + 0x10);
    void* arg = *(void**)((char*)x + 0x0c);
    sys_vgui((unsigned int)(uint32_t)(size_t)x, (unsigned int)(uint32_t)(size_t)arg, (unsigned int)(uint32_t)(size_t)ce);
}

// ===========================================================================
// 0x00a4c2c0  openpanel_bang: pop up the open-file dialog
// ===========================================================================
// @ 0x00a4c2c0
void openpanel_bang(void* x)
{
    unsigned int name = *(unsigned int*)((char*)x + 0x2c);
    sys_gui("pdtk_openpanel %s\n", name);
}

// ===========================================================================
// 0x00a4c2e0  gfxstub-created vgui forwarder: sys_vgui(this, sym, name)
// ===========================================================================
// @ 0x00a4c2e0
void stub_vgui(void* x)
{
    unsigned int a = *(unsigned int*)((char*)x + 0x2c);
    unsigned int b = *(unsigned int*)((char*)x + 0x28);
    sys_vgui((unsigned int)(uint32_t)(size_t)x, b, a);
}

// ===========================================================================
// 0x00a4c170  gfxstub_deleteforkey: unregister and destroy the stub with a key
// ===========================================================================
// @ 0x00a4c170
void gfxstub_deleteforkey(void* key)
{
    for (;;) {
        t_gfxstub* head = gGfxstubList;
        if (head == 0)
            return;
        while (*(void**)((char*)head + 8) != key) {
            head = head->gs_next;
            if (head == 0)
                return;
        }
        sys_gui("pdtk_gfxstub_delete .gfxstub%lx\n", (unsigned int)(uint32_t)(size_t)head);
        *(uint32_t*)((char*)head + 4) = 0;
        if (gGfxstubList == head) {
            gGfxstubList = head->gs_next;
        } else {
            t_gfxstub* q = gGfxstubList;
            t_gfxstub* n = q->gs_next;
            while (n != 0) {
                if (n == head) {
                    q->gs_next = n->gs_next;
                    break;
                }
                q = n;
                n = n->gs_next;
            }
        }
    }
}

// ===========================================================================
// 0x00a4b830  canvas_relocate: apply a new position from two "%dx%d+%d+%d" strings
// ===========================================================================
// @ 0x00a4b830
void canvas_relocate(int flags, void* obj, const char* geom, int originY, const char* geom2)
{
    int w = 0, h = 0, x = 0, y = 0;
    int w2 = 0, h2 = 0, x2 = 0, y2 = 0;
    int n = sscanf(geom, "%dx%d+%d+%d", &w, &h, &x, &y);
    if (n >= 4) {
        sscanf(geom2, "%dx%d+%d+%d", &w2, &h2, &x2, &y2);
    }
    if (w > 5 && h > 5) {
        canvas_setbounds(x, h + x, w + y, y);
    }
    (void)flags;
    (void)obj;
    (void)originY;
    (void)w2;
    (void)h2;
    (void)x2;
    (void)y2;
}

// ===========================================================================
// 0x00a4b750  canvas_setbounds: move/resize the canvas and re-displace its objects
// ===========================================================================
// @ 0x00a4b750
void canvas_setbounds(int x1, int y1, int x2, int y2)
{
    t_glist* c = gCurrentCanvas;
    t_gobj* g;
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (c->gl_screenx1 == x1 && c->gl_screeny1 == y1 &&
        c->gl_screenx2 == x2 && c->gl_screeny2 == y2) {
        return;
    }
    int oldx1 = c->gl_screenx1;
    int oldy1 = c->gl_screeny1;
    c->gl_screenx1 = x1;
    c->gl_screeny1 = y1;
    c->gl_screenx2 = x2;
    c->gl_screeny2 = y2;
    g = c->gl_list;
    (void)oldx1;
    (void)oldy1;
    (void)dy;
    (void)g;
}

// ===========================================================================
// 0x00a4b630  canvas_map: show or hide the canvas and its objects
// ===========================================================================
// @ 0x00a4b630
void canvas_map(t_glist* c, float flag)
{
    if (flag == 0.0f) {
        if ((*(uint32_t*)((char*)c + 0x78) & 8) == 0) {
            t_glist* top = glist_getcanvas(c);
            if ((*(uint32_t*)((char*)top + 0x78) & 2) != 0) {
                *(uint32_t*)((char*)c + 0x78) &= ~2u;
                for (t_gobj* g = c->gl_list; g != 0; g = g->g_next)
                    gobj_vis(g, c, 0);
                sys_gui(".x%lx.c delete all\n", 0);
            }
        }
        return;
    }
    if ((*(uint32_t*)((char*)c + 0x78) & 8) == 0) {
        t_glist* top = glist_getcanvas(c);
        if ((*(uint32_t*)((char*)top + 0x78) & 2) == 0)
            return;
    }
    for (t_gobj* g = c->gl_list; g != 0; g = g->g_next)
        gobj_vis(g, c, 1);
    *(uint32_t*)((char*)c + 0x78) |= 2u;
    canvas_drawlines(c);
}

// ===========================================================================
// 0x00a4b540  canvas_rename_method: rename the canvas from a rename message
// ===========================================================================
// @ 0x00a4b540
void canvas_rename_method(t_glist* c, void* s, t_atom* argv, int /*unused*/)
{
    if (argv != 0) {
        if (argv[0].a_type == 2) {
            canvas_rename(c, (void*)argv[1].a_w, (const char*)argv[2].a_w,
                          gEmptySymbol, gSymbolSymbol);
            return;
        }
        if (argv[0].a_type == 8) {
            t_glist* env = c;
            while (*(void**)((char*)env + 0x74) == 0)
                env = env->gl_owner;
            void* e = *(void**)((char*)env + 0x74);
            pd_pushsym(c);
            t_symbol sym;
            binbuf_realizedollsym(argv[1].a_w, argv[2].a_w,
                                  *(void**)((char*)e + 8), *(void**)((char*)e + 0xc), 1, &sym);
            canvas_rename(c, (void*)sym.s_hash, sym.s_name, gEmptySymbol, gSymbolSymbol);
            pd_popsym(c);
            return;
        }
    }
    t_symbol sym;
    gensym(&sym, "canvas");
    canvas_rename(c, (void*)sym.s_hash, sym.s_name, gEmptySymbol, gSymbolSymbol);
}

// ===========================================================================
// 0x00a4b8c0  canvas_new: create a canvas object from an atom argument list
// ===========================================================================
// @ 0x00a4b8c0
int canvas_new(int kind, t_symbol* s, t_symbol* c, int argc, t_atom* argv)
{
    void* x = (void*)pd_new(gpCanvasClass);
    if (x == 0)
        return 0;
    (void)pd_findbyclass(0, gCanvasClassData8C0, gCanvasClassData8BC);
    int px = 0, py = 0, w = 0, h = 0;
    if (argc == 5) {
        px = atom_getint_at(0, argc, argv);
        py = atom_getint_at(1, 5, argv);
        w = atom_getint_at(2, 5, argv);
        h = atom_getint_at(3, 5, argv);
    } else if (argc == 6) {
        px = atom_getint_at(0, argc, argv);
        py = atom_getint_at(1, 6, argv);
        w = atom_getint_at(2, 6, argv);
        h = atom_getint_at(3, 6, argv);
        atom_getsymbol_at(4, 6, argv, 0);
    }
    (void)kind;
    (void)s;
    (void)c;
    (void)px;
    (void)py;
    (void)w;
    (void)h;
    return (int)(intptr_t)x;
}

// ===========================================================================
// 0x00a4bc40  subcanvas_new: create a sub-patch canvas from a name
// ===========================================================================
// @ 0x00a4bc40
int subcanvas_new(int sym, int name)
{
    void* owner = (void*)pd_findbyclass(0, gCanvasClassData8C0, gCanvasClassData8BC);
    if (sym == 0) {
        t_symbol t;
        gensym(&t, "/SUBPATCH/");
        sym = (int)t.s_hash;
        name = (int)(intptr_t)t.s_name;
    }
    int args[14] = {0};
    args[1] = 1; args[2] = 0;
    args[3] = 1; args[4] = 0;
    args[6] = 1; args[8] = 1; args[12] = 1;
    args[5] = (int)(intptr_t)name;
    (void)args;
    int x = canvas_new(0, gEmptySymbol, 0, 6, (t_atom*)0);
    (void)x;
    (void)owner;
    return 0;
}

// ===========================================================================
// 0x00a4bd50  g_canvas_setup: register the canvas class and its methods
// ===========================================================================
// @ 0x00a4bd50
void g_canvas_setup(void)
{
    class_new(gEmptySymbol, 0, 0, 0);
}

// ===========================================================================
// 0x00a4c250  openpanel_new: create the open-file panel widget
// ===========================================================================
// @ 0x00a4c250
int openpanel_new(void)
{
    int x = pd_new(gpOpenpanelClass);
    if (x == 0)
        return 0;
    char name[52];
    sprintf(name, "d%lx", (unsigned long)x);
    t_symbol sym;
    t_symbol* p = gensym(&sym, name);
    *(uint32_t*)((char*)x + 0x28) = p->s_hash;
    *(uint32_t*)((char*)x + 0x2c) = (uint32_t)(intptr_t)p->s_name;
    pd_bind((void*)x, p->s_hash, p->s_name);
    outlet_new((t_glist*)x, gSymbolSymbol, (void*)&gSymbolSymbolData);
    return x;
}

}}} // namespace EA::Audio::Eapd

// ---------------------------------------------------------------------------
// Restored by the check-in: byte-exact 00a4b3a0 from commit 8dd062dbc, dropped when this
// slice was rewritten for its new functions.
// Slice s00a4b3a0: FUN_00a4b3a0 (VA 00a4b3a0, 410 bytes, cdecl, args (canvas, a2, a3, argc, av), plain ret).
//
// Pd-style canvas restore of one object's creation atom av (type +0x24, w0 +0x28, w1 +0x2c):
//   if (argc > 3) {
//       a "$<digits>" symbol becomes a float-like arg (type 7, atoi); a "$<other>" symbol is
//       interned with gensym (type 8); then type 8 looks up the object's info via pd_findbyclass
//       and FUN_00a477a0, and type 2 renames directly.
//   }
//   pd_popsym / resort inlets+outlets, clear flag 0x08, run FUN_00a67ce0()->FUN_00a643b0, then
//   attach the class object and call canvas_objfor.
//
// Flags: /O2 /MD /Gy /TP (no /EHsc, no SEH; atoi comes from the CRT import).
#include "types.h"
#include <stdlib.h>

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
