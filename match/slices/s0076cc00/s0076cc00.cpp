// Slice s0076cc00 (batch w2g3, slice 38).
// Render-target/graphics helper cluster (SP::cRTTManager / cRTTCapture support). Default flags.
#include "types.h"

#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PV virtual void CAT_(_pv, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

extern "C" void*  EASTL_allocator_allocate(uint32_t n, const char* name, int a, int b, const char* f, int line); // 0x00f473a0
extern "C" void   EASTL_allocator_deallocate(void* p);   // 0x00f47380

// allocator.h literal used by the vector growth path
static const char kAllocatorFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// ------------------------------------------------------------------ 0x28-byte scene job element
// Layout recovered from 0076b1f0 / 0076d5c0 / 0076cd30.
struct E28 {
    int32_t       a0;                 // +0x00
    int32_t       a4;                 // +0x04 (low word used as a ushort by CaptureSceneViews)
    float         f8;                 // +0x08
    float         fc;                 // +0x0c
    float         f10;                // +0x10
    float         f14;                // +0x14
    uint8_t       b18;                // +0x18
    uint8_t       b19;                // +0x19
    uint8_t       pad1a[2];           // +0x1a
    int32_t       i1c;                // +0x1c
    int32_t       i20;                // +0x20
    int32_t       i24;                // +0x24
};

// 0076b1f0: E28::operator= (defined in the s0076acd0 slice).  Thunk gives the thiscall ABI.
struct AssignThunk { void FUN_0076b1f0(const E28* src); };
// 0076b9a0: copy a range of E28 elements, returns the advanced destination.
E28* __cdecl FUN_0076b9a0(const E28* first, const E28* last, E28* dst);
// 0076cbb0: erase one E28 element at `position`.
struct EraseThunk { void FUN_0076cbb0(E28* position); };
// 0076b5d0: reset the viewer's referenced sub-objects.
struct ResetThunk { void FUN_0076b5d0(); };
// 0068f970: cJob::ContinueJob.
struct JobThunk { int FUN_0068f970(); };
// 007c3f70: cViewer construction on a raw 0x174 allocation (returns the object).
struct CtorThunk { void* FUN_007c3f70(); };
// 007c4dd0: cViewer::Init.
struct InitThunk { void FUN_007c4dd0(int arg); };
// 0067dd10: SP::App singleton.
struct AppObj;
AppObj* __cdecl FUN_0067dd10();
// 007c40f0: append one short-indexed vertex record (3x3 rotation + translation).
struct RecordThunk { void FUN_007c40f0(unsigned short* dst); };

extern float g_01630698;              // 0x01630698
extern float g_0163069c;              // 0x0163069c
extern float g_016306a0;              // 0x016306a0
extern float g_016307d8;              // 0x016307d8

// ------------------------------------------------------------------ vector of 0x28-byte scene jobs
struct E28Vec {
    E28* mBegin;   // +0
    E28* mEnd;     // +4
    E28* mCap;     // +8

    void insert(E28* position, const E28* value);   // @ 0x0076cc00
};

// @ 0x0076cc00  EASTL vector insert with the growth path used by this container.
void E28Vec::insert(E28* position, const E28* value)
{
    if (mEnd != mCap) {
        E28* last = mEnd;
        if (value >= position && value < mEnd)
            value = value + 1;
        if (last)
            ((AssignThunk*)last)->FUN_0076b1f0(last - 1);
        while (last != position) {
            --last;
            *last = last[-1];
        }
        *position = *value;
        mEnd += 1;
        return;
    }
    uint32_t count = (uint32_t)(mEnd - mBegin);
    uint32_t newCap = count;
    if (count)
        newCap = count * 2;
    else
        newCap = 1;
    E28* newData = 0;
    if (newCap)
        newData = (E28*)EASTL_allocator_allocate(newCap * sizeof(E28), "Graphics", 0, 0,
                                                 kAllocatorFile, 0xd1);
    E28* newEnd = FUN_0076b9a0(mBegin, position, newData);
    if (newEnd)
        ((AssignThunk*)newEnd)->FUN_0076b1f0(value);
    E28* after = FUN_0076b9a0(position, mEnd, newEnd + 1);
    if (mBegin && *(int*)((char*)mBegin - 4) != 0)
        EASTL_allocator_deallocate(mBegin);
    mBegin = newData;
    mEnd = after;
    mCap = newData + newCap;
}

