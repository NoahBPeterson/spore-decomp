// src/game/SPGonzago/_at_00e20000.cpp -- migrated from slice(s) s00e2f6e0, s00e2e6e0, s00e21880, s00e20860, s00e1fb20 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00e20000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cString.h"

// unnamed retail callees and globals (address in the comment)
extern wchar_t gEmptyWString[];     // 0x013ec468
#include <new>
#include "cSPUILayout.h"
#include <math.h>
#include "SP/cRelationshipManager.h"
#include "SP/cViewer.h"

// ---- items of slice s00e1fb20 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
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
TribeStrategy* TribeInstance();                    // 0x00cd40b0 (decl above)
NounMgr* GetNounManager();                         // 0x00b3d300
Target* __cdecl GetPlayerTribe(NounMgr* mgr);      // 0x00bfc5f0 (cGameNounManager::GetPlayerTribe)
bool __cdecl IsHerbivoreTribe();                   // 0x00c8e850
uint32 __cdecl SPIDFromName(const char* name, uint32 a, uint32 b); // 0x00571cf0
uint32 __cdecl MakeCommunityEditorID(uint32 a);    // 0x00bda3b0
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
struct PanelBase {
    void OpenEditor(uint32* blk, uint32 a, uint32 b);   // 0x00e1e500
    bool BaseOnMessage(uint32 msg, void* p);            // 0x00e18600
};
struct TestWin;
struct cString {
    char pad[0x10];
    cString();                                                        // 0x006b5060
    ~cString();                                                       // 0x006b5240
    void Load(uint32 fmt, uint32 a, const wchar_t* s);                // 0x006b54b0
    const wchar_t* GetText();                                         // 0x006b55c0
};
struct TestWinEx : TestWin {
    void SetVisibleSlot(uint32 v);            // 0x00e18860
    void SetSlotText(const wchar_t* t);       // 0x00e18890
    void UpdateSlot(uint32 v);                // 0x00e20360
};
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
ContentValidationSummarizer::~ContentValidationSummarizer()
{
    if ((int)((uint32)((char*)str44.mpEnd - (char*)str44.mpBegin) & 0xfffffffe) > 2 &&
        str44.mpBegin) {
        FreeNode(str44.mpBegin);
    }
}
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
// ---- items of slice s00e1fb20 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(HMODULE h);

