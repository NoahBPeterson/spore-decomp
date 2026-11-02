// src/game/SPGonzago/MemoryMan.cpp -- migrated from slice(s) s00f46560, s009013e0, s00900410, s006ab3d0, s005fe1d0 by tools/migrate/rewrite.py
// Object file: SPGonzago/MemoryMan.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/LimitStopwatch.h"
#include "EA/Variant.h"
#include "EA/Stopwatch.h"
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"
#include "SP/cSPUICredits.h"
#include "cSPUILayout.h"
#include "cSPUILayoutManager.h"
#include "SP/cString.h"
#include <string.h>
#include <intrin.h>
#include "EA/Allocator/FixedAllocatorBase.h"
#include "EA/IO/IStream.h"
#include "EA/IO/MemoryStream.h"
#include "EA/Allocator/StackAllocator.h"
#include "EA/XHTML/Style/Stylesheet.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
#include "EA/XML/XmlTextWriter.h"
#include <stdarg.h>
#include "EA/UTFWinExtras/cXHTMLFrameSet.h"
#include <xmmintrin.h>
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

// ---- items of slice s005fe1d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void _pv##n();
#define PV10(n) PV(n##0) PV(n##1) PV(n##2) PV(n##3) PV(n##4) PV(n##5) PV(n##6) PV(n##7) PV(n##8) PV(n##9)
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);
inline void* operator new(size_t, void* p) throw() { return p; }
namespace EA {
namespace ResourceMan {
class Key_s005f_e1d0 { public:
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
  Key_s005f_e1d0() : instanceID(0), typeID(0), groupID(0) {}
  Key_s005f_e1d0(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};  // namespace ResourceMan
}
}
namespace EA {
template <typename T>
class AutoRefCount_s005f_e1d0 {
 public:
  T* mpObject;
  AutoRefCount_s005f_e1d0() : mpObject(0) {}
  ~AutoRefCount_s005f_e1d0() {
    if (mpObject) mpObject->Release();
  }
  AutoRefCount_s005f_e1d0& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  // @ 0x005fe320 (AutoRefCount<cPropertyList>::Reset, emitted out of line)
  void Reset() {
    if (mpObject) {
      T* const pTemp = mpObject;
      mpObject = 0;
      pTemp->Release();
    }
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005f_e1d0 {
 public:
  RefCountVTemplate_s005f_e1d0() : mnRefCount(0) {}
  virtual ~RefCountVTemplate_s005f_e1d0() {}
  virtual int AddRef();
  virtual int Release();
  T mnRefCount;
};
}
namespace EA {
namespace UTFWin {
class Message_s005f_e1d0 { public:
  class IWindow_s005f_e1d0* source;   // +0x00
  uint32_t pad04;
  uint32_t eventType;      // +0x08
  uint32_t param0C;        // +0x0c (button: control ID)
  uint32_t param10;        // +0x10 (key: virtual key)
  uint32_t param14;        // +0x14 (key: modifiers)
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005f_e1d0;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005f_e1d0 {
 public:
  PV(0) PV(1) PV(2)
  virtual void* Cast(uint32_t typeID);              // +0x0c
  virtual IWindow_s005f_e1d0* GetParent();                     // +0x10
  PV(5) PV(6)
  virtual uint32_t GetControlID();                  // +0x1c
  PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual void* GetArea();                          // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(uint32_t flag, bool value);  // +0x7c
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV10(4)
  PV(50) PV(51) PV(52) PV(53)
  virtual void AddWindow(IWindow_s005f_e1d0* pWindow);         // +0xd8
  PV(55) PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s005f_e1d0* pWinProc);      // +0x104
  virtual void RemoveWinProc(IWinProc_s005f_e1d0* pWinProc);   // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class IButton {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual uint32_t GetButtonStateFlags();                  // +0x20
  PV(9)
  virtual void SetButtonStateFlag(uint32_t flag, bool v);  // +0x28
};
}
}
namespace EA {
namespace UTFWin {
class IWindowManager {
 public:
  PV(0)
  virtual IWindow_s005f_e1d0* GetMainWindow();                // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV10(1) PV10(2)
  PV(30) PV(31)
  virtual bool IsModal(IWindow_s005f_e1d0* pWindow);          // +0x80
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005f_e1d0 {
 public:
  virtual ~IWinProc_s005f_e1d0() {}
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual uint32_t GetEventFlags() const = 0;
  virtual bool HandleUIMessage(IWindow_s005f_e1d0* pWindow, const Message_s005f_e1d0& message) = 0;
};
}
}
using EA::ResourceMan::Key_s005f_e1d0;
using EA::UTFWin::IWindow_s005f_e1d0;
class cSPUILayout_s005f_e1d0 {
 public:
  virtual ~cSPUILayout_s005f_e1d0();
  virtual int AddRef();
  virtual int Release();
  cSPUILayout_s005f_e1d0();                                                    // 0x00810000
  bool Init(const Key_s005f_e1d0& key, bool bVisible, uint32_t parentID);      // 0x008120d0
  void SetReloadCallback(void (*pFn)(void*, uint32_t, bool), void* pData);  // 0x00810090
  void SetParentWin(IWindow_s005f_e1d0* pParent, bool b, uint32_t id);         // 0x008121b0
  IWindow_s005f_e1d0* FindWindowByID(uint32_t id, bool recursive);             // 0x008105b0
  void Shutdown(bool b);                                            // 0x00811ad0
  uint32_t pad[5];
};
class cSPUILayoutManager_s005f_e1d0 {
 public:
  IWindow_s005f_e1d0* GetWorldMainWindow(uint32_t id);  // 0x00810620
};
namespace SPUIHelpers {
cSPUILayoutManager_s005f_e1d0* GetLayoutManager();                                                // 0x00805070
}
namespace SPUIHelpers {
void AnchorWindowToWindow(IWindow_s005f_e1d0* anchor, IWindow_s005f_e1d0* window, uint32_t flags, int a);    // 0x00807340
}
namespace SPUIHelpers {
void BeginModal(IWindow_s005f_e1d0* window, void* callback, int a);                              // 0x008099a0
}
namespace SPUIHelpers {
void EndModal(IWindow_s005f_e1d0* window, uint32_t result, int a);                               // 0x00809c50
}
namespace SPUIHelpers {
void* GetImageFromLayout(cSPUILayout_s005f_e1d0* layout, uint32_t id);                           // 0x008061c0
}
namespace SPUIHelpers {
void SetWindowImage(IWindow_s005f_e1d0* window, void* image, int a);                             // 0x008068d0
}
namespace SP {
EA::UTFWin::IWindowManager* WindowManager();  // 0x0067caa0
}
inline bool IsButtonDown(IWindow_s005f_e1d0* window) {
  if (window) {
    EA::UTFWin::IButton* button = (EA::UTFWin::IButton*)window->Cast(0x8ed27e7a);
    if (button && (button->GetButtonStateFlags() & 4)) return true;
  }
  return false;
}
namespace eastl {
extern wchar_t gEmptyString16[2];
}
namespace eastl {
class allocator_s005f_e1d0 { public:};
}
namespace eastl {
class string16_s005f_e1d0 {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  allocator_s005f_e1d0 mAllocator;
  string16_s005f_e1d0() {
    mpBegin = gEmptyString16;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  ~string16_s005f_e1d0() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin) operator delete[](mpBegin);
  }
  const wchar_t* c_str() const { return mpBegin; }
  string16_s005f_e1d0& operator=(const wchar_t* p);                  // 0x005c3d90
  string16_s005f_e1d0& assign(const wchar_t* pBegin, const wchar_t* pEnd);  // 0x00423650
  string16_s005f_e1d0& assign(const wchar_t* p) { return assign(p, p + CharStrlen(p)); }
  int sprintf(const wchar_t* pFormat, ...);               // 0x0041e050
  static size_t CharStrlen(const wchar_t* p) {
    const wchar_t* pCurrent = p;
    while (*pCurrent) ++pCurrent;
    return (size_t)(pCurrent - p);
  }
};
}
namespace SP {
class cString_s005f_e1d0 {  // localized string
 public:
  cString_s005f_e1d0();                                                // 0x006b5060
  ~cString_s005f_e1d0();                                               // 0x006b5240
  void SetText(uint32_t tableID, uint32_t instanceID, int a);  // 0x006b54b0
  const wchar_t* GetText();                                 // 0x006b55c0
  uint32_t mData[5];
};
}
namespace SP {
struct cStringKey {  // table/instance pair with an inline text buffer
  uint32_t mTableID;
  uint32_t mInstanceID;
  wchar_t mBuffer[256];
  cStringKey() : mTableID(0xffffffff), mInstanceID(0xffffffff) { mBuffer[0] = 0; }
};
}
namespace SP {
void LookupLocalizedString(const cStringKey& key, cString_s005f_e1d0& out);  // 0x006b56d0
}
namespace SP {
struct cLocalizedEntry {  // 12-byte localized string reference
  uint32_t mInstanceID;
  uint32_t mUnknown04;
  uint32_t mTableID;
};
}
namespace SP {
struct Property {
  uint32_t pad00[4];
  uint16_t pad10;
  int16_t mnType;  // +0x12
  uint32_t* GetValueUInt32();  // 0x0041ea00
};
}
namespace SP {
class cPropertyList_s005f_e1d0 {
 public:
  PV(0)
  virtual int Release();  // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Property*& pOut);  // +0x24
  int AddRef();
};
}
namespace SP {
class cSPUICredits_s005f_e1d0 {
 public:
  EA::AutoRefCount_s005f_e1d0<cPropertyList_s005f_e1d0> mCreditNamesProperties;  // +0x00
  int mNumCreditNames;                                     // +0x04
  cLocalizedEntry* mCreditNames;                           // +0x08
  eastl::string16_s005f_e1d0 mReturnString;                           // +0x0c
  uint32_t mScrollSpeed;                                   // +0x1c
  uint32_t mPropertyID;                                    // +0x20
  Key_s005f_e1d0 mBackgroundKey;                                      // +0x24
  Key_s005f_e1d0 mMusicKey;                                           // +0x30
  cString_s005f_e1d0 mTitle;                                          // +0x3c
  uint32_t mLineSpacing;                                   // +0x50
  uint32_t mFadeTime;                                      // +0x54

