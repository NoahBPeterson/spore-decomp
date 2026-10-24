// Slice s01076540 -- SP::cSPUISpaceTrading::DoMessage (0x01076b80), the IWinProc message handler of the
// space-trading UI. this = IWinProc subobject (retail layout, offsets from the asm).
// Flags: /O2 /MD /Gy /TP (UI module: x87 floats, no /EHsc)
#include "types.h"

#define PAD(n) virtual void pad##n()

struct IWindow;
struct Rect { float left, top, right, bottom; };

class cSPUILayout {
public:
    virtual void Pad0();                                     // +0x00
    virtual void AddRef();                                   // +0x04
    virtual void Release();                                  // +0x08
    virtual void Pad3(); virtual void Pad4(); virtual void Pad5(); virtual void Pad6();
    virtual void Pad7(); virtual void Pad8(); virtual void Pad9();
    void Shutdown(uint32_t flags);                           // 0x00811ad0 (ret 4)
    IWindow* FindWindowByID(uint32_t id, int recursive);     // 0x008105b0 (ret 8)
    cSPUILayout* Ctor();                                     // 0x00810000
    bool Init(const wchar_t* name, uint32_t a, uint32_t b, uint32_t c);  // 0x00812160 (ret 0x10)
};

// EA::UTFWin::IWindow (vtable slots per ModAPI)
struct ITextWindow {
    PAD(0); PAD(1); PAD(2); PAD(3); PAD(4); PAD(5); PAD(6); PAD(7); PAD(8); PAD(9);
    virtual void SetColor(uint32_t color);                    // +0x28
};

struct IWindow {
    PAD(0); PAD(1); PAD(2);
    virtual ITextWindow* Slot0C(uint32_t key);                // +0x0c
    virtual IWindow* GetParent();                             // +0x10
    PAD(5); PAD(6);
    virtual uint32_t GetControlID();                          // +0x1c
    PAD(8); PAD(9);
    virtual uint32_t GetFlags();                              // +0x28
    PAD(11); PAD(12); PAD(13);
    virtual Rect* GetArea();                                  // +0x38
    PAD(15); PAD(16); PAD(17); PAD(18); PAD(19);
    virtual void Slot50(uint32_t id);                         // +0x50
    PAD(21); PAD(22);
    virtual void Slot5C(uint32_t value);                      // +0x5c
    PAD(24);
    virtual void SetPosition(float x, float y);               // +0x64
    PAD(26); PAD(27); PAD(28); PAD(29); PAD(30);
    virtual void SetFlag(uint32_t flag, int value);           // +0x7c
    virtual void Slot80(void* buffer);                        // +0x80
    PAD(33); PAD(34); PAD(35); PAD(36); PAD(37); PAD(38); PAD(39); PAD(40); PAD(41);
    PAD(42); PAD(43); PAD(44); PAD(45); PAD(46); PAD(47); PAD(48); PAD(49); PAD(50); PAD(51);
    PAD(52); PAD(53);
    virtual void SlotD8(IWindow* child);                      // +0xd8
    virtual void SlotDC(IWindow* child);                      // +0xdc
    PAD(56); PAD(57); PAD(58); PAD(59);
    virtual IWindow* FindWindowByID(uint32_t id, int recursive);   // +0xf0
    PAD(61); PAD(62); PAD(63); PAD(64);
    virtual void Slot104(void* p);                            // +0x104
};

struct Message { IWindow* source; uint32_t pad4; uint32_t type; };

// EA::Audio system (slots by offset)
struct AudioSystem {
    PAD(0); PAD(1); PAD(2); PAD(3); PAD(4); PAD(5); PAD(6); PAD(7);
    virtual uint32_t Slot20();                                // +0x20
    PAD(9); PAD(10); PAD(11); PAD(12); PAD(13);
    virtual void Slot38(uint32_t a);                          // +0x38
    virtual void Slot3C(uint32_t a, float b);                 // +0x3c
    virtual void Slot40(uint32_t a, uint32_t b);              // +0x40
    PAD(17); PAD(18); PAD(19); PAD(20); PAD(21);
    virtual void Slot58();                                    // +0x58
};
AudioSystem* GetSystemAT();                                   // 0x00a206f0 EA::Audio::GetSystemAT

