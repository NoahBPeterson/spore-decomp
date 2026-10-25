// src/game/SPGonzago/SPSolarSystem.cpp -- migrated from slice(s) s01351ae0, s00c84120, s00423960, s00423110 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSolarSystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include <stdarg.h>

// ---- items of slice s00423110 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Elem38 {
    int data[14];
    void Assign(const Elem38* other);   // 0x00537dc0
};
inline Elem38* CopyElems(Elem38* first, Elem38* last, Elem38* result)
{
    const bool b0 = false;
    const bool b1 = false;
    const bool b2 = false;
    for (; first != last; ++first, ++result)
        result->Assign(first);
    return result;
}
struct Elem38Vector {
    Elem38* mpBegin;
    Elem38* mpEnd;
    Elem38* erase(Elem38* first, Elem38* last);   // 0x004238c0
};
// ---- items of slice s00423110 end

// ---- items of slice s00423960 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, uint32_t);
#pragma intrinsic(memcpy)
#pragma intrinsic(_InterlockedIncrement)
struct Allocator { const char* mpName; };
void* __cdecl AllocatorAllocate(Allocator* alloc, uint32_t size, uint32_t align, uint32_t offset);  // FUN_0042dee0
void  __cdecl AllocatorDeallocate(void* block);                                                    // EASTL_allocator_deallocate
struct Counted { char pad[0x40]; int mnRefCount; void Release(); };  // count at +0x40, plain; Release = FUN_0040f360
typedef Counted* CountedPtr;
struct ByteBuffer
{
    char* mBegin;
    char* mEnd;
    char* mCapacity;
    Allocator mAllocator;

    ByteBuffer(uint32_t n, const Allocator* /*alloc*/);
};
CountedPtr* __cdecl CopyBackwardCounted(CountedPtr* first, CountedPtr* last, CountedPtr* destEnd);  // FUN_0042e6e0
struct CountedPtrVector
{
    CountedPtr* mBegin;
    CountedPtr* mEnd;
    CountedPtr* mCapacity;
    Allocator mAllocator;

    void DoInsertValue(CountedPtr* pos, CountedPtr* value);
};
struct Record56
{
    uint32_t data[14];
    Record56* CopyConstruct(const Record56* src);   // FUN_0040ce80
    void Assign(const Record56* src);               // FUN_00537dc0
};
Record56* __cdecl   UninitializedCopyRecords(Record56* first, Record56* last, Record56* dest);  // FUN_00429ce0
struct Record56Vector
{
    Record56* mBegin;
    Record56* mEnd;
    Record56* mCapacity;
    Allocator mAllocator;

    void DoInsertValue(Record56* pos, const Record56* value);
};
// ---- items of slice s00423960 end

// ---- items of slice s00c84120 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace Simulator {
struct cPtrVector {
    void* mpBegin;                                           // +0x00
    void* mpEnd;                                             // +0x04
    void* mpCapacity;                                        // +0x08
};
}
namespace Simulator {
struct cSolarSystem {
    void*       mpVtable0;                                   // +0x00
    uint32_t    mRefCount;                                   // +0x04
    void*       mpVtable1;                                   // +0x08
    void*       mpOwnerStar;                                 // +0x0c
    cPtrVector  mPlanets;                                    // +0x10
    uint32_t    mPad1c;                                      // +0x1c
    uint32_t    mPad20;                                      // +0x20
    cPtrVector  mCelestialBodies;                            // +0x24
    uint32_t    mPad30;                                      // +0x30
    uint32_t    mPad34;                                      // +0x34
    cPtrVector  mModels;                                     // +0x38
    void*       mpStar1;                                     // +0x44
    void*       mpStar2;                                     // +0x48

    cSolarSystem();
};
}
// ---- items of slice s00c84120 end

// ---- items of slice s01351ae0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
struct PropDesc {
    const char* mName;   // +0x00
    u32 mHash;   // +0x04
    u32 mType;   // +0x08
    u32 mPad0C;   // +0x0c
    u32 mPad10;   // +0x10
    u32 mPad14;   // +0x14
    u32 mZero18;   // +0x18
    u32 mZero1C;   // +0x1c
    void* mDefault;   // +0x20
    void* mFn24;   // +0x24
    void* mFn28;   // +0x28
    void* mFn2C;   // +0x2c
    void* mFn30;   // +0x30
    void* mFn34;   // +0x34
    void* mFn38;   // +0x38
};
// ---- items of slice s01351ae0 end

// @ 0x004238c0
Elem38* Elem38Vector::erase(Elem38* first, Elem38* last)
{
    Elem38* position = CopyElems(last, mpEnd, first);
    for (Elem38* p = position; p < mpEnd; ++p) {
    }
    mpEnd -= (last - first);
    return first;
}

