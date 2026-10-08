// Slice s008af670: T2K (Type 2000) glyph decoder -- ReadDeltaXYValue (0x008af670).
// Decodes one compressed delta pair (dx, dy) from the stream; returns the on-curve flag.
// Module flags: /O2 /MD /Gy /TP.
#include "types.h"

typedef uint8_t uint8;
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

extern "C" {
void tsi_Error(tsiMemObject* mem, int32 errCode);   // 0x008d10c0
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

// @ 0x008af670
uint32 ReadDeltaXYValue(InputStream* in, int16* dx, int16* dy)
{
    uint32 value = ReadUnsignedByteMacro(in) << 8;
    value |= ReadUnsignedByteMacro(in);
    int code = (int)(value >> 14);
    value &= 0x3fff;
    uint32 x, y;
    if (value < 0x898) {
        if (value == 0 && code <= 1) {
            uint16 a = (uint16)(ReadUnsignedByteMacro(in) << 8);
            a |= ReadUnsignedByteMacro(in);
            uint16 b = (uint16)(ReadUnsignedByteMacro(in) << 8);
            b |= ReadUnsignedByteMacro(in);
            *dx = (int16)a;
            *dy = (int16)b;
            return code == 0;
        }
        x = value;
        y = 0;
    }
    else if (value < 0x313c) {
        value -= 0x898;
        x = (int16)value / 0x66 + 1;
        y = (int16)value % 0x66 + 1;
    }
    else if (value < 0x393c) {
        uint32 v = (value - 0x313c) << 8;
        v |= ReadUnsignedByteMacro(in);
        x = v / 0x2d4 + 1;
        y = v % 0x2d4 + 1;
    }
    else {
        uint32 v = (value - 0x393c) << 8;
        v |= ReadUnsignedByteMacro(in);
        v <<= 8;
        v |= ReadUnsignedByteMacro(in);
        x = v / 0x299a;
        y = v % 0x299a;
    }
    int32 ry = 0;
    int32 rx = 0;
    switch (code) {
    case 0: rx = x; ry = y; break;
    case 1: rx = -(int32)y; ry = x; break;
    case 2: rx = -(int32)x; ry = -(int32)y; break;
    case 3: rx = y; ry = -(int32)x; break;
    }
    *dx = (int16)(rx >> 1);
    *dy = (int16)ry;
    return 1 - (rx & 1);
}
