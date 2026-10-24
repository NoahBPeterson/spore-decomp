// Slice s010691e0 (batch gold7) -- SP::cSPUISpace star-rollover helpers.
//
//   0x010691e0  SP::cSPUISpace::UpdateStarRollover(cStarRecord* pStar)
//   0x010697b0  SP::cSPUISpace::FUN_010697b0(cCivData* pCiv)      (ret 4)
//   0x01069aa0  SP::cSPUISpace::FUN_01069aa0()                    (thiscall)
//
// Complete, behaviourally faithful rewrites (not byte-exact: the compiler's instruction
// scheduling / basic-block layout differs; sizes 1497/632/1442 vs 1486/750/1522).  Retail
// member offsets differ from the 2008 dev PDB (the whole cSPUISpace block is shifted); the
// stub class below uses the retail offsets read off the disassembly and keeps the dev-PDB
// member names where the role matches.  Shared vocabulary with the neighbouring slices
// s0106cc70 (UpdateTravelLine) and s0106ba00 (UpdatePlanetRollover).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (SSE scalar float copies + cvtsi2ss, x87 for
// float arguments; AutoRefCount / vector locals without an EH frame -> no /EHsc).

#include "types.h"

#pragma pack(push, 8)

struct Vector3 { float x, y, z; Vector3() {} Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {} };

namespace Math {
struct Rectangle {
    float x1, y1, x2, y2;
    Rectangle() {}
    Rectangle(float l, float t, float r, float b) : x1(l), y1(t), x2(r), y2(b) {}
    void Union(const Rectangle& a, const Rectangle& b);              // 0x00805530
};
struct Point { float x, y; Point() {} Point(float ax, float ay) : x(ax), y(ay) {} };
}

struct ResourceKey { uint32_t instanceID, typeID, groupID; };

