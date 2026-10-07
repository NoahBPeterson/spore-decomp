// Slice s008cfd50: T2K (Type 2000 font scaler, truetype.c) CacheKeyTables_sfntClass.
// Flags: /O2 /MD /Gy /EHsc /TP
//
// Frees every cached TrueType table of an sfntClass, then re-reads the key tables of logical
// font `logicalFontNumber` from the stream: ttcf, the offset table, head/bhed, hhea, vhea, maxp,
// loca, the CFF and DSIG locations, sloc, ffst, ffhm, hmtx, vmtx, kern (skipped for fonts with
// an 'fvar' table), EBLC/bloc with the EBDT/bdat offset, EBSC, the T2K glyph class, and the
// 'post' and 'OS/2' fields the scaler keeps. Returns 1.
//
// cl gave the original TU-local register conventions: CacheKeyTables_sfntClass takes t in ESI
// (callers 0x008d0d39 / 0x008d101a), and the static readers it calls take mem/stream in
// registers (New_ttcfClass eax/ebx, New_headClass/New_hheaClass/New_maxpClass ebx/edi,
// New_hmtxClass eax = numberOfHMetrics, New_kernClass eax = mem, which needs New_kernSubTable
// and New_kernSubTable0Data). Their real bodies are given below (they are not VAs of this slice)
// so that cl emits the same calls; GetUPEM / GetNumGlyphs_sfntClass / GetTableDirEntry_sfntClass
// are cdecl but in the same TU (cl keeps EDX live across GetNumGlyphs_sfntClass and inlines
// GetTableDirEntry_sfntClass at the top-level call sites). All of these helpers except
// New_hmtxClass (30 bytes: cmovg/branch shape) also match their original VAs. The stand-in caller
// at the bottom pins the convention of CacheKeyTables_sfntClass itself.
#include "types.h"
#include <stddef.h>

typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int32_t int32;

struct tsiMemObject;
struct InputStream;

#define tag_TTCHeader       0x74746366 /* 'ttcf' */
#define tag_FontHeader      0x68656164 /* 'head' */
#define tag_BFontHeader     0x62686564 /* 'bhed' */
#define tag_HoriHeader      0x68686561 /* 'hhea' */
#define tag_VertHeader      0x76686561 /* 'vhea' */
#define tag_MaxProfile      0x6d617870 /* 'maxp' */
#define tag_IndexToLoc      0x6c6f6361 /* 'loca' */
#define tag_CFF             0x43464620 /* 'CFF ' */
#define tag_DSIG            0x44534947 /* 'DSIG' */
#define tag_sloc            0x736c6f63 /* 'sloc' */
#define tag_ffst            0x66667374 /* 'ffst' */
#define tag_ffhm            0x6666686d /* 'ffhm' */
#define tag_HorizontalMetrics 0x686d7478 /* 'hmtx' */
#define tag_VerticalMetrics 0x766d7478 /* 'vmtx' */
#define tag_Kerning         0x6b65726e /* 'kern' */
#define tag_fvar            0x66766172 /* 'fvar' */
#define tag_EBLC            0x45424c43 /* 'EBLC' */
#define tag_bloc            0x626c6f63 /* 'bloc' */
#define tag_EBDT            0x45424454 /* 'EBDT' */
#define tag_bdat            0x62646174 /* 'bdat' */
#define tag_EBSC            0x45425343 /* 'EBSC' */
#define tag_PostScript      0x706f7374 /* 'post' */
#define tag_OS_2            0x4f532f32 /* 'OS/2' */

#define T2K_ERR_BAD_HMTX    10025

