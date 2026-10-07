// Slice s00ef50a0 -- 0x00ef50a0 (3289 bytes, __thiscall, no args): one-time window setup of
// the scenario-mode Sporepedia large asset view (name guessed: Load; same TU as
// Simulator::cSPScenarioModeSporepediaLargeAssetView, reached by tail jump from 0x00ef5d80).
//
// Looks up every control of its layout (cSPUILayout at +0x30) into AutoRefCount<IWindow>
// members, creates its helper objects (render-window controller +0x94, asset verbs +0x98,
// +0xa8 helper, two UI::TextZoomName at +0xac/+0xb0), fills name / author / description / tags
// from the IAssetData at +0x9c, lays out the author line and the buttons next to it, and
// shows the edit button only for downloaded assets that are not the player's own and not
// queued. Sets mIsLoaded (+0xc0); returns at once when already loaded.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the original has no EH frame).
#include "types.h"
#include <string.h>
#pragma intrinsic(wcslen)

#pragma warning(disable: 4100)

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                                     // 0x00f473a0
void operator delete[](void* p);                                                     // 0x00f47380

struct Rect {
    float x1, y1, x2, y2;
    Rect() {}
    Rect(const Rect& o) : x1(o.x1), y1(o.y1), x2(o.x2), y2(o.y2) {}
};
struct Point {
    float x, y;
    Point(float ax, float ay) : x(ax), y(ay) {}
    Point(const Point& o) : x(o.x), y(o.y) {}
};

struct IWinProc { virtual void wp00(); };

// EA::UTFWin::IWindow (vtable slots from the ModAPI headers)
struct IWindow {
    virtual int  AddRef();                                         // +0x00
    virtual int  Release();                                        // +0x04
    virtual void v08();
    virtual void* Cast(uint32_t type);                             // +0x0c
    virtual IWindow* GetParent();                                  // +0x10
    virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual const Rect& GetRealArea();                             // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void v5c(); virtual void v60();
    virtual void SetLocation(float x, float y);                    // +0x64
    virtual void v68();
    virtual void SetLayoutArea(const Rect& r);                     // +0x6c
    virtual void v70(); virtual void v74(); virtual void v78();
    virtual void SetFlag(int flag, bool value);                    // +0x7c
    virtual void SetCaption(const wchar_t* text);                  // +0x80
    virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual void vf0(); virtual void vf4(); virtual void vf8(); virtual void vfc();
    virtual void v100();
    virtual void AddWinProc(IWinProc* proc);                       // +0x104
};

// EA::UTFWin::IText (Cast(0x0f15f4bd))
struct IText {
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
    virtual IWindow* ToWindow();                                   // +0x10
    virtual void func14h(bool b);                                  // +0x14
};
static const uint32_t kITextType = 0x0f15f4bd;

struct IObject {
    virtual void o00(); virtual void o04(); virtual void o08();
    virtual void* Cast(uint32_t type);                             // +0x0c
};
struct cSPAssetDataOTDB {
    bool IsLocalAsset();                                           // 0x006418e0
};

struct string16 {                                                  // eastl::basic_string<wchar_t>
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    static wchar_t gEmptyString[1];                                // 0x01667bac
    string16() : mpBegin(gEmptyString), mpEnd(gEmptyString), mpCapacity(gEmptyString + 1) {}
    ~string16()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator delete[](mpBegin);
    }
    const wchar_t* c_str() const { return mpBegin; }
};

// Sporepedia::IAssetData
struct IAssetData {
    virtual void a00(); virtual void a04(); virtual void a08();
    virtual const wchar_t* GetName();                              // +0x0c
    virtual const wchar_t* GetAuthorName();                        // +0x10
    virtual const wchar_t* GetDescription();                       // +0x14
    virtual void a18(); virtual void a1c();
    virtual void GetTags(string16& dst);                           // +0x20
    virtual void a24(); virtual void a28(); virtual void a2c();
    virtual void a30(); virtual void a34(); virtual void a38(); virtual void a3c();
    virtual void a40(); virtual void a44(); virtual void a48(); virtual void a4c();
    virtual void a50(); virtual void a54(); virtual void a58(); virtual void a5c();
    virtual void a60(); virtual void a64(); virtual void a68(); virtual void a6c();
    virtual bool IsShared();                                       // +0x70
    uint32_t pad04[3];
};
// cSPAssetDataOTDB-like: IAssetData + Object (+0x10)
struct cAssetData : IAssetData, IObject {
};

struct cAssetMetadata {
    uint64_t GetAssetKey();                                        // 0x005508a0
};

struct cSPUILayout {
    IWindow* FindWindowByID(uint32_t id, bool recursive);          // 0x008105b0
};

