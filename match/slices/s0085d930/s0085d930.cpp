// Slice s0085d930 -- 0x85xxxx region (allocator/streaming helpers).
//
// Frozen batch gold5.  32-bit x86, MSVC 2008 SP1, flags /O2 /MD /Gy /TP
// /arch:SSE /fp:fast (default /GS on).

typedef unsigned int  uint;
typedef unsigned char byte;
typedef unsigned short wchar16;

typedef void* (__cdecl *ALLOC_FN)(int, int, int);
#define ALLOCATOR(p) (*(ALLOC_FN*)(*(int*)((char*)(p) + 4)))

void FUN_0085e2d0();

// @ 0x0085e5c0 -- FUN_0085e5c0
// Allocates the 0x40-byte vtable-ish object (installing FUN_0085e2d0 as its
// first entry) plus a (count << 8) table of 0xffffffff words.
void __cdecl FUN_0085e5c0(int param_1) {
    int* puVar1 = (int*)ALLOCATOR(param_1)(param_1, 1, 0x40);
    *(int*)(param_1 + 0x5bc) = (int)puVar1;
    puVar1[0] = (int)FUN_0085e2d0;
    puVar1[0xb] = 0;
    puVar1[0xc] = 0;
    puVar1[0xd] = 0;
    puVar1[0xe] = 0;
    int iVar3 = 0;
    int iVar6 = (int)ALLOCATOR(param_1)(param_1, 1, *(int*)(param_1 + 0x20) << 8);
    *(int*)(param_1 + 0xa0) = iVar6;
    int* puVar2 = (int*)iVar6;
    if (0 < *(int*)(param_1 + 0x20)) {
        do {
            iVar3 = iVar3 + 1;
            int* puVar4 = puVar2;
            for (int iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1) {
                *puVar4 = 0xffffffff;
                puVar4 = puVar4 + 1;
            }
            puVar2 = puVar2 + 0x40;
        } while (iVar3 < *(int*)(param_1 + 0x20));
    }
}

// @ 0x0085e630 -- FUN_0085e630
// Clamps the request to the buffer capacity, decodes up to that many elements
// through the codec at +0x5c4 and copies the result through the sink at +0x5cc.
void __cdecl FUN_0085e630(int param_1, int param_2, int param_3, int param_4, int param_5,
                          int* param_6, int param_7) {
    int* piVar4 = param_6;
    int iVar3 = param_1;
    int iVar2 = *(int*)(param_1 + 0x5b0);
    uint uVar5 = param_7 - *param_6;
    if (uVar5 > *(uint*)(iVar2 + 0x10)) {
        uVar5 = *(uint*)(iVar2 + 0x10);
    }
    int local = 0;
    (*(void(__cdecl**)(int, int, int, int, int, int*, uint))(*(int*)(param_1 + 0x5c4) + 4))(
        iVar3, param_2, param_3, param_4, *(int*)(iVar2 + 0xc), &local, uVar5);
    (*(void(__cdecl**)(int, int, int, int))(*(int*)(iVar3 + 0x5cc) + 4))(
        iVar3, *(int*)(iVar2 + 0xc), param_5 + *piVar4 * 4, local);
    *piVar4 = *piVar4 + local;
}

// @ 0x0085e6b0 -- FUN_0085e6b0
// Decodes into the sink buffer, zero-fills the gap the decoder left behind and
// recycles the buffer once it is full.
void __cdecl FUN_0085e6b0(int param_1, int param_2, int param_3, int param_4, int param_5,
                          int* param_6) {
    int iVar2 = *(int*)(param_1 + 0x5b0);
    uint* puVar1 = (uint*)(iVar2 + 0x18);
    if (*(int*)(iVar2 + 0x18) == 0) {
        int uVar4 = (*(int(__cdecl**)(int, int, int, int, int))(*(int*)(param_1 + 4) + 0x1c))(
            param_1, *(int*)(iVar2 + 8), *(int*)(iVar2 + 0x14), *(int*)(iVar2 + 0x10), 1);
        *(int*)(iVar2 + 0xc) = uVar4;
    }
    uint uVar3 = *puVar1;
    (*(void(__cdecl**)(int, int, int, int, int, uint*, int))(*(int*)(param_1 + 0x5c4) + 4))(
        param_1, param_2, param_3, param_4, *(int*)(iVar2 + 0xc), puVar1, *(int*)(iVar2 + 0x10));
    if (*puVar1 > uVar3) {
        int iVar5 = *puVar1 - uVar3;
        (*(void(__cdecl**)(int, int, int, int))(*(int*)(param_1 + 0x5cc) + 4))(
            param_1, *(int*)(iVar2 + 0xc) + uVar3 * 4, 0, iVar5);
        *param_6 = *param_6 + iVar5;
    }
    if (*puVar1 >= *(uint*)(iVar2 + 0x10)) {
        *(int*)(iVar2 + 0x14) = *(int*)(iVar2 + 0x14) + *(uint*)(iVar2 + 0x10);
        *puVar1 = 0;
    }
}

