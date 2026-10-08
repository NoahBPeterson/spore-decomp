// RenderWare 4 rwaudio core: sample-buffer mixing kernels and the rwaudio
// TimerManager / System registry helpers (prebuilt MSVC library code inside SporeApp.exe).
// Built with VC .NET 2003 (cl 13.10) and link-time code generation (/GL + /LTCG); most
// call-bearing functions cannot be byte-exact from a single-object /vc71 compile.
// compile with /vc71 /O2 /MD /Gy /TP
#include "types.h"
#include <string.h>

// The original zero-fill calls go through the memset import thunk (0x011e073e).
extern "C" void* __cdecl rw_memset(void* dst, int value, unsigned bytes); // 0x011e073e

// -------------------------------------------------------------------------------------
// Mix kernels (rw::audio::core) -- the fixed source->destination channel remap
// functions, the dispatcher, and the two primitives they call. The X360 bodies are
// documented in the BurnoutDecomp RenderWare reconstruction; these are the x86 (cdecl)
// spellings. The two primitives live in a sibling TU (0x01134260 / 0x011342c0).
// -------------------------------------------------------------------------------------
namespace rw { namespace audio { namespace core {

void CopyWithGain(float* pDst, const float* pSrc, float gain, int numSamples); // 0x01134260
void MixWithGain(float* pDst, const float* pSrc, float gain, int numSamples);  // 0x011342c0

static const float KF_CHANNEL_FOLD = 0.70700002f;

// @ 0x0112ce20 -- mono -> stereo inline form (both at gain * 0.707).
void ReChannelGainWrite1x2(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    const float scaled = gain * KF_CHANNEL_FOLD;
    CopyWithGain(ppDst[0], ppSrc[0], scaled, numSamples);
    CopyWithGain(ppDst[1], ppSrc[0], scaled, numSamples);
}

// @ 0x0112ce70 -- mono -> quad: equal-power FL/FR, rears zeroed.
void ReChannelGainWrite1x4(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    const float scaled = gain * KF_CHANNEL_FOLD;
    CopyWithGain(ppDst[0], ppSrc[0], scaled, numSamples);
    CopyWithGain(ppDst[1], ppSrc[0], scaled, numSamples);
    const unsigned bytes = (unsigned)numSamples << 2;
    rw_memset(ppDst[2], 0, bytes);
    rw_memset(ppDst[3], 0, bytes);
}

// @ 0x0112cee0 -- mono -> 5.1: straight into the centre channel, others zeroed.
void ReChannelGainWrite1x6(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    CopyWithGain(ppDst[1], ppSrc[0], gain, numSamples);
    const unsigned bytes = (unsigned)numSamples << 2;
    rw_memset(ppDst[0], 0, bytes);
    rw_memset(ppDst[2], 0, bytes);
    rw_memset(ppDst[3], 0, bytes);
    rw_memset(ppDst[4], 0, bytes);
    rw_memset(ppDst[5], 0, bytes);
}

// @ 0x0112cf50 -- stereo -> mono: L then R accumulated into dst channel 0.
void ReChannelGainWrite2x1(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    CopyWithGain(ppDst[0], ppSrc[0], gain, numSamples);
    MixWithGain(ppDst[0], ppSrc[1], gain, numSamples);
}

// @ 0x0112cfa0 -- stereo -> stereo: two straight copies.
void ReChannelGainWrite2x2(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    CopyWithGain(ppDst[0], ppSrc[0], gain, numSamples);
    CopyWithGain(ppDst[1], ppSrc[1], gain, numSamples);
}

// @ 0x0112cff0 -- stereo -> quad: L/R fronts, rears zeroed.
void ReChannelGainWrite2x4(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    CopyWithGain(ppDst[0], ppSrc[0], gain, numSamples);
    CopyWithGain(ppDst[1], ppSrc[1], gain, numSamples);
    const unsigned bytes = (unsigned)numSamples << 2;
    rw_memset(ppDst[2], 0, bytes);
    rw_memset(ppDst[3], 0, bytes);
}

// @ 0x0112d050 -- stereo -> 5.1: L->FL, R->FR; centre/rears/LFE zeroed.
void ReChannelGainWrite2x6(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    CopyWithGain(ppDst[0], ppSrc[0], gain, numSamples);
    CopyWithGain(ppDst[2], ppSrc[1], gain, numSamples);
    const unsigned bytes = (unsigned)numSamples << 2;
    rw_memset(ppDst[1], 0, bytes);
    rw_memset(ppDst[3], 0, bytes);
    rw_memset(ppDst[4], 0, bytes);
    rw_memset(ppDst[5], 0, bytes);
}

// @ 0x0112d0d0 -- quad -> mono: sum all four into dst channel 0.
void ReChannelGainWrite4x1(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    float* dst0 = ppDst[0];
    CopyWithGain(dst0, ppSrc[0], gain, numSamples);
    MixWithGain(dst0, ppSrc[1], gain, numSamples);
    MixWithGain(dst0, ppSrc[2], gain, numSamples);
    MixWithGain(dst0, ppSrc[3], gain, numSamples);
}

// @ 0x0112d140 -- quad -> stereo: L = FL + BL, R = FR + BR.
void ReChannelGainWrite4x2(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    float* dst0 = ppDst[0];
    CopyWithGain(dst0, ppSrc[0], gain, numSamples);
    MixWithGain(dst0, ppSrc[2], gain, numSamples);
    float* dst1 = ppDst[1];
    CopyWithGain(dst1, ppSrc[1], gain, numSamples);
    MixWithGain(dst1, ppSrc[3], gain, numSamples);
}

// @ 0x0112d1c0 -- quad -> quad: four straight copies.
void ReChannelGainWrite4x4(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    CopyWithGain(ppDst[0], ppSrc[0], gain, numSamples);
    CopyWithGain(ppDst[1], ppSrc[1], gain, numSamples);
    CopyWithGain(ppDst[2], ppSrc[2], gain, numSamples);
    CopyWithGain(ppDst[3], ppSrc[3], gain, numSamples);
}

// @ 0x0112d240 -- quad -> 5.1: FL/FR/BL/BR; centre and LFE zeroed.
void ReChannelGainWrite4x6(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    CopyWithGain(ppDst[0], ppSrc[0], gain, numSamples);
    CopyWithGain(ppDst[2], ppSrc[1], gain, numSamples);
    CopyWithGain(ppDst[3], ppSrc[2], gain, numSamples);
    CopyWithGain(ppDst[4], ppSrc[3], gain, numSamples);
    const unsigned bytes = (unsigned)numSamples << 2;
    rw_memset(ppDst[1], 0, bytes);
    rw_memset(ppDst[5], 0, bytes);
}

// @ 0x0112d2e0 -- 5.1 -> mono fold-down (LFE omitted): centre, then FR, BR, BL, FL.
void ReChannelGainWrite6x1(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    float* dst0 = ppDst[0];
    CopyWithGain(dst0, ppSrc[1], gain, numSamples);
    MixWithGain(dst0, ppSrc[2], gain, numSamples);
    MixWithGain(dst0, ppSrc[4], gain, numSamples);
    MixWithGain(dst0, ppSrc[3], gain, numSamples);
    MixWithGain(dst0, ppSrc[0], gain, numSamples);
}

// @ 0x0112d370 -- 5.1 -> stereo fold-down: L = 0.707*C + FL + BL, R = 0.707*C + FR + BR.
void ReChannelGainWrite6x2(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    const float foldGain = gain * KF_CHANNEL_FOLD;
    float* dst0 = ppDst[0];
    CopyWithGain(dst0, ppSrc[1], foldGain, numSamples);
    MixWithGain(dst0, ppSrc[0], gain, numSamples);
    MixWithGain(dst0, ppSrc[3], gain, numSamples);
    float* dst1 = ppDst[1];
    CopyWithGain(dst1, ppSrc[1], foldGain, numSamples);
    MixWithGain(dst1, ppSrc[2], gain, numSamples);
    MixWithGain(dst1, ppSrc[4], gain, numSamples);
}

// @ 0x0112d420 -- 5.1 -> quad fold-down: FL' = 0.707*C + FL, FR' = 0.707*C + FR, BL/BR.
void ReChannelGainWrite6x4(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    const float foldGain = gain * KF_CHANNEL_FOLD;
    CopyWithGain(ppDst[0], ppSrc[1], foldGain, numSamples);
    MixWithGain(ppDst[0], ppSrc[0], gain, numSamples);
    CopyWithGain(ppDst[1], ppSrc[1], foldGain, numSamples);
    MixWithGain(ppDst[1], ppSrc[2], gain, numSamples);
    CopyWithGain(ppDst[2], ppSrc[3], gain, numSamples);
    CopyWithGain(ppDst[3], ppSrc[4], gain, numSamples);
}

// @ 0x0112d4e0 -- 5.1 -> 5.1: six straight copies (centre first, as the asm orders them).
void ReChannelGainWrite6x6(float** ppDst, float** ppSrc, float gain, int numSamples)
{
    CopyWithGain(ppDst[1], ppSrc[1], gain, numSamples);
    CopyWithGain(ppDst[0], ppSrc[0], gain, numSamples);
    CopyWithGain(ppDst[2], ppSrc[2], gain, numSamples);
    CopyWithGain(ppDst[3], ppSrc[3], gain, numSamples);
    CopyWithGain(ppDst[4], ppSrc[4], gain, numSamples);
    CopyWithGain(ppDst[5], ppSrc[5], gain, numSamples);
}

// @ 0x0112d590 -- the channel-remap dispatcher (x86 arg order:
// ppDst, ppSrc, gain, numDstChannels, numSrcChannels, numSamples).
void ReChannelGainWrite(float** ppDst, float** ppSrc, float gain,
                        unsigned numDstChannels, unsigned numSrcChannels, int numSamples)
{
    switch (numSrcChannels)
    {
    case 1u:
        switch (numDstChannels)
        {
        case 1u:
            CopyWithGain(ppDst[0], ppSrc[0], gain, numSamples);
            return;
        case 2u: ReChannelGainWrite1x2(ppDst, ppSrc, gain, numSamples); return;
        case 4u: ReChannelGainWrite1x4(ppDst, ppSrc, gain, numSamples); return;
        case 6u: ReChannelGainWrite1x6(ppDst, ppSrc, gain, numSamples); return;
        default: break;
        }
        break;
    case 2u:
        switch (numDstChannels)
        {
        case 1u: ReChannelGainWrite2x1(ppDst, ppSrc, gain, numSamples); return;
        case 2u: ReChannelGainWrite2x2(ppDst, ppSrc, gain, numSamples); return;
        case 4u: ReChannelGainWrite2x4(ppDst, ppSrc, gain, numSamples); return;
        case 6u: ReChannelGainWrite2x6(ppDst, ppSrc, gain, numSamples); return;
        default: break;
        }
        break;
    case 4u:
        switch (numDstChannels)
        {
        case 1u: ReChannelGainWrite4x1(ppDst, ppSrc, gain, numSamples); return;
        case 2u: ReChannelGainWrite4x2(ppDst, ppSrc, gain, numSamples); return;
        case 4u: ReChannelGainWrite4x4(ppDst, ppSrc, gain, numSamples); return;
        case 6u: ReChannelGainWrite4x6(ppDst, ppSrc, gain, numSamples); return;
        default: break;
        }
        break;
    case 6u:
        switch (numDstChannels)
        {
        case 1u: ReChannelGainWrite6x1(ppDst, ppSrc, gain, numSamples); return;
        case 2u: ReChannelGainWrite6x2(ppDst, ppSrc, gain, numSamples); return;
        case 4u: ReChannelGainWrite6x4(ppDst, ppSrc, gain, numSamples); return;
        case 6u: ReChannelGainWrite6x6(ppDst, ppSrc, gain, numSamples); return;
        default: break;
        }
        break;
    default:
        break;
    }

    // Generic fallback: copy the channels that overlap, zero-fill any surplus destination.
    if (numSrcChannels < numDstChannels)
    {
        unsigned copied = 0;
        for (; copied < numSrcChannels; ++copied)
            CopyWithGain(ppDst[copied], ppSrc[copied], gain, numSamples);

        const unsigned bytes = (unsigned)numSamples << 2;
        for (unsigned ch = copied; ch < numDstChannels; ++ch)
            rw_memset(ppDst[ch], 0, bytes);
    }
    else
    {
        for (unsigned ch = 0; ch < numDstChannels; ++ch)
            CopyWithGain(ppDst[ch], ppSrc[ch], gain, numSamples);
    }
}

}} } // namespace rw::audio::core

