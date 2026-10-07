// Slice s00ee5480 -- UI::cScenarioEditModeScriptUI::HandleUIMessage (0x00ee5480, 5117 bytes).
//
// The scenario editor's "script" (goals / act settings) panel window procedure: drag-and-drop
// of goal icons (mouse down/move/up), the scenario name text field, the act/goal buttons and
// the act-setting sliders. Always returns false (never consumes the message).
//
// `this` is the IWinProc sub-object at +0xc of the panel (vtable 0x0148a80c, IWinProc vtable
// 0x0148a838); member offsets below are those of the full object.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE (UI module: no /EHsc, no /fp:fast).
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

// EA math helper (SSE asm): round-up float to int
__forceinline int CeilToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        add      ecx, 1
        ucomiss  xmm1, xmm0
        cmovb    eax, ecx
    }
}

// ---------------------------------------------------------------------------------------------
// UTFWin
// ---------------------------------------------------------------------------------------------
struct Point {
    float x, y;
    Point() {}
    Point(float _x, float _y) : x(_x), y(_y) {}
};

struct RectT {
    float x1, y1, x2, y2;
    RectT& operator=(const RectT& other);                       // 0x00572600
};

class IWindow {
public:
    PV4
    virtual IWindow* GetParent();                               // +0x10
    PV2
    virtual uint32_t GetControlID();                            // +0x1c
    PV4 PV2
    virtual const RectT& GetRealArea();                         // +0x38
    virtual const wchar_t* GetCaption();                        // +0x3c
    PV4 PV2 PV
    virtual void SetShadeColor(uint32_t color);                 // +0x5c
    PV4
    virtual void SetLayoutLocation(float x, float y);           // +0x70
    PV
    virtual void SetCursorID(uint32_t id);                      // +0x78
    PV16 PV
    virtual Point ToGlobalCoordinates(Point local);             // +0xc0
    PV4 PV
    virtual void AddWindow(IWindow* window);                    // +0xd8
    virtual void RemoveWindow(IWindow* window);                 // +0xdc
    PV2
    virtual void BringToFront(IWindow* window);                 // +0xe8
    PV
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive); // +0xf0
};

struct Message {
    IWindow* mSrc;             // +0x00
    IWindow* mDst;             // +0x04
    uint32_t mType;            // +0x08
    union {
        struct { float x, y; int state; int button; } mouse;
        struct { int a0, a1, a2; union { IWindow* window; int a3; }; } args;
    };
};

enum {
    kMsgMouseDown = 0x06,
    kMsgMouseUp = 0x07,
    kMsgMouseMove = 0x08,
    kMsgMouseLeave = 0x1c,
    kMsgButtonSelect = 0x04cab02d,
    kMsgButtonFocus = 0x0685a2b9,
    kMsgSliderRelease = 0x07a44749,
    kMsgSliderPress = 0x07a4489c,
    kMsgComponentActivated = 0x287259f6,
    kMsgValueChanged = 0xef00a884,
};

class IWinProc {
public:
    PV4 PV2
    virtual bool HandleUIMessage(IWindow* window, const Message& msg) = 0;
};

class IWindowManager {
public:
    virtual void func0();
    virtual IWindow* GetMainWindow();                                        // +0x04
    PV2
    virtual void SendMsg(IWindow* src, IWindow* dst, const Message& msg, bool inheritable); // +0x10
    PV8 PV4 PV
    virtual IWindow* GetMainWindowIndex(int index);                          // +0x48
    PV2 PV
    virtual void SetMainWindowIndex(int index, IWindow* window);             // +0x58
};
IWindowManager* WindowManager();                                             // 0x0067caa0

class IMessageManager {
public:
    PV4 PV
    virtual void PostMSG(uint32_t messageID, uint32_t data, int flags);      // +0x14
};
IMessageManager* MessageServer();                                            // 0x0067dcc0

struct cSPUILayoutManager {
    IWindow* FindWindowByID(uint32_t id);                                    // 0x00810620
};
cSPUILayoutManager* UILayoutManager();                                       // 0x0080fee0

