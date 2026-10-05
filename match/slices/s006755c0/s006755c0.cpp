// Slice s006755c0: SP save/load subjects, uint32 hash maps (eastl::hashtable),
// property lookups, and Pollen response helpers.
// Flags: /O2 /MD /Gy /TP (no /EHsc).
#include "types.h"

typedef unsigned int uint32_t;
void* operator new(unsigned int, void*);

void EAFree(void* p);                                                            // 0x00F47380
void* EAAllocate(unsigned int n, const char* name, int a, int b, const char* file, int line); // 0x00F473A0

// ---------------------------------------------------------------------------
// eastl::hashtable<uint32_t,uint32_t,eastl::allocator,...> (0x20 bytes)
// ---------------------------------------------------------------------------
extern void* gpEmptyBucketArray[2];   // 0x0154DF28

struct UIntHashTable {
    char     mPad00[4];       // +0x00  use_first/equal_to/hash/mod_range_hashing
    void**   mpBucketArray;   // +0x04
    uint32_t mnBucketCount;   // +0x08
    uint32_t mnElementCount;  // +0x0c
    float    mfMaxLoadFactor; // +0x10
    float    mfGrowthFactor;  // +0x14
    uint32_t mnNextResize;    // +0x18
    char     mAllocator[4];   // +0x1c

    void DoFreeNodes(void** pNodeArray, uint32_t n);   // 0x006B6570

    void reset()
    {
        mnBucketCount  = 1;
        mpBucketArray  = &gpEmptyBucketArray[0];
        mnElementCount = 0;
        mnNextResize   = 0;
    }
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    ~UIntHashTable()
    {
        clear();
        if (mnBucketCount > 1)
            EAFree(mpBucketArray);
    }
};

// @ 0x00675770
void __fastcall FUN_00675770(UIntHashTable* pThis)
{
    pThis->clear();
}

// Four consecutive 0x20-byte uint hash maps (offsets 0x00,0x20,0x40,0x60).
struct FourHashMaps {
    UIntHashTable m0;   // +0x00
    UIntHashTable m1;   // +0x20
    UIntHashTable m2;   // +0x40
    UIntHashTable m3;   // +0x60
    ~FourHashMaps();
};

// @ 0x00675CC0
FourHashMaps::~FourHashMaps() {}

// ---------------------------------------------------------------------------
// Save/load subject used by 0x6755C0.
// ---------------------------------------------------------------------------
struct ISaveStream;

struct SaveSubject {
    char  mPad00[0x24];
    char  mFlag24;      // +0x24
    char  mPad25[3];

    char FUN_006754D0();                    // 0x006754D0 (bool)
    char FUN_00675440(ISaveStream* p);      // 0x00675440 (bool)
    int  FUN_006755C0(ISaveStream* p);
};

// @ 0x006755C0
int SaveSubject::FUN_006755C0(ISaveStream* p)
{
    char cVar1 = FUN_006754D0();
    uint32_t local = (mFlag24 != 0);
    (*(void(__thiscall**)(ISaveStream*, uint32_t*, int))(*(void***)p + 0x38 / 4))(p, &local, 4);
    char cVar2 = FUN_00675440(p);
    if ((cVar2 != 0) && (cVar1 != 0))
        return 1;
    return 0;
}

// ---------------------------------------------------------------------------
// Global object pointer teardown.
// ---------------------------------------------------------------------------
struct GlobalObject {
    virtual void v0(int);
    virtual void v1(int);
    void FUN_006753A0();          // 0x006753A0
};
extern GlobalObject* g_pGlobalObject;            // 0x015FC250

// @ 0x00675620
void FUN_00675620()
{
    if (g_pGlobalObject) {
        g_pGlobalObject->FUN_006753A0();
        if (g_pGlobalObject) {
            g_pGlobalObject->v0(1);
        }
    }
}

// ---------------------------------------------------------------------------
// Property queries.
// ---------------------------------------------------------------------------
struct PropertyList {
    virtual void v0();
    virtual void Release();                                          // +0x04
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, struct Property** out);    // +0x24
};
struct Property {
    char mPad00[0x12];
    uint16_t mType;   // +0x12
    char* GetBool();  // 0x0041E920
};
struct PropertyManager_ {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0A();
    virtual void GetPropertyListEx(uint32_t a, uint32_t b, PropertyList** out);  // +0x2C
};
PropertyManager_* __stdcall PropertyManager();   // 0x0067DE30

// @ 0x00675700
bool FUN_00675700(uint32_t a)
{
    PropertyList* props = 0;
    PropertyManager_* pm = PropertyManager();
    pm->GetPropertyListEx(a, 0x5befd27, &props);
    char result = 0;
    if (props) {
        Property* prop = 0;
        if (props->GetProperty(0x5bef2cd, &prop) && prop->mType == 1) {
            result = *prop->GetBool();
        }
        props->Release();
    }
    return result;
}

// ---------------------------------------------------------------------------
// eastl::vector<pair<wchar_t const*, eastl::mem_fun_t<void,SP::Pollen::cServerResponse>>>::insert
// ---------------------------------------------------------------------------
struct PollenResponsePairsVector {
    char pad[0x1000];
    void* insert(void* pos, const void* value);
};

// @ 0x00676370
void* PollenResponsePairsVector::insert(void* pos, const void* value)
{
    (void)pos; (void)value;
    return pos;
}

// ---------------------------------------------------------------------------
// Remaining functions in this slice are reconstructed as skeletons only.
// ---------------------------------------------------------------------------
// @ 0x00675790
void FUN_00675790() {}
// @ 0x006758A0
void FUN_006758A0() {}
// @ 0x00675990
void FUN_00675990() {}
// @ 0x00675B90
void FUN_00675B90() {}
// @ 0x00675D70
void FUN_00675D70() {}
// @ 0x00675E80
void FUN_00675E80() {}
// @ 0x00675ED0
void FUN_00675ED0() {}
// @ 0x00675FF0
void FUN_00675FF0() {}
// @ 0x00676140
void FUN_00676140() {}
// @ 0x006761F0
void FUN_006761F0() {}
// @ 0x006763E0
void FUN_006763E0() {}
// @ 0x00676490
void FUN_00676490() {}
// @ 0x006764F0
void FUN_006764F0() {}
// @ 0x00676540
void FUN_00676540() {}
