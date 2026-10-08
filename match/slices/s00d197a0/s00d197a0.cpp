// Slice s00d197a0: SP::cGameEditInputStrategy::DoMessage @ 0x00D197A0 (2259 bytes).
//
// The level ("game edit") editor's UI window-procedure handler (IWinProc::HandleUIMessage(IWindow*,
// const Message&), ret 8). It reacts to button/list control IDs of the editor UI: highlights the
// clicked tool button, toggles the marker/template/rule option windows, opens the save/load dialogs,
// creates and rotates gameplay markers, scrolls the marker property area.
//
// `this` is the IWinProc secondary-base subobject at +0x40 of cGameEditInputStrategy (member offsets
// in the disassembly are the full offsets minus 0x40; calls to members use [esi-0x40]).
// Retail layout is the 2008 PDB's shifted by +4 from 0xa4 on (see s00d1afe0 / s00d1a2b0).
// Flags: x87 float path (no /arch:SSE): /O2 /MD /Gy /TP /GS-.
#include "types.h"

#define VS1(n) virtual void n();
#define VS4(n) VS1(n##0) VS1(n##1) VS1(n##2) VS1(n##3)
#define VS16(n) VS4(n##a) VS4(n##b) VS4(n##c) VS4(n##d)

namespace eastl {
extern char gEmptyString[];   // 0x01667bac
}

// eastl::string16 as a local (default-constructed to the shared empty string, then DeallocateSelf).
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    string16()
    {
        mpBegin = (wchar_t*)eastl::gEmptyString;
        mpEnd = (wchar_t*)eastl::gEmptyString;
        mpCapacity = (wchar_t*)eastl::gEmptyString + 1;
    }
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf();   // 0x00933960
};

class IWindow {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual int GetValue();  // +0x28
    virtual void s2c();
    virtual void s30();
    virtual uint32_t GetText(int index);  // +0x34
    virtual void s38();
    virtual void s3c();
    virtual int GetSelection();  // +0x40
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void SetText(const void* p, int v);  // +0x60
    virtual void SetArea(float x, float y);  // +0x64
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void SetFlag(int flag, int value);  // +0x7c
};

class IGrid {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual void s8c();
    virtual void s90();
    virtual void s94();
    virtual void s98();
    virtual void s9c();
    virtual void sa0();
    virtual bool GetSelected(void** ppItem, int* pIndex);  // +0xa4
    virtual void sa8();
    virtual void sac();
    virtual void sb0();
    virtual void sb4();
    virtual void sb8();
    virtual void sbc();
    virtual void sc0();
    virtual void sc4();
    virtual void sc8();
    virtual void scc();
    virtual void sd0();
    virtual void sd4();
    virtual void sd8();
    virtual void sdc();
    virtual void se0();
    virtual void se4();
    virtual void se8();
    virtual void sec();
    virtual void sf0();
    virtual void sf4();
    virtual void sf8();
    virtual void sfc();
    virtual void s100();
    virtual void s104();
    virtual void s108();
    virtual void s10c();
    virtual void s110();
    virtual void s114();
    virtual void s118();
    virtual void s11c();
    virtual void s120();
    virtual void s124();
    virtual void s128();
    virtual void s12c();
    virtual void s130();
    virtual void s134();
    virtual void s138();
    virtual void s13c();
    virtual void s140();
    virtual void s144();
    virtual void s148();
    virtual void s14c();
    virtual void s150();
    virtual void s154();
    virtual void s158();
    virtual void s15c();
    virtual void s160();
    virtual void s164();
    virtual void s168();
    virtual void s16c();
    virtual void s170();
    virtual void s174();
    virtual void s178();
    virtual void s17c();
    virtual void s180();
    virtual void s184();
    virtual void s188();
    virtual void s18c();
    virtual void s190();
    virtual void s194();
    virtual void s198();
    virtual void s19c();
    virtual void GetItemText(int a, int index, wchar_t** ppText);  // +0x1a0
    virtual void s1a4();
    virtual void s1a8();
    virtual void s1ac();
    virtual void s1b0();
    virtual void s1b4();
    virtual void s1b8();
    virtual void s1bc();
    virtual void s1c0();
    virtual int GetItemKey(int a, int index);  // +0x1c4
};

class IGameInput {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void SetCursorMode(uint32_t id, bool b);  // +0x64
};

class IMessageServer {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void Post(uint32_t id, void* pMsg, int a, int b);  // +0x18
};

class IPlanetTerrain {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual void SetSomething(uint32_t v);  // +0x8c
};

// value built in place through AutoRefCount<...>::AutoRefCount(T*) (0x00572660) and passed by value
struct SourceRef {
    IWindow* mp;
    SourceRef(IWindow* p);                         // 0x00572660
    SourceRef(const SourceRef& o) : mp(o.mp) {}
};

