// Slice s00649340 -- SP::cSPUIAssetBrowser::ReloadCallback (window wiring / teardown).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), same module as s00650630.
#include "types.h"

void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);                   // 0x00f473a0
void* operator new(unsigned int n, int align, const char* name, void* alloc);  // 0x009512d0
void* GetUIAllocator();                                           // 0x009512c0

struct IWindow {
    virtual void AddRef();
    virtual void Release();
    virtual void vf2(); virtual void vf3(); virtual void vf4(); virtual void vf5();
    virtual void vf6(); virtual void vf7(); virtual void vf8(); virtual void vf9();
    virtual void vf10(); virtual void vf11(); virtual void vf12(); virtual void vf13();
    virtual void vf14(); virtual void vf15();
    virtual const wchar_t* GetCaption();                         // slot 16 (+0x40)
    virtual void vf17(); virtual void vf18(); virtual void vf19(); virtual void vf20();
    virtual void vf21(); virtual void vf22(); virtual void vf23(); virtual void vf24();
    virtual void vf25(); virtual void vf26(); virtual void vf27(); virtual void vf28();
    virtual void vf29(); virtual void vf30();
    virtual void SetFlag(int flag, bool value);                   // slot 31 (+0x7c)
    virtual void vf32(); virtual void vf33(); virtual void vf34(); virtual void vf35();
    virtual void vf36(); virtual void vf37(); virtual void vf38(); virtual void vf39();
    virtual void vf40(); virtual void vf41(); virtual void vf42(); virtual void vf43();
    virtual void vf44(); virtual void vf45(); virtual void vf46(); virtual void vf47();
    virtual void vf48(); virtual void vf49(); virtual void vf50(); virtual void vf51();
    virtual void vf52(); virtual void vf53(); virtual void vf54(); virtual void vf55();
    virtual void vf56(); virtual void vf57(); virtual void vf58(); virtual void vf59();
    virtual void vf60(); virtual void vf61(); virtual void vf62(); virtual void vf63();
    virtual void vf64();
    virtual void AddWinProc(void* proc);                          // slot 65 (+0x104)
};

template <typename T>
struct AutoRefCount {
    T* mpObject;
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
};

// Members whose assignment the original calls out of line (0x00b5f950, a COMDAT-folded
// AutoRefCount<T>::operator=(T*)); teardown still clears them inline.
template <typename T>
struct AutoRefCountOOL {
    T* mpObject;
    AutoRefCountOOL& operator=(T* p);                             // 0x00b5f950
    void Clear() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
};

struct cSPUILayout {
    IWindow* FindWindowByID(unsigned int id, bool bRecurse);      // 0x008105b0
};

// Objects with AddRef at slot 0 / Release at slot 1.
struct RefObj0 {
    virtual void AddRef();
    virtual void Release();
};
// Objects with AddRef at slot 1 / Release at slot 2.
struct RefObj1 {
    virtual void vf0();
    virtual void AddRef();
    virtual void Release();
};

struct cSPUISporeGuidePage : RefObj1 {
    uint32_t pad04[(0x70 - 4) / 4];                          // sizeof 0x70
    cSPUISporeGuidePage();                                        // 0x00672400
    void Init(IWindow* w);                                        // 0x00672480
    void Shutdown();                                              // 0x006725a0
};
struct cSPUIAssetWebBrowser : RefObj0 {
    uint32_t pad04[(0xac - 4) / 4];                          // sizeof 0xac
    cSPUIAssetWebBrowser();                                       // 0x0065b930
    void Init(IWindow* w, bool b);                                // 0x0065bac0
    void Shutdown();                                              // 0x0065b1b0
};
struct cSPUIFeedEdit : RefObj1 {
    uint32_t pad04[(0x14c - 4) / 4];                          // sizeof 0x14c
    cSPUIFeedEdit();                                              // 0x0065daa0
    void Init(IWindow* w);                                        // 0x0065f700
    void Shutdown();                                              // 0x0065ca10
};
struct cSPUIFeedList : RefObj0 {
    uint32_t pad04[(0x6c - 4) / 4];                          // sizeof 0x6c
    cSPUIFeedList();                                              // 0x00663040
    void Init(IWindow* a, void* p, bool b, IWindow* c);           // 0x00663860
    void Shutdown();                                              // 0x006628d0
};
struct cSPUIAssetGrid : RefObj0 {
    uint32_t pad04[(0x1f0 - 4) / 4];                          // sizeof 0x1f0
    cSPUIAssetGrid();                                             // 0x00651990
    void Init(IWindow* a, IWindow* b, IWindow* c);                // 0x00651ff0
    void Shutdown();                                              // 0x00654650
};
struct cSPUIAssetPreview : RefObj0 {   // 0xa30-byte object at browser+0xb8
    uint32_t pad04[(0xa30 - 4) / 4];                          // sizeof 0xa30
    cSPUIAssetPreview();                                          // 0x00643840
    void Init();                                                  // 0x00642860
    void Shutdown();                                              // 0x00643d30
};
struct cSPUIAssetVerbs : RefObj0 {
    uint32_t pad04[(0x5c - 4) / 4];                          // sizeof 0x5c
    cSPUIAssetVerbs();                                            // 0x00656b00
    void Init(IWindow* w);                                        // 0x00656b80
    void Shutdown();                                              // 0x006566f0
};

