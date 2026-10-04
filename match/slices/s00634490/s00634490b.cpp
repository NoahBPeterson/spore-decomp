// SSE-compiled part of the play-mode UI module (/O2 /MD /Gy /TP /GS- /arch:SSE):
// a rectangle intersection and the two tooltip helpers (they keep float defaults on the stack).

#include "s00634490_ui.h"

struct RectF {
    float x0, y0, x1, y1;
    bool Intersect(const RectF& a, const RectF& b);
};

// @ 0x00634b60
bool RectF::Intersect(const RectF& a, const RectF& b)
{
    if (b.x0 >= a.x1 || a.x0 >= b.x1 || b.y0 >= a.y1 || a.y0 >= b.y1) {
        y0 = 0.0f;
        x1 = 0.0f;
        x0 = 0.0f;
        y1 = 0.0f;
        return false;
    }
    x0 = (a.x0 > b.x0) ? a.x0 : b.x0;
    y0 = (a.y0 > b.y0) ? a.y0 : b.y0;
    x1 = (a.x1 < b.x1) ? a.x1 : b.x1;
    y1 = (a.y1 < b.y1) ? a.y1 : b.y1;
    return true;
}

// @ 0x00635040
void cSPPlayModeUI::ShowToolTip(uint32_t id, uint32_t a2, uint32_t a3, cSPUITooltipWinProc* existing, float* pos)
{
    float defaults[2];
    defaults[0] = gTipDefault0;
    defaults[1] = gTipDefault1;
    UIWin* win = FindPlayModeUIWindow(id);
    if (win) {
        cString str;
        str.Load(0x7518573e, a2, a3);
        UIProc* proc = win->QueryProc(0x8ed27e7a);
        if (!pos)
            pos = defaults;
        cSPUITooltipWinProc* tip = existing;
        cSPUITooltipWinProc* result = 0;
        if (!tip) {
            void* mem = FUN_009512d0(0x68, 4, "UI/Tooltip", FUN_009512c0());
            if (mem) {
                tip = new (mem) cSPUITooltipWinProc(L"Tooltips", 0x3754e6c, str.Format(pos, 0, (const wchar_t*)0x13fe714, 0));
                if (tip) {
                    tip->AddRef();
                    result = tip;
                }
            }
        } else {
            tip->SetText(str.Format2(-1, 1));
            tip->AddRef();
            result = tip;
        }
        proc->GetParent()->SetTooltip(result);
        if (result)
            result->Release();
    }
}

// @ 0x00635160
void cSPPlayModeUI::ShowEditorUIToolTip(uint32_t id, uint32_t a2, uint32_t a3, cSPUITooltipWinProc* existing, float* pos)
{
    float defaults[2];
    defaults[0] = gTipDefault0;
    defaults[1] = gTipDefault1;
    cSPEditorUI* ed = mApp->mEditorUI;
    UIWin* win = ed->FindWindowByID(id);
    if (win) {
        cString str;
        str.Load(0x7518573e, a2, a3);
        UIProc* proc = win->QueryProc(0x8ed27e7a);
        if (!pos)
            pos = defaults;
        cSPUITooltipWinProc* tip = existing;
        cSPUITooltipWinProc* result = 0;
        if (!tip) {
            void* mem = FUN_009512d0(0x68, 4, "UI/Tooltip", FUN_009512c0());
            if (mem) {
                tip = new (mem) cSPUITooltipWinProc(L"Tooltips", 0x3754e6c, str.Format(pos, 0, (const wchar_t*)0x13fe714, 0));
                if (tip) {
                    tip->AddRef();
                    result = tip;
                }
            }
        } else {
            tip->SetText(str.Format2(-1, 1));
            tip->AddRef();
            result = tip;
        }
        proc->GetParent()->SetTooltip(result);
        if (result)
            result->Release();
    }
}
