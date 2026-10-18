// src/game/Spui/SPUIPropertyEditor.cpp -- migrated from slice(s) s00b5f040, s00826960, s00825930, s00824c20, s00823e30, s00823a00, s008220e0, s0081fd70, s0081c9c0 by tools/migrate/rewrite.py
// Object file: Spui/SPUIPropertyEditor.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPUIPropertyEditor.h"
#include "EA/Trace/ILogFilter.h"
#include "EA/Audio/ConfigurationAggregate.h"
#include "EA/Variant.h"
#include "SP/cPropertyUI.h"
#include <string.h>
#include "EA/Swarm/cIComponent.h"
#include <stdlib.h>
#include <stddef.h>
#include "cSPUILayout.h"
#include "EA/UTFWin/IWindow.h"
#include "SP/cDirectPropertyList.h"
#include <wchar.h>
#include "EA/Swarm/cIMap.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include <new>
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"
#include <intrin.h>

// ---- items of slice s0081c9c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VTSLOT(p, off) ((*(void***)(p))[(off) / 4])
struct Layout { void Shutdown(int); };
struct Variant {
  int f0; int f4; int f8;
  char pad00[4];
  unsigned short flags;   // +0x10
  unsigned short typeId;  // +0x12
  void Destruct(int);
  void Call5(int, int, int, int, int);
  Variant* Reset(int v);
  Variant* Set20(int v);
};
struct D3 {
  char pad[0x10];
  short w10;   // +0x10
  short w12;   // +0x12
  void Call5(int, int, int, int, int);
  D3* Init(int arg);
  D3* Init2(int arg);
};
// ---- items of slice s0081c9c0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern void* MessageServer();
extern int g_15bbbf3;
extern int g_16af8d8;

// ---- items of slice s0081fd70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyString16[2];  // 0x01667bac
extern int gWindowListNodeOffset;  // 0x01440aec
void* __cdecl EASTL_allocator_allocate(size_t n, const char* name, int flags, int a, const char* file, int line);
#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
struct PtrVec {
  void** mpBegin;
  void** mpEnd;
  void** mpCapacity;
  void DoInsertValue(void** position, void* const& value);
};
void operator delete(void* p);    // 0x00f47380
void operator delete[](void* p);  // 0x00f47380
struct EString16 {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  unsigned mAllocator;
  EString16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
  ~EString16() {
    if ((int)(((unsigned)mpCapacity - (unsigned)mpBegin) & 0xfffffffe) > 2 && mpBegin)
      operator delete[](mpBegin);
  }
  const wchar_t* c_str() const { return mpBegin; }
  void assign(const wchar_t* b, const wchar_t* e);  // 0x00423650
  EString16& operator=(const wchar_t* p) {
    const wchar_t* q = p;
    while (*q) ++q;
    assign(p, p + (q - p));
    return *this;
  }
};
double __cdecl StrtodW(const wchar_t* s, wchar_t** end);  // 0x0092ddc0
struct Vector4 { float x, y, z, w; };
struct ColorRGB { float r, g, b; };
struct ColorRGBA { float r, g, b, a; };
enum { kTypeVector3 = 0x31, kTypeColorRGB = 0x32, kTypeVector4 = 0x33, kTypeColorRGBA = 0x34 };
struct Variant_s0081_fd70 {
  unsigned mData[4];
  unsigned short mFlags;  // +0x10
  unsigned short mType;   // +0x12
  Variant_s0081_fd70() {}
  ~Variant_s0081_fd70() {
    if (mFlags & 4) Destruct(0);
  }
  void Destruct(int);                                                       // 0x0093db80
  bool Set(int type, int flags, const void* p, unsigned size, unsigned n);  // 0x0093dd80
  Variant_s0081_fd70& operator=(const Variant_s0081_fd70& x);                                     // 0x00542b80
  Variant_s0081_fd70& Assign(Vector4* p);                                              // 0x0081dc60
  Variant_s0081_fd70& AssignArrayRGB(ColorRGB* p);                                     // 0x0081db80
  Variant_s0081_fd70& AssignArrayRGBA(ColorRGBA* p);                                   // 0x0081dbf0
  Variant_s0081_fd70& AssignArray(ColorRGB* p) { return AssignArrayRGB(p); }
  Variant_s0081_fd70& AssignArray(ColorRGBA* p) { return AssignArrayRGBA(p); }
};
struct VariantPtr : Variant_s0081_fd70 {  // 0x0081e690
  VariantPtr(Vector4* p) {
    mType = 0;
    mFlags = 0;
    Assign(p);
  }
};
template <int kType> struct VariantConv : Variant_s0081_fd70 {
  VariantConv(const Variant_s0081_fd70& v) {
    mFlags = 2;
    mType = kType;
    Variant_s0081_fd70::operator=(v);
  }
};
template <int kType, class T> struct VariantT16 : Variant_s0081_fd70 {  // 0x0081ddd0 / 0x0081de30
  VariantT16(const T& v) {
    mFlags = 2;
    mType = kType;
    Set(kType, 0, &v, 0x10, 1);
  }
};
struct VariantRGB : Variant_s0081_fd70 {  // ColorRGB stored inline (typed setter 0x006a3610 inlined)
  VariantRGB(const ColorRGB& v) {
    ColorRGB* d = (ColorRGB*)mData;
    *d = v;
    mFlags = 2;
    mType = kTypeColorRGB;
  }
};
template <int kType, class T> struct VariantArr : Variant_s0081_fd70 {
  VariantArr(T* const& p) {
    mFlags = 2;
    mType = kType;
    AssignArray(p);
  }
};
template <class T> struct AutoRefCount {
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  ~AutoRefCount() {
    if (mpObject) mpObject->Release();
  }
  AutoRefCount& operator=(T* p) {
    if (p != mpObject) {
      T* old = mpObject;
      if (p) p->AddRef();
      mpObject = p;
      if (old) old->Release();
    }
    return *this;
  }
  T** AsPPTypeParam() {
    *this = 0;
    return &mpObject;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
struct IWindow;
struct ListNode { ListNode* mpNext; };
struct ChildIterator {
  ListNode* mpNode;
  IWindow* operator*() const { return (IWindow*)((char*)mpNode + gWindowListNodeOffset); }
  ChildIterator& operator++() {
    mpNode = mpNode->mpNext;
    return *this;
  }
  bool operator!=(const ChildIterator& x) const { return mpNode != x.mpNode; }
};
struct IWindow {
  virtual int AddRef();
  virtual int Release();
  virtual void w2();
  virtual void* Cast(unsigned iid) const;  // slot 3
  virtual void w4(); virtual void w5(); virtual void w6();
  virtual unsigned GetControlID() const;  // slot 7
  virtual void w8(); virtual void w9(); virtual void w10(); virtual void w11();
  virtual void w12(); virtual void w13(); virtual void w14(); virtual void w15();
  virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
  virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23();
  virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27();
  virtual void w28(); virtual void w29(); virtual void w30(); virtual void w31();
  virtual void w32(); virtual void w33(); virtual void w34(); virtual void w35();
  virtual void w36(); virtual void w37(); virtual void w38(); virtual void w39();
  virtual void w40(); virtual void w41(); virtual void w42(); virtual void w43();
  virtual void w44(); virtual void w45(); virtual void w46(); virtual void w47();
  virtual void w48(); virtual void w49(); virtual void w50();
  virtual ChildIterator children_begin();  // slot 51
  virtual ChildIterator children_end();    // slot 52
};
struct IWinTextEdit {
  enum { IID = 0xcf428691 };
  virtual int AddRef();
  virtual int Release();
  virtual void t2(); virtual void t3(); virtual void t4(); virtual void t5();
  virtual void t6(); virtual void t7(); virtual void t8(); virtual void t9();
  virtual void t10(); virtual void t11(); virtual void t12(); virtual void t13();
  virtual void t14(); virtual void t15(); virtual void t16(); virtual void t17();
  virtual void t18(); virtual void t19(); virtual void t20();
  virtual const wchar_t* GetText();  // slot 21
};
template <class T> inline T* interface_cast(const AutoRefCount<IWindow>& w) {
  return w.mpObject ? (T*)w.mpObject->Cast(T::IID) : 0;
}
struct PropertyList {
  virtual int AddRef();
  virtual int Release();
  virtual void l2(); virtual void l3(); virtual void l4();
  virtual void SetProperty(unsigned id, const Variant_s0081_fd70& v);  // slot 5
  virtual void l6(); virtual void l7(); virtual void l8(); virtual void l9();
  virtual Variant_s0081_fd70* GetProperty(unsigned id);  // slot 10
};
struct IPropManager {
  virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
  virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
  virtual void m8(); virtual void m9(); virtual void m10();
  virtual bool GetPropertyList(unsigned instanceID, unsigned groupID, PropertyList** out);  // slot 11
};
namespace SP {
 IPropManager* PropertyManager();   // 0x0067de30
}
static inline void* VariantValue(Variant_s0081_fd70* v) {
  if (v->mFlags & 0x30) return *(void**)v->mData;
  return v->mType ? (void*)v : 0;
}
namespace SP {
class cPropertyUI_s0081_fd70 {
 public:
  unsigned mPad0[3];
  unsigned mCurrentGroupID;     // +0xc
  unsigned mCurrentInstanceID;  // +0x10
  void ReloadPropResource();    // 0x0081e230
  void ModifyVec4(IWindow* window, bool bArray);   // 0x0081fd70
  void ModifyRGB(IWindow* window, bool bArray);    // 0x00820210
  void ModifyRGBA(IWindow* window, bool bArray);   // 0x00820680
};  // namespace SP
}
    void operator delete(void*); // 0x00f47380
// ---- items of slice s0081fd70 end

// ---- items of slice s008220e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct EString16_s0082_20e0 {  // eastl::string16, 0x10 bytes
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  unsigned mAllocator;
  EString16_s0082_20e0() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
  ~EString16_s0082_20e0() {
    if ((int)(((unsigned)mpCapacity - (unsigned)mpBegin) & 0xfffffffe) > 2 && mpBegin)
      operator delete[](mpBegin);
  }
  const wchar_t* c_str() const { return mpBegin; }
  EString16_s0082_20e0& operator=(const wchar_t* p);      // 0x005c3d90 (assign(p, p + wcslen(p)))
  EString16_s0082_20e0& operator=(const EString16_s0082_20e0& x);    // 0x0057cb60
};
struct EString8 {  // eastl::string8, 0x10 bytes
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  unsigned mAllocator;
  ~EString8();                                 // 0x00530670
  EString8& operator=(const EString8& x);      // 0x00579c60
};
namespace EA {
EString8 ConvertToString8(const wchar_t* p, int n = -1);  // 0x0093c440
}
namespace EA {
EString8 ConvertToString8(const EString16_s0082_20e0& s);           // 0x0093c570
}
float ParseFloat(const wchar_t* s);  // 0x00671b80 (StrtodW wrapper, end pointer discarded)
struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct ResourceKey {
  unsigned instanceID, typeID, groupID;
  ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
};
ResourceKey* SPKeyFromName(ResourceKey* out, const wchar_t* name, unsigned type, unsigned group);  // 0x0068d840
enum {
  kTypeBool = 1, kTypeInt32 = 9, kTypeUInt32 = 0xa, kTypeFloat = 0xd, kTypeString8 = 0x12,
  kTypeString16 = 0x13, kTypeKey = 0x20, kTypeVector2 = 0x30, kTypeVector3_s0082_20e0 = 0x31,
  kTypeColorRGB_s0082_20e0 = 0x32, kTypeVector4_s0082_20e0 = 0x33, kTypeColorRGBA_s0082_20e0 = 0x34
};
static const unsigned kTypeArray = 0x80000000u;
struct Variant_s0082_20e0 {  // 0x14 bytes
  unsigned mData[4];
  unsigned short mFlags;  // +0x10
  unsigned short mType;   // +0x12
  Variant_s0082_20e0() {}
  ~Variant_s0082_20e0() {
    if (mFlags & 4) Destruct(0);
  }
  void Destruct(int);                                                      // 0x0093db80
  bool Set(int type, int flags, const void* p, unsigned size, unsigned n);  // 0x0093dd80
  Variant_s0082_20e0& operator=(const Variant_s0082_20e0& x);                                    // 0x00542b80
  void* GetValue();                                                        // 0x00446ff0
  // typed setters (out of line in the binary)
  Variant_s0082_20e0& Assign(const bool& v);         // 0x00422e20
  Variant_s0082_20e0& Assign(const ResourceKey& v);  // 0x00422f40
  Variant_s0082_20e0& Assign(const Vector2& v);      // 0x006a3510
  Variant_s0082_20e0& Assign(const Vector3& v);      // 0x006a3570
  Variant_s0082_20e0& Assign(const ColorRGB& v);     // 0x006a3610
  Variant_s0082_20e0& Assign(Vector4* p);            // 0x0081dc60 (by reference, flag 0x20)
  Variant_s0082_20e0& AssignArray(bool* p);          // 0x0081d7a0
  Variant_s0082_20e0& AssignArray(int* p);           // 0x0081d800
  Variant_s0082_20e0& AssignArray(unsigned* p);      // 0x0081d870
  Variant_s0082_20e0& AssignArray(float* p);         // 0x0081d8e0
  Variant_s0082_20e0& AssignArray(EString8* p);      // 0x0081d950
  Variant_s0082_20e0& AssignArray(EString16_s0082_20e0* p);     // 0x0081d9c0
  Variant_s0082_20e0& AssignArray(ResourceKey* p);   // 0x0081da30
  Variant_s0082_20e0& AssignArray(Vector2* p);       // 0x0081daa0
  Variant_s0082_20e0& AssignArray(Vector3* p);       // 0x0081db10
  Variant_s0082_20e0& AssignArray(ColorRGB* p);      // 0x0081db80
  Variant_s0082_20e0& AssignArray(ColorRGBA* p);     // 0x0081dbf0
};
struct VariantString : Variant_s0082_20e0 {
  VariantString(const EString16_s0082_20e0& s) {
    mType = 0;
    mFlags = 0;
    Set(kTypeString16, 9, &s, 0x10, 1);
  }
};
struct VariantPtr_s0082_20e0 : Variant_s0082_20e0 {
  VariantPtr_s0082_20e0(Vector4* p) {
    mType = 0;
    mFlags = 0;
    Assign(p);
  }
};
template <int kType> struct VariantConv_s0082_20e0 : Variant_s0082_20e0 {
  VariantConv_s0082_20e0(const Variant_s0082_20e0& v) {
    mFlags = 2;
    mType = kType;
    Variant_s0082_20e0::operator=(v);
  }
};
template <int kType, class T> struct VariantT : Variant_s0082_20e0 {
  VariantT(const T& v) {
    mFlags = 2;
    mType = kType;
    Assign(v);
  }
};
template <int kType, class T> struct VariantT16_s0082_20e0 : Variant_s0082_20e0 {
  VariantT16_s0082_20e0(const T& v) {
    mFlags = 2;
    mType = kType;
    Set(kType, 0, &v, 0x10, 1);
  }
};
template <int kType, class S> struct VariantStr : Variant_s0082_20e0 {
  VariantStr(const S& s) {
    mFlags = 0xb;
    mType = kType;
    Set(kType, 9, &s, 0x10, 1);
  }
};
template <int kType, class T> struct VariantArr_s0082_20e0 : Variant_s0082_20e0 {
  VariantArr_s0082_20e0(T* const& p) {
    mFlags = 2;
    mType = kType;
    AssignArray(p);
  }
};
struct IWindow_s0082_20e0;
struct ChildIterator_s0082_20e0 {
  ListNode* mpNode;
  ChildIterator_s0082_20e0() {}
  ChildIterator_s0082_20e0(const ChildIterator_s0082_20e0& x) : mpNode(x.mpNode) {}
  IWindow_s0082_20e0* operator*() const { return (IWindow_s0082_20e0*)((char*)mpNode + gWindowListNodeOffset); }
  ChildIterator_s0082_20e0& operator++() {
    mpNode = mpNode->mpNext;
    return *this;
  }
  bool operator!=(const ChildIterator_s0082_20e0& x) const { return mpNode != x.mpNode; }
};
struct IWindow_s0082_20e0 {
  virtual int AddRef();
  virtual int Release();
  virtual void w2();
  virtual void* Cast(unsigned iid) const;  // slot 3
  virtual void w4();
  virtual void w5();
  virtual void w6();
  virtual unsigned GetControlID() const;  // slot 7
  virtual void w8(); virtual void w9(); virtual void w10(); virtual void w11();
  virtual void w12(); virtual void w13(); virtual void w14(); virtual void w15();
  virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
  virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23();
  virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27();
  virtual void w28(); virtual void w29(); virtual void w30(); virtual void w31();
  virtual void w32(); virtual void w33(); virtual void w34(); virtual void w35();
  virtual void w36(); virtual void w37(); virtual void w38(); virtual void w39();
  virtual void w40(); virtual void w41(); virtual void w42(); virtual void w43();
  virtual void w44(); virtual void w45(); virtual void w46(); virtual void w47();
  virtual void w48(); virtual void w49(); virtual void w50();
  virtual ChildIterator_s0082_20e0 children_begin();  // slot 51
  virtual ChildIterator_s0082_20e0 children_end();    // slot 52
};
struct IWinButton {
  enum { IID = 0x8ed27e7a };
  virtual int AddRef();
  virtual int Release();
  virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5();
  virtual void b6(); virtual void b7();
  virtual unsigned GetButtonStateFlags() const;  // slot 8
};
template <class T> inline T* interface_cast_s0082_20e0(const AutoRefCount<IWindow_s0082_20e0>& w) {  // 0x0081d780 / 0x005c2570
  return w.mpObject ? (T*)w.mpObject->Cast(T::IID) : 0;
}
struct PropertyIDList {  // eastl::vector<uint32_t, sp_vector_allocator>
  unsigned* mpBegin;
  unsigned* mpEnd;
  unsigned* mpCapacity;
  unsigned mPad[2];
  PropertyIDList() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~PropertyIDList() {
    if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin);
  }
  bool empty() const { return mpBegin == mpEnd; }
};
struct PropertyList_s0082_20e0 {
  virtual int AddRef();
  virtual int Release();
  virtual void l2(); virtual void l3(); virtual void l4();
  virtual void SetProperty(unsigned id, const Variant_s0082_20e0& v);  // slot 5
  virtual void l6(); virtual void l7(); virtual void l8(); virtual void l9();
  virtual Variant_s0082_20e0* GetProperty(unsigned id);  // slot 10
  virtual void l11(); virtual void l12(); virtual void l13(); virtual void l14();
  virtual void l15(); virtual void l16();
  virtual void GetPropertyIDs(PropertyIDList& out);  // slot 17
};
struct IPropManager_s0082_20e0 {
  virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
  virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
  virtual void m8(); virtual void m9(); virtual void m10();
  virtual bool GetPropertyList(unsigned instanceID, unsigned groupID, PropertyList_s0082_20e0** out);  // slot 11
};
struct IResourceManager {
  virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3();
  virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7();
  virtual bool WriteResource(PropertyList_s0082_20e0* res, int a, int b, int c, int d);  // slot 8
};
namespace SP {
IPropManager_s0082_20e0* PropertyManager_s0082_20e0();  // 0x0067de30
}
IResourceManager* ResourceManager();  // 0x008de1a0
namespace SP {
class cPropertyUI_s0082_20e0 {
 public:
  unsigned mPad0[3];
  unsigned mCurrentGroupID;     // +0xc
  unsigned mCurrentInstanceID;  // +0x10
  unsigned mPad1[0x14];
  AutoRefCount<IWindow_s0082_20e0> mHolderWindow;  // +0x64