// -------------------------------------------------------------------------------------
// rwaudio TimerManager / Collection / System / PlugIn helpers.
//
// Class layouts are the exact x86 (32-bit) PDB layouts. Collection is a block-pooled
// doubly-linked node container; TimerManager owns two of them plus a deferred-remove
// slot; PlugInDescRunTime is the run-time plug-in descriptor. Several callees live in
// sibling TUs and are only declared here (annotated with their original address).
// -------------------------------------------------------------------------------------
namespace rw { namespace audio { namespace core {

// ---- ListDNode / Collection -------------------------------------------------------
struct ListDNode
{
    ListDNode* pnext; // +0x0
    ListDNode* pprev; // +0x4
};

class Collection
{
public:
    struct Node // Collection::ItemNode
    {
        Node* mpNext;     // +0x0
        Node* mpPrev;     // +0x4
        void** mppOwner;  // +0x8 (owner is &handle->mItemHandleNode)
    };

    void* mpBlockHead;   // +0x0
    void* mpBlockTail;   // +0x4
    int   miBlockCount;  // +0x8
    Node* mpFreeHead;    // +0xc
    Node* mpUsedHead;    // +0x10
    int   mSize;         // +0x14
    int   mCapacity;     // +0x18

    int AddCapacity(int count);        // 0x01133ad0
    bool AddItem(void** outOwner);     // 0x01133bd0
    Node* GetUsedHead();               // 0x01133b60
    Node* UnlinkUsed(void** owner);    // 0x01133a60
    void RemoveNode(void** owner);     // 0x01133c30
    void RemoveUsedNode(Node* node);   // 0x01133a80
    void Defragment();                 // 0x01133c90
    Collection* Clear();               // 0x01133e30
    Collection* Release();             // 0x01133b70
};

// ---- TimerHandle / TimerManager ---------------------------------------------------
struct TimerHandle
{
    void* mpItemHandleNode;         // +0x0  ItemHandle::pNode
    void* mpCallback;               // +0x4
    void* mpContext;                // +0x8
    const char* mpName;             // +0xc
    unsigned int mCpuTicks;         // +0x10
    unsigned char mStage;           // +0x14
    unsigned char mTimerVisibility; // +0x15
};

struct TimerManager
{
    Collection maCollections[2]; // +0x0
    float mfCallbackTime;        // +0x38
    TimerHandle* mpCurrentHandle;// +0x3c
    int miCurrentCollection;     // +0x40
    Collection::Node* mpDeferredRemoveNode; // +0x44

