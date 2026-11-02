// src/game/UTFSpore_Win32/MessageBox.cpp -- migrated from slice(s) s0097e1f0, s0096d2f0, s01300280, s0097f390 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/MessageBox.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinControls/IWinButton.h"
#include "EA/UTFWinControls/IWinText.h"
#include "EA/UTFWin/IWindow.h"

// unnamed retail callees and globals (address in the comment)
extern const wchar_t g_OK[];        // 0x014439bc
extern const wchar_t g_Yes[];       // 0x014439b4
extern const wchar_t g_No[];        // 0x014439ac
extern const wchar_t g_Cancel[];    // 0x0144399c
#include <intrin.h>
#include "EA/UTFWinControls/WinGrid.h"
#include <math.h>

// ---- items of slice s0097f390 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct Rect {
    float x1, y1, x2, y2;
    Rect(float a, float b, float c, float d) : x1(a), y1(b), x2(c), y2(d) {}
};
struct IWindowManager;
struct IWindow;
struct Msg {                    // UTFWin::Message
    IWindow* source;            // +0
    int      type;              // +4
    int      eventType;         // +8
    int      pad0c, pad10;
    float*   out;               // +0x14
};
struct IWindowManager {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual bool SendMsg(IWindow* src, IWindow* dst, const Msg* msg, bool inheritable);   // +0x10
};
struct IWindow {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10();
    virtual IWindowManager* GetWindowManager();            // +0x14
    virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24();
    virtual uint GetFlags();                               // +0x28
    virtual void s2c(); virtual void s30(); virtual void s34();
    virtual const float* GetRealArea();                    // +0x38
    virtual void s3c(); virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c();
    virtual void SetArea(const Rect* r);                   // +0x60
    virtual void s64(); virtual void s68(); virtual void s6c(); virtual void s70(); virtual void s74();
    virtual void s78();
    virtual void SetFlag(uint flag, bool value);           // +0x7c
    virtual void SetCaption(const wchar_t* text);          // +0x80
    virtual void SetTextFontID(uint style);                // +0x84
    virtual void s88(); virtual void s8c(); virtual void s90(); virtual void s94(); virtual void s98();
    virtual void s9c(); virtual void sa0(); virtual void sa4(); virtual void sa8(); virtual void sac();
    virtual void sb0(); virtual void sb4(); virtual void sb8(); virtual void sbc(); virtual void sc0();
    virtual void sc4(); virtual void sc8(); virtual void scc(); virtual void sd0(); virtual void sd4();
    virtual void AddWindow(IWindow* w);                    // +0xd8
};
struct IWinButton {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual IWindow* GetWindow();                          // +0x10
    virtual void s14(); virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24();
    virtual void s28(); virtual void s2c(); virtual void s30(); virtual void s34(); virtual void s38();
    virtual void s3c(); virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50();
    virtual void SetBorder(float l, float t, float r, float b);   // +0x54
    virtual void s58(); virtual void s5c();
    virtual void SetDrawable(void* d);                     // +0x60
};
struct IWinText {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual IWindow* GetWindow();                          // +0x10
    virtual void s14(); virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24();
    virtual void SetTextColor(uint c);                     // +0x28
    virtual void s2c(); virtual void s30(); virtual void s34();
    virtual void SetBorder(float l, float t, float r, float b);   // +0x38
};
struct IMsgBoxSub {                                        // IWinMessageBox sub-object at +0x338
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c(); virtual void s10();
    virtual void s14(); virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24();
    virtual void s28(); virtual void s2c(); virtual void s30(); virtual void s34(); virtual void s38();
    virtual void s3c(); virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c(); virtual void s60();
    virtual void s64(); virtual void s68(); virtual void s6c(); virtual void s70(); virtual void s74();
    virtual void s78();
    virtual void AddButton(const wchar_t* text, int id, int a, int b);   // +0x7c
};
struct AutoRefCountText {                                  // EA::AutoRefCount<IWinText>
    IWinText* mpObject;
    void Assign(IWinText* p);                              // @ 0x00b5f950 (operator=)
};
IWinText* WinText_CreateDefault(int a, uint b);            // @ 0x00989130 (cdecl)
extern const wchar_t g_OK[];        // 0x014439bc
extern const wchar_t g_Yes[];       // 0x014439b4
extern const wchar_t g_No[];        // 0x014439ac
extern const wchar_t g_Cancel[];    // 0x0144399c
struct WinMessageBox {
    char     pad0[4];
    char     pad4[0x2d0 - 4];
    float    mClient[4];            // +0x2d0: client-area rectangle (l, t, r, b)
    char     pad2e0[0x338 - 0x2e0];
    IMsgBoxSub mSub;                // +0x338 (vptr only)
    uint     mnType;                // +0x33c
    float    mfGutter;              // +0x340
    float    mfTextBorder[4];       // +0x344
    float    mfButtonBorder[4];     // +0x354
    float    mfButtonMinW;          // +0x364
    float    mfButtonMinH;          // +0x368
    float    mfButtonSpacing;       // +0x36c
    float    mfButtonW;             // +0x370
    float    mfButtonH;             // +0x374
    uint     mnButtonTextStyle;     // +0x378
    uint     mnButtonAlignment;     // +0x37c
    IWinButton** mpButtonsBegin;    // +0x380
    IWinButton** mpButtonsEnd;      // +0x384
    char     pad388[0x3b4 - 0x388];
    wchar_t* mpTextBegin;           // +0x3b4 (msMessageText begin)
    wchar_t* mpTextEnd;             // +0x3b8
    char     pad3bc[0x3c4 - 0x3bc];
    uint     mnMessageTextStyle;    // +0x3c4
    uint     mnMessageTextColor;    // +0x3c8
    AutoRefCountText mpMessageText; // +0x3cc
    void*    mpButtonDrawable;      // +0x3d0

