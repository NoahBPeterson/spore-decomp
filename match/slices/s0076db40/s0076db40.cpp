// Slice s0076db40 (batch w2g3, slice 39).
// SP::cRTTManager page-table accessors plus render-target record helpers. Default flags + SSE2.
#include "types.h"

extern "C" void* EASTL_allocator_allocate(uint32_t n, const char* name, int a, int b, const char* f, int line); // 0x00f473a0
extern "C" void  EASTL_allocator_deallocate(void* p);   // 0x00f47380

extern "C" long _InterlockedExchangeAdd(volatile long* Addend, long Value);
extern "C" long _InterlockedExchange(volatile long* Target, long Value);
extern "C" long _InterlockedIncrement(volatile long* Addend);
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedIncrement)

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

// @ 0x0076de80  memberwise copy of 0x1d records with a 0x20 stride; returns the advanced out.
PageRecord* __cdecl CopyPageRecords(PageRecord* first, PageRecord* last, PageRecord* out)
{
    for (; first != last; ++first, ++out)
        *out = *first;
    return out;
}

// @ 0x0076de20  uninitialized memberwise copy; advances *out and returns the out pointer.
PageRecord* __cdecl UninitCopyPageRecords(PageRecord** out, PageRecord* first, PageRecord* last, PageRecord* dst)
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
    return (PageRecord*)out;
}