struct PlanetKey { uint32_t a, b, c; };

// Heap message object (MessageBasicRC<5>, 0x40 bytes): AddRef at +4, Release at +8.
class MessageBasicRC5 {
public:
    virtual void s00();
    virtual int AddRef();
    virtual int Release();
    uint32_t pad04[(0x8 - 0x4) / 4];
    int mValue;                       // +0x08
    uint32_t pad0c;
    int mFlag;                        // +0x10
    uint32_t pad14[(0x30 - 0x14) / 4];
    uint32_t mMessageID;              // +0x30
    uint32_t pad34[3];
    explicit MessageBasicRC5(int a);  // 0x00421c80
};
void* operator new(unsigned int n, const char* name, int a, int b, int c, int d);   // 0x00f473a0

class cCommandGameplayMarker {
public:
    uint32_t pad00[0x108 / 4];
    uint32_t mMarkerType;             // +0x108
    uint32_t pad10c[(0x124 - 0x10c) / 4];
    uint32_t mShape;                  // +0x124
    uint32_t pad128[(0x19c - 0x128) / 4];
    void* mpFirst;                    // +0x19c
};

// Selected-object reference (AutoRefCount): Release is virtual slot 0xc0.
class IReleasable {
public:
    VS16(a) VS16(b) VS16(c)
    virtual void ReleaseRef();        // +0xc0
};
struct SelectedRef {
    IReleasable* mpObject;
};

class cNounManager {
public:
    void FUN_00b25fe0();                              // 0x00b25fe0
    void RemoveNoun(void* pNoun);                     // 0x00b225d0
    void RemoveNounsOfType(uint32_t typeID);          // 0x00b22650
};
class cPlanetModel {
public:
    uint32_t pad00[0x24 / 4];
    class IPlanetTerrain* mpTerrain;                  // +0x24
    void FUN_00b8c0f0();                              // 0x00b8c0f0
    void FUN_00b8d8a0(const PlanetKey* pKey, int a, int b);   // 0x00b8d8a0 (ret 0xc)
};
class cEditMode {
public:
    void MarkDirty();                                 // 0x00d1bf10
};

namespace EA { namespace IO {
void SplitPath(const wchar_t* path, wchar_t* drive, wchar_t* dir, wchar_t* name, wchar_t* ext, int flags); // 0x00930180
} }

cNounManager* NounManager();                          // 0x00b3d300
cPlanetModel* PlanetModel();                          // 0x00b3d350
IGameInput* GameInputManager();                       // 0x00b3d250
IMessageServer* MessageServer();                      // 0x0067dcc0
cEditMode* GetEditMode();                             // 0x00d1bf00
uint32_t HashName(const wchar_t* pName);              // 0x00572c50
uint32_t GetPlanetThing();                            // 0x0067dd50
void PrepareDialog();                                 // 0x00b908c0
int GetCurrentGameModeAlt();                          // 0x00b5b820
void EnterGameMode(int mode);                         // 0x00ba1c60
void LoadScenario(cCommandGameplayMarker* p, uint32_t classId, uint32_t x);   // 0x00b931c0
void SaveScenario(const wchar_t* pName);              // 0x00d1cb00
void InterfaceCast(uint32_t id, int b);               // 0x00d1c610
uint32_t GetGameplayMarkerClassId(uint32_t type);     // 0x00d15b30

extern uint32_t gIgnoreParam;           // 0x0158265c
extern uint32_t gMarkerVisibilityMode;  // 0x0169dc1c
extern uint8_t gEditorFlag20;           // 0x0169dc20
extern uint8_t gEditorFlag21;           // 0x0169dc21

struct UIMessage {
    IWindow* mpSource;                  // +0x00
    uint32_t pad04;
    uint32_t mType;                     // +0x08
    uint32_t mParam;                    // +0x0c
};

class cInputStrategyBase {
public:
    virtual void v00();
    uint32_t pad04[(0x3c - 4) / 4];
};
class IHandlerRC4 {
public:
    virtual void h00();
};
class IWinProc {
public:
    virtual void w00();
    virtual bool HandleUIMessage(IWindow* pWindow, const UIMessage& msg);
};
class RefCountV {
public:
    virtual void r00();
    int mRefCount;
};