// @ 0x0085e760 -- FUN_0085e760
// Copies as many buffered elements as both the ring and the caller's remaining
// count allow through the sink at +0x5cc, then advances and recycles the ring.
void __cdecl FUN_0085e760(int param_1, int param_2, int param_3, int param_4, int param_5,
                          int* param_6, int param_7) {
    int iVar1 = *(int*)(param_1 + 0x5b0);
    if (*(int*)(iVar1 + 0x18) == 0) {
        int uVar2 = (*(int(__cdecl**)(int, int, int, int, int))(*(int*)(param_1 + 4) + 0x1c))(
            param_1, *(int*)(iVar1 + 8), *(int*)(iVar1 + 0x14), *(int*)(iVar1 + 0x10), 0);
        *(int*)(iVar1 + 0xc) = uVar2;
    }
    uint uVar4 = *(int*)(iVar1 + 0x10) - *(int*)(iVar1 + 0x18);
    uint uVar3 = param_7 - *param_6;
    if (uVar4 > uVar3) {
        uVar4 = uVar3;
    }
    uVar3 = *(int*)(param_1 + 0x74) - *(int*)(iVar1 + 0x14);
    if (uVar4 > uVar3) {
        uVar4 = uVar3;
    }
    (*(void(__cdecl**)(int, int, int, uint))(*(int*)(param_1 + 0x5cc) + 4))(
        param_1, *(int*)(iVar1 + 0xc) + *(int*)(iVar1 + 0x18) * 4, param_5 + *param_6 * 4, uVar4);
    *param_6 = *param_6 + uVar4;
    *(int*)(iVar1 + 0x18) = *(int*)(iVar1 + 0x18) + uVar4;
    if (*(uint*)(iVar1 + 0x18) >= *(uint*)(iVar1 + 0x10)) {
        *(int*)(iVar1 + 0x14) = *(int*)(iVar1 + 0x14) + *(uint*)(iVar1 + 0x10);
        *(int*)(iVar1 + 0x18) = 0;
    }
}

// ===========================================================================
// Shared layouts for the stream/decode drivers in this slice.
//
// StreamCtx  - the decoder object whose address is param_1 of every driver
// StreamDesc - decoded-stream descriptor stored at StreamCtx.mpDesc (+0x5bc)
// StreamState - ring/bit state stored at StreamCtx.mpStream (+0x5b0)
// BitReader  - scratch block handed to the bit-refill helper FUN_00859bb0
// ===========================================================================
struct StreamDesc {                  // Ctx.mpDesc
    char  _pad00[0x04];
    void* mpfnDecode;                // +0x04  decoder entry installed per stream
    int  mBitBuf;                    // +0x08  pending bit accumulator
    int  mBitCount;                  // +0x0c  bits available in mBitBuf
    int  mField10;                   // +0x10  (handed to the bit-refill helper)
    int  mRepeat;                    // +0x14  remaining run-length repeats
    int  mAcc0;                      // +0x18  per-channel delta accumulator 0
    int  mAcc1;                      // +0x1c  per-channel delta accumulator 1
    int  mAcc2;                      // +0x20  per-channel delta accumulator 2
    int  mAcc3;                      // +0x24  per-channel delta accumulator 3
    int  mPending;                   // +0x28  remaining elements for this pass
    int** mppTables;                 // +0x2c  huffman decode table per stream
};

