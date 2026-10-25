// Slice s007bedb0 — SP::cThumbnailManager capture/dispatch routines.
// /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"
#include <intrin.h>

struct RectID { int mPageID; int mAllocID; bool IsValid() const { return mAllocID != -1; } };

// types used by the CSA photo pipeline reconstructed at the bottom of the file
struct cRTTManager;
struct cFilterChainJob;
struct cThumbEffect;
struct Ref1;
struct CSARequest;
struct CaptureDoneMsg;

// ---------------------------------------------------------------------------
// jobs (only Shutdown is needed by ThumbnailDone)
// ---------------------------------------------------------------------------
struct cPaletteThumbnailJob { void Shutdown(); };
struct cEditorThumbnailJob  { void Shutdown(); };
struct cCSAThumbnailJob     { void Shutdown(); };
struct cGameThumbnailJob    { void Shutdown(); };

// ---------------------------------------------------------------------------
// @ 0x007bf610  SP::cThumbnailManager::ThumbnailDone(this, msg)   (ret 4)
// ---------------------------------------------------------------------------
struct MessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void Call14(int a, int b, int c);                 // +0x14
    virtual void Post(int a, int b, int c, int d);              // +0x18
};
MessageServer* __cdecl SP_MessageServer();          // 0x0067dcc0

struct RTTFree {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void Free(int page, int alloc);                   // +0x14
};
void* __cdecl FUN_0067dda0();

struct DoneMsg {
    char pad0[8];
    int m8;                                                    // +0x08
    char pad1[4];
    int m10;                                                   // +0x10
    char pad2[4];
    void* mJob;                                                // +0x18
};

struct cThumbnailManager {
    char pad0[0x14];
    RectID mThumbRectID;                                       // +0x14
    RectID mBlurThumbRectID1;                                  // +0x1c
    RectID mBlurThumbRectID2;                                  // +0x24
    RectID mTempThumbnailBuffer;                               // +0x2c
    RectID mCSALargeRectID;                                    // +0x34
    RectID mCSASmallRectID;                                    // +0x3c
    RectID mCSAAntiAliasRectID;                                // +0x44
    char pad4c[0x10b4 - 0x4c];
    cRTTManager* mRTTMgr;                                      // +0x10b4
    char pad10b8[0x10e4 - 0x10b8];
    cFilterChainJob* mPostFilter0;                             // +0x10e4
    cFilterChainJob* mPostFilter1;                             // +0x10e8
    cFilterChainJob* mPostFilter2;                             // +0x10ec

    void ThumbnailDone(DoneMsg* msg);
    void CaptureCSAPhotos(CSARequest* req);                    // 0x007bedb0
    void SetupCSARTTs(CSARequest* req);                        // 0x007bf300
    void DispatchCaptureDone(CaptureDoneMsg* msg);             // 0x007bf720
    void SetupThumbnailRTTs(int a, char b);                    // 0x007b26a0
    void InitPostProcessEffect(int type, cThumbEffect* chain, bool enable, bool alt,
                               struct Vec2f v, float f);       // 0x007ba350
};

void cThumbnailManager::ThumbnailDone(DoneMsg* msg)
{
    int u = msg->m8;
    switch (msg->m10) {
    case 2: ((cCSAThumbnailJob*)msg->mJob)->Shutdown(); break;
    case 1: ((cEditorThumbnailJob*)msg->mJob)->Shutdown(); break;
    case 0: ((cPaletteThumbnailJob*)msg->mJob)->Shutdown(); break;
    case 3: ((cGameThumbnailJob*)msg->mJob)->Shutdown();
    }
    SP_MessageServer()->Call14(u, 0, 0);
    RTTFree* r = (RTTFree*)FUN_0067dda0();
    if (mThumbRectID.IsValid())
        r->Free(mThumbRectID.mPageID, mThumbRectID.mAllocID);
    if (mBlurThumbRectID1.IsValid())
        r->Free(mBlurThumbRectID1.mPageID, mBlurThumbRectID1.mAllocID);
    if (mBlurThumbRectID2.IsValid())
        r->Free(mBlurThumbRectID2.mPageID, mBlurThumbRectID2.mAllocID);
    if (mTempThumbnailBuffer.IsValid())
        r->Free(mTempThumbnailBuffer.mPageID, mTempThumbnailBuffer.mAllocID);
    if (mCSALargeRectID.IsValid())
        r->Free(mCSALargeRectID.mPageID, mCSALargeRectID.mAllocID);
    if (mCSASmallRectID.IsValid())
        r->Free(mCSASmallRectID.mPageID, mCSASmallRectID.mAllocID);
    if (mCSAAntiAliasRectID.IsValid())
        r->Free(mCSAAntiAliasRectID.mPageID, mCSAAntiAliasRectID.mAllocID);
}

