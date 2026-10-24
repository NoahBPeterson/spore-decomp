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
    uint16_t type0;    // +0
    uint16_t count;    // +2
    uint16_t type;     // +4 (width-table index)
    uint8_t b6;        // +6
    uint8_t split;     // +7
    uint8_t kind;      // +8
    uint8_t mode;      // +9
    uint8_t b0a;       // +0xa
    uint8_t b0b;       // +0xb
    uint8_t b0c;       // +0xc
    uint8_t b0d;       // +0xd
    uint8_t b0e;       // +0xe
    uint8_t b0f;       // +0xf
    uint8_t b10;       // +0x10
    uint8_t b11;       // +0x11
    uint8_t b12;       // +0x12
    uint8_t b13;       // +0x13
    uint8_t pad14[4];
};                      // 0x18

struct CoefBlock {
    uint16_t mCoef[0x3e];  // 0x7c bytes, indexed in 16-bit words
};

struct TailCodebook {          // 0x014d8e20, 8 bytes per entry
    const uint8_t* mpTable;    // +0
    uint8_t pad4[2];
    uint8_t shift;             // +6
    uint8_t pad7;
};

struct BitDecoder {
    uint8_t pad0[4];
    uint32_t m4;               // +0x4
    uint32_t m8;               // +0x8
    uint32_t mC;               // +0xc
    uint32_t pad10;            // +0x10
    uint8_t pad14[4];          // +0x14
    uint8_t m18;               // +0x18
    uint8_t pad19[0xb];
    const uint8_t* mpRead;     // +0x24
    const uint8_t* mpBegin;    // +0x28
    const uint8_t* mp2c;       // +0x2c
    uint32_t mBuffer;          // +0x30
    int mBitCount;             // +0x34
    uint8_t m38;               // +0x38
    uint8_t m39;               // +0x39
    uint8_t m3a;               // +0x3a
    uint8_t m3b;               // +0x3b
    uint8_t m3c;               // +0x3c
    uint8_t pad3d;
    uint8_t m3e;               // +0x3e
    uint8_t pad3f;
    uint8_t pad40;
    uint8_t m41;               // +0x41
    uint8_t pad42;
    uint8_t m43;               // +0x43
    uint8_t m44;               // +0x44
    uint8_t pad45[2];
    uint8_t m47;               // +0x47
    uint8_t m48;               // +0x48
    uint8_t pad49[7];          // +0x49
    void* mp50;                // +0x50
    const uint8_t* mpFlags;    // +0x54: 4 bytes per block, starting at +4
    BlockEntry mEntries[4];    // +0x58
    CoefBlock mBlocks[2];      // +0xb8
    uint8_t pad1b0[8];
    void* mp1b8;               // +0x1b8

    uint32_t ReadBits(int n);  // 0x011573b0
    void ReadBlock(int block, int sub);   // 0x011577d0

    void FUN_01157de0(int block, int sub, uint8_t* out);
    void FUN_01158000(int block, int sub);
    void FUN_01158160(int block, int sub, float* out, int bits);
    int FUN_011585c0(uint32_t flags);
    int FUN_01158670(const uint8_t* data, int unused);