template <typename T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount& operator=(T* p);                                           // 0x00b5f950
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

struct string16 {                                                            // eastl::basic_string<wchar_t>
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    string16();
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf();                                                   // 0x00933960
};
extern wchar_t gEmptyString[2];                                              // 0x01667bac
inline string16::string16() : mpBegin(gEmptyString), mpEnd(gEmptyString), mpCapacity(gEmptyString + 1) {}
bool operator==(const string16& a, const wchar_t* b);                        // 0x006ab760

struct IValueControl {
    PV8
    virtual int GetValue();                                                  // +0x20
};
IValueControl* GetValueControl(IWindow* window);                             // 0x005ff6a0

// ---------------------------------------------------------------------------------------------
// Scenario
// ---------------------------------------------------------------------------------------------
struct ResourceKey { uint32_t instanceID, typeID, groupID; };
struct Triple { int a, b, c; };

struct cScenarioAct {                       // 0x4e0 bytes
    uint8_t b00;
    bool mbFlag1;                           // +0x01
    bool mbFlag2;                           // +0x02
    uint8_t b03;
    uint32_t pad04[0x120];
    float mValue484;                        // +0x484
    float pad488;
    float mValue48C;                        // +0x48c
    float mValue490;                        // +0x490
    float mValue494;                        // +0x494
    float mValue498;                        // +0x498
    float mValue49C;                        // +0x49c
    float mValue4A0;                        // +0x4a0
    int mState4A4;                          // +0x4a4
    int pad4a8;
    int mSetting4AC;                        // +0x4ac
    int mSetting4B0;                        // +0x4b0
    int mSetting4B4;                        // +0x4b4
    int mSetting4B8;                        // +0x4b8
    uint32_t pad4bc[9];
    cScenarioAct(const cScenarioAct& other);  // 0x00dfd080
    ~cScenarioAct();                          // 0x00dfbba0
};

struct cScenarioData {
    ResourceKey mKey;                       // +0x00
    uint32_t pad0c[5];
    bool mbFlag20;                          // +0x20
    int mMode24;                            // +0x24
    Triple mValue28;                        // +0x28
    uint32_t pad34[5];
    int mMode48;                            // +0x48
    int pad4c;
    Triple mValue50;                        // +0x50
    uint32_t pad5c[5];
    cScenarioAct* mpActs;                   // +0x70
    bool Check25670();                      // 0x00f25670
    bool Check253e0();                      // 0x00f253e0
    bool Check27670();                      // 0x00f27670
    void GetName(string16& out);            // 0x00f28b80
    void SetName(const wchar_t* name);      // 0x00f293b0
};

struct cScenarioResource {
    cScenarioData* GetData(uint32_t id);    // 0x00f3e8a0
    int GetActCount();                      // 0x00f3be30
    void ClearAndPropagate();               // 0x00f40370
    void Update41a10(uint32_t id);          // 0x00f41a10
    void CommitEdit();                      // 0x00f427c0
    void BeginEdit();                       // 0x00f45970
    void EndEdit();                         // 0x00f45a80
};

struct cScenarioTerrainUI { void Refresh31d0(); };      // 0x00ee31d0 receiver
struct cScenarioEditHistory {
    void Undo7a80();                                     // 0x00ef7a80
};
struct cScenarioEditView {
    uint32_t pad00[5];
    struct Sub { void Update39a0(uint32_t id); }* mpSub;  // +0x14 (0x00ed39a0)
    cScenarioTerrainUI* mpTerrainUI;                       // +0x18
    cScenarioTerrainUI* GetTerrainUI();                    // 0x006c0200 (returns mpTerrainUI)
    cScenarioEditHistory* GetHistory(int index);          // 0x00ed4b50
};
struct cScenarioTutorialsChecklistUI { void ToggleHint(int a, int b); };  // 0x00efbbe0

