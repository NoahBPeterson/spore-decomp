// Slice s0064acd0 -- cSPUIAssetBrowser launch / ban / message handling.
// Module flags: /O2 /MD /Gy /TP.
#include "types.h"

struct Key { uint32_t a, b, c; };
struct Key4 { uint32_t a, b, c, d; };

// Refcounted object: slot 0 unknown, slot 1 AddRef, slot 2 Release.
struct IRef  { virtual int AddRef(); virtual int Release(); };
struct IRef2 { virtual void s0(); virtual int AddRef(); virtual int Release(); };

void* operator new(unsigned int n, const char* name, int a, int b, int c, int d);
void __cdecl operator delete(void* p);

#define S(n) virtual void s##n();

// ---- singletons -------------------------------------------------------------
struct IMessageServer {
    S(0) S(1) S(2) S(3) S(4)
    virtual void Post(uint32_t id, void* data, int flag);                 // slot 5 (+0x14)
    virtual void Post4(uint32_t id, void* data, int a, int b);            // slot 6 (+0x18)
};
IMessageServer* __cdecl GetMessageServer();                               // 0x67dcc0

struct IObjectTemplateDB {
    S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
    S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
    S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29)
    virtual void SetBanned(Key* k, bool banned);                          // slot 30 (+0x78)
};
IObjectTemplateDB* __cdecl GetObjectTemplateDB();                         // 0x67cb40

struct IApp {
    S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12) S(13)
    virtual int GetMode();                                                // slot 14 (+0x38)
};
IApp* __cdecl GetApp();                                                   // 0x67dd10

int __cdecl FUN_00552300(void* key);

// ---- ban list ---------------------------------------------------------------
struct IBanObj {
    S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12) S(13) S(14) S(15)
    virtual Key* GetKey();                                                // slot 16 (+0x40)
    S(17) S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27)
    virtual bool IsOfficial();                                            // slot 28 (+0x70)
};
struct BanEntry {            // 0x14 bytes
    Key key;
    uint32_t pad;
    IBanObj* obj;            // +0x10
};
// Message payload built by FUN_00644a80 (16 bytes, refcounted pointer at +0xc).
struct BanMsg {
    uint32_t d[3];
    IRef* p;
    BanMsg(void* owner, Key* k, int flag);                                // 0x644a80
};
// Message payload built by FUN_00666af0/00666a60 (refcounted pointer at +0x10, two flag bytes).
struct FeedMsg {
    uint32_t d[4];
    IRef* p;                 // +0x10
    uint8_t flagA;           // +0x14
    uint8_t flagB;           // +0x15
    void Init(uint32_t id);                                               // 0x666af0
    void InitFromAsset(void* asset);                                      // 0x666a60
};

// ---- card (HandleMessage) -----------------------------------------------------
struct CardBase {
    S(0)
    virtual void SetKey(Key* k);                                          // slot 1
    S(2) S(3) S(4) S(5) S(6) S(7) S(8)
    virtual uint32_t GetTypeID();                                         // slot 9 (+0x24)
    S(10)
    virtual bool IsAssetCard();                                           // slot 11 (+0x2c)
    uint32_t pad[3];
};
struct Card : CardBase, IRef {};          // IRef subobject at +0x10
struct CardRef {
    Card* p;
    void Assign(Card* c);                                                 // 0x6428c0
};
typedef Card* (__cdecl *CardFactory)();
typedef Card* (__cdecl *CardWrapFn)(Card*);
struct ConfigTable {                                                      // `this` is the config id itself
    CardFactory GetFactory(uint32_t typeId);                              // 0x642c10
    CardWrapFn  GetWrapper(uint32_t kind);                                // 0x642c40
};
struct TimelineSporepediaCardData : Card {                                // 0x78 bytes (operator new size)
    TimelineSporepediaCardData();                                         // 0x642100
    uint32_t data[(0x78 - 0x14) / 4];
};
struct AssetHolder {                                                      // 8 bytes at stack
    uint32_t a, b;
    AssetHolder() { a = 0; b = 0; }
    void Set(CardRef* c);                                                 // 0x642930
    ~AssetHolder();                                                       // 0x644fc0
};
struct VecIter { void Finish(); };                                        // 0x645db0

