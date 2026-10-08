// Slice s00e1fb20 (cl2 #372): 0x00e1fb20, a UI refresh routine of an anonymous-namespace
// "test bed" style window class (PDB candidate cPlanetTestBedCheat::runIteration; the body walks
// a category/group/sub/item tree, matches items against the unlocked collectable list and
// fills the slot windows of a layout).  No /EHsc (stack list with no EH frame).

#include "types.h"
#include <new>

typedef unsigned int uint32;

struct RC {
    virtual void v00();
    virtual int AddRef();
    virtual int Release();
};

struct RC0 {   // interface whose slot 0 = AddRef, slot 1 = Release
    virtual int AddRef();
    virtual int Release();
};

struct Item : RC {
    uint32 pad04, pad08;
    uint32 a;      // 0x0c
    uint32 b;      // 0x10
    uint32 c;      // 0x14
};

struct Sub {
    char pad[0x70];
    Item** itemsBegin;   // 0x70
    Item** itemsEnd;     // 0x74
    Item* At(uint32 i);  // 0x005c7f00
};

struct Group : RC {
    uint32 pad04, pad08;
    Sub** subsBegin;     // 0x0c
    Sub** subsEnd;       // 0x10
    char pad14[0x74 - 0x14];
    uint32 id;           // 0x74
    Sub* At(uint32 i);   // 0x005c1ce0
};

struct Categories {
    char pad[0xc];
    Group** begin;       // 0x0c
    Group** end;         // 0x10
    Group* At(uint32 i); // 0x005c5de0
};

struct Entry {
    uint32 idx;
    bool flag;
    RC* obj;
    Entry(uint32 i, bool f, RC* o) : idx(i), flag(f), obj(o) { if (o) o->AddRef(); }
    Entry(const Entry& r) : idx(r.idx), flag(r.flag), obj(r.obj) { if (obj) obj->AddRef(); }
    ~Entry() { if (obj) obj->Release(); }
};

struct EntryVec {
    Entry* b;
    Entry* e;
    Entry* cap;
    void Destroy(Entry* first, Entry* last);       // 0x00e1f700
    void DoInsertValue(Entry* pos, const Entry& v); // 0x00e1f780
    void push_back(const Entry& v) {
        if (e < cap) {
            Entry* p = e;
            e = p + 1;
            if (p) new (p) Entry(v);
        } else {
            DoInsertValue(e, v);
        }
    }
};

struct LNode {
    LNode* next;
    LNode* prev;
    uint32 val;
};

struct PLink {
    PLink* next;
    PLink* prev;
};

struct PNode : PLink {
    uint32 lo;
    uint32 hi;
};

struct PList : PLink {
    uint32 unused;   // 12-byte stack object (no 8-byte alignment)
    void Fill(void* src);  // 0x00e1fa20
};

struct Window {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void SetControlID(uint32 id);                 // 0x50
    virtual void SetCommandID(uint32 id);                 // 0x54
    virtual void v58();
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void SetFlag(uint32 flag, bool v);            // 0x7c
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8c();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9c();
    virtual void va0();
    virtual void va4();
    virtual void va8();
    virtual void vac();
    virtual void vb0();
    virtual void vb4();
    virtual void vb8();
    virtual void vbc();
    virtual void vc0();
    virtual void vc4();
    virtual void vc8();
    virtual void vcc();
    virtual void vd0();
    virtual void vd4();
    virtual void vd8();
    virtual void vdc();
    virtual void ve0();
    virtual void ve4();
    virtual void ve8();
    virtual void vec();
    virtual Window* FindWindowByID(uint32 id, bool recursive);  // 0xf0
};

struct Layout {
    char pad[0x14];
    Window* root;
    Window* FindWindowByID(uint32 id, bool recursive);  // 0x008105b0 (cSPUILayout)
};

struct SlotList {   // this+0x4c
    char pad[0x18];
    Layout** layouts;   // 0x18
    void Reset();                              // 0x00e0a640
    void Build(void* spec, uint32 count);       // 0x00e0a780
    Layout* At(uint32 i);                       // 0x00e09c90
};


struct Inner {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual uint32 GetId();   // 0x1c
};

