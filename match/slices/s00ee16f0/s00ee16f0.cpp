// slice s00ee16f0 -- 0x00ee16f0 (4,452 bytes): the scenario-tutorial checklist panel's
// Refresh().  Earlier note named it UI::cScenarioTutorialsChecklistUI::Refresh (inferred);
// the class here is a local stub (TutorialPanel) with the offsets the function uses.
//
// What it does: looks up the active tutorial entry (g_16c7aa4->f74->Find(mID)); when the
// panel layout is visible and the entry exists it refreshes every widget of the panel
// (title text, prev/next page buttons, category tabs, progress counters, the goal/hint
// rows with icons and images, sliders/number fields formatted via EA::Locale), then always
// syncs the tutorial state (FUN_00ed8a30) and the member at +0x48 (FUN_00ed9990).
//
// Module flags: UI module, /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (SSE mulss/cvttss2si,
// x87 float pushes, no /EHsc frame for the cString/string16 locals, no /GS cookie for the
// wchar_t buffers).
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16

struct ResourceKey {
    uint32_t instanceID;   // +0
    uint32_t typeID;       // +4
    uint32_t groupID;      // +8
};

// ---------------------------------------------------------------------------------------------
// UTFWin (ModAPI IWindow slot names)
// ---------------------------------------------------------------------------------------------
class IWindow {
public:
    PV2 PV
    virtual void* Cast(uint32_t typeID);                                  // +0x0c
    virtual IWindow* GetParent();                                         // +0x10
    PV2
    virtual uint32_t GetControlID();                                      // +0x1c
    PV8 PV4 PV2 PV
    virtual void SetShadeColor(uint32_t color);                           // +0x5c
    PV4 PV2 PV
    virtual void SetFlag(int flag, bool value);                           // +0x7c
    virtual void SetCaption(const wchar_t* caption);                      // +0x80
    PV16 PV8 PV
    virtual void BringToFront(IWindow* w);                                // +0xe8
    PV
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive);         // +0xf0
};

// interface 0xcf428691 (text field)
class ITextField {
public:
    enum { TYPE = 0xcf428691 };
    PV16 PV8
    virtual void SetText(const wchar_t* text, int flags);                 // +0x60
    PV
    virtual void SetMaxLength(int n);                                     // +0x68
};

// interface 0x8ed27e7a (button)
class IButton {
public:
    enum { TYPE = 0x8ed27e7a };
    PV8 PV2
    virtual void SetButtonStateFlag(int flag, bool value);                // +0x28
};

template <class T>
inline T* object_cast(IWindow* w)
{
    return w ? (T*)w->Cast(T::TYPE) : 0;
}

inline void SetButtonFlag(IWindow* w, int flag, bool value)
{
    if (IButton* button = object_cast<IButton>(w))
        button->SetButtonStateFlag(flag, value);
}

// per-category window owned by the panel (array at +0x1c)
class CategoryWinBase {
public:
    PV4 PV2 PV
    virtual void SetEnabled(bool b);                                      // +0x1c
};

class CategoryWinProc {          // secondary base at +4 (what messages carry)
public:
    PV
};

class CategoryWin : public CategoryWinBase, public CategoryWinProc {
public:
    void SetValue(int v);                                                 // 0x00f38bc0
};

// data of message 0x07c41ae9 (category clicked)
struct CategoryMessage {
    uint32_t pad00[2];
    int      mIndex;                  // +0x08
    uint32_t pad0c;
    CategoryWinProc* mpSource;        // +0x10
};

class IRefreshTarget {            // secondary base at +0x24 of the +0x14 object
public:
    PV4 PV2
    virtual void Refresh(int a);                                          // +0x18
};

class ProgressBase {
public:
    PV4 PV2 PV
    virtual void SetID(uint32_t id);                                      // +0x1c
    uint32_t pad04[3];
    uint32_t mID;                                                         // +0x10
    uint32_t pad14[4];
};

class ProgressObj : public ProgressBase, public IRefreshTarget {
public:
    uint32_t GetID();                                                     // 0x007f54d0
    void Update();                                                        // 0x00ece300
    inline void Sync(uint32_t id)
    {
        if (GetID() != id)
            SetID(id);
    }
};