    __forceinline uint ButtonCount() const { return (uint)(mpButtonsEnd - mpButtonsBegin); }
    bool WinDialogRefresh();        // @ 0x0096c6f0
    bool Refresh();                 // @ 0x0097f390
};
// ---- items of slice s0097f390 end

// ---- items of slice s0096d2f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned __cdecl wcslen(const wchar_t*);
#pragma intrinsic(wcslen)
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
}
namespace EA {
struct IRefCounted {
    virtual int AddRef();          // +0x00
    virtual int Release();         // +0x04
};
}
namespace EA {
namespace UTFWin {
class IWindow_s0096_d2f0;
}
}
namespace EA {
namespace UTFWin {
class WindowIterator { public:
    void* mpNode;                  // +0x00
    void* mpNode2;                 // +0x04
    void* mpNode3;                 // +0x08
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s0096_d2f0 { public:
PV(0);
PV(1);
PV(2);
PV(3);
PV(4);
PV(5);
PV(6);
    virtual uint32_t GetId();                              // +0x1c  slot 7
PV(8);
PV(9);
PV(10);
PV(11);
PV(12);
PV(13);
    virtual const RectF& GetRealArea();                    // +0x38  slot 14
PV(15);
PV(16);
PV(17);
PV(18);
PV(19);
PV(20);
PV(21);
PV(22);
PV(23);
    virtual void SetArea(const RectF& area);               // +0x60  slot 24
    PV(25);
    virtual void SetSize(float w, float h);                // +0x68  slot 26
PV(27);
PV(28);
PV(29);
PV(30);
    virtual void SetFlag(uint32_t flag, bool value);       // +0x7c  slot 31
PV(32);
PV(33);
PV(34);
PV(35);
PV(36);
PV(37);
PV(38);
PV(39);
PV(40);
PV(41);
PV(42);
PV(43);
PV(44);
PV(45);
PV(46);
PV(47);
PV(48);
PV(49);
PV(50);
    virtual WindowIterator ChildBegin();                   // +0xcc  slot 51
    virtual WindowIterator ChildEnd();                     // +0xd0  slot 52

    void WinSetFlag(uint32_t flag, int value);             // 0x00961760
};
}
}
namespace EA {
namespace UTFWinControls {
using EA::RectF;
}
}
namespace EA {
namespace UTFWinControls {
using EA::UTFWin::IWindow_s0096_d2f0;
}
}
namespace EA {
namespace UTFWinControls {
using EA::UTFWin::WindowIterator;
}
}
namespace EA {
namespace UTFWinControls {
struct WinDialogBase {
PV(0);
PV(1);
PV(2);
PV(3);
PV(4);
PV(5);
PV(6);
PV(7);
PV(8);
PV(9);
PV(10);
PV(11);
PV(12);
PV(13);
PV(14);
PV(15);
PV(16);
PV(17);
PV(18);
PV(19);
PV(20);
PV(21);
PV(22);
PV(23);
PV(24);
PV(25);
PV(26);
PV(27);
PV(28);
PV(29);
PV(30);
PV(31);
PV(32);
PV(33);
PV(34);
    virtual bool Refresh();                                // +0x8c  slot 35 (0x0096c6f0)
    PV(36);                                                // +0x90  slot 36
    virtual void SetSize(float w, float h);                // +0x94  slot 37 (0x0096d2f0)
    virtual void GetMinSize(float& w, float& h);           // +0x98  slot 38 (0x0096d3f0)
    virtual void GetMaxSize(float& w, float& h);           // +0x9c  slot 39 (0x0096d500)
    virtual void SetRefreshFlag(unsigned v);               // +0xa0  slot 40 (0x0096b6a0)

