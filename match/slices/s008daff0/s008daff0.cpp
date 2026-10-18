// Slice s008daff0 (0x8daff0..0x8dc200) - Resource::PFIndexModifiable (the modifiable packed-file
// index) plus the hole-table helpers that share the same address range.
//
// Layout of Resource::PFIndexModifiable (retail, from the disassembly):
//   +0x00 vftable
//   +0x04 ICoreAllocator* mpAllocator
//   +0x08 hashtable<u32, pair<...>>  (auto-ref map, buckets start at +0x0c)
//   +0x28 hashtable<Key, pair<Key,PFFileInfo>>  mItemsMap
//         +0x2c mpBucketArray  +0x30 mnBucketCount  +0x34 mnElementCount
//         +0x38 maxLoad(1.0)   +0x3c growth(2.0)    +0x40 nextResize
//         +0x44 allocator      +0x48 flags
//
// Functions (VA, name):
//   008daff0  PFIndexModifiable::Write
//   008db230  PFIndexModifiable::SetIsSaved
//   008db280  PFIndexModifiable::CheckFilesInRange
//   008db310  PFIndexModifiable::CheckFilesInSizeRange
//   008db3a0  HoleSet::Reset
//   008db450  PFIndexModifiable::InsertUnique
//   008db560  rbtree insert helper
//   008db5e0  partition helper
//   008db630  final sort pass
//   008db730  PFIndexModifiable::PFIndexModifiable
//   008db7b0  PFIndexModifiable::_virtual_dtor
//   008db810  PFIndexModifiable::GetFileInfo
//   008db850  PFIndexModifiable::RemoveFile
//   008db8c0  HoleSet::HoleSet
//   008db8f0  quicksort helper
//   008db9b0  PFIndexModifiable::Read
//   008dbb10  PFIndexModifiable::GetFileInfoRef (insert-on-miss)
//   008dbcf0  PFIndexModifiable::GetFiles
//   008dbdb0  PFIndexModifiable::GetAllFiles
//   008dbeb0  PFIndexModifiable::PutFileInfo
//   008dbef0  helper
//   008dbf20  HoleSet::AllocAt
//   008dc000  HoleSet::Release
//   008dc120  HoleSet::MergeFrom

#include "types.h"

// ---------------------------------------------------------------------------
// external callees (direct calls only; rel32 targets are masked)
// ---------------------------------------------------------------------------
extern "C" void* __cdecl operator_delete__(void* p);                                    // 0xf47380
extern "C" void* __cdecl operator_new(int size, const char* name, int a, int b,
                                      const char* file, int line);                      // 0xf473a0
extern "C" void* __cdecl RBTreeIncrement(void* node);                                   // 0x921580
extern "C" void* __cdecl RBTreeDecrement(void* node);                                   // 0x9215c0
extern "C" void* __cdecl RBTreeErase(void* node, void* header);                         // 0x921880
extern "C" void* __cdecl RBTreeInsert(void* node, void* parent, void* header, int lazy); // 0x9216a0
extern "C" void* __cdecl DoNukeSubtree(void* node);                                     // 0x9a9600
struct RBTreeBase { void DoNukeSubtree(void* root); void* Erase(void* node); };
extern "C" void  __cdecl FUN_00925f30();                                                // 0x925f30 (fixed-pool init)
extern "C" void  __cdecl FUN_00921440(void* out, int a, void* b, int c);                // 0x921440
extern "C" void  __cdecl FUN_008de690(int a);                                           // 0x8de690
extern "C" void  __cdecl FUN_008dac90(void** pArray, unsigned n);                       // 0x8dac90 DoFreeNodes
extern "C" void* __cdecl FUN_0088aa50();                                                // 0x88aa50 (hashtable erase)
extern "C" int  __stdcall FUN_008dbc20(void* a, void* node, void* val, bool flags); // 0x8dbc20
extern "C" void  __cdecl FUN_008dbba0(void* a, void* b, void* c);                       // 0x8dbba0
extern "C" void  __cdecl FUN_008daeb0(int* a, int* b, int c);                           // 0x8daeb0
extern "C" void  __cdecl FUN_008daef0(int* a, int* b, int c);                           // 0x8daef0
extern "C" void  __cdecl FUN_008dadd0(int* arr, int a, int b, int c, int d, int e);     // 0x8dadd0
extern const int kTimeoutNone[];

