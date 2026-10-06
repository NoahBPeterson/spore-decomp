// Slice s0106ba00 (batch op2_big) — 0x0106ba00, 3880 bytes.
//
// SP::cSPUISpace::UpdatePlanetRollover(cPlanet* pPlanet)   (__thiscall, ret 4)
//
// The name comes from the dev PDB (?UpdatePlanetRollover@cSPUISpace@SP@@IAEXPAVcPlanet@2@@Z).
// Retail member offsets differ from the dev layout, so cSPUISpace below is declared with
// the retail offsets this function uses; member names follow the dev PDB where the role
// matches (mRolloverPlanet, mPlanetRolloverFrame, ...).  Callees without a recovered name
// keep their FUN_ address names.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (SSE scalar float copies and cvtsi2ss, x87
// for float arguments; AutoRefCount locals without an EH frame -> no /EHsc).

#include "types.h"

#pragma pack(push, 8)

struct Vector3 { float x, y, z; };

namespace Math {
struct Rectangle {
    float x1, y1, x2, y2;
    Rectangle() {}
    Rectangle(float l, float t, float r, float b) : x1(l), y1(t), x2(r), y2(b) {}
    void Union(const Rectangle& a, const Rectangle& b);              // 0x00805530
};
struct Point {
    float x, y;
    Point() {}
    Point(float ax, float ay) : x(ax), y(ay) {}
};
struct ColorRGB { float r, g, b; };
struct ColorRGBA {
    float r, g, b, a;
    ColorRGBA(const ColorRGB& c, float alpha) : r(c.r), g(c.g), b(c.b), a(alpha) {}
};
}

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey() {}
    ResourceKey(const ResourceKey& k) : instanceID(k.instanceID), typeID(k.typeID), groupID(k.groupID) {}
};

namespace EA {
template <class T> class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T** AsPPTypeParam();                                             // 0x00A16F40 (shared instance)
    // operator=(T*) with a null argument, inlined at each site
    __forceinline void Clear()
    {
        if (mpObject != 0) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
};
}

struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    bool empty() const { return mpBegin == mpEnd; }
    const wchar_t* c_str() const { return mpBegin; }
};

namespace EA { namespace UTFWin {
class IWindow {
public:
    virtual int AddRef();                                            // +0x0
    virtual int Release();                                           // +0x4
    virtual void _v08(); virtual void _v0c();
    virtual IWindow* GetParent();                                    // +0x10
    virtual void _v14(); virtual void _v18(); virtual void _v1c(); virtual void _v20();
    virtual void _v24(); virtual void _v28(); virtual void _v2c(); virtual void _v30();
    virtual const Math::Rectangle& GetArea();                        // +0x34
    virtual void _v38(); virtual void _v3c(); virtual void _v40(); virtual void _v44();
    virtual void _v48(); virtual void _v4c(); virtual void _v50(); virtual void _v54();
    virtual void _v58();
    virtual void SetShadeColor(uint32_t color);                      // +0x5c
    virtual void SetArea(const Math::Rectangle& area);               // +0x60
    virtual void SetLocation(float x, float y);                      // +0x64
    virtual void _v68(); virtual void _v6c(); virtual void _v70(); virtual void _v74();
    virtual void _v78();
    virtual void SetFlag(int flag, bool value);                      // +0x7c
    virtual void SetCaption(const wchar_t* caption);                 // +0x80
    virtual void _v84(); virtual void _v88(); virtual void _v8c(); virtual void _v90();
    virtual void _v94(); virtual void _v98(); virtual void _v9c(); virtual void _va0();
    virtual void _va4(); virtual void _va8(); virtual void _vac(); virtual void _vb0();
    virtual void _vb4(); virtual void _vb8(); virtual void _vbc(); virtual void _vc0();
    virtual void _vc4(); virtual void _vc8(); virtual void _vcc(); virtual void _vd0();
    virtual void _vd4();
    virtual void AddWindow(IWindow* pWindow);                        // +0xd8
    virtual void RemoveWindow(IWindow* pWindow);                     // +0xdc
    virtual void _ve0(); virtual void _ve4(); virtual void _ve8(); virtual void _vec();
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive);    // +0xf0
};
} }
using EA::UTFWin::IWindow;

