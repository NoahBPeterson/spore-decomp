// slice s005d27e0 -- cSPEditorSpine vertebra-tree helpers (names from the dev PDB where they fit;
// the retail layout differs from the PDB, so fields below are by offset).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

void operator_delete__(void* p);   // 0x00f47380 (cdecl)

// refcounted block (AddRef at vtbl+4, Release at vtbl+8)
struct RefObj {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
    virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
};
// handle-like object (Release at vtbl+4, Delete at +0x10, Reset at +0x1c)
struct HandleObj {
    virtual void v0();
    virtual void Release();
    virtual void v2(); virtual void v3();
    virtual void Delete(int flag);
    virtual void v5(); virtual void v6();
    virtual void Reset();
    void SetState(RefObj* o);            // 0x005a8a60 cHandleish::SetState
};
// Havok-style refcounted object: vtbl[0]=deleting dtor, +4 memSize, +6 refCount
struct HkRef {
    virtual void* Destroy(int flags);
    unsigned short memSize;
    short refCount;
    void removeReference();              // 0x0109ae60 hkWorldObject::removeReference
    void release() { if (memSize != 0) { if (--refCount == 0) Destroy(1); } }
};
struct HkWorld : HkRef {
    void removeAction(HkRef* a);                     // 0x01086f40 hkWorld::removeAction
    void removeConstraint(char* tmp, void* c);       // 0x01086e90 hkWorld::removeConstraint
    void removeEntity(char* tmp, void* b);           // 0x01083110
    void addPhantom(HkRef* p);                       // 0x01083320 hkWorld::addPhantom
    void removePhantom(HkRef* p);                    // 0x01083400 hkWorld::removePhantom
};
struct hkThreadMem {
    void deallocateChunk(void* p, int size, int type);   // 0x0107db10
};
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long idx);
extern unsigned long g_tlsThreadMem;                 // 0x016e4174
void* operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0 (EA)
struct Block;
Block* NextVertebra(Block* b);           // 0x004a5970 (cdecl)

template <class T> struct AutoRef {
    T* mp;
    AutoRef() : mp(0) {}
    AutoRef(T* p) : mp(p) { if (p) p->AddRef(); }
    ~AutoRef() { if (mp) mp->Release(); }
    AutoRef& operator=(T* p) {
        if (p != mp) { if (p) p->AddRef(); T* old = mp; mp = p; if (old) old->Release(); }
        return *this;
    }
};

struct RbNode {
    RbNode* mpRight; RbNode* mpLeft; RbNode* mpParent; int color;
    unsigned key;            // +0x10
    void* body;              // +0x14  (value.first)
};
struct VertVal { void* body; void* pad4; void* constraint; void* pad12; };
struct VIter { RbNode* node; };

RbNode* RBTreeIncrement(RbNode* n);                  // 0x00921580 (cdecl)
void RBTreeErase(RbNode* n, RbNode* anchor);         // 0x00921880 (cdecl)

struct VMap {                       // eastl::map<unsigned, VertVal> at spine+0xcc
    int pad0;
    RbNode* anchorRight;            // +0xd0 anchor node base
    RbNode* anchorLeft;
    RbNode* root;                   // +0xd8
    char color;
    unsigned size;                  // +0xe0
    VertVal* Index(const unsigned* k);                   // 0x00632e90 map::operator[]
    VIter* Find(VIter* out, const unsigned* k);          // 0x00e5c780 rbtree::find
    void DoNukeSubtree(RbNode* n);                       // 0x009a9600
    ~VMap() { DoNukeSubtree(root); }
    __forceinline void Clear() {
        RbNode* p = root;
        RbNode* nxt = 0;
        while (p) {
            DoNukeSubtree(p->mpRight);
            nxt = p->mpLeft;
            operator_delete__(p);
            p = nxt;
        }
        RbNode* anchor = Anchor();
        anchorRight = anchor;
        anchorLeft = anchor;
        root = nxt;
        color = 0;
        size = 0;
    }
    RbNode* Anchor() { return (RbNode*)&anchorRight; }
    __forceinline RbNode* LowerFind(unsigned key) {
        RbNode* anchor = Anchor();
        RbNode* cur = root;
        RbNode* best = anchor;
        while (cur) {
            if (!(cur->key < key)) { best = cur; cur = cur->mpLeft; }
            else cur = cur->mpRight;
        }
        if (best != anchor && !(key < best->key)) return best;
        return anchor;
    }
};

