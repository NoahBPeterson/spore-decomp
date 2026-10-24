// Slice s01135a30 -- MP3 layer-III Huffman decoding  @ 0x01135ba0  (2234 bytes).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
//
// ISO dist10 III_huffman_decode(): for one granule/channel it decodes the big_values pairs
// (region0/1/2 table selects, linbits escapes, sign bits), scales every value by |x|^(4/3)
// and the global gain, then decodes the count1 quadruples, rewinds any bits read past the
// end of the part2_3 data, skips the stuffing and zero-fills the rest of the 576 lines.
#include "../../include/types.h"
#include <string.h>

extern "C" const int16_t g_sfBandIndex[];       // 0x014cb4e0: 30 shorts (0x3c bytes) per sample-rate index
extern "C" const float g_pow43[32];             // 0x014cb460  i^(4/3), i < 32
extern "C" const uint8_t g_linbits[];           // 0x014cbcd0  per table_select
extern "C" const float g_gainEnd[];             // 0x014cc17c  gain scale, indexed negatively

struct Count1Table {                            // 0x015c0004, 8 bytes each
    const uint8_t* mTable;                      // (flags, length) byte pairs
    uint16_t mBits;                             // address bits of the table
    uint16_t pad;
};
extern "C" const Count1Table g_count1Tables[];  // 0x015c0004

struct BitReader {                              // bit stream with a 2 KB ring buffer
    int pad0;
    unsigned int mPos;                          // +0x04  next byte
    unsigned int mBitsLeft;                     // +0x08  bits left in the cache
    unsigned int mCache;                        // +0x0c  MSB-aligned
    uint8_t mBuf[0x800];                        // +0x10

    unsigned int ReadBits(unsigned int n);      // 0x01134af0 (thiscall, ret 4)

    __forceinline unsigned int Bit()
    {
        if (mBitsLeft == 0) {
            unsigned int p = mPos;
            mCache = (unsigned int)mBuf[p & 0x7ff] << 24;
            mPos = p + 1;
            mBitsLeft = 8;
        }
        unsigned int c = mCache;
        mBitsLeft--;
        unsigned int bit = c >> 31;
        mCache = c + c;
        return bit;
    }
    __forceinline int BitPos() const { return (int)mPos * 8 - (int)mBitsLeft; }
    // un-read bits so the stream position is `nbits` bits earlier than the cache implies
    __forceinline void SetPos(unsigned int bitsLeftTotal)
    {
        mPos -= bitsLeftTotal >> 3;
        mBitsLeft = bitsLeftTotal & 7;
        if (mBitsLeft)
            mCache = (unsigned int)mBuf[(mPos - 1) & 0x7ff] << (0x20 - mBitsLeft);
    }
};

struct Pow43Calc {
    void Compute(int n, const int16_t* vals, float* out);   // 0x01143e70 (thiscall, ret 0xc)
};

struct HuffTable { const int16_t* mTree; int pad; };         // 8 bytes, tree is NULL for unused tables

struct GrInfo {                                              // 0x18 bytes
    uint16_t part2_3_length;                                 // +0x00
    uint16_t big_values;                                     // +0x02
    char pad4[2];
    uint8_t gainIdx;                                         // +0x06
    uint8_t window_switching_flag;                           // +0x07
    uint8_t block_type;                                      // +0x08
    uint8_t mixed_flag;                                      // +0x09
    uint8_t region0_count;                                   // +0x0a
    uint8_t region1_count;                                   // +0x0b
    uint8_t table_select[3];                                 // +0x0c
    uint8_t count1table_select;                              // +0x0f
    char pad10[0x18 - 0x10];
};

struct Layer3Decoder {
    char pad0[0x34];
    Pow43Calc mPow43;                                        // +0x34
    char pad35[0x70 - 0x35];
    uint8_t sfreq;                                           // +0x70
    char pad71[0x88 - 0x71];
    HuffTable mHuff[32];                                     // +0x88
    GrInfo mGr[1];                                           // +0x188 (stride 0x18)
    char pad1a0[0x2710 - 0x1a0];
    BitReader mBits;                                         // +0x2710

    void HuffmanDecode(int gr, int ch, float* xr, int extraBits);
};

