// Slice s00b047b0: pool / rbtree / vector helpers for the SPPlanet "Simulator"
// subsystem (0x00b047b0..0x00b058f0).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int   uint;

// ---------------------------------------------------------------------------
// shared helper declarations (addresses in comments; chk masks relocations)
// ---------------------------------------------------------------------------
void  make_heap_range2(void* a, void* b, float x, float y, float z);       // 0x00b03e40
void  sort_heap_range2(void* a, void* b, float x, float y, float z);       // 0x00b03ea0
void  heap_adjust(void* a, int n, int i, int j, void* v, float x, float y, float z); // 0x00b02a40
void* make_heap_a(void* a, void* b, void* c, void* d);                     // 0x00b00cd0
void* sort_partition_a(void* a, void* b, void* c, int d);                  // 0x00b038e0
void  sort_by_distance(void* a, void* b, void* c, int d);                  // 0x00b04590
void* make_heap_b(void* a, void* b, void* c, float x, float y, float z,
                  float x2, float y2, float z2);                           // 0x00b00f50
void* sort_partition_b(void* a, void* b, void* c);                         // 0x00b03a20
void  sort_and_visit(void* a, void* b, void* c, float x, float y, float z); // 0x00b04670
void* make_heap_c(void* a, void* b, void* c, float x, float y, float z,
                  float x2, float y2, float z2);                           // 0x00b011f0
void* sort_partition_c(void* a, void* b, void* c);                         // 0x00b03b50

void  operator_delete(void* p);                                            // 0x00f47380
// The two absolute data addresses passed to the allocator; declared as arrays so
// the compiler emits relocations instead of folding the constants.
extern char g_allocName_13ebb38[];                                         // 0x013ebb38
extern char g_allocFile_13f09b4[];                                         // 0x013f09b4
void* EAAllocate(uint size, const char* cat, int a, int b, const char* file, int line); // 0x00f473a0
void  vect_copy(void* dst, void* first, void* last);                       // 0x005f4d00
void  memcpy_(void* dst, void* src, uint n);                               // 0x011e0744
void  DoInsertValueI(void* v, uint* at, const uint* v2);                   // 0x004558a0
void  ReadInt32(void* stream, void* out, int n, int flags);                // 0x0093a780
void* RBTreeIncrement(void* n);                                            // 0x00921580
void  RBTreeErase(void* n, void* head);                                    // 0x00921880
void  RBTreeInsert(void* n, void* parent, void* head, int side);           // 0x009216a0
void* rbtree_find(void* root, void* head, void* key, unsigned char flag);  // 0x00b02750
void* FUN_00b3d3b0(void* a);                                               // 0x00b3d3b0
void* FUN_00b2b1e0(void* a);                                               // 0x00b2b1e0
void  FUN_00b3d420(void* a);                                               // 0x00b3d420
void  release_node_chain(void* p);                                         // 0x00b04350
void* GetSpeciesFromID(void* mgr, int id);                                 // 0x00b90410
uint  FUN_00b8f860(void* species);                                         // 0x00b8f860
void* FUN_00b3d440();                                                      // 0x00b3d440 (no args)
void* FUN_00b3d440_arg(void* p);                                           // 0x00b3d440 (1 stack arg)
void  FUN_00ac0450(void* self);                                            // 0x00ac0450
void  FUN_00c3fe70(void* self);                                            // 0x00c3fe70
void  remove_1st(void* vec);                                               // 0x00acca00
void  reserve_tex(void* vec, uint n);                                      // 0x004e0880
void* erase_range(void* vec, void* first, void* last);                     // 0x00e25bd0

// eastl::vector<T,sp_vector_allocator>::erase(first,last), thiscall.
struct VVec {
    int* mpBegin_00;
    int* mpEnd_04;
    int* mpCap_08;
    void* erase(void* first, void* last);
    void  reserve(uint n);       // 0x00b04c50
};

// ---------------------------------------------------------------------------
// The pool / rbtree container.  Member offsets (retail):
//   +0x00 vptr            +0x04 head anchor    +0x08 node count/limit slot
//   +0x0c root            +0x10 color byte     +0x14 size
//   +0x18 free-list head  +0x20 pool begin     +0x24 pool end
//   +0x28 node stride (bytes)
// ---------------------------------------------------------------------------
struct PoolOwner {
    void  rbcontainer_copy(void* src);       // 0x00b04520 (thiscall, 1 stack arg)
    void* AllocNode(const uint* k);          // 0x00b03820
    void* AllocNodeTiny(const uint* k);      // 0x00b03880
    void  release_node_chain(void* p);       // 0x00b04350
};

struct PoolElem;

