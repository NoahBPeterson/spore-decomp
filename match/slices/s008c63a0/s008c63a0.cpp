// Slice s008c63a0: Adobe T2K (Type 2000) embedded-bitmap scaler/merger from psread.c,
// linked into SporeApp.exe:
//   008c63a0 MergeBits   merge one sbit glyph's rows into a larger glyph bitmap
//   008c6500 CopyRows    row copy for the vertical rescale (Bresenham row selection)
//   008c65d0 PackRows    row copy / bit repack for the horizontal rescale
//   008c6720 ScaleBits   rescale an sbit glyph to the substitute ppem
//   008c6990 ExtractBitMap  decode a packed bitmap (EBLC/EBDT image formats 1..9)
//
// The library was built with whole-program codegen (/GL + /LTCG): the original's static
// helpers receive arguments in arbitrary registers (MergeBits eax/ecx/edx, CopyRows
// eax/esi, PackRows eax/edx/ecx) and its leaf callees (CreateBitMap, ReadSmallMetrics,
// ReadBigMetrics, FindGlyph_blocClass) use the retail register ABI too.  A stock
// single-object cl cannot reproduce those conventions, so MergeBits/CopyRows/PackRows are
// kept static and out of line while ScaleBits and ExtractBitMap keep their external cdecl
// linkage; everything here is complete, behaviourally equivalent source recorded in
// nonmatching.txt.
//
// Structures use the 2008 dev-PDB names and offsets (tools/pdb_type.py):
//   sbitGlypInfoData +0x0 offset, +0x4 glyphIndex, +0x6 ppemX, +0x8 ppemY,
//                    +0xa substitutePpemX, +0xc substitutePpemY, +0xe substituteBitDepth,
//                    +0xf bitDepth, +0x10 flags, +0x12 imageFormat, +0x14 bigGlyphMetrics,
//                    +0x24 smallMetricsUsed, +0x28 rowBytes, +0x2c baseAddr, +0x30 N
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <string.h>

typedef uint8_t uint8;
typedef int8_t int8;
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
    uint32 pad220[3];              // +0x220
    tsiMemObject* mem;             // +0x22c
};

struct bigGlyphMetrics {
    uint16 height;         // +0x00
    uint16 width;          // +0x02
    int16  horiBearingX;   // +0x04
    int16  horiBearingY;   // +0x06
    uint16 horiAdvance;    // +0x08
    int16  vertBearingX;   // +0x0a
    int16  vertBearingY;   // +0x0c
    uint16 vertAdvance;    // +0x0e
};

struct SbitGlyphInfo {           // sbitGlypInfoData, 0x34
    uint32 dataOffset;           // +0x00
    uint16 glyphIndex;           // +0x04
    uint16 ppemX;                // +0x06
    uint16 ppemY;                // +0x08
    uint16 substitutePpemX;      // +0x0a
    uint16 substitutePpemY;      // +0x0c
    uint8  substituteBitDepth;   // +0x0e
    uint8  bitDepth;             // +0x0f
    uint8  flags;                // +0x10
    uint8  pad11;                // +0x11
    uint16 imageFormat;          // +0x12
    bigGlyphMetrics bigM;        // +0x14
    int32  smallMetricsUsed;     // +0x24
    uint32 rowBytes;             // +0x28
    uint8* baseAddr;             // +0x2c
    uint32 bitmapSize;           // +0x30
};

// One entry of the image-format 8/9 table: a glyph code, the sub-glyph's merge offset
// (x/bit position, y/row) and the glyph info record filled by FindGlyph_blocClass.
struct SbitGlyphRecord {         // 0x38
    uint16 glyphCode;            // +0x00
    uint8  x;                    // +0x02
    uint8  y;                    // +0x03
    SbitGlyphInfo info;          // +0x04
};

// The font object whose first member is the memory pool.
struct BlocFont {
    tsiMemObject* mem;           // +0x00
};

