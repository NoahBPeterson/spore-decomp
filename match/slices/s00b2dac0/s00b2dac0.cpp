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
struct NounMgr {
    Entry* Create(u32 noun, u32 kind, u32 z, const Vec3* pos, const Quat* q);   // 0xb23650 ret 0x14
    void* GetAvatar();                                                          // 0xb1fdb0
    void  RemoveNoun(void* noun);                                               // 0xb225d0 (ret 4)
};
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

// ==== city display strategy (SP::cCityDisplayStrategy, 0x00b2dac0 / 0x00b2e830)
//
// Retail layout (recovered from the asm, not the 2008 PDB):
//   +0x20  state dword (bit 0 = layer active)
//   +0x154 max drawn entry count (property 0x28bd2fd)
//   +0x15c list head / +0x160 list end of 0x18-byte city records
//   +0x170 intrusive list of nouns (nodes are 0x10 bytes: next, prev, noun, colour)

struct CityNoun;
struct ObstacleMgr;

struct CityRec {
    u32         m0;      // +0x00
    u32         m4;      // +0x04
    u32         m8;      // +0x08
    u32         mC;      // +0x0c
    void*       mNoun;   // +0x10
    u32         m14;     // +0x14
};

struct CityRecList {
    CityRec* mBegin;                                            // +0x00
    CityRec* mEnd;                                              // +0x04
    CityRec* FUN_00b2a8d0(void* a, void* b);                     // 0xb2a8d0 (ret 8)
};

struct CityMapNode {
    CityMapNode* mNext;                                         // +0x00
    CityMapNode* mPrev;                                         // +0x04
    CityNoun*    mNoun;                                         // +0x08
    u32          mColor;                                        // +0x0c
};

struct CityMap {
    CityMapNode* mHead;                                         // +0x00 (== &mMap when empty)
    CityMapNode* mTail;                                         // +0x04
};

struct CityNoun {
    char pad00[0x34];
    u8   mFlags34;                                              // +0x34 (bit 2 = fresh)
    char pad35[0x38 - 0x35];
    u32  m38;                                                   // +0x38
    u32  m3C;                                                   // +0x3c
    u32  m40;                                                   // +0x40
    char pad44[0x50 - 0x44];
    void* m50;                                                  // +0x50
    char pad54[0x5c - 0x54];
    void* m5C;                                                  // +0x5c
    char pad60[0x68 - 0x60];
    void* m68;                                                  // +0x68
    char pad6C[0x7c - 0x6c];
    char mKey7C[0xc];                                           // +0x7c species key
    int  mState88;                                              // +0x88
};

struct PropDesc { char pad00[0x12]; u16 mType12; };

struct Props {
    u8 GetProperty(u32 id, PropDesc** out);                     // vt[0x24] (ret 8)
};
extern Props* g_sAppProperties;                                 // 0x15fd918
extern float  g_layerScale;                                     // 0x13f781c
extern "C" const float* GetPropertyAsFloat();                   // 0x41ea70
extern "C" void TryGetUIntProperty(Props* p, u32 id, u32* out); // 0x410370 (ret 0xc)
void* GetCurrentGameMode();                                     // 0xb5b800

static inline void* GetViewer()                                 // app vt[0x50] -> vt[0x1c]
{
    void* app = VCall0(SP_App(), 0x50);
    return app ? VCall0(app, 0x1c) : 0;
}

struct ObstacleMgr {
    void* FindById(u32 a, u32 b, u32 c);                        // 0xb74e90 (ret 0xc)
    void  Remove(void* o);                                      // 0xb74ef0 (ret 4)
};