struct cScenarioMode {
    uint32_t pad00[5];
    cScenarioEditView* mpEditView;          // +0x14
    uint32_t pad18[0x17];
    cScenarioResource* mpResource;          // +0x74
    uint32_t pad78[0x17];
    cScenarioTutorialsChecklistUI* mpChecklistUI; // +0xd4
};
extern cScenarioMode* gScenarioMode;        // 0x016c7aa4

int GetActiveAct();                         // 0x00efc520
void SetActiveAct(int act);                 // 0x00efc8c0
int GetRecorderState();                     // 0x00435e90
void PlayUISound(uint32_t soundID, int state); // 0x00435ed0

struct IScriptHandler {
    PV4 PV2 PV
    virtual void OnChanged(uint32_t id);    // +0x1c
};

// helpers of this module (cdecl)
bool GetDropTarget(int* target);                                                    // 0x00edd2d0
int GetGoalIndex(IWindow* window);                                                  // 0x00edcce0
void Checklist_PropertyDispatcher(cScenarioData* d, cScenarioAct* a, uint32_t id, int target, int goal); // 0x00ee0eb0
bool CanDropGoal(cScenarioAct* a, uint32_t id, int target, int goal);               // 0x00eddf30
void CenterWindow(IWindow* window, Point p);                                        // 0x00806ca0
void ReleaseWindowRef(IWindow* window, bool b);                                      // 0x00e12f80
bool IsSecondaryButton(IWindow* window);                                            // 0x00edce00
void ShowModePicker(uint32_t id, IScriptHandler* h, bool secondary, IWindow* w);    // 0x00edfcc0
IWindow* FindChildByID(IWindow* window, uint32_t id);                               // 0x00edc9e0
uint32_t GetSliderID(IWindow* window);                                              // 0x008050f0
void OnSlider8c0(cScenarioData* d, cScenarioAct* a, float oldValue);                // 0x00ede8c0
void OnSlider400(cScenarioData* d, cScenarioAct* a, float oldValue);                // 0x00ede400
void OnSlider2b0(cScenarioData* d, cScenarioAct* a, float oldValue);                // 0x00ede2b0
void OnSlider9f0(cScenarioData* d, cScenarioAct* a, float oldValue);                // 0x00ede9f0
void OnSlider530(cScenarioData* d, cScenarioAct* a, float oldValue);                // 0x00ede530
void OnSlider790(cScenarioData* d, cScenarioAct* a, float oldValue);                // 0x00ede790
void OnSlider660(cScenarioData* d, cScenarioAct* a, float oldValue);                // 0x00ede660
Triple PickObject(uint32_t kind, uint32_t id, cScenarioData* d);                    // 0x00eef810
void PreparePicker(IWindow* window, int flags);                                     // 0x00edf2c0
void PickerCallback();                                                              // 0x00edf370
void CreateCallbackWinProc(IWindow* window, void (*callback)(), int a, int b, IScriptHandler* h); // 0x008085d0
bool IsGoalButton(IWindow* window);                                                 // 0x00edcf30
bool ToggleGoalFlag(cScenarioData* d, cScenarioAct* a, bool b);                     // 0x00ee01e0
void UpdateGoalFlag(uint32_t id, bool b);                                           // 0x00ee1140
void ResetTerrain();                                                                // 0x00ecb730
void ApplyActData(cScenarioData* d, int mode);                                      // 0x00f0bdf0
void SetActState(uint32_t id, int act, int state);                                  // 0x00ee0960
void ToggleBoolUndoable(bool* dst, const bool* src);                                // 0x00edfd30
void PrepareModeChange();                                                           // 0x00f0bea0
void ApplyModeChange(cScenarioData* d, int mode);                                   // 0x00ecb520
bool SetActSetting4AC(cScenarioData* d, cScenarioAct* a, int index);                // 0x00ede110
void ShowActSettingTip(uint32_t id, uint32_t tip);                                  // 0x00ed8950
bool Checklist_SetProperty4a8(cScenarioData* d, cScenarioAct* a, int index);        // 0x00ee0310
bool Checklist_SetProperty4b0(cScenarioData* d, cScenarioAct* a, int index);        // 0x00ee0450
bool Checklist_SetProperty4b4(cScenarioData* d, cScenarioAct* a, int index);        // 0x00ee0590
bool SetActSetting4B8(cScenarioData* d, cScenarioAct* a, int index, uint32_t id);   // 0x00ee06d0
void ReadSliderValue(int value, float* dst, bool* changedA, bool* changedB, uint32_t sound); // 0x00edfa30
void FormatNumber(double value, wchar_t* buf, int size, int decimals);              // 0x00881f00
void FormatInteger(__int64 value, wchar_t* buf, int size);                          // 0x00881ae0
void UpdateSliderLabel(IWindow* w, float value, bool a, bool b, uint32_t sound, const wchar_t* text); // 0x00edf830
float ComputeSliderDisplay(ResourceKey key, float value);                           // 0x00eeebd0
void SetActFlag(uint32_t id, bool b);                                               // 0x00ee1200
float GetSliderValue(IWindow* window);                                              // 0x00edcfc0

