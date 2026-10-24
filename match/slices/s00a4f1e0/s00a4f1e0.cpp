// Slice s00a4f1e0 -- EA::Audio::Eapd: the Pure-Data-derived text / message / gatom widgets
// plus the small gatom helpers, and the canvas object-creation machinery in gold7.
//
// Object layouts, taken from the retail disassembly:
//
//   t_text / t_message ("Text")             t_gatom ("Gatom")
//     (0x00) class ptr                        (0x00) class ptr
//     (0x04) te_outlet                        (0x04) te_outlet
//     (0x08) te_binbuf                        (0x08) te_binbuf
//     (0x14) te_xpix (short)                  (0x14) te_xpix (short)
//     (0x16) te_ypix (short)                  (0x16) te_ypix (short)
//     (0x18) te_w    (short)                  (0x18) te_w    (short)
//     (0x1c) te_flags                         (0x1c) te_flags
//     (0x28) te_pd    (the receiver)          (0x28) a_atom   (12 bytes)
//     (0x2c) te_msgout                        (0x34) a_glist
//     (0x30) te_glist                         (0x3c) a_max
//     (0x34) te_clock                         (0x40) a_min
//                                             (0x5c) a_dirty
//                                             (0x84) a_grabbed
//
// The atom type codes are the Pd ones: 1 FLOAT, 2 SYMBOL, 4 SEMI, 7 DOLLAR, 8 DOLLSYM.
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed short   i16;
typedef signed int     i32;

struct Glist;                       // opaque canvas/glist

struct t_symbol {
    u32         mHash;              // +0x00
    const char* mpName;             // +0x04
};

