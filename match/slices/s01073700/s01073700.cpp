// Slice s01073700 (batch op3_big) — 0x01073700, 3229 bytes.
//
// SP::cSPUISpace::Init()   (__thiscall, no args)
//
// The name comes from the dev PDB.  Retail member offsets differ from the dev layout, so
// cSPUISpace below is declared with the retail offsets this function uses; members without
// a recovered name are named by role or offset.  Callees without a recovered name keep their
// FUN_ address names.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (SSE scalar float stores, x87 float
// arguments, a cString local with a dtor but no EH frame -> no /EHsc).

#include "types.h"

#pragma pack(push, 8)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};

namespace Math {
struct Rectangle {
    float x1, y1, x2, y2;
    float GetBottom() const { return y2; }
};
}

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey() {}
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};

// EA math helper, hand-written SSE in the original (FloorToInt).
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                       // 0x00f473a0
void* GetUIAllocator();                                               // 0x009512c0
void* operator new(unsigned int size, unsigned int align, const char* name,
                   void* pAllocator);                                 // 0x009512d0

extern const char kAllocName_13f6b3c[];                               // 0x013f6b3c
#define UI_NEW new (kAllocName_13f6b3c, 0, 0, 0, 0)

namespace EA {
template <class T> class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    AutoRefCount& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
}

// Objects whose refcount lives at +4 and whose Release deletes through the virtual
// deleting dtor (RefCountTemplate, inlined).
class cRefCounted {
public:
    virtual ~cRefCounted();
    int mnRefCount;
    int AddRef() { return ++mnRefCount; }
    int Release()
    {
        int n = mnRefCount + -1; mnRefCount = n; if (n == 0) {
            mnRefCount = 1;
            delete this;
            return 0;
        }
        return mnRefCount;
    }
};

class IWinProc {
public:
    virtual int AddRef();                                            // +0x0
    virtual int Release();                                           // +0x4
};

namespace EA { namespace UTFWin {
class IWindow {
public:
    virtual int AddRef();                                            // +0x0
    virtual int Release();                                           // +0x4
    virtual void _v08();
    virtual void* Cast(uint32_t typeID);                             // +0xc
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34();
    virtual const Math::Rectangle& GetRealArea();                    // +0x38
    virtual void _v3c(); virtual void _v40(); virtual void _v44(); virtual void _v48();
    virtual void _v4c(); virtual void _v50(); virtual void _v54(); virtual void _v58();
    virtual void _v5c(); virtual void _v60(); virtual void _v64(); virtual void _v68();
    virtual void _v6c(); virtual void _v70(); virtual void _v74(); virtual void _v78();
    virtual void SetFlag(int flag, bool value);                      // +0x7c
    virtual void _v80(); virtual void _v84(); virtual void _v88(); virtual void _v8c();
    virtual void _v90(); virtual void _v94(); virtual void _v98(); virtual void _v9c();
    virtual void _va0(); virtual void _va4(); virtual void _va8(); virtual void _vac();
    virtual void _vb0(); virtual void _vb4(); virtual void _vb8(); virtual void _vbc();
    virtual void _vc0(); virtual void _vc4(); virtual void _vc8(); virtual void _vcc();
    virtual void _vd0(); virtual void _vd4();
    virtual void AddWindow(IWindow* pWindow);                        // +0xd8
    virtual void _vdc(); virtual void _ve0(); virtual void _ve4(); virtual void _ve8();
    virtual void _vec(); virtual void _vf0(); virtual void _vf4(); virtual void _vf8();
    virtual void _vfc(); virtual void _v100();
    virtual void AddWinProc(IWinProc* pProc);                        // +0x104
};
} }
using EA::UTFWin::IWindow;

// UI meter component reached through IWindow::Cast(0x106f146)
struct cMeterHolder {
    uint32_t pad[0x20c / 4];
    class cMeter {
    public:
        virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
        virtual void _v10();
        virtual void SetValue(int value);                            // +0x14
    } mMeter;                                   // +0x20c
};

