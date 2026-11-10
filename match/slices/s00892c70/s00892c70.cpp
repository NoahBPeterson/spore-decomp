// Slice s00892c70: look one record up in the object's small hash map and, when the key is
// present, hand the record to a virtual on the owning object while its critical section is held.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// NO MATCH yet: see notes.txt for what the code shape has to do with the pair the lookup returns.
//
// The owner's layout is not known from a header yet; the offsets are the ones the function
// touches: a vtable at +0x00, the section at +0x28, counters at +0x104..+0x124 and the map
// (buckets at +0x04, bucket count at +0x08) at +0x150.  The vtable slot called is +0x34.
#include "game/types.h"

typedef int64_t int64;

// Kernel32 section calls through their IAT slots: dllimport keeps the retail
// `call dword ptr [IAT]` form and the callee-pop convention.
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);   // IAT 0x013cc2d8
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);   // IAT 0x013cc2dc

struct CriticalSection {
    uint32_t d[6];
};

// Chain node of the hash map: a 16-bit key, then the next node.
struct MapEntry {
    uint16_t mKey;
    uint16_t mPad;
    MapEntry* mpNext;
};

// The map proper, as far as the lookup needs it.
struct MapLookup {
    uint32_t m00;
    MapEntry** mpBuckets;                           // +0x04
    uint32_t mnBuckets;                             // +0x08
};

// What the lookup hands back: the entry (or the bucket end marker) and the bucket slot.
struct FindResult {
    MapEntry* mpEntry;
    MapEntry** mpSlot;
};

FindResult FindEntry(MapLookup* map, const uint16_t* key); // 0x00892970

// A flat three-dword sequence (begin, used count, data) at +0x12c.
struct FlatSection {
    uint32_t mBegin;                                // +0x00
    uint32_t mCount;                                // +0x04
    uint32_t* mpData;                               // +0x08
};

extern "C" int _ftol2_sse(double);

// The item handed to the virtual: only its address is used here.
struct LookupItem {
    uint32_t d[5];
};

// The virtual called inside the section, through its vtable slot.
struct LookupVirtuals {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void Start(LookupItem* item, CriticalSection* cs);      // +0x34
};

struct LookupOwner : LookupVirtuals {
    uint32_t pad04[(0x28 - 0x04) / 4];
    CriticalSection mSection;                       // +0x28
    uint32_t pad40[(0x104 - 0x40) / 4];
    float mField104;                                // +0x104
    void** mpField108;                              // +0x108
    void** mpField10C;                              // +0x10C
    float mField110;                                // +0x110
    uint32_t pad114[(0x120 - 0x114) / 4];
    MapEntry* mpEntry;                              // +0x120
    int mnFlags;                                    // +0x124
    uint32_t pad128[(0x12c - 0x128) / 4];
    FlatSection mVec;                               // +0x12c
    uint32_t pad138[(0x150 - 0x138) / 4];
    MapLookup mMap;                                 // +0x150

    bool Add(LookupItem* item);
};

// @ 0x00892c70
bool LookupOwner::Add(LookupItem* item)
{
    EnterCriticalSection(&mSection);

    FindResult found = FindEntry(&mMap, (const uint16_t*)item);
    if (found.mpEntry == mMap.mpBuckets[mMap.mnBuckets]) {
        LeaveCriticalSection(&mSection);
        return false;
    }
    Start(item, &mSection);

    // The vector's used count grows by one; a fixed-point copy of a float already covers it, so
    // the original keeps the two spills (fp control word, then the int64 result).
    mVec.mCount = _ftol2_sse((double)mField110);
    mpField10C = (void**)&mField104;
    mnFlags = 0x20;
    mpEntry = found.mpEntry;
    *(uint32_t*)&mField104 = _ftol2_sse((double)mField110 + 0.0f);
    mpField108 = (void**)&mField104;
    LeaveCriticalSection(&mSection);
    return true;
}