extern "C" {
void tsi_Error(tsiMemObject* mem, int32 errCode);        // 0x008d10c0
void* tsi_AllocMem(tsiMemObject* mem, uint32 size);      // 0x008d1260
void tsi_DeAllocMem(tsiMemObject* mem, void* p);         // 0x008d1440
void Seek_InputStream(InputStream* in, uint32 pos);      // 0x008cc580
void PrimeT2KInputStream(InputStream* in);               // 0x008cc0b0
int16 ReadInt16(InputStream* in);                        // 0x008cc190
void ReadSmallMetrics(InputStream* in, void* metrics);   // 0x008c4a00
void ReadBigMetrics(InputStream* in, void* metrics);     // 0x008c44d0
uint8* CreateBitMap(tsiMemObject* mem, SbitGlyphInfo* glyph, int width, int depth,
                    uint8 mode, int resetPerRow, int* rowBytesOut, int maxLevel,
                    InputStream* in, int height);        // 0x008c54d0
int FindGlyph_blocClass(BlocFont* font, void* subtable, InputStream* in, uint16 code,
                        uint16 ppemX, uint16 ppemY, SbitGlyphInfo* info); // 0x008c5320
}

#define T2K_ERR_TRANS_FAIL 10024

static __forceinline int ReadUnsignedByteSlow(InputStream* in)
{
    int error = in->ReadToRamFunc(in->nonRamID, in->tmp_ch, in->pos++, 1);
    if (error < 0) {
        tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
        return 0;
    }
    return in->tmp_ch[0];
}

#define ReadUnsignedByteMacro2(stream) \
    ((int)(((stream)->pos - (stream)->posZero + 1 > (stream)->cacheCount ? PrimeT2KInputStream(stream) : (void)0), \
             (stream)->privateBase[(stream)->pos++ - (stream)->posZero]))

#define ReadUnsignedByteMacro(stream) \
    ((uint8)((stream)->privateBase != 0 \
                 ? ((stream)->ReadToRamFunc != 0 ? ReadUnsignedByteMacro2(stream) \
                                                 : (stream)->privateBase[(stream)->pos++]) \
                 : ReadUnsignedByteSlow(stream)))

// Merges `src`'s rows into `dst` starting at destination row `rowOffset`.
// `bitPos` is the destination bit position of the first source pixel.  With mode == 0
// the source is a packed 1-bpp row; otherwise one source byte maps to one destination byte
// (maximum of the two values is kept).
// @ 0x008c63a0
static __declspec(noinline) void MergeBits(SbitGlyphInfo* dst, SbitGlyphInfo* src, uint8 bitPos,
                                           uint8 rowOffset, uint8 mode)
{
    uint8* dstBase = dst->baseAddr;
    uint8* srcBase = src->baseAddr;
    int dstRowBytes = dst->rowBytes;
    int srcRowBytes = src->rowBytes;
    int dstWidth = dst->bigM.width;
    int srcWidth = src->bigM.width;

    if (dstBase == 0 || srcBase == 0)
        return;

    uint8* dstEnd = dstBase + dst->bigM.height * dstRowBytes;
    uint8* dstRow = dstBase + rowOffset * dstRowBytes;

    if (mode == 0) {
        int rows = src->bigM.height;
        if (rows <= 0)
            return;
        int startBit = bitPos;
        do {
            int bit = startBit;
            int x = 0;
            if (srcWidth > 0) {
                int acc = 0;
                do {
                    if (bit >= dstWidth)
                        break;
                    if ((x & 7) == 0)
                        acc = srcBase[x >> 3];
                    acc += acc;
                    if (acc & 0x100)
                        dstRow[bit >> 3] |= (uint8)(0x80 >> (bit & 7));
                    x++;
                    bit++;
                } while (x < srcWidth);
            }
            dstRow += dstRowBytes;
            srcBase += srcRowBytes;
            if (dstRow >= dstEnd)
                return;
            rows--;
        } while (rows > 0);
    } else {
        int rows = src->bigM.height;
        if (rows <= 0)
            return;
        int startBit = bitPos;
        uint8* s = srcBase - startBit;
        do {
            int x = 0;
            int p = startBit;
            if (srcWidth > 0) {
                do {
                    if (p >= dstWidth)
                        break;
                    uint8 v = s[p];
                    if (v != 0 && v > dstRow[p])
                        dstRow[p] = v;
                    x++;
                    p++;
                } while (x < srcWidth);
            }
            srcBase += srcRowBytes;
            s = srcBase - startBit;
            dstRow += dstRowBytes;
            if (dstRow >= dstEnd)
                return;
            rows--;
        } while (rows > 0);
    }
}

