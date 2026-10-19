// src/game/plugins/sndplayer1.cpp.cpp -- migrated from slice(s) s011388f0, s01137aa0, s0112dca0, s0112ce20 by tools/migrate/rewrite.py
// Object file: plugins/sndplayer1.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/PlugIn.h"
#include "rw/audio/core/PlugInDescRunTime.h"
#include <string.h>
#include "rw/audio/core/DecoderRegistry.h"
#include "rw/audio/core/StreamPool.h"
#include "rw/audio/core/System.h"
#include "rw/audio/core/TimerHandle.h"
#include "rw/audio/core/Voice.h"
#include <xmmintrin.h>
#include <emmintrin.h>
#include "rw/audio/core/SubMix.h"
#include "rw/audio/core/TimerManager.h"

// ---- items of slice s0112ce20 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace audio {
namespace core {
struct PlugInDescRunTime_s0112_ce20;
}
}
}
namespace rw {
namespace audio {
namespace core {
class PlugIn_s0112_ce20
{
public:
    void** vftable;                  // +0x0
    void* mpSystemUseGetSystemAccessor; // +0x4
    void* mpVoice;                   // +0x8
    const char* mpAttribute;         // +0xc
    PlugInDescRunTime_s0112_ce20* mpPlugInDescRunTime; // +0x10
    float mLatencyInSamples;         // +0x14

    PlugIn_s0112_ce20* Initialize_SndPlayer1();    // 0x0112dbb0 (PlugIn::Initialize<SndPlayer1>)
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct EventDescRunTime
{
    int numParameters;               // +0x0
    void* pEventDescToolSide;        // +0x4
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct ParameterDescRunTime
{
    int parameterDirection;          // +0x0
    int parameterType;               // +0x4
    double minExtremeValue;          // +0x8
    double maxExtremeValue;          // +0x10
    void* pParameterDescToolSide;    // +0x18
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct PlugInDescRunTime_s0112_ce20
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
}
}
}
// ---- items of slice s0112ce20 end

// ---- items of slice s0112dca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma function(memcpy)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
namespace rw {
namespace audio {
namespace core {
struct ListDNode_s0112_dca0 { ListDNode_s0112_dca0* pnext; ListDNode_s0112_dca0* pprev; };
}
}
}
namespace rw {
namespace audio {
namespace core {
struct System_s0112_dca0;
}
}
}
namespace rw {
namespace audio {
namespace core {
struct StreamPool_s0112_dca0;
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
struct StreamPool_s0112_dca0
{
    System_s0112_dca0*      mpSystem;       // +0x0
    StreamDesc_s0112_dca0*  mpStreamDesc;   // +0x4
    u8           mTimerHandle[0x18]; // +0x8
    void*        mpAllocator;    // +0x20
    u32          mGuid;          // +0x24
    u8           mNumStreams;    // +0x28
    char         pad1[3];
    ListDNode_s0112_dca0    mListNode;      // +0x2c