// ------------------------------------------------------------------ cSPTransform / App context
struct Vec3 { float x, y, z; };
struct Matrix33 { void FUN_0041cb40(const void* src); };
struct cSPTransform {
    unsigned short mFlags;              // +0x00
    unsigned short mModificationCount;  // +0x02
    Vec3           mTranslation;        // +0x04
    float          mScale;              // +0x10
    float          mRotation[9];        // +0x14
};

struct AppCtx50 {
    PV4 PV2 PV
    virtual void* GetTransform();        // +0x1c
};
struct AppObj {
    PV8 PV8 PV4
    virtual AppCtx50* GetCtx50();        // +0x50
};

// 0067dcc0: message server singleton (Post lives at vtable +0x14).
struct MsgServer { PV4 PV virtual void Post(uint32_t id, void* msg, int flag); };
MsgServer* __cdecl MessageServer();                     // 0x0067dcc0

// 0067dd60: RTT raster resolver singleton (Resolve lives at vtable +0x34).
struct RTTResolver;
RTTResolver* __cdecl GetRTTResolver();                  // 0x0067dd60

// ------------------------------------------------------------------ allocation helpers
extern "C" long __cdecl _InterlockedExchange(long volatile* p, long v);
#pragma intrinsic(_InterlockedExchange)

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);   // 0x00f473a0
void  operator delete[](void* p);                                           // 0x00f47380
void  operator delete(void* p);                                             // 0x00f47380
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}

// ------------------------------------------------------------------ snapshot/viewer wrapper
struct SysObj {
    SysObj();                     // 0x007c3f70
    void Begin(void* p, int n);   // 0x007c4be0
    void End(int n);              // 0x007c3c50
    char pad[0x174];
};

struct Slot48Obj {
    PV8 PV8 PV2
    virtual void Slot48(int arg); // +0x48
};

struct PrepOut {
    char     pad00[0x40];
    uint32_t m40;      // +0x40
    char     pad44[0x78 - 0x44];
    uint32_t m78;      // +0x78
    uint32_t m7c;      // +0x7c
    uint32_t m80;      // +0x80
    uint32_t m84;      // +0x84
    float    m88;      // +0x88
    float    m8c;      // +0x8c
};

// The object at SnapshotWrap::mField80: a capture host whose job lives at +0x13c.
struct ContinueThunk { int FUN_0068f970(); };
struct CaptureHost {
    char             pad00[0x13c];
    ContinueThunk*   mJob;    // +0x13c
};
// vtable+4 release slot of the capture host.
struct ReleaseObj { virtual void Slot0(); virtual void Release(); };

struct SnapshotWrap {
    char      pad00[0xc];
    SysObj*   mSystem;      // +0x0c
    int32_t   mFlags;       // +0x10
    int32_t   mFlags2;      // +0x14
    void*     mSceneArray;  // +0x18 array of 0x3c records, item pointer at record+0x38
    char      pad1c[0x50 - 0x1c];
    int32_t   mField50;     // +0x50
    char      pad54[0x68 - 0x54];
    uint8_t   mField68;     // +0x68
    char      pad69[0x70 - 0x69];
    void*     mField70;     // +0x70
    char      pad74[0x80 - 0x74];
    void*     mField80;     // +0x80
    void*     mField84;     // +0x84
    E28Vec    mJobs;        // +0x88

    void Teardown(int a, int b, int c, int d);              // @ 0x0076d970
    void CreateViewer(int32_t* rect);                       // @ 0x0076d8e0
    void Update(int unused);                                // @ 0x0076cd30
    void push_back(int a0, int a1, float a2, float a3, float a4, float a5,
                   int a6, char a7, char a8, int a9, int a10);   // @ 0x0076d5c0
    void PushThreeJobs(int a0, int a1, int a2, int a3, float a4, float a5,
                       float a6, float a7, int a8, char a9, char a10,
                       int a11, int a12, int a13);          // @ 0x0076d6e0
    void Effects_PrepareRender(int idx, void* a, PrepOut* out, char flag); // @ 0x0076da50
};

