// Slice s00ee4390: 0x00ee4390 (4,328 bytes), the window procedure of the scenario editor's
// behaviour panel (SP::cScenarioEditModeBehaviorUI, see slices s00ee2860/s00ee3800; the
// dev-PDB caller-scored candidate was SP::cSPEditorManipulatorUIBlockWinProc::DoMessage).
//
// HandleUIMessage(window, msg) of the IWinProc base at +8 (so `this` in the asm is the
// object + 8 and Outer methods get `lea ecx,[edi-8]`). It always returns false. Messages:
//   1 (key down)          enter/escape in the name field -> commit and release focus
//   8 (mouse move)        drag of a behaviour icon: move it, tint it green/red by validity
//   7 (mouse up)          drop of a dragged icon on a slot (0x715cdc0: open the pie menu of
//                         choices with a cHideOnMoveScreenPosition; 0x7394420/0x75e1200:
//                         assign the dragged id to the item)
//   0x17                  name field lost focus -> release focus
//   0x1c / 0x1b           text field focus out / in (rename / description edits)
//   0x287259f6 (button)   the panel's buttons (add/remove/reorder tutorials, modal dialogs,
//                         toggles stored in global properties, act selection 0x743b8e1..e8)
//   0x4f5527e8            slider value (time limit table), then falls into 6
//   6 (mouse down)        pick up an icon for dragging / right click on a slot
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc: the cString/vector locals
// have no EH frame; SSE addss for the drag position needs /fp:fast).
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

struct Point {
    float x, y;
    Point() {}
    Point(float _x, float _y) : x(_x), y(_y) {}
    Point(const Point& o) : x(o.x), y(o.y) {}
};

struct RectT {
    float x1, y1, x2, y2;
    RectT& operator=(const RectT& other);                                 // 0x00572600
};

struct ColorRGB {
    float r, g, b;
    ColorRGB(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
};
uint32_t __cdecl ColorRGBToU32(const ColorRGB& c);                        // 0x00458a40

// ---------------------------------------------------------------------------------------------
// UTFWin
// ---------------------------------------------------------------------------------------------
class IWindow {
public:
    PV4
    virtual IWindow* GetParent();                                         // +0x10
    PV2
    virtual uint32_t GetControlID();                                      // +0x1c
    PV4
    virtual uint32_t GetShadeColor();                                     // +0x30
    PV
    virtual const RectT& GetRealArea();                                   // +0x38
    virtual const wchar_t* GetCaption();                                  // +0x3c
    PV4 PV2 PV
    virtual void SetShadeColor(uint32_t color);                           // +0x5c
    PV4
    virtual void SetLayoutLocation(float x, float y);                     // +0x70
    PV
    virtual void SetCursorID(uint32_t id);                                // +0x78
    PV16 PV
    virtual Point ToGlobalCoordinates(Point local);                       // +0xc0
    PV4 PV
    virtual void AddWindow(IWindow* window);                              // +0xd8
    virtual void RemoveWindow(IWindow* window);                           // +0xdc
    PV4
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive);         // +0xf0
};

struct Message {
    IWindow* mSrc;                   // +0x00
    IWindow* mWindow;                // +0x04
    uint32_t mType;                  // +0x08
    union {
        struct { float x, y; int state; int button; } mouse;               // +0x0c
        struct { int a0, key, a2, a3; } keys;                              // +0x0c
        struct { int a0, a1, a2; IWindow* window; } focus;                 // +0x0c
        struct { int controlID; int value; int a2, a3; } button;           // +0x0c
    };
};