// out[idx[k]] *= pow43(val[k]) for the escape values collected so far
static __forceinline void ApplyEscapes(Pow43Calc* calc, int n, const int16_t* vals, const int16_t* idx,
                                       float* tmp, float* xr)
{
    calc->Compute(n, vals, tmp);
    for (int k = 0; k < n; k++)
        xr[idx[k]] = tmp[k] * xr[idx[k]];
}

// @ 0x01135ba0
void Layer3Decoder::HuffmanDecode(int gr, int ch, float* xr, int extraBits)
{
    int n = 0;
    GrInfo* g = &mGr[ch + gr * 2];
    const int endBit = g->part2_3_length + extraBits;
    int region1Start, region2Start;
    if (g->window_switching_flag && g->block_type == 2) {
        region1Start = 36;
        region2Start = 576;
    } else {
        const int base = sfreq * 30;
        region1Start = g_sfBandIndex[base + g->region0_count + 1];
        region2Start = g_sfBandIndex[base + g->region0_count + g->region1_count + 2];
    }

    const float gain = g_gainEnd[-(int)g->gainIdx];
    const float ngain = -gain;
    const float zero = 0.0f;
    short s = 0;
    int16_t idx[32];
    __declspec(align(16)) float tmp[32];
    int16_t vals[32];

    const int count = g->big_values * 2;
    for (int i = 0; i < count; i += 2, s += 2) {
        int sel;
        if (i < region1Start)
            sel = g->table_select[0];
        else if (i < region2Start)
            sel = g->table_select[1];
        else
            sel = g->table_select[2];
        const int linbits = g_linbits[sel];
        const int16_t* p = mHuff[sel].mTree;
        if (p == 0) {
            xr[s] = zero;
            xr[s + 1] = zero;
            continue;
        }
        int v = *p;
        while (v < 0) {
            p++;
            if (mBits.Bit())
                p += -v;
            v = *p;
        }
        int x = v >> 4;
        int y = v & 0xf;
        if (x == 15 && linbits)
            x = mBits.ReadBits(linbits) + 15;
        if (x != 0) {
            if (mBits.Bit()) xr[s] = ngain; else xr[s] = gain;
            if (x < 32) {
                xr[s] = g_pow43[x] * xr[s];
            } else {
                idx[n] = s;
                vals[n] = (int16_t)x;
                n++;
                if (n >= 32) {
                    ApplyEscapes(&mPow43, n, vals, idx, tmp, xr);
                    n = 0;
                }
            }
        } else {
            xr[s] = zero;
        }
        if (y == 15 && linbits)
            y = mBits.ReadBits(linbits) + 15;
        if (y != 0) {
            if (mBits.Bit()) xr[s + 1] = ngain; else xr[s + 1] = gain;
            if (y < 32) {
                xr[s + 1] = g_pow43[y] * xr[s + 1];
            } else {
                idx[n] = s + 1;
                vals[n] = (int16_t)y;
                n++;
                if (n >= 32) {
                    ApplyEscapes(&mPow43, n, vals, idx, tmp, xr);
                    n = 0;
                }
            }
        } else {
            xr[s + 1] = zero;
        }
    }
    ApplyEscapes(&mPow43, n, vals, idx, tmp, xr);

    // count1 region
    const Count1Table* t = &g_count1Tables[g->count1table_select];
    int pos = mBits.BitPos();
    while (pos < endBit && s < 0x240) {
        const unsigned int code = mBits.ReadBits(t->mBits);
        const uint8_t* e = t->mTable + code * 2;
        mBits.mBitsLeft += t->mBits - e[1];
        mBits.SetPos(mBits.mBitsLeft);
        const unsigned int flags = e[0];
        if (flags & 8) { if (mBits.Bit()) xr[s] = ngain; else xr[s] = gain; } else xr[s] = zero;
        if (flags & 4) { if (mBits.Bit()) xr[s + 1] = ngain; else xr[s + 1] = gain; } else xr[s + 1] = zero;
        if (flags & 2) { if (mBits.Bit()) xr[s + 2] = ngain; else xr[s + 2] = gain; } else xr[s + 2] = zero;
        if (flags & 1) { if (mBits.Bit()) xr[s + 3] = ngain; else xr[s + 3] = gain; } else xr[s + 3] = zero;
        s += 4;
        pos = mBits.BitPos();
    }
    if (pos > endBit) {
        mBits.SetPos(pos + (mBits.mBitsLeft - endBit));
        s -= 4;
    }
    pos = mBits.BitPos();
    if (pos < endBit)
        mBits.ReadBits(endBit - pos);
    if (s < 0x240)
        memset(&xr[s], 0, (0x240 - s) * 4);
}

