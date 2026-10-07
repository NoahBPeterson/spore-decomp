// Slice s007bde20 -- SP::cThumbnailManager: Shutdown (0x7bde20) and two palette-capture routines
// (0x7be430 CapturePaletteThumbnail, 0x7bea00 sibling).  /O2 /MD /Gy /EHsc /TP /arch:SSE.
//
// Class names for the helper objects (cThumbEffect, cThumbJob*, cThumbTarget*) are Claude-coined
// placeholders: the retail binary has no RTTI for them and the PDB layouts differ.  Field offsets
// and virtual slots are taken from the disassembly.
#include "types.h"
#include <intrin.h>

// ---- allocation: EA 6-arg operator new ("Graphics",0,0,0,0) -------------------------------------
void* operator new(size_t size, const char* name, int a, int b, int c, int d);

// ---- shared small types -------------------------------------------------------------------------
struct Vec3 { float x, y, z; Vec3(const float& a, const float& b, const float& c) { x = a; y = b; z = c; } Vec3() {} };

struct cRenderTargetRectID { int mPageID; int mAllocID; };

// FUN_007c3f70 / 7c3ba0 / 7c4dd0 / 7c4000: the 0x174-byte viewer object.
struct cViewer
{
    uint32_t pad[0x5d];
    cViewer();             // 0x7c3f70
    ~cViewer();            // 0x7c4000
    void Shutdown();       // 0x7c3ba0
    void Init(int arg);    // 0x7c4dd0
};

// Interface with the vtable slots the code uses (0x2c/4 = 11: unregister handler).
struct IHandler { virtual void h0(); };

struct cMessageServer
{
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual void UnregisterHandler(IHandler* handler, unsigned msgID, int priority);  // slot 11
};
struct cModelManager
{
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void m5();
    virtual void UnregisterModelType(unsigned id);  // slot 6
};
struct cSporeManager1  // FUN_0067dd40's return value
{
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void Flush();  // slot 13 (0x34)
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
    virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38();
    virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48();
    virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53();
    virtual void v54(); virtual void v55(); virtual void v56();
    virtual void GetHandle(int* out2);  // slot 57 (0xe4)
};
struct cMessageHandle { int a, b; };
struct cMessageEvent;
struct cSporeManager2  // FUN_0067dd50's return value: slot 30 (0x78) takes the handle
{
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void Dispatch(void* handle);  // slot 30
};

cModelManager* GetModelManager();     // 0x67dd80
cMessageServer* GetMessageServer();   // 0x67dcc0
cSporeManager1* GetManager1();        // 0x67dd40
cSporeManager2* GetManager2();        // 0x67dd50

// Generic ref-counted object with the AddRef/Release slots the thumbnail objects use.
struct RefTarget
{
    virtual int AddRef();
    virtual int Release();
};
// Variant with a leading dummy slot (C and the message objects)
struct RefTarget2
{
    virtual void dummy();
    virtual int AddRef();
    virtual int Release();
};

template <class T> struct RefPtrL  // an AutoRefCount-style local
{
    T* p;
    RefPtrL(T* q) : p(q) { if (p) p->AddRef(); }
    ~RefPtrL() { if (p) p->Release(); }
    T* operator->() const { return p; }
    operator T*() const { return p; }
};

// ---- job objects used by Shutdown ---------------------------------------------------------------
struct cRCVirt { virtual void v0(); virtual void Release(); virtual void Release2(); };  // slots 1, 2

struct cFilterChainJob;
struct cFilterChainJob : cRCVirt
{
    uint32_t pad[(0x60 - 4) / 4];           // up to +0x60
    cFilterChainJob* mChain;                // +0x60 (non-null -> Shutdown)
    uint32_t pad2[(0x78 - 0x64) / 4];       // to +0x78
    bool mInitialized;                      // +0x78
    uint8_t pad3[3];
    uint32_t pad4[(0x90 - 0x7c) / 4];       // to +0x90
    cRCVirt* mEffect;                       // +0x90 (release via slot 2)
    void Shutdown();              // 0x7b96d0
};