// An embedded red-black tree node base: left/right/parent links + colour byte.
struct NodeBase {
    NodeBase* mpLeft_00;      // +0x00
    NodeBase* mpRight_04;     // +0x04
    NodeBase* mpParent_08;    // +0x08
    uint8_t   mColor_0c;      // +0x0c
    uint8_t   pad0d[3];       // +0x0d
};

struct PoolElem;

// The inline value stored in a pooled rbtree node.  Its first member is a
// pointer to a polymorphic object whose vtable[1] slot is the release hook.
struct Payload {
    void*    mpTarget_00;            // +0x00
    uint32_t mRest_04[0x50 / 4 - 1]; // +0x04 .. +0x67
    void CopyFrom(const Payload* src); // 0x00b01cb0 (thiscall copy-ctor)
};

// A pooled tree/list node (the rbtree value and the copy chain share this
// layout): node_base at +0x00, key pair at +0x10/+0x14, payload at +0x18.
struct PoolElem {
    PoolElem* mpLink0_00;     // +0x00  child / free-list link
    PoolElem* mpLink1_04;     // +0x04  child / chain link
    PoolElem* mpParent_08;    // +0x08
    uint8_t   mColor_0c;      // +0x0c
    uint8_t   pad0d[3];       // +0x0d
    uint32_t  mKeyA_10;       // +0x10
    uint32_t  mKeyB_14;       // +0x14
    Payload   mPayload_18;    // +0x18
};

// A pooled object as stored in a slot vector: a polymorphic sub-object at
// +0x68 and a liveness flag at +0x7c.
struct SlottedObj {
    uint32_t pad00[0x68 / 4]; // +0x00 .. +0x64
    void*    mpSub_68;        // +0x68  polymorphic object (vtable[1] released)
    uint32_t pad6c[4];        // +0x6c .. +0x7b
    uint8_t  mFlag_7c;        // +0x7c
    uint8_t  pad7d[3];        // +0x7d
};

// ---------------------------------------------------------------------------
// The pool / rbtree container.  Member offsets (retail):
//   +0x00 vptr            +0x04 anchor node (head == &anchor)
//   +0x14 size            +0x18 free-list head   +0x20 pool begin
//   +0x24 pool end        +0x28 node stride (bytes)
// The anchor is a bare node_base at +0x04: its parent link is the tree root
// and its right link holds the slot pointer.
// ---------------------------------------------------------------------------
struct RBTree : PoolOwner {
    void*    mpvptr_00;       // +0x00  vptr
    NodeBase mAnchor_04;      // +0x04  sentinel node
    int      mnSize_14;       // +0x14  element count
    int*     mpFree_18;       // +0x18  free-list head
    uint32_t mPad_1c;         // +0x1c  (unused gap)
    int*     mpPoolBegin_20;  // +0x20  pooled-node range begin
    int*     mpPoolEnd_24;    // +0x24  pooled-node range end
    uint32_t mnStride_28;     // +0x28  node allocation size

    void  eraseRange(int* out, void* first, void* last);   // 0x00b04ed0
    void  insert(int* out, uint* key, uint hint);          // 0x00b04f70
    void* copyNode(PoolElem* src, PoolElem* parent);       // 0x00b05000
};

// opaque pooled node (key at +0, tree links follow)
struct PoolNode {
    uint32_t mKey_00;
};

// One embedded (begin,end) pointer vector inside a leaf record.
struct LeafVec {
    void** mpBegin_00;        // +0x00
    void** mpEnd_04;          // +0x04
};

// The bookkeeping header the allocator keeps immediately before a block.
struct AllocHdr {
    uint32_t mSize_00;        // +0x00  owned size (0 => not owned)
};

// A 0x19a8-byte simulator leaf record: six embedded pointer vectors, each
// owning a run of pooled pointers that are destructed and released.
struct Leaf {
    uint32_t mPad_000[0x4c / 4];             // +0x000 .. +0x048
    LeafVec  mVec_04c;                       // +0x04c
    uint32_t mPad_054[(0xa4 - 0x54) / 4];    // +0x054 .. +0x0a0
    LeafVec  mVec_0a4;                       // +0x0a4
    uint32_t mPad_0ac[(0xfc - 0xac) / 4];    // +0x0ac .. +0x0f8
    LeafVec  mVec_0fc;                       // +0x0fc
    uint32_t mPad_104[(0x160 - 0x104) / 4];  // +0x104 .. +0x15c
    LeafVec  mVec_160;                       // +0x160
    uint32_t mPad_168[(0x978 - 0x168) / 4];  // +0x168 .. +0x974
    LeafVec  mVec_978;                       // +0x978
    uint32_t mPad_980[(0x1190 - 0x980) / 4]; // +0x980 .. +0x118c
    LeafVec  mVec_1190;                      // +0x1190
    uint32_t mPad_1198[(0x19a8 - 0x1198) / 4];// +0x1198 .. +0x19a4
};

