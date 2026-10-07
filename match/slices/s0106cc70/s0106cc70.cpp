// Slice s0106cc70 -- SP::cSPUISpace::UpdateTravelLine(target)   (__thiscall, ret 4)
//
// Space-stage rollover for the star / travel target under the cursor: hides everything while a
// modal UI / transition is active, otherwise fills the star rollover (owner colour, capture
// bars, planets, SETI, travel range colouring), positions and frames it, and keeps the
// "travel line" effect on the target while it is within the UFO's range.
// Retail member offsets differ from the dev PDB; stubs below use the offsets this function uses
// (shared vocabulary with the neighbouring s0106ba00 UpdatePlanetRollover).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (SSE scalar float copies and cvtsi2ss, x87 for
// float arguments; AutoRefCount / vector locals without an EH frame -> no /EHsc).

#include "types.h"

#pragma pack(push, 8)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

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
uint32_t PackARGB(int a, int r, int g, int b);                      // 0x0067AC80 (EA::Color)
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
    virtual void _v24(); virtual void _v28(); virtual void _v2c(); virtual void _v30();
    virtual const Math::Rectangle& GetArea();                        // +0x34
    virtual const Math::Rectangle& GetRealArea();                    // +0x38
    virtual void _v3c(); virtual void _v40(); virtual void _v44();
    virtual void _v48(); virtual void _v4c(); virtual void _v50(); virtual void _v54();
    virtual void _v58();
    virtual void SetShadeColor(uint32_t color);                      // +0x5c
    virtual void SetArea(const Math::Rectangle& area);               // +0x60
    virtual void SetLocation(float x, float y);                      // +0x64
    virtual void _v68(); virtual void _v6c();
    virtual void SetLayoutLocation(float x, float y);                // +0x70
    virtual void _v74();
    virtual void _v78();
    virtual void SetFlag(int flag, bool value);                      // +0x7c
    virtual void SetCaption(const wchar_t* caption);                 // +0x80
    virtual void _v84(); virtual void _v88(); virtual void _v8c();
    virtual int Invalidate();                                        // +0x90
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

struct Transform {
    uint16_t mFlags;                            // +0x0
    uint16_t mnChangeCount;                     // +0x2
    uint32_t pad04[3];
    float mfScale;                              // +0x10
    uint32_t pad14[(0x38 - 0x14) / 4];
    Transform();                                                     // 0x00434040
    void SetOffset(const Vector3& offset);                           // 0x00571D40
};

namespace EA { namespace Swarm {
class cIVisualEffect {
public:
    virtual int AddRef();                                            // +0x0
    virtual int Release();                                           // +0x4
    virtual bool Start(int flags);                                   // +0x8
    virtual bool Stop(int flags);                                    // +0xc
    virtual void _v10();
    virtual void SetTransform(const ::Transform& xform);             // +0x14
};
class IEffectsManager {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28();
    virtual bool CreateVisualEffect(uint32_t id, int flags, cIVisualEffect** ppEffect);  // +0x2c
};
} }

