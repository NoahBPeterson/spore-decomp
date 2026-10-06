// Slice s00a2e650 - SP UI/effects manager helpers (hash-table bookkeeping, effect creation).
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>
#include <string.h>
#include <stdlib.h>

inline void* operator new(unsigned, void* p) { return p; }
inline void operator delete(void*, void*) {}

#define VCALL(T, p, off) ((T)((*(void***)(p))[(off) / 4]))

void* __cdecl EaNew(unsigned size, const char* name, int a, int b, const char* file, int line);  // 0xf473a0
void __cdecl EaDelete(void* p);                                                                    // 0xf47380

extern "C" {
int __stdcall QueryPerformanceCounter(__int64* lpPerformanceCount);
}

// ---- eastl::map<unsigned long,unsigned long>::operator[]  (0xa2e060) --------
struct MapUU {
    int& operator[](const uint32_t& key);
};

// ---- generic refcounted pointer used by the effect code ------------------------
static inline void ObjAddRef(void* p) { VCALL(void(__thiscall*)(void*), p, 0)(p); }
static inline void ObjRelease(void* p) { VCALL(void(__thiscall*)(void*), p, 4)(p); }

struct FxRef {
    void* p;
    FxRef() : p(0) {}
    ~FxRef()
    {
        if (p)
            ObjRelease(p);
    }
    FxRef& operator=(void* o)
    {
        if (o != p) {
            void* old = p;
            if (o)
                ObjAddRef(o);
            p = o;
            if (old)
                ObjRelease(old);
        }
        return *this;
    }
    void** AsPP();  // 0x00a16f40
};

struct FxRef2 {  // AutoRefCount with out-of-line assignment (0x00b5f950)
    void* p;
    FxRef2() : p(0) {}
    ~FxRef2()
    {
        if (p)
            ObjRelease(p);
    }
    void Assign(void* o);
};

// ---- Stopwatch (EA::Stopwatch) --------------------------------------------------
struct Stopwatch {
    unsigned __int64 mnStartTime;
    unsigned __int64 mnTotalElapsedTime;
    int mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
    Stopwatch(int units, int start);  // 0x0093a560
    void RestartInline()
    {
        if (mnUnits == 1) {
            unsigned __int64 t = __rdtsc();
            ((unsigned*)&mnStartTime)[1] = (unsigned)(t >> 32);
            ((unsigned*)&mnStartTime)[0] = (unsigned)t;
        } else {
            __int64 t;
            QueryPerformanceCounter(&t);
            mnStartTime = t;
        }
        mnTotalElapsedTime = 0;
    }
};

// ---- hashtable iterator / table stubs -----------------------------------------------
struct HIter {
    void* node;
    void** bucket;
    HIter() {}
    HIter(const HIter& o) : node(o.node), bucket(o.bucket) {}
};

struct HT1 {  // key -> node table at +0x1277b4
    char pad[4];
    void** mpBuckets;
    unsigned mnBuckets;
    HIter find(const unsigned& key);  // 0x00a23c10
    HIter erase(HIter it);            // 0x00a2e1b0
    void* End() { return mpBuckets[mnBuckets]; }
};
struct Pair2 {
    unsigned key;
    FxRef val;
    Pair2(const unsigned& k, void* v);  // 0x00a21d90
};
struct HT2 {  // table at +0x157440
    char pad[4];
    void** mpBuckets;
    unsigned mnBuckets;
    HIter find(const unsigned& key);        // 0x00645ed0
    HIter Insert(const Pair2& p);           // 0x00a27630
    HIter erase(HIter it);                  // 0x00d2c9f0
    void* End() { return mpBuckets[mnBuckets]; }
};
struct HT4 {  // table at +0x404 (unsigned -> int)
    char pad[4];
    void** mpBuckets;
    unsigned mnBuckets;
    HIter find(const unsigned& key);        // 0x00645ed0
    HIter Op(const unsigned* id);           // 0x00a274d0
    HIter erase(HIter it);                  // 0x00b51640
    void* End() { return mpBuckets[mnBuckets]; }
};
struct LPair {
    void* cur;
    void* ve;
};
struct LIter {
    void* p;
    void Next();  // 0x00a21290
};
struct List3 {  // at +0x157438
    void Begin_(LIter* out);               // 0x00a21c70
    void End_(LIter* out);                 // 0x00a21c90
    void Insert(LPair** pp);               // 0x00a21cb0
};
bool __cdecl MatchEntry(void* entry, bool flag, void* g48);  // 0x00a20df0

