// Batch w1g5 slice s0069e3a0: SP::cObjectDatabase open/has-key + SP::cCOMSerializer
// (rbtree of class/ID info) and the cCOMSerializer ctor/reset/dtor.
// Region is /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-.
#include "types.h"
#include <new>

typedef void* VP;

extern "C" void* EASTL_allocator_allocate(unsigned size, const char* name, int, int, const char* file, int line); // 0x00f473a0
extern "C" void  EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* operator_new6(unsigned size, const char* name, int, int, int, int);
extern "C" void* FUN_00920090(); // 0x00920090 returns the object-factory singleton
extern "C" void  FUN_0093a780(void* io, void* p, int n, int f);
extern "C" void  FUN_00932da0();
extern "C" void  FUN_004c0410(int);
extern "C" void  FUN_0069e880(void*);
extern "C" void  FUN_005766e0(void*);
extern "C" void  FUN_0069f160_reset(void*);
extern "C" void  FUN_0069eea0();

extern char g_vtbl_1408750[];
extern char g_vtbl_1408728[];
extern char g_vtbl_14095cc[];
extern char g_vtbl_13eb938[];
extern char g_vtbl_13ec458[];
extern char g_vtbl_1408550[];
extern char g_vtbl_14085dc[];
extern char g_vtbl_1408598[];
extern char g_vtbl_14085f0[];
extern char g_vtbl_1408668[];
extern char g_vtbl_140862c[];

