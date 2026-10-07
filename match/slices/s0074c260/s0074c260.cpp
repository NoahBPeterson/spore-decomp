// Slice s0074c260: cModelWorld draw/occluder helpers (~0x0074c260-0x0074d2c0).
// /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "../../include/types.h"

extern "C" void* __cdecl memmove_(void* dst, const void* src, unsigned size);

// ---------------------------------------------------------------------------
// @ 0x0074CA70  vector<int>::remove_first / erase-by-value
// ---------------------------------------------------------------------------
struct VecInt {
    char pad0[0x4c];
    int* begin;   // +0x4c
    int* end;     // +0x50
    bool remove_first(int v);
};

bool VecInt::remove_first(int v)
{
    int n = (int)((char*)end - (char*)begin) >> 2;
    if (n > 0) {
        int i = 0;
        int* p = begin;
        do {
            if (*p == v) {
                int* dst = begin + i;
                int* src = dst + 1;
                if (src < end)
                    memmove_(dst, src, (unsigned)((char*)end - (char*)src));
                end = (int*)((char*)end - 4);
                return true;
            }
            ++i;
            ++p;
        } while (i < n);
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0074CDD0  vector<E18>::push_back (element 0x18)
// ---------------------------------------------------------------------------
struct E18 {
    float a, b, c, d, e, f;
    E18& operator=(const E18& o) { a = o.a; b = o.b; c = o.c; d = o.d; e = o.e; f = o.f; return *this; }
};
struct E18Vt {
    void DoInsert(E18* pos, const E18* v);   // 0074c020
};
struct Vec18 {
    E18* begin;   // +0x00
    E18* end;     // +0x04
    E18* cap;     // +0x08
    void push_back(const E18* v);
};

void Vec18::push_back(const E18* v)
{
    E18* e = end;
    if (e < cap) {
        end = e + 1;
        if (e)
            *e = *v;
    } else {
        ((E18Vt*)this)->DoInsert(e, v);
    }
}

// ---------------------------------------------------------------------------
// EASTL quick_sort_impl / get_partition / median, literal EASTL shapes
// ---------------------------------------------------------------------------
namespace eastl {

template <typename T> struct iterator_traits;
template <typename T> struct iterator_traits<T*> { typedef T value_type; };

template <typename It, typename Compare>
void partial_sort(It first, It middle, It last, Compare compare);   // out of line elsewhere

template <typename It, typename Compare>
inline It median(It a, It b, It c, Compare compare)
{
    if (compare(*a, *b)) {
        if (compare(*b, *c)) return b;
        else if (compare(*a, *c)) return c;
        else return a;
    } else if (compare(*a, *c)) return a;
    else if (compare(*b, *c)) return c;
    return b;
}

template <typename It, typename T, typename Compare>
It get_partition(It first, It last, T pivotValue, Compare compare)
{
    for (;; ++first) {
        while (compare(*first, pivotValue)) ++first;
        --last;
        while (compare(pivotValue, *last)) --last;
        if (first >= last) return first;
        T temp(*first);
        *first = *last;
        *last = temp;
    }
}

template <typename It, typename Size, typename Compare>
void quick_sort_impl(It first, It last, Size kRecursionCount, Compare compare)
{
    typedef typename iterator_traits<It>::value_type value_type;
    while ((last - first) > 28 && (kRecursionCount > 0)) {
        const It position_partition(eastl::get_partition(first, last, *eastl::median(first, first + (last - first) / 2, last - 1, compare), compare));
        eastl::quick_sort_impl(position_partition, last, --kRecursionCount, compare);
        last = position_partition;
    }
    if (kRecursionCount == 0)
        eastl::partial_sort(first, last, last, compare);
}

}  // namespace eastl

// 8-byte draw-model record sorted by a float key at +4.
struct cDrawModelInfo { void* p; float key; };
struct DrawGreater { int pad; bool operator()(const cDrawModelInfo& a, const cDrawModelInfo& b) const { return a.key > b.key; } };
struct cAlphaSortLessComparator { int pad; bool operator()(const cDrawModelInfo& a, const cDrawModelInfo& b) const { return a.key < b.key; } };

// @ 0x0074C260  quick_sort_impl<cDrawModelInfo*>  (descending by key)
template void eastl::quick_sort_impl<cDrawModelInfo*, int, DrawGreater>(cDrawModelInfo*, cDrawModelInfo*, int, DrawGreater);

// @ 0x0074C370  quick_sort_impl<cDrawModelInfo*,int,cAlphaSortLessComparator>  (ascending by key)
template void eastl::quick_sort_impl<cDrawModelInfo*, int, cAlphaSortLessComparator>(cDrawModelInfo*, cDrawModelInfo*, int, cAlphaSortLessComparator);

// ---------------------------------------------------------------------------
// cOccluder sorts (0x18-byte records, function-pointer comparator)
// ---------------------------------------------------------------------------
struct cOccluder {
    float f[6];
    cOccluder() {}
    cOccluder(const cOccluder& o) { f[0] = o.f[0]; f[1] = o.f[1]; f[2] = o.f[2]; f[3] = o.f[3]; f[4] = o.f[4]; f[5] = o.f[5]; }
};
typedef bool (__cdecl *OccCmp)(const cOccluder&, const cOccluder&);

// @ 0x0074C580  eastl::get_partition<cOccluder*,cOccluder,bool(*)(const cOccluder&,const cOccluder&)>
template cOccluder* eastl::get_partition<cOccluder*, cOccluder, OccCmp>(cOccluder*, cOccluder*, cOccluder, OccCmp);

// @ 0x0074D190  eastl::quick_sort_impl<cOccluder*,int,bool(*)(...)>
template void eastl::quick_sort_impl<cOccluder*, int, OccCmp>(cOccluder*, cOccluder*, int, OccCmp);

// ---------------------------------------------------------------------------
// cModelWorld
// ---------------------------------------------------------------------------
struct RefCounted { virtual void AddRef(); virtual void Release(); };
struct ModelKey { uint32_t inst, type, group; };

struct PropListW { bool GetDescription(uint32_t hash); };
extern PropListW* g_appProps;   // 0x15fd918
bool __cdecl GetPropertyAsKey(void* props, uint32_t id, ModelKey* out);   // 0x6a1250

#define V(n) virtual void v##n();
// resource manager slots used here: 0x0c, 0x14, 0x38, 0x58
struct ResMgrW {
    V(0) V(1) V(2)
    virtual bool Lookup0c(ModelKey* key, RefCounted** out, int a, int b, int c, int d);   // 0x0c
    V(4)
    virtual bool Find14(ModelKey* key, RefCounted** out);                                  // 0x14
    V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13)
    virtual void Notify38(uint32_t a, uint32_t b);                                         // 0x38
    V(15) V(16) V(17) V(18) V(19) V(20) V(21)
    virtual int Error58(ModelKey* key);                                                    // 0x58
};
ResMgrW* __cdecl GetResMgrW();    // 0x67dcd0
ResMgrW* __cdecl GetResMgrW2();   // 0x67dd60

// scratch vector with a 32-entry inline buffer (cookie word before the buffer is 0 while inline)
struct TmpVec {
    uint32_t* b; uint32_t* e; void* owner; uint32_t pad[3]; uint32_t prefix; uint32_t buf[32];
    TmpVec() : b(buf), e(buf), owner(0), prefix(0) {}
};
struct RefHolder { RefCounted* p; RefHolder() : p(0) {} ~RefHolder() { if (p) p->Release(); } };
struct ResW : RefCounted { };
void __cdecl FillResourceList(RefCounted* res, TmpVec* out, void* fn);   // 0x7141e0
void __fastcall DestructRange(TmpVec* v, int, uint32_t* b, uint32_t* e); // 0x70f520
extern "C" void __cdecl OpDeleteArr(void* p);   // 0xf47380
extern char g_fn743910[];

struct cModelInstance;
struct LoadReq {
    uint32_t key; RefCounted* model; uint32_t a4, a5, idx, z0, z1;
    ~LoadReq() { if (model) model->Release(); }
};
struct LoadQueue {
    uint32_t d;
    void Push(LoadReq* r);           // 0x74bda0
    void Remove(uint32_t* pkey);     // 0x74be40
};
struct ModelEntry {
    char pad0[8]; uint32_t key; uint32_t flags0; char pad10[0x128]; int idx;   // flags at +0xc, idx at +0x138
};

struct cModelWorld {
    char pad0[0x314];
    LoadQueue queue;            // +0x314
    uint32_t active[8][0x14];   // +0x318, stride 0x50 (first dword compared)
    bool ModelIsResidentInMemory(RefCounted* model);
    void __stdcall UpdateFromPropList(RefCounted* model, ModelEntry* entry, int idx, int z);   // 0x74b760 (free in orig)
    void ScheduleForLoad(ModelEntry* entry, RefCounted* model, uint32_t a4, uint32_t a5);
    void Load74a920(RefCounted* model, ModelEntry* entry, int idx);   // 0x74a920
};
void __stdcall UpdateFromPropList(RefCounted* model, ModelEntry* entry, int idx, int z);

// @ 0x0074C670  SP::cModelWorld::ModelIsResidentInMemory
bool cModelWorld::ModelIsResidentInMemory(RefCounted* model)
{
    if (!g_appProps->GetDescription(0x69089a6))
        return false;
    if (model == 0)
        return false;
    ResMgrW* mgr = GetResMgrW();
    int i = 0;
    do {
        ModelKey k = { 0, 0, 0 };
        if (!GetPropertyAsKey(model, 0xf9efbb + i, &k)) {
            if (i == 0)
                return false;
            break;
        }
        RefHolder res;
        k.type = 0xe6bce5;
        if (!mgr->Find14(&k, &res.p) && mgr->Error58(&k) != 0)
            return false;
        if (res.p == 0) {
            k.type = 0x2f4e681b;
            if (!mgr->Find14(&k, 0) && mgr->Error58(&k) != 0)
                return false;
        } else {
            TmpVec v;
            FillResourceList(res.p, &v, g_fn743910);
            if (v.b != v.e) {
                DestructRange(&v, 0, v.b, v.e);
                if (v.b != 0 && v.b[-1] != 0)
                    OpDeleteArr(v.b);
                return false;
            }
            DestructRange(&v, 0, v.b, v.e);
            if (v.b != 0 && v.b[-1] != 0)
                OpDeleteArr(v.b);
        }
        ++i;
    } while (i < 4);

    ModelKey k2 = { 0, 0, 0 };
    if (GetPropertyAsKey(model, 0xf9efc0, &k2)) {
        k2.type = 0xe6bce5;
        if (!mgr->Find14(&k2, 0) && mgr->Error58(&k2) != 0)
            return false;
        k2.type = 0x2f4e681b;
        if (!mgr->Find14(&k2, 0)) {
            if (mgr->Error58(&k2) != 0)
                return false;
        }
    }
    return true;
}

// @ 0x0074C910  SP::cModelWorld::ScheduleForLoad
void cModelWorld::ScheduleForLoad(ModelEntry* entry, RefCounted* model, uint32_t a4, uint32_t a5)
{
    entry->flags0 &= 0xffffbfff;
    if (entry->idx >= 0)
        UpdateFromPropList(model, entry, entry->idx, 0);
    uint32_t* key = &entry->key;
    bool found;
    {
        uint32_t i = 0;
        uint32_t* p = &active[0][0];
        for (;;) {
            if ((uint32_t*)*p == key) { found = true; break; }
            ++i;
            p += 0x14;
            if (i >= 8) { found = false; break; }
        }
    }
    bool propOn = g_appProps->GetDescription(0x3dd1848d);
    bool resident = ModelIsResidentInMemory(model);
    if (!propOn || (!found && resident)) {
        uint32_t* kk = key;
        queue.Remove(kk ? (uint32_t*)&kk : 0);
        Load74a920(model, entry, entry->idx);
    } else {
        LoadReq r;
        r.key = (uint32_t)key;
        r.model = model;
        if (model) model->AddRef();
        r.a4 = a4;
        r.a5 = a5;
        r.idx = entry->idx;
        r.z0 = 0;
        r.z1 = 0;
        queue.Push(&r);
    }
}

// ---------------------------------------------------------------------------
// @ 0x0074CAD0  per-model load job step (state machine over +0x2c)
// ---------------------------------------------------------------------------
struct JobW { char pad[0x20]; RefCounted* res; };
struct cJobW {
    void Wait();        // 0x6926b0
    void GetStatus();   // 0x690120
    void Run6913c0(struct JobW* j);              // 0x6913c0
    bool Continuation(void* fn, void* arg);      // 0x68f9f0
};
extern char g_fn74d080[];   // 0x74d080
struct ResListW { void Fill(TmpVec* out, void* fn); };   // 0x73bd60 (thiscall on the resource)
struct PropOwner { char pad[0x10]; uint32_t flags; };
extern bool __cdecl GetPropertyAsKeyP(void* props, uint32_t id, ModelKey* out);
void __cdecl FUN_00756790(JobW** job, uint32_t inst, uint32_t grp, uint32_t flags);
struct LoadJob {
    uint32_t pad0;
    PropOwner* props;      // +0x04
    uint32_t pad8;
    uint32_t grp;          // +0x0c
    uint32_t flags;        // +0x10
    char pad14[0x10];
    uint32_t userArg;      // +0x24
    char pad28[4];
    int state;             // +0x2c
    JobW* job;             // +0x30
    RefCounted* refs[6];   // +0x34
    uint32_t count;        // +0x4c (overlaps refs end; see original)
    bool Step(cJobW* cj);
};
bool LoadJob::Step(cJobW* cj)
{
    if (state == 6) {
        state = 0;
        count = 1;
    } else {
        RefCounted* r;
        if (job == 0) {
            r = 0;
        } else {
            ((cJobW*)job)->Wait();
            r = job->res;
        }
        ResMgrW* mgr = GetResMgrW2();
        RefCounted* old = refs[state];
        if (r != old) {
            if (r) ((uint32_t*)r)[1]++;
            refs[state] = r;
            if (old) {
                int n = ((int*)old)[1] - 1;
                ((int*)old)[1] = n;
                if (n == 0) {
                    ((int*)old)[1] = 1;
                    old->Release();
                }
            }
        }
        if (r) {
            TmpVec v;
            ((ResListW*)r)->Fill(&v, g_fn743910);
            uint32_t* p = v.b;
            if (p != v.e) {
                do {
                    mgr->Notify38(*p, userArg);
                    ++p;
                } while (p != v.e);
            }
            DestructRange(&v, 0, v.b, v.e);
            if (v.b != 0 && v.b[-1] != 0)
                OpDeleteArr(v.b);
        }
        ++state;
    }
    JobW** pj = &job;
    if (*pj != 0) {
        cJobW* oj = (cJobW*)*pj;
        *pj = 0;
        oj->GetStatus();
    }
    if (state == 6)
        return true;
    ModelKey k = { 0, 0, 0 };
    uint32_t sz;
    uint32_t fl;
    if (state == 0) {
        if (GetPropertyAsKey(props, 0xf9efbb, &k)) {
            sz = k.group;
            if (sz == 0xffffffff) sz = grp;
            fl = flags;
            FUN_00756790(pj, k.inst, sz, fl);
        }
    } else if (state == 4) {
        if ((flags & 0x20) && props && GetPropertyAsKey(props, 0xf9efc1, &k)) {
            sz = k.group;
            if (sz == 0xffffffff) sz = props->flags;
            fl = flags;
            FUN_00756790(pj, k.inst, sz, fl);
        }
    } else if (state == 5) {
        if (GetPropertyAsKey(props, 0xf9efc0, &k)) {
            fl = 0;
            sz = -(uint32_t)(k.group != 0xffffffff) & k.group;
            FUN_00756790(pj, k.inst, sz, fl);
        }
    } else {
        if (!GetPropertyAsKey(props, state + 0xf9efbb, &k)) {
            state = 3;
        } else {
            sz = k.group;
            if (sz == 0xffffffff) sz = props->flags;
            FUN_00756790(pj, k.inst, sz, flags);
            ++count;
        }
    }
    cj->Run6913c0(*pj);
    return cj->Continuation(g_fn74d080, this);
}

// ---------------------------------------------------------------------------
// @ 0x0074CE20  eastl::vector<E14>::DoInsertValue
// ---------------------------------------------------------------------------
inline void* operator new(unsigned, void* p) { return p; }
inline void operator delete(void*, void*) {}
struct E14V { float x, y, z, w; };
struct E14 {
    int a; E14V v;
    E14(const E14& o) {
        a = o.a;
        unsigned sign = (unsigned)o.a >> 31;
        if ((sign & 1) == 0) {
            E14V* d = &v;
            if (d) { d->x = o.v.x; d->y = o.v.y; d->z = o.v.z; d->w = o.v.w; }
        }
    }
    E14& operator=(const E14& o);   // 0x7456a0
};
E14* __cdecl copy_backward14(E14* first, E14* last, E14* dest);          // 0x745f40
E14* __cdecl uninit_copy14(E14* first, E14* last, E14* dest);            // 0x745bb0
void* __cdecl operator_new_dbg(unsigned size, const char* name, int a, int b, const char* file, int line);
extern "C" void __cdecl operator_delete_arr(void* p);
struct VecE14 {
    E14* mBegin; E14* mEnd; E14* mCap;
    void DoInsertValue(E14* pos, const E14& value);
};
// @ 0x0074CE20
void VecE14::DoInsertValue(E14* pos, const E14& value)
{
    if (mEnd != mCap) {
        const E14* pv = &value;
        if (pv >= pos && pv < mEnd)
            ++pv;
        ::new (mEnd) E14(*(mEnd - 1));
        copy_backward14(pos, mEnd - 1, mEnd);
        *pos = *pv;
        ++mEnd;
        return;
    }
    int nPrev = (int)(mEnd - mBegin);
    int nNew;
    if (nPrev) nNew = nPrev * 2; else nNew = 1;
    const int* pNew = &nNew; (void)pNew;
    E14* newBegin = nNew ? (E14*)operator_new_dbg(nNew * sizeof(E14), "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    E14* newPos = uninit_copy14(mBegin, pos, newBegin);
    ::new (newPos) E14(value);
    E14* newEnd = uninit_copy14(pos, mEnd, newPos + 1);
    if (mBegin)
        operator_delete_arr(mBegin);
    mBegin = newBegin;
    mEnd = newEnd;
    mCap = newBegin + nNew;
}

// ---------------------------------------------------------------------------
// @ 0x0074D2C0  SP::cModelWorld::HandleMessage
// ---------------------------------------------------------------------------
struct ListNode { ListNode* next; };
struct ModelNode {   // list node for models, 0x134/+0x98 fields used below
    ListNode link;
    char pad4[0x94];
    struct ResChain* chain;   // +0x98
    char pad9c[0x98];
    uint32_t handle;          // +0x134
};
struct ResChain { char pad[0x30]; ResChain* next; };
struct ReleaseTarget { V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
    virtual void Free(uint32_t h); };       // slot 8 = 0x20
struct MsgHeader { char pad[8]; uint32_t a; uint32_t pad2; uint32_t b; uint32_t pad3; uint32_t c; };

struct cModelWorldMsg {
    char pad[0x194 - 8];       // this here is the IMessageListener subobject (world+8)
    ListNode listA;            // +0x194 sentinel
    ListNode listB;            // +0x19c sentinel
    char pad1a4[0x1c4 - 0x1a4];
    ReleaseTarget* target;     // +0x1c4
    bool HandleMessage(uint32_t msgId, MsgHeader* msg);
};
void __stdcall ShutdownModel(cModelWorld* w, ModelNode* n);                       // 0x746b90 (thiscall)
struct cModelWorldX {
    void ShutdownModel(ModelNode* n);                                              // 0x746b90
    void ScheduleForLoad(ModelNode* n, ResChain* chain, uint32_t a, uint32_t b);   // 0x74c910
};

bool cModelWorldMsg::HandleMessage(uint32_t msgId, MsgHeader* msg)
{
    if (msgId == 0xf62def) {
        ModelKey k;
        uint32_t c = msg->c;
        k.inst = msg->a; k.type = msg->b; k.group = msg->c;   // msg + 8 / +0x10 / +0x18
        RefHolder res;
        ResMgrW* mgr = GetResMgrW();
        if (res.p) { RefCounted* t = res.p; res.p = 0; t->Release(); }
        if (mgr->Lookup0c(&k, &res.p, 0, 0, 0, 0)) {
            ResChain* want = (ResChain*)res.p;
            cModelWorldX* world = (cModelWorldX*)((char*)this - 8);
            for (ListNode* n = listA.next; n != &listA; n = n->next) {
                ModelNode* m = (ModelNode*)n;
                for (ResChain* r = m->chain; r; r = r->next) {
                    if (r == want) {
                        world->ShutdownModel(m);
                        world->ScheduleForLoad(m, m->chain, k.group, k.type);
                        want = (ResChain*)res.p;
                        break;
                    }
                }
            }
            for (ListNode* n = listB.next; n != &listB; n = n->next) {
                ModelNode* m = (ModelNode*)n;
                for (ResChain* r = m->chain; r; r = r->next) {
                    if (r == want) {
                        world->ScheduleForLoad(m, m->chain, k.group, k.type);
                        want = (ResChain*)res.p;
                        break;
                    }
                }
            }
        }
        (void)c;
        return true;
    }
    if (msgId != 0x2495f34)
        return false;
    for (ListNode* n = listA.next; n != &listA; n = n->next) {
        ModelNode* m = (ModelNode*)n;
        if (m->handle != 0)
            target->Free(m->handle);
        m->handle = 0;
    }
    return true;
}
