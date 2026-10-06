// Slice s00994c80 -- EA::UTFWinExtras::WinXHTML::CreateFormControl (0x00994c80).
// Builds the UTFWin control (button / text edit / check box / radio / combo box / grid / window)
// that represents an XHTML <input>, <select>, <textarea> or <button> form element, binds it to the
// DOM FormControl and adds it to the content window.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (no /EHsc: the option-text string16 local has no EH frame).
#include "types.h"

extern "C" __declspec(dllimport) long __cdecl wcstol(const wchar_t* s, wchar_t** end, int base);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);

// ---------------------------------------------------------------- placeholder virtual slots
#define VP_CAT2(a, b) a##b
#define VP_CAT(a, b) VP_CAT2(a, b)
#define VP1 virtual void VP_CAT(_vp, __COUNTER__)();
#define VP2 VP1 VP1
#define VP4 VP2 VP2
#define VP8 VP4 VP4
#define VP16 VP8 VP8
#define VP32 VP16 VP16
#define VP64 VP32 VP32

// ---------------------------------------------------------------- allocator (UTFWin)
void* GetUTFWinAllocator();                                                       // 0x009512c0
void* operator new(unsigned int size, int align, const char* name, void* alloc);  // 0x009512d0
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void operator delete[](void* p);                                                  // 0x00f47380

// ---------------------------------------------------------------- UTFWin interfaces
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

// ---------------------------------------------------------------- concrete UTFWin classes
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

// ---------------------------------------------------------------- XHTML DOM
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
extern wchar_t gEmptyString16;                           // 0x01667bac
inline string16::string16() : mpBegin(&gEmptyString16), mpEnd(&gEmptyString16), mpCapacity(&gEmptyString16 + 1) {}

namespace XHTML {
struct NodeVBase {
    VP2
    /* 08h */ virtual void GetTextContent(string16& out);
};
struct Node : NodeVBase, intrusive_list_node {
    int Type();                                          // 0x00fc7e50
};
enum { kNodeTypeElement = 1 };
enum {
    kElementInput = 0x17, kElementSelect = 0x18, kElementOption = 0x19,
    kElementTextarea = 0x1a, kElementButton = 0x1b
};
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
struct Element : Node {
    uint32_t pad0c[3];
    NodeList mChildNodes;                                // +0x18
    uint32_t pad20[2];
    int mElementType;                                    // +0x28
    const wchar_t* GetAttrValue(const wchar_t* name);    // 0x008e45b0


};
struct FormControl : Element {
    void SetControl(IWindow* w);                         // 0x008e4b60
};
}  // namespace XHTML

// attribute / value names (EA::XHTML::DOM string table)
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

namespace Hash { uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int a); }  // 0x00932f30

// IFormControlMgr's object handed to the window as kFormControlProp (0x344a0b7)
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


// ---------------------------------------------------------------- WinXHTML (as seen by this method)
struct WinXHTML {
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

    void CreateFormControl(XHTML::FormControl* pFormControl);
};

__forceinline void BindFormControl(WinXHTML* self, XHTML::FormControl* pFormControl, IWindow* pWindow, const wchar_t* pDisabled)
{
    pFormControl->SetControl(pWindow);
    pWindow->SetUserObject(kFormControlProp, new ("FormControlRef", 0, 0, 0, 0) FormControlRef(pFormControl));
    if (pDisabled)
        pWindow->SetFlag(kWinFlagEnabled, false);
    self->mContentWindow->AddWindow(pWindow);
}

// @ 0x00994c80
void WinXHTML::CreateFormControl(XHTML::FormControl* pFormControl)
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
