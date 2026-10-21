// Slice s011586f0 (0x011586f0 - 0x011595f0): EATech subband / requantizer decoder.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
// The class embeds an MSB-first bit-stream reader and the two 0x900-byte scratch
// spectra the requantizer chain runs over. Member names are descriptive; every
// offset is read off the disassembly.
//
//   0x011586f0  decode one block frame into `dst`
//   0x01158880  multi-band variant (up to mBands bands)
//   0x01158a80  frame entry: aligns to 8 bits, dispatches on mBands
//   0x01158ad0  scalar deleting destructor
//   0x01158b10  grow a 4-byte-stride scratch allocation
//   0x01158b90  find a registered stream index by handle
//   0x01158be0  x87 scale-accumulate, 4-wide unrolled
//   0x01158c60  SSE scale-accumulate, 4-wide unrolled
//   0x01158d00  int16 -> float conversion, 8-wide unrolled
//   0x01158d80  windowed sample reconstruction (EAX=src, EDX=offset)
//   0x01159030  flush the bit-allocation scratch
//   0x01159130  bits consumed per sample (allocation walk)
//   0x011592c0  bits consumed per sample, streaming variant
//   0x011594e0  set a float scale field from a sample count
//   0x01159500  decode one packet
//   0x011595f0  free the scratch allocation

#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed   short i16;

// 0x18-byte per-band descriptor at this+0x58.
struct BlockEntry {
    u8     pad0[4];
    u16    type;   // +4
    u8     pad6;
    u8     split;  // +7
    u8     kind;   // +8
    u8     mode;   // +9
    u8     pad_a[14];
};

// this+0x838: an eastl-shaped vector of 4-byte elements (begin/end/capacity).
struct ScratchVec {
    u32* begin;     // +0x00
    u32* end;       // +0x04
    u32* capacity;  // +0x08
};

class CSubbandDecoder {
public:
    void*       vftable;       // +0x00
    u8          pad04[0x14 - 0x04];
    int         mPos;          // +0x14 (bits used >> 3)
    u8          pad18[0x1c - 0x18];
    const u8*   mpQuantTable;  // +0x1c
    int         mAllocMode;    // +0x20
    union {
        struct { const u8* mpRead; const u8* mpStart; };   // +0x24 / +0x28 (bit reader)
        struct { float mScaleA; float mScaleB; };          // +0x24 / +0x28 (requantizer)
    };
    int         mBlockSize;    // +0x2c
    int         mBitsLeft;     // +0x30
    int         mBitCount;     // +0x34
    int         mField38;      // +0x38
    union {
        struct { u16 mField3cLo; u8 mInterleave; u8 pad3f0; };
        int mField3c;          // +0x3c
    };
    u8          pad3f[0x48 - 0x40];
    u8          mBands;        // +0x48
    u8          pad49[0x54 - 0x49];
    u8*         mpFlags;       // +0x54
    BlockEntry  mEntries[16];  // +0x58
    u8          pad1b8[0x838 - 0x58 - 16 * 0x18];
    ScratchVec  mScratch;      // +0x838
    u8          pad844[0x1828 - 0x844];
    u32*        mpAlloc;       // +0x1828
    int         mAllocSize;    // +0x182c
    int         mAllocCap;     // +0x1830

    u32  ReadBits(int n);                                       // 0x011573b0
    void FUN_01157460(int x);                                   // 0x01157460
    void FUN_011577d0(int block, int sub);                      // 0x011577d0
    void FUN_01158000(int block, int sub);                      // 0x01158000
    void FUN_01158160(int block, int sub, void* buf, int len);  // 0x01158160
    void FUN_01163f50(int block, int sub, void* buf);           // 0x01163f50
    void FUN_01165820(int block, int sub, void* a, void* b);    // 0x01165820
    void FUN_01165d00(int block, int sub, void* p);             // 0x01165d00
    void FUN_011673e0(int block, int sub, void* p);             // 0x011673e0
    void FUN_01163dc0();                                        // 0x01163dc0

