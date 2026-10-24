// Slice s011666d0 — EA RenderWare Audio MPEG layer-3 decoder (rw::audio::core, EaLayer3Dec):
// 36-point IMDCT of one long block with windowing.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//
// The algorithm is mpg123's dct36 (two prefix-sum passes, 9-point DCTs on the even and odd
// halves, tfcos36 butterflies) with all COS9 constants doubled, and without the overlap-add:
// the 36 windowed outputs are written straight to `out`. The hybrid buffers are interleaved:
// input and output samples are 4 floats apart.
//
// The original is a TU-local (static) helper with a register convention
// (eax = in, ecx = window, edx = out); it is called at 0x01167474/0x01167480/0x01167580.
// Imdct36Caller is only a stand-in caller so that cl emits the static helper with the
// same kind of convention; it is not part of the slice.
#include "types.h"

#define IN(i)  in[(i) * 4]
#define OUT(i) out[(i) * 4]

// @ 0x011666d0
static void Imdct36(float* in, float* out, const float* win)
{
    IN(17) += IN(16); IN(16) += IN(15); IN(15) += IN(14); IN(14) += IN(13);
    IN(13) += IN(12); IN(12) += IN(11); IN(11) += IN(10); IN(10) += IN(9);
    IN(9)  += IN(8);  IN(8)  += IN(7);  IN(7)  += IN(6);  IN(6)  += IN(5);
    IN(5)  += IN(4);  IN(4)  += IN(3);  IN(3)  += IN(2);  IN(2)  += IN(1);
    IN(1)  += IN(0);

    IN(17) += IN(15); IN(15) += IN(13); IN(13) += IN(11); IN(11) += IN(9);
    IN(9)  += IN(7);  IN(7)  += IN(5);  IN(5)  += IN(3);  IN(3)  += IN(1);

    // even half, even samples (2*cos(k*pi/18): c1 1.9696, c2 1.8794, c4 1.5321, c5 1.2856, c7 0.6840, c8 0.3473)
    float t  = IN(12) + IN(0) * 2.0f;
    float e1 = IN(4) * 1.8793852f + IN(8) * 1.5320889f + IN(16) * 0.34729636f + t;
    float e2 = IN(4) + IN(0) * 2.0f - IN(8) - IN(12) - IN(12) - IN(16);
    float e3 = t - IN(4) * 0.34729636f - IN(8) * 1.8793852f + IN(16) * 1.5320889f;
    float e4 = t - IN(4) * 1.5320889f + IN(8) * 0.34729636f - IN(16) * 1.8793852f;
    float e5 = IN(0) - IN(4) + IN(8) - IN(12) + IN(16);

    // even half, odd samples
    float s6 = IN(6) * 1.7320508f;
    float o1 = IN(2) * 1.9696155f + s6 + IN(10) * 1.2855753f + IN(14) * 0.6840403f;
    float o2 = (IN(2) - IN(10) - IN(14)) * 1.7320508f;
    float o3 = IN(2) * 1.2855753f - s6 - IN(10) * 0.6840403f + IN(14) * 1.9696155f;
    float o4 = IN(2) * 0.6840403f - s6 + IN(10) * 1.9696155f - IN(14) * 1.2855753f;

    // odd half, even samples
    float u  = IN(13) + IN(1) * 2.0f;
    float f1 = IN(5) * 1.8793852f + IN(9) * 1.5320889f + IN(17) * 0.34729636f + u;
    float f2 = IN(5) + IN(1) * 2.0f - IN(9) - IN(13) - IN(13) - IN(17);
    float f3 = u - IN(5) * 0.34729636f - IN(9) * 1.8793852f + IN(17) * 1.5320889f;
    float f4 = u - IN(5) * 1.5320889f + IN(9) * 0.34729636f - IN(17) * 1.8793852f;
    float f5 = (IN(1) - IN(5) + IN(9) - IN(13) + IN(17)) * 0.70710677f;

    // odd half, odd samples
    float s7 = IN(7) * 1.7320508f;
    float g1 = IN(3) * 1.9696155f + s7 + IN(11) * 1.2855753f + IN(15) * 0.6840403f;
    float g2 = (IN(3) - IN(11) - IN(15)) * 1.7320508f;
    float g3 = IN(3) * 1.2855753f - s7 - IN(11) * 0.6840403f + IN(15) * 1.9696155f;
    float g4 = IN(3) * 0.6840403f - s7 + IN(11) * 1.9696155f - IN(15) * 1.2855753f;

    // tfcos36 butterflies: sum0 + sum1 -> out[26-v], out[27+v];
    //                      sum0 - sum1 -> out[8-v],  out[9+v]
    float sum0, sum1;
    float tmp[18];  // tmp[v] = sum (v = 0..8), tmp[17 - v] = difference
    sum0 = o1 + e1; sum1 = (g1 + f1) * 0.5019099f;  tmp[0] = sum1 + sum0; tmp[17] = sum0 - sum1;
    sum0 = o2 + e2; sum1 = (g2 + f2) * 0.51763809f; tmp[1] = sum1 + sum0; tmp[16] = sum0 - sum1;
    sum0 = o3 + e3; sum1 = (g3 + f3) * 0.55168897f; tmp[2] = sum1 + sum0; tmp[15] = sum0 - sum1;
    sum0 = o4 + e4; sum1 = (g4 + f4) * 0.61038727f; tmp[3] = sum1 + sum0; tmp[14] = sum0 - sum1;
    sum0 = e5;      sum1 = f5;                       tmp[4] = sum1 + sum0; tmp[13] = sum0 - sum1;
    sum0 = e4 - o4; sum1 = (f4 - g4) * 0.8717234f;  tmp[5] = sum1 + sum0; tmp[12] = sum0 - sum1;
    sum0 = e3 - o3; sum1 = (f3 - g3) * 1.1831008f;  tmp[6] = sum1 + sum0; tmp[11] = sum0 - sum1;
    sum0 = e2 - o2; sum1 = (f2 - g2) * 1.9318516f;  tmp[7] = sum1 + sum0; tmp[10] = sum0 - sum1;
    sum0 = e1 - o1; sum1 = (f1 - g1) * 5.7368565f;  tmp[8] = sum1 + sum0; tmp[9] = sum0 - sum1;

    OUT(0)  = tmp[9] * win[0];
    OUT(1)  = win[1]  * tmp[10];
    OUT(2)  = win[2]  * tmp[11];
    OUT(3)  = win[3]  * tmp[12];
    OUT(4)  = win[4]  * tmp[13];
    OUT(5)  = win[5]  * tmp[14];
    OUT(6)  = win[6]  * tmp[15];
    OUT(7)  = win[7]  * tmp[16];
    OUT(8)  = win[8]  * tmp[17];
    OUT(9)  = win[9]  * tmp[17];
    OUT(10) = win[10] * tmp[16];
    OUT(11) = win[11] * tmp[15];
    OUT(12) = win[12] * tmp[14];
    OUT(13) = win[13] * tmp[13];
    OUT(14) = win[14] * tmp[12];
    OUT(15) = win[15] * tmp[11];
    OUT(16) = win[16] * tmp[10];
    OUT(17) = win[17] * tmp[9];
    OUT(18) = win[18] * tmp[8];
    OUT(19) = win[19] * tmp[7];
    OUT(20) = win[20] * tmp[6];
    OUT(21) = win[21] * tmp[5];
    OUT(22) = win[22] * tmp[4];
    OUT(23) = win[23] * tmp[3];
    OUT(24) = win[24] * tmp[2];
    OUT(25) = win[25] * tmp[1];
    OUT(26) = win[26] * tmp[0];
    OUT(27) = win[27] * tmp[0];
    OUT(28) = win[28] * tmp[1];
    OUT(29) = win[29] * tmp[2];
    OUT(30) = win[30] * tmp[3];
    OUT(31) = win[31] * tmp[4];
    OUT(32) = win[32] * tmp[5];
    OUT(33) = win[33] * tmp[6];
    OUT(34) = win[34] * tmp[7];
    OUT(35) = win[35] * tmp[8];
}

