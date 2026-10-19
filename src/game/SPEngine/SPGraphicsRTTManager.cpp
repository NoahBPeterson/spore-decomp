// src/game/SPEngine/SPGraphicsRTTManager.cpp -- migrated from slice(s) s0076ed30, s0076db40, s0076cc00 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsRTTManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cViewer.h"
#include <xmmintrin.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void   EASTL_allocator_deallocate(void* p);   // 0x00f47380

// ---- items of slice s0076cc00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void   EASTL_allocator_deallocate(void* p);   // 0x00f47380
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
struct OwnedSub {
    void Destroy();    // 0x007c3ba0
    void Cleanup();    // 0x007c4000
};
struct Holder {
    char      pad00[0xc];
    OwnedSub* mSub;   // +0x0c
};
// ---- items of slice s0076cc00 end

// ---- items of slice s0076db40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PageRecord {
    int a[7];             // +0x00
    unsigned char b;      // +0x1c
    PageRecord& operator=(const PageRecord& o);
};
PageRecord& PageRecord::operator=(const PageRecord& o)
{
    a[0] = o.a[0]; a[1] = o.a[1]; a[2] = o.a[2]; a[3] = o.a[3];
    a[4] = o.a[4]; a[5] = o.a[5]; a[6] = o.a[6]; b = o.b;
    return *this;
}
struct PageInfo_s0076_db40 {
    void* mData;      // +0x00
    char  pad04[0x28];
    int   mA;         // +0x2c
    int   mB;         // +0x30
    int   mRefCount;  // +0x34
    void* mTexture;   // +0x38
};
struct PageVec_s0076_db40 { PageInfo_s0076_db40* mBegin; PageInfo_s0076_db40* mEnd; PageInfo_s0076_db40* mCap; };
struct cRTTManager_s0076_db40 {
    char    pad[0x18];
    PageVec_s0076_db40 mTexturePages;   // +0x18

    // @ 0x0076db40  lazily resolve the raster from a page's texture instance.
    void* GetTextureHandle(int i);  // 0x0076db40 (cRTTManager::GetTextureHandle)
    // @ 0x0076dbb0  page texture pointer.
    void* GetTexture(int i);  // 0x0076dbb0 (cRTTManager::GetTexture)
    // @ 0x0076dc00  copy a 4-dword rect for sub-page `sub` into out.
    bool  GetRect(int i, int sub, int* out);  // 0x0076dc00 (cRTTManager::GetRect)
    // @ 0x0076dc70  copy the rect and its (w,h) deltas.
    bool  GetRectSizes(int i, int sub, int* a, int* b, int* c, int* d);  // 0x0076dc70 (cRTTManager::GetRectSizes)
    // @ 0x0076dcf0  copy mA/mB.
    bool  GetAB(int i, int* a, int* b);  // 0x0076dcf0 (cRTTManager::GetAB)
    // @ 0x0076dd60  fill the page raster and a sprite texture.
    bool  FillSprite(int i, int a, int b);  // 0x0076dd60 (cRTTManager::FillSprite)
    // @ 0x0076ddb0  find a page by (mA,mB,refcount == criteria); returns index.
    bool  FindPage(int a, int b, int c, int* out);
    // @ 0x0076e040  per-page rectangle scale (1/pageSize) in float.
    bool  GetScaledRect(int i, int sub, float* a, float* b);  // 0x0076e040 (cRTTManager::GetScaledRect)
    // @ 0x0076e110  allocate a new texture page.
    bool  AllocateNewPage(int pageId, int w, int h, int depth);  // 0x0076e110 (cRTTManager::AllocateNewPage)
};
struct SpVec { char* mBegin; char* mEnd; char* mCap; void DeallocateSelf(); };
struct VecElem { int pad0; SpVec v; int pad2[4]; };
void __stdcall FreeElemArray(VecElem* first, VecElem* last);
struct Rec3c {
    char  pad00[0x38];
    void* mTexture;   // +0x38
    void  DestroyOne();
};
struct SomeObj3 {
    char pad[0x18];
    Rec3c* mBegin;    // +0x18
    Rec3c* mEnd;      // +0x1c
    void Destroy();
};
struct BigRec {
    char pad00[0x14];
    char padVec[0x14];   // +0x14 vector<float,sp_vector_allocator>
    char pad28[0x10];
    void* mRef;          // +0x38
};
struct BigRecOps {
    void* Construct(void* src);
    int   CopyFrom(BigRecOps* src);
};
struct BigRec2 {
    char pad00[0x38];
};
struct cRTTCheat {
    void* Construct();
    void  Execute(void* args);
};
// ---- items of slice s0076db40 end

