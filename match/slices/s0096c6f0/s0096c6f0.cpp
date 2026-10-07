// Slice s0096c6f0 - EA::UTFWinControls::WinDialog::Refresh (0x96c6f0, 3060 bytes).
//
// Lays out a UTFWin dialog: queries the dialog drawable for the size of its ten frame
// components, computes the component rectangles (client, title bar, four edges, four corners),
// creates or disposes the close button and the title text, positions them, computes the client
// area and the minimum size, and finally clamps and applies the window size.
//
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (UTFWin region, see s0096e3a0).
// Retail layout = 2008 PDB layout of WinDialog shifted by +0x14 (Window grew by 0x14 bytes).

#include "types.h"

#define PV(n) virtual void pv##n()

namespace EA {

struct RectF {
    float x1, y1, x2, y2;
    RectF() {}
    RectF(float l, float t, float r, float b) : x1(l), y1(t), x2(r), y2(b) {}
    RectF(const RectF& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) {}
    float Width() const  { return x2 - x1; }
    float Height() const { return y2 - y1; }
};
struct Vec2 {
    float x, y;
    Vec2() {}
    Vec2(float fx, float fy) : x(fx), y(fy) {}
    Vec2& operator=(const Vec2& v) { x = v.x; y = v.y; return *this; }
};

template <class T>
struct AutoRefCount {
    T* mpObject;

    AutoRefCount& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

namespace UTFWin {

struct IWindow;

// UTFWin message (only the fields this function sets).
struct Message {
    IWindow* source;        // +0x00
    int      field_04;      // +0x04
    int      eventType;     // +0x08
    int      param0;        // +0x0c
    int      param1;        // +0x10
    int      param2;        // +0x14
    void*    pData;         // +0x18
};

struct IWindowManager {
    PV(0); PV(1); PV(2); PV(3);
    virtual bool SendMsg(IWindow* pTarget, IWindow* pSource, Message* pMsg, int flags); // +0x10
};

struct IWindow {
    PV(0); PV(1); PV(2); PV(3); PV(4);
    virtual IWindowManager* GetWindowManager();                       // +0x14
    PV(6); PV(7); PV(8); PV(9); PV(10); PV(11); PV(12); PV(13);
    virtual const RectF& GetRealArea();                               // +0x38
    PV(15); PV(16); PV(17); PV(18); PV(19);
    virtual void SetControlID(uint32_t id);                           // +0x50
    PV(21); PV(22); PV(23);
    virtual void SetArea(const RectF& area);                          // +0x60
    PV(25);
    virtual void SetSize(float w, float h);                           // +0x68
    PV(27); PV(28); PV(29); PV(30);
    virtual void SetFlag(uint32_t flag, bool value);                  // +0x7c
    virtual void SetCaption(const wchar_t* caption);                  // +0x80
    virtual void SetTextFontID(uint32_t id);                          // +0x84
    PV(34); PV(35);
    virtual int  Invalidate();                                        // +0x90
    PV(37); PV(38); PV(39); PV(40); PV(41); PV(42); PV(43); PV(44); PV(45); PV(46); PV(47);
    PV(48); PV(49); PV(50); PV(51); PV(52); PV(53);
    virtual void AddWindow(IWindow* pWindow);                         // +0xd8
    PV(55);
    virtual void DisposeWindowFamily(IWindow* pWindow);               // +0xe0
};

struct IDrawable {
    virtual int   AddRef();
    virtual int   Release();
    PV(2);
    virtual void* Cast(uint32_t type);                                // +0x0c
    PV(4); PV(5);
    virtual bool  GetDimensions(Vec2* dst, int state, int index);     // +0x18
};

} // namespace UTFWin

namespace UTFWinControls {

using UTFWin::IWindow;

struct IButtonDrawable { virtual int AddRef(); virtual int Release(); };

struct IWinButton {
    virtual int   AddRef();
    virtual int   Release();
    PV(2);
    virtual void* Cast(uint32_t type);                                // +0x0c
    virtual IWindow* ToWindow();                                      // +0x10
    PV(5); PV(6); PV(7); PV(8); PV(9); PV(10); PV(11); PV(12); PV(13); PV(14); PV(15);
    PV(16); PV(17); PV(18); PV(19); PV(20); PV(21); PV(22); PV(23);
    virtual void SetButtonDrawable(IButtonDrawable* pDrawable);       // +0x60
};

struct IWinText {
    virtual int   AddRef();
    virtual int   Release();
    PV(2); PV(3);
    virtual IWindow* ToWindow();                                      // +0x10
    PV(5); PV(6); PV(7); PV(8); PV(9);
    virtual void SetTextColor(uint32_t color);                        // +0x28
    PV(11); PV(12); PV(13);
    virtual void SetTextBorders(float l, float t, float r, float b);  // +0x38
};

namespace WinButton { IWinButton* CreateDefault(int type, int a, int b); }      // 0x9671c0
namespace WinText   { IWinText*   CreateDefault(int a, uint32_t styleId); }     // 0x989130

struct WinDialogBase {                                                // primary vtable
    PV(0);  PV(1);  PV(2);  PV(3);  PV(4);  PV(5);  PV(6);  PV(7);  PV(8);  PV(9);
    PV(10); PV(11); PV(12); PV(13); PV(14); PV(15); PV(16); PV(17); PV(18); PV(19);
    PV(20); PV(21); PV(22); PV(23); PV(24); PV(25); PV(26); PV(27); PV(28); PV(29);
    PV(30); PV(31); PV(32); PV(33); PV(34); PV(35); PV(36); PV(37); PV(38); PV(39);
    virtual void UpdateLayout(int a);                                 // +0xa0
};

enum {
    kDialogTitleText   = 0x04,
    kDialogTitleBar    = 0x08,
    kDialogCloseButton = 0x10,
    kDialogComponents  = 0x20
};

enum {
    kComponentClient = 0, kComponentTitle, kComponentLeft, kComponentRight, kComponentTop,
    kComponentBottom, kComponentTopLeft, kComponentTopRight, kComponentBottomLeft,
    kComponentBottomRight, kComponentCount
};

class WinDialog : public WinDialogBase, public IWindow {
public:
    bool Refresh();