    TimerManager();                            // 0x0112da90
    bool AddTimer(TimerHandle* handle, void* callback, void* context, const char* name,
                  int collectionIndex, unsigned char visibility); // 0x0112d8e0
    void RemoveTimer(TimerHandle* handle);     // 0x0112d940
    void ExecuteTimers(int collectionIndex);   // 0x0112d9b0
    void Defragment();                         // 0x0112da30
    void Release();                            // 0x0112da60
};

// @ 0x0112d8e0 -- register `handle` in collection `collectionIndex` and fill it in.
bool TimerManager::AddTimer(TimerHandle* handle, void* callback, void* context,
                            const char* name, int collectionIndex, unsigned char visibility)
{
    Collection* pCollection = &maCollections[collectionIndex];
    if (pCollection->mCapacity == 0)
        pCollection->AddCapacity(74);

    bool result = pCollection->AddItem(&handle->mpItemHandleNode);
    if (!result)
    {
        handle->mpCallback = callback;
        handle->mpContext = context;
        handle->mpName = name;
        handle->mStage = (unsigned char)collectionIndex;
        handle->mTimerVisibility = visibility;
        handle->mCpuTicks = 0;
    }
    return result;
}

// @ 0x0112d940 -- unregister `handle`; defer the unlink if it is currently executing.
void TimerManager::RemoveTimer(TimerHandle* handle)
{
    if (handle == mpCurrentHandle)
    {
        miCurrentCollection = handle->mStage;
        mpDeferredRemoveNode = maCollections[handle->mStage].UnlinkUsed(&handle->mpItemHandleNode);
    }
    else
    {
        if (handle->mStage != 3)
            maCollections[handle->mStage].RemoveNode(&handle->mpItemHandleNode);
    }
    handle->mStage = 3;
    handle->mCpuTicks = 0;
}

// @ 0x0112d9b0 -- run every timer in collection `collectionIndex`.
void TimerManager::ExecuteTimers(int collectionIndex)
{
    Collection::Node* node = maCollections[collectionIndex].GetUsedHead();
    while (node)
    {
        TimerHandle* handle = (TimerHandle*)node->mppOwner;

        mpDeferredRemoveNode = 0;
        mpCurrentHandle = handle;
        typedef void (*TimerCallback)(void* context, float time);
        ((TimerCallback)handle->mpCallback)(handle->mpContext, mfCallbackTime);

        Collection::Node* deferred = mpDeferredRemoveNode;
        mpCurrentHandle = 0;
        node = node->mpNext;

        if (deferred)
        {
            maCollections[miCurrentCollection].RemoveUsedNode(deferred);
            mpDeferredRemoveNode = 0;
        }
        else
        {
            handle->mCpuTicks = 0;
        }
    }
}

// @ 0x0112da30 -- compact both owned collections.
void TimerManager::Defragment()
{
    Collection* p = maCollections;
    int n = 2;
    while (n--)
    {
        p->Defragment();
        ++p;
    }
}

// @ 0x0112da60 -- clear then release both owned collections.
void TimerManager::Release()
{
    Collection* p = maCollections;
    int n = 2;
    while (n--)
    {
        p->Clear();
        p->Release();
        ++p;
    }
}

// @ 0x0112da90 -- zero both collections, seed the callback time to -1, clear the defer slot.
TimerManager::TimerManager()
{
    for (int i = 0; i < 2; ++i)
    {
        Collection& c = maCollections[i];
        c.mpBlockHead = 0;
        c.mpBlockTail = 0;
        c.miBlockCount = 0;
        c.mpFreeHead = 0;
        c.mpUsedHead = 0;
        c.mSize = 0;
        c.mCapacity = 0;
    }
    mfCallbackTime = -1.0f;
    mpDeferredRemoveNode = 0;
}

// ---- PlugIn / PlugInRegistry ------------------------------------------------------
struct PlugInDescRunTime;

class PlugIn
{
public:
    void** vftable;                  // +0x0
    void* mpSystemUseGetSystemAccessor; // +0x4
    void* mpVoice;                   // +0x8
    const char* mpAttribute;         // +0xc
    PlugInDescRunTime* mpPlugInDescRunTime; // +0x10
    float mLatencyInSamples;         // +0x14