// Copies `srcRowBytes`-sized rows from src to dst, selecting source rows with the
// Bresenham counter (oldSize/newSize) the vertical rescale uses.
// @ 0x008c6500
static __declspec(noinline) void CopyRows(uint8* src, int srcRowBytes, uint8* dst,
                                          int oldSize, int newSize)
{
    int n = oldSize * newSize;
    int pos = oldSize >> 1;
    int step = newSize;
    uint8* s = src;
    uint8* d = dst;

    if (pos >= n)
        return;

    if (newSize > oldSize) {
        do {
            while (step < pos) {
                step += newSize;
                s += srcRowBytes;
            }
            if (srcRowBytes > 0) {
                for (int i = 0; i < srcRowBytes; i++)
                    d[i] = s[i];
            }
            pos += oldSize;
            d += srcRowBytes;
        } while (pos < n);
    } else {
        do {
            while (step < pos) {
                step += newSize;
                s += srcRowBytes;
            }
            if (srcRowBytes > 0) {
                for (int i = 0; i < srcRowBytes; i++)
                    d[i] = s[i];
            }
            pos += oldSize;
            d += srcRowBytes;
        } while (pos < n);
    }
}

// Copies/rescales one row of `width` destination pixels from src to dst.  mode == 0
// writes a packed 1-bpp destination, otherwise one byte per pixel.
// @ 0x008c65d0
static __declspec(noinline) void PackRows(int width, uint8* dst, int rows, uint8* src,
                                          int step, int srcRowBytes, int dstRowBytes,
                                          uint8 mode)
{
    for (int r = 0; r < rows; r++) {
        int x;
        if (mode == 0) {
            uint8 cur = *src;
            uint8 acc = 0;
            int bit = 0;
            int avail = width;
            int pos = step >> 1;
            for (x = 0; x < width; x++) {
                while (avail < pos) {
                    bit++;
                    avail += width;
                    cur += cur;
                    if ((bit & 7) == 0)
                        cur = src[bit >> 3];
                }
                if (cur & 0x80)
                    acc |= (uint8)(0x80 >> (x & 7));
                if ((x & 7) == 7) {
                    dst[x >> 3] = acc;
                    acc = 0;
                }
                pos += step;
            }
            if ((x & 7) != 0)
                dst[(x - 1) >> 3] = acc;
        } else {
            int srcRow = 0;
            int avail = width;
            int pos = step >> 1;
            for (x = 0; x < width; x++) {
                if (avail < pos) {
                    do {
                        srcRow++;
                        avail += width;
                    } while (avail < pos);
                }
                dst[x] = src[srcRow];
                pos += step;
            }
        }
        src += srcRowBytes;
        dst += dstRowBytes;
    }
}

