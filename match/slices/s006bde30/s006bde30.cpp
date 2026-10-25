// Slice s006bde30 — DatabasePackedFile::OpenRecord + PFIndexModifiable index methods (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "../s006bc1b0/s006bc1b0.h"
#include <string.h>

// Iterator returned by eraseNode: node pointer + current bucket slot.
struct HTIterator {
    uint32*  mpNode;   // 0x00
    uint32** mpBucket; // 0x04
};

// westl hash-table helper (bucket array at +4, bucket count at +8).
struct HT {
    char      pad00[4];
    uint32**  mpBucketArray;  // 0x04
    uint32    mnBucketCount;  // 0x08
    uint32    mnElementCount; // 0x0c
    char      pad10[0xc];
    void*     mAllocator;     // 0x1c
    void*     mpAllocName;    // 0x20

    void      DoFreeNodes(uint32* buckets, uint32 count);   // 0x6be640
    HTIterator* eraseNode(HTIterator* out, uint32* node, uint32* buckets); // 0x6be820
    void      rehash(uint32 newBucketCount);                // 0x6be8d0
};

// Rbtree node used by the lower-bound helper (type/group at 0x10/0x14).
struct RBNode {
    RBNode* mpLeft;    // 0x00
    RBNode* mpRight;   // 0x04
    char    pad08[8];
    uint32  mType;     // 0x10
    uint32  mGroup;    // 0x14
    char    pad18[0x10];
    RBNode* mpNext;    // 0x28
};

// Rbtree header: sentinel at +4, root at +0xc.
struct RBTree {
    char    pad00[4];
    RBNode* mpHeader;  // 0x04
    char    pad08[4];
    RBNode* mpRoot;    // 0x0c

    void* lowerBound(void** out, const uint32* key);  // 0x6be890
};

void   FUN_006be690(uint32* first, uint32* last);   // 0x6be690
void   FUN_006be6e0(uint32* first, uint32* last);   // 0x6be6e0
void* FUN_006be730(uint32** a, uint32** b, uint32** c); // 0x6be730
void   FUN_006be7c0(uint32* a, int first, int last, uint32 value); // 0x6be7c0
void   FUN_006be980(uint32* array, int first, int last, int index,
                    uint32 value, uint32 extra);   // 0x6be980

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

// Node layout used by the PF index hashtable.
struct PFNode {
    uint32  mKeyType;     // 0x00
    uint32  mField04;     // 0x04
    uint32  mField08;     // 0x08
    uint32  mField0C;     // 0x0c
    uint32  mDataOffset;  // 0x10
    uint32  mDataSize;    // 0x14
    uint32  mField18;     // 0x18
    uint32  mField1C;     // 0x1c
    uint16  mFlags;       // 0x20
    uint8   mbSaved;      // 0x22
    char    pad23[5];
    PFNode* mpNext;       // 0x28
};

// Complete on-disk view of PFIndexModifiable's first members.
struct PFIndexMembers {
    void*           vtbl;            // 0x00
    ICoreAllocator* mpAllocator;     // 0x04
    char            pad08[0x24];
    uint32*         mapBucketArray;  // 0x2c
    uint32          mapBucketCount;  // 0x30
    void*           mpBaseIndex;     // 0x34
};

// The 0x006beb60 function is the 4-argument writer; keep a member receiver so
// the calling convention is thiscall with a 0x10-byte stack cleanup.
struct PFIndexWriter : PFIndexModifiable {
    bool Write(void** ppData, uint32* pSize, uint32 count, char flag);
};

