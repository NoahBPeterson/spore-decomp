// Slice s00e052d0: civilization HUD mode - feedback panel bookkeeping + minimap state, superweapon
// button kind mapping / click / cooldown arc / tooltip, stance buttons and the comm-rel HUD message
// handler (DoMessage).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
// Layouts: cSPUIGlobalUI is 0x68 bytes with four 12-byte comm-rel button records at +0x24;
// cSPUIGlobalUICiv adds a refcount base at +0x68 and the cIWinProc base at +0x70, then
//   0x74..0x84  five zeroed dwords          0x88/0x89  minimap flags
//   0x8c        tCivButton mButtons[4]      0xbc       float scratch
//   0xc0/0xc4   scratch ids                 0xd8       cooldown-shown bytes [4]
//   0xdc        id->index rbtree (anchor +0xe0, size +0xf0)
#include "types.h"

#define VSLOT(n) virtual void _v##n();

void __cdecl EASTL_allocator_deallocate(void* p);   // 0x00f47380

// ---------------------------------------------------------------------------
// strings
// ---------------------------------------------------------------------------
extern const wchar_t gEmptyString16[];   // 0x01667bac

struct sString16 {
    const wchar_t* mpBegin;      // +0x00
    const wchar_t* mpEnd;        // +0x04
    const wchar_t* mpCapacity;   // +0x08
    sString16() {
        mpBegin = gEmptyString16;
        mpEnd = gEmptyString16;
        mpCapacity = gEmptyString16 + 1;
    }
    void assign(const wchar_t* pBegin, const wchar_t* pEnd);   // 0x00423650
    void append(const wchar_t* pBegin, const wchar_t* pEnd);   // 0x00429580
    void Dtor() {
        if ((((uint32_t)mpCapacity - (uint32_t)mpBegin) & 0xfffffffe) > 2 && mpBegin)
            EASTL_allocator_deallocate((void*)mpBegin);
    }
};

void WStr_Format(sString16* pOut, const wchar_t* pFormat, ...);   // 0x0041e050

inline uint32_t wcslen(const wchar_t* pString) {
    const wchar_t* pEnd = pString;
    while (*pEnd)
        ++pEnd;
    return (uint32_t)(pEnd - pString);
}

// localized string (table id + key), 12 bytes
class cString {
public:
    uint32_t mnTableId;                                                  // +0x00
    uint32_t mnKey;                                                      // +0x04
    const wchar_t* mpString;                                             // +0x08
    cString(uint32_t nTableId, uint32_t nKey, const wchar_t* pString);   // 0x006b5770
    ~cString();                                                          // 0x006b5240
    const wchar_t* GetText();                                            // 0x006b55c0
};

void FormatMoney(double fValue, wchar_t* pBuffer, int32_t nSize, const wchar_t* pFormat,
                 const void* pTag);   // 0x008822e0

// ---------------------------------------------------------------------------
// small vectors
// ---------------------------------------------------------------------------
struct SimpleVectorU32 {
    uint32_t* mpBegin;      // +0x00
    uint32_t* mpEnd;        // +0x04
    uint32_t* mpCapacity;   // +0x08
    void push_back(const uint32_t& value);   // 0x00454860
};

void VectorAddModels(uint32_t nModel, SimpleVectorU32* pOut);   // 0x00555e80

void FreeSimpleVector(SimpleVectorU32* pVector) {
    if (pVector->mpBegin && ((int32_t*)pVector->mpBegin)[-1] != 0)
        EASTL_allocator_deallocate(pVector->mpBegin);
}

// ---------------------------------------------------------------------------
// game nouns
// ---------------------------------------------------------------------------
class cCivilization;
class cVehicle;
class cIObject;
class cMessage;

struct sCivilizationList {          // 0x00b25ca0 result
    cCivilization** mpBegin;        // +0x00
    cCivilization** mpEnd;          // +0x04
};