struct StreamState {                 // Ctx.mpStream
    char _pad00[0x08];
    int  mField08;                   // +0x08
    int  mpBuffer;                   // +0x0c  element buffer
    int  mCapacity;                  // +0x10  elements per buffer slot
    int  mBase;                      // +0x14  ring base offset
    int  mCount;                     // +0x18  elements currently buffered
};

struct StreamObject {                // entry of Ctx.mpStreamTab (+0x54c)
    char _pad00[0x04];
    int  mIndex;                     // +0x04  sample-table slot index
    char _pad08[0x14 - 0x08];
    int  mField14;                   // +0x14  decode mode (plain streams)
    int  mField18;                   // +0x18  decode mode (interlaced streams)
};

struct StreamInner {                 // object at Ctx.mpInner (+0x00)
    void* mpfnError;                 // +0x00  called as (int ctx)
    void* mpNotify;                  // +0x04  called as (int ctx, int code)
    char  _pad08[0x14 - 0x08];
    int   mErrorCode;                // +0x14
    int   mField18;                  // +0x18  error argument 0
    int   mField1c;                  // +0x1c  error argument 1
    int   mField20;                  // +0x20  error argument 2
    int   mField24;                  // +0x24  error argument 3
};

struct StreamCtx {
    StreamInner* mpInner;            // +0x00  error/report sub-object
    void*        mpVtbl;             // +0x04
    char         _pad08[0x14 - 0x08];
    int*         mpSrcPair;          // +0x14  { mSrcLo, mSrcHi }
    char         _pad18[0x20 - 0x18];
    int          mCapacity;          // +0x20
    char         _pad24[0x74 - 0x24];
    int          mField74;           // +0x74
    char         _pad78[0xa0 - 0x78];
    int*         mpSampleTable;      // +0xa0  0x100-byte sample/predictor slots
    void**       mpTablesB4;         // +0xb4  per-mode tables (plain streams)
    void**       mpTablesC4;         // +0xc4  per-mode tables (interlaced streams)
    char         _padc8[0x114 - 0xc8];
    int          mField114;          // +0x114
    char         _pad118[0x548 - 0x118];
    int          mChannelCount;      // +0x548  number of streams
    void**       mpStreamTab;        // +0x54c  per-channel stream objects
    char         _pad550[0x564 - 0x550];
    int          mElemCount;         // +0x564
    int*         mChannelIds;        // +0x568  per-output channel index
    char         _pad56c[0x590 - 0x56c];
    int          mField590;          // +0x590
    int          mField594;          // +0x594
    int          mField598;          // +0x598
    int          mBitIndex;          // +0x59c
    int          mSrcState;          // +0x5a0
    char         _pad5a4[0x5b0 - 0x5a4];
    StreamState* mpStream;           // +0x5b0
    char         _pad5b4[0x5bc - 0x5b4];
    StreamDesc*  mpDesc;             // +0x5bc
    void*        mpDecoder;          // +0x5c4
    void*        mpSink;             // +0x5cc
};

struct BitReader {                   // scratch block passed to FUN_00859bb0
    int        mSrc0;                // +0x00
    int        mSrc1;                // +0x04
    int        mSrc2;                // +0x08
    int        mBitBuf;              // +0x0c  out
    int        mBitCount;            // +0x10  out
    StreamCtx* mpCtx;                // +0x14  back-reference
    void*      mpField18;            // +0x18  &StreamDesc::mField10
};

extern "C" int FUN_0085d8b0(void);                                   // 0x0085d8b0
extern "C" int FUN_00859bb0(BitReader* st, int buf, int count, int mode);  // 0x00859bb0