// ---------------------------------------------------------------------------
// Layer3Dec construction / state helpers (slice s01135a30 part 2).
// Base sub-object lives at +0x34 and is a CMpegLayer3Base (vtable at +0x34).
// ---------------------------------------------------------------------------

struct MpegLayer3Base {                 // at Layer3Dec + 0x34
    void* mpVtbl;                       // +0x00
    void Init();                        // 0x01146ca0 (thiscall)
    void Release();                     // 0x01146cf0 (thiscall)
    void Reset(int b);                  // 0x01148cf0 (thiscall, ret 4)
    void Reset2(int b);                 // 0x01146d20 (thiscall, ret 4)
    void Reset3();                      // 0x01148cc0 (thiscall)
    int Open();                         // 0x01148c60 (thiscall) -> int
    void Prepare();                     // 0x01148a20 (thiscall)
    void Finish();                      // 0x01148cb0 (thiscall)
    int  DecodeOpen();                  // 0x01148c00 (thiscall) -> int
};

struct Layer3DecObj {                   // Layer3Dec instance
    void* mpVtbl;                       // +0x00
    char pad04[0x2e - 0x04];
    uint8_t mSampleRateIdx;             // +0x2e
    char pad2f[0x48 - 0x2f];
    uint16_t mGranuleCount;             // +0x48 (0x480 or 0x240)
    char pad4a[0x4b - 0x4a];
    uint8_t mStarted;                   // +0x4b
    uint8_t mChannelCount;              // +0x4c
    char pad4d[0x54 - 0x4d];
    int mpStreamA;                      // +0x54
    int mpStreamB;                      // +0x58
    char pad5c[0x6c - 0x5c];
    uint8_t mFlag6c;                    // +0x6c
    uint8_t mFlag6d;                    // +0x6d
    char pad6e[0x6f - 0x6e];
    uint8_t mFlag6f;                    // +0x6f
    char pad70[0x71 - 0x70];
    uint8_t mNumGranules;               // +0x71 (set to 1 or 2)
    char pad72[0x308 - 0x72];
    int m308;                           // +0x308
    char pad30c[0x2710 - 0x30c];
    int m2710;                          // +0x2710
    int m2714;                          // +0x2714
    int m2718;                          // +0x2718
    char pad271c[0x2f20 - 0x271c];
    int m2f20;                          // +0x2f20
    int m2f24;                          // +0x2f24
    char pad2f28[0x1a000];              // (opaque tail)

    // __thiscall targets declared as members (MSVC 7.1 rejects __thiscall free functions).
    Layer3DecObj* FUN_011368b0(int arg);        // @ 0x011368b0
    Layer3DecObj* FUN_01136910(unsigned int flags);  // @ 0x01136910
    int FUN_01136980(int arg, int arg2);                  // @ 0x01136980
    void FUN_01135a30(int arg1, int arg2);      // @ 0x01135a30
    int FUN_01136460(int arg1);                 // @ 0x01136460
};

extern "C" void __cdecl operator_delete(void* p);   // 0x00f47380
extern "C" void __stdcall FUN_011357f0(int arg1, int arg2, uint8_t* out);  // 0x011357f0

// @ 0x01136860
int __fastcall FUN_01136860(Layer3DecObj* self)
{
    self->mGranuleCount = 0x480;
    if (self->mFlag6f != 0)
        self->mGranuleCount = 0x240;
    uint8_t one = (self->mFlag6f == 0);
    self->mFlag6c = 1;
    self->mFlag6d = 1;
    self->mNumGranules = one + 1;
    self->m308 = 0;
    self->m2710 = 0;
    self->m2714 = 0;
    self->m2718 = 0;
    return 0;
}

// @ 0x011368b0
Layer3DecObj* Layer3DecObj::FUN_011368b0(int arg)
{
    Layer3DecObj* self = this;
    self->mpVtbl = (void*)0x014a7e54;
    MpegLayer3Base* base = (MpegLayer3Base*)((char*)self + 0x34);
    base->Init();
    self->mpVtbl = (void*)0x014a7f18;
    base->mpVtbl = (void*)0x014a7f14;
    self->m2710 = 0;
    self->m2714 = 0;
    self->m2718 = 0;
    base->Reset(arg);
    base->Reset2(arg);
    return self;
}