    void WindowCtor();                                     // 0x00962a10
    void WindowDtor();                                     // 0x00962740
};
}
}
namespace EA {
namespace UTFWinControls {
class WinDialog : public WinDialogBase, public IWindow_s0096_d2f0 {
public:
    uint32_t pad08[(0x210 - 0x08) / 4];   // +0x08
    bool     mbRefresh;                   // +0x210
    char     pad211[3];
    uint32_t mnDialogFlags;               // +0x214
    uint32_t mnSelectedComponent;         // +0x218
    float    mnCursorOffsetX;             // +0x21c
    float    mnCursorOffsetY;             // +0x220
    EA::IRefCounted* mpCloseButtonDrawable; // +0x224
    EA::IRefCounted* mpCloseButton;       // +0x228
    EA::IRefCounted* mpTitleText;         // +0x22c
    RectF    mrComponentArea[10];         // +0x230
    RectF    mrClientArea;                // +0x2d0
    RectF    mfClientAreaBorder;          // +0x2e0
    RectF    mfTitleTextBorder;           // +0x2f0
    RectF    mfCloseButtonBorder;         // +0x300
    float    mfMaxW;                      // +0x310
    float    mfMaxH;                      // +0x314
    float    mfMinW;                      // +0x318
    float    mfMinH;                      // +0x31c
    uint32_t mnTitleTextColor;            // +0x320
    uint32_t mnTitleTextStyle;            // +0x324

    WinDialog* Init();                    // 0x0096e0c0
    void       Destroy();                 // 0x0096e260

    // Override the same-named virtuals in both bases.
    void SetSize(float w, float h);       // 0x0096d2f0
    void GetMinSize(float& w, float& h);  // 0x0096d3f0
    void GetMaxSize(float& w, float& h);  // 0x0096d500
};
}
}
namespace EA {
namespace UTFWinControls {
struct WString {
    const wchar_t* mpBegin;               // +0x00
    const wchar_t* mpEnd;                 // +0x04
    const wchar_t* mpCapacity;            // +0x08
    void assign(const wchar_t* first, const wchar_t* last);
};
}
}
namespace EA {
namespace UTFWinControls {
struct IWinDialogSub {
PV(0);
PV(1);
PV(2);
PV(3);
PV(4);
PV(5);
PV(6);
PV(7);
    virtual void AutoSize();                              // +0x20  slot 8  (0x0096dc70)
PV(9);
PV(10);
PV(11);
PV(12);
PV(13);
PV(14);
PV(15);
PV(16);
    virtual void SetTitleText(const wchar_t* p);          // +0x44  slot 17 (0x0096e350)
PV(18);
PV(19);
PV(20);
PV(21);
PV(22);
PV(23);
PV(24);
PV(25);
PV(26);
PV(27);