struct t_atom {
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
    t_atom a_atom;                  // +0x28
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

// ---------------------------------------------------------------- globals ----
extern void* gpTextClass;           // 0x16754f0 the "comment" text class
extern void* gpMsgClass;            // 0x16754fc the message class
extern void* gpMessagePd;           // 0x16754f8 receiver pd of a message box
extern void* gpNewestObject;        // 0x16753f4 last object created by an eval
extern void* gpObjTextPd;           // 0x16753e8 eval target used by canvas_objtext
extern void* gpTextInletClass;      // 0x167582c
extern void* gpTextOutletClass;     // 0x1675830
extern void* gpOutletTypeSym;       // 0x16758c8 second symbol given to outlet_new

extern t_symbol gEmptySymbol;       // 0x167589c
extern t_symbol gFloatSymbol;       // 0x16758c4

// ---------------------------------------------------------------- callees ----
void*     pd_new(void* cls);                                            // 0x00a49390
void*     binbuf_new(void);                                             // 0x00a46c20
void      binbuf_clear(void* b);                                        // 0x00a46c80
void      binbuf_add(void* b, int argc, t_atom* argv);                  // 0x00a471a0
void      binbuf_addsemi(void* b);                                      // 0x00a47540
void      binbuf_addtext(void* b, int argc, t_atom* argv);              // 0x00a47570
void      binbuf_eval(void* b, void* target, int argc, t_atom* argv);   // 0x00a478b0
void      binbuf_gettextbuf(void* b, char* buf, int n);                 // 0x00a47780
float     atom_getfloat_at(int n, int argc, t_atom* argv);              // 0x00a468f0
int       atom_getint_at(int n, int argc, t_atom* argv);                // 0x00a46920
float     atom_getfloat(t_atom* a);                                     // 0x00a46760
t_symbol* atom_getsymbol(t_symbol* out, t_atom* a);                     // 0x00a46790
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
void*     outlet_new(void* owner, t_symbol s, void* s2);                // 0x00a49d30
void*     clock_new(void* owner, void* fn);                             // 0x00a49080
void      clock_free(void* c);                                          // 0x00a49260
void      clock_delay(void* c, float f);                                // 0x00a491e0
void      gatom_bang(Gatom* x);                                         // 0x00a4fdb0 (other slice)
void      sys_gui(void* a, void* b, void* c);                           // 0x00c2e4e0
int       FUN_011838a0(void* p);                                        // 0x011838a0
void      FUN_00a4c690(void* obj, void* gl, int f);                     // 0x00a4c690
double    iat_floor(double d);                                          // 0x011e0906
char*     strncpy_imp(char* d, const char* s, int n);                   // msvcr90 strncpy

static t_symbol gGensymScratch;     // per-call name scratch, as in Pd's gensym

// ===========================================================================
// @ 0x00a4f1e0
void glist_text(Glist* gl, t_symbol s, int argc, t_atom* argv)
{
    (void)s;
    t_atom a;
    t_symbol scratch;
    int ypos;
    int xpos;
    Text* x = (Text*)pd_new(gpTextClass);
    if (x == 0)
        return;
    x->te_flags &= 0xfffffffc;
    x->te_w = 0;
    x->te_binbuf = binbuf_new();
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

// ===========================================================================
// @ 0x00a4f380
void canvas_objtext(Glist* gl, void* b, i16 xpix, i16 ypix, int created)
{
    Text* x = 0;
    gpNewestObject = 0;
    pd_pushsym();
    int argc = 0;
    t_atom* argv = 0;
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

// ===========================================================================
// @ 0x00a4f4b0
void canvas_obj(Glist* gl, t_symbol s, int argc, t_atom* argv)
{
    (void)s;
    void* b = binbuf_new();
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

// ===========================================================================
// @ 0x00a4f590
void canvas_objfor(Glist* gl, Text* x, int argc, t_atom* argv)
{
    x->te_w = 0;
    x->te_flags = (x->te_flags & 0xfffffffd) | 1;
    x->te_binbuf = binbuf_new();
    x->te_xpix = (i16)atom_getfloat_at(0, argc, argv);
    x->te_ypix = (i16)atom_getfloat_at(1, argc, argv);
    if (argc > 2)
        binbuf_addtext(x->te_binbuf, argc - 2, argv + 2);
    glist_add(gl, x);
}

// ===========================================================================
// @ 0x00a4f670
void messresponder_symbol(Text* x, t_symbol s)
{
    outlet_symbol(x->te_outlet, s);
}

// ===========================================================================
// @ 0x00a4f6f0
void message_bang(Text* x)
{
    binbuf_eval(x->te_binbuf, (void*)&x->te_pd, 0, 0);
}

// ===========================================================================
// @ 0x00a4f710
void message_float(Text* x, float f)
{
    t_atom a;
    a.a_type = 1;
    a.a_w.a_float = f;
    binbuf_eval(x->te_binbuf, (void*)&x->te_pd, 1, &a);
}

// ===========================================================================
// @ 0x00a4f750
void message_symbol(Text* x, t_symbol s)
{
    t_atom a;
    a.a_type = 2;
    a.a_w.a_symbol = s;
    binbuf_eval(x->te_binbuf, (void*)&x->te_pd, 1, &a);
}

// ===========================================================================
// @ 0x00a4f790
void message_list(Text* x, t_symbol s, int argc, t_atom* argv)
{
    (void)s;
    binbuf_eval(x->te_binbuf, (void*)&x->te_pd, argc, argv);
}

// ===========================================================================
// @ 0x00a4f7b0
// Retail bounds cover two adjacent methods; only the first is marker-bound.
void message_set(Text* x, t_symbol s, u32 p4, int argc, t_atom* argv)
{
    (void)s; (void)p4;
    binbuf_clear(x->te_binbuf);
    binbuf_add(x->te_binbuf, argc, argv);
    glist_retext(x->te_glist, x);
}

void message_add(Text* x, t_symbol s, int argc, t_atom* argv)
{
    (void)s;
    binbuf_add(x->te_binbuf, argc, argv);
    glist_retext(x->te_glist, x);
}

// ===========================================================================
// @ 0x00a4f810
// Retail bounds cover two adjacent methods; only the first is marker-bound.
void message_add2(Text* x, t_symbol s, int argc, t_atom* argv)
{
    (void)s;
    binbuf_add(x->te_binbuf, argc, argv);
    binbuf_addsemi(x->te_binbuf);
    glist_retext(x->te_glist, x);
}

void message_addsemi(Text* x)
{
    t_atom a;
    a.a_type = 4;
    a.a_w.a_int = 0;
    binbuf_add(x->te_binbuf, 1, &a);
    glist_retext(x->te_glist, x);
}

// ===========================================================================
// @ 0x00a4f880
void message_addcomma(Text* x)
{
    binbuf_add(x->te_binbuf, 0, 0);
    binbuf_addsemi(x->te_binbuf);
    glist_retext(x->te_glist, x);
}

// ===========================================================================
// @ 0x00a4f8b0
void message_adddollar(Text* x, float f)
{
    t_atom a;
    i32 i = (i32)f;
    if (i < 0)
        i = 0;
    a.a_type = 7;
    a.a_w.a_int = i;
    binbuf_add(x->te_binbuf, 1, &a);
    glist_retext(x->te_glist, x);
}

// ===========================================================================
// @ 0x00a4f900
void message_adddollsym(Text* x, t_symbol s)
{
    t_atom a;
    a.a_type = 8;
    a.a_w.a_symbol = s;
    binbuf_add(x->te_binbuf, 1, &a);
    glist_retext(x->te_glist, x);
}

// ===========================================================================
// @ 0x00a4f950
void message_click(Text* x)
{
    t_atom a;
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

// ===========================================================================
// @ 0x00a4f9e0
void message_tick(Text* x)
{
    if (!glist_isvisible(x->te_glist))
        return;
    sys_gui((void*)".x%lx.c itemconfigure %sR -width 1\n",
            glist_getcanvas(x->te_glist),
            rtext_gettag(glist_findrtext(x->te_glist, x)));
}

// ===========================================================================
// @ 0x00a4fa30
// Retail bounds cover a 12-byte clock_free tail-jmp thunk plus canvas_msg.
void clock_free_msg(Text* x)
{
    clock_free(x->te_clock);
}

void canvas_msg(Glist* gl, t_symbol s, int argc, t_atom* argv)
{
    (void)s;
    Text* x = (Text*)pd_new(gpMsgClass);
    if (x == 0)
        return;
    x->te_pd = gpMessagePd;
    x->te_msgout = outlet_new(x, gFloatSymbol, gpOutletTypeSym);
    x->te_flags = (x->te_flags & 0xfffffffe) | 2;
    x->te_w = 0;
    x->te_binbuf = binbuf_new();
    x->te_glist = gl;
    x->te_clock = clock_new(x, (void*)message_tick);
    if (argc > 1)
    {
        x->te_xpix = (i16)atom_getfloat_at(0, argc, argv);
        x->te_ypix = (i16)atom_getfloat_at(1, argc, argv);
        if (argc > 2)
            binbuf_addtext(x->te_binbuf, argc - 2, argv + 2);
        glist_add(gl, x);
        return;
    }
    {
        t_symbol sym = *gensym(&gGensymScratch, "editmode");
        pd_vmess(gl, sym, "i", 1);
    }
    glist_noselect(gl);
    int lx = 0, ly = 0;
    canvas_getlastxy(gl, &lx, &ly);
    x->te_xpix = (i16)(lx - 3);
    x->te_ypix = (i16)(ly - 3);
    glist_add(gl, x);
    glist_noselect(gl);
    glist_select(gl, x);
    FUN_00a4c690(x, gl, 1);
    canvas_startmotion(glist_getcanvas(gl));
}

// ===========================================================================
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

// ===========================================================================
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

// ===========================================================================
// @ 0x00a4fce0
void FUN_00a4fce0(Gatom* x)
{
    glist_retext(x->a_glist, x);
}

// ===========================================================================
// @ 0x00a4fd00
void gatom_retext(Gatom* x, int flag)
{
    binbuf_clear(x->te_binbuf);
    binbuf_add(x->te_binbuf, 1, &x->a_atom);
    if (flag != 0 && glist_isvisible(x->a_glist) != 0)
        sys_gui((void*)x, x->a_glist, (void*)FUN_00a4fce0);
}

// ===========================================================================
// @ 0x00a4fd50
void gatom_set(Gatom* x, t_symbol s, int argc, t_atom* argv)
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

// ===========================================================================
// @ 0x00a4fe90
void gatom_float(Gatom* x, float f)
{
    t_atom a;
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

// ===========================================================================
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

// ===========================================================================
// @ 0x00a4ff70
void gatom_symbol(Gatom* x, t_symbol s)
{
    t_atom a;
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

// ===========================================================================
// @ 0x00a4fff0
// Drag handler for a gatom: a_grabbed == 0 snaps the new value to a 1/100 grid,
// otherwise the drag is coarse (1/100 of the delta).  The retail FP sequence is
// only approximated here.
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
// ---------------------------------------------------------------------------
// Restored by the check-in: byte-exact 00a4fdb0 from commit 8dd062dbc, dropped when this
// slice was rewritten for its new functions.
// Slice s00a4f1e0: EA::Audio::Eapd::gatom_bang (0x00a4fdb0, 221 bytes). __cdecl, one t_gatom* arg, plain ret.
// Callees (all cdecl, caller pops): outlet_float(to, f) 0x00a49570, outlet_symbol(outlet, sym) 0x00a49df0,
// pd_send_float(a, b, f) 0x00a67230, pd_send_symbol(a, b, sym) 0x00a67250.
// Offsets are from the disassembly: +0x0c outlet, +0x28 a_type (1 float, 2 symbol), +0x2c value (float or
// t_symbol), +0x4c / +0x54 symbol pointers, +0x88 / +0x8c send target words.
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

struct t_symbol {               // by-value pair: hash at +0, name pointer at +4
    uint32_t    mHash;
    const char* mpName;
};

struct t_connection {
    t_connection* oc_next;      // +0
    void*         oc_to;        // +4: inlet the connection feeds
};

struct t_outlet {
    uint32_t       pad00[2];
    t_connection*  o_connections;   // +0x08
};

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

// Reentrancy depth of gatom_bang's outlet loop (global at 0x0167545c).
extern int gBangDepth;
// The empty symbol (global at 0x0167589c, compared by value).
extern t_symbol* gEmptySymbol;

void outlet_float(void* to, float f);                              // 0x00a49570
void outlet_symbol(t_outlet* o, t_symbol s);                       // 0x00a49df0
void pd_send_float(uint32_t a, uint32_t b, float f);               // 0x00a67230
void pd_send_symbol(uint32_t a, uint32_t b, t_symbol s);           // 0x00a67250

// @ 0x00a4fdb0
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

}}}