// the entity passed to SimObj::fillSlot (a creature/planet record)
struct SimEnt {
    uint32_t pad00[2];        // +0x00
    void*    mpSub_08;        // +0x08
    uint32_t pad0c[5];        // +0x0c
    uint32_t mId_20;          // +0x20
    uint32_t pad24[3];        // +0x24
    uint32_t mFlags_30;       // +0x30
};

// ---------------------------------------------------------------------------
// thiscall helpers reached through ecx.  A method declared on a class whose
// `this` lives at the same address as the operand produces `mov ecx, <ptr>`.
// ---------------------------------------------------------------------------
struct SimObj;
struct SelfOps {                       // 0x00c3fe70  (thiscall, ecx = SimObj)
    void Finish();
};
struct Sub130 {                        // 0x00ac0450  (thiscall, ecx = SimObj+0x130)
    void Init();
};
struct SysMgr {                        // 0x00b3d440 returns the singleton manager
    void* Get();
};

// ---------------------------------------------------------------------------
// The big "Simulator" manager.  Only the members this slice touches are named;
// everything else is padding.
// ---------------------------------------------------------------------------
struct SimObj : SelfOps {
    uint32_t pad000[0x4c / 4];                 // +0x000 .. +0x048
    uint32_t mKeyId_4c;                        // +0x04c
    uint32_t mKeyPitch_50;                     // +0x050
    uint32_t mKeyIdx_54;                       // +0x054
    uint32_t pad058[(0x108 - 0x58) / 4];       // +0x058 .. +0x104
    void*    mpSub_108;                        // +0x108
    uint32_t pad10c[(0x130 - 0x10c) / 4];      // +0x10c .. +0x12c
    Sub130   mSub_130;                         // +0x130 (1-byte object -> padded to 4)
    uint32_t pad134[(0x148 - 0x134) / 4];      // +0x134 .. +0x144
    uint32_t mFlags_148;                       // +0x148
    uint32_t pad14c;                           // +0x14c
    uint32_t mA_150;                           // +0x150
    uint32_t mB_154;                           // +0x154
    uint32_t mId_158;                          // +0x158
    uint32_t mSel_15c;                         // +0x15c
    uint32_t mIdx_160;                         // +0x160
    uint32_t mE_164;                           // +0x164
    uint32_t mF_168;                           // +0x168
    uint32_t mG_16c;                           // +0x16c
    uint32_t pad170[(0x1b8e08 - 0x170) / 4];   // +0x170 .. +0x1b8e04
    // +0x1b8e08 .. +0x1e5ef is a large opaque region (the same offset as
    // +0x1e5f0 only when the object has no intervening members); modelled as
    // an unchecked byte span so the following members land exactly.
    uint8_t  mbFlag_1b8e08;                    // +0x1b8e08
    uint8_t  padBig[0x57E7];                   // +0x1b8e09 .. +0x1e5ef
    void*    mpTreeRoot_1e5f0;                 // +0x1e5f0
    void*    mpTreeHead_1e5f4;                 // +0x1e5f4

    void  fillSlot(SimEnt* ent);               // 0x00b04aa0
    void* findSlot(uint id, int species);      // 0x00b04ba0
    void* slotAt(uint id, int species, uint idx); // 0x00b04c20
    void  reset();                             // 0x00b05800
    void* curEntry();                          // 0x00b058a0
    uint  curEntryBits();                      // 0x00b058f0
};

// ===========================================================================
// @ 0x00b047b0
// heap-sort range helper: pop each element out of the heap by distance
// ===========================================================================
void* FUN_00b047b0(void** param_1, void** param_2, void** param_3,
                   float px, float py, float pz)
{
    make_heap_range2(param_1, param_2, px, py, pz);
    void** it = param_2;
    while (it < param_3) {
        float* cur = (float*)*it;
        float* top = (float*)*param_1;
        float dcur = (pz - cur[2]) * (pz - cur[2])
                   + (px - cur[0]) * (px - cur[0])
                   + (py - cur[1]) * (py - cur[1]);
        float dtop = (pz - top[2]) * (pz - top[2])
                   + (py - top[1]) * (py - top[1])
                   + (px - top[0]) * (px - top[0]);
        if (dtop < dcur) {
            *it = top;
            heap_adjust(param_1, 0, (int)((char*)param_2 - (char*)param_1) >> 2,
                        0, cur, px, py, pz);
        }
        ++it;
    }
    sort_heap_range2(param_1, param_2, px, py, pz);
    return param_1;
}

