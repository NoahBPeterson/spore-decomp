// Play-mode UI module (0x00634490..0x0063550F): photo-browser navigation, the play-mode token
// translator, and the cSPPlayModeUI window helpers (find/enable/highlight/tooltips...).
// Compiled /O2 /MD /Gy /TP /GS- (no /arch:SSE); the SSE-compiled functions live in s00634490b.cpp.

#include "s00634490_ui.h"

extern "C" void* memmove(void*, const void*, size_t);

// ---- strings -------------------------------------------------------------
struct wstring16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAlloc;
    wstring16& operator=(const wchar_t* p);   // 0x005c3d90
};

// ---------------------------------------------------------------------------
// photo browser: next/prev + refresh
// ---------------------------------------------------------------------------
struct cJob {
    int ContinueJob();
};
struct RBNode;
struct RBAnchor {
    RBNode* mpNodeRight;
    RBNode* mpNodeLeft;
    RBNode* mpNodeParent;
    uint8_t mColor;
};
struct PhotoTypeMap {
    uint32_t mCompare;
    RBAnchor mAnchor;
    uint32_t mnSize;
    void DoNuke(RBNode* n);   // 0x009a9600
    void clear() {
        DoNuke(mAnchor.mpNodeParent);
        mAnchor.mpNodeRight = (RBNode*)&mAnchor;
        mAnchor.mpNodeLeft = (RBNode*)&mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
};
struct PhotoBrowser {
    virtual void v0();
    uint32_t mPhotosBegin;      // +0x04
    uint32_t mPhotosEnd;        // +0x08
    uint32_t pad0[3];
    uint32_t mCurrentFirstPhotoIndex;      // +0x18
    uint32_t mCurrentSelectedPhotoIndex;   // +0x1c
    uint32_t pad1[(0x68 - 0x20) / 4];
    PhotoTypeMap mPhotoTypeMap;            // +0x68
    uint32_t pad2[(0xea4 - 0x80) / 4];
    uint32_t mPhotoCount;                  // +0xea4

    uint32_t Size() const { return (uint32_t)((int)(mPhotosEnd - mPhotosBegin) >> 2); }
    cJob* IsPhotosWriting();               // 0x00630470
    uint32_t PhotoCountChanged();          // 0x00631b30
    void FUN_00634030();
    void ClearLoadedPhotos();              // 0x00632b00
    void ShowImageThumbnail();             // 0x00633cc0
    void UpdatePhotoCountText();           // 0x00630d10
    void ReleaseAsyncHandle();             // 0x006303a0
    void FUN_00633ea0();

    void RefreshAfterDelete();
    void NextPhoto();
    void PrevPhoto();
};

// @ 0x00634490
void PhotoBrowser::RefreshAfterDelete()
{
    cJob* job = IsPhotosWriting();
    if (job) {
        while (job->ContinueJob() == 4) {
        }
    }
    mPhotoTypeMap.clear();
    uint32_t n = PhotoCountChanged();
    if (n != mPhotoCount) {
        mPhotoCount = n;
        FUN_00634030();
    }
    if (mCurrentFirstPhotoIndex >= 5) {
        mCurrentFirstPhotoIndex -= 5;
        ClearLoadedPhotos();
    }
    ShowImageThumbnail();
    UpdatePhotoCountText();
}

// @ 0x00634520
void PhotoBrowser::NextPhoto()
{
    ++mCurrentSelectedPhotoIndex;
    if (mCurrentSelectedPhotoIndex >= Size()) {
        mCurrentSelectedPhotoIndex = Size() - 1;
        FUN_00633ea0();
        UpdatePhotoCountText();
    } else {
        ReleaseAsyncHandle();
        FUN_00633ea0();
        UpdatePhotoCountText();
    }
}

// @ 0x00634570
void PhotoBrowser::PrevPhoto()
{
    uint32_t i = mCurrentSelectedPhotoIndex;
    if (i > 0 && i < Size()) {
        mCurrentSelectedPhotoIndex = i - 1;
        ReleaseAsyncHandle();
    }
    FUN_00633ea0();
    UpdatePhotoCountText();
}

// ---------------------------------------------------------------------------
// cPlayModeTokenTranslator
// ---------------------------------------------------------------------------
struct cStringTokenTranslator {
    virtual void v0();
    uint32_t pad;
    cStringTokenTranslator();     // 0x006b5870
};
struct cPlayModeTokenTranslator : cStringTokenTranslator {
    uint32_t pageCurrent;         // +0x08
    uint32_t pageCount;           // +0x0c
    uint32_t photoCurrent;        // +0x10
    uint32_t photoCount;          // +0x14
    const wchar_t* movieName;     // +0x18
    const wchar_t* moviePathname; // +0x1c
    uint32_t bgPageCurrent;       // +0x20
    uint32_t bgPageCount;         // +0x24
    uint32_t animPageCurrent;     // +0x28
    uint32_t animPageCount;       // +0x2c
    const wchar_t* videoURL;      // +0x30
    const wchar_t* statusMessage; // +0x34
    const wchar_t* gifName;       // +0x38
    const wchar_t* mayaExportName;// +0x3c
    const wchar_t* mayaExportPath;// +0x40
    const wchar_t* mYear;         // +0x44
    const wchar_t* mMonth;        // +0x48
    const wchar_t* mDayOfMonth;   // +0x4c
    const wchar_t* mTime;         // +0x50
    const wchar_t* mUnused54;     // +0x54
    const wchar_t* movieNamePrefix; // +0x58
    const wchar_t* mUnused5c;     // +0x5c