struct hkMotion { float getMass(); };                // 0x01088270 hkRigidMotion::getMass
struct hkBody { char pad[0x58]; hkMotion* motion; };

struct ModelT { char pad[0x58]; float f58; };     // cMWModel: +0x58 packs mHighlightType/mCustomPickLevel/+0x5a
struct Cookie {                                    // object at block+0x28 (editor model owner)
    float F4adaa0(int a, int b, int c);            // 0x004adaa0 (fastcall; returns +0x38)
    struct PhysW* F4ad450();                       // 0x004ad450 (fastcall; returns +0x30)
    void F4abaf0(struct BlockT* b, int v);         // 0x004abaf0
};
struct BlockT : RefObj {
    char pad4[0x10 - 4];
    ModelT* model;               // +0x10
    char pad14[0x28 - 0x14];
    Cookie* cookie;              // +0x28
    char pad2c[0x48 - 0x2c];
    float px, py, pz;            // +0x48
    char pad54[0x60 - 0x54];
    float m[9];                  // +0x60 3x3 rotation, rows
    char pad84[0x1d8 - 0x84];
    float scale;                 // +0x1d8
    char pad1dc[4];
    float minScale, maxScale;    // +0x1e0 +0x1e4
    char pad1e8[0x33c - 0x1e8];
    BlockT* nextVertebra;        // +0x33c
    char children[4];            // +0x340 (source container for FixedVec8::Fill)
    char pad3[0xdc8 - 0x344];
    unsigned flags;              // +0xdc8
    BlockT();                                           // 0x004346b0
    void FUN_00438700(BlockT* o);                       // 0x00438700
    void BuildBlock(void* a, unsigned b, void* c, void* world, float x, int d, int e, int f);   // 0x00441440
    void FUN_00448e90(float* pos, int v);               // 0x00448e90
    void FUN_00449420(float* rot, int v);               // 0x00449420
    void FUN_00440090(float s, int v);                  // 0x00440090
    void FUN_00440020(float s, int v);                  // 0x00440020
};

// small fixed vector of AutoRef<BlockT>, 8 inline elements (EASTL fixed_vector shape)
struct FixedVec8 {
    BlockT** mpBegin; BlockT** mpEnd; BlockT** mpCap;
    unsigned pad[2];
    unsigned overflowFlag;
    BlockT* buf[8];
    FixedVec8() : mpBegin(buf), overflowFlag(0), mpEnd(buf), mpCap(buf + 8) {}
    ~FixedVec8() {
        BlockT** e = mpEnd;
        for (BlockT** p = mpBegin; p < e; p++)
            if (*p) (*p)->Release();
        if (mpBegin && mpBegin[-1]) operator_delete__(mpBegin);
    }
    void Fill(void* src);                       // 0x00453f20
};

struct Ob {
    void FUN_0048a4c0();
    void FUN_005d59c0();
    void FUN_00438700(BlockT* b);
    void FUN_004acab0(BlockT* b, int v);
};

struct hkTransform { float rot[3][4]; float pos[4]; };
struct Mat3 { float m[9]; };
void FUN_004a92c0(Mat3* rot, hkTransform* xf);   // 0x004a92c0 (cdecl)
void FUN_005cd670(hkTransform* xf, int axis);    // 0x005cd670 (cdecl)
struct PhysW { void* World(); };                    // 0x004b91c0 (fastcall; returns +8)
struct hkMem { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
               virtual void* Alloc(int size, int type); };      // vtbl+0x10