// Stand-in caller (not part of the slice): keeps the static helper emitted with a
// register convention, like the original caller at 0x01167474.
extern const float kImdctWindows[4][36];  // 0x014d7370
void Imdct36Caller(float* in, float* out)
{
    Imdct36(in, out, kImdctWindows[0]);
    Imdct36(in + 1, out + 1, kImdctWindows[0]);
}

// ---------------------------------------------------------------------------
// 0x01167190 / 0x011673E0: the eight-subblock driver around the scalar IMDCT helpers.
// The core is /GL + /LTCG code with register ABIs (HELPER_Imdct12X1 takes `out` in eax and
// its input on the stack, see s01145d10/s01165820); cl has no spelling for those, so the
// helpers are declared with plain argument lists and the call sequences differ from retail.
// ---------------------------------------------------------------------------

extern "C" void* __cdecl memset(void* pDst, int nValue, unsigned int nBytes);

// 0x011661b0: 12-point IMDCT of one lane (retail: out in eax, in on the stack).
void HELPER_Imdct12X1(float* pOut, float* pIn);

// 0x016f16ec: the module's allocator (import pointer).
extern void* (*const g_pfnAudioAlloc)(unsigned int nBytes);

// One band's lapping state; the band table at +0x58 holds entries of 0x18 bytes.
struct BandState
{
    unsigned char mPad00[7];         // +0x00
    bool          mbLeftWindow;      // +0x07 the previous block overlaps this one
    unsigned char mnWindowSequence;  // +0x08 2 = eight short windows (12-point IMDCTs)
    bool          mbRightWindow;     // +0x09 this block overlaps the next one
    unsigned char mPad0a[0x0e];      // +0x0a
};

