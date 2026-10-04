// SP::Pollen::cXHTMLWin (the XHTML window used by the Spore.com registration/login pages), the hover
// title, and the DOM form-control helpers. Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "s00622f20.h"

extern "C" __declspec(dllimport) double __cdecl wcstod(const wchar_t*, wchar_t**);
extern "C" __declspec(dllimport) int __cdecl wcsncmp(const wchar_t*, const wchar_t*, unsigned int);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);

using EA::AutoRefCount;
namespace EA {
namespace XHTML {
namespace DOM {
struct Element;
struct Node;
}  // namespace DOM
}  // namespace XHTML
}  // namespace EA

// ---- DOM -----------------------------------------------------------------------------------------
struct DomHook {  // eastl::intrusive_list_node
  DomHook* mpNext;
  DomHook* mpPrev;
};
struct DomNodeBase {
  PV(0) PV(1)
  virtual void GetText(string16* pOut);  // +8
  PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool DispatchEvent(void* pEvent, bool b);  // +0x24
};
struct DomElement;
struct DomNode : DomNodeBase, DomHook {  // hook at +4 (placed after the vptr)
  int Type();                // 0x00fc7e50
  DomElement* AsElement();   // 0x008e52f0
};
struct DomNodeList {
  uint32_t pad;
  DomHook mAnchor;
};
struct IControlHolder {
  PV(0) PV(1) PV(2)
  virtual EA::UTFWin::IWindow* GetWindow(uint32_t type);  // +0xc
};
struct DomElement : DomNode {
  uint32_t pad1[(0x14 - 0xc) / 4];
  DomNodeList mChildren;  // +0x14
  uint32_t pad2[(0x28 - 0x20) / 4];
  int mTag;  // +0x28
  uint32_t pad3[(0x44 - 0x2c) / 4];
  IControlHolder* mpControl;  // +0x44
  const wchar_t* GetAttrValue(const wchar_t* name);  // 0x008e45b0
  void SetControl(void* p);                          // 0x008e4b60
  DomElement* GetParent();                           // 0x00ff0420
};
extern const wchar_t* gAttrDisabled;  // 0x015212a0
extern const wchar_t* gAttrType;      // 0x01521294
extern const wchar_t* gTypeHidden;    // 0x015212c0
extern const wchar_t* gTypeSubmit;    // 0x015212b8
extern const wchar_t* gAttrTabIndex;  // 0x015212b0
extern const wchar_t* gLinkPrefix;    // 0x015212c8
extern unsigned int gLinkPrefixLen;   // 0x015f61a4

inline unsigned int WStrLen(const wchar_t* s) {
  const wchar_t* ps = s + 1;
  do {
  } while (*s++);
  return (unsigned int)(s - ps);
}

