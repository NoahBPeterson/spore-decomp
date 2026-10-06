// Slice s00f0ac40 - Simulator/creator UI list and container helpers.
// /O2 /MD /Gy /EHsc /TP /arch:SSE region.
//
// A tool-panel UI: a global state block (g_16c7d90) holds five {window, index,
// savedA, savedB} entries, each index selecting a list of 0x44-byte records kept in
// vector-like containers {begin, end, cap}.
#include "types.h"

typedef unsigned int uint;

// UI window interface (vtable slots by index; byte offset in comment)
struct IWin {
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual IWin* QueryInterface(uint id);  // 0xc
    virtual IWin* GetParent();  // 0x10
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void SetState(int a, int b);  // 0x28
    virtual void* Query(float f, void* out, int a, int b, int c);  // 0x2c
    virtual void pad12();
    virtual float* GetArea();  // 0x34
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual void SetFlags(int v);  // 0x5c
    virtual void SetText(const void* s, int b);  // 0x60
    virtual void SetPos(float x, float y);  // 0x64
    virtual void SetFontStyle(int v);  // 0x68
    virtual void pad27();
    virtual void pad28();
    virtual void pad29();
    virtual void pad30();
    virtual void SetVisible(int a, int b);  // 0x7c
    virtual void SetImage(const void* p);  // 0x80
    virtual void pad33();
    virtual void pad34();
    virtual void pad35();
    virtual void pad36();
    virtual void pad37();
    virtual void pad38();
    virtual void pad39();
    virtual void pad40();
    virtual void pad41();
    virtual void pad42();
    virtual void pad43();
    virtual void pad44();
    virtual void pad45();
    virtual void pad46();
    virtual void AddRef();  // 0xbc
    virtual void Release();  // 0xc0
    virtual void pad49();
    virtual void pad50();
    virtual void pad51();
    virtual void pad52();
    virtual void pad53();
    virtual void pad54();
    virtual void pad55();
    virtual void pad56();
    virtual void pad57();
    virtual void pad58();
    virtual void pad59();
    virtual IWin* FindChild(uint id, int recurse);  // 0xf0
};

struct SubObj {                             // 0x3c bytes at +4 of a Rec
    uint pad[15];
    void Dtor();                            // 0xf280f0
    void CopyCtor(const SubObj* src);       // 0xdfb280
    void* Name();                           // 0xf26360
    uint  Flags();                          // 0xf26380
};
struct Rec {                                // 0x44 bytes
    int    kind;                            // +0x00
    SubObj sub;                             // +0x04
    int    icon;                            // +0x40
    Rec* Ctor();                            // 0xf28b30
};
struct RecVec {
    Rec* mpBegin; Rec* mpEnd; Rec* mpCap;   // vector<Rec> at +0 of a container
    Rec* erase(Rec* first, Rec* last);      // 0xf0b0e0
    void insert_n(Rec* pos, uint n, const Rec& val);  // 0xf0b150
    void resize(uint n);                    // 0xf0b390
};

struct Ctx {                                // g_16c7d90->ctx
    uint pad0[0x1c];
    char* recBegin;                         // +0x70: array of 0x4e0-byte records
    char* recEnd;                           // +0x74
    char Check();                           // 0xf25670
};
struct Entry { IWin* win; int idx; int savedA; int savedB; };
struct Tool { IWin* panel; int state; int a; int b; };
struct UIState {                            // *g_16c7d90
    void* layout;                           // +0x00 cSPUILayout*
    Ctx*  ctx;                              // +0x04
    char* owner;                            // +0x08
    int   mode;                             // +0x0c
    Entry entries[5];                       // +0x10
    uint  pad[8];
    Tool* tool;                             // +0x80
};
extern UIState* g_16c7d90;

extern "C" int  ScenarioTutorials_GetActive();                 // 0xefc520
extern "C" Rec* FUN_00dfb930(Rec* last, Rec* end, Rec* first); // eastl::copy
extern "C" Rec* FUN_00f09db0(Rec* a, Rec* b, Rec* dst);
extern "C" void FUN_00f07bd0(Rec* a, Rec* b, Rec* dst);
extern "C" void FUN_00f09d70(Rec* dst, uint n, const Rec* val, Rec* hint);
extern "C" void FUN_00f09880(Rec* a, Rec* b, Rec* c);
extern "C" void FUN_00f09800(Rec* a, Rec* b, const Rec* val);
extern "C" void FUN_00dfb8e0(Rec** out, Rec* a, Rec* b, Rec* c, Rec* d);
extern "C" void* operator_new(uint size, const char* tag, int a, int b, const char* file, int line);
extern "C" void operator_delete__(void* p);

