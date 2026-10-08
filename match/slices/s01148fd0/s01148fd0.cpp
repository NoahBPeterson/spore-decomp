// Slice s01148fd0 -- RenderWare 4 rw::audio::core EALayer3 stream decoder.
// Build: VC .NET 2003 (cl 13.10) + /GL /LTCG.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE2
#include <string.h>

#pragma function(memset)

namespace rw { namespace audio { namespace core {

class System {
public:
    void* Alloc(unsigned int size, const char* name, unsigned int align, unsigned int flags);
    void  Free(void* p, unsigned int flags);
};
extern System* g_pSystem;                 // 0x16e61a8
extern void ScaleSamples(float* pData, float scale, int numSamples);  // 0x1148da0

class Decoder {
public:
    void** vftable;                           // +0x00
    System* mpSystem;                         // +0x04
    void* mpDecoder;                          // +0x08
    void* mpReleaseEvent;                     // +0x0c
    void* mSampleBufferStorage;               // +0x10
    void* mpDecodeEvent;                      // +0x14
    unsigned int mGuid;                       // +0x18
    int mDecodeSlotSamplesDecoded;            // +0x1c
    unsigned int mInstanceSize;               // +0x20
    unsigned int mRequestDescOffset;          // +0x24
    unsigned int mSampleBufferOffset;         // +0x28
    unsigned short mDecodedSamplesAvailable;  // +0x2c
    unsigned char mNumChannels;               // +0x2e
    unsigned char mFeedSlot;                  // +0x2f
    unsigned char mPrepareSlot;               // +0x30
    unsigned char mDecodeSlot;                // +0x31
    unsigned char mMaxSlots;                  // +0x32
    unsigned char mIsBlockBased;              // +0x33

    int GetCurrentRequestDesc(char* param_2, int* param_3, int param_4,
                              unsigned int* param_5, unsigned int* param_6,
                              unsigned int* param_7, int param_8);
};

class EALayer3Core;
class EaLayer3DecoderInstance;

// The embedded decoder object: CMpegBase at +0, HELPER_CMpegLayer3Base up to
// +0x1d0, then mpDecodedFrame.  Virtual slots +8/+0xc/+0x14 are the three the
// granule parser calls.
class HELPER_CEALayer3 {
public:
    ~HELPER_CEALayer3();                      // non-virtual (direct call in the dtor)
    virtual int v0();                         // slot 0 (+0)
    virtual int v1b();                        // slot 1 (+4)
    virtual int v2(void* p);                  // slot 2 (+8)   parse header
    virtual int v3(void* p);                  // slot 3 (+0xc) feed
    virtual int v4();                         // slot 4 (+0x10) get info
    virtual int v5();                         // slot 5 (+0x14) decode granule
    int Real_mSampFreq;                       // +0x04
    int mSampFreq;                            // +0x08
    int mBitRate;                             // +0x0c
    int cFrameSize;                           // +0x10
    unsigned short mFrameSamples;             // +0x14
    unsigned char mLayer;                     // +0x16
    unsigned char mOpened;                    // +0x17
    unsigned char mChannels;                  // +0x18
    char pad19[0x1b0];                        // +0x19 .. +0x1c8
    void* mTail1c8;                           // +0x1c8
    int   mFrameStart;                        // +0x1cc
    float* mpDecodedFrame;                    // +0x1d0
};

class EaLayer3DecoderInstance {
public:
    HELPER_CEALayer3 mDecoder;                // +0x000
    int  mDecodedCount;                       // +0x1d4
    int  mDecodedStart;                       // +0x1d8
    int  mLatency;                            // +0x1dc
    bool mReset;                              // +0x1e0
    char pad1e1[3];
    float* mpRawIntData;                      // +0x1e4
    int  mRawSamples;                         // +0x1e8
    int  mRawOffset;                          // +0x1ec
    int  mRawSamplesConsumed;                 // +0x1f0
};

class EaLayer3DecBase : public Decoder {
public:
    EALayer3Core*  mpLoadedEALayer3Core;      // +0x34
    unsigned char* mpEncodedSample;           // +0x38
    EALayer3Core** mppEaLayer3Core;           // +0x3c
    int  mRemainingSamples;                   // +0x40
    int  mTotalChannels;                      // +0x44
    int  mNumEaLayer3CoreInstances;           // +0x48
    int  mLatency;                            // +0x4c
    int  mSkipSamples;                        // +0x50
    char mVersion;                            // +0x54
    bool mNewFeed;                            // +0x55

