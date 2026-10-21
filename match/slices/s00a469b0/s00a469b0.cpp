// Slice s00a469b0: EA::Audio::Eapd (EA's embedded Pure Data) - binbuf.c atom/t_binbuf helpers.
// 0x00a469b0-0x00a478ab.  Object file SPAudio/eapdtext.obj (VS2008 SP1).
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

namespace EA { namespace Audio { namespace Eapd {

struct t_symbol {
    uint32_t    mHash;   // +0
    const char* mpName;  // +4
};

struct t_atom {          // 12 bytes
    int32_t a_type;
    union {
        float    w_float;
        int32_t  w_index;
        t_symbol w_symbol;
    } a_w;
};

struct t_binbuf {
    int32_t b_n;      // +0 atoms used
    t_atom* b_vec;    // +4 atoms
};

// callees (address in the comment)
t_symbol* gensym(t_symbol* out, const char* name);            // 0x00a675f0
void* getbytes(int n, const char* tag);                       // 0x00a49610
void  freebytes(void* p, int n);                              // 0x00a49650
void* resizebytes(void* p, int oldsize, int newsize, const char* tag);   // 0x00a49670
int   canvas_getdollarzero();                                 // 0x00a4a4b0
int   binbuf_realizedollsym(t_symbol s, int ac, const t_atom* av, int max,
                            t_symbol* out);                   // 0x00a477a0

// @ 0x00a469b0
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

// @ 0x00a46bc0
void binbuf_vectortext(int argc, const t_atom* argv, char* buf, int bufsize)
{
    char atomtext[80];
    int i;

    *buf = 0;
    atomtext[0] = ' ';
    for (i = 0; i < argc; i++) {
        atom_string(argv, atomtext + 1, 79);
        strncat(buf, atomtext + (i == 0), bufsize);
        argv++;
    }
}

// @ 0x00a46c20
t_binbuf* binbuf_new()
{
    t_binbuf* b = (t_binbuf*)getbytes(8, "EAPd/t_binbuf");

    b->b_n = 0;
    b->b_vec = (t_atom*)getbytes(0, "EAPd/t_binbuf_atoms");
    return b;
}

// @ 0x00a46c50
void binbuf_free(t_binbuf* b)
{
    freebytes(b->b_vec, b->b_n * (int)sizeof(t_atom));
    freebytes(b, 8);
}

// @ 0x00a46c80
void binbuf_clear(t_binbuf* b)
{
    b->b_vec = (t_atom*)resizebytes(b->b_vec, b->b_n * (int)sizeof(t_atom), 0,
                                    "EAPd/t_binbuf_atoms");
    b->b_n = 0;
}

// @ 0x00a46cb0
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

// @ 0x00a47080
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

// @ 0x00a471a0
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

// @ 0x00a47220
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

// @ 0x00a47350
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

// @ 0x00a47540
void binbuf_addsemi(t_binbuf* b)
{
    t_atom a;

    a.a_type = 3;
    a.a_w.w_index = 0;
    binbuf_add(b, 1, &a);
}

// @ 0x00a47570
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

// @ 0x00a47780
void binbuf_gettextbuf(t_binbuf* b, char* buf, int bufsize)
{
    binbuf_vectortext(b->b_n, b->b_vec, buf, bufsize);
}

// @ 0x00a477a0
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

}}}