// ---- feed list / property list ------------------------------------------------
struct IProp { uint8_t pad[0x12]; uint16_t type; bool* GetBool(); };      // 0x41e920
struct IPropList {
    S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8)
    virtual bool GetProperty(uint32_t id, IProp** out);                   // slot 9 (+0x24)
};
struct FeedCategory {
    void Expand(int b);                                                    // 0x664480
};
struct FeedList {
    void SetHidden(bool b);                                               // 0x662a90
    FeedCategory* FindCategory(uint32_t id);                              // 0x662a40
    void FUN_00662ad0();
};
bool __cdecl GetPropertyAsKeyInstance(IPropList* props, uint32_t id, uint32_t* out);   // 0x6a12a0
void __cdecl GetPropertyKeyArray(IPropList* props, uint32_t id, int* count, Key** arr); // 0x6a0ae0

// ---- asset grid ---------------------------------------------------------------
struct GridInner {
    void FUN_00661380(void* outVec);                                      // 0x661380
    void FUN_00662750(uint32_t a, uint32_t b, bool c);                    // 0x662750
};
struct AssetGrid {
    uint8_t pad0[0xe0];
    GridInner* inner;                                                     // +0xe0
    uint8_t pad1[0x178 - 0xe4];
    uint32_t id178;                                                       // +0x178
    uint8_t pad2[0x1bb - 0x17c];
    uint8_t b1bb;                                                         // +0x1bb
    void FUN_0064f310();
    void FilterEntries();                                                 // 0x64e5b0
    bool Layout(Key* key, uint8_t b30, int one, uint32_t f38);            // 0x655840
};
bool __cdecl SetAssetData(uint32_t id, int one);                          // 0x4bbe20
struct AssetList { Key* begin; Key* end; Key* cap; };
struct FeedItem {
    uint8_t pad[0x178];
    uint32_t id178;
    void GetAssetList(AssetList* out);                                    // 0x668d90
};

// ---- editor launch data -------------------------------------------------------
struct WString {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity;
    void assign(const wchar_t* b, const wchar_t* e);                      // 0x423650
    WString& operator=(const WString& o);                                 // 0x57cb60
    void DeallocateSelf();                                                // 0x933960
};
extern wchar_t gEmptyWString[2];                                          // 0x1667bac
struct LaunchData;
struct LaunchDataRef {
    LaunchData* p;
    void Assign(LaunchData* d);                                           // 0x61df40 / 0x5766e0
    void CopyFrom(const void* other);                                     // 0x5766e0
};
struct SubRef { IRef* p; void CopyFrom(const void* other); };             // 0xac9480
struct LaunchData : IRef2 {
    uint32_t f04, f08;
    uint32_t f0c;                                                         // +0x0c
    Key k10;                                                              // +0x10
    uint32_t f1c;
    uint32_t pad20;
    Key4 k24;                                                             // +0x24
    uint8_t b34, b35, b36, b37, b38, b39, b3a, b3b, b3c, b3d, b3e, b3f;
    uint32_t pad40[4];
    WString str50;                                                        // +0x50
    uint32_t pad5c[2];
    uint8_t b64, b65, b66, b67;
    uint32_t pad68;
    uint8_t b6c, b6d, b6e, b6f;
    uint32_t pad70[5];
    uint32_t f84, f88, f8c, f90;
    SubRef f94;
    LaunchDataRef f98;
    LaunchData();                                                         // 0x5a9080
};
void __cdecl EditorLaunch(LaunchData* d);                                 // 0x5a9200
void __cdecl EditorLaunchEx(uint32_t id, Key* k, uint32_t a, uint32_t b, Key4 v, bool flag); // 0x5a94d0