// @ 0x006beb60
bool PFIndexWriter::Write(void** ppData, uint32* pSize, uint32 count, char flag)
{
    PFIndexMembers* self = (PFIndexMembers*)this;
    PFNode* first = (PFNode*)*self->mapBucketArray;
    uint32* bucket = self->mapBucketArray;
    if (first == 0) {
        do {
            ++bucket;
            first = (PFNode*)*bucket;
        } while (first == 0);
    }

    bool hasBase = (self->mpBaseIndex != 0);
    bool sameF4 = hasBase;
    bool sameF8 = hasBase;
    uint32 firstF4 = 0;
    uint32 firstF8 = 0;
    if (hasBase) {
        firstF4 = first->mField04;
        firstF8 = first->mField08;
    }

    PFNode* end = (PFNode*)*(self->mapBucketArray + self->mapBucketCount);
    PFNode* node = first;
    while (node != end) {
        if (sameF4 && node->mField04 != firstF4)
            sameF4 = false;
        if (sameF8 && node->mField08 != firstF8)
            sameF8 = false;
        node = node->mpNext;
        while (node == 0) {
            ++bucket;
            node = (PFNode*)*bucket;
        }
    }

    uint32 base = 4;
    uint32 entryBase = 0x24;
    if (sameF4) {
        base = 8;
        entryBase = 0x20;
    }
    if (sameF8) {
        base += 4;
        entryBase -= 4;
    }
    base += 4;
    *pSize = base + (entryBase - 4) * count;

    uint32* mem = (uint32*)((void*(__thiscall*)(void*, uint32, const char*, int))
        (*(void***)self->mpAllocator)[8 / 4])
        (self->mpAllocator, *pSize, "Resource/PFIndexModifiable_image", 0);
    *ppData = mem;
    if (mem == 0)
        return false;

    uint32 n = 1;
    mem[0] = (sameF8 ? 2u : 0u) | (sameF4 ? 1u : 0u) | 4u;
    if (sameF4)
        mem[n++] = firstF4;
    if (sameF8)
        mem[n++] = firstF8;
    mem[n++] = 0;

    uint32* out = mem + n;
    bucket = self->mapBucketArray;
    node = (PFNode*)*bucket;
    if (node == 0) {
        do {
            ++bucket;
            node = (PFNode*)*bucket;
        } while (node == 0);
    }
    while (node != end) {
        if (!sameF4)
            *out++ = node->mField04;
        if (!sameF8)
            *out++ = node->mField08;
        *out++ = node->mKeyType;
        *out++ = node->mDataOffset;
        *out++ = node->mDataSize;
        *out++ = node->mField18;
        *out++ = node->mField1C;
        *out++ = node->mFlags | ((node->mbSaved != 0 || flag != 0) ? 0x10000u : 0u);
        node = node->mpNext;
        while (node == 0) {
            ++bucket;
            node = (PFNode*)*bucket;
        }
    }
    return true;
}

// ===========================================================================
// Resource::DatabasePackedFile
// ===========================================================================

// Record metadata returned by PFIndexModifiable::vtable[0x28].
struct PFRecordInfo {
    uint32 mField0;       // 0x00
    uint32 mField4;       // 0x04
    uint32 mOffset;       // 0x08
    uint32 mSize;         // 0x0c
    uint16 mCompression;  // 0x10
};

struct PFRecordInfoOut {
    uint32 mUnknown;      // 0x00
    uint32 mOffset;       // 0x04
    uint32 mSize;         // 0x08
    uint32 mCompression;  // 0x0c
};

struct OpenRecordPair {
    uint32 mType;     // 0x00
    uint32 mGroup;    // 0x04
    uint32 mInstance; // 0x08
    void*  mpRecord;  // 0x0c
};

struct OpenRecordTree : RBTreeHead {
    void insert(void* access, OpenRecordPair* pair);  // 0x008da3a0
};