class IWindowManager {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4c();
    virtual void _v50(); virtual void _v54(); virtual void _v58(); virtual void _v5c();
    virtual void _v60(); virtual void _v64(); virtual void _v68(); virtual void _v6c();
    virtual void _v70(); virtual void _v74(); virtual void _v78(); virtual void _v7c();
    virtual void _v80();
    virtual void* GetModalWindow();                                  // +0x84
};

namespace App {
class PropertyList {
public:
    virtual int AddRef();
    virtual int Release();
};
class IPropertyManager {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppList);  // +0x2c
};
}

struct Transform;
namespace EA { namespace Swarm {
class cIVisualEffect {
public:
    virtual int AddRef();                                            // +0x0
    virtual int Release();                                           // +0x4
    virtual bool Start(int flags);                                   // +0x8
    virtual bool Stop(int flags);                                    // +0xc
    virtual void _v10();
    virtual void SetTransform(const ::Transform& xform);        // +0x14
};
class IEffectsManager {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28();
    virtual bool CreateVisualEffect(uint32_t id, int flags, cIVisualEffect** ppEffect);  // +0x2c
};
} }

struct Transform {
    uint16_t mFlags;                            // +0x0
    uint16_t mnChangeCount;                     // +0x2
    uint32_t pad04[3];
    float mfScale;                              // +0x10
    uint32_t pad14[(0x40 - 0x14) / 4];
    Transform();                                                     // 0x00434040
    void SetOffset(const Vector3& offset);                           // 0x00571D40
    void SetScale(float scale) { mfScale = scale; mnChangeCount++; }
};

namespace EA { namespace Locale {
    int SetNumberString(int64_t value, wchar_t* pBuffer, int bufferSize);  // 0x00881AE0
} }

namespace SP {

class cString {   // retail size 0x14
public:
    uint32_t pad[5];
    const wchar_t* GetText();                                        // 0x006B55C0
};

class cEmpire {
public:
    uint32_t pad00[0x50 / 4];
    uint32_t mFlags;                            // +0x50
    uint32_t pad54[(0x84 - 0x54) / 4];
    uint32_t mEmpireID;                         // +0x84
    Math::ColorRGB GetColor();                                       // 0x00C32CD0
    int GetWeaponryLevel();                                          // 0x00C317A0
    bool FUN_00c308b0();                                             // 0x00C308B0
};

class cPlanetRecord {
public:
    bool FUN_00b8d970();                                             // 0x00B8D970
    void GetTypeID(uint32_t* pOut);                                  // 0x00B8DD60
    const uint32_t* GetPropListID();                                 // 0x00B8DAD0
    bool HasTool(uint32_t toolID);                                   // 0x00B8E040
};

struct cCityList {
    uint32_t pad00[0x3c / 4];
    void** mpBegin;                             // +0x3c
    void** mpEnd;                               // +0x40
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};

struct cCityVector {
    cCityList** mpBegin;
    cCityList** mpEnd;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};

class cPlanet {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28();
    virtual const Vector3& GetPosition();                            // +0x2c
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4c();
    virtual void _v50(); virtual void _v54();
    virtual bool IsPlayerOwned();                                    // +0x58
    virtual void _v5c(); virtual void _v60(); virtual void _v64(); virtual void _v68();
    virtual void _v6c(); virtual void _v70(); virtual void _v74(); virtual void _v78();
    virtual void _v7c(); virtual void _v80(); virtual void _v84(); virtual void _v88();
    virtual void _v8c(); virtual void _v90(); virtual void _v94(); virtual void _v98();
    virtual void _v9c(); virtual void _va0(); virtual void _va4(); virtual void _va8();
    virtual void _vac(); virtual void _vb0(); virtual void _vb4(); virtual void _vb8();
    virtual int AddRef();                                            // +0xbc
    virtual int Release();                                           // +0xc0

    uint32_t pad04[(0x13c - 0x4) / 4];
    cPlanetRecord* mpPlanetRecord;              // +0x13c

