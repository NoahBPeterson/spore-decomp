// src/game/ealayer31/decealayer3process.cpp.cpp -- migrated from slice(s) s01148fd0 by tools/migrate/rewrite.py
// Object file: ealayer31/decealayer3process.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/System.h"
#include <string.h>
#pragma function(memset)
#pragma function(memcpy)
#pragma function(memmove)

// ---- items of slice s01148fd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
class Decoder {
public:
    void** vftable;                           // +0x00
    System_s0114_8fd0* mpSystem;                         // +0x04
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
}
}
}
namespace rw {
namespace audio {
namespace core {
class EALayer3Core;
}
}
}
namespace rw {
namespace audio {
namespace core {
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

    // The decode callback the base Decoder invokes.  It reaches its two
    // operands (the instance and the caller's sample-buffer descriptor) from
    // the stack -- the binary does NOT read `this` from ecx -- so it is a
    // static member, i.e. an ordinary __cdecl function.
    static int DecodeEvent(EaLayer3DecBase* self, char* param_2);
};
}
}
}
// ---- items of slice s01148fd0 end

// @ 0x011495b0
namespace rw { namespace audio { namespace core {
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
}}}  // namespace rw::audio::core
