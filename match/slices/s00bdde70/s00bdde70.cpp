// Slice s00bdde70: SP::cCity::UpdateCityHallRollover (0x00bdde70), __thiscall ret 4.
//
// Fills the civ-stage city rollover (cSPUIRolloverCivCityHall) with this city's data:
//   * the allegiance bar: one entry per empire that owns part of the city, in the empire's color,
//     the city's own civilization selected;
//   * the title text (string 0x68c71fb / 0x653ea92 of table 0xdc351566) into property 0x2cf2f74;
//   * the income number's text color: green while the party is on (happiness above 50), red during
//     a riot (below 50), cyan otherwise, white when the income is not positive;
//   * five happiness bars (properties 0x4fe1aa0..) and five healthy-citizen bars (0x4fe38f0..);
//   * the relationship value toward the player (0x46adf86) and the housing count (0x199a7d2);
//   * the city name (0x2cf2f44), the vehicle specialty icon and the player-city button state.
// Every callee/global is a masked relocation; the stub classes below fix calling conventions,
// argument lists, vtable slots and field offsets only.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <string.h>

void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags, const char* file, int line);   // 0x00F473A0
void __cdecl operator delete[](void* p);                                   // 0x00F47380

enum
{
    kGameModeCiv   = 0x01654c04,
    kGameModeSpace = 0x01654c05,
};

struct WStr {  // eastl::basic_string<wchar_t> (begin, end, capacity-end)
    wchar_t *b, *e, *cap;
};

struct Variant {  // EA::Variant
    char data[0x10];
    unsigned short mFlags;
    unsigned short mTypeId;
    void Set(int type, int kind, const void* p, int size, int copy);   // 0x0093dd80
    void Destruct(int);                                                // 0x0093db80
};

struct cString {  // SP::cString
    char d[0x14];
    cString();                                                         // 0x006b5060
    ~cString();                                                        // 0x006b5240
    void Load(unsigned int tableId, unsigned int instanceId, int flag); // 0x006b54b0 (ret 0xc)
    const wchar_t* GetText();                                          // 0x006b55c0
};

struct IColorable {  // interface cast out of a window (typeID 0xf15f4bd)
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual void SetColor(unsigned int argb);                          // +0x28
};

struct IWindow {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual IColorable* Cast(unsigned int typeID);                     // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual IWindow* FindWindow(unsigned int id, int recurse);         // +0xf0
};

// rollover UI
struct cSPUIRolloverCivCityHall
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void Refresh();                                            // +0x20
    char pad04[0x78 - 0x4];
    IWindow* GetRootWindow();                                          // 0x00828100
    void ClearEntries();                                               // 0x00e2adb0
    void AddEntry(int slot, int count, unsigned int argb);             // 0x00e2c840 (ret 0xc)
    void SelectEntry(int slot);                                        // 0x00e2ab10 (ret 4)
    void SetProp(unsigned int id, Variant* v, int a, int b);           // 0x00828c30 (ret 0x10)
    void SetSpecialtyIcon(unsigned int id);                            // 0x00e2a7b0 (ret 4)
    void SetOwnerButtonState(bool b);                                  // 0x00e2a600 (ret 4)
};

struct cColor3c { unsigned int GetARGB(); };                           // 0x00b6f310 (on civ+0x3c)

struct cCivilization
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual int GetRelationshipEmpire(int empireId);                   // +0x4c
    char pad04[0x3c - 0x4];
    cColor3c mColor;                                                   // +0x3c
};

struct cGameNounManager
{
    cCivilization* FindCivilization(unsigned int empireId);            // 0x00b25f40 (ret 4)
    cCivilization* GetPlayerCivilization();                            // 0x00b25fb0
    int GetPlayerEmpireOrMinus1();                                     // 0x00b1f9d0 (does not use this)
};

struct cCivModeStrategy { void SetSelectedCity(void* city); };         // 0x00cfe780 (ret 4)
extern cCivModeStrategy* gCivModeStrategy;                             // 0x0169d3c8

struct ICityName
{
    virtual void v00();
    virtual const wchar_t* GetName();                                  // +0x4
};

struct RBNode { RBNode* mpRight; RBNode* mpLeft; RBNode* mpParent; int mColor; unsigned int mKey; int mValue; };
RBNode* RBTreeIncrement(RBNode* p);                                    // 0x00921580 (cdecl)

