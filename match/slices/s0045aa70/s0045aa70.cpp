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
    Iter* erase(Iter* out, Iter it);                    // @0x45b3e0
    void  clearBuckets(Node** b, uint32_t n);           // @0x45b750
    Node** at(int* key);                                // @0x45b290
    Node* allocNode(void* pair);                        // @0x45b660
    void  freeNode(Node* n);                            // @0x45b6f0
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
    ThisBase_Ctor(&table, &tag);
}

// @ 0x45ab00
cContentValidationSummarizer::~cContentValidationSummarizer()
{
    vtbl = (void*)0x13ecc8c;
    ThisBase_Dtor(&table);
    vtbl = (void*)0x13ec458;
}

// @ 0x45ab30
void cContentValidationSummarizer::ClearAll()
{
    Iter it;
    table.find(&it, 0);            // begin() (0x564140)
    for (;;) {
        Node** end = &table.buckets[table.nbuckets];
        Node* endNode = *end;
        if (it.node == endNode) break;
        it.node->value->Stop(1);
        Iter tmp, cur = it;
        it = *table.erase(&tmp, cur);
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
        extern void HTable_Insert(HTable*, Iter*, void*, int);   // @0x45b4c0
        HTable_Insert(this, &r, &pair, 0);
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
    Node* n = (Node*)Alloc((char*)this + 0x14, 0xc, 4, 0);
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

// Large aggregate: simple vectors/strings. Sub-object helpers are thiscalls.
struct Sub { void ctor(char* tag); void init(); void dtor(); void dtor2(); void dtor3(); };
struct Vec { void* b; void* e; void* c; };
struct BigObj {
    uint32_t a, b, c;                // +0
    void Hdr_ctor();                 // @0x45dac0 on this+? (this)
};
extern void  F45dac0(void* p);       // thiscall @0x45dac0
extern void  F540470(void* p, char* t);
extern void  F429360(void* p, char* t);
extern void  F45d750(void* p);
extern void  F425990(void* p);
extern void  F554b10(void* p);
extern void  F45daf0(void* p);
extern void  F5156b0(void* p);
extern void  F540520(void* p);
extern void  WString_FreeBuffer(void* p);

// @ 0x45b7c0
void* BigObj_ctor(uint32_t* p)
{
    char t[17];
    p[0] = 0; p[1] = 0; p[2] = 0;
    F45dac0(p);
    F540470((char*)p + 0x10, &t[0]);
    F540470((char*)p + 0x24, &t[1]);
    F540470((char*)p + 0x38, &t[2]);
    F540470((char*)p + 0x4c, &t[3]);
    F540470((char*)p + 0x60, &t[4]);
    F540470((char*)p + 0x74, &t[5]);
    F540470((char*)p + 0x88, &t[6]);
    F540470((char*)p + 0x9c, &t[7]);
    F540470((char*)p + 0xb0, &t[8]);
    F540470((char*)p + 0xc4, &t[9]);
    F540470((char*)p + 0xd8, &t[10]);
    F540470((char*)p + 0xec, &t[11]);
    F540470((char*)p + 0x100, &t[12]);
    p[0x45] = 0; p[0x46] = 0; p[0x47] = 0;
    F429360((char*)p + 0x10c, &t[13]);
    F540470((char*)p + 0x114, &t[14]);
    p[0x4f] = 0; p[0x50] = 0; p[0x51] = 0;
    F429360((char*)p + 0x13c, &t[15]);
    return p;
}

// @ 0x45b9a0
void BigObj_dtor(char* p)
{
    F45d750(p + 0x13c);
    F45d750(p + 0x128);
    F45d750(p + 0x114);
    F45d750(p + 0x100);
    uint32_t x;
    for (x = *(uint32_t*)(p + 0xec); x < *(uint32_t*)(p + 0xf0); x += 4) {}
    F425990((void*)x);
    for (x = *(uint32_t*)(p + 0xd8); x < *(uint32_t*)(p + 0xdc); x += 4) {}
    F425990((void*)x);
    for (x = *(uint32_t*)(p + 0xc4); x < *(uint32_t*)(p + 0xc8); x += 4) {}
    F425990((void*)x);
    for (x = *(uint32_t*)(p + 0xb0); x < *(uint32_t*)(p + 0xb4); x += 4) {}
    F425990((void*)x);
    for (x = *(uint32_t*)(p + 0x9c); x < *(uint32_t*)(p + 0xa0); x += 4) {}
    F425990((void*)x);
    for (x = *(uint32_t*)(p + 0x88); x < *(uint32_t*)(p + 0x8c); x += 0x10) {}
    F554b10((void*)x);
    for (x = *(uint32_t*)(p + 0x74); x < *(uint32_t*)(p + 0x78); x += 8) {}
    F45daf0((void*)x);
    for (x = *(uint32_t*)(p + 0x60); x < *(uint32_t*)(p + 0x64); x += 0xc) {}
    F5156b0((void*)x);
    for (x = *(uint32_t*)(p + 0x4c); x < *(uint32_t*)(p + 0x50); x += 0xc) {}
    F5156b0((void*)x);
    for (x = *(uint32_t*)(p + 0x38); x < *(uint32_t*)(p + 0x3c); x += 8) {}
    F45daf0((void*)x);
    for (x = *(uint32_t*)(p + 0x24); x < *(uint32_t*)(p + 0x28); x += 0xc) {}
    F5156b0((void*)x);
    F540520(p + 0x10);
    WString_FreeBuffer(p);
}
