// src/game/plugins/samplecapture.cpp.cpp -- migrated from slice(s) s011388f0 by tools/migrate/rewrite.py
// Object file: plugins/samplecapture.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/DecoderRegistry.h"
#include "rw/audio/core/StreamPool.h"
#include "rw/audio/core/TimerManager.h"

// unnamed retail callees and globals (address in the comment)
extern const float g_one;                          // 0x01485720
extern "C" double ceil(double);                                // msvcr90!ceil
#include <xmmintrin.h>

// ---- items of slice s011388f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
typedef unsigned short u16;
template <class T> static inline T& A(void* p, int off) { return *(T*)((char*)p + off); }
namespace rw {
namespace audio {
namespace core {
class System_s0113_88f0;
}
}
}
namespace rw {
namespace audio {
namespace core {
class Decoder;
}
}
}
namespace rw {
namespace audio {
namespace core {
class DecoderRegistry_s0113_88f0;
}
}
}
namespace rw {
namespace audio {
namespace core {
class TimerHandle_s0113_88f0 { public:
    void* mItemHandle; void* mpCallback; void* mpContext; char* mpName;
    unsigned int mCpuTicks; unsigned char mStage; unsigned char mTimerVisibility; unsigned char pad16[2];
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class System_s0113_88f0 { public:
    char pad00[0x20]; char* mpCommandBuffer; char pad24[0x90]; unsigned int mCommandIndex; // +0xb4
void* Alloc(int size, const char* name, int align, int alloc);
void Free(void* p, int alloc);
void RemoveTimer(TimerHandle_s0113_88f0* t);
int Lock();
int Unlock();
DecoderRegistry_s0113_88f0* GetDecoderRegistry();
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class Decoder { public:
    char pad00[0x20]; unsigned short mNumChannels;
char FUN_0114c8c0(char*, unsigned, int, int, void*, int);
void FUN_01133f40();
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class DecoderRegistry_s0113_88f0 {
    public: int FUN_01133ed0(int);
    Decoder* DecoderFactory(int, int, int, System_s0113_88f0*);  // 0x01133fc0 (rw::audio::core::DecoderRegistry::DecoderFactory)
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct TimerMgr {
    char AddTimer(void*, void*, void*, const char*, int, int); // 0x0112d8e0
};
}
}
}
extern const float g_one;                          // 0x01485720
extern "C" double ceil(double);                                // msvcr90!ceil
// ---- items of slice s011388f0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace rw { namespace audio { namespace core { void __cdecl FUN_011393d0(void* self); }}}  // 0x011393d0 (stays in the slice: not this object's)

// @ 0x01139500
namespace rw { namespace audio { namespace core {
int __cdecl FUN_01139500(void* rec)
{
    void* self = A<void*>(rec, 4);
    if (A<int>(self, 0x54) != 0)
        return A<int>(rec, 8);
    A<u8>(self, 0x7e) = 0; A<int>(self, 0x70) = 0;
    A<float>(self, 0x48) = A<float>(rec, 0xc);
    A<int>(self, 0x50) = _mm_cvtss_si32(_mm_load_ss((float*)((char*)rec + 0x14)));
    A<int>(self, 0x4c) = _mm_cvtss_si32(_mm_load_ss((float*)((char*)rec + 0x10)));
    A<int>(self, 0x54) = A<int>(rec, 0x18);
    A<int>(self, 0x58) = A<int>(rec, 0x1c);
    if (A<int>(self, 0x50) == 0) A<u16>(self, 0x76) = 2;
    double v = ceil((double)(A<float>(self, 0x48) * 256.0f) / A<float>(A<void*>(self, 4), 0xc0));
    A<int>(self, 0x60) = (int)v;
    unsigned sz = ((unsigned)A<u16>(self, 0x76) * (unsigned)A<int>(self, 0x60) * (unsigned)A<int>(self, 0x4c) + 0xf) & 0xfffffff0u;
    A<int>(self, 0x6c) = (int)sz;
    void* buf = A<System_s0113_88f0*>(self, 4)->Alloc((int)sz, "rw::audio::core::SampleCapture::mpBuf", 0x10, 0);
    A<int>(self, 0x78) = (int)buf;
    if (!buf) return 0;
    A<int>(self, 0x5c) = (int)0xbf800000;
    A<int>(self, 0x64) = 0; A<int>(self, 0x68) = 0; A<u8>(self, 0x7c) = 0; A<u8>(self, 0x7d) = 2;
    char ok = ((TimerMgr*)((char*)A<void*>(self, 4) + 0x60))->AddTimer(
                   (void*)((char*)self + 0x24), (void*)&FUN_011393d0, self, "SampleCapture", 1, 1);
    if (ok == 0) {
        A<u8>(self, 0x7e) = 1; A<float>(self, 0x40) = g_one;
    }
    return A<int>(rec, 8);
}
}}}  // namespace rw::audio::core