// rw::audio::core::HELPER_Imdct12X4Implementation: renders the eight hybrid subblocks of one
// granule for one channel. Each subblock runs four 36-point IMDCTs (long window) or four
// 12-point IMDCTs (eight-short sequence), is overlap-added into the output and leaves the
// second half of its fresh samples as that lane's 72-sample history in the work buffer.
class HELPER_Imdct12X4Implementation
{
public:
    void Transform(unsigned int nChannel, unsigned int nBlock, float* pOutput);  // 0x011673e0

    unsigned char mPad000[0x48];   // +0x000
    unsigned char mnChannelCount;  // +0x048
    unsigned char mPad049[0x0f];   // +0x049
    BandState     mBands[14];      // +0x058 entry = nBlock + 2 * nChannel
    unsigned char mPad1a8[8];      // +0x1a8
    void*         mpWorkBuffer;    // +0x1b0 mnChannelCount * 0x900 bytes (8 blocks of 72 floats)
};

// Overlap-adds the fresh samples in `pIn` with the lane history in `pHistory` into `pOut`,
// then rotates that history: the second half of the fresh block becomes the new history.
// The four lanes are interleaved (stride 4 floats).
// The original body is fully unrolled (18 lines per lane); the two halves are kept apart:
// first the overlap-add of the fresh 72 samples, then the rotation of the history.
#define ADD(k)  pOut[lane + (k)] = pIn[lane + (k)] + pHistory[lane + (k)]
#define ROT(k)  pHistory[lane + (k)] = pIn[lane + (k) + 72]

// @ 0x01167190
void FUN_01167190(float* pOut, const float* pIn, float* pHistory)
{
    for (unsigned int lane = 0; lane < 4; ++lane)
    {
        ADD(0);  ADD(4);  ADD(8);  ADD(12); ADD(16); ADD(20);
        ADD(24); ADD(28); ADD(32); ADD(36); ADD(40); ADD(44);
        ADD(48); ADD(52); ADD(56); ADD(60); ADD(64); ADD(68);

        ROT(0);  ROT(4);  ROT(8);  ROT(12); ROT(16); ROT(20);
        ROT(24); ROT(28); ROT(32); ROT(36); ROT(40); ROT(44);
        ROT(48); ROT(52); ROT(56); ROT(60); ROT(64); ROT(68);
    }
}

// @ 0x011673e0
void HELPER_Imdct12X4Implementation::Transform(unsigned int nChannel, unsigned int nBlock, float* pOutput)
{
    if (mpWorkBuffer == 0)
    {
        unsigned int nBytes = (unsigned int)mnChannelCount * 0x900;
        mpWorkBuffer = g_pfnAudioAlloc(nBytes);
        if (mpWorkBuffer == 0)
            pOutput[0] = 0.0f;
        else
            memset(mpWorkBuffer, 0, nBytes);
    }

    unsigned int nBand = nBlock + 2 * nChannel;
    float* pWork = (float*)((char*)mpWorkBuffer + nChannel * 0x900);
    float sTime[144];
    unsigned int nDone = 0;

    if (mBands[nBand].mbLeftWindow && mBands[nBand].mbRightWindow)
    {
        Imdct36(pOutput + 0, sTime + 0, kImdctWindows[0]);
        Imdct36(pOutput + 1, sTime + 1, kImdctWindows[0]);
        HELPER_Imdct12X1(sTime + 2, pOutput + 2);
        HELPER_Imdct12X1(sTime + 3, pOutput + 3);
        FUN_01167190(pOutput, sTime, pWork);
        nDone = 1;
    }

    if (mBands[nBand].mnWindowSequence == 2)
    {
        if (nDone < 8)
        {
            float* pBlock = pOutput + nDone * 72;
            unsigned int nLeft = 8 - nDone;
            do
            {
                HELPER_Imdct12X1(sTime + 0, pBlock + 0);
                HELPER_Imdct12X1(sTime + 1, pBlock + 1);
                HELPER_Imdct12X1(sTime + 2, pBlock + 2);
                HELPER_Imdct12X1(sTime + 3, pBlock + 3);
                FUN_01167190(pBlock, sTime, pWork);
                pBlock += 72;
                pWork += 72;
            } while (--nLeft != 0);
        }
    }
    else if (nDone < 8)
    {
        const float* pWindow = kImdctWindows[mBands[nBand].mnWindowSequence];
        float* pBlock = pOutput + nDone * 72;
        unsigned int nLeft = 8 - nDone;
        do
        {
            for (unsigned int j = 0; j < 4; ++j)
                Imdct36(pBlock + j, sTime + j, pWindow);
            FUN_01167190(pBlock, sTime, pWork);
            pBlock += 72;
            pWork += 72;
        } while (--nLeft != 0);
    }
}
