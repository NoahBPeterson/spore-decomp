// Slice s00a6d020 -- EA::Swarm::cEffectsManager update / shutdown / init and helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE
#include "types.h"
#include <string.h>
#include <intrin.h>

// ---------------------------------------------------------------------------
// external helpers / globals
extern "C" void  operator_delete__(void* p);                                    // 0xf47380
extern "C" void  FUN_011e073e(void* dst, int val, int size);                    // 0x11e073e
extern "C" void* EAAllocate(unsigned size, const char* file, int a, int b, int c, int d); // 0xf473a0
extern "C" void  MakeCaseInsensitive(void* s);                                  // 0x8409b0
extern "C" __declspec(dllimport) int sprintf(char*, const char*, ...);          // 0x13cc4a0
extern "C" __declspec(dllimport) int isdigit(int);                              // 0x13cc4cc
extern "C" __declspec(dllimport) unsigned long strtoul(const char*, char**, int); // 0x13cc4f8
extern "C" __declspec(dllimport) size_t strlen(const char*);

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long* p); // 0x13cc2b8

// dispatch tables iterated by Shutdown/Init
extern int gTblB[];        // 0x1675eb0
extern int gTblBEnd;       // 0x16766b0
extern int gTblA[];        // 0x16759f8
extern int gTblAEnd;       // 0x1675e78

// string / float constant pools
extern const char  kStatsFmt[];     // 0x1455b10
extern const char  kDensityFmt[];   // 0x1455b00
extern const char  kSwarmSurface[]; // 0x1455c48
extern const char  kSwarm[];        // 0x13f1fdc
extern const float kOne;            // 0x1485720
extern const float kZero;           // 0x1485378
extern const float kPoint1;         // 0x1488874
extern const float kPoint9;         // 0x13ec4b4
extern const float kPoint4;         // 0x13ec434

// small-object vtables installed by Init (addresses, not contents)
extern char kVtA2c[];    // 0x1455a2c
extern char kVtA64[];    // 0x1455a64
extern char kVtA98[];    // 0x1455a98
extern char kVtAcc[];    // 0x1455acc
extern char kVtRel[];    // 0x1455a60
extern char kVtEffMgr[]; // 0x1455b80
extern char kVtRefCnt[]; // 0x1455b7c
extern char kVtGme[];    // 0x13ef094

// 0xa70780 (cEffectsWorld ctor), 0x950ea0 (UTFWin::IDrawable::UseCollision),
// 0x93a3a0 (Stopwatch::GetElapsedTimeFloat), 0xae6970 (vector dtor) and
// 0x961d60 (hashtable::DoFreeNodes) are non-virtual __thiscall callees; model
// them as member functions so ecx is set.
struct cEffectsWorld {
    cEffectsWorld* ctor(void* mgr, float* density);   // 0xa70780
};
struct IDrawableCall {
    bool UseCollision(unsigned id, unsigned c);       // 0x950ea0
};
struct VectorObj {
    void dtor();                                       // 0xae6970
};
struct HashOps {
    void DoFreeNodes(void** bucket, int count);        // 0x961d60
};

// ---------------------------------------------------------------------------
// object model
namespace EA { namespace Swarm {

struct EString {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    void* mpAlloc;      // +0x0c
    void assign(const char* first, const char* last);
};

struct HashNode { int mKey; void* mValue; HashNode* mpNext; };
struct HashIter { HashNode* mpNode; HashNode** mpBucket; };

struct HashTable {
    void*       mpF0;             // +0x00
    HashNode**  mpBucketArray;    // +0x04
    int         mnBucketCount;    // +0x08
    int         mnElementCount;   // +0x0c
    int         mPad[4];          // +0x10
    HashIter* find(HashIter* out, const unsigned* key);   // 0x645ed0
    void**   f(const void* key);                     // 0x962100
    HashIter erase(const HashIter& it);              // 0xadc970
};

struct PairKey { int a; int b; };
struct CompNode { int f00; int f04; int mComp; };     // mComp at +0x08
struct CompIter { CompNode* mpNode; void* mpBucket; };
struct CompMap {
    void*      mpF0;             // +0x00
    CompNode** mpBucketArray;    // +0x04
    int        mnBucketCount;    // +0x08
    CompIter*  find(CompIter* out, const PairKey* key);   // 0xa7bf40
};

struct IRefCounted {
    virtual void AddRef();     // 0x00
    virtual void Release();    // 0x04
};

struct IComponent : IRefCounted {
    virtual void v08();                       // 0x08
    virtual void Release2();                  // 0x0c
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c();                       // 0x1c
};

struct ICollection : IRefCounted {
    virtual char v08();                       // 0x08
    virtual void v0c();                       // 0x0c
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual int  v2c(int a, int b, int c);    // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38();
    virtual char v3c(int a, const char* b);   // 0x3c

