// Slice s009c0f60 -- the eastl containers that own the creature body records.
//
//   009c0f60  vector<0x30-wide T>::insert(pos, const T&)         (no realloc path)
//   009c10c0  vector<0x3c-wide T>::insert(pos, const T&)
//   009c11e0  vector<0x30-wide T>::insert(pos, n, const T&)
//   009c13a0  vector<0x2c-wide T>::insert(pos, n, const T&)      (wiggle statics)
//   009c1560  hash_table::DoInsertValue(out, key, value, reuse)
//   009c1630  hash_table::hash_table(bucket_count, allocator)    (ctor, ret 8)
//   009c1790  vector<0x10c-wide T>::insert(pos, n, const T&)     (body instance data)
//   009c1980  vector<700-byte T>::insert(pos, n, const T&)       (wiggle instance data)
//   009c1b70  vector<bool, fixed_vector_allocator<1,16,1,0,1>>::insert(pos, first, last)
//   009c1d30  CollectFlaggedNodes                                (queue 8-byte records)
//   009c1dc0  nSPCreatureAnim::creature_static_data::Clear
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// The vector member layout is eastl's: mpBegin / mpEnd / mpCapacity at
// 0x00 / 0x04 / 0x08 (sp_vector_allocator holds no state).  Every grow path
// allocates with eastl's debug operator new and releases the old block through
// the aligned-buffer header stored just below mpBegin.
#include "types.h"
#include <string.h>

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;

// ---------------------------------------------------------------------------
// eastl allocator entry points
// ---------------------------------------------------------------------------
void* operator_new(size_t n, const char* name, int flags, int align,
                   const char* file, int line);
void operator_delete__(void* p);

#define EASTL_NEW(n) operator_new((n), "EASTL", 0, 0, \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)

#define EASTL_FREE(p) do { \
    if ((p) != 0 && *(int*)((u8*)(p) - 4) != 0) operator_delete__(p); \
} while (0)

// ---------------------------------------------------------------------------
// per-element helper routines (out of line in the original image)
// ---------------------------------------------------------------------------
void  FUN_009b3c80(void* p);                       // destroy / move slot (0x30)
void  FUN_009b47f0(void* dst, void* first, void* last);
void* FUN_009b4290(void* first, void* last, void* dst);
void  FUN_009b3ab0(void* p);                       // destroy / copy slot (0x3c)
void  FUN_009b4870(void* dst, void* first, void* last);
void* FUN_009b4350(void* first, void* last, void* dst);
void  FUN_009b41e0(const void* value);             // copy to a temporary slot
void* FUN_009b4910(void* first, void* last, void* dst);
void  FUN_009b44e0(void* dst, unsigned n, const void* value, void* at);
void  FUN_009b4ab0(void* dst, void* first, void* last);
void  FUN_009b4490(void* first, void* end, const void* temp);
void  FUN_009b4230(const void* value);
void* FUN_009b4990(void* first, void* last, void* dst);
void  FUN_009b4b10(void* dst, void* first, void* last);
void  FUN_009bef30(void* dst, unsigned n, const void* value, void* at);
void  FUN_009bee30(void* out, void* first, void* last, void* dst);
void  FUN_009beec0(void* first, void* last, const void* src);
void  FUN_009be850(const void* value);             // 0x10c copy ctor / assign
void  FUN_009bedb0(void* out, void* first, void* last, void* dst);
void  FUN_009bf600(void* dst, void* first, void* last);
void  FUN_009c0d40(void* first, void* end, const void* temp);
void  FUN_009bea50(const void* value);             // 700-byte copy ctor / assign
void  FUN_009bedf0(void* out, void* first, void* last, void* dst);
void  FUN_009bf640(void* dst, void* first, void* last);
void  FUN_009c0d70(void* first, void* end, const void* temp);
void* FUN_009bf500(void* first, void* last, void* dst);
void* FUN_009bf580(void* first, void* last, void* dst);
void  FUN_009c0aa0(void* dst, unsigned n, const void* value);
void  FUN_009c0ad0(void* dst, unsigned n, const void* value);
void* bool_insert_fill(void* dst, void* first, long bytes);   // 009a0c50
void  FUN_009b4310(void* dst, void* first, void* last);
void  FUN_009b43f0(void* dst, void* first, void* last);
void  RBTreeInsert(void* node, void* key, void* root, u32 reuse);
void  FUN_00a22220(u32 n);                         // hash_table::Rehash