// ---------------------------------------------------------------------------
// shared types
// ---------------------------------------------------------------------------
struct HTNode {                 // 0x20-byte hashtable node for mItemsMap
    char      d00[0xc];         // +0x00 (key: 3 dwords)
    unsigned  mnOffset;         // +0x0c
    unsigned  mnSize;           // +0x10
    char      d14[6];           // +0x14
    unsigned char mbSaved;      // +0x1a
    char      d1b;              // +0x1b
    HTNode*   mpNext;           // +0x1c
};

struct HTIterator { void* mpNode; const void* mpKey; };   // 8-byte hashtable iterator

// eastl::vector<Key, sp_vector_allocator> as seen at the call site: begin/end/cap at +0/+4/+8.
// DoInsertValue is a __thiscall member (ecx = the vector), ret 8.
struct KeyVec {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCap;        // +0x08
    void  DoInsertValue(void* pos, const void* val);   // 0x4e3e10
};

struct HT {                     // the hashtable object (embedded at PFIndexModifiable+0x28)
    char       d00[4];
    HTNode**   mpBucketArray;   // +0x04
    unsigned   mnBucketCount;   // +0x08
    unsigned   mnElementCount;  // +0x0c
    float      mfMaxLoadFactor; // +0x10
    float      mfGrowthFactor;  // +0x14
    unsigned   mnNextResize;    // +0x18
    void*      mpCoreAllocator; // +0x1c
    unsigned   mnFlags;         // +0x20

    void find(void* out, const void* key);                    // 0x8db3d0
    void InsertUnique(void* out, const void* val, unsigned flags); // 0x8db450
    void* GetFileInfoRef(const void* key);                    // 0x8dbb10
    void erase(HTIterator* it);                               // 0x88aa50
};

// hole-table rbtree node: position @+0x10, size @+0x14 (key not inline)
struct HoleNode { char d10[0x10]; unsigned mnPos; unsigned mnSize; };

struct HoleSet {                // EA::ResourceMan hole table (0x20 bytes)
    int        mExtent;         // +0x00
    char       d04[4];          // +0x04
    HoleNode*  mAnchor;         // +0x08 (past-the-end header)
    HoleNode*  mRoot;           // +0x0c
    char       d10[8];          // +0x10
    int        mnSize;          // +0x18
    char       d1c[4];          // +0x1c

    HoleSet();                                        // 0x8db8c0
    void Reset(int extent);                           // 0x8db3a0
    HoleNode* AllocAt(int size);                      // 0x8dbf20
    void Release(unsigned pos, int size);             // 0x8dc000
    void MergeFrom(HoleSet* other);                   // 0x8dc120
};

class PFIndexModifiable {
public:
    void**     vtbl;            // +0x00
    void*      mpAllocator;     // +0x04
    char       d08[0x20];       // +0x08..+0x27
    HT         mItemsMap;       // +0x28
    char       d4c[0x8];        // +0x4c..+0x53

    bool Write(int flags, int* pSize, int count, void** ppBuf,
               int a6, int a7, int a8);                  // 0x8daff0
    void SetIsSaved();                                   // 0x8db230
    bool CheckFilesInRange(unsigned a, unsigned b);      // 0x8db280
    bool CheckFilesInSizeRange(unsigned a, unsigned b);  // 0x8db310
    PFIndexModifiable(void* alloc);                      // 0x8db730
    void* _virtual_dtor(int flags);                      // 0x8db7b0
    void* GetFileInfo(const void* key);                  // 0x8db810
    bool RemoveFile(const void* key, void* out);         // 0x8db850
    int Read(unsigned* buf, unsigned a3, int count, char flag); // 0x8db9b0
    int GetFiles(void* vec, void* filter);               // 0x8dbcf0
    unsigned GetAllFiles(int a2, unsigned a3, int a4, void* vec); // 0x8dbdb0
    void PutFileInfo(int a1, int* info);                 // 0x8dbeb0
};

