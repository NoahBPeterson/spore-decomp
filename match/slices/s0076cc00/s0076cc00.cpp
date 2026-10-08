// Slice s0076cc00 (batch w2g3, slice 38).
// Render-target/graphics helper cluster (SP::cRTTManager / cRTTCapture support). Default flags.
#include "types.h"

extern "C" void*  EASTL_allocator_allocate(uint32_t n, const char* name, int a, int b, const char* f, int line);
extern "C" void   EASTL_allocator_deallocate(void* p);   // 0x00f47380

// ------------------------------------------------------------------ shared helpers (other TUs)
void  FUN_0076b1f0(void* dst);                            // element move-construct (0x28 bytes)
void* FUN_0076b9a0(void* first, void* last, void* dst);   // uninitialized relocate
void  FUN_0076cbb0(void* p);                              // erase one 0x28 element
void  FUN_007c4be0(void* p, int n);
void  FUN_007c3c50(int n);
void  FUN_007b0e60(void* p);

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

// ------------------------------------------------------------------ vector of 0x28-byte scene jobs
struct Job28 { uint32_t mWord[10]; };   // 0x28
struct JobVec28 {
    Job28* mBegin;   // +0
    Job28* mEnd;     // +4
    Job28* mCap;     // +8

    // @ 0x0076cc00  insert(before, value): full EASTL vector insert with growth.
    Job28* insert(Job28* position, const Job28* value);
    // @ 0x0076d5c0  build a 0x28 element from arguments and append it.
    void push_back(const Job28* value);
};

// @ 0x0076cc00
Job28* JobVec28::insert(Job28* position, const Job28* value)
{
    if (mEnd == mCap) {
        uint32_t oldCount = (uint32_t)((char*)mEnd - (char*)mBegin) / sizeof(Job28);
        uint32_t newCap = oldCount ? oldCount * 2 : 1;
        Job28* newData = (Job28*)EASTL_allocator_allocate(newCap * sizeof(Job28), "Graphics", 0, 0, 0, 0);
        Job28* newEnd = (Job28*)FUN_0076b9a0(mBegin, position, newData);
        if (newEnd)
            FUN_0076b1f0(newEnd);
        Job28* after = (Job28*)FUN_0076b9a0(position, mEnd, newEnd + 1);
        if (mBegin && *(int*)((char*)mBegin - 4) != 0)
            EASTL_allocator_deallocate(mBegin);
        mBegin = newData;
        mEnd = after;
        mCap = newData + newCap;
        return newEnd;
    }
    Job28* last = mEnd;
    if (position != mEnd) {
        FUN_0076b1f0(last);
        while (last != position) {
            --last;
            *last = last[-1];
        }
    }
    *position = *value;
    mEnd = mEnd + 1;
    return position;
}

// @ 0x0076d5c0  (skeleton; see partial.txt)
void JobVec28::push_back(const Job28* value)
{
    if (mEnd < mCap) {
        FUN_0076b1f0(mEnd);
        mEnd = mEnd + 1;
    } else {
        insert(mEnd, value);
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

// ------------------------------------------------------------------ snapshot/viewer wrapper
struct Viewer174 {
    char    pad00[0xc];
    void*   mField0c;   // +0x0c
    int32_t mField10;   // +0x10
    int32_t mField14;   // +0x14
};
void  InitViewer174(void* viewer, int arg);   // 0x007c4dd0
void* AllocViewer174();                       // 0x007c3f70 (ctor)

struct SysObj {
    void Begin(void* p, int n);   // 0x007c4be0
    void End(int n);              // 0x007c3c50
};

struct SnapshotWrap {
    char      pad00[0xc];
    SysObj*   mSystem;    // +0x0c
    int32_t   mFlags;     // +0x10
    int32_t   mFlags2;    // +0x14

    void Teardown(int a, int b, int c, int d);              // @ 0x0076d970
    void CreateViewer(int32_t* rect);                       // @ 0x0076d8e0
    void Update();                                          // @ 0x0076cd30
};

// @ 0x0076d970
void SnapshotWrap::Teardown(int, int, int, int)
{
    if (mSystem != 0) {
        mSystem->Begin(&mFlags, 1);
        mSystem->End(7);
    }
}

// @ 0x0076d8e0
void SnapshotWrap::CreateViewer(int32_t* rect)
{
    Viewer174* v = (Viewer174*)EASTL_allocator_allocate(0x174, "Graphics", 0, 0, 0, 0);
    if (v)
        v = (Viewer174*)AllocViewer174();
    mSystem = (SysObj*)v;
    InitViewer174(v, 0);
    mFlags = rect[0];
    mFlags2 = rect[1];
}

// @ 0x0076cd30  (skeleton; see partial.txt)
void SnapshotWrap::Update()
{
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
#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PV virtual void CAT_(_pv, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

extern "C" long __cdecl _InterlockedExchange(long volatile* p, long v);
#pragma intrinsic(_InterlockedExchange)

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);   // 0x00f473a0
void  operator delete[](void* p);                                           // 0x00f47380
void  operator delete(void* p);                                             // 0x00f47380
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}

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
struct MsgServer { PV4 PV virtual void Post(uint32_t id, void* msg, int flag); };       // +0x14
MsgServer* __cdecl MessageServer();                                                     // 0x0067dcc0
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

// @ 0x0076d6e0
void __cdecl PushThreeJobs(void* a, void* b, void* c, int v, int w, int x, int y, int z,
                           int m1, int m2, int m3, int m4, int m5, int m6)
{
    (void)a; (void)b; (void)c; (void)v; (void)w; (void)x; (void)y; (void)z;
    (void)m1; (void)m2; (void)m3; (void)m4; (void)m5; (void)m6;
    // skeleton: three 0x0076d5c0 calls (see partial.txt)
}

// @ 0x0076da50
void __cdecl Effects_PrepareRender(int* self, int idx, void* a, int out, char flag)
{
    (void)self; (void)idx; (void)a; (void)out; (void)flag;
    // skeleton: per-job virtual dispatch and destination rect fill (see partial.txt)
}
