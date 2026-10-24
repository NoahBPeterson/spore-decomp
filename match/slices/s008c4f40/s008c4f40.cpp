// Slice s008c4f40 -- Adobe T2K (Type2K) font sbit-metrics routines linked into SporeApp.exe:
//
//   008c4f40  GetFontWideSbitMetrics  fill the horizontal/vertical font-wide metrics blocks
//   008c5320  FindGlyph_blocClass     locate a glyph's bitmap data pointer in a sbit table
//
// Both take their arguments in the retail whole-program (LTCG) register ABI, so a stock
// single-object cl cannot reproduce the bytes; they are written as complete, behaviourally
// equivalent C++ (every path and call of the original) and recorded in nonmatching.txt.
//
// Structures use the 2008 dev-PDB names and offsets (tools/pdb_type.py):
//   blocClass           +0x08 fontIsSbitOnly, +0x0c requestedBitDepth, +0x48 nTables, +0x4c table
//   bitmapSizeTable     +0x14 hori[12], +0x20 vert[12], +0x2c start/endGlyphIndex,
//                       +0x30 ppemX, +0x31 ppemY, +0x32 bitDepth, +0x33 flags, +0x34 table
//   indexSubTableArray  +0x00 firstGlyphIndex, +0x02 lastGlyphIndex, +0x04 indexSubTable
//   indexSubHeader      +0x00 indexFormat, +0x02 imageFormat, +0x04 imageDataOffset
//   indexSubTable1      +0x08 offsetArray     indexSubTable2  +0x08 imageSize, +0x0c bigMetrics
//   indexSubTable4      +0x08 numGlyphs, +0x0c glyphArray (codeOffsetPair)
//   indexSubTable5      +0x08 imageSize, +0x0c bigMetrics, +0x1c numGlyphs, +0x20 glyphArray
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed char    s8;

// ---------------------------------------------------------------- PDB structures
struct indexSubHeader          // 0x08
{
    u16 indexFormat;      // +0x00
    u16 imageFormat;      // +0x02
    u32 imageDataOffset;  // +0x04
};

struct indexSubTableArray      // 0x08
{
    u16 firstGlyphIndex;      // +0x00
    u16 lastGlyphIndex;       // +0x02
    indexSubHeader* indexSubTable; // +0x04
};

struct bigGlyphMetrics         // 0x10
{
    u16 height;        // +0x00
    u16 width;         // +0x02
    short horiBearingX;// +0x04
    short horiBearingY;// +0x06
    u16 horiAdvance;   // +0x08
    short vertBearingX;// +0x0a
    short vertBearingY;// +0x0c
    u16 vertAdvance;   // +0x0e
};

struct bitmapSizeTable         // 0x38
{
    u32  mem;                      // +0x00
    u32  indexSubTableArrayOffset; // +0x04
    u32  indexTableSize;           // +0x08
    u32  numberOfIndexSubTables;   // +0x0c
    u32  colorRef;                 // +0x10
    u8   hori[12];                 // +0x14
    u8   vert[12];                 // +0x20
    u16  startGlyphIndex;          // +0x2c
    u16  endGlyphIndex;            // +0x2e
    u8   ppemX;                    // +0x30
    u8   ppemY;                    // +0x31
    u8   bitDepth;                 // +0x32
    u8   flags;                    // +0x33
    indexSubTableArray* table;     // +0x34
};

struct blocClass               // 0x54
{
    u32 mem;                       // +0x00
    u32 startOffset;               // +0x04
    int fontIsSbitOnly;            // +0x08
    u32 requestedBitDepth;         // +0x0c
    u8  gInfo[0x34];               // +0x10  sbitGlypInfoData (unused here)
    u32 version;                   // +0x44
    u32 nTables;                   // +0x48
    bitmapSizeTable* table;        // +0x4c
    u8* cacheTables;               // +0x50
};

// A font-wide metrics block (0x18 bytes) written by GetFontWideSbitMetrics.
struct FontWideMetrics
{
    int   valid;  // +0x00
    short a;      // +0x04
    short b;      // +0x06
    short c;      // +0x08
    u16   d;      // +0x0a
    int   e;      // +0x0c
    int   f;      // +0x10
    short g;      // +0x14
    short h;      // +0x16
};

// The local query/result buffer FindBitmapSizeTable fills (an sbitGlypInfoData header).
struct SbitSizeQuery          // 0x14
{
    u8  pad00[6];          // +0x00
    u16 glyphIndex;        // +0x06
    u16 ppemY;             // +0x08
    u16 substitutePpemX;   // +0x0a
    u16 substitutePpemY;   // +0x0c
};

