// Slice s00a0d2d0: the anim-viewer / anim-feedback block — the job-ref map
// find-or-insert and the anim-data tree nuke, the 0x18-byte (KF) and 0x1c-byte
// (Rec) vector algorithms (copy / fill / assign / resize / grow), the
// viewer-anim-data copy ctor and assignment, the anim-feedback script command
// execute bodies and the anim-viewer cheat unregister.
//
// Layouts are retail offsets read off the disassembly; field names are Claude-coined.
// Module flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <intrin.h>

typedef unsigned int uint;

struct WideStr {                                                     // DynamicString, 16 bytes
    uint16_t* begin;                                                 // +0x00
    uint16_t* end;                                                   // +0x04
    uint16_t* cap;                                                   // +0x08
    void*     a0c;                                                   // +0x0c
    void AllocateSelf(int n);                                        // 0x00429760
    void Assign(const uint16_t* b, const uint16_t* e);               // 0x00423650
};
typedef WideStr WStr;

// =========================================================================== free callees
void* __cdecl GetManager();                                          // 0x0067dcd0
void* __cdecl FUN_0068f4d0();                                        // 0x0068f4d0
void* __cdecl WCopy(void* dst, const void* src, uint n);             // 0x011e0744
void* __cdecl EAAllocate(uint size, const char* name, int, int, const char* file, int line); // 0x00f473a0
void  __cdecl operator_delete__(void* p);                            // 0x00f47380
void* __cdecl RBTreeIncrement(void* node);                           // 0x00921580
void  __cdecl RemoveHandler(void* h, void* a, void* b, void* c, void* d); // 0x00571db0
void  __cdecl FUN_009a9680();                                        // 0x009a9680
void  __cdecl FUN_009c1dc0();                                        // 0x009c1dc0
void  __cdecl FUN_009c26a0();                                        // 0x009c26a0

void* __stdcall FUN_00a0ad10(void** out, void* hint, void* key, char flag);  // 0x00a0ad10
void  __cdecl FUN_00a0c090(void** out, void* first, void* last, void* dst, void* src); // 0x00a0c090
void  __cdecl FUN_00a0c230(void* a, void* b, void* c);               // 0x00a0c230
void* __cdecl FUN_00a0d740(uint n, void* first, void* last);         // 0x00a0d740
void  __cdecl FUN_00a0ade0(void* dst, uint count, const void* value); // 0x00a0ade0
void* __cdecl FUN_00a0af70(void* first, void* last, void* dst);      // 0x00a0af70
void  __cdecl FUN_00a0a580(void* a, void* b, void* c);               // 0x00a0a580
void* __cdecl FUN_00a0a520(void* v);                                  // 0x00a0a520
void  __cdecl FUN_00a0be60(void* end, uint count, const void* value);// 0x00a0be60
void  __cdecl FUN_00a0dee0(void* first, void* last);                 // 0x00a0dee0
void  __cdecl FUN_00a09810(void* first, void* last);                 // 0x00a09810
bool  __cdecl FUN_00a09740(void* obj, void** out);                   // 0x00a09740
void* __cdecl FUN_00e5c780(void** out, const void* key);             // 0x00e5c780 (tree find)

WStr*  __cdecl ConvertToString16(void* out, const char* s, int n);   // 0x0093c5a0
uint   __cdecl FNV1_String16(const uint16_t* s, uint basis, uint x); // 0x00932f30
uint16_t* __cdecl strchr16(const uint16_t* s, int c);                // 0x013cc458

// =========================================================================== little classes
struct KFBase {                                                      // 0x14-byte sub-object
    uint32_t w[5];
    void operator=(const KFBase& o);                                 // 0x00a0b110
};
struct KF {                                                          // 0x18 element
    KFBase b;                                                        // +0x00
    float  prob;                                                     // +0x14
};

struct VHelper { void dtor(void* b, void* e); };                     // 0x00a0aca0
struct RecDtor { void dtor(void* b, void* e); };                     // 0x00a0bc90

struct Rec {                                                         // 0x1c record
    float    f0;                                                     // +0x00
    float    f4;                                                     // +0x04
    uint32_t f8;                                                     // +0x08
    WideStr  s;                                                      // +0x0c
    uint32_t f18;                                                    // +0x18
    void ctorFrom(const Rec& o);                                     // 0x00a093b0
};