namespace SPUIHelpers {
    void SetWindowAreaToParent(IWindow* w);                        // 0x00806bf0
    void CenterWindow(IWindow* w, Point center);                   // 0x00806ca0
    void AutoSizeWindowForText(IWindow* w, int a, int b);          // 0x00806e40
}

struct IAuthManager {
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1c();
    virtual void m20();
    virtual bool IsOffline();                                      // +0x24
    virtual void m28(); virtual void m2c(); virtual void m30(); virtual void m34();
    virtual void m38(); virtual void m3c();
    virtual uint64_t GetUserID();                                  // +0x40
};
namespace SP { namespace Pollen { IAuthManager* AuthManager(); } }   // 0x00607a60

struct QueueEntry {                                                // 0x70 bytes
    uint32_t pad00[4];
    uint64_t mAssetKey;                                            // +0x10
    uint32_t pad18[(0x68 - 0x18) / 4];
    int      mState;                                               // +0x68
    uint32_t pad6c;
};
struct QueueVector {                                               // eastl::vector<QueueEntry>
    QueueEntry* mpBegin;
    QueueEntry* mpEnd;
    QueueEntry* mpCapacity;
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    QueueEntry& operator[](unsigned i) { return mpBegin[i]; }
};
struct cAssetQueue {
    uint32_t pad000[0xc8 / 4];
    QueueVector mEntries;                                          // +0xc8
};
cAssetQueue* AssetQueue();                                         // 0x0067cb30

struct RefCounted {
    virtual int AddRef();                                          // +0x00
    virtual int Release();                                         // +0x04
};
struct cRenderViewController : RefCounted {                        // 0x80 bytes
    cRenderViewController();                                       // 0x00f46dd0
    void Attach(IWindow* w);                                       // 0x00f46eb0
    uint32_t pad[(0x80 - 4) / 4];
};
namespace SP {
struct cSPUIAssetVerbs : RefCounted {                              // 0x5c bytes
    cSPUIAssetVerbs();                                             // 0x00656b00
    void Init(IWindow* w);                                         // 0x00656b80
    uint32_t pad[(0x5c - 4) / 4];
};
}
struct cAssetHelperA8 : RefCounted {                               // 0xd0 bytes
    cAssetHelperA8();                                              // 0x006700d0
    virtual void r08(); virtual void r0c(); virtual void r10(); virtual void r14();
    virtual void r18(); virtual void r1c();
    virtual void Init(cSPUILayout* layout, cAssetMetadata* md);    // +0x20
    uint32_t pad[(0xd0 - 4) / 4];
};
struct ZoomOffset {
    int a, b, c;
    ZoomOffset() : a(0), b(0), c(0) {}
};
namespace UI {
struct TextZoomName {                                              // 0x78 bytes
    virtual void z00();
    virtual int  AddRef();                                         // +0x04
    virtual int  Release();                                        // +0x08
    TextZoomName();                                                // 0x008345c0
    void SetTargetWindow(IText* text, int a, int b, int c, ZoomOffset off);   // 0x00834fa0
    uint32_t pad[(0x78 - 4) / 4];
};
}

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* const old = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (old)
                old->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

inline void ShowWindow(IWindow* w, bool show)
{
    if (w)
        w->SetFlag(1, show);
}

namespace Simulator {
struct cSPScenarioModeSporepediaLargeAssetView : IWinProc {
    uint32_t pad004[(0x30 - 4) / 4];
    cSPUILayout* mpLayout;                                         // +0x30
    uint32_t pad034;
    AutoRefCount<IWindow> mWinRoot;                                // +0x38 0xf3c6dc19
    AutoRefCount<IWindow> mWinAuthor;                              // +0x3c 0x53d6fe2a
    AutoRefCount<IWindow> mWinDescription;                         // +0x40 0xb456a483
    AutoRefCount<IWindow> mWinTags;                                // +0x44 0xb456a47a
    uint32_t pad048;
    AutoRefCount<IWindow> mWinEdit;                                // +0x4c 0x06135298
    AutoRefCount<IWindow> mWin50;                                  // +0x50 0x06136d30
    AutoRefCount<IWindow> mWin54;                                  // +0x54 0x0615c7a8
    AutoRefCount<IWindow> mWin58;                                  // +0x58 0x07b26750
    AutoRefCount<IWindow> mWinsA[4];                               // +0x5c 0x07cc9c40 + i
    AutoRefCount<IWindow> mWinsB[4];                               // +0x6c 0x07ccb020 + i
    AutoRefCount<IWindow> mWin7c;                                  // +0x7c 0x07b15fc0
    AutoRefCount<IWindow> mWin80;                                  // +0x80 0x07b23b28
    AutoRefCount<IWindow> mWin84;                                  // +0x84 0x07b173e8
    AutoRefCount<IWindow> mWin88;                                  // +0x88 0x07b173f0
    AutoRefCount<IWindow> mWinBakingIndicator;                     // +0x8c 0x3431bd1e
    AutoRefCount<IWindow> mWinBakingForeground;                    // +0x90 0x34a0979a
    AutoRefCount<cRenderViewController> mRenderView;               // +0x94
    AutoRefCount<SP::cSPUIAssetVerbs> mAssetVerbs;                 // +0x98
    cAssetData*     mpAssetData;                                   // +0x9c
    cAssetMetadata* mpMetadata;                                    // +0xa0
    uint32_t pad0a4;
    AutoRefCount<cAssetHelperA8> mHelperA8;                        // +0xa8
    AutoRefCount<UI::TextZoomName> mTagsZoom;                      // +0xac
    AutoRefCount<UI::TextZoomName> mNameZoom;                      // +0xb0
    uint32_t pad0b4[3];
    bool mIsLoaded;                                                // +0xc0

