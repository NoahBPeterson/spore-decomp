// Slice s008cd6f0: T2K (Type 2000 font scaler) sfnt.c / truetype.c table constructors
// and destructors -- the sfnt sub-table readers (kern, sfnt offset table, hhea, hmtx,
// head, maxp, loca, ttcf) plus the two sloc helpers.
//
// Several of these are TU-local (static) helpers to which cl gave a *custom register
// convention* (the memory object and/or the stream arriving in eax/ebx/edi instead of on
// the stack).  They are written as ordinary `static` functions with a same-TU stand-in
// caller so cl reproduces the convention (see docs/codegen.md 6.3).  The rest are plain
// cdecl and are written to match byte-for-byte.
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <stddef.h>

typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int32_t int32;

struct tsiMemObject;

typedef int (*PF_READ_TO_RAM)(void* id, uint8* dest, int32 offset, int32 numBytes);

struct InputStream {
    uint8* privateBase;            // +0x000
    PF_READ_TO_RAM ReadToRamFunc;  // +0x004
    void* nonRamID;                // +0x008
    uint8 tmp_ch[0x208];           // +0x00c
    uint32 cacheCount;             // +0x214
    uint32 posZero;                // +0x218
    uint32 pos;                    // +0x21c
    uint32 f220;                   // +0x220
    uint32 pad224[2];              // +0x224
    tsiMemObject* mem;             // +0x22c
};

struct sfnt_DirectoryEntry {
    uint32 tag;      // +0x0
    uint32 checkSum; // +0x4
    uint32 offset;   // +0x8
    uint32 length;   // +0xc
};

struct sfnt_OffsetTable {
    tsiMemObject* mem;           // +0x00
    int32 version;               // +0x04
    uint16 numOffsets;           // +0x08
    uint16 searchRange;          // +0x0a
    uint16 entrySelector;        // +0x0c
    uint16 rangeShift;           // +0x0e
    sfnt_DirectoryEntry* table;  // +0x10
};

struct kernSub10 {
    tsiMemObject* mem;  // +0x00
    int32 pad04[2];     // +0x04
    void* f0c;          // +0x0c
};

struct kernSubTable {
    tsiMemObject* mem;  // +0x00
    int16 version;      // +0x04
    int16 pad06;
    int32 pad08;        // +0x08
    int32 pad0c;        // +0x0c
    kernSub10* f10;     // +0x10
};

struct kernClass {
    tsiMemObject* mem;       // +0x00
    int16 version;           // +0x04
    int16 pad06;
    int32 nTables;           // +0x08
    kernSubTable** tables;   // +0x0c
};

struct sfntClass {
    uint8 pad00[0x74];
    kernClass* kern;   // +0x74
};

struct hheaClass {
    tsiMemObject* mem;           // +0x00
    int32 version;               // +0x04
    int16 Ascender;              // +0x08
    int16 Descender;             // +0x0a
    int16 LineGap;               // +0x0c
    uint16 advanceWidthMax;      // +0x0e
    int16 minLeftSideBearing;    // +0x10
    int16 minRightSideBearing;   // +0x12
    int16 xMaxExtent;            // +0x14
    int16 caretSlopeRise;        // +0x16
    int16 caretSlopeRun;         // +0x18
    int16 caretOffset;           // +0x1a
    int16 reserved2;             // +0x1c
    int16 reserved3;             // +0x1e
    int16 reserved4;             // +0x20
    int16 reserved5;             // +0x22
    int16 metricDataFormat;      // +0x24
    uint16 numberOfHMetrics;     // +0x26
};

struct hmtxClass {
    tsiMemObject* mem;   // +0x00
    int32 f04;           // +0x04
    int32 f08;           // +0x08
    uint16* f0c;         // +0x0c
    uint16* f10;         // +0x10
};

struct ttcfClass {
    tsiMemObject* mem;      // +0x0
    uint32 version;         // +0x4
    uint32 directoryCount;  // +0x8
    uint32* tableOffsets;   // +0xc
};

struct headClass {
    tsiMemObject* mem;       // +0x00
    int32 version;           // +0x04
    int32 fontRevision;      // +0x08
    uint32 checkSumAdjust;   // +0x0c
    uint32 magicNumber;      // +0x10
    uint16 flags;            // +0x14
    uint16 unitsPerEm;       // +0x16
    int32 created[2];        // +0x18
    int32 modified[2];       // +0x20
    int16 xMin;              // +0x28
    int16 yMin;              // +0x2a
    int16 xMax;              // +0x2c
    int16 yMax;              // +0x2e
    int16 macStyle;          // +0x30
    int16 lowestRecPPEM;     // +0x32
    int16 fontDirectionHint; // +0x34
    int16 indexToLocFormat;  // +0x36
    int16 glyphDataFormat;   // +0x38
};