static const char kEastlAllocH[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// ===========================================================================
// rbtree node / tree used by cCOMSerializer.
// ===========================================================================
struct RBNode {
    RBNode* mpNodeLeft;     // +0
    RBNode* mpNodeRight;    // +4
    RBNode* mpNodeParent;   // +8
    unsigned char mColor;   // +0xc
    char pad0[3];
    // value area starts at +0x10
};

struct P550; struct P_ecc0;
struct Iter { RBNode* n; Iter() {} Iter(RBNode* p) : n(p) {} Iter(const Iter& o) : n(o.n) {} };

// EASTL rbtree: the anchor lives at +4 (after the allocator/compare pointer).
struct Tree {
    void* mAllocator;       // +0
    RBNode mAnchor;         // +4
    unsigned int mnSize;    // +0x14
    int pad2;               // +0x18
    Tree() : mAnchor() {
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
    ~Tree();
    RBNode* AllocA(P550* src);
    RBNode* CopyA(RBNode* pNode, RBNode* pParent);
    RBNode* AllocB(P_ecc0* src);
    RBNode* CopyB(RBNode* pNode, RBNode* pParent);
    void Nuke(RBNode* pNode);
    RBNode** find(RBNode** out, const unsigned* key);                 // 0x00e5c780
    struct IterBool* InsertID(struct IterBool* out, struct IDPair* v, struct Tag t); // 0x0069e770
    Iter* InsertHint(Iter* out, Iter pos, struct IDPair* v, struct Tag t); // 0x0069e8f0
    IterBool* InsertClass(IterBool* out, struct ClassPair* v, Tag t); // 0x0069eea0
    void* IndexID(const unsigned* key);                               // operator[]
};
struct Tag {};
struct IterBool { RBNode* it; bool ok; };
// cIDInfo: AutoRefCount of a serializable (AddRef = vslot 0, Release = vslot 1)
struct AR {
    void* p;
    AR() : p(0) {}
    AR(const AR& o) : p(o.p) { if (p) ((void(__thiscall*)(void*))(*(void***)p)[0])(p); }
    ~AR() { if (p) ((void(__thiscall*)(void*))(*(void***)p)[1])(p); }
    AR& operator=(void* v);                                           // 0x00b5f950
};
struct IDPair { unsigned first; AR second; IDPair(unsigned k, const AR& a) : first(k), second(a) {} };

// ---------------------------------------------------------------------------
// 0x0069e550  allocate an 8-byte-value node (pair<key,AutoRefCount>)
// ---------------------------------------------------------------------------
struct P550 { int key; void* obj; };
// @ 0x0069e550
RBNode* Tree::AllocA(P550* src)
{
    RBNode* n = (RBNode*)EASTL_allocator_allocate(0x18, "App", 0, 0, kEastlAllocH, 0xd1);
    *(int*)((char*)n + 0x10) = src->key;
    void* o = src->obj;
    *(void**)((char*)n + 0x14) = o;
    if (o)
        ((void(__thiscall*)(void*))(*(void***)o)[0])(o);
    return n;
}

// ---------------------------------------------------------------------------
// 0x0069e6c0  rbtree<...cFeedbackEvent...>::DoCopySubtree
// ---------------------------------------------------------------------------
// @ 0x0069e6c0
RBNode* Tree::CopyA(RBNode* pNode, RBNode* pParent)
{
    RBNode* pNew = AllocA((P550*)((char*)pNode + 0x10));
    pNew->mpNodeLeft = 0;
    pNew->mpNodeRight = 0;
    pNew->mpNodeParent = pParent;
    pNew->mColor = pNode->mColor;
    if (pNode->mpNodeLeft)
        pNew->mpNodeLeft = CopyA(pNode->mpNodeLeft, pNew);
    RBNode* pPrev = pNew;
    for (RBNode* p = pNode->mpNodeRight; p; p = p->mpNodeRight) {
        RBNode* pNodeNew = AllocA((P550*)((char*)p + 0x10));
        pNodeNew->mpNodeLeft = 0;
        pNodeNew->mpNodeRight = 0;
        pNodeNew->mpNodeParent = pPrev;
        pNodeNew->mColor = p->mColor;
        pPrev->mpNodeRight = pNodeNew;
        if (p->mpNodeLeft)
            pNodeNew->mpNodeLeft = CopyA(p->mpNodeLeft, pNodeNew);
        pPrev = pNodeNew;
    }
    return pNew;
}

// ---------------------------------------------------------------------------
// 0x0069ecc0  allocate a 0x38-byte cClassInfo node
// ---------------------------------------------------------------------------
struct P_ecc0 { int a; int b; int c; char rest[0x28]; };
// @ 0x0069ecc0
RBNode* Tree::AllocB(P_ecc0* src)
{
    RBNode* n = (RBNode*)EASTL_allocator_allocate(0x38, "App", 0, 0, kEastlAllocH, 0xd1);
    *(int*)((char*)n + 0x10) = src->a;
    *(int*)((char*)n + 0x14) = src->b;
    *(int*)((char*)n + 0x18) = src->c;
    FUN_0069e880(src->rest);
    return n;
}

// ---------------------------------------------------------------------------
// 0x0069edb0  rbtree<...cClassInfo...>::DoCopySubtree
// ---------------------------------------------------------------------------
// @ 0x0069edb0
RBNode* Tree::CopyB(RBNode* pNode, RBNode* pParent)
{
    RBNode* pNew = AllocB((P_ecc0*)((char*)pNode + 0x10));
    pNew->mpNodeLeft = 0;
    pNew->mpNodeRight = 0;
    pNew->mpNodeParent = pParent;
    pNew->mColor = pNode->mColor;
    if (pNode->mpNodeLeft)
        pNew->mpNodeLeft = CopyB(pNode->mpNodeLeft, pNew);
    RBNode* pPrev = pNew;
    for (RBNode* p = pNode->mpNodeRight; p; p = p->mpNodeRight) {
        RBNode* pNodeNew = AllocB((P_ecc0*)((char*)p + 0x10));
        pNodeNew->mpNodeLeft = 0;
        pNodeNew->mpNodeRight = 0;
        pNodeNew->mpNodeParent = pPrev;
        pNodeNew->mColor = p->mColor;
        pPrev->mpNodeRight = pNodeNew;
        if (p->mpNodeLeft)
            pNodeNew->mpNodeLeft = CopyB(p->mpNodeLeft, pNodeNew);
        pPrev = pNodeNew;
    }
    return pNew;
}

// ---------------------------------------------------------------------------
// 0x0069ee60  rbtree<...cClassInfo...>::DoNukeSubtree
// ---------------------------------------------------------------------------
extern "C" void FUN_d0c930(void* value, void* arg);
// @ 0x0069ee60
void Tree::Nuke(RBNode* pNode)
{
    while (pNode) {
        Nuke(pNode->mpNodeLeft);
        RBNode* pRight = pNode->mpNodeRight;
        FUN_d0c930((char*)pNode + 0x1c, *(void**)((char*)pNode + 0x28));
        EASTL_allocator_deallocate(pNode);
        pNode = pRight;
    }
}

// ---------------------------------------------------------------------------
// 0x0069f0b0  cCOMSerializer destructor body
// ---------------------------------------------------------------------------
struct CComSer {
    VP vt0;                 // +0
    int mRefCount;          // +4
    VP vt8;                 // +8
    unsigned char flag_c;   // +0xc
    char pad0[3];
    Tree mTree1;            // +0x10  (mClassIDMapForWriting)
    Tree mTree2;            // +0x2c  (mClassIDMap)
    int mMode;              // +0x48
    unsigned char b4c;      // +0x4c
    unsigned char b4d;      // +0x4d
    char pad2[2];
    void* p50;              // +0x50
    void* p54;              // +0x54
    void* p58;              // +0x58
    void* p5c;              // +0x5c
    void dtor();
    void reset();
};

// @ 0x0069f0b0
void CComSer::dtor()
{
    vt0 = g_vtbl_1408750;
    vt8 = g_vtbl_1408728;
    void* a = p54;
    if (a && *(int*)((char*)a - 4))
        EASTL_allocator_deallocate(a);
    if (p50)
        ((void(__thiscall*)(void*))(*(void***)p50)[4 / 4])(p50);
    mTree2.Nuke(mTree2.mAnchor.mpNodeParent);
    mTree1.Nuke(mTree1.mAnchor.mpNodeParent);
    vt8 = g_vtbl_13eb938;
    vt0 = g_vtbl_13ec458;
}

// ---------------------------------------------------------------------------
// 0x0069f160  cCOMSerializer::reset
// ---------------------------------------------------------------------------
// @ 0x0069f160
void CComSer::reset()
{
    flag_c = 0;
    mTree1.Nuke(mTree1.mAnchor.mpNodeParent);
    mTree1.mAnchor.mpNodeLeft = &mTree1.mAnchor;
    mTree1.mAnchor.mpNodeRight = &mTree1.mAnchor;
    mTree1.mAnchor.mpNodeParent = 0;
    mTree1.mAnchor.mColor = 0;
    mTree1.mnSize = 0;
    mTree2.Nuke(mTree2.mAnchor.mpNodeParent);
    mTree2.mAnchor.mpNodeLeft = &mTree2.mAnchor;
    mTree2.mAnchor.mpNodeRight = &mTree2.mAnchor;
    mTree2.mAnchor.mpNodeParent = 0;
    mTree2.mAnchor.mColor = 0;
    mTree2.mnSize = 0;
    b4c = 0;
    b4d = 0;
    void* p = p50;
    if (p) {
        p50 = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[4 / 4])(p);
    }
}

// ---------------------------------------------------------------------------
// 0x0069f940  thunk: reset the serializer at this-8, return true
// ---------------------------------------------------------------------------
struct F940 { bool f(); };
bool F940::f()
{
    ((CComSer*)((char*)this - 8))->reset();
    return true;
}

// ---------------------------------------------------------------------------
// Remaining functions: behaviour-only reconstructions (see bookkeeping).
// ---------------------------------------------------------------------------
extern "C" void  FUN_0093a700(void*, void*, int, int);
extern "C" void  FUN_00f47380(void*);

// 0x0069e3a0 / 0x0069e470 / 0x0069e5d0: SP::cObjectDatabase members
typedef void (__thiscall *VFn0)(void*);
struct ReleaseGuard {
    void* p;
    ReleaseGuard(void* q) : p(q) { if (q) ((VFn0)(*(void***)q)[4 / 4])(q); }
    ~ReleaseGuard() { ((VFn0)(*(void***)p)[8 / 4])(p); }
};
struct ResKey { int a, b, c; };
extern "C" ResKey* FUN_00ac0d80(ResKey* first, ResKey* last, const ResKey* key); // 0x00ac0d80 eastl::find<Key*,Key>
struct DbVt { void* pad[0x30 / 4]; };
struct cObjDB {
    char pad0[0x18];
    void** mpDatabase;      // +0x18
    bool OpenIStream(int a, void** out);
    bool OpenOStream(int a, void** out, int b);
    bool HasKey(const ResKey* key);
};

// @ 0x0069e3a0
bool cObjDB::OpenIStream(int a, void** out)
{
    *out = 0;
    void* p = operator_new6(0x1c, "App", 0, 0, 0, 0);
    if (p) {
        *(void**)((char*)p + 4) = 0;
        *(void**)((char*)p + 8) = g_vtbl_1408550;
        *(void**)p = g_vtbl_14085dc;
        *(void**)((char*)p + 8) = g_vtbl_1408598;
        *(unsigned char*)((char*)p + 0xc) = 1;
        *(void**)((char*)p + 0x10) = 0;
        *(void**)((char*)p + 0x14) = 0;
        *(void**)((char*)p + 0x18) = 0;
    }
    ReleaseGuard g(p);
    void* sub = (char*)p + 8;
    char ok = ((char(__thiscall*)(void*, void*, int))(*(void***)sub)[0x10 / 4])(sub, this, a);
    if (ok) {
        *out = sub;
        ((VFn0)(*(void***)sub)[0])(sub);
    }
    return *out != 0;
}

// @ 0x0069e470
bool cObjDB::OpenOStream(int a, void** out, int b)
{
    *out = 0;
    void* p = operator_new6(0x18, "App", 0, 0, 0, 0);
    if (p) {
        *(void**)((char*)p + 4) = 0;
        *(void**)((char*)p + 8) = g_vtbl_14085f0;
        *(void**)p = g_vtbl_1408668;
        *(void**)((char*)p + 8) = g_vtbl_140862c;
        *(unsigned char*)((char*)p + 0xc) = 0;
        *(void**)((char*)p + 0x10) = 0;
        *(unsigned char*)((char*)p + 0x14) = 1;
    }
    ReleaseGuard g(p);
    void* sub = (char*)p + 8;
    char ok = ((char(__thiscall*)(void*, void*, int, int))(*(void***)sub)[0x10 / 4])(sub, this, a, b);
    if (ok) {
        *out = sub;
        ((VFn0)(*(void***)sub)[0])(sub);
    }
    return *out != 0;
}

struct KeyVec {
    ResKey* b; ResKey* e; ResKey* c;
    ~KeyVec() { if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b); }
};