// ---------------------------------------------------------------------------------------------
// EASTL wstring (16 bytes incl. allocator), only what is used here
// ---------------------------------------------------------------------------------------------
extern wchar_t gEmptyString16[];                                          // 0x01667bac
void __cdecl FreeArray(void* p);                                          // 0x00f47380 (operator delete[])

struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    string16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
    }
    void DoFree(wchar_t* p, uint32_t)
    {
        if (p)
            FreeArray(p);
    }
    const wchar_t* c_str() const { return mpBegin; }
};

namespace SP {
class cString {
public:
    cString(uint32_t tableID, uint32_t instanceID, int flags);            // 0x006b5770
    ~cString();                                                           // 0x006b5240
    const wchar_t* GetText();                                             // 0x006b55c0
    uint32_t mData[5];                                                    // retail size 0x14 (frame layout; dev PDB says 0x1c)
};
}

// ---------------------------------------------------------------------------------------------
// tutorial data
// ---------------------------------------------------------------------------------------------
struct TutorialStep {                 // 0x4e0-byte record
    bool     mbDone;                  // +0x000
    bool     mbFlag1;                 // +0x001
    bool     mbFlag2;                 // +0x002
    uint8_t  pad003[0x484 - 0x3];
    float    mValue484;               // +0x484
    uint32_t pad488;
    float    mValue48c;               // +0x48c
    float    mValue490;               // +0x490
    float    mValue494;               // +0x494
    float    mValue498;               // +0x498
    float    mValue49c;               // +0x49c
    float    mValue4a0;               // +0x4a0
    int      mIcon;                   // +0x4a4
    uint32_t mType4a8;                // +0x4a8
    uint32_t mType4ac;                // +0x4ac
    uint32_t mType4b0;                // +0x4b0
    uint32_t mType4b4;                // +0x4b4
    uint32_t mType4b8;                // +0x4b8
    int      mValue4bc;               // +0x4bc
    int      mValue4c0;               // +0x4c0
    int      mValue4c4;               // +0x4c4
    bool     mbLocked;                // +0x4c8
    uint8_t  pad4c9[3];
    struct Elem { uint32_t d[8]; };
    Elem*    mpGoalsBegin;            // +0x4cc
    Elem*    mpGoalsEnd;              // +0x4d0
    Elem*    mpGoalsCapacity;         // +0x4d4
    uint8_t  pad4d8[0x4e0 - 0x4d8];
    uint32_t GoalCount() const { return (uint32_t)(mpGoalsEnd - mpGoalsBegin); }
};

class Tutorial {
public:
    ResourceKey mKey;                 // +0x00
    uint32_t pad0c[5];
    uint8_t  mPage;                   // +0x20
    uint8_t  pad21[3];
    int      mMode24;                 // +0x24
    uint32_t pad28[8];
    int      mMode48;                 // +0x48
    uint32_t pad4c[9];
    TutorialStep* mpSteps;            // +0x70

    void GetName(string16& out);                                          // 0x00f28b80
    ResourceKey GetImageA();                                              // 0x00f25160
    ResourceKey GetImageB();                                              // 0x00f251f0
    ResourceKey GetImageC(bool* pDimmed);                                 // 0x00f25240
    int  GetStateA();                                                     // 0x00f252c0
    int  GetStateB();                                                     // 0x00f252f0
    bool HasValue330();                                                   // 0x00f25330
    bool HasValue420();                                                   // 0x00f25420
    bool HasValue430();                                                   // 0x00f25430
    bool HasValue470();                                                   // 0x00f25470
    bool HasValue560();                                                   // 0x00f25560
    bool IsFlag600();                                                     // 0x00f25600
    bool HasValue670();                                                   // 0x00f25670
};

class TutorialManager {
public:
    int       GetCount();                                                 // 0x00f3be30
    uint32_t  GetGoalCount(uint32_t id);                                  // 0x00f3c7f0
    Tutorial* Find(uint32_t id);                                          // 0x00f3e8a0
};

struct GameGlobals {
    uint32_t pad[0x74 / 4];
    TutorialManager* mpTutorials;     // +0x74
};
extern GameGlobals* g_16c7aa4;
inline TutorialManager* GetTutorials() { return g_16c7aa4->mpTutorials; }

class cSPUILayout {
public:
    bool IsVisible();                                                     // 0x00810070
};

struct StateSync {
    void Set(int v);                                                      // 0x00ed9990
};

struct CountLimits {
    static const uint32_t kMaxCount = 999;                                // 0x0148a94c
};
const uint32_t CountLimits::kMaxCount;

