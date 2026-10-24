// Slice s00fc8450 -- rw::movie streaming helpers (Bink-style chunk writer / MovieDecoder setup).
// The BufferedWriter methods append to a fixed buffer and flush it when full (0x00fc83b0), the
// chunk validator walks {tag,len} records, and the rest is the MovieDecoder constructor plus two
// stream-tap setters and the decoder resource teardown.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.  Callees are masked relocations: declarations
// only need the right calling convention and argument sizes.
typedef unsigned int uint;

extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int size);
extern "C" void* __cdecl memset(void* dst, int value, unsigned int size);

inline void* operator new(unsigned int, void* place) { return place; }   // placement new

// the retail build's min() keeps the left operand on ties (a <= b ? a : b), which is what makes
// the clamp a short branch instead of a cmov
#define SP_MIN(a, b) ((a) <= (b) ? (a) : (b))

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

struct BufferedWriter {
    char           pad00[8];
    unsigned char* mBuffer;                     // +0x08
    int            mCapacity;                   // +0x0c
    int            mPos;                        // +0x10
    int            mBase;                       // +0x14
    int            mEnd;                        // +0x18

    void Flush();                                                     // 0x00fc83b0
    void Seek(int offset, int origin);                                // 0x00fc8450
    void Write(const void* data, int count);                          // 0x00fc84b0
    void WriteFill(unsigned char value, int count);                   // 0x00fc8500
    void Write16(unsigned short value);                               // 0x00fc8550
    void Write32(unsigned int value);                                 // 0x00fc8580
};

// {tag,len} reader accounting state
struct ChunkTracker {
    IRefCounted* mpRef;                         // +0x00  only counted once
    unsigned int mLimit;                        // +0x04
    unsigned int mTotal;                        // +0x08
};

struct VideoRenderableManager {
    VideoRenderableManager(ICoreAllocator* allocator);                // 0x00fce560
};

// teardown object sitting right before the decoder constructor: allocator, one reference-counted
// object, a mutex, a scratch buffer and the renderable slot array (each slot starts at -1)
struct RenderableStore {
    ICoreAllocator*     mAllocator;             // +0x00
    IRefCounted*        mpObject;               // +0x04
    EA::Thread::Mutex*  mMutex;                 // +0x08
    char                pad0c[4];
    void*               mpBuffer;               // +0x10
    char                pad14[8];
    unsigned int        mCount;                 // +0x1c
    int**               mpArray;                // +0x20

    void Destroy();                                                  // 0x00fc9050
};

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

// ---------------------------------------------------------------------------------------------
// buffer writer
// ---------------------------------------------------------------------------------------------
// @ 0x00fc8450
void BufferedWriter::Seek(int offset, int origin)
{
    int delta = offset;
    if (origin == 1) {
        delta = offset - mBase - mPos;
    } else if (origin == 2) {
        delta = mEnd - mBase - mPos + offset;
    }
    if (delta == 0)
        return;
    int newPos = mPos + delta;
    if (newPos > 0 && newPos < mCapacity && mBase == mEnd) {
        mPos = newPos;
        return;
    }
    Flush();
    mBase += delta;
}

// @ 0x00fc84b0
void BufferedWriter::Write(const void* data, int count)
{
    while (count > 0) {
        int n = SP_MIN(mCapacity - mPos, count);
        memcpy(mBuffer + mPos, data, n);
        mPos += n;
        if (mPos == mCapacity)
            Flush();
        count -= n;
        data = (const char*)data + n;
    }
}

// @ 0x00fc8500
void BufferedWriter::WriteFill(unsigned char value, int count)
{
    while (count > 0) {
        int n = SP_MIN(mCapacity - mPos, count);
        memset(mBuffer + mPos, value, n);
        mPos += n;
        if (mPos == mCapacity)
            Flush();
        count -= n;
    }
}

// @ 0x00fc8550
void BufferedWriter::Write16(unsigned short value)
{
    if (mCapacity - mPos < 2)
        Flush();
    *(unsigned short*)(mBuffer + mPos) = value;
    mPos += 2;
}

// @ 0x00fc8580
void BufferedWriter::Write32(unsigned int value)
{
    if (mCapacity - mPos < 4)
        Flush();
    *(unsigned int*)(mBuffer + mPos) = value;
    mPos += 4;
}

// ---------------------------------------------------------------------------------------------
// chunk validation
// ---------------------------------------------------------------------------------------------
// @ 0x00fc85b0
int ValidateChunk(const int* header, unsigned int size, unsigned int type, ChunkTracker* tracker,
                  bool (*callback)(const int*, void*), void* context, unsigned int* outLength)
{
    if (size < 8)
        return 0;
    if (callback != 0 && !callback(header, context))
        return 0;
    unsigned int length = (unsigned int)header[1];
    if (size < length)
        return 0;
    *outLength = length;
    if (tracker != 0) {
        tracker->mTotal += length;
        if (tracker->mTotal >= tracker->mLimit)
            return 2;
        if (tracker->mpRef != 0 && *header == *(const int*)tracker->mpRef)
            return 2;
    }
    return 1;
}

// @ 0x00fc8640
bool IsSCChunk(const char* data)
{
    if (data[0] == 'S' && data[1] == 'C')
        return true;
    return false;
}

// ---------------------------------------------------------------------------------------------
// decoder lifetime
// ---------------------------------------------------------------------------------------------
// @ 0x00fc9050
void RenderableStore::Destroy()
{
    if (mMutex != 0) {
        mMutex->~Mutex();
        mAllocator->Free(mMutex, 0);
        mMutex = 0;
    }
    if (mpObject != 0) {
        mpObject->Destroy(0);
        mAllocator->Free(mpObject, 0);
        mpObject = 0;
    }
    if (mpArray != 0) {
        for (unsigned int i = 0; i < mCount; i++)
            *(int*)mpArray[i] = -1;
        mAllocator->Free(mpArray, 0);
        mpArray = 0;
    }
    if (mpBuffer != 0) {
        mAllocator->Free(mpBuffer, 0);
        mpBuffer = 0;
    }
}

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