class cCivilization {
public:
    int32_t GetRwTypeKind(uint32_t nType);          // 0x00bef980 ret 4
    int32_t GetSuperweaponSpeccy();                 // 0x00bf0f40 ret 0
    bool SuperweaponOnCooldown(int32_t nKind);      // 0x00bf1790 ret 4
    float GetSuperweaponCooldown(int32_t nKind);    // 0x00bf17f0 ret 4
    bool CanUseSuperweapon(int32_t nKind);          // 0x00bf8a00 ret 4
    int32_t GetSuperweaponLevel(uint32_t nType);    // 0x00befa50 ret 4
    float InteractionScore(uint32_t nType);         // 0x00bf6cb0 ret 4
    int32_t GetInteractionLevel();                  // 0x00bf01e0 ret 0
    uint8_t mnPad00[0x8a];                          // +0x00
    uint8_t mbHidden;                               // +0x8a
};

struct sTerrainCurrency {           // SP::GetGameTerrainCursor result
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18)
    VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
    virtual void GetSelection(SimpleVectorU32* pOut, uint32_t nType);   // +0x60
    VSLOT(25) VSLOT(26) VSLOT(27)
    virtual bool HasSelection();                                        // +0x70
};

sTerrainCurrency* GetGameTerrainCursor();   // 0x00b30d70

class cIObject {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18)
    VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27)
    VSLOT(28) VSLOT(29) VSLOT(30) VSLOT(31) VSLOT(32) VSLOT(33) VSLOT(34) VSLOT(35) VSLOT(36)
    VSLOT(37) VSLOT(38) VSLOT(39) VSLOT(40) VSLOT(41) VSLOT(42) VSLOT(43) VSLOT(44) VSLOT(45)
    virtual cVehicle* AsVehicle(uint32_t nType);    // +0xb8
    VSLOT(47)
    virtual void Release();                         // +0xc0
};

class cVehicle : public cIObject {
public:
    uint8_t mnPadC4[0xa60];     // +0xc4
    int32_t mnStance;           // +0xb24
    void SetStance(int32_t nStance, bool bInstant);   // 0x00c9fa70 ret 8
};

class cTerrainEditor {
public:
    uint8_t mnPad00[0x10fc];    // +0x00
    uint32_t mnModel0;          // +0x10fc
    uint32_t mnModel1;          // +0x1100
    uint32_t mnModel2;          // +0x1104
};

class cGameNounManager {
public:
    cCivilization* GetPlayerCivilization();       // 0x00b25fb0 ret 0
    sCivilizationList* GetCivilizationList();     // 0x00b25ca0 ret 0
    cTerrainEditor* GetCurrentTerrainSphere();    // 0x00f67d90 ret 0
};

cGameNounManager* NounManager();   // 0x00b3d300

struct sGameTime {
    uint8_t mnPad00[0x48];      // +0x00
    uint8_t mbPaused;           // +0x48
};

sGameTime* GameTimeManager();   // 0x00b3d380

class cCommScreen {
public:
    bool IsActive();            // 0x00ae9390 ret 0
};

cCommScreen* CommManager();     // 0x00b3d4a0

// ---------------------------------------------------------------------------
// civilization mode strategy
// ---------------------------------------------------------------------------
class cCivModeState;

class cCommRelay {
public:
    void OnMessage(void* pWindow, uint32_t nValue);   // 0x00e35290 ret 8
    void OnEnd();                                     // 0x00e352b0 ret 0
};

class cCivModeState {
public:
    uint8_t mnPad00[0xe4];      // +0x00
    cCommRelay* mpRelay;        // +0xe4
    uint8_t mnPadE8[0x58];      // +0xe8
    int32_t mnSelectedWeapon;   // +0x140
    void EnterWeaponMode(int32_t nKind);   // 0x00cf1be0 ret 4
};

class cCivModeStrategy {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8)
    virtual void ExecuteMessage(uint32_t nMessage, uint32_t nArg);   // +0x24
    cCivModeState* GetState();                     // 0x00cf74f0 ret 0
    void OnTechLevelUpgradeButtonPress();          // 0x00cf8160 ret 0
};

cCivModeStrategy* GetCivModeStrategy();            // 0x00cf74c0

// ---------------------------------------------------------------------------
// UI objects
// ---------------------------------------------------------------------------
class cRenderCtx;
class DSub;

class cIWinProc {
public:
    virtual bool DoMessage(void* pWindow, cMessage* pMsg);   // overridden by cSPUIGlobalUICiv
    virtual void Release();
    VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18)
    virtual uint32_t GetCommandId(uint32_t nArg);            // +0x4c
    uint32_t FireSelectedCommEvent();                        // 0x00bf0810 ret 0
};

