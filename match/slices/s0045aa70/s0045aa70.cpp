// Slice s0045aa70: Simulator::cContentValidationSummarizer-style effect table + XformMsg helpers
// and a large container-owning object ctor/dtor. Hand-modelled layouts (see comments).
#include "types.h"

struct IRefObj {            // intrusive ref-counted object: vtbl[0]=AddRef, [1]=Release
    virtual void AddRef();
    virtual void Release();
};

struct IEffect {            // effect instance (vtbl slots used by this slice)
    virtual void v0();
    virtual void Release();                 // 0x04
    virtual void Start(int flag);           // 0x08
    virtual void Stop(int flag);            // 0x0c
    virtual void v10();
    virtual void v14();
    virtual void SetTransform(void* msg);   // 0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c(); virtual void v30();
};

struct XformMsg {           // 0x38 bytes; ctor @0x434040
    uint16_t flags;         // |4 = has position, |2 = has matrix
    int16_t  count;
    float    pos[3];
    uint32_t pad0[2];
    uint32_t mat[9];
    XformMsg();
};

struct EffectsMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool CreateEffect(int key, int unused, IEffect** out);   // 0x2c
};
EffectsMgr* SP_EffectsManager();            // @0x67ddd0

struct Node {               // hash node: key, value, next
    int      key;
    IEffect* value;
    Node*    next;
};
struct Iter { Node* node; Node** bucket; };
inline bool operator!=(const Iter& a, const Iter& b) { return a.node != b.node; }

struct EffectTable {        // lives at cSummarizer+8
    uint32_t pad0;          // +0 (unused here)
    Node**   buckets;       // +4
    uint32_t nbuckets;      // +8
    uint32_t count;         // +0xc
    uint32_t alloc;         // +0x10 (allocator at +0x14 of ... see below)

    void   find(Iter* out, int* key);                  // @0x421950
    Iter*  erase(Iter* out, Iter it);                  // @0x45b3e0
    void   freeBuckets(Node** b, uint32_t n);          // @0x45b750
    IEffect** operator_index(int* key);                // @0x45b290
};

struct Summarizer {
    void*    vtbl;          // +0
    uint32_t pad4;          // +4
    // table at +8: [+8 pad][+0xc buckets][+0x10 nbuckets][+0x14 count]
    uint32_t t_pad;         // +8
    uint32_t t_pad2;        // +0xc is accessed as *(this+0xc) in 0x45b210
    char     tail[0x40];
};

// Real layout of the hashtable as seen from its owner (this+8 == table):
//   table+0 pad, table+4 buckets, table+8 nbuckets, table+0xc count.
struct HTable {
    uint32_t pad;
    Node**   buckets;   // +4
    uint32_t nbuckets;  // +8
    uint32_t count;     // +0xc
    void  find(Iter* out, int* key);                    // @0x421950
    void  begin(Iter* out);                             // 0x564140
    Iter  end() { Iter i; i.node = *(&buckets[nbuckets]); i.bucket = &buckets[nbuckets]; return i; }
    Iter* erase(Iter* out, Iter it);                    // @0x45b3e0
    void  clearBuckets(Node** b, uint32_t n);           // @0x45b750
    Node** at(int* key);                                // @0x45b290
    void  FUN_0045b4c0(Iter* out, void* pair, int unused); // @0x45b4c0 insert (thiscall, 3 args)
    Node* allocNode(void* pair);                        // @0x45b660
    void  freeNode(Node* n);                            // @0x45b6f0
};

// The base-object helpers operate on the +8 table sub-object: this (ecx) is &table and there is no
// hidden self argument.  Hex-named members keep the relocation resolver exact.
struct TableCtorApi {
    void FUN_005640f0(char* tag);   // 0x5640f0
};
struct TableDtorApi {
    void FUN_0045b380();            // 0x45b380
};

struct cContentValidationSummarizer {
    void*  vtbl;        // +0
    int    f4;          // +4
    HTable table;       // +8

