// Slice s007b7530 - cThumbnailManager post-process job helpers.
//
// 0x007b7530 sets up a thumbnail render-target job (RTT allocation, viewer wrapper,
// image resource and a posted render message); 0x007b77a0 tears the posted job down;
// 0x007b7830 / 0x007b7920 / 0x007b7a20 drive a frame job: bind the job's viewer to a
// raster, draw through the world's layer renderer, fit the result and run the job.
#include "types.h"
#include <intrin.h>

#pragma intrinsic(_InterlockedExchange)

// 6-arg pool allocator (size, arena tag, flags, debug flags, file, line) and the
// matching operator delete.
void* operator new(unsigned int size, const char* arena, int a, int b, int c, int d);  // 0x00f473a0
void operator delete(void* p);                                                          // 0x00f47380

// ---------------------------------------------------------------------------
// viewer and render plumbing
// ---------------------------------------------------------------------------
struct cViewer {
    virtual void AddRef();                                               // vtable +0x00
    virtual void Release();                                              // vtable +0x04
    void SetRaster(const int* handle, bool setViewport);                 // 0x007c4be0
    void Clear(unsigned flags) const;                                    // 0x007c3c50
    void SetRenderType(int type, int flags);                             // 0x007c3ce0
    void Shutdown();                                                     // 0x007c3ba0
    ~cViewer();                                                          // 0x007c4000
    bool Copy(const cViewer* src, bool a, bool b);                       // 0x007c50b0
};

struct DrawRect {                                                        // {viewer, 0, 0, 0}
    cViewer* viewer;
    int a, b, c;
};

struct ILayerDraw {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void Draw(int a, int b, const DrawRect* rect, int d);        // +0x0c
};

struct IModelWorld {
    virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
    virtual void w04(); virtual void w05(); virtual void w06(); virtual void w07();
    virtual void w08(); virtual void w09(); virtual void w10(); virtual void w11();
    virtual void w12(); virtual void w13(); virtual void w14(); virtual void w15();
    virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23();
    virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27();
    virtual void w28(); virtual void w29(); virtual void w30(); virtual void w31();
    virtual void w32(); virtual void w33(); virtual void w34(); virtual void w35();
    virtual void w36(); virtual void w37(); virtual void w38(); virtual void w39();
    virtual void w40(); virtual void w41(); virtual void w42(); virtual void w43();
    virtual void w44(); virtual void w45(); virtual void w46(); virtual void w47();
    virtual void w48(); virtual void w49(); virtual void w50(); virtual void w51();
    virtual void w52(); virtual void w53(); virtual void w54(); virtual void w55();
    virtual void w56(); virtual void w57(); virtual void w58(); virtual void w59();
    virtual void w60(); virtual void w61(); virtual void w62(); virtual void w63();
    virtual void w64(); virtual void w65(); virtual void w66(); virtual void w67();
    virtual void w68(); virtual void w69(); virtual void w70(); virtual void w71();
    virtual void w72(); virtual void w73(); virtual void w74(); virtual void w75();
    virtual void w76(); virtual void w77(); virtual void w78();
    virtual ILayerDraw* GetLayerDraw();                                  // +0x13c
};

struct ItemList {
    char pad0[0x0c];
    void** begin;                                                        // +0x0c
    void** end;                                                          // +0x10
    void Fn(int a, int b, const DrawRect* rect, int d);                  // 0x007b49f0
};

struct FrameScene {                                                      // render-target context
    char pad00[0x08];
    int raster[2];                                                       // +0x08
    ItemList* items;                                                     // +0x10
    char pad14[0x14];                                                    // +0x14
    bool secondPass;                                                     // +0x28
    char pad29[3];
    int field2c;                                                         // +0x2c
};

void SetShaderData(int id, unsigned value, int flag);                    // 0x00777ae0

// A frame job: viewer + world renderer, the job's own raster handle, the captured
// RGBA image and the scene/context record.
struct FrameJob {
    char pad00[0x10];
    IModelWorld* world;                                                  // +0x10
    cViewer* viewer;                                                     // +0x14
    int raster[2];                                                       // +0x18
    char pad20[4];
    int h;                                                               // +0x24
    int w;                                                               // +0x28
    unsigned char* data;                                                 // +0x2c
    FrameScene* scene;                                                   // +0x30
    void Fit();                                                          // 0x007b5e20
    void FitAspect();                                                    // 0x007b6160
    void RunA();                                                         // 0x007b6010
    void FinishRender();                                                 // 0x007b2e10
    void RunTiles(int a, int b, int unused, int d);
    void RunAspect(int a, int b, int unused, int d);
};

// 0x007b7a20's job keeps the context in a pointer at +0x18 (raster at +0x14,
// item list at +0x24).
struct FrameCtxB {
    char pad00[0x14];
    int raster[2];                                                       // +0x14
    char pad1c[8];
    ItemList* items;                                                     // +0x24
};

struct FrameJobB {
    char pad00[0x10];
    IModelWorld* world;                                                  // +0x10
    cViewer* viewer;                                                     // +0x14
    FrameCtxB* ctx;                                                      // +0x18
    void RunB();                                                         // 0x007b63b0
    void RunCopy(int a, int b, cViewer** src, int d);
};

