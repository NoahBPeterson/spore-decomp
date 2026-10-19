// slice s006373e0: cSPPlayModeUI shutdown + YouTube username/password + email/video helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /GS- (no /EHsc).
#include "../s00636320/s00636320.h"
#include <ctype.h>
#include <string.h>

cFourStrings::~cFourStrings() {}

// @ 0x006373E0
bool cSPPlayModeUI::Shutdown()
{
    if (mpEditor && mpEditor->mPaintPaletteObject)
        ((cSPEditorNaming*)mpEditor->mPaintPaletteObject)->ResetParentWin();

    mCameraControlsLayout.Shutdown(true);

    IWindow* w = mpEditor->mpEditorUI->FindWindowByID(0x4816f20);
    w->v55(mLayout.FindWindowByID(0xffffffff, true));

    w = mpEditor->mpEditorUI->FindWindowByID(0x5b9cdb0);
    w->SetFlag(1, 0);

    w = mpEditor->mpEditorUI->FindWindowByID(0x3f67620);
    BeginProfScope(1, 1)->End();
    EndModal(w, 0, 0);

    ResetSendEmailWindow();
    HideMovieSavedDialogCustom();
    HideYouTubeLoginDialog();

    mLayout.Shutdown(true);
    mbLayoutInit = false;
    return true;
}

// @ 0x006374B0
void cSPPlayModeUI::SetYTUsername(const eastl::string& s)
{
    eastl::string16 w = EA::ConvertToString16(s);
    const wchar_t* p = w.c_str();
    IWindow* win = FindPlayModeUIWindow(0x5650498);
    win->SetCaption(p);
}

// @ 0x00637510
void cSPPlayModeUI::SetYTPassword(const eastl::string& s)
{
    eastl::string16 w = EA::ConvertToString16(s);
    const wchar_t* p = w.c_str();
    IWindow* win = FindPlayModeUIWindow(0x5650500);
    win->SetCaption(p);
}

// @ 0x006377D0
void cSPPlayModeUI::GetEditorText(uint32_t id, eastl::string* out)
{
    cSPEditorUI* ui = mpEditor->mpEditorUI;
    IWindow* w = ui->FindWindowByID(id);
    out->sprintf("%ls", w->GetText());
}

// @ 0x00637800
void cSPPlayModeUI::GetYTUsername(eastl::string* out)
{
    IWindow* w = FindPlayModeUIWindow(0x5650498);
    out->sprintf("%ls", w->GetText());
}

// @ 0x00637830
void cSPPlayModeUI::GetYTPassword(eastl::string* out)
{
    IWindow* w = FindPlayModeUIWindow(0x5650500);
    out->sprintf("%ls", w->GetText());
}

namespace {
// Same 16-byte layout as the shared eastl::basic_string<char>; the string members reached here
// are plain thiscalls (ecx = &string) in the retail image.
struct StrOps {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mpAllocator;
    size_t find_last_of(const char* pSet, size_t nPos) const;   // 0x0091BEC0
    StrOps& erase(size_t nPos, size_t nCount);                  // 0x0061E200
};
}  // namespace

// 0x0062FF90: pointer to the last byte in (pLow,pHigh] equal to any byte of [pFirst,pLast);
// returns pLow when nothing matches.
const char* FindLastInSet(const char* pHigh, const char* pLow, const char* pFirst, const char* pLast);