    char     pad04[4];                    // +0x04
    uint32_t mnDialogFlags;               // +0x08
    uint32_t mnSelectedComponent;         // +0x0c
    float    mnCursorOffsetX;             // +0x10
    float    mnCursorOffsetY;             // +0x14
    void*    mpCloseButtonDrawable;       // +0x18
    void*    mpCloseButton;               // +0x1c
    void*    mpTitleText;                 // +0x20
    RectF    mrComponentArea[10];         // +0x24
    RectF    mrClientArea;                // +0xc4
    RectF    mfClientAreaBorder;          // +0xd4
    RectF    mfTitleTextBorder;           // +0xe4
    RectF    mfCloseButtonBorder;         // +0xf4
    float    mfMaxW;                      // +0x104
    float    mfMaxH;                      // +0x108
    float    mfMinW;                      // +0x10c
    float    mfMinH;                      // +0x110
    uint32_t mnTitleTextColor;            // +0x114
    uint32_t mnTitleTextStyle;            // +0x118
    WString  msTitleText;                 // +0x11c
};
}
}
// ---- items of slice s0096d2f0 end

// ---- items of slice s0097e1f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
bool __fastcall WinDialog_DoMessage(void* self, void* unused, int* msg);   // 0x0096c430  __thiscall ret 4
#define VT(o, i) ((*(void***)(o))[i])
#define VCALL0(R, o, i)        (((R(__thiscall*)(void*))VT(o, i))(o))
#define VCALL1(R, o, i, A, a)  (((R(__thiscall*)(void*, A))VT(o, i))(o, a))
#define VCALL2(R, o, i, A, a, B, b) (((R(__thiscall*)(void*, A, B))VT(o, i))(o, a, b))
struct IRef {                                   // ref-counted object: slot0 AddRef, slot1 Release
    virtual int AddRef() throw();
    virtual int Release() throw();
};
struct MsgBoxSub {                               // IWinMessageBox sub-object
    void* mVptr;                                 // +0
    int   mType;                                 // +4
void vt0();
void vt1();
void vt2();
void vt3();
void vt4();
void vt5();
void vt6();
void vt7();
void vt8();
void vt9();
void vt10();
void vt11();
void vt12();
void vt13();
void vt14();
void vt15();
void vt16();
void vt17();
void vt18();
void vt19();
void vt20();
void vt21();
void vt22();
void vt23();
void vt24();
void vt25();
void vt26();
void vt27();
void vt28();
void vt29();
void vt30();
void vt31();
    void vt32();                                 // +0x80
    void vt33();                                 // +0x84
    void vt34();                                 // +0x88
    void SetType(int t);                         // 0x0097ed30, ret 4
    void Set8c(int v);                           // 0x0097ed60, ret 4
    void Set90(int v);                           // 0x0097ed80, ret 4
    void SetBorder0(float a, float b, float c, float d);   // 0x0097eda0, ret 0x10
    void SetBorder1(float a, float b, float c, float d);   // 0x0097ee10, ret 0x10
    void Set40(int v);                           // 0x0097ee50, ret 4
    void Set2c30(float a, float b);              // 0x0097ee70, ret 8
    void Set34(float v);                         // 0x0097ee90, ret 4
    void Set44(int v);                           // 0x0097eec0, ret 4
    void Set8(float v);                          // 0x0097eee0, ret 4
    void SetDrawable(IRef* p);                   // 0x0097efa0, ret 4
};
struct Msg_s0097_e1f0 {                                     // UTFWin::Message
    IRef*    source;                             // +0
    int      pad4;
    unsigned eventType;                          // +8
    unsigned subType;                            // +0xc
    int      pad10;
    int      id;                                 // +0x14
};
struct WinMessageBox_s0097_e1f0 {
    void*  mVptr;                                // +0
    void*  mSerVptr;                             // +4
    void*  mIWindowVptr;                         // +8
    char   pad0[0x34 - 0xc];
    void*  mInstanceId;                          // +0x34
    char   pad1[0x80 - 0x38];
    void*  mCommentBegin;                        // +0x80
    void*  mCommentEnd;                          // +0x84
    char   pad2[0x338 - 0x88];
    MsgBoxSub mSub;                              // +0x338
    char   pad3[0x40];                           // +0x340 .. +0x380
    IRef** mpButtonsBegin;                       // +0x380
    IRef** mpButtonsEnd;                         // +0x384