// Window-glide procedure ("UI/... Window Glide").
struct IGlideParams {          // embedded at +0x0c
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3();
    virtual void vf4(); virtual void vf5();
    virtual void SetDuration(float t);                            // +0x18
    virtual void vf7();
    virtual void SetEnabled(bool b);                              // +0x20
    virtual void vf9();
    virtual void SetEase(float a, float b);                       // +0x28
    virtual void vf11();
    virtual void SetMode(int m);                                  // +0x30
    virtual void vf13();
    virtual void SetRate(float r);                                // +0x38
    uint32_t pad04[0x14];
};
struct Vector2 { float x, y; Vector2(float x_, float y_) : x(x_), y(y_) {} };
struct IGlideOffset {          // embedded at +0x60
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3();
    virtual void vf4(); virtual void vf5();
    virtual void SetOffset(const Vector2& v);                     // +0x18
};
struct GlideRefBase {
    virtual void AddRef();
    virtual void Release();
    uint32_t pad04[2];
};
struct WindowGlide : GlideRefBase, IGlideParams, IGlideOffset {  // IGlideParams @+0x0c, IGlideOffset @+0x60
    uint32_t pad64[3];
    WindowGlide();                                                // 0x009700b0
};

struct ScreenInfo { int width; int pad[7]; };
struct IRenderer {
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3();
    virtual void vf4(); virtual void vf5(); virtual void vf6();
    virtual ScreenInfo* GetScreenInfo();                          // +0x1c
};
IRenderer* GetRenderer();                                         // 0x0067dd50

struct StyleObj { uint32_t pad[0x80]; float mSize; };             // +0x200
struct StyleManager {
    StyleObj* GetStyle(const wchar_t* name, int flags);          // 0x00894670
};
StyleManager* GetStyleManager(bool bCreate);                      // 0x00885bd0

struct AppPropsInner { uint32_t pad[0x46]; int mSporepediaWebEnabled; };  // +0x118
struct AppProps { uint32_t pad[0xf]; AppPropsInner* mpInner; };           // +0x3c
extern AppProps* g_AppProperties;                                 // 0x015fd918

void SetWindowAreaToParent(IWindow* w);                           // 0x00806bf0
void EndModal(IWindow* w, int a, int b);                          // 0x00809c50
void BeginModal(IWindow* w, int a, int b);                        // 0x008099a0
void PrepareWebWindow(IWindow* w);                                // 0x008098d0
void SetScale(IWindow* w, float sx, float sy);                    // 0x00808190
void SetWindowAlpha(IWindow* w, float a);                         // 0x00804fc0

struct WinProcBase { uint32_t pad[5]; };