// ---------------------------------------------------------------------------
// @ 0x007bf9c0  setter block (this + 8 stack args, ret 0x20)
// ---------------------------------------------------------------------------
struct RefLike {
    virtual int AddRef();                                      // +0x00
    virtual void Release();                                    // +0x04
};
struct RefVector {
    char pad[0x14];
    void operator=(void* v);                                   // 0x0041ebe0
};
struct Pair { int x, y; };

struct SetterBlock {
    char pad0[0xc];
    void* m0c;                                                 // +0x0c
    void* m10;                                                 // +0x10
    char pad1[0x80];                                           // +0x14..0x93
    Pair  m94;                                                 // +0x94
    Pair  m9c;                                                 // +0x9c
    char pad2[4];                                              // +0xa4
    RefLike* m_a8;                                             // +0xa8
    RefVector m_ac;                                            // +0xac
    int   m_c0;                                                // +0xc0
    unsigned char m_c4;                                        // +0xc4
    float m_c8, m_cc, m_d0, m_d4;                              // +0xc8
    unsigned char m_d8;                                        // +0xd8

    void Set(void* a1, int a2, int a3, int a4, Pair* a5, Pair* a6, int a7, char a8);
};

void SetterBlock::Set(void* a1, int a2, int a3, int a4, Pair* a5, Pair* a6, int a7, char a8)
{
    if (m_c4 == 0) {
        m_c0 = 0;
        RefLike* old = m_a8;
        if (a1 != old) {
            if (a1) ((RefLike*)a1)->AddRef();
            m_a8 = (RefLike*)a1;
            if (old) old->Release();
        }
        m0c = (void*)a3;
        m10 = (void*)a4;
        m94.x = a5->x; m94.y = a5->y;
        m9c.x = a6->x; m9c.y = a6->y;
        m_c0 = a7;
        m_c4 = 1;
        m_c8 = 0.0f; m_cc = 0.0f; m_d0 = 0.0f; m_d4 = 0.0f;
        m_ac = (void*)a2;
        m_d8 = (unsigned char)a8;
    }
}

// ===========================================================================
// CSA photo pipeline: 0x007bedb0 CaptureCSAPhotos, 0x007bf300 SetupCSARTTs,
// 0x007bf720 DispatchCaptureDone.
//
// Class names are Claude-coined placeholders (the retail binary has no RTTI for
// these); field offsets and virtual slots come from the disassembly.  Helper
// objects share the layouts already reconstructed in s007bde20/s007b19c0.
// ===========================================================================
void* __cdecl operator new(size_t size, const char* name, int a, int b, int c, int d);  // 0x00f473a0

struct Vec2f { float x, y; Vec2f(float a, float b) : x(a), y(b) {} };
struct Vec4f { float x, y, z, w; Vec4f(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };
struct ScreenDims { int width, height; };

// @ 0x006a25a0
struct cPropertyList {
    bool GetDescription(unsigned id);
};
extern cPropertyList* gAppProperties;                            // 0x015fd918
extern float g_fVecX;                                            // 0x01635640
extern float g_fVecY;                                            // 0x01635644
extern wchar_t g_emptyString16[];                                // 0x01667bac
extern const wchar_t g_thumbNameFmt[];                           // 0x013f5c04

// RTT manager (this+0x10b4): AllocateRTT +0x10, GetRaster +0x18, RegisterRTT +0x48
struct cRTTManager {
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3();
    virtual RectID AllocateRTT(int w, int h, int fmt, int a, int b, int c);   // +0x10
    virtual void r5();                                                        // +0x14
    virtual void* GetRaster(int page, int alloc);                             // +0x18
    virtual void r7(); virtual void r8(); virtual void r9();
    virtual void r10(); virtual void r11(); virtual void r12(); virtual void r13();
    virtual void r14(); virtual void r15(); virtual void r16(); virtual void r17();
    virtual void RegisterRTT(int page, int alloc, const char* name);          // +0x48
};

// application services (FUN_0067dd50): display dims +0x1c, dispatch +0x78
struct cSporeManager2 {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    virtual ScreenDims* GetDims();                                  // +0x1c, slot 7
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29();
    virtual void Dispatch(void* handle);                            // +0x78, slot 30
};

// renderer (FUN_0067dd40): GetCurrentRenderTarget +0xe4
struct cRenderer {
#define PV(n) virtual void pv##n();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
    PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56)
    virtual void GetCurrentRenderTarget(RectID* out);               // +0xe4, slot 57
#undef PV
};

