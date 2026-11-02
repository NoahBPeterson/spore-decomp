// src/game/UTFSpore_Win32/winxhtml.cpp -- migrated from slice(s) s00995b20, s00994c80, s00994240, s00993520, s00992480 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/winxhtml.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinExtras/WinXHTML.h"
#include "EA/XHTML/DOM/Document.h"
#include "EA/XHTML/Layout/Page.h"
#include "EA/XHTML/DOM/EventListener.h"
#include "EA/UTFWin/IDrawable.h"
#include "EA/UTFWinControls/IWinGrid.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWinControls/WinGrid.h"
#include "EA/UTFWin/Window.h"
#include "EA/UTFWinExtras/cXHTMLFrameSet.h"

// unnamed retail callees and globals (address in the comment)
extern float g_negMask;        // 0x013eb8b0  (-x sign flip); 0x013ec4d8 for WatchWindow ctor

// ---- items of slice s00992480 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
typedef signed   int   i32;
static inline u32  ld32(char* b, u32 off) { return *(u32*)(b + off); }
static inline void st32(char* b, u32 off, u32 v) { *(u32*)(b + off) = v; }
static inline u8   ld8 (char* b, u32 off) { return *(u8*)(b + off); }
static inline void st8 (char* b, u32 off, u8 v) { *(u8*)(b + off) = v; }
static inline float ldf(char* b, u32 off) { return *(float*)(b + off); }
static inline void stf (char* b, u32 off, float v) { *(float*)(b + off) = v; }
void  Obj962740_f(char* p);                                          // 0x00962740  base dtor
void  FUN_00950bb0(char* p);                                         // base message handler
void  DestroyFormControls(char* doc);                                // 0x008e2890
void  RemoveAllChildren(char* doc);                                  // 0x008e2930
void  Page_dtor(char* page);                                         // 0x008ec810
void  Page_NotifyImagesAbandoned(char* page);                        // 0x008eb7a0
void  Page_Render(char* page, char* batch, const void* a, const void* b); // 0x008eb870
void  RenderCtx_End2D(char* ctx);                                    // 0x0095bb20
char* RenderCtx_Begin2D(char* ctx, void* mode);                      // 0x0095bc10
void  FUN_00571e80(char* sw);                                        // Stopwatch::Restart
float Stopwatch_GetElapsedTimeFloat(char* sw);                       // 0x005ff1a0
void  RefObj_release(char* p);                                       // an IRefCount::Release (vt+4)
extern float g_negMask;        // 0x013eb8b0  (-x sign flip); 0x013ec4d8 for WatchWindow ctor
struct PageOps        { void __thiscall SetSelectionRange(int a, int b); };
typedef void (__thiscall *SlotSetInt)(char* self, int v);
typedef int  (__thiscall *SlotGetInt)(char* self);
// ---- items of slice s00992480 end

// ---- items of slice s00993520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_009512c0(void);                                    // 0x9512c0
extern "C" void* FUN_009512d0(int size, int align, const char* name, void* alloc); // 0x9512d0
extern "C" void* WinWindow_ctor(void* mem);                             // 0x962a10
extern "C" void* FrameDrawable_ctor(void* mem);                         // 0x96fe30
extern "C" void* StdDrawable_ctor(void* mem);                           // 0x988420
extern "C" void* ComboBoxDrawable_ctor(void* mem);                      // 0x969000
extern "C" void  FUN_008ec790(void* a);                                 // 0x8ec790
extern "C" void  Page_FUN_008eb830(void* page, void* a);                // 0x8eb830
extern "C" void* XHTML_Style_CreateDefaultStylesheet(void);             // 0x8fa050
extern "C" void* Text_GetStyleManager(int flag);                        // 0x885bd0
extern "C" int   Text_StyleManagerAddStyle(void* mgr, int key, void* style, unsigned* out); // 0x894970
extern "C" void  Stopwatch_ctor(void* self, int a, int b);              // 0x93a560
extern float  g_kDefaultWidth;                                          // 0x1470f1c
#define VF(o, off, sig) ((sig)(*(void***)(o))[(off) / 4])
struct WinXHTML {
    void* mVtbl0;                   // 0x000
    void* mIWindow;                 // 0x004   (IWindow interface sub-object)
    char  pad[0x200 - 8];
    unsigned char mbRefresh;        // 0x200
    char  pad2[0x23c - 0x201];
    void* mDoc;                     // 0x23c
    void* mPageRoot;                // 0x240
    char  pad3[0x850 - 0x244];
    void* mFormCtrlDrawable[5];     // 0xa850
    float mVisibleArea[4];          // 0xa864  (left/top/right/bottom)
    void* mContentWindow;           // 0xa874
    void* mScrollbar0;              // 0xa878
    void* mDrawable0;               // 0xa87c
    int   mEnabled0;                // 0xa880
    float mPref0X;                  // 0xa884
    float mPref0Y;                  // 0xa888
    void* mScrollbar1;              // 0xa88c
    void* mDrawable1;               // 0xa890
    int   mEnabled1;                // 0xa894
    float mPref1X;                  // 0xa898
    float mPref1Y;                  // 0xa89c
    void* mScrollPosish;            // 0xa8a0
    void* mField_a8a4;              // 0xa8a4

    void CreateScrollbar(int which);
    void DestroyFormControl(void* fc);
    void SetFormControlStyle(void* fc, void* style);
    void GetFormControlSize(void* fc, void* out);
    void SetFormControlArea(void* fc, void* area);
    void SetFormControlDrawable(int which, void* drawable);
    void SerUpdate();
    WinXHTML();
    bool Init();
    bool Shutdown();
    void CalculateVisibleArea();
    void SetScrollbarDrawable(int which, void* drawable);
};
extern "C" void* WinScrollbar_ctor(void* mem);                          // 0x983790
extern "C" void* ScrollbarDrawable_ctor(void* mem);                     // 0x9838a0
extern "C" void  Window_Initialize(void* self);                         // 0xb1fbf0
extern "C" void  Window_Shutdown(void* self);                           // 0x961e80
extern "C" void  Win_SerUpdate(void* self);                             // 0x9614a0
extern "C" void  Text_StyleManagerRemoveStyle(void* mgr, int key);       // 0x894700
extern "C" void  XHTML_DOM_FormControl_SetControl(void* fc, void* ctl);  // 0x8e4b60
extern "C" void  DocX_RemoveAllChildren(void* doc);                     // 0x8e2930
extern float  g_kScrollbarSize;                                         // 0x13eecd8
// ---- items of slice s00993520 end

// ---- items of slice s00994240 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* DAT_01550104;                                      // 0x1550104  (DOM attribute name)
struct XHTMLPage {
    void Layout();                                              // 0x8ec360
    unsigned char Pick(void* pt, void* out);                    // 0x8ec4f0
    void SetImageRequester(void* node, int kind);               // 0x8eb7e0
    void Resize(float w, float h);                              // 0x8ec8c0
    unsigned FUN_008ecc90(void* node);                          // 0x8ecc90
    void FUN_008edc30();                                        // 0x8edc30
    void FUN_008edc90(void* doc);                               // 0x8edc90
};
struct DOMNode    { void* AsElement(); };                       // 0x8e52f0
struct DOMElement { void* GetAttrValue(void* key); };           // 0x8e45b0
struct DOMDocument {
    void DestroyFormControls();                                 // 0x8e2890
    void FUN_008e2870();                                        // 0x8e2870
};
struct DocX { unsigned char CheckFlag(unsigned char v); };      // 0x8e29e0
struct WinMsg {
    void* r0;
    void* r1;
    int   code;
    int   f3;
    int   f4;
    int   f5;
    int   f6;
};
struct WinXHTML_s0099_4240 {
    void CalculateVisibleArea();        // 0x9940f0
    void FUN_00994240();                // 0x994240
    void FUN_00994c30(int);             // 0x994c30
    void FUN_00992ee0(void* a);         // 0x992ee0
    void FUN_00992e00(int lo, int hi);  // 0x992e00
    bool FUN_009948a0(float x, float y, int a);   // 0x9948a0
    bool OnFocusChange(int a, void* b);           // 0x9947f0
    bool OnMouseDown(float x, float y, int a, int b);  // 0x994a40
    void SetDocument(void* doc);                  // 0x994b00
};
struct WinXHTMLCmd {
    void OnDOMEvent(void* param_2);     // 0x9946b0
};
// ---- items of slice s00994240 end

