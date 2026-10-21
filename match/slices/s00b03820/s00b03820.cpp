// Slice s00b03820 -- Simulator / SPGonzago pool allocator + quad-tree math helpers.
// Range 0x00b03820..0x00b046c0.  Module: SPGonzago/SPPlanet.obj (work/migrate/modmap.json
// anchors: Simulator::cFruitGroup::cFruitGroup 0x00b02ca0 .. Simulator::cGameData 0x00b183d0).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast   (see manifest.txt)
#include "types.h"

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

// The two absolute data addresses passed to EAAllocate; declared as arrays so the
// compiler emits relocations instead of folding the constants.
extern char g_allocName_13ebb38[];     // 0x013ebb38
extern char g_allocFile_13f09b4[];     // 0x013f09b4

// ---------------------------------------------------------------- supporting decls
// ---------------------------------------------------------------- supporting decls
struct TinyCopyT { void Copy(const void* src); };                  // 0x00b01cb0 (thiscall, 1 arg)
struct BigElem   { void Ctor(void* src); };                        // 0x00b03680 (thiscall, 1 arg)
struct BigElemD  { void Dtor(); void Dtor2(void* src); };          // 0x00b03740 (thiscall)

void* __cdecl FUN_00f473a0(uint32 size, const char* name, int, int, const char* file, int line);
void  __cdecl FUN_00f47380(void* p);
void  __cdecl FUN_011e0744(void* dst, const void* src, uint32 n);
void  __cdecl FUN_00b02930(void*, int, int, int, void*, float, float, float);
void  __cdecl FUN_00b02a40(void*, int, int, int, void*, float, float, float);
float __cdecl FUN_00936090(float* p);                              // scalar helper
void  __cdecl FUN_00ac8050_ish(void* a, const char* b, int c);      // per-node visitor
void* __cdecl FUN_00921580(void* node);                             // eastl::RBTreeIncrement
void  __cdecl FUN_00921880(void* node, void* head);                 // eastl::RBTreeErase
void  __cdecl FUN_00ac20d0(int n, void* src);                       // vector range assign
void  __cdecl FUN_0076ffd0(void* a, void* b, void* c, void* d);     // eastl::copy

struct RefObj { void AddRef(); void Release(); };                   // vtable slots 0,1
// Explicit vtable slot-0 dispatch (keeps the call from being elided when the vfunc
// has no definition in this TU).
typedef void (__thiscall* RefVtSlot0)(void*);
inline void RefObjCall0(void* obj)
{
    RefVtSlot0* vt = *(RefVtSlot0**)obj;
    vt[0](obj);
}
inline void RefObjCall1(void* obj)
{
    RefVtSlot0* vt = *(RefVtSlot0**)obj;
    vt[1](obj);
}

// ---------------------------------------------------------------- pool node + owner
struct PoolNode {                       // carved in 0x20-byte units
    PoolNode* next;                     // +0x00
    uint32    pad04[3];                 // +0x04
    float     f10;                      // +0x10
    float     f14;                      // +0x14
    float     f18;                      // +0x18
    uint32    pad1c;                    // +0x1c
};

struct PoolOwner {
    uint32    pad00[6];
    PoolNode* freeList;                 // +0x18
    uint32    pad1c[3];
    uint32    chunkSize;                // +0x28

    PoolNode* AllocNode(const uint32* src);     // 0x00b03820
    PoolNode* AllocNodeTiny(const uint32* src); // 0x00b03880

    void release_node_chain(void* node);        // 0x00b04350
    void erase_tree_node(void** out, void* node);// 0x00b043b0
    void* rbcontainer_copy(void* src);          // 0x00b04520
};

// @ 0x00b03820
PoolNode* PoolOwner::AllocNode(const uint32* src)
{
    PoolNode* node = freeList;
    if (node != 0) {
        freeList = node->next;
    } else {
        node = (PoolNode*)FUN_00f473a0(chunkSize, g_allocName_13ebb38, 0, 0,
                                       g_allocFile_13f09b4, 0xd1);
    }
    float* dst = &node->f10;
    if (dst != 0) {
        uint32* d = (uint32*)dst;
        const uint32* s = src;
        d[0] = s[0];
        d[1] = s[1];
        void* r = (void*)s[2];
        d[2] = (uint32)r;
        if (r != 0)
            RefObjCall0(r);
    }
    return node;
}

