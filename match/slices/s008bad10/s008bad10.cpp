// T2K / tsi font engine, slice s008bad10 (0x008bad10-0x008bb0d0+).
// CFF (Compact Font Format) support: the index-structure reader, per-index data fetch, the T2
// name-property accessor and the two DICT parsers (Private DICT and Top DICT).
//
// The CFF index structure keeps its memory context at +0, the absolute data base at +4, the
// offset width at +8, the decoded offset array at +0xc and the entry count (int16) at +0x10.
// The Top DICT class holds the decoded operands (charset/encoding/charstrings offsets, the
// FontMatrix and FontBBox, and the Private DICT location).
//
// These are translation-unit-local statics whose parameters the compiler assigned to registers
// interprocedurally (the index class in esi, the CFF class in ecx, the stream in ebx, the index
// in eax, ...).  Their callers live in other slices of the same object, so they are
// behaviour-complete here, not byte-exact (see nonmatching.txt).
#include "types.h"
typedef uint8_t uint8; typedef int16_t int16; typedef uint16_t uint16;
typedef uint32_t uint32; typedef int32_t int32;

struct tsiMemObject;

// ---- callees (addresses in comments) ------------------------------------------------------------
extern "C" void* tsi_AllocMem(tsiMemObject*, uint32);                  // 0x008d1260
extern "C" int   util_FixMul(int, int);                                // 0x008d1590
extern "C" int16 ReadInt16(void*);                                     // 0x008cc190
extern "C" int   Tell_InputStream(void*);                              // 0x008cc5b0
extern "C" void  Seek_InputStream(void*, int);                         // 0x008cc580
extern "C" int   PeekInt16(void*, void*, int);                         // 0x008cc220
extern "C" void  PrimeT2KInputStream(void*);                           // 0x008cc0b0
extern "C" void  tsi_Error(void*, int);                                // 0x008d10c0
// offset readers, from slice s008b9e10 (stream in esi)
extern "C" uint8  ReadOfffset1(void*);                                 // 0x008b9fa0
extern "C" int16  ReadOfffset2(void*);                                 // 0x008ba050
extern "C" uint32 ReadOfffset3(void*);                                 // 0x008ba1c0
extern "C" int32  ReadOfffset4(void*);                                 // 0x008ba3d0
// operand readers, from slice s008b9e10 (stream in edi/esi, tag in eax)
extern "C" int    READ_REAL(void*);                                    // 0x008ba680
extern "C" uint32 READ_INTEGER(void*, int);                            // 0x008ba7c0

// ---- object layouts -----------------------------------------------------------------------------

// Byte-producing input stream (same layout as slice s008b9e10).
struct TsiStream {
    uint8*  ptr;                 // 0x000
    int   (*fn)(int, uint8*, int, int);  // 0x004
    int     arg;                 // 0x008
    uint8   byte;                // 0x00c
    char    pad00d[0x214 - 0x00d];
    uint32  size;                // 0x214
    int     primeBase;           // 0x218
    int     curpos;              // 0x21c
    char    pad220[0x22c - 0x220];
    tsiMemObject* errctx;        // 0x22c
};

// Decoded CFF INDEX.
struct CFFIndex {
    tsiMemObject* mem;           // 0x00
    int     f04;                 // 0x04 absolute data base
    uint8   offSize;             // 0x08 offset width
    char    pad09[0x0c - 0x09];
    int*    offsets;             // 0x0c decoded offsets (count+1 entries)
    int16   count;               // 0x10
};

// Decoded CFF Top DICT.
struct CFFTopDict {
    int16   f00, f02, f04, f06, f08;                    // 0x00
    int32   f0c;                                        // 0x0c
    int32   f10, f14, f18, f1c;                         // 0x10
    int32   f20, f24;                                   // 0x20
    int32   f28, f2c;                                   // 0x28
    uint8   f30;                                        // 0x30
    char    pad31[0x34 - 0x31];
    int32   f34, f38, f3c;                              // 0x34
    int32   f40, f44;                                   // 0x40
    int32   f48, f4c, f50, f54;                         // 0x48
    union {                                             // 0x58
        int32 copy[65];                                 //   operand copy (0x58..0x15c)
        struct { char _p[0x40]; int16 lo, hi; } v;      //   0x98/0x9a view of the copy
    } bbox;
    char    pad9c[0x15c - 0x9c];
    int32   f15c, f160, f164, f168;                     // 0x15c
    uint8   f16c;                                       // 0x16c
};

