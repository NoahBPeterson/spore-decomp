// Slice s0076db40 (batch w2g3, slice 39).
// SP::cRTTManager page-table accessors plus render-target record helpers. Default flags + SSE2.
#include "types.h"

extern "C" void* EASTL_allocator_allocate(uint32_t n, const char* name, int a, int b, const char* f, int line); // 0x00f473a0
extern "C" void  EASTL_allocator_deallocate(void* p);   // 0x00f47380

// ------------------------------------------------------------------ page records
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

// @ 0x0076de80  memberwise copy of 0x1d records with a 0x20 stride.
void __cdecl CopyPageRecords(PageRecord* first, PageRecord* last, PageRecord* out)
{
    for (; first != last; ++first, ++out)
        *out = *first;
}

// @ 0x0076de20  uninitialized memberwise copy; advances *out.
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

// ------------------------------------------------------------------ cRTTManager page table
struct PageInfo {
    void* mData;      // +0x00
    char  pad04[0x28];
    int   mA;         // +0x2c
    int   mB;         // +0x30
    int   mRefCount;  // +0x34
    void* mTexture;   // +0x38
};
struct PageVec { PageInfo* mBegin; PageInfo* mEnd; PageInfo* mCap; };
struct cRTTManager {
    char    pad[0x18];
    PageVec mTexturePages;   // +0x18

    // @ 0x0076db40  lazily resolve the raster from a page's texture instance.
    void* GetTextureHandle(int i);
    // @ 0x0076dbb0  page texture pointer.
    void* GetTexture(int i);
    // @ 0x0076dc00  copy a 4-dword rect for sub-page `sub` into out.
    bool  GetRect(int i, int sub, int* out);
    // @ 0x0076dc70  copy the rect and its (w,h) deltas.
    bool  GetRectSizes(int i, int sub, int* a, int* b, int* c, int* d);
    // @ 0x0076dcf0  copy mA/mB.
    bool  GetAB(int i, int* a, int* b);
    // @ 0x0076dd60  fill the page raster and a sprite texture.
    bool  FillSprite(int i, int a, int b);
    // @ 0x0076ddb0  find a page by (mA,mB,refcount == criteria); returns index.
    bool  FindPage(int a, int b, int c, int* out);
    // @ 0x0076e040  per-page rectangle scale (1/pageSize) in float.
    bool  GetScaledRect(int i, int sub, float* a, float* b);
    // @ 0x0076e110  allocate a new texture page.
    bool  AllocateNewPage(int pageId, int w, int h, int depth);
};