  void ReloadPropResource();  // 0x0081e230
  void SavePropFile();        // 0x008220e0
};
}
// ---- items of slice s008220e0 end

// ---- items of slice s00823a00 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IMessageServer;
struct cPropertyUI;
struct cSPUILayout_s0082_3a00 {
  virtual int AddRef();       // slot 0
  virtual int Release();      // slot 4
  int pad8;                   // +0x8
  void SetVisibility(bool b);  // 0x00810590 (cSPUILayout::SetVisibility)
};
struct cPropertyUI {
  virtual int AddRef();       // slot 0
  virtual int Release();      // slot 4
  char pad0[8];               // +0x4 .. +0xb
  int mCurrentGroupID;        // +0xc
  int mCurrentInstanceID;     // +0x10
  char pad1[0x44 - 0x14];     // +0x14 .. +0x43
  cSPUILayout_s0082_3a00 mLayout;        // +0x44
  char padEnd[0x190 - 0x44 - sizeof(cSPUILayout_s0082_3a00)];
  cPropertyUI();
  bool Init(const wchar_t* name, unsigned int flags);
  void PopulateGroupsGrid();
};
template <class T>
struct AutoRefCount_s0082_3a00 {
  T* mpObject;
  T* operator->() const { return mpObject; }
  AutoRefCount_s0082_3a00& operator=(T* p) {
    T* old = mpObject;
    if (p != old) {
      if (p) p->AddRef();
      mpObject = p;
      if (old) old->Release();
    }
    return *this;
  }
};
struct IMessageServer {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
  virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
  virtual void AddMessageHandler(void* handler, int id);  // slot 8 (+0x20)
};
IMessageServer* MessageServer_s0082_3a00();
struct AppPropsInner { char pad[0x54]; int f54; };
struct AppPropsOuter { char pad[0x3c]; AppPropsInner* p3c; };
struct cSPUIPropertyEditor {
  virtual bool HandleMessage(int msg, void* arg);   // slot 0
  char pad0[8];                                     // +0x4 .. +0xb
  AutoRefCount_s0082_3a00<cPropertyUI> mPropUI;                // +0xc
  bool mInitialized;                                // +0x10
  void Init();
};
void* operator new(unsigned int size, const char* name, int, int, int, int);
extern AppPropsOuter* g_sAppProperties;
// ---- items of slice s00823a00 end

// ---- items of slice s00823e30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gEmptyString8[2];       // 0x01667bac (shared empty-string storage)
struct EString8_s0082_3e30 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    unsigned mAllocator;
    EString8_s0082_3e30() : mpBegin(gEmptyString8), mpEnd(gEmptyString8), mpCapacity(gEmptyString8 + 1) {}
    ~EString8_s0082_3e30() {
        if ((int)(mpCapacity - mpBegin) > 1 && mpBegin) operator delete[](mpBegin);
    }
    int sprintf(const char* fmt, ...);   // 0x00472fe0 (cdecl, this pushed first)
    int sprintf(const char* fmt, double v);   // same function, double argument
};
struct EString16_s0082_3e30 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    unsigned mAllocator;
    EString16_s0082_3e30() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    explicit EString16_s0082_3e30(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~EString16_s0082_3e30() {
        if ((int)(((unsigned)mpCapacity - (unsigned)mpBegin) & 0xfffffffe) > 2 && mpBegin) operator delete[](mpBegin);
    }
    const wchar_t* c_str() const { return mpBegin; }
    void RangeInitialize(const wchar_t* p);   // 0x00579a90
};
EString16_s0082_3e30 __cdecl ConvertToString16(const EString8_s0082_3e30& s);   // 0x0093c6d0
float __cdecl ParseFloatW(const wchar_t* s);              // 0x00671b80
struct IWindow_s0082_3e30 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual IWindow_s0082_3e30* GetParent();            // +0x10
    virtual void v5(); virtual void v6();
    virtual unsigned GetControlID();         // +0x1c
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20();
    virtual const wchar_t* GetText();        // +0x54
    virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
    virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void SetText(const wchar_t* text);   // +0x80
};
struct Variant_s0082_3e30 {
    char pad[0x12];
    unsigned short mType;   // +0x12
};
struct PropertyList_s0082_3e30 {
    virtual void v0();
    virtual int Release();   // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8(); virtual void v9();
    virtual Variant_s0082_3e30* GetProperty(unsigned id);   // +0x28
};
struct IPropManager_s0082_3e30 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual void GetPropertyList(unsigned instanceID, unsigned groupID, PropertyList_s0082_3e30** out);   // +0x2c
};
namespace SP {
 IPropManager_s0082_3e30* PropertyManager_s0082_3e30();   // 0x0067de30
}
struct HashNode { unsigned first; IWindow_s0082_3e30* second; HashNode* next; };
struct HashIter { HashNode* mpNode; HashNode** mpBucket; };
struct HashMapU32 {
    unsigned pad0;
    HashNode** mpBucketArray;   // +4
    unsigned mnBucketCount;     // +8
    char pad1[0x20 - 0xc];
    HashIter find(const unsigned& key);   // 0x00645ed0
};
namespace SP {
class cPropertyUI_s0082_3e30 {
public:
    char pad0[0xc];
    unsigned mCurrentGroupID;       // +0xc
    unsigned mCurrentInstanceID;    // +0x10
    char pad1[0x38 - 0x14];
    float mFloatIncrement;          // +0x38
    unsigned mIntIncrement;         // +0x3c
    char pad2[0x64 - 0x40];
    IWindow_s0082_3e30* mRootWindow;           // +0x64
    char pad3[0x150 - 0x68];
    HashMapU32 mSpinnerMap;         // +0x150
    void ModifyInt32(IWindow_s0082_3e30* w, bool bArray);    // 0x00820ec0
    void ModifyUInt32(IWindow_s0082_3e30* w, bool bArray);   // 0x00821260
    void ModifyFloat(IWindow_s0082_3e30* w, bool bArray);    // 0x00821600
    void ModifyVec2(IWindow_s0082_3e30* w, bool bArray);     // 0x0081f490
    void ModifyVec3(IWindow_s0082_3e30* w, bool bArray);     // 0x0081f900
    void ModifyVec4(IWindow_s0082_3e30* w, bool bArray);     // 0x0081fd70
    void ModifyRGB(IWindow_s0082_3e30* w, bool bArray);      // 0x00820210
    void ModifyRGBA(IWindow_s0082_3e30* w, bool bArray);     // 0x00820680
    void ProcessSpinnerButtons(unsigned buttonID);   // 0x00823e30
};
}
template <class T>
struct AutoRefCountT {
    T* mpObject;
    AutoRefCountT() : mpObject(0) {}
    ~AutoRefCountT() { if (mpObject) mpObject->Release(); }
    T** AsPPTypeParam() {
        T* old = mpObject;
        if (old) { mpObject = 0; old->Release(); }
        return &mpObject;
    }
    T* operator->() const { return mpObject; }
};
// ---- items of slice s00823e30 end