// ---- items of slice s0076ed30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PageInfo_s0076_ed30 { char pad[0x3c]; };
PageInfo_s0076_ed30* MoveRange76(PageInfo_s0076_ed30* first, PageInfo_s0076_ed30* last, PageInfo_s0076_ed30* out);   // cdecl (0x76e900)
struct PageVec_s0076_ed30 {
    PageInfo_s0076_ed30* mBegin;
    PageInfo_s0076_ed30* mEnd;
    PageInfo_s0076_ed30* mCap;
    void destroyRange(PageInfo_s0076_ed30* first, PageInfo_s0076_ed30* last);   // thiscall (0x76e3b0)
    PageInfo_s0076_ed30* erase(PageInfo_s0076_ed30* first, PageInfo_s0076_ed30* last);     // @ 0x0076ed90
};
struct ArgScriptOptionParser {
    char pad[0x10];
};
struct cCommandBase {
    char pad[4];
};
struct cRTTCheat_s0076_ed30 {
    char pad[0x10];
    ArgScriptOptionParser mParser;   // +0x10
    void ScalarDelete();  // 0x0076ed30 (cRTTCheat::ScalarDelete)
};
void DestroyOptionParser(ArgScriptOptionParser* p);   // 0x00405050
void DestroyCommandBase(cCommandBase* p);             // 0x0083c750
// ---- items of slice s0076ed30 end

// @ 0x0076d820
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





// @ 0x0076da50
void __cdecl Effects_PrepareRender(int* self, int idx, void* a, int out, char flag)
{
    (void)self; (void)idx; (void)a; (void)out; (void)flag;
    // skeleton: per-job virtual dispatch and destination rect fill (see partial.txt)
}





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




// @ 0x0076db40
void* cRTTManager_s0076_db40::GetTextureHandle(int i)
{
    (void)i;
    return 0;
}