// Rescales an sbit glyph from its source ppem to the substitute ppem, vertically first
// and then horizontally.
// @ 0x008c6720
void ScaleBits(tsiMemObject* mem, SbitGlyphInfo* gi, uint8 mode, uint32 flags)
{
    uint32 ppemX = gi->ppemX;
    uint32 oldWidth = gi->bigM.width;
    uint32 subX = gi->substitutePpemX;
    uint32 newWidth = (uint32)((int32)(ppemX * oldWidth + (subX >> 1)) / (int32)subX);
    uint32 ppemY = gi->ppemY;
    uint32 oldHeight = gi->bigM.height;
    uint32 subY = gi->substitutePpemY;
    uint32 newHeight = (uint32)((int32)(ppemY * oldHeight + (subY >> 1)) / (int32)subY);

    if ((flags & 0x3000) != 0) {
        gi->bigM.horiBearingX = (int16)(gi->bigM.horiBearingX * 3);
        gi->bigM.vertBearingX = (int16)(gi->bigM.vertBearingX * 3);
        newWidth *= 3;
    } else if ((flags & 0xc000) != 0) {
        gi->bigM.horiBearingY = (int16)(gi->bigM.horiBearingY * 3);
        gi->bigM.vertBearingY = (int16)(gi->bigM.vertBearingY * 3);
        newHeight *= 3;
    }

    int cmp = -1;
    int which = 0;
    if ((int)oldHeight < (int)newHeight)
        cmp = 1;
    else if ((int)newHeight < (int)oldHeight) {
        cmp = 0;
        which = 1;
    }
    if (oldWidth == newWidth)
        which = -1;

    for (int pass = 0; pass < 2; pass++) {
        if (cmp == pass) {
            uint32 size = gi->rowBytes * newHeight;
            uint8* newBuf = (uint8*)tsi_AllocMem(mem, size);
            CopyRows(gi->baseAddr, (int)gi->rowBytes, newBuf, (int)oldHeight, (int)newHeight);
            tsi_DeAllocMem(mem, gi->baseAddr);
            gi->baseAddr = newBuf;
            gi->bigM.height = (uint16)newHeight;
            gi->bigM.horiBearingY = (int16)(((int)gi->bigM.horiBearingY * (int)ppemY
                                             + (int)(subY >> 1)) / (int)subY);
            gi->bigM.vertBearingY = (int16)(((int)gi->bigM.vertBearingY * (int)ppemY
                                             + (int)(subY >> 1)) / (int)subY);
            gi->bigM.vertAdvance = (uint16)(((int)gi->bigM.vertAdvance * (int)ppemY
                                             + (int)(subY >> 1)) / (int)subY);
        } else if (which == pass) {
            int newRowBytes = (mode == 0) ? (int)(newWidth + 7) / 8 : (int)newWidth;
            uint32 size = newRowBytes * newHeight;
            uint8* newBuf = (uint8*)tsi_AllocMem(mem, size);
            PackRows((int)newWidth, newBuf, (int)newHeight, gi->baseAddr, (int)oldWidth,
                     (int)gi->rowBytes, newRowBytes, mode);
            tsi_DeAllocMem(mem, gi->baseAddr);
            gi->baseAddr = newBuf;
            gi->bigM.width = (uint16)newWidth;
            gi->rowBytes = newRowBytes;
            gi->bigM.horiBearingX = (int16)(((int)gi->bigM.horiBearingX * (int)ppemX
                                             + (int)(subX >> 1)) / (int)subX);
            gi->bigM.vertBearingX = (int16)(((int)gi->bigM.vertBearingX * (int)ppemX
                                             + (int)(subX >> 1)) / (int)subX);
            gi->bigM.horiAdvance = (uint16)(((int)gi->bigM.horiAdvance * (int)ppemX
                                             + (int)(subX >> 1)) / (int)subX);
        }
    }
    gi->bitmapSize = (uint32)gi->bigM.height * gi->rowBytes;
}