// @ 0x00423960
void Record56Vector::DoInsertValue(Record56* pos, const Record56* value)
{
    if (mEnd != mCapacity)
    {
        const Record56* v = value;
        if (v >= pos && v < mEnd)
            ++v;

        Record56* slot = mEnd;
        if (slot)
            slot->CopyConstruct(mEnd - 1);

        Record56* dst = mEnd;
        Record56* src = mEnd - 1;
        while (src != pos)
        {
            --src;
            --dst;
            dst->Assign(src);
        }
        pos->Assign(v);
        ++mEnd;
    }
    else
    {
        int count = (int)(mEnd - mBegin);
        uint32_t newCount = count ? count * 2 : 1;
        Record56* newBuf = newCount ? (Record56*)AllocatorAllocate(&mAllocator, newCount * sizeof(Record56), 4, 0) : 0;

        Record56* ins = UninitializedCopyRecords(mBegin, pos, newBuf);
        if (ins)
            ins->CopyConstruct(value);
        ins = ins + 1;
        Record56* newEnd = UninitializedCopyRecords(pos, mEnd, ins);

        int oldCapacity = (int)(mCapacity - mBegin);
        (void)oldCapacity;
        if (mBegin && ((uint32_t*)mBegin)[-1])
            AllocatorDeallocate(mBegin);
        mBegin = newBuf;
        mEnd = newEnd;
        mCapacity = newBuf + newCount;
    }
}

// @ 0x00423be0
ByteBuffer::ByteBuffer(uint32_t n, const Allocator*)
{
    mBegin = n ? (char*)AllocatorAllocate(&mAllocator, n, 1, 0) : 0;
    mEnd = mBegin;
    mCapacity = mBegin + n;
}

// @ 0x00423c40
void CountedPtrVector::DoInsertValue(CountedPtr* pos, CountedPtr* value)
{
    if (mEnd != mCapacity)
    {
        CountedPtr* v = value;
        if (v >= pos && v < mEnd)
            ++v;

        CountedPtr* slot = mEnd;
        if (slot)
        {
            *slot = mEnd[-1];
            if (*slot) ++(*slot)->mnRefCount;
        }

        CopyBackwardCounted(pos, mEnd - 1, mEnd);

        CountedPtr incoming = *v;
        if (incoming != *pos)
        {
            CountedPtr old = *pos;
            if (incoming) ++incoming->mnRefCount;
            *pos = incoming;
            if (old) old->Release();
        }
        ++mEnd;
    }
    else
    {
        int count = (int)(mEnd - mBegin);
        uint32_t newCount = count ? count * 2 : 1;
        CountedPtr* newBuf = newCount ? (CountedPtr*)AllocatorAllocate(&mAllocator, newCount * 4, 4, 0) : 0;

        CountedPtr* head = (CountedPtr*)memcpy(newBuf, mBegin, (char*)pos - (char*)mBegin);
        CountedPtr* ins = head + (pos - mBegin);
        if (ins)
        {
            *ins = *value;
            if (*ins) ++(*ins)->mnRefCount;
        }
        CountedPtr* tail = (CountedPtr*)memcpy(ins + 1, pos, (char*)mEnd - (char*)pos);
        CountedPtr* newEnd = tail + (mEnd - pos);

        if (mBegin && ((uint32_t*)mBegin)[-1])
            AllocatorDeallocate(mBegin);
        mBegin = newBuf;
        mEnd = newEnd;
        mCapacity = newBuf + newCount;
    }
}

// @ 0x00c84b50
namespace Simulator {
cSolarSystem::cSolarSystem()
{
    mRefCount = 0;
    mpVtable1 = (void*)0x01444434;
    mpVtable0 = (void*)0x0147349c;
    mpVtable1 = (void*)0x01473478;
    mpOwnerStar = 0;
    mPlanets.mpBegin = 0;
    mPlanets.mpEnd = 0;
    mPlanets.mpCapacity = 0;
    mCelestialBodies.mpBegin = 0;
    mCelestialBodies.mpEnd = 0;
    mCelestialBodies.mpCapacity = 0;
    mModels.mpBegin = 0;
    mModels.mpEnd = 0;
    mModels.mpCapacity = 0;
    mpStar1 = 0;
    mpStar2 = 0;
}
}  // namespace Simulator

// @ 0x013526b0
void FUN_013526b0(void)
{
    PropDesc d;
    d.mName = (const char*)0x147351c;
    d.mHash = 0x38cfa88;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc86560;
    d.mFn28 = (void*)0xc43790;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)0xb6f860;
    d.mFn38 = (void*)0xc6c390;
    d.mType = 0x10;
    *(PropDesc*)0x1579d78 = d;

    d.mName = (const char*)0x1473508;
    d.mHash = 0x38cfad9;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc85460;
    d.mFn28 = (void*)0xaca730;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)0xb6f860;
    d.mFn38 = (void*)0xc6c390;
    d.mType = 0x24;
    *(PropDesc*)0x1579db4 = d;

    d.mName = (const char*)0x1473500;
    d.mHash = 0x38cfae4;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc843f0;
    d.mFn28 = (void*)0xbca960;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)0xb6f550;
    d.mFn38 = (void*)0xac8050;
    d.mType = 0x38;
    *(PropDesc*)0x1579df0 = d;

    d.mName = (const char*)0x14734f8;
    d.mHash = 0x38cfafe;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc843f0;
    d.mFn28 = (void*)0xbca960;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)0xb6f550;
    d.mFn38 = (void*)0xac8050;
    d.mType = 0x3c;
    *(PropDesc*)0x1579e2c = d;
}