template <class T>
inline const T& min_ref(const T& a, const T& b)
{
    return (b < a) ? b : a;
}

// id tables (0x0148a708 ...)
extern const uint32_t kCategoryWindowIDs[6];                              // 0x0148a708
extern const uint32_t kTable720[5];                                       // 0x0148a720
extern const uint32_t kTable738[6];                                       // 0x0148a738
extern const uint32_t kTable738Count;                                     // 0x0148a750
extern const uint32_t kTable754[3];                                       // 0x0148a754
extern const uint32_t kTable764[3];                                       // 0x0148a764
extern const uint32_t kTable774[5];                                       // 0x0148a774

template <int N>
inline int IndexOf(uint32_t value, const uint32_t (&table)[N])
{
    int index = -1;
    for (uint32_t i = 0; i < (uint32_t)N; i++) {
        if (value == table[i]) {
            index = (int)i;
            break;
        }
    }
    return index;
}

// external helpers (all __cdecl)
int   __cdecl ScenarioTutorials_GetActive();                                         // 0x00efc520
void  __cdecl Tutorial_Prepare(Tutorial* t);                                         // 0x00f0be80
bool  __cdecl Tutorial_IsComplete(Tutorial* t);                                      // 0x00ecb6b0
void  __cdecl SetPageLabel(IWindow* w, int page);                                    // 0x00ed1350
void  __cdecl SetButtonEnabled(IWindow* w, bool enabled);                            // 0x00e12fa0
void  __cdecl SetWindowText(IWindow* w, const wchar_t* text);                        // 0x00e12fc0
int   __cdecl IndexOfCounted(const uint32_t& v, const uint32_t* table, const uint32_t& count); // 0x00edcec0
void  __cdecl SetNumberString(int64_t value, wchar_t* buf, int size);                // 0x00881ae0
void  __cdecl SetNumberStringF(double value, wchar_t* buf, int size, int decimals);  // 0x00881f00
void  __cdecl ShowValue(uint32_t id, float value);                                   // 0x00ee1510
void  __cdecl SetSlider(IWindow* w, float value, float minValue, float maxValue);    // 0x00eddf90
float __cdecl GetStepTarget(ResourceKey key, float value);                           // 0x00eeebd0
void  __cdecl SetValueField(IWindow* w, float value, bool b2, bool b1, uint32_t fmt, const wchar_t* text); // 0x00edf830
void  __cdecl SetModeIcon(IWindow* w, int mode);                                     // 0x00ee1080
void  __cdecl SetWindowImage(IWindow* w, const ResourceKey& key, int frame);         // 0x00807bb0
void* __cdecl GetButtonDrawable(IWindow* w, int a);                                  // 0x00806880
void  __cdecl SetImageIcon(IWindow* w, void* drawable, int a);                       // 0x00806aa0
int   __cdecl GetIconIndex(IWindow* w, int index);                                   // 0x00eddee0
void  __cdecl SetImageIconFrom(IWindow* w, int* index, int a);                       // 0x00806b20
void  __cdecl SetChoiceRow(IWindow* w, bool last, int value);                        // 0x00ede040
void  __cdecl SyncTutorialState(int mode, uint32_t id);                              // 0x00ed8a30
IWindow* __cdecl FindAncestorByID(IWindow* w, uint32_t id);                          // 0x00edc9e0
void  __cdecl SelectCategory(uint32_t id, int mode, int index);                      // 0x00ee0960

class TutorialPanel {
public:
    uint32_t     pad00[4];
    cSPUILayout* mpLayout;            // +0x10
    ProgressObj* mpProgress;          // +0x14
    IWindow*     mpWindow;            // +0x18
    CategoryWin** mpCategoryWins;     // +0x1c (6 entries)
    uint32_t     mID;                 // +0x20
    uint32_t     pad24[9];
    StateSync    mState;              // +0x48

    void UpdateHeader();                                                  // 0x00edef10
    void UpdateLayout();                                                  // 0x00edf410
    void Refresh();
    bool HandleMessage(uint32_t messageID, void* data);

    inline IWindow* FindWindow(uint32_t id)
    {
        IWindow* window = mpWindow;
        return window ? window->FindWindowByID(id, true) : 0;
    }
};

