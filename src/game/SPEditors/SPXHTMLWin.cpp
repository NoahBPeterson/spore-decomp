// src/game/SPEditors/SPXHTMLWin.cpp -- migrated from slice(s) s00623f90, s00622f20 by tools/migrate/rewrite.py
// Object file: SPEditors/SPXHTMLWin.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/CustomWinProc.h"
#include "EA/XHTML/DOM/Document.h"
#include "EA/UTFWin/ISerializable.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/Message.h"
#include "EA/UTFWin/MultiHeapObject.h"
#include "SP/cPropertyList.h"
#include "EA/UTFWinExtras/WinXHTML.h"
#include "SP/cPollinator.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "SP/cStringTokenTranslator.h"
#include <new>
#include <string.h>
#include <math.h>
#include <float.h>
#include <wchar.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" unsigned int __cdecl strlen(const char*);
extern char gEmptyString[];  // 0x01667bac (shared "" for char and wchar_t strings)
extern "C" __declspec(dllimport) double __cdecl wcstod(const wchar_t*, wchar_t**);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
extern const wchar_t* gAttrType;      // 0x01521294
extern const wchar_t* gTypeSubmit;    // 0x015212b8
extern const wchar_t* gAttrTabIndex;  // 0x015212b0
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(strlen)

// ---- items of slice s00622f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
extern char gEmptyString[];  // 0x01667bac (shared "" for char and wchar_t strings)
namespace eastl {
struct allocator_s0062_2f20 {
  allocator_s0062_2f20() {}
};
}
namespace eastl {
template <typename T>
inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
}
namespace eastl {
template <typename T>
inline unsigned int CharStrlen(const T* p) {
  const T* pCurrent = p;
  while (*pCurrent) ++pCurrent;
  return (unsigned int)(pCurrent - p);
}
}
namespace eastl {
int Compare(const char* p1, const char* p2, unsigned int n);  // FUN_00606ea0
}
namespace eastl {
template <typename I1, typename I2>
I1 search(I1 first1, I1 last1, I2 first2, I2 last2);  // 0x005e8ff0
}
namespace eastl {
template <typename T, typename A = allocator_s0062_2f20>
struct basic_string_s0062_2f20 {
  typedef unsigned int size_type;
  enum { npos = -1 };
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;