struct maxpClass {
    tsiMemObject* mem;       // +0x00
    int32 version;           // +0x04
    uint16 numGlyphs;        // +0x08
    uint16 maxPoints;        // +0x0a
    uint16 maxContours;      // +0x0c
    uint16 maxCompositePoints;   // +0x0e
    uint16 maxCompositeContours; // +0x10
    uint16 maxZones;         // +0x12
    uint16 maxTwilightPoints;    // +0x14
    uint16 maxStorage;       // +0x16
    uint16 maxFunctionDefs;  // +0x18
    uint16 maxInstructionDefs;   // +0x1a
    uint16 maxStackElements; // +0x1c
    uint16 maxSizeOfInstructions; // +0x1e
    uint16 maxComponentElements;  // +0x20
    uint16 maxComponentDepth;     // +0x22
};

struct locaClass {
    tsiMemObject* mem;   // +0x00
    uint32* offsets;     // +0x04
    int32 n;             // +0x08
    int16 format;        // +0x0c
};

struct slocRecord {
    uint16 first;    // +0x0
    uint16 f2;       // +0x2
    int32 offset;    // +0x4
};

struct slocClass {
    tsiMemObject* mem;      // +0x00
    int32 f04;              // +0x04
    uint16 count;           // +0x08
    int16 pad0a;
    slocRecord* records;    // +0x0c
    int32 f10;              // +0x10
    int32 f14;              // +0x14
};

extern "C" {
void* tsi_AllocMem(tsiMemObject* mem, int32 size);        // 0x008d1260
void  tsi_DeAllocMem(tsiMemObject* mem, void* p);         // 0x008d1440
void  tsi_Error(tsiMemObject* mem, int32 code);           // 0x008d10c0
int16 ReadInt16(InputStream* in);                         // 0x008cc190
int32 ReadInt32(InputStream* in);                         // 0x008cc0f0
void  Rewind_InputStream(InputStream* in);                // 0x008cc550
void  Seek_InputStream(InputStream* in, int32 off);       // 0x008cc580
int32 Tell_InputStream(InputStream* in);                  // 0x008cc5b0
void  PrimeT2KInputStream(InputStream* in);               // 0x008cc0b0

// GetKernSubTable0Value is a TU-local helper in the original (this in ecx, the high
// half of the key in dx, the low half on the stack) -- declared __fastcall so the call
// site in GetSfntClassKernValue lines up.
uint16 __fastcall GetKernSubTable0Value(kernSub10* t, int32 hi, int32 lo);  // 0x008cd610
}

// The kern sub-table constructor is TU-local with mem in eax; declare it so the call
// site below at least uses the right argument order.
extern "C" kernSubTable* New_kernSubTable(tsiMemObject* mem, int32 flag);   // 0x008cd660

// ---------------------------------------------------------------------------------
// kern table
// ---------------------------------------------------------------------------------

// @ 0x008cd6f0
static kernClass* New_kernClass(tsiMemObject* mem, InputStream* in)
{
    int32 flag = 0;
    kernClass* k = (kernClass*)tsi_AllocMem(mem, 0x10);
    k->mem = mem;
    k->version = ReadInt16(in);
    k->nTables = ReadInt16(in);
    if (k->version == 1 && k->nTables == 0) {
        k->nTables = ReadInt32(in);
        flag = 1;
    }
    k->tables = (kernSubTable**)tsi_AllocMem(mem, k->nTables * 4);
    for (int32 i = 0; i < k->nTables; i++) {
        k->tables[i] = New_kernSubTable(mem, flag);
    }
    return k;
}

// @ 0x008cd790
void Delete_kernClass(kernClass* k)
{
    if (k != NULL) {
        for (int32 i = 0; i < k->nTables; i++) {
            kernSubTable* t = k->tables[i];
            if (t->version == 0) {
                kernSub10* s = t->f10;
                if (s != NULL) {
                    if (s->f0c != NULL) tsi_DeAllocMem(s->mem, s->f0c);
                    tsi_DeAllocMem(s->mem, s);
                }
            }
            tsi_DeAllocMem(t->mem, t);
        }
        tsi_DeAllocMem(k->mem, k->tables);
        tsi_DeAllocMem(k->mem, k);
    }
}

