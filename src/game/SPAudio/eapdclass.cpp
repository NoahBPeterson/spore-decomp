// src/game/SPAudio/eapdclass.cpp -- migrated from slice(s) s00a488d0, s00a478b0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdclass.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stdarg.h>
#include <string.h>

// ---- items of slice s00a478b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct t_atom {           // 12 bytes
    int a_type;
    union {
        float    w_float;
        int      w_index;
        t_symbol w_symbol;
    } a_w;
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
enum { A_NULL = 0, A_FLOAT = 1, A_SYMBOL = 2, A_SEMI = 3, A_COMMA = 4, A_DEFFLOAT = 5, A_DEFSYM = 6,
       A_DOLLAR = 7, A_DOLLSYM = 8, A_GIMME = 9 };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
enum { MAXPDARG = 5 };
}
}
}
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
typedef t_class* t_pd;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_methodentry {     // 0x24 bytes
    t_symbol me_name;      // +0
    void*    me_fun;       // +8
    int      me_arg[MAXPDARG + 1];   // +0xc
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class {
    char pad00[8];
    t_symbol       c_helpname;                                  // +0x08 ("<name>-help")
    char pad10[0xc];
    t_methodentry* c_methods;                                   // +0x1c
    int            c_nmethod;                                   // +0x20
    char pad24[4];
    void (*c_bangmethod)(t_pd* x);                              // +0x28
    void (*c_floatmethod)(t_pd* x, float f);                    // +0x2c
    void (*c_symbolmethod)(t_pd* x, t_symbol s);                // +0x30
    void (*c_listmethod)(t_pd* x, t_symbol s, int argc, t_atom* argv);   // +0x34
    void (*c_anymethod)(t_pd* x, t_symbol s, int argc, t_atom* argv);    // +0x38
    void*          c_propertiesfn;                              // +0x3c
    void*          c_savefn;                                    // +0x40
    void*          c_drawfunction;                              // +0x44
    char           c_pad48;                                     // +0x48
    char           c_gobj;         // +0x49: graphical object (has an outlet list)
    char           c_pad4a[2];
    t_class*       c_next;                                      // +0x4c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol s_float;       // 0x16758c4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol s_bang;        // 0x16758b4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol s_list;        // 0x16758ac
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol s_symbol;      // 0x1675894
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol s_;            // 0x167589c (empty symbol)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_pd pd_objectmaker;    // 0x16753e8
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_pd* pd_newest;        // 0x16753f4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef t_pd* (*t_newgimme)(t_symbol s, int argc, t_atom* argv);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef void (*t_messgimme)(t_pd* x, t_symbol s, int argc, t_atom* argv);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef t_pd* (*t_new0)(float, float, float, float, float);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef t_pd* (*t_new1)(t_symbol, float, float, float, float, float);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef t_pd* (*t_new2)(t_symbol, t_symbol, float, float, float, float, float);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef t_pd* (*t_new3)(t_symbol, t_symbol, t_symbol, float, float, float, float, float);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef t_pd* (*t_new4)(t_symbol, t_symbol, t_symbol, t_symbol, float, float, float, float, float);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef t_pd* (*t_new5)(t_symbol, t_symbol, t_symbol, t_symbol, t_symbol, float, float, float, float, float);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef void (*t_fun0)(t_pd*, float, float, float, float, float);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef void (*t_fun1)(t_pd*, t_symbol, float, float, float, float, float);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef void (*t_fun2)(t_pd*, t_symbol, t_symbol, float, float, float, float, float);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef void (*t_fun3)(t_pd*, t_symbol, t_symbol, t_symbol, float, float, float, float, float);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef void (*t_fun4)(t_pd*, t_symbol, t_symbol, t_symbol, t_symbol, float, float, float, float, float);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef void (*t_fun5)(t_pd*, t_symbol, t_symbol, t_symbol, t_symbol, t_symbol, float, float, float, float, float);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol* gensym(t_symbol* out, const char* name);                        // 0x00a675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  freebytes(void* p, int n);                                          // 0x00a49650
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* resizebytes(void* p, int oldsize, int newsize, const char* tag);    // 0x00a49670
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  sys_vgui_sym(uint32_t obj, uint32_t sel, uint32_t arg);             // 0x00a671b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  sys_gui(t_pd* x, t_symbol s, int argc, t_atom* argv);               // 0x00c2e4e0 (empty stub)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_vmess(t_pd* x, t_symbol s, const char* fmt, ...);                // 0x00a487f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* gpCanvasMaker; // 0x1675408
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* gClassList;    // 0x167540c  class_add() list
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol gObjectSym;    // 0x16758a4  "object"
}
}
}
// ---- items of slice s00a478b0 end

