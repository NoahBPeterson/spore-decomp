// Slice s0090b310: expat 2.0.1 xmlrole.c prolog/content-model state handlers.
// Handlers are PROLOG_HANDLER(state, tok, ptr, end, enc); here state is p (handler at
// +0x00, includeLevel at +0x04, role_none at +0x08, documentEntity at +0x10) and the
// ENCODING *enc is parser (nameMatchesAscii at +0x1c, minBytesPerChar at +0x44).
// The inlined tail common(): if (!state->documentEntity && tok == XML_TOK_PARAM_ENTITY_REF)
// return XML_ROLE_INNER_PARAM_ENTITY_REF; state->handler = error; return XML_ROLE_ERROR;
// flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// The 8 struct-decl attribute-type keywords scanned by attlist2 (0x0154dc1c).
extern const wchar_t* const g_CDATA_kw[8];      // 0x0154dc1c
extern const wchar_t  kStr_CDATA[];             // "CDATA"
extern const wchar_t  kStr_IMPLIED[];           // "IMPLIED"
extern const wchar_t  kStr_REQUIRED[];          // "REQUIRED"
extern const wchar_t  kStr_FIXED[];             // "FIXED"
extern const wchar_t  kStr_INCLUDE[];           // "INCLUDE"
extern const wchar_t  kStr_IGNORE[];            // "IGNORE"
extern const wchar_t  kStr_SYSTEM[];            // "SYSTEM"
extern const wchar_t  kStr_PUBLIC[];            // "PUBLIC"
extern const wchar_t  kStr_PCDATA[];            // "PCDATA"
extern const wchar_t  kStr_NOTATION[];          // "NOTATION"
extern const wchar_t  kStr_EMPTY[];             // "EMPTY"
extern const wchar_t  kStr_ANY[];               // "ANY"
extern const wchar_t  kStr_NDATA[];             // "NDATA"

// Addresses of out-of-slice handlers / mid-function labels referenced only by value.
extern void __cdecl S_90b0a0();                 // 0x0090b0a0  attlist9
extern void __cdecl S_90b160();                 // 0x0090b160  declClose
extern void __cdecl S_90b1c0();                 // 0x0090b1c0  entity6
extern void __cdecl S_90b210();                 // 0x0090b210  entity9
extern void __cdecl S_90b250();                 // 0x0090b250  notation3
extern void __cdecl S_90b6a0();                 // 0x0090b6a0  entity8
extern void __cdecl S_90b6e0();                 // 0x0090b6e0  notation4
extern void __cdecl S_90b400();                 // 0x0090b400  element5
extern void __cdecl S_90bb20();                 // 0x0090bb20  attlist6
extern void __cdecl S_90bc10();                 // 0x0090bc10  entity1
extern void __cdecl S_90be40();                 // 0x0090be40  entity2
extern void __cdecl S_90c240();                 // 0x0090c240  internalSubset
extern void __cdecl S_90c3d0();                 // 0x0090c3d0  externalSubset1
extern void __cdecl S_90e31100();               // 0x00e31100  error (IWinProc::GetPriority)

// In-slice handlers referenced before their definition.
int __cdecl attlist8(int*, int, int, void*, int*);      // 0x0090b310
int __cdecl element7(int*, int);                        // 0x0090b460
int __cdecl entity5(int*, int, void*, void*, int*);     // 0x0090b610
int __cdecl attlist4(int*, int);                        // 0x0090b720
int __cdecl attlist7(int*, int);                        // 0x0090b780
int __cdecl element4(int*, int);                        // 0x0090b7e0
int __cdecl element6(int*, int);                        // 0x0090b830
int __cdecl entity7(int*, int, void*, void*, int*);     // 0x0090b940
int __cdecl notation1(int*, int, void*, void*, int*);   // 0x0090ba00
int __cdecl attlist3(int*, int);                        // 0x0090baa0
int __cdecl element3(int*, int);                        // 0x0090bb60
int __cdecl notation0(int*, int);                       // 0x0090bc90
int __cdecl attlist5(int*, int);                        // 0x0090bce0
int __cdecl element2(int*, int, int, void*, int*);      // 0x0090bd20
int __cdecl attlist2(int*, int, void*, void*, int*);    // 0x0090bf00
int __cdecl element1(int*, int, void*, void*, int*);    // 0x0090bfd0
int __cdecl attlist1(int*, int);                        // 0x0090c100
int __cdecl entity0(int*, int);                         // 0x0090c0a0
int __cdecl attlist0(int*, int);                        // 0x0090c1f0

#define PARSER_ERR   ((void*)&S_90e31100)
#define ROLLBACK(p)  (((int*)(p))[4] == 0)