// Ref-counted objects with a virtual dtor in slot 0 and AddRef/Release in slots 1/2.
class cSPUILayout {
public:
    virtual ~cSPUILayout();                                          // +0x0
    virtual int AddRef();                                            // +0x4
    virtual int Release();                                           // +0x8
    uint32_t pad04[(0x18 - 0x4) / 4];
    cSPUILayout();                                                   // 0x00810000
    bool Init(const wchar_t* name, uint32_t groupID, bool visible, uint32_t parentID);   // 0x00812160
    bool Init(const ResourceKey& key, bool visible, uint32_t parentID);                  // 0x008120d0
    void SetVisibility(bool visible);                                // 0x00810590
    IWindow* FindWindowByID(uint32_t id, bool recursive);            // 0x008105b0
};

class cSPUIGlobalUI {
public:
    virtual void _v00(); virtual void _v04();
    virtual void Load(const void* pParams);                          // +0x8
    uint32_t pad04[(0x68 - 0x4) / 4];
    cSPUIGlobalUI();                                                 // 0x00e03ab0
    IWindow* FindWindowByID(uint32_t id);                            // 0x00e012b0
    cSPUILayout* GetLayout();                                        // 0x0093b6c0 (shared getter, returns +8)
};
extern const char g_GlobalUIParams[];                                // 0x015b9294

class cWindowGroup : public cRefCounted {   // 0x38 bytes, "Simulator/Space/UI"
public:
    uint32_t pad08[(0x38 - 0x8) / 4];
    cWindowGroup(cSPUILayout* pLayout, const void* pName);           // 0x00e28a10
    void FUN_00e29c80();                                             // 0x00e29c80
};
extern const char g_WindowGroupName[];                               // 0x0149c47c

namespace UI {
class CursorAttachment : public IWinProc {
public:
    uint32_t pad04[(0x100 - 0x4) / 4];
    CursorAttachment();                                              // 0x00e2c920
};

class cUITimedTooltip : public cRefCounted {
public:
    uint32_t pad08[(0x60 - 0x8) / 4];
    cUITimedTooltip();                                               // 0x00e36480
    void Init(ResourceKey layoutKey, uint32_t windowID, int delayMS, int fadeMS);  // 0x00e36b30
};

class CRG_Minimap : public IWinProc, public IWindow {
public:
    virtual int AddRef();
    virtual int Release();
    uint32_t pad08[(0x344 - 0x8) / 4];
    Vector3 mCameraDir;                         // +0x344
    uint32_t pad350[(0x9a8 - 0x350) / 4];
    CRG_Minimap(int width, int height, const Vector3& dir, const Vector3& up, float f, bool b);  // 0x00e0fc90
    void SetUp(const Vector3& up);                                   // 0x00e0c1f0
};

class Posse {
public:
    virtual int AddRef();                                            // +0x0
    virtual int Release();                                           // +0x4
    virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4c();
    virtual void _v50(); virtual void _v54(); virtual void _v58(); virtual void _v5c();
    virtual void _v60(); virtual void _v64(); virtual void _v68(); virtual void _v6c();
    virtual void _v70(); virtual void _v74(); virtual void _v78(); virtual void _v7c();
    virtual bool Init(const wchar_t* name, uint32_t groupID);        // +0x80
    virtual void _v84(); virtual void _v88(); virtual void _v8c();
    virtual void SetSize(float a, float b, int c, int d);            // +0x90
    virtual void _v94(); virtual void _v98(); virtual void _v9c();
    virtual void _va0(); virtual void _va4(); virtual void _va8(); virtual void _vac();
    virtual void _vb0(); virtual void _vb4();
    virtual void SetCaption(const wchar_t* text);                    // +0xb8
    virtual void _vbc();
    virtual void SetVisible(bool visible);                           // +0xc0

    struct Entry { uint32_t a, b; };
    uint32_t pad04[(0xa4 - 0x4) / 4];
    Entry* mpBegin;                             // +0xa4
    Entry* mpEnd;                               // +0xa8
    uint32_t padac[(0x20c - 0xac) / 4];
    Posse();                                                         // 0x00e25710
    int size() const { return (int)(mpEnd - mpBegin); }
};

class cUIFlashWindowManager {
public:
    virtual ~cUIFlashWindowManager();
    virtual int AddRef();                                            // +0x4
    virtual int Release();                                           // +0x8
    uint32_t pad04[(0x58 - 0x4) / 4];
    cUIFlashWindowManager();                                         // 0x00e31050
    void FUN_00e2f370();                                             // 0x00e2f370
};
}