// ---- items of slice s00994c80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) long __cdecl wcstol(const wchar_t* s, wchar_t** end, int base);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);
extern wchar_t gEmptyString16;                           // 0x01667bac
extern const wchar_t* gAttrType;       // 0x01550108
extern const wchar_t* gAttrValue;      // 0x0155010c
extern const wchar_t* gAttrName;       // 0x01550110
extern const wchar_t* gAttrLabel;      // 0x01550114
extern const wchar_t* gAttrChecked;    // 0x01550118
extern const wchar_t* gAttrDisabled;   // 0x0155011c
extern const wchar_t* gAttrReadonly;   // 0x01550124
extern const wchar_t* gAttrSize;       // 0x01550128
extern const wchar_t* gAttrMultiple;   // 0x0155012c
extern const wchar_t* gValButton;      // 0x01550138
extern const wchar_t* gValText;        // 0x0155013c
extern const wchar_t* gValPassword;    // 0x01550140
extern const wchar_t* gValCheckbox;    // 0x01550144
extern const wchar_t* gValRadio;       // 0x01550148
extern const wchar_t* gValSubmit;      // 0x0155014c
extern const wchar_t* gValReset;       // 0x01550150
extern const wchar_t* gValImage;       // 0x01550154
extern const wchar_t* gValHidden;      // 0x01550158
#define VP_CAT2(a, b) a##b
#define VP_CAT(a, b) VP_CAT2(a, b)
#define VP1 virtual void VP_CAT(_vp, __COUNTER__)();
#define VP2 VP1 VP1
#define VP4 VP2 VP2
#define VP8 VP4 VP4
#define VP16 VP8 VP8
#define VP32 VP16 VP16
void* GetUTFWinAllocator();                                                       // 0x009512c0
void* operator new(unsigned int size, int align, const char* name, void* alloc);  // 0x009512d0
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void operator delete[](void* p);                                                  // 0x00f47380
struct IDrawable {
    VP4
    /* 10h */ virtual void* GetObjectID();   // passed to ITextEdit slot 0xe8
};
struct IWindow {
    VP16 VP4
    /* 50h */ virtual void SetControlID(uint32_t id);
    /* 54h */ virtual void SetCommandID(uint32_t id);
    VP8 VP1
    /* 7Ch */ virtual void SetFlag(int flag, bool value);
    /* 80h */ virtual void SetCaption(const wchar_t* caption);
    VP8 VP2
    /* ACh */ virtual void SetFillColor(uint32_t color);
    /* B0h */ virtual void SetDrawable(IDrawable* d);
    /* B4h */ virtual void func45(int);
    /* B8h */ virtual void SetUserObject(uint32_t id, void* obj);
    VP4 VP2 VP1
    /* D8h */ virtual void AddWindow(IWindow* w);
};
struct IButton {
    VP4
    /* 10h */ virtual IWindow* ToWindow();
    VP2
    /* 1Ch */ virtual void SetButtonType(int type);
    VP2
    /* 28h */ virtual void SetButtonStateFlag(int flag, bool value);
    VP4 VP2
    /* 44h */ virtual void SetButtonGroupID(uint32_t id);
    VP2 VP1
    /* 54h */ virtual void SetCaptionBorders(float l, float t, float r, float b);
};
struct Rect {
    float l, t, r, b;
    void Set(float v) { l = v; t = v; r = v; b = v; }
};
struct ITextEdit {
    VP4
    /* 10h */ virtual IWindow* ToWindow();
    VP4 VP1
    /* 28h */ virtual void SetMargins(const Rect* margins);
    VP4 VP1
    /* 40h */ virtual void SetEditMode(int mode);
    /* 44h */ virtual void SetEditFlag(int flag, bool value);
    VP4 VP2
    /* 60h */ virtual void SetText(const wchar_t* text, int len);
    VP1
    /* 68h */ virtual void SetMaxTextLength(int n);
    VP16 VP8 VP4 VP2 VP1
    /* E8h */ virtual void SetScrollbarDrawable(int vertical, void* drawable);
};
struct IComboBox {
    VP4
    /* 10h */ virtual IWindow* ToWindow();
    VP2
    /* 1Ch */ virtual void SetComboBoxFlag(int flag, bool value);
    /* 20h */ virtual void AddValue(const wchar_t* value);
    VP8 VP1
    /* 48h */ virtual void SetColor(int index, uint32_t color);
    VP4 VP1
    /* 60h */ virtual void SetScrollbarDrawable(IDrawable* d);
};
struct IWinGrid {
    VP4
    /* 10h */ virtual IWindow* ToWindow();
    VP4 VP2
    /* 2Ch */ virtual void SetGridFlag(int flag, bool value);
    VP2 VP1
    /* 3Ch */ virtual void SetColor(uint32_t color, int index);
    VP4 VP2
    /* 58h */ virtual void SetCellMargins(float l, float t, float r, float b);
    VP1
    /* 60h */ virtual void SetCellPadding(float l, float t, float r, float b);
    VP4
    /* 74h */ virtual void SetSelectionLimits(int a, int max, int b);
    VP8
    /* 98h */ virtual void SetHeaderFlags(int a, int b);
    VP8
    /* BCh */ virtual void SetAutoSize(int a, int b);
    VP8 VP1
    /* E4h */ virtual void SetLineWidth(float w);
    VP32 VP8 VP4 VP2 VP1
    /* 1A4h */ virtual void SetCellText(int col, int row, const wchar_t* text, int a, int b, int c);
    VP16 VP8
    /* 208h */ virtual void SetHScrollbarDrawable(IDrawable* d);
    /* 20Ch */ virtual void SetVScrollbarDrawable(IDrawable* d);
};
struct WindowImplBase { virtual void w0(); };
struct WindowImpl : WindowImplBase, IWindow {            // EA::UTFWin::Window, 0x20c bytes
    WindowImpl();                                        // 0x00962a10
    uint32_t mBody[0x81];
};
struct ControlBase { virtual void c0(); uint32_t mBody[0x82]; };   // the Window part, 0x20c bytes
struct WinButton : ControlBase, IButton {               // 0x888 bytes
    WinButton();                                         // 0x00966f90
    uint32_t mBody[0x19e];
};
struct WinTextEdit : ControlBase, ITextEdit {           // 0x658 bytes
    WinTextEdit();                                       // 0x0098c110
    uint32_t mBody[0x112];
};
struct WinComboBox : ControlBase, IComboBox {           // 0x2b8 bytes
    WinComboBox();                                       // 0x00969450
    uint32_t mBody[0x2a];
};
struct WinGrid : ControlBase, IWinGrid {                // 0xa90 bytes
    WinGrid();                                           // 0x009770e0
    uint32_t mBody[0x220];
};
struct StdDrawable : IDrawable {                        // 0x7c bytes
    StdDrawable();                                       // 0x00988420
    uint32_t mBody[0x1e];
};
struct intrusive_list_node {
    intrusive_list_node* mpNext;
    intrusive_list_node* mpPrev;
};
struct string16 {                                        // eastl::basic_string<wchar_t>
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    string16();
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    static void DoFree(wchar_t* p) {
        if (p)
            operator delete[](p);
    }
    const wchar_t* c_str() const { return mpBegin; }
};
inline string16::string16() : mpBegin(&gEmptyString16), mpEnd(&gEmptyString16), mpCapacity(&gEmptyString16 + 1) {}
namespace XHTML {
struct NodeVBase {
    VP2
    /* 08h */ virtual void GetTextContent(string16& out);
};
}
namespace XHTML {
struct Node : NodeVBase, intrusive_list_node {
    int Type();                                          // 0x00fc7e50
};
}
namespace XHTML {
enum { kNodeTypeElement = 1 };
}
namespace XHTML {
enum {
    kElementInput = 0x17, kElementSelect = 0x18, kElementOption = 0x19,
    kElementTextarea = 0x1a, kElementButton = 0x1b
};
}
namespace XHTML {
struct NodeList {                                        // eastl::intrusive_list<Node>
    intrusive_list_node mAnchor;
    struct iterator {
        Node* mpNode;
        iterator(Node* p) : mpNode(p) {}
        iterator& operator++() { mpNode = static_cast<Node*>(mpNode->mpNext); return *this; }
        bool operator!=(const iterator& x) const { return mpNode != x.mpNode; }
    };
    iterator begin() { return iterator(static_cast<Node*>(mAnchor.mpNext)); }
    iterator end() { return iterator(static_cast<Node*>(&mAnchor)); }
};
}
namespace XHTML {
struct Element : Node {
    uint32_t pad0c[3];
    NodeList mChildNodes;                                // +0x18
    uint32_t pad20[2];
    int mElementType;                                    // +0x28
    const wchar_t* GetAttrValue(const wchar_t* name);    // 0x008e45b0

};
}
namespace XHTML {
struct FormControl : Element {
    void SetControl(IWindow* w);                         // 0x008e4b60
};
}
namespace Hash {
 uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int a);   // 0x00932f30
}
struct RefCounted {
    virtual int AddRef();
    virtual int Release();
    int mnRefCount;
    RefCounted() : mnRefCount(0) {}
};
struct FormControlRef : RefCounted {                     // vtable 0x013fdac0, 0xc bytes
    XHTML::FormControl* mpFormControl;
    FormControlRef(XHTML::FormControl* fc) : mpFormControl(fc) {}
    virtual int AddRef();
    virtual int Release();
};
enum {
    kWinFlagVisible = 1, kWinFlagEnabled = 2,
    kButtonTypeCheckBox = 2, kButtonTypeRadio = 3,
    kCommandSubmit = 0x344a710, kCommandReset = 0x344a711, kCommandRadio = 0x344a712,
    kFormControlProp = 0x344a0b7,
    kFormFillColor = 0xffccccee
};
template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
struct WinXHTML_s0099_4c80 {
    uint32_t pad0[0xa658 / 4];
    IDrawable* mFormCtrlDrawable[5];    // +0xa658 button, text edit, check box, radio, combo box
    float mVisibleArea[4];              // +0xa66c
    IWindow* mContentWindow;            // +0xa67c
    struct ScrollbarState {
        void* mScrollbar;
        IDrawable* mDrawable;
        int mEnabled;
        float mPreferredSize[2];
    } mScrollbars[2];                   // +0xa680 (horizontal), +0xa694 (vertical)

    void CreateFormControl(XHTML::FormControl* pFormControl);  // 0x00994c80 (WinXHTML::CreateFormControl)
};
__forceinline void BindFormControl(WinXHTML_s0099_4c80* self, XHTML::FormControl* pFormControl, IWindow* pWindow, const wchar_t* pDisabled)
{
    pFormControl->SetControl(pWindow);
    pWindow->SetUserObject(kFormControlProp, new ("FormControlRef", 0, 0, 0, 0) FormControlRef(pFormControl));
    if (pDisabled)
        pWindow->SetFlag(kWinFlagEnabled, false);
    self->mContentWindow->AddWindow(pWindow);
}
// ---- items of slice s00994c80 end

// ---- items of slice s00995b20 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct XDomElement;
class WinXHTML_ {
public:
    void FUN_00992e60(uint32_t v);
    void FUN_00992ea0(uint32_t v);
    void FUN_00995b20(XDomElement* fc, const uint16_t* value);
    void FUN_00995ea0(XDomElement* fc, void* out);
    bool FUN_009960b0(float x, float y, uint32_t button, uint32_t flags);
};
struct XDomElement {
    void*         mpVtbl;        // @0x00 (Node vtable)
    XDomElement*  mpNext;        // @0x04 (intrusive_list_node.mpNext)
    XDomElement*  mpPrev;        // @0x08
    uint32_t      mnType;        // @0x0c
    void*         mpDocument;    // @0x10
    XDomElement*  mpParent;      // @0x14
    XDomElement*  mpChildFirst;  // @0x18 (child-list anchor .mpNext)
    XDomElement*  mpChildLast;   // @0x1c
    uint8_t       mPad20[0x08];  // @0x20
    uint32_t      mElementType;  // @0x28
    uint8_t       mPad2c[0x18];  // @0x2c
    void*         mpFormObj;     // @0x44 (object whose vtable[3] yields IFormControlMgr)
};
typedef void* (__thiscall* XDomQueryFn)(void*, uint32_t);
// ---- items of slice s00995b20 end

