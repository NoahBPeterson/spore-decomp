// src/game/SPEditors/SPEditorNaming.cpp -- migrated from slice(s) s0064dbd0, s005bfb90, s005beaf0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorNaming.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/IDrawable.h"
#include "EA/UTFWin/IWindow.h"
#include "SP/cCollectableItems.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorLimbStructure.h"
#include "SP/cSPEditorManipulationObject.h"
#include "SP/cSPEditorModel.h"
#include "SP/cSPEditorNaming.h"
#include "SP/cSPEditorSpine.h"
#include "SP/cSpeciesSummarizer.h"
#include <new>
#include <float.h>
#include <string.h>
#include "EA/Messaging/IHandler.h"
#include "EA/Messaging/Server.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cISPEditorNameProvider.h"
#include "SP/cSPEditorPageControls.h"
#include "SP/cSPEditorPaintLikeThis.h"
#include "SP/cSPNameGuard.h"
#include "SP/cSPPaletteCategoryUI.h"
#include "SP/cSPUIAssetComments.h"
#include "SP/cSPUIAssetGrid.h"
#include <intrin.h>

// ---- items of slice s005beaf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
class Vector3Template_s005b_eaf0 {
 public:
  T x, y, z;
  Vector3Template_s005b_eaf0() {}
  Vector3Template_s005b_eaf0(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
};
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline Vector3Template_s005b_eaf0<T, N> operator+(const Vector3Template_s005b_eaf0<T, N>& a, const Vector3Template_s005b_eaf0<T, N>& b) {
  return Vector3Template_s005b_eaf0<T, N>(a.x + b.x, a.y + b.y, a.z + b.z);
}
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline Vector3Template_s005b_eaf0<T, N> operator-(const Vector3Template_s005b_eaf0<T, N>& a, const Vector3Template_s005b_eaf0<T, N>& b) {
  return Vector3Template_s005b_eaf0<T, N>(a.x - b.x, a.y - b.y, a.z - b.z);
}
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline Vector3Template_s005b_eaf0<T, N> operator*(const Vector3Template_s005b_eaf0<T, N>& a, T s) {
  return Vector3Template_s005b_eaf0<T, N>(a.x * s, a.y * s, a.z * s);
}
}
}
}
namespace EA {
namespace ResourceMan {
class Key_s005b_eaf0 {
 public:
  unsigned int mInstance;  // +0x0
  unsigned int mType;      // +0x4
  unsigned int mGroup;     // +0x8
};
}
}
bool IsReservedID(unsigned short id);  // FUN_004f56f0
struct cResourceFilter {
  // @ 0x005BF8C0
  bool IsValid(const EA::ResourceMan::Key_s005b_eaf0& unused, const EA::ResourceMan::Key_s005b_eaf0* key);
};
class IDrawable {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void SetHighlight(int a);                             // +0x1c
};
class IWindow {
 public:
  PV(0) PV(1) PV(2)
  virtual IDrawable* Cast(uint32_t typeID);                     // +0xc
  virtual IWindow* GetParent();                                 // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual uint32_t GetFlags();                                  // +0x28
  PV(11) PV(12) PV(13)
  virtual void Revalidate();                                    // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);                   // +0x7c
  virtual void SetCaption(const wchar_t* text);                 // +0x80
  PV(33) PV(34) PV(35)
  virtual void Refresh();                                       // +0x90
};
class cSPUILayout_s005b_eaf0 {
 public:
  IWindow* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
  void SetParentWin(IWindow* parent, bool b, uint32_t id);  // 0x008121b0 (cSPUILayout::SetParentWin)
  char pad[0xc];
};
namespace SP {
class cISPEditorNameProvider_s005b_eaf0;
}
namespace SP {
struct NameMessage {
  cISPEditorNameProvider_s005b_eaf0* mpProvider;  // +0x0
  uint32_t pad4;
  const wchar_t* mpText;               // +0x8
};
}
namespace SP {
struct MouseMessage {
  uint32_t pad0[2];
  struct Msg {
    uint32_t pad0[2];
    int mType;      // +0x8
    int mId;        // +0xc
    char mButton;   // +0x10
    char pad11[3];
    int mX;         // +0x14
    int mY;         // +0x18
  }* mpMsg;  // +0x8
};
}
namespace SP {
bool IsMouseCaptured();  // FUN_008053b0
}
namespace SP {
void ScreenToWindow(float x, float y, float* outX, float* outY);  // FUN_00804f80
}
namespace SP {
class IWindowManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  virtual IWindow* PickWindow(const float* point);  // +0x44
};
}
namespace SP {
IWindowManager* WindowManager();
}
namespace SP {
struct cSPEditorNamingWinProc {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void SetExpanded(bool expanded);  // +0x1c
};
}
namespace SP {
class cSPEditorNaming_s005b_eaf0 : public cSPEditorNamingWinProc {
 public:
  struct IHandlerRC {
    virtual bool HandleMessage(uint32_t messageID, void* message);
  };
  // the IHandlerRC base sits at +0x4
  struct Handler : public IHandlerRC {
    bool HandleMessage(uint32_t messageID, void* message);
    char pad04[8];
    bool mIsExpanded;                        // +0xc (full +0x10)
    bool mAllowNameEdit;                     // +0xd
    char pad0e[2];
    void* mNameGuard;                        // +0x10
    cSPUILayout_s005b_eaf0* mLayout;                    // +0x14 (full +0x18)
    cISPEditorNameProvider_s005b_eaf0* mpDataProvider;  // +0x18 (full +0x1c)
  } mHandler;                                // +0x4
  uint32_t mNameType;                        // +0x20
  struct WString { wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; int mAllocator; } mNamePrompt;  // +0x24
  IWindow* mOriginalParent;                  // +0x34

