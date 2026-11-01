// src/game/SPEditors/_at_00600000.cpp -- migrated from slice(s) s0060b730, s0060a720, s00609790, s00605870 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_00600000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/Variant.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorVerbIconTray.h"
#include "SP/cSPVerbTrayCollection.h"
#include "SP/cString.h"
#include "SP/Pollen/CookieHandler.h"
#include "EA/Internet/HTTPResponse.h"
#include "EA/Messaging/IHandler.h"
#include "EA/Messaging/Server.h"
#include "EA/Internet/IRequestResponseFilter.h"
#include "SP/Pollen/cCookie.h"
#include "cSPUILayout.h"
#include "EA/IO/IStream.h"
#include "EA/IO/MemoryStream.h"
#include "evp_cipher_ctx_st.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) unsigned int __stdcall GetDriveTypeA(const char* root);
extern "C" __declspec(dllimport) int __stdcall GetVolumeInformationA(const char* root, char* name, unsigned long nameSize,
                                                                     unsigned long* serial, unsigned long* maxComponent,
                                                                     unsigned long* flags, char* fsName, unsigned long fsNameSize);
extern "C" __declspec(dllimport) int __stdcall GetDiskFreeSpaceExA(const char* dir, uint64_t* freeToCaller, uint64_t* total, uint64_t* totalFree);
extern "C" __declspec(dllimport) unsigned long __stdcall GetLogicalDrives();
extern const wchar_t kSlash[];                                     // 0x13fa030  L"/"

// ---- items of slice s00605870 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);
inline void* operator new(size_t, void* p) { return p; }
struct ResourceKey {
  uint32_t mInstance;  // +0x0
  uint32_t mType;      // +0x4
  uint32_t mGroup;     // +0x8
  ResourceKey() : mInstance(0), mType(0), mGroup(0) {}
  ResourceKey(uint32_t i, uint32_t t, uint32_t g) : mInstance(i), mType(t), mGroup(g) {}
};
namespace EA {
template <typename T>
class AutoRefCount_s0060_5870 {
 public:
  T* mpObject;
  AutoRefCount_s0060_5870() : mpObject(0) {}
  AutoRefCount_s0060_5870(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s0060_5870(const AutoRefCount_s0060_5870& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s0060_5870() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s0060_5870& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  AutoRefCount_s0060_5870& operator=(const AutoRefCount_s0060_5870& x) { return operator=(x.mpObject); }
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
namespace COM {
class IUnknown32_s0060_5870 {
 public:
  ~IUnknown32_s0060_5870() {}
  virtual int AddRef();
  virtual int Release();
  PV(2)
  virtual void* Cast(uint32_t typeID);  // +0xc
};  // namespace COM
}
}
namespace EA {
template <typename T>
class RefCountVTemplate_s0060_5870 {
 public:
  RefCountVTemplate_s0060_5870() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s0060_5870() {}
  T mRefCount;
};
}
namespace EA {
namespace UTFWin {
class IWindow_s0060_5870 {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44)
  PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
  PV(59)
  virtual IWindow_s0060_5870* FindWindowByID(uint32_t controlID, bool recursive);  // +0xf0
};  // namespace UTFWin
}
}
using EA::AutoRefCount_s0060_5870;
using EA::UTFWin::IWindow_s0060_5870;
namespace eastl {
class allocator_s0060_5870 { public:};
}
namespace eastl {
struct sp_vector_allocator_s0060_5870 {
  uint32_t mData[2];
  sp_vector_allocator_s0060_5870() {}
  void deallocate(void* p, size_t) {
    if (((uint32_t*)p)[-1]) operator delete[](p);
  }
};
}
namespace eastl {
struct true_type {};
}
namespace eastl {
struct false_type { false_type() {} };
}
namespace eastl {
template <typename T>
struct copy_result {
  T* mpResult;
  copy_result() {}
};
}
namespace eastl {
template <typename T, typename Tag>
copy_result<T> uninitialized_copy_impl(const T* first, const T* last, T* dest, Tag);  // 0x00829110
}
namespace eastl {
template <typename T>
inline T* uninitialized_copy_ptr(const T* first, const T* last, T* result) {
  const copy_result<T> r = uninitialized_copy_impl(first, last, result, false_type());
  return r.mpResult;
}
}
namespace eastl {
template <typename T>
struct VectorBase_s0060_5870 {
  T* mpBegin;                       // +0x0
  T* mpEnd;                         // +0x4
  T* mpCapacity;                    // +0x8
  sp_vector_allocator_s0060_5870 mAllocator;   // +0xc
  VectorBase_s0060_5870() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  VectorBase_s0060_5870(size_t n, const sp_vector_allocator_s0060_5870& allocator_s0060_5870);  // 0x0066AEC0 (folded)
  ~VectorBase_s0060_5870() {
    if (mpBegin) mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
  }
};
}
namespace eastl {
template <typename T>
class vector_s0060_5870 : public VectorBase_s0060_5870<T> {
 public:
  vector_s0060_5870() {}
  vector_s0060_5870(const vector_s0060_5870& x) : VectorBase_s0060_5870<T>((size_t)(x.mpEnd - x.mpBegin), x.mAllocator) {
    this->mpEnd = uninitialized_copy_ptr(x.mpBegin, x.mpEnd, this->mpBegin);
  }
  ~vector_s0060_5870() { DoDestroyValues(this->mpBegin, this->mpEnd); }
  void DoDestroyValues(T* first, T* last) {
    for (; first < last; ++first) first->~T();
  }
  size_t size() const { return (size_t)(this->mpEnd - this->mpBegin); }
  T& operator[](size_t n) { return this->mpBegin[n]; }
  T* erase(T* first, T* last);                     // 0x00E25BD0 (folded)
  void clear() { erase(this->mpBegin, this->mpEnd); }
  void resize(size_t n);                           // 0x005E77E0
  T* DoInsertValue(T* position, const T& value);   // 0x006650C0
  void push_back(const T& value) {
    if (this->mpEnd < this->mpCapacity)
      ::new (this->mpEnd++) T(value);
    else
      DoInsertValue(this->mpEnd, value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
  }
};
}
namespace eastl {
template <typename T1, typename T2>
struct pair_s0060_5870 {
  T1 first;
  T2 second;
  pair_s0060_5870(const T1& a, const T2& b) : first(a), second(b) {}
  pair_s0060_5870(const pair_s0060_5870& x) : first(x.first), second(x.second) {}
};
}
namespace eastl {
struct rbtree_node_base_s0060_5870 {
  rbtree_node_base_s0060_5870* mpNodeRight;
  rbtree_node_base_s0060_5870* mpNodeLeft;
  rbtree_node_base_s0060_5870* mpNodeParent;
  char mColor;
};
}
namespace eastl {
template <typename T>
struct rbtree_node_s0060_5870 : public rbtree_node_base_s0060_5870 {
  T mValue;  // +0x10
};
}
namespace eastl {
template <typename T>
struct rbtree_iterator_s0060_5870 {
  typedef rbtree_node_s0060_5870<T> node_type;
  node_type* mpNode;
  rbtree_iterator_s0060_5870() : mpNode(0) {}
  explicit rbtree_iterator_s0060_5870(const node_type* pNode) : mpNode((node_type*)pNode) {}
  rbtree_iterator_s0060_5870(const rbtree_iterator_s0060_5870& x) : mpNode(x.mpNode) {}
  T* operator->() const { return &mpNode->mValue; }
  bool operator==(const rbtree_iterator_s0060_5870& x) const { return mpNode == x.mpNode; }
};
}
namespace eastl {
template <typename T>
struct less_s0060_5870 {
  bool operator()(const T& a, const T& b) const { return a < b; }
};
}
namespace eastl {
template <typename Key, typename T>
class map_s0060_5870 {
 public:
  typedef pair_s0060_5870<const Key, T> value_type;
  typedef rbtree_node_s0060_5870<value_type> node_type;
  typedef rbtree_iterator_s0060_5870<value_type> iterator;

