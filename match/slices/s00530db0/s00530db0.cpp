// Slice s00530db0: Swarm skin-paint "distribute" effect component
// (cSPSkinPaintDistributeEffect): ctor/dtor, SetWorld, Stop / Clear, IsRunning, plus the
// eastl uninitialized_copy and vector insert-fill helpers. Unoptimized module:
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef unsigned int size_t;
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
inline void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, name, flags, debugFlags, file, line); }
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);   // 0x0042dee0
extern "C" void EASTL_allocator_deallocate(void* p);                        // 0x00f47380

// ---------------------------------------------------------------- pair / vector
struct PairIF {
    int first;
    float second;
    PairIF() : first(0), second(0.0f) {}
};
struct VectorIF {
    PairIF* mpBegin;
    PairIF* mpEnd;
    PairIF* mpCapacity;
    uint32_t mAlloc[2];
    VectorIF() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoInsertValues(PairIF* position, uint32_t n, const PairIF& value);   // @ 0x00530db0
};

// ---------------------------------------------------------------- @ 0x005311a0
// uninitialized_copy: construct [first,last) into dest, returning the end iterator.
struct PairIter { PairIF* p; };
PairIter uninitialized_copy(PairIF* first, PairIF* last, PairIF* dest)
{
    PairIF* p = dest;
    for (; first != last; ++first, ++p) {
        if (p != 0)
            *p = *first;
    }
    PairIter result;
    result.p = p;
    return result;
}

// ---------------------------------------------------------------- @ 0x00530db0
void VectorIF::DoInsertValues(PairIF* position, uint32_t n, const PairIF& value)
{
    if (n == 0)
        return;
    uint32_t nOld = (uint32_t)(mpEnd - mpBegin);
    uint32_t nIndex = (uint32_t)(position - mpBegin);
    if (nOld + n > (uint32_t)(mpCapacity - mpBegin)) {
        uint32_t nNewCapacity = nOld * 2;
        if (nNewCapacity < nOld + n)
            nNewCapacity = nOld + n;
        PairIF* pNew = (nNewCapacity == 0) ? 0
                                           : (PairIF*)EASTL_Allocate(mAlloc, nNewCapacity * 8, 4, 0);
        PairIF* p = pNew;
        for (uint32_t i = 0; i < nIndex; ++i)
            *p++ = mpBegin[i];
        for (uint32_t i = 0; i < n; ++i)
            *p++ = value;
        for (uint32_t i = nIndex; i < nOld; ++i)
            *p++ = mpBegin[i];
        if (mpBegin != 0 && ((uint32_t*)mpBegin)[-1] != 0)
            EASTL_allocator_deallocate(mpBegin);
        mpBegin = pNew;
        mpEnd = p;
        mpCapacity = pNew + nNewCapacity;
        return;
    }
    for (uint32_t i = nOld; i > nIndex; --i)
        mpBegin[i + n - 1] = mpBegin[i - 1];
    for (uint32_t i = 0; i < n; ++i)
        mpBegin[nIndex + i] = value;
    mpEnd = mpBegin + nOld + n;
}

// ---------------------------------------------------------------- Swarm component
struct cIComponent {
    cIComponent() {}
    virtual ~cIComponent() {}
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void Stop(int immediate);   // +0x0c
};
struct RefCountTemplate {
    int mRefCount;
    RefCountTemplate() : mRefCount(0) {}
    virtual ~RefCountTemplate() {}
    virtual int AddRef();
    virtual int Release();
};
struct cComponentBase : cIComponent, RefCountTemplate {
    cComponentBase() {}
    virtual ~cComponentBase() {}
    virtual int AddRef();
    virtual int Release();
};

struct cIVisualEffect {
    virtual void e0();
    virtual void e1();
    virtual void e2();
    virtual void Stop(int immediate);   // +0x0c
    virtual bool IsActive();            // +0x10
};

struct VectorAutoRef {
    cIVisualEffect** mpBegin;
    cIVisualEffect** mpEnd;
    cIVisualEffect** mpCapacity;
    uint32_t mAlloc[2];
    VectorAutoRef() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorAutoRef();
    cIVisualEffect** erase(cIVisualEffect** first, cIVisualEffect** last);   // 0x00533500
};

void* GetPaintSystem();     // 0x00401080
struct cPaintSystem { bool IsPaused(); };   // IsPaused @ 0x00525a40 (thiscall)

struct cSPSkinPaintDistributeEffect : cComponentBase {
    void* mpDesc;                       // +0x0c
    void* mpWorld;                      // +0x10
    int mComponentId;                   // +0x14
    VectorAutoRef mEffectsList;         // +0x18
    bool mNeedsFirstTick;               // +0x2c
    cSPSkinPaintDistributeEffect(void* desc, int componentId);   // @ 0x00531270
    ~cSPSkinPaintDistributeEffect();                             // @ 0x00531310
    void SetWorld(void* world, void* b, void* c);                // @ 0x00531360
    void Clear();                                                // @ 0x00531380
    void Start(void* a);                                         // @ 0x005313c0
    void Stop(int immediate);                                    // @ 0x005313e0
    bool IsRunning();                                            // @ 0x00531470
};

// ---------------------------------------------------------------- @ 0x00531270
cSPSkinPaintDistributeEffect::cSPSkinPaintDistributeEffect(void* desc, int componentId)
    : mpDesc(desc), mpWorld(0), mComponentId(componentId)
{
}

// ---------------------------------------------------------------- @ 0x00531310
cSPSkinPaintDistributeEffect::~cSPSkinPaintDistributeEffect()
{
}

// ---------------------------------------------------------------- @ 0x00531220
cSPSkinPaintDistributeEffect* CreateDistributeEffect(void* desc, int componentId)
{
    return new ("Swarm", 0, 0, 0, 0) cSPSkinPaintDistributeEffect(desc, componentId);
}

// ---------------------------------------------------------------- @ 0x00531360
void cSPSkinPaintDistributeEffect::SetWorld(void* world, void* b, void* c)
{
    (void)b;
    (void)c;
    mpWorld = world;
    mNeedsFirstTick = false;
}

// ---------------------------------------------------------------- @ 0x00531380
void cSPSkinPaintDistributeEffect::Clear()
{
    mEffectsList.erase(mEffectsList.mpBegin, mEffectsList.mpEnd);
    mpWorld = 0;
}

// ---------------------------------------------------------------- @ 0x005313c0
void cSPSkinPaintDistributeEffect::Start(void* a)
{
    (void)a;
    mNeedsFirstTick = true;
}

// ---------------------------------------------------------------- @ 0x005313e0
void cSPSkinPaintDistributeEffect::Stop(int immediate)
{
    GetPaintSystem();
    for (cIVisualEffect** p = mEffectsList.mpBegin; p != mEffectsList.mpEnd; ++p)
        (*p)->Stop(immediate);
    mEffectsList.erase(mEffectsList.mpBegin, mEffectsList.mpEnd);
    mNeedsFirstTick = false;
}

// ---------------------------------------------------------------- @ 0x00531470
bool cSPSkinPaintDistributeEffect::IsRunning()
{
    if (!mNeedsFirstTick) {
        void* p = GetPaintSystem();
        if (!((cPaintSystem*)p)->IsPaused()) {
            for (uint32_t i = 0; i < (uint32_t)(mEffectsList.mpEnd - mEffectsList.mpBegin); ++i) {
                if (mEffectsList.mpBegin[i]->IsActive())
                    return true;
            }
            return false;
        }
    }
    return true;
}
