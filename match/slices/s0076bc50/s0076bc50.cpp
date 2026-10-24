// Slice s0076bc50 (batch w2g3, slice 37).
// SP::cRTTCapture: render-to-texture capture manager used by the editor/effects code.
// Layout below is the retail one recovered from the ctor (0076c660) and dtor (0076c710);
// the dev-PDB header in src/game/include/SP/cRTTCapture.h stops at mSceneViewJobs and is
// therefore not used. Default flags region (/O2 /MD /Gy /EHsc /TP).
#include "types.h"
#include <xmmintrin.h>

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

// A three-pointer eastl vector whose end/capacity pointers carry a low tag bit.
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
    cRenderTargetRectID mCubemapFaceRectID;   // +0x0c
    void*               mCubeViewers[6];      // +0x14
    void*               mImpostorViewers[6];  // +0x2c
    float               mSunDir[3];           // +0x44
    unsigned            mCurrentCubemapRes;   // +0x50
    bool                mOutCoeffs;           // +0x54
    char                pad55[3];
    char*               mCoeffFilename;       // +0x58
    bool                mBrightenDir;         // +0x5c
    bool                mGenerateSH;          // +0x5d
    char                pad5e[2];
    unsigned            mCubeCaptureMessage;  // +0x60
    void*               mSnapshotViewer;      // +0x64
    bool                mJobInProgress;       // +0x68
    char                pad69[3];
    void*               mRTTMgr;              // +0x6c
    void*               mGraphicsSystem;      // +0x70
    cRenderTargetRectID mTempSnapRectID;      // +0x74
    int                 mTempSnapRegistered;  // +0x7c
    void*               mTempSnapZRaster;     // +0x80  refcounted viewer/raster
    unsigned            mTempSnapResolution;  // +0x84
    void*               mOwnedBlock;          // +0x88  heap block with a 4-byte header
    void*               mField8c;             // +0x8c
    void*               mField90;             // +0x90
    char                pad94[8];             // +0x94
    OwnedRefObj*        mEffectsListener;     // +0x9c
    SpVec               mSceneViewJobs;       // +0xa0
    bool                mResetDone;           // +0xb0
    char                padb1[3];

    cRTTCapture();
    ~cRTTCapture();

    // @ 0x0076bc50  Snapshot/cubemap capture job (7 dwords, mixed inlined EASTL setup).
    bool TakeSnapshot(void* view, int res2, int res, int cube, unsigned flags,
                      unsigned p7, unsigned genSH);
    // @ 0x0076c210  Message-driven capture entry (1 arg).
    bool HandleCaptureMessage(void* payload);
    // @ 0x0076c7c0  IHandlerRC::HandleMessage (ecx = IHandlerRC subobject, i.e. capture+8).
    bool HandleMessage(int msgId, void* payload);
};

extern char gEmptySpVec;   // 0x01667bac shared empty buffer

// ------------------------------------------------------------------ callees
// The raw-address declarations are resolved by the trailing address comment.
// __fastcall(self, dummy, ...) gives ecx = self, edx = don't-care and the remaining
// arguments on the stack, which is the __thiscall shape of the original callees.
int  __fastcall ResetRefs76bs(void* self, int);                         // 0x76b5d0
int  __fastcall ReleaseViewer76b8(void* self, int);                     // 0x76b840
int  __fastcall RefreshCubeMap(void* self, int, int index);             // 0x76b240
int  __fastcall TakeCubeMap76ba(void* self, int, int a1, void* a2,     // 0x76ba30
                                int a3, int a4, int a5, int a6, int a7,
                                void* a8, int a9, void* a10, int a11,
                                int a12);