// 006e3100: SP::CaptureSceneViews(int, cFaceCamera**, float x4, ushort, char, int x3)
struct cFaceCamera;
void __cdecl CaptureSceneViews(int view, cFaceCamera** cameras, float a, float b,
                               float c, float d, unsigned short flags, char opt,
                               int x, int y, int z);          // 0x006e3100

// @ 0x0076d8e0  allocate and initialise the viewer, then copy the capture rect.
void SnapshotWrap::CreateViewer(int32_t* rect)
{
    SysObj* v = new("Graphics", 0, 0, 0, 0) SysObj();
    mSystem = v;
    ((InitThunk*)v)->FUN_007c4dd0(0);
    mFlags = rect[0];
    mFlags2 = rect[1];
}

// @ 0x0076cd30  per-frame capture wrapper: continue/retire the job, then launch the next view.
void SnapshotWrap::Update(int unused)
{
    (void)unused;
    if (mField80) {
        ContinueThunk* jobMgr = ((CaptureHost*)mField80)->mJob;
        if (jobMgr) {
            int state = jobMgr->FUN_0068f970();
            if ((unsigned)(state - 7) <= 1) {
                ((Slot48Obj*)mField70)->Slot48(0);
                ((ResetThunk*)mField80)->FUN_0076b5d0();
                if (mField80) {
                    ReleaseObj* old = (ReleaseObj*)mField80;
                    mField80 = 0;
                    old->Release();
                }
                MsgServer* ms = MessageServer();
                if (mField84 && ms)
                    ms->Post((uint32_t)(size_t)mField84, 0, 0);
                mField84 = 0;
            }
        }
    }
    if (mJobs.mBegin != mJobs.mEnd && mField68 == 0) {
        E28 job;
        ((AssignThunk*)&job)->FUN_0076b1f0(mJobs.mBegin);
        mField68 = 1;
        CaptureSceneViews(job.a0, (cFaceCamera**)((char*)this + 0x2c),
                          job.f8, job.fc, job.f10, job.f14,
                          *(unsigned short*)&job.a4, (char)job.b19,
                          job.i1c, job.i20, job.i24);
        ((EraseThunk*)&mJobs)->FUN_0076cbb0(mJobs.mBegin);
    }
}

// @ 0x0076d5c0  build a 0x28 job element from the arguments and append it.
void SnapshotWrap::push_back(int a0, int a1, float a2, float a3, float a4, float a5,
                             int a6, char a7, char a8, int a9, int a10)
{
    cSPTransform xf;
    if (a7) {
        xf.mFlags = 0;
        xf.mModificationCount = 0;
        xf.mTranslation.x = g_01630698;
        xf.mTranslation.y = g_0163069c;
        xf.mTranslation.z = g_016306a0;
        xf.mScale = 1.0f;
        ((Matrix33*)xf.mRotation)->FUN_0041cb40(&g_016307d8);
        AppCtx50* ctx = FUN_0067dd10()->GetCtx50();
        ((RecordThunk*)ctx->GetTransform())->FUN_007c40f0((unsigned short*)&xf);
    }
    E28& e = *(E28*)&xf;
    mField50 = a1;
    e.a0 = a0;
    e.a4 = a1;
    e.f8 = a2;
    e.fc = a3;
    e.f10 = a4;
    e.f14 = a5;
    e.b18 = a7;
    e.b19 = a8;
    e.i1c = a9;
    e.i20 = a10;
    e.i24 = a6;
    if (mJobs.mEnd < mJobs.mCap) {
        E28* p = mJobs.mEnd;
        mJobs.mEnd = p + 1;
        if (p)
            ((AssignThunk*)p)->FUN_0076b1f0(&e);
    } else {
        mJobs.insert(mJobs.mEnd, &e);
    }
}

// @ 0x0076d6e0  queue the three capture views (formats 5 / 7 / 6).
void SnapshotWrap::PushThreeJobs(int a0, int a1, int a2, int a3, float a4, float a5,
                                 float a6, float a7, int a8, char a9, char a10,
                                 int a11, int a12, int a13)
{
    push_back(a0, a3, a4, a5, a6, a7, 0,  a9, a10, a11, 5);
    push_back(a1, a3, a4, a5, a6, a7, 0,  a9, a10, a12, 7);
    push_back(a2, a3, a4, a5, a6, a7, a8, a9, a10, a13, 6);
}

