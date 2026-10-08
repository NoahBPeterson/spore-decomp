// RenderWare 4 rwaudio core: System built-in registration, StreamPool, Voice and the
// stream/chunk pump (prebuilt MSVC library code inside SporeApp.exe).
// Built with VC .NET 2003 (cl 13.10) + /LTCG; object-heavy, so behaviour-equivalent
// source, not byte-exact.
// compile with /vc71 /O2 /MD /Gy /TP
#include "types.h"
#include <string.h>

// The original's grow path calls the CRT memcpy (E8 to 0x11e0744); with /O2 the compiler
// would inline it as `rep movsd`, dropping the call from the observable trace.
#pragma function(memcpy)

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// =====================================================================================
// System / StreamPool / Voice (x86 PDB layouts).
// =====================================================================================
namespace rw { namespace audio { namespace core {

struct ListDNode { ListDNode* pnext; ListDNode* pprev; };

struct System;
struct StreamPool;

// The registry list head used by StreamPool::GetInstance / Release (0x016e61ac).
extern ListDNode* g_pStreamPoolList; // 0x016e61ac

// ---- StreamPool (x86, size 0x34) --------------------------------------------------
struct StreamDesc
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

struct StreamPool
{
    System*      mpSystem;       // +0x0
    StreamDesc*  mpStreamDesc;   // +0x4
    u8           mTimerHandle[0x18]; // +0x8
    void*        mpAllocator;    // +0x20
    u32          mGuid;          // +0x24
    u8           mNumStreams;    // +0x28
    char         pad1[3];
    ListDNode    mListNode;      // +0x2c

    void QueueRelease();         // 0x0112e410
    StreamDesc* AcquireStream(float priority, void* streamLost, int context); // 0x0112dfa0
};

// ---- Voice (x86, size 0x50) -------------------------------------------------------
struct PlugIn;
struct PlugInLocationDesc;

struct Voice
{
    float mAverager[4];          // +0x0  rw::audio::core::CpuCycleAverager
    System* mpSystem;            // +0x10
    char* mpName;                // +0x14
    PlugInLocationDesc* mpPlugInLocationDescs; // +0x18
    ListDNode mExpelNode;        // +0x1c
    float mPitch;                // +0x24
    float mDecaySamples;         // +0x28
    float mDecayEatenSamples;    // +0x2c
    float mExpelAfterDecaySamples; // +0x30
    u32   mCreationTimeStamp;    // +0x34
    float mPriority;             // +0x38
    u32   mCpuTicks;             // +0x3c
    u32   mSize;                 // +0x40
    u8    mNumPlugIns;           // +0x44
    u8    mDiscontinuityPlugIn;  // +0x45
    u8    mInputPlugInStartPoint;// +0x46
    u8    mState;                // +0x47
    u8    mProcessingStage;      // +0x48
    u8    mExpelReason;          // +0x49
    u8    pad0[2];
    PlugIn* mpPlugIns[1];        // +0x4c