extern const uint32_t kSetting4ACTips[];    // 0x0148a488
extern const uint32_t kSetting4B0Tips[];    // 0x0148a4a0
extern const uint32_t kSetting4B4Tips[];    // 0x0148a4b0
extern const uint32_t kSetting4B8Tips[];    // 0x0148a4c0

// ---------------------------------------------------------------------------------------------
// the panel
// ---------------------------------------------------------------------------------------------
class cScenarioEditModeUIBase {
public:
    virtual ~cScenarioEditModeUIBase();
    uint32_t m04;
    uint32_t m08;
};

namespace UI {
class cScenarioEditModeScriptUI : public cScenarioEditModeUIBase, public IWinProc {
public:
    uint32_t m10;
    IScriptHandler* mpHandler;              // +0x14
    IWindow* mpMainWindow;                  // +0x18
    uint32_t m1c;
    uint32_t mScenarioID;                   // +0x20
    int mbTextEditing;                      // +0x24
    int mGoalPage;                          // +0x28
    float mSliderStartValue;                // +0x2c
    AutoRefCount<IWindow> mpDragWindow;     // +0x30
    AutoRefCount<IWindow> mpDragParent;     // +0x34
    RectT mDragArea;                        // +0x38

    void Refresh();                         // 0x00ee16f0
    void EndDrag();                         // 0x00edf410
    IWindow* FindGoalWindow(uint32_t id);   // 0x00edf070
    void SelectGoal(int id);                // 0x00edf090
    void ClearSelection();                  // 0x00edf240
    void ShowGoalSummary();                 // 0x00ee30d0

