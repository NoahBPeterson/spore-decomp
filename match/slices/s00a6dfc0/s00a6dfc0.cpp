// Slice s00a6dfc0 -- EA::Swarm::cEffectsManager collection vectors / effect-map
//   lookups and EA::Swarm::cEffectsParser resource-map lookups + DrawInfo parse.
//   16 functions.  Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE
#include "types.h"
#include <string.h>

// ---------------------------------------------------------------------------
// masked relocations modelled as ordinary callees
extern "C" void  MakeCaseInsensitive(void* s);                              // 0x8409b0
extern "C" void* EAAllocate(unsigned size, const char* a, int b, int c, const char* file, int line); // 0xf473a0
extern "C" void  operator_delete__(void* p);                                // 0xf47380
extern "C" void  v0093a560(void* sw, int units, bool b);                    // 0x93a560 Stopwatch ctor
extern "C" void  v00a6cdb0(void* p);                                        // 0xa6cdb0 cGlobalParams ctor
extern "C" void  v0011e073e(void* block, int val, int size);                // 0x11e073e operator new[]
extern "C" void  v005f7870(const void* a, const void* b, int n);            // 0x5f7870 eastl::Compare
extern "C" int   v005f7870r(const void* a, const void* b, int n);           // 0x5f7870 returns the ordering
extern "C" void* v009215c0(void* node);                                     // 0x9215c0 RBTreeDecrement
extern "C" bool  v00812210(void* a, void* b);                              // 0x812210 key compare
extern "C" void* v00898b80(void* out, void* a, void* b, void* c, void* d);  // 0x898b80 uninitialized_copy
extern "C" void* v00abced0(void* a, void* b, void* c);                      // 0xabced0 copy_backward
extern "C" void* v00a177f0(void* a, void* b, const void* v);                // 0xa177f0 fill
extern "C" void* v006e5760(void* a, unsigned n, const void* v);             // 0x6e5760 uninitialized_fill_n
extern "C" void* v00a11310(const void* a, const void* b, void* c);          // 0xa11310 memmove
extern "C" void  v00a0a360(void* vec, void* a, void* b);                    // 0xa0a360 SL71::v0a360
extern "C" void  v007e2be0(void* a, void* b);                               // 0x7e2be0 vector realloc
extern "C" void* v007e2ea0(void* out, void* ht);                            // 0x7e2ea0 hashtable find
extern "C" void  v00a6e9e0(void** out, void* map);                          // 0xa6e9e0 map find
extern "C" void  v00a6ea80(void** out, void* map);                          // 0xa6ea80 map insert
extern "C" void  v00b20930(void** out, void* key);                          // 0xb20930 MapStrFind::Find
extern "C" void  v00a6e570(void* out, void* node, void* key, int side);     // 0xa6e570 map insert-node
extern "C" void  v00a6e9e0(void** out, void* map);                          // 0xa6e9e0 map find
extern "C" void  v00a6ea80(void** out, void* map);                          // 0xa6ea80 map insert
extern "C" void  v00a6d8c0(void* a, void* b, void* c);                      // 0xa6d8c0 vector realloc helper
extern "C" void  v007e2be0(void* a, void* b);                               // 0x7e2be0 vector realloc helper
extern "C" void  v00a69310(void* obj);                                      // 0xa69310 collection refresh
extern "C" void  v00a72060(void* core, int filter);                         // 0xa72060
extern "C" const char** v00838330(void* args, const char* name, int n);      // 0x838330 OptionArguments
extern "C" const char** v00838130(void* args, const char* name, int* count, int lo, int hi); // 0x838130
extern "C" int   v008380b0(void* args, const char* flag);                   // 0x8380b0 HasFlag
extern "C" unsigned char v00840bb0(const char* s, const void* tbl);         // 0x840bb0 ParseEnum