class cUIWindow {
public:
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual cUIWindow* FindWindowByID(uint32_t nID);         // +0x0c
    VSLOT(4)
    virtual cUIWindow* GetRenderable();                      // +0x14
    VSLOT(6)
    virtual uint32_t GetID();                                // +0x1c
    VSLOT(8) VSLOT(9)
    virtual void SetFlag(uint32_t nFlag, bool bValue);       // +0x28
    VSLOT(11) VSLOT(12) VSLOT(13)
    virtual const float* GetArea();                          // +0x38
    VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
    VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30)
    virtual void SetVisible(uint32_t nVisible, bool bFlag);   // +0x7c
    VSLOT(32) VSLOT(33) VSLOT(34) VSLOT(35)
    virtual void Invalidate();                               // +0x90
    VSLOT(37) VSLOT(38) VSLOT(39) VSLOT(40) VSLOT(41)
    virtual DSub* GetSub(uint32_t nID);                      // +0xa8
    VSLOT(43) VSLOT(44) VSLOT(45) VSLOT(46) VSLOT(47) VSLOT(48) VSLOT(49) VSLOT(50) VSLOT(51)
    VSLOT(52) VSLOT(53) VSLOT(54) VSLOT(55) VSLOT(56) VSLOT(57) VSLOT(58) VSLOT(59)
    virtual cUIWindow* GetChild(uint32_t nID, uint32_t nArg);   // +0xf0
    cRenderCtx* mpRenderCtx;    // +0xf4
};

class DSub {
public:
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual DSub* GetSub(uint32_t nID);                      // +0x0c
    uint8_t mnPad10[0x0c];      // +0x10
    int32_t mnWidth;            // +0x1c
    int32_t mnHeight;           // +0x20
    int32_t GetField10(int32_t nIndex);                      // 0x00830cf0 ret 4
    void GetPair38(float* pOut, int32_t nCount);             // 0x00830d30 ret 8
    void GetPair40(float* pOut, int32_t nCount);             // 0x00830d60 ret 8
};

class cRenderCtx {
public:
    void* Begin2D(void* pRenderMode);    // 0x0095bc10 ret 4
    void End2D();                        // 0x0095bb20 ret 0
};

struct sBatch2D {
    VSLOT(0)
    virtual void SetColor(uint32_t nColor);   // +0x04
};

void DrawArc(void* pBatch, float fA, float fB, float fC, uint32_t nColor0, uint32_t nColor1,
             float fD, float fE, int32_t nArg, float fF);   // 0x00805740

void SetTooltipText(cUIWindow* pWindow, const wchar_t* pText, int32_t nCount, int32_t nFlag);
                                                             // 0x00806de0
bool SetTooltipByKey(cUIWindow* pWindow, uint32_t nValue, const wchar_t* pText, int32_t nArg);
                                                             // 0x00807c70

const wchar_t* GetTypeNameFromRwType(uint32_t nType);   // 0x00e043c0
const wchar_t* GetKindName(int32_t nKind);              // 0x00e04330
const wchar_t* GetRwTypeNameB(uint32_t nType);          // 0x00e044b0
const wchar_t* GetRwTypeNameC(uint32_t nType);          // 0x00e04450

// ---------------------------------------------------------------------------
// civ HUD state
// ---------------------------------------------------------------------------
struct tCommButton {                // base class comm-rel button record
    void* mpObject;                 // +0x00
    uint32_t mnPad04;               // +0x04
    uint32_t mnPad08;               // +0x08
};

class cSPUIGlobalUI {
public:
    VSLOT(0)
    cSPUIGlobalUI();
    void Construct();                          // 0x00e03ab0
    cUIWindow* FindWindowByID(uint32_t nID);   // 0x00e012b0 ret 4
    uint8_t mnPad04[0x20];                     // +0x04
    tCommButton mCommButtons[4];               // +0x24
    uint8_t mnPad54[0x14];                     // +0x54
};

class cUIRefCount {
public:
    virtual void _v0();
    int32_t mnRefCount;             // +0x04
    cUIRefCount() : mnRefCount(0) {}
};

