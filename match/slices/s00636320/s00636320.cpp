// slice s00636320: cSPPlayModeUI photo-viewer button + movie-saved dialog.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /GS- (no /EHsc).
#include "s00636320.h"

// @ 0x00636320
void cSPPlayModeUI::EnablePhotoViewerButton(bool b)
{
    mpEditor->mpEditorUI->EnableUIButton(0x445ea50, b);

    IWindow* w = FindPlayModeUIWindow(0x445ea18);
    if (w && (w->v10() & 2)) {
        w = FindPlayModeUIWindow(0x5ac71db);
        if (w)
            w->SetFlag(2, 1);

        w = FindPlayModeUIWindow(0x445ea50);
        if (w)
            w->v03(0x8ed27e7a)->SetMode(4, 0);

        w = FindPlayModeUIWindow(0x4463e78);
        if (w)
            w->SetFlag(1, 0);

        w = mpEditor->mpEditorUI->FindWindowByID(0x447c040);
        if (w)
            w->SetFlag(1, 0);

        w = mpEditor->mpEditorUI->FindWindowByID(0x447c4e8);
        if (w)
            w->SetFlag(1, 0);

        w = FindPlayModeUIWindow(0x40eb500);
        if (w)
            w->SetFlag(1, 0);

        w = FindPlayModeUIWindow(0x40eb518);
        if (w)
            w->SetFlag(1, 0);

        w = FindPlayModeUIWindow(0x40eb7e8);
        if (w)
            w->SetFlag(1, 0);

        w = FindPlayModeUIWindow(0x40eb7f8);
        if (w)
            w->SetFlag(1, 0);

        w = FindPlayModeUIWindow(0x40eb818);
        if (w)
            w->SetFlag(1, 0);
    }
}

// @ 0x006364A0
void cSPPlayModeUI::HideMovieSavedDialogCustom()
{
    BeginProfScope(1, 1)->End();

    if (mpMovieSavedDialog)
        EndModal(mpMovieSavedDialog, 0, 0);

    IWindow* w = FindPlayModeUIWindow(0x5b60540);
    if (w && mpMovieSavedDialog) {
        IOther* o = mpMovieSavedDialog->GetOther();
        o->Attach(mpMovieSavedDialog);
        w->v54(mpMovieSavedDialog);
    }

    if (mpMovieSavedDialog) {
        IWindow* old = mpMovieSavedDialog;
        mpMovieSavedDialog = 0;
        old->Release();
    }

    w = FindPlayModeUIWindow(0x5b5ef50);
    if (w)
        w->SetFlag(1, 0);

    w = FindPlayModeUIWindow(0x5b60540);
    if (w)
        w->SetFlag(1, 0);
}