struct Props {
    void** vt;
    int pad[2];
    int m0c;   // 0x0166da38
    int m10;   // 0x0166da3c
    Props();           // 0x00a107a0
    ~Props();          // 0x013c17e0 (atexit)
    void Set(void* o);   // 0x00a108e0
    void Load(void* o);  // 0x00a10920
};
struct G48 {
    char b0;
    char b1;
    char pad[0x12];
    int kind;  // +0x14
    char pad2[0x48 - 0x18];
};
extern G48 g_g48;  // 0x0166da48

// Accessors to large-offset members (the object is > 1MB).
#define AT(T, base, off) (*(T*)((char*)(base) + (off)))

struct MgrBase {
    bool Create(unsigned name, unsigned id, void* existing, float* pos, void** out);  // 0xa2e650
    void SetEntry(unsigned key, void* val);                                           // 0xa2edd0
    void PostEvent(unsigned a, unsigned b, unsigned c, unsigned d, void* ref);        // 0xa2ee40
    bool RemoveEntry(void* obj);                                                       // 0xa2eed0
    void Rebuild();                                                                    // 0xa2ef60
};

// ---- 0xa2e650 ----------------------------------------------------------------------
// @ 0xa2e650
bool MgrBase::Create(unsigned name, unsigned id, void* existing, float* pos, void** out)
{
    if (name == 0 || id == 0)
        return false;

    FxRef ve;
    ve = VCALL(void*(__thiscall*)(MgrBase*, unsigned), this, 0x1d4)(this, id);
    if (ve.p) {
        if (out) {
            *out = ve.p;
            ObjAddRef(ve.p);
        }
        return true;
    }

    memset(&g_g48, 0, 0x48);
    static Props s_props;
    if (s_props.m10 == 0) {
        FxRef pl;
        bool ok = VCALL(bool(__thiscall*)(MgrBase*, unsigned, void**, unsigned), this, 0x138)(
            this, 0x25238ae2, &pl.p, 0x21407ee);
        if (ok && pl.p)
            s_props.Load(pl.p);
    }

    FxRef2 r14;
    r14.Assign(existing);
    if (r14.p == 0)
        VCALL(bool(__thiscall*)(MgrBase*, unsigned, void**, unsigned), this, 0x138)(this, name, &r14.p,
                                                                                    0x21407ee);
    s_props.Set(r14.p);

    float prob;
    if (VCALL(bool(__thiscall*)(Props*, unsigned, float*), &s_props, 0x30)(&s_props, 0x8fc9308e, &prob)) {
        if ((float)rand() * (1.0f / 32767.0f) > prob)
            return false;
    }
    int lvl;
    if (VCALL(bool(__thiscall*)(Props*, unsigned, int*), &s_props, 0x28)(&s_props, 0xb2550953, &lvl)) {
        if (AT(int, this, 0x200) < lvl)
            return false;
    }
    if (!VCALL(bool(__thiscall*)(MgrBase*, G48*, unsigned, unsigned, Props*, float*), this, 0x90)(
            this, &g_g48, name, id, &s_props, pos))
        return false;
    if (AT(bool, this, 0x95) && !g_g48.b1)
        return false;

    bool flag = false;
    int type = VCALL(int(__thiscall*)(MgrBase*, G48*), this, 0x144)(this, &g_g48);
    if (type == 1 || type == 2)
        return false;
    if (type == 3) {
        flag = true;
    } else if (type == 4) {
        if (!VCALL(bool(__thiscall*)(MgrBase*, G48*, void**), this, 0x148)(this, &g_g48, ve.AsPP()))
            return false;
        int kind = VCALL(int(__thiscall*)(void*), ve.p, 0x44)(ve.p);
        if (kind != g_g48.kind) {
            VCALL(void(__thiscall*)(void*, int, int), ve.p, 0x18)(ve.p, 3, AT(unsigned char, this, 0x3fd));
            if (ve.p) {
                void* t = ve.p;
                ve.p = 0;
                ObjRelease(t);
            }
        } else {
            unsigned key2 = VCALL(unsigned(__thiscall*)(void*), ve.p, 0x54)(ve.p);
            HT1& m1 = AT(HT1, this, 0x1277b4);
            HIter it1 = m1.find(key2);
            if (it1.node != m1.End())
                m1.erase(it1);

            HT2& m2 = AT(HT2, this, 0x157440);
            HIter it2 = m2.find(key2);
            if (it2.node != m2.End()) {
                m2.Insert(Pair2(name, (char*)it2.node + 4));
                m2.erase(it2);
            }

            HT4& m4 = AT(HT4, this, 0x404);
            HIter it4 = m4.find(key2);
            if (it4.node != m4.End()) {
                m4.Op(&id);
                HIter e;
                e.node = it4.node;
                e.bucket = *(void***)((char*)it4.node + 4);
                m4.erase(e);
            }

            VCALL(void(__thiscall*)(void*, unsigned), ve.p, 0x50)(ve.p, id);
            VCALL(void(__thiscall*)(void*), ve.p, 0x34)(ve.p);
            void* sub = ve.p ? (char*)ve.p + 4 : 0;
            VCALL(void(__thiscall*)(MgrBase*, unsigned, void*), this, 0x118)(this, key2, sub);
            VCALL(void(__thiscall*)(MgrBase*, unsigned, unsigned, int, int, int), this, 0x128)(this, 0x3a129e8,
                                                                                                key2, 1, 0, 0);
            VCALL(void(__thiscall*)(MgrBase*, unsigned, unsigned, int, int, int), this, 0x128)(this, 0x3a129ee,
                                                                                                key2, 0, 0, 0);
        }
    }

    if (ve.p == 0) {
        List3& l3 = AT(List3, this, 0x157438);
        LIter cur, end;
        l3.Begin_(&cur);
        l3.End_(&end);
        void* c = cur.p;
        void* e = end.p;
        while (c != e) {
            bool want = (flag || AT(bool, this, 0x95)) ? true : false;
            if (MatchEntry(c, want, &g_g48))
                break;
            cur.Next();
            c = cur.p;
        }
        int g38 = s_props.m0c;
        if (!VCALL(bool(__thiscall*)(MgrBase*, unsigned, unsigned, int, void**), this, 0x84)(this, name, id, g38,
                                                                                               ve.AsPP()))
            return false;
        LPair pr;
        pr.cur = c;
        pr.ve = ve.p;
        LPair* pp = &pr;
        l3.Insert(&pp);

        if (AT(bool, this, 0x95)) {
            VCALL(void(__thiscall*)(void*, int, int, float, int), ve.p, 0x1c)(ve.p, 1, 0, -1.0f, 1);
        } else if (flag) {
            VCALL(void(__thiscall*)(void*, int, int, float, int), ve.p, 0x1c)(ve.p, 1, 3, -1.0f, 1);
        } else {
            int* b = AT(int*, this, 0x13769c);
            int* e2 = AT(int*, this, 0x1376a0);
            if (b != e2) {
                for (int* q = b; q != e2; ++q) {
                    if (VCALL(bool(__thiscall*)(void*, int), ve.p, 0x3c)(ve.p, *q)) {
                        VCALL(void(__thiscall*)(void*, int, int, float, int), ve.p, 0x1c)(ve.p, 1, 0, -1.0f, 1);
                        break;
                    }
                }
            }
        }
        if (!VCALL(bool(__thiscall*)(void*, int, int), ve.p, 0x20)(ve.p, -1, 0))
            VCALL(void(__thiscall*)(MgrBase*, void*, int), this, 0x14c)(this, ve.p, 1);
    }

    if (pos) {
        void* sub = (char*)ve.p + 4;
        typedef void(__thiscall * SetF)(void*, unsigned, float, int);
        VCALL(SetF, sub, 0xc)(sub, 0x50c5d67, pos[0], 1);
        sub = (char*)ve.p + 4;
        VCALL(SetF, sub, 0xc)(sub, 0x50c5d66, pos[1], 1);
        sub = (char*)ve.p + 4;
        VCALL(SetF, sub, 0xc)(sub, 0x50c5d65, pos[2], 1);
    }
    if (out) {
        ObjAddRef(ve.p);
        *out = ve.p;
    }
    return true;
}

