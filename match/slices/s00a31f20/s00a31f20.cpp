// s00a31f20: EA::Audio::System (command handling, hash-container glue, destructor body)
#include "types.h"

typedef unsigned int uint;

namespace EA { namespace Audio {
struct Command {
    uint Type();                                   // EA::XHTML::DOM::Node::Type, 0x00fc7e50
    void GetUint32(uint key, uint32_t* out);       // 0x00a0fab0
    void GetBool(uint key, float* out);            // 0x00a0fa70 (the flag lands in a float-typed slot)
};
}}

struct MsgServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Send(uint id, void* msg, uint flags);   // slot 5 (+0x14)
};
MsgServer* __cdecl GetServer();                          // EA::Messaging::GetServer 0x00883860
void __cdecl RemoveHandler(uint a, uint b, uint c, uint d, uint e);   // EA::Messaging::RemoveHandler 0x00571db0
void __cdecl operator_delete__(void* p);                 // 0x00f47380

extern char vtbl_BehaviorMessage[];   // 0x013eb90c
extern char vtbl_Msg2[];              // 0x01452a38
extern char vt_0140de80[];
extern char vt_01403934[];
extern char vtbl_PaintSystem[];       // 0x013eb394
extern char vtbl_01452d38[];
extern char vtbl_01452d24[];

// Message built on the stack. The pointer handed to Send() is &refcount (base + 4).
struct MsgBase {
    int refcount;           // +4
    MsgBase() : refcount(0) {}
    virtual ~MsgBase() {}
};
struct Msg : MsgBase {
    uint32_t f8;
    uint32_t pad0c;
    uint32_t f10;
    uint32_t pad14;
    uint32_t f18;
    uint32_t pad1c;
    uint32_t f20;
    char     pad24[0x80 - 0x24];
    uint32_t id;            // +0x80
    uint32_t pad84;
    uint32_t flags;         // +0x88
    virtual ~Msg() {}
};
struct MsgC {                 // message whose base is built by an out-of-line ctor (0x00a227a0)
    int refcount;
    uint32_t f8, pad0c, f10, pad14, f18, pad1c, f20;
    char pad24[0x80 - 0x24];
    uint32_t id, pad84, flags;
    virtual ~MsgC() {}
};

struct HMapRaw {                                          // eastl hash_map reached by raw offset
    void* Find(uint32_t* outIter, uint32_t* key);                    // FUN_00a23ef0 (returns out iterator)
    void  Erase(uint32_t* outIter, uint32_t node, uint32_t bucket);  // FUN_00a23db0
};
struct MsgCtor { void Init(uint id); };                   // FUN_00a227a0, this = &Msg::refcount
struct ListA { void Add(uint32_t* key); };                // FUN_00a30f10
struct ListB {
    void Push(uint32_t* key);                             // 0x00a21d30
};

// ---------------------------------------------------------------------------
// ---- 0x00a31f20  EA::Audio::System::DoCommandMainThread
struct System {
    bool DoCommandMainThread(EA::Audio::Command* cmd);
};

