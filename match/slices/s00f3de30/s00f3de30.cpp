// Slice s00f3de30: simulator (editor) feedback / entity-table helpers.
// Optimized module: /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <new>
#include <intrin.h>

struct cX;
struct cGameData;
struct cEntity;
struct cEntity { char pad[0x209]; uint8_t visited; char pad20a[0x228 - 0x20a]; uint32_t id; char tail[0x234 - 0x22c]; };   // 0x234 bytes
struct SparseEl { uint32_t flags; cEntity ent; };                                                            // 0x238 bytes

struct cObject {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual cObject* QueryInterface(uint32_t id); // slot 3 (+0xc)
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual uint32_t GetType(); // slot 8 (+0x20)
    virtual void s9();
    virtual void s10();
    virtual bool IsDisabled(); // slot 11 (+0x2c)
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual const float* GetPosition(); // slot 38 (+0x98)
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void* GetProperty(uint32_t id, void* out); // slot 46 (+0xb8)
    char pad4[0x24 - 4];
    uint32_t id24;
    char pad28[0x50 - 0x28];
    uint32_t flags50;
    cGameData* GetGameData();    // 0xb18530
    bool FUN_00c0c0e0();                         // 0xc0c0e0
    const float* FUN_00f0d3e0();                 // 0xf0d3e0
    const float* FUN_00c0bc00();                 // 0xc0bc00
};
struct cGameData { char pad[0x70]; char* mpRows; bool FUN_00f25670(); };      // rows of 0x4e0 bytes
struct cCombatant { int GetDamageState(); };                                  // 0x8e7f80
struct cNounManager { uint32_t GetAvatar(); };                                // 0xb1fdb0