// @ 0x01136910
Layer3DecObj* Layer3DecObj::FUN_01136910(unsigned int flags)
{
    Layer3DecObj* self = this;
    MpegLayer3Base* base = (MpegLayer3Base*)((char*)self + 0x34);
    self->mpVtbl = (void*)0x014a7f18;
    base->mpVtbl = (void*)0x014a7f14;
    base->Release();
    self->mpVtbl = (void*)0x014a7e54;
    if (flags & 1)
        operator_delete(self);
    return self;
}

// @ 0x01136960
char __cdecl FUN_01136960(Layer3DecObj* self)
{
    self->m2f24 = 0;
    self->m2f20 = 0;
    self->FUN_011368b0(self->mSampleRateIdx);
    return 1;
}

// @ 0x01136980
int Layer3DecObj::FUN_01136980(int arg, int arg2)
{
    Layer3DecObj* self = this;
    if (self->mStarted != 0)
        ((MpegLayer3Base*)((char*)self + 0x34))->Reset3();
    self->mStarted = 1;
    self->mpStreamA = arg;
    self->mpStreamB = arg;
    if (arg == 0)
        return -1;
    MpegLayer3Base* base = (MpegLayer3Base*)((char*)self + 0x34);
    if (base->Open() != 0)
        return -1;
    base->Prepare();
    FUN_01136860(self);
    base->Finish();
    return 0;
}

// @ 0x01135a30
void Layer3DecObj::FUN_01135a30(int arg1, int arg2)
{
    Layer3DecObj* self = this;
    GrInfo* gr = (GrInfo*)((char*)self + 0x188 + (arg2 + arg1 * 2) * 0x18);
    uint16_t* out = (uint16_t*)((char*)self + 0x1e8 + arg1 * 0x7c);
    uint8_t local_38[56];
    FUN_011357f0(arg1, arg2, local_38);

    if (gr->window_switching_flag != 0 && gr->block_type == 2) {
        if (gr->mixed_flag != 0) {
            out[0] = local_38[0];
            out[1] = local_38[1];
            out[2] = local_38[2];
            out[3] = local_38[3];
            out[4] = local_38[4];
            out[5] = local_38[5];
            out[6] = local_38[6];
            out[7] = local_38[7];
            uint8_t* p = local_38 + 9;
            uint16_t* q = out + 0x27;
            int n = 9;
            do {
                q[-0xd] = p[-1];
                q[0] = p[0];
                q[0xd] = p[1];
                p += 3;
                q += 1;
            } while (--n != 0);
            uint16_t* z = out + 0x23;
            int m = 3;
            do {
                *z = 0;
                z += 0xd;
            } while (--m != 0);
            return;
        }
        uint8_t* p2 = local_38 + 1;
        uint16_t* q2 = out + 0x24;
        int n2 = 0xc;
        do {
            q2[-0xd] = p2[-1];
            q2[0] = p2[0];
            q2[0xd] = p2[1];
            p2 += 3;
            q2 += 1;
        } while (--n2 != 0);
        uint16_t* z = out + 0x23;
        int m = 3;
        do {
            *z = 0;
            z += 0xd;
        } while (--m != 0);
        return;
    }

    unsigned int i = 0;
    do {
        out[i] = local_38[i];
        i++;
    } while (i < 0x15);
    out[0x15] = 0;
    out[0x16] = 0;
}

// ---------------------------------------------------------------------------
// EALayer3Core::Decode (0x01136460). The object shares the Layer3DecObj prefix; fields used only
// here are named in EALayer3Obj and reached through a cast.
// ---------------------------------------------------------------------------
extern "C" int  __stdcall FUN_01134a60(int n);          // 0x01134a60
extern "C" void __cdecl FUN_01134b70();                 // 0x01134b70
extern "C" void __stdcall FUN_01134af0(int n);          // 0x01134af0
extern "C" void __stdcall FUN_01135350(int ch, unsigned int gr);   // 0x01135350
extern "C" void __stdcall FUN_01144020(int ch, unsigned int gr, char* p);   // 0x01144020
extern "C" void __stdcall FUN_011443b0(unsigned int gr, char* p);  // 0x011443b0
extern "C" void __stdcall FUN_01145d10(int ch, unsigned int gr, char* a, char* b); // 0x01145d10
extern "C" void __stdcall FUN_01146200(int ch, unsigned int gr, char* p);  // 0x01146200
extern "C" void __stdcall FUN_01165fa0(char* a, char* b);   // 0x01165fa0
extern "C" void __stdcall FUN_011467f0(int ch, unsigned int gr, char* p);  // 0x011467f0
extern "C" void __cdecl FUN_011675c0(char* p);          // 0x011675c0
extern "C" void __stdcall FUN_0116ff30(char* a, char* b);  // 0x0116ff30
extern "C" void __stdcall FUN_01148050(int ch, int src, char* dst);  // 0x01148050
extern "C" int  __cdecl FUN_1135ba0_call(void* self, int ch, unsigned int gr, char* p, int bits);  // 0x01135ba0
extern int DAT_014cbc30[];
extern int DAT_014cbcb0[];