// ---------------------------------------------------------------------------
// constant pools
extern const char  kTerrain[];      // 0x1455e4c "terrain"
extern const char  kWater[];        // 0x1455e44 "water"
extern const char  kTextureOpt[];   // 0x1455d84 "texture"
extern const char  kDrawOpt[];      // 0x1455e94 "draw"
extern const char  kBufferOpt[];    // 0x1455e8c "buffer"
extern const char  kLayerOpt[];     // 0x1455e84 "layer"
extern const char  kSortOffsetOpt[];// 0x1455e78 "sortOffset"
extern const char  kLightFlag[];    // 0x1455e70 "light"
extern const char  kNoFogFlag[];    // 0x1455e68 "noFog"
extern const char  kShadowFlag[];   // 0x142ee28 "shadow"
extern const char  kNoShadowFlag[]; // 0x1455e5c "noShadow"
extern const char  kNoCullFlag[];   // 0x1455e54 "noCull"
extern const char* gFlagUser1;      // 0x1554778 "user1"
extern const char* gFlagUser2;      // 0x155477c "user2"
extern const char* gFlagUser3;      // 0x1554780 "user3"
extern const char  gDecalEnumTbl[]; // 0x15546e8 enum table ptr
extern const char  kEaStlName[];    // 0x13f2150 "EASTL"
extern const char  kEaAllocFile[];  // 0x13ebb38 EASTL allocator.h
extern const float kOne;            // 0x1485720 1.0f
extern const float kTwo;            // 0x1470f1c 2.0f
extern const float kPoint9;         // 0x13ec4b4 0.9f
extern char  kVtEffMgr[];           // 0x1455b80
extern char  kVtRefCnt[];           // 0x1455b7c
extern char  kVtGme[];              // 0x13ef094
extern void* gEmptyString16;        // 0x1667bac
extern const float gFloatA;         // 0x1676a0c
extern const float gFloatB;         // 0x1676a10
extern const float gFloatC;         // 0x1676a14
extern int   gEmptyDecalTable[];    // 0x154df28 empty decal-manager table

namespace EA { namespace Swarm {

// ---------------------------------------------------------------------------
// eastl string8 (4 words) used for the scratch name buffer at parser +0x3c4
struct EString {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    void* mpAlloc;      // +0x0c
    void assign(const char* first, const char* last);   // 0x00454cb0
};

// ---------------------------------------------------------------------------
// the parser object; methods below are real members so __thiscall applies
struct DrawInfoTarget;
class cEffectsParser { public:
    char      _pad00[0x10];
    unsigned  mFlags;               // +0x10
    char      _pad14[0x0c];
    void*     mpColl;               // +0x20
    char      _pad24[0x20];
    int       m44;                  // +0x44
    char      _pad48[0x30];
    int       m78;                  // +0x78
    char      _pad7c[0x10];
    void*     mpSaveColl;           // +0x8c
    char      _pad90[0x28];
    char      mEditors[0x13 * 0x20]; // +0xb8
    char      mName[0x10];          // +0x3c4