// ---------------------------------------------------------------------------
// generic growth helper: double the current element count (min 1)
// ---------------------------------------------------------------------------
static unsigned grow_count(unsigned have) {
    return have == 0 ? 1 : have * 2;
}

// ===========================================================================
// 0x30-byte element vector
// ===========================================================================
struct Vec30 {
    u8* begin;
    u8* end;
    u8* cap;

    void Insert(u8* pos, u8* value);                            // 009c0f60
    void InsertFill(u8* pos, unsigned n, const void* value);    // 009c11e0
};

// @ 0x009c0f60
void Vec30::Insert(u8* pos, u8* value) {
    if (end != cap) {
        // the value may live inside the range we are about to shift
        if (pos <= value && value < end) value += 0x30;
        if (end != 0) FUN_009b3c80(end - 0x30);
        FUN_009b47f0(pos, end - 0x30, end);
        for (int i = 0; i < 12; i++) ((u32*)pos)[i] = ((u32*)value)[i];
        end += 0x30;
        return;
    }

    unsigned n = grow_count((unsigned)((end - begin) / 0x30));
    u8* mem = (u8*)EASTL_NEW(n * 0x30);
    u8* mid = (u8*)FUN_009b4290(begin, pos, mem);
    if (mem != 0) FUN_009b3c80(value);
    u8* newEnd = (u8*)FUN_009b4290(pos, end, mem + 0x30);
    EASTL_FREE(begin);
    begin = mem;
    end = newEnd;
    cap = mem + n * 0x30;
    (void)mid;
}

// @ 0x009c11e0
void Vec30::InsertFill(u8* pos, unsigned n, const void* value) {
    if ((unsigned)((cap - end) / 0x30) < n) {
        unsigned have = (unsigned)((end - begin) / 0x30);
        unsigned need = have + n;
        unsigned want = grow_count(have);
        if (need < want) need = want;
        u8* mem = (u8*)EASTL_NEW(need * 0x30);
        u8* p = (u8*)FUN_009b4910(begin, pos, mem);
        FUN_009b44e0(p, n, value, pos);
        u8* newEnd = (u8*)FUN_009b4910(pos, end, p + n * 0x30);
        EASTL_FREE(begin);
        begin = mem;
        end = newEnd;
        cap = mem + need * 0x30;
        return;
    }
    if (n == 0) return;

    FUN_009b41e0(value);                       // copy the value into a local slot
    u8 tmp[0x30];
    memcpy(tmp, value, 0x30);
    u8* e = end;
    unsigned tail = (unsigned)((e - pos) / 0x30);

    if (tail < n) {
        // not enough room after pos: fill the gap, then shift the tail
        FUN_009b44e0(e, n - tail, tmp, pos);
        end = e + (n - tail) * 0x30;
        FUN_009b4ab0(pos, e, end);
        end += tail * 0x30;
        FUN_009b4490(pos, pos + n * 0x30, tmp);
    } else {
        // enough room: move the last n elements out, then shift in the fill
        u8* at = e - n * 0x30;
        FUN_009b4ab0(at, e, e);
        end = e + n * 0x30;
        FUN_009b4490(pos, at + n * 0x30, tmp);
    }
}

// ===========================================================================
// 0x3c-byte element vector
// ===========================================================================
struct Vec3c {
    u8* begin;
    u8* end;
    u8* cap;

    void Insert(u8* pos, u8* value);                            // 009c10c0
};

// @ 0x009c10c0
void Vec3c::Insert(u8* pos, u8* value) {
    if (end != cap) {
        if (pos <= value && value < end) value += 0x3c;
        if (end != 0) FUN_009b3ab0(end - 0x3c);
        FUN_009b4870(pos, end - 0x3c, end);
        FUN_009b3ab0(value);
        end += 0x3c;
        return;
    }

    unsigned n = grow_count((unsigned)((end - begin) / 0x3c));
    u8* mem = (u8*)EASTL_NEW(n * 0x3c);
    FUN_009b4350(begin, pos, mem);
    FUN_009b3ab0(value);
    u8* newEnd = (u8*)FUN_009b4350(pos, end, mem + 0x3c);
    EASTL_FREE(begin);
    begin = mem;
    end = newEnd;
    cap = mem + n * 0x3c;
}