// ===========================================================================
// @ 0x0085ddd0  read one bit per output element into the caller's bit array
// ===========================================================================
int __cdecl FUN_0085ddd0(int param_1, int param_2)
{
    StreamCtx*  ctx  = (StreamCtx*)param_1;
    int*        outs = (int*)param_2;

    const int   shift = ctx->mBitIndex;
    StreamDesc* desc  = ctx->mpDesc;

    if (ctx->mField114 != 0 && desc->mPending == 0 && FUN_0085d8b0() == 0)
        return 0;

    BitReader st;
    st.mSrc0 = ctx->mpSrcPair[0];
    st.mSrc1 = ctx->mpSrcPair[1];
    st.mSrc2 = ctx->mSrcState;
    st.mpCtx = ctx;
    st.mpField18 = &desc->mField10;

    int buf   = desc->mBitBuf;
    int count = desc->mBitCount;
    const wchar16 mask = (wchar16)(1 << (shift & 0x1f));

    for (int i = 0; i < ctx->mElemCount; ++i) {
        wchar16* out = (wchar16*)outs[i];
        if (count < 1) {
            if (FUN_00859bb0(&st, buf, count, 1) == 0)
                return 0;
            buf   = st.mBitBuf;
            count = st.mBitCount;
        }
        count -= 1;
        if ((buf >> (count & 0x1f)) & 1)
            *out |= mask;
    }

    ctx->mpSrcPair[0] = st.mSrc0;
    ctx->mpSrcPair[1] = st.mSrc1;
    ctx->mSrcState    = st.mSrc2;
    desc->mPending   -= 1;
    desc->mBitBuf     = buf;
    desc->mBitCount   = count;
    return 1;
}

extern "C" int FUN_00859cc0(BitReader* st, int buf, int count, int table, unsigned sym);  // 0x00859cc0

// Huffman decode tables used by the run-length symbol decoder.
extern "C" const int gHuffLimit_141d308[];    // 0x0141d308  per-length escape threshold
extern "C" const int gHuffOffset_141d348[];   // 0x0141d348  per-length escape base
extern "C" const int gOutMap_141e880[];       // 0x0141e880  output index per decoded position

// ===========================================================================
// @ 0x0085db80  run-length symbol decoder (writes short values into *param_2)
// ===========================================================================
int __cdecl FUN_0085db80(int param_1, int* param_2)
{
    StreamCtx*  ctx  = (StreamCtx*)param_1;
    StreamDesc* desc = ctx->mpDesc;

    const int limit = ctx->mField594;
    const int shift = ctx->mBitIndex;

    if (ctx->mField114 != 0 && desc->mPending == 0 && FUN_0085d8b0() == 0)
        return 0;

    if (desc->mRepeat != 0) {                  // still inside a run
        desc->mPending -= 1;
        desc->mRepeat  -= 1;
        return 1;
    }

    int idx = ctx->mField590;

    BitReader st;
    st.mSrc0     = ctx->mpSrcPair[0];
    st.mSrc1     = ctx->mpSrcPair[1];
    st.mSrc2     = ctx->mSrcState;
    st.mpCtx     = ctx;
    st.mpField18 = &desc->mField10;

    int             bitBuf   = desc->mBitBuf;
    int             bitCount = desc->mBitCount;
    int*            table    = (int*)desc->mppTables[4];  // descriptor table set, slot 4 (desc+0x3c)
    unsigned char*  bytes    = (unsigned char*)table;
    short*          outBase  = (short*)(size_t)*param_2;
    int             run      = 0;

    for (;;) {
        if (limit < idx)
            break;

        unsigned sym;
        if (bitCount < 8) {
            if (FUN_00859bb0(&st, bitBuf, bitCount, 0) == 0)
                return 0;
            bitCount = st.mBitCount;
            bitBuf   = st.mBitBuf;
        }
        if (bitCount < 8) {
            sym = (unsigned)FUN_00859cc0(&st, bitBuf, bitCount, (int)(size_t)table, 1);
            bitCount = st.mBitCount;
            bitBuf   = st.mBitBuf;
            if ((int)sym < 0)
                return 0;
        } else {
            unsigned v = (unsigned)(bitBuf >> ((bitCount - 8) & 0x1f)) & 0xff;
            int n = table[0x35 + v];                      // table[0xd4/4 + v]
            if (n == 0) {
                sym = (unsigned)FUN_00859cc0(&st, bitBuf, bitCount, (int)(size_t)table, 9);
                bitCount = st.mBitCount;
                bitBuf   = st.mBitBuf;
                if ((int)sym < 0)
                    return 0;
            } else {
                sym = bytes[0x4d4 + v];
                bitCount -= n;
            }
        }

        int      hi = (int)sym >> 4;
        unsigned lo = sym & 0xfu;

        if (lo == 0) {
            if (hi == 0xf) {                              // long zero run
                idx += 0xf;
                if (++idx > limit)
                    break;
                continue;
            }
            run = 1 << (hi & 0x1f);
            if (hi != 0) {
                if (bitCount < hi) {
                    if (FUN_00859bb0(&st, bitBuf, bitCount, hi) == 0)
                        return 0;
                    bitCount = st.mBitCount;
                    bitBuf   = st.mBitBuf;
                }
                bitCount -= hi;
                run += (bitBuf >> (bitCount & 0x1f)) & (run - 1);
            }
            run -= 1;
            break;
        }

        idx += hi;
        if (bitCount < (int)lo) {
            if (FUN_00859bb0(&st, bitBuf, bitCount, (int)lo) == 0)
                return 0;
            bitCount = st.mBitCount;
            bitBuf   = st.mBitBuf;
        }
        bitCount -= (int)lo;
        unsigned val = ((1u << lo) - 1u) & (unsigned)(bitBuf >> (bitCount & 0x1f));
        if ((int)val < gHuffLimit_141d308[lo])
            val = (unsigned)(gHuffOffset_141d348[lo] + (int)val);
        outBase[gOutMap_141e880[idx]] = (short)(val << (shift & 0x1f));
        if (++idx > limit)
            break;
    }

    ctx->mpSrcPair[0] = st.mSrc0;
    ctx->mpSrcPair[1] = st.mSrc1;
    ctx->mSrcState    = st.mSrc2;
    desc->mPending   -= 1;
    desc->mBitBuf     = bitBuf;
    desc->mBitCount   = bitCount;
    desc->mRepeat     = run;
    return 1;
}

