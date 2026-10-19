// src/game/ealayer30/helper_ealayer3decf.cpp.cpp -- migrated from slice(s) s01148fd0, s01148050 by tools/migrate/rewrite.py
// Object file: ealayer30/helper_ealayer3decf.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/System.h"
#include <string.h>
#include <xmmintrin.h>
#include <new>
#pragma function(memset)

// ---- items of slice s01148050 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace audio {
namespace core {
class System_s0114_8050 {
public:
    void* Alloc(unsigned int size, const char* name, unsigned int align, unsigned int flags);  // 0x0112c820 (rw::audio::core::System::Alloc)
    void  Free(void* p, unsigned int flags);  // 0x0112c850 (rw::audio::core::System::Free)
};
}
}
}
namespace rw {
namespace audio {
namespace core {
extern System_s0114_8050* g_pSystem;                 // 0x16e61a8
}
}
}
namespace rw {
namespace audio {
namespace core {
class HELPER_CEALayer3 {
public:
    HELPER_CEALayer3();
    char mData[0x1d4];
};
}
}
}
namespace rw {
namespace audio {
namespace core {
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
}
}
}
namespace rw {
namespace audio {
namespace core {
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
}
}
}
// ---- items of slice s01148050 end

// ---- items of slice s01148fd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma function(memcpy)
#pragma function(memmove)
namespace rw {
namespace audio {
namespace core {
class System_s0114_8fd0 {
public:
    void* Alloc(unsigned int size, const char* name, unsigned int align, unsigned int flags);  // 0x0112c820 (rw::audio::core::System::Alloc)
    void  Free(void* p, unsigned int flags);  // 0x0112c850 (rw::audio::core::System::Free)
};
}
}
}
namespace rw {
namespace audio {
namespace core {
extern System_s0114_8fd0* g_pSystem_s0114_8fd0;                 // 0x16e61a8
}
}
}
namespace rw {
namespace audio {
namespace core {
class EaLayer3DecoderInstance_s0114_8fd0;
}
}
}
namespace rw {
namespace audio {
namespace core {
class HELPER_CEALayer3_s0114_8fd0 {
public:
    ~HELPER_CEALayer3_s0114_8fd0();                      // non-virtual (direct call in the dtor)
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
    char pad18[0x24];                         // +0x18 .. +0x3b
    unsigned char mChannels;                  // +0x3c
    char pad3d[0x1c8 - 0x3d];                 // +0x3d .. +0x1c7
    void* mTail1c8;                           // +0x1c8
    int   mFrameStart;                        // +0x1cc
    float* mpDecodedFrame;                    // +0x1d0
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class EaLayer3DecoderInstance_s0114_8fd0 {
public:
    HELPER_CEALayer3_s0114_8fd0 mDecoder;                // +0x000
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
}
}
}
namespace rw {
namespace audio {
namespace core {
class HELPER_CEALayer3DecF_s0114_8fd0 {
public:
    unsigned char* mInputData;                // +0x00
    int mMaxSamples;                          // +0x04
    int mNumChannels;                         // +0x08
    float** mppResidueArrays;                 // +0x0c
    int mResidueArrayInstances;               // +0x10
    EaLayer3DecoderInstance_s0114_8fd0* pDecoderInstanceArray;  // +0x14
    int decoderInstanceCount;                 // +0x18

    ~HELPER_CEALayer3DecF_s0114_8fd0();
    int DecodeGranules(int a2, int a3, int a4, int a5, int* a6);  // 0x01149020 (rw::audio::core::HELPER_CEALayer3DecF::DecodeGranules)
    int Decode(int a2, int* a3);
};
}
}
}
// ---- items of slice s01148fd0 end

// @ 0x01148eb0
namespace rw { namespace audio { namespace core {
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
}}}  // namespace rw::audio::core

// @ 0x01148fd0
namespace rw { namespace audio { namespace core {
HELPER_CEALayer3DecF_s0114_8fd0::~HELPER_CEALayer3DecF_s0114_8fd0()
{
    if (mppResidueArrays != 0) {
        for (int i = 0; i < decoderInstanceCount; ++i)
            ((HELPER_CEALayer3_s0114_8fd0*)((char*)pDecoderInstanceArray + i * 500))->~HELPER_CEALayer3_s0114_8fd0();
        if (mppResidueArrays != 0)
            g_pSystem_s0114_8fd0->Free(mppResidueArrays, 0);
    }
}
}}}  // namespace rw::audio::core

// @ 0x01149020
namespace rw { namespace audio { namespace core {
int HELPER_CEALayer3DecF_s0114_8fd0::DecodeGranules(int a2, int a3, int a4, int a5, int* a6)
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
        EaLayer3DecoderInstance_s0114_8fd0* inst = pDecoderInstanceArray + iVar6;
        HELPER_CEALayer3_s0114_8fd0* pv = &inst->mDecoder;
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
            inst->mpRawIntData = (float*)g_pSystem_s0114_8fd0->Alloc(
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
                    g_pSystem_s0114_8fd0->Free(inst->mpRawIntData, 0);
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
}}}  // namespace rw::audio::core