extern hkMem* g_hkMemory;                           // 0x016e4178
struct CdPoint { char pad[0x1c]; float dist; struct Coll* a; unsigned pad24; struct Coll* b; unsigned pad2c; };
struct Coll { void* timeObj; char pad[0x1c - 4]; unsigned flags; };
struct PointCollector {                             // hkCdPointCollector over a fixed hkArray (8 inline points)
    void* vt; float earlyOut; unsigned pad8, padc;
    CdPoint* data; int size; unsigned capFlags; unsigned pad1c;
    CdPoint buf[8];
};
extern char vtbl_collector[];                       // 0x013ef55c
struct hkSimpleShapePhantom : HkRef {
    hkSimpleShapePhantom(HkRef* shape, const hkTransform* xf, unsigned key);   // 0x0108c750
    virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(); virtual void v12();
    virtual void getClosestPoints(PointCollector* c);       // vtbl+0x34
};
inline void* operator new(unsigned, void* p) { return p; }
float TimeObjValue(void* t);                        // 0x005cd910 (cdecl)
void* operator_new_ed(unsigned size, const char* name, int, int, int, int);   // 0x00f473a0
extern char kEditor[];
extern char g_threadMemKey;
extern char vtbl_13f89d4[], vtbl_13f89c4[], vtbl_cEditorResource[], vtbl_cContentValidationSummarizer[];
extern float g_015ba0d0, g_015ba0d4;

struct Spine {
    void* vt0;                   // +0x00
    int refCount;                // +0x04
    void* vt8;                   // +0x08
    float f0c, f10;              // +0x0c +0x10
    HkWorld* world;              // +0x14
    HandleObj* p18;              // +0x18
    HkRef* hk1c;                 // +0x1c hkWorldObject
    char pad20[0x3c - 0x20];
    HkRef* action;               // +0x3c
    char pad40[0x4c - 0x40];
    float maxBlockScale;         // +0x4c
    char pad50[0xc5 - 0x50];
    char dirty;                  // +0xc5
    char padc6[0xcc - 0xc6];
    VMap vertebrae;              // +0xcc
    char padE4[0xe8 - 0xe4];
    AutoRef<RefObj> firstVertebra;   // +0xe8
    AutoRef<RefObj> lastVertebra;    // +0xec
    void* pF0;                       // +0xf0
    AutoRef<HandleObj> firstHandle;  // +0xf4
    AutoRef<HandleObj> lastHandle;   // +0xf8
    void* pFC;                       // +0xfc
    unsigned u100;
    unsigned inst104;                // +0x104 (model key instance)
    unsigned* vecBegin;          // +0x108
    unsigned* vecEnd;            // +0x10c
    char pad110[0x11c - 0x110];
    float halfWidth;             // +0x11c
    Ob* route1;                  // +0x120
    Ob* route2;                  // +0x124

    void FUN_005d14a0();
    void FUN_005d1e70();
    void FUN_005d1f30();
    void FUN_005d2740(unsigned k);
    BlockT* FUN_005d27e0(BlockT* src, float* dir, float* rot);
    HkRef* CreateVertebraShape(float scale);            // 0x005cd9a0
    unsigned MakeVertKey(float scale, int idx);         // 0x005cdb30
    void FUN_005ce060(VertVal* out, float scale, struct hkTransform* xf);   // 0x005ce060
    void FUN_005d2790();
    bool FUN_005d3010(unsigned key, int, int, int, int, int, int);
    float FUN_005d3100();
    void FUN_005d31b0();
    void FUN_005d3300(BlockT* b);
    void FUN_005d35c0();
};