    __declspec(noinline) void FUN_01168130();   // 0x01168130
    __declspec(noinline) void FUN_011683d0();   // 0x011683d0
    void Refill();
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

// ------------------------------------------------------------------ large-value code paths
// Shared tables of the coefficient / band decoder.
extern const uint8_t gCover[];        // 0x014ceb30: rows of 4 counts, indexed [groupMode + mode*3]
extern const int16_t gThr1[];         // 0x014d6fd2: 30-entry sub-band thresholds, also gThr2 at 0x014d6fd4
extern const int16_t gThr2[];         // 0x014d6fd4
extern const float gScaleTab[];       // 0x014cef8c: scale[0] is at 0x014cef8c, indexed by -band
extern const float gPowTab[];         // 0x014cef90
extern const int16_t* gCodebook[];    // 0x014d8ce0: sign-coded Huffman tables
extern const uint8_t gCodebookSize[]; // 0x014d8d60
extern const TailCodebook gTailCb[];  // 0x014d8e20
extern const uint16_t gTab14d76e8[];  // 0x014d76e8
extern void* (*g_pfnAlloc)(uint32_t); // 0x016f16ec

extern "C" void* __cdecl memset(void*, int, unsigned int);

struct IDecoderVtbl {                  // the vtable used by FUN_01158670
    virtual void v0();
    virtual int v1(uint8_t b);
    virtual void v2();
    virtual void v3();
    virtual void v4();
};

void BitDecoder::FUN_011683d0()
{
    mp2c = mpRead;
    mBuffer = 0;
    mBitCount = 0;
}

void BitDecoder::FUN_01168130()
{
    if (g_pfnAlloc) {
        uint32_t n = m48 * (9 * 128);
        void* p = g_pfnAlloc(n);
        mp50 = p;
        memset(p, 0, n);
    } else {
        uint32_t n = m48 * (9 * 256);
        void* p = g_pfnAlloc(n);
        mp50 = p;
        memset(p, 0, n);
    }
}

__forceinline void BitDecoder::Refill()
{
    while (mBitCount < 24) {
        mBuffer |= (uint32_t)*mpRead++ << (24 - mBitCount);
        mBitCount += 8;
    }
}

// @ 0x01157de0  BitDecoder::FUN_01157de0 -- 45 coefficient bytes of one block -> byte buffer
void BitDecoder::FUN_01157de0(int block, int sub, uint8_t* out)
{
    BlockEntry* e = &mEntries[sub + block * 2];
    uint32_t type = e->type0;
    int mode = 0;
    int groupMode = 0;
    uint32_t bits[4];

    if (e->kind == 2) {
        if (e->mode == 0)
            groupMode = 1;
        else
            groupMode = ((e->mode != 1) - 1) & 2;
    }
    if (!((m44 == 1 || m44 == 3) && block == 1)) {
        if (type < 400) {
            uint32_t q = type >> 4;
            bits[0] = q / 5;
            bits[1] = q % 5;
            e->b13 = 0;
            bits[2] = (type >> 2) & 3;
            bits[3] = type & 3;
            mode = 0;
        } else if (type < 500) {
            uint32_t t = (type - 400) >> 2;
            bits[0] = t / 5;
            bits[1] = t % 5;
            e->b13 = 0;
            bits[2] = type & 3;
            mode = 1;
            bits[3] = 0;
        } else if (type < 512) {
            uint32_t t = type - 500;
            bits[0] = t / 3;
            bits[1] = t % 3;
            bits[2] = 0;
            e->b13 = 1;
            mode = 2;
            bits[3] = 0;
        }
    }
    if ((m44 == 1 || m44 == 3) && block == 1) {
        uint32_t h = type >> 1;
        if (h < 255) {
            if (h < 180) {
                bits[0] = h / 0x24;
                uint32_t r = h % 0x24;
                bits[1] = r / 6;
                bits[2] = r % 6;
                mode = 3;
            } else if (h < 244) {
                bits[0] = ((h + 0xc) >> 4) & 3;
                bits[1] = ((h - 4) >> 2) & 3;
                bits[2] = h & 3;
                mode = 4;
            } else {
                bits[0] = (h - 0xf4) / 3;
                bits[1] = (h - 0xf4) % 3;
                bits[2] = 0;
                mode = 5;
            }
            bits[3] = 0;
            e->b13 = 0;
        }
    }
    memset(out, 0, 0x2d);
    const uint8_t* cover = &gCover[(groupMode + mode * 3) * 4];
    uint32_t n = 0;
    for (uint32_t i = 0; i < 4; i++)
        for (uint32_t k = 0; k < cover[i]; k++) {
            uint32_t v = bits[i];
            if (v != 0)
                v = ReadBits((int)v);
            out[n] = (uint8_t)v;
            n++;
        }
}

// @ 0x01158000  BitDecoder::FUN_01158000 -- spread the 45 bytes over one 0x7c-byte coefficient block
void BitDecoder::FUN_01158000(int block, int sub)
{
    BlockEntry* e = &mEntries[sub + block * 2];
    uint16_t* out = mBlocks[block].mCoef;
    uint8_t buf[0x38];

    FUN_01157de0(block, sub, buf);
    if (e->split != 0 && e->kind == 2) {
        if (e->mode != 0) {
            const uint8_t* s = buf;
            uint16_t* o = out;
            for (uint32_t i = 8; i != 0; i--)
                *o++ = *s++;
            const uint8_t* p = buf + 9;
            uint16_t* d = out + 0x27;
            for (uint32_t k = 9; k != 0; k--) {
                d[-0xd] = p[-1];
                d[0] = p[0];
                d[0xd] = p[1];
                p += 3;
                d++;
            }
        } else {
            const uint8_t* p = buf + 1;
            uint16_t* d = out + 0x24;
            for (uint32_t k = 12; k != 0; k--) {
                d[-0xd] = p[-1];
                d[0] = p[0];
                d[0xd] = p[1];
                p += 3;
                d++;
            }
        }
        uint16_t* z = out + 0x23;
        for (uint32_t k = 3; k != 0; k--) {
            *z = 0;
            z += 0xd;
        }
        return;
    }
    for (uint32_t i = 0; i < 0x15; i++)
        out[i] = buf[i];
    out[0x15] = 0;
    out[0x16] = 0;
}

// @ 0x01158160  BitDecoder::FUN_01158160 -- Huffman band of 16-bit values into a float spectrum
void BitDecoder::FUN_01158160(int block, int sub, float* out, int bits)
{
    BlockEntry* e = &mEntries[sub + block * 2];
    int total = e->type0 + bits;
    int thr1;
    int thr2;

    if (e->split != 0 && e->kind == 2) {
        thr1 = 0x24;
        thr2 = 0x240;
    } else {
        int off = m3c * 30;
        thr1 = gThr1[off + e->b0a];
        thr2 = gThr2[off + e->b0a + e->b0b];
    }
    float scale = gScaleTab[-(int32_t)e->b6];
    float nscale = -scale;
    int n = e->count * 2;
    int j = 0;
    for (; j < n; j += 2) {
        int cb = j < thr1 ? e->b0c : (j < thr2 ? e->b0d : e->b0e);
        int sz = gCodebookSize[cb];
        const int16_t* p = gCodebook[cb];
        if (p == 0) {
            out[j] = 0.0f;
            out[j + 1] = 0.0f;
            continue;
        }
        Refill();
        int v = *p;
        while (v < 0) {
            p++;
            if ((int32_t)mBuffer < 0)
                p -= v;
            mBitCount--;
            mBuffer <<= 1;
            v = *p;
        }
        int v1 = v >> 4;
        int v2 = v & 0xf;
        if (v1 == 0xf) {
            if (sz != 0)
                v1 = (int)ReadBits(sz) + 15;
        }
        if (v1 == 0) {
            out[j] = 0.0f;
        } else {
            float f = gPowTab[v1];
            if ((int32_t)mBuffer < 0)
                out[j] = f * nscale;
            else
                out[j] = f * scale;
            mBitCount--;
            mBuffer <<= 1;
        }
        if (v2 == 0xf && sz != 0)
            v2 = (int)ReadBits(sz) + 15;
        if (v2 == 0) {
            out[j + 1] = 0.0f;
        } else {
            float f = gPowTab[v2];
            if ((int32_t)mBuffer < 0)
                out[j + 1] = f * nscale;
            else
                out[j + 1] = f * scale;
            mBitCount--;
            mBuffer <<= 1;
        }
    }
    const TailCodebook* tc = &gTailCb[e->b0f];
    int32_t used = (int32_t)(mpRead - mpBegin) * 8 - mBitCount;
    float* q = out + j + 2;
    while (used < total) {
        if (j >= 0x240)
            break;
        Refill();
        const uint8_t* c = tc->mpTable + ((mBuffer >> tc->shift) << 1);
        mBitCount -= c[1];
        mBuffer <<= c[1];
        for (int k = 0; k < 4; k++) {
            if (c[0] & (8 >> k)) {
                if ((int32_t)mBuffer < 0)
                    q[k] = nscale;
                else
                    q[k] = scale;
                mBuffer <<= 1;
                mBitCount--;
            } else {
                q[k] = 0.0f;
            }
        }
        j += 4;
        q += 4;
        used = (int32_t)(mpRead - mpBegin) * 8 - mBitCount;
    }
    if (used > total) {
        uint32_t back = used + (mBitCount - total);
        mpRead -= back >> 3;
        mBitCount = back & 7;
        if (mBitCount != 0)
            mBuffer = (uint32_t)*(mpRead - 1) << (32 - mBitCount);
        j -= 4;
    }
    used = (int32_t)(mpRead - mpBegin) * 8 - mBitCount;
    if (used < total)
        ReadBits(total - used);
    if (j < 0x240)
        memset(out + j, 0, (0x240 - j) * 4);
}

// @ 0x011585c0  BitDecoder::FUN_011585c0 -- block-type / channel setup from a 16-bit mode word
int BitDecoder::FUN_011585c0(uint32_t flags)
{
    uint32_t x = (flags >> 6) & 3;
    uint32_t z = (flags >> 4) & 3;
    uint8_t y = (uint8_t)((flags >> 2) & 3);

    m44 = (uint8_t)flags & 3;
    m3e = x & 1;
    uint8_t nz = (uint8_t)(x != 3);
    bool zero = x == 0;
    m43 = y;
    m18 = 3;
    m3b = nz;
    m3a = zero;
    if (zero) {
        m41 = (uint8_t)(z + 6);
        m3c = (uint8_t)(z + 6);
    } else {
        m41 = (uint8_t)(z + nz * 3);
        m3c = (uint8_t)(z + (-nz & 3));
    }
    m48 = (uint8_t)((y != 3) + 1);
    uint16_t v = gTab14d76e8[m41];
    m8 = v;
    m4 = v;
    return 0;
}

// @ 0x01158670  BitDecoder::FUN_01158670 -- start decoding a new bit-stream
int BitDecoder::FUN_01158670(const uint8_t* data, int unused)
{
    if (m47 != 0)
        ((IDecoderVtbl*)this)->v3();
    m47 = 1;
    mpRead = data;
    mpBegin = data;
    int r = ((IDecoderVtbl*)this)->v1(data[0]);
    if (r == -1)
        return r;
    FUN_01168130();
    if (mp1b8 == 0) {
        uint32_t n = m48 * 0x900;
        mC = n;
        mp1b8 = g_pfnAlloc(n);
    }
    m38 = 1;
    m39 = 1;
    FUN_011683d0();
    return 0;
}