// CFF font class (the object GetT2NameProperty is called on).
struct CFFClass {
    char    pad00[4];
    TsiStream* stream;           // 0x004
    char    pad08[0x238 - 0x08];
    int     nameIndex;           // 0x238
    char    pad23c[0x374 - 0x23c];
    CFFIndex* nameIdx;           // 0x374
};

// ---- shared byte reader -------------------------------------------------------------------------

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

// @ 0x008bad10  (stream in esi)
extern "C" CFFIndex* tsi_NewCFFIndexClass(tsiMemObject* mem, TsiStream* s)
{
    CFFIndex* ix = (CFFIndex*)tsi_AllocMem(mem, 0x14);
    ix->mem = mem;
    ix->f04 = 0;

    int16 count = ReadInt16(s);
    ix->count = count;
    if (count != 0) {
        ix->offSize = ts_readByte(s);
        ix->offsets = (int*)tsi_AllocMem(mem, (uint32)(uint16)count * 4 + 4);

        uint32 (*read)(TsiStream*);
        if (ix->offSize == 1)
            read = (uint32 (*)(TsiStream*))ReadOfffset1;
        else if (ix->offSize == 2)
            read = (uint32 (*)(TsiStream*))ReadOfffset2;
        else if (ix->offSize == 3)
            read = (uint32 (*)(TsiStream*))ReadOfffset3;
        else
            read = (uint32 (*)(TsiStream*))ReadOfffset4;

        int i = 0;
        do {
            ix->offsets[i] = (int)read(s);
            ++i;
        } while (i <= (int)(uint16)count);

        int t = Tell_InputStream(s);
        ix->f04 = t - 1;
        Seek_InputStream(s, ix->offsets[(uint16)count] + (t - 1));
    }
    return ix;
}

// @ 0x008bae70  (index in eax, class in ecx, stream in ebx)
extern "C" int tsi_GetCFFData(int index, CFFIndex* ix, TsiStream* s)
{
    int buf = 0;
    if (index >= 0 && index < (int)(uint16)ix->count) {
        int pos = Tell_InputStream(s);
        Seek_InputStream(s, ix->offsets[index] + ix->f04);

        int len = ix->offsets[index + 1] - ix->offsets[index];
        int p = (int)tsi_AllocMem(ix->mem, (uint32)(len + 2));
        buf = p;
        PeekInt16(s, (void*)p, len);
        *(uint8*)(p + len) = 0;
        *(uint8*)(p + len + 1) = 0;
        Seek_InputStream(s, pos);
    }
    return buf;
}

// @ 0x008baee0
extern "C" int GetT2NameProperty(CFFClass* t, int unused, int16 kind)
{
    if (kind == 4 && t->nameIdx != 0)
        return tsi_GetCFFData(t->nameIndex, t->nameIdx, t->stream);
    return 0;
}

// @ 0x008baf10
extern "C" void tsi_ParsePrivateDictData(void* p)
{
    char*   base = (char*)p;
    TsiStream* s = *(TsiStream**)(base + 4);
    int st[64];
    int n = 0;

    int savepos = Tell_InputStream(s);
    *(int*)(base + 0x4fc) = 0;
    *(int*)(base + 0x500) = 0;
    *(int*)(base + 0x504) = 0;
    *(int*)(base + 0x508) = 0;

    Seek_InputStream(s, *(int*)(base + 0x3c0) + *(int*)(base + 8));
    int end = *(int*)(base + 0x3bc) + *(int*)(base + 0x3c0) + *(int*)(base + 8);

    while ((uint32)Tell_InputStream(s) < (uint32)end) {
        uint8 b = ts_readByte(s);
        if (b <= 0x1b || b == 0x1f) {
            if (b == 0x13)
                *(int*)(base + 0x4fc) = st[0];
            else if (b == 0x14)
                *(int*)(base + 0x504) = st[0];
            else if (b == 0x15)
                *(int*)(base + 0x508) = st[0];
            n = 0;
        } else if (b == 0x1e) {
            st[n++] = READ_REAL(s);
        } else {
            st[n++] = (int)READ_INTEGER(s, b);
        }
    }

    if (*(int*)(base + 0x4fc) != 0)
        *(int*)(base + 0x500) = *(int*)(base + 0x3c0) + *(int*)(base + 0x4fc) + *(int*)(base + 8);
    Seek_InputStream(s, savepos);
}

