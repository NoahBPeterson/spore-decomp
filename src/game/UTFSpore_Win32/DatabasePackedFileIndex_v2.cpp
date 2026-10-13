// src/game/UTFSpore_Win32/DatabasePackedFileIndex_v2.cpp -- migrated from slice(s) s006bfda0, s006bede0, s006bde30 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/DatabasePackedFileIndex_v2.obj (retail-only second family, tools/migrate/modmap_overrides.json).  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/PFIndexModifiable.h"
#include "EA/CompressionRefpack.h"
#include "EA/ResourceMan/DatabasePackedFile.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/ResourceMan/Key.h"
#include "EA/Thread/Mutex.h"
#include "EA/ResourceMan/PFHoleTable.h"
#include "EA/IO/FileStream.h"
#include "EA/IO/MemoryStream.h"
#include "EA/ResourceMan/PFRecordRead.h"
#include "EA/ResourceMan/PFRecordWrite.h"
#include <intrin.h>

// ---- items of slice s006bde30 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  uint32;
typedef unsigned char  uint8;
typedef unsigned long long uint64;
struct HT {
    char   pad00[0xc];
    uint32 mnElementCount;   // 0x0c
    char   pad10[0xc];
    void*  mAllocator;       // 0x1c
    char   pad20[8];

    void   DoFreeNodes(uint32* buckets, uint32 count);   // 0x6be640
    uint32* eraseNode(uint32* out, uint32 node, uint32* buckets); // 0x6be820
    void   lowerBound(uint32* out, uint32* key);          // 0x6be890
    void   rehash(uint32 newBucketCount);                 // 0x6be8d0
    void   heapSiftDown(int, int, int, int);              // 0x6be980
};
void   FUN_006be690(uint32* first, uint32* last);   // 0x6be690
void   FUN_006be6e0(uint32* first, uint32* last);   // 0x6be6e0
void* FUN_006be730(uint32** a, uint32** b, uint32** c); // 0x6be730
void   FUN_006be7c0(uint32* a, int first, int last, uint32 value); // 0x6be7c0
// ---- items of slice s006bde30 end

// ---- items of slice s006bede0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PFHoleTable {
    int   field_0;
    char  pad[0x24];
    int64_t FUN_006bfc50(uint32 a, uint32 b);       // 0x6bfc50
    void    FUN_006bff10(PFHoleTable* other);        // 0x6bff10
    bool    FUN_006bff90(uint32 a, uint32 b, int c, int d); // 0x6bff90
    void    FUN_006bef70(uint32 a, uint32 b);        // 0x6bef70
    void    FUN_006bfda0(uint32 a, uint32 b, uint32 c, uint32 d); // 0x6bfda0
    void    FUN_006bf5a0();                          // 0x6bf5a0
};
void FUN_006bf030(void* a, void* b);                 // 0x6bf030
void FUN_006bf140(void* a, void* b);                 // 0x6bf140
void FUN_006bf1e0(void* a);                          // 0x6bf1e0
void FUN_006bf240(void* a, void* b);                 // 0x6bf240
void FUN_006bf2c0(void* a, void* b, void* c);        // 0x6bf2c0
void FUN_006bf430(void* a);                          // 0x6bf430
void FUN_006bf5d0(void* a, void* b, void* c, void* d); // 0x6bf5d0
void* FUN_006bf7d0(void* a, void* b);                // 0x6bf7d0
void FUN_006bf8f0(void* a, void* b, void* c, void* d); // 0x6bf8f0
void* FUN_006bfc20(void* a, void* b, void* c);       // 0x6bfc20
// ---- items of slice s006bede0 end

// ---- items of slice s006bfda0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef int            intptr_t;
struct HoleRec { u32 startLo, startHi, sizeLo, sizeHi; };
struct HoleNode {
    HoleNode* parent;   // +0x00
    HoleNode* left;     // +0x04
    HoleNode* right;    // +0x08
    void*     color;    // +0x0c
    HoleRec   rec;      // +0x10
};
struct HoleTable {
    char data[0x20];
    void FUN_006bfda0(u32 startLo, u32 startHi, u32 sizeLo, u32 sizeHi); // 0x6bfda0
    bool FUN_006bff90(u32 a, u32 b, u32 c, u32 d);                       // 0x6bff90
    void FUN_006bff10(HoleTable* other);                                 // 0x6bff10
};
struct PFIndexModifiable {
    void* vtbl;                // +0x00
    char  pad04[0x28];
    void** mpBucketArray;      // +0x2c
    u32    mnBucketCount;      // +0x30
    bool func24h(HoleTable* holes, u32 a, u32 b, u32 c, u32 d);
};
// ---- items of slice s006bfda0 end

