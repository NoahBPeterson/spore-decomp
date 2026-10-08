// Slice s007bb670 — SP::cContentValidationSummarizer setup + a cThumbnailManager
// message handler.  Both are /O2 /arch:SSE2 /EHsc routines in the UI/thumbnail
// region.  Reconstructed from the Ghidra decompile; see nonmatching.txt.
#include "types.h"

// --- job / rect object (shared with s007ba350) -----------------------------
struct RectID { int mPageID; int mAllocID; };

struct  Job {
    virtual void v0();       // +0
    virtual void v1();       // +4
    virtual void v2();       // +8
    char pad[0x98];
    unsigned char m82;       // +0x82
    unsigned char m83;       // +0x83
    int  m84, m88, m8c, m90, m94;
    int  m98, m9c, ma0, ma4;
    int  mac[8];
    float mcc;
};

// cThumbnailManager::cFilterChainJob
struct cFilterChainJob { void Shutdown(); };

// An object referenced through +0x10c8 (AutoRefCount<T> payload).
struct ModelObj {
    virtual void v0();       // +0
    virtual void v1();       // +4
    char pad[0x38];
    int  m40;                // +0x40
};

struct Thumb {
    char pad[0xc];
    int  m0c;                // +0xc
    int  m10;                // +0x10
    char pad2[0x94];
    ModelObj* m_a8;          // +0xa8
    char pad3[0x18];
    unsigned char m_c4;      // +0xc4
};

// SP::MessageServer's base message object (refcounted, 2 vtables).
struct BehaviorMessage {
    virtual void v0();       // +0
    virtual void v1();       // +4
    virtual void v2();       // +8
    int  mRefCount;          // +4
    int  m8;                 // +8
    int  mc;                 // +0xc
    int  m10;                // +0x10
    int  m14;
    int  m18;                // +0x18
    int  m1c;
    int  m20;                // +0x20
    int  m24;
    int  m28;                // +0x28
};

struct MessageServer_t {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void Send(int id, BehaviorMessage* msg, int a);   // +0x14
};

void* operator new(unsigned int size, const char* group, int a, int b, int c, int d);

extern "C" {
    void* __cdecl FUN_0067dd50();
    void* __cdecl FUN_0067dd40();
    MessageServer_t* __cdecl SP_MessageServer();
}

// Helpers of the summarizer setup (thiscall on the job / manager).
void FUN_007b9420(Job* self, int v);
void FUN_007b9510(Job* self, int id, int* a, int* b, int c);
void FUN_007b9750(Job* self, void* other);
Job* FUN_007b8550(Job* p);

// ---------------------------------------------------------------------------
// @ 0x007bb670  cThumbnailManager message handler (vtable table at 0x140ff64, thiscall, ret 4).
// Builds the 7-filter "dilate" post chain for a request: filter 0 reads the size rect, filters 1-4
// ping-pong between two temp rects, filter 5 writes the result rect (rect from the render-target
// manager), filter 6 is an extra copy added when the 0x1a91189c app property is set.  The chain is
// handed to the manager together with a RefBaseA22 callback object (message id 0x5221305).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
// ---------------------------------------------------------------------------
#include <intrin.h>
#pragma intrinsic(_InterlockedExchange)

