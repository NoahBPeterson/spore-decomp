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
    void Remove(Eff* e);    // 0x00662c10
    void SetEnabled(bool v); // 0x00662920
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

// ===========================================================================
// Additional members of the same translation unit (slice s00e1fb20).
// ===========================================================================

// ---- shared helpers -------------------------------------------------------

TribeStrategy* TribeInstance();                    // 0x00cd40b0 (decl above)
NounMgr* GetNounManager();                         // 0x00b3d300

Target* __cdecl GetPlayerTribe(NounMgr* mgr);      // 0x00bfc5f0 (cGameNounManager::GetPlayerTribe)
bool __cdecl IsHerbivoreTribe();                   // 0x00c8e850
uint32 __cdecl SPIDFromName(const char* name, uint32 a, uint32 b); // 0x00571cf0
uint32 __cdecl MakeCommunityEditorID(uint32 a);    // 0x00bda3b0
uint32* __cdecl GetGlobalData();                   // 0x00b3d300 returns noun mgr

// ---- TestWin-facing message handler (this == TestWin+0x0c) ----------------

// View of the TestWin fields reached through the handler subobject at
// TestWin+0x0c.  Field offsets below are relative to the subobject.
struct Panel12 {
    char     pad00[0x08];
    uint32   id;         // +0x08  (TestWin+0x14)
    char     pad0c[0x34 - 0x0c];
    uint32   f34;        // +0x34  (TestWin+0x40, checked against 0)
    char     pad38[0x3c - 0x38];
    CheckList* checks;   // +0x3c  (TestWin+0x48)
    char     pad40[0xd4 - 0x40];
    uint32   groupId;    // +0xd4  (TestWin+0xe0)

    bool OnMessage(uint32 msg, void* p);  // 0x00e20210
};

// The two outer handlers are non-virtual helpers of the owning window.
struct PanelBase {
    void OpenEditor(uint32* blk, uint32 a, uint32 b);   // 0x00e1e500
    bool BaseOnMessage(uint32 msg, void* p);            // 0x00e18600
};
struct TestWin;

// ---- TestWin slot refresh driven by a string id ---------------------------

struct cString {
    char pad[0x10];
    cString();                                                        // 0x006b5060
    ~cString();                                                       // 0x006b5240
    void Load(uint32 fmt, uint32 a, const wchar_t* s);                // 0x006b54b0
    const wchar_t* GetText();                                         // 0x006b55c0
};

// The Win owns two string-id-driven sub-widgets addressed by this+0x18/0x1c.
struct SlotWnd {
    virtual void v00();
    virtual void v04();
};

struct TestWinEx : TestWin {
    void SetVisibleSlot(uint32 v);            // 0x00e18860
    void SetSlotText(const wchar_t* t);       // 0x00e18890
    void UpdateSlot(uint32 v);                // 0x00e20360
};

// ---- UI/GGE/PatchManager (vtable 0x1480498, 0x2080 bytes) ------------------

// eastl container (begin/capacity/end) initialised by 0x00579a90
struct WBlob {
    void* mpBegin;      // +0x00
    void* mpCapacity;   // +0x04
    void* mpEnd;        // +0x08
    void  RangeInit(const void* src);  // 0x00579a90 eastl::wstring::range_initialize
};

extern wchar_t gEmptyWString[];     // 0x013ec468

typedef void* HMODULE;
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(HMODULE h);

struct PatchElem {
    uint32* vec0Begin;   // +0x00
    uint32  pad04;       // +0x04
    uint32* vec0End;     // +0x08
    uint32  pad0c;       // +0x0c
    uint32* vec1Begin;   // +0x10
    uint32  pad14;       // +0x14
    uint32* vec1End;     // +0x18
    char    pad1c[0x2c - 0x1c];
    uint8_t flag2c;      // +0x2c (cleared per element)
    char    pad2d[0x38 - 0x2d];

    void* Destroy(unsigned flags);   // 0x00e206b0 (vector deleting dtor, ret 4)
};

// Base class (vtable 0x13ec458): owns data +0x04..+0x4f including the +0x44
// container that the base destructor releases.
struct ContentValidationSummarizer {
    virtual void b00();
    virtual void b04();
    virtual void b08();
    virtual void b0c();
    virtual void b10();
    virtual void b14();
    virtual void b18();
    virtual void b1c();
    // data
    void*    f04;        // +0x04
    void*    hModule;    // +0x08 (HMODULE)
    char     pad0c[0x20 - 0x0c];
    void (*fn20)(uint32, void*);  // +0x20 callback
    char     pad24[0x38 - 0x24];
    void (*fn38)();      // +0x38
    uint32   f3c;        // +0x3c
    char     pad40[0x44 - 0x40];
    WBlob    str44;      // +0x44
    uint32   f50;        // +0x50
    ~ContentValidationSummarizer();
};