    u32   FUN_011586f0(int dst);
    u32   FUN_01158880(int dst);
    void  FUN_01158a80();
    void* FUN_01158ad0(u8 flags);
    int   FUN_01159130(int n);
    int   FUN_011592c0(int n, const void* a, void* b);
    int   FUN_01159500(int n, void* a, void* b);

    int BitsUsed() const { return (int)((mpRead - mpStart) * 8 - mBitCount); }
};

// Helpers in other objects (conventions read off the call sites).
void FUN_01165fa0(const void* src, void* dst);              // 0x01165fa0 (cdecl, 2 args)
void NegateRows(float* p);                                  // 0x011675c0 (cdecl, 1 arg)
void FUN_01167cf0(const void* a, const void* b);            // 0x01167cf0 (cdecl, 2 args)
void FilterTransform(int band, void* dst, const void* src); // 0x0116b1c0 (thiscall, ret 0xc)
void PolySynth(int band, void* dst, const void* src);       // 0x01169370 (thiscall, ret 0xc)
int  FUN_01141150(int h);                                   // 0x01141150 (cdecl, 1 arg)
void FUN_0116ff30(const void* src, void* dst);              // 0x0116ff30 (CopyArr)
void FUN_01164200(int band, void* buf);                     // 0x01164200 (thiscall, ret 8)
int  FUN_0113f720(int mode);                                // 0x0113f720 (cdecl, 1 arg)
void SNDMEMI_alloc(void* p, int n);                         // 0x0113ec90 (cdecl, 2 args)
void  operator delete(void* p);

// 0x0112c820 / 0x0112c850: the audio system allocator. Both are __thiscall with the
// system singleton in ECX (loaded from 0x016e61a8 at every call site).
class SystemAlloc {
public:
    void* Alloc(int size, int a, int b, int c);   // 0x0112c820, ret 0x10
    void  Free(void* p, int flags);               // 0x0112c850, ret 8
};
extern SystemAlloc* g_pSystem;                    // 0x016e61a8

// 0x016f16f4: a global allocator-free function pointer used by the deleting dtor.
extern void (*g_pFreeFn)(void*);                  // 0x016f16f4

// 0x01158b10: grow a 4-byte-stride scratch buffer.
void GrowScratch(void** dst, int* count, int needed, int stride);
// 0x01158b90: index of the stream registered for handle `h`, or -1.
int  FindStream(int h);
// 0x01158be0 / 0x01158c60: out += in * scale over `n` floats.
void ScaleAccumX87(u32 n, float scale, const float* in, float* out);
void ScaleAccumSSE(u32 n, float scale, const float* in, float* out);
// 0x01158d00: widen `n` int16 samples to float.
void WidenI16(u32 n, const i16* in, float* out);
// 0x01158d80: windowed reconstruction. Custom register convention: `a` in EAX,
// `offset` in EDX; the rest on the stack.
void Reconstruct(u32 a, int offset, const float* win, float* out, int n);

void FlushScratch2(CSubbandDecoder* self, int count, int* out);  // 0x01159030

extern "C" int DAT_016f1734;                                // 0x016f1734
extern "C" u8  DAT_016e7bfe;                                // 0x016e7bfe (stream count, a byte)
extern "C" void* DAT_016e7fcc[];                            // 0x016e7fcc (stream table)

// 0x01485720 = 1.0f, 0x013eb1bc = 0.5f, 0x013eb8b0 = sign bit, 0x01470f1c = 0.5f,
// 0x013f1ca8 = 1/4096.
extern "C" const float kOne;    // 0x01485720
extern "C" const float kHalf;   // 0x013eb1bc
extern "C" const float kSign;   // 0x013eb8b0
extern "C" const float kHalf2;  // 0x01470f1c
extern "C" const float kInv4096;// 0x013f1ca8