// SubObj/Rec/Ctx helpers (thiscall members)
extern "C" void FUN_00f0aa80();

struct Layout { IWin* FindWindowByID(uint id, int b); };  // cSPUILayout::FindWindowByID @ 0x8105b0
extern "C" void* SPUIHelpers_SetButtonState(IWin* w, int b);   // 0x806880
extern "C" void  SPUIHelpers_SetImageIcon(IWin* w, void* img, int b);  // 0x806aa0

struct WinMgr {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4();
    virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9();
    virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14();
    virtual void p15(); virtual void p16(); virtual void p17();
    virtual IWin* GetWindowList(int a);                         // 0x48
    virtual void SetWindowList(int a, void* w);                 // 0x4c
};
extern WinMgr* WindowManager();                                 // 0x67caa0

static const char kEastlFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// @ 0x00f0b0e0
Rec* RecVec::erase(Rec* first, Rec* last)
{
    Rec* dst = FUN_00dfb930(last, mpEnd, first);
    Rec* end = mpEnd;
    for (; dst < end; ++dst)
        dst->sub.Dtor();
    mpEnd -= (last - first);
    return first;
}

// @ 0x00f0b150
void RecVec::insert_n(Rec* pos, uint n, const Rec& val)
{
    if ((uint)(mpCap - mpEnd) < n) {
        uint size = (uint)(mpEnd - mpBegin);
        uint newCap = size * 2;
        if (size == 0)
            newCap = 1;
        if (newCap <= size + n)
            newCap = size + n;
        Rec* mem = 0;
        if (newCap)
            mem = (Rec*)operator_new(newCap * sizeof(Rec), "Simulator", 0, 0, kEastlFile, 0xd1);
        Rec* b = mpBegin;
        Rec* p1 = FUN_00f09db0(b, pos, mem);
        FUN_00f07bd0(b, pos, mem);
        FUN_00f09d70(p1, n, &val, p1);
        Rec* p2 = p1 + n;
        Rec* e = mpEnd;
        Rec* p3 = FUN_00f09db0(pos, e, p2);
        FUN_00f07bd0(pos, e, p2);
        if (mpBegin && ((int*)mpBegin)[-1])
            operator_delete__(mpBegin);
        mpBegin = mem;
        mpEnd = p3;
        mpCap = mem + newCap;
    } else if (n != 0) {
        Rec tmp;
        tmp.kind = val.kind;
        tmp.sub.CopyCtor(&val.sub);
        tmp.icon = val.icon;
        Rec* e = mpEnd;
        uint after = (uint)(e - pos);
        if (n < after) {
            Rec* mid = e - n;
            Rec* it = pos;
            FUN_00dfb8e0(&it, mid, e, e, pos);
            mpEnd += n;
            FUN_00f09880(pos, mid, e);
            FUN_00f09800(pos, pos + n, &tmp);
        } else {
            FUN_00f09d70(e, n - after, &tmp, pos);
            mpEnd += n - after;
            Rec* it = pos;
            FUN_00dfb8e0(&it, pos, e, mpEnd, pos);
            mpEnd += after;
            FUN_00f09800(pos, e, &tmp);
        }
        tmp.sub.Dtor();
    }
}

