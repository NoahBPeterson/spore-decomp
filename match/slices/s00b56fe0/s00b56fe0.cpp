// s00b56fe0 : build a constraint between two physics entities (type pair dispatch)
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

struct __declspec(align(16)) V4 {
    float x, y, z, w;
    V4() {}
    void set(const V4& o) { x = o.x; y = o.y; z = o.z; w = o.w; }
};

struct Motion {
    char pad0[0x40];
    V4 rot;           // +0x40
    char pad1[0xd0 - 0x50];
    V4 vec;           // +0xd0
    float getMass() const; // 0x01088270
};

struct ListNode { ListNode* end; };

struct PropPair { int v; int w; };

struct Ent {
    char pad0[0xc];
    void* handle;       // +0x0c
    char pad1[0x4c - 0x10];
    int propBase;       // +0x4c (array, 16-byte entries)
    int propCount;      // +0x50
    char pad2[0x58 - 0x54];
    Motion* motion;     // +0x58
    PropPair* getProp(PropPair* out, int id); // 0x00496140
};

struct Pair { Ent* a; Ent* b; };

struct Src {
    char pad0[0xc];
    char* list;         // +0x0c
    struct { char pad[0xe]; uint8_t strength; }* info; // +0x10
};

extern const float kOne; // 0x01485720
extern const float kMinusOne; // 0x013eb1bc
extern const float kStrengthScale; // 0x0146150c

float BuildAnchor(const V4* q, float scale, const V4* v, float mass, V4* out); // 0x00b4d670
void  Reject(const V4* q); // 0x00b4da40
void  AddA(void* h, int which, int flag, const V4* q); // 0x00b4e820
void  AddB(void* h0, void* h1, int prop, int which, int flag, const V4* q); // 0x00b4e980
void  AddC(void* h0, void* h1, int flag, const V4* q); // 0x00b4ead0

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
static inline float Len3(const V4* v)
{
    double s = (double)v->z * v->z;
    s += (double)v->y * v->y;
    s += (double)v->x * v->x;
    return (float)sqrt(s);
}

struct Work {
    V4 q;             // 0x20
    V4 q2;            // 0x30
    V4 vecA;          // 0x40
    V4 vecB;          // 0x50
    V4 rotA;          // 0x60
    V4 rotB;          // 0x70
    float massA, massB, scale;
    bool fa, fb;
    float res;
    float pad[3];
    V4 out0;
    V4 out1;
    float len;
};