// ---- items of slice s00824c20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* GetAllocator();                                                      // 0x009512c0
extern void* AllocAligned(unsigned size, int align, const char* name, void* a);   // 0x009512d0
extern const char kTextEditName[];                                                // "UI/UI/WinTextEdit"
extern const char kStyleStr[];                                                    // 0x015a4361
extern const char kBtnTextA[];                                                    // 0x01419de8
extern const char kBtnTextB[];                                                    // 0x013faf54
extern const char kIntFmt[];                                                      // 0x013fc740 "%d"
extern const float kQuarter;                                                      // 0x013eb8a0
extern const float kRect2W;                                                       // 0x013eecd8
extern const float kRect2H;                                                       // 0x01419d38
extern const float kRect1W;                                                       // 0x01419d40 (60)
extern const float kSpin80;                                                       // 0x014763c4
extern const float kBtn2Y;                                                        // 0x0140c7a4
extern const float kAdv30;                                                        // 0x014853bc
extern char kEmptyStr[2];                                                         // 0x01667bac
struct IWinW {
  virtual void AddRef();
  virtual void Release();
  virtual void s2();
  virtual void s3();
  virtual void s4();
  virtual void s5();
  virtual void s6();
  virtual unsigned GetID();  // slot 7
  virtual void s8();
  virtual void s9();
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
  virtual void SetA(unsigned a);  // slot 20
  virtual void SetB(unsigned b);  // slot 21
  virtual void s22();
  virtual void s23();
  virtual void SetArea(const float* r);  // slot 24
  virtual void SetPos(float x, float y);  // slot 25
  virtual void s26();
  virtual void s27();
  virtual void s28();
  virtual void s29();
  virtual void s30();
  virtual void s31();
  virtual void SetText(const void* t);  // slot 32
  virtual void SetHash(unsigned h);  // slot 33
  virtual void s34();
  virtual void s35();
  virtual void V36();  // slot 36
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
  virtual void s49();
  virtual void s50();
  virtual void s51();
  virtual void s52();
  virtual void s53();
  virtual void AddChild(IWinW* w);  // slot 54
};
struct ITE {
  virtual void AddRef();  // slot 0
  virtual void Release();  // slot 1
  virtual void s2();
  virtual void s3();
  virtual IWinW* GetWin();  // slot 4
  virtual void s5();
  virtual void V6(const void* s);  // slot 6
  virtual void s7();
  virtual void SetColor(int i, unsigned c);  // slot 8
  virtual void s9();
  virtual void s10();
  virtual void s11();
  virtual void V12(float f);  // slot 12
  virtual void s13();
  virtual void s14();
  virtual void s15();
  virtual void V16(int a);  // slot 16
  virtual void V17(int a, int b);  // slot 17
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
  virtual void V37(int a, int b);  // slot 37
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
  virtual void V48(int a);  // slot 48
};
struct IBtn {
  virtual void AddRef();  // slot 0
  virtual void Release();  // slot 1
  virtual void s2();
  virtual void s3();
  virtual IWinW* GetWin();  // slot 4
};
struct IGrid {
  virtual void AddRef();  // slot 0
  virtual void Release();  // slot 1
  virtual void s2();
  virtual void s3();
  virtual void s4();
  virtual void s5();
  virtual void s6();
  virtual void s7();
  virtual void s8();
  virtual void s9();
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
  virtual void s49();
  virtual void s50();
  virtual void s51();
  virtual void s52();
  virtual void s53();
  virtual void s54();
  virtual void s55();
  virtual void s56();
  virtual void s57();
  virtual void s58();
  virtual void s59();
  virtual void s60();
  virtual void s61();
  virtual void s62();
  virtual void s63();
  virtual void s64();
  virtual void s65();
  virtual void s66();
  virtual void s67();
  virtual void s68();
  virtual void s69();
  virtual void s70();
  virtual void s71();
  virtual void s72();
  virtual void s73();
  virtual void s74();
  virtual void s75();
  virtual void s76();
  virtual void s77();
  virtual void s78();
  virtual void s79();
  virtual void s80();
  virtual void s81();
  virtual void s82();
  virtual void s83();
  virtual void s84();
  virtual void s85();
  virtual void s86();
  virtual void s87();
  virtual void s88();
  virtual void s89();
  virtual void s90();
  virtual void V91();  // slot 91
};
extern IBtn* CreateDefaultButton(int a, int b, int c);                            // 0x009671c0 WinButton::CreateDefault
struct WinTextEdit;  // EA::UTFWinControls::WinTextEdit, 0x658 bytes; ITE sub-object at +0x20c
struct WinTextEditMem {
  WinTextEdit* Construct();  // 0x0098c110 (thiscall, returns this)
};
struct EString {  // eastl::string (narrow)
  char* b;
  char* e;
  char* cap;
  EString() : b(kEmptyStr), e(kEmptyStr), cap(kEmptyStr + 1) {}
  void sprintf(const char* fmt, ...);                                             // 0x00472fe0 (cdecl)
  ~EString() {
    if ((int)(cap - b) > 1 && b) operator delete[](b);
  }
};
template <class T>
struct RefHold {  // local owning reference: AddRef on construction (if non-null), Release on scope exit
  T* p;
  explicit RefHold(T* x) : p(x) {
    if (p) p->AddRef();
  }
  ~RefHold() {
    if (p) p->Release();
  }
  T* operator->() const { return p; }
};
struct EString16_s0082_4c20 {  // eastl::string16
  char* b;
  char* e;
  char* cap;
  ~EString16_s0082_4c20() {
    if ((int)(((unsigned)cap - (unsigned)b) & 0xfffffffe) > 2 && b) operator delete(b);
  }
};
extern EString16_s0082_4c20* ConvertToString16(EString16_s0082_4c20* out, const EString* in);          // 0x0093c6d0
template <class T>
struct SpVec {  // eastl::vector<T*, sp_vector_allocator>, 0x14 bytes
  T** b;
  T** e;
  T** cap;
  unsigned pad[2];
  unsigned size() const {
    if (b == e) return 0;
    return (unsigned)(e - b);
  }
  void Grow(T** pos, T** val);   // vector<T*>::DoInsertValue; per-T addresses in symbols/slices/s00825930.txt
  void push_back(T* v) {
    T* tmp = v;
    T** at = e;
    if (at < cap) {
      e = at + 1;
      if (at) *at = v;
    } else {
      Grow(at, &tmp);
    }
  }
  ~SpVec() {
    if (b && ((int*)b)[-1]) operator delete(b);
  }
};
template <class T> struct AutoRef {
  T* p;
  AutoRef& operator=(T* o) {
    if (p != o) {
      T* old = p;
      if (o) o->AddRef();
      p = o;
      if (old) old->Release();
    }
    return *this;
  }
  ~AutoRef() {
    if (p) p->Release();
  }
};
struct HashMapBase {  // eastl::hash_map<unsigned, T*>, 0x20 bytes
  unsigned pad0;
  void* buckets;      // +4
  unsigned nbuckets;  // +8
  unsigned count;     // +0xc
  unsigned pad[4];
  void DoFreeNodes(void* b, unsigned n);  // 0x00693230
  void clear() {
    DoFreeNodes(buckets, nbuckets);
    count = 0;
  }
  ~HashMapBase() {
    clear();
    if (nbuckets > 1) operator delete(buckets);
  }
};
struct TEMap : HashMapBase {
  ITE*& operator[](const unsigned& k);  // 0x00820af0
};
struct BtnMap : HashMapBase {};
struct cSPUILayout_s0082_4c20 {
  unsigned pad[6];
  ~cSPUILayout_s0082_4c20();  // 0x00811fe0
};
struct IWinProc {
  virtual ~IWinProc() {}
  virtual void ip0();
  virtual void ip1();
  virtual void ip2();
};
struct RefCountVTemplate {
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  int mRefCount;
};
struct cPropertyUI_s0082_4c20 : IWinProc, RefCountVTemplate {
  unsigned mCurrentGroupID;     // +0xc
  unsigned mCurrentInstanceID;  // +0x10
  float mCurrentX;              // +0x14
  float mCurrentY;              // +0x18
  float mCurrentWindowX;        // +0x1c
  float mCurrentWindowY;        // +0x20
  float mPreviousScrollVal;     // +0x24
  float mRefreshScrollVal;      // +0x28
  float mScrollRatio;           // +0x2c
  float mScrollHeight;          // +0x30
  unsigned mSpinnerButtonID;    // +0x34
  float mFloatIncrement;        // +0x38
  unsigned mIntIncrement;       // +0x3c
  bool returnPressed;           // +0x40
  cSPUILayout_s0082_4c20 mLayout;          // +0x44
  AutoRef<IBtn> mEditorDialog;  // +0x5c
  AutoRef<IBtn> mChooserDialog; // +0x60
  AutoRef<IWinW> mHolderWindow; // +0x64
  AutoRef<IBtn> mScrollbar;     // +0x68
  AutoRef<IBtn> mTitleText;     // +0x6c
  SpVec<IBtn> mButton;          // +0x70
  SpVec<IBtn> mToggleButton;    // +0x84
  SpVec<IBtn> mComboBox;        // +0x98
  SpVec<IBtn> mGrid;            // +0xac
  SpVec<IBtn> mSpinner;         // +0xc0
  SpVec<IBtn> mSlider;          // +0xd4
  SpVec<IBtn> mText;            // +0xe8
  SpVec<ITE> mTextEdit;         // +0xfc
  SpVec<IWinW> mSubWindow;      // +0x110
  AutoRef<IBtn> mDialog;        // +0x124
  AutoRef<IGrid> mGroupsGrid;   // +0x128
  AutoRef<IGrid> mPropsGrid;    // +0x12c
  TEMap mPropToTextEditMap;     // +0x130
  TEMap mSpinnerToTextEditMap;  // +0x150
  BtnMap mPropToToggleButtonMap;// +0x170

  void ClearAll();  // 0x00824c20
  unsigned AddSpinnerRow(unsigned id, float value, IWinW* parent);                    // 0x00825930
  unsigned AddIntSpinnerRow(unsigned id, int value, IWinW* parent);                   // 0x008252b0
  unsigned AddTextEditRowA(unsigned id, const void* text, IWinW* parent);             // 0x00825fc0
  unsigned AddTextEditRowB(unsigned id, const void* text, IWinW* parent);             // 0x00826290
  virtual ~cPropertyUI_s0082_4c20();                                                             // 0x00826560
};
// ---- items of slice s00824c20 end

