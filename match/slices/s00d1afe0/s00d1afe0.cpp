// Slice s00d1afe0: SP::cGameEditInputStrategy::HandleMessage (0x00d1afe0, 2932 bytes).
//
// Command/message dispatcher of the level ("game edit") editor: hot-loading the level
// editor prop, gameplay marker creation/rotation/properties, object manipulation commands,
// camera commands, load/save dialogs and copy/paste.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (same module as s00d1a2b0; no /EHsc:
// the AutoRefCount-style locals get no EH frame).
//
// HandleMessage is reached through the secondary base at +0x3c (the message handler), so
// `this` inside is the full object and cl emits [ecx-0x3c] for the primary object.
// Retail layout of cGameEditInputStrategy is the 2008 PDB's shifted by +4 from 0xa4 on.
#include "types.h"

#define VS1(n) virtual void n();
#define VS4(n) VS1(n##0) VS1(n##1) VS1(n##2) VS1(n##3)

// ---------------------------------------------------------------------------------------
// Value types
// ---------------------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

struct Quaternion {
    float x, y, z, w;
};

bool operator!=(const Vector3& a, const Vector3& b); // 0x0041dd30 (out of line)

namespace SP {
void OrthogonalVector(Vector3* pOut, const Vector3* pIn);                               // 0x006985b0
void QuaternionFromFacingAndUp(Quaternion* pOut, const Vector3* pFacing, const Vector3* pUp); // 0x0069b600
}

namespace EA {
namespace Hash {
uint32_t FNV1_String16(const wchar_t* pString, uint32_t seed, int bCaseInsensitive); // 0x00932f30
}
// EA::StdC::DateTime-like value; constructed with a time frame, first dword = seconds (low).
class DateTime {
public:
    uint32_t mnSecondsLo;
    uint32_t mnSecondsHi;
    DateTime(int timeFrame) { Set(timeFrame); }
    void Set(int timeFrame); // 0x0092e3d0
};
}

// ---------------------------------------------------------------------------------------
// Objects reached through interfaces
// ---------------------------------------------------------------------------------------
class IObject {
public:
    virtual int AddRef();               // +0x00
    virtual int Release();              // +0x04
    virtual void v08();
    virtual void* Cast(uint32_t typeID); // +0x0c
};

class IWinFlags {
public:
    VS4(a)
    VS4(b)
    VS1(c0)
    VS1(c1)
    virtual uint32_t GetFlags(); // +0x28
};

class IWinProps : public IObject {
public:
    virtual IWinFlags* GetWindow(); // +0x10
};

class IWindow {
public:
    VS4(a)
    VS4(b)
    VS1(c0)
    virtual void SetValue(int value, bool b); // +0x24
    virtual uint32_t GetFlags();               // +0x28
    VS1(c3)
    VS1(d0)
    virtual uint32_t GetText(int index);       // +0x34
    VS1(d2)
    VS1(d3)
    virtual int GetSelection();                // +0x40
    VS4(e)
    VS4(f)
    virtual void SetArea(float x, float y);    // +0x64
    VS1(g2)
    VS1(g3)
    VS1(h0)
    VS1(h1)
    VS1(h2)
    virtual void SetFlag(int flag, int value); // +0x7c
};

class cSPUILayout {
public:
    IObject* FindWindowByID(uint32_t controlID, bool recursive); // 0x008105b0
};

// Spatial part of a gameplay marker (at +0x34 of the noun)
class cSpatialPart {
public:
    VS4(a)
    VS4(b)
    VS4(c)
    VS1(d0)
    VS1(d1)
    virtual void SetPosition(const Vector3* pPos);       // +0x38
    virtual void SetOrientation(const Quaternion* pQuat); // +0x3c
};

class cCommandGameplayMarker;

class MarkerRef {
public:
    cCommandGameplayMarker* mpObject;
    MarkerRef& operator=(cCommandGameplayMarker* p); // 0x00b5f950
    void Assign(MarkerRef* other);                   // 0x00ac9480
};