    PlugIn* Initialize_SndPlayer1();    // 0x0112dbb0 (PlugIn::Initialize<SndPlayer1>)
};

// @ 0x0112dbb0 -- PlugIn::Initialize<SndPlayer1>: clear the vtable, name "Unknown",
// null the run-time descriptor and set the latency byte to 3. Returns `this`.
PlugIn* PlugIn::Initialize_SndPlayer1()
{
    vftable = 0;
    mpAttribute = "Unknown";
    mpPlugInDescRunTime = 0;
    *(unsigned char*)&mLatencyInSamples = 3;
    return this;
}

// Run-time plug-in descriptor (x86 PDB layout, size 0x34).
struct EventDescRunTime
{
    int numParameters;               // +0x0
    void* pEventDescToolSide;        // +0x4
};

struct ParameterDescRunTime
{
    int parameterDirection;          // +0x0
    int parameterType;               // +0x4
    double minExtremeValue;          // +0x8
    double maxExtremeValue;          // +0x10
    void* pParameterDescToolSide;    // +0x18
};

struct PlugInDescRunTime
{
    char* name;                              // +0x0
    void* GetSize;                           // +0x4
    void* CreateInstance;                    // +0x8
    void* pPreProcess;                       // +0xc
    void* pProcess;                          // +0x10
    void* pChannelMaps;                      // +0x14
    ParameterDescRunTime* pParameterDescRunTime; // +0x18
    EventDescRunTime* pEventDescRunTime;     // +0x1c
    void* pPlugInDescToolSide;               // +0x20
    void* listNode;                          // +0x24
    unsigned int guid;                       // +0x28
    unsigned char plugInType;                // +0x2c
    unsigned char numConstructorParameters;  // +0x2d
    unsigned char numAttributes;             // +0x2e
    unsigned char numEvents;                 // +0x2f
    unsigned char isVariableInputChannels;   // +0x30
    unsigned char isVariableOutputChannels;  // +0x31
    unsigned char registryIndex;             // +0x32
};

// @ 0x0112dae0 -- wire a PlugInDescRunTime's parameter/event tool-side pointers to the
// loaded default-value arrays: parameter entries get pParameterDescToolSide =
// pDefaults + i*0x30; event entries get pEventDescToolSide = pEventDefaults + i*0x10.
void PlugInDescFixup(PlugInDescRunTime* desc, char* pDefaults, char* pEventDefaults)
{
    unsigned index = 0;

    for (unsigned i = 0; i < desc->numConstructorParameters; ++i, ++index)
        desc->pParameterDescRunTime[index].pParameterDescToolSide = pDefaults + index * 0x30;

    for (unsigned i = 0; i < desc->numAttributes; ++i, ++index)
        desc->pParameterDescRunTime[index].pParameterDescToolSide = pDefaults + index * 0x30;

    for (unsigned i = 0; i < desc->numEvents; ++i)
    {
        desc->pEventDescRunTime[i].pEventDescToolSide = pEventDefaults + i * 0x10;
        for (int j = 0; j < desc->pEventDescRunTime[i].numParameters; ++j, ++index)
            desc->pParameterDescRunTime[index].pParameterDescToolSide = pDefaults + index * 0x30;
    }
}

// Plug-in descriptor getters (each returns a pointer to a static descriptor).
PlugInDescRunTime* GetPlugInDesc_1136c30(); // 0x01136c30
PlugInDescRunTime* GetPlugInDesc_1136c40(); // 0x01136c40
PlugInDescRunTime* GetPlugInDesc_1136c50(); // 0x01136c50
PlugInDescRunTime* GetPlugInDesc_1136af0(); // 0x01136af0
PlugInDescRunTime* GetPlugInDesc_1134ad0(); // 0x01134ad0
PlugInDescRunTime* GetPlugInDesc_1134730(); // 0x01134730
PlugInDescRunTime* GetPlugInDesc_1134720(); // 0x01134720
PlugInDescRunTime* GetPlugInDesc_1134710(); // 0x01134710
PlugInDescRunTime* GetPlugInDesc_11346f0(); // 0x011346f0
PlugInDescRunTime* GetPlugInDesc_11346d0(); // 0x011346d0
PlugInDescRunTime* GetPlugInDesc_11346c0(); // 0x011346c0
PlugInDescRunTime* GetPlugInDesc_11343a0(); // 0x011343a0
PlugInDescRunTime* GetPlugInDesc_1134370(); // 0x01134370

// PlugInRegistry (x86 PDB layout, size 0x18).
class PlugInRegistry
{
public:
    void* mpHead;                 // +0x0  mPlugInDescRunTimeList.phead
    void* mppTail;                // +0x4  mPlugInDescRunTimeList.ptail
    int   muCount;                // +0x8  mPlugInDescRunTimeList.entries
    void* mpEnumerator;           // +0xc
    void* mpSystem;               // +0x10
    unsigned char mCurrentRegistryIndex; // +0x14

