// Slice s00a13fc0 -- EA::Audio::Group (connect/shutdown/ctor/dtor, hash-table ctor),
// EA::Audio::Playlist (choose/shuffle/clear) and rw::audio::core (Chorus, bit-depth
// mix helper).  Names come from the 2008 dev-build PDB where known.
#include "types.h"
#include <stdlib.h>
#include <string.h>
#include <new>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---------------------------------------------------------------------------
// Out-of-line callees (names carry their retail VA so the difftest resolver can
// bind them to the original code).
// ---------------------------------------------------------------------------
struct SystemAT;
SystemAT* FUN_00a206f0();                      // EA::Audio::GetSystemAT
void* FUN_00a16ad0(u32 size);
int   FUN_00a16d00(void* mem, int id);
void  FUN_00a16a30(void* self, void* server);
void  FUN_00a16a90(void* self, void* v);
void  FUN_00a136f0(void* out, void* key, int unused);
void  FUN_00a24480(void* self, void* buckets, u32 count);
void  FUN_00a22220(void* self, u32 n);
void  FUN_00a240b0(void* self, void* a, void* b, void* c, void* d, void* e, void* f);
u32   FUN_00921340(u32 n);
u32   FUN_009213c0(void* self, u32 v);
void  FUN_00921260(void* pool, void* begin, u32 n, u32 size, u32 align, u32 flags);
void  FUN_00a2f210();

// ===========================================================================
// EA::Audio::Playlist
// ===========================================================================
// retail layout: RefCount at +0, eastl::fixed_vector<unsigned,30> at +8
struct SoundList {
    unsigned* mpBegin;      // +0x00
    unsigned* mpEnd;        // +0x04
    unsigned* mpCapacity;   // +0x08
    unsigned  mBuffer[30];  // +0x0c

    unsigned* begin()       { return mpBegin; }
    unsigned* end()         { return mpEnd; }
    unsigned  size() const  { return (unsigned)(mpEnd - mpBegin); }

    // eastl::vector<unsigned, fixed_vector_allocator<...> >::erase
    __forceinline unsigned* erase(unsigned* first, unsigned* last)
    {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
        return first;
    }
};

struct Playlist {
    void*      mVtbl;        // +0x00 RefCountTemplate
    int        mRefCount;    // +0x04
    SoundList  mSounds;      // +0x08  (0x84 bytes)
    unsigned   mPad8c[3];    // +0x8c
    unsigned   mLastChoice;  // +0x98
    unsigned*  mpIterator;   // +0x9c

    unsigned Choose();                       // 0x00a146a0
    void     Shuffle();                      // 0x00a14730
    bool     Clear();                        // 0x00a147b0
};

// STL-style binder used by eastl::random_shuffle in this build.
struct pointer_to_unary_function {
    int (*mpFunc)(int);
    int operator()(int n) const { return mpFunc(n); }
};

// @ 0x00a14680
int __cdecl FUN_00a14680(int n)
{
    return rand() % n;
}

// @ 0x00a146a0
unsigned Playlist::Choose()
{
    if (mSounds.begin() == mSounds.end())
        return 0;
    if (mpIterator == 0 || mpIterator == mSounds.end())
        mpIterator = mSounds.begin();
    mLastChoice = *mpIterator++;
    return mLastChoice;
}

// @ 0x00a146e0
void __cdecl FUN_00a146e0(unsigned* first, unsigned* last,
                          pointer_to_unary_function& rng)
{
    for (unsigned* i = first + 1; i < last; ++i) {
        unsigned* j = first + rng((i - first) + 1);
        unsigned tmp = *i;
        *i = *j;
        *j = tmp;
    }
}

// @ 0x00a14730
void Playlist::Shuffle()
{
    pointer_to_unary_function rng = { &FUN_00a14680 };
    FUN_00a146e0(mSounds.mpBegin, mSounds.mpEnd, rng);
    mpIterator = mSounds.mpBegin;
    if (mSounds.size() > 1 && *mSounds.mpBegin == mLastChoice)
        Choose();
}