// ---- items of slice s00e20860 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char* __stdcall GetCommandLineA();
extern "C" unsigned long __stdcall GetCurrentProcessId();
extern "C" double __cdecl sqrt(double);
extern float DAT_016ac208, DAT_016ac20c, DAT_016ac210;   // Translation
extern float DAT_016ac214[9];                            // rotation
extern float DAT_016a0dd0, DAT_016a0dd4, DAT_016a0dd8;   // offset vector
extern float DAT_016a0d80;                               // divisor
extern float DAT_013f4fd0;                               // 2^32
extern float DAT_0148054c;                               // 2*pi
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef          short s16;
void* __cdecl operator_new(u32 size, const char* file, int, int, int, int); // 0xf473a0
void* __cdecl FUN_0067dcc0();        // 0x0067dcc0 SP::MessageServer()
void* __cdecl FUN_0067cad0();        // 0x0067cad0 cSPBoundingBox::AddBoundingBox()
void* __cdecl FUN_006c10e0();        // 0x006c10e0 Sound/Audio::GetSystemAT
void  __cdecl FUN_00478db0(void*);   // 0x00478db0
void* __cdecl FUN_0080fac0(void*, void*, int);  // 0x0080fac0 cSPUILayeredObject::MethodFAC0
void  __cdecl FUN_0080ea50(void*);   // 0x0080ea50 RemoveAllModels
void  __cdecl FUN_0080d790(void*, int, int);    // 0x0080d790
void  __cdecl FUN_004099b0(float);   // 0x004099b0 EA::Swarm::cTransform::PreRotateY
void  __cdecl FUN_00537dc0(void*, const void*);    // 0x00537dc0 cSPTransformOps::Assign
void  __cdecl FUN_0041cb40(void*, const void*);    // 0x0041cb40 Matrix3::Assign
void  __cdecl FUN_006bac90(void*, void*);          // 0x006bac90
void  __cdecl FUN_006b9440(void*);                 // 0x006b9440 Basis3::Build
void  __cdecl FUN_004e0850(void*, const wchar_t*, ...); // 0x004e0850 wstring format
void  __cdecl FUN_0077d1d0(void*);   // 0x0077d1d0 Simulator::cCreatureAbility ctor
void* __cdecl FUN_004558a0(void*, void*, int); // 0x004558a0 VectorInsertU32
void  __cdecl FUN_0061df40(void*);   // 0x0061df40 MessageBasicRC ctor wrapper
void  __cdecl WStr_Append(void*, const wchar_t*); // 0x00429580
void  __cdecl FUN_00e205e0(void*);   // 0x00e205e0 (same obj, thiscall reg-arg)
void  __cdecl FUN_00e20f10(void*, void*); // 0x00e20f10 (same obj)
void __cdecl EA_ConvertToString16(wchar_t* out, const char* in);
struct RefObj { void** vtbl; };   // +0x00 vtable
struct SwModel {
  RefObj* mpRef;          // +0x00
  u32    mRefFlags;       // +0x04
  u16    mFlags;          // +0x08
  s16    mRefCount;       // +0x0a
  float  mPosX;           // +0x0c
  float  mPosY;           // +0x10
  float  mPosZ;           // +0x14
  float  mAngle;          // +0x18
  u8     pad1c[0x40 - 0x1c];
  s32    mRefCountObject; // +0x40
};
void SwModel_Release(SwModel* m, bool unk) {
  RefObj* r = m->mpRef;
  ((void(__thiscall*)(RefObj*, SwModel*, int))r->vtbl[0x170 / 4])(r, m, unk);
}
struct SwModelPair {
  SwModel* p0;            // +0x00
  SwModel* p1;            // +0x04
  void*    p2;            // +0x08
};
struct MapDescription {
  void** vtbl;      // +0x00 vtbl_Swarm::MapDescription
  u16    w4;        // +0x04
  u16    w6;        // +0x06
  void*  p8;        // +0x08 (points to +0xc)
  u8     data[0x10c - 0xc];
};
struct SimAbility {                 // Simulator::cCreatureAbility
  u8     pad0[0xc];
  void** vecCur;                    // +0x0c
  void** vecEnd;                    // +0x10
};
struct cSPTransform_s00e2_0860 {
  u32   mFlags;       // +0x00 (low 16 used as flag word by peers)
  u32   pad04;        // +0x04
  float mTx;          // +0x08
  float mTy;          // +0x0c
  float mTz;          // +0x10
  u32   mModCount;    // +0x14
  u32   mPad18;       // +0x18
  float mScale;       // +0x1c
  float mRot[9];      // +0x20
};
struct LayeredLocal {
  void** vtbl;        // +0x00
  u32    field04;     // +0x04
  u8     data08[0x40 - 0x08];
};
struct LayeredTriple {
  LayeredLocal* p0;   // +0x00
  LayeredLocal* p1;   // +0x04
  LayeredLocal* p2;   // +0x08
};
static void BuildBaseTransform(cSPTransform_s00e2_0860* t) {
  t->mTx = DAT_016ac208;
  t->mTy = DAT_016ac20c;
  t->mTz = DAT_016ac210;
  t->mModCount = 0;
  t->mFlags = 0;
  t->mScale = 1.0f;
  FUN_0041cb40(t->mRot, DAT_016ac214);   // Matrix3::Assign
}
struct cInstallItem {
  float  f00;        // +0x00
  u8     pad04[0x10 - 4];
  u32    mContentId; // +0x10  (4 dwords of id at 0x10..0x1f)
  u8     pad20[0x2c - 0x20];
  u8     mbChecked;  // +0x2c
  u8     mbInstalled;// +0x2d
  u8     pad2e[0x38 - 0x2e];
};
struct cInstaller {
  u8     pad00[0x08];
  void*  mpObject;      // +0x08
  u8     pad0c[0x10 - 0x0c];
  bool (*mpfnIsReady)(void);                                   // +0x10
  u8     pad14[0x1c - 0x14];
  bool (*mpfnTest)(u32, void*);                                // +0x1c
  bool (*mpfnTest2)(u32, void*);                               // +0x24
  bool (*mpfnCheck)(void*, void*, u32, void*);                 // +0x2c
  void (*mpfnEval)(u32, void*, void*);                         // +0x30
  u8     pad34[0x3c - 0x34];
  int    mState;        // +0x3c
  u8     pad40[0x54 - 0x40];
  cInstallItem* mpItems;// +0x54
  int    mItemCount;    // +0x58
  int    mIndex;        // +0x5c
  u8     pad60[0x64 - 0x60];
  int    mControlValue; // +0x64
};
static void FormatInstallItem(cInstallItem* it) {
  wchar_t id[4];
  *(u32*)id = it->mContentId;
  FUN_004e0850(&id, L"<InstallItem ContentId=\"%s\"/>", it->mContentId, 0, 0, 0);
  WStr_Append(id, id);
}
struct BehaviorMessage {
  void** vtbl;      // +0x00
  u32    mRefCount; // +0x04
  s32    mSub;      // +0x08 (index 2)
  u8     pad0c[0x30 - 0x0c];
  u32    mKind;     // +0x30 (index 0xc)
  u8     pad34[0x38 - 0x34];
  u32    mF38;      // +0x38
};
static BehaviorMessage* MakeBehaviorMessage() {
  BehaviorMessage* m = (BehaviorMessage*)operator_new(0x40, "App", 0, 0, 0, 0);
  if (!m)
    return 0;
  m->mKind = 0;
  m->vtbl = (void**)0x13eb90c;     // vtbl_UI::BehaviorMessage
  m->mRefCount = 0;                // locked xchg in retail
  m->vtbl = (void**)0x13eb844;     // derived vtable
  m->mF38 = 0;
  ((void(__thiscall*)(BehaviorMessage*))m->vtbl[1])(m);
  return m;
}
static void PostMessage(u32 kind, void* payload) {
  void* srv = FUN_0067dcc0();      // MessageServer
  ((void(__thiscall*)(void*, u32, void*, int))(*(void***)srv)[0x14 / 4])(srv, kind, payload, 0);
}
// ---- items of slice s00e20860 end

