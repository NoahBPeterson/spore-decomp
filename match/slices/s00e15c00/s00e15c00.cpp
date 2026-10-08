// Slice s00e15c00: FUN_00e16090 (~1.9 KB, __thiscall, one pointer argument), refresh of a
// mission-tracker panel from a mission object (the argument).
//
// `this` holds the layout (+0xc, owned), the panel layout (+0x1c), the relationship strip
// (+0x20, owned), the root window (+0x24) and a status window (+0x2c). The mission object is
// queried through its vtable: status caption (+0xa8, shown in the +0x2c window unless the
// mission kind is 5 or it has no fill), then the three title/count windows
// (0x740ea83e / 0x55d3e68 / 0x52350c8) are captioned and laid out right-aligned, the caption
// windows 0x5235140 / 0x74cb0c14 are set, the mission's image and strip widgets are updated
// and the optional progress-icon layout is rebuilt.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (UI module: movss, x87 float returns, no EH frame).
#include "types.h"

typedef wchar_t char16;
struct Rect {
    float x1, y1, x2, y2;
    Rect() {}
    Rect(const Rect& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) {}
};

extern char16 gEmptyString[];   // 0x01667bac
extern const char16 gStr13ec468[];   // 0x013ec468
extern const char gNameUI[];       // 0x013f6b3c
void operator delete[](void* p);  // 0x00f47380
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   int file, int line);   // 0x00f473a0

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
    uint32_t a, b, c;
};

// ---------------------------------------------------------------------------------------
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
    virtual void  v5c(); virtual void v60(); virtual void v64();
    virtual void  SetSize(float w, float h);                        // 0x68
    virtual void  SetLayoutArea(const Rect& area);                  // 0x6c
    virtual void  v70(); virtual void v74(); virtual void v78();
    virtual void  SetFlag(uint32_t flag, bool value);               // 0x7c
    virtual void  SetCaption(const char16* caption);                // 0x80
    virtual void  v84(); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void  v94();
    virtual void  v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void  va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
    virtual void  vb8(); virtual void vbc(); virtual void vc0(); virtual void vc4();
    virtual void  vc8(); virtual void vcc(); virtual void vd0(); virtual void vd4();
    virtual void  vd8(); virtual void vdc(); virtual void ve0(); virtual void ve4();
    virtual void  ve8(); virtual void vec();
    virtual IWindow* FindWindowByID(uint32_t controlID, bool recursive);   // 0xf0
    virtual void  vf4(); virtual void vf8(); virtual void vfc(); virtual void v100();
    virtual void  SetOwner(void* owner);                            // 0x104
};

// Result of Cast(0xf15f4bd) on a window.
class IWinText {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10();
    virtual void SetEnabled(int on);                                // 0x14
};

// The mission object (argument). Its vtable is queried directly.
class IMission {
public:
    virtual void m00(); virtual void m04(); virtual void m08();
    virtual void* Cast(uint32_t typeID);                            // 0x0c
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1c();
    virtual void m20(); virtual void m24(); virtual void m28(); virtual void m2c();
    virtual void m30(); virtual void m34(); virtual void m38(); virtual void m3c();
    virtual void m40(); virtual void m44(); virtual void m48(); virtual void m4c();
    virtual void m50(); virtual void m54(); virtual void m58(); virtual void m5c();
    virtual int  GetKind();                                         // 0x60
    virtual void m64(); virtual void m68(); virtual void m6c(); virtual void m70();
    virtual void m74(); virtual void m78();
    virtual float GetProgress();                                    // 0x7c
    virtual void m80();
    virtual void OnShown();                                         // 0x84
    virtual void OnDone();                                          // 0x88
    virtual void GetTitleText(string16* out);                       // 0x8c
    virtual void m90(); virtual void m94();
    virtual void GetText98(string16* out);                          // 0x98
    virtual void m9c();
    virtual void GetTextA0(string16* out);                          // 0xa0
    virtual int  GetStatusFill();                                   // 0xa4
    virtual void GetStatusText(string16* out);                      // 0xa8
    virtual void mac(); virtual void mb0();
    virtual void GetTextB4(string16* out);                          // 0xb4

    int  FUN_00c2ec30();   // 0x00c2ec30 progress-bar layout id
    int  FUN_00c2ec80();   // 0x00c2ec80 progress-icons window id
    bool GetProgressIconLayout(ResourceKey* out);   // 0x00c2e4f0
};

// Result of Cast(0x7406a570) on the mission.
class IMissionImage {
public:
    bool FUN_00c2f320(void** pTexture);   // 0x00c2f320
    int  FUN_00c2e820();                  // 0x00c2e820
};
// Result of Cast(0x34364118).
class IMissionValue {
public:
    float FUN_00c2f650();                 // 0x00c2f650
};