// ===========================================================================
// @ 0x00b048f0
// destructor sweep over a range of 0x19a8-byte leaves
// ===========================================================================
int FUN_00b048f0(int param_1, int param_2, int param_3)
{
    if (param_1 != param_2) {
        Leaf* leaf = (Leaf*)param_1;
        do {
            void** end;
            void** it;

            end = leaf->mVec_1190.mpEnd_04;
            for (it = leaf->mVec_1190.mpBegin_00; it < end; it += 0x20)
                (*(void(__thiscall**)(void*, int))(*it))(*it, 0);
            {
                void* a = leaf->mVec_1190.mpBegin_00;
                if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                    operator_delete(a);
            }

            end = leaf->mVec_978.mpEnd_04;
            for (it = leaf->mVec_978.mpBegin_00; it < end; it += 0x20)
                (*(void(__thiscall**)(void*, int))(*it))(*it, 0);
            {
                void* a = leaf->mVec_978.mpBegin_00;
                if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                    operator_delete(a);
            }

            end = leaf->mVec_160.mpEnd_04;
            for (it = leaf->mVec_160.mpBegin_00; it < end; it += 0x20)
                (*(void(__thiscall**)(void*, int))(*it))(*it, 0);
            {
                void* a = leaf->mVec_160.mpBegin_00;
                if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                    operator_delete(a);
            }

            end = leaf->mVec_0fc.mpEnd_04;
            for (it = leaf->mVec_0fc.mpBegin_00; it < end; ++it) {
                void* e = *it;
                if (e)
                    (*(void(__thiscall**)(void*))e)(e);
            }
            {
                void* a = leaf->mVec_0fc.mpBegin_00;
                if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                    operator_delete(a);
            }

            end = leaf->mVec_0a4.mpEnd_04;
            for (it = leaf->mVec_0a4.mpBegin_00; it < end; ++it) {
                void* e = *it;
                if (e)
                    (*(void(__thiscall**)(void*))e)(e);
            }
            {
                void* a = leaf->mVec_0a4.mpBegin_00;
                if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                    operator_delete(a);
            }

            end = leaf->mVec_04c.mpEnd_04;
            for (it = leaf->mVec_04c.mpBegin_00; it < end; ++it) {
                void* e = *it;
                if (e)
                    (*(void(__thiscall**)(void*))e)(e);
            }
            {
                void* a = leaf->mVec_04c.mpBegin_00;
                if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                    operator_delete(a);
            }

            param_3 += 0x19a8;
            param_1 += 0x19a8;
            ++leaf;
        } while (param_1 != param_2);
    }
    return param_3;
}

// ===========================================================================
// @ 0x00b04aa0  thiscall: fill in a species-dependent slot
// ===========================================================================
void SimObj::fillSlot(SimEnt* ent)
{
    unsigned char flag = (unsigned char)(ent->mFlags_30 & 1);
    uint   key  = ent->mId_20;
    if (ent->mpSub_08 == 0 && flag == 0)
        return;

    uint* tail = (uint*)this->mpTreeHead_1e5f4;
    uint  local = key;
    uint* found = (uint*)rbtree_find(this->mpTreeRoot_1e5f0, tail, &local,
                                     this->mbFlag_1b8e08);
    uint* sel = tail;
    if (found != tail && key >= *found && found != found + 0x66a)
        sel = found;
    if (sel == tail)
        return;

    FUN_00b3d3b0(ent);
    void* p = FUN_00b2b1e0(ent);
    if (!p)
        return;
    FUN_00b3d420(p);
    void* sp = GetSpeciesFromID(p, 0);
    if (!sp)
        return;
    uint id = FUN_00b8f860(sp);
    uint* slot;
    if (id == 0x29c388a)
        slot = &sel[0xd];
    else if (id == 0x3a8be428)
        slot = &sel[0xa];
    else if (id == 0x6d60a1cc)
        slot = &sel[0x10];
    else
        return;
    if (!slot)
        return;
    if (flag) {
        slot[0] = 0;
        slot[1] = 0;
        slot[2] = 0;
        return;
    }
    void* src = (*(void*(**)(void*))(*(int*)sp + 0x18))((void*)sp);
    slot[0] = ((uint*)src)[0];
    slot[1] = ((uint*)src)[1];
    slot[2] = ((uint*)src)[2];
}

