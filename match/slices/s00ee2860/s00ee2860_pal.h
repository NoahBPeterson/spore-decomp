#pragma once
// Slice s00ee2860, second translation unit: 0x00ee2960, the scenario-edit tutorial/behaviour
// palette's per-item refresh (shows or hides the item widgets of one palette entry, sets their
// images, tooltips and the count caption).
//
// Module flags: UI module, /O2 /MD /Gy /TP /GS- (no /EHsc frame for the cString locals, no
// cookie for the wchar_t buffer), no SSE needed (no float code).
#include "types.h"
extern "C" __declspec(dllimport) wchar_t* __cdecl _ltow(long, wchar_t*, int) throw();   // msvcr90 import

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
    ResourceKey() throw() {}
    ResourceKey(const ResourceKey&) throw();
};

// UTFWin IWindow, only the slots used here
class IWindow {
public:
    PV2 PV
    virtual void* Cast(uint32_t typeID) throw();                                  // +0x0c
    PV16 PV2 PV
    virtual void SetShadeColor(uint32_t color) throw();                           // +0x5c
    PV4 PV2 PV
    virtual void SetFlag(int flag, bool value) throw();                           // +0x7c
    virtual void SetCaption(const wchar_t* caption) throw();                      // +0x80
    PV16 PV8 PV2 PV
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive) throw();         // +0xf0
};

// interface 0x8ed27e7a (button)
class IButton {
public:
    enum { TYPE = 0x8ed27e7a };
    PV4
    virtual IWindow* GetWindow() throw();                                         // +0x10
    PV4 PV
    virtual void SetButtonStateFlag(int flag, uint8_t value) throw();                // +0x28
};

template <class T>
inline T* object_cast(IWindow* w) throw()
{
    return w ? (T*)w->Cast(T::TYPE) : 0;
}

inline void SetButtonFlag(IWindow* w, int flag, uint8_t value) throw()
{
    if (IButton* button = object_cast<IButton>(w))
        button->SetButtonStateFlag(flag, value);
}

namespace SP {
class cString {
public:
    cString() throw();                                                            // 0x006b5060
    cString(uint32_t tableID, uint32_t instanceID, int flags) throw();            // 0x006b5770
    ~cString() throw();                                                           // 0x006b5240
    const wchar_t* GetText() throw();                                             // 0x006b55c0
    uint32_t mData[5];                                                    // retail size 0x14
};
}

// one palette entry
struct PaletteItem {
    int     mType;          // +0x00 (index into kTypeImageInstance)
    int     mID;            // +0x04 (tutorial id, -1 none)
    int     mImageID;       // +0x08
    int     mCount;         // +0x0c
    uint8_t mFlag10;        // +0x10
    uint8_t pad11[3];
    uint8_t mFlags14;       // +0x14 (bit 0 = highlighted)
};

class Tutorial {
public:
    bool IsLocked() throw();                                                      // 0x00f25ed0
};

class TutorialManager {
public:
    Tutorial* Find(uint32_t id) throw();                                          // 0x00f3e8a0
    int GetItemCount(int mode, PaletteItem* item, int id, int a, int b, int c, int d, bool e) throw(); // 0x00f416b0
};

struct GameGlobals {
    uint32_t pad[0x74 / 4];
    TutorialManager* mpTutorials;     // +0x74
};
extern GameGlobals* g_16c7aa4;                                            // 0x016c7aa4
inline TutorialManager* GetTutorials() throw() { return g_16c7aa4->mpTutorials; }

extern const uint32_t kTypeImageInstance[];                               // 0x0148a544

bool  __cdecl IsTypeA(int type) throw();                                                       // 0x00f3b320
bool  __cdecl IsTypeB(int type) throw();                                                       // 0x00f3b340
int   __cdecl ScenarioTutorials_GetActive() throw();                                           // 0x00efc520
void  __cdecl BuildItemText(PaletteItem* item, SP::cString* out) throw();                      // 0x00edd130
void  __cdecl SetTooltip(PaletteItem* item, SP::cString* a, SP::cString* b) throw();           // 0x00ee2860
ResourceKey __cdecl GetItemImageKey(int id) throw();                                           // 0x00edd240
void  __cdecl SetTooltipText(IWindow* w, const wchar_t* text, int a, bool b) throw();          // 0x00806de0
void  __cdecl SetWindowImageResource(IWindow* w, const ResourceKey& key, int a) throw();       // 0x00807cb0
void  __cdecl SetWindowImage(IWindow* w, const ResourceKey& key, int frame) throw();           // 0x00807bb0

template <class T>
inline const T& min_ref(const T& a, const T& b) throw()
{
    return (b < a) ? b : a;
}