// @ 0x0069e5d0
bool cObjDB::HasKey(const ResKey* key)
{
    KeyVec v = { 0, 0, 0 };
    void* db = mpDatabase;
    ((void(__thiscall*)(void*, KeyVec*, int))(*(void***)db)[0x30 / 4])(db, &v, 0);
    return FUN_00ac0d80(v.b, v.e, key) != v.e;
}

// 0x0069e9e0 onGetSPSerializable, 0x0069eb60 map operator[]
// @ 0x0069eb60
void* Tree::IndexID(const unsigned* key)
{
    RBNode* lb = &mAnchor;
    RBNode* cur = mAnchor.mpNodeParent;
    while (cur) {
        if (*(unsigned*)((char*)cur + 0x10) >= *key) {
            lb = cur;
            cur = cur->mpNodeRight;
        } else {
            cur = cur->mpNodeLeft;
        }
    }
    if (lb == &mAnchor || *key < *(unsigned*)((char*)lb + 0x10)) {
        AR tmp;
        IDPair v(*key, tmp);
        Iter r;
        InsertHint(&r, Iter(lb), &v, Tag());
        __assume(v.second.p == 0);
        __assume(tmp.p == 0);
        lb = r.n;
    }
    return (char*)lb + 0x14;
}

struct F_e9e0 { char pad[0x10]; Tree t1; Tree t2; int mMode; bool f(void** out, unsigned instanceID, unsigned classID); };
// @ 0x0069e9e0
bool F_e9e0::f(void** out, unsigned instanceID, unsigned classID)
{
    *out = 0;
    RBNode* itC;
    t2.find(&itC, &classID);
    if (itC != &t2.mAnchor) {
        Tree* sub = (Tree*)((char*)itC + 0x1c);
        RBNode* itI;
        sub->find(&itI, &instanceID);
        if (itI == &sub->mAnchor) {
            void* fac = FUN_00920090();
            *out = ((void*(__thiscall*)(void*, unsigned, int, int, int))(*(void***)fac)[0x20 / 4])(fac, classID, 0x179c807, 0, 0);
            if (!*out)
                return false;
            AR tmp;
            IDPair v(instanceID, tmp);
            IterBool r;
            sub->InsertID(&r, &v, Tag());
            __assume(v.second.p == 0);
            __assume(tmp.p == 0);
            ++*(int*)((char*)itC + 0x18);
            ++mMode;
            ((AR*)((char*)r.it + 0x14))->operator=(*out);
            ((void(__thiscall*)(void*))(*(void***)*out)[0])(*out);
            return true;
        }
        *out = *(void**)((char*)itI + 0x14);
        ((void(__thiscall*)(void*))(*(void***)*out)[0])(*out);
        return true;
    }
    return false;
}