class IWindowManager {
public:
    PV
    virtual IWindow* GetMainWindow();                                     // +0x04
    PV2
    virtual void SendMsg(IWindow* src, IWindow* dst, const Message& msg, bool inheritable); // +0x10
    PV8 PV4 PV
    virtual IWindow* GetMainWindowIndex(int index);                       // +0x48
    virtual void SetFocusWindow(int index, IWindow* window);              // +0x4c
    PV2
    virtual void SetCaptureWindow(int index, IWindow* window);            // +0x58
    PV8 PV2
    virtual IWindow* GetModalWindow();                                    // +0x84
};
IWindowManager* __cdecl WindowManager();                                  // 0x0067caa0
IWindowManager* __cdecl GetUTFWinManager();                               // 0x00957f30

class IWinProc {
public:
    PV4 PV2
    virtual bool HandleUIMessage(IWindow* window, const Message& msg) = 0;
};

template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p);                                                   // 0x00572660 (out of line)
    AutoRefCount& operator=(T* p);                                        // 0x00b5f950
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// AutoRefCount<cHideOnMoveScreenPosition>, spelled as a plain struct so the checker can map its
// out-of-line constructor (one body at 0x00572660 serves every T).
class cHideOnMoveScreenPosition;
struct HideOnMoveRef {
    cHideOnMoveScreenPosition* mpObject;
    HideOnMoveRef(cHideOnMoveScreenPosition* p);                          // 0x00572660
};

class cSPUILayout {
public:
    IWindow* FindWindowByID(uint32_t id, bool recursive);                 // 0x008105b0
};

class cLayoutRoot {
public:
    IWindow* FindWindow(uint32_t id);                                     // 0x00810620
};
cLayoutRoot* __cdecl LayoutRoot();                                        // 0x0080fee0

namespace SP {
class cString {
public:
    cString();                                                            // 0x006b5060
    ~cString();                                                           // 0x006b5240
    const wchar_t* GetText();                                             // 0x006b55c0
    uint32_t mData[5];                   // retail size 0x14 (dev PDB says 0x1c)
};
}

// choice list (0x188 bytes): header + fixed_vector of up to 5 0x44-byte choices at +0x18/+0x30
struct ChoiceVector {
    uint32_t mHeader[6];
    void*    mpBegin;                // +0x18
    void*    mpEnd;                  // +0x1c
    void*    mpCapacity;             // +0x20
    uint32_t mOverflow[3];           // +0x24
    uint8_t  mBuffer[0x154];         // +0x30
    int      mSelected;              // +0x184
    ChoiceVector();                                                       // 0x00f2bd10
    ~ChoiceVector();                                                      // 0x00dfbb60
};

class cHideOnMoveScreenPosition {
public:
    typedef void (__cdecl* Callback)(void*);
    cHideOnMoveScreenPosition(void* object, Callback callback, void* context); // 0x00edfe10
    virtual int AddRef();
    virtual int Release();
    PV2
    virtual void GetScreenPosition(float* x, float* y);                   // +0x10
    uint32_t mData[7];                   // sizeof 0x20
};
void* operator new(size_t size, const char* name, int, int, int, int);    // 0x00f473a0

class cSPUIPieMenu {
public:
    void Hide();                                                          // 0x00818330
    void RemoveAllItems();                                                // 0x00818c80
    void SetCallback(void (__cdecl* callback)(void*, int), void* context); // 0x008182c0
    void Show(float x, float y, cHideOnMoveScreenPosition* anchor, int flags); // 0x00819ad0
    void AddItem(uint32_t iconID, const wchar_t* text, uint32_t color, bool enabled); // 0x0081a940
};

// ---------------------------------------------------------------------------------------------
// scenario data
// ---------------------------------------------------------------------------------------------
struct ScenarioItem {                // returned by GetItem (0x00f3bf00)
    int      mKind;                  // +0x00
    int      mBehaviorA;             // +0x04
    int      mBehaviorB;             // +0x08
    uint32_t pad0c;
    bool     mbEnabled;              // +0x10
};

struct GoalEntry {                   // 0x188 bytes
    uint32_t pad00[3];
    int      mCount;                 // +0x0c
    uint8_t  pad10[0x188 - 0x10];
};