class cSpaceWinProc : public IWinProc {     // 0xc0 bytes, "Simulator"
public:
    uint32_t pad04[(0xc0 - 0x4) / 4];
    cSpaceWinProc();                                                 // 0x00fe75d0
};

class cRefObject16 {                        // 0x10 bytes, singleton at 0x016e2234
public:
    virtual void _v00();
    virtual int AddRef();                                            // +0x4
    uint32_t pad04[(0x10 - 0x4) / 4];
    cRefObject16();                                                  // 0x01066880
};
extern cRefObject16* g_pSpaceUIObject;                               // 0x016e2234

class cGameModeC {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34();
    virtual void AddObject(cRefObject16* p, bool b);                 // +0x38
};
cGameModeC* FUN_00b3d230();                                          // 0x00b3d230

namespace EA { namespace Messaging {
class IHandler;
class IMessageServer {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20();
    virtual void AddHandler(IHandler* pHandler, uint32_t messageID); // +0x24
};
class IHandler {
public:
    virtual void _v00();
};
} }
using EA::Messaging::IHandler;
using EA::Messaging::IMessageServer;

// Message-ID registration helper embedded in cSPUISpace at +0x56c (inlined).
struct cMessageRegistrar {
    IMessageServer* mpServer;
    IHandler* mpHandler;
    const uint32_t* mpMessageIDs;
    uint32_t mnMessageCount;
    uint32_t mnFlags;
    void Init(IMessageServer* pServer, IHandler* pHandler, const uint32_t* pIDs, uint32_t count)
    {
        mpServer = pServer;
        mpHandler = pHandler;
        mpMessageIDs = pIDs;
        mnMessageCount = count;
        mnFlags = 0;
        if (pServer && pHandler) {
            for (uint32_t i = 0; i < count; i++)
                pServer->AddHandler(pHandler, pIDs[i]);
        }
    }
};
extern const uint32_t kSpaceUIMessageIDs[25];                        // 0x0149c418
extern const uint32_t kMeterWindowIDs[5];                            // 0x0149c158

namespace ArgScript {
class cCommandBase {
public:
    virtual ~cCommandBase();
    uint32_t pad04[3];
    cCommandBase();                                                  // 0x0083c800
};
}