// @ 0x008bb0d0  (stream in ecx, index class on the stack, dict class on the stack, index in eax)
extern "C" void tsi_ParseCFFTopDict(TsiStream* s, CFFIndex* ix, CFFTopDict* d, int index)
{
    int st[64];
    int n = 0;

    int start = Tell_InputStream(s);

    d->f18 = 0; d->f10 = 0; d->f1c = 0; d->f14 = 0;
    d->f24 = 0;
    d->f160 = 0; d->f164 = 0;
    d->f34 = 0; d->f38 = 0; d->f40 = 0; d->f44 = 0;
    d->f48 = 0; d->f50 = 0; d->f54 = 0;
    d->f20 = 0;
    d->f16c = 0;
    d->f28 = -100;
    d->f2c = 50;
    d->f15c = 0x10000;
    d->f168 = 0x10000;
    d->f4c = 1;
    d->f30 = 2;

    Seek_InputStream(s, ix->offsets[index] + ix->f04);
    int end = ix->offsets[index + 1] + ix->f04;

    while ((uint32)Tell_InputStream(s) < (uint32)end) {
        uint8 b = ts_readByte(s);
        int   v0 = st[0];

        if (b <= 0x1b || b == 0x1f) {
            if (b == 0x0c) {
                uint8 op2 = ts_readByte(s);
                switch (op2) {
                case 1:  d->f20 = v0; break;
                case 2:  d->f24 = v0; break;
                case 3:  d->f28 = v0; break;
                case 4:  d->f2c = v0; break;
                case 6:  d->f30 = (uint8)v0; break;
                case 7:
                    d->f15c = util_FixMul(v0, 0x3e80000);
                    d->f164 = util_FixMul(st[1], 0x3e80000);
                    d->f160 = util_FixMul(st[2], 0x3e80000);
                    d->f168 = util_FixMul(st[3], 0x3e80000);
                    break;
                case 0x1c:
                    d->f48 = n - 4;
                    d->f4c = v0;
                    for (int k = 0; k < n - 4; ++k)
                        d->bbox.copy[k] = st[k + 1];
                    d->f50 = st[d->f48 + 1];
                    d->f54 = (int)tsi_AllocMem(ix->mem, (uint32)d->f50 * 4);
                    d->bbox.v.lo = (int16)st[d->f48 + 2];
                    d->bbox.v.hi = (int16)st[d->f48 + 3];
                    /* falls through into the FontMatrix case */
                    d->f15c = util_FixMul(v0, 0x3e80000);
                    d->f164 = util_FixMul(st[1], 0x3e80000);
                    d->f160 = util_FixMul(st[2], 0x3e80000);
                    d->f168 = util_FixMul(st[3], 0x3e80000);
                    break;
                case 0x1e:
                    d->f16c = 1;
                    break;
                default:
                    break;
                }
            } else {
                switch (b) {
                case 0:  d->f00 = (int16)v0; break;
                case 1:  d->f02 = (int16)v0; break;
                case 2:  d->f04 = (int16)v0; break;
                case 3:  d->f06 = (int16)v0; break;
                case 4:  d->f08 = (int16)v0; break;
                case 5:  d->f10 = v0; d->f14 = st[1]; d->f18 = st[2]; d->f1c = st[3]; break;
                case 13: d->f0c = v0; break;
                case 15: d->f34 = v0; break;
                case 16: d->f38 = v0; break;
                case 17: d->f3c = v0; break;
                case 18: d->f40 = v0; d->f44 = st[1]; break;
                default: break;
                }
            }
            n = 0;
        } else if (b == 0x1e) {
            st[n++] = READ_REAL(s);
        } else {
            st[n++] = (int)READ_INTEGER(s, b);
        }
    }

    Seek_InputStream(s, start);
}
