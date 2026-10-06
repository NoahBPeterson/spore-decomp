// Slice s00d00ee0: SP simulator container/set helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (SSE2 also fine for the two lower_bound helpers)
#include "types.h"

extern "C" void* __cdecl FUN_00921580(void* node);

// ===========================================================================
// @ 0x00d011e0  __cdecl: destroy tree from root until sentinel
// ===========================================================================
extern "C" int __cdecl Fd011e0(int unused, void* t)
{
    char* base = (char*)t;
    void* node = *(void**)(base + 8);
    void* sentinel = base + 4;
    while (node != sentinel)
        node = FUN_00921580(node);
    return 1;
}

// ===========================================================================
// @ 0x00d01210  __cdecl lower_bound over 0x20-byte elements
// ===========================================================================
extern "C" int* __cdecl Fd01210(int* first, int* last, int* value)
{
    int n = (int)((char*)last - (char*)first) >> 5;
    if (n > 0) {
        unsigned v = *(unsigned*)value;
        do {
            int half = n >> 1;
            int* mid = (int*)((char*)first + (half << 5));
            if (*(unsigned*)mid < v) {
                first = (int*)((char*)mid + 0x20);
                n -= half + 1;
            } else {
                n = half;
            }
        } while (n > 0);
    }
    return first;
}

// ===========================================================================
// @ 0x00d01260  __cdecl lower_bound over 8-byte elements
// ===========================================================================
extern "C" int* __cdecl Fd01260(int* first, int* last, int* value)
{
    int n = (int)((char*)last - (char*)first) >> 3;
    if (n > 0) {
        unsigned v = *(unsigned*)value;
        do {
            int half = n >> 1;
            int* mid = (int*)((char*)first + (half << 3));
            if (*(unsigned*)mid < v) {
                first = (int*)((char*)mid + 8);
                n -= half + 1;
            } else {
                n = half;
            }
        } while (n > 0);
    }
    return first;
}

// ===========================================================================
// @ 0x00d018d0  __thiscall: erase range [first,last) of 8-byte elements
// ===========================================================================
int* __fastcall Fd018d0(void* self, int, int* first, int* last)
{
    char* end = *(char**)((char*)self + 4);
    char* d = (char*)first;
    char* s = (char*)last;
    int cnt = (int)((char*)last - (char*)first);
    while (s != end) {
        *(int*)d = *(int*)s;
        *(int*)(d + 4) = *(int*)(s + 4);
        d += 8;
        s += 8;
    }
    *(char**)((char*)self + 4) = end - cnt;
    return first;
}

// ===========================================================================
// Relationship container helpers (SP::cRelationshipManager family), written over the
// retail offsets. EASTL red-black tree nodes: right at +0, left at +4, parent at +8, color at
// +0xc, value at +0x10; the tree object is {allocator(4), anchor(0x10), size(4)}.
// ===========================================================================
inline void* operator new(unsigned, void* p) { return p; }

extern "C" void* __cdecl EaAlloc(unsigned sz, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl EaFree(void* p);                                     // 0x00f47380
extern "C" void* __cdecl MemCopyThunk(void* d, const void* s, unsigned n);    // 0x011e0744
extern "C" void  __cdecl WriteUint32(void* stream, const uint32_t* v, int count, int endian); // 0x0093aa70
extern "C" void  __cdecl RBTreeInsert(void* node, void* parent, void* anchor, int side);     // 0x009216a0
extern "C" void* __cdecl RBTreeIncrement(void* node);                         // 0x00921580
extern "C" void* __cdecl RBTreeDecrement(void* node);                         // 0x009215c0
extern "C" void  __cdecl NormalizePair(uint32_t* a, uint32_t* b);             // 0x00d009a0
extern "C" int*  __cdecl LowerBound32(int* first, int* last, const uint32_t& value, uint8_t flag); // 0x00d01210
inline uint32_t CopyU32(uint32_t v) { return v; }

extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
#pragma intrinsic(memcpy)
static const char kAllocFile[] = "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

struct IStream {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void* GetRaw();               // slot 6 (+0x18)
};
struct ISerializer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void EndRecord();             // slot 7 (+0x1c)
    virtual IStream* GetStream();         // slot 8 (+0x20)
};
struct cVarListSerializer {
    char buf[0xa00];
    cVarListSerializer(const void* list, const void* desc, uint32_t id);  // 0x00692f90
    void Serialize(ISerializer* s);                                       // 0x00692900
};
extern char kVarListDescA[];   // 0x01582008
extern char kVarListDescB[];   // 0x01581f50

