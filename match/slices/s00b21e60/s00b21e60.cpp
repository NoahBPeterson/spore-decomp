// Slice s00b21e60 (cl1_part #33): game-noun manager helpers, class-map serializer,
// paint-system dtor and friends.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE.
#include "types.h"
#include <new>

// ---- shared stubs ---------------------------------------------------------
typedef unsigned int uint;

struct IRefCount {
    virtual int AddRef();
    virtual int Release();
    virtual int Slot2();
    virtual void* Cast(unsigned id);
};

extern void* __cdecl SporeNew(unsigned size, const char* name, int a, int b, const char* file, int line);
extern void __cdecl operator_delete__(void* p);   // 0x00f47380

template <class T> struct ARC {
    T* p;
    ARC(T* q) : p(q) { if (p) p->AddRef(); }
    ARC(const ARC& o) : p(o.p) { if (p) p->AddRef(); }
    ~ARC() { if (p) p->Release(); }
    bool operator==(T* o) const { return p == o; }
    ARC& operator=(T* np) { T* old = p; if (old != np) { if (np) np->AddRef(); p = np; if (old) old->Release(); } return *this; }
};

// EASTL rbtree node/header: {right, left, parent, color}
struct RBNode { RBNode* right; RBNode* left; RBNode* parent; char color; };

// ---------------------------------------------------------------------------
// 0x00b21e60: read a count-prefixed (key, object) list from a serializer into a map
struct IFile;
struct IStream {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual IFile* GetFile();
};
struct ISerializer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void Pop();
    virtual IStream* GetStream();
    virtual void v9();
    virtual void ReadObject(unsigned id, IRefCount** out, int flag);
};
extern int __cdecl ReadInt32(IFile* f, void* dst, int count, int endian);   // 0x0093a780

struct ClsKV {
    int key; IRefCount* val;
    ClsKV(unsigned k, IRefCount* v) : key(k), val(v) { if (val) val->AddRef(); }
    ~ClsKV() { if (val) val->Release(); }
};
struct ClsNode : RBNode { int key; IRefCount* val; };
struct ClsInsRes { ClsNode* node; bool inserted; };
struct ClsMap {
    int pad0;
    RBNode anchor;
    uint size;
    void __thiscall DoNuke(RBNode* root);   // 0x00d0c930
    void __thiscall Insert(ClsInsRes* out, ClsKV* kv, bool bUnique);   // 0x00dd6740
};

// @ 0x00b21e60
void __cdecl ReadClassMap(ISerializer* ser, ClsMap* m)
{
    m->DoNuke(m->anchor.parent);
    m->anchor.right = &m->anchor;
    m->anchor.left = &m->anchor;
    m->anchor.parent = 0;
    m->anchor.color = 0;
    m->size = 0;

    uint count = 0;
    IFile* f0 = ser->GetStream()->GetFile();
    ReadInt32(f0, &count, 1, 0);
    for (uint i = 0; i < count; i++) {
        IRefCount* obj = 0;
        uint key;
        IFile* f1 = ser->GetStream()->GetFile();
        ReadInt32(f1, &key, 1, 0);
        ser->Pop();
        if (obj) { IRefCount* t = obj; obj = 0; t->Release(); }
        ser->ReadObject(0x17f243b, &obj, 0);
        ser->Pop();
        ClsInsRes res;
        {
            ClsKV kv(key, obj);
            m->Insert(&res, &kv, false);
        }
        if (!res.inserted) {
            IRefCount* old = res.node->val;
            if (obj != old) {
                if (obj) obj->AddRef();
                res.node->val = obj;
                if (old) old->Release();
            }
        }
        if (obj) obj->Release();
    }
    ser->Pop();
}

// ---------------------------------------------------------------------------
// 0x00b21fe0: rbtree DoInsertValue for the same map type
struct ClsKVCopy { int key; IRefCount* val; ClsKVCopy(const ClsKV& o); };
struct ClsIter { void* node; ClsIter(void* n) : node(n) {} };
struct ClsMap2 {
    int pad0;
    RBNode anchor;
    uint size;
    ClsIter __thiscall InsertValue(RBNode* pos, ClsKV* v, bool bForceLeft);
};
extern void __cdecl RBTreeInsert(RBNode* node, RBNode* parent, RBNode* anchor, int bLeft);
struct ClsNodeAlloc : RBNode {
    ClsKVCopy value;
};
inline void* operator new(size_t, ClsKVCopy* p) { return p; }