    void QueueRelease();         // 0x0112e410
    StreamDesc_s0112_dca0* AcquireStream(float priority, void* streamLost, int context); // 0x0112dfa0
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct System_s0112_dca0
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
}
}
}
// ---- items of slice s0112dca0 end

// ---- items of slice s01137aa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_one;                        // 0x01485720
extern const float g_reqHandleMax;               // 0x014ab748
extern const int   g_codecTable[];               // 0x014ab6f8
extern "C" int FUN_01137cd0(void* rec);          // 0x01137cd0
extern "C" int FUN_01137a30(void* rec);          // 0x01137a30
extern "C" int FUN_01137d60(char* data, unsigned int size, int, int, int, int, unsigned int* out);
namespace rw {
namespace audio {
namespace core {
struct System_s0113_7aa0;
}
}
}
namespace rw {
namespace audio {
namespace core {
struct Voice_s0113_7aa0;
}
}
}
namespace rw {
namespace audio {
namespace core {
struct Decoder;
}
}
}
namespace rw {
namespace audio {
namespace core {
struct DecoderRegistry_s0113_7aa0;
}
}
}
namespace rw {
namespace audio {
namespace core {
struct StreamPool_s0113_7aa0;
}
}
}
namespace rw {
namespace audio {
namespace core {
struct PlugInDescRunTime_s0113_7aa0;
}
}
}
namespace rw {
namespace audio {
namespace core {
struct Stream;
}
}
}
namespace rw {
namespace audio {
namespace core {
struct Attribute_t_s0113_7aa0 { union { double f64; float f32; }; };
}
}
}
namespace rw {
namespace audio {
namespace core {
struct PlugIn_s0113_7aa0 {
    void** vftable;                          // +0x00
    System_s0113_7aa0* mpSystem;                        // +0x04
    Voice_s0113_7aa0* mpVoice;                          // +0x08
    Attribute_t_s0113_7aa0* mpAttribute;                // +0x0c
    PlugInDescRunTime_s0113_7aa0* mpPlugInDescRunTime;  // +0x10
    float mLatencyInSamples;                 // +0x14
    float mDecaySamples;                     // +0x18
    unsigned int mCpuTicks;                  // +0x1c
    unsigned char mInputChannels;            // +0x20
    unsigned char mOutputChannels;           // +0x21
    unsigned char pad22[2];
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct TimerHandle_s0113_7aa0 {
    void* mItemHandle;              // +0x00
    void* mpCallback;               // +0x04
    void* mpContext;                // +0x08
    char* mpName;                   // +0x0c
    unsigned int mCpuTicks;         // +0x10
    unsigned char mStage;           // +0x14
    unsigned char mTimerVisibility; // +0x15
    unsigned char pad16[2];
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct ChunkInfo {
    int   f00;      // +0x00
    int   size;     // +0x04
    char* pData;    // +0x08
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct Stream {
    char pad00[4];
    int  QueueFile(int a0, int a1, int a2, void* cb, int cbArg); // 0x011e69d0
    ChunkInfo* GetChunk();                                       // 0x011e6b50
    int  FUN_011e6bf0();                                         // 0x011e6bf0
    int  FUN_011e6c00(int);                                      // 0x011e6c00
    int  FUN_011e6c40();                                         // 0x011e6c40
    int  FUN_011e6c80(int);                                      // 0x011e6c80
    int  FUN_011e7c70(ChunkInfo*);                               // 0x011e7c70
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct StreamPool_s0113_7aa0 {
    void* CreateStream(float rate, void* cb, void* ctx);         // 0x0112dfa0
    void  ReleaseStream(void* handle);                           // 0x0112e1e0
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct System_s0113_7aa0 {
    char pad00[0x20];
    char* mpCommandBuffer;       // +0x20
    char pad24[0x90];
    unsigned int mCommandIndex;  // +0xb4

    void* Alloc(int size, const char* name, int align, int alloc); // 0x0112c820
    void  Free(void* p, int alloc);                                // 0x0112c850
    void  RemoveTimer(TimerHandle_s0113_7aa0* t);                             // 0x0112dad0
    int   Lock();                                                  // 0x0112c600
    int   Unlock();                                                // 0x0112c620
    DecoderRegistry_s0113_7aa0* GetDecoderRegistry();                         // 0x0112dc80
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct Voice_s0113_7aa0 {
    char pad00[0x38];
    float mPriority;             // +0x38
    void  FUN_0112e450();        // 0x0112e450
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct Decoder {
    char pad00[0x20];
    unsigned short mNumChannels; // +0x20
    char FUN_0114c8c0(char* data, unsigned int size, int flag,
                      int a3, void* a4, int a5);                 // 0x0114c8c0
    void FUN_01133f40();                                         // 0x01133f40
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct DecoderRegistry_s0113_7aa0 {
    int  FUN_01133ed0(int key);                                  // 0x01133ed0
    Decoder* DecoderFactory(int codecObj, int codec, int a, System_s0113_7aa0* sys); // 0x01133fc0
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct RequestExternal {           // size 0x50 (PDB)
    double streamFileOffset;       // +0x00
    char*  pSampleData;            // +0x08
    int    loopStartStreamOffset;  // +0x0c
    int    gigaSamplesInRam;       // +0x10
    int    numSamplesFed;          // +0x14
    int    numBytesFed;            // +0x18
    char*  pStreamLoopFileName;    // +0x1c
    StreamPool_s0113_7aa0* pStreamPool;       // +0x20
    void*  streamHandle;           // +0x24
    Stream* pRwCoreStream;         // +0x28
    int    streamerRequestId;      // +0x2c
    char*  pNextChunk;             // +0x30
    char*  pLoopStartChunk;        // +0x34
    void*  pSeekData;              // +0x38
    int    playerSkip;             // +0x3c
    unsigned int seekChunkOffset;  // +0x40
    int    seekDataVersion;        // +0x44
    unsigned char codec;           // +0x48
    unsigned char playType;        // +0x49
    unsigned char feedSlotLatest;  // +0x4a
    unsigned char expelMode;       // +0x4b
    bool   seekChunkIsNewFeed;     // +0x4c
    unsigned char pad4d[3];
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct FeedDesc {                  // size 0x10 (PDB)
    ChunkInfo* pChunkInfo;         // +0x00
    Stream* pRwCoreStream;         // +0x04
    int     chunkSamplesPlayed;    // +0x08
    unsigned char decoderRequestHandle; // +0x0c
    unsigned char feedState;       // +0x0d
    unsigned char requestIndex;    // +0x0e
    unsigned char pad0F;
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct RequestInternal {
    double streamFileOffset;       // +0x00
    Decoder* pDecoder;             // +0x08
    float  handle;                 // +0x0c
    float  f10;                    // +0x10
    int    samplesFed;             // +0x14
    int    f18;                    // +0x18
    void*  f1C;                    // +0x1c
    int    f20;                    // +0x20
    int    f24;                    // +0x24
    unsigned short numChannels;    // +0x28
    unsigned char state;           // +0x2a
    unsigned char codec;           // +0x2b
    int    f2C;                    // +0x2c
};  // 0x30
}
}
}
namespace rw {
namespace audio {
namespace core {
struct SndPlayer1 : PlugIn_s0113_7aa0 {
    Attribute_t_s0113_7aa0 mAttribute[3];                    // +0x28
    TimerHandle_s0113_7aa0 mTimerHandle;                     // +0x40
    RequestExternal* mpRequestExternal;           // +0x58
    FeedDesc mFeedDesc[20];                       // +0x5c
    Decoder* mpLoadedDecoder;                     // +0x19c
    float mCurrentRequestHandle;                  // +0x1a0
    float mCurrentRequestSampleRate;              // +0x1a4
    int   mCurrentRequestSamplesPlayed;           // +0x1a8
    int   mCurrentRequestNumSamples;              // +0x1ac
    float* mpRequestHandle;                       // +0x1b0
    float mLastRequestHandleProcessed;            // +0x1b4
    float mLastRequestHandleSuccessfullyProcessed;// +0x1b8
    float mPreviousSampleRate;                    // +0x1bc
    unsigned short mSamplesRequested;             // +0x1c0
    unsigned short mDeclickBufferOffset;          // +0x1c2
    unsigned short mRequestInternalOffset;        // +0x1c4
    unsigned char mMaxChannels;                   // +0x1c6
    unsigned char mNextFreeRequest;               // +0x1c7
    unsigned char mNextRequestToFree;             // +0x1c8
    unsigned char mCurrentRequest;                // +0x1c9
    unsigned char mMaxRequests;                   // +0x1ca
    unsigned char mDcOffsetsGathered;             // +0x1cb
    unsigned char mNumDeclickSamples;             // +0x1cc
    unsigned char mNextFeedSlotToFill;            // +0x1cd
    unsigned char mNextFeedSlotToFree;            // +0x1ce
    unsigned char mTimerAdded;                    // +0x1cf

    RequestInternal* internal(int i)
    { return (RequestInternal*)((char*)this + mRequestInternalOffset + i * 0x30); }

    void  FreeRequest(int index);                         // 0x01137aa0
    void  FreeFinishedRequests();                         // 0x01137bc0
    void  Shutdown();                                     // 0x01137c90
    void  SendCommand(int cmd, void* param);              // 0x01138130
    char* FeedChunk(char* data, int index, char a, char b);// 0x01138050
    bool  StreamNextChunk(int index, int a3, int a4);     // 0x011384b0
    bool  HandleLoopStart(int index);                     // 0x01138570
    bool  HandleSampleEnd(int index, unsigned char* out); // 0x01138640
    bool  StartRequest(int index);                        // 0x011387b0
    void  FUN_011376d0(int a, int b);                     // 0x011376d0
    void  FUN_011377f0(int a, int b, int c);              // 0x011377f0
    void  FUN_01137950();                                 // 0x01137950
    void  FUN_011379f0(int* out);                         // 0x011379f0
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct PlayRec {
    void* code;             // +0x00
    SndPlayer1* self;       // +0x04
    double f08;             // +0x08
    double f10;             // +0x10
    double f18;             // +0x18
    int    f20;             // +0x20
    int    f24;             // +0x24
    int    f28;             // +0x28
    unsigned short recSize; // +0x2c
    unsigned char f2e;      // +0x2e
    unsigned char f2f;
    float  f30;             // +0x30
    int    f34;
    char   name[1];         // +0x38
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct CmdPayload {
    double f00;
    double f08;
    double f10;
    int    i18;
    int    i1c;
    int    i20;
    int    i24;
    float  f28;
    float  f2c;
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct CmdParam {
    double f00;
    double f08;
    int    i10;
    int    i14;
    int    i18;
    float  f1c;
    float  f20;
};
}
}
}
rw::audio::core::StreamPool_s0113_7aa0* __cdecl FUN_0112df80(int id);   // 0x0112df80
char __cdecl FUN_011e0744(void* dst, const void* src, unsigned int n); // 0x011e0744
namespace rw {
namespace audio {
namespace core {
void __cdecl FreeAllRequests(SndPlayer1* self);  // 0x01137c30
}  // namespace rw::audio::core
}
}
// ---- items of slice s01137aa0 end

// ---- items of slice s011388f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct Voice_s0113_88f0;
}
}
}
namespace rw {
namespace audio {
namespace core {
struct Decoder_s0113_88f0;
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
struct StreamPool_s0113_88f0;
}
}
}
namespace rw {
namespace audio {
namespace core {
struct PlugInDescRunTime_s0113_88f0;
}
}
}
namespace rw {
namespace audio {
namespace core {
struct Stream_s0113_88f0;
}
}
}
namespace rw {
namespace audio {
namespace core {
struct Attribute_t_s0113_88f0 { union { double f64; float f32; }; };
}
}
}
namespace rw {
namespace audio {
namespace core {
struct PlugIn_s0113_88f0 {
    void** vftable; System_s0113_88f0* mpSystem; Voice_s0113_88f0* mpVoice; Attribute_t_s0113_88f0* mpAttribute;
    PlugInDescRunTime_s0113_88f0* mpPlugInDescRunTime; float mLatencyInSamples; float mDecaySamples;
    unsigned int mCpuTicks; unsigned char mInputChannels; unsigned char mOutputChannels; unsigned char pad22[2];
};
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
struct Stream_s0113_88f0 {
    char pad00[4];
    int QueueFile(int, int, int, void*, int); ChunkInfo* GetChunk();
    int FUN_011e6bf0(); int FUN_011e6c00(int); int FUN_011e6c40(); int FUN_011e6c80(int); int FUN_011e7c70(ChunkInfo*);
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct StreamPool_s0113_88f0 {
    void* CreateStream(float, void*, void*);
    void ReleaseStream(void*);
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct System_s0113_88f0 {
    char pad00[0x20]; char* mpCommandBuffer; char pad24[0x90]; unsigned int mCommandIndex; // +0xb4
    void* Alloc(int size, const char* name, int align, int alloc); void Free(void* p, int alloc);
    void RemoveTimer(TimerHandle_s0113_88f0* t); int Lock(); int Unlock(); DecoderRegistry_s0113_88f0* GetDecoderRegistry();
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct Decoder_s0113_88f0 {
    char pad00[0x20]; unsigned short mNumChannels;
    char FUN_0114c8c0(char*, unsigned, int, int, void*, int); void FUN_01133f40();
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct DecoderRegistry_s0113_88f0 {
    int FUN_01133ed0(int);
    Decoder_s0113_88f0* DecoderFactory(int, int, int, System_s0113_88f0*);  // 0x01133fc0 (rw::audio::core::DecoderRegistry::DecoderFactory)
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct RequestExternal_s0113_88f0 {
    double streamFileOffset; char* pSampleData; int loopStartStreamOffset; int gigaSamplesInRam;
    int numSamplesFed; int numBytesFed; char* pStreamLoopFileName; StreamPool_s0113_88f0* pStreamPool;
    void* streamHandle; Stream_s0113_88f0* pRwCoreStream; int streamerRequestId; char* pNextChunk;
    char* pLoopStartChunk; void* pSeekData; int playerSkip; unsigned seekChunkOffset;
    int seekDataVersion; unsigned char codec; unsigned char playType; unsigned char feedSlotLatest;
    unsigned char expelMode; bool seekChunkIsNewFeed; unsigned char pad4d[3];
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct FeedDesc_s0113_88f0 {
    ChunkInfo* pChunkInfo; Stream_s0113_88f0* pRwCoreStream; int chunkSamplesPlayed;
    unsigned char decoderRequestHandle; unsigned char feedState; unsigned char requestIndex; unsigned char pad0F;
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct RequestInternal_s0113_88f0 {
    double streamFileOffset; Decoder_s0113_88f0* pDecoder; float handle; float f10; int samplesFed; int f18;
    void* f1C; int f20; int f24; unsigned short numChannels; unsigned char state; unsigned char codec; int f2C;
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct SndPlayer1_s0113_88f0 : PlugIn_s0113_88f0 {
    Attribute_t_s0113_88f0 mAttribute[3]; TimerHandle_s0113_88f0 mTimerHandle; RequestExternal_s0113_88f0* mpRequestExternal;
    FeedDesc_s0113_88f0 mFeedDesc[20]; Decoder_s0113_88f0* mpLoadedDecoder; float mCurrentRequestHandle; float mCurrentRequestSampleRate;
    int mCurrentRequestSamplesPlayed; int mCurrentRequestNumSamples; float* mpRequestHandle;
    float mLastRequestHandleProcessed; float mLastRequestHandleSuccessfullyProcessed; float mPreviousSampleRate;
    unsigned short mSamplesRequested; unsigned short mDeclickBufferOffset; unsigned short mRequestInternalOffset;
    unsigned char mMaxChannels; unsigned char mNextFreeRequest; unsigned char mNextRequestToFree;
    unsigned char mCurrentRequest; unsigned char mMaxRequests; unsigned char mDcOffsetsGathered;
    unsigned char mNumDeclickSamples; unsigned char mNextFeedSlotToFill; unsigned char mNextFeedSlotToFree;
    unsigned char mTimerAdded;
    RequestInternal_s0113_88f0* internal(int i) { return (RequestInternal_s0113_88f0*)((char*)this + mRequestInternalOffset + i * 0x30); }
    void FreeFinishedRequests(); void FUN_01137950();                     // 0x01137bc0 / 0x01137950
    bool StartRequest(int); bool HandleLoopStart(int);                    // 0x011387b0 / 0x01138570
    bool HandleSampleEnd(int, u8*); bool StreamNextChunk(int, int, int);  // 0x01138640 / 0x011384b0
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
// ---- items of slice s011388f0 end

// @ 0x0112dbb0
namespace rw { namespace audio { namespace core {
PlugIn_s0112_ce20* PlugIn_s0112_ce20::Initialize_SndPlayer1()
{
    vftable = 0;
    mpAttribute = "Unknown";
    mpPlugInDescRunTime = 0;
    *(unsigned char*)&mLatencyInSamples = 3;
    return this;
}
}}}  // namespace rw::audio::core

// @ 0x0112df80
namespace rw { namespace audio { namespace core {
StreamPool_s0112_dca0* StreamPool_GetInstance(u32 guid)
{
    ListDNode_s0112_dca0* node = g_pStreamPoolList;
    while (node)
    {
        if (*(int*)((char*)node - 8) == (int)guid)
            return (StreamPool_s0112_dca0*)((char*)node - 0x2c);
        node = node->pnext;
    }
    return 0;
}
}}}  // namespace rw::audio::core

// @ 0x0112dfa0
namespace rw { namespace audio { namespace core {
StreamDesc_s0112_dca0* StreamPool_s0112_dca0::AcquireStream(float priority, void* streamLost, int context)
{
    StreamPool_s0112_dca0* self = this;
    u32 n = self->mNumStreams;
    for (u32 i = 0; i < n; ++i)
    {
        StreamDesc_s0112_dca0* s = &self->mpStreamDesc[i];
        if (s->allocated != 0 && s->pStreamLostContext != 0 &&
            s->pStreamLostContext == (void*)context)
        {
            s->refCount = (u16)(s->refCount + 1);
            return s;
        }
    }
    for (u32 i = 0; i < n; ++i)
    {
        StreamDesc_s0112_dca0* s = &self->mpStreamDesc[i];
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
    StreamDesc_s0112_dca0* best = 0;
    float bestPri = priority;
    u32 i = 0;
    if (n >= 4)
    {
        u32 blocks = ((n - 4) >> 2) + 1;
        StreamDesc_s0112_dca0* p = self->mpStreamDesc;
        u32 cnt = blocks * 4;
        (void)p;
        for (u32 b = 0; b < blocks; ++b)
        {
            StreamDesc_s0112_dca0* q = &self->mpStreamDesc[i];
            for (int k = 0; k < 4; ++k, ++i)
            {
                StreamDesc_s0112_dca0* s = &q[k];
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
        StreamDesc_s0112_dca0* s = &self->mpStreamDesc[i];
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
}}}  // namespace rw::audio::core

// @ 0x01137bc0
namespace rw { namespace audio { namespace core {
void SndPlayer1::FreeFinishedRequests()
{
    unsigned char b = mNextRequestToFree;
    while (internal(b)->state == 4) {
        FreeRequest(b);
        unsigned char n = (unsigned char)(b + 1);
        b = (n == mMaxRequests) ? 0 : n;
        mNextRequestToFree = b;
    }
}
}}}  // namespace rw::audio::core

// @ 0x01137c30
namespace rw { namespace audio { namespace core {
void __cdecl FreeAllRequests(SndPlayer1* self)
{
    for (unsigned int i = 0; i < self->mMaxRequests; i++)
        if (self->internal(i)->state != 0)
            self->FreeRequest(i);
    self->mCurrentRequest = 0;
    self->mNextFreeRequest = 0;
    self->mNextRequestToFree = 0;
}
}}}  // namespace rw::audio::core

// @ 0x01137c90
namespace rw { namespace audio { namespace core {
void SndPlayer1::Shutdown()
{
    FreeAllRequests(this);
    if (mTimerAdded == 1)
        mpSystem->RemoveTimer(&mTimerHandle);
    if (mpRequestHandle)
        mpSystem->Free(mpRequestHandle, 0);
}
}}}  // namespace rw::audio::core

// @ 0x01137de0
namespace rw { namespace audio { namespace core {
unsigned int __cdecl FUN_01137de0(void* recv)
{
    PlayRec* rec = (PlayRec*)recv;
    SndPlayer1* self = rec->self;
    System_s0113_7aa0* sys = self->mpSystem;

    self->mLastRequestHandleProcessed = rec->f30;

    RequestInternal* ri = self->internal(self->mNextFreeRequest);
    if (ri->state != 0)
        return (unsigned int)rec->recSize;

    RequestExternal* re = &self->mpRequestExternal[self->mNextFreeRequest];

    ri->handle = rec->f30;
    ri->pDecoder = 0;
    ri->streamFileOffset = rec->f08;
    re->streamFileOffset = rec->f10;
    re->expelMode = rec->f2e;
    ri->state = 1;
    re->numSamplesFed = 0;
    re->numBytesFed = 0;
    re->streamHandle = 0;
    re->streamerRequestId = 0;
    re->pStreamLoopFileName = 0;

    self->FUN_011376d0(self->mNextFreeRequest, rec->f24);

    // The original converts the x87 float*double product with `fistp dword`, which rounds to
    // nearest (FPCW 0x027F) and yields 0x80000000 on overflow/NaN. A plain (int) cast uses
    // __ftol2, which truncates and returns the low 32 bits of an int64 (differing in
    // [2^31, 2^63)). `cvtsd2si` (round-nearest per MXCSR, integer-indefinite on overflow)
    // reproduces the original exactly; the product must round to double first, so pass it
    // through _mm_set_sd rather than letting it stay in an extended-precision x87 register.
    int n = _mm_cvtsd_si32(_mm_set_sd((double)ri->f10 * rec->f18));
    if (n <= 0)
        n = 0;
    if (n != 0) {
        if (re->playType == 2)
            n = 0;
        if (ri->f18 >= 0)
            n = 0;
    }
    if (n < ri->samplesFed) {
        self->FUN_011377f0(self->mNextFreeRequest, rec->f28, n);

        unsigned char pt = re->playType;
        if (pt == 1 || pt == 2) {
            StreamPool_s0113_7aa0* pool = FUN_0112df80(rec->f20);
            re->pStreamPool = pool;
            void* h = pool->CreateStream(self->mpVoice->mPriority,
                                         (void*)&FreeAllRequests, self);
            re->streamHandle = h;
            if (!h)
                goto fail;
            re->pRwCoreStream = *(Stream**)((char*)h + 0x14);
            if (ri->f18 >= 0) {
                char* nm = rec->name;
                char* e = nm;
                while (*e)
                    e++;
                unsigned int len = (unsigned int)(e - nm) + 1;
                void* dst = sys->Alloc((int)len, "SndPlayer1 StreamLoopFileName", 0x10, 0);
                re->pStreamLoopFileName = (char*)dst;
                if (!dst)
                    goto fail;
                FUN_011e0744(dst, nm, len);
            }
            if (!(re->playType == 2 && ri->f18 >= 0 && re->gigaSamplesInRam > ri->f18)) {
                __int64 off = (__int64)((double)re->seekChunkOffset + re->streamFileOffset);
                int id = re->pRwCoreStream->QueueFile(
                    (int)rec->name, (int)(unsigned int)off,
                    (int)((unsigned __int64)off >> 32), (void*)&FUN_01137d60, (int)self);
                re->streamerRequestId = id;
            }
            if (ri->f18 >= 0 &&
                !(re->playType == 2 && re->gigaSamplesInRam < ri->samplesFed)) {
                for (int k = 0; k < 2; k++) {
                    __int64 off = (__int64)((double)re->loopStartStreamOffset + re->streamFileOffset);
                    int id = re->pRwCoreStream->QueueFile(
                        (int)rec->name, (int)(unsigned int)off,
                        (int)((unsigned __int64)off >> 32), (void*)&FUN_01137d60, (int)self);
                    if (re->streamerRequestId == 0)
                        re->streamerRequestId = id;
                }
            }
        }
        ri->state = 1;
        unsigned char b = (unsigned char)(self->mNextFreeRequest + 1);
        b = (b == self->mMaxRequests) ? 0 : b;
        self->mNextFreeRequest = b;
        self->mLastRequestHandleSuccessfullyProcessed = rec->f30;
        return (unsigned int)(int)(float)rec->recSize;
    }
fail:
    ri->samplesFed = 0;
    ri->state = 0;
    return (unsigned int)(int)(float)rec->recSize;
}
}}}  // namespace rw::audio::core

// @ 0x01138050
namespace rw { namespace audio { namespace core {
char* SndPlayer1::FeedChunk(char* data, int index, char flag2, char flag3)
{
    RequestInternal* ri = internal(index);
    RequestExternal* re = &mpRequestExternal[index];
    unsigned int size  = ((unsigned int)(unsigned char)data[0] << 24) |
                         ((unsigned int)(unsigned char)data[1] << 16) |
                         ((unsigned int)(unsigned char)data[2] << 8) |
                         (unsigned int)(unsigned char)data[3];
    unsigned int size2 = ((unsigned int)(unsigned char)data[4] << 24) |
                         ((unsigned int)(unsigned char)data[5] << 16) |
                         ((unsigned int)(unsigned char)data[6] << 8) |
                         (unsigned int)(unsigned char)data[7];
    unsigned char slot = re->feedSlotLatest;
    FeedDesc* fd = &mFeedDesc[slot];
    fd->feedState = 1;
    fd->chunkSamplesPlayed = 0;
    fd->requestIndex = (unsigned char)index;
    fd->pRwCoreStream = re->pRwCoreStream;
    int a3v, a4v, a5v;
    if (flag3 == 0) {
        a3v = a4v = a5v = 0;
    } else {
        fd->chunkSamplesPlayed = ri->f20;
        a5v = re->seekDataVersion;
        a4v = (int)re->pSeekData;
        a3v = ri->f20;
    }
    char r = ri->pDecoder->FUN_0114c8c0(data + 8, size2, (flag2 == 0) ? 1 : 0,
                                        a3v, (void*)a4v, a5v);
    fd->decoderRequestHandle = (unsigned char)r;
    re->numSamplesFed += (int)size2;
    return data + size;
}
}}}  // namespace rw::audio::core

// @ 0x01138130
namespace rw { namespace audio { namespace core {
void SndPlayer1::SendCommand(int cmd, void* param)
{
    System_s0113_7aa0* sys = mpSystem;
    CmdParam* pp = (CmdParam*)param;
    CmdPayload payload;
    CmdPayload* pl;
    int edx;

    if (cmd == 0) {
        payload.f00 = pp->f00;
        payload.f08 = pp->f08;
        payload.f10 = 0.0;
        payload.i18 = pp->i10;
        payload.i1c = pp->i14;
        payload.i20 = 0;
        payload.i24 = pp->i18;
        payload.f28 = pp->f1c;
        payload.f2c = pp->f20;
        pl = &payload;
        edx = 0;
        goto shared;
    }
    if (cmd == 5) {
        pl = (CmdPayload*)param;
        edx = 5;
        goto shared;
    }
    if (cmd == 1) {
        int* rec = (int*)(sys->mpCommandBuffer + sys->mCommandIndex);
        sys->mCommandIndex += 8;
        rec[1] = (int)this;
        rec[0] = (int)&FUN_01137cd0;
        return;
    }
    if (cmd == 2) {
        float f = *(float*)param;
        float r = 0.0f;
        if (f < mAttribute[0].f32 ||
            ((f == mAttribute[0].f32 ||
              (f <= mLastRequestHandleProcessed &&
               mLastRequestHandleSuccessfullyProcessed <= f &&
               f != mLastRequestHandleSuccessfullyProcessed)) &&
             mAttribute[2].f64 == 0.0))
            r = g_one;
        *(float*)((char*)param + 4) = r;
        return;
    }
    if (cmd == 3) {
        int i = 0;
        if (mMaxRequests == 0)
            return;
        float f = *(float*)param;
        int extOff = 0;
        int intOff = 0;
        for (;;) {
            RequestInternal* ri = (RequestInternal*)((char*)this + mRequestInternalOffset + intOff);
            if (ri->handle == f) {
                unsigned char st = ri->state;
                if (st != 4 && st != 0) {
                    RequestExternal* re = (RequestExternal*)((char*)mpRequestExternal + extOff);
                    unsigned char pt = re->playType;
                    if (pt == 1 || pt == 2) {
                        *(float*)((char*)param + 4) = (float)re->numBytesFed;
                        *(float*)((char*)param + 8) = 0.0f;
                        if (re->pRwCoreStream == 0) {
                            *(float*)((char*)param + 8) = g_one;
                            return;
                        }
                        int x;
                        if (ri->f18 < 0) {
                            x = re->pRwCoreStream->FUN_011e6c00(re->streamerRequestId);
                        } else if ((float)(unsigned int)i == mAttribute[0].f32) {
                            x = re->pRwCoreStream->FUN_011e6bf0();
                        } else {
                            x = re->pRwCoreStream->FUN_011e6c00(re->streamerRequestId);
                        }
                        *(float*)((char*)param + 4) += (float)x;
                        if (re->pRwCoreStream->FUN_011e6c80(re->streamerRequestId) == 3) {
                            *(float*)((char*)param + 8) = g_one;
                            return;
                        }
                        if (re->pRwCoreStream->FUN_011e6c40() != 2)
                            return;
                        *(float*)((char*)param + 8) = g_one;
                        return;
                    }
                    if (pt == 0) {
                        *(float*)((char*)param + 4) = 0.0f;
                        *(float*)((char*)param + 8) = g_one;
                        return;
                    }
                }
            }
            intOff += 0x30;
            *(float*)((char*)param + 4) = 0.0f;
            *(float*)((char*)param + 8) = 0.0f;
            i++;
            extOff += 0x50;
            if ((unsigned char)i >= mMaxRequests)
                return;
        }
    }
    if (cmd != 4)
        return;
    {
        char* rec = sys->mpCommandBuffer + sys->mCommandIndex;
        sys->mCommandIndex += 0x18;
        ((int*)rec)[1] = (int)this;
        ((int*)rec)[0] = (int)&FUN_01137a30;
        *(double*)(rec + 8) = *(double*)param;
        *(float*)(rec + 0x10) = *(float*)((char*)param + 8);
    }
    return;

shared:
    {
        float* rh = mpRequestHandle;
        *rh = *rh + g_one;
        rh = mpRequestHandle;
        if (*rh > g_reqHandleMax)
            *rh = g_one;
        rh = mpRequestHandle;
        float cur = *rh;
        pl->f2c = cur;
        if (edx == 0)
            *(float*)((char*)param + 0x20) = cur;

        char* name = (char*)pl->i18;
        unsigned int size;
        if (name == 0) {
            size = 1;
        } else {
            char* e = name;
            while (*e)
                e++;
            size = (unsigned int)(e - name) + 1;
        }
        char* ring = sys->mpCommandBuffer + sys->mCommandIndex;
        unsigned int recSize = (size + 0x3b) & ~3u;
        sys->mCommandIndex += recSize;
        PlayRec* rec = (PlayRec*)ring;
        rec->self = this;
        rec->code = (void*)&FUN_01137de0;
        rec->f30 = *mpRequestHandle;
        rec->f08 = pl->f00;
        rec->f10 = pl->f08;
        rec->f18 = pl->f10;
        rec->f24 = pl->i1c;
        rec->f28 = pl->i20;
        rec->f20 = pl->i24;
        rec->f2e = (unsigned char)_mm_cvtss_si32(_mm_load_ss(&pl->f28));
        rec->recSize = (unsigned short)recSize;
        if (size != 1) {
            char* dst = rec->name;
            for (unsigned int k = 0; k < size; k++)
                dst[k] = name[k];
        } else {
            rec->name[0] = 0;
        }
    }
}
}}}  // namespace rw::audio::core

// @ 0x011384b0
namespace rw { namespace audio { namespace core {
bool SndPlayer1::StreamNextChunk(int index, int a3, int a4)
{
    RequestInternal* ri = internal(index);
    RequestExternal* re = &mpRequestExternal[index];
    if (ri->state == 1 && re->streamerRequestId != 0 &&
        re->pRwCoreStream->FUN_011e6c80(re->streamerRequestId) == 0) {
        ri->samplesFed = 0;
        return 0;
    }
    ChunkInfo* ci = re->pRwCoreStream->GetChunk();
    if (!ci)
        return 0;
    unsigned char fslot = mNextFeedSlotToFill;
    bool fresh = (mFeedDesc[fslot].feedState == 0);
    unsigned char useSlot = (unsigned char)index;
    if (fresh) {
        useSlot = fslot;
        mNextFeedSlotToFill = (unsigned char)((fslot + 1 == 0x14) ? 0 : fslot + 1);
    }
    re->numBytesFed += ci->size;
    if (!fresh)
        return 0;
    re->feedSlotLatest = useSlot;
    mFeedDesc[useSlot].pChunkInfo = ci;
    FeedChunk(ci->pData, index, (char)a3, (char)a4);
    return 1;
}
}}}  // namespace rw::audio::core

// @ 0x01138570
namespace rw { namespace audio { namespace core {
bool SndPlayer1::HandleLoopStart(int index)
{
    RequestInternal* ri = internal(index);
    RequestExternal* re = &mpRequestExternal[index];
    if (re->playType == 0) {
        re->pLoopStartChunk = re->pNextChunk;
        unsigned char slot = mNextFeedSlotToFill;
        if (mFeedDesc[slot].feedState == 0)
            mNextFeedSlotToFill = (unsigned char)((slot + 1 == 0x14) ? 0 : slot + 1);
        else
            slot = (unsigned char)index;
        re->feedSlotLatest = slot;
        re->pNextChunk = FeedChunk(re->pNextChunk, index, 1, 0);
        return 1;
    }
    if (re->playType == 1 || ri->f18 >= re->gigaSamplesInRam) {
        if (StreamNextChunk(index, 1, 0) == 0)
            return 0;
    } else {
        re->pLoopStartChunk = re->pNextChunk;
        int slot;
        FUN_011379f0(&slot);
        re->feedSlotLatest = (unsigned char)slot;
        re->pNextChunk = FeedChunk(re->pNextChunk, index, 1, 0);
    }
    return 1;
}
}}}  // namespace rw::audio::core

// @ 0x01138640
namespace rw { namespace audio { namespace core {
bool SndPlayer1::HandleSampleEnd(int index, unsigned char* out)
{
    RequestInternal* ri = internal(index);
    RequestExternal* re = &mpRequestExternal[index];
    if (ri->f18 < 0) {
        *out = 1;
        return 1;
    }
    *out = 0;
    if (re->playType == 0) {
        if (ri->f18 == 0)
            re->pLoopStartChunk = re->pSampleData;
        unsigned char slot = mNextFeedSlotToFill;
        if (mFeedDesc[slot].feedState == 0)
            mNextFeedSlotToFill = (unsigned char)((slot + 1 == 0x14) ? 0 : slot + 1);
        else
            slot = (unsigned char)index;
        re->feedSlotLatest = slot;
        ri->samplesFed = ri->f18;
        re->pNextChunk = FeedChunk(re->pLoopStartChunk, index, 1, 0);
        return 1;
    }
    if (re->playType == 1) {
        __int64 off = (__int64)((double)re->loopStartStreamOffset + re->streamFileOffset);
        re->pRwCoreStream->QueueFile((int)re->pStreamLoopFileName, (int)(unsigned int)off,
                                     (int)((unsigned __int64)off >> 32),
                                     (void*)&FUN_01137d60, (int)this);
        ri->samplesFed = ri->f18;
        if (StreamNextChunk(index, 1, 0) == 0)
            return 0;
    } else {
        ri->samplesFed = ri->f18;
        if (ri->f18 < re->gigaSamplesInRam) {
            if (ri->f18 == 0)
                re->pLoopStartChunk = re->pSampleData;
            int slot;
            FUN_011379f0(&slot);
            re->feedSlotLatest = (unsigned char)slot;
            re->pNextChunk = FeedChunk(re->pLoopStartChunk, index, 1, 0);
        }
        if (re->gigaSamplesInRam < ri->samplesFed) {
            __int64 off = (__int64)((double)re->loopStartStreamOffset + re->streamFileOffset);
            re->pRwCoreStream->QueueFile((int)re->pStreamLoopFileName, (int)(unsigned int)off,
                                         (int)((unsigned __int64)off >> 32),
                                         (void*)&FUN_01137d60, (int)this);
            if (re->gigaSamplesInRam <= ri->f18) {
                if (StreamNextChunk(index, 1, 0) == 0)
                    return 0;
            }
        }
    }
    return 1;
}
}}}  // namespace rw::audio::core

// @ 0x011387b0
namespace rw { namespace audio { namespace core {
bool SndPlayer1::StartRequest(int index)
{
    RequestInternal* ri = internal(index);
    RequestExternal* re = &mpRequestExternal[index];
    System_s0113_7aa0* sys = mpSystem;

    sys->Lock();
    DecoderRegistry_s0113_7aa0* dr = sys->GetDecoderRegistry();
    int codecObj = dr->FUN_01133ed0(g_codecTable[re->codec]);
    Decoder* dec = dr->DecoderFactory(codecObj, ri->codec, 0x14, sys);
    ri->pDecoder = dec;
    if (!dec) {
        sys->Unlock();
        return 0;
    }
    ri->numChannels = dec->mNumChannels;
    bool flag = (ri->f24 != 0 || ri->f20 != 0 || re->playerSkip != 0);

    unsigned char pt = re->playType;
    if (pt == 0 || pt == 2) {
        unsigned char slot = mNextFeedSlotToFill;
        unsigned char useSlot = (unsigned char)flag;
        if (mFeedDesc[slot].feedState == 0) {
            useSlot = slot;
            mNextFeedSlotToFill = (unsigned char)((slot + 1 == 0x14) ? 0 : slot + 1);
        }
        re->feedSlotLatest = useSlot;
        re->pNextChunk = FeedChunk(re->pSampleData + re->seekChunkOffset, index,
                                   (char)re->seekChunkIsNewFeed, (char)flag);
    } else {
        if (StreamNextChunk(index, (int)re->seekChunkIsNewFeed, (int)flag) == 0) {
            if (ri->pDecoder) {
                ri->pDecoder->FUN_01133f40();
                ri->pDecoder = 0;
            }
            sys->Unlock();
            return 0;
        }
    }
    sys->Unlock();
    return 1;
}
}}}  // namespace rw::audio::core

// @ 0x011388f0
namespace rw { namespace audio { namespace core {
void __cdecl FUN_011388f0(SndPlayer1_s0113_88f0* self)
{
    if (A<char>(A<void*>(self, 8), 0x47) == 2)
        return;
    self->FUN_01137950();
    self->FreeFinishedRequests();
    u8 b = self->mCurrentRequest;
    u16 off = self->mRequestInternalOffset;
    RequestInternal_s0113_88f0* ri = (RequestInternal_s0113_88f0*)((char*)self + off + b * 0x30);
    char st = ri->state;
    if (st == 4 || st == 0) {
        self->mAttribute[0].f32 = self->mCurrentRequestHandle;
        self->mAttribute[2].f64 = 0.0; self->mAttribute[1].f64 = 0.0;
        return;
    }
    self->mAttribute[0].f32 = self->mCurrentRequestHandle;
    self->mAttribute[2].f64 = (double)((float)self->mCurrentRequestNumSamples / self->mCurrentRequestSampleRate);
    self->mAttribute[1].f64 = (double)((float)self->mCurrentRequestSamplesPlayed / self->mCurrentRequestSampleRate);
    while (ri->samplesFed == 0) {
        b = (u8)(b + 1); b = (b == self->mMaxRequests) ? 0 : b;
        ri = (RequestInternal_s0113_88f0*)((char*)self + off + b * 0x30);
        st = ri->state;
        if (st == 4 || st == 0) return;
    }
    for (;;) {
        for (;;) {
            if (ri->state == 4 || ri->state == 0) return;
            if (self->mFeedDesc[self->mNextFeedSlotToFill].feedState != 0) return;
            void* h = self->mpRequestExternal[b].streamHandle;
            if (h) A<float>(h, 8) = A<float>(A<void*>(self, 8), 0x38);
            if (ri->state == 1) { if (!self->StartRequest(b)) return; ri->state = 2; }
            if (ri->state == 2 && self->mFeedDesc[self->mNextFeedSlotToFill].feedState == 0) break;
            b = (u8)(b + 1); b = (b == self->mMaxRequests) ? 0 : b;
            if (b == self->mCurrentRequest) return;
            ri = (RequestInternal_s0113_88f0*)((char*)self + off + b * 0x30);
        }
        int sf = self->mpRequestExternal[b].numSamplesFed;
        if (sf == ri->f18) { if (!self->HandleLoopStart(b)) return; }
        else if (sf == ri->samplesFed) {
            u8 out = 0;
            if (!self->HandleSampleEnd(b, &out)) return;
            if (out) {
                ri->state = 3;
                b = (u8)(b + 1); b = (b == self->mMaxRequests) ? 0 : b;
                if (b == self->mCurrentRequest) return;
                ri = (RequestInternal_s0113_88f0*)((char*)self + off + b * 0x30);
            }
        } else { if (!self->StreamNextChunk(b, 0, 0)) return; }
    }
}
}}}  // namespace rw::audio::core

// @ 0x01138af0
namespace rw { namespace audio { namespace core {
bool __cdecl FUN_01138af0(SndPlayer1_s0113_88f0* self, float* pReq)
{
    if (pReq == 0) pReq = (float*)1;
    else pReq = (float*)_mm_cvtss_si32(_mm_load_ss(pReq));   /* cvtss2si: round to nearest */
    if (self) {
        *(void**)self = (void*)0x14ab718;
        /* PlugIn::Initialize<...>(self+0x40) */
        A<int>(self, 0x40) = 0;
        A<int>(self, 0x4c) = 0x13f9034;
        A<int>(self, 0x50) = 0;
        A<u8>(self, 0x54) = 3;
    }
    int a = (int)self;
    int b = (a + 0x1d7) & 0xfffffff8;
    self->mRequestInternalOffset = (u16)((((int)A<u8>(self, 0x21) * 4 + b + 7) & 0xfffffff8) - a);
    self->mDeclickBufferOffset = (u16)(b - a);
    A<int>(self, 0xc) = (int)((char*)self + 0x28);
    self->mTimerAdded = 0;
    void* buf = self->mpSystem->Alloc((int)pReq * 0x50 + 4, "SndPlayer1 RequestHandle and RequestExternal array", 0x10, 0);
    self->mpRequestHandle = (float*)buf;
    if (!buf) return false;
    self->mpRequestExternal = (RequestExternal_s0113_88f0*)((char*)buf + 4);
    self->mMaxRequests = (u8)(int)pReq;
    for (int i = 0, off = 0; i < (int)pReq; i++, off += 0x30)
        *(u8*)((char*)self + self->mRequestInternalOffset + off + 0x2a) = 0;
    self->mAttribute[2].f64 = 0.0; self->mAttribute[1].f64 = 0.0;
    self->mMaxChannels = A<u8>(self, 0x21);
    A<float>(self, 0x28) = 0.0f;
    *self->mpRequestHandle = 0.0f;
    self->mLastRequestHandleProcessed = 0.0f;
    self->mLastRequestHandleSuccessfullyProcessed = 0.0f;
    self->mCurrentRequest = 0; self->mNextRequestToFree = 0; self->mNextFreeRequest = 0;
    self->mCurrentRequestHandle = 0.0f;
    self->mCurrentRequestSampleRate = A<float>(self->mpSystem, 0xc0);
    self->mCurrentRequestSamplesPlayed = 0; self->mCurrentRequestNumSamples = 0;
    self->mNumDeclickSamples = 0; self->mDcOffsetsGathered = 0;
    self->mPreviousSampleRate = A<float>(self->mpSystem, 0xc0);
    self->mNextFeedSlotToFill = 0; self->mNextFeedSlotToFree = 0;
    for (int i = 0; i < 20; i++) { A<int>(self, 0x5c + i * 0x10) = 0; A<u8>(self, 0x5c + i * 0x10 + 0xd) = 0; }
    char ok = ((TimerMgr*)((char*)self->mpSystem + 0x60))->AddTimer(
                   (void*)((char*)self + 0x40), (void*)&FUN_011388f0, self, "SndPlayer", 1, 1);
    if (ok != 0)
        return false;
    self->mTimerAdded = 1;
    return true;
}
}}}  // namespace rw::audio::core
