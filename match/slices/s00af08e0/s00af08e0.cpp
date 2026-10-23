// Slice s00af08e0 — cSPUILayoutManager time-of-day lookup tables.
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "s00af08e0.h"
#include <math.h>
#include <string.h>
#include <intrin.h>
#pragma intrinsic(sqrt)

union LI { struct { u32 lo; int hi; } s; u64 q; };
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LI* li);

typedef u32 (__thiscall* VCall1)(void* self, void* arg);
typedef u32 (__thiscall* VCall0)(void* self);
typedef u8  (__thiscall* VFlag)(void* self);

bool __cdecl Lookup(void* table, u32 hash, int t, int key, float* out);

// @ 0x00af08e0 — allocate a tree node and copy the record out of src.
__declspec(noinline)
Node* __stdcall NewNode(const Node* src, void* parent)
{
    Node* n = (Node*)EAAllocate(0x20, g_allocName, 0, 0, g_allocFile, 0xd1);
    if (&n->key)
    {
        u32* d = (u32*)&n->key;
        d[0] = src->key;
        d[1] = src->t0;
        d[2] = src->t1;
        d[3] = src->v;
    }
    n->left = 0;
    n->right = 0;
    n->parent = (Node*)parent;
    n->color = src->color;
    return n;
}

// @ 0x00af0940 — lower/upper bound pair for a key.
void __thiscall RBTree::FindBounds(HIter* out, const int* key)
{
    Node* root = this->root;
    Node* lower = (Node*)&this->base;
    if (root != 0)
    {
        int k = *key;
        Node* n = root;
        do
        {
            if (k < n->key)
            {
                lower = n;
                n = n->right;
            }
            else
            {
                n = n->left;
            }
        } while (n != 0);
    }
    Node* upper = (Node*)&this->base;
    if (root != 0)
    {
        int k = *key;
        Node* n = root;
        do
        {
            if (n->key < k)
            {
                n = n->left;
            }
            else
            {
                upper = n;
                n = n->right;
            }
        } while (n != 0);
    }
    out->b = lower;
    out->a = upper;
}

// @ 0x00af09a0 — deep copy a subtree.
Node* __thiscall RBTree::Clone(Node* src, void* parent)
{
    Node* head = NewNode(src, parent);
    if (src->left != 0)
        head->left = Clone(src->left, head);
    Node* prev = head;
    for (Node* p = src->right; p != 0; p = p->right)
    {
        Node* n = (Node*)EAAllocate(0x20, g_allocName, 0, 0, g_allocFile, 0xd1);
        if (&n->key)
        {
            u32* d = (u32*)&n->key;
            d[0] = p->key;
            d[1] = p->t0;
            d[2] = p->t1;
            d[3] = p->v;
        }
        n->left = 0;
        n->right = 0;
        n->parent = prev;
        n->color = p->color;
        prev->right = n;
        if (p->left != 0)
            n->left = Clone(p->left, n);
        prev = n;
    }
    return head;
}

// @ 0x00af0a60 — probe the table for a time-of-day hit.
bool __cdecl Lookup(void* table, u32 hash, int t, int key, float* out)
{
    HashTable* t1 = (HashTable*)table;
    HIter h;
    ((XHash*)t1)->HashFind(&h, &hash);
    if ((HashNode*)h.a != t1->buckets[t1->bucketCount])
    {
        RBTree* tree = (RBTree*)((char*)(HashNode*)h.a + 4);
        tree->FindBounds(&h, &key);
        Node* n = (Node*)h.a;
        for (Node* last = (Node*)h.b; n != last; n = RBTreeInc(n))
        {
            if (t >= n->t0 && t <= n->t1)
            {
                if (out)
                    *out = *(float*)&n->v;
                return true;
            }
        }
    }
    return false;
}

// @ 0x00af0af0 — world lookup keyed by the entity's current context.
bool __thiscall LayoutMgr::LookupA(void* entity, int key, float* out)
{
    float secs = ((XTimeOfDay*)Instance())->GetSeconds(
        ((XComp*)((XComp*)entity)->Get())->GetPosition());
    float day = *(float*)((char*)Instance() + 0x24);
    float f;
    if (day > g_zero)
        f = secs / day;
    else
        f = secs * g_invDay;
    int ms = (int)((f * g_secPerDay) * g_msPerSec);
    u32 comp = ((XComp*)entity)->Get();
    u32 hash = 0x50a2c197;
    void* arch = ((XSpeciesMgr*)GetSetting9(*(u32*)(comp + 0x88), *(u32*)(comp + 0xf0)))->GetArchetype();
    if (arch != 0)
    {
        comp = ((XComp*)entity)->Get();
        u32 idx = *(u32*)(comp + 0x90);
        u32 cnt = (u32)((*(int*)((char*)arch + 0x3e0) - *(int*)((char*)arch + 0x3dc)) >> 2);
        if (idx < cnt)
            hash = *(u32*)(*(u32*)((char*)arch + 0x3dc) + idx * 4);
    }
    return Lookup(this, hash, ms, key, out);
}