struct Eff {
    char pad[0xa0];
    Inner* inner;          // 0xa0
};
struct Checker {
    Eff* Check(uint32 id);  // 0x006646c0
};
struct CheckList {
    uint32 Count();         // 0x00662a10
    Checker* At(uint32 i);  // 0x00662a20
};

struct Target : RC0 {
    void* GetUnlockedItems();   // 0x005939a0
};

struct TribeNode {
    uint32 key;
    uint32 pad;
    TribeNode* next;   // 0x08
};

struct TribeStrategy {
    char pad[0xac];
    TribeNode** buckets; // 0xac
    uint32 nBuckets;     // 0xb0
    char pad2[0x19c - 0xb4];
    Target* selected;    // 0x19c
};

struct Sphere {
    char pad[0x10e8];
    Target* p;
};
struct NounMgr {
    Sphere* GetCurrentTerrainSphere();   // 0x00f67d90
};

struct Holder { char pad[0x10]; Target* ref; };

struct TestWin {
    char pad00[0x10];
    uint32 mode;           // 0x10
    uint32 id;             // 0x14
    char pad18[0x34 - 0x18];
    LNode* headNext; LNode* headPrev; // 0x34 (EASTL list sentinel)
    char pad3c[4];
    Categories* cats;      // 0x40
    Holder* holder;        // 0x44
    CheckList* checks;     // 0x48
    SlotList slots;        // 0x4c
    char pad50[0xc0 - 0x4c - sizeof(SlotList)];
    EntryVec entries;      // 0xc0
    char padcc[0xd8 - 0xcc];
    uint32 specKey;        // 0xd8
    char paddc[4];
    uint32 groupId;        // 0xe0

    void Refresh();
};

// ---- external functions ----
TribeStrategy* TribeInstance();                    // 0x00cd40b0
NounMgr* GetNounManager();                         // 0x00b3d300
Target* GetDefaultTarget();                        // 0x00e5c4f0
struct Key64 { uint32 lo, hi; };
Key64 __cdecl MakeKey(uint32 hi, uint32 lo);   // 0x00593980
const uint32* __cdecl LookupKeyTriple(uint32 i);   // 0x00c9cec0
void __cdecl SortEntries(Entry* b, Entry* e, uint32 n);   // 0x00e1fa90
void __cdecl FreeNode(void* p);                    // 0xf47380 operator delete
void __cdecl SetWindowImage(Window* w, void* img, int idx);  // 0x00807bb0

struct Dispatcher {
    void Post(uint32 a, uint32 b, uint32 c, uint32 d, uint32 e);  // 0x00e30e20 (ret 0x14)
};
struct GlobalInfo { char pad[0x5c]; Dispatcher* disp; };
GlobalInfo* GetGlobalInfo();                        // 0x00b3d3f0

struct SpecHeader {
    uint32 key;
    uint32 a;
    uint32 b;
};

static inline LNode* FindInList(LNode* head, uint32 v) {
    LNode* n = head->next;
    for (; n != head; n = n->next) {
        if (n->val == v) break;
    }
    return n;
}

static inline void EraseNode(LNode* n) {
    LNode* x = n->next->prev;
    x->prev->next = x->next;
    x->next->prev = x->prev;
    FreeNode(x);
}