// ---- hashtable stand-in (this+0x15c) -------------------------------------------
struct IHandlerObj {
    S(0) S(1)
    virtual bool TryHandle(Key* k, int one);                              // slot 2 (+8)
};
struct HIter { void* node; HIter() {} HIter(const HIter& o) { node = o.node; } };
struct HMap {
    uint32_t pad;
    void** buckets;                                                       // +0x160 (this+4)
    uint32_t nBuckets;                                                    // +0x164
    HIter find(const uint32_t& key) const;                                // 0x645ed0
    IHandlerObj*& operator[](const uint32_t& key);                        // 0x646f40
};

// ---- window-ish objects ---------------------------------------------------------
struct IWin80 {
    S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12) S(13) S(14) S(15)
    S(16) S(17) S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(30)
    virtual void Fade(int a, int b);                                      // slot 31 (+0x7c)
};
struct IWin5c {
    S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12) S(13) S(14) S(15)
    S(16) S(17) S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(30)
    S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39) S(40) S(41) S(42) S(43) S(44) S(45)
    S(46) S(47) S(48) S(49) S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57)
    virtual void SetFocusChild(void* w);                                  // slot 58 (+0xe8)
};

struct IPendingWin {
    S(0)
    virtual int Release();
};

// ---- the browser ------------------------------------------------------------------
struct Msg {                       // message passed to HandleMessage
    uint32_t pad0[4];
    uint32_t f10;                  // +0x10
    uint32_t f14;
    uint8_t  b18;
    uint8_t  pad19[3];
    uint32_t f1c, f20;
    Key      key;                  // +0x24
    uint8_t  b30, b31, b32, pad33;
    uint32_t f34, f38;
};

struct cSPUIAssetBrowser {
    uint32_t vptr;                 // +0x00
    uint32_t pad04[6];             // +0x04
    uint8_t  b1c, b1d, b1e, b1f;   // +0x1c
    uint32_t f20;                  // +0x20
    uint16_t pad24;                // +0x24
    uint8_t  b26, b27;             // +0x26
    uint16_t pad28;                // +0x28
    uint8_t  b2a, b2b;             // +0x2a
    uint32_t pad2c[12];            // +0x2c
    IWin5c*  p5c;                  // +0x5c
    uint32_t pad60;
    IRef*    p64;                  // +0x64
    uint32_t pad68[6];
    IWin80*  p80;                  // +0x80
    uint32_t pad84[13];
    uint32_t cfgId;                // +0xb8
    AssetGrid* grid;               // +0xbc
    FeedList* feedList;            // +0xc0
    uint32_t padc4[2];
    BanEntry* banBegin;            // +0xcc
    BanEntry* banEnd;              // +0xd0
    uint32_t padd4[34];            // +0xd4
    HMap     handlers;             // +0x15c
    uint32_t pad168[11];
    IPropList* props;              // +0x194
    uint32_t pad198;
    uint32_t mField19C;            // +0x19c
    uint32_t f1a0, f1a4, f1a8;     // +0x1a0
    uint8_t  b1ac, b1ad, b1ae, b1af;
    LaunchDataRef f1b0;            // +0x1b0
    LaunchData* src1b4;            // +0x1b4
    uint32_t f1b8;                 // +0x1b8
    uint32_t f1bc;                 // +0x1bc
    uint32_t f1c0;                 // +0x1c0
    uint8_t  b1c4, b1c5, b1c6, b1c7;
    uint32_t pad1c8[7];
    uint32_t f1e4, f1e8;           // +0x1e4
    uint8_t  b1ec, b1ed, b1ee, b1ef;
    uint32_t pad1f0[14];
    IRef*    p228;                 // +0x228
    uint32_t f22c;                 // +0x22c
    uint32_t pad230;
    uint8_t  b234, b235, b236, b237;
    uint32_t f238;                 // +0x238
    uint8_t  b23c, b23d, b23e, b23f;
    uint32_t f240, f244, f248;     // +0x240
    uint8_t  b24c;                 // +0x24c