struct ActData {                     // returned by GetAct (0x00f3be60)
    uint8_t    mName[0x3c];          // +0x00 (string)
    uint8_t    mDescription[0x3c];   // +0x3c (string)
    int        mTimeLimit;           // +0x78
    bool       mbFlag7c;             // +0x7c
    uint8_t    pad7d[7];
    GoalEntry* mpGoals;              // +0x84
};

class ScenarioData {
public:
    int           GetCount();                                             // 0x00f3be30
    ActData*      GetAct(int act);                                        // 0x00f3be60
    int           GetActIndex(int act);                                   // 0x00f3bec0
    ScenarioItem* GetItem(int act, int index);                            // 0x00f3bf00
    int           GetItemObjectID(int* selected);                         // 0x00f3d780
    void*         IsValidSelection(int id);                               // 0x00f3dc70
    void*         Find(int id);                                           // 0x00f3e8a0
    void          Commit();                                               // 0x00f427c0
    void          MoveItem(int act, int index);                           // 0x00f43830
    void          RemoveAct(int act);                                     // 0x00f44210
    int           InsertAct(int act);                                     // 0x00f44a40
    void          BeginEdit();                                            // 0x00f45970
    void          EndEdit();                                              // 0x00f45a80
};

class cScenarioTutorialsChecklistUI {
public:
    void ToggleHint(int a, int b);                                        // 0x00efbbe0
};

class cScenarioMenu {
public:
    void Refresh();                                                       // 0x00ef7a80
};
class cScenarioUI {
public:
    cScenarioMenu* GetMenu(int index);                                    // 0x00ed4b50
};

struct GameGlobals {
    uint32_t pad00[5];
    cScenarioUI* mpUI;                                                    // +0x14
    uint32_t pad18[0x74 / 4 - 6];
    ScenarioData* mpData;                                                 // +0x74
    uint32_t pad78[(0xd4 - 0x78) / 4];
    cScenarioTutorialsChecklistUI* mpChecklist;                           // +0xd4
};
extern GameGlobals* g_16c7aa4;
inline ScenarioData* GetScenarioData() { return g_16c7aa4->mpData; }

class cAvatarSelection {
public:
    PV2 PV
    virtual int GetSelectedWindow();                                      // +0x0c
};
struct cAvatar {
    uint8_t pad[0x5a8];
    cAvatarSelection mSelection;                                          // +0x5a8
};
class cGameNounManager {
public:
    cAvatar* GetAvatar();                                                 // 0x00b1fdb0
};
cGameNounManager* __cdecl NounManager();                                  // 0x00b3d300

class cScenarioTutorials {
public:
    void SetSelectedWindow(int window);                                   // 0x00efe930
    void SurfaceQuery(int behavior);                                      // 0x00f00380
};
extern cScenarioTutorials g_15ad328;

class cPanelPart {
public:
    void Update();                                                        // 0x00ee30d0
};

extern "C" __declspec(dllimport) long __cdecl _wtol(const wchar_t* s);

// globals
extern float gToggleGrid;                                                 // 0x016c77b0
extern float gToggleSnap;                                                 // 0x016c77ac
extern const uint32_t kTimeLimits[6];                                     // 0x0148a4fc
extern const uint32_t kTimeLimitCount;                                    // 0x0148a514
extern const uint32_t kChoiceIDs[11];                                     // 0x0148a518
extern const uint32_t kChoiceIcons[12];                                   // 0x0148a544