// The visual effect "Transform" local used by FUN_010697b0 (retail layout read off the
// disassembly: flags / change-count, an offset vector, a scale and a 3x3 matrix).
struct Matrix3f {
    float m00, m01, m02;
    float m10, m11, m12;
    float m20, m21, m22;
};
struct EffectTransform {
    uint16_t mFlags;                            // +0x00
    uint16_t mnChangeCount;                     // +0x02
    Vector3  mOffset;                           // +0x04
    uint32_t pad10;                             // +0x10
    float    mfScale;                           // +0x14
    Matrix3f mMatrix;                           // +0x18
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
    virtual void _v24(); virtual bool _v28(); virtual void _v2c(); virtual void _v30();
    virtual const Math::Rectangle& GetArea();                        // +0x34
    virtual const Math::Rectangle& GetRealArea();                    // +0x38
    virtual void _v3c(); virtual void _v40(); virtual void _v44();
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

// EA::UTFWinControls::IWinText -- the star rollover text window interface.
class IWinText {
public:
    virtual int AddRef();                                            // +0x0
    virtual int Release();                                           // +0x4
    virtual void _v08(); virtual void _v0c(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1c(); virtual void _v20(); virtual void _v24();
    virtual void _v28(); virtual void _v2c(); virtual void _v30(); virtual void _v34();
    virtual void _v38(); virtual void _v3c(); virtual void _v40(); virtual void _v44();
    virtual void _v48(); virtual void _v4c(); virtual void _v50(); virtual void _v54();
    virtual void _v58(); virtual void _v5c(); virtual void _v60(); virtual void _v64();
    virtual void _v68(); virtual void _v6c(); virtual void _v70(); virtual void _v74();
    virtual void _v78();
    virtual void SetFlag(int flag, bool value);                      // +0x7c
    virtual void SetCaption(const wchar_t* caption);                 // +0x80
};

// Windows that expose a "set layout location" (used by FindWindowByID + SetLocation pair in
// the sibling slices); the star rollover uses plain IWindow for every one of them, but keeps
// this as a base so the vtable slot indices line up.
typedef IWindow IWindowEx;

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

namespace SP {

class cString {   // retail size 0x14
public:
    wchar_t* mpBegin;
    uint32_t pad[4];
    const wchar_t* GetText();                                        // 0x006B55C0
    const wchar_t* c_str() const { return mpBegin; }
};

class cCivData;                                                      // size 0x44

// cCivData::GetCities() returns the city list; retail city objects carry their runtime state
// (mState at +0x28, etc.).  Only the pieces this slice touches are named.
class cCityRuntime {
public:
    uint32_t pad00[0x28 / 4];
    int mState;                                 // +0x28
    bool FUN_00b8d970();                         // 0x00B8D970
    int  FUN_00b8dab0();                         // 0x00B8DAB0 (city type)
};

class cCityList {
public:
    uint32_t pad00[0x3c / 4];
    cCityRuntime** mpBegin;                      // +0x3c
    cCityRuntime** mpEnd;                        // +0x40
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};

class cCivData {
public:
    cCityList* GetCities();                                          // 0x005C65E0 (retail stub name)
};

// A minimal cStarRecord view: GetName() returns the planet name string.
class cStarRecord {
public:
    cString* GetName();                                              // 0x00C707E0
};

// The space-gfx singleton (0x00b3d470): +0x30 window slot, +0x38 selected id, +0x94
// effects manager.
class cSpaceGfx {
public:
    class cSlot {
    public:
        virtual int AddRef();                                        // +0x0
        virtual int Release();                                       // +0x4
        virtual void Use(int a);                                     // +0x08 (Show/SetEnabled)
        virtual void Show(bool b);                                   // +0x0c
        virtual bool IsVisible();                                    // +0x10
        virtual void SetTransform(const EffectTransform& t);         // +0x14
        virtual void _v18(); virtual void _v1c(); virtual void _v20(); virtual void _v24();
        virtual void _v28(); virtual void _v2c(); virtual void _v30(); virtual void _v34();
        virtual void _v38(); virtual void _v3c(); virtual void _v40();
        virtual void SetParams(int a, const void* data, int count);  // +0x44
    };
    uint32_t pad00[0x30 / 4];
    EA::AutoRefCount<cSlot> mSlot30;             // +0x30
    uint32_t pad34;
    cCivData* mSelectedID;                       // +0x38
    uint32_t pad3c[(0x94 - 0x3c) / 4];
    class cEffectsMgr {
    public:
        virtual void _v00(); virtual void _v04();
        virtual bool CreateVisualEffect(uint32_t id, int flags, void** out);  // +0x08
    }* mpEffectsMgr94;                           // +0x94
};
cSpaceGfx* GetSpaceGfx();                                            // 0x00B3D470 (FUN_00b3d470)

class cPlayerInventory {
public:
    class cCivList {
    public:
        virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
        virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
        virtual void _v20(); virtual void _v24(); virtual void _v28();
        virtual const Vector3& GetPosition();                        // +0x2c
    };
    uint32_t pad00[0x34 / 4];
    cCivList* mpCivList_34;                      // +0x34
    uint32_t pad38[(0x74c - 0x38) / 4];
    uint8_t    mFlag74c;                         // +0x74c
};

class cSimObject {                                                   // object with a window at +0xd4
public:
    uint32_t pad00[0xd4 / 4];
    IWinText* mpText_0d4;                        // +0xd4
};

class cPlayerUFO {
public:
    cPlayerInventory* GetPlayerInventory();                          // 0x00A1AD60
    bool FUN_00ffc8d0(cCivData* pCiv);                               // 0x00FFC8D0
    int  FUN_00ffc4e0(cCivData* a, cCivData* pCiv);                  // 0x00FFC4E0
};
cPlayerUFO* GetUFOSimulator();                                       // 0x00FFBE50

class cEmpire;
class cSpaceStar;

cCivData*  FUN_01021240();                                           // 0x01021240 (active civ)
cSimObject* FUN_01036e20();                                          // 0x01036E20
cSpaceStar* FUN_0067dd50();                                          // 0x0067DD50
cEmpire* FUN_01021300();                                             // 0x01021300 (player empire)
int  FUN_01021090();                                                 // 0x01021090 (player empire id)

class cEmpire {
public:
    uint32_t pad00[0x84 / 4];
    int mEmpireID;                              // +0x84
    int FUN_00c30cb0();                                              // 0x00C30CB0
};

class cWindowRef : public EA::AutoRefCount<IWindow> {
public:
    cWindowRef& operator=(IWindow* p);                               // 0x00B5F950 (shared out-of-line instance)
};
class cTextRef : public EA::AutoRefCount<IWinText> {
public:
    cTextRef& operator=(IWinText* p);                                // 0x00B5F950 (shared out-of-line instance)
};

class cSPUIMeter {
public:
    bool IsVisible();                                                // 0x00E06970
};

class cMeterHolder {
public:
    class cMeter {
    public:
        virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
        virtual int  GetMaxValue();                                  // +0x10
        virtual void SetValue(int value);                            // +0x14
        virtual int  GetState();                                     // +0x18
    };
    uint32_t pad[0x20c / 4];
    cMeter mMeter;                               // +0x20c
};
cMeterHolder* FUN_00deced0(IWindow* pWindow);                         // 0x00DECED0

class cSpaceTokenTranslator {
public:
    uint32_t pad00[3];
    cCityRuntime* mpCity;                        // +0xc
};
extern cSpaceTokenTranslator* gpSpaceTokenTranslator;                // 0x016E0D08

struct cModeState { uint32_t pad00[0x2c / 4]; int mState; };          // +0x2c

class cGameModeA { public: bool FUN_00ae9390(); };                    // 0x00AE9390
class cGameModeB { public: bool FUN_00e18c70(int a); };               // 0x00E18C70
class cGameModeC { public: bool FUN_00b5ca60(); };                    // 0x00B5CA60

cGameModeA* FUN_00b3d4a0();                                          // 0x00B3D4A0
cGameModeB* FUN_00b3d3f0();                                          // 0x00B3D3F0
cGameModeC* FUN_00b3d230();                                          // 0x00B3D230
cModeState* FUN_00b3d4d0();                                          // 0x00B3D4D0
IWindowManager* WindowManager();                                     // 0x0067CAA0

class cSPUIGlobalUI {
public:
    IWindow* FindWindowByID(uint32_t id);                            // 0x00E012B0
};

// cSpaceStar -- the object querying a row span (FUN_0067dd50's result); GetRowSpan returns the
// int array whose [8]/[0xc] entries are the rollover's row/column counts.
class cSpaceStar {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18();
    virtual int* GetRowSpan();                                       // +0x1c
};

void  FUN_010677b0(cCivData* pCiv, float x, float y);                // 0x010677B0
void  FUN_01043d10(float* out, void* a, void* b, float c, void* v);  // 0x01043D10
void  Matrix3_Assign(void* m, const void* src);                      // 0x0041CB40
float FUN_00c8c7f0(cCityRuntime* p, int* pOut);                      // 0x00C8C7F0
void* FUN_00bba790(cCivData* pCiv);                                  // 0x00BBA790 (city/civ list)
void  SPUIHelpers_SetTooltipText(IWindow* w, const wchar_t* text);   // 0x00806DE0

class cSpaceTradeRouteManager {
public:
    float SystemHasTradeRouteWithPlayer(int starID, void* pAvatar);  // 0x01037DD0
};
class cSpaceStarManager {
public:
    cSpaceTradeRouteManager* FUN_00ba6490();                         // 0x00BA6490
};
class cGameNounManager { public: void* GetAvatar(); };               // 0x00B1FDB0
cSpaceStarManager* StarManager();                                    // 0x00B3D2A0

struct Rect4 { float x1, y1, x2, y2; };
void SPUIHelpers_GetMainWindowArea(Rect4* out);                      // 0x00805EA0

extern uint32_t gStarMeterIDs[5];                                    // 0x0149C158

// float / data constants used by the effect transform in FUN_010697b0
extern const float kFxOffsetX;                                       // 0x016E2824
extern const float kFxOffsetY;                                       // 0x016E2828
extern const float kFxOffsetZ;                                       // 0x016E282C
extern const Matrix3f kFxMatrixSrc;                                  // 0x016E2800
extern const float kEffectFade;                                      // 0x01488874

// layout constants used by the star rollover (shared with the sibling slices)
extern const float kRolloverRowHeight;                               // 0x0149C1A0 (25.0f)
extern const float kRolloverBlockHeight;                             // 0x0149C1A4 (26.0f)
extern const float kEffectGizmoScaleX;                               // 0x01494FBC (0.67f)

namespace SPUIHelpers {
    void DestroyRolloverFrame(IWindow* pFrame);                      // 0x008074A0
    IWindow* CreateRolloverFrame(const wchar_t* name, float x, float y, float w, float h,
                                 IWindow** ppContainer, int a, int b, float radius, uint32_t id);  // 0x008093B0
    void UpdateRolloverFrame(IWindow* pFrame, float x, float y, int c, float radius);               // 0x00809370
}

class cSPUISpace {
public:
    uint32_t pad000[(0xe4 - 0x0) / 4];
    cString mStarTooltipA;                      // +0xe4
    cString mStarTooltipB;                      // +0xf8
    uint32_t pad10c[(0x224 - 0x10c) / 4];
    cSPUIGlobalUI* mpGlobalUI;                  // +0x224
    uint32_t pad228[(0x588 - 0x228) / 4];
    cTextRef  mStarRolloverText;                // +0x588 (AutoRefCount<IWinText>)
    uint32_t pad58c;
    cWindowRef mStarRolloverFrame;              // +0x590
    uint32_t pad594;
    EA::AutoRefCount<IWindow> mMissionRolloverRoot;   // +0x598
    EA::AutoRefCount<IWindow> mStarRolloverRoot;      // +0x59c
    uint32_t pad5a0[3];
    EA::AutoRefCount<cSPUIMeter> mpCaptureMeterA;     // +0x5ac
    EA::AutoRefCount<cSPUIMeter> mpCaptureMeterB;     // +0x5b0
    EA::AutoRefCount<cSPUIMeter> mpAnimator;          // +0x5b4

