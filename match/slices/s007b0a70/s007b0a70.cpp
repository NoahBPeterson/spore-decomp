// Slice s007b0a70 — graphics texture/vector helpers (eastl vector of 0x20-byte nodes,
// image registration and DXT compression wrappers). Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// ---------------------------------------------------------------------------
// external helpers (definitions elsewhere; call targets are masked relocs)
// ---------------------------------------------------------------------------
void  __cdecl EAFree(void* p);                                    // 0x00F47380
void* __cdecl EAAlloc(unsigned n, const char* name, int a, int b, const char* f, int l); // 0x00F473A0
void  __cdecl DestroyElems(void* first, void* last);              // 0x00B007F0
void** __cdecl CopyIntrusive(void** first, void** last, void** dest); // 0x006F43E0
void  __cdecl RemoveIf(void* a, void* b, void* c);                // 0x0076DE80
void* __cdecl MoveNodes(void* a, void* b, void* c);               // 0x007AF5D0
void  __cdecl MoveNodes2(void* a, void* b, void* c);              // 0x007AF6D0
void* __cdecl DoCopy4(void* first, void* last, void* dest);       // 0x006782C0

void** CopyRefRange4(void** first, void** last, void** dest);     // 0x007B0040

struct PVec { void** b; void** e; void DestroyRange(void* first, void* last); }; // 0x0070F520 __thiscall
struct UVec {
    unsigned* b; unsigned* e; unsigned* c;
    void DoInsertValue(unsigned* pos, const unsigned& v);          // 0x004558A0 __thiscall
    void reserve(unsigned n);                                      // 0x004E0880 __thiscall
    void push_back(const unsigned& v) {
        unsigned* p = e;
        if (p < c) { e = p + 1; if (p) *p = v; }
        else DoInsertValue(p, v);
    }
    void push_val(unsigned v) {
        unsigned* p = e;
        if (p < c) { e = p + 1; if (p) *p = v; }
        else DoInsertValue(p, v);
    }
};
void* __cdecl MemMove(void* d, const void* s, unsigned n);          // 0x011E0744 (CRT memmove thunk)
void  __cdecl UninitCopy(struct T20** out, struct T20* a, struct T20* b, struct T20* c, struct T20* d); // 0x0076DE20
void  __cdecl FillRange(struct T20* a, struct T20* b, const struct T20* v); // 0x007AF620
void  __cdecl FillN(struct T20* d, unsigned n, const struct T20* v);        // 0x007AF670
void  __cdecl FillN(struct T20* d, unsigned n, const struct T20* v, struct T20* extra); // 0x007AF670

struct T20 {
    int a,b,c,d,e,f,g; char h;
    T20& operator=(const T20& o) { a=o.a;b=o.b;c=o.c;d=o.d;e=o.e;f=o.f;g=o.g;h=o.h; return *this; }
};

struct C20;

// helpers defined further down
void FUN_007b0920_helper(C20* self, T20* pos, int count);         // 0x007B0920

struct C20 {
    T20* begin;  T20* end;  T20* cap;                             // +0x0
    PVec v0;                                                      // +0xc
    UVec fv;                                                      // +0x14 free list
    PVec v2;                                                      // +0x20
    void grow(T20* p, const T20& v);                              // 0x007b0a70
    void push_back(const T20& v);                                 // 0x007b0f40
    void resize(int n);                                           // 0x007b1040
    int  Alloc();                                                 // 0x007b10a0
    void clear();                                                 // 0x007b1950
    void InsertN(T20* pos, unsigned n, const T20* v);             // 0x007b0be0
    void Reap(int idx);                                           // 0x007b0e60
    void AddNode(int a, int b);                                   // 0x007b0fa0
    void Reserve(unsigned n);                                     // 0x007b0890
};

// 4-byte-element vector used by the container helpers
struct C4 {
    void** begin; void** end; void** cap;
    void assign(void** first, void** last, void* tag);            // 0x007b0da0 (ret 0xc; tag unused)
};

// ---------------------------------------------------------------------------
// @ 0x007b0f40  eastl::vector<T20>::push_back
// ---------------------------------------------------------------------------
void C20::push_back(const T20& v)
{
    T20* p = end;
    if (p < cap) {
        end = p + 1;
        if (p)
            *p = v;
    } else {
        grow(p, v);
    }
}

