// Slice s008c54d0: T2K (Type 2000) embedded-bitmap decoder -- CreateBitMap @ 0x008c54d0.
// Unpacks a 1/2/4/8 bit-per-pixel sbit image from the input stream into a freshly allocated
// 1 bpp (mode 0) or 8 bpp (mode != 0) bitmap and reports the row stride.
// Same-TU static helper: cl gives it a register calling convention (ecx = mem, eax = height,
// esi = stream), so a small caller keeps it from being inlined.
// Module flags: /O2 /MD /Gy /TP.
#include "types.h"
#include <string.h>

typedef uint8_t uint8;
typedef int8_t int8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int32_t int32;

struct tsiMemObject;
typedef int (*PF_READ_TO_RAM)(void* id, uint8* dst, uint32 pos, uint32 n);

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

struct SbitGlyph {                 // only the fields touched here
    char pad0[0xf];
    uint8 bitsPerPixel;            // +0x0f
    char pad10[0x20];
    uint32 bitmapSize;             // +0x30
};

extern "C" {
void tsi_Error(tsiMemObject* mem, int32 errCode);   // 0x008d10c0
void* tsi_AllocMem(tsiMemObject* mem, uint32 size); // 0x008d1260
void PrimeT2KInputStream(InputStream* in);          // 0x008cc0b0
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

// mode: 0 = 1 bpp output, -1 = generic depth unpack, anything else = switch on depth.
// resetPerRow: restart the bit reader at every row.  maxLevel: gray value of a full pixel.
// @ 0x008c54d0
static __declspec(noinline) uint8* CreateBitMap(tsiMemObject* mem, SbitGlyph* glyph, int width, int depth,
                                                uint8 mode, int resetPerRow, int* rowBytesOut,
                                                int maxLevel, InputStream* in, int height)
{
    int rowBytes = width;
    if (mode == 0) rowBytes = (width + 7) / 8;
    uint32 size = rowBytes * height;
    glyph->bitmapSize = size;
    if (size == 0) {
        *rowBytesOut = 0;
        return 0;
    }
    uint8* buf = (uint8*)tsi_AllocMem(mem, size);
    memset(buf, 0, size);
    int left = 0;
    int cur = 0;
    if (mode > 0) {
        glyph->bitsPerPixel = 8;
        if (mode == 0xff) {
            left = depth;
            int mask = (1 << depth) - 1;
            uint8* row = buf;
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    left -= depth;
                    if (left == 0) { cur = ReadUnsignedByteMacro(in); left = 8; }
                    row[x] = (uint8)((cur >> (left - depth)) & mask);
                }
                if (resetPerRow) left = depth;
                row += width;
            }
        } else {
            switch (depth) {
            case 1: {
                uint8* row = buf;
                for (int y = 0; y < height; y++) {
                    for (int x = 0; x < width; x++) {
                        if (left-- == 0) { cur = ReadUnsignedByteMacro(in); left = 7; }
                        cur <<= 1;
                        row[x] = (cur & 0x100) ? maxLevel : 0;
                    }
                    if (resetPerRow) left = 0;
                    row += rowBytes;
                }
                break;
            }
            case 2: {
                left = 2;
                uint8* row = buf;
                for (int y = 0; y < height; y++) {
                    for (int x = 0; x < width; x++) {
                        left -= 2;
                        if (left == 0) { cur = ReadUnsignedByteMacro(in); left = 8; }
                        switch ((cur >> (left - 2)) & 3) {
                        case 0: row[x] = 0; break;
                        case 1: row[x] = (uint8)(maxLevel / 3); break;
                        case 2: row[x] = (uint8)((maxLevel * 2) / 3); break;
                        case 3: row[x] = (uint8)maxLevel; break;
                        }
                    }
                    if (resetPerRow) left = 2;
                    row += rowBytes;
                }
                break;
            }
            case 4: {
                uint8* row = buf;
                if (maxLevel == 0x7e) {
                    for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x += 2) {
                            uint8 b = ReadUnsignedByteMacro(in);
                            uint8 hi = b >> 4;
                            row[x] = (uint8)(((hi >> 1) & 6) + hi * 8);
                            if (x + 1 < width) {
                                uint8 lo = b & 0xf;
                                row[x + 1] = (uint8)(((lo >> 1) & 6) + lo * 8);
                            }
                        }
                        row += rowBytes;
                    }
                } else {
                    for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x += 2) {
                            uint8 b = ReadUnsignedByteMacro(in);
                            row[x] = (uint8)((b >> 4) * 0x11);
                            if (x + 1 < width) row[x + 1] = (uint8)((b & 0xf) * 0x11);
                        }
                        row += rowBytes;
                    }
                }
                break;
            }
            case 8:
                if (maxLevel == 0x7e) {
                    for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                            uint8 b = ReadUnsignedByteMacro(in);
                            buf[x] = (uint8)((b * 0x7e + 0x3f) / 0x7e);
                        }
                    }
                } else {
                    for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) buf[x] = ReadUnsignedByteMacro(in);
                    }
                }
                break;
            }
        }
        } else {
        glyph->bitsPerPixel = 1;
        switch (depth) {
        case 8: {
            uint8* row = buf;
            for (int y = 0; y < height; y++) {
                int x = 0;
                if (0 < width) do {
                    int8 b = (int8)ReadUnsignedByteMacro(in);
                    if (b < 0) row[x >> 3] |= (uint8)(1 << (7 - x % 8));
                    x++;
                } while (x < width);
                row += rowBytes;
            }
            break;
        }
        case 4: {
            left = 4;
            uint8* row = buf;
            for (int y = 0; y < height; y++) {
                int x = 0;
                if (0 < width) do {
                    left -= 4;
                    if (left == 0) { cur = ReadUnsignedByteMacro(in); left = 8; }
                    if ((cur >> (left - 4)) & 8) row[x >> 3] |= (uint8)(1 << (7 - x % 8));
                    x++;
                } while (x < width);
                if (resetPerRow) left = 4;
                row += rowBytes;
            }
            break;
        }
        case 2: {
            left = 2;
            uint8* row = buf;
            for (int y = 0; y < height; y++) {
                int x = 0;
                if (0 < width) do {
                    left -= 2;
                    if (left == 0) { cur = ReadUnsignedByteMacro(in); left = 8; }
                    if ((cur >> (left - 2)) & 2) row[x >> 4] |= (uint8)(1 << (7 - x % 8));
                    x++;
                } while (x < width);
                row += rowBytes;
                if (resetPerRow) left = 2;
            }
            break;
        }
        default:
        if (resetPerRow == 0) {
            uint8* row = buf;
            for (int y = 0; y < height; y++) {
                int x;
                uint8 acc = 0;
                for (x = 0; x < width; x++) {
                    if (left-- == 0) { cur = ReadUnsignedByteMacro(in); left = 7; }
                    cur <<= 1;
                    if (cur & 0x100) acc |= (uint8)(0x80 >> (x & 7));
                    if ((x & 7) == 7) { row[x >> 3] = acc; acc = 0; }
                }
                if (x & 7) row[x >> 3] = acc;
                row += rowBytes;
            }
        } else {
            uint8* row = buf;
            for (int y = 0; y < height; y++) {
                for (int i = 0; i < rowBytes; i++) row[i] = ReadUnsignedByteMacro(in);
                row += rowBytes;
            }
        }
        }
    }
    *rowBytesOut = rowBytes;
    return buf;
}

// Callers (stand-ins for the sbit extractor at 0x008c6990) so the static stays out of line.
uint8* ExtractBitMap(tsiMemObject* mem, SbitGlyph* g, int w, int d, int rst, int* rb, int lvl, InputStream* in, int h)
{
    uint8* r = CreateBitMap(mem, g, w, d, 1, rst, rb, lvl, in, h);
    if (!r) r = CreateBitMap(mem, g, w, d, 0, rst, rb, lvl, in, h);
    if (!r) r = CreateBitMap(mem, g, w, d, 0xff, rst, rb, lvl, in, h);
    return r;
}