  void SetDisplayText(const wchar_t* text);  // 0x005bf950 (SP::cSPEditorNaming::SetDisplayText)
  void ResetParentWin();  // 0x005bfb70 (SP::cSPEditorNaming::ResetParentWin)
};
}
// ---- items of slice s005beaf0 end

// ---- items of slice s005bfb90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
namespace eastl {
extern wchar_t gEmptyString[2];
}
namespace eastl {
template <typename T>
inline unsigned int CharStrlen(const T* p) {
  const T* pCurrent = p;
  while (*pCurrent)
    ++pCurrent;
  return (unsigned int)(pCurrent - p);
}
}
namespace eastl {
class wstring {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  int mAllocator;
  wstring() {
    mpEnd = mpBegin = gEmptyString;
    mpCapacity = mpBegin + 1;
  }
  wstring(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
  ~wstring() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin)
      EASTL_allocator_deallocate(mpBegin);
  }
  void RangeInitialize(const wchar_t* p);
  wstring& trim();
  void sprintf(const wchar_t* fmt, ...);
  wstring& assign(const wchar_t* first, const wchar_t* last);  // WString_Assign (0x00423650)
  const wchar_t* c_str() const { return mpBegin; }
  bool empty() const { return mpEnd == mpBegin; }
};
}
namespace EA {
template <typename T>
class AutoRefCount_s005b_fb90 {
 public:
  T* mpObject;
  AutoRefCount_s005b_fb90() : mpObject(0) {}
  ~AutoRefCount_s005b_fb90() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005b_fb90& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005b_fb90 {
 public:
  RefCountVTemplate_s005b_fb90() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005b_fb90() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace ResourceMan {
struct Key_s005b_fb90 {
  unsigned int mInstance, mType, mGroup;
  Key_s005b_fb90(unsigned int i, unsigned int t, unsigned int g) : mInstance(i), mType(t), mGroup(g) {}
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005b_fb90;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005b_fb90 {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2)
  virtual void* Cast(uint32_t typeID);                  // +0xc
  PV(4) PV(5) PV(6)
  virtual uint32_t GetControlID();                      // +0x1c
  PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual const wchar_t* GetCaption();                  // +0x3c
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);           // +0x7c
  virtual void SetCaption(const wchar_t* text);         // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41)
  virtual IWindow_s005b_fb90* GetDrawable();                       // +0xa8
  PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
  PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s005b_fb90* proc);              // +0x104
  virtual void RemoveWinProc(IWinProc_s005b_fb90* proc);           // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005b_fb90 {
 public:
  ~IWinProc_s005b_fb90() {}
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4)
  virtual bool HandleUIMessage(IWindow_s005b_fb90* window, const void* message);  // +0x14
  PV(6)
};
}
}
namespace EA {
namespace UTFWin {
class IButtonDrawable {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetImageState(int state, bool value);    // +0x28
};
}
}
namespace EA {
namespace UTFWin {
class ITextEdit {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  PV(31) PV(32) PV(33) PV(34) PV(35) PV(36)
  virtual void SetSelection(int start, int end);        // +0x94
  PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52)
  PV(53) PV(54)
  virtual void SelectAll();                             // +0xdc
};
}
}
namespace EA {
namespace UTFWin {
class IColorDrawable {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual uint32_t GetColor(int index);                 // +0x10
  virtual void SetColor(int index, uint32_t color);     // +0x14
};
}
}
namespace EA {
namespace Messaging {
class IHandler_s005b_fb90 {
 public:
  IHandler_s005b_fb90() {}
  ~IHandler_s005b_fb90() {}
  virtual bool HandleMessage(uint32_t messageID, void* message);
};
}
}
namespace EA {
namespace Messaging {
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMSG(uint32_t messageID, void* data, void* source);       // +0x14
  PV(6) PV(7)
  virtual void AddHandler(IHandler_s005b_fb90* handler, uint32_t messageID);           // +0x20
  PV(9) PV(10)
  virtual void RemoveHandler(IHandler_s005b_fb90* handler, uint32_t messageID, int priority);  // +0x2c
};
}
}
using EA::UTFWin::IWindow_s005b_fb90;
class cSPUILayout_s005b_fb90 {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  cSPUILayout_s005b_fb90();
  IWindow_s005b_fb90* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
  bool Init(const EA::ResourceMan::Key_s005b_fb90& key, bool b, uint32_t id);  // 0x008120d0 (cSPUILayout::Init)
  void SetParentWin(IWindow_s005b_fb90* parent, bool b, uint32_t id);  // 0x008121b0 (cSPUILayout::SetParentWin)
  void Shutdown(bool b);  // 0x00811ad0 (cSPUILayout::Shutdown)
  char pad[0x18 - 4];
};
namespace SP {
EA::Messaging::IMessageServer* MessageServer();
}
namespace SP {
class IWindowManager_s005b_fb90 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  PV(17) PV(18)
  virtual void SetFocusWindow(int a, IWindow_s005b_fb90* window);  // +0x4c
};
}
namespace SP {
IWindowManager_s005b_fb90* WindowManager_s005b_fb90();
}
namespace SP {
void PlayUISound(uint32_t id, uint32_t arg);  // 0x00435ed0
}
namespace SP {
class INameGenerator {
 public:
  eastl::wstring GenerateName(uint32_t nameType);  // FUN_005ecf80
};
}
namespace SP {
INameGenerator* NameGenerator();  // FUN_004010a0
}
namespace SP {
namespace Audio {
class ISystem {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual uint32_t GetSoundContext();  // +0x20
};
}
}
namespace SP {
Audio::ISystem* GetAudioSystem();  // EA::Audio::GetSystemAT (0x00a206f0)
}
namespace SP {
class cISPEditorNameProvider_s005b_fb90 {
 public:
  virtual void SetName(const wchar_t* name);          // +0x0
  virtual const wchar_t* GetName();                   // +0x4
  virtual void SetTag(const wchar_t* tag);            // +0x8
  virtual const wchar_t* GetTag();                    // +0xc
  virtual void SetDescription(const wchar_t* desc);   // +0x10
  virtual const wchar_t* GetDescription();            // +0x14
};
}
namespace SP {
class cSPNameGuard_s005b_fb90 : public EA::UTFWin::IWinProc_s005b_fb90, public EA::RefCountVTemplate_s005b_fb90<int> {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
namespace SP {
struct UIMessage {
  uint32_t pad0;
  IWindow_s005b_fb90* mpSource;   // +0x4
  int mType;           // +0x8
  int mParam1;         // +0xc
  int mParam2;         // +0x10
  int mParam3;         // +0x14
};
}
namespace SP {
class cSPEditorNaming_s005b_fb90 : public EA::UTFWin::IWinProc_s005b_fb90, public EA::Messaging::IHandler_s005b_fb90, public EA::RefCountVTemplate_s005b_fb90<int> {
 public:
  bool mIsExpanded;                              // +0x10
  bool mAllowNameEdit;                           // +0x11
  EA::AutoRefCount_s005b_fb90<cSPNameGuard_s005b_fb90> mNameGuard;     // +0x14
  EA::AutoRefCount_s005b_fb90<cSPUILayout_s005b_fb90> mLayout;         // +0x18
  cISPEditorNameProvider_s005b_fb90* mpDataProvider;        // +0x1c
  unsigned int mNameType;                        // +0x20
  eastl::wstring mNamePrompt;                    // +0x24
  IWindow_s005b_fb90* mOriginalParent;                      // +0x34