// @ 0x00992dc0
void __fastcall FUN_00992dc0(char* self, int, u32 mask, u8 set)
{
    if (set) st32(self, 0xa84c, ld32(self, 0xa84c) | mask);
    else     st32(self, 0xa84c, ld32(self, 0xa84c) & ~mask);
}

// @ 0x00992e00
void __fastcall FUN_00992e00(char* self, int, i32 a, i32 b)
{
    if (a != (i32)ld32(self, 0xa858) || b != (i32)ld32(self, 0xa85c)) {
        st32(self, 0xa85c, (u32)b);
        st32(self, 0xa858, (u32)a);
        ((PageOps*)(self + 0x218))->SetSelectionRange(a, b);
        char* win = self + 4;
        (*(void(__fastcall**)(char*))(*(u32*)win + 0x90))(win);
    }
}

// @ 0x00992e60
void __fastcall FUN_00992e60(char* self, int, i32 v)
{
    if (v != (i32)ld32(self, 0xa8dc)) {
        char* win = self + 4;
        i32 cur = ((SlotGetInt)(*(u32*)win + 0x24))(win);
        if (cur == (i32)ld32(self, 0xa8dc)) {
            ((SlotSetInt)(*(u32*)win + 0x78))(win, v);
        }
        st32(self, 0xa8dc, (u32)v);
    }
}

// @ 0x00992ea0
void __fastcall FUN_00992ea0(char* self, int, i32 v)
{
    if (v != (i32)ld32(self, 0xa8e0)) {
        char* win = self + 4;
        i32 cur = ((SlotGetInt)(*(u32*)win + 0x24))(win);
        if (cur == (i32)ld32(self, 0xa8e0)) {
            ((SlotSetInt)(*(u32*)win + 0x78))(win, v);
        }
        st32(self, 0xa8e0, (u32)v);
    }
}

// @ 0x00992ee0
void __fastcall FUN_00992ee0(char* self, int, i32 show)
{
    if (show != 0 || ld8(self, 0xa8e4) != 0) {
        char* win = self + 4;
        u32 fn = ld32(win, 0x114);
        void* msg[5];
        msg[0] = 0; msg[1] = 0; msg[2] = 0; msg[3] = 0; msg[4] = (void*)(size_t)show;
        ((void(__fastcall*)(char*, void*))fn)(win, msg);
        st8(self, 0xa8e4, show != 0);
    }
}

// @ 0x00993000
void __fastcall WinXHTML_dtor(char* self, int)
{
    char* doc = (char*)ld32(self, 0x23c);
    st32(self, 0, 0x1446590u);                  // vtbl WinXHTML
    st32(self, 4, 0x1446470u);
    st32(self, 0x20c, 0x1446440u);
    st32(self, 0x210, 0x144642cu);
    if (doc) {
        DestroyFormControls(doc);
        st32(doc, 0x38, 0);
        st32(doc, 0x3c, 0);
    }
    // release two lists of intrusive objects (two 0x14-stride slots below +0xa8b4)
    char* p = self + 0xa8b4;
    for (int i = 1; i >= 0; --i) {
        char* a = *(char**)(p - 0x10);
        p -= 0x14;
        if (a) RefObj_release(a);
        char* b = *(char**)p;
        if (b) RefObj_release(b);
    }
    char* s1 = (char*)ld32(self, 0xa888);
    if (s1) RefObj_release(s1);
    char* q = self + 0xa878;
    for (int i = 4; i >= 0; --i) {
        char* a = *(char**)(q - 4);
        q -= 4;
        if (a) RefObj_release(a);
    }
    Page_dtor(self + 0x218);
    st32(self, 0x210, 0x13eb938u);              // GmeEditorResBase vtable
    st32(self, 0x20c, 0x13eb938u);
    Obj962740_f(self);
}

// @ 0x00993130
u8 __fastcall WinXHTML_DoMessage(char* self, int, char* msg)
{
    if (ld32(msg, 8) != (i32)0x8ef0c8dd) {
        FUN_00950bb0(msg);
        return 0;
    }
    float nv;
    char* a = (char*)ld32(self, 0xa88c);
    if (a) nv = (float)(*(i32(__fastcall**)(char*))(*(u32*)a + 0x28))(a);
    else   nv = 0.0f;
    float nh;
    char* b = (char*)ld32(self, 0xa8a0);
    if (b) nh = (float)(*(i32(__fastcall**)(char*))(*(u32*)b + 0x28))(b);
    else   nh = 0.0f;

    if (nv != ldf(self, 0xa8b4) || nh != ldf(self, 0xa8b8)) {
        char* sb = (char*)ld32(self, 0xa888);
        stf(self, 0xa8b4, nv);
        stf(self, 0xa8b8, nh);
        // +0x64: thiscall, takes -nv and -nh pushed as two floats.
        (*(void(__fastcall**)(char*, int, float, float))(*(u32*)sb + 0x64))(sb, 0, -nv, -nh);
        char* win = self + 4;
        (*(void(__fastcall**)(char*))(*(u32*)win + 0x90))(win);
    }
    return 1;
}

// @ 0x00993200
u8 __fastcall FUN_00993200(char* self, int, i32, i32, i32, i32 lineOffset)
{
    char* sb = (char*)ld32(self, 0xa8a0);
    if (sb) {
        u32 vt = *(u32*)sb;
        i32 range = (*(i32(__fastcall**)(char*, int))(vt + 0x28))(sb, 1);
        i32 v = lineOffset + ((lineOffset >> 31) & 3);
        (*(void(__fastcall**)(char*, int))(vt + 0x24))(sb, range - (v >> 2));
    }
    return 1;
}

// @ 0x00993240
u8 __fastcall WinXHTML_OnCtrlValueChanged(char* self, int, u32 id, char* ctrl)
{
    if (id == 0x344a712u) {
        char* o = (char*)(*(void*(__fastcall**)(char*, u32, int))(*(u32*)ctrl + 0xb4))(ctrl, 0x344a0b7u, 0);
        if (o) {
            char* p = (char*)(*(void*(__fastcall**)(char*, u32, int))(*(u32*)o + 0xc))(o, 0x344a654u, 0);
            if (p) {
                char* t = (char*)ld32(p, 8);
                if (t) {
                    (*(void(__fastcall**)(char*, int, void*))(*(u32*)t + 0x24))(t, 5, (void*)0);
                }
            }
        }
        return 1;
    }
    if (id >= 0xcf454afau && id <= 0xcf454afbu) return 1;
    return 0;
}

// @ 0x009932c0
u8 __fastcall FUN_009932c0(char* self, int, char* ctrl, u32 id)
{
    char* o = (char*)(*(void*(__fastcall**)(char*, u32, int))(*(u32*)ctrl + 0xb4))(ctrl, 0x344a0b7u, 0);
    if (!o) return 0;
    char* p = (char*)(*(void*(__fastcall**)(char*, u32, int))(*(u32*)o + 0xc))(o, 0x344a654u, 0);
    if (!p) return 0;
    char* t = (char*)ld32(p, 8);
    if (!t) return 0;
    if (id != 0x344a710u && id != 0x344a711u) return 0;
    int which = (id == 0x344a710u) ? 2 : 3;
    if (!((ld8(self, 0xa84c) & which) && (i32)ld32(self, 0xa8d8) == (i32)(size_t)t
          && Stopwatch_GetElapsedTimeFloat(self + 0xa8c0) <= 0.75f)) {
        (*(void(__fastcall**)(char*, int, void*))(*(u32*)t + 0x24))(t, which, (void*)0);
    }
    st32(self, 0xa8d8, (u32)(size_t)t);
    FUN_00571e80(self + 0xa8c0);
    return 1;
}

// @ 0x00993390
void __fastcall FUN_00993390(char* self, int)
{
    typedef void (__fastcall *Fn)(char*);
    char* doc = *(char**)(self + 0x23c);
    if (doc) ((Fn)RemoveAllChildren)(doc);
    ((Fn)Page_NotifyImagesAbandoned)(self + 0x218);
}

// @ 0x009933b0
u8 __fastcall WinXHTML_OnRebuild(char* self, int, char* ctx)
{
    char* batch = RenderCtx_Begin2D(ctx, 0);

    float neg = g_negMask;                     // [0x13eb8b0]
    float w = ldf(self, 0x90) - ldf(self, 0x88);
    float h = ldf(self, 0x94) - ldf(self, 0x8c);

    float src[4];                              // first local rect: 0,0,w,h
    src[0] = 0.0f;
    src[1] = 0.0f;
    src[2] = ldf(self, 0x90) - ldf(self, 0x88);
    src[3] = ldf(self, 0x94) - ldf(self, 0x8c);

    float sx = ldf(self, 0xa8b4) * -1.0f;
    float sy = ldf(self, 0xa8b8) * -1.0f;
    (void)neg;

    float dst[4];                              // second local rect: sx,sy,sx+w,sy+h
    dst[0] = sx;
    dst[1] = sy;
    dst[2] = w + sx;
    dst[3] = h + sy;

    Page_Render(self + 0x218, batch, dst, src);
    RenderCtx_End2D(ctx);
    return 1;
}

// @ 0x00993490
void __fastcall WinXHTML_SetScrollPosition(char* self, int, float* pos)
{
    if (ldf(self, 0xa8b4) != pos[0] || ldf(self, 0xa8b8) != pos[1]) {
        char* vb = (char*)ld32(self, 0xa8a0);
        stf(self, 0xa8b4, pos[0]);
        stf(self, 0xa8b8, pos[1]);
        if (vb) (*(void(__fastcall**)(char*, int, int))(*(u32*)vb + 0x24))(vb, (i32)pos[1], 0);
        char* hb = (char*)ld32(self, 0xa88c);
        if (hb) (*(void(__fastcall**)(char*, int, int))(*(u32*)hb + 0x24))(hb, (i32)pos[0], 0);
        char* win = self + 4;
        (*(void(__fastcall**)(char*))(*(u32*)win + 0x90))(win);
    }
}