    cContentValidationSummarizer();                       // 0x45aa70
    ~cContentValidationSummarizer();                      // 0x45ab00
    void ClearAll();                                      // 0x45ab30
    IEffect* Play(int key, int mode, void* msg, int key2);// 0x45ac20
    IEffect* Find(int key);                               // 0x45b210
    void Play0(int key, int mode);                        // 0x45ae10
    void PlayFrom(int key, int mode, char* src, int key2);// 0x45ae40
    void PlayPosMat(int key, int mode, float* pos, uint32_t* mat); // 0x45aed0
    void PlayPos(int key, int mode, float* pos);          // 0x45af60
    void Start(int key);                                  // 0x45afc0
    void Stop(int key);                                   // 0x45b000
    void SetXform(int key, void* msg);                    // 0x45b040
    void SetXformFrom(int key, char* src);                // 0x45b080
    void SetEnabled(int key, bool b);                     // 0x45b110
    void Remove(int key);                                 // 0x45b150
};

void ThisBase_Ctor(void* p, char* tag);   // @0x5640f0 (thiscall on table)
void ThisBase_Dtor(void* p);              // @0x45b380

// @ 0x45aa70
cContentValidationSummarizer::cContentValidationSummarizer()
{
    vtbl = (void*)0x13ec458;
    f4 = 0;
    vtbl = (void*)0x13ecc8c;
    char tag;
    ((TableCtorApi*)&table)->FUN_005640f0(&tag);
}

// @ 0x45ab00
cContentValidationSummarizer::~cContentValidationSummarizer()
{
    vtbl = (void*)0x13ecc8c;
    ((TableDtorApi*)&table)->FUN_0045b380();
    vtbl = (void*)0x13ec458;
}

// @ 0x45ab30
void cContentValidationSummarizer::ClearAll()
{
    Iter it;
    table.begin(&it);              // 0x564140
    while (it != table.end()) {
        Node* node = it.node;
        IEffect* pEffect = node->value;
        pEffect->Stop(1);
        Iter tmp;
        it = *table.erase(&tmp, it);
    }
    table.clearBuckets(table.buckets, table.nbuckets);
    table.count = 0;
}

// @ 0x45ac20
IEffect* cContentValidationSummarizer::Play(int key, int mode, void* msg, int key2)
{
    IEffect* eff = 0;
    EffectsMgr* mgr = SP_EffectsManager();
    if (eff) { IEffect* t = eff; eff = 0; t->Release(); }
    if (mgr->CreateEffect(key, 0, &eff)) {
        eff->SetTransform(msg);
        eff->Start(0);
        if (mode == 1) {
            if (key2 != 0) key = key2;
            Iter it;
            table.find(&it, &key);
            if (it.node == *(&table.buckets[table.nbuckets])) {
                IEffect** slot = (IEffect**)table.at(&key);
                IEffect* cur = eff;
                IEffect* old = *slot;
                if (cur != old) {
                    if (cur) ((IRefObj*)cur)->AddRef();
                    *slot = cur;
                    if (old) old->Release();
                }
            }
        }
    }
    IEffect* ret = eff;
    if (eff) eff->Release();
    return ret;
}

// @ 0x45ae10
void cContentValidationSummarizer::Play0(int key, int mode)
{
    XformMsg m;
    Play(key, mode, &m, 0);
}

// @ 0x45ae40
void cContentValidationSummarizer::PlayFrom(int key, int mode, char* src, int key2)
{
    XformMsg m;
    if (src) {
        m.pos[0] = *(float*)(src + 0x48);
        m.pos[1] = *(float*)(src + 0x4c);
        m.pos[2] = *(float*)(src + 0x50);
        m.flags |= 4; m.count += 1;
        for (int i = 0; i < 9; i++) m.mat[i] = *(uint32_t*)(src + 0x60 + i * 4);
        m.flags |= 2; m.count += 1;
    }
    Play(key, mode, &m, key2);
}

// @ 0x45aed0
void cContentValidationSummarizer::PlayPosMat(int key, int mode, float* pos, uint32_t* mat)
{
    XformMsg m;
    m.pos[0] = pos[0]; m.pos[1] = pos[1]; m.pos[2] = pos[2];
    for (int i = 0; i < 9; i++) m.mat[i] = mat[i];
    m.flags |= 6; m.count += 2;
    Play(key, mode, &m, 0);
}