void TestWin::Refresh()
{
    slots.Reset();
    entries.Destroy(entries.b, entries.e);

    Group* group = 0;
    {
        uint32 n = (uint32)(cats->end - cats->begin);
        uint32 k = 0;
        if ((int)n <= 0) return;
        for (;;) {
            Group* g = cats->At(k);
            if (g != group) {
                Group* old = group;
                if (g) g->AddRef();
                group = g;
                if (old) old->Release();
            }
            if (group->id == groupId) break;
            ++k;
            if ((int)n <= (int)k) {
                group->Release();
                return;
            }
        }
    }

    Eff* eff = 0;
    if (checks) {
        uint32 cnt = checks->Count();
        for (uint32 i = 0; i < cnt; ++i) {
            eff = checks->At(i)->Check(groupId);
            if (eff) break;
        }
    }

    Target* target = 0;
    switch (mode) {
    case 0x1654c00:
        target = GetDefaultTarget();
        break;
    case 0x1654c01: {
        Sphere* s = GetNounManager()->GetCurrentTerrainSphere();
        if (s && s->p) target = s->p;
        break;
    }
    case 0x1654c02:
        if (id != 0x6722bd6) target = TribeInstance()->selected;
        break;
    }
    {
        Holder* h = holder;
        if (h) {
            Target* old = h->ref;
            if (target != old) {
                if (target) target->AddRef();
                h->ref = target;
                if (old) old->Release();
            }
        }
    }

    PList list;
    list.next = list.prev = &list;
    if (holder->ref) list.Fill(holder->ref->GetUnlockedItems());

    uint32 count = 0;
    uint32 nSubs = (uint32)(group->subsEnd - group->subsBegin);
    for (uint32 i = 0; i < nSubs; ++i) {
        Sub* sub = group->At(i);
        uint32 nItems = (uint32)(sub->itemsEnd - sub->itemsBegin);
        for (uint32 j = 0; j < nItems; ++j) {
            Item* item = sub->At(j);
            if (!item) continue;
            if (holder->ref) {
                Key64 key = MakeKey(item->c, item->a);
                uint32 idx = 0;
                PLink* l = list.next;
                for (; l != &list; l = l->next) {
                    PNode* n = (PNode*)l;
                    if (n->lo == key.lo && n->hi == key.hi) {
                        Entry tmp(idx, false, item);
                        LNode* f = FindInList((LNode*)&headNext, item->a);
                        tmp.flag = (f != (LNode*)&headNext);
                        if (tmp.flag) EraseNode(f);
                        entries.push_back(tmp);
                        break;
                    }
                    ++idx;
                }
            } else if (id == 0x6722bd6) {
                TribeStrategy* t = TribeInstance();
                TribeNode** pb = t->buckets;
                TribeNode* n = *pb;
                if (!n) {
                    do { ++pb; } while (!*pb);
                    n = *pb;
                }
                t = TribeInstance();
                TribeNode* endNode = t->buckets[t->nBuckets];
                uint32 idx = 0;
                while (n != endNode) {
                    uint32 key = n->key;
                    const uint32* tri = LookupKeyTriple(key);
                    if (tri[0] == item->a && tri[1] == item->b && tri[2] == item->c) {
                        Entry tmp(idx, false, item);
                        LNode* f = FindInList((LNode*)&headNext, key);
                        tmp.flag = (f != (LNode*)&headNext);
                        if (tmp.flag) EraseNode(f);
                        entries.push_back(tmp);
                        break;
                    }
                    n = n->next;
                    if (!n) {
                        do { ++pb; n = *pb; } while (!n);
                    }
                    ++idx;
                }
            }
            ++count;
        }
    }

    SortEntries(entries.b, entries.e, nSubs);
    SpecHeader spec;
    spec.key = specKey;
    spec.a = 0x510a95b;
    spec.b = 0x40464100;
    slots.Build(&spec, count);

    uint32 nEnt = (uint32)(entries.e - entries.b);
    for (uint32 k = 0; k < count; ++k) {
        Window* win = slots.At(k)->FindWindowByID(0x60b1490, true);
        if (!win) continue;
        RC* obj = 0;
        bool flag = false;
        if (k < nEnt) {
            obj = entries.b[k].obj;
            flag = entries.b[k].flag;
        }
        bool has = obj != 0;
        win->SetControlID(k + 0x66652c2);
        win->SetCommandID(0x66651c3);
        win->SetFlag(0x1000, true);
        if (flag) {
            uint32 v;
            if (eff) v = eff->inner->GetId();
            else v = id;
            GetGlobalInfo()->disp->Post(k + 0x66652c2, v, 0x19a90282, 0, 0);
        }
        Window* c = win->FindWindowByID(0x60b1040, false);
        if (c) {
            c->SetFlag(1, has);
            if (has) SetWindowImage(c, (char*)obj + 0x18, -1);
        }
        c = win->FindWindowByID(0x60b0f50, false);
        if (c) c->SetFlag(1, !has);
        c = win->FindWindowByID(0x60b0e48, false);
        if (c) c->SetFlag(1, false);
        c = win->FindWindowByID(0x60b18d0, false);
        if (c) c->SetFlag(1, false);
    }

    PLink* p = list.next;
    while (p != &list) {
        PLink* nx = p->next;
        FreeNode(p);
        p = nx;
    }
    group->Release();
}