// 0x0069ec20  load one class object blob (behaviour)
struct F_ec20 {
    bool f(int* io, unsigned index);
    bool g(void* io, unsigned maxLen, unsigned* outCRC);   // 0x0069ec20 (3-arg form, as LoadClassObjects calls it)
};
// @ 0x0069ec20
bool F_ec20::f(int* io, unsigned index)
{
    if (index > 0xf4240)
        return false;
    void* p = ((void*(__thiscall*)(void*))(*(void***)io)[0x18 / 4])(io);
    ((void(__thiscall*)(void*, int))(*(void***)p)[0x24 / 4])(p, 0);
    FUN_004c0410(index + 1);
    p = ((void*(__thiscall*)(void*))(*(void***)io)[0x18 / 4])(io);
    int r = ((int(__thiscall*)(void*, void*, unsigned))(*(void***)p)[0x30 / 4])(p, this, index);
    bool ok = r != 0;
    if (ok) {
        *(unsigned char*)((char*)this + index) = 0;
        FUN_00932da0();
    }
    p = ((void*(__thiscall*)(void*))(*(void***)io)[0x18 / 4])(io);
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[0x28 / 4])(p, 0, 0);
    return ok;
}

// 0x0069f1d0  SP::cCOMSerializer::LoadClassObjects (thiscall on the cICOMSerializer base, real object = this-8)
#define VT(o) (*(void***)(o))
#define VC0(R, o, s)             ((R(__thiscall*)(void*))VT(o)[s])(o)
#define VC1(R, A, o, s, a)       ((R(__thiscall*)(void*, A))VT(o)[s])(o, a)
#define VC2(R, A, B, o, s, a, b) ((R(__thiscall*)(void*, A, B))VT(o)[s])(o, a, b)

