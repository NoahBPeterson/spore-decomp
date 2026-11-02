// src/game/SPAudio/eapdbinbuf.cpp -- migrated from slice(s) s00a478b0, s00a469b0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdbinbuf.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// ---- items of slice s00a469b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol {
    uint32_t    mHash;   // +0
    const char* mpName;  // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom {          // 12 bytes
    int32_t a_type;
    union {
        float    w_float;
        int32_t  w_index;
        t_symbol w_symbol;
    } a_w;
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_binbuf {
    int32_t b_n;      // +0 atoms used
    t_atom* b_vec;    // +4 atoms
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol* gensym(t_symbol* out, const char* name);            // 0x00a675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* getbytes(int n, const char* tag);                       // 0x00a49610
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  freebytes(void* p, int n);                              // 0x00a49650
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* resizebytes(void* p, int oldsize, int newsize, const char* tag);   // 0x00a49670
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   canvas_getdollarzero();                                 // 0x00a4a4b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   binbuf_realizedollsym(t_symbol s, int ac, const t_atom* av, int max,
                            t_symbol* out);                   // 0x00a477a0
}
}
}
// ---- items of slice s00a469b0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace EA { namespace Audio { namespace Eapd { void atom_string(const t_atom* a, char* buf, int bufsize); }}}  // 0x00a469b0 (stays in the slice: not this object's)
namespace EA { namespace Audio { namespace Eapd { void binbuf_vectortext(int argc, const t_atom* argv, char* buf, int bufsize); }}}  // 0x00a46bc0 (stays in the slice: not this object's)

// ---- items of slice s00a478b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct t_atom_s00a4_78b0 {           // 12 bytes
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
    void (*c_listmethod)(t_pd* x, t_symbol s, int argc, t_atom_s00a4_78b0* argv);   // +0x34
    void (*c_anymethod)(t_pd* x, t_symbol s, int argc, t_atom_s00a4_78b0* argv);    // +0x38
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
extern t_symbol s_list;        // 0x16758ac
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
struct t_binbuf_s00a4_78b0 {
    int32_t b_n;      // +0 atoms in use
    t_atom_s00a4_78b0* b_vec;    // +4 atoms
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  binbuf_text(t_binbuf_s00a4_78b0* b, const char* text, int sz);                 // 0x00a46cb0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   binbuf_realizedollsym(t_symbol s, int ac, const t_atom_s00a4_78b0* av, int forobjectmaker,
                            t_symbol* out);                               // 0x00a477a0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol* atom_getsymbol(t_symbol* out, t_atom_s00a4_78b0* a);                       // 0x00a46790
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_pd* EapdBindRemove(t_symbol s);                                         // 0x00a671d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* canvas_getcurrent();                                                // 0x00a4a430
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  outlet_float(t_pd* x, float f);                                     // 0x00a49570
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_list(t_pd* x, t_symbol s, int argc, t_atom_s00a4_78b0* argv);               // 0x00a495b0
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
extern t_atom_s00a4_78b0*  gEvalBuf;      // 0x1554260  cursor into the shared binbuf_eval output buffer
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_atom_s00a4_78b0*  gEvalBufEnd;   // 0x155425c  end of that buffer
}
}
}
// ---- items of slice s00a478b0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace EA { namespace Audio { namespace Eapd { void pd_typedmess(t_pd* x, t_symbol s, int argc, t_atom_s00a4_78b0* argv); }}}  // 0x00a48100 (stays in the slice: not this object's)