// @ 0x00993520
void EA::UTFWinExtras::WinXHTML::CreateScrollbar(EA::UTFWinExtras::WinXHTML::tScrollbar param_2)
{
    char* self = (char*)this;
    char* st = self + param_2 * 0x14 + 0xa88c;   // &mScrollbars[param_2+1]
    void** ppScrollbar = (void**)st;                       // +0 mScrollbar
    void** ppDrawable  = (void**)(st + 4);                 // +4 mDrawable
    int*   pEnabled    = (int*)(st + 8);                   // +8 mEnabled
    float* pPref       = (float*)(st + 0xc);               // +0xc mPreferredSize

    if (*pEnabled == 0) {
        // kScrollbarNever: tear the scrollbar down
        void* sb = *ppScrollbar;
        if (sb == 0)
            return;
        void* iface = VF(sb, 0x10, void*(__thiscall*)(void*))(sb);
        VF(self + 4, 0xe0, void(__thiscall*)(void*, void*))(self + 4, iface);
        void* old = *ppScrollbar;
        if (old == 0)
            return;
        *ppScrollbar = 0;
        VF(old, 4, void(__thiscall*)(void*))(old);
        return;
    }

    // create the scrollbar if absent
    if (*ppScrollbar == 0) {
        void* mem = FUN_009512d0(0x2d0, 8, "UTFWin/WinXHTML/Scrollbar", FUN_009512c0());
        void* sb = 0;
        if (mem != 0) {
            void* c = ((void*(__thiscall*)(void*))WinScrollbar_ctor)(mem);
            if (c != 0)
                sb = (char*)c + 0x20c;
        }
        void* old = *ppScrollbar;
        if (sb != old) {
            if (sb != 0)
                VF(sb, 0, void(__thiscall*)(void*))(sb);
            *ppScrollbar = sb;
            if (old != 0)
                VF(old, 4, void(__thiscall*)(void*))(old);
        }
        void* iface = VF(*ppScrollbar, 0x10, void*(__thiscall*)(void*))(*ppScrollbar);
        VF(iface, 0x7c, void(__thiscall*)(void*, int, int))(iface, 0x200, 1);
        iface = VF(*ppScrollbar, 0x10, void*(__thiscall*)(void*))(*ppScrollbar);
        VF(iface, 0x7c, void(__thiscall*)(void*, int, int))(iface, 0x40, 1);
        iface = VF(*ppScrollbar, 0x10, void*(__thiscall*)(void*))(*ppScrollbar);
        VF(iface, 0x14, void(__thiscall*)(void*, int))(iface, param_2 == 1 ? 2 : 1);
        iface = VF(*ppScrollbar, 0x10, void*(__thiscall*)(void*))(*ppScrollbar);
        VF(self + 4, 0xd8, void(__thiscall*)(void*, void*))(self + 4, iface);
    }

    // choose the drawable
    if (*ppDrawable == 0) {
        void* mem = FUN_009512d0(0x2c, 4, "UTFWin/WinXHTML/ScrollbarDrawable", FUN_009512c0());
        void* d = 0;
        if (mem != 0)
            d = ScrollbarDrawable_ctor(mem);
        VF(*ppScrollbar, 0x5c, void(__thiscall*)(void*, void*))(*ppScrollbar, d);
    } else {
        void* r;
        if (*ppDrawable != 0)
            r = VF(*ppDrawable, 0xc, void*(__thiscall*)(void*, unsigned))(*ppDrawable, 0x6ec581fd);
        else
            r = 0;
        VF(*ppScrollbar, 0x5c, void(__thiscall*)(void*, void*))(*ppScrollbar, r);
    }

    // size hints + attach to the parent window
    float sz = g_kScrollbarSize;
    pPref[0] = sz;
    pPref[1] = sz;
    int rel[5];
    rel[0] = 0x16; rel[1] = 0; rel[2] = 0; rel[3] = 0; rel[4] = 0;
    if (VF(self + 4, 0x14, void*(__thiscall*)(void*))(self + 4) != 0) {
        void* dw = VF(*ppScrollbar, 0x10, void*(__thiscall*)(void*))(*ppScrollbar);
        void* win = VF(self + 4, 0x14, void*(__thiscall*)(void*))(self + 4);
        void* a = VF(dw, 0x10, void*(__thiscall*)(void*, void*, void*, int))(dw, win, rel, 0);
        void* b = VF(*ppScrollbar, 0x10, void*(__thiscall*)(void*))(*ppScrollbar);
        VF(a, 0x10, void(__thiscall*)(void*, void*))(a, b);
    }
}

// @ 0x00993720
void EA::UTFWinExtras::WinXHTML::DestroyFormControl(EA::XHTML::DOM::FormControl * param_2)
{
    char* self = (char*)this;
    void* ctl = *(void**)((char*)param_2 + 0x44);
    if (ctl == 0)
        return;
    void* piVar2 = VF(ctl, 0xc, void*(__thiscall*)(void*, unsigned))(ctl, 0xeeee8218);
    if (piVar2 == 0)
        return;
    int iVar3 = VF(piVar2, 0x40, int(__thiscall*)(void*))(piVar2);
    if (iVar3 != 1) {
        void* mgr = Text_GetStyleManager(1);
        if (mgr != 0)
            ((void(__thiscall*)(void*, int))Text_StyleManagerRemoveStyle)(mgr, iVar3);
    }
    if (VF(piVar2, 0x10, int(__thiscall*)(void*))(piVar2) != 0)
        VF(*(void**)(self + 0xa67c), 0xe0, void(__thiscall*)(void*, void*))(*(void**)(self + 0xa67c), piVar2);
    ((void(__thiscall*)(void*, void*))XHTML_DOM_FormControl_SetControl)(param_2, 0);
}

// @ 0x009937a0
void WinXHTML::SetFormControlStyle(void* param_2, void* param_3)
{
    char* self = (char*)this;
    void* pfc = *(void**)((char*)param_2 + 0x44);
    if (pfc == 0)
        return;
    void* piVar1 = VF(pfc, 0xc, void*(__thiscall*)(void*, unsigned))(pfc, 0xeeee8218);
    if (piVar1 == 0)
        return;
    void* mgr = Text_GetStyleManager(1);
    if (mgr != 0) {
        unsigned key = ((int(__thiscall*)(void*, int, void*))Text_StyleManagerAddStyle)(mgr, -2, (char*)param_3 + 0xc);
        VF(piVar1, 0x84, void(__thiscall*)(void*, unsigned))(piVar1, key);
        void* q = VF(piVar1, 0xc, void*(__thiscall*)(void*, unsigned))(piVar1, 0xaf1ee902);
        if (q != 0)
            VF(q, 0x34, void(__thiscall*)(void*, unsigned))(q, key);
    }
    void* r = VF(piVar1, 0xc, void*(__thiscall*)(void*, unsigned))(piVar1, 0x8ed27e7a);
    if (r != 0) {
        VF(r, 0x4c, void(__thiscall*)(void*, int, unsigned))(r, 0, *(unsigned*)(self + 0x28c));
    } else {
        r = VF(piVar1, 0xc, void*(__thiscall*)(void*, unsigned))(piVar1, 0x2f5528d9);
        if (r != 0) {
            VF(r, 0x48, void(__thiscall*)(void*, int, unsigned))(r, 0, *(unsigned*)(self + 0x28c));
            VF(r, 0x48, void(__thiscall*)(void*, int, unsigned))(r, 1, *(unsigned*)(self + 0x2bc));
        } else {
            r = VF(piVar1, 0xc, void*(__thiscall*)(void*, unsigned))(piVar1, 0xaf1ee902);
            if (r != 0) {
                VF(r, 0x3c, void(__thiscall*)(void*, unsigned, int))(r, *(unsigned*)(self + 0x28c), 0);
                VF(r, 0x3c, void(__thiscall*)(void*, unsigned, int))(r, *(unsigned*)(self + 0x2bc), 1);
                VF(r, 0x4c, void(__thiscall*)(void*, int))(r, 0);
            }
        }
    }
    void* s = VF(piVar1, 0xa8, void*(__thiscall*)(void*))(piVar1);
    if (s != 0) {
        void* t = VF(s, 0xc, void*(__thiscall*)(void*, unsigned))(s, 0x30d54ac);
        if (t != 0) {
            *(unsigned*)((char*)t + 0x10) = *(unsigned*)(self + 0x2c0);
            return;
        }
    }
    VF(piVar1, 0xac, void(__thiscall*)(void*, unsigned))(piVar1, *(unsigned*)(self + 0x2c0));
}

// @ 0x00993b70
void WinXHTML::SetFormControlArea(void* param_2, void* param_3)
{
    char* page = (char*)this;
    void* pfc = *(void**)((char*)param_2 + 0x44);
    if (pfc == 0)
        return;
    void* piVar1 = VF(pfc, 0xc, void*(__thiscall*)(void*, unsigned))(pfc, 0xeeee8218);
    if (piVar1 == 0)
        return;
    VF(piVar1, 0x60, void(__thiscall*)(void*, void*))(piVar1, param_3);
}

// @ 0x00993ba0
void EA::UTFWinExtras::WinXHTML::SetFormControlDrawable(int param_2, EA::UTFWin::IDrawable * param_3)
{
    char* self = (char*)this;
    if ((unsigned)param_2 > 4)
        return;
    void** slot = (void**)(self + param_2 * 4 + 0xa864);   // mFormCtrlDrawable[param_2]
    void* old = *slot;
    if (param_3 == old)
        return;
    if (param_3 != 0)
        VF(param_3, 0, void(__thiscall*)(void*))(param_3);
    *slot = param_3;
    if (old != 0)
        VF(old, 4, void(__thiscall*)(void*))(old);
}

// @ 0x00993bf0
void EA::UTFWinExtras::WinXHTML::SerUpdate()
{
    CreateScrollbar((EA::UTFWinExtras::WinXHTML::tScrollbar)1);
    CreateScrollbar((EA::UTFWinExtras::WinXHTML::tScrollbar)0);
    ((void(__thiscall*)(void*))Win_SerUpdate)(this);
}