    cPlayModeTokenTranslator();
    bool TranslateToken(const wchar_t* token, wstring16* out);
};

// @ 0x006345b0
cPlayModeTokenTranslator::cPlayModeTokenTranslator()
    : cStringTokenTranslator()
{
    movieName = 0;
    moviePathname = 0;
    videoURL = 0;
    statusMessage = 0;
    gifName = 0;
    mayaExportName = 0;
    mayaExportPath = 0;
    mYear = 0;
    mMonth = 0;
    mDayOfMonth = 0;
    mTime = 0;
    mUnused54 = 0;
    movieNamePrefix = 0;
    mUnused5c = 0;
    pageCurrent = 0;
    pageCount = 0;
    photoCurrent = 0;
    photoCount = 0;
    bgPageCurrent = 0;
    bgPageCount = 0;
    animPageCurrent = 0;
    animPageCount = 0;
}

struct PropertyListG {
    bool GetBool(uint32_t id);    // 0x006a25a0
};
extern PropertyListG* gPropList;  // 0x015fd918
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int caseFold);   // 0x00932f30
void SetNumberString(double v, wchar_t* buf, int len, int flag);          // 0x00881ea0

// @ 0x00634640
static void FixSlashes(wstring16* s)
{
    char c = gPropList->GetBool(0x61b67b6) ? '/' : '\\';
    wchar_t sep = c;
    wchar_t* p = s->mpBegin;
    if (p != s->mpEnd) {
        do {
            if (*p == L'\\' || *p == L'/') {
                *p = sep;
                ++p;
                if (p == s->mpEnd)
                    break;
                while (*p == L'\\' || *p == L'/') {
                    memmove(p, p + 1, (uint32_t)(s->mpEnd - p) * 2);
                    s->mpEnd += -1;
                    if (p == s->mpEnd)
                        break;
                }
            } else {
                ++p;
            }
        } while (p != s->mpEnd);
    }
}

#define STR_CASE(h, field)                \
    case h:                               \
        if (field) {                      \
            *out = field;                 \
            return true;                  \
        }                                 \
        return false;
#define STR_CASE_FIX(h, field)            \
    case h:                               \
        if (field) {                      \
            *out = field;                 \
            FixSlashes(out);              \
            return true;                  \
        }                                 \
        return false;
#define NUM_CASE(h, field)                       \
    case h: {                                    \
        *out = L"";                              \
        wchar_t buf[64];                         \
        SetNumberString((double)(uint32_t)(field), buf, 0x40, 0); \
        buf[63] = 0;                             \
        *out = buf;                              \
        return true;                             \
    }

// @ 0x006346e0
bool cPlayModeTokenTranslator::TranslateToken(const wchar_t* token, wstring16* out)
{
    uint32_t h = FNV1_String16(token, 0x811c9dc5, 1);
    switch (h) {
        STR_CASE(0x15277637, movieName)
        STR_CASE_FIX(0x0ebf0c84, mayaExportPath)
        NUM_CASE(0x17629ad3, photoCount)
        NUM_CASE(0x1a6ef8ca, pageCurrent)
        NUM_CASE(0x1868fd54, bgPageCurrent)
        STR_CASE(0x227b55d7, mDayOfMonth)
        STR_CASE(0x248b7480, videoURL)
        NUM_CASE(0x3c5de426, animPageCurrent)
        STR_CASE(0x3fbf8399, mYear)
        STR_CASE(0x4dfeeba0, mayaExportName)
        STR_CASE(0x54798e40, mMonth)
        STR_CASE_FIX(0x5ae2d414, mUnused5c)
        NUM_CASE(0x7e083aa8, pageCount)
        STR_CASE(0x822d5473, statusMessage)
        STR_CASE(0x86110de6, mUnused54)
        NUM_CASE(0x8cdec7e6, bgPageCount)
        STR_CASE(0x8f2d29e5, movieNamePrefix)
        STR_CASE_FIX(0xaab49c2a, moviePathname)
        STR_CASE(0xd38ccf35, mTime)
        STR_CASE_FIX(0xd3f585c1, gifName)
        NUM_CASE(0xe6202d34, animPageCount)
        NUM_CASE(0xfa795731, photoCurrent)
    }
    return false;
}

