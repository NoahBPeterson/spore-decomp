// Slice s00536d40: Swarm skin-paint particle effect + transform helpers.
// 00536d40/00537390/005375d0/00537c90 are large stubs (partial.txt). The rest are
// implemented. Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }
void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
inline void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, name, flags, debugFlags, file, line); }
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);   // 0x0042dee0
void* GetPaintSystem();                                                     // 0x00401080
struct cPaintSystem { bool IsPaused(); };                                   // 0x00525a40

// ---------------------------------------------------------------- cSPTransform (0x38)
struct cSPTransform {
    uint16_t mFlags;        // +0x00
    uint16_t mModCount;     // +0x02
    float mTranslation[3];  // +0x04
    float mScale;           // +0x10
    float mRotation[9];     // +0x14
    cSPTransform();                                                            // 0x00434040
    cSPTransform(const cSPTransform& x);                                       // @ 0x00538000
    cSPTransform& operator=(const cSPTransform& x);                            // @ 0x00537dc0
    void Compound(const cSPTransform& x);                                      // @ 0x00537f40
};
int VectorNotEqual(const float* a, const float* b);   // 0x0041dd30
int RotationNotEqual(const float* a, const float* b);// 0x0041dd90

// @ 0x00537dc0
cSPTransform& cSPTransform::operator=(const cSPTransform& x)
{
    bool bCopy = false;
    if (mFlags != x.mFlags)
        bCopy = true;
    else if (VectorNotEqual(mTranslation, x.mTranslation))
        bCopy = true;
    else if (!(mScale == x.mScale))
        bCopy = true;
    else if ((mFlags & 2) != 0 && RotationNotEqual(mRotation, x.mRotation))
        bCopy = true;
    if (bCopy) {
        mModCount = mModCount + 1;
        mFlags = x.mFlags;
        mTranslation[0] = x.mTranslation[0];
        mTranslation[1] = x.mTranslation[1];
        mTranslation[2] = x.mTranslation[2];
        mScale = x.mScale;
        for (int i = 0; i < 9; ++i)
            mRotation[i] = x.mRotation[i];
    }
    return *this;
}

// @ 0x00537dc0
// The retail symbol for this VA is ?Assign@cSPTransformOps@@QAEPAU1@PBX@Z (Ghidra guesses operator=):
// same layout as cSPTransform, but the source is an untyped pointer.
struct cSPTransformOps {
    uint16_t mFlags;        // +0x00
    uint16_t mModCount;     // +0x02
    float mTranslation[3];  // +0x04
    float mScale;           // +0x10
    float mRotation[9];     // +0x14
    cSPTransformOps* Assign(const void* x);   // 0x00537dc0
};
cSPTransformOps* cSPTransformOps::Assign(const void* xv)
{
    const cSPTransformOps* x = (const cSPTransformOps*)xv;
    bool bCopy = false;
    if (mFlags != x->mFlags)
        bCopy = true;
    else if (VectorNotEqual(mTranslation, x->mTranslation))
        bCopy = true;
    else if (!(mScale == x->mScale))
        bCopy = true;
    else if ((mFlags & 2) != 0 && RotationNotEqual(mRotation, x->mRotation))
        bCopy = true;
    if (bCopy) {
        mModCount = mModCount + 1;
        mFlags = x->mFlags;
        mTranslation[0] = x->mTranslation[0];
        mTranslation[1] = x->mTranslation[1];
        mTranslation[2] = x->mTranslation[2];
        mScale = x->mScale;
        for (int i = 0; i < 9; ++i)
            mRotation[i] = x->mRotation[i];
    }
    return this;
}

// ---------------------------------------------------------------- @ 0x005372f0
struct CBlockCommandBase28 {
    char pad[0x30];
    void OnRegister(void* parser, void* state);   // 0x0083c780
};
struct CmdStateBlock28 : CBlockCommandBase28 {
    void* mState;                                  // +0x30
    void OnRegister(void* parser, void* state);
};
void CmdStateBlock28::OnRegister(void* parser, void* state)
{
    mState = state ? (void*)((char*)state - 0x34) : 0;
    CBlockCommandBase28::OnRegister(parser, state);
}

// ---------------------------------------------------------------- @ 0x00537330
struct T16 {
    float a, b, c;
    uint8_t d, e;
    uint16_t f;
    T16& operator=(const T16& x);   // @ 0x00537330
};
// A trivially-copyable view of T16: the vector's shifting loops move elements
// with raw 16-byte copies rather than calling the user-defined operator=.
struct T16Raw { uint32_t w[4]; };
T16& T16::operator=(const T16& x)
{
    a = x.a;
    b = x.b;
    c = x.c;
    d = x.d;
    e = x.e;
    f = x.f;
    return *this;
}