// ---- 0xa2edd0 ------------------------------------------------------------------------
struct EntryVal {
    char pad[0x18];
    int m18;
    void Assign(void* v);  // 0x00a25000
};

// @ 0xa2edd0
void MgrBase::SetEntry(unsigned key, void* val)
{
    HT1* m = &AT(HT1, this, 0x1277b4);
    HIter it = m->find(key);
    if (it.node != m->End()) {
        EntryVal* ev = (EntryVal*)((char*)it.node + 4);
        ev->Assign(val);
        if (ev->m18 == 0)
            it = m->erase(it);
    }
}

// ---- 0xa2ee40 ------------------------------------------------------------------------
struct EventMsg {
    unsigned a, b, c, d;
    void* ref;
    EventMsg(unsigned a_, unsigned b_, unsigned c_, unsigned d_, void* r) : a(a_), b(b_), c(c_), d(d_), ref(r)
    {
        if (ref)
            ObjAddRef(ref);
    }
    ~EventMsg()
    {
        if (ref)
            ObjRelease(ref);
    }
};
struct EventQueue {
    void Push(const EventMsg& m);  // 0x00a2e260
};

// @ 0xa2ee40
void MgrBase::PostEvent(unsigned a, unsigned b, unsigned c, unsigned d, void* ref)
{
    EventMsg m(a, b, c, d, ref);
    AT(EventQueue, this, 0x15b77c).Push(m);
}