  cSPEditorNaming_s005b_fb90();
  ~cSPEditorNaming_s005b_fb90();
  virtual int AddRef();
  virtual int Release();
  virtual void SetExpanded(bool expanded);  // IWinProc slot 7 (+0x1c) 0x005c0380
  bool HandleUIMessage(IWindow_s005b_fb90* window, const void* message);
  bool HandleMessage(uint32_t messageID, void* message);
  void Shutdown();  // 0x005bfb90 (SP::cSPEditorNaming::Shutdown)
  void SetTagField(bool enabled);
  void SetDataProvider(cISPEditorNameProvider_s005b_fb90* provider);  // 0x005bfcc0 (SP::cSPEditorNaming::SetDataProvider)
  void Init(cISPEditorNameProvider_s005b_fb90* provider, IWindow_s005b_fb90* parent, uint32_t layoutID, bool allowNameEdit, unsigned int nameType);  // 0x005bfd40 (SP::cSPEditorNaming::Init)
  void SetPrompt(const wchar_t* prompt);  // 0x005c0320 (SP::cSPEditorNaming::SetPrompt)
  void SetDisplayText(const wchar_t* text);  // 0x005bf950 (SP::cSPEditorNaming::SetDisplayText)
};
}
// ---- items of slice s005bfb90 end

// ---- items of slice s0064dbd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_64aba0(void*, void*);
namespace SP {
struct cSPEditorNaming_s0064_dbd0 {
    char pad0[0x10];
    bool mIsExpanded;          // +0x10
    bool mAllowNameEdit;       // +0x11
    char pad1[0x14 - 0x12];
    void* mNameGuard;          // +0x14
    void* mLayout;             // +0x18
    void* mpDataProvider;      // +0x1c
    uint32_t mNameType;        // +0x20
    char pad2[0x34 - 0x24];
    void* mOriginalParent;     // +0x34
    char pad3[0x224];
    uint32_t f224;             // +0x224
    char pad4[0x234 - 0x228];
    bool f234;                 // +0x234