__declspec(dllimport) void* __cdecl memcpy(void*, const void*, unsigned int);

// @ 0x011586f0
u32 CSubbandDecoder::FUN_011586f0(int dst)
{
    u8    alloc[12];
    int   bits;
    float bufA[0x240];
    float bufB[0x240];
    int   band;
    int   i;
    float* pu7;
    float* pu5;

    mpFlags = alloc;
    pu7 = bufA;
    pu5 = bufB;
    band = (int)ReadBits(1);
    FUN_01157460(band);
    bits = BitsUsed();
    if (mInterleave == 1)
        FUN_011577d0(0, band);
    else
        FUN_01158000(0, band);
    FUN_01158160(0, band, bufA, bits);
    FUN_01163f50(0, band, bufA);
    BlockEntry* e = &mEntries[band];
    if (e->split != 0 && e->kind == 2) {
        FUN_01165820(0, band, bufA, bufB);
        pu7 = bufB;
        pu5 = bufA;
    }
    FUN_01165d00(0, band, pu7);
    FUN_01165fa0(pu7, pu5);
    FUN_011673e0(0, band, pu5);
    NegateRows(pu5);
    if (DAT_016f1734 == 0) {
        FUN_0116ff30(pu5, pu7);
        i = 0x12;
        do {
            FilterTransform(0, (void*)dst, pu7);
            dst += 0x80;
            pu7 = (float*)((char*)pu7 + 0x80);
        } while (--i);
    } else {
        FUN_01167cf0(pu5, pu7);
        i = 0x12;
        do {
            PolySynth(0, (void*)dst, pu7);
            dst += 0x80;
            pu7 = (float*)((char*)pu7 + 0x40);
        } while (--i);
    }

    u32 rem = (u32)(-mBitCount) & 7;
    if (rem != 0)
        ReadBits(8 - (int)rem);
    mPos = BitsUsed() >> 3;
    return 0;
}

// @ 0x01158880
u32 CSubbandDecoder::FUN_01158880(int dst)
{
    u8     alloc[12];
    float  buf0[0x240];
    float  buf1[0x240];
    float  buf2[0x240];
    float* slots[4];
    int    band;
    int    n;
    float* pc;

    slots[0] = buf0;
    mpFlags  = alloc;
    slots[1] = buf1;
    slots[2] = buf2;
    band = (int)ReadBits(1);
    FUN_01157460(band);

    for (u32 b = 0; b < mBands; b++) {
        int bits = BitsUsed();
        if (mInterleave == 1)
            FUN_011577d0((int)b, band);
        else
            FUN_01158000((int)b, band);
        pc = slots[b];
        FUN_01158160((int)b, band, pc, bits);
        FUN_01163f50((int)b, band, pc);
    }

    FUN_01164200(band, buf0);

    for (u32 b = 0; b < mBands; b++) {
        slots[3] = (float*)((char*)this + (band * 3 + 0xc) * 8);
        u8* tile = (u8*)slots[3];
        if (tile[-1] == 0 || tile[0] != 2) {
            pc = slots[b];
            slots[b] = slots[2];
            slots[2] = pc;
        } else {
            FUN_01165820((int)b, band, slots[b], slots[2]);
        }
        FUN_01165d00((int)b, band, slots[2]);
        pc = slots[b];
        FUN_01165fa0(slots[2], pc);
        FUN_011673e0((int)b, band, pc);
        NegateRows(pc);

        if (DAT_016f1734 == 0) {
            FUN_01167cf0(pc, slots[2]);
            n = 0x12;
            pc = slots[2];
            do {
                FilterTransform((int)b, (void*)dst, pc);
                dst += 0x80;
                pc = (float*)((char*)pc + 0x80);
            } while (--n);
        } else {
            FUN_01167cf0(pc, slots[2]);
            n = 0x12;
            pc = slots[2];
            do {
                PolySynth((int)b, (void*)dst, pc);
                dst += 0x80;
                pc = (float*)((char*)pc + 0x40);
            } while (--n);
        }
        slots[3] = (float*)((char*)slots[3] + 0x30);
    }

    u32 rem = (u32)(-mBitCount) & 7;
    if (rem != 0)
        ReadBits(8 - (int)rem);
    mPos = BitsUsed() >> 3;
    return 0;
}