extern const unsigned kMaxCRCDataLength;   // 0x014084ec == 1000000
RBNode* RBTreeIncrement(RBNode* p);        // 0x00921580

struct SRef {   // intrusive ref to a stream/serializable: AddRef = vslot 0, Release = vslot 1
    void* p;
    SRef() : p(0) {}
    ~SRef() { if (p) VC0(void, p, 1); }
    void reset() { if (p) { void* o = p; p = 0; VC0(void, o, 1); } }
};
struct Key3 { unsigned a, b, c; };

struct IDMap {      // eastl::map<uint, cIDInfo>, 0x1c bytes
    void* pad;
    RBNode* l; RBNode* r; RBNode* par; unsigned char col; char p3[3]; unsigned size; int p18;
    IDMap() { l = (RBNode*)&l; r = (RBNode*)&l; par = 0; col = 0; size = 0; }
    IDMap(const IDMap& o);                     // 0x0069e880
    ~IDMap() { NukeSubtree(par); }
    void NukeSubtree(RBNode* root);            // 0x00d0c930
};
struct ClassInfo { unsigned read, inst; IDMap map; };
struct ClassPair {  // pair<const uint, cClassInfo>
    unsigned first; unsigned read, inst; IDMap map;
    ClassPair(unsigned k, const ClassInfo& c) : first(k), read(c.read), inst(c.inst), map(c.map) {}
};