namespace SP {
namespace Pollen {
using namespace EA;
using namespace EA::UTFWin;

// @ 0x00622f20
double ToDouble(const wchar_t* s) {
  wchar_t* end;
  return wcstod(s, &end);
}

struct LinkMessage {
  uint32_t pad[2];
  uint32_t mEventType;  // +8
  uint32_t pad2[3];
  const wchar_t** mppURL;  // +0x18
};
// @ 0x00622f40
bool __stdcall HandleLinkMessage(void* unused, const LinkMessage* msg) {
  if (msg->mEventType == 0x3326e8a) {
    const wchar_t** pp = msg->mppURL;
    if (*pp && wcsncmp(*pp, gLinkPrefix, gLinkPrefixLen) == 0 && WStrLen(*pp) > gLinkPrefixLen) {
      AppSystem()->OpenURL(*pp + gLinkPrefixLen);
      return true;
    }
  }
  return false;
}

// @ 0x00623000
bool __stdcall IsSubmittableControl(DomElement* e) {
  if (e) {
    if (!e->GetAttrValue(gAttrDisabled)) {
      int tag = e->mTag;
      const wchar_t* type = e->GetAttrValue(gAttrType);
      if (tag != 0x15 && tag != 0x16) {
        if (tag != 0x17 || (type && _wcsicmp(type, gTypeHidden) != 0)) return true;
      }
    }
  }
  return false;
}

// ---- intrusive-list hook helper ---------------------------------------------------------------
// @ 0x00623260
struct DomHookX : DomHook {
  void GetNode(DomNode** ppNode);
};
void DomHookX::GetNode(DomNode** ppNode) {
  if (this)
    *ppNode = (DomNode*)((char*)this - 4);
  else
    *ppNode = 0;
}

// ---- ref-counted object release ------------------------------------------------------------------
struct RefCounted {
  virtual void pv0();
  virtual void pv1();
  virtual void Destroy(int flags);  // +8
  int mRefCount;                    // +4
  int ReleaseRef();
};
// @ 0x00623070
int RefCounted::ReleaseRef() {
  int n = mRefCount + -1;
  mRefCount = n;
  if (n == 0) {
    mRefCount = 1;
    Destroy(1);
    return 0;
  }
  return n;
}

// ---- XHTML button factory ---------------------------------------------------------------------------
// @ 0x006230b0
bool CreateXHTMLButton(IWindow** ppButton) {
  cSPUILayout layout;
  bool ok = false;
  ResourceKey key = ResourceKey::Make(0xceb6dd52, 0x510a95b, 0x40464100);
  if (layout.Init(key, 0, 0x5b598fa)) {
    AutoRefCount<IWindow> w(layout.FindWindowByID(0, true));
    if (w.mpObject) {
      *ppButton = w.mpObject;
      w.mpObject->AddRef();
      ok = true;
    }
    layout.Shutdown(true);
  }
  return ok;
}

// ---- form-control helpers --------------------------------------------------------------------------------
struct FormControlRef {
  uint32_t pad[0x44 / 4];
  IControlHolder* mpControl;  // +0x44
};
// @ 0x00623150
void __stdcall ShowFormControl(FormControlRef* c, int unused) {
  IControlHolder* h = c->mpControl;
  IWindow* w = h ? h->GetWindow(0xeeee8218) : 0;
  w->SetFlag(1, true);
}

// ---- DOM tree searches for form submission ---------------------------------------------------------
// @ 0x00623570
DomElement* FindSubmitChild(DomElement* e) {
  DomNode* n = static_cast<DomNode*>(e->mChildren.mAnchor.mpNext);
  DomNode* end = (DomNode*)&e->mChildren;
  while (n != end) {
    DomElement* c = n->AsElement();
    if (c) {
      int tag = c->mTag;
      if (tag == 0x17 || tag == 0x1b) {
        const wchar_t* type = c->GetAttrValue(gAttrType);
        if (type && _wcsicmp(type, gTypeSubmit) == 0) return c;
      } else if (tag != 0x15) {
        DomElement* r = FindSubmitChild(c);
        if (r) return r;
      }
    }
    n = static_cast<DomNode*>(n->mpNext);
  }
  return 0;
}

// @ 0x00623610
DomElement* FindFormChild(DomElement* e) {
  DomNode* n = static_cast<DomNode*>(e->mChildren.mAnchor.mpNext);
  for (;;) {
    DomNode* end = (DomNode*)&e->mChildren;
    if (n == end) return 0;
    DomElement* c = n->AsElement();
    if (c) {
      if (c->mTag == 0x15) return c;
      DomElement* r = FindFormChild(c);
      if (r) return r;
    }
    n = static_cast<DomNode*>(n->mpNext);
  }
}

// ---- cXHTMLWin --------------------------------------------------------------------------------------------
struct DomDocument {
  uint32_t pad[0x38 / 4];
  uint32_t mUnk38;  // +0x38
  uint32_t mUnk3c;  // +0x3c
  DomElement* mpRoot;  // +0x40
  void DestroyFormControls();  // 0x008e2890
  bool FUN_008e29e0(bool b);   // 0x008e29e0
};
struct XListNode {
  XListNode* mpNext;
  XListNode* mpPrev;
  DomElement* mpElement;
};
struct XList {
  XListNode* mpNext;
  XListNode* mpPrev;
  bool empty() const { return mpNext == (const XListNode*)this; }
};
struct WXBase0 {
  virtual void wx0();
};
struct WXBase1 {  // the window part (IWindow-like)
  virtual void wx1();
  void SetHoverHandler(void* p);  // 0x00961fc0
  uint32_t pad[0x204 / 4];
};
struct WXBase2 {
  virtual void wx2();
};
struct WXBase3 {
  virtual void wx3();
  uint32_t pad[(0x23c - 0x214) / 4];
};
struct WinXHTML : WXBase0, WXBase1, WXBase2, WXBase3 {
  WinXHTML();              // 0x00993c10
  virtual ~WinXHTML();     // 0x00993000
  bool DoMessage(const Message& msg);  // 0x00993130
  void SetFormControlValue(DomElement* e, const wchar_t* value);  // 0x00995b20
  DomDocument* mpDocument;  // +0x23c
  uint32_t pad2[(0xa67c - 0x240) / 4];
};
struct IFormHost {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27)
  PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40)
  PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53)
  PV(54) PV(55) PV(56)
  virtual void RemoveControl(IWindow* w);  // +0xe0
};