    const string16& GetName();                                       // 0x00C707E0
    int FUN_00c70880();                                              // 0x00C70880
    int GetNumCities();                                              // 0x00C70E00
    int FUN_00c70860();                                              // 0x00C70860
    bool IsOwnedBy(cEmpire* pEmpire, int a);                         // 0x00C70B20
    cEmpire* GetEmpire();                                            // 0x00C71E30
    float GetRadius();                                               // 0x00C71470
    const cCityVector& GetCities();                                  // 0x00C71000
};

class cPlanetRef : public EA::AutoRefCount<cPlanet> {
public:
    cPlanetRef& operator=(cPlanet* p);                               // 0x00C70110 (out of line)
};

class cWindowRef : public EA::AutoRefCount<IWindow> {
public:
    cWindowRef& operator=(IWindow* p);                               // 0x00B5F950 (shared out-of-line instance)
};

class cSPUIAnimator {
public:
    virtual int AddRef();
    virtual int Release();
    void Shutdown(bool b);                                           // 0x00E06940
};

class cSpaceTokenTranslator {
public:
    uint32_t pad00[3];
    cPlanetRecord* mpPlanetRecord;              // +0xc
};
extern cSpaceTokenTranslator* gpSpaceTokenTranslator;                // 0x016E0D08

struct cGameTimeManager {
    uint32_t pad00[0x48 / 4];
    uint32_t mFlags;                            // +0x48
};

struct cModeState {
    uint32_t pad00[0x2c / 4];
    int mState;                                 // +0x2c
};

class cGameModeA { public: bool FUN_00ae9390(); };                   // 0x00AE9390
class cGameModeB { public: bool FUN_00e18c70(int a); };              // 0x00E18C70
class cGameModeC { public: bool FUN_00b5ca60(); };                   // 0x00B5CA60

cGameModeA* FUN_00b3d4a0();                                          // 0x00B3D4A0
cGameModeB* FUN_00b3d3f0();                                          // 0x00B3D3F0
cGameModeC* FUN_00b3d230();                                          // 0x00B3D230
cModeState* FUN_00b3d4d0();                                          // 0x00B3D4D0
IWindowManager* WindowManager();                                     // 0x0067CAA0
App::IPropertyManager* PropertyManager();                            // 0x0067DE30
EA::Swarm::IEffectsManager* EffectsManager();                        // 0x0067DDD0
cGameTimeManager* GameTimeManager();                                 // 0x00B3D380

bool GetPropertyAsUint32(App::PropertyList* pList, uint32_t id, uint32_t* pOut);  // 0x004AF210
uint32_t ColorRGBAToU32(const Math::ColorRGBA& color);                             // 0x004580C0
void SetImageFromKey(IWindow* pWindow, const ResourceKey& key);                    // 0x00E2F5C0
const ResourceKey& GetPlanetImageKey(cPlanetRecord* pRecord);                      // 0x00E2EBA0
void SetEmpireIcon(uint32_t empireID, IWindow* pWindow);                           // 0x00E2E6E0
int GetNumSpiceColonies(cPlanetRecord* pRecord, int a);                            // 0x00C705C0
void WorldToScreen(const Vector3& pos, float* pX, float* pY);                      // 0x00E50750
float GetScreenRadius(const Vector3& pos, float radius);                           // 0x01066390

struct cMeterHolder {
    uint32_t pad[0x20c / 4];
    class cMeter {
    public:
        virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
        virtual int GetMaxValue();                                   // +0x10
        virtual void SetValue(int value);                            // +0x14
    } mMeter;                                   // +0x20c
};
cMeterHolder* FUN_00deced0(IWindow* pWindow);                         // 0x00DECED0

class cSPSpaceColonyTuning { public: int GetMaxSpicePerColony(); };                 // 0x01029900
class cSPSpaceEconomyTuning { public: float GetSpiceProductionStorageMultiplier(); }; // 0x0102FB20
cSPSpaceColonyTuning* FUN_01029790();                                // 0x01029790
cSPSpaceEconomyTuning* FUN_0102f810();                               // 0x0102F810
extern uint32_t k_placespicestorage;                                 // 0x016E2524

extern ResourceKey g_kHomePlanetImage;                               // 0x015B9124
extern ResourceKey g_kOwnedPlanetImage;                              // 0x015B9118

class cSPLivingUniverse {
public:
    static cEmpire* GetPlayerEmpire();                               // 0x01021300
    static cPlanetRecord* GetPlayerHomePlanet();                     // 0x01021370
    static cPlanetRecord* GetActivePlanetRecord();                   // 0x010212A0
};

namespace SPUIHelpers {
    void DestroyRolloverFrame(IWindow* pFrame);                      // 0x008074A0
    IWindow* CreateRolloverFrame(const wchar_t* name, float x, float y, float w, float h,
                                 IWindow** ppContainer, int a, int b, float radius, uint32_t id);  // 0x008093B0
    void UpdateRolloverFrame(IWindow* pFrame, float x, float y, bool b, float radius);              // 0x00809370
    Math::Rectangle GetWindowBounds(IWindow* pWindow);                                             // 0x00805FE0
}

class cSPUISpace {
public:
    uint32_t pad000[0x300 / 4];
    EA::AutoRefCount<EA::Swarm::cIVisualEffect> mPlanetRolloverEffect;  // +0x300
    uint32_t pad304[(0x3b0 - 0x304) / 4];
    cString mDominantSpecies;                   // +0x3b0
    uint32_t pad3c4[(0x3d8 - 0x3c4) / 4];
    cString mAddPlants;                         // +0x3d8
    cString mImproveTScore;                     // +0x3ec
    uint32_t pad400[(0x4c8 - 0x400) / 4];
    cString mSentient;                          // +0x4c8
    uint32_t pad4dc[(0x584 - 0x4dc) / 4];
    cPlanetRef mRolloverPlanet;                 // +0x584
    uint32_t pad588;
    cWindowRef mPlanetRolloverFrame;            // +0x58c
    uint32_t pad590[2];
    EA::AutoRefCount<IWindow> mMissionRolloverRoot;   // +0x598
    uint32_t pad59c;
    EA::AutoRefCount<IWindow> mPlanetRolloverRoot;    // +0x5a0
    uint32_t pad5a4[4];
    EA::AutoRefCount<cSPUIAnimator> mpAnimator;       // +0x5b4