cSporeManager2* GetSporeManager2();     // 0x0067dd50
cRenderer*      GetRenderer();          // 0x0067dd40
void __cdecl FUN_007bdde0_dummy();      // (unused placeholder; real call is a member below)

// reference-counted bases.  Ref0: AddRef slot 0, Release slot 1.
// Ref1: dummy slot 0, AddRef slot 1, Release slot 2 (message objects).
struct Ref0 { virtual int AddRef(); virtual int Release(); };
struct Ref1 { virtual void rDummy(); virtual int AddRef(); virtual int Release(); };
struct Base2 { virtual void bDummy(); };    // secondary vptr at +4

// event descriptor handed to cFilterChainJob::Queue / job->Queue
struct cThumbJobMsgEvent {
    int a;              // +0x00
    int b;              // +0x04
    bool c;             // +0x08
    int d;              // +0x0c
    int e;              // +0x10
    unsigned id;        // +0x14
    void* data;         // +0x18
    int f, g, h, i;     // +0x1c..+0x28
};

struct WString16 { void* begin; void* end; void* capEnd; };

// chain job (0x10e4/0x10e8/0x10ec): +0x60 chain, +0x78 initialized, +0x90 effect
struct cFilterChainJob : Ref1 {
    char pad04[0x60 - 4];
    cFilterChainJob* mChain;                      // +0x60
    char pad64[0x78 - 0x64];
    bool mInitialized;                            // +0x78
    char pad79[0x90 - 0x79];
    Ref1* mEffect;                                // +0x90
    virtual void f3();                            // +0x0c
    virtual void* BuildHandle(int zero, cThumbJobMsgEvent* ev);   // +0x10
    void Shutdown();                              // 0x007b96d0
    void Reset();                                 // 0x007bdde0
};

// 0x58-byte thumbnail job (vtable 0x140ffb0)
struct cThumbJob : Ref1 {
    int m04;                                      // +0x04
    int m08, m0c, m10, m14, m18, m1c;             // +0x08 rect ids
    int m20, m24, m28;                            // +0x20
    int m2c, m30, m34, m38;                       // +0x2c
    bool m3c;                                     // +0x3c
    char pad3d[3];
    Ref0* m40;                                    // +0x40
    WString16 mName;                              // +0x44
    int m50;                                      // +0x50
    void* m54;                                    // +0x54
    cThumbJob() : m04(0), m08(-1), m0c(-1), m10(-1), m14(-1), m18(-1), m1c(-1),
                  m20(0), m24(0), m28(0), m2c(0), m30(0), m34(0), m38(0), m3c(false),
                  m40(0), m50(0), m54(0)
    { mName.begin = g_emptyString16; mName.end = g_emptyString16; mName.capEnd = g_emptyString16 + 2; }
};

// 0x34-byte effect/chain object (vtable pair 0x140ffe0 / 0x140ffd0)
struct cThumbEffect : Ref0, Base2 {
    virtual void e2(); virtual void e3();
    virtual void* Queue(int zero, cThumbJobMsgEvent* ev);         // +0x10, slot 4
    int m08;                                      // +0x08
    int m0c, m10, m14;                            // +0x0c
    bool m20;                                     // +0x20
    char pad21[3];
    int m24, m28, m2c, m30;                       // +0x24
    cThumbEffect() : m08(0), m0c(0), m10(0), m14(0), m20(false), m24(0), m28(0), m2c(0), m30(0) {}
    void Run(void* req, int w, cThumbJob* job);   // 0x007b2f40
    void Run2(void* req, cThumbJob* job);         // 0x007b31f0
};