namespace SP {

class cString {   // retail size 0x14
public:
    uint32_t pad[5];
    cString();                                                       // 0x006b5060
    ~cString();                                                      // 0x006b5240
    bool Load(uint32_t instanceID, uint32_t tableID, int a);         // 0x006b54b0
    const wchar_t* GetText();                                        // 0x006b55c0
};

namespace SpaceCheats {
class cCommandToolCheat : public ArgScript::cCommandBase {
public:
    virtual void ParseLine();
    cCommandToolCheat() {}
};
}

class cCheatManager {
public:
    void AddCheat(ArgScript::cCommandBase*) {}
};
cCheatManager* CheatManager();                                       // 0x0067de20
IMessageServer* MessageServer();                                     // 0x0067dcc0

class cEmpire {
public:
    const ResourceKey& GetUFOKey();                                  // 0x00c326b0
};
class cSPLivingUniverse {
public:
    static cEmpire* GetPlayerEmpire();                               // 0x01021300
};
class cStarMap {
public:
    void FilterHelperRebuildAll();                                   // 0x01048ce0
};
cStarMap* FUN_01046fc0();                                            // 0x01046fc0

struct cGameData {
    uint32_t pad[0x714 / 4];
    int mType;                                  // +0x714
};
struct cGameDataVector {
    cGameData** mpBegin;
    cGameData** mpEnd;
    cGameData* const* begin() const { return mpBegin; }
    cGameData* const* end() const { return mpEnd; }
};
struct cGameDataList {
    uint32_t pad00;
    cGameDataVector mData;                      // +0x4
};
typedef void (*tGameDataFn)();
class cGameNounManager {
public:
    cGameDataList* GetGameDataVector(tGameDataFn a, tGameDataFn b, tGameDataFn c, tGameDataFn d,
                                     const void* pType);             // 0x00b21340
};
cGameNounManager* NounManager();                                     // 0x00b3d300
void FUN_00cd7d10(); void FUN_00d3d420(); void FUN_00ad48b0(); void FUN_00b1e500();
extern const char g_18ebadc[];                                       // 0x018ebadc

bool world(int id);                                                  // 0x00685520

class cSPUISpace;
struct cSpaceGame {
    uint32_t pad[0x14 / 4];
    cSPUISpace* mpUI;                           // +0x14
};
cSpaceGame* SpaceGameGet();                                          // 0x01002bd0

class cSPUISpace : public IWinProc {
public:
    uint32_t pad04[2];
    IHandler mHandler;                                               // +0xc (IHandlerRC base)
    uint32_t pad10[(0x10c - 0x10) / 4];
    cString mNewUFOScannedText;                                      // +0x10c
    cString mUFOAlreadyScannedText;                                  // +0x120
    uint32_t pad134[(0x224 - 0x134) / 4];
    cSPUIGlobalUI* mpGlobalUI;                                       // +0x224
    EA::AutoRefCount<cWindowGroup> mpWindowGroup;                    // +0x228
    EA::AutoRefCount<cSPUILayout> mpStarRolloverLayout;              // +0x22c
    EA::AutoRefCount<cSPUILayout> mpStarTooltipLayout;               // +0x230
    EA::AutoRefCount<cSPUILayout> mpPlanetTooltipLayout;             // +0x234
    uint32_t pad238[(0x258 - 0x238) / 4];
    EA::AutoRefCount<cSPUILayout> mpOverlayLayout;                   // +0x258
    uint32_t pad25c[(0x2f8 - 0x25c) / 4];
    int mn2f8;                                                       // +0x2f8
    uint32_t pad2fc[(0x31c - 0x2fc) / 4];
    EA::AutoRefCount<UI::CRG_Minimap> mpMinimap;                     // +0x31c
    uint32_t pad320[(0x56c - 0x320) / 4];
    cMessageRegistrar mMessageRegistrar;                             // +0x56c
    EA::AutoRefCount<IWindow> mpMasterGlowImage;                     // +0x580
    uint32_t pad584[(0x598 - 0x584) / 4];
    EA::AutoRefCount<IWindow> mpStarRolloverWindow;                  // +0x598
    EA::AutoRefCount<IWindow> mpStarTooltipWindow;                   // +0x59c
    EA::AutoRefCount<IWindow> mpPlanetTooltipWindow;                 // +0x5a0
    EA::AutoRefCount<UI::CursorAttachment> mpCursorAttachment;       // +0x5a4
    EA::AutoRefCount<UI::cUITimedTooltip> mpTimedTooltip;            // +0x5a8
    uint32_t pad5ac[(0x5c4 - 0x5ac) / 4];
    EA::AutoRefCount<UI::Posse> mpPosse;                             // +0x5c4
    uint32_t pad5c8[(0x5d4 - 0x5c8) / 4];
    bool mb5d4;                                                      // +0x5d4
    bool mbInitialized;                                              // +0x5d5
    uint32_t pad5d8[(0x61c - 0x5d8) / 4];
    EA::AutoRefCount<UI::cUIFlashWindowManager> mpFlashWindowManager; // +0x61c
    uint32_t pad620[(0x690 - 0x620) / 4];
    float mfOverlayHeight;                                           // +0x690
    EA::AutoRefCount<cSpaceWinProc> mpOverlayWinProc;                // +0x694

    void Init();
    void FUN_01068f70();                                             // 0x01068f70
    void FUN_01070290();                                             // 0x01070290
    void InitFoodwebInfo();                                          // 0x01071a00
    void FUN_0106a280();                                             // 0x0106a280
    void FUN_010666b0();                                             // 0x010666b0
    void UpdateActivePlanetInfo();                                   // 0x0106a4e0
    void FUN_0106b500(cGameData* pData);                             // 0x0106b500
    void FUN_01072680();                                             // 0x01072680
    void AddCursors();                                               // 0x0106e020
};

inline cSPUILayout* GetSpaceGlobalLayout()
{
    cSpaceGame* pGame = SpaceGameGet();
    if (pGame && pGame->mpUI)
        return pGame->mpUI->mpGlobalUI->GetLayout();
    return 0;
}

}  // namespace SP

namespace SPUIHelpers {
    void CreateImageFromResource(uint32_t typeID, uint32_t instanceID, const wchar_t* name,
                                 EA::AutoRefCount<IWindow>* ppWindow, int a, int b, int c);  // 0x00806320
    void SetWindowImage(IWindow* pWindow, const ResourceKey& key, int index);               // 0x00807bb0
    void SetTooltipText(IWindow* pWindow, const wchar_t* text, int a, int b);               // 0x00806de0
}