class cSPUIGlobalUICiv;

struct tCivButton {                 // superweapon button record, 12 bytes
    uint32_t mnObject;              // +0x00
    uint8_t mbFlag04;               // +0x04
    uint8_t mbFlag05;               // +0x05
    uint8_t mnPad06[0x02];          // +0x06
    cIWinProc* mpObject;            // +0x08
};

struct sCivIndexNode {
    sCivIndexNode* mpLeft;          // +0x00
    sCivIndexNode* mpRight;         // +0x04
    sCivIndexNode* mpParent;        // +0x08
    uint32_t mnColor;               // +0x0c
    uint32_t mnKey;                 // +0x10
    uint32_t mnValue;               // +0x14
};

struct cCivIndexMap {
    uint32_t mnPad00;               // +0x00
    sCivIndexNode* mpAnchorLeft;    // +0x04
    sCivIndexNode* mpAnchorRight;   // +0x08
    sCivIndexNode* mpAnchorParent;  // +0x0c
    uint8_t mbAnchorColor;          // +0x10
    uint8_t mnPad11[0x03];          // +0x11
    uint32_t mnSize;                // +0x14
    void find(const uint32_t& key, sCivIndexNode** ppResult);   // 0x00e5c780 ret 8
};

sCivIndexNode* RBTreeIncrement(sCivIndexNode* pNode);                 // 0x00921580
void RBTreeErase(sCivIndexNode* pAnchor, sCivIndexNode* pNode);       // 0x00921880

class cMessage {
public:
    uint8_t mnPad00[0x08];          // +0x00
    uint32_t mnId;                  // +0x08
    uint32_t mnParam;               // +0x0c
    uint8_t mnPad10[0x08];          // +0x10
    cUIWindow* mpWindow;            // +0x18
};

class cSPUIGlobalUICiv : public cSPUIGlobalUI, public cUIRefCount, public cIWinProc {
public:
    cSPUIGlobalUICiv();
    bool DoMessage(void* pWindow, cMessage* pMsg);    // overrides cIWinProc::DoMessage
    void RemoveCivFeedback(cCivilization* pCiv);                 // 0x00e052d0
    void SuperweaponClick(uint32_t nButtonId);                   // 0x00e05530
    void SelectStance(int32_t nStance);                          // 0x00e05870
    void SyncStanceWithSelection(int32_t nStance);               // 0x00e05930
    void SetButtonTooltip(uint32_t nWindowId, uint32_t nTextA, uint32_t nTextB, int32_t nCount);
                                                                 // 0x00e05ab0
    void SyncSuperweaponButton(uint32_t nWindowId, int32_t* pnState, int32_t nIndex);
    void DeactivateCommRelPanel(int32_t nIndex);                 // 0x00e04960
    void SetMinimapStateFromButton(int32_t nState);              // 0x00e04560
    void SetStanceButtonsState(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e);
                                                                 // 0x00e046b0
    uint32_t mnPad74;               // +0x74
    uint32_t mnPad78;               // +0x78
    uint32_t mnPad7c;               // +0x7c
    uint32_t mnPad80;               // +0x80
    uint32_t mnPad84;               // +0x84
    uint8_t mbMinimapVisible;       // +0x88
    uint8_t mbPad89;                // +0x89
    uint8_t mnPad8a[0x02];          // +0x8a
    tCivButton mButtons[4];         // +0x8c
    float mfCooldown;               // +0xbc
    uint32_t mnPadC0;               // +0xc0
    uint32_t mnPadC4;               // +0xc4
    uint8_t mnPadC8[0x10];          // +0xc8
    uint8_t mbCooldownShown[4];     // +0xd8
    cCivIndexMap mCivToIndex;       // +0xdc
};

bool DrawSuperweaponCooldown(cUIWindow* pButton, cMessage* pMsg);   // 0x00e05590
void UpdateSuperweaponTooltip(cUIWindow* pWindow, uint32_t nRwType);   // 0x00e05de0
int32_t GetSuperweaponKind(uint32_t nButtonId);                        // 0x00e053c0