// ===========================================================================
// @ 0x00b04ba0  thiscall: find the slot for a species id, 2 stack args
// ===========================================================================
void* SimObj::findSlot(uint id, int species)
{
    uint8_t flag = this->mbFlag_1b8e08;
    void*   root = this->mpTreeRoot_1e5f0;
    void*   head = this->mpTreeHead_1e5f4;
    uint* n = (uint*)rbtree_find(root, head, &id, flag);
    if (n == (uint*)head || id < *n || n == n + 0x66a)
        n = (uint*)head;
    if (n == (uint*)head)
        return 0;
    if (species == 0x29c388a)
        return n + 0x29;
    if (species == 0x3a8be428)
        return n + 0x13;
    if (species == 0x6d60a1cc)
        return n + 0x3f;
    return 0;
}

// ===========================================================================
// @ 0x00b04c20  thiscall: look up a slot then index into its vector
// ===========================================================================
void* SimObj::slotAt(uint id, int species, uint idx)
{
    int* v = (int*)this->findSlot(id, species);
    if (v != 0 && idx < (uint)((v[1] - v[0]) >> 2))
        return *(void**)(v[0] + idx * 4);
    return 0;
}

// ===========================================================================
// @ 0x00b04c50  thiscall: reserve() for a vector of 0x38-byte elements
// ===========================================================================
void VVec::reserve(uint n)
{
    if (n > (uint)(((char*)this->mpCap_08 - (char*)this->mpBegin_00) / 0x38)) {
        void* mem;
        if (n != 0)
            mem = EAAllocate(n * 0x38, g_allocName_13ebb38, 0, 0,
                             g_allocFile_13f09b4, 0xd1);
        else
            mem = 0;
        vect_copy(this->mpBegin_00, this->mpEnd_04, mem);
        if (this->mpBegin_00) {
            int* blk = (int*)((char*)this->mpBegin_00 - 4);
            if (*blk != 0)
                operator_delete(this->mpBegin_00);
        }
        int oldn = (int)(((char*)this->mpEnd_04 - (char*)this->mpBegin_00) / 0x38);
        this->mpBegin_00 = (int*)mem;
        this->mpEnd_04   = (int*)((char*)mem + oldn * 0x38);
        this->mpCap_08   = (int*)((char*)mem + n * 0x38);
    }
}

// ===========================================================================
// @ 0x00b04e00  __stdcall: deserialize a vector of ints off a stream
// ===========================================================================
void __stdcall FUN_00b04e00(void* unused, int* vec, void* param_2)
{
    void* first = (void*)vec[0];
    void* last  = (void*)vec[1];
    memcpy_(first, last, (uint)((char*)last - (char*)last));
    vec[1] += -((int)((char*)last - (char*)first) >> 2) * 4;

    uint count = 0;
    void* s = (*(void*(**)(void*))(*(int*)param_2 + 0x20))(param_2);
    void* s2 = (*(void*(**)(void*))(*(int*)s + 0x18))(s);
    ReadInt32(s2, &count, 1, 0);
    reserve_tex(vec, count);

    uint i = 0;
    while (i < count) {
        void* t = (*(void*(**)(void*))(*(int*)param_2 + 0x20))(param_2);
        void* t2 = (*(void*(**)(void*))(*(int*)t + 0x18))(t);
        uint v;
        ReadInt32(t2, &v, 1, 0);
        int* slot = (int*)vec[1];
        if (slot < (int*)vec[2]) {
            vec[1] = (int)(slot + 1);
            if (slot)
                *slot = (int)v;
        } else {
            DoInsertValueI(slot, (uint*)&slot, &v);
        }
        ++i;
    }
    (*(void(__thiscall**)(void*))(*(int*)param_2 + 0x1c))(param_2);
}

// ===========================================================================
// @ 0x00b04ed0  thiscall: erase a range of rbtree nodes
// ===========================================================================
void RBTree::eraseRange(int* param_2, void* param_3, void* param_4)
{
    PoolElem* head = (PoolElem*)&this->mAnchor_04;
    if ((void*)param_3 == *(void**)&this->mAnchor_04.mpRight_04 && param_4 == head) {
        release_node_chain(this->mAnchor_04.mpParent_08);
        this->mAnchor_04.mpParent_08 = 0;
        this->mAnchor_04.mColor_0c = 0;
        this->mnSize_14 = 0;
        this->mAnchor_04.mpRight_04 = (NodeBase*)head;
        this->mAnchor_04.mpLeft_00 = (NodeBase*)head;
        *param_2 = (int)head;
        return;
    }
    PoolElem* cur = (PoolElem*)param_3;
    if (cur != (PoolElem*)param_4) {
        do {
            --this->mnSize_14;
            PoolElem* next = (PoolElem*)RBTreeIncrement(cur);
            RBTreeErase(cur, head);
            void* target = cur->mPayload_18.mpTarget_00;
            if (target) {
                (*(void(__thiscall**)(void*))(*(int*)target + 4))(target);
            }
            if (cur < (PoolElem*)this->mpPoolBegin_20 || (PoolElem*)this->mpPoolEnd_24 <= cur) {
                operator_delete(cur);
            } else {
                cur->mpLink0_00 = (PoolElem*)this->mpFree_18;
                this->mpFree_18 = (int*)cur;
            }
            cur = next;
        } while (cur != (PoolElem*)param_4);
    }
    *param_2 = (int)cur;
}