// @ 0x00b03880
PoolNode* PoolOwner::AllocNodeTiny(const uint32* src)
{
    PoolNode* node = freeList;
    if (node != 0) {
        freeList = node->next;
    } else {
        node = (PoolNode*)FUN_00f473a0(chunkSize, g_allocName_13ebb38, 0, 0,
                                       g_allocFile_13f09b4, 0xd1);
    }
    uint32* d = (uint32*)&node->f10;
    if (d != 0) {
        d[0] = src[0];
        ((TinyCopyT*)((char*)d + 8))->Copy(&src[2]);
    }
    return node;
}

// ------------------------------------------------------------------ quad-tree sorts
// Distance-keyed quick-sort partitions (pointer arrays of nodes with a position at
// +0x5c..+0x64 / +0x10..+0x18).  Kick off from a pivot position.

// @ 0x00b038e0
void __cdecl sort_partition_a(void** lo, void** hi, void* pivot, const float* pos)
{
    float px = pos[0];
    float py = pos[1];
    float pz = pos[2];
    void** left = lo;
    void*  pivotNode = pivot;
    for (;;) {
        void* n;
        do {
            n = *left;
            float dx = px - *(float*)((char*)pivotNode + 0x5c);
            float dy = py - *(float*)((char*)pivotNode + 0x60);
            float dz = pz - *(float*)((char*)pivotNode + 0x64);
            float dp = dz * dz + dy * dy + dx * dx;
            float ex = px - *(float*)((char*)n + 0x5c);
            float ey = py - *(float*)((char*)n + 0x60);
            float ez = pz - *(float*)((char*)n + 0x64);
            float dn = ez * ez + ey * ey + ex * ex;
            if (dn <= dp)
                break;
            ++left;
        } while (true);

        void** right = hi;
        for (;;) {
            float ex = px - *(float*)((char*)pivotNode + 0x5c);
            float ey = py - *(float*)((char*)pivotNode + 0x60);
            float ez = pz - *(float*)((char*)pivotNode + 0x64);
            float dp = ez * ez + ey * ey + ex * ex;
            (void)dp;
            --right;
            void* m = *right;
            float gx = px - *(float*)((char*)m + 0x5c);
            float gy = py - *(float*)((char*)m + 0x60);
            float gz = pz - *(float*)((char*)m + 0x64);
            float dm = gz * gz + gy * gy + gx * gx;
            if (dm > dp)
                break;
        }
        if (left >= right)
            return;
        void* t = *left;
        *left = *right;
        *right = t;
        ++left;
    }
}

// @ 0x00b03a20
void __cdecl sort_partition_b(void** lo, void** hi, void* pivot,
                              float px, float py, float pz)
{
    void** left = lo;
    void*  pivotNode = pivot;
    for (;;) {
        void* n;
        do {
            n = *left;
            float dz = pz - *(float*)((char*)pivotNode + 0x18);
            float dy = py - *(float*)((char*)pivotNode + 0x14);
            float dx = px - *(float*)((char*)pivotNode + 0x10);
            float dp = dz * dz + dy * dy + dx * dx;
            float ex = px - *(float*)((char*)n + 0x10);
            float ey = py - *(float*)((char*)n + 0x14);
            float ez = pz - *(float*)((char*)n + 0x18);
            float dn = ez * ez + ey * ey + ex * ex;
            if (dn <= dp)
                break;
            ++left;
        } while (true);

        void** right = hi;
        for (;;) {
            float ex = px - *(float*)((char*)pivotNode + 0x10);
            float ey = py - *(float*)((char*)pivotNode + 0x14);
            float ez = pz - *(float*)((char*)pivotNode + 0x18);
            float dp = ez * ez + ey * ey + ex * ex;
            (void)dp;
            --right;
            void* m = *right;
            float gx = px - *(float*)((char*)m + 0x10);
            float gy = py - *(float*)((char*)m + 0x14);
            float gz = pz - *(float*)((char*)m + 0x18);
            float dm = gz * gz + gy * gy + gx * gx;
            if (dm > dp)
                break;
        }
        if (left >= right)
            return;
        void* t = *left;
        *left = *right;
        *right = t;
        ++left;
    }
}