// ------------------------------------------------------------------ scene job record layout
struct JobItem { uint32_t m0; uint8_t mFlags; };
struct Rec3c { char pad[0x38]; JobItem* mItem; };
struct PrepOwner {
    PV8 PV
    virtual void Prepare(int idx, void* a, unsigned short* o0, unsigned short* o1,
                         unsigned short* o2, unsigned short* o3);   // +0x24
};
struct ResolveMgr {
    PV8 PV4 PV
    virtual void Resolve(JobItem* item);                            // +0x34
};

// @ 0x0076da50  prepare one scene job's destination record.
void SnapshotWrap::Effects_PrepareRender(int idx, void* a, PrepOut* out, char flag)
{
    Rec3c* rec = (Rec3c*)((char*)mSceneArray + (size_t)idx * 0x3c);
    JobItem* item = rec->mItem;
    if ((item->mFlags & 1) == 0) {
        ResolveMgr* mgr = (ResolveMgr*)GetRTTResolver();
        mgr->Resolve(item);
    }
    out->m40 = item->m0;
    if (flag) {
        unsigned short q0, q1, q2, q3;
        ((PrepOwner*)this)->Prepare(idx, a, &q0, &q1, &q2, &q3);
        out->m78 = q0;
        out->m7c = q1;
        out->m80 = q2;
        out->m84 = q3;
        out->m88 = 0.0f;
        out->m8c = 1.0f;
    }
}

// ------------------------------------------------------------------ key comparator
struct Key29 {
    int32_t pad0;   // +0x00
    int32_t a;      // +0x04
    int32_t b;      // +0x08
    int32_t c;      // +0x0c
};

// @ 0x0076f540  (slice 40's comparator, declared here for the page bookkeeping callers)
bool __cdecl LessPage(const Key29& x, const Key29& y)
{
    if (x.a < y.a) return true;
    if (x.a > y.a) return false;
    if (x.b < y.b) return true;
    if (x.b > y.b) return false;
    if (x.c < y.c) return true;
    return false;
}

// ------------------------------------------------------------------ cRTTManager page release
struct PageInfo {
    char    pad00[0x34];
    int32_t mRefCount;   // +0x34
    int32_t mPad38;      // +0x38
    void    Release(void* arg);   // 0x007b0e60
};
struct PageVec {
    PageInfo* mBegin;   // +0x00
    PageInfo* mEnd;     // +0x04
    PageInfo* mCap;     // +0x08
};
struct cRTTManager {
    char      pad00[0x10];
    bool      mInitialized;       // +0x10
    int32_t   mDefaultResolution; // +0x14
    PageVec   mTexturePages;      // +0x18

    // @ 0x0076d9e0  release one page allocation; true when a page was released.
    bool ReleasePage(int index, void* arg);
};

// @ 0x0076d9e0
bool cRTTManager::ReleasePage(int index, void* arg)
{
    if (index >= 0 && index < (int)(mTexturePages.mEnd - mTexturePages.mBegin)) {
        PageInfo* p = mTexturePages.mBegin + index;
        if (p->mRefCount > 0) {
            p->Release(arg);
            --p->mRefCount;
            return true;
        }
    }
    return false;
}

// ------------------------------------------------------------------ small setters / query helpers
struct RectThing {
    char    pad00[0x78];
    int32_t mW0;      // +0x78
    int32_t mH0;      // +0x7c
    int32_t mW1;      // +0x80
    int32_t mH1;      // +0x84
    float   mFrac;    // +0x88
    float   mScale;   // +0x8c

    // @ 0x0076d7d0
    void SetSize(uint16_t a, uint16_t b, uint16_t c, uint16_t d);
};

// @ 0x0076d7d0
void RectThing::SetSize(uint16_t a, uint16_t b, uint16_t c, uint16_t d)
{
    mW0 = a;
    mH0 = b;
    mW1 = c;
    mH1 = d;
    mFrac = 0.0f;
    mScale = 1.0f;
}

