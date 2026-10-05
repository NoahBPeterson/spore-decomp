// Slice s007bced0 — SP::cThumbnailManager thumbnail-job Shutdown methods and
// two large setup/teardown routines.  Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2.
// The small Shutdown methods use the EA::AutoRefCount / RefCountTemplate /
// EA::Thread::AtomicInt idioms, reproduced from the matched sources.
#include "types.h"
#include <intrin.h>
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)

// ---------------------------------------------------------------------------
// EA reference-count primitives
// ---------------------------------------------------------------------------
namespace EA {
    namespace Thread {
        struct AtomicInt {
            volatile long mValue;
            long GetValue() const { return _InterlockedExchangeAdd((long*)&mValue, 0); }
            long Increment() { return _InterlockedIncrement((long*)&mValue); }
            long Decrement() { return _InterlockedDecrement((long*)&mValue); }
        };
    }

    template <typename T> struct RefCountTemplate {
        virtual ~RefCountTemplate() {}
        virtual int AddRef() { return mRefCount++ + 1; }
        virtual int Release() { int n = mRefCount - 1; mRefCount = n; if (n == 0) { mRefCount = 1; delete this; } return n; }
        T mRefCount;
    };

    template <typename T> struct AutoRefCount {
        T* mpObject;
        AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
        ~AutoRefCount() { if (mpObject) mpObject->Release(); }
        T* operator->() const { return mpObject; }
        operator T*() const { return mpObject; }
        AutoRefCount& operator=(T* pObject) {
            if (pObject != mpObject) {
                T* const pTemp = mpObject;
                if (pObject) pObject->AddRef();
                mpObject = pObject;
                if (pTemp) pTemp->Release();
            }
            return *this;
        }
    };
}

void __cdecl EASTL_deallocate(void* p);           // 0x00f47380

// ---------------------------------------------------------------------------
// interface hierarchy
// ---------------------------------------------------------------------------
struct cFilterChainJob {
    virtual int AddRef();                          // +0x00
    virtual void Release();                        // +0x04
    void Shutdown();
};

struct cTextureInstance {                          // refcount at +8, non-virtual
    void* mRaster;                                 // +0x00
    unsigned char mFlags;                          // +0x04
    char pad[3];
    EA::Thread::AtomicInt mRefCount;               // +0x08
    void AddRef() { mRefCount.Increment(); }
    void Release() {
        mRefCount.Decrement();
        if (mRefCount.GetValue() < 1)
            mRefCount.Increment();
        else
            mRefCount.GetValue();
    }
};

struct cViewer {
    void FUN_007c3ba0();                           // 0x007c3ba0
    void FUN_007c4000();                           // 0x007c4000
};

// ---------------------------------------------------------------------------
// job info payloads (layouts from the dev PDB)
// ---------------------------------------------------------------------------
struct cPaletteJobInfo : EA::RefCountTemplate<int> {
    int mRectId0;                                  // +0x08
    int mRectId1;                                  // +0x0c
    EA::AutoRefCount<cFilterChainJob> mPostProcessLayer;   // +0x10
    unsigned mCameraId;                            // +0x14
    unsigned mWidth;                               // +0x18
    unsigned mHeight;                              // +0x1c
    unsigned mInstance;                            // +0x20
    unsigned mGroup;                               // +0x24
    bool mUseImageSpaceFraming;                    // +0x28
    void Shutdown();
};

struct cEditorJobInfo : EA::RefCountTemplate<int> {
    int mRectId0;                                  // +0x08
    int mRectId1;                                  // +0x0c
    EA::AutoRefCount<cFilterChainJob> mPostProcessLayer;   // +0x10
    unsigned mWidth;                               // +0x14
    unsigned mHeight;                              // +0x18
    EA::AutoRefCount<cTextureInstance> mThumbnailTex;      // +0x1c
    void Shutdown();
};

struct cCSAJobInfo : EA::RefCountTemplate<int> {
    char pad[0x40 - 0x08];
    EA::AutoRefCount<cFilterChainJob> mPostProcessLayer;   // +0x40
    void Shutdown();
};

struct cGameThumbJobInfo : EA::RefCountTemplate<int> {
    unsigned mRes;                                 // +0x08
    unsigned mGroup;                               // +0x0c
    unsigned mInstance;                            // +0x10
    int mRectId0;                                  // +0x14
    int mRectId1;                                  // +0x18
    unsigned mWidth;                               // +0x1c
    unsigned mHeight;                              // +0x20
    EA::AutoRefCount<cFilterChainJob> mPostProcessLayer;   // +0x24
    void Shutdown();
};