// @ 0x006375E0  anonymous-namespace name validator; the string is taken by value and the
// callee frees it (MSVC x86: by-value class params are destroyed by the callee).
// NOTE: the frozen shared eastl::basic_string has a compiler-generated (shallow) copy ctor,
// while retail EASTL's is deep.  The callee-side destroy that the ABI emits is what retail
// does, so callers must hand this function an owning copy of the text.
char FindParentDir2(eastl::string name)
{
    char ok = 1;

    // Strip a trailing ".<letters>" extension.
    const size_t pos = ((StrOps*)&name)->find_last_of(".", (size_t)-1);
    if (pos == (size_t)-1 || (size_t)(name.mpEnd - name.mpBegin - 1) <= pos) {
        ok = 0;
    } else {
        const size_t nLen0 = (size_t)(name.mpEnd - name.mpBegin);
        size_t i = pos + 1;
        for (; i < nLen0; ++i)
            if (!isalpha((unsigned char)name.mpBegin[i])) { ok = 0; break; }
        if (ok) ((StrOps*)&name)->erase(pos, (size_t)-1);
    }

    // Position of the character just before the last '@'.
    const int nLen = (int)(name.mpEnd - name.mpBegin);
    int nUse = -1;
    if (nLen != 0) {
        const int nMinus = nLen - 1;
        const int nNone = -1;
        const int nHi = ((size_t)nMinus < (size_t)-1) ? nMinus : nNone;
        const char* pAt = FindLastInSet(name.mpBegin + nHi + 1, name.mpBegin, "@", "@" + 1);
        nUse = (pAt == name.mpBegin) ? -1 : (int)(pAt - name.mpBegin) - 1;
    }

    if (ok && nUse != -1 && nUse < nLen - 1) {
        size_t j = (size_t)(nUse + 1);
        for (; (int)j < nLen; ++j) {
            const char c = name.mpBegin[j];
            if (!isalnum((unsigned char)c) && c != '.' && c != '-') { ok = 0; break; }
        }
        if (ok) {
            const int nTail = nLen - nUse;
            const int nNoneB = -1;
            const int nSkip = ((size_t)nTail < (size_t)-1) ? nTail : nNoneB;
            char* pSrc = name.mpBegin + nUse + nSkip;
            char* pDst = name.mpBegin + nUse;
            if (pDst != pSrc) {
                memmove(pDst, pSrc, (size_t)(name.mpEnd - pSrc) + 1);
                name.mpEnd = pDst + (name.mpEnd - pSrc);
            }
            if (name.mpEnd != name.mpBegin) {
                const size_t nEnd = (size_t)(name.mpEnd - name.mpBegin);
                for (size_t k = 0; k < nEnd; ++k) {
                    const char c = name.mpBegin[k];
                    if (!isalnum((unsigned char)c) && c != '.' && c != '-' && c != '+' &&
                        c != '_' && c != '%') {
                        ok = 0;
                        break;
                    }
                }
            }
        }
    } else {
        ok = 0;
    }

    // The by-value parameter's dangling copy is destroyed by the callee (MSVC x86 ABI); the
    // automatic ~eastl::string() here inlines to DeallocateSelf() exactly like the retail tail.
    return ok;
}

// ---------------------------------------------------------------- send-email dialog helpers
// Every symbol below is an external dispatch target in the retail image (relocation-masked there).
void  BeginModal(IWindow* w, int a, int b);                            // 0x00809C30
void  FUN_008068D0(IWindow* w, int a, int b);                          // 0x008068D0
void  FUN_00807840(int a, int b, int c, void* p, int d, int e, int f); // 0x00807840

struct cPlayModeSub238 { void Setup(int a, int b); };                  // object at mpPlayMode+0x238
struct cSPPlayModeSubModePhoto {                                      // object at mpPlayMode+0x1e8
    void ShowErrorDialog(uint32_t id, const wchar_t* msg);
};
struct cSPPlayModeUIExtra {                                            // extra cSPPlayModeUI members
    void SetSendEmailDialogVisibility(int b);
};
struct IEmailField { void* mpValue; };                                 // result of IAuth::GetField()
struct IAuth {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual IEmailField* GetField();                                   // +0x30
};
IAuth* FUN_00607A60As();                                               // 0x00607A60

// 0x006B8F00 fills a string16 from the auth record field.
void FUN_006B8F00(void* pFieldValue, eastl::string16* pOut);

