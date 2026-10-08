// Slice s01148050 -- RenderWare 4 rw::audio::core MPEG/EALayer3 base object.
// Built with VC .NET 2003 (cl 13.10) + /GL /LTCG; most functions that make calls
// cannot be single-object byte-exact.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE2
#include <string.h>
#include <xmmintrin.h>
#include <new>

#pragma function(memset)

namespace rw { namespace audio { namespace core {

class System {
public:
    void* Alloc(unsigned int size, const char* name, unsigned int align, unsigned int flags);
    void  Free(void* p, unsigned int flags);
};

extern System* g_pSystem;                 // 0x16e61a8
extern const short g_bitRateTable[];      // 0x14ce430
extern const unsigned short g_sampFreqTable[];  // 0x14ce43c
extern float g_synthScratch[32];          // 0x16e8280
extern const float g_synthMatrixA[];      // 0x15c2f00
extern const float g_synthMatrixB[];      // 0x15c3300
extern const float g_synthWindow[];       // 0x14cc1b0 (16 floats before 0x14cc1f0)
extern const float g_mw0[];               // 0x14cc1f0
extern const float g_mw1[];               // 0x14cca74
extern const float g_mw2[];               // 0x14cd308
extern const float g_mw3[];               // 0x14cdb9c
extern const float g_mb0[];               // 0x14cc970
extern const float g_mb1[];               // 0x14ce31c
extern const float g_mb2[];               // 0x14cda88
extern const float g_mb3[];               // 0x14cd1f4

class CMpegBase {
public:
    virtual ~CMpegBase();                 // +0x00
    int Real_mSampFreq;                   // +0x04
    int mSampFreq;                        // +0x08
    int mBitRate;                         // +0x0c
    int cFrameSize;                       // +0x10
    unsigned short mFrameSamples;         // +0x14
    unsigned char mLayer;                 // +0x16
    unsigned char mOpened;                // +0x17
    unsigned char mChannels;              // +0x18
    char pad19[3];                        // +0x19
    unsigned int mHeader;                 // +0x1c
    unsigned char* mBufPtr;               // +0x20
    unsigned char* mBufPtrBase;           // +0x24
    unsigned char* mBufPtrNext;           // +0x28
    unsigned int mShiftReg;               // +0x2c
    int mShiftRegBits;                    // +0x30
    int mResetSynthRequired;              // +0x34
    unsigned char mBandOffset[2];         // +0x38
    unsigned char mMPEG25;                // +0x3a
    unsigned char mLSF;                   // +0x3b
    unsigned char sfreq;                  // +0x3c
    unsigned char max_gr;                 // +0x3d
    unsigned char mVersion;               // +0x3e
    unsigned char mErrorProt;             // +0x3f
    unsigned char mBitRateIdx;            // +0x40
    unsigned char mSampFreqIdx;           // +0x41
    unsigned char mPadding;               // +0x42
    unsigned char mMode;                  // +0x43
    unsigned char mModeExt;               // +0x44
    unsigned char mCopyright;             // +0x45
    unsigned char mOriginal;              // +0x46
    char pad47;                           // +0x47
    void* mpPolySynthHistory;             // +0x48
    void* mpLoadedPolySynthHistory;       // +0x4c

    CMpegBase();
    void SetBuffer(unsigned char* p);
    void ResetLoadedHistory();
    int ParseHeader(unsigned int header);      // 0x1148a40 (body below as ParseHeaderImpl)
    int ParseHeaderImpl(unsigned int header);
    int  ReadHeader();
    int  PeekHeader();
    void ResetBits();
    int  Close();
    int  AllocateSynth(int numChannels);

