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
struct cJobPostFilter;
struct DrawCtx;
struct RectID { int mPageID; int mAllocID; };
struct Vec4 {
    float x, y, z, w;
    Vec4() {}
    Vec4(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
};

// The filter chain job (retail layout 0x34 bytes): two vptrs (primary AddRef/Release, secondary
// RefCountVTemplate at +4 with the count at +8), a filter list at +0xc, an init flag at +0x20.
struct cChainBaseA { virtual int AddRef(); virtual int Release(); };
struct cChainBaseB {
    virtual void b0();
    virtual void b1();
    int mRefCount;
    cChainBaseB() { mRefCount = 0; }
};
struct cFilterChainJob : cChainBaseA, cChainBaseB {
    cJobPostFilter** mFilterBegin;                 // +0x0c  mFilters (eastl::vector<AutoRefCount<cJobPostFilter>>)
    cJobPostFilter** mFilterEnd;                   // +0x10
    cJobPostFilter** mFilterCapacity;              // +0x14
    int m18, m1c;
    unsigned char mInitialized;                    // +0x20
    int m24, m28, m2c, m30;
    cFilterChainJob() {
        mFilterBegin = 0; mFilterEnd = 0; mFilterCapacity = 0;
        mInitialized = 0;
        m24 = 0; m28 = 0; m2c = 0; m30 = 0;
    }
    void AddFilter(cJobPostFilter* pFilter);       // 0x007b9750
    void DrawLayer(int a0, int layer, DrawCtx* ctx, int a3);   // 0x007b49f0
    void Shutdown();                               // 0x007b96d0
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

struct DrawCtx;
struct cViewer {
    void FUN_007c3ba0();                           // 0x007c3ba0
    void FUN_007c4000();                           // 0x007c4000
    void Copy(const cViewer* src, int a, int b);   // 0x007c50b0 (SP::cViewer::Copy)
    void SetClearColor(const Vec4& c);            // 0x007c3c20
    void Flush(int mode);                          // 0x007c3c50
    void SetRaster(const RectID* r, int a);        // 0x007c4be0
    void FUN_007c40c0(float* a, float* b);         // 0x007c40c0 (reads two view extents)
    void FUN_007c4b00(float a, float b);           // 0x007c4b00 (writes the two view extents)
    void FUN_007c4ad0(float a, float b);           // 0x007c4ad0 (view offset)
    void SetViewportRect(int x, int y, int w, int h);   // 0x007c5310
};
struct DrawCtx {                                   // argument 3 of DrawLayer
    cViewer* viewer;
    int a, b, c;
};
struct ILayerDraw {                                // world->GetLayerDraw()
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void Draw(int a0, int layer, DrawCtx* ctx, int a3);   // +0xc
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
    RectID mLargeRectId;                           // +0x08
    RectID mSmallRectId;                           // +0x10
    RectID mAntiAliasRectId;                       // +0x18
    unsigned mResLarge;                            // +0x20
    unsigned mResSmall;                            // +0x24
    char pad28[0x40 - 0x28];
    EA::AutoRefCount<cFilterChainJob> mPostProcessLayer;   // +0x40
    char pad44[0x54 - 0x44];
    ILayerDraw* mExtraLayer;                       // +0x54
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

struct IModelWorld {
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
    virtual void s57();
    virtual void s58();
    virtual void s59();
    virtual void s60();
    virtual void s61();
    virtual void s62();
    virtual void s63();
    virtual void s64();
    virtual void s65();
    virtual void s66();
    virtual void s67();
    virtual void s68();
    virtual void s69();
    virtual void s70();
    virtual void s71();
    virtual void s72();
    virtual void s73();
    virtual void s74();
    virtual void s75();
    virtual void s76();
    virtual void s77();
    virtual void s78();
    virtual ILayerDraw* GetLayerDraw();            // +0x13c
};

struct cCSAThumbnailJob {
    char pad0[0xc];
    bool mInitialized;                             // +0x0c
    IModelWorld* mModelWorld;                      // +0x10
    IModelWorld* mBackgroundModelWorld;            // +0x14
    cViewer* mViewer;                              // +0x18
    cViewer* mFilterViewer;                        // +0x1c
    EA::AutoRefCount<cCSAJobInfo> mInfo;           // +0x20
    void Shutdown();
    void DrawLayer(int a0, int layer, DrawCtx* ctx, int a3);          // 0x007bd750
    void FUN_007b3090();                                              // 0x007b3090
    void RenderLargeTiledImage(int a0, int layer, DrawCtx* ctx, int a3);   // 0x007b8cb0
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
    void DilateWithoutAOStart(struct DilateReq* req);                // 0x007bced0
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
// Singletons and post-filter support shared by the two big routines below
// (retail cJobPostFilter is 0xe4 bytes; the 2008 PDB's is 0xa8)
// ---------------------------------------------------------------------------
void* operator new(unsigned int size, const char* group, int a, int b, int c, int d);   // 0x00f473a0
void operator delete(void* p);                                                         // 0x00f47380

struct cPropertyList {
    bool GetDescription(unsigned id);                          // 0x006a25a0
};
extern cPropertyList* sAppProperties;                          // 0x015fd918

struct IMgr {                                                  // 0x0067dd50
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06();
    virtual int* GetScreenSize();                              // +0x1c: {width, height}
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void DrawTarget(int a3, int w, int h, DrawCtx* c, int one, int zero);   // +0x40
    virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29();
    virtual void Post(void* sender, int a, void* msg);         // +0x78
};
IMgr* __cdecl GetMgr();                                        // 0x0067dd50

struct IRtt {                                                  // 0x0067dd40
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42();
    virtual void GetRectAC(RectID* out);                       // +0xac
    virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48();
    virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); virtual void s55();
    virtual void GetRectE0(RectID* out, int index);            // +0xe0
};
IRtt* __cdecl GetRtt();                                        // 0x0067dd40

struct cJobPostFilter {
    virtual int AddRef();                          // +0x00
    virtual int Release();                         // +0x04
    virtual void v2();
    virtual void Draw(int a0, int layer, DrawCtx* ctx, int a3);   // +0x0c
    unsigned mRefCountV[2];                        // +0x04 RefCountVTemplate
    unsigned mMaterialId;                          // +0x0c
    RectID mSrcRectID;                             // +0x10
    unsigned mSrcRaster;                           // +0x18
    RectID mDestRectID;                            // +0x1c
    struct RectVec {                               // eastl::vector<cRenderTargetRectID>, +0x24
        RectID* mpBegin;
        RectID* mpEnd;
        RectID* mpCapacity;
        void DoInsertValue(RectID* position, const RectID& value);   // 0x006ec390
        void push_back(const RectID& v) {
            RectID* p = mpEnd;
            if (p < mpCapacity) {
                mpEnd = p + 1;
                if (p) *p = v;
            } else {
                DoInsertValue(p, v);
            }
        }
        static RectID* copy(RectID* first, RectID* last, RectID* result) {
            for (; first != last; ++first, ++result)
                *result = *first;
            return result;
        }
        void erase(RectID* first, RectID* last) {
            if (first != last) {
                RectID* itEnd = copy(last, mpEnd, first);
                (void)itEnd;
                mpEnd -= (last - first);
            }
        }
        RectID* begin() { return mpBegin; }
        RectID* end() { return mpEnd; }
        void clear() { erase(begin(), end()); }
    } mAdditionalRectIDs;
    unsigned pad30[2];                             // +0x30
    cViewer* mViewer;                              // +0x38
    Vec4 mCustomParams[4];                         // +0x3c
    unsigned pad7c[1];
    bool mInitialized;                             // +0x80
    bool mDumpTexture;                             // +0x81
    bool mClearBeforeDraw;                         // +0x82
    bool mOverrideViewport;                        // +0x83
    int mView[4];                                  // +0x84
    int mQuadrant;                                 // +0x94
    Vec4 mClearColor;                              // +0x98
    bool mPreSetViewport;                          // +0xa8
    char padA9[0xe4 - 0xa9];