// A localised string handle (SP::cString): first member is a string16, plus a source-table key.
struct cString {
    eastl::string16 mpLocalString;                                      // +0
    uint32_t mKey;                                                      // +0x10
    uint32_t mTable;                                                    // +0x14
    void Load(uint32_t table, uint32_t key, const wchar_t* fallback);   // thiscall
    const wchar_t* c_str();                                             // thiscall
};

// string16 / string8 support reached through the retail CRT/Eastl.
struct IString16Ops {
    void* mpBegin; void* mpEnd; void* mpCapacity; void* mpAllocator;
    void RangeInitialize(const wchar_t* p);
};
namespace EA {
void ConvertToString8Impl(eastl::string* pOut, const wchar_t* pSrc, unsigned int length);  // 0x0093C440
}

// video-upload panel + message server virtual dispatches.
struct IVideoSource {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual const wchar_t** GetURL();               // +0x14
};
IVideoSource* FUN_0067DE40As();                                        // 0x0067DE40

struct IMessageServer {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void Send(uint32_t msgId, void* pData, int flags);  // +0x14
};
IMessageServer* MessageServer();                                       // 0x00809950

// @ 0x00637860  builds and shows the "tell a friend about your video" e-mail dialog.
void cSPPlayModeUI::ShowSendEmailDialog()
{
    BeginProfScope(0, 1)->End();

    cSPEditorUI* ui = mpEditor->mpEditorUI;

    // Reset the dialog and its picture panel.
    IWindow* w = ui->FindWindowByID(0x3ffb8cc);
    if (w) {
        ((cPlayModeSub238*)((char*)mpPlayMode + 0x238))->Setup(0, 0);
        FUN_008068D0(w, 0, 0xffffffff);
    }

    // Pre-fill the "your e-mail" field from the signed-in account.
    eastl::string16 yourEmail;
    IAuth* pAuth = FUN_00607A60As();
    FUN_006B8F00(pAuth->GetField()->mpValue, &yourEmail);
    w = ui->FindWindowByID(0x4581d50);
    w->SetCaption(yourEmail.mpBegin);

    // Localised captions for the four text fields.
    cString text;
    {
        w = ui->FindWindowByID(0x45adfc8);
        if (w) { text.Load(0x7518573e, 0x5b5b8c4, L"*Tell a friend about your video*"); w->SetCaption(text.c_str()); }
        w = ui->FindWindowByID(0x45ae078);
        if (w) { text.Load(0x7518573e, 0x45ad62f, L"*Your Email*"); w->SetCaption(text.c_str()); }
        w = ui->FindWindowByID(0x45ae090);
        if (w) { text.Load(0x7518573e, 0x45ad634, L"*Recipient's Email*"); w->SetCaption(text.c_str()); }
        w = ui->FindWindowByID(0x45ae0c0);
        if (w) { text.Load(0x7518573e, 0x45ad63a, L"*Your Message*"); w->SetCaption(text.c_str()); }
    }

    // Clear the flags on the option checkboxes.
    w = ui->FindWindowByID(0x447c4e8); if (w) w->SetFlag(1, 0);
    w = ui->FindWindowByID(0x447c040); if (w) w->SetFlag(1, 0);
    w = ui->FindWindowByID(0x447b968); if (w) w->SetFlag(1, 0);
    w = ui->FindWindowByID(0x447b980); if (w) w->SetFlag(1, 0);
    w = ui->FindWindowByID(0x3f6c990); if (w) w->SetFlag(1, 0);
    w = ui->FindWindowByID(0x3f67720); if (w) w->SetFlag(1, 0);
    w = ui->FindWindowByID(0x3f67720); if (w) w->SetFlag(2, 0);
    w = ui->FindWindowByID(0x56be960); if (w) w->SetFlag(1, 1);
    w = ui->FindWindowByID(0x56be960); if (w) w->SetFlag(2, 1);

    // Default message text.
    eastl::string16 caption;
    {
        cString msg;
        msg.Load(0x7518573e, 0x56bcdca, L"*Check out my video!*");
        ((IString16Ops*)&caption)->RangeInitialize(msg.c_str());
        w = ui->FindWindowByID(0x4581d90);
        w->SetCaption(caption.mpBegin);
    }

    // Lay the dialog out at the default position.
    IWindow* dlg = ui->FindWindowByID(0x3ffb8cc);
    if (dlg) {
        FUN_00807840(0x2f7d0004, 0x40607300, 0xb563455a, &caption, 0, 0xffffffff, 0xffffffff);
        FUN_008068D0(dlg, 0, 0);
    }

    // Show and enter the modal dialog.
    w = ui->FindWindowByID(0x3f67620);
    if (w) {
        w->SetFlag(1, 1);
        ((cSPPlayModeUIExtra*)this)->SetSendEmailDialogVisibility(1);
        BeginModal(w, 0, 0);
        BeginProfScope(0, 1)->End();
    }
}

