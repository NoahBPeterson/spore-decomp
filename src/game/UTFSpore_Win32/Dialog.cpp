// src/game/UTFSpore_Win32/Dialog.cpp -- migrated from slice(s) s0096bdd0, s01300280, s0096c6f0, s0096ad00 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Dialog.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinControls/IWinButton.h"
#include "EA/UTFWinControls/IWinText.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/IWindowMgr.h"
#include "EA/Text/LineLayout.h"
#include "EA/UTFWin/Message.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/Text/TextStyle.h"
#include "EA/Text/Typesetter.h"
#include "EA/UTFWin/Window.h"

// ---- items of slice s0096ad00 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct Vec2 {
    float x, y;
    Vec2() {}
    Vec2(float a, float b) : x(a), y(b) {}
    Vec2& operator=(const Vec2& v) { x = v.x; y = v.y; return *this; }
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
struct IWindow_s0096_ad00;
}
}
namespace EA {
namespace UTFWin {
struct IWindowMgr_s0096_ad00;
}
}
namespace EA {
namespace UTFWin {
struct IWindowMgr_s0096_ad00 {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7);
    PV(8); PV(9); PV(10); PV(11); PV(12); PV(13); PV(14);
    virtual void* GetCapture(int);                 // +0x3c
    PV(16); PV(17); PV(18); PV(19); PV(20);
    virtual void* GetCapture2(int);                // +0x54
    virtual void  SetCapture(int, void*);          // +0x58
    virtual void  SetCapture2(int, void*);         // +0x5c
};
}
}
namespace EA {
namespace UTFWin {
struct IWindow_s0096_ad00 {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7);
    PV(8); PV(9); PV(10); PV(11); PV(12); PV(13); PV(14);
    PV(15); PV(16); PV(17); PV(18); PV(19); PV(20);
    PV(21); PV(22); PV(23); PV(24); PV(25); PV(26); PV(27); PV(28); PV(29); PV(30);
    virtual void SetFlag(uint32_t flag, int value);    // +0x7c
    PV(32); PV(33); PV(34); PV(35);
    virtual int  Invalidate();                         // +0x90
};
}
}
namespace EA {
namespace UTFWin {
struct WindowVt {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7); PV(8); PV(9);
    PV(10); PV(11); PV(12); PV(13); PV(14); PV(15); PV(16); PV(17); PV(18); PV(19);
    PV(20); PV(21); PV(22); PV(23); PV(24); PV(25); PV(26); PV(27); PV(28); PV(29);
    PV(30); PV(31); PV(32); PV(33); PV(34);
    PV(35);
    virtual int  GetComponentAt(float x, float y);     // +0x90
    PV(37); PV(38); PV(39);
    virtual void UpdateLayout(int mode);               // +0xa0

    bool Window_Initialize();       // 0x00b1fbf0
    void Window_SerUpdate();        // 0x009614a0
    void Window_InvalidateLayout(); // 0x009609b0
    void Window_Shutdown();         // 0x00961e80
};
}
}
using EA::UTFWin::IWindow_s0096_ad00;
using EA::UTFWin::IWindowMgr_s0096_ad00;
using EA::UTFWin::IWindowMgr_s0096_ad00;
struct WinDialog : EA::UTFWin::WindowVt {
    uint32_t pad04[(0x88 - 0x04) / 4];        // +0x04
    EA::RectF mArea;                           // +0x88
    uint32_t pad98[(0x210 - 0x98) / 4];       // +0x98
    bool     mbRefresh;                        // +0x210
    uint32_t mnDialogFlags;                    // +0x214
    int      mnSelectedComponent;              // +0x218
    float    mnCursorOffsetX;                  // +0x21c
    float    mnCursorOffsetY;                  // +0x220
    void*    mpCloseButtonDrawable;            // +0x224
    void*    mpCloseButton;                    // +0x228
    void*    mpTitleText;                      // +0x22c

    void SetRefreshFlag(unsigned v);           // 0x0096b6a0
    bool OnMouseUp(int, int, int, unsigned flags); // 0x0096b600
    int  OnMouseDown(int, float px, float py, unsigned eventType); // 0x0096b460
};
struct DlgSub20c {
    uint32_t pad00[2];                         // +0x00
    int      mFlags;                           // +0x08
    uint32_t pad0c[(0xd4 - 0x0c) / 4];         // +0x0c
    float    mLocalBorder[4];                  // +0x0d4
    float    mTitleBorder[4];                  // +0x0e4
    float    mCloseBorder[4];                  // +0x0f4
    float    mMaxW, mMaxH;                     // +0x104
    float    mMinW, mMinH;                     // +0x10c
    int      mTitleTextColor;                  // +0x114
    int      mTitleTextStyle;                  // +0x118