    long long EffectsMapID(const char* s);                          // 00a6e600
    long long MapFindA(const char* s);                              // 00a6eaf0
    long long MapFindB(const char* s, int idx);                     // 00a6eb60
    long long MapFindC(const char* s, int idx);                     // 00a6ebd0
    long long LookupRes(int idx, const char* s);                    // 00a6ec40
    void      ParseDrawInfoOptions(void* args, void* obj, DrawInfoTarget* t); // 00a6ed80
    int       GetInheritedA(int a, int depth, void* c);             // 00a6f090
    int       GetInheritedB(int a, int depth, void* c);             // 00a6f0d0
};

// ---------------------------------------------------------------------------
// shared shapes
struct Ctrl {
    unsigned    mFlags;         // +0x10 (used by FUN_00a6ec40)
    int         m18;            // +0x18
    int         m1c;            // +0x1c
    void*       mpColl;         // +0x20 collection
    int         m44;            // +0x44 resource-id table pointer array
    int         m78;            // +0x78
    void*       mp82c;          // +0x8c save-collection
    char        mEditors[0x13 * 0x20];  // +0xb8
    char        mName[0x10];    // +0x3c4
};

struct DrawInfoTarget {
    int      m00;               // +0x00
    int      m04;               // +0x04
    char     m08;               // +0x08
    char     mType;             // +0x09 (0xf = text; else decal)
    char     mFlags;            // +0x0a
    char     mBuffer;           // +0x0b
    short    mLayer;            // +0x0c
    char     _pad0e[2];
    float    mSortOffset;       // +0x10
    char     _pad14[4];
    unsigned mResA;             // +0x18
    unsigned mResB;             // +0x1c
};

struct ArgScriptArgs {
    const char** OptionArguments(const char* name, int n);                  // 0x838330
    const char** OptionArguments(const char* name, int* count, int lo, int hi); // 0x838130
    char         HasFlag(const char* name);                                 // 0x8380b0
};

// object pointed at by cEffectsParser +0x20 (a cICollection-ish interface)
struct IResourceCollection {
    virtual void v00(); virtual void v04();
    virtual char v08(int a, const char* b, void* out);  // +0x08
    virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual int  v20(int idx, void* a, void* b);        // +0x20
    virtual void v24();
    virtual int  v28(int idx, void* a, void* b);        // +0x28
};

// ---------------------------------------------------------------------------
// eastl SimpleVector<unsigned> with an sp_vector_allocator
struct UIntVec {
    unsigned* mpBegin;      // +0x00
    unsigned* mpEnd;        // +0x04
    unsigned* mpCapacity;   // +0x08
    void reserve(unsigned n);                          // 0x004e0880
    void DoInsertValue(unsigned* pos, const unsigned* v); // 0x004558a0
};

// ---------------------------------------------------------------------------
// the effects manager; FUN_00a6dfc0 walks its root decal hash into a vector
// ---------------------------------------------------------------------------
// 3x3 matrix; only Assign() is referenced here
struct Matrix3 {
    float m[12];
    void Assign(const float* src);      // 0x0041cb40
};
extern const float gMatIdent[12];       // 0x1676ab8 identity matrix block

// ---------------------------------------------------------------------------
// eastl vector<T> as stored in the manager (12-byte header: begin/end/cap)
// FUN_00a6d8c0 appends a range and FUN_007e2be0 fixes up the tail pointer
struct VecBase {
    char*  mpBegin;         // +0x00
    char*  mpEnd;           // +0x04
    char*  mpCapacity;      // +0x08
    char*  Append(void* first, void* last);          // 0xa6d8c0
    void   FixTail(char* p);                         // 0x7e2be0
};

// ---------------------------------------------------------------------------
// refcounted collection interface stored in the manager's vector at +0x2c
struct ICollection {
    virtual void AddRef();      // +0x00
    virtual void Release();     // +0x04
};

class cEffectsManager { public:
    char      _pad00[0x2c];
    void**    mpCollBegin;          // +0x2c (vector of ICollection*)
    void**    mpCollEnd;            // +0x30
    void**    mpCollCapacity;       // +0x34
    char      _pad38[0x224 - 0x38];
    void*     mpHashF0;             // +0x224
    void**    mpBuckets;            // +0x228 (HashTable.mpBucketArray)
    int       mnBucketCount;        // +0x22c
    int       mnElementCount;       // +0x230
    void      FUN_00a6dfc0(void* vec);      // 00a6dfc0
    bool      FUN_00a6e050(void* p);        // 00a6e050
    void      FUN_00a6e320(VecBase* vec, void* b, void* c);  // 00a6e320
    void      FUN_00a6e3e0(VecBase* vec, void* b);           // 00a6e3e0
    void*     FUN_00a6e4b0();                                // 00a6e4b0
};

// ---------------------------------------------------------------------------
// globals
float* gpRootMap;   // 0x154df28 (the manager's root decal table)

// ===========================================================================
// @ 0x00a6dfc0
void cEffectsManager::FUN_00a6dfc0(void* vec)
{
    cEffectsManager* ebx = this;
    UIntVec* ebp = (UIntVec*)vec;
    ebp->reserve((unsigned)ebx->mnElementCount);

    unsigned** edi = (unsigned**)ebx->mpBuckets;
    unsigned* esi = *edi;
    if (esi == 0) {
        ++edi;
        if (*edi == 0) {
            do { ++edi; } while (*edi == 0);
        }
        esi = *edi;
    }
    unsigned* end = *(unsigned**)((char*)ebx->mpBuckets + ebx->mnBucketCount * 4);
    while (esi != end) {
        unsigned* dst = ebp->mpEnd;
        if (dst < ebp->mpCapacity) {
            ebp->mpEnd = dst + 1;
            if (dst != 0)
                *dst = *esi;
        }
        else {
            ebp->DoInsertValue(dst, esi);
        }
        esi = (unsigned*)esi[2];
        while (esi == 0) {
            esi = (unsigned*)edi[1];
            ++edi;
        }
    }
}

// ===========================================================================
// @ 0x00a6e050
bool cEffectsManager::FUN_00a6e050(void* p)
{
    cEffectsManager* ebp = this;
    ICollection* ebx = (ICollection*)p;
    ICollection** piVar5 = (ICollection**)((char*)ebp + 0x2c);

    int n = (*(int*)((char*)ebp + 0x30) - *(int*)((char*)ebp + 0x2c)) >> 2;
    int i = 0;
    if (0 < n) {
        ICollection** piVar4 = (ICollection**)*piVar5;
        do {
            if (*piVar4 == ebx)
                return true;
            ++i;
            ++piVar4;
        } while (i < n);
    }

    n = (*(int*)((char*)ebp + 0x30) - (int)*piVar5) >> 2;
    i = 0;
    if (0 < n) {
        ICollection** base = (ICollection**)*piVar5;
        ICollection** piVar4 = base;
        do {
            if (*piVar4 == 0) {
                ICollection* old = base[i];
                if (ebx != old) {
                    if (ebx != 0)
                        ebx->AddRef();
                    base[i] = ebx;
                    if (old != 0)
                        old->Release();
                }
                goto tail;
            }
            ++i;
            ++piVar4;
        } while (i < n);
    }

    if (ebx != 0)
        ebx->AddRef();
    {
        ICollection** puVar1 = (ICollection**)((char*)ebp + 0x30);
        if (puVar1 < (ICollection**)((char*)ebp + 0x34)) {
            *(ICollection***)((char*)ebp + 0x30) = puVar1 + 1;
            if (puVar1 != 0) {
                *puVar1 = ebx;
                if (ebx != 0)
                    ebx->AddRef();
            }
        }
        else {
            v00a0a360(puVar1, &ebx, 0);
        }
    }
    if (ebx != 0)
        ebx->Release();

tail:
    v00a69310(ebp);
    {
        ICollection** bk = (ICollection**)(*(int*)((char*)ebp + 0x228));
        ICollection* node = (ICollection*)*bk;
        if (node == 0) {
            ++bk;
            node = (ICollection*)*bk;
            while (node == 0) {
                ++bk;
                node = (ICollection*)*bk;
            }
        }
        ICollection* end = *(ICollection**)(*(int*)((char*)ebp + 0x228) + *(int*)((char*)ebp + 0x22c) * 4);
        while (node != end) {
            v00a72060(*(void**)((char*)node + 4), -1);
            node = *(ICollection**)((char*)node + 8);
            while (node == 0) {
                node = *(ICollection**)((char*)bk + 4);
                ++bk;
            }
        }
    }
    return true;
}

// ===========================================================================
// @ 0x00a6e1a0
void* cEffectsManager_ctor(void* self)
{
    char* esi = (char*)self;
    int ebx = 0;
    *(int*)(esi + 4) = 0x13ef094;                 // ??_7GmeRefCount@@6B@
    *(int*)(esi + 8) = ebx;
    v0093a560(esi + 0x10, 4, false);              // Stopwatch
    *(int*)(esi + 0x00) = 0x1455b80;
    *(int*)(esi + 4) = 0x1455b7c;
    *(char*)(esi + 0x0c) = (char)ebx;
    *(int*)(esi + 0x2c) = ebx;
    *(int*)(esi + 0x30) = ebx;
    *(int*)(esi + 0x34) = ebx;
    *(int*)(esi + 0x40) = ebx;
    *(int*)(esi + 0x44) = ebx;
    *(int*)(esi + 0x48) = ebx;
    *(int*)(esi + 0x4c) = ebx;
    *(float*)(esi + 0x50) = 0.0f;
    *(int*)(esi + 0x54) = ebx;
    *(float*)(esi + 0x58) = kOne;
    *(float*)(esi + 0x5c) = kPoint9;
    *(float*)(esi + 0x60) = 0.0f;
    *(float*)(esi + 0x64) = kOne;
    *(int*)(esi + 0x68) = ebx;
    *(int*)(esi + 0x6c) = ebx;
    *(int*)(esi + 0x70) = ebx;
    v0011e073e(esi + 0x74, ebx, 0x4c);
    void* edi = (void*)gEmptyString16;
    *(void**)(esi + 0xc0) = edi;
    *(void**)(esi + 0xc4) = edi;
    *(int*)(esi + 0xc8) = 0x1667bad;
    v00a6cdb0(esi + 0xd0);
    *(int*)(esi + 0x1f0) = ebx;
    *(int*)(esi + 0x1f4) = 0;
    *(int*)(esi + 0x1f8) = 0;
    *(int*)(esi + 0x1fc) = 0;
    *(int*)(esi + 0x200) = 0;
    *(int*)(esi + 0x204) = 0;
    *(int*)(esi + 0x208) = 0;
    *(int*)(esi + 0x20c) = 0;
    *(int*)(esi + 0x210) = 0;
    *(int*)(esi + 0x214) = 0;
    *(int*)(esi + 0x218) = 0;
    *(int*)(esi + 0x21c) = 0;
    *(int*)(esi + 0x220) = 0;
    *(float*)(esi + 0x234) = kOne;
    *(float*)(esi + 0x238) = kTwo;
    *(int*)(esi + 0x230) = ebx;
    *(int*)(esi + 0x23c) = ebx;
    *(int*)(esi + 0x22c) = 1;
    *(int*)(esi + 0x228) = 0x154df28;
    *(int*)(esi + 0x244) = ebx;
    *(void**)(esi + 0x248) = edi;
    *(void**)(esi + 0x24c) = edi;
    *(int*)(esi + 0x250) = 0x1667bad;
    return esi;
}

// ===========================================================================
// @ 0x00a6e320
void cEffectsManager::FUN_00a6e320(VecBase* vec, void* b, void* c)
{
    char* ebp = (char*)this;
    char* ebx = vec->mpBegin;
    char* esi = vec->mpEnd;
    char* r = vec->Append(esi, ebx);
    vec->FixTail(r);
    int d = (int)(esi - ebx);
    vec->mpEnd += ((d / 12) * 0x24);
    char* bk = *(char**)(ebp + 0x228);
    char* node = *(char**)bk;
    if (node == 0) {
        bk += 4;
        if (*(char**)bk == 0) {
            do { bk += 4; } while (*(char**)bk == 0);
        }
        node = *(char**)bk;
    }
    char* end = *(char**)(*(int*)(ebp + 0x228) + *(int*)(ebp + 0x22c) * 4);
    while (node != end) {
        char* coll = *(char**)(node + 4);
        (*(void(__thiscall**)(void*, void*, void*, void*))(*((char**)*(char**)coll) + 0x44))(coll, (void*)vec, b, c);
        node = *(char**)(node + 8);
        while (node == 0) {
            char* t = *(char**)(bk + 4);
            bk += 4;
            node = t;
        }
    }
}

// ===========================================================================
// @ 0x00a6e3e0
void cEffectsManager::FUN_00a6e3e0(VecBase* vec, void* b)
{
    char* ebx = (char*)this;
    char* ebp = vec->mpBegin;
    char* esi = vec->mpEnd;
    char* r = vec->Append(esi, ebp);
    vec->FixTail(r);
    int d = (int)(esi - ebp);
    vec->mpEnd += (d / 12) * 0x24;
    int n = (*(int*)(ebx + 0x30) - *(int*)(ebx + 0x2c)) >> 2;
    for (int i = 0; i < n; ++i) {
        char* c = *(char**)(*(int*)(ebx + 0x2c) + i * 4);
        if (c != 0)
            (*(void(__thiscall**)(void*, void*, void*))(*((char**)*(char**)c) + 0x40))(c, (void*)vec, b);
    }
}

// ===========================================================================
// @ 0x00a6e4b0
void* cEffectsManager::FUN_00a6e4b0()
{
    char* esi = (char*)this;
    *(int*)(esi + 0) = 0x40;
    int zc = 0;
    int zb = 0;
    *(int*)(esi + 4) = zb;
    *(short*)(esi + 0x0a) = (short)zc;
    int za = 0;
    *(short*)(esi + 0x08) = (short)za;
    *(float*)(esi + 0x0c) = gFloatA;
    *(float*)(esi + 0x10) = gFloatB;
    *(float*)(esi + 0x14) = gFloatC;
    *(float*)(esi + 0x18) = kOne;
    ((Matrix3*)(esi + 0x1c))->Assign(gMatIdent);
    float one = kOne;
    *(char*)(esi + 0x40) = (char)zb;
    *(char*)(esi + 0x41) = (char)zb;
    *(int*)(esi + 0x44) = zb;
    *(int*)(esi + 0x48) = zb;
    *(int*)(esi + 0x4c) = zb;
    int za2 = 0;
    int zd = 0;
    *(short*)(esi + 0x7a) = (short)za2;
    *(int*)(esi + 0x70) = zb;
    *(int*)(esi + 0x74) = zb;
    *(float*)(esi + 0x58) = one;
    *(float*)(esi + 0x5c) = one;
    *(float*)(esi + 0x60) = one;
    *(float*)(esi + 0x64) = one;
    *(float*)(esi + 0x68) = one;
    *(float*)(esi + 0x6c) = one;
    *(short*)(esi + 0x78) = (short)zd;
    *(float*)(esi + 0x7c) = one;
    *(int*)(esi + 0x80) = -1;
    return esi;
}

// ===========================================================================
// @ 0x00a6e600
long long cEffectsParser::EffectsMapID(const char* s)
{
    const char* p = s;
    const char* q = p + 1;
    do { } while (*p++ != 0);
    char* esi = (char*)this + 0x3c4;
    ((EString*)esi)->assign(s, s + (int)(p - q));
    MakeCaseInsensitive(esi);
    if (strcmp(kTerrain, s) == 0)
        return 0;
    if (strcmp(kWater, s) == 0)
        return 1;
    void* coll = *(void**)((char*)this + 0x8c);
    if (coll != 0) {
        long long v = (*(long long(__thiscall**)(void*, const char*))(*((char**)coll) + 0x1c))(coll, s);
        if (v != -1)
            return v;
    }
    return -1;
}

// ===========================================================================
// @ 0x00a6e6e0
void FUN_00a6e6e0(void* self, void* out, int* key)
{
    char* ebx = (char*)self;
    char* puVar8 = ebx + 4;
    char bVar9 = 1;
    if (*(void**)(ebx + 0xc) != 0) {
        int iVar1 = *key;
        int iVar6 = key[1] - iVar1;
        int local_4 = iVar6;
        char* puVar4 = *(char**)(ebx + 0xc);
        for (;;) {
            puVar8 = puVar4;
            int iVar7 = *(int*)(puVar8 + 0x14) - *(int*)(puVar8 + 0x10);
            int local_8 = iVar7;
            int* piVar5 = &local_8;
            if (iVar6 <= iVar7)
                piVar5 = &local_4;
            int cmp = v005f7870r((void*)iVar1, *(void**)(puVar8 + 0x10), *piVar5);
            if (cmp == 0) {
                if (iVar6 < iVar7)
                    cmp = -1;
                else
                    cmp = (iVar7 < iVar6);
            }
            bVar9 = cmp < 0;
            puVar4 = bVar9 ? *(char**)(puVar8 + 4) : *(char**)puVar8;
            if (puVar4 == 0)
                break;
        }
    }
    char* puVar4 = puVar8;
    if (bVar9) {
        if (puVar8 == *(char**)(ebx + 8))
            goto do_insert;
        puVar4 = (char*)v009215c0(puVar8);
    }
    if (v00812210(puVar4 + 0x10, key)) {
    do_insert:
        v00a6e570(&key, puVar8, key, 0);
        *(int*)out = (int)key;
        *((char*)out + 4) = 1;
        return;
    }
    *(int*)out = (int)puVar4;
    *((char*)out + 4) = 0;
}

// ===========================================================================
// @ 0x00a6e7e0
void FUN_00a6e7e0(void* self, char* dst, unsigned count, void* val)
{
    char* esiSelf = (char*)self;
    char* pBegin = *(char**)esiSelf;
    char* pEnd = *(char**)(esiSelf + 4);
    unsigned capacity = (unsigned)((*(char**)(esiSelf + 8) - pEnd) / 0xc);
    if (capacity >= count) {
        if (count == 0)
            return;
        int local_c = *(int*)val;
        char* oldEnd = pEnd;
        int local_8 = ((int*)val)[1];
        int local_4 = ((int*)val)[2];
        unsigned have = (unsigned)((pEnd - dst) / 0xc);
        if (count < have) {
            unsigned n = count * 0xc;
            char* src = oldEnd - count * 0xc;
            v00898b80(&val, src, oldEnd, oldEnd, dst);
            v00abced0(dst, src, oldEnd);
            *(int*)(esiSelf + 4) += n;
            v00a177f0(dst, dst + n, &local_c);
            return;
        }
        unsigned extra = count - have;
        v006e5760(oldEnd, extra, &local_c);
        *(int*)(esiSelf + 4) += extra * 0xc;
        v00898b80(&dst, dst, oldEnd, *(void**)(esiSelf + 4), dst);
        *(int*)(esiSelf + 4) += have * 0xc;
        v00a177f0(dst, oldEnd, &local_c);
        return;
    }
    unsigned oldCount = (unsigned)((pEnd - pBegin) / 0xc);
    unsigned cap2 = oldCount * 2;
    if (oldCount == 0)
        cap2 = 1;
    unsigned need = oldCount + count;
    if (need > cap2)
        cap2 = need;
    void* newBuf;
    if (cap2 == 0)
        newBuf = 0;
    else
        newBuf = EAAllocate(cap2 * 0xc, kEaStlName, 0, 0, kEaAllocFile, 0xd1);
    char* mid = (char*)v00a11310(pBegin, dst, newBuf);
    v006e5760(mid, count, val);
    char* fin = (char*)v00a11310(dst, pEnd, mid + count * 0xc);
    if (pBegin != 0 && *(int*)(pBegin - 4) != 0)
        operator_delete__(pBegin);
    *(char**)esiSelf = (char*)newBuf;
    *(char**)(esiSelf + 4) = fin;
    *(char**)(esiSelf + 8) = (char*)newBuf + cap2 * 0xc;
}

// ===========================================================================
// @ 0x00a6eaf0
long long cEffectsParser::MapFindA(const char* s)
{
    void* self = this;
    char* edi = (char*)self;
    char* p = (char*)s;
    char* q = p + 1;
    do { } while (*p++ != 0);
    int len = (int)(p - q);
    char* esi = edi + 0x3c4;
    ((EString*)esi)->assign(s, s + len);
    MakeCaseInsensitive(esi);
    void* local_8[2];
    char* tbl = edi + 0x24;
    v007e2ea0(local_8, tbl);
    int ecx = *(int*)(tbl + 8);
    int edx = *(int*)(tbl + 4);
    long long r = *(int*)((char*)local_8[0] + 0x10);
    if ((int)local_8[0] == *(int*)(edx + ecx * 4))
        r = -1;
    return r;
}

// ===========================================================================
// @ 0x00a6eb60
long long cEffectsParser::MapFindB(const char* s, int idx)
{
    void* self = this;
    char* edi = (char*)self;
    char* esi = edi + 0x3c4;
    const char* p = s;
    do { } while (*p++ != 0);
    ((EString*)esi)->assign(s, p - 1);
    MakeCaseInsensitive(esi);
    char* tbl = *(char**)(edi + 0x44) + idx * 0x20;
    void* local_8[2];
    v007e2ea0(local_8, tbl);
    int ecx = *(int*)(tbl + 8);
    int edx = *(int*)(tbl + 4);
    if ((int)local_8[0] == *(int*)(edx + ecx * 4))
        return -1;
    return *(int*)((char*)local_8[0] + 0x10);
}

// ===========================================================================
// @ 0x00a6ebd0
long long cEffectsParser::MapFindC(const char* s, int idx)
{
    void* self = this;
    char* edi = (char*)self;
    char* esi = edi + 0x3c4;
    const char* p = s;
    do { } while (*p++ != 0);
    ((EString*)esi)->assign(s, p - 1);
    MakeCaseInsensitive(esi);
    char* tbl = *(char**)(edi + 0x78) + idx * 0x20;
    void* local_8[2];
    v007e2ea0(local_8, tbl);
    int ecx = *(int*)(tbl + 8);
    int edx = *(int*)(tbl + 4);
    if ((int)local_8[0] == *(int*)(edx + ecx * 4))
        return -1;
    return *(int*)((char*)local_8[0] + 0x10);
}

// ===========================================================================
// @ 0x00a6ec40
long long cEffectsParser::LookupRes(int idx, const char* s)
{
    void* self = this;
    char* esi = (char*)self;
    char* edi = esi + 0x3c4;
    const char* p = s;
    do { } while (*p++ != 0);
    ((EString*)edi)->assign(s, p - 1);
    MakeCaseInsensitive(edi);
    if (idx < 0x13) {
        char* ep = (char*)(idx * 0x20 + esi + 0xb8);
        void* local_10[3];
        v00a6e9e0(local_10, ep);
        if ((int)local_10[0] != *(int*)(*(int*)(ep + 4) + *(int*)(ep + 8) * 4))
            return ((long long*)local_10[0])[2];
    }
    if (idx == 1) {
        int a = ((cEffectsParser*)esi)->MapFindC((char*)*(void**)edi, 1);
        if (a >= 0) {
            char* coll = *(char**)(esi + 0x20);
            char* r = (char*)(*(void*(__thiscall**)(char*, int, int))(*((char**)coll) + 0x28))(coll, a, 1);
            return *(long long*)(r + 8);
        }
    }
    void* save = *(void**)(esi + 0x8c);
    if (save != 0) {
        void* local_10[3];
        char c = (*(char(__thiscall**)(void*, int, const char*, void*))(*((char**)save) + 8))(save, idx, s, local_10);
        if (c)
            return *(long long*)local_10;
        if (((*(unsigned*)(esi + 0x10) >> 1) & 1) == 0) {
            void* it[2];
            v00b20930(it, edi);
            if ((int)it[0] == (int)(esi + 0x3d8 + idx * 0x1c))
                v00a6ea80(it, edi);
        }
    }
    return -1;
}

// ===========================================================================
// @ 0x00a6ed80
void cEffectsParser::ParseDrawInfoOptions(void* args, void* obj, DrawInfoTarget* t)
{
    void* self = this;
    char* ebp = (char*)self;
    char* edi = (char*)args;
    if (t->mType == 0x0f) {
        const char** oa = v00838330(args, kTextureOpt, 1);
        if (oa != 0) {
            char* name = (char*)oa[0];
            char* e = name;
            while (*e) ++e;
            ((EString*)(ebp + 0x3c4))->assign(name, e);
            MakeCaseInsensitive(ebp + 0x3c4);
            char* ep = ebp + 0xb8;
            void* local[3];
            {
                v00a6e9e0(local, ep);
            }
            if ((int)local[0] != *(int*)(*(int*)(ep + 4) + *(int*)(ep + 8) * 4)) {
                t->mResA = ((unsigned*)local[0])[4];
                t->mResB = ((unsigned*)local[0])[5];
                goto after_type;
            }
            {
                void* save = *(void**)(ebp + 0x8c);
                if (save != 0) {
                    char c = (*(char(__thiscall**)(void*, int, const char*, void*))(*((char**)save) + 8))(save, 0, name, local);
                    if (c) {
                        t->mResA = ((unsigned*)local)[0];
                        t->mResB = ((unsigned*)local)[1];
                        goto after_type;
                    }
                    if (((*(unsigned*)(ebp + 0x10) >> 1) & 1) == 0) {
                        void* it[2];
                        char* d = ebp + 0x3d4;
                        {
                            v00b20930(it, d);
                        }
                        if ((int)it[0] == (int)(ebp + 0x3d8)) {
                            v00a6ea80(it, d);
                        }
                    }
                }
                t->mResA = 0xffffffff;
                t->mResB = 0xffffffff;
            }
        }
    }
    else {
        int lc = 0;
        const char** oa = v00838130(args, kDrawOpt, &lc, 1, 2);
        (void)lc;
        if (oa != 0) {
            t->mType = (char)v00840bb0(oa[0], gDecalEnumTbl);
            if (lc > 1) {
                long long r = this->LookupRes(0, oa[1]);
                t->mResA = (unsigned)r;
                t->mResB = (unsigned)(r >> 32);
            }
        }
    }
after_type:
    {
        const char** oa = v00838330(args, kBufferOpt, 1);
        if (oa != 0) {
            unsigned char r = (*(unsigned char(__thiscall**)(void*, const char*))(*((char**)obj) + 0xa0))(obj, oa[0]);
            t->mBuffer = (char)r;
        }
    }
    {
        const char** oa = v00838330(args, kLayerOpt, 1);
        if (oa != 0) {
            short r = (*(short(__thiscall**)(void*, const char*))(*((char**)obj) + 0x9c))(obj, oa[0]);
            t->mLayer = r;
        }
    }
    {
        const char** oa = v00838330(args, kSortOffsetOpt, 1);
        if (oa != 0) {
            float r = (*(float(__thiscall**)(void*, const char*))(*((char**)obj) + 0x98))(obj, oa[0]);
            t->mSortOffset = r;
        }
    }
    if (v008380b0(edi, kLightFlag))
        t->mFlags |= 1;
    if (v008380b0(edi, kNoFogFlag))
        t->mFlags |= 2;
    if (v008380b0(edi, kShadowFlag))
        t->mFlags |= 8;
    if (v008380b0(edi, kNoShadowFlag))
        t->mFlags &= (char)0xf7;
    if (v008380b0(edi, kNoCullFlag))
        t->mFlags |= 0x10;
    if (v008380b0(edi, gFlagUser1))
        t->mFlags |= 0x20;
    if (v008380b0(edi, gFlagUser2))
        t->mFlags |= 0x40;
    if (v008380b0(edi, gFlagUser3))
        t->mFlags |= 0x80;
}

// ===========================================================================
// @ 0x00a6f090
int cEffectsParser::GetInheritedA(int a, int depth, void* c)
{
    if (depth < 3)
        goto zero;
    {
        int idx = MapFindB(*(const char**)(a + 8), (int)c);
        if (idx < 0)
            goto zero;
        {
            char* coll = *(char**)((char*)this + 0x20);
            return (*(int(__thiscall**)(char*, int, void*))(*((char**)coll) + 0x20))(coll, idx, c);
        }
    }
zero:
    return 0;
}

// @ 0x00a6f0d0
int cEffectsParser::GetInheritedB(int a, int depth, void* c)
{
    if (depth < 3)
        goto zero;
    {
        int idx = MapFindC(*(const char**)(a + 8), (int)c);
        if (idx < 0)
            goto zero;
        {
            char* coll = *(char**)((char*)this + 0x20);
            return (*(int(__thiscall**)(char*, int, void*))(*((char**)coll) + 0x28))(coll, idx, c);
        }
    }
zero:
    return 0;
}

}}  // namespace EA::Swarm