inline void PutU32(ISerializer* ser, uint32_t value)
{
    IStream* st = ser->GetStream();
    uint32_t tmp = value;
    void* raw = st->GetRaw();
    WriteUint32(raw, &tmp, 1, 0);
}
inline void PutF32(ISerializer* ser, float value)
{
    IStream* st = ser->GetStream();
    float tmp = value;
    void* raw = st->GetRaw();
    WriteUint32(raw, (uint32_t*)&tmp, 1, 0);
}

struct RBNode { RBNode* right; RBNode* left; RBNode* parent; uint8_t color; uint8_t pad[3]; };
struct RelData { float value; union { uint32_t flags; struct { uint8_t bit0 : 1; uint8_t bit1 : 1; }; }; uint32_t pad[4]; };      // 0x18
struct RelValue { uint32_t k0, k1; RelData data; };                    // 0x20
struct RelNode { RBNode h; RelValue v; };                              // 0x30
struct PairKeyNode { RBNode h; uint32_t k0, k1; };                     // 0x18

inline bool PairLess(const uint32_t* a, const uint32_t* b)
{
    return a[0] < b[0] || (!(b[0] < a[0]) && a[1] < b[1]);
}

struct Iter {
    RBNode* node;
    Iter() {}
    Iter(RBNode* n) { node = n; }
    Iter(const Iter& o) { node = o.node; }
};
struct InsRes {
    Iter it; bool inserted;
    InsRes() {}
    InsRes(const Iter& i, bool b) : it(i) { inserted = b; }
    InsRes(const InsRes& o) : it(o.it) { inserted = o.inserted; }
};
struct TrueTag {};
struct RelTree {
    uint32_t alloc; RBNode anchor; uint32_t size;
    __declspec(noinline) void find(RBNode** out, const uint32_t* key);                                       // 0x00d00f80
    __declspec(noinline) Iter InsertImpl(RBNode* parent, const RelValue* value, bool forceLeft);             // 0x00d012a0
    __declspec(noinline) InsRes Insert(const RelValue* value, TrueTag tag);                                  // 0x00d01340
    __declspec(noinline) Iter InsertHint(Iter hint, const RelValue* value, TrueTag tag);                     // 0x00d01920
};
struct FeedbackNode { RBNode h; uint32_t key; float value; };
struct FeedbackTree {
    uint32_t alloc; RBNode anchor; uint32_t size;
    void find(FeedbackNode** out, const uint32_t* key);  // 0x00e5c780
};
struct PairSetTree {
    __declspec(noinline) PairKeyNode* DoCopySubtree(PairKeyNode* src, PairKeyNode* dest);   // 0x00d01820
};
PairKeyNode* __stdcall DoCreateNode(PairKeyNode* src, PairKeyNode* parent);  // 0x00e2b7f0

struct Noun {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual uint32_t GetID();    // slot 19 (+0x4c)
    char pad[0x80];
    uint32_t mId;                // +0x84
    char pad2[1];
    uint8_t mFlag89;             // +0x89
    void NotifyOther(Noun* o);   // 0x00c32830
    void Finish();               // 0x00c31c50
    float GetPower();            // 0x00c31990
};

extern char kEmptyStr[];         // 0x01667bac
struct String {
    char* b; char* e; char* c;
    String() { b = kEmptyStr; e = kEmptyStr; c = kEmptyStr + 1; }
    __forceinline String(const char* p) {
        b = 0; e = 0; c = 0;
        unsigned n = 0;
        while (p[n]) ++n;
        RangeInitialize(n + 1);
        char* d = b;
        MemCopyThunk(d, p, n);
        e = d + n;
        *d = 0;
    }
    ~String() { if ((c - b) > 1 && b) EaFree(b); }
    String& sprintf(const char* fmt, ...);        // 0x00472fe0 (cdecl, this pushed)
    void assign(const char* f, const char* l);    // 0x00454cb0
    void RangeInitialize(unsigned n);             // 0x00475ab0
};

