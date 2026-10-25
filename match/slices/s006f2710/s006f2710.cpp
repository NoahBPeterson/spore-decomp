// Slice s006f2710 — SP::cEffectsResources (effect-resource table) helpers.
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE.
#include "types.h"
#include <intrin.h>

#pragma intrinsic(_InterlockedIncrement, _InterlockedDecrement, _InterlockedExchange)

// ---- external functions ----------------------------------------------------
extern "C" void EASTL_allocator_deallocate(void* p);                          // 0x00f47380
void* EAAllocate(unsigned int n, const char* name, int flags, int align,
                 const char* file, int line);                                // 0x00f473a0
void* EffectsManager();                                                      // 0x0067ddd0
extern "C" bool GetPropertyAsFloatArray(void* p, unsigned id, int* count,
                                        void** out);                         // 0x006a08b0

void __stdcall FreeChainsA(void** buckets, unsigned count);                  // 0x006f2270
void __stdcall FreeChainsB(void** buckets, unsigned count);                  // 0x006f22c0
void __stdcall FreeChainsC(void** buckets, unsigned count);                  // 0x006f2430

// ---- external data ---------------------------------------------------------
extern void* g_baseVtable[];        // 0x0140b5e8
extern void* g_derivedVtable[];     // 0x0140b638
extern void* g_secVtableA[];        // 0x0140b630
extern void* g_secVtableB[];        // 0x0140b62c
extern void* g_abilityVtable[];     // 0x013ef094
extern void* g_refcountVtable[];    // 0x0140b5a0
extern void* g_emptyBucketArray[];  // 0x0154df28
extern void* g_mapDescVtable[];     // 0x01453948
extern float g_mapRowDefaults[4];   // 0x0161917c
extern const float kOne;            // 0x01485720
extern const float kTwo;            // 0x01470f1c

// ---- interfaces reached through pointer fields -----------------------------
struct IEffectFactory {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void* Create(unsigned lo, unsigned hi, int zero);        // +0x20
};
struct IEffectLookup {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09();
    virtual void* Lookup(unsigned key);                              // +0x28
};
struct IRefCounted {
    virtual void Destroy(int flags);                                 // +0x00
    virtual void Release();                                          // +0x04
};

// ---- containers ------------------------------------------------------------
struct PtrVec {
    void** mpBegin;   // +0x00
    void** mpEnd;     // +0x04
    void** mpCap;     // +0x08
    void DoInsertValue(void** pos, void* const& v);                  // 0x004558a0
    void push_back(void* v)
    {
        if (mpEnd < mpCap)
            *mpEnd++ = v;
        else
            DoInsertValue(mpEnd, v);
    }
    void* front() const { return *mpBegin; }
};

// Four-byte-key hash table (find at 0x00685f30, insert at 0x006f21b0).
struct HtTable {
    unsigned mHash;         // +0x00
    void**   mBuckets;      // +0x04
    unsigned mBucketCount;  // +0x08
    unsigned mElementCount; // +0x0c
    unsigned* FindOrInsert2(const unsigned* key);                    // 0x006f2510
};

struct Swarm {
    void*  mpVtbl;          // +0x00
    long   mRefCount;       // +0x04
    PtrVec mVec;            // +0x08
    Swarm* Init();                                                   // 0x0077d1d0
    void   Push(void* desc);                                         // 0x0077d970
    void   AddRef() { _InterlockedIncrement(&mRefCount); }
    void   Release()
    {
        if (_InterlockedDecrement(&mRefCount) == 0)
        {
            _InterlockedExchange(&mRefCount, 1);
            ((void (__fastcall*)(void*, int))((void**)mpVtbl)[0])(this, 1);
        }
    }
};

struct Graphics {
    void*          mpVtbl;   // +0x00
    unsigned short m4;       // +0x04
    unsigned short m6;       // +0x06
    void*          mp8;      // +0x08
    unsigned       mCount;   // +0x0c
    Graphics* Init();                                                // 0x0040d010
    unsigned  Add(int key, unsigned val);                            // 0x0077cb10
};

// A row description handed to a Swarm (0x10c for the shared row, 0x20 for the
// short per-element description).
struct MapDescription {
    void*          mpVtbl;      // +0x00
    unsigned short m4;          // +0x04
    unsigned short m6;          // +0x06
    float*         mpRows;      // +0x08
    float          mRows[0x40]; // +0x0c
};