// ---- items of slice s00e21880 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IWindow;
struct IWindow {
    virtual void      v000();                               // +0x00
    virtual void      v004();                               // +0x04
    virtual void      v008();                               // +0x08
    virtual void*     Cast(uint32_t nType);                 // +0x0c
    virtual IWindow*  GetParent();                          // +0x10
    virtual void      v014();
    virtual void      v018();
    virtual uint32_t  GetTypeID();                          // +0x1c
    virtual uint32_t  GetFlags();                           // +0x20
    virtual void      v024();
    virtual void      v028(int32_t nSlot, void* pValue);    // +0x28
    virtual void      v02c();
    virtual void      v030();
    virtual void      v034();
    virtual float*    GetRect();                            // +0x38
    virtual void      v03c();
    virtual void      v040();
    virtual IWindow*  v044(const float* pPoint);            // +0x44
    virtual void      v048();
    virtual void      v04c();
    virtual void      v050();
    virtual IWindow*  v054(bool bUnknown);                  // +0x54
    virtual void      v058(bool bArg1, bool bArg2);         // +0x58
    virtual void      v05c();
    virtual void      v060();
    virtual void      v064();
    virtual void      v068();
    virtual void      v06c();
    virtual void      v070(float fX, float fY);             // +0x70
    virtual void      v074(float fWidth, float fHeight);    // +0x74
    virtual void      v078();
    virtual void      v07c(bool bArg1, bool bArg2);         // +0x7c
    virtual void      v080(const char* pText);              // +0x80
    virtual void      v084();
    virtual void      v088();
    virtual int32_t   v08c();                               // +0x8c
    virtual void      v090();
    virtual void      v094();
    virtual void      v098();
    virtual void      v09c();
    virtual void      v0a0(void (*pfnCallback)(), void* pArg);  // +0xa0
    virtual void      v0a4();
    virtual void      v0a8();
    virtual void      v0ac();
    virtual void      v0b0();
    virtual bool      v0b4();                               // +0xb4
    virtual void      v0b8(IWindow* pArg1, IWindow* pArg2); // +0xb8
    virtual void      v0bc();
    virtual float*    v0c0(const float* pPoint);            // +0xc0
    virtual IWindow*  v0c4();                               // +0xc4
    virtual void      v0c8();
    virtual void      v0cc();
    virtual void      v0d0();
    virtual void      v0d4();
    virtual void      v0d8();
    virtual void      v0dc(void* pArg);                     // +0xdc
    virtual void      v0e0();
    virtual void      v0e4();
    virtual void      v0e8(IWindow* pWindow);               // +0xe8
    virtual void      v0ec();
    virtual IWindow*  FindWindowByID(uint32_t nID, bool bRecursive);   // +0xf0
    virtual void      v0f4();
    virtual void      v0f8();
    virtual void      v0fc();
    virtual void      v100();
    virtual void      v104();
    virtual void      v108(void* pArg);                     // +0x108
};
void            __cdecl SPUIFrameCallbackA();              // 0x00e21700
void            __cdecl SPUIFrameCallbackB();              // 0x00e21720
// ---- items of slice s00e21880 end