// Full-object view: 0x0069f840's real `this` is the cICOMSerializer base (this+8).
struct CS8 {
    char pad0[0x24];
    Tree t2;                // +0x24 (real +0x2c) mClassIDMap
    int mMode;              // +0x40
    unsigned char loaded;   // +0x44 (real +0x4c)
    char pad1[3];
    void* db;               // +0x48 (real +0x50) cObjectDatabase
    bool LoadClassObjects(void* progress);
};

static inline void ReadI32(void* stream, void* dst)
{
    FUN_0093a780(VC0(void*, VC0(void*, stream, 8), 6), dst, 1, 0);
}

// @ 0x0069f1d0
bool CS8::LoadClassObjects(void* progress)
{
    bool ok = false;
    if (!loaded) {
        SRef s1;
        Key3 k1 = { 0x0179d304u, 0x0179d310u, 0 };
        if (VC2(char, Key3*, void**, db, 6, &k1, &s1.p)) {
            VC1(void, void*, s1.p, 16, progress);
            ok = true;
            int version, count, third;
            ReadI32(s1.p, &version);
            ReadI32(s1.p, &count);
            ReadI32(s1.p, &third);
            if (version == 1) {
                while (count) {
                    --count;
                    unsigned classID;
                    ReadI32(s1.p, &classID);
                    ClassInfo ci;
                    ClassPair v(classID, ci);
                    IterBool r;
                    t2.InsertClass(&r, &v, Tag());
                    ReadI32(s1.p, (char*)r.it + 0x14);
                    *(unsigned*)((char*)r.it + 0x18) = 0;
                }
            } else {
                ok = false;
            }
            if (!VC0(char, s1.p, 7))
                ok = false;
            if (!VC1(char, void*, db, 7, s1.p)) {
                ok = false;
            } else if (ok) {
                SRef s2;
                unsigned idx = 0;
                RBNode* it = t2.mAnchor.mpNodeRight;
                RBNode* end = &t2.mAnchor;
                Key3 k2 = { 0x0179d304u, 0x0179d310u, 0 };
                float total = (float)t2.mnSize;
                if (it != end) {
                    do {
                        unsigned classID = *(unsigned*)((char*)it + 0x10);
                        k2.b = classID;
                        void* d = db;
                        s2.reset();
                        if (VC2(char, Key3*, void**, d, 6, &k2, &s2.p)) {
                            VC1(void, void*, s2.p, 16, progress);
                            void* x2 = VC0(void*, s2.p, 8);
                            unsigned cnt = *(unsigned*)((char*)it + 0x14);
                            if (cnt >= kMaxCRCDataLength) {
                                ok = false;
                            } else if (cnt != 0) {
                                do {
                                    --cnt;
                                    int posA = VC1(int, int, VC0(void*, x2, 6), 9, 0);
                                    unsigned recLen;
                                    ReadI32(s2.p, &recLen);
                                    if (recLen > (unsigned)(VC0(int, VC0(void*, x2, 6), 7) + posA)) {
                                        ok = false;
                                        break;
                                    }
                                    unsigned expectedCRC;
                                    ReadI32(s2.p, &expectedCRC);
                                    unsigned tmp = recLen - 8;
                                    const unsigned* m = &kMaxCRCDataLength;
                                    if (tmp <= kMaxCRCDataLength)
                                        m = &tmp;
                                    unsigned lim = *m;
                                    tmp = 0;
                                    F_ec20* ser = (F_ec20*)((char*)this - 8);
                                    bool good = ser->g(x2, lim, &tmp);
                                    if (good) {
                                        ok = (expectedCRC == tmp);
                                        good = ok;
                                    }
                                    if (!good) {
                                        VC2(void, int, int, VC0(void*, x2, 6), 10, recLen + posA, 0);
                                        ok = false;
                                        break;
                                    }
                                    unsigned instanceID;
                                    ReadI32(s2.p, &instanceID);
                                    SRef obj;
                                    F_e9e0* real = (F_e9e0*)((char*)this - 8);
                                    if (real->f(&obj.p, instanceID, classID)) {
                                        VC1(void, void*, obj.p, 5, this);
                                        int pos = VC1(int, int, VC0(void*, x2, 6), 9, 0);
                                        if (pos != (int)(recLen + posA))
                                            VC2(void, int, int, VC0(void*, x2, 6), 10, recLen + posA, 0);
                                    } else {
                                        VC2(void, int, int, VC0(void*, x2, 6), 10, recLen + posA, 0);
                                    }
                                } while (cnt != 0);
                            }
                            if (!VC1(char, void*, db, 7, s2.p))
                                ok = false;
                            if (((int*)it)[6] != ((int*)it)[5])
                                ok = false;
                        }
                        VC1(void, float, db, 14, (float)idx * 100.0f / total);
                        it = RBTreeIncrement(it);
                        ++idx;
                    } while (it != end);
                }
            }
        }
        loaded = 1;
    }
    return ok;
}