    bool DoMessage(void* sender, int* msg);  // 0x0064dbd0 (SP::cSPEditorNaming::DoMessage)
};  // namespace SP
}
// ---- items of slice s0064dbd0 end

// @ 0x005bf8c0
bool cResourceFilter::IsValid(const EA::ResourceMan::Key_s005b_eaf0& unused, const EA::ResourceMan::Key_s005b_eaf0* key)
{
  if (key->mGroup == 5 && !IsReservedID(*(unsigned short*)((char*)key + 0x10)))
    return true;
  return false;
}

// @ 0x005bf950
namespace SP {
void cSPEditorNaming_s005b_eaf0::SetDisplayText(const wchar_t* text)
{
  IWindow* window = mHandler.mLayout->FindWindowByID(0xd0e6d04b, true);
  if (window) {
    if (wcslen(text) == 0)
      window->SetCaption(mNamePrompt.mpBegin);
    else
      window->SetCaption(text);
  }
  window = mHandler.mLayout->FindWindowByID(0xc7ceb1bd, true);
  if (window)
    window->SetCaption(text);
}
}  // namespace SP

// @ 0x005bf9d0
namespace SP {
bool cSPEditorNaming_s005b_eaf0::Handler::HandleMessage(uint32_t messageID, void* message)
{
  switch (messageID) {
    case 0x73127e6:
      if (((NameMessage*)message)->mpProvider == mpDataProvider) {
        IWindow* window = mLayout->FindWindowByID(0x5415e48, true);
        if (window)
          window->SetCaption(((NameMessage*)message)->mpText);
        return true;
      }
      break;
    case 0x1ee1001:
      if (mIsExpanded) {
        MouseMessage::Msg* msg = ((MouseMessage*)message)->mpMsg;
        if (msg->mType == 5 && msg->mId == 0x3e8 && msg->mButton == 1 && !IsMouseCaptured()) {
          float px, py;
          ScreenToWindow((float)msg->mX, (float)msg->mY, &px, &py);
          float pt[2];
          pt[0] = px;
          pt[1] = py;
          IWindow* picked = WindowManager()->PickWindow(pt);
          IWindow* root = mLayout->FindWindowByID(0x272eb68e, true);
          IWindow* w = picked;
          if (picked != root) {
            for (;;) {
              if (!w) {
                ((cSPEditorNaming_s005b_eaf0*)((char*)this - 4))->SetExpanded(false);
                break;
              }
              w = w->GetParent();
              if (w == root)
                return true;
            }
          }
          return true;
        }
      }
      break;
    case 0x14418c3f:
      if (((NameMessage*)message)->mpProvider == mpDataProvider) {
        IWindow* window = mLayout->FindWindowByID(0xaddc11ef, true);
        if (window)
          window->SetCaption(((NameMessage*)message)->mpText);
        return true;
      }
      break;
    case 0x7aa519dc:
      if (((NameMessage*)message)->mpProvider == mpDataProvider) {
        ((cSPEditorNaming_s005b_eaf0*)((char*)this - 4))->SetDisplayText(((NameMessage*)message)->mpText);
        return true;
      }
      break;
  }
  return false;
}
}  // namespace SP

// @ 0x005bfb70
namespace SP {
void cSPEditorNaming_s005b_eaf0::ResetParentWin()
{
  mHandler.mLayout->SetParentWin(mOriginalParent, true, 0x5b598fa);
}
}  // namespace SP

// @ 0x005bfb90
namespace SP {
void cSPEditorNaming_s005b_fb90::Shutdown()
{
  IWindow_s005b_fb90* window = mLayout->FindWindowByID(0xc7ceb1bd, true);
  if (window)
    window->RemoveWinProc(mNameGuard);
  if (mNameGuard)
    mNameGuard = 0;
  window = mLayout->FindWindowByID(0x272eb68e, true);
  if (window)
    window->RemoveWinProc(this);
  MessageServer()->RemoveHandler(this, 0x14418c3f, -9999);
  MessageServer()->RemoveHandler(this, 0x7aa519dc, -9999);
  MessageServer()->RemoveHandler(this, 0x1ee1001, -9999);
  if (mLayout->FindWindowByID(0x5415e48, true))
    MessageServer()->AddHandler(this, 0x73127e6);
  if (mLayout) {
    mLayout->Shutdown(true);
    mLayout = 0;
  }
  mpDataProvider = 0;
}
}  // namespace SP

// @ 0x005bfc90
namespace SP {
void cSPEditorNaming_s005b_fb90::SetTagField(bool enabled)
{
  IWindow_s005b_fb90* window = mLayout->FindWindowByID(0x272eb68e, true);
  if (window)
    window->SetFlag(2, enabled);
}
}  // namespace SP

// @ 0x005bfcc0
namespace SP {
void cSPEditorNaming_s005b_fb90::SetDataProvider(cISPEditorNameProvider_s005b_fb90* provider)
{
  mpDataProvider = provider;
  if (provider) {
    SetDisplayText(provider->GetName());
    IWindow_s005b_fb90* window = mLayout->FindWindowByID(0xaddc11ef, true);
    if (window) {
      const wchar_t* tag = mpDataProvider->GetTag();
      window->SetCaption(tag);
    }
    window = mLayout->FindWindowByID(0x5415e48, true);
    if (window) {
      const wchar_t* desc = mpDataProvider->GetDescription();
      window->SetCaption(desc);
    }
  }
}
}  // namespace SP

// @ 0x005bfd40
namespace SP {
void cSPEditorNaming_s005b_fb90::Init(cISPEditorNameProvider_s005b_fb90* provider, IWindow_s005b_fb90* parent, uint32_t layoutID, bool allowNameEdit, unsigned int nameType)
{
  mLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout_s005b_fb90();
  mLayout->Init(EA::ResourceMan::Key_s005b_fb90(layoutID, 0x510a95b, 0x40464100), true, 0x5b598fa);
  mLayout->SetParentWin(parent, true, 0x5b598fa);
  mAllowNameEdit = allowNameEdit;
  mNameType = allowNameEdit ? nameType : 0;
  mIsExpanded = false;
  mOriginalParent = parent;
  SetDataProvider(provider);
  MessageServer()->AddHandler(this, 0x7aa519dc);
  MessageServer()->AddHandler(this, 0x14418c3f);
  MessageServer()->AddHandler(this, 0x1ee1001);
  if (mLayout->FindWindowByID(0x5415e48, true))
    MessageServer()->AddHandler(this, 0x73127e6);
  IWindow_s005b_fb90* window = mLayout->FindWindowByID(0x272eb68e, true);
  if (window) {
    window->SetFlag(1, true);
    window->AddWinProc(this);
  }
  if (!mAllowNameEdit) {
    IWindow_s005b_fb90* src = mLayout->FindWindowByID(0x272eb68e, true);
    IWindow_s005b_fb90* dst = mLayout->FindWindowByID(0x56c1e03, true);
    if (src && dst) {
      IWindow_s005b_fb90* d = src->GetDrawable();
      EA::UTFWin::IColorDrawable* srcColors = d ? (EA::UTFWin::IColorDrawable*)d->Cast(0x103c1908) : 0;
      d = dst->GetDrawable();
      EA::UTFWin::IColorDrawable* dstColors = d ? (EA::UTFWin::IColorDrawable*)d->Cast(0x103c1908) : 0;
      if (srcColors && dstColors) {
        for (int i = 0; i < 8; i++)
          srcColors->SetColor(i, dstColors->GetColor(i));
      }
    }
  }
  IWindow_s005b_fb90* nameWindow = mLayout->FindWindowByID(0xc7ceb1bd, true);
  if (nameWindow) {
    mNameGuard = new ("Editor", 0, 0, 0, 0) cSPNameGuard_s005b_fb90();
    nameWindow->AddWinProc(mNameGuard);
  }
}
}  // namespace SP

// @ 0x005bfff0
namespace SP {
cSPEditorNaming_s005b_fb90::cSPEditorNaming_s005b_fb90()
: mIsExpanded(false), mAllowNameEdit(true), mpDataProvider(0), mNameType(0), mOriginalParent(0) {}
}  // namespace SP

// @ 0x005c0070
namespace SP {
cSPEditorNaming_s005b_fb90::~cSPEditorNaming_s005b_fb90()
{}
}  // namespace SP

// @ 0x005c0100
namespace SP {
bool cSPEditorNaming_s005b_fb90::HandleUIMessage(IWindow_s005b_fb90* window, const void* message)
{
  const UIMessage* msg = (const UIMessage*)message;
  switch (msg->mType) {
    case 0x287259f6:
      if (msg->mParam1 == 2) {
        Audio::ISystem* sys = GetAudioSystem();
        PlayUISound(0xa03e74b2, sys ? sys->GetSoundContext() : 0);
        eastl::wstring name = NameGenerator()->GenerateName(mNameType);
        SetDisplayText(name.c_str());
        return true;
      }
      break;
    case 1:
      if (msg->mParam2 == 0xd || msg->mParam2 == 0x1b) {
        if (!(msg->mParam3 & 0x47) && mIsExpanded) {
          SetExpanded(false);
          WindowManager_s005b_fb90()->SetFocusWindow(0, mOriginalParent);
          return true;
        }
      } else if (msg->mParam2 == 9 && msg->mpSource) {
        uint32_t id = msg->mpSource->GetControlID();
        if (id == 0xc7ceb1bd) {
          IWindow_s005b_fb90* next = mLayout->FindWindowByID(0xaddc11ef, true);
          if (next) {
            WindowManager_s005b_fb90()->SetFocusWindow(0, next);
            return true;
          }
        } else if (id == 0xaddc11ef) {
          IWindow_s005b_fb90* next = mLayout->FindWindowByID(0x5415e48, true);
          if (next) {
            WindowManager_s005b_fb90()->SetFocusWindow(0, next);
            return true;
          }
          next = mLayout->FindWindowByID(0xc7ceb1bd, true);
          if (next) {
            WindowManager_s005b_fb90()->SetFocusWindow(0, next);
            return true;
          }
        } else if (id == 0x5415e48) {
          IWindow_s005b_fb90* next = mLayout->FindWindowByID(0xc7ceb1bd, true);
          if (next) {
            WindowManager_s005b_fb90()->SetFocusWindow(0, next);
            return true;
          }
        }
      }
      break;
    case 0x18:
      if (msg->mParam1 == 1) {
        SetExpanded(msg->mParam3 == 1);
        return true;
      }
      break;
  }
  return false;
}
}  // namespace SP

// @ 0x005c0320
namespace SP {
void cSPEditorNaming_s005b_fb90::SetPrompt(const wchar_t* prompt)
{
  mNamePrompt.assign(prompt, prompt + eastl::CharStrlen(prompt));
  IWindow_s005b_fb90* window = mLayout->FindWindowByID(0xc7ceb1bd, true);
  if (window)
    SetDisplayText(window->GetCaption());
}
}  // namespace SP

// @ 0x005c0380
namespace SP {
void cSPEditorNaming_s005b_fb90::SetExpanded(bool expanded)
{
  if (mIsExpanded != expanded) {
    mIsExpanded = expanded;
    if (expanded) {
      IWindow_s005b_fb90* window = mLayout->FindWindowByID(0x272eb68e, true);
      if (window)
        ((EA::UTFWin::IButtonDrawable*)window->Cast(0x8ed27e7a))->SetImageState(4, true);
      window = mLayout->FindWindowByID(0x453ef531, true);
      if (window)
        ((EA::UTFWin::IButtonDrawable*)window->Cast(0x8ed27e7a))->SetImageState(4, true);
      if (mAllowNameEdit) {
        IWindow_s005b_fb90* nameWindow = mLayout->FindWindowByID(0xc7ceb1bd, true);
        if (nameWindow) {
          nameWindow->SetFlag(1, true);
          EA::UTFWin::ITextEdit* edit = (EA::UTFWin::ITextEdit*)nameWindow->Cast(0xcf428691);
          edit->SetSelection(wcslen(nameWindow->GetCaption()), 0);
          edit->SelectAll();
          WindowManager_s005b_fb90()->SetFocusWindow(0, nameWindow);
        }
        window = mLayout->FindWindowByID(0xd0e6d04b, true);
        if (window)
          window->SetFlag(1, false);
      }
      window = mLayout->FindWindowByID(0xaddc11ef, true);
      if (window)
        window->SetFlag(2, true);
      window = mLayout->FindWindowByID(0x5415e48, true);
      if (window)
        window->SetFlag(2, true);
      window = mLayout->FindWindowByID(0x552c901, true);
      if (window && mNameType) {
        window->SetFlag(1, true);
        window->SetFlag(2, true);
      }
      PlayUISound(0x6871e3b9, 0x46adfee);
      MessageServer()->PostMSG(0x716d445, 0, 0);
    } else {
      IWindow_s005b_fb90* window = mLayout->FindWindowByID(0x272eb68e, true);
      if (window)
        ((EA::UTFWin::IButtonDrawable*)window->Cast(0x8ed27e7a))->SetImageState(4, false);
      window = mLayout->FindWindowByID(0x453ef531, true);
      if (window)
        ((EA::UTFWin::IButtonDrawable*)window->Cast(0x8ed27e7a))->SetImageState(4, false);
      if (mAllowNameEdit) {
        IWindow_s005b_fb90* nameWindow = mLayout->FindWindowByID(0xc7ceb1bd, true);
        if (nameWindow)
          nameWindow->SetFlag(1, false);
        eastl::wstring name(nameWindow->GetCaption());
        name.trim();
        if (name.empty()) {
          SetDisplayText(mpDataProvider->GetName());
        } else {
          SetDisplayText(name.c_str());
          mpDataProvider->SetName(name.c_str());
        }
        window = mLayout->FindWindowByID(0xd0e6d04b, true);
        if (window)
          window->SetFlag(1, true);
      }
      window = mLayout->FindWindowByID(0xaddc11ef, true);
      if (window) {
        mpDataProvider->SetTag(window->GetCaption());
        window->SetFlag(2, false);
      }
      window = mLayout->FindWindowByID(0x5415e48, true);
      if (window) {
        mpDataProvider->SetDescription(window->GetCaption());
        window->SetFlag(2, false);
      }
      window = mLayout->FindWindowByID(0x552c901, true);
      if (window) {
        window->SetFlag(1, false);
        window->SetFlag(2, false);
      }
      PlayUISound(0x6871e3b9, 0x46adfee);
      MessageServer()->PostMSG(0x716d446, 0, 0);
    }
  }
}
}  // namespace SP

// @ 0x0064dbd0
bool SP::cSPEditorNaming_s0064_dbd0::DoMessage(void* sender, int* msg)
{
    (void)sender;
    int kind = msg[2];
    // approximate reconstruction of the large hash-switch handler
    if (kind == 1) {
        int a = msg[4];
        int b = msg[5];
        if (mIsExpanded)
            return true;
        if (a == 0x42) {
            if (b != 0 && mNameGuard)
                return false;
        }
        return true;
    }
    if (kind == 0x17) {
        if (mAllowNameEdit)
            return true;
        if (msg[3] == -0xe) {
            FUN_64aba0((char*)this + 0x14c, 0);
            return true;
        }
        if (msg[3] == 0x447060a) {
            FUN_64aba0((char*)this + 0x14c, 0);
            return true;
        }
        return false;
    }
    return false;
}
