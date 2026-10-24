// Slice s0115a5b0: rw::audio::core::HELPER_CEALayer3::DecodeHuffman (ISO 11172-3 "III_hufman_decode"):
// big_values pairs through the Huffman tables (with linbits escapes, batched x^(4/3) via SToPowerOf4over3),
// then the count1 quadruples, then bit-position fix-up and zero fill of the remaining lines.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"
#include <string.h>

namespace rw { namespace audio { namespace core {

extern const float  kGainTable[];       // 0x014da454 (indexed by -global_gain)
extern const short  kSfbBounds[];       // 0x014da570 (sfreq*30 + region index)
extern const float  kPow43Small[32];    // 0x014da4f0
extern const short* const kHuffTables[];// 0x014dc190 (null = table with no codes)
extern const uint8_t kLinbits[];        // 0x014dc210

struct Count1Table {                    // 8 bytes, at 0x014dc2d0
    const uint8_t* entries;             // +0 pairs of (flags, length)
    uint16_t pad4;
    uint8_t shift;                      // +6
    uint8_t pad7;
};
extern const Count1Table kCount1[];

struct GranuleInfo {                    // 0x18 bytes
    uint16_t part2And3Length;           // +0
    uint16_t bigValues;                 // +2
    uint16_t scaleFacCompress;          // +4
    uint8_t globalGain;                 // +6
    uint8_t windowSwitchingFlag;        // +7
    uint8_t blockType;                  // +8
    uint8_t mixedBlockFlag;             // +9
    uint8_t region0Count;               // +0xa
    uint8_t region1Count;               // +0xb
    uint8_t tableSelect[3];             // +0xc
    uint8_t count1TableSelect;          // +0xf
    uint8_t subBlockGain[3];            // +0x10
    uint8_t preFlag;                    // +0x13
    uint8_t scaleFacScale;              // +0x14
    uint8_t pad15[3];
};

// +0x6c scratch object: granule index followed by per-channel scfsi bits
struct Layer3Temp {                     // 0xc bytes
    uint32_t mGranule;                  // +0
    uint8_t  mScfsi[2][4];              // +4, +8
};

class System;

class HELPER_CMpegBase {
public:
    void** vftable;                     // +0x00
    uint32_t mSampFreq;                 // +0x04
    uint32_t Real_mSampFreq;            // +0x08
    uint32_t pad0c;                     // +0x0c
    uint32_t cFrameSize;                // +0x10
    uint16_t mFrameSamples;             // +0x14
    uint8_t mLayer;                     // +0x16
    uint8_t pad17;                      // +0x17
    const uint8_t* mBufPtr;             // +0x18
    const uint8_t* mBufPtrBase;         // +0x1c
    const uint8_t* mBufSave;            // +0x20
    int mShiftReg;                      // +0x24
    int mShiftRegBits;                  // +0x28
    uint8_t mSynthState[2];             // +0x2c
    uint8_t mMPEG25;                    // +0x2e
    uint8_t mLSF;                       // +0x2f
    uint8_t sfreq;                      // +0x30
    uint8_t pad31;                      // +0x31
    uint8_t mVersion;                   // +0x32
    uint8_t pad33;                      // +0x33
    uint8_t pad34;                      // +0x34
    uint8_t mSampFreqIdx;               // +0x35
    uint8_t pad36;                      // +0x36
    uint8_t mMode;                      // +0x37
    uint8_t mModeExt;                   // +0x38
    uint8_t pad39;                      // +0x39
    uint8_t pad3a;                      // +0x3a
    uint8_t mOpened;                    // +0x3b
    uint8_t mChannels;                  // +0x3c
    uint8_t pad3d[3];                   // +0x3d..+0x3f
    uint32_t pad40;                     // +0x40
    void* mpSynthHistory;               // +0x44
    uint32_t pad48[9];                  // +0x48..+0x6b
    void* mpTemp;                       // +0x6c
    int GetBits(int n);                 // 0x011598a0 (thiscall, ret 4)
    void FUN_01170500();                // 0x01170500 (thiscall, ret 0)
    void FUN_01170510();                // 0x01170510 (thiscall, ret 0)
    int  FUN_01170230();                // 0x01170230 (thiscall, ret 0)
};

class HELPER_CMpegLayer3Base : public HELPER_CMpegBase {
public:
    ~HELPER_CMpegLayer3Base();          // 0x0116c390 (thiscall, ret 0)
    void SToPowerOf4over3(int n, short* in, float* out);   // 0x0116c1a0 (thiscall, ret 0xc)
    void Dequantize(int ch, int gr, float* out);           // 0x0116c3c0 (thiscall, ret 0xc)
};

class HELPER_CEALayer3 : public HELPER_CMpegLayer3Base {
public:
    GranuleInfo mGranuleInfo[2][2];     // +0x70
    uint16_t mBandOffset[2][62];        // +0xd0 (stride 0x7c)
    uint32_t pad1c8[2];                 // +0x1c8
    float* mpDecodedFrame;              // +0x1d0