    cJobPostFilter();                              // 0x007b8550
    void Initialize(int flags);                    // 0x007b9420
    void InitBlur(int taps, const RectID& src, const RectID& dest, int flags);   // 0x007b9510
    void SetClearColor(Vec4 c) { mClearColor = c; mClearBeforeDraw = true; }     // 0x007b27a0
    void Shutdown()
    {
        if (mInitialized) {
            if (mViewer) {
                mViewer->FUN_007c3ba0();
                cViewer* v = mViewer;
                if (v) {
                    v->FUN_007c4000();
                    operator delete(v);
                }
                mViewer = 0;
            }
            if (mSrcRaster)
                mSrcRaster = 0;
            mAdditionalRectIDs.clear();
            mInitialized = false;
        }
    }
};

// ---------------------------------------------------------------------------
// behavior message posted when a dilate job is queued (layouts from s007bbf80)
// ---------------------------------------------------------------------------
struct BehaviorMessageBase {
    virtual void d0();
    virtual int AddRef();
    virtual int Release();
    volatile long mRef;
    BehaviorMessageBase() { mRef = 0; }
};
struct BehaviorMessage : BehaviorMessageBase {
    unsigned f08;
    unsigned pad0c;
    unsigned f10;
    unsigned pad14;
    unsigned f18;
    unsigned f1c;
    BehaviorMessage() { f18 = 0; }
};
struct PostMsg {
    int kind;
    int a;
    unsigned char b;
    int c, d;
    unsigned id;
    BehaviorMessage* data;
    int e, f, g, h;
    PostMsg(BehaviorMessage* bm) {
        a = 0; b = 0; c = 0; d = 0;
        e = 0; f = 0; g = 0; h = 0;
        kind = 1;
        data = bm;
        id = 0x21d752f;
    }
    ~PostMsg() { if (data) data->Release(); }
};

// ---------------------------------------------------------------------------
// @ 0x007bced0  cThumbnailManager handler for message 0x31e09b4 (dilate without ambient occlusion).
// Builds a filter chain of six dilate/blur passes between the render-target rects of the request and
// posts a BehaviorMessage (0x21d752f, DilateWithoutAODone) once the chain is queued.
// ---------------------------------------------------------------------------
struct DilateReq {
    unsigned pad0[2];
    unsigned f08;
    unsigned pad0c;
    unsigned f10;
    unsigned pad14;
    unsigned f18;
};
typedef EA::AutoRefCount<cJobPostFilter> FilterPtr;

void cThumbnailManager::DilateWithoutAOStart(DilateReq* req)
{
    unsigned b = req->f08;
    RectID rect;
    rect.mAllocID = req->f10;
    rect.mPageID = req->f18;
    IMgr* mgr = GetMgr();
    RectID sizeId;
    sizeId.mPageID = -1;
    sizeId.mAllocID = -1;
    GetRtt()->GetRectAC(&sizeId);

    EA::AutoRefCount<cFilterChainJob> cs(new ("Graphics", 0, 0, 0, 0) cFilterChainJob());
    if (!cs.mpObject->mInitialized) {
        cs.mpObject->mInitialized = 1;
        cs.mpObject->m28 = 0;
    }
    FilterPtr f0(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f1(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f2(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f3(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f4(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f5(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());

    RectID pA, pB;
    pA.mPageID = -1; pA.mAllocID = -1;
    pB.mPageID = -1; pB.mAllocID = -1;
    GetRtt()->GetRectE0(&pA, 0);
    GetRtt()->GetRectE0(&pB, 1);
    f0.mpObject->InitBlur(0xe7, sizeId, pA, 0);
    f0.mpObject->SetClearColor(Vec4(0.0f, 0.0f, 0.0f, 0.0f));
    f0.mpObject->mAdditionalRectIDs.push_back(sizeId);
    f0.mpObject->mCustomParams[0].x = 1.0f;
    f0.mpObject->mCustomParams[0].y = 1.0f;
    f0.mpObject->mCustomParams[0].z = 1.0f;
    f0.mpObject->mCustomParams[0].w = 1.0f;
    f0.mpObject->mCustomParams[1].x = 1.0f;
    f0.mpObject->mCustomParams[1].y = 1.0f;
    f0.mpObject->mCustomParams[1].z = 1.0f;
    f0.mpObject->mCustomParams[1].w = 0.0f;
    f1.mpObject->InitBlur(0xd2, pA, pB, 0);
    f2.mpObject->InitBlur(0xd2, pB, pA, 0);
    f3.mpObject->InitBlur(0xd2, pA, pB, 0);
    f4.mpObject->InitBlur(0xd2, pB, pA, 0);
    f5.mpObject->InitBlur(0xcc, pA, rect, 0);
    f5.mpObject->mAdditionalRectIDs.push_back(sizeId);
    cs.mpObject->AddFilter(f0.mpObject);
    cs.mpObject->AddFilter(f1.mpObject);
    cs.mpObject->AddFilter(f2.mpObject);
    cs.mpObject->AddFilter(f3.mpObject);
    cs.mpObject->AddFilter(f4.mpObject);
    cs.mpObject->AddFilter(f5.mpObject);

    BehaviorMessage* bm = new ("Graphics", 0, 0, 0, 0) BehaviorMessage();
    if (bm)
        bm->AddRef();
    bm->f08 = b;
    bm->f10 = (unsigned)cs.mpObject;
    PostMsg msg(bm);
    mgr->Post(cs.mpObject, 0, &msg);
}

// ---------------------------------------------------------------------------
// @ 0x007bd750  cCSAThumbnailJob::DrawLayer (cILayer slot 3; this = the job, args = DrawLayer's)
// Renders the job's model worlds into the viewer, then (when the 0x5c8af84 property is set) tiles
// the image into a 2x2 grid of viewports, running one post filter per tile.
// ---------------------------------------------------------------------------
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

void cCSAThumbnailJob::DrawLayer(int a0, int layer, DrawCtx* ctx, int a3)
{
    mViewer->Copy(ctx->viewer, 0, 0);
    Vec4 clear(0.0f, 0.0f, 0.0f, 0.0f);
    mViewer->SetClearColor(clear);
    if (!sAppProperties->GetDescription(0x5c8af84)) {
        mViewer->SetRaster(&mInfo.mpObject->mSmallRectId, 1);
        mViewer->Flush(7);
        DrawCtx c;
        c.viewer = mViewer;
        c.a = 0;
        c.b = 0;
        c.c = 0;
        mBackgroundModelWorld->GetLayerDraw()->Draw(a0, layer, &c, a3);
        mModelWorld->GetLayerDraw()->Draw(a0, layer, &c, a3);
        ILayerDraw* extra = mInfo.mpObject->mExtraLayer;
        if (extra)
            extra->Draw(a0, layer, &c, a3);
        GetMgr()->DrawTarget(a3, 0x12, 0x12, &c, 1, 0);
        if (mInfo.mpObject->mPostProcessLayer.mpObject) {
            cJobPostFilter* first = *mInfo.mpObject->mPostProcessLayer.mpObject->mFilterBegin;
            first->mDestRectID = mInfo.mpObject->mSmallRectId;
            mInfo.mpObject->mPostProcessLayer.mpObject->DrawLayer(a0, layer, &c, a3);
        }
    } else {
        mFilterViewer->Copy(mViewer, 0, 0);
        mFilterViewer->Flush(7);
        unsigned tileW = mInfo.mpObject->mResSmall;
        int* screen = GetMgr()->GetScreenSize();
        unsigned tileH = (unsigned)RoundToInt((float)screen[1] / (float)screen[0] * (float)mInfo.mpObject->mResSmall) >> 1;
        tileW >>= 1;
        float v1, v2;
        mViewer->FUN_007c40c0(&v1, &v2);
        v1 = v1 * 0.5f;
        v2 = v2 * 0.5f;
        mViewer->FUN_007c4b00(v1, v2);
        Vec4 p0(1.2f, 1.0f, 1.0f, 1.0f);
        Vec4 p1(0.0f, 1.0f, 1.0f, 0.0f);
        for (unsigned i = 0; i < 2; i++) {
            float rowF = 1.0f - (float)i * 2.0f;
            unsigned xo = i * tileW;
            for (unsigned j = 0; j < 2; j++) {
                mViewer->FUN_007c4ad0(rowF * v1, -(1.0f - (float)j * 2.0f) * v2);
                mViewer->SetRaster(&mInfo.mpObject->mAntiAliasRectId, 1);
                mViewer->Flush(7);
                DrawCtx c;
                c.viewer = mViewer;
                c.a = 0;
                c.b = 0;
                c.c = 0;
                mBackgroundModelWorld->GetLayerDraw()->Draw(a0, layer, &c, a3);
                mModelWorld->GetLayerDraw()->Draw(a0, layer, &c, a3);
                ILayerDraw* extra = mInfo.mpObject->mExtraLayer;
                if (extra)
                    extra->Draw(a0, layer, &c, a3);
                GetMgr()->DrawTarget(a3, 0x12, 0x12, &c, 1, 0);
                if (mInfo.mpObject->mPostProcessLayer.mpObject) {
                    cJobPostFilter* first = *mInfo.mpObject->mPostProcessLayer.mpObject->mFilterBegin;
                    first->mDestRectID = mInfo.mpObject->mAntiAliasRectId;
                    mInfo.mpObject->mPostProcessLayer.mpObject->DrawLayer(a0, layer, &c, a3);
                }
                mFilterViewer->SetRaster(&mInfo.mpObject->mSmallRectId, 1);
                mFilterViewer->SetViewportRect(xo, j * tileH, tileW, tileH);
                FilterPtr filter(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
                filter.mpObject->Initialize(0);
                filter.mpObject->mMaterialId = 0x88549f64;
                filter.mpObject->mSrcRectID = mInfo.mpObject->mAntiAliasRectId;
                filter.mpObject->mDestRectID = mInfo.mpObject->mSmallRectId;
                filter.mpObject->mCustomParams[0] = p0;
                filter.mpObject->mCustomParams[1] = p1;
                filter.mpObject->mCustomParams[3] = clear;
                filter.mpObject->mPreSetViewport = true;
                DrawCtx c2;
                c2.viewer = mFilterViewer;
                c2.a = 0;
                c2.b = 0;
                c2.c = 0;
                filter.mpObject->Draw(0, 0, &c2, a3);
                filter.mpObject->Shutdown();
            }
        }
    }
    FUN_007b3090();
    RenderLargeTiledImage(a0, layer, ctx, a3);
}