// @ 0x0076dbb0
void* cRTTManager::GetTexture(int i)
{
    if (i < 0) return 0;
    if (i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return 0;
    if (mTexturePages.mBegin[i].mRefCount <= 0) return 0;
    return mTexturePages.mBegin[i].mTexture;
}

// @ 0x0076dc00
bool cRTTManager::GetRect(int i, int sub, int* out)
{
    if (i < 0) return false;
    if (i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return false;
    if (mTexturePages.mBegin[i].mRefCount <= 0) return false;
    int* src = (int*)((char*)mTexturePages.mBegin[i].mData + sub * 0x20);
    out[0] = src[0]; out[1] = src[1]; out[2] = src[2]; out[3] = src[3];
    return true;
}

// @ 0x0076dc70
bool cRTTManager::GetRectSizes(int i, int sub, int* a, int* b, int* c, int* d)
{
    if (i < 0) return false;
    if (i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return false;
    if (mTexturePages.mBegin[i].mRefCount <= 0) return false;
    int* src = (int*)((char*)mTexturePages.mBegin[i].mData + sub * 0x20);
    *a = src[0]; *b = src[1]; *c = src[2] - src[0]; *d = src[3] - src[1];
    return true;
}

// @ 0x0076dcf0
bool cRTTManager::GetAB(int i, int* a, int* b)
{
    if (i < 0) return false;
    if (i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return false;
    if (mTexturePages.mBegin[i].mRefCount <= 0) return false;
    *a = mTexturePages.mBegin[i].mA;
    *b = mTexturePages.mBegin[i].mB;
    return true;
}

// @ 0x0076dd60
extern int RasterFill(void* raster, int a);
extern int FillSpriteTexture(void* dst, int a);
bool cRTTManager::FillSprite(int i, int a, int b)
{
    void* tex = mTexturePages.mBegin[i].mTexture;
    if (((unsigned char*)tex)[4] & 1)
        ;
    else {
        // lazily create the raster on first use
    }
    int r = RasterFill(*(void**)tex, 0);
    FillSpriteTexture((void*)b, r);
    return true;
}

// @ 0x0076ddb0
bool cRTTManager::FindPage(int a, int b, int c, int* out)
{
    unsigned count = (unsigned)((mTexturePages.mEnd - mTexturePages.mBegin));
    unsigned idx = 0;
    if (count != 0) {
        PageInfo* p = mTexturePages.mBegin;
        do {
            if (p->mB == 0 && p->mA == a && p->mB == b && p->mRefCount == c) {
                *out = idx;
                return true;
            }
            ++idx;
            ++p;
        } while (idx < count);
    }
    return false;
}

// @ 0x0076e040
bool cRTTManager::GetScaledRect(int i, int sub, float* a, float* b)
{
    if (i < 0) return false;
    if (i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return false;
    if (mTexturePages.mBegin[i].mRefCount <= 0) return false;
    PageInfo* p = mTexturePages.mBegin + i;
    int* src = (int*)((char*)p->mData + sub * 0x20);
    float sx = 1.0f / (float)p->mA;
    float sy = 1.0f / (float)p->mB;
    a[0] = sx * (float)src[0];
    a[1] = sx * (float)src[1];
    b[0] = sy * (float)src[2];
    b[1] = sy * (float)src[3];
    return true;
}

// @ 0x0076db40  (skeleton; see partial.txt)
void* cRTTManager::GetTextureHandle(int i)
{
    (void)i;
    return 0;
}

// @ 0x0076e110  (skeleton; see partial.txt)
extern int RasterCreate();
bool cRTTManager::AllocateNewPage(int pageId, int w, int h, int depth)
{
    (void)pageId; (void)w; (void)h; (void)depth;
    return false;
}

// ------------------------------------------------------------------ empty-vector dealloc
struct SpVec { char* mBegin; char* mEnd; char* mCap; void DeallocateSelf(); };
void SpVec::DeallocateSelf()
{
    if ((mCap - mBegin) > 1 && mBegin)
        EASTL_allocator_deallocate(mBegin);
}

// @ 0x0076e1e0  SpVec::DeallocateSelf above is the byte-exact match for this VA.

// ------------------------------------------------------------------ 0x20-stride element array free
struct VecElem { int pad0; SpVec v; int pad2[4]; };
void __stdcall FreeElemArray(VecElem* first, VecElem* last);
void __stdcall FreeElemArray(VecElem* first, VecElem* last)
{
    for (; first < last; first += 1) {
        if ((first->v.mCap - first->v.mBegin) > 1 && first->v.mBegin)
            EASTL_allocator_deallocate(first->v.mBegin);
    }
}

// @ 0x0076e430  FreeElemArray above is the byte-exact match for this VA.

// ------------------------------------------------------------------ record-array helpers
// @ 0x0076e2c0  single 0x3c-record destructor (refcounted texture + two vectors).
extern void ReleaseTextureRef(void* tex);
struct Rec3c {
    char  pad00[0x38];
    void* mTexture;   // +0x38
    void  DestroyOne();
};
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

// @ 0x0076e5c0
struct SomeObj3 {
    char pad[0x18];
    Rec3c* mBegin;    // +0x18
    Rec3c* mEnd;      // +0x1c
    void Destroy();
};
void SomeObj3::Destroy()
{
    DestroyRecArray(mBegin, mEnd);
    if (mBegin && *(int*)((char*)mBegin - 4) != 0)
        EASTL_allocator_deallocate(mBegin);
}

// ------------------------------------------------------------------ record copy/relocate
struct BigRec {
    char pad00[0x14];
    char padVec[0x14];   // +0x14 vector<float,sp_vector_allocator>
    char pad28[0x10];
    void* mRef;          // +0x38
};
void CopyBigRec(BigRec* dst, BigRec* src);        // 0x0076e4b0
void AssignFloatVec(void* dst, void* src);        // 0x0050d4e0

// @ 0x0076e670  (skeleton; see partial.txt)
struct BigRecOps {
    void* Construct(void* src);
    int   CopyFrom(BigRecOps* src);
};
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

// @ 0x0076e7a0  range destructor for a 0x38-byte record array.
struct BigRec2 {
    char pad00[0x38];
};
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

// @ 0x0076e840  (skeleton; see partial.txt)
int __cdecl CopyBigRecRange(BigRec* first, BigRec* last, BigRec* out)
{
    (void)first; (void)last;
    return (int)(size_t)out;
}

// @ 0x0076e900  (skeleton; see partial.txt)
void* __cdecl CopyBigRecRange2(void* first, void* last, void* out)
{
    (void)first; (void)last;
    return out;
}

// @ 0x0076e9b0  (skeleton; see partial.txt)
void* __cdecl CopyBigRecRangeBack(void* first, void* last, void* out)
{
    (void)first; (void)last;
    return out;
}

// ------------------------------------------------------------------ big bodies
// @ 0x0076dee0
void __cdecl RegisterCaptureJob(void* arg)
{
    (void)arg;   // skeleton: viewer + behaviour-message job registration (see partial.txt)
}

// @ 0x0076ea60
struct cRTTCheat {
    void* Construct();
    void  Execute(void* args);
};
void* cRTTCheat::Construct()
{
    return this;   // skeleton: cRTTCheat ctor (see partial.txt)
}

// @ 0x0076eb00
void cRTTCheat::Execute(void* args)
{
    (void)args;   // skeleton: cRTTCheat::Execute (see partial.txt)
}