    void DecodeHuffman(int a, int b, float* out, int endBit);   // 0x0115a710 (ret 0x10)
    void UnpackTableSet(int channel, int granule);              // 0x0115a5b0 (ret 8)
    void Huffman_UnpackTableSet(int channel, int granule, uint8_t* out); // 0x0115a380 (ret 0xc)
    void GetSideInfo(int granule);                              // 0x01159950 (ret 4)
    void GetScaleFactors(int channel, int granule);             // 0x01159cc0 (ret 8)
    uint32_t ProcessHeader(uint32_t header);                    // 0x0115aeb0 (ret 4)
    int Open(const void* data, unsigned size);                  // 0x0115af60 (ret 8)
    int DecodeMono(float* out);                                 // 0x0115aff0 (ret 4)
    int DecodeStereo(float* out);                               // 0x0115b180 (ret 4)
    void Decode();                                              // 0x0115b3b0 (ret 0)
    void* Destroy(unsigned flags);                              // 0x0115b400 (ret 4)
    void FUN_0116dd70(int ch, int gr, float* in, float* out);   // 0x0116dd70 (ret 0x10)
    void FUN_0116e250(int ch, int gr, float* p);                // 0x0116e250 (ret 0xc)
    void FUN_0116fc20(int ch, int gr, float* p);                // 0x0116fc20 (ret 0xc)
    void FUN_01172e10(int ch, float* out, float* p);            // 0x01172e10 (ret 0xc)
    void FUN_01170fc0(int ch, float* out, float* p);            // 0x01170fc0 (ret 0xc)
    void III_stereo(int gr, float* p);                          // 0x0116c750 (ret 8)
};

class System {
public:
    void* Alloc(unsigned size, const char* name, unsigned align, unsigned flags); // 0x0112c820
    void  Free(void* p, unsigned flags);                                          // 0x0112c850
};

extern System* g_pSystem;               // 0x016e61a8
extern int g_floatPath;                 // 0x016f1840
extern void* g_vtblEALayer3[];          // 0x014ce8a0
extern const uint16_t kSampleRates[];   // 0x014dab04

void __cdecl FUN_01165fa0(float* a, float* b);   // 0x01165fa0
void __cdecl NegateRows(float* p);               // 0x011675c0
void __cdecl FUN_0116ff30(float* a, float* b);   // 0x0116ff30
void __cdecl FUN_0116fdc0(float* a, float* b);   // 0x0116fdc0
void __cdecl GameDelete(void* p);                // 0x00f47380

// +4/0x18/0x1c "EALayer3" frame header parsed by the request-description helper
struct EALayer3Header {
    uint32_t mValue00;                  // +0x00
    uint32_t mFlags;                    // +0x04 (0, 2 or 6)
    uint32_t mBitrate;                  // +0x08
    uint32_t mBitrate2;                 // +0x0c
    uint32_t mFrameSize;                // +0x10
    uint32_t mChannels;                 // +0x14
    uint32_t mSamples;                  // +0x18
    uint32_t mMode;                     // +0x1c
    int GetFrameLength();               // 0x0115b440
    uint32_t Parse(const uint8_t* data); // 0x0115b470
};

static __forceinline void ScaleBatch(float* out, const short* xi, const float* xp, int cnt)
{
    int k = 0;
    if (cnt >= 4) {
        do {
            out[xi[k]] = xp[k] * out[xi[k]];
            out[xi[k + 1]] = xp[k + 1] * out[xi[k + 1]];
            out[xi[k + 2]] = xp[k + 2] * out[xi[k + 2]];
            out[xi[k + 3]] = xp[k + 3] * out[xi[k + 3]];
            k += 4;
        } while (k < cnt - 3);
    }
    for (; k < cnt; k++)
        out[xi[k]] = xp[k] * out[xi[k]];
}

// @ 0x0115a710
void HELPER_CEALayer3::DecodeHuffman(int a, int b, float* out, int endBit)
{
    const GranuleInfo* g = &mGranuleInfo[a][b];
    endBit += g->part2And3Length;
    int n = 0;
    int region1Start, region2Start;
    if (g->windowSwitchingFlag && g->blockType == 2) {
        region1Start = 36;
        region2Start = 576;
    } else {
        int base = sfreq * 30 + g->region0Count;
        region1Start = kSfbBounds[base + 1];
        region2Start = kSfbBounds[base + g->region1Count + 2];
    }
    int bigValues = g->bigValues;
    const float gain = *(kGainTable - g->globalGain);
    const float negGain = -gain;
    short idx = 0;
    short xi[32];
    __declspec(align(16)) float xp[32];
    short xv[32];
    int i = 0;
    if (bigValues * 2 > 0) {
        do {
            int tbl;
            if (i < region1Start)
                tbl = g->tableSelect[0];
            else if (i < region2Start)
                tbl = g->tableSelect[1];
            else
                tbl = g->tableSelect[2];
            int linbits = kLinbits[tbl];
            if (kHuffTables[tbl]) {
                int pos = (int)(mBufPtr - mBufPtrBase) * 8 - mShiftRegBits;
                while (mShiftRegBits < 24 && pos + mShiftRegBits < endBit) {
                    mShiftReg |= (uint32_t)*mBufPtr++ << (24 - mShiftRegBits);
                    mShiftRegBits += 8;
                }
                const short* t = kHuffTables[tbl];
                int v = *t;
                while (v < 0) {
                    t++;
                    if (mShiftReg < 0)
                        t -= v;
                    mShiftRegBits += -1;
                    mShiftReg <<= 1;
                    v = *t;
                }
                int x = v >> 4;
                int y = v & 15;
                if (x == 15 && linbits)
                    x = GetBits(linbits) + 15;
                float* o = out + idx;
                if (x) {
                    *o = mShiftReg < 0 ? negGain : gain;
                    if (x < 32) {
                        *o = kPow43Small[x] * *o;
                    } else {
                        xi[n] = idx;
                        xv[n] = (short)x;
                        n++;
                        if (n >= 32) {
                            int cnt = n;
                            SToPowerOf4over3(cnt, xv, xp);
                            ScaleBatch(out, xi, xp, cnt);
                            n = 0;
                        }
                    }
                    mShiftRegBits--;
                    mShiftReg <<= 1;
                } else {
                    *o = 0.0f;
                }
                if (y == 15 && linbits)
                    y = GetBits(linbits) + 15;
                if (y) {
                    o[1] = mShiftReg < 0 ? negGain : gain;
                    if (y < 32) {
                        o[1] = kPow43Small[y] * o[1];
                    } else {
                        xi[n] = idx + 1;
                        xv[n] = (short)y;
                        n++;
                        if (n >= 32) {
                            int cnt = n;
                            SToPowerOf4over3(cnt, xv, xp);
                            ScaleBatch(out, xi, xp, cnt);
                            n = 0;
                        }
                    }
                    mShiftRegBits--;
                    mShiftReg <<= 1;
                } else {
                    o[1] = 0.0f;
                }
            } else {
                float* o = out + idx;
                o[0] = 0.0f;
                o[1] = 0.0f;
            }
            idx += 2;
            i += 2;
        } while (i < bigValues * 2);
    }
    {
        int cnt = n;
        SToPowerOf4over3(cnt, xv, xp);
        ScaleBatch(out, xi, xp, cnt);
    }
    const Count1Table* ct = &kCount1[g->count1TableSelect];
    int pos = (int)(mBufPtr - mBufPtrBase) * 8 - mShiftRegBits;
    if (pos < endBit) {
        do {
            if (idx >= 0x240)
                break;
            while (mShiftRegBits < 24 && mShiftRegBits + pos < endBit) {
                mShiftReg |= (uint32_t)*mBufPtr++ << (24 - mShiftRegBits);
                mShiftRegBits += 8;
            }
            const uint8_t* e = ct->entries + ((uint32_t)mShiftReg >> ct->shift) * 2;
            mShiftRegBits -= e[1];
            mShiftReg <<= e[1];
            if (e[0] & 8) {
                out[idx] = mShiftReg < 0 ? negGain : gain;
                mShiftReg <<= 1;
                mShiftRegBits += -1;
            } else {
                *(int*)&out[idx] = 0;
            }
            if (e[0] & 4) {
                out[idx + 1] = mShiftReg < 0 ? negGain : gain;
                mShiftReg <<= 1;
                mShiftRegBits += -1;
            } else {
                *(int*)&out[idx + 1] = 0;
            }
            if (e[0] & 2) {
                out[idx + 2] = mShiftReg < 0 ? negGain : gain;
                mShiftReg <<= 1;
                mShiftRegBits += -1;
            } else {
                *(int*)&out[idx + 2] = 0;
            }
            if (e[0] & 1) {
                out[idx + 3] = mShiftReg < 0 ? negGain : gain;
                mShiftReg <<= 1;
                mShiftRegBits += -1;
            } else {
                *(int*)&out[idx + 3] = 0;
            }
            idx += 4;
            pos = (int)(mBufPtr - mBufPtrBase) * 8 - mShiftRegBits;
        } while (pos < endBit);
    }
    if (pos > endBit) {
        uint32_t u = pos + (mShiftRegBits - endBit);
        mBufPtr -= u >> 3;
        mShiftRegBits = u & 7;
        if (mShiftRegBits)
            mShiftReg = mBufPtr[-1] << (32 - mShiftRegBits);
        idx -= 4;
    }
    pos = (int)(mBufPtr - mBufPtrBase) * 8 - mShiftRegBits;
    if (pos < endBit)
        GetBits(endBit - pos);
    if (idx < 0x240)
        memset(out + idx, 0, (0x240 - idx) * 4);
}

// @ 0x0115a5b0
void HELPER_CEALayer3::UnpackTableSet(int channel, int granule)
{
    GranuleInfo* g = &mGranuleInfo[channel][granule];
    uint16_t* sfb = mBandOffset[channel];
    uint8_t local[0x38];

    Huffman_UnpackTableSet(channel, granule, local);
    if (g->windowSwitchingFlag && g->blockType == 2) {
        if (g->mixedBlockFlag) {
            for (int i = 0; i < 8; i++)
                sfb[i] = local[i];
            const uint8_t* p = local + 8;
            for (int i = 0; i < 9; i++) {
                sfb[0x1a + i] = p[0];
                sfb[0x27 + i] = p[1];
                sfb[0x34 + i] = p[2];
                p += 3;
            }
            sfb[0x23] = 0;
            sfb[0x30] = 0;
            sfb[0x3d] = 0;
            return;
        }
        const uint8_t* p = local;
        for (int i = 0; i < 12; i++) {
            sfb[0x17 + i] = p[0];
            sfb[0x24 + i] = p[1];
            sfb[0x31 + i] = p[2];
            p += 3;
        }
        sfb[0x23] = 0;
        sfb[0x30] = 0;
        sfb[0x3d] = 0;
        return;
    }
    for (int i = 0; i < 0x15; i++)
        sfb[i] = local[i];
    sfb[0x15] = 0;
    sfb[0x16] = 0;
}

// @ 0x0115aeb0
uint32_t HELPER_CEALayer3::ProcessHeader(uint32_t header)
{
    uint32_t version = (header >> 6) & 3;
    uint32_t sfreqIndex = (header >> 4) & 3;
    uint32_t mode = (header >> 2) & 3;

    mModeExt = (uint8_t)(header & 3);
    mVersion = (uint8_t)(version & 1);
    mLSF = (version != 3);
    mMPEG25 = (version == 0);
    mMode = (uint8_t)mode;
    mLayer = 3;
    if (mMPEG25) {
        mSampFreqIdx = (uint8_t)(sfreqIndex + 6);
    } else {
        mSampFreqIdx = (uint8_t)(mLSF * 3 + sfreqIndex);
        sfreq = (uint8_t)(((mLSF - 1) & 3) + sfreqIndex);
    }
    mChannels = (uint8_t)((mode != 3) + 1);
    uint32_t rate = kSampleRates[mSampFreqIdx];
    Real_mSampFreq = rate;
    mSampFreq = rate;
    return 0;
}

// @ 0x0115af60
int HELPER_CEALayer3::Open(const void* data, unsigned size)
{
    if (mOpened)
        FUN_01170510();
    void** vt = vftable;
    typedef int (__thiscall* OpenFn)(void*, unsigned);
    OpenFn fn = (OpenFn)vt[1];
    mOpened = 1;
    mBufPtr = (const uint8_t*)data;
    mBufPtrBase = (const uint8_t*)data;
    int r = fn(this, *(const uint8_t*)data);
    if (r == -1)
        return -1;
    r = FUN_01170230();
    if (r < 0)
        return -1;
    if (mpDecodedFrame == 0) {
        mFrameSamples = 0x240;
        unsigned bytes = (unsigned)mChannels * 0x900;
        mpDecodedFrame = (float*)g_pSystem->Alloc(bytes, "EaLayer3DecodedFrame", 0x10, 0);
        if (mpDecodedFrame == 0)
            return -1;
    }
    mSynthState[0] = 1;
    mSynthState[1] = 1;
    FUN_01170500();
    return 0;
}

// @ 0x0115aff0
int HELPER_CEALayer3::DecodeMono(float* out)
{
    Layer3Temp temp;
    __declspec(align(16)) float bufA[576];
    __declspec(align(16)) float bufB[576];

    mpTemp = &temp;
    int granule = GetBits(1);
    GetSideInfo(granule);
    int endBit = (int)(mBufPtr - mBufPtrBase) * 8 - mShiftRegBits;
    if (mVersion == 1)
        GetScaleFactors(0, granule);
    else
        UnpackTableSet(0, granule);
    DecodeHuffman(0, granule, bufA, endBit);
    Dequantize(0, granule, bufA);
    float* p = bufA;
    float* q = bufB;
    if (mGranuleInfo[0][granule].windowSwitchingFlag &&
        mGranuleInfo[0][granule].blockType == 2) {
        FUN_0116dd70(0, granule, bufA, bufB);
        p = bufB;
        q = bufA;
    }
    FUN_0116e250(0, granule, p);
    FUN_01165fa0(p, q);
    FUN_0116fc20(0, granule, q);
    NegateRows(q);
    if (g_floatPath == 0) {
        FUN_0116ff30(q, p);
        for (int i = 0; i < 0x12; i++) {
            FUN_01172e10(0, out, p);
            out += 0x20;
            p += 0x20;
        }
    } else {
        FUN_0116fdc0(q, p);
        for (int i = 0; i < 0x12; i++) {
            FUN_01170fc0(0, out, p);
            out += 0x20;
            p += 0x10;
        }
    }
    unsigned pad = (unsigned)(-mShiftRegBits) & 7;
    if (pad)
        GetBits(8 - pad);
    cFrameSize = (unsigned)((int)(mBufPtr - mBufPtrBase) * 8 - mShiftRegBits) >> 3;
    return 0;
}

// @ 0x0115b180
int HELPER_CEALayer3::DecodeStereo(float* out)
{
    Layer3Temp temp;
    __declspec(align(16)) float buf0[576];
    __declspec(align(16)) float buf1[576];
    __declspec(align(16)) float buf2[576];
    float* bufs[3] = { buf0, buf1, buf2 };

    mpTemp = &temp;
    int granule = GetBits(1);
    GetSideInfo(granule);
    for (unsigned ch = 0; ch < mChannels; ch++) {
        int endBit = (int)(mBufPtr - mBufPtrBase) * 8 - mShiftRegBits;
        if (mVersion == 1)
            GetScaleFactors(ch, granule);
        else
            UnpackTableSet(ch, granule);
        DecodeHuffman(ch, granule, bufs[ch], endBit);
        Dequantize(ch, granule, bufs[ch]);
    }
    III_stereo(granule, buf0);
    for (unsigned ch = 0; ch < mChannels; ch++) {
        const GranuleInfo* g = &mGranuleInfo[ch][granule];
        if (!g->windowSwitchingFlag || g->blockType != 2) {
            float* t = bufs[ch];
            bufs[ch] = bufs[2];
            bufs[2] = t;
        } else {
            FUN_0116dd70(ch, granule, bufs[ch], bufs[2]);
        }
        FUN_0116e250(ch, granule, bufs[2]);
        FUN_01165fa0(bufs[2], bufs[ch]);
        FUN_0116fc20(ch, granule, bufs[ch]);
        NegateRows(bufs[ch]);
        if (g_floatPath == 0) {
            FUN_0116ff30(bufs[ch], bufs[2]);
            float* t = bufs[2];
            for (int i = 0; i < 0x12; i++) {
                FUN_01172e10(ch, out, t);
                t += 0x20;
                out += 0x20;
            }
        } else {
            FUN_0116fdc0(bufs[ch], bufs[2]);
            float* t = bufs[2];
            for (int i = 0; i < 0x12; i++) {
                FUN_01170fc0(ch, out, t);
                t += 0x10;
                out += 0x20;
            }
        }
    }
    unsigned pad = (unsigned)(-mShiftRegBits) & 7;
    if (pad)
        GetBits(8 - pad);
    cFrameSize = (unsigned)((int)(mBufPtr - mBufPtrBase) * 8 - mShiftRegBits) >> 3;
    return 0;
}

// @ 0x0115b3b0
void HELPER_CEALayer3::Decode()
{
    void** vt = vftable;
    mBufPtrBase = mBufPtr;
    typedef void (__thiscall* HeaderFn)(void*, int);
    ((HeaderFn)vt[1])(this, GetBits(8));
    if (mChannels == 1)
        DecodeMono(mpDecodedFrame);
    else
        DecodeStereo(mpDecodedFrame);
}

// @ 0x0115b400
void* HELPER_CEALayer3::Destroy(unsigned flags)
{
    float* p = mpDecodedFrame;
    vftable = g_vtblEALayer3;
    if (p != 0)
        g_pSystem->Free(p, 0);
    this->HELPER_CMpegLayer3Base::~HELPER_CMpegLayer3Base();
    if (flags & 1)
        GameDelete(this);
    return this;
}

// @ 0x0115b440
int EALayer3Header::GetFrameLength()
{
    int result = 0x240;
    switch (mMode) {
    case 0:
        result = 0x240 - (int)mSamples;
        // fall through
    case 1:
        if (mFlags == 0)
            result = (int)mFrameSize;
        return result;
    case 2:
        if (mFlags == 0)
            return (int)(mFrameSize * 2);
        return 0x240;
    default:
        return 0x240;
    }
}

// @ 0x0115b470
uint32_t EALayer3Header::Parse(const uint8_t* data)
{
    int16_t word = (int16_t)((data[0] << 8) | data[1]);
    mChannels = (uint32_t)(((word >> 14) & 1) + 1);
    uint32_t value = (uint32_t)word & 0xfff;
    if (data[0] & 0x80) {
        int32_t d = (int32_t)(((uint32_t)data[2] << 24) | ((uint32_t)data[3] << 16) |
                              ((uint32_t)data[4] << 8) | (uint32_t)data[5]);
        mMode = (uint32_t)((d >> 30) & 3);
        mSamples = (uint32_t)((d >> 20) & 0x3ff);
        mFrameSize = (uint32_t)((d >> 10) & 0x3ff);
        uint32_t bits = (uint32_t)d & 0x3ff;
        mBitrate = bits;
        mFlags = bits ? 6 : 0;
        mBitrate2 = bits + 6;
        return value;
    }
    mBitrate2 = 0;
    mFrameSize = 0;
    mSamples = 0;
    mMode = 0;
    mBitrate = value - 2;
    mFlags = 2;
    return value;
}

}}}
