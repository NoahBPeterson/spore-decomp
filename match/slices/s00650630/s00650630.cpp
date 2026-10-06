// Slice s00650630 -- SP::cSPUIAssetGrid::ReloadCallback (window wiring / teardown) and two
// EASTL insertion-sort helpers over SP::cSPAssetGridEntry (comparator passed by value).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);  // 0x00f473a0

struct IWindow;
struct cSPUILayout;

// Window-ish control returned by IWindow::GetControl (only slot 5 is used here).
struct IWindowControl {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5(int arg);
};

struct IWindow {
    virtual void AddRef();
    virtual void Release();
    virtual void vf2();
    virtual IWindowControl* GetControl(unsigned id);
    virtual IWindow* GetParent();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual float* GetArea();
    virtual float* GetRealArea();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
    virtual void vf19();
    virtual void vf20();
    virtual void vf21();
    virtual void vf22();
    virtual void vf23();
    virtual void vf24();
    virtual void SetPos(float x, float y);
    virtual void vf26();
    virtual void SetArea(float* rect);
    virtual void SetPosition(float x, float y);
    virtual void vf29();
    virtual void vf30();
    virtual void vf31();
    virtual void vf32();
    virtual void vf33();
    virtual void vf34();
    virtual void vf35();
    virtual void vf36();
    virtual void vf37();
    virtual void vf38();
    virtual void vf39();
    virtual void vf40();
    virtual void vf41();
    virtual void vf42();
    virtual void vf43();
    virtual void vf44();
    virtual void vf45();
    virtual void vf46();
    virtual void vf47();
    virtual void vf48();
    virtual void vf49();
    virtual void vf50();
    virtual void vf51();
    virtual void vf52();
    virtual void vf53();
    virtual void AddWindow(IWindow* w);
    virtual void RemoveWindow(IWindow* w);
    virtual void vf56();
    virtual void vf57();
    virtual void vf58();
    virtual void vf59(IWindow* w);
    virtual void vf60();
    virtual void vf61();
    virtual void vf62();
    virtual void vf63();
    virtual void vf64();
    virtual void AddWinProc(void* proc);
    virtual void RemoveWinProc(void* proc);
};