// @ 0x00af0bd0 — world lookup keyed by a component flag.
bool __thiscall LayoutMgr::LookupB(void* entity, int key, float* out)
{
    u32 local[3];
    void* comp = (void*)((XComp*)entity)->GetAlt();
    u32 id = ((VCall1)(*(void***)comp)[0x58 / 4])(comp, local);
    float secs = ((XTimeOfDay*)Instance())->GetSeconds(id);
    float day = *(float*)((char*)Instance() + 0x24);
    float f;
    if (day > g_zero)
        f = secs / day;
    else
        f = secs * g_invDay;
    u8 flag = ((VFlag)(*(void***)((char*)entity + 0xc0))[0x58 / 4])((char*)entity + 0xc0);
    u32 hash = flag ? 0x2d0c5c76 : 0x20bd87a3;
    int ms = (int)((f * g_secPerDay) * g_msPerSec);
    return Lookup((HashTable*)((char*)this + 0x20), hash, ms, key, out);
}

// @ 0x00af0c90 — world lookup keyed by the time-of-day sub-object flag.
bool __thiscall LayoutMgr::LookupC(void* entity, int key, float* out)
{
    void* obj = (char*)entity + 0x120;
    u32 id = ((VCall0)(*(void***)obj)[0x2c / 4])(obj);
    float secs = ((XTimeOfDay*)Instance())->GetSeconds(id);
    float day = *(float*)((char*)Instance() + 0x24);
    float f;
    if (day > g_zero)
        f = secs / day;
    else
        f = secs * g_invDay;
    u8 flag = ((VFlag)(*(void***)obj)[0x58 / 4])(obj);
    u32 hash = flag ? 0x2d0c5c76 : 0x20bd87a3;
    int ms = (int)((f * g_secPerDay) * g_msPerSec);
    return Lookup((HashTable*)((char*)this + 0x20), hash, ms, key, out);
}

// @ 0x00af0db0 — free every bucket chain and the inner value chains.
void __thiscall HashTable::FreeChains(HashNode** buckets, u32 count)
{
    for (u32 i = 0; i < count; i++)
    {
        HashNode* n = buckets[i];
        while (n != 0)
        {
            HashNode* cur = n;
            n = n->next;
            InnerNode* p = *(InnerNode**)((char*)cur + 0x10);
            while (p != 0)
            {
                ((XClear*)((char*)cur + 4))->ClearValue(p->val);
                InnerNode* pn = p->next;
                FreeMem(p);
                p = pn;
            }
            FreeMem(cur);
        }
        buckets[i] = 0;
    }
}

// @ 0x00af0f30 — clear both tables.
void __thiscall LayoutMgr::ClearBucketChains()
{
    mbInit = 0;
    t1.FreeChains(t1.buckets, t1.bucketCount);
    t1.size = 0;
    HashTable* t2p = &t2;
    t2p->FreeChains(t2p->buckets, t2p->bucketCount);
    t2p->size = 0;
}

// @ 0x00af0f70 — fetch (creating if absent) the world record for a key.
void* __thiscall HashTable::GetOrCreate(const u32* key)
{
    HIter it;
    ((XHash*)this)->HashFind(&it, key);
    if ((HashNode*)it.a == buckets[bucketCount])
    {
        World tmp;
        RBTree* t = &tmp.tree;
        t->base = &t->base;
        t->end = &t->base;
        t->root = 0;
        t->flag = 0;
        t->size = 0;

        Pair v;
        v.key = *key;
        ((XTreeCopy*)&v.w)->CopyFrom(&tmp);
        ((XHashIns*)this)->InsertVal(&it, &v, 0);
        ((XTreeNuke*)&v.w)->Nuke(v.w.tree.root);
        ((XTreeNuke*)&tmp)->Nuke(tmp.tree.root);
    }
    return (char*)it.a + 4;
}

// @ 0x00af1020 — build both time-of-day tables from the property database.
struct PropEntry { u32 key; int idx; };
struct SrcEntry { u32 id; HashTable* tbl; };
struct VecU32 { u32* begin; u32* end; u32* cap; };