struct cAmbOccJob : cRCVirt
{
    uint32_t pad0[2];                       // +4 .. +0xc
    int m0c, m10;
    uint32_t pad[(0xa8 - 0x14) / 4];        // up to +0xa8
    cRCVirt* mHandle;                       // +0xa8
    uint32_t pad2[(0xc4 - 0xac) / 4];
    bool mActive;                           // +0xc4
};

struct cTimelineJob : cRCVirt
{
    uint32_t pad[(0x34 - 4) / 4];           // up to +0x34
    cViewer* mViewer;                       // +0x34
    uint32_t pad2[(0x40 - 0x38) / 4];
    bool mActive;                           // +0x40
};

struct cTextureInstance { uint32_t pad[2]; volatile long mnRefCount; };  // refcount at +8

static inline void ReleaseTexture(cTextureInstance*& slot)
{
    if (slot != 0 && slot != 0)
    {
        volatile long* rc = &slot->mnRefCount;
        slot = 0;
        _InterlockedExchangeAdd(rc, -1);
        long n = _InterlockedExchangeAdd(rc, 0);
        if (n < 1)
            _InterlockedExchangeAdd(rc, 1);
        else
            _InterlockedExchangeAdd(rc, 0);
    }
}

struct cIThumbnailManager { virtual void tm0(); };

struct cRTTManager
{
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3(); virtual void r4();
    virtual void ReleaseRect(cRenderTargetRectID id);  // slot 5
};

// ---- the manager ---------------------------------------------------------------------------------
struct cThumbEffect;
struct cThumbJobBase;
struct cThumbTarget;
struct cCaptureCtx;
struct cPaletteRequest;
struct cPaletteImageRequest;

class cThumbnailManager : public cIThumbnailManager, public IHandler
{
public:
    int mnRefCount;                              // +0x08
    uint32_t pad0c[(0x64 - 0xc) / 4];            // +0x0c .. +0x64
    cTextureInstance* mTimelineCellBg;           // +0x64
    cTextureInstance* mTimelineCreatureBg;       // +0x68
    cTextureInstance* mTimelineTribeBg;          // +0x6c
    cTextureInstance* mTimelineCivBg;            // +0x70
    cTextureInstance* mTimelineSpaceBg;          // +0x74
    cViewer* mSplatterViewer;                    // +0x78
    cViewer* mBakeInfoSplatterViewer;            // +0x7c
    cViewer* mNMapSpecSplatterViewer;            // +0x80
    cViewer* mDilateViewer;                      // +0x84
    cViewer* mAmbOccShadowViewers[1024];         // +0x88
    cViewer* mAmbOccSplatterViewer;              // +0x1088
    cViewer* mAmbOccGatherViewer;                // +0x108c
    void* mLargeBufferTexture;                   // +0x1090
    cRenderTargetRectID mLargeBufferTextureRectID;  // +0x1094
    uint32_t pad109c[(0x10b4 - 0x109c) / 4];
    cRTTManager* mRTTMgr;                        // +0x10b4
    uint32_t pad10b8[(0x10e4 - 0x10b8) / 4];
    cFilterChainJob* mPostFilter0;               // +0x10e4
    cFilterChainJob* mPostFilter1;               // +0x10e8
    cFilterChainJob* mPostFilter2;               // +0x10ec
    uint32_t pad10f0[(0x10fc - 0x10f0) / 4];
    cFilterChainJob* mAOPostProcessLayer;        // +0x10fc
    cAmbOccJob* mAmbOccRenderJob[1024];          // +0x1100
    cTimelineJob* mTimelineJobs[3];              // +0x2100

    bool Shutdown();                                                       // 0x7bde20
    void SetupThumbnailRTTs(unsigned a, int b);                            // 0x7b26a0
    void InitPostProcessEffect(unsigned a, cThumbEffect* e, int one, bool noAA, Vec3 v);  // 0x7ba350
    void CapturePaletteThumbnail(cCaptureCtx* ctx, cPaletteRequest* req);  // 0x7be430
    void CapturePaletteImageThumbnail(cCaptureCtx* ctx, cPaletteImageRequest* req);  // 0x7bea00
    void FUN_007b9e80();                                                   // 0x7b9e80
};

static inline void ReleaseJob(cFilterChainJob*& slot)
{
    cFilterChainJob* j = slot;
    if (j)
    {
        slot = 0;
        j->Release();
    }
}

