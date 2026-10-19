// src/game/cmn/fastfirengine.cpp.cpp -- migrated from slice(s) s0114da70 by tools/migrate/rewrite.py
// Object file: cmn/fastfirengine.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/System.h"
#include <string.h>
#include <math.h>
#include <xmmintrin.h>
#pragma function(memset)

// ---- items of slice s0114da70 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef float f32;
typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
namespace rw {
namespace audio {
namespace core {
struct AudioChannelBuffer {
    char pad0[4];
    f32* mpSamples; // +0x04
    char pad8[0x0E - 0x08];
    u16  muStride;  // +0x0E
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct System_s0114_da70 {
    char pad0[0x14];
    void* Alloc(u32 size, const char* tag, int flags, int align);  // 0x0112c820 (rw::audio::core::System::Alloc)
    void  Free(void* p, int flags);  // 0x0112c850 (rw::audio::core::System::Free)
};
}
}
}
namespace rw {
namespace audio {
namespace core {
extern System_s0114_da70* g_pSystem; // DAT_016e61a8
}
}
}
namespace rw {
namespace audio {
namespace core {
struct FastFirEngine;
}
}
}
namespace rw {
namespace audio {
namespace core {
struct FastFirEngine {
    void* mpBuffer;    // +0x00
    f32*  mpInput[2];  // +0x04 / +0x08
    f32*  mpFreq;      // +0x0C
    void* mpImpulse;   // +0x10
    f32*  mpConv;      // +0x14
    f32*  mpOutput[2]; // +0x18 / +0x1C
    s32   miConvBytes; // +0x20
    s32   miBlockFftLen; // +0x24
    s32   miField28;   // +0x28
    s32   miNumBlocks; // +0x2C
    s32   miWriteBlock;// +0x30
    s32   miField34;   // +0x34
    s32   miFrameLen;  // +0x38
    s32   miBlockLen;  // +0x3C
    s32   miFftClearLen; // +0x40
    s32   miField44;   // +0x44
    s32   miBlockStride; // +0x48
    s32   miField4C;   // +0x4C
    s32   miField50;   // +0x50
    s32   miNumPasses; // +0x54
    s32   miField58;   // +0x58
    s32   miCurPass;   // +0x5C
    f32   mfField60;   // +0x60
    s32   miPingA;     // +0x64
    s32   miPingB;     // +0x68
    void* mpFft;       // +0x6C
    s32   miField70;   // +0x70
    s32   miInputChannels; // +0x74
    s32   miOutputChannels;// +0x78
    void* mpDist;      // +0x7C
    s32   miFftDone;   // +0x80
    s32   miMacDone;   // +0x84
    s32   miIfftDone;  // +0x88
    s32   miField8C;   // +0x8C
    u8    mbField90;   // +0x90