    void SetFlags(int f);                                     // 0x0096b400
    void SetLocalBorder(float, float, float, float);          // 0x0096b710
    void SetTitleBorder(float, float, float, float);          // 0x0096b7b0
    void SetCloseBorder(float, float, float, float);          // 0x0096b850
    void SetTitleTextStyle(int v);                            // 0x0096b770
    void SetTitleTextColor(int v);                            // 0x0096b900
    void SetMinSize(float w, float h);                        // 0x0096b930
    void SetMaxSize(float w, float h);                        // 0x0096b990
};
struct DlgSub4 {
    void InvalidateAndLayout();                               // 0x0096b680
};
struct DictIface {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7);
    PV(8); PV(9); PV(10); PV(11); PV(12); PV(13); PV(14); PV(15);
    PV(16); PV(17); PV(18); PV(19); PV(20); PV(21); PV(22); PV(23);
    virtual void v60(void* n);                                // +0x60
    virtual void* v64();                                      // +0x64
};
struct DialogState {
    char  pad00[0x18];
    void* mpValue;                                            // +0x18
    void* mpHook;                                             // +0x1c

    void  SetValue(void* p);                                  // 0x0096bd60
    void* GetValue();                                         // 0x0096bdb0
};
struct DialogDrawable {
    char  pad00[0x18];
    void* mpImage0;                                           // +0x18
    void* mpImage1;                                           // +0x1c

    void* AsInterface(uint32_t type);                         // 0x0096ba00
    bool  GetNaturalSize(EA::Vec2* dst, int state, int index); // 0x0096ba30
    void* BaseAsInterface(uint32_t type);                     // 0x00951240
};
struct ImageTable {
    uint32_t pad00[1];
    void*    mpBackground;                                    // +0x04
    uint32_t mBlitMode;                                       // +0x08
    void*    mpImages[10];                                    // +0x0c

    void SetImage(unsigned idx, void* p);                     // 0x0096bb10
    void GetBackground(void** out);                           // 0x0096bb50
    void SetBlitMode(unsigned mode);                          // 0x0096bb60
    void GetBlitMode(void** out);                             // 0x0096bb70
};
// ---- items of slice s0096ad00 end

// ---- items of slice s0096c6f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
struct Vec2_s0096_c6f0 {
    float x, y;
    Vec2_s0096_c6f0() {}
    Vec2_s0096_c6f0(float fx, float fy) : x(fx), y(fy) {}
    Vec2_s0096_c6f0& operator=(const Vec2_s0096_c6f0& v) { x = v.x; y = v.y; return *this; }
};
}
namespace EA {
template <class T>
struct AutoRefCount_s0096_c6f0 {
    T* mpObject;

    AutoRefCount_s0096_c6f0& operator=(T* pObject)
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
}
namespace EA {
namespace UTFWin {
struct IWindow_s0096_c6f0;
}
}
namespace EA {
namespace UTFWin {
struct Message_s0096_c6f0 {
    IWindow_s0096_c6f0* source;        // +0x00
    int      field_04;      // +0x04
    int      eventType;     // +0x08
    int      param0;        // +0x0c
    int      param1;        // +0x10
    int      param2;        // +0x14
    void*    pData;         // +0x18
};
}
}
namespace EA {
namespace UTFWin {
struct IWindowManager {
    PV(0); PV(1); PV(2); PV(3);
    virtual bool SendMsg(IWindow_s0096_c6f0* pTarget, IWindow_s0096_c6f0* pSource, Message_s0096_c6f0* pMsg, int flags); // +0x10
};
}
}
namespace EA {
namespace UTFWin {
struct IWindow_s0096_c6f0 {
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
    virtual void AddWindow(IWindow_s0096_c6f0* pWindow);                         // +0xd8
    PV(55);
    virtual void DisposeWindowFamily(IWindow_s0096_c6f0* pWindow);               // +0xe0
};
}
}
namespace EA {
namespace UTFWin {
struct IDrawable_s0096_c6f0 {
    virtual int   AddRef();
    virtual int   Release();
    PV(2);
    virtual void* Cast(uint32_t type);                                // +0x0c
    PV(4); PV(5);
    virtual bool  GetDimensions(Vec2_s0096_c6f0* dst, int state, int index);     // +0x18
};
}
}
namespace EA {
namespace UTFWinControls {
using UTFWin::IWindow_s0096_c6f0;
}
}
namespace EA {
namespace UTFWinControls {
struct IButtonDrawable_s0096_c6f0 {
    virtual int AddRef();
    virtual int Release();
};
}
}
namespace EA {
namespace UTFWinControls {
struct IWinButton_s0096_c6f0 {
    virtual int   AddRef();
    virtual int   Release();
    PV(2);
    virtual void* Cast(uint32_t type);                                // +0x0c
    virtual IWindow_s0096_c6f0* ToWindow();                                      // +0x10
    PV(5); PV(6); PV(7); PV(8); PV(9); PV(10); PV(11); PV(12); PV(13); PV(14); PV(15);
    PV(16); PV(17); PV(18); PV(19); PV(20); PV(21); PV(22); PV(23);
    virtual void SetButtonDrawable(IButtonDrawable_s0096_c6f0* pDrawable);       // +0x60
};
}
}
namespace EA {
namespace UTFWinControls {
struct IWinText_s0096_c6f0 {
    virtual int   AddRef();
    virtual int   Release();
    PV(2); PV(3);
    virtual IWindow_s0096_c6f0* ToWindow();                                      // +0x10
    PV(5); PV(6); PV(7); PV(8); PV(9);
    virtual void SetTextColor(uint32_t color);                        // +0x28
    PV(11); PV(12); PV(13);
    virtual void SetTextBorders(float l, float t, float r, float b);  // +0x38
};
}
}
namespace EA {
namespace UTFWinControls {
namespace WinButton {
 IWinButton_s0096_c6f0* CreateDefault(int type, int a, int b);   // 0x9671c0
}
}
}
namespace EA {
namespace UTFWinControls {
namespace WinText {
 IWinText_s0096_c6f0*   CreateDefault(int a, uint32_t styleId);   // 0x989130
}
}
}
namespace EA {
namespace UTFWinControls {
struct WinDialogBase {                                                // primary vtable
    PV(0);  PV(1);  PV(2);  PV(3);  PV(4);  PV(5);  PV(6);  PV(7);  PV(8);  PV(9);
    PV(10); PV(11); PV(12); PV(13); PV(14); PV(15); PV(16); PV(17); PV(18); PV(19);
    PV(20); PV(21); PV(22); PV(23); PV(24); PV(25); PV(26); PV(27); PV(28); PV(29);
    PV(30); PV(31); PV(32); PV(33); PV(34); PV(35); PV(36); PV(37); PV(38); PV(39);
    virtual void UpdateLayout(int a);                                 // +0xa0
};
}
}
namespace EA {
namespace UTFWinControls {
enum {
    kDialogTitleText   = 0x04,
    kDialogTitleBar    = 0x08,
    kDialogCloseButton = 0x10,
    kDialogComponents  = 0x20
};
}
}
namespace EA {
namespace UTFWinControls {
enum {
    kComponentClient = 0, kComponentTitle, kComponentLeft, kComponentRight, kComponentTop,
    kComponentBottom, kComponentTopLeft, kComponentTopRight, kComponentBottomLeft,
    kComponentBottomRight, kComponentCount
};
}
}
namespace EA {
namespace UTFWinControls {
class WinDialog_s0096_c6f0 : public WinDialogBase, public IWindow_s0096_c6f0 {
public:
    bool Refresh();