namespace n670 {

struct RectID { int mPageID; int mAllocID; };
struct Vec4 {
    float x, y, z, w;
    Vec4() {}
    Vec4(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
};

// RefBaseA22 -> callback object installed on the chain (0x20 bytes; vtable 0x1452a38)
struct RefBaseA22 {
    virtual ~RefBaseA22();
    virtual int AddRef();                            // +0x04
    virtual int Release();                           // +0x08
    volatile long mnRefCount;                        // +0x04
    RefBaseA22() { _InterlockedExchange(&mnRefCount, 0); }
};
struct cChainCallback : RefBaseA22 {
    int mField08, pad0c;                             // +0x08
    void* mChain;                                    // +0x10
    int pad14;
    int mField18, pad1c;                             // +0x18
    cChainCallback() : mField18(0) {}
    virtual ~cChainCallback();
};
struct DrvPtr {
    RefBaseA22* mpObject;
    DrvPtr& operator=(RefBaseA22* p)
    {
        if (p != mpObject) {
            RefBaseA22* const old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};
struct CbPtr {
    RefBaseA22* mpObject;
    CbPtr(RefBaseA22* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~CbPtr() { if (mpObject) mpObject->Release(); }
};

struct cJobPostFilter;
struct cChainBaseA { virtual int AddRef(); virtual int Release(); };
struct cChainBaseB {
    virtual void b0();
    virtual void b1();
    int mRefCount;
    cChainBaseB() { mRefCount = 0; }
};
struct cFilterChainJob : cChainBaseA, cChainBaseB {
    cJobPostFilter** mFilterBegin;                   // +0x0c
    cJobPostFilter** mFilterEnd;                     // +0x10
    cJobPostFilter** mFilterCapacity;                // +0x14
    int m18, m1c;
    unsigned char mInitialized;                      // +0x20
    int m24, m28, m2c;
    DrvPtr mCallback;                                // +0x30
    cFilterChainJob() {
        mFilterBegin = 0; mFilterEnd = 0; mFilterCapacity = 0;
        mInitialized = 0;
        m24 = 0; m28 = 0; m2c = 0; mCallback.mpObject = 0;
    }
    void AddFilter(cJobPostFilter* pFilter);         // 0x007b9750
};
struct ChainPtr {
    cFilterChainJob* mpObject;
    ChainPtr(cFilterChainJob* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~ChainPtr() { if (mpObject) mpObject->Release(); }
    cFilterChainJob* operator->() const { return mpObject; }
};

struct cJobPostFilter {
    virtual int AddRef();                            // +0x00
    virtual int Release();                           // +0x04
    virtual void v2();
    virtual void Draw(int a0, int layer, void* ctx, int a3);   // +0x0c
    unsigned mRefCountV[2];                          // +0x04
    unsigned mMaterialId;                            // +0x0c
    RectID mSrcRectID;                               // +0x10
    unsigned mSrcRaster;                             // +0x18
    RectID mDestRectID;                              // +0x1c
    struct RectVec {                                 // eastl::vector<cRenderTargetRectID>, +0x24
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
    } mAdditionalRectIDs;
    unsigned pad30[2];
    void* mViewer;                                   // +0x38
    Vec4 mCustomParams[4];                           // +0x3c
    unsigned pad7c[1];
    bool mInitialized;                               // +0x80
    bool mDumpTexture;                               // +0x81
    bool mClearBeforeDraw;                           // +0x82
    bool mOverrideViewport;                          // +0x83
    int mView[4];                                    // +0x84
    int mQuadrant;                                   // +0x94
    Vec4 mClearColor;                                // +0x98
    bool mPreSetViewport;                            // +0xa8
    char padA9[0xe4 - 0xa9];

    cJobPostFilter();                                // 0x007b8550
    void Initialize(int flags);                      // 0x007b9420
    void InitBlur(int taps, const RectID& src, const RectID& dest, int flags);   // 0x007b9510
    void SetClearColor(Vec4 c) { mClearColor = c; mClearBeforeDraw = true; }     // 0x007b27a0
};
typedef struct FilterPtrT {
    cJobPostFilter* mpObject;
    FilterPtrT(cJobPostFilter* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~FilterPtrT() { if (mpObject) mpObject->Release(); }
    cJobPostFilter* operator->() const { return mpObject; }
} FilterPtr;

struct PostMsg {                                     // 0x2c bytes passed to IMgr::Post
    int kind;
    int a;
    unsigned char b;
    int c, d;
    unsigned id;
    void* data;
    int e, f, g, h;
    PostMsg() {
        a = 0; b = 1; c = 0; d = 0;
        e = 0; f = 0; g = 0; h = 0;
        kind = 1;
        data = 0;
        id = 0;
    }
};

struct IMgr {                                        // 0x0067dd50
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29();
    virtual void Post(void* sender, int a, void* msg);         // +0x78
};
IMgr* __cdecl GetMgr();                              // 0x0067dd50

struct IRtt {                                        // 0x0067dd40
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42();
    virtual void GetRectAC(RectID* out);             // +0xac
    virtual void s44(); virtual void s45(); virtual void s46();
    virtual void GetRectBC(RectID* out);             // +0xbc
    virtual void s48(); virtual void s49();
    virtual void GetRectC8(RectID* out);             // +0xc8
    virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); virtual void s55();
    virtual void GetRectE0(RectID* out, int index);  // +0xe0
};
IRtt* __cdecl GetRtt();                              // 0x0067dd40

struct cPropertyList {
    bool GetDescription(unsigned id);                // 0x006a25a0
};
extern cPropertyList* sAppProperties;                // 0x015fd918

struct cThumbnailManager {
    void __thiscall DilateSetup(int arg);            // 0x007bb670
};

void __thiscall cThumbnailManager::DilateSetup(int arg)
{
    IMgr* mgr = GetMgr();
    IRtt* rtt = GetRtt();
    RectID sizeId;
    sizeId.mPageID = -1;
    sizeId.mAllocID = -1;
    RectID rectB;
    rectB.mPageID = -1;
    rectB.mAllocID = -1;
    rtt->GetRectAC(&sizeId);
    rtt->GetRectBC(&rectB);

    ChainPtr cs(new ("Graphics", 0, 0, 0, 0) cFilterChainJob());
    if (!cs->mInitialized) {
        cs->mInitialized = 1;
        cs->m28 = 0;
    }
    FilterPtr f0(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f1(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f2(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f3(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f4(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f5(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());
    FilterPtr f6(new ("Graphics", 0, 0, 0, 0) cJobPostFilter());

    RectID t;
    RectID pA, pB;
    pA.mPageID = -1; pA.mAllocID = -1;
    pB.mPageID = -1; pB.mAllocID = -1;
    GetRtt()->GetRectE0(&pA, 0);
    GetRtt()->GetRectE0(&pB, 1);
    f0->InitBlur(0xe7, sizeId, pA, 0);
    f0->mAdditionalRectIDs.push_back(sizeId);
    f0->mCustomParams[0].x = 1.0f;
    f0->mCustomParams[0].y = 1.0f;
    f0->mCustomParams[0].z = 1.0f;
    f0->mCustomParams[0].w = 1.0f;
    f0->mCustomParams[1].x = 1.0f;
    f0->mCustomParams[1].y = 1.0f;
    f0->mCustomParams[1].z = 1.0f;
    f0->mCustomParams[1].w = 0.0f;
    f1->InitBlur(0xd2, pA, pB, 0);
    f2->InitBlur(0xd2, pB, pA, 0);
    f3->InitBlur(0xd2, sizeId, pB, 0);
    f4->InitBlur(0xd2, pB, sizeId, 0);
    f5->InitBlur(0xcc, pA, rectB, 0);
    f5->SetClearColor(Vec4(0.0f, 0.0f, 0.0f, 0.0f));
    f5->mAdditionalRectIDs.push_back(sizeId);

    cPropertyList* props = sAppProperties;
    if (props->GetDescription(0x1a91189c)) {
        f6->Initialize(0);
        f6->mMaterialId = 0x28;
        f6->mSrcRectID = rectB;
        t.mPageID = -1;
        t.mAllocID = -1;
        GetRtt()->GetRectC8(&t);
        f6->mDestRectID = t;
        f6->mCustomParams[0].x = 1.0f;
        f6->mCustomParams[0].y = 1.0f;
        f6->mCustomParams[0].z = 1.0f;
        f6->mCustomParams[0].w = 1.0f;
        f6->mCustomParams[1].x = 0.0f;
        f6->mCustomParams[1].y = 1.0f;
        f6->mCustomParams[1].z = 1.0f;
        f6->mCustomParams[1].w = 0.0f;
        f6->mCustomParams[3].x = 0.0f;
        f6->mCustomParams[3].y = 0.0f;
        f6->mCustomParams[3].z = 0.0f;
        f6->mCustomParams[3].w = 0.0f;
    }
    cs->AddFilter(f0.mpObject);
    cs->AddFilter(f1.mpObject);
    cs->AddFilter(f2.mpObject);
    cs->AddFilter(f3.mpObject);
    cs->AddFilter(f4.mpObject);
    cs->AddFilter(f5.mpObject);
    if (props->GetDescription(0x1a91189c))
        cs->AddFilter(f6.mpObject);

    cs->m24 = 1;
    CbPtr cb(new ("Graphics", 0, 0, 0, 0) cChainCallback());
    ((cChainCallback*)cb.mpObject)->mField08 = arg;
    ((cChainCallback*)cb.mpObject)->mChain = cs.mpObject;
    cs->m2c = 0x5221305;
    cs->mCallback = cb.mpObject;
    if (cs->m24 == 0)
        cs->m24 = 0x14;
    cs->AddRef();
    PostMsg msg;
    mgr->Post(cs.mpObject, 0, &msg);
}

}  // namespace n670

// ---------------------------------------------------------------------------
// @ 0x007bbde0  cThumbnailManager message handler (ret 4)
// ---------------------------------------------------------------------------
struct cThumbnailManager {
    char pad[0x10c8];
    ModelObj*     mModel;        // +0x10c8
    char pad2[0x10fc - 0x10cc];
    cFilterChainJob* mFilterChain;   // +0x10fc
    Thumb* mThumbs[1024];        // +0x1100

    void HandleSomething(void* msg);
};

void cThumbnailManager::HandleSomething(void* msg)
{
    int f8  = *(int*)((char*)msg + 8);
    int f10 = *(int*)((char*)msg + 0x10);
    int f18 = *(int*)((char*)msg + 0x18);
    int f20 = *(int*)((char*)msg + 0x20);
    int f28 = *(int*)((char*)msg + 0x28);
    int f30 = *(int*)((char*)msg + 0x30);

    if (f8 == f18 - 1) {
        if (f18 != 0) {
            Thumb** p = mThumbs;
            int n = f18;
            do {
                Thumb* t = *p;
                if (t->m_c4) {
                    ModelObj* o = t->m_a8;
                    if (o) { t->m_a8 = 0; o->v1(); }
                    t->m0c = 0;
                    t->m10 = 0;
                    t->m_c4 = 0;
                }
                ++p;
                --n;
            } while (n);
        }
        mFilterChain->Shutdown();
        ModelObj* m = mModel;
        if (m) {
            m->v0();                     // placeholder for vtable+0x16c call
            m = mModel;
            if (m) {
                mModel = 0;
                if (m->m40 <= 1)
                    m->v1();             // placeholder for vtable+0x170 call
                else
                    --m->m40;
            }
        }
        BehaviorMessage* bm = new ("Graphics",0,0,0,0) BehaviorMessage();
        if (bm) bm->v1();
        bm->m8  = f10;
        bm->m10 = f20;
        bm->m18 = f28;
        bm->m20 = f30;
        SP_MessageServer()->Send(0x21d7528, bm, 0);
        if (bm) bm->v2();
    }
}
