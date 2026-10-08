// Slice s00b2dac0 (cl2 #177): 0x00b2e010, a 2 KB "populate N game nouns on a planet" manager method.
//
// The object (SpawnMgr) owns two eastl::multimap-like red-black trees of
// (uint64 key -> AutoRefCount<Entry>): an "active" tree at +0x1ac (anchor +0x1b0, size +0x1c0)
// and a "pool" tree at +0x1c8 (keyed by entry type).  The method (ret 0x1c, 7 args) is
//   Spawn(type, perRec, key, recs, nRecs, scale)
// For each of nRecs 0x4c-byte placement records it places perRec entries of the given type
// (1 or 3) at random world positions on the current planet, either reusing pooled entries of
// that type (those are then moved to the active tree under `key`), creating new ones through
// the noun manager, or stealing the farthest active entry of that type.
#include "types.h"

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef uint64_t u64;

inline void* operator new(unsigned int, void* p) { return p; }

extern "C" void* op_new(u32 size, const char* name, int a, int b, const char* file, int line);  // 0xf473a0
extern "C" void  op_del_arr(void* p);                                                         // 0xf47380

struct Vec3 { float x, y, z; Vec3() {} Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {} };
struct Quat { float x, y, z, w; };

// ---- refcounted game entry ------------------------------------------------
struct Entry {
    virtual void AddRef();           // slot 0 (declared only: out-of-line vcall)
    virtual void Release();          // slot 1
    void Activate(int a, int b);     // 0xc3f8b0 thiscall ret 8
    char pad0[0x34 - 4];
    void* placer;                    // +0x34: sub-object with its own vtable (not a pointer; address-of only)
    char pad1[0x110 - 0x38];
    int type;                        // +0x110
    void* Placer() { return (char*)this + 0x34; }
};

// Placer sub-object vtable slots: 0x38 SetPos(const Vec3*), 0x3c SetOrient(const Quat*), 0xac GetModel()
// Placer data: byte +0x71 (flag), +0x75 (flag)
struct Model { void* obj; u32 flags; };
typedef void  (__thiscall *VFn1)(void*, const void*);
typedef Model* (__thiscall *VFnM)(void*);
typedef void  (__thiscall *VFnObj)(void*, Model*, int);

static inline void PlaceEntry(Entry* e, const Vec3* pos, const Quat* q)
{
    void* pl = e->Placer();
    ((VFn1)(*(void***)pl)[0x38 / 4])(pl, pos);
    ((VFn1)(*(void***)pl)[0x3c / 4])(pl, q);
    ((u8*)pl)[0x75] = 1;
    ((u8*)pl)[0x71] = 0;
    VFnM getm = (VFnM)(*(void***)pl)[0xac / 4];
    if (getm(pl)) {
        Model* m = getm(pl);
        m->flags |= 1;
        m = getm(pl);
        ((VFnObj)(*(void***)m->obj)[0x16c / 4])(m->obj, m, 1);
        e->Activate(1, 0);
    }
}

// ---- smart pointer --------------------------------------------------------
struct Ref {
    Entry* p;
    Ref() : p(0) {}
    Ref(Entry* e) : p(e) { if (e) e->AddRef(); }
    void Adopt(Entry* e) { p = e; if (e) e->AddRef(); }
    Ref(const Ref& r) : p(r.p) { Entry* q = r.p; if (q) q->AddRef(); }
    ~Ref() { if (p) p->Release(); }
};

// eastl::vector<Ref> with sp_vector_allocator
extern "C" Ref* eastl_copy_impl(Ref* first, Ref* last, Ref* dest);   // 0x6782c0
struct PVec {
    Ref* b; Ref* e; Ref* c;
    void DoInsertValue(Ref* pos, const Ref* val);    // 0xaea5d0 thiscall ret 8
    void push_back(const Ref& r)
    {
        if (e < c) { new (e) Ref(r); ++e; }
        else DoInsertValue(e, &r);
    }
    unsigned size() const { return (unsigned)(e - b); }
    void erase(Ref* first, Ref* last)
    {
        Ref* i = eastl_copy_impl(last, e, first);
        for (Ref* q = i; q < e; ++q) q->~Ref();
        e -= (last - first);
    }
    void clear() { erase(b, e); }
    ~PVec()
    {
        for (Ref* q = b; q < e; ++q) q->~Ref();
        if (b && ((u32*)b)[-1]) op_del_arr(b);
    }
};