    int UpdateCaptureBarsVisibility(cPlanetRecord* pRecord);                           // 0x010673F0
    IWindow* UpdateMissionRollover(int a, cPlanet* pPlanet, float x, float y);         // 0x0106A0A0
    void FUN_01067720(cPlanetRecord* pRecord, Math::Point pos, bool b);               // 0x01067720
    static ResourceKey GetDominantSpeciesThumbnailKey(cPlanetRecord* pRecord);         // 0x01065F00
    void UpdatePlanetRollover(cPlanet* pPlanet);
};

}  // namespace SP

#pragma pack(pop)

using namespace SP;

template <class T> static inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }

static __forceinline void DetachFromParent(IWindow* pWindow)
{
    if (pWindow->GetParent())
        pWindow->GetParent()->RemoveWindow(pWindow);
}

void cSPUISpace::UpdatePlanetRollover(cPlanet* pPlanet)
{
    bool bShowRollover = false;

    int modeState;
    if (FUN_00b3d4a0()->FUN_00ae9390() ||
        FUN_00b3d3f0()->FUN_00e18c70(0) ||
        FUN_00b3d230()->FUN_00b5ca60() ||
        (modeState = FUN_00b3d4d0()->mState) == 1 || modeState == 2 ||
        WindowManager()->GetModalWindow() != 0)
    {
        mPlanetRolloverRoot->SetFlag(1, false);
        DetachFromParent(mPlanetRolloverRoot);
        DetachFromParent(mMissionRolloverRoot);
        if (mpAnimator)
        {
            mpAnimator->Shutdown(true);
            mpAnimator.Clear();
        }
        SPUIHelpers::DestroyRolloverFrame(mPlanetRolloverFrame);
        mPlanetRolloverFrame.Clear();
        mRolloverPlanet.Clear();
        return;
    }

    cPlanetRecord* pRecord = pPlanet ? pPlanet->mpPlanetRecord : 0;
    int numCaptureBars = UpdateCaptureBarsVisibility(pRecord);
    bool bTransitioning = FUN_00b3d230()->FUN_00b5ca60();
    int row;

    if (!bTransitioning)
    {
        if (!pPlanet)
            goto noPlanet;

        gpSpaceTokenTranslator->mpPlanetRecord = pPlanet->mpPlanetRecord;
        row = 0;

        IWindow* pWindow = mPlanetRolloverRoot->FindWindowByID(0x1c23501, true);
        if (pWindow)
        {
            bool bHasName = !pPlanet->GetName().empty();
            pWindow->SetFlag(1, bHasName);
            if (bHasName)
            {
                pWindow->SetCaption(pPlanet->GetName().c_str());
                bShowRollover = true;
            }
        }

        pWindow = mPlanetRolloverRoot->FindWindowByID(0x37c2c94, true);
        if (pWindow)
        {
            bool bSentient;
            if (pPlanet->FUN_00c70880() == 1 || pPlanet->FUN_00c70880() == 0 ||
                pPlanet->mpPlanetRecord->FUN_00b8d970())
                bSentient = false;
            else
                bSentient = true;
            pWindow->SetFlag(1, bSentient);
            if (bSentient)
            {
                pWindow->SetCaption(mSentient.GetText());
                bShowRollover = true;
            }
        }

        cEmpire* pEmpire = pPlanet->GetEmpire();
        cEmpire* pPlayerEmpire = cSPLivingUniverse::GetPlayerEmpire();

        IWindow* pWeaponWindow = mPlanetRolloverRoot->FindWindowByID(0x5e62810, true);
        if (pWeaponWindow)
            pWeaponWindow->SetFlag(1, false);

        IWindow* pSwatch = mPlanetRolloverRoot->FindWindowByID(0x4bdc316, true);
        if (pEmpire)
        {
            pSwatch->SetShadeColor(ColorRGBAToU32(Math::ColorRGBA(pEmpire->GetColor(), 1.0f)));
            if (pWeaponWindow && !((pEmpire->mFlags >> 6) & 1) && !pEmpire->FUN_00c308b0())
            {
                pWeaponWindow->SetFlag(1, true);
                cMeterHolder::cMeter& meter = FUN_00deced0(pWeaponWindow)->mMeter;
                int maxLevel = meter.GetMaxValue() - 1;
                int level = pEmpire->GetWeaponryLevel() + 1;
                meter.SetValue(Min(level, maxLevel));
            }
        }
        else
        {
            pSwatch->SetShadeColor(0x8c79898d);
        }

        IWindow* pCityWindow = mPlanetRolloverRoot->FindWindowByID(0x1c23510, true);
        if (pCityWindow)
        {
            pCityWindow->SetFlag(1, false);
            IWindow* pPlanetImage = mPlanetRolloverRoot->FindWindowByID(0x1c23512, true);
            bool bHasCities = pPlanet->GetNumCities() > 0;
            pPlanetImage->SetFlag(1, bHasCities);
            if (pPlanet->mpPlanetRecord == cSPLivingUniverse::GetPlayerHomePlanet())
                SetImageFromKey(pPlanetImage, g_kHomePlanetImage);
            else if (pPlanet->IsOwnedBy(cSPLivingUniverse::GetPlayerEmpire(), 0))
                SetImageFromKey(pPlanetImage, g_kOwnedPlanetImage);
            else if (bHasCities)
                SetImageFromKey(pPlanetImage, GetPlanetImageKey(pPlanet->mpPlanetRecord));

            IWindow* pSpeciesImage = mPlanetRolloverRoot->FindWindowByID(0x1c23511, true);
            pSpeciesImage->SetFlag(1, false);
            IWindow* pEmpireIcon = mPlanetRolloverRoot->FindWindowByID(0x1c23513, true);
            pEmpireIcon->SetFlag(1, false);
            mPlanetRolloverRoot->FindWindowByID(0x1c23515, true)->SetFlag(1, false);
            IWindow* pSpeciesText = mPlanetRolloverRoot->FindWindowByID(0x1c23514, true);
            pSpeciesText->SetFlag(1, false);

            if (pPlanet->GetNumCities() > 1 && pPlanet->FUN_00c70860() != 0)
            {
                pCityWindow->SetFlag(1, true);
                pSpeciesImage->SetFlag(1, true);
                row = 1;
                SetImageFromKey(pSpeciesImage, GetDominantSpeciesThumbnailKey(pPlanet->mpPlanetRecord));
                if (pPlanet->GetNumCities() == 5 && pEmpire != pPlayerEmpire)
                    SetEmpireIcon(pEmpire->mEmpireID, pEmpireIcon);
                pSpeciesText->SetFlag(1, true);
                pSpeciesText->SetCaption(mDominantSpecies.GetText());
                bShowRollover = true;
            }
        }

        IWindow* pSpiceWindow = mPlanetRolloverRoot->FindWindowByID(0x1c23502, true);
        if (pSpiceWindow)
        {
            uint32_t typeID;
            pRecord->GetTypeID(&typeID);
            if (pPlanet->GetNumCities() == 0)
            {
                pSpiceWindow->SetFlag(1, false);
            }
            else if (typeID == 0x6334d0ad || typeID == 0x4f3d572f)
            {
                pSpiceWindow->SetFlag(1, false);
            }
            else
            {
                pSpiceWindow->SetLocation(pSpiceWindow->GetArea().x1, (float)row * 25.0f + 26.0f);
                pSpiceWindow->SetFlag(1, true);
                row++;

                EA::AutoRefCount<App::PropertyList> pPropList;
                uint32_t color = 0xffffffff;
                App::IPropertyManager* pPropManager = PropertyManager();
                pPropManager->GetPropertyList(*pRecord->GetPropListID(), 0x34d97fa, pPropList.AsPPTypeParam());
                GetPropertyAsUint32(pPropList, 0x58cbb75, &color);
                IWindow* pIcon = mPlanetRolloverRoot->FindWindowByID(0x63c0918, true);
                if (pIcon)
                    pIcon->SetShadeColor(color | 0xff000000);

                IWindow* pSpiceText = mPlanetRolloverRoot->FindWindowByID(0x1c23503, true);
                if (pSpiceText)
                {
                    IWindow* pStorage = mPlanetRolloverRoot->FindWindowByID(0x67cff08, true);
                    if (pStorage)
                        pStorage->SetFlag(1, false);

                    int numSpice = GetNumSpiceColonies(pPlanet->mpPlanetRecord, 0);
                    if (numSpice == 0 && pEmpire != pPlayerEmpire)
                    {
                        if (pPlanet->GetNumCities() > 1)
                            pSpiceText->SetCaption(mImproveTScore.GetText());
                        else
                            pSpiceText->SetCaption(mAddPlants.GetText());
                    }
                    else
                    {
                        wchar_t buffer[32];
                        buffer[0] = 0;
                        EA::Locale::SetNumberString(numSpice, buffer, 0x28);
                        pSpiceText->SetCaption(buffer);
                        if (pStorage && pPlanet->IsPlayerOwned())
                        {
                            uint32_t numBuildings = 0;
                            const cCityVector& cities = pPlanet->GetCities();
                            for (int i = 0; i < (int)cities.size(); i++)
                                numBuildings += cities.mpBegin[i]->size();
                            if (numBuildings != 0)
                            {
                                float maxSpice = (float)FUN_01029790()->GetMaxSpicePerColony();
                                float capacity;
                                if (pPlanet->mpPlanetRecord->HasTool(k_placespicestorage))
                                    capacity = FUN_0102f810()->GetSpiceProductionStorageMultiplier() * maxSpice;
                                else
                                    capacity = maxSpice;
                                buffer[0] = 0;
                                EA::Locale::SetNumberString((int64_t)(capacity * (float)numBuildings), buffer, 0x28);
                                mPlanetRolloverRoot->FindWindowByID(0x67cf148, true)->SetCaption(buffer);
                                pStorage->SetFlag(1, true);
                            }
                        }
                    }
                }
            }
        }

        if (mPlanetRolloverRoot)
        {
            float screenX, screenY;
            WorldToScreen(pPlanet->GetPosition(), &screenX, &screenY);
            screenY -= 15.0f;
            float screenRadius = GetScreenRadius(pPlanet->GetPosition(), pPlanet->GetRadius());
            if (mRolloverPlanet == pPlanet)
            {
                SPUIHelpers::UpdateRolloverFrame(mPlanetRolloverFrame, screenX, screenY, true, screenRadius);
            }
            else
            {
                if (mPlanetRolloverFrame)
                {
                    DetachFromParent(mPlanetRolloverRoot);
                    DetachFromParent(mMissionRolloverRoot);
                    SPUIHelpers::DestroyRolloverFrame(mPlanetRolloverFrame);
                    mPlanetRolloverFrame.Clear();
                }
                float height = (float)(row + numCaptureBars) * 25.0f + 26.0f;
                const Math::Rectangle& area = mPlanetRolloverRoot->GetArea();
                Math::Rectangle rect(area.x1, area.y1, area.x2, area.y1 + height);
                mPlanetRolloverRoot->SetArea(rect);
                mPlanetRolloverRoot->SetLocation(0.0f, 0.0f);
                IWindow* pMission = UpdateMissionRollover(0, pPlanet, rect.x1, rect.y1);
                if (pMission)
                {
                    rect.Union(rect, pMission->GetArea());
                    const Math::Rectangle& missionArea = pMission->GetArea();
                    mPlanetRolloverRoot->SetLocation(0.0f, missionArea.y2 - missionArea.y1);
                    pMission->SetLocation(0.0f, 0.0f);
                }
                EA::AutoRefCount<IWindow> pContainer;
                mPlanetRolloverFrame = SPUIHelpers::CreateRolloverFrame(
                    L"RolloverFrameGeneric", screenX, screenY, rect.x2 - rect.x1, rect.y2 - rect.y1,
                    pContainer.AsPPTypeParam(), 1, 1, screenRadius, 0xe9f70df9);
                DetachFromParent(mPlanetRolloverRoot);
                pContainer->AddWindow(mPlanetRolloverRoot);
                if (pMission)
                {
                    DetachFromParent(pMission);
                    pContainer->AddWindow(pMission);
                }
            }
        }

        Math::Rectangle bounds = SPUIHelpers::GetWindowBounds(mPlanetRolloverRoot);
        FUN_01067720(pRecord, Math::Point(bounds.x1 + 90.0f, bounds.y1 + ((float)row * 25.0f + 26.0f - 4.0f)), true);
    }

    if (pPlanet && !bTransitioning && pPlanet->mpPlanetRecord != cSPLivingUniverse::GetActivePlanetRecord())
    {
        if (!mPlanetRolloverEffect)
        {
            EA::Swarm::IEffectsManager* pEffects = EffectsManager();
            if (pEffects->CreateVisualEffect(0xae40751c, 0, mPlanetRolloverEffect.AsPPTypeParam()))
                mPlanetRolloverEffect->Start(0);
            if (!mPlanetRolloverEffect)
                goto done;
        }
        Transform xform;
        xform.SetOffset(pPlanet->GetPosition());
        xform.SetScale(pPlanet->GetRadius());
        mPlanetRolloverEffect->SetTransform(xform);
        goto done;
    }

noPlanet:
    if (mPlanetRolloverEffect)
    {
        mPlanetRolloverEffect->Stop((GameTimeManager()->mFlags >> 1) & 1);
        mPlanetRolloverEffect.Clear();
    }

done:
    if (!bShowRollover && mRolloverPlanet && mPlanetRolloverFrame)
    {
        DetachFromParent(mPlanetRolloverRoot);
        DetachFromParent(mMissionRolloverRoot);
        SPUIHelpers::DestroyRolloverFrame(mPlanetRolloverFrame);
        mPlanetRolloverFrame.Clear();
        mRolloverPlanet.Clear();
    }
    mRolloverPlanet = pPlanet;
    mPlanetRolloverRoot->SetFlag(1, bShowRollover || mRolloverPlanet);
}