// @ 0x00a147b0
bool Playlist::Clear()
{
    mSounds.erase(mSounds.begin(), mSounds.end());
    mpIterator = mSounds.mpBegin;
    return true;
}

// ===========================================================================
// rw::audio::core::Chorus + bit-depth mix helper
// ===========================================================================
struct tDelayLine {
    int m0, m4, m8, mc, m10;
    tDelayLine();
    ~tDelayLine();
};

// @ 0x00a14980
tDelayLine::tDelayLine()
{
    m0 = 0;
    m4 = 0;
    m8 = 0;
    mc = 0;
    m10 = 0;
}

// element destructor (0x00a151a0 in retail, outside this slice)
tDelayLine::~tDelayLine()
{
}

struct AudioEffect {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual ~AudioEffect() {}
    char mData[0x20];           // +0x04 .. +0x24
};

struct Chorus : AudioEffect {
    tDelayLine mDelays[6];      // +0x24 .. +0x9c
    Chorus();
    ~Chorus();
};

// @ 0x00a149b0
Chorus::Chorus()
{
}

// @ 0x00a14a10
Chorus::~Chorus()
{
}

// Small descriptor initialised by 0x00a14940 and consumed by 0x00a14810.
struct MixSource {
    char  m00[0x0c];
    void* mpValue;              // +0x0c
    char  m10[0x11];
    u8    mChannels;            // +0x21
    char  m22[0x06];
    float mBits;                // +0x28 (16.0f)
    float mBlend;               // +0x30 (0.0f)
};

struct AudioBuffer {
    void* mp0;                  // +0x00
    float* mpData;              // +0x04
    char  m08[6];
    u16   mStride;              // +0x0e
};

struct MixCtx {
    char         m00000[0x3000c];
    AudioBuffer* mpSrc;         // +0x3000c
    AudioBuffer* mpDst;         // +0x30010
    char         m30014[0x0c];
    int          mCount;        // +0x30020
};

extern const float kFloat16;    // 16.0f
extern char gType_14bc0fc;      // "type" pointer stored at object +0

// @ 0x00a14940
bool __cdecl FUN_00a14940(void* p)
{
    if (p != 0)
        *(void**)p = &gType_14bc0fc;
    float* pf = (float*)((char*)p + 0x28);
    *pf = kFloat16;
    *(void**)((char*)p + 0x0c) = pf;
    *(float*)((char*)p + 0x30) = 0.0f;
    return true;
}

// @ 0x00a14810
bool __cdecl FUN_00a14810(MixSource* src, MixCtx* ctx)
{
    int n = 0x10 - (int)src->mBits;
    if (n != 0) {
        float blend = src->mBlend;
        u16   mask = (u16)~((1 << n) - 1);
        int   channels = src->mChannels;
        AudioBuffer* pa = ctx->mpSrc;
        AudioBuffer* pb = ctx->mpDst;
        int count = ctx->mCount;
        for (int i = 0; i < channels; i++) {
            float* s = (float*)((char*)pa->mpData + (u32)pa->mStride * i * 4);
            float* d = (float*)((char*)pb->mpData + (u32)pb->mStride * i * 4);
            for (int j = 0; j < count; j++) {
                float v = s[j];
                if (blend == 0.0f) {
                    d[j] = v;
                } else {
                    float q = (float)(short)((int)(v * 32767.0f) & mask) * 3.0518509447574615e-05f;
                    if (blend != 1.0f)
                        q = q * blend + v * (1.0f - blend);
                    d[j] = q;
                }
            }
        }
        ctx->mpDst = pa;
        ctx->mpSrc = pb;
    }
    return true;
}

// ===========================================================================
// EA::Audio::Group
// ===========================================================================
struct PHNode { u32 hash; void* value; PHNode* next; };   // 12 bytes