// ---- items of slice s00a488d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uintptr_t;   // VS2008 <stdint.h> absent from types.h
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class_s00a4_88d0;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol_s00a4_88d0 {
    void* s_name;    // +0
    void* s_thing;   // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class_s00a4_88d0 {
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
    t_class_s00a4_88d0* c_next;      // +0x4c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom_s00a4_88d0 {
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
extern t_class_s00a4_88d0*    gpObjectMaker;   // 0x16753e8
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class_s00a4_88d0*    gpTemplateMaker; // 0x1675408
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class_s00a4_88d0*    gclasslist;      // 0x167540c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a4_88d0    gListSymbol;     // 0x16753ec  (list selector copy; 0x16753f8/0x1675400 are later copies)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a4_88d0    gListSym3;       // 0x1675400  (third "list" copy)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a4_88d0    gListSymB;       // 0x16753f8  (second "list" copy)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a4_88d0    gFloatSymbol;    // 0x16758c4 / c8   ("float")
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a4_88d0    gAnythingSym;    // 0x167589c / a0   ("anything")
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a4_88d0    gListSym2;       // 0x16758ac / b0   ("list", used by pd_list)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern void*       gAnythingThing;  // 0x16753f0  (second word of the "anything" copy)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern void* gBangName;             // 0x16758b4  ("bang")
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern void* gFloatName;            // 0x16758c4  ("float")
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern void* gSymbolName;           // 0x1675894  ("symbol")
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern void* gListName;             // 0x16758ac  ("list")
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern void* gAnythingName;         // 0x16758cc  ("anything")
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a4_88d0    gObjectSym_s00a4_88d0;      // 0x16758a4 / a8
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
inline unsigned int strlen(const char* s) { unsigned int n = 0; while (s[n]) ++n; return n; }
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
inline int strcmp(const char* a, const char* b) { while (*a && *a == *b) { ++a; ++b; } return (unsigned char)*a - (unsigned char)*b; }
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* gensym(t_symbol_s00a4_88d0* out, const char* s);                                    // 0xa675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool  class_addmethod(t_class_s00a4_88d0* c, void* fn, void* sel_lo, void* sel_hi, int* atoms); // 0xa47e70
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool  class_addlist(t_class_s00a4_88d0* c, void* fn);                                     // 0xa47f70
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool  class_addanything(t_class_s00a4_88d0* c, void* fn);                                 // 0xa47f90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  class_addpointer(t_class_s00a4_88d0* c, void* fn, void* name_hi);                   // 0xa47fc0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  sys_gui_release(void* obj, void* sel_a, void* sel_b);                    // 0xa67620
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* getbytes(int n, const char* tag);                                        // 0xa49610
}
}
}
// ---- items of slice s00a488d0 end