// ---------------------------------------------------------------------------
// @ 0x007b0a70  eastl::vector<T20>::DoInsertValue / grow-on-insert
// ---------------------------------------------------------------------------
void C20::grow(T20* pos, const T20& v)
{
    T20* e = end;
    if (e != cap) {
        T20* src = pos;
        if (pos <= &v && &v < e)
            src = (T20*)((char*)&v + 0x20);
        if (e) {
            e->a = e[-1].a; e->b = e[-1].b; e->c = e[-1].c; e->d = e[-1].d;
            e->e = e[-1].e; e->f = e[-1].f; e->g = e[-1].g; e->h = e[-1].h;
        }
        MoveNodes2(pos, (char*)e - 0x20, e);
        *pos = v;
        end = (T20*)((char*)e + 0x20);
        return;
    }
    int n = (int)(e - begin);
    n = (n == 0) ? 1 : n * 2;
    T20* p = n ? (T20*)EAAlloc(n << 5, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    T20* q = (T20*)MoveNodes(begin, pos, p);
    if (q)
        *q = v;
    T20* ne = (T20*)MoveNodes(pos, e, (char*)q + 0x20);
    if (begin && *((int*)begin - 1))
        EAFree(begin);
    end = ne;
    cap = (T20*)((char*)p + n*0x20);
    begin = p;
}

// ---------------------------------------------------------------------------
// @ 0x007b0be0  eastl::vector<T20>::DoInsertValues(pos, n, value)
// ---------------------------------------------------------------------------
void C20::InsertN(T20* pos, unsigned n, const T20* v)
{
    unsigned n0 = n;
    T20* e = end;
    if (n0 <= (unsigned)(cap - e)) {
        if (n0 > 0) {
            T20 tmp;
            unsigned after = (unsigned)(e - pos);
            T20* e2 = end;
            tmp = *v;
            if (n0 < after) {
                T20* src = e2 - n0;
                UninitCopy(&pos, src, e2, e2, pos);
                end += n0;
                MoveNodes2(pos, src, e2);
                FillRange(pos, pos + n0, &tmp);
            } else {
                FillN(e2, n0 - after, &tmp);
                end += n0 - after;
                UninitCopy(&pos, pos, e2, end, pos);
                end += after;
                FillRange(pos, e2, &tmp);
            }
        }
    } else {
        unsigned cnt = (unsigned)(e - begin);
        unsigned nc = cnt ? cnt * 2 : 1;
        n = cnt + n0;
        if (n < nc) n = nc;
        T20* p = n ? (T20*)EAAlloc(n << 5, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        T20* q = (T20*)MoveNodes(begin, pos, p);
        FillN(q, n0, v, pos);
        T20* ne = (T20*)MoveNodes(pos, end, q + n0);
        if (begin && ((int*)begin)[-1])
            EAFree(begin);
        begin = p;
        end = ne;
        cap = p + n;
    }
}

// ---------------------------------------------------------------------------
// @ 0x007b0da0  eastl::vector<Ref4>::assign (4-byte elements)
// ---------------------------------------------------------------------------
void C4::assign(void** first, void** last, void* tag)
{
    int n = (int)((char*)last - (char*)first) >> 2;
    if ((int)((char*)cap - (char*)begin) >> 2 < n) {
        void** p = (void**)DoCopy4(first, last, 0);   // reuse as grow helper FUN_007b0920
        DestroyElems(begin, end);
        if (begin && *((int*)begin - 1))
            EAFree(begin);
        void** ne = (void**)((char*)p + n*4);
        begin = p; end = ne; cap = ne;
        return;
    }
    int cur = (int)((char*)end - (char*)begin) >> 2;
    if (n <= cur) {
        void** ne = (void**)DoCopy4(first, last, begin);
        DestroyElems(ne, end);
        end = ne;
        return;
    }
    void** mid = (void**)((char*)first + cur*4);
    DoCopy4(first, mid, begin);
    CopyRefRange4(mid, last, end);
    end = (void**)((char*)end + (n - cur)*4);
}

// ---------------------------------------------------------------------------
// @ 0x007b1040  eastl::vector<T20>::resize(n)
// ---------------------------------------------------------------------------
void C20::resize(int n)
{
    int cnt = (int)(end - begin);
    if (n > cnt) {
        T20 tmp;
        InsertN(end, n - cnt, &tmp);
    } else {
        T20* ne = begin + n;
        RemoveIf(end, end, ne);
        end = (T20*)((char*)end - ((char*)end - (char*)ne));
    }
}

// ---------------------------------------------------------------------------
// @ 0x007b10a0  allocate a slot index (reuse a free-list entry if present)
// ---------------------------------------------------------------------------
int C20::Alloc()
{
    if (fv.b != fv.e) {
        int v = fv.e[-1];
        fv.e--;
        return v;
    }
    int n = (int)(end - begin);
    resize(n + 1);
    return n;
}

// ---------------------------------------------------------------------------
// @ 0x007b1950  clear two 4-byte vectors at +0xc / +0x20
// ---------------------------------------------------------------------------
void C20::clear()
{
    void** b1 = v0.b;
    void** e1 = v0.e;
    PVec* p = &v0;
    void** r = CopyIntrusive(e1, e1, b1);
    p->DestroyRange(r, p->e);
    p->e -= (e1 - b1);
    void** e2 = v2.e;
    p = &v2;
    void** b2 = p->b;
    r = CopyIntrusive(e2, e2, b2);
    p->DestroyRange(r, p->e);
    p->e -= (e2 - b2);
}

// ---------------------------------------------------------------------------
// remaining entry points (best-effort reconstruction)
// ---------------------------------------------------------------------------
// @ 0x007b0e60  (tree-node reap: fold redundant nodes and push their indices on a free list)
void C20::Reap(int idx)
{
    unsigned a;
    begin[idx].h = 0;
    int p = begin[idx].e;
    while (p >= 0) {
        a = begin[p].f;
        idx = begin[p].g;
        if (begin[a].f >= 0) return;
        if (begin[a].h) return;
        if (begin[idx].f >= 0) return;
        if (begin[idx].h) return;
        begin[p].f = -1;
        begin[p].g = -1;
        fv.push_back(a);
        fv.push_back(idx);
        p = begin[p].e;
    }
}

// @ 0x007b0fa0  (build a T20 from two ints and push it)
void C20::AddNode(int a, int b)
{
    T20* b0 = begin;
    T20* e0 = end;
    RemoveIf(e0, e0, b0);
    end -= (e0 - b0);
    UVec* f = &fv;
    unsigned* fe = f->e;
    unsigned* fb = f->b;
    MemMove(fb, fe, (char*)f->e - (char*)fe);
    f->e -= (fe - fb);
    Reserve(16);
    f->reserve(16);
    T20 t;
    t.a = 0; t.b = 0; t.c = a; t.d = b; t.e = -1; t.f = -1; t.g = -1; t.h = 0;
    push_back(t);
}

// ---------------------------------------------------------------------------
// object model for the texture / DXT job code (layouts from the dev PDB: SP::cJob, SP::cTexturePreload)
// ---------------------------------------------------------------------------
extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

void* operator new(unsigned int, const char*, int, int, int, int);     // 0x00F473A0
void  operator delete(void*, const char*, int, int, int, int);

struct IRc { virtual int AddRef(); virtual int Release(); };           // EA::COM::IUnknown32 shape (slots 0,1)
struct AtomicLong {
    volatile long v;
    AtomicLong() { _InterlockedExchange(&v, 0); }
};
struct RcTpl {                                                          // EA::RefCountTemplate<int>
    virtual int AddRef(); virtual int Release();
    AtomicLong mRefCount;
};
struct ICom { virtual long QueryInterface(); virtual int AddRef(); virtual int Release(); };

template<class T> struct RcPtr {
    T* p;
    void operator=(T* q) {
        T* old = p;
        if (q != old) {
            if (q) q->AddRef();
            p = q;
            if (old) old->Release();
        }
    }
};
template<class T> struct AutoRC {
    T* p;
    AutoRC(T* q) : p(q) { if (p) p->AddRef(); }
    ~AutoRC() { if (p) p->Release(); }
};

struct Img : IRc { uint32_t pad[6]; int mWidth; int mHeight; int mFormat; void* mData; };   // +0x1c/+0x20/+0x24/+0x28
struct ImgA : Img { ImgA(int w, int h); };                              // 0x007A9E10 (format 1 chain)
struct ImgB : Img { ImgB(int w, int h); };                              // 0x004328D0

struct ImgVec { Img** b; Img** e; };                                    // the caller's image list

struct cJob {
    void* mpCallback;           // +0x0
    void* mpCallbackData;       // +0x4
    IRc*  mpExtraObject;        // +0x8
    char* mpDebugName;          // +0xc
    int   mPriority;            // +0x10
    int   mStatus;              // +0x14
    unsigned mThreadAffinity;   // +0x18
    int   mSlot;                // +0x1c
    void* mpReturnValue;        // +0x20
    void* mpCleanupReturnValue; // +0x24
    int  Release();             // 0x00690120
    void Attach(IRc* d);        // 0x0068F9B0
    void GetStatus() const;     // 0x006909B0
    void Wait();                // 0x006926B0
};
struct AutoJob {
    cJob* p;
    AutoJob() : p(0) {}
    ~AutoJob() { if (p) p->Release(); }
    void Reset() { cJob* t = p; if (t) { p = 0; t->Release(); } }
};
struct VecDst { void** Assign(struct MipVec* other); };                // 0x007B0980 __thiscall (eastl vector assignment)
struct Sched {                                                          // job scheduler singleton
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual bool Acquire(AutoJob* out);                                 // vtable +0x10
};
Sched* __cdecl GetSched();                                              // 0x0068F4D0
void   __cdecl DispatchAsync(cJob* j);                                  // 0x006B47A0
bool   __cdecl FUN_007b0020();
bool   __cdecl FUN_007b03d0();

struct MipVec {
    RcPtr<Img>* b; RcPtr<Img>* e; RcPtr<Img>* c;
    MipVec() : b(0), e(0), c(0) {}
    void resize(unsigned n);                                            // 0x00421BF0 __thiscall
};
// MSVC lays the non-polymorphic base (the vector) after the two polymorphic ones but constructs it first.
struct MipChain : MipVec, IRc, RcTpl {                                  // 0x20 bytes, vtables 0x140FC04/0x140FC00
    uint32_t pad[2];
    virtual int AddRef(); virtual int Release();
};
struct DxtData : IRc, RcTpl {                                           // 0x1c bytes, vtables 0x140FBDC/0x140FBD8
    RcPtr<MipChain> chain;                                              // +0xc
    int   mMessage;                                                     // +0x10
    RcPtr<ICom> mHandler;                                               // +0x14
    char  mFlag;                                                        // +0x18
    DxtData() { chain.p = 0; mHandler.p = 0; }
    virtual int AddRef(); virtual int Release();
};
struct Owner { void* vt0; IRc sub; };                                   // refcount interface lives at +4
struct TexVec : C4 { TexVec() { begin = 0; end = 0; cap = 0; } };
struct TexData : TexVec, IRc, RcTpl {                                   // 0x3c bytes, vtables 0x140FC18/0x140FC14
    uint32_t pad[2];
    Owner* mOwner;                                                      // +0x20
    int mSize[3];                                                       // +0x24
    int mFmt; int mBlockBytes; int mBytesPerPixel;                      // +0x30
    TexData() { mOwner = 0; mSize[0] = 0; mSize[1] = 0; mSize[2] = 0; }
    bool Upload(int flag);                                              // 0x007AF720 __thiscall
    virtual int AddRef(); virtual int Release();
};

// ---------------------------------------------------------------------------
// @ 0x007b10d0  SP::RegisterImagesAsTexture
// ---------------------------------------------------------------------------
bool SP_RegisterImagesAsTexture(ImgVec* images, int* size, Owner* owner, bool async)
{
    Img** it = images->b;
    int n = (int)(images->e - it);
    Img* first = *it;
    unsigned w = first->mWidth;
    if (w != (unsigned)first->mHeight || (w & (w - 1)) != 0)
        return false;
    for (int i = 1; i < n; ++i) {
        Img* cur = it[i];
        Img* prev = it[i - 1];
        if (cur->mFormat != prev->mFormat || cur->mWidth != prev->mWidth / 2 || cur->mHeight != prev->mHeight / 2)
            return false;
    }
    int fmt = 0, blockBytes = 0, bpp = 0;
    switch (first->mFormat) {
    case 1: fmt = 0x1c; bpp = 1; break;
    case 2: fmt = 0x15; bpp = 4; break;
    case 4: fmt = 0x31545844; blockBytes = 8; break;
    case 5: fmt = 0x33545844; blockBytes = 16; break;
    case 6: fmt = 0x35545844; blockBytes = 16; break;
    default: return false;
    }
    TexData* o = new("Graphics", 0, 0, 0, 0) TexData;
    AutoRC<TexData> h((TexData*)o);
    o->assign((void**)images->b, (void**)images->e, images);
    {
        Owner* old = o->mOwner;
        if (owner != old) {
            if (owner) owner->sub.AddRef();
            o->mOwner = owner;
            if (old) old->sub.Release();
        }
    }
    o->mSize[0] = size[0];
    o->mSize[1] = size[1];
    o->mSize[2] = size[2];
    o->mFmt = fmt;
    o->mBlockBytes = blockBytes;
    o->mBytesPerPixel = bpp;
    bool ok = false;
    if (async) {
        AutoJob job;
        Sched* s = GetSched();
        job.Reset();
        if (s->Acquire(&job)) {
            job.p->Attach(o);
            job.p->mpCallback = (void*)&FUN_007b0020;
            job.p->mpCallbackData = o;
            job.p->mThreadAffinity = 4;
            DispatchAsync(job.p);
            job.p->GetStatus();
            ok = true;
        }
    } else {
        ok = o->Upload(0);
    }
    return ok;
}

// ---------------------------------------------------------------------------
// @ 0x007b13b0  (create a DXT / mip-chain compress job for an image)
// ---------------------------------------------------------------------------
bool FUN_007b13b0(Img* img, cJob** out, char flag)
{
    unsigned w = img->mWidth;
    if (w != (unsigned)img->mHeight || (w & (w - 1)) != 0)
        return false;
    if ((flag != 0 || img->mFormat != 1) && img->mFormat != 2)
        return false;
    int mips = 0;
    for (int t = (int)w; t != 0; t >>= 1)
        ++mips;
    AutoJob job;
    Sched* s = GetSched();
    job.Reset();
    if (s->Acquire(&job)) {
    MipChain* mc = new("Graphics", 0, 0, 0, 0) MipChain;
    AutoRC<MipChain> list(mc);
    list.p->resize(mips);
    list.p->b[0] = img;
    for (int i = 1; i < mips; ++i) {
        Img* src = list.p->b[i - 1].p;
        Img* r;
        if (img->mFormat == 1)
            r = new("Graphics", 0, 0, 0, 0) ImgA(src->mWidth / 2, src->mHeight / 2);
        else
            r = new("Graphics", 0, 0, 0, 0) ImgB(src->mWidth / 2, src->mHeight / 2);
        list.p->b[i] = r;
    }
    DxtData* d = new("Graphics", 0, 0, 0, 0) DxtData;
    AutoRC<DxtData> data(d);
    data.p->chain = list.p;
    data.p->mMessage = 0;
    ICom* t = data.p->mHandler.p;
    if (t) {
        data.p->mHandler.p = 0;
        t->Release();
    }
    data.p->mFlag = flag;
    job.p->Attach(data.p);
    job.p->mSlot = 1;
    job.p->mpCallback = (void*)&FUN_007b03d0;
    job.p->mpCallbackData = data.p;
    job.p->mThreadAffinity = 1;
    *out = job.p;
    job.p = 0;
    return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x007b1710  SP::DXTCompress  /  @ 0x007b1830 (same with flag = 1)
// ---------------------------------------------------------------------------
bool SP_DXTCompress(Img* image, VecDst* outImages, void* message, ICom* handler)
{
    AutoJob job;
    if (!FUN_007b13b0(image, &job.p, 0))
        return false;
    DxtData* d = (DxtData*)job.p->mpExtraObject;
    d->mMessage = (int)message;
    d->mHandler = handler;
    MipVec* v = d->chain.p;
    outImages->Assign(v);
    job.p->GetStatus();
    if (!message) {
        job.p->Wait();
        void* r = job.p->mpReturnValue;
        return r == d->chain.p;
    }
    return true;
}

// @ 0x007b1830  DXTCompress variant (flag = 1)
bool FUN_007b1830(Img* image, VecDst* outImages, void* message, ICom* handler)
{
    AutoJob job;
    if (!FUN_007b13b0(image, &job.p, 1))
        return false;
    DxtData* d = (DxtData*)job.p->mpExtraObject;
    d->mMessage = (int)message;
    d->mHandler = handler;
    MipVec* v = d->chain.p;
    outImages->Assign(v);
    job.p->GetStatus();
    if (!message) {
        job.p->Wait();
        void* r = job.p->mpReturnValue;
        return r == d->chain.p;
    }
    return true;
}

// @ 0x007b0040 is provided by the s007af8b0 TU; this slice only needs the declaration.