class cXHTMLWin : public WinXHTML {
 public:
  cXHTMLWin();
  virtual ~cXHTMLWin();
  void DestroyFormControl(DomElement* e);  // 0x00623370
  bool FocusNextControl();                  // 0x006233f0
  bool SubmitForm();                        // 0x00623660
  bool OnKeyDown(int a, int key, int c);    // 0x00623ef0
  bool OnKeyUp(int a, int key, int c);      // 0x00622fe0
  bool HandleMessage(const Message& msg);   // 0x00623190
  void SetFormControlValue(DomElement* e, const wchar_t* value);  // 0x00623c90

  IWindow* mpFormHost;  // +0xa67c
  uint32_t pad3[(0xa6dc - 0xa680) / 4];
  XList mControlList;     // +0xa6dc
  uint32_t pad4[(0xa888 - 0xa6e4) / 4];
  uint32_t mSubmitButtonID;  // +0xa888
  uint32_t pad5[(0xa8e8 - 0xa88c) / 4];
  XList mFormList;        // +0xa8e8
  uint32_t pad6;
  bool mbSubmitting;      // +0xa8f4
};

// @ 0x00622fe0
bool cXHTMLWin::OnKeyUp(int a, int key, int c) {
  if (key == 0xd) {
    mbSubmitting = false;
    return true;
  }
  return false;
}

// @ 0x00623190
bool cXHTMLWin::HandleMessage(const Message& msg) {
  if (msg.mEventType == 0x287259f6 && msg.mpSource) {
    uint32_t id = mSubmitButtonID;
    if ((uint32_t)msg.mpSource->GetParent() == id) return true;
  }
  return DoMessage(msg);
}

inline void FreeListNodes(XList* list) {
  XListNode* p = list->mpNext;
  XListNode* end = (XListNode*)list;
  while (p != end) {
    XListNode* cur = p;
    p = p->mpNext;
    EASTL_allocator_deallocate(cur);
  }
}
inline void ClearList(XList* list) {
  FreeListNodes(list);
  list->mpNext = (XListNode*)list;
  list->mpPrev = (XListNode*)list;
}

// @ 0x00623280
cXHTMLWin::~cXHTMLWin() {
  DomDocument* doc = mpDocument;
  if (doc) {
    doc->DestroyFormControls();
    doc->mUnk38 = 0;
    doc->mUnk3c = 0;
  }
  FreeListNodes(&mFormList);
}

// @ 0x00623370
void cXHTMLWin::DestroyFormControl(DomElement* e) {
  XList* list = &mControlList;
  if (!list->empty()) ClearList(list);
  IControlHolder* h = e->mpControl;
  if (h) {
    IWindow* w = h->GetWindow(0xeeee8218);
    if (w) {
      if (w->GetParent()) mpFormHost->DisposeWindowFamily(w);
      e->SetControl(0);
    }
  }
}

// @ 0x00623660
bool cXHTMLWin::SubmitForm() {
  DomElement* form = 0;
  for (XListNode* n = mFormList.mpNext; n != (XListNode*)&mFormList; n = n->mpNext) {
    IControlHolder* h = n->mpElement->mpControl;
    if (h) {
      IWindow* w = h->GetWindow(0xeeee8218);
      if (w && w->IsEnabled(0)) form = n->mpElement;
    }
  }
  DomElement* root;
  if (form) {
    DomElement* e = form;
    while (e->mTag != 0x15) {
      e = e->GetParent();
      if (!e) return false;
    }
    root = e;
  } else {
    if (!mpDocument || !mpDocument->mpRoot) return false;
    root = FindFormChild(mpDocument->mpRoot);
    if (!root) return false;
  }
  DomElement* submit = FindSubmitChild(root);
  if (!submit) return false;
  struct Click {
    DomElement* mpSource;
    int mType;
  } click = {submit, 2};
  submit->DispatchEvent(&click, true);
  return true;
}