// ---------------------------------------------------------------------------
// cSPPlayModeUI
// ---------------------------------------------------------------------------
// @ 0x00634b10
void cSPPlayModeUI::AttachWinProc()
{
    UIWin* w = mLayout.FindWindowByID(0x5b5ef50, true);
    if (w)
        w->SetTooltip(this);
    w = mLayout.FindWindowByID(0x5650568, true);
    if (w)
        w->SetTooltip(this);
}

// @ 0x00634c10
cSPPlayModeUI::cSPPlayModeUI()
    : mLayout(), mLayout2(), mFlag44(0), mFlag45(0), mTimer(5, 0)
{
    mField64 = 0;
    mField68 = 0;
}

// @ 0x00634c80
void cSPPlayModeUI::UpdateButtonEffects(int unused)
{
    UIWin* w = mLayout2.FindWindowByID(0x4cab570, true);
    if (w) {
        UIProc* p = w->QueryProc(0x8ed27e7a);
        if (p->GetState() & 2) {
            FxController* fx = mApp->FUN_00572400();
            if (fx)
                fx->SetScaleA(gBtnFx0);
        }
    }
    w = mLayout2.FindWindowByID(0x4cab571, true);
    if (w) {
        UIProc* p = w->QueryProc(0x8ed27e7a);
        if (p->GetState() & 2) {
            FxController* fx = mApp->FUN_00572400();
            if (fx)
                fx->SetScaleA(gBtnFx1);
        }
    }
    w = mLayout2.FindWindowByID(0x4cab56f, true);
    if (w) {
        UIProc* p = w->QueryProc(0x8ed27e7a);
        if (p->GetState() & 2) {
            FxController* fx = mApp->FUN_00572400();
            if (fx)
                fx->SetScaleB(gBtnFx2);
        }
    }
    w = mLayout2.FindWindowByID(0x4cab56e, true);
    if (w) {
        UIProc* p = w->QueryProc(0x8ed27e7a);
        if (p->GetState() & 2) {
            FxController* fx = mApp->FUN_00572400();
            if (fx)
                fx->SetScaleB(gBtnFx3);
        }
    }
}

// @ 0x00634dc0
UIWin* cSPPlayModeUI::FindPlayModeUIWindow(uint32_t id)
{
    UIObjVec* objs = mLayout.GetObjects();
    int n = (int)(objs->mpEnd - objs->mpBegin);
    for (int i = 0; i < n; ++i) {
        UIWin* obj = objs->mpBegin[i];
        if (obj) {
            UIWin* win = (UIWin*)obj->QueryProc(0xeeee8218);
            if (win) {
                if (win->GetID() == id)
                    return win;
                UIWin* r = win->FindChild(id, true);
                if (r)
                    return r;
            }
        }
    }
    return 0;
}

// @ 0x00634e40
UIWin* cSPPlayModeUI::FindEditorUIWindow(uint32_t id)
{
    cSPEditorUI* ed = mApp->mEditorUI;
    return ed->FindWindowByID(id);
}

// @ 0x00634e50
int cSPPlayModeUI::FUN_00634e50()
{
    return mApp->mObj98->Release();
}

// @ 0x00634e60
uint8_t cSPPlayModeUI::IsItemVisible(uint32_t id)
{
    uint8_t result = 0;
    UIWin* w = FindPlayModeUIWindow(id);
    if (w) {
        result = w->GetFlags();
        result &= 1;
    }
    return result;
}

// @ 0x00634e90
void cSPPlayModeUI::SetHighlight(uint32_t id, bool v)
{
    UIWin* w = FindPlayModeUIWindow(id);
    if (w)
        w->QueryProc(0x8ed27e7a)->SetFlags(8, v);
}