// ---- element info ----------------------------------------------------------
union ElemData {
    unsigned __int64 mData;     // +0x08
    float*           mpFloats;
    void*            mpObj;
    float            mFloat;    // low word reinterpreted as float
};
struct ElemInfo {
    unsigned       mType;    // +0x00
    unsigned       mFlags;   // +0x04
    ElemData       mValue;   // +0x08
    unsigned short mCount;   // +0x10
    unsigned char  mKind;    // +0x12
    unsigned char  mPad[5];  // +0x13
};
struct Info {
    char      mPad0[0x10];
    unsigned  m10;           // +0x10
    unsigned  m14;           // +0x14
    ElemInfo* mpElems;       // +0x18
    ElemInfo* mpElemsEnd;    // +0x1c
};

// ---- SP::cEffectsResources -------------------------------------------------
struct cEffectsResources {
    void*           mpVtbl;      // +0x00
    HtTable         mTableA;     // +0x04
    float           mA14;        // +0x14
    float           mA18;        // +0x18
    float           mA1c;        // +0x1c
    unsigned        mPad20;      // +0x20
    HtTable         mTableB;     // +0x24
    float           mB34;        // +0x34
    float           mB38;        // +0x38
    float           mB3c;        // +0x3c
    unsigned        mPad40;      // +0x40
    void*           mpSecA;      // +0x44
    long            mRefCount;   // +0x48
    void*           mpSecB;      // +0x4c
    void*           mp50;        // +0x50
    IEffectFactory* mp54;        // +0x54
    IEffectLookup*  mp58;        // +0x58
    IRefCounted*    mp5c;        // +0x5c
    void*           mp60;        // +0x60
    void*           mp64;        // +0x64
    void*           mp68;        // +0x68
    unsigned        mPad6c;      // +0x6c
    unsigned        mPad70;      // +0x70
    void*           mp74;        // +0x74
    void*           mp78;        // +0x78
    void*           mp7c;        // +0x7c
    unsigned        mPad80[2];   // +0x80
    HtTable         mTableC;     // +0x88
    float           mC98;        // +0x98
    float           mC9c;        // +0x9c
    float           mCa0;        // +0xa0
    unsigned        mPadA4;      // +0xa4
    HtTable         mTableD;     // +0xa8
    float           mDb8;        // +0xb8
    float           mDbc;        // +0xbc
    float           mDc0;        // +0xc0

    int Process(void* key, unsigned unused, Info* info);             // 0x006f2710
};

// ---- helpers ---------------------------------------------------------------
static void CopyRowsClamped(MapDescription* d, int idx, const float* src, int count)
{
    int end = idx + count;
    if (end > 0x40)
        end = 0x40;
    for (int i = idx; i < end; ++i)
        d->mRows[i] = src[i - idx];
}

static MapDescription* NewSharedRows()
{
    MapDescription* d = (MapDescription*)EAAllocate(0x10c, "Graphics", 0, 0, 0, 0);
    if (d)
    {
        d->m4 = 0x206;
        d->m6 = 0x100;
        d->mpVtbl = g_mapDescVtable;
        d->mpRows = d->mRows;
        for (int i = 0; i < 0x40; ++i)
            d->mRows[i] = g_mapRowDefaults[i & 3];
    }
    return d;
}

// ---- EffectsManager virtual-dispatch stubs ---------------------------------
struct IVT_A { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
               virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
               virtual void a8(); virtual void a9(); };
struct IVT_B : IVT_A { virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3();
               virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7();
               virtual void b8(); virtual void b9(); };
struct IVT_C : IVT_B { virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3();
               virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7();
               virtual void c8(); virtual void c9(); };
struct IVT_D : IVT_C { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
               virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
               virtual void SetState(int a, bool b); };

// ---- 0x006f2f30 -------------------------------------------------------------
// @ 0x006f2f30
int __stdcall RetMinus1(int, int, int, int)
{
    return -1;
}

// ---- 0x006f2f40 -------------------------------------------------------------
// @ 0x006f2f40
int __stdcall RetThird(int, int, int c)
{
    return c;
}

// ---- 0x006f3290 -------------------------------------------------------------
// @ 0x006f3290
void ResetEffectStates()
{
    IVT_D* m = (IVT_D*)EffectsManager();
    m->SetState(0, 0);
    m->SetState(1, 0);
    m->SetState(2, 0);
    m->SetState(3, 1);
}

// ---- 0x006f33d0 -------------------------------------------------------------
struct IVT33d0 {
    virtual void v0();
    virtual void Release();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12(int);
};
struct Owner33d0 {
    char pad0[0x34];
    IVT33d0* mpAt34;   // +0x34
    char pad1[0x58 - 0x38];
    int mAt58;         // +0x58
    void ReleaseIf();
};
// @ 0x006f33d0
void Owner33d0::ReleaseIf()
{
    if (mAt58 >= 0) {
        mpAt34->v12(mAt58);
        IVT33d0* p = mpAt34;
        if (p) {
            mpAt34 = 0;
            p->Release();
        }
        mAt58 = -1;
    }
}