// @ 0x006233f0 : Tab navigation, picks the form control to focus next (ordered by the tabindex attribute)
bool cXHTMLWin::FocusNextControl() {
  XListNode* const end = (XListNode*)&mFormList;
  XListNode* start = mFormList.mpNext;
  if (start != end) {
    do {
      IControlHolder* h = start->mpElement->mpControl;
      if (h) {
        IWindow* w = h->GetWindow(0xeeee8218);
        if (w && w->IsEnabled(0)) break;
      }
      start = start->mpNext;
    } while (start != end);
  }
  if (start == end) return false;
  IWindow* best = 0;
  const wchar_t* bestIdx = start->mpElement->GetAttrValue(gAttrTabIndex);
  XListNode* it = start;
  for (;;) {
    it = it->mpNext;
    if (it == end) it = end->mpNext;
    if (it == start) break;
    if (!best) {
      IControlHolder* h = it->mpElement->mpControl;
      best = h ? h->GetWindow(0xeeee8218) : 0;
      bestIdx = it->mpElement->GetAttrValue(gAttrTabIndex);
    } else {
      const wchar_t* idx = it->mpElement->GetAttrValue(gAttrTabIndex);
      if (idx && bestIdx) {
        wchar_t* pEndA;
        wchar_t* pEndB;
        double a = wcstod(idx, &pEndA);
        double b = wcstod(bestIdx, &pEndB);
        if (a > b) {
          IControlHolder* h = it->mpElement->mpControl;
          best = h ? h->GetWindow(0xeeee8218) : 0;
          bestIdx = idx;
        }
      }
    }
  }
  if (!best) return false;
  WindowManager()->SetFocus(0, best);
  return true;
}

// @ 0x00623ef0
bool cXHTMLWin::OnKeyDown(int a, int key, int c) {
  if (key == 9) {
    if (!mpDocument || mpDocument->FUN_008e29e0(true)) return false;
    return FocusNextControl();
  }
  if (key == 0xd) {
    if (!mbSubmitting) {
      mbSubmitting = true;
      return SubmitForm();
    }
  }
  return false;
}

// ---- property lists / watchers ---------------------------------------------------------------------------
struct IPropValue {
  uint8_t pad[0x10];
  uint8_t mFlags;   // +0x10 (0x30: indirect storage)
  uint8_t pad11;
  uint16_t mType;   // +0x12
  const float* GetFloatPtr();
};
struct PropListNode {  // SP::cPropertyList
  uint32_t pad[0x30 / 4];
  PropListNode* mpParent;  // +0x30
  uint32_t mnModCount;     // +0x34
  uint32_t GetModificationCount();  // 0x006237a0
};
extern const float gDefaultFloat;  // 0x015d9c6c

// @ 0x006237a0
uint32_t PropListNode::GetModificationCount() {
  uint32_t parentCount = mpParent ? mpParent->GetModificationCount() : 0;
  return mnModCount + parentCount;
}

struct IPropListener {
  virtual void pv0();
  virtual void OnPropertiesLoaded(PropListNode* pProps);  // +4
  uint32_t pad;
  IPropListener* mpNext;  // +8
};
struct PropChangeNotifier {
  IPropListener* mpFirst;  // +0
  uint32_t mnVersion;      // +4
  // @ 0x006237d0
  bool Notify(PropListNode* pProps);
};
bool PropChangeNotifier::Notify(PropListNode* pProps) {
  if (mnVersion != 0xffffffff) return false;
  uint32_t version = pProps->GetModificationCount();
  bool changed = version != 0xffffffff;
  if (changed) {
    mnVersion = version;
    for (IPropListener* p = mpFirst; p; p = p->mpNext) p->OnPropertiesLoaded(pProps);
  }
  return changed;
}

struct IPropertyListV {
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, IPropValue** ppValue);  // +0x24
};
struct cFloatPropWatch {
  uint32_t pad;
  uint32_t mPropID;  // +4
  uint32_t pad2;
  float mValue;      // +0xc
  // @ 0x006231d0
  bool Refresh(IPropertyListV* pProps);
};
bool cFloatPropWatch::Refresh(IPropertyListV* pProps) {
  IPropValue* pValue;
  if (pProps->GetProperty(mPropID, &pValue)) {
    const float* pData;
    if (pValue->mType == 0xd || pValue->mType == 0x10) {
      if (pValue->mFlags & 0x30)
        pData = *(const float**)pValue;
      else
        pData = pValue->mType ? (const float*)pValue : 0;
    } else {
      pData = &gDefaultFloat;
    }
    float f = *pData;
    if (mValue != f) {
      mValue = f;
      return true;
    }
  }
  return false;
}

