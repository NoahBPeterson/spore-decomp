// Slice s007c13f0 — large capture routine plus a 9-argument setter block.
// /O2 /arch:SSE2 /EHsc.  See partial.txt.
#include "types.h"
#include <intrin.h>

// ---------------------------------------------------------------------------
// Allocator used by every `new ("Graphics", 0, 0, 0, 0) T` in this file.
// 0x00F473A0  operator new(size_t, const char*, int, int, int, int)
// ---------------------------------------------------------------------------
void* operator new(size_t size, const char* name, int a, int b, int c, int d);

namespace SPL {

// ---------------------------------------------------------------------------
// Small vector family.  Every vector in this file is a begin/end/capacity
// triple followed by two allocator words (0x14 bytes); the assignment
// operators live out of line and are shared per element size:
//   0x0041EBE0  element size 4      (RefVectorA / RefVectorB)
//   0x004269B0  element size 8      (SplatParams::V)
//   0x00421290  element size 0x18   (Elem24Vector)
//   0x0041E0D0  element size 0x38   (XformVector)
// ---------------------------------------------------------------------------
struct RefVectorA {
    void* mpBegin;          // +0x00
    void* mpEnd;            // +0x04
    void* mpCapacity;       // +0x08
    int   mAlloc0;          // +0x0c
    int   mAlloc1;          // +0x10
    RefVectorA& operator=(const RefVectorA& rhs);   // 0x0041EBE0
};

struct RefVectorB {
    void* mpBegin;          // +0x00
    void* mpEnd;            // +0x04
    void* mpCapacity;       // +0x08
    int   mAlloc0;          // +0x0c
    int   mAlloc1;          // +0x10
    RefVectorB& operator=(const RefVectorB& rhs);   // 0x0041EBE0
};

struct Elem24Vector {
    void* mpBegin;          // +0x00
    void* mpEnd;            // +0x04
    void* mpCapacity;       // +0x08
    int   mAlloc0;          // +0x0c
    int   mAlloc1;          // +0x10
    Elem24Vector& operator=(const Elem24Vector& rhs);   // 0x00421290
};

struct XformVector {
    void* mpBegin;          // +0x00
    void* mpEnd;            // +0x04
    void* mpCapacity;       // +0x08
    int   mAlloc0;          // +0x0c
    int   mAlloc1;          // +0x10
    XformVector& operator=(const XformVector& rhs);     // 0x0041E0D0
};

// Splat parameters: an 8-byte-element vector plus a trailing flag.
struct SplatParams {
    struct V {
        void* mpBegin;      // +0x00
        void* mpEnd;        // +0x04
        void* mpCapacity;   // +0x08
        int   mAlloc0;      // +0x0c
        int   mAlloc1;      // +0x10
        V& operator=(const V& rhs);                     // 0x004269B0
    } mVec;                 // +0x00
    bool mFlag;             // +0x14
};

// Render-target rectangle identity.
struct RectID {
    int mPageID;            // +0x00
    int mAllocID;           // +0x04
};

struct FilterChainJob {
    virtual int AddRef();   // +0x00
    virtual int Release();  // +0x04
};

// Reference-counted pointer slot (AddRef slot 0 / Release slot 1).
struct ChainRef {
    FilterChainJob* mpObject;                               // +0x00
    ChainRef& operator=(FilterChainJob* p)
    {
        if (p != mpObject) {
            FilterChainJob* const old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};

// ---------------------------------------------------------------------------
// Splat job.  Objects of this type live in cThumbnailManagerSplat at
// +0x10e4 / +0x10e8 / +0x10ec (see slice s007c1c10).
// ---------------------------------------------------------------------------
struct cSplatJob {
    virtual void j00();                                     // +0x00
    virtual void j01();
    virtual void j02();
    virtual void j03();
    virtual void* GetLayer(int a, void* info);              // +0x10
    char pad04[0x0c - 0x04];                                // +0x04
    RefVectorA  mMeshes;                                    // +0x0c
    RefVectorB  mMaterials;                                 // +0x20
    SplatParams mParams;                                    // +0x34
    Elem24Vector mElem24;                                   // +0x4c
    ChainRef    mChain;                                     // +0x60
    RectID      mRect;                                      // +0x64
    void*       mViewer;                                    // +0x6c
    void*       mField70;                                   // +0x70
    char pad74[0x7c - 0x74];                                // +0x74
    XformVector mXforms;                                    // +0x7c

    // 0x007C1B70 (thiscall, ret 0x24)
    void Init(const RefVectorA& a0, void* a1, const RefVectorB& a2, const SplatParams& a3,
              const Elem24Vector& a4, const RectID* a5, void* a6, const XformVector& a7,
              FilterChainJob* a8);
};

// @ 0x007c1b70  copy every configuration block handed in by the caller into
// the job: the two ref-vectors, the 8-byte-element parameter vector plus its
// flag, the 0x18-byte element vector, the optional filter chain (refcounted),
// the viewer, the screen-space rect (two dwords) and the transform vector.
void cSplatJob::Init(const RefVectorA& a0, void* a1, const RefVectorB& a2, const SplatParams& a3,
                     const Elem24Vector& a4, const RectID* a5, void* a6, const XformVector& a7,
                     FilterChainJob* a8)
{
    mMeshes = a0;                   // 0x0041ebe0
    mMaterials = a2;                // 0x0041ebe0
    mParams = a3;                   // 0x004269b0 (vector) + this+0x48 (flag)
    mElem24 = a4;                   // 0x00421290
    mViewer = a6;                   // this+0x6c
    mChain = a8;                    // this+0x60 (AddRef / Release)
    mField70 = a1;                  // this+0x70
    mRect = *a5;                    // this+0x64 / this+0x68
    mXforms = a7;                   // 0x0041e0d0
}

}  // namespace SPL

// ===========================================================================
// cThumbnailManager initialisation.
// Grabs the ambient model world, switches it into splat mode, subscribes the
// manager's message handler to the twelve thumbnail messages, caches the RTT
// manager, then builds the viewer set: four named splatter viewers, the two
// ambient-occlusion viewers, 0x400 shadow viewers each paired with a filter
// resource, three splat jobs, one ambient-occlusion completion handler and the
// three timeline jobs.  Finally drops the five cached timeline textures and
// runs the post-init hook.  Always returns true.
// ===========================================================================
namespace SPL {

// --- generic refcounted object whose counter lives at +0x08 ---------------
struct RefCountedInline {
    void* mpVtable;                 // +0x00
    int   mField04;                 // +0x04
    volatile long mnRefCount;       // +0x08
    void AddRef()
    {
        _InterlockedIncrement(&mnRefCount);
    }
    void Release()
    {
        _InterlockedExchangeAdd(&mnRefCount, -1L);
        if (_InterlockedExchangeAdd(&mnRefCount, 0L) < 1)
            _InterlockedIncrement(&mnRefCount);
        else
            _InterlockedExchangeAdd(&mnRefCount, 0L);
    }
};

// --- AutoRefCount for objects with virtual AddRef/Release -----------------
template<class T> struct AutoRefCount {
    T* mpObject;                                            // +0x00
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* const old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};

// --- AutoRefCount for objects with the inline counter at +0x08 ------------
template<class T> struct AutoRefCountInline {
    T* mpObject;                                            // +0x00
    AutoRefCountInline& operator=(T* p)
    {
        if (p != mpObject) {
            T* const old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};

// --- engine services ------------------------------------------------------
struct IModelWorld {
    virtual int AddRef();                                   // +0x00
    virtual int Release();                                  // +0x04
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
    virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
    virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41();
    virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45();
    virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
    virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53();
    virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57();
    virtual void v58(); virtual void v59(); virtual void v60(); virtual void v61();
    virtual void v62(); virtual void v63(); virtual void v64(); virtual void v65();
    virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69();
    virtual void v70(); virtual void v71(); virtual void v72();
    virtual void SetSplatMode(int a, int b, int c);         // +0x124
    virtual void v74(); virtual void v75(); virtual void v76();
    virtual void SetSplatFlags(int a);                      // +0x134
};

struct IModelManager {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03(); virtual void m04();
    virtual IModelWorld* CreateWorld(unsigned int name, int flags);   // +0x14
};

struct IMessageServer {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void Subscribe(void* handler, unsigned int message);       // +0x20
};

IModelManager* ModelManager();          // 0x0067DD80
IMessageServer* MessageServer();        // 0x0067DCC0
void* GetRTTManager();                  // 0x0067DDA0

// --- viewers and per-object resources ------------------------------------
struct cViewer {
    cViewer* Construct();               // 0x007C3F70
    bool Init(bool value);              // 0x007C4DD0
    void Clear(unsigned int flags) const;   // 0x007C3CC0
    char mData[0x174];                  // objects are 0x174 bytes (no vptr modelled)
};

struct cFilterRes {
    virtual int AddRef();               // +0x00
    virtual int Release();              // +0x04
    cFilterRes* Ctor();                 // 0x007B8B30
    char mData[0xd8];                   // objects are 0xdc bytes
};

struct cContentValidationSummarizer {
    virtual int AddRef();               // +0x00
    virtual int Release();              // +0x04
    cContentValidationSummarizer();     // 0x007C12A0
    char mData[0x90];                   // objects are 0x94 bytes
};

// --- refcounted message handlers built inline ----------------------------
struct IHandlerPrimary {
    virtual int AddRef();               // +0x00
    virtual int Release();              // +0x04
    virtual void h02(); virtual void h03();
};

// EA::RefCountVTemplate<int>: its own vtable plus the counter at +0x04.
struct RefCountVTemplateInt {
    virtual void Destroy(int);          // +0x00
    volatile long mnRefCount;           // +0x04
    RefCountVTemplateInt() : mnRefCount(0) {}
};

// Ambient-occlusion completion handler (0x34 bytes).
struct cAmbOccDoneHandler : IHandlerPrimary, RefCountVTemplateInt {
    int  mField0c;                      // +0x0c
    int  mField10;                      // +0x10
    int  mField14;                      // +0x14
    char pad18[0x20 - 0x18];            // +0x18
    bool mbField20;                     // +0x20
    int  mField24;                      // +0x24
    int  mField28;                      // +0x28
    int  mField2c;                      // +0x2c
    int  mField30;                      // +0x30
    cAmbOccDoneHandler()
        : mField0c(0), mField10(0), mField14(0), mbField20(false),
          mField24(0), mField28(0), mField2c(0), mField30(0) {}
};

// Timeline job (0x54 bytes).
struct cTimelineJobHandler : IHandlerPrimary, RefCountVTemplateInt {
    int  mField0c;                      // +0x0c
    int  mField10;                      // +0x10
    int  mField14;                      // +0x14
    char pad18[0x20 - 0x18];            // +0x18
    int  mField20;                      // +0x20
    int  mField24;                      // +0x24
    int  mField28;                      // +0x28
    char pad2c[0x38 - 0x2c];            // +0x2c
    int  mField38;                      // +0x38
    int  mField3c;                      // +0x3c
    bool mbField40;                     // +0x40
    char pad44[0x54 - 0x44];            // +0x44
    cTimelineJobHandler()
        : mField0c(0), mField10(0), mField14(0), mField20(0), mField24(0), mField28(0),
          mField38(-1), mField3c(-1), mbField40(false) {}
};

// --- the manager itself --------------------------------------------------
struct cThumbnailManager {
    void* mpVtable;                                     // +0x00
    char  mHandlerSink[4];                              // +0x04  (this+4 for MessageServer)
    char  pad08[0x64 - 0x08];                           // +0x08
    AutoRefCountInline<RefCountedInline> mTimelineCellBg;    // +0x64
    AutoRefCountInline<RefCountedInline> mTimelineCreatureBg;  // +0x68
    AutoRefCountInline<RefCountedInline> mTimelineTribeBg;      // +0x6c
    AutoRefCountInline<RefCountedInline> mTimelineCivBg;        // +0x70
    AutoRefCountInline<RefCountedInline> mTimelineSpaceBg;      // +0x74
    cViewer* mSplatterViewer;                           // +0x78
    cViewer* mBakeInfoSplatterViewer;                   // +0x7c
    cViewer* mNMapSpecSplatterViewer;                   // +0x80
    cViewer* mDilateViewer;                             // +0x84
    cViewer* mAmbOccShadowViewers[0x400];               // +0x88
    cViewer* mAmbOccSplatterViewer;                     // +0x1088
    cViewer* mAmbOccGatherViewer;                       // +0x108c
    char  pad1090[0x109c - 0x1090];                     // +0x1090
    void* mWatermarkRaster;                             // +0x109c
    void* mScreenshotRaster;                            // +0x10a0
    char  pad10a4[0x10b4 - 0x10a4];                     // +0x10a4
    void* mRTTMgr;                                      // +0x10b4
    char  pad10b8[0x10c4 - 0x10b8];                     // +0x10b8
    AutoRefCount<IModelWorld> mAOModelWorld;            // +0x10c4
    char  pad10c8[0x10e4 - 0x10c8];                     // +0x10c8
    AutoRefCount<cContentValidationSummarizer> mDiffuseSplatterJob;    // +0x10e4
    AutoRefCount<cContentValidationSummarizer> mBakeInfoSplatterJob;   // +0x10e8
    AutoRefCount<cContentValidationSummarizer> mNMapSpecSplatterJob;   // +0x10ec
    char  pad10f0[0x10fc - 0x10f0];                     // +0x10f0
    AutoRefCount<cAmbOccDoneHandler> mAODoneHandler;    // +0x10fc
    AutoRefCount<cFilterRes> mAmbOccRenderJobs[0x400];  // +0x1100
    AutoRefCount<cTimelineJobHandler> mTimelineJobs[3]; // +0x2100

    void Finalize();                                    // 0x007B9B00
    bool Initialize();                                  // 0x007C13F0
};

inline cViewer* NewViewer()
{
    void* const mem = ::operator new(sizeof(cViewer), "Graphics", 0, 0, 0, 0);
    return mem ? static_cast<cViewer*>(mem)->Construct() : 0;
}

inline cFilterRes* NewFilterRes()
{
    void* const mem = ::operator new(sizeof(cFilterRes), "Graphics", 0, 0, 0, 0);
    return mem ? static_cast<cFilterRes*>(mem)->Ctor() : 0;
}

// @ 0x007c13f0
bool cThumbnailManager::Initialize()
{
    mAOModelWorld = ModelManager()->CreateWorld(0x247d6ad, 0);
    mAOModelWorld.mpObject->SetSplatMode(1, 0, 0);
    mAOModelWorld.mpObject->SetSplatFlags(1);

    IMessageServer* const server = MessageServer();
    if (server) {
        server->Subscribe(mHandlerSink, 0x1c913db);
        server->Subscribe(mHandlerSink, 0x1c91270);
        server->Subscribe(mHandlerSink, 0x212c1ee);
        server->Subscribe(mHandlerSink, 0x21d7528);
        server->Subscribe(mHandlerSink, 0x31e09b4);
        server->Subscribe(mHandlerSink, 0x21d752f);
        server->Subscribe(mHandlerSink, 0x50b834d);
        server->Subscribe(mHandlerSink, 0x5221305);
        server->Subscribe(mHandlerSink, 0x5fadac4);
        server->Subscribe(mHandlerSink, 0x5fc2c38);
        server->Subscribe(mHandlerSink, 0x7b240a0);
        server->Subscribe(mHandlerSink, 0x238de9c);
    }

    mRTTMgr = GetRTTManager();

    mSplatterViewer = NewViewer();
    mSplatterViewer->Init(false);
    mSplatterViewer->Clear(0);

    mBakeInfoSplatterViewer = NewViewer();
    mBakeInfoSplatterViewer->Init(false);
    mBakeInfoSplatterViewer->Clear(0);

    mNMapSpecSplatterViewer = NewViewer();
    mNMapSpecSplatterViewer->Init(false);
    mNMapSpecSplatterViewer->Clear(0);

    mDilateViewer = NewViewer();
    mDilateViewer->Init(false);
    mDilateViewer->Clear(0);

    mAmbOccSplatterViewer = NewViewer();
    mAmbOccSplatterViewer->Init(false);
    mAmbOccSplatterViewer->Clear(0);

    mAmbOccGatherViewer = NewViewer();
    mAmbOccGatherViewer->Init(false);
    mAmbOccGatherViewer->Clear(0);

    for (int i = 0; i < 0x400; ++i) {
        mAmbOccShadowViewers[i] = NewViewer();
        mAmbOccShadowViewers[i]->Init(false);
        mAmbOccRenderJobs[i] = NewFilterRes();
    }

    mDiffuseSplatterJob = new ("Graphics", 0, 0, 0, 0) cContentValidationSummarizer();
    mBakeInfoSplatterJob = new ("Graphics", 0, 0, 0, 0) cContentValidationSummarizer();
    mNMapSpecSplatterJob = new ("Graphics", 0, 0, 0, 0) cContentValidationSummarizer();

    mAODoneHandler = new ("Graphics", 0, 0, 0, 0) cAmbOccDoneHandler();

    mScreenshotRaster = 0;
    mWatermarkRaster = 0;

    mTimelineCellBg = 0;
    mTimelineCreatureBg = 0;
    mTimelineTribeBg = 0;
    mTimelineCivBg = 0;
    mTimelineSpaceBg = 0;

    for (int i = 0; i < 3; ++i)
        mTimelineJobs[i] = new ("Graphics", 0, 0, 0, 0) cTimelineJobHandler();

    Finalize();
    return true;
}

}  // namespace SPL