// @ 0x0076d820  bytes per pixel for a raster format.
int __cdecl RasterFormatSize(int width, int height, int format)
{
    int mult = 0;
    switch (format) {
    case 0x1a:
    case 0x6f:
        mult = 2;
        break;
    case 0x1c:
        mult = 1;
        break;
    case 0x15:
    case 0x16:
    case 0x70:
    case 0x72:
        mult = 4;
        break;
    }
    return mult * width * height;
}

// A 0x1d-byte POD record used by the RTT page allocator bookkeeping.
struct PageRecord {
    int32_t mData[7];   // +0x00
    uint8_t mFlag;      // +0x1c
    PageRecord(const PageRecord& o);
};

// @ 0x0076d9a0
PageRecord::PageRecord(const PageRecord& o)
{
    for (int i = 0; i < 7; ++i) mData[i] = o.mData[i];
    mFlag = o.mFlag;
}

// @ 0x0076d970
void SnapshotWrap::Teardown(int, int, int, int)
{
    if (mSystem != 0) {
        mSystem->Begin(&mFlags, 1);
        mSystem->End(7);
    }
}

// ------------------------------------------------------------------ message hook
struct OwnedSub {
    void Destroy();    // 0x007c3ba0
    void Cleanup();    // 0x007c4000
};
struct Holder {
    char      pad00[0xc];
    OwnedSub* mSub;   // +0x0c
};

// @ 0x0076db00
bool __stdcall OnCaptureMessage(int msgId, void* payload)
{
    if (msgId == 0x3d037f1) {
        Holder* h = (Holder*)*(void**)((char*)payload + 8);
        OwnedSub* sub = h->mSub;
        if (sub != 0) {
            sub->Destroy();
            sub = h->mSub;
            if (sub != 0) {
                sub->Cleanup();
                EASTL_allocator_deallocate(sub);
            }
        }
        return true;
    }
    return false;
}

// ------------------------------------------------------------------ remaining large bodies
// @ 0x0076ce50  tile-by-tile render-to-texture capture of a viewer into one big RGBA image
// (optionally saved as "<path>.png" through a Daf job).  Names are Claude-coined from behaviour.

// message object posted to the message server (0x18 bytes)
struct RefBaseA22 {
    virtual ~RefBaseA22();
    virtual void AddRef();
    virtual void Release();
    long mRefCount;
    int  mField8;
    int  mFieldC;
    int  mField10;
    int  mField14;
    RefBaseA22() : mField10(0) { _InterlockedExchange(&mRefCount, 0); }
};
struct DrvBA22 : RefBaseA22 {
    virtual ~DrvBA22();
    DrvBA22() {}
};

template <class T> struct ARef {
    T* mp;
    ARef(T* p) : mp(p) { if (mp) mp->AddRef(); }
    ~ARef() { if (mp) mp->Release(); }
    T* operator->() const { return mp; }
};

struct CapViewer {
    bool Copy(CapViewer* src, int a, int b);               // 0x007c50b0 (ret 0xc)
    void SetRaster(const void* key, int n);                // 0x007c4be0 (ret 8)
    void FUN_007c3c50(int n);                              // 0x007c3c50 (ret 4)
    void GetSize(float* w, float* h);                      // 0x007c40c0 (ret 8)
    void SetOffset(float x, float y);                      // 0x007c4ad0 (ret 8)
};
struct CapTarget { PV2 PV virtual void Process(int a, int b, void* s, uint32_t c); };   // +0x0c
struct EffectsMgr { PV8 PV8 virtual void SetXY(float a, float b); };                     // +0x40
EffectsMgr* __cdecl EffectsManager();                                                   // 0x0067ddd0
struct DevInfo {
    PV8 PV8 PV8 PV8 PV8 PV8 PV2 PV                                                     // slots 0..50
    virtual void GetPair(uint32_t* out);                                               // +0xcc
};
DevInfo* __cdecl GetDevInfo();                                                          // 0x0067dd40
struct PixFormat { char pad[0x10]; uint8_t mBits; };
struct RasterMgr {
    PV4                                                                                 // slots 0..3
    virtual uint32_t* Create(uint32_t* out, int w, int h, int fmt, int a, int b, int c);   // +0x10
    virtual void Release(uint32_t lo, uint32_t hi);                                     // +0x14
    virtual PixFormat* GetFormat(uint32_t lo, uint32_t hi);                             // +0x18
    PV2
    virtual void GetInfo(uint32_t lo, uint32_t hi, int* w2, int* h2, int* w, int* h);   // +0x24
    PV2
    virtual void Read(uint32_t lo, uint32_t hi, void* dst);                             // +0x30
    PV4 PV
    virtual void SetName(uint32_t lo, uint32_t hi, const char* name);                   // +0x48
};
RasterMgr* __cdecl GetRasterMgr();                                                      // 0x0067dda0
struct ReadMgr {
    PV8 PV8 PV4 PV2
    virtual void Fill(uint32_t* a, uint32_t* b, uint32_t c, float d);                  // +0x58
};
ReadMgr* __cdecl GetReadMgr();                                                          // 0x0067ddb0