struct cSPUIAssetBrowser {
    uint32_t pad00[2];
    WinProcBase mWinProc;                                         // +0x08
    bool mbModal;                                                 // +0x1c
    char pad1d[0x0c];
    bool mb29;                                                    // +0x29
    char pad2a[0x2e];
    cSPUILayout* mLayout;                                         // +0x58
    uint32_t pad5c;
    AutoRefCount<IWindow> mWin60;
    AutoRefCount<IWindow> mWin64;   // modal root
    AutoRefCount<IWindow> mWin68;
    AutoRefCount<IWindow> mWin6c;
    AutoRefCount<IWindow> mWin70;
    AutoRefCount<IWindow> mWin74;
    AutoRefCount<IWindow> mWin78;
    AutoRefCount<IWindow> mWin7c;
    AutoRefCount<IWindow> mWin80;
    AutoRefCount<IWindow> mWin84;
    AutoRefCount<IWindow> mWin88;
    AutoRefCount<IWindow> mWin8c;
    AutoRefCount<IWindow> mWin90;   // Sporepedia webpage
    AutoRefCount<IWindow> mWin94;
    AutoRefCount<IWindow> mWin98;   // Spore guide
    AutoRefCount<IWindow> mWin9c;
    AutoRefCount<IWindow> mWinA0;
    uint32_t padA4;
    AutoRefCount<IWindow> mWinA8;
    AutoRefCount<IWindow> mWinAC;
    AutoRefCount<IWindow> mWinB0;
    AutoRefCount<IWindow> mWinB4;
    AutoRefCountOOL<cSPUIAssetPreview> mPreview;                  // +0xb8
    AutoRefCountOOL<cSPUIAssetGrid> mGrid;                        // +0xbc
    AutoRefCountOOL<cSPUIFeedList> mFeedList;                     // +0xc0
    AutoRefCount<cSPUIFeedEdit> mFeedEdit;                        // +0xc4
    AutoRefCount<cSPUIAssetVerbs> mVerbs;                         // +0xc8
    uint32_t padCC[(0x1e0 - 0xcc) / 4];
    void* mp1E0;                                                  // +0x1e0
    uint32_t pad1E4[(0x214 - 0x1e4) / 4];
    float mStyleSize;                                             // +0x214
    uint32_t pad218;
    AutoRefCount<cSPUIAssetWebBrowser> mWebBrowser;               // +0x21c
    AutoRefCount<cSPUIAssetWebBrowser> mWebBrowser2;              // +0x220
    AutoRefCount<cSPUISporeGuidePage> mGuidePage;                 // +0x224

    void FilterGridEntries(bool b);                               // 0x00648d90
};

static __forceinline void SetupGlide(WindowGlide* glide) {
    glide->SetEnabled(true);
    glide->SetDuration(0.5f);
    glide->SetEase(0.2f, 0.2f);
    glide->SetMode(2);
    glide->SetRate(10.0f);
    ScreenInfo info = *GetRenderer()->GetScreenInfo();
    glide->SetOffset(Vector2((float)info.width * 1.5f, 0.0f));
}

