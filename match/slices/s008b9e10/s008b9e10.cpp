// T2K / tsi font engine, slice s008b9e10 (0x008b9e10-0x008ba7c0).
// Type 1 font-object construction/destruction plus the byte-level readers of the T2K/CFF
// input stream (1/2/3/4-byte big-endian offset readers, the packed-real reader and the
// CFF operand decoder).
//
// The stream object (the T1Class' input source) keeps the current buffer at +0, a refill
// callback at +4, its argument at +8, a one-byte landing pad at +0xc and, further in, the
// primed window size at +0x214, the window base at +0x218, the cursor at +0x21c, the error
// context at +0x22c and a "raw mode" flag at +0x238.
//
// Most of these are translation-unit-local statics whose parameters the compiler assigned to
// registers interprocedurally (ReadOfffset1-4 and READ_REAL take the stream in esi/edi,
// READ_INTEGER takes the stream in esi and its operator tag in eax).  Their callers live in
// other slices of the same object, so those functions are behaviour-complete here, not
// byte-exact (see nonmatching.txt).
#include "types.h"
typedef uint8_t uint8; typedef int16_t int16; typedef uint16_t uint16;
typedef uint32_t uint32; typedef int32_t int32;

struct tsiMemObject;

// ---- callees (addresses in comments) ------------------------------------------------------------
extern "C" void* tsi_AllocMem(tsiMemObject*, uint32);                  // 0x008d1260
extern "C" void  tsi_DeAllocMem(tsiMemObject*, void*);                 // 0x008d1440
extern "C" void* GetEntireStreamIntoMemory(void*);                     // 0x008cc2c0
extern "C" int   TransformData(void*, void*, int, int);                // 0x008b6f00 (this in edi, buf in ebx, size in eax, which on stack)
extern "C" void  BuildCMAP(void*);                                     // 0x008b8f30 (object in eax)
extern "C" void  BuildSubrs(void*);                                    // 0x008b8cc0 (object in esi)
extern "C" void  BuildMetricsEtc(void*);                               // 0x008b8890 (object in eax)
extern "C" char* tsi_T1Find(void*, const char*, int, int);             // 0x008b6e90
extern "C" int16 ATOI(const uint8*);                                   // 0x008b6a20 (string in ecx)
extern "C" int   ATOFixed(const uint8*, int);                          // 0x008b6a70 (string in eax)
extern "C" void  Delete_GlyphClass(void*);                             // 0x008b0280
extern "C" void  Delete_hashClass(void*);                              // 0x008d1cb0
extern "C" void  PrimeT2KInputStream(void*);                           // 0x008cc0b0
extern "C" void  tsi_Error(void*, int);                                // 0x008d10c0

// ---- object layouts -----------------------------------------------------------------------------

// A byte-producing input stream (T2K/CFF font source).
struct TsiStream {
    uint8*  ptr;                 // 0x000 current window (0 => pull through fn)
    int   (*fn)(int, uint8*, int, int);  // 0x004 refill callback (arg, dst, pos, n)
    int     arg;                 // 0x008 callback argument
    uint8   byte;                // 0x00c one-byte landing pad
    char    pad00d[0x214 - 0x00d];
    uint32  size;                // 0x214 primed window size
    int     primeBase;           // 0x218 window base
    int     curpos;              // 0x21c read cursor
    char    pad220[0x22c - 0x220];
    tsiMemObject* errctx;        // 0x22c error/memory context
    char    pad230[0x238 - 0x230];
    uint8   flag;                // 0x238 raw-mode flag
};

// Type 1 font class (0x224 bytes).  base/len/off/limit describe the in-memory font buffer;
// codes (+0x34) and adobeCodes (+0x38) are per-glyph 16-bit code tables; charStrings (+0x3c)
// is the per-glyph charstring pointer table.
struct T1Class {
    tsiMemObject* mem;           // 0x00
    int32   f04;                 // 0x04
    int32   base;                // 0x08
    int32   len;                 // 0x0c
    int32   off;                 // 0x10
    int32   limit;               // 0x14
    char    pad18[0x28 - 0x18];
    int16   charBase;            // 0x28
    char    pad2a[0x34 - 0x2a];
    int16*  codes;               // 0x34
    int16*  adobeCodes;          // 0x38
    void**  charStrings;         // 0x3c
    char    pad40[0x44 - 0x40];
    void**  subrs;               // 0x44
    char    pad48[0x1cc - 0x48];
    void*   glyph;               // 0x1cc
    char    pad1d0[0x21c - 0x1d0];
    void*   hashClass;           // 0x21c
};

// ---- shared byte reader (the original inlines this into every reader) ---------------------------

static uint8 ts_readByte(TsiStream* s)
{
    if (s->ptr == 0) {
        int pos = s->curpos;
        s->curpos = pos + 1;
        if (s->fn(s->arg, &s->byte, pos, 1) < 0) {
            tsi_Error(s->errctx, 0x2728);
            return 0;
        }
        return s->byte;
    }
    if (s->fn == 0)
        return s->ptr[s->curpos++];
    if ((uint32)(s->curpos - s->primeBase + 1) > s->size)
        PrimeT2KInputStream(s);
    return s->ptr[s->curpos++ - s->primeBase];
}

// ---- functions ----------------------------------------------------------------------------------