// @ 0x00b21fe0
ClsIter __thiscall ClsMap2::InsertValue(RBNode* pos, ClsKV* v, bool bForceLeft)
{
    int bLeft;
    if (!bForceLeft && pos != &anchor && !(v->key < ((ClsNode*)pos)->key)) bLeft = 1; else bLeft = 0;
    ClsNodeAlloc* n = (ClsNodeAlloc*)SporeNew(0x24, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    ::new (&n->value) ClsKVCopy(*v);
    RBTreeInsert(n, pos, &anchor, bLeft);
    size++;
    return ClsIter(n);
}

// ---------------------------------------------------------------------------
// 0x00b22060: SP vector swap (retail layout: begin, end, cap, allocator, inline buffer)
struct SPVecP {
    void** begin; void** end; void** cap; int alloc; void** inlineBuf;
    SPVecP(const SPVecP& o);   // 0x00b20c00
    ~SPVecP() { if ((int)((char*)cap - (char*)begin) > 1 && begin && begin != inlineBuf) operator_delete__(begin); }
    void __thiscall AssignRange(void** b, void** e);   // 0x009199c0
    void __thiscall swap(SPVecP& x);
};

// @ 0x00b22060
void __thiscall SPVecP::swap(SPVecP& x)
{
    if (&x.alloc == &alloc) {
        void** t;
        t = begin; begin = x.begin; x.begin = t;
        t = end;   end = x.end;     x.end = t;
        t = cap;   cap = x.cap;     x.cap = t;
    } else {
        SPVecP temp(*this);
        if (&x != this) AssignRange(x.begin, x.end);
        if (&temp != &x) x.AssignRange(temp.begin, temp.end);
    }
}

// ---------------------------------------------------------------------------
// cGameData base: two polymorphic bases, 0x34 bytes
struct GDBase0 { virtual void g0(); };
struct GDBase1 { virtual void g1(); };
struct cGameData : GDBase0, GDBase1 {
    char pad[0x2c];
    cGameData();
    virtual ~cGameData();
};

// 0x00b22100: Simulator::cVehicleGroupOrder::cVehicleGroupOrder
struct RBNodeI { RBNodeI* right; RBNodeI* left; RBNodeI* parent; int color; };
struct VGOTree {
    int alloc; RBNodeI anchor; uint size;
    VGOTree() : anchor() { anchor.left = &anchor; anchor.right = &anchor; anchor.parent = 0; *(char*)&anchor.color = 0; size = 0; }
};
struct VecP3 { int* a; int* b; int* c; VecP3() : a(0), b(0), c(0) {} };
// Non-polymorphic view of cGameData so the vtable stores name the image's vtables.
struct cGameDataNV {
    void* vp0; void* vp1; char pad[0x2c];
    cGameDataNV();   // 0x00b18660
};
extern void* vtbl_cVehicleGroupOrder[];    // 0x0145ee58
extern void* vtbl_cVehicleGroupOrder_1[];  // 0x0145ee44
struct VGOBase : cGameDataNV {
    VGOBase() { vp0 = vtbl_cVehicleGroupOrder; vp1 = vtbl_cVehicleGroupOrder_1; }
};
struct cVehicleGroupOrder : VGOBase {
    VGOTree tree;       // +0x34
    int f4c;
    VecP3 stars;        // +0x50 vector of ARC<cStarRecord>
    int f5c, f60;
    int arc64;          // +0x64
    char pad68[0x14];
    int f7c, f80, f84;  // vector of 0x178-byte elements
    cVehicleGroupOrder();
};

// @ 0x00b22100
cVehicleGroupOrder::cVehicleGroupOrder()
{
    arc64 = 0;
    f7c = 0; f80 = 0; f84 = 0;
}

// ---------------------------------------------------------------------------
// 0x00b22180: cVehicleGroupOrder body of dtor (members then base dtor)
struct Elem178 { char d[0x178]; void __thiscall Dtor(); };
struct StarVec { int a, b, c; ~StarVec(); };
struct TreeNuke {
    int pad; RBNode anchor; uint size;
    void __thiscall Nuke(RBNode* root);
    ~TreeNuke() { Nuke(anchor.parent); }
};
struct cVGOImpl : cGameData {
    TreeNuke tree;             // +0x34
    char pad4c[4];
    StarVec stars;             // +0x50
    char pad5c[8];
    IRefCount* arc64;          // +0x64
    char pad68[0x14];
    Elem178* begin7c;
    Elem178* end80;
    void __thiscall DtorBody();
};

// @ 0x00b22180
void __thiscall cVGOImpl::DtorBody()
{
    Elem178* last = end80;
    Elem178* e = begin7c;
    for (; e < last; e++) e->Dtor();
    if (begin7c && ((int*)begin7c)[-1]) operator_delete__(begin7c);
    IRefCount* a = arc64;
    if (a) a->Release();
    stars.~StarVec();
    tree.~TreeNuke();
    this->cGameData::~cGameData();
}

// ---------------------------------------------------------------------------
// 0x00b22210: function-static singleton, constructed on first use
struct StaticBase { StaticBase(int); };
struct StaticObj : StaticBase {
    virtual ~StaticObj();
    void* pData;       // +0x14
    int one;           // +0x18
    int zero1c;
    float fA;          // +0x20
    float fB;          // +0x24
    int zero28;
    StaticObj();
};
extern char DAT_0154df28[];
extern const float kFloat1, kFloat2;
StaticObj::StaticObj() : StaticBase(0)
{
    fA = kFloat1;
    fB = kFloat2;
    one = 1;
    pData = DAT_0154df28;
    zero1c = 0;
    zero28 = 0;
}

// @ 0x00b22210
StaticObj* GetStaticObj()
{
    static StaticObj inst;
    return &inst;
}

// ---------------------------------------------------------------------------
// cGameNounManager (retail layout, only the members these functions touch)
struct ListNode { ListNode* next; ListNode* prev; };

struct cNoun {                       // cGameData seen through its refcount base
    virtual int AddRef();            // 0
    virtual int Release();           // 1
    virtual int Slot2();             // 2
    virtual void* Cast(unsigned id); // 3
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual int GetType();           // 8  (+0x20)
    virtual bool Init(void* desc, void* a, void* b); // 9 (+0x24)
    char pad04[8];
    ListNode node;                   // +0x0c
    char pad14[0xc];
    bool removed;                    // +0x20
    static cNoun* FromNode(ListNode* n) { return n ? (cNoun*)((char*)n - 0xc) : 0; }
};

// vector<ARC<T>> with sp_vector_allocator (begin, end, cap)
struct NounVec {
    cNoun** begin; cNoun** end; cNoun** cap;
    void __thiscall DoInsertValue(cNoun** pos, ARC<cNoun>* v);   // 0x00aea5d0
    void push_back(ARC<cNoun>& v)
    {
        if (end < cap) {
            cNoun** p = end++;
            if (p) { *p = v.p; if (v.p) v.p->AddRef(); }
        } else {
            DoInsertValue(end, &v);
        }
    }
    void erase(cNoun** first, cNoun** last);
};
extern cNoun** __cdecl do_copy(cNoun** last, cNoun** end, cNoun** first);   // 0x006782c0
void NounVec::erase(cNoun** first, cNoun** last)
{
    cNoun** pos = do_copy(last, end, first);
    for (cNoun** q = pos; q < end; q++) if (*q) (*q)->Release();
    end -= (last - first);
}

struct StaticNounVec : NounVec {
    StaticNounVec() { begin = 0; end = 0; cap = 0; }
    ~StaticNounVec();   // 0x00ae6970
};
struct IMapFn { char d[0x1c]; void __thiscall Fn(void* other); };   // Fn: 0x00b21da0
struct cHerd;
struct cGameNounManager {
    char pad0[0x58];
    ARC<cNoun> mAvatarHerd;          // +0x58
    char pad5c[0x1c];
    ListNode mNouns;                 // +0x78
    NounVec mTempNouns;              // +0x80
    char pad8c[0xc];
    IMapFn mapA;                     // +0x98
    char mapB[0x10];                 // +0xb4
    char padc4[0x48];
    ListNode mPending;               // +0x10c

    void __thiscall FlushTemp();                  // 0xb206d0
    void __thiscall PostRemove(cNoun* n);         // 0xb20d30
    void __thiscall PostRemove2(cNoun* n);        // 0xb201a0
    cNoun* __thiscall CreateNoun(unsigned id);    // 0xb20c60
    void __thiscall RemoveNoun(cNoun* n);
    void __thiscall RemoveHerd(cNoun* herd);
    void __thiscall RemoveNounsOfType(int type);
    void __thiscall RemoveNounsWithInterface(unsigned id);
    void __thiscall Cleanup();
    void __thiscall Update();
    void __thiscall Dummy225b0();
    cNoun* __thiscall CreateAndInit(struct NounDesc* d, void* a2, void* a3, void* a4);
};

// @ 0x00b225d0
void __thiscall cGameNounManager::RemoveNoun(cNoun* n)
{
    n->removed = true;
    ARC<cNoun> a(n);
    mTempNouns.push_back(a);
    PostRemove(n);
    PostRemove2(n);
}

// @ 0x00b225b0
void __thiscall cGameNounManager::Dummy225b0()
{
    FlushTemp();
    mapA.Fn(mapB);
}

// @ 0x00b22930
struct cHerdI : cNoun {};
void __thiscall cGameNounManager::RemoveHerd(cNoun* herd)
{
    RemoveNoun(herd);
    if (mAvatarHerd == herd) mAvatarHerd = 0;
}

// @ 0x00b22650
void __thiscall cGameNounManager::RemoveNounsOfType(int type)
{
    static StaticNounVec found;
    for (cNoun* it = cNoun::FromNode(mNouns.next); it != cNoun::FromNode(&mNouns); it = cNoun::FromNode(it->node.next)) {
        if (it->GetType() == type) {
            ARC<cNoun> a(it);
            found.push_back(a);
        }
    }
    for (uint i = 0; i < (uint)(found.end - found.begin); i++) RemoveNoun(found.begin[i]);
    found.erase(found.begin, found.end);
}

// @ 0x00b227c0
void __thiscall cGameNounManager::RemoveNounsWithInterface(unsigned id)
{
    static StaticNounVec found;
    for (cNoun* it = cNoun::FromNode(mNouns.next); it != cNoun::FromNode(&mNouns); it = cNoun::FromNode(it->node.next)) {
        if (it->Cast(id)) {
            ARC<cNoun> a(it);
            found.push_back(a);
        }
    }
    for (uint i = 0; i < (uint)(found.end - found.begin); i++) RemoveNoun(found.begin[i]);
    found.erase(found.begin, found.end);
}

// ---------------------------------------------------------------------------
// 0x00b22bc0: for every noun implementing interface 0xce9f6639 run PostRemove
struct RawVec {
    cNoun** begin; cNoun** end; cNoun** cap;
    void __thiscall DoInsertValue(cNoun** pos, cNoun** v);   // 0x00b96600
    ~RawVec() { if (begin && ((int*)begin)[-1]) operator_delete__(begin); }
};

// @ 0x00b22bc0
void __thiscall cGameNounManager::Cleanup()
{
    FlushTemp();
    mapA.Fn(mapB);
    cNoun* it = cNoun::FromNode(mNouns.next);
    cNoun* last = cNoun::FromNode(&mNouns);
    RawVec v = { 0, 0, 0 };
    for (; it != last; it = cNoun::FromNode(it->node.next)) {
        if (it && it->Cast(0xce9f6639)) {
            cNoun* tmp = it;
            if (v.end < v.cap) {
                cNoun** p = v.end++;
                if (p) *p = it;
            } else {
                v.DoInsertValue(v.end, &tmp);
            }
        }
    }
    int n = v.end - v.begin;
    for (int i = 0; i < n; i++) PostRemove(v.begin[i]);
}

// ---------------------------------------------------------------------------
// 0x00b22cc0: create a noun from a descriptor and run its initialisation
struct IProps;
struct NounDesc { unsigned id; int pad[2]; IProps* props; };
struct cNounData {                    // result of Cast(0x1186577)
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual void SetA(void* a);       // 14 (0x38)
    virtual void SetB(void* b);       // 15 (0x3c)
    char pad04[0x54];
    unsigned f58;                     // +0x58
    char pad5c[0x15];
    bool b71;                         // +0x71
    char pad72[0x1a];
    float f8c;                        // +0x8c
};
extern bool __cdecl GetBoolProperty(IProps* p, unsigned id, bool* out);   // 0x00407190
extern bool __cdecl GetPropertyAsUint32(IProps* p, unsigned id, unsigned* out);   // 0x004af210
extern bool __cdecl GetFloatProperty(IProps* p, unsigned id, float* out);   // 0x0040cf10
extern const float kFloat1;

// @ 0x00b22cc0
cNoun* __thiscall cGameNounManager::CreateAndInit(NounDesc* d, void* a2, void* a3, void* a4)
{
    cNoun* n = CreateNoun(d->id);
    if (n) {
        cNounData* x = (cNounData*)n->Cast(0x1186577);
        if (x) {
            if (a3) x->SetA(a3);
            if (a4) x->SetB(a4);
            if (d->props) {
                bool b = false;
                if (GetBoolProperty(d->props, 0x3d08e15, &b)) x->b71 = b;
                unsigned u = 0;
                if (GetPropertyAsUint32(d->props, 0x93336c12, &u)) x->f58 = u;
                float f = kFloat1;
                if (GetFloatProperty(d->props, 0x4a0ca460, &f)) x->f8c = f;
            }
        }
        if (!n->Init(d, a2, a3)) {
            RemoveNoun(n);
            return 0;
        }
    }
    return n;
}

// ---------------------------------------------------------------------------
// 0x00b22e80 / 0x00b22ea0: small vector helpers on a holder object
struct SPVecARC { void** begin; void** end; void** cap; void __thiscall erase(void** f, void** l); void __thiscall DoInsertValue(void** pos, void** v); };
struct VecHolder { int pad; SPVecARC vec; };

// @ 0x00b22e80
void __cdecl ClearHolderVec(VecHolder* h)
{
    SPVecARC* v = &h->vec;
    v->erase(v->begin, v->end);
}

#define V4(n) virtual void n##a(); virtual void n##b(); virtual void n##c(); virtual void n##d();
struct IObj47 {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual IObj47* Cast(unsigned id);   // 3
    V4(a) V4(b) V4(c) V4(d) V4(e) V4(f) V4(g) V4(h) V4(i) V4(j)   // 4..43
    virtual void p44(); virtual void p45(); virtual void p46();
    virtual void AddRefX();              // 47 (+0xbc)
    virtual void ReleaseX();             // 48 (+0xc0)
};
struct VecHolder2 { int pad; struct { IObj47** begin; IObj47** end; IObj47** cap;
    void __thiscall DoInsertValue(IObj47** pos, IObj47** v); } vec; };

// @ 0x00b22ea0
void __cdecl PushBackCast(VecHolder2* h, IObj47* obj)
{
    IObj47* x = obj ? obj->Cast(0x1186577) : 0;
    if (x) x->AddRefX();
    IObj47** p = h->vec.end;
    if (p < h->vec.cap) {
        h->vec.end = p + 1;
        if (p) {
            *p = x;
            if (x) x->AddRefX();
        }
    } else {
        h->vec.DoInsertValue(p, &x);
    }
    if (x) x->ReleaseX();
}

// ---------------------------------------------------------------------------
// 0x00b222a0: look up every id from two freshly built sets in the global class registry
struct SetNode : RBNode { int key; };
struct SetMap {
    int pad;
    RBNode anchor;
    uint size;
    int pad2;
    SetMap() : anchor() { anchor.right = &anchor; anchor.left = &anchor; anchor.parent = 0; anchor.color = 0; size = 0; }
    ~SetMap() { Free(anchor.parent); }
    void Free(RBNode* p)
    {
        while (p) {
            DoNuke(p->right);
            RBNode* l = p->left;
            operator_delete__(p);
            p = l;
        }
    }
    void __thiscall DoNuke(RBNode* p);   // 0x009a9600
};
extern RBNode g_ClassRegistry;       // 0x01568550 (anchor of the registry map)
extern char g_Logger[];              // 0x01568584
extern void __cdecl LogError(void* logger, const char* fmt, ...);   // 0x00b21060
extern RBNode* __cdecl RBTreeIncrement(RBNode* n);   // 0x00921580
extern void __stdcall BuildClassSets(SetMap* a, SetMap* b);   // 0x00b211e0

static __forceinline void CheckRegistered(SetMap& m)
{
    for (RBNode* it = m.anchor.left; it != &m.anchor; it = RBTreeIncrement(it)) {
        int key = ((SetNode*)it)->key;
        RBNode* best = &g_ClassRegistry;
        RBNode* cur = g_ClassRegistry.parent;
        while (cur) {
            if (!(((SetNode*)cur)->key < key)) { best = cur; cur = cur->left; }
            else cur = cur->right;
        }
        if (best == &g_ClassRegistry || key < ((SetNode*)best)->key)
            LogError(g_Logger, "clsid 0x%08x", key);
    }
}

// @ 0x00b222a0
void ValidateClassSets()
{
    SetMap x;
    SetMap y;
    BuildClassSets(&x, &y);
    CheckRegistered(x);
    CheckRegistered(y);
}

// ---------------------------------------------------------------------------
// 0x00b22440: Skinner::PaintSystem destructor body
extern void* vtbl_PaintSystemA[];   // 0x0145ef10
extern void* vtbl_PaintSystemB[];   // 0x0145eec0
extern void* vtbl_PaintSystemC[];   // 0x0145eeb8
extern void* vtbl_PaintSystem[];   // 0x013eb394
struct PS_Tree {
    void __thiscall Nuke(RBNode* root);   // 0x00d0c930
};
struct PS_Tree2 {
    void __thiscall Nuke(RBNode* root);   // 0x009a9600
};
struct PS_Vec {
    void __thiscall Dtor();   // 0x00ae6970
};
struct PS_ListBase {
    void __thiscall Dtor();   // 0x00620230
};
struct PS_RenderJobs {
    void __thiscall Clear();   // 0x0075f3f0
};
struct PS_Hash {
    void __thiscall Clear(int a, int b);   // 0x00b20a50
};
struct PS_Gonzago {
    void __thiscall Dtor();   // 0x00b5b9a0
};
extern void __cdecl RemoveHandler(int h, int a, int b, int c, int d);   // 0x00571db0
template <class T> static inline T* At(void* base, int off) { return (T*)((char*)base + off); }
template <class T> static inline T& Fld(void* base, int off) { return *(T*)((char*)base + off); }

// @ 0x00b22440
void __fastcall PaintSystem_DtorBody(void* self)
{
    Fld<void**>(self, 0) = vtbl_PaintSystemA;
    Fld<void**>(self, 4) = vtbl_PaintSystemB;
    Fld<void**>(self, 8) = vtbl_PaintSystemC;
    At<PS_RenderJobs>(self, 0x10c)->Clear();
    At<PS_Tree>(self, 0xec)->Nuke(Fld<RBNode*>(self, 0xf8));
    At<PS_Tree>(self, 0xd0)->Nuke(Fld<RBNode*>(self, 0xdc));
    At<PS_Tree2>(self, 0xb4)->Nuke(Fld<RBNode*>(self, 0xc0));
    At<PS_Tree2>(self, 0x98)->Nuke(Fld<RBNode*>(self, 0xa4));
    At<PS_Vec>(self, 0x80)->Dtor();
    At<PS_ListBase>(self, 0x78)->Dtor();
    if (Fld<IRefCount*>(self, 0x74)) Fld<IRefCount*>(self, 0x74)->Release();
    if (Fld<IRefCount*>(self, 0x70)) Fld<IRefCount*>(self, 0x70)->Release();
    At<PS_Vec>(self, 0x5c)->Dtor();
    if (Fld<IRefCount*>(self, 0x58)) Fld<IRefCount*>(self, 0x58)->Release();
    if (Fld<IRefCount*>(self, 0x54)) Fld<IRefCount*>(self, 0x54)->Release();
    int h = Fld<int>(self, 0x40);
    if (h) {
        Fld<int>(self, 0x40) = 0;
        RemoveHandler(h, Fld<int>(self, 0x44), Fld<int>(self, 0x48), Fld<int>(self, 0x4c), Fld<int>(self, 0x50));
    }
    PS_Hash* hash = At<PS_Hash>(self, 0x20);
    hash->Clear(Fld<int>(self, 0x24), Fld<int>(self, 0x28));
    Fld<uint>(self, 0x2c) = 0;
    if (Fld<uint>(self, 0x28) > 1) operator_delete__(Fld<void*>(self, 0x24));
    At<PS_Gonzago>(self, 4)->Dtor();
    Fld<void**>(self, 0) = vtbl_PaintSystem;
}

// ---------------------------------------------------------------------------
// 0x00b22960: per-frame processing of the pending-data list
extern void* kSysGui;
struct SysGui { void __thiscall SetSerializer(); };   // 0x00c2e4e0
struct ModelMgr {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6();
    virtual IRefCount* Lookup(unsigned id);   // 7 (+0x1c)
};
extern ModelMgr* __cdecl GetModelManager();   // 0x0067dd80
struct IPending {                       // result of Cast(0x1186577)
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12();
    virtual float f13();                // +0x34
    virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void s22(); virtual void s23(); virtual void s24();
    virtual void Apply(void* data, float f); // 25 (+0x64)
    virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
    virtual void s34(); virtual void s35();
    virtual bool HasCtx();              // 36 (+0x90)
    virtual void s37(); virtual void s38(); virtual void s39();
    virtual bool BindCtx(IRefCount* ctx); // 40 (+0xa0)
    virtual void s41(); virtual void s42();
    virtual struct PInfo* GetInfo();    // 43 (+0xac)
    char pad04[0x4c];
    unsigned flags;                     // +0x50
};
struct PInfo { int pad; unsigned f4; char pad8[0x68]; char data[1]; };  // data at +0x70
struct PNode { PNode* next; PNode* prev; IRefCount* value; };
struct UIMessage {
    void __thiscall Destruct();   // 0x00421cf0
    void** vptr; int rc; int d0; int padc; void* d1; char pad14[0x1c]; int id; char pad34[4]; int flags;
};
extern void* vtbl_UIMessageBase[];   // 0x013eb90c
extern void* vtbl_UIMessage[];   // 0x013eb844
struct MsgServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void Post(unsigned type, UIMessage* m, int flag);   // 5 (+0x14)
};
extern MsgServer* __cdecl GetMessageServer();   // 0x0067dcc0