  less_s0060_5870<Key> mCompare;         // +0x0
  rbtree_node_base_s0060_5870 mAnchor;   // +0x4
  uint32_t mnSize;            // +0x14
  allocator_s0060_5870 mAllocator;       // +0x18

  map_s0060_5870() : mAnchor(), mnSize(0) { reset(); }
  ~map_s0060_5870() { DoNukeSubtree((node_type*)mAnchor.mpNodeParent); }
  void reset() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  iterator end() { return iterator((node_type*)&mAnchor); }
  iterator DoInsertValue(iterator position, const value_type& value, true_type);  // 0x00605D90
  iterator insert(iterator position, const value_type& value) {
    return DoInsertValue(position, value, true_type());
  }
  iterator lower_bound(const Key& key) {
    node_type* pCurrent = (node_type*)mAnchor.mpNodeParent;
    rbtree_node_base_s0060_5870* pRangeEnd = &mAnchor;
    while (pCurrent) {
      if (!mCompare(pCurrent->mValue.first, key)) {
        pRangeEnd = pCurrent;
        pCurrent = (node_type*)pCurrent->mpNodeLeft;
      } else
        pCurrent = (node_type*)pCurrent->mpNodeRight;
    }
    return iterator((node_type*)pRangeEnd);
  }
  T& operator[](const Key& key);
  void DoFreeNode(node_type* pNode) {
    pNode->~node_type();
    operator delete[](pNode);
  }
  void DoNukeSubtree(node_type* pNode);
};
}
namespace SP {
class cSPVerbTrayCollection_s0060_5870;
}
namespace SP {
class cSPEditorVerbIconTray_s0060_5870 {
 public:
  cSPEditorVerbIconTray_s0060_5870();
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void Init(IWindow_s0060_5870* window, ResourceKey trayKey, int justification, bool animate, int useDefaultImages);  // +0x1c 0x005e7830
  virtual void Shutdown();                                                // +0x20 0x005e76b0
  void SetVerbIconList(void* list);              // 0x5e8470
  void SetValue(void* value);                    // 0x5e61b0
  float GetLevel();                              // 0x5e6390
  void SetLayoutGroup(uint32_t groupID);         // 0x5e5e80
  void SetLayoutKey(ResourceKey key);            // 0x5e5e60
  void SetIconKey(ResourceKey key);              // 0x5e5e40
  void SetShowLevel(bool b);                     // 0x5e5ec0
  void SetResizeStyle(bool b);                   // 0x5e5ea0
  void SetShowIcons(bool b);                     // 0x5e6170
  void SetIgnoreKeyPress(bool b);                // 0x5e5ee0
  char pad[0x11c - 4];
  AutoRefCount_s0060_5870<EA::COM::IUnknown32_s0060_5870> mpCollection;  // +0x11c (retail)
};
}
namespace SP {
class cSPVerbTrayCollection_s0060_5870 : public EA::COM::IUnknown32_s0060_5870, public EA::RefCountVTemplate_s0060_5870<int> {
 public:
  typedef eastl::vector_s0060_5870<AutoRefCount_s0060_5870<cSPEditorVerbIconTray_s0060_5870> > TrayVector;
  typedef eastl::map_s0060_5870<AutoRefCount_s0060_5870<IWindow_s0060_5870>, TrayVector> TrayMap;

  cSPVerbTrayCollection_s0060_5870();
  ~cSPVerbTrayCollection_s0060_5870();
  PV(4) PV(5) PV(6) PV(7)
  virtual IWindow_s0060_5870* GetTrayWindow(uint32_t controlID);                          // +0x20
  virtual void InitTrays(ResourceKey propList, const ResourceKey* trayKeys, int trayCount);  // +0x24 0x00605f90
  virtual void Layout();                                                         // +0x28

  void SetValue(void* value);
  float GetTotalLevel();
  IWindow_s0060_5870* FindWindow(uint32_t controlID);
  void SetVerbIconList(void* list);
  void Init(IWindow_s0060_5870* parent, ResourceKey propList, const ResourceKey* trayKeys, int trayCount, bool ignoreKeyPress);  // 0x00605980 (SP::cSPVerbTrayCollection::Init)
  void ShutdownTrays();

