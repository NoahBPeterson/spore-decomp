// Slice s00dd4b20 -- SP::cSPUICommScreen::UpdateSpaceInfo (0x00dd4b20, 1594 bytes, __thiscall, ret 0x20).
//
// Refreshes the space-comm screen's info panel for one empire / planet: the empire icon, the planet
// image (home, owned or plain), the empire-colour tints, the "visit" flags of the buttons chosen by
// the a3..a8 booleans, three tooltips (each shown only when the matching query succeeds), the two
// money read-outs (formatted with SetMoneyString, or the screen's default text when no empire or no
// amount), the tutorial-mode copy of the empire icon, and finally the empire name caption (the
// localized default name when the empire has none).
// Argument names are provisional: a1 = empire id, a2 = star-record id, a3..a8 = visibility flags.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no EH frame in the original).
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey() {}
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
    ResourceKey(const ResourceKey& k) : instanceID(k.instanceID), typeID(k.typeID), groupID(k.groupID) {}
};

struct ColorRGB { float r, g, b; };

// eastl::basic_string<wchar_t> (16 bytes).
void __cdecl ea_delete(void* p);   // 0x00f47380
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAlloc;
    void assign(const wchar_t* b, const wchar_t* e);               // 0x00423650
    ~string16()
    {
        if ((((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin)
            ea_delete(mpBegin);
    }
    string16& operator=(const string16& x)
    {
        if (this != &x)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
};
bool __cdecl operator==(const string16& s, const wchar_t* lit);   // 0x006ab760

struct cString {                    // SP::cString, 0x14 bytes
    uint32_t d[5];
    const wchar_t* GetText();                                      // 0x006b55c0
};

// Iterator over an IWindow's intrusive child list. The node stores the link to the next node;
// the element itself lives at (char*)node + gWindowNodeOffset. Returned by value, so MSVC
// passes a hidden result buffer (the class has a user copy constructor and is therefore
// non-trivial).
struct ChildIter {
    void* mpNode;
    ChildIter() : mpNode(0) {}
    ChildIter(const ChildIter& x) : mpNode(x.mpNode) {}
};

struct IWindow {
    virtual void v00();                                            // slot 0 (+0x00)
    virtual void v01();                                            // slot 1 (+0x04)
    virtual void v02();                                            // slot 2 (+0x08)
    virtual void* Cast(uint32_t id);                               // slot 3 (+0x0c)
    virtual IWindow* GetChildHost();                               // slot 4 (+0x10)
    PV2                                                            // slots 5..6
    virtual uint32_t GetID();                                      // slot 7 (+0x1c)
    PV8 PV2 PV                                                     // slots 8..18
    virtual int GetSelectionState(int arg);                        // slot 19 (+0x4c)
    PV2 PV                                                         // slots 20..22
    virtual void SetShade(uint32_t color);                         // slot 23 (+0x5c)
    PV4 PV2 PV                                                     // slots 24..30
    virtual void SetFlag(int flag, bool on);                       // slot 31 (+0x7c)
    virtual void SetCaption(const wchar_t* text);                  // slot 32 (+0x80)
    PV8 PV2                                                        // slots 33..42
    virtual void SetColor(uint32_t color);                         // slot 43 (+0xac)
    PV4 PV2 PV                                                     // slots 44..50
    virtual ChildIter GetChildListBegin();                         // slot 51 (+0xcc)
    virtual ChildIter GetChildListEnd();                           // slot 52 (+0xd0)
    PV4 PV2 PV                                                     // slots 53..59
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive);  // slot 60 (+0xf0)
};

class cSPUILayout { public:
    virtual void v00();                                            // +0x00
    virtual int AddRef();                                          // +0x04
    virtual int Release();                                         // +0x08
    cSPUILayout* ctor();                                           // 0x00810000 (returns this)
    bool Init(const wchar_t* name, int a, bool b, uint32_t c);     // 0x00812160
    void Shutdown(unsigned int b);                                 // 0x00811ad0
    void SetVisibility(int b);                                     // 0x00810590
    IWindow* FindWindowByID(uint32_t id, bool recursive);          // 0x008105b0
};
class cSPUIGlobalUI { public:
    IWindow* FindWindowByID(uint32_t id);                          // 0x00e012b0
};
struct cTutorialMgr { uint32_t pad[0x89]; cSPUIGlobalUI* mpGlobalUI; };   // +0x224
cTutorialMgr* __cdecl TutorialManager();                           // 0x010666a0

struct cEmpire {
    const ColorRGB* GetColor(ColorRGB* out);                       // 0x00c32cd0
    string16* GetEmpireName();                                     // 0x005c65e0
};
struct cStarManager {
    void* GetStarRecord(uint32_t id);                              // 0x00ba6dc0
    cEmpire* GetEmpireByID(uint32_t id);                           // 0x00ba9370
};
cStarManager* __cdecl StarManager();                               // 0x00b3d2a0
cEmpire* __cdecl GetPlayerEmpire();                                // 0x01021300
void* __cdecl GetPlayerHomePlanet();                               // 0x01021370

struct cPlanet {
    PV8 PV8 PV4 PV2                                                // slots 0..21
    virtual bool IsNotOwnable();                                   // slot 22 (+0x58)
    uint32_t pad04[(0x13c - 4) / 4];
    void* mpRecord;                                                // +0x13c
    void* GetEconomyKey();                                         // 0x00c71e30
};
cPlanet* __cdecl GetActivePlanet();                                // 0x01021260

struct cTuning {
    int GetAmountA(cEmpire* e, int x);                             // 0x01030b70
    int GetAmountB(cEmpire* e, int x);                             // 0x0102f8d0
    int GetAmountA();                                              // 0x01030b70 (this-only form)
    int GetAmountB();                                              // 0x0102f8d0 (this-only form)
};
cTuning* __cdecl SpaceEconomyTuning();                             // 0x0102f810
cTuning* __cdecl SpaceEconomyTuning(void* economyKey, int mode);   // 0x0102f810

struct cTokenTranslator { uint32_t pad[3]; void* mpStar; };        // +0xc
extern cTokenTranslator* gpTokenTranslator;                        // 0x016e0d08

struct INameLocale { string16 GetText(uint32_t id); };             // 0x005ecf80
INameLocale* __cdecl LocaleManager();                              // 0x004010a0

struct IAudioSystem { PV8 virtual int GetPatch(); };               // slot 8 (+0x20)
IAudioSystem* __cdecl GetSystemAT();                               // 0x00a206f0
void __cdecl KillSetiEffects(uint32_t id, int arg);                // 0x00435ed0
uint32_t __cdecl GetCurrentGameMode();                             // 0x00b5b800
void __cdecl SetEmpireIcon(uint32_t empireId, IWindow* w);         // 0x00e2e6e0
void __cdecl SetImageFromKey(IWindow* w, const ResourceKey& key);  // 0x00e2f5c0
uint32_t __cdecl ColorRGBToU32(const ColorRGB* c);                 // 0x00458a40
void __cdecl SetTooltipText(IWindow* w, const wchar_t* text, int a, int b);   // 0x00806de0
int __cdecl SetMoneyString(double v, wchar_t* buf, int size, const wchar_t* fmt, const wchar_t* sym);   // 0x008822e0
int __cdecl SetMoneyString(double v, wchar_t* buf, int size);      // 0x00b33c30 (globals read inside)

extern ResourceKey g_kHomePlanetImage;                             // 0x015a2a80
extern ResourceKey g_kOwnedPlanetImage;                            // 0x015a2a74
extern ResourceKey g_kDefaultPlanetImage;                          // 0x015a29a0
extern const wchar_t* gMoneyFormat;                                // 0x015a2960
extern const wchar_t gMoneySymbol[];                               // 0x0147cd50

// ---------------------------------------------------------------------------
// Types used by cSPUICommScreen::DoMessage and the event-log layout helpers.
// ---------------------------------------------------------------------------

// One UI message: the sender window, the message kind, the control ID that fired it and up to
// two flag words. mpTarget is the game object the message is about.
struct UIMessage {
    IWindow*  mpSender;                                            // +0x00
    uint32_t  mUnused04;                                           // +0x04
    uint32_t  mType;                                               // +0x08
    uint32_t  mControlID;                                          // +0x0c
    uint8_t   mFlags10;                                            // +0x10
    uint8_t   mPad11[3];
    uint8_t   mFlags14;                                            // +0x14
    uint8_t   mPad15[3];
    IWindow*  mpTarget;                                            // +0x18
};

// Minimal view of a sim object: only the object-type tag is needed here.
struct IGameObject {
    virtual void v00();                                            // +0x00
    virtual void v01();                                            // +0x04
    PV4 PV                                                         // slots 2..6
    virtual int GetType();                                         // slot 7 (+0x1c)
};

// Cast target 0x8ed27e7a: button state (slot 8/9) and button-group tag (slot 11/12).
struct IButton {
    PV8                                                            // slots 0..7
    virtual uint32_t GetState();                                   // slot 8 (+0x20)
    virtual void SetState(uint32_t v);                             // slot 9 (+0x24)
    PV                                                             // slot 10
    virtual uint32_t GetGroup();                                   // slot 11 (+0x2c)
    virtual void SetGroup(uint32_t v);                             // slot 12 (+0x30)
};

struct cCommEvent {
    uint32_t pad00[0x0e];                                          // +0x00
    uint32_t mAt38;                                                // +0x38
    int GetID();                                                   // 0x006c0200
};

struct cCommManager {
    void CloseCommEvent();                                         // 0x00aea210
    void SetupAudio();                                             // 0x00ae90d0
    cCommEvent* GetEvent();                                        // 0x00a42730
    void FUN_00aeb720(int commContext, int id);                    // 0x00aeb720
    void ReleaseSelected(void* commEvent);                         // 0x00aea850
    void FUN_00aebcd0(int index);                                  // 0x00aebcd0
};
cCommManager* __cdecl CommManager();                               // 0x00b3d4a0

struct cSPUISpace {
    void FUN_01077630();                                           // 0x01077630
    bool FUN_01075500();                                           // 0x01075500
    void FUN_01075ef0();                                           // 0x01075ef0
};
struct cSPSimulatorSpaceGame {
    uint32_t pad00[6];                                             // +0x00
    cSPUISpace* mpSpace;                                           // +0x18
};
cSPSimulatorSpaceGame* __cdecl SpaceGameGet();                     // 0x01002bd0

struct cUFOSimulator {
    void FUN_010019a0();                                           // 0x010019a0
    void FUN_00ffd280();                                           // 0x00ffd280
};
cUFOSimulator* __cdecl GetUFOSimulator();                          // 0x00ffbe50

struct cAssetView {
    void ShowRelationship(int a, int b);                           // 0x00e35290
    void HideRelationship();                                       // 0x00e352b0
};
struct cCivState {
    uint32_t pad00[0x39];                                          // +0x00
    cAssetView* mpAssetView;                                       // +0xe4
};
struct cCivModeStrategy {
    static cCivModeStrategy* Get();                                // 0x00cf74c0
    cCivState* GetState();                                         // 0x00cf74f0
};
struct cSPUIRolloverCivRelationship {
    void ShowRelationshipRollover(IWindow* anchor, int empireId, int mode);  // 0x00e2d6a0
    void HideRelationshipRollover();                               // 0x00e2a6c0
};
struct cTutorialMgrRel {
    uint8_t pad00[0x5a4];                                          // +0x00
    cSPUIRolloverCivRelationship* mpRollover;                      // +0x5a4
};
cTutorialMgrRel* __cdecl TutorialManagerRel();                     // 0x010666a0

struct cStarRecordRef {
    int GetCommContext(uint32_t a, uint32_t b, int c, int d);      // 0x00ce6950
};

int __cdecl GetRecorderState();                                    // 0x00435e90
void __cdecl FUN_0102d7e0();                                       // 0x0102d7e0
int __cdecl GetPlayerEmpireID();                                   // 0x01021090
void* __cdecl SPUIOperatorNew(int size, const char* name, int a, int b, int c, int d);   // 0x00f473a0

// Layout stack drained by ShutdownLayoutStack / GetEventLogItemLayout (eastl::vector).
extern cSPUILayout** gpLayoutStackBegin;                           // 0x015a2c40
extern cSPUILayout** gpLayoutStackEnd;                             // 0x015a2c44
extern int gWindowNodeOffset;                                      // 0x01440aec
extern const wchar_t gEmptyText[];                                 // 0x013ec468
extern const wchar_t gCommSpeakerText[];                           // 0x013fa1d4
extern const wchar_t gEventLogItemName[];                          // 0x0147cdf0
extern const char gEventLogLayoutName[];                           // 0x0147ce0c

class cSPUICommScreen {
public:
    uint32_t pad00[2];                                             // +0x00
    IWindow* mpOwnerWindow;                                        // +0x08
    cSPUILayout* mpLayout;                                         // +0x0c
    uint32_t pad10[5];                                             // +0x10
    IWindow* mpChildWindow;                                        // +0x24
    uint32_t pad28[(0x44 - 0x28) / 4];                             // +0x28
    cString mDefaultText;                                          // +0x44
    uint32_t pad58[(0xec - 0x58) / 4];                             // +0x58
    string16 mTitle;                                               // +0xec

    const ResourceKey& GetEmpireImageKey(cEmpire* e, bool b);      // 0x00dd2320
    bool FUN_00dd21c0(cEmpire* e, const wchar_t** pText);          // 0x00dd21c0
    bool FUN_00dd4950(cPlanet* p, const wchar_t** pText);          // 0x00dd4950
    bool FUN_00dd2650(cPlanet* p, const wchar_t** pText);          // 0x00dd2650
    void FUN_00dd2d30();                                           // 0x00dd2d30
    void SetSpeakerText(const wchar_t* text);                      // 0x00dd2ad0

    void UpdateSpaceInfo(uint32_t a1, uint32_t a2, bool a3, bool a4, bool a5, bool a6, bool a7, bool a8);
    bool DoMessage(IWindow* window, UIMessage* msg);               // 0x00dd5160
};

// @ 0x00dd4b20
void cSPUICommScreen::UpdateSpaceInfo(uint32_t a1, uint32_t a2, bool a3, bool a4, bool a5, bool a6, bool a7, bool a8)
{
    cEmpire* player = GetPlayerEmpire();
    IWindow* wIcon = mpLayout->FindWindowByID(0x4a4504f, true);
    IWindow* wPlanet = mpLayout->FindWindowByID(0x49382d8, true);
    IWindow* wUnused = mpLayout->FindWindowByID(0x49382e8, true);
    IWindow* wEmpireImg = mpLayout->FindWindowByID(0x5edff88, true);
    IWindow* wTint = mpLayout->FindWindowByID(0x6243260, true);
    void* star = StarManager()->GetStarRecord(a2);
    cPlanet* planet = GetActivePlanet();
    (void)wUnused;

    bool flag;
    if (planet && !planet->IsNotOwnable()) {
        SetEmpireIcon(a1, wIcon);
        flag = true;
    } else {
        flag = false;
    }
    wIcon->SetFlag(1, flag);

    if (planet) {
        void* recordA = planet->mpRecord;
        if (GetPlayerHomePlanet() == recordA)
            SetImageFromKey(wPlanet, g_kHomePlanetImage);
        else if (planet->IsNotOwnable())
            SetImageFromKey(wPlanet, g_kOwnedPlanetImage);
        else
            SetImageFromKey(wPlanet, g_kDefaultPlanetImage);
    } else {
        SetImageFromKey(wPlanet, g_kDefaultPlanetImage);
    }

    cEmpire* emp = StarManager()->GetEmpireByID(a1);
    uint32_t color;
    if (emp) {
        ColorRGB c;
        color = ColorRGBToU32(emp->GetColor(&c));
    } else {
        color = 0x80808080;
    }

    if (wEmpireImg) {
        if (emp) {
            SetImageFromKey(wEmpireImg, GetEmpireImageKey(emp, false));
        } else {
            ResourceKey k(0xbf4a63b8, 0x2f7d0004, 0x0354663b);
            SetImageFromKey(wEmpireImg, k);
        }
    }
    if (wTint)
        wTint->SetColor(color);

    if (GetCurrentGameMode() == 0x1654c05) {
        IWindow* gw = TutorialManager()->mpGlobalUI->FindWindowByID(0x64e7368);
        if (gw) {
            IWindow* host = gw->GetChildHost();
            host->SetFlag(1, true);
            IWindow* wL = host->FindWindowByID(0x64e7c28, true);
            IWindow* wM = host->FindWindowByID(0x64e7c29, true);
            if (wM)
                SetImageFromKey(wM, GetEmpireImageKey(player, false));
            if (wL) {
                ColorRGB c;
                wL->SetColor(ColorRGBToU32(player->GetColor(&c)));
            }
        }
    }

    if (a3) {
        IAudioSystem* at = GetSystemAT();
        KillSetiEffects(0x94271b42, at ? at->GetPatch() : 0);
    }
    mpLayout->FindWindowByID(0x5e3c090, true)->SetFlag(1, a3);

    const wchar_t* text = L"";
    bool ok1 = a3 && FUN_00dd21c0(emp, &text);
    IWindow* wF = mpLayout->FindWindowByID(0x57df5ca, true);
    wF->SetFlag(2, ok1);
    SetTooltipText(wF, text, -1, 1);

    text = L"";
    bool ok2 = a3 && FUN_00dd4950(planet, &text);
    IWindow* wG = mpLayout->FindWindowByID(0x57df5c8, true);
    wG->SetFlag(2, ok2);
    SetTooltipText(wG, text, -1, 1);

    text = L"";
    bool ok3 = a3 && FUN_00dd2650(planet, &text);
    IWindow* wH = mpLayout->FindWindowByID(0x57df5c9, true);
    wH->SetFlag(2, ok3);
    SetTooltipText(wH, text, -1, 1);

    mpLayout->FindWindowByID(0x5dff098, true)->SetFlag(1, a5);
    mpLayout->FindWindowByID(0x5e51d28, true)->SetFlag(2, true);
    mpLayout->FindWindowByID(0x5e51d30, true)->SetFlag(2, a4);
    mpLayout->FindWindowByID(0x5e4f778, true)->SetFlag(1, a6);
    mpLayout->FindWindowByID(0x5e4f770, true)->SetFlag(1, a8);
    mpLayout->FindWindowByID(0x5e4f788, true)->SetFlag(1, a7);
    mpLayout->FindWindowByID(0x2cf324c, true)->SetShade(color);

    IWindow* wI = mpLayout->FindWindowByID(0x66fc580, true);
    wI->SetFlag(1, ok2);
    if (ok2) {
        int amount = 0;
        if (emp)
            amount = SpaceEconomyTuning()->GetAmountA(emp, 0);
        if (emp && amount) {
            wchar_t buf[16];
            SetMoneyString((double)amount, buf, 16, gMoneyFormat, gMoneySymbol);
            buf[15] = 0;
            wI->SetCaption(buf);
        } else {
            wI->SetCaption(mDefaultText.GetText());
        }
    }

    IWindow* wJ = mpLayout->FindWindowByID(0x66fc590, true);
    wJ->SetFlag(1, ok3);
    if (ok3) {
        int amount = 0;
        if (emp)
            amount = SpaceEconomyTuning()->GetAmountB(emp, 0);
        if (emp && amount) {
            wchar_t buf[16];
            SetMoneyString((double)amount, buf, 16, gMoneyFormat, gMoneySymbol);
            buf[15] = 0;
            wJ->SetCaption(buf);
        } else {
            wJ->SetCaption(mDefaultText.GetText());
        }
    }

    gpTokenTranslator->mpStar = star;

    const wchar_t* name;
    if (emp) {
        name = emp->GetEmpireName()->mpBegin;
    } else {
        if (mTitle == L"") {
            string16 tmp = LocaleManager()->GetText(0x51aa76bb);
            mTitle = tmp;
        }
        name = mTitle.mpBegin;
    }
    wUnused->SetCaption(name);
}

// ---------------------------------------------------------------------------
// Layout-stack helpers (event log items are pooled: hide instead of destroy).
// ---------------------------------------------------------------------------

// @ 0x00dd5950
void ShutdownLayoutStack()
{
    while (gpLayoutStackBegin != gpLayoutStackEnd) {
        cSPUILayout* layout = gpLayoutStackEnd[-1];
        --gpLayoutStackEnd;
        layout->Shutdown(1);
        layout->Release();
    }
}

// @ 0x00dd5990
cSPUILayout* GetEventLogItemLayout()
{
    if (gpLayoutStackBegin != gpLayoutStackEnd) {
        cSPUILayout* layout = gpLayoutStackEnd[-1];
        --gpLayoutStackEnd;
        layout->SetVisibility(1);
        return layout;
    }

    cSPUILayout* layout = (cSPUILayout*)SPUIOperatorNew(0x18, gEventLogLayoutName, 0, 0, 0, 0);
    layout = layout ? layout->ctor() : 0;
    layout->AddRef();
    layout->Init(gEventLogItemName, 0x40464100, true, 0x3469e7a3);
    layout->SetVisibility(1);
    return layout;
}

// ---------------------------------------------------------------------------
// cSPUICommScreen::DoMessage
//
// Window-proc entry point for the space-comm screen. Handles the generic message kinds
// (radio-group sync on 0x13, window teardown on 0xa, civ-relationship rollover on 0x1b/0x1c)
// and then dispatches on the control ID of the button that fired the message.
// ---------------------------------------------------------------------------

// @ 0x00dd5160
bool cSPUICommScreen::DoMessage(IWindow* window, UIMessage* msg)
{
    if (msg->mType == 0x8ef0c8dd)
        FUN_00dd2d30();

    // The "comm event closed" notification: only act when the pressed button is the close
    // button (id 1) of the comm-event window itself.
    if (window->GetID() == 0x1c3bb0c && msg->mType == 0xe && msg->mControlID == 1) {
        if ((msg->mFlags10 & 1) && !(msg->mFlags14 & 1))
            CommManager()->CloseCommEvent();
        return true;
    }

    // Radio-group sync: copy the pressed radio button's state and group tag to every sibling
    // button of the same window.
    if (msg->mType == 0x13) {
        uint32_t id = window->GetID();
        if (id == 0x5e51d28 || (id >= 0x57df5c8 && id <= 0x57df5ca) || id == 0x5e51d30) {
            IButton* source = (IButton*)window->Cast(0x8ed27e7a);
            uint32_t group = source->GetGroup();
            uint32_t state = source->GetState();
            ChildIter begin = window->GetChildListBegin();
            ChildIter end = window->GetChildListEnd();
            void* node = begin.mpNode;
            while (node != end.mpNode) {
                IWindow* child = (IWindow*)((char*)node + gWindowNodeOffset);
                if (child) {
                    IButton* button = (IButton*)child->Cast(0x8ed27e7a);
                    if (button) {
                        button->SetGroup(group);
                        button->SetState(state);
                    }
                }
                node = *(void**)node;
            }
        }
    }

    switch (msg->mType) {
    case 0xa: {
        // Window teardown: release the target, and re-arm the audio when the screen itself
        // is the window being destroyed.
        IWindow* target = msg->mpTarget;
        if (target)
            target->v00();
        if (msg->mControlID == 0x4b417d4 && window == target)
            CommManager()->SetupAudio();
        if (target)
            target->v01();
        return false;
    }
    case 0x1b: {
        // Civ-relationship rollover shown for the clicked empire.
        IGameObject* target = (IGameObject*)msg->mpTarget;
        if (target->GetType() == 0x4501222) {
            if (GetCurrentGameMode() == 0x1654c04) {
                if (mpOwnerWindow != 0 && cCivModeStrategy::Get() != 0 &&
                    cCivModeStrategy::Get()->GetState() != 0 &&
                    cCivModeStrategy::Get()->GetState()->mpAssetView != 0) {
                    cCivState* state = cCivModeStrategy::Get()->GetState();
                    state->mpAssetView->ShowRelationship((int)target,
                                                         mpOwnerWindow->GetSelectionState(0));
                }
            } else if (GetCurrentGameMode() == 0x1654c05) {
                cCommEvent* commEvent = CommManager()->GetEvent();
                if (commEvent) {
                    int empireId = commEvent->GetID();
                    if (empireId != -1 && empireId != GetPlayerEmpireID()) {
                        TutorialManagerRel()->mpRollover->ShowRelationshipRollover(
                            (IWindow*)target, empireId, 1);
                    }
                }
            }
        }
        break;
    }
    case 0x1c: {
        // Civ-relationship rollover hidden again.
        IGameObject* target = (IGameObject*)msg->mpTarget;
        if (target->GetType() == 0x4501222) {
            if (GetCurrentGameMode() == 0x1654c04) {
                cCivModeStrategy::Get()->GetState()->mpAssetView->HideRelationship();
            } else if (GetCurrentGameMode() == 0x1654c05) {
                cCommEvent* commEvent = CommManager()->GetEvent();
                if (commEvent && commEvent->GetID() != -1)
                    TutorialManagerRel()->mpRollover->HideRelationshipRollover();
            }
        }
        break;
    }
    }

    switch (msg->mControlID) {
    case 0x57df5c8:
    case 0x57df5c9: {
        // The two money read-outs of the selected empire / planet.
        cPlanet* planet = GetActivePlanet();
        void* economyKey = planet->GetEconomyKey();
        const wchar_t* text = gEmptyText;
        int amount;
        IWindow* moneyWindow;
        bool ok;
        if (msg->mControlID == 0x57df5c8) {
            KillSetiEffects(0xa56f01d6, GetRecorderState());
            GetUFOSimulator()->FUN_010019a0();
            amount = SpaceEconomyTuning(economyKey, 0)->GetAmountA();
            moneyWindow = mpLayout->FindWindowByID(0x66fc580, true);
            ok = FUN_00dd4950(GetActivePlanet(), &text);
        } else {
            KillSetiEffects(0xe53b6408, GetRecorderState());
            GetUFOSimulator()->FUN_00ffd280();
            amount = SpaceEconomyTuning(economyKey, 0)->GetAmountB();
            moneyWindow = mpLayout->FindWindowByID(0x66fc590, true);
            ok = FUN_00dd2650(GetActivePlanet(), &text);
        }
        msg->mpSender->SetFlag(2, ok);
        SetTooltipText(msg->mpSender, text, -1, 1);
        moneyWindow->SetFlag(1, true);
        if (!ok)
            return true;
        if (amount == 0) {
            moneyWindow->SetCaption(mDefaultText.GetText());
            return true;
        }
        wchar_t buf[16];
        SetMoneyString((double)amount, buf, 0x10);
        buf[15] = 0;
        moneyWindow->SetCaption(buf);
        return true;
    }
    case 0x4b417d4: {
        // The comm-screen background was clicked: locate it in the child list and tell the
        // comm manager which entry was picked.
        KillSetiEffects(0x7cd49637, GetRecorderState());
        ChildIter end = mpChildWindow->GetChildListEnd();
        ChildIter begin = mpChildWindow->GetChildListBegin();
        void* node = begin.mpNode;
        int index = 0;
        while (node != end.mpNode) {
            if ((IWindow*)((char*)node + gWindowNodeOffset) == window) {
                CommManager()->FUN_00aebcd0(index);
                break;
            }
            node = *(void**)node;
            ++index;
        }
        return true;
    }
    case 0x5dff098: {
        // Open the comm event for the current contact.
        if (SpaceGameGet()->mpSpace->FUN_01075500())
            SpaceGameGet()->mpSpace->FUN_01075ef0();
        FUN_0102d7e0();
        void* commEvent = CommManager()->GetEvent();
        cPlanet* planet = GetActivePlanet();
        int context = ((cStarRecordRef*)planet->mpRecord)->GetCommContext(
            0xc8fbf7d7, 0x2ea8fb98, 0, 0);
        CommManager()->FUN_00aeb720(context, CommManager()->GetEvent()->GetID());
        CommManager()->ReleaseSelected(commEvent);
        return true;
    }
    case 0x5e4f770: {
        void* commEvent = CommManager()->GetEvent();
        cPlanet* planet = GetActivePlanet();
        int context = ((cStarRecordRef*)planet->mpRecord)->GetCommContext(
            CommManager()->GetEvent()->mAt38, 0xe2aec541, 0, 0);
        CommManager()->FUN_00aeb720(context, CommManager()->GetEvent()->GetID());
        CommManager()->ReleaseSelected(commEvent);
        return true;
    }
    case 0x5e4f778: {
        // Leave the comm event.
        if (SpaceGameGet()->mpSpace->FUN_01075500())
            SpaceGameGet()->mpSpace->FUN_01075ef0();
        FUN_0102d7e0();
        void* commEvent = CommManager()->GetEvent();
        CommManager()->CloseCommEvent();
        CommManager()->ReleaseSelected(commEvent);
        return true;
    }
    case 0x5e4f788: {
        void* commEvent = CommManager()->GetEvent();
        cPlanet* planet = GetActivePlanet();
        int context = ((cStarRecordRef*)planet->mpRecord)->GetCommContext(
            CommManager()->GetEvent()->mAt38, 0x1fce3de8, 0, 0);
        CommManager()->FUN_00aeb720(context, CommManager()->GetEvent()->GetID());
        CommManager()->ReleaseSelected(commEvent);
        return true;
    }
    case 0x5e51d28:
    case 0x5e51d30: {
        IAudioSystem* audio = GetSystemAT();
        KillSetiEffects(0x94271b42, audio ? audio->GetPatch() : 0);
        void* commEvent = CommManager()->GetEvent();
        cPlanet* planet = GetActivePlanet();
        int context = ((cStarRecordRef*)planet->mpRecord)->GetCommContext(
            0xc8fbf7d7, msg->mControlID == 0x5e51d28 ? 0xd38e52bf : 0xf6f6b0a5, 0, 0);
        CommManager()->FUN_00aeb720(context, CommManager()->GetEvent()->GetID());
        CommManager()->ReleaseSelected(commEvent);
        return true;
    }
    case 0x57df5ca: {
        // Speaker / portrait panel refresh.
        IAudioSystem* audio = GetSystemAT();
        KillSetiEffects(0x94271b42, audio ? audio->GetPatch() : 0);
        SpaceGameGet()->mpSpace->FUN_01077630();
        SetSpeakerText(gCommSpeakerText);
        mpLayout->FindWindowByID(0x5dff098, true)->SetFlag(1, true);
        mpLayout->FindWindowByID(0x5e4f778, true)->SetFlag(1, true);
        return true;
    }
    }

    return false;
}