// @ 0x006bde30
bool DatabasePackedFile::OpenRecord(void* keyPtr, void** ppRecord, uint32 desiredAccess,
                                    int createDisposition, char flag, void* pInfo)
{
    Key* key = (Key*)keyPtr;
    void* record = 0;
    if ((desiredAccess & 3) == 0)
        return false;

    EA::Thread::AutoLock lock(mIndexMutex, &g_mutexParam);
    if (mnAccessFlags == 0) {
        if (!FUN_006bc0a0())
            return false;
    }

    PFRecordInfo* rec = 0;
    if (mpIndex != 0) {
        rec = (PFRecordInfo*)((void*(__thiscall*)(void*, Key*))
            (*(void***)mpIndex)[0x28 / 4])(mpIndex, key);
    }
    if (rec != 0 && pInfo != 0) {
        PFRecordInfoOut* out = (PFRecordInfoOut*)pInfo;
        out->mUnknown = 0xffffffff;
        out->mOffset = rec->mOffset;
        out->mSize = rec->mSize;
        out->mCompression = rec->mCompression;
    }
    if (ppRecord == 0)
        return rec != 0;

    int disposition = createDisposition;
    if (disposition == 6)
        disposition = ((desiredAccess & 2) != 0) + 3;

    bool reject;
    if (rec != 0)
        reject = (disposition == 1);
    else {
        if (disposition == 3)
            return false;
        reject = (disposition == 5);
    }
    if (reject || (mnAccessFlags & desiredAccess) != desiredAccess)
        return false;

    bool create = false;
    if (disposition == 2 || disposition == 5)
        create = true;

    OpenRecordTree* tree = (OpenRecordTree*)((char*)this + 0x4f0);
    char* end = (char*)this + 0x4f4;

    if (rec != 0) {
        if (((desiredAccess & 2) == 0 || !create) &&
            rec->mCompression != 0 && (flag & 1) == 0)
            return false;

        if ((desiredAccess & 2) == 0) {
            void* found = 0;
            void** it = tree->find(&found, key);
            if (*(void**)*it == end) {
                record = ((void*(__thiscall*)(void*, uint32, PFRecordInfo*, Key*))
                    (*(void***)vtbl)[0x4c / 4])(this, desiredAccess, rec, key);
            } else {
                void* node = *(void**)*it;
                void* openInfo = *(void**)((char*)node + 0x1c);
                if (*(uint32*)((char*)openInfo + 8) != 0x6492fe4)
                    return false;
                record = ((void*(__thiscall*)(void*, uint32, void*, Key*))
                    (*(void***)vtbl)[0x50 / 4])(this, desiredAccess, openInfo, key);
            }
        } else {
            void* found = 0;
            void** it = tree->find(&found, key);
            if (*(void**)*it != end)
                return false;

            if (!create) {
                if (rec->mCompression == 0) {
                    record = ((void*(__thiscall*)(void*, uint32, uint32, uint32,
                                                  Key*))(*(void***)vtbl)[0x58 / 4])
                        (this, desiredAccess, rec->mField0, rec->mField4, key);
                } else {
                    void* buffer = ((void*(__thiscall*)(void*, uint32, const char*, int))
                        (*(void***)mpAllocator)[8 / 4])
                        (mpAllocator, rec->mSize, "Resource/Raw", 0);
                    if (buffer != 0) {
                        if (DecompressRecord(rec->mCompression, rec->mField0,
                                             rec->mField4, rec->mOffset,
                                             rec->mSize, (uint32)buffer)) {
                            record = ((void*(__thiscall*)(void*, uint32, void*,
                                                          uint32, Key*))
                                (*(void***)vtbl)[0x54 / 4])
                                (this, desiredAccess, buffer, rec->mSize, key);
                            if (record != 0) {
                                ((void(__thiscall*)(void*))(*(void***)record)[1])(record);
                                OpenRecordPair pair;
                                pair.mType = key->type;
                                pair.mGroup = key->group;
                                pair.mInstance = key->instance;
                                pair.mpRecord = record;
                                tree->insert(&desiredAccess, &pair);
                                ((void(__thiscall*)(void*))(*(void***)record)[1])(record);
                                *ppRecord = record;
                                return true;
                            }
                        }
                        ((void(__thiscall*)(void*, void*, int))
                            (*(void***)mpAllocator)[0xc / 4])(mpAllocator, buffer, 0);
                    }
                }
            } else {
                record = ((void*(__thiscall*)(void*, uint32, int, int, int, Key*))
                    (*(void***)vtbl)[0x58 / 4])(this, desiredAccess, 0, 0, 0, key);
                if (record != 0) {
                    ((void(__thiscall*)(void*))(*(void***)vtbl)[0x84 / 4])(this);
                    ((void(__thiscall*)(void*, Key*))(*(void***)vtbl)[0x40 / 4])(this, key);
                }
            }
        }
    } else {
        record = ((void*(__thiscall*)(void*, uint32, int, int, int, Key*))
            (*(void***)vtbl)[0x58 / 4])(this, desiredAccess, 0, 0, 0, key);
        if (record != 0)
            ((void(__thiscall*)(void*))(*(void***)vtbl)[0x84 / 4])(this);
    }

    if (record != 0) {
        ((void(__thiscall*)(void*))(*(void***)record)[1])(record);
        OpenRecordPair pair;
        pair.mType = key->type;
        pair.mGroup = key->group;
        pair.mInstance = key->instance;
        pair.mpRecord = record;
        tree->insert(&desiredAccess, &pair);
    }

    if (record != 0)
        ((void(__thiscall*)(void*))(*(void***)record)[1])(record);
    *ppRecord = record;
    return record != 0;
}