// ---------------------------------------------------------------------------
// cSPUIGlobalUICiv
// ---------------------------------------------------------------------------
// @ 0x00e052d0
void cSPUIGlobalUICiv::RemoveCivFeedback(cCivilization* pCiv) {
    sCivIndexNode* pNode;
    mCivToIndex.find((const uint32_t&)pCiv, &pNode);
    sCivIndexNode* pAnchor = (sCivIndexNode*)&mCivToIndex.mpAnchorLeft;
    if (pNode != pAnchor) {
        uint32_t nIndex = pNode->mnValue;
        DeactivateCommRelPanel((int32_t)nIndex);
        cIWinProc** ppObject = &mButtons[nIndex].mpObject;
        cIWinProc* pObject = *ppObject;
        if (pObject) {
            *ppObject = 0;
            pObject->Release();
        }
        --mCivToIndex.mnSize;
        RBTreeIncrement(pNode);
        RBTreeErase(pAnchor, pNode);
        EASTL_allocator_deallocate(pNode);
    }

    bool bHasOther = false;
    cCivilization* pPlayer = NounManager()->GetPlayerCivilization();
    sCivilizationList* pCivs = NounManager()->GetCivilizationList();
    cCivilization** it = pCivs->mpBegin;
    while (it != pCivs->mpEnd && !bHasOther) {
        cCivilization* pIter = *it;
        if (pIter != pPlayer && pIter != pCiv && !pIter->mbHidden)
            bHasOther = true;
        ++it;
    }
    mbMinimapVisible = mbMinimapVisible && bHasOther;
    SetMinimapStateFromButton(0);
}

// @ 0x00e053c0
int32_t GetSuperweaponKind(uint32_t nButtonId) {
    int32_t nKind = -1;
    cCivilization* pPlayer = NounManager()->GetPlayerCivilization();
    if (!pPlayer)
        return nKind;
    if (nButtonId == 0x5a55b40) {
        switch (pPlayer->GetSuperweaponSpeccy()) {
        case 0: nKind = 2; break;
        case 1: nKind = 8; break;
        case 2: nKind = 5; break;
        }
    } else {
        SimpleVectorU32 models = {0, 0, 0};
        cTerrainEditor* pTerrain = NounManager()->GetCurrentTerrainSphere();
        if (pTerrain) {
            VectorAddModels(pTerrain->mnModel0, &models);
            VectorAddModels(pTerrain->mnModel1, &models);
            VectorAddModels(pTerrain->mnModel2, &models);
        }
        uint32_t nCount = (uint32_t)(models.mpEnd - models.mpBegin);
        for (uint32_t i = 0; i < nCount; ++i) {
            int32_t nModelKind = pPlayer->GetRwTypeKind(models.mpBegin[i]);
            bool bMatch;
            switch (nModelKind) {
            case 0: case 6: case 11: bMatch = (nButtonId == 0x5a55b20); break;
            case 1: case 4: case 7: bMatch = (nButtonId == 0x5a55b30); break;
            case 3: case 9: case 10: bMatch = (nButtonId == 0x5a55b10); break;
            default: bMatch = false; break;
            }
            if (bMatch) {
                nKind = nModelKind;
                if (nKind != -1)
                    break;
            }
        }
        FreeSimpleVector(&models);
    }
    return nKind;
}

// @ 0x00e05530
void cSPUIGlobalUICiv::SuperweaponClick(uint32_t nButtonId) {
    int32_t nKind = GetSuperweaponKind(nButtonId);
    if (nKind == -1)
        return;
    cCivModeState* pState = GetCivModeStrategy()->GetState();
    if (pState->mnSelectedWeapon != nKind) {
        GetCivModeStrategy()->GetState()->EnterWeaponMode(nKind);
        return;
    }
    GetCivModeStrategy()->ExecuteMessage(0x1b, 0);
}