    void ShowSporeGuide();
    void BanItem();
    void HandleMessage(Msg* m);
    void LaunchEditorEnd();
    void Update();                                                        // 0x64ab20
    void SetLargeCardVisibililty(int a, int b, int c);                    // 0x6478c0
    void FilterGridEntries(int a);                                        // 0x648d90
    void SetVisibility(int a, int b, int c);                              // 0x64a400
    void FUN_00644e20(int a);                                             // 0x644e20
    void FUN_0064c280();                                                  // 0x64c280
    IBanObj* FUN_00645300();                                              // 0x645300
};
struct ABSingleton {
    uint32_t FUN_00645cc0();
    uint32_t FUN_00645bf0();
};
ABSingleton* __cdecl GetAssetBrowser();                                   // 0x401030
struct BanVector {
    void ClearAssetViews();                                               // 0x648aa0
    VecIter* Insert(Key* key, AssetHolder* h);                            // 0x648ce0
};
void __cdecl LaunchSporeGuide(uint32_t id);                               // 0x0064aba0
void __cdecl GetEditorSettings(bool flag, LaunchData** out);              // 0x6447c0
extern uint32_t g15da784, g15da788, g15da78c, g15da790;
struct GameRoot { uint8_t pad[0x3c]; struct { uint8_t pad[0x118]; uint32_t f118; }* sub; };
extern GameRoot* g15fd918;

// @ 0x0064b6a0
void cSPUIAssetBrowser::ShowSporeGuide() {
    LaunchSporeGuide(mField19C);
}

// @ 0x0064b4b0
void cSPUIAssetBrowser::BanItem() {
    if (banBegin == banEnd)
        return;
    IMessageServer* ms = GetMessageServer();
    uint32_t off = 0;
    for (unsigned i = 0; i < (unsigned)(banEnd - banBegin); i++, off += 0x14) {
        BanEntry* e = (BanEntry*)((char*)banBegin + off);
        IBanObj* obj = e->obj;
        if (obj) {
            Key itemKey = e->key;
            Key* kp = obj->GetKey();
            Key k2 = *kp;
            bool flag = false;
            if ((FUN_00552300(&k2) == 1 && obj->IsOfficial()) || f22c == 0)
                flag = true;
            GetObjectTemplateDB()->SetBanned(&k2, flag);
            if (b2a && grid) {
                BanMsg msg(p228, &itemKey, 0);
                ms->Post(0x3b60b3ad, &msg, 0);
                if (msg.p)
                    msg.p->Release();
            }
        }
    }
    FilterGridEntries(0);
    if (b2a) {
        ms->Post(0x53dd093, 0, 0);
        if (grid)
            grid->FilterEntries();
    } else {
        SetLargeCardVisibililty(0, 0, 0);
        Update();
    }
    bool changed = false;
    GetMessageServer()->Post(0x12a93f05, &changed, 0);
    if (changed) {
        Update();
        ms->Post(0x4715068, 0, 0);
    }
}

