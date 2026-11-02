// src/game/cmn/streampool.cpp.cpp -- migrated from slice(s) s0112dca0 by tools/migrate/rewrite.py
// Object file: cmn/streampool.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#pragma function(memcpy)

// ---- items of slice s0112dca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
namespace rw {
namespace audio {
namespace core {
class ListDNode_s0112_dca0 { public: ListDNode_s0112_dca0* pnext; ListDNode_s0112_dca0* pprev; };
}
}
}
namespace rw {
namespace audio {
namespace core {
class System_s0112_dca0;
}
}
}
namespace rw {
namespace audio {
namespace core {
extern ListDNode_s0112_dca0* g_pStreamPoolList; // 0x016e61ac
}
}
}
namespace rw {
namespace audio {
namespace core {
struct StreamDesc_s0112_dca0
{
    double timeStamp;            // +0x0
    float  priority;             // +0x8
    void*  pStreamLostCallback;  // +0xc
    void*  pStreamLostContext;   // +0x10
    void*  pStream;              // +0x14
    u16    refCount;             // +0x18
    u8     allocated;            // +0x1a
    char   pad[1];
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class PlugIn_s0112_dca0;
}
}
}
namespace rw {
namespace audio {
namespace core {
class System_s0112_dca0
{ public:
    void*  mpStackAllocator;     // +0x0
    void*  mpAssertImplementation;// +0x4
    double mSystemTime;          // +0x8
    void*  mExpelledVoiceList;   // +0x10
    void*  mpAllocator;          // +0x14
    void*  mpPhysicalAlloc;      // +0x18
    void*  mpPhysicalFree;       // +0x1c
    char*  mpCommandBuffer;      // +0x20
    void*  mpMasteringSubMix;    // +0x24
    void*  mpPlugInRegistry;     // +0x28
    void*  mpDecoderRegistry;    // +0x2c
    void*  mpEncoderRegistry;    // +0x30
    void*  mpProfiler;           // +0x34
    void*  mpJobScheduler;       // +0x38
    void*  mMutexIsLockedFn;     // +0x3c
    void*  mMutexLockFn;         // +0x40
    void*  mMutexUnlockFn;       // +0x44
    void*  mpExecuteCommandsMutex;// +0x48
    void*  mpMutex;              // +0x4c
    void*  mpLockThreadId;       // +0x50
    void*  mpRwAudioCoreThreadId;// +0x54
    void*  mpVoiceListNodes;     // +0x58
    u8     mTimerList[4];        // +0x5c
    u8     mTimerManager[0x48];  // +0x60
    void*  mpAssertHandler;      // +0xa8
    void*  mGetCsisLibraryType;  // +0xac
    u32    mCommandBufferSize;   // +0xb0
    u32    mCommandIndex;        // +0xb4
    u32    mCommandBufferHighWater;// +0xb8
    float  mSystemTimerPeriod;   // +0xbc
    float  mSampleRate;          // +0xc0
    float  mCpuFrequency;        // +0xc4
    float  mCpuLoadLimit;        // +0xc8
    u32    mMixerCpuTicks;       // +0xcc
    u32    mCommandExecutionCpuTicks;// +0xd0
    u32    mTimerExecutionCpuTicks;// +0xd4
    u32    mLoadBalancerCpuTicks;// +0xd8
    u32    mExpelVoicesCpuTicks; // +0xdc
    u32    mCommandTimeStamp;    // +0xe0
    u8     pad1[0xc];            // +0xe4
    u16    mNumActiveVoices;     // +0xf0
    u16    mMaxActiveVoices;     // +0xf2

    void* Alloc(int size, const char* name, int align, int a5); // 0x0112c820
    void  Free(void* p, void* allocator);                       // 0x0112c850
    void  RemoveTimer(void* timerHandle);                       // 0x0112dad0
    void  FUN_0112c590();                                       // 0x0112c590
};
}
}
}
namespace rw {
namespace audio {
namespace core {
int   FUN_011e7910(int, int, int, int, int, int);                              // 0x011e7910
}
}
}
namespace rw {
namespace audio {
namespace core {
class PlugIn_s0112_dca0 { public: void Initialize(); };  // 0x0112dbb0 (thiscall: ecx = plug-in)
}
}
}
// ---- items of slice s0112dca0 end

// @ 0x0112e290
namespace rw { namespace audio { namespace core {
void* StreamPool_Create(int a1, int numStreams, int chunkSize, int a4, System_s0112_dca0* system, int a6)
{
    int size = numStreams * chunkSize + numStreams * 0x20 + 0x40;
    if (size == 0) size = 0x34;
    char* p = (char*)system->Alloc(size, 0, 0x10, a6);
    if (!p) return 0;

    ((PlugIn_s0112_dca0*)(p + 8))->Initialize(); // PlugIn::Initialize<SndPlayer1>

    unsigned start = ((unsigned)(p + 0x3b)) & 0xfffffff8u;
    *(int*)(p + 4) = (int)start;
    start = (start + 0xf + numStreams * 0x20) & 0xfffffff0u;
    *(int*)(p + 0x20) = a6;
    *(int*)(p + 0) = (int)system;
    *(u8*)(p + 0x28) = (u8)numStreams;
    *(int*)(p + 0x24) = a1;
    if (numStreams > 0)
    {
        int descBase = *(int*)(p + 4);
        int cursor = (int)start;
        int count = numStreams;
        do
        {
            StreamDesc_s0112_dca0* sd = (StreamDesc_s0112_dca0*)(descBase);
            sd->allocated = 0;
            sd->refCount = 0;
            sd->pStream = (void*)FUN_011e7910(a4 + 3, cursor, chunkSize, 0, 0, 0);
            cursor += chunkSize;
            descBase += 0x20;
        } while (--count);
    }
    // append pool to the registry list at +0x2c
    ListDNode_s0112_dca0* node = (ListDNode_s0112_dca0*)(p + 0x2c);
    node->pnext = g_pStreamPoolList;
    node->pprev = 0;
    if (g_pStreamPoolList) g_pStreamPoolList->pprev = node;
    g_pStreamPoolList = node;
    return p;
}
}}}  // namespace rw::audio::core