extern "C" Vec3* FUN_00b2a790(Vec3* out);                                     // 0xb2a790
extern "C" Vec3* Vector3_Normalize(Vec3* out, const Vec3* in);                // 0x436ce0
extern "C" const Vec3* DirectionToSurfacePosition(void* model, const Vec3* in, u32 planet);  // 0xb815a0
extern "C" void* FUN_00b3d3c0(const float* pos, int** endSlot, int kind, int flag, float height, int mode);  // 0xb3d3c0
extern "C" void  FUN_00b3d3c0_3(u32 a, u32 b, u32 c);                         // 0xb3d3c0 (3-arg form)
extern "C" void  FUN_00b79c30(void* ctx);                                     // 0xb79c30
extern "C" void  FUN_00b2a6f0(void* rec);                                     // 0xb2a6f0
extern "C" void* FUN_00b2d160(void* rec);                                     // 0xb2d160
extern "C" void* FUN_00b73e70();                                              // 0xb73e70
extern "C" void  FUN_0040ce80(void* p);                                       // 0x40ce80
extern "C" void  FUN_00401090(void* p);                                       // 0x401090
extern "C" void* FUN_004df440(void* key);                                     // 0x4df440 GetPlantProfile
extern "C" void* FUN_00b2b430(u32 a, u32 b, u32 c, int d, void* prof, void* key, u16* out);  // 0xb2b430
extern "C" void* FUN_00b72320(void* a, void* b);                              // 0xb72320
extern "C" u64   FUN_00b72410(void* a, void* b);                              // 0xb72410
extern "C" void  FUN_00b2a620(void* a, u64 b, void* c);                       // 0xb2a620
extern "C" void  FUN_00b2d9a0(void* out);                                     // 0xb2d9a0
extern "C" void  FUN_00b73de0(int on);                                        // 0xb73de0 (ret 4)
extern "C" void  FUN_00b73f30(void* a, void* b);                              // 0xb73f30
extern "C" void  FUN_00b2a650();                                              // 0xb2a650
extern "C" void* FUN_00b2b830(void* first, void* last, void* end);            // 0xb2b830 (ret 0xc)
extern "C" int   FUN_00b74e90(u32 a, u32 b, u32 c);                           // 0xb74e90 (ret 0xc)
extern "C" void* PlanetModelGet(Vec3* out, u32 planet);                        // 0xb3d350 (sret form)
extern "C" void* memmove(void* dst, const void* src, unsigned int n);           // 0x11e0744

class cCityDisplayStrategy
{
public:
    void DrawLayer();                                           // 0x00b2dac0
    void FUN_00b2e830();                                        // 0x00b2e830
    ObstacleMgr* GetObstacleMgr();                              // 0x00b3d3c0 (retail: ecx = this, no args)

    char        pad00[0x20];
    u32         mState20;                                       // +0x20
    char        pad24[0x154 - 0x24];
    u32         mMax154;                                        // +0x154
    char        pad158[0x15c - 0x158];
    CityRecList mEntries;                                       // +0x15c
    CityMap     mMap;                                           // +0x170
};