// @ 0x007b7830
void FrameJob::RunTiles(int a, int b, int unused, int d) {
    (void)unused;
    viewer->SetRaster(scene->raster, true);
    viewer->Clear(7);
    if (scene->field2c == 9)
        viewer->SetRenderType(0xf, 0);
    DrawRect rect;
    rect.viewer = viewer;
    rect.a = 0;
    rect.b = 0;
    rect.c = 0;
    world->GetLayerDraw()->Draw(a, b, &rect, d);
    if (scene->secondPass) {
        viewer->SetRaster(raster, true);
        viewer->Clear(7);
        world->GetLayerDraw()->Draw(a, b, &rect, d);
        Fit();
    }
    scene->items->Fn(a, b, &rect, d);
    RunA();
}

// @ 0x007b7920
void FrameJob::RunAspect(int a, int b, int unused, int d) {
    (void)unused;
    unsigned saved = *(volatile unsigned*)0x016f6e34;
    SetShaderData(0x223, 0, 1);
    viewer->SetRaster(scene->raster, true);
    viewer->Clear(7);
    DrawRect rect;
    rect.viewer = viewer;
    rect.a = 0;
    rect.b = 0;
    rect.c = 0;
    world->GetLayerDraw()->Draw(a, b, &rect, d);
    viewer->SetRaster(raster, true);
    viewer->Clear(7);
    world->GetLayerDraw()->Draw(a, b, &rect, d);
    FitAspect();
    scene->items->Fn(a, b, &rect, d);
    SetShaderData(0x223, saved, 1);
    FinishRender();
}

// @ 0x007b7a20
void FrameJobB::RunCopy(int a, int b, cViewer** src, int d) {
    viewer->Copy(*src, false, false);
    viewer->SetRaster(ctx->raster, true);
    viewer->Clear(7);
    DrawRect rect;
    rect.viewer = viewer;
    rect.a = 0;
    rect.b = 0;
    rect.c = 0;
    world->GetLayerDraw()->Draw(a, b, &rect, d);
    ctx->items->Fn(a, b, &rect, d);
    RunB();
}

// ---------------------------------------------------------------------------
// 0x007b77a0: finish/tear down the posted render job.
// ---------------------------------------------------------------------------
struct PostedJob {
    char pad00[0x0c];
    bool bound;                                                          // +0x0c
    cViewer* viewer;                                                     // +0x10
    void* owner;                                                         // +0x14
};

struct RefHolder {
    char pad0[8];
    void* obj;                                                           // +0x08
};
void __fastcall RefHolder_Reset(RefHolder* h);                           // 0x007b64f0

struct JobFinishArg {
    char pad00[8];
    PostedJob* job;                                                      // +0x08
    int pad0c;
    int messageId;                                                       // +0x10
};

struct IPostSink {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual void p3();
    virtual void p4();
    virtual void Finish(int a, int b);                                   // +0x14
};
IPostSink* GetPostSink();                                                // 0x0067dda0

struct IMsgServer {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void PostMessage(int id, void* payload, int zero);           // +0x14
};
IMsgServer* MessageServer();                                             // 0x0067dcc0

struct JobTail {
    char pad00[0x14];
    int f14;                                                             // +0x14
    int f18;                                                             // +0x18
    void Finish(JobFinishArg* arg);
};

// @ 0x007b77a0
void JobTail::Finish(JobFinishArg* arg) {
    PostedJob* job = arg->job;
    if (job->bound) {
        if (job->viewer) {
            job->viewer->Shutdown();
            delete job->viewer;
            job->viewer = 0;
        }
        if (job->owner)
            RefHolder_Reset((RefHolder*)job->owner);
        job->bound = false;
    }
    IPostSink* sink = GetPostSink();
    if (f18 != -1)
        sink->Finish(f14, f18);
    int messageId = arg->messageId;
    MessageServer()->PostMessage(messageId, 0, 0);
}

// ---------------------------------------------------------------------------
// 0x007b7530: allocate the thumbnail RTT + viewer wrapper and post the render job.
// ---------------------------------------------------------------------------
struct ViewerHolder;

struct ImageRef {
    void* p;                                                             // +0x00
    void Set(int image);                                                 // 0x00576650
};

struct ViewerHolder {
    virtual void d0();
    virtual void AddRef();                                               // vtable +0x04
    virtual void Release();                                              // vtable +0x08
    int f04;                                                             // +0x04
    ImageRef image;                                                      // +0x08
    cViewer* viewer;                                                     // +0x0c
    int f10;                                                             // +0x10
    int f14;                                                             // +0x14
    ViewerHolder() : f04(0) {
        image.p = 0;
        viewer = 0;
    }
};