// @ 0x005D27E0
// Grow the spine by one vertebra at its first or last end: probe a new vertebra shape with a Havok
// phantom, and if the spot is free build the block, its body and constraint, and link it in.
BlockT* Spine::FUN_005d27e0(BlockT* src, float* dir, float* rot)
{
    if ((RefObj*)src != firstVertebra.mp && (RefObj*)src != lastVertebra.mp)
        return 0;
    float lo = src->minScale;
    float hi = src->maxScale;
    bool ok = false;
    float scale = src->scale * maxBlockScale;
    scale = scale > lo ? scale : lo;
    scale = scale < hi ? scale : hi;

    float e = halfWidth * 2.0f * 0.25f + halfWidth;
    float ox = dir[0] * e;
    float oy = dir[1] * e;
    float oz = dir[2] * e;
    float pos[3];
    pos[1] = (src->py + oy) + ((oy * rot[4] + oz * rot[7]) + ox * rot[1]);
    pos[2] = (src->pz + oz) + ((oy * rot[5] + oz * rot[8]) + ox * rot[2]);
    pos[0] = (ox + src->px) + ((oy * rot[3] + oz * rot[6]) + ox * rot[0]);

    Mat3 m9;
    const float* sm = src->m;
    m9.m[0] = (sm[0] * rot[0] + sm[1] * rot[3]) + sm[2] * rot[6];
    m9.m[1] = (sm[0] * rot[1] + sm[1] * rot[4]) + sm[2] * rot[7];
    m9.m[2] = (sm[0] * rot[2] + sm[1] * rot[5]) + sm[2] * rot[8];
    m9.m[3] = (sm[3] * rot[0] + sm[4] * rot[3]) + sm[5] * rot[6];
    m9.m[4] = (sm[3] * rot[1] + sm[4] * rot[4]) + sm[5] * rot[7];
    m9.m[5] = (sm[3] * rot[2] + sm[4] * rot[5]) + sm[5] * rot[8];
    m9.m[6] = (sm[6] * rot[0] + sm[7] * rot[3]) + sm[8] * rot[6];
    m9.m[7] = (sm[6] * rot[1] + sm[7] * rot[4]) + sm[8] * rot[7];
    m9.m[8] = (sm[6] * rot[2] + sm[7] * rot[5]) + sm[8] * rot[8];

    hkTransform xf;
    xf.rot[0][0] = 1.0f; xf.rot[0][1] = 0.0f; xf.rot[0][2] = 0.0f; xf.rot[0][3] = 0.0f;
    xf.rot[1][0] = 0.0f; xf.rot[1][1] = 1.0f; xf.rot[1][2] = 0.0f; xf.rot[1][3] = 0.0f;
    xf.rot[2][0] = 0.0f; xf.rot[2][1] = 0.0f; xf.rot[2][2] = 1.0f; xf.rot[2][3] = 0.0f;
    xf.pos[0] = pos[0]; xf.pos[1] = pos[1]; xf.pos[2] = pos[2]; xf.pos[3] = 0.0f;
    Mat3 m9c = m9;
    FUN_004a92c0(&m9c, &xf);
    FUN_005cd670(&xf, 0);

    HkRef* shape = CreateVertebraShape(scale);
    unsigned key = MakeVertKey(scale, (RefObj*)src == firstVertebra.mp ? -1 : (int)vertebrae.size);
    hkSimpleShapePhantom* ph =
        new (g_hkMemory->Alloc(0x130, 0x2e)) hkSimpleShapePhantom(shape, &xf, key);
    ph->memSize = 0x130;
    world->addPhantom(ph);
    ph->removeReference();

    PointCollector col;
    col.vt = vtbl_collector;
    col.earlyOut = 3.4028200e38f;
    col.data = col.buf;
    col.capFlags = 0x80000008;
    col.size = 0;
    ph->getClosestPoints(&col);
    int n = col.size;
    if (n > 0) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            CdPoint& pt = col.data[i];
            float d = pt.dist;
            if (d >= 0.0f) {
                count++;
            } else {
                float ad = d < 0.0f ? -d : d;
                if ((pt.a->flags & 0x1f) == 2 && (pt.b->flags & 0x1f) == 2) {
                    float ta = TimeObjValue(pt.a->timeObj);
                    float tb = TimeObjValue(pt.b->timeObj);
                    if (ad < ta && ad < tb)
                        count++;
                }
            }
        }
        if (count == n && n <= 1)
            ok = true;
    } else {
        ok = true;
    }
    world->removePhantom(ph);
    shape->release();

    BlockT* nb = 0;
    if (ok) {
        VertVal tmp;
        void* cookie = src->cookie;
        FUN_005ce060(&tmp, scale, &xf);
        BlockT* blk = new ("Editor", 0, 0, 0, 0) BlockT();
        nb = blk;
        float x = ((Cookie*)cookie)->F4adaa0(1, 1, 1);
        PhysW* pw = ((Cookie*)cookie)->F4ad450();
        void* wld = pw->World();
        nb->BuildBlock(pFC, inst104, pF0, wld, x, 1, 1, 1);
        nb->model;  // SP::ModelManager()
        if (nb->model)
            nb->model->f58 = 0.0f;
        nb->FUN_00448e90(pos, 0);
        nb->FUN_00449420(m9c.m, 0);
        nb->FUN_00440090(scale, 0);
        nb->FUN_00440020(scale, 1);
        unsigned k2 = (unsigned)nb;
        VertVal* v = vertebrae.Index(&k2);
        *v = tmp;
        if ((RefObj*)src == firstVertebra.mp) {
            nb->FUN_00438700((BlockT*)firstVertebra.mp);
            ((Cookie*)cookie)->F4abaf0(nb, 1);
            firstVertebra = (RefObj*)nb;
            firstHandle.mp->SetState(firstVertebra.mp);
        } else {
            ((BlockT*)lastVertebra.mp)->FUN_00438700(nb);
            ((Cookie*)cookie)->F4abaf0(nb, 1);
            lastVertebra = (RefObj*)nb;
            lastHandle.mp->SetState(lastVertebra.mp);
        }
        FUN_005d2790();
    }
    col.vt = vtbl_collector;
    if ((int)col.capFlags >= 0) {
        hkThreadMem* tm = (hkThreadMem*)TlsGetValue(g_tlsThreadMem);
        tm->deallocateChunk(col.data, (col.capFlags & 0x3fffffff) * 0x30, 0x14);
    }
    return nb;
}
// @ 0x005D3010
// Tear down one vertebra by key (callback-shaped signature, 6 trailing args unused).
bool Spine::FUN_005d3010(unsigned key, int, int, int, int, int, int)
{
    int n = (int)(vecEnd - vecBegin);
    int i = 0;
    if (n > 0) {
        do {
            ((Ob*)vecBegin[i])->FUN_0048a4c0();
            i++;
        } while (i < n);
    }
    if (dirty) {
        FUN_005d14a0();
        dirty = 0;
    }
    unsigned k = key;
    key = k;
    RbNode* endN = (RbNode*)((char*)this + 0xd0);
    RbNode* it = vertebrae.LowerFind(k);
    if (it != endN && vertebrae.Index(&key)) {
        FUN_005d2740(k);
        if (action) {
            world->removeAction(action);
            action->release();
            action = 0;
        }
        return true;
    }
    return false;
}