// ---- cSPHoverTitle -----------------------------------------------------------------------------------------
struct ITextWin {
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void SetFlag2(bool b);  // +0x14
};
struct HoverBaseA {
  virtual void ha0();
};
class cSPHoverTitle : public HoverBaseA, public EA::RefCountVTemplate<int> {
 public:
  cSPHoverTitle(IWindow* pParent);
  ~cSPHoverTitle();
  void Layout();    // 0x00623830
  void Load();      // 0x006239c0
  AutoRefCount<IWindow> mpParent;          // +0xc
  AutoRefCount<cSPUILayout> mpLayout;      // +0x10
  AutoRefCount<IWindow> mpTitleWin;        // +0x14
  float mDelay;                            // +0x18
  string16 mText;                          // +0x1c
  AutoRefCount<IPropertyListV> mpProps;    // +0x2c
};
extern const float gHoverDelay;  // 0x013fda5c
extern const float gHoverOffsetX, gHoverOffsetY;  // 0x013fdcf4, 0x013fdcf8

// @ 0x00623730
cSPHoverTitle::cSPHoverTitle(IWindow* pParent) : mpParent(pParent), mDelay(gHoverDelay) {
  mpLayout.mpObject = 0;
  mpTitleWin.mpObject = 0;
}

// @ 0x00623af0
cSPHoverTitle::~cSPHoverTitle() {
  mpTitleWin = 0;
  mpParent = 0;
  if (mpLayout.mpObject) mpLayout.mpObject->Shutdown(true);
  mpLayout = 0;
  mpProps = 0;
}

struct IPropertyMgr {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
  virtual bool GetPropertyList(uint32_t id, IPropertyListV** ppList);  // +0x30
};
IPropertyMgr* PropertyManager();  // 0x0067de30
extern PropChangeNotifier gHoverPropNotifier;  // 0x015215a4
void GetCursorPosition(float* pX, float* pY);  // 0x00804ed0
extern const float gPadX, gPadFlipX, gPadY, gPadFlipY;  // 0x015f6144, 0x015f6194, 0x015f6184, 0x015f6164

// @ 0x00623830
void cSPHoverTitle::Layout() {
  const wchar_t* text = mText.mpBegin;
  mpTitleWin.mpObject->SetCaption(text);
  if (mpTitleWin.mpObject) {
    ITextWin* t = (ITextWin*)mpTitleWin.mpObject->Cast(0xf15f4bd);
    if (t) {
      mpTitleWin.mpObject->SetSize(gHoverOffsetX, gHoverOffsetY);
      t->SetFlag2(true);
      t->SetFlag2(false);
    }
  }
  float pos[2];
  GetCursorPosition(&pos[0], &pos[1]);
  mpParent.mpObject->ToLocalCoordinates2(SPPoint(pos[0], pos[1]), (SPPoint*)pos);
  const float* prc = mpParent.mpObject->GetRealArea();
  const float* rc = mpTitleWin.mpObject->GetArea();
  float w = rc[2] - rc[0];
  if (gPadX + w + pos[0] > prc[2])
    pos[0] = pos[0] - (w + gPadFlipX);
  else
    pos[0] = gPadX + pos[0];
  float h = rc[3] - rc[1];
  if (gPadY + h + pos[1] > prc[3])
    pos[1] = pos[1] - (h + gPadFlipY);
  else
    pos[1] = gPadY + pos[1];
  mpTitleWin.mpObject->SetPosition(pos[0], pos[1]);
  mpTitleWin.mpObject->SetFlag(1, true);
  mpTitleWin.mpObject->Invalidate();
}

// @ 0x006239c0
void cSPHoverTitle::Load() {
  IPropertyMgr* pm = PropertyManager();
  IPropertyListV** pp = &mpProps.mpObject;
  if (*pp) {
    IPropertyListV* p = *pp;
    *pp = 0;
    p->Release();
  }
  if (pm->GetPropertyList(0x5c770db7, pp)) gHoverPropNotifier.Notify((PropListNode*)*pp);
  mpLayout = new ("UI/XHTML Hover Layout", 0, 0, 0, 0) cSPUILayout();
  {
    ResourceKey key = ResourceKey::Make(0x16bcc4fd, 0x510a95b, 0x40464100);
    mpLayout.mpObject->Init(key, 1, 0x5b598fa);
  }
  mpLayout.mpObject->SetVisibility(false);
  mpLayout.mpObject->SetParentWin(mpParent.mpObject, true, 0x5b598fa);
  mpTitleWin = mpLayout.mpObject->FindWindowByID(0x7db2908, true);
  IWindow* wt = mpTitleWin.mpObject;
  if (wt) wt->SetFlag(0x10, true);
}