    FastFirEngine();                                        // 0x0114e300
    ~FastFirEngine();                                       // 0x0114e340
    int  SetChannels(s32 inputChannels, s32 outputChannels);// 0x0114e370
    void* Filter(AudioChannelBuffer* in, void* out, s32 a4, s32 a5); // 0x0115de20
    void Reset();                                           // 0x0114e580
    int  Configure(s32 channels, s32 blockSize, s32 a4, s32 a5, s32 a6, s32 impulseSamples,
                   s16* pImpulse);                          // 0x0114e5e0
    void LoadDistributionCalc(s32 sizeLog2, s32 numBlocks); // 0x0114e400
    f32  EstimateLoad(s32 a2, s32 a3, s32 a4, s32 a5);      // 0x0114e390
};
}
}
}
namespace rw {
namespace audio {
namespace core {
void FFT_Alloc(s32 sizeLog2, char flag, void** outHandle);
}
}
}
namespace rw {
namespace audio {
namespace core {
void FFT_Init(void* handle);
}
}
}
namespace rw {
namespace audio {
namespace core {
void* FFT_Free(void** handle); // 0x0115e3c0
}
}
}
// ---- items of slice s0114da70 end

// @ 0x0114e400
namespace rw { namespace audio { namespace core {
void FastFirEngine::LoadDistributionCalc(s32 param_2, s32 param_3)
{
    f32 fVar10 = (f32)miOutputChannels;
    f32 fVar8 = (f32)(param_2 - 1) * 18.09f;
    s32 iVar2 = miNumPasses;
    f32 fVar7 = (((1.0f - mfField60 * 0.01f) * (f32)param_3) * fVar10) * 22.65f / fVar8;
    f32 fVar11 = fVar7 / (f32)param_3;
    s32 iVar5 = 0, iVar4 = 0, iVar6 = 0, local_4 = 0;
    fVar7 = ((fVar10 * 10.97f) / fVar8 + (f32)miInputChannels) + fVar10 + fVar7;
    f32 fVar8b = 1.0f;
    s32 pass = 0;
    if (0 < iVar2) {
        s32 iVar3 = 0;
        do {
            f32 fVar9 = fVar7 / (f32)(iVar2 - pass);
            f32 fVar10b = fVar9;
            if (fVar8b * 0.5f <= fVar9) {
                do {
                    if (iVar4 < miInputChannels) {
                        int* p = (int*)((char*)mpDist + 4 + iVar3);
                        *p = *p + 1;
                        iVar4++;
                        fVar10b -= 1.0f;
                        if (miInputChannels <= iVar4)
                            fVar8b = fVar11;
                    } else if (iVar6 < param_3) {
                        int* p = (int*)((char*)mpDist + iVar3);
                        *p = *p + 1;
                        iVar6++;
                        fVar10b -= fVar11;
                        if (param_3 <= iVar6)
                            fVar8b = 1.0f;
                    } else if (iVar5 < miOutputChannels) {
                        int* p = (int*)((char*)mpDist + 8 + iVar3);
                        *p = *p + 1;
                        iVar5++;
                        fVar10b -= 1.0f;
                    } else {
                        fVar10b = 0.0f;
                    }
                    local_4 = iVar5;
                } while (fVar8b * 0.5f <= fVar10b);
            }
            fVar7 = fVar7 - (fVar9 - fVar10b);
            if (pass == miNumPasses - 1 && iVar5 < miOutputChannels) {
                int* p = (int*)((char*)mpDist + -4 + miNumPasses * 0xC);
                *p = *p + (miOutputChannels - local_4);
                iVar5 = local_4;
            }
            iVar2 = miNumPasses;
            pass++;
            iVar3 += 0xC;
        } while (pass < iVar2);
    }
}
}}}  // namespace rw::audio::core

// @ 0x0114e580
namespace rw { namespace audio { namespace core {
void FastFirEngine::Reset()
{
    if (mpBuffer) {
        g_pSystem->Free(mpBuffer, 0);
        mpBuffer = 0;
    }
    if (mpFft) {
        FFT_Free(&mpFft);
        mpFft = 0;
    }
    miCurPass = 0;
    miWriteBlock = 0;
    miPingA = 0;
    miPingB = 0;
    miFftDone = 0;
    miMacDone = 0;
    miIfftDone = 0;
    miField8C = 0;
    mbField90 = 0;
}
}}}  // namespace rw::audio::core

// @ 0x0114e5e0
namespace rw { namespace audio { namespace core {
int FastFirEngine::Configure(s32 channels, s32 blockSize, s32 a4, s32 a5, s32 a6, s32 impulseSamples, s16* pImpulse)
{
    if (mpBuffer)
        Reset();

    if (impulseSamples % blockSize) {
        miField34 = impulseSamples % blockSize;
        miNumBlocks = impulseSamples / blockSize + 1;
    } else {
        miField34 = blockSize;
        miNumBlocks = impulseSamples / blockSize;
    }

    miFrameLen = channels;
    miBlockLen = blockSize;
    miField50 = blockSize;

    const s32 fftClearLen = 2 * blockSize + 2;
    miFftClearLen = fftClearLen;

    mfField60 = ((f32)(blockSize - a4) / (f32)blockSize) * 100.0f;

    s32 v37 = fftClearLen / 16;
    if (fftClearLen % 16)
        ++v37;
    const s32 blockFftLen = 16 * v37;

    const s32 outputChannels = miOutputChannels;
    const s32 inputChannels = miInputChannels;

    miField44 = a5;
    miField4C = a5;
    miBlockStride = blockFftLen;
    miBlockFftLen = blockFftLen;
    miNumPasses = blockSize / channels;

    const s32 numBlocks = miNumBlocks;
    const s32 numPasses = blockSize / channels;
    const u32 outPartBytes = ((u32)outputChannels * (u32)blockSize) * 8u;
    const s32 inFreqBytes = 4 * inputChannels * blockFftLen;
    const s32 convBytes = 4 * outputChannels * blockFftLen;
    const s32 impFreqBytes = 4 * numBlocks * inputChannels * a5;

    miConvBytes = convBytes;

    const u32 totalBytes = (u32)(2 * (6 * numPasses + inFreqBytes) + convBytes) + outPartBytes +
                           (u32)impFreqBytes;

    void* buffer = g_pSystem->Alloc(totalBytes, "Reverb IR Buffer", 0x10, 0);
    mpBuffer = buffer;

    char* cursor = (char*)buffer;
    mpInput[0] = (f32*)cursor; cursor += inFreqBytes;
    mpInput[1] = (f32*)cursor; cursor += inFreqBytes;
    mpFreq = (f32*)cursor;     cursor += impFreqBytes;
    mpConv = (f32*)cursor;     cursor += convBytes;
    mpOutput[0] = (f32*)cursor; cursor += outPartBytes / 2;
    mpOutput[1] = (f32*)cursor; cursor += outPartBytes / 2;
    mpDist = cursor;

    memset(mpDist, 0, (size_t)((blockSize / channels) * 12));

    s32 sizeLog2 = 0;
    for (s32 n = 2 * blockSize; n > 1; n /= 2)
        ++sizeLog2;

    if (!mpFft) {
        FFT_Alloc(sizeLog2, 0, &mpFft);
        FFT_Init(mpFft);
    }

    miField28 = a6;
    mpImpulse = pImpulse;
    miField58 = a5 + 8;

    LoadDistributionCalc(sizeLog2, miNumBlocks);
    return 1;
}
}}}  // namespace rw::audio::core