// ===========================================================================
// 0x2c-byte element vector (the wiggle static records)
// ===========================================================================
struct Vec44 {
    u8* begin;
    u8* end;
    u8* cap;

    void InsertFill(u8* pos, unsigned n, const void* value);    // 009c13a0
};

// @ 0x009c13a0
void Vec44::InsertFill(u8* pos, unsigned n, const void* value) {
    if ((unsigned)((cap - end) / 0x2c) < n) {
        unsigned have = (unsigned)((end - begin) / 0x2c);
        unsigned need = have + n;
        unsigned want = grow_count(have);
        if (need < want) need = want;
        u8* mem = (u8*)EASTL_NEW(need * 0x2c);
        u8* p = (u8*)FUN_009b4990(begin, pos, mem);
        FUN_009bef30(p, n, value, pos);
        u8* newEnd = (u8*)FUN_009b4990(pos, end, p + n * 0x2c);
        EASTL_FREE(begin);
        begin = mem;
        end = newEnd;
        cap = mem + need * 0x2c;
        return;
    }
    if (n == 0) return;

    FUN_009b4230(value);
    u8 tmp[0x2c];
    memcpy(tmp, value, 0x2c);
    u8* e = end;
    unsigned tail = (unsigned)((e - pos) / 0x2c);

    if (tail < n) {
        FUN_009bef30(e, n - tail, tmp, pos);
        end = e + (n - tail) * 0x2c;
        FUN_009b4b10(pos, e, end);
        end += tail * 0x2c;
        FUN_009beec0(pos, pos + n * 0x2c, tmp);
    } else {
        u8* at = e - n * 0x2c;
        FUN_009b4b10(at, e, e);
        end = e + n * 0x2c;
        FUN_009beec0(pos, at + n * 0x2c, tmp);
    }
}

// ===========================================================================
// 0x10c-byte element vector (creature_body_instance_data)
// ===========================================================================
struct Vec10c {
    u8* begin;
    u8* end;
    u8* cap;

    void InsertFill(u8* pos, unsigned n, const void* value);    // 009c1790
};

// @ 0x009c1790
void Vec10c::InsertFill(u8* pos, unsigned n, const void* value) {
    if ((unsigned)((cap - end) / 0x10c) < n) {
        unsigned have = (unsigned)((end - begin) / 0x10c);
        unsigned need = have + n;
        unsigned want = grow_count(have);
        if (need < want) need = want;
        u8* mem = (u8*)EASTL_NEW(need * 0x10c);
        u8* p = (u8*)FUN_009bf500(begin, pos, mem);
        FUN_009c0aa0(p, n, value);
        u8* newEnd = (u8*)FUN_009bf500(pos, end, p + n * 0x10c);
        EASTL_FREE(begin);
        begin = mem;
        end = newEnd;
        cap = mem + need * 0x10c;
        return;
    }
    if (n == 0) return;

    FUN_009be850(value);
    u8 tmp[0x10c];
    memcpy(tmp, value, 0x10c);
    u8* e = end;
    unsigned tail = (unsigned)((e - pos) / 0x10c);

    if (tail <= n) {
        FUN_009c0aa0(e, n - tail, tmp);
        end = e + (n - tail) * 0x10c;
        FUN_009bedb0(&n, pos, e, end);
        end += tail * 0x10c;
        FUN_009c0d40(pos, e, tmp);
    } else {
        u8* at = e - n * 0x10c;
        FUN_009bedb0(&n, at, e, e);
        end += n * 0x10c;
        FUN_009bf600(pos, at, e);
        FUN_009c0d40(pos, pos + n * 0x10c, tmp);
    }
}

// ===========================================================================
// 700-byte element vector (creature_body_wiggle_instance_data)
// ===========================================================================
struct Vec700 {
    u8* begin;
    u8* end;
    u8* cap;

    void InsertFill(u8* pos, unsigned n, const void* value);    // 009c1980
};