  TrayVector mVerbTrays;                  // +0xc
  AutoRefCount_s0060_5870<IWindow_s0060_5870> mWinParent;       // +0x20
  AutoRefCount_s0060_5870<IWindow_s0060_5870> mWinVerbTray;     // +0x24
  TrayMap mWindowsToVerbTrays;            // +0x28
  int mJustification;                     // +0x44
  bool mAnimateValues;                    // +0x48
  uint32_t mImageGroup;                   // +0x4c
  bool mIgnoreKeyPress;                   // +0x50
};
}
template struct eastl::pair_s0060_5870<const AutoRefCount_s0060_5870<IWindow_s0060_5870>, SP::cSPVerbTrayCollection_s0060_5870::TrayVector>;
template void SP::cSPVerbTrayCollection_s0060_5870::TrayMap::DoNukeSubtree(SP::cSPVerbTrayCollection_s0060_5870::TrayMap::node_type*);
template SP::cSPVerbTrayCollection_s0060_5870::TrayVector& SP::cSPVerbTrayCollection_s0060_5870::TrayMap::operator[](const AutoRefCount_s0060_5870<IWindow_s0060_5870>&);
extern "C" __declspec(dllimport) unsigned int __stdcall GetDriveTypeA(const char* root);
extern "C" __declspec(dllimport) int __stdcall GetVolumeInformationA(const char* root, char* name, unsigned long nameSize,
                                                                     unsigned long* serial, unsigned long* maxComponent,
                                                                     unsigned long* flags, char* fsName, unsigned long fsNameSize);
extern "C" __declspec(dllimport) int __stdcall GetDiskFreeSpaceExA(const char* dir, uint64_t* freeToCaller, uint64_t* total, uint64_t* totalFree);
extern "C" __declspec(dllimport) unsigned long __stdcall GetLogicalDrives();
extern "C" __declspec(dllimport) int __cdecl strncmp(const char* a, const char* b, size_t n);
namespace EA {
namespace ResourceMan {
class IResourceManager {
 public:
  PV(0) PV(1) PV(2)
  virtual bool GetResource(const ResourceKey& key, void* result, int a, int b, int c, int d);  // +0xc
};
}
}
namespace EA {
namespace ResourceMan {
IResourceManager* GetManager();  // 0x8de1a0
}
}
namespace SP {
namespace FunctionalMatch {
struct Constraint_s0060_5870 {
  uint32_t mParameter;  // +0x0
  int mType;            // +0x4
  union {
    struct { int mMin, mMax; } mIntVal;
    struct { float mMin, mMax; } mFloatVal;
  };                    // +0x8
  Constraint_s0060_5870(const Constraint_s0060_5870& x)
      : mParameter(x.mParameter), mType(x.mType), mIntVal(x.mIntVal), mFloatVal(x.mFloatVal) {}
};
}
}
namespace SP {
namespace FunctionalMatch {
struct ConstraintNode {
  Constraint_s0060_5870 mConstraint;                  // +0x0
  eastl::vector_s0060_5870<ConstraintNode> mChildren; // +0x10
  ConstraintNode(const ConstraintNode& x);
  ~ConstraintNode();
};
}
}
using SP::FunctionalMatch::ConstraintNode;
template <> eastl::vector_s0060_5870<ConstraintNode>::vector_s0060_5870(const vector_s0060_5870& x);  // 0x004e38d0
namespace SP {
class cString_s0060_5870 {
 public:
  cString_s0060_5870(uint32_t instanceID, uint32_t groupID, const wchar_t* defaultText);  // 0x6b5770
  ~cString_s0060_5870();                                                                  // 0x6b5240
  const wchar_t* c_str();                                                      // 0x6b55c0
  uint32_t pad[5];
};  // namespace SP
}
struct WStr {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  uint32_t mAllocator;
  WStr& append(const wchar_t* first, const wchar_t* last);                 // 0x429580
  WStr& replace(size_t position, size_t n, const wchar_t* p);              // 0x5f8f80
  size_t size() const { return (size_t)(mpEnd - mpBegin); }
  wchar_t back() const { return mpBegin[size() - 1]; }
  const wchar_t* c_str() const { return mpBegin; }
};
inline size_t wstrlen(const wchar_t* p) {
  const wchar_t* e = p;
  while (*e) e++;
  return (size_t)(e - p);
}
inline WStr& operator+=(WStr& s, const wchar_t* p) { return s.append(p, p + wstrlen(p)); }
extern const wchar_t kSlash[];                                     // 0x13fa030  L"/"
bool GetSpecialFolder(uint32_t folderID, WStr& path, int flags);   // 0x688830
bool CreateFolder(const wchar_t* path);                            // 0x932ae0
// ---- items of slice s00605870 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) int __cdecl strncmp(const char* a, const char* b, size_t n);

// ---- items of slice s00609790 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" void* __cdecl memset(void*, int, unsigned int);
extern "C" char* __cdecl strcpy(char*, const char*);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);
#pragma intrinsic(memset)
#pragma intrinsic(strlen, strcpy)
#pragma intrinsic(_InterlockedExchange)
struct evp_cipher_st;
struct evp_cipher_ctx_st_s0060_9790 {
  uint32_t pad[35];  // size 0x8c
};
extern "C" void EVP_CIPHER_CTX_init(evp_cipher_ctx_st_s0060_9790* ctx);
extern "C" int EVP_CIPHER_CTX_cleanup(evp_cipher_ctx_st_s0060_9790* ctx);
extern "C" const evp_cipher_st* EVP_aes_128_cfb8();  // FUN_01176e10 (exact cipher unverified)
extern "C" int EVP_EncryptInit_ex(evp_cipher_ctx_st_s0060_9790* ctx, const evp_cipher_st* type, void* impl, const unsigned char* key,
const unsigned char* iv);
extern "C" int EVP_EncryptUpdate(evp_cipher_ctx_st_s0060_9790* ctx, unsigned char* out, int* outl, const unsigned char* in, int inl);
extern "C" int EVP_DecryptUpdate(evp_cipher_ctx_st_s0060_9790* ctx, unsigned char* out, int* outl, const unsigned char* in, int inl);
namespace EA {
namespace Thread {
template <typename T>
class AtomicInt_s0060_9790 { public:
  AtomicInt_s0060_9790() { _InterlockedExchange((volatile long*)&mValue, 0); }
  volatile T mValue;
};  // namespace Thread
}
}
namespace EA {
namespace COM {
template <typename T>
class RefCountTemplateA {
 public:
  virtual ~RefCountTemplateA() {}
  T mRefCount;
};
}
}
namespace EA {
namespace IO {
class IStream_s0060_9790 {
 public:
  virtual ~IStream_s0060_9790() {}
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual uint32_t GetType() const = 0;
  virtual int GetAccessFlags() const = 0;
  virtual int GetState() const = 0;
  virtual bool Close() = 0;
  virtual uint32_t GetSize() const = 0;
  virtual bool SetSize(uint32_t size) = 0;
  virtual int GetPosition(int positionType) const = 0;
  virtual bool SetPosition(int position, int positionType) = 0;
  virtual uint32_t GetAvailable() const = 0;
  virtual uint32_t Read(void* pData, uint32_t nSize) = 0;
  virtual bool Flush() = 0;
  virtual bool Write(const void* pData, uint32_t nSize) = 0;
};
}
}
namespace EA {
namespace IO {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount(T* p) : mpObject(p) {
    if (mpObject) mpObject->AddRef();
  }
  ~AutoRefCount() {
    if (mpObject) mpObject->Release();
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
}
namespace SP {
namespace Pollen {
class cEncryptedStream : public EA::IO::IStream_s0060_9790, public EA::COM::RefCountTemplateA<EA::Thread::AtomicInt_s0060_9790<int> > {
 public:
  cEncryptedStream(EA::IO::IStream_s0060_9790* pStream);
  virtual ~cEncryptedStream();
  virtual int AddRef();
  virtual int Release();
  virtual uint32_t GetType() const;
  virtual int GetAccessFlags() const;
  virtual int GetState() const;
  virtual bool Close();
  virtual uint32_t GetSize() const;
  virtual bool SetSize(uint32_t size);
  virtual int GetPosition(int positionType) const;
  virtual bool SetPosition(int position, int positionType);
  virtual uint32_t GetAvailable() const;
  virtual uint32_t Read(void* pData, uint32_t nSize);
  virtual bool Flush();
  virtual bool Write(const void* pData, uint32_t nSize);
  virtual bool Init(const uint8_t* pKey);  // +0x3c