// @ 0x00993c10
WinXHTML::WinXHTML()
{
    char* self = (char*)this;
    ((void(__thiscall*)(void*))WinWindow_ctor)(self);
    *(void**)(self + 0x20c) = (void*)0x14463ec;
    *(void**)(self + 0x210) = (void*)0x1446418;
    char* page = self + 0x218;
    *(void**)self = (void*)0x1446590;
    *(void**)(self + 4) = (void*)0x1446470;
    *(void**)(self + 0x20c) = (void*)0x1446440;
    *(void**)(self + 0x210) = (void*)0x144642c;
    *(unsigned char*)(self + 0x214) = 0;
    ((void(__thiscall*)(void*))FUN_008ec790)(page);
    *(int*)(self + 0xa84c) = 3;
    *(void**)(self + 0xa850) = 0;
    *(void**)(self + 0xa854) = 0;
    *(void**)(self + 0xa860) = 0;
    *(void**)(self + 0xa864) = 0;
    *(void**)(self + 0xa868) = 0;
    *(void**)(self + 0xa86c) = 0;
    *(void**)(self + 0xa870) = 0;
    *(void**)(self + 0xa874) = 0;
    *(void**)(self + 0xa888) = 0;
    *(void**)(self + 0xa88c) = 0;
    *(float*)(self + 0xa878) = 0.0f;
    *(float*)(self + 0xa87c) = 0.0f;
    *(float*)(self + 0xa880) = 0.0f;
    *(float*)(self + 0xa884) = 0.0f;
    *(void**)(self + 0xa890) = 0;
    *(void**)(self + 0xa8a0) = 0;
    *(void**)(self + 0xa8a4) = 0;
    *(float*)(self + 0xa8b4) = 0.0f;
    *(float*)(self + 0xa8b8) = 0.0f;
    // Stopwatch::Stopwatch(self+0xa8c0, 5, 1)
    ((void(__thiscall*)(void*, int, int))Stopwatch_ctor)(self + 0xa8c0, 5, 1);
    *(void**)(self + 0xa8d8) = 0;
    *(int*)(self + 0xa8dc) = 0x1002;
    *(int*)(self + 0xa8e0) = 0x1006;
    *(unsigned char*)(self + 0xa8e4) = 0;
    void* ss = XHTML_Style_CreateDefaultStylesheet();
    ((void(__thiscall*)(void*, void*))Page_FUN_008eb830)(page, ss);
    void* root = *(void**)(self + 0x240);
    VF(root, 4, void(__thiscall*)(void*))(root);
    void* a4 = *(void**)(self + 0xa8a4);
    if (a4 != 0) {
        *(void**)(self + 0xa8a4) = 0;
        VF(a4, 4, void(__thiscall*)(void*))(a4);
    }
    void* a0 = *(void**)(self + 0xa8a0);
    if (a0 != 0) {
        *(void**)(self + 0xa8a0) = 0;
        VF(a0, 4, void(__thiscall*)(void*))(a0);
    }
    *(void**)(self + 0xa8a8) = (void*)1;
    void* sb1 = *(void**)(self + 0xa890);
    if (sb1 != 0) {
        *(void**)(self + 0xa890) = 0;
        VF(sb1, 4, void(__thiscall*)(void*))(sb1);
    }
    void* dr1 = *(void**)(self + 0xa88c);
    if (dr1 != 0) {
        *(void**)(self + 0xa88c) = 0;
        VF(dr1, 4, void(__thiscall*)(void*))(dr1);
    }
    *(void**)(self + 0xa894) = (void*)1;
    // ContentWindow
    {
        void* mem = FUN_009512d0(0x20c, 4, "UTFWin/WinXHTML/ContentWindow", FUN_009512c0());
        void* cw = 0;
        if (mem != 0) {
            void* c = ((void*(__thiscall*)(void*))WinWindow_ctor)(mem);
            if (c != 0)
                cw = (char*)c + 4;
        }
        void* old = *(void**)(self + 0xa888);
        if (cw != old) {
            if (cw != 0)
                VF(cw, 0, void(__thiscall*)(void*))(cw);
            *(void**)(self + 0xa888) = cw;
            if (old != 0)
                VF(old, 4, void(__thiscall*)(void*))(old);
        }
    }
    // FrameDrawable
    {
        void* mem = FUN_009512d0(0x60, 4, "UTFWin/WinXHTML/FrameDrawable", FUN_009512c0());
        char* fd = 0;
        if (mem != 0)
            fd = (char*)((void*(__thiscall*)(void*))FrameDrawable_ctor)(mem);
        float w = g_kDefaultWidth;
        *(int*)(fd + 0xc) = 5;
        *(float*)(fd + 0x58) = w;
        *(float*)(fd + 0x50) = w;
        *(float*)(fd + 0x54) = w;
        *(float*)(fd + 0x4c) = w;
        *(int*)(fd + 0x10) = (int)0xffccccee;
        void* old = *(void**)(self + 0xa868);
        if (fd != old) {
            VF(fd, 0, void(__thiscall*)(void*))(fd);
            *(void**)(self + 0xa868) = fd;
            if (old != 0)
                VF(old, 4, void(__thiscall*)(void*))(old);
        }
    }
    // StdDrawable -> drawables 0xa864, 0xa86c, 0xa870, content window
    {
        void* mem = FUN_009512d0(0x7c, 4, "UTFWin/WinXHTML/StdDrawable", FUN_009512c0());
        void* sd = 0;
        if (mem != 0)
            sd = ((void*(__thiscall*)(void*))StdDrawable_ctor)(mem);
        void* old = *(void**)(self + 0xa864);
        if (sd != old) {
            if (sd != 0)
                VF(sd, 0, void(__thiscall*)(void*))(sd);
            *(void**)(self + 0xa864) = sd;
            if (old != 0)
                VF(old, 4, void(__thiscall*)(void*))(old);
        }
        old = *(void**)(self + 0xa86c);
        if (sd != old) {
            if (sd != 0)
                VF(sd, 0, void(__thiscall*)(void*))(sd);
            *(void**)(self + 0xa86c) = sd;
            if (old != 0)
                VF(old, 4, void(__thiscall*)(void*))(old);
        }
        old = *(void**)(self + 0xa870);
        if (sd != old) {
            if (sd != 0)
                VF(sd, 0, void(__thiscall*)(void*))(sd);
            *(void**)(self + 0xa870) = sd;
            if (old != 0)
                VF(old, 4, void(__thiscall*)(void*))(old);
        }
        old = *(void**)(self + 0xa874);
        if (sd != old) {
            if (sd != 0)
                VF(sd, 0, void(__thiscall*)(void*))(sd);
            *(void**)(self + 0xa874) = sd;
            if (old != 0)
                VF(old, 4, void(__thiscall*)(void*))(old);
        }
    }
    // ComboBoxDrawable
    {
        void* mem = FUN_009512d0(0x1c, 4, "UTFWin/WinXHTML/ComboBoxDrawable", FUN_009512c0());
        void* cb = 0;
        if (mem != 0)
            cb = ((void*(__thiscall*)(void*))ComboBoxDrawable_ctor)(mem);
        void* old = *(void**)(self + 0xa878);
        if (cb != old) {
            if (cb != 0)
                VF(cb, 0, void(__thiscall*)(void*))(cb);
            *(void**)(self + 0xa878) = cb;
            if (old != 0)
                VF(old, 4, void(__thiscall*)(void*))(old);
        }
    }
}

// @ 0x00993fa0
bool EA::UTFWinExtras::WinXHTML::Init()
{
    char* self = (char*)this;
    VF(self + 4, 0x7c, void(__thiscall*)(void*, int, int))(self + 4, 0x400, 1);
    void* sb = *(void**)(self + 0xa888);
    if (sb != 0)
        VF(self + 4, 0xd8, void(__thiscall*)(void*, void*))(self + 4, sb);
    CreateScrollbar((EA::UTFWinExtras::WinXHTML::tScrollbar)1);
    CreateScrollbar((EA::UTFWinExtras::WinXHTML::tScrollbar)0);
    return ((bool(__thiscall*)(void*))Window_Initialize)(this);
}

// @ 0x00993ff0
bool EA::UTFWinExtras::WinXHTML::Shutdown()
{
    char* self = (char*)this;
    if (*(void**)(self + 0x23c) != 0)
        ((void(__thiscall*)(void*))DocX_RemoveAllChildren)(*(void**)(self + 0x23c));
    ((void(__thiscall*)(void*))Page_NotifyImagesAbandoned)(self + 0x218);
    void* p;
    p = *(void**)(self + 0xa8a0);
    if (p != 0) { *(void**)(self + 0xa8a0) = 0; VF(p, 4, void(__thiscall*)(void*))(p); }
    p = *(void**)(self + 0xa8a4);
    if (p != 0) { *(void**)(self + 0xa8a4) = 0; VF(p, 4, void(__thiscall*)(void*))(p); }
    p = *(void**)(self + 0xa88c);
    if (p != 0) { *(void**)(self + 0xa88c) = 0; VF(p, 4, void(__thiscall*)(void*))(p); }
    p = *(void**)(self + 0xa890);
    if (p != 0) { *(void**)(self + 0xa890) = 0; VF(p, 4, void(__thiscall*)(void*))(p); }
    p = *(void**)(self + 0xa888);
    if (p != 0)
        VF(self + 4, 0xdc, void(__thiscall*)(void*, void*))(self + 4, p);
    p = *(void**)(self + 0xa888);
    if (p != 0) { *(void**)(self + 0xa888) = 0; VF(p, 4, void(__thiscall*)(void*))(p); }
    if (*(unsigned char*)(self + 0xa8e4) != 0) {
        int msg[5];
        msg[0] = 0x51a1a2e; msg[1] = 0; msg[2] = 0; msg[3] = 0; msg[4] = 0;
        VF(self + 4, 0x114, void(__thiscall*)(void*, int*))(self + 4, msg);
        *(unsigned char*)(self + 0xa8e4) = 0;
    }
    return ((bool(__thiscall*)(void*))Window_Shutdown)(this);
}

// @ 0x009940f0
void EA::UTFWinExtras::WinXHTML::CalculateVisibleArea()
{
    char* self = (char*)this;
    float w = *(float*)(self + 0x90) - *(float*)(self + 0x88);
    float h = *(float*)(self + 0x94) - *(float*)(self + 0x8c);
    *(float*)(self + 0xa878) = 0.0f;
    *(float*)(self + 0xa87c) = 0.0f;
    *(float*)(self + 0xa880) = w;
    *(float*)(self + 0xa884) = h;
    void* sb0 = *(void**)(self + 0xa8a0);
    if (sb0 != 0) {
        void* iface = VF(sb0, 0x10, void*(__thiscall*)(void*))(sb0);
        if ((VF(iface, 0x28, unsigned(__thiscall*)(void*))(iface) & 1) != 0)
            *(float*)(self + 0xa880) = *(float*)(self + 0xa880) - *(float*)(self + 0xa8ac);
    }
    void* sb1 = *(void**)(self + 0xa88c);
    if (sb1 != 0) {
        void* iface = VF(sb1, 0x10, void*(__thiscall*)(void*))(sb1);
        if ((VF(iface, 0x28, unsigned(__thiscall*)(void*))(iface) & 1) != 0)
            *(float*)(self + 0xa884) = *(float*)(self + 0xa884) - *(float*)(self + 0xa89c);
    }
    if (*(float*)(self + 0xa880) < *(float*)(self + 0xa878)
        || *(float*)(self + 0xa884) < *(float*)(self + 0xa87c)) {
        *(float*)(self + 0xa880) = *(float*)(self + 0xa878);
        *(float*)(self + 0xa884) = *(float*)(self + 0xa87c);
    }
}