class cCommandGameplayMarker {
public:
    uint32_t pad00[0x34 / 4];
    cSpatialPart mSpatial;            // +0x34
    uint32_t pad38[(0x108 - 0x38) / 4];
    uint32_t mMarkerType;             // +0x108
    uint32_t mField10c;               // +0x10c
    uint32_t mField110;               // +0x110
    uint32_t mMarkerID;               // +0x114
    uint32_t pad118;
    int mGroupIndex;                  // +0x11c
    float mScale;                     // +0x120
    uint32_t mShape;                  // +0x124
    uint32_t pad128[(0x19c - 0x128) / 4];
    MarkerRef mFirst;                 // +0x19c
    MarkerRef mPrev;                  // +0x1a0

    void AddChild(cCommandGameplayMarker* pChild); // 0x00c3eac0
};

class cGameNounManager {
public:
    IObject* CreateNoun(uint32_t nounID);              // 0x00b20c60
    void RemoveNoun(IObject* pNoun);                   // 0x00b225d0
    cCommandGameplayMarker* CreateGameplayMarker();    // 0x00b938b0
};

class cCameraManagerLike {
public:
    VS4(a)
    VS4(b)
    VS4(c)
    VS1(d0)
    VS1(d1)
    virtual Vector3 ScreenToWorld(void* pOut, Vector3 screenPos); // +0x38
};

class cTerrainCameraController {
public:
    void SetFloats5(float a, float b, float c, float d, float e); // 0x00b0f720
    void SetEnabled(bool b);                                       // 0x00b10c40
    void MoveTo(const Vector3* pPos, int arg);                    // 0x00b13bb0
};

class cPlanetModel {
public:
    void GetUpVector(Vector3* pOut, const Vector3* pPos); // 0x00b7e3b0
};

class cCanvasThing {
public:
    void SetVisible(bool b); // 0x008013d0
};

namespace SP {
cGameNounManager* NounManager();                  // 0x00b3d300
cPlanetModel* PlanetModel();                      // 0x00b3d350
}
cCameraManagerLike* GetCamera();                  // 0x00b3d240
cTerrainCameraController* GetTerrainCamera();     // 0x00b3d280
cCanvasThing* GetCanvas();                        // 0x0067cab0
void PrepareDialog();                             // 0x00b908c0
uint32_t HashText(uint32_t text);                 // 0x00572c50
void OpenSaveDialog(const Vector3* pPos, uint32_t* pName, int a, uint32_t name, int b); // 0x00b9b090

// ---------------------------------------------------------------------------------------
// Message parameters
// ---------------------------------------------------------------------------------------
struct cParam {
    IObject* mpObject;
    uint32_t pad04[3];
    uint8_t mFlags;   // +0x10
    uint8_t pad11;
    uint16_t mCount;  // +0x12

    IObject* AsObject()
    {
        if (mFlags & 0x30)
            return mpObject;
        if (mCount)
            return (IObject*)this;
        return 0;
    }
};

class cParams {
public:
    VS4(a)
    VS1(b0)
    VS1(b1)
    VS1(b2)
    virtual cParam* Get(int index); // +0x1c
};

class cMessage {
public:
    VS4(a)
    virtual cParams* GetParams(); // +0x10
    uint32_t pad04;
    int mValue;          // +0x08
    uint32_t pad0c;
    int mState;          // +0x10
    uint32_t pad14;
    uint32_t mName;      // +0x18
};

template <typename T> inline T* object_cast(IObject* p, uint32_t typeID)
{
    return p ? (T*)p->Cast(typeID) : 0;
}