// The upstream FASTCALL common(state, tok), inlined into every handler. Written as a real
// static function (and inlined by /O2) because for two handlers that is what reproduces the
// original's register choice (tok in ecx); the byte-identical inline form is used elsewhere.
static int __cdecl common(int* p, int tok)
{
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090b310
int __cdecl attlist8(int* p, int tok, int off, void* arg4, int* parser)
{
    switch (tok) {
    case 0xf:
        return 0x21;
    case 0x14:
        if (((int (__cdecl*)(int*, int, void*, const wchar_t*))parser[7])
                (parser, parser[0x11] + off, arg4, kStr_IMPLIED) != 0) {
            *p = (int)&attlist1;
            return 0x23;
        }
        if (((int (__cdecl*)(int*, int, void*, const wchar_t*))parser[7])
                (parser, parser[0x11] + off, arg4, kStr_REQUIRED) != 0) {
            *p = (int)&attlist1;
            return 0x24;
        }
        if (((int (__cdecl*)(int*, int, void*, const wchar_t*))parser[7])
                (parser, parser[0x11] + off, arg4, kStr_FIXED) != 0) {
            *p = (int)&S_90b0a0;
            return 0x21;
        }
        break;
    case 0x1b:
        *p = (int)&attlist1;
        return tok + 0xa;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090b460
int __cdecl element7(int* p, int tok)
{
    switch (tok) {
    case 0xf:
        return 0x27;
    case 0x18:
        p[1] -= 1;
        if (p[1] == 0) {
            *p = (int)&S_90b160;
            p[2] = 0x27;
        }
        return 0x2d;
    case 0x24:
        p[1] -= 1;
        if (p[1] == 0) {
            *p = (int)&S_90b160;
            p[2] = 0x27;
        }
        return 0x2e;
    case 0x23:
        p[1] -= 1;
        if (p[1] == 0) {
            *p = (int)&S_90b160;
            p[2] = 0x27;
        }
        return 0x2f;
    case 0x25:
        p[1] -= 1;
        if (p[1] == 0) {
            *p = (int)&S_90b160;
            p[2] = 0x27;
        }
        return 0x30;
    case 0x26:
        *p = (int)&element6;
        return 0x32;
    case 0x15:
        *p = (int)&element6;
        return 0x31;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090b610
int __cdecl entity5(int* p, int tok, void* arg3, void* arg4, int* parser)
{
    switch (tok) {
    case 0xf:
        return 0xb;
    case 0x11: {
        int v = (int)&S_90c240;
        if (ROLLBACK(p))
            v = (int)&S_90c3d0;
        *p = v;
        return 0xf;
    }
    case 0x12:
        if (((int (__cdecl*)(int*, void*, void*, const wchar_t*))parser[7])
                (parser, arg3, arg4, kStr_NDATA) != 0) {
            *p = (int)&S_90b1c0;
            return 0xb;
        }
        break;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090b720
int __cdecl attlist4(int* p, int tok)
{
    switch (tok) {
    case 0xf:
        return 0x21;
    case 0x15:
        *p = (int)&attlist3;
        return 0x21;
    case 0x18:
        *p = (int)&attlist8;
        return 0x21;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090b780
int __cdecl attlist7(int* p, int tok)
{
    switch (tok) {
    case 0xf:
        return 0x21;
    case 0x15:
        *p = (int)&S_90bb20;
        return 0x21;
    case 0x18:
        *p = (int)&attlist8;
        return 0x21;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090b7e0
int __cdecl element4(int* p, int tok)
{
    switch (tok) {
    case 0xf:
        return 0x27;
    case 0x12:
    case 0x29:
        *p = (int)&S_90b400;
        return 0x33;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090b830
int __cdecl element6(int* p, int tok)
{
    switch (tok) {
    case 0xf:
        return 0x27;
    case 0x17:
        p[1] += 1;
        return 0x2c;
    case 0x12:
    case 0x29:
        *p = (int)&element7;
        return 0x33;
    case 0x1e:
        *p = (int)&element7;
        return 0x35;
    case 0x1f:
        *p = (int)&element7;
        return 0x34;
    case 0x20:
        *p = (int)&element7;
        return 0x36;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090b940
int __cdecl entity7(int* p, int tok, void* arg3, void* arg4, int* parser)
{
    switch (tok) {
    case 0xf:
        return 0xb;
    case 0x12:
        if (((int (__cdecl*)(int*, void*, void*, const wchar_t*))parser[7])
                (parser, arg3, arg4, kStr_SYSTEM) != 0) {
            *p = (int)&S_90b210;
            return 0xb;
        }
        if (((int (__cdecl*)(int*, void*, void*, const wchar_t*))parser[7])
                (parser, arg3, arg4, kStr_PUBLIC) != 0) {
            *p = (int)&S_90b6a0;
            return 0xb;
        }
        break;
    case 0x1b:
        *p = (int)&S_90b160;
        p[2] = 0xb;
        return tok - 0xf;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090ba00
int __cdecl notation1(int* p, int tok, void* arg3, void* arg4, int* parser)
{
    switch (tok) {
    case 0xf:
        return 0x11;
    case 0x12:
        if (((int (__cdecl*)(int*, void*, void*, const wchar_t*))parser[7])
                (parser, arg3, arg4, kStr_SYSTEM) != 0) {
            *p = (int)&S_90b250;
            return tok - 1;
        }
        if (((int (__cdecl*)(int*, void*, void*, const wchar_t*))parser[7])
                (parser, arg3, arg4, kStr_PUBLIC) != 0) {
            *p = (int)&S_90b6e0;
            return 0x11;
        }
        break;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090baa0
int __cdecl attlist3(int* p, int tok)
{
    switch (tok) {
    case 0xf:
        return 0x21;
    case 0x12:
    case 0x13:
    case 0x29:
        *p = (int)&attlist4;
        return 0x1f;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090bb60
int __cdecl element3(int* p, int tok)
{
    switch (tok) {
    case 0xf:
        return 0x27;
    case 0x18:
        *p = (int)&S_90b160;
        p[2] = 0x27;
        return 0x2d;
    case 0x24:
        *p = (int)&S_90b160;
        p[2] = 0x27;
        return 0x2e;
    case 0x15:
        *p = (int)&element4;
        return 0x27;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090bc90
int __cdecl notation0(int* p, int tok)
{
    switch (tok) {
    case 0xf:
        return 0x11;
    case 0x12:
        *p = (int)&notation1;
        return 0x12;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090bce0
int __cdecl attlist5(int* p, int tok)
{
    switch (tok) {
    case 0xf:
        return 0x21;
    case 0x17:
        *p = (int)&S_90bb20;
        return 0x21;
    }
    return common(p, tok);
}

// ===========================================================================
// @ 0x0090bd20
int __cdecl element2(int* p, int tok, int off, void* arg4, int* parser)
{
    switch (tok) {
    case 0xf:
        return 0x27;
    case 0x14:
        if (((int (__cdecl*)(int*, int, void*, const wchar_t*))parser[7])
                (parser, parser[0x11] + off, arg4, kStr_PCDATA) != 0) {
            *p = (int)&element3;
            return 0x2b;
        }
        break;
    case 0x17:
        p[1] = 2;
        *p = (int)&element6;
        return 0x2c;
    case 0x12:
    case 0x29:
        *p = (int)&element7;
        return 0x33;
    case 0x1e:
        *p = (int)&element7;
        return 0x35;
    case 0x1f:
        *p = (int)&element7;
        return 0x34;
    case 0x20:
        *p = (int)&element7;
        return 0x36;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090bf00
int __cdecl attlist2(int* p, int tok, void* arg3, void* arg4, int* parser)
{
    switch (tok) {
    case 0xf:
        return 0x21;
    case 0x12: {
        int i;
        for (i = 0; i < 8; ++i) {
            if (((int (__cdecl*)(int*, void*, void*, const wchar_t*))parser[7])
                    (parser, arg3, arg4, g_CDATA_kw[i]) != 0) {
                *p = (int)&attlist8;
                return i + 0x17;
            }
        }
        if (((int (__cdecl*)(int*, void*, void*, const wchar_t*))parser[7])
                (parser, arg3, arg4, kStr_NOTATION) != 0) {
            *p = (int)&attlist5;
            return 0x21;
        }
        break;
    }
    case 0x17:
        *p = (int)&attlist3;
        return 0x21;
    }
    return common(p, tok);
}

// ===========================================================================
// @ 0x0090bfd0
int __cdecl element1(int* p, int tok, void* arg3, void* arg4, int* parser)
{
    switch (tok) {
    case 0xf:
        return 0x27;
    case 0x12:
        if (((int (__cdecl*)(int*, void*, void*, const wchar_t*))parser[7])
                (parser, arg3, arg4, kStr_EMPTY) != 0) {
            *p = (int)&S_90b160;
            p[2] = 0x27;
            return 0x2a;
        }
        if (((int (__cdecl*)(int*, void*, void*, const wchar_t*))parser[7])
                (parser, arg3, arg4, kStr_ANY) != 0) {
            *p = (int)&S_90b160;
            p[2] = 0x27;
            return 0x29;
        }
        break;
    case 0x17:
        *p = (int)&element2;
        p[1] = 1;
        return tok + 0x15;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090c100
int __cdecl attlist1(int* p, int tok)
{
    switch (tok) {
    case 0xf:
        return 0x21;
    case 0x11:
        *p = p[4] ? (int)&S_90c240 : (int)&S_90c3d0;
        return 0x21;
    case 0x12:
    case 0x29:
        *p = (int)&attlist2;
        return 0x16;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090c0a0
int __cdecl entity0(int* p, int tok)
{
    switch (tok) {
    case 0xf:
        return 0xb;
    case 0x12:
        *p = (int)&S_90be40;
        return 9;
    case 0x16:
        *p = (int)&S_90bc10;
        return 0xb;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}

// ===========================================================================
// @ 0x0090c1f0
int __cdecl attlist0(int* p, int tok)
{
    switch (tok) {
    case 0xf:
        return 0x21;
    case 0x12:
    case 0x29:
        *p = (int)&attlist1;
        return 0x22;
    }
    if (ROLLBACK(p) && tok == 0x1c)
        return 0x3b;
    *p = (int)PARSER_ERR;
    return -1;
}