  struct Key {
    uint32_t mData[4];
  };
  evp_cipher_ctx_st_s0060_9790 mContext;                   // +0xc
  EA::IO::AutoRefCount<EA::IO::IStream_s0060_9790> mpStream;  // +0x98
  Key mKey;                                     // +0x9c
  int mState;                                   // +0xac
};
}
}
namespace SP {
namespace Pollen {
extern const uint8_t kKeyMask[16];  // 0x013fb0dc
}
}
namespace EA {
namespace Thread {
class AutoFutex { public:
  void* mpFutex;
  ~AutoFutex();
};
}
}
// ---- items of slice s00609790 end

// ---- items of slice s0060a720 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(strlen)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
namespace UTFWin {
class IWinProc {
 public:
  virtual ~IWinProc() {}
  virtual void pv0() = 0;
  virtual void pv1() = 0;
  virtual void pv2() = 0;
  virtual void pv3() = 0;
};
}
namespace UTFWin {
class IWindow {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual uint32_t GetControlID();  // +0x1c
  PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31)
  virtual void SetCaption(const wchar_t* pText);  // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
  PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55)
  PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63)
  PV(64)
  virtual void AddWinProc(IWinProc* pWinProc);     // +0x104
  virtual void RemoveWinProc(IWinProc* pWinProc);  // +0x108
};
}
class IMessageListener {
 public:
  PV(0) PV(1)
};
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void MessageSend(uint32_t messageID, void* pData, void* pListener);  // +0x14
  PV(6) PV(7) PV(8)
  virtual void AddListener(IMessageListener* pListener, uint32_t messageID);   // +0x24
  PV(10)
  virtual void RemoveListener(IMessageListener* pListener, uint32_t messageID, int priority);  // +0x2c
};
class IRefCounted {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void pv2();
  virtual IRefCounted* Query(uint32_t id);  // +0xc
};
class IObjectTemplateDB {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool IsBusy();  // +0x1c
  virtual void Reset();   // +0x20
};
namespace SP {
IMessageServer* MessageServer();           // 0x0067dcc0
}
namespace SP {
IObjectTemplateDB* ObjectTemplateDB();     // 0x0067cb40
}
namespace SP {
class cString_s0060_a720 {
 public:
  cString_s0060_a720();                                              // 0x006b5060
  ~cString_s0060_a720();                                             // 0x006b5240
  void Load(uint32_t tableID, uint32_t instanceID, int);  // 0x006b54b0
  const wchar_t* GetText();                               // 0x006b55c0
  char pad[0x14];
};
}
struct ResourceKey_s0060_a720 {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};
class cSPUILayout_s0060_a720 {
 public:
  cSPUILayout_s0060_a720();                                                        // 0x00810000
  bool Init(const ResourceKey_s0060_a720* pKey, int, uint32_t);                   // 0x008120d0
  UTFWin::IWindow* FindWindowByID(uint32_t controlID, int bRecursive);  // 0x008105b0
  void Shutdown(int);                                                   // 0x00811ad0
  ~cSPUILayout_s0060_a720();                                                       // 0x00811fe0
  char pad[0x18];
};
namespace SPUIHelpers {
void BeginModal(UTFWin::IWindow* pWindow, void* pWinProc, int);  // 0x008099a0
}
namespace SPUIHelpers {
void EndModal(UTFWin::IWindow* pWindow, uint32_t result, int);          // 0x00809c50
}
namespace SPUIHelpers {
void AutoSizeWindowForText(UTFWin::IWindow* pWindow, int, int);    // 0x00806e40
}
void* AllocUIObject(unsigned size, unsigned align, const char* pName, void* pHeap);  // 0x009512d0
void* GetUIHeap();                                                                   // 0x009512c0
extern IRefCounted* gpMessageHandle;  // 0x015f3f80
namespace UI {
class cDBCheckDialog;
}
namespace UI {
class AsyncResourceBase {  // Resource::Async, +0x4
 public:
  AsyncResourceBase() { mpResource = 0; }
  virtual ~AsyncResourceBase() {}
  virtual void as0();
  virtual void as1();
  virtual void as2();
  uint32_t mpResource;  // +0x8
};
}
namespace UI {
class cDBCheckDialog : public UTFWin::IWinProc, public AsyncResourceBase {
 public:
  __declspec(noinline) cDBCheckDialog();
  __declspec(noinline) bool Init();
  bool Close(void* pCause);
  virtual void pv0();
  virtual void pv1();
  virtual void pv2();
  virtual void pv3();
  bool mbShown;          // +0xc
  char pad0d[3];
  cSPUILayout_s0060_a720 mLayout;   // +0x10
};
}
namespace UI {
class IEditorDialogA {  // +0x0
 public:
  ~IEditorDialogA() {}
  virtual void a0() = 0;
  virtual void a1() = 0;
  virtual void a2() = 0;
  virtual void a3() = 0;
  virtual bool Init() = 0;      // +0x10
  virtual bool Shutdown() = 0;  // +0x14
  virtual void Show() = 0;      // +0x18
};
}
namespace UI {
class __declspec(novtable) IEditorDialogB {  // +0x4
 public:
  virtual void b0() = 0;
  virtual void OnWinProcEvent(UTFWin::IWindow* pWindow, int) = 0;  // +0x4
  virtual void b2() = 0;
};
}
namespace UI {
class IPaintSystemC {  // +0x8
 public:
  ~IPaintSystemC() {}
  virtual void c0() = 0;
  virtual bool HandleMessage(uint32_t messageID, void* pData) = 0;  // +0x4
};
}
namespace UI {
class cContentValidationSummarizer {  // +0xc
 public:
  cContentValidationSummarizer() : mField(0) {}
  ~cContentValidationSummarizer() {}
  virtual void d0();
  virtual void d1();
  virtual void d2();
  virtual void d3();
  uint32_t mField;  // +0x10
};
}
namespace UI {
template <typename T>
struct DialogRef {
  T* mpObject;
  DialogRef() : mpObject(0) {}
  ~DialogRef() {
    if (mpObject) mpObject->Release();
  }
  void Assign(T* p);  // 0x00b5f950 (EA::AutoRefCount<..>::operator=)
  void reset() {
    T* const p = mpObject;
    if (p) {
      mpObject = 0;
      p->Release();
    }
  }
};
}
namespace UI {
class DBCheck : public IEditorDialogA,
                public IEditorDialogB,
                public IPaintSystemC,
                public cContentValidationSummarizer {
 public:
  DBCheck();
  ~DBCheck();
  virtual bool Init();
  virtual bool Shutdown();
  virtual void Show();
  virtual void OnWinProcEvent(UTFWin::IWindow* pWindow, int);
  virtual bool HandleMessage(uint32_t messageID, void* pData);
  DialogRef<IRefCounted> mpDialog;  // +0x14
};
}
namespace UI {
class cInsertDiscDialog {
 public:
  bool Init();
  void Show(void* pWinProc, uint32_t captionInstanceID);
  void* v0;
  void* v4;
  void* v8;
  cSPUILayout_s0060_a720 mLayout;  // +0xc
};
}
namespace UI {
class __declspec(novtable) IPromptA {
 public:
  virtual void a0() = 0;
};
}
namespace UI {
class __declspec(novtable) IPromptB {
 public:
  virtual void b0() = 0;
};
}
namespace UI {
class cPromptCaster : public IPromptA, public IPromptB {
 public:
  // @ 0x0060b670
  void* Cast(uint32_t typeID);
  virtual void a0();
  virtual void b0();
};
}
namespace UI {
class __declspec(novtable) IListenerP0 {
 public:
  virtual void p0() = 0;
};
}
namespace UI {
class IListenerP1 {
 public:
  ~IListenerP1() {}
  virtual void p1() = 0;
};
}
namespace UI {
class IListenerP2 {
 public:
  ~IListenerP2() {}
  virtual void p2() = 0;
};
}
namespace UI {
class cListenerP3 : public IMessageListener {
 public:
  virtual void p3();
};
}
namespace UI {
class cPromptListener : public IListenerP0, public IListenerP1, public IListenerP2, public cListenerP3 {
 public:
  // @ 0x0060b6b0
  bool Register();
  virtual void p0();
  virtual void p1();
  virtual void p2();
};
}
namespace UI {
struct UIMessage {
  UTFWin::IWindow* mpSource;  // +0x0
  uint32_t pad4;
  uint32_t mType;             // +0x8
};
}
namespace UI {
class cPromptHandler {
 public:
  // @ 0x0060b710
  bool HandleUIMessage(UTFWin::IWindow* pWindow, UIMessage* pMessage);
  void* v0;
};
}
// ---- items of slice s0060a720 end