// @ 0x009941e0
void EA::UTFWinExtras::WinXHTML::SetScrollbarDrawable(EA::UTFWinExtras::WinXHTML::tScrollbar param_2, EA::UTFWinControls::IScrollbarDrawable * param_3)
{
    char* self = (char*)this;
    void** slot = (void**)(self + param_2 * 0x14 + 0xa890);
    void* old = *slot;
    if (param_3 != old) {
        if (param_3 != 0)
            VF(param_3, 0, void(__thiscall*)(void*))(param_3);
        *slot = param_3;
        if (old != 0)
            VF(old, 4, void(__thiscall*)(void*))(old);
    }
    CreateScrollbar((EA::UTFWinExtras::WinXHTML::tScrollbar)1);
    CreateScrollbar((EA::UTFWinExtras::WinXHTML::tScrollbar)0);
}

// @ 0x00994240
void WinXHTML_s0099_4240::FUN_00994240()
{
    char* self = (char*)this;
    bool flag1;
    bool flag2;
    float saved[4];

    saved[0] = *(float*)(self + 0xa878);
    saved[1] = *(float*)(self + 0xa87c);
    saved[2] = *(float*)(self + 0xa880);
    saved[3] = *(float*)(self + 0xa884);
    CalculateVisibleArea();
    if (*(float*)(self + 0xa878) != saved[0] || *(float*)(self + 0xa87c) != saved[1]
        || *(float*)(self + 0xa880) != saved[2] || *(float*)(self + 0xa884) != saved[3])
        ((XHTMLPage*)(self + 0x218))->Resize(*(float*)(self + 0xa880) - *(float*)(self + 0xa878),
                                             *(float*)(self + 0xa884) - *(float*)(self + 0xa87c));

    saved[0] = *(float*)(self + 0xa878);
    saved[1] = *(float*)(self + 0xa87c);
    saved[2] = *(float*)(self + 0xa880);
    saved[3] = *(float*)(self + 0xa884);
    if (*(int*)(self + 0xa8a8) == 2)
        flag1 = 1;
    else if (*(int*)(self + 0xa8a8) == 1
             && (float)*(int*)(self + 0x250) > *(float*)(self + 0xa884) - *(float*)(self + 0xa87c))
        flag1 = 1;
    else
        flag1 = 0;
    if (*(void**)(self + 0xa8a0) != 0) {
        void* sb = *(void**)(self + 0xa8a0);
        void* w = VF(sb, 0x10, void*(__thiscall*)(void*))(sb);
        VF(w, 0x7c, void(__thiscall*)(void*, int, int))(w, 1, flag1);
    }

    CalculateVisibleArea();
    if (*(float*)(self + 0xa878) != saved[0] || *(float*)(self + 0xa87c) != saved[1]
        || *(float*)(self + 0xa880) != saved[2] || *(float*)(self + 0xa884) != saved[3])
        ((XHTMLPage*)(self + 0x218))->Resize(*(float*)(self + 0xa880) - *(float*)(self + 0xa878),
                                             *(float*)(self + 0xa884) - *(float*)(self + 0xa87c));

    if (*(int*)(self + 0xa894) == 2)
        flag2 = 1;
    else if (*(int*)(self + 0xa894) == 1
             && (float)*(int*)(self + 0x24c) > *(float*)(self + 0xa880) - *(float*)(self + 0xa878))
        flag2 = 1;
    else
        flag2 = 0;
    if (*(void**)(self + 0xa88c) != 0) {
        void* sb = *(void**)(self + 0xa88c);
        void* w = VF(sb, 0x10, void*(__thiscall*)(void*))(sb);
        VF(w, 0x7c, void(__thiscall*)(void*, int, int))(w, 1, flag2);
    }

    CalculateVisibleArea();
    if (*(void**)(self + 0xa8a0) != 0) {
        saved[0] = (*(float*)(self + 0x90) - *(float*)(self + 0x88)) - *(float*)(self + 0xa8ac);
        saved[1] = 0.0f;
        saved[2] = *(float*)(self + 0x90) - *(float*)(self + 0x88);
        saved[3] = *(float*)(self + 0x94) - *(float*)(self + 0x8c);
        if (flag2 != 0)
            saved[3] = saved[3] - *(float*)(self + 0xa89c);
        void* sb = *(void**)(self + 0xa8a0);
        void* w = VF(sb, 0x10, void*(__thiscall*)(void*))(sb);
        VF(w, 0x60, void(__thiscall*)(void*, void*))(w, saved);
        sb = *(void**)(self + 0xa8a0);
        VF(sb, 0x34, void(__thiscall*)(void*, int, int))(sb, (int)(float)*(int*)(self + 0x250), 1);
        sb = *(void**)(self + 0xa8a0);
        VF(sb, 0x3c, void(__thiscall*)(void*, int, int))(
            sb, (int)(*(float*)(self + 0xa884) - *(float*)(self + 0xa87c)), 1);
        sb = *(void**)(self + 0xa8a0);
        VF(sb, 0x4c, void(__thiscall*)(void*, int))(sb, 0x10);
        sb = *(void**)(self + 0xa8a0);
        w = VF(sb, 0x10, void*(__thiscall*)(void*))(sb);
        if (VF(w, 0x100, unsigned char(__thiscall*)(void*, int))(w, 1) == 0) {
            sb = *(void**)(self + 0xa8a0);
            VF(sb, 0x24, void(__thiscall*)(void*, int, int))(sb, (int)*(float*)(self + 0xa8b8), 0);
        }
    }

    if (*(void**)(self + 0xa88c) != 0) {
        saved[0] = 0.0f;
        saved[1] = (*(float*)(self + 0x94) - *(float*)(self + 0x8c)) - *(float*)(self + 0xa89c);
        saved[2] = *(float*)(self + 0x90) - *(float*)(self + 0x88);
        saved[3] = *(float*)(self + 0x94) - *(float*)(self + 0x8c);
        if (flag1 != 0)
            saved[2] = saved[2] - *(float*)(self + 0xa8ac);
        void* sb = *(void**)(self + 0xa88c);
        void* w = VF(sb, 0x10, void*(__thiscall*)(void*))(sb);
        VF(w, 0x60, void(__thiscall*)(void*, void*))(w, saved);
        sb = *(void**)(self + 0xa88c);
        VF(sb, 0x34, void(__thiscall*)(void*, int, int))(sb, (int)(float)*(int*)(self + 0x24c), 1);
        sb = *(void**)(self + 0xa88c);
        VF(sb, 0x3c, void(__thiscall*)(void*, int, int))(
            sb, (int)(*(float*)(self + 0xa880) - *(float*)(self + 0xa878)), 1);
        sb = *(void**)(self + 0xa88c);
        VF(sb, 0x4c, void(__thiscall*)(void*, int))(sb, 0x10);
        sb = *(void**)(self + 0xa88c);
        w = VF(sb, 0x10, void*(__thiscall*)(void*))(sb);
        if (VF(w, 0x100, unsigned char(__thiscall*)(void*, int))(w, 1) == 0) {
            sb = *(void**)(self + 0xa88c);
            VF(sb, 0x24, void(__thiscall*)(void*, int, int))(sb, (int)*(float*)(self + 0xa8b4), 0);
        }
    }
}

// @ 0x009946b0
void WinXHTMLCmd::OnDOMEvent(void* param_2)
{
    char* self = (char*)this;      // WinXHTML base + 0x210
    int*  p = (int*)param_2;

    if (p[1] == 4) {
        char* win = self - 0x20c;
        void* (__thiscall* fn1)(void*) =
            *(void*(__thiscall**)(void*))((char*)*(void**)win + 0x20);
        WinMsg m;
        m.code = 0x3326e8b;
        m.f3 = (int)fn1(win);
        m.f6 = p[0];
        void (__thiscall* fn2)(void*, void*) =
            *(void(__thiscall**)(void*, void*))((char*)*(void**)win + 0x114);
        m.f4 = 0;
        m.f5 = 0;
        fn2(win, &m);
        return;
    }
    if (p[1] == 6) {
        void* doc = *(void**)(self + 0x2c);
        if (doc != 0) {
            if (((DocX*)doc)->CheckFlag(1) == 0) {
                if (*(int*)(self + 0x44) == 0)
                    ((XHTMLPage*)(self + 8))->FUN_008edc30();
                ((XHTMLPage*)(self + 8))->Layout();
                ((WinXHTML_s0099_4240*)(self - 0x210))->FUN_00994240();
                char* win = self - 0x20c;
                void (__thiscall* fn)(void*) =
                    *(void(__thiscall**)(void*))((char*)*(void**)win + 0x90);
                fn(win);
            }
            if (((DocX*)doc)->CheckFlag(0) == 0) {
                char* win = self - 0x20c;
                void (__thiscall* fn)(void*, void*) =
                    *(void(__thiscall**)(void*, void*))((char*)*(void**)win + 0x114);
                WinMsg m;
                m.code = 0x51a1a2d;
                m.f3 = 0;
                m.f4 = 0;
                m.f5 = 0;
                m.f6 = (int)doc;
                fn(win, &m);
            }
        }
    }
}