// Helper for the index-image read path.  The out-of-line constructor at
// 0x00686430 fills an object whose second word is the allocated buffer.
struct IndexReadBuffer {
    void* mpPad;   // 0x00
    void* mpData;  // 0x04
    void Read(uint32 size, char* outFlag);  // 0x00686430
};

inline uint32& IndexReadOffset(DatabasePackedFile* p) { return p->field_510[8]; }  // 0x530
inline uint32& IndexReadSize(DatabasePackedFile* p)   { return p->field_510[9]; }  // 0x534
inline uint32& IndexImageSize(DatabasePackedFile* p)  { return p->field_510[10]; } // 0x538
inline uint32& IndexBufferSize(DatabasePackedFile* p) { return p->field_510[11]; } // 0x53c

// @ 0x006be1d0
bool DatabasePackedFile::FUN_006be1d0()
{
    if (IndexImageSize(this) == 0) {
        if (mpIndex == 0)
            mpIndex = (PFIndexModifiable*)((void*(__thiscall*)(void*, int))
                (*(void***)vtbl)[0x7c / 4])(this, 3);
        if (((int(__thiscall*)(void*))(*(void***)mpIndex)[0xc / 4])(mpIndex) == 0) {
            ((void(__thiscall*)(void*))(*(void***)vtbl)[0x88 / 4])(this);
        }
        return true;
    }

    bool result = false;
    if (!mFile.FUN_00929900((int)IndexReadOffset(this), (int)IndexReadSize(this), 0))
        return false;

    IndexReadBuffer buffer;
    char flag = 0;
    buffer.Read(IndexBufferSize(this), &flag);

    if (mFile.FUN_00929100(buffer.mpData, IndexBufferSize(this)) != 0) {
        if (mpIndex == 0)
            mpIndex = (PFIndexModifiable*)((void*(__thiscall*)(void*, int))
                (*(void***)vtbl)[0x7c / 4])(this, 3);
        if (mpIndex != 0) {
            result = ((bool(__thiscall*)(void*, void*, uint32, uint32, int))
                (*(void***)mpIndex)[0x34 / 4])
                (mpIndex, buffer.mpData, IndexBufferSize(this),
                 IndexImageSize(this), 1);
        }
        bool committed = ((bool(__thiscall*)(void*))(*(void***)vtbl)[0x78 / 4])(this);
        if (!committed && !mbEnableReadOnCorruptFiles)
            result = false;
        else if (result) {
            ((void(__thiscall*)(void*))(*(void***)vtbl)[0x88 / 4])(this);
            field_4dc = false;
            result = true;
        }
    }

    if (buffer.mpData != 0)
        ::operator delete(buffer.mpData);
    return result;
}

// The 0x006be350 entry point is a thiscall method with five stack arguments
// (database pointer + key type/group/instance + an options word).
struct DBPWriteHelper {
    bool WriteRecord(DatabasePackedFile* self, uint32 type, uint32 group,
                     uint32 instance, uint16 flags);
};

