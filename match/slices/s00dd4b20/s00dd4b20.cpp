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

struct IWindow {
    PV4                                                            // slots 0..3
    virtual IWindow* GetChildHost();                               // slot 4 (+0x10)
    PV8 PV8 PV2                                                    // slots 5..22
    virtual void SetShade(uint32_t color);                         // slot 23 (+0x5c)
    PV4 PV2 PV                                                     // slots 24..30
    virtual void SetFlag(int flag, bool on);                       // slot 31 (+0x7c)
    virtual void SetCaption(const wchar_t* text);                  // slot 32 (+0x80)
    PV8 PV2                                                        // slots 33..42
    virtual void SetColor(uint32_t color);                         // slot 43 (+0xac)
    PV8 PV8                                                        // slots 44..59
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive);  // slot 60 (+0xf0)
};

struct cSPUILayout {
    IWindow* FindWindowByID(uint32_t id, bool recursive);          // 0x008105b0
};
struct cSPUIGlobalUI {
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
};
cPlanet* __cdecl GetActivePlanet();                                // 0x01021260

struct cTuning {
    int GetAmountA(cEmpire* e, int x);                             // 0x01030b70
    int GetAmountB(cEmpire* e, int x);                             // 0x0102f8d0
};
cTuning* __cdecl SpaceEconomyTuning();                             // 0x0102f810

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

extern ResourceKey g_kHomePlanetImage;                             // 0x015a2a80
extern ResourceKey g_kOwnedPlanetImage;                            // 0x015a2a74
extern ResourceKey g_kDefaultPlanetImage;                          // 0x015a29a0
extern const wchar_t* gMoneyFormat;                                // 0x015a2960
extern const wchar_t gMoneySymbol[];                               // 0x0147cd50

class cSPUICommScreen {
public:
    uint32_t pad00[3];
    cSPUILayout* mpLayout;                                         // +0x0c
    uint32_t pad10[0x34 / 4];
    cString mDefaultText;                                          // +0x44
    uint32_t pad58[(0xec - 0x58) / 4];
    string16 mTitle;                                               // +0xec

    const ResourceKey& GetEmpireImageKey(cEmpire* e, bool b);      // 0x00dd2320
    bool FUN_00dd21c0(cEmpire* e, const wchar_t** pText);          // 0x00dd21c0
    bool FUN_00dd4950(cPlanet* p, const wchar_t** pText);          // 0x00dd4950
    bool FUN_00dd2650(cPlanet* p, const wchar_t** pText);          // 0x00dd2650

    void UpdateSpaceInfo(uint32_t a1, uint32_t a2, bool a3, bool a4, bool a5, bool a6, bool a7, bool a8);
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
