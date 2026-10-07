// Slice 5: nSPSkinner texture/refcount helpers plus paint-system ctor and a large render job.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

void  EASTL_allocator_deallocate(void* p);                         // 0x00f47380
void* EA_alloc(unsigned size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void  Memset32(void* dst, int value, int count);                   // 0x0092cb00

extern void* g_vtblSimCreatureAbility;   // 0x013ef094
extern void* g_vtblF1c6c;                // 0x013f1c6c
extern void* g_vtblBca4;                 // 0x013ebca4
extern void* g_vtblBcb8;                 // 0x013ebcb8

struct SimAbility {
    void* deleting_dtor(unsigned flags);
};
struct AtomicRefCounted {
    int vtbl;
    int mCount;
    void Release();              // 0x00402420 (thiscall)
};
struct ThreadedObject {
    void Release();              // 0x00404f90 Resource::ThreadedObject::Release (thiscall)
};
struct RefHolder {
    int vtbl;                    // +0x00
    AtomicRefCounted mRef;       // +0x04 (mCount at +0x08)
    int AddRef();
};
struct ThreadedRes {
    void dtor();
};
struct BitmapBase {
    BitmapBase(int w, int h);                                     // 0x00432960 (thiscall)
};
struct Bitmap : BitmapBase {
    Bitmap(int w, int h, int fill);
};


extern "C" long _InterlockedExchangeAdd(long volatile*, long);
#pragma intrinsic(_InterlockedExchangeAdd)

// ---- shared helpers ---------------------------------------------------------------------
struct RC {                                   // AtomicRefCounted: refcount at +8
    int vtbl; int pad;
    volatile int mCount;
    void AddRef() { _InterlockedExchangeAdd((long*)&mCount, 1); }
    void Release();                           // 0x00402420
};
struct RCPtr {                                // eastl intrusive_ptr<RC>
    RC* p;
    RCPtr(const RCPtr& o) : p(o.p) { if (p) p->AddRef(); }
    RCPtr& operator=(RC* nv)
    {
        if (nv != p) {
            RC* old = p;
            if (nv) nv->AddRef();
            p = nv;
            if (old) old->Release();
        }
        return *this;
    }
};
inline void* operator new(unsigned, void* p) { return p; }
void* PoolAlloc(void* allocator, unsigned bytes, int align, int flags);        // 0x00511810 (cdecl)
void* MoveRange(void* dst, const void* src, int bytes);                        // 0x011e0744 (cdecl)
void  CopyAssignAtomicBackward(RCPtr* first, RCPtr* last, RCPtr* destEnd);     // 0x0042eb20 (cdecl)
void  OperatorDelete(void* p);                                                 // 0x00f47380 (cdecl)

// eastl::fixed_vector<intrusive_ptr<RC>, ...>
struct RCPtrVec {
    RCPtr* mBegin;          // +0
    RCPtr* mEnd;            // +4
    RCPtr* mCap;            // +8
    int  mAllocator;        // +0xc
    RCPtr* mFixedBuf;       // +0x10
    void DoInsertValue(RCPtr* pos, const RCPtr* value);   // 0x0051d300
};

// @ 0x0051d300 eastl::vector<intrusive_ptr<AtomicRefCounted>>::DoInsertValue (insert one at pos)
void RCPtrVec::DoInsertValue(RCPtr* pos, const RCPtr* value)
{
    if (mEnd != mCap) {
        const RCPtr* v = value;
        if (v >= pos && v < mEnd)
            ++v;
        new (mEnd) RCPtr(*(mEnd - 1));
        CopyAssignAtomicBackward(pos, mEnd - 1, mEnd);
        *pos = v->p;
        mEnd = mEnd + 1;
    } else {
        int prev = (int)(mEnd - mBegin);
        int nNew = prev ? prev * 2 : 1;
        RCPtr* newBegin = nNew ? (RCPtr*)PoolAlloc(&mAllocator, nNew * 4, 4, 0) : 0;
        RCPtr* ins = (RCPtr*)MoveRange(newBegin, mBegin, (int)((char*)pos - (char*)mBegin)) + (pos - mBegin);
        new (ins) RCPtr(*value);
        ++ins;
        RCPtr* tail = (RCPtr*)MoveRange(ins, pos, (int)((char*)mEnd - (char*)pos)) + (mEnd - pos);
        if (mBegin && mBegin != mFixedBuf)
            OperatorDelete(mBegin);
        mBegin = newBegin;
        mEnd = tail;
        mCap = newBegin + nNew;
    }
}

// ---- 0x0051d720: per-instance particle/decal parameter sampling ---------------------------
struct Vec3f {
    float x, y, z;
    Vec3f() {}
    Vec3f(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3f(const Vec3f& o) : x(o.x), y(o.y), z(o.z) {}
    float& operator[](int i) { return (&x)[i]; }
};
struct S6 { float f[19]; };             // 0x4c-byte scratch block (default at 0x013f1c20)
struct OutB {
    RC*   f0;           char p4[0x0c];
    float f10;          char p14[0x28];
    float f3c;          float f40;     char p44[8];
    float f4c;          float f50;     char p54[8];
    float f5c;          Vec3f f60;     float f6c;     char p70[4];
    float f74;          char p78[4];   float f7c;     float f80;     float f84;
    char  f88;          char p89[0x13]; unsigned f9c; unsigned fa0; unsigned fa4;
};
struct SrcInner { char pad[0x68]; unsigned mMask; };
struct SrcA {
    int idx;            char p4[0x18];
    unsigned flags;     char p20[8];
    int f28;            SrcInner* inner;      // +0x2c
    char p30[4];        float* values;        // +0x34
};
struct Sampler;
struct Tables { char p[0x10]; struct Tbl* t; };
struct Tbl { char p[0x58]; int* ids; };
struct Singleton { char p[0x10]; Tbl* tbl; float Func5169d0(); };   // 0x005169d0
Singleton* GetSingleton();                                           // 0x00401080
struct Filler { void Fill(S6* out, float t, int a, int b, int id); };// 0x00515710
struct ItemVec {
    RC** mBegin; RC** mEnd;
    bool Probe();                                                     // 0x00526430
};
float Frac(float v, float* whole);                                    // 0x004fa520 (cdecl)
Vec3f HSVtoRGB(Vec3f hsv);                                            // 0x0052a030 (cdecl)
extern S6 g_default6;                                                 // 0x013f1c20
extern Vec3f g_palette[];                                             // 0x015df204

static inline float WrapHue(float h)
{
    float d;
    return Frac(h / 360.0f, &d) * 360.0f;
}
static inline float Clamp01(float v)
{
    float hi = 1.0f;
    float r = v > 0.0f ? v : 0.0f;
    return r < hi ? r : hi;
}

struct Sampler {
    int pad0;
    ItemVec mItems;                 // +4
    char p0c[0x10];
    unsigned mFlags;                // +0x1c
    Vec3f mColor;                   // +0x20
    signed char mIdx;               // +0x2c
    char p2d[0x3f];
    Filler mFiller;                 // +0x6c
    char p6d[0x3b];
    unsigned char fa8, fa9, faa;
    void Sample(float t, SrcA* a, int p4, int p5, S6* p6, OutB* p7);   // 0x0051d720
};

// @ 0x0051d720
void Sampler::Sample(float t, SrcA* a, int p4, int p5, S6* p6, OutB* p7)
{
    unsigned local_20 = a->flags;
    int local_1c = a->f28;
    if (!mItems.Probe()) {
        if (mItems.mBegin == mItems.mEnd - 1) {
            p7->f0 = *mItems.mBegin;
        } else {
            unsigned local_24 = local_20;
            if (mFlags & 1)
                local_24 ^= (local_20 * local_1c) >> 16;
            else if (mFlags & 2)
                local_24 += local_1c;
            unsigned n = (unsigned)(mItems.mEnd - mItems.mBegin);
            p7->f0 = mItems.mBegin[local_24 % n];
        }
    }
    if (mFlags & 4)
        t = GetSingleton()->Func5169d0();
    if (fa8) p7->f9c = fa8;
    if (fa9) p7->fa0 = fa9;
    if (faa) p7->fa4 = faa;
    p7->f4c = 0.1f;
    p7->f50 = 0.5f;
    *p6 = g_default6;
    Vec3f* src = mIdx < 0 ? &mColor : &g_palette[mIdx];
    Vec3f v(src->x, src->y, src->z);
    p6->f[7] = v[0];
    p6->f[8] = v[1];
    p6->f[9] = v[2];
    if (a->values) {
        float* sv = a->values;
        unsigned mask = a->inner->mMask;
        for (int i = 0; mask; mask >>= 1, ++i)
            if (mask & 1)
                p6->f[i] = sv[i];
    }
    int id = GetSingleton()->tbl->ids[a->idx * 3];
    mFiller.Fill(p6, t, p4, p5, id);
    if (p6->f[4] > 0.0f)
        return;
    Vec3f hsv;
    hsv[0] = WrapHue(p6->f[7]);
    hsv[1] = Clamp01(p6->f[8]);
    hsv[2] = p6->f[9];
    float sgnA = 1.0f;
    float sgnB = 1.0f;
    if (0.0f > p6->f[13]) {
        if (p7->fa0 == 2) { p7->fa0 = 3; sgnA = -1.0f; }
        else if (p7->fa0 == 3) { p7->fa0 = 2; sgnA = -1.0f; }
    }
    if (0.0f > p6->f[11]) {
        if (p7->fa4 == 2) { p7->fa4 = 3; sgnB = -1.0f; }
        else if (p7->fa4 == 3) { p7->fa4 = 2; sgnB = -1.0f; }
    }
    p7->f10 = p6->f[0];
    p7->f40 = p6->f[1];
    p7->f3c = WrapHue(p6->f[2]);
    p7->f5c = Clamp01(p6->f[6]);
    p7->f60 = HSVtoRGB(hsv);
    p7->f6c = Clamp01(p6->f[10]);
    p7->f74 = Clamp01(p6->f[13] * sgnA);
    p7->f7c = Clamp01(p6->f[14]);
    p7->f80 = Clamp01(p6->f[11] * sgnB);
    p7->f84 = Clamp01(p6->f[12]);
    if (mFlags & 0x80)
        p7->f88 = 2;
    else if (mIdx == -2)
        p7->f88 = 1;
    else
        p7->f88 = 0;
}

// ---- constructors (/Od inline-ctor chains) --------------------------------------------------
struct RootA { virtual void ra(); RootA() {} };                          // vtbl 0x013eb394
struct Base0 : RootA { virtual void ra(); virtual void b0(); Base0() {} };   // vtbl 0x013eb384
struct SimBase { virtual void sb(); int f4; SimBase() : f4(0) {} };      // vtbl 0x013ef094
struct PtrZ { void* p; PtrZ() : p(0) {} };
struct Elem12 { int a, b, c; Elem12() {} };
struct Vec3z { int a, b, c; Vec3z() { a = 0; b = 0; c = 0; } };
extern Vec3z g_default12;                                                // 0x015de460

struct ThreadedResObj : SimBase {                                        // final vtbl 0x013f1c6c
    virtual void sb();
    PtrZ f8;                // +8
    Vec3z fc;               // +0xc
    int f18[4];             // +0x18
    int f28[4];             // +0x28
    Elem12 e38[3];          // +0x38
    int f5c;
    int f60;
    unsigned char b64, b65, b66, b67, b68, b69, b6a, b6b, b6c;
    char p6d[0x0f];
    PtrZ f7c;               // +0x7c
    PtrZ f80;               // +0x80
    ThreadedResObj();       // 0x0051df40
};

// @ 0x0051df40 ThreadedRes-like ctor (aggregate of defaults)
ThreadedResObj::ThreadedResObj()
{
    for (int i = 0; i < 3; ++i)
        *(Vec3z*)&e38[i] = g_default12;
    for (int i = 0; i < 4; ++i)
        f18[i] = 0;
    for (int i = 0; i < 4; ++i)
        f28[i] = 0x4d2;
    f60 = -1;
    b64 = 0; b65 = 0; b66 = 0; b67 = 0; b68 = 0; b69 = 0; b6a = 0; b6b = 0; b6c = 0;
}

template <int N> inline void ScratchSlots() { unsigned s[N]; }
struct BBox { void Reset(); __forceinline BBox() { ScratchSlots<6>(); Reset(); } };   // Reset: 0x00409c00
struct Tag { Tag() {} };
struct AllocFixed { int x; AllocFixed(const Tag&); };   // 0x00429360
struct FixedVec {
    void* b; void* e; void* c; AllocFixed a;
    __forceinline FixedVec(const Tag& t) : b(0), e(0), c(0), a(t) {}
};
struct FixedVec2 {
    void* b; void* e; void* c; AllocFixed a;
    __forceinline FixedVec2(const Tag& t) : b(0), e(0), c(0), a(t) { ScratchSlots<2>(); }
};
struct Sub94 { char pad[0x5c]; Sub94(); };                // 0x0041cfe0

struct PaintSystemObj : Base0, SimBase {                  // final vtbls 0x013f1c74 / 0x013f1c70
    virtual void ra();
    virtual void b0();
    virtual void sb();
    PtrZ f0c, f10, f14, f18, f1c;
    char p20[4];
    BBox bb24;                                            // +0x24 (0x18 bytes)
    char p25[0x17];
    FixedVec v3c;                                         // +0x3c
    char p4c[0x34];
    FixedVec2 v80;                                        // +0x80
    char p90[4];
    Sub94 s94;                                            // +0x94
    PtrZ ff0, ff4, ff8, ffc, f100, f104;
    PaintSystemObj();                                     // 0x0051e180
};

// @ 0x0051e180 Skinner::PaintSystem::PaintSystem
PaintSystemObj::PaintSystemObj() : v3c(Tag()), v80(Tag())
{
}

// @ 0x0051d5f0 SimAbility scalar deleting dtor
void* SimAbility::deleting_dtor(unsigned flags)
{
    *(void**)((char*)this + 4) = &g_vtblSimCreatureAbility;
    if ((flags & 1) != 0)
        EASTL_allocator_deallocate(this);
    return this;
}

// @ 0x0051d690 Bitmap ctor
Bitmap::Bitmap(int w, int h, int fill)
    : BitmapBase(w, h)
{
    *(void**)this = &g_vtblBca4;
    *(void**)((char*)this + 0x18) = &g_vtblBcb8;
    void* buf = EA_alloc((unsigned)(w * h * 4), "Graphics", 0, 0, 0, 0);
    *(void**)((char*)this + 0x28) = buf;
    *(int*)((char*)this + 0x24) = 2;
    Memset32(*(void**)((char*)this + 0x28), fill, w * h);
}

// eastl::intrusive_ptr-style holder; its inlined dtor gives the /Od member-address temps.
template <class T> struct IPtr51 {
    T* mpObject;
    void Reset() { if (mpObject) mpObject->Release(); }
};
// base part (vtable 0x13ef094 = Simulator::cCreatureAbility): holder at +8, then the base vtable.
struct ThreadedResBase51 {
    void* vtbl;
    int f4;
    IPtr51<ThreadedObject> m8;
    // pad: three dead /Od slots (ebp-0x14..-0xc) the original frame also has, likely from other inlined member dtors.
    void Teardown() { int pad[3]; m8.Reset(); *(void**)this = &g_vtblSimCreatureAbility; }
};

// @ 0x0051e100 ThreadedRes dtor
void ThreadedRes::dtor()
{
    *(void**)this = &g_vtblF1c6c;
    ((IPtr51<AtomicRefCounted>*)((char*)this + 0x80))->Reset();
    ((IPtr51<AtomicRefCounted>*)((char*)this + 0x7c))->Reset();
    ((ThreadedResBase51*)this)->Teardown();
}

// @ 0x0051e340 RefHolder::AddRef (non-atomic)
int RefHolder::AddRef()
{
    AtomicRefCounted& r = mRef;
    int n = r.mCount + 1;
    r.mCount = r.mCount + 1;
    return n;
}