// ---- items of slice s00825930 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char kSprintfFmt[];                                                  // 0x013fcac8
extern const float kRowAdvance;                                                   // 0x01419dd4 (210)
extern const float kEditW;                                                        // 0x01477fbc
extern const float kEditH;                                                        // 0x013eecd8
struct EString_s0082_5930 {  // eastl::string (narrow)
  char* b;
  char* e;
  char* cap;
  EString_s0082_5930() : b(kEmptyStr), e(kEmptyStr), cap(kEmptyStr + 1) {}
  void sprintf(const char* fmt, ...);                                             // 0x00472fe0 (cdecl)
};
struct EString16_s0082_5930 {  // eastl::string16
  char* b;
  char* e;
  char* cap;
  ~EString16_s0082_5930() {
    if ((int)(((unsigned)cap - (unsigned)b) & 0xfffffffe) > 2 && b) operator delete(b);
  }
};
extern EString16_s0082_5930* ConvertToString16(EString16_s0082_5930* out, const EString_s0082_5930* in);          // 0x0093c6d0
struct cSPUILayout_s0082_5930 {
  unsigned pad[6];
  ~cSPUILayout_s0082_5930();  // 0x00811fe0
};
struct cPropertyUI_s0082_5930 : IWinProc, RefCountVTemplate {
  unsigned mCurrentGroupID;     // +0xc
  unsigned mCurrentInstanceID;  // +0x10
  float mCurrentX;              // +0x14
  float mCurrentY;              // +0x18
  float mCurrentWindowX;        // +0x1c
  float mCurrentWindowY;        // +0x20
  float mPreviousScrollVal;     // +0x24
  float mRefreshScrollVal;      // +0x28
  float mScrollRatio;           // +0x2c
  float mScrollHeight;          // +0x30
  unsigned mSpinnerButtonID;    // +0x34
  float mFloatIncrement;        // +0x38
  unsigned mIntIncrement;       // +0x3c
  bool returnPressed;           // +0x40
  cSPUILayout_s0082_5930 mLayout;          // +0x44
  AutoRef<IBtn> mEditorDialog;  // +0x5c
  AutoRef<IBtn> mChooserDialog; // +0x60
  AutoRef<IWinW> mHolderWindow; // +0x64
  AutoRef<IBtn> mScrollbar;     // +0x68
  AutoRef<IBtn> mTitleText;     // +0x6c
  SpVec<IBtn> mButton;          // +0x70
  SpVec<IBtn> mToggleButton;    // +0x84
  SpVec<IBtn> mComboBox;        // +0x98
  SpVec<IBtn> mGrid;            // +0xac
  SpVec<IBtn> mSpinner;         // +0xc0
  SpVec<IBtn> mSlider;          // +0xd4
  SpVec<IBtn> mText;            // +0xe8
  SpVec<ITE> mTextEdit;         // +0xfc
  SpVec<IWinW> mSubWindow;      // +0x110
  AutoRef<IBtn> mDialog;        // +0x124
  AutoRef<IGrid> mGroupsGrid;   // +0x128
  AutoRef<IGrid> mPropsGrid;    // +0x12c
  TEMap mPropToTextEditMap;     // +0x130
  TEMap mSpinnerToTextEditMap;  // +0x150
  BtnMap mPropToToggleButtonMap;// +0x170

  void ClearAll();  // 0x00824c20
  unsigned AddSpinnerRow(unsigned id, float value, IWinW* parent);                    // 0x00825930
  unsigned AddTextEditRowA(unsigned id, const void* text, IWinW* parent);             // 0x00825fc0
  unsigned AddTextEditRowB(unsigned id, const void* text, IWinW* parent);             // 0x00826290
  virtual ~cPropertyUI_s0082_5930();                                                             // 0x00826560
};
    void CreateDefaultButton(...); // 0x009671c0
// ---- items of slice s00825930 end

// ---- items of slice s00826960 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyString16[];  // 0x01667bac (EASTL empty-string buffer)
extern const int kDefaultInt32;       // 0x015d1160
extern const uint32_t kDefaultUInt32; // 0x015d1164
struct string8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;
};
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;

    string16()
    {
        mpBegin = gEmptyString16;
        mpEnd = gEmptyString16;
        mpCapacity = gEmptyString16 + 1;
    }
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf();  // 0x00933960
    const wchar_t* c_str() const { return mpBegin; }
};
namespace EA {
string16 ConvertToString16(const string8& s);  // 0x0093c6d0
}
void operator_delete__(void* p);  // 0x00f47380 (operator delete[])
struct UIntVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAllocator;

    UIntVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~UIntVector()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    uint32_t& operator[](uint32_t n) { return mpBegin[n]; }
};
struct HashMap {
    uint32_t mHash;
    void** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    uint32_t mRest[4];

    void DoFreeNodes(void** pBucketArray, uint32_t n);  // 0x00693230
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
};
struct ColorRGB_s0082_6960 {
    float r, g, b;
    ColorRGB_s0082_6960() {}
    ColorRGB_s0082_6960& operator=(const ColorRGB_s0082_6960& c)
    {
        r = c.r;
        g = c.g;
        b = c.b;
        return *this;
    }
};
struct ColorRGBA_s0082_6960 {
    float r, g, b, a;
    ColorRGBA_s0082_6960() {}
    ColorRGBA_s0082_6960& operator=(const ColorRGBA_s0082_6960& c)
    {
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;
        return *this;
    }
};
struct ResourceKey_s0082_6960 {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
enum {
    kTypeBool_s0082_6960 = 1, kTypeInt32_s0082_6960 = 9, kTypeUInt32_s0082_6960 = 0xa, kTypeFloat_s0082_6960 = 0xd, kTypeString8_s0082_6960 = 0x12,
    kTypeString16_s0082_6960 = 0x13, kTypeKey_s0082_6960 = 0x20, kTypeVector2_s0082_6960 = 0x30, kTypeVector3_s0082_6960 = 0x31,
    kTypeColorRGB_s0082_6960 = 0x32, kTypeVector4_s0082_6960 = 0x33, kTypeColorRGBA_s0082_6960 = 0x34, kTypeArray_s0082_6960 = 0x80000000
};
struct Property {
    void* mpData;        // +0x00 (array data, or the inline value itself)
    uint32_t pad04;
    int mnItemCount;     // +0x08
    uint32_t pad0c;
    uint16_t mnFlags;    // +0x10 (0x30 = array)
    uint16_t mnType;     // +0x12

    void* GetDataPtr()
    {
        if (mnFlags & 0x30)
            return mpData;
        return mnType ? this : 0;
    }
    // only used once the type is known to be bool
    const bool* GetValueBoolUnchecked() { return (const bool*)((mnFlags & 0x30) ? mpData : this); }
    const int* GetValueInt32()
    {
        return (mnType == kTypeInt32_s0082_6960 || mnType == 0x10) ? (const int*)GetDataPtr() : &kDefaultInt32;
    }
    const uint32_t* GetValueUInt32()
    {
        return (mnType == kTypeUInt32_s0082_6960 || mnType == 0x10) ? (const uint32_t*)GetDataPtr() : &kDefaultUInt32;
    }

    const float* GetValueFloat();            // 0x0041ea70
    const string8* GetValueString8();        // 0x0060ebf0
    const string16* GetValueString16();      // 0x0068a4f0
    const ResourceKey_s0082_6960* GetValueKey();        // 0x006a1030
    const Vector2* GetValueVector2();        // 0x006a0f70
    const Vector3* GetValueVector3();        // 0x00cce910
    const Vector4* GetValueVector4();        // 0x006a0fa0
    const ColorRGB_s0082_6960* GetValueColorRGB();      // 0x006a0fd0
    const ColorRGBA_s0082_6960* GetValueColorRGBA();    // 0x006a1000
    int GetItemCount();                      // 0x00571ef0
    void* GetValue();                        // 0x00446ff0
};
class cPropertyList_s0082_6960 {
public:
    virtual int AddRef();
    virtual int Release();                                       // 0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual bool HasProperty(uint32_t id);                       // 0x1c 0x006a2470
    virtual void v20();
    virtual void v24();
    virtual Property* GetPropertyObject(uint32_t id);            // 0x28
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void GetPropertyIDs(UIntVector& ids);                // 0x44 0x006a3070
};
template <class T>
struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr()
    {
        if (mpObject)
            mpObject->Release();
    }
    void reset()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
class cPropertyManager_s0082_6960 {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual const wchar_t* GetPropertyName(uint32_t id);                                   // 0x1c
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID,
                                 intrusive_ptr<cPropertyList_s0082_6960>& dst);                       // 0x2c
};
cPropertyManager_s0082_6960* PropertyManager_s0082_6960();  // 0x0067de30
namespace EA {
namespace ResourceMan {
class IResourceManager_s0082_6960 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78();
    virtual bool GetFileName(const ResourceKey_s0082_6960& key, string16& name);  // 0x7c
};
}
}
namespace EA {
namespace ResourceMan {
IResourceManager_s0082_6960* GetManager();  // 0x0067dcd0
}
}
class IWindow;
class IWinScrollbar {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual void SetValue(int value, int notify);  // 0x24
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual int GetMaxValue();                     // 0x38
    virtual void SetMaxValue(int value, int notify);  // 0x3c
};
template <class T>
struct AutoRefCount_s0082_6960 {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
struct WindowVector {
    IWindow** mpBegin;
    IWindow** mpEnd;
    IWindow** mpCapacity;
    uint32_t mAllocator;
    IWindow*& operator[](int i) { return mpBegin[i]; }
};
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }
namespace SP {
class cPropertyUI_s0082_6960 {
public:
    void LoadPropFile(uint32_t groupID, uint32_t instanceID, bool refresh);  // 0x00826960 (SP::cPropertyUI::LoadPropFile)

    void ClearWindows();                                          // 0x008268b0
    void AddLabel(const wchar_t* text);                           // 0x00824e10
    int AddSubWindow(uint32_t propertyID);                        // 0x00824ff0
    void AddBool(int id, bool value, IWindow* parent);            // 0x00825110
    void AddInt(int id, int value, IWindow* parent);              // 0x008252b0
    void AddFloat(int id, float value, IWindow* parent);          // 0x00825930
    void AddString(int id, const wchar_t* value, IWindow* parent);  // 0x00825fc0
    void AddKey(int id, const wchar_t* value, IWindow* parent);   // 0x00826290
    void UpdateLayout();                                          // 0x0081e070

    void NewLine()
    {
        mCurrentX = 0.0f;
        mCurrentY += 30.0f;
    }

    uint32_t pad00[3];
    uint32_t mCurrentGroupID;     // +0x0c
    uint32_t mCurrentInstanceID;  // +0x10
    float mCurrentX;              // +0x14
    float mCurrentY;              // +0x18
    float mCurrentWindowX;        // +0x1c
    float mCurrentWindowY;        // +0x20
    float mPreviousScrollVal;     // +0x24
    float mRefreshScrollVal;      // +0x28
    float mScrollRatio;           // +0x2c
    float mScrollHeight;          // +0x30
    uint32_t mSpinnerButtonID;    // +0x34
    uint32_t pad38[(0x64 - 0x38) / 4];
    AutoRefCount_s0082_6960<IWindow> mHolderWindow;  // +0x64
    AutoRefCount_s0082_6960<IWinScrollbar> mScrollbar;  // +0x68
    uint32_t pad6c[(0x110 - 0x6c) / 4];
    WindowVector mSubWindows;     // +0x110
    uint32_t pad120[(0x130 - 0x120) / 4];
    HashMap mSpinnerToTextEditMap;   // +0x130
    HashMap mPropToTextEditMap;      // +0x150
    HashMap mPropToToggleButtonMap;  // +0x170
};  // namespace SP
}
// ---- items of slice s00826960 end

// ---- items of slice s00b5f040 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWinControls {
class IWinText_s00b5_f040 {
public:
    virtual int AddRef();
    virtual int Release();
};
}
}
namespace EA {
template <typename T> struct AutoRefCount_s00b5_f040 {
    T* mpObject;
    AutoRefCount_s00b5_f040& operator=(T* p);
};
}
namespace EA {
template struct AutoRefCount_s00b5_f040<UTFWinControls::IWinText_s00b5_f040>;
}
// ---- items of slice s00b5f040 end

// @ 0x0081d7a0
Variant* Variant::Reset(int v)
{
  if (flags & 4) Destruct(1);
  unsigned short f = flags & 2;
  if (f && typeId != 1) { Call5(1, 0x20, v, 1, 1); return this; }
  flags = f | 0x20; typeId = 1;
  f0 = v; f4 = 1; f8 = 1;
  return this;
}