// 0x24-byte post-process job (vtable pair 0x140fe1c / 0x140fe0c)
struct cPostJob : Ref0, Base2 {
    virtual void p2(); virtual void p3();
    virtual void* Queue(int zero, cThumbJobMsgEvent* ev);         // +0x10, slot 4
    int m08;                                      // +0x08
    bool m0c;                                     // +0x0c
    char pad0d[3];
    int m10, m14;                                 // +0x10
    int m18, m1c;                                 // +0x18
    int m20;                                      // +0x20
    cPostJob() : m08(0), m0c(false), m10(0), m14(0), m18(0), m1c(0), m20(0) {}
    void Run(void* req, int w, cThumbJob* job);   // 0x007b2f40
};

// 0x1c-byte stage object (vtable pair 0x140fe40 / 0x140fe30)
struct cStage1c : Ref0, Base2 {
    int m08;                                      // +0x08
    bool m0c;                                     // +0x0c
    char pad0d[3];
    int m10, m14, m18;                            // +0x10
    cStage1c() : m08(0), m0c(false), m10(0), m14(0), m18(0) {}
};

// 0x28-byte job (vtable 0x140fdb8)
struct cThumbJob28 : Ref1 {
    int m04, m08, m0c, m10;                       // +0x04
    int m14, m18;                                 // +0x14
    int m1c, m20, m24;                            // +0x1c
    cThumbJob28() : m04(0), m08(0), m0c(0), m10(0), m14(-1), m18(-1), m1c(0), m20(0), m24(0) {}
};

// 0x28/0x30-byte behaviour messages (vtbl 0x13eb90c -> 0x1452a38)
struct cMsg28 : Ref1 {
    volatile long mRef;                           // +0x04
    int m08, m0c, m10, m14;                       // +0x08
    void* m18;                                    // +0x18
    int m1c, m20, m24;                            // +0x1c
    cMsg28() : mRef(0), m08(0), m0c(0), m10(0), m14(0), m18(0), m1c(0), m20(0), m24(0) {}
};
struct cMsg30 : Ref1 {
    volatile long mRef;                           // +0x04
    int m08, m0c, m10, m14, m18, m1c, m20, m24, m28;   // +0x08..+0x28
    cMsg30() : mRef(0), m08(0), m0c(0), m10(0), m14(0), m18(0), m1c(0), m20(0), m24(0), m28(0) {}
};

// @ 0x005766e0
struct cRefList {
    void* Pop(void** out);
};
void __cdecl WStr_Format(void* dst, const wchar_t* fmt, Vec4f v);   // 0x0041e050

// request structures (field offsets straight from the disassembly)
struct CSARequest {
    int m00, m04;
    unsigned m08;        // +0x08 (long dimension, clamped to 1024)
    int m0c;             // +0x0c
    int m10;             // +0x10 notify id
    int m14;             // +0x14 create the post-process chain / takes the next dimension
    int m18, m1c, m20, m24;
    int m28, m2c, m30, m34;   // +0x28 name arguments
};

struct CaptureDoneMsg {
    int m00, m04;
    int m08;             // +0x08 notify id
    int m0c, m10, m14;
    int m18;             // +0x18 status (1 = success, 2 = ...)
    int m1c;
    int m20;             // +0x20 job type (0/1/2)
};

// --- globals declared above with their addresses --------------------------
// 0x0067dd50 / 0x0067dd40 / 0x0067dcc0 are the accessor symbols.
cSporeManager2* GetSporeManager2();     // 0x0067dd50
cRenderer*      GetRenderer();          // 0x0067dd40

