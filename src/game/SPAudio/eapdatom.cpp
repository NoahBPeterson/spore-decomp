// src/game/SPAudio/eapdatom.cpp
//
// Eapd's atom accessors: pull a float, an int or a symbol out of a t_atom.

#include "game/types.h"

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
};
extern Sym2 gFloatSymbol;   // 0x16758c4 ("float")
extern Sym2 gEmptySymbol;   // 0x167589c

extern "C" int  __cdecl hk_snprintf(char* buf, unsigned int n, const char* fmt, ...);   // 0x0107f390 (equiv t2)
extern "C" void __cdecl gensym(Sym2* out, const char* name);                            // 0x00a675f0 (equiv t2)

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
Sym2* atom_getsymbol(Sym2* out, Atom* in)
{
    if (in->type == 2) {
        out->a = in->v[0];
        out->b = in->v[1];
    } else {
        out->a = gFloatSymbol.a;
        out->b = gFloatSymbol.b;
    }
    return out;
}

// @ 0x00a467c0
Sym2* atom_gensym(Sym2* out, Atom* in)
{
    char buf[32];
    if (in->type == 2) {
        out->a = in->v[0];
        out->b = in->v[1];
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
        out->a = gEmptySymbol.a;
        out->b = gEmptySymbol.b;
        return out;
    }
    if (arr[i].type == 2) {
        out->a = arr[i].v[0];
        out->b = arr[i].v[1];
        return out;
    }
    out->a = gEmptySymbol.a;
    out->b = gEmptySymbol.b;
    return out;
}