extern const ResourceKey g_kTimedTooltipLayout;                      // 0x015b92a0

using namespace SP;

void SP::cSPUISpace::Init()
{
    mpMasterGlowImage = 0;
    SPUIHelpers::CreateImageFromResource(0x2f7d0004, 0x106c7116, L"fight-buton-1-2",
                                         &mpMasterGlowImage, 0, -1, -1);

    if (!mpGlobalUI)
        mpGlobalUI = UI_NEW cSPUIGlobalUI();
    mpGlobalUI->Load(g_GlobalUIParams);

    if (!mpStarRolloverLayout)
        mpStarRolloverLayout = UI_NEW cSPUILayout();
    mpStarRolloverLayout->Init(L"SpaceStarRollover", 0x40464100, true, 0xe9f70df9);
    mpStarRolloverLayout->SetVisibility(false);
    mpStarRolloverWindow = mpStarRolloverLayout->FindWindowByID(0x1c22440, true);

    if (!mpStarTooltipLayout)
        mpStarTooltipLayout = UI_NEW cSPUILayout();
    mpStarTooltipLayout->Init(L"SpaceStarTooltip", 0x40464100, true, 0xe9f70df9);
    mpStarTooltipLayout->SetVisibility(false);
    mpStarTooltipWindow = mpStarTooltipLayout->FindWindowByID(0x1c22500, true);

    mpCursorAttachment = new ("UI/CursorAttachment", 0, 0, 0, 0) UI::CursorAttachment();

    if (!mpPlanetTooltipLayout)
        mpPlanetTooltipLayout = UI_NEW cSPUILayout();
    mpPlanetTooltipLayout->Init(L"SpacePlanetTooltip", 0x40464100, true, 0xe9f70df9);
    mpPlanetTooltipLayout->SetVisibility(false);
    mpPlanetTooltipWindow = mpPlanetTooltipLayout->FindWindowByID(0x1c23500, true);

    mn2f8 = -1;
    if (!mpTimedTooltip) {
        mpTimedTooltip = new ("UI/cUITimedTooltip", 0, 0, 0, 0) UI::cUITimedTooltip();
        mpTimedTooltip->Init(g_kTimedTooltipLayout, 0x711bb33c, 200, 250);
    }

    if (!mpMinimap) {
        IWindow* pMinimapWindow = mpGlobalUI->FindWindowByID(0x190722e);
        if (pMinimapWindow) {
            const Math::Rectangle& area = pMinimapWindow->GetRealArea();
            int width = FloorToInt(area.x2 - area.x1);
            int height = FloorToInt(area.y2 - area.y1);
            mpMinimap = new (8, "UI/SpaceMinimap", GetUIAllocator())
                UI::CRG_Minimap(width, height, Vector3(0.0f, 0.0f, -1.0f), Vector3(0.0f, 1.0f, 0.0f), 0.0f, false);
            mpMinimap->SetUp(Vector3(0.0f, 1.0f, 0.0f));
            mpMinimap->mCameraDir = Vector3(0.0f, 0.0f, 1.0f);
            pMinimapWindow->AddWindow(mpMinimap);
        }
    }

    mpWindowGroup = new ("Simulator/Space/UI", 0, 0, 0, 0)
        cWindowGroup(mpGlobalUI->GetLayout(), g_WindowGroupName);
    mpWindowGroup->FUN_00e29c80();

    EA::AutoRefCount<IWindow> pMainWindow = mpGlobalUI->FindWindowByID(0xffffffff);
    if (pMainWindow)
        pMainWindow->AddWinProc(this);

    uint32_t winProcWindowIDs[5] = { 0x52339c0, 0x52339a8, 0x5233980, 0xb2001000, 0x36c0957 };
    for (int i = 0; i < 5; i++) {
        IWindow* pWindow = mpGlobalUI->FindWindowByID(winProcWindowIDs[i]);
        if (pWindow)
            pWindow->AddWinProc(this);
    }

    if (!g_pSpaceUIObject) {
        g_pSpaceUIObject = UI_NEW cRefObject16();
        g_pSpaceUIObject->AddRef();
    }
    FUN_00b3d230()->AddObject(g_pSpaceUIObject, true);

    if (MessageServer())
        mMessageRegistrar.Init(MessageServer(), &mHandler, kSpaceUIMessageIDs, 25);

    CheatManager()->AddCheat(UI_NEW SpaceCheats::cCommandToolCheat());

    FUN_01068f70();
    FUN_01070290();
    InitFoodwebInfo();
    FUN_0106a280();
    FUN_010666b0();
    FUN_01046fc0()->FilterHelperRebuildAll();
    UpdateActivePlanetInfo();

    {
        ResourceKey ufoKey = cSPLivingUniverse::GetPlayerEmpire()->GetUFOKey();
        ufoKey.typeID = 0x2f7d0004;
        IWindow* pUFOWindow = GetSpaceGlobalLayout()->FindWindowByID(0xb0b00000, true);
        SPUIHelpers::SetWindowImage(pUFOWindow, ufoKey, -1);
    }

    mpPosse = new (4, "UI/UIPosse", GetUIAllocator()) UI::Posse();
    if (!mpPosse->Init(L"PosseBar", 0x40464100)) {
        mpPosse = 0;
    } else {
        mpPosse->SetSize(10.0f, 250.0f, 0, 0);
        cString caption;
        caption.Load(0x2db6dad3, 0x5baafc0, 0);
        mpPosse->SetCaption(caption.GetText());

        cGameNounManager* pNounManager = NounManager();
        const cGameDataVector& dataVec = pNounManager->GetGameDataVector(
            FUN_00cd7d10, FUN_00d3d420, FUN_00ad48b0, FUN_00b1e500, g_18ebadc)->mData;
        for (cGameData* const* it = dataVec.begin(), * const* itEnd = dataVec.end(); it != itEnd; ++it) {
            if ((*it)->mType == 3)
                FUN_0106b500(*it);
        }
        FUN_01072680();
        mpPosse->SetVisible(false);
        if (mpPosse && mpPosse->size() != 0)
            mpPosse->SetVisible(true);
    }

    for (int i = 0; i < 5; i++) {
        IWindow* pWindow = mpGlobalUI->FindWindowByID(kMeterWindowIDs[i]);
        if (pWindow) {
            ((cMeterHolder*)pWindow->Cast(0x106f146))->mMeter.SetValue(0);
            pWindow->SetFlag(1, false);
        }
    }

    IWindow* pWindow = mpGlobalUI->FindWindowByID(0x6567050);
    if (pWindow)
        SPUIHelpers::SetTooltipText(pWindow, mNewUFOScannedText.GetText(), -1, 1);
    pWindow = mpGlobalUI->FindWindowByID(0x6567051);
    if (pWindow)
        SPUIHelpers::SetTooltipText(pWindow, mUFOAlreadyScannedText.GetText(), -1, 1);

    AddCursors();
    mbInitialized = true;

    if (!mpFlashWindowManager) {
        mpFlashWindowManager = new ("UI/cUIFlashWindowManager", 0, 0, 0, 0) UI::cUIFlashWindowManager();
        mpFlashWindowManager->FUN_00e2f370();
    }

    if (world(2)) {
        ResourceKey layoutKey(0x9831b38f, 0x510a95b, 0x40464100);
        mpOverlayLayout = new ("Simulator", 0, 0, 0, 0) cSPUILayout();
        mpOverlayLayout->Init(layoutKey, true, 0x5b598fa);
        mpOverlayLayout->SetVisibility(true);
        mfOverlayHeight = 0.0f;
        IWindow* pHeightWindow = mpOverlayLayout->FindWindowByID(0x7cf8048, true);
        if (pHeightWindow)
            mfOverlayHeight = pHeightWindow->GetRealArea().GetBottom();

        uint32_t overlayWindowIDs[9] = { 0x75dd108, 0x75dd100, 0x5e4f770, 0x770996a, 0x5e4f788,
                                         0x7ce3cb0, 0x7ce1750, 0x7bb9fc8, 0x755e358 };
        mpOverlayWinProc = new ("Simulator", 0, 0, 0, 0) cSpaceWinProc();
        for (uint32_t i = 0; i < 9; i++) {
            IWindow* pOverlayWindow = mpOverlayLayout->FindWindowByID(overlayWindowIDs[i], true);
            if (pOverlayWindow)
                pOverlayWindow->AddWinProc(mpOverlayWinProc);
        }
    } else {
        mpOverlayWinProc = 0;
        mpOverlayLayout = 0;
    }
}

#pragma pack(pop)