// ---- 0xa2eed0 ------------------------------------------------------------------------
struct IdObj {
    virtual void v0();
    virtual void v1();
    virtual unsigned GetId();  // +8
};
struct HT1b {
    void Remove(const unsigned* key);  // 0x00a2e0e0
};

// @ 0xa2eed0
bool MgrBase::RemoveEntry(void* obj)
{
    IdObj* o = (IdObj*)obj;
    unsigned k = o->GetId();
    AT(HT1b, this, 0x1277b4).Remove(&k);
    k = o->GetId();
    HT4* m = &AT(HT4, this, 0x404);
    HIter it = m->find(k);
    if (it.node == m->End())
        return false;
    it = m->erase(it);
    return true;
}

// ---- 0xa2ef60 ------------------------------------------------------------------------
extern void* __cdecl ObjectError();  // 0x008de1a0

struct SNode {
    void* sub;
    SNode* next;
};
struct Tree {
    void DoNukeSubtree(void* n);  // 0x009a9600
};
struct Snap {
    int pad0;
    Tree tree;   // +4
    int pad8[2];
    SNode* head; // +0x10
    Snap(MapUU* m);  // 0x00a2d940
    ~Snap()
    {
        SNode* p = head;
        while (p) {
            tree.DoNukeSubtree(p->sub);
            SNode* nx = p->next;
            EaDelete(p);
            p = nx;
        }
    }
};
struct Elem {
    unsigned key;
    unsigned val;
    unsigned third;
};
struct EVec {
    Elem* b;
    Elem* e;
    Elem* c;
    ~EVec()
    {
        if (b && ((int*)b)[-1] != 0)
            EaDelete(b);
    }
};
struct HT5 {  // table at +0x33d4
    char pad[4];
    void** mpBuckets;
    unsigned mnBuckets;
    unsigned mnCount;
    void DoFreeNodes(void** buckets, unsigned n);  // 0x00a1b6c0
    HIter find(const unsigned& key);                // 0x00645ed0
    void* End() { return mpBuckets[mnBuckets]; }
};
struct P2 {
    unsigned a, b;
};
struct HT5I {
    HIter Insert(const P2* p, bool flag);  // 0x00a26ce0
};

// @ 0xa2ef60
void MgrBase::Rebuild()
{
    Stopwatch sw(4, 0);
    void* dbg = ObjectError();
    if (dbg) {
        sw.RestartInline();
        MapUU* map = &AT(MapUU, this, 0x118a5c);
        Snap snap(map);
        EVec vec;
        vec.b = 0;
        vec.e = 0;
        vec.c = 0;
        VCALL(void(__thiscall*)(void*, EVec*, Snap*, int), dbg, 0x38)(dbg, &vec, &snap, 0);
        sw.RestartInline();
        HT5* t = &AT(HT5, this, 0x33d4);
        t->DoFreeNodes(t->mpBuckets, t->mnBuckets);
        t->mnCount = 0;
        Elem* last = vec.e;
        for (Elem* p = vec.b; p != last; ++p) {
            HIter it = t->find(p->key);
            if (it.node == t->End()) {
                P2 pr;
                pr.a = p->key;
                pr.b = p->val;
                ((HT5I*)t)->Insert(&pr, false);
            } else {
                unsigned* nv = (unsigned*)it.node + 1;
                int a = (*map)[p->val];
                if ((*map)[*nv] <= a)
                    *nv = p->val;
            }
        }
    }
}

// ---- 0xa2f180 / 0xa2f1a0 ------------------------------------------------------------
class cTypeMapHolder {
public:
    char pad[0x118a5c];
    MapUU mMap;                                               // +0x118a5c
    void SetTypePriority(uint32_t type, uint32_t priority);   // @ 0xa2f180
    void InitDefaultPriorities();                             // @ 0xa2f1a0
};