namespace SP {

class cString {   // retail size 0x14
public:
    uint32_t pad[5];
    const wchar_t* GetText();                                        // 0x006B55C0
};

class cStarRecord;

class cEmpire {
public:
    uint32_t pad00[0x50 / 4];
    uint32_t mFlags;                            // +0x50
    uint32_t pad54[(0x84 - 0x54) / 4];
    uint32_t mEmpireID;                         // +0x84
    const Math::ColorRGB& GetColor(Math::ColorRGB* pOut);            // 0x00C32CD0
    int GetWeaponryLevel();                                          // 0x00C317A0
    bool FUN_00c308b0();                                             // 0x00C308B0
    int FUN_00c30cb0();                                              // 0x00C30CB0
    cStarRecord* FUN_00c30c60();                                     // 0x00C30C60
    bool IsFlag6() const { return ((mFlags >> 6) & 1) != 0; }
};

class cOwnerData { public: int FUN_00b1fdb0(); };                    // 0x00B1FDB0 (owner empire id, -1 = none)

class cPlanetRecord {
public:
    virtual int AddRef();
    virtual int Release();
    int FUN_00b8dab0();                                              // 0x00B8DAB0 (planet type)
    cOwnerData* FUN_00b8de30();                                      // 0x00B8DE30
};

class cPlanetRecordVector {        // eastl::vector<AutoRefCount<cPlanetRecord>, sp_vector_allocator>
public:
    EA::AutoRefCount<cPlanetRecord>* mpBegin;
    EA::AutoRefCount<cPlanetRecord>* mpEnd;
    EA::AutoRefCount<cPlanetRecord>* mpCapacity;
    uint32_t mAllocator;
    cPlanetRecordVector(const void* src);                            // 0x00BA95A0
    ~cPlanetRecordVector();                                          // 0x00AE6970
    int size() const { return (int)(mpEnd - mpBegin); }
    EA::AutoRefCount<cPlanetRecord>& operator[](int i) { return mpBegin[i]; }
};
void FUN_01022530(cPlanetRecordVector* v);                           // 0x01022530 (sort)

class cStarRecord {
public:
    const Vector3* GetPosition();                                    // 0x005C65E0
    bool FUN_00bb9af0(int a);                                        // 0x00BB9AF0
    bool FUN_00bb9c00();                                             // 0x00BB9C00
    const void* FUN_00bba790();                                      // 0x00BBA790 (planet list)
    const string16* GetName();                                       // 0x00BB9DE0
};

class cStar {                                  // the 3D star / travel target object
public:
    uint32_t pad00[0x34 / 4];
    int m34;                                    // +0x34
    uint32_t pad38[(0xa0 - 0x38) / 4];
    Vector3 mPosition;                          // +0xa0
    uint32_t padac;
    string16 mName;                             // +0xb0
    uint32_t padb8[(0xc8 - 0xb8) / 4];
    float mRadius;                              // +0xc8
};

class cTravelTarget;
cStar* FUN_010662d0(cTravelTarget* p);                               // 0x010662D0
cStarRecord* FUN_010662f0(cTravelTarget* p);                         // 0x010662F0

class cWindowRef : public EA::AutoRefCount<IWindow> {
public:
    cWindowRef& operator=(IWindow* p);                               // 0x00B5F950 (shared out-of-line instance)
};
class cTargetRef : public EA::AutoRefCount<cTravelTarget> {
public:
    cTargetRef& operator=(cTravelTarget* p);                         // 0x00B5F950 (shared out-of-line instance)
};
class cTravelTarget {
public:
    virtual int AddRef();
    virtual int Release();
};

class cSPUIAnimator {
public:
    virtual int AddRef();
    virtual int Release();
    void Shutdown(bool b);                                           // 0x00E06940
};

class cSpaceTokenTranslator {
public:
    uint32_t pad00[4];
    cStarRecord* mpStarRecord;                  // +0x10
};
extern cSpaceTokenTranslator* gpSpaceTokenTranslator;                // 0x016E0D08
extern bool g_bSetiDisabled;                                         // 0x015B7430

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
EA::Swarm::IEffectsManager* EffectsManager();                        // 0x0067DDD0
cGameTimeManager* GameTimeManager();                                 // 0x00B3D380

class cUFOSimulator {
public:
    bool FUN_00ffc8d0(cStarRecord* star);                            // 0x00FFC8D0 (reachable)
    int FUN_00ffc4e0(cStarRecord* from, cStarRecord* to);            // 0x00FFC4E0 (jumps)
    float FUN_00ffd220(cStarRecord* star);                           // 0x00FFD220 (radius)
    float GetMaxTravelDistance();                                    // 0x00FFBFC0
};
cUFOSimulator* GetUFOSimulator();                                    // 0x00FFBE50

class cSpaceGame { public: void FUN_01002bf0(cStarRecord* star); };  // 0x01002BF0
cSpaceGame* SpaceGameGet();                                          // 0x01002BD0

class cStarManager { public: cEmpire* GetEmpireByID(int id); };      // 0x00BA9370
cStarManager* StarManager();                                         // 0x00B3D2A0
class cRelationshipManager { public: bool FUN_00d01b50(uint32_t a, uint32_t b); };  // 0x00D01B50
cRelationshipManager* RelationshipManager();                         // 0x00B3D2C0

uint32_t ColorRGBAToU32(const Math::ColorRGBA& color);               // 0x004580C0
void SetEmpireIcon(uint32_t empireID, IWindow* pWindow);             // 0x00E2E6E0
void WorldToScreen(const Vector3& pos, float* pX, float* pY);        // 0x00E50750
float GetScreenRadius(const Vector3& pos, float radius);             // 0x01066390
float FUN_010434e0(const Vector3* a, const Vector3* b);              // 0x010434E0 (distance)

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

class cSPLivingUniverse {
public:
    static int GetUniverseContext();                                 // 0x01021080
    static cEmpire* GetPlayerEmpire();                               // 0x01021300
    static cStarRecord* GetActiveStarRecord();                       // 0x01021240
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
    uint32_t pad000[0x230 / 4];
    void* m230;                                 // +0x230 (star-planet row container)
    uint32_t pad234[(0x2fc - 0x234) / 4];
    EA::AutoRefCount<EA::Swarm::cIVisualEffect> mTravelLineEffect;   // +0x2fc
    uint32_t pad300[(0x414 - 0x300) / 4];
    cString mTravelText;                        // +0x414
    uint32_t pad428[(0x588 - 0x428) / 4];
    cTargetRef mRolloverTarget;                 // +0x588
    uint32_t pad58c;
    cWindowRef mStarRolloverFrame;              // +0x590
    uint32_t pad594;
    EA::AutoRefCount<IWindow> mMissionRolloverRoot;   // +0x598
    EA::AutoRefCount<IWindow> mStarRolloverRoot;      // +0x59c
    uint32_t pad5a0[3];
    EA::AutoRefCount<cSPUIAnimator> mpCaptureMeterA;  // +0x5ac
    EA::AutoRefCount<cSPUIAnimator> mpCaptureMeterB;  // +0x5b0
    EA::AutoRefCount<cSPUIAnimator> mpAnimator;       // +0x5b4