struct cGNM2 {
    char pad[0x80];
    NounVec mTempNouns;     // +0x80
    char pad8c[0x80];
    PNode mPending;         // +0x10c
    void __thiscall FlushTemp();   // 0x00b206d0
    void __thiscall ProcessPending();
};

// @ 0x00b22960
void __thiscall cGNM2::ProcessPending()
{
    ((SysGui*)0x0167c988)->SetSerializer();
    IRefCount* ctx = GetModelManager()->Lookup(0xeb9968);
    if (ctx) ctx->AddRef();
    PNode* node = mPending.next;
    while (node != &mPending) {
        IRefCount* obj = node->value;
        bool keep = false;
        IPending* d = 0;
        if (obj) d = (IPending*)obj->Cast(0x1186577);
        PInfo* info = 0;
        bool erase = false;
        if (!d) {
            erase = true;
        } else {
            info = d->GetInfo();
            if (!info) {
                if (!d->HasCtx() || !d->BindCtx(ctx) || !(info = d->GetInfo())) erase = true;
            }
        }
        if (!erase) {
            unsigned fl = d->flags;
            if (!(fl & 0x20)) {
                if (info->f4 >> 14 & 1) {
                    d->flags = fl & ~0x10u;
                    d->Apply(info->data, d->f13());
                    keep = false;
                } else {
                    d->flags = fl | 0x10;
                    keep = true;
                }
            }
            if (info && (d->flags & 0x8000)) {
                if ((info->f4 >> 14 & 1) && !(info->f4 >> 18 & 1)) {
                    d->Apply(info->data, d->f13());
                    erase = true;
                } else {
                    node = node->next;
                    continue;
                }
            } else if (keep) {
                node = node->next;
                continue;
            } else {
                erase = true;
            }
        }
        // erase the node and broadcast a removal message
        PNode* next = node->next;
        PNode* dead = next->prev;
        dead->prev->next = dead->next;
        dead->next->prev = dead->prev;
        if (dead->value) dead->value->Release();
        operator_delete__(dead);
        UIMessage msg;
        msg.id = 0;
        msg.rc = 0;
        msg.vptr = vtbl_UIMessageBase;
        msg.vptr = vtbl_UIMessage;
        msg.flags = 0;
        msg.d0 = 3;
        msg.d1 = obj;
        GetMessageServer()->Post(0x1a0219e, &msg, 0);
        msg.Destruct();
        node = next;
    }
    FlushTemp();
    mTempNouns.erase(mTempNouns.begin, mTempNouns.end);
    if (ctx) ctx->Release();
}