// @ 0x00ee2960
void __cdecl f00ee2960(IWindow* win, PaletteItem* item, bool a3, bool a4)
{
    if (!win)
        return;

    bool hasItem = item != 0;
    bool v1 = hasItem && IsTypeA(item->mType);
    bool v2 = hasItem && IsTypeB(item->mType);
    bool v3 = hasItem && item->mType == 2;

    if (IWindow* w = win->FindWindowByID(0x75e0a48, true))
        w->SetFlag(1, a3);
    if (IWindow* w = win->FindWindowByID(0x75e0ba0, true))
        w->SetFlag(1, hasItem);

    if (a3) {
        if (IWindow* w = win->FindWindowByID(0x715cdc0, true))
            w->SetFlag(1, !a4);
        if (IWindow* w = win->FindWindowByID(0x7638b20, true))
            w->SetFlag(1, !a4);
        if (IWindow* w = win->FindWindowByID(0x7638be8, true))
            w->SetFlag(1, a4);
    }

    if (hasItem) {
        bool isX = item->mFlags14 & 1;
        SP::cString s1;
        BuildItemText(item, &s1);
        ResourceKey key;
        key.instanceID = kTypeImageInstance[item->mType];
        uint8_t flag10 = item->mFlag10;
        key.typeID = 0x2f7d0004;
        key.groupID = 0x8a7be0c0;

        SetButtonFlag(win->FindWindowByID(0x7461828, true), 4, flag10);
        if (IWindow* w = win->FindWindowByID(0x7df41c0, true))
            w->SetFlag(1, v2);
        if (IWindow* w = win->FindWindowByID(0x7e20aa8, true))
            w->SetFlag(1, false);

        if (v2) {
            IWindow* wa = win->FindWindowByID(0x7df4c98, true);
            IWindow* wb = win->FindWindowByID(0x7e20aa8, true);
            IWindow* wc = win->FindWindowByID(0x7e1f2f8, true);
            IButton* bc = object_cast<IButton>(wc);
            Tutorial* tut = GetTutorials()->Find(item->mID);
            bool locked = tut && tut->IsLocked();
            SP::cString s2(0xea78cfb9, 0x7df5fb4, 0);
            SP::cString s3(0xf3108302, 0x7ec7659, 0);
            int value;
            if (item->mCount == 0) {
                wa->SetFlag(2, false);
                wc->SetFlag(2, true);
                bc->SetButtonStateFlag(4, true);
                SetTooltipText(bc->GetWindow(), s2.GetText(), -1, true);
                wb->SetFlag(1, true);
                const int kMax = 99;
                int n = GetTutorials()->GetItemCount(ScenarioTutorials_GetActive(), item, item->mID, 0, 0, 0, 0, true);
                value = min_ref(n, kMax);
            } else {
                wa->SetFlag(2, true);
                wc->SetFlag(2, !locked);
                bc->SetButtonStateFlag(4, false);
                SetTooltipText(bc->GetWindow(), (locked ? s3 : s2).GetText(), -1, true);
                wb->SetFlag(1, false);
                value = item->mCount;
            }
            uint32_t bufStore[4];   // wchar_t[8] without a /GS cookie
            wchar_t* buf = (wchar_t*)bufStore;
            wa->SetCaption(_ltow(value, buf, 10));
        }

        if (IWindow* w = win->FindWindowByID(0x74656a0, true))
            w->SetFlag(1, v3);
        if (v3) {
            bool hasID = item->mID != -1;
            if (IWindow* w = win->FindWindowByID(0x74656a0, true))
                w->SetFlag(2, hasID);
        }

        IWindow* img = win->FindWindowByID(0x7394420, true);
        SetWindowImageResource(img, key, 0);
        SP::cString s4;
        if (isX)
            SetTooltip(item, &s1, &s4);
        SetTooltipText(img, (isX ? s4 : s1).GetText(), -1, true);
        uint32_t color = isX ? 0xffff0000 : 0xffffffff;
        img->SetShadeColor(color);
        SetWindowImage(win->FindWindowByID(0x715cdd0, true), GetItemImageKey(item->mID), -1);

        if (IWindow* w = win->FindWindowByID(0x75e06f8, true))
            w->SetFlag(1, v1);
        if (v1) {
            IWindow* img2 = win->FindWindowByID(0x75e1200, true);
            SetWindowImageResource(img2, key, 0);
            SetTooltipText(img2, (isX ? s4 : s1).GetText(), -1, true);
            img2->SetShadeColor(color);
            SetWindowImage(win->FindWindowByID(0x75e1208, true), GetItemImageKey(item->mImageID), -1);
        }

        SetButtonFlag(win->FindWindowByID(0x7479d1a, true), 4, v1);
    } else {
        if (IWindow* w = win->FindWindowByID(0x7e20aa8, true))
            w->SetFlag(1, false);
        if (IWindow* w = win->FindWindowByID(0x7df41c0, true))
            w->SetFlag(1, false);
    }
}