// @ 0x005D3100
// Total rigid-body mass over the vertebra chain.
float Spine::FUN_005d3100()
{
    float total = 0.0f;
    BlockT* nextB = (BlockT*)firstVertebra.mp;
    BlockT* b;
    while (b = nextB, b != 0) {
        nextB = 0;
        unsigned key = (unsigned)b;
        RbNode* it = vertebrae.LowerFind(key);
        VertVal* v;
        if (it != (RbNode*)((char*)this + 0xd0))
            v = vertebrae.Index(&key);
        else
            v = 0;
        total = ((hkBody*)v->body)->motion->getMass() + total;
        if (b != (BlockT*)lastVertebra.mp)
            nextB = (BlockT*)NextVertebra((Block*)b);
    }
    return total;
}

// @ 0x005D31B0
// Remove every vertebra body from the world and clear the spine's containers.
void Spine::FUN_005d31b0()
{
    FUN_005d14a0();
    FUN_005d1e70();
    char tmp;
    RbNode* anchor = vertebrae.Anchor();
    for (RbNode* n = vertebrae.anchorLeft; n != anchor; n = RBTreeIncrement(n))
        world->removeEntity(&tmp, n->body);
    vertebrae.Clear();
    if (firstHandle.mp) {
        firstHandle.mp->Reset();
        HandleObj* h = firstHandle.mp;
        if (h) { firstHandle.mp = 0; h->Release(); }
    }
    if (lastHandle.mp) {
        lastHandle.mp->Reset();
        HandleObj* h = lastHandle.mp;
        if (h) { lastHandle.mp = 0; h->Release(); }
    }
    RefObj* r = firstVertebra.mp;
    if (r) { firstVertebra.mp = 0; r->Release(); }
    r = lastVertebra.mp;
    if (r) { lastVertebra.mp = 0; r->Release(); }
    Ob* rt = route1;
    if (rt) {
        rt->FUN_005d59c0();
        operator_delete__(rt);
        route1 = 0;
    }
    rt = route2;
    if (rt) {
        rt->FUN_005d59c0();
        operator_delete__(rt);
        route2 = 0;
    }
}