// @ 0x0081da30
Variant* Variant::Set20(int v)
{
  if (flags & 4) Destruct(1);
  unsigned short f = flags & 2;
  if (f && typeId != 0x20) { Call5(0x20, 0x20, v, 0xc, 1); return this; }
  flags = f | 0x20; typeId = 0x20;
  f0 = v; f4 = 0xc; f8 = 1;
  return this;
}










// @ 0x0081dce0
void SP::cSPUIPropertyEditor::Shutdown()
{
  void* p = mPropUI.mpObject;
  if (p != 0) {
    ((Layout*)((char*)p + 0x44))->Shutdown(1);
    p = mPropUI.mpObject;
    if (p != 0) {
      mPropUI.mpObject = 0;
      ((void (__thiscall*)(void*))VTSLOT(p, 4))(p);
    }
  }
  void* s = MessageServer();
  if (s != 0) {
    ((void (__thiscall*)(void*, void*, void*, int))VTSLOT(s, 0x2c))(s, this, &g_15bbbf3, 0xffffd8f1);
    ((void (__thiscall*)(void*, void*, void*, int))VTSLOT(s, 0x2c))(s, this, &g_16af8d8, 0xffffd8f1);
  }
}










// @ 0x0081ddd0
D3* D3::Init(int arg)
{ w10 = 2; w12 = 0x33; Call5(0x33, 0, arg, 0x10, 1); return this; }










// @ 0x0081de30
D3* D3::Init2(int arg)
{ w10 = 2; w12 = 0x34; Call5(0x34, 0, arg, 0x10, 1); return this; }









// @ 0x0081fd70
namespace SP {
void cPropertyUI_s0081_fd70::ModifyVec4(IWindow* window, bool bArray)
{
  AutoRefCount<IWinTextEdit> textEdit;
  AutoRefCount<PropertyList> propList;
  EString16 text;
  AutoRefCount<IWindow> childWindow;
  PropertyManager()->GetPropertyList(mCurrentInstanceID, mCurrentGroupID, propList.AsPPTypeParam());
  if (!bArray) {
    Vector4 v4;
    wchar_t* end;
    for (ChildIterator it = window->children_begin(); it != window->children_end(); ++it) {
      unsigned idx = (*it)->GetControlID();
      if (idx) {
        childWindow = *it;
        textEdit = interface_cast<IWinTextEdit>(childWindow);
        text = textEdit->GetText();
        (&v4.x)[idx - 1] = (float)StrtodW(text.c_str(), &end);
      }
    }
    propList->SetProperty(window->GetControlID(), VariantT16<kTypeVector4, Vector4>(v4));
  } else {
    Vector4* pValue = (Vector4*)VariantValue(propList->GetProperty(window->GetControlID()));
    Vector4* pCur = pValue;
    Vector4 v4;
    unsigned i = 0;
    wchar_t* end;
    for (ChildIterator it = window->children_begin(); it != window->children_end(); ++it) {
      if ((*it)->GetControlID()) {
        childWindow = *it;
        textEdit = interface_cast<IWinTextEdit>(childWindow);
        text = textEdit->GetText();
        (&v4.x)[i] = (float)StrtodW(text.c_str(), &end);
        ++i;
        if (i == 4) {
          ++pCur;
          *pCur = v4;
          i = 0;
        }
      }
    }
    propList->SetProperty(window->GetControlID(), VariantConv<kTypeVector3>(VariantPtr(pValue)));
  }
  childWindow = 0;
  textEdit = 0;
  ReloadPropResource();
}
}  // namespace SP









// @ 0x00820210
namespace SP {
void cPropertyUI_s0081_fd70::ModifyRGB(IWindow* window, bool bArray)
{
  AutoRefCount<IWinTextEdit> textEdit;
  AutoRefCount<PropertyList> propList;
  EString16 text;
  AutoRefCount<IWindow> childWindow;
  PropertyManager()->GetPropertyList(mCurrentInstanceID, mCurrentGroupID, propList.AsPPTypeParam());
  if (!bArray) {
    ColorRGB c;
    wchar_t* end;
    for (ChildIterator it = window->children_begin(); it != window->children_end(); ++it) {
      unsigned idx = (*it)->GetControlID();
      if (idx) {
        childWindow = *it;
        textEdit = interface_cast<IWinTextEdit>(childWindow);
        text = textEdit->GetText();
        (&c.r)[idx - 1] = (float)StrtodW(text.c_str(), &end);
      }
    }
    propList->SetProperty(window->GetControlID(), VariantRGB(c));
  } else {
    ColorRGB* pValue = (ColorRGB*)VariantValue(propList->GetProperty(window->GetControlID()));
    ColorRGB* pCur = pValue;
    ColorRGB c;
    unsigned i = 0;
    wchar_t* end;
    for (ChildIterator it = window->children_begin(); it != window->children_end(); ++it) {
      if ((*it)->GetControlID()) {
        childWindow = *it;
        textEdit = interface_cast<IWinTextEdit>(childWindow);
        text = textEdit->GetText();
        (&c.r)[i] = (float)StrtodW(text.c_str(), &end);
        ++i;
        if (i == 3) {
          ++pCur;
          *pCur = c;
          i = 0;
        }
      }
    }
    propList->SetProperty(window->GetControlID(), VariantArr<kTypeColorRGB, ColorRGB>(pValue));
  }
  childWindow = 0;
  textEdit = 0;
  ReloadPropResource();
}
}  // namespace SP









// @ 0x00820680
namespace SP {
void cPropertyUI_s0081_fd70::ModifyRGBA(IWindow* window, bool bArray)
{
  AutoRefCount<IWinTextEdit> textEdit;
  AutoRefCount<PropertyList> propList;
  EString16 text;
  AutoRefCount<IWindow> childWindow;
  PropertyManager()->GetPropertyList(mCurrentInstanceID, mCurrentGroupID, propList.AsPPTypeParam());
  if (!bArray) {
    ColorRGBA c;
    wchar_t* end;
    for (ChildIterator it = window->children_begin(); it != window->children_end(); ++it) {
      unsigned idx = (*it)->GetControlID();
      if (idx) {
        childWindow = *it;
        textEdit = interface_cast<IWinTextEdit>(childWindow);
        text = textEdit->GetText();
        (&c.r)[idx - 1] = (float)StrtodW(text.c_str(), &end);
      }
    }
    propList->SetProperty(window->GetControlID(), VariantT16<kTypeColorRGBA, ColorRGBA>(c));
  } else {
    ColorRGBA* pValue = (ColorRGBA*)VariantValue(propList->GetProperty(window->GetControlID()));
    ColorRGBA* pCur = pValue;
    ColorRGBA c;
    unsigned i = 0;
    wchar_t* end;
    for (ChildIterator it = window->children_begin(); it != window->children_end(); ++it) {
      if ((*it)->GetControlID()) {
        childWindow = *it;
        textEdit = interface_cast<IWinTextEdit>(childWindow);
        text = textEdit->GetText();
        (&c.r)[i] = (float)StrtodW(text.c_str(), &end);
        ++i;
        if (i == 4) {
          ++pCur;
          *pCur = c;
          i = 0;
        }
      }
    }
    propList->SetProperty(window->GetControlID(), VariantArr<kTypeColorRGBA, ColorRGBA>(pValue));
  }
  childWindow = 0;
  textEdit = 0;
  ReloadPropResource();
}
}  // namespace SP









// @ 0x00820bb0
void PtrVec::DoInsertValue(void** position, void* const& value)
{
  if (mpEnd != mpCapacity) {
    void* const* pv = &value;
    if (pv >= position && pv < mpEnd) ++pv;
    if (mpEnd) *mpEnd = *(mpEnd - 1);
    size_t n = (size_t)((char*)(mpEnd - 1) - (char*)position);
    memmove(mpEnd - ((int)n >> 2), position, n);
    *position = *pv;
    ++mpEnd;
  } else {
    uint32_t prevSize = (uint32_t)(mpEnd - mpBegin);
    uint32_t newSize = prevSize ? 2 * prevSize : 1;
    void** pNew = newSize ? (void**)EASTL_allocator_allocate(newSize * 4, "Editor", 0, 0, ALLOC_FILE, 0xd1) : 0;
    size_t nBefore = (char*)position - (char*)mpBegin;
    memcpy(pNew, mpBegin, nBefore);
    void** pNewPos = pNew + (nBefore >> 2);
    if (pNewPos) *pNewPos = value;
    size_t nAfter = (char*)mpEnd - (char*)position;
    void** pNewEnd = (void**)memcpy(pNewPos + 1, position, nAfter);
    pNewEnd += (int)nAfter >> 2;
    if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
    mpBegin = pNew; mpEnd = pNewEnd; mpCapacity = pNew + newSize;
  }
}