class cGameEditInputStrategy : public cInputStrategyBase, public IHandlerRC4, public IWinProc, public RefCountV {
public:
    SelectedRef mpSelectedObject;                 // +0x4c
    uint32_t pad50;
    void* mpSelectedObjectManipulator;            // +0x54
    uint32_t pad58[(0x78 - 0x58) / 4];
    IWindow* mLevelNameTextEdit;                  // +0x78
    uint32_t pad7c;
    IWindow* mLoadDialogWindow;                   // +0x80
    IWindow* mLoadPlanetDialogWindow;             // +0x84
    IGrid* mGridFileList;                         // +0x88
    IGrid* mPlanetGridFileList;                   // +0x8c
    PlanetKey* mPlanetKeysBegin;                  // +0x90
    uint32_t pad94[(0xa4 - 0x94) / 4];
    IWindow* mGameplayMarkerRoot;                 // +0xa4
    IWindow* mGameplayMarkerArea;                 // +0xa8
    IWindow* mGameplayMarkerScrollbar;            // +0xac
    IWindow* mVisibilityCombo;                    // +0xb0
    IWindow* mRuleOptionsList;                    // +0xb4
    uint32_t padb8;
    IWindow* mTemplateOptionsList;                // +0xbc

    virtual bool HandleUIMessage(IWindow* pWindow, const UIMessage& msg);

    void SetButtonHighlight(SourceRef arg);                           // 0x00d18860
    uint32_t GetGameplayMarkerTypeFromUI();                           // 0x00d15fb0
    uint32_t FUN_00d16820();                                          // 0x00d16820
    void CommitChangesToGameplayMarker(cCommandGameplayMarker* p, bool b);   // 0x00d172d0
    void PopulateLoadDialogGridWithLevels();                          // 0x00d16960
    void PopulateLoadPlanetDialogGrid();                              // 0x00d194c0
    bool GetSaveFileName(string16* pName, int a);                     // 0x00d18b40
    void DoSaveSelectedFile(string16* pName);                         // 0x00d18df0
    void SetPlanet(const PlanetKey* pKey);                            // 0x00d16b90
    void FUN_00d15a10(int v);                                         // 0x00d15a10
    void FUN_00d15600();                                              // 0x00d15600
    static cCommandGameplayMarker* RotateObject(SelectedRef* pSelected);   // 0x00d15330

    void ShowOptionWindows(int templateValue, int ruleValue)
    {
        IWindow* w = mGameplayMarkerRoot;
        if (w)
            w->SetFlag(1, 0);
        w = mTemplateOptionsList;
        if (w)
            w->SetFlag(1, templateValue);
        w = mRuleOptionsList;
        if (w)
            w->SetFlag(1, ruleValue);
    }
};

