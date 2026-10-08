// Slice s00e16a70: FUN_00e16a70 (~1.6 KB, __thiscall, one bool argument), refresh of a
// three-row UI panel from the game's mission/objective log.
//
// `this` holds the layout root window (+0x24), a title window (+0x30) and a list container
// window (+0x34). Unless the bool argument is set it writes the panel title, then for each of
// the three rows looks up the row window (controls 0x795a200+i / 0x792dcc5+i / 0x792dd06+i /
// 0x7a2f850+i), shows or hides it depending on the log entry, restyles the row, resizes it,
// stacks it below the previous row (running height `total`) and finally resizes the container
// to the accumulated height. The tail updates the caption and visibility of control 0x754f66e
// (a timer-style entry) from the log object.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (UI module: movss, x87 compares, no EH frame).
#include "types.h"

typedef wchar_t char16;
struct Rect {
    float x1, y1, x2, y2;
    __forceinline Rect(float l, float t, float r, float b) : x1(l), y1(t), x2(r), y2(b) {}
};

// ---------------------------------------------------------------------------------------
// UTFWin window interface (slots from the ModAPI IWindow header, checked against the asm)
class IWindow {
public:
    virtual int   AddRef();                                         // 0x00
    virtual int   Release();                                        // 0x04
    virtual void  v08();                                            // 0x08
    virtual void* Cast(uint32_t typeID);                            // 0x0c
    virtual IWindow* GetParent();                                   // 0x10
    virtual void  v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void  v24(); virtual void v28(); virtual void v2c(); virtual void v30();
    virtual void  v34();
    virtual const Rect& GetRealArea();                              // 0x38
    virtual void  v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void  v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void  v5c(); virtual void v60(); virtual void v64(); virtual void v68();
    virtual void  SetLayoutArea(const Rect& area);                  // 0x6c
    virtual void  v70();
    virtual void  SetLayoutSize(float w, float h);                  // 0x74
    virtual void  v78();
    virtual void  SetFlag(uint32_t flag, bool value);               // 0x7c
    virtual void  SetCaption(const char16* caption);              // 0x80
    virtual void  v84(); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void  v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual uint32_t GetFillColor();                                // 0xa4
    virtual void  va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
    virtual void  vb8(); virtual void vbc(); virtual void vc0(); virtual void vc4();
    virtual void  vc8(); virtual void vcc(); virtual void vd0(); virtual void vd4();
    virtual void  vd8(); virtual void vdc(); virtual void ve0(); virtual void ve4();
    virtual void  ve8(); virtual void vec();
    virtual IWindow* FindWindowByID(uint32_t controlID, bool recursive);   // 0xf0
};

// The interface returned by Cast(0x8ed27e7a) on a row window.
class IRowControl {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual IWindow* GetWindow();                                   // 0x10
    virtual void SetEnabled(int on);                                // 0x14
    virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24();
    virtual void s28(); virtual void s2c(); virtual void s30(); virtual void s34();
    virtual void s38(); virtual void s3c(); virtual void s40(); virtual void s44();
    virtual void s48();
    virtual void SetValue(int index, uint32_t value);               // 0x4c
};

// ---------------------------------------------------------------------------------------
// eastl::basic_string<char16>
extern char16 gEmptyString[];   // 0x01667bac
void operator delete[](void* p);  // 0x00f47380
struct string16 {
    char16* mpBegin;
    char16* mpEnd;
    char16* mpCapacity;
    uint32_t  mAllocator;
    string16() : mpBegin(&gEmptyString[0]), mpEnd(&gEmptyString[0]), mpCapacity(&gEmptyString[1]) {}
    ~string16()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            delete[] mpBegin;
    }
};

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
};

// ---------------------------------------------------------------------------------------
// The log object (game state +0x78); entries are 0x1ac bytes.
class cMissionLog {
public:
    void  GetTitle(string16* out);        // 0x00f1b9b0
    void  GetObjectiveTitle(string16* out);   // 0x00f1ba00
    int   GetEntryCount();                // 0x00f19bc0
    bool  IsEntryComplete(int i);         // 0x00f19be0
    void  GetEntryText(int i, string16* out);   // 0x00f1ba50
    bool  IsEntryActive(int i);           // 0x00f19cc0
    bool  IsEntryNew(int i);              // 0x00f19c80
    int   GetEntryProgress(int i);        // 0x00f19c20
    int   GetEntryIcon(int i);            // 0x00f19c00
    bool  HasTimer();                     // 0x00f19b80
    void  GetTimerText(string16* out);    // 0x00f1dc50
    float GetTimerSeconds();              // 0x00f19160
};

struct GameState {
    uint32_t pad00[0x78 / 4];
    cMissionLog* mpLog;        // +0x78
    uint32_t pad7c[(0xd0 - 0x7c) / 4];
    int mnPlayerCount;         // +0xd0
};
extern GameState* g_pGame;     // 0x016c7aa4

class LimitStopwatch {
public:
    void SetTimeLimit(uint32_t limit, int units);   // 0x0093a480
};
extern uint32_t g_AlertTimeLimit;   // 0x015a4cc8
extern float g_TimerWarnSeconds; // 0x015a4cd8

void FillIconResource(ResourceKey* out, int icon);                      // 0x00edcac0
void SetWindowImageResource(IWindow* w, ResourceKey* key, int flags);   // 0x00807cb0

template<class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

class cMissionPanel {
public:
    uint32_t  pad00[0x24 / 4];
    IWindow*  mpRoot;              // +0x24
    uint32_t  pad28[2];
    IWindow*  mpTitleWin;          // +0x30
    IWindow*  mpListWin;           // +0x34
    uint32_t  pad38[(0x98 - 0x38) / 4];
    float     mfMinRowHeight;      // +0x98
    int       mnProgress[3];       // +0x9c
    uint8_t   mbAlerted[3];        // +0xa8
    uint8_t   pada[5];
    LimitStopwatch mAlertTimer;    // +0xb0