// @ 0x006be640
void HT::DoFreeNodes(uint32* buckets, uint32 count)
{
    for (uint32 i = 0; i < count; ++i) {
        uint32 node = buckets[i];
        while (node != 0) {
            uint32 cur = node;
            node = *(uint32*)(node + 0x28);
            ((void(__thiscall*)(void*, uint32, int))(*(void***)mAllocator)[0xc / 4])
                (mAllocator, cur, 0x30);
        }
        buckets[i] = 0;
    }
}



// @ 0x006be690
void FUN_006be690(uint32* first, uint32* last)
{
    uint32* p = first;
    if (p != last) {
        for (++p; p != last; ++p) {
            uint32 v = *p;
            uint32* q = p;
            while (q != first) {
                uint32 prev = q[-1];
                if (*(uint32*)(prev + 0x14) < *(uint32*)(v + 0x14) ||
                    (*(uint32*)(prev + 0x14) <= *(uint32*)(v + 0x14) &&
                     *(uint32*)(prev + 0x10) <= *(uint32*)(v + 0x10)))
                    break;
                *q = prev;
                --q;
            }
            *q = v;
        }
    }
}



// @ 0x006be6e0
void FUN_006be6e0(uint32* first, uint32* last)
{
    for (; first != last; ++first) {
        uint32 v = *first;
        uint32* q = first;
        while (q != first) {
            uint32 prev = q[-1];
            if (*(uint32*)(prev + 0x14) < *(uint32*)(v + 0x14) ||
                (*(uint32*)(prev + 0x14) <= *(uint32*)(v + 0x14) &&
                 *(uint32*)(prev + 0x10) <= *(uint32*)(v + 0x10)))
                break;
            --q;
        }
        *q = v;
    }
}



// @ 0x006be730
void* FUN_006be730(uint32** a, uint32** b, uint32** c)
{
    uint32 u1 = *(uint32*)((char*)*a + 0x10), v1 = *(uint32*)((char*)*a + 0x14);
    uint32 u2 = *(uint32*)((char*)*b + 0x10), v2 = *(uint32*)((char*)*b + 0x14);
    uint32 u3, v3;
    if (!(v2 < v1) && !(v2 <= v1 && u2 <= u1)) {
        u3 = *(uint32*)((char*)*c + 0x10);
        v3 = *(uint32*)((char*)*c + 0x14);
        if (v2 <= v3 && (v2 < v3 || u2 < u3))
            return b;
        if (v1 <= v3 && (v1 < v3 || u1 < u3))
            return c;
        return a;
    }
    u3 = *(uint32*)((char*)*c + 0x10);
    v3 = *(uint32*)((char*)*c + 0x14);
    if (v3 < v1 || (v3 <= v1 && u3 <= u1)) {
        if (v2 <= v3) {
            if (v2 < v3)
                return c;
            if (u2 < u3)
                return c;
        }
        return b;
    }
    return a;
}



// @ 0x006be7c0
void FUN_006be7c0(uint32* a, int first, int last, uint32 value)
{
    if (last <= first) {
        a[last] = value;
        return;
    }
    for (;;) {
        int parent = (last - 1) >> 1;
        uint32 pv = a[parent];
        if (*(uint32*)(value + 0x14) < *(uint32*)(pv + 0x14))
            break;
        if (*(uint32*)(value + 0x14) <= *(uint32*)(pv + 0x14) &&
            *(uint32*)(value + 0x10) <= *(uint32*)(pv + 0x10))
            break;
        a[last] = pv;
        last = parent;
        if (parent <= first)
            break;
    }
    a[last] = value;
}



// @ 0x006be820
uint32* HT::eraseNode(uint32* out, uint32 node, uint32* buckets)
{
    // TODO(partial).
    return out;
}