int  __fastcall RasterLock(void* self, int, unsigned flags, int a, int* out); // 0x11ef750
int  __fastcall RasterUnlock(void* self, int, int* out);                // 0x11ef880
extern "C" {
void* __cdecl MessageServer(void);                                     // 0x67dcc0
void* __cdecl EffectsManager(void);                                    // 0x67ddd0
void* __cdecl App67dda0(void);                                         // 0x67dda0
void  __cdecl FUN_00761110(void* p);                                   // 0x761110
void* __cdecl CreateRaster(int a, int b, int c, int d, int e);         // 0x761420
void* __cdecl App6740(void);                                           // 0x67dd40
void* __cdecl App6750(void);                                           // 0x67dd50
void* __cdecl App(void);                                               // 0x67dd10
void* __cdecl Alloc6(unsigned size, const char* tag, int, int, int, int); // 0xf473a0
}

void* __fastcall Ctor76b350(void* self, int);                          // 0x76b350
void* __fastcall Ctor760c00(void* self, int);                          // 0x760c00
int   __fastcall FUN_00760fd0(void* self, int, int a, int type, int b); // 0x760fd0
void  __fastcall Ctor76b460(void* self, int, void* rect, void* o1, void* o2,
                            void* o3, int res, int scaled, int view, int cube,
                            int tiled, int tiles, int res80);           // 0x76b460
int   __fastcall CopyFrom76b8(void* self, int, void* other);            // 0x7c5240
int   __fastcall FUN_7c4b50(void* self, int, float scale);              // 0x7c4b50
int   __fastcall SetClearColor76c3(void* self, int, const void* color); // 0x7c3c20

typedef int   (__thiscall *FnI0)(void*);
typedef int   (__thiscall *FnI1)(void*, int);
typedef int   (__thiscall *FnI2)(void*, int, int);
typedef int   (__thiscall *FnI3)(void*, int, int, int*);
typedef void* (__thiscall *FnP0)(void*);
typedef void* (__thiscall *FnP1)(void*, int);
typedef void* (__thiscall *FnP2)(void*, int, int);
typedef void* (__thiscall *FnPp)(void*, void*);
typedef int*  (__thiscall *FnItem)(void*, int);
typedef void* (__thiscall *FnSend)(void*, void*, int, void*);
typedef void* (__thiscall *FnRT)(void*, cRenderTargetRectID*, int, int, int,
                                 int, int, int);
typedef void* (__thiscall *FnS3)(void*, int, int, const char*);

// 0x20-byte refcounted driver block (vtable, refcount, payload slots).
struct DriveObj {
    void* mVtbl;      // +0x00
    int   mRefCount;  // +0x04
    int   mField08;   // +0x08
    int   mField0C;   // +0x0c
    int   mField10;   // +0x10
    int   mField14;   // +0x14
    int   mField18;   // +0x18
    int   mField1C;   // +0x1c
};
struct Color4 { float r, g, b, a; };
// Capture-completion message posted to the render-target manager.
struct SnapshotMsg {
    int   mField00;   // +0x00
    int   mField04;   // +0x04
    char  mField08;   // +0x08
    char  mPad09[3];
    int   mField0C;   // +0x0c
    int   mField10;   // +0x10
    int   mMsgID;     // +0x14
    void* mJob;       // +0x18
    void* mViewer;    // +0x1c
    int   mField20;   // +0x20
    int   mField24;   // +0x24
    int   mField28;   // +0x28
};

cRTTCapture::cRTTCapture()
    : mCubemapFaceRectID(), mOutCoeffs(false),
      mCoeffFilename(0), mBrightenDir(false), mGenerateSH(false),
      mCubeCaptureMessage(0), mSnapshotViewer(0), mJobInProgress(false),
      mRTTMgr(0), mGraphicsSystem(0),
      mTempSnapRectID(), mTempSnapRegistered(0), mTempSnapZRaster(0),
      mTempSnapResolution(0), mOwnedBlock(0), mField8c(0), mField90(0),
      mEffectsListener(0), mResetDone(true)
{
    mCubemapFaceRectID.mPageID = -1;
    mCubemapFaceRectID.mAllocID = -1;
    mTempSnapRectID.mPageID = -1;
    mTempSnapRectID.mAllocID = -1;
    mSceneViewJobs.mBegin = &gEmptySpVec;
    mSceneViewJobs.mEnd = &gEmptySpVec;
    mSceneViewJobs.mCapacity = &gEmptySpVec + 1;
}