// ---- items of slice s0060b730 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Thread {
template <typename T>
class AtomicInt_s0060_b730 { public:
  AtomicInt_s0060_b730() { _InterlockedExchange((volatile long*)&mValue, 0); }
  volatile T mValue;
};
}
}
class IMessageServer_s0060_b730 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void MessageSend(uint32_t messageID, void* pData, void* pListener);  // +0x14
  virtual void MessagePost(uint32_t messageID, void* pData, int, int);  // +0x18
  PV(7) PV(8)
  virtual void AddListener(IMessageListener* pListener, uint32_t messageID);   // +0x24
  PV(10)
  virtual void RemoveListener(IMessageListener* pListener, uint32_t messageID, int priority);  // +0x2c
};
namespace SP {
IMessageServer_s0060_b730* MessageServer_s0060_b730();           // 0x0067dcc0
}
struct ResourceKey_s0060_b730 {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};
class cSPUILayout_s0060_b730 {
 public:
  cSPUILayout_s0060_b730();                                                        // 0x00810000
  bool Init(const ResourceKey_s0060_b730* pKey, int, uint32_t);                   // 0x008120d0
  UTFWin::IWindow* FindWindowByID(uint32_t controlID, int bRecursive);  // 0x008105b0
  void Shutdown(int);                                                   // 0x00811ad0
  ~cSPUILayout_s0060_b730();                                                       // 0x00811fe0
  char pad[0x18];
};
extern IRefCounted* gpInsertDiscHandle;  // 0x015f4200
int GetDiscState(int);  // 0x00606610
namespace UI {
class cInsertDiscDialog_s0060_b730 : public UTFWin::IWinProc, public AsyncResourceBase {
 public:
  __declspec(noinline) cInsertDiscDialog_s0060_b730();
  virtual void pv0();
  virtual void pv1();
  virtual void pv2();
  virtual void pv3();
  bool Init();                                      // 0x0060b550 (slice s0060a720)
  void Show(void* pWinProc, uint32_t captionInstanceID);  // 0x0060b5e0
  bool HandleUIMessage(void*, void* pMessage);  // vtable slot 6
  cSPUILayout_s0060_b730 mLayout;  // +0xc
};
}
namespace UI {
class IEditorDialogA_s0060_b730 {  // +0x0
 public:
  ~IEditorDialogA_s0060_b730() {}
  virtual void a0() = 0;
  virtual void a1() = 0;
  virtual void a2() = 0;
  virtual void Cast() = 0;
  virtual bool Init() = 0;      // +0x10
  virtual bool Shutdown() = 0;  // +0x14
  virtual void Show() = 0;      // +0x18
};
}
namespace UI {
class cEditorResourceB {  // +0x4
 public:
  cEditorResourceB() {}
  ~cEditorResourceB() {}
  virtual void b0();
  virtual void b1();
  virtual void b2();
};
}
namespace UI {
class __declspec(novtable) IWinProcC {  // +0x8
 public:
  virtual void c0() = 0;
  virtual void OnWinProcEvent(UTFWin::IWindow* pWindow, uint32_t controlID) = 0;  // +0x4
  virtual void c2() = 0;
};
}
namespace UI {
class IPaintSystemD {  // +0xc
 public:
  ~IPaintSystemD() {}
  virtual void d0() = 0;
  virtual bool HandleMessage(uint32_t messageID, void* pData) = 0;  // +0x4
};
}
namespace UI {
class cContentValidationSummarizer_s0060_b730 {  // +0x10
 public:
  cContentValidationSummarizer_s0060_b730() : mField(0) {}
  ~cContentValidationSummarizer_s0060_b730() {}
  virtual void e0();
  virtual void e1();
  virtual void e2();
  virtual void e3();
  uint32_t mField;  // +0x14
};
}
namespace UI {
class IMessageBase {
 public:
  IMessageBase() {
    mpData[0] = 0;
    pad38 = 0;
  }
  virtual void m0();
  virtual void m1();
  EA::Thread::AtomicInt_s0060_b730<int> mRefCount;  // +0x4
  uint32_t mFlags;                       // +0x8
  char pad[0x24];
  uint32_t mpData[2];                    // +0x30, +0x34 (+0x38 follows)
  uint32_t pad38;
  uint32_t pad3c;
};
}
namespace UI {
class SlotMessage : public IMessageBase {
 public:
  SlotMessage() { mFlags = 1; }
  ~SlotMessage();  // 0x00421cf0
  virtual void m0();
  virtual void m1();
};
}
namespace UI {
class InsertDisc : public IEditorDialogA_s0060_b730,
                   public cEditorResourceB,
                   public IWinProcC,
                   public IPaintSystemD,
                   public cContentValidationSummarizer_s0060_b730 {
 public:
  InsertDisc();
  ~InsertDisc();
  virtual void Cast();
  virtual bool Init();
  __declspec(noinline) virtual bool Shutdown();
  virtual void Show();
  virtual void OnWinProcEvent(UTFWin::IWindow* pWindow, uint32_t controlID);
  virtual bool HandleMessage(uint32_t messageID, void* pData);
  virtual void b0();
  virtual void b1();
  virtual void b2();
  virtual void d0();
  virtual void c0();
  virtual void c2();
  virtual void a0();
  virtual void a1();
  virtual void a2();
  virtual void e0();
  virtual void e1();
  virtual void e2();
  virtual void e3();
  DialogRef<IRefCounted> mpDialog;  // +0x18
  bool mbFlag1c;                    // +0x1c
  bool mbFlag1d;                    // +0x1d
};
}
namespace UI {
struct IInsertDiscHandle : public IRefCounted {
  char pad[0x14];
  IRefCounted* mpDialog;  // +0x18
};
}
namespace UI {
extern IInsertDiscHandle* gpInsertDiscOwner;  // 0x015f4200 (same global, owner view)
}
// ---- items of slice s0060b730 end