    void PolySynth(int iChannel, float* pOutSamples, float* pInSamples);
    void PolySynth2(int iChannel, float* pOutSamples, float* pInSamples);
};

void SynthesisMatrix(int dst, float* out2, const float* in);

// Scratch and local body for the shared 32-point matrixing DCT (0x01146dd0), whose custom
// register convention (eax=in, edx=outA, stack=outB) a single-object cl cannot emit.
extern float g_dct32Scratch[64];                 // 0x016e8180
void Dct32Local(const float* in, float* outA, float* outB);
#include "s01148050_dct32.h"

// @ 0x01148050
void CMpegBase::PolySynth(int iChannel, float* pOutSamples, float* pInSamples)
{
    int iPhase = (mBandOffset[iChannel] - 1) & 0xF;
    mBandOffset[iChannel] = (unsigned char)iPhase;

    int iOdd = iPhase & 1;
    int iNotOdd = iOdd ^ 1;
    int iCol = iPhase + iNotOdd;

    float* pHistory = (float*)((char*)mpLoadedPolySynthHistory + iChannel * 0x900);
    float* pColumnA = pHistory + iOdd * 288 + ((iPhase + iOdd) & 0xF);
    float* pColumnB = pHistory + iNotOdd * 288 + iCol;
    Dct32Local(pInSamples, pColumnB, pColumnA);

    float* pBank = pHistory + iNotOdd * 288;
    float* pWindow = (float*)g_synthWindow + 16 - iCol;

    // out[0..15]
    for (int j = 0; j < 16; ++j) {
        float* pW = pWindow + 32 * j;
        float* pH = pBank + 16 * j;
        float acc = pW[0] * pH[0];
        for (int t = 1; t < 16; ++t) {
            float term = pW[t] * pH[t];
            if ((t & 1) != 0)
                acc = acc - term;
            else
                acc = acc + term;
        }
        pOutSamples[j] = acc;
    }

    // out[16]
    {
        float* pW = pWindow + 512;
        float* pH = pBank + 256;
        float acc = 0.0f;
        for (int u = 0; u < 8; ++u)
            acc = acc + pW[2 * u] * pH[2 * u];
        pOutSamples[16] = acc;
    }

    // out[17..31]
    {
        float* pWindowRev = pWindow + 480 + 2 * iCol;   // == g_synthWindow + 496 + iCol
        for (int k = 0; k < 15; ++k) {
            float* pW2 = pWindowRev - 32 * k;
            float* pH = pBank + 240 - 16 * k;
            float acc = pW2[-1] * pH[0];
            // The original negates with `xorps` against 0x80000000, which flips a NaN's sign
            // bit; an arithmetic 0.0f - acc does not.  Flip the bit explicitly to match.
            {
                union { float f; unsigned int u; } bits;
                bits.f = acc;
                bits.u ^= 0x80000000u;
                acc = bits.f;
            }
            for (int t = 1; t < 15; ++t)
                acc = acc - pW2[-1 - t] * pH[t];
            acc = acc - pW2[0] * pH[15];
            pOutSamples[17 + k] = acc;
        }
    }
}

// @ 0x01148340
void SynthesisMatrix(int dst, float* out2, const float* in)
{
    float* S = g_synthScratch;
    float* D = g_synthScratch + 16;

    S[0] = in[0] + in[31];  S[1] = in[1] + in[30];  S[2] = in[2] + in[29];  S[3] = in[3] + in[28];
    D[0] = in[0] - in[31];  D[1] = in[1] - in[30];  D[2] = in[2] - in[29];  D[3] = in[3] - in[28];
    S[4] = in[4] + in[27];  S[5] = in[5] + in[26];  S[6] = in[6] + in[25];  S[7] = in[7] + in[24];
    D[4] = in[4] - in[27];  D[5] = in[5] - in[26];  D[6] = in[6] - in[25];  D[7] = in[7] - in[24];
    S[8] = in[8] + in[23];  S[9] = in[9] + in[22];  S[10] = in[10] + in[21]; S[11] = in[11] + in[20];
    D[8] = in[8] - in[23];  D[9] = in[9] - in[22];  D[10] = in[10] - in[21]; D[11] = in[11] - in[20];
    S[12] = in[12] + in[19]; S[13] = in[13] + in[18]; S[14] = in[14] + in[17]; S[15] = in[15] + in[16];
    D[12] = in[12] - in[19]; D[13] = in[13] - in[18]; D[14] = in[14] - in[17]; D[15] = in[15] - in[16];

    float* pfVar20 = (float*)(dst + 0x400);
    const float* pfVar17 = g_synthMatrixA;
    int iVar18 = 0;
    int iVar19 = 0;
    const float* pfVar16 = pfVar17;
    float fVar3 = 0, fVar21 = 0, fVar22 = 0, fVar23 = 0, fVar24 = 0, fVar25 = 0;
    float fVar26 = 0, fVar27 = 0, fVar28 = 0, fVar29 = 0, fVar30 = 0, fVar31 = 0, fVar32 = 0;
    float fVar33 = 0, fVar34 = 0, fVar35 = 0, fVar36 = 0, fVar37 = 0, fVar38 = 0, fVar39 = 0;
    float fVar40 = S[4], fVar41 = 0, fVar42 = S[5], fVar43 = 0, fVar44 = S[15];
    float fVar45 = S[6], fVar46 = 0, fVar47 = S[7], fVar48 = 0, fVar49 = 0, fVar50 = 0;
    float fVar51 = 0, fVar52 = 0, fVar53 = S[12], fVar54 = S[13], fVar55 = S[14], fVar56 = S[15];

    do {
        iVar19 = iVar18;
        pfVar16 = pfVar17;
        fVar44 = S[15]; fVar39 = S[14]; fVar36 = S[13]; fVar33 = S[12];
        fVar29 = S[7];  fVar26 = S[6];  fVar23 = S[5];  fVar3 = S[4];
        fVar21 = S[0] * pfVar16[0x10];
        fVar24 = S[1] * pfVar16[0x11];
        fVar27 = S[2] * pfVar16[0x12];
        fVar30 = S[3] * pfVar16[0x13];
        fVar41 = pfVar16[0x14]; fVar43 = pfVar16[0x15]; fVar46 = pfVar16[0x16]; fVar48 = pfVar16[0x17];
        fVar34 = S[8] * pfVar16[0x18];
        fVar35 = S[9] * pfVar16[0x19];
        fVar37 = S[10] * pfVar16[0x1a];
        fVar38 = S[11] * pfVar16[0x1b];
        fVar49 = pfVar16[0x1c]; fVar50 = pfVar16[0x1d]; fVar51 = pfVar16[0x1e]; fVar52 = pfVar16[0x1f];
        iVar18 = iVar19 + 2;
        *pfVar20 = (((S[0] * pfVar16[0] + fVar40 * pfVar16[4]) + (S[8] * pfVar16[8] + fVar53 * pfVar16[0xc])) +
                    ((S[1] * pfVar16[1] + fVar42 * pfVar16[5]) + (S[9] * pfVar16[9] + fVar54 * pfVar16[0xd]))) +
                   (((S[3] * pfVar16[3] + fVar47 * pfVar16[7]) + (S[11] * pfVar16[0xb] + fVar56 * pfVar16[0xf])) +
                    ((S[2] * pfVar16[2] + fVar45 * pfVar16[6]) + (S[10] * pfVar16[10] + fVar55 * pfVar16[0xe])));
        pfVar20[-0x20] = (((fVar21 + fVar40 * fVar41) + (fVar34 + fVar53 * fVar49)) +
                          ((fVar24 + fVar42 * fVar43) + (fVar35 + fVar54 * fVar50))) +
                         (((fVar30 + fVar47 * fVar48) + (fVar38 + fVar56 * fVar52)) +
                          ((fVar27 + fVar45 * fVar46) + (fVar37 + fVar55 * fVar51)));
        fVar30 = S[15]; fVar27 = S[14]; fVar24 = S[13]; fVar21 = S[12];
        fVar52 = pfVar16[0x1b]; fVar51 = pfVar16[0x1a]; fVar50 = pfVar16[0x19]; fVar49 = pfVar16[0x18];
        fVar48 = pfVar16[0x17]; fVar46 = pfVar16[0x16]; fVar43 = pfVar16[0x15]; fVar41 = pfVar16[0x14];
        pfVar20 = pfVar20 - 0x40;
        pfVar17 = pfVar16 + 0x20;
        fVar40 = fVar3; fVar42 = fVar23; fVar45 = fVar26; fVar47 = fVar29;
        fVar53 = fVar33; fVar54 = fVar36; fVar55 = fVar39; fVar56 = fVar44;
    } while (iVar18 != 8);

    fVar40 = (((S[0] * pfVar16[0x20] + fVar3 * pfVar16[0x24]) + (S[8] * pfVar16[0x28] + fVar33 * pfVar16[0x2c])) +
              ((S[1] * pfVar16[0x21] + fVar23 * pfVar16[0x25]) + (S[9] * pfVar16[0x29] + fVar36 * pfVar16[0x2d]))) +
             (((S[3] * pfVar16[0x23] + fVar29 * pfVar16[0x27]) + (S[11] * pfVar16[0x2b] + fVar44 * pfVar16[0x2f])) +
              ((S[2] * pfVar16[0x22] + fVar26 * pfVar16[0x26]) + (S[10] * pfVar16[0x2a] + fVar39 * pfVar16[0x2e])));
    iVar19 = iVar19 + 3;
    *pfVar20 = fVar40;
    *out2 = fVar40;
    pfVar20 = out2 + 0x20;
    pfVar17 = pfVar16 + 0x30;

    do {
        pfVar16 = pfVar17;
        fVar38 = S[15]; fVar37 = S[14]; fVar35 = S[13]; fVar34 = S[12];
        fVar44 = S[7];  fVar39 = S[6];  fVar36 = S[5];  fVar33 = S[4];
        fVar22 = S[0] * pfVar16[0x10];
        fVar25 = S[1] * pfVar16[0x11];
        fVar28 = S[2] * pfVar16[0x12];
        fVar31 = S[3] * pfVar16[0x13];
        fVar40 = pfVar16[0x14]; fVar42 = pfVar16[0x15]; fVar45 = pfVar16[0x16]; fVar47 = pfVar16[0x17];
        fVar53 = pfVar16[0x18]; fVar54 = pfVar16[0x19]; fVar55 = pfVar16[0x1a]; fVar56 = pfVar16[0x1b];
        fVar3 = pfVar16[0x1c]; fVar23 = pfVar16[0x1d]; fVar26 = pfVar16[0x1e]; fVar29 = pfVar16[0x1f];
        iVar19 = iVar19 + 2;
        *pfVar20 = (((S[0] * pfVar16[0] + fVar41 * pfVar16[4]) + (fVar49 * pfVar16[8] + fVar21 * pfVar16[0xc])) +
                    ((S[1] * pfVar16[1] + fVar43 * pfVar16[5]) + (fVar50 * pfVar16[9] + fVar24 * pfVar16[0xd]))) +
                   (((S[3] * pfVar16[3] + fVar48 * pfVar16[7]) + (fVar52 * pfVar16[0xb] + fVar30 * pfVar16[0xf])) +
                    ((S[2] * pfVar16[2] + fVar46 * pfVar16[6]) + (fVar51 * pfVar16[10] + fVar27 * pfVar16[0xe])));
        pfVar20[0x20] = (((fVar22 + fVar41 * fVar40) + (fVar49 * fVar53 + fVar21 * fVar3)) +
                         ((fVar25 + fVar43 * fVar42) + (fVar50 * fVar54 + fVar24 * fVar23))) +
                        (((fVar31 + fVar48 * fVar47) + (fVar52 * fVar56 + fVar30 * fVar29)) +
                         ((fVar28 + fVar46 * fVar45) + (fVar51 * fVar55 + fVar27 * fVar26)));
        fVar56 = D[15]; fVar55 = D[14]; fVar54 = D[13]; fVar53 = D[12];
        fVar47 = D[11]; fVar45 = D[10]; fVar42 = D[9];  fVar40 = D[8];
        pfVar20 = pfVar20 + 0x40;
        pfVar17 = pfVar16 + 0x20;
        fVar41 = fVar33; fVar43 = fVar36; fVar46 = fVar39; fVar48 = fVar44;
        fVar49 = S[8]; fVar50 = S[9]; fVar51 = S[10]; fVar52 = S[11];
        fVar21 = fVar34; fVar24 = fVar35; fVar27 = fVar37; fVar30 = fVar38;
    } while (iVar19 != 0xf);

    iVar18 = 0;
    pfVar17 = g_synthMatrixB;
    *pfVar20 = (((S[0] * pfVar16[0x20] + fVar33 * pfVar16[0x24]) + (S[8] * pfVar16[0x28] + fVar34 * pfVar16[0x2c])) +
                ((S[1] * pfVar16[0x21] + fVar36 * pfVar16[0x25]) + (S[9] * pfVar16[0x29] + fVar35 * pfVar16[0x2d]))) +
               (((S[3] * pfVar16[0x23] + fVar44 * pfVar16[0x27]) + (S[11] * pfVar16[0x2b] + fVar38 * pfVar16[0x2f])) +
                ((S[2] * pfVar16[0x22] + fVar39 * pfVar16[0x26]) + (S[10] * pfVar16[0x2a] + fVar37 * pfVar16[0x2e])));
    pfVar20 = (float*)(dst + 0x3c0);
    fVar41 = D[4]; fVar43 = D[5]; fVar46 = D[6]; fVar48 = D[7];
    do {
        fVar22 = D[15]; fVar38 = D[14]; fVar37 = D[13]; fVar35 = D[12];
        fVar34 = D[7];  fVar30 = D[6];  fVar44 = D[5];  fVar27 = D[4];
        fVar49 = pfVar17[0];
        const float* pfVar4 = pfVar17 + 1;
        const float* pfVar5 = pfVar17 + 2;
        const float* pfVar6 = pfVar17 + 3;
        const float* pfVar16b = pfVar17 + 4;
        const float* pfVar7 = pfVar17 + 5;
        const float* pfVar8 = pfVar17 + 6;
        const float* pfVar9 = pfVar17 + 7;
        const float* pfVar1 = pfVar17 + 8;
        const float* pfVar10 = pfVar17 + 9;
        const float* pfVar11 = pfVar17 + 10;
        const float* pfVar12 = pfVar17 + 11;
        const float* pfVar2 = pfVar17 + 12;
        const float* pfVar13 = pfVar17 + 13;
        const float* pfVar14 = pfVar17 + 14;
        const float* pfVar15 = pfVar17 + 15;
        fVar25 = D[0] * pfVar17[0x10];
        fVar28 = D[1] * pfVar17[0x11];
        fVar31 = D[2] * pfVar17[0x12];
        fVar32 = D[3] * pfVar17[0x13];
        fVar50 = pfVar17[0x14]; fVar51 = pfVar17[0x15]; fVar52 = pfVar17[0x16]; fVar3 = pfVar17[0x17];
        fVar23 = pfVar17[0x18]; fVar26 = pfVar17[0x19]; fVar29 = pfVar17[0x1a]; fVar33 = pfVar17[0x1b];
        fVar21 = pfVar17[0x1c]; fVar36 = pfVar17[0x1d]; fVar24 = pfVar17[0x1e]; fVar39 = pfVar17[0x1f];
        pfVar17 = pfVar17 + 0x20;
        iVar18 = iVar18 + 2;
        *pfVar20 = (((D[0] * fVar49 + fVar41 * *pfVar16b) + (fVar40 * *pfVar1 + fVar53 * *pfVar2)) +
                    ((D[1] * *pfVar4 + fVar43 * *pfVar7) + (fVar42 * *pfVar10 + fVar54 * *pfVar13))) +
                   (((D[3] * *pfVar6 + fVar48 * *pfVar9) + (fVar47 * *pfVar12 + fVar56 * *pfVar15)) +
                    ((D[2] * *pfVar5 + fVar46 * *pfVar8) + (fVar45 * *pfVar11 + fVar55 * *pfVar14)));
        pfVar20[-0x20] = (((fVar25 + fVar41 * fVar50) + (fVar40 * fVar23 + fVar53 * fVar21)) +
                          ((fVar28 + fVar43 * fVar51) + (fVar42 * fVar26 + fVar54 * fVar36))) +
                         (((fVar32 + fVar48 * fVar3) + (fVar47 * fVar33 + fVar56 * fVar39)) +
                          ((fVar31 + fVar46 * fVar52) + (fVar45 * fVar29 + fVar55 * fVar24)));
        pfVar20 = pfVar20 - 0x40;
        fVar41 = fVar27; fVar43 = fVar44; fVar46 = fVar30; fVar48 = fVar34;
        fVar40 = D[8]; fVar42 = D[9]; fVar45 = D[10]; fVar47 = D[11];
        fVar53 = fVar35; fVar54 = fVar37; fVar55 = fVar38; fVar56 = fVar22;
    } while (iVar18 != 8);

    out2 = out2 + 0x10;
    iVar18 = 8;
    do {
        fVar3 = D[15]; fVar52 = D[14]; fVar51 = D[13]; fVar50 = D[12];
        fVar49 = D[7];  fVar48 = D[6];  fVar46 = D[5];  fVar43 = D[4];
        fVar40 = pfVar17[0];
        const float* pfVar2 = pfVar17 + 1;
        const float* pfVar4 = pfVar17 + 2;
        const float* pfVar5 = pfVar17 + 3;
        const float* pfVar20b = pfVar17 + 4;
        const float* pfVar6 = pfVar17 + 5;
        const float* pfVar7 = pfVar17 + 6;
        const float* pfVar8 = pfVar17 + 7;
        const float* pfVar16c = pfVar17 + 8;
        const float* pfVar9 = pfVar17 + 9;
        const float* pfVar10 = pfVar17 + 10;
        const float* pfVar11 = pfVar17 + 11;
        const float* pfVar1 = pfVar17 + 12;
        const float* pfVar12 = pfVar17 + 13;
        const float* pfVar13 = pfVar17 + 14;
        const float* pfVar14 = pfVar17 + 15;
        fVar23 = D[0] * pfVar17[0x10];
        fVar26 = D[1] * pfVar17[0x11];
        fVar29 = D[2] * pfVar17[0x12];
        fVar33 = D[3] * pfVar17[0x13];
        fVar42 = pfVar17[0x14]; fVar45 = pfVar17[0x15]; fVar47 = pfVar17[0x16]; fVar53 = pfVar17[0x17];
        fVar21 = D[8] * pfVar17[0x18];
        fVar36 = D[9] * pfVar17[0x19];
        fVar24 = D[10] * pfVar17[0x1a];
        fVar39 = D[11] * pfVar17[0x1b];
        fVar54 = pfVar17[0x1c]; fVar55 = pfVar17[0x1d]; fVar56 = pfVar17[0x1e]; fVar41 = pfVar17[0x1f];
        pfVar17 = pfVar17 + 0x20;
        iVar18 = iVar18 + 2;
        *out2 = (((D[0] * fVar40 + fVar27 * *pfVar20b) + (D[8] * *pfVar16c + fVar35 * *pfVar1)) +
                 ((D[1] * *pfVar2 + fVar44 * *pfVar6) + (D[9] * *pfVar9 + fVar37 * *pfVar12))) +
                (((D[3] * *pfVar5 + fVar34 * *pfVar8) + (D[11] * *pfVar11 + fVar22 * *pfVar14)) +
                 ((D[2] * *pfVar4 + fVar30 * *pfVar7) + (D[10] * *pfVar10 + fVar38 * *pfVar13)));
        out2[0x20] = (((fVar23 + fVar27 * fVar42) + (fVar21 + fVar35 * fVar54)) +
                      ((fVar26 + fVar44 * fVar45) + (fVar36 + fVar37 * fVar55))) +
                     (((fVar33 + fVar34 * fVar53) + (fVar39 + fVar22 * fVar41)) +
                      ((fVar29 + fVar30 * fVar47) + (fVar24 + fVar38 * fVar56)));
        out2 = out2 + 0x40;
        fVar27 = fVar43; fVar44 = fVar46; fVar30 = fVar48; fVar34 = fVar49;
        fVar35 = fVar50; fVar37 = fVar51; fVar38 = fVar52; fVar22 = fVar3;
    } while (iVar18 != 0x10);
}

// @ 0x01148710
void CMpegBase::PolySynth2(int iChannel, float* pOutSamples, float* pInSamples)
{
    unsigned char bVar18 = (unsigned char)((mBandOffset[iChannel] - 1) & 0xf);
    mBandOffset[iChannel] = bVar18;
    unsigned int uVar27 = bVar18;
    unsigned int uVar19 = uVar27 & 1;
    unsigned int uVar1 = uVar27 + (uVar19 ^ 1);
    int iVar26 = iChannel * 0x900 + (int)mpLoadedPolySynthHistory;
    float* pfVar20 = (float*)((uVar19 ^ 1) * 0x480 + iVar26);
    SynthesisMatrix(iVar26 + ((uVar27 + uVar19 & 0xf) + uVar19 * 0x120) * 4,
                    (float*)((char*)pfVar20 + uVar1 * 4), pInSamples);

    float* pWin;
    float* pBank;
    switch (uVar1 & 3) {
    case 0: pWin = (float*)g_mw0 - uVar1; pBank = (float*)g_mb0 + uVar1; break;
    case 1: pWin = (float*)g_mw1 - uVar1; pBank = (float*)g_mb1 + uVar1; break;
    case 2: pWin = (float*)g_mw2 - uVar1; pBank = (float*)g_mb2 + uVar1; break;
    default: pWin = (float*)g_mw3 - uVar1; pBank = (float*)g_mb3 + uVar1; break;
    }

    float fVar2, fVar3, fVar4, fVar5, fVar6, fVar7, fVar8, fVar9;
    float fVar10, fVar11, fVar12, fVar13, fVar14, fVar15, fVar16, fVar17;
    float fVar28, fVar29, fVar30, fVar31, fVar32, fVar33, fVar34, fVar35;
    float fVar36, fVar37, fVar38, fVar39, fVar40, fVar41, fVar42, fVar43;
    int iVar26b = 0;
    float* pfVar25 = pWin + 0x20;
    float* pfVar23 = pOutSamples;
    float* pfVar22 = pfVar20;

    fVar28 = pfVar20[4] * pWin[4];
    fVar30 = pfVar20[5] * pWin[5];
    fVar32 = pfVar20[6] * pWin[6];
    fVar34 = pfVar20[7] * pWin[7];
    fVar40 = pfVar20[0xc] * pWin[0xc];
    fVar41 = pfVar20[0xd] * pWin[0xd];
    fVar42 = pfVar20[0xe] * pWin[0xe];
    fVar43 = pfVar20[0xf] * pWin[0xf];
    fVar36 = pfVar20[8] * pWin[8] + *pfVar20 * *pWin;
    fVar37 = pfVar20[9] * pWin[9] + pfVar20[1] * pWin[1];
    fVar38 = pfVar20[10] * pWin[10] + pfVar20[2] * pWin[2];
    fVar39 = pfVar20[11] * pWin[11] + pfVar20[3] * pWin[3];
    float* pfVar24 = pWin + 0x20;
    do {
        pfVar25 = pfVar24;
        pfVar23 = pOutSamples;
        pfVar22 = pfVar20;
        fVar40 = fVar36 + (fVar40 + fVar28);
        fVar41 = fVar37 + (fVar41 + fVar30);
        fVar42 = fVar38 + (fVar42 + fVar32);
        fVar43 = fVar39 + (fVar43 + fVar34);
        fVar28 = pfVar22[0x14] * pfVar25[4];
        fVar30 = pfVar22[0x15] * pfVar25[5];
        fVar32 = pfVar22[0x16] * pfVar25[6];
        fVar34 = pfVar22[0x17] * pfVar25[7];
        fVar36 = pfVar22[0x18] * pfVar25[8] + pfVar22[0x10] * *pfVar25;
        fVar37 = pfVar22[0x19] * pfVar25[9] + pfVar22[0x11] * pfVar25[1];
        fVar38 = pfVar22[0x1a] * pfVar25[10] + pfVar22[0x12] * pfVar25[2];
        fVar39 = pfVar22[0x1b] * pfVar25[0xb] + pfVar22[0x13] * pfVar25[3];
        *pfVar23 = (fVar42 + fVar40) - (fVar43 + fVar41);
        iVar26b = iVar26b + 1;
        fVar40 = pfVar22[0x1c] * pfVar25[0xc];
        fVar41 = pfVar22[0x1d] * pfVar25[0xd];
        fVar42 = pfVar22[0x1e] * pfVar25[0xe];
        fVar43 = pfVar22[0x1f] * pfVar25[0xf];
        pfVar20 = pfVar22 + 0x10;
        pOutSamples = pfVar23 + 1;
        pfVar24 = pfVar25 + 0x20;
    } while (iVar26b != 0xf);

    fVar29 = pfVar25[0x20];
    fVar31 = pfVar25[0x22];
    fVar33 = pfVar25[0x24];
    fVar35 = pfVar25[0x26];
    fVar2 = pfVar25[0x28];
    fVar3 = pfVar25[0x2a];
    fVar4 = pfVar22[0x20];
    fVar5 = pfVar22[0x22];
    fVar6 = pfVar22[0x24];
    fVar7 = pfVar22[0x26];
    fVar8 = pfVar22[0x28];
    fVar9 = pfVar22[0x2a];
    pfVar23[1] = (((fVar38 + fVar32) + fVar42) + ((fVar36 + fVar28) + fVar40)) -
                 (((fVar39 + fVar34) + fVar43) + ((fVar37 + fVar30) + fVar41));
    iVar26b = 0;
    fVar30 = pBank[-0xf];
    fVar32 = pBank[-0xe];
    fVar34 = pBank[-0xd];
    fVar28 = pBank[0];
    fVar36 = pBank[-0xc];
    fVar37 = pBank[-0xb];
    fVar38 = pBank[-10];
    fVar39 = pBank[-9];
    pfVar23[2] = (((fVar9 * fVar3 + fVar5 * fVar31) + fVar7 * fVar35) + pfVar22[0x2e] * pfVar25[0x2e])
                 + (((fVar8 * fVar2 + fVar4 * fVar29) + fVar6 * fVar33) + pfVar22[0x2c] * pfVar25[0x2c]);
    fVar40 = pfVar22[0x10] * pBank[-1];
    fVar41 = pfVar22[0x11] * pBank[-2];
    fVar42 = pfVar22[0x12] * pBank[-3];
    fVar43 = pfVar22[0x13] * pBank[-4];
    fVar29 = pfVar22[0x14] * pBank[-5];
    fVar31 = pfVar22[0x15] * pBank[-6];
    fVar33 = pfVar22[0x16] * pBank[-7];
    fVar35 = pfVar22[0x17] * pBank[-8];
    fVar39 = pfVar22[0x18] * fVar39;
    fVar38 = pfVar22[0x19] * fVar38;
    fVar37 = pfVar22[0x1a] * fVar37;
    fVar36 = pfVar22[0x1b] * fVar36;
    fVar34 = pfVar22[0x1c] * fVar34;
    fVar32 = pfVar22[0x1d] * fVar32;
    fVar30 = pfVar22[0x1e] * fVar30;
    fVar28 = pfVar22[0x1f] * fVar28;
    pfVar20 = pfVar22 + 0x10;
    pfVar24 = pfVar23 + 2;
    do {
        pfVar22 = pfVar24;
        fVar2 = pBank[-0x28];
        fVar3 = pBank[-0x27];
        fVar4 = pBank[-0x26];
        fVar5 = pBank[-0x25];
        fVar29 = fVar34 + fVar29;
        fVar31 = fVar32 + fVar31;
        fVar33 = fVar30 + fVar33;
        fVar35 = fVar28 + fVar35;
        fVar6 = pBank[-0x2c];
        fVar7 = pBank[-0x2b];
        fVar8 = pBank[-0x2a];
        fVar9 = pBank[-0x29];
        fVar10 = pfVar20[-0x10];
        fVar11 = pfVar20[-0xf];
        fVar12 = pfVar20[-0xe];
        fVar13 = pfVar20[-0xd];
        pfVar24 = pfVar22 + 1;
        fVar14 = pfVar20[-8];
        fVar15 = pfVar20[-7];
        fVar16 = pfVar20[-6];
        fVar17 = pfVar20[-5];
        fVar34 = pfVar20[-4] * pBank[-0x2d];
        fVar32 = pfVar20[-3] * pBank[-0x2e];
        fVar30 = pfVar20[-2] * pBank[-0x2f];
        fVar28 = pfVar20[-1] * pBank[-0x20];
        *pfVar24 = 0.0f - ((((fVar36 + fVar43) + fVar35) + ((fVar38 + fVar41) + fVar31)) +
                           (((fVar37 + fVar42) + fVar33) + ((fVar39 + fVar40) + fVar29)));
        fVar39 = fVar14 * fVar9;
        fVar38 = fVar15 * fVar8;
        fVar37 = fVar16 * fVar7;
        fVar36 = fVar17 * fVar6;
        fVar29 = pfVar20[-0xc] * fVar5;
        fVar31 = pfVar20[-0xb] * fVar4;
        fVar33 = pfVar20[-10] * fVar3;
        fVar35 = pfVar20[-9] * fVar2;
        iVar26b = iVar26b + 1;
        fVar40 = fVar10 * pBank[-0x21];
        fVar41 = fVar11 * pBank[-0x22];
        fVar42 = fVar12 * pBank[-0x23];
        fVar43 = fVar13 * pBank[-0x24];
        pfVar20 = pfVar20 + -0x10;
        pBank = pBank + -0x20;
    } while (iVar26b != 0xe);
    pfVar22[2] = 0.0f - (((((fVar36 + fVar43) + fVar35) + fVar28) +
                          (((fVar38 + fVar41) + fVar31) + fVar32)) +
                         ((((fVar37 + fVar42) + fVar33) + fVar30) +
                          (((fVar39 + fVar40) + fVar29) + fVar34)));
}

// @ 0x01148a00
void CMpegBase::SetBuffer(unsigned char* p)
{
    mBufPtr = p;
    mBufPtrBase = p;
    mBufPtrNext = p;
    mShiftReg = 0;
    mShiftRegBits = 0;
}

// @ 0x01148a20
void CMpegBase::ResetLoadedHistory()
{
    if (mpLoadedPolySynthHistory)
        memset(mpLoadedPolySynthHistory, 0, (unsigned int)mChannels * 0x900);
}

// @ 0x01148a40
int CMpegBase::ParseHeaderImpl(unsigned int header)
{
    if ((header & 0xffe00000) != 0xffe00000)
        return -1;

    unsigned char layer = (unsigned char)(4 - ((header >> 17) & 3));
    unsigned char unk09 = (unsigned char)((header >> 9) & 1);
    unsigned char mode6 = (unsigned char)((header >> 6) & 3);
    mMode       = (unsigned char)((header >> 6) & 3);
    mModeExt    = (unsigned char)((header >> 4) & 3);
    mLayer      = layer;
    mCopyright  = (unsigned char)((header >> 3) & 1);
    mErrorProt  = (unsigned char)((header >> 16) & 1);
    mOriginal   = (unsigned char)((header >> 2) & 1);
    mVersion    = (unsigned char)((header >> 19) & 1);
    unsigned char bandIdx = (unsigned char)((header >> 12) & 0xf);
    mPadding    = unk09;
    mBitRateIdx = bandIdx;

    if (layer == 4 || bandIdx == 0xf)
        return -1;

    if ((header & 0x100000) == 0) {
        mLSF = 1;
        mMPEG25 = 1;
    } else {
        mLSF = (unsigned char)(((header >> 19) & 1) == 0);
        mMPEG25 = 0;
    }
    unsigned char bVar2 = (unsigned char)((header >> 10) & 3);
    if (mMPEG25 == 0) {
        mSampFreqIdx = (unsigned char)(mLSF * 3 + bVar2);
        sfreq = (unsigned char)((((mLSF != 0) ? 0 : 3) & 3) + bVar2);
    } else {
        mSampFreqIdx = (unsigned char)((bVar2 & 3) + 6);
    }
    mChannels = (unsigned char)(((header >> 6) & 3) != 3) + 1;
    unsigned short uVar1 = g_sampFreqTable[mSampFreqIdx];
    mSampFreq = uVar1;
    Real_mSampFreq = uVar1;

    if (((header >> 12) & 0xf) == 0)
        return -1;

    int bitrate = g_bitRateTable[((int)mLSF * 3 + layer) * 0x10 + bandIdx];
    mBitRate = bitrate;
    if (layer == 1) {
        cFrameSize = (bitrate * 12000 / Real_mSampFreq + unk09) * 4;
        cFrameSize += -4;
        return 0x180;
    }
    int r = bitrate * 0x23280 / Real_mSampFreq;
    int ret = 0x480;
    cFrameSize = r;
    (void)mode6;
    if (layer == 3 && unk09 != 0) {
        cFrameSize = r >> 1;
        ret = 0x240;
    }
    if (unk09 != 0)
        cFrameSize += 1;
    cFrameSize += -4;
    return ret;
}

// @ 0x01148c00
int CMpegBase::ReadHeader()
{
    mBufPtr = mBufPtrNext;
    mShiftReg = 0;
    mShiftRegBits = 0;
    unsigned int header;
    if (mBufPtrNext == 0)
        header = mHeader;
    else {
        unsigned char* p = mBufPtrNext;
        header = p[0];
        header = (header << 8) | p[1];
        header = (header << 8) | p[2];
        header = (header << 8) | p[3];
    }
    if (ParseHeader(header) == -1)
        return -1;
    mBufPtr += 4;
    mBufPtrNext = (unsigned char*)(mBufPtr + cFrameSize);
    return 0;
}

// @ 0x01148c60
int CMpegBase::PeekHeader()
{
    if (mBufPtr == 0)
        return (ParseHeader(mHeader) != -1) - 1;
    unsigned char* p = mBufPtr;
    unsigned int header = p[0];
    header = (header << 8) | p[1];
    header = (header << 8) | p[2];
    header = (header << 8) | p[3];
    return (ParseHeader(header) != -1) - 1;
}

// @ 0x01148cb0
void CMpegBase::ResetBits()
{
    mBufPtrNext = mBufPtr;
    mShiftReg = 0;
    mShiftRegBits = 0;
}

// @ 0x01148cc0
int CMpegBase::Close()
{
    if (mOpened != 0) {
        mHeader = 0;
        mOpened = 0;
    }
    return 0;
}

// @ 0x01148cd0
CMpegBase::CMpegBase()
{
    mResetSynthRequired = 0;
    mOpened = 0;
    mHeader = 0;
    mpPolySynthHistory = 0;
    mpLoadedPolySynthHistory = 0;
}

// @ 0x01148cf0
int CMpegBase::AllocateSynth(int numChannels)
{
    int size = numChannels * 0x900;
    void* p = g_pSystem->Alloc(size, "PolySynthHistoryF", 0x10, 0);
    mpPolySynthHistory = p;
    if (p == 0)
        return -1;
    memset(p, 0, size);
    return 0;
}

// @ 0x01148d40
CMpegBase::~CMpegBase()
{
    if (mpPolySynthHistory)
        g_pSystem->Free(mpPolySynthHistory, 0);
}

// ---------------------------------------------------------------------------
// EALayer3 stream decoder instance / HELPER_CEALayer3DecF.
// ---------------------------------------------------------------------------
class HELPER_CEALayer3 {
public:
    HELPER_CEALayer3();
    char mData[0x1d4];
};

class EaLayer3DecoderInstance {
public:
    HELPER_CEALayer3 mDecoder;   // +0x000
    int  mDecodedCount;     // +0x1d4
    int  mDecodedStart;     // +0x1d8
    int  mLatency;          // +0x1dc
    bool mReset;            // +0x1e0
    char pad1e1[3];
    float* mpRawIntData;    // +0x1e4
    int  mRawSamples;       // +0x1e8
    int  mRawOffset;        // +0x1ec
    int  mRawSamplesConsumed; // +0x1f0
};

class HELPER_CEALayer3DecF {
public:
    unsigned char* mInputData;        // +0x00
    int mMaxSamples;                  // +0x04
    int mNumChannels;                 // +0x08
    float** mppResidueArrays;         // +0x0c
    int mResidueArrayInstances;       // +0x10
    EaLayer3DecoderInstance* pDecoderInstanceArray;  // +0x14
    int decoderInstanceCount;         // +0x18