    void UpdateStarRollover(cStarRecord* pStar);                              // 0x010691E0
    void FUN_010697b0(cCivData* pCiv);                                        // 0x010697B0
    void FUN_01069aa0();                                                      // 0x01069AA0
    int  UpdateCaptureBarsVisibility(cCivData* pCiv);                         // 0x01067510
    void FUN_010677b0(cCivData* pCiv, float x, float y, bool b);              // 0x010677B0
};

}  // namespace SP

#pragma pack(pop)

using namespace SP;

template <class T> static __forceinline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }

template <class P> static __forceinline void DetachFromParent(const P& pWindow)
{
    if (pWindow->GetParent())
        pWindow->GetParent()->RemoveWindow(pWindow);
}

// ---------------------------------------------------------------------------
// 0x010691e0  UpdateStarRollover(cStarRecord* pStar)
// ---------------------------------------------------------------------------
// @ 0x010691e0
void cSPUISpace::UpdateStarRollover(cStarRecord* pStar)
{
    int modeState;
    if (FUN_00b3d4a0()->FUN_00ae9390() ||
        FUN_00b3d3f0()->FUN_00e18c70(0) ||
        FUN_00b3d230()->FUN_00b5ca60() ||
        (modeState = FUN_00b3d4d0()->mState) == 1 || modeState == 2 ||
        WindowManager()->GetModalWindow() != 0)
    {
        mStarRolloverRoot->SetFlag(1, false);
        DetachFromParent(mStarRolloverRoot);
        DetachFromParent(mMissionRolloverRoot);
        SPUIHelpers::DestroyRolloverFrame(mStarRolloverFrame);
        mStarRolloverFrame.Clear();
        mStarRolloverText.Clear();
        return;
    }

    bool bShow = false;
    IWindow* pText = mStarRolloverRoot->FindWindowByID(0x1c22501, true);
    if (!pText)
        goto finish;

    {
        cSimObject* pObj = FUN_01036e20();
        if (!pObj) {
            if (mStarRolloverText && mStarRolloverFrame) {
                DetachFromParent(mStarRolloverRoot);
                DetachFromParent(mMissionRolloverRoot);
                SPUIHelpers::DestroyRolloverFrame(mStarRolloverFrame);
                mStarRolloverFrame.Clear();
                mStarRolloverText.Clear();
            }
            mStarRolloverText.Clear();
            goto finish;
        }

        int* pRows = FUN_0067dd50()->GetRowSpan();
        float fRow = (float)pRows[2] - 1.0f;
        float fCol = (float)pRows[3] - 1.0f;
        bShow = true;

        if (mStarRolloverText == pObj->mpText_0d4) {
            SPUIHelpers::UpdateRolloverFrame(mStarRolloverFrame, fRow, fCol, 1, 0.0f);
        } else {
            mStarRolloverText = pObj->mpText_0d4;

            IWindow* pOwnerBlock  = mStarRolloverRoot->FindWindowByID(0x684c020, true);
            IWindow* pEmpireIcon  = mStarRolloverRoot->FindWindowByID(0x1c22519, true);
            IWindow* pPlanetBlock = mStarRolloverRoot->FindWindowByID(0x4cad958, true);
            IWindow* pWeaponMeter = mStarRolloverRoot->FindWindowByID(0x1c22518, true);
            IWindow* pOwnerColor  = mStarRolloverRoot->FindWindowByID(0x5e62728, true);
            IWindow* pTravelText  = mStarRolloverRoot->FindWindowByID(0x6270638, true);

            if (pOwnerBlock)  pOwnerBlock->SetFlag(1, false);
            if (pEmpireIcon)  pEmpireIcon->SetFlag(1, false);
            if (pPlanetBlock) pPlanetBlock->SetFlag(1, false);
            if (pWeaponMeter) pWeaponMeter->SetFlag(1, false);
            if (pOwnerColor)  pOwnerColor->SetFlag(1, false);
            if (pTravelText)  pTravelText->SetFlag(1, false);

            pTravelText->SetCaption(((cStarRecord*)pStar)->GetName()->c_str());

            const Math::Rectangle& area = mStarRolloverRoot->GetArea();
            float x1 = area.x1;
            float y1 = area.y1;
            float x2 = area.x2;
            float y2 = area.y1 + kRolloverBlockHeight;
            mStarRolloverRoot->SetArea(Math::Rectangle(x1, y1, x2, y2));
            mStarRolloverRoot->SetLocation(0.0f, 0.0f);

            if (mStarRolloverFrame) {
                DetachFromParent(mStarRolloverRoot);
                DetachFromParent(mMissionRolloverRoot);
                SPUIHelpers::DestroyRolloverFrame(mStarRolloverFrame);
                mStarRolloverFrame.Clear();
            }
            EA::AutoRefCount<IWindow> pContainer;
            mStarRolloverFrame = SPUIHelpers::CreateRolloverFrame(
                L"RolloverFrameGeneric", fRow, fCol, x2 - x1, y2 - y1,
                pContainer.AsPPTypeParam(), 1, 1, 0.0f, 0xe9f70df9);
            DetachFromParent(mStarRolloverRoot);
            pContainer->AddWindow(mStarRolloverRoot);
        }
    }

finish:
    if (mStarRolloverRoot)
        mStarRolloverRoot->SetFlag(1, bShow);
}

// ---------------------------------------------------------------------------
// 0x010697b0  FUN_010697b0(cCivData* pCiv)
// ---------------------------------------------------------------------------
// @ 0x010697b0
void cSPUISpace::FUN_010697b0(cCivData* pCiv)
{
    cSpaceGfx::cSlot* pSlot = GetSpaceGfx()->mSlot30.mpObject;
    if (!pCiv) {
        pSlot->Show(false);
        GetSpaceGfx()->mSelectedID = 0;
        return;
    }

    cCivData* pActive = FUN_01021240();
    if (pCiv == pActive) {
        pSlot->Show(false);
        GetSpaceGfx()->mSelectedID = 0;
        return;
    }

    cCityRuntime** pCities = (cCityRuntime**)pCiv->GetCities();
    cPlayerInventory* pInv = GetUFOSimulator()->GetPlayerInventory();
    Vector3 vPos(0.0f, 0.0f, 0.0f);
    if (pInv->mFlag74c == 1) {
        if (pCiv == GetSpaceGfx()->mSelectedID)
            return;
        vPos = *(Vector3*)pActive->GetCities();
        GetSpaceGfx()->mSelectedID = pCiv;
    } else {
        vPos = GetUFOSimulator()->GetPlayerInventory()->mpCivList_34->GetPosition();
    }

    bool bReachable = GetUFOSimulator()->FUN_00ffc8d0(pCiv);
    int nCost = GetUFOSimulator()->FUN_00ffc4e0(pActive, pCiv);
    if (bReachable) {
        int nLimit = FUN_01021300()->FUN_00c30cb0();
        if (nCost <= nLimit)
            goto havePos;
    }
    vPos = Vector3(0.05f, 0.05f, 1.0f);

havePos:
    pSlot->Show(true);

    cSpaceGfx* pGfx = GetSpaceGfx();
    cSpaceGfx::cEffectsMgr* pEffects = pGfx->mpEffectsMgr94;
    pGfx->mSlot30.Clear();
    pEffects->CreateVisualEffect(0x840cea6, 0, (void**)&pGfx->mSlot30);

    cSpaceGfx::cSlot* pSlot2 = GetSpaceGfx()->mSlot30.mpObject;
    if (!pSlot2->IsVisible())
        pSlot2->Use(0);

    EffectTransform xform;
    xform.mOffset = Vector3(kFxOffsetX, kFxOffsetY, kFxOffsetZ);
    xform.mFlags = 0;
    xform.mnChangeCount = 0;
    xform.mfScale = 1.0f;
    Matrix3_Assign(&xform.mMatrix, &kFxMatrixSrc);
    xform.mFlags |= 4;
    xform.mnChangeCount++;
    xform.mOffset = vPos;
    pSlot2->SetTransform(xform);

    FUN_01043d10(0, 0, 0, kEffectFade, 0);
    pSlot2->SetParams(0xd, 0, 0);
    pSlot2->SetParams(5, 0, 3);

    (void)pCities;
}

// ---------------------------------------------------------------------------
// 0x01069aa0  FUN_01069aa0()
// ---------------------------------------------------------------------------
// @ 0x01069aa0
void cSPUISpace::FUN_01069aa0()
{
    Rect4 area;
    SPUIHelpers_GetMainWindowArea(&area);
    float cx = (area.y2 - area.y1) * 0.5f + 5.0f;

    int nCaptureBars = UpdateCaptureBarsVisibility(FUN_01021240());
    IWindow* pWindow = mpGlobalUI->FindWindowByID(0x65680f8);
    if (!pWindow)
        return;

    pWindow->SetFlag(1, nCaptureBars > 0);
    int nRows = 0;
    bool bSeti = false;
    float fY = 10.0f;
    if (nCaptureBars > 0) {
        const Math::Rectangle& wa = pWindow->GetArea();
        float x1 = wa.x1, y1 = wa.y1, x2 = wa.x2, y2 = wa.y2;
        float pos = (cx - y2) * 0.5f - (x2 - x1) * 0.5f;
        pWindow->SetLocation(pos, 0.0f);

        const Math::Rectangle& wa2 = pWindow->GetArea();
        Math::Rectangle r(wa2.x1, wa2.y1, wa2.x2, (float)nCaptureBars * 25.0f + 49.0f);
        pWindow->SetArea(r);

        FUN_010677b0(FUN_01021240(), cx, 13.0f, false);

        IWindow* pBar = mpGlobalUI->FindWindowByID(0x6567050);
        if (pBar) {
            pBar->SetFlag(1, mpCaptureMeterA && mpCaptureMeterA->IsVisible());
            if (mpCaptureMeterA && mpCaptureMeterA->IsVisible()) {
                const Math::Rectangle& ba = pBar->GetArea();
                pBar->SetLocation(ba.x1, 10.0f);
                fY = 35.0f;
            }
        }
        pBar = mpGlobalUI->FindWindowByID(0x6567051);
        if (pBar)
            pBar->SetFlag(1, mpCaptureMeterB && mpCaptureMeterB->IsVisible());
        if (mpCaptureMeterB && mpCaptureMeterB->IsVisible()) {
            if (pBar) {
                const Math::Rectangle& ba = pBar->GetArea();
                pBar->SetLocation(ba.x1, fY);
                fY = fY + 25.0f;
            }
            void* pList = FUN_00bba790(FUN_01021240());
            cCityRuntime** pBegin = *(cCityRuntime***)pList;
            int nCities = (int)((cCityRuntime**)(*(cCityRuntime***)((char*)pList + 4) - pBegin));
            bSeti = true;
            for (int i = 0; i < nCities; i++) {
                cCityRuntime* pCity = pBegin[i];
                if (pCity->mState == 1 || pCity->mState == 0)
                    continue;
                if (pCity->FUN_00b8d970())
                    continue;
                if (pCity->FUN_00b8dab0() != 5)
                    continue;
                if (nRows >= 5)
                    goto nextCity;

                {
                    IWindow* pMeter = mpGlobalUI->FindWindowByID(gStarMeterIDs[nRows]);
                    cMeterHolder* pHolder = FUN_00deced0(pMeter);
                    bool bVisible = pMeter != 0 && pMeter->_v28();
                    if (pMeter && !bVisible)
                        pMeter->SetFlag(1, true);

                    int empireID = -1;
                    float fDist = FUN_00c8c7f0(pCity, &empireID);
                    if (fDist < 100.0f || empireID == FUN_01021090()) {
                        if (pHolder->mMeter.GetState() != 0 || !bVisible) {
                            gpSpaceTokenTranslator->mpCity = pCity;
                            SPUIHelpers_SetTooltipText(pMeter, mStarTooltipA.GetText());
                            pHolder->mMeter.SetValue(-1);
                        }
                        bSeti = false;
                    } else {
                        if (pHolder->mMeter.GetState() != 1 || !bVisible) {
                            gpSpaceTokenTranslator->mpCity = pCity;
                            SPUIHelpers_SetTooltipText(pMeter, mStarTooltipB.GetText());
                            pHolder->mMeter.SetValue(1);
                        }
                    }
                    nRows++;
                }
nextCity:
                ;
            }

            IWindow* pHeight = mpGlobalUI->FindWindowByID(0x65b9b00);
            if (pHeight) {
                const Math::Rectangle& ha = pHeight->GetArea();
                pHeight->SetLocation((float)(5 - nRows) * 16.5f + 27.0f, ha.y1);
            }
        }
    }

    IWindow* pSetiFrame = mpGlobalUI->FindWindowByID(0x65680e8);
    if (pSetiFrame) {
        pSetiFrame->SetFlag(1, bSeti);
        if (bSeti) {
            const Math::Rectangle& sa = pSetiFrame->GetArea();
            pSetiFrame->SetLocation(sa.x1, fY + 5.0f);
        }
    }

    IWindow* pTrade = mpGlobalUI->FindWindowByID(0x65ce2da);
    if (pTrade) {
        cSpaceTradeRouteManager* pMgr = StarManager()->FUN_00ba6490();
        float fTrade = pMgr->SystemHasTradeRouteWithPlayer(
            *(int*)((char*)FUN_01021240() + 0x70),
            ((cGameNounManager*)FUN_01021240())->GetAvatar());
        pTrade->SetFlag(1, fTrade >= 100.0f);
        if (fTrade >= 100.0f) {
            const Math::Rectangle& ta = pTrade->GetArea();
            pTrade->SetLocation(ta.x1, fY + 5.0f);
        }
    }

    if (nRows < 5) {
        for (int i = nRows; i < 5; i++) {
            IWindow* pMeter = mpGlobalUI->FindWindowByID(gStarMeterIDs[i]);
            if (pMeter)
                pMeter->SetFlag(1, false);
        }
    }
}