// ===========================================================================
// @ 0x0085d930  per-channel delta decoder (channel id per output element)
// ===========================================================================
int __cdecl FUN_0085d930(int param_1, int param_2)
{
    StreamCtx*  ctx  = (StreamCtx*)param_1;
    StreamDesc* desc = ctx->mpDesc;

    const int shift = ctx->mBitIndex;

    if (ctx->mField114 != 0 && desc->mPending == 0 && FUN_0085d8b0() == 0)
        return 0;

    BitReader st;
    st.mSrc0     = ctx->mpSrcPair[0];
    st.mSrc1     = ctx->mpSrcPair[1];
    st.mSrc2     = ctx->mSrcState;
    st.mpCtx     = ctx;
    st.mpField18 = &desc->mField10;

    int bitCount = desc->mBitCount;
    int bitBuf   = desc->mBitBuf;
    const int savedRepeat = desc->mRepeat;

    int acc[4];
    acc[0] = desc->mAcc0;
    acc[1] = desc->mAcc1;
    acc[2] = desc->mAcc2;
    acc[3] = desc->mAcc3;

    const int elemCount = ctx->mElemCount;
    for (int i = 0; i < elemCount; ++i) {
        short* out = (short*)(size_t)((int*)param_2)[i];
        int    ch  = ctx->mChannelIds[i];                       // ctx+0x568
        int*   stream = (int*)ctx->mpStreamTab[ch];             // ctx+0x54c
        int*   table  = (int*)desc->mppTables[stream[5]];       // desc+0x2c + idx*4

        unsigned sym;
        if (bitCount < 8) {
            if (FUN_00859bb0(&st, bitBuf, bitCount, 0) == 0)
                return 0;
            bitCount = st.mBitCount;
            bitBuf   = st.mBitBuf;
        }
        if (bitCount < 8) {
            sym = (unsigned)FUN_00859cc0(&st, bitBuf, bitCount, (int)(size_t)table, 1);
            bitCount = st.mBitCount;
            bitBuf   = st.mBitBuf;
            if ((int)sym < 0)
                return 0;
        } else {
            unsigned v = (unsigned)(bitBuf >> ((bitCount - 8) & 0x1f)) & 0xff;
            int n = table[0x35 + v];
            if (n == 0) {
                sym = (unsigned)FUN_00859cc0(&st, bitBuf, bitCount, (int)(size_t)table, 9);
                bitCount = st.mBitCount;
                bitBuf   = st.mBitBuf;
                if ((int)sym < 0)
                    return 0;
            } else {
                sym = ((unsigned char*)table)[0x4d4 + v];
                bitCount -= n;
            }
        }

        unsigned delta = 0;
        if (sym != 0) {
            if (bitCount < (int)sym) {
                if (FUN_00859bb0(&st, bitBuf, bitCount, (int)sym) == 0)
                    return 0;
                bitCount = st.mBitCount;
                bitBuf   = st.mBitBuf;
            }
            bitCount -= (int)sym;
            delta = ((1u << sym) - 1u) & (unsigned)(bitBuf >> (bitCount & 0x1f));
            if ((int)delta < gHuffLimit_141d308[sym])
                delta = (unsigned)(gHuffOffset_141d348[sym] + (int)delta);
        }

        acc[ch] += (int)delta;
        *out = (short)(acc[ch] << (shift & 0x1f));
    }

    ctx->mpSrcPair[0] = st.mSrc0;
    ctx->mpSrcPair[1] = st.mSrc1;
    ctx->mSrcState    = st.mSrc2;
    desc->mPending   -= 1;
    desc->mBitCount   = bitCount;
    desc->mRepeat     = savedRepeat;
    desc->mAcc0       = acc[0];
    desc->mBitBuf     = bitBuf;
    desc->mAcc1       = acc[1];
    desc->mAcc2       = acc[2];
    desc->mAcc3       = acc[3];
    return 1;
}