    void FUN_00a69380(void* mgr);             // 0xa69380
};

struct IValue : IRefCounted {
    virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual char v28();
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(float, float, void*);

    void FUN_00a719c0(int i);                 // 0xa719c0
    void FUN_00a72010(int i);                 // 0xa72010
};

struct IWorld : IRefCounted {
    virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(void* p);                // 0x1c
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c();                       // 0x4c
};

struct IRenderer : IRefCounted {
    virtual void v08(float* p);               // 0x08
};

struct Stopwatch {
    unsigned   mnStartLo;     // +0x00
    unsigned   mnStartHi;     // +0x04
    unsigned   mnElapsedLo;   // +0x08
    unsigned   mnElapsedHi;   // +0x0c
    int        mnUnits;       // +0x10
    float      mfCoeff;       // +0x14
    long long  GetElapsedTimeFloat();   // 0x93a3a0
};

struct ResInfo {
    int f00, f04, f08, f0c, f10, f14, f18, f1c;
    int f20, f24, f28, f2c, f30, f34, f38, f3c;
    int f40, f44, f48;
};

struct InitParams {
    float a;        // +0x00
    float b;        // +0x04
    float c;        // +0x08
    float d;        // +0x0c
    float e;        // +0x10
    char  f;        // +0x14
    char  pad[3];
    float g;        // +0x18
    int   h;        // +0x1c
};

struct cEffectsManager {
    void*      mpVtbl;                 // +0x00
    void*      mpRefVtbl;              // +0x04
    int        m08;                    // +0x08
    char       mInitialized;           // +0x0c
    char       _pad0d[3];
    Stopwatch  mTimer;                 // +0x10
    float      mDampedSimTimeInMS;     // +0x28
    ICollection** mCollectionsBegin;   // +0x2c
    ICollection** mCollectionsEnd;     // +0x30
    void*      m34;                    // +0x34
    void*      m38;                    // +0x38
    void*      m3c;                    // +0x3c
    IRenderer* mRenderer;              // +0x40
    IRefCounted* m44;                  // +0x44
    IRefCounted* m48;                  // +0x48
    int        m4c;                    // +0x4c
    float      m50;                    // +0x50
    int        m54;                    // +0x54
    float      m58;                    // +0x58
    float      m5c;                    // +0x5c
    float      m60;                    // +0x60
    float      m64;                    // +0x64
    int        m68;                    // +0x68
    int        m6c;                    // +0x6c
    int        m70;                    // +0x70
    ResInfo    mResInfo;               // +0x74
    EString    mStatsStr;              // +0xc0
    float      mDensity;               // +0xd0
    int        md4;                    // +0xd4
    char       _padD8[0xe0 - 0xd8];
    int        mE0;                    // +0xe0
    int        mE4;                    // +0xe4
    int        mE8;                    // +0xe8
    char       _padEC[0x1f0 - 0xec];
    IComponent* m1f0;                  // +0x1f0
    IComponent* m1f4[12];              // +0x1f4
    HashTable  mHash;                  // +0x224
    IWorld*    mWorld;                 // +0x244
    EString    mName;                  // +0x248