struct EALayer3Obj {
    char pad00[0x44];
    int m44;                            // +0x44
    int m4c;                            // +0x4c
    char pad50[0x6f - 0x50];
    uint8_t m6f;                        // +0x6f
    char pad70[0x71 - 0x70];
    uint8_t m71;                        // +0x71
    uint8_t m72;                        // +0x72
    uint8_t m73;                        // +0x73
    char pad74[0x77 - 0x74];
    uint8_t m77;                        // +0x77
    char pad78[0x7c - 0x78];
    int m7c;                            // +0x7c
    int m80;                            // +0x80
    char pad84[0x184 - 0x84];
    int* m184;                          // +0x184
    char pad188[0x2e0 - 0x188];
    int m2e0;                           // +0x2e0
    int m2e4;                           // +0x2e4
    char pad2e8[0x2f4 - 0x2e8];
    int m2f4;                           // +0x2f4
    int m2f8;                           // +0x2f8
    char* m2fc;                         // +0x2fc
    char* m300;                         // +0x300
    char* m304;                         // +0x304
    int m308;                           // +0x308
    char pad30c[0x2710 - 0x30c];
    int m2710;                          // +0x2710 (ring index)
    int m2714;                          // +0x2714
    int m2718;                          // +0x2718
    unsigned int m271c;                 // +0x271c
    uint8_t m2720[0x800];               // +0x2720
};