// @ 0x009c1980
void Vec700::InsertFill(u8* pos, unsigned n, const void* value) {
    if ((unsigned)((cap - end) / 700) < n) {
        unsigned have = (unsigned)((end - begin) / 700);
        unsigned need = have + n;
        unsigned want = grow_count(have);
        if (need < want) need = want;
        u8* mem = (u8*)EASTL_NEW(need * 700);
        u8* p = (u8*)FUN_009bf580(begin, pos, mem);
        FUN_009c0ad0(p, n, value);
        u8* newEnd = (u8*)FUN_009bf580(pos, end, p + n * 700);
        EASTL_FREE(begin);
        begin = mem;
        end = newEnd;
        cap = mem + need * 700;
        return;
    }
    if (n == 0) return;

    FUN_009bea50(value);
    u8 tmp[700];
    memcpy(tmp, value, 700);
    u8* e = end;
    unsigned tail = (unsigned)((e - pos) / 700);

    if (tail <= n) {
        FUN_009c0ad0(e, n - tail, tmp);
        end = e + (n - tail) * 700;
        FUN_009bedf0(&n, pos, e, end);
        end += tail * 700;
        FUN_009c0d70(pos, e, tmp);
    } else {
        u8* at = e - n * 700;
        FUN_009bedf0(&n, at, e, e);
        end += n * 700;
        FUN_009bf640(pos, at, e);
        FUN_009c0d70(pos, pos + n * 700, tmp);
    }
}

// ===========================================================================
// eastl hash table
// ===========================================================================
struct HTable {
    u32 bucketCount;                    // 0x00
    void* buckets;                      // 0x04
    u32 pad08;                          // 0x08
    u32 elementCount;                   // 0x0c
    float loadFactor;                   // 0x10
    float growthFactor;                 // 0x14
    void* freeList;                     // 0x18

    void DoInsertValue(void** out, void* key, u32* value, char reuse);   // 009c1560
};

// @ 0x009c1560
void HTable::DoInsertValue(void** out, void* key, u32* value, char reuse) {
    // a key that is already stored and sorts before the incoming value keeps
    // its node; everything else links a fresh one
    u32 keep = 0;
    if (reuse == 0 && key != (void*)((u8*)this + 4) &&
        *(u32*)((u8*)key + 0x10) <= *value)
        keep = 1;

    void** node = (void**)*(void**)((u8*)this + 0x18);
    if (node == 0)
        node = (void**)EASTL_NEW(*(u32*)((u8*)this + 0x28));
    else
        *(void**)((u8*)this + 0x18) = *node;

    if (node != 0) node[4] = (void*)*value;

    RBTreeInsert(node, key, (u8*)this + 4, keep);
    ((u32*)((u8*)this + 0x14))[0]++;
    *out = node;
}

extern "C" void fixed_pool_base_init(void* pool, void* begin, u32 size,
                                     u32 nodeSize, u32 alignment, u32 flags);
void* FUN_00921340(u32 n);
u32   FUN_009213c0(u32 n);
void* FUN_009c09c0(void* node, void* a, void* b, void* c, void* d, void* e,
                   void* pool);

// @ 0x009c1630  hash_table::hash_table(bucket_count, allocator) -- ctor, ret 8
HTable* HTableCtor(HTable* self, u32 bucketCount, void* allocator) {
    void* pool[0x18 / 4];
    ((void**)pool)[0] = 0;                                  // mpHead
    fixed_pool_base_init(pool, (u8*)self + 0x7c, 0xc0, 0xc, 4, 0);

    void* node = FUN_00921340(0x11);
    FUN_009c09c0(node, (void*)bucketCount, &allocator, &allocator, allocator,
                 &allocator, pool);

    (*(float*)((u8*)self + 0x10)) = 1.0f;                   // 0x461c4000
    (*(float*)((u8*)self + 0x14)) = 2.0f;                   // 0x40000000
    *(void**)((u8*)self + 0x18) = 0;

    u32 need = FUN_009213c0(*(u32*)((u8*)self + 0x0c));
    if (*(u32*)((u8*)self + 0x08) < need)
        FUN_00a22220(need);                                 // Rehash
    return self;
}

