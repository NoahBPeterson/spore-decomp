// src/game/SPAudio/eapdatom.cpp
//
// Eapd's atom accessors: pull a float, an int or a symbol out of a t_atom.

#include "game/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// Atom kinds stored in t_atom::mType.
enum {
    kAtomFloat  = 1,
    kAtomSymbol = 2,
};

struct Atom {
    int   type;
    union {
        float f;
        const char* s;
        const char* v[2];
    };
};

// A symbol is a (hash, name) pair; 0x16758c4 is gFloatSymbol, 0x167589c gEmptySymbol.
struct Sym2 {
    const char* a;
    const char* b;
    Sym2() {}
    Sym2(const Sym2& o) { a = o.a; b = o.b; }
};
extern Sym2 gFloatSymbol;   // 0x16758c4 ("float")
extern Sym2 gEmptySymbol;   // 0x167589c

extern "C" int  __cdecl hk_snprintf(char* buf, unsigned int n, const char* fmt, ...);   // 0x0107f390 (equiv t2)
extern "C" void __cdecl gensym(Sym2* out, const char* name);                            // 0x00a675f0 (equiv t2)

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
// ---- items of slice s00a469b0 end

// @ 0x00a46760
inline float atom_getfloat(Atom* a)
{
    if (a->type == kAtomFloat)
        return a->f;
    return 0.0f;
}

// @ 0x00a46770
int atom_getint(Atom* a)
{
    return (int)atom_getfloat(a);
}

// @ 0x00a46790
Sym2 atom_getsymbol(Atom* in)
{
    if (in->type == 2)
        return *(Sym2*)in->v;
    return gFloatSymbol;
}

// @ 0x00a467c0
Sym2* atom_gensym(Sym2* out, Atom* in)
{
    char buf[32];
    if (in->type == 2) {
        Sym2 t(*(Sym2*)in->v);
        *out = t;
        return out;
    }
    if (in->type == 1)
        hk_snprintf(buf, 32, "%g", (double)in->f);
    else
        hk_snprintf(buf, 32, "???");
    gensym(out, buf);
    return out;
}

// @ 0x00a46830
Sym2* atom_vectorgensym(Sym2* out, int count, Atom* atoms)
{
    char buf[1000];
    int used = 0;
    int remain = 1000;
    int n = count;
    Atom* p = atoms;
    while (n > 0) {
        int w;
        if (p->type == 1)
            w = hk_snprintf(buf + used, remain, "%g ", (double)p->f);
        else if (p->type == 2)
            w = hk_snprintf(buf + used, remain, "%s ", p->s);
        else
            w = hk_snprintf(buf + used, remain, "??? ");
        if (w > 0) {
            used += w;
            remain -= w;
        }
        ++p;
        --n;
    }
    buf[used] = 0;
    gensym(out, buf);
    return out;
}

// @ 0x00a468f0
inline float atom_getfloat_at(int i, int n, Atom* arr)
{
    if (n > i && arr[i].type == kAtomFloat)
        return arr[i].f;
    return 0.0f;
}

// @ 0x00a46920
int atom_getint_at(int i, int n, Atom* arr)
{
    return (int)atom_getfloat_at(i, n, arr);
}

// @ 0x00a46950
Sym2* atom_getsymbol_at(Sym2* out, int i, int n, Atom* arr)
{
    if (n <= i) {
        Sym2 t(gEmptySymbol);
        *out = t;
    } else if (arr[i].type == 2) {
        Sym2 t(*(Sym2*)arr[i].v);
        *out = t;
    } else {
        Sym2 t(gEmptySymbol);
        *out = t;
    }
    return out;
}

// @ 0x00a469b0
namespace EA { namespace Audio { namespace Eapd {
void atom_string(const t_atom* a, char* buf, int bufsize)
{
    char tbuf[32];

    switch (a->a_type)
    {
    case 3:      // A_SEMI
        strcpy(buf, ";");
        return;
    case 4:      // A_COMMA
        strcpy(buf, ",");
        return;

    case 1:      // A_FLOAT
        sprintf(tbuf, "%g", (double)a->a_w.w_float);
        if ((unsigned int)strlen(tbuf) < (unsigned int)(bufsize - 1)) {
            strcpy(buf, tbuf);
            return;
        }
        if (a->a_w.w_float < 0.0f)
            strcpy(buf, "-");
        else
            strcat(buf, "+");
        return;

    case 2:      // A_SYMBOL
        {
            char* bufp = buf;
            const char* sourceptr = a->a_w.w_symbol.mpName;
            unsigned int count = 0;

            if (sourceptr[0]) {
                const char* p = sourceptr;
                int quote = 0;
                char c = *p;
                do {
                    if (c == ';' || c == ',' || c == '\\' ||
                        (c == '$' && p == sourceptr && p[1] >= '0' && p[1] <= '9'))
                        quote = 1;
                    c = p[1];
                    count++;
                    p++;
                } while (c);
                if (quote) {
                    const char* e = buf + bufsize - 2;
                    char c;
                    while (bufp < e) {
                        c = *sourceptr;
                        if (c == '\0')
                            break;
                        if (c == ';' || c == ',' || c == '\\' ||
                            (c == '$' && bufp == buf && sourceptr[1] >= '0' &&
                             sourceptr[1] <= '9'))
                            *bufp++ = '\\';
                        *bufp++ = c;
                        sourceptr++;
                    }
                    if (*sourceptr)
                        *bufp++ = '*';
                    *bufp = 0;
                    return;
                }
            }
            if (count < (unsigned int)(bufsize - 1)) {
                strcpy(buf, sourceptr);
                return;
            }
            strncpy(buf, sourceptr, bufsize - 2);
            buf[bufsize - 2] = '*';
            buf[bufsize - 1] = 0;
            return;
        }

    case 7:      // A_DOLLAR
        sprintf(buf, "$%d", a->a_w.w_index);
        return;
    case 8:      // A_DOLLSYM
        sprintf(buf, "$%s", a->a_w.w_symbol.mpName);
        return;
    }
}
}}}  // namespace EA::Audio::Eapd