struct KVec {                                                        // vector<KF>
    KF* begin;                                                       // +0x00
    KF* end;                                                         // +0x04
    KF* cap;                                                         // +0x08
    void* copyCtor(const KVec& src);                                 // 0x00a0d350
    KVec& operator=(const KVec& o);                                  // 0x00a0dd90
    void  resize(uint a);                                            // 0x00a0e0b0
    void  insertAt(KF* pos, uint count, const KF& value);            // 0x00a0da40
};
struct RecVec {                                                      // vector<Rec>
    Rec* begin;                                                      // +0x00
    Rec* end;                                                        // +0x04
    Rec* cap;                                                        // +0x08
    void resize(uint a);                                             // 0x00a0d660
    void growAt(Rec* end, const Rec& value);                         // 0x00a0bcf0
};

// script parser (cArguments)
struct Parser {
    const char** MainArguments(int n);                               // 0x00838320
    const char** OptionArguments(const char* name, int n);           // 0x00838330
};

// host / converter object at this+4
struct Host2 {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual void v6();  virtual void v7();
    virtual void v8();  virtual void v9();  virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34();
    virtual void  v35(void* x);                                      // +0x8c
    virtual void  v36(); virtual void v37();
    virtual float v38(const char* s);                                // +0x98
    virtual void  v39();
    virtual uint  v40(const char* s);                                // +0xa0
};

// job-ref smart pointer payload
struct JobRef { void operator=(const JobRef& o); };                  // 0x00630540
struct Job    { int Release(); };                                    // 0x00690120
struct RefCounted {
    virtual void Destroy(bool del);                                  // vtable +0x00
    int refcount;                                                    // +0x04
};
struct StaticData { int Clear(void* p); int Release(); };            // 0x009c1dc0 / 0x009c26a0

// =========================================================================== trees
struct TNode2 {                                                      // job-ref map node
    TNode2* l;                                                       // +0x00
    TNode2* r;                                                       // +0x04
    void*   up;                                                      // +0x08
    uint    color;                                                   // +0x0c
    uint    key;                                                     // +0x10
    void*   val;                                                     // +0x14
};
struct TreeMap {                                                     // rbtree<uint,JobRef>
    uint   pad00;                                                    // +0x00
    void*  anchor;                                                   // +0x04
    void*  endNode;                                                  // +0x08
    void*  root;                                                     // +0x0c
    uint   pad10;                                                    // +0x10
    uint   count;                                                    // +0x14
    void* findOrInsert(uint* key);                                   // 0x00a0d2d0
    void* find(void** out, const void* key);                         // 0x00e5c780
};

struct AnimNode {                                                    // anim-data tree node
    AnimNode* l;                                                     // +0x00
    AnimNode* r;                                                     // +0x04
    uint8_t   pad08[0x10];                                           // +0x08 .. +0x17
    WideStr   s;                                                     // +0x18
    uint8_t   pad24[0x18];                                           // +0x28 .. +0x3f
    KVec      vec;                                                   // +0x40
};
struct AnimTree {
    uint32_t pad00;                                                  // +0x00
    void*    anchor;                                                 // +0x04
    void*    endNode;                                                // +0x08
    void*    root;                                                   // +0x0c
    uint8_t  color;                                                  // +0x10
    uint8_t  pad11[3];                                               // +0x11
    uint32_t count;                                                  // +0x14
    void nukeSubtree(AnimNode* n);                                   // 0x00a0d9c0
};

// =========================================================================== remaining objects
struct ViewerData {                                                  // 0x00a0d420 this
    uint8_t  pad00[0x10];                                            // +0x00
    WideStr  s;                                                      // +0x10
    uint8_t  pad1c[0x18];                                            // +0x20 .. +0x37
    KVec     vec;                                                    // +0x38
    void Clear();                                                    // 0x00a0d420
};

