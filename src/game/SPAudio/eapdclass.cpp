// src/game/SPAudio/eapdclass.cpp -- migrated from slice(s) s00a478b0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdclass.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

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
        t_symbol w_symbol;
    } a_w;
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
enum { A_NULL = 0, A_FLOAT = 1, A_SYMBOL = 2, A_POINTER = 3, A_SEMI = 4, A_DEFFLOAT = 5, A_DEFSYM = 6, A_GIMME = 9 };
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
    char pad00[0x1c];
    t_methodentry* c_methods;                                   // +0x1c
    int            c_nmethod;                                   // +0x20
    char pad24[4];
    void (*c_bangmethod)(t_pd* x);                              // +0x28
    void (*c_floatmethod)(t_pd* x, float f);                    // +0x2c
    void (*c_symbolmethod)(t_pd* x, t_symbol s);                // +0x30
    void (*c_listmethod)(t_pd* x, t_symbol s, int argc, t_atom* argv);   // +0x34
    void (*c_anymethod)(t_pd* x, t_symbol s, int argc, t_atom* argv);    // +0x38
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
// ---- items of slice s00a478b0 end

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