// ===========================================================================
// 0x8daff0  PFIndexModifiable::Write
// ===========================================================================
// @ 0x008daff0
bool PFIndexModifiable::Write(int flags, int* pSize, int count, void** ppBuf,
                              int a6, int a7, int a8)
{
    bool bSameOffset = true;
    bool bSameSize = true;
    unsigned nFirstOffset = 0;
    unsigned nLastOffset = 0;
    (void)a6; (void)a7;

    HTNode** pb = mItemsMap.mpBucketArray;
    HTNode* p = *pb;
    if (p == 0) {
        ++pb;
        while (*pb == 0)
            ++pb;
        p = *pb;
    }
    if (mItemsMap.mnElementCount == 0) {
        bSameOffset = false;
        bSameSize = false;
    } else {
        nLastOffset = p->mnSize;
        nFirstOffset = p->mnOffset;
        p = p->mpNext;
        while (p == 0) { ++pb; p = *pb; }
    }
    while (p != mItemsMap.mpBucketArray[mItemsMap.mnBucketCount]) {
        if (!bSameSize || p->mnOffset != nFirstOffset)
            bSameSize = false;
        if (bSameOffset && p->mnSize == nLastOffset)
            bSameOffset = true;
        else
            bSameOffset = false;
        p = p->mpNext;
        while (p == 0) { ++pb; p = *pb; }
    }
    int nElem = 0x20;
    *pSize = 4;
    if (bSameSize) {
        *pSize = 8;
        nElem = 0x1c;
    }
    if (bSameOffset) {
        *pSize += 4;
        nElem -= 4;
    }
    *pSize += 4;
    int nTotal = *pSize + (nElem - 4) * count;
    *pSize = nTotal;
    unsigned* pBuf = (unsigned*)((void* (__thiscall*)(void*, unsigned, const char*, int))
                                 (*(void***)mpAllocator)[8 / 4])(mpAllocator, nTotal, (const char*)0x140a1dc, 0);
    *ppBuf = pBuf;
    if (pBuf == 0)
        return false;

    int i = 1;
    *pBuf = (-(unsigned)bSameOffset & 2) | ((flags >> 16) & 0xff) | 4;
    if ((flags >> 16) & 0xff) {
        pBuf[1] = nFirstOffset;
        i = 2;
    }
    if (bSameOffset) {
        pBuf[i] = (unsigned)nLastOffset;
        ++i;
    }
    pBuf[i] = 0;

    unsigned* pOut = pBuf + i + 1;
    HTNode** pb2 = mItemsMap.mpBucketArray;
    HTNode* q = *pb2;
    if (q == 0) {
        ++pb2;
        while (*pb2 == 0) ++pb2;
        q = *pb2;
    }
    HTNode* end = mItemsMap.mpBucketArray[mItemsMap.mnBucketCount];
    while (q != end) {
        if ((flags >> 16) == 0) {
            *pOut++ = q->mnOffset;
        }
        if ((flags >> 24) == 0) {
            *pOut++ = q->mnSize;
        }
        *pOut = *(unsigned*)((char*)q + 0x00);
        pOut[1] = *(unsigned*)((char*)q + 0x0c);
        pOut[2] = *(unsigned*)((char*)q + 0x10) | 0x80000000;
        pOut[3] = *(unsigned*)((char*)q + 0x14);
        unsigned hi;
        if (*(char*)((char*)q + 0x1a) == 0 && a8 == 0)
            hi = 0;
        else
            hi = 0x10000;
        pOut[4] = (unsigned short)*(unsigned*)((char*)q + 0x18) | hi;
        pOut += 5;
        q = q->mpNext;
        while (q == 0) { ++pb2; q = *pb2; }
    }
    return true;
}

// ===========================================================================
// 0x8db230  PFIndexModifiable::SetIsSaved
// ===========================================================================
// @ 0x008db230
void PFIndexModifiable::SetIsSaved()
{
    HTNode** pb = mItemsMap.mpBucketArray;
    HTNode* p = *pb;
    if (p == 0) {
        ++pb;
        while (*pb == 0)
            ++pb;
        p = *pb;
    }
    while (p != mItemsMap.mpBucketArray[mItemsMap.mnBucketCount]) {
        p->mbSaved = 1;
        p = p->mpNext;
        while (p == 0) { ++pb; p = *pb; }
    }
}

// ===========================================================================
// 0x8db280  PFIndexModifiable::CheckFilesInRange
// ===========================================================================
// @ 0x008db280
bool PFIndexModifiable::CheckFilesInRange(unsigned a, unsigned b)
{
    HTNode** pb = mItemsMap.mpBucketArray;
    HTNode* p = *pb;
    if (p == 0) {
        ++pb;
        while (*pb == 0)
            ++pb;
        p = *pb;
    }
    HTNode* end = mItemsMap.mpBucketArray[mItemsMap.mnBucketCount];
    while (p != end) {
        if (p->mnSize != 0) {
            if ((unsigned)(b - (p->mnSize)) < (unsigned)p->mnOffset ||
                (unsigned)p->mnOffset < a) {
            } else {
                return false;
            }
        }
        p = p->mpNext;
        while (p == 0) { ++pb; p = *pb; }
    }
    return true;
}