// the 0x38 copy-ctor struct (id + wide string + floats + bytes + uints + KVec)
struct S {
    uint32_t id;                                                     // +0x00
    WideStr  s;                                                      // +0x04
    float    f14;                                                    // +0x14
    float    f18;                                                    // +0x18
    uint8_t  b1c, b1d, b1e;                                          // +0x1c,1d,1e
    uint32_t f20;                                                    // +0x20
    uint32_t f24;                                                    // +0x24
    uint32_t f28;                                                    // +0x28
    KVec     vec;                                                    // +0x2c
    S(const S& o);                                                   // 0x00a0d7a0
    S& operator=(const S& o);                                        // 0x00a0df30
    void reset();                                                    // 0x00a0e250
};

struct ObjA {                                                        // this+0xc -> this
    uint8_t pad00[0x38];                                             // +0x00
    RecVec* pv;                                                      // +0x38
};

struct Obj {                                                         // command state at this+0x30
    uint8_t pad00[0x04];                                             // +0x00
    float   f04;                                                     // +0x04
    uint8_t pad08[0x04];                                             // +0x08
    S       s;                                                       // +0x0c
    uint8_t pad44[0x08];                                             // +0x44 .. +0x4b
    float   f4c;                                                     // +0x4c
    float   f50;                                                     // +0x50
    float   f54;                                                     // +0x54
};

struct Cmd {
    uint8_t pad00[0x04];                                             // +0x00
    Host2*  f04;                                                     // +0x04
    uint8_t pad08[0x28];                                             // +0x08 .. +0x2f
    Obj*    f30;                                                     // +0x30
    void Execute_470(void* parser);                                  // 0x00a0d470
    void notify(uint key);                                           // 0x00a0d570
    void ResetCmd(void* parser);                                     // 0x00a0e2e0
    void AddProb(void* parser);                                      // 0x00a0e350
    void SetName(void* parser);                                      // 0x00a0e3f0
};

struct Cheat {
    uint8_t pad00[0x04];                                             // +0x00
    Host2*  f04;                                                     // +0x04
    uint8_t pad08[0x04];                                             // +0x08
    ObjA*   f0c;                                                     // +0x0c
    void Execute_880(void* parser);                                  // 0x00a0d880
};

struct CleanupObj {                                                  // 0x00a0dfa0 this
    uint8_t  pad00[0x54];                                            // +0x00 .. +0x53
    void*    f54;                                                    // +0x54
    void*    f58;                                                    // +0x58
    void*    f5c;                                                    // +0x5c
    void*    f60;                                                    // +0x60
    void*    f64;                                                    // +0x64
    uint8_t  pad68[0x80 - 0x68];                                     // +0x68 .. +0x7f
    uint32_t f80;                                                    // +0x80
    RefCounted* f84;                                                 // +0x84
    bool Unregister();                                               // 0x00a0dfa0
};

struct XObj { void* f0; void Reset(); };                             // 0x166c058 object

// globals
extern XObj       g_x166c058;                                        // 0x0166c058
extern void*      g_p166cc08;                                        // 0x0166cc08
extern AnimTree   g_tree1551a68;                                     // 0x01551a68

// =========================================================================== 0x00a0d2d0
// @ 0x00a0d2d0
void* TreeMap::findOrInsert(uint* key)
{
    void* e  = root;
    void* lb = (char*)this + 4;
    if (e != 0) {
        do {
            uint nk = *(uint*)((char*)e + 0x10);
            if (nk < *key) {
                e = *(void**)e;
            } else {
                lb = e;
                e = *(void**)((char*)e + 4);
            }
        } while (e != 0);
    }
    if (lb != (char*)this + 4 && *(uint*)((char*)lb + 0x10) <= *key)
        return (char*)lb + 0x14;

    uint k[2];
    k[0] = *key;
    k[1] = 0;
    void* out;
    FUN_00a0ad10(&out, lb, k, 0);
    return (char*)out + 0x14;
}