// @ 0xa2f180
void cTypeMapHolder::SetTypePriority(uint32_t type, uint32_t priority)
{
    mMap[type] = (int)priority;
}

// @ 0xa2f1a0
void cTypeMapHolder::InitDefaultPriorities()
{
    mMap[0x3055f61] = 0;
    mMap[0x2b9f662] = 1;
    mMap[0x1a527db] = 2;
}

// ---- fixed_hash_map constructors (0xa2f210 / 0xa2f310 / 0xa2f410) ----------------------
struct PoolBase {
    void* mpHead;
    void* mpNext;
    void init(void* mem, unsigned size, unsigned nodeSize, unsigned align, unsigned off);  // 0x00921260
};
struct FixedAlloc {
    PoolBase pool;
    void* mpBegin;
    void* mpEnd;
    unsigned nodeSize;
    void* mpBuckets;
    FixedAlloc(char* buf, unsigned size, char* buckets)
    {
        pool.mpHead = 0;
        pool.init(buf, size, 0xc, 4, 0);
        mpBegin = buf;
        mpEnd = buf + size;
        nodeSize = 0xc;
        mpBuckets = buckets;
    }
};
struct Policy {
    float maxLoad;
    float growth;
    unsigned nextResize;
    unsigned Calc(unsigned n);  // 0x009213c0
};
unsigned __cdecl NextPrime(unsigned n);  // 0x00921340

#define FIXED_HT(NAME, POOLOFF, POOLSZ, NB)                                                    \
    struct NAME##Base {                                                                         \
        char pad0[8];                                                                           \
        unsigned mnBuckets;                                                                     \
        unsigned mnCount;                                                                       \
        Policy mPolicy;                                                                         \
        char pad1c[0x34 - 0x1c];                                                                \
        NAME##Base(unsigned nb, int a0, int* a1p, int* a1q, int a1, int* a1r, const FixedAlloc& al);  \
        ~NAME##Base();                                                                          \
        void Rehash(unsigned n);                                                                \
    };                                                                                          \
    struct NAME : NAME##Base {                                                                  \
        NAME(int a0, int a1);                                                                   \
    };                                                                                          \
    NAME::NAME(int a0, int a1)                                                                  \
        : NAME##Base(NextPrime(NB), a0, &a1, &a1, a1, &a1, FixedAlloc((char*)this + POOLOFF, POOLSZ, (char*)this + 0x34))  \
    {                                                                                           \
        Policy tmp;                                                                             \
        tmp.maxLoad = 10000.0f;                                                                 \
        tmp.growth = 2.0f;                                                                      \
        tmp.nextResize = 0;                                                                     \
        mPolicy = tmp;                                                                          \
        unsigned n = tmp.Calc(mnCount);                                                         \
        if (n > mnBuckets)                                                                      \
            Rehash(n);                                                                          \
    }

// @ 0xa2f210
FIXED_HT(FHT1, 0x35c, 0x960, 0xc9)
// @ 0xa2f310
FIXED_HT(FHT2, 0x1cc, 0x4b0, 0x65)
// @ 0xa2f410
FIXED_HT(FHT3, 0x80c, 0x1770, 0x1f5)

// ---- 0xa2f5d0: hash node allocate-and-construct -------------------------------------------
struct MappedVal {
    char d[0x1e0];
    MappedVal(const MappedVal& o);  // 0x00a2e2f0
};
struct HNodeV {
    unsigned key;
    MappedVal val;
    int m1e4;
};
struct SrcPair {
    unsigned key;
    MappedVal val;
};
struct NodePool {
    char pad[0x1c];
    void* mpHead;  // +0x1c
    char pad20[0x2c - 0x20];
    unsigned mnNodeSize;  // +0x2c
    HNodeV* Alloc(const SrcPair* src);
};

// @ 0xa2f5d0
HNodeV* NodePool::Alloc(const SrcPair* src)
{
    HNodeV* n = (HNodeV*)mpHead;
    if (n == 0)
        n = (HNodeV*)EaNew(mnNodeSize, "EASTL", 0, 0,
                           "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                           0xd1);
    else
        mpHead = *(void**)n;
    if (n) {
        n->key = src->key;
        new (&n->val) MappedVal(src->val);
    }
    n->m1e4 = 0;
    return n;
}