// ===========================================================================
// @ 0x0085ded0  interlaced / progressive row decoder (multi-pass filter)
// ===========================================================================
int __cdecl FUN_0085ded0(int param_1, int* param_2)
{
    StreamCtx*  ctx  = (StreamCtx*)param_1;
    StreamDesc* desc = ctx->mpDesc;

    const int      limit    = ctx->mField594;
    const unsigned mask     = 1u << (ctx->mBitIndex & 0x1f);
    const unsigned signMask = (unsigned)(-(int)mask);

    if (ctx->mField114 != 0 && desc->mPending == 0 && FUN_0085d8b0() == 0)
        return 0;

    BitReader st;
    st.mSrc0     = ctx->mpSrcPair[0];
    st.mSrc1     = ctx->mpSrcPair[1];
    st.mSrc2     = ctx->mSrcState;
    st.mpCtx     = ctx;
    st.mpField18 = &desc->mField10;

    int    bitBuf   = desc->mBitBuf;
    int    bitCount = desc->mBitCount;
    short* outBase  = (short*)(size_t)*param_2;
    int*   table    = (int*)desc->mppTables[4];   // +0x3c

    int pass   = desc->mRepeat;                   // +0x14  remaining passes
    int idx    = ctx->mField590;
    int nFixed = 0;
    int fixed[65];

    unsigned delta;
    int      run;

    if (pass != 0)
        goto filterPass;

    for (; idx <= limit; ++idx) {
        unsigned sym;
        if (bitCount < 8) {
            if (FUN_00859bb0(&st, bitBuf, bitCount, 0) == 0)
                goto fail;
            bitCount = st.mBitCount;
            bitBuf   = st.mBitBuf;
        }
        if (bitCount < 8) {
            sym = (unsigned)FUN_00859cc0(&st, bitBuf, bitCount, (int)(size_t)table, 1);
            bitCount = st.mBitCount;
            bitBuf   = st.mBitBuf;
            if ((int)sym < 0)
                goto fail;
        } else {
            unsigned v = (unsigned)(bitBuf >> ((bitCount - 8) & 0x1f)) & 0xff;
            int n = table[0x35 + v];
            if (n == 0) {
                sym = (unsigned)FUN_00859cc0(&st, bitBuf, bitCount, (int)(size_t)table, 9);
                bitCount = st.mBitCount;
                bitBuf   = st.mBitBuf;
                if ((int)sym < 0)
                    goto fail;
            } else {
                sym = ((unsigned char*)table)[0x4d4 + v];
                bitCount -= n;
            }
        }

        run   = (int)sym >> 4;
        delta = 0;
        if ((sym & 0xfu) == 0) {
            if (run != 0xf) {                     // start of a filtered pass
                pass = 1 << (run & 0x1f);
                if (run == 0)
                    goto filterPass;
                if (bitCount < run) {
                    if (FUN_00859bb0(&st, bitBuf, bitCount, run) == 0)
                        goto fail;
                    bitCount = st.mBitCount;
                    bitBuf   = st.mBitBuf;
                }
                bitCount -= run;
                pass += (bitBuf >> (bitCount & 0x1f)) & (pass - 1);
                goto filterPass;
            }
            // run == 0xf: plain zero run, falls through with delta == 0
        } else {
            if ((sym & 0xfu) != 1) {              // corrupt stream
                StreamInner* inner = ctx->mpInner;
                inner->mErrorCode = 0x72;
                (*(void(__cdecl**)(int, int))(&inner->mpNotify))(param_1, -1);
            }
            if (bitCount < 1) {
                if (FUN_00859bb0(&st, bitBuf, bitCount, 1) == 0)
                    goto fail;
                bitCount = st.mBitCount;
                bitBuf   = st.mBitBuf;
            }
            bitCount -= 1;
            delta = ((bitBuf >> (bitCount & 0x1f)) & 1) ? mask : signMask;
        }

        do {
            short* p = outBase + gOutMap_141e880[idx];
            if (*p == 0) {
                if (--run < 0)
                    break;
            } else {
                if (bitCount < 1) {
                    if (FUN_00859bb0(&st, bitBuf, bitCount, 1) == 0)
                        goto fail;
                    bitCount = st.mBitCount;
                    bitBuf   = st.mBitBuf;
                }
                bitCount -= 1;
                if (((bitBuf >> (bitCount & 0x1f)) & 1) && (mask & (unsigned)*p) == 0) {
                    if (*p < 0)
                        *p = (short)(*p + (short)signMask);
                    else
                        *p = (short)(*p + (short)mask);
                }
            }
            ++idx;
        } while (idx <= limit);

        if (delta != 0) {
            int slot = gOutMap_141e880[idx];
            outBase[slot] = (short)delta;
            fixed[nFixed++] = slot;
        }
    }
    goto done;

filterPass:
    if (pass != 0) {
        for (; idx <= limit; ++idx) {
            short* p = outBase + gOutMap_141e880[idx];
            if (*p != 0) {
                if (bitCount < 1) {
                    if (FUN_00859bb0(&st, bitBuf, bitCount, 1) == 0)
                        goto fail;
                    bitCount = st.mBitCount;
                    bitBuf   = st.mBitBuf;
                }
                bitCount -= 1;
                if (((bitBuf >> (bitCount & 0x1f)) & 1) && (mask & (unsigned)*p) == 0) {
                    unsigned d = ((int)*p < 0) ? signMask : mask;
                    *p = (short)(*p + (short)d);
                }
            }
        }
        pass -= 1;
    }

done:
    ctx->mpSrcPair[0] = st.mSrc0;
    ctx->mpSrcPair[1] = st.mSrc1;
    ctx->mSrcState    = st.mSrc2;
    desc->mPending   -= 1;
    desc->mBitCount   = bitCount;
    desc->mBitBuf     = bitBuf;
    desc->mRepeat     = pass;
    return 1;

fail:
    for (; 0 < nFixed; --nFixed)
        outBase[fixed[nFixed]] = 0;
    return 0;
}