// A fixed-capacity hash table with an embedded eastl::fixed_pool.
struct PHTable {
    u32      m00;
    PHNode** mpBuckets;        // +0x04
    u32      mnBucketCount;    // +0x08
    u32      mnElementCount;   // +0x0c
    u32      m10;
    u32      m14;
    u32      m18;
    PHNode*  mpFreeList;       // +0x1c
    u32      m20;
    void*    mpPoolBegin;      // +0x24
    void*    mpPoolEnd;        // +0x28
    u32      m2c;
    void*    mpInline;         // +0x30

    void FreeBuckets(PHNode** buckets, u32 count);
    ~PHTable();
};

PHTable::~PHTable()
{
    FreeBuckets(mpBuckets, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1 && mpBuckets != (PHNode**)mpInline) {
        if ((char*)mpBuckets < (char*)mpPoolBegin || (char*)mpPoolEnd <= (char*)mpBuckets)
            operator delete(mpBuckets);
        else {
            *(void**)mpBuckets = mpFreeList;
            mpFreeList = (PHNode*)mpBuckets;
        }
    }
}

// mMixees: first member hash table (0xff0 bytes, FHT1 ctor at 0x00a2f210).
struct FHT1 {
    PHTable mTable;                              // +0x00
    char    mPad[0xff0 - sizeof(PHTable)];
    FHT1() {}
    FHT1(unsigned& a, unsigned& b);
};

// mRegisters / mAggregates: 0x438 bytes, ctor at 0x00a144c0.
struct HTable28 {
    PHTable mTable;                              // +0x00
    char    mPad[0x438 - sizeof(PHTable)];
    HTable28() {}
    __declspec(noinline) HTable28(unsigned& a, unsigned& b);
};

// @ 0x00a144c0
HTable28::HTable28(unsigned& a, unsigned& b)
{
    char* pool = (char*)this + 0x104;
    FUN_00921260((char*)this + 0x0c, pool, 600, 0xc, 4, 0);
    mTable.m10 = 0x461c4000;      // 10000.0f
    mTable.m14 = 0x40000000;      // 2.0f
    mTable.m18 = 0;
    u32 h = FUN_00921340(0x33);
    FUN_00a240b0(this, &a, &b, &a, &b, &a, &b);
    (void)h;
    u32 cap = FUN_009213c0(this, mTable.m10);
    if (mTable.mnBucketCount < cap)
        FUN_00a22220(this, cap);
}

struct MixableBase {
    void* mVtbl;
};

struct RefCountBase {
    void* mRefVtbl;
    ~RefCountBase() { mRefVtbl = (void*)0x13ef094; }
};

struct Group : MixableBase, RefCountBase {
    int       mRefCount;     // +0x08
    u32       mId;           // +0x0c
    u32       mPauseCount;   // +0x10
    FHT1      mMixees;       // +0x14
    HTable28  mRegisters;    // +0x1004
    HTable28  mAggregates;   // +0x143c

    Group(u32 id);
    bool ConnectPrimitive(u32 id, void* prim);
    bool Shutdown();
    ~Group();
};

// @ 0x00a145c0
Group::Group(u32 id)
{
    mRefVtbl = (void*)0x13ef094;
    mRefCount = 0;
    mId = id;
    mPauseCount = 0;
    mVtbl = (void*)0x1449454;
    mRefVtbl = (void*)0x1449450;
    new (&mMixees) FHT1(id, id);
    new (&mRegisters) HTable28(id, id);
    new (&mAggregates) HTable28(id, id);
}