// ---------------------------------------------------------------------------
// thumbnail-job objects (members in address order)
// ---------------------------------------------------------------------------
struct cPaletteThumbnailJob {
    char pad0[0xc];
    bool mInitialized;                             // +0x0c
    void* mModelWorld;                             // +0x10
    cViewer* mViewer;                              // +0x14
    int mBounds[2];                                // +0x18
    unsigned mTextureSize;                         // +0x20
    int mBoundsTextureWidth;                       // +0x24
    int mBoundsTextureHeight;                      // +0x28
    unsigned char* mTempPixelData;                 // +0x2c
    EA::AutoRefCount<cPaletteJobInfo> mInfo;       // +0x30
    void Shutdown();
};

struct cEditorThumbnailJob {
    char pad0[0xc];
    bool mInitialized;                             // +0x0c
    void* mModelWorld;                             // +0x10
    cViewer* mViewer;                              // +0x14
    int mBounds[2];                                // +0x18
    unsigned mTextureSize;                         // +0x20
    int mBoundsTextureWidth;                       // +0x24
    int mBoundsTextureHeight;                      // +0x28
    unsigned char* mTempPixelData;                 // +0x2c
    EA::AutoRefCount<cEditorJobInfo> mInfo;        // +0x30
    void Shutdown();
};

struct cCSAThumbnailJob {
    char pad0[0xc];
    bool mInitialized;                             // +0x0c
    void* mModelWorld;                             // +0x10
    void* mBackgroundModelWorld;                   // +0x14
    cViewer* mViewer;                              // +0x18
    cViewer* mFilterViewer;                        // +0x1c
    EA::AutoRefCount<cCSAJobInfo> mInfo;           // +0x20
    void Shutdown();
};

struct cGameThumbnailJob {
    char pad0[0xc];
    bool mInitialized;                             // +0x0c
    void* mModelWorld;                             // +0x10
    cViewer* mViewer;                              // +0x14
    EA::AutoRefCount<cGameThumbJobInfo> mInfo;     // +0x18
    void Shutdown();
};

struct Obj90 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

// ---------------------------------------------------------------------------
// @ 0x007bd4c0  SP::cThumbnailManager::DilateWithoutAODone(this, void* msg)
// ---------------------------------------------------------------------------
struct MessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void Send(int a, int b, int c, int d);            // +0x18
};
MessageServer* __cdecl SP_MessageServer();          // 0x0067dcc0

struct DilateMsg {
    char pad[8];
    int m8;                                        // +0x08
    int mc;                                        // +0x0c
    cFilterChainJob* mJob;                         // +0x10
};

struct cThumbnailManager {
    char pad[0x10d0];
    bool mCurrentlyCapturingAO;                    // +0x10d0

    void DilateWithoutAODone(DilateMsg* msg);
};
void cThumbnailManager::DilateWithoutAODone(DilateMsg* msg)
{
    int u = msg->m8;
    msg->mJob->Shutdown();
    mCurrentlyCapturingAO = false;
    SP_MessageServer()->Send(u, 0, 0, 0);
}

// ---------------------------------------------------------------------------
// @ 0x007bd500  cPaletteJobInfo::Shutdown(void* pInfo)   (ret 4)
// ---------------------------------------------------------------------------
void __stdcall PaletteJobInfo_Shutdown(cPaletteJobInfo* pInfo)
{
    cFilterChainJob* pcVar1 = pInfo->mPostProcessLayer.mpObject;
    int uVar2 = pInfo->mRectId0;
    pcVar1->Shutdown();
    pcVar1->Release();
    SP_MessageServer()->Send(uVar2, 0, 0, 0);
}

// ---------------------------------------------------------------------------
// @ 0x007bd540  cPaletteThumbnailJob::Shutdown
// ---------------------------------------------------------------------------
void cPaletteThumbnailJob::Shutdown()
{
    if (mInitialized) {
        if (mTempPixelData != 0 && mInfo.mpObject->mUseImageSpaceFraming) {
            EASTL_deallocate(mTempPixelData);
            mTempPixelData = 0;
        }
        cPaletteJobInfo* pcVar1 = mInfo.mpObject;
        if (pcVar1 != 0) {
            if (pcVar1->mPostProcessLayer.mpObject != 0) {
                pcVar1->mPostProcessLayer.mpObject->Shutdown();
                pcVar1->mPostProcessLayer = 0;
            }
            mInfo = 0;
        }
        if (mViewer != 0) {
            mViewer->FUN_007c3ba0();
            cViewer* pcVar3 = mViewer;
            if (pcVar3 != 0) {
                pcVar3->FUN_007c4000();
                EASTL_deallocate(pcVar3);
            }
            mViewer = 0;
        }
        mInitialized = false;
    }
}