// The glyph-info record FindGlyph_blocClass fills.
struct SbitGlyphRecord
{
    u32  dataPtr;            // +0x00  bitmap data pointer (0 when absent)
    u16  glyphIndex;         // +0x04
    u8   pad06[8];           // +0x06
    u8   substituteBitDepth; // +0x0e
    u8   bitDepth;           // +0x0f
    u8   flags;              // +0x10
    u16  imageFormat;        // +0x12
    bigGlyphMetrics bigM;    // +0x14
};

// A code/offset pair (index format 4).
struct codeOffsetPair
{
    u16 glyphCode; // +0x00
    u16 offset;    // +0x02
};

// Index subtable bodies, one per indexFormat (1..5), all sharing the indexSubHeader prefix.
struct indexSubTable1            // index format 1 and 3, size 0x0c
{
    indexSubHeader header;       // +0x00
    u32* offsetArray;            // +0x08
};

struct indexSubTable2            // index format 2, size 0x1c
{
    indexSubHeader header;       // +0x00
    u32 imageSize;               // +0x08
    bigGlyphMetrics bigM;        // +0x0c
};

struct indexSubTable4            // index format 4, size 0x10
{
    indexSubHeader header;       // +0x00
    u32 numGlyphs;               // +0x08
    codeOffsetPair* glyphArray;  // +0x0c
};

struct indexSubTable5            // index format 5, size 0x24
{
    indexSubHeader header;       // +0x00
    u32 imageSize;               // +0x08
    bigGlyphMetrics bigM;        // +0x0c
    u32 numGlyphs;               // +0x1c
    u16* glyphArray;             // +0x20
};

// ---------------------------------------------------------------- callees
// The retail callee FindBitmapSizeTable (0x008c4dc0) uses the whole-program (LTCG) register
// ABI: the size table arrives in esi, the glyph code in eax and to ecx, with the subtable and
// the out buffer on the stack. No C declaration can pass esi, so the callee cannot be bound;
// equiv.py therefore reports both functions below UNSUPPORTED (docs/equivalence.md: a
// register-argument ABI our declaration does not reproduce is UNSUPPORTED, not tested).
namespace retail {
    int FindBitmapSizeTable(void* self, int xy, void* subtable, void* out); // 0x008c4dc0
}

// ---------------------------------------------------------------- scaling helper
// scaled = (value * num + den / 2) / den, truncating toward zero (cdq/idiv).
// The original inlines this seven times; keep it __forceinline so cl folds it back.
__forceinline int ScaleMetric(int value, int num, int den)
{
    return (value * num + (den >> 1)) / den;
}

// =====================================================================================
// @ 0x008c4f40  GetFontWideSbitMetrics
// Fills the horizontal metrics block (hor) and the vertical metrics block (ver) from the
// sbit table FindBitmapSizeTable selects for the requested ppem pair. xppem drives the
// horizontal byte columns, yppem the vertical ones; the substitute ppems from the query
// buffer are the divisors.
// Params (retail): self, subtable, yppem, xppem, hor, ver.
void GetFontWideSbitMetrics(void* self, void* subtable, int yppem, int xppem,
                            FontWideMetrics* hor, FontWideMetrics* ver)
{
    SbitSizeQuery siz;
    bitmapSizeTable* t = (bitmapSizeTable*)retail::FindBitmapSizeTable(self, xppem, subtable, &siz);
    if (t == 0) {
        hor->valid = 0;
        ver->valid = 0;
        return;
    }

    int subX = siz.substitutePpemX;   // +0x0a
    int subY = siz.substitutePpemY;   // +0x0c

    // ---- horizontal block (hori[0..4] = advance, bearingY, width, bearingX, row)
    hor->valid = 1;
    hor->a = (short)ScaleMetric((s8)t->hori[0], xppem, subY);
    hor->b = (short)ScaleMetric((s8)t->hori[1], xppem, subY);
    hor->c = 0;
    hor->d = (u16)ScaleMetric((u8)t->hori[2], yppem, subX);
    hor->f = ScaleMetric((s8)t->hori[3], yppem, subX);
    hor->e = ScaleMetric((s8)t->hori[4], xppem, subY);

    // Normalise the row/bit values: double both while they still fit in 16 bits.
    for (int i = 0; i < 16; ++i) {
        int e = hor->e;
        int f = hor->f;
        if (e >= 0x10000 || e <= -0x10000)
            break;
        if (f >= 0x10000 || f <= -0x10000)
            break;
        hor->e = e + e;
        hor->f = f + f;
    }

    // ---- vertical block (vert[0..4] = advance, bearingX, width, row, bearingY)
    ver->valid = 1;
    ver->a = (short)ScaleMetric((s8)t->vert[0], yppem, subX);
    ver->b = (short)ScaleMetric((s8)t->vert[1], yppem, subX);
    ver->c = 0;
    ver->d = (u16)ScaleMetric((u8)t->vert[2], xppem, subY);
    ver->f = ScaleMetric((s8)t->vert[4], yppem, subX);
    ver->e = ScaleMetric((s8)t->vert[3], xppem, subY);

    for (int i = 0; i < 16; ++i) {
        int e = ver->e;
        int f = ver->f;
        if (e >= 0x10000 || e <= -0x10000)
            break;
        if (f >= 0x10000 || f <= -0x10000)
            break;
        ver->e = e + e;
        ver->f = f + f;
    }

    // A negative "bearing" marker in hori[9] flips the vertical bearings.
    if (hor->b > 0 && (s8)t->hori[9] < 0) {
        hor->b = (short)-hor->b;
        ver->b = (short)-ver->b;
    }
}