// @ 0x00a141c0
bool Group::Shutdown()
{
    // 1. ask every mixee to disconnect
    PHNode** b = mMixees.mTable.mpBuckets;
    PHNode* n = b[0];
    unsigned bi = 0;
    if (!n) {
        do { n = b[++bi]; } while (!n);
    }
    PHNode* end = b[mMixees.mTable.mnBucketCount];
    while (n != end) {
        u32 key = n->hash;
        n = n->next;
        if (!n) { do { n = b[++bi]; } while (!n); }
        ((void (__thiscall*)(Group*, u32))(*(void***)this)[0x2c / 4])(this, key);
    }

    // 2. release registers that point back at this group
    b = mRegisters.mTable.mpBuckets;
    n = b[0];
    bi = 0;
    if (!n) {
        do { n = b[++bi]; } while (!n);
    }
    end = b[mRegisters.mTable.mnBucketCount];
    while (n != end) {
        void* v = n->value;
        if (((void* (__thiscall*)(void*))(*(void***)v)[0x30 / 4])(v) == this)
            ((void (__thiscall*)(void*))(*(void***)v)[0x14 / 4])(v);
        n = n->next;
        if (!n) { do { n = b[++bi]; } while (!n); }
    }
    mRegisters.mTable.FreeBuckets(mRegisters.mTable.mpBuckets, mRegisters.mTable.mnBucketCount);
    mRegisters.mTable.mnElementCount = 0;

    // 3. release the remaining aggregates
    b = mAggregates.mTable.mpBuckets;
    n = b[0];
    bi = 0;
    if (!n) {
        do { n = b[++bi]; } while (!n);
    }
    end = b[mAggregates.mTable.mnBucketCount];
    while (n != end) {
        void* v = n->value;
        ((void (__thiscall*)(void*))(*(void***)v)[0x14 / 4])(v);
        n = n->next;
        if (!n) { do { n = b[++bi]; } while (!n); }
    }
    mAggregates.mTable.FreeBuckets(mAggregates.mTable.mpBuckets, mAggregates.mTable.mnBucketCount);
    mAggregates.mTable.mnElementCount = 0;
    return true;
}

// @ 0x00a14380
Group::~Group()
{
    mVtbl = (void*)0x1449454;
    mRefVtbl = (void*)0x1449450;
}

// @ 0x00a13fc0
bool Group::ConnectPrimitive(u32 id, void* prim)
{
    SystemAT* sys = FUN_00a206f0();
    void* handle = ((void* (__thiscall*)(SystemAT*, u32))(*(void***)sys)[0xf8 / 4])(sys, id);
    if (handle == 0)
        return false;

    PHNode** b = mAggregates.mTable.mpBuckets;
    PHNode* n = b[0];
    unsigned bi = 0;
    if (!n) {
        do { n = b[++bi]; } while (!n);
    }
    PHNode* end = b[mAggregates.mTable.mnBucketCount];
    void* obj;
    if (n != end) {
        obj = n->value;
        if (obj) {
            ((void (__thiscall*)(void*))(*(void***)obj)[0x00 / 4])(obj);
        }
        ((void (__thiscall*)(void*, void*))(*(void***)obj)[0x10 / 4])(obj, prim);
    } else {
        void* mem = FUN_00a16ad0(0x6c);
        obj = 0;
        if (mem)
            obj = (void*)FUN_00a16d00(mem, id);
        if (obj) {
            ((void (__thiscall*)(void*))(*(void***)obj)[0x00 / 4])(obj);
        }
        FUN_00a16a30(obj, handle);
        FUN_00a16a90(obj, handle);
        ((void (__thiscall*)(void*, void*))(*(void***)obj)[0x10 / 4])(obj, prim);
        ((void (__thiscall*)(void*))(*(void***)obj)[0x10 / 4])(obj);
        FUN_00a136f0(&mAggregates, &id, 0);
    }

    int r = ((int (__thiscall*)(void*))(*(void***)obj)[0x18 / 4])(obj);
    if (r == 1) {
        ((void (__thiscall*)(void*, int))(*(void***)obj)[0x2c / 4])(obj, 1);
        PHNode** b2 = mMixees.mTable.mpBuckets;
        PHNode* n2 = b2[0];
        unsigned bi2 = 0;
        if (!n2) {
            do { n2 = b2[++bi2]; } while (!n2);
        }
        PHNode* end2 = b2[mMixees.mTable.mnBucketCount];
        while (n2 != end2) {
            void* v = n2->value;
            ((void (__thiscall*)(void*, void*))(*(void***)v)[0x18 / 4])(v, obj);
            n2 = n2->next;
            if (!n2) { do { n2 = b2[++bi2]; } while (!n2); }
        }
    }
    ((void (__thiscall*)(void*))(*(void***)obj)[0x04 / 4])(obj);
    return true;
}
