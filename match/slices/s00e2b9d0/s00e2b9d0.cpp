// UpdateVehicleButtons @ 0x00E2B9D0 (2052 bytes, __thiscall, no args): cSPUIRolloverCivCityHall's refresh of the three
// "buy vehicle" buttons (windows 0x62d6902 / 0x62d6908 / 0x62d690f). For each button it works out whether the
// vehicle is available (the city's vehicle model key is non-null, and for button 1 the city has a target
// position) and affordable (player money >= cost), enables / shades the button and builds the tooltip text.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PV virtual void CAT_(_pv, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

struct ResourceKey { uint32_t instanceID, typeID, groupID; };
struct Vector3 { float x, y, z; };

extern Vector3 gZeroVector;                                // 0x016ac548
extern wchar_t gEmptyStringBuf[2];                         // 0x01667bac (shared empty eastl string storage)
bool __cdecl Vector3_NotEqual(const Vector3* a, const Vector3* b);                // 0x0041dd30
bool __cdecl ResourceKey_Equal(const ResourceKey* a, const ResourceKey* b);        // 0x004eb930
void __cdecl ea_delete(void* p);                           // 0x00f47380

// eastl::basic_string<wchar_t> as the game uses it (the allocator member is never initialised here)
struct string16
{
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAlloc;
    string16() { mpBegin = gEmptyStringBuf; mpEnd = gEmptyStringBuf; mpCapacity = gEmptyStringBuf + 1; }
    ~string16()
    {
        if ((((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin)
            ea_delete(mpBegin);
    }
    void append(const wchar_t* b, const wchar_t* e);       // 0x00429580 (ret 8)
    string16& operator+=(const wchar_t* s);                // 0x00599bb0 (ret 4)
};

struct cString   // SP::cString, 0x14 bytes
{
    uint32_t d[5];
    cString(uint32_t tableID, uint32_t instanceID, const wchar_t* defaultText);   // 0x006b5770 (ret 0xc)
    ~cString();                                                                    // 0x006b5240
    const wchar_t* GetText();                                                      // 0x006b55c0
};

struct IWindow
{
    PV8 PV2
    virtual int IsVisible();                        // +0x28 (slot 10)
    PV8 PV4
    virtual void SetShade(uint32_t color);          // +0x5c (slot 23)
    PV4 PV2 PV
    virtual void SetFlag(int flag, bool on);        // +0x7c (slot 31)
};

struct cSPUILayout
{
    char data[0x9c];
    IWindow* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0 (ret 8)
};

struct cCity
{
    char pad000[0x32c];
    Vector3 mTarget;                                        // +0x32c (0x00fa0e00 returns its address)
    int GetVehicleSpecialty();                              // 0x00bd81d0
    Vector3* FUN_00fa0e00();                                // 0x00fa0e00
};

struct cCivilization
{
    int FUN_00bf2100(int specialty);                        // 0x00bf2100 (ret 4): vehicles available
    float FUN_00bf2170(int specialty, int index);           // 0x00bf2170 (ret 8): cost
    float GetMoney();                                       // 0x00bef6d0
    const ResourceKey* GetModelTypeKey(int modelType);      // 0x00bf9770 (ret 4)
    int FUN_00bf0c50();                                     // 0x00bf0c50: vehicle count
    int FUN_0113ab90();                                     // 0x0113ab90: returns 0x24 (capacity)
};

struct cGameNounManager { cCivilization* GetPlayerCivilization(); };   // 0x00b25fb0
cGameNounManager* __cdecl NounManager();                                // 0x00b3d300
int __cdecl FUN_00c9e6d0(int specialty, int index);                     // 0x00c9e6d0

struct IAudioSystem { PV8 virtual int GetPatch(); };                    // +0x20
IAudioSystem* __cdecl GetSystemAT();                                    // 0x00a206f0
void __cdecl KillSetiEffects(uint32_t id, int arg);                     // 0x00435ed0
void __cdecl SetTooltipText(IWindow* w, const wchar_t* text, uint32_t color, int flag);   // 0x00806de0
void __cdecl UpdateMouseFocus(int flag);                                // 0x00804f50

struct cCivModeStrategy
{
    static cCivModeStrategy* Get();                         // 0x00cf74c0
    bool CanBuildAirVehicles();                             // 0x00cf7600
};

struct cSPUIRolloverCivCityHall
{
    char pad000[0xc];
    cSPUILayout mLayout;                                    // +0x0c
    cCity* mpCity;                                          // +0xa8
    void UpdateVehicleButtons();
};

static __forceinline bool Vector3_Equal(const Vector3& a, const Vector3& b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
static __forceinline bool IsNonZero(const ResourceKey* k) { return k->instanceID != 0 || k->typeID != 0 || k->groupID != 0; }

#define APPEND_FILL_LINE() \
    do { \
        if (civ->FUN_00bf0c50() >= civ->FUN_0113ab90()) { cString line(0xc0152a6d, 0x65cd6f2, 0); text += line.GetText(); } \
        else { cString line(0xc0152a6d, 0x6562784, 0); text += line.GetText(); } \
    } while (0)

#define APPEND_LINE(ID) \
    do { cString line(0xc0152a6d, (ID), 0); text += line.GetText(); } while (0)

enum { kRed = 0xffff0000, kWhite = 0xffffffff };

void cSPUIRolloverCivCityHall::UpdateVehicleButtons()   // @ 0x00E2B9D0
{
    bool affordable;
    cCivilization* civ = NounManager()->GetPlayerCivilization();
    if (!civ || !mpCity)
        return;

    // ---- the city hall button: make sure the space music is not playing ----
    IWindow* w = mLayout.FindWindowByID(0x62d5618, true);
    if (!(w->IsVisible() & 1))
    {
        IAudioSystem* at = GetSystemAT();
        KillSetiEffects(0xa47319c2, at ? at->GetPatch() : 0);
    }
    w->SetFlag(1, true);

    // ---- vehicle button 0 ----
    ResourceKey zeroKey = { 0, 0, 0 };
    w = mLayout.FindWindowByID(0x62d6902, true);
    w->SetFlag(1, true);
    bool available = civ->FUN_00bf2100(mpCity->GetVehicleSpecialty()) > 0 &&
                     IsNonZero(civ->GetModelTypeKey(FUN_00c9e6d0(mpCity->GetVehicleSpecialty(), 0)));
    affordable = civ->FUN_00bf2170(mpCity->GetVehicleSpecialty(), 0) <= civ->GetMoney();
    w->SetFlag(2, available && affordable);
    if (available && !affordable) w->SetShade(kRed); else w->SetShade(kWhite);
    {
        string16 text;
        cString header(0xc0152a6d, 0x64a7064, 0);
        const wchar_t* p = header.GetText();
        const wchar_t* e = p; while (*e) ++e;
        text.append(p, p + (e - p));
        if (civ->FUN_00bf2100(mpCity->GetVehicleSpecialty()) == 0)
        {
            APPEND_FILL_LINE();
        }
        else
        {
            const ResourceKey* key = civ->GetModelTypeKey(FUN_00c9e6d0(mpCity->GetVehicleSpecialty(), 0));
            if (key->instanceID == 0 && key->typeID == 0 && key->groupID == 0)
                APPEND_LINE(0x657690b);
            else if (!affordable)
                APPEND_LINE(0x671fb71);
        }
        uint32_t color;
        if (available && !affordable) color = kRed; else color = kWhite;
        SetTooltipText(w, text.mpBegin, color, 1);
    }

    // ---- vehicle button 1: also needs a target position ----
    w = mLayout.FindWindowByID(0x62d6908, true);
    w->SetFlag(1, true);
    available = civ->FUN_00bf2100(mpCity->GetVehicleSpecialty()) > 0 &&
                IsNonZero(civ->GetModelTypeKey(FUN_00c9e6d0(mpCity->GetVehicleSpecialty(), 1))) &&
                Vector3_NotEqual(mpCity->FUN_00fa0e00(), &gZeroVector);
    affordable = civ->FUN_00bf2170(mpCity->GetVehicleSpecialty(), 1) <= civ->GetMoney();
    w->SetFlag(2, available && affordable);
    if (available && !affordable) w->SetShade(kRed); else w->SetShade(kWhite);
    {
        string16 text;
        cString header(0xc0152a6d, 0x64a705d, 0);
        const wchar_t* p = header.GetText();
        const wchar_t* e = p; while (*e) ++e;
        text.append(p, p + (e - p));
        const Vector3* t = mpCity->FUN_00fa0e00();
        if (Vector3_Equal(*t, gZeroVector))
            APPEND_LINE(0x65767b3);
        else if (civ->FUN_00bf2100(mpCity->GetVehicleSpecialty()) == 0)
        {
            APPEND_FILL_LINE();
        }
        else
        {
            if (ResourceKey_Equal(civ->GetModelTypeKey(FUN_00c9e6d0(mpCity->GetVehicleSpecialty(), 1)), &zeroKey))
                APPEND_LINE(0x657690c);
            else if (!affordable)
                APPEND_LINE(0x671fb71);
        }
        uint32_t color;
        if (available && !affordable) color = kRed; else color = kWhite;
        SetTooltipText(w, text.mpBegin, color, 1);
    }

    // ---- vehicle button 2: air vehicle, needs CanBuildAirVehicles ----
    w = mLayout.FindWindowByID(0x62d690f, true);
    w->SetFlag(1, true);
    available = civ->FUN_00bf2100(mpCity->GetVehicleSpecialty()) > 0 &&
                     IsNonZero(civ->GetModelTypeKey(FUN_00c9e6d0(mpCity->GetVehicleSpecialty(), 2)));
    affordable = civ->FUN_00bf2170(mpCity->GetVehicleSpecialty(), 2) <= civ->GetMoney();
    w->SetFlag(2, available && affordable);
    if (available && !affordable) w->SetShade(kRed); else w->SetShade(kWhite);
    {
        string16 text;
        cString header(0xc0152a6d, 0x64a7057, 0);
        const wchar_t* p = header.GetText();
        const wchar_t* e = p; while (*e) ++e;
        text.append(p, p + (e - p));
        if (!cCivModeStrategy::Get()->CanBuildAirVehicles())
            APPEND_LINE(0x65767bb);
        else if (civ->FUN_00bf2100(mpCity->GetVehicleSpecialty()) == 0)
            APPEND_FILL_LINE();
        else if (ResourceKey_Equal(civ->GetModelTypeKey(FUN_00c9e6d0(mpCity->GetVehicleSpecialty(), 2)), &zeroKey))
            APPEND_LINE(0x657690d);
        else if (!affordable)
            APPEND_LINE(0x671fb71);
        uint32_t color;
        if (available && !affordable) color = kRed; else color = kWhite;
        SetTooltipText(w, text.mpBegin, color, 1);
    }

    UpdateMouseFocus(1);
}