// helpers (all __cdecl)
int   __cdecl ScenarioTutorials_GetActive();                              // 0x00efc520
void  __cdecl ScenarioTutorials_SetActive(int act);                       // 0x00efc8c0
int*  __cdecl GetSelectedBehavior();                                      // 0x00efc8f0
int   __cdecl GetCurrentBehaviorSet();                                    // 0x00efe5b0
bool  __cdecl GetSelectedID(int* out);                                    // 0x00edd2d0
IWindow* __cdecl FindSlotWindow(IWindow* w);                              // 0x00edca20
int   __cdecl GetSlotIndex(IWindow* w);                                   // 0x00edca60
bool  __cdecl IsSlotID(uint32_t id);                                      // 0x00edca90
bool  __cdecl IsButtonChecked(IWindow* w);                                // 0x00edcf30
void  __cdecl ListChoices(ChoiceVector* v, uint32_t id, int selected);    // 0x00edd310
bool  __cdecl IsChoiceAvailable(ChoiceVector* v, int set, int index);     // 0x00edd370
void  __cdecl GetChoiceName(ChoiceVector* v, int selected, SP::cString* name); // 0x00edd020
bool  __cdecl AssignString(void* dst, const wchar_t** text);              // 0x00edfce0
bool  __cdecl AssignBool(bool* dst, bool* value);                         // 0x00edfd30
bool  __cdecl AssignFromTable(int* dst, int index, const uint32_t* table, const uint32_t* count); // 0x00edfd70
bool  __cdecl AssignInt(int* dst, int* value);                            // 0x00edfda0
void  __cdecl MoveWindowTo(IWindow* w, Point p);                          // 0x00806ca0
bool  __cdecl IsSlotCompatible(int selected, int a, int b, int act);      // 0x00ee3800
bool  __cdecl CanPlace(ScenarioItem* item, int selected, uint32_t controlID, int index, bool commit); // 0x00ee41e0
bool  __cdecl IsTextFieldActive(IWindow* w, int a, int b);                // 0x00ec7490
bool  __cdecl IsEditing();                                                // 0x008053b0
void  __cdecl SetWindowVisible(IWindow* w, bool visible);                 // 0x00e12f80
void  __cdecl SetPageLabel(IWindow* w, int page);                         // 0x00ed1350
bool  __cdecl EndModal(IWindow* w, int ok, bool b);                      // 0x00809c50
bool  __cdecl BeginModal(IWindow* w, void* proc, bool b);                 // 0x008099a0
int   __cdecl GetRecorderState();                                         // 0x00435e90
void  __cdecl PlayUISound(uint32_t id, int state);                        // 0x00435ed0
void  __cdecl SetGlobalProperty(int id, float value);                     // 0x005ca880
void* __cdecl GetObjectByID(int id);                                      // 0x00b18e00
void  __cdecl ClearBehaviorSelection();                                   // 0x00ecb730
void  __cdecl ShowItemPanel(ScenarioItem* item);                          // 0x00f0bc80
void  __cdecl OnPieMenuChoice(void* context, int choice);                 // 0x00ee3430
void  __cdecl OnPieMenuMoved(void* context);                              // 0x00ee3400

class IPanelBase {
public:
    virtual void Destroy();
    uint32_t mRefCount;
};
class IPanelHandler {
public:
    virtual void HandleMessage();
};

namespace SP {
class cScenarioEditModeBehaviorUI : public IPanelBase, public IWinProc, public IPanelHandler {
public:
    uint32_t     pad10[2];
    cPanelPart*  mpPart;                // +0x18
    uint32_t     pad1c;
    IWindow*     mpWindow;              // +0x20
    uint32_t     pad24;
    IWindow*     mpPieWindow;           // +0x28
    uint32_t     pad2c[5];
    cSPUILayout* mpRenameLayout;        // +0x40
    cSPUILayout* mpDeleteLayout;        // +0x44
    uint32_t     pad48[0x1d];
    cSPUIPieMenu* mpPieMenu;            // +0xbc
    uint8_t      padc0[5];
    bool         mbNameFocused;         // +0xc5
    bool         mbPieMenuShown;        // +0xc6
    uint8_t      padc7;
    int          mPieSelection;         // +0xc8
    int          mPieSet;               // +0xcc
    int          mPieIndex;             // +0xd0
    AutoRefCount<IWindow> mpDragWindow; // +0xd4
    AutoRefCount<IWindow> mpDragParent; // +0xd8
    RectT        mDragArea;             // +0xdc
    uint32_t     mDragShade;            // +0xec
    uint32_t     padf0[5];
    int          mSlotA;                // +0x104
    int          mSlotB;                // +0x108