void __stdcall BuildConstraint(Pair* p, unsigned flag, Src* src)
{
    Ent* a = p->a;
    Ent* b = p->b;
    if (!b || !a) return;
    Work w;
    V4 neg;
    PropPair t1;
    w.scale = kOne;
    w.res = 0.0f;
    Motion* ma = a->motion;
    Motion* mb = b->motion;
    w.vecA.set(ma->vec);
    w.vecB.set(mb->vec);
    w.massA = a->motion->getMass();
    w.massB = b->motion->getMass();
    w.rotA.set(a->motion->rot);
    w.rotB.set(b->motion->rot);
    PropPair* r;
    r = a->getProp(&t1, 9);
    w.fa = r->v != 0;
    r = b->getProp(&t1, 9);
    w.fb = r->v != 0;
    if ((char)flag != 0 && src != 0) {
        ListNode* n = (ListNode*)src->list;
        if (((int)((char*)n->end - (char*)n) - 0x30) / 0x30 > 0) {
            V4* e = (V4*)((char*)n + 0x30);
            w.q.set(e[1]);
            w.q2.set(e[0]);
            w.scale = (float)src->info->strength * kStrengthScale;
        } else {
            *(char*)&flag = 0;
        }
    }
    PropPair* ta = a->getProp(&t1, 0);
    PropPair* tb = b->getProp((PropPair*)&neg, 0);
    int typeB = tb->v;
    int typeA = ta->v;
    switch (typeA) {
    case 1:
        if (typeB == 3) {
            if ((char)flag) {
                neg.x = w.q.x * kMinusOne; neg.y = w.q.y * kMinusOne; neg.z = w.q.z * kMinusOne; neg.w = w.q.w * kMinusOne;
                w.res = BuildAnchor(&neg, w.scale, &w.vecB, w.massB, &w.out1);
                w.len = Len3(&w.vecB);
            }
            AddA(b->handle, 0, flag, &w.q);
        }
        break;
    case 2:
        if (typeB == 3) {
            if ((char)flag) {
                neg.x = w.q.x * kMinusOne; neg.y = w.q.y * kMinusOne; neg.z = w.q.z * kMinusOne; neg.w = w.q.w * kMinusOne;
                w.res = BuildAnchor(&neg, w.scale, &w.vecB, w.massB, &w.out1);
                w.len = Len3(&w.vecB);
            }
            PropPair* pr = a->getProp(&t1, 5);
            AddB(b->handle, a->handle, pr->v, 0, flag, &w.q);
            return;
        }
        break;
    case 3:
        switch (typeB) {
        case 1:
            if ((char)flag) {
                w.res = BuildAnchor(&w.q, w.scale, &w.vecA, w.massA, &w.out0);
                w.len = Len3(&w.vecA);
            }
            AddA(a->handle, 1, flag, &w.q);
            return;
        case 2:
            if ((char)flag) {
                w.res = BuildAnchor(&w.q, w.scale, &w.vecA, w.massA, &w.out0);
                w.len = Len3(&w.vecA);
            }
            {
                PropPair* pr = b->getProp((PropPair*)&neg, 5);
                AddB(a->handle, b->handle, pr->v, 1, flag, &w.q);
            }
            return;
        case 3:
            if ((char)flag) {
                if (w.massB == 0.0f) {
                    w.res = BuildAnchor(&w.q, w.scale, &w.vecA, w.massA, &w.out0);
                    w.len = Len3(&w.vecA);
                } else if (w.massA == 0.0f) {
                    neg.x = w.q.x * kMinusOne; neg.y = w.q.y * kMinusOne; neg.z = w.q.z * kMinusOne; neg.w = w.q.w * kMinusOne;
                    w.res = BuildAnchor(&neg, w.scale, &w.vecB, w.massB, &w.out1);
                    w.len = Len3(&w.vecB);
                } else {
                    Reject(&w.q);
                }
            }
            AddC(a->handle, b->handle, flag, &w.q);
            return;
        }
        break;
    }
}

// ---------------------------------------------------------------------------
// Havok container helpers around 0x00b57680..0x00b57bf0.
// ---------------------------------------------------------------------------

struct HkRelativePtr {
    char m_pad00[0xc];
    HkRelativePtr* m_next;  // +0xc
    int m_offset;           // +0x10
    char m_pad14[0x4];
    uint8_t m_isRelative;   // +0x18
};

struct HkPtrPair {
    HkRelativePtr* m_first;   // +0x0
    HkRelativePtr* m_second;  // +0x4
    char m_pad08[0x14];
    uint32_t m_flag;          // +0x1c
};

static inline void* ResolveHkPtr(HkRelativePtr* p)
{
    if (p->m_isRelative == 1)
        return (char*)p + p->m_offset;
    return 0;
}

struct HkPtrConverter {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14(void** out, int count, HkPtrPair* pair);
    void Convert(HkPtrPair* pair);
};

// @ 0x00b57680
void HkPtrConverter::Convert(HkPtrPair* pair)
{
    void* first = ResolveHkPtr(pair->m_first);
    void* second = ResolveHkPtr(pair->m_second);
    void* local[2];
    local[0] = first;
    local[1] = second;
    v14(local, 1, pair);
}

void* __cdecl opnew_f473a0(void* allocator, const char* name, int a, int b,
                           const char* file, unsigned size);  // 0x00f473a0
void __cdecl opdel_f47380(void* p);                          // 0x00f47380

struct HkNodeData {
    uint32_t m_a;   // +0x0
    uint32_t m_b;   // +0x4
    uint32_t m_c;   // +0x8
};