  cSPUICredits_s005f_e1d0();
  ~cSPUICredits_s005f_e1d0();
  void LoadNamesFromProp();  // 0x005fe340 (SP::cSPUICredits::LoadNamesFromProp)
  void SetPropertyID(uint32_t id);
  uint32_t GetCreditNameTable(uint16_t index);
  const wchar_t* GetCreditName(uint16_t index);
};
}
namespace SP {
extern const wchar_t gCreditSpace[] = L" ";   // 0x13fa1d4
}
class cSPUIChoiceDialog : public EA::UTFWin::IWinProc_s005f_e1d0, public EA::RefCountVTemplate_s005f_e1d0<int> {
 public:
  EA::AutoRefCount_s005f_e1d0<cSPUILayout_s005f_e1d0> mpLayout;  // +0x0c
  bool mbActive;                           // +0x10
  bool mbCancelled;                        // +0x11
  int mFirstChoice;                        // +0x14
  int mSecondChoice;                       // +0x18
  void* mpModalCallback;                   // +0x1c

  cSPUIChoiceDialog(void* pModalCallback);
  virtual int AddRef();
  virtual int Release();
  virtual uint32_t GetEventFlags() const;
  virtual bool HandleUIMessage(IWindow_s005f_e1d0* pWindow, const EA::UTFWin::Message_s005f_e1d0& message);