// @ 0x0064b6b0
void cSPUIAssetBrowser::HandleMessage(Msg* m) {
    Key* key = &m->key;
    bool hasKey = key->a != 0;
    if (!b2a) {
        bool handled = false;
        if (hasKey && m->b30) {
            Key4 k4;
            k4.a = key->a; k4.b = key->b; k4.c = key->c;
            k4.d = 0;
            CardRef card;
            card.p = 0;
            CardFactory fn = 0;
            if (cfgId != 0)
                fn = ((ConfigTable*)cfgId)->GetFactory(m->key.b);
            Card* made;
            if (fn)
                made = fn();
            else
                made = new("Sporepedia", 0, 0, 0, 0) TimelineSporepediaCardData();
            card.Assign(made);
            Card* c = card.p;
            c->SetKey((Key*)&k4);
            CardWrapFn w = ((ConfigTable*)cfgId)->GetWrapper(c->GetTypeID());
            if (w) {
                card.Assign(w(c));
                c = card.p;
            }
            if (c->IsAssetCard()) {
                AssetHolder h;
                h.Set(&card);
                BanVector* v = (BanVector*)&banBegin;
                v->ClearAssetViews();
                v->Insert(key, &h)->Finish();
                SetLargeCardVisibililty(1, 0, 0);
                handled = true;
            }
            ((IRef*)c)->Release();
        }
        if (!handled)
            Update();
        IRef* t = p228;
        if (t) {
            p228 = 0;
            t->Release();
        }
        return;
    }

    if (f1a0 == 0 && f1a4 == 0) {
        f1a0 = m->f1c;
        uint32_t t20 = m->f20;
        f1a4 = t20;
        if (f1a0 == 0 && t20 == 0)
            f1a8 = 0;
        else
            f1a8 = m->f14;
    }
    b1ac = m->b18;
    f20 = m->f34;
    bool bl = false;
    {
        IProp* out;
        if (props && props->GetProperty(0xb4d1731e, &out) && out->type == 1)
            bl = *out->GetBool();
    }
    if (grid)
        grid->b1bb = bl;
    bool show;
    if (m->b32 && !b26 && !b27 && p228)
        show = false;
    else
        show = true;
    bool r12;
    if (!hasKey) {
        r12 = false;
        if (show)
            r12 = true;
    } else {
        r12 = true;
    }
    b1ed = 0;
    if (grid) {
        if (f1e4 != 0 && f1e8 != 0) {
            GridInner* e0 = grid->inner;
            if (e0) {
                AssetList t = { 0, 0, 0 };
                e0->FUN_00661380(&t);
                if (t.begin)
                    operator delete(t.begin);
                e0->FUN_00662750(f1e4, f1e8, !show);
            }
            if (show)
                grid->FUN_0064f310();
        } else if (show) {
            b1ed = 1;
            grid->FUN_0064f310();
        }
    }
    if (r12) {
        bool hide = true;
        IProp* o2;
        if (props && props->GetProperty(0x5aeeaa2, &o2) && o2->type == 1)
            hide = *o2->GetBool();
        feedList->SetHidden(hide);
        int count = 0;
        Key* arr = 0;
        GetPropertyKeyArray(props, 0x59c3490, &count, &arr);
        for (int i = 0; i < count; i++) {
            FeedCategory* c = feedList->FindCategory(arr[i].a);
            if (c)
                c->Expand(1);
        }
    }
    FeedMsg fm;
    bool post = true;
    if (show) {
        uint32_t v = m->f10;
        if (v) {
            fm.Init(v);
            fm.flagA = 1;
            fm.flagB = 1;
        } else if (GetPropertyAsKeyInstance(props, 0x3449565e, &v)) {
            fm.Init(v);
            fm.flagB = 1;
        } else {
            post = false;
        }
    } else if (p228) {
        fm.InitFromAsset(p228);
    } else {
        post = false;
    }
    if (post) {
        GetMessageServer()->Post(0xb3d53f95, &fm, 0);
        if (fm.p)
            fm.p->Release();
    }
    if (hasKey && grid) {
        if (!grid->Layout(key, m->b30, 1, m->f38)) {
            if (SetAssetData(m->key.b, 1)) {
                FeedMsg fm2;
                fm2.Init(0xe2415c7d);
                GetMessageServer()->Post(0xb3d53f95, &fm2, 0);
                grid->Layout(key, m->b30, 1, m->f38);
                if (fm2.p)
                    fm2.p->Release();
            }
        }
    }
    FeedItem* it = (FeedItem*)p228;
    if (it && it->id178 == 0x11f44f6b) {
        AssetList l = { 0, 0, 0 };
        it->GetAssetList(&l);
        if (l.begin == l.end) {
            FeedMsg fm3;
            fm3.Init(0xe2415c7d);
            GetMessageServer()->Post(0xb3d53f95, &fm3, 0);
            if (fm3.p)
                fm3.p->Release();
        }
        if (l.begin && ((uint32_t*)l.begin)[-1])
            operator delete(l.begin);
    }
    if (m->b31)
        feedList->FUN_00662ad0();
}