// @ 0x008cd810
void GetSfntClassKernValue(sfntClass* sfnt, int32 a2, int32 a3, uint16* out1, uint16* out2)
{
    uint16 v = 0;
    *out2 = 0;
    *out1 = 0;
    kernClass* k = sfnt->kern;
    if (k != NULL) {
        if (k->nTables > 0 && k->tables[0]->version == 0) {
            v = GetKernSubTable0Value(k->tables[0]->f10, a2, a3);
        }
        *out1 = v;
    }
}

// ---------------------------------------------------------------------------------
// sfnt offset table
// ---------------------------------------------------------------------------------

// @ 0x008cd860
sfnt_OffsetTable* New_sfnt_OffsetTable(tsiMemObject* mem, InputStream* in)
{
    sfnt_OffsetTable* t = (sfnt_OffsetTable*)tsi_AllocMem(mem, 0x14);
    t->mem = mem;
    t->version = ReadInt32(in);
    t->numOffsets = ReadInt16(in);
    t->searchRange = ReadInt16(in);
    t->entrySelector = ReadInt16(in);
    t->rangeShift = ReadInt16(in);
    t->table = (sfnt_DirectoryEntry*)tsi_AllocMem(mem, (uint32)t->numOffsets << 4);
    sfnt_DirectoryEntry* e = t->table;
    for (int32 i = 0; i < (int32)(uint32)t->numOffsets; i++) {
        e->tag = ReadInt32(in);
        e->checkSum = ReadInt32(in);
        e->offset = ReadInt32(in);
        e->length = ReadInt32(in);
        e++;
    }
    return t;
}

// @ 0x008cd910
void Delete_sfnt_OffsetTable(sfnt_OffsetTable* t)
{
    if (t != NULL) {
        tsi_DeAllocMem(t->mem, t->table);
        tsi_DeAllocMem(t->mem, t);
    }
}

// ---------------------------------------------------------------------------------
// hhea table
// ---------------------------------------------------------------------------------

// @ 0x008cd940
static hheaClass* New_hheaClass(tsiMemObject* mem, InputStream* in)
{
    hheaClass* h = (hheaClass*)tsi_AllocMem(mem, 0x28);
    h->mem = mem;
    h->version = ReadInt32(in);
    h->Ascender = ReadInt16(in);
    h->Descender = ReadInt16(in);
    h->LineGap = ReadInt16(in);
    h->advanceWidthMax = ReadInt16(in);
    h->minLeftSideBearing = ReadInt16(in);
    h->minRightSideBearing = ReadInt16(in);
    h->xMaxExtent = ReadInt16(in);
    h->caretSlopeRise = ReadInt16(in);
    h->caretSlopeRun = ReadInt16(in);
    h->caretOffset = ReadInt16(in);
    h->reserved2 = ReadInt16(in);
    h->reserved3 = ReadInt16(in);
    h->reserved4 = ReadInt16(in);
    h->reserved5 = ReadInt16(in);
    h->metricDataFormat = ReadInt16(in);
    h->numberOfHMetrics = ReadInt16(in);
    return h;
}

// ---------------------------------------------------------------------------------
// hmtx table
// ---------------------------------------------------------------------------------

// @ 0x008cda00
hmtxClass* New_hmtxEmptyClass(tsiMemObject* mem, int32 n, int32 n2)
{
    hmtxClass* h = (hmtxClass*)tsi_AllocMem(mem, 0x14);
    h->mem = mem;
    h->f04 = n;
    h->f08 = n2;
    if (n2 <= 0) tsi_Error(mem, 0x2729);
    if (n <= 0) tsi_Error(mem, 0x2729);
    h->f0c = (uint16*)tsi_AllocMem(mem, n * 2);
    h->f10 = (uint16*)tsi_AllocMem(mem, n * 2);
    return h;
}

// @ 0x008cda70
static hmtxClass* New_hmtxClass(tsiMemObject* mem, InputStream* in, int32 count, int32 count2)
{
    int32 n = count < count2 ? count : count2;
    hmtxClass* h = New_hmtxEmptyClass(mem, count2, n);
    int32 i = 0;
    if (n > 0) {
        for (; i < n; i++) {
            h->f10[i] = ReadInt16(in);
            h->f0c[i] = ReadInt16(in);
        }
        if (i > 0) {
            uint16 last = h->f10[i - 1];
            for (; i < count2; i++) {
                h->f10[i] = last;
                h->f0c[i] = ReadInt16(in);
            }
        }
    }
    return h;
}