// @ 0x00634ec0
void cSPPlayModeUI::SetSelected(uint32_t id, bool v)
{
    UIWin* w = FindPlayModeUIWindow(id);
    if (w)
        w->QueryProc(0x8ed27e7a)->SetFlags(4, v);
}

// @ 0x00634ef0
void cSPPlayModeUI::SetEnabled(uint32_t id, bool v)
{
    UIWin* w = FindPlayModeUIWindow(id);
    if (w)
        w->SetFlag(2, v);
}

// @ 0x00634f20
void cSPPlayModeUI::SetEditorUIEnabled(uint32_t id, bool v)
{
    cSPEditorUI* ed = mApp->mEditorUI;
    UIWin* w = ed->FindWindowByID(id);
    if (w)
        w->SetFlag(2, v);
}

// @ 0x00634f50
void cSPPlayModeUI::SetHideOut(uint32_t id, bool v)
{
    UIWin* w;
    switch (id) {
    case 0x44594d8:
        w = FindPlayModeUIWindow(0x5ac71d9);
        if (w)
            w->SetFlag(1, v);
        break;
    case 0x3e831e4:
        w = FindPlayModeUIWindow(0x5ac71d8);
        if (w)
            w->SetFlag(1, v);
        break;
    case 0x445a468:
        w = FindPlayModeUIWindow(0x5ac71da);
        if (w)
            w->SetFlag(1, v);
        break;
    case 0x445ea18:
        w = FindPlayModeUIWindow(0x5ac71db);
        if (w)
            w->SetFlag(2, !v);
        break;
    }
}

// @ 0x00635010
void cSPPlayModeUI::SetEditorText(uint32_t id, const wchar_t** text)
{
    cSPEditorUI* ed = mApp->mEditorUI;
    UIWin* w = ed->FindWindowByID(id);
    w->SetText(*text);
}

// @ 0x00635290
void cSPPlayModeUI::RemoveTooltip(uint32_t id, void* tip)
{
    if (tip) {
        UIWin* w = FindPlayModeUIWindow(id);
        if (w)
            w->QueryProc(0x8ed27e7a)->GetParent()->RemoveTooltip(tip);
    }
}

// @ 0x006352d0
void cSPPlayModeUI::DoCommand103()
{
    mApp->mEditorUI->DoCommand(0x103);
}

// @ 0x006352f0
void cSPPlayModeUI::DoCommand102()
{
    mApp->mEditorUI->DoCommand(0x102);
}

// @ 0x00635310
void cSPPlayModeUI::SetPrompt(uint32_t v)
{
    UIWin* w = FindPlayModeUIWindow(0x5665f58);
    if (!w)
        w = mField68;
    if (w) {
        UIProc* p = w->QueryProc(0x8ed27e7a);
        if (p)
            p->SetState13(4, v);
    }
}

// @ 0x00635350
void cSPPlayModeUI::FUN_00635350(uint32_t a, uint32_t b)
{
    mApp->mEditorUI->FUN_005de690(a, b);
    mApp->mEditorUI->EnableUIButton(0x58b74e8, a);
}

// @ 0x00635380
void cSPPlayModeUI::ShowEditor()
{
    mApp->mEditorUI->Show();
}

// @ 0x00635390
void cSPPlayModeUI::ToggleNameAndDescribe(bool v)
{
    UIWin* w = mApp->mEditorUI->FindWindowByID(0x5a73030);
    if (w) {
        if (!(w->GetFlags() & 2) && !v)
            w->SetFlag(2, true);
        else
            w->SetFlag(2, false);
    }
}

// @ 0x006353e0
void cSPPlayModeUI::SetTagField(uint32_t v)
{
    cSPEditorNaming* n = mApp->mNaming;
    if (n)
        n->SetTagField(v);
}

// @ 0x00635400
struct WinMgrCurrent {};
void cSPPlayModeUI::SetSendEmailDialogVisibility(bool v)
{
    cSPEditorUI* ed = mApp->mEditorUI;
    ed->FindWindowByID(0x5b9cdb0)->SetFlag(1, v);
    UIWin* w = mApp->mEditorUI->FindWindowByID(0x3f67620);
    if (v) {
        FUN_0067cac0(0, 1)->FUN_0067c420();
        BeginModal(w, 0, 0);
        void* p = WindowManager()->GetCurrent();
        WinMgrOwner* o = p ? (WinMgrOwner*)((char*)p - 4) : 0;
        o->mHandler->FUN_00802a30(0);
    } else {
        FUN_0067cac0(1, 1)->FUN_0067c420();
        EndModal(w, 0, 0);
    }
}