    uint32_t                     pad08[(0x88 - 0x08) / 4];
    RectF                        mArea;                    // +0x88
    uint32_t                     pad98[(0x1e0 - 0x98) / 4];
    UTFWin::IDrawable*           mpDrawable;               // +0x1e0
    uint32_t                     pad1e4[(0x210 - 0x1e4) / 4];
    bool                         mbRefresh;                // +0x210
    uint32_t                     mnDialogFlags;            // +0x214
    uint32_t                     mnSelectedComponent;      // +0x218
    float                        mnCursorOffsetX;          // +0x21c
    float                        mnCursorOffsetY;          // +0x220
    AutoRefCount<IButtonDrawable> mpCloseButtonDrawable;   // +0x224
    AutoRefCount<IWinButton>     mpCloseButton;            // +0x228
    AutoRefCount<IWinText>       mpTitleText;              // +0x22c
    RectF                        mrComponentArea[10];      // +0x230
    RectF                        mrClientArea;             // +0x2d0
    RectF                        mfClientAreaBorder;       // +0x2e0
    RectF                        mfTitleTextBorder;        // +0x2f0
    RectF                        mfCloseButtonBorder;      // +0x300
    float                        mfMaxW;                   // +0x310
    float                        mfMaxH;                   // +0x314
    float                        mfMinW;                   // +0x318
    float                        mfMinH;                   // +0x31c
    uint32_t                     mnTitleTextColor;         // +0x320
    uint32_t                     mnTitleTextStyle;         // +0x324
    const wchar_t*               msTitleText;              // +0x328 (eastl::basic_string mpBegin)
};

// @ 0x0096c6f0
bool WinDialog::Refresh()
{
    if (!mbRefresh || !mpDrawable)
        return false;

    UpdateLayout(0);

    const bool bDialogDrawable = (mpDrawable ? mpDrawable->Cast(0x6f0c6ff6) : 0) != 0;

    Vec2 size[kComponentCount];
    if (bDialogDrawable) {
        for (unsigned i = 0; i < kComponentCount; ++i) {
            Vec2 dim(0.0f, 0.0f);
            if (!mpDrawable->GetDimensions(&dim, 0, i)) {
                switch (i) {
                    case kComponentClient:
                        dim.x = mArea.x2 - mArea.x1;
                        dim.y = mArea.y2 - mArea.y1;
                        break;
                    case kComponentTitle:
                        dim.y = 20.0f;
                        break;
                }
            }
            size[i] = dim;
        }
    } else {
        for (unsigned i = 0; i < kComponentCount; ++i) {
            size[i].x = 0.0f;
            size[i].y = 0.0f;
        }
        size[kComponentTitle].y = 20.0f;
    }

    const uint32_t flags = mnDialogFlags;
    if ((flags & kDialogComponents) && bDialogDrawable) {
        RectF* const r = mrComponentArea;

        r[kComponentLeft].x1 = 0.0f;
        r[kComponentLeft].x2 = size[kComponentLeft].x;
        r[kComponentLeft].y1 = 0.0f;
        r[kComponentLeft].y2 = mArea.y2 - mArea.y1;

        r[kComponentRight].x1 = (mArea.x2 - mArea.x1) - size[kComponentRight].x;
        r[kComponentRight].x2 = r[kComponentRight].x1 + size[kComponentRight].x;
        r[kComponentRight].y1 = 0.0f;
        r[kComponentRight].y2 = mArea.y2 - mArea.y1;

        r[kComponentTop].x1 = 0.0f;
        r[kComponentTop].x2 = mArea.x2 - mArea.x1;
        r[kComponentTop].y1 = 0.0f;
        r[kComponentTop].y2 = size[kComponentTop].y;

        r[kComponentBottom].x1 = 0.0f;
        r[kComponentBottom].x2 = mArea.x2 - mArea.x1;
        r[kComponentBottom].y1 = (mArea.y2 - mArea.y1) - size[kComponentBottom].y;
        r[kComponentBottom].y2 = r[kComponentBottom].y1 + size[kComponentBottom].y;

        r[kComponentTopLeft].x1 = 0.0f;
        r[kComponentTopLeft].x2 = size[kComponentTopLeft].x;
        r[kComponentTopLeft].y1 = 0.0f;
        r[kComponentTopLeft].y2 = size[kComponentTopLeft].y;

        r[kComponentTopRight].x1 = (mArea.x2 - mArea.x1) - size[kComponentTopRight].x;
        r[kComponentTopRight].x2 = mArea.x2 - mArea.x1;
        r[kComponentTopRight].y1 = 0.0f;
        r[kComponentTopRight].y2 = size[kComponentTopRight].y;

        r[kComponentBottomLeft].x1 = 0.0f;
        r[kComponentBottomLeft].x2 = size[kComponentBottomLeft].x;
        r[kComponentBottomLeft].y1 = (mArea.y2 - mArea.y1) - size[kComponentBottomLeft].y;
        r[kComponentBottomLeft].y2 = mArea.y2 - mArea.y1;

        r[kComponentBottomRight].x1 = (mArea.x2 - mArea.x1) - size[kComponentBottomRight].x;
        r[kComponentBottomRight].x2 = mArea.x2 - mArea.x1;
        r[kComponentBottomRight].y1 = (mArea.y2 - mArea.y1) - size[kComponentBottomRight].y;
        r[kComponentBottomRight].y2 = mArea.y2 - mArea.y1;

        float top = size[kComponentTop].y;
        if (flags & kDialogTitleBar) {
            r[kComponentTitle].y1 = top;
            top += size[kComponentTitle].y;
            r[kComponentTitle].x2 = r[kComponentRight].x1;
            r[kComponentTitle].x1 = size[kComponentLeft].x;
            r[kComponentTitle].y2 = top;
        }
        r[kComponentClient].y1 = top;
        r[kComponentClient].x2 = r[kComponentRight].x1;
        r[kComponentClient].x1 = size[kComponentLeft].x;
        r[kComponentClient].y2 = r[kComponentBottom].y1;
    } else {
        RectF* const r = mrComponentArea;
        if (flags & kDialogTitleBar) {
            r[kComponentTitle].x1 = 0.0f;
            r[kComponentTitle].x2 = mArea.x2 - mArea.x1;
            r[kComponentTitle].y1 = 0.0f;
            r[kComponentTitle].y2 = size[kComponentTitle].y;
        }
        if ((flags & kDialogTitleBar) && bDialogDrawable)
            r[kComponentClient].y1 = r[kComponentTitle].y2;
        else
            r[kComponentClient].y1 = 0.0f;
        r[kComponentClient].x1 = 0.0f;
        r[kComponentClient].x2 = mArea.x2 - mArea.x1;
        r[kComponentClient].y2 = mArea.y2 - mArea.y1;
    }

    // Close button.
    if ((flags & kDialogCloseButton) && (flags & kDialogTitleBar)) {
        if (!mpCloseButton) {
            mpCloseButton = WinButton::CreateDefault(1, 0, 0);
            if (mpCloseButton) {
                if (mpCloseButtonDrawable)
                    mpCloseButton->SetButtonDrawable(mpCloseButtonDrawable);
                mpCloseButton->ToWindow()->SetControlID(0x4f0dd487);
                mpCloseButton->ToWindow()->SetFlag(0x200, true);
                mpCloseButton->ToWindow()->SetArea(RectF(0.0f, 0.0f, 14.0f, 14.0f));
                static_cast<IWindow*>(this)->AddWindow(mpCloseButton->ToWindow());
            }
        }
    } else if (mpCloseButton) {
        static_cast<IWindow*>(this)->DisposeWindowFamily(mpCloseButton->ToWindow());
        mpCloseButton = 0;
    }

    // Title text.
    if ((mnDialogFlags & kDialogTitleText) && (mnDialogFlags & kDialogTitleBar)) {
        if (!mpTitleText) {
            mpTitleText = WinText::CreateDefault(-1, 0xf170dc1);
            if (mpTitleText) {
                mpTitleText->ToWindow()->SetControlID(0xef3d61c5);
                mpTitleText->ToWindow()->SetFlag(0x200, true);
                mpTitleText->ToWindow()->SetFlag(0x10, true);
                static_cast<IWindow*>(this)->AddWindow(mpTitleText->ToWindow());
            }
        }
    } else if (mpTitleText) {
        static_cast<IWindow*>(this)->DisposeWindowFamily(mpTitleText->ToWindow());
        mpTitleText = 0;
    }

    if (mpCloseButton) {
        if (mpCloseButtonDrawable)
            mpCloseButton->SetButtonDrawable(mpCloseButtonDrawable);

        float buttonW = mpCloseButton->ToWindow()->GetRealArea().Width();
        float buttonH = mpCloseButton->ToWindow()->GetRealArea().Height();

        if (mpCloseButton) {
            IWindow* pWindow = (IWindow*)mpCloseButton->Cast(0xeeee8218);
            if (pWindow) {
                Vec2 preferred;
                UTFWin::Message msg;
                msg.pData     = &preferred;
                msg.eventType = 0x16;
                msg.param0    = 0;
                if (pWindow->GetWindowManager() &&
                    pWindow->GetWindowManager()->SendMsg(pWindow, pWindow, &msg, 0)) {
                    buttonW = preferred.x;
                    buttonH = preferred.y;
                }
            }
        }

        const RectF& title = mrComponentArea[kComponentTitle];
        RectF area;
        // Note: the original uses the button height for x and the width for y.
        area.x1 = (title.x2 - mfCloseButtonBorder.x2) - buttonH;
        area.y1 = (title.Height() - buttonW) * 0.5f + mrComponentArea[kComponentTitle].y1;
        area.x2 = area.x1 + buttonH;
        area.y2 = area.y1 + buttonW;
        mpCloseButton->ToWindow()->SetArea(area);
    }

    if (mpTitleText) {
        mpTitleText->ToWindow()->SetCaption(msTitleText);
        mpTitleText->ToWindow()->SetTextFontID(mnTitleTextStyle);
        mpTitleText->SetTextColor(mnTitleTextColor);
        mpTitleText->SetTextBorders(mfTitleTextBorder.x1, mfTitleTextBorder.y1,
                                    mfTitleTextBorder.x2, mfTitleTextBorder.y2);

        RectF area = mrComponentArea[kComponentTitle];
        if (mpCloseButton)
            area.x2 = mpCloseButton->ToWindow()->GetRealArea().x1 - mfCloseButtonBorder.x1;
        mpTitleText->ToWindow()->SetArea(area);
    }

    // Client area.
    const uint32_t flags2 = mnDialogFlags;
    if ((flags2 & kDialogComponents) && bDialogDrawable) {
        mrClientArea.x1 = mrComponentArea[kComponentLeft].x2;
        mrClientArea.x2 = mrComponentArea[kComponentRight].x1;
        if (flags2 & kDialogTitleBar)
            mrClientArea.y1 = mrComponentArea[kComponentTitle].y2;
        else
            mrClientArea.y1 = mrComponentArea[kComponentTop].y2;
        mrClientArea.y2 = mrComponentArea[kComponentBottom].y1;
    } else {
        if ((flags2 & kDialogTitleBar) && bDialogDrawable)
            mrClientArea.y1 = mrComponentArea[kComponentTitle].y2;
        else
            mrClientArea.y1 = 0.0f;
        mrClientArea.x1 = 0.0f;
        mrClientArea.x2 = mArea.Width();
        mrClientArea.y2 = mArea.Height();
    }
    mrClientArea.x1 += mfClientAreaBorder.x1;
    mrClientArea.y1 += mfClientAreaBorder.y1;
    mrClientArea.x2 -= mfClientAreaBorder.x2;
    mrClientArea.y2 -= mfClientAreaBorder.y2;

    // Minimum size.
    float minW = 0.0f;
    float minH = 0.0f;
    const RectF* const r = mrComponentArea;
    if ((flags2 & kDialogComponents) && bDialogDrawable) {
        const float topH = r[kComponentTop].y2 - r[kComponentTop].y1;
        if (flags2 & kDialogTitleBar) {
            minW = r[kComponentLeft].Width();
            minW += r[kComponentRight].Width();
            minH = (r[kComponentBottom].Height() + topH) + r[kComponentTitle].Height();
        } else {
            minW = (r[kComponentRight].x2 - r[kComponentRight].x1) + (r[kComponentLeft].x2 - r[kComponentLeft].x1);
            minH = (r[kComponentBottom].y2 - r[kComponentBottom].y1) + topH;
        }
    } else if ((flags2 & kDialogTitleBar) && bDialogDrawable) {
        minH = r[kComponentTitle].y2 - r[kComponentTitle].y1;
    }

    IWinButton* const pCloseButton = mpCloseButton;
    if (pCloseButton && bDialogDrawable) {
        const RectF& a = pCloseButton->ToWindow()->GetRealArea();
        minW = (((a.x2 - a.x1) + mfCloseButtonBorder.x2) + mfCloseButtonBorder.x1) + minW;
    }

    if (minW > mfMinW)
        mfMinW = minW;
    if (minH > mfMinH)
        mfMinH = minH;

    float w = mArea.x2 - mArea.x1;
    float h = mArea.y2 - mArea.y1;
    if (mfMinW > w)
        w = mfMinW;
    if (w > mfMaxW)
        w = mfMaxW;
    if (mfMinH > h)
        h = mfMinH;
    if (h > mfMaxH)
        h = mfMaxH;

    IWindow* const pWindow = static_cast<IWindow*>(this);
    pWindow->SetSize(w, h);
    pWindow->Invalidate();
    return true;
}

} // namespace UTFWinControls
} // namespace EA
