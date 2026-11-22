// src/game/SPMovie/moviedecoder.cpp -- migrated from slice s00fc8450 (SPMovie/moviedecoder.obj).
// Function bodies keep the slice's code verbatim; the slice's local stubs are kept as the slice spelled them,
// which is what keeps the retail decorated names (the ctor's ICoreAllocator parameter) unchanged.
// Hand-landed: tools/migrate/rewrite.py cannot emit a compiling preamble for this slice (its EA::Thread stub
// rename rewrites the namespace prefix of qualified names); see work/migrate/report_s00fc8450_moviedecoder.md.

#include "game/types.h"

typedef unsigned int uint;

inline void* operator new(unsigned int, void* place) { return place; }   // placement new

// ---------------------------------------------------------------------------------------------
// allocator interface used by MovieDecoder (vtable +0x04 = Alloc, +0x0c = Free)
// ---------------------------------------------------------------------------------------------
struct ICoreAllocator {
    virtual void  v00();
    virtual void* Alloc(unsigned int size, const char* name, int flags, int align, void* extra); // +0x04
    virtual void  v08();
    virtual void  Free(void* ptr, int flags);                                                    // +0x0c
};

unsigned int ThreadMemSize();       // 0x00922bf0 (4)
unsigned int SemaphoreMemSize();    // 0x009227f0 (0x10)

namespace EA { namespace Thread {
struct Mutex { ~Mutex(); };                                        // 0x00922130
struct Semaphore;
struct Thread;
struct ThreadFactory { static Thread* ConstructThread(void* mem); }; // 0x00922c00
Semaphore* MakeSemaphore(void* mem);                               // 0x009228c0
} }

namespace rw { namespace movie {

// destroyed through its first vtable slot (the deleting-destructor entry point)
struct IRefCounted {
    virtual void Destroy(int flags);                                // +0x00
};

struct VideoRenderableManager {
    VideoRenderableManager(ICoreAllocator* allocator);                // 0x00fce560
};

// teardown object sitting right before the decoder constructor: allocator, one reference-counted
// object, a mutex, a scratch buffer and the renderable slot array (each slot starts at -1)
struct MovieDecoder {
    ICoreAllocator*            mAllocator;                        // +0x00
    IRefCounted*               mVideoDecoder;                     // +0x04
    EA::Thread::Mutex*         mMutex;                            // +0x08
    IRefCounted*               mSubtitleDecoder;                  // +0x0c
    void*                      mpRenderableBuffer;                // +0x10
    void*                      mVideoStreamTapHandle;             // +0x14
    void*                      mAudioStreamTapHandle;             // +0x18
    void*                      mSubtitleStreamTapHandle;          // +0x1c
    void*                      mOverlayStreamTapHandle;           // +0x20
    EA::Thread::Thread*        mVideoDecodeThread;                // +0x24
    void*                      mVideoDecodeThreadMem;             // +0x28
    EA::Thread::Semaphore*     mEmptyVideoRenderablesSemaphore;   // +0x2c
    void*                      mEmptyVideoRenderablesSemaphoreMem;// +0x30
    VideoRenderableManager*    mVideoRenderableManager;           // +0x34
    unsigned int               mNumVideoRenderables;              // +0x38
    int                        mCurFrameNumber;                   // +0x3c
    int                        mTotalFrames;                      // +0x40
    void*                      mEventLogger;                      // +0x44
    int                        mState;                            // +0x48

    MovieDecoder(ICoreAllocator* allocator);                      // 0x00fc90e0
    void SetStreamTaps(void* audio, void* subtitle);              // 0x00fc91f0
    void SetOverlayStreamTap(void* tap);                          // 0x00fc9210
};

// @ 0x00fc90e0
MovieDecoder::MovieDecoder(ICoreAllocator* allocator)
{
    mAllocator = allocator;
    mVideoDecoder = 0;
    mMutex = 0;
    mSubtitleDecoder = 0;
    mpRenderableBuffer = 0;
    mVideoStreamTapHandle = 0;
    mAudioStreamTapHandle = 0;
    mOverlayStreamTapHandle = 0;
    mVideoDecodeThreadMem = mAllocator->Alloc(ThreadMemSize(), "mVideoDecodeThreadMem", 1, 0x10, 0);
    mVideoDecodeThread = EA::Thread::ThreadFactory::ConstructThread(mVideoDecodeThreadMem);
    mEmptyVideoRenderablesSemaphoreMem =
        mAllocator->Alloc(SemaphoreMemSize(), "mEmptyVideoRenderablesSemaphoreMem", 1, 0x10, 0);
    mEmptyVideoRenderablesSemaphore = EA::Thread::MakeSemaphore(mEmptyVideoRenderablesSemaphoreMem);
    mVideoRenderableManager =
        (VideoRenderableManager*)mAllocator->Alloc(0x50, "VideoRenderableManager object", 1, 4, 0);
    mVideoRenderableManager = mVideoRenderableManager
        ? new (mVideoRenderableManager) VideoRenderableManager(mAllocator)
        : 0;
    mNumVideoRenderables = 0;
    mCurFrameNumber = 0;
    mTotalFrames = 0;
    mEventLogger = 0;
    mState = 0;
}

// @ 0x00fc91f0
void MovieDecoder::SetStreamTaps(void* audio, void* subtitle)
{
    if (mState == 0) {
        mAudioStreamTapHandle = audio;
        mSubtitleStreamTapHandle = subtitle;
    }
}

// @ 0x00fc9210
void MovieDecoder::SetOverlayStreamTap(void* tap)
{
    if (mState == 0)
        mOverlayStreamTapHandle = tap;
}

} }