// ===========================================================================
// vector<bool, fixed_vector_allocator<1,16,1,0,1>>
// word storage: every element occupies a dword, 16 dwords of inline storage
// ===========================================================================
struct BoolVec {
    u8* begin;                          // 0x00
    u8* end;                            // 0x04
    u8* cap;                            // 0x08
    u8* storage;                        // 0x0c  inline buffer
    u8* storageEnd;                     // 0x10

    void Insert(u8* pos, u8* first, u8* last);                  // 009c1b70
};

void* bool_insert_dispatch(void* at, void* first, long bytes);

// @ 0x009c1b70
void BoolVec::Insert(u8* pos, u8* first, u8* last) {
    if (first == last) return;

    u8* e = end;
    long bytes = last - first;
    unsigned words = (unsigned)(bytes >> 2);

    if (words <= (unsigned)((cap - e) >> 2)) {
        u8* at = e;
        unsigned have = (unsigned)((e - pos) >> 2);
        if (have <= words) {
            // build the new tail first, then insert the remainder in place
            u8* tail = first + have * 4;
            bool_insert_dispatch(at, tail, last - tail);
            end += (words - have) * 4;
            bool_insert_dispatch(end, pos, at - pos);
            end += have * 4;
            memmove(pos + (have - (unsigned)((tail - first) >> 2)) * 4,
                    first, tail - first);
            return;
        }
        u8* split = at - words * 4;
        bool_insert_dispatch(at, split, at - split);
        end += words * 4;
        memmove(split + words * 4, split, (size_t)(at - split));
        u8* head = split;
        bool_insert_dispatch(pos, first, bytes);
        (void)head;
        return;
    }

    unsigned have = (unsigned)((e - begin) >> 2);
    unsigned need = have + words;
    unsigned want = grow_count(have);
    if (need < want) need = want;

    u8* mem = (u8*)EASTL_NEW(need * 4);
    u8* head = pos;
    u8* p = (u8*)bool_insert_dispatch(mem, begin, head - begin);
    p += words * 4;
    p = (u8*)bool_insert_dispatch(p, first, bytes);
    p += (e - pos);
    bool_insert_dispatch(p, pos, e - pos);

    if (begin != 0 && begin != storage) EASTL_FREE(begin);
    end = p;
    begin = mem;
    cap = mem + need * 4;
}

// ===========================================================================
// nSPCreatureAnim body bookkeeping
// ===========================================================================
struct AnimNode {                       // 0x468 bytes
    u8 pad000[0x150];
    u32 flags;                          // 0x150
    u8 pad154[0x440 - 0x154];
    int root;                           // 0x440
};

struct PendingRec {                     // 8-byte queue element
    AnimNode* node;
    char flag;
};

struct PendingQueue {                   // vector<{AnimNode*, char}> at +0x3cc
    PendingRec* begin;                  // 0x3cc
    PendingRec* end;                    // 0x3d0
    PendingRec* cap;                    // 0x3d4

    void Push(const PendingRec& value) {
        PendingRec* e = end;
        if (e < cap) {
            end = e + 1;
            if (e != 0) *e = value;
        } else {
            Grow(e, &value);
        }
    }
    void Grow(PendingRec* at, const PendingRec* value);   // -> 0x009a0c50
};

struct StaticVec {                      // eastl::vector<T, sp_vector_allocator>
    void* begin;
    void* end;
    void* cap;
};

struct XformRec {                       // one inv_bone_rest_xforms entry
    u8 d[0x3c];
};

struct BodyVec {                        // vector<creature_body_static_data>, 0x468
    AnimNode* begin;
    AnimNode* end;
    AnimNode* cap;
};

struct XformVec {                       // vector<0x3c-byte record>
    XformRec* begin;
    XformRec* end;
    XformRec* cap;
};

struct Rgb3 {                           // one skin-colour triple
    float x1, x2, x3;
};

