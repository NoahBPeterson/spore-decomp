// Slice s00a478b0: EA::Audio::Eapd::pd_typedmess (Pure Data m_class.c), 1776 bytes.
// The EA port passes t_symbol by value (hash, name); atoms are 12 bytes (type + 8-byte payload).
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <stdarg.h>
#include <string.h>

namespace EA { namespace Audio { namespace Eapd {

struct t_symbol {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};
// Symbols are compared by their first word only (the original loads one dword).
inline bool operator==(const t_symbol& a, const t_symbol& b) { return a.mHash == b.mHash; }

struct t_atom {           // 12 bytes
    int a_type;
    union {
        float    w_float;
        int      w_index;
        t_symbol w_symbol;
    } a_w;
};
// Atom tags (see binbuf_text): 3/4 are the ';' and ',' atoms, 7/8 the dollar arguments.
enum { A_NULL = 0, A_FLOAT = 1, A_SYMBOL = 2, A_SEMI = 3, A_COMMA = 4, A_DEFFLOAT = 5, A_DEFSYM = 6,
       A_DOLLAR = 7, A_DOLLSYM = 8, A_GIMME = 9 };
enum { MAXPDARG = 5 };

struct t_class;
typedef t_class* t_pd;

struct t_methodentry {     // 0x24 bytes
    t_symbol me_name;      // +0
    void*    me_fun;       // +8
    int      me_arg[MAXPDARG + 1];   // +0xc
};

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

extern t_symbol s_float;       // 0x16758c4
extern t_symbol s_bang;        // 0x16758b4
extern t_symbol s_list;        // 0x16758ac
extern t_symbol s_symbol;      // 0x1675894
extern t_symbol s_;            // 0x167589c (empty symbol)
extern t_pd pd_objectmaker;    // 0x16753e8
extern t_pd* pd_newest;        // 0x16753f4

typedef t_pd* (*t_newgimme)(t_symbol s, int argc, t_atom* argv);
typedef void (*t_messgimme)(t_pd* x, t_symbol s, int argc, t_atom* argv);

typedef t_pd* (*t_new0)(float, float, float, float, float);
typedef t_pd* (*t_new1)(t_symbol, float, float, float, float, float);
typedef t_pd* (*t_new2)(t_symbol, t_symbol, float, float, float, float, float);
typedef t_pd* (*t_new3)(t_symbol, t_symbol, t_symbol, float, float, float, float, float);
typedef t_pd* (*t_new4)(t_symbol, t_symbol, t_symbol, t_symbol, float, float, float, float, float);
typedef t_pd* (*t_new5)(t_symbol, t_symbol, t_symbol, t_symbol, t_symbol, float, float, float, float, float);

typedef void (*t_fun0)(t_pd*, float, float, float, float, float);
typedef void (*t_fun1)(t_pd*, t_symbol, float, float, float, float, float);
typedef void (*t_fun2)(t_pd*, t_symbol, t_symbol, float, float, float, float, float);
typedef void (*t_fun3)(t_pd*, t_symbol, t_symbol, t_symbol, float, float, float, float, float);
typedef void (*t_fun4)(t_pd*, t_symbol, t_symbol, t_symbol, t_symbol, float, float, float, float, float);
typedef void (*t_fun5)(t_pd*, t_symbol, t_symbol, t_symbol, t_symbol, t_symbol, float, float, float, float, float);

// @ 0xa48100
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


// ==================================================================================================
// Rest of the EAPd class / binbuf / message API (0x00a478b0-0x00a488d0).
// ==================================================================================================

struct t_binbuf {
    int32_t b_n;      // +0 atoms in use
    t_atom* b_vec;    // +4 atoms
};

// Callees that live outside this slice.
t_symbol* gensym(t_symbol* out, const char* name);                        // 0x00a675f0
void* getbytes(int n, const char* tag);                                   // 0x00a49610
void  freebytes(void* p, int n);                                          // 0x00a49650
void* resizebytes(void* p, int oldsize, int newsize, const char* tag);    // 0x00a49670
void  binbuf_text(t_binbuf* b, const char* text, int sz);                 // 0x00a46cb0
int   binbuf_realizedollsym(t_symbol s, int ac, const t_atom* av, int forobjectmaker,
                            t_symbol* out);                               // 0x00a477a0
t_symbol* atom_getsymbol(t_symbol* out, t_atom* a);                       // 0x00a46790
t_pd* EapdBindRemove(t_symbol s);                                         // 0x00a671d0
void* canvas_getcurrent();                                                // 0x00a4a430
int   canvas_getdollarzero();                                             // 0x00a4a4b0
void  outlet_float(t_pd* x, float f);                                     // 0x00a49570
void  pd_list(t_pd* x, t_symbol s, int argc, t_atom* argv);               // 0x00a495b0
void  obj_list(t_pd* x, t_symbol s, int argc, t_atom* argv);              // 0x00a49b40
void  sys_vgui_sym(uint32_t obj, uint32_t sel, uint32_t arg);             // 0x00a671b0
void  sys_gui(t_pd* x, t_symbol s, int argc, t_atom* argv);               // 0x00c2e4e0 (empty stub)
void  class_addfloat(t_pd* x, float f);                                   // 0x00a48910
void  pd_vmess(t_pd* x, t_symbol s, const char* fmt, ...);                // 0x00a487f0

// Globals owned by the message system.
extern t_atom*  gEvalBuf;      // 0x1554260  cursor into the shared binbuf_eval output buffer
extern t_atom*  gEvalBufEnd;   // 0x155425c  end of that buffer
extern t_class* gpCanvasMaker; // 0x1675408
extern t_class* gClassList;    // 0x167540c  class_add() list
extern t_symbol gObjectSym;    // 0x16758a4  "object"

// @ 0x00a478b0
void binbuf_eval(t_binbuf* x, t_pd* target, int argc, t_atom* argv)
{
    t_atom* const savbuf = gEvalBuf;    /* start of the message being built */
    t_atom* ap = x->b_vec;
    int n = x->b_n;
    t_symbol s;                         /* selector symbol */
    t_symbol ds;                        /* realized dollar symbol */
    t_symbol tmp;                       /* atom_getsymbol scratch */
    t_symbol gsemi;                     /* gensym scratch, ";" */
    t_symbol gcomma;                    /* gensym scratch, "," */

    for (;;)
    {
        if (target == 0)
        {
            /* between messages: skip the separators, then bind the selector */
            if (!n)
                break;
            while (ap->a_type == A_SEMI || ap->a_type == A_COMMA)
            {
                n--;
                ap++;
                if (!n)
                    return;
            }
            if (!n)
                break;
            if (ap->a_type == A_DOLLAR)
            {
                int i = ap->a_w.w_index;
                if (i <= 0 || i > argc || argv[i - 1].a_type != A_SYMBOL)
                    goto skipmessage;
                s = argv[i - 1].a_w.w_symbol;
            }
            else if (ap->a_type == A_DOLLSYM)
            {
                if (!binbuf_realizedollsym(ap->a_w.w_symbol, argc, argv, 0, &s))
                    goto skipmessage;
            }
            else
            {
                t_symbol* sp = atom_getsymbol(&tmp, ap);
                s = *sp;
            }
            target = EapdBindRemove(s);
            if (target == 0)
            {
            skipmessage:
                do {
                    n--;
                    ap++;
                } while (n != 0 && ap->a_type != A_SEMI);
            }
            else
            {
                n--;
                ap++;
            }
        }
        if (target == 0)
            continue;

        /* one message */
        {
            int nargs = 0;
            t_pd* rcv = target;
            t_atom* out = gEvalBuf;

            for (;;)
            {
                if (out >= gEvalBufEnd)
                    goto done;
                switch (ap->a_type)
                {
                case A_FLOAT:
                case A_SYMBOL:
                    *out = *ap;
                    break;
                case A_SEMI:
                    if (target != &pd_objectmaker)
                    {
                        rcv = 0;
                        goto dispatch;
                    }
                    out->a_type = A_SYMBOL;
                    out->a_w.w_symbol = *gensym(&gsemi, ";");
                    break;
                case A_COMMA:
                    if (target != &pd_objectmaker)
                        goto dispatch;
                    out->a_type = A_SYMBOL;
                    out->a_w.w_symbol = *gensym(&gcomma, ",");
                    break;
                case A_DOLLAR:
                    {
                        int i = ap->a_w.w_index;
                        if (i > 0 && i <= argc)
                            *out = argv[i - 1];
                        else
                        {
                            out->a_type = A_FLOAT;
                            if (i == 0)
                                out->a_w.w_float = (float)canvas_getdollarzero();
                            else
                                out->a_w.w_float = 0.0f;
                        }
                    }
                    break;
                case A_DOLLSYM:
                    if (!binbuf_realizedollsym(ap->a_w.w_symbol, argc, argv,
                                               target == &pd_objectmaker, &ds))
                        goto done;
                    out->a_type = A_SYMBOL;
                    out->a_w.w_symbol = ds;
                    break;
                default:
                    goto done;
                }
                out++;
                gEvalBuf = out;
                n--;
                nargs++;
                ap++;
                if (!n)
                    break;
            }
        dispatch:
            if (nargs != 0)
            {
                if (savbuf->a_type == A_FLOAT)
                {
                    if (nargs == 1)
                        outlet_float(target, savbuf->a_w.w_float);
                    else
                        pd_list(target, s_list, nargs, savbuf);
                }
                else if (savbuf->a_type == A_SYMBOL)
                    pd_typedmess(target, savbuf[1].a_w.w_symbol, nargs - 1, savbuf + 1);
            }
            gEvalBuf = savbuf;
            if (!n)
                break;
            target = rcv;
            n--;
            ap++;
        }
    }
done:
    gEvalBuf = savbuf;
}

// @ 0x00a47c00
void* glob_evaltext(const char* text, int len)
{
    void* canvas = canvas_getcurrent();
    t_binbuf* b = (t_binbuf*)getbytes(8, "EAPd/t_binbuf");

    b->b_n = 0;
    b->b_vec = (t_atom*)getbytes(0, "EAPd/t_binbuf_atoms");
    binbuf_text(b, text, len);
    binbuf_eval(b, 0, 0, 0);
    freebytes(b->b_vec, b->b_n * (int)sizeof(t_atom));
    freebytes(b, 8);

    void* newcanvas = canvas_getcurrent();
    if (newcanvas != canvas)
    {
        t_symbol tmp;
        t_symbol* sp = gensym(&tmp, "pop");
        pd_vmess((t_pd*)newcanvas, *sp, "i", canvas == 0);
    }
    return newcanvas;
}

// --------------------------------------------------------------------------------------------------
// Default methods: when a class has no handler, the message walks down to a generic one.
// --------------------------------------------------------------------------------------------------

void pd_defaultlist(t_pd* x, t_symbol s, int argc, t_atom* argv);   // 0x00a47d70

// @ 0x00a47cb0
void pd_defaultbang(t_pd* x)
{
    t_class* c = *x;

    if (c->c_listmethod != pd_defaultlist)
        c->c_listmethod(x, s_list, 0, 0);
    else
        c->c_anymethod(x, s_bang, 0, 0);
}

// @ 0x00a47d00
void pd_defaultsymbol(t_pd* x, t_symbol s)
{
    t_atom a;

    a.a_w.w_symbol = s;
    a.a_type = A_SYMBOL;
    if ((*x)->c_listmethod != pd_defaultlist)
        (*x)->c_listmethod(x, s_list, 1, &a);
    else
        (*x)->c_anymethod(x, s_symbol, 1, &a);
}

// @ 0x00a47d70
void pd_defaultlist(t_pd* x, t_symbol s, int argc, t_atom* argv)
{
    if (argc == 0) {
        if ((*x)->c_bangmethod != pd_defaultbang) {
            (*x)->c_bangmethod(x);
            return;
        }
    }
    else if (argc == 1) {
        if (argv->a_type == A_FLOAT && (*x)->c_floatmethod != class_addfloat) {
            (*x)->c_floatmethod(x, argv->a_w.w_float);
            return;
        }
        if (argv->a_type == A_SYMBOL && (*x)->c_symbolmethod != pd_defaultsymbol) {
            (*x)->c_symbolmethod(x, argv->a_w.w_symbol);
            return;
        }
    }
    if ((*x)->c_anymethod != sys_gui) {
        (*x)->c_anymethod(x, s_list, argc, argv);
        return;
    }
    if ((*x)->c_gobj)
        obj_list(x, s, argc, argv);
}

// @ 0x00a47e30
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

// @ 0x00a47e70
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

// @ 0x00a47fb0
void class_setpropertiesfn(t_class* c, void* fn)
{
    if (c)
        c->c_propertiesfn = fn;
}

// @ 0x00a47fc0
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

// @ 0x00a48030
void class_setsavefn(t_class* c, void* fn)
{
    if (c)
        c->c_savefn = fn;
}

// @ 0x00a48040  (the PDB names this block new_anything; the message constructor itself sits at
// 0x00a48050, right after this byte-exact field setter)
void class_setdrawfunction(t_class* c, void* fn)
{
    if (c)
        c->c_drawfunction = fn;
}

// @ 0x00a480b0
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

// @ 0x00a487f0
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

// @ 0x00a48890
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

}}}