// @ 0x00b03b50
void __cdecl sort_partition_c(void** lo, void** hi, const float* pivot,
                              float px, float py, float pz)
{
    float dx0 = px - pivot[0];
    float dy0 = py - pivot[1];
    float dz0 = pz - pivot[2];
    void** left = lo;
    for (;;) {
        void* n;
        do {
            n = *left;
            float ex = px - *(float*)((char*)n + 0);
            float ey = py - *(float*)((char*)n + 4);
            float ez = pz - *(float*)((char*)n + 8);
            float dn = ez * ez + ey * ey + ex * ex;
            float dp = dz0 * dz0 + dy0 * dy0 + dx0 * dx0;
            if (dn <= dp)
                break;
            ++left;
        } while (true);

        void** right = hi;
        for (;;) {
            --right;
            void* m = *right;
            float gx = px - *(float*)((char*)m + 0);
            float gy = py - *(float*)((char*)m + 4);
            float gz = pz - *(float*)((char*)m + 8);
            float dm = gz * gz + gy * gy + gx * gx;
            float dp = dz0 * dz0 + dy0 * dy0 + dx0 * dx0;
            if (dm > dp)
                break;
        }
        if (left >= right)
            return;
        void* t = *left;
        *left = *right;
        *right = t;
        ++left;
    }
}

// @ 0x00b03ca0
void* __cdecl construct_range_big(void* first, void* last, void* cursor)
{
    void* r = cursor;
    while (first != last) {
        if (r != 0)
            ((BigElem*)r)->Ctor(first);
        first = (char*)first + 0x80;
        r = (char*)r + 0x80;
    }
    return r;
}

// @ 0x00b03d70
void __cdecl make_heap_range(void* first, void* last,
                             float px, float py, float pz)
{
    int n = (int)(((char*)last - (char*)first) >> 2);
    if (n < 2)
        return;
    for (int i = ((n - 2) >> 1) + 1; i != 0; ) {
        --i;
        FUN_00b02930(first, i, n, i, *(void**)((char*)first + i * 4), px, py, pz);
    }
}

// @ 0x00b03dd0
void __cdecl sort_heap_range(void* first, void* last,
                             float px, float py, float pz)
{
    int n = (int)(((char*)last - (char*)first) >> 2);
    while (n > 1) {
        void** e = (void**)((char*)last - 4);
        void*  v = *e;
        *e = *(void**)first;
        FUN_00b02930(first, 0, n - 1, 0, v, px, py, pz);
        --e;
        last = e;
        n = (int)(((char*)last - (char*)first) >> 2);
    }
}

// @ 0x00b03e40
void __cdecl make_heap_range2(void* first, void* last,
                              float px, float py, float pz)
{
    int n = (int)(((char*)last - (char*)first) >> 2);
    if (n < 2)
        return;
    for (int i = ((n - 2) >> 1) + 1; i != 0; ) {
        --i;
        FUN_00b02a40(first, i, n, i, *(void**)((char*)first + i * 4), px, py, pz);
    }
}

// @ 0x00b03ea0
void __cdecl sort_heap_range2(void* first, void* last,
                              float px, float py, float pz)
{
    int n = (int)(((char*)last - (char*)first) >> 2);
    while (n > 1) {
        void** e = (void**)((char*)last - 4);
        void*  v = *e;
        *e = *(void**)first;
        FUN_00b02a40(first, 0, n - 1, 0, v, px, py, pz);
        --e;
        last = e;
        n = (int)(((char*)last - (char*)first) >> 2);
    }
}

// @ 0x00b03f10
void* __cdecl destroy_range_big(void* first, void* last, void* cursor)
{
    void* r = cursor;
    while (last != first) {
        ((BigElemD*)r)->Dtor();
        last = (char*)last + 0x80;
        r = (char*)r + 0x80;
    }
    return r;
}

// @ 0x00b03f50
void* __cdecl destroy_range_big2(void* first, void* last, void* cursor)
{
    if (last != first) {
        do {
            last = (char*)last - 0x80;
            cursor = (char*)cursor - 0x80;
            ((BigElemD*)cursor)->Dtor2(last);
        } while (last != first);
    } else {
        cursor = cursor;
    }
    return cursor;
}

// ------------------------------------------------------------------ node lookup
struct RedBlackTree {
    void* begin;                        // +0x00
    void* end;                          // +0x04
    uint8 flags[0x19a810];              // +0x08..
    uint8 flag19a818;                   // +0x19a818

    void* Find(uint32* key);            // 0x00b03f90
};

void* __cdecl FUN_00b02750(void* begin, void* last, uint32* key, uint8 f);

// @ 0x00b03f90
void* RedBlackTree::Find(uint32* key)
{
    void* last = end;
    void* r = FUN_00b02750(begin, last, key, flag19a818);
    if (r == last || *key < *(uint32*)r || r == (char*)r + 0x19a8)
        r = last;
    return r;
}