void __thiscall LayoutMgr::BuildTables()
{
    if (mbInit)
        return;
    mbInit = 1;
    void* pm = PropertyManager();
    SrcEntry src[2] = { { 0xbc20ed3a, &t1 }, { 0xcfc92e4b, &t2 } };
    PropEntry map[7] = {
        { 0x44d93bf0, 2 }, { 0x737e2d79, 0 }, { 0x43c23e71, 1 },
        { 0x45cb28e8, 3 }, { 0xa94d6d17, 4 }, { 0xf5f01a87, 5 },
        { 0x1e640af0, 6 },
    };
    void* rec = 0;
    for (int s = 0; s < 2; s++)
    {
        u32 ctx = src[s].id;
        VecU32 list = { 0, 0, 0 };
        ((bool (__thiscall*)(void*, u32, void*))(*(void***)pm)[0x48 / 4])(pm, ctx, &list);
        u32* p = list.begin;
        while (p != list.end)
        {
            u32 id = *p;
            if (rec)
            {
                ((void (__thiscall*)(void*))(*(void***)rec)[1])(rec);
                rec = 0;
            }
            if (((u8 (__thiscall*)(void*, u32, u32, void**))(*(void***)pm)[0x2c / 4])(pm, id, ctx, &rec))
            {
                World* w = (World*)src[s].tbl->GetOrCreate(&id);
                for (u32 e = 0; e < 7; e++)
                {
                    int count = 0;
                    int data = 0;
                    if (!FindProperty(rec, map[e].key, &count, &data))
                        continue;
                    if (count <= 0)
                        continue;
                    int slot = map[e].idx;
                    int off = 0;
                    for (int i = 0; i < count; i++, off += 0xc)
                    {
                        float* d = (float*)(data + off);
                        float f0 = (d[0] * g_minScale) * g_minScale2;
                        int t0 = (int)f0;
                        if (f0 < (float)t0)
                            t0--;
                        float f1 = (d[1] * g_minScale) * g_minScale2;
                        int t1 = (int)f1;
                        if (f1 < (float)t1)
                            t1--;
                        float v = d[2];
                        if (v < g_eps)
                            v = g_one;

                        RBTree* tr = &w->tree;
                        Node* base = (Node*)&tr->base;
                        Node* parent = base;
                        Node* n = tr->root;
                        int side = 0;
                        while (n)
                        {
                            parent = n;
                            n = (slot >= n->key) ? n->left : n->right;
                        }
                        if (parent != base && slot >= parent->key)
                            side = 1;
                        Node* nn = (Node*)EAAllocate(0x20, g_allocName, 0, 0, g_allocFile, 0xd1);
                        if (&nn->key)
                        {
                            nn->key = slot;
                            nn->t0 = t0;
                            nn->t1 = t1;
                            nn->v = *(u32*)&v;
                        }
                        RBTreeInsert(nn, parent, base, side);
                        tr->size++;
                    }
                }
            }
            p++;
        }
        if (list.begin && list.begin[-1])
            FreeMem(list.begin);
    }
    if (rec)
        ((void (__thiscall*)(void*))(*(void***)rec)[1])(rec);
}

// @ 0x00af13b0 — lazily create the layout-manager singleton.
void __cdecl CreateLayoutManager()
{
    LayoutMgr* cur = (LayoutMgr*)g_singleton_167ad74;
    if (cur != 0)
        return;
    LayoutMgr* m = (LayoutMgr*)EAAllocate(0x44, g_allocName, 0, 0, 0, 0);
    if (m == 0)
    {
        g_singleton_167ad74 = 0;
    }
    else
    {
        float one = g_one;
        float two = g_two;
        m->t1.f10 = one;
        m->t1.f14 = two;
        m->t1.size = 0;
        m->t1.unk18 = 0;
        m->t1.bucketCount = 1;
        m->t1.buckets = (HashNode**)0x0154df28;
        m->t2.f10 = one;
        m->t2.f14 = two;
        m->t2.size = 0;
        m->t2.unk18 = 0;
        m->t2.bucketCount = 1;
        m->t2.buckets = (HashNode**)0x0154df28;
        m->mbInit = 0;
        g_singleton_167ad74 = (u32)m;
    }
}

// @ 0x00af1430 — non-deleting destructor.
void __thiscall TimerOwner::Dtor()
{
    vtable = 0x0145c1bc;
    ((XGonzago*)timer)->Dtor();
    ((XList*)&head)->DoClear();
}

// @ 0x00af1450 — restart the timer and append a string to the list.
void __thiscall TimerOwner::Add(const void* wstr)
{
    ((XSPTimer*)timer)->Restart();
    ((XList*)&head)->DoClear();
    ListHead* h = &head;
    h->next = (ListNode*)h;
    h->prev = (ListNode*)h;
    ListNode* n = (ListNode*)EAAllocate(0x18, g_allocName, 0, 0, g_allocFile, 0xd1);
    if (&n->str)
        ((XWString*)&n->str)->Ctor(wstr);
    n->next = (ListNode*)h;
    n->prev = h->prev;
    h->prev->next = n;
    h->prev = n;
}