struct JobRelease { void Release(); };                                                  // 0x00690120
extern void __cdecl FUN_0075d870();                                                     // 0x0075d870
struct JobObj {
    void (__cdecl* mFn)();   // +0
    int mF4;
    char pad8[0x10];
    int mF18;                // +0x18
    void FUN_0068f9b0(void* daf);                                                       // 0x0068f9b0 (ret 4)
    void FUN_006909b0();                                                                // 0x006909b0
};
struct JobSvc { PV4 virtual void Create(JobObj** out); };                               // +0x10
JobSvc* __cdecl GetJobSvc();                                                            // 0x0068f4d0

struct Daf {
    virtual void AddRef();
    virtual void Release();
    uint32_t mVptr2;
    long mAtomic;
    char mName[0x104];
    void* mFormat;       // +0x110
    int mW;              // +0x114
    int mH;              // +0x118
    void* mPixels;       // +0x11c
    char mFlag;          // +0x120
    Daf() throw();       // 0x0076af50
};
extern float g_two;                                                                     // 0x01470f1c
extern char g_emptyStr;                                                                 // 0x01667bac
struct EStr {
    char* b; char* e; char* c;
    EStr() : b(&g_emptyStr), e(&g_emptyStr), c(&g_emptyStr + 1) {}
    ~EStr() { if (c - b > 1 && b) operator delete(b); }
    int sprintf(const char* fmt, ...);                                                  // 0x00472fe0
};

struct TileCapture {
    char   pad00[0xc];
    CapTarget* mTarget0;     // +0x0c
    CapTarget* mTarget1;     // +0x10
    CapTarget* mTarget2;     // +0x14
    CapViewer* mViewer;      // +0x18
    uint32_t   mRaster[2];   // +0x1c
    bool       mSized;       // +0x24
    uint32_t   mTiles;       // +0x28
    int        mW;           // +0x2c
    int        mH;           // +0x30
    char       mPath[5];     // +0x34
    char       pad39[0x139 - 0x39];
    bool       mDirect;      // +0x139
    char       pad13a[2];
    JobObj*    mJob;         // +0x13c

    void Capture(int a1, int a2, CapViewer** pViewer, uint32_t a4);
};

struct ViewState { CapViewer* viewer; int z0, z1, z2; };

#define RENDER_PASS()                                                                 \
    {                                                                                 \
        ViewState vs;                                                                 \
        vs.viewer = mViewer; vs.z0 = 0; vs.z1 = 0; vs.z2 = 0;                         \
        EffectsManager()->SetXY(0.0f, 0.0f);                                          \
        mTarget0->Process(a1, a2, &vs, a4);                                           \
        MessageServer()->Post(0x12d74a2, rawMsg, 0);                                  \
        mTarget1->Process(a1, a2, &vs, a4);                                           \
        EffectsManager()->SetXY(0.0f, 0.0f);                                          \
        mTarget2->Process(a1, a2, &vs, a4);                                           \
    }