// @ 0x006064c0
bool IsSporeDisc(const char* root)
{
  char decoded[8];
  uint64_t totalBytes;
  unsigned long flags;
  char volumeName[128];
  if (GetDriveTypeA(root) != 5 /*DRIVE_CDROM*/) return false;
  if (!GetVolumeInformationA(root, volumeName, 0x7f, 0, 0, &flags, 0, 0)) return false;
  char* d = decoded;
  for (const char* s = volumeName; *s; s++) *d++ = *s ^ 0x2a;
  *d = 0;
  if (strncmp(decoded, "yzexo", 6) != 0) return false;  // "SPORE" xor 0x2a
  if (!GetDiskFreeSpaceExA(root, 0, &totalBytes, 0)) return false;
  if (totalBytes < 0x80000000ull) return false;
  return true;
}

// @ 0x00606590
bool FindSporeDisc(char* driveLetter, const char* hint)
{
  if (hint && IsSporeDisc(hint)) {
    *driveLetter = *hint;
    return true;
  }
  unsigned long drives = GetLogicalDrives();
  char root[3] = {'C', ':', 0};
  unsigned int mask = 1;
  for (unsigned int i = 0; i < 26; i++, mask += mask) {
    if (drives & mask) {
      root[0] = (char)('A' + i);
      if (IsSporeDisc(root)) {
        *driveLetter = root[0];
        return true;
      }
    }
  }
  return false;
}

// @ 0x00606610
int CheckSporeDisc(const char* hint)
{
  char drive;
  return FindSporeDisc(&drive, hint) ? 0 : 2;
}

// @ 0x00606640
void* GetResourceAs30bdee3(const ResourceKey& key)
{
  AutoRefCount_s0060_5870<EA::COM::IUnknown32_s0060_5870> resource;
  if (EA::ResourceMan::GetManager()->GetResource(ResourceKey(key.mInstance, 0x30bdee3, key.mGroup),
                                                 &resource.AsOutParam(), 0, 0, 0, 0)) {
    void* result = resource ? resource->Cast(0x30bdee3) : 0;
    return result;
  }
  return 0;
}

// @ 0x00606790
bool GetArchiveFolder(WStr& path)
{
  SP::cString_s0060_5870 archive(0x19f76d11, 0x6244eb0, L"Archive/");
  GetSpecialFolder(0xa0214b, path, 0);
  path += archive.c_str();
  if (path.back() == 0xff0f)
    path.replace(path.size() - 1, 1, kSlash);
  else if (path.back() != L'/')
    path += kSlash;
  if (CreateFolder(path.c_str())) return true;
  return false;
}

// @ 0x00609790
namespace SP { namespace Pollen {
cEncryptedStream::cEncryptedStream(EA::IO::IStream_s0060_9790* pStream)
: mpStream(pStream), mState(-2) {}
}}  // namespace SP::Pollen

// @ 0x006097f0
namespace SP { namespace Pollen {
bool cEncryptedStream::Init(const uint8_t* pKey)
{
  if (mpStream) {
    uint8_t key[16];
    for (int i = 0; i < 16; ++i) key[i] = pKey[i] ^ kKeyMask[i];
    EVP_CIPHER_CTX_init(&mContext);
    if (EVP_EncryptInit_ex(&mContext, EVP_aes_128_cfb8(), 0, key, 0) > 0) {
      mKey = *(const Key*)pKey;
      mState = 0;
      return true;
    }
    mState = -1;
  }
  return false;
}
}}  // namespace SP::Pollen

// @ 0x00609910
namespace SP { namespace Pollen {
int cEncryptedStream::GetAccessFlags() const
{
  if (mpStream && mState == 0) return mpStream->GetAccessFlags();
  return 0;
}
}}  // namespace SP::Pollen

// @ 0x00609930
namespace SP { namespace Pollen {
int cEncryptedStream::GetState() const
{
  if (!mpStream) return -1;
  if (mState) return mState;
  return mpStream->GetState();
}
}}  // namespace SP::Pollen

// @ 0x00609960
namespace SP { namespace Pollen {
bool cEncryptedStream::Close()
{
  if (!mpStream) return false;
  EVP_CIPHER_CTX_cleanup(&mContext);
  memset(&mKey, 0, sizeof(mKey));
  mState = -2;
  return mpStream->Close();
}
}}  // namespace SP::Pollen

// @ 0x006099b0
namespace SP { namespace Pollen {
uint32_t cEncryptedStream::GetSize() const
{
  if (mpStream && mState == 0) return mpStream->GetSize();
  return (uint32_t)-1;
}
}}  // namespace SP::Pollen

// @ 0x006099d0
namespace SP { namespace Pollen {
int cEncryptedStream::GetPosition(int positionType) const
{
  if (mpStream && mState == 0) return mpStream->GetPosition(positionType);
  return -1;
}
}}  // namespace SP::Pollen

// @ 0x00609a00
namespace SP { namespace Pollen {
bool cEncryptedStream::SetPosition(int position, int positionType)
{
  if (mpStream && mState == 0) {
    if (position == 0 && positionType == 0) {
      if (!Init((const uint8_t*)&mKey)) return false;
      if (mpStream->SetPosition(0, 0)) return true;
    }
    mState = -1;
  }
  return false;
}
}}  // namespace SP::Pollen

// @ 0x00609a70
namespace SP { namespace Pollen {
uint32_t cEncryptedStream::GetAvailable() const
{
  if (mpStream && mState == 0) return mpStream->GetAvailable();
  return (uint32_t)-1;
}
}}  // namespace SP::Pollen

// @ 0x00609a90
namespace SP { namespace Pollen {
uint32_t cEncryptedStream::Read(void* pData, uint32_t nSize)
{
  uint8_t* pOut = (uint8_t*)pData;
  if (!pOut) mState = -1;
  if (mpStream && mState == 0) {
    uint32_t nTotal = 0;
    uint32_t nRead;
    do {
      uint8_t buffer[0x400];
      int nOut;
      nRead = mpStream->Read(buffer, sizeof(buffer));
      if (EVP_DecryptUpdate(&mContext, pOut, &nOut, buffer, (int)nRead) <= 0) return (uint32_t)-1;
      pOut += nOut;
      nTotal += nRead;
    } while (nRead > 0 && nRead < nSize);
    return nTotal;
  }
  return (uint32_t)-1;
}
}}  // namespace SP::Pollen

// @ 0x00609b50
namespace SP { namespace Pollen {
bool cEncryptedStream::SetSize(uint32_t size)
{
  if (mpStream && mState == 0) return mpStream->SetSize(size);
  return false;
}
}}  // namespace SP::Pollen

// @ 0x00609b80
namespace SP { namespace Pollen {
bool cEncryptedStream::Flush()
{
  if (mpStream && mState == 0) return mpStream->Flush();
  return false;
}
}}  // namespace SP::Pollen