struct cCombatant { int GetDamageState(); };                           // 0x008e7f80
struct cCitizen { char pad[0x588]; cCombatant mCombatant; };           // +0x588

cGameNounManager* NounManager();                                       // 0x00b3d300
int GetCurrentGameMode();                                              // 0x00b5b800
float GetRelationshipValue(int otherEmpire, int myEmpire);             // 0x00d00d00 (cdecl, float in st0)
extern wchar_t gEmptyW[2];                                             // 0x01667bac

static const char kEastlFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

struct cCity
{
    char pad000[0x34];
    ICityName mName;                                                   // +0x34 (embedded, own vtable)
    char pad038[0x304 - 0x38];
    float mfHappiness;                                                 // +0x304
    char pad308[0x33c - 0x308];
    bool mbIsPlayerCity;                                               // +0x33c
    char pad33d[0x354 - 0x33d];
    cCitizen** mCitizensBegin;                                         // +0x354
    cCitizen** mCitizensEnd;                                           // +0x358
    char pad35c[0x540 - 0x35c];
    int mVehicleSpecialty;                                             // +0x540
    char pad544[0x590 - 0x544];
    cCivilization* mpCivilization;                                     // +0x590
    char pad594[0x5a4 - 0x594];
    RBNode* mAllegianceAnchorRight;                                    // +0x5a4 (map<uint,int> anchor)
    RBNode* mAllegianceBegin;                                          // +0x5a8
    char pad5ac[0x668 - 0x5ac];
    int mHappyCount;                                                   // +0x668
    int mUnhappyCount;                                                 // +0x66c
    char pad670[0x678 - 0x670];
    int mFinalIncome;                                                  // +0x678
    char pad67c[0x698 - 0x67c];
    bool mPartyOn;                                                     // +0x698
    char pad699[0x6c0 - 0x699];
    bool mRiotOn;                                                      // +0x6c0

    int GetHousingAmount();                                            // 0x00bd8960
    void UpdateCityHallRollover(cSPUIRolloverCivCityHall* pUI);
};

// Inline-constructed wstring from a zero-terminated buffer (eastl basic_string(const T*) inlined).
static __forceinline int CharStrlen(const wchar_t* p)
{
    const wchar_t* q = p;
    while (*q)
        ++q;
    return (int)(q - p);
}

static __forceinline void MakeWStr(WStr& s, const wchar_t* p)
{
    s.b = s.e = s.cap = 0;
    const wchar_t* pEnd = p + CharStrlen(p);
    int n = (int)(pEnd - p);
    unsigned int sz = n + 1;
    wchar_t* buf;
    if (sz > 1) {
        buf = (wchar_t*)operator new(sz * 2, "Simulator", 0, 0, kEastlFile, 0xd1);
        s.b = buf;
        s.cap = (wchar_t*)((char*)buf + sz * 2);
    } else {
        buf = gEmptyW;
        s.b = gEmptyW;
        s.cap = gEmptyW + 1;
    }
    s.e = buf;
    memcpy(buf, p, n * 2);
    s.e = buf + n;
    *s.e = 0;
}

static __forceinline void FreeWStr(WStr& s)
{
    if ((int)(((char*)s.cap - (char*)s.b) & ~1) > 2 && s.b)
        operator delete[](s.b);
}

static __forceinline void SetStringProp(cSPUIRolloverCivCityHall* pUI, unsigned int id, WStr& s)
{
    Variant v;
    v.mFlags = 0;
    v.mTypeId = 0;
    v.Set(0x13, 9, &s, 0x10, 1);
    pUI->SetProp(id, &v, 1, 0);
    if (v.mFlags & 4)
        v.Destruct(0);
}

static __forceinline void SetFloatProp(cSPUIRolloverCivCityHall* pUI, unsigned int id, float f)
{
    Variant v;
    v.mTypeId = 0xd;
    v.mFlags = 0;
    *(float*)v.data = f;
    pUI->SetProp(id, &v, 2, 0);
    if (v.mFlags & 4)
        v.Destruct(0);
}