    void HideStarPlanet(void* container, int index);                                   // 0x01065B60
    bool DisplayStarPlanet(void* container, int index, cPlanetRecord* pRecord);        // 0x01068970
    void ManageSeti(cStarRecord* pStar, int* pRow);                                    // 0x0106B310
    int UpdateCaptureBarsVisibility(cStarRecord* pStar);                               // 0x01067510
    IWindow* UpdateMissionRollover(cStarRecord* pStar, int a, float x, float y);       // 0x0106A0A0
    void FUN_010697b0(cStarRecord* pStar);                                             // 0x010697B0
    void FUN_010677b0(cStarRecord* pStar, Math::Point pos, bool b);                    // 0x010677B0
    void UpdateTravelLine(cTravelTarget* pTarget);
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

// 0x0106cc70
void cSPUISpace::UpdateTravelLine(cTravelTarget* pTarget)
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
        if (mpAnimator) {
            mpAnimator->Shutdown(true);
            mpAnimator.Clear();
        }
        if (cSPLivingUniverse::GetUniverseContext() == 2) {
            if (mpCaptureMeterA) {
                mpCaptureMeterA->Shutdown(true);
                mpCaptureMeterA.Clear();
            }
            if (mpCaptureMeterB) {
                mpCaptureMeterB->Shutdown(true);
                mpCaptureMeterB.Clear();
            }
        }
        SPUIHelpers::DestroyRolloverFrame(mStarRolloverFrame);
        mStarRolloverFrame.Clear();
        mRolloverTarget.Clear();
        return;
    }

    cStar* pStar = FUN_010662d0(pTarget);
    cStarRecord* pRecord = FUN_010662f0(pTarget);
    if (!pStar && !pRecord) {
        mStarRolloverRoot->SetFlag(1, false);
        if (mStarRolloverFrame) {
            // the retail code tests the frame's parent here (not the root's)
            if (mStarRolloverFrame->GetParent())
                mStarRolloverRoot->GetParent()->RemoveWindow(mStarRolloverRoot);
            DetachFromParent(mMissionRolloverRoot);
            SPUIHelpers::DestroyRolloverFrame(mStarRolloverFrame);
            mStarRolloverFrame.Clear();
            mRolloverTarget.Clear();
        }
    }

    cStarRecord* pLineStar = pRecord;
    if (pStar && pStar->m34 == 0)
        pLineStar = cSPLivingUniverse::GetActiveStarRecord();