struct HkPoolNode {
    union {
        HkPoolNode* m_next;  // +0x0 (free-list link)
        uint32_t m_a;        // +0x0 (payload copy)
    };
    uint32_t m_b;            // +0x4
    uint32_t m_c;            // +0x8
    uint32_t m_flags;        // +0xc
    char m_tail[0xd1 - 0x10];
};

struct HkNodePool {
    char m_pad00[0x1c];
    HkPoolNode* m_freeList;  // +0x1c
    char m_pad20[0xc];
    void* m_allocator;       // +0x2c
    void __thiscall AddNode(const HkNodeData* data);
};

// @ 0x00b576d0
void HkNodePool::AddNode(const HkNodeData* data)
{
    HkPoolNode* node = m_freeList;
    if (node != 0)
        m_freeList = node->m_next;
    else {
        void* allocator = m_allocator;
        node = (HkPoolNode*)opnew_f473a0(allocator, "Simulator", 0, 0,
                                         (const char*)0x013ebb38, 0xd1);
    }
    if (node != 0) {
        node->m_a = data->m_a;
        node->m_b = data->m_b;
        node->m_c = data->m_c;
    }
    node->m_flags = 0;
}

struct AllocVec {
    void* m_allocator;     // +0x00
    void* m_begin;         // +0x04
    uint32_t m_capacity;   // +0x08
    uint32_t m_size;       // +0x0c
    char m_pad10[0xc];
    void* m_freeList;      // +0x1c
    char m_pad20[0x4];
    void* m_poolBegin;     // +0x24
    void* m_poolEnd;       // +0x28
    char m_pad2c[0x4];
    void* m_empty;         // +0x30

    void __thiscall Deallocate(void* begin, uint32_t capacity);  // 0x00a42fe0
    void Clear();
};

void AllocVec::Clear()
{
    Deallocate(m_begin, m_capacity);
    void* p = m_begin;
    m_size = 0;
    if (m_capacity > 1 && p != m_empty) {
        if (p >= m_poolBegin && p < m_poolEnd) {
            *(void**)p = m_freeList;
            m_freeList = p;
        } else {
            opdel_f47380(p);
        }
    }
}

struct HkContainerOwner {
    void* m_vptr;          // +0x00
    AllocVec m_vec2;       // +0x04
    char m_gap[0x1858 - 0x04 - sizeof(AllocVec)];
    AllocVec m_vec1;       // +0x1858
    void Destroy();
};

// @ 0x00b57720
void HkContainerOwner::Destroy()
{
    m_vec1.Clear();
    m_vec2.Clear();
    m_vptr = (void*)0x013f8990;
}

struct HkValueRange {
    uint32_t m_lo;  // +0x0
    uint32_t m_hi;  // +0x4
};

struct HkRangeSource {
    char m_pad00[0x8];
    uint32_t m_lo;  // +0x8
    uint32_t m_hi;  // +0xc
};

struct HkRefMap {
    char m_pad00[0x34];
    uint32_t* FindRef(HkValueRange* range);  // 0x00b577d0
    void Erase(HkValueRange* range);         // 0x00b51c20
};

struct HkRefOwner {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14(HkValueRange* range, int a, int b);
    HkRefMap m_map;    // +0x04
    void Remove(HkRangeSource* range);
};

// @ 0x00b579b0
void HkRefOwner::Remove(HkRangeSource* range)
{
    uint32_t lo = range->m_lo;
    uint32_t hi = range->m_hi;
    if (hi < lo) {
        uint32_t t = lo;
        lo = hi;
        hi = t;
    }
    HkValueRange key;
    key.m_lo = lo;
    key.m_hi = hi;
    uint32_t* ref = m_map.FindRef(&key);
    *ref -= 1;
    int count = (int)*ref;
    if (count == 0) {
        v14(&key, 0, 0);
        m_map.Erase(&key);
        return;
    }
    if (count < 0) {
        *ref = 0;
        m_map.Erase(&key);
    }
}

uint32_t g_167ecdc;  // 0x0167ecdc
void* __cdecl FUN_00b53940(void* obj);  // 0x00b53940

struct HkWorld {
    void AddPair(void* a, void* b, float t);  // 0x00b54b40
    void RemovePhantom(void* phantom);        // 0x01083400
};