// @ 0x00609ba0
namespace SP { namespace Pollen {
bool cEncryptedStream::Write(const void* pData, uint32_t nSize)
{
  if (!pData) mState = -1;
  if (mpStream && mState == 0) {
    while (nSize > 0) {
      uint8_t buffer[0x400];
      int nOut;
      const uint32_t nChunk = nSize > sizeof(buffer) ? sizeof(buffer) : nSize;
      if (EVP_EncryptUpdate(&mContext, buffer, &nOut, (const uint8_t*)pData, (int)nChunk) > 0) {
        if (!mpStream->Write(buffer, (uint32_t)nOut)) return false;
        pData = (const uint8_t*)pData + nOut;
        nSize -= nOut;
      }
    }
    return true;
  }
  return false;
}
}}  // namespace SP::Pollen

// @ 0x00609c70
namespace SP { namespace Pollen {
cEncryptedStream::~cEncryptedStream()
{ Close(); }
}}  // namespace SP::Pollen

// @ 0x00609d90
namespace eastl {
template <typename I1, typename I2> inline I1 find(I1 first, I1 last, const I2& value)
{
  while ((first != last) && !(*first == value)) ++first;
  return first;
}
}  // namespace eastl

// @ 0x00609e40
EA::Thread::AutoFutex::~AutoFutex()
{ LeaveCriticalSection(mpFutex); }

// @ 0x0060b050
namespace UI {
bool cDBCheckDialog::Init()
{
  ResourceKey_s0060_a720 key;
  key.instanceID = 0x4b0ac091;
  key.typeID = 0x510a95b;
  key.groupID = 0x40464100;
  if (mLayout.Init(&key, 1, 0x5b598f7)) {
    UTFWin::IWindow* const pWindow = mLayout.FindWindowByID(0x431e538, 1);
    if (pWindow) {
      pWindow->AddWinProc(this);
      return true;
    }
    mLayout.Shutdown(1);
  }
  SP::MessageServer()->MessageSend(0x8085c4c, 0, 0);
  return false;
}
}  // namespace UI

// @ 0x0060b110
namespace UI {
bool DBCheck::Init()
{
  IMessageServer* const pServer = SP::MessageServer();
  if (pServer) pServer->AddListener((IMessageListener*)(IPaintSystemC*)this, 0x238de9c);
  return true;
}
}  // namespace UI

// @ 0x0060b150
namespace UI {
cDBCheckDialog::cDBCheckDialog()
: mbShown(false) {}
}  // namespace UI

// @ 0x0060b180
namespace UI {
bool cDBCheckDialog::Close(void* pCause)
{
  if (mbShown) {
   if (SP::ObjectTemplateDB()) {
    SP::ObjectTemplateDB()->Reset();
    SP::MessageServer()->MessageSend(0x8085c4c, 0, 0);
    UTFWin::IWindow* const pWindow = mLayout.FindWindowByID(0x431e538, 1);
    if (pWindow) {
      SPUIHelpers::EndModal(pWindow, ((UTFWin::IWindow*)pCause)->GetControlID(), 1);
      pWindow->RemoveWinProc(this);
    }
    mLayout.Shutdown(1);
   }
  } else {
    mbShown = true;
  }
  return true;
}
}  // namespace UI

// @ 0x0060b220
namespace UI {
DBCheck::DBCheck()
{}
}  // namespace UI

// @ 0x0060b290
namespace UI {
bool DBCheck::Shutdown()
{
  IMessageServer* const pServer = SP::MessageServer();
  if (pServer) pServer->RemoveListener((IMessageListener*)(IPaintSystemC*)this, 0x238de9c, -9999);
  mpDialog.reset();
  return true;
}
}  // namespace UI

// @ 0x0060b2e0
namespace UI {
void DBCheck::Show()
{
  if (SP::ObjectTemplateDB() && !SP::ObjectTemplateDB()->IsBusy()) {
    if (!mpDialog.mpObject) {
      void* const pMem = AllocUIObject(0x28, 4, "UI/cDBCheckDialog", GetUIHeap());
      mpDialog.Assign(pMem ? (IRefCounted*)new (pMem) cDBCheckDialog() : 0);
      ((cDBCheckDialog*)mpDialog.mpObject)->Init();
    }
    IEditorDialogB* const pWinProc = this;
    cDBCheckDialog* const pDialog = (cDBCheckDialog*)mpDialog.mpObject;
    UTFWin::IWindow* const pWindow = pDialog->mLayout.FindWindowByID(0x431e538, 1);
    if (pWindow) SPUIHelpers::BeginModal(pWindow, pWinProc, 1);
  } else if (SP::MessageServer()) {
    SP::MessageServer()->MessageSend(0x8085c4c, 0, 0);
  }
}
}  // namespace UI

// @ 0x0060b390
namespace UI {
void DBCheck::OnWinProcEvent(UTFWin::IWindow* pWindow, int)
{
  if (pWindow->GetControlID() == 0x431e538) mpDialog.reset();
}
}  // namespace UI

// @ 0x0060b3c0
namespace UI {
IRefCounted* GetMessageHandle()
{
  if (gpMessageHandle) return gpMessageHandle->Query(0x8085c7e);
  return 0;
}
}  // namespace UI

// @ 0x0060b3e0
namespace UI {
void SetMessageHandle(IRefCounted* p)
{
  if (p) p->AddRef();
  if (gpMessageHandle) {
    gpMessageHandle->Release();
    gpMessageHandle = 0;
  }
  if (p) {
    gpMessageHandle = p->Query(0x8085c57);
    return;
  }
  gpMessageHandle = 0;
}
}  // namespace UI

// @ 0x0060b470
namespace UI {
DBCheck::~DBCheck()
{
  IMessageServer* const pServer = SP::MessageServer();
  if (pServer) pServer->RemoveListener((IMessageListener*)(IPaintSystemC*)this, 0x238de9c, -9999);
  mpDialog.reset();
}
}  // namespace UI

// @ 0x0060b4f0
namespace UI {
bool DBCheck::HandleMessage(uint32_t messageID, void* pData)
{
  if (messageID == 0x238de9c) {
    Shutdown();
    if (gpMessageHandle) gpMessageHandle->Release();
    gpMessageHandle = 0;
    return true;
  }
  return false;
}
}  // namespace UI

// @ 0x0060b550
namespace UI {
bool cInsertDiscDialog::Init()
{
  ResourceKey_s0060_a720 key;
  key.instanceID = 0x5b9f6852;
  key.typeID = 0x510a95b;
  key.groupID = 0x40464100;
  if (mLayout.Init(&key, 1, 0x5b598f7)) {
    UTFWin::IWindow* const pText = mLayout.FindWindowByID(0x7f869a8, 1);
    if (pText) SPUIHelpers::AutoSizeWindowForText(pText, 1, 0);
    UTFWin::IWindow* const pFrame = mLayout.FindWindowByID(0x7f86a40, 1);
    if (pFrame) {
      pFrame->AddWinProc((UTFWin::IWinProc*)this);
      return true;
    }
    mLayout.Shutdown(1);
  }
  return false;
}
}  // namespace UI