// @ 0x45af60
void cContentValidationSummarizer::PlayPos(int key, int mode, float* pos)
{
    XformMsg m;
    m.pos[0] = pos[0]; m.pos[1] = pos[1]; m.pos[2] = pos[2];
    m.flags |= 4; m.count += 1;
    Play(key, mode, &m, 0);
}

// @ 0x45afc0
void cContentValidationSummarizer::Start(int key)
{
    IEffect* e = Find(key);
    if (e) e->Start(1);         // vtbl+8
}

// @ 0x45b000
void cContentValidationSummarizer::Stop(int key)
{
    IEffect* e = Find(key);
    if (e) e->Stop(1);          // vtbl+0xc
}

// @ 0x45b040
void cContentValidationSummarizer::SetXform(int key, void* msg)
{
    IEffect* e = Find(key);
    if (e) e->SetTransform(msg);
}

// @ 0x45b080
void cContentValidationSummarizer::SetXformFrom(int key, char* src)
{
    XformMsg m;
    if (src) {
        m.pos[0] = *(float*)(src + 0x48);
        m.pos[1] = *(float*)(src + 0x4c);
        m.pos[2] = *(float*)(src + 0x50);
        m.flags |= 4; m.count += 1;
        for (int i = 0; i < 9; i++) m.mat[i] = *(uint32_t*)(src + 0x60 + i * 4);
        m.flags |= 2; m.count += 1;
    }
    SetXform(key, &m);
}

// @ 0x45b110
void cContentValidationSummarizer::SetEnabled(int key, bool b)
{
    IEffect* e = Find(key);
    if (e) ((void(__thiscall*)(IEffect*, int))(*(void***)e)[0x30 / 4])(e, !b);
}

// @ 0x45b150
void cContentValidationSummarizer::Remove(int key)
{
    Iter it;
    table.find(&it, &key);
    Node* endNode = *(&table.buckets[table.nbuckets]);
    if (it.node != endNode) {
        it.node->value->Stop(1);
        Iter tmp;
        table.erase(&tmp, it);
    }
}

// @ 0x45b210
IEffect* cContentValidationSummarizer::Find(int key)
{
    Iter it;
    table.find(&it, &key);
    if (it.node == *(&table.buckets[table.nbuckets])) return 0;
    return it.node->value;
}

// @ 0x45b290
Node** HTable::at(int* key)
{
    Iter it;
    find(&it, key);
    if (it.node == *(&buckets[nbuckets])) {
        struct { int key; IRefObj* a; IRefObj* b; } pair = { *key, 0, 0 };
        Iter r;
        FUN_0045b4c0(&r, &pair, 0);
        Node** slot = (Node**)((char*)r.node + 4);
        if (pair.b) pair.b->Release();
        if (pair.a) pair.a->Release();
        return slot;
    }
    return (Node**)((char*)it.node + 4);
}

// @ 0x45b3e0
Iter* HTable::erase(Iter* out, Iter it)
{
    Node* node = it.node;
    Node* nxt = node->next;
    Node** b = it.bucket;
    while (nxt == 0) { ++b; nxt = *b; }
    Node* cur = *it.bucket;
    if (cur == node) {
        *it.bucket = cur->next;
    } else {
        Node* n = cur->next;
        for (; n != node; n = n->next) cur = n;
        cur->next = n->next;
    }
    freeNode(node);
    count--;
    out->node = nxt;
    out->bucket = b;
    return out;
}

extern void* Alloc(void* allocator, int size, int align, int flags);   // @0x42dee0
// @ 0x45b660
Node* HTable::allocNode(void* pairv)
{
    struct P { int key; IRefObj* val; };
    P* pr = (P*)pairv;
    Node* n = (Node*)Alloc((char*)this + 0x1c, 0xc, 4, 0);
    if (n) {
        n->key = pr->key;
        n->value = (IEffect*)pr->val;
        if (n->value) ((IRefObj*)n->value)->AddRef();
    }
    n->next = 0;
    return n;
}

// @ 0x45b6f0
void HTable::freeNode(Node* n)
{
    if (n->value) ((IRefObj*)n->value)->Release();
    operator delete[](n);
}