extern "C" {
    void*      __cdecl operator_new(uint32_t sz, const char* name, int a, int b, const char* file, int line);
    void       __cdecl operator_delete__(void* p);
    void*      __cdecl memset_thunk(void* d, int v, uint32_t n);              // 0x11e073e
    cObject*   __cdecl FUN_00b18e00(const void* h);
    cObject*   __cdecl ResourceQuery1186577(const void* key);                 // 0xeeca30
    cNounManager* __cdecl NounManager();                                      // 0xb3d300
    void       __cdecl RemoveHandler(uint32_t id, uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x571db0
    bool       __cdecl FUN_00f3b2f0(uint32_t t);
    void       __cdecl FUN_00f3b710(const void* p);
    uint32_t   __cdecl FUN_00eece20(const void* p);                           // ResourceKeyToIcon
    uint32_t   __cdecl FUN_00eecf10(const void* p);
    void       __cdecl FUN_00eef570(void* r);
    void       __cdecl FUN_00eef4b0(void* v);
    void       __cdecl FUN_00eee760(const void* key, void* vec);
}

template<class T> struct ARC {                    // EA::AutoRefCount with floor-at-zero release
    T* p;
    ~ARC() {
        if (p) {
            volatile long* rc = (volatile long*)((char*)p + 8);
            _InterlockedExchangeAdd(rc, -1);
            long n = _InterlockedExchangeAdd(rc, 0);
            if (n < 1) _InterlockedExchangeAdd(rc, 1);
            else       _InterlockedExchangeAdd(rc, 0);
        }
    }
};
struct cRC8 { uint32_t pad[2]; };
struct cRCDeleting { virtual void Destroy(int del); uint32_t refCount; };
struct RCPtr {
    cRCDeleting* p;
    ~RCPtr() {
        if (p) {
            int n = p->refCount - 1;
            p->refCount = n;
            if (n == 0) {
                p->refCount = 1;
                p->Destroy(1);
            }
        }
    }
};
struct MsgSub {
    uint32_t id, a, b, c, d;
    ~MsgSub() {
        if (id) {
            uint32_t t = id;
            id = 0;
            RemoveHandler(t, a, b, c, d);
        }
    }
};
struct ArrPtr {
    void* p;
    ~ArrPtr() {
        if (p && ((int*)p)[-1] != 0) operator_delete__(p);
    }
};
struct WStr {                                  // eastl::wstring (16 bytes)
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCap; uint32_t alloc;
    ~WStr() {
        if ((int)((((uint32_t)mpCap) - ((uint32_t)mpBegin)) & ~1u) > 2 && mpBegin)
            operator_delete__(mpBegin);
    }
};
struct HNode { uint32_t key; cObject* value; HNode* next; };

struct HT_Str {                                // hashtable<wchar_t const*, wchar_t const*> (0x20 bytes)
    uint32_t pad0; void** mpBuckets; uint32_t mnBuckets; uint32_t mnElements; uint32_t pad1[4];
    void DoFreeNodes(void** b, uint32_t n);    // 0x693230
    ~HT_Str() {
        DoFreeNodes(mpBuckets, mnBuckets);
        mnElements = 0;
        if (mnBuckets > 1) operator_delete__(mpBuckets);
    }
};
struct HT_Id {                                 // hashtable<uint, pair<uint, T*>> (0x20 bytes)
    uint32_t pad0; HNode** mpBuckets; uint32_t mnBuckets; uint32_t mnElements; uint32_t pad1[4];
    void DoFreeNodes(HNode** b, uint32_t n);   // 0x961d60
    void find(HNode** out, const uint32_t* key);   // 0x645ed0
    ~HT_Id() {
        DoFreeNodes(mpBuckets, mnBuckets);
        mnElements = 0;
        if (mnBuckets > 1) operator_delete__(mpBuckets);
    }
};
struct HT3 {                                   // position set (0x20 bytes)
    uint32_t pad0; void** mpBuckets; uint32_t mnBuckets; uint32_t mnElements; uint32_t pad1[4];
    void DoFreeNodes(void** b, uint32_t n);    // 0x93dc70
    void Insert(char* out, const float* pos, bool v);   // 0x8dfcd0
    void Clear() { DoFreeNodes(mpBuckets, mnBuckets); mnElements = 0; }
    ~HT3() {
        Clear();
        if (mnBuckets > 1) operator_delete__(mpBuckets);
    }
};

struct SparseTable {                           // at owner+0x2c10
    SparseEl* mpBegin; SparseEl* mpEnd; uint32_t pad[3]; uint32_t startIdx;
};
struct EntRef { cEntity* p; char pad[0x1c]; };
struct EntVec { EntRef* mpBegin; EntRef* mpEnd; EntRef* mpCap; };
struct Row38 { char b[0x38]; };
struct Vec38 {
    Row38* mpBegin; Row38* mpEnd; Row38* mpCap;
    void erase(Row38* pos);   // 0xff1600
};
struct RbNode { };
struct RbMap {
    uint32_t pad; RbNode endNode;
    RbNode** find(RbNode** out, const uint32_t* key);   // 0xe5c780
};
struct cTrack { char pad[8]; RbMap map; bool FUN_00edfde0(); };
struct cInfo { char pad[0x70]; char* mpRowsBegin; char* mpRowsEnd; bool FUN_00f254d0(); };
struct LbElem { int key; int pad; char payload[0x27e8 - 8]; };

struct cOwner {
    virtual void v0();
    virtual void Release();                    // slot 1
    char pad4[0x178 - 4];
    Vec38 rows;                                // +0x178
    char pad184[0x2bf4 - 0x184];
    LbElem* mpLbBegin;                         // +0x2bf4
    LbElem* mpLbEnd;                           // +0x2bf8
    char pad2bfc[0x2c08 - 0x2bfc];
    uint8_t lbFlag;                            // +0x2c08
    char pad2c09[0x2c10 - 0x2c09];
    SparseTable table;                         // +0x2c10
};
struct OwnerRef {
    cOwner* p;
    ~OwnerRef() { if (p) p->Release(); }
    cOwner* operator->() const { return p; }
};
extern "C" LbElem* __cdecl FUN_00ed29b0(LbElem* b, LbElem* e, const int* key, int flag);   // lower_bound

struct cB0 { virtual ~cB0() {} virtual void b0(); };
struct cB1 { virtual void b1(); };
struct cB2 { virtual ~cB2() {} virtual void b2(); };

extern char g_disabledFlag;       // 0x16c89a8
extern char g_pass3Flag;          // 0x15acb40
extern uint32_t g_stats[12];      // 0x16c87bc

struct cX : cB0, cB1, cB2 {
    uint32_t  pad0c;
    OwnerRef  mpOwner;            // +0x10
    char      pad14[0x30 - 0x14];
    ARC<cRC8> arc30, arc34, arc38;
    ARC<cRC8> arc3c[4];
    WStr      s4c, s5c, s6c;
    char      pad7c[0x8c - 0x7c];
    cEntity*  mpAvatar;           // +0x8c
    HT_Str    h90;
    HT_Id     hb0;
    RCPtr     rcD0;
    MsgSub    sub;                // +0xd4
    char      padE8[0x128 - 0xe8];
    ArrPtr    arr128;
    char      pad12c[0x13c - 0x12c];
    HT3       h13c, h15c, h17c, h19c, h1bc, h1dc;

    ~cX();                                         // 0xf3df50
    void  FUN_00f3e2b0(cEntity* key, cObject* res, int flag);
    void  FUN_00f3e3b0(int unused);
    __declspec(noinline) void  FUN_00f3e590(void* p, bool flag);
    bool  FUN_00f3e6d0(cObject* obj, uint32_t* info, int idx, cTrack* ent);
    void  FUN_00f3e810(int idx);
    __declspec(noinline) void* FUN_00f3e8a0(int key);
    __declspec(noinline) float FUN_00f3e910();
    void  FUN_00f3ecb0(cEntity* key, cObject* obj, uint32_t* out);
    void  FUN_00f3e6b0(void* p);
    void* FUN_00f3e900(int* p);
    int   FUN_00f3ec90(int arg);

    void  FUN_00f3b800(cEntity* key, cObject* res, int flag);
    void  FUN_00f3da90(void* key, void* arg);
    cTrack* FUN_00f3dc70(cObject* obj);
    float FUN_00f3dce0(uint32_t* stats);
};

inline SparseEl* TableStart(cOwner* o) {
    uint32_t idx = o->table.startIdx;
    return idx < 0x3fffffff ? o->table.mpBegin + idx : o->table.mpEnd;
}
inline void TableNext(SparseEl*& p) {
    uint32_t f;
    do {
        f = p->flags;
        ++p;
        if ((f >> 30) & 1) break;
    } while ((int)p->flags < 0);
}

// ---------------------------------------------------------------------------
// vector<SummaryEntry> (0x44-byte elements) helpers
// ---------------------------------------------------------------------------
struct CString { char b[0x14]; CString& operator=(const CString& o); };          // SP::cString (0x6b5430)
struct WStrA {                                                                    // eastl::wstring with inline operator=
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCap; uint32_t alloc;
    void assign(const wchar_t* b, const wchar_t* e);                              // 0x423650
    WStrA& operator=(const WStrA& x) { if (&x != this) assign(x.mpBegin, x.mpEnd); return *this; }
};
struct SummaryEntry {
    uint32_t id;       // +0
    CString  name;     // +4
    WStrA    text;     // +0x18
    uint32_t a, b;     // +0x28, +0x2c
    WStrA    desc;     // +0x30
    uint32_t c;        // +0x40
    SummaryEntry& operator=(const SummaryEntry& o) {
        id = o.id; name = o.name; text = o.text; a = o.a; b = o.b; desc = o.desc; c = o.c;
        return *this;
    }
};
struct SummaryVec {
    SummaryEntry* mpBegin; SummaryEntry* mpEnd; SummaryEntry* mpCap;
    SummaryVec(const SummaryVec& x);
};
extern "C" void __cdecl uninitialized_copy_Summary(SummaryEntry** out, SummaryEntry* first, SummaryEntry* last,
                                                   SummaryEntry* dest, const SummaryVec* tag);   // 0xdfb8e0

// @ 0x00f3de30
SummaryVec::SummaryVec(const SummaryVec& x) {
    int n = (int)(x.mpEnd - x.mpBegin);
    SummaryEntry* p;
    if (n)
        p = (SummaryEntry*)operator_new(n * sizeof(SummaryEntry), "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    else
        p = 0;
    mpCap = p + n;
    mpBegin = p;
    mpEnd = p;
    SummaryEntry* out;
    uninitialized_copy_Summary(&out, x.mpBegin, x.mpEnd, p, &x);
    mpEnd = out;
}

// @ 0x00f3dec0   eastl::fill_n<SummaryEntry*, unsigned, SummaryEntry>
SummaryEntry* FillSummary(SummaryEntry* first, unsigned n, const SummaryEntry* value) {
    for (; n > 0; --n, ++first)
        *first = *value;
    return first;
}

// ---------------------------------------------------------------------------
// @ 0x00f3df50  destructor
// ---------------------------------------------------------------------------
cX::~cX() {
}

// ---------------------------------------------------------------------------
// @ 0x00f3e2b0
// ---------------------------------------------------------------------------
void cX::FUN_00f3e2b0(cEntity* key, cObject* res, int flag) {
    if (!res) {
        res = ResourceQuery1186577(key);
        if (!res) return;
    }
    if (res->flags50 & 0x2000) {
        EntVec v;
        v.mpBegin = 0; v.mpEnd = 0; v.mpCap = 0;
        void* r = res->GetProperty(0x17f243b, &v);
        FUN_00eef570(r);
        FUN_00f3b800(key, res, flag);
        FUN_00f3da90(key, 0);
        FUN_00eee760(key, &v);
        for (EntRef* it = v.mpBegin; it != v.mpEnd; ++it)
            it->p->visited = 1;
        FUN_00eef4b0(&v);
        if (v.mpBegin && ((int*)v.mpBegin)[-1] != 0)
            operator_delete__(v.mpBegin);
        return;
    }
    FUN_00f3b800(key, res, flag);
    FUN_00f3da90(key, 0);
}

// ---------------------------------------------------------------------------
// @ 0x00f3e3b0
// ---------------------------------------------------------------------------
void cX::FUN_00f3e3b0(int unused) {
    (void)unused;
    cOwner* o = mpOwner.p;
    if (g_pass3Flag) {
        for (SparseEl* it = TableStart(o); o->table.mpEnd != it; TableNext(it))
            *((uint8_t*)it + 0x20d) = 0;
        if (mpAvatar) mpAvatar->visited = 0;
        for (SparseEl* it = TableStart(o); o->table.mpEnd != it; TableNext(it)) {
            cObject* r = ResourceQuery1186577(&it->ent);
            if (r && (r->flags50 & 0x2000))
                FUN_00f3e2b0(&it->ent, r, 0);
        }
        for (SparseEl* it = TableStart(o); o->table.mpEnd != it; TableNext(it)) {
            if (*((uint8_t*)it + 0x20d) == 0)
                FUN_00f3e2b0(&it->ent, 0, 0);
        }
    } else {
        for (SparseEl* it = TableStart(o); o->table.mpEnd != it; TableNext(it))
            FUN_00f3b800(&it->ent, 0, 1);
    }
    if (mpAvatar && mpAvatar->visited == 0)
        FUN_00f3e2b0(mpAvatar, 0, 0);
}

// ---------------------------------------------------------------------------
// @ 0x00f3e590
// ---------------------------------------------------------------------------
void cX::FUN_00f3e590(void* p, bool flag) {
    cOwner* o = mpOwner.p;
    for (SparseEl* it = TableStart(o); o->table.mpEnd != it; TableNext(it)) {
        cEntity* key = &it->ent;
        uint32_t id;
        if (key == mpAvatar) {
            id = NounManager()->GetAvatar();
        } else {
            HNode* node;
            id = 0;
            hb0.find(&node, &key->id);
            if (hb0.mpBuckets[hb0.mnBuckets] != node)
                id = (uint32_t)node->value;
        }
        cObject* obj = FUN_00b18e00((void*)id);
        if (obj) {
            bool notFlagged = (obj->flags50 & 0x2000) != 0x2000;
            if (notFlagged != flag)
                FUN_00f3da90(key, p);
        }
    }
    if (!flag && mpAvatar)
        FUN_00f3da90(mpAvatar, p);
}

// ---------------------------------------------------------------------------
// @ 0x00f3e6b0 (byte-exact)
// ---------------------------------------------------------------------------
void cX::FUN_00f3e6b0(void* p) {
    FUN_00f3e590(p, 1);
    FUN_00f3e590(p, 0);
}

// ---------------------------------------------------------------------------
// @ 0x00f3e6d0
// ---------------------------------------------------------------------------
extern char g_typeCombatant;     // 0x13f94d4 (interface id is the address)
bool cX::FUN_00f3e6d0(cObject* obj, uint32_t* info, int idx, cTrack* ent) {
    if (obj->IsDisabled())
        return false;
    if (ent == 0) {
        cTrack* t = FUN_00f3dc70(obj);
        if (t && t->FUN_00edfde0()) {
            if (info[0x61] != 0xffffffff) return false;
            info[0x61] = 0xd;
            return false;
        }
    } else {
        uint32_t k = obj->id24;
        RbNode* out;
        RbNode** it = ent->map.find(&out, &k);
        if (*it != &ent->map.endNode)
            return false;
    }
    cGameData* data = obj->GetGameData();
    bool bVar;
    if (data && data->mpRows[idx * 0x4e0 + 2] != 0 && data->FUN_00f25670() && FUN_00f3b2f0(info[0]))
        bVar = true;
    else
        bVar = false;
    cCombatant* comb = (cCombatant*)obj->QueryInterface((uint32_t)&g_typeCombatant);
    if (comb && comb->GetDamageState() == 2 && !bVar)
        return false;
    if (info[0] - 4 < 2) {
        cObject* q = obj->QueryInterface(0xce9f6639);
        if (q && q->FUN_00c0c0e0()) {
            if (info[0x61] != 0xffffffff) return false;
            info[0x61] = 0xf;
            return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00f3e810
// ---------------------------------------------------------------------------
void cX::FUN_00f3e810(int idx) {
    cOwner* o = mpOwner.p;
    if (idx >= 0 && idx < (int)(o->rows.mpEnd - o->rows.mpBegin)) {
        if (mpAvatar)
            FUN_00f3b710(&o->rows.mpBegin[idx]);
        Vec38& r = mpOwner.p->rows;
        r.erase(&r.mpBegin[idx]);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3e8a0  (lower_bound lookup; returns payload or null)
// ---------------------------------------------------------------------------
void* cX::FUN_00f3e8a0(int key) {
    cOwner* o = mpOwner.p;
    LbElem* end = o->mpLbEnd;
    LbElem* p = FUN_00ed29b0(o->mpLbBegin, end, &key, o->lbFlag);
    if (p == end || key < p->key)
        p = end;
    if (end != p)
        return (char*)p + 8;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f3e900 (byte-exact)
// ---------------------------------------------------------------------------
void* cX::FUN_00f3e900(int* p) {
    return FUN_00f3e8a0(*(int*)((char*)p + 0x1c));
}

// ---------------------------------------------------------------------------
// @ 0x00f3e910
// ---------------------------------------------------------------------------
float cX::FUN_00f3e910() {
    if (g_disabledFlag) return 0.0f;
    h13c.Clear();
    h15c.Clear();
    h17c.Clear();
    h19c.Clear();
    h1bc.Clear();
    h1dc.Clear();
    memset_thunk(g_stats, 0, 0x30);
    HNode** b = hb0.mpBuckets;
    HNode** bp = b;
    HNode* node = *bp;
    if (!node) {
        ++bp;
        while (*bp == 0) ++bp;
        node = *bp;
    }
    HNode* endNode = b[hb0.mnBuckets];
    while (node != endNode) {
        cObject* o = node->value;
        if (o) {
            float pos[3];
            const float* src = FUN_00b18e00(o)->GetPosition();
            pos[0] = src[0]; pos[1] = src[1]; pos[2] = src[2];
            uint32_t type = o->GetType();
            char tmp[12];
            HT3* tbl;
            if (type == 0x70703b3) {
                ++g_stats[0];
                tbl = &h13c;
            } else if (type > 0x70703b3) {
                if (type == 0x74e0069) {
                    ++g_stats[4];
                    const float* r = o->QueryInterface(0x74e0069)->FUN_00f0d3e0();
                    pos[0] = r[0]; pos[1] = r[1]; pos[2] = r[2];
                    tbl = &h1bc;
                } else if (type == 0x7b38ba7) {
                    ++g_stats[5];
                    const float* r = o->QueryInterface(0x7b38ba7)->FUN_00f0d3e0();
                    pos[0] = r[0]; pos[1] = r[1]; pos[2] = r[2];
                    tbl = &h1dc;
                } else {
                    goto other;
                }
            } else if (type == 0x18c6de8 || type == 0x18ebadc) {
                ++g_stats[1];
                cObject* q = o->QueryInterface(0xb033b403);
                if (q) {
                    const float* r = (const float*)((char*)q + 0x780);
                    pos[0] = r[0]; pos[1] = r[1]; pos[2] = r[2];
                }
                tbl = &h15c;
            } else if (type == 0x18eb45e) {
                ++g_stats[2];
                const float* r = o->QueryInterface(0xce9f6639)->FUN_00c0bc00();
                pos[0] = r[0]; pos[1] = r[1]; pos[2] = r[2];
                tbl = &h17c;
            } else {
            other:
                ++g_stats[3];
                tbl = &h19c;
            }
            tbl->Insert(tmp, pos, false);
        }
        node = node->next;
        while (node == 0) {
            ++bp;
            node = *bp;
        }
    }
    g_stats[6]  = h13c.mnElements;
    g_stats[7]  = h15c.mnElements;
    g_stats[8]  = h17c.mnElements;
    g_stats[9]  = h19c.mnElements;
    g_stats[10] = h1bc.mnElements;
    g_stats[11] = h1dc.mnElements;
    return FUN_00f3dce0(g_stats);
}

// ---------------------------------------------------------------------------
// @ 0x00f3ec90 (byte-exact with /arch:SSE, manifest override)
// ---------------------------------------------------------------------------
int cX::FUN_00f3ec90(int arg) {
    (void)arg;
    if (1.0f > FUN_00f3e910()) return 1;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f3ecb0
// ---------------------------------------------------------------------------
void cX::FUN_00f3ecb0(cEntity* key, cObject* obj, uint32_t* out) {
    out[1] = 0xeb5c1d8e;
    *(uint8_t*)&out[2] = 0;
    if (key == mpAvatar) {
        out[0] = 0xe34e8a60;
        out[3] = 0xffffffff;
        return;
    }
    cInfo* p = (cInfo*)FUN_00f3e8a0(*(int*)key);
    out[3] = 0;
    for (uint32_t i = 0; i < (uint32_t)((p->mpRowsEnd - p->mpRowsBegin) / 0x4e0); ++i) {
        if (i < 0x20) {
            if (*(uint8_t*)(p->mpRowsBegin + i * 0x4e0) != 0)
                out[3] |= 1u << (i & 0x1f);
            else
                out[3] &= ~(1u << (i & 0x1f));
        }
    }
    out[0] = FUN_00eece20(p);
    if (out[0] == 0xe34e8a60 && obj) {
        cObject* q = obj->QueryInterface(0xce9f6639);
        if (q)
            *(uint8_t*)&out[2] = q->FUN_00c0c0e0();
    }
    if (out[0] == 0x6031c03a)
        out[1] = FUN_00eecf10(p);
    if (out[0] == 0xcf56099a && p->FUN_00f254d0()) {
        out[0] = 0x6031c03a;
        out[1] = 0x0b7e477a;
    }
}