// @ 0x009947f0
bool WinXHTML_s0099_4240::OnFocusChange(int param_2, void* param_3)
{
    char* self = (char*)this;

    if (param_2 != 1)
        return true;
    if (param_3 == (self != 0 ? (void*)(self + 4) : 0))
        return true;
    if (*(char*)(self + 0xa8e4) != 0) {
        void* w = (void*)(self + 4);
        void (__thiscall* fn)(void*, void*) =
            *(void(__thiscall**)(void*, void*))((char*)*(void**)w + 0x114);
        WinMsg m;
        m.code = 0x51a1a2e;
        m.f3 = 0;
        m.f4 = 0;
        m.f5 = 0;
        m.f6 = 0;
        fn(w, &m);
        *(char*)(self + 0xa8e4) = 0;
    }
    if (*(void**)(self + 0x478) != 0) {
        ((XHTMLPage*)(self + 0x218))->SetImageRequester(0, 0);
        ((XHTMLPage*)(self + 0x218))->FUN_008ecc90(0);
        ((XHTMLPage*)(self + 0x218))->Layout();
        FUN_00994240();
    }
    VF(self + 4, 0x90, void(__thiscall*)(void*))(self + 4);
    return true;
}

// @ 0x009948a0
bool WinXHTML_s0099_4240::FUN_009948a0(float param_2, float param_3, int)
{
    char* self = (char*)this;
    float pt[2];
    int   hit[7];

    pt[0] = *(float*)(self + 0xa8b4) + param_2;
    int target = *(int*)(self + 0xa8dc);
    pt[1] = *(float*)(self + 0xa8b8) + param_3;
    unsigned char ok = ((XHTMLPage*)(self + 0x218))->Pick(pt, hit);
    if (ok != 0) {
        if (hit[4] != 0)
            target = hit[4];
        else if (hit[1] != 0)
            target = *(int*)(self + 0xa8e0);
    }
    VF(self + 4, 0x78, void(__thiscall*)(void*, int))(self + 4, target);
    unsigned& rng = *(unsigned*)(self + 0xa850);
    rng = (unsigned)hit[6];
    if (hit[0] != 0 && *(void**)(self + 0x47c) != (void*)hit[0]) {
        void* elem = ((DOMNode*)(void*)hit[0])->AsElement();
        if (elem != 0) {
            void* title = ((DOMElement*)elem)->GetAttrValue(DAT_01550104);
            FUN_00992ee0(title);
        } else if (*(char*)(self + 0xa8e4) != 0) {
            void* w = (void*)(self + 4);
            void (__thiscall* fn)(void*, void*) =
                *(void(__thiscall**)(void*, void*))((char*)*(void**)w + 0x114);
            WinMsg m;
            m.code = 0x51a1a2e;
            m.f3 = 0;
            m.f4 = 0;
            m.f5 = 0;
            m.f6 = 0;
            fn(w, &m);
            *(char*)(self + 0xa8e4) = 0;
        }
    }
    unsigned char changed = ((XHTMLPage*)(self + 0x218))->FUN_008ecc90((void*)hit[0]);
    if (*(int*)(self + 0xa860) == 2) {
        if (hit[1] != *(int*)(self + 0x478)) {
            ((XHTMLPage*)(self + 0x218))->SetImageRequester((void*)hit[1], 2);
            goto laidout;
        }
    } else if (*(int*)(self + 0xa860) == 0) {
        if (hit[1] != *(int*)(self + 0x478)) {
            ((XHTMLPage*)(self + 0x218))->SetImageRequester((void*)hit[1], 4);
            goto laidout;
        }
    } else {
        unsigned& a = *(unsigned*)(self + 0xa854);
        FUN_00992e00((a < rng) ? a : rng, (rng < a) ? rng : a);
    }
    if (changed == 0)
        return true;
laidout:
    ((XHTMLPage*)(self + 0x218))->Layout();
    FUN_00994240();
    VF(self + 4, 0x90, void(__thiscall*)(void*))(self + 4);
    return true;
}

// @ 0x00994a40
bool WinXHTML_s0099_4240::OnMouseDown(float param_2, float param_3, int, int param_5)
{
    char* self = (char*)this;

    if (param_5 == 8) {
        VF(self, 0x44, void(__thiscall*)(void*, float, float, int))(self, param_2, param_3, 8);
        void* o = *(void**)(self + 0x34);
        VF(o, 0x58, void(__thiscall*)(void*, int, void*))(o, 1, self + 4);
        if (*(void**)(self + 0x478) != 0) {
            *(int*)(self + 0xa860) = 2;
            ((XHTMLPage*)(self + 0x218))->SetImageRequester(*(void**)(self + 0x478), 2);
            ((XHTMLPage*)(self + 0x218))->Layout();
            FUN_00994240();
            VF(self + 4, 0x90, void(__thiscall*)(void*))(self + 4);
            return true;
        }
        if ((*(unsigned char*)(self + 0xa84c) & 1) != 0) {
            FUN_00992e00(0, 0);
            *(int*)(self + 0xa854) = *(int*)(self + 0xa850);
            *(int*)(self + 0xa860) = 1;
        }
        return true;
    }
    return false;
}

// @ 0x00994b00
void WinXHTML_s0099_4240::SetDocument(void* param_2)
{
    char* self = (char*)this;
    void* doc = *(void**)(self + 0x23c);

    if (doc != 0) {
        ((DOMDocument*)doc)->DestroyFormControls();
        *(int*)((char*)doc + 0x38) = 0;
        *(int*)((char*)doc + 0x3c) = 0;
    }
    if (*(char*)(self + 0xa8e4) != 0) {
        void* w = (void*)(self + 4);
        void (__thiscall* fn)(void*, void*) =
            *(void(__thiscall**)(void*, void*))((char*)*(void**)w + 0x114);
        WinMsg m;
        m.code = 0x51a1a2e;
        m.f3 = 0;
        m.f4 = 0;
        m.f5 = 0;
        m.f6 = 0;
        fn(w, &m);
        *(char*)(self + 0xa8e4) = 0;
    }
    ((XHTMLPage*)(self + 0x218))->FUN_008edc90(param_2);
    if (param_2 != 0) {
        *(int*)((char*)param_2 + 0x38) = (int)(self + 0x20c);
        *(int*)((char*)param_2 + 0x3c) = (int)(self + 0x210);
        ((DOMDocument*)param_2)->FUN_008e2870();
    }
    ((XHTMLPage*)(self + 0x218))->Resize(*(float*)(self + 0xa880) - *(float*)(self + 0xa878),
                                         *(float*)(self + 0xa884) - *(float*)(self + 0xa87c));
    if (((DocX*)param_2)->CheckFlag(1) == 0) {
        ((XHTMLPage*)(self + 0x218))->Layout();
        FUN_00994240();
        VF(self + 4, 0x90, void(__thiscall*)(void*))(self + 4);
    }
    if (((DocX*)param_2)->CheckFlag(0) == 0) {
        void* w = (void*)(self + 4);
        void (__thiscall* fn)(void*, void*) =
            *(void(__thiscall**)(void*, void*))((char*)*(void**)w + 0x114);
        WinMsg m;
        m.code = 0x51a1a2d;
        m.f3 = 0;
        m.f4 = 0;
        m.f5 = 0;
        m.f6 = (int)param_2;
        fn(w, &m);
    }
}

// @ 0x00994c30
void WinXHTML_s0099_4240::FUN_00994c30(int)
{
    char* self = (char*)this;

    FUN_00994240();
    ((XHTMLPage*)(self + 0x218))->Resize(*(float*)(self + 0xa880) - *(float*)(self + 0xa878),
                                         *(float*)(self + 0xa884) - *(float*)(self + 0xa87c));
}