    void FUN_00e154d0(int arg);    // 0x00e154d0
    void FUN_00e16a70(bool bSkipList);
};

// @ 0x00E16A70
void cMissionPanel::FUN_00e16a70(bool bSkipList)
{
    string16 text;
    bool noPlayers = (g_pGame->mnPlayerCount == 0);
    cMissionLog* log = g_pGame->mpLog;

    if (!bSkipList) {
        IWindow* titleCtl = mpRoot->FindWindowByID(0x52350c8, true);
        if (titleCtl) {
            log->GetTitle(&text);
            titleCtl->SetCaption(text.mpBegin);
        }
        if (mpTitleWin) {
            log->GetObjectiveTitle(&text);
            mpTitleWin->SetCaption(text.mpBegin);
            char16* caption = text.mpBegin;
            IWindow* sub = mpRoot->FindWindowByID(0x7f5abd0, true);
            if (sub)
                sub->SetCaption(caption);
        }
        if (mpListWin) {
            float total = 0.0f;
            uint32_t colorA = mpRoot->FindWindowByID(0x792f6d0, true)->GetFillColor();
            uint32_t colorB = mpRoot->FindWindowByID(0x792f6d1, true)->GetFillColor();
            uint32_t colorC = mpRoot->FindWindowByID(0x7d78b80, true)->GetFillColor();
            int i = 0;
            int count = log->GetEntryCount();
            int* pProgress = mnProgress;

            for (; i < 3; i++, pProgress++) {
                uint32_t rowID = i + 0x792dcc5;
                IWindow* rowWin = mpRoot->FindWindowByID(rowID + 0x2c53b, true);
                if (rowWin)
                    rowWin->SetFlag(2, true);

                bool done;
                if (i < count && log->IsEntryComplete(i))
                    done = true;
                else
                    done = false;

                bool show;
                if (i < count && (done || noPlayers))
                    show = true;
                else
                    show = false;
                if (rowWin)
                    rowWin->SetFlag(1, show);
                if (!show)
                    continue;

                IWindow* container = mpRoot->FindWindowByID(rowID, true);
                IRowControl* ctl = container ? (IRowControl*)container->Cast(0x8ed27e7a) : 0;
                if (noPlayers && !done) {
                    ctl->SetValue(0, colorC);
                    ctl->SetValue(4, colorC);
                    ctl->SetValue(5, colorC);
                    ctl->SetValue(6, colorC);
                    ctl->SetValue(7, colorC);
                }
                string16 entryText;
                log->GetEntryText(i, &entryText);
                done = log->IsEntryActive(i);
                bool isNew = log->IsEntryNew(i);
                if (isNew) {
                    if (!done && !mbAlerted[i]) {
                        mbAlerted[i] = 1;
                        FUN_00e154d0(0);
                        mAlertTimer.SetTimeLimit(g_AlertTimeLimit, 1);
                    }
                } else {
                    mbAlerted[i] = 0;
                }
                int progress = log->GetEntryProgress(i);
                if (progress != *pProgress) {
                    *pProgress = progress;
                    if (rowWin)
                        rowWin->SetFlag(2, false);
                }

                bool notNew = !isNew;
                float adjust = 0.0f;
                const Rect* area;
                if (ctl) {
                    container->SetFlag(2, noPlayers && notNew);
                    ctl->SetValue(1, notNew ? colorA : colorB);
                    area = &container->GetRealArea();
                    float oldHeight = area->y2 - area->y1;
                    float width = area->x2 - area->x1;
                    container->SetCaption(entryText.mpBegin);
                    ctl->SetEnabled(1);
                    float height = area->y2 - area->y1;
                    const float* pHeight = &mfMinRowHeight;
                    if (height > mfMinRowHeight)
                        pHeight = &height;
                    float newHeight = *pHeight;
                    ctl->GetWindow()->SetLayoutSize(width, newHeight);
                    adjust = newHeight - oldHeight;
                }
                const Rect* rowArea = &rowWin->GetRealArea();
                Rect placed(rowArea->x1, total, rowArea->x2,
                            ((rowArea->y2 - rowArea->y1) + adjust) + total);
                rowWin->SetLayoutArea(placed);

                IWindow* iconWin = mpRoot->FindWindowByID(i + 0x792dd06, true);
                if (iconWin) {
                    iconWin->SetFlag(1, notNew);
                    iconWin->SetFlag(0x10, !noPlayers);
                    if (notNew) {
                        ResourceKey key;
                        FillIconResource(&key, log->GetEntryIcon(i));
                        SetWindowImageResource(iconWin, &key, 0);
                    }
                }
                mpRoot->FindWindowByID(i + 0x7a2f850, true)->SetFlag(1, !notNew);
                total = ((rowArea->y2 - rowArea->y1) + total);
            }
            IWindow* list = mpListWin;
            const Rect& listArea = list->GetRealArea();
            list->SetLayoutSize(listArea.x2 - listArea.x1, total);
        }
    }

    IWindow* timerWin = mpRoot->FindWindowByID(0x754f66e, true);
    if (timerWin) {
        bool hasTimer = log->HasTimer();
        timerWin->SetFlag(1, false);
        if (hasTimer) {
            log->GetTimerText(&text);
            timerWin->SetCaption(text.mpBegin);
            timerWin->SetFlag(2, log->GetTimerSeconds() < g_TimerWarnSeconds);
        }
    }
}