// @ 0x00af14b0 — constructor.
TimerOwner* __thiscall TimerOwner::Ctor()
{
    vtable = 0x0145c1bc;
    ListHead* h = &head;
    h->next = (ListNode*)h;
    h->prev = (ListNode*)h;
    ((XGonzago*)timer)->Ctor();
    g_stopwatch.SetUnits(4);
    if ((g_stopwatch.lo | g_stopwatch.hi) == 0)
    {
        if (g_stopwatch.units == 1)
        {
            u64 t = __rdtsc();
            g_stopwatch.hi = (u32)(t >> 32);
            g_stopwatch.lo = (u32)t;
            ((XSPTimer*)timer)->Start();
            return this;
        }
        LI li;
        QueryPerformanceCounter(&li);
        g_stopwatch.lo = li.s.lo;
        g_stopwatch.hi = (u32)li.s.hi;
    }
    ((XSPTimer*)timer)->Start();
    return this;
}

// @ 0x00af1540 — deleting destructor.
TimerOwner* __thiscall TimerOwner::Delete(u32 flags)
{
    vtable = 0x0145c1bc;
    ((XGonzago*)timer)->Dtor();
    ((XList*)&head)->DoClear();
    if (flags & 1)
        FreeMem(this);
    return this;
}

// @ 0x00af1570 — fill a world record.
void __cdecl InitWorld(World* dst, u32 a2, const Vec3* a3, const Vec3* a4,
                       float a5, u8 a6, const Block* blk)
{
    dst->f20 = a2;
    dst->f24 = 0;
    dst->p = *a3;
    dst->q = *a4;
    dst->f54 = a5;
    dst->flag40 = a6;
    dst->d34 = g_default34;
    dst->d38 = g_default38;
    dst->d3c = g_default3c;
    if (blk != 0)
    {
        *(Block*)dst = *blk;
    }
    else
    {
        memset(dst, 0, 0x20);
    }
}

// @ 0x00af1610 — fill a world record with the extra route points.
void __cdecl InitWorld2(World* dst, u32 a2, const Vec3* a3, const Vec3* a4,
                        const Vec3* a5, const Vec3* a6, const Vec3* a7, float a8)
{
    dst->f20 = a2;
    dst->f24 = 3;
    dst->p = *a3;
    dst->q = *a4;
    dst->f54 = a8;
    dst->r5 = *a5;
    dst->r6 = *a6;
    dst->r7 = *a7;
    dst->flag40 = 0;
    dst->d34 = g_default34;
    dst->d38 = g_default38;
    dst->d3c = g_default3c;
    dst->tree.unk00 = 0;
    dst->tree.base = 0;
    dst->tree.end = 0;
    dst->tree.root = 0;
    *(u32*)&dst->tree.flag = 0;
    dst->tree.size = 0;
    dst->tree.unk18 = 0;
    dst->gap1c = 0;
}

// @ 0x00af16f0 — ray/sphere intersection, returns the hit fraction.
bool __cdecl RaySphere(const Vec3* p, const Vec3* dir, float scale, const Vec3* center,
                       float radius, float* out)
{
    float dx = p->x - center->x;
    float dy = p->y - center->y;
    float dz = p->z - center->z;
    float b = dir->y * dy + dir->z * dz + dir->x * dx;
    float c = dx * dx + dy * dy + dz * dz - radius * radius;
    float disc = b * b - c * scale;
    if (c < 0.0f)
    {
        if (out)
            *out = 0.0f;
        return true;
    }
    if (disc < 0.0f)
        return false;
    float s = (float)sqrt(disc);
    float t = -b - s;
    if (s - b < 0.0f)
        return false;
    if (t > scale)
        return false;
    if (out)
    {
        if (t > 0.0f)
            *out = t / scale;
        else
            *out = 0.0f;
    }
    return true;
}

// @ 0x00af17f0 — sweep a sphere along a segment and build the world record.
bool __cdecl SweepWorld(World* dst, u32 id, const Vec3* origin, const Vec3* center,
                        const Vec3* dir, Vec3* tvec, float scale, float radius,
                        u8 flag, const Block* blk)
{
    Vec3 local;
    float t = tvec->x;
    local.x = dir->x * t;
    local.y = dir->y * t;
    local.z = dir->z * t;
    float hit;
    if (RaySphere(origin, &local, t * t, center, radius, &hit))
    {
        if (hit != 0.0f || flag)
        {
            float nt = (tvec->x * hit) * scale;
            tvec->x = nt;
            local.x = dir->x * nt + origin->x;
            local.y = dir->y * nt + origin->y;
            local.z = dir->z * nt + origin->z;
            InitWorld(dst, id, center, &local, radius, flag, blk);
            return true;
        }
    }
    return false;
}