// @ 0x00994c80
void WinXHTML_s0099_4c80::CreateFormControl(XHTML::FormControl* pFormControl)
{
    Rect textMargins, passwordMargins, textareaMargins;
    switch (pFormControl->mElementType) {
    case XHTML::kElementInput: {
        const wchar_t* pType = pFormControl->GetAttrValue(gAttrType);
        const wchar_t* pValue = pFormControl->GetAttrValue(gAttrValue);
        const wchar_t* pName = pFormControl->GetAttrValue(gAttrName);
        const wchar_t* pDisabled = pFormControl->GetAttrValue(gAttrDisabled);
        const wchar_t* pReadonly = pFormControl->GetAttrValue(gAttrReadonly);
        const wchar_t* pSize = pFormControl->GetAttrValue(gAttrSize);
        if (!pType)
            return;
        int nSize = 0;
        if (pSize)
            nSize = wcstol(pSize, 0, 0);
        IWindow* pWindow;

        if (_wcsicmp(pType, gValButton) == 0) {
            IButton* pButton = new (4, "UTFWin/WinXHTML/Button", GetUTFWinAllocator()) WinButton();
            pButton->SetCaptionBorders(12.0f, 4.0f, 12.0f, 4.0f);
            pWindow = pButton->ToWindow();
            if (pValue)
                pWindow->SetCaption(pValue);
            pWindow->SetDrawable(mFormCtrlDrawable[0]);
            pWindow->SetFillColor(kFormFillColor);
        } else if (_wcsicmp(pType, gValText) == 0) {
            ITextEdit* pEdit = new (8, "UTFWin/WinXHTML/WinTextEdit", GetUTFWinAllocator()) WinTextEdit();
            pWindow = pEdit->ToWindow();
            textMargins.Set(4.0f);
            pEdit->SetMargins(&textMargins);
            if (pValue)
                pEdit->SetText(pValue, 0);
            if (pReadonly)
                pEdit->SetEditFlag(1, true);
            if (nSize)
                pEdit->SetMaxTextLength(nSize);
            pWindow->SetDrawable(mFormCtrlDrawable[1]);
            pWindow->SetFillColor(kFormFillColor);
        } else if (_wcsicmp(pType, gValPassword) == 0) {
            ITextEdit* pEdit = new (8, "UTFWin/WinXHTML/WinTextEdit", GetUTFWinAllocator()) WinTextEdit();
            pWindow = pEdit->ToWindow();
            passwordMargins.Set(4.0f);
            pEdit->SetMargins(&passwordMargins);
            pEdit->SetEditFlag(0x80, true);
            if (pValue)
                pEdit->SetText(pValue, 0);
            if (pReadonly)
                pEdit->SetEditFlag(1, true);
            if (nSize)
                pEdit->SetMaxTextLength(nSize);
            pWindow->SetDrawable(mFormCtrlDrawable[1]);
            pWindow->SetFillColor(kFormFillColor);
        } else if (_wcsicmp(pType, gValCheckbox) == 0) {
            IButton* pButton = new (4, "UTFWin/WinXHTML/Button", GetUTFWinAllocator()) WinButton();
            pButton->SetButtonType(kButtonTypeCheckBox);
            pWindow = pButton->ToWindow();
            pWindow->SetFillColor(kFormFillColor);
            pWindow->SetDrawable(mFormCtrlDrawable[2]);
            if (pFormControl->GetAttrValue(gAttrChecked))
                pButton->SetButtonStateFlag(4, true);
        } else if (_wcsicmp(pType, gValRadio) == 0) {
            IButton* pButton = new (4, "UTFWin/WinXHTML/Button", GetUTFWinAllocator()) WinButton();
            pButton->SetButtonType(kButtonTypeRadio);
            pButton->SetButtonGroupID(Hash::FNV1_String16(pName, 0x811c9dc5, 0));
            pWindow = pButton->ToWindow();
            pWindow->SetFillColor(kFormFillColor);
            pWindow->SetDrawable(mFormCtrlDrawable[3]);
            pWindow->SetCommandID(kCommandRadio);
        } else if (_wcsicmp(pType, gValSubmit) == 0) {
            IButton* pButton = new (4, "UTFWin/WinXHTML/Button", GetUTFWinAllocator()) WinButton();
            pButton->SetCaptionBorders(12.0f, 4.0f, 12.0f, 4.0f);
            pWindow = pButton->ToWindow();
            if (pValue)
                pWindow->SetCaption(pValue);
            else
                pWindow->SetCaption(L"Submit");
            pWindow->SetDrawable(mFormCtrlDrawable[0]);
            pWindow->SetFillColor(kFormFillColor);
            pWindow->SetCommandID(kCommandSubmit);
        } else if (_wcsicmp(pType, gValReset) == 0) {
            IButton* pButton = new (4, "UTFWin/WinXHTML/Button", GetUTFWinAllocator()) WinButton();
            pButton->SetCaptionBorders(12.0f, 4.0f, 12.0f, 4.0f);
            pWindow = pButton->ToWindow();
            if (pValue)
                pWindow->SetCaption(pValue);
            else
                pWindow->SetCaption(L"Reset");
            pWindow->SetDrawable(mFormCtrlDrawable[0]);
            pWindow->SetFillColor(kFormFillColor);
            pWindow->SetCommandID(kCommandReset);
        } else if (_wcsicmp(pType, gValImage) == 0) {
            IButton* pButton = new (4, "UTFWin/WinXHTML/Button", GetUTFWinAllocator()) WinButton();
            pWindow = pButton->ToWindow();
            pWindow->SetDrawable(new (4, "UTFWin/WinXHTML/StdDrawable", GetUTFWinAllocator()) StdDrawable());
        } else if (_wcsicmp(pType, gValHidden) == 0) {
            pWindow = new (4, "UTFWin/WinXHTML/Window", GetUTFWinAllocator()) WindowImpl();
            pWindow->SetFlag(kWinFlagVisible, false);
            if (pValue)
                pWindow->SetCaption(pValue);
        } else {
            return;
        }
        BindFormControl(this, pFormControl, pWindow, pDisabled);
        break;
    }

    case XHTML::kElementButton: {
        const wchar_t* pType = pFormControl->GetAttrValue(gAttrType);
        const wchar_t* pValue = pFormControl->GetAttrValue(gAttrValue);
        const wchar_t* pDisabled = pFormControl->GetAttrValue(gAttrDisabled);
        IButton* pButton = new (4, "UTFWin/WinXHTML/Button", GetUTFWinAllocator()) WinButton();
        pButton->SetCaptionBorders(12.0f, 4.0f, 12.0f, 4.0f);
        IWindow* pWindow = pButton->ToWindow();
        pWindow->SetDrawable(mFormCtrlDrawable[0]);
        pWindow->SetFillColor(kFormFillColor);
        if (pValue) {
            pWindow->SetCaption(pValue);
        } else if (_wcsicmp(pType, gValSubmit) == 0) {
            pWindow->SetCaption(L"Submit");
            pWindow->SetCommandID(kCommandSubmit);
        } else if (_wcsicmp(pType, gValReset) == 0) {
            pWindow->SetCaption(L"Reset");
            pWindow->SetCommandID(kCommandReset);
        }
        BindFormControl(this, pFormControl, pWindow, pDisabled);
        break;
    }
    case XHTML::kElementSelect: {
        IWinGrid* pGrid = 0;
        IComboBox* pCombo = 0;
        const wchar_t* pDisabled = pFormControl->GetAttrValue(gAttrDisabled);
        const wchar_t* pSize = pFormControl->GetAttrValue(gAttrSize);
        const wchar_t* pMultiple = pFormControl->GetAttrValue(gAttrMultiple);
        IWindow* pWindow;
        int nRows = 1;
        if (pSize) {
            int nSize = wcstol(pSize, 0, 0);
            nRows = Max(1, nSize);
        }
        if (nRows > 1 || pMultiple) {
            pGrid = new (8, "WinXHTML/WinGrid", GetUTFWinAllocator()) WinGrid();
            pWindow = pGrid->ToWindow();
            pGrid->SetSelectionLimits(1, pMultiple ? 0x7fffffff : 1, 0);
            pGrid->SetGridFlag(1, false);
            pGrid->SetGridFlag(2, false);
            pGrid->SetGridFlag(0x200, false);
            pGrid->SetGridFlag(0x400, false);
            pGrid->SetColor(0xff939393, 2);
            pGrid->SetColor(0xffaeaeae, 3);
            pGrid->SetColor(0xff000000, 4);
            pGrid->SetColor(0xffd7e0f2, 5);
            pGrid->SetColor(0xff000000, 6);
            pGrid->SetColor(0xffaeaeae, 7);
            pGrid->SetCellMargins(2.0f, 2.0f, 2.0f, 2.0f);
            pGrid->SetCellPadding(2.0f, 1.0f, 2.0f, 1.0f);
            pGrid->SetAutoSize(1, 0);
            pGrid->SetHeaderFlags(1, 1);
            pGrid->SetLineWidth(0.0f);
            pWindow->SetDrawable(mFormCtrlDrawable[1]);
            if (mScrollbars[1].mDrawable)
                pGrid->SetHScrollbarDrawable(mScrollbars[1].mDrawable);
            if (mScrollbars[0].mDrawable)
                pGrid->SetVScrollbarDrawable(mScrollbars[0].mDrawable);
        } else {
            pCombo = new (4, "WinXHTML/ComboBox", GetUTFWinAllocator()) WinComboBox();
            pWindow = pCombo->ToWindow();
            pWindow->SetDrawable(mFormCtrlDrawable[4]);
            if (mScrollbars[1].mDrawable)
                pCombo->SetScrollbarDrawable(mScrollbars[1].mDrawable);
            pCombo->SetComboBoxFlag(1, false);
            pCombo->SetColor(2, 0xff000000);
            pCombo->SetColor(3, 0xffd7e0f2);
            pCombo->SetColor(4, 0xff000000);
            pCombo->SetColor(5, 0xffaeaeae);
        }

        int nRow = 0;
        for (XHTML::NodeList::iterator it = pFormControl->mChildNodes.begin(); it != pFormControl->mChildNodes.end(); ++it) {
            XHTML::Node* pNode = it.mpNode;
            if (pNode->Type() == XHTML::kNodeTypeElement &&
                static_cast<XHTML::Element*>(pNode)->mElementType == XHTML::kElementOption) {
                XHTML::Element* pOption = static_cast<XHTML::Element*>(pNode);
                string16 sText;
                const wchar_t* pLabel = pOption->GetAttrValue(gAttrLabel);
                const wchar_t* pOptValue = pOption->GetAttrValue(gAttrValue);
                if (!pLabel || !pOptValue) {
                    pOption->GetTextContent(sText);
                    if (!pLabel)
                        pLabel = sText.c_str();
                }
                if (pGrid) {
                    pGrid->SetCellText(0, nRow, pLabel, 0, 1, 0);
                    ++nRow;
                } else if (pCombo) {
                    pCombo->AddValue(pLabel);
                }
            }
        }
        BindFormControl(this, pFormControl, pWindow, pDisabled);
        break;
    }

    case XHTML::kElementTextarea: {
        const wchar_t* pDisabled = pFormControl->GetAttrValue(gAttrDisabled);
        const wchar_t* pReadonly = pFormControl->GetAttrValue(gAttrReadonly);
        ITextEdit* pEdit = new (8, "UTFWin/WinXHTML/WinTextEdit", GetUTFWinAllocator()) WinTextEdit();
        IWindow* pWindow = pEdit->ToWindow();
        textareaMargins.Set(4.0f);
        pEdit->SetMargins(&textareaMargins);
        pEdit->SetEditMode(2);
        if (pReadonly)
            pEdit->SetEditFlag(1, true);
        pWindow->SetDrawable(mFormCtrlDrawable[1]);
        pWindow->SetFillColor(0xffffffff);
        IDrawable* pVScroll = mScrollbars[1].mDrawable;
        if (pVScroll)
            pEdit->SetScrollbarDrawable(1, pVScroll->GetObjectID());
        IDrawable* pHScroll = mScrollbars[0].mDrawable;
        if (pHScroll)
            pEdit->SetScrollbarDrawable(0, pHScroll->GetObjectID());
        BindFormControl(this, pFormControl, pWindow, pDisabled);
        break;
    }

    }
}

// @ 0x00995b20
void __thiscall WinXHTML_::FUN_00995b20(XDomElement* fc, const uint16_t* value)
{
    if (fc == 0)
        return;
    void* formObj = fc->mpFormObj;
    if (formObj == 0)
        return;
    void* mgr = ((XDomQueryFn)(*(void***)formObj)[3])(formObj, 0xeeee8218);
    if (mgr == 0)
        return;
    uint32_t type = fc->mElementType;  // 23 = Input, 24 = Select, 26 = Textarea
    (void)type;
    (void)value;
    // incomplete
}

// @ 0x00995ea0
void __thiscall WinXHTML_::FUN_00995ea0(XDomElement* fc, void* out)
{
    if (fc == 0)
        return;
    void* formObj = fc->mpFormObj;
    if (formObj == 0)
        return;
    void* mgr = ((XDomQueryFn)(*(void***)formObj)[3])(formObj, 0xeeee8218);
    if (mgr == 0)
        return;
    (void)out;
    // incomplete
}

// @ 0x009960b0
bool EA::UTFWinExtras::WinXHTML::OnMouseUp(float x, float y, unsigned int button, unsigned int flags)
{
    (void)x;
    (void)y;
    (void)button;
    (void)flags;
    // incomplete
    return false;
}