// @ 0x0076dbb0
void* cRTTManager_s0076_db40::GetTexture(int i)
{
    if (i < 0) return 0;
    if (i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return 0;
    if (mTexturePages.mBegin[i].mRefCount <= 0) return 0;
    return mTexturePages.mBegin[i].mTexture;
}



// @ 0x0076dc00
bool cRTTManager_s0076_db40::GetRect(int i, int sub, int* out)
{
    if (i < 0) return false;
    if (i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return false;
    if (mTexturePages.mBegin[i].mRefCount <= 0) return false;
    int* src = (int*)((char*)mTexturePages.mBegin[i].mData + sub * 0x20);
    out[0] = src[0]; out[1] = src[1]; out[2] = src[2]; out[3] = src[3];
    return true;
}



// @ 0x0076dc70
bool cRTTManager_s0076_db40::GetRectSizes(int i, int sub, int* a, int* b, int* c, int* d)
{
    if (i < 0) return false;
    if (i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return false;
    if (mTexturePages.mBegin[i].mRefCount <= 0) return false;
    int* src = (int*)((char*)mTexturePages.mBegin[i].mData + sub * 0x20);
    *a = src[0]; *b = src[1]; *c = src[2] - src[0]; *d = src[3] - src[1];
    return true;
}



// @ 0x0076dcf0
bool cRTTManager_s0076_db40::GetAB(int i, int* a, int* b)
{
    if (i < 0) return false;
    if (i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return false;
    if (mTexturePages.mBegin[i].mRefCount <= 0) return false;
    *a = mTexturePages.mBegin[i].mA;
    *b = mTexturePages.mBegin[i].mB;
    return true;
}



// @ 0x0076de20
void __cdecl UninitCopyPageRecords(PageRecord** out, PageRecord* first, PageRecord* last, PageRecord* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst) *dst = *first;
            ++first;
            ++dst;
        } while (first != last);
        *out = dst;
    }
}



// @ 0x0076de80
void __cdecl CopyPageRecords(PageRecord* first, PageRecord* last, PageRecord* out)
{
    for (; first != last; ++first, ++out)
        *out = *first;
}



// @ 0x0076e040
bool cRTTManager_s0076_db40::GetScaledRect(int i, int sub, float* a, float* b)
{
    if (i < 0) return false;
    if (i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return false;
    if (mTexturePages.mBegin[i].mRefCount <= 0) return false;
    PageInfo_s0076_db40* p = mTexturePages.mBegin + i;
    int* src = (int*)((char*)p->mData + sub * 0x20);
    float sx = 1.0f / (float)p->mA;
    float sy = 1.0f / (float)p->mB;
    a[0] = sx * (float)src[0];
    a[1] = sx * (float)src[1];
    b[0] = sy * (float)src[2];
    b[1] = sy * (float)src[3];
    return true;
}



// @ 0x0076e110
bool cRTTManager_s0076_db40::AllocateNewPage(int pageId, int w, int h, int depth)
{
    (void)pageId; (void)w; (void)h; (void)depth;
    return false;
}



// @ 0x0076e1e0
void SpVec::DeallocateSelf()
{
    if ((mCap - mBegin) > 1 && mBegin)
        EASTL_allocator_deallocate(mBegin);
}



// @ 0x0076e2c0
void Rec3c::DestroyOne()
{
    if (mTexture) {
        // AutoRefCount<...>::Release: decrement at +8, delete when it reaches 0
        volatile int* rc = (volatile int*)((char*)mTexture + 8);
        int n = --*rc;
        if (n < 1) ++*rc;
    }
    void* p = *(void**)((char*)this + 0x14);
    if (p && *(int*)((char*)p - 4) != 0)
        EASTL_allocator_deallocate(p);
    p = *(void**)this;
    if (p && *(int*)((char*)p - 4) != 0)
        EASTL_allocator_deallocate(p);
}



// @ 0x0076e320
Rec3c* __cdecl DestroyRecRange(Rec3c* first, Rec3c* last, Rec3c* out)
{
    if (first == last) return out;
    do {
        first->DestroyOne();
        ++first;
        ++out;
    } while (first != last);
    return out;
}



// @ 0x0076e3b0
void __stdcall DestroyRecArray(Rec3c* first, Rec3c* last)
{
    for (; first < last; ++first)
        first->DestroyOne();
}



// @ 0x0076e430
void __stdcall FreeElemArray(VecElem* first, VecElem* last)
{
    for (; first < last; first += 1) {
        if ((first->v.mCap - first->v.mBegin) > 1 && first->v.mBegin)
            EASTL_allocator_deallocate(first->v.mBegin);
    }
}



// @ 0x0076e5c0
void SomeObj3::Destroy()
{
    DestroyRecArray(mBegin, mEnd);
    if (mBegin && *(int*)((char*)mBegin - 4) != 0)
        EASTL_allocator_deallocate(mBegin);
}



// @ 0x0076e670
void* BigRecOps::Construct(void* src)
{
    (void)src;
    return this;
}



// @ 0x0076e750
int BigRecOps::CopyFrom(BigRecOps* src)
{
    (void)src;
    return (int)(size_t)this;
}



// @ 0x0076e7a0
void __stdcall DestroyBigRecArray(BigRec2* first, BigRec2* last)
{
    for (; first < last; ++first) {
        VecElem* e = *(VecElem**)((char*)first + 0x24);
        VecElem* b = *(VecElem**)((char*)first + 0x20);
        for (; b < e; b += 1) {
            if ((b->v.mCap - b->v.mBegin) > 1 && b->v.mBegin)
                EASTL_allocator_deallocate(b->v.mBegin);
        }
        void* p = *(void**)((char*)first + 0x20);
        if (p && *(int*)((char*)p - 4) != 0)
            EASTL_allocator_deallocate(p);
        SpVec* v = (SpVec*)((char*)first + 0x10);
        if ((v->mCap - v->mBegin) > 1 && v->mBegin)
            EASTL_allocator_deallocate(v->mBegin);
        v = (SpVec*)first;
        if ((v->mCap - v->mBegin) > 1 && v->mBegin)
            EASTL_allocator_deallocate(v->mBegin);
    }
}



// @ 0x0076e840
int __cdecl CopyBigRecRange(BigRec* first, BigRec* last, BigRec* out)
{
    (void)first; (void)last;
    return (int)(size_t)out;
}



// @ 0x0076e900
void* __cdecl CopyBigRecRange2(void* first, void* last, void* out)
{
    (void)first; (void)last;
    return out;
}



// @ 0x0076e9b0
void* __cdecl CopyBigRecRangeBack(void* first, void* last, void* out)
{
    (void)first; (void)last;
    return out;
}



// @ 0x0076ea60
void* cRTTCheat::Construct()
{
    return this;   // skeleton: cRTTCheat ctor (see partial.txt)
}



// @ 0x0076eb00
void cRTTCheat::Execute(void* args)
{
    (void)args;   // skeleton: cRTTCheat::Execute (see partial.txt)
}


// @ 0x0076ed30
void cRTTCheat_s0076_ed30::ScalarDelete()
{
    DestroyOptionParser(&mParser);
    DestroyCommandBase((cCommandBase*)this);
    EASTL_allocator_deallocate(this);
}

// @ 0x0076ed90
PageInfo_s0076_ed30* PageVec_s0076_ed30::erase(PageInfo_s0076_ed30* first, PageInfo_s0076_ed30* last)
{
    PageInfo_s0076_ed30* newEnd = MoveRange76(last, mEnd, first);
    destroyRange(newEnd, mEnd);
    mEnd -= last - first;
    return first;
}

// @ 0x0076edf0
void __cdecl BigVecInsert(void* self, unsigned pos, unsigned value)
{
    (void)self; (void)pos; (void)value;   // skeleton: 0x3c-element insert with growth (see partial.txt)
}

// @ 0x0076f050
bool __cdecl RTTCheatInit(void* self)
{
    (void)self;   // skeleton: RTT page allocation + cheat registration (see partial.txt)
    return false;
}

// @ 0x0076f280
void __cdecl RTTBigJob(void* self)
{
    (void)self;   // skeleton: 703-byte job setup (see partial.txt)
}