// ---- red-black trees ------------------------------------------------------
struct Pair { u64 key; Ref val; Pair(u64 k, const Ref& v) : key(k), val(v) {} };
struct NodeBase { NodeBase* right; NodeBase* left; NodeBase* parent; int color; };
struct Node : NodeBase { Pair kv; };
struct NodeRange { Node* first; Node* last; };

extern "C" Node* RBTreeIncrement(Node* n);                                    // 0x921580
extern "C" void  RBTreeErase(Node* n, Node* anchor);                           // 0x921880
extern "C" void  RBTreeInsert(Node* n, Node* parent, Node* anchor, bool left); // 0x9216a0

struct Tree {
    u32 cmp;
    NodeBase anchor;
    u32 size;
    u32 alloc;
    void EqualRange(NodeRange* out, const u64* key);       // 0xb02430 thiscall ret 8
    void Erase(Node** out, Node* first, Node* last);       // 0xb2ca80 thiscall ret 0xc
};

// ---- world helpers --------------------------------------------------------
struct PlanetModelT {
    Vec3* MakeRandomWorldPosition(Vec3* out, const void* rec, float a, float b);   // 0xb81780 ret 0x10
    Vec3* GetUp(Vec3* out, const Vec3* pos);                                      // 0xb7e3b0 ret 8
    Quat* BuildSurfaceOrientation(Quat* out, const Vec3* pos);                    // 0xb7f190 ret 8
};
PlanetModelT* PlanetModel();                                                      // 0xb3d350
struct NounMgr { Entry* Create(u32 noun, u32 kind, u32 z, const Vec3* pos, const Quat* q); }; // 0xb23650 ret 0x14
NounMgr* NounManager();                                                           // 0xb3d300
void  OrthogonalVector(Vec3* out, const Vec3* in);                                // 0x6985b0
Quat* QuaternionFromFacingAndUp(Quat* out, const Vec3* facing, const Vec3* up);   // 0x69b600
void  SortByDistance(Ref* b, Ref* e, Vec3 cam);                                   // 0xb2d3a0

struct Viewer { void GetCameraLocationInfo(Vec3* pos, Vec3* extra, int a, int b); }; // 0x7c3d30 ret 0x10
void* SP_App();                                                                   // 0x67dd10
static inline void* VCall0(void* o, int off) { return ((void* (__thiscall *)(void*))(*(void***)o)[off / 4])(o); }

extern Vec3 g_defaultCam;     // 0x167e0a0
extern int  g_maxEntries;     // 0x1568cf0 (initial 60)

struct Rec {
    u16 a, b;
    float f[4];
    Vec3 v0, v1, v2;
    char pad[0x4c - 0x38];
};
struct LocalRec {
    u16 a, b;
    float f[4];
    Vec3 v0, v1, v2;
};

struct SpawnMgr {
    char pad[0x1ac];
    Tree active;       // +0x1ac (anchor +0x1b0, size +0x1c0)
    Tree pool;         // +0x1c8 (anchor +0x1cc)

    // @ 0x00b2e010
    void Spawn(int type, int perRec, u64 key, const Rec* recs, unsigned nRecs, float scale);
};