// @ 0x00e05590
bool DrawSuperweaponCooldown(cUIWindow* pButton, cMessage* pMsg) {
    uint32_t nButtonId = pButton->GetID();
    cCivilization* pPlayer = NounManager()->GetPlayerCivilization();
    if (!pPlayer)
        return false;
    int32_t nKind = GetSuperweaponKind(nButtonId);
    if (nKind == -1)
        return false;
    if (!pPlayer->SuperweaponOnCooldown(nKind))
        return false;
    cUIWindow* pRenderable = pButton->GetRenderable();
    pRenderable->GetRenderable()->SetFlag(0, pButton != 0);
    pButton->GetRenderable()->SetFlag(0, true);

    cRenderCtx* pCtx = (cRenderCtx*)pMsg->mpWindow;
    DSub* pSub = pButton->GetSub(0x53eb526);
    float* pArea = (float*)pButton->GetArea();
    int32_t nWidth = pSub->mnWidth;
    int32_t nHeight = pSub->mnHeight;
    float mfHalfW = (pArea[2] - pArea[0]) * 0.5f;
    float mfHalfH = (pArea[3] - pArea[1]) * 0.5f;
    float mfW = (float)nWidth;
    float mfH = (float)nHeight;
    float pair38[4];
    float pair40[4];
    pSub->GetPair38(pair38, 4);
    pSub->GetPair40(pair40, 4);
    float mfA = pair38[0] * mfW * 0.5f;
    float mfB = pair38[1] * mfH * 0.5f;
    float mfRadius = mfA < mfB ? mfA : mfB;
    sBatch2D* pBatch = (sBatch2D*)pCtx->Begin2D(0);
    pBatch->SetColor(0xbf0000ff);
    float mfRatio = pPlayer->GetSuperweaponCooldown(nKind) * 0.0f;
    DrawArc(pBatch, pArea[0] + mfHalfW, pArea[1] + mfHalfH, mfRadius, 0xbf0000ff, 0xbf0000ff,
            mfRatio, mfRatio, 0, 0.0f);
    pCtx->End2D();
    return true;
}

// @ 0x00e057a0
cSPUIGlobalUICiv::cSPUIGlobalUICiv()
    : mnPad74(0)
    , mnPad78(0)
    , mnPad7c(0)
    , mnPad80(0)
    , mnPad84(0)
    , mbMinimapVisible(0)
    , mbPad89(0) {
    for (int i = 0; i < 4; ++i)
        mButtons[i].mpObject = 0;
    mfCooldown = 0.0f;
    mnPadC0 = 0;
    mnPadC4 = 0;
    mCivToIndex.mpAnchorRight = 0;
    mCivToIndex.mpAnchorParent = 0;
    mCivToIndex.mbAnchorColor = 0;
    mCivToIndex.mpAnchorParent = 0;
    mCivToIndex.mbAnchorColor = 0;
    mCivToIndex.mnSize = 0;
    mCivToIndex.mpAnchorRight = (sCivIndexNode*)&mCivToIndex.mpAnchorLeft;
    mCivToIndex.mpAnchorLeft = (sCivIndexNode*)&mCivToIndex.mpAnchorLeft;
}

// @ 0x00e05870
void cSPUIGlobalUICiv::SelectStance(int32_t nStance) {
    SimpleVectorU32 selection = {0, 0, 0};
    GetGameTerrainCursor()->GetSelection(&selection, 0x137e8e0);
    for (uint32_t* it = selection.mpBegin; it != selection.mpEnd; ++it) {
        cVehicle* pVehicle = 0;
        if (*it)
            pVehicle = ((cIObject*)*it)->AsVehicle(0x137e8e0);
        pVehicle->SetStance(nStance, false);
    }
    for (uint32_t* it = selection.mpBegin; it < selection.mpEnd; ++it) {
        if (*it)
            ((cIObject*)*it)->Release();
    }
    FreeSimpleVector(&selection);
}