// ---- items of slice s00e2e6e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float  g_kHundred;               // 0x013ec4d0 100.0f
extern float  g_kPercent;               // 0x013eb960 0.01f
uint32_t __cdecl GetPlayerEmpireID();                                  // 0x01021090
class tIWindow;
class tIWindow {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04 Release
    virtual void* v08();                        // +0x08
    virtual void* v0c(uint32_t nKey);           // +0x0c
    virtual void* v10();                        // +0x10
    virtual void  v14(void* pState);            // +0x14
    virtual void  v18();                        // +0x18
    virtual void  v1c();                        // +0x1c
    virtual void  v20();                        // +0x20
    virtual void  v24();                        // +0x24
    virtual void  v28(int32_t nState);          // +0x28
    virtual void* v2c();                        // +0x2c
    virtual void  v30(int32_t nA, int32_t nB);  // +0x30
    virtual void*    v34();                     // +0x34
    virtual void*    v38();                     // +0x38
    virtual void*    v3c(uint32_t nKey, int32_t nFlag); // +0x3c
    virtual void*    v40();                     // +0x40
    virtual void*    v44();                     // +0x44
    virtual uint32_t v48();                     // +0x48
    virtual int32_t  v4c();                     // +0x4c
    virtual void*    v50();                     // +0x50
    virtual uint32_t v54();                     // +0x54
    virtual uint32_t v58();                     // +0x58
    virtual void     v5c(int32_t nState);       // +0x5c sets the strip state
    virtual void     v60(int32_t nState);       // +0x60
    virtual void     v64();                     // +0x64
    virtual void     v68();                     // +0x68
    virtual void     v6c();                     // +0x6c
    virtual float    v70();                     // +0x70
    virtual void     v74();                     // +0x74
    virtual void     v78();                     // +0x78
    virtual void     v7c(int32_t nA, int32_t nB); // +0x7c visible/state pair
    virtual void     v80();                     // +0x80
    virtual void     v84();                     // +0x84
    virtual void     v88();                     // +0x88
    virtual void     v8c(void* pValue);         // +0x8c
    virtual void     v90();                     // +0x90
    virtual void     v94();                     // +0x94
    virtual void*    v98();                     // +0x98
    virtual void*    v9c();                     // +0x9c
    virtual void*    va0();                     // +0xa0
    virtual void*    va4();                     // +0xa4
    virtual void*    va8();                     // +0xa8
    virtual void*    vac();                     // +0xac
    virtual void*    vb0();                     // +0xb0
    virtual void*    vb4();                     // +0xb4
    virtual void*    vb8();                     // +0xb8
    virtual void*    vbc();                     // +0xbc
    virtual void*    vc0();                     // +0xc0
    virtual void*    vc4();                     // +0xc4
    virtual void*    vc8();                     // +0xc8
    virtual void*    vcc();                     // +0xcc
    virtual void*    vd0();                     // +0xd0
    virtual void*    vd4();                     // +0xd4
    virtual void*    vd8();                     // +0xd8
    virtual void*    vdc();                     // +0xdc
    virtual void*    ve0();                     // +0xe0
    virtual void*    ve4();                     // +0xe4
    virtual void*    ve8();                     // +0xe8
    virtual void*    vec();                     // +0xec
    virtual void*    vf0(uint32_t nKey, int32_t nFlag); // +0xf0
};
class cRelationshipManager {
public:
    bool  FUN_00d01b50(uint32_t nEmpireA, uint32_t nEmpireB);   // 0x00d01b50
    float FUN_00d00d00(uint32_t nEmpireA, uint32_t nEmpireB);   // 0x00d00d00
    int32_t FUN_00d00780(float fValue);                         // 0x00d00780
};
cRelationshipManager* __cdecl RelationshipManager();    // 0x00b3d2c0
void   __cdecl FUN_00807430(void* pWindow, float fAmount);                      // 0x00807430
// ---- items of slice s00e2e6e0 end

// ---- items of slice s00e2f6e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
typedef int intptr_t;
#define nullptr 0
struct Rect {
    float mX;
    float mY;
    float mWidth;
    float mHeight;
};
class IRefCounted {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};
class IWindow_s00e2_f6e0 : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual void SetVisible(bool bVisible);
    virtual void v20();
    virtual void v24();
    virtual void v28(int a);
    virtual void v2c();
    virtual Rect* GetArea();
    virtual void SetPosition(float fX, float fY);
    virtual void SetScale(float fScale);
};
class cSPUILayout_s00e2_f6e0 {
public:
    void Init(const wchar_t* pName, uint32_t a, int b, uint32_t c);  // 0x00812160 (cSPUILayout::Init)
    IWindow_s00e2_f6e0* FindWindowByID(uint32_t nId, int bFind);  // 0x008105b0 (cSPUILayout::FindWindowByID)
};
class cMessageServer {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20(void* pTarget, uint32_t nMessage);
    virtual void v24();
    virtual void v28(void* pTarget, uint32_t nMessage, int nData);
    virtual void v2c(void* pTarget, uint32_t nMessage, int nData);
};
class cSPUIAnimator_s00e2_f6e0 {
public:
    void AddAnimation(void* pAnimation, void* pTarget, int nKind);  // 0x007f8d10 (cSPUIAnimator::AddAnimation)
    void RemoveAnimation(void* pTarget, int nIndex);  // 0x007f6210 (cSPUIAnimator::RemoveAnimation)
    void Update();  // 0x007f63b0 (cSPUIAnimator::Update)
};
class cSPAssetData : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    bool IsDiscovered();
    uint8_t mPad18[0x08];
};
class cSPUIAssetView : public IWindow_s00e2_f6e0 {
public:
    void Bind(IWindow_s00e2_f6e0* pParent, cSPAssetData* pData, int a, int b);
};
class cMessageTarget {
public:
    virtual void v00();
    virtual void v04();
};
class cSPUIAssetDiscoveryCard : public IRefCounted {
public:
    void Init();
    void ApplyFrame(int* pData);
    cSPUIAssetDiscoveryCard* Clone();

    cSPUILayout_s00e2_f6e0* mpLayout;              // 0x00
    IWindow_s00e2_f6e0* mpParentWin;               // 0x04
    uint8_t mPad08[0x08];               // 0x08
    IWindow_s00e2_f6e0* mpTextWindow;              // 0x10
    cSPAssetData* mpAssetData;          // 0x14
    cSPUIAssetView* mpAssetView;        // 0x18
};
class cSPUIAssetDiscoveryManager : public cMessageTarget {
public:
    void Init();
    void ReloadTuning();
    void Shutdown();
    void Reset();
    void Update(uint nMilliseconds);
    int HandleCardMessage(int nMessage, int nData, int nFlags);
    int HandleAssetMessage(int nMessage, int nData);
    void ReleaseCurrentCard();
    void PushCard(cSPUIAssetDiscoveryCard** ppCard, int nFlags);