// ---------------------------------------------------------------------------
// @ 0x007bedb0  SP::cThumbnailManager::CaptureCSAPhotos(this, req)   (1360 B)
// ---------------------------------------------------------------------------
void cThumbnailManager::CaptureCSAPhotos(CSARequest* req)
{
    unsigned w = req->m08;
    if (w > 0x400u) {
        // clamp: round w up to a multiple of ceil(w / 1024), then divide
        float f = (float)w * 0.0009765625f;
        unsigned step = (unsigned)(int)f;
        if ((float)step < f)
            step++;
        w = (w % step + w) / step;
    }

    ScreenDims* dims = GetSporeManager2()->GetDims();
    float ratio = (float)dims->height / (float)dims->width;
    int h  = (int)((float)w * ratio);
    int w2 = (int)((float)req->m0c * ratio);
    int h2 = req->m0c;

    RectID id = mRTTMgr->AllocateRTT((int)w, h, 0x15, 0, -1, 0);
    mCSALargeRectID = id;
    mRTTMgr->RegisterRTT(id.mPageID, id.mAllocID, "CSALargeRTT");

    id = mRTTMgr->AllocateRTT(w2, h2, 0x15, 0, -1, 0);
    mCSASmallRectID = id;
    mRTTMgr->RegisterRTT(id.mPageID, id.mAllocID, "CSASmallRTT");

    if (gAppProperties->GetDescription(0x5c8af84)) {
        id = mRTTMgr->AllocateRTT(800, 600, 0x15, 0, -1, 0);
        mCSAAntiAliasRectID = id;
        mRTTMgr->RegisterRTT(id.mPageID, id.mAllocID, "CSAAntiAliasRTT");
    }

    cThumbEffect* effect = 0;
    if (req->m14) {
        effect = new ("Graphics", 0, 0, 0, 0) cThumbEffect;
        effect->AddRef();
        if (!effect->m20) {
            effect->m20 = true;
            effect->m28 = 0;
        }
        InitPostProcessEffect(req->m14, effect, false, false,
                              Vec2f(g_fVecX, g_fVecY), 0.0f);
    }

    cPostJob* post = new ("Graphics", 0, 0, 0, 0) cPostJob;
    post->AddRef();

    cThumbJob* job = new ("Graphics", 0, 0, 0, 0) cThumbJob;
    job->AddRef();
    job->m08 = mCSALargeRectID.mPageID;
    job->m0c = mCSALargeRectID.mAllocID;
    job->m10 = mCSASmallRectID.mPageID;
    job->m14 = mCSASmallRectID.mAllocID;
    job->m18 = mCSAAntiAliasRectID.mPageID;
    job->m1c = mCSAAntiAliasRectID.mAllocID;

    if (job->m40 != (Ref0*)post) {
        post->AddRef();
        Ref0* old = job->m40;
        job->m40 = post;
        if (old)
            old->Release();
    }
    job->m20 = (int)w;
    job->m24 = req->m0c;
    job->m28 = 1;
    job->m3c = false;
    job->m2c = req->m18;
    job->m30 = req->m1c;
    job->m38 = req->m24;
    job->m34 = req->m20;

    WStr_Format(&job->mName, g_thumbNameFmt,
                Vec4f((float)req->m28, (float)req->m2c, (float)req->m30, (float)req->m34));

    post->Run(req, (int)w, job);

    cMsg28* msg = new ("Graphics", 0, 0, 0, 0) cMsg28;
    msg->AddRef();
    msg->m08 = req->m10;
    msg->m10 = 2;
    msg->m18 = post;

    cThumbJobMsgEvent ev;
    ev.a = 1; ev.b = 6; ev.c = false; ev.d = 0; ev.e = 0;
    ev.id = 0x1c913db; ev.data = msg;
    ev.f = ev.g = ev.h = ev.i = 0;
    void* handle = post->Queue(0, &ev);
    GetSporeManager2()->Dispatch(handle);

    msg->Release();
    job->Release();
    post->Release();
    if (effect)
        effect->Release();
}