// ===========================================================================
// 0x8db310  PFIndexModifiable::CheckFilesInSizeRange
// ===========================================================================
// @ 0x008db310
bool PFIndexModifiable::CheckFilesInSizeRange(unsigned a, unsigned b)
{
    if (b == 0)
        return true;
    unsigned nEnd = a + b;
    HTNode** pb = mItemsMap.mpBucketArray;
    HTNode* p = *pb;
    if (p == 0) {
        ++pb;
        while (*pb == 0)
            ++pb;
        p = *pb;
    }
    HTNode* end = mItemsMap.mpBucketArray[mItemsMap.mnBucketCount];
    while (p != end) {
        if (p->mnSize != 0 && p->mnOffset < nEnd && a < p->mnOffset + p->mnSize)
            return false;
        p = p->mpNext;
        while (p == 0) { ++pb; p = *pb; }
    }
    return true;
}

// ===========================================================================
// 0x8db3a0  HoleSet::Reset
// ===========================================================================
// @ 0x008db3a0
void HoleSet::Reset(int extent)
{
    ((RBTreeBase*)((char*)this + 4))->DoNukeSubtree(*(void**)((char*)this + 0x10));
    char* b = (char*)this + 4;
    void* p = b + 4;
    *(void**)(b + 8) = p;
    *(void**)p = p;
    *(void**)(b + 0xc) = 0;
    *(char*)(b + 0x10) = 0;
    *(void**)(b + 0x14) = 0;
    mExtent = extent;
}

// ===========================================================================
// 0x8db450  PFIndexModifiable::InsertUnique
// ===========================================================================
// @ 0x008db450
void HT::InsertUnique(void* out, const void* val, unsigned flags)
{
    (void)flags;
    const unsigned* v = (const unsigned*)val;
    unsigned hash = v[0] ^ v[2];
    unsigned bucket = hash % mnBucketCount;
    HTNode* node = mpBucketArray[bucket];
    while (node != 0) {
        if (v[0] == *(unsigned*)((char*)node + 0x00) &&
            v[1] == *(unsigned*)((char*)node + 0x04) &&
            v[2] == *(unsigned*)((char*)node + 0x08)) {
            *(void**)out = node;
            *((char*)out + 8) = 0;
            *(void**)((char*)out + 4) = &mpBucketArray[bucket];
            return;
        }
        node = node->mpNext;
    }
    FUN_00921440(out, (int)mpCoreAllocator, mpCoreAllocator, 1);
    HTNode* n = (HTNode*)((void* (__thiscall*)(void*, int, int, unsigned))
                          (*(void***)mpCoreAllocator)[8 / 4])(mpCoreAllocator, 0x20, 0, mnFlags);
    if (n != 0) {
        for (int k = 0; k < 7; ++k)
            ((unsigned*)n)[k] = v[k];
    }
    n->mpNext = 0;
    n->mpNext = mpBucketArray[bucket];
    mpBucketArray[bucket] = n;
    ++mnElementCount;
    *(void**)out = n;
    *((char*)out + 8) = 1;
    *(void**)((char*)out + 4) = &mpBucketArray[bucket];
}

// ===========================================================================
// 0x8dbb10  HT::GetFileInfoRef (insert-on-miss)
// ===========================================================================
// @ 0x008dbb10
void* HT::GetFileInfoRef(const void* key)
{
    HTNode* out[2];
    find(&out[0], key);
    if (out[0] == mpBucketArray[mnBucketCount]) {
        int val[7];
        val[0] = *(int*)((char*)key + 0);
        val[1] = *(int*)((char*)key + 4);
        val[2] = *(int*)((char*)key + 8);
        val[3] = 0;
        val[4] = 0;
        val[5] = 0;
        val[6] = 0;
        InsertUnique(&val[0], &val[0], 0);
    }
    return (char*)out[0] + 0xc;
}