static inline void FreeStr(WString& s) {
    if (((uint32_t)((char*)s.mpCapacity - (char*)s.mpBegin) & ~1u) > 2 && s.mpBegin)
        operator delete(s.mpBegin);
}

// @ 0x0064acd0
void cSPUIAssetBrowser::LaunchEditorEnd() {
    if (b24c) {
        b24c = 0;
        b234 = 0;
        if (p80 && p5c) {
            p80->Fade(1, b1c);
            p80->Fade(0x40, 0);
            if (p64)
                p5c->SetFocusChild(p64);
            b1f = 0;
        }
        FUN_0064c280();
        return;
    }
    Key k = { 0, 0, 0 };
    if (banBegin != banEnd && (banEnd - banBegin) == 1 && banBegin->obj != 0) {
        IBanObj* o = FUN_00645300();
        Key* kp = o->GetKey();
        k = *kp;
    }
    void* endNode = handlers.buckets[handlers.nBuckets];
    if (handlers.find(k.b).node != endNode) {
        IHandlerObj* h = handlers[k.b];
        if (h->TryHandle(&k, 1)) {
            SetVisibility(0, 0, 0);
            b234 = 0;
            FUN_00644e20(0);
            return;
        }
    }
    bool f15 = false;
    if (b1c4 && f1b8 != 0x2ccd1d2)
        f15 = true;
    WString tmpStr;
    tmpStr.mpBegin = gEmptyWString;
    tmpStr.mpEnd = gEmptyWString;
    tmpStr.mpCapacity = gEmptyWString + 1;
    Key4 key4;
    uint8_t t18, t10, t12, t11, t14, t13, t16;
    LaunchData* src = src1b4;
    if (src) {
        key4 = src->k24;
        t18 = src->b34; t10 = src->b36; t12 = src->b38; t11 = src->b37;
        t14 = src->b3a; t13 = src->b3d; t16 = src->b6f;
        if (&src->str50 != &tmpStr)
            tmpStr.assign(src->str50.mpBegin, src->str50.mpEnd);
    } else {
        LaunchData* out = 0;
        GetEditorSettings(b1c4, &out);
        key4 = out->k24;
        t18 = out->b34; t10 = out->b36; t12 = out->b38; t11 = out->b37;
        t14 = out->b3a; t13 = out->b3d; t16 = out->b6f;
        out->Release();
    }
    LaunchDataRef cell;
    cell.p = 0;
    LaunchData* esi = 0;
    bool b17 = false;
    uint32_t ebx;
    if (b235) {
        ebx = GetAssetBrowser()->FUN_00645cc0();
        b17 = true;
        if (f1b0.p) {
            cell.CopyFrom(&f1b0);
            esi = cell.p;
        }
        b235 = 0;
        k.a = 0; k.b = 0; k.c = 0;
        if (esi)
            goto finish;
        goto std_launch;
    }
    if (b23c) {
        ebx = f238;
        b23c = 0;
        goto std_launch;
    }
    ebx = f1c0;
    if (ebx == 0) {
        ebx = GetAssetBrowser()->FUN_00645cc0();
        if (ebx == 0)
            ebx = (uint32_t)-1;
    }
    if (g15fd918->sub->f118 == 0 || f1b8 != 0x51b22b0)
        goto std_launch;
    {
        // "Casual" editor launch
        uint32_t c0 = g15da784, c1 = g15da788, c2 = g15da78c, c3 = g15da790;
        LaunchData* p = new("Casual", 0, 0, 0, 0) LaunchData();
        cell.Assign(p);
        LaunchData* e = cell.p;
        e->f1c = 0x418a508;
        e->k10 = k;
        e->f0c = 0x5bf8f774;
        e->f90 = 0x517560a;
        if (e->f94.p) {
            IRef* t = e->f94.p;
            e->f94.p = 0;
            t->Release();
        }
        e->k24.a = c0; e->k24.b = c1; e->k24.c = c2; e->k24.d = c3;
        e->b34 = t18; e->b36 = t10; e->b37 = t11; e->b38 = t12; e->b3d = t13;
        e->b3c = 0;
        e->b64 = 1;
        e->b6d = 0;
        e->b6e = 0;
        Key4 kv;
        kv.a = c0; kv.b = c1; kv.c = c2; kv.d = c3;
        EditorLaunchEx(0x5bf8f774, &k, 0x517560a, f1bc, kv, t18 != 0);
        GetMessageServer()->Post4(0xb03bc30c, e, 0, 0);
        if (GetApp()->GetMode() == 0xdbdba1)
            GetMessageServer()->Post4(0x51cc0b8, 0, 0, 0);
        SetVisibility(0, 0, 0);
        b234 = 0;
        FUN_00644e20(0);
        e->Release();
        tmpStr.DeallocateSelf();
        return;
    }
std_launch:
    {
        LaunchData* p = new("Editor", 0, 0, 0, 0) LaunchData();
        if (p) {
            p->AddRef();
            esi = p;
        }
        esi->k10 = k;
        esi->f0c = ebx;
        esi->f90 = 0x13c5a95e;
        esi->f94.CopyFrom(&f1bc);
        esi->k24 = key4;
        esi->b34 = t18; esi->b36 = t10; esi->b37 = t11; esi->b38 = t12;
        esi->b3a = t14; esi->b3d = t13;
        esi->b6d = b1c4; esi->b6e = f15; esi->b6f = t16;
        esi->b64 = 1;
        if (&tmpStr != &esi->str50)
            esi->str50.assign(tmpStr.mpBegin, tmpStr.mpEnd);
        if (b17 && GetAssetBrowser()->FUN_00645bf0()) {
            LaunchData* e2 = new("Editor", 0, 0, 0, 0) LaunchData();
            LaunchDataRef cell2;
            cell2.p = e2;
            if (e2)
                e2->AddRef();
            e2->f0c = GetAssetBrowser()->FUN_00645bf0();
            e2->f90 = 0x13c5a95e;
            e2->f94.CopyFrom(&f1bc);
            e2->k24 = key4;
            e2->b34 = t18; e2->b36 = t10; e2->b37 = t11; e2->b38 = t12;
            e2->b3a = t14; e2->b3d = t13;
            e2->b6d = b1c4; e2->b6e = f15; e2->b6f = t16;
            e2->b64 = 1;
            e2->b3c = 1;
            e2->b6c = 1;
            e2->str50 = tmpStr;
            esi->f98.CopyFrom(&cell2);
            esi->b34 = 0;
            e2->Release();
        }
    }
finish:
    if (f240) {
        LaunchData* c = esi->f98.p;
        if (c) {
            c->f84 = f240; c->f88 = f244; c->f8c = f248;
        } else {
            esi->f84 = f240; esi->f88 = f244; esi->f8c = f248;
        }
    }
    if (esi->f1c == 0x1654c10)
        esi->b39 = 0;
    EditorLaunch(esi);
    SetVisibility(0, 0, 0);
    b234 = 0;
    if (p80 && p5c) {
        p80->Fade(1, b1c);
        p80->Fade(0x40, 0);
        if (p64)
            p5c->SetFocusChild(p64);
        b1f = 0;
    }
    esi->Release();
    FreeStr(tmpStr);
}