// @ 0x00a47e30
namespace EA {
namespace Audio {
namespace Eapd {
bool clearallclasses()
{
    t_class* c = gClassList;

    gClassList = 0;
    while (c) {
        t_class* next = c->c_next;
        freebytes(c->c_methods, 0);
        freebytes(c, 0);
        c = next;
    }
    return true;
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a47e70
namespace EA { namespace Audio { namespace Eapd {
bool class_addmethod(t_class* c, void* fn, t_symbol name, const int* types)
{
    bool ok = false;

    if (!c)
        return ok;
    if (!fn)
        return ok;
    int size = c->c_nmethod * (int)sizeof(t_methodentry);
    t_methodentry* p = (t_methodentry*)resizebytes(c->c_methods, size,
                                                   size + (int)sizeof(t_methodentry),
                                                   "EAPd/t_methodentry");
    if (!p)
        return ok;
    c->c_methods = p;
    t_methodentry* m = p + c->c_nmethod;
    c->c_nmethod++;
    m->me_name = name;
    m->me_fun = fn;
    for (int i = 0; i <= MAXPDARG; i++)
        m->me_arg[i] = types[i];
    return true;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a47fb0
namespace EA { namespace Audio { namespace Eapd {
void class_setpropertiesfn(t_class* c, void* fn)
{
    if (c)
        c->c_propertiesfn = fn;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a47fc0
namespace EA { namespace Audio { namespace Eapd {
void class_sethelpsymbol(t_class* c, t_symbol helpname)
{
    t_symbol tmp;
    char buf[1001];

    buf[1000] = 0;
    strncpy(buf, helpname.mpName, 1000);
    strncat(buf, "-help", 1000);
    t_symbol* sp = gensym(&tmp, buf);
    c->c_helpname = *sp;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48030
namespace EA { namespace Audio { namespace Eapd {
void class_setsavefn(t_class* c, void* fn)
{
    if (c)
        c->c_savefn = fn;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48040
namespace EA { namespace Audio { namespace Eapd {
void class_setdrawfunction(t_class* c, void* fn)
{
    if (c)
        c->c_drawfunction = fn;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a480b0
namespace EA { namespace Audio { namespace Eapd {
bool sys_close()
{
    if (pd_objectmaker && gpCanvasMaker) {
        sys_vgui_sym((uint32_t)(uintptr_t)&gpCanvasMaker, gObjectSym.mHash,
                     (uint32_t)(uintptr_t)gObjectSym.mpName);
        gpCanvasMaker = 0;
        pd_objectmaker = 0;
        return true;
    }
    return false;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48100
namespace EA { namespace Audio { namespace Eapd {
void pd_typedmess(t_pd* x, t_symbol s, int argc, t_atom* argv)
{
    t_class* c = *x;

    if (s == s_float) {
        if (!argc)
            c->c_floatmethod(x, 0.0f);
        else if (argv->a_type == A_FLOAT)
            c->c_floatmethod(x, argv->a_w.w_float);
        return;
    }
    if (s == s_bang) {
        c->c_bangmethod(x);
        return;
    }
    if (s == s_list) {
        c->c_listmethod(x, s, argc, argv);
        return;
    }
    if (s == s_symbol) {
        if (argc && argv->a_type == A_SYMBOL)
            c->c_symbolmethod(x, argv->a_w.w_symbol);
        else
            c->c_symbolmethod(x, s_);
        return;
    }

    int i;
    t_methodentry* m;
    for (i = c->c_nmethod, m = c->c_methods + i - 1; i--; m--) {
        if (m->me_name == s) {
            const int* wp = m->me_arg;
            if (*wp == A_GIMME) {
                if (x == &pd_objectmaker)
                    pd_newest = ((t_newgimme)m->me_fun)(s, argc, argv);
                else
                    ((t_messgimme)m->me_fun)(x, s, argc, argv);
                return;
            }
            float ad[MAXPDARG + 1];
            t_symbol sa[MAXPDARG + 1];
            float* dp = ad;
            t_symbol* ap = sa;
            int narg = 0;
            int wanttype;
            if (argc > MAXPDARG)
                argc = MAXPDARG;
            while ((wanttype = *wp++) != 0) {
                switch (wanttype) {
                case A_FLOAT:
                    if (!argc)
                        return;
                case A_DEFFLOAT:
                    if (!argc)
                        *dp = 0;
                    else {
                        if (argv->a_type != A_FLOAT)
                            return;
                        *dp = argv->a_w.w_float;
                        argc--;
                        argv++;
                    }
                    dp++;
                    break;
                case A_SYMBOL:
                    if (!argc)
                        return;
                case A_DEFSYM:
                    if (!argc)
                        *ap = s_;
                    else {
                        if (argv->a_type == A_SYMBOL)
                            *ap = argv->a_w.w_symbol;
                        else if (x == &pd_objectmaker && argv->a_type == A_FLOAT && argv->a_w.w_float == 0)
                            *ap = s_;
                        else
                            return;
                        argc--;
                        argv++;
                    }
                    narg++;
                    ap++;
                    break;
                }
            }
            if (x == &pd_objectmaker) {
                switch (narg) {
                case 0: pd_newest = ((t_new0)m->me_fun)(ad[0], ad[1], ad[2], ad[3], ad[4]); break;
                case 1: pd_newest = ((t_new1)m->me_fun)(sa[0], ad[0], ad[1], ad[2], ad[3], ad[4]); break;
                case 2: pd_newest = ((t_new2)m->me_fun)(sa[0], sa[1], ad[0], ad[1], ad[2], ad[3], ad[4]); break;
                case 3: pd_newest = ((t_new3)m->me_fun)(sa[0], sa[1], sa[2], ad[0], ad[1], ad[2], ad[3], ad[4]); break;
                case 4: pd_newest = ((t_new4)m->me_fun)(sa[0], sa[1], sa[2], sa[3], ad[0], ad[1], ad[2], ad[3], ad[4]); break;
                case 5: pd_newest = ((t_new5)m->me_fun)(sa[0], sa[1], sa[2], sa[3], sa[4], ad[0], ad[1], ad[2], ad[3], ad[4]); break;
                default: pd_newest = 0; break;
                }
            } else {
                switch (narg) {
                case 0: ((t_fun0)m->me_fun)(x, ad[0], ad[1], ad[2], ad[3], ad[4]); break;
                case 1: ((t_fun1)m->me_fun)(x, sa[0], ad[0], ad[1], ad[2], ad[3], ad[4]); break;
                case 2: ((t_fun2)m->me_fun)(x, sa[0], sa[1], ad[0], ad[1], ad[2], ad[3], ad[4]); break;
                case 3: ((t_fun3)m->me_fun)(x, sa[0], sa[1], sa[2], ad[0], ad[1], ad[2], ad[3], ad[4]); break;
                case 4: ((t_fun4)m->me_fun)(x, sa[0], sa[1], sa[2], sa[3], ad[0], ad[1], ad[2], ad[3], ad[4]); break;
                case 5: ((t_fun5)m->me_fun)(x, sa[0], sa[1], sa[2], sa[3], sa[4], ad[0], ad[1], ad[2], ad[3], ad[4]); break;
                }
            }
            return;
        }
    }
    c->c_anymethod(x, s, argc, argv);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a487f0
namespace EA { namespace Audio { namespace Eapd {
void pd_vmess(t_pd* x, t_symbol s, const char* fmt, ...)
{
    t_atom atoms[MAXPDARG];      /* the original walks one atom past this buffer */
    t_atom* argv = atoms;
    va_list ap;
    int n = 0;

    va_start(ap, fmt);
    for (;;) {
        int c = *fmt++;
        if (c == 'f') {
            argv->a_w.w_float = (float)va_arg(ap, double);
            argv->a_type = A_FLOAT;
        }
        else if (c == 'i') {
            argv->a_w.w_float = (float)va_arg(ap, int);
            argv->a_type = A_FLOAT;
        }
        else if (c == 's') {
            argv->a_w.w_symbol = va_arg(ap, t_symbol);
            argv->a_type = A_SYMBOL;
        }
        else
            break;
        n++;
        argv++;
        if (n > MAXPDARG)
            break;
    }
    va_end(ap);
    pd_typedmess(x, s, n, atoms);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48890
namespace EA { namespace Audio { namespace Eapd {
void* class_getmethod(t_pd* x, t_symbol s)
{
    t_class* c = *x;
    int n = c->c_nmethod;
    t_methodentry* m = c->c_methods + n - 1;

    while (n) {
        n--;
        if (m->me_name == s)
            return m->me_fun;
        m--;
    }
    return (void*)sys_gui;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a488d0
namespace EA { namespace Audio { namespace Eapd {
void* zgetfn(t_class_s00a4_88d0** pp, void* name)
{
    t_class_s00a4_88d0* c = *pp;
    int n = c->c_nmethod;
    char* e = (char*)c->c_methods + n * 0x24 - 0x24;
    while (n != 0) {
        --n;
        if (*(void**)e == name)
            return *(void**)(e + 8);
        e -= 0x24;
    }
    return 0;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48910
namespace EA { namespace Audio { namespace Eapd {
void class_addfloat(void* x, float f)
{
    t_class_s00a4_88d0* c = *(t_class_s00a4_88d0**)x;
    t_atom_s00a4_88d0 atoms[1];
    atoms[0].a_type = 1;
    atoms[0].a_w = f;
    if (c->c_listmethod != (void*)0x00a47d70) {
        typedef void (*ListFn)(void*, void*, void*, int, void*);
        ((ListFn)c->c_listmethod)(x, gListSym2.s_name, gListSym2.s_thing, 1, atoms);
    } else {
        typedef void (*SymFn)(void*, void*, void*, int, void*);
        ((SymFn)c->c_symbolmethod)(x, gFloatSymbol.s_name, gFloatSymbol.s_thing, 1, atoms);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48980
namespace EA { namespace Audio { namespace Eapd {
bool class_addcreator(void* fn, void* sel, void* a3, void* a4)
{
    t_class_s00a4_88d0* c = gpObjectMaker;
    char ok = 0;
    if (c) {
        if (sel == gBangName) {
            ok = 0;
            if (!fn)
                return ok;
            c->c_bangmethod = fn;
            return 1;
        }
        if (sel == gFloatName) {
            ok = 0;
            if (!fn)
                return ok;
            c->c_floatmethod = fn;
            return 1;
        }
        if (sel == gSymbolName) {
            ok = 0;
            if (!fn)
                return ok;
            c->c_symbolmethod = fn;
            return 1;
        }
        if (sel == gListName)
            return class_addlist(c, fn);
        if (sel == gAnythingName)
            return class_addanything(c, fn);
        return class_addmethod(c, fn, sel, a3, (int*)a4);
    }
    return ok != 0;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48a30
namespace EA { namespace Audio { namespace Eapd {
bool class_addmethod0(t_class_s00a4_88d0* c, void* fn, t_symbol_s00a4_88d0 sel, void* t0)
{
    int atoms[7];
    atoms[6] = 0;
    atoms[1] = 0; atoms[2] = 0; atoms[3] = 0; atoms[4] = 0; atoms[5] = 0;
    atoms[0] = (int)(uintptr_t)t0;
    return class_addmethod(c, fn, sel.s_name, sel.s_thing, atoms);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48a80
namespace EA { namespace Audio { namespace Eapd {
bool class_addmethod1(t_class_s00a4_88d0* c, void* fn, t_symbol_s00a4_88d0 sel, void* t0, void* t1)
{
    int atoms[7];
    atoms[6] = 1;
    atoms[2] = 0; atoms[3] = 0; atoms[4] = 0; atoms[5] = 0;
    atoms[0] = (int)(uintptr_t)t0;
    atoms[1] = (int)(uintptr_t)t1;
    return class_addmethod(c, fn, sel.s_name, sel.s_thing, atoms);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48ad0
namespace EA { namespace Audio { namespace Eapd {
bool class_addmethod2(t_class_s00a4_88d0* c, void* fn, t_symbol_s00a4_88d0 sel, void* t0, void* t1, void* t2)
{
    int atoms[7];
    atoms[6] = 2;
    atoms[3] = 0; atoms[4] = 0; atoms[5] = 0;
    atoms[0] = (int)(uintptr_t)t0;
    atoms[1] = (int)(uintptr_t)t1;
    atoms[2] = (int)(uintptr_t)t2;
    return class_addmethod(c, fn, sel.s_name, sel.s_thing, atoms);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48b30
namespace EA { namespace Audio { namespace Eapd {
bool class_addmethod4(t_class_s00a4_88d0* c, void* fn, t_symbol_s00a4_88d0 sel, void* t0, void* t1, void* t2, void* t3, void* t4)
{
    int atoms[7];
    atoms[0] = (int)(uintptr_t)t0;
    atoms[1] = (int)(uintptr_t)t1;
    atoms[2] = (int)(uintptr_t)t2;
    atoms[3] = (int)(uintptr_t)t3;
    atoms[4] = (int)(uintptr_t)t4;
    atoms[6] = 4;
    atoms[5] = 0;
    return class_addmethod(c, fn, sel.s_name, sel.s_thing, atoms);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48b90
namespace EA { namespace Audio { namespace Eapd {
bool class_addmethod5(t_class_s00a4_88d0* c, void* fn, t_symbol_s00a4_88d0 sel, void* t0, void* t1, void* t2, void* t3, void* t4, void* t5)
{
    int atoms[7];
    atoms[0] = (int)(uintptr_t)t0;
    atoms[1] = (int)(uintptr_t)t1;
    atoms[2] = (int)(uintptr_t)t2;
    atoms[3] = (int)(uintptr_t)t3;
    atoms[4] = (int)(uintptr_t)t4;
    atoms[5] = (int)(uintptr_t)t5;
    atoms[6] = 5;
    return class_addmethod(c, fn, sel.s_name, sel.s_thing, atoms);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48bf0
namespace EA { namespace Audio { namespace Eapd {
t_class_s00a4_88d0* class_new(t_symbol_s00a4_88d0 name, void* newmethod, void* freemethod, int size, int flags, t_atom_s00a4_88d0* atoms)
{
    int type = flags & 3;
    if (type == 0)
        type = 3;
    if (newmethod) {
        class_addcreator(newmethod, name.s_name, name.s_thing, atoms);
        if (gListSymbol.s_name != gAnythingSym.s_name) {
            const char* p = (const char*)name.s_name;
            char n = (char)strlen(p);
            const char* q = (const char*)gAnythingThing;   // 0x16753f0
            char m = (char)strlen(q);
            if (m > n) {
                if (strcmp(p, q + (m - n)) == 0)
                    class_addcreator(name.s_name, *(void**)&gListSymbol.s_name, freemethod, atoms);
            }
        }
    }
    t_class_s00a4_88d0* c = (t_class_s00a4_88d0*)getbytes(0x50, "[class]");
    if (c != 0) {
        c->c_name = name.s_name;
        c->c_helpname = name.s_thing;
        class_addpointer(c, name.s_name, name.s_thing);
        c->c_size = (unsigned)size;
        c->c_methods = (void*)getbytes(0, "[methods]");
        c->c_nmethod = 0;
        c->c_freemethod = freemethod;
        c->c_bangmethod = (void*)0x00a47cb0;
        c->c_floatmethod = (void*)0x00a48910;
        c->c_symbolmethod = (void*)0x00a47d00;
        c->c_listmethod = (void*)0x00a47d70;
        c->c_anymethod = (void*)0x00c2e4e0;
        c->c_wb = (type != 3) ? (void*)0x01554364 : 0;
        c->c_gobj = (char)(type >= 2);
        c->c_firstin = (char)(~((unsigned)size >> 3) & 1);
        c->c_patchable = (char)(type == 3);
        {
            t_symbol_s00a4_88d0* sel = &gListSymbol;
            if (sel->s_name == gAnythingSym.s_name)
                sel = &gListSym3;      // 0x1675400
            c->c_filetypes = sel->s_name;
            c->c_filedefault = sel->s_thing;
        }
        c->c_savefn = (type == 3) ? (void*)0x00a50e00 : (void*)0x00c2e4e0;
        c->c_next = gclasslist;
        gclasslist = c;
    }
    return c;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48db0
namespace EA { namespace Audio { namespace Eapd {
bool class_addcreator_m(void* a0, void* a1, void* a2, void* a3, void* a4)
{
    int locals[7];
    locals[6] = 0;
    locals[1] = 0; locals[2] = 0; locals[3] = 0; locals[4] = 0; locals[5] = 0;
    locals[0] = (int)(uintptr_t)a3;
    return class_addcreator(a0, a1, a2, locals);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48e00
namespace EA { namespace Audio { namespace Eapd {
bool class_addcreator_m2(void* a0, void* a1, void* a2, void* a3, void* a4)
{
    int locals[7];
    locals[2] = 0; locals[3] = 0; locals[4] = 0; locals[5] = 0;
    locals[0] = (int)(uintptr_t)a3;
    locals[1] = (int)(uintptr_t)a4;
    locals[6] = 1;
    return class_addcreator(a0, a1, a2, locals);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48e50
namespace EA { namespace Audio { namespace Eapd {
t_class_s00a4_88d0* class_new_m1(t_symbol_s00a4_88d0 name, void* newmethod, void* freemethod, int size, int flags, void* t0)
{
    int atoms[7];
    atoms[6] = 0;
    atoms[1] = 0; atoms[2] = 0; atoms[3] = 0; atoms[4] = 0; atoms[5] = 0;
    atoms[0] = (int)(uintptr_t)t0;
    return class_new(name, newmethod, freemethod, size, flags, (t_atom_s00a4_88d0*)atoms);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48ea0
namespace EA { namespace Audio { namespace Eapd {
t_class_s00a4_88d0* class_new_m2(t_symbol_s00a4_88d0 name, void* newmethod, void* freemethod, int size, int flags, void* t0, void* t1)
{
    int atoms[7];
    atoms[2] = 0; atoms[3] = 0; atoms[4] = 0; atoms[5] = 0;
    atoms[0] = (int)(uintptr_t)t0;
    atoms[1] = (int)(uintptr_t)t1;
    atoms[6] = 1;
    return class_new(name, newmethod, freemethod, size, flags, (t_atom_s00a4_88d0*)atoms);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48f00
namespace EA { namespace Audio { namespace Eapd {
t_class_s00a4_88d0* class_new_m3(t_symbol_s00a4_88d0 name, void* newmethod, void* freemethod, int size, int flags, void* t0, void* t1, void* t2)
{
    int atoms[7];
    atoms[3] = 0; atoms[4] = 0; atoms[5] = 0;
    atoms[0] = (int)(uintptr_t)t0;
    atoms[1] = (int)(uintptr_t)t1;
    atoms[2] = (int)(uintptr_t)t2;
    atoms[6] = 2;
    return class_new(name, newmethod, freemethod, size, flags, (t_atom_s00a4_88d0*)atoms);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a48f60
namespace EA { namespace Audio { namespace Eapd {
bool mess_init()
{
    gListSymbol.s_name = gAnythingSym.s_name;
    gListSymbol.s_thing = gAnythingSym.s_thing;
    gListSymB.s_name = gAnythingSym.s_name;
    gListSymB.s_thing = gAnythingSym.s_thing;
    gListSym3.s_name = gAnythingSym.s_name;
    gListSym3.s_thing = gAnythingSym.s_thing;
    t_symbol_s00a4_88d0 tmp;
    t_symbol_s00a4_88d0* s1 = (t_symbol_s00a4_88d0*)gensym(&tmp, "list");
    int atoms[7];
    atoms[0] = 0; atoms[1] = 0; atoms[2] = 0; atoms[3] = 0;
    atoms[4] = 0; atoms[5] = 0; atoms[6] = 0;
    t_class_s00a4_88d0* c1 = class_new(*s1, 0, 0, 4, 0, (t_atom_s00a4_88d0*)atoms);
    gpObjectMaker = c1;
    char ok = (char)(c1 != 0);
    t_symbol_s00a4_88d0 tmp2;
    t_symbol_s00a4_88d0* s2 = (t_symbol_s00a4_88d0*)gensym(&tmp2, "object");
    atoms[0] = 0; atoms[1] = 0; atoms[2] = 0; atoms[3] = 0;
    atoms[4] = 0; atoms[5] = 0; atoms[6] = 0;
    t_class_s00a4_88d0* c2 = class_new(*s2, 0, 0, 4, 0, (t_atom_s00a4_88d0*)atoms);
    gpTemplateMaker = c2;
    ok &= (char)(c2 != 0);
    sys_gui_release(&gpTemplateMaker, gObjectSym_s00a4_88d0.s_name, gObjectSym_s00a4_88d0.s_thing);
    char al = 0;
    if (gpObjectMaker != 0 && (void*)0x00a48050 != 0) {
        gpObjectMaker->c_anymethod = (void*)0x00a48050;
        al = 1;
    }
    ok &= al;
    return ok != 0;
}
}}}  // namespace EA::Audio::Eapd