// ---- 0x006f2fb0 -------------------------------------------------------------
// @ 0x006f2fb0
cEffectsResources* __fastcall Ctor2fb0(cEffectsResources* this_)
{
    this_->mpVtbl = g_baseVtable;
    this_->mA14 = kOne;
    this_->mA18 = kTwo;
    this_->mTableA.mBucketCount = 1;
    this_->mTableA.mBuckets = g_emptyBucketArray;
    this_->mTableA.mElementCount = 0;
    this_->mA1c = 0.0f;
    this_->mB34 = kOne;
    this_->mB38 = kTwo;
    this_->mTableB.mElementCount = 0;
    this_->mB3c = 0.0f;
    this_->mTableB.mBucketCount = 1;
    this_->mTableB.mBuckets = g_emptyBucketArray;
    return this_;
}

// ---- 0x006f2e80 -------------------------------------------------------------
__declspec(noinline) void __fastcall BaseDtor2e80(cEffectsResources* this_);
// @ 0x006f2e80
void __fastcall BaseDtor2e80(cEffectsResources* this_)
{
    this_->mpVtbl = g_baseVtable;
    FreeChainsB(this_->mTableB.mBuckets, this_->mTableB.mBucketCount);
    this_->mTableB.mElementCount = 0;
    if (this_->mTableB.mBucketCount > 1)
        EASTL_allocator_deallocate(this_->mTableB.mBuckets);
    FreeChainsA(this_->mTableA.mBuckets, this_->mTableA.mBucketCount);
    this_->mTableA.mElementCount = 0;
    if (this_->mTableA.mBucketCount > 1)
        EASTL_allocator_deallocate(this_->mTableA.mBuckets);
}

// ---- 0x006f2f70 -------------------------------------------------------------
// @ 0x006f2f70
void __fastcall Dtor2f70(cEffectsResources* this_)
{
    this_->mpSecA = g_abilityVtable;
    BaseDtor2e80(this_);
}

// ---- 0x006f3030 -------------------------------------------------------------
// @ 0x006f3030
void __fastcall Dtor3030(cEffectsResources* this_)
{
    this_->mpVtbl = g_derivedVtable;
    this_->mpSecA = g_secVtableA;
    this_->mpSecB = g_secVtableB;
    FreeChainsB(this_->mTableD.mBuckets, this_->mTableD.mBucketCount);
    this_->mTableD.mElementCount = 0;
    if (this_->mTableD.mBucketCount > 1)
        EASTL_allocator_deallocate(this_->mTableD.mBuckets);
    FreeChainsC(this_->mTableC.mBuckets, this_->mTableC.mBucketCount);
    this_->mTableC.mElementCount = 0;
    if (this_->mTableC.mBucketCount > 1)
        EASTL_allocator_deallocate(this_->mTableC.mBuckets);
    if (this_->mp74 && *(int*)((char*)this_->mp74 - 4) != 0)
        EASTL_allocator_deallocate(this_->mp74);
    if (this_->mp60 && *(int*)((char*)this_->mp60 - 4) != 0)
        EASTL_allocator_deallocate(this_->mp60);
    if (this_->mp5c)
        this_->mp5c->Release();
    this_->mpSecA = g_abilityVtable;
    BaseDtor2e80(this_);
}

// ---- 0x006f31b0 -------------------------------------------------------------
// @ 0x006f31b0
cEffectsResources* __fastcall Ctor31b0(cEffectsResources* this_)
{
    Ctor2fb0(this_);
    this_->mpSecA = g_abilityVtable;
    this_->mRefCount = 0;
    this_->mpSecB = g_refcountVtable;
    this_->mpVtbl = g_derivedVtable;
    this_->mpSecA = g_secVtableA;
    this_->mpSecB = g_secVtableB;
    this_->mp50 = 0;
    this_->mp54 = 0;
    this_->mp58 = 0;
    this_->mp5c = 0;
    this_->mp60 = 0;
    this_->mp64 = 0;
    this_->mp68 = 0;
    this_->mp74 = 0;
    this_->mp78 = 0;
    this_->mp7c = 0;
    this_->mC98 = kOne;
    this_->mC9c = kTwo;
    this_->mTableC.mBucketCount = 1;
    this_->mTableC.mBuckets = g_emptyBucketArray;
    this_->mTableC.mElementCount = 0;
    this_->mCa0 = 0.0f;
    this_->mDb8 = kOne;
    this_->mDbc = kTwo;
    this_->mTableD.mBuckets = g_emptyBucketArray;
    this_->mTableD.mElementCount = 0;
    this_->mDc0 = 0.0f;
    this_->mTableD.mBucketCount = 1;
    return this_;
}