// @ 0x0060b5e0
namespace UI {
void cInsertDiscDialog::Show(void* pWinProc, uint32_t captionInstanceID)
{
  UTFWin::IWindow* const pFrame = mLayout.FindWindowByID(0x7f86a40, 1);
  if (pFrame) {
    UTFWin::IWindow* const pCaption = mLayout.FindWindowByID(0x7f869f8, 1);
    if (pCaption) {
      SP::cString_s0060_a720 text;
      text.Load(0x91eecf98, captionInstanceID, 0);
      pCaption->SetCaption(text.GetText());
    }
    SPUIHelpers::BeginModal(pFrame, pWinProc, 1);
  }
}
}  // namespace UI

// @ 0x0060b670
namespace UI {
void* cPromptCaster::Cast(uint32_t typeID)
{
  if (typeID == 0xee3f516e) return this;
  if (typeID != 0x2f009dd0) return typeID == 0x35ec342a ? this : 0;
  return static_cast<IPromptB*>(this);
}
}  // namespace UI

// @ 0x0060b6b0
namespace UI {
bool cPromptListener::Register()
{
  IMessageServer* const pServer = SP::MessageServer();
  if (pServer) {
    pServer->AddListener(static_cast<cListenerP3*>(this), 0x49a32cb);
    pServer->AddListener(static_cast<cListenerP3*>(this), 0x238de9c);
  }
  return true;
}
}  // namespace UI

// @ 0x0060b710
namespace UI {
bool cPromptHandler::HandleUIMessage(UTFWin::IWindow* pWindow, UIMessage* pMessage)
{
  if (pMessage->mType == 0x287259f6) pMessage->mpSource->GetControlID();
  return false;
}
}  // namespace UI

// @ 0x0060b730
namespace UI {
cInsertDiscDialog_s0060_b730::cInsertDiscDialog_s0060_b730()
{}
}  // namespace UI

// @ 0x0060b760
namespace UI {
InsertDisc::InsertDisc()
: mbFlag1c(true), mbFlag1d(true) {}
}  // namespace UI

// @ 0x0060b800
namespace UI {
bool InsertDisc::Shutdown()
{
  IMessageServer_s0060_b730* const pServer = SP::MessageServer_s0060_b730();
  if (pServer) {
    pServer->RemoveListener((IMessageListener*)(IPaintSystemD*)this, 0x49a32cb, -9999);
    pServer->RemoveListener((IMessageListener*)(IPaintSystemD*)this, 0x238de9c, -9999);
  }
  mpDialog.reset();
  return true;
}
}  // namespace UI

// @ 0x0060b870
namespace UI {
void InsertDisc::OnWinProcEvent(UTFWin::IWindow* pWindow, uint32_t controlID)
{
  if (pWindow->GetControlID() == 0x7f86a40 && controlID == 0x7f869a8) mpDialog.reset();
}
}  // namespace UI

// @ 0x0060b8b0
namespace UI {
void SetInsertDiscHandle(IRefCounted* p)
{
  if (p) p->AddRef();
  if (gpInsertDiscHandle) {
    gpInsertDiscHandle->Release();
    gpInsertDiscHandle = 0;
  }
  if (p) {
    gpInsertDiscHandle = p->Query(0x35ec342a);
    return;
  }
  gpInsertDiscHandle = 0;
}
}  // namespace UI

// @ 0x0060b910
namespace UI {
bool cInsertDiscDialog_s0060_b730::HandleUIMessage(void*, void* pMessage)
{
  UIMessage* const pMsg = (UIMessage*)pMessage;
  if (pMsg->mType == 0x287259f6) {
    if (pMsg->mpSource->GetControlID() == 0x7f869a8) {
      if (gpInsertDiscHandle) gpInsertDiscHandle->Query(0x7201461);
      IMessageServer_s0060_b730* const pServer = SP::MessageServer_s0060_b730();
      pServer->MessagePost(0x153c326, 0, 0, 0);
      UTFWin::IWindow* const pWindow = mLayout.FindWindowByID(0x7f86a40, 1);
      if (pWindow) {
        SPUIHelpers::EndModal(pWindow, pMsg->mpSource->GetControlID(), 1);
        pWindow->RemoveWinProc(this);
      }
      mLayout.Shutdown(1);
      IInsertDiscHandle* const pOwner = gpInsertDiscOwner;
      IRefCounted* const p = pOwner->mpDialog;
      if (p) {
        pOwner->mpDialog = 0;
        p->Release();
      }
      return true;
    }
  }
  return false;
}
}  // namespace UI

// @ 0x0060b9e0
namespace UI {
InsertDisc::~InsertDisc()
{
  Shutdown();
}
}  // namespace UI

// @ 0x0060ba40
namespace UI {
bool InsertDisc::HandleMessage(uint32_t messageID, void* pData)
{
  if (messageID == 0x49a32cb) {
    Show();
    IMessageServer_s0060_b730* const pServer = SP::MessageServer_s0060_b730();
    if (pServer) pServer->RemoveListener((IMessageListener*)(IPaintSystemD*)this, 0x49a32cb, -9999);
    return true;
  }
  if (messageID == 0x238de9c) {
    Shutdown();
    if (gpInsertDiscHandle) gpInsertDiscHandle->Release();
    gpInsertDiscHandle = 0;
    return true;
  }
  return false;
}
}  // namespace UI

// @ 0x0060bae0
namespace UI {
void InsertDisc::Show()
{
  IMessageServer_s0060_b730* const pServer = SP::MessageServer_s0060_b730();
  SlotMessage msg;
  int nResult = 3;
  const int nState = GetDiscState(0);
  switch (nState) {
  case 0:
    msg.mFlags = 1;
    nResult = 6;
    pServer->MessageSend(0x67c75bd6, &msg, 0);
    if (mpDialog.mpObject) mpDialog.reset();
    break;
  case 1:
    msg.mFlags = 1;
    pServer->MessageSend(0x275a9c8c, &msg, 0);
    if (!mpDialog.mpObject) {
      void* const pMem = AllocUIObject(0x24, 4, "UI/cInsertDiscDialog", GetUIHeap());
      mpDialog.Assign(pMem ? (IRefCounted*)new (pMem) cInsertDiscDialog_s0060_b730() : 0);
      ((cInsertDiscDialog_s0060_b730*)mpDialog.mpObject)->Init();
    }
    ((cInsertDiscDialog_s0060_b730*)mpDialog.mpObject)->Show((IWinProcC*)this, 0xdd0763ff);
    break;
  case 2:
    nResult = 0;
    {
      msg.mFlags = 1;
      pServer->MessageSend(0x634297ad, &msg, 0);
      if (!mpDialog.mpObject) {
        void* const pMem = AllocUIObject(0x24, 4, "UI/cInsertDiscDialog", GetUIHeap());
        mpDialog.Assign(pMem ? (IRefCounted*)new (pMem) cInsertDiscDialog_s0060_b730() : 0);
        ((cInsertDiscDialog_s0060_b730*)mpDialog.mpObject)->Init();
      }
      ((cInsertDiscDialog_s0060_b730*)mpDialog.mpObject)->Show((IWinProcC*)this, 0x49d1ee03);
    }
    break;
  default:
    nResult = 0;
    break;
  }
  msg.mFlags = nResult * 7;
  SP::MessageServer_s0060_b730()->MessageSend(0xeda117de, &msg, 0);
}
}  // namespace UI