// @ 0x008220e0
namespace SP {
void cPropertyUI_s0082_20e0::SavePropFile()
{
  AutoRefCount<PropertyList_s0082_20e0> propList;
  PropertyIDList ids;
  Vector2 v2;
  Vector3 v3;
  Vector4 v4;
  PropertyManager_s0082_20e0()->GetPropertyList(mCurrentInstanceID, mCurrentGroupID, propList.AsPPTypeParam());
  bool bValue = false;
  AutoRefCount<IWinButton> button;
  EString16_s0082_20e0 text;
  AutoRefCount<IWinTextEdit> textEdit;
  AutoRefCount<IWindow_s0082_20e0> window;
  AutoRefCount<IWinTextEdit> childTextEdit;
  AutoRefCount<IWindow_s0082_20e0> childWindow;

  if (propList) {
    propList->GetPropertyIDs(ids);
    if (!ids.empty()) {
      for (ChildIterator_s0082_20e0 it = mHolderWindow->children_begin(); it != mHolderWindow->children_end(); ++it) {
        unsigned id = (*it)->GetControlID();
        if (!id) continue;
        Variant_s0082_20e0* prop = propList->GetProperty(id);
        unsigned short type = prop->mType;

        if (type == kTypeBool) {
          window = *it;
          button = interface_cast_s0082_20e0<IWinButton>(window);
          if (button->GetButtonStateFlags() & 4)
            bValue = true;
          else
            bValue = false;
          propList->SetProperty(id, VariantT<kTypeBool, bool>(bValue));
        } else if (type == kTypeInt32) {
          window = *it;
          textEdit = interface_cast_s0082_20e0<IWinTextEdit>(window);
          text = textEdit->GetText();
          propList->SetProperty(id, VariantConv_s0082_20e0<kTypeInt32>(VariantString(text)));
        } else if (type == kTypeUInt32) {
          window = *it;
          textEdit = interface_cast_s0082_20e0<IWinTextEdit>(window);
          text = textEdit->GetText();
          propList->SetProperty(id, VariantConv_s0082_20e0<kTypeUInt32>(VariantString(text)));
        } else if (type == kTypeFloat) {
          window = *it;
          textEdit = interface_cast_s0082_20e0<IWinTextEdit>(window);
          text = textEdit->GetText();
          propList->SetProperty(id, VariantConv_s0082_20e0<kTypeFloat>(VariantString(text)));
        } else if (type == kTypeString8) {
          window = *it;
          textEdit = interface_cast_s0082_20e0<IWinTextEdit>(window);
          text = textEdit->GetText();
          EString8 text8 = EA::ConvertToString8(text.c_str());
          propList->SetProperty(id, VariantStr<kTypeString8, EString8>(text8));
        } else if (type == kTypeString16) {
          window = *it;
          textEdit = interface_cast_s0082_20e0<IWinTextEdit>(window);
          text = textEdit->GetText();
          propList->SetProperty(id, VariantStr<kTypeString16, EString16_s0082_20e0>(text));
        } else if (type == kTypeKey) {
          window = *it;
          textEdit = interface_cast_s0082_20e0<IWinTextEdit>(window);
          text = textEdit->GetText();
          ResourceKey key;
          SPKeyFromName(&key, text.c_str(), 0, 0);
          propList->SetProperty(id, VariantT<kTypeKey, ResourceKey>(key));
        } else if (type == kTypeVector2) {
          window = *it;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            unsigned cid = (*c)->GetControlID();
            if (cid) {
              childWindow = *c;
              childTextEdit = interface_cast_s0082_20e0<IWinTextEdit>(childWindow);
              text = childTextEdit->GetText();
              (&v2.x)[cid - 1] = ParseFloat(text.c_str());
            }
          }
          propList->SetProperty(id, VariantT<kTypeVector2, Vector2>(v2));
        } else if (type == kTypeVector3_s0082_20e0) {
          window = *it;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            unsigned cid = (*c)->GetControlID();
            if (cid) {
              childWindow = *c;
              childTextEdit = interface_cast_s0082_20e0<IWinTextEdit>(childWindow);
              text = childTextEdit->GetText();
              (&v3.x)[cid - 1] = ParseFloat(text.c_str());
            }
          }
          propList->SetProperty(id, VariantT<kTypeVector3_s0082_20e0, Vector3>(v3));
        } else if (type == kTypeVector4_s0082_20e0) {
          window = *it;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            unsigned cid = (*c)->GetControlID();
            if (cid) {
              childWindow = *c;
              childTextEdit = interface_cast_s0082_20e0<IWinTextEdit>(childWindow);
              text = childTextEdit->GetText();
              (&v4.x)[cid - 1] = ParseFloat(text.c_str());
            }
          }
          propList->SetProperty(id, VariantT16_s0082_20e0<kTypeVector4_s0082_20e0, Vector4>(v4));
        } else if (type == kTypeColorRGB_s0082_20e0) {
          ColorRGB color;
          window = *it;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            unsigned cid = (*c)->GetControlID();
            if (cid) {
              childWindow = *c;
              childTextEdit = interface_cast_s0082_20e0<IWinTextEdit>(childWindow);
              text = childTextEdit->GetText();
              (&color.r)[cid - 1] = ParseFloat(text.c_str());
            }
          }
          propList->SetProperty(id, VariantT<kTypeColorRGB_s0082_20e0, ColorRGB>(color));
        } else if (type == kTypeColorRGBA_s0082_20e0) {
          ColorRGBA color;
          window = *it;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            unsigned cid = (*c)->GetControlID();
            if (cid) {
              childWindow = *c;
              childTextEdit = interface_cast_s0082_20e0<IWinTextEdit>(childWindow);
              text = childTextEdit->GetText();
              (&color.r)[cid - 1] = ParseFloat(text.c_str());
            }
          }
          propList->SetProperty(id, VariantT16_s0082_20e0<kTypeColorRGBA_s0082_20e0, ColorRGBA>(color));
        }
        // Array types: mType is 16 bits, so these never match at run time, but the
        // original compiled them (the compares are emitted after a movzx).
        else if (type == (kTypeArray | kTypeBool)) {
          window = *it;
          bool* pStart = (bool*)prop->GetValue();
          bool* p = pStart;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              button = interface_cast_s0082_20e0<IWinButton>(childWindow);
              *p++ = (button->GetButtonStateFlags() & 4) == 4;
            }
          }
          propList->SetProperty(id, VariantArr_s0082_20e0<kTypeBool, bool>(pStart));
        } else if (type == (kTypeArray | kTypeInt32)) {
          window = *it;
          int* pStart = (int*)prop->GetValue();
          int* p = pStart;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast_s0082_20e0<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              *p++ = wcstol(text.c_str(), 0, 0);
            }
          }
          propList->SetProperty(id, VariantArr_s0082_20e0<kTypeInt32, int>(pStart));
        } else if (type == (kTypeArray | kTypeUInt32)) {
          window = *it;
          unsigned* pStart = (unsigned*)prop->GetValue();
          unsigned* p = pStart;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast_s0082_20e0<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              *p++ = wcstoul(text.c_str(), 0, 0);
            }
          }
          propList->SetProperty(id, VariantArr_s0082_20e0<kTypeUInt32, unsigned>(pStart));
        } else if (type == (kTypeArray | kTypeFloat)) {
          window = *it;
          float* pStart = (float*)prop->GetValue();
          float* p = pStart;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast_s0082_20e0<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              *p++ = ParseFloat(text.c_str());
            }
          }
          propList->SetProperty(id, VariantArr_s0082_20e0<kTypeFloat, float>(pStart));
        } else if (type == (kTypeArray | kTypeString8)) {
          window = *it;
          EString8* pStart = (EString8*)prop->GetValue();
          EString8* p = pStart;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast_s0082_20e0<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              *p = EA::ConvertToString8(text);
              ++p;
            }
          }
          propList->SetProperty(id, VariantArr_s0082_20e0<kTypeString8, EString8>(pStart));
        } else if (type == (kTypeArray | kTypeString16)) {
          window = *it;
          EString16_s0082_20e0* pStart = (EString16_s0082_20e0*)prop->GetValue();
          EString16_s0082_20e0* p = pStart;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast_s0082_20e0<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              *p = text;
              ++p;
            }
          }
          propList->SetProperty(id, VariantArr_s0082_20e0<kTypeString16, EString16_s0082_20e0>(pStart));
        } else if (type == (kTypeArray | kTypeKey)) {
          window = *it;
          ResourceKey* pStart = (ResourceKey*)prop->GetValue();
          ResourceKey* p = pStart;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast_s0082_20e0<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              SPKeyFromName(p, text.c_str(), 0, 0);
              ++p;
            }
          }
          propList->SetProperty(id, VariantArr_s0082_20e0<kTypeKey, ResourceKey>(pStart));
        } else if (type == (kTypeArray | kTypeVector2)) {
          window = *it;
          int n = 0;
          Vector2* pStart = (Vector2*)prop->GetValue();
          Vector2* p = pStart;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast_s0082_20e0<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              (&v2.x)[n] = ParseFloat(text.c_str());
              if (++n == 2) {
                *++p = v2;  // the original pre-increments: the first element is never written
                n = 0;
              }
            }
          }
          propList->SetProperty(id, VariantArr_s0082_20e0<kTypeVector2, Vector2>(pStart));
        } else if (type == (kTypeArray | kTypeVector3_s0082_20e0)) {
          window = *it;
          int n = 0;
          Vector3* pStart = (Vector3*)prop->GetValue();
          Vector3* p = pStart;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast_s0082_20e0<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              (&v3.x)[n] = ParseFloat(text.c_str());
              if (++n == 3) {
                *++p = v3;
                n = 0;
              }
            }
          }
          propList->SetProperty(id, VariantArr_s0082_20e0<kTypeVector3_s0082_20e0, Vector3>(pStart));
        } else if (type == (kTypeArray | kTypeVector4_s0082_20e0)) {
          window = *it;
          int n = 0;
          Vector4* pStart = (Vector4*)prop->GetValue();
          Vector4* p = pStart;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast_s0082_20e0<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              (&v4.x)[n] = ParseFloat(text.c_str());
              if (++n == 4) {
                *++p = v4;
                n = 0;
              }
            }
          }
          // The original wraps the Vector4 array by reference and converts it to a Vector3 property.
          propList->SetProperty(id, VariantConv_s0082_20e0<kTypeVector3_s0082_20e0>(VariantPtr_s0082_20e0(pStart)));
        } else if (type == (kTypeArray | kTypeColorRGB_s0082_20e0)) {
          window = *it;
          int n = 0;
          ColorRGB color;
          ColorRGB* pStart = (ColorRGB*)prop->GetValue();
          ColorRGB* p = pStart;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast_s0082_20e0<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              (&color.r)[n] = ParseFloat(text.c_str());
              if (++n == 3) {
                *++p = color;
                n = 0;
              }
            }
          }
          propList->SetProperty(id, VariantArr_s0082_20e0<kTypeColorRGB_s0082_20e0, ColorRGB>(pStart));
        } else if (type == (kTypeArray | kTypeColorRGBA_s0082_20e0)) {
          window = *it;
          int n = 0;
          ColorRGBA color;
          ColorRGBA* pStart = (ColorRGBA*)prop->GetValue();
          ColorRGBA* p = pStart;
          for (ChildIterator_s0082_20e0 c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast_s0082_20e0<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              (&color.r)[n] = ParseFloat(text.c_str());
              if (++n == 4) {
                *++p = color;
                n = 0;
              }
            }
          }
          propList->SetProperty(id, VariantArr_s0082_20e0<kTypeColorRGBA_s0082_20e0, ColorRGBA>(pStart));
        }
      }
    }
  }

  ResourceManager()->WriteResource(propList, 0, 0, 0, 0);
  propList = 0;
  textEdit = 0;
  if (window) window = 0;
  if (childTextEdit) childTextEdit = 0;
  if (childWindow) childWindow = 0;
  ReloadPropResource();
}
}  // namespace SP






// @ 0x00823a00
void cSPUIPropertyEditor::Init()
{
  if (mInitialized) return;
  mPropUI = new ("UI/SPUIPropertyEditor/mPropUI", 0, 0, 0, 0) cPropertyUI();
  if (mPropUI->Init(L"PropertyEditor", 0x40464100)) {
    mPropUI->PopulateGroupsGrid();
    mInitialized = true;
    IMessageServer* ms = MessageServer_s0082_3a00();
    if (ms) {
      ms->AddMessageHandler(this, 0x15bbbf3);
      ms->AddMessageHandler(this, 0x16af8d8);
    }
  } else {
    mPropUI = 0;
  }
}






// @ 0x00823ac0
bool SP::cSPUIPropertyEditor::HandleMessage(unsigned int msg, void * arg)
{
  switch (msg) {
    case 0x15bbbf3:
      if (((AppPropsInner*)g_sAppProperties->p3c)->f54 != 0) {
        if (mInitialized) {
          mPropUI.mpObject->PopulateGroupsGrid();
          mPropUI.mpObject->mLayout.SetVisibility(true);
          return true;
        }
        Init();
        mPropUI.mpObject->mLayout.SetVisibility(true);
        return true;
      }
      mPropUI.mpObject->mLayout.SetVisibility(false);
      return true;
    case 0x16af8d8:
      if (mPropUI.mpObject->mCurrentGroupID != 0 && mPropUI.mpObject->mCurrentInstanceID != 0)
        return true;
      return false;
  }
  return false;
}