struct TradeItem {
    PAD(0); PAD(1); PAD(2); PAD(3); PAD(4); PAD(5); PAD(6); PAD(7);
    PAD(8); PAD(9); PAD(10); PAD(11);
    virtual const char* Slot30(void* buffer);                 // +0x30
    char pad04[0x10];
    uint32_t f14;                                             // +0x14
    char pad18[0x18];
    uint32_t f30;                                             // +0x30
    int Get18();                                              // 0x006c0200
};

struct TradeItemInfo { char pad[0x10]; uint32_t f10; };

struct cSPSpaceTrading {
    TradeItem* GetUserItem(uint32_t idx);                     // 0x01039ab0
    TradeItem* GetNPCItem(uint32_t idx);                      // 0x01039ad0
    void PerformTrade();                                      // 0x0103eff0
    void CreateNPCInventory(uint32_t planet, uint32_t arg);   // 0x0103e8e0
    uint32_t Fn103b950(uint32_t a, uint32_t isUser, TradeItem* item, uint32_t d);   // 0x0103b950
    void Fn103dbd0(uint32_t a);                               // 0x0103dbd0
    TradeItemInfo* Fn1039c00(TradeItem* item);                // 0x01039c00
    uint32_t Fn1039b70(TradeItem* item);                      // 0x01039b70
    void* Fn103a540(TradeItem* item);                         // 0x0103a540
};
cSPSpaceTrading* GetSpaceTrading();                           // 0x00b3d3d0

struct ObjB490 {
    void Fn(uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00ae7e10 (ret 0x10)
};
ObjB490* GetB490();                                           // 0x00b3d490

struct Empire { char pad[0x58]; uint32_t f58; };
struct StarManager {
    Empire* GetEmpireByID(uint32_t id);   // 0x00ba9370
};
StarManager* GetStarManager();                                // 0x00b3d2a0
struct NounManager {
    uint32_t GetAvatar();   // 0x00b1fdb0
};
NounManager* IsArchived();                                    // 0x01021240 (SP::cSPMission::IsArchived)
struct Planet { char pad[0x13c]; uint32_t f13c; };
Planet* GetActivePlanet();                                    // 0x01021260

struct ObjAED4D0 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void Fn28(uint32_t key, uint32_t id, uint32_t* o1, uint32_t* o2);   // +0x28
};
ObjAED4D0* GetAED4D0();                                       // 0x00aed4d0

uint32_t GetRecorderState();                                  // 0x00435e90
void KillSetiEffects(uint32_t key, uint32_t state);           // 0x00435ed0 SP::cSPUISpace::KillSetiEffects
void SetGlobalProperty(uint32_t id, float value);             // 0x005ca880

class cSPUIAnimator { public: void Update(); };                      // 0x007f63b0
struct Sub50 {
    void Fn36540();                                           // 0x00e36540
    void Fn36620();                                           // 0x00e36620
};

struct cSPUISpaceTrading {
    char pad00[0x14];
    void* mClient14;                // +0x14
    IWindow* mWindow18;             // +0x18
    char pad1c[4];
    void* mClient20;                // +0x20
    IWindow* mWindow24;             // +0x24
    cSPUILayout** mItemsBegin;      // +0x28
    cSPUILayout** mItemsEnd;        // +0x2c
    cSPUILayout** mItemsCap;        // +0x30
    char pad34[8];
    cSPUIAnimator** mAnimBegin;     // +0x3c
    cSPUIAnimator** mAnimEnd;       // +0x40
    char pad1[0x50 - 0x44];
    Sub50 mSub50;                   // +0x50
    char pad2[0x104 - 0x50 - sizeof(Sub50)];
    cSPUILayout* mLayout;           // +0x104
    char pad3[0x11d - 0x108];
    bool mTrading;                  // +0x11d
    char pad4[2];
    int mActiveItemIndex;           // +0x120
    bool mIsUserItem;               // +0x124