struct JobInfoBase {
    virtual void AddRef();                                               // +0x00
    virtual void Release();                                              // +0x04
    virtual void b2();
    virtual void b3();
    virtual int* Build(int zero, void* msg);                             // +0x10
};
struct JobInfoCVS {
    virtual void cv0();
    int cv4;                                                             // +0x08
    JobInfoCVS() { cv4 = 0; }
};
struct JobInfo : JobInfoBase, JobInfoCVS {                               // 0x1c, "Graphics" heap
    bool bound;                                                          // +0x0c
    cViewer* viewer;                                                     // +0x10
    ViewerHolder* owner;                                                 // +0x14
    int arg18;                                                           // +0x18
    JobInfo() {
        bound = false;
        viewer = 0;
        owner = 0;
        arg18 = 0;
    }
    void AttachViewer(ViewerHolder* holder);                             // 0x007b3760
};

struct RenderMsgBase {
    virtual void d0();
    virtual void AddRef();                                               // vtable +0x04
    virtual void Release();                                              // vtable +0x08
    volatile long refs;                                                  // +0x04
    RenderMsgBase() { _InterlockedExchange(&refs, 0); }
};
struct RenderMsg : RenderMsgBase {                                       // 0x20, "Graphics" heap
    JobInfo* job;                                                        // +0x08
    int f0c;
    int arg10;                                                           // +0x10
    int f14;
    int arg18;                                                           // +0x18
    int pad1c;
    RenderMsg() : arg18(0) {}
};

struct MsgBuf {
    int a;                                                               // +0x00
    int b;                                                               // +0x04
    char flag;                                                           // +0x08
    int d;                                                               // +0x0c
    int e;                                                               // +0x10
    int tag;                                                             // +0x14
    RenderMsg* msg;                                                      // +0x18
    int g, h, i, j;                                                      // +0x1c
};

struct RtOut {                                                           // RTT allocation result
    int a, b, c;
};

struct IRtManager {
    virtual void r0();
    virtual void r1();
    virtual void r2();
    virtual void r3();
    virtual RtOut* GetRtt(RtOut* out, int key, int key2, int kind,
                          int a, int b, int c);                          // +0x10
    virtual void r5();
    virtual cViewer* GetViewer(int a, int b);                            // +0x18
    virtual void r7(); virtual void r8(); virtual void r9(); virtual void r10();
    virtual void r11(); virtual void r12(); virtual void r13(); virtual void r14();
    virtual void r15(); virtual void r16(); virtual void r17();
    virtual void SetRttName(int a, int b, const char* name);             // +0x48
};

struct IMsgSink {
    char pad[0x78];
    virtual void Post(void* msg);                                        // +0x78
};
IMsgSink* GetMsgSink();                                                  // 0x0067dd50

struct ThumbnailManager {
    char pad00[0x10];
    cViewer* viewer;                                                     // +0x10
    int rttA;                                                            // +0x14
    int rttB;                                                            // +0x18
    char pad1c[0x10b4 - 0x1c];
    IRtManager* rtManager;                                               // +0x10b4
    void Setup(void* arg);
};

struct SetupArg {
    char pad00[8];
    int imageId;                                                         // +0x08
    int key;                                                             // +0x0c
    cViewer* srcViewer;                                                  // +0x10
    int image;                                                           // +0x14
    int targetId;                                                        // +0x18
};

template <class T> struct SmartP {
    T* mp;
    SmartP(T* p) { mp = p; if (mp) mp->AddRef(); }
    ~SmartP() { if (mp) mp->Release(); }
    T* operator->() const { return mp; }
    operator T*() const { return mp; }
};

// @ 0x007b7530
void ThumbnailManager::Setup(void* arg_) {
    SetupArg* arg = (SetupArg*)arg_;
    SmartP<JobInfo> job(new ("Graphics", 0, 0, 0, 0) JobInfo);
    JobInfo* pJob = job;

    RtOut out;
    RtOut* rtt = rtManager->GetRtt(&out, arg->key, arg->key, 0x15, 0, -1, 0);
    rttA = rtt->a;
    rttB = rtt->b;
    rtManager->SetRttName(rtt->a, rtt->b, "ThumbnailRTT");
    viewer = rtManager->GetViewer(rttA, rttB);

    SmartP<ViewerHolder> holder(new ("Graphics", 0, 0, 0, 0) ViewerHolder);
    cViewer* oldViewer = holder->viewer;
    cViewer* src = arg->srcViewer;
    if (src != oldViewer) {
        if (src)
            src->AddRef();
        holder->viewer = src;
        if (oldViewer)
            oldViewer->Release();
    }
    holder->image.Set(arg->image);
    holder->f10 = arg->imageId;
    holder->f14 = arg->key;
    pJob->AttachViewer(holder);

    SmartP<RenderMsg> msg(new ("Graphics", 0, 0, 0, 0) RenderMsg);
    msg->job = pJob;
    msg->arg10 = arg->targetId;

    MsgBuf buf;
    buf.a = 1;
    buf.b = 0;
    buf.flag = 1;
    buf.d = 0;
    buf.e = 0;
    buf.tag = 0;
    buf.msg = 0;
    buf.g = buf.h = buf.i = buf.j = 0;
    buf.flag = 0;
    buf.msg = msg;
    buf.tag = 0x7b240a0;

    IMsgSink* sink = GetMsgSink();
    sink->Post(pJob->Build(0, &buf));
}