// ===========================================================================
// 0x8db560  rbtree insert helper
// ===========================================================================
// @ 0x008db560
struct RBTree {
    void insertUnique(int* out, int* parent, int* value, char flag);   // 0x8db560
};

void RBTree::insertUnique(int* out, int* parent, int* value, char flag)
{
    unsigned lazy = 0;
    if (flag == 0 && parent != (int*)((char*)this + 4) && *(int*)((char*)parent + 0x10) <= *value)
        lazy = 1;
    int node = (int)operator_new(
        0x18, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if ((int*)(node + 0x10) != 0) {
        *(int*)(node + 0x10) = *value;
        *(int*)(node + 0x14) = value[1];
    }
    RBTreeInsert((void*)node, (void*)parent, (void*)((char*)this + 4), (int)lazy);
    *(int*)((char*)this + 0x14) = *(int*)((char*)this + 0x14) + 1;
    *out = node;
}

// ===========================================================================
// 0x8db5e0  partition helper
// ===========================================================================
// @ 0x008db5e0
extern "C" void* FUN_008db5e0(int* lo, int* hi, int* pivot)
{
    for (;;) {
        int* a = lo;
        unsigned pv = *(unsigned*)((char*)pivot + 0xc);
        while (*(unsigned*)((char*)*a + 0xc) < pv)
            ++a;
        int* b = hi;
        unsigned bv = *(unsigned*)((char*)*(b - 1) + 0xc);
        while (pv < bv) {
            --b;
            bv = *(unsigned*)((char*)*(b - 1) + 0xc);
        }
        if (a >= b)
            return a;
        int t = *a;
        *a = *b;
        *b = t;
        ++a;
        lo = a;
    }
}

// ===========================================================================
// 0x8db630  final sort pass
// ===========================================================================
// @ 0x008db630
extern "C" void FUN_008db630(int* lo, int* mid, int* hi, int d)
{
    FUN_008daeb0(lo, mid, d);
    for (int* p = mid; p < hi; ++p) {
        int v = *p;
        if (*(unsigned*)((char*)v + 0xc) < *(unsigned*)((char*)*lo + 0xc)) {
            *p = *lo;
            FUN_008dadd0(lo, 0, (int)(mid - lo), 0, v, d);
        }
    }
    FUN_008daef0(lo, mid, d);
}

// ===========================================================================
// 0x8db730  PFIndexModifiable::PFIndexModifiable
// ===========================================================================
// @ 0x008db730
PFIndexModifiable::PFIndexModifiable(void* alloc)
{
    (void)alloc;
    vtbl = (void**)0x1436878;
    mpAllocator = alloc;
    FUN_00925f30();
    *(float*)((char*)this + 0x38) = *(float*)0x1485720;
    *(float*)((char*)this + 0x3c) = *(float*)0x1470f1c;
    *(void**)((char*)this + 0x44) = (char*)this + 8;
    *(unsigned*)((char*)this + 0x48) = 0;
    *(unsigned*)((char*)this + 0x34) = 0;
    *(unsigned*)((char*)this + 0x40) = 0;
    *(unsigned*)((char*)this + 0x30) = 1;
    *(void**)((char*)this + 0x2c) = (void*)0x154df28;
}

// ===========================================================================
// 0x8db7b0  PFIndexModifiable::_virtual_dtor
// ===========================================================================
// @ 0x008db7b0
void* PFIndexModifiable::_virtual_dtor(int flags)
{
    FUN_008dac90((void**)((char*)this + 0x2c), *(unsigned*)((char*)this + 0x30));
    *(unsigned*)((char*)this + 0x34) = 0;
    unsigned n = *(unsigned*)((char*)this + 0x30);
    if (n > 1) {
        void* a = *(void**)((char*)this + 0x44);
        void* p = ((void* (__thiscall*)(void*))(((void**)(*(void**)a))[0xc / 4]))(a);
        (void)p;
        unsigned sz = n * 4 + 4;
        void* bucket = *(void**)((char*)this + 0x2c);
        ((void (__thiscall*)(void*, void*, unsigned))(((void**)(*(void**)a))[0xc / 4]))(a, bucket, sz);
    }
    FUN_008dac90((void**)((char*)this + 0x0c), *(unsigned*)((char*)this + 0x10));
    *(void**)this = (void*)0x13effb8;
    if (flags & 1)
        operator_delete__(this);
    return this;
}

// ===========================================================================
// 0x8db810  PFIndexModifiable::GetFileInfo
// ===========================================================================
// @ 0x008db810
void* PFIndexModifiable::GetFileInfo(const void* key)
{
    HTNode* out[2];
    HT* ht = &mItemsMap;
    ht->find(&out[0], key);
    if (out[0] != ht->mpBucketArray[ht->mnBucketCount])
        return (char*)out[0] + 0xc;
    return 0;
}

// ===========================================================================
// 0x8db850  PFIndexModifiable::RemoveFile
// ===========================================================================
// @ 0x008db850
bool PFIndexModifiable::RemoveFile(const void* key, void* out)
{
    HTNode* node[2];
    HT* ht = &mItemsMap;
    ht->find(&node[0], key);
    if (node[0] != ht->mpBucketArray[ht->mnBucketCount]) {
        *(unsigned*)((char*)out + 0x00) = *(unsigned*)((char*)node[0] + 0x0c);
        *(unsigned*)((char*)out + 0x04) = *(unsigned*)((char*)node[0] + 0x10);
        *(unsigned*)((char*)out + 0x08) = *(unsigned*)((char*)node[0] + 0x14);
        *(unsigned*)((char*)out + 0x0c) = *(unsigned*)((char*)node[0] + 0x18);
        HTIterator it;
        it.mpNode = node[0];
        it.mpKey = (void*)key;
        ht->erase(&it);
        return true;
    }
    return false;
}

// ===========================================================================
// 0x8db8c0  HoleSet::HoleSet
// ===========================================================================
// @ 0x008db8c0
HoleSet::HoleSet()
{
    mExtent = -1;
    char* p = (char*)this + 8;
    *(void**)(p + 4) = 0;
    *(void**)(p + 8) = 0;
    *(void**)(p + 0xc) = 0;
    *(void**)p = p;
    *(void**)((char*)this + 0xc) = p;
    *(void**)((char*)this + 0x10) = 0;
    *((char*)this + 0x14) = 0;
    *(void**)((char*)this + 0x18) = 0;
}

// ===========================================================================
// 0x8db8f0  quicksort helper
// ===========================================================================
// @ 0x008db8f0
extern "C" void FUN_008db8f0(int* lo, int* hi, int depth, int d)
{
    while ((hi - lo) * 4 > 0x70 && depth > 0) {
        unsigned a = *(unsigned*)((char*)*lo + 0xc);
        unsigned b = *(unsigned*)((char*)*(hi - 1) + 0xc);
        int mid = (int)(hi - lo) / 2;
        unsigned c = *(unsigned*)((char*)lo[mid] + 0xc);
        int* piv;
        if (a < c) {
            if (c < b) piv = lo + mid;
            else if (a < b) piv = hi - 1;
            else piv = lo;
        } else {
            if (a < b) piv = lo;
            else if (c < b) piv = lo + mid;
            else piv = hi - 1;
        }
        int* split = (int*)FUN_008db5e0(lo, hi, (int*)piv);
        --depth;
        FUN_008db8f0(split, hi, depth, d);
        hi = split;
    }
    if (depth == 0)
        FUN_008db630(lo, hi, hi, d);
}

// ===========================================================================
// 0x8db9b0  PFIndexModifiable::Read
// ===========================================================================
// @ 0x008db9b0
int PFIndexModifiable::Read(unsigned* buf, unsigned a3, int count, char flag)
{
    (void)a3;
    unsigned u = buf[0];
    int i = 1;
    if (((u >> 2) & 1) == 0)
        return 0;
    unsigned firstOffset = 0xffffffff;
    if (u & 1) {
        firstOffset = buf[1];
        i = 2;
    }
    unsigned pos = 0xffffffff;
    if ((u >> 1) & 1) {
        pos = buf[i];
        ++i;
    }
    if (buf[i] != 0)
        return 0;
    if (count != 0) {
        unsigned* p = buf + i + 1;
        unsigned sel = u;
        do {
            unsigned offset, ptemp, size, unused;
            if (sel & 1)
                offset = firstOffset;
            else { offset = p[0]; ++p; }
            if ((u >> 1) & 1)
                pos = pos;
            else { pos = *p; ++p; }
            ptemp = *p;
            size = p[1];
            unused = p[2];
            unsigned flags = p[3];
            p += 4;
            unsigned short w;
            if ((int)unused < 0) {
                unsigned w2 = *p;
                ++p;
                (void)w2;
                w = 0;
            } else {
                w = (unused == flags) ? 0 : 0xffff;
            }
            (void)ptemp;
            if (flag)
                w |= 0x100;
            int rec[7];
            rec[0] = offset;
            rec[1] = pos;
            rec[2] = ptemp;
            rec[3] = size;
            rec[4] = (int)w;
            rec[5] = 0;
            mItemsMap.InsertUnique(&rec[0], &rec[0], 0);
            --count;
            if (count == 0)
                break;
            sel = u & 0xff;
        } while (true);
    }
    return 1;
}

// ===========================================================================
// 0x8dbcf0  PFIndexModifiable::GetFiles
// ===========================================================================
// @ 0x008dbcf0
int PFIndexModifiable::GetFiles(void* vec, void* filter)
{
    HTNode** pb = mItemsMap.mpBucketArray;
    HTNode* p = *pb;
    int n = 0;
    if (p == 0) {
        ++pb;
        while (*pb == 0) ++pb;
        p = *pb;
    }
    HTNode* end = mItemsMap.mpBucketArray[mItemsMap.mnBucketCount];
    while (p != end) {
        if (filter == 0 ||
            ((bool (__thiscall*)(void*, void*))(((void**)(*(void**)filter))[4 / 4]))(filter, p)) {
            if (vec != 0) {
                char* w = *(char**)((char*)vec + 4);
                if (w < *(char**)((char*)vec + 8)) {
                    *(char**)((char*)vec + 4) = w + 0xc;
                    if (w != 0) {
                        *(unsigned*)(w + 0) = *(unsigned*)((char*)p + 0x00);
                        *(unsigned*)(w + 4) = *(unsigned*)((char*)p + 0x04);
                        *(unsigned*)(w + 8) = *(unsigned*)((char*)p + 0x08);
                    }
                } else {
                    ((KeyVec*)vec)->DoInsertValue(w, p);
                }
            }
            ++n;
        }
        p = p->mpNext;
        while (p == 0) { ++pb; p = *pb; }
    }
    return n;
}

// ===========================================================================
// 0x8dbdb0  PFIndexModifiable::GetAllFiles
// ===========================================================================
// @ 0x008dbdb0
unsigned PFIndexModifiable::GetAllFiles(int a2, unsigned a3, int a4, void* vec)
{
    (void)a4;
    HTNode** big = (HTNode**)((void* (__thiscall*)(void*, unsigned, const char*, int))
                              (*(void***)mpAllocator)[8 / 4])(
        mpAllocator, mItemsMap.mnElementCount * 4, (const char*)0x140a248, 0);
    HTNode** pb = mItemsMap.mpBucketArray;
    HTNode* p = *pb;
    if (p == 0) {
        ++pb;
        while (*pb == 0) ++pb;
        p = *pb;
    }
    HTNode* end = mItemsMap.mpBucketArray[mItemsMap.mnBucketCount];
    HTNode** out = big;
    while (p != end) {
        *out++ = p;
        p = p->mpNext;
        while (p == 0) { ++pb; p = *pb; }
    }
    a3 &= 0xffffff00;
    FUN_008dbba0(big, (char*)big + a2 * 4, (void*)a3);
    for (HTNode** q = big; q < out; ++q) {
        char* w = *(char**)((char*)vec + 4);
        HTNode* v = *q;
        if (w < *(char**)((char*)vec + 8)) {
            *(char**)((char*)vec + 4) = w + 0xc;
            if (w != 0) {
                *(unsigned*)(w + 0) = *(unsigned*)((char*)v + 0x00);
                *(unsigned*)(w + 4) = *(unsigned*)((char*)v + 0x04);
                *(unsigned*)(w + 8) = *(unsigned*)((char*)v + 0x08);
            }
        } else {
            ((KeyVec*)vec)->DoInsertValue(w, v);
        }
    }
    ((void (__thiscall*)(void*, void*, unsigned))(((void**)(*(void**)mpAllocator))[0xc / 4]))(
        mpAllocator, big, 0);
    return a3;
}

// ===========================================================================
// 0x8dbeb0  PFIndexModifiable::PutFileInfo
// ===========================================================================
// @ 0x008dbeb0
void PFIndexModifiable::PutFileInfo(int a1, int* info)
{
    int c = info[2];
    int d = info[3];
    int a = info[0];
    int b = info[1];
    unsigned* out = (unsigned*)mItemsMap.GetFileInfoRef((const void*)a1);
    out[0] = a;
    out[1] = b;
    out[2] = c;
    out[3] = d;
}

// ===========================================================================
// 0x8dbef0  helper
// ===========================================================================
// @ 0x008dbef0
extern "C" int __stdcall FUN_008dbef0(int a1, int a2, int a3)
{
    bool flag = false;
    FUN_008dbc20((void*)a1, (void*)a2, (void*)a3, flag);
    return a1;
}

// ===========================================================================
// 0x8dbf20  HoleSet::AllocAt
// ===========================================================================
// @ 0x008dbf20
HoleNode* HoleSet::AllocAt(int size)
{
    HoleNode* p = mRoot;
    HoleNode* best = mAnchor;
    unsigned bestSize = 0xffffffff;
    if (p != mAnchor) {
        do {
            unsigned holeSize = p->mnSize;
            if (holeSize >= (unsigned)size && holeSize < bestSize) {
                best = p;
                bestSize = holeSize;
                if (holeSize == (unsigned)size)
                    break;
            }
            p = (HoleNode*)RBTreeIncrement(p);
        } while (p != mAnchor);
        if (best != mAnchor) {
            unsigned pos = best->mnPos;
            unsigned holeSize = best->mnSize;
            HoleNode* next = (HoleNode*)RBTreeIncrement(best);
            --mnSize;
            RBTreeIncrement(best);
            RBTreeErase(best, (char*)this + 8);
            operator_delete__(best);
            unsigned rest = holeSize - (unsigned)size;
            if (rest != 0) {
                void* args[1];
                args[0] = (void*)rest;
                FUN_008dbc20(&size, next, &pos, rest);
            }
            return (HoleNode*)pos;
        }
    }
    int old = mExtent;
    mExtent = old + size;
    return (HoleNode*)old;
}

// ===========================================================================
// 0x8dc000  HoleSet::Release
// ===========================================================================
// @ 0x008dc000
void HoleSet::Release(unsigned pos, int size)
{
    HoleNode* p = mRoot;
    HoleNode* slot = mAnchor;
    while (p != 0) {
        if (p->mnPos < pos) {
            p = (HoleNode*)p->d10;   // left
        } else {
            slot = p;
            p = *(HoleNode**)((char*)p + 4);   // right
        }
    }
    unsigned base = pos;
    int sz = size;
    if (slot != mRoot) {
        HoleNode* prev = (HoleNode*)RBTreeDecrement(slot);
        unsigned pp = prev->mnPos;
        unsigned ps = prev->mnSize;
        if (pp + ps == pos) {
            --mnSize;
            sz = ps + size;
            base = pp;
            RBTreeIncrement(prev);
            RBTreeErase(prev, (char*)this + 8);
            operator_delete__(prev);
        }
    }
    if (slot == mAnchor) {
        if (pos + size == (unsigned)mExtent) {
            mExtent -= size;
            return;
        }
    } else if (base + sz == slot->mnPos) {
        sz += slot->mnSize;
        HoleNode* next = (HoleNode*)RBTreeIncrement(slot);
        --mnSize;
        RBTreeIncrement(slot);
        RBTreeErase(slot, (char*)this + 8);
        operator_delete__(slot);
        slot = next;
    }
    FUN_008dbc20(&pos, slot, &base, pos & 0xffffff00);
}

// ===========================================================================
// 0x8dc120  HoleSet::MergeFrom
// ===========================================================================
// @ 0x008dc120
void HoleSet::MergeFrom(HoleSet* other)
{
    for (HoleNode* p = other->mRoot; p != other->mAnchor; p = (HoleNode*)RBTreeIncrement(p))
        Release(p->mnPos, p->mnSize);
    HoleNode* q = other->mRoot;
    while (q != 0) {
        DoNukeSubtree(*(void**)q);
        HoleNode* n = *(HoleNode**)((char*)q + 4);
        operator_delete__(q);
        q = n;
    }
    other->mRoot = 0;
    other->mAnchor = 0;
    *(char*)((char*)other + 0x14) = 0;
    *(void**)((char*)other + 0x18) = 0;
    HoleNode* hdr = (HoleNode*)((char*)other + 8);
    *(void**)((char*)other + 0x0c) = hdr;
    *(void**)((char*)other + 0x08) = hdr;
}