// @ 0x00ee16f0
void TutorialPanel::Refresh()
{
    int mode = ScenarioTutorials_GetActive();
    int count = 1;
    TutorialManager* mgr = g_16c7aa4->mpTutorials;
    if (mgr)
        count = mgr->GetCount();
    Tutorial* tut = GetTutorials()->Find(mID);

    if (mpLayout->IsVisible() && tut) {
        UpdateHeader();
        Tutorial_Prepare(tut);
        bool complete = Tutorial_IsComplete(tut);
        TutorialStep* step = &tut->mpSteps[mode];
        UpdateLayout();

        string16 name;
        tut->GetName(name);
        const wchar_t* pName = name.c_str();

        if (IWindow* w = FindWindow(0x7957ba8)) {
            if (ITextField* text = (ITextField*)w->Cast(ITextField::TYPE)) {
                text->SetMaxLength(0x20);
                text->SetText(pName, 0);
            }
        }

        if (IWindow* w = FindWindow(0x76a93c54)) {
            w->SetFlag(1, count > 1);
            IWindow* pageLabel = FindWindow(0x76a93c53);
            IWindow* nextButton = FindWindow(0x76a93c51);
            IWindow* prevButton = FindWindow(0x76a93c50);
            IWindow* titleText = FindWindow(0x76a93c52);
            if (pageLabel && nextButton && prevButton && titleText) {
                SetPageLabel(pageLabel, tut->mPage);
                SetButtonEnabled(prevButton, mode > 0);
                SetButtonEnabled(nextButton, mode < count - 1);
                SP::cString title(0xefdb68ec, 0x96a94d76, 0);
                SetWindowText(titleText, title.GetText());
            }
        }

        if (IWindow* w = FindWindow(0x7a41548)) {
            bool flag = tut->IsFlag600();
            w->SetFlag(1, flag);
        }

        for (uint32_t i = 0; i < 6; i++) {
            CategoryWin* win;
            if (mpWindow->GetControlID() == kCategoryWindowIDs[i] && (win = mpCategoryWins[i]) != 0) {
                bool hasIcon = step->mIcon != -1;
                win->SetEnabled(hasIcon);
                mpCategoryWins[i]->SetValue(hasIcon ? step->mIcon : 0);
                mpWindow->FindWindowByID(0x7ec6a40, true)->SetFlag(1, hasIcon);
                object_cast<IButton>(mpWindow->FindWindowByID(0x7ec82c0, true))->SetButtonStateFlag(4, hasIcon);
            }
        }

        SetButtonFlag(FindWindow(0x742bde0), 4, step->mbDone);

        if (mpProgress) {
            uint32_t id = mID;
            if (id != mpProgress->GetID())
                mpProgress->SetID(id);
            mpProgress->Refresh(0);
            mpProgress->Update();
        }

        uint32_t goalCount = GetTutorials()->GetGoalCount(mID);
        wchar_t countText[32];
        SetNumberString(min_ref(goalCount, CountLimits::kMaxCount), countText, 0x20);
        if (IWindow* w = FindWindow(0x792e8a0))
            w->SetCaption(countText);

        if (tut->HasValue470()) {
            IWindow* group = FindWindow(0x742bd88);
            IWindow* lockedRow = group->FindWindowByID(0x742be59, false);
            IWindow* openRow = group->FindWindowByID(0x742be58, false);
            if (step->mbLocked || step->GoalCount() > 0) {
                uint32_t id = IndexOf(step->mType4ac, kTable738) + 0x742cbe0;
                if (step->mbLocked)
                    id = 0x742cbe5;
                if (IWindow* w = lockedRow->FindWindowByID(id, true)) {
                    if (IButton* button = (IButton*)w->Cast(IButton::TYPE))
                        button->SetButtonStateFlag(4, true);
                }
                lockedRow->SetFlag(1, true);
                openRow->SetFlag(1, false);
            } else {
                IWindow* row = group->FindWindowByID(0x742be58, false);
                int index = IndexOfCounted(step->mType4ac, kTable738, kTable738Count);
                if (IWindow* w = row->FindWindowByID(index + 0x742cbe0, true)) {
                    if (IButton* button = (IButton*)w->Cast(IButton::TYPE))
                        button->SetButtonStateFlag(4, true);
                }
                lockedRow->SetFlag(1, false);
                row->SetFlag(1, true);
            }
        }

        if (tut->HasValue470()) {
            ShowValue(mID, step->mValue484);
            SetSlider(FindWindow(0x792bf78), step->mValue484, 0.0f, 175.0f);
        }

        wchar_t text[32];
        if (tut->HasValue330()) {
            float target = GetStepTarget(tut->mKey, step->mValue48c);
            SetNumberString((int64_t)target, text, 0x20);
            SetValueField(FindWindow(0x7918320), step->mValue48c, step->mbFlag2, step->mbFlag1,
                          0xf69d44ec, text);
        }

        IWindow* modeA = FindWindow(0x76c61c8);
        IWindow* modeB = FindWindow(0x2791ba0);
        if (modeA && modeB) {
            if (tut->GetStateA()) {
                modeA->SetFlag(1, true);
                IWindow* shown;
                IWindow* hidden;
                if (tut->GetStateA() == 3) {
                    shown = modeA->FindWindowByID(0x2791ca0, true);
                    hidden = modeA->FindWindowByID(0x2791ca1, true);
                } else {
                    hidden = modeA->FindWindowByID(0x2791ca0, true);
                    shown = modeA->FindWindowByID(0x2791ca1, true);
                }
                shown->SetFlag(1, true);
                hidden->SetFlag(1, false);
                IWindow* modeIcon = shown->FindWindowByID(0x6849100, true);
                SetModeIcon(modeIcon, tut->mMode24);
                IWindow* icon = shown->FindWindowByID(0x3791003, true);
                if (tut->mMode24 == 2) {
                    IWindow* image = icon->FindWindowByID(0x3791001, true);
                    icon->SetFlag(1, true);
                    ResourceKey key = tut->GetImageA();
                    SetWindowImage(image, key, -1);
                } else if (tut->GetStateA() == 3) {
                    icon->SetFlag(1, false);
                }
            } else {
                modeA->SetFlag(1, false);
            }

            if (tut->GetStateB()) {
                modeB->SetFlag(1, true);
                IWindow* shown;
                IWindow* hidden;
                if (tut->GetStateB() == 3) {
                    shown = modeB->FindWindowByID(0x2791ba1, true);
                    hidden = modeB->FindWindowByID(0x2791ba2, true);
                } else {
                    hidden = modeB->FindWindowByID(0x2791ba1, true);
                    shown = modeB->FindWindowByID(0x2791ba2, true);
                }
                hidden->SetFlag(1, false);
                shown->SetFlag(1, true);
                IWindow* modeIcon = shown->FindWindowByID(0x6849100, true);
                SetModeIcon(modeIcon, tut->mMode48);
                IWindow* icon = shown->FindWindowByID(0x3791003, true);
                if (tut->mMode48 == 2) {
                    IWindow* image = icon->FindWindowByID(0x3791001, true);
                    icon->SetFlag(1, true);
                    ResourceKey key = tut->GetImageB();
                    SetWindowImage(image, key, -1);
                } else if (tut->GetStateB() == 3) {
                    icon->SetFlag(1, false);
                }
                bool dimmed;
                ResourceKey key = tut->GetImageC(&dimmed);
                IWindow* image = modeB->FindWindowByID(0x3791002, true);
                SetWindowImage(image, key, -1);
                if (dimmed)
                    image->SetShadeColor(0x77ffffff);
                else
                    image->SetShadeColor(0xffffffff);
            } else {
                modeB->SetFlag(1, false);
            }
        }

        if (tut->HasValue420() && FindWindow(0x9918320))
            SetSlider(FindWindow(0x9918320), step->mValue4a0, 1.0f, 50.0f);
        else if (FindWindow(0x9918320))
            FindWindow(0x9918320)->SetFlag(1, false);

        if (tut->HasValue560() && FindWindow(0x742bed0))
            FindWindow(0x742bed0)->SetFlag(1, true);
        else if (!tut->HasValue560() && FindWindow(0x742bed0))
            FindWindow(0x742bed0)->SetFlag(1, false);

        if (tut->HasValue430() && FindWindow(0x8918320))
            SetSlider(FindWindow(0x8918320), step->mValue49c, 0.0f, 2000.0f);
        else if (!tut->HasValue330() && FindWindow(0x8918320))
            FindWindow(0x8918320)->SetFlag(1, false);

        if (tut->HasValue430() && FindWindow(0x892bf78)) {
            ShowValue(mID, step->mValue498);
            SetSlider(FindWindow(0x892bf78), step->mValue498, 0.0f, 50.0f);
        } else if (!tut->HasValue470() && FindWindow(0x892bf78)) {
            FindWindow(0x892bf78)->SetFlag(1, false);
        }

        if (tut->HasValue470()) {
            SetNumberStringF((int)(step->mValue494 * 100.0f), text, 0x20, 0);
            SetValueField(FindWindow(0x7c8a7d0), step->mValue494, false, false, 0x7cc8a44, text);
        }

        if (tut->HasValue470()) {
            uint32_t fmt = 0;
            switch (tut->mKey.typeID) {
            case 0x24682294:
            case 0x476a98c7:
                fmt = 0x7cc8a4b;
                SetNumberStringF((int)(step->mValue490 * 100.0f), text, 0x20, 0);
                break;
            case 0x2b978c46:
                fmt = 0x7cc8a48;
                SetNumberString((int64_t)step->mValue490, text, 0x20);
                break;
            }
            SetValueField(FindWindow(0x7c8a7a8), step->mValue490, false, false, fmt, text);
        }

        if (tut->HasValue330()) {
            IWindow* w = FindWindow(0x742bd98);
            int index = IndexOf(step->mType4a8, kTable720);
            void* drawable;
            if (w) {
                IWindow* button = w->FindWindowByID(index + 0x742cbe0, true);
                drawable = GetButtonDrawable(button, 0);
            } else {
                drawable = 0;
            }
            SetImageIcon(w, drawable, 0);
            int iconIndex = GetIconIndex(w, index);
            SetImageIconFrom(w, &iconIndex, 1);
        }

        if (tut->HasValue670()) {
            IWindow* w = FindWindow(0x742bdb0);
            if (complete) {
                w->SetFlag(1, false);
            } else {
                w->SetFlag(1, true);
                int index = IndexOf(step->mType4b0, kTable754);
                IWindow* button = w->FindWindowByID(index + 0x742cbe0, true);
                void* drawable = GetButtonDrawable(button, 0);
                SetImageIcon(w, drawable, 0);
                SetChoiceRow(w, step->mType4b0 == 3, step->mValue4bc);
            }
        }

        if (tut->HasValue670()) {
            IWindow* w = FindWindow(0x742bdc0);
            if (complete) {
                w->SetFlag(1, false);
            } else {
                w->SetFlag(1, true);
                int index = IndexOf(step->mType4b4, kTable764);
                IWindow* button = w->FindWindowByID(index + 0x742cbe0, true);
                void* drawable = GetButtonDrawable(button, 0);
                SetImageIcon(w, drawable, 0);
                SetChoiceRow(w, step->mType4b4 == 3, step->mValue4c0);
            }
        }

        if (tut->HasValue470()) {
            IWindow* w = FindWindow(0x742bdd0);
            if (complete) {
                w->SetFlag(1, false);
            } else {
                w->SetFlag(1, true);
                int index = IndexOf(step->mType4b8, kTable774);
                IWindow* button = w->FindWindowByID(index + 0x742cbe0, true);
                void* drawable = GetButtonDrawable(button, 0);
                SetImageIcon(w, drawable, 0);
                SetChoiceRow(w, step->mType4b8 == 5, step->mValue4c4);
            }
        }
    }

    SyncTutorialState(mode, mID);
    mState.Set(1);
}

// @ 0x00ee27a0  (Ghidra folds this into 0x00ee16f0's 4,452-byte range: Refresh ends with ret at
// 0x00ee279f; this is the panel's message handler, the only caller of Refresh in that range)
bool TutorialPanel::HandleMessage(uint32_t messageID, void* data)
{
    switch (messageID) {
    case 0x7c41ae9: {
        CategoryMessage* msg = (CategoryMessage*)data;
        CategoryWinProc* source = msg->mpSource;
        for (uint32_t i = 0; i < 6; i++) {
            if (source == mpCategoryWins[i]) {
                SelectCategory(mID, ScenarioTutorials_GetActive(), msg->mIndex);
                Refresh();
                return false;
            }
        }
        break;
    }
    case 0x7c41aeb:
        if (IWindow* w = FindAncestorByID((IWindow*)data, 0x7a41548))
            w->GetParent()->BringToFront(w);
        break;
    case 0x7ef2d80:
        Refresh();
        break;
    }
    return false;
}