    void SerUpdate();                            // 0x0097ec90
    bool DoMessage(Msg_s0097_e1f0* msg);                    // 0x0097efe0
};
struct WinGridBase {                             // the IWinGrid sub-object at grid-0x20c
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
    virtual void Slot35();                       // +0x8c
    virtual void v36();
    virtual void Slot37(float x, float y);       // +0x94
    virtual void Slot38(float* w, float* h);     // +0x98
    virtual void Slot39(float* x, float* y);     // +0x9c
};
struct GridScroll {                              // the scrolling-row object at grid+0x1c0
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
    virtual void* Slot4();                       // +0x10  (4)
virtual void v05();
virtual void v06();
    virtual void Slot7(int a);                   // +0x1c  (7)
virtual void v08();
virtual void v09();
    virtual bool Slot26();                       // +0x28  (10)
virtual void v11();
virtual void v12();
virtual void v13();
    virtual const float* GetArea();              // +0x38  (14)
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
    virtual void DrawRow(float x, float rowH);   // +0x68  (26)
};
struct WinGrid {                                 // the WinGrid main object (this)
    char  pad0[0x134];
    float mRowH;                                 // +0x134
    char  pad1[0x164 - 0x138];
    float mX;                                    // +0x164
    float mY;                                    // +0x168
    char  pad2[0x1c0 - 0x16c];
    GridScroll* mpScroll;                        // +0x1c0
    void UpdateArea();                           // 0x0097f130
};
// ---- items of slice s0097e1f0 end

// @ 0x0096e350
namespace EA { namespace UTFWinControls {
void IWinDialogSub::SetTitleText(const wchar_t* p)
{
    const wchar_t* e = p;
    while (*e != 0)
        ++e;
    msTitleText.assign(p, &p[e - p]);
    ((WinDialog*)((char*)this - 0x20c))->SetRefreshFlag(1);
}
}}  // namespace EA::UTFWinControls

// @ 0x0097efe0
bool WinMessageBox_s0097_e1f0::DoMessage(Msg_s0097_e1f0* msg)
{
    IRef** it;
    IRef* found;

    if (msg->eventType == 0x287259f6) {
        it = mpButtonsBegin;
        for (; it != mpButtonsEnd; ++it) {
            found = VCALL0(IRef*, *it, 0x10 / 4);        // button -> GetWindow()
            if (found != 0 && found == msg->source)
                goto found_it;
        }
        if (msg->subType == 0x4f0dd487) {
            if (mInstanceId != 0) {
                void* w = (char*)this + 4;
                if (VCALL1(bool, mInstanceId, 0x80 / 4, void*, w)) {
                    VCALL2(void, mInstanceId, 0x78 / 4, void*, w, int, 3);
                    return true;
                }
            }
            {
                struct { int pad0; int pad1; unsigned evt; void* text; int id; } local;
                local.evt = 0x8f4d1281;
                local.text = mCommentEnd ? mCommentEnd : mCommentBegin;
                local.id = 3;
                VCALL1(void, (char*)this + 4, 0x114 / 4, void*, &local);
            }
            return true;
        }
    }
    return WinDialog_DoMessage(this, 0, (int*)msg);

found_it:
    {
        void* w = (char*)this + 4;
        if (mInstanceId != 0) {
            if (VCALL1(bool, mInstanceId, 0x80 / 4, void*, w)) {
                unsigned id = VCALL0(unsigned, found, 0x1c / 4);
                VCALL2(void, mInstanceId, 0x78 / 4, void*, w, unsigned, id);
                return true;
            }
        }
        {
            struct { int pad0; int pad1; unsigned evt; void* text; int id; } local;
            local.evt = 0x8f4d1281;
            local.text = mCommentEnd ? mCommentEnd : mCommentBegin;
            local.id = (int)VCALL0(unsigned, found, 0x1c / 4);
            VCALL1(void, (char*)this + 4, 0x114 / 4, void*, &local);
        }
        return true;
    }
}

// @ 0x0097f130
void WinGrid::UpdateArea()
{
    WinGridBase* base = (WinGridBase*)((char*)this - 0x20c);
    float sw, sh, w, h;
    float limit;
    float x, y;
    float pos, height, drawX;
    GridScroll* row;
    const float* area;

    base->Slot35();
    base->Slot38(&sw, &sh);
    base->Slot39(&w, &h);
    limit = mRowH * 2.0f;
    x = mX;
    if (limit + mX < sw)
        x = sw;
    y = mY;
    if (limit + mY < sh)
        y = sh;

    if (mpScroll != 0) {
        row = (GridScroll*)mpScroll->Slot4();
        if (row->Slot26() & 1) {
            mpScroll->Slot7(0);
            row = (GridScroll*)mpScroll->Slot4();
            area = row->GetArea();
            pos = area[2] - area[0];
            row = (GridScroll*)mpScroll->Slot4();
            area = row->GetArea();
            height = area[3] - area[1];
            if (pos > x) {
                do {
                    if (pos <= height * 4.0f)
                        break;
                    if (pos > w) {
                        drawX = w;
                    } else {
                        drawX = pos - 10.0f;
                        if (x > pos - 10.0f)
                            drawX = x;
                    }
                    row = (GridScroll*)mpScroll->Slot4();
                    row->DrawRow(drawX, height);
                    mpScroll->Slot7(1);
                    row = (GridScroll*)mpScroll->Slot4();
                    area = row->GetArea();
                    height = area[3] - area[1];
                    pos = drawX;
                } while (pos > x);
            }
            y = (mRowH + height) + y;
            if (pos > x)
                x = pos;
        }
    }
    limit = mRowH * 2.0f;
    base->Slot37(limit + x, limit + y);
}

// @ 0x0097f390
bool WinMessageBox::Refresh()
{
    if (WinDialogRefresh()) {
    if (mpButtonsBegin == mpButtonsEnd) {
        switch (mnType) {
        case 1:
            mSub.AddButton(g_OK, 0, 0, 1);
            break;
        case 2:
            mSub.AddButton(g_OK, 0, 0, 1);
            mSub.AddButton(g_Cancel, 3, 0, 0);
            break;
        case 3:
            mSub.AddButton(g_Yes, 1, 0, 1);
            mSub.AddButton(g_No, 2, 0, 0);
            break;
        case 4:
            mSub.AddButton(g_Yes, 1, 0, 1);
            mSub.AddButton(g_No, 2, 0, 0);
            mSub.AddButton(g_Cancel, 3, 0, 0);
            break;
        }
    }

    if (mpTextBegin == mpTextEnd || mnMessageTextStyle == 0) {
        if (mpMessageText.mpObject)
            mpMessageText.mpObject->GetWindow()->SetFlag(1, false);
    } else {
        if (!mpMessageText.mpObject) {
            mpMessageText.Assign(WinText_CreateDefault(-1, 0xf170dc1));
            if (mpMessageText.mpObject)
                ((IWindow*)((char*)this + 4))->AddWindow(mpMessageText.mpObject->GetWindow());
        }
        if (mpMessageText.mpObject) {
            mpMessageText.mpObject->GetWindow()->SetCaption(mpTextBegin);
            mpMessageText.mpObject->GetWindow()->SetTextFontID(mnMessageTextStyle);
            mpMessageText.mpObject->GetWindow()->SetFlag(1, true);
            mpMessageText.mpObject->GetWindow()->SetFlag(0x200, true);
            mpMessageText.mpObject->GetWindow()->SetFlag(0x10, true);
            mpMessageText.mpObject->SetTextColor(mnMessageTextColor);
            mpMessageText.mpObject->SetBorder(mfTextBorder[0], mfTextBorder[1], mfTextBorder[2], mfTextBorder[3]);
        }
    }

    mfButtonH = 0.0f;
    mfButtonW = 0.0f;
    _ReadWriteBarrier();

    if (mpButtonsBegin != mpButtonsEnd) {
        _ReadWriteBarrier();
        IWinButton** it = mpButtonsBegin;
        mfButtonH = mfButtonMinH;
        mfButtonW = mfButtonMinW;
        for (; it != mpButtonsEnd; ++it) {
            IWinButton* btn = *it;
            if (btn) {
                btn->SetBorder(mfButtonBorder[0], mfButtonBorder[1], mfButtonBorder[2], mfButtonBorder[3]);
                btn->GetWindow()->SetTextFontID(mnButtonTextStyle);
                if (mpButtonDrawable)
                    btn->SetDrawable(mpButtonDrawable);
                const float* r = btn->GetWindow()->GetRealArea();
                float w = r[2] - r[0];
                r = btn->GetWindow()->GetRealArea();
                float h = r[3] - r[1];
                IWindow* win = btn->GetWindow();
                if (win) {
                    float out[2];
                    Msg m;
                    m.out = out;
                    m.type = 0x16;
                    m.eventType = 0;
                    if (win->GetWindowManager()) {
                        if (win->GetWindowManager()->SendMsg(win, win, &m, false))
                            w = out[1];
                    }
                }
                if (w > mfButtonW)
                    mfButtonW = w;
                if (h > mfButtonH)
                    mfButtonH = h;
                IWindow* bw = btn->GetWindow();
                Rect rc(0.0f, 0.0f, mfButtonW, mfButtonH);
                bw->SetArea(&rc);
            }
        }
        for (IWinButton** it = mpButtonsBegin; it != mpButtonsEnd; ++it) {
            if (*it) {
                IWindow* w = (*it)->GetWindow();
                Rect rc(0.0f, 0.0f, mfButtonW, mfButtonH);
                w->SetArea(&rc);
            }
        }
        float a = (float)(ButtonCount() - 1) * mfButtonSpacing;
        _ReadWriteBarrier();
        mfButtonW = a + (float)ButtonCount() * mfButtonW;
    }

    if (mpMessageText.mpObject) {
        if (mpMessageText.mpObject->GetWindow()->GetFlags() & 1) {
            float g = mfGutter;
            Rect rc(mClient[0] + g, mClient[1] + g, mClient[2] - g, (mClient[3] - mfButtonH) - g * 2.0f);
            mpMessageText.mpObject->GetWindow()->SetArea(&rc);
        }
    }

    if (mpButtonsBegin != mpButtonsEnd) {
        float y = mClient[1] + mfGutter;
        if (mpMessageText.mpObject) {
            if (mpMessageText.mpObject->GetWindow()->GetFlags() & 1)
                y = mpMessageText.mpObject->GetWindow()->GetRealArea()[3] + mfGutter;
        }
        float g = mfGutter;
        y = ((((mClient[3] - y) - mfButtonH) - g) * 0.5f) + y;
        float x = mClient[0];
        switch (mnButtonAlignment) {
        case 1:
            x = x + g;
            break;
        case 2:
            x = (mClient[2] - mfButtonW) - g;
            break;
        case 3:
            x = ((((mClient[2] - x) - mfButtonW) - g * 2.0f) * 0.5f + x) + g;
            break;
        }
        for (IWinButton** it = mpButtonsBegin; it != mpButtonsEnd; ++it) {
            IWindow* win = (*it)->GetWindow();
            if (win) {
                const float* r = win->GetRealArea();
                float bottom = (r[3] - r[1]) + y;
                r = win->GetRealArea();
                Rect rc(x, y, (r[2] - r[0]) + x, bottom);
                win->SetArea(&rc);
            }
            const float* r2 = win->GetRealArea();
            x = ((r2[2] - r2[0]) + mfButtonSpacing) + x;
        }
    }
    return true;
    }
    return false;
}

// @ 0x01300b20
void init_154f94c()
{
    *(int*)0x154f94c = 1;
    *(int*)0x154f950 = 0;
    *(int*)0x154f954 = 0;
    *(int*)0x154f958 = 0xeec2c011;
    *(short*)0x154f95c = 0xb;
    *(int*)0x154f960 = 0x340;
    *(int*)0x154f964 = 1;
}