static inline void ShutdownFilter(cFilterChainJob*& slot)
{
    cFilterChainJob* f = slot;
    if (f)
    {
        if (f->mInitialized)
        {
            if (f->mChain)
                f->mChain->Shutdown();
            cRCVirt* e = f->mEffect;
            if (e)
            {
                f->mEffect = 0;
                e->Release2();
            }
            f->mInitialized = false;
        }
        ReleaseJob(slot);
    }
}

bool cThumbnailManager::Shutdown()
{
    GetModelManager()->UnregisterModelType(0x247d6adu);
    cMessageServer* ms = GetMessageServer();
    if (ms)
    {
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x1c913db, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x1c91270, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x212c1ee, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x21d7528, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x31e09b4, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x21d752f, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x50b834d, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x5221305, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x5fadac4, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x5fc2c38, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x7b240a0, -10000);
        ms->UnregisterHandler(static_cast<IHandler*>(this), 0x238de9c, -10000);
    }
    GetManager1()->Flush();

    if (mSplatterViewer)
    {
        mSplatterViewer->Shutdown();
        delete mSplatterViewer;
        mSplatterViewer = 0;
    }
    if (mBakeInfoSplatterViewer)
    {
        mBakeInfoSplatterViewer->Shutdown();
        delete mBakeInfoSplatterViewer;
        mBakeInfoSplatterViewer = 0;
    }
    if (mNMapSpecSplatterViewer)
    {
        mNMapSpecSplatterViewer->Shutdown();
        delete mNMapSpecSplatterViewer;
        mNMapSpecSplatterViewer = 0;
    }
    if (mDilateViewer)
    {
        mDilateViewer->Shutdown();
        delete mDilateViewer;
        mDilateViewer = 0;
    }
    if (mAmbOccSplatterViewer)
    {
        mAmbOccSplatterViewer->Shutdown();
        delete mAmbOccSplatterViewer;
        mAmbOccSplatterViewer = 0;
    }
    if (mAmbOccGatherViewer)
    {
        mAmbOccGatherViewer->Shutdown();
        delete mAmbOccGatherViewer;
        mAmbOccGatherViewer = 0;
    }
    if (mLargeBufferTexture)
    {
        mRTTMgr->ReleaseRect(mLargeBufferTextureRectID);
        mLargeBufferTexture = 0;
    }

    for (int i = 0; i < 1024; i++)
    {
        if (mAmbOccShadowViewers[i])
        {
            mAmbOccShadowViewers[i]->Shutdown();
            delete mAmbOccShadowViewers[i];
            mAmbOccShadowViewers[i] = 0;
        }
        cAmbOccJob* job = mAmbOccRenderJob[i];
        if (job)
        {
            if (job->mActive)
            {
                cRCVirt* h = job->mHandle;
                if (h)
                {
                    job->mHandle = 0;
                    h->Release();
                }
                job->m0c = 0;
                job->m10 = 0;
                job->mActive = false;
            }
            cAmbOccJob* j2 = mAmbOccRenderJob[i];
            if (j2)
            {
                mAmbOccRenderJob[i] = 0;
                j2->Release();
            }
        }
    }

    if (mAOPostProcessLayer)
    {
        mAOPostProcessLayer->Shutdown();
        ReleaseJob(mAOPostProcessLayer);
    }

    ShutdownFilter(mPostFilter0);
    ShutdownFilter(mPostFilter1);
    ShutdownFilter(mPostFilter2);

    ReleaseTexture(mTimelineCellBg);
    ReleaseTexture(mTimelineCreatureBg);
    ReleaseTexture(mTimelineTribeBg);
    ReleaseTexture(mTimelineCivBg);
    ReleaseTexture(mTimelineSpaceBg);

    for (int i = 0; i < 3; i++)
    {
        cTimelineJob* tj = mTimelineJobs[i];
        if (tj)
        {
            if (tj->mActive)
            {
                if (tj->mViewer)
                {
                    tj->mViewer->Shutdown();
                    delete tj->mViewer;
                    tj->mViewer = 0;
                }
                tj->mActive = false;
            }
            cTimelineJob* t2 = mTimelineJobs[i];
            if (t2)
            {
                mTimelineJobs[i] = 0;
                t2->Release();
            }
        }
    }

    FUN_007b9e80();
    return true;
}