// @ 0x00649340  SP::cSPUIAssetBrowser::ReloadCallback
void ReloadCallback(cSPUIAssetBrowser* self, void* unused, bool bLoad) {
    if (!bLoad) {
        self->FilterGridEntries(false);
        if (self->mWin64.mpObject)
            EndModal(self->mWin64.mpObject, 0, 0);
        if (self->mGuidePage.mpObject) {
            self->mGuidePage.mpObject->Shutdown();
            self->mGuidePage = 0;
        }
        if (self->mWebBrowser.mpObject) {
            self->mWebBrowser.mpObject->Shutdown();
            self->mWebBrowser = 0;
        }
        if (self->mWebBrowser2.mpObject) {
            self->mWebBrowser2.mpObject->Shutdown();
            self->mWebBrowser2 = 0;
        }
        if (self->mFeedList.mpObject) {
            self->mFeedList.mpObject->Shutdown();
            self->mFeedList.Clear();
        }
        if (self->mFeedEdit.mpObject) {
            self->mFeedEdit.mpObject->Shutdown();
            self->mFeedEdit = 0;
        }
        if (self->mGrid.mpObject) {
            self->mGrid.mpObject->Shutdown();
            self->mGrid.Clear();
        }
        if (self->mPreview.mpObject) {
            self->mPreview.mpObject->Shutdown();
            self->mPreview.Clear();
        }
        if (self->mVerbs.mpObject) {
            self->mVerbs.mpObject->Shutdown();
            self->mVerbs = 0;
        }
        return;
    }

    self->mWin64 = self->mLayout->FindWindowByID(0x53c6dc80, true);
    self->mWin80 = self->mLayout->FindWindowByID(0xd40f99b8, true);
    if (self->mWin64.mpObject) {
        self->mWin64.mpObject->AddWinProc(&self->mWinProc);
        SetWindowAreaToParent(self->mWin64.mpObject);
        self->mWin64.mpObject->SetFlag(1, false);
    }
    if (self->mWin80.mpObject) {
        SetWindowAreaToParent(self->mWin80.mpObject);
        self->mWin80.mpObject->SetFlag(1, false);
    }

    self->mWin60 = self->mLayout->FindWindowByID(0x061da4d6, true);
    self->mWin98 = self->mLayout->FindWindowByID(0x058c80b8, true);
    if (self->mWin98.mpObject) {
        self->mGuidePage = new ("UI", 0, 0, 0, 0) cSPUISporeGuidePage();
        self->mGuidePage.mpObject->Init(self->mWin98.mpObject);
    }

    self->mWin90 = self->mLayout->FindWindowByID(0xd4a1f5f0, true);
    if (self->mWin90.mpObject) {
        if (g_AppProperties->mpInner->mSporepediaWebEnabled)
            PrepareWebWindow(self->mWin64.mpObject);
        WindowGlide* glide = new (8, "UI/Sporepedia webpage Window Glide", GetUIAllocator()) WindowGlide();
        if (glide)
            glide->AddRef();
        SetupGlide(glide);
        self->mWin90.mpObject->AddWinProc(glide);
        self->mWebBrowser = new ("UI", 0, 0, 0, 0) cSPUIAssetWebBrowser();
        self->mWebBrowser.mpObject->Init(self->mWin90.mpObject, false);
        self->mFeedEdit = new ("UI", 0, 0, 0, 0) cSPUIFeedEdit();
        self->mFeedEdit.mpObject->Init(self->mWin90.mpObject);
        glide->Release();
    }

    self->mWin94 = self->mLayout->FindWindowByID(0x062983b8, true);
    if (self->mWin94.mpObject) {
        self->mWebBrowser2 = new ("UI", 0, 0, 0, 0) cSPUIAssetWebBrowser();
        self->mWebBrowser2.mpObject->Init(self->mWin94.mpObject, true);
    }

    self->mWinB0 = self->mLayout->FindWindowByID(0xb44ec3db, true);
    if (self->mWinB0.mpObject) {
        const wchar_t* name = self->mWinB0.mpObject->GetCaption();
        StyleObj* style = GetStyleManager(true)->GetStyle(name, 0);
        if (style)
            self->mStyleSize = style->mSize;
    }

    self->mWinB4 = self->mLayout->FindWindowByID(0x066787d8, true);
    self->mWin9c = self->mLayout->FindWindowByID(0x94174874, true);
    if (self->mWin9c.mpObject) {
        SetScale(self->mWin9c.mpObject, 0.1f, 0.1f);
        SetWindowAlpha(self->mWin9c.mpObject, 0.0f);
        self->mWin9c.mpObject->SetFlag(1, true);
    }

    self->mWinA0 = self->mLayout->FindWindowByID(0x94177e4a, true);
    self->mWin84 = self->mLayout->FindWindowByID(0x34ac3265, true);
    self->mWin88 = self->mLayout->FindWindowByID(0x25c6faed, true);
    self->mWin8c = self->mLayout->FindWindowByID(0x05ac4930, true);
    self->mWinAC = self->mLayout->FindWindowByID(0x05cd544b, true);
    self->mWinA8 = self->mLayout->FindWindowByID(0x0580ab50, true);
    if (self->mWinA8.mpObject) {
        self->mVerbs = new ("UI", 0, 0, 0, 0) cSPUIAssetVerbs();
        self->mVerbs.mpObject->Init(self->mWinA8.mpObject);
    }

    self->mWin68 = self->mLayout->FindWindowByID(0x53c5b390, true);
    self->mWin6c = self->mLayout->FindWindowByID(0x07de7437, true);
    if (self->mWin68.mpObject && self->mWin6c.mpObject) {
        self->mFeedList = new ("UI", 0, 0, 0, 0) cSPUIFeedList();
        if (self->mp1E0)
            self->mFeedList.mpObject->Init(self->mWin68.mpObject, self->mp1E0, self->mb29,
                                           self->mWin6c.mpObject);
    }

    self->mWin70 = self->mLayout->FindWindowByID(0x53c5b392, true);
    self->mWin74 = self->mLayout->FindWindowByID(0x53c5b391, true);
    if (self->mWin74.mpObject) {
        WindowGlide* glide = new (8, "UI/Asset Window Glide", GetUIAllocator()) WindowGlide();
        if (glide)
            glide->AddRef();
        SetupGlide(glide);
        self->mWin74.mpObject->AddWinProc(glide);
        glide->Release();
    }

    self->mWin78 = self->mLayout->FindWindowByID(0x06737680, true);
    self->mWin7c = self->mLayout->FindWindowByID(0x07d13d88, true);
    if (self->mWin74.mpObject && self->mWin78.mpObject && self->mWin7c.mpObject) {
        self->mGrid = new ("UI", 0, 0, 0, 0) cSPUIAssetGrid();
        self->mGrid.mpObject->Init(self->mWin74.mpObject, self->mWin78.mpObject,
                                   self->mWin7c.mpObject);
        self->mPreview = new ("UI", 0, 0, 0, 0) cSPUIAssetPreview();
        self->mPreview.mpObject->Init();
    }

    if (self->mbModal && self->mWin64.mpObject)
        BeginModal(self->mWin64.mpObject, 0, 0);
    self->FilterGridEntries(false);
}