// 3-window tail shared by the highlight cases: show/hide flags of the option windows
// @ 0x00D197A0
bool cGameEditInputStrategy::HandleUIMessage(IWindow* pWindow, const UIMessage& msg)
{
    if (msg.mParam == gIgnoreParam)
        return false;

    IGameInput* pInput = GameInputManager();

    if (msg.mType == 0x8ef0c8dd) {
        if (msg.mParam == 0x36c3e74) {
            int v = mGameplayMarkerScrollbar->GetValue();
            mGameplayMarkerArea->SetArea(0.0f, (float)-v);
        }
        return true;
    }

    if (msg.mType == 0x4f5527e8) {
        switch ((int)msg.mParam) {
        case 0xabc0fff8: {
            MessageBasicRC5* pMsg = new("App", 0, 0, 0, 0) MessageBasicRC5(0);
            if (pMsg)
                pMsg->AddRef();
            pMsg->mMessageID = 0x3d0891e;
            pMsg->mValue = mGameplayMarkerScrollbar ? mGameplayMarkerScrollbar->GetValue() : 0;
            pMsg->mFlag = 1;
            MessageServer()->Post(pMsg->mMessageID, pMsg, 0, 0);
            pMsg->Release();
            break;
        }
        case 0xabc0fff9:
            if (RotateObject(&mpSelectedObject)) {
                uint32_t classId = GetGameplayMarkerClassId(GetGameplayMarkerTypeFromUI());
                uint32_t x = FUN_00d16820();
                cCommandGameplayMarker* pMarker = RotateObject(&mpSelectedObject);
                LoadScenario(pMarker, classId, x);
            }
            break;
        case 0x3e0691c:
            if (mVisibilityCombo) {
                int sel = mVisibilityCombo->GetSelection();
                if (sel == 0)
                    gMarkerVisibilityMode = 0;
                else
                    gMarkerVisibilityMode = HashName((const wchar_t*)mVisibilityCombo->GetText(sel));
            }
            break;
        }
    }

    switch ((int)msg.mParam) {
    case 0x135688e:
        SetButtonHighlight(SourceRef(msg.mpSource));
        pInput->SetCursorMode(0x137d8fe, true);
        ShowOptionWindows(0, 0);
        return true;
    case 0x92b3c8eb:
        SetButtonHighlight(SourceRef(msg.mpSource));
        pInput->SetCursorMode(0x12ba6ae8, true);
        return true;
    case 0x136abf8:
        SetButtonHighlight(SourceRef(msg.mpSource));
        pInput->SetCursorMode(0x137c407, true);
        ShowOptionWindows(0, 0);
        return true;
    case 0x13e7786:
        mLoadDialogWindow->SetFlag(1, 1);
        PopulateLoadDialogGridWithLevels();
        return true;
    case 0x13e7736: {
        string16 name;
        if (GetSaveFileName(&name, 0)) {
            GetEditMode();
            SaveScenario(name.mpBegin);
        }
        return true;
    }
    case 0x13e778c: {
        NounManager()->FUN_00b25fe0();
        if (mpSelectedObjectManipulator) {
            NounManager()->RemoveNoun(mpSelectedObjectManipulator);
            mpSelectedObjectManipulator = 0;
        }
        PrepareDialog();
        gEditorFlag20 = 1;
        mGameplayMarkerRoot->SetFlag(1, 0);
        return true;
    }
    case 0x14143be: {
        mLoadDialogWindow->SetFlag(1, 0);
        void* pItem;
        int index;
        wchar_t* pPath;
        int key = 0;
        if (mGridFileList->GetSelected(&pItem, &index)) {
            mGridFileList->GetItemText(0, index, &pPath);
            key = mGridFileList->GetItemKey(0, index);
        }
        if (gEditorFlag21) {
            if (key == 0)
                return true;
            FUN_00d15a10(key);
            return true;
        }
        wchar_t name[256];
        EA::IO::SplitPath(pPath, 0, 0, name, 0, 4);
        NounManager()->RemoveNounsOfType(0x36be27e);
        InterfaceCast(HashName(name), 1);
        mLevelNameTextEdit->SetText(name, 0);
        return true;
    }
    case 0x14143b4:
        mLoadDialogWindow->SetFlag(1, 0);
        mGameplayMarkerRoot->SetFlag(1, 0);
        return true;
    case 0x147c3f6:
        mLoadPlanetDialogWindow->SetFlag(1, 1);
        PopulateLoadPlanetDialogGrid();
        return true;
    case 0x147ccec:
        mLoadPlanetDialogWindow->SetFlag(1, 0);
        return true;
    case 0x147ccf2: {
        mLoadPlanetDialogWindow->SetFlag(1, 0);
        NounManager()->FUN_00b25fe0();
        void* pItem;
        int index;
        if (!mPlanetGridFileList->GetSelected(&pItem, &index))
            return true;
        PlanetKey key = mPlanetKeysBegin[index];
        SetPlanet(&key);
        PlanetModel()->FUN_00b8c0f0();
        PlanetModel()->FUN_00b8d8a0(&key, 0, 1);
        PlanetModel()->mpTerrain->SetSomething(GetPlanetThing());
        GetEditMode()->MarkDirty();
        return true;
    }
    case 0x2afbb64:
        SetButtonHighlight(SourceRef(msg.mpSource));
        pInput->SetCursorMode(0x2afab18, true);
        ShowOptionWindows(0, 0);
        return true;
    case 0x29fe4ed:
        PrepareDialog();
        EnterGameMode(GetCurrentGameModeAlt());
        return true;
    case 0x36c46d4:
        CommitChangesToGameplayMarker(RotateObject(&mpSelectedObject), true);
        return false;
    case 0x36c4718: {
        FUN_00d15600();
        cCommandGameplayMarker* p = RotateObject(&mpSelectedObject);
        if (!p)
            return false;
        LoadScenario(p, 0xffffffff, 0xffffffff);
        return false;
    }
    case 0x3a869e8:
        SetButtonHighlight(SourceRef(msg.mpSource));
        pInput->SetCursorMode(0x3a86a56, true);
        ShowOptionWindows(1, 0);
        return true;
    case 0x12b933e5:
        SetButtonHighlight(SourceRef(msg.mpSource));
        pInput->SetCursorMode(0x3a86a57, true);
        ShowOptionWindows(0, 1);
        return true;
    case 0x4f65940: {
        cCommandGameplayMarker* p = RotateObject(&mpSelectedObject);
        if (!(p && p->mMarkerType == 0xc012ae1f && p->mShape == 4 && p->mpFirst == 0)) {
            IReleasable* q = mpSelectedObject.mpObject;
            if (q) {
                mpSelectedObject.mpObject = 0;
                q->ReleaseRef();
            }
        }
        pInput->SetCursorMode(0x4f64c5d, true);
        return true;
    }
    case 0x52b3c8d7: {
        string16 name;
        if (GetSaveFileName(&name, 0))
            DoSaveSelectedFile(&name);
        return true;
    }
        case 0x72b3c8e2:
        SetButtonHighlight(SourceRef(msg.mpSource));
        pInput->SetCursorMode(0xb2ba6adb, true);
        return true;
    }
    return false;
}