    uint8_t mPad14[0x0c];               // 0x14
    void* mpMessageTarget;              // 0x20
    uint8_t mPad24[0x08];               // 0x24
    cSPUIAssetDiscoveryCard** mpCardsBegin;   // 0x2c
    cSPUIAssetDiscoveryCard** mpCardsCur;     // 0x30
    cSPUIAssetDiscoveryCard** mpCardsEnd;     // 0x34
    cSPUIAssetDiscoveryCard** mpCardsCap;     // 0x38
    cSPUIAssetDiscoveryCard* mpCurrentCard;   // 0x3c
    cSPUIAssetDiscoveryCard* mpSelectedCard;  // 0x50
    int mnPaused;                       // 0x54
    int mnAnimationState;               // 0x58
    cSPUIAnimator_s00e2_f6e0* mpAnimator;          // 0x5c
    uint64_t mnElapsed;                 // 0x60
    int mnSlideInStart;                 // 0x68
    int mnSlideOutStart;                // 0x6c
    int mnRotateStart;                  // 0x70
    int mnZoomStart;                    // 0x74
    int mnStopLow;                      // 0x78
    int mnStopHigh;                     // 0x7c
    int mnScaleLow;                     // 0x80
    int mnScaleHigh;                    // 0x84
    int mnRotateLow;                    // 0x88
    int mnRotateHigh;                   // 0x8c
    int mnZoomLow;                      // 0x90
    int mnZoomHigh;                     // 0x94
    int mnFinalLow;                     // 0x98
    int mnFinalHigh;                    // 0x9c
    float mFinalScale;                  // 0xa0
    float mTimeStart;                   // 0xa4
    float mTimeScaleBack;               // 0xa8
    float mTimeRotate;                  // 0xac
    float mTimeStop;                    // 0xb0
    float mTime;                        // 0xb4
    int mCount;                         // 0xb8
    int64_t mTimeStopMS;                // 0xbc
    int64_t mTimeStartMS;               // 0xc4
    int64_t mTimeScaleBackMS;           // 0xcc
    int64_t mTimeRotateMS;              // 0xd4
    int64_t mTimeMS;                    // 0xdc
};
void* operator_new(size_t nSize, const char* pName, int a, int b, const char* pFile, int nLine);
void* operator_new(size_t nSize, const char* pName, int a, int b, int c, int d);
void operator_delete__(void* pMemory);
void* MessageServer();
void* GetPropertyAsFloat();
void* GetPropertyAsKeyArray();
void* GetPropertyAsVariant(void* pValue, int a);
bool QueryProperty(void* pData, uint32_t nKey, void** ppOut);
void* CreateTimer();
void ReleaseCardResource(int a);
void* GetCardTarget(void* pCard);
// ---- items of slice s00e2f6e0 end

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

// @ 0x00e20860
void __fastcall FUN_00e20860(cInstaller* self, s32)
{
  if (!self->mpObject)
    return;

  bool ready = self->mpfnIsReady();
  if (!ready && self->mState != 9) {
    BehaviorMessage* m = MakeBehaviorMessage();
    if (!m) {
      // allocation failed: nothing to post
    } else {
      m->mKind = 0x5d676ed;
      m->mSub  = 0;
      PostMessage(m->mKind, m);
    }
    if (self->mState == 2)
      FUN_00e205e0(self);
    self->mState = 9;
    if (m)
      ((void(__thiscall*)(BehaviorMessage*))m->vtbl[2])(m);
    return;
  }

  switch (self->mState) {
  case 1: {
    void* out = 0;
    bool r = self->mpfnTest(self->mpItems[self->mIndex].mContentId, &out);
    self->mState = r ? 2 : 9;
    break;
  }
  case 2: {
    s32 out = 0;
    self->mpfnEval(self->mpItems[self->mIndex].mContentId, &self->mControlValue, &out);
    if (out == 7 || out == 8 || out == 9 || out == 10) {
      BehaviorMessage* m = MakeBehaviorMessage();
      FUN_0061df40(m);
      m->mKind = 0x5d676ed;
      switch (out) {
        case 7:  m->mSub = 1; break;
        case 8:  m->mSub = 2; break;
        case 9:  m->mSub = 0; break;
        case 10: m->mSub = 3; break;
      }
      PostMessage(m->mKind, m);
      FUN_00e205e0(self);
      self->mState = 9;
      ((void(__thiscall*)(BehaviorMessage*))m->vtbl[2])(m);
      return;
    }
    if (self->mControlValue == 100) {
      cInstallItem* it = &self->mpItems[self->mIndex];
      it->mbChecked = 0;
      it->mbInstalled = 1;
      self->mIndex++;
      if (self->mIndex < self->mItemCount) {
        self->mControlValue = 0;
        self->mState = 1;
        return;
      }
      self->mState = 0xb;
      PostMessage(0x5d66be3, 0);
      return;
    }
    break;
  }
  case 3: {
    // Build the "<InstallItems>...</InstallItems>" payload and hand it off.
    for (int i = 0, off = 0; i < self->mItemCount; i++, off += sizeof(cInstallItem)) {
      cInstallItem* it = (cInstallItem*)((char*)self->mpItems + off);
      if (it->mbInstalled)
        FormatInstallItem(it);
    }
    const char* cmd = GetCommandLineA();
    wchar_t cmdline[260];
    EA_ConvertToString16(cmdline, cmd);
    unsigned pid = GetCurrentProcessId();
    wchar_t out[260];
    bool ok = self->mpfnCheck(out, (void*)pid, pid, cmdline);
    if (!ok) {
      BehaviorMessage* m = MakeBehaviorMessage();
      m->mKind = 0x5d676ed;
      m->mSub = 4;
      PostMessage(m->mKind, m);
      self->mState = 9;
      ((void(__thiscall*)(BehaviorMessage*))m->vtbl[2])(m);
    } else if (pid == 0) {
      BehaviorMessage* m = MakeBehaviorMessage();
      FUN_0061df40(m);
      m->mKind = 0x5d676ed;
      m->mSub = 4;
      PostMessage(m->mKind, m);
      self->mState = 9;
      ((void(__thiscall*)(BehaviorMessage*))m->vtbl[2])(m);
    } else if (pid == 3) {
      void* srv = FUN_0067dcc0();
      ((void(__thiscall*)(void*, void*, void*, int, int))(*(void***)srv)[0x18 / 4])(srv, (void*)0x0153c326, 0, 0, 0);
      self->mState = 0xb;
    }
    break;
  }
  case 4:
  case 6: {
    void* out = 0;
    bool r = self->mpfnTest2(self->mpItems[self->mIndex].mContentId, &out);
    if (r)
      self->mState = (self->mState != 6 ? 2 : 5);
    break;
  }
  }
}