// @ 0x00a31f20
bool System::DoCommandMainThread(EA::Audio::Command* cmd)
{
    uint8_t* self = (uint8_t*)this;
    uint type = cmd->Type();
    switch (type) {
    case 0x3a0fcce: {
        if (GetServer()) {
            uint32_t a, b, c;
            cmd->GetUint32(0x3a0fce5, &a);
            cmd->GetUint32(0x3475385, &b);
            cmd->GetUint32(0x39e3c9f, &c);
            Msg m;
            m.id = 0x3a127dc;
                        m.f8 = a;
            m.f10 = b;
            m.flags = 7;
            m.f18 = c;
            GetServer()->Send(0x3a127dc, &m.refcount, 0);
            if (a == 0x3a129ee) {
                ((ListA*)(self + 0x11b3c8))->Add(&b);
                uint32_t it[2];
                HMapRaw* map = (HMapRaw*)(self + 0x128ae0);
                map->Find(it, &b);
                uint32_t* mp = (uint32_t*)map;
                if (it[0] != *(uint32_t*)(mp[1] + mp[2] * 4)) {
                    map->Erase(it, it[0], it[1]);
                    if (b - 0x3e9 < 0x3e8) {
                        ((ListB*)(self + 0x12c9ac))->Push(&b);
                    } else if (b - 1 < 0x3e8) {
                        uint32_t* q = (uint32_t*)(self + 0x132808);
                        uint32_t endNode = *(uint32_t*)(q[1] + q[2] * 4);
                        uint32_t it2[2];
                        uint32_t* r = (uint32_t*)((HMapRaw*)q)->Find(it2, &b);
                        if (*r == endNode)
                            ((ListB*)(self + 0x1366d4))->Push(&b);
                    }
                }
            }
        }
        break;
    }
    case 0x407c01d: {
        uint32_t v1, v2;
        float v3;
        cmd->GetUint32(0x3475385, &v1);
        cmd->GetUint32(0x34753a7, &v2);
        cmd->GetBool(0x34753aa, &v3);
        typedef void (__thiscall *Fn)(System*, uint32_t, uint32_t, float);
        ((Fn)(*(void***)this)[0x1e4 / 4])(this, v1, v2, v3);
        break;
    }
    case 0x45022f5: {
        if (GetServer()) {
            uint32_t id, a, b, c, d;
            cmd->GetUint32(0x4502316, &id);
            cmd->GetUint32(0x39e3c9f, &a);
            cmd->GetUint32(0x39e3ca6, &b);
            cmd->GetUint32(0x39e3caa, &c);
            cmd->GetUint32(0x39e3cb1, &d);
            MsgC m;
            ((MsgCtor*)&m.refcount)->Init(id);
            m.f8 = a;
            m.f10 = b;
            m.flags |= 1;
            m.flags |= 2;
            m.flags |= 4;
            m.flags |= 8;
            m.f18 = c;
            m.f20 = d;
            GetServer()->Send(id, &m.refcount, 0);
        }
            break;
    }
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00a32220  eastl::fixed_hash_map<uint, EA::Audio::Subscription, 100, 101, 1, ...>::fixed_hash_map
struct fixed_pool_base {
    uint32_t mpHead;
    uint32_t mpOwner;
    uint32_t mpPoolBegin;
    uint32_t mpPoolEnd;
    uint32_t mnNodeSize;
    uint32_t mpBuckets;
    void init(void* mem, uint size, uint nodeSize, uint align, uint offset);   // 0x00921260
};
void* __cdecl FUN_00921340(uint n);                                                   // 0x00921340
struct FHMapBase {
    uint32_t pad[4];
    void Ctor(void* a, uint b, uint32_t* c, uint32_t* d, uint e, uint32_t* f, fixed_pool_base* g);   // FUN_00a23b60
    void Rehash(uint n);                                                              // FUN_00a22110
};
struct PrimePolicy { uint GetBucketCount(uint n); };                                  // FUN_009213c0

struct FixedHashMap {
    uint32_t pad0[2];
    uint32_t mnBucketCount;     // +8
    uint32_t mnElementCount;    // +0xc
    float    mfMaxLoadFactor;   // +0x10
    float    mfGrowthFactor;    // +0x14
    uint32_t mnRehashCount;     // +0x18
    char     pad1c[0x34 - 0x1c];
    char     pad34[0x1cc - 0x34];
    FixedHashMap(uint a, uint b);
};

FixedHashMap::FixedHashMap(uint a, uint b)
{
    fixed_pool_base pool;
    pool.mpOwner = (uint32_t)this;
    pool.mpHead = 0;
    pool.init((char*)this + 0x1cc, 4000, 0x28, 4, 0);
    pool.mpPoolBegin = (uint32_t)((char*)this + 0x1cc);
    pool.mpPoolEnd = (uint32_t)((char*)this + 0x1cc + 4000);
    pool.mnNodeSize = 0x28;
    pool.mpBuckets = (uint32_t)((char*)this + 0x34);
    void* r = FUN_00921340(0x65);
    ((FHMapBase*)this)->Ctor(r, a, &b, &b, b, &b, &pool);
    mfMaxLoadFactor = 10000.0f;
    mfGrowthFactor = 2.0f;
    mnRehashCount = 0;
    PrimePolicy pp;
    uint n = pp.GetBucketCount(mnElementCount);
    if (n > mnBucketCount)
        ((FHMapBase*)this)->Rehash(n);
}

// ---------------------------------------------------------------------------
// @ 0x00a32320  swap of two hash containers via a 1 KB temporary
struct HashTmp {
    void Ctor(void* src);                              // FUN_00a310b0
    void Dtor();                                       // FUN_00a26da0
};
struct HashDst {
    void Clear(uint32_t a, uint32_t b);                // FUN_00a2ae90
    void Assign(uint32_t a, uint32_t b, uint32_t c);   // FUN_00a2b2e0
};

void FUN_00a32320(uint32_t* x, uint32_t* y)
{
    struct { uint32_t pre; uint32_t t0, t1; char rest[0x3f0]; } tmp;
    ((HashTmp*)&tmp.t0)->Ctor(x);
    if (x != y) {
        ((HashDst*)x)->Clear(x[0], x[1]);
        ((HashDst*)x)->Assign(y[0], y[1], tmp.pre);
    }
    if (y != &tmp.t0) {
        ((HashDst*)y)->Clear(y[0], y[1]);
        ((HashDst*)y)->Assign(tmp.t0, tmp.t1, tmp.pre);
    }
    ((HashTmp*)&tmp.t0)->Dtor();
}

// ---------------------------------------------------------------------------
// ---- 0x00a323e0  hash_map<uint, fixed_hash_map<uint,float,20,21,...>, ...>::operator[]
struct OuterMap {
    uint32_t pad[1];
    uint32_t* mpBuckets;        // +4
    uint32_t mnBucketCount;     // +8
    uint32_t* operator_index(uint32_t* key);
};
struct OMFind {
    void Find(uint32_t* out, uint32_t* key);               // 0x00a23b00
};
struct OMNodeCtor {
    void Ctor(void* a);                                    // 0x00a2e2f0
};
struct OMTmp {
    void* Make(char* a, char* b);                          // 0x00a1e320
};
struct OMInsert {
    void Insert(uint32_t* out, void* node, uint32_t flag); // 0x00a30f80
};
struct OMNodeDtor {
    void Dtor();                                           // 0x00a2aa70
};
struct OMFree {
    void DoFreeNodes(uint32_t nodes, uint32_t count);      // 0x00a1b6c0
};

// @ 0x00a323e0
// return find(k) != end() ? it->second : insert(value_type(k, mapped_type())).first->second
uint32_t* OuterMap::operator_index(uint32_t* key)
{
    uint32_t it[2];
    ((OMFind*)this)->Find(it, key);
    if (it[0] != mpBuckets[mnBucketCount])
        return (uint32_t*)(it[0] + 4);
    char cmp;                                   // empty hash/equal_to temporaries
    uint32_t t[0x1e0 / 4];                      // mapped_type() (fixed_hash_map<uint,float,20,21>)
    void* pt = ((OMTmp*)t)->Make(&cmp, &cmp);
    struct { uint32_t key; char val[0x1dc - 4]; } node;     // value_type(k, t)
    node.key = *key;
    ((OMNodeCtor*)&node.val)->Ctor(pt);
    ((OMInsert*)this)->Insert(it, &node, it[0] & 0xffffff00);   // by-value true_type: low byte 0
    uint32_t* r = (uint32_t*)(it[0] + 4);
    ((OMNodeDtor*)&node)->Dtor();
    // ~t: DoFreeNodes, then release the bucket array (pool slot or heap)
    ((OMFree*)t)->DoFreeNodes(t[1], t[2]);
    uint32_t* b = (uint32_t*)t[1];
    t[3] = 0;
    if (t[2] > 1 && b != (uint32_t*)t[0xc]) {
        if (b < (uint32_t*)t[9] || (uint32_t*)t[10] <= b)
            operator_delete__(b);
        else {
            *b = t[7];
            t[7] = (uint32_t)b;
        }
    }
    return r;
}

// ---------------------------------------------------------------------------
// ---- 0x00a32550  EA::Audio::System destructor body (tears down ~40 fixed EASTL containers)
struct HT {
    void Key_Free(uint32_t, uint32_t);          // 0x007611f0
    void TS_Free(uint32_t, uint32_t);           // 0x00a1b6c0 (TextStyle pair table DoFreeNodes)
    void F68fb70(uint32_t, uint32_t);
    void F24480(uint32_t, uint32_t);
    void F2add0(uint32_t, uint32_t);
    void F2f6e0(uint32_t, uint32_t);            // table of fixed_hash_map<uint,float,...>
    void F276e0(uint32_t, uint32_t);            // Subscription table
    void F26f30(uint32_t, uint32_t);
    void Fb6fdf0(uint32_t, uint32_t);
    void RbNuke(uint32_t node);                 // 0x009a9600
};
struct Simple { void Dtor(); };                 // thiscall, no args
struct SimpleA {
    void a26da0(); void a222c0(); void a23920(); void ilb(); void a227d0();
    void f11e64d0();                            // 0x011e64d0
    void mutexDtor();                           // 0x00922130 (EA::Thread::Mutex::~Mutex)
    void f921e40();                             // 0x00921e40
    void f922e10();                             // 0x00922e10
};

template<int I> static inline void PoolTail(uint32_t* d)
{
    uint32_t* p = (uint32_t*)d[I];
    d[I + 2] = 0;
    if (d[I + 1] > 1 && p != (uint32_t*)d[I + 0xb]) {
        if (p < (uint32_t*)d[I + 8] || (uint32_t*)d[I + 9] <= p)
            operator_delete__(p);
        else {
            *p = d[I + 6];
            d[I + 6] = (uint32_t)p;
        }
    }
}
template<int I> static inline void NoPoolTail(uint32_t* d)
{
    d[I + 2] = 0;
    if (d[I + 1] > 1)
        operator_delete__((void*)d[I]);
}
template<int I> static inline void FixedBuf(uint32_t* d)       // fixed_vector buffer, I+4 = inline buffer
{
    uint32_t p = d[I];
    if (p != 0 && p != d[I + 4])
        operator_delete__((void*)p);
}
template<int I> static inline void CountedBuf(uint32_t* d)     // new[] with count cookie
{
    uint32_t p = d[I];
    if (p != 0 && *(uint32_t*)(p - 4) != 0)
        operator_delete__((void*)p);
}

struct SystemDtor {
    void Destroy();
};

#define HTBASE(I) ((HT*)&d[(I) - 1])

// @ 0x00a32550
void SystemDtor::Destroy()
{
    uint32_t* d = (uint32_t*)this;
    d[0] = (uint32_t)vtbl_01452d38;
    d[1] = (uint32_t)vtbl_01452d24;
    HTBASE(0x56efe)->Key_Free(d[0x56efe], d[0x56eff]);
    NoPoolTail<0x56efe>(d);
    FixedBuf<0x56edf>(d);
    ((SimpleA*)((char*)this + 0x15b77c))->a26da0();
    if (d[0x56dde])
        (*(void (__thiscall**)(void*))(*(uint32_t*)d[0x56dde] + 8))((void*)d[0x56dde]);
    CountedBuf<0x56dce>(d);
    HTBASE(0x563d5)->F24480(d[0x563d5], d[0x563d6]);
    PoolTail<0x563d5>(d);
    ((SimpleA*)((char*)this + 0x157c60))->a222c0();
    HTBASE(0x55d11)->F24480(d[0x55d11], d[0x55d12]);
    PoolTail<0x55d11>(d);
    ((SimpleA*)((char*)this + 0x157438))->ilb();
    HTBASE(0x4dffb)->TS_Free(d[0x4dffb], d[0x4dffc]);
    PoolTail<0x4dffb>(d);
    HTBASE(0x4de58)->F68fb70(d[0x4de58], d[0x4de59]);
    PoolTail<0x4de58>(d);
    HTBASE(0x4dde0)->TS_Free(d[0x4dde0], d[0x4dde1]);
    PoolTail<0x4dde0>(d);
    FixedBuf<0x4dda7>(d);
    FixedBuf<0x4d9b5>(d);
    HTBASE(0x4ca03)->F68fb70(d[0x4ca03], d[0x4ca04]);
    PoolTail<0x4ca03>(d);
    FixedBuf<0x4c610>(d);
    HTBASE(0x4b65e)->F68fb70(d[0x4b65e], d[0x4b65f]);
    PoolTail<0x4b65e>(d);
    FixedBuf<0x4b26b>(d);
    HTBASE(0x4a2b9)->F68fb70(d[0x4a2b9], d[0x4a2ba]);
    PoolTail<0x4a2b9>(d);
    HTBASE(0x49dee)->F2add0(d[0x49dee], d[0x49def]);
    PoolTail<0x49dee>(d);
    HTBASE(0x46cf3)->F2f6e0(d[0x46cf3], d[0x46cf4]);
    PoolTail<0x46cf3>(d);
    HTBASE(0x468f7)->TS_Free(d[0x468f7], d[0x468f8]);
    PoolTail<0x468f7>(d);
    HTBASE(0x466ef)->F24480(d[0x466ef], d[0x466f0]);
    PoolTail<0x466ef>(d);
    ((SimpleA*)((char*)this + 0x119ba4))->a23920();
    HTBASE(0x462ed)->TS_Free(d[0x462ed], d[0x462ee]);
    PoolTail<0x462ed>(d);
    HTBASE(0x462e5)->F26f30(d[0x462e5], d[0x462e6]);
    NoPoolTail<0x462e5>(d);
    HTBASE(0x4629f)->TS_Free(d[0x4629f], d[0x462a0]);
    PoolTail<0x4629f>(d);
    ((HT*)&d[0x46297])->RbNuke(d[0x4629a]);
    HTBASE(0x46290)->Fb6fdf0(d[0x46290], d[0x46291]);
    NoPoolTail<0x46290>(d);
    HTBASE(0x46288)->Fb6fdf0(d[0x46288], d[0x46289]);
    NoPoolTail<0x46288>(d);
    HTBASE(0x46280)->Fb6fdf0(d[0x46280], d[0x46281]);
    NoPoolTail<0x46280>(d);
    HTBASE(0x2010a)->F276e0(d[0x2010a], d[0x2010b]);
    PoolTail<0x2010a>(d);
    HTBASE(0xcf6)->TS_Free(d[0xcf6], d[0xcf7]);
    PoolTail<0xcf6>(d);
    HTBASE(0x8fa)->TS_Free(d[0x8fa], d[0x8fb]);
    PoolTail<0x8fa>(d);
    HTBASE(0x4fe)->F24480(d[0x4fe], d[0x4ff]);
    PoolTail<0x4fe>(d);
    HTBASE(0x102)->TS_Free(d[0x102], d[0x103]);
    PoolTail<0x102>(d);
    CountedBuf<0xe9>(d);
    CountedBuf<0xd5>(d);
    CountedBuf<0xc1>(d);
    CountedBuf<0xad>(d);
    CountedBuf<0x99>(d);
    CountedBuf<0x85>(d);
    if (d[0x7e])
        (*(void (__thiscall**)(void*))(*(uint32_t*)d[0x7e] + 4))((void*)d[0x7e]);
    ((SimpleA*)((char*)this + 0x198))->a227d0();
    ((SimpleA*)((char*)this + 0xf8))->f11e64d0();
    ((SimpleA*)((char*)this + 0xb8))->mutexDtor();
    d[0x28] = (uint32_t)vt_0140de80;
    d[0x27] = (uint32_t)vt_01403934;
    ((SimpleA*)((char*)this + 0x28))->f921e40();
    ((SimpleA*)((char*)this + 0x20))->f922e10();
    if (d[2]) {
        uint32_t h = d[2];
        d[2] = 0;
        RemoveHandler(h, d[3], d[4], d[5], d[6]);
    }
    d[1] = (uint32_t)vtbl_PaintSystem;
}

// ---------------------------------------------------------------------------
// ---- 0x00a32ea0  EA::Audio::System::SetOutputProperty
struct InnerMap {
    uint32_t pad;
    uint32_t* mpBuckets;
    uint32_t mnBucketCount;
};
struct OuterIdx {
    InnerMap* Index(uint32_t* key);                        // 0x00a323e0 (operator[], ret 4)
};
struct InnerFind {
    void Find(uint32_t* out, uint32_t* key);               // 0x00645ed0
};
struct InnerInsert {
    void Insert(uint32_t* pairOut, uint32_t* pairKV, uint32_t flag);   // 0x00a26ce0
};

struct SystemProps {
    void SetOutputProperty(uint32_t id, uint32_t prop, float value);
};

// @ 0x00a32ea0
void SystemProps::SetOutputProperty(uint32_t id, uint32_t prop, float value)
{
    InnerMap* m = ((OuterIdx*)((char*)this + 0x11b3c8))->Index(&id);
    uint32_t it;
    ((InnerFind*)m)->Find(&it, &prop);
    uint32_t saved = prop;
    if (it != m->mpBuckets[m->mnBucketCount]) {
        ((float*)it)[1] = value;
        return;
    }
    prop = prop & 0xffffff00;
    uint32_t kv[2];
    kv[0] = saved;
    ((float*)kv)[1] = value;
    char out[12];
    ((InnerInsert*)m)->Insert((uint32_t*)out, kv, prop);
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct ListB {
    void Push(unsigned int*); // 0x00a21d30
};
struct OuterIdx {
    void Index(unsigned int*); // 0x00a323e0
};
struct InnerFind {
    void Find(unsigned int*, unsigned int*); // 0x00645ed0
};
struct OMFind {
    void Find(unsigned int*, unsigned int*); // 0x00a23b00
};
struct SimpleA {
    void mutexDtor(); // 0x00922130
    void f922e10(); // 0x00922e10
    void f921e40(); // 0x00921e40
    void f11e64d0(); // 0x011e64d0
};
struct InnerInsert {
    void Insert(unsigned int*, unsigned int*, unsigned int); // 0x00a26ce0
};
struct OMInsert {
    void Insert(unsigned int*, void*, unsigned int); // 0x00a30f80
};
struct OMNodeCtor {
    void Ctor(void*); // 0x00a2e2f0
};
struct OMNodeDtor {
    void Dtor(); // 0x00a2aa70
};
struct OMTmp {
    void Make(char*, char*); // 0x00a1e320
};
}
