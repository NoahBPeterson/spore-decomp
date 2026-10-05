// Slice s0076bc50 (batch w2g3, slice 37).
// SP::cRTTCapture: render-to-texture capture manager used by the editor/effects code.
// The three large methods are inlined-heavy /O2 code (message handling, snapshot setup);
// only the constructor/destructor are fully modelled here. Default flags region.
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);   // 0x00f47380
static inline void Deallocate(void* p) { EASTL_allocator_deallocate(p); }

// ------------------------------------------------------------------ small stubs
struct cRenderTargetRectID { int mPageID; int mAllocID; };

// Refcounted interface (vtable + int refcount at +4).
struct RefCountV { virtual ~RefCountV(); int mRefCount; };
// Message handler interface at +8 (deleting dtor, HandleMessage, AddRef, Release).
struct IHandlerRC {
    virtual ~IHandlerRC();
    virtual bool HandleMessage(int msgId, void* payload);
    virtual int  AddRef();
    virtual int  Release();
};

// An eastl vector whose end/capacity pointers carry a low tag bit (sp_vector_allocator).
struct SpVec {
    void* mBegin;
    void* mEnd;
    void* mCapacity;
};

struct OwnedRefObj {
    virtual ~OwnedRefObj();
    virtual void Release();
};

// ------------------------------------------------------------------ cRTTCapture
struct cRTTCapture : RefCountV, IHandlerRC {
    cRenderTargetRectID mCubemapFaceRectID;   // +0xc
    char                pad14[0x68 - 0x14];
    bool                mJobInProgress;        // +0x68
    char                pad69[0x6c - 0x69];
    void*               mRTTMgr;              // +0x6c
    void*               mGraphicsSystem;      // +0x70
    cRenderTargetRectID mTempSnapRectID;      // +0x74
    void*               mTempSnapRaster;      // +0x7c
    void*               mTempSnapZRaster;     // +0x80
    SpVec               mSceneViewJobs;       // +0x84 (sp_vector alloc = 4 dwords)
    void*               mOwnedBlock;          // +0x88 heap block with a 4-byte header
    void*               mField8c;             // +0x8c
    void*               mField90;             // +0x90
    OwnedRefObj*        mField9c;             // +0x9c
    SpVec               mFieldA0;             // +0xa0
    bool                mFieldB0;             // +0xb0
    char                padb1[3];

    cRTTCapture();
    ~cRTTCapture();

    // @ 0x0076bc50  Snapshot/cubemap capture job (7 args, mixed inlined EASTL setup).
    bool TakeSnapshot(void* a, void* b, unsigned res, char cube, unsigned char flags, void* p7, char genSH);
    // @ 0x0076c210  Message-driven capture entry (1 arg).
    bool HandleCaptureMessage(void* payload);
    // @ 0x0076c7c0  IHandlerRC::HandleMessage.
    bool HandleMessage(int msgId, void* payload);
};

extern char gEmptySpVec;   // 0x01667bac shared empty buffer

cRTTCapture::cRTTCapture()
    : mCubemapFaceRectID(), mJobInProgress(false),
      mRTTMgr(0), mGraphicsSystem(0),
      mTempSnapRectID(), mTempSnapRaster(0), mTempSnapZRaster(0),
      mOwnedBlock(0), mField8c(0), mField90(0), mField9c(0), mFieldB0(true)
{
    mCubemapFaceRectID.mPageID = -1;
    mCubemapFaceRectID.mAllocID = -1;
    mTempSnapRectID.mPageID = -1;
    mTempSnapRectID.mAllocID = -1;
    mSceneViewJobs.mBegin = 0;
    mSceneViewJobs.mEnd = 0;
    mSceneViewJobs.mCapacity = 0;
    mFieldA0.mBegin = &gEmptySpVec;
    mFieldA0.mEnd = &gEmptySpVec;
    mFieldA0.mCapacity = &gEmptySpVec + 1;
}

cRTTCapture::~cRTTCapture()
{
    // mFieldA0 (three-pointer string/vector with a shared empty sentinel)
    {
        int n = (int)((char*)mFieldA0.mCapacity - (char*)mFieldA0.mBegin);
        if (n > 1 && mFieldA0.mBegin != 0)
            Deallocate(mFieldA0.mBegin);
    }
    if (mField9c)
        mField9c->Release();
    if (mOwnedBlock && *(int*)((char*)mOwnedBlock - 4) != 0)
        Deallocate(mOwnedBlock);
    if (mTempSnapZRaster)
        ((OwnedRefObj*)mTempSnapZRaster)->Release();
}

// @ 0x0076bc50
bool cRTTCapture::TakeSnapshot(void* a, void* b, unsigned res, char cube,
                               unsigned char flags, void* p7, char genSH)
{
    // Full body omitted: allocates a temporary cViewer (0x140 bytes) and a scene-view job,
    // queries the RTT manager page layout, computes the tiled resolution and dispatches the
    // job. Kept as a skeleton (see partial.txt).
    (void)a; (void)b; (void)res; (void)cube; (void)flags; (void)p7; (void)genSH;
    return false;
}

// @ 0x0076c210
bool cRTTCapture::HandleCaptureMessage(void* payload)
{
    // Full body omitted: same family as TakeSnapshot, driven from a queued message.
    (void)payload;
    return false;
}

// @ 0x0076c7c0
bool cRTTCapture::HandleMessage(int msgId, void* payload)
{
    // Full body omitted: switch over capture message ids (0x1c7f3db / 0x1c7f90a / 0x1c91267)
    // that drives the cubemap/snapshot jobs. Skeleton only (see partial.txt).
    (void)msgId; (void)payload;
    return false;
}