// @ 0x00e20d30
void __fastcall FUN_00e20d30(SwModelPair* self, s32, float angle)
{
  if (self->p0) {
    self->p0->mRefCount++;
    self->p0->mAngle = angle;
  }
  if (self->p1) {
    self->p1->mRefCount++;
    self->p1->mAngle = angle;
  }
}

// @ 0x00e20d60
void __fastcall FUN_00e20d60(SwModelPair* self, s32)
{
  if (self->p0) {
    self->p0->mPosX += DAT_016a0dd0;
    self->p0->mPosY += DAT_016a0dd4;
    self->p0->mPosZ += DAT_016a0dd8;
    self->p0->mFlags |= 4;
    self->p0->mRefCount++;
  }
  if (self->p1) {
    self->p1->mPosX += DAT_016a0dd0;
    self->p1->mPosY += DAT_016a0dd4;
    self->p1->mPosZ += DAT_016a0dd8;
    self->p1->mFlags |= 4;
    self->p1->mRefCount++;
  }
}

// @ 0x00e20e00
void __fastcall FUN_00e20e00(SwModelPair* self)
{
  if (self->p0) {
    SwModel* m = self->p0;
    self->p0 = 0;
    if (m->mRefCountObject <= 1)
      SwModel_Release(m, (m->mRefFlags >> 31) != 0);
    else
      m->mRefCountObject--;
  }
  if (self->p1) {
    SwModel* m = self->p1;
    self->p1 = 0;
    if (m->mRefCountObject <= 1)
      SwModel_Release(m, (m->mRefFlags >> 31) != 0);
    else
      m->mRefCountObject--;
  }
}

// @ 0x00e20e80
void __fastcall FUN_00e20e80(SwModelPair* self)
{
  if (self->p0) {
    SwModel* m = self->p0;
    self->p0 = 0;
    if (m->mRefCountObject <= 1)
      SwModel_Release(m, (m->mRefFlags >> 31) != 0);
    else
      m->mRefCountObject--;
  }
  if (self->p1) {
    SwModel* m = self->p1;
    self->p1 = 0;
    if (m->mRefCountObject <= 1)
      SwModel_Release(m, (m->mRefFlags >> 31) != 0);
    else
      m->mRefCountObject--;
  }
  if (self->p2) {
    void* m = self->p2;
    self->p2 = 0;
    ((void(__thiscall*)(void*))(*(void***)m)[8 / 4])(m);
  }
}

// @ 0x00e20f10
void __cdecl FUN_00e20f10(void* model, float* dir)
{
  void* sys = FUN_006c10e0();                     // Sound/Audio get
  void* ob  = ((void*(__thiscall*)(void*, void*))(*(void***)sys)[0xa8 / 4])(sys, model);
  if (!ob)
    return;
  void* basis = *(void**)((char*)ob + 8);

  float x = dir[0], y = dir[1], z = dir[2];
  float inv = 1.0f / (float)sqrt((double)(x * x + y * y + z * z));

  cSPTransform_s00e2_0860 xf;
  xf.mFlags = 0;
  xf.mTx = DAT_016ac208;
  xf.mTy = DAT_016ac20c;
  xf.mTz = DAT_016ac210;
  xf.mModCount = 0;
  xf.mScale = 1.0f;
  FUN_0041cb40(xf.mRot, DAT_016ac214);           // Matrix3::Assign

  float n[3];
  n[0] = x * inv;
  n[1] = y * inv;
  n[2] = z * inv;

  float pos[3];
  pos[0] = 0.0f; pos[1] = 0.0f; pos[2] = 1.0f;
  FUN_006bac90(n, pos);
  FUN_006b9440(basis);                            // Basis3::Build
}

