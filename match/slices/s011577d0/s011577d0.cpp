// Slice s011577d0 -- 0x011577d0: per-block coefficient-width reader of a bit-stream decoder.
// Flags: /O2 /MD /Gy /TP /EHsc (default).
//
// The decoder object embeds an MSB-first bit reader (read pointer +0x24, bit buffer +0x30, bit count
// +0x34; ReadBits = 0x011573b0, thiscall, ret 4).  Each block (0x7c bytes of 16-bit coefficients, at
// +0xb8) is described by a pair of 0x18-byte entries at +0x58 whose ushort at +4 indexes two signed
// width tables (0x014ceb10 / 0x014ceb20).  A width of 0 reads nothing and yields 0.
//
// This function fills one block:
//  - If the entry is "split" (+7 != 0 and +8 == 2) either all coefficient groups are read in the
//    short straight-line order (entry +9 == 0) or in the loop order (+9 != 0);
//  - otherwise four groups are read only when the per-block flag byte (table at +0x54, 4 bytes per
//    block starting at +4) is clear or the `refresh` argument is 0.
// Each path ends by zeroing the trailing words of the block.
#include "types.h"

extern const int8_t gWidthA[];  // 0x014ceb10
extern const int8_t gWidthB[];  // 0x014ceb20

struct BlockEntry {
    uint8_t pad0[4];
    uint16_t type;     // +4
    uint8_t pad6;
    uint8_t split;     // +7
    uint8_t kind;      // +8
    uint8_t mode;      // +9
    uint8_t pad_a[14];
};                      // 0x18

struct BitDecoder {
    uint8_t pad0[0x24];
    const uint8_t* mpRead;     // +0x24
    uint32_t pad28[2];
    uint32_t mBuffer;          // +0x30
    int mBitCount;             // +0x34
    uint32_t pad38[7];
    const uint8_t* mpFlags;    // +0x54: 4 bytes per block, starting at +4
    BlockEntry mEntries[1];    // +0x58 (really more)

    uint32_t ReadBits(int n);  // 0x011573b0
    void ReadBlock(int block, int sub);   // 0x011577d0
};

// "width 0 reads nothing" wrapper used all over the decoder.
static __forceinline uint32_t Rd(BitDecoder* d, int n)
{
    uint32_t v;
    if (n == 0)
        v = 0;
    else
        v = d->ReadBits(n);
    return v;
}

void BitDecoder::ReadBlock(int block, int sub)
{
    BlockEntry* e = &mEntries[sub + block * 2];
    int wA = gWidthA[e->type];
    int wB = gWidthB[e->type];
    uint16_t* out = (uint16_t*)((uint8_t*)this + 0xb8 + block * 0x7c);

    if (e->split != 0 && e->kind == 2) {
        if (e->mode != 0) {
            for (int i = 0; i < 8; i++)
                out[i] = Rd(this, wA);
            uint16_t* colA = out + 0x1a;
            for (int c = 3; c != 0; c--) {
                uint16_t* p = colA;
                for (int r = 3; r != 0; r--) {
                    *p = Rd(this, wA);
                    p += 13;
                }
                colA++;
            }
            uint16_t* colB = out + 0x1d;
            for (int c = 6; c != 0; c--) {
                uint16_t* p = colB;
                for (int r = 3; r != 0; r--) {
                    *p = Rd(this, wB);
                    p += 13;
                }
                colB++;
            }
        } else {
            // straight-line: six columns of three words, stride 13 words
            out[0x17] = Rd(this, wA); out[0x24] = Rd(this, wA); out[0x31] = Rd(this, wA);
            out[0x18] = Rd(this, wA); out[0x25] = Rd(this, wA); out[0x32] = Rd(this, wA);
            out[0x19] = Rd(this, wA); out[0x26] = Rd(this, wA); out[0x33] = Rd(this, wA);
            out[0x1a] = Rd(this, wA); out[0x27] = Rd(this, wA); out[0x34] = Rd(this, wA);
            out[0x1b] = Rd(this, wA); out[0x28] = Rd(this, wA); out[0x35] = Rd(this, wA);
            out[0x1c] = Rd(this, wA); out[0x29] = Rd(this, wA); out[0x36] = Rd(this, wA);
            out[0x1d] = Rd(this, wB); out[0x2a] = Rd(this, wB); out[0x37] = Rd(this, wB);
            out[0x1e] = Rd(this, wB); out[0x2b] = Rd(this, wB); out[0x38] = Rd(this, wB);
            out[0x1f] = Rd(this, wB); out[0x2c] = Rd(this, wB); out[0x39] = Rd(this, wB);
            out[0x20] = Rd(this, wB); out[0x2d] = Rd(this, wB); out[0x3a] = Rd(this, wB);
            out[0x21] = Rd(this, wB); out[0x2e] = Rd(this, wB); out[0x3b] = Rd(this, wB);
            out[0x22] = Rd(this, wB); out[0x2f] = Rd(this, wB); out[0x3c] = Rd(this, wB);
        }
        out[0x23] = 0;
        out[0x30] = 0;
        out[0x3d] = 0;
        return;
    }

    const uint8_t* f = mpFlags + 4 + block * 4;
    if (f[0] == 0 || sub == 0) {
        out[0] = Rd(this, wA); out[1] = Rd(this, wA); out[2] = Rd(this, wA);
        out[3] = Rd(this, wA); out[4] = Rd(this, wA); out[5] = Rd(this, wA);
    }
    if (f[1] == 0 || sub == 0) {
        out[6] = Rd(this, wA); out[7] = Rd(this, wA); out[8] = Rd(this, wA);
        out[9] = Rd(this, wA); out[10] = Rd(this, wA);
    }
    if (f[2] == 0 || sub == 0) {
        out[0xb] = Rd(this, wB); out[0xc] = Rd(this, wB); out[0xd] = Rd(this, wB);
        out[0xe] = Rd(this, wB); out[0xf] = Rd(this, wB);
    }
    if (f[3] == 0 || sub == 0) {
        out[0x10] = Rd(this, wB); out[0x11] = Rd(this, wB); out[0x12] = Rd(this, wB);
        out[0x13] = Rd(this, wB); out[0x14] = Rd(this, wB);
    }
    out[0x15] = 0;
    out[0x16] = 0;
}