    void SkipBlocks();
    int DecodeEvent(char* param_2);
};

class HELPER_CEALayer3DecF {
public:
    unsigned char* mInputData;                // +0x00
    int mMaxSamples;                          // +0x04
    int mNumChannels;                         // +0x08
    float** mppResidueArrays;                 // +0x0c
    int mResidueArrayInstances;               // +0x10
    EaLayer3DecoderInstance* pDecoderInstanceArray;  // +0x14
    int decoderInstanceCount;                 // +0x18

    ~HELPER_CEALayer3DecF();
    int DecodeGranules(int a2, int a3, int a4, int a5, int* a6);
    int Decode(int a2, int* a3);
};

// @ 0x01148fd0
HELPER_CEALayer3DecF::~HELPER_CEALayer3DecF()
{
    if (mppResidueArrays != 0) {
        for (int i = 0; i < decoderInstanceCount; ++i)
            ((HELPER_CEALayer3*)((char*)pDecoderInstanceArray + i * 500))->~HELPER_CEALayer3();
        if (mppResidueArrays != 0)
            g_pSystem->Free(mppResidueArrays, 0);
    }
}

// @ 0x01149020
int HELPER_CEALayer3DecF::DecodeGranules(int a2, int a3, int a4, int a5, int* a6)
{
    int iVar6 = a4;                       // channel pair index
    int local_1c = 0;
    int local_8[2];
    local_8[1] = a3;
    local_8[0] = a2;
    int local_10 = 0;                     // running sample offset
    *a6 = 0;
    for (;;) {
        if (a5 == 0)
            return local_1c;
        unsigned char uVar2 = *mInputData;
        unsigned char* puVar7 = mInputData + 1;
        mInputData = puVar7;
        EaLayer3DecoderInstance* inst = pDecoderInstanceArray + iVar6;
        HELPER_CEALayer3* pv = &inst->mDecoder;
        if (inst->mReset == false) {
            pv->v3(puVar7);
        } else {
            int iVar8 = pv->v2(puVar7);
            if (iVar8 < 0) {
                mInputData = mInputData - 1;
                return -1;
            }
            inst->mReset = false;
        }
        int iVar8 = pv->v5();
        if (iVar8 < 0) {
            float* pf = inst->mDecoder.mpDecodedFrame;
            if (pf != 0)
                memset(pf, 0, (unsigned int)inst->mDecoder.mChannels *
                               (unsigned int)inst->mDecoder.mFrameSamples * 4);
        }
        iVar8 = inst->mDecoder.cFrameSize;
        mInputData = mInputData + iVar8;
        local_1c = local_1c + 1 + iVar8;
        inst->mDecodedCount = 0x240;
        inst->mDecodedStart = 0;
        if (uVar2 != 0) {
            unsigned char* p = mInputData;
            unsigned int u = *(unsigned int*)p;
            inst->mRawSamples = (int)((u >> 24) | ((u >> 16) & 0xff00) | ((u >> 8) & 0xff0000) | (u << 24));
            u = *(unsigned int*)(p + 4);
            inst->mRawOffset = (int)((u >> 24) | ((u >> 16) & 0xff00) | ((u >> 8) & 0xff0000) | (u << 24));
            inst->mpRawIntData = (float*)g_pSystem->Alloc(
                (unsigned int)inst->mDecoder.mChannels * inst->mRawSamples * 4,
                "CEALayer3DecF-rawSamples", 0x10, 0);
            if (inst->mpRawIntData == 0)
                return -1;
            inst->mRawSamplesConsumed = 0;
            float* pfVar9 = inst->mpRawIntData;
            p += 8;
            int n = 0;
            if (0 < inst->mRawSamples) {
                do {
                    unsigned short w = *(unsigned short*)p;
                    pfVar9[0] = (float)(short)((w << 8) | (w >> 8));
                    ++n;
                    p += 2;
                    ++pfVar9;
                } while (n < inst->mRawSamples);
            }
            if (1 < inst->mDecoder.mChannels && (n = 0, 0 < inst->mRawSamples)) {
                do {
                    unsigned short w = *(unsigned short*)p;
                    pfVar9[0] = (float)(short)((w << 8) | (w >> 8));
                    ++n;
                    p += 2;
                    ++pfVar9;
                } while (n < inst->mRawSamples);
            }
            iVar8 = (int)((unsigned int)inst->mDecoder.mChannels * inst->mRawSamples * 2 + 8);
            mInputData = mInputData + iVar8;
            local_1c = local_1c + iVar8;
        }
        int iVar11 = 0;
        iVar8 = inst->mLatency;
        if (iVar8 < 1) {
            *a6 = *a6 + inst->mDecodedCount;
        } else if (iVar8 < inst->mDecodedCount) {
            inst->mDecodedStart = inst->mDecodedStart + iVar8;
            inst->mDecodedCount = inst->mDecodedCount - inst->mLatency;
            inst->mLatency = 0;
            *a6 = *a6 + inst->mDecodedCount;
        } else {
            inst->mLatency = inst->mLatency - inst->mDecodedCount;
            inst->mDecodedCount = 0;
        }
        int param_2 = inst->mDecodedCount;
        if (0 < param_2) {
            if (0x240 < param_2)
                param_2 = 0x240;
            if (inst->mDecoder.mChannels != 0) {
                int off = 0;
                do {
                    memcpy((void*)(local_8[iVar11] + local_10 * 4),
                           inst->mDecoder.mpDecodedFrame + inst->mDecodedStart + off,
                           param_2 * 4);
                    ++iVar11;
                    off += 0x240;
                } while (iVar11 < (int)(unsigned int)inst->mDecoder.mChannels);
            }
            float* pr = inst->mpRawIntData;
            if (pr != 0) {
                int avail = inst->mRawSamples - inst->mRawSamplesConsumed;
                int cnt = param_2;
                if (avail <= param_2)
                    cnt = avail;
                int ch = 0;
                if (inst->mDecoder.mChannels != 0) {
                    do {
                        memcpy((void*)(local_8[ch] + (inst->mRawOffset + local_10) * 4),
                               pr + inst->mRawSamplesConsumed, cnt * 4);
                        pr = pr + inst->mRawSamples;
                        ++ch;
                    } while (ch < (int)(unsigned int)inst->mDecoder.mChannels);
                }
                inst->mRawSamplesConsumed = inst->mRawSamplesConsumed + cnt;
                if (inst->mRawSamplesConsumed == inst->mRawSamples && inst->mpRawIntData != 0) {
                    g_pSystem->Free(inst->mpRawIntData, 0);
                    inst->mpRawIntData = 0;
                }
            }
            inst->mDecodedStart = inst->mDecodedStart + param_2;
            local_10 = local_10 + param_2;
            inst->mDecodedCount = inst->mDecodedCount - param_2;
        }
        a5 = a5 - 1;
    }
}

// @ 0x01149490
int HELPER_CEALayer3DecF::Decode(int a2, int* a3)
{
    int total = 0;
    *a3 = 0;
    unsigned char* puVar1 = mInputData;
    int local_14 = 0;
    bool bVar2 = false;
    int local_10 = 0;
    unsigned char local_15 = 0;
    int iVar5 = 0;
    if (0 < mResidueArrayInstances) {
        do {
            if (bVar2) {
                mInputData = mInputData + 1;
            } else {
                local_15 = *mInputData;
                mInputData = mInputData + 1;
                bVar2 = true;
            }
            int iVar3 = DecodeGranules((int)mppResidueArrays[iVar5],
                                       (int)mppResidueArrays[iVar5 + 1],
                                       local_10, local_15, a3);
            int iVar4 = 2;
            if (iVar5 == mNumChannels - 1)
                iVar4 = 1;
            for (int iVar6 = iVar5; iVar6 < iVar4 + iVar5; ++iVar6)
                memcpy((void*)(*(int*)(a2 + 4) + (unsigned int)*(unsigned short*)(a2 + 0xe) * iVar6 * 4),
                       mppResidueArrays[iVar6], *a3 * 4);
            if (iVar3 < 0) {
                mInputData = puVar1;
                return -1;
            }
            local_14 = local_14 + 1 + iVar3;
            local_10 = local_10 + 1;
            iVar5 = iVar5 + 2;
        } while (iVar5 < mResidueArrayInstances);
    }
    if (mMaxSamples < *a3)
        *a3 = mMaxSamples;
    if (-1 < mMaxSamples)
        mMaxSamples = mMaxSamples - *a3;
    return local_14;
}

// @ 0x011495b0
void EaLayer3DecBase::SkipBlocks()
{
    int iVar4 = mSkipSamples;
    if (0 < iVar4) {
        if (mNewFeed == false || 0x2e < iVar4 || mVersion == 1) {
            mLatency = 0;
        } else {
            mLatency = mLatency + -0x240;
        }
        int iVar7 = 0;
        int iVar6;
        if (mNewFeed == false || mVersion == 1) {
            iVar6 = iVar4 / 0x240;
            iVar7 = iVar6 * 0x240;
        } else {
            iVar6 = (iVar4 + 0x451) / 0x240;
            if (1 < iVar6)
                iVar7 = iVar6 * 0x240 + -0x451;
        }
        mSkipSamples = iVar4 - iVar7;
        int descOff = (int)mRequestDescOffset + (unsigned int)mDecodeSlot * 0x14;
        int iVar7b = (iVar6 + -1) / 10;
        if (mVersion == 0)
            iVar7b = iVar6;
        char* desc = (char*)this + descOff;
        void* base = (*(int*)(desc + 0xc) != 0) ? desc : 0;
        unsigned short* puVar1 = (unsigned short*)*(void**)((char*)base + 4);

        int local_10 = 0;
        int local_c = 0;
        iVar4 = 0;
        if (1 < iVar7b) {
            int iVar3 = (iVar7b - 2) / 2 + 1;
            iVar4 = iVar3 * 2;
            do {
                unsigned short a = puVar1[0];
                local_10 += (short)((a << 8) | (a >> 8));
                unsigned short b = puVar1[1];
                local_c += (short)((b << 8) | (b >> 8));
                puVar1 += 2;
                --iVar3;
            } while (iVar3 != 0);
        }
        int iVar3b = 0;
        if (iVar4 < iVar7b) {
            unsigned short a = *puVar1;
            iVar3b = (short)((a << 8) | (a >> 8));
        }
        iVar3b = iVar3b + local_10 + local_c;
        iVar6 = iVar6 + iVar7b * -10;
        if (0 < iVar6) {
            unsigned char* puVar5 = mpEncodedSample + iVar3b;
            do {
                if (0 < mNumEaLayer3CoreInstances) {
                    int n = mNumEaLayer3CoreInstances;
                    do {
                        unsigned int uVar2 = (((unsigned int)puVar5[0] << 8) | puVar5[1]) & 0xfff;
                        puVar5 += uVar2;
                        iVar3b += uVar2;
                        --n;
                    } while (n != 0);
                }
                --iVar6;
            } while (iVar6 != 0);
        }
        mpEncodedSample = mpEncodedSample + iVar3b;
    }
}

// @ 0x01149760
void __stdcall ConvertSamples(int* param_1, unsigned char* param_2, int param_3, unsigned int param_4)
{
    unsigned int uVar4 = param_4;
    if (param_3 == 2) {
        float* pf3 = (float*)param_1[0];
        float* pf6 = (float*)param_1[1];
        unsigned int n = param_4 >> 2;
        unsigned char* p = param_2;
        if (n != 0) {
            unsigned char* q = param_2 + 9;
            do {
                pf3[0] = (float)(short)((p[0] << 8) | p[1]);
                pf3[1] = (float)(short)((p[4] << 8) | p[5]);
                pf3[2] = (float)(short)((p[8] << 8) | p[9]);
                pf3[3] = (float)(short)((p[12] << 8) | p[13]);
                pf6[0] = (float)(short)((p[2] << 8) | p[3]);
                pf6[1] = (float)(short)((p[6] << 8) | p[7]);
                pf6[2] = (float)(short)((p[10] << 8) | p[11]);
                pf6[3] = (float)(short)((p[14] << 8) | p[15]);
                pf3 += 4; pf6 += 4; p += 0x10; q += 0x10; --n;
            } while (n != 0);
        }
        unsigned int r = param_4 - (param_4 & 0xfffffffc);
        if (r != 0) {
            do {
                *pf3 = (float)(short)((p[0] << 8) | p[1]);
                *pf6 = (float)(short)((p[2] << 8) | p[3]);
                ++pf3; ++pf6; p += 4; --r;
            } while (r != 0);
        }
    } else {
        float* pf3 = (float*)param_1[0];
        unsigned int uVar5 = param_4 & 0xfffffffc;
        unsigned int uVar8 = param_4 >> 2;
        unsigned char* p = param_2;
        if (uVar8 != 0) {
            unsigned char* q = param_2 + 5;
            do {
                pf3[0] = (float)(short)((p[0] << 8) | p[1]);
                pf3[1] = (float)(short)((p[2] << 8) | p[3]);
                pf3[2] = (float)(short)((p[4] << 8) | p[5]);
                pf3[3] = (float)(short)((p[6] << 8) | p[7]);
                pf3 += 4;
                p += 8;
                q += 8;
                --uVar8;
            } while (uVar8 != 0);
        }
        for (unsigned int k = uVar4 - uVar5; k != 0; --k) {
            *pf3 = (float)(short)((p[0] << 8) | p[1]);
            ++pf3; p += 2;
        }
    }
}

// @ 0x01149a00
int __stdcall DecodeRawSamples(unsigned char* param_1, int param_2, int param_3)
{
    unsigned char* p = param_1;
    unsigned int count = ((unsigned int)p[0] << 24) | ((unsigned int)p[1] << 16) |
                         ((unsigned int)p[2] << 8) | p[3];
    unsigned int offset = ((unsigned int)p[4] << 24) | ((unsigned int)p[5] << 16) |
                          ((unsigned int)p[6] << 8) | p[7];
    p += 8;
    int iVar7 = 0;
    if (*(unsigned char*)(param_3 + 0x18) != 0) {
        do {
            if (0 < (int)count) {
                float* pf = (float*)(*(int*)(param_2 + iVar7 * 4) + offset * 4);
                int n = (int)count;
                do {
                    unsigned short w = *(unsigned short*)p;
                    pf[0] = (float)(short)((w << 8) | (w >> 8));
                    p += 2; ++pf; --n;
                } while (n != 0);
            }
            ++iVar7;
        } while (iVar7 < (int)(unsigned int)*(unsigned char*)(param_3 + 0x18));
    }
    return (unsigned int)*(unsigned char*)(param_3 + 0x18) * (int)count * 2 + 8;
}

// @ 0x01149ac0
int Decoder::GetCurrentRequestDesc(char* param_2, int* param_3, int param_4,
                                   unsigned int* param_5, unsigned int* param_6,
                                   unsigned int* param_7, int param_8)
{
    (void)param_2; (void)param_3; (void)param_4;
    (void)param_5; (void)param_6; (void)param_7; (void)param_8;
    return 0;
}

// @ 0x01149d60
int EaLayer3DecBase::DecodeEvent(char* param_2)
{
    (void)param_2;
    return -1;
}

}}} // namespace rw::audio::core