// ---------------------------------------------------------------------------
// 0x0069f840  cCOMSerializer::cCOMSerializer (behaviour)
// The object carries two vtables: the base cICOMSerializer vptr at +8 (set to
// LRUCache then to the real serializer table) and the singleton mixin vptr at
// +0; the two rbtrees at +0x10/+0x2c default-construct their anchors, then the
// body zeroes the remaining scalars, calls reset(), and assigns the database
// smart reference (AddRef the new, Release the old).
// ---------------------------------------------------------------------------
struct CComSerBase {
    VP vt0;                 // +0
    int mRefCount;          // +4
    VP vt8;                 // +8
    unsigned char flag_c;   // +0xc
    char pad0[3];
    CComSerBase()
    {
        mRefCount = 0;
        *(VP volatile*)&vt8 = g_vtbl_14095cc;   // LRUCache base vptr (must stay)
        vt0 = g_vtbl_1408750;
        vt8 = g_vtbl_1408728;
        flag_c = 0;
    }
    ~CComSerBase();
};

struct CtorSer : CComSerBase {
    Tree mTree1;            // +0x10
    Tree mTree2;            // +0x2c
    int mMode;              // +0x48
    unsigned char b4c;      // +0x4c
    unsigned char b4d;      // +0x4d
    char pad2[2];
    void* p50;              // +0x50
    void* p54;
    void* p58;
    void* p5c;
    CtorSer(void* param);
};

// @ 0x0069f840
CtorSer::CtorSer(void* param)
{
    mMode = 0;
    b4c = 0;
    b4d = 0;
    p50 = 0;
    p54 = 0;
    p58 = 0;
    p5c = 0;
    ((CComSer*)this)->reset();
    void* old = p50;
    if (param != old) {
        if (param) ((void(__thiscall*)(void*))(*(void***)param)[0])(param);
        p50 = param;
        if (old) ((void(__thiscall*)(void*))(*(void***)old)[1])(old);
    }
}