cRTTCapture::~cRTTCapture()
{
    // mSceneViewJobs (three-pointer vector with a shared empty sentinel)
    {
        int n = (int)((char*)mSceneViewJobs.mCapacity - (char*)mSceneViewJobs.mBegin);
        if (n > 1 && mSceneViewJobs.mBegin != 0)
            Deallocate(mSceneViewJobs.mBegin);
    }
    if (mEffectsListener)
        mEffectsListener->Release();
    if (mOwnedBlock && *(int*)((char*)mOwnedBlock - 4) != 0)
        Deallocate(mOwnedBlock);
    if (mTempSnapZRaster)
        ((OwnedRefObj*)mTempSnapZRaster)->Release();
}

// @ 0x0076bc50
bool cRTTCapture::TakeSnapshot(void* view, int res2, int res, int cube,
                               unsigned flags, unsigned p7, unsigned genSH)
{
    void* appCheck = App6740();
    if ((unsigned char)((FnI0)(*(void***)appCheck)[0x3c / 4])(appCheck))
        return false;

    // Replace the stored temp-snapshot raster (0x140-byte D350 object).
    {
        void* raw = Alloc6(0x140, "Graphics", 0, 0, 0, 0);
        void* nw = raw ? Ctor76b350(raw, 0) : 0;
        void* old = mTempSnapZRaster;
        if (nw != old) {
            if (nw)
                ((FnP0)(*(void***)nw)[0])(nw);
            mTempSnapZRaster = nw;
            if (old)
                ((FnP0)(*(void***)old)[1])(old);
        }
    }

    mTempSnapResolution = (unsigned)res2;

    cRenderTargetRectID rect;
    rect.mPageID = -1;
    rect.mAllocID = -1;
    int res80 = (res == 0x80);

    void* p = App6750();
    int* dims = (int*)((FnP0)(*(void***)p)[0x1c / 4])(p);
    int w = dims[0];
    int h = dims[1];
    if (res < w)
        res = w;
    float scale = (float)w / (float)h;
    float invScale = 1.0f / scale;
    int half = (int)_mm_cvtss_si32(_mm_set_ss((float)(unsigned)res * invScale));

    int tiles = 1;
    char tiled = 0;
    if (genSH == 0 && res == w) {
        void* gfx = mGraphicsSystem;
        ((FnP0)(*(void***)gfx)[0x88 / 4])(gfx);
        ((FnPp)(*(void***)gfx)[0xcc / 4])(gfx, &rect);
    } else {
        tiled = 1;
        if (w < res) {
            tiles = (w - 1 + res) / w;
            res = w * tiles;
        }
        void* rtt = App67dda0();
        cRenderTargetRectID out;
        cRenderTargetRectID* rid = (cRenderTargetRectID*)
            ((FnRT)(*(void***)rtt)[0x10 / 4])(rtt, &out, res / tiles,
                                              half / tiles, 0x15, 0, -1, 0);
        int page = rid->mPageID;
        int alloc = rid->mAllocID;
        ((FnS3)(*(void***)rtt)[0x48 / 4])(rtt, page, alloc, "TempSnapshot");
        if (alloc != -1) {
            void* reg = ((FnP2)(*(void***)rtt)[0x18 / 4])(rtt, page, alloc);
            mTempSnapRegistered = (int)reg;
            mTempSnapRectID.mPageID = page;
            mTempSnapRectID.mAllocID = alloc;
        }
        rect.mPageID = mTempSnapRectID.mPageID;
        rect.mAllocID = mTempSnapRectID.mAllocID;
    }

    void* mgr = App6750();

    // Three helper objects dispatched by scene-view item type.
    void* o1;
    {
        void* raw = Alloc6(0x20, "Graphics", 0, 0, 0, 0);
        o1 = raw ? Ctor760c00(raw, 0) : 0;
    }
    if (o1)
        ((FnP0)(*(void***)o1)[0])(o1);
    void* o2;
    {
        void* raw = Alloc6(0x20, "Graphics", 0, 0, 0, 0);
        o2 = raw ? Ctor760c00(raw, 0) : 0;
    }
    if (o2)
        ((FnP0)(*(void***)o2)[0])(o2);
    void* o3;
    {
        void* raw = Alloc6(0x20, "Graphics", 0, 0, 0, 0);
        o3 = raw ? Ctor760c00(raw, 0) : 0;
    }
    if (o3)
        ((FnP0)(*(void***)o3)[0])(o3);

    {
        void* app = App();
        void* src = ((FnP0)(*(void***)app)[0x50 / 4])(app);
        src = ((FnP0)(*(void***)src)[0x1c / 4])(src);
        CopyFrom76b8(mSnapshotViewer, 0, src);
    }
    *(char*)((char*)mSnapshotViewer + 0x16c) = 1;
    FUN_7c4b50(mSnapshotViewer, 0, scale);
    Color4 color = { 0.0f, 0.0f, 0.0f, 0.0f };
    SetClearColor76c3(mSnapshotViewer, 0, &color);

    int count = ((FnI0)(*(void***)mgr)[0x68 / 4])(mgr);
    int threshold = flags ? 0x20 : 0x1a;
    for (int i = 0; i < count; ++i) {
        int* item = (int*)((FnItem)(*(void***)mgr)[0x70 / 4])(mgr, i);
        int type = item[1];
        if (type == 1)
            continue;
        if (type < 8)
            FUN_00760fd0(o1, 0, item[0], type, item[2]);
        else if (type == 8)
            FUN_00760fd0(o2, 0, item[0], 8, item[2]);
        else if ((unsigned)type <= (unsigned)threshold)
            FUN_00760fd0(o3, 0, item[0], type, item[2]);
    }

    int scaled = (int)_mm_cvtss_si32(_mm_set_ss((float)(unsigned)res * invScale));
    Ctor76b460(mTempSnapZRaster, 0, &rect, o1, o2, o3, res, scaled,
               (int)(size_t)view, cube, tiled, tiles, res80);

    // Completion job object posted with the message below.
    void* job = 0;
    {
        void* raw = Alloc6(0x18, "Graphics", 0, 0, 0, 0);
        if (raw) {
            DriveObj* j = (DriveObj*)raw;
            j->mField10 = 0;
            j->mVtbl = (void*)0x13eb90c;
            j->mRefCount = 0;
            j->mVtbl = (void*)0x1452a38;
            job = raw;
        }
    }
    if (job)
        ((FnP0)(*(void***)job)[1])(job);
    ((DriveObj*)job)->mField08 = (int)(unsigned char)p7;

    SnapshotMsg msg;
    msg.mField00 = 1;
    msg.mField04 = 0;
    msg.mField08 = 0;
    msg.mField0C = 0;
    msg.mField10 = 0;
    msg.mMsgID = 0x1c91267;
    msg.mJob = job;
    msg.mViewer = mSnapshotViewer;
    msg.mField20 = 0;
    msg.mField24 = 0;
    msg.mField28 = 0;
    ((FnSend)(*(void***)mgr)[0x78 / 4])(mgr, mTempSnapZRaster, 0, &msg);
    ((FnP1)(*(void***)mGraphicsSystem)[0x48 / 4])(mGraphicsSystem, 1);

    if (job)
        ((FnP0)(*(void***)job)[2])(job);
    if (o3)
        ((FnP0)(*(void***)o3)[1])(o3);
    if (o2)
        ((FnP0)(*(void***)o2)[1])(o2);
    if (o1)
        ((FnP0)(*(void***)o1)[1])(o1);
    return true;
}