// ===========================================================================
// @ 0x00b04f70  thiscall: insert a node into the rbtree
// ===========================================================================
void RBTree::insert(int* param_2, uint* param_3, uint)
{
    PoolElem* head = (PoolElem*)&this->mAnchor_04;
    PoolElem* pos  = head;
    int   side;
    PoolElem* root = (PoolElem*)this->mAnchor_04.mpParent_08;
    if (root) {
        PoolElem* n = root;
        uint k1 = param_3[1];
        uint k0 = param_3[0];
        do {
            pos = n;
            if (n->mKeyB_14 < k1 || (n->mKeyB_14 <= k1 && n->mKeyA_10 <= k0))
                n = n->mpLink0_00;
            else
                n = n->mpLink1_04;
        } while (n);
    }
    if (pos != head) {
        if (pos->mKeyB_14 <= param_3[1] &&
            (param_3[1] != pos->mKeyB_14 || pos->mKeyA_10 <= param_3[0])) {
            side = 1;
            goto insert;
        }
    }
    side = 0;
insert:
    {
        PoolElem* nd = (PoolElem*)AllocNode(param_3);
        RBTreeInsert(nd, pos, head, side);
        ++this->mnSize_14;
        *param_2 = (int)nd;
    }
}

// ===========================================================================
// @ 0x00b05000  thiscall: deep-copy a tiny binary tree
// ===========================================================================
void* RBTree::copyNode(PoolElem* src, PoolElem* parent)
{
    PoolElem* node = (PoolElem*)AllocNodeTiny(&src->mKeyA_10);
    node->mpLink0_00 = 0;
    node->mpLink1_04 = 0;
    node->mpParent_08 = parent;
    node->mColor_0c   = src->mColor_0c;

    if (src->mpLink0_00)
        node->mpLink0_00 = (PoolElem*)copyNode(src->mpLink0_00, node);

    PoolElem* s    = src->mpLink1_04;
    PoolElem* prev = node;
    while (s) {
        PoolElem* dst = (PoolElem*)this->mpFree_18;
        if (dst) {
            this->mpFree_18 = (int*)dst->mpLink0_00;
        } else {
            dst = (PoolElem*)EAAllocate(this->mnStride_28, g_allocName_13ebb38, 0, 0,
                                        g_allocFile_13f09b4, 0xd1);
        }
        if (&dst->mKeyA_10) {
            dst->mKeyA_10 = s->mKeyA_10;
            dst->mPayload_18.CopyFrom(&s->mPayload_18);
        }
        dst->mpLink0_00  = 0;
        dst->mpLink1_04  = 0;
        dst->mpParent_08 = prev;
        dst->mColor_0c   = s->mColor_0c;
        prev->mpLink1_04 = dst;
        if (s->mpLink0_00)
            dst->mpLink0_00 = (PoolElem*)copyNode(s->mpLink0_00, dst);
        s    = s->mpLink1_04;
        prev = dst;
    }
    return node;
}

// ===========================================================================
// @ 0x00b051f0  destructor sweep over a count of 0x19a8-byte leaves
// ===========================================================================
void FUN_00b051f0(uint param_1, uint param_2)
{
    if (param_1 >= param_2)
        return;
    uint n = ((param_2 - param_1) - 1) / 0x19a8 + 1;
    Leaf* leaf = (Leaf*)param_1;
    do {
        void** end;
        void** it;

        end = leaf->mVec_1190.mpEnd_04;
        for (it = leaf->mVec_1190.mpBegin_00; it < end; it += 0x20)
            (*(void(__thiscall**)(void*, int))(*it))(*it, 0);
        {
            void* a = leaf->mVec_1190.mpBegin_00;
            if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                operator_delete(a);
        }

        end = leaf->mVec_978.mpEnd_04;
        for (it = leaf->mVec_978.mpBegin_00; it < end; it += 0x20)
            (*(void(__thiscall**)(void*, int))(*it))(*it, 0);
        {
            void* a = leaf->mVec_978.mpBegin_00;
            if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                operator_delete(a);
        }

        end = leaf->mVec_160.mpEnd_04;
        for (it = leaf->mVec_160.mpBegin_00; it < end; it += 0x20)
            (*(void(__thiscall**)(void*, int))(*it))(*it, 0);
        {
            void* a = leaf->mVec_160.mpBegin_00;
            if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                operator_delete(a);
        }

        end = leaf->mVec_0fc.mpEnd_04;
        for (it = leaf->mVec_0fc.mpBegin_00; it < end; ++it) {
            void* e = *it;
            if (e)
                (*(void(__thiscall**)(void*))e)(e);
        }
        {
            void* a = leaf->mVec_0fc.mpBegin_00;
            if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                operator_delete(a);
        }

        end = leaf->mVec_0a4.mpEnd_04;
        for (it = leaf->mVec_0a4.mpBegin_00; it < end; ++it) {
            void* e = *it;
            if (e)
                (*(void(__thiscall**)(void*))e)(e);
        }
        {
            void* a = leaf->mVec_0a4.mpBegin_00;
            if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                operator_delete(a);
        }

        end = leaf->mVec_04c.mpEnd_04;
        for (it = leaf->mVec_04c.mpBegin_00; it < end; ++it) {
            void* e = *it;
            if (e)
                (*(void(__thiscall**)(void*))e)(e);
        }
        {
            void* a = leaf->mVec_04c.mpBegin_00;
            if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                operator_delete(a);
        }

        ++leaf;
        --n;
    } while (n != 0);
}