// ---- 0x006f2710 -------------------------------------------------------------
// @ 0x006f2710
int cEffectsResources::Process(void* key, unsigned, Info* info)
{
    if ((info->m10 & info->m14) == 0xffffffffu)
        return 0;

    void* token = mp58->Lookup(info->m10);

    Swarm* swarm = (Swarm*)EAAllocate(0x1c, "Swarm", 0, 0, 0, 0);
    swarm = swarm ? swarm->Init() : 0;

    int count = (int)(info->mpElemsEnd - info->mpElems);
    ElemInfo* elems = info->mpElems;

    // A "kind 6" element attaches a fresh Graphics object to the swarm.
    for (int i = 0; i < count; ++i)
    {
        if (elems[i].mKind == 6)
        {
            Graphics* g = (Graphics*)EAAllocate(0x70, "Graphics", 0, 0, 0, 0);
            g = g ? g->Init() : 0;
            swarm->mVec.push_back(g);
            break;
        }
    }

    MapDescription* shared = 0;
    for (int i = 0; i < count; ++i)
    {
        ElemInfo* e = &elems[i];
        unsigned mType = e->mType;
        unsigned mFlags = e->mFlags;
        int idx = (int)(mType - 0x10000) >> 4;

        if (idx >= 0)
        {
            if (!shared)
                shared = NewSharedRows();
            if (e->mKind == 0)
            {
                if (idx < 0x40)
                    shared->mRows[idx] = e->mValue.mFloat;
            }
            else if ((short)e->mCount > 0)
            {
                CopyRowsClamped(shared, idx, e->mValue.mpFloats, (short)e->mCount);
            }
        }
        else if (mFlags == 0)
        {
            switch (mType)
            {
            case 0:
            case 1:
            {
                unsigned v = (unsigned)mp54->Create((unsigned)e->mValue.mData,
                                                    (unsigned)(e->mValue.mData >> 32), 0);
                if (v)
                    ((Graphics*)swarm->mVec.front())->Add((int)mType, v);
                break;
            }
            case 2: case 3: case 4: case 5: case 6: case 7:
            {
                unsigned v = (unsigned)mp54->Create((unsigned)e->mValue.mData,
                                                    (unsigned)(e->mValue.mData >> 32), 0);
                if (v)
                    ((Graphics*)swarm->mVec.front())->Add((int)mType - 2, v);
                break;
            }
            case 8:
            {
                if (!shared)
                    shared = NewSharedRows();
                int n = (short)e->mCount;
                if (n > 0)
                    CopyRowsClamped(shared, 0, e->mValue.mpFloats, n);
                break;
            }
            case 9:
            {
                MapDescription* d = (MapDescription*)EAAllocate(0x20, "Graphics", 0, 0, 0, 0);
                if (d)
                {
                    d->m4 = 0x205;
                    d->m6 = 0x14;
                    d->mpVtbl = g_mapDescVtable;
                    d->mpRows = d->mRows;
                    float* s = e->mValue.mpFloats;
                    d->mRows[0] = s[0];
                    d->mRows[1] = s[1];
                    d->mRows[2] = s[2];
                    d->mRows[3] = s[3];
                    d->mRows[4] = s[4];
                }
                swarm->Push(d);
                break;
            }
            }
        }
    }
    if (shared)
        swarm->mVec.push_back(shared);

    swarm->AddRef();

    unsigned* slot = mTableC.FindOrInsert2((const unsigned*)&key);
    slot[0] = (unsigned)token;
    Swarm* old = (Swarm*)slot[1];
    if (swarm != old)
    {
        if (swarm)
            swarm->AddRef();
        slot[1] = (unsigned)swarm;
        if (old)
            old->Release();
    }
    if (swarm)
        swarm->Release();
    return 1;
}

// ---- 0x006f32e0 -------------------------------------------------------------
// This function compares floats with SSE comiss (the retail module is /fp:fast);
// scope the same effect to this one function so the slice keeps its /arch:SSE flags.
#pragma float_control(precise, off)
// @ 0x006f32e0
void __cdecl ApplyStateFromProperty(void* propList, float threshold)
{
    int count;
    float* arr;
    if (!GetPropertyAsFloatArray(propList, 0x1524f2e, &count, (void**)&arr) || count <= 0)
    {
        ResetEffectStates();
        return;
    }
    IVT_D* m = (IVT_D*)EffectsManager();
    m->SetState(0, arr[0] >= threshold);
    for (int i = 0; i < count - 1; ++i)
        m->SetState(i + 1, threshold > arr[i] && arr[i + 1] >= threshold);
    m->SetState(3, threshold > arr[count - 1]);
}
#pragma float_control(precise, on)
