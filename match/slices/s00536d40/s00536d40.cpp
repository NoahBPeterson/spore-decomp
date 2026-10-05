// Slice s00536d40: Swarm skin-paint particle effect + transform helpers.
// 00536d40/00537390/005375d0/00537c90 are large stubs (partial.txt). The rest are
// implemented. Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int size_t;
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
struct Elem16 {
    uint32_t d[4];
};
struct Vec16 {
    Elem16* mpBegin;
    Elem16* mpEnd;
    Elem16* mpCapacity;
    uint32_t mAlloc[2];
    Vec16() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void resize(uint32_t n);                                // @ 0x005370b0
    Elem16* erase(Elem16* first, Elem16* last);             // 0x00548690
    void DoInsert(Elem16* position, uint32_t n, const Elem16& v);   // 0x005375d0
};
void Vec16::resize(uint32_t n)
{
    if ((uint32_t)(mpEnd - mpBegin) < n) {
        Elem16 v;
        DoInsert(mpEnd, n - (uint32_t)(mpEnd - mpBegin), v);
    } else {
        erase(mpBegin + n, mpEnd);
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
struct Big50 {
    Big50(void* a, void* b);   // @ 0x00537c90
};
Big50* CreateBig50(void* a, void* b)
{
    return new ("Swarm", 0, 0, 0, 0) Big50(a, b);
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
    void Set(void* a, void* b, void* c);
};
void Host537ef0::Set(void* a, void* b, void* c)
{
    (void)c;
    cSPTransform t1(*(const cSPTransform*)b);
    t1.Compound(*(const cSPTransform*)a);
    cSPTransform t2(t1);
    mTransform = t2;
}

// ---------------------------------------------------------------- stubs (partial)
// @ 0x00536d40
void ParticleEffectStub() {}
// @ 0x00537390
void ParticleCommandStub() {}
// @ 0x005375d0
void Vec16DoInsertStub() {}
// @ 0x00537c90
void Big50CtorStub() {}