// @ 0x00e05930
void cSPUIGlobalUICiv::SyncStanceWithSelection(int32_t nStance) {
    if (!GetGameTerrainCursor()->HasSelection()) {
        SetStanceButtonsState(0, 0, 0, 0, 0);
        return;
    }
    SimpleVectorU32 selection = {0, 0, 0};
    GetGameTerrainCursor()->GetSelection(&selection, 0x137e8e0);
    bool bSetStance = false;
    bool bHasStance1 = false;
    bool bHasStance0 = false;
    if (nStance != -1) {
        bSetStance = true;
        if (nStance == 0)
            bHasStance0 = true;
        else if (nStance == 1)
            bHasStance1 = true;
    }
    for (uint32_t* it = selection.mpBegin; it != selection.mpEnd; ++it) {
        if (bHasStance0 && bHasStance1)
            break;
        cVehicle* pVehicle = 0;
        if (*it)
            pVehicle = ((cIObject*)*it)->AsVehicle(0x137e8e0);
        if (bSetStance) {
            pVehicle->SetStance(nStance, false);
        } else {
            switch (pVehicle->mnStance) {
            case 0: bHasStance0 = true; break;
            case 1: bHasStance1 = true; break;
            }
        }
    }
    bool bBoth = bHasStance0 && bHasStance1;
    SetStanceButtonsState(bHasStance0, 1, bHasStance1, 1, bBoth);
    for (uint32_t* it = selection.mpBegin; it < selection.mpEnd; ++it) {
        if (*it)
            ((cIObject*)*it)->Release();
    }
    FreeSimpleVector(&selection);
}

// @ 0x00e05ab0
void cSPUIGlobalUICiv::SetButtonTooltip(uint32_t nWindowId, uint32_t nTextA, uint32_t nTextB,
                                        int32_t nCount) {
    cUIWindow* pWindow = FindWindowByID(nWindowId);
    sString16 text;
    if (nCount > 0) {
        cString string(0xc0152a6d, nTextA, 0);
        const wchar_t* pText = string.GetText();
        text.assign(pText, pText + wcslen(pText));
    } else {
        cString string(0xc0152a6d, nTextB, 0);
        const wchar_t* pText = string.GetText();
        text.assign(pText, pText + wcslen(pText));
    }
    SetTooltipText(pWindow, text.mpBegin, -1, 1);
    pWindow->Invalidate();
    text.Dtor();
}

// @ 0x00e05bb0
bool cSPUIGlobalUICiv::DoMessage(void* pWindow, cMessage* pMsg) {
    bool bResult = false;
    if (pMsg->mnId == 0x1b) {
        cUIWindow* pSource = pMsg->mpWindow;
        if ((uint32_t)(pSource->GetID() - 0x4655fd5) <= 3) {
            cIWinProc* pButton = mButtons[pSource->GetID() - 0x4655fd5].mpObject;
            cCivModeState* pState = GetCivModeStrategy()->GetState();
            ((cCommRelay*)pState->mpRelay)->OnMessage(pSource, pButton->GetCommandId(1));
            return bResult;
        }
    } else if (pMsg->mnId == 0x1c) {
        cUIWindow* pSource = pMsg->mpWindow;
        if ((uint32_t)(pSource->GetID() - 0x4655fd5) <= 3) {
            cCivModeState* pState = GetCivModeStrategy()->GetState();
            ((cCommRelay*)pState->mpRelay)->OnEnd();
            return bResult;
        }
    } else if (pMsg->mnId == 0x287259f6) {
        if (CommManager()->IsActive())
            return bResult;
        uint32_t nCommand = pMsg->mnParam;
        bool bStance1 = false;
        bool bStance0 = false;
        switch (nCommand) {
        case 0x5a55b10:
        case 0x5a55b20:
        case 0x5a55b30:
        case 0x5a55b40:
            SuperweaponClick(nCommand);
            bResult = true;
            break;
        case 0x4655fd5:
        case 0x4655fd6:
        case 0x4655fd7:
        case 0x4655fd8:
            if (!(GameTimeManager()->mbPaused & 1)) {
                mButtons[nCommand - 0x4655fd5].mpObject->FireSelectedCommEvent();
                bResult = true;
            }
            break;
        case 0x4c61b50:
            bStance0 = true;
            bStance1 = true;
            SetStanceButtonsState(bStance1, 1, bStance0, 1, 0);
            SelectStance(bStance0 ? 1 : 0);
            break;
        case 0x4c61dd8:
            bStance1 = true;
            SetStanceButtonsState(bStance1, 1, bStance0, 1, 0);
            SelectStance(bStance0 ? 1 : 0);
            break;
        case 0x562a141:
            SetMinimapStateFromButton(0);
            bResult = true;
            break;
        case 0x6453746:
            GetCivModeStrategy()->OnTechLevelUpgradeButtonPress();
            break;
        }
        return bResult;
    } else if (pMsg->mnId == 0xd) {
        return DrawSuperweaponCooldown((cUIWindow*)pWindow, pMsg);
    }
    return bResult;
}