    PlugInDescRunTime* RegisterPlugInRunTime(PlugInDescRunTime* info); // 0x01133f00
    void RegisterBuiltInPlugIns();           // 0x0112dbd0
};

// @ 0x0112dbd0 -- register every built-in plug-in descriptor.
void PlugInRegistry::RegisterBuiltInPlugIns()
{
    RegisterPlugInRunTime(GetPlugInDesc_1136c30());
    RegisterPlugInRunTime(GetPlugInDesc_1136c40());
    RegisterPlugInRunTime(GetPlugInDesc_1136c50());
    RegisterPlugInRunTime(GetPlugInDesc_1136af0());
    RegisterPlugInRunTime(GetPlugInDesc_1134ad0());
    RegisterPlugInRunTime(GetPlugInDesc_1134730());
    RegisterPlugInRunTime(GetPlugInDesc_1134720());
    RegisterPlugInRunTime(GetPlugInDesc_1134710());
    RegisterPlugInRunTime(GetPlugInDesc_11346f0());
    RegisterPlugInRunTime(GetPlugInDesc_11346d0());
    RegisterPlugInRunTime(GetPlugInDesc_11346c0());
    RegisterPlugInRunTime(GetPlugInDesc_11343a0());
    RegisterPlugInRunTime(GetPlugInDesc_1134370());
}

// ---- rw::audio::core::System (subset) ---------------------------------------------
class System;
class DecoderRegistry;

DecoderRegistry* CreateDecoderRegistry(System* system); // 0x01133f80

class System
{
public:
    void* mpStackAllocator;        // +0x0
    void* mpAssertImplementation;  // +0x4
    double mSystemTime;            // +0x8
    void* mExpelledVoiceList;      // +0x10
    void* mpAllocator;             // +0x14
    void* mpPhysicalAlloc;         // +0x18
    void* mpPhysicalFree;          // +0x1c
    char* mpCommandBuffer;         // +0x20
    void* mpMasteringSubMix;       // +0x24
    PlugInRegistry* mpPlugInRegistry; // +0x28
    DecoderRegistry* mpDecoderRegistry; // +0x2c

    DecoderRegistry* GetDecoderRegistry(); // 0x0112dc80
};

// @ 0x0112dc80 -- lazily create and return the decoder registry.
DecoderRegistry* System::GetDecoderRegistry()
{
    extern System* g_pAudioSystem; // 0x016e61a8
    if (mpDecoderRegistry == 0)
        mpDecoderRegistry = CreateDecoderRegistry(g_pAudioSystem);
    return mpDecoderRegistry;
}

}}} // namespace rw::audio::core