class cSPUILayout {
public:
    virtual void d00();
    virtual void AddRef();                                          // 0x04
    virtual void Release();                                         // 0x08
    uint32_t d[5];
    cSPUILayout();                                                  // 0x00810000
    IWindow* FindWindowByID(uint32_t id, bool recursive);           // 0x008105b0
    void Shutdown(int arg);                                         // 0x00811ad0
    void Init(const ResourceKey* key, int arg, uint32_t id);        // 0x008120d0
    bool SetParentWin(IWindow* win, int arg, uint32_t id);          // 0x008121b0
};

class cSPUIRelationshipStrip {
public:
    virtual void d00();
    virtual void AddRef();                                          // 0x04
    virtual void Release();                                         // 0x08
    uint32_t d[2];
    cSPUIRelationshipStrip();                                       // 0x00e2ec40
    void Init(IWindow* win);                                        // 0x00e2ec60
    void FUN_00e2ed70(int v);                                       // 0x00e2ed70
    void FUN_00e2ef80(float v);                                     // 0x00e2ef80
};

// Texture wrapper / image (UI::Image).
class cTextureInstanceWrapper {
public:
    virtual void AddRef();
    uint32_t d[4];
    cTextureInstanceWrapper(void* tex);                             // 0x008333b0
    uint32_t GetWidth();                                            // 0x008332a0
    uint32_t GetHeight();                                           // 0x008332d0
};
class UIImage {
public:
    virtual void AddRef();                                          // 0x00
    virtual void Release();                                         // 0x04
    uint32_t d[10];
    UIImage(cTextureInstanceWrapper* tex, uint32_t w, uint32_t h, float u0, float v0, float u1,
            float v1, int flags);                                   // 0x009579f0
};

// Smart pointer assignment (0x00572620).
template<class T> struct RefPtr {
    T* p;
    void Set(T* n);
};
typedef RefPtr<cSPUIRelationshipStrip> StripPtr;
typedef RefPtr<cSPUILayout> LayoutPtr;

void SetImageFromLayout(IWindow* w, void* cache, int layoutId, int flags);   // 0x00806a60 (cdecl)
void SetDrawableImage(IWindow* w, UIImage* img, int flags);                  // 0x008068d0 (cdecl)
void* GetImageCache();                                                       // 0x00b3d400 (cdecl)
IWinText* CastToText(IWindow* w);                                            // 0x005994b0 (cdecl)
void UpdateProgessIcons(cSPUILayout* layout, IMission* mission);             // 0x00e2e790 (cdecl)

class cImageCacheOwner {
public:
    void* FUN_00e14c70();   // 0x00e14c70
};

class cMissionTracker {
public:
    uint32_t  pad00[3];
    LayoutPtr mpLayout;            // +0x0c
    uint32_t  pad10[3];
    cSPUILayout* mpPanelLayout;    // +0x1c
    StripPtr  mpStrip;             // +0x20
    IWindow*  mpRoot;              // +0x24
    uint32_t  pad28;
    IWindow*  mpStatusWin;         // +0x2c
    uint32_t  pad30[(0x98 - 0x30) / 4];
    float     mfProgress;          // +0x98

    void FUN_00e145b0(IMission* m);    // 0x00e145b0
    void FUN_00e14690(IMission* m);    // 0x00e14690
    void FUN_00e16090(IMission* m);
};