void TileCapture::Capture(int a1, int a2, CapViewer** pViewer, uint32_t a4)
{
    CapTarget* t0 = mTarget0;
    if (t0 == 0)
        return;
    mViewer->Copy(*pViewer, 1, 0);
    RefBaseA22* rawMsg = new("App", 0, 0, 0, 0) DrvBA22();
    ARef<RefBaseA22> msg(rawMsg);
    rawMsg->mField8 = (int)*pViewer;
    if (mSized) {
        uint32_t q[2] = { 0xffffffff, 0xffffffff };
        GetDevInfo()->GetPair(q);
        int u0, v0, wid, hei;
        GetRasterMgr()->GetInfo(q[0], q[1], &u0, &v0, &wid, &hei);
        PixFormat* fmt = GetRasterMgr()->GetFormat(q[0], q[1]);
        uint32_t total = (fmt->mBits >> 3) * wid * hei;
        mH = mTiles * hei;
        mW = mTiles * wid;
        uint8_t* big = new("Graphics", 0, 0, 0, 0) uint8_t[mTiles * mTiles * total];
        uint8_t* tile = new("Graphics", 0, 0, 0, 0) uint8_t[total];
        for (uint32_t j = 0; j < mTiles; j++) {
            for (uint32_t i = 0; i < mTiles; i++) {
                q[0] = 0xffffffff;
                q[1] = 0xffffffff;
                GetDevInfo()->GetPair(q);
                int u1, v1, wid1, hei1;
                GetRasterMgr()->GetInfo(q[0], q[1], &u1, &v1, &wid1, &hei1);
                mViewer->SetRaster(q, 1);
                float fw, fh;
                mViewer->GetSize(&fw, &fh);
                fw = fw * g_two;
                fh = fh * g_two;
                mViewer->SetOffset(-((fw * (float)j) / (float)(mTiles * wid1)),
                                   (fh * (float)i) / (float)(mTiles * hei1));
                mViewer->FUN_007c3c50(7);
                RENDER_PASS()
                if (mDirect) {
                    uint32_t pr[2] = { 0xffffffff, 0xffffffff };
                    RasterMgr* rm = GetRasterMgr();
                    uint32_t tmp[2];
                    uint32_t* r = rm->Create(tmp, 0x80, 0x80, 0x15, 0, -1, 0);
                    pr[0] = r[0];
                    pr[1] = r[1];
                    rm->SetName(r[0], r[1], "ScreenshotThumbnailRTT");
                    GetReadMgr()->Fill(q, pr, a4, 0.0f);
                    rm->GetInfo(pr[0], pr[1], &u0, &v0, &wid, &hei);
                    mH = mTiles * hei;
                    mW = mTiles * wid;
                    rm->Read(pr[0], pr[1], tile);
                    rm->Release(pr[0], pr[1]);
                } else {
                    GetRasterMgr()->Read(q[0], q[1], tile);
                }
                int dst = (mW * i + j) * 4;
                int src = 0;
                for (int y = 0; y < hei; y++) {
                    for (int x = 0; x < wid; x++) {
                        big[dst] = tile[src];
                        big[dst + 1] = tile[src + 1];
                        big[dst + 2] = tile[src + 2];
                        big[dst + 3] = tile[src + 3];
                        dst += mTiles * 4;
                        src += 4;
                    }
                    dst += (mTiles - 1) * mW * 4;
                }
            }
        }
        if (mPath[0] != 0) {
            EStr str;
            str.sprintf("%s.png", mPath);
            Daf* rawDaf = new("Graphics", 0, 0, 0, 0) Daf();
            ARef<Daf> daf(rawDaf);
            {
                char* s = str.b;
                char* d = rawDaf->mName;
                char c;
                do {
                    c = *s++;
                    *d++ = c;
                } while (c);
            }
            rawDaf->mFormat = fmt;
            rawDaf->mW = mW;
            rawDaf->mH = mH;
            rawDaf->mPixels = big;
            rawDaf->mFlag = 0;
            JobSvc* svc = GetJobSvc();
            if (mJob) {
                JobObj* old = mJob;
                mJob = 0;
                ((JobRelease*)old)->Release();
            }
            svc->Create(&mJob);
            mJob->mFn = FUN_0075d870;
            mJob->mF4 = 0;
            mJob->mF18 = 4;
            mJob->FUN_0068f9b0(rawDaf);
            mJob->FUN_006909b0();
        } else {
            operator delete(big);
        }
        operator delete(tile);
    } else {
        mViewer->SetRaster(mRaster, 1);
        mViewer->FUN_007c3c50(7);
        RENDER_PASS()
    }
}

// 0x0067dd60: RTT raster resolver singleton.