    void      DoUpdate(float a, float b);                       // 00a6d020
    bool      FUN_00a6d3b0(ICollection* p);                     // 00a6d3b0
    void      FUN_00a6d480();                                   // 00a6d480
    bool      FUN_00a6d4e0(int a, int b);                       // 00a6d4e0
    int       FUN_00a6d5a0(int a, int b, int c, int d);         // 00a6d5a0
    const char* GetStatsString();                               // 00a6d640
    bool      GetEffectInfo(int a, const char* name);           // 00a6d730
    unsigned  FUN_00a6d7b0(int a, int b);                       // 00a6d7b0
    unsigned  FUN_00a6d840(const char* s);                      // 00a6d840
    bool      Shutdown();                                       // 00a6d950
    bool      FUN_00a6da80(unsigned key);                       // 00a6da80
    bool      FUN_00a6db00(int a, int b, unsigned c);           // 00a6db00
    ~cEffectsManager();                                         // 00a6db40
    bool      Init();                                           // 00a6dc60
    void      SetRenderer(IRenderer* p);                        // 00a6ded0
    IWorld*   CreateWorld(unsigned id, unsigned b);             // 00a6df30
};

// function-pointer typedefs for the two manager vtable slots used by Init
typedef void (__thiscall *VfnA8)(void* self, InitParams* params);
typedef void (__thiscall *Vfn78)(void* self, unsigned hash, int zero, void* obj);

// ---------------------------------------------------------------------------
// hashtable iteration helpers
inline HashNode* HashFirst(HashNode**& b)
{
    HashNode* n = *b;
    if (n == 0) {
        ++b;
        if (*b == 0) {
            do { ++b; } while (*b == 0);
        }
        n = *b;
    }
    return n;
}

inline void HashNext(HashNode**& b, HashNode*& node)
{
    node = node->mpNext;
    if (node == 0) {
        do {
            ++b;
            node = *b;
        } while (node == 0);
    }
}

// ===========================================================================
// @ 0x00a6d020
void cEffectsManager::DoUpdate(float a, float b)
{
    if (mTimer.mnUnits == 1) {
        unsigned long long t = __rdtsc();
        mTimer.mnStartLo = (unsigned)t;
        mTimer.mnStartHi = (unsigned)(t >> 32);
    }
    else {
        long long ctr;
        QueryPerformanceCounter(&ctr);
        mTimer.mnStartLo = (unsigned)ctr;
        mTimer.mnStartHi = (unsigned)(ctr >> 32);
    }
    mTimer.mnElapsedLo = 0;
    mTimer.mnElapsedHi = 0;
    FUN_011e073e(&mResInfo, 0, 0x4c);
    mResInfo.f38 = m54;

    int count = (int)(mCollectionsEnd - mCollectionsBegin);
    for (int i = 0; i < count; ++i) {
        ICollection* coll = mCollectionsBegin[i];
        if (coll != 0 && coll->v08() != 0) {
            HashNode** bucket = mHash.mpBucketArray;
            HashNode* node = HashFirst(bucket);
            HashNode* end = mHash.mpBucketArray[mHash.mnBucketCount];
            while (node != end) {
                ((IValue*)node->mValue)->FUN_00a719c0(i);
                HashNext(bucket, node);
            }
            coll->v0c();
            bucket = mHash.mpBucketArray;
            node = HashFirst(bucket);
            end = mHash.mpBucketArray[mHash.mnBucketCount];
            while (node != end) {
                ((IValue*)node->mValue)->FUN_00a72010(i);
                HashNext(bucket, node);
            }
        }
    }

    if (m1f0 != 0)
        m1f0->v1c();

    for (int i = 0; i < 12; ++i) {
        if (m1f4[i] != 0)
            m1f4[i]->v1c();
    }

    if (mRenderer != 0)
        mRenderer->v08(&mDensity);

    if (m50 > kZero) {
        if (a > m50) a = m50;
        if (b > m50) b = m50;
    }

    m6c = 0;
    {
        HashNode** bucket = mHash.mpBucketArray;
        HashNode* node = HashFirst(bucket);
        HashNode* end = mHash.mpBucketArray[mHash.mnBucketCount];
        while (node != end) {
            IValue* v = (IValue*)node->mValue;
            if (*(int*)((char*)v + 0x20) != 4) {
                int before = mResInfo.f10 + mResInfo.f18;
                v->v54(a, b, &mResInfo);
                int after = mResInfo.f10 + mResInfo.f18;
                if ((v->v28() & 1) == 0)
                    m6c += after - before;
            }
            HashNext(bucket, node);
        }
    }

    float fA = (float)mE0;
    float fB = m58;
    float fC = m5c;
    if (fA != 0.0f && (float)m6c > fA) {
        mDensity = (((kOne - fC) * fA) / (float)m6c + fC) * mDensity;
    }
    else if (fB > mDensity) {
        float x = ((kOne - fC) * fA + (float)m6c * fC) * mDensity;
        if ((float)m6c * fB <= x)
            mDensity = fB;
        else
            mDensity = x / (float)m6c;
    }

    long long elapsed = mTimer.GetElapsedTimeFloat();
    float sim = (float)elapsed * mTimer.mfCoeff;
    mDampedSimTimeInMS = (sim - mDampedSimTimeInMS) * kPoint1 + mDampedSimTimeInMS;
}

// ===========================================================================
// @ 0x00a6d3b0
bool cEffectsManager::FUN_00a6d3b0(ICollection* p)
{
    int n = (int)(mCollectionsEnd - mCollectionsBegin);
    for (int i = 0; i < n; ++i) {
        if (mCollectionsBegin[i] == p) {
            p->AddRef();
            p->FUN_00a69380(this);
            ICollection* old = mCollectionsBegin[i];
            mCollectionsBegin[i] = 0;
            if (old != 0)
                old->Release();

            HashNode** bucket = mHash.mpBucketArray;
            HashNode* node = HashFirst(bucket);
            HashNode* end = mHash.mpBucketArray[mHash.mnBucketCount];
            while (node != end) {
                ((IValue*)node->mValue)->FUN_00a719c0(i);
                HashNext(bucket, node);
            }
            p->Release();
            return true;
        }
    }
    return false;
}

// ===========================================================================
// @ 0x00a6d480
void cEffectsManager::FUN_00a6d480()
{
    HashNode** bucket = mHash.mpBucketArray;
    HashNode* node = HashFirst(bucket);
    HashNode* end = mHash.mpBucketArray[mHash.mnBucketCount];
    while (node != end) {
        ((IValue*)node->mValue)->v38();
        HashNext(bucket, node);
    }
}

// ===========================================================================
// @ 0x00a6d4e0
bool cEffectsManager::FUN_00a6d4e0(int a, int b)
{
    int n = (int)(mCollectionsEnd - mCollectionsBegin);
    for (int i = 0; i < n; ++i) {
        ICollection* coll = mCollectionsBegin[i];
        if (coll != 0) {
            CompMap* map = (CompMap*)((char*)coll + 0x68);
            PairKey key;
            key.a = a;
            key.b = b;
            CompIter it;
            map->find(&it, &key);
            if (it.mpNode != map->mpBucketArray[map->mnBucketCount])
                return true;
        }
    }
    return false;
}

// ===========================================================================
// @ 0x00a6d5a0
int cEffectsManager::FUN_00a6d5a0(int a, int b, int c, int d)
{
    int n = (int)(mCollectionsEnd - mCollectionsBegin);
    for (int i = 0; i < n; ++i) {
        ICollection* coll = mCollectionsBegin[i];
        if (coll != 0) {
            CompMap* map = (CompMap*)((char*)coll + 0x68);
            PairKey key;
            key.a = a;
            key.b = b;
            CompIter it;
            map->find(&it, &key);
            if (it.mpNode != map->mpBucketArray[map->mnBucketCount] &&
                it.mpNode->mComp >= 0)
                return coll->v2c(it.mpNode->mComp, c, d);
        }
    }
    return 0;
}

// ===========================================================================
// @ 0x00a6d640
const char* cEffectsManager::GetStatsString()
{
    char buf[2048];
    sprintf(buf, kStatsFmt, (double)mDampedSimTimeInMS,
            mResInfo.f00, mResInfo.f04, mResInfo.f08,
            mResInfo.f14, mResInfo.f10, mResInfo.f1c, mResInfo.f18,
            mResInfo.f24, mResInfo.f20, mResInfo.f28, mResInfo.f30, mResInfo.f2c);
    if (mDensity < kOne) {
        char* e = buf + strlen(buf);
        sprintf(e, kDensityFmt, (double)mDensity);
    }
    mStatsStr.assign(buf, buf + strlen(buf));
    return mStatsStr.mpBegin;
}

// ===========================================================================
// @ 0x00a6d730
bool cEffectsManager::GetEffectInfo(int a, const char* name)
{
    mName.assign(name, name + strlen(name));
    MakeCaseInsensitive(&mName);

    int n = (int)(mCollectionsEnd - mCollectionsBegin);
    for (int i = 0; i < n; ++i) {
        ICollection* c = mCollectionsBegin[i];
        if (c != 0) {
            if (c->v3c(a, mName.mpBegin) != 0)
                return true;
        }
    }
    return false;
}

// ===========================================================================
// @ 0x00a6d7b0
unsigned cEffectsManager::FUN_00a6d7b0(int a, int b)
{
    PairKey key;
    CompIter it;
    int n = (int)(mCollectionsEnd - mCollectionsBegin);
    for (int i = 0; i < n; ++i) {
        ICollection* coll = mCollectionsBegin[i];
        if (coll != 0) {
            CompMap* map = (CompMap*)((char*)coll + 0x68);
            key.a = a;
            key.b = b;
            map->find(&it, &key);
            if (it.mpNode != map->mpBucketArray[map->mnBucketCount] &&
                it.mpNode->mComp >= 0)
                return ((unsigned)i << 24) | (unsigned)it.mpNode->mComp;
        }
    }
    return 0xffffffffu;
}

// ===========================================================================
// @ 0x00a6d840
unsigned cEffectsManager::FUN_00a6d840(const char* s)
{
    if (s == 0)
        return (unsigned)(size_t)mWorld;
    if (isdigit((unsigned char)*s) != 0) {
        unsigned key = (unsigned)strtoul(s, 0, 0);
        HashTable* h = &mHash;
        HashIter it;
        HashIter* r = h->find(&it, &key);
        if (r->mpNode != h->mpBucketArray[h->mnBucketCount])
            return (unsigned)(size_t)r->mpNode->mValue;
    }
    return 0;
}

// ===========================================================================
// @ 0x00a6d8c0
struct CopyRec {
    EString a;      // +0x00
    EString b;      // +0x10
    void*   ref;    // +0x20
};

CopyRec* FUN_00a6d8c0(CopyRec* first, CopyRec* last, CopyRec* dest)
{
    if (first != last) {
        do {
            if (first != dest)
                dest->a.assign(first->a.mpBegin, first->a.mpEnd);
            if (&first->b != &dest->b)
                dest->b.assign(first->b.mpBegin, first->b.mpEnd);
            void* nv = first->ref;
            void* ov = dest->ref;
            if (nv != ov) {
                if (nv != 0)
                    ((IRefCounted*)nv)->AddRef();
                dest->ref = nv;
                if (ov != 0)
                    ((IRefCounted*)ov)->Release();
            }
            ++dest;
            ++first;
        } while (first != last);
    }
    return dest;
}

// ===========================================================================
// @ 0x00a6d950
bool cEffectsManager::Shutdown()
{
    if (!mInitialized)
        return true;
    mInitialized = false;

    int* pB = gTblB;
    do {
        void (*fn)(int) = (void (*)(int))*pB;
        if (fn != 0)
            fn(0);
        pB += 8;
    } while (pB < &gTblBEnd);

    int* pA = gTblA;
    do {
        void (*fn)(int) = (void (*)(int))*pA;
        if (fn != 0)
            fn(0);
        pA += 9;
    } while (pA < &gTblAEnd);

    if (mWorld != 0) {
        IWorld* w = mWorld;
        mWorld = 0;
        w->Release();
    }

    {
        HashNode** bucket = mHash.mpBucketArray;
        HashNode* node = HashFirst(bucket);
        HashNode* end = mHash.mpBucketArray[mHash.mnBucketCount];
        while (node != end) {
            ((IValue*)node->mValue)->v50();
            HashNext(bucket, node);
        }
    }
    ((HashOps*)&mHash)->DoFreeNodes((void**)mHash.mpBucketArray, mHash.mnBucketCount);
    mHash.mnElementCount = 0;

    if (m1f0 != 0) {
        IComponent* c = m1f0;
        m1f0 = 0;
        c->Release2();
    }
    for (int i = 0; i < 12; ++i) {
        IComponent* c = m1f4[i];
        if (c != 0) {
            m1f4[i] = 0;
            c->Release2();
        }
    }
    return true;
}

// ===========================================================================
// @ 0x00a6da80
bool cEffectsManager::FUN_00a6da80(unsigned key)
{
    HashTable* h = &mHash;
    HashIter it;
    HashIter* r = h->find(&it, &key);
    if (r->mpNode != h->mpBucketArray[h->mnBucketCount]) {
        IValue* v = (IValue*)r->mpNode->mValue;
        v->v50();
        IValue* old = (IValue*)r->mpNode->mValue;
        if (old != 0) {
            r->mpNode->mValue = 0;
            old->Release();
        }
        h->erase(it);
        return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00a6db00
bool cEffectsManager::FUN_00a6db00(int a, int b, unsigned c)
{
    unsigned r = FUN_00a6d7b0(a, b);
    if ((int)r < 0)
        return false;
    ICollection* coll = mCollectionsBegin[(int)r >> 24];
    return ((IDrawableCall*)coll)->UseCollision(r & 0xffffff, c);
}

// ===========================================================================
// @ 0x00a6db40
cEffectsManager::~cEffectsManager()
{
    mpVtbl = (void*)kVtEffMgr;
    mpRefVtbl = (void*)kVtRefCnt;

    if ((mName.mpCapacity - mName.mpBegin) > 1 && mName.mpBegin != 0)
        operator_delete__(mName.mpBegin);

    if (mWorld != 0)
        mWorld->Release();

    ((HashOps*)&mHash)->DoFreeNodes((void**)mHash.mpBucketArray, mHash.mnBucketCount);
    mHash.mnElementCount = 0;
    if (mHash.mnBucketCount > 1)
        operator_delete__(mHash.mpBucketArray);

    for (int i = 11; i >= 0; --i) {
        IComponent* c = m1f4[i];
        if (c != 0)
            c->Release2();
    }
    if (m1f0 != 0)
        m1f0->Release2();

    if ((mStatsStr.mpCapacity - mStatsStr.mpBegin) > 1 && mStatsStr.mpBegin != 0)
        operator_delete__(mStatsStr.mpBegin);

    if (m48 != 0)
        m48->Release();
    if (m44 != 0)
        m44->Release();
    if (mRenderer != 0)
        mRenderer->Release();

    ((VectorObj*)&mCollectionsBegin)->dtor();
    mpRefVtbl = (void*)kVtGme;
}

// ===========================================================================
// @ 0x00a6dc60
bool cEffectsManager::Init()
{
    if (mInitialized)
        return true;
    mInitialized = true;
    FUN_011e073e(&mResInfo, 0, 0x4c);

    InitParams params;
    params.a = kOne;
    params.b = kOne;
    params.c = kPoint9;
    params.d = kZero;
    params.e = kOne;
    params.f = 1;
    params.g = kPoint4;
    params.h = 0;
    ((VfnA8)(*(void***)this)[0xa8 / 4])(this, &params);

    mE8 = 1000;

    {
        void* p = EAAllocate(0xc, kSwarmSurface, 0, 0, 0, 0);
        if (p != 0) {
            *(int*)((char*)p + 8) = 0;
            *(const void**)p = (const void*)kVtA2c;
            *(const void**)((char*)p + 4) = (const void*)kVtRel;
        }
        ((Vfn78)(*(void***)this)[0x78 / 4])(this, 0x8e88fab0, 0, p);
    }
    {
        void* p = EAAllocate(0xc, kSwarmSurface, 0, 0, 0, 0);
        if (p != 0) {
            *(int*)((char*)p + 8) = 0;
            *(const void**)p = (const void*)kVtA64;
            *(const void**)((char*)p + 4) = (const void*)kVtRel;
        }
        ((Vfn78)(*(void***)this)[0x78 / 4])(this, 0xce9f4d94, 0, p);
    }
    {
        void* p = EAAllocate(0xc, kSwarmSurface, 0, 0, 0, 0);
        if (p != 0) {
            *(int*)((char*)p + 8) = 0;
            *(const void**)p = (const void*)kVtA98;
            *(const void**)((char*)p + 4) = (const void*)kVtRel;
        }
        ((Vfn78)(*(void***)this)[0x78 / 4])(this, 0xae88fac6, 0, p);
    }
    {
        void* p = EAAllocate(0xc, kSwarmSurface, 0, 0, 0, 0);
        if (p != 0) {
            *(int*)((char*)p + 8) = 0;
            *(const void**)p = (const void*)kVtAcc;
            *(const void**)((char*)p + 4) = (const void*)kVtRel;
        }
        ((Vfn78)(*(void***)this)[0x78 / 4])(this, 0xee8a4494, 0, p);
    }

    {
        int* pA = gTblA;
        do {
            void (*fn)(int) = (void (*)(int))*pA;
            if (fn != 0)
                fn(1);
            pA += 9;
        } while (pA < &gTblAEnd);
    }
    {
        int* pB = gTblB;
        do {
            void (*fn)(int) = (void (*)(int))*pB;
            if (fn != 0)
                fn(1);
            pB += 8;
        } while (pB < &gTblBEnd);
    }

    IWorld* w;
    {
        void* mem = EAAllocate(0xa4, kSwarm, 0, 0, 0, 0);
        if (mem != 0)
            w = (IWorld*)((cEffectsWorld*)mem)->ctor(this, &mDensity);
        else
            w = 0;
    }
    w->v4c();
    w->v1c(mRenderer);

    IWorld* old = mWorld;
    if (w != old) {
        w->AddRef();
        mWorld = w;
        if (old != 0)
            old->Release();
    }

    {
        unsigned key = 0;
        IWorld** slot = (IWorld**)mHash.f(&key);
        IWorld* cur = *slot;
        if (w != cur) {
            w->AddRef();
            *slot = w;
            if (cur != 0)
                cur->Release();
        }
    }
    return true;
}

// ===========================================================================
// @ 0x00a6ded0
void cEffectsManager::SetRenderer(IRenderer* p)
{
    IRenderer* old = mRenderer;
    if (p != old) {
        if (p != 0)
            p->AddRef();
        mRenderer = p;
        if (old != 0)
            old->Release();
    }
    if (mHash.mnElementCount != 0) {
        unsigned key = 0;
        IWorld* w = *(IWorld**)mHash.f(&key);
        w->v1c(p);
    }
}

// ===========================================================================
// @ 0x00a6df30
IWorld* cEffectsManager::CreateWorld(unsigned id, unsigned b)
{
    (void)b;
    IWorld* w;
    {
        void* mem = EAAllocate(0xa4, kSwarm, 0, 0, 0, 0);
        if (mem != 0)
            w = (IWorld*)((cEffectsWorld*)mem)->ctor(this, &mDensity);
        else
            w = 0;
    }
    w->v4c();
    w->v1c(mRenderer);

    IWorld** slot = (IWorld**)mHash.f(&id);
    IWorld* cur = *slot;
    if (w != cur) {
        w->AddRef();
        *slot = w;
        if (cur != 0)
            cur->Release();
    }
    return w;
}

}}  // namespace EA::Swarm