template <typename T> class RefPtr {
public:
    T* mpObject;
    RefPtr(T* p) : mpObject(p)
    {
        if (mpObject)
            mpObject->AddRef();
    }
    ~RefPtr()
    {
        if (mpObject)
            mpObject->Release();
    }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

// 4-byte by-value argument built in place
struct HighlightArg {
    int mValue;
    HighlightArg(int v) : mValue(v) {}
    HighlightArg(const HighlightArg& o) : mValue(o.mValue) {}
};

class SelectedRef {
public:
    void* mpObject;
    void SetSelected(cSpatialPart* p); // 0x00c70110
};

// ---------------------------------------------------------------------------------------
// cGameEditInputStrategy
// ---------------------------------------------------------------------------------------
class cInputStrategyBase {
public:
    virtual void v00();
    uint32_t pad04[(0x3c - 4) / 4];
};

class IMessageHandler {
public:
    virtual void h00();
    virtual void h04();
    virtual void h08();
    virtual bool HandleMessage(uint32_t messageID, void* pMessage);
};

extern uint8_t gGameplayMarkerPlacing;   // 0x0167ade8
extern int gLevelEditorHotloadCount;     // 0x0169dc24
extern Vector3 gCursorScreenPos;         // 0x0169dc28
extern Vector3 gMarkerDragStart;         // 0x0167ae08
extern Vector3 gMarkerDragCurrent;       // 0x0167ae14

class cGameEditInputStrategy : public cInputStrategyBase, public IMessageHandler {
public:
    uint32_t pad40[(0x4c - 0x40) / 4];
    SelectedRef mpSelectedObject;          // +0x4c
    uint32_t pad50[(0xa4 - 0x50) / 4];
    IWindow* mGameplayMarkerRoot;          // +0xa4
    IWindow* mGameplayMarkerArea;          // +0xa8
    IWindow* mGameplayMarkerScrollbar;     // +0xac
    uint32_t padb0;
    IWindow* mRuleOptionsList;             // +0xb4
    IWindow* mTemplateOptions;             // +0xb8
    IWindow* mTemplateOptionsList;         // +0xbc
    IWindow* mPlanetNameEdit;              // +0xc0
    uint32_t padc4[(0xe0 - 0xc4) / 4];
    cSPUILayout mLayout;                   // +0xe0

    bool HandleMessage(uint32_t messageID, void* pMessage);

    void HotloadLevelEditorProp();                                                      // 0x00d160c0
    void CommitChangesToGameplayMarker(IObject* pMarker, bool b);                       // 0x00d172d0
    void ShowGameplayMarkerProperties(IObject* pMarker, bool bReadOnly, bool bDefaults); // 0x00d1a2b0
    void StartSelection(void* pObject, int value, Vector3* pPos);                       // 0x00d15ab0
    void SelectionDrag(void* pObject, int value, Vector3* pPos);                        // 0x00d15af0
    void SelectionEnd(void* pObject, int value, Vector3* pPos);                         // 0x00d15280
    void DoObjectManipulation(uint32_t messageID, void* pMessage);                      // 0x00d178a0
    void HandleRotateMessage(uint32_t messageID, void* pMessage);                       // 0x00d15980
    void DeleteSelected();                                                              // 0x00d164d0
    void SaveLevel(Vector3* pPos, uint32_t name);                                       // 0x00d15160
    void LoadLevel(bool b);                                                             // 0x00d15c00
    void Copy();                                                                        // 0x00d19460
    void SetButtonHighlight(HighlightArg arg);                                          // 0x00d18860

    static cCommandGameplayMarker* RotateObject(SelectedRef* pSelected);                // 0x00d15330
};

// @ 0x00d1afe0
bool cGameEditInputStrategy::HandleMessage(uint32_t messageID, void* pMessage)
{
    if (messageID == 0xf62def) {
        uint32_t name = ((cMessage*)pMessage)->mName;
        if (name == EA::Hash::FNV1_String16(L"LevelEditor", 0x811c9dc5, 1))
            HotloadLevelEditorProp();
        return true;
    }
    if (messageID == 0x15ccac2) {
        gLevelEditorHotloadCount++;
        return true;
    }
    if (messageID == 0x3d0891e) {
        cMessage* pMsg = (cMessage*)pMessage;
        bool bReadOnly = false;
        RefPtr<IWinProps> pProps(object_cast<IWinProps>(mLayout.FindWindowByID(0xabc0fff8, true), 0x2f5528d9));
        if (pProps)
            bReadOnly = (pProps->GetWindow()->GetFlags() & 2) != 0;

        cGameNounManager* pNounMgr = SP::NounManager();
        RefPtr<IObject> pMarker(object_cast<IObject>(pNounMgr->CreateNoun(0x36be27e), 0x36be278));

        CommitChangesToGameplayMarker(pMarker, false);
        ShowGameplayMarkerProperties(pMarker, bReadOnly, pMsg->mState == 1);
        SP::NounManager()->RemoveNoun(pMarker);
        IWindow* pScroll = mGameplayMarkerScrollbar;
        if (pScroll && mGameplayMarkerArea) {
            int value = pMsg->mValue;
            pScroll->SetValue(value, true);
            mGameplayMarkerArea->SetArea(0.0f, (float)-value);
        }
        return true;
    }

    cParams* pParams = ((cMessage*)pMessage)->GetParams();
    IObject* pObject = pParams->Get(0)->AsObject();
    void* pTarget = object_cast<void>(pObject, 0x17f243b);
    void* pWinObject;
    if (pObject)
        pWinObject = pObject->Cast(0x1186577);
    int value = *(int*)pParams->Get(1);
    Vector3 pos(*(Vector3*)pParams->Get(3));
    pParams->Get(2);

    switch (messageID) {
    case 0x1cbf999: {
        gGameplayMarkerPlacing = 1;
        gMarkerDragStart = gMarkerDragCurrent = GetCamera()->ScreenToWorld(0, gCursorScreenPos);
        return true;
    }
    case 0x127ec9d:
    case 0x1270f6b:
    case 0x1271936:
    case 0x127433b:
    case 0x127e78c:
    case 0x13674b6:
        DoObjectManipulation(messageID, pMessage);
        return true;
    case 0xe39174:
        StartSelection(pTarget, value, &pos);
        return true;
    case 0xe615bf:
        SelectionDrag(pTarget, value, &pos);
        return true;
    case 0xfc6f3b:
        SelectionEnd(pTarget, value, &pos);
        return true;
    case 0x1380379:
        HandleRotateMessage(0x1380379, pMessage);
        return true;
    case 0x137c407:
        DeleteSelected();
        return true;
    case 0x137d8fe:
        return true;
    case 0x158b25b: {
        cTerrainCameraController* pCam = GetTerrainCamera();
        if (pCam) {
            pCam->SetFloats5(0.1f, 0.1f, 0.1f, 0.1f, 0.1f);
            Vector3 p = GetCamera()->ScreenToWorld(0, gCursorScreenPos);
            if (p.x * p.x + p.y * p.y + p.z * p.z > 0.0f)
                pCam->MoveTo(&p, 0);
        }
        return true;
    }
    case 0x158b25d: {
        bool bOn = (uint32_t)value > 0;
        cTerrainCameraController* pCam = GetTerrainCamera();
        if (pCam)
            pCam->SetEnabled(bOn);
        GetCanvas()->SetVisible(!bOn);
        return true;
    }
    case 0x4f64c5d:
    case 0x2943a9f:
        return true;
    case 0x1cbf99a:
        gMarkerDragCurrent = GetCamera()->ScreenToWorld(0, gCursorScreenPos);
        return true;
    case 0x244aaa4:
        if (pWinObject) {
            cCommandGameplayMarker* pMarker = RotateObject(&mpSelectedObject);
            if (pMarker)
                ShowGameplayMarkerProperties((IObject*)pMarker, false, false);
        }
        return true;
    case 0x2a65b79:
        gGameplayMarkerPlacing = 0;
        SetButtonHighlight(HighlightArg(0));
        {
            IWindow* w = mGameplayMarkerRoot;
            if (w)
                w->SetFlag(1, 0);
            w = mTemplateOptionsList;
            if (w)
                w->SetFlag(1, 0);
            w = mRuleOptionsList;
            if (w)
                w->SetFlag(1, 0);
        }
        return true;
    case 0x2afab07: {
        Vector3 p = GetCamera()->ScreenToWorld(0, gCursorScreenPos);
        cCommandGameplayMarker* pNew = SP::NounManager()->CreateGameplayMarker();
        bool bDefaults = true;
        if (mGameplayMarkerRoot->GetFlags() & 1) {
            cCommandGameplayMarker* pOld = RotateObject(&mpSelectedObject);
            if (pOld) {
                CommitChangesToGameplayMarker((IObject*)pOld, true);
                pNew->AddChild(pOld);
                bDefaults = false;
                if (pNew->mMarkerType == 0xc012ae1f)
                    pNew->mGroupIndex++;
            }
        }
        Vector3 up;
        cPlanetModel* pPlanet = SP::PlanetModel();
        pPlanet->GetUpVector(&up, &p);
        Vector3 facing;
        SP::OrthogonalVector(&facing, &up);
        Quaternion q;
        SP::QuaternionFromFacingAndUp(&q, &facing, &up);
        pNew->mSpatial.SetPosition(&p);
        pNew->mSpatial.SetOrientation(&q);
        mpSelectedObject.SetSelected(&pNew->mSpatial);
        ShowGameplayMarkerProperties((IObject*)pNew, true, bDefaults);
        return true;
    }
    case 0x3a86a56:
    case 0x3a86a57:
    case 0x2afab18:
        return true;
    case 0x3a86a8e: {
        Vector3 p = GetCamera()->ScreenToWorld(0, gCursorScreenPos);
        if (mTemplateOptions && p != gCursorScreenPos) {
            PrepareDialog();
            int sel = mTemplateOptions->GetSelection();
            uint32_t name = HashText(mTemplateOptions->GetText(sel));
            OpenSaveDialog(&p, &name, 1, name, 1);
        }
        return true;
    }
    case 0x52ba744d:
        SaveLevel(&pos, 0xc5eb4d3d);
        return true;
    case 0x4f65079: {
        cCommandGameplayMarker* pNew = SP::NounManager()->CreateGameplayMarker();
        cCommandGameplayMarker* pPrev = RotateObject(&mpSelectedObject);
        uint32_t id;
        int index;
        if (pPrev && pPrev->mMarkerType == 0xc012ae1f && pPrev->mShape == 4) {
            index = pPrev->mGroupIndex + 1;
            id = pPrev->mMarkerID;
        } else {
            static uint32_t sNextMarkerID = EA::DateTime(2).mnSecondsLo;
            id = ++sNextMarkerID;
            index = 0;
        }
        pNew->mMarkerType = 0xc012ae1f;
        pNew->mField10c = 0;
        pNew->mField110 = 0;
        pNew->mMarkerID = id;
        pNew->mGroupIndex = index;
        pNew->mScale = 1.0f;
        pNew->mShape = 4;
        Vector3 p = GetCamera()->ScreenToWorld(0, gCursorScreenPos);
        Vector3 up;
        cPlanetModel* pPlanet = SP::PlanetModel();
        pPlanet->GetUpVector(&up, &p);
        Vector3 facing;
        SP::OrthogonalVector(&facing, &up);
        Quaternion q;
        SP::QuaternionFromFacingAndUp(&q, &facing, &up);
        pNew->mSpatial.SetPosition(&p);
        pNew->mSpatial.SetOrientation(&q);
        if (pPrev) {
            pPrev->mFirst = pNew;
            if (index == 0)
                pPrev->mPrev = pPrev;
            pNew->mPrev.Assign(&pPrev->mPrev);
        }
        mpSelectedObject.SetSelected(&pNew->mSpatial);
        return true;
    }
    case 0x12ba6ae8:
        return true;
    case 0x32b9318d: {
        Vector3 p = GetCamera()->ScreenToWorld(0, gCursorScreenPos);
        IWindow* pEdit = mPlanetNameEdit;
        if (pEdit) {
            int sel = pEdit->GetSelection();
            SaveLevel(&p, HashText(mPlanetNameEdit->GetText(sel)));
        }
        return true;
    }
    case 0x92baae9b:
        LoadLevel(false);
        return true;
    case 0xb2ba6adb:
        Copy();
        return true;
    case 0xb2baae85:
        LoadLevel(true);
        return true;
    }
    return false;
}