  basic_string_s0062_2f20() : mpBegin(0), mpEnd(0), mpCapacity(0) {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  basic_string_s0062_2f20(const T* pBegin, const T* pEnd, const A& allocator_s0062_2f20)
      : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator_s0062_2f20) {
    RangeInitialize(pBegin, pEnd);
  }
  struct CtorSprintf {};
  basic_string_s0062_2f20(CtorSprintf, const T* pFormat, ...);  // 0x00473020 (wchar_t), 0x00472f50 (char)
  basic_string_s0062_2f20& sprintf(const T* pFormat, ...);       // 0x00472fe0 (char)
  // (out of line at 0x0057cb10 elsewhere; this TU inlines it with AllocateSelf expanded)
  basic_string_s0062_2f20(const basic_string_s0062_2f20& x) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(x.mAllocator) {
    RangeInitializeInl(x.mpBegin, x.mpEnd);
  }
  ~basic_string_s0062_2f20() { DeallocateSelf(); }

  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1)
      DoFree(mpBegin, mpCapacity - mpBegin);
  }
  void DoFree(T* p, size_type) {
    if (p) EASTL_allocator_deallocate(p);
  }
  void AllocateSelf(size_type n);  // 0x00475ab0 (char)
  void RangeInitialize(const T* pBegin, const T* pEnd) {
    const size_type n = (size_type)(pEnd - pBegin);
    AllocateSelf(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
  static T* CharStringUninitializedCopy(const T* pSource, const T* pSourceEnd, T* pDestination) {
    memmove(pDestination, pSource, (size_t)(pSourceEnd - pSource) * sizeof(T));
    return pDestination + (pSourceEnd - pSource);
  }
  size_type length() const { return (size_type)(mpEnd - mpBegin); }
  const T* c_str() const { return mpBegin; }
  void clear() {
    if (mpBegin != mpEnd) {
      *mpBegin = 0;
      mpEnd = mpBegin;
    }
  }
  basic_string_s0062_2f20& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0 (char), 0x00423650 (wchar_t)
  basic_string_s0062_2f20& operator=(const T* p);  // 0x005c3d90 (wchar_t)
  basic_string_s0062_2f20& assign(const T* p) { return assign(p, p + CharStrlen(p)); }
  basic_string_s0062_2f20& operator=(const basic_string_s0062_2f20& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  basic_string_s0062_2f20& replace(size_type position, size_type n, const T* p);  // 0x005f8f80 (wchar_t)
  void Trim();                                                       // 0x00606e60 (wchar_t)

  static int compare(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2) {
    const int n1 = (int)(pEnd1 - pBegin1);
    const int n2 = (int)(pEnd2 - pBegin2);
    const int nMin = min_alt(n1, n2);
    const int cmp = Compare(pBegin1, pBegin2, (size_type)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
  }
  int compare(const T* p) const;
  basic_string_s0062_2f20 substr(size_type position, size_type n) const;
  basic_string_s0062_2f20 left(size_type n) const;
  size_type find(const T* p, size_type position, size_type n) const {
    T* const pBegin = mpBegin;
    T* const pEnd = mpEnd;
    if ((position + n) <= (size_type)(pEnd - pBegin)) {
      const T* const pResult = search(pBegin + position, pEnd, p, p + n);
      if ((pResult != pEnd) || (n == 0)) return (size_type)(pResult - pBegin);
    }
    return (size_type)npos;
  }
  size_type find(const T* p, size_type position = 0) const;
  size_type find(T c, size_type position = 0) const;  // 0x00607580 (char)
  bool empty() const { return (mpBegin == mpEnd); }
  size_type size() const { return (size_type)(mpEnd - mpBegin); }
  T* DoAllocate(size_type n) {
    return (T*)EASTL_allocator_allocate(n * sizeof(T), "Editor", 0, 0, "EASTL/allocator.h", 0xd1);
  }
  void AllocateSelf() {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  void AllocateSelfN(size_type n) {
    if (n > 1) {
      mpBegin = DoAllocate(n);
      mpEnd = mpBegin;
      mpCapacity = mpBegin + n;
    } else
      AllocateSelf();
  }
  void RangeInitializeInl(const T* pBegin, const T* pEnd) {
    const size_type n = (size_type)(pEnd - pBegin);
    AllocateSelfN(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
};
}
typedef eastl::basic_string_s0062_2f20<wchar_t> string16;
namespace EA {
namespace COM {
class IUnknown32_s0062_2f20 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t type) const = 0;
  virtual void pvUnknown3();
  ~IUnknown32_s0062_2f20() {}
};  // namespace COM
}
}
namespace EA {
template <typename T>
class RefCountVTemplate_s0062_2f20 {
 public:
  RefCountVTemplate_s0062_2f20() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s0062_2f20() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
template <typename T>
class AutoRefCount_s0062_2f20 {
 public:
  T* mpObject;
  AutoRefCount_s0062_2f20() : mpObject(0) {}
  AutoRefCount_s0062_2f20(T* pObject) : mpObject(pObject) {
    if (mpObject) mpObject->AddRef();
  }
  AutoRefCount_s0062_2f20& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  ~AutoRefCount_s0062_2f20() {
    if (mpObject) mpObject->Release();
  }
  T*& AsOutParam() {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return mpObject;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace EA {
namespace UTFWin {
class IWindow_s0062_2f20;
}
}
namespace EA {
namespace UTFWin {
struct Message_s0062_2f20 {
  IWindow_s0062_2f20* mpSource;  // +0x0
  uint32_t pad4;
  uint32_t mEventType;  // +0x8
  uint32_t padc;
  uint32_t mKey;  // +0x10
};
}
}
namespace EA {
namespace UTFWin {
struct SPPoint {
  float x, y;
  SPPoint() {}
  SPPoint(float x_, float y_) : x(x_), y(y_) {}
  SPPoint(const SPPoint& p) : x(p.x), y(p.y) {}
};
}
}
namespace EA {
namespace UTFWin {
struct IWindowChildIter {  // eastl::intrusive_list iterator (value = node pointer)
  void* mpNode;
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s0062_2f20 {
 public:
  virtual int AddRef();                                    // +0
  virtual int Release();                                   // +4
  PV(2)
  virtual void* Cast(uint32_t type);                       // +0xc
  virtual IWindow_s0062_2f20* GetParent();                            // +0x10
  PV(5) PV(6)
  virtual uint32_t GetControlID();                         // +0x1c
  virtual uint32_t GetCommandID();                         // +0x20
  PV(9)
  virtual uint32_t GetFlags();                             // +0x28
  PV(11) PV(12)
  virtual const float* GetArea();                          // +0x34
  virtual const float* GetRealArea();                      // +0x38
  virtual const wchar_t* GetCaption();                     // +0x3c
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  PV(25)
  virtual void SetSize(float w, float h);                  // +0x68
  PV(27)
  virtual void SetPosition(float x, float y);              // +0x70
  PV(29) PV(30)
  virtual void SetFlag(uint32_t flag, bool value);         // +0x7c
  virtual void SetCaption(const wchar_t* text);            // +0x80
  PV(33) PV(34) PV(35)
  virtual int Invalidate();                                // +0x90
  PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
  virtual bool ToLocalCoordinates2(SPPoint globalPos, SPPoint* pOut);  // +0xc8
  virtual IWindowChildIter GetChildrenBegin();             // +0xcc
  virtual IWindowChildIter GetChildrenEnd();               // +0xd0
  PV(53) PV(54) PV(55)
  virtual void DisposeWindowFamily(IWindow_s0062_2f20* pChild);       // +0xe0
  PV(57) PV(58) PV(59) PV(60) PV(61) PV(62)
  virtual bool IsEnabled(int index);                       // +0xfc
  PV(64)
  virtual void AddWinProc(class IWinProc_s0062_2f20* p);              // +0x104
  virtual void RemoveWinProc(class IWinProc_s0062_2f20* p);           // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s0062_2f20 : public COM::IUnknown32_s0062_2f20 {
 public:
  virtual uint32_t GetEventFlags();
  virtual bool HandleUIMessage(IWindow_s0062_2f20* pWindow, const Message_s0062_2f20& msg) = 0;
};
}
}
namespace EA {
namespace UTFWin {
class IWindowManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  PV(15) PV(16) PV(17) PV(18)
  virtual void SetFocus(int a, IWindow_s0062_2f20* pWindow);  // +0x4c
};
}
}
struct ResourceKey {
  uint32_t mInstance, mType, mGroup;
  static ResourceKey Make(uint32_t instance, uint32_t type, uint32_t group) {
    ResourceKey k;
    k.mInstance = instance;
    k.mType = type;
    k.mGroup = group;
    return k;
  }
};
class cSPUILayout_s0062_2f20 {
 public:
  cSPUILayout_s0062_2f20();           // 0x00810000
  virtual ~cSPUILayout_s0062_2f20();
  virtual int AddRef();
  virtual int Release();
  bool SetVisibility(bool b);                                                    // 0x00810590
  void SetParentWin(EA::UTFWin::IWindow_s0062_2f20* pParent, bool b, uint32_t id);          // 0x008121b0
  bool Init(const ResourceKey& key, int a, uint32_t b);                // 0x008120d0
  EA::UTFWin::IWindow_s0062_2f20* FindWindowByID(uint32_t id, bool recursive);    // 0x008105b0
  void Shutdown(bool b);                                               // 0x00811ad0
  uint32_t pad[5];
};
namespace SP {
EA::UTFWin::IWindowManager* WindowManager();  // 0x0067caa0
}
extern "C" __declspec(dllimport) double __cdecl wcstod(const wchar_t*, wchar_t**);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
using EA::AutoRefCount_s0062_2f20;
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
  virtual EA::UTFWin::IWindow_s0062_2f20* GetWindow(uint32_t type);  // +0xc
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
extern const wchar_t* gAttrType;      // 0x01521294
extern const wchar_t* gTypeSubmit;    // 0x015212b8
extern const wchar_t* gAttrTabIndex;  // 0x015212b0
inline unsigned int WStrLen(const wchar_t* s) {
  const wchar_t* ps = s + 1;
  do {
  } while (*s++);
  return (unsigned int)(s - ps);
}
namespace SP {
namespace Pollen {
using namespace EA;
}
}
namespace SP {
namespace Pollen {
using namespace EA::UTFWin;
}
}
namespace SP {
namespace Pollen {
struct DomHookX : DomHook {
  DomNode** GetNode(DomNode** ppNode);
};
}
}
namespace SP {
namespace Pollen {
struct FormControlRef {
  uint32_t pad[0x44 / 4];
  IControlHolder* mpControl;  // +0x44
};
}
}
namespace SP {
namespace Pollen {
struct DomDocument {
  uint32_t pad[0x38 / 4];
  uint32_t mUnk38;  // +0x38
  uint32_t mUnk3c;  // +0x3c
  DomElement* mpRoot;  // +0x40
  void DestroyFormControls();  // 0x008e2890
  bool FUN_008e29e0(bool b);   // 0x008e29e0
};
}
}
namespace SP {
namespace Pollen {
struct XListNode {
  XListNode* mpNext;
  XListNode* mpPrev;
  DomElement* mpElement;
};
}
}
namespace SP {
namespace Pollen {
struct XList {
  XListNode* mpNext;
  XListNode* mpPrev;
  bool empty() const { return mpNext == (const XListNode*)this; }
};
}
}
namespace SP {
namespace Pollen {
struct WXBase0 {
  virtual void wx0();
};
}
}
namespace SP {
namespace Pollen {
struct WXBase1 {  // the window part (IWindow-like)
  virtual void wx1();
  void SetHoverHandler(void* p);  // 0x00961fc0
  uint32_t pad[0x204 / 4];
};
}
}
namespace SP {
namespace Pollen {
struct WXBase2 {
  virtual void wx2();
};
}
}
namespace SP {
namespace Pollen {
struct WXBase3 {
  virtual void wx3();
  uint32_t pad[(0x23c - 0x214) / 4];
};
}
}
namespace SP {
namespace Pollen {
struct WinXHTML : WXBase0, WXBase1, WXBase2, WXBase3 {
  WinXHTML();              // 0x00993c10
  virtual ~WinXHTML();     // 0x00993000
  bool DoMessage(const Message_s0062_2f20& msg);  // 0x00993130
  void SetFormControlValue(DomElement* e, const wchar_t* value);  // 0x00995b20
  DomDocument* mpDocument;  // +0x23c
  uint32_t pad2[(0xa67c - 0x240) / 4];
};
}
}
namespace SP {
namespace Pollen {
class cXHTMLWin : public WinXHTML {
 public:
  cXHTMLWin();
  virtual ~cXHTMLWin();
  void DestroyFormControl(DomElement* e);  // 0x00623370
  bool FocusNextControl();                  // 0x006233f0
  bool SubmitForm();                        // 0x00623660
  bool OnKeyDown(int a, int key, int c);    // 0x00623ef0
  bool OnKeyUp(int a, int key, int c);      // 0x00622fe0
  bool HandleMessage(const Message_s0062_2f20& msg);   // 0x00623190
  void SetFormControlValue(DomElement* e, const wchar_t* value);  // 0x00623c90

  IWindow_s0062_2f20* mpFormHost;  // +0xa67c
  uint32_t pad3[(0xa6dc - 0xa680) / 4];
  XList mControlList;     // +0xa6dc
  uint32_t pad4[(0xa888 - 0xa6e4) / 4];
  uint32_t mSubmitButtonID;  // +0xa888
  uint32_t pad5[(0xa8e8 - 0xa88c) / 4];
  XList mFormList;        // +0xa8e8
  uint32_t pad6;
  bool mbSubmitting;      // +0xa8f4
};
}
}
namespace SP {
namespace Pollen {
inline void FreeListNodes(XList* list) {
  XListNode* p = list->mpNext;
  XListNode* end = (XListNode*)list;
  while (p != end) {
    XListNode* cur = p;
    p = p->mpNext;
    EASTL_allocator_deallocate(cur);
  }
}
}
}
namespace SP {
namespace Pollen {
inline void ClearList(XList* list) {
  FreeListNodes(list);
  list->mpNext = (XListNode*)list;
  list->mpPrev = (XListNode*)list;
}
}
}
namespace SP {
namespace Pollen {
struct IPropValue {
  uint8_t pad[0x10];
  uint8_t mFlags;   // +0x10 (0x30: indirect storage)
  uint8_t pad11;
  uint16_t mType;   // +0x12
  const float* GetFloatPtr();
};
}
}
namespace SP {
namespace Pollen {
extern const float gDefaultFloat;  // 0x015d9c6c
}
}
namespace SP {
namespace Pollen {
struct IPropertyListV {
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, IPropValue** ppValue);  // +0x24
};
}
}
namespace SP {
namespace Pollen {
struct cFloatPropWatch {
  uint32_t pad;
  uint32_t mPropID;  // +4
  uint32_t pad2;
  float mValue;      // +0xc
  // @ 0x006231d0
  bool Refresh(IPropertyListV* pProps);
};
}
}
namespace SP {
namespace Pollen {
struct ITextWin {
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void SetFlag2(bool b);  // +0x14
};
}
}
namespace SP {
namespace Pollen {
struct HoverBaseA {
  virtual void ha0();
};
}
}
namespace SP {
namespace Pollen {
class cSPHoverTitle : public HoverBaseA, public EA::RefCountVTemplate_s0062_2f20<int> {
 public:
  cSPHoverTitle(IWindow_s0062_2f20* pParent);
  ~cSPHoverTitle();
  void Layout();    // 0x00623830
  void Load();      // 0x006239c0
  AutoRefCount_s0062_2f20<IWindow_s0062_2f20> mpParent;          // +0xc
  AutoRefCount_s0062_2f20<cSPUILayout_s0062_2f20> mpLayout;      // +0x10
  AutoRefCount_s0062_2f20<IWindow_s0062_2f20> mpTitleWin;        // +0x14
  float mDelay;                            // +0x18
  string16 mText;                          // +0x1c
  AutoRefCount_s0062_2f20<IPropertyListV> mpProps;    // +0x2c
};
}
}
namespace SP {
namespace Pollen {
extern const float gHoverOffsetX, gHoverOffsetY;  // 0x013fdcf4, 0x013fdcf8
}
}
namespace SP {
namespace Pollen {
void GetCursorPosition(float* pX, float* pY);  // 0x00804ed0
}
}
namespace SP {
namespace Pollen {
extern const float gPadX, gPadFlipX, gPadY, gPadFlipY;  // 0x015f6144, 0x015f6194, 0x015f6184, 0x015f6164
}
}
namespace SP {
namespace Pollen {
extern int gWindowNodeOffset;  // 0x01440aec : offset from an intrusive child-list node to its IWindow
}
}
namespace SP {
namespace Pollen {
extern const wchar_t* gAttrSelected;  // L"selected" at 0x013fdd28
}
}
namespace SP {
namespace Pollen {
extern const wchar_t* gAttrValue;     // L"value"    at 0x013fda1c
}
}
namespace SP {
namespace Pollen {
struct cSPUIPopupMenuWin {
  uint32_t pad[0x888 / 4];
  uint32_t mItemIndex;  // +0x888
  void OnMenuItemSelected(int a, void* pItem);  // 0x0081bef0
};
}
}
// ---- items of slice s00622f20 end

// ---- items of slice s00623f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyWString[];   // shared empty-string storage (0x1667bac)
extern const wchar_t* gAttrValue;      // 0x1521298  L"value"
extern const wchar_t* gAttrLabel;      // 0x152129c  L"label"
extern const wchar_t* gAttrDisabled;   // 0x15212a0  L"disabled"
extern const wchar_t* gAttrReadonly;   // 0x15212a4  L"readonly"
extern const wchar_t* gAttrSize;       // 0x15212a8  L"size"
extern const wchar_t* gAttrMultiple;   // 0x15212ac  L"multiple"
extern const wchar_t* gValButton;      // 0x15212b4  L"button"
extern const wchar_t* gValSubmit;      // 0x15212b8  L"submit"
extern const wchar_t* gValReset;       // 0x15212bc  L"reset"
extern const wchar_t* gValText;        // 0x15212c4  L"text"
extern const float gTextMarginUnit;    // 0x14853e0
extern const float kDelayShort; // 0x15f6154
extern const float kDelayLong;  // 0x15f627c
extern const wchar_t gEmptyCaption[];   // L"" (0x13ec468)
struct Vector3 { float x, y, z; Vector3() {} Vector3(float a, float b, float c) : x(a), y(b), z(c) {} };
static inline Vector3 operator*(const Vector3& v, float s) { return Vector3(v.x * s, v.y * s, v.z * s); }
struct WString { wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity;   // eastl::basic_string<wchar_t>
    void assign(const wchar_t* b, const wchar_t* e);   // 0x00423650
};
struct LinkNode { LinkNode* mpNext; LinkNode* mpPrev; };
struct WStringLocal {   // eastl::basic_string<wchar_t> local with an inline default ctor
    const wchar_t* mpBegin;
    const wchar_t* mpEnd;
    const wchar_t* mpCapacity;
    WStringLocal() : mpBegin(gEmptyWString), mpEnd(gEmptyWString), mpCapacity(gEmptyWString + 1) {}
    ~WStringLocal();   // 0x933960 (SP::QualifyNameWithGroup in the name table: really the string dtor)
};
float __cdecl GetElapsedSeconds();   // SPUIHelpers::GetElapsedSeconds
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);
void* __cdecl FUN_009512c0();
void* __cdecl FUN_009512d0(unsigned size, unsigned align, const char* name, void* alloc);
struct IQuery {
    virtual void q0();
    virtual void q1();
    virtual void q2();
    virtual void* Query(unsigned id);   // +0x0c
};
struct DomNode_s0062_3f90 {
    virtual void d0();
    virtual void d1();
    virtual void GetText(WString* out);   // +0x08
    LinkNode link;                        // +4 (mpNext, mpPrev)
    int Type();                           // EA::XHTML::DOM::Node::Type (0xfc7e50)
};
struct Element : DomNode_s0062_3f90 {
    char padE[0x18 - 0x0c];
    LinkNode mChildren;                   // +0x18 circular anchor
    char padE2[0x28 - 0x20];
    int mType;                            // +0x28
    char padE3[0x44 - 0x2c];
    IQuery* mpControl;                    // +0x44
    const wchar_t* GetAttrValue(const wchar_t* name);   // 0x8e45b0
};
struct FormControl : Element {
    void SetControl(void* pWindow);       // 0x8e4b60
};
struct IWinObj {
    virtual void AddRef();
    virtual void Release();
    virtual void w2();
    virtual void w3();
    virtual void w4();
    virtual void w5();
    virtual void w6();
    virtual void w7();
    virtual void w8();
    virtual void w9();
    virtual void w10();
    virtual void w11();
    virtual void w12();
    virtual void w13();
    virtual void w14();
    virtual void w15();
    virtual void w16();
    virtual void w17();
    virtual void w18();
    virtual void w19();
    virtual void w20();
    virtual void SetCommand(unsigned id);
    virtual void w22();
    virtual void w23();
    virtual void w24();
    virtual void w25();
    virtual void w26();
    virtual void w27();
    virtual void w28();
    virtual void w29();
    virtual void w30();
    virtual void SetFlag(int flag, int value);
    virtual void SetCaption(const wchar_t* text);
    virtual void w33();
    virtual void w34();
    virtual void w35();
    virtual void w36();
    virtual void w37();
    virtual void w38();
    virtual void w39();
    virtual void w40();
    virtual void w41();
    virtual void w42();
    virtual void SetColorA(unsigned c);
    virtual void SetColorB(unsigned c);
    virtual void w45();
    virtual void SetProperty(unsigned id, void* pRef);
};
struct ITextCtl {
    virtual void t0();
    virtual void Release();
    virtual void t2();
    virtual void t3();
    virtual IWinObj* GetWindow();
    virtual void t5();
    virtual void t6();
    virtual void t7();
    virtual void t8();
    virtual void t9();
    virtual void SetMargins(const float* rect);
    virtual void t11();
    virtual void t12();
    virtual void t13();
    virtual void t14();
    virtual void t15();
    virtual void SetAlign(int a);
    virtual void SetFlags(int a, int b);
    virtual void t18();
    virtual void t19();
    virtual void t20();
    virtual void t21();
    virtual void t22();
    virtual void t23();
    virtual void t24();
    virtual void t25();
    virtual void SetMaxLength(int n);
    virtual void t27();
    virtual void t28();
    virtual void t29();
    virtual void t30();
    virtual void t31();
    virtual void t32();
    virtual void t33();
    virtual void t34();
    virtual void t35();
    virtual void t36();
    virtual void t37();
    virtual void t38();
    virtual void t39();
    virtual void t40();
    virtual void t41();
    virtual void t42();
    virtual void t43();
    virtual void t44();
    virtual void t45();
    virtual void t46();
    virtual void t47();
    virtual void t48();
    virtual void t49();
    virtual void t50();
    virtual void t51();
    virtual void t52();
    virtual void t53();
    virtual void t54();
    virtual void t55();
    virtual void t56();
    virtual void t57();
    virtual void SetFont(int a, void* font);
};
struct IWinContainer {
    virtual void c0();
    virtual void c1();
    virtual void c2();
    virtual void c3();
    virtual void c4();
    virtual void c5();
    virtual void c6();
    virtual void c7();
    virtual void c8();
    virtual void c9();
    virtual void c10();
    virtual void c11();
    virtual void c12();
    virtual void c13();
    virtual void c14();
    virtual void c15();
    virtual void c16();
    virtual void c17();
    virtual void c18();
    virtual void c19();
    virtual void c20();
    virtual void c21();
    virtual void c22();
    virtual void c23();
    virtual void c24();
    virtual void c25();
    virtual void c26();
    virtual void c27();
    virtual void c28();
    virtual void c29();
    virtual void c30();
    virtual void c31();
    virtual void c32();
    virtual void c33();
    virtual void c34();
    virtual void c35();
    virtual void c36();
    virtual void c37();
    virtual void c38();
    virtual void c39();
    virtual void c40();
    virtual void c41();
    virtual void c42();
    virtual void c43();
    virtual void c44();
    virtual void c45();
    virtual void c46();
    virtual void c47();
    virtual void c48();
    virtual void c49();
    virtual void c50();
    virtual void c51();
    virtual void c52();
    virtual void c53();
    virtual void AddWindow(IWinObj* w);
};
struct cSPUIPopupMenuWin_s0062_3f90 {
    virtual void AddRef();
    virtual void Release();
    char pad[0x8c8 - 4];
    unsigned mField8c8;
    void* AddMenuItem(const unsigned* key, int a, int b, int c);   // 0x81b6a0
};
struct cSPUILayout_s0062_3f90 {   // 0x810000 ctor ... (24 bytes of state)
    unsigned pad[6];
    cSPUILayout_s0062_3f90();
    ~cSPUILayout_s0062_3f90();
    bool Init(const unsigned* key, int a, int b);                  // 0x8120d0
    IWinObj* FindWindowByID(int id, int recurse);                  // 0x8105b0
    void Shutdown(bool b);                                         // 0x811ad0
};
template <class T> struct AutoRef {   // EA::AutoRefCount<T> (AsPPTypeParam is not inlined in this build)
    T* mp;
    AutoRef() : mp(0) {}
    ~AutoRef() { if (mp) mp->Release(); }
    T** AsPPTypeParam();
    void Assign(T* p);   // operator=(T*): AddRef new, Release old (0xb5f950)
};
bool __cdecl CreateXHTMLButton(IWinObj** pOut);    // SP::Pollen::CreateXHTMLButton (0x6230b0)
cSPUIPopupMenuWin_s0062_3f90* __cdecl InterfaceCastPopup(AutoRef<IWinObj>* p);   // 0x623090
struct WinXHTMLBase {
    bool ShouldCreate(FormControl* pCtl);          // 0x623000
    void CreateFormControlBase(FormControl* pCtl); // 0x994c80  EA::UTFWinExtras::WinXHTML::CreateFormControl
};
struct WinTextEditObj {
    char pad4[4];
    IWinObj mWin;                                  // +4 (subobject; only its vtable is used)
    char pad5[0x20c - 8];
    ITextCtl mText;                                // +0x20c
    WinTextEditObj();                              // 0x98c110
    void SetMode(int mode);                        // 0x9896c0
};
struct FormControlRef_s0062_3f90 {   // 12-byte ref object stored as a window property
    void* vtbl;
    int mnRefCount;
    FormControl* mpControl;
    FormControlRef_s0062_3f90(FormControl* p) : mnRefCount(0), mpControl(p) {}
    virtual void vf0();
};
struct SMessage { char pad[8]; int mId; char pad2[0x18 - 0x0c]; const wchar_t* mpData; };
struct IPopWin {
    virtual void pw0();
    virtual void pw1();
    virtual void pw2();
    virtual void pw3();
    virtual void pw4();
    virtual void pw5();
    virtual void pw6();
    virtual void pw7();
    virtual void pw8();
    virtual void pw9();
    virtual unsigned IsShown();
    virtual void pw11();
    virtual void pw12();
    virtual void pw13();
    virtual void pw14();
    virtual void pw15();
    virtual void pw16();
    virtual void pw17();
    virtual void pw18();
    virtual void pw19();
    virtual void pw20();
    virtual void pw21();
    virtual void pw22();
    virtual void pw23();
    virtual void pw24();
    virtual void pw25();
    virtual void pw26();
    virtual void pw27();
    virtual void pw28();
    virtual void pw29();
    virtual void pw30();
    virtual void SetFlag(int flag, int value);
};
struct WStrMember {   // eastl::basic_string<wchar_t> member (12 bytes)
    wchar_t* a; wchar_t* b; wchar_t* c;
    WStrMember& operator=(const wchar_t* p);   // 0x5c3d90
};
struct cPopupTimer {
    char pad0[0x10];
    int mField10;
    IPopWin* mpWin;
    float mNextTime;
    WStrMember mText;     // +0x1c
    bool OnMessage(void* unused, SMessage* m);   // @ 0x00623f90
    void Refresh();       // 0x623830
    void Create();        // 0x6239c0
};
struct IFontRef { virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3(); virtual void* GetFont(); };
struct IBaseObj { virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual unsigned GetHandle(); };
struct TabStopNode { TabStopNode* mpNext; TabStopNode* mpPrev; FormControl* mpValue; };
struct cXHTMLWin_s0062_3f90 {   // the WinXHTML sub-object at +0x20c of the real window; offsets are from `this` here
    char pad0[0xa65c];
    unsigned mColorText;          // +0xa65c
    char pad1[0xa67c - 0xa660];
    IWinContainer* mpContainer;   // +0xa67c
    char pad2[0xa684 - 0xa680];
    IFontRef* mpFontBody;         // +0xa684
    char pad3[0xa698 - 0xa688];
    IFontRef* mpFontEdit;         // +0xa698
    char pad4[0xa6dc - 0xa69c];
    TabStopNode mTabStops;        // +0xa6dc list anchor (value unused)
    void CreateFormControl(FormControl* pCtl);                       // 0x00624080
    void GetFormControlValue(FormControl* pCtl, WString* pOut);      // 0x006248d0
    void GetFormControlValueBase(FormControl* pCtl, WString* pOut);  // 0x00995ea0
};
void __fastcall LinkListBegin(LinkNode* anchor, LinkNode** pOut);   // FUN_00623260 (thiscall in orig; helper)
// ---- items of slice s00623f90 end

// @ 0x00622fe0
namespace SP { namespace Pollen {
bool cXHTMLWin::OnKeyUp(int a, int key, int c)
{
  if (key == 0xd) {
    mbSubmitting = false;
    return true;
  }
  return false;
}
}}  // namespace SP::Pollen

// @ 0x006230b0
namespace SP { namespace Pollen {
bool CreateXHTMLButton(IWindow_s0062_2f20** ppButton)
{
  cSPUILayout_s0062_2f20 layout;
  bool ok = false;
  ResourceKey key = ResourceKey::Make(0xceb6dd52, 0x510a95b, 0x40464100);
  if (layout.Init(key, 0, 0x5b598fa)) {
    AutoRefCount_s0062_2f20<IWindow_s0062_2f20> w(layout.FindWindowByID(0, true));
    if (w.mpObject) {
      *ppButton = w.mpObject;
      w.mpObject->AddRef();
      ok = true;
    }
    layout.Shutdown(true);
  }
  return ok;
}
}}  // namespace SP::Pollen

// @ 0x00623150
namespace SP { namespace Pollen {
void __stdcall ShowFormControl(FormControlRef* c, int unused)
{
  IControlHolder* h = c->mpControl;
  IWindow_s0062_2f20* w = h ? h->GetWindow(0xeeee8218) : 0;
  w->SetFlag(1, true);
}
}}  // namespace SP::Pollen

// @ 0x00623190
namespace SP { namespace Pollen {
bool cXHTMLWin::HandleMessage(const Message_s0062_2f20& msg)
{
  if (msg.mEventType == 0x287259f6 && msg.mpSource) {
    uint32_t id = mSubmitButtonID;
    if ((uint32_t)msg.mpSource->GetParent() == id) return true;
  }
  return DoMessage(msg);
}
}}  // namespace SP::Pollen

// @ 0x006231d0
namespace SP { namespace Pollen {
bool cFloatPropWatch::Refresh(IPropertyListV* pProps)
{
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
}}  // namespace SP::Pollen

// @ 0x00623260
namespace SP { namespace Pollen {
DomNode** DomHookX::GetNode(DomNode** ppNode)
{
  DomNode* node = this ? (DomNode*)((char*)this - 4) : 0;
  *ppNode = node;
  return ppNode;
}
}}  // namespace SP::Pollen

// @ 0x00623280
namespace SP { namespace Pollen {
cXHTMLWin::~cXHTMLWin()
{
  DomDocument* doc = mpDocument;
  if (doc) {
    doc->DestroyFormControls();
    doc->mUnk38 = 0;
    doc->mUnk3c = 0;
  }
  FreeListNodes(&mFormList);
}
}}  // namespace SP::Pollen

// @ 0x00623370
namespace SP { namespace Pollen {
void cXHTMLWin::DestroyFormControl(DomElement* e)
{
  XList* list = &mControlList;
  if (!list->empty()) ClearList(list);
  IControlHolder* h = e->mpControl;
  if (h) {
    IWindow_s0062_2f20* w = h->GetWindow(0xeeee8218);
    if (w) {
      if (w->GetParent()) mpFormHost->DisposeWindowFamily(w);
      e->SetControl(0);
    }
  }
}
}}  // namespace SP::Pollen

// @ 0x006233f0
namespace SP { namespace Pollen {
bool cXHTMLWin::FocusNextControl()
{
  XListNode* const end = (XListNode*)&mFormList;
  XListNode* start = mFormList.mpNext;
  if (start != end) {
    do {
      IControlHolder* h = start->mpElement->mpControl;
      if (h) {
        IWindow_s0062_2f20* w = h->GetWindow(0xeeee8218);
        if (w && w->IsEnabled(0)) break;
      }
      start = start->mpNext;
    } while (start != end);
  }
  if (start == end) return false;
  IWindow_s0062_2f20* best = 0;
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
}}  // namespace SP::Pollen

// @ 0x00623570
namespace SP { namespace Pollen {
DomElement* FindSubmitChild(DomElement* e)
{
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
}}  // namespace SP::Pollen

// @ 0x00623610
namespace SP { namespace Pollen {
DomElement* FindFormChild(DomElement* e)
{
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
}}  // namespace SP::Pollen

// @ 0x00623660
namespace SP { namespace Pollen {
bool cXHTMLWin::SubmitForm()
{
  DomElement* form = 0;
  for (XListNode* n = mFormList.mpNext; n != (XListNode*)&mFormList; n = n->mpNext) {
    IControlHolder* h = n->mpElement->mpControl;
    if (h) {
      IWindow_s0062_2f20* w = h->GetWindow(0xeeee8218);
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
}}  // namespace SP::Pollen

// @ 0x00623830
namespace SP { namespace Pollen {
void cSPHoverTitle::Layout()
{
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
}}  // namespace SP::Pollen

// @ 0x00623c90
namespace SP { namespace Pollen {
void cXHTMLWin::SetFormControlValue(DomElement* e, const wchar_t* value)
{
  IControlHolder* h = e->mpControl;
  IWindow_s0062_2f20* menu = 0;
  if (h) menu = (IWindow_s0062_2f20*)h->GetWindow(0x4c058d5);
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
  IWindow_s0062_2f20* list = (IWindow_s0062_2f20*)((char*)menu + 4);
  IWindowChildIter it = list->GetChildrenBegin();
  IWindowChildIter end = list->GetChildrenEnd();
  while (it.mpNode != end.mpNode) {
    IWindow_s0062_2f20* w = (IWindow_s0062_2f20*)((char*)it.mpNode + gWindowNodeOffset);
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
}}  // namespace SP::Pollen

// @ 0x00623ef0
namespace SP { namespace Pollen {
bool cXHTMLWin::OnKeyDown(int a, int key, int c)
{
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
}}  // namespace SP::Pollen

// @ 0x00623f90
bool cPopupTimer::OnMessage(void* unused, SMessage* m)
{
    if (m->mId == 0xc) {
        float now = GetElapsedSeconds();
        if (mNextTime <= now) {
            if (mpWin->IsShown() & 1) {
                mpWin->SetFlag(1, 0);
                mNextTime = FLT_MAX;
            } else {
                Refresh();
                mNextTime = GetElapsedSeconds() + kDelayShort;
            }
        }
        return false;
    }
    if (m->mId == 0x51a1a2e) {
        if (m->mpData) {
            if (mField10 == 0)
                Create();
            if (mpWin) {
                if (mpWin->IsShown() & 1)
                    mpWin->SetFlag(1, 0);
                mText = m->mpData;
                mNextTime = GetElapsedSeconds() + kDelayLong;
            }
            return true;
        }
        if (mpWin) {
            mpWin->SetFlag(1, 0);
            mNextTime = FLT_MAX;
        }
        return true;
    }
    return false;
}

// @ 0x00624080
void cXHTMLWin_s0062_3f90::CreateFormControl(FormControl* pCtl)
{
    WinXHTMLBase* pBase = (WinXHTMLBase*)((char*)this - 0x20c);
    if (pBase->ShouldCreate(pCtl)) {
        TabStopNode* pAnchor = &mTabStops;
        TabStopNode* pNode = new("Editor", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) TabStopNode;
        if (&pNode->mpValue)
            pNode->mpValue = pCtl;
        pNode->mpNext = pAnchor;
        pNode->mpPrev = pAnchor->mpPrev;
        pAnchor->mpPrev->mpNext = pNode;
        pAnchor->mpPrev = pNode;
    }

    AutoRef<IWinObj> win;
    const wchar_t* pType = pCtl->GetAttrValue(gAttrType);
    const wchar_t* pValue = pCtl->GetAttrValue(gAttrValue);
    const wchar_t* pSize = pCtl->GetAttrValue(gAttrSize);
    const wchar_t* pReadonly = pCtl->GetAttrValue(gAttrReadonly);

    switch (pCtl->mType) {
    case 0x17:   // <input>
        if (!pType)
            break;
        if (_wcsicmp(pType, gValButton) == 0) {
            if (CreateXHTMLButton(win.AsPPTypeParam())) {
                if (pValue)
                    win.mp->SetCaption(pValue);
                else
                    win.mp->SetCaption(gEmptyCaption);
            }
            goto finalize;
        }
        if (_wcsicmp(pType, gValSubmit) == 0) {
            if (CreateXHTMLButton(win.AsPPTypeParam())) {
                if (pValue) {
                    win.mp->SetCaption(pValue);
                } else {
                    win.mp->SetCaption(L"Submit");
                    win.mp->SetCommand(0x344a710);
                }
            }
            goto finalize;
        }
        if (_wcsicmp(pType, gValReset) == 0) {
            if (CreateXHTMLButton(win.AsPPTypeParam())) {
                if (pValue) {
                    win.mp->SetCaption(pValue);
                } else {
                    win.mp->SetCaption(L"Reset");
                    win.mp->SetCommand(0x344a711);
                }
            }
            goto finalize;
        }
        if (_wcsicmp(pType, gValText) == 0) {
            void* pMem = FUN_009512d0(0x658, 8, "UTFWin/WinXHTML/WinTextEdit", FUN_009512c0());
            WinTextEditObj* pEdit = pMem ? ::new (pMem) WinTextEditObj() : 0;
            ITextCtl* pText = &pEdit->mText;
            win.Assign(pText->GetWindow());
            float margins[4] = { gTextMarginUnit, gTextMarginUnit, gTextMarginUnit, gTextMarginUnit };
            pText->SetMargins(margins);
            pEdit->SetMode(2);
            if (pValue)
                pEdit->mWin.SetCaption(pValue);
            if (pReadonly)
                pText->SetFlags(1, 1);
            if (pSize) {
                long n = wcstol(pSize, 0, 0);
                if (n)
                    pText->SetMaxLength(n);
            }
            win.mp->SetColorB(mColorText);
            win.mp->SetColorA(0xffccccee);
            goto finalize;
        }
        pBase->CreateFormControlBase(pCtl);
        break;

    case 0x18: {   // <select>
        const wchar_t* pMultiple = pCtl->GetAttrValue(gAttrMultiple);
        int rows = 1;
        if (pSize) {
            int n = (int)wcstol(pSize, 0, 0);
            rows = (n > 1) ? n : 1;
        }
        if (pMultiple || rows != 1) {
            pBase->CreateFormControlBase(pCtl);
            break;
        }
        {
            cSPUILayout_s0062_3f90 layout;
            AutoRef<cSPUIPopupMenuWin_s0062_3f90> popup;
            unsigned layoutKey[3] = { 0x7b9fba30, 0x510a95b, 0x40464100 };
            if (layout.Init(layoutKey, 0, 0x5b598fa)) {
                win.Assign(layout.FindWindowByID(0, 1));
                if (win.mp)
                    popup.Assign(InterfaceCastPopup(&win));
            }
            layout.Shutdown(true);
            if (popup.mp) {
                popup.mp->mField8c8 = ((IBaseObj*)((char*)this - 0x208))->GetHandle();
                LinkNode* pAnchor = &pCtl->mChildren;
                LinkNode* it = pAnchor;
                LinkListBegin(pAnchor, &it);
                Element* pCur = (Element*)it;
                for (;;) {
                    Element* pEnd = pAnchor->mpNext ? (Element*)((char*)pAnchor->mpNext - 4) : 0;
                    if (pCur == pEnd)
                        break;
                    DomNode_s0062_3f90* pChild = pCur->link.mpPrev ? (DomNode_s0062_3f90*)((char*)pCur->link.mpPrev - 4) : 0;
                    if (pChild->Type() == 1) {
                        Element* pElem = pCur->link.mpPrev ? (Element*)((char*)pCur->link.mpPrev - 4) : 0;
                        if (pElem->mType == 0x19) {
                            WStringLocal text;
                            const wchar_t* pLabel = pElem->GetAttrValue(gAttrLabel);
                            if (!pLabel) {
                                pElem->GetText((WString*)&text);
                                pLabel = text.mpBegin;
                            }
                            unsigned itemKey[3] = { 0xa10d844a, 0x510a95b, 0x40464100 };
                            void* pItem = popup.mp->AddMenuItem(itemKey, 0, 0, 0);
                            if (pItem)
                                ((IWinObj*)((char*)pItem + 4))->SetCaption(pLabel);
                        }
                    }
                    pCur = pCur->link.mpPrev ? (Element*)((char*)pCur->link.mpPrev - 4) : 0;
                }
            }
        }
        goto finalize;
    }

    case 0x1a: {   // <textarea>
        const wchar_t* pDisabled = pCtl->GetAttrValue(gAttrDisabled);
        void* pMem = FUN_009512d0(0x658, 8, "UTFWin/WinXHTML/WinTextEdit", FUN_009512c0());
        WinTextEditObj* pEdit = pMem ? ::new (pMem) WinTextEditObj() : 0;
        ITextCtl* pText = &pEdit->mText;
        win.Assign(pText->GetWindow());
        float margins[4] = { gTextMarginUnit, gTextMarginUnit, gTextMarginUnit, gTextMarginUnit };
        pText->SetMargins(margins);
        pText->SetMaxLength(0xff);
        pEdit->SetMode(2);
        pText->SetAlign(2);
        if (pReadonly)
            pText->SetFlags(1, 1);
        win.mp->SetColorB(mColorText);
        win.mp->SetColorA(0xffffffff);
        if (mpFontEdit)
            pText->SetFont(1, mpFontEdit->GetFont());
        if (mpFontBody)
            pText->SetFont(0, mpFontBody->GetFont());
        pCtl->SetControl(win.mp);
        FormControlRef_s0062_3f90* pRef = new("FormControlRef", 0, 0, 0, 0) FormControlRef_s0062_3f90(pCtl);
        win.mp->SetProperty(0x344a0b7, pRef);
        if (pDisabled)
            win.mp->SetFlag(2, 0);
        goto finalize;
    }

    case 0x1b:   // <button>
        if (win.mp) {
            IWinObj* old = win.mp;
            win.mp = 0;
            old->Release();
        }
        if (CreateXHTMLButton(win.AsPPTypeParam())) {
            if (pValue) {
                win.mp->SetCaption(pValue);
            } else if (_wcsicmp(pType, gValSubmit) == 0) {
                win.mp->SetCaption(L"Submit");
                win.mp->SetCommand(0x344a710);
            } else if (_wcsicmp(pType, gValReset) == 0) {
                win.mp->SetCaption(L"Reset");
                win.mp->SetCommand(0x344a711);
            }
        }
        goto finalize;

    default:
        pBase->CreateFormControlBase(pCtl);
        break;
    }
    return;

finalize:
    if (win.mp) {
        pCtl->SetControl(win.mp);
        FormControlRef_s0062_3f90* pRef = new("UI/FormControlRef", 0, 0, 0, 0) FormControlRef_s0062_3f90(pCtl);
        win.mp->SetProperty(0x344a0b7, pRef);
        if (pCtl->GetAttrValue(gAttrDisabled))
            win.mp->SetFlag(2, 0);
        win.mp->SetFlag(1, 0);
        mpContainer->AddWindow(win.mp);
    }
}

// @ 0x006248d0
void cXHTMLWin_s0062_3f90::GetFormControlValue(FormControl* pCtl, WString* pOut)
{
    IQuery* q = pCtl->mpControl;
    char* pSel;
    if (!q || !(pSel = (char*)q->Query(0x4c058d5))) {
        GetFormControlValueBase(pCtl, pOut);
        return;
    }
    int idx = 0;
    LinkNode* pAnchor = &pCtl->mChildren;
    Element* pNode = pAnchor->mpNext ? (Element*)((char*)pAnchor->mpNext - 4) : 0;
    for (;;) {
        Element* pEnd = pAnchor ? (Element*)((char*)pAnchor - 4) : 0;
        if (pNode == pEnd)
            return;
        if (pNode->Type() == 1) {
            int cur = idx++;
            if (*(int*)(pSel + 0x8ac) == cur) {
                const wchar_t* v = pNode->GetAttrValue(gAttrValue);
                if (!v) {
                    pNode->GetText(pOut);
                    return;
                }
                const wchar_t* e = v;
                while (*e)
                    ++e;
                pOut->assign(v, v + (e - v));
                return;
            }
        }
        LinkNode* n = pNode->link.mpNext;
        pNode = n ? (Element*)((char*)n - 4) : 0;
    }
}