    uint32_t                     pad08[(0x88 - 0x08) / 4];
    RectF                        mArea;                    // +0x88
    uint32_t                     pad98[(0x1e0 - 0x98) / 4];
    UTFWin::IDrawable_s0096_c6f0*           mpDrawable;               // +0x1e0
    uint32_t                     pad1e4[(0x210 - 0x1e4) / 4];
    bool                         mbRefresh;                // +0x210
    uint32_t                     mnDialogFlags;            // +0x214
    uint32_t                     mnSelectedComponent;      // +0x218
    float                        mnCursorOffsetX;          // +0x21c
    float                        mnCursorOffsetY;          // +0x220
    AutoRefCount_s0096_c6f0<IButtonDrawable_s0096_c6f0> mpCloseButtonDrawable;   // +0x224
    AutoRefCount_s0096_c6f0<IWinButton_s0096_c6f0>     mpCloseButton;            // +0x228
    AutoRefCount_s0096_c6f0<IWinText_s0096_c6f0>       mpTitleText;              // +0x22c
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
}
}
// ---- items of slice s0096c6f0 end

// ---- items of slice s0096bdd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 4)
#pragma pack(pop)
struct RectF_s0096_bdd0 {
  float mLeft, mTop, mRight, mBottom;
};
struct WinDialogVtbl {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
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
virtual void v35();
  virtual int  v36(float a, float b);  // +0x90
};
struct WinDialogBase_s0096_bdd0 {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
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
  virtual void SetRect(RectF_s0096_bdd0 const* pRect);  // +0x60
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
  virtual void v29();
  virtual void SetCursor(int id);            // +0x78
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
  virtual void v35();
  virtual void Refresh();                    // +0x90
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
virtual void v46();
virtual void v47();
virtual void v48();
virtual void v49();
virtual void v50();
virtual void v51();
virtual void v52();
virtual void v53();
virtual void v54();
virtual void v55();
virtual void v56();
virtual void v57();
virtual void v58();
virtual void v59();
virtual void v60();
virtual void v61();
virtual void v62();
virtual void v63();
virtual void v64();
virtual void v65();
virtual void v66();
virtual void v67();
virtual void v68();
  virtual void UpdateWindow(void* local);    // +0x114
};
struct MouseManager {
virtual void m00();
virtual void m01();
virtual void m02();
virtual void m03();
virtual void m04();
virtual void m05();
virtual void m06();
virtual void m07();
virtual void m08();
virtual void m09();
virtual void m10();
virtual void m11();
virtual void m12();
virtual void m13();
virtual void m14();
  virtual void GetPoint(void* pPoint);  // +0x3c
virtual void m16();
virtual void m17();
virtual void m18();
virtual void m19();
  virtual void m20();
  virtual void* GetTarget(int flag);    // +0x54
};
struct CompContainer {
virtual void c00();
virtual void c01();
virtual void c02();
virtual void c03();
virtual void c04();
virtual void c05();
virtual void c06();
virtual void c07();
virtual void c08();
virtual void c09();
virtual void c10();
virtual void c11();
virtual void c12();
virtual void c13();
virtual void c14();
  virtual void GetPoint(void* pPoint);  // +0x3c
};
struct CompContainerSub {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
virtual void s44();
virtual void s45();
virtual void s46();
virtual void s47();
  virtual void s48();
  virtual void DrawPoint(RectF_s0096_bdd0 const* pRect);  // +0xc4
};
struct ICompContainer {
virtual void i00();
virtual void i01();
virtual void i02();
  virtual void* FindWindow(unsigned int id);                            // +0x0c
  virtual void  AddComponent(void* arg, RectF_s0096_bdd0 const* r, void* local);   // +0x10
};
struct IWinRef {
virtual void r00();
virtual void r01();
virtual void r02();
virtual void r03();
  virtual void* QueryLayout();  // +0x10
};
struct ILayout {
virtual void l00();
virtual void l01();
virtual void l02();
virtual void l03();
virtual void l04();
virtual void l05();
virtual void l06();
  virtual void* GetWindow();  // +0x1c
};
struct WinDialog_s0096_bdd0 {
  void* mVT0;                                // 0x000
  void* mVT1;                                // 0x004  base sub-object vptr
  void* mUnk08;                              // 0x008
  void* mVT2;                                // 0x00c
  void* mUnk10;                              // 0x010
  char  mPad14[0x34 - 0x14];
  MouseManager*  mObj34;                     // 0x034
  CompContainer* mObj38;                     // 0x038
  char  mPad3c[0x80 - 0x3c];
  void* mObj80;                              // 0x080
  void* mObj84;                              // 0x084
  RectF_s0096_bdd0 mWindowRect;                         // 0x088
  char  mPad98[0x1d8 - 0x98];
  int   mRef1d8;                             // 0x1d8
  int   mRef1dc;                             // 0x1dc
  ICompContainer* mComponents;               // 0x1e0
  char  mPad1e4[0x214 - 0x1e4];
  unsigned int mFlags;                       // 0x214
  int   mKind;                               // 0x218
  float mOff21c;                             // 0x21c
  float mOff220;                             // 0x220
  char  mPad224[0x228 - 0x224];
  IWinRef* mWinRef;                          // 0x228
  char  mPad22c[0x230 - 0x22c];
  RectF_s0096_bdd0 mRect230;                            // 0x230
  RectF_s0096_bdd0 mRect240;                            // 0x240
  RectF_s0096_bdd0 mChildren[8];                        // 0x250 .. 0x2cf
  char  mPad2d0[0x2e0 - 0x2d0];
  RectF_s0096_bdd0 mBorder;                             // 0x2e0
  char  mPad2f0[0x310 - 0x2f0];
  RectF_s0096_bdd0 mMinMax;                             // 0x310