// ---------------------------------------------------------------- @ 0x005370b0
T16* UninitCopy16(T16* first, T16* last, T16* dest);  // 0x00537ac0
void UninitCopyFwd16(void** out, T16* first, T16* last, T16* dest);  // 0x00537a40
T16* UninitFill16(T16* dst, uint32_t n, const T16* v);   // 0x00537b60
T16* UninitCopyRev16(T16* first, T16* last, T16* dest); // 0x00537bc0
T16* MoveByCopy16(T16* dst, T16* src, T16* fill);     // 0x005371a0
struct Vec16 {
    T16*     mpBegin;
    T16*     mpEnd;
    T16*     mpCapacity;
    uint32_t mAlloc[2];
    uint32_t mPad0[5];              // +0x14
    float*   mpFloatsBegin;         // +0x28
    float*   mpFloatsEnd;           // +0x2c
    Vec16() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void resize(uint32_t n, const T16& v);                  // @ 0x005370b0
    T16* erase(T16* first, T16* last);                      // 0x00548690
    void DoInsert(T16* position, uint32_t n, const T16& v); // 0x005375d0
    void insertOne(T16* position, const T16& v);            // @ 0x00537390
    void push_back(const T16& v);                           // 0x00537130
};
void Vec16::resize(uint32_t n, const T16& v)
{
    if ((uint32_t)(mpEnd - mpBegin) < n) {
        DoInsert(mpEnd, n - (uint32_t)(mpEnd - mpBegin), v);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}
// ---------------------------------------------------------------- @ 0x00537390
void Vec16::insertOne(T16* position, const T16& v)
{
    if (mpEnd == mpCapacity) {
        uint32_t oldN = (uint32_t)(mpEnd - mpBegin);
        uint32_t newN = oldN == 0 ? 1 : oldN << 1;
        T16* buf = newN == 0 ? 0 : (T16*)EASTL_Allocate(mAlloc, newN << 4, 4, 0);
        T16* mid = UninitCopy16(mpBegin, position, buf);
        if (mid != 0)
            *mid = v;
        T16* end = UninitCopy16(position, mpEnd, mid + 1);
        T16* old = mpBegin;
        if (old != 0 && *(int*)((char*)old - 4) != 0)
            operator delete(old);
        mpBegin = buf;
        mpEnd = end;
        mpCapacity = buf + newN;
    } else {
        const T16* src = &v;
        if (src >= position && src < mpEnd)
            src = src + 1;
        if (mpEnd != 0)
            *mpEnd = *(mpEnd - 1);
        T16* dst = mpEnd;
        T16* prev = mpEnd - 1;
        while (prev != position) {
            prev = prev - 1;
            dst = dst - 1;
            *(T16Raw*)dst = *(T16Raw*)prev;
        }
        *(T16Raw*)position = *(T16Raw*)src;
        mpEnd = mpEnd + 1;
    }
}
// ---------------------------------------------------------------- @ 0x00537130
void Vec16::push_back(const T16& v)
{
    if (mpEnd != mpCapacity) {
        if (mpEnd != 0)
            *mpEnd = v;
        mpEnd = mpEnd + 1;
    } else {
        insertOne(mpEnd, v);
    }
}

// ---------------------------------------------------------------- @ 0x00537240
struct Elem20 {
    uint32_t d[5];
};
Elem20* uninitialized_copy20(Elem20* first, Elem20* last, Elem20* dest)
{
    Elem20* p = dest;
    for (; first != last; ++first, ++p) {
        if (p != 0)
            *p = *first;
    }
    return p;
}

// ---------------------------------------------------------------- @ 0x00537c10
// A refcounted wrapper around a transform-bearing effect object (0x50 bytes).
extern int g_vt_013f2210;           // 0x013f2210
extern int g_vt_013ef094;           // 0x013ef094  (Simulator::cCreatureAbility)
extern int g_vt_013f21d4;           // 0x013f21d4
extern int g_vt_013f2194;           // 0x013f2194
extern int g_vt_013f2d6c;           // 0x013f2d6c
extern int g_vt_013f2d68;           // 0x013f2d68
struct Big50 {
    void*        mVtbl;             // +0x00
    void*        mVtbl2;            // +0x04
    void*        mVtbl2Field;       // +0x08
    cSPTransform mTransform;        // +0x0c
    void*        mPad44;            // +0x44
    void*        mRefA;             // +0x48
    void*        mRefB;             // +0x4c
    Big50(void* a, void* b);   // @ 0x00537c90
};
Big50* CreateBig50(void* a, void* b)
{
    return new ("Swarm", 0, 0, 0, 0) Big50(a, b);
}

// ---------------------------------------------------------------- @ 0x00537c90
Big50::Big50(void* a, void* b)
{
    mVtbl = &g_vt_013f2210;
    mVtbl2 = &g_vt_013ef094;
    mVtbl2Field = 0;
    mVtbl = &g_vt_013f21d4;
    mVtbl2 = &g_vt_013f2194;
    mVtbl = &g_vt_013f2d6c;
    mVtbl2 = &g_vt_013f2d68;
    mRefA = a;
    if (mRefA != 0) {
        void* vtbl = *(void**)((char*)mRefA + 8);
        void (*fn)(char*) = *(void (**)(char*))vtbl;
        fn((char*)mRefA + 8);
    }
    mRefB = b;
}

// ---------------------------------------------------------------- @ 0x00537d60
extern int g_vt_a, g_vt_b, g_vt_c;
struct H537d60 {
    void ResetVtables();
};
void H537d60::ResetVtables()
{
    *(void**)this = &g_vt_a;
    *(void**)((char*)this + 4) = &g_vt_b;
    *(void**)((char*)this + 4) = &g_vt_c;
}

// ---------------------------------------------------------------- @ 0x00537d90
struct Host537d90 {
    char pad0[0xc];
    cSPTransform mTransform;   // +0x0c
    bool mFlag;                // +0x44
    void Init(void* a, void* b, void* c);
};
void Host537d90::Init(void* a, void* b, void* c)
{
    (void)a;
    (void)b;
    (void)c;
    cSPTransform t;
    mTransform = t;
    mFlag = false;
}

// ---------------------------------------------------------------- @ 0x00537ea0
struct Host537ea0 {
    char pad0[0x44];
    bool mFlag;   // +0x44
    bool IsUsable();
};
bool Host537ea0::IsUsable()
{
    if (mFlag) {
        void* p = GetPaintSystem();
        if (!((cPaintSystem*)p)->IsPaused())
            return false;
    }
    return true;
}

// ---------------------------------------------------------------- @ 0x00537ef0
struct Host537ef0 {
    char pad0[0xc];
    cSPTransform mTransform;   // +0x0c
    void Set(void* a, void* b);
};
void Host537ef0::Set(void* a, void* b)
{
    cSPTransform t1(*(const cSPTransform*)b);
    t1.Compound(*(const cSPTransform*)a);
    cSPTransform t2(t1);
    ((cSPTransformOps*)((char*)this + 0xc))->Assign(&t2);
}

// ---------------------------------------------------------------- @ 0x005375d0
// Vec16::DoInsert(position, n, v): insert n copies of v at position, growing the
// buffer when the spare capacity is too small.
void Vec16::DoInsert(T16* position, uint32_t n, const T16& v)
{
    if (n > (uint32_t)(mpCapacity - mpEnd) >> 4) {
        uint32_t oldN = (uint32_t)(mpEnd - mpBegin) >> 4;
        uint32_t cap = oldN > 0 ? oldN << 1 : 1;
        uint32_t want = cap < oldN + n ? oldN + n : cap;
        T16* buf = want == 0 ? 0 : (T16*)EASTL_Allocate(mAlloc, want << 4, 4, 0);
        T16* mid = UninitCopy16(mpBegin, position, buf);
        UninitFill16(mid, n, &v);
        mid = mid + n;
        T16* end = UninitCopyRev16(position, mpEnd, mid);
        T16* old = mpBegin;
        if (old != 0 && *(int*)((char*)old - 4) != 0)
            operator delete(old);
        mpBegin = buf;
        mpEnd = end;
        mpCapacity = buf + want;
    } else if (n != 0) {
        T16 vv;
        *(T16Raw*)&vv = *(T16Raw*)&v;
        uint32_t fill = (uint32_t)(mpEnd - position) >> 4;
        T16* last = mpEnd;
        if (n < fill) {
            T16* dest;
            UninitCopyFwd16((void**)&dest, last - n, last, last);   // duplicate the tail past the end
            mpEnd = mpEnd + n;
            T16* a = last;
            T16* b = last - n;
            while (b != position) {
                b = b - 1;
                a = a - 1;
                *(T16Raw*)a = *(T16Raw*)b;
            }
            T16* p = position;
            T16* stop = position + n;
            while (p != stop) {
                *(T16Raw*)p = *(T16Raw*)&vv;
                p = p + 1;
            }
        } else {
            UninitFill16(mpEnd, n - fill, &vv);
            mpEnd = mpEnd + (n - fill);
            MoveByCopy16(position, last, mpEnd);
            mpEnd = mpEnd + fill;
            T16* p = position;
            while (p != last) {
                *(T16Raw*)p = *(T16Raw*)&vv;
                p = p + 1;
            }
        }
    }
}

// ---------------------------------------------------------------- @ 0x00536d40
// cSPSkinPaintParticleEffect command: seed the effect's Elem16 list from the
// default entry, convert the argument list to floats and stage the tweak block.
extern float g_skinDefault0;   // 0x015e1bf0
extern float g_skinDefault1;   // 0x015e1bf4
extern float g_skinDefault2;   // 0x015e1bf8
extern float kZero;            // 0x01485378 (0.0f)
extern float kOne;             // 0x01485720 (1.0f)
struct cArgs536d40 {
    int  OptionArguments(unsigned id, int a);                  // 0x00838330
    int  OptionArguments(unsigned id, int a, int* n, int b);   // 0x00838130
    bool HasFlag(unsigned id);                                 // 0x008380b0
};
struct ArgConverter {                                          // self+4
    virtual float Convert(int v);                              // vtbl +0x98
};
void  AddFloat4547f0(void* vec, float* f);                     // 0x004547f0
void  Finalize4227f0(void* vec, void* v);                      // 0x004227f0

// The command object owning the effect; only the fields this routine touches.
struct cSPSkinPaintParticleEffect {
    char          mPad00[4];        // +0x00
    ArgConverter* mpConverter;      // +0x04  converts argument tokens to floats
    char          mPad08[4];        // +0x08
    void**        mpEffectHolder;   // +0x0c  holder whose +0x4c is the effect
    uint8_t       mUnknown10;       // +0x10

    void ParticleEffect(cArgs536d40* args, int* argList, int nargs);   // @ 0x00536d40
};

void cSPSkinPaintParticleEffect::ParticleEffect(cArgs536d40* args, int* argList, int nargs)
{
    Vec16* vec = *(Vec16**)((char*)mpEffectHolder + 0x4c);
    uint32_t size = (uint32_t)(vec->mpEnd - vec->mpBegin) >> 4;
    if (size > 0 && vec->mpBegin[0].d < 0xfd)
        return;
    if (size > 1 && vec->mpBegin[1].d < 0xfe)
        return;

    if (size < 2) {
        T16 def;
        def.a = g_skinDefault0;
        def.b = g_skinDefault1;
        def.c = g_skinDefault2;
        def.d = 0xff;
        def.e = 0;
        def.f = 0;
        vec->resize(2, def);
    }

    T16 tweak;
    tweak.a = g_skinDefault0;
    tweak.b = g_skinDefault1;
    tweak.c = g_skinDefault2;
    tweak.d = 0xff;
    tweak.e = (uint8_t)nargs;
    tweak.f = (uint16_t)(uint32_t)((vec->mpFloatsEnd - vec->mpFloatsBegin) >> 2);

    for (int i = 0; i < nargs; ++i) {
        float f = mpConverter->Convert(argList[i]);
        AddFloat4547f0(vec->mpFloatsBegin, &f);
    }

    int opt = args->OptionArguments(0x13f2d14, 1);
    if (opt != 0)
        tweak.a = mpConverter->Convert(*(int*)opt);

    int count = nargs;
    opt = args->OptionArguments(0x13f2d0c, 1, &nargs, 2);
    if (opt != 0) {
        tweak.b = mpConverter->Convert(*(int*)opt);
        float z;
        if (nargs == 2)
            z = mpConverter->Convert(*(int*)(opt + 4));
        else
            z = tweak.b;
        tweak.c = z;
    }
    (void)count;

    int idx = (int)((vec->mpEnd - vec->mpBegin) >> 4);
    vec->push_back(tweak);

    char block[0x14];
    *(float*)(block + 0) = kZero;
    *(float*)(block + 4) = kZero;
    *(float*)(block + 8) = kZero;
    *(float*)(block + 12) = kZero;
    block[0x10] = (char)mUnknown10;
    block[0x11] = (char)idx;
    block[0x12] = 2;
    block[0x13] = 0;

    if (args->HasFlag(0x13f27d8))
        block[0x12] = 1;
    if (args->HasFlag(0x13f2d00)) {
        if (size >= 1 && vec->mpBegin[0].d == 0xfd)
            *(float*)(block + 0) = kOne;
    }
    if (args->HasFlag(0x13f2cf4)) {
        if (size >= 2 && vec->mpBegin[1].d == 0xfe)
            *(float*)(block + 4) = kOne;
    }
    Finalize4227f0((char*)vec + 0x14, block);
}

