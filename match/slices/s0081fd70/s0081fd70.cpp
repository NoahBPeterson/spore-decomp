// Slice s0081fd70 -- SP::cPropertyUI property-modify overloads / Value helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ===========================================================================
// 00820b50 / 00820b80  Value-holder (EA::Variant-like) constructors.
//   Stored order matters: the type-id store is scheduled before the flag store,
//   which makes cl put 0x12/0x13 in eax and 0xb in ecx.
// ===========================================================================
struct VariantCtor12 {
  void* m0;                 // +0x0
  char pad0[0xc];           // +0x4
  unsigned short mFlags;    // +0x10
  unsigned short mTypeId;   // +0x12
  VariantCtor12(int v);
  void Set(int, int, int, int, int);
};

VariantCtor12::VariantCtor12(int v) {
  mTypeId = 0x12;
  mFlags = 0xb;
  Set(0x12, 9, v, 0x10, 1);
}

struct VariantCtor13 {
  void* m0;                 // +0x0
  char pad0[0xc];           // +0x4
  unsigned short mFlags;    // +0x10
  unsigned short mTypeId;   // +0x12
  VariantCtor13(int v);
  void Set(int, int, int, int, int);
};

VariantCtor13::VariantCtor13(int v) {
  mTypeId = 0x13;
  mFlags = 0xb;
  Set(0x13, 9, v, 0x10, 1);
}


// ===========================================================================
// 0x00820bb0  eastl::vector<T*, sp_vector_allocator>::DoInsertValue
// ===========================================================================
#include <string.h>
void* __cdecl EASTL_allocator_allocate(size_t n, const char* name, int flags, int a, const char* file, int line);
#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380

struct PtrVec {
  void** mpBegin;
  void** mpEnd;
  void** mpCapacity;
  void DoInsertValue(void** position, void* const& value);
};

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

// ===========================================================================
// SP::cPropertyUI::ModifyVec4 / ModifyRGB / ModifyRGBA  (0x81fd70 / 0x820210 / 0x820680)
//   Read the control rows of one property row window (children carry control IDs 1..N, each a
//   text edit) back into an N-float value and write it to the PropertyList of the current
//   instance. With bArray set, the value is written through the pointer held by the existing
//   (array) property instead of replacing it. Declarations are shared with s008220e0.
// ===========================================================================
extern wchar_t gEmptyString16[2];  // 0x01667bac
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

struct Variant {
  unsigned mData[4];
  unsigned short mFlags;  // +0x10
  unsigned short mType;   // +0x12
  Variant() {}
  ~Variant() {
    if (mFlags & 4) Destruct(0);
  }
  void Destruct(int);                                                       // 0x0093db80
  bool Set(int type, int flags, const void* p, unsigned size, unsigned n);  // 0x0093dd80
  Variant& operator=(const Variant& x);                                     // 0x00542b80
  Variant& Assign(Vector4* p);                                              // 0x0081dc60
  Variant& AssignArrayRGB(ColorRGB* p);                                     // 0x0081db80
  Variant& AssignArrayRGBA(ColorRGBA* p);                                   // 0x0081dbf0
  Variant& AssignArray(ColorRGB* p) { return AssignArrayRGB(p); }
  Variant& AssignArray(ColorRGBA* p) { return AssignArrayRGBA(p); }
};
struct VariantPtr : Variant {  // 0x0081e690
  VariantPtr(Vector4* p) {
    mType = 0;
    mFlags = 0;
    Assign(p);
  }
};
template <int kType> struct VariantConv : Variant {
  VariantConv(const Variant& v) {
    mFlags = 2;
    mType = kType;
    Variant::operator=(v);
  }
};
template <int kType, class T> struct VariantT16 : Variant {  // 0x0081ddd0 / 0x0081de30
  VariantT16(const T& v) {
    mFlags = 2;
    mType = kType;
    Set(kType, 0, &v, 0x10, 1);
  }
};
struct VariantRGB : Variant {  // ColorRGB stored inline (typed setter 0x006a3610 inlined)
  VariantRGB(const ColorRGB& v) {
    ColorRGB* d = (ColorRGB*)mData;
    *d = v;
    mFlags = 2;
    mType = kTypeColorRGB;
  }
};
template <int kType, class T> struct VariantArr : Variant {
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
extern int gWindowListNodeOffset;  // 0x01440aec
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
  virtual void SetProperty(unsigned id, const Variant& v);  // slot 5
  virtual void l6(); virtual void l7(); virtual void l8(); virtual void l9();
  virtual Variant* GetProperty(unsigned id);  // slot 10
};
struct IPropManager {
  virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
  virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
  virtual void m8(); virtual void m9(); virtual void m10();
  virtual bool GetPropertyList(unsigned instanceID, unsigned groupID, PropertyList** out);  // slot 11
};
namespace SP { IPropManager* PropertyManager(); }  // 0x0067de30

// Variant::GetValue (inlined): by-pointer variants hold the address, others the object itself.
static inline void* VariantValue(Variant* v) {
  if (v->mFlags & 0x30) return *(void**)v->mData;
  return v->mType ? (void*)v : 0;
}

namespace SP {
class cPropertyUI {
 public:
  unsigned mPad0[3];
  unsigned mCurrentGroupID;     // +0xc
  unsigned mCurrentInstanceID;  // +0x10
  void ReloadPropResource();    // 0x0081e230
  void ModifyVec4(IWindow* window, bool bArray);   // 0x0081fd70
  void ModifyRGB(IWindow* window, bool bArray);    // 0x00820210
  void ModifyRGBA(IWindow* window, bool bArray);   // 0x00820680
};

// @ 0x0081fd70
void cPropertyUI::ModifyVec4(IWindow* window, bool bArray) {
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

// @ 0x00820210
void cPropertyUI::ModifyRGB(IWindow* window, bool bArray) {
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

// @ 0x00820680
void cPropertyUI::ModifyRGBA(IWindow* window, bool bArray) {
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
// --- equivalence checker address annotations
    void operator delete(void*); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