// @ 0x005D3300
// Remove vertebra `b`: drop its Havok bodies, fix up first/last, release children, erase the map node.
void Spine::FUN_005d3300(BlockT* b)
{
    void* cookie = b->cookie;
    FUN_005d1e70();
    char tmp;
    unsigned key = (unsigned)b;
    VIter it;
    VIter* found = vertebrae.Find(&it, &key);
    VertVal* v;
    if (found->node != vertebrae.Anchor())
        v = vertebrae.Index(&key);
    else
        v = 0;
    RefObj* next = 0;
    if (v->constraint) {
        world->removeConstraint(&tmp, v->constraint);
        v->constraint = 0;
    }
    if (v->body)
        world->removeEntity(&tmp, v->body);
    v->body = 0;
    v->pad12 = 0;
    if ((RefObj*)b == firstVertebra.mp) {
        RefObj* n = (RefObj*)NextVertebra((Block*)b);
        if (n) {
            n->AddRef();
            next = n;
        }
        firstVertebra = next;
        firstHandle.mp->SetState(firstVertebra.mp);
    }
    if ((RefObj*)b == lastVertebra.mp) {
        RefObj* n2 = b->nextVertebra;
        if (n2 != next) {
            RefObj* old = next;
            if (n2) n2->AddRef();
            next = n2;
            if (old) old->Release();
        }
        lastVertebra = next;
        lastHandle.mp->SetState(lastVertebra.mp);
    }
    if (!next) {
        RefObj* n3 = b->nextVertebra;
        if (n3) {
            n3->AddRef();
            next = n3;
        }
    }
    FixedVec8 vec;
    vec.Fill(b->children);
    for (int i = (int)(vec.mpEnd - vec.mpBegin) - 1; i >= 0; i--) {
        AutoRef<BlockT> c(vec.mpBegin[i]);
        if (!((c.mp->flags >> 7) & 1))
            ((Ob*)next)->FUN_00438700(c.mp);
    }
    RbNode* y = vertebrae.LowerFind(key);
    if (y != vertebrae.Anchor()) {
        vertebrae.size--;
        RBTreeIncrement(y);
        RBTreeErase(y, vertebrae.Anchor());
        operator_delete__(y);
    }
    ((Ob*)cookie)->FUN_004acab0(b, 0);
    FUN_005d1f30();
    if (next) next->Release();
}

// @ 0x005D35C0
// Spine teardown (dtor body): reset vtables, release everything it holds.
void Spine::FUN_005d35c0()
{
    float a = f10;
    float c = f0c;
    vt0 = vtbl_13f89d4;
    vt8 = vtbl_13f89c4;
    g_015ba0d0 = c;
    g_015ba0d4 = a;
    if (hk1c) hk1c->removeReference();
    if (action) action->release();
    if (world) world->release();
    FUN_005d31b0();
    if (p18) p18->Delete(1);
    unsigned* arr = vecBegin;
    if (arr && arr[-1]) operator_delete__(arr);
    if (lastHandle.mp) lastHandle.mp->Release();
    if (firstHandle.mp) firstHandle.mp->Release();
    if (lastVertebra.mp) lastVertebra.mp->Release();
    if (firstVertebra.mp) firstVertebra.mp->Release();
    vertebrae.~VMap();
    vt8 = vtbl_cEditorResource;
    vt0 = vtbl_cContentValidationSummarizer;
}