struct PatchMgr : ContentValidationSummarizer {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    PatchElem* elems;    // +0x54
    int      nElems;     // +0x58
    int      idx5c;      // +0x5c
    uint32   f60;        // +0x60
    char     pad64[0x2068 - 0x64];
    WBlob    str2068;    // +0x2068

    void Apply();                  // 0x00e205e0
    ~PatchMgr();                   // 0x00e20630 (scalar deleting)
    PatchMgr();                    // 0x00e20780
    void Shutdown();               // 0x00e20800
};

// @ 0x00e20210
bool Panel12::OnMessage(uint32 msg, void* p)
{
    if (msg == 0x1e8c9e0) {
        if (f34 == 0 && id == 0x6722bd6) {
            uint32 tribe = *(uint32*)((char*)p + 8);
            GetPlayerTribe(GetNounManager());
            if (tribe == (uint32)(uintptr_t)GetPlayerTribe(GetNounManager())) {
                GetPlayerTribe(GetNounManager());
                const char* name = IsHerbivoreTribe() ? "PaletteIDTribeHerbivore"
                                                      : "PaletteIDTribeCarnivore";
                uint32 a = SPIDFromName(name, 0x41, 0);
                uint32 b = SPIDFromName("CommunityEditor", 0, a);
                uint32 c = MakeCommunityEditorID(b);
                uint32 blk[3];
                blk[0] = c;
                blk[1] = 0xb1b104;
                blk[2] = 0x406b6a00;
                ((PanelBase*)((char*)this - 0xc))->OpenEditor(blk, 0xffffffff, 0);
            }
        }
        return false;
    }
    if (msg != 0x5bf34455)
        return ((PanelBase*)this)->BaseOnMessage(msg, p);

    uint32 i = 0;
    uint32 n = checks ? checks->Count() : 0;
    for (; i < n; ++i) {
        Eff* e = checks->At(i)->Check(groupId);
        if (e) {
            Inner* in = *(Inner**)((char*)e + 0xa0);
            Dispatcher* d = GetGlobalInfo()->disp;
            d->Post(0, in->GetId(), 0x2c765c39, 0, 0);
            break;
        }
    }
    groupId = *(uint32*)((char*)p + 8);
    ((TestWin*)((char*)this - 0xc))->Refresh();
    return true;
}

// @ 0x00e20360
void TestWinEx::UpdateSlot(uint32 v)
{
    SetVisibleSlot(v);
    cString str;
    uint32 m = mode;
    if (m == 0x1654c00) {
        str.Load(0x8b96f855, 0x60c9906, L"*Cell parts unlocked*");
    } else if (m == 0x1654c01) {
        str.Load(0x8b96f855, 0x60c9907, L"*Creature parts unlocked*");
    } else if (m == 0x1654c02) {
        if (id == 0x6722bd6)
            str.Load(0x8b96f855, 0x625b1b1, L"*Tools unlocked*");
        else
            str.Load(0x8b96f855, 0x625b1b0, L"*Accessories unlocked*");
    }
    SetSlotText(str.GetText());
    if (checks != 0) {
        uint32 nNodes = 0;
        for (LNode* n = headNext; (LNode*)&headNext != n; n = n->next) ++nNodes;
        if (nNodes != 0) {
            uint32 nCats = (uint32)(cats->end - cats->begin);
            for (uint32 i = 0; i < nCats; ++i) {
                Group* g = cats->At(i);
                uint32 nPages = (uint32)(g->subsEnd - g->subsBegin);
                for (uint32 j = 0; j < nPages; ++j) {
                    Sub* pg = g->At(j);
                    uint32 nItems = (uint32)(pg->itemsEnd - pg->itemsBegin);
                    for (uint32 k = 0; k < nItems; ++k) {
                        Item* it = pg->At(k);
                        if (!it || it->a == 0) continue;
                        LNode* f = FindInList((LNode*)&headNext, it->a);
                        if (f == (LNode*)&headNext) continue;
                        uint32 cnt = checks->Count();
                        for (uint32 x = 0; x < cnt; ++x) {
                            Eff* e = checks->At(x)->Check(g->id);
                            if (e) {
                                Inner* in = *(Inner**)((char*)e + 0xa0);
                                Dispatcher* d = GetGlobalInfo()->disp;
                                d->Post(in->GetId(), id, 0x2c765c39, 0, 0);
                                break;
                            }
                        }
                    }
                }
            }
        }
        uint32 cnt = checks->Count();
        for (uint32 x = 0; x < cnt; ++x) {
            Eff* e = checks->At(x)->Check(groupId);
            if (e) { checks->Remove(e); break; }
        }
        checks->SetEnabled(true);
    }
    Refresh();
}

// base half of 0x00e20630, reached from ~PatchMgr
ContentValidationSummarizer::~ContentValidationSummarizer()
{
    if ((int)((uint32)((char*)str44.mpEnd - (char*)str44.mpBegin) & 0xfffffffe) > 2 &&
        str44.mpBegin) {
        FreeNode(str44.mpBegin);
    }
}