// @ 0x00E16090
void cMissionTracker::FUN_00e16090(IMission* m)
{
    if (!m)
        return;
    m->OnShown();
    if (mpStatusWin) {
        int fill = m->GetStatusFill();
        if (m->GetKind() == 5 || fill == 0) {
            mpStatusWin->SetFlag(1, false);
            mpStatusWin->SetCaption(gStr13ec468);
        } else {
            mpStatusWin->SetFlag(1, true);
            string16 status;
            m->GetStatusText(&status);
            mpStatusWin->SetCaption(status.mpBegin);
        }
    }

    IWindow* wCount = mpRoot->FindWindowByID(0x740ea83e, true);
    IWindow* wIcon = mpRoot->FindWindowByID(0x55d3e68, true);
    IWindow* wTitle = mpRoot->FindWindowByID(0x52350c8, true);
    if (wCount && wIcon && wTitle) {
        string16 countText;
        m->GetTextB4(&countText);
        wCount->SetFlag(1, true);
        wCount->SetCaption(countText.mpBegin);
        if (countText.mpBegin == countText.mpEnd) {
            const Rect& r = wCount->GetRealArea();
            Rect rc = r;
            rc.x1 = rc.x2;
            wCount->SetLayoutArea(rc);
        } else {
            IWinText* t = CastToText(wCount);
            if (t)
                t->SetEnabled(0);
        }
        bool hasLayout = false;
        int layoutId = m->FUN_00c2ec30();
        if (layoutId) {
            hasLayout = true;
            void* cache = ((cImageCacheOwner*)GetImageCache())->FUN_00e14c70();
            SetImageFromLayout(wIcon, cache, layoutId, -1);
        } else {
            wIcon->SetFlag(1, false);
        }
        const Rect& countArea = wCount->GetRealArea();
        const Rect& iconArea = wIcon->GetRealArea();
        Rect rc = iconArea;
        float width = rc.x2 - rc.x1;
        float x = countArea.x1;
        if (countText.mpBegin != countText.mpEnd)
            x -= 5.0f;
        rc.x2 = x;
        rc.x1 = x - width;
        wIcon->SetLayoutArea(rc);

        string16 titleText;
        m->GetTitleText(&titleText);
        wTitle->SetCaption(titleText.mpBegin);
        const Rect& titleArea = wTitle->GetRealArea();
        float h = titleArea.y2 - titleArea.y1;
        wTitle->SetSize((hasLayout ? rc.x1 : rc.x2) - titleArea.x1, h);
    }

    string16 text98;
    m->GetTextA0(&text98);
    IWindow* w5 = mpRoot->FindWindowByID(0x5235140, true);
    if (w5)
        w5->SetCaption(text98.mpBegin);
    string16 text9c;
    m->GetText98(&text9c);
    IWindow* w6 = mpRoot->FindWindowByID(0x74cb0c14, true);
    if (w6)
        w6->SetCaption(text9c.mpBegin);

    IMissionImage* img = (IMissionImage*)m->Cast(0x7406a570);
    if (img) {
        IWindow* wImage = mpRoot->FindWindowByID(0x5235098, true);
        void* tex = 0;
        if (wImage && img->FUN_00c2f320(&tex)) {
            cTextureInstanceWrapper* wrap = new(gNameUI, 0, 0, 0, 0) cTextureInstanceWrapper(tex);
            UIImage* im = new("UI/Image", 0, 0, 0, 0)
                UIImage(wrap, wrap->GetWidth(), wrap->GetHeight(), 0.0f, 0.0f, 1.0f, 1.0f, 0);
            if (im)
                im->AddRef();
            SetDrawableImage(wImage, im, -1);
            if (im)
                im->Release();
        }
        int stripVal = img->FUN_00c2e820();
        IWindow* wStrip = mpRoot->FindWindowByID(0x94a4a6ea, true);
        if (wStrip) {
            if (!mpStrip.p) {
                mpStrip.Set(new(gNameUI, 0, 0, 0, 0) cSPUIRelationshipStrip());
                mpStrip.p->Init(wStrip);
            }
            mpStrip.p->FUN_00e2ed70(stripVal);
            wStrip->SetFlag(1, true);
        }
    }

    IMissionValue* val = (IMissionValue*)m->Cast(0x34364118);
    if (val) {
        float v = val->FUN_00c2f650();
        IWindow* wStrip = mpRoot->FindWindowByID(0x94a4a6ea, true);
        if (wStrip) {
            if (!mpStrip.p) {
                mpStrip.Set(new(gNameUI, 0, 0, 0, 0) cSPUIRelationshipStrip());
                mpStrip.p->Init(wStrip);
            }
            mpStrip.p->FUN_00e2ef80(v);
            wStrip->SetOwner(this);
            wStrip->SetFlag(1, true);
        }
    }

    int iconWinId = m->FUN_00c2ec80();
    if (iconWinId) {
        IWindow* wIcons = mpPanelLayout->FindWindowByID(iconWinId, true);
        if (wIcons) {
            ResourceKey key = {0, 0, 0};
            if (m->GetProgressIconLayout(&key)) {
                LayoutPtr* slot = &mpLayout;
                if (slot->p) {
                    slot->p->Shutdown(1);
                    if (slot->p) {
                        cSPUILayout* old = slot->p;
                        slot->p = 0;
                        old->Release();
                    }
                }
                slot->Set(new(gNameUI, 0, 0, 0, 0) cSPUILayout());
                slot->p->Init(&key, 1, 0x5b598fa);
                slot->p->SetParentWin(wIcons, 1, 0x5b598fa);
                wIcons->v94();
                wIcons->SetFlag(1, true);
                UpdateProgessIcons(slot->p, m);
            }
        }
    }

    FUN_00e145b0(m);
    FUN_00e14690(m);
    mfProgress = m->GetProgress();
    m->OnDone();
}