// =========================================================================== 0x00a0d350
// @ 0x00a0d350
void* KVec::copyCtor(const KVec& src)
{
    int n = (int)(src.end - src.begin);
    KF* base;
    if (n == 0)
        base = 0;
    else
        base = (KF*)EAAllocate(n * 0x18, "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    cap = (KF*)((char*)base + n * 0x18);
    begin = base;
    end = base;
    void* out;
    FUN_00a0c090(&out, src.begin, src.end, base, (void*)&src);
    end = (KF*)out;
    return this;
}

// =========================================================================== 0x00a0d3e0
// @ 0x00a0d3e0
KF* __cdecl FUN_00a0d3e0(KF* first, KF* last, KF* dst)
{
    while (first != last) {
        dst->b = first->b;
        dst->prob = first->prob;
        ++first;
        ++dst;
    }
    return dst;
}

// =========================================================================== 0x00a0d420
// @ 0x00a0d420
void ViewerData::Clear()
{
    VHelper* vh = (VHelper*)&vec;
    vh->dtor(vec.begin, vec.end);
    if (vec.begin != 0 && *(int*)((char*)vec.begin - 4) != 0)
        operator_delete__(vec.begin);

    uint16_t* b = s.begin;
    int gap = (int)(((char*)s.cap - (char*)b) & 0xfffffffe);
    if (gap > 2 && b != 0)
        operator_delete__(b);
}

// =========================================================================== 0x00a0d470
// @ 0x00a0d470
void Cmd::Execute_470(void* parser)
{
    const char** a = ((Parser*)parser)->MainArguments(1);

    Rec r;
    r.f0 = 1.0f;
    r.f4 = -1.0f;
    r.f8 = 0;
    r.s.begin = (uint16_t*)0x01667bac;
    r.s.end   = (uint16_t*)0x01667bac;
    r.s.cap   = (uint16_t*)0x01667bae;

    ObjA* o = (ObjA*)f30;
    RecVec* v = o->pv;
    if (v->end < v->cap) {
        Rec* slot = v->end;
        v->end = slot + 1;
        if (slot != 0)
            slot->ctorFrom(r);
    } else {
        v->growAt(v->end, r);
    }

    if ((((char*)r.s.cap - (char*)r.s.begin) & 0xfffffffe) > 2 && r.s.begin != 0)
        operator_delete__(r.s.begin);

    Rec* last = v->end - 1;
    WStr tmp;
    WStr* p = ConvertToString16(&tmp, a[0], -1);
    if (p != &last->s)
        last->s.Assign(p->begin, p->end);

    if ((((char*)tmp.cap - (char*)tmp.begin) & 0xfffffffe) > 2 && tmp.begin != 0)
        operator_delete__(tmp.begin);
}

// =========================================================================== 0x00a0d570
// @ 0x00a0d570
void Cmd::notify(uint key)
{
    void* out;
    if (g_x166c058.f0 == 0)
        return;
    TreeMap* g = (TreeMap*)g_x166c058.f0;
    g->find(&out, &key);
    if (out != (char*)g + 4)
        return;
    TreeMap* t = (TreeMap*)((char*)this + 0x34);
    t->find(&out, &key);
    if (out != (char*)this + 0x38)
        return;

    struct K3 { uint a, b, c; } k;
    k.a = key;
    k.b = 0xee17c6ad;
    k.c = 0;

    void* mgr = GetManager();
    void* r = (void*)(*(void*(**)(void*, void*))(*(char**)mgr + 0x58))(mgr, &k);
    if (r == 0)
        return;

    void* b1 = 0;
    uint c1 = 0;
    bool ok = (bool)(*(char(**)(void*, void**, uint*, int, int, int))(*(char**)r + 0x34))(
        r, &b1, &c1, 1, 6, 1);
    if (!ok)
        goto release;
    {
        void* job = 0;
        FUN_00a09740(out, &job);
        void* slot = t->findOrInsert(&key);
        ((JobRef*)slot)->operator=(*(JobRef*)&job);
        if (job != 0)
            ((Job*)job)->Release();
    }
release:
    if (out != 0)
        (*(void(**)(void*))(*(char**)out + 8))(out);
}

// =========================================================================== 0x00a0d660
// @ 0x00a0d660
void RecVec::resize(uint a)
{
    uint n = (uint)(end - begin);
    if (a > n) {
        Rec tmp;
        tmp.f0 = 1.0f;
        tmp.f4 = -1.0f;
        tmp.f8 = 0;
        tmp.s.begin = (uint16_t*)0x01667bac;
        tmp.s.end   = (uint16_t*)0x01667bac;
        tmp.s.cap   = (uint16_t*)0x01667bae;
        FUN_00a0be60(end, a - n, &tmp);
        if ((((char*)tmp.s.cap - (char*)tmp.s.begin) & 0xfffffffe) > 2 && tmp.s.begin != 0)
            operator_delete__(tmp.s.begin);
    } else {
        RecDtor* rd = (RecDtor*)this;
        rd->dtor(begin + a, end);
    }
}

// =========================================================================== 0x00a0d7a0
// @ 0x00a0d7a0
S::S(const S& o)
{
    id = o.id;
    s.begin = 0;
    s.end = 0;
    s.cap = 0;
    int n = (int)(o.s.end - o.s.begin);
    s.AllocateSelf(n + 1);
    WCopy(s.begin, o.s.begin, (uint)n * 2);
    s.end = (uint16_t*)((char*)s.begin + n * 2);
    *s.end = 0;
    f14 = o.f14;
    f18 = o.f18;
    b1c = o.b1c;
    b1d = o.b1d;
    b1e = o.b1e;
    f20 = o.f20;
    f24 = o.f24;
    f28 = o.f28;
    vec.copyCtor(o.vec);
}

// =========================================================================== 0x00a0d850
// @ 0x00a0d850
void __cdecl FUN_00a0d850(KF* first, KF* last, const KF* value)
{
    for (; first != last; ++first) {
        first->b = value->b;
        first->prob = value->prob;
    }
}

// =========================================================================== 0x00a0d880
// @ 0x00a0d880
void Cheat::Execute_880(void* parser)
{
    const char** a = ((Parser*)parser)->MainArguments(1);

    RecVec* v = (RecVec*)(*(char**)((char*)f0c + 0x3c) - 0x18);
    v->resize((uint)(v->end - v->begin) + 1);

    Rec* last = v->end - 1;
    WStr tmp;
    WStr* r = ConvertToString16(&tmp, a[0], -1);
    if (r != &last->s)
        last->s.Assign(r->begin, r->end);
    if ((((char*)tmp.cap - (char*)tmp.begin) & 0xfffffffe) > 2 && tmp.begin != 0)
        operator_delete__(tmp.begin);

    uint id;
    const char** o = ((Parser*)parser)->OptionArguments("instanceId", 1);
    if (o != 0) {
        id = f04->v40(o[0]);
    } else {
        uint16_t* str = last->s.begin;
        uint16_t* pw = strchr16(str, '/');
        if (pw != 0)
            str = pw + 1;
        id = FNV1_String16(str, 0x811c9dc5, 1);
    }
    last->f8 = id;

    const char** ds = ((Parser*)parser)->OptionArguments("durationScale", 1);
    if (ds != 0)
        last->f0 = f04->v38(ds[0]);

    const char** du = ((Parser*)parser)->OptionArguments("duration", 1);
    if (du != 0)
        last->f4 = f04->v38(du[0]);
}

// =========================================================================== 0x00a0d9c0
// @ 0x00a0d9c0
void AnimTree::nukeSubtree(AnimNode* n)
{
    while (n != 0) {
        nukeSubtree(n->l);
        AnimNode* next = n->r;
        VHelper* vh = (VHelper*)&n->vec;
        vh->dtor(n->vec.begin, n->vec.end);
        if (n->vec.begin != 0 && *(int*)((char*)n->vec.begin - 4) != 0)
            operator_delete__(n->vec.begin);
        uint16_t* b = n->s.begin;
        int gap = (int)(((char*)n->s.cap - (char*)b) & 0xfffffffe);
        if (gap > 2 && b != 0)
            operator_delete__(b);
        operator_delete__(n);
        n = next;
    }
}

// =========================================================================== 0x00a0da40
// @ 0x00a0da40
void KVec::insertAt(KF* pos, uint count, const KF& value)
{
    uint n = (uint)(end - begin);
    if ((uint)(cap - begin) >= count) {
        if (count != 0) {
            FUN_00a0a520((void*)&value);
            float p = value.prob;
            uint tail = (uint)((KF*)end - pos);
            if (count < tail) {
                KF* bail = end - count;
                void* out;
                FUN_00a0c090(&out, bail, end, end, end);
                end = (KF*)((char*)end + count * 0x18);
                FUN_00a0c230(pos, bail, (void*)out);
                FUN_00a0d850(pos, (KF*)((char*)pos + count * 0x18), &value);
            } else {
                FUN_00a0ade0(end, count - tail, &value);
                end = (KF*)((char*)end + (count - tail) * 0x18);
                void* out;
                FUN_00a0c090(&out, pos, (void*)(end), end, end);
                end = (KF*)((char*)end + tail * 0x18);
                FUN_00a0d850(pos, (KF*)end, &value);
            }
            FUN_00a09810((void*)&value, (void*)((char*)&value + 1));
            (void)p;
        }
        return;
    }

    uint old = (uint)((char*)end - (char*)begin) / 0x18;
    uint want = old * 2;
    if (old == 0)
        want = 1;
    uint need = old + count;
    if (need < want)
        need = want;
    KF* nb;
    if (need == 0)
        nb = 0;
    else
        nb = (KF*)EAAllocate(need * 0x18, "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    KF* m1 = (KF*)FUN_00a0af70(begin, pos, nb);
    FUN_00a0a580(begin, pos, nb);
    FUN_00a0ade0(m1, count, &value);
    KF* m2 = (KF*)((char*)m1 + count * 0x18);
    KF* e1 = end;
    KF* m3 = (KF*)FUN_00a0af70(pos, e1, m2);
    FUN_00a0a580(pos, e1, m2);
    if (begin != 0 && *(int*)((char*)begin - 4) != 0)
        operator_delete__(begin);
    begin = nb;
    end = m3;
    cap = (KF*)((char*)nb + need * 0x18);
}

// =========================================================================== 0x00a0dd90
// @ 0x00a0dd90
KVec& KVec::operator=(const KVec& o)
{
    if (&o != this) {
        uint n = (uint)(o.end - o.begin);
        if ((uint)(cap - begin) < n) {
            KF* nb = (KF*)FUN_00a0d740(n, o.begin, o.end);
            VHelper* vh = (VHelper*)this;
            vh->dtor(begin, end);
            if (begin != 0 && *(int*)((char*)begin - 4) != 0)
                operator_delete__(begin);
            cap = (KF*)((char*)nb + n * 0x18);
            begin = nb;
            end = (KF*)((char*)nb + n * 0x18);
        } else {
            uint have = (uint)(end - begin);
            if (have < n) {
                FUN_00a0d3e0(o.begin, o.begin + have, begin);
                void* out;
                FUN_00a0c090(&out, o.begin + have, o.end, end, o.end);
                end = (KF*)((char*)begin + n * 0x18);
            } else {
                KF* r = FUN_00a0d3e0(o.begin, o.end, begin);
                VHelper* vh = (VHelper*)this;
                vh->dtor(r, end);
                end = (KF*)((char*)begin + n * 0x18);
            }
        }
    }
    return *this;
}

// =========================================================================== 0x00a0df30
// @ 0x00a0df30
S& S::operator=(const S& o)
{
    id = o.id;
    WideStr* src = (WideStr*)&o.s;
    if (src != &s)
        s.Assign(src->begin, src->end);
    f14 = o.f14;
    f18 = o.f18;
    b1c = o.b1c;
    b1d = o.b1d;
    b1e = o.b1e;
    f20 = o.f20;
    f24 = o.f24;
    f28 = o.f28;
    vec = o.vec;
    return *this;
}

// =========================================================================== 0x00a0dfa0
// @ 0x00a0dfa0
bool CleanupObj::Unregister()
{
    if (f54 != 0) {
        void* h = f54;
        f54 = 0;
        RemoveHandler(h, f58, f5c, f60, f64);
    }
    f80 = 0;
    if (f84 != 0) {
        RefCounted* p = f84;
        f84 = 0;
        if (_InterlockedExchangeAdd((volatile long*)&p->refcount, -1) == 1) {
            _InterlockedExchange((volatile long*)&p->refcount, 1);
            p->Destroy(true);
        }
    }
    {
        void* anchor = (char*)this + 0x1c;
        for (void* it = *(void**)((char*)this + 0x20); it != anchor;
             it = RBTreeIncrement(it)) {
            void* sd = *(void**)((char*)it + 0x18);
            if (sd != 0) {
                ((StaticData*)sd)->Clear(0);
                sd = *(void**)((char*)it + 0x18);
                if (sd != 0) {
                    *(void**)((char*)it + 0x18) = 0;
                    ((StaticData*)sd)->Release();
                }
            }
        }
    }
    ((AnimTree*)((char*)this + 0x18))->nukeSubtree(*(AnimNode**)((char*)this + 0x24));
    {
        void** anchor = (void**)((char*)this + 0x1c);
        anchor[0] = anchor;
        *(void**)((char*)this + 0x20) = anchor;
        *(void**)((char*)this + 0x24) = 0;
        *((uint8_t*)this + 0x28) = 0;
        *(void**)((char*)this + 0x2c) = 0;
    }
    g_tree1551a68.nukeSubtree((AnimNode*)g_tree1551a68.root);
    g_tree1551a68.anchor  = &g_tree1551a68.anchor;
    g_tree1551a68.endNode = &g_tree1551a68.anchor;
    g_tree1551a68.root    = 0;
    g_tree1551a68.color   = 0;
    g_tree1551a68.count   = 0;
    FUN_009a9680();
    g_p166cc08 = 0;
    return true;
}

// =========================================================================== 0x00a0e0b0
// @ 0x00a0e0b0
void KVec::resize(uint a)
{
    uint n = (uint)(end - begin);
    if (a > n) {
        KF tmp;
        tmp.b.w[0] = 0;
        tmp.b.w[1] = 0;
        tmp.b.w[2] = 0;
        tmp.prob = 1.0f;
        RecDtor* rd = (RecDtor*)&tmp;
        rd->dtor(0, 0);
        insertAt(end, a - n, tmp);
        FUN_00a09810((void*)tmp.b.w, (void*)((char*)tmp.b.w + 4));
        if (tmp.b.w[0] != 0 && *(int*)((char*)tmp.b.w[0] - 4) != 0)
            operator_delete__((void*)tmp.b.w[0]);
    } else {
        FUN_00a0dee0(begin + a, end);
    }
}

// =========================================================================== 0x00a0e250
// @ 0x00a0e250
void S::reset()
{
    id = 0xffffffff;
    if (s.end != s.begin) {
        *s.begin = 0;
        s.end = s.begin;
    }
    f14 = 0.0f;
    f18 = -1.0f;
    b1c = 0;
    b1d = 0;
    b1e = 0;
    f20 = 0;
    f24 = 0;
    f28 = 4;

    KF* b = vec.begin;
    KF* e = vec.end;
    KF* r = FUN_00a0d3e0(e, e, b);
    VHelper* vh = (VHelper*)&vec;
    vh->dtor(r, e);
    vec.end = (KF*)((char*)vec.end + ((uint)((char*)e - (char*)b) / 0x18) * 0x18);
}

// =========================================================================== 0x00a0e2e0
// @ 0x00a0e2e0
void Cmd::ResetCmd(void* parser)
{
    (void)parser;
    f30->s.reset();
    f30->f4c = 0.0f;
    f30->f50 = 1.0f;
    f30->f54 = -1.0f;
    f30->s.f14 = f30->f04;
    f30->s.vec.resize(1);
    f04->v35(this);
}

// =========================================================================== 0x00a0e350
// @ 0x00a0e350
void Cmd::AddProb(void* parser)
{
    f30->s.vec.resize((uint)(f30->s.vec.end - f30->s.vec.begin) + 1);
    float f = 1.0f;
    const char** a = ((Parser*)parser)->OptionArguments("probability", 1);
    if (a != 0)
        f = f04->v38(a[0]);
    f30->s.vec.end[-1].prob = f;
    f30->f4c += f;
    f04->v35(this);
}

// =========================================================================== 0x00a0e3f0
// @ 0x00a0e3f0
void Cmd::SetName(void* parser)
{
    f30->s.reset();
    f30->f4c = 0.0f;
    f30->f50 = 1.0f;
    f30->f54 = -1.0f;
    f30->s.f14 = f30->f04;
    const char** a = ((Parser*)parser)->MainArguments(2);
    f30->s.id = f04->v40(a[0]);
    WStr tmp;
    WStr* p = ConvertToString16(&tmp, a[1], -1);
    if (p != &f30->s.s)
        f30->s.s.Assign(p->begin, p->end);
    int gap = (int)(((char*)tmp.cap - (char*)tmp.begin) & 0xfffffffe);
    if (gap > 2 && tmp.begin != 0)
        operator_delete__(tmp.begin);
    f04->v35(this);
}