// @ 0x00637C90  validates the video-URL dialog fields and submits them to the message server.
// NOTE: the retail function returns a char in AL; the frozen header declares it void.
void cSPPlayModeUI::SendVideoURLInfoToServer()
{
    cSPEditorUI* ui = mpEditor->mpEditorUI;
    cFourStrings strings;      // strings.a/.b/.c/.d hold the sender/recipient/message/url text
    eastl::string field;       // scratch text read back from the edit controls
    bool bFailed = false;

    // --- sender address -------------------------------------------------
    IWindow* w = ui->FindWindowByID(0x4581d50);
    field.sprintf("%ls", w->GetText());
    if (field.mpEnd == field.mpBegin) {
    show_bad_sender:
        w = ui->FindWindowByID(0x5b9cdb0);
        w->SetFlag(1, 0);
        IWindow* dlg = ui->FindWindowByID(0x3f67620);
        BeginProfScope(1, 1)->End();
        EndModal(dlg, 0, 0);
        ((cSPPlayModeSubModePhoto*)((char*)mpPlayMode + 0x1e8))
            ->ShowErrorDialog(0x4585f1f, L"*My email invalid*");
        bFailed = true;
    } else {
        eastl::string copy(field);
        if (!FindParentDir2(copy)) goto show_bad_sender;
    }

    strings.a.sprintf("%s", field.mpBegin);

    // --- recipient address ----------------------------------------------
    w = ui->FindWindowByID(0x4581d78);
    field.sprintf("%ls", w->GetText());
    if (!bFailed) {
        if (field.mpEnd != field.mpBegin) {
            eastl::string copy(field);
            if (FindParentDir2(copy)) goto recipient_ok;
        }
        w = ui->FindWindowByID(0x5b9cdb0);
        w->SetFlag(1, 0);
        IWindow* dlg = ui->FindWindowByID(0x3f67620);
        BeginProfScope(1, 1)->End();
        EndModal(dlg, 0, 0);
        ((cSPPlayModeSubModePhoto*)((char*)mpPlayMode + 0x1e8))
            ->ShowErrorDialog(0x4585f49, L"*Recipients email invalid*");
        bFailed = true;
    }

recipient_ok:
    strings.b.sprintf("%s", field.mpBegin);

    // --- message body ---------------------------------------------------
    w = ui->FindWindowByID(0x4581d90);
    field.sprintf("%ls", w->GetText());
    strings.c.sprintf("%s", field.mpBegin);

    // --- video URL ------------------------------------------------------
    const wchar_t* pUrl = *FUN_0067DE40As()->GetURL();
    eastl::string url8;
    EA::ConvertToString8Impl(&url8, pUrl, (unsigned int)-1);
    strings.d.sprintf("%s", url8.mpBegin);

    // --- submit ---------------------------------------------------------
    if (!bFailed)
        MessageServer()->Send(0x56cd8c4, &strings.a, 0);

    // `strings` and the scratch string are destroyed here (cFourStrings dtor 0x00637570).
}