// @ 0x006be890
void HT::lowerBound(uint32* out, uint32* key)
{
    // TODO(partial).
    *out = 0;
}



// @ 0x006be8d0
void HT::rehash(uint32 newBucketCount)
{
    // TODO(partial).
}



// @ 0x006be980
void HT::heapSiftDown(int, int, int, int)
{
    // TODO(partial).
}



// @ 0x006bea90
unsigned __int64 EA::ResourceMan::PFIndexModifiable::GetFarthestFileExtent() const
{
    uint32* p = ((uint32 *)mIndex.mpBucketArray);
    uint32 node = *p;
    if (node == 0) {
        do {
            ++p;
            node = *p;
        } while (node == 0);
    }
    uint32 end = ((uint32 *)mIndex.mpBucketArray)[mIndex.mnBucketCount];
    uint64 best = 0;
    while (node != end) {
        uint64 v = *(uint64*)(node + 0x10) + (uint64)*(uint32*)(node + 0x18);
        if (best < v)
            best = v;
        node = *(uint32*)(node + 0x28);
        while (node == 0) {
            ++p;
            node = *p;
        }
        end = ((uint32 *)mIndex.mpBucketArray)[mIndex.mnBucketCount];
    }
    return best;
}



// @ 0x006beb00
unsigned __int64 EA::ResourceMan::PFIndexModifiable::GetAllocatedBytes() const
{
    uint32* p = ((uint32 *)mIndex.mpBucketArray);
    uint32 node = *p;
    if (node == 0) {
        do {
            ++p;
            node = *p;
        } while (node == 0);
    }
    uint32 end = ((uint32 *)mIndex.mpBucketArray)[mIndex.mnBucketCount];
    uint64 sum = 0;
    while (node != end) {
        sum += (uint64)*(uint32*)(node + 0x18);
        node = *(uint32*)(node + 0x28);
        while (node == 0) {
            ++p;
            node = *p;
        }
        end = ((uint32 *)mIndex.mpBucketArray)[mIndex.mnBucketCount];
    }
    return sum;
}



// @ 0x006beb60
bool EA::ResourceMan::PFIndexModifiable::WriteToMemory(void *& a1, unsigned int & a2, unsigned int a3, bool a4)
{
    // TODO(partial): index serialization (hashtable walk + DBPF record formatting).
    return false;
}



// @ 0x006bed90
void EA::ResourceMan::PFIndexModifiable::SetIsSaved()
{
    uint32* p = ((uint32 *)mIndex.mpBucketArray);
    uint32 node = *p;
    if (node == 0) {
        do {
            ++p;
            node = *p;
        } while (node == 0);
    }
    uint32 end = ((uint32 *)mIndex.mpBucketArray)[mIndex.mnBucketCount];
    if (node != end) {
        do {
            *(uint8*)(node + 0x22) = 1;
            node = *(uint32*)(node + 0x28);
            while (node == 0) {
                ++p;
                node = *p;
            }
        } while (node != ((uint32 *)mIndex.mpBucketArray)[mIndex.mnBucketCount]);
    }
}



// @ 0x006bede0
bool EA::ResourceMan::PFIndexModifiable::Validate(unsigned int begin, unsigned int end) const
{
    // TODO(partial): iterate the record map testing each chunk range.
    return false;
}


// @ 0x006beeb0
bool EA::ResourceMan::PFIndexModifiable::ValidateFreeSpace(unsigned int begin, unsigned int size) const
{
    // TODO(partial): iterate the record map testing each chunk size.
    return false;
}


// @ 0x006bef70
void PFHoleTable::FUN_006bef70(uint32 a, uint32 b)
{
    // TODO(partial): rbtree insert/erase of a hole record.
}


// @ 0x006bf030
void FUN_006bf030(void*, void*)
{}


// @ 0x006bf140
void FUN_006bf140(void*, void*)
{}


// @ 0x006bf1e0
void FUN_006bf1e0(void*)
{}


// @ 0x006bf240
void FUN_006bf240(void*, void*)
{}


// @ 0x006bf2c0
void FUN_006bf2c0(void*, void*, void*)
{}


// @ 0x006bf370
EA::ResourceMan::PFIndexModifiable::PFIndexModifiable(EA::Allocator::ICoreAllocator * allocator)
{
    // TODO(partial): constructor.
    return;
}