// ---- construction -------------------------------------------------------------------------------------------
extern PropChangeNotifier gXHTMLWinHandlerObj;  // 0x015215a0
// @ 0x00623be0
cXHTMLWin::cXHTMLWin() {
  mFormList.mpNext = (XListNode*)&mFormList;
  mFormList.mpPrev = (XListNode*)&mFormList;
  mbSubmitting = false;
  ((WXBase1*)this)->SetHoverHandler(&gXHTMLWinHandlerObj);
  cSPHoverTitle* t = new ("UI/cSPHoverTitle", 0, 0, 0, 0) cSPHoverTitle((IWindow*)(WXBase1*)this);
  ((WXBase1*)this)->SetHoverHandler(t);
}

// ---- <select> support ---------------------------------------------------------------------------------------
extern int gWindowNodeOffset;  // 0x01440aec : offset from an intrusive child-list node to its IWindow
extern const wchar_t* gAttrSelected;  // L"selected" at 0x013fdd28
extern const wchar_t* gAttrValue;     // L"value"    at 0x013fda1c
struct cSPUIPopupMenuWin {
  uint32_t pad[0x888 / 4];
  uint32_t mItemIndex;  // +0x888
  void OnMenuItemSelected(int a, void* pItem);  // 0x0081bef0
};

// @ 0x00623c90
void cXHTMLWin::SetFormControlValue(DomElement* e, const wchar_t* value) {
  IControlHolder* h = e->mpControl;
  IWindow* menu = 0;
  if (h) menu = (IWindow*)h->GetWindow(0x4c058d5);
  if (!menu) {
    WinXHTML::SetFormControlValue(e, value);
    return;
  }
  if (!value) return;
  int sel = 0;
  int counter = 0;
  if (WStrLen(value) == 0) {
    DomHook* anchor = &e->mChildren.mAnchor;
    DomNode* n = static_cast<DomNode*>(anchor->mpNext);
    sel = -1;
    while (n != static_cast<DomNode*>(anchor)) {
      if (sel != -1) break;
      if (n->Type() == 1) {
        if (n->AsElement()->GetAttrValue(gAttrSelected)) sel = counter;
        counter++;
      }
      n = static_cast<DomNode*>(n->mpNext);
    }
    if (sel == -1) sel = 0;
  } else {
    DomHook* anchor = &e->mChildren.mAnchor;
    DomNode* n = static_cast<DomNode*>(anchor->mpNext);
    while (n != static_cast<DomNode*>(anchor)) {
      if (n->Type() == 1 && n->AsElement()->mTag == 0x19) {
        const wchar_t* v = n->AsElement()->GetAttrValue(gAttrValue);
        if (v) {
          if (_wcsicmp(v, value) == 0) {
            sel = counter;
            break;
          }
        } else {
          string16 text;
          n->GetText(&text);
          if (_wcsicmp(text.mpBegin, value) == 0) {
            sel = counter;
            break;
          }
        }
        counter++;
      }
      n = static_cast<DomNode*>(n->mpNext);
    }
  }
  IWindow* list = (IWindow*)((char*)menu + 4);
  IWindowChildIter it = list->GetChildrenBegin();
  IWindowChildIter end = list->GetChildrenEnd();
  while (it.mpNode != end.mpNode) {
    IWindow* w = (IWindow*)((char*)it.mpNode + gWindowNodeOffset);
    if (w) {
      cSPUIPopupMenuWin* item = (cSPUIPopupMenuWin*)w->Cast(0x4c058cf);
      if (item && (uint32_t)sel == item->mItemIndex) {
        ((cSPUIPopupMenuWin*)menu)->OnMenuItemSelected(0, item);
        return;
      }
    }
    it.mpNode = *(void**)it.mpNode;
    end = list->GetChildrenEnd();
  }
}

// @ 0x00623f40 (separate function located inside the 0x00623ef0 range; the callback registered by cRegistrationDialog)
struct IXHTMLWinManager {
  void Register(cXHTMLWin* w);  // 0x00621bf0
};
IXHTMLWinManager* GetXHTMLWinManager();  // 0x00621c70
cXHTMLWin* CreateXHTMLWin() {
  cXHTMLWin* w = new (8, "UI/cXHTMLWin", GetDefaultAllocator()) cXHTMLWin();
  IXHTMLWinManager* mgr = GetXHTMLWinManager();
  if (mgr) mgr->Register(w);
  return w;
}
}  // namespace Pollen
}  // namespace SP