// ===========================================================================
// @ 0x00b05410  introsort driver (int pointers)
// ===========================================================================
void FUN_00b05410(int param_1, int param_2, int param_3, int param_4)
{
    uint span = (uint)(param_2 - param_1);
    while ((int)(span & 0xfffffffc) > 0x70 && param_3 > 0) {
        int* mid = (int*)make_heap_a((void*)param_1,
                                     (void*)(param_1 + (((param_2 - param_1) >> 2)
                                                        - ((param_2 - param_1) >> 31) >> 1) * 4),
                                     (void*)(param_2 - 4), (void*)param_4);
        int i = (int)sort_partition_a((void*)param_1, (void*)param_2, (void*)*mid, param_4);
        --param_3;
        FUN_00b05410(i, param_2, param_3, param_4);
        span = (uint)(i - param_1);
        param_2 = i;
    }
    if (param_3 == 0)
        sort_by_distance((void*)param_1, (void*)param_2, (void*)param_2, param_4);
}

// ===========================================================================
// @ 0x00b054a0  introsort driver (float keys)
// ===========================================================================
void FUN_00b054a0(int param_1, int param_2, int param_3, int param_4,
                 float px, float py, float pz)
{
    int pa = param_4;
    uint span = (uint)(param_2 - param_1);
    while ((int)(span & 0xfffffffc) > 0x70 && param_3 > 0) {
        int* mid = (int*)make_heap_b((void*)param_1,
                                     (void*)(param_1 + (((param_2 - param_1) >> 2)
                                                        - ((param_2 - param_1) >> 31) >> 1) * 4),
                                     (void*)(param_2 - 4), px, py, pz, px, py, pz);
        int i = (int)sort_partition_b((void*)param_1, (void*)param_2, (void*)*mid);
        --param_3;
        FUN_00b054a0(i, param_2, param_3, pa, px, py, pz);
        span = (uint)(i - param_1);
        param_2 = i;
    }
    if (param_3 == 0)
        sort_and_visit((void*)param_1, (void*)param_2, (void*)param_2, px, py, pz);
}

// ===========================================================================
// @ 0x00b055c0  introsort driver (float keys, variant)
// ===========================================================================
void FUN_00b055c0(int param_1, int param_2, int param_3, int param_4,
                 float px, float py, float pz)
{
    int pa = param_4;
    uint span = (uint)(param_2 - param_1);
    while ((int)(span & 0xfffffffc) > 0x70 && param_3 > 0) {
        int* mid = (int*)make_heap_c((void*)param_1,
                                     (void*)(param_1 + (((param_2 - param_1) >> 2)
                                                        - ((param_2 - param_1) >> 31) >> 1) * 4),
                                     (void*)(param_2 - 4), px, py, pz, px, py, pz);
        int i = (int)sort_partition_c((void*)param_1, (void*)param_2, (void*)*mid);
        --param_3;
        FUN_00b055c0(i, param_2, param_3, pa, px, py, pz);
        span = (uint)(i - param_1);
        param_2 = i;
    }
    if (param_3 == 0)
        FUN_00b047b0((void**)param_1, (void**)param_2, (void**)param_2, px, py, pz);
}

// ===========================================================================
// @ 0x00b056e0  construct a range of pool elements at *out, copying [begin,end)
// ===========================================================================
int** FUN_00b056e0(int** out, int* first, int* last, int* obj)
{
    *out = obj;
    while (first != last) {
        int* p = *out;
        if (p) {
            ((PoolOwner*)p)->rbcontainer_copy(first);
            *p = 0x145c660;
        }
        first = (int*)((char*)first + 0x24);
        *out  = (int*)((char*)*out + 0x24);
    }
    return out;
}

