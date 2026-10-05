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
// @ 0x0076ce50
void __cdecl Effects_Process(int* self, void* arg)
{
    (void)self; (void)arg;   // skeleton: 1904-byte job/vector processing (see partial.txt)
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