// @ 0x00bdde70
void cCity::UpdateCityHallRollover(cSPUIRolloverCivCityHall* pUI)
{
    IWindow* pRoot = pUI->GetRootWindow();
    int slot = 0;
    pUI->ClearEntries();
    for (RBNode* pNode = mAllegianceBegin; pNode != (RBNode*)&mAllegianceAnchorRight; pNode = RBTreeIncrement(pNode)) {
        int count = pNode->mValue;
        unsigned int empireId = pNode->mKey;
        if (count > 0) {
            cCivilization* pCiv = NounManager()->FindCivilization(empireId);
            if (pCiv) {
                pUI->AddEntry(slot, count, pCiv->mColor.GetARGB());
                if (pCiv == mpCivilization)
                    pUI->SelectEntry(slot);
                ++slot;
            }
        }
    }

    int mode = GetCurrentGameMode();
    unsigned int titleId = mode == kGameModeSpace ? 0x68c71fb : 0x653ea92;
    gCivModeStrategy->SetSelectedCity(this);
    cString title;
    title.Load(0xdc351566, titleId, 0);
    WStr titleText;
    MakeWStr(titleText, title.GetText());
    SetStringProp(pUI, 0x2cf2f74, titleText);

    IWindow* pWindow = pRoot->FindWindow(0x2cf2f74, 1);
    IColorable* pIncomeText = pWindow ? pWindow->Cast(0xf15f4bd) : 0;

    int income = mFinalIncome;
    if (GetCurrentGameMode() != kGameModeSpace) {
        if (mPartyOn && mfHappiness > 50.0f)
            income = income * 2;
        if (mRiotOn && mfHappiness < 50.0f)
            income = income / 2;
    }
    if (income > 0) {
        if (mPartyOn && mfHappiness > 50.0f)
            pIncomeText->SetColor(0xff00ff00);
        else if (mRiotOn && mfHappiness < 50.0f)
            pIncomeText->SetColor(0xffff0000);
        else
            pIncomeText->SetColor(0xff00ffff);
    } else {
        pIncomeText->SetColor(0xffffffff);
    }

    int diff = mHappyCount - mUnhappyCount;
    for (int i = 0; i < 5; ++i) {
        float f = 0.0f;
        if (diff > 0) {
            if (i < diff)
                f = 100.0f;
        } else if (diff < 0) {
            if (i < -diff)
                f = 50.0f;
        }
        SetFloatProp(pUI, i + 0x4fe1aa0, f);
    }

    int healthy = 0;
    for (cCitizen** it = mCitizensBegin; it != mCitizensEnd; ++it) {
        if ((*it)->mCombatant.GetDamageState() == 0)
            ++healthy;
    }
    for (int i = 0; i < 5; ++i) {
        float f = 0.0f;
        if (i < healthy)
            f = 100.0f;
        SetFloatProp(pUI, i + 0x4fe38f0, f);
    }

    cCivilization* pCiv = mpCivilization;
    float relation;
    if (pCiv == NounManager()->GetPlayerCivilization()) {
        relation = 50.0f;
    } else {
        int myEmpire = NounManager()->GetPlayerEmpireOrMinus1();
        relation = GetRelationshipValue(pCiv->GetRelationshipEmpire(myEmpire), myEmpire);
    }
    SetFloatProp(pUI, 0x46adf86, relation);

    {
        Variant v;
        v.mTypeId = 9;
        v.mFlags = 0;
        *(int*)v.data = GetHousingAmount();
        pUI->SetProp(0x199a7d2, &v, 1, 0);
        if (v.mFlags & 4)
            v.Destruct(0);
    }

    {
        WStr nameText;
        MakeWStr(nameText, mName.GetName());
        SetStringProp(pUI, 0x2cf2f44, nameText);
        FreeWStr(nameText);
    }

    if (GetCurrentGameMode() == kGameModeCiv) {
        unsigned int icon;
        switch (mVehicleSpecialty) {
        case 0: icon = 0x2cf2f38; break;
        case 1: icon = 0x2cf2f34; break;
        case 2: icon = 0x2cf2f30; break;
        default: icon = 0; break;
        }
        pUI->SetSpecialtyIcon(icon);
    } else if (GetCurrentGameMode() == kGameModeSpace) {
        pUI->SetSpecialtyIcon(0);
    }

    pUI->SetOwnerButtonState(!mbIsPlayerCity);
    pUI->Refresh();
    FreeWStr(titleText);
}
