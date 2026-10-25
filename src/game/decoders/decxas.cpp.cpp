// src/game/decoders/decxas.cpp.cpp -- migrated from slice(s) s01148fd0 by tools/migrate/rewrite.py
// Object file: decoders/decxas.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
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
namespace rw {
namespace audio {
namespace core {
class EALayer3DecCore {
public:
    void Feed(unsigned char* p, int flag);   // 0x0115cc60
    void SetBuffer(unsigned char* p);         // 0x01148a00
    int  Decode(int* outPtrs);                // 0x0115ccb0
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct EALayer3FrameHdr {
    int field00;      // +0x00
    int headerSize;   // +0x04  bytes of header to skip (2 or 6)
    int field08;      // +0x08
    int field0C;      // +0x0c
    int field10;      // +0x10
    int field14;      // +0x14
    int field18;      // +0x18
    int field1C;      // +0x1c  framing mode

    unsigned int Parse(const unsigned char* p);  // 0x0115b470
    int CalcSize();                              // 0x0115b440
};
}
}
}
// ---- items of slice s01148fd0 end

// @ 0x01149760
namespace rw { namespace audio { namespace core {
int __stdcall ConvertSamples(int* param_1, unsigned char* param_2, int param_3, unsigned int param_4)
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
    return 0;
}
}}}  // namespace rw::audio::core

// @ 0x01149a00
namespace rw { namespace audio { namespace core {
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
}}}  // namespace rw::audio::core

// @ 0x01149ac0
namespace rw { namespace audio { namespace core {
int Decoder::GetCurrentRequestDesc(char* param_2, int* param_3, int param_4, unsigned int* param_5, unsigned int* param_6, unsigned int* param_7, int param_8)
{
    EALayer3FrameHdr hdr;
    unsigned int out[4];
    int nChans = param_8;
    int local_30 = 0;
    int tail;
    int i;
    char* pcVar2 = 0;
    EALayer3DecCore* core = (EALayer3DecCore*)param_4;
    EaLayer3DecBase* self = (EaLayer3DecBase*)this;  // called on the derived instance

    out[0] = 0;
    if (self->mVersion == 0) {
        // v1 header is not framed: a leading 0xEE marks raw-sample payload.
        if (*(unsigned char*)param_2 == 0xEE)
            out[0] = 1;
        param_8 = 1;
        pcVar2 = param_2 + 1;
    } else {
        param_8 = (int)hdr.Parse((const unsigned char*)param_2);
        if (hdr.headerSize == 0)
            goto LAB;
        pcVar2 = param_2 + hdr.headerSize;
    }
    if (pcVar2 != 0) {
        if (self->mNewFeed != 0)
            core->Feed((unsigned char*)pcVar2, 0);
        else
            core->SetBuffer((unsigned char*)pcVar2);
        if (core->Decode(param_3) < 0) {
            i = 0;
            if (nChans > 0) {
                do {
                    memset((void*)param_3[i], 0,
                           (unsigned int)*(unsigned short*)((char*)param_4 + 0x14) * 4);
                    ++i;
                } while (i < nChans);
            }
        }
    }
LAB:
    out[2] = 0;
    if (self->mVersion == 0) {
        *param_5 = 0x240;
        *param_6 = 0;
        if (self->mLatency > 0) {
            unsigned int cur = *param_5;
            if (self->mLatency < (int)cur) {
                *param_6 = (unsigned int)self->mLatency;
                *param_5 = cur - (unsigned int)self->mLatency;
                local_30 = self->mLatency;
            } else {
                *param_6 = cur;
                *param_5 = 0;
            }
        }
    } else {
        *param_5 = (unsigned int)hdr.CalcSize();
        if (hdr.field1C == 0)
            local_30 = hdr.field18;
        else if (hdr.field1C == 2)
            out[2] = (unsigned int)hdr.field18;
    }
    if (self->mSkipSamples > 0) {
        unsigned int cur = *param_5;
        if (self->mSkipSamples < (int)cur) {
            *param_7 = (unsigned int)self->mSkipSamples;
            *param_5 = cur - (unsigned int)self->mSkipSamples;
            local_30 += self->mSkipSamples;
        } else {
            *param_7 = cur;
            *param_5 = 0;
        }
    }
    if (self->mVersion == 0) {
        param_8 += *(int*)((char*)param_4 + 0x10);
        if (out[0] != 0) {
            i = 0;
            if (nChans > 0) {
                do {
                    out[i] = (unsigned int)param_3[i] + *param_6 * 4;
                    ++i;
                } while (i < nChans);
            }
            param_8 += DecodeRawSamples((unsigned char*)(param_2 + param_8),
                                        (int)out, param_4);
        }
    } else {
        if (hdr.field10 > 0) {
            i = 0;
            if (nChans > 0) {
                do {
                    out[i] = (unsigned int)param_3[i] + (unsigned int)hdr.field18 * 4;
                    ++i;
                } while (i < nChans);
            }
            ConvertSamples((int*)out, (unsigned char*)(param_2 + hdr.field0C),
                           nChans, (unsigned int)hdr.field10);
        }
    }
    if ((int)*param_5 > 0 && local_30 > 0) {
        i = 0;
        if (nChans > 0) {
            do {
                char* dst = (char*)param_3[i];
                memmove(dst, dst + local_30 * 4, (unsigned int)*param_5 * 4);
                ++i;
            } while (i < nChans);
        }
    }
    tail = (int)out[2] - local_30;
    if (tail > 0) {
        i = 0;
        if (nChans > 0) {
            do {
                memset((void*)param_3[i], 0, (unsigned int)tail * 4);
                ++i;
            } while (i < nChans);
        }
    }
    return param_8;
}
}}}  // namespace rw::audio::core