// ---------------------------------------------------------------------------
// @ 0x007bd5d0  cEditorJobInfo::Shutdown
// ---------------------------------------------------------------------------
void cEditorJobInfo::Shutdown()
{
    if (mPostProcessLayer.mpObject != 0) {
        mPostProcessLayer.mpObject->Shutdown();
        mPostProcessLayer = 0;
    }
    if (mThumbnailTex.mpObject != 0) {
        mThumbnailTex = 0;
    }
}

// ---------------------------------------------------------------------------
// @ 0x007bd640  cEditorThumbnailJob::Shutdown
// ---------------------------------------------------------------------------
void cEditorThumbnailJob::Shutdown()
{
    if (mInitialized) {
        if (mTempPixelData != 0) {
            EASTL_deallocate(mTempPixelData);
            mTempPixelData = 0;
        }
        if (mInfo.mpObject != 0) {
            mInfo.mpObject->Shutdown();
            mInfo = 0;
        }
        if (mViewer != 0) {
            mViewer->FUN_007c3ba0();
            cViewer* pcVar2 = mViewer;
            if (pcVar2 != 0) {
                pcVar2->FUN_007c4000();
                EASTL_deallocate(pcVar2);
            }
            mViewer = 0;
        }
        mInitialized = false;
    }
}

// ---------------------------------------------------------------------------
// @ 0x007bd6b0  cCSAThumbnailJob::Shutdown
// ---------------------------------------------------------------------------
void cCSAThumbnailJob::Shutdown()
{
    if (mInitialized) {
        cCSAJobInfo* pcVar1 = mInfo.mpObject;
        if (pcVar1 != 0) {
            if (pcVar1->mPostProcessLayer.mpObject != 0) {
                pcVar1->mPostProcessLayer.mpObject->Shutdown();
                pcVar1->mPostProcessLayer = 0;
            }
            mInfo = 0;
        }
        if (mViewer != 0) {
            mViewer->FUN_007c3ba0();
            cViewer* pcVar3 = mViewer;
            if (pcVar3 != 0) {
                pcVar3->FUN_007c4000();
                EASTL_deallocate(pcVar3);
            }
            mViewer = 0;
        }
        if (mFilterViewer != 0) {
            mFilterViewer->FUN_007c3ba0();
            cViewer* pcVar3 = mFilterViewer;
            if (pcVar3 != 0) {
                pcVar3->FUN_007c4000();
                EASTL_deallocate(pcVar3);
            }
            mFilterViewer = 0;
        }
        mInitialized = false;
    }
}

// ---------------------------------------------------------------------------
// @ 0x007bdd70  cGameThumbnailJob::Shutdown
// ---------------------------------------------------------------------------
void cGameThumbnailJob::Shutdown()
{
    if (mInitialized) {
        cGameThumbJobInfo* pcVar1 = mInfo.mpObject;
        if (pcVar1 != 0) {
            if (pcVar1->mPostProcessLayer.mpObject != 0) {
                pcVar1->mPostProcessLayer.mpObject->Shutdown();
                pcVar1->mPostProcessLayer = 0;
            }
            mInfo = 0;
        }
        if (mViewer != 0) {
            mViewer->FUN_007c3ba0();
            cViewer* pcVar3 = mViewer;
            if (pcVar3 != 0) {
                pcVar3->FUN_007c4000();
                EASTL_deallocate(pcVar3);
            }
            mViewer = 0;
        }
        mInitialized = false;
    }
}

// ---------------------------------------------------------------------------
// @ 0x007bdde0  (thiscall-like: object in ecx)
// ---------------------------------------------------------------------------
void __fastcall FUN_007bdde0(void* p)
{
    if (*(char*)((char*)p + 0x78) != 0) {
        if (*(void**)((char*)p + 0x60) != 0)
            (*(cFilterChainJob**)((char*)p + 0x60))->Shutdown();
        Obj90* q = *(Obj90**)((char*)p + 0x90);
        if (q != 0) {
            *(void**)((char*)p + 0x90) = 0;
            q->v2();
        }
        *(char*)((char*)p + 0x78) = 0;
    }
}

// ---------------------------------------------------------------------------
// @ 0x007bced0  (giant setup; skeleton)
// ---------------------------------------------------------------------------
void __cdecl FUN_007bced0(void* p) { (void)p; }

// ---------------------------------------------------------------------------
// @ 0x007bd750  (giant setup; skeleton)
// ---------------------------------------------------------------------------
void __cdecl FUN_007bd750(void* p) { (void)p; }