// @ 0x00e05de0
void UpdateSuperweaponTooltip(cUIWindow* pWindow, uint32_t nRwType) {
    cCivilization* pPlayer = NounManager()->GetPlayerCivilization();
    if (!pPlayer)
        return;
    int32_t nLevel = pPlayer->GetSuperweaponLevel(nRwType);
    sString16 text;
    text.append(0, 0);
    {
        cString string(0x9a5acf10, (uint32_t)GetTypeNameFromRwType(nRwType), 0);
        const wchar_t* pText = string.GetText();
        text.append(pText, pText + wcslen(pText));
    }
    wchar_t buffer[0x40];
    uint16_t tag[2];
    tag[0] = 0x268a;
    tag[1] = 0;
    FormatMoney((double)pPlayer->InteractionScore(nRwType), buffer, 0x40, L"%-F%-p", tag);
    {
        sString16 formatted;
        WStr_Format(&formatted, L" (%ls) - ", buffer);
        text.append(formatted.mpBegin, formatted.mpEnd);
    }
    if (pPlayer->GetInteractionLevel() < nLevel) {
        const wchar_t* pName;
        switch (nLevel) {
        case 2: pName = (const wchar_t*)0x62e9ec2; break;
        case 4: pName = (const wchar_t*)0x62e9ec6; break;
        case 6: pName = (const wchar_t*)0x62e9eca; break;
        default: pName = (const wchar_t*)0x62eabde; break;
        }
        cString string(0xc0152a6d, (uint32_t)pName, 0);
        const wchar_t* pText = string.GetText();
        text.append(pText, pText + wcslen(pText));
    } else {
        cString string(0x9a5acf10, (uint32_t)GetRwTypeNameB(nRwType), 0);
        const wchar_t* pText = string.GetText();
        text.append(pText, pText + wcslen(pText));
    }
    text.append((const wchar_t*)0x147f418, (const wchar_t*)0x147f418 + wcslen((const wchar_t*)0x147f418));
    {
        cString string(0x841536d5, (uint32_t)GetRwTypeNameC(nRwType), 0);
        const wchar_t* pText = string.GetText();
        text.append(pText, pText + wcslen(pText));
    }
    text.append((const wchar_t*)0x147f414, (const wchar_t*)0x147f414 + wcslen((const wchar_t*)0x147f414));
    SetTooltipText(pWindow, text.mpBegin, -1, 1);
    text.Dtor();
}

// @ 0x00e060c0
void cSPUIGlobalUICiv::SyncSuperweaponButton(uint32_t nWindowId, int32_t* pnState, int32_t nIndex) {
    cCivilization* pPlayer = NounManager()->GetPlayerCivilization();
    if (!pPlayer)
        return;
    cUIWindow* pWindow = FindWindowByID(nWindowId);
    int32_t nSelected = GetCivModeStrategy()->GetState()->mnSelectedWeapon;
    int32_t nKind = GetSuperweaponKind(nWindowId);
    if (nKind != *pnState) {
        *pnState = nKind;
        SetTooltipByKey(pWindow, mnPadC4, GetKindName(nKind), -1);
    }
    UpdateSuperweaponTooltip(pWindow, (uint32_t)nKind);
    bool bVisible = (nKind != -1);
    pWindow->SetVisible(1, bVisible);
    pWindow->SetVisible(2, pPlayer->CanUseSuperweapon(nKind));
    cUIWindow* pInner = pWindow->FindWindowByID(0x8ed27e7a);
    pInner->SetFlag(4, nSelected == nKind);
    cUIWindow* pNext = FindWindowByID(nWindowId + 1);
    if (pNext)
        pNext->SetVisible(1, !bVisible);
    if (nKind != -1) {
        if (pPlayer->SuperweaponOnCooldown(nKind)) {
            pWindow->Invalidate();
            mbCooldownShown[nIndex] = 1;
        } else if (mbCooldownShown[nIndex]) {
            pWindow->Invalidate();
            mbCooldownShown[nIndex] = 0;
        }
    }
}

// @ 0x00e060c0 alternate marker for the same symbol family (see SyncSuperweaponButton)
