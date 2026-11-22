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
#include "EA/IO/IStream.h"
#include "EA/ResourceMan/PFRecordBase.h"
#include "EA/Allocator/ZoneObject.h"

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
    uint32* lowerBound(uint32* out, uint32* key);          // 0x6be890
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
// ---- items of slice s006bede0 end

// ---- items of slice s006bfda0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* sub_9215c0(void*);                     // RBTreeDecrement  (cdecl)
extern void* sub_921580(void*);                     // RBTreeIncrement  (cdecl)
extern void  sub_921880(void*, void*);              // RBTreeErase      (cdecl)
extern void  sub_f47380(void*);                     // allocator deallocate (cdecl)
extern void  sub_9a9600(void*);                     // rbtree nuke subtree
extern void  __fastcall sub_6be890(void*, int, void*, const void*); // lowerBound (set, out, key)
extern void  __fastcall sub_8dae70(void*, int, void*, void*);       // Erase (set, out next, node)
typedef unsigned int   u32;
typedef unsigned char  u8;
struct RBSet {
    void  Find(void* out, const void* key);                      // 0xa057f0 ret 8
    void  DoInsertValue(void* a, void* node, void* b, u32 tag);  // 0x6bf8f0 ret 0x10
};
struct HoleRec { u32 startLo, startHi, sizeLo, sizeHi; };
struct HoleRange { u32 lo, hi; };
struct HoleNode {
    HoleNode* parent;   // +0x00
    HoleNode* left;     // +0x04
    HoleNode* right;    // +0x08
    void*     color;    // +0x0c
    HoleRec   rec;      // +0x10
};
extern void __fastcall FUN_006bfc20(void* set, int edx, void* out, HoleNode* pos, const HoleRec* rec); // 0x6bfc20 insert hole
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
struct HashNode {
    u32      pad00[4];         // +0x00
    u32      startLo;          // +0x10
    u32      startHi;          // +0x14
    u32      sizeLo;           // +0x18
    u32      sizeHi;           // +0x1c
    u32      pad20[2];         // +0x20
    HashNode* next;            // +0x28
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
    // eastl::promote_heap ordered by the 64-bit offset at +0x10
    for (int parent = (last - 1) >> 1;
         (last > first) && (*(uint64*)(a[parent] + 0x10) < *(uint64*)(value + 0x10));
         parent = (last - 1) >> 1) {
        a[last] = a[parent];
        last = parent;
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
uint32* HT::lowerBound(uint32* out, uint32* key)
{
    struct Node {
        Node* right;
        Node* left;
        Node* parent;
        uint32 color;
        uint64 key;
    };
    Node* node = *(Node**)((char*)this + 0xc);
    Node* result = (Node*)((char*)this + 4);
    if (node) {
        uint64 value = *(const uint64*)key;
        do {
            if (value < node->key) {
                result = node;
                node = node->left;
            } else {
                node = node->right;
            }
        } while (node);
    }
    *out = (uint32)result;
    return out;
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

// The v2 index stores the 64-bit-position record layout. The shared
// PFRecordInfo header describes the older 16-byte record; this one is 24 bytes.
struct PFRecordInfoV2 {
    uint64 mnPosition;
    uint32 mnSize;
    uint32 mnSizeDecompressed;
    uint16_t mnCompressionType;
    uint8 mbCommitted;
};
struct PFItemsMapV2 {
    struct Iterator {
        void* mpNode;
        void** mpBucket;
        Iterator() {}
        Iterator(const Iterator& other) : mpNode(other.mpNode), mpBucket(other.mpBucket) {}
    };
    uint32 mFunctors;
    void** mpBucketArray;
    uint32 mnBucketCount;
    void Find(Iterator* out, const EA::ResourceMan::Key& key); // 0x006befb0
    void Erase(Iterator* out, Iterator position); // 0x006be820
    PFRecordInfoV2* FindOrInsert(const EA::ResourceMan::Key& key); // 0x006bf7d0
};

// @ 0x006bf4e0
EA::ResourceMan::PFRecordInfo * EA::ResourceMan::PFIndexModifiable::FindRecord(EA::ResourceMan::Key const & key)
{
    PFItemsMapV2* map = (PFItemsMapV2*)&mIndex;
    PFItemsMapV2::Iterator it;
    map->Find(&it, key);
    if (it.mpNode != map->mpBucketArray[map->mnBucketCount])
        return (EA::ResourceMan::PFRecordInfo*)((char*)it.mpNode + 0x10);
    return 0;
}

// @ 0x006bf520
bool EA::ResourceMan::PFIndexModifiable::DeleteRecord(EA::ResourceMan::Key const & key, EA::ResourceMan::PFRecordInfo & out)
{
    PFItemsMapV2* map = (PFItemsMapV2*)&mIndex;
    PFItemsMapV2::Iterator it;
    map->Find(&it, key);
    if (it.mpNode != map->mpBucketArray[map->mnBucketCount]) {
        *(PFRecordInfoV2*)&out = *(const PFRecordInfoV2*)((char*)it.mpNode + 0x10);
        map->Erase(&it, it);
        return true;
    }
    return false;
}

// The retail initialiser returns the object pointer in eax (mov eax, ecx at
// 0x006bf5a0).  A plain C++ body leaves ecx holding it; route the initial
// pointer through a tiny noinline identity so cl copies `this` into eax and
// keeps the tree pointer in ecx, matching the retail register roles.
__declspec(noinline) static void* __fastcall PFHoleTableKeepThis(void* self) { return self; }

// @ 0x006bf5a0
void PFHoleTable::FUN_006bf5a0()
{
    uint32* a = (uint32*)PFHoleTableKeepThis(this);
    uint32* p = a + 3;
    a[0] = 0xffffffff;
    a[1] = 0xffffffff;
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
    PFRecordInfoV2 value = *(const PFRecordInfoV2*)&info;
    PFItemsMapV2* map = (PFItemsMapV2*)&mIndex;
    *map->FindOrInsert(key) = value;
}

// Empty dispatch tag passed by value to the unique-key insertion overload.
struct HoleInsertUniqueTag {};
struct HoleTree {
    void DoInsertValueHint(HoleNode** result, HoleNode* hint, const HoleRec* value, HoleInsertUniqueTag); // 0x006bf8f0
    HoleNode** Insert(HoleNode** result, HoleNode* hint, const HoleRec* value);
};

// @ 0x006bfc20
HoleNode** HoleTree::Insert(HoleNode** result, HoleNode* hint, const HoleRec* value)
{
    DoInsertValueHint(result, hint, value, HoleInsertUniqueTag());
    return result;
}

// @ 0x006bfda0
void HoleTable::FUN_006bfda0(u32 a, u32 b, u32 c, u32 d)
{
    char* base = data;
    char* set = base + 8;
    HoleRange start = { a, b };
    HoleRange size  = { c, d };
    HoleNode* root;
    ((RBSet*)set)->Find(&root, &start);
    if (root != *(HoleNode**)(set + 4)) {
        HoleNode* prev = (HoleNode*)sub_9215c0(root);
        u32 endLo = prev->rec.startLo + prev->rec.sizeLo;
        u32 endHi = prev->rec.startHi + prev->rec.sizeHi
                  + (endLo < prev->rec.startLo ? 1 : 0);
        if (endLo == start.lo && endHi == start.hi) {
            u32 nLo = prev->rec.sizeLo + size.lo;
            u32 nHi = prev->rec.sizeHi + size.hi + (nLo < prev->rec.sizeLo ? 1 : 0);
            start.lo = prev->rec.startLo;
            start.hi = prev->rec.startHi;
            size.lo = nLo;
            size.hi = nHi;
            (*(int*)(set + 0x0c))--;
            sub_921580(prev);
            sub_921880(prev, set + 4);
            sub_f47380(prev);
        }
    }
    if (root == *(HoleNode**)(set + 4)) {
        u32 extLo = *(u32*)(base + 0);
        if (start.lo + size.lo == extLo &&
            start.hi + size.hi + (start.lo + size.lo < start.lo ? 1 : 0) == *(u32*)(base + 4)) {
            *(u32*)(base + 0) = extLo - size.lo;
            *(u32*)(base + 4) -= size.hi + (extLo < size.lo ? 1 : 0);
            return;
        }
    } else {
        u32 eLo = root->rec.startLo + root->rec.sizeLo;
        u32 eHi = root->rec.startHi + root->rec.sizeHi + (eLo < root->rec.startLo ? 1 : 0);
        if (start.lo + size.lo == eLo &&
            start.hi + size.hi + (start.lo + size.lo < start.lo ? 1 : 0) == eHi) {
            u32 carry = (start.lo + root->rec.startLo < start.lo) ? 1 : 0;
            start.lo = start.lo + root->rec.startLo;
            start.hi = start.hi + root->rec.startHi + carry;
            size.lo = root->rec.sizeLo;
            size.hi = root->rec.sizeHi;
            HoleNode* nxt = (HoleNode*)sub_921580(root);
            (*(int*)(set + 0x0c))--;
            sub_921580(root);
            sub_921880(root, set + 4);
            sub_f47380(root);
            root = nxt;
        }
    }
    ((RBSet*)set)->DoInsertValue(&size, root, &start, size.lo & 0xffffff00u);
}

// @ 0x006bff10
void HoleTable::FUN_006bff10(HoleTable* other)
{
    char* o = other->data;
    char* set = o + 8;
    HoleNode* it  = *(HoleNode**)(set + 8);
    HoleNode* end = *(HoleNode**)(set + 4);
    while (it != end) {
        FUN_006bfda0(it->rec.startLo, it->rec.startHi, it->rec.sizeLo, it->rec.sizeHi);
        it = (HoleNode*)sub_921580(it);
    }
    HoleNode* n = *(HoleNode**)(o + 0x14);
    char* p = o + 8;
    while (n) {
        sub_9a9600(*(void**)n);
        HoleNode* nxt = *(HoleNode**)((char*)n + 4);
        sub_f47380(n);
        n = nxt;
    }
    *(void**)(p + 0x0c) = 0;
    *(u8*)(p + 0x10)    = 0;
    *(void**)(p + 0x14) = 0;
    void* self = p + 4;
    *(void**)(p + 8) = self;
    *(void**)(self)  = self;
}

// @ 0x006bff90
bool HoleTable::FUN_006bff90(u32 startLo, u32 startHi, u32 sizeLo, u32 sizeHi)
{
    u32* base = (u32*)data;
    if ((sizeLo | sizeHi) == 0)
        return true;

    u32 endLo = startLo + sizeLo;
    u32 endHi = startHi + sizeHi + (endLo < startLo ? 1 : 0);
    u32 extLo = base[0];
    u32 extHi = base[1];
    if (endHi < extHi || (endHi == extHi && endLo <= extLo)) {
        // The range ends inside the current extent: split the hole that
        // contains `start` and re-insert the two remainder ranges around it.
        HoleRec key;
        key.startLo = startLo; key.startHi = startHi;
        key.sizeLo  = sizeLo;  key.sizeHi  = sizeHi;

        HoleNode* node;
        sub_6be890(data + 8, 0, &node, &key);               // 0x6be890 lowerBound
        if (node == *(HoleNode**)(data + 0x10))             // set.end()
            return false;

        HoleNode* prev = (HoleNode*)sub_9215c0(node);       // RBTreeDecrement
        u32 plo   = prev->rec.startLo;
        u32 phi   = prev->rec.startHi;
        u32 pEndLo = plo + prev->rec.sizeLo;
        u32 pEndHi = phi + prev->rec.sizeHi + (pEndLo < plo ? 1 : 0);

        HoleNode* erased;
        sub_8dae70(data + 8, 0, &erased, prev);             // erase prev -> next

        if (phi < startHi || (phi == startHi && plo < startLo)) {
            // [prevStart, start) stays free.
            HoleRec gap;
            gap.startLo = plo;
            gap.startHi = phi;
            gap.sizeLo  = startLo - plo;
            gap.sizeHi  = (startHi - phi) - (startLo < plo ? 1 : 0);
            FUN_006bfc20(data + 8, 0, &erased, node, &gap); // 0x6bfc20 insert
        }
        if (endHi < pEndHi || (endHi == pEndHi && endLo < pEndLo)) {
            // [end, prevEnd) stays free.
            HoleRec gap;
            gap.startLo = endLo;
            gap.startHi = endHi;
            gap.sizeLo  = pEndLo - endLo;
            gap.sizeHi  = (pEndHi - endHi) - (pEndLo < endLo ? 1 : 0);
            FUN_006bfc20(data + 8, 0, &node, node, &gap);   // 0x6bfc20 insert
        }
    } else {
        // The range extends past the current extent.
        if (startHi < extHi || (startHi == extHi && startLo < extLo))
            return false;
        base[0] = endLo;
        base[1] = endHi;
        if (startHi > extHi || (startHi == extHi && startLo > extLo))
            FUN_006bfda0(extLo, extHi, startLo - extLo,
                         (startHi - extHi) - (startLo < extLo ? 1 : 0));
    }
    return true;
}

// @ 0x006c0120
bool PFIndexModifiable::func24h(HoleTable* holes, u32 a, u32 b, u32 c, u32 d)
{
    HashNode* node = (HashNode*)*mpBucketArray;
    void** bucketPtr = mpBucketArray;
    if (node == 0) {
        bucketPtr = mpBucketArray + 1;
        node = (HashNode*)*bucketPtr;
        while (node == 0) {
            bucketPtr = bucketPtr + 1;
            node = (HashNode*)*bucketPtr;
        }
    }
    if (node == (HashNode*)mpBucketArray[mnBucketCount])
        return true;
    for (;;) {
        u32 size = node->sizeLo;
        if (size != 0) {
            u32 sLo = node->startLo;
            u32 sHi = node->startHi;
            if (!(sHi >= b && (sHi > b || sLo >= a)))
                return false;
            if (!(sHi <= d && (sHi < d || sLo < c)))
                return false;
            u32 lenLo = c - sLo;
            u32 lenHi = d - sHi - (c < sLo ? 1u : 0u);
            if (lenHi == 0 && size > lenLo)
                return false;
            if (!holes->FUN_006bff90(sLo, sHi, size, 0))
                return false;
        }
        node = node->next;
        if (node == 0) {
            do {
                bucketPtr = bucketPtr + 1;
                node = (HashNode*)*bucketPtr;
            } while (node == 0);
        }
        if (node == (HashNode*)mpBucketArray[mnBucketCount])
            break;
    }
    return true;
}