extern "C" void FUN_008599f0(int param_1, int table, void* out);  // 0x008599f0

// ===========================================================================
// @ 0x0085e2d0  stream setup / validation: checks the geometry fields,
// reports mismatches to Ctx.mpInner, installs the right decoder entry at
// StreamDesc.mpfnDecode (+0x04), prepares the per-stream tables and clears
// the bit state.
// ===========================================================================
void __cdecl FUN_0085e2d0(int param_1)
{
    StreamCtx*  ctx  = (StreamCtx*)param_1;
    StreamDesc* desc = ctx->mpDesc;
    StreamInner* inner = ctx->mpInner;

    const bool interlaced = ctx->mField590 != 0;
    bool bad = false;
    bool ok;

    if (interlaced) {
        if (ctx->mField594 < ctx->mField590 || 0x3f < ctx->mField594)
            bad = true;
        ok = ctx->mChannelCount == 1;
    } else {
        ok = ctx->mField594 == 0;
    }
    if (!ok)
        bad = true;
    if (ctx->mField598 != 0 && ctx->mBitIndex != ctx->mField598 - 1)
        bad = true;

    if (0xd < ctx->mBitIndex || bad) {
        inner->mErrorCode = 0xe;
        inner->mField18 = ctx->mField590;
        inner->mField1c = ctx->mField594;
        inner->mField20 = ctx->mField598;
        inner->mField24 = ctx->mBitIndex;
        (*(void(__cdecl**)(int))inner)((int)(size_t)param_1);
    }

    const int count = ctx->mChannelCount;
    if (0 < count) {
        void** ppStream = ctx->mpStreamTab;
        for (int i = 0; i < count; ++i) {
            StreamObject* stream = (StreamObject*)ppStream[i];
            const int slot = stream->mIndex;
            int* piVal = (int*)((char*)ctx->mpSampleTable + slot * 0x100);
            if (interlaced && *piVal < 0) {
                inner->mErrorCode = 0x6f;
                inner->mField18 = slot;
                inner->mField1c = 0;
                ((void(__cdecl*)(int, int))inner->mpNotify)((int)(size_t)param_1, -1);
            }
            int idx = ctx->mField590;
            if (idx <= ctx->mField594) {
                do {
                    const int val = piVal[idx];
                    if (ctx->mField598 != (val & ((val < 0) - 1))) {
                        inner->mErrorCode = 0x6f;
                        inner->mField18 = slot;
                        inner->mField1c = idx;
                        ((void(__cdecl*)(int, int))inner->mpNotify)((int)(size_t)param_1, -1);
                    }
                    piVal[idx] = ctx->mBitIndex;
                    ++idx;
                } while (idx <= ctx->mField594);
            }
        }
    }

    if (ctx->mField598 == 0) {
        if (interlaced)
            desc->mpfnDecode = (void*)&FUN_0085db80;
        else
            desc->mpfnDecode = (void*)&FUN_0085d930;
    } else if (interlaced) {
        desc->mpfnDecode = (void*)&FUN_0085ded0;
    } else {
        desc->mpfnDecode = (void*)&FUN_0085ddd0;
    }

    if (0 < count) {
        int*  puStack = &desc->mAcc0;              // desc+0x18
        void** ppStream = ctx->mpStreamTab;
        for (int i = 0; i < count; ++i) {
            StreamObject* stream = (StreamObject*)ppStream[i];
            if (interlaced) {
                const unsigned mode = (unsigned)stream->mField18;
                if (3 < mode || ctx->mpTablesC4[mode] == 0) {
                    inner->mErrorCode = 0x31;
                    inner->mField18 = (int)mode;
                    (*(void(__cdecl**)(int))inner)((int)(size_t)param_1);
                }
                int** slot = &desc->mppTables[mode];
                FUN_008599f0((int)(size_t)param_1, (int)(size_t)ctx->mpTablesC4[mode], slot);
                desc->mppTables[4] = *slot;
            } else if (ctx->mField598 == 0) {
                const unsigned mode = (unsigned)stream->mField14;
                if (3 < mode || ctx->mpTablesB4[mode] == 0) {
                    inner->mErrorCode = 0x31;
                    inner->mField18 = (int)mode;
                    (*(void(__cdecl**)(int))inner)((int)(size_t)param_1);
                }
                FUN_008599f0((int)(size_t)param_1, (int)(size_t)ctx->mpTablesB4[mode], &desc->mppTables[mode]);
            }
            *puStack = 0;
            ++puStack;
        }
    }

    desc->mBitCount = 0;
    desc->mBitBuf   = 0;
    desc->mField10  = 0;
    desc->mRepeat   = 0;
    desc->mPending  = ctx->mField114;
}