// @ 0x01158a80
void CSubbandDecoder::FUN_01158a80()
{
    void* v = vftable;
    mpStart = mpRead;
    u32 x = ReadBits(8);
    ((void (__thiscall*)(CSubbandDecoder*, u32))((void**)v)[1])(this, x);
    if (mBands == 1)
        FUN_011586f0(*(int*)((char*)this + 0x1b8));
    else
        FUN_01158880(*(int*)((char*)this + 0x1b8));
}

// @ 0x01158ad0
void* CSubbandDecoder::FUN_01158ad0(u8 flags)
{
    void* p = *(void**)((char*)this + 0x1b8);
    vftable = (void*)0x014ce868;
    if (p != 0)
        g_pFreeFn(p);
    FUN_01163dc0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// @ 0x01158b10
void GrowScratch(void** dst, int* count, int needed, int stride)
{
    int n = *count;
    if (n >= needed)
        return;
    if (n == 0) {
        *count = needed;
    } else {
        int d = *count;
        do {
            d += d;
            *count = d;
        } while (d < needed);
    }
    void* src = *dst;
    void* dstNew = g_pSystem->Alloc(*count * stride, 0, 0x10, 0);
    if (src != 0) {
        memcpy(dstNew, src, (size_t)n * stride);
        g_pSystem->Free(src, 0);
    }
    *dst = dstNew;
}

// @ 0x01158b90
int FindStream(int h)
{
    int i = 0;
    if (DAT_016e7bfe > 0) {
        do {
            void* e = DAT_016e7fcc[i];
            if (e != 0) {
                if (FUN_01141150(*(int*)e) == h)
                    return i;
            }
            ++i;
        } while (i < (int)DAT_016e7bfe);
    }
    return -1;
}

// @ 0x01158be0
void ScaleAccumX87(u32 n, float scale, const float* in, float* out)
{
    for (u32 i = 0; i < n; i++)
        out[i] += in[i] * scale;
}

// @ 0x01158c60
void ScaleAccumSSE(u32 n, float scale, const float* in, float* out)
{
    for (u32 i = 0; i < n; i++)
        out[i] += in[i] * scale;
}

// @ 0x01158d00
void WidenI16(u32 n, const i16* in, float* out)
{
    for (u32 i = 0; i < n; i++)
        out[i] = (float)in[i];
}

// @ 0x01158d80
void Reconstruct(u32 a, int offset, const float* win, float* out, int n)
{
    const float* src = (const float*)a;
    float d, s;
    if (offset < 1) {
        d = 0.0f;
        s = 1.0f;
        offset = -offset;
    } else {
        s = -1.0f;
        d = 1.0f;
    }
    s = s / (float)n;

    int i = offset;
    if (offset < n) {
        if (3 < n - offset) {
            float* o = out + 1;
            int cnt = ((n - offset) - 4u >> 2) + 1;
            i = offset + cnt * 4;
            const float* w2 = src + 2 + offset;
            const float* w = src + 3;
            do {
                o[-1] = (1.0f - d) * w[-3] + w2[-2] * d;
                d += s;
                *o = (1.0f - d) * *(float*)((char*)o + ((char*)src - (char*)out)) + w2[-1] * d;
                d += s;
                o[1] = (1.0f - d) * w[-1] + *w2 * d;
                d += s;
                o[2] = (1.0f - d) * *w + w2[1] * d;
                w2 += 4;
                o += 4;
                w += 4;
                d += s;
            } while (--cnt);
        }
        if (i < n) {
            float* o = out + (i - offset);
            do {
                *o = (1.0f - d) * *(float*)((char*)o + ((char*)src - (char*)out)) + src[i] * d;
                ++i;
                ++o;
                d += s;
            } while (i < n);
        }
    }

    int j = 0;
    if (3 < offset) {
        const float* w2 = win + 2;
        const float* w = src + 3 + (n - offset);
        float* o = out + 1 + (n - offset);
        int cnt = ((offset - 4u) >> 2) + 1;
        j = cnt * 4;
        do {
            o[-1] = (1.0f - d) * w[-3] + w2[-2] * d;
            d += s;
            *o = (1.0f - d) * *(float*)((char*)o + ((char*)src - (char*)out)) + w2[-1] * d;
            d += s;
            o[1] = (1.0f - d) * w[-1] + *w2 * d;
            d += s;
            o[2] = (1.0f - d) * *w + w2[1] * d;
            w2 += 4;
            o += 4;
            w += 4;
            d += s;
        } while (--cnt);
    }
    if (j < offset) {
        float* o = out + ((j - offset) + n);
        do {
            *o = (1.0f - d) * *(float*)((char*)o + ((char*)src - (char*)out)) + win[j] * d;
            ++j;
            ++o;
            d += s;
        } while (j < offset);
    }
}

// @ 0x01159030
void FlushScratch2(CSubbandDecoder* self, int count, int* out)
{
    void* pvVar2;
    void* _Src;
    if (self->mBitCount < 1) {
        _Src  = (void*)*out;
        pvVar2 = (void*)((char*)*out + self->mBlockSize * 4);
    } else {
        pvVar2 = (void*)*out;
        _Src  = (void*)((char*)self + 0x40);
    }

    if (count == 0) {
        memcpy((char*)self + 0x838, _Src, self->mBlockSize * 4);
        self->mBitsLeft -= self->mBlockSize;
        self->mField38 = self->mBlockSize;
        *out = (int)pvVar2;
        self->mBitCount = 0;
        self->mField3c = 0;
        return;
    }
    if (count > 0) {
        memcpy((char*)self + 0x838, _Src, count * 4);
        Reconstruct((u32)pvVar2, count, (const float*)((char*)self + 0x838 + count * 4),
                    (float*)_Src, self->mBlockSize);
        self->mBitsLeft -= self->mBlockSize;
        self->mField38 = self->mBlockSize + count;
        *out = (int)pvVar2;
        self->mBitCount = 0;
        self->mField3c = 0;
        return;
    }
    Reconstruct((u32)pvVar2, self->mBlockSize, (const float*)((char*)self + 0x838),
                (float*)_Src, self->mBlockSize);
    memcpy((char*)self + 0x838 + self->mBlockSize * 4,
           (const char*)pvVar2 + count * -4, (self->mBlockSize + count) * 4);
    self->mBitsLeft -= self->mBlockSize * 2;
    self->mField38 = self->mBlockSize * 2 + count;
    *out = (int)((char*)pvVar2 + self->mBlockSize * 4);
    self->mBitCount = 0;
    self->mField3c = 0;
}

// @ 0x01159130
int CSubbandDecoder::FUN_01159130(int param_2)
{
    if (mField38 < param_2) {
        int iVar6 = mBitsLeft;
        int param_1 = 0;
        int iVar3 = 0;
        int iVar5 = 0;
        u8* pbVar7 = (u8*)mpQuantTable;
        float fVar11 = *(const float*)((char*)this + 0x28);
        float fVar10 = fVar11;
        int rem = param_2 - mField38;
        if (0 < rem) {
            int iVar4 = mBlockSize;
            do {
                if (iVar6 < iVar4)
                    break;
                if (iVar6 < iVar4 * 2) {
                    iVar5 = mBlockSize;
                    iVar3 = 0;
                    fVar10 = fVar11;
                } else {
                    float fVar8 = *(const float*)((char*)this + 0x24);
                    iVar3 = iVar4 / 2 + (int)*pbVar7;
                    if (1.0f <= fVar8) {
                        fVar8 = (float)iVar4 * fVar8;
                        fVar10 = ((float)iVar4 + fVar11) - fVar8;
                        fVar8 = ((float)(iVar3 + iVar4) + fVar11) - fVar8;
                        fVar11 = fVar10;
                        if (fVar10 < 0.0f)
                            fVar11 = -fVar10;
                        float fVar9 = fVar8;
                        if (fVar8 < 0.0f)
                            fVar9 = -fVar8;
                        ++pbVar7;
                        if (fVar9 <= fVar11)
                            goto LAB_01159211;
                        iVar5 = mBlockSize;
                        iVar3 = 0;
                    } else {
                        fVar8 = (float)iVar4 * fVar8;
                        fVar10 = ((float)iVar4 + fVar11) - fVar8;
                        fVar8 = ((float)(iVar4 * 2 - iVar3) + fVar11) - fVar8 * 2.0f;
                        fVar11 = fVar10;
                        if (fVar10 < 0.0f)
                            fVar11 = -fVar10;
                        float fVar9 = fVar8;
                        if (fVar8 < 0.0f)
                            fVar9 = -fVar8;
                        if (fVar9 <= fVar11) {
                            pbVar7 += 2;
                            iVar3 = -iVar3;
                        LAB_01159211:
                            fVar10 = fVar8;
                            if (iVar3 < 0)
                                iVar5 = mBlockSize * 2;
                            else
                                iVar5 = mBlockSize;
                        } else {
                            iVar5 = mBlockSize;
                            ++pbVar7;
                            iVar3 = 0;
                        }
                    }
                }
                param_1 += iVar5;
                iVar6 -= iVar5;
                iVar4 = mBlockSize;
                if (rem <= iVar5 + iVar3) {
                    rem = 0;
                    break;
                }
                rem -= iVar5 + iVar3;
                fVar11 = fVar10;
            } while (0 < rem);
            iVar5 = param_1;
            if (0 < iVar3)
                iVar5 = param_1 + iVar4;
            if (0 < rem) {
                if (iVar6 < rem)
                    iVar5 += iVar6;
                else
                    iVar5 += rem;
            }
        }
        if (mBitCount < iVar5)
            return iVar5 - mBitCount;
    }
    return 0;
}

// @ 0x011592c0
int CSubbandDecoder::FUN_011592c0(int param_2, const void* param_3, void* param_4)
{
    int take = mField38;
    if (param_2 <= mField38)
        take = param_2;
    memcpy(param_4, (char*)this + 0x838 + mField3c * 4, take * 4);
    param_4 = (char*)param_4 + take * 4;
    mField3c += take;
    mField38 -= take;
    int iVar4 = param_2 - take;
    if (iVar4 == 0)
        return take;

    int param_1 = 0;
    int total = take;
    if (0 < iVar4) {
        do {
            int iVar3 = mBlockSize;
            if (mBitsLeft < iVar3)
                break;
            if (mBitsLeft < iVar3 * 2) {
                param_1 = 0;
            } else {
                u8* pbVar5 = (u8*)mpQuantTable;
                float fVar9 = *(const float*)((char*)this + 0x24);
                float fVar8 = *(const float*)((char*)this + 0x28);
                param_1 = iVar3 / 2 + (int)*pbVar5;
                float fVar7 = (float)iVar3;
                if (1.0f <= fVar9) {
                    float fVar6 = (fVar8 + fVar7) - fVar7 * fVar9;
                    fVar8 = ((float)(param_1 + iVar3) + fVar8) - fVar7 * fVar9;
                    fVar9 = fVar6;
                    if (fVar6 < 0.0f)
                        fVar9 = -fVar6;
                    fVar7 = fVar8;
                    if (fVar8 < 0.0f)
                        fVar7 = -fVar8;
                    if (fVar7 <= fVar9) {
                        *(float*)((char*)this + 0x28) = fVar8;
                    } else {
                        *(float*)((char*)this + 0x28) = fVar6;
                        param_1 = 0;
                    }
                LAB_01159423:
                    ++pbVar5;
                } else {
                    float fVar6 = (fVar8 + fVar7) - fVar7 * fVar9;
                    fVar8 = ((float)(iVar3 * 2 - param_1) + fVar8) - (fVar7 * fVar9) * 2.0f;
                    fVar9 = fVar6;
                    if (fVar6 < 0.0f)
                        fVar9 = -fVar6;
                    fVar7 = fVar8;
                    if (fVar8 < 0.0f)
                        fVar7 = -fVar8;
                    if (fVar9 < fVar7) {
                        *(float*)((char*)this + 0x28) = fVar6;
                        param_1 = 0;
                        goto LAB_01159423;
                    }
                    pbVar5 += 2;
                    param_1 = -param_1;
                    *(float*)((char*)this + 0x28) = fVar8;
                }
                mpQuantTable = pbVar5;
            }
            FlushScratch2(this, param_1, (int*)&param_3);
            int iVar3b = mField38;
            if (iVar4 <= mField38)
                iVar3b = iVar4;
            memcpy(param_4, (char*)this + 0x838 + mField3c * 4, iVar3b * 4);
            mField3c += iVar3b;
            mField38 -= iVar3b;
            total += iVar3b;
            param_4 = (char*)param_4 + iVar3b * 4;
            iVar4 -= iVar3b;
        } while (0 < iVar4);
        const void* pvVar2 = param_3;
        if (0 < param_1) {
            memcpy((char*)this + 0x40, param_3, mBlockSize * 4);
            mBitCount = mBlockSize;
            pvVar2 = (const char*)pvVar2 + mBlockSize * 4;
        }
        if (0 < iVar4) {
            if (mBitsLeft < iVar4)
                iVar4 = mBitsLeft;
            memcpy(param_4, pvVar2, iVar4 * 4);
            mBitsLeft -= iVar4;
            total += iVar4;
        }
    }
    return total;
}

// @ 0x011594e0
void FUN_011594e0(CSubbandDecoder* self, int n)
{
    *(float*)((char*)self + 0x24) = (float)n * kInv4096;
}

// @ 0x01159500
int CSubbandDecoder::FUN_01159500(int n, void* a, void* b)
{
    if (mBitsLeft == 0) {
        return ((int (__thiscall*)(CSubbandDecoder*, int, void*, void*, int))
                (*(void**)((char*)this + 8)))(this, 0xc8, b, a, (int)*(u8*)((char*)this + 0x1a));
    }
    int u = FUN_01159130(n);
    if (mAllocMode >= 0) {
        if (FUN_0113f720(mAllocMode) < u)
            return 0;
    }
    if (u > 0) {
        if ((u * 4) != mAllocCap && mAllocCap <= u * 4) {
            int need = (u & 0xffffffc0) + 0x40;
            if (mAllocSize < need)
                GrowScratch((void**)&mpAlloc, &mAllocSize, need, 4);
            a = (char*)mpAlloc + 8;
        }
        int r = ((int (__thiscall*)(CSubbandDecoder*, int, void*, void*, int))
                 (*(void**)((char*)this + 8)))(this, u, b, a, (int)*(u8*)((char*)this + 0x1a));
        if (r < 1)
            return r;
    }
    int got = FUN_011592c0(n, a, b);
    if (got < n)
        SNDMEMI_alloc((char*)b + got * 4, (n - got) * 4);
    return n;
}

// @ 0x011595f0
void FUN_011595f0(CSubbandDecoder* self)
{
    void* p = self->mpAlloc;
    if (p != 0) {
        g_pSystem->Free(p, 0);
        self->mpAlloc = 0;
        self->mAllocSize = 0;
    }
}