  void Close();
  void Show();
  bool IsButtonChecked(uint32_t id);
  void Accept();
  void Cancel() {
    mbActive = false;
    mbCancelled = true;
    Close();
  }
  void Init(uint32_t imageID, bool bShowExtra);
  static void OnLayoutReload(void* pData, uint32_t, bool bLoaded);
};
// ---- items of slice s005fe1d0 end

// ---- items of slice s006ab3d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_cacheManager;   // 0x016c8b44
struct CacheManager {
    void Method(void* p, int a, int b, int c, int d, int e);   // 0x009289f0
};
// ---- items of slice s006ab3d0 end

// ---- items of slice s00900410 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int __cdecl strcmp(const char*, const char*);
extern void* g_vtblXmlReader;      // 0x0143a094
extern void* g_vtblXmlTextReader;  // 0x0143a0b0
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n); // 0x011e0744
#pragma intrinsic(strcmp)
typedef unsigned int uint32;
typedef unsigned short uint16;
namespace EA {
namespace Allocator {
class ICoreAllocator_s0090_0410;
}
}
namespace EA {
namespace Allocator {
class StackAllocator_s0090_0410 {
public:
    uint32 mnDefaultBlockSize;       // +0x00
    void*  mpCurrentBlock;           // +0x04
    char*  mpCurrentBlockEnd;        // +0x08
    char*  mpCurrentObjectBegin;     // +0x0c
    char*  mpCurrentObjectEnd;       // +0x10
    void*  mpCoreAllocationFunction; // +0x14
    void*  mpCoreFreeFunction;       // +0x18
    void*  mpCoreFunctionContext;    // +0x1c
    void*  mpTopBookmark;            // +0x20

    StackAllocator_s0090_0410(void* pBlock = 0, uint32 blockSize = 0xffffffff, void* alloc = 0,
                   void* free = 0, void* ctx = 0);                 // 0x00928cd0
    bool AllocateNewBlock(uint32 size);                            // 0x00928ba0
    void Init(void* pBlock, uint32 size, void* alloc, void* free, void* ctx); // 0x00928b00
    void Reset();                                                  // 0x00928dc0
    void* Allocate(uint32 size) {
        if ((int)(mpCurrentBlockEnd - mpCurrentObjectBegin) - (int)size < 0) {
            if (!AllocateNewBlock(size))
                return 0;
        }
        char* p = mpCurrentObjectBegin;
        mpCurrentObjectBegin = p + size;
        mpCurrentObjectEnd = p + size;
        return p;
    }
};
}
}
namespace EA {
namespace Allocator {
ICoreAllocator_s0090_0410* GetDefaultAllocator();   // 0x00925cb0
}
}
struct Token {
    Token* mpNext;       // +0x00
    int    mToken;       // +0x04
    int    field8;       // +0x08
    int    fieldc;       // +0x0c
    int    field10;      // +0x10
    union {
        int* mpEntries;      // +0x14 (element tokens)
        int  mnValueLength;  // +0x14 (text tokens)
    };
    int    mnEntryCount; // +0x18
};
struct MemoryStream_s0090_0410 {
    void** vftable;             // +0x00
    void*  mpSharedPointer;     // +0x04
    int    mnRefCount;          // +0x08
    uint32 mnSize;              // +0x0c
    uint32 mnCapacity;          // +0x10
    uint32 mnPosition;          // +0x14
    bool   mbResizeEnabled;     // +0x18
    float  mfResizeFactor;      // +0x1c
    int    mnResizeIncrement;   // +0x20
    MemoryStream_s0090_0410(int);                                          // 0x0093bd50
    void SetData(const void* p, uint32 size, int a, int b, int c); // 0x0093be30
    void Reset();                                               // 0x0093bde0
    bool Grow(uint32 size);                                     // 0x00928ba0-ish
};
namespace EA {
namespace IO {
enum PositionType_s0090_0410 { kPositionTypeBegin_s0090_0410 = 0 };
}
}
namespace EA {
namespace IO {
class IStream_s0090_0410 {
public:
    virtual ~IStream_s0090_0410();                                  // slot 0
    virtual int  AddRef();                               // slot 1 (+0x04)
    virtual int  Release();                              // slot 2 (+0x08)
    virtual int  GetType() const;                        // slot 3
    virtual int  GetAccessFlags() const;                 // slot 4
    virtual int  GetState() const;                       // slot 5
    virtual bool Close();                                // slot 6 (+0x18)
    virtual uint32 GetSize() const;                      // slot 7 (+0x1c)
    virtual bool SetSize(uint32 size);                   // slot 8
    virtual int  GetPosition(PositionType_s0090_0410 type) const;   // slot 9 (+0x24)
    virtual bool SetPosition(int pos, PositionType_s0090_0410 type);// slot 10 (+0x28)
    virtual uint32 GetAvailable() const;                 // slot 11
    virtual uint32 Read(void* p, uint32 size);           // slot 12 (+0x30)
    virtual bool Flush();                                // slot 13
    virtual bool Write(const void* p, uint32 size);      // slot 14
};
}
}
class XmlReader {
public:
    void** vftable;                 // +0x00
    int    mResultCode;             // +0x04
    int    mAllocatorContextName;   // +0x08
    int    mAllocatorContextAlloc;  // +0x0c
    char   mAllocator[0x24];        // +0x10
    EA::IO::IStream_s0090_0410* mpInputStream; // +0x34
    Token* mpFirstToken;            // +0x38
    Token* mpLastToken;             // +0x3c
    Token* mpCurrentToken;          // +0x40
    void*  mpSourcePath;            // +0x44
    char   mMemoryStream[0x24];     // +0x48