    void CommitName(IWindow* w, ActData* act);                            // 0x00ee3540
    void Refresh();                                                       // 0x00ee31d0
    void OnDragEnd();                                                     // 0x00edd810
    void OnNameFocus();                                                   // 0x00eddb00
    void OnNameBlur();                                                    // 0x00edcb10
    void OnButtonDefault();                                               // 0x00edcb40
    void ToggleGridButton();                                              // 0x00eddbe0
    void OnShare();                                                       // 0x00ee40f0
    cSPUIPieMenu* GetPieMenu() { return mpPieMenu; }

    virtual bool HandleUIMessage(IWindow* window, const Message& msg);
};
}

using namespace SP;

// @ 0x00ee4390
bool cScenarioEditModeBehaviorUI::HandleUIMessage(IWindow* window, const Message& msg)
{
    ScenarioData* data = g_16c7aa4->mpData;
    if (data) {
    int act = ScenarioTutorials_GetActive();
    ActData* actData = data->GetAct(act);
    if (actData) {
    switch (msg.mType) {
    case 1: {
        IWindow* main = WindowManager()->GetMainWindowIndex(0);
        if (main->GetControlID() == 0x7df4c98) {
            int key = msg.keys.key;
            if (key == 0xd || key == 0xe) {
                CommitName(main, actData);
                WindowManager()->SetFocusWindow(0, main->GetParent());
                return false;
            }
        }
        break;
    }

    case 8: {
        if (mpDragWindow != msg.mWindow)
            break;
        const RectT& area = msg.mWindow->GetRealArea();
        Point pos;
        pos.x = msg.mouse.x + area.x1;
        pos.y = area.y1 + msg.mouse.y;
        MoveWindowTo(msg.mWindow, pos);
        uint32_t color = 0xffffffff;
        int selected;
        if (GetSelectedID(&selected)) {
            bool ok;
            if (msg.mWindow->GetControlID() == 0x715cdc0) {
                ok = IsSlotCompatible(selected, mSlotA, mSlotB,
                                      GetScenarioData()->GetActIndex(ScenarioTutorials_GetActive()));
            } else {
                int index = GetSlotIndex(mpDragParent);
                ScenarioItem* item = data->GetItem(act, index);
                ok = CanPlace(item, selected, msg.mWindow->GetControlID(), index, false);
            }
            color = ok ? 0xff00ff00 : 0xffff0000;
        }
        msg.mWindow->SetShadeColor(color);
        Point global = msg.mWindow->ToGlobalCoordinates(Point(msg.mouse.x, msg.mouse.y));
        Message copy = msg;
        copy.mouse.x = global.x;
        copy.mouse.y = global.y;
        WindowManager()->SendMsg(0, WindowManager()->GetMainWindow(), copy, false);
        return false;
    }

    case 7: {
        if (mpDragWindow != msg.mWindow)
            break;
        OnDragEnd();
        int* selected = GetSelectedBehavior();
        if (!selected)
            break;
        switch (msg.mWindow->GetControlID()) {
        case 0x715cdc0: {
            if (!GetScenarioData()->IsValidSelection(GetCurrentBehaviorSet()))
                break;
            if (!IsSlotCompatible(*selected, mSlotA, mSlotB,
                                  GetScenarioData()->GetActIndex(ScenarioTutorials_GetActive())))
                break;
            mpPieMenu->RemoveAllItems();
            SP::cString name;
            ChoiceVector choices;
            int set = GetCurrentBehaviorSet();
            mPieSet = set;
            data->Find(*selected);
            int index = GetSlotIndex(FindSlotWindow(msg.mWindow));
            for (uint32_t i = 0; i < 11; i++) {
                uint32_t id = kChoiceIDs[i];
                ListChoices(&choices, id, *selected);
                bool enabled = IsChoiceAvailable(&choices, set, index);
                GetChoiceName(&choices, *selected, &name);
                if (mSlotB)
                    enabled = mSlotB == id;
                uint32_t color;
                if (enabled)
                    color = ColorRGBToU32(ColorRGB(1.0f, 1.0f, 1.0f));
                else
                    color = ColorRGBToU32(ColorRGB(1.0f, 0.0f, 0.0f));
                mpPieMenu->AddItem(kChoiceIcons[id], name.GetText(), color, enabled);
            }
            mpPieMenu->SetCallback(OnPieMenuChoice, this);
            void* object = GetObjectByID(data->GetItemObjectID(selected));
            HideOnMoveRef anchor(
                new ("Simulator/cHideOnMoveScreenPosition", 0, 0, 0, 0)
                    cHideOnMoveScreenPosition(object, OnPieMenuMoved, this));
            cHideOnMoveScreenPosition* pAnchor = anchor.mpObject;
            float x, y;
            pAnchor->GetScreenPosition(&x, &y);
            mpPieMenu->Show(x, y, pAnchor, 0xb);
            mPieSelection = *selected;
            mPieIndex = index;
            mbPieMenuShown = true;
            PlayUISound(0xb8a2c0b6, GetRecorderState());
            WindowManager()->SetFocusWindow(0, mpPieWindow);
            Refresh();
            g_16c7aa4->mpChecklist->ToggleHint(0x68, 0x69);
            g_16c7aa4->mpChecklist->ToggleHint(0x79, 0x7a);
            pAnchor->Release();
            return false;
        }
        case 0x7394420:
        case 0x75e1200: {
            if (!GetScenarioData()->IsValidSelection(GetCurrentBehaviorSet()))
                break;
            int index = GetSlotIndex(FindSlotWindow(msg.mWindow));
            ScenarioItem* item = data->GetItem(act, index);
            if (!CanPlace(item, *selected, msg.mWindow->GetControlID(), index, true))
                break;
            if (!AssignInt(msg.mWindow->GetControlID() == 0x7394420 ? &item->mBehaviorA : &item->mBehaviorB,
                           selected))
                break;
            GetScenarioData()->Commit();
            Refresh();
            if (cAvatar* avatar = NounManager()->GetAvatar())
                g_15ad328.SetSelectedWindow(avatar->mSelection.GetSelectedWindow());
            if (item->mKind == 6)
                g_16c7aa4->mpChecklist->ToggleHint(0x7e, 0x7f);
            return false;
        }
        }
        break;
    }

    case 0x17:
        if (msg.mSrc->GetControlID() == 0x743b978) {
            GetUTFWinManager()->SetFocusWindow(0, GetUTFWinManager()->GetMainWindow());
            return false;
        }
        break;

    case 0x1c: {
        switch (msg.focus.window->GetControlID()) {
        case 0x5ca82b7:
        case 0x7ccbd48:
            OnNameBlur();
            break;
        case 0x7df4c98:
            if (msg.focus.a0 != 0)
                return false;
            CommitName(msg.focus.window, actData);
            break;
        }
        if (msg.focus.a0 != 0)
            break;
        if (mbNameFocused && !IsEditing() && !IsTextFieldActive(mpWindow, 0, 1)) {
            PlayUISound(0x1db24d95, GetRecorderState());
            SetWindowVisible(mpWindow->FindWindowByID(0x75f60b0, true), false);
            mbNameFocused = false;
        }
        if (mbPieMenuShown && !IsTextFieldActive(mpPieWindow, 0, 1)) {
            mpPieMenu->Hide();
            mbPieMenuShown = false;
            mPieSelection = -1;
            Refresh();
        }
        IWindow* field = msg.focus.window;
        switch (field->GetControlID()) {
        case 0x710a140: {
            const wchar_t* text = field->GetCaption();
            AssignString(actData->mDescription, &text);
            return false;
        }
        case 0x743b978: {
            const wchar_t* text = field->GetCaption();
            AssignString(actData->mName, &text);
            return false;
        }
        }
        break;
    }

    case 0x1b: {
        switch (msg.focus.window->GetControlID()) {
        case 0x5ca82b7:
        case 0x7ccbd48:
            OnNameFocus();
            break;
        }
        if (msg.focus.a0 != 0)
            break;
        if (msg.focus.window->GetControlID() != 0x743b978)
            break;
        SetWindowVisible(mpWindow->FindWindowByID(0x75f60b0, true), true);
        SetPageLabel(mpWindow->FindWindowByID(0x453ef531, true), 1);
        PlayUISound(0x72d342a9, GetRecorderState());
        mbNameFocused = true;
        mpPart->Update();
        return false;
    }

    case 0x287259f6:
        switch (msg.button.controlID) {
        case 0x447c040:
            PlayUISound(0x956eae88, GetRecorderState());
            ToggleGridButton();
            return false;

        case -15:
        case -14:
            EndModal(WindowManager()->GetModalWindow(), msg.button.controlID == -15, true);
            PlayUISound(0x1db24d95, GetRecorderState());
            return false;

        case 0x59434c0:
            PlayUISound(0x13bed0aa, GetRecorderState());
            OnShare();
            return false;

        case 0x7461828: {
            ScenarioItem* item = data->GetItem(act, GetSlotIndex(msg.mSrc));
            bool checked = IsButtonChecked(msg.mSrc);
            AssignBool(&item->mbEnabled, &checked);
            PlayUISound(0x7b802df5, GetRecorderState());
            return false;
        }

        case 0x743bc38:
            PlayUISound(0xc433d97a, GetRecorderState());
            gToggleGrid = (float)(gToggleGrid == 0.0f);
            SetGlobalProperty(0x2f77e2a9, gToggleGrid);
            ToggleGridButton();
            data->BeginEdit();
            if (act == data->GetCount() - 1)
                ScenarioTutorials_SetActive(act - 1);
            data->RemoveAct(act);
            data->EndEdit();
            Refresh();
            return false;

        case 0x73bbc38: {
            int index = GetSlotIndex(msg.mSrc);
            data->BeginEdit();
            data->MoveItem(act, index);
            data->EndEdit();
            PlayUISound(0x29a5412f, GetRecorderState());
            Refresh();
            data->Commit();
            return false;
        }

        case 0x7462210: {
            int limit = IsButtonChecked(msg.mSrc) ? 0x3c : -1;
            AssignInt(&actData->mTimeLimit, &limit);
            PlayUISound(0xe76c9b4f, GetRecorderState());
            Refresh();
            return false;
        }

        case 0x7bd2d40:
            BeginModal(mpRenameLayout->FindWindowByID(0x71725b0, true), static_cast<IPanelHandler*>(this), true);
            PlayUISound(0x72d342a9, GetRecorderState());
            return false;

        case 0x74656a0: {
            ScenarioItem* item = data->GetItem(act, GetSlotIndex(msg.mSrc));
            ClearBehaviorSelection();
            ShowItemPanel(item);
            PlayUISound(0x72d342a9, GetRecorderState());
            return false;
        }

        case 0x7bd2db8:
            BeginModal(mpDeleteLayout->FindWindowByID(0x7172600, true), static_cast<IPanelHandler*>(this), true);
            PlayUISound(0x72d342a9, GetRecorderState());
            return false;

        case 0x7bd2dd0: {
            data->BeginEdit();
            int newAct = data->InsertAct(ScenarioTutorials_GetActive() + 1);
            if (newAct > 0)
                ScenarioTutorials_SetActive(newAct);
            data->EndEdit();
            Refresh();
            PlayUISound(0x7858f486, GetRecorderState());
            gToggleSnap = (float)(gToggleSnap == 0.0f);
            SetGlobalProperty(0xbd6db48, gToggleSnap);
            ToggleGridButton();
            return false;
        }

        case 0x5ca82b7:
        case 0x4a1cb6d:
        case 0x7ccbd48:
            OnButtonDefault();
            return false;

        default:
            if (msg.button.controlID >= 0x743b8e1 && msg.button.controlID < 0x743b8e9) {
                ScenarioTutorials_SetActive(msg.button.controlID - 0x743b8e1);
                PlayUISound(0xe10deda0, GetRecorderState());
                Refresh();
                return false;
            }
            break;

        case 0x453ef531:
            SetWindowVisible(mpWindow->FindWindowByID(0x75f60b0, true), false);
            PlayUISound(0x1db24d95, GetRecorderState());
            mbNameFocused = false;
            return false;

        case 0x7e1fe70: {
            bool checked = IsButtonChecked(msg.mSrc);
            AssignBool(&actData->mbFlag7c, &checked);
            PlayUISound(0xe76c9b4f, GetRecorderState());
            Refresh();
            return false;
        }

        case 0x7e1f2f8: {
            int index = GetSlotIndex(msg.mSrc);
            if (actData->mpGoals[index].mCount == 0) {
                IWindow* field = msg.mSrc->GetParent()->FindWindowByID(0x7df4c98, false);
                int count = _wtol(field->GetCaption());
                AssignInt(&actData->mpGoals[index].mCount, &count);
            } else {
                int count = 0;
                AssignInt(&actData->mpGoals[index].mCount, &count);
            }
            Refresh();
            GetScenarioData()->Commit();
            PlayUISound(0xe76c9b4f, GetRecorderState());
            return false;
        }
        }
        break;

    case 0x4f5527e8:
        if (msg.button.controlID == 0x721a150) {
            AssignFromTable(&actData->mTimeLimit, msg.button.value, kTimeLimits, &kTimeLimitCount);
            PlayUISound(0xe76c9b4f, GetRecorderState());
        }
        // fall through
    case 6:
        if (IsSlotID(msg.mWindow->GetControlID()) && !mpDragWindow) {
            mpDragWindow = msg.mWindow;
            mDragArea = msg.mWindow->GetRealArea();
            mpDragParent = msg.mWindow->GetParent();
            Point global = msg.mWindow->ToGlobalCoordinates(Point(mDragArea.x1, mDragArea.y1));
            mpDragParent->RemoveWindow(msg.mWindow);
            mDragShade = mpDragWindow->GetShadeColor();
            LayoutRoot()->FindWindow(0x5b598fa)->AddWindow(msg.mWindow);
            msg.mWindow->SetLayoutLocation(global.x, global.y);
            WindowManager()->SetCaptureWindow(1, msg.mWindow);
            mpDragWindow->SetCursorID(0x747d67c);
            PlayUISound(0xc29e2486, GetRecorderState());
            g_15ad328.SetSelectedWindow(0);
            g_16c7aa4->mpUI->GetMenu(0)->Refresh();
            return false;
        }
        if (msg.mouse.button == 0x3ea &&
            (msg.mWindow->GetControlID() == 0x715cdd0 || msg.mWindow->GetControlID() == 0x75e1208)) {
            ScenarioItem* item = data->GetItem(act, GetSlotIndex(FindSlotWindow(msg.mWindow)));
            int behavior = item->mBehaviorA;
            if (msg.mWindow->GetControlID() == 0x75e1208)
                behavior = item->mBehaviorB;
            g_15ad328.SurfaceQuery(behavior);
        }
        break;
    }
    }
    }
    return false;
}