// @ 0x008b9e10
extern "C" T1Class* tsi_NewT1Class(tsiMemObject* mem, TsiStream* stream, int size)
{
    T1Class* t = (T1Class*)tsi_AllocMem(mem, 0x224);
    t->mem = mem;
    t->glyph = 0;
    t->base = 0;
    t->len = 0;

    void* buf = GetEntireStreamIntoMemory(stream);
    if (stream->flag == 0) {
        if (TransformData(t, buf, size, 0x14) != 0) {
            tsi_DeAllocMem(mem, t);
            return 0;
        }
        // exactly one of ptr/fn non-zero means the source is already decoded in place
        if (stream->ptr == 0) {
            if (stream->fn == 0)
                goto init;
        } else if (stream->fn != 0) {
            goto init;
        }
        stream->flag = 1;
    } else {
        t->f04 = (int)buf;
        t->base = (int)buf;
        t->len = size;
        t->off = (int)(tsi_T1Find(t, "ntfile eexec", 0, size) - (char*)buf);
    }

init:
    t->codes = 0;
    t->adobeCodes = 0;
    t->charStrings = 0;
    t->subrs = 0;
    t->limit = t->len;
    t->off = 0;                       // (also discards the offset found above)

    BuildCMAP(t);
    BuildSubrs(t);

    int16 lenIV = 4;
    char* p = tsi_T1Find(t, "/lenIV ", 0, t->limit);
    if (p != 0)
        lenIV = ATOI((const uint8*)p);
    t->charBase = lenIV;

    BuildMetricsEtc(t);
    return t;
}

// @ 0x008b9f20
extern "C" void tsi_DeleteT1Class(T1Class* t)
{
    if (t != 0) {
        Delete_GlyphClass(t->glyph);
        if (t->base != t->f04)
            tsi_DeAllocMem(t->mem, (void*)t->base);
        tsi_DeAllocMem(t->mem, t->codes);
        tsi_DeAllocMem(t->mem, t->adobeCodes);
        tsi_DeAllocMem(t->mem, t->charStrings);
        tsi_DeAllocMem(t->mem, t->subrs);
        Delete_hashClass(t->hashClass);
        tsi_DeAllocMem(t->mem, t);
    }
}

// @ 0x008b9fa0
extern "C" uint8 ReadOfffset1(TsiStream* s)
{
    return ts_readByte(s);
}

// @ 0x008ba050
extern "C" int16 ReadOfffset2(TsiStream* s)
{
    uint8 hi = ts_readByte(s);
    uint8 lo = ts_readByte(s);
    return (int16)((hi << 8) | lo);
}

// @ 0x008ba1c0
extern "C" uint32 ReadOfffset3(TsiStream* s)
{
    uint32 v = ts_readByte(s);
    v = (v << 8) | ts_readByte(s);
    v = (v << 8) | ts_readByte(s);
    return v;
}

// @ 0x008ba3d0
extern "C" int32 ReadOfffset4(TsiStream* s)
{
    uint32 v = ts_readByte(s);
    v = (v << 8) | ts_readByte(s);
    v = (v << 8) | ts_readByte(s);
    v = (v << 8) | ts_readByte(s);
    return (int32)v;
}

// @ 0x008ba680  (stream in edi)
extern "C" int READ_REAL(TsiStream* s)
{
    uint8 nib[4];
    char  out[68];
    int   n = 0;

    for (;;) {
        uint8 b = ts_readByte(s);
        nib[1] = b & 0xf;
        nib[0] = b >> 4;
        for (int k = 0; k < 2; ++k) {
            switch (nib[k]) {
            case 10: out[n] = '.';  break;               // nibble 0xa: decimal point
            case 11: out[n] = 'E';  break;               // nibble 0xb: exponent
            case 12: out[n] = 'E';  out[++n] = '-'; break; // 0xc: negative exponent
            case 14: out[n] = '-';  break;               // 0xe: minus sign
            case 13: continue;                           // 0xd: no character
            case 15:                                     // 0xf: end of number
                out[n] = 0;
                return ATOFixed((const uint8*)out, 0);
            default:
                out[n] = (char)(nib[k] + 0x30);
                break;
            }
            ++n;
        }
    }
}

// @ 0x008ba7c0  (stream in esi, operator tag in eax)
extern "C" uint32 READ_INTEGER(TsiStream* s, int tag)
{
    uint32 v = 0;

    if (tag == 0x1c) {                     // shortint: 2 bytes
        v = ts_readByte(s);
    } else if (tag == 0x1d) {              // longint: 4 bytes
        v = ts_readByte(s);
        v = (v << 8) | ts_readByte(s);
        v = (v << 8) | ts_readByte(s);
    } else if (tag <= 0xf6) {              // single-byte integer, bias 0x8b
        return (uint32)(tag - 0x8b);
    } else if (tag <= 0xfa) {              // positive 2-byte, bias 0xf694
        return (uint32)(tag * 0x100 - 0xf694 + ts_readByte(s));
    } else if (tag <= 0xfe) {              // negative 2-byte
        return (uint32)(0xfa94 - tag * 0x100 - ts_readByte(s));
    } else {                               // 0xff: reserved
        return 0;
    }
    return (v << 8) | ts_readByte(s);
}