struct HkPhantom {
    char m_pad00[0x8];
    HkWorld* m_world;  // +0x8
};

// @ 0x00b57bf0
void __cdecl FUN_00b57bf0(void* a, void* b, float t)
{
    if (g_167ecdc == 0)
        return;
    void* ra = FUN_00b53940(a);
    void* rb = FUN_00b53940(b);
    if (ra != 0 && rb != 0)
        ((HkWorld*)g_167ecdc)->AddPair(ra, rb, t);
}

struct HkHashIter {
    void* m_node;    // +0x0
    void* m_bucket;  // +0x4
};

struct HkHashTable {
    void* m_allocator;       // +0x00
    void** m_buckets;        // +0x04
    uint32_t m_bucketCount;  // +0x08
    uint32_t m_size;         // +0x0c
    char m_pad10[0xc];
    void* m_freeList;        // +0x1c
    char m_pad20[0x4];
    void* m_poolBegin;       // +0x24
    void* m_poolEnd;         // +0x28
    char m_pad2c[0x4];
    void* m_empty;           // +0x30

    uint32_t* FindRef(HkValueRange* key);                  // 0x00b577d0
    HkHashIter* Find(HkHashIter* out, HkValueRange* key);   // 0x00b51bb0
    void Erase(HkValueRange* key);                          // 0x00b51c20
    void Begin(HkHashIter* out);                            // 0x00594410
    void DoFreeNodes(void** buckets, uint32_t count);       // 0x00a1b6c0
};

struct HkBody {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void* v20();  // +0x20

    char m_pad04[0x8];
    void* m_handle;       // +0x0c
    char m_pad10[0x88 - 0x10];
    uint32_t m_field88;   // +0x88

    PropPair* getProp(PropPair* out, int key);  // 0x00496140
};

struct HkSelectOwner {
    char m_pad00[0x4];
    HkRefMap m_refs;      // +0x04
    char m_gap[0x1858 - 0x4 - sizeof(HkRefMap)];
    HkHashTable m_table;  // +0x1858
    void Select(HkPtrPair* pair);
};

void* g_18c6de8 = 0;  // 0x018c6de8

// @ 0x00b57840
void HkSelectOwner::Select(HkPtrPair* pair)
{
    HkRelativePtr* firstNode = pair->m_first;
    HkRelativePtr* firstRoot = firstNode;
    for (HkRelativePtr* n = firstNode->m_next; n != 0; n = n->m_next)
        firstRoot = n;
    HkBody* a = (HkBody*)ResolveHkPtr(firstRoot);

    HkRelativePtr* secondNode = pair->m_second;
    HkRelativePtr* secondRoot = secondNode;
    for (HkRelativePtr* n = secondNode->m_next; n != 0; n = n->m_next)
        secondRoot = n;
    HkBody* b = (HkBody*)ResolveHkPtr(secondRoot);

    if ((uint32_t)b < (uint32_t)a) {
        HkBody* t = a;
        a = b;
        b = t;
    }

    HkValueRange key;
    key.m_lo = (uint32_t)a;
    key.m_hi = (uint32_t)b;

    uint32_t* ref = m_refs.FindRef(&key);
    ++*ref;

    void* endNode = m_table.m_buckets[m_table.m_bucketCount];
    HkHashIter it;
    m_table.Find(&it, &key);
    if (it.m_node != endNode) {
        pair->m_flag = 1;
        return;
    }

    void* handleA = a->m_handle;
    if (handleA == 0)
        return;
    void* handleB = b->m_handle;
    if (handleB == 0)
        return;

    PropPair pa;
    PropPair pb;
    int typeA = a->getProp(&pa, 0)->v;
    int typeB = b->getProp(&pb, 0)->v;

    HkBody* a3 = 0;
    HkBody* a2 = 0;
    HkBody* b3 = 0;
    HkBody* b2 = 0;
    if (typeA == 3)
        a3 = a;
    else if (typeA == 2)
        a2 = a;
    if (typeB == 3)
        b3 = b;
    else if (typeB == 2)
        b2 = b;

    HkBody* chosen;
    if (a3 != 0 && a3->v20() == &g_18c6de8) {
        chosen = b2;
    } else if (b3 != 0 && b3->v20() == &g_18c6de8) {
        chosen = a2;
    } else {
        return;
    }

    if (chosen == 0)
        return;
    if (chosen->m_field88 - 1 > 1)
        return;
    pair->m_flag = 1;
}