struct cGameNounManager {
    Noun* GetPlayerCivilization();                 // 0x00b25fb0
    void* GetNoun(uint32_t id);                    // 0x00b20790
    String UpdateDebugUI(void* noun);              // 0x00b20ee0
};
cGameNounManager* NounManager();                   // 0x00b3d300
struct cEmpireStar { float GetPower(); };
struct cStarManager { Noun* GetEmpireByID(uint32_t id); };   // 0x00ba9370
cStarManager* StarManager();                       // 0x00b3d2a0
extern char kSpaceMode[];                          // 0x01654c05
char* GetCurrentGameMode();                        // 0x00b5b800
Noun* GetPlayerEmpire();                           // 0x01021300

struct ActivePlanet { uint32_t FindEmbassy(); };   // 0x00ce6950
ActivePlanet* GetActivePlanetRecord();             // 0x010212a0
bool __cdecl SignBit(uint32_t v);                  // 0x00ba6650

struct IMessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Post(uint32_t type, void* msg, int arg);   // slot 5 (+0x14)
};
namespace EA { namespace Messaging { IMessageServer* GetServer(); } }  // 0x00883860

extern char vtbl_UI_BehaviorMessage[];   // 0x013eb90c
extern char vtbl_SlotMessage[];          // 0x013eb844
struct BehaviorMsg {
    const void* vptr; volatile long refCount; uint32_t slot0; uint32_t padA; uint32_t slot1; uint32_t body[7]; uint32_t arg; uint32_t padB; uint32_t mask; uint32_t padC;
    void Destruct();                         // 0x00421cf0
};
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

struct Tuning { float base, scale, lo, hi, pad, asym; };    // asym at +0x14
inline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

struct RelCalc {
    __declspec(noinline) float A0ee0(Noun* a, Noun* b);
    int   GetRelLevel(uint32_t a, uint32_t b, int flag);   // 0x00d00a70
    float GetRel(uint32_t a, uint32_t b, int flag);        // 0x00d00a10
};

struct RecItem { uint32_t key; RelTree tree; uint32_t pad; };   // 0x20

struct RelBook {
    char pad0[0x24];
    RelTree mEmpty;                 // +0x24
    char pad1[0x9c - 0x24 - sizeof(RelTree)];
    RecItem* mBegin;                // +0x9c
    RecItem* mEnd;                  // +0xa0
    char pad2[0xb0 - 0xa4];
    uint8_t mFlag;                  // +0xb0

    __declspec(noinline) RelTree* A1ab0(uint32_t a, uint32_t b);
    __declspec(noinline) bool  A1b50(uint32_t a, uint32_t b);
    __declspec(noinline) float A1b80(uint32_t a, uint32_t b, uint32_t key);
    __declspec(noinline) String A1bb0(uint32_t a, uint32_t b);
    __declspec(noinline) String A1db0(Noun* a, Noun* b);
    __declspec(noinline) void  A1e30(Noun* a, Noun* b);
    __declspec(noinline) bool A1f20(uint32_t a, uint32_t b);
    float GetRel(uint32_t a, uint32_t b, int flag);   // 0x00d00a10
    __declspec(noinline) RelData* FindRel(RelTree* t, uint32_t a, uint32_t b);  // 0x00d01410 (this unused)
    __declspec(noinline) float FindRelFeedback(RelTree* t, uint32_t a, uint32_t b, uint32_t key);    // 0x00d01470
    __declspec(noinline) float FindRelScaled(RelTree* t, uint32_t a, uint32_t b, uint32_t key, Tuning* p); // 0x00d015d0
};

struct RelWriter {
    char pad[0x90];
    char* mBegin;   // +0x90
    char* mEnd;     // +0x94
    __declspec(noinline) void A14e0(ISerializer* ser);
};