// @ 0x00f0b390
void RecVec::resize(uint n)
{
    uint size = (uint)(mpEnd - mpBegin);
    if (n > size) {
        Rec tmp;
        insert_n(mpEnd, n - (uint)(mpEnd - mpBegin), *tmp.Ctor());
        tmp.sub.Dtor();
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x00f0b420
Rec* GetListRec(int index)
{
    RecVec* list = 0;
    int active = ScenarioTutorials_GetActive();
    UIState* g = g_16c7d90;
    char* rec;
    Ctx* ctx = g->ctx;
    if (ctx == 0) {
        rec = 0;
    } else if ((int)((ctx->recEnd - ctx->recBegin) / 0x4e0) > active) {
        rec = ctx->recBegin + active * 0x4e0;
    } else {
        rec = 0;
    }
    switch (g->mode) {
    case 1: list = (RecVec*)(rec + 0x170); break;
    case 2: list = (RecVec*)(rec + 4); break;
    case 3: list = (RecVec*)(g->owner + 0x18); break;
    }
    if ((int)(list->mpEnd - list->mpBegin) <= index)
        list->resize(5);
    return list->mpBegin + index;
}

static Entry* FindEntry(IWin* w)
{
    UIState* g = g_16c7d90;
    for (int i = 0; i < 5; i++) {
        if (g->entries[i].win == w)
            return &g->entries[i];
    }
    return 0;
}

// @ 0x00f0b4d0
void ShowEntry(IWin* w)
{
    Entry* e = FindEntry(w);
    Rec* r = GetListRec(e->idx);
    e->savedA = r->kind;
    e->savedB = r->icon;
    w->SetFlags(-1);
    IWin* a = w->FindChild(0xcefa1100, 0);
    void* name = r->sub.Name();
    if (a) {
        IWin* b = a->QueryInterface(0xcf428691);
        if (b) {
            b->SetFontStyle(0xc0);
            b->SetText(name, 0);
        }
    }
    int k = r->kind;
    if (k >= 0 && k <= 4) {
        IWin* c = w->FindChild((uint)(k * 0x10 - 0x3105edf0), 0);
        if (c) {
            IWin* d = c->QueryInterface(0x8ed27e7a);
            if (d)
                d->SetState(4, 1);
        }
        for (int i = 0; i < 4; i++) {
            IWin* t = w->FindChild(0x7da65e0 + i, 1);
            if (i == r->kind)
                t->SetVisible(1, 1);
            else
                t->SetVisible(1, 0);
        }
    }
    IWin* icon = w->FindChild(0x742bdd0, 0);
    if (r->icon >= 0 && r->kind <= 4) {
        IWin* lay = ((Layout*)g_16c7d90->layout)->FindWindowByID(0x1742be59, 1);
        int ic = r->icon;
        void* img;
        if (lay) {
            IWin* ch = lay->FindChild(ic + 0x742cbe0, 1);
            img = SPUIHelpers_SetButtonState(ch, 0);
        } else {
            img = 0;
        }
        SPUIHelpers_SetImageIcon(icon, img, 0);
    }
    if (g_16c7d90->ctx->Check())
        icon->SetVisible(1, 1);
    else
        icon->SetVisible(1, 0);
}

// @ 0x00f0b690
void HideEntry(IWin* w)
{
    Entry* e = FindEntry(w);
    Rec* r = GetListRec(e->idx);
    e->savedA = r->kind;
    e->savedB = r->icon;
    w->SetFlags(0x77ffffff);
    w->SetVisible(1, 1);
    IWin* a = w->FindChild(0xcefa1100, 0);
    if (a) {
        IWin* b = a->QueryInterface(0xcf428691);
        if (b) {
            b->SetFontStyle(0xc0);
            b->SetText((const void*)0x13ec468, 0);
        }
    }
    uint id = 0xcefa1210;
    for (int i = 0; i < 4; i++) {
        IWin* t = w->FindChild(0x7da65e0 + i, 1);
        if (i == r->kind)
            t->SetVisible(1, 1);
        else
            t->SetVisible(1, 0);
        IWin* c = w->FindChild(id, 0);
        if (c) {
            IWin* d = c->QueryInterface(0x8ed27e7a);
            if (d)
                d->SetState(4, 1);
            d = c->QueryInterface(0x8ed27e7a);
            if (d)
                d->SetState(4, 0);
        }
        id += 0x10;
    }
    IWin* c = w->FindChild((uint)(r->kind * 0x10 - 0x3105edf0), 0);
    if (c) {
        IWin* d = c->QueryInterface(0x8ed27e7a);
        if (d)
            d->SetState(4, 1);
    }
    IWin* lay = ((Layout*)g_16c7d90->layout)->FindWindowByID(0x1742be59, 1);
    IWin* icon = w->FindChild(0x742bdd0, 0);
    int ic = r->icon;
    void* img;
    if (lay) {
        IWin* ch = lay->FindChild(ic + 0x742cbe0, 1);
        img = SPUIHelpers_SetButtonState(ch, 0);
    } else {
        img = 0;
    }
    SPUIHelpers_SetImageIcon(icon, img, 0);
    if (g_16c7d90->ctx->Check())
        icon->SetVisible(1, 1);
    else
        icon->SetVisible(1, 0);
}

// @ 0x00f0b8b0
void RefreshEntries()
{
    if (g_16c7d90 == 0)
        return;
    IWin* list = WindowManager()->GetWindowList(0);
    for (int off = 0; off < 0x50; off += 0x10) {
        Entry* e = (Entry*)((char*)g_16c7d90 + off + 0x10);
        Rec* r = GetListRec(e->idx);
        if (r->sub.Flags() > 0)
            goto show;
        {
            IWin* w = e->win;
            IWin* p = list;
            if (p) {
                do {
                    if (p == w)
                        goto show;
                    p = p->GetParent();
                } while (p);
            }
            HideEntry(e->win);
            continue;
        }
    show:
        ShowEntry(e->win);
    }
}

extern "C" void* __stdcall AddBoundingBox_67cad0(IWin* panel, int a, int b);   // 0x67cad0
struct BBox { void Renderer(); };                                      // 0x80d710

// @ 0x00f0b940
void SetToolMode(int mode)
{
    UIState* g;
    void* lay;
    uint id;
    switch (mode) {
    case 1: lay = g_16c7d90->layout; id = 0xcefa0000; break;
    case 2: lay = g_16c7d90->layout; id = 0xcefa0001; break;
    case 3: lay = g_16c7d90->layout; id = 0xcefa0002; break;
    default: goto after;
    }
    {
        IWin* w = ((Layout*)lay)->FindWindowByID(id, 1);
        if (w) {
            IWin* q = w->QueryInterface(0x8ed27e7a);
            if (q)
                q->SetState(4, 1);
        }
    }
after:
    g = g_16c7d90;
    g->mode = mode;
    IWin* cur = 0;
    int i = 0;
    Entry* e = &g->entries[0];
    do {
        i++;
        if (e->idx == 0) {
            cur = g->entries[i - 1].win;
            break;
        }
        e++;
    } while (i < 5);
    IWin* x = cur->FindChild(0xcefa1100, 1);
    WindowManager()->SetWindowList(0, x);
    RefreshEntries();
}

// @ 0x00f0ba10
void FinishTool()
{
    Tool* t = g_16c7d90->tool;
    void* bb = AddBoundingBox_67cad0(t->panel, 0, 1);
    ((BBox*)bb)->Renderer();
    if (g_16c7d90->tool->state == -1) {
        IWin* w = ((Layout*)g_16c7d90->layout)->FindWindowByID(0xceff0000, 1);
        IWin* x = w->FindChild(0xcefa1000, 0);
        float* area = x->GetArea();
        float f = (area[3] - area[1]) * 4.2f;
        g_16c7d90->tool->panel->SetPos(0.0f, f);
        Tool** pt = &g_16c7d90->tool;
        char c = g_16c7d90->ctx->Check();
        (*pt)->a = c ? 0 : 2;
        (*pt)->b = 0;
        (*pt)->state = 4;
        (*pt)->panel->SetFlags(-1);
        IWin* y = g_16c7d90->tool->panel->FindChild(0xcefa1100, 1);
        y->SetImage((const void*)0x13ec468);
        FUN_00f0aa80();
        WindowManager()->SetWindowList(0, w);
        RefreshEntries();
        g_16c7d90->tool = 0;
    } else {
        IWin* y = g_16c7d90->tool->panel->FindChild(0xcefa1100, 1);
        g_16c7d90->tool = 0;
        FUN_00f0aa80();
        WindowManager()->SetWindowList(0, y);
        g_16c7d90->tool = 0;
    }
}

// ---- 0xf0ac40: collect the avatar's tribe objects and link their referenced objects ----
struct Avatar;
struct NounMgr { Avatar* GetAvatar(); };                 // 0xb1fdb0
extern NounMgr* NounManager();                           // 0xb3d300
struct ObjMgr {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4();
    virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9();
    virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14();
    virtual void p15(); virtual void p16(); virtual void p17();
    virtual void Add(void* q);                           // 0x48
};
extern ObjMgr* FUN_00b3d240();

struct Obj : IWin { uint GameData(); };                  // GameData: 0xb18530 (thiscall)
struct Sys78 {
    char pad[0xb8];
    uint cookie;                                         // +0xb8
    char** GetRecs();                                    // 0xf191d0
    uint   Count();                                      // 0xf19bc0
    char   IsSkipped(uint i);                            // 0xf19c80
};
struct Mgr74 { char Validate(Obj* o, void* key, uint cookie, void* rec); };   // 0xf3e6d0
struct Global7aa4 { char pad[0x74]; Mgr74* mgr74; Sys78* sys78; };
extern Global7aa4* g_16c7aa4;
extern "C" Obj* FUN_00b68720(int kind);
extern uint* __fastcall FUN_006c0200(IWin* q);
extern "C" void FUN_00f09960(Obj* o, void* rec, void* tbl, int flag);
extern "C" Obj* FUN_00f08750(void* rec, int id, uint cookie, void* vec, void* avatarObj);
extern "C" void FUN_00cd0550(void* vec, void** pos, void** val);
extern "C" void FUN_00f09cf0(void** b, void** e, char flag);

struct HNode { uint key; HNode* next; };
struct UIntSet {
    HNode** buckets; uint nBuckets; uint nElem; float load; float growth; uint nextResize;
    bool contains(uint key) const {
        HNode* n = buckets[key % nBuckets];
        while (n) {
            if (key == n->key)
                return true;
            n = n->next;
        }
        return false;
    }
    void DoFreeNodes(HNode** b, uint n);                 // 0x6b6570
};
extern HNode* g_154df28[];

// 50-slot fixed vector of pointers
struct PtrVec {
    void** mpBegin; void** mpEnd; void** mpCap; uint pad; void* buf[50];
};
// 16-slot fixed vector of pointers
struct PtrVec16 {
    void** mpBegin; void** mpEnd; void** mpCap; void* buf[16];
};

// @ 0x00f0ac40
void CollectTribeObjects()
{
    UIntSet seen;
    seen.buckets = (HNode**)g_154df28;
    seen.nBuckets = 1;
    seen.nElem = 0;
    seen.load = 1.0f;
    seen.growth = 2.0f;
    seen.nextResize = 0;

    Avatar* av = NounManager()->GetAvatar();
    Obj* avObj = av ? (Obj*)((char*)av + 0xc0) : 0;
    if (avObj)
        avObj->AddRef();

    PtrVec held;
    held.mpBegin = held.buf;
    held.mpEnd = held.buf;
    held.mpCap = held.buf + 50;
    held.pad = 0;
    ObjMgr* mgr = FUN_00b3d240();
    mgr->Add(avObj->Query(30.0f, &held, 0, 0, 0));

    Sys78* sys = g_16c7aa4->sys78;
    uint cookie = sys->cookie;
    char** recs = sys->GetRecs();
    uint count = sys->Count();

    PtrVec16 sel;
    sel.mpBegin = sel.buf;
    sel.mpEnd = sel.buf;
    sel.mpCap = sel.buf + 16;
    void** selBuf = sel.buf;
    uint off = 0;
    for (uint i = 0; i < count; i++, off += 0x1ac) {
        char* rec = *recs + off;
        if (!sys->IsSkipped(i) && rec[0x34] != 0) {
            void* p = *recs + off;
            if (sel.mpEnd < sel.mpCap) {
                void** s = sel.mpEnd++;
                if (s)
                    *s = p;
            } else {
                FUN_00cd0550(&sel.mpBegin, sel.mpEnd, &p);
            }
        }
    }
    FUN_00f09cf0(sel.mpBegin, sel.mpEnd, 0);
    uint nSel = (uint)(sel.mpEnd - sel.mpBegin);

    for (uint j = 0; j < nSel; j++) {
        char* rec = (char*)sel.mpBegin[j];
        int ids[2];
        ids[0] = *(int*)(rec + 0x28);
        ids[1] = *(int*)(rec + 0x2c);
        for (uint k = 0; k < 2; k++) {
            int id = ids[k];
            if (id == -1)
                continue;
            Mgr74* m74 = g_16c7aa4->mgr74;
            Obj* o = FUN_00b68720(4);
            if (o != 0) {
                uint* q = FUN_006c0200(o->QueryInterface(0x17f243b));
                if (q && *q == (uint)id && o->GameData() != 0 &&
                    m74->Validate(o, rec + 0x24, cookie, rec)) {
                    // keep o
                } else {
                    o = 0;
                }
            }
            if (o) {
                uint key = o->GameData();
                if (!seen.contains(key))
                    FUN_00f09960(o, rec, &seen, 1);
            }
            Obj* r = FUN_00f08750(rec, ids[k], cookie, &held, avObj);
            if (r && r != o) {
                uint key = r->GameData();
                if (!seen.contains(key))
                    FUN_00f09960(r, rec, &seen, 0);
            }
        }
    }

    if (sel.mpBegin && sel.mpBegin != selBuf)
        operator_delete__(sel.mpBegin);
    for (void** p = held.mpBegin; p < held.mpEnd; ++p) {
        if (*p)
            ((Obj*)*p)->Release();
    }
    if (held.mpBegin && ((int*)held.mpBegin)[-1])
        operator_delete__(held.mpBegin);
    avObj->Release();
    seen.DoFreeNodes(seen.buckets, seen.nBuckets);
    seen.nextResize = 0;
    if (seen.nBuckets > 1)
        operator_delete__(seen.buckets);
}