// Key-function definitions force MSVC to emit the vftables in this TU.
void ContentValidationSummarizer::b00() {}
void ContentValidationSummarizer::b04() {}
void ContentValidationSummarizer::b08() {}
void ContentValidationSummarizer::b0c() {}
void ContentValidationSummarizer::b10() {}
void ContentValidationSummarizer::b14() {}
void ContentValidationSummarizer::b18() {}
void ContentValidationSummarizer::b1c() {}
void PatchMgr::v00() {}
void PatchMgr::v04() {}
void PatchMgr::v08() {}
void PatchMgr::v0c() {}
void PatchMgr::v10() {}
void PatchMgr::v14() {}
void PatchMgr::v18() {}
void PatchMgr::v1c() {}

// @ 0x00e205e0
void PatchMgr::Apply()
{
    void* local = this;
    fn20(*(uint32*)((char*)elems + idx5c * 0x38 + 0x10), &local);
    for (int i = 0; i < nElems; ++i)
        ((uint8_t*)elems)[i * 0x38 + 0x2c] = 0;
    f3c = 8;
}

// @ 0x00e20630
PatchMgr::~PatchMgr()
{
    if ((int)((uint32)((char*)str2068.mpEnd - (char*)str2068.mpBegin) & 0xfffffffe) > 2 &&
        str2068.mpBegin) {
        FreeNode(str2068.mpBegin);
    }
}

// @ 0x00e206b0
void* PatchElem::Destroy(unsigned flags)
{
    if (flags & 2) {
        uint32* base = (uint32*)((char*)this - 4);
        int n = *(int*)((char*)this - 4);
        PatchElem* e = (PatchElem*)((char*)this + n * sizeof(PatchElem));
        for (int i = n - 1; i >= 0; --i) {
            --e;
            if ((int)((uint32)((char*)e->vec1End - (char*)e->vec1Begin) & 0xfffffffe) > 2 &&
                e->vec1Begin)
                FreeNode(e->vec1Begin);
            if ((int)((uint32)((char*)e->vec0End - (char*)e->vec0Begin) & 0xfffffffe) > 2 &&
                e->vec0Begin)
                FreeNode(e->vec0Begin);
        }
        if (flags & 1)
            FreeNode(base);
        return base;
    }
    if ((int)((uint32)((char*)vec1End - (char*)vec1Begin) & 0xfffffffe) > 2 && vec1Begin)
        FreeNode(vec1Begin);
    if ((int)((uint32)((char*)vec0End - (char*)vec0Begin) & 0xfffffffe) > 2 && vec0Begin)
        FreeNode(vec0Begin);
    if (flags & 1)
        FreeNode(this);
    return this;
}

// @ 0x00e20780
PatchMgr::PatchMgr()
{
    *(uint32*)((char*)this + 4) = 0;
    str44.mpBegin = 0; str44.mpCapacity = 0; str44.mpEnd = 0;
    str44.RangeInit(gEmptyWString);
    str2068.mpBegin = 0; str2068.mpCapacity = 0; str2068.mpEnd = 0;
    str2068.RangeInit(gEmptyWString);
    *(uint32*)((char*)this + 0x08) = 0;
    *(uint32*)((char*)this + 0x0c) = 0;
    *(uint32*)((char*)this + 0x38) = 0;
    *(uint32*)((char*)this + 0x10) = 0;
    *(uint32*)((char*)this + 0x14) = 0;
    *(uint32*)((char*)this + 0x18) = 0;
    *(uint32*)((char*)this + 0x1c) = 0;
    *(uint32*)((char*)this + 0x24) = 0;
    *(uint32*)((char*)this + 0x20) = 0;
    *(uint32*)((char*)this + 0x30) = 0;
    *(uint32*)((char*)this + 0x28) = 0;
    *(uint32*)((char*)this + 0x34) = 0;
    elems = 0;
    nElems = 0;
    f3c = 0;
    idx5c = -1;
    f60 = 0xffffffff;
}

// @ 0x00e20800
void PatchMgr::Shutdown()
{
    if (hModule != 0) {
        fn38();
        FreeLibrary((HMODULE)hModule);
        *(uint32*)((char*)this + 0x08) = 0;
        *(uint32*)((char*)this + 0x0c) = 0;
        *(uint32*)((char*)this + 0x38) = 0;
        *(uint32*)((char*)this + 0x10) = 0;
        *(uint32*)((char*)this + 0x14) = 0;
        *(uint32*)((char*)this + 0x18) = 0;
        *(uint32*)((char*)this + 0x1c) = 0;
        *(uint32*)((char*)this + 0x24) = 0;
        *(uint32*)((char*)this + 0x20) = 0;
        *(uint32*)((char*)this + 0x30) = 0;
        *(uint32*)((char*)this + 0x28) = 0;
        *(uint32*)((char*)this + 0x34) = 0;
    }
    if (elems != 0) {
        elems->Destroy(3);
        elems = 0;
        nElems = 0;
    }
}