// ===========================================================================
// @ 0x00b05730  construct n pool elements at p, copying src each time
// ===========================================================================
void FUN_00b05730(int* p, uint n, int, void* src)
{
    while (n > 0) {
        if (p) {
            ((PoolOwner*)p)->rbcontainer_copy(src);
            *p = 0x145c660;
        }
        --n;
        p = (int*)((char*)p + 0x24);
    }
}

// ===========================================================================
// @ 0x00b05770  construct pool elements at dest, copying [srcBegin,srcEnd)
// ===========================================================================
int* FUN_00b05770(int* srcBegin, int* srcEnd, int* dest, int)
{
    while (srcBegin != srcEnd) {
        if (dest) {
            ((PoolOwner*)dest)->rbcontainer_copy(srcBegin);
            *dest = 0x145c660;
        }
        srcBegin = (int*)((char*)srcBegin + 0x24);
        dest     = (int*)((char*)dest + 0x24);
    }
    return dest;
}

// ===========================================================================
// @ 0x00b057b0  clear a vector of pooled objects, then erase the range
// ===========================================================================
void FUN_00b057b0(int* param_1)
{
    unsigned int sn = (unsigned int)((param_1[1] - param_1[0]) >> 2);
    unsigned int i = 0;
    if (sn <= 0) {
        ;
    } else {
        do {
            SlottedObj* obj = ((SlottedObj**)param_1[0])[i];
            void* sub = obj->mpSub_68;
            if (sub) {
                obj->mpSub_68 = 0;
                (*(void(__thiscall**)(void*))(*(int*)sub + 4))(sub);
            }
            ++i;
            obj->mFlag_7c = 1;
        } while (i < sn);
    }
    ((VVec*)param_1)->erase((void*)param_1[0], (void*)param_1[1]);
}

// ===========================================================================
// @ 0x00b05800  thiscall: reset a Simulator-like object
// ===========================================================================
void SimObj::reset()
{
    if (this->mFlags_148 & 1) {
        void* tmp = (void*)this;
        void* mgr = FUN_00b3d440_arg(&tmp);
        remove_1st((char*)mgr + 0x1b905c);
    }
    this->mA_150 = 0xffffffff;
    this->mB_154 = 0;
    this->mE_164 = 0xffffffff;
    this->mId_158 = 0x6d60a1cc;
    this->mSel_15c = 0xffffffff;
    this->mIdx_160 = 0xffffffff;
    this->mF_168 = 0;
    {
        int* sub = (int*)this->mpSub_108;
        if (sub) {
            this->mpSub_108 = 0;
            (*(void(__thiscall**)(int*))(sub[0] + 4))(sub);
        }
    }
    this->mG_16c = 6;
    this->mSub_130.Init();
    this->Finish();
}

// ===========================================================================
// @ 0x00b058a0  thiscall: look up an element by index
// ===========================================================================
void* SimObj::curEntry()
{
    uint pitch = this->mId_158;
    uint key   = this->mSel_15c;
    uint idx   = this->mIdx_160;
    SimObj* mgr = (SimObj*)FUN_00b3d440();
    return mgr->slotAt(key, pitch, idx);
}

// slot table returned by findSlot(): a pair of element pointers.
struct SlotVec {
    void** mpBegin_00;      // +0x00
    void** mpEnd_04;        // +0x04
};
// the looked-up entry: a 64-bit bit mask at +0x48.
struct SubObj48 {
    uint mPad_00[0x48 / 4];        // +0x00 .. +0x44
    unsigned long long mBits_48;   // +0x48
};
static uint popcount32(uint v)
{
    v = v - ((v >> 1) & 0x55555555);
    v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
    v = (v + (v >> 4)) & 0x0f0f0f0f;
    return (v * 0x01010101) >> 24;
}

// ===========================================================================
// @ 0x00b058f0  thiscall: bit count of an entry looked up by index
// ===========================================================================
uint SimObj::curEntryBits()
{
    uint idx   = this->mKeyIdx_54;
    uint id50  = this->mKeyPitch_50;
    uint sel4c = this->mKeyId_4c;
    uint r = 0;
    SimObj* mgr = (SimObj*)FUN_00b3d440();
    SlotVec* a = (SlotVec*)mgr->findSlot(sel4c, id50);
    if (a && idx < (uint)(a->mpEnd_04 - a->mpBegin_00)) {
        SubObj48* e = (SubObj48*)a->mpBegin_00[idx];
        if (e)
            r = popcount32((uint)(e->mBits_48 >> 32));
    }
    return r;
}