// @ 0x00a46c20
namespace EA { namespace Audio { namespace Eapd {
t_binbuf* binbuf_new()
{
    t_binbuf* b = (t_binbuf*)getbytes(8, "EAPd/t_binbuf");

    b->b_n = 0;
    b->b_vec = (t_atom*)getbytes(0, "EAPd/t_binbuf_atoms");
    return b;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a46c50
namespace EA { namespace Audio { namespace Eapd {
void binbuf_free(t_binbuf* b)
{
    freebytes(b->b_vec, b->b_n * (int)sizeof(t_atom));
    freebytes(b, 8);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a46c80
namespace EA { namespace Audio { namespace Eapd {
void binbuf_clear(t_binbuf* b)
{
    b->b_vec = (t_atom*)resizebytes(b->b_vec, b->b_n * (int)sizeof(t_atom), 0,
                                    "EAPd/t_binbuf_atoms");
    b->b_n = 0;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a46cb0
namespace EA { namespace Audio { namespace Eapd {
void binbuf_text(t_binbuf* b, const char* text, int sz)
{
    const char* textp = text;
    const char* textend = text + sz;
    t_atom* ap;
    int nalloc = 16;
    int natom = 0;
    char buf[1000];
    char* bufp;
    int quoted;
    int slash;

    freebytes(b->b_vec, b->b_n * (int)sizeof(t_atom));
    ap = b->b_vec = (t_atom*)getbytes(nalloc * (int)sizeof(t_atom), "EAPd/t_binbuf_atoms");
    b->b_n = 0;
    for (;;) {
        while (textp != textend) {
            char c = *textp;
            if (c != ' ' && c != '\n' && c != '\r' && c != '\t')
                break;
            textp++;
        }
        if (textp == textend)
            break;
        if (*textp == ';') {
            ap->a_type = 3;
            ap->a_w.w_index = 0;
            textp++;
        }
        else if (*textp == ',') {
            ap->a_type = 4;
            ap->a_w.w_index = 0;
            textp++;
        }
        else {
            int type = 0;
            char c;

            bufp = buf;
            quoted = (*textp == '\\');
            do {
                c = *textp++;
                *bufp = c;
                slash = (c == '\\');
                if (type >= 0) {
                    int digit = (c >= '0' && c <= '9');
                    int dot = (c == '.');
                    int sign = (c == '-' || c == '+');
                    int expo = (c == 'e' || c == 'E');

                    if (type == 0) {
                        if (c == '-')
                            type = 1;
                        else if (digit)
                            type = 2;
                        else
                            type = dot ? 3 : -1;
                    }
                    else if (type == 1) {
                        if (digit)
                            type = 2;
                        else
                            type = dot ? 3 : -1;
                    }
                    else if (type == 2) {
                        if (dot)
                            type = 4;
                        else if (expo)
                            type = 6;
                        else if (!digit)
                            type = -1;
                    }
                    else if (type == 3) {
                        type = digit ? 5 : -1;
                    }
                    else if (type == 4) {
                        if (digit)
                            type = 5;
                        else
                            type = expo ? -1 : 6;
                    }
                    else if (type == 5) {
                        if (expo)
                            type = 6;
                        else if (!digit)
                            type = -1;
                    }
                    else if (type == 6) {
                        if (sign)
                            type = 7;
                        else
                            type = digit ? 8 : -1;
                    }
                    else if (type == 7) {
                        type = digit ? 8 : -1;
                    }
                    else if (type == 8) {
                        if (!digit)
                            type = -1;
                    }
                }
                if (!slash)
                    bufp++;
            } while (textp != textend && bufp != buf + 1000 &&
                     (slash || ((c = *textp) != ' ' && c != '\n' && c != '\r' &&
                                c != '\t' && c != ',' && c != ';')));
            *bufp = 0;
            if (buf[0] == '$' && buf[1] >= '0' && buf[1] <= '9' && !quoted) {
                const char* p = buf + 2;
                while (*p && *p >= '0' && *p <= '9')
                    p++;
                if (*p) {
                    t_symbol tmp;
                    t_symbol* sp;
                    ap->a_type = 8;
                    sp = gensym(&tmp, buf + 1);
                    ap->a_w.w_symbol.mHash = sp->mHash;
                    ap->a_w.w_symbol.mpName = sp->mpName;
                }
                else {
                    ap->a_type = 7;
                    ap->a_w.w_index = atoi(buf + 1);
                }
            }
            else if (type == 2 || type == 4 || type == 5 || type == 8) {
                ap->a_type = 1;
                ap->a_w.w_float = (float)atof(buf);
            }
            else {
                t_symbol tmp;
                t_symbol* sp;
                ap->a_type = 2;
                sp = gensym(&tmp, buf);
                ap->a_w.w_symbol.mHash = sp->mHash;
                ap->a_w.w_symbol.mpName = sp->mpName;
            }
        }
        ap++;
        natom++;
        if (natom == nalloc) {
            t_atom* newvec = (t_atom*)resizebytes(b->b_vec, nalloc * (int)sizeof(t_atom),
                                                  nalloc * 2 * (int)sizeof(t_atom),
                                                  "EAPd/t_binbuf_atoms");
            b->b_vec = newvec;
            nalloc *= 2;
            ap = (t_atom*)((char*)newvec + natom * (int)sizeof(t_atom));
        }
        if (textp == textend)
            break;
    }
    b->b_vec = (t_atom*)resizebytes(b->b_vec, nalloc * (int)sizeof(t_atom),
                                    natom * (int)sizeof(t_atom), "EAPd/t_binbuf_atoms");
    b->b_n = natom;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a47080
namespace EA { namespace Audio { namespace Eapd {
void binbuf_gettext(t_binbuf* b, char** bufp, int* lengthp)
{
    char* buf = (char*)getbytes(0, "EAPd/char");
    const t_atom* ap = b->b_vec;
    int n = b->b_n;
    int len = 0;
    char text[1000];

    if (n != 0) {
        do {
            int len2;
            char* newbuf;
            n--;
            if ((ap->a_type == 3 || ap->a_type == 4) && len != 0 && buf[len - 1] == ' ')
                len--;
            atom_string(ap, text, 1000);
            len2 = (int)strlen(text);
            newbuf = (char*)resizebytes(buf, len, len + len2 + 1, "EAPd/char");
            if (!newbuf)
                break;
            strcpy(newbuf + len, text);
            newbuf[len + len2] = (ap->a_type == 3) ? ' ' : '\n';
            buf = newbuf;
            ap++;
            len = len + len2 + 1;
        } while (n != 0);
        if (len != 0 && buf[len - 1] == ' ') {
            char* newbuf = (char*)resizebytes(buf, len, len - 1, "EAPd/char");
            if (newbuf) {
                buf = newbuf;
                len--;
            }
        }
    }
    *bufp = buf;
    *lengthp = len;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a471a0
namespace EA { namespace Audio { namespace Eapd {
void binbuf_add(t_binbuf* b, int argc, const t_atom* argv)
{
    int n = b->b_n + argc;
    t_atom* vec = (t_atom*)resizebytes(b->b_vec, b->b_n * (int)sizeof(t_atom),
                                       n * (int)sizeof(t_atom), "EAPd/t_binbuf_atoms");
    if (vec) {
        t_atom* ap;
        int i;

        b->b_vec = vec;
        ap = (t_atom*)((char*)vec + b->b_n * (int)sizeof(t_atom));
        for (i = argc; i != 0; --i) {
            *ap = *argv;
            argv++;
            ap++;
        }
        b->b_n = n;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a47220
namespace EA { namespace Audio { namespace Eapd {
void binbuf_addv(t_binbuf* b, const char* fmt, ...)
{
    t_atom av[100];
    int n = 0;
    va_list ap;

    va_start(ap, fmt);
    for (;;) {
        char c;
        if (n >= 100)
            break;
        c = *fmt++;
        switch (c) {
        case ',':
            av[n].a_type = 4;
            av[n].a_w.w_index = 0;
            break;
        case ';':
            av[n].a_type = 3;
            av[n].a_w.w_index = 0;
            break;
        case 'f':
            av[n].a_type = 1;
            av[n].a_w.w_float = (float)va_arg(ap, double);
            break;
        case 'i':
            av[n].a_type = 1;
            av[n].a_w.w_float = (float)va_arg(ap, int);
            break;
        case 's':
            av[n].a_type = 2;
            av[n].a_w.w_symbol = va_arg(ap, t_symbol);
            break;
        default:
            goto done;
        }
        n++;
    }
done:
    binbuf_add(b, n, av);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a47350
namespace EA { namespace Audio { namespace Eapd {
void binbuf_addbinbuf(t_binbuf* b, const t_binbuf* b2)
{
    t_binbuf* b3 = binbuf_new();
    t_atom* ap;
    char buf[1000];
    int i;

    binbuf_add(b3, b2->b_n, b2->b_vec);
    for (i = 0, ap = b3->b_vec; i < b3->b_n; i++, ap++) {
        switch (ap->a_type) {
        case 2:      // A_SYMBOL
            {
                const char* s = ap->a_w.w_symbol.mpName;
                if (!strcmp(s, ";")) {
                    t_symbol tmp;
                    t_symbol* sp;
                    ap->a_type = 2;
                    sp = gensym(&tmp, ";");
                    ap->a_w.w_symbol.mHash = sp->mHash;
                    ap->a_w.w_symbol.mpName = sp->mpName;
                }
                else if (!strcmp(s, ",")) {
                    t_symbol tmp;
                    t_symbol* sp;
                    ap->a_type = 2;
                    sp = gensym(&tmp, ",");
                    ap->a_w.w_symbol.mHash = sp->mHash;
                    ap->a_w.w_symbol.mpName = sp->mpName;
                }
            }
            break;
        case 3:      // A_SEMI
            {
                t_symbol tmp;
                t_symbol* sp;
                ap->a_type = 2;
                sp = gensym(&tmp, ";");
                ap->a_w.w_symbol.mHash = sp->mHash;
                ap->a_w.w_symbol.mpName = sp->mpName;
            }
            break;
        case 4:      // A_COMMA
            {
                t_symbol tmp;
                t_symbol* sp;
                ap->a_type = 2;
                sp = gensym(&tmp, ",");
                ap->a_w.w_symbol.mHash = sp->mHash;
                ap->a_w.w_symbol.mpName = sp->mpName;
            }
            break;
        case 7:      // A_DOLLAR
            {
                t_symbol tmp;
                t_symbol* sp;
                sprintf(buf, "$%d", ap->a_w.w_index);
                ap->a_type = 2;
                sp = gensym(&tmp, buf);
                ap->a_w.w_symbol.mHash = sp->mHash;
                ap->a_w.w_symbol.mpName = sp->mpName;
            }
            break;
        case 8:      // A_DOLLSYM
            {
                t_symbol tmp;
                t_symbol* sp;
                sprintf(buf, "$%s", ap->a_w.w_symbol.mpName);
                ap->a_type = 2;
                sp = gensym(&tmp, buf);
                ap->a_w.w_symbol.mHash = sp->mHash;
                ap->a_w.w_symbol.mpName = sp->mpName;
            }
            break;
        }
    }
    binbuf_add(b, b3->b_n, b3->b_vec);
    binbuf_free(b3);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a47540
namespace EA { namespace Audio { namespace Eapd {
void binbuf_addsemi(t_binbuf* b)
{
    t_atom a;

    a.a_type = 3;
    a.a_w.w_index = 0;
    binbuf_add(b, 1, &a);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a47570
namespace EA { namespace Audio { namespace Eapd {
void binbuf_addtext(t_binbuf* b, int argc, const t_atom* av)
{
    int n = b->b_n + argc;
    t_atom* vec = (t_atom*)resizebytes(b->b_vec, b->b_n * (int)sizeof(t_atom),
                                       n * (int)sizeof(t_atom), "EAPd/t_binbuf_atoms");
    if (vec) {
        t_atom* ap = (t_atom*)((char*)vec + b->b_n * (int)sizeof(t_atom));
        b->b_vec = vec;
        while (argc != 0) {
            argc--;
            if (av->a_type == 2) {
                const char* s = av->a_w.w_symbol.mpName;
                if (!strcmp(s, ";")) {
                    ap->a_type = 3;
                    ap->a_w.w_index = 0;
                }
                else if (!strcmp(s, ",")) {
                    ap->a_type = 4;
                    ap->a_w.w_index = 0;
                }
                else if (s[0] == '$' && s[1] >= '0' && s[1] <= '9') {
                    const char* p = s + 2;
                    int nondigit = 0;
                    char c = *p;
                    if (c) {
                        do {
                            if (c < '0' || c > '9')
                                nondigit = 1;
                            c = p[1];
                            p++;
                        } while (c);
                    }
                    if (nondigit) {
                        t_symbol tmp;
                        t_symbol* sp;
                        ap->a_type = 8;
                        sp = gensym(&tmp, s + 1);
                        ap->a_w.w_symbol.mHash = sp->mHash;
                        ap->a_w.w_symbol.mpName = sp->mpName;
                    }
                    else {
                        int idx = 0;
                        sscanf(s + 1, "%d", &idx);
                        ap->a_type = 7;
                        ap->a_w.w_index = idx;
                    }
                }
                else
                    *ap = *av;
            }
            else
                *ap = *av;
            av++;
            ap++;
        }
        b->b_n = n;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a47780
namespace EA { namespace Audio { namespace Eapd {
void binbuf_gettextbuf(t_binbuf* b, char* buf, int bufsize)
{
    binbuf_vectortext(b->b_n, b->b_vec, buf, bufsize);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a477a0
namespace EA { namespace Audio { namespace Eapd {
int binbuf_realizedollsym(t_symbol s, int ac, const t_atom* av, int max, t_symbol* out)
{
    char ok = 1;
    long n = atol(s.mpName);
    char buf[1000] = "";
    const char* p = s.mpName;

    if (p[0]) {
        char c = p[0];
        do {
            if (c < '0' || c > '9')
                break;
            if (c && n >= 0 && n <= ac) {
                if (n == 0)
                    sprintf(buf, "%d", canvas_getdollarzero());
                else
                    atom_string(&av[n - 1], buf, 499);
            }
            else {
                if (max)
                    sprintf(buf, "$%d", (int)n);
                else
                    ok = 0;
            }
            c = p[1];
            p++;
        } while (c);
        if (!ok)
            return 0;
    }
    strncat(buf, p, 499);
    {
        t_symbol tmp;
        t_symbol* sp = gensym(&tmp, buf);
        out->mHash = sp->mHash;
        out->mpName = sp->mpName;
    }
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a478b0
namespace EA { namespace Audio { namespace Eapd {
void binbuf_eval(t_binbuf_s00a4_78b0* x, t_pd* target, int argc, t_atom_s00a4_78b0* argv)
{
    t_atom_s00a4_78b0* const savbuf = gEvalBuf;    /* start of the message being built */
    t_atom_s00a4_78b0* ap = x->b_vec;
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
            t_atom_s00a4_78b0* out = gEvalBuf;

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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a47c00
namespace EA { namespace Audio { namespace Eapd {
void* glob_evaltext(const char* text, int len)
{
    void* canvas = canvas_getcurrent();
    t_binbuf_s00a4_78b0* b = (t_binbuf_s00a4_78b0*)getbytes(8, "EAPd/t_binbuf");

    b->b_n = 0;
    b->b_vec = (t_atom_s00a4_78b0*)getbytes(0, "EAPd/t_binbuf_atoms");
    binbuf_text(b, text, len);
    binbuf_eval(b, 0, 0, 0);
    freebytes(b->b_vec, b->b_n * (int)sizeof(t_atom_s00a4_78b0));
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
}}}  // namespace EA::Audio::Eapd