    bool RemoveFromActive();     // 0x0112e5a0
    void Release(char param_2);  // 0x0112e600
    void Stop(u8 param_2);       // 0x0112e690
    void QueueRelease();         // 0x0112e950
};

// ---- System (subset of the 0x100-byte layout) --------------------------------------
struct System
{
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

// =====================================================================================
// Sibling-TU helpers (declared; resolved by the equivalence checker where annotated).
// =====================================================================================
extern "C" {
void  FUN_0113ec60(); // 0x0113ec60
void  FUN_0113e730(); // 0x0113e730
void  FUN_0113e630(); // 0x0113e630
void  FUN_0113e590(); // 0x0113e590
void  FUN_0113e4a0(); // 0x0113e4a0
void  FUN_0113ccc0(); // 0x0113ccc0
void  FUN_0113cae0(); // 0x0113cae0
void  FUN_0113ca60(); // 0x0113ca60
void  FUN_0113c900(); // 0x0113c900
void  FUN_0113c830(); // 0x0113c830
void  FUN_0113c760(); // 0x0113c760
void  FUN_0113c6d0(); // 0x0113c6d0
void  FUN_0113c5d0(); // 0x0113c5d0
void  FUN_0113c510(); // 0x0113c510
void  FUN_0113c420(); // 0x0113c420
void  FUN_0113c320(); // 0x0113c320
void  FUN_0113c240(); // 0x0113c240
void  FUN_0113c190(); // 0x0113c190
void  FUN_0113c0e0(); // 0x0113c0e0
void  FUN_0113c010(); // 0x0113c010
void  FUN_0113b990(); // 0x0113b990
void  FUN_0113b700(); // 0x0113b700
void  FUN_0113b2e0(); // 0x0113b2e0
void  FUN_0113af30(); // 0x0113af30
void  FUN_0113add0(); // 0x0113add0
void  FUN_0113acc0(); // 0x0113acc0
void  FUN_0113abb0(); // 0x0113abb0
void  FUN_0113ab60(); // 0x0113ab60
void  FUN_0113aaa0(); // 0x0113aaa0
void  FUN_0113a720(); // 0x0113a720
void  FUN_01139860(); // 0x01139860
void  FUN_011396e0(); // 0x011396e0
void  FUN_01139350(); // 0x01139350
void  FUN_01139060(); // 0x01139060
void  FUN_01138f70(); // 0x01138f70
void  FUN_01138cb0(); // 0x01138cb0
void  FUN_01137660(); // 0x01137660
void  FUN_01137370(); // 0x01137370
void  FUN_011370f0(); // 0x011370f0
void  FUN_01137090(); // 0x01137090
}

void* FUN_0113e7e0(); void* FUN_0113e660(); void* FUN_0113e5c0(); void* FUN_0113e4d0();
void* FUN_0113cdc0(); void* FUN_0113cb10(); void* FUN_0113caa0(); void* FUN_0113c940();
void* FUN_0113c860(); void* FUN_0113c790(); void* FUN_0113c700(); void* FUN_0113c610();
void* FUN_0113c540(); void* FUN_0113c450(); void* FUN_0113c350(); void* FUN_0113c280();
void* FUN_0113c1c0(); void* FUN_0113c110(); void* FUN_0113c050(); void* FUN_0113b9c0();
void* FUN_0113b740(); void* FUN_0113b320(); void* FUN_0113af60(); void* FUN_0113ae20();
void* FUN_0113ad00(); void* FUN_0113abc0(); void* FUN_0113aba0(); void* FUN_0113aad0();
void* FUN_0113a760(); void* FUN_01139890(); void* FUN_01139720(); void* FUN_01139380();
void* FUN_011390a0(); void* FUN_01138f80(); void* FUN_01138cf0(); void* FUN_011376c0();
void* FUN_011373b0(); void* FUN_01137120(); void* FUN_011370c0(); void* FUN_01136e00();

// StreamPool / Voice / System callees.
// Decoder registry (FUN_0112cd60 is a __thiscall method: `mov ecx,esi; call`).
struct DecoderRegistry { void* Register(void* desc); };                        // 0x0112cd60

void* FUN_0112c580(System* s);                                                 // 0x0112c580
int __fastcall FUN_011e6c40(void* p);                                          // 0x011e6c40
void __fastcall FUN_011e7cf0(void* p);                                                   // 0x011e7cf0
int   FUN_011e7910(int, int, int, int, int, int);                              // 0x011e7910
void  FUN_011e7c70(void* p);                                                   // 0x011e7c70
// Stream::ReleaseChunk is a __thiscall method (ecx = stream, one stack arg).
struct Stream { void ReleaseChunk(void* chunk); };                             // 0x011e7c70
void* FUN_0112cc10(void*, void*, void*, void*, unsigned char);                 // 0x0112cc10
struct PlugIn { void Initialize(); };  // 0x0112dbb0 (thiscall: ecx = plug-in)
void  FUN_0112dbb0(void* plugIn);                                              // 0x0112dbb0
void __fastcall FUN_011e7b70(void* p);                                         // 0x011e7b70
void  FUN_0112e380(void);                                                      // 0x0112e380
void  FUN_01133450(void);                                                      // 0x01133450
void  FUN_01133460(void);                                                      // 0x01133460
void  SNDPKTPLAY_submit(int a, void* b);                                      // 0x0112e9?? external
int __fastcall Stream_GetChunk(void* stream);                                           // rw::core::filesys::Stream::GetChunk

// ---- System built-in registration list (0x0112dca0) -------------------------------
// @ 0x0112dca0 -- register every built-in decoder descriptor (ecx = this registry).
void __fastcall RegisterBuiltInDecoders(DecoderRegistry* self)
{
    FUN_0113ec60();
    self->Register(FUN_0113e7e0());
    FUN_0113e730(); self->Register(FUN_0113e660());
    FUN_0113e630(); self->Register(FUN_0113e5c0());
    FUN_0113e590(); self->Register(FUN_0113e4d0());
    FUN_0113e4a0(); self->Register(FUN_0113cdc0());
    FUN_0113ccc0(); self->Register(FUN_0113cb10());
    FUN_0113cae0(); self->Register(FUN_0113caa0());
    FUN_0113ca60(); self->Register(FUN_0113c940());
    FUN_0113c900(); self->Register(FUN_0113c860());
    FUN_0113c830(); self->Register(FUN_0113c790());
    FUN_0113c760(); self->Register(FUN_0113c700());
    FUN_0113c6d0(); self->Register(FUN_0113c610());
    FUN_0113c5d0(); self->Register(FUN_0113c540());
    FUN_0113c510(); self->Register(FUN_0113c450());
    FUN_0113c420(); self->Register(FUN_0113c350());
    FUN_0113c320(); self->Register(FUN_0113c280());
    FUN_0113c240(); self->Register(FUN_0113c1c0());
    FUN_0113c190(); self->Register(FUN_0113c110());
    FUN_0113c0e0(); self->Register(FUN_0113c050());
    FUN_0113c010(); self->Register(FUN_0113b9c0());
    FUN_0113b990(); self->Register(FUN_0113b740());
    FUN_0113b700(); self->Register(FUN_0113b320());
    FUN_0113b2e0(); self->Register(FUN_0113af60());
    FUN_0113af30(); self->Register(FUN_0113ae20());
    FUN_0113add0(); self->Register(FUN_0113ad00());
    FUN_0113acc0(); self->Register(FUN_0113abc0());
    FUN_0113abb0(); self->Register(FUN_0113aba0());
    FUN_0113ab60(); self->Register(FUN_0113aad0());
    FUN_0113aaa0(); self->Register(FUN_0113a760());
    FUN_0113a720(); self->Register(FUN_01139890());
    FUN_01139860(); self->Register(FUN_01139720());
    FUN_011396e0(); self->Register(FUN_01139380());
    FUN_01139350(); self->Register(FUN_011390a0());
    FUN_01139060(); self->Register(FUN_01138f80());
    FUN_01138f70(); self->Register(FUN_01138cf0());
    FUN_01138cb0(); self->Register(FUN_011376c0());
    FUN_01137660(); self->Register(FUN_011373b0());
    FUN_01137370(); self->Register(FUN_01137120());
    FUN_011370f0(); self->Register(FUN_011370c0());
    FUN_01137090(); self->Register(FUN_01136e00());
}

// @ 0x0112df80 -- StreamPool::GetInstance: find the pool with the given guid.
StreamPool* StreamPool_GetInstance(u32 guid)
{
    ListDNode* node = g_pStreamPoolList;
    while (node)
    {
        if (*(int*)((char*)node - 8) == (int)guid)
            return (StreamPool*)((char*)node - 0x2c);
        node = node->pnext;
    }
    return 0;
}

// @ 0x0112dfa0 -- StreamPool::AcquireStream(priority, streamLost, context).
StreamDesc* StreamPool::AcquireStream(float priority, void* streamLost, int context)
{
    StreamPool* self = this;
    u32 n = self->mNumStreams;
    for (u32 i = 0; i < n; ++i)
    {
        StreamDesc* s = &self->mpStreamDesc[i];
        if (s->allocated != 0 && s->pStreamLostContext != 0 &&
            s->pStreamLostContext == (void*)context)
        {
            s->refCount = (u16)(s->refCount + 1);
            return s;
        }
    }
    for (u32 i = 0; i < n; ++i)
    {
        StreamDesc* s = &self->mpStreamDesc[i];
        if (s->allocated == 0)
        {
            s->allocated = 1;
            s->refCount = (u16)(s->refCount + 1);
            s->priority = priority;
            s->pStreamLostCallback = streamLost;
            s->pStreamLostContext = (void*)context;
            s->timeStamp = self->mpSystem->mSystemTime;
            return s;
        }
    }
    // eviction: lowest priority, ties by lowest timeStamp
    double bestTime = 1.7976931348623157e+308;
    StreamDesc* best = 0;
    float bestPri = priority;
    u32 i = 0;
    if (n >= 4)
    {
        u32 blocks = ((n - 4) >> 2) + 1;
        StreamDesc* p = self->mpStreamDesc;
        u32 cnt = blocks * 4;
        (void)p;
        for (u32 b = 0; b < blocks; ++b)
        {
            StreamDesc* q = &self->mpStreamDesc[i];
            for (int k = 0; k < 4; ++k, ++i)
            {
                StreamDesc* s = &q[k];
                bool take = false;
                if (s->priority < bestPri) { take = true; }
                else if (s->priority == bestPri && s->timeStamp < bestTime) { take = true; }
                if (take) { bestPri = s->priority; bestTime = s->timeStamp; best = s; }
            }
        }
        (void)cnt;
    }
    for (; i < n; ++i)
    {
        StreamDesc* s = &self->mpStreamDesc[i];
        bool take = false;
        if (s->priority < bestPri) { take = true; }
        else if (s->priority == bestPri && s->timeStamp < bestTime) { take = true; }
        if (take) { bestPri = s->priority; bestTime = s->timeStamp; best = s; }
    }
    if (!(bestPri < priority) || !(bestPri < 100.0f) || best == 0)
        return 0;
    typedef void (*LostCb)(void*);
    ((LostCb)best->pStreamLostCallback)(best->pStreamLostContext);
    best->allocated = 1;
    best->refCount = (u16)(best->refCount + 1);
    best->priority = priority;
    best->pStreamLostCallback = streamLost;
    best->pStreamLostContext = (void*)context;
    best->timeStamp = self->mpSystem->mSystemTime;
    return best;
}

// @ 0x0112e1e0 -- StreamPool::ReleaseStream (refcount is signed 16-bit).
void __stdcall StreamPool_ReleaseStream(StreamDesc* desc)
{
    if (--desc->refCount == 0)
    {
        FUN_011e7b70(desc->pStream);
        desc->allocated = 0;
    }
}

// @ 0x0112e210 -- StreamPool::ReleaseHandler (runs from the TimerManager callback).
void StreamPool_ReleaseHandler(StreamPool* self)
{
    int i = 0;
    if (self->mNumStreams > 0)
    {
        do
        {
            if (FUN_011e6c40(self->mpStreamDesc[i].pStream) != 0)
                return;
            ++i;
        } while (i < (int)self->mNumStreams);
    }
    i = 0;
    if (self->mNumStreams > 0)
    {
        do { FUN_011e7cf0(self->mpStreamDesc[i].pStream); ++i; }
        while (i < (int)self->mNumStreams);
    }
    self->mpSystem->RemoveTimer(&self->mTimerHandle);
    self->mpSystem->FUN_0112c590();
    self->mpSystem->Free(self, self->mpAllocator);
}

// @ 0x0112e290 -- StreamPool::Create (System::CreateStreamPool).
void* StreamPool_Create(int a1, int numStreams, int chunkSize, int a4, System* system, int a6)
{
    int size = numStreams * chunkSize + numStreams * 0x20 + 0x40;
    if (size == 0) size = 0x34;
    char* p = (char*)system->Alloc(size, 0, 0x10, a6);
    if (!p) return 0;

    ((PlugIn*)(p + 8))->Initialize(); // PlugIn::Initialize<SndPlayer1>

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
            StreamDesc* sd = (StreamDesc*)(descBase);
            sd->allocated = 0;
            sd->refCount = 0;
            sd->pStream = (void*)FUN_011e7910(a4 + 3, cursor, chunkSize, 0, 0, 0);
            cursor += chunkSize;
            descBase += 0x20;
        } while (--count);
    }
    // append pool to the registry list at +0x2c
    ListDNode* node = (ListDNode*)(p + 0x2c);
    node->pnext = g_pStreamPoolList;
    node->pprev = 0;
    if (g_pStreamPoolList) g_pStreamPoolList->pprev = node;
    g_pStreamPoolList = node;
    return p;
}

// @ 0x0112e410 -- queue a ReleaseHandler callback command for this pool.
void StreamPool::QueueRelease()
{
    System* s = mpSystem;
    char* cmd = s->mpCommandBuffer + s->mCommandIndex;
    s->mCommandIndex += 8;
    *(void**)cmd = (void*)&FUN_0112e380;
    *(void**)(cmd + 4) = this;
}

// @ 0x0112e440 -- Voice::GetDecayProgress = mDecaySamples / System->mSampleRate.
double __fastcall Voice_GetDecayProgress(int p)
{
    int s = *(int*)(p + 0x10);
    return (double)*(float*)(p + 0x28) / (double)*(float*)(s + 0xc0);
}

// @ 0x0112e450 -- Voice::StartDecay: enter state 1 and latch the decay countdown.
void __fastcall Voice_StartDecay(int p)
{
    if (*(char*)(p + 0x47) == 0)
    {
        *(char*)(p + 0x47) = 1;
        *(float*)(p + 0x30) = *(float*)(p + 0x28);
    }
}

// @ 0x0112e470 -- System::AddActiveVoice (insert voice sorted by processing stage).
int FUN_0112e470(int param_1)
{
    int v = *(int*)(param_1 + 4);
    int s = *(int*)(v + 0x10);
    u16 n = *(u16*)(s + 0xf0);
    if (n >= *(u16*)(s + 0xf2))
    {
        u16 cap = *(u16*)(s + 0xf2);
        int newCap = cap + 0x20;
        void* pv = ((System*)s)->Alloc(newCap * 8,
                                "rw::audio::core::System::mpVoiceListNodes", 0x10, 0);
        if (!pv)
        {
            *(u8*)(v + 0x47) = 2;
            *(u8*)(v + 0x49) = 1;
            int* node = (int*)(v + 0x1c);
            int* head = (int*)(s + 0x10);
            *(int*)(v + 0x1c) = *head;
            *(int*)(v + 0x20) = 0;
            int h = *head;
            if (h) *(int**)(h + 4) = node;
            *head = (int)node;
            return 8;
        }
        // copy old array (cap*8 bytes) into the new block
        memcpy(pv, *(void**)(s + 0x58), (u32)cap * 8);
        ((System*)s)->Free(*(void**)(s + 0x58), 0);
        *(void**)(s + 0x58) = pv;
        *(u16*)(s + 0xf2) = (u16)newCap;
    }
    u16 count = *(u16*)(s + 0xf0);
    int idx = 0;
    if (count != 0)
    {
        int* e = *(int**)(s + 0x58);
        do
        {
            if (*(u8*)(v + 0x48) <= *(u8*)(*e + 0x48)) break;
            ++idx;
            e += 2;
        } while (idx < (int)count);
    }
    int* arr = *(int**)(s + 0x58);
    int* slot = arr + idx * 2;
    memmove(slot + 2, slot, ((u32)count - idx) * 8);
    *(int*)(*(int*)(s + 0x58) + idx * 8) = v;
    *(int*)(*(int*)(s + 0x58) + 4 + idx * 8) = *(int*)(v + 0x40);
    *(u16*)(s + 0xf0) = (u16)(count + 1);
    return 8;
}

// @ 0x0112e5a0 -- Voice::RemoveFromActive.
bool Voice::RemoveFromActive()
{
    int voice = (int)this;
    int s = *(int*)(voice + 0x10);
    u32 n = *(u16*)(s + 0xf0);
    int i = 0;
    if (n != 0)
    {
        int* e = *(int**)(s + 0x58);
        do
        {
            if (*e == voice)
            {
                u16* pc = (u16*)(s + 0xf0);
                *pc = (u16)(*pc - 1);
                void* dst = (void*)(*(int*)(s + 0x58) + i * 8);
                memmove(dst, (char*)dst + 8, ((u32)*pc - i) * 8);
                return true;
            }
            ++i;
            e += 2;
        } while (i < (int)n);
    }
    return false;
}

// @ 0x0112e600 -- Voice::Release (disconnect plug-ins and free).
void Voice::Release(char param_2)
{
    int v = (int)this;
    int i = 0;
    if (*(u8*)(v + 0x44) != 0)
    {
        int* pp = (int*)(v + 0x4c);
        do
        {
            if (*pp != 0)
            {
                int plug = *pp;
                ((void(*)(void))(*(int*)plug))();
                ((void(*)(int))(*(int*)(*(int*)plug + 0xc)))(0);
            }
            ++i;
            ++pp;
        } while (i < (int)*(u8*)(v + 0x44));
    }
    if (param_2 == 0 && !RemoveFromActive())
    {
        int s = *(int*)(v + 0x10);
        int* head = (int*)(s + 0x10);
        int* node = (int*)(v + 0x1c);
        if (node == head)
            *(int*)(s + 0x10) = *head;
        if (*(int**)(v + 0x20) != 0)
            **(int**)(v + 0x20) = *node;
        if (*(int*)node != 0)
            *(int*)(*node + 4) = *(int*)(v + 0x20);
    }
    (*(System**)(v + 0x10))->Free((void*)v, 0);
}

// @ 0x0112e690 -- Voice::Stop: mark stopped and expel from the active list.
void Voice::Stop(u8 param_2)
{
    int v = (int)this;
    if (*(u8*)(v + 0x47) != 2)
    {
        *(u8*)(v + 0x47) = 2;
        *(u8*)(v + 0x49) = param_2;
        *(int*)(v + 0) = 0;
        *(int*)(v + 4) = 0;
        *(int*)(v + 8) = 0;
        *(int*)(v + 0x3c) = 0;
        if (*(u8*)(v + 0x44) != 0)
        {
            u32 k = 0;
            int* pp = (int*)(v + 0x4c);
            do { *(int*)(*pp + 0x1c) = 0; ++k; ++pp; } while (k < *(u8*)(v + 0x44));
        }
        int s = *(int*)(v + 0x10);
        int* node = (int*)(v + 0x1c);
        int* head = (int*)(s + 0x10);
        *(int*)(v + 0x20) = 0;
        *(int*)(v + 0x1c) = *head;
        int h = *head;
        if (h) *(int**)(h + 4) = node;
        *head = (int)node;
    }
}

// @ 0x0112e700 -- Voice release command (queued): release `*(param+4)` and return 8.
int FUN_0112e700(int param)
{
    ((Voice*)*(int*)(param + 4))->Release(0);
    return 8;
}

// @ 0x0112e720 -- Voice::Voice (constructor).
void* Voice_ctor(u8 processingStage, int numPlugIns, int plugInDescs, void** outPlugIns,
                 System* system)
{
    int total = (numPlugIns * 4 + 0x53) & 0xfffffff8;
    total += numPlugIns * 0xc;
    if (numPlugIns > 0)
    {
        int p = plugInDescs;
        for (int k = 0; k < numPlugIns; ++k)
        {
            typedef int (*SizeFn)(int);
            int sz = ((SizeFn)(*(int*)(*(int*)(p + 4) + 4)))(p);
            total = (total + 0xf) & 0xfffffff0;
            total += sz;
            p += 0xc;
        }
    }
    int allocSize = total ? total : 0x50;
    char* v = (char*)system->Alloc(allocSize, 0, 0x10, 0);
    if (!v) return 0;

    *(int*)(v + 0xc) = 0;
    *(int*)(v + 0x40) = total;
    if (numPlugIns > 0)
    {
        int* pp = (int*)(v + 0x4c);
        for (int k = numPlugIns; k != 0; --k) { *pp = 0; ++pp; }
    }
    *(int*)(v + 0x24) = 0x3f800000; // mPitch = 1.0f
    *(u8*)(v + 0x48) = processingStage;
    *(int*)(v + 0x28) = 0;
    *(int*)(v + 0x2c) = 0;
    *(int*)(v + 0x30) = 0;
    *(int*)(v + 0x14) = (int)"Unknown";
    *(int*)(v + 0x10) = (int)system;
    *(u8*)(v + 0x44) = (u8)numPlugIns;
    *(u8*)(v + 0x47) = 0;
    *(u8*)(v + 0x49) = 0;
    *(int*)(v + 0x34) = system->mCommandTimeStamp;
    *(int*)(v + 0x38) = 0x42c80000; // mPriority = 100.0f
    unsigned locs = ((unsigned)(v + numPlugIns * 4 + 0x53)) & 0xfffffff8u;
    *(u8*)(v + 0x45) = 0;
    *(u8*)(v + 0x4a) = 0;
    *(int*)(v + 0x3c) = 0;
    *(int*)(v + 0) = 0x46855556;
    *(int*)(v + 4) = 0x46855556;
    *(int*)(v + 8) = 0x46855556;
    *(int*)(v + 0x18) = locs;
    unsigned dataCursor = locs + numPlugIns * 0xc;
    u8 firstStage = 0;
    *(u8*)(v + 0x46) = 0xff;
    int p = plugInDescs;
    u32 k = 0;
    if (numPlugIns > 0)
    {
        int* pp = (int*)(v + 0x4c);
        for (; (int)k < numPlugIns; ++k, p += 0xc, ++pp)
        {
            int src = *(int*)(p + 4);
            int* slot = (int*)(*(int*)(v + 0x18) + k * 0xc);
            if (*(u8*)(src + 0x2c) < 4) *(u8*)(v + 0x46) = (u8)k;
            typedef int (*SizeFn)(int);
            u16 sz = (u16)((SizeFn)(*(int*)(src + 4)))(p);
            *(u16*)((char*)slot + 8) = sz;
            unsigned q = (dataCursor + 0xf) & 0xfffffff0u;
            dataCursor = q + sz;
            int obj = (int)FUN_0112cc10((void*)q, v, (void*)src, (void*)p, firstStage);
            *pp = obj;
            if (obj == 0)
            {
                u32 j = 0;
                if (*(u8*)(v + 0x44) != 0)
                {
                    int* qq = (int*)(v + 0x4c);
                    do
                    {
                        if (*qq)
                        {
                            int plug = *qq;
                            ((void(*)(void))(*(int*)plug))();
                            ((void(*)(int))(*(int*)(*(int*)plug + 0xc)))(0);
                        }
                        ++j; ++qq;
                    } while (j < *(u8*)(v + 0x44));
                }
                (*(System**)(v + 0x10))->Free(v, 0);
                return 0;
            }
            slot[1] = *(int*)(src + 0x10);
            slot[0] = *(int*)(src + 0xc);
            firstStage = *(u8*)(p + 8);
            (void)firstStage;
        }
    }
    *outPlugIns = (void*)(v + 0x4c);
    u32 idx = system->mCommandIndex;
    char* cmd = system->mpCommandBuffer + idx;
    system->mCommandIndex = idx + 8;
    *(void**)(cmd + 4) = v;
    *(void**)cmd = (void*)&FUN_0112e470;
    return v;
}

// @ 0x0112e950 -- Voice::QueueRelease (queue the release command).
void Voice::QueueRelease()
{
    System* s = *(System**)((int)this + 0x10);
    char* cmd = s->mpCommandBuffer + s->mCommandIndex;
    s->mCommandIndex += 8;
    *(void**)cmd = (void*)&FUN_0112e700;
    *(void**)(cmd + 4) = this;
}

// @ 0x0112e980 -- System::Alloc wrapper for the singleton.
void FUN_0112e980(void* p1, int p2)
{
    extern System* g_pAudioSystem; // 0x016e61a8
    g_pAudioSystem->Alloc(p2, (const char*)p1, 0x10, 0);
}

// @ 0x0112e9b0 -- submit one packet into the sound player.
void FUN_0112e9b0(int* s, int param_2, unsigned param_3, int param_4, u8 param_5)
{
    (void)param_4; (void)param_5;
    unsigned blocks = param_3 / (unsigned)((int)*(short*)((char*)s + 0xc2) *
                                          (int)(short)s[0x30]);
    typedef void (*SubmitFn)(int, unsigned, unsigned);
    ((SubmitFn)(*(int*)(s[0x2b])))(param_2, param_3, blocks);

    int n = (short)s[0x30];
    unsigned vals[8];
    int base = *(int*)((int)s * 5 + 200);
    int step = n ? (0x4000 / (n * 4)) : 0;
    for (int i = 0; i < n; ++i)
        vals[i] = (unsigned)(base + i * step);

    typedef void (*Submit2)(unsigned*, unsigned);
    ((Submit2)(*(int*)(s[0x2b]) + 4))(vals, blocks);
    FUN_01133450();
    SNDPKTPLAY_submit(s[0x28], vals);
    FUN_01133460();
    s[2] += blocks;
    s[0x31] += 1;
    *s += param_3;
}

// @ 0x0112eab0 -- pull one chunk from the stream and submit it.
void FUN_0112eab0(int p)
{
    if (*(int*)(p + 0xb0) == 0)
    {
        int i = 0;
        int* q = (int*)(p + 0xd8);
        do
        {
            if (q[4] == 0)
            {
                int chunk = Stream_GetChunk(*(void**)(p + 0x94));
                if (chunk == 0) return;
                FUN_0112e9b0((int*)p, *(int*)(chunk + 8), *(unsigned*)(chunk + 4), i, 1);
                *q = chunk;
            }
            ++i;
            ++q;
        } while (i < 4);
    }
    else
    {
        if (*(int*)(p + 0xb4) == 0)
        {
            *(int*)(p + 0xb4) = Stream_GetChunk(*(void**)(p + 0x94));
            ((Stream*)*(void**)(p + 0x94))->ReleaseChunk(*(void**)(p + 0xb4));
        }
        int chunk = Stream_GetChunk(*(void**)(p + 0x94));
        if (chunk != 0)
        {
            FUN_0112e9b0((int*)p, *(int*)(chunk + 8), *(unsigned*)(chunk + 4), 0, 0);
            *(int*)(p + 0xd8) = chunk;
            *(int*)(p + 0xb4) = 0;
            *(int*)(p + 0xb0) = 0;
        }
    }
}

// @ 0x0112eb70 -- release the chunk slot matching `id` and pump the stream.
void FUN_0112eb70(int id, int p)
{
    int i = 0;
    int* q = (int*)(p + 0xc8);
    while (i < 4)
    {
        if (id == *q) break;
        ++i;
        ++q;
    }
    *(int*)(p + 0xc4) -= 1;
    int chunk = *(int*)(p + 0xd8 + i * 4);
    if (chunk != 0)
    {
        ((Stream*)*(void**)(p + 0x94))->ReleaseChunk((void*)chunk);
        *(int*)(p + 0xd8 + i * 4) = 0;
    }
    *(int*)(p + 0xe8 + i * 4) = 0;
    if (*(int*)(p + 0xc4) == 0 && *(int*)(p + 0x90) == 0)
        *(int*)(p + 0xc) = 3;
    FUN_0112eab0(p);
}

}}} // namespace rw::audio::core