// @ 0x0076c210
bool cRTTCapture::HandleCaptureMessage(void* payload)
{
    void* appCheck = App6740();
    if ((unsigned char)((FnI0)(*(void***)appCheck)[0x3c / 4])(appCheck)) {
        void* ms = MessageServer();
        ((FnI3)(*(void***)ms)[0x14 / 4])(ms, (int)payload, 0, 0);
        return false;
    }

    // One-shot capture raster (0x140-byte D350 object).
    void* raster;
    {
        void* raw = Alloc6(0x140, "Graphics", 0, 0, 0, 0);
        raster = raw ? Ctor76b350(raw, 0) : 0;
    }
    if (raster)
        ((FnP0)(*(void***)raster)[0])(raster);

    cRenderTargetRectID rect;
    rect.mPageID = -1;
    rect.mAllocID = -1;

    void* gfx = mGraphicsSystem;
    ((FnP0)(*(void***)gfx)[0x88 / 4])(gfx);
    ((FnPp)(*(void***)gfx)[0xcc / 4])(gfx, &rect);

    void* mgr = App6750();

    // Completion job object (vtable + refcount set up inline).
    DriveObj* job = (DriveObj*)Alloc6(0x20, "Graphics", 0, 0, 0, 0);
    if (job) {
        job->mField18 = 0;
        job->mVtbl = (void*)0x13eb90c;
        job->mRefCount = 0;
        job->mVtbl = (void*)0x1452a38;
    }
    if (job)
        ((FnP0)(*(void***)job)[1])(job);
    job->mField08 = (int)payload;

    // Three helper objects dispatched by scene-view item type.
    void* oA;
    {
        void* raw = Alloc6(0x20, "Graphics", 0, 0, 0, 0);
        oA = raw ? Ctor760c00(raw, 0) : 0;
    }
    if (oA)
        ((FnP0)(*(void***)oA)[0])(oA);
    void* oB;
    {
        void* raw = Alloc6(0x20, "Graphics", 0, 0, 0, 0);
        oB = raw ? Ctor760c00(raw, 0) : 0;
    }
    if (oB)
        ((FnP0)(*(void***)oB)[0])(oB);
    void* oC;
    {
        void* raw = Alloc6(0x20, "Graphics", 0, 0, 0, 0);
        oC = raw ? Ctor760c00(raw, 0) : 0;
    }
    if (oC)
        ((FnP0)(*(void***)oC)[0])(oC);

    {
        void* app = App();
        void* src = ((FnP0)(*(void***)app)[0x50 / 4])(app);
        src = ((FnP0)(*(void***)src)[0x1c / 4])(src);
        CopyFrom76b8(mSnapshotViewer, 0, src);
    }
    Color4 color = { 0.0f, 0.0f, 0.0f, 0.0f };
    SetClearColor76c3(mSnapshotViewer, 0, &color);

    int count = ((FnI0)(*(void***)mgr)[0x68 / 4])(mgr);
    for (int i = 0; i < count; ++i) {
        int* item = (int*)((FnItem)(*(void***)mgr)[0x70 / 4])(mgr, i);
        int type = item[1];
        if (type < 8)
            FUN_00760fd0(oA, 0, item[0], type, item[2]);
        else if (type == 8)
            FUN_00760fd0(oB, 0, item[0], 8, item[2]);
        else if ((unsigned)type <= 0x1a)
            FUN_00760fd0(oC, 0, item[0], type, item[2]);
    }

    Ctor76b460(raster, 0, &rect, oA, oB, oC, 0, 0, 0, 0, 0, 2, 0);
    job->mField10 = (int)raster;

    SnapshotMsg msg;
    msg.mField00 = 1;
    msg.mField04 = 0;
    msg.mField08 = 0;
    msg.mField0C = 0;
    msg.mField10 = 0;
    msg.mMsgID = 0x3ea7e1b;
    msg.mJob = job;
    msg.mViewer = mSnapshotViewer;
    msg.mField20 = 0;
    msg.mField24 = 0;
    msg.mField28 = 0;
    ((FnSend)(*(void***)mgr)[0x78 / 4])(mgr, raster, 0, &msg);
    ((FnP1)(*(void***)mGraphicsSystem)[0x48 / 4])(mGraphicsSystem, 1);

    if (oC)
        ((FnP0)(*(void***)oC)[1])(oC);
    if (oB)
        ((FnP0)(*(void***)oB)[1])(oB);
    if (oA)
        ((FnP0)(*(void***)oA)[1])(oA);
    if (job)
        ((FnP0)(*(void***)job)[2])(job);
    if (raster)
        ((FnP0)(*(void***)raster)[1])(raster);
    return true;
}