// @ 0x006bf430
void FUN_006bf430(void*)
{}


// @ 0x006bf4e0
EA::ResourceMan::PFRecordInfo * EA::ResourceMan::PFIndexModifiable::FindRecord(EA::ResourceMan::Key const & key)
{
    // TODO(partial): hashtable find + return &entry.info.
    return 0;
}


// @ 0x006bf520
bool EA::ResourceMan::PFIndexModifiable::DeleteRecord(EA::ResourceMan::Key const & key, EA::ResourceMan::PFRecordInfo & out)
{
    // TODO(partial): hashtable find + erase.
    return false;
}


// @ 0x006bf5a0
void PFHoleTable::FUN_006bf5a0()
{
    uint32* a = (uint32*)this;
    a[0] = 0xffffffff;
    a[1] = 0xffffffff;
    uint32* p = a + 3;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[0] = (uint32)p;
    a[4] = (uint32)p;
    a[5] = 0;
    *((uint8*)a + 0x18) = 0;
    a[7] = 0;
}


// @ 0x006bf5d0
void FUN_006bf5d0(void*, void*, void*, void*)
{}


// @ 0x006bf660
bool EA::ResourceMan::PFIndexModifiable::ReadFromMemory(void const * data, unsigned int size, unsigned int count, bool flag)
{
    // TODO(partial): parse DBPF index records into the map.
    return false;
}


// @ 0x006bf7d0
void* FUN_006bf7d0(void*, void*)
{ return 0; }


// @ 0x006bf8f0
void FUN_006bf8f0(void*, void*, void*, void*)
{}


// @ 0x006bfa00
unsigned int EA::ResourceMan::PFIndexModifiable::GetKeyList(eastl::vector<EA::ResourceMan::Key, eastl::sp_vector_allocator> * dst, EA::ResourceMan::KeyFilter * filter) const
{
    // TODO(partial): iterate records matching an IKeyFilter.
    return 0;
}


// @ 0x006bfac0
unsigned int EA::ResourceMan::PFIndexModifiable::GetKeysSortedByPosition(eastl::vector<EA::ResourceMan::Key, eastl::sp_vector_allocator> * dst) const
{
    // TODO(partial): append every key to the destination vector.
    return 0;
}


// @ 0x006bfbc0
void EA::ResourceMan::PFIndexModifiable::AddRecord(EA::ResourceMan::Key const & key, EA::ResourceMan::PFRecordInfo const & info)
{
    // TODO(partial): insert-or-find then copy the record info.
    return;
}


// @ 0x006bfc20
void* FUN_006bfc20(void* a, void*, void*)
{ return a; }


// @ 0x006c0120
bool PFIndexModifiable::func24h(HoleTable* holes, u32 a, u32 b, u32 c, u32 d)
{
    void** bucket = mpBucketArray;
    intptr_t node = (intptr_t)*bucket;
    void** bucketPtr = bucket;
    if (node == 0) {
        bucketPtr = bucket + 1;
        node = (intptr_t)*bucketPtr;
        while (node == 0) {
            bucketPtr = bucketPtr + 1;
            node = (intptr_t)*bucketPtr;
        }
    }
    void** itPtr = bucketPtr;
    if (node != (intptr_t)mpBucketArray[mnBucketCount]) {
        for (;;) {
            HoleNode* n = (HoleNode*)node;
            u32 size = n->rec.sizeLo;             // +0x18
            if (size != 0) {
                u32 sLo = n->rec.startLo;         // +0x10
                u32 sHi = n->rec.startHi;         // +0x14
                if (sHi > b || (sHi == b && sLo >= a)) {
                    if (sHi < c || (sHi == c && sLo < d)) {
                        u32 len = d - sLo;
                        if (len >= size)
                            return true;
                        if (!holes->FUN_006bff90(sLo, sHi, size, 0))
                            return false;
                    }
                }
            }
            node = (intptr_t)n->right;            // +0x28 successor
            while (node == 0) {
                bucketPtr = bucketPtr + 1;
                itPtr = bucketPtr;
                node = (intptr_t)*bucketPtr;
            }
            if (node == (intptr_t)mpBucketArray[mnBucketCount])
                break;
        }
    }
    return true;
}