// @ 0x00e21040
void __fastcall FUN_00e21040(SwModelPair* self, s32, s32 frame)
{
  if (!self->p0)
    return;
  float f = (float)frame;
  if (frame < 0)
    f += DAT_013f4fd0;
  f = (f / DAT_016a0d80) * DAT_0148054c;
  ((void(__thiscall*)(void*, float))FUN_004099b0)((char*)self->p0 + 8, f);
  ((void(__thiscall*)(void*, float))FUN_004099b0)((char*)self->p1 + 8, f);
  FUN_00e20f10(self->p0, (float*)&DAT_016a0dd0);
  FUN_00e20f10(self->p1, (float*)&DAT_016a0dd0);
}

// @ 0x00e210b0
void __cdecl FUN_00e210b0(void* effect)
{
  if (!effect)
    return;
  *(u32*)((char*)effect + 4) |= 0x12;

  MapDescription* md = (MapDescription*)operator_new(0x10c, "Simulator", 0, 0, 0, 0);
  if (md) {
    md->w4 = 0x206;
    md->w6 = 0x100;
    md->vtbl = (void**)0x1453948;   // vtbl_Swarm::MapDescription
    md->p8 = (char*)md + 0xc;
  }
  float* f = (float*)((char*)md + 0xc);
  f[0] = 1.0f; f[1] = 0.0f; f[2] = 0.0f; f[3] = 0.0f;
  f[4] = 0.0f; f[5] = 1.0f; f[6] = 0.0f; f[7] = 0.0f;
  f[8] = 0.0f; f[9] = 0.0f; f[10] = 1.0f; f[11] = 0.0f;
  f[12] = 0.0f; f[13] = 0.0f; f[14] = 0.0f; f[15] = 1.0f;

  SimAbility* ca = (SimAbility*)operator_new(0x1c, "Simulator", 0, 0, 0, 0);
  if (ca)
    FUN_0077d1d0(ca);

  void** cur = ca->vecCur;
  void*  mdv = md;
  if (cur < ca->vecEnd) {
    ca->vecCur = cur + 1;
    if (cur)
      *cur = mdv;
  } else {
    FUN_004558a0(cur, &mdv, 0);
  }
  void* box = FUN_0067cad0();            // cSPBoundingBox::AddBoundingBox
  void* sys = ((void*(__thiscall*)(void*))FUN_006c10e0)(box);
  ((void(__thiscall*)(void*, void*, void*, int))(*(void***)sys)[0xa4 / 4])(sys, effect, ca, -1);
}

// @ 0x00e21260
void __fastcall FUN_00e21260(LayeredTriple* self, s32, void* a, void* b, LayeredLocal* newLocal)
{
  LayeredLocal* old = self->p2;
  if (newLocal != old) {
    if (newLocal)
      ((void(__thiscall*)(LayeredLocal*))(*(void***)newLocal)[4 / 4])(newLocal);  // AddRef
    self->p2 = newLocal;
    if (old)
      ((void(__thiscall*)(LayeredLocal*))(*(void***)old)[8 / 4])(old);            // Release
  }

  cSPTransform_s00e2_0860 xform;
  BuildBaseTransform(&xform);
  if (self->p0) {
    FUN_00537dc0(&xform, (char*)self->p0 + 8);   // cSPTransformOps::Assign(dst, &p0->transform)
  } else {
    xform = xform;   // keep the base transform (p0 null)
  }

  if (newLocal) {
    FUN_0080ea50(newLocal);                      // RemoveAllModels
    FUN_00478db0(FUN_0080fac0(self->p0->field04 ? (void*)self->p0->field04 : 0, 0, 0));
    FUN_00478db0(FUN_0080fac0(*(void**)((char*)self->p1 + 4), 0, 0));
    FUN_0080d790(newLocal, 1, 1);
    self->p0->field04 |= 1;
    ((LayeredLocal*)self->p1)->field04 |= 1;
    FUN_00537dc0((char*)self->p0 + 8, &xform);
    FUN_00537dc0((char*)self->p1 + 8, &xform);
    FUN_00e210b0(self->p0);
    FUN_00e210b0(self->p1);
  }
}

// @ 0x00e21960
void __fastcall PosseSetFrameCallbackA(IWindow* pThis)
{
    pThis->v0a0(SPUIFrameCallbackA, 0);
}

// @ 0x00e21980
void __fastcall PosseSetFrameCallbackB(IWindow* pThis)
{
    pThis->v0a0(SPUIFrameCallbackB, 0);
}

// @ 0x00e21ab0
int32_t SPUIInvalidIndex()
{
    return -1;
}