// @ 0x0076c7c0
// ecx is the IHandlerRC subobject (capture + 8), so every field below is addressed
// relative to that subobject. MSVC compiles this override of IHandlerRC::HandleMessage
// with `this` already folded to the complete object (ecx - 8 here), so re-add the
// subobject offset: m = capture + 8, cap = m - 8 = capture.
bool cRTTCapture::HandleMessage(int msgId, void* payload)
{
    char* m = (char*)this + 8;
    char* p = (char*)payload;
    cRTTCapture* cap = (cRTTCapture*)(m - 8);

    if (msgId == 0x1c7f3db) {
        int cube  = *(int*)(p + 0x20);
        int view  = *(int*)(p + 8);
        int res   = *(int*)(p + 0x10);
        int arg2  = *(int*)(p + 0x18);
        if (cube == 0)
            *(char*)(m + 0xa8) = 0;
        // The compiler materialises the trailing bool by overwriting the low byte of the
        // payload stack slot, which is then passed as the 5th argument.
        unsigned flag = ((unsigned)(size_t)payload & 0xFFFFFF00u)
                      | (*(int*)(p + 0x28) == 1 ? 1u : 0u);
        if (view != 0) {
            cap->TakeSnapshot((void*)view, arg2, res, cube, flag, 0, 1);
            return true;
        }
        cap->TakeSnapshot(0, 0, 0, 0, 0, 0, 1);
        return true;
    }

    if (msgId == 0x1c7f90a) {
        int a1 = *(int*)(p + 8);
        void* a2 = *(void**)(p + 0x10);
        int a6 = *(int*)(p + 0x18) == 1;
        int a7 = *(int*)(p + 0x20) == 1;
        int a8 = *(int*)(p + 0x28) == 1;
        void* a9 = *(void**)(p + 0x30);
        int a10 = *(int*)(p + 0x38) == 1;
        void* a11 = *(void**)(p + 0x40);
        int a12 = *(int*)(p + 0x48) == 1;
        int a3 = *(int*)(p + 0x50) == 1;
        unsigned last = ((unsigned)(size_t)payload & 0xFFFFFF00u)
                      | (*(int*)(p + 0x58) == 1 ? 1u : 0u);
        TakeCubeMap76ba(cap, 0, a1, a2, a3, 0, a6, a7, a8, a9, a10, a11, a12, (int)last);
        return true;
    }

    if (msgId == 0x1c91267) {
        if (*(char*)(m + 0xa8) == 0) {
            void* o = *(void**)(m + 0x68);
            ((FnI1)(*(void***)o)[0x48 / 4])(o, 0);
            ResetRefs76bs(*(void**)(m + 0x78), 0);
            void* r = *(void**)(m + 0x78);
            if (r) {
                *(void**)(m + 0x78) = 0;
                ((FnI0)(*(void***)r)[1])(r);
            }
            void* ms = MessageServer();
            int id = *(int*)(m + 0x7c);
            if (id != 0 && ms != 0)
                ((FnI3)(*(void***)ms)[0x14 / 4])(ms, id, 0, 0);
            *(int*)(m + 0x7c) = 0;
            *(char*)(m + 0xa8) = 1;
        }
        if (*(int*)(m + 0x74) != 0) {
            void* o = App67dda0();
            ((FnI2)(*(void***)o)[0x14 / 4])(o, *(int*)(m + 0x6c), *(int*)(m + 0x70));
            *(int*)(m + 0x74) = 0;
        }
        if (*(int*)(p + 8) != 0) {
            int* q = (int*)(m + 0x94);
            if (*q) {
                ((FnI1)(*(void***)*q)[0x0c / 4])((void*)*q, 0);
                int* old = (int*)*q;
                if (old) {
                    *q = 0;
                    ((FnI0)(*(void***)old)[1])(old);
                }
            }
            void* em = EffectsManager();
            if (*q) {
                int* old = (int*)*q;
                *q = 0;
                ((FnI0)(*(void***)old)[1])(old);
            }
            int ok = ((FnI3)(*(void***)em)[0x2c / 4])(em, 0x44ed103, 0, q);
            if (ok)
                ((FnI1)(*(void***)*q)[8 / 4])((void*)*q, 0);
        }
        return true;
    }

    if (msgId == 0x3ea7e1b) {
        void* o = *(void**)(m + 0x68);
        ((FnI1)(*(void***)o)[0x48 / 4])(o, 0);
        ResetRefs76bs(*(void**)(p + 0x10), 0);
        void* ms = MessageServer();
        void* v = *(void**)(p + 8);
        if (v != 0 && ms != 0)
            ((FnI3)(*(void***)ms)[0x14 / 4])(ms, (int)v, 0, 0);
        return true;
    }

    if (msgId == 0x1c91276) {
        int index = *(int*)(p + 8);
        int page  = *(int*)(p + 0x10);
        int alloc = *(int*)(p + 0x18);
        ReleaseViewer76b8(*(void**)(p + 0x20), 0);
        *(int*)(m + 4) = alloc;
        *(int*)(m + 8) = page;
        if (index == 5) {
            void* o = *(void**)(m + 0x68);
            ((FnI1)(*(void***)o)[0x44 / 4])(o, 0);
            RefreshCubeMap(cap, 0, 5);
        }
        return true;
    }

    if (msgId == 0x1c9127b) {
        int index = *(int*)(p + 8);
        int page  = *(int*)(p + 0x10);
        int alloc = *(int*)(p + 0x18);
        int* rasterp = *(int**)(p + 0x28);
        ResetRefs76bs(*(void**)(p + 0x40), 0);
        *(int*)(m + 4) = alloc;
        *(int*)(m + 8) = page;
        if (index == 0) {
            if (rasterp != 0 && *rasterp != 0) {
                FUN_00761110((void*)*rasterp);
                *rasterp = 0;
            }
            int res = *(int*)(m + 0x48);
            *rasterp = (int)CreateRaster(res, res, 1, 0x1208, 0x15);
        }
        int raster = *rasterp;
        *(char*)(raster + 0x12) = (char)index;
        int out;
        if (RasterLock((void*)*rasterp, 0, 2, 0, &out)) {
            void* gfx = *(void**)(m + 0x64);
            ((FnI2)(*(void***)gfx)[0x30 / 4])(gfx, *(int*)(m + 4), *(int*)(m + 8));
            RasterUnlock((void*)*rasterp, 0, &out);
        }
        {
            void* gfx = *(void**)(m + 0x64);
            ((FnI2)(*(void***)gfx)[0x14 / 4])(gfx, *(int*)(m + 4), *(int*)(m + 8));
        }
        if (index == 5) {
            void* v = *(void**)(p + 0x30);
            if (v != 0) {
                void* ms = MessageServer();
                if (ms != 0)
                    ((FnI3)(*(void***)ms)[0x14 / 4])(ms, (int)v, 0, 0);
            }
            FUN_00761110(*(void**)(p + 0x38));
            *(char*)(m + 0x60) = 0;
        }
        {
            void* ms = MessageServer();
            ((FnI3)(*(void***)ms)[0x14 / 4])(ms, 0x12d74a2, 0, 0);
        }
        return true;
    }

    return false;
}