    __forceinline bool IsOwnOrInvalid()
    {
        IAuthManager* am = SP::Pollen::AuthManager();
        cAssetMetadata* md = mpMetadata;
        return am->GetUserID() == md->GetAssetKey() || mpMetadata->GetAssetKey() == (uint64_t)-2 ||
               mpMetadata->GetAssetKey() == (uint64_t)-1;
    }
    void UpdateStats();                                            // 0x00ef4bd0
    void UpdateButtons();                                          // 0x00ef4e40
    void Load();
};

// @ 0x00ef50a0
void cSPScenarioModeSporepediaLargeAssetView::Load()
{
    if (mIsLoaded)
        return;

    mWinRoot = mpLayout->FindWindowByID(0xf3c6dc19, true);
    if (mWinRoot) {
        mWinRoot->AddWinProc(this);
        SPUIHelpers::SetWindowAreaToParent(mWinRoot);
        mRenderView = new("UI", 0, 0, 0, 0) cRenderViewController();
        mRenderView->Attach(mWinRoot);
    }

    AutoRefCount<IWindow> renderWin(mpLayout->FindWindowByID(0x080d8270, true));
    if (mWinRoot && renderWin) {
        const Rect& a = renderWin->GetRealArea();
        Rect r = mWinRoot->GetRealArea();
        float w = a.x2 - a.x1;
        float h = a.y2 - a.y1;
        if (w > h) {
            float rw = r.x2 - r.x1;
            float nw = rw - (w - h);
            float d = (rw - nw) * 0.5f;
            r.x1 += d;
            r.x2 -= d;
        } else if (h > w) {
            float rh = r.y2 - r.y1;
            float nh = rh - (h - w);
            float d = (rh - nh) * 0.5f;
            r.y1 += d;
            r.y2 -= d;
        }
        mWinRoot->SetLayoutArea(r);
    }

    mWinEdit = mpLayout->FindWindowByID(0x06135298, true);
    if (mWinEdit && !SP::Pollen::AuthManager()->IsOffline()) {
        bool queued = false;
        if (mpMetadata) {
            QueueVector& entries = AssetQueue()->mEntries;
            unsigned n = entries.size();
            for (unsigned i = 0; i < n; ++i) {
                QueueEntry& e = entries[i];
                if (e.mState == 2 && e.mAssetKey == mpMetadata->GetAssetKey()) {
                    queued = true;
                    break;
                }
            }
        }
        mWin54 = mpLayout->FindWindowByID(0x0615c7a8, true);
        if (mWin54)
            mWin54->SetFlag(1, queued);
        mWinEdit->SetFlag(1, mpMetadata != 0 && !queued && !IsOwnOrInvalid());
    } else {
        ShowWindow(mWinEdit, false);
    }

    mWin50 = mpLayout->FindWindowByID(0x06136d30, true);
    ShowWindow(mWin50, false);

    IWindow* verbsWin = mpLayout->FindWindowByID(0x34af0c8f, true);
    if (verbsWin) {
        mAssetVerbs = new("UI", 0, 0, 0, 0) SP::cSPUIAssetVerbs();
        mAssetVerbs->Init(verbsWin);
    }

    mWin58 = mpLayout->FindWindowByID(0x07b26750, true);
    for (int i = 0; i < 4; ++i) {
        mWinsA[i] = mpLayout->FindWindowByID(0x07cc9c40 + i, true);
        mWinsB[i] = mpLayout->FindWindowByID(0x07ccb020 + i, true);
    }
    UpdateStats();
    UpdateButtons();

    mHelperA8 = new("UI", 0, 0, 0, 0) cAssetHelperA8();
    mHelperA8->Init(mpLayout, mpMetadata);

    mWin7c = mpLayout->FindWindowByID(0x07b15fc0, true);
    mWin80 = mpLayout->FindWindowByID(0x07b23b28, true);
    mWin84 = mpLayout->FindWindowByID(0x07b173e8, true);
    mWin88 = mpLayout->FindWindowByID(0x07b173f0, true);
    mWinBakingIndicator = mpLayout->FindWindowByID(0x3431bd1e, true);
    mWinBakingForeground = mpLayout->FindWindowByID(0x34a0979a, true);
    ShowWindow(mWinBakingForeground, false);

    IWindow* nameWin = mpLayout->FindWindowByID(0x53d6fe29, true);
    if (nameWin) {
        nameWin->SetCaption(mpAssetData->GetName());
        mNameZoom = new("UI/cSPUITextZoom", 0, 0, 0, 0) UI::TextZoomName();
        mNameZoom->SetTargetWindow((IText*)nameWin->Cast(kITextType), 0, 0, 0, ZoomOffset());
    }

    mWinAuthor = mpLayout->FindWindowByID(0x53d6fe2a, true);
    if (mWinAuthor) {
        mWinAuthor->SetCaption(mpAssetData->GetAuthorName());
        SPUIHelpers::AutoSizeWindowForText(mWinAuthor, 0, 0);
        if (mWinAuthor->GetParent()) {
            Rect pr = mWinAuthor->GetParent()->GetRealArea();
            Rect a = mWinAuthor->GetRealArea();
            mWinAuthor->SetLocation((pr.x2 + pr.x1) * 0.5f - (a.x2 - a.x1) * 0.5f, a.y1);
        }
        if (mWinEdit) {
            Rect ar = mWinAuthor->GetRealArea();
            const Rect& er = mWinEdit->GetRealArea();
            mWinEdit->SetLocation(ar.x2, er.y1);
            Rect r = mWinEdit->GetRealArea();
            if (mWin50)
                SPUIHelpers::CenterWindow(mWin50, Point((r.x2 + r.x1) * 0.5f, (r.y2 + r.y1) * 0.5f));
            if (mWin54)
                SPUIHelpers::CenterWindow(mWin54, Point((r.x2 + r.x1) * 0.5f, (r.y2 + r.y1) * 0.5f));
        }
        cSPAssetDataOTDB* otdb;
        if (mpAssetData != 0 &&
            (otdb = (cSPAssetDataOTDB*)static_cast<IObject*>(mpAssetData)->Cast(0x13d55dc8)) != 0 &&
            otdb->IsLocalAsset())
            mWinAuthor->SetFlag(0x10, true);
        else
            mWinAuthor->SetFlag(0x10, false);
    }

    IWindow* sharedWin = mpLayout->FindWindowByID(0x056e3f98, true);
    if (sharedWin)
        sharedWin->SetFlag(1, mpAssetData->IsShared());

    mWinDescription = mpLayout->FindWindowByID(0xb456a483, true);
    const wchar_t* desc = mpAssetData->GetDescription();
    if (mWinDescription) {
        if (desc != 0 && wcslen(desc) != 0) {
            mWinDescription->SetCaption(desc);
            mWinDescription->GetParent()->SetFlag(1, true);
            mWinDescription->SetFlag(1, true);
        } else {
            mWinDescription->GetParent()->SetFlag(1, false);
            mWinDescription->SetFlag(1, false);
        }
    }
    if (mWinDescription && mWinDescription->GetParent())
        mWinDescription->GetParent()->AddWinProc(this);

    mWinTags = mpLayout->FindWindowByID(0xb456a47a, true);
    if (mWinTags && mpAssetData) {
        string16 tags;
        mpAssetData->GetTags(tags);
        mWinTags->SetCaption(tags.c_str());
    }
    if (mWinTags && mWinTags->GetParent())
        mWinTags->GetParent()->AddWinProc(this);

    IWindow* tagsBox = mpLayout->FindWindowByID(0x07eb4153, true);
    IText* tagsText = tagsBox ? (IText*)tagsBox->Cast(kITextType) : 0;
    if (mWinTags && tagsText) {
        Rect r = mWinTags->GetRealArea();
        tagsText->func14h(false);
        r.x1 = tagsText->ToWindow()->GetRealArea().x2;
        mWinTags->SetLayoutArea(r);
    }

    if (mWinTags) {
        mTagsZoom = new("UI/cSPUITextZoom", 0, 0, 0, 0) UI::TextZoomName();
        mTagsZoom->SetTargetWindow(mWinTags ? (IText*)mWinTags->Cast(kITextType) : 0, 0, 0, 0, ZoomOffset());
    }

    mIsLoaded = true;
}
}