    int  GetTokenType();
    int  GetTokenCount();
    int  GetEntryA(int idx);
    int  GetEntryB(int idx);
    int  IsAtEnd();
    void FUN_00900610(void* a1, void* a2, void* a3);
    int  FUN_00900720(const uint16* s);
    void FUN_009007b0();
    __declspec(noinline) void* ReadString(EA::Allocator::StackAllocator_s0090_0410* pAlloc, uint32* pOut);
    void FUN_009008f0();
    void* FUN_00900970(const void* v);

    XmlReader(void* pAllocator);
    ~XmlReader();
    void* DeletingDtor(char flags);
    char  InitAllocator(EA::IO::IStream_s0090_0410* pStream, const uint16* pPath);
};
class XmlTextReader : public XmlReader {
public:
    void*  mpParser;             // +0x6c
    bool   mbEndOfStream;        // +0x70
    int    mnDepth;              // +0x74
    void*  mpTokenBufferStart;   // +0x78
    void*  mpTokenBufferEnd;     // +0x7c
    uint32 mnTokenBufferBytes;   // +0x80
    uint32 mnFlags;              // +0x84

    int  MapError(int err);
    char Read();

    XmlTextReader(void* pAllocator);
    ~XmlTextReader();
    XmlTextReader* DeletingDtor(char flags);
    char InitParser();
};
void OnStartElement2(XmlTextReader* t, void* a2, void* a3, void* a4);   // 0x00900db0
void OnStartElement(XmlTextReader* t, void* a2, int* a3);               // 0x00900e60
void OnEndElement(XmlTextReader* t, void* a2);                          // 0x00900f70
void OnCharacterData(XmlTextReader* t, void* a2, int a3);               // 0x00900ff0
void OnComment(XmlTextReader* t, void* a2);                             // 0x009010c0
void OnPI(XmlTextReader* t, void* a2, void* a3);                        // 0x00901150
struct MemPool { void LockedRealloc(void* p, uint32 size, int align); };
extern MemPool* g_memPool;
void XML_ParserFree(void* parser);                                       // 0x009055d0
int  XML_Parse(void* parser, const char* buf, int len, int isFinal);     // 0x00905740
int  FUN_00903b40(void* parser);
void* FUN_00900900(short* s, EA::Allocator::StackAllocator_s0090_0410* a); // 0x00900900
extern "C" void g_use_ptr(uint32*);
void __cdecl operator_delete(void* p);         // 0x00f47380
void* __cdecl operator_new(unsigned size, const char* name, int, int, int, int); // 0x00f473a0
inline void* operator new(unsigned size, const char* name, int a, int b, int c, int d)
{
    return operator_new(size, name, a, b, c, d);
}
static Token* AllocToken(XmlTextReader* t, uint32 size)
{
    return (Token*)((EA::Allocator::StackAllocator_s0090_0410*)(t->mAllocator))->Allocate(size);
}
static void AppendTok(XmlTextReader* t, Token* p)
{
    if (t->mpLastToken != 0) {
        t->mpLastToken->mpNext = p;
        t->mpLastToken = p;
    } else {
        t->mpFirstToken = p;
        t->mpLastToken = p;
    }
}
// ---- items of slice s00900410 end

// ---- items of slice s009013e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(wcslen)
struct ReaderRange {
    unsigned int m00;   // +0x00
    unsigned int m04;   // +0x04
    unsigned int m08;   // +0x08
    unsigned int m0c;   // +0x0c
    unsigned int m10;   // +0x10
    void FUN_00928c40(unsigned int v);   // 0x928c40
};
namespace EA {
namespace XML {
class XmlTextReader_s0090_13e0 {
public:
    char          _pad00[0x10];
    ReaderRange   mRange;     // +0x10
    char          _pad24[0x14];
    int           m38;        // +0x38
    int           m3c;        // +0x3c
    int           m40;        // +0x40
    char          _pad44[0x28];
    void*         m6c;        // +0x6c
    char          _pad70[0x0c];
    int           m7c;        // +0x7c

    bool FUN_009013e0();                       // 0x9013e0
    void FUN_00901440(int a, int b);           // 0x901440
    void FUN_00901480(int a, int b, int c);    // 0x901480
    bool FUN_00901df0();                       // 0x901df0
    bool FUN_00901e40();                       // 0x901e40
    char FUN_00901340();                       // 0x901340 Read
    void FUN_00901220();                       // 0x901220 InitParser
    char FUN_00900a30(int a, int b);           // 0x900a30
    char FUN_00900610(int a, int b, int c);    // 0x900610
};
}
}
extern "C" size_t wcslen(const wchar_t*);
// ---- items of slice s009013e0 end

// ---- items of slice s00f46560 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void* __stdcall GetProcessHeap();
extern "C" __declspec(dllimport) void* __stdcall HeapAlloc(void*, unsigned long, unsigned int);
extern char* g_16c8b44;
extern "C" void  FUN_00571db0(void*, void*, void*, void*, void*);  // 0x00571db0  EA::Messaging::RemoveHandler
struct Method { void M(); };
struct Method1 { void FUN_009276c0(void*); };
struct Method6 { void M(int, int, int, int, int, int); };
struct Method8 { void M(int, int, int, int, int, int, int, int); };
void* f_47480();
typedef void  (__thiscall* FnP)(void*);
static inline void* Vslot(void* o, int off) {
    return ((void**)(*(void**)o))[off / 4];
}
__declspec(noinline) void f_47380(int p);   // defined at 0x00F47380 below
struct cXHTMLFrameSet {
    void  FUN_00996cc0(void*);                         // 0x00996cc0  cXHTMLFrameSet::cXHTMLFrameSet
    void  FUN_00996280(int, int, int, int);            // 0x00996280  configure
    void  FUN_00997140();                              // 0x00997140  ClearJobs
    void  FUN_009968a0();                              // 0x009968a0  ~cXHTMLFrameSet
    void* FUN_00996d40(unsigned int);                  // 0x00996d40  GetFrame
    bool  FUN_00997730(void*, const void*, void*, int); // 0x00997730  HandleLocationChange
    bool  FUN_009978b0(void*, void*);                  // 0x009978b0  HandleFormSubmit
    bool  FUN_009979f0(void*, unsigned int);           // 0x009979f0  Attach
};
static cXHTMLFrameSet* FrameAt(void* base, int off) {
    return (cXHTMLFrameSet*)((char*)base + off);
}
struct WString16 {
    unsigned int* mpBegin;      // +0x00
    unsigned int* mpEnd;        // +0x04
    unsigned int* mpCapacity;   // +0x08
};
struct cOnlineTab {
    unsigned char mPad00[0x10];
    unsigned char mFrameSet[0x64];  // +0x10  embedded cXHTMLFrameSet
    void* mpFrame74;                // +0x74
    void* mpFrame78;                // +0x78
    WString16 mUrl;                 // +0x7c
    unsigned int mf88;              // +0x88  (uninitialised here)
    void* mpHandler;                // +0x8c
    void* mHandlerArg0;             // +0x90
    void* mHandlerArg1;             // +0x94
    int   mHandlerArg2;             // +0x98
    int   mHandlerArg3;             // +0x9c