// =====================================================================================================
// Palette capture helpers
// =====================================================================================================

// 0x34-byte effect object (vptr pair at +0, +4)
struct cThumbRef { virtual int AddRef(); virtual int Release(); };
struct cThumbBase2 { virtual void sb0(); int m08; cThumbBase2() : m08(0) {} };  // second base (vptr +4, field +8)

struct cThumbEffect : cThumbRef, cThumbBase2
{
    virtual void e2(); virtual void e3(); virtual void e4();
    virtual void CaptureBox(Vec3* box, cViewer* world, int p, float z, int q, float w);  // slot 5 (0x14)
    virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual void e10();
    virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15();
    virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19();
    virtual void CaptureRect(void* src, cViewer* world, int p, void* q, float r, float z);   // slot 20 (0x50)
    int m0c, m10, m14;   // +0xc..+0x14
    int pad18, pad1c;
    bool mFlag;          // +0x20
    int m24, m28, m2c, m30;
    cThumbEffect();
};

cThumbEffect::cThumbEffect() : m0c(0), m10(0), m14(0), mFlag(false), m24(0), m28(0), m2c(0), m30(0) {}

// job object: AddRef slot 0, Release slot 1, slot 4: build the message handle
struct cThumbJobMsgEvent
{
    int a;        // +0
    int b;        // +4
    bool c;       // +8
    int d;        // +0xc
    int e;        // +0x10
    unsigned id;  // +0x14
    void* data;   // +0x18
    int f, g, h, i;
};

struct cThumbJobA : cThumbRef, cThumbBase2
{
    virtual void j2(); virtual void j3();
    virtual void* Queue(int zero, cThumbJobMsgEvent* ev);  // slot 4
    bool m0c;
    int m10;
    int pad14;
    int m18, m1c;
    uint32_t pad20[3];
    int m2c, m30;
    cThumbJobA();
    void Run(void* arg1, cViewer* world, cThumbTarget* tgt);  // 0x7b2ab0
};
cThumbJobA::cThumbJobA() : m0c(false), m10(0), m18(-1), m1c(-1), m2c(0), m30(0) {}

struct cThumbJobB : cThumbRef, cThumbBase2
{
    virtual void j2(); virtual void j3();
    virtual void* Queue(int zero, cThumbJobMsgEvent* ev);  // slot 4
    bool m0c;
    int m10;
    int pad14;
    int m18, m1c;
    uint32_t pad20[3];
    int m2c, m30;
    cThumbJobB();
    void Run(void* arg1, cViewer* world, cThumbTarget* tgt);  // 0x7b2ca0
};
cThumbJobB::cThumbJobB() : m0c(false), m10(0), m18(-1), m1c(-1), m2c(0), m30(0) {}

struct cImageResource { int v; void Set(int resKey); };  // 0x576650 (thiscall, 1 arg), object at target+0x1c

// target object C: slot0 dummy, AddRef slot 1, Release slot 2.  Two variants (0x30 and 0x34 bytes)
struct cThumbTarget
{
    virtual void dummy();
    virtual int AddRef();
    virtual int Release();
    int pad04;                      // +4
    int mHandleA, mHandleB;         // +8, +0xc
    cThumbEffect* mEffect;          // +0x10 (AutoRefCount, slot-1 release)
    int m14, m18, m1c, m20, m24;
    bool m28;
    int m2c;
    cThumbTarget();
};
cThumbTarget::cThumbTarget() : pad04(0), mHandleA(-1), mHandleB(-1), mEffect(0) {}

struct cThumbTargetB  // 0x34 bytes: image-resource variant
{
    virtual void dummy();
    virtual int AddRef();
    virtual int Release();
    int pad04;
    int mHandleA, mHandleB;
    cThumbEffect* mEffect;          // +0x10
    int m14, m18;
    cImageResource mImage;          // +0x1c (resource at ctor)
    float m20, m24;                 // +0x20, +0x24
    int m28, m2c, m30;
    cThumbTargetB();
};
cThumbTargetB::cThumbTargetB() : pad04(0), mHandleA(-1), mHandleB(-1), mEffect(0) {}