void SpawnMgr::Spawn(int type, int perRec, u64 key, const Rec* recs, unsigned nRecs, float scale)
{
    if (nRecs == 0) return;
    bool flagged = false;
    u32 kind;
    switch (type) {
    case 1:
        kind = 0x0b25e449;
        break;
    case 3:
        kind = 0x950109e8;
        flagged = true;
        break;
    default:
        return;
    }

    PVec vec = { 0, 0, 0 };
    int vecCount = 0;
    for (Node* n = (Node*)active.anchor.left; n != (Node*)&active.anchor; n = RBTreeIncrement(n)) {
        Ref t(n->kv.val);
        if (t.p->type == type) {
            vec.push_back(t);
            ++vecCount;
        }
    }

    Vec3 cam = g_defaultCam;
    Vec3 camExtra;
    Viewer* viewer = (Viewer*)VCall0(VCall0(SP_App(), 0x50), 0x1c);
    if (viewer) viewer->GetCameraLocationInfo(&cam, &camExtra, 0, 0);
    SortByDistance(vec.b, vec.e, cam);

    Tree* poolTree = &pool;
    u64 typeKey = (__int64)type;
    NodeRange range;
    poolTree->EqualRange(&range, &typeKey);
    Node* cursor = range.first;
    Node* last = range.last;
    int rangeCount = 0;
    for (Node* n = range.first; n != last; ) {
        n = RBTreeIncrement(n);
        ++rangeCount;
    }

    const Rec* r = recs;
    for (unsigned ri = nRecs; ri != 0; --ri, ++r) {
        LocalRec rec;
        rec.a = r->a; rec.b = r->b;
        rec.f[0] = r->f[0]; rec.f[1] = r->f[1]; rec.f[2] = r->f[2]; rec.f[3] = r->f[3];
        rec.v0 = r->v0; rec.v1 = r->v1; rec.v2 = r->v2;
        if (perRec <= 0) continue;
        int idx = rangeCount + vecCount;
        for (int k = perRec; k != 0; --k) {
            Vec3 pos;
            PlanetModel()->MakeRandomWorldPosition(&pos, rec.f, scale * 2.0f, scale * 3.0f);
            Quat q;
            if (flagged) {
                Vec3 up;
                PlanetModel()->GetUp(&up, &pos);
                Vec3 facing;
                OrthogonalVector(&facing, &up);
                Quat tq;
                q = *QuaternionFromFacingAndUp(&tq, &facing, &up);
            } else {
                Quat tq;
                q = *PlanetModel()->BuildSurfaceOrientation(&tq, &pos);
            }

            Ref er;
            if (cursor != last) {
                // reuse a pooled entry
                Entry* pe = cursor->kv.val.p;
                if (pe) {
                    er.Adopt(pe);
                    PlaceEntry(pe, &pos, &q);
                }
                cursor = RBTreeIncrement(cursor);
            } else if (idx < g_maxEntries) {
                // create a new entry
                er.Adopt(NounManager()->Create(0x3a2511e, kind, 0, &pos, &q));
                ++vecCount;
                ++idx;
            } else {
                // steal the farthest active entry of this type
                if (vec.size() == 0) continue;
                er.Adopt(vec.e[-1].p);
                vec.e = vec.e - 1;
                if (vec.e->p) vec.e->p->Release();
                for (Node* n = (Node*)active.anchor.left; n != (Node*)&active.anchor; n = RBTreeIncrement(n)) {
                    if (er.p == n->kv.val.p) {
                        --active.size;
                        RBTreeIncrement(n);
                        RBTreeErase(n, (Node*)&active.anchor);
                        if (n->kv.val.p) n->kv.val.p->Release();
                        op_del_arr(n);
                        break;
                    }
                }
                PlaceEntry(er.p, &pos, &q);
            }

            if (er.p) {
                Pair tmp(key, er);
                Node* y = (Node*)&active.anchor;
                Node* x = (Node*)active.anchor.parent;
                while (x) {
                    y = x;
                    if (x->kv.key <= key) x = (Node*)x->right;
                    else x = (Node*)x->left;
                }
                bool left = !(y == (Node*)&active.anchor || key < y->kv.key);
                Node* nn = (Node*)op_new(0x20, "Simulator", 0, 0,
                    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
                new (&nn->kv) Pair(tmp);
                RBTreeInsert(nn, y, (Node*)&active.anchor, left);
                ++active.size;
            }
        }
    }

    Node* ign;
    poolTree->Erase(&ign, range.first, cursor);
    vec.clear();
}
