// src/game/plugins/snd9.cpp.cpp -- migrated from slice(s) s011388f0 by tools/migrate/rewrite.py
// Object file: plugins/snd9.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/DecoderRegistry.h"
#include "rw/audio/core/PlugIn.h"
#include "rw/audio/core/StreamPool.h"
#include "rw/audio/core/SubMix.h"
#include "rw/audio/core/System.h"
#include "rw/audio/core/TimerHandle.h"
#include "rw/audio/core/TimerManager.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int  FUN_01141710(void);                            // 0x01141710
extern "C" int  FUN_011332c0(void);                            // 0x011332c0
extern "C" int  FUN_01133290(void);                            // 0x01133290
extern "C" int  FUN_011431a0(void* ptrs, int n);               // 0x011431a0
extern "C" int  FUN_0113f940(void);                            // 0x0113f940
#include <xmmintrin.h>

// ---- items of slice s011388f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
template <class T> static inline T& A(void* p, int off) { return *(T*)((char*)p + off); }
namespace rw {
namespace audio {
namespace core {
struct System_s0113_88f0;
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
struct DecoderRegistry_s0113_88f0;
}
}
}
namespace rw {
namespace audio {
namespace core {
struct TimerHandle_s0113_88f0 {
    void* mItemHandle; void* mpCallback; void* mpContext; char* mpName;
    unsigned int mCpuTicks; unsigned char mStage; unsigned char mTimerVisibility; unsigned char pad16[2];
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct System_s0113_88f0 {
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
struct DecoderRegistry_s0113_88f0 {
    int FUN_01133ed0(int);
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
extern "C" int  FUN_01141710(void);                            // 0x01141710
extern "C" int  FUN_011332c0(void);                            // 0x011332c0
extern "C" int  FUN_01133290(void);                            // 0x01133290
extern "C" int  FUN_011431a0(void* ptrs, int n);               // 0x011431a0
extern "C" int  FUN_0113f940(void);                            // 0x0113f940
// ---- items of slice s011388f0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace rw { namespace audio { namespace core { void __stdcall FUN_01138d40(float rate); }}}  // 0x01138d40 (stays in the slice: not this object's)

// @ 0x01138d90
namespace rw { namespace audio { namespace core {
void __cdecl FUN_01138d90(void* self)
{
    int local[6];
    local[0] = A<int>(self, 0x40); local[1] = A<int>(self, 0x44); local[2] = A<int>(self, 0x48);
    local[3] = A<int>(self, 0x4c); local[4] = A<int>(self, 0x50); local[5] = A<int>(self, 0x54);
    float sr = A<float>(A<void*>(self, 4), 0xc0);
    if (sr != A<float>(self, 0x58)) {
        FUN_01138d40(sr);
        A<float>(self, 0x58) = sr;
        A<int>(self, 0x5c) = 0; A<int>(self, 0x60) = 0; A<int>(self, 0x64) = 0;
    }
    FUN_01141710();
    int budget = 0x100;
    for (;;) {
        if (A<int>(self, 0x64) < 1) {
            A<int>(self, 0x5c) = A<int>(self, 0x5c) + 1;
            FUN_011332c0(); FUN_01133290();
            int v = (A<int>(self, 0x5c) * _mm_cvtss_si32(_mm_load_ss(&sr))) / 100;
            unsigned rem = (unsigned)((v - A<int>(self, 0x60)) & 0xffffff0);
            A<int>(self, 0x64) = (int)rem;
            A<int>(self, 0x60) = (int)(rem + A<int>(self, 0x60));
            if (A<int>(self, 0x5c) > 30000) { A<int>(self, 0x5c) = 0; A<int>(self, 0x60) = 0; }
        }
        int take = A<int>(self, 0x64);
        int use = take;
        if (budget <= take) use = budget;
        budget -= use;
        A<int>(self, 0x64) = take - use;
        FUN_011431a0(local, use);
        FUN_0113f940();
        int adv = use * 4;
        local[0] += adv; local[1] += adv; local[2] += adv;
        local[3] += adv; local[4] += adv; local[5] += adv;
        if (budget <= 0) break;
    }
}
}}}  // namespace rw::audio::core

// @ 0x01138ec0
namespace rw { namespace audio { namespace core {
bool __cdecl FUN_01138ec0(void* self)
{
    if (self) {
        *(void**)self = (void*)0x14b085c;
        /* PlugIn::Initialize<...>(self+0x24) */
        A<int>(self, 0x24) = 0;
        A<int>(self, 0x30) = 0x13f9034;
        A<int>(self, 0x34) = 0;
        A<u8>(self, 0x38) = 3;
    }
    A<u8>(self, 0x68) = 0;
    void* buf = A<System_s0113_88f0*>(self, 4)->Alloc(0x1800, "rw::audio::core::Snd9Service::mpMixBufStart", 0x80, 0);
    A<int>(self, 0x3c) = (int)buf;
    if (!buf) return false;
    A<int>(self, 0x40) = (int)((char*)buf + 0x400);
    A<int>(self, 0x44) = (int)((char*)buf + 0x800);
    A<int>(self, 0x50) = (int)buf;
    A<int>(self, 0x48) = (int)((char*)buf + 0x1000);
    A<int>(self, 0x54) = (int)((char*)buf + 0x1400);
    A<int>(self, 0x4c) = (int)((char*)buf + 0xc00);
    A<float>(self, 0x58) = A<float>(A<void*>(self, 4), 0xc0);
    A<int>(self, 0x5c) = 0; A<int>(self, 0x60) = 0; A<int>(self, 0x64) = 0;
    char ok = ((TimerMgr*)((char*)A<void*>(self, 4) + 0x60))->AddTimer(
                   (void*)((char*)self + 0x24), (void*)&FUN_01138d90, self, "Snd9Service", 1, 1);
    if (ok != 0)
        return false;
    A<u8>(self, 0x68) = 1;
    return true;
}
}}}  // namespace rw::audio::core