// ---------------------------------------------------------------------------------
// ttcf table
// ---------------------------------------------------------------------------------

// @ 0x008cdb00
static ttcfClass* New_ttcfClass(tsiMemObject* mem, InputStream* in)
{
    ttcfClass* t = NULL;
    Rewind_InputStream(in);
    if (ReadInt32(in) == 0x74746366) {
        t = (ttcfClass*)tsi_AllocMem(mem, 0x10);
        t->mem = mem;
        t->version = ReadInt32(in);
        t->directoryCount = ReadInt32(in);
        t->tableOffsets = (uint32*)tsi_AllocMem(mem, t->directoryCount * 4);
        for (int32 i = 0; i < (int32)t->directoryCount; i++) {
            t->tableOffsets[i] = ReadInt32(in);
        }
    }
    Rewind_InputStream(in);
    return t;
}

// ---------------------------------------------------------------------------------
// head table
// ---------------------------------------------------------------------------------

// @ 0x008cdb80
static headClass* New_headClass(tsiMemObject* mem, InputStream* in)
{
    headClass* h = (headClass*)tsi_AllocMem(mem, 0x3c);
    h->mem = mem;
    h->version = ReadInt32(in);
    h->fontRevision = ReadInt32(in);
    h->checkSumAdjust = ReadInt32(in);
    h->magicNumber = ReadInt32(in);
    h->flags = ReadInt16(in);
    h->unitsPerEm = ReadInt16(in);
    h->created[0] = ReadInt32(in);
    h->created[1] = ReadInt32(in);
    h->modified[0] = ReadInt32(in);
    h->modified[1] = ReadInt32(in);
    h->xMin = ReadInt16(in);
    h->yMin = ReadInt16(in);
    h->xMax = ReadInt16(in);
    h->yMax = ReadInt16(in);
    h->macStyle = ReadInt16(in);
    h->lowestRecPPEM = ReadInt16(in);
    h->fontDirectionHint = ReadInt16(in);
    h->indexToLocFormat = ReadInt16(in);
    h->glyphDataFormat = ReadInt16(in);
    return h;
}

// ---------------------------------------------------------------------------------
// maxp table
// ---------------------------------------------------------------------------------

// @ 0x008cdc50
static maxpClass* New_maxpClass(tsiMemObject* mem, InputStream* in)
{
    maxpClass* m = (maxpClass*)tsi_AllocMem(mem, 0x24);
    m->mem = mem;
    m->version = ReadInt32(in);
    m->numGlyphs = ReadInt16(in);
    if (m->version == 0x10000) {
        m->maxPoints = ReadInt16(in);
        m->maxContours = ReadInt16(in);
        m->maxCompositePoints = ReadInt16(in);
        m->maxCompositeContours = ReadInt16(in);
        m->maxZones = ReadInt16(in);
        m->maxTwilightPoints = ReadInt16(in);
        m->maxStorage = ReadInt16(in);
        m->maxFunctionDefs = ReadInt16(in);
        m->maxInstructionDefs = ReadInt16(in);
        m->maxStackElements = ReadInt16(in);
        m->maxSizeOfInstructions = ReadInt16(in);
        m->maxComponentElements = ReadInt16(in);
        m->maxComponentDepth = ReadInt16(in);
    } else {
        m->maxPoints = 4;
        m->maxContours = 0;
        m->maxCompositePoints = 0;
        m->maxCompositeContours = 0;
        m->maxZones = 1;
        m->maxTwilightPoints = 0;
        m->maxStorage = 0;
        m->maxFunctionDefs = 1;
        m->maxInstructionDefs = 0;
        m->maxStackElements = 1;
        m->maxSizeOfInstructions = 0;
        m->maxComponentElements = 0;
        m->maxComponentDepth = 0;
    }
    return m;
}

// ---------------------------------------------------------------------------------
// loca table
// ---------------------------------------------------------------------------------