// 0x28-byte BehaviorMessage-like object: slot0 dummy, AddRef slot 1, Release slot 2
struct cThumbDoneMsg
{
    virtual void dummy();
    virtual int AddRef();
    virtual int Release();
    volatile long mRef;       // +4
    int m08, m0c, m10, m14;
    void* mJob;               // +0x18
    int m1c, m20, m24;
    cThumbDoneMsg();
};
cThumbDoneMsg::cThumbDoneMsg() : m20(0) { _InterlockedExchange(&mRef, 0); }

// request/context structs (offsets from the disassembly)
struct BBox3 { Vec3 mn, mx; };

struct cPaletteRequest
{
    uint32_t pad00[2];
    unsigned m08;          // +8
    int m0c;               // +0xc
    unsigned m10;          // +0x10
    int m14;               // +0x14
    unsigned m18;          // +0x18
    unsigned m1c;          // +0x1c
    unsigned m20;
    float m24;             // +0x24 (second variant)
    float m28;             // +0x28
    BBox3* mBoxBegin;      // +0x2c
    BBox3* mBoxEnd;        // +0x30
    uint32_t pad34[2];
    unsigned m3c;          // +0x3c
    unsigned m40;          // +0x40
    int mMode;             // +0x44
    float m48;             // +0x48
    float m4c;             // +0x4c
    float m50;             // +0x50
};

struct cPropertyList { bool GetDescription(unsigned id); };  // 0x6a25a0
extern cPropertyList* g_sAppProperties;                       // [0x15fd918]
extern float g_fFltMax;      // [0x140fd1c]
extern float g_fNegFltMax;   // [0x13f51ac]
extern float g_fOne;
extern float g_fVecX;  // 0x01635640
extern float g_fVecY;  // 0x01635644

// 0x7be430
void cThumbnailManager::CapturePaletteThumbnail(cCaptureCtx* ctx, cPaletteRequest* req)
{
    bool hasDesc = g_sAppProperties->GetDescription(0x5cb6033);
    SetupThumbnailRTTs(req->m08, 1);

    RefPtrL<cThumbEffect> effect(new ("Graphics", 0, 0, 0, 0) cThumbEffect);
    if (!effect->mFlag)
    {
        effect->mFlag = true;
        effect->m28 = 0;
    }
    InitPostProcessEffect(req->m40, effect, 1, !hasDesc, Vec3(g_fVecX, g_fVecY, 0.0f));

    RefPtrL<cThumbJobA> job(new ("Graphics", 0, 0, 0, 0) cThumbJobA);
    cThumbTarget* tgtRaw = new ("Graphics", 0, 0, 0, 0) cThumbTarget;
    RefPtrL<cThumbTarget> tgt(tgtRaw);

    cMessageHandle h = { -1, -1 };
    GetManager1()->GetHandle(&h.a);
    tgt->mHandleA = h.a;
    tgt->mHandleB = h.b;
    if (tgt->mEffect != effect.p)
    {
        effect->AddRef();
        cThumbEffect* old = tgt->mEffect;
        tgt->mEffect = effect.p;
        if (old)
            old->Release();
    }
    tgt->m14 = req->m0c;
    tgt->m20 = req->m18;
    tgt->m24 = req->m14;
    tgt->m18 = req->m08;
    tgt->m1c = req->m08;
    tgt->m28 = hasDesc;
    tgt->m2c = req->m40;

    cViewer* world = new ("Graphics", 0, 0, 0, 0) cViewer;
    world->Init(0);

    if (req->mMode == 1)
    {
        effect->CaptureRect(&req->mBoxBegin, world, req->m0c, &req->m1c, req->m28, 0.0f);
    }
    else if (req->mMode == 0)
    {
        BBox3 box;
        box.mn.x = box.mn.y = box.mn.z = g_fFltMax;
        box.mx.x = box.mx.y = box.mx.z = g_fNegFltMax;
        unsigned i = 0;
        const BBox3* src = req->mBoxBegin;
        for (; i < (unsigned)(req->mBoxEnd - req->mBoxBegin); i++, src++)
        {
            if (box.mn.x > box.mx.x)
            {
                box = *src;
            }
            else
            {
                if (src->mn.x < box.mn.x) box.mn.x = src->mn.x;
                if (src->mx.x > box.mx.x) box.mx.x = src->mx.x;
                if (src->mn.y < box.mn.y) box.mn.y = src->mn.y;
                if (src->mx.y > box.mx.y) box.mx.y = src->mx.y;
                if (src->mn.z < box.mn.z) box.mn.z = src->mn.z;
                if (src->mx.z > box.mx.z) box.mx.z = src->mx.z;
            }
        }
        effect->CaptureBox(&box.mn, world, req->m0c, req->m48, (int)req->m40, 1.0f);
    }

    job->Run(ctx, world, tgt);
    world->Shutdown();
    if (world)
        delete world;

    RefPtrL<cThumbDoneMsg> msg(new ("Graphics", 0, 0, 0, 0) cThumbDoneMsg);
    msg->m08 = req->m10;
    msg->m10 = 0;
    msg->mJob = job.p;

    cThumbJobMsgEvent ev;
    ev.a = 1;
    ev.b = 4;
    ev.c = false;
    ev.d = 0;
    ev.e = 0;
    ev.id = 0x1c913db;
    ev.data = msg.p;
    ev.f = ev.g = ev.h = ev.i = 0;
    void* handle = job->Queue(0, &ev);
    GetManager2()->Dispatch(handle);
}