// ---------------------------------------------------------------------------
// @ 0x007bf300  SP::cThumbnailManager::SetupCSARTTs(this, req)   (772 B)
// ---------------------------------------------------------------------------
void cThumbnailManager::SetupCSARTTs(CSARequest* req)
{
    SetupThumbnailRTTs(req->m08, 1);

    cThumbEffect* effect = new ("Graphics", 0, 0, 0, 0) cThumbEffect;
    effect->AddRef();
    if (!effect->m20) {
        effect->m20 = true;
        effect->m28 = 0;
    }
    InitPostProcessEffect(6, effect, true, true, Vec2f(g_fVecX, g_fVecY), 0.0f);

    cStage1c* stage = new ("Graphics", 0, 0, 0, 0) cStage1c;
    stage->AddRef();

    cThumbJob28* job = new ("Graphics", 0, 0, 0, 0) cThumbJob28;
    job->AddRef();

    RectID cur;
    cur.mPageID = -1;
    cur.mAllocID = -1;
    GetRenderer()->GetCurrentRenderTarget(&cur);
    job->m14 = cur.mPageID;
    job->m18 = cur.mAllocID;

    if (job->m24 != (int)(size_t)effect) {
        effect->AddRef();
        int old = job->m24;
        job->m24 = (int)(size_t)effect;
        if (old)
            ((Ref0*)(size_t)old)->Release();
    }
    job->m1c = req->m08;
    job->m20 = req->m08;
    job->m10 = req->m10;
    job->m0c = req->m0c;

    effect->Run2(req, (cThumbJob*)job);

    cMsg28* msg = new ("Graphics", 0, 0, 0, 0) cMsg28;
    msg->AddRef();
    msg->m08 = req->m14;
    msg->m10 = 3;
    msg->m18 = stage;

    cThumbJobMsgEvent ev;
    ev.a = 1; ev.b = req->m18; ev.c = false; ev.d = 0; ev.e = 0;
    ev.id = 0x1c913db; ev.data = msg;
    ev.f = ev.g = ev.h = ev.i = 0;
    void* handle = effect->Queue(0, &ev);
    GetSporeManager2()->Dispatch(handle);

    msg->Release();
    job->Release();
    stage->Release();
    effect->Release();
}

// ---------------------------------------------------------------------------
// @ 0x007bf720  SP::cThumbnailManager::DispatchCaptureDone(this, msg)  (663 B)
// ---------------------------------------------------------------------------
void cThumbnailManager::DispatchCaptureDone(CaptureDoneMsg* msg)
{
    int status   = msg->m18;
    int jobType  = msg->m20;
    int notifyId = msg->m08;

    cFilterChainJob* chain = 0;
    if (jobType == 0)
        chain = mPostFilter0;
    else if (jobType == 1)
        chain = mPostFilter1;
    else if (jobType == 2)
        mPostFilter2->Reset();

    if (chain && chain->mInitialized) {
        if (chain->mChain)
            chain->mChain->Shutdown();
        Ref1* effect = chain->mEffect;
        if (effect) {
            chain->mEffect = 0;
            effect->Release();
        }
        chain->mInitialized = false;
    }

    cMsg30* out = new ("Graphics", 0, 0, 0, 0) cMsg30;
    out->AddRef();
    out->m08 = notifyId;
    out->m10 = 0;
    out->m18 = status;
    out->m28 = 0;

    cThumbJobMsgEvent ev;
    ev.a = 4; ev.b = 0; ev.c = true; ev.d = 0; ev.e = 0;
    ev.id = 0; ev.data = 0;
    ev.f = ev.g = ev.h = ev.i = 0;

    bool posted = false;
    if (status == 1 && jobType == 0) {
        out->m20 = 1;
        chain = mPostFilter1;
        Ref1* old = chain->mEffect;
        if ((Ref1*)out != old) {
            out->AddRef();
            chain->mEffect = out;
            if (old)
                old->Release();
        }
        GetSporeManager2()->Dispatch(chain->BuildHandle(0, &ev));
        posted = true;
    } else if (status == 2) {
        if (jobType == 0) {
            out->m20 = 1;
            chain = mPostFilter1;
            Ref1* old = chain->mEffect;
            if ((Ref1*)out != old) {
                out->AddRef();
                chain->mEffect = out;
                if (old)
                    old->Release();
            }
            GetSporeManager2()->Dispatch(chain->BuildHandle(0, &ev));
            posted = true;
        } else if (jobType == 1) {
            out->m20 = 2;
            cRefList* list = (cRefList*)((char*)mPostFilter2 + 0x90);
            list->Pop((void**)&out);
            GetSporeManager2()->Dispatch(mPostFilter2->BuildHandle(0, &ev));
            posted = true;
        }
    }

    if (!posted)
        SP_MessageServer()->Post(notifyId, 0, 0, 0);

    out->Release();
}