// @ 0x01136460
int Layer3DecObj::FUN_01136460(int arg1)
{
    EALayer3Obj* o = (EALayer3Obj*)this;
    char local_3f1c[12];
    uint8_t local_3f10[2304];
    uint8_t local_3610[4608];
    uint8_t local_2410[2304];
    char local_1b10[2304];
    uint8_t local_1210[2304];
    char local_910[2300];
    unsigned int local_3f44;
    char* local_3f40;
    int local_3f3c;
    char* local_3f38[4];
    char* local_3f28;
    int local_3f24[2];
    int iVar4;
    int iVar7;
    unsigned int uVar5;
    uint8_t bVar1;

    o->m184 = (int*)local_3f1c;
    local_3f24[0] = arg1;
    local_3f24[1] = arg1 + 0x1200;
    iVar4 = ((MpegLayer3Base*)((char*)this + 0x34))->DecodeOpen();
    if (iVar4 == 0) {
        if (o->m73 == 0)
            FUN_01134a60(0x10);
        FUN_01134b70();
        if (o->m6f == 0)
            iVar4 = (o->m44 - ((((o->m77 != 3) - 1) & 0xfffffff1) + 0x20)) - (((o->m73 != 0) - 1) & 2);
        else
            iVar4 = (o->m44 - ((unsigned int)(o->m77 != 3) * 8 + 9)) - (((o->m73 != 0) - 1) & 2);
        iVar7 = iVar4;
        if (iVar4 > 0) {
            do {
                uint8_t uVar3 = (uint8_t)FUN_01134a60(8);
                o->m2720[o->m2710 & 0x7ff] = uVar3;
                iVar7--;
                o->m2710 = (o->m2710 + 1) & 0x7ff;
            } while (iVar7 != 0);
        }
        local_3f40 = (char*)((unsigned int)(o->m2714 * 8 - o->m2718) >> 3);
        uVar5 = -(unsigned int)o->m2718 & 7;
        if (uVar5 != 0) {
            FUN_01134af0(8 - (int)uVar5);
            local_3f40 = (char*)((int)local_3f40 + 1);
        }
        iVar7 = (o->m308 - *o->m184) - (int)local_3f40;
        iVar4 = o->m308 + iVar4;
        o->m308 = iVar4;
        if (iVar7 >= 0) {
            if ((int)local_3f40 > 0x800) {
                o->m308 = iVar4 - 0x800;
                o->m2714 = o->m2714 - 0x800;
                if (o->m2718 != 0) {
                    o->m271c = (unsigned int)o->m2720[(o->m2714 - 1) & 0x7ff]
                             << (0x20 - (char)o->m2718 & 0x1f);
                }
            }
            for (; iVar7 > 0; iVar7--)
                FUN_01134af0(8);
            local_3f44 = 0;
            if (o->m71 != 0) {
                local_3f40 = (char*)((char*)o + 400);
                do {
                    local_3f38[0] = local_1b10;
                    uVar5 = 0;
                    local_3f38[1] = (char*)local_1210;
                    local_3f38[2] = (char*)local_910;
                    o->m2e4 = o->m2e0;
                    if (o->m4c != 0) {
                        do {
                            iVar4 = o->m2714;
                            iVar7 = o->m2718;
                            if (o->m72 == 1)
                                FUN_01135350((int)uVar5, local_3f44);
                            else
                                ((Layer3DecObj*)this)->FUN_01135a30((int)uVar5, (int)local_3f44);
                            char* pcVar2 = local_3f38[uVar5];
                            DAT_014cbc30[2] = 0x1a;   /* 0x015c000a */
                            DAT_014cbcb0[1] = 4;      /* 0x015c0010 */
                            DAT_014cbc30[1] = 6;      /* 0x015c0008 */
                            DAT_014cbc30[0] = 0;      /* 0x015c0004 <- &DAT_014cbc30 */
                            DAT_014cbcb0[0] = 0;      /* 0x015c000c <- &DAT_014cbcb0 */
                            DAT_014cbcb0[2] = 0x1c;   /* 0x015c0012 */
                            FUN_1135ba0_call((void*)((char*)this + 0x34), (int)uVar5, local_3f44, pcVar2, iVar4 * 8 - iVar7);
                            FUN_01144020((int)uVar5, local_3f44, pcVar2);
                            uVar5++;
                        } while (uVar5 < o->m4c);
                    }
                    if (o->m4c == 2) {
                        o->m2fc = (char*)local_2410;
                        o->m300 = (char*)local_3f10;
                        o->m304 = (char*)local_3610;
                        FUN_011443b0(local_3f44, local_1b10);
                    }                    uVar5 = 0;
                    if (o->m4c != 0) {
                        local_3f38[3] = local_3f40;
                        do {
                            char** ppcVar6;
                            if (local_3f38[3][-1] == 0 || local_3f38[3][0] != 2) {
                                char* pcVar2 = local_3f38[uVar5];
                                ppcVar6 = local_3f38 + uVar5;
                                *ppcVar6 = local_3f38[2];
                                local_3f38[2] = pcVar2;
                            } else {
                                ppcVar6 = local_3f38 + uVar5;
                                FUN_01145d10((int)uVar5, local_3f44, local_3f38[uVar5], local_3f38[2]);
                            }
                            FUN_01146200((int)uVar5, local_3f44, local_3f38[2]);
                            char* pcVar2 = *ppcVar6;
                            FUN_01165fa0(local_3f38[2], pcVar2);
                            o->m2f8 = o->m2f4;
                            FUN_011467f0((int)uVar5, local_3f44, pcVar2);
                            o->m80 = o->m7c;
                            FUN_011675c0(pcVar2);
                            FUN_0116ff30(pcVar2, local_3f38[2]);
                            iVar4 = local_3f24[uVar5];
                            local_3f28 = local_3f38[2];
                            local_3f3c = 0x12;
                            do {
                                FUN_01148050((int)uVar5, iVar4, local_3f28);
                                local_3f28 += 0x80;
                                iVar4 += 0x80;
                            } while (--local_3f3c != 0);
                            bVar1 = o->m4c;
                            local_3f38[3] += 0x30;
                            local_3f24[uVar5] = iVar4;
                            uVar5++;
                        } while (uVar5 < bVar1);
                    }
                    local_3f40 += 0x18;
                    local_3f44++;
                } while (local_3f44 < o->m71);
            }
            return 0;
        }
    }
    return -1;
}