    HELPER_CEALayer3DecF();
    void ResetDecoders();
    int Feed(unsigned char* pData, int numSamples, unsigned int numChannels);
};

// @ 0x01148e30
void HELPER_CEALayer3DecF::ResetDecoders()
{
    for (int i = 0; i < decoderInstanceCount; ++i) {
        EaLayer3DecoderInstance* p = (EaLayer3DecoderInstance*)((char*)pDecoderInstanceArray + i * 500);
        p->mLatency = 0x451;
        p->mDecodedCount = 0;
        p->mReset = true;
    }
    mMaxSamples = 0;
}

// @ 0x01148e80
HELPER_CEALayer3DecF::HELPER_CEALayer3DecF()
    : mInputData(0), mMaxSamples(0), mNumChannels(0), mppResidueArrays(0),
      mResidueArrayInstances(0), pDecoderInstanceArray(0), decoderInstanceCount(0)
{
    ResetDecoders();
    mppResidueArrays = 0;
}

// @ 0x01148eb0
int HELPER_CEALayer3DecF::Feed(unsigned char* pData, int numSamples, unsigned int numChannels)
{
    if (mMaxSamples > 0)
        return -1;
    mInputData = pData;
    mMaxSamples = numSamples;
    if (mppResidueArrays == 0) {
        unsigned int remainder = numChannels & 0x80000001;
        mNumChannels = numChannels;
        if ((int)remainder < 0)
            remainder = (remainder - 1 | 0xfffffffe) + 1;
        if (remainder == 0)
            mResidueArrayInstances = numChannels;
        else
            mResidueArrayInstances = numChannels + 1;
        if (numChannels == 1 || numChannels == 2)
            decoderInstanceCount = 1;
        else {
            int n = (int)numChannels / 2;
            if (remainder != 0)
                n = n + 1;
            decoderInstanceCount = n;
        }
        mppResidueArrays = (float**)g_pSystem->Alloc(
            mResidueArrayInstances * 0x1b04 + decoderInstanceCount * 500, "CEALayer3DecF-Arrays", 0x10, 0);
        if (mppResidueArrays == 0)
            return -1;
        float* pInst = (float*)(mppResidueArrays + mResidueArrayInstances);
        int i = 0;
        if (mResidueArrayInstances > 0) {
            do {
                mppResidueArrays[i] = pInst;
                ++i;
                pInst = (float*)((char*)pInst + 0x1b00);
            } while (i < mResidueArrayInstances);
        }
        pDecoderInstanceArray = (EaLayer3DecoderInstance*)pInst;
        int j = 0;
        if (decoderInstanceCount > 0) {
            int off = 0;
            do {
                char* p = (char*)pDecoderInstanceArray + off;
                if (p != 0) {
                    new (p) HELPER_CEALayer3();   // HELPER_CEALayer3 ctor, 0x1159900
                }
                *(unsigned int*)(p + 0x1dc) = 0x451;
                *(unsigned int*)(p + 0x1d4) = 0;
                *(unsigned int*)(p + 0x1e4) = 0;
                *(unsigned char*)(p + 0x1e0) = 1;
                ++j;
                off += 500;
            } while (j < decoderInstanceCount);
        }
    }
    return 0;
}

// @ 0x01148da0
void ScaleSamples(float* pData, float scale, int numSamples)
{
    if (numSamples <= 0)
        return;
    if ((((unsigned int)pData) & 0xf) == 0 && ((unsigned int)numSamples & 0xf) == 0) {
        float* pEnd = pData + numSamples;
        do {
            pData[0] *= scale;  pData[1] *= scale;  pData[2] *= scale;  pData[3] *= scale;
            pData[4] *= scale;  pData[5] *= scale;  pData[6] *= scale;  pData[7] *= scale;
            pData[8] *= scale;  pData[9] *= scale;  pData[10] *= scale; pData[11] *= scale;
            pData[12] *= scale; pData[13] *= scale; pData[14] *= scale; pData[15] *= scale;
            pData += 16;
        } while (pData != pEnd);
        return;
    }
    float* pEnd = pData + numSamples;
    for (; pData < pEnd; ++pData)
        *pData = *pData * scale;
}

}}} // namespace rw::audio::core
