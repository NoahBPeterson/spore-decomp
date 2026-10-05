// Slice s006bde30 — DatabasePackedFile::OpenRecord + PFIndexModifiable index methods (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "../s006bc1b0/s006bc1b0.h"

// westl hash-table / rbtree helpers keep their receiver in ecx -> model as a stub receiver.
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

// ===========================================================================
// Resource::PFIndexModifiable
// ===========================================================================

// @ 0x006bed90
void PFIndexModifiable::SetIsSaved()
{
    uint32* p = mapBucketArray;
    uint32 node = *p;
    if (node == 0) {
        do {
            ++p;
            node = *p;
        } while (node == 0);
    }
    uint32 end = mapBucketArray[mapBucketCount];
    if (node != end) {
        do {
            *(uint8*)(node + 0x22) = 1;
            node = *(uint32*)(node + 0x28);
            while (node == 0) {
                ++p;
                node = *p;
            }
        } while (node != mapBucketArray[mapBucketCount]);
    }
}

// @ 0x006bea90
uint64 PFIndexModifiable::GetDataEnd()
{
    uint32* p = mapBucketArray;
    uint32 node = *p;
    if (node == 0) {
        do {
            ++p;
            node = *p;
        } while (node == 0);
    }
    uint32 end = mapBucketArray[mapBucketCount];
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
        end = mapBucketArray[mapBucketCount];
    }
    return best;
}

// @ 0x006beb00
uint64 PFIndexModifiable::GetTotalDiskSize()
{
    uint32* p = mapBucketArray;
    uint32 node = *p;
    if (node == 0) {
        do {
            ++p;
            node = *p;
        } while (node == 0);
    }
    uint32 end = mapBucketArray[mapBucketCount];
    uint64 sum = 0;
    while (node != end) {
        sum += (uint64)*(uint32*)(node + 0x18);
        node = *(uint32*)(node + 0x28);
        while (node == 0) {
            ++p;
            node = *p;
        }
        end = mapBucketArray[mapBucketCount];
    }
    return sum;
}

// @ 0x006beb60
bool PFIndexModifiable::Write()
{
    // TODO(partial): index serialization (hashtable walk + DBPF record formatting).
    return false;
}

// ===========================================================================
// Resource::DatabasePackedFile
// ===========================================================================

// @ 0x006bde30
bool DatabasePackedFile::OpenRecord(void* key, void** ppRecord, uint32 desiredAccess,
                                    int createDisposition, char flag, void* pInfo)
{
    // TODO(partial): full OpenRecord (open-record multimap, decompress, record factory).
    return false;
}

// @ 0x006be1d0
bool DatabasePackedFile::FUN_006be1d0()
{
    // TODO(partial): read/rebuild index record.
    return false;
}

// @ 0x006be350
bool DatabasePackedFile::FUN_006be350()
{
    // TODO(partial): erase open-record entries.
    return false;
}

// ===========================================================================
// westl hashtable/rbtree instantiations
// ===========================================================================

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