    bool  FUN_00f46920(void* p);                        // Shutdown
    bool  FUN_00f46a40();                               // teardown
    void  FUN_00f46ab0(int a2);                         // set frame
    void* FUN_00f46b50();                               // ctor
    void  FUN_00f46c00();                               // dtor
    void  FUN_00f46cf0(int a1, int a2, int a3, int a4); // url builder
};
extern "C" __declspec(dllimport) int __stdcall HeapFree(void*, unsigned long, void*);
extern char __cdecl cdecl_f935ad0(void*);
extern char* g_16c8b40;
// ---- items of slice s00f46560 end

// @ 0x005fe4b0
namespace SP {
cSPUICredits_s005f_e1d0::~cSPUICredits_s005f_e1d0()
{}
}  // namespace SP

// @ 0x005fe4f0
namespace SP {
void cSPUICredits_s005f_e1d0::SetPropertyID(uint32_t id)
{
  mPropertyID = id;
  LoadNamesFromProp();
}
}  // namespace SP

// @ 0x005fe500
namespace SP {
const wchar_t* cSPUICredits_s005f_e1d0::GetCreditName(uint16_t index)
{
  cString_s005f_e1d0 unused;
  if (mCreditNames) {
    cString_s005f_e1d0 text;
    const uint32_t tableID = mCreditNames[index].mTableID;
    if (tableID == 0)
      mReturnString.assign(gCreditSpace);
    else if (tableID == 1)
      mReturnString = gCreditSpace;
    else if (tableID == 0xabe0cc37 && mCreditNames[index].mInstanceID == 0)
      mReturnString = gCreditSpace;
    else {
      cStringKey key;
      key.mTableID = mCreditNames[index].mTableID;
      key.mInstanceID = mCreditNames[index].mInstanceID;
      LookupLocalizedString(key, text);
      mReturnString = text.GetText();
    }
  }
  return mReturnString.c_str();
}
}  // namespace SP

// @ 0x005fe600
cSPUIChoiceDialog::cSPUIChoiceDialog(void* pModalCallback)
: mbActive(false), mbCancelled(false), mFirstChoice(-1), mSecondChoice(-1), mpModalCallback(pModalCallback) {}

// @ 0x005fe650
void cSPUIChoiceDialog::Close()
{
  if (mpLayout) {
    IWindow_s005f_e1d0* window = mpLayout->FindWindowByID(0x61b2daa, true);
    if (window && SP::WindowManager()->IsModal(window)) {
      window->SetFlag(1, false);
      SPUIHelpers::EndModal(window, 0, 0);
    }
    mpLayout->Shutdown(true);
    mpLayout.Reset();
  }
  mbActive = false;
}

// @ 0x005fe6c0
void cSPUIChoiceDialog::Show()
{
  mbActive = true;
  mbCancelled = false;
  mFirstChoice = -1;
  mSecondChoice = -1;
  if (IWindow_s005f_e1d0* window = mpLayout->FindWindowByID(0x61b5e4e, true)) {
    if (EA::UTFWin::IButton* button = (EA::UTFWin::IButton*)window->Cast(0x8ed27e7a)) button->SetButtonStateFlag(4, true);
  }
  if (IWindow_s005f_e1d0* window = mpLayout->FindWindowByID(0x61f3ce5, true)) {
    if (EA::UTFWin::IButton* button = (EA::UTFWin::IButton*)window->Cast(0x8ed27e7a)) button->SetButtonStateFlag(4, true);
  }
  if (IWindow_s005f_e1d0* window = mpLayout->FindWindowByID(0x61b2daa, true)) SPUIHelpers::BeginModal(window, mpModalCallback, 0);
}

// @ 0x005fe760
bool cSPUIChoiceDialog::IsButtonChecked(uint32_t id)
{ return IsButtonDown(mpLayout->FindWindowByID(id, true)); }

// @ 0x005fe7a0
void cSPUIChoiceDialog::Accept()
{
  mbActive = false;
  mbCancelled = false;
  if (IsButtonDown(mpLayout->FindWindowByID(0x61b5e4d, true)))
    mFirstChoice = 0;
  else if (IsButtonDown(mpLayout->FindWindowByID(0x61b5e4e, true)))
    mFirstChoice = 1;
  else if (IsButtonChecked(0x61b5e4f))
    mFirstChoice = 2;

  if (IsButtonDown(mpLayout->FindWindowByID(0x61f3ce5, true)))
    mSecondChoice = 0;
  else if (IsButtonDown(mpLayout->FindWindowByID(0x61f3ce6, true)))
    mSecondChoice = 2;
  else if (IsButtonChecked(0x61f3ce7))
    mSecondChoice = 1;
  Close();
}

// @ 0x005fe8e0
bool cSPUIChoiceDialog::HandleUIMessage(IWindow_s005f_e1d0* pWindow, const EA::UTFWin::Message_s005f_e1d0& message)
{
  if (mpLayout) {
    switch (message.eventType) {
      case 1:
        if (!(message.param14 & 0x47)) {
          if (message.param10 == 0xd) Accept();
          if (message.param10 == 0x1b) Cancel();
        }
        return true;
      case 0x287259f6:
        if (message.param0C == 0x61c282f) {
          Cancel();
          return true;
        }
        if (message.param0C == 0x61c282e) Accept();
        return true;
      case 2:
      case 5:
        return true;
    }
  }
  return false;
}

// @ 0x005fe970
void cSPUIChoiceDialog::OnLayoutReload(void* pData, uint32_t, bool bLoaded)
{
  cSPUIChoiceDialog* self = (cSPUIChoiceDialog*)pData;
  if (!bLoaded) {
    if (self->mpLayout) {
      if (IWindow_s005f_e1d0* window = self->mpLayout->FindWindowByID(0x61b2daa, true)) window->RemoveWinProc(self);
    }
  } else {
    IWindow_s005f_e1d0* parent = SPUIHelpers::GetLayoutManager()->GetWorldMainWindow(0x5b598f7);
    self->mpLayout->SetParentWin(parent, true, 0x5b598fa);
    if (IWindow_s005f_e1d0* window = self->mpLayout->FindWindowByID(0x61b2daa, true)) {
      window->AddWinProc(self);
      SPUIHelpers::AnchorWindowToWindow(parent, window, 0x300, 0);
    }
  }
}

// @ 0x005fea60
void cSPUIChoiceDialog::Init(uint32_t imageID, bool bShowExtra)
{
  mpLayout = new ("UI", 0, 0, 0, 0) cSPUILayout_s005f_e1d0();
  const Key_s005f_e1d0 key(0x90a57bfa, 0x510a95b, 0x40464100);
  mpLayout->Init(key, true, 0x5b598fa);
  mpLayout->SetReloadCallback(OnLayoutReload, this);
  IWindow_s005f_e1d0* parent = SPUIHelpers::GetLayoutManager()->GetWorldMainWindow(0x5b598f7);
  mpLayout->SetParentWin(parent, true, 0x5b598fa);
  if (IWindow_s005f_e1d0* window = mpLayout->FindWindowByID(0x61b2daa, true)) {
    window->AddWinProc(this);
    SPUIHelpers::AnchorWindowToWindow(parent, window, 0x300, 0);
  }
  if (IWindow_s005f_e1d0* window = mpLayout->FindWindowByID(0x61f3c8b, true)) window->SetFlag(1, bShowExtra);
  if (imageID) {
    if (IWindow_s005f_e1d0* window = mpLayout->FindWindowByID(0x62e9622, true)) {
      void* image = SPUIHelpers::GetImageFromLayout(mpLayout, imageID);
      SPUIHelpers::SetWindowImage(window, image, -1);
    }
  }
}

// @ 0x006abeb0
void FUN_006abeb0(void* p)
{
    ((CacheManager*)g_cacheManager)->Method(p, 0, 0, 0, 0, 0);
}

// @ 0x00900900
void* FUN_00900900(short* s, EA::Allocator::StackAllocator_s0090_0410* a)
{
    short* p = s;
    do { } while (*p++ != 0);
    uint32 n = ((uint32)((p - (s + 1)) * 2) + 9) & ~7u;
    char* dst;
    if ((int)((a->mpCurrentBlockEnd - a->mpCurrentObjectBegin) - n) < 0) {
        if (!a->AllocateNewBlock(n))
            return 0;
    }
    dst = a->mpCurrentObjectBegin;
    a->mpCurrentObjectBegin = dst + n;
    a->mpCurrentObjectEnd = dst + n;
    short* d = (short*)dst;
    while ((*d++ = *s++) != 0) { }
    return dst;
}

// @ 0x00900990
XmlReader::XmlReader(void* pAllocator)
{
    XmlReader* t = this;
    t->vftable = (void**)&g_vtblXmlReader;
    t->mResultCode = 0;
    t->mAllocatorContextName = 0;
    if (pAllocator == 0)
        pAllocator = EA::Allocator::GetDefaultAllocator();
    t->mAllocatorContextAlloc = (int)pAllocator;
    new (t->mAllocator) EA::Allocator::StackAllocator_s0090_0410();
    t->mpInputStream = 0;
    t->mpFirstToken = 0;
    t->mpLastToken = 0;
    t->mpCurrentToken = 0;
    t->mpSourcePath = 0;
    new (t->mMemoryStream) MemoryStream_s0090_0410(0);
}

// @ 0x009009e0
XmlReader::~XmlReader()
{
    XmlReader* t = this;
    t->vftable = (void**)&g_vtblXmlReader;
    ((EA::Allocator::StackAllocator_s0090_0410*)(t->mAllocator))->Reset();
    if (t->mpInputStream != 0) {
        int* p = (int*)t->mpInputStream;
        t->mpInputStream = 0;
        (*(void(__thiscall**)(int*))((char*)*p + 8))(p);
    }
    ((MemoryStream_s0090_0410*)(t->mMemoryStream))->Reset();
    if (t->mpInputStream != 0) {
        int* p = (int*)t->mpInputStream;
        (*(void(__thiscall**)(int*))((char*)*p + 8))(p);
    }
    ((EA::Allocator::StackAllocator_s0090_0410*)(t->mAllocator))->Reset();
}

// @ 0x00900ab0
void* XmlReader::DeletingDtor(char flags)
{
    XmlReader* t = this;
    t->vftable = (void**)&g_vtblXmlReader;
    ((EA::Allocator::StackAllocator_s0090_0410*)t->mAllocator)->Reset();
    EA::IO::IStream_s0090_0410* p = t->mpInputStream;
    if (p != 0) {
        t->mpInputStream = 0;
        p->Release();
    }
    ((MemoryStream_s0090_0410*)t->mMemoryStream)->Reset();
    if (t->mpInputStream != 0)
        t->mpInputStream->Release();
    ((EA::Allocator::StackAllocator_s0090_0410*)t->mAllocator)->Reset();
    if (flags & 1)
        operator_delete(t);
    return t;
}

// @ 0x00900b10
void FUN_00900b10(void* p, uint32 size)
{
    g_memPool->LockedRealloc(p, size, 0);
}

// @ 0x00900b30
XmlTextReader::XmlTextReader(void* pAllocator)
: XmlReader(pAllocator)
{
    XmlTextReader* t = this;
    t->mpParser = 0;
    t->mbEndOfStream = 0;
    t->mnDepth = 0;
    t->mpTokenBufferStart = 0;
    t->mpTokenBufferEnd = 0;
    t->mnTokenBufferBytes = 0;
    t->mnFlags = 0;
    t->vftable = (void**)&g_vtblXmlTextReader;
}

// @ 0x00900b70
XmlTextReader::~XmlTextReader()
{
    XmlTextReader* t = this;
    t->vftable = (void**)&g_vtblXmlTextReader;
    if (t->mpParser != 0)
        XML_ParserFree(t->mpParser);
}

// @ 0x00900ba0
int XmlTextReader::MapError(int err)
{
    (void)this;
    switch (err) {
    case 0: return 0;
    case 1: return 3;   case 2: return 4;   case 3: return 5;
    case 4: return 6;   case 5: return 7;   case 6: return 8;
    case 7: return 9;   case 8: return 10;  case 9: return 0xb;
    case 10: return 0xc; case 0xb: return 0xd; case 0xc: return 0xe;
    case 0xd: return 0xf; case 0xe: return 0x10; case 0xf: return 0x11;
    case 0x10: return 0x12; case 0x11: return 0x13; case 0x12: return 0x14;
    case 0x13: return 0x15; case 0x14: return 0x16; case 0x15: return 0x17;
    case 0x16: return 0x18; case 0x17: return 0x19; case 0x18: return 0x1a;
    case 0x19: return 0x1b; case 0x1a: return 0x1c; case 0x1b: return 0x1d;
    case 0x1c: return 0x1e; case 0x1d: return 0x1f; case 0x1e: return 0x20;
    case 0x1f: return 0x21; case 0x20: return 0x22; case 0x21: return 0x23;
    case 0x22: return 0x24; case 0x23: return 0x25; case 0x24: return 0x26;
    case 0x25: return 0x27;
    default: return 0x28;
    }
}

// @ 0x00900d90
int XmlReader::IsAtEnd()
{
    XmlReader* t = this;
    if (t->mpCurrentToken == 0 && *(char*)((char*)t + 0x70) != 0)
        return 1;
    return 0;
}

// @ 0x00900db0
void OnStartElement2(XmlTextReader* t, void* a2, void* a3, void* a4)
{
    if ((t->mnFlags & 8) == 0)
        return;
    Token* p = AllocToken(t, 0x20);
    if (p != 0)
        p->mToken = 6;
    else
        p = 0;
    p->field8 = (int)t->FUN_00900970(a2);
    p->fieldc = 0;
    p->mpEntries = (int*)t->FUN_00900970(a3);
    p->mnEntryCount = (int)t->FUN_00900970(a4);
    p->mpNext = 0;
    p->field10 = t->mnDepth;
    if (t->mpLastToken != 0) {
        t->mpLastToken->mpNext = p;
        t->mpLastToken = p;
    } else {
        t->mpFirstToken = p;
        t->mpLastToken = p;
    }
}

// @ 0x00900e60
void OnStartElement(XmlTextReader* t, void* a2, int* a3)
{
    Token* p = AllocToken(t, 0x20);
    if (!p)
        return;
    p->mToken = 1;
    int n = 0;
    while (a3[n] != 0)
        n++;
    p->mnEntryCount = n / 2;
    p->field8 = (int)t->FUN_00900970(a2);
    p->fieldc = 0;
    int* arr = (int*)((EA::Allocator::StackAllocator_s0090_0410*)(t->mAllocator))
                   ->Allocate((uint32)(n * 4 + 7) & ~7u);
    p->mpEntries = arr;
    for (int i = 0; i < n; i++)
        arr[i] = (int)t->FUN_00900970((void*)a3[i]);
    p->mpNext = 0;
    p->field10 = t->mnDepth;
    if (t->mpLastToken != 0) {
        t->mpLastToken->mpNext = p;
        t->mnDepth++;
        t->mpLastToken = p;
    } else {
        t->mnDepth++;
        t->mpFirstToken = p;
        t->mpLastToken = p;
    }
}

// @ 0x00900f70
void OnEndElement(XmlTextReader* t, void* a2)
{
    Token* p = AllocToken(t, 0x18);
    if (!p)
        return;
    p->mToken = 2;
    p->field8 = (int)t->FUN_00900970(a2);
    p->fieldc = 0;
    t->mnDepth--;
    p->mpNext = 0;
    p->field10 = t->mnDepth;
    AppendTok(t, p);
}

// @ 0x00900ff0
void OnCharacterData(XmlTextReader* t, void* a2, int a3)
{
    Token* p = AllocToken(t, 0x18);
    if (p != 0)
        p->mToken = 4;
    else
        p = 0;
    p->field8 = 0;
    uint32 size = (uint32)(a3 * 2);
    uint32 n = (size + 9) & ~7u;
    char* dst = (char*)((EA::Allocator::StackAllocator_s0090_0410*)(t->mAllocator))->Allocate(n);
    p->fieldc = (int)dst;
    memcpy(dst, a2, size);
    *(short*)(dst + size) = 0;
    p->mpEntries = (int*)a3;
    p->mpNext = 0;
    p->field10 = t->mnDepth;
    AppendTok(t, p);
}

// @ 0x009010c0
void OnComment(XmlTextReader* t, void* a2)
{
    if ((t->mnFlags & 1) == 0)
        return;
    Token* p = AllocToken(t, 0x18);
    if (!p)
        return;
    p->mToken = 3;
    p->field8 = 0;
    p->fieldc = (int)t->FUN_00900970(a2);
    p->mpNext = 0;
    p->field10 = t->mnDepth;
    AppendTok(t, p);
}

// @ 0x00901150
void OnPI(XmlTextReader* t, void* a2, void* a3)
{
    if ((t->mnFlags & 2) == 0)
        return;
    Token* p = AllocToken(t, 0x18);
    if (!p)
        return;
    p->mToken = 5;
    p->field8 = (int)t->FUN_00900970(a2);
    p->fieldc = (int)t->FUN_00900970(a3);
    p->mpNext = 0;
    p->field10 = t->mnDepth;
    AppendTok(t, p);
}

// @ 0x009011e0
XmlTextReader* XmlTextReader::DeletingDtor(char flags)
{
    XmlTextReader* t = this;
    t->vftable = (void**)&g_vtblXmlTextReader;
    if (t->mpParser != 0)
        XML_ParserFree(t->mpParser);
    ((XmlReader*)t)->~XmlReader();
    if (flags & 1)
        g_use_ptr((uint32*)t);
    return t;
}

// @ 0x00901340
char XmlTextReader::Read()
{
    XmlTextReader* t = this;
    if (t->mbEndOfStream) {
        t->mResultCode = 1;
        return 0;
    }
    while (t->mpFirstToken == 0) {
        uint32 n = t->mpInputStream->Read(t->mpTokenBufferStart, 0x2000);
        t->mnTokenBufferBytes = n;
        if ((int)n < 0)
            goto readfail;
        if (n < 0x2000)
            t->mbEndOfStream = 1;
        if (!XML_Parse(t->mpParser, (const char*)t->mpTokenBufferStart, (int)n, t->mbEndOfStream))
            goto parsefail;
    }
    return 1;
parsefail:
    t->mResultCode = t->MapError(FUN_00903b40(t->mpParser));
    return 0;
readfail:
    t->mResultCode = 2;
    return 0;
}

// @ 0x009013e0
namespace EA { namespace XML {
bool XmlTextReader_s0090_13e0::FUN_009013e0()
{
    if (m40 != 0)
        m40 = *(int*)m40;
    if (m40 == 0) {
        ReaderRange* r = &mRange;
        unsigned int v = (unsigned int)m7c;
        if (v > r->m04 && v < r->m08) {
            r->m0c = v;
            r->m10 = v;
        } else {
            r->FUN_00928c40(v);
        }
        m40 = 0;
        m3c = 0;
        m38 = 0;
        if (!FUN_00901340())
            return false;
        m40 = m38;
    }
    return true;
}
}}  // namespace EA::XML

// @ 0x00f46c00
void cOnlineTab::FUN_00f46c00()
{
    *(void**)((char*)this + 0) = (void*)0x148d5dc;
    *(void**)((char*)this + 4) = (void*)0x148d5d4;
    *(void**)((char*)this + 8) = (void*)0x148d5c4;
    _ReadWriteBarrier();

    if (mpHandler) {
        void* h = mpHandler;
        mpHandler = 0;
        FUN_00571db0(h, mHandlerArg0, mHandlerArg1, (void*)mHandlerArg2, (void*)mHandlerArg3);
    }

    unsigned int* begin = mUrl.mpBegin;
    if (((int)((char*)mUrl.mpCapacity - (char*)begin) & (int)0xfffffffe) > 2 && begin)
        f_47380((int)begin);

    void* p = mpFrame78;
    if (p) (*(FnP)Vslot(p, 4))(p);
    p = mpFrame74;
    if (p) (*(FnP)Vslot(p, 4))(p);

    FrameAt(this, 0x10)->FUN_009968a0();
    *(void**)((char*)this + 8) = (void*)0x13ec458;
    *(void**)((char*)this + 4) = (void*)0x13eb394;
    *(void**)((char*)this + 0) = (void*)0x13eb938;
}

// @ 0x00f47380
__declspec(noinline) void f_47380(int p)
{
    if (p) ((Method1*)g_16c8b44)->FUN_009276c0((void*)p);
}

// @ 0x00f473a0
void f_473a0(int a1, int a2, int a3, int a4, int a5, int a6)
{
    ((Method6*)g_16c8b44)->M(a1, a3, a4, a2, a5, a6);
}

// @ 0x00f473d0
void f_473d0(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    ((Method8*)g_16c8b44)->M(a1, a2, a3, a5, a6, a4, a7, a8);
}

// @ 0x00f47410
void f_47410(int p)
{ ((Method1*)g_16c8b44)->FUN_009276c0((void*)p); }

// @ 0x00f47430
namespace EA {
namespace Allocator {
void ShutdownSharedAllocator()
{
    char* p = g_16c8b40;
    if (p) {
        char ok = cdecl_f935ad0(p);
        p = g_16c8b40;
        if (ok && p) {
            ((Method*)(p + 0x18))->M();
            HeapFree(GetProcessHeap(), 0, p);
        }
        g_16c8b40 = 0;
    }
}
}
}  // namespace EA::Allocator

// @ 0x00f47480
void* f_47480()
{
    char* p = (char*)HeapAlloc(GetProcessHeap(), 0, 0x530);
    if (p) {
        *(int*)(p + 4) = 0;
        *(int*)p = 0;
        *(int*)(p + 0x10) = 0x2b5c;
        *(p + 0x14) = 0;
        ((Method6*)(p + 0x18))->M(0, 0, 1, 0, 0, 0);
    }
    return p;
}