// @ 0x00823e30
void SP::cPropertyUI_s0082_3e30::ProcessSpinnerButtons(unsigned buttonID)
{
    HashIter it = mSpinnerMap.find(buttonID);
    if (it.mpNode == mSpinnerMap.mpBucketArray[mSpinnerMap.mnBucketCount]) return;
    IWindow_s0082_3e30* second = it.mpNode->second;
    IWindow_s0082_3e30* rowWindow = (second->GetParent()->GetParent() != mRootWindow)
        ? second->GetParent()->GetParent() : second->GetParent();
    unsigned id = rowWindow->GetControlID();
    AutoRefCountT<PropertyList_s0082_3e30> propList;
    PropertyManager_s0082_3e30()->GetPropertyList(mCurrentInstanceID, mCurrentGroupID, propList.AsPPTypeParam());
    Variant_s0082_3e30* variant = propList->GetProperty(id);
    EString16_s0082_3e30 text(second->GetText());
    unsigned short type = variant->mType;
    if ((buttonID & 1) == 0) {
        if (type == 0x9) {
            {
                EString8_s0082_3e30 s;
                s.sprintf("%d", mIntIncrement + (long)wcstol(text.mpBegin, 0, 0));
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyInt32(second->GetParent(), false);
            }
        } else if (type == 0xa) {
            {
                EString8_s0082_3e30 s;
                s.sprintf("%d", mIntIncrement + wcstoul(text.mpBegin, 0, 0));
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyUInt32(second->GetParent(), false);
            }
        } else if (type == 0xd) {
            {
                EString8_s0082_3e30 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyFloat(second->GetParent(), false);
            }
        } else if (type == 0x30) {
            {
                EString8_s0082_3e30 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyVec2(second->GetParent()->GetParent(), false);
            }
        } else if (type == 0x31) {
            {
                EString8_s0082_3e30 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyVec3(second->GetParent()->GetParent(), false);
            }
        } else if (type == 0x33) {
            {
                EString8_s0082_3e30 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyVec4(second->GetParent()->GetParent(), false);
            }
        } else if (type == 0x32) {
            {
                EString8_s0082_3e30 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyRGB(second->GetParent()->GetParent(), false);
            }
        } else if (type == 0x34) {
            {
                EString8_s0082_3e30 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyRGBA(second->GetParent()->GetParent(), false);
            }
        } else {
            unsigned t = type;
            if (t == 0x80000009) {
                {
                    EString8_s0082_3e30 s;
                    s.sprintf("%f", mIntIncrement + (long)wcstol(text.mpBegin, 0, 0));
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyInt32(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x8000000a) {
                {
                    EString8_s0082_3e30 s;
                    s.sprintf("%f", mIntIncrement + wcstoul(text.mpBegin, 0, 0));
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyUInt32(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x8000000d) {
                {
                    EString8_s0082_3e30 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyFloat(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000030) {
                {
                    EString8_s0082_3e30 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyVec2(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000031) {
                {
                    EString8_s0082_3e30 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyVec3(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000033) {
                {
                    EString8_s0082_3e30 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyVec4(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000032) {
                {
                    EString8_s0082_3e30 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyRGB(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000034) {
                {
                    EString8_s0082_3e30 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyRGBA(second->GetParent()->GetParent(), true);
                }
            }
        }
    } else {
        if (type == 0x9) {
            {
                EString8_s0082_3e30 s;
                s.sprintf("%f", (long)wcstol(text.mpBegin, 0, 0) - mIntIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyInt32(second->GetParent(), false);
            }
        } else if (type == 0xa) {
            {
                EString8_s0082_3e30 s;
                s.sprintf("%f", wcstoul(text.mpBegin, 0, 0) - mIntIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyUInt32(second->GetParent(), false);
            }
        } else if (type == 0xd) {
            {
                EString8_s0082_3e30 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyFloat(second->GetParent(), false);
            }
        } else if (type == 0x30) {
            {
                EString8_s0082_3e30 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyVec2(second->GetParent()->GetParent(), false);
            }
        } else if (type == 0x31) {
            {
                EString8_s0082_3e30 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyVec3(second->GetParent()->GetParent(), false);
            }
        } else if (type == 0x33) {
            {
                EString8_s0082_3e30 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyVec4(second->GetParent()->GetParent(), false);
            }
        } else if (type == 0x32) {
            {
                EString8_s0082_3e30 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyRGB(second->GetParent()->GetParent(), false);
            }
        } else if (type == 0x34) {
            {
                EString8_s0082_3e30 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyRGBA(second->GetParent()->GetParent(), false);
            }
        } else {
            unsigned t = type;
            if (t == 0x80000009) {
                {
                    EString8_s0082_3e30 s;
                    s.sprintf("%f", (long)wcstol(text.mpBegin, 0, 0) - mIntIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyInt32(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x8000000a) {
                {
                    EString8_s0082_3e30 s;
                    s.sprintf("%f", wcstoul(text.mpBegin, 0, 0) - mIntIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyUInt32(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x8000000d) {
                {
                    EString8_s0082_3e30 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyFloat(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000030) {
                {
                    EString8_s0082_3e30 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyVec2(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000031) {
                {
                    EString8_s0082_3e30 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyVec3(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000033) {
                {
                    EString8_s0082_3e30 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyVec4(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000032) {
                {
                    EString8_s0082_3e30 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyRGB(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000034) {
                {
                    EString8_s0082_3e30 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyRGBA(second->GetParent()->GetParent(), true);
                }
            }
        }
    }
}




// @ 0x008252b0
unsigned cPropertyUI_s0082_4c20::AddIntSpinnerRow(unsigned id, int value, IWinW* parent)
{
  unsigned idx = mTextEdit.size();
  unsigned n0 = mButton.size();
  unsigned n1 = (mButton.b == mButton.e) ? 1 : (unsigned)(mButton.e - mButton.b) + 1;
  RefHold<IBtn> b1(CreateDefaultButton(1, 0, 0));
  RefHold<IBtn> b2(CreateDefaultButton(1, 0, 0));
  void* mem = AllocAligned(0x658, 8, kTextEditName, GetAllocator());
  WinTextEdit* w = mem ? ((WinTextEditMem*)mem)->Construct() : 0;
  RefHold<ITE> te(w ? (ITE*)((char*)w + 0x20c) : 0);
  float r1[4] = {0.0f, 0.0f, kRect1W, kRect2W};
  te->GetWin()->SetArea(r1);
  te->SetColor(0, 0xff000000);
  te->SetColor(1, 0xffffffff);
  te->SetColor(2, 0xff777777);
  te->SetColor(3, 0xffffffff);
  te->SetColor(4, 0xffffffff);
  te->SetColor(5, 0xff43a2ff);
  te->SetColor(6, 0xff000000);
  te->SetColor(7, 0xff000000);
  te->V6(kStyleStr);
  EString s;
  s.sprintf(kIntFmt, value);
  IWinW* tw = te->GetWin();
  {
    EString16_s0082_4c20 out16;
    tw->SetText(ConvertToString16(&out16, &s)->b);
  }
  te->V12(kQuarter);
  te->V37(0, 0);
  te->V17(0x54, 1);
  te->V16(0);
  te->V48(10);
  unsigned pid;
  unsigned* kp;
  if (parent == mHolderWindow.p) {
    te->GetWin()->SetPos(mCurrentX, mCurrentY);
    te->GetWin()->SetB(id);
    kp = &id;
  } else {
    te->GetWin()->SetPos(mCurrentX, 0.0f);
    pid = parent->GetID();
    te->GetWin()->SetB(pid);
    kp = &pid;
  }
  mPropToTextEditMap[*kp] = te.p;
  te->GetWin()->V36();
  te->GetWin()->SetA(id);
  mCurrentX += kSpin80;
  float r2[4] = {0.0f, 0.0f, kRect2W, kRect2H};
  b1->GetWin()->SetArea(r2);
  b2->GetWin()->SetArea(r2);
  b1->GetWin()->SetHash(0xaf14b67e);
  b2->GetWin()->SetHash(0xaf14b67e);
  b1->GetWin()->SetText(kBtnTextA);
  b2->GetWin()->SetText(kBtnTextB);
  b1->GetWin()->SetA(0);
  b1->GetWin()->SetB(mSpinnerButtonID);
  mSpinnerToTextEditMap[mSpinnerButtonID] = te.p;
  ++mSpinnerButtonID;
  b2->GetWin()->SetA(0);
  b2->GetWin()->SetB(mSpinnerButtonID);
  mSpinnerToTextEditMap[mSpinnerButtonID] = te.p;
  ++mSpinnerButtonID;
  b1->GetWin()->SetPos(kSpin80, 0.0f);
  b2->GetWin()->SetPos(kSpin80, kBtn2Y);
  mCurrentX += kAdv30;
  mTextEdit.push_back(te.p);
  mButton.push_back(b1.p);
  mButton.push_back(b2.p);
  parent->AddChild(mTextEdit.b[idx]->GetWin());
  mTextEdit.b[idx]->GetWin()->AddChild(mButton.b[n0]->GetWin());
  mTextEdit.b[idx]->GetWin()->AddChild(mButton.b[n1]->GetWin());
  return idx;
}



// @ 0x00825930
unsigned cPropertyUI_s0082_5930::AddSpinnerRow(unsigned id, float value, IWinW* parent)
{
  unsigned idx = mTextEdit.size();
  unsigned n0 = mButton.size();
  unsigned n1 = (mButton.b == mButton.e) ? 1 : (unsigned)(mButton.e - mButton.b) + 1;
  IBtn* b1 = CreateDefaultButton(1, 0, 0);
  if (b1) b1->AddRef();
  IBtn* b2 = CreateDefaultButton(1, 0, 0);
  if (b2) b2->AddRef();
  void* mem = AllocAligned(0x658, 8, kTextEditName, GetAllocator());
  WinTextEdit* w = mem ? ((WinTextEditMem*)mem)->Construct() : 0;
  ITE* te = w ? (ITE*)((char*)w + 0x20c) : 0;
  if (te) te->AddRef();
  float r1[4] = {0.0f, 0.0f, kRect1W, kRect2W};
  te->GetWin()->SetArea(r1);
  te->SetColor(0, 0xff000000);
  te->SetColor(1, 0xffffffff);
  te->SetColor(2, 0xff777777);
  te->SetColor(3, 0xffffffff);
  te->SetColor(4, 0xffffffff);
  te->SetColor(5, 0xff43a2ff);
  te->SetColor(6, 0xff000000);
  te->SetColor(7, 0xff000000);
  te->V6(kStyleStr);
  EString_s0082_5930 s;
  s.sprintf(kSprintfFmt, (double)value);
  IWinW* tw = te->GetWin();
  {
    EString16_s0082_5930 out16;
    tw->SetText(ConvertToString16(&out16, &s)->b);
  }
  te->V12(kQuarter);
  te->V37(0, 0);
  te->V17(0x54, 1);
  te->V16(0);
  te->V48(10);
  unsigned pid;
  unsigned* kp;
  if (parent == mHolderWindow.p) {
    te->GetWin()->SetPos(mCurrentX, mCurrentY);
    te->GetWin()->SetB(id);
    kp = &id;
  } else {
    te->GetWin()->SetPos(mCurrentX, 0.0f);
    pid = parent->GetID();
    te->GetWin()->SetB(pid);
    kp = &pid;
  }
  mPropToTextEditMap[*kp] = te;
  te->GetWin()->V36();
  te->GetWin()->SetA(id);
  mCurrentX += kSpin80;
  float r2[4] = {0.0f, 0.0f, kRect2W, kRect2H};
  b1->GetWin()->SetArea(r2);
  b2->GetWin()->SetArea(r2);
  b1->GetWin()->SetHash(0xaf14b67e);
  b2->GetWin()->SetHash(0xaf14b67e);
  b1->GetWin()->SetText(kBtnTextA);
  b2->GetWin()->SetText(kBtnTextB);
  b1->GetWin()->SetA(0);
  b1->GetWin()->SetB(mSpinnerButtonID);
  mSpinnerToTextEditMap[mSpinnerButtonID] = te;
  ++mSpinnerButtonID;
  b2->GetWin()->SetA(0);
  b2->GetWin()->SetB(mSpinnerButtonID);
  mSpinnerToTextEditMap[mSpinnerButtonID] = te;
  ++mSpinnerButtonID;
  b1->GetWin()->SetPos(kSpin80, 0.0f);
  b2->GetWin()->SetPos(kSpin80, kBtn2Y);
  mCurrentX += kAdv30;
  mTextEdit.push_back(te);
  mButton.push_back(b1);
  mButton.push_back(b2);
  parent->AddChild(mTextEdit.b[idx]->GetWin());
  mTextEdit.b[idx]->GetWin()->AddChild(mButton.b[n0]->GetWin());
  mTextEdit.b[idx]->GetWin()->AddChild(mButton.b[n1]->GetWin());
  te->Release();
  b2->Release();
  b1->Release();
  return idx;
}



// @ 0x00825fc0
unsigned cPropertyUI_s0082_5930::AddTextEditRowA(unsigned id, const void* text, IWinW* parent)
{
  unsigned idx = (mTextEdit.b == mTextEdit.e) ? 0 : (unsigned)(mTextEdit.e - mTextEdit.b);
  void* mem = AllocAligned(0x658, 8, kTextEditName, GetAllocator());
  WinTextEdit* w = mem ? ((WinTextEditMem*)mem)->Construct() : 0;
  ITE* te = w ? (ITE*)((char*)w + 0x20c) : 0;
  if (te) te->AddRef();
  float r1[4] = {0.0f, 0.0f, kEditW, kEditH};
  te->GetWin()->SetArea(r1);
  te->SetColor(0, 0xff000000);
  te->SetColor(1, 0xffffffff);
  te->SetColor(2, 0xff777777);
  te->SetColor(3, 0xffffffff);
  te->SetColor(4, 0xffffffff);
  te->SetColor(5, 0xff43a2ff);
  te->SetColor(6, 0xff000000);
  te->SetColor(7, 0xff000000);
  te->V6(kStyleStr);
  te->GetWin()->SetText(text);
  te->V12(kQuarter);
  te->V37(0, 0);
  te->V17(0x54, 1);
  te->V16(0);
  te->V48(10);
  te->GetWin()->V36();
  te->GetWin()->SetA(id);
  if (parent == mHolderWindow.p) {
    te->GetWin()->SetPos(mCurrentX, mCurrentY);
  } else {
    te->GetWin()->SetPos(mCurrentX, 0.0f);
    id = parent->GetID();
  }
  te->GetWin()->SetB(id);
  mPropToTextEditMap[id] = te;
  mTextEdit.push_back(te);
  mCurrentX += kRowAdvance;
  parent->AddChild(mTextEdit.b[idx]->GetWin());
  te->Release();
  return idx;
}



// @ 0x00826290
unsigned cPropertyUI_s0082_5930::AddTextEditRowB(unsigned id, const void* text, IWinW* parent)
{
  unsigned idx = mTextEdit.size();
  void* mem = AllocAligned(0x658, 8, kTextEditName, GetAllocator());
  WinTextEdit* w = mem ? ((WinTextEditMem*)mem)->Construct() : 0;
  ITE* te = w ? (ITE*)((char*)w + 0x20c) : 0;
  if (te) te->AddRef();
  float r1[4] = {0.0f, 0.0f, kEditW, kEditH};
  te->GetWin()->SetArea(r1);
  te->SetColor(0, 0xff000000);
  te->SetColor(1, 0xffffffff);
  te->SetColor(2, 0xff777777);
  te->SetColor(3, 0xffffffff);
  te->SetColor(4, 0xffffffff);
  te->SetColor(5, 0xff43a2ff);
  te->SetColor(6, 0xff000000);
  te->SetColor(7, 0xff000000);
  te->V6(kStyleStr);
  te->V12(kQuarter);
  te->V37(0, 0);
  te->GetWin()->SetText(text);
  te->V17(0x54, 1);
  te->V16(0);
  te->V48(10);
  te->GetWin()->SetA(id);
  te->GetWin()->V36();
  mTextEdit.push_back(te);
  if (parent == mHolderWindow.p) {
    te->GetWin()->SetPos(mCurrentX, mCurrentY);
  } else {
    te->GetWin()->SetPos(mCurrentX, 0.0f);
    id = parent->GetID();
  }
  te->GetWin()->SetB(id);
  mPropToTextEditMap[id] = te;
  mCurrentX += kRowAdvance;
  parent->AddChild(mTextEdit.b[idx]->GetWin());
  te->Release();
  return idx;
}



// @ 0x00826560
cPropertyUI_s0082_5930::~cPropertyUI_s0082_5930()
{
  if (mEditorDialog.p) mEditorDialog = 0;
  if (mScrollbar.p) mScrollbar = 0;
  if (mHolderWindow.p) mHolderWindow = 0;
  if (mChooserDialog.p) mChooserDialog = 0;
  if (mTitleText.p) mTitleText = 0;
  ClearAll();
  if (mGroupsGrid.p) {
    mGroupsGrid.p->V91();
    mGroupsGrid = 0;
  }
  if (mPropsGrid.p) {
    mPropsGrid.p->V91();
    mPropsGrid = 0;
  }
  if (mSpinnerToTextEditMap.count) mSpinnerToTextEditMap.clear();
  if (mPropToTextEditMap.count) mPropToTextEditMap.clear();
  if (mPropToToggleButtonMap.count) mPropToToggleButtonMap.clear();
}


// @ 0x00826960
namespace SP {
void cPropertyUI_s0082_6960::LoadPropFile(uint32_t groupID, uint32_t instanceID, bool refresh)
{
    mCurrentGroupID = groupID;
    mCurrentInstanceID = instanceID;
    ClearWindows();
    mSpinnerButtonID = 0;

    intrusive_ptr<cPropertyList_s0082_6960> propList;
    UIntVector ids;
    Vector2 vector2;
    Vector3 vector3;
    Vector4 vector4;
    ColorRGB_s0082_6960 colorRGB;
    ColorRGBA_s0082_6960 colorRGBA;
    cPropertyManager_s0082_6960* propManager = PropertyManager_s0082_6960();
    propList.reset();
    propManager->GetPropertyList(instanceID, groupID, propList);

    mPropToTextEditMap.clear();
    mSpinnerToTextEditMap.clear();
    mPropToToggleButtonMap.clear();

    if (propList) {
        propList->GetPropertyIDs(ids);
        if (!ids.empty()) {
            int count = ids.size();
            for (int i = 0; i < count; i++) {
                const wchar_t* name = propManager->GetPropertyName(ids[i]);
                Property* prop = propList->GetPropertyObject(ids[i]);
                uint16_t type = prop->mnType;

                if (type == kTypeBool_s0082_6960) {
                    if (*prop->GetValueBoolUnchecked())
                        AddBool(ids[i], true, mHolderWindow);
                    else
                        AddBool(ids[i], false, mHolderWindow);
                    AddLabel(name);
                    NewLine();
                } else if (type == kTypeInt32_s0082_6960) {
                    AddLabel(name);
                    AddInt(ids[i], *prop->GetValueInt32(), mHolderWindow);
                    NewLine();
                } else if (type == kTypeUInt32_s0082_6960) {
                    AddLabel(name);
                    AddInt(ids[i], *prop->GetValueUInt32(), mHolderWindow);
                    NewLine();
                } else if (type == kTypeFloat_s0082_6960) {
                    AddLabel(name);
                    AddFloat(ids[i], *prop->GetValueFloat(), mHolderWindow);
                    NewLine();
                } else if (type == kTypeString8_s0082_6960) {
                    AddLabel(name);
                    AddString(ids[i], EA::ConvertToString16(*prop->GetValueString8()).c_str(), mHolderWindow);
                    NewLine();
                } else if (type == kTypeString16_s0082_6960) {
                    AddLabel(name);
                    AddString(ids[i], prop->GetValueString16()->c_str(), mHolderWindow);
                    NewLine();
                } else if (type == kTypeKey_s0082_6960) {
                    EA::ResourceMan::IResourceManager_s0082_6960* resourceManager = EA::ResourceMan::GetManager();
                    const ResourceKey_s0082_6960* key = prop->GetValueKey();
                    string16 keyName;
                    resourceManager->GetFileName(*key, keyName);
                    AddLabel(name);
                    AddKey(ids[i], keyName.c_str(), mHolderWindow);
                    NewLine();
                } else if (type == kTypeVector2_s0082_6960) {
                    vector2 = *prop->GetValueVector2();
                    AddLabel(name);
                    NewLine();
                    int window = AddSubWindow(ids[i]);
                    AddFloat(1, vector2.x, mSubWindows[window]);
                    AddFloat(2, vector2.y, mSubWindows[window]);
                    NewLine();
                } else if (type == kTypeVector3_s0082_6960) {
                    vector3 = *prop->GetValueVector3();
                    AddLabel(name);
                    NewLine();
                    int window = AddSubWindow(ids[i]);
                    AddFloat(1, vector3.x, mSubWindows[window]);
                    AddFloat(2, vector3.y, mSubWindows[window]);
                    AddFloat(3, vector3.z, mSubWindows[window]);
                    NewLine();
                } else if (type == kTypeVector4_s0082_6960) {
                    vector4 = *prop->GetValueVector4();
                    AddLabel(name);
                    NewLine();
                    int window = AddSubWindow(ids[i]);
                    AddFloat(1, vector4.x, mSubWindows[window]);
                    AddFloat(2, vector4.y, mSubWindows[window]);
                    AddFloat(2, vector4.z, mSubWindows[window]);  // sic: the original passes 2 twice
                    AddFloat(4, vector4.w, mSubWindows[window]);
                    NewLine();
                } else if (type == kTypeColorRGB_s0082_6960) {
                    colorRGB = *prop->GetValueColorRGB();
                    AddLabel(name);
                    NewLine();
                    int window = AddSubWindow(ids[i]);
                    AddFloat(1, colorRGB.r, mSubWindows[window]);
                    AddFloat(2, colorRGB.g, mSubWindows[window]);
                    AddFloat(3, colorRGB.b, mSubWindows[window]);
                    NewLine();
                } else if (type == kTypeColorRGBA_s0082_6960) {
                    colorRGBA = *prop->GetValueColorRGBA();
                    AddLabel(name);
                    NewLine();
                    int window = AddSubWindow(ids[i]);
                    AddFloat(1, colorRGBA.r, mSubWindows[window]);
                    AddFloat(2, colorRGBA.g, mSubWindows[window]);
                    AddFloat(3, colorRGBA.b, mSubWindows[window]);
                    AddFloat(4, colorRGBA.a, mSubWindows[window]);
                    NewLine();
                } else if (type == (kTypeArray_s0082_6960 | kTypeBool_s0082_6960)) {
                    int n = prop->GetItemCount();
                    const bool* values = (const bool*)prop->GetValue();
                    AddLabel(name);
                    NewLine();
                    int window = AddSubWindow(ids[i]);
                    for (int j = 0; j < n; j++) {
                        if (values[j])
                            AddBool(j + 1, true, mSubWindows[window]);
                        else
                            AddBool(j + 1, false, mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray_s0082_6960 | kTypeInt32_s0082_6960)) {
                    int n = prop->GetItemCount();
                    const int* values = (const int*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        AddInt(j + 1, values[j], mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray_s0082_6960 | kTypeUInt32_s0082_6960)) {
                    int n = prop->GetItemCount();
                    const uint32_t* values = (const uint32_t*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        AddInt(j + 1, values[j], mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray_s0082_6960 | kTypeFloat_s0082_6960)) {
                    int n = prop->GetItemCount();
                    const float* values = (const float*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        AddFloat(j + 1, values[j], mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray_s0082_6960 | kTypeString8_s0082_6960)) {
                    int n = prop->GetItemCount();
                    const string8* values = (const string8*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        AddString(j + 1, EA::ConvertToString16(values[j]).c_str(), mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray_s0082_6960 | kTypeString16_s0082_6960)) {
                    int n = prop->GetItemCount();
                    const string16* values = (const string16*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        AddString(j + 1, values[j].c_str(), mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray_s0082_6960 | kTypeKey_s0082_6960)) {
                    EA::ResourceMan::IResourceManager_s0082_6960* resourceManager = EA::ResourceMan::GetManager();
                    int n = prop->GetItemCount();
                    const ResourceKey_s0082_6960* values = (const ResourceKey_s0082_6960*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    string16 keyName;
                    for (int j = 0; j < n; j++) {
                        resourceManager->GetFileName(values[j], keyName);
                        AddKey(j + 1, keyName.c_str(), mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray_s0082_6960 | kTypeVector2_s0082_6960)) {
                    int n = prop->GetItemCount();
                    const Vector2* values = (const Vector2*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        vector2 = values[j];
                        AddFloat(j + 1, vector2.x, mSubWindows[window]);
                        AddFloat(j + 2, vector2.y, mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray_s0082_6960 | kTypeVector3_s0082_6960)) {
                    int n = prop->GetItemCount();
                    const Vector3* values = (const Vector3*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        vector3 = values[j];
                        AddFloat(j + 1, vector3.x, mSubWindows[window]);
                        AddFloat(j + 2, vector3.y, mSubWindows[window]);
                        AddFloat(j + 3, vector3.z, mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray_s0082_6960 | kTypeVector4_s0082_6960)) {
                    int n = prop->GetItemCount();
                    const Vector4* values = (const Vector4*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        vector4 = values[j];
                        AddFloat(j + 1, vector4.x, mSubWindows[window]);
                        AddFloat(j + 2, vector4.y, mSubWindows[window]);
                        AddFloat(j + 3, vector4.z, mSubWindows[window]);
                        AddFloat(j + 4, vector4.w, mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray_s0082_6960 | kTypeColorRGB_s0082_6960)) {
                    int n = prop->GetItemCount();
                    const Vector3* values = (const Vector3*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        vector3 = values[j];
                        AddFloat(j + 1, vector3.x, mSubWindows[window]);
                        AddFloat(j + 2, vector3.y, mSubWindows[window]);
                        AddFloat(j + 3, vector3.z, mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray_s0082_6960 | kTypeColorRGBA_s0082_6960)) {
                    int n = prop->GetItemCount();
                    const Vector4* values = (const Vector4*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        vector4 = values[j];
                        AddFloat(j + 1, vector4.x, mSubWindows[window]);
                        AddFloat(j + 2, vector4.y, mSubWindows[window]);
                        AddFloat(j + 3, vector4.z, mSubWindows[window]);
                        AddFloat(j + 4, vector4.w, mSubWindows[window]);
                        NewLine();
                    }
                }
            }

            mScrollRatio = mCurrentY / mScrollHeight;
            if (mScrollRatio > 1.0f) {
                float maxValue = (float)mScrollbar->GetMaxValue() / mScrollRatio;
                int newMax = RoundToInt(maxValue);
                mScrollbar->SetMaxValue(newMax, 1);
            }
            if (refresh) {
                float value = mRefreshScrollVal;
                mScrollbar->SetValue(RoundToInt(value), 1);
            }
            UpdateLayout();
        }
    }
}
}  // namespace SP

// @ 0x00b5f950
EA::AutoRefCount_s00b5_f040<EA::UTFWinControls::IWinText_s00b5_f040>& EA::AutoRefCount_s00b5_f040<EA::UTFWinControls::IWinText_s00b5_f040>::operator=(UTFWinControls::IWinText_s00b5_f040* p)
{
    UTFWinControls::IWinText_s00b5_f040* old = mpObject;
    if (p != old) {
        if (p != 0)
            p->AddRef();
        mpObject = p;
        if (old != 0)
            old->Release();
    }
    return *this;
}