// Decodes one EBDT bitmap for the glyph description in `gi`.  Image formats 1/2/5/6/7
// carry the metrics inline; formats 8/9 pull a table of sub-glyphs, decode each
// recursively and merge them into the parent bitmap.
// @ 0x008c6990
void ExtractBitMap(BlocFont* font, void* subtable, SbitGlyphInfo* gi, InputStream* in,
                   int imgOffset, int mode, int level, int maxLevel, uint32 flags)
{
    uint8* bitmap = 0;
    int rowBytes = 0;

    Seek_InputStream(in, gi->dataOffset + imgOffset);
    gi->smallMetricsUsed = 0;

    switch (gi->imageFormat) {
    case 1:
        ReadSmallMetrics(in, &gi->bigM);
        gi->smallMetricsUsed = 1;
        if (maxLevel != 0)
            bitmap = CreateBitMap(font->mem, gi, gi->bigM.width, gi->bitDepth, (uint8)mode,
                                  1, &rowBytes, maxLevel, in, gi->bigM.height);
        break;
    case 2:
        ReadSmallMetrics(in, &gi->bigM);
        gi->smallMetricsUsed = 1;
        if (maxLevel != 0)
            bitmap = CreateBitMap(font->mem, gi, gi->bigM.width, gi->bitDepth, (uint8)mode,
                                  0, &rowBytes, maxLevel, in, gi->bigM.height);
        break;
    case 5:
        if (maxLevel != 0)
            bitmap = CreateBitMap(font->mem, gi, gi->bigM.width, gi->bitDepth, (uint8)mode,
                                  0, &rowBytes, maxLevel, in, gi->bigM.height);
        break;
    case 6:
        ReadBigMetrics(in, &gi->bigM);
        if (maxLevel != 0)
            bitmap = CreateBitMap(font->mem, gi, gi->bigM.width, gi->bitDepth, (uint8)mode,
                                  1, &rowBytes, maxLevel, in, gi->bigM.height);
        break;
    case 7:
        ReadBigMetrics(in, &gi->bigM);
        if (maxLevel != 0)
            bitmap = CreateBitMap(font->mem, gi, gi->bigM.width, gi->bitDepth, (uint8)mode,
                                  0, &rowBytes, maxLevel, in, gi->bigM.height);
        break;
    case 8:
        ReadSmallMetrics(in, &gi->bigM);
        gi->smallMetricsUsed = 1;
        Seek_InputStream(in, in->pos + 1);
        goto composite;
    case 9:
        ReadBigMetrics(in, &gi->bigM);
    composite:
        {
            uint32 count = (uint16)ReadInt16(in);
            SbitGlyphRecord* table = (SbitGlyphRecord*)tsi_AllocMem(font->mem, count * 0x38);
            if ((int)count > 0) {
                for (uint32 i = 0; i < count; i++) {
                    table[i].glyphCode = (uint16)ReadInt16(in);
                    table[i].x = ReadUnsignedByteMacro(in);
                    table[i].y = ReadUnsignedByteMacro(in);
                }
                for (uint32 i = 0; i < count; i++) {
                    FindGlyph_blocClass(font, subtable, in, table[i].glyphCode,
                                        gi->substitutePpemX, gi->substitutePpemY,
                                        &table[i].info);
                }
            }
            if (maxLevel != 0) {
                if ((uint8)mode == 0)
                    rowBytes = ((int)gi->bigM.width + 7 + (((int)gi->bigM.width + 7) >> 31 & 7)) >> 3;
                else
                    rowBytes = (int)gi->bigM.width;
                uint32 size = (uint32)(uint16)gi->bigM.height * (uint32)rowBytes;
                bitmap = (uint8*)tsi_AllocMem(font->mem, size);
                gi->bitmapSize = size;
                if ((int)size > 0)
                    memset(bitmap, 0, size);
                gi->baseAddr = bitmap;
                gi->rowBytes = (uint32)rowBytes;
                if (level + 1 < 0x11 && (int)count > 0) {
                    for (uint32 i = 0; i < count; i++) {
                        ExtractBitMap(font, subtable, &table[i].info, in, imgOffset, mode,
                                      level + 1, maxLevel, flags);
                        MergeBits(gi, &table[i].info, table[i].x, table[i].y, (uint8)mode);
                        tsi_DeAllocMem(font->mem, table[i].info.baseAddr);
                        table[i].info.baseAddr = 0;
                    }
                }
                tsi_DeAllocMem(font->mem, table);
            }
        }
        break;
    default:
        break;
    }

    gi->rowBytes = (uint32)rowBytes;
    gi->baseAddr = bitmap;
    if ((uint8)mode != 0xff) {
        if ((flags & 0xf000) != 0
            || gi->substitutePpemX != gi->ppemX
            || gi->substitutePpemY != gi->ppemY)
            ScaleBits(font->mem, gi, (uint8)mode, flags);
    }
}