template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p) {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T** operator&() {   // out-parameter use: drops the held reference first
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    void AssignFromPtr(T** src);   // 0x00ac9480 (thiscall, 1 arg)
};

struct ResourceKey {
    unsigned int mInstanceID;   // +0
    unsigned int mTypeID;       // +4
    unsigned int mGroupID;      // +8
};

// cSPUILayout: vtable slot 0 = (placeholder), slot 1 = AddRef, slot 2 = Release.
struct cSPUILayout {
    char pad[0x18];
    cSPUILayout();                                          // 0x00810000
    virtual void vf0();
    virtual void AddRef();
    virtual void Release();
    IWindow* FindWindowByID(unsigned int id, bool bRecurse);          // 0x008105b0
    void Init(ResourceKey* key, bool b, unsigned int arg);            // 0x008120d0
};

struct IProperty {
    char pad0[0x10];
    unsigned short flags;       // +0x10 (0x30 = value is behind a pointer)
    unsigned short type;        // +0x12 (1 = bool)
    // Property data pointer lives at +0 (overlaid here for the inline accessor).
};
struct IPropertyList {
    virtual void AddRef();
    virtual void Release();
    virtual void vf2(); virtual void vf3(); virtual void vf4();
    virtual void vf5(); virtual void vf6(); virtual void vf7(); virtual void vf8();
    virtual bool GetProperty(unsigned int id, IProperty** out);       // slot 9
};
struct IPropertyManager {
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3();
    virtual void vf4(); virtual void vf5(); virtual void vf6(); virtual void vf7();
    virtual void vf8(); virtual void vf9(); virtual void vf10();
    virtual void GetPropertyList(unsigned int group, unsigned int instance, IPropertyList** out);  // slot 11
};

struct IScrollControl {   // object at ScrollFrameVertical+0x20 (slot 7)
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3();
    virtual void vf4(); virtual void vf5(); virtual void vf6();
    virtual void vf7(bool a, bool b);
};

struct ScrollFrameVertical {
    virtual void AddRef();
    virtual void Release();
    char pad08[0x0c];
    IWindow* mpScrollWindow;      // +0x10
    char pad14[4];
    IWindow* mpClientParent;      // +0x18
    char pad1c[4];
    IScrollControl* mpControl;    // +0x20
    char pad24[0x24];
    ScrollFrameVertical();                                                   // 0x0082a040
    bool CreateScrollFrameVertical(unsigned int id, int zero, void* handler); // 0x0082a140
    void Shutdown();                                                         // 0x0082a450
};

struct cSPUIFeedFilter {
    virtual void AddRef();
    virtual void Release();
    char pad[0x108];
    cSPUIFeedFilter();                                      // 0x00661020
    void Init(IWindow* win, unsigned int hash);              // 0x006625f0
    void SetVisible(bool b);                                 // 0x0065fa80
    void Shutdown();                                         // 0x0065fa20
};
struct cSPUISearchBox {
    virtual void AddRef();
    virtual void Release();
    char pad[0x60];
    cSPUISearchBox();                                        // 0x00671ec0
    void Init(IWindow* win);                                 // 0x00671da0
    void SetVisible(bool b);                                 // 0x00671c80
    void Shutdown();                                         // 0x00671c00
};

struct GridRow {            // row returned by LookupRow (0x0066a800)
    char pad[8];
    unsigned int mDefaultID;    // +0x08
    char pad2[0x1c];
    unsigned int mInstance;     // +0x28
    unsigned int mUseGroup;     // +0x2c
    unsigned int mGroup;        // +0x30
};
GridRow* LookupRow(int index);                       // 0x0066a800 (cdecl)
IPropertyManager* PropertyManager();                 // 0x0067de30
void SetWindowAreaToParent(IWindow* w);              // 0x00806bf0 (cdecl)
extern const unsigned int g_GridWinIDs[24];          // 0x01400420

struct cSPUIAssetGrid {
    char pad00[0x18];
    cSPUILayout* mLayout;                           // +0x18
    AutoRefCount<IWindow> mWinParent;               // +0x1c
    AutoRefCount<IWindow> mWinRoot;                 // +0x20
    AutoRefCount<IWindow> mWinGrid;                 // +0x24
    AutoRefCount<IWindow> mWinMessagePrimary;       // +0x28
    AutoRefCount<IWindow> mWinMessageSecondary;     // +0x2c
    AutoRefCount<IWindow> mWinFeedHeader;           // +0x30
    AutoRefCount<IWindow> mWinFeedFilter;           // +0x34
    AutoRefCount<IWindow> mWinSearch;               // +0x38
    AutoRefCount<IWindow> mWinSortButtonsParent;    // +0x3c
    AutoRefCount<IWindow> mWinBtnMakeNew;           // +0x40
    AutoRefCount<IWindow> mWin44;                   // +0x44
    AutoRefCount<IWindow> mWin48;                   // +0x48
    AutoRefCount<IWindow> mWin4c;                   // +0x4c
    AutoRefCount<IWindow> mWin50;                   // +0x50
    AutoRefCount<IWindow> mWin54;                   // +0x54 (feed filter host)
    AutoRefCount<IWindow> mWin58;                   // +0x58 (search box host)
    AutoRefCount<IWindow> mWin5c;                   // +0x5c
    AutoRefCount<IWindow> mWin60;                   // +0x60
    AutoRefCount<IWindow> mWin64;                   // +0x64
    AutoRefCount<IWindow> mWin68;                   // +0x68
    AutoRefCount<IWindow> mWin6c;                   // +0x6c
    AutoRefCount<IWindow> mWin70;                   // +0x70
    AutoRefCount<IWindow> mWin74;                   // +0x74
    AutoRefCount<IWindow> mWin78;                   // +0x78
    AutoRefCount<IWindow> mWin7c;                   // +0x7c
    AutoRefCount<IWindow> mWinArr[24];              // +0x80
    AutoRefCount<cSPUIFeedFilter> mFeedFilter;      // +0xe0
    AutoRefCount<cSPUISearchBox> mSearchBox;        // +0xe4
    char padE8[0x12c - 0xe8];
    float mCellWidth;                               // +0x12c
    float mCellHeight;                              // +0x130
    float mScrollWidth;                             // +0x134
    char pad138[0x18c - 0x138];
    AutoRefCount<ScrollFrameVertical> mScrollFrame; // +0x18c
};

// Reads the bool a property holds (flags 0x30 mean the data sits behind a pointer).
static inline bool PropBool(IProperty* p) {
    char* data = (char*)p;
    if (p->flags & 0x30)
        data = *(char**)p;
    return *data != 0;
}

// @ 0x00650630  SP::cSPUIAssetGrid::ReloadCallback
void ReloadCallback(cSPUIAssetGrid* self, void* unused, bool bLoad) {
    if (!bLoad) {
        if (self->mWin48.mpObject && self->mWinRoot.mpObject && self->mWinParent.mpObject) {
            self->mWinRoot.mpObject->RemoveWindow(self->mWin48.mpObject);
            self->mWinParent.mpObject->AddWindow(self->mWin48.mpObject);
        }
        if (self->mWin4c.mpObject && self->mWinGrid.mpObject && self->mWinParent.mpObject) {
            self->mWinGrid.mpObject->RemoveWindow(self->mWin4c.mpObject);
            self->mWinParent.mpObject->AddWindow(self->mWin4c.mpObject);
        }
        if (self->mFeedFilter.mpObject) {
            self->mFeedFilter.mpObject->Shutdown();
            self->mFeedFilter = 0;
        }
        if (self->mSearchBox.mpObject) {
            self->mSearchBox.mpObject->Shutdown();
            self->mSearchBox = 0;
        }
        if (self->mWinMessagePrimary.mpObject)
            self->mWinMessagePrimary.mpObject->RemoveWinProc(self);
        if (self->mWin48.mpObject)
            self->mWin48.mpObject->RemoveWinProc(self);
        if (self->mWinMessageSecondary.mpObject)
            self->mWinMessageSecondary.mpObject->RemoveWinProc(self);
        if (self->mWin5c.mpObject)
            self->mWin5c.mpObject->RemoveWinProc(self);
        if (self->mScrollFrame.mpObject) {
            self->mScrollFrame.mpObject->mpClientParent->GetParent()->RemoveWinProc(self);
            self->mScrollFrame.mpObject->Shutdown();
            self->mScrollFrame = 0;
        }
        return;
    }

    self->mWinMessagePrimary = self->mLayout->FindWindowByID(0xf3c6dc19, true);
    if (self->mWinMessagePrimary.mpObject)
        self->mWinMessagePrimary.mpObject->AddWinProc(self);
    self->mWin48 = self->mLayout->FindWindowByID(0x06737ba8, true);
    if (self->mWin48.mpObject)
        self->mWin48.mpObject->AddWinProc(self);
    self->mWin4c = self->mLayout->FindWindowByID(0x07d13d20, true);
    self->mWinMessageSecondary = self->mLayout->FindWindowByID(0xf3c6d819, true);
    if (self->mWinMessageSecondary.mpObject)
        self->mWinMessageSecondary.mpObject->AddWinProc(self);
    self->mWin50 = self->mLayout->FindWindowByID(0x14248528, true);
    self->mWin54 = self->mLayout->FindWindowByID(0x34346c9e, true);
    self->mWin58 = self->mLayout->FindWindowByID(0x14936ecb, true);
    self->mWin68 = self->mLayout->FindWindowByID(0x05949e98, true);
    self->mWin6c = self->mLayout->FindWindowByID(0x07e31d60, true);
    self->mWin70 = self->mLayout->FindWindowByID(0x2218130a, true);

    for (int i = 0; i < 24; ++i) {
        self->mWinArr[i] = self->mLayout->FindWindowByID(g_GridWinIDs[i], true);
        if (!self->mWinArr[i].mpObject) {
            GridRow* row = LookupRow(i);
            if (row) {
                unsigned int instance = row->mInstance;
                unsigned int useGroup = row->mUseGroup;
                unsigned int group = row->mGroup;
                if (instance) {
                    cSPUILayout* dlg = new ("Sporepedia", 0, 0, 0, 0) cSPUILayout();
                    if (dlg)
                        dlg->AddRef();
                    ResourceKey key;
                    key.mInstanceID = instance;
                    key.mGroupID = group;
                    key.mTypeID = 0x0510a95b;
                    dlg->Init(&key, true, 0x05b598fa);
                    unsigned int id = row->mDefaultID;
                    if (useGroup)
                        id = group;
                    IWindow* win = dlg->FindWindowByID(id, true);
                    if (win) {
                        win->AddRef();
                        if (self->mWin70.mpObject) {
                            win->GetParent()->RemoveWindow(win);
                            self->mWin70.mpObject->AddWindow(win);
                            self->mWinArr[i].AssignFromPtr(&win);
                        }
                        win->Release();
                    }
                    if (dlg)
                        dlg->Release();
                }
            }
        }
    }

    self->mWin74 = self->mLayout->FindWindowByID(0x07ce5010, true);
    self->mWin78 = self->mLayout->FindWindowByID(0x07ce2701, true);
    self->mWin7c = self->mLayout->FindWindowByID(0x07ce2700, true);

    {
        float* a = self->mWinArr[0].mpObject->GetArea();
        self->mCellWidth = a[2] - a[0];
    }
    {
        float* a = self->mWinArr[0].mpObject->GetArea();
        self->mCellHeight = a[3] - a[1];
    }
    {
        float* a = self->mWin70.mpObject->GetArea();
        self->mScrollWidth = a[2] - a[0];
    }

    if (self->mWin6c.mpObject && self->mWin70.mpObject) {
        IWindow* w = self->mWin6c.mpObject;
        if (w) {
            IWindowControl* ctl = w->GetControl(0x0f15f4bd);
            if (ctl) {
                float* r1 = self->mWin6c.mpObject->GetRealArea();
                float left1 = r1[0];
                float right1 = r1[2];
                ctl->vf5(0);
                float* r2 = self->mWin6c.mpObject->GetRealArea();
                float left2 = r2[0];
                float right2 = r2[2];
                float* r3 = self->mWin70.mpObject->GetRealArea();
                float dx = (right2 - left2) - (right1 - left1);
                self->mWin70.mpObject->SetPosition(dx + r3[0], r3[1]);
            }
        }
    }

    self->mWin5c = self->mLayout->FindWindowByID(0x14580f81, true);
    if (self->mWin5c.mpObject)
        self->mWin5c.mpObject->AddWinProc(self);
    self->mWin60 = self->mLayout->FindWindowByID(0x065666c8, true);
    self->mWin64 = self->mLayout->FindWindowByID(0x065666c0, true);

    bool bUseFeedFilter = false;
    AutoRefCount<IPropertyList> props;
    IPropertyManager* pm = PropertyManager();
    pm->GetPropertyList(0xb55619c2, 0x851d4139, &props);
    if (props.mpObject) {
        IProperty* prop;
        if (props.mpObject->GetProperty(0x6dcfc1b5, &prop)) {
            if (prop->type == 1)
                bUseFeedFilter = PropBool(prop);
        }
    }

    if (self->mWin54.mpObject && bUseFeedFilter) {
        cSPUIFeedFilter* ff = new ("UI", 0, 0, 0, 0) cSPUIFeedFilter();
        self->mFeedFilter = ff;
        self->mFeedFilter.mpObject->Init(self->mWin54.mpObject, 0xbda06a7c);
        self->mFeedFilter.mpObject->SetVisible(true);
    }
    if (self->mWin58.mpObject) {
        cSPUISearchBox* sb = new ("UI", 0, 0, 0, 0) cSPUISearchBox();
        self->mSearchBox = sb;
        self->mSearchBox.mpObject->Init(self->mWin58.mpObject);
        self->mSearchBox.mpObject->SetVisible(true);
    }

    self->mWinFeedHeader = self->mLayout->FindWindowByID(0x0654fce8, true);
    self->mWinFeedFilter = self->mLayout->FindWindowByID(0x0654fdd0, true);
    self->mWinSearch = self->mLayout->FindWindowByID(0x065402b0, true);
    self->mWinSortButtonsParent = self->mLayout->FindWindowByID(0x13d704e1, true);
    self->mWinBtnMakeNew = self->mLayout->FindWindowByID(0x53da7eec, true);
    self->mWin44 = self->mLayout->FindWindowByID(0x07aa9f70, true);

    if (self->mWinMessagePrimary.mpObject)
        SetWindowAreaToParent(self->mWinMessagePrimary.mpObject);

    ScrollFrameVertical* sf = new ("UI/ScrollFrameVertical", 0, 0, 0, 0) ScrollFrameVertical();
    self->mScrollFrame = sf;
    if (self->mScrollFrame.mpObject->CreateScrollFrameVertical(0xaef7d6ba, 0, (char*)self + 8)) {
        IWindow* host = self->mLayout->FindWindowByID(0x5460f69c, true);
        IWindow* scrollWin = self->mScrollFrame.mpObject->mpScrollWindow;
        IWindow* client = self->mScrollFrame.mpObject->mpClientParent;
        host->AddWindow(scrollWin);
        host->vf59(scrollWin);
        scrollWin->SetArea(self->mWinMessageSecondary.mpObject->GetRealArea());
        self->mWinMessageSecondary.mpObject->GetParent()->RemoveWindow(self->mWinMessageSecondary.mpObject);
        client->AddWindow(self->mWinMessageSecondary.mpObject);
        self->mWinMessageSecondary.mpObject->SetPos(0.0f, 0.0f);
        IWindow* clientParent = client->GetParent();
        if (clientParent)
            clientParent->AddWinProc(self);
        self->mScrollFrame.mpObject->mpControl->vf7(true, true);
    } else {
        self->mScrollFrame = 0;
    }
}

// ---------------------------------------------------------------------------
// SP::cSPAssetGridEntry (0x20 bytes) and EASTL insertion sorts with a by-value comparator.
// ---------------------------------------------------------------------------
struct IRefCountBase {
    virtual void AddRef();
    virtual void Release();
};
struct EntryPrimary { virtual void v(); char pad0[0xc]; };
struct EntryView : EntryPrimary, IRefCountBase {};   // refcount base at +0x10
struct EntryData : IRefCountBase {};

struct GridEntry {
    void* m00;
    void* m04;
    void* m08;
    AutoRefCount<EntryView> m0c;     // +0x0c
    AutoRefCount<EntryData> m10;     // +0x10
    float m14;
    float m18;
    bool m1c;
    bool m1d;
    GridEntry() {}
    GridEntry& operator=(const GridEntry&);   // 0x0064f450
};

struct CompareA {   // 0x0064ff90: two entries BY VALUE
    bool operator()(GridEntry a, GridEntry b) const;
};

namespace eastl {

// @ 0x006511b0  eastl::insertion_sort<GridEntry*, CompareA>
template <typename It, typename Compare>
void insertion_sort(It first, It last, Compare compare) {
    if (first != last) {
        It iCurrent, iNext, iSorted = first;
        for (++iSorted; iSorted != last; ++iSorted) {
            const GridEntry temp(*iSorted);
            iNext = iCurrent = iSorted;
            for (--iCurrent; (iNext != first) && compare(temp, *iCurrent); --iNext, --iCurrent)
                *iNext = *iCurrent;
            *iNext = temp;
        }
    }
}

// @ 0x00651390  unguarded insertion sort (no lower-bound check)
template <typename It, typename Compare>
void insertion_sort_unguarded(It first, It last, Compare compare) {
    for (It i = first; i != last; ++i) {
        const GridEntry temp(*i);
        It iNext = i;
        It iCurrent = i - 1;
        while (compare(temp, *iCurrent)) {
            *iNext = *iCurrent;
            --iNext;
            --iCurrent;
        }
        *iNext = temp;
    }
}

template void insertion_sort<GridEntry*, CompareA>(GridEntry*, GridEntry*, CompareA);
template void insertion_sort_unguarded<GridEntry*, CompareA>(GridEntry*, GridEntry*, CompareA);

}  // namespace eastl