// @ 0x008cdd60
locaClass* New_locaClass(tsiMemObject* mem, InputStream* in, int16 format, int32 numGlyphs)
{
    locaClass* l = (locaClass*)tsi_AllocMem(mem, 0x10);
    int32 n = numGlyphs >> (format + 1);
    l->format = format;
    l->mem = mem;
    l->n = n;
    l->offsets = (uint32*)tsi_AllocMem(mem, n * 4);
    if (in != NULL) {
        if (format == 1) {
            for (int32 i = 0; i < n; i++) {
                l->offsets[i] = ReadInt32(in);
            }
        } else if (format == 0) {
            for (int32 i = 0; i < n; i++) {
                int32 v = (uint16)ReadInt16(in);
                l->offsets[i] = (uint32)v * 2;
            }
        } else {
            tsi_Error(mem, 0x2729);
        }
    }
    return l;
}

// ---------------------------------------------------------------------------------
// sloc table
// ---------------------------------------------------------------------------------

// @ 0x008cde20
slocClass* FF_New_slocClass(tsiMemObject* mem, InputStream* in)
{
    slocClass* s = (slocClass*)tsi_AllocMem(mem, 0x18);
    s->mem = mem;
    s->f04 = ReadInt32(in);
    s->count = ReadInt16(in);
    s->records = (slocRecord*)tsi_AllocMem(mem, (uint32)s->count * 8);
    slocRecord* r = s->records;
    for (int32 i = 0; i < (int32)(uint32)s->count; i++) {
        r->first = ReadInt16(in);
        r->f2 = ReadInt16(in);
        r->offset = ReadInt32(in);
        r++;
    }
    s->f10 = ReadInt32(in);
    s->f14 = Tell_InputStream(in);
    return s;
}

// @ 0x008cdec0
int32 FF_SLOC_MapIndexToOffset(slocClass* s, InputStream* in, int32 index)
{
    slocRecord* rec = s->records;
    uint16 a = 0, c = 0;
    uint8 b;
    int32 lo, hi, mid;

    Seek_InputStream(in, s->f14 + index);
    if (in->pos < in->f220) {
        if (in->privateBase != NULL) {
            if (in->ReadToRamFunc == NULL) {
                b = in->privateBase[in->pos];
                in->pos++;
            } else {
                if ((in->pos - in->posZero) + 1 > in->cacheCount) PrimeT2KInputStream(in);
                b = in->privateBase[in->pos - in->posZero];
                in->pos++;
            }
        } else {
            uint8* p = in->tmp_ch;
            in->pos++;
            if (in->ReadToRamFunc(in->nonRamID, p, in->pos - 1, 1) < 0) {
                tsi_Error(in->mem, 0x2728);
                b = 0;
            } else {
                b = *p;
            }
        }
    } else {
        b = 0xff;
    }

    hi = (int32)s->count - 2;
    lo = 0;
    mid = 0;
    if (hi >= 0) {
        do {
            mid = (hi + lo + 1) >> 1;
            a = rec[mid].first;
            c = rec[mid + 1].first;
            if (index < (int32)a) {
                hi = mid - 1;
            } else {
                if (index < (int32)c) break;
                if (index < (int32)a) hi = mid - 1;
                else lo = mid + 1;
            }
        } while (lo <= hi);
    }
    return ((index - (int32)a) * (int32)rec[mid].f2) / ((int32)(uint16)(c - 1) - (int32)a)
           + rec[mid].offset - (int32)b;
}

// ---------------------------------------------------------------------------------
// Stand-in callers: keep the TU-local helpers referenced (so cl emits them) and pin
// their register conventions.  Not part of the slice.
// ---------------------------------------------------------------------------------
void* s008cd6f0_kern(tsiMemObject* mem, InputStream* in)
{
    return New_kernClass(mem, in);
}

void* s008cd6f0_hhea(tsiMemObject* mem, InputStream* in)
{
    return New_hheaClass(mem, in);
}

void* s008cd6f0_hmtx(tsiMemObject* mem, InputStream* in, int32 count, int32 count2)
{
    return New_hmtxClass(mem, in, count, count2);
}

void* s008cd6f0_ttcf(tsiMemObject* mem, InputStream* in)
{
    return New_ttcfClass(mem, in);
}

void* s008cd6f0_head(tsiMemObject* mem, InputStream* in)
{
    return New_headClass(mem, in);
}

void* s008cd6f0_maxp(tsiMemObject* mem, InputStream* in)
{
    return New_maxpClass(mem, in);
}

void* s008cd6f0_loca(tsiMemObject* mem, InputStream* in, int16 format, int32 numGlyphs)
{
    return New_locaClass(mem, in, format, numGlyphs);
}