// request layout used by the image-resource variant
struct cPaletteImageRequest
{
    uint32_t pad00[2];
    unsigned m08;          // +8
    int m0c;               // +0xc
    unsigned m10;          // +0x10
    int m14;               // +0x14
    unsigned m18, m1c, m20;  // +0x18..+0x20
    float m24;             // +0x24
    uint32_t m28[4];       // +0x28 (address passed on)
    unsigned m38;
    unsigned m3c;          // +0x3c
    float m40, m44, m48;   // +0x40..+0x48
    float m4c, m50;        // +0x4c, +0x50
};

// 0x7bea00: image-resource variant
// @ 0x007bea00
void cThumbnailManager::CapturePaletteImageThumbnail(cCaptureCtx* ctx, cPaletteImageRequest* req)
{
    SetupThumbnailRTTs(req->m08, 1);

    RefPtrL<cThumbEffect> effect(new ("Graphics", 0, 0, 0, 0) cThumbEffect);
    if (!effect->mFlag)
    {
        effect->mFlag = true;
        effect->m28 = 0;
    }
    InitPostProcessEffect(req->m3c, effect, 1, false, Vec3(req->m40, req->m44, req->m48));

    RefPtrL<cThumbJobB> job(new ("Graphics", 0, 0, 0, 0) cThumbJobB);
    RefPtrL<cThumbTargetB> tgt(new ("Graphics", 0, 0, 0, 0) cThumbTargetB);

    cMessageHandle h = { -1, -1 };
    GetManager1()->GetHandle(&h.a);
    tgt->mHandleA = h.a;
    tgt->mHandleB = h.b;
    if (tgt->mEffect != effect.p)
    {
        effect->AddRef();
        cThumbEffect* old = tgt->mEffect;
        tgt->mEffect = effect.p;
        if (old)
            old->Release();
    }
    tgt->m14 = req->m08;
    tgt->m18 = req->m08;
    tgt->mImage.Set(req->m14);
    tgt->m24 = req->m50;
    tgt->m20 = req->m4c;
    tgt->m28 = req->m18;
    tgt->m2c = req->m1c;
    tgt->m30 = req->m20;

    cViewer* world = new ("Graphics", 0, 0, 0, 0) cViewer;
    world->Init(0);
    effect->CaptureRect(&req->m28, world, req->m0c, &req->m18, req->m24, 0.0f);
    job->Run(ctx, world, (cThumbTarget*)tgt.p);
    world->Shutdown();
    if (world)
        delete world;

    RefPtrL<cThumbDoneMsg> msg(new ("Graphics", 0, 0, 0, 0) cThumbDoneMsg);
    msg->m08 = req->m10;
    msg->m10 = 1;
    msg->mJob = job.p;

    cThumbJobMsgEvent ev;
    ev.a = 1;
    ev.b = 4;
    ev.c = false;
    ev.d = 0;
    ev.e = 0;
    ev.id = 0x1c913db;
    ev.data = msg.p;
    ev.f = ev.g = ev.h = ev.i = 0;
    void* handle = job->Queue(0, &ev);
    GetManager2()->Dispatch(handle);
}