// @ 0x006be350
bool DBPWriteHelper::WriteRecord(DatabasePackedFile* self, uint32 type, uint32 group,
                                 uint32 instance, uint16 flags)
{
    Key key;
    key.type = type;
    key.group = group;
    key.instance = instance;

    EA::Thread::AutoLock lock(self->mIndexMutex, &g_mutexParam);
    if ((self->mnAccessFlags & 2) == 0)
        return false;
    if (self->mnAccessFlags == 0 && !self->FUN_006bc0a0())
        return false;

    OpenRecordTree* tree = (OpenRecordTree*)((char*)self + 0x4f0);
    char* end = (char*)self + 0x4f4;
    void* found = 0;
    void** it = tree->find(&found, &key);
    if (*(void**)*it != end)
        return false;

    void* record = ((void*(__thiscall*)(void*, uint32, int, int, int, Key*))
        (*(void***)self->vtbl)[0x58 / 4])(self, 2, 0, 0, 0, &key);
    if (record == 0)
        return false;
    ((void(__thiscall*)(void*))(*(void***)record)[1])(record);

    OpenRecordPair pair;
    pair.mType = type;
    pair.mGroup = group;
    pair.mInstance = instance;
    pair.mpRecord = record;
    tree->insert(&flags, &pair);
    ((void(__thiscall*)(void*))(*(void***)self->vtbl)[0x84 / 4])(self);

    bool written = self->FUN_006bcb50(type, group, instance, (uint32)record);

    void* found2 = 0;
    void** it2 = tree->find(&found2, &key);
    if (*(void**)*it2 != end) {
        --self->mapCount;
        ((void(__thiscall*)(void*))(*(void***)record)[2])(record);
        ((void(__thiscall*)(void*, void*, int))
            (*(void***)self->mpAllocator)[0xc / 4])
            (self->mpAllocator, *(void**)*it2, 0x20);
    }
    self->field_4dc = true;
    return written;
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
HTIterator* HT::eraseNode(HTIterator* out, uint32* node, uint32* buckets)
{
    RBNode* n = (RBNode*)node;
    out->mpBucket = (uint32**)buckets;
    out->mpNode = (uint32*)n->mpNext;
    while (out->mpNode == 0) {
        ++out->mpBucket;
        out->mpNode = *out->mpBucket;
    }

    RBNode* first = *(RBNode**)buckets;
    if (first == n) {
        *(RBNode**)buckets = first->mpNext;
    } else {
        RBNode* prev = first;
        for (RBNode* cur = first->mpNext; cur != n; cur = cur->mpNext)
            prev = cur;
        prev->mpNext = n->mpNext;
    }

    ((void(__thiscall*)(void*, void*, int))(*(void***)mAllocator)[0xc / 4])
        (mAllocator, node, 0x30);
    --mnElementCount;
    return out;
}

// @ 0x006be890
void* RBTree::lowerBound(void** out, const uint32* key)
{
    RBNode* node = mpRoot;
    void** result = (void**)&mpHeader;
    if (node == 0) {
        *out = result;
        return out;
    }
    uint32 keyType = key[0];
    uint32 keyGroup = key[1];
    do {
        if (keyGroup > node->mGroup ||
            (keyGroup == node->mGroup && keyType > node->mType)) {
            node = node->mpLeft;
        } else {
            result = (void**)node;
            node = node->mpRight;
        }
    } while (node != 0);
    *out = result;
    return out;
}

// @ 0x006be8d0
void HT::rehash(uint32 newBucketCount)
{
    uint32 byteCount = newBucketCount * 4;
    uint32* newBuckets =
        (uint32*)((void*(__thiscall*)(void*, uint32, int, void*))(*(void***)mAllocator)[8 / 4])
            (mAllocator, byteCount + 4, 0, mpAllocName);
    operator_new_array(newBuckets, 0, byteCount);
    newBuckets[newBucketCount] = 0xffffffff;

    for (uint32 i = 0; i < mnBucketCount; ++i) {
        uint32* node = mpBucketArray[i];
        while (node != 0) {
            uint32 bucket = (node[2] ^ node[0]) % newBucketCount;
            mpBucketArray[i] = (uint32*)node[10];
            node[10] = newBuckets[bucket];
            newBuckets[bucket] = (uint32)node;
            node = mpBucketArray[i];
        }
    }

    if (mnBucketCount > 1) {
        ((void(__thiscall*)(void*, void*, uint32))(*(void***)mAllocator)[0xc / 4])
            (mAllocator, mpBucketArray, mnBucketCount * 4 + 4);
    }
    mpBucketArray = (uint32**)newBuckets;
    mnBucketCount = newBucketCount;
}

// @ 0x006be980
void FUN_006be980(uint32* array, int first, int last, int index,
                  uint32 value, uint32 extra)
{
    int left = index * 2;
    int child = left + 2;
    while (child < last) {
        uint32 right = array[child];
        uint32 leftValue = array[child - 1];
        if (*(uint32*)(right + 0x14) < *(uint32*)(leftValue + 0x14) ||
            (*(uint32*)(right + 0x14) <= *(uint32*)(leftValue + 0x14) &&
             *(uint32*)(right + 0x10) < *(uint32*)(leftValue + 0x10))) {
            child = left + 1;
        }
        array[index] = array[child];
        index = child;
        left = index * 2;
        child = left + 2;
    }
    if (child == last) {
        array[index] = array[child - 1];
        index = left + 1;
    }
    FUN_006be7c0(array, first, index, value);
}