// ---------------------------------------------------------------------------
// @ 0x00d00ee0
float RelCalc::A0ee0(Noun* a, Noun* b)
{
    if (a->mFlag89 == 0 && b->mFlag89 == 0) {
        Noun* player = NounManager()->GetPlayerCivilization();
        if (player) {
            uint32_t pid = player->GetID();
            uint32_t aid = a->GetID();
            if (GetRelLevel(aid, pid, 1) >= 4) {
                uint32_t pid2 = player->GetID();
                uint32_t bid = b->GetID();
                if (GetRelLevel(bid, pid2, 1) <= 1)
                    return -10.0f;
            }
        }
        return 0.0f;
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00d00f80  lower_bound then verify (map::find over pair<uint,uint> keys)
void RelTree::find(RBNode** out, const uint32_t* key)
{
    RBNode* end = &anchor;
    RBNode* best = end;
    RBNode* n = anchor.parent;
    while (n) {
        const uint32_t* nk = (const uint32_t*)((char*)n + 0x10);
        if (!PairLess(nk, key)) {
            best = n;
            n = n->left;
        } else {
            n = n->right;
        }
    }
    if (best != end && !PairLess(key, (const uint32_t*)((char*)best + 0x10)))
        *out = best;
    else
        *out = end;
}

// ---------------------------------------------------------------------------
// @ 0x00d00ff0  write a map<pair<uint,uint>, VarList>
__declspec(noinline) void __cdecl WriteVarMap(ISerializer* ser, RelTree* t)
{
    PutU32(ser, t->size);
    RBNode* end = &t->anchor;
    for (RBNode* it = t->anchor.left; it != end; it = (RBNode*)RBTreeIncrement(it)) {
        PutU32(ser, *(uint32_t*)((char*)it + 0x10));
        PutU32(ser, *(uint32_t*)((char*)it + 0x14));
        ser->EndRecord();
        cVarListSerializer vs((char*)it + 0x18, kVarListDescA, 0x1a80d26);
        vs.Serialize(ser);
        ser->EndRecord();
    }
    ser->EndRecord();
}

// ---------------------------------------------------------------------------
// @ 0x00d01110  write a map<uint,float>
__declspec(noinline) void __cdecl WriteFloatMap(ISerializer* ser, RelTree* t)
{
    PutU32(ser, t->size);
    RBNode* end = &t->anchor;
    for (RBNode* it = t->anchor.left; it != end; it = (RBNode*)RBTreeIncrement(it)) {
        PutU32(ser, *(uint32_t*)((char*)it + 0x10));
        ser->EndRecord();
        PutF32(ser, *(float*)((char*)it + 0x14));
        ser->EndRecord();
    }
    ser->EndRecord();
}

// ---------------------------------------------------------------------------
// @ 0x00d012a0  rbtree::DoInsertValueImpl
Iter RelTree::InsertImpl(RBNode* parent, const RelValue* value, bool forceLeft)
{
    int side = (!forceLeft && parent != &anchor && !PairLess(&value->k0, (const uint32_t*)((char*)parent + 0x10))) ? 1 : 0;
    RelNode* node = (RelNode*)EaAlloc(0x30, "Simulator", 0, 0, kAllocFile, 0xd1);
    RelValue* dst = &node->v;
    if (dst) memcpy(dst, value, sizeof(RelValue));
    RBTreeInsert(node, parent, &anchor, side);
    ++size;
    return Iter(&node->h);
}

// ---------------------------------------------------------------------------
// @ 0x00d01340  rbtree::DoInsertValue(value, true_type): returns pair<iterator,bool> via sret
InsRes RelTree::Insert(const RelValue* value, TrueTag)
{
    RBNode* cur = anchor.parent;
    RBNode* lower = &anchor;
    bool less = true;
    while (cur) {
        less = PairLess(&value->k0, (const uint32_t*)((char*)cur + 0x10));
        lower = cur;
        cur = less ? cur->left : cur->right;
    }
    RBNode* parent = lower;
    if (less) {
        if (lower != anchor.left)
            lower = (RBNode*)RBTreeDecrement(lower);
        else
        {
            Iter r = InsertImpl(lower, value, false);
            return InsRes(r, true);
        }
    }
    if (PairLess((const uint32_t*)((char*)lower + 0x10), &value->k0)) {
        Iter r = InsertImpl(parent, value, false);
        return InsRes(r, true);
    }
    return InsRes(Iter(lower), false);
}

// ---------------------------------------------------------------------------
// @ 0x00d01410  find a relationship record by (a,b); returns the data part or null
RelData* RelBook::FindRel(RelTree* t, uint32_t a, uint32_t b)
{
    NormalizePair(&a, &b);
    uint32_t key[2] = { a, b };
    RBNode* it;
    t->find(&it, key);
    RelData* r = 0;
    if (it != &t->anchor)
        r = (RelData*)((char*)it + 0x18);
    return r;
}

// @ 0x00d01470  look up a feedback strength by event key
float RelBook::FindRelFeedback(RelTree* t, uint32_t a, uint32_t b, uint32_t key)
{
    float result = 0.0f;
    RelData* d = FindRel(t, a, b);
    if (d) {
        uint32_t k = key;
        FeedbackNode* it;
        ((FeedbackTree*)((char*)d + 8))->find(&it, &k);
        if ((char*)it != (char*)d + 0xc)
            result = it->value;
    }
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x00d014e0  cRelationshipManager::Write
void RelWriter::A14e0(ISerializer* ser)
{
    PutU32(ser, 0x301b5d9f);
    PutU32(ser, (uint32_t)(mEnd - mBegin) >> 5);
    char* end = mEnd;
    for (char* it = mBegin; it != end; it += 0x20) {
        PutU32(ser, *(uint32_t*)it);
        WriteVarMap(ser, (RelTree*)(it + 4));
    }
    cVarListSerializer vs((char*)this - 0xc, kVarListDescB, 0x1a80d26);
    vs.Serialize(ser);
}

// ---------------------------------------------------------------------------
// @ 0x00d015d0  scaled relationship feedback strength (tuning-weighted, power-ratio adjusted)
float RelBook::FindRelScaled(RelTree* t, uint32_t a, uint32_t b, uint32_t key, Tuning* p)
{
    RelData* d = FindRel(t, a, b);
    if (d) {
        FeedbackNode* it;
        ((FeedbackTree*)((char*)d + 8))->find(&it, &key);
        if ((char*)it != (char*)d + 0xc) {
            float mult = 1.0f;
            if (p->asym != 0.0f && GetCurrentGameMode() == kSpaceMode) {
                Noun* e1 = StarManager()->GetEmpireByID(a);
                Noun* e2 = StarManager()->GetEmpireByID(b);
                if (e1 && e2) {
                    float s1 = e1->GetPower();
                    float s2 = e2->GetPower();
                    float num, den;
                    if (p->asym > 0.0f) { num = s2; den = s1; }
                    else                { num = s1; den = s2; }
                    float ratio = 2.0f;
                    if (den > 1.5258789e-05f)
                        ratio = num / den;
                    ratio = Clamp(ratio, 0.5f, 2.0f);
                    mult = (float)fabs(p->asym) * (ratio - 1.0f) + 1.0f;
                }
            }
            float v = it->value * p->scale * mult + p->base;
            return Clamp(v, p->lo, p->hi);
        }
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00d01820  rbtree::DoCopySubtree over a set of pair keys
PairKeyNode* PairSetTree::DoCopySubtree(PairKeyNode* src, PairKeyNode* dest)
{
    PairKeyNode* root = DoCreateNode(src, dest);
    if (src->h.right)
        root->h.right = &DoCopySubtree((PairKeyNode*)src->h.right, root)->h;
    PairKeyNode* destNode = root;
    for (src = (PairKeyNode*)src->h.left; src; src = (PairKeyNode*)src->h.left) {
        PairKeyNode* nn = (PairKeyNode*)EaAlloc(0x18, "Simulator", 0, 0, kAllocFile, 0xd1);
        uint32_t* kp = &nn->k0;
        if (kp) { kp[0] = src->k0; kp[1] = src->k1; }
        nn->h.right = 0;
        nn->h.left = 0;
        nn->h.parent = &destNode->h;
        nn->h.color = src->h.color;
        destNode->h.left = &nn->h;
        if (src->h.right)
            nn->h.right = &DoCopySubtree((PairKeyNode*)src->h.right, nn)->h;
        destNode = nn;
    }
    return root;
}

// ---------------------------------------------------------------------------
// @ 0x00d01920  rbtree::DoInsertValue(hint, value, true_type)
Iter RelTree::InsertHint(Iter hint, const RelValue* value, TrueTag tag)
{
    RBNode* rightmost = anchor.right;
    if (hint.node == rightmost || hint.node == &anchor) {
        if (size != 0 && PairLess((const uint32_t*)((char*)rightmost + 0x10), &value->k0))
            return InsertImpl(rightmost, value, false);
        InsRes r = Insert(value, TrueTag());
        return r.it;
    }
    Iter next((RBNode*)RBTreeIncrement(hint.node));
    if (PairLess((const uint32_t*)((char*)hint.node + 0x10), &value->k0) &&
        PairLess(&value->k0, (const uint32_t*)((char*)next.node + 0x10))) {
        if (hint.node->right)
            return InsertImpl(next.node, value, true);
        return InsertImpl(hint.node, value, false);
    }
    InsRes r = Insert(value, TrueTag());
    return r.it;
}

// ---------------------------------------------------------------------------
// @ 0x00d01ab0  find the per-key relationship tree for an (a,b) pair, else the empty tree
RelTree* RelBook::A1ab0(uint32_t a, uint32_t b)
{
    NormalizePair(&a, &b);
    ActivePlanet* rec = GetActivePlanetRecord();
    if (rec) {
        if (!SignBit(a) || !SignBit(b)) {
            uint32_t key = rec->FindEmbassy();
            a = key;
            RecItem* last = mEnd;
            RecItem* it = (RecItem*)LowerBound32((int*)mBegin, (int*)last, a, mFlag);
            if (it == last || key < it->key || it == it + 1)
                it = last;
            if (it != last)
                return &it->tree;
        }
    }
    return &mEmpty;
}

// @ 0x00d01b50
bool RelBook::A1b50(uint32_t a, uint32_t b)
{
    return FindRel(A1ab0(a, b), a, b) != 0;
}

// @ 0x00d01b80
float RelBook::A1b80(uint32_t a, uint32_t b, uint32_t key)
{
    return FindRelFeedback(A1ab0(a, b), a, b, key);
}

// ---------------------------------------------------------------------------
// @ 0x00d01bb0  SP::cRelationshipManager::GetDebugString
String RelBook::A1bb0(uint32_t a, uint32_t b)
{
    String result;
    cGameNounManager* nm = NounManager();
    bool same = (a == b);
    if (same) {
        String name = nm->UpdateDebugUI(nm->GetNoun(a));
        RelData* d = FindRel(A1ab0(a, b), a, b);
        if (d)
            result.sprintf("%s 0x%08x -> self = %.1f", name.b, a, (double)d->value);
        else
            result.sprintf("%s 0x%08x -> self = none", name.b, a);
        return result;
    }
    NormalizePair(&a, &b);
    String nameA = nm->UpdateDebugUI(nm->GetNoun(a));
    String nameB = nm->UpdateDebugUI(nm->GetNoun(b));
    String val;
    bool has = FindRel(A1ab0(a, b), a, b) != 0;
    if (has)
        val.sprintf("%.1f", (double)GetRel(a, b, 1));
    else
        val.assign("none", "none" + 4);
    result.sprintf("%s 0x%08x -> %s 0x%08x = %s", nameA.b, a, nameB.b, b, val.b);
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x00d01db0  debug string for a pair of nouns (empty string if either is missing)
String RelBook::A1db0(Noun* a, Noun* b)
{
    if (a && b) {
        uint32_t ida = a->GetID();
        uint32_t idb = b->GetID();
        return A1bb0(ida, idb);
    }
    return String("");
}

// ---------------------------------------------------------------------------
// @ 0x00d01e30  SP::cRelationshipManager::EndAlliance
void RelBook::A1e30(Noun* a, Noun* b)
{
    Noun* player = GetPlayerEmpire();
    if (b == 0)
        b = player;
    uint32_t idA = a->mId;
    uint32_t idB = b->mId;
    RelData* d = FindRel(A1ab0(idA, idB), idA, idB);
    if (d)
        d->flags &= ~2u;
    if (b != player) {
        d = FindRel(A1ab0(idB, idA), idB, idA);
        if (d)
            d->flags &= ~2u;
    }
    a->NotifyOther(b);
    b->NotifyOther(a);
    if (b == player) {
        BehaviorMsg msg;
        msg.arg = 0;
        msg.vptr = vtbl_UI_BehaviorMessage;
        _InterlockedExchange(&msg.refCount, 0);
        msg.vptr = vtbl_SlotMessage;
        msg.mask = 0;
        msg.slot0 = (uint32_t)a;
        msg.slot1 = (uint32_t)b;
        EA::Messaging::GetServer()->Post(0x4445d44, &msg, 0);
        msg.Destruct();
    }
    a->Finish();
    b->Finish();
}

// ---------------------------------------------------------------------------
// @ 0x00d01f20  relationship flag 0 of (a,b)
bool RelBook::A1f20(uint32_t a, uint32_t b)
{
    RelData* d = FindRel(A1ab0(a, b), a, b);
    if (d)
        return d->bit0;
    return false;
}