    bool DoMessage(IWindow* win, Message* msg);               // 0x01076b80
    TradeItem* GetActiveItem();                               // 0x01075450
    void Fn10759c0(IWindow* w, TradeItem* item, bool isUser);   // 0x010759c0 (ret 0xc)
    void SetMidPanel();                                       // 0x010755d0
    void UpdateMidPanel();                                    // 0x01075ff0
    void RemoveExistingItem();                                // 0x01075690
    void Fn10763c0();                                         // 0x010763c0
    void Fn1076b00();                                         // 0x01076b00
    void AddItem(IWindow* parent, uint32_t index, uint32_t field, uint32_t type, TradeItem* item);  // 0x01076540 (ret 0x14)
    void AddNPCItems();                                       // 0x01076a00
    void AddUserItems();                                      // 0x01076a60
};

void* EAlloc(uint32_t size, const char* name, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // 0x00f473a0
char FUN_00807690(void* p, int v);                                  // 0x00807690
void FUN_008822e0(double value, int buf, int size, int fmt, int arg);   // 0x008822e0
void SetNumberString(uint32_t value, uint32_t flags, void* buf, int size);   // 0x00881ae0
void SetImageFromKey(IWindow* win, const char* key);                // 0x00e2f5c0
void FUN_005c8480(cSPUILayout** pos, cSPUILayout** value);          // 0x005c8480
struct PropKey { uint32_t v0, v1, v2; };
void GetPropertyAsKey(uint32_t prop, uint32_t key, PropKey* out);   // 0x006a1250

struct PlayerInventory {
    PAD(0); PAD(1); PAD(2); PAD(3); PAD(4); PAD(5); PAD(6); PAD(7); PAD(8); PAD(9);
    PAD(10); PAD(11); PAD(12); PAD(13); PAD(14); PAD(15); PAD(16); PAD(17); PAD(18); PAD(19);
    PAD(20); PAD(21); PAD(22); PAD(23); PAD(24); PAD(25); PAD(26); PAD(27); PAD(28); PAD(29);
    PAD(30); PAD(31); PAD(32); PAD(33); PAD(34);
    virtual uint32_t GetItemCount();                           // +0x8c
};
struct SpaceGame { PlayerInventory* GetPlayerInventory(); };       // 0x00a1ad60
SpaceGame* SpaceGameGet();                                         // 0x01002bd0

// 0x00435e90 helper body inlined by the compiler in two blocks
#define AUDIO_STATE(var) uint32_t var = 0; { AudioSystem* at_ = GetSystemAT(); if (at_) var = at_->Slot20(); }

static __forceinline void ItemLoop(cSPUISpaceTrading* t, uint32_t flag)
{
    int n = 10;
    do {
        TradeItem* item;
        int idx = t->mActiveItemIndex;
        if (idx == -1)
            item = 0;
        else if (t->mIsUserItem)
            item = GetSpaceTrading()->GetUserItem(idx);
        else
            item = GetSpaceTrading()->GetNPCItem(idx);
        GetSpaceTrading()->Fn103b950(flag, t->mIsUserItem, item, 1);
    } while (--n);
}

// @ 0x01076b80
bool cSPUISpaceTrading::DoMessage(IWindow* win, Message* msg)
{
    if (msg->type == 0xc) {
        uint32_t n = mAnimEnd - mAnimBegin;
        for (uint32_t i = 0; i < n; i++)
            mAnimBegin[i]->Update();
        mSub50.Fn36540();
    }

    if (msg->type == 0x1b) {
        if (win->GetControlID() >= 0x10000 && win->GetControlID() <= 0x21000) {
            IWindow* parent = win->GetParent();
            if (parent) {
                bool isUser;
                TradeItem* item;
                if (win->GetControlID() >= 0x10000 && win->GetControlID() <= 0x11000) {
                    isUser = true;
                    item = GetSpaceTrading()->GetUserItem(win->GetControlID() - 0x10000);
                } else {
                    isUser = false;
                    item = GetSpaceTrading()->GetNPCItem(win->GetControlID() - 0x20000);
                }
                IWindow* w = parent->FindWindowByID(0x64bb040, 1);
                if (item) {
                    w->SetFlag(1, 1);
                    Fn10759c0(parent, (TradeItem*)item, isUser);
                } else {
                    w->SetFlag(1, 0);
                    mSub50.Fn36620();
                }
            }
        }
    }

    if (msg->type == 0x1c) {
        IWindow* parent = win->GetParent();
        if (parent && win->GetControlID() >= 0x10000 && win->GetControlID() <= 0x21000) {
            parent->FindWindowByID(0x64bb040, 1)->SetFlag(1, 0);
            mSub50.Fn36620();
        }
    }

    if (msg->type != 0x17)
        return false;

    switch (msg->source->GetControlID()) {
    case 0x4c1510a:
        KillSetiEffects(0x23d6523e, GetRecorderState());
        mTrading = true;
        GetSpaceTrading()->PerformTrade();
        mTrading = false;
        SetMidPanel();
        mActiveItemIndex = -1;
        SetGlobalProperty(0x8952a239, 1.0f);
        {
            Empire* e = GetStarManager()->GetEmpireByID(IsArchived()->GetAvatar());
            uint32_t a, b;
            GetAED4D0()->Fn28(0x55125425, e->f58, &b, &a);
            GetB490()->Fn(b, a, 0, 1);
        }
        GetSpaceTrading()->Fn103dbd0(0);
        {
            uint32_t planet = GetActivePlanet()->f13c;
            GetSpaceTrading()->CreateNPCInventory(planet, 0);
        }
        Fn1076b00();
        return false;
    case 0x4c1510c:
        KillSetiEffects(0x2fd72b7e, GetRecorderState());
        mTrading = true;
        GetSpaceTrading()->PerformTrade();
        mTrading = false;
        SetMidPanel();
        mActiveItemIndex = -1;
        SetGlobalProperty(0x3ec6f5f7, 1.0f);
        {
            Empire* e = GetStarManager()->GetEmpireByID(IsArchived()->GetAvatar());
            uint32_t a, b;
            GetAED4D0()->Fn28(0x55125425, e->f58, &b, &a);
            GetB490()->Fn(b, a, 0, 1);
        }
        GetSpaceTrading()->Fn103dbd0(0);
        {
            uint32_t planet = GetActivePlanet()->f13c;
            GetSpaceTrading()->CreateNPCInventory(planet, 0);
        }
        Fn1076b00();
        return false;
    case 0x4c1510d:
        KillSetiEffects(0xc16d25b1, GetRecorderState());
        GetSpaceTrading()->Fn103b950(0, mIsUserItem, GetActiveItem(), 1);
        UpdateMidPanel();
        SetGlobalProperty(0xa63b066b, 1.0f);
        return false;
    case 0x4c1510f:
        KillSetiEffects(0xc16d25b1, GetRecorderState());
        GetSpaceTrading()->Fn103b950(1, mIsUserItem, GetActiveItem(), 1);
        UpdateMidPanel();
        SetGlobalProperty(0xa84a842c, 1.0f);
        return false;
    case 0x5db90d0: {
        {
            AudioSystem* a0 = GetSystemAT();
            KillSetiEffects(0xc16d25b1, a0 ? a0->Slot20() : 0);
        }
        ItemLoop(this, 1);
        UpdateMidPanel();
        AudioSystem* at = GetSystemAT();
        if (at) {
            at->Slot38(0x3cdd1a9);
            at->Slot40(0x34753a7, 0xa84a842c);
            at->Slot3C(0x34753aa, 1.0f);
            at->Slot58();
        }
        return false;
    }
    case 0x5db90d1: {
        {
            AudioSystem* a0 = GetSystemAT();
            KillSetiEffects(0xc16d25b1, a0 ? a0->Slot20() : 0);
        }
        ItemLoop(this, 0);
        UpdateMidPanel();
        AudioSystem* at = GetSystemAT();
        if (at) {
            at->Slot38(0x3cdd1a9);
            at->Slot40(0x34753a7, 0xa63b066b);
            at->Slot3C(0x34753aa, 1.0f);
            at->Slot58();
        }
        return false;
    }
    default:
        break;
    }

    uint32_t id = win->GetControlID();
    uint32_t rel = id - 0x20000;
    if (rel <= 0x1000) {
        IWindow* w = mLayout->FindWindowByID(id, 1);
        bool bad;
        if (!w) {
            bad = true;
        } else {
            uint32_t fl = w->GetParent()->FindWindowByID(0x5dce858, 1)->GetFlags();
            bad = false;
            if (fl & 1) bad = true;
        }
        TradeItem* item = GetSpaceTrading()->GetNPCItem(rel);
        if (bad || !item)
            return false;
        if (!item->Get18())
            return false;
        RemoveExistingItem();
        mIsUserItem = false;
        mActiveItemIndex = rel;
        KillSetiEffects(0x7cd49637, GetRecorderState());
        IWindow* c = w->GetParent()->FindWindowByID(0x4c6f028, 1);
        if (c) c->SetFlag(1, 1);
        Fn10763c0();
        SetGlobalProperty(0xfd1bd4f, 1.0f);
    }
    if (id - 0x10000 <= 0x1000) {
        IWindow* w = mLayout->FindWindowByID(id, 1);
        bool bad;
        if (!w) {
            bad = true;
        } else {
            uint32_t fl = w->GetParent()->FindWindowByID(0x5dce858, 1)->GetFlags();
            if (fl & 1) bad = true; else bad = false;
        }
        GetSpaceTrading()->GetUserItem(id - 0x10000);
        if (bad)
            return false;
        RemoveExistingItem();
        mIsUserItem = true;
        mActiveItemIndex = id - 0x10000;
        KillSetiEffects(0x7cd49637, GetRecorderState());
        IWindow* c = w->GetParent()->FindWindowByID(0x4c6f028, 1);
        if (c) c->SetFlag(1, 1);
        Fn10763c0();
        SetGlobalProperty(0xfd1bd4f, 1.0f);
    }
    return false;
}

// @ 0x01076540
void cSPUISpaceTrading::AddItem(IWindow* parent, uint32_t index, uint32_t field, uint32_t type, TradeItem* item)
{
    cSPUILayout* layout = (cSPUILayout*)EAlloc(0x18, (const char*)0x013f6b3c, 0, 0, 0, 0);
    if (layout)
        layout = layout->Ctor();
    if (layout)
        layout->AddRef();
    layout->Init(L"tradingItem", 0x40464100, 1, 0x5b598fa);

    IWindow* win = layout->FindWindowByID(0x5da5f30, 1);
    if (win->GetParent())
        win->GetParent()->SlotDC(win);
    parent->SlotD8(win);

    Rect* pr = parent->GetParent()->GetParent()->GetArea();
    float parentWidth = pr->right - pr->left;
    Rect* wr = win->GetArea();
    float cellW = (wr->right - wr->left) + 6.0f;
    Rect* wr2 = win->GetArea();
    float cellH = (wr2->bottom - wr2->top) + 6.0f;

    uint32_t columns = (uint32_t)(int)parentWidth / (uint32_t)(int)cellW;
    uint32_t row = index / columns;
    uint32_t col = index % columns;
    win->SetPosition((float)col * cellW, (float)row * cellH);

    win->SetFlag(1, 1);
    win->SetFlag(2, 1);
    IWindow* itemName = win->FindWindowByID(0x3504b00, 1);
    IWindow* itemPrice = win->FindWindowByID(0x3504c10, 1);

    wchar_t nameBuf[16];
    wchar_t priceBuf[16];

    if (item) {
        itemName->SetFlag(1, 1);
        FUN_008822e0((double)item->Get18(), (int)nameBuf, 0x10, *(int*)0x015b9448,
                     (int)0x0149c570);
    } else {
        itemName->SetFlag(1, 0);
        nameBuf[0] = 0;
    }

    itemPrice->SetFlag(1, 0);
    priceBuf[0] = 0;

    if (item && field != 0) {
        PropKey key;
        key.v0 = key.v1 = key.v2 = 0;
        GetPropertyAsKey(item->f30, 0x34f1a4f, &key);
        if (key.v0 != 0x4edcc2bf && key.v0 != 0xeb1a8062) {
            itemPrice->SetFlag(1, 1);
            SetNumberString(field, 0, priceBuf, 0x10);
        }
    }

    nameBuf[15] = 0;
    priceBuf[15] = 0;

    IWindow* label = win->FindWindowByID(0x4c07191, 1);
    label->Slot50(index + type);
    itemName->Slot80(nameBuf);
    itemPrice->Slot80(priceBuf);

    if (item) {
        if (item->Get18() == 0 && type == 0x20000)
            win->FindWindowByID(0x5dce858, 1)->SetFlag(1, 1);

        uint32_t state = GetSpaceTrading()->Fn103b950(1, (type == 0x10000), item, 0);
        label->SetFlag(2, state == 0);
        if (state == 2) {
            ITextWindow* text = itemName->Slot0C(0xf15f4bd);
            text->SetColor(0xffaa1111);
        }
        itemName->SetFlag(1, state != 4);
        win->FindWindowByID(0x5dce858, 1)->SetFlag(1, state == 4);

        IWindow* image = win->FindWindowByID(0x3504bc0, 1);
        PropKey imgBuf;
        imgBuf.v0 = imgBuf.v1 = imgBuf.v2 = 0;
        SetImageFromKey(image, item->Slot30(&imgBuf));

        if (item->f14 == 4) {
            void* v = GetSpaceTrading()->Fn103a540(item);
            if (v)
                image->Slot5C((uint32_t)v);
        }
    }

    label->Slot104(this);

    cSPUILayout** pos = mItemsEnd;
    if (pos < mItemsCap) {
        mItemsEnd = pos + 1;
        *pos = layout;
        if (layout)
            layout->AddRef();
    } else {
        FUN_005c8480(pos, &layout);
    }
    if (layout)
        layout->Release();
}

// @ 0x01076a00
void cSPUISpaceTrading::AddNPCItems()
{
    int i = 0;
    while (GetSpaceTrading()->GetUserItem(i) != 0) {
        TradeItem* item = GetSpaceTrading()->GetUserItem(i);
        TradeItemInfo* info = GetSpaceTrading()->Fn1039c00(item);
        AddItem(mWindow18, i, info->f10, 0x10000, item);
        ++i;
    }
}

// @ 0x01076a60
void cSPUISpaceTrading::AddUserItems()
{
    int i = 0;
    while (GetSpaceTrading()->GetNPCItem(i) != 0) {
        TradeItem* item = GetSpaceTrading()->GetNPCItem(i);
        uint32_t value = GetSpaceTrading()->Fn1039b70(item);
        AddItem(mWindow24, i, value, 0x20000, item);
        ++i;
    }
    PlayerInventory* inv = SpaceGameGet()->GetPlayerInventory();
    uint32_t n = inv->GetItemCount();
    if (n > 0) {
        uint32_t k = n;
        do {
            AddItem(mWindow24, i, 0, 0x20000, 0);
            ++i;
        } while (--k);
    }
}

// @ 0x01076b00
void cSPUISpaceTrading::Fn1076b00()
{
    while (((uint32_t)((char*)mItemsEnd - (char*)mItemsBegin)) & 0xfffffffc) {
        mItemsEnd[-1]->Shutdown(1);
        --mItemsEnd;
        cSPUILayout* old = *mItemsEnd;
        if (old)
            old->Release();
    }
    AddUserItems();
    AddNPCItems();
    if (mActiveItemIndex != -1)
        UpdateMidPanel();
    FUN_00807690(mClient14, 0);
    FUN_00807690(mClient20, 0);
}