  bool OnMouseMove(float a, float b, float c);  // 0x0096bdd0
  bool DoMessage(void* msg);                    // 0x0096c430
  int  FUN_0096c4c0(float x, float y);          // 0x0096c4c0
  bool OnRebuild(void* arg);                    // 0x0096c5d0
  bool DoMessageBase(void* msg);                // 0x00950bb0
  void OnPaint(void* arg);                      // 0x00960310
};
struct MsgArg {
  int          mPad0;
  int          mPad4;
  unsigned int mType;
  void*        mPtr;
  int          mResult;
  int          mPad14;
  int          mPad18;
};
// ---- items of slice s0096bdd0 end

// @ 0x0096b380
void __fastcall Sub_b380(WinDialog* this_)
{
    this_->UpdateLayout(1);
    return this_->Window_SerUpdate();
}

// @ 0x0096b3a0
bool __fastcall WinDialog_Init(WinDialog* this_)
{
    if (this_->Window_Initialize()) {
        this_->UpdateLayout(1);
        return true;
    }
    return false;
}

// @ 0x0096b400
void DlgSub20c::SetFlags(int f)
{
    if (mFlags != f) {
        mFlags = f;
        return ((EA::UTFWin::WindowVt*)((char*)this - 0x20c))->UpdateLayout(1);
    }
}

// @ 0x0096b460
int WinDialog::OnMouseDown(int, float px, float py, unsigned eventType)
{
    if (eventType != 8)
        return 0;
    (void)px;
    (void)py;

    char* esi = (char*)this;
    int comp = this->GetComponentAt(py, px);
    *(int*)(esi + 0x218) = comp;
    if (comp == -1)
        goto finish;

    if (comp <= 9) {
        switch (comp) {
        case 0:
        case 1:
            if ((*(unsigned char*)(esi + 0x214) & 1) == 0) {
                if ((*(unsigned char*)(esi + 0x214) & 2) == 0) {
                    *(int*)(esi + 0x218) = -1;
                }
            }
            break;
        default:
            if ((*(unsigned char*)(esi + 0x214) & 2) == 0) {
                *(int*)(esi + 0x218) = -1;
            }
            break;
        }
    }
    if (*(int*)(esi + 0x218) == -1)
        goto finish;

    {
        IWindowMgr_s0096_ad00* pMgr = *(IWindowMgr_s0096_ad00**)(esi + 0x34);
        char* pWin = *(char**)(esi + 0x38);
        void* pHit = pMgr ? pMgr->GetCapture(1) : 0;
        (void)pHit;

        EA::Vec2 local;
        pMgr->GetCapture(0);                   // placeholder for area query
        (void)pWin;
        (void)local;
    }
    {
        IWindowMgr_s0096_ad00* pMgr = *(IWindowMgr_s0096_ad00**)(esi + 0x34);
        IWindow_s0096_ad00* pIWin = (IWindow_s0096_ad00*)(esi + 4);
        if (pMgr->GetCapture2(1) != pIWin)
            pMgr->SetCapture2(1, pIWin);
    }

finish:
    ((IWindow_s0096_ad00*)(esi + 4))->Invalidate();
    return 1;
}

// @ 0x0096b600
bool WinDialog::OnMouseUp(int, int, int, unsigned flags)
{
    if ((flags & 8) == 0) {
        IWindow_s0096_ad00* pSelf = this ? (IWindow_s0096_ad00*)((char*)this + 4) : 0;
        if ((*(IWindowMgr_s0096_ad00**)((char*)this + 0x34))->GetCapture2(1) == (void*)pSelf)
            (*(IWindowMgr_s0096_ad00**)((char*)this + 0x34))->SetCapture2(1, (IWindow_s0096_ad00*)((char*)this + 4));

        *(int*)((char*)this + 0x218) = -1;
        ((IWindow_s0096_ad00*)((char*)this + 4))->Invalidate();
        return true;
    }
    return false;
}

// @ 0x0096b660
bool __fastcall WinDialog_OnTick(WinDialog* this_)
{
    this_->pv35();
    return true;
}

// @ 0x0096b680
void DlgSub4::InvalidateAndLayout()
{
    ((EA::UTFWin::WindowVt*)((char*)this - 4))->UpdateLayout(1);
    return ((EA::UTFWin::WindowVt*)((char*)this))->Window_InvalidateLayout();
}

// @ 0x0096b6a0
void WinDialog::SetRefreshFlag(unsigned v)
{
    if (*(unsigned char*)((char*)this + 0x210) != (unsigned char)v) {
        *(unsigned char*)((char*)this + 0x210) = (unsigned char)v;
        ((IWindow_s0096_ad00*)((char*)this + 4))->SetFlag(8, v);
    }
}

// @ 0x0096b710
void DlgSub20c::SetLocalBorder(float a, float b, float c, float d)
{
    mLocalBorder[0] = a;
    mLocalBorder[1] = b;
    mLocalBorder[2] = c;
    mLocalBorder[3] = d;
    ((EA::UTFWin::WindowVt*)((char*)this - 0x20c))->UpdateLayout(1);
}

// @ 0x0096b770
void DlgSub20c::SetTitleTextStyle(int v)
{
    mTitleTextStyle = v;
    return ((EA::UTFWin::WindowVt*)((char*)this - 0x20c))->UpdateLayout(1);
}

// @ 0x0096b7b0
void DlgSub20c::SetTitleBorder(float a, float b, float c, float d)
{
    mTitleBorder[0] = a;
    mTitleBorder[1] = b;
    mTitleBorder[2] = c;
    mTitleBorder[3] = d;
    ((EA::UTFWin::WindowVt*)((char*)this - 0x20c))->UpdateLayout(1);
}

// @ 0x0096b850
void DlgSub20c::SetCloseBorder(float a, float b, float c, float d)
{
    mCloseBorder[0] = a;
    mCloseBorder[1] = b;
    mCloseBorder[2] = c;
    mCloseBorder[3] = d;
    ((EA::UTFWin::WindowVt*)((char*)this - 0x20c))->UpdateLayout(1);
}

// @ 0x0096b900
void DlgSub20c::SetTitleTextColor(int v)
{
    mTitleTextColor = v;
    return ((EA::UTFWin::WindowVt*)((char*)this - 0x20c))->UpdateLayout(1);
}

// @ 0x0096b930
void DlgSub20c::SetMinSize(float w, float h)
{
    mMinW = w;
    mMinH = h;
    ((EA::UTFWin::WindowVt*)((char*)this - 0x20c))->UpdateLayout(1);
}

// @ 0x0096b990
void DlgSub20c::SetMaxSize(float w, float h)
{
    mMaxW = w;
    mMaxH = h;
    ((EA::UTFWin::WindowVt*)((char*)this - 0x20c))->UpdateLayout(1);
}

// @ 0x0096ba00
void* DialogDrawable::AsInterface(uint32_t type)
{
    if (type != 0x6f0c6ff6u) {
        if (type != 0xeec58382u)
            return BaseAsInterface(type);
        if (this)
            return (void*)((char*)this + 4);
        return 0;
    }
    return this;
}

// @ 0x0096ba30
bool DialogDrawable::GetNaturalSize(EA::Vec2* dst, int, int index)
{
    switch (index) {
    case 0:
        if (mpImage0) {
            dst->x = (float)*(int*)((char*)mpImage0 + 0x1c);
            dst->y = (float)*(int*)((char*)mpImage0 + 0x20);
        }
        return true;
    case 1:
        if (mpImage1) {
            dst->y = (float)*(int*)((char*)mpImage1 + 0x20);
            return true;
        }
        dst->y = 20.0f;
        return true;
    case 2:
    case 3:
        dst->x = 3.0f;
        return true;
    case 4:
    case 5:
        dst->y = 3.0f;
        return true;
    case 6:
    case 7:
    case 8:
    case 9:
        dst->x = 3.0f;
        dst->y = 3.0f;
        return true;
    default:
        return false;
    }
}

// @ 0x0096bb10
void ImageTable::SetImage(unsigned idx, void* p)
{
    if (idx >= 10)
        return;
    if (mpImages[idx] == p)
        return;
    if (p)
        ((EA::IRefCounted*)p)->AddRef();
    EA::IRefCounted* old = (EA::IRefCounted*)mpImages[idx];
    if (old)
        old->Release();
    mpImages[idx] = p;
}

// @ 0x0096bb50
void ImageTable::GetBackground(void** out)
{ *out = mpBackground; }

// @ 0x0096bb60
void ImageTable::SetBlitMode(unsigned mode)
{
    if (mode <= 3)
        mBlitMode = mode;
}

// @ 0x0096bb70
void ImageTable::GetBlitMode(void** out)
{ *out = (void*)mBlitMode; }

// @ 0x0096bd00
void __fastcall WinDialog_Shutdown(WinDialog* this_)
{
    if (*(EA::IRefCounted**)((char*)this_ + 0x224)) {
        EA::IRefCounted* p = *(EA::IRefCounted**)((char*)this_ + 0x224);
        *(void**)((char*)this_ + 0x224) = 0;
        p->Release();
    }
    if (*(EA::IRefCounted**)((char*)this_ + 0x228)) {
        EA::IRefCounted* p = *(EA::IRefCounted**)((char*)this_ + 0x228);
        *(void**)((char*)this_ + 0x228) = 0;
        p->Release();
    }
    if (*(EA::IRefCounted**)((char*)this_ + 0x22c)) {
        EA::IRefCounted* p = *(EA::IRefCounted**)((char*)this_ + 0x22c);
        *(void**)((char*)this_ + 0x22c) = 0;
        p->Release();
    }
    return this_->Window_Shutdown();
}

// @ 0x0096bd60
void DialogState::SetValue(void* p)
{
    EA::IRefCounted* old = (EA::IRefCounted*)mpValue;
    if (p != old) {
        if (p)
            ((EA::IRefCounted*)p)->AddRef();
        mpValue = p;
        if (old)
            old->Release();
    }
    DictIface* q = (DictIface*)mpHook;
    if (q)
        return q->v60(mpValue);
}

// @ 0x0096bdb0
void* DialogState::GetValue()
{
    DictIface* q = (DictIface*)mpHook;
    if (q)
        return q->v64();
    return mpValue;
}

// @ 0x0096bdd0
bool WinDialog_s0096_bdd0::OnMouseMove(float a, float b, float c)
{
  WinDialogBase_s0096_bdd0* pSelf = (this != 0) ? (WinDialogBase_s0096_bdd0*)((char*)this + 4) : 0;
  if (mObj34->GetTarget(1) == (void*)pSelf) {
    RectF_s0096_bdd0 rect = mWindowRect;
    float pt[2];
    mObj34->GetPoint(pt);
    ((CompContainerSub*)((char*)mObj38 + 4))->DrawPoint(&rect);

    float w = mWindowRect.mRight - mWindowRect.mLeft;
    float h = mWindowRect.mBottom - mWindowRect.mTop;
    switch (mKind) {
      case 0:
        rect.mLeft = pt[0] - mOff21c;
        rect.mTop = pt[1] - mOff220;
        rect.mRight = w + rect.mLeft;
        rect.mBottom = h + rect.mTop;
        break;
      case 1: {
        float right = rect.mRight;
        float l = pt[0] - mOff21c;
        rect.mLeft = l;
        if (mMinMax.mRight > right - l) rect.mLeft = right - mMinMax.mRight;
        if (right - rect.mLeft <= mMinMax.mLeft) break;
        rect.mLeft = right - mMinMax.mLeft;
        break;
      }
      case 2: {
        float right = mOff21c + pt[0];
        rect.mRight = right;
        if (mMinMax.mRight > right - rect.mLeft)
          rect.mRight = rect.mLeft + mMinMax.mRight;
        if (rect.mRight - rect.mLeft <= mMinMax.mLeft) break;
        rect.mRight = rect.mLeft + mMinMax.mLeft;
        break;
      }
      case 3: {
        float bottom = rect.mBottom;
        float t = pt[1] - mOff220;
        rect.mTop = t;
        if (mMinMax.mBottom > bottom - t) rect.mTop = bottom - mMinMax.mBottom;
        if (bottom - rect.mTop <= mMinMax.mTop) break;
        rect.mTop = bottom - mMinMax.mTop;
        break;
      }
      case 4: {
        float bottom = mOff220 + pt[1];
        rect.mBottom = bottom;
        if (mMinMax.mBottom > bottom - rect.mTop)
          rect.mBottom = rect.mTop + mMinMax.mBottom;
        if (rect.mBottom - rect.mTop <= mMinMax.mTop) break;
        rect.mBottom = rect.mTop + mMinMax.mTop;
        break;
      }
      case 5: {
        float right = rect.mRight;
        float bottom = rect.mBottom;
        float l = pt[0] - mOff21c;
        float t = pt[1] - mOff220;
        rect.mLeft = l;
        if (mMinMax.mRight > right - l) rect.mLeft = right - mMinMax.mRight;
        rect.mTop = t;
        if (mMinMax.mBottom > bottom - t) rect.mTop = bottom - mMinMax.mBottom;
        if (right - rect.mLeft <= mMinMax.mLeft) break;
        rect.mLeft = right - mMinMax.mLeft;
        if (bottom - rect.mTop <= mMinMax.mTop) break;
        rect.mTop = bottom - mMinMax.mTop;
        break;
      }
      case 6: {
        float right = mOff21c + pt[0];
        float t = pt[1] - mOff220;
        rect.mRight = right;
        rect.mTop = t;
        if (mMinMax.mRight > right - rect.mLeft)
          rect.mRight = rect.mLeft + mMinMax.mRight;
        if (mMinMax.mBottom > rect.mBottom - t)
          rect.mTop = rect.mBottom - mMinMax.mBottom;
        if (rect.mRight - rect.mLeft <= mMinMax.mLeft) break;
        rect.mRight = rect.mLeft + mMinMax.mLeft;
        if (rect.mBottom - rect.mTop <= mMinMax.mTop) break;
        rect.mTop = rect.mBottom - mMinMax.mTop;
        break;
      }
      case 7: {
        float right = rect.mRight;
        float bottom = mOff220 + pt[1];
        float l = pt[0] - mOff21c;
        rect.mLeft = l;
        rect.mBottom = bottom;
        if (mMinMax.mRight > right - l) rect.mLeft = right - mMinMax.mRight;
        if (mMinMax.mBottom > bottom - rect.mTop)
          rect.mBottom = rect.mTop + mMinMax.mBottom;
        if (right - rect.mLeft <= mMinMax.mLeft) {
          if (bottom - rect.mTop <= mMinMax.mTop) break;
          rect.mBottom = rect.mTop + mMinMax.mTop;
          break;
        }
        rect.mLeft = right - mMinMax.mLeft;
        if (bottom - rect.mTop <= mMinMax.mTop) break;
        rect.mBottom = rect.mTop + mMinMax.mTop;
        break;
      }
      case 8: {
        float right = mOff21c + pt[0];
        float bottom = mOff220 + pt[1];
        rect.mRight = right;
        rect.mBottom = bottom;
        if (mMinMax.mRight > right - rect.mLeft)
          rect.mRight = rect.mLeft + mMinMax.mRight;
        if (mMinMax.mBottom > bottom - rect.mTop)
          rect.mBottom = rect.mTop + mMinMax.mBottom;
        if (rect.mRight - rect.mLeft > mMinMax.mLeft)
          rect.mRight = rect.mLeft + mMinMax.mLeft;
        if (rect.mBottom - rect.mTop <= mMinMax.mTop) break;
        rect.mBottom = rect.mTop + mMinMax.mTop;
        break;
      }
      case 9:
      default:
        break;
    }
    ((WinDialogBase_s0096_bdd0*)&mVT1)->SetRect(&rect);
  } else {
    int r = ((WinDialogVtbl*)this)->v36(c, b);
    int cmd;
    switch (r) {
      case 2:
      case 3: cmd = 0x1009; break;
      case 4:
      case 5: cmd = 0x1008; break;
      case 6:
      case 9: cmd = 0x100a; break;
      case 7:
      case 8: cmd = 0x100b; break;
      default: cmd = 0x1002; break;
    }
    ((WinDialogBase_s0096_bdd0*)&mVT1)->SetCursor(cmd);
  }
  ((WinDialogBase_s0096_bdd0*)&mVT1)->Refresh();
  return true;
}

// @ 0x0096c430
bool WinDialog_s0096_bdd0::DoMessage(void* msg)
{
  int* pMsg = (int*)msg;
  if (pMsg[2] != 0x287259f6) return DoMessageBase(msg);
  if (pMsg[3] != 0x4f0dd487) return DoMessageBase(msg);
  if (mObj38 != 0) {
    MsgArg local;
    local.mType = 0x8f4d1282;
    local.mPtr = (mObj84 != 0) ? mObj84 : mObj80;
    IWinRef* pRef = mWinRef;
    ILayout* pLayout = (ILayout*)pRef->QueryLayout();
    local.mResult = (int)pLayout->GetWindow();
    ((WinDialogBase_s0096_bdd0*)&mVT1)->UpdateWindow(&local);
  }
  return true;
}

// @ 0x0096c4c0
int WinDialog_s0096_bdd0::FUN_0096c4c0(float x, float y)
{
  unsigned int flags = mFlags;
  if ((flags & 0x20) != 0) {
    float w = mWindowRect.mRight - mWindowRect.mLeft - mBorder.mRight;
    float h = mWindowRect.mBottom - mWindowRect.mTop - mBorder.mBottom;
    if (x < mBorder.mLeft) {
      if (y < mBorder.mTop) return 6;
      if (h <= y) return 8;
      return 2;
    }
    if (w <= x) {
      if (y < mBorder.mTop) return 7;
      if (h <= y) return 9;
      return 3;
    }
    if (y < mBorder.mTop) return 4;
    if (h <= y) return 5;
  }
  if ((flags & 8) != 0) {
    if (mRect240.mLeft <= x && mRect240.mTop <= y && x < mRect240.mRight &&
        y < mRect240.mBottom)
      return 1;
    return -1;
  }
  return 0;
}

// @ 0x0096c5d0
bool WinDialog_s0096_bdd0::OnRebuild(void* arg)
{
  if (mComponents != 0 && mComponents->FindWindow(0x6f0c6ff6) != 0) {
    int local[4];
    local[0] = 0;
    local[1] = 0;
    local[2] = mRef1dc;
    local[3] = mRef1d8;
    mComponents->AddComponent(arg, &mRect230, local);

    if ((mFlags & 8) != 0) {
      local[1] = 1;
      mComponents->AddComponent(arg, &mRect240, local);
    }

    if ((mFlags & 0x20) != 0) {
      for (int i = 2; i < 10; ++i) {
        RectF_s0096_bdd0* r = &mChildren[i - 2];
        if (r->mRight > r->mLeft && r->mBottom > r->mTop) {
          local[1] = i;
          mComponents->AddComponent(arg, r, local);
        }
      }
    }
  } else {
    OnPaint(arg);
  }
  return true;
}

// @ 0x0096c6f0
namespace EA { namespace UTFWinControls {
bool WinDialog_s0096_c6f0::Refresh()
{
    if (!mbRefresh || !mpDrawable)
        return false;

    UpdateLayout(0);

    const bool bDialogDrawable = (mpDrawable ? mpDrawable->Cast(0x6f0c6ff6) : 0) != 0;

    Vec2_s0096_c6f0 size[kComponentCount];
    if (bDialogDrawable) {
        for (unsigned i = 0; i < kComponentCount; ++i) {
            Vec2_s0096_c6f0 dim(0.0f, 0.0f);
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
                static_cast<IWindow_s0096_c6f0*>(this)->AddWindow(mpCloseButton->ToWindow());
            }
        }
    } else if (mpCloseButton) {
        static_cast<IWindow_s0096_c6f0*>(this)->DisposeWindowFamily(mpCloseButton->ToWindow());
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
                static_cast<IWindow_s0096_c6f0*>(this)->AddWindow(mpTitleText->ToWindow());
            }
        }
    } else if (mpTitleText) {
        static_cast<IWindow_s0096_c6f0*>(this)->DisposeWindowFamily(mpTitleText->ToWindow());
        mpTitleText = 0;
    }