struct HkStyleNode {
    uint32_t m_key;      // +0x0
    void* m_value;       // +0x4
    HkStyleNode* m_next; // +0x8
};

struct HkGlobalHash {
    char m_pad00[0x4];
    void** m_buckets;        // +0x4
    uint32_t m_bucketCount;  // +0x8
    uint32_t m_size;         // +0xc

    void Begin(HkHashIter* out);                       // 0x00594410
    void DoFreeNodes(void** buckets, uint32_t count);  // 0x00a1b6c0
};

struct HkPtrVector {
    void** m_begin;  // +0x0
    void** m_end;    // +0x4
    void** m_cap;    // +0x8
};

struct HkRBTree {
    char m_pad00[0x4];
    void* m_sentinel;   // +0x4
    void* m_sentinel2;  // +0x8
    void* m_root;       // +0xc
    uint32_t m_size;    // +0x10
    uint32_t m_flag;    // +0x14
    uint32_t m_field18; // +0x18
    void DoNukeSubtree(void* root);  // 0x00d3b370
};

struct HkGameSystem {
    char m_pad00[0x20];
    int m_field20;  // +0x20
};

HkGlobalHash g_1683e98;  // 0x01683e98
HkPtrVector g_1569b68;   // 0x01569b68
HkRBTree g_1686738;      // 0x01686738
HkPtrVector g_1569c00;   // 0x01569c00
uint32_t g_167ecd0;      // 0x0167ecd0
uint8_t g_167ecdb;       // 0x0167ecdb

void* __cdecl FUN_00b3d310();                        // 0x00b3d310
void __cdecl FUN_01083110(void* temp, void* value);  // 0x01083110
void* __cdecl memcpy(void* dst, const void* src, unsigned size);

// @ 0x00b57a50
void __cdecl FUN_00b57a50()
{
    HkGameSystem* sys = (HkGameSystem*)FUN_00b3d310();
    if (sys->m_field20 != 0 || g_167ecd0 == 0)
        return;

    HkHashIter it;
    g_1683e98.Begin(&it);
    HkStyleNode* endNode =
        (HkStyleNode*)g_1683e98.m_buckets[g_1683e98.m_bucketCount];
    HkStyleNode* node = (HkStyleNode*)it.m_node;
    uint8_t temp;
    while (node != endNode) {
        if (node->m_value != 0)
            FUN_01083110(&temp, node->m_value);
        node->m_value = 0;
        node = node->m_next;
        while (node == 0) {
            it.m_bucket = (char*)it.m_bucket + 4;
            node = *(HkStyleNode**)it.m_bucket;
        }
    }

    g_1683e98.DoFreeNodes(g_1683e98.m_buckets, g_1683e98.m_bucketCount);
    g_1683e98.m_size = 0;

    for (void** p = g_1569b68.m_begin; p != g_1569b68.m_end; ++p) {
        if (*p != 0)
            FUN_01083110(&temp, *p);
    }
    g_1569b68.m_end = g_1569b68.m_begin;

    g_1686738.DoNukeSubtree(g_1686738.m_root);
    g_1686738.m_sentinel = &g_1686738.m_sentinel;
    g_1686738.m_sentinel2 = &g_1686738.m_sentinel;
    g_1686738.m_root = 0;
    g_1686738.m_size = 0;
    g_1686738.m_flag = 0;
    g_1686738.m_field18 = 0;

    for (void** p = g_1569c00.m_begin; p != g_1569c00.m_end; ++p) {
        HkPhantom* phantom = (HkPhantom*)*p;
        if (phantom != 0)
            phantom->m_world->RemovePhantom(phantom);
    }
    g_1569c00.m_end = g_1569c00.m_begin;
    g_167ecdb = 0;
}