    virtual bool HandleUIMessage(IWindow* window, const Message& msg);
};

// @ 0x00ee5480
bool cScenarioEditModeScriptUI::HandleUIMessage(IWindow* window, const Message& msg)
{
    if (mScenarioID == (uint32_t)-1 || mScenarioID == (uint32_t)-2)
        return false;
    cScenarioData* data = gScenarioMode->mpResource->GetData(mScenarioID);
    if (!data)
        return false;
    cScenarioAct* act = data->mpActs + GetActiveAct();

    switch (msg.mType) {
    case kMsgMouseUp: {
        if (mpDragWindow != msg.mDst)
            break;
        EndDrag();
        int target;
        if (GetDropTarget(&target)) {
            Checklist_PropertyDispatcher(data, act, mScenarioID, target, GetGoalIndex(msg.mDst));
            if (act->mSetting4B8 == 5 && target == -2)
                gScenarioMode->mpChecklistUI->ToggleHint(0x4f, 0x50);
        }
        Refresh();
        return false;
    }

    case kMsgMouseDown: {
        IWindow* w = msg.mDst;
        if (w->GetControlID() == 0x742c8f8 && mpDragWindow == 0) {
            IWindow* goal = FindGoalWindow(GetGoalIndex(w));
            if (goal) {
                w = goal->FindWindowByID(0x742c8d0, true);
                ReleaseWindowRef(w, true);
            }
        }
        if (!w || w->GetControlID() != 0x742c8d0 || mpDragWindow != 0)
            break;
        mpDragWindow = w;
        mDragArea = w->GetRealArea();
        mpDragParent = w->GetParent();
        Point p = w->ToGlobalCoordinates(Point(mDragArea.x1, mDragArea.y1));
        mpDragParent->RemoveWindow(w);
        UILayoutManager()->FindWindowByID(0x5b598fa)->AddWindow(w);
        w->SetLayoutLocation(p.x, p.y);
        WindowManager()->SetMainWindowIndex(1, w);
        mpDragWindow->SetCursorID(0x747d67c);
        PlayUISound(0xc29e2486, GetRecorderState());
        gScenarioMode->mpEditView->GetHistory(0)->Undo7a80();
        return false;
    }

    case kMsgMouseMove: {
        if (mpDragWindow != msg.mDst)
            break;
        const RectT& area = msg.mDst->GetRealArea();
        CenterWindow(msg.mDst, Point(area.x1 + msg.mouse.x, area.y1 + msg.mouse.y));
        uint32_t color = 0xffffffff;
        int target;
        if (GetDropTarget(&target))
            color = CanDropGoal(act, mScenarioID, target, GetGoalIndex(mpDragParent)) ? 0xff00ff00 : 0xffff0000;
        msg.mDst->SetShadeColor(color);
        Point p = msg.mDst->ToGlobalCoordinates(Point(msg.mouse.x, msg.mouse.y));
        Message m = msg;
        m.mouse.x = p.x;
        m.mouse.y = p.y;
        WindowManager()->SendMsg(0, WindowManager()->GetMainWindow(), m, false);
        return false;
    }

    case kMsgButtonSelect: {
        if (msg.args.a0 == 0x6849100) {
            bool secondary = IsSecondaryButton(msg.mSrc);
            int mode = msg.args.a1;
            int current = secondary ? data->mMode48 : data->mMode24;
            if (mode == current)
                break;
            if (mode == 2 && (secondary ? data->mValue50.a == 0 : data->mValue28.a == 0)) {
                ShowModePicker(mScenarioID, mpHandler, secondary, mpMainWindow);
            } else {
                gScenarioMode->mpResource->BeginEdit();
                if (secondary) {
                    data->mMode48 = mode;
                    Refresh();
                } else {
                    if (data->Check27670() || data->Check253e0()) {
                        if ((current == 2 || current == 1) && mode == 0 && data->mMode48 == 1)
                            data->mMode48 = 0;
                        if (current == 0 && mode == 1 && data->mMode48 == 0)
                            data->mMode48 = 1;
                    }
                    data->mMode24 = mode;
                    gScenarioMode->mpEditView->mpSub->Update39a0(mScenarioID);
                    mpHandler->OnChanged(mScenarioID);
                }
                gScenarioMode->mpResource->Update41a10(mScenarioID);
                gScenarioMode->mpResource->EndEdit();
            }
        }
        PlayUISound(0xe76c9b4f, GetRecorderState());
        return false;
    }

    case kMsgMouseLeave: {
        if (msg.args.a0 != 0)
            break;
        IWindow* w = msg.args.window;
        if (w->GetControlID() == 0x7957ba8) {
            string16 name;
            data->GetName(name);
            if (!(name == w->GetCaption())) {
                gScenarioMode->mpResource->BeginEdit();
                data->SetName(w->GetCaption());
                MessageServer()->PostMSG(0x795b639, mScenarioID, 0);
                gScenarioMode->mpResource->EndEdit();
                Refresh();
            }
        }
        if (mbTextEditing != 0) {
            if (!FindChildByID(WindowManager()->GetMainWindowIndex(0), 0x742be58)) {
                ClearSelection();
                return false;
            }
        }
        break;
    }

    case kMsgButtonFocus: {
        if (msg.args.a0 == 0x6849100) {
            IWindow* w = FindChildByID(msg.mSrc, 0x76c61c8);
            if (w)
                w->GetParent()->BringToFront(w);
            w = FindChildByID(msg.mSrc, 0x2791ba0);
            if (w)
                w->GetParent()->BringToFront(w);
        }
        PlayUISound(0xe76c9b4f, GetRecorderState());
        return false;
    }

    case kMsgSliderPress: {
        if (msg.args.a0 != 0x742cd10)
            break;
        switch (GetSliderID(msg.mSrc)) {
        case 0x7c8a7a8: mSliderStartValue = act->mValue490; break;
        case 0x792bf78: mSliderStartValue = act->mValue484; break;
        case 0x7918320: mSliderStartValue = act->mValue48C; break;
        case 0x7c8a7d0: mSliderStartValue = act->mValue494; break;
        case 0x8918320: mSliderStartValue = act->mValue49C; break;
        case 0x892bf78: mSliderStartValue = act->mValue498; break;
        case 0x9918320: mSliderStartValue = act->mValue4A0; break;
        default: return false;
        }
        gScenarioMode->mpResource->BeginEdit();
        return false;
    }

    case kMsgSliderRelease: {
        if (msg.args.a0 != 0x742cd10)
            break;
        switch (GetSliderID(msg.mSrc)) {
        case 0x7c8a7a8: OnSlider8c0(data, act, mSliderStartValue); break;
        case 0x792bf78: OnSlider400(data, act, mSliderStartValue); break;
        case 0x7918320: OnSlider2b0(data, act, mSliderStartValue); break;
        case 0x7c8a7d0: OnSlider9f0(data, act, mSliderStartValue); break;
        case 0x9918320: OnSlider530(data, act, mSliderStartValue); break;
        case 0x892bf78: OnSlider790(data, act, mSliderStartValue); break;
        case 0x8918320: OnSlider660(data, act, mSliderStartValue); break;
        default: return false;
        }
        gScenarioMode->mpResource->CommitEdit();
        return false;
    }

    case kMsgComponentActivated: {
        int id = msg.args.a0;
        switch (id) {
        case 0x595e0a8:
            ShowGoalSummary();
            PlayUISound(0x1db24d95, GetRecorderState());
            return false;

        case 0x3791005: {
            PlayUISound(0x13bed0aa, GetRecorderState());
            Triple picked = PickObject(0xb10e526f, mScenarioID, data);
            if (picked.a == 0)
                return false;
            gScenarioMode->mpResource->BeginEdit();
            IWindow* mainWindow = mpMainWindow;
            PreparePicker(mainWindow, 0);
            CreateCallbackWinProc(mainWindow, PickerCallback, 2, 0, mpHandler);
            if (IsSecondaryButton(msg.mSrc)) {
                data->mValue50 = picked;
                Refresh();
            } else {
                data->mValue28 = picked;
                gScenarioMode->mpEditView->mpSub->Update39a0(mScenarioID);
                mpHandler->OnChanged(mScenarioID);
            }
            gScenarioMode->mpResource->Update41a10(mScenarioID);
            gScenarioMode->mpResource->EndEdit();
            return false;
        }

        case 0x3791004:
            ShowModePicker(mScenarioID, mpHandler, IsSecondaryButton(msg.mSrc), mpMainWindow);
            return false;

        case 0x742bd98:
        case 0x742bdb0:
        case 0x742bdc0:
        case 0x742bdd0:
            if (IsGoalButton(msg.mSrc)) {
                SelectGoal(msg.args.a0);
                PlayUISound(0x6e649e21, GetRecorderState());
            } else {
                ClearSelection();
                PlayUISound(0xcc089e57, GetRecorderState());
            }
            return false;

        case 0x742bde0: {
            bool goal = IsGoalButton(msg.mSrc);
            if (ToggleGoalFlag(data, act, goal)) {
                Refresh();
                UpdateGoalFlag(mScenarioID, goal);
                gScenarioMode->mpResource->ClearAndPropagate();
            }
            gScenarioMode->mpResource->CommitEdit();
            PlayUISound(0x7b802df5, GetRecorderState());
            return false;
        }

        case 0x791a7c0:
        case 0x791a7c8:
            mGoalPage += (msg.args.a0 == 0x791a7c8) ? 1 : -1;
            PlayUISound(0xe10deda0, GetRecorderState());
            Refresh();
            return false;

        case 0x74656a0:
            ResetTerrain();
            ApplyActData(gScenarioMode->mpResource->GetData(mScenarioID), 2);
            Refresh();
            return false;

        case 0x7ec82c0: {
            cScenarioData* d = gScenarioMode->mpResource->GetData(mScenarioID);
            cScenarioAct actCopy(d->mpActs[GetActiveAct()]);
            if (actCopy.mState4A4 == -1) {
                PlayUISound(0x6e649e21, GetRecorderState());
                SetActState(mScenarioID, GetActiveAct(), 0xa);
            } else {
                PlayUISound(0xcc089e57, GetRecorderState());
                SetActState(mScenarioID, GetActiveAct(), -1);
            }
            Refresh();
            return false;
        }

        case 0x76a93c53: {
            bool value = !data->mbFlag20;
            ToggleBoolUndoable(&data->mbFlag20, &value);
            PlayUISound(0xe76c9b4f, GetRecorderState());
            return false;
        }

        case 0x76a93c50:
        case 0x76a93c51: {
            cScenarioEditView* view = gScenarioMode->mpEditView;
            cScenarioResource* resource = gScenarioMode->mpResource;
            if (!view || !resource)
                return false;
            cScenarioTerrainUI* terrainUI = view->GetTerrainUI();
            if (!terrainUI)
                return false;
            SetActiveAct((GetActiveAct() + (msg.args.a0 == 0x76a93c51 ? 1 : -1)) % resource->GetActCount());
            terrainUI->Refresh31d0();
            Refresh();
            PlayUISound(0xe10deda0, GetRecorderState());
            return false;
        }

        default:
            if (id >= 0x742cbe0 && id < 0x742cbe6) {
                bool changed = false;
                ClearSelection();
                switch (msg.mSrc->GetParent()->GetParent()->GetControlID()) {
                case 0x742bd88: {
                    int index = msg.args.a0 - 0x742cbe0;
                    if (msg.args.a3 == 2 && index != 5 && data->Check25670()) {
                        PrepareModeChange();
                        ApplyModeChange(gScenarioMode->mpResource->GetData(mScenarioID), 1);
                        Refresh();
                        break;
                    }
                    if (index == 5 && data->Check25670()) {
                        PrepareModeChange();
                        ApplyModeChange(gScenarioMode->mpResource->GetData(mScenarioID), 0);
                    } else {
                        ResetTerrain();
                    }
                    changed = SetActSetting4AC(data, act, index);
                    Refresh();
                    if (changed)
                        ShowActSettingTip(mScenarioID, kSetting4ACTips[act->mSetting4AC]);
                    gScenarioMode->mpResource->CommitEdit();
                    if (act->mSetting4AC == 5)
                        gScenarioMode->mpChecklistUI->ToggleHint(0x49, 0x4a);
                    break;
                }
                case 0x742bd98:
                    changed = Checklist_SetProperty4a8(data, act, msg.args.a0 - 0x742cbe0);
                    if (changed)
                        gScenarioMode->mpResource->CommitEdit();
                    break;
                case 0x742bdb0:
                    changed = Checklist_SetProperty4b0(data, act, msg.args.a0 - 0x742cbe0);
                    if (changed) {
                        gScenarioMode->mpResource->CommitEdit();
                        ShowActSettingTip(mScenarioID, kSetting4B0Tips[act->mSetting4B0]);
                    }
                    break;
                case 0x742bdc0:
                    changed = Checklist_SetProperty4b4(data, act, msg.args.a0 - 0x742cbe0);
                    if (changed) {
                        gScenarioMode->mpResource->CommitEdit();
                        ShowActSettingTip(mScenarioID, kSetting4B4Tips[act->mSetting4B4]);
                    }
                    break;
                case 0x742bdd0: {
                    changed = SetActSetting4B8(data, act, msg.args.a0 - 0x742cbe0, mScenarioID);
                    if (changed) {
                        ShowActSettingTip(mScenarioID, kSetting4B8Tips[act->mSetting4B8]);
                        gScenarioMode->mpResource->CommitEdit();
                    }
                    int setting = act->mSetting4B8;
                    if (setting == 5)
                        gScenarioMode->mpChecklistUI->ToggleHint(0x4c, 0x4d);
                    else if (setting == 4)
                        gScenarioMode->mpChecklistUI->ToggleHint(0x5f, 0x60);
                    break;
                }
                }
                PlayUISound(0xe76c9b4f, GetRecorderState());
                if (changed)
                    Refresh();
            }
            break;
        }
        break;
    }

    case kMsgValueChanged: {
        if (msg.args.a0 != 0x742cd10)
            break;
        bool changed;
        wchar_t text[0x20];
        switch (GetSliderID(msg.mSrc)) {
        case 0x7c8a7a8: {
            IValueControl* control = GetValueControl(msg.mSrc);
            int value = control ? control->GetValue() : 0;
            uint32_t sound = 0;
            switch (data->mKey.typeID) {
            case 0x24682294:
            case 0x476a98c7:
                sound = 0x7cc8a4b;
                break;
            case 0x2b978c46:
                sound = 0x7cc8a48;
                break;
            }
            bool changedA, changedB;
            ReadSliderValue(value, &act->mValue490, &changedA, &changedB, sound);
            switch (data->mKey.typeID) {
            case 0x24682294:
            case 0x476a98c7:
                FormatNumber((double)(int)(act->mValue490 * 100.0f), text, 0x20, 0);
                break;
            case 0x2b978c46:
                FormatInteger((__int64)act->mValue490, text, 0x20);
                break;
            }
            UpdateSliderLabel(FindGoalWindow(0x7c8a7a8), act->mValue490, false, false, sound, text);
            return false;
        }
        case 0x792bf78: {
            float value = GetSliderValue(msg.mSrc);
            float scaled = value * 175.0f;
            changed = act->mValue484 != scaled;
            act->mValue484 = scaled;
            if (value == 1.0f)
                gScenarioMode->mpChecklistUI->ToggleHint(0x52, 0x53);
            break;
        }
        case 0x7918320: {
            IValueControl* control = GetValueControl(msg.mSrc);
            int value = control ? control->GetValue() : 0;
            ReadSliderValue(value, &act->mValue48C, &act->mbFlag2, &act->mbFlag1, 0xf69d44ec);
            float display = ComputeSliderDisplay(data->mKey, act->mValue48C);
            FormatInteger(CeilToInt(display), text, 0x20);
            UpdateSliderLabel(FindGoalWindow(0x7918320), act->mValue48C, act->mbFlag2, act->mbFlag1,
                              0xf69d44ec, text);
            SetActFlag(mScenarioID, act->mbFlag1);
            return false;
        }
        case 0x7c8a7d0: {
            IValueControl* control = GetValueControl(msg.mSrc);
            int value = control ? control->GetValue() : 0;
            bool changedA, changedB;
            ReadSliderValue(value, &act->mValue494, &changedA, &changedB, 0x7cc8a44);
            FormatNumber((double)(int)(act->mValue494 * 100.0f), text, 0x20, 0);
            UpdateSliderLabel(FindGoalWindow(0x7c8a7d0), act->mValue494, false, false, 0x7cc8a44, text);
            return false;
        }
        case 0x9918320: {
            float value = GetSliderValue(msg.mSrc) * 49.0f + 1.0f;
            changed = act->mValue4A0 != value;
            act->mValue4A0 = value;
            break;
        }
        case 0x892bf78: {
            float value = GetSliderValue(msg.mSrc) * 50.0f;
            changed = act->mValue498 != value;
            act->mValue498 = value;
            break;
        }
        case 0x8918320: {
            float value = GetSliderValue(msg.mSrc) * 2000.0f;
            changed = act->mValue49C != value;
            act->mValue49C = value;
            break;
        }
        default:
            return false;
        }
        if (changed)
            Refresh();
        return false;
    }
    }
    return false;
}
}  // namespace UI