    if (mpCloseButton) {
        if (mpCloseButtonDrawable)
            mpCloseButton->SetButtonDrawable(mpCloseButtonDrawable);

        float buttonW = mpCloseButton->ToWindow()->GetRealArea().Width();
        float buttonH = mpCloseButton->ToWindow()->GetRealArea().Height();

        if (mpCloseButton) {
            IWindow_s0096_c6f0* pWindow = (IWindow_s0096_c6f0*)mpCloseButton->Cast(0xeeee8218);
            if (pWindow) {
                Vec2_s0096_c6f0 preferred;
                UTFWin::Message_s0096_c6f0 msg;
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

    IWinButton_s0096_c6f0* const pCloseButton = mpCloseButton;
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

    IWindow_s0096_c6f0* const pWindow = static_cast<IWindow_s0096_c6f0*>(this);
    pWindow->SetSize(w, h);
    pWindow->Invalidate();
    return true;
}
}}  // namespace EA::UTFWinControls

// @ 0x01300950
void init_154f4dc()
{
    *(int*)0x154f4dc = 0xa;
    *(int*)0x154f4e0 = 0;
    *(int*)0x154f4e4 = 0;
    *(int*)0x154f4e8 = 0x2f42e1a2;
    *(short*)0x154f4ec = 9;
    *(int*)0x154f4f0 = 0x10;
    *(int*)0x154f4f4 = 1;
    *(int*)0x154f4f8 = 0;
    *(int*)0x154f4fc = 0;
    *(int*)0x154f500 = 0x2f42e1a3;
    *(short*)0x154f504 = 9;
    *(int*)0x154f508 = 0x14;
    *(int*)0x154f50c = 1;
}