// ------------------------------------------------------------------ node pool ctor
// @ 0x00b04270
void __cdecl pool_owner_ctor(void* self)
{
    uint32* p = (uint32*)self;
    p[0x20 / 4] = 0;
    p[0x24 / 4] = 0;
    p[0x28 / 4] = 0;
    p[0x2c / 4] = 0;
    p[0x30 / 4] = 0;
    p[0x34 / 4] = 0;
    p[0x38 / 4] = 0;
    p[0x3c / 4] = 0;
    p[0x40 / 4] = 0;
    p[0x58 / 4] = 0;
    *(void**)((char*)self + 0x44) = (char*)self + 0x5c;
    *(void**)((char*)self + 0x48) = (char*)self + 0x5c;
    *(void**)((char*)self + 0x4c) = (char*)self + 0x5c + 0x40;
    p[0xb0 / 4] = 0;
    *(void**)((char*)self + 0x9c) = (char*)self + 0xb4;
    *(void**)((char*)self + 0xa0) = (char*)self + 0xb4;
    *(void**)((char*)self + 0xa4) = (char*)self + 0xb4 + 0x40;
    p[0x108 / 4] = 0;
    *(void**)((char*)self + 0xf4) = (char*)self + 0x10c;
    *(void**)((char*)self + 0xf8) = (char*)self + 0x10c;
    *(void**)((char*)self + 0xfc) = (char*)self + 0x10c + 0x40;
    p[0x16c / 4] = 0;
    *(void**)((char*)self + 0x158) = (char*)self + 0x170;
    *(void**)((char*)self + 0x15c) = (char*)self + 0x170;
    *(void**)((char*)self + 0x160) = (char*)self + 0x170 + 0x800;
    *(void**)((char*)self + 0x970) = (char*)self + 0x988;
    *(void**)((char*)self + 0x974) = (char*)self + 0x988;
    p[0x984 / 4] = 0;
    *(void**)((char*)self + 0x978) = (char*)self + 0x988 + 0x800;
    p[0x119c / 4] = 0;
    *(void**)((char*)self + 0x1188) = (char*)self + 0x11a0;
    *(void**)((char*)self + 0x118c) = (char*)self + 0x11a0;
    *(void**)((char*)self + 0x1190) = (char*)self + 0x11a0 + 0x800;
}

// ------------------------------------------------------------------ node free walk
// @ 0x00b04420
void __cdecl node_free_walk(void* self, void* node)
{
    while (node != 0) {
        node_free_walk(self, *(void**)node);
        void* next = *(void**)((char*)node + 4);
        *(uint32*)((char*)node + 0x18) = 0;
        *(uint32*)((char*)node + 0x20) = 0;
        *(uint32*)((char*)node + 0x24) = 0;
        void* a = *(void**)((char*)node + 0x28);
        if (a != 0) {
            *(uint32*)((char*)node + 0x28) = 0;
            void* vt = *(void**)a;
            (*(void(__thiscall**)(void*))(*(uint32*)vt + 4))(a);
        }
        void* b = *(void**)((char*)node + 0x2c);
        if (b != 0) {
            *(uint32*)((char*)node + 0x2c) = 0;
            void* vt = *(void**)b;
            (*(void(__thiscall**)(void*))(*(uint32*)vt + 0x38))(b);
        }
        *(uint32*)((char*)node + 0x30) = 0;
        void* c = *(void**)((char*)node + 0x2c);
        if (c != 0) {
            void* vt = *(void**)c;
            (*(void(__thiscall**)(void*))(*(uint32*)vt + 0x38))(c);
        }
        void* d = *(void**)((char*)node + 0x28);
        if (d != 0) {
            void* vt = *(void**)d;
            (*(void(__thiscall**)(void*))(*(uint32*)vt + 4))(d);
        }
        if (node >= *(void**)((char*)self + 0x20) && node < *(void**)((char*)self + 0x24)) {
            *(void**)node = *(void**)((char*)self + 0x18);
            *(void**)((char*)self + 0x18) = node;
        } else {
            FUN_00f47380(node);
        }
        node = next;
    }
}

// @ 0x00b03fd0
// Tree dump / serializer: builds a wide-string label from the tree's key text, then walks
// every node applying a per-node visitor, collapsing the "all ok" flag.
void __cdecl walk_tree_dump(void* tree, const char* label)
{
    void* first = *(void**)tree;
    int   ok    = 1;
    void* guard = 0;
    (void)guard;
    if (first != *(void**)((char*)tree + 4)) {
        FUN_00ac8050_ish(tree, label, 0);
    }
    (void)ok;
}

// @ 0x00b04120
// Same dump walk as 0x00b03fd0 but the per-node visitor receives node+8 (the payload
// rather than the header) and steps by the 0x19a8 node stride.
void __cdecl walk_tree_dump2(void* tree, const char* label)
{
    void* first = *(void**)tree;
    int   ok    = 1;
    if (first != *(void**)((char*)tree + 4)) {
        FUN_00ac8050_ish(tree, label, 0);
    }
    (void)ok;
}

