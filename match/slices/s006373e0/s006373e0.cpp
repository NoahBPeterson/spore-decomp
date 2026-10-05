// slice s006373e0: cSPPlayModeUI shutdown + YouTube username/password + email/video helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /GS- (no /EHsc).
#include "../s00636320/s00636320.h"

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

// @ 0x006375E0  PARTIAL: anonymous-namespace filename/parent-dir validator.
char FindParentDir2(int a, int b, int c)
{
    (void)a; (void)b; (void)c;
    return 0;
}

// @ 0x00637860  PARTIAL: builds the send-email dialog.
void cSPPlayModeUI::ShowSendEmailDialog()
{
}

// @ 0x00637C90  PARTIAL: validates and submits the video URL info.
void cSPPlayModeUI::SendVideoURLInfoToServer()
{
}