// @ 0x00e2e6e0
void __cdecl FUN_00e2e6e0(uint32_t nEmpire, tIWindow* pWindow)
{
    uint32_t nPlayer = GetPlayerEmpireID();
    bool bFriend = nEmpire == nPlayer;
    if (nEmpire != 0xffffffffu && nPlayer != 0xffffffffu && nPlayer != nEmpire)
        bFriend = RelationshipManager()->FUN_00d01b50(nEmpire, nPlayer);
    if (pWindow != 0)
    {
        pWindow->v7c(1, bFriend);
        if (bFriend)
        {
            float fAmount = g_kHundred;
            if (nEmpire != nPlayer)
                fAmount = RelationshipManager()->FUN_00d00d00(nEmpire, nPlayer);
            FUN_00807430(pWindow, fAmount * g_kPercent);
        }
    }
}

// @ 0x00e2fcb0
void cSPUIAssetDiscoveryCard::ApplyFrame(int* pData)
{
    if (pData == nullptr)
        return;

    void* pValue = nullptr;
    if (QueryProperty(pData, 0x689fa1bu, &pValue)) {
        if (*(int16_t*)((uint8_t*)pValue + 0x12) == 10)
            mpAssetData = (cSPAssetData*)GetPropertyAsFloat();
    }
    if (QueryProperty(pData, 0x689fa1du, &pValue)) {
        if (*(int16_t*)((uint8_t*)pValue + 0x12) == 1)
            mpTextWindow = (IWindow_s00e2_f6e0*)GetPropertyAsKeyArray();
    }

    void* pVariant = nullptr;
    GetPropertyAsVariant(&pVariant, 0x689fa1cu);
    ReleaseCardResource(0);
}

// @ 0x00e2fd40
void cSPUIAssetDiscoveryManager::ReleaseCurrentCard()
{
    cSPUIAssetDiscoveryCard** ppCurrent = mpCardsBegin;
    if (ppCurrent + 1 == mpCardsEnd) {
        if (*ppCurrent != nullptr)
            (*ppCurrent)->Release();
        if (mpCardsCur != nullptr)
            operator_delete__(mpCardsCur);
        mpCardsCap = mpCardsEnd + 1;
        mpCardsEnd = (cSPUIAssetDiscoveryCard**)(intptr_t)*mpCardsCap;
        mpCardsCur = mpCardsEnd;
        mpCardsBegin = mpCardsCur;
    } else {
        mpCardsBegin = ppCurrent + 1;
        if (*ppCurrent != nullptr)
            (*ppCurrent)->Release();
    }
}

// @ 0x00e2fda0
cSPUIAssetDiscoveryCard* cSPUIAssetDiscoveryCard::Clone()
{
    cSPUIAssetDiscoveryCard* pCopy = (cSPUIAssetDiscoveryCard*)
        (intptr_t)operator_new(0x18, "Simulator", 0, 0, "EASTL/allocator.h", 0xd1);
    if (pCopy != nullptr) {
        pCopy->mpLayout = mpLayout;
        pCopy->mpParentWin = mpParentWin;
        if (mpTextWindow != nullptr)
            mpTextWindow->AddRef();
        pCopy->mpTextWindow = mpTextWindow;
        if (mpAssetData != nullptr)
            mpAssetData->AddRef();
        pCopy->mpAssetData = mpAssetData;
        if (mpAssetView != nullptr)
            mpAssetView->AddRef();
        pCopy->mpAssetView = mpAssetView;
    }
    if (pCopy != nullptr)
        pCopy->mpParentWin = nullptr;
    return pCopy;
}

// @ 0x00e2fe10
void cSPUIAssetDiscoveryManager::Init()
{
    cMessageServer* pServer = (cMessageServer*)MessageServer();
    pServer->v20((cMessageTarget*)this, 0xf62defu);
    pServer = (cMessageServer*)MessageServer();
    pServer->v20((cMessageTarget*)this, 0xd33b6aa2u);
    pServer = (cMessageServer*)MessageServer();
    pServer->v20((cMessageTarget*)this, 0x533b6aa4u);

    ReloadTuning();

    if (mpAnimator == nullptr) {
        void* pMemory = (void*)(intptr_t)operator_new(0x20, "UI/AssetDiscoveryAnimator", 0, 0, 0, 0);
        if (pMemory != nullptr)
            mpAnimator = (cSPUIAnimator_s00e2_f6e0*)CreateTimer();
        else
            mpAnimator = nullptr;
    }
}

// @ 0x00e2feb0
int cSPUIAssetDiscoveryManager::HandleAssetMessage(int nMessage, int nData)
{
    if (nMessage == 0xf62def && nData == 0x689fa1a) {
        int nAssetId = 0;
        cSPUIAssetDiscoveryCard** ppCard = nullptr;
        GetCardTarget(&ppCard);
        cSPUIAssetDiscoveryCard** ppEnd = mpCardsBegin + 0;
        while (ppCard != ppEnd) {
            if (*(int*)ppCard == nAssetId)
                (*ppCard)->ApplyFrame((int*)(ppCard + 1));
            ppCard = (cSPUIAssetDiscoveryCard**)(intptr_t)((void**)ppCard)[5];
            while (ppCard == nullptr)
                ppCard = (cSPUIAssetDiscoveryCard**)(intptr_t)((void**)ppCard)[1];
        }
        return 1;
    }
    return 1;
}