// @ 0x00b04350
// Recursive release of a node chain; returns freed nodes to this+0x18 free list
// when the node lies inside the [this+0x20, this+0x24) pool, else the global delete.
void PoolOwner::release_node_chain(void* node)
{
    while (node != 0) {
        release_node_chain(*(void**)node);
        void* next = *(void**)((char*)node + 4);
        void* ref  = *(void**)((char*)node + 0x18);
        if (ref != 0)
            RefObjCall1(ref);
        if (node >= *(void**)((char*)this + 0x20) && node < *(void**)((char*)this + 0x24)) {
            *(void**)node = *(void**)((char*)this + 0x18);
            *(void**)((char*)this + 0x18) = node;
        } else {
            FUN_00f47380(node);
        }
        node = next;
    }
}

// @ 0x00b043b0
// Erase one node from the eastl::rbtree at this+4, releasing its payload, then
// return the successor through *out.
void PoolOwner::erase_tree_node(void** out, void* node)
{
    --*(int*)((char*)this + 0x14);
    void* next = FUN_00921580(node);
    FUN_00921880(node, (char*)this + 4);
    if (node >= *(void**)((char*)this + 0x20) && node < *(void**)((char*)this + 0x24)) {
        *(void**)node = *(void**)((char*)this + 0x18);
        *(void**)((char*)this + 0x18) = node;
        *out = next;
        return;
    }
    FUN_00f47380(node);
    *out = next;
}

// @ 0x00b04520
// Copy ctor for the eastl rbtree-backed container (vtable stored at dst+0).
void* PoolOwner::rbcontainer_copy(void* src)
{
    *(void**)this = (void*)0x01411b88;
    *(uint8*)((char*)this + 4) = *(uint8*)((char*)src + 4);
    FUN_00ac20d0((int)((*(char**)((char*)src + 0xc) - *(char**)((char*)src + 8)) >> 3),
                 (char*)src + 0x14);
    FUN_0076ffd0(*(void**)((char*)src + 8), *(void**)((char*)src + 0xc),
                 *(void**)((char*)this + 8), src);
    *(void**)((char*)this + 0x0c) = src;
    *(uint32*)((char*)this + 0x1c) = *(uint32*)((char*)src + 0x1c);
    *(uint32*)((char*)this + 0x20) = *(uint32*)((char*)src + 0x20);
    return this;
}

void __cdecl make_heap_range(void* first, void* last, float px, float py, float pz);
void __cdecl FUN_00b03d20(void** first, void** last, const float* pos);

// @ 0x00b04670
// Build a heap over [first,last) keyed by squared distance to pos, then pop the heap in
// order, calling the per-pop visitor with the node payload.
void __cdecl sort_and_visit(void** first, void** last, const float* pos)
{
    float px = pos[0];
    float py = pos[1];
    float pz = pos[2];
    make_heap_range(first, last, px, py, pz);
    void** it = first;
    void** hi = last;
    while (it < hi) {
        void* n = *it;
        (void)n;
        ++it;
    }
    FUN_00b03d20(first, last, pos);
}

// ------------------------------------------------------------------ distance sort
void __cdecl FUN_00b03ce0(void** first, void** last, const float* pos);
void __cdecl FUN_00b02830(void** first, int, int, int, void* v, const float* pos);
void __cdecl FUN_00b03d20(void** first, void** last, const float* pos);

// @ 0x00b04590
void __cdecl sort_by_distance(void** first, void** last, const float* pos)
{
    FUN_00b03ce0(first, last, pos);
    float px = pos[0];
    float py = pos[1];
    float pz = pos[2];
    for (void** it = last; it < first; ++it) {
        void*  n = *it;
        void*  m = *first;
        float az = pz - *(float*)((char*)n + 0x64);
        float bz = pz - *(float*)((char*)m + 0x64);
        float ax = px - *(float*)((char*)n + 0x5c);
        float bx = px - *(float*)((char*)m + 0x5c);
        float ay = py - *(float*)((char*)n + 0x60);
        float by = py - *(float*)((char*)m + 0x60);
        if (az * az + ax * ax + ay * ay < bz * bz + by * by + bx * bx) {
            *it = m;
            FUN_00b02830(first, 0, (int)((char*)last - (char*)first) >> 2, 0, n, pos);
        }
    }
    FUN_00b03d20(first, last, pos);
}