// @ 0x45b750
void HTable::clearBuckets(Node** b, uint32_t n)
{
    for (uint32_t i = 0; i < n; i++) {
        Node* p = b[i];
        while (p) {
            Node* nx = p->next;
            freeNode(p);
            p = nx;
        }
        b[i] = 0;
    }
}

// ---------------------------------------------------------------------------
// ColladaExport (0x150 bytes), layout shared with slice s004629e0.
// ---------------------------------------------------------------------------
struct VAlloc { char b; };              // empty allocator tag (distinct temp per member)

struct AllocObj {                       // allocator sub-object at +0xc of a vector
    uint32_t mA, mB;                    // +0x00, +0x04
    void ctor(const VAlloc& alloc);     // 0x429360
};

struct VecHdr {                         // vector header + sp_vector_allocator (0x14 bytes)
    void*    mpBegin;                   // +0x00
    void*    mpEnd;                     // +0x04
    void*    mpCapacity;                // +0x08
    AllocObj mAllocator;                // +0x0c
    VecHdr() { ctor(VAlloc()); }
    VecHdr(const VAlloc& alloc) { ctor(alloc); }
    void ctor(const VAlloc& alloc);     // 0x540470  (empty the three pointers)
    void dtor4();                       // 0x425990  (4-byte elements: int/uint32/pointer)
    void dtor8();                       // 0x45daf0  (8-byte elements)
    void dtor12();                      // 0x5156b0  (12-byte elements: Vector3)
    void dtor16();                      // 0x554b10  (16-byte elements: Vector4f)
    void dtor64();                      // 0x45d750  (64-byte elements: Matrix4)
    void dtorVec3();                    // 0x540520  (out-of-line vector<Vector3> dtor)
};

struct PadVec {                         // 0x14: vector whose allocator is constructed separately
    void*    mpBegin;                   // +0x00
    void*    mpEnd;                     // +0x04
    void*    mpCapacity;                // +0x08
    AllocObj mAllocator;                // +0x0c
    PadVec() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; mAllocator.ctor(VAlloc()); }
    void dtor64();                      // 0x45d750
};

struct WString {
    void*    mpBegin;                   // +0x00
    void*    mpEnd;                     // +0x04
    void*    mpCapacity;                // +0x08
    uint32_t mAllocator;                // +0x0c
    WString() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; SetEmpty(); }
    void SetEmpty();                    // 0x45dac0
    void Free();                        // 0x4237d0
};

struct ColladaExport {
    WString  mName;                     // +0x000
    VecHdr   mPositions;                // +0x010
    VecHdr   mNormals;                  // +0x024
    VecHdr   mUVs;                      // +0x038
    VecHdr   mTangents;                 // +0x04c
    VecHdr   mBinormals;                // +0x060
    VecHdr   mBoneIndices;              // +0x074
    VecHdr   mBoneWeights;              // +0x088
    VecHdr   mPosIndices;               // +0x09c
    VecHdr   mNormalIndices;            // +0x0b0
    VecHdr   mUVIndices;                // +0x0c4
    VecHdr   mBoneNames;                // +0x0d8
    VecHdr   mBoneParents;              // +0x0ec
    VecHdr   mBindMatrices;             // +0x100
    PadVec   mPad114;                   // +0x114
    VecHdr   mBoneMatrices;             // +0x128
    PadVec   mPad13c;                   // +0x13c

    ColladaExport();
    ~ColladaExport();
};

// @ 0x45b7c0
ColladaExport::ColladaExport()
{
}

// @ 0x45b9a0
ColladaExport::~ColladaExport()
{
    mPad13c.dtor64();
    mBoneMatrices.dtor64();
    mPad114.dtor64();
    mBindMatrices.dtor64();
    mBoneParents.dtor4();
    mBoneNames.dtor4();
    mUVIndices.dtor4();
    mNormalIndices.dtor4();
    mPosIndices.dtor4();
    mBoneWeights.dtor16();
    mBoneIndices.dtor8();
    mBinormals.dtor12();
    mTangents.dtor12();
    mUVs.dtor8();
    mNormals.dtor12();
    mPositions.dtorVec3();
    mName.Free();
}