    bool bTransitioning = FUN_00b3d230()->FUN_00b5ca60();
    if (!bTransitioning) {
        IWindow* pOwnerBlock = mStarRolloverRoot->FindWindowByID(0x684c020, true);
        IWindow* pEmpireIcon = mStarRolloverRoot->FindWindowByID(0x1c22519, true);
        IWindow* pPlanetBlock = mStarRolloverRoot->FindWindowByID(0x4cad958, true);
        IWindow* pWeaponMeter = mStarRolloverRoot->FindWindowByID(0x5e62728, true);
        IWindow* pOwnerColor = mStarRolloverRoot->FindWindowByID(0x4bdc316, true);
        pOwnerBlock->SetFlag(1, false);
        pEmpireIcon->SetFlag(1, false);
        pPlanetBlock->SetFlag(1, false);
        if (pWeaponMeter)
            pWeaponMeter->SetFlag(1, false);
        IWindow* pTravelText = mStarRolloverRoot->FindWindowByID(0x6270638, true);
        bool bIsActiveStar = true;
        pTravelText->SetFlag(1, false);
        pOwnerColor->SetShadeColor(0x8c79898d);
        int row = 0;

        if (cSPLivingUniverse::GetUniverseContext() == 2 && pRecord) {
            cStarRecord* pActive = cSPLivingUniverse::GetActiveStarRecord();
            bIsActiveStar = (pRecord == pActive);
            IWindow* pTravelCaption = mStarRolloverRoot->FindWindowByID(0x328e99b, true);
            if (!bIsActiveStar) {
                pTravelText->SetFlag(1, true);
                gpSpaceTokenTranslator->mpStarRecord = pRecord;
                pTravelCaption->SetCaption(mTravelText.GetText());
                uint32_t color = EA::PackARGB(0xff, 0xff, 0xff, 0xff);
                bool bReachable = GetUFOSimulator()->FUN_00ffc8d0(pRecord);
                int jumps = GetUFOSimulator()->FUN_00ffc4e0(pActive, pRecord);
                if (!bReachable || jumps > cSPLivingUniverse::GetPlayerEmpire()->FUN_00c30cb0())
                    color = EA::PackARGB(0xff, 0xff, 0, 0);
                pTravelText->SetShadeColor(color);
                pTravelText->Invalidate();
            }

            for (int i = 0; i < 5; i++)
                HideStarPlanet(m230, i);

            if (pRecord->FUN_00bb9af0(2) &&
                pRecord != cSPLivingUniverse::GetPlayerEmpire()->FUN_00c30c60()) {
                pOwnerBlock->SetFlag(1, false);
                pPlanetBlock->SetFlag(1, true);
                row = 1;
            } else if (pRecord->FUN_00bb9c00() || g_bSetiDisabled) {
                SpaceGameGet()->FUN_01002bf0(pRecord);
                pOwnerBlock->SetFlag(1, true);
                cEmpire* pPlayer = cSPLivingUniverse::GetPlayerEmpire();
                cPlanetRecord* pAllied = 0;
                cEmpire* pOwner = 0;
                {
                    cPlanetRecordVector planets(pRecord->FUN_00bba790());
                    FUN_01022530(&planets);
                    int n = planets.size();
                    for (int i = 0; i < n; i++) {
                        cPlanetRecord* pPlanet = planets[i];
                        if (DisplayStarPlanet(m230, row, pPlanet))
                            row++;
                        if (pPlanet->FUN_00b8dab0() == 5) {
                            int empireID = pPlanet->FUN_00b8de30()->FUN_00b1fdb0();
                            if (empireID != -1) {
                                cEmpire* pEmpire = StarManager()->GetEmpireByID(empireID);
                                if (pEmpire) {
                                    pOwner = pEmpire;
                                    if (pPlayer && pEmpire != pPlayer &&
                                        RelationshipManager()->FUN_00d01b50(pEmpire->mEmpireID, pPlayer->mEmpireID))
                                        pAllied = pPlanet;
                                }
                            }
                        }
                    }
                    if (pOwner) {
                        Math::ColorRGB tmp;
                        pOwnerColor->SetShadeColor(ColorRGBAToU32(Math::ColorRGBA(pOwner->GetColor(&tmp), 1.0f)));
                        if (pWeaponMeter && !pOwner->IsFlag6() && !pOwner->FUN_00c308b0()) {
                            pWeaponMeter->SetFlag(1, true);
                            cMeterHolder::cMeter* pMeter = &FUN_00deced0(pWeaponMeter)->mMeter;
                            int maxLevel = pMeter->GetMaxValue() - 1;
                            int level = pOwner->GetWeaponryLevel() + 1;
                            pMeter->SetValue(Min(level, maxLevel));
                        }
                    }
                    if (pAllied)
                        SetEmpireIcon(pOwner->mEmpireID, pEmpireIcon);
                }
            }
        }
        if (!g_bSetiDisabled)
            ManageSeti(pRecord, &row);

        mStarRolloverRoot->FindWindowByID(0x1c22518, true)->SetFlag(1, false);
        int numCaptureBars = 0;
        if (cSPLivingUniverse::GetUniverseContext() == 2)
            numCaptureBars = UpdateCaptureBarsVisibility(pRecord);

        if (pStar || pRecord) {
            Vector3 pos = pStar ? pStar->mPosition : *pRecord->GetPosition();
            float screenX, screenY;
            WorldToScreen(pos, &screenX, &screenY);
            screenY -= 10.0f;
            float radius = pStar ? pStar->mRadius : GetUFOSimulator()->FUN_00ffd220(pRecord);
            float screenRadius = GetScreenRadius(pos, radius);
            if (mRolloverTarget == pTarget) {
                SPUIHelpers::UpdateRolloverFrame(mStarRolloverFrame, screenX, screenY, true, screenRadius);
            } else {
                float height = (float)(numCaptureBars + row) * 25.0f + 26.0f;
                const Math::Rectangle& area = mStarRolloverRoot->GetArea();
                Math::Rectangle rect(area.x1, area.y1, area.x2, area.y1 + height);
                if (!bIsActiveStar)
                    rect.y2 += 25.0f;
                mStarRolloverRoot->SetArea(rect);
                mStarRolloverRoot->SetLocation(0.0f, 0.0f);
                if (!bIsActiveStar) {
                    const Math::Rectangle& textArea = pTravelText->GetRealArea();
                    float textX = textArea.x1;
                    float textY1 = textArea.y1;
                    float textY2 = textArea.y2;
                    const Math::Rectangle& rootArea = mStarRolloverRoot->GetRealArea();
                    pTravelText->SetLayoutLocation(textX, rootArea.y2 - (textY2 - textY1));
                }
                IWindow* pMission = 0;
                if (cSPLivingUniverse::GetUniverseContext() == 2) {
                    pMission = UpdateMissionRollover(pRecord, 0, rect.x1, rect.y1);
                    if (pMission) {
                        rect.Union(rect, pMission->GetArea());
                        const Math::Rectangle& missionArea = pMission->GetArea();
                        mStarRolloverRoot->SetLocation(0.0f, missionArea.y2 - missionArea.y1);
                        pMission->SetLocation(0.0f, 0.0f);
                    }
                }
                mStarRolloverRoot->SetFlag(1, true);
                if (mStarRolloverFrame) {
                    DetachFromParent(mStarRolloverRoot);
                    DetachFromParent(mMissionRolloverRoot);
                    SPUIHelpers::DestroyRolloverFrame(mStarRolloverFrame);
                    mStarRolloverFrame.Clear();
                }
                EA::AutoRefCount<IWindow> pContainer;
                mStarRolloverFrame = SPUIHelpers::CreateRolloverFrame(
                    L"RolloverFrameGeneric", screenX, screenY, rect.x2 - rect.x1, rect.y2 - rect.y1,
                    pContainer.AsPPTypeParam(), 1, 1, screenRadius, 0xe9f70df9);
                DetachFromParent(mStarRolloverRoot);
                pContainer->AddWindow(mStarRolloverRoot);
                if (pMission) {
                    DetachFromParent(pMission);
                    pContainer->AddWindow(pMission);
                }
                mStarRolloverFrame->GetArea();
                mStarRolloverFrame->GetArea();
                IWindow* pName = mStarRolloverRoot->FindWindowByID(0x1c22501, true);
                pName->SetCaption(pRecord ? pRecord->GetName()->c_str() : pStar->mName.c_str());
            }
        }

        FUN_010697b0(pRecord);
        if (cSPLivingUniverse::GetUniverseContext() == 2) {
            Math::Rectangle bounds = SPUIHelpers::GetWindowBounds(mStarRolloverRoot);
            FUN_010677b0(pLineStar, Math::Point(bounds.x1 + 90.0f, bounds.y1 + ((float)row * 25.0f + 26.0f - 4.0f)), true);
        }
    }

    if (pRecord && !bTransitioning && pRecord != cSPLivingUniverse::GetActiveStarRecord()) {
        float distance = FUN_010434e0(cSPLivingUniverse::GetActiveStarRecord()->GetPosition(), pRecord->GetPosition());
        if (distance <= GetUFOSimulator()->GetMaxTravelDistance()) {
            if (!mTravelLineEffect) {
                EA::Swarm::IEffectsManager* pEffects = EffectsManager();
                if (pEffects->CreateVisualEffect(0x30af20a9, 0, mTravelLineEffect.AsPPTypeParam()))
                    mTravelLineEffect->Start(0);
                if (!mTravelLineEffect)
                    goto done;
            }
            Transform xform;
            xform.SetOffset(*pRecord->GetPosition());
            mTravelLineEffect->SetTransform(xform);
            mRolloverTarget = pTarget;
            return;
        }
    }

    if (mTravelLineEffect) {
        mTravelLineEffect->Stop((GameTimeManager()->mFlags >> 1) & 1);
        mTravelLineEffect.Clear();
    }

done:
    mRolloverTarget = pTarget;
}