// @ 0x00b2dac0
void cCityDisplayStrategy::DrawLayer()
{
    if ((mState20 & 1) == 0)
        return;

    float height = g_layerScale;
    PropDesc* desc;
    Props* props = g_sAppProperties;
    if (props != 0 && props->GetProperty(0x2979cd6, &desc) && desc->mType12 == 0xd)
        height = *GetPropertyAsFloat();

    float x = g_defaultCam.x;
    float y = g_defaultCam.y;
    float z = g_defaultCam.z;
    Vec3 scratch, dir;
    short bump = 0;                         // fresh-noun counter kept in the frame
    u32   bumpFlag = 0;

    if (GetCurrentGameMode() == (void*)0x1654c05) {
        const Vec3* p = FUN_00b2a790(&scratch);
        x = p->x;
        y = p->y;
        z = p->z;
        height = 21.0f;                                         // 0x41a80000
    } else if (GetCurrentGameMode() == (void*)0x1654c01) {
        void* avatar = NounManager()->GetAvatar();
        if (avatar == 0) {
            Viewer* viewer = (Viewer*)GetViewer();
            if (viewer != 0) {
                Vec3 cam;
                viewer->GetCameraLocationInfo(&cam, &scratch, 0, 0);
                x = cam.x;
                y = cam.y;
                z = cam.z;
            }
        } else {
            u32 planet = (u32)VCall0(*(void**)((char*)avatar + 0xc0), 0x2c);
            void* model = PlanetModelGet(&scratch, planet);
            const Vec3* p = DirectionToSurfacePosition(model, &scratch, planet);
            x = p->x;
            y = p->y;
            z = p->z;
        }
    } else {
        Viewer* viewer = (Viewer*)GetViewer();
        if (viewer != 0) {
            Vec3 cam;
            viewer->GetCameraLocationInfo(&cam, &scratch, 0, 0);
            const Vec3* d = Vector3_Normalize(&dir, &scratch);
            x = cam.x + d->x * 24.0f;
            y = cam.y + d->y * 24.0f;
            z = cam.z + d->z * 24.0f;
            height = 15.0f;                                     // 0x41700000
        }
    }

    if (x == g_defaultCam.x && y == g_defaultCam.y && z == g_defaultCam.z)
        return;

    if (g_sAppProperties != 0)
        TryGetUIntProperty(g_sAppProperties, 0x28bd2fd, &mMax154);

    int  ids[257];                          // ids[0] is the eastl capacity header
    int* begin = ids + 1;
    int* end = begin;
    ids[0] = 0;

    void* ctx = FUN_00b3d3c0(&x, &end, 7, 1, height, 0);
    FUN_00b79c30(ctx);

    int n = (int)(end - begin);
    int* pos = begin + ((n <= (int)mMax154) ? n : (int)mMax154);
    memmove(pos, end, 0);                   // retail inlines insert() with a zero count
    n = (int)(end - begin);

    // prune the record list: records whose noun is unknown are dropped, records whose
    // noun is in the new id list consume that id (so it is not drawn twice)
    CityRec* rec = mEntries.mBegin;
    while (rec != mEntries.mEnd) {
        CityMapNode* stop = (CityMapNode*)&mMap;
        CityMapNode* node = mMap.mHead;
        while (node != stop && node->mNoun != (CityNoun*)rec->mNoun)
            node = node->mNext;
        if (node == stop || rec->mNoun == 0) {
            FUN_00b3d3c0_3(rec->m8, rec->mC, rec->m0);
            int id = FUN_00b74e90(rec->m8, rec->mC, rec->m0);
            int* p = begin;
            while (p != end && *p != id)
                ++p;
            if (p != end) {
                memmove(p, p + 1, (char*)end - (char*)(p + 1));
                --end;
                rec = (CityRec*)((char*)rec + 0x18);
                continue;
            }
            FUN_00b2a6f0(rec);
            rec = (CityRec*)FUN_00b2d160(rec);
        } else {
            rec = (CityRec*)((char*)rec + 0x18);
        }
    }

    // draw the ids that are still pending
    u32 i = 0;
    while (i < (u32)(end - begin)) {
        if ((int)mMax154 <= (int)(((char*)mEntries.mEnd - (char*)mEntries.mBegin) / 0x18))
            break;
        CityNoun* noun = (CityNoun*)begin[i];
        if (noun != 0 && noun->mState88 < 3) {
            void* layer = FUN_00b73e70();
            FUN_0040ce80(layer);
            if ((noun->mFlags34 & 4) != 0) {
                ++bump;
                bumpFlag = 0x3f800000;
            }
            FUN_00401090(noun->mKey7C);
            void* prof = FUN_004df440(noun->mKey7C);
            if (prof != 0) {
                u16 tmp = 0;
                void* hit = FUN_00b2b430(noun->m38, noun->m3C, noun->m40, 8, prof, noun->mKey7C, &tmp);
                if (hit != 0) {
                    void* s50 = noun->m50;
                    void* h1 = FUN_00b72320(s50, hit);
                    FUN_00b3d3c0_3((u32)h1, 0, 0);
                    u64 h2 = FUN_00b72410(h1, s50);
                    FUN_00b2a620(noun->m5C, h2, hit);
                    FUN_00b2d9a0(&dir);
                    FUN_00b73de0(1);
                    FUN_00b73f30(noun->m68, &dir);
                    FUN_00b2a650();
                }
            }
        }
        ++i;
    }

    if (begin != 0 && begin[-1] != 0)
        op_del_arr(begin);
}

// @ 0x00b2e830
void cCityDisplayStrategy::FUN_00b2e830()
{
    for (CityRec* rec = mEntries.mBegin; rec != mEntries.mEnd;
         rec = (CityRec*)((char*)rec + 0x18)) {
        ObstacleMgr* mgr = GetObstacleMgr();
        void* obj = mgr->FindById(rec->m8, rec->mC, rec->m0);
        if (obj != 0)
            mgr->Remove(obj);
        if (rec->mNoun != 0) {
            NounManager()->RemoveNoun(rec->mNoun);
            CityNoun* noun = (CityNoun*)rec->mNoun;
            if (noun != 0) {
                rec->mNoun = 0;
                ((void (__thiscall *)(void*))(*(void***)noun)[1])(noun);
            }
        }
    }

    CityRec* first = mEntries.mBegin;
    CityRec* last = mEntries.mEnd;
    CityRec* keep = (CityRec*)FUN_00b2b830(first, last, last);
    mEntries.FUN_00b2a8d0(mEntries.mEnd, keep);
    mEntries.mEnd += (last - first);        // inlined erase trim (records removed)

    CityMapNode* stop = (CityMapNode*)&mMap;
    for (CityMapNode* n = mMap.mHead; n != stop; n = n->mNext)
        NounManager()->RemoveNoun(n->mNoun);

    CityMapNode* n = mMap.mHead;
    while (n != stop) {
        CityMapNode* next = n->mNext;
        if (n->mNoun != 0)
            ((void (__thiscall *)(void*))(*(void***)n->mNoun)[1])(n->mNoun);
        op_del_arr(n);
        n = next;
    }
    mMap.mTail = stop;
    mMap.mHead = stop;
}