struct sfnt_DirectoryEntry {
    uint32 tag;           // +0x0
    uint32 checkSum;      // +0x4
    uint32 offset;        // +0x8
    uint32 length;        // +0xc
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

struct ttcfClass {
    tsiMemObject* mem;      // +0x0
    uint32 version;         // +0x4
    uint32 directoryCount;  // +0x8
    uint32* tableOffsets;   // +0xc
};

struct headClass {
    tsiMemObject* mem;          // +0x00
    int32 version;              // +0x04
    int32 fontRevision;         // +0x08
    uint32 checkSumAdjustment;  // +0x0c
    uint32 magicNumber;         // +0x10
    uint16 flags;               // +0x14
    uint16 unitsPerEm;          // +0x16
    int32 created_bc;           // +0x18
    int32 created_ad;           // +0x1c
    int32 modified_bc;          // +0x20
    int32 modified_ad;          // +0x24
    int16 xMin;                 // +0x28
    int16 yMin;                 // +0x2a
    int16 xMax;                 // +0x2c
    int16 yMax;                 // +0x2e
    uint16 macStyle;            // +0x30
    uint16 lowestRecPPEM;       // +0x32
    int16 fontDirectionHint;    // +0x34
    int16 indexToLocFormat;     // +0x36
    int16 glyphDataFormat;      // +0x38
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

struct maxpClass {
    tsiMemObject* mem;              // +0x00
    int32 version;                  // +0x04
    uint16 numGlyphs;               // +0x08
    uint16 maxPoints;               // +0x0a
    uint16 maxContours;             // +0x0c
    uint16 maxCompositePoints;      // +0x0e
    uint16 maxCompositeContours;    // +0x10
    uint16 maxElements;             // +0x12
    uint16 maxTwilightPoints;       // +0x14
    uint16 maxStorage;              // +0x16
    uint16 maxFunctionDefs;         // +0x18
    uint16 maxInstructionDefs;      // +0x1a
    uint16 maxStackElements;        // +0x1c
    uint16 maxSizeOfInstructions;   // +0x1e
    uint16 maxComponentElements;    // +0x20
    uint16 maxComponentDepth;       // +0x22
};

struct hmtxClass {
    tsiMemObject* mem;       // +0x00
    int32 numGlyphs;         // +0x04
    int32 numberOfHMetrics;  // +0x08
    int16* lsb;              // +0x0c
    uint16* aw;              // +0x10
};

struct locaClass {
    tsiMemObject* mem;       // +0x0
    uint32* offsets;         // +0x4
    int32 n;                 // +0x8
    int16 indexToLocFormat;  // +0xc
};

struct T2K_sloc_entry;
struct slocClass {
    tsiMemObject* mem;           // +0x00
    uint32 version;              // +0x04
    uint16 num_sloc_entries;     // +0x08
    T2K_sloc_entry* sloc;        // +0x0c
    uint32 numCorrections;       // +0x10
    uint32 correctionOffset;     // +0x14
};

struct kernPair0Struct {
    uint32 leftRightIndex;   // +0x0
    int16 value;             // +0x4
};

struct kernSubTable0Data {
    tsiMemObject* mem;           // +0x0
    uint16 nPairs;               // +0x4
    uint16 searchRange;          // +0x6
    uint16 entrySelector;        // +0x8
    uint16 rangeShift;           // +0xa
    kernPair0Struct* pairs;      // +0xc
};

struct kernSubTable {
    tsiMemObject* mem;           // +0x00
    uint16 version;              // +0x04
    int32 length;                // +0x08
    uint16 coverage;             // +0x0c
    void* kernData;              // +0x10
};

struct kernClass {
    tsiMemObject* mem;          // +0x0
    uint16 version;             // +0x4
    int32 nTables;              // +0x8
    kernSubTable** table;       // +0xc
};

struct T1Class {
    uint32_t pad00[0x30 / 4];
    int16 NumCharStrings;      // +0x030
    uint16 pad32;
    uint32_t pad34[(0x1e0 - 0x34) / 4];
    int32 upem;                // +0x1e0
};

struct CFFClass {
    uint32_t pad00[0xc / 4];
    int32 NumCharStrings;      // +0x00c
    uint32_t pad10[(0x21c - 0x10) / 4];
    int32 upem;                // +0x21c
};

struct PFRClass {
    uint32_t pad00[0x108 / 4];
    int16 NumCharStrings;      // +0x108
    uint16 pad10a;
    int32 upem;                // +0x10c
};

struct ffstClass;
struct ffhmClass;
struct blocClass;
struct ebscClass;
struct T2KTTClass;

struct CFF_Class {
    uint32 offset;   // +0x0
    uint32 length;   // +0x4
};

struct DSIGClass {
    uint32 offset;   // +0x0
    uint32 length;   // +0x4
};

typedef void (*StyleMetricsFuncPtr)(hmtxClass* hmtx, tsiMemObject* mem, uint16 UPEM, int32* params);

struct sfntClass {
    sfnt_OffsetTable* offsetTable0;      // +0x00
    void* GetAWFuncPtr1;                 // +0x04
    void* GetAWParam1;                   // +0x08
    void* GetAWFuncPtr2;                 // +0x0c
    void* GetAWParam2;                   // +0x10
    uint16* awCache_hashKey;             // +0x14
    uint16* awCache_aw;                  // +0x18
    uint16 upem;                         // +0x1c
    T1Class* T1;                         // +0x20
    CFFClass* T2;                        // +0x24
    PFRClass* PFR;                       // +0x28
    slocClass* sloc;                     // +0x2c
    ffstClass* ffst;                     // +0x30
    ffhmClass* ffhm;                     // +0x34
    blocClass* bloc;                     // +0x38
    ebscClass* ebsc;                     // +0x3c
    uint32 bdatOffset;                   // +0x40
    T2KTTClass* t2kTT;                   // +0x44
    void* ffhint;                        // +0x48
    ttcfClass* ttcf;                     // +0x4c
    headClass* head;                     // +0x50
    maxpClass* maxp;                     // +0x54
    locaClass* loca;                     // +0x58
    void* gasp;                          // +0x5c
    hheaClass* hhea;                     // +0x60
    hheaClass* vhea;                     // +0x64
    hmtxClass* hmtx;                     // +0x68
    hmtxClass* vmtx;                     // +0x6c
    void* cmap;                          // +0x70
    kernClass* kern;                     // +0x74
    CFF_Class CFF;                       // +0x78
    DSIGClass DSIG;                      // +0x80
    uint16 preferedPlatformID;           // +0x88
    uint16 preferedPlatformSpecificID;   // +0x8a
    int16 post_underlinePosition;        // +0x8c
    int16 post_underlineThickness;       // +0x8e
    uint32 isFixedPitch;                 // +0x90
    uint16 firstCharCode;                // +0x94
    uint16 lastCharCode;                 // +0x96
    uint16 hintsAvailable;               // +0x98
    int32 xPPEm;                         // +0x9c
    int32 yPPEm;                         // +0xa0
    void* globalHintsCache;              // +0xa4
    void* StyleFunc;                     // +0xa8
    StyleMetricsFuncPtr StyleMetricsFunc; // +0xac
    int32 params[4];                     // +0xb0
    int32 xScale;                        // +0xc0
    int32 yScale;                        // +0xc4
    int useNativeHints;                  // +0xc8
    int strokeGlyph;                     // +0xcc
    int greyScaleLevel;                  // +0xd0
    int32 currentCoordinate[2];          // +0xd4
    InputStream* in;                     // +0xdc
    InputStream* in2;                    // +0xe0
    void* out;                           // +0xe4
    tsiMemObject* mem;                   // +0xe8
    void* model;                         // +0xec
    int32 numGlyphs;                     // +0xf0
    int32 numberOfLogicalFonts;          // +0xf4
};

extern "C" {
void* tsi_AllocMem(tsiMemObject* mem, int32 size);
void tsi_DeAllocMem(tsiMemObject* mem, void* p);
void tsi_Error(tsiMemObject* mem, int32 errCode);
int32 ReadInt32(InputStream* in);
int16 ReadInt16(InputStream* in);
void Rewind_InputStream(InputStream* in);
void Seek_InputStream(InputStream* in, uint32 offset);
InputStream* New_InputStream2(tsiMemObject* mem, InputStream* in, uint32 offset, uint32 length,
                              int32 unused, int* errCode);
void Delete_InputStream(InputStream* t, int* errCode);

sfnt_OffsetTable* New_sfnt_OffsetTable(tsiMemObject* mem, InputStream* in);       // 0x008cd860
locaClass* New_locaClass(tsiMemObject* mem, InputStream* in, int16 indexToLocFormat, int32 length); // 0x008cdd60
hmtxClass* New_hmtxEmptyClass(tsiMemObject* mem, int32 numGlyphs, int32 numberOfHMetrics); // 0x008cda00
void Delete_kernClass(kernClass* t);                                               // 0x008cd790
slocClass* FF_New_slocClass(tsiMemObject* mem, InputStream* in);                   // 0x008cde20
ffstClass* FF_New_ffstClass(tsiMemObject* mem, InputStream* in, int32 length);     // 0x008cbf10
void FF_Delete_ffstClass(ffstClass* t);                                            // 0x008cc020
ffhmClass* FF_New_ffhmClass(tsiMemObject* mem, InputStream* in);                   // 0x008cb6b0
void FF_Delete_ffhmClass(ffhmClass* t);                                            // 0x008cd910 (ICF)
blocClass* New_blocClass(tsiMemObject* mem, int fontIsSbitOnly, InputStream* in);  // 0x008c75f0
void Delete_blocClass(blocClass* t);                                               // 0x008c4000
ebscClass* New_ebscClass(tsiMemObject* mem, InputStream* in);                      // 0x008c4030
void Delete_ebscClass(ebscClass* t);                                               // 0x008cd910 (ICF)
T2KTTClass* New_T2KTTClass(tsiMemObject* mem, InputStream* in, sfntClass* font);   // 0x008cc770
}

// ---------------------------------------------------------------- static table readers
// (bodies of 0x008cdb00, 0x008cdb80, 0x008cd940, 0x008cdc50, 0x008cda70, 0x008cd6f0)

static void Delete_sfnt_OffsetTable(sfnt_OffsetTable* t)
{
    if (t != NULL) {
        tsi_DeAllocMem(t->mem, t->table);
        tsi_DeAllocMem(t->mem, t);
    }
}

static ttcfClass* New_ttcfClass(tsiMemObject* mem, InputStream* in)
{
    ttcfClass* t = NULL;
    int i;

    Rewind_InputStream(in);
    if (ReadInt32(in) == tag_TTCHeader) {
        t = (ttcfClass*)tsi_AllocMem(mem, sizeof(ttcfClass));
        t->mem = mem;
        t->version = ReadInt32(in);
        t->directoryCount = ReadInt32(in);
        t->tableOffsets = (uint32*)tsi_AllocMem(mem, t->directoryCount * sizeof(uint32));
        for (i = 0; i < (int32)t->directoryCount; i++) {
            t->tableOffsets[i] = ReadInt32(in);
        }
    }
    Rewind_InputStream(in);
    return t;
}

static void Delete_ttcfClass(ttcfClass* t)
{
    if (t != NULL) {
        tsi_DeAllocMem(t->mem, t->tableOffsets);
        tsi_DeAllocMem(t->mem, t);
    }
}

static headClass* New_headClass(tsiMemObject* mem, InputStream* in)
{
    headClass* t = (headClass*)tsi_AllocMem(mem, sizeof(headClass));
    t->mem = mem;
    t->version = ReadInt32(in);
    t->fontRevision = ReadInt32(in);
    t->checkSumAdjustment = ReadInt32(in);
    t->magicNumber = ReadInt32(in);
    t->flags = ReadInt16(in);
    t->unitsPerEm = ReadInt16(in);
    t->created_bc = ReadInt32(in);
    t->created_ad = ReadInt32(in);
    t->modified_bc = ReadInt32(in);
    t->modified_ad = ReadInt32(in);
    t->xMin = ReadInt16(in);
    t->yMin = ReadInt16(in);
    t->xMax = ReadInt16(in);
    t->yMax = ReadInt16(in);
    t->macStyle = ReadInt16(in);
    t->lowestRecPPEM = ReadInt16(in);
    t->fontDirectionHint = ReadInt16(in);
    t->indexToLocFormat = ReadInt16(in);
    t->glyphDataFormat = ReadInt16(in);
    return t;
}

static void Delete_headClass(headClass* t)
{
    if (t != NULL) {
        tsi_DeAllocMem(t->mem, t);
    }
}

static hheaClass* New_hheaClass(tsiMemObject* mem, InputStream* in)
{
    hheaClass* t = (hheaClass*)tsi_AllocMem(mem, sizeof(hheaClass));
    t->mem = mem;
    t->version = ReadInt32(in);
    t->Ascender = ReadInt16(in);
    t->Descender = ReadInt16(in);
    t->LineGap = ReadInt16(in);
    t->advanceWidthMax = ReadInt16(in);
    t->minLeftSideBearing = ReadInt16(in);
    t->minRightSideBearing = ReadInt16(in);
    t->xMaxExtent = ReadInt16(in);
    t->caretSlopeRise = ReadInt16(in);
    t->caretSlopeRun = ReadInt16(in);
    t->caretOffset = ReadInt16(in);
    t->reserved2 = ReadInt16(in);
    t->reserved3 = ReadInt16(in);
    t->reserved4 = ReadInt16(in);
    t->reserved5 = ReadInt16(in);
    t->metricDataFormat = ReadInt16(in);
    t->numberOfHMetrics = ReadInt16(in);
    return t;
}

static void Delete_hheaClass(hheaClass* t)
{
    if (t != NULL) {
        tsi_DeAllocMem(t->mem, t);
    }
}

static hmtxClass* New_hmtxClass(tsiMemObject* mem, InputStream* in, int32 numGlyphs, int32 numberOfHMetrics)
{
    int i;
    hmtxClass* t;

    numberOfHMetrics = numberOfHMetrics > numGlyphs ? numGlyphs : numberOfHMetrics;
    t = New_hmtxEmptyClass(mem, numGlyphs, numberOfHMetrics);
    for (i = 0; i < numberOfHMetrics; i++) {
        t->aw[i] = ReadInt16(in);
        t->lsb[i] = ReadInt16(in);
    }
    if (i >= 1) {
        uint16 lastAW = t->aw[i - 1];
        for (; i < numGlyphs; i++) {
            t->aw[i] = lastAW;
            t->lsb[i] = ReadInt16(in);
        }
    }
    return t;
}

static void Delete_hmtxClass(hmtxClass* t)
{
    if (t != NULL) {
        tsi_DeAllocMem(t->mem, t->lsb);
        tsi_DeAllocMem(t->mem, t->aw);
        tsi_DeAllocMem(t->mem, t);
    }
}

static maxpClass* New_maxpClass(tsiMemObject* mem, InputStream* in)
{
    maxpClass* t = (maxpClass*)tsi_AllocMem(mem, sizeof(maxpClass));
    t->mem = mem;
    t->version = ReadInt32(in);
    t->numGlyphs = ReadInt16(in);
    if (t->version == 0x00010000) {
        t->maxPoints = ReadInt16(in);
        t->maxContours = ReadInt16(in);
        t->maxCompositePoints = ReadInt16(in);
        t->maxCompositeContours = ReadInt16(in);
        t->maxElements = ReadInt16(in);
        t->maxTwilightPoints = ReadInt16(in);
        t->maxStorage = ReadInt16(in);
        t->maxFunctionDefs = ReadInt16(in);
        t->maxInstructionDefs = ReadInt16(in);
        t->maxStackElements = ReadInt16(in);
        t->maxSizeOfInstructions = ReadInt16(in);
        t->maxComponentElements = ReadInt16(in);
        t->maxComponentDepth = ReadInt16(in);
    } else {
        // CFF-style 0.5 maxp: only numGlyphs is present
        t->maxPoints = 4;
        t->maxContours = 0;
        t->maxCompositePoints = 0;
        t->maxCompositeContours = 0;
        t->maxElements = 1;
        t->maxTwilightPoints = 0;
        t->maxStorage = 0;
        t->maxFunctionDefs = 1;
        t->maxInstructionDefs = 0;
        t->maxStackElements = 1;
        t->maxSizeOfInstructions = 0;
        t->maxComponentElements = 0;
        t->maxComponentDepth = 0;
    }
    return t;
}

static void Delete_maxpClass(maxpClass* t)
{
    if (t != NULL) {
        tsi_DeAllocMem(t->mem, t);
    }
}

static void Delete_locaClass(locaClass* t)
{
    if (t != NULL) {
        tsi_DeAllocMem(t->mem, t->offsets);
        tsi_DeAllocMem(t->mem, t);
    }
}

static void FF_Delete_slocClass(slocClass* t)
{
    if (t != NULL) {
        tsi_DeAllocMem(t->mem, t->sloc);
        tsi_DeAllocMem(t->mem, t);
    }
}

// 0x008cd580 (not in this slice; mem in EAX, in in EBX)
static kernSubTable0Data* New_kernSubTable0Data(tsiMemObject* mem, InputStream* in)
{
    int i;
    kernSubTable0Data* t = (kernSubTable0Data*)tsi_AllocMem(mem, sizeof(kernSubTable0Data));
    t->mem = mem;
    t->nPairs = ReadInt16(in);
    t->searchRange = ReadInt16(in);
    t->entrySelector = ReadInt16(in);
    t->rangeShift = ReadInt16(in);
    t->pairs = (kernPair0Struct*)tsi_AllocMem(mem, t->nPairs * sizeof(kernPair0Struct));
    for (i = 0; i < t->nPairs; i++) {
        t->pairs[i].leftRightIndex = ReadInt32(in);
        t->pairs[i].value = ReadInt16(in);
    }
    return t;
}

// 0x008cd660 (not in this slice; mem in EDI, in in EAX)
static kernSubTable* New_kernSubTable(tsiMemObject* mem, int appleFormat, InputStream* in)
{
    kernSubTable* t = (kernSubTable*)tsi_AllocMem(mem, sizeof(kernSubTable));
    t->mem = mem;
    t->kernData = NULL;
    if (appleFormat) {
        t->length = ReadInt32(in);
        t->coverage = ReadInt16(in);
        ReadInt16(in);  // tupleIndex
        t->version = t->coverage & 0xff;
    } else {
        t->version = ReadInt16(in);
        t->length = (uint16)ReadInt16(in);
        t->coverage = ReadInt16(in);
    }
    if (t->version == 0 && t->length > 0) {
        t->kernData = New_kernSubTable0Data(mem, in);
    }
    return t;
}

static kernClass* New_kernClass(tsiMemObject* mem, InputStream* in)
{
    int i;
    int appleFormat = 0;
    kernClass* t = (kernClass*)tsi_AllocMem(mem, sizeof(kernClass));
    t->mem = mem;
    t->version = ReadInt16(in);
    t->nTables = ReadInt16(in);
    if (t->version == 1 && t->nTables == 0) {
        // Apple 'kern' header: 32-bit version 1.0, then a 32-bit table count
        t->nTables = ReadInt32(in);
        appleFormat = 1;
    }
    t->table = (kernSubTable**)tsi_AllocMem(mem, t->nTables * sizeof(kernSubTable*));
    for (i = 0; i < t->nTables; i++) {
        t->table[i] = New_kernSubTable(mem, appleFormat, in);
    }
    return t;
}

// @ 0x008ceb70 (not in this slice) -- in the same TU, so cl knows which registers it clobbers
uint16 GetUPEM(sfntClass* t)
{
    if (t->upem == 0) {
        uint16 upem = 2048;
        if (t->T1 != NULL) {
            upem = (uint16)t->T1->upem;
        } else if (t->T2 != NULL) {
            upem = (uint16)t->T2->upem;
        } else if (t->PFR != NULL) {
            upem = (uint16)t->PFR->upem;
        } else if (t->sloc == NULL && t->head != NULL) {
            upem = t->head->unitsPerEm;
        }
        t->upem = upem;
    }
    return t->upem;
}

// @ 0x008cef90 (not in this slice)
int32 GetNumGlyphs_sfntClass(sfntClass* t)
{
    int32 n;
    if (t->T1 != NULL) return t->T1->NumCharStrings;
    if (t->T2 != NULL) return t->T2->NumCharStrings;
    if (t->PFR != NULL) return t->PFR->NumCharStrings;
    n = t->maxp->numGlyphs;
    if (t->loca != NULL && t->loca->n <= n) n = t->loca->n - 1;
    return n;
}

// @ 0x008cebe0 (not in this slice; inlined at most call sites below)
sfnt_DirectoryEntry* GetTableDirEntry_sfntClass(sfntClass* t, int32 tag)
{
    int i;
    for (i = 0; i < t->offsetTable0->numOffsets; i++) {
        if (t->offsetTable0->table[i].tag == (uint32)tag) {
            return &t->offsetTable0->table[i];
        }
    }
    return NULL;
}

// ---------------------------------------------------------------- CacheKeyTables_sfntClass

// @ 0x008cffd0 (static: t in ESI)
static int CacheKeyTables_sfntClass(sfntClass* t, InputStream* in, int32 logicalFontNumber)
{
    sfnt_DirectoryEntry* dirEntry;
    InputStream* in2;

    Delete_sfnt_OffsetTable(t->offsetTable0);  t->offsetTable0 = NULL;
    Delete_ttcfClass(t->ttcf);                 t->ttcf = NULL;
    Delete_headClass(t->head);                 t->head = NULL;
    Delete_hheaClass(t->hhea);                 t->hhea = NULL;
    Delete_hheaClass(t->vhea);                 t->vhea = NULL;
    Delete_hmtxClass(t->hmtx);                 t->hmtx = NULL;
    Delete_hmtxClass(t->vmtx);                 t->vmtx = NULL;
    Delete_maxpClass(t->maxp);                 t->maxp = NULL;
    Delete_locaClass(t->loca);                 t->loca = NULL;
    FF_Delete_slocClass(t->sloc);              t->sloc = NULL;
    FF_Delete_ffstClass(t->ffst);              t->ffst = NULL;
    FF_Delete_ffhmClass(t->ffhm);              t->ffhm = NULL;
    Delete_kernClass(t->kern);                 t->kern = NULL;
    Delete_blocClass(t->bloc);                 t->bloc = NULL;
    Delete_ebscClass(t->ebsc);                 t->ebsc = NULL;
    t->CFF.offset = 0;
    t->CFF.length = 0;
    t->DSIG.offset = 0;
    t->DSIG.length = 0;

    t->ttcf = New_ttcfClass(t->mem, in);
    if (t->ttcf != NULL) {
        t->numberOfLogicalFonts = t->ttcf->directoryCount;
        Seek_InputStream(in, t->ttcf->tableOffsets[logicalFontNumber]);
    }
    t->offsetTable0 = New_sfnt_OffsetTable(t->mem, in);

    dirEntry = GetTableDirEntry_sfntClass(t, tag_FontHeader);
    if (dirEntry == NULL) dirEntry = GetTableDirEntry_sfntClass(t, tag_BFontHeader);
    if (dirEntry != NULL) {
        in2 = New_InputStream2(t->mem, in, dirEntry->offset, dirEntry->length, 0, NULL);
        t->head = New_headClass(t->mem, in2);
        Delete_InputStream(in2, NULL);
    }
    dirEntry = GetTableDirEntry_sfntClass(t, tag_HoriHeader);
    if (dirEntry != NULL) {
        in2 = New_InputStream2(t->mem, in, dirEntry->offset, dirEntry->length, 0, NULL);
        t->hhea = New_hheaClass(t->mem, in2);
        Delete_InputStream(in2, NULL);
    }
    dirEntry = GetTableDirEntry_sfntClass(t, tag_VertHeader);
    if (dirEntry != NULL) {
        in2 = New_InputStream2(t->mem, in, dirEntry->offset, dirEntry->length, 0, NULL);
        t->vhea = New_hheaClass(t->mem, in2);
        Delete_InputStream(in2, NULL);
    }
    if (t->head != NULL && t->head->glyphDataFormat == 2002) {
        // T2K-compressed fonts store the metrics in 1/8 units
        if (t->hhea != NULL) {
            t->hhea->Ascender <<= 3;
            t->hhea->Descender <<= 3;
            t->hhea->LineGap <<= 3;
            t->hhea->advanceWidthMax <<= 3;
            t->hhea->minLeftSideBearing <<= 3;
            t->hhea->minRightSideBearing <<= 3;
            t->hhea->xMaxExtent <<= 3;
        }
        if (t->vhea != NULL) {
            t->vhea->Ascender <<= 3;
            t->vhea->Descender <<= 3;
            t->vhea->LineGap <<= 3;
            t->vhea->advanceWidthMax <<= 3;
            t->vhea->minLeftSideBearing <<= 3;
            t->vhea->minRightSideBearing <<= 3;
            t->vhea->xMaxExtent <<= 3;
        }
    }
    dirEntry = GetTableDirEntry_sfntClass(t, tag_MaxProfile);
    if (dirEntry != NULL) {
        in2 = New_InputStream2(t->mem, in, dirEntry->offset, dirEntry->length, 0, NULL);
        t->maxp = New_maxpClass(t->mem, in2);
        Delete_InputStream(in2, NULL);
    }
    dirEntry = GetTableDirEntry_sfntClass(t, tag_IndexToLoc);
    if (dirEntry != NULL) {
        in2 = New_InputStream2(t->mem, in, dirEntry->offset, dirEntry->length, 0, NULL);
        t->loca = New_locaClass(t->mem, in2, t->head->indexToLocFormat, dirEntry->length);
        Delete_InputStream(in2, NULL);
    }
    dirEntry = GetTableDirEntry_sfntClass(t, tag_CFF);
    if (dirEntry != NULL) {
        t->CFF.offset = dirEntry->offset;
        t->CFF.length = dirEntry->length;
    }
    dirEntry = GetTableDirEntry_sfntClass(t, tag_DSIG);
    if (dirEntry != NULL) {
        t->DSIG.offset = dirEntry->offset;
        t->DSIG.length = dirEntry->length;
    }
    dirEntry = GetTableDirEntry_sfntClass(t, tag_sloc);
    if (dirEntry != NULL) {
        Seek_InputStream(in, dirEntry->offset);
        t->sloc = FF_New_slocClass(t->mem, in);
    }
    dirEntry = GetTableDirEntry_sfntClass(t, tag_ffst);
    if (dirEntry != NULL) {
        in2 = New_InputStream2(t->mem, in, dirEntry->offset, dirEntry->length, 0, NULL);
        t->ffst = FF_New_ffstClass(t->mem, in2, dirEntry->length);
        Delete_InputStream(in2, NULL);
    } else if (t->CFF.offset == 0) {
        t->ffst = FF_New_ffstClass(t->mem, NULL, 0);
    }
    dirEntry = GetTableDirEntry_sfntClass(t, tag_ffhm);
    if (dirEntry != NULL) {
        in2 = New_InputStream2(t->mem, in, dirEntry->offset, dirEntry->length, 0, NULL);
        t->ffhm = FF_New_ffhmClass(t->mem, in2);
        Delete_InputStream(in2, NULL);
    }
    dirEntry = GetTableDirEntry_sfntClass(t, tag_HorizontalMetrics);
    if (dirEntry != NULL && t->hhea != NULL && t->maxp != NULL) {
        in2 = New_InputStream2(t->mem, in, dirEntry->offset, dirEntry->length, 0, NULL);
        t->hmtx = New_hmtxClass(t->mem, in2, GetNumGlyphs_sfntClass(t), t->hhea->numberOfHMetrics);
        Delete_InputStream(in2, NULL);
        if (t->StyleMetricsFunc != NULL) {
            t->StyleMetricsFunc(t->hmtx, t->mem, GetUPEM(t), t->params);
        }
    }
    dirEntry = GetTableDirEntry_sfntClass(t, tag_VerticalMetrics);
    if (dirEntry != NULL && t->vhea != NULL && t->maxp != NULL) {
        in2 = New_InputStream2(t->mem, in, dirEntry->offset, dirEntry->length, 0, NULL);
        t->vmtx = New_hmtxClass(t->mem, in2, GetNumGlyphs_sfntClass(t), t->vhea->numberOfHMetrics);
        Delete_InputStream(in2, NULL);
    }
    dirEntry = GetTableDirEntry_sfntClass(t, tag_Kerning);
    if (dirEntry != NULL && GetTableDirEntry_sfntClass(t, tag_fvar) != NULL) {
        dirEntry = NULL;  // no kerning for variation fonts
    }
    t->kern = NULL;
    if (dirEntry != NULL && dirEntry->length > 8) {
        in2 = New_InputStream2(t->mem, in, dirEntry->offset, dirEntry->length, 0, NULL);
        t->kern = New_kernClass(t->mem, in2);
        Delete_InputStream(in2, NULL);
    }

    t->bdatOffset = 0;
    t->bloc = NULL;
    t->ebsc = NULL;
    dirEntry = GetTableDirEntry_sfntClass(t, tag_EBLC);
    if (dirEntry == NULL) dirEntry = GetTableDirEntry_sfntClass(t, tag_bloc);
    if (dirEntry != NULL) {
        Seek_InputStream(in, dirEntry->offset);
        t->bloc = New_blocClass(t->mem, t->loca == NULL, in);
        dirEntry = GetTableDirEntry_sfntClass(t, tag_EBDT);
        if (dirEntry == NULL) dirEntry = GetTableDirEntry_sfntClass(t, tag_bdat);
        if (dirEntry != NULL) {
            uint32 version;
            Seek_InputStream(in, dirEntry->offset);
            version = ReadInt32(in);
            if (version >= 0x00020000 && version < 0x00030000) {
                t->bdatOffset = dirEntry->offset;
            }
        }
    }
    dirEntry = GetTableDirEntry_sfntClass(t, tag_EBSC);
    if (dirEntry != NULL) {
        in2 = New_InputStream2(t->mem, in, dirEntry->offset, dirEntry->length, 0, NULL);
        t->ebsc = New_ebscClass(t->mem, in2);
        Delete_InputStream(in2, NULL);
    }

    if (t->head != NULL && (t->head->glyphDataFormat < 2000 || t->head->glyphDataFormat > 2002)
        && t->CFF.offset == 0) {
        t->t2kTT = New_T2KTTClass(t->mem, in, t);
    }

    dirEntry = GetTableDirEntry_sfntClass(t, tag_PostScript);
    if (dirEntry != NULL) {
        Seek_InputStream(in, dirEntry->offset + 8);
        t->post_underlinePosition = ReadInt16(in);
        t->post_underlineThickness = ReadInt16(in);
        t->isFixedPitch = ReadInt32(in);
    } else {
        t->post_underlinePosition = 0;
        t->post_underlineThickness = 0;
        t->isFixedPitch = 0;
    }
    dirEntry = GetTableDirEntry_sfntClass(t, tag_OS_2);
    if (dirEntry != NULL) {
        Seek_InputStream(in, dirEntry->offset + 64);  // usFirstCharIndex
        t->firstCharCode = ReadInt16(in);
        t->lastCharCode = ReadInt16(in);
    } else {
        t->firstCharCode = 0;
        t->lastCharCode = 0xffff;
    }
    return 1;
}

// Stand-in for New_sfntClassLogical's two calls (0x008d0d39, 0x008d101a): makes cl emit
// CacheKeyTables_sfntClass with t in ESI like the original.
int s008cfd50_CacheKeyTablesCaller(sfntClass* t, int32 logicalFontNumber, int* errCode)
{
    if (!CacheKeyTables_sfntClass(t, t->in, logicalFontNumber)) {
        *errCode = T2K_ERR_BAD_HMTX;
        return 0;
    }
    if (!CacheKeyTables_sfntClass(t, t->in, logicalFontNumber + 1)) {
        *errCode = T2K_ERR_BAD_HMTX;
        return 0;
    }
    return 1;
}