// nSPCreatureAnim::creature_static_data -- the per-species animation template
struct CreatureStaticData {
    u16   name[0x104];                          // 0x000
    char  filename[0x108];                      // 0x208
    u32   uid[2];                               // 0x310
    u32   type_id;                              // 0x318
    u32   group_id;                             // 0x31c
    u32   instance_id;                          // 0x320
    Rgb3  skin_colors[3];                       // 0x324
    u8    pad348[0x34c - 0x348];
    u8    BranchPredicates;                     // 0x34c
    u8    pad34d[0x350 - 0x34d];
    u32   f350;                                 // 0x350
    u32   f354;                                 // 0x354
    u8    pad358[0x374 - 0x358];
    float f374;                                 // 0x374
    int   num_bones_with_mesh_parts;            // 0x378
    u8    pad37c[0x380 - 0x37c];
    u8    f380;                                 // 0x380
    u8    pad381[0x384 - 0x381];
    BodyVec Bodies;                             // 0x384  vector<creature_body_static_data>
    u8    pad390[0x3ac - 0x390];
    int   mMaxStraightLegLength_Scalable;       // 0x3ac  stored as 0xffffffff
    int   mGear;                                // 0x3b0
    XformVec inv_bone_rest_xforms;              // 0x3b4  vector<0x3c-byte records>
    u8    pad3c0[0x3c8 - 0x3c0];
    u32   f3c8;                                 // 0x3c8
    PendingQueue pending;                       // 0x3cc  vector<{AnimNode*, char}>
    u8    pad3d8[0x3e0 - 0x3d8];
    u32   f3e0;                                 // 0x3e0
    u8    pad3e4[0x3ec - 0x3e4];
    float f3ec;                                 // 0x3ec  defaults to 4.0f
    u32   f3f0;                                 // 0x3f0
    u8    pad3f4[0x3f5 - 0x3f4];
    u8    f3f5;                                 // 0x3f5

    void CollectFlagged();                                          // 009c1d30
    void Clear(int unused);                                         // 009c1dc0
};

// @ 0x009c1d30  queue the body records flagged 0x8
void CreatureStaticData::CollectFlagged() {
    int n = (int)(Bodies.end - Bodies.begin);
    if (n == 0) return;

    for (int off = 0; n != 0; off += 0x468, n--) {
        AnimNode* node = (AnimNode*)((char*)Bodies.begin + off);
        if ((node->flags & 8) != 0) {
            PendingRec rec;
            rec.node = node;
            rec.flag = 0;
            pending.Push(rec);
        }
    }
}

// @ 0x009c1dc0  nSPCreatureAnim::creature_static_data::Clear
//   (takes one unused stack argument -- the original returns with `ret 4`)
void CreatureStaticData::Clear(int) {
    name[0] = 0;
    filename[0] = 0;
    uid[0] = 0;
    uid[1] = 0;
    instance_id = 0;
    group_id = 0;
    type_id = 0;
    BranchPredicates = 1;

    // Bodies: run the range destructor, then rewind mpEnd by the whole-element
    // count.  The original spells this `mpEnd -= (mpEnd - mpBegin)` in element
    // units, so any partial trailing element (impossible for a well formed
    // vector) would survive the rewind.
    FUN_009b4310(Bodies.end, Bodies.end, Bodies.begin);
    Bodies.end -= Bodies.end - Bodies.begin;

    mMaxStraightLegLength_Scalable = -1;
    mGear = -1;
    num_bones_with_mesh_parts = -1;

    skin_colors[0].x1 = 1.0f;
    skin_colors[1].x1 = 1.0f;
    skin_colors[0].x2 = 1.0f;
    skin_colors[0].x3 = 1.0f;
    skin_colors[1].x2 = 1.0f;
    skin_colors[1].x3 = 1.0f;
    skin_colors[2].x1 = 1.0f;
    skin_colors[2].x2 = 1.0f;
    skin_colors[2].x3 = 1.0f;

    // inv_bone_rest_xforms: same destroy + whole-element rewind
    FUN_009b43f0(inv_bone_rest_xforms.end, inv_bone_rest_xforms.end,
                 inv_bone_rest_xforms.begin);
    inv_bone_rest_xforms.end -= inv_bone_rest_xforms.end -
                                inv_bone_rest_xforms.begin;

    f3c8 = 0;

    // pending: the original copies the 8-byte records backwards over themselves
    // and then rewinds mpEnd onto mpBegin by the same (dead) element count
    pending.end -= pending.end - pending.begin;

    f374 = 0.0f;
    f350 = 0;
    f354 = 0;
    f3f0 = 0;
    f3f5 = 0;
    f380 = 0;
    f3e0 = 0;
    f3ec = 4.0f;
}