// ------------------------------------------------------------------ cRTTManager page table
struct PageInfo {
    void* mData;      // +0x00
    char  pad04[0x24];
    int   mC;         // +0x28
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
    void* GetTextureHandle(int i, int);
    // @ 0x0076dbb0  page texture pointer.
    void* GetTexture(int i, int reserved);
    // @ 0x0076dc00  copy a 4-dword rect for sub-page `sub` into out.
    bool  GetRect(int i, int sub, int* out);
    // @ 0x0076dc70  copy the rect and its (w,h) deltas.
    bool  GetRectSizes(int i, int sub, int* a, int* b, int* c, int* d);
    // @ 0x0076dcf0  copy mA/mB.
    bool  GetAB(int i, int reserved, int* a, int* b);
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
void* cRTTManager::GetTexture(int i, int)
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
bool cRTTManager::GetAB(int i, int, int* a, int* b)
{
    if (i < 0) return false;
    if (i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return false;
    if (mTexturePages.mBegin[i].mRefCount <= 0) return false;
    *a = mTexturePages.mBegin[i].mA;
    *b = mTexturePages.mBegin[i].mB;
    return true;
}

struct RTTRaster {
    unsigned D3D9GetMipLevelSize(unsigned char level);          // 0x011f0000, ret 4
    void FillSpriteTexture(int a, unsigned size, int z);        // 0x011f0440, ret 0xc
};
struct RTTTexRef;
struct IRTTResolver {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12();
    virtual void Resolve(RTTTexRef* t);                         // +0x34
};
struct RTTTexRef {
    RTTRaster* mRaster;     // +0
    unsigned   mFlags;      // +4, bit 0 = raster resolved
};
IRTTResolver* GetRTTResolver();                                 // 0x0067dd60 (cdecl)
// @ 0x0076dd60
bool cRTTManager::FillSprite(int i, int a, int b)
{
    RTTTexRef* t = (RTTTexRef*)mTexturePages.mBegin[i].mTexture;
    if (!(t->mFlags & 1))
        GetRTTResolver()->Resolve(t);
    RTTRaster* r = t->mRaster;
    r->FillSpriteTexture(b, r->D3D9GetMipLevelSize(0), 0);
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
            if (p->mRefCount == 0 && p->mA == a && p->mB == b && p->mC == c) {
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

// @ 0x0076db40
void* cRTTManager::GetTextureHandle(int i, int)
{
    if (i < 0 || i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return 0;
    PageInfo* p = mTexturePages.mBegin + i;
    if (p->mRefCount <= 0) return 0;
    RTTTexRef* t = (RTTTexRef*)p->mTexture;
    if (!(t->mFlags & 1))
        GetRTTResolver()->Resolve(t);
    return t->mRaster;
}

// @ 0x0076e110
void* FUN_0067dd50();                 // 0x0067dd50
void* SP_IDGenerator();               // 0x0067de60
void  FUN_0076d8e0(void* arg);        // 0x0076d8e0
void  GetImageResource();             // 0x00576650
void  FUN_007b0fa0();                 // 0x007b0fa0
bool cRTTManager::AllocateNewPage(int pageId, int w, int h, int depth)
{
    void* mgr = FUN_0067dd50();
    ((void(__thiscall*)(void*))((void**)mgr)[0x1c / 4])(mgr);

    void* resolver = GetRTTResolver();
    int buf[3];
    buf[0] = pageId;
    buf[1] = 0;
    buf[2] = 0x40002a00;
    if (pageId == -1) {
        void* gen = SP_IDGenerator();
        ((void(__thiscall*)(void*, int*, int, int, int, int, int))((void**)gen)[1])
            (gen, buf, 0x2f4e681c, 0, 0, 0x2a, 0);
    }
    void* res = ((void*(__thiscall*)(void*, int, int, int, int, int, int, int, int))
                     ((void**)resolver)[0x3c / 4])
        (resolver, buf[0], buf[2], w, h, 1, 9, depth, 0);
    if (res != 0) {
        ((void(__thiscall*)(void*, void*))GetImageResource)((char*)this + 0x38, res);
        *(int*)((char*)this + 0x28) = depth;
        *(int*)((char*)this + 0x34) = 0;
        *(int*)((char*)this + 0x2c) = w;
        *(int*)((char*)this + 0x30) = h;
        ((void(__thiscall*)(void*, int, int))FUN_007b0fa0)(this, w, h);
        return true;
    }
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
        // AutoRefCount release: atomic decrement at +8, restore when it would drop below 1.
        volatile long* rc = (volatile long*)((char*)mTexture + 8);
        _InterlockedExchangeAdd(rc, -1);
        if (_InterlockedExchangeAdd(rc, 0) < 1)
            _InterlockedIncrement(rc);
        else
            _InterlockedExchangeAdd(rc, 0);
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
    *(void**)this = (void*)0x140e398;
    *(void**)((char*)this + 4) = (void*)0x140e384;
    *(void**)((char*)this + 8) = (void*)0x140e374;
    DestroyRecArray(mBegin, mEnd);
    if (mBegin && *(int*)((char*)mBegin - 4) != 0)
        EASTL_allocator_deallocate(mBegin);
    *(void**)((char*)this + 8) = (void*)0x13ec458;
    *(void**)((char*)this + 4) = (void*)0x13eb394;
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

// 0x0076e610  0x2c-byte object factory (three vtables: +0, +4 and +8; RefCount at +0xc).
// The base-class constructors' vtable stores (GB1 at +4, RefCountVTemplate at +8) are kept as volatile
// stores: the original does not elide them before the final vtables are written.
struct Obj2c {
    void* vt0;          // +0x00
    void* vt4;          // +0x04
    void* vt8;          // +0x08
    int   mRefCount;    // +0x0c
    char  mFlag;        // +0x10
    int   mSize;        // +0x14
    int   f18, f1c, f20;
};
// @ 0x0076e610
Obj2c* __cdecl CreateObj2c()
{
    volatile Obj2c* p = (volatile Obj2c*)EASTL_allocator_allocate(0x2c, "Graphics", 0, 0, 0, 0);
    if (p) {
        p->vt4 = (void*)0x13eb384;
        p->mRefCount = 0;
        p->vt8 = (void*)0x13ec458;
        p->mFlag = 0;
        p->vt0 = (void*)0x140e398;
        p->vt4 = (void*)0x140e384;
        p->vt8 = (void*)0x140e374;
        p->mSize = 0x200;
        p->f18 = 0;
        p->f1c = 0;
        p->f20 = 0;
        return (Obj2c*)p;
    }
    return 0;
}

// @ 0x0076e670
struct Vec20 { void Construct(int count, void* tag); };   // 0x0076e200 (thiscall)
struct VecF  { void Construct(int count, void* tag); };   // 0x004aa350 (thiscall)
void* eastl_DoInsertValue_11e0744(void*, void*, int);     // 0x011e0744 (cdecl)
struct BigRecOps {
    void* Construct(void* src);
    int   CopyFrom(BigRecOps* src);
};
void* BigRecOps::Construct(void* src)
{
    char* s = (char*)src;
    char* t = (char*)this;
    ((Vec20*)t)->Construct((*(int*)(s + 4) - *(int*)s) >> 5, s + 0xc);
    PageRecord* out;
    ((void(__cdecl*)(PageRecord**, PageRecord*, PageRecord*, PageRecord*, PageRecord*))UninitCopyPageRecords)
        (&out, *(PageRecord**)s, *(PageRecord**)(s + 4), *(PageRecord**)t, (PageRecord*)s);
    *(void**)(t + 4) = out;
    ((VecF*)(t + 0x14))->Construct((*(int*)(s + 0x18) - *(int*)(s + 0x14)) >> 2, s + 0x20);
    int size = *(int*)(s + 0x18) - *(int*)(s + 0x14);
    void* p = eastl_DoInsertValue_11e0744(*(void**)(t + 0x14), *(void**)(s + 0x14), size);
    *(void**)(t + 0x18) = (char*)p + (size >> 2) * 4;
    return this;
}

// @ 0x0076e750
int BigRecOps::CopyFrom(BigRecOps* src)
{
    Construct(src);
    char* s = (char*)src;
    char* t = (char*)this;
    *(int*)(t + 0x28) = *(int*)(s + 0x28);
    *(int*)(t + 0x2c) = *(int*)(s + 0x2c);
    *(int*)(t + 0x30) = *(int*)(s + 0x30);
    *(int*)(t + 0x34) = *(int*)(s + 0x34);
    int r = *(int*)(s + 0x38);
    *(int*)(t + 0x38) = r;
    if (r != 0)
        _InterlockedIncrement((volatile long*)(r + 8));
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
struct CObj18 { void* vt; void* f4; int f8, fc, f10, f14; };
struct CaptureJobMsg {
    int f00, f04;
    char f08;
    int f0c, f10, f14;
    void* f18;
    int f1c, f20, f24, f28;
};
void __cdecl RegisterCaptureJob(void* arg)
{
    CObj18* a = (CObj18*)EASTL_allocator_allocate(0x18, "Graphics", 0, 0, 0, 0);
    if (a) {
        a->f4 = (void*)0x13ec458;
        a->f8 = 0;
        a->vt = (void*)0x140e360;
        a->f4 = (void*)0x149bad8;
        a->fc = 0;
        a->f10 = -1;
        a->f14 = -1;
    }
    if (a)
        ((void(__thiscall*)(void*))((void**)a)[0])(a);

    FUN_0076d8e0(arg);

    CObj18* b = (CObj18*)EASTL_allocator_allocate(0x18, "Graphics", 0, 0, 0, 0);
    if (b) {
        b->f10 = 0;
        b->vt = (void*)0x13eb90c;
        _InterlockedExchange((volatile long*)((char*)b + 4), 0);
        b->vt = (void*)0x1452a38;
    }
    if (b)
        ((void(__thiscall*)(void*))((void**)b)[1])(b);

    *(void**)((char*)b + 8) = a;

    CaptureJobMsg msg;
    msg.f00 = 1; msg.f04 = 0; msg.f08 = 0; msg.f0c = 0; msg.f10 = 0;
    msg.f14 = 0x3d037f1; msg.f18 = b; msg.f1c = 0; msg.f20 = 0; msg.f24 = 0; msg.f28 = 0;

    void* r = ((void*(__thiscall*)(void*, int, void*))((void**)a)[0x10 / 4])(a, 0, &msg);
    void* s = FUN_0067dd50();
    ((void(__thiscall*)(void*, void*))((void**)s)[0x78 / 4])(s, r);

    if (b)
        ((void(__thiscall*)(void*))((void**)b)[2])(b);
    ((void(__thiscall*)(void*))((void**)a)[1])(a);
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

// ---- cRTTCheat::Execute support (0x0076eb00)
namespace EA { namespace ArgScript {
struct cArguments;
struct cIParser;
// 0x0083b9d0  cArgumentSpec::Parse(cArguments*, cIParser*)
struct cArgumentSpec {
    void Parse(cArguments* args, cIParser* parser);
};
} }  // namespace EA::ArgScript

// 0x00841000  EA::ArgScript::Output(cIParser*, const char*, ...)
namespace EA { namespace ArgScript {
void Output(cIParser* parser, const char* fmt, ...);
} }  // namespace EA::ArgScript

// 0x007ae960  FlagHolder::IsSet() const
struct FlagHolder {
    unsigned char IsSet() const;
};

// 0x0076d820  RasterFormatSize(w, h, fmt)
int __cdecl RasterFormatSize(int width, int height, int format);

// raster view for the default camera/zbuffer rasters
namespace rw { namespace graphics {
struct Raster {
    int            m_format;    // +0x00
    char           pad04[8];
    uint16_t       m_width;     // +0x0c
    uint16_t       m_height;    // +0x0e
    uint32_t D3D9GetMipLevelSize(unsigned char level);   // 0x011f0000, thiscall ret 4
};
} }  // namespace rw::graphics

// page record used by the RTT page vector ([this+0xd8])
struct RTTPageRec {
    char     pad00[0x28];
    uint16_t mType;      // +0x28
    uint16_t mWidth;     // +0x2c
    uint16_t mHeight;    // +0x30
    uint16_t mAllocs;    // +0x34
    char     pad36[6];
};
struct RTTPageVec {
    char        pad00[0x18];
    RTTPageRec* mBegin;  // +0x18
    RTTPageRec* mEnd;    // +0x1c
};
struct IRTTRelease {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual void Release();                              // +0x3c
};

// the object at [this+0xd8]: vtable at +0, page vector at +0x18
struct RTTPageHolder {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual void Release();                              // +0x3c
    RTTPageRec* mBegin;   // +0x18
    RTTPageRec* mEnd;     // +0x1c
};

// cRTTCheat layout used by Execute (thiscall, 1 stack arg).
struct cRTTCheatLayout {
    char                         pad00[4];
    EA::ArgScript::cIParser*     mParser;     // +0x04
    char                         pad08[8];
    EA::ArgScript::cArgumentSpec mSpec;       // +0x10
    char                         pad14[0x6c];
    unsigned                     mFlags;      // +0x80, bit0 = list pages, bit1 = release
    char                         pad84[0x54];
    RTTPageHolder*               mPages;      // +0xd8
};
typedef char sizeof_check_cRTTCheat[(sizeof(cRTTCheatLayout) == 0xdc) ? 1 : -1];

rw::graphics::Raster* g_defaultCameraRaster;   // 0x015d0838
rw::graphics::Raster* g_defaultZBufferRaster;  // 0x015d083c
extern "C" const float g_kBytesToMB;           // 0x0140e4b0 = 9.536743e-07f

// @ 0x0076eb00
void cRTTCheat::Execute(void* args)
{
    cRTTCheatLayout* self = (cRTTCheatLayout*)this;
    self->mSpec.Parse((EA::ArgScript::cArguments*)args, self->mParser);
    if (self->mFlags & 1) {
        unsigned count = (unsigned)((self->mPages->mEnd - self->mPages->mBegin) / 0x3c);
        count &= 0xffff;
        EA::ArgScript::Output(self->mParser, "%d render target pages allocated:\n", count);

        int total = 0;
        int freed = 0;
        rw::graphics::Raster* r = g_defaultCameraRaster;
        if (r != 0) {
            unsigned size = r->D3D9GetMipLevelSize(0);
            total = (int)size;
            EA::ArgScript::Output(self->mParser,
                " DebugName: %hs, page %d, %d x %d, type %d, allocs %d, used %d, size %d K\n",
                "MainColor", 0, (int)r->m_width, (int)r->m_height, (int)r->m_format,
                1, 1, (size + 0x3ff) >> 10);
        }
        r = g_defaultZBufferRaster;
        if (r != 0) {
            unsigned size = r->D3D9GetMipLevelSize(0);
            total += (int)size;
            EA::ArgScript::Output(self->mParser,
                " DebugName: %hs, page %d, %d x %d, type %d, allocs %d, used %d, size %d K\n",
                "MainDepth", 0, (int)r->m_width, (int)r->m_height, (int)r->m_format,
                1, 1, (size + 0x3ff) >> 10);
        }
        for (int i = 0; i < (int)count; ++i) {
            RTTPageRec* rec = self->mPages->mBegin + i;
            int size = RasterFormatSize(rec->mWidth, rec->mHeight, rec->mType);
            total += size;
            if (rec->mAllocs == 0)
                freed += size;
            unsigned char used = ((FlagHolder*)rec)->IsSet();
            EA::ArgScript::Output(self->mParser,
                " DebugName: %hs, page %d, %d x %d, type %d, allocs %d, used %d, size %d K\n",
                0, i, (int)rec->mWidth, (int)rec->mHeight, (int)rec->mType, (int)rec->mAllocs,
                (int)used, (size + 0x3ff) >> 10);
        }
        EA::ArgScript::Output(self->mParser, "Total RTT pages: %1.1f MB freed: %1.1f MB\n",
            (double)((float)total * g_kBytesToMB), (double)((float)freed * g_kBytesToMB));
    }
    if ((self->mFlags >> 1) & 1)
        self->mPages->Release();
}