// =====================================================================================
// @ 0x008c5320  FindGlyph_blocClass
// Locates glyph codepoint `code` inside the sbit table selected for the requested ppem
// pair and returns its bitmap data pointer (0 when absent), filling `info`.
// Returns 1 when data was found, 0 otherwise.
int FindGlyph_blocClass(blocClass* self, void* subtable, int yppem, u16 code,
                        void* unused, SbitGlyphRecord* info, int xppem)
{
    bitmapSizeTable* t = (bitmapSizeTable*)retail::FindBitmapSizeTable(self, xppem, subtable, info);

    u32 data = 0;
    u16 imageFormat = 0;
    u8  bitDepth = 0;

    if (t == 0)
        goto done;
    if (code < t->startGlyphIndex || code > t->endGlyphIndex)
        goto done;

    {
        int nSub = (int)t->numberOfIndexSubTables;
        if (nSub <= 0)
            goto done;

        indexSubTableArray* arr = t->table;
        int i = 0;
        while (i < nSub) {
            if (code >= arr[i].firstGlyphIndex && code <= arr[i].lastGlyphIndex)
                break;
            ++i;
        }
        if (i >= nSub)
            goto done;

        {
            indexSubTableArray* sub = &arr[i];
            indexSubHeader* hdr = sub->indexSubTable;

            bitDepth = t->bitDepth;
            info->substituteBitDepth = t->bitDepth;
            info->bitDepth = t->bitDepth;
            info->flags = t->flags;
            imageFormat = hdr->imageFormat;

            int fmt = (int)hdr->indexFormat - 1;
            if ((u32)fmt > 4)
                goto done;

            switch (fmt) {
            case 0:   // index format 1
            case 2:   // index format 3 (same arm as 1)
            {
                indexSubTable1* h1 = (indexSubTable1*)hdr;
                data = h1->offsetArray[(u32)code - sub->firstGlyphIndex];
                break;
            }
            case 1:   // index format 2
            {
                indexSubTable2* h2 = (indexSubTable2*)hdr;
                data = ((u32)code - sub->firstGlyphIndex) * h2->imageSize
                       + hdr->imageDataOffset;
                info->bigM = h2->bigM;
                break;
            }
            case 3:   // index format 4 (code/offset pairs)
            {
                indexSubTable4* h4 = (indexSubTable4*)hdr;
                int numGlyphs = (int)h4->numGlyphs;
                codeOffsetPair* pairs = h4->glyphArray;
                int lo = 0;
                while (lo < numGlyphs) {
                    if (pairs[lo].glyphCode == code) {
                        data = (u32)pairs[lo].offset + hdr->imageDataOffset;
                        break;
                    }
                    ++lo;
                }
                break;
            }
            case 4:   // index format 5 (sparse glyph index)
            {
                indexSubTable5* h5 = (indexSubTable5*)hdr;
                int numGlyphs = (int)h5->numGlyphs;
                u16* glyphs = h5->glyphArray;
                int lo = 0;
                while (lo < numGlyphs) {
                    if (glyphs[lo] == code) {
                        data = (u32)lo * h5->imageSize + hdr->imageDataOffset;
                        break;
                    }
                    ++lo;
                }
                break;
            }
            }
        }
    }

done:
    info->dataPtr = data;
    info->glyphIndex = code;
    info->imageFormat = imageFormat;
    (void)bitDepth;
    (void)yppem;
    (void)unused;
    (void)xppem;
    return data != 0 ? 1 : 0;
}
