// Slice s0081f0e0 -- SP::cPropertyUI property-modify overloads (ResourceKey / Vec2 / Vec3).
// Flags (whole cluster): /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Read the control rows of one property row window back into a value and write it to the
// PropertyList of the current instance. With bArray set, the value is written through the pointer
// held by the existing (array) property. Declarations are shared with s0081fd70 / s008220e0.
#include "types.h"

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

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Vector4 { float x, y, z, w; };
struct ResourceKey {
  unsigned instanceID, typeID, groupID;
  ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
};
ResourceKey* SPKeyFromName(ResourceKey* out, const wchar_t* name, unsigned type, unsigned group);  // 0x0068d840
struct ColorRGB { float r, g, b; };
struct ColorRGBA { float r, g, b, a; };

enum { kTypeKey = 0x20, kTypeVector2 = 0x30, kTypeVector3 = 0x31, kTypeColorRGB = 0x32, kTypeVector4 = 0x33, kTypeColorRGBA = 0x34 };

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
  Variant& Assign(const ResourceKey& v);                                    // 0x00422f40
  Variant& AssignArrayVec2(Vector2* p);                                      // 0x0081daa0
  Variant& AssignArrayVec3(Vector3* p);                                      // 0x0081db10
  Variant& Assign(Vector4* p);                                              // 0x0081dc60
  Variant& AssignArrayRGB(ColorRGB* p);                                     // 0x0081db80
  Variant& AssignArrayRGBA(ColorRGBA* p);                                   // 0x0081dbf0
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
// Key array held by reference (Variant::Assign(Key*) inlined: pointer, element size 12, count 1)
struct VariantKeyPtr : Variant {
  VariantKeyPtr(ResourceKey* p) {
    mData[0] = (unsigned)p;
    mData[1] = 0xc;
    mData[2] = 1;
    mFlags = 0x22;
    mType = kTypeKey;
  }
};
// Plain value stored inline (typed setter inlined)
template <int kType, class T> struct VariantInline : Variant {
  VariantInline(const T& v) {
    *(T*)mData = v;
    mFlags = 2;
    mType = kType;
  }
};
struct VariantArrVec2 : Variant {
  VariantArrVec2(Vector2* const& p) {
    mFlags = 2;
    mType = kTypeVector2;
    AssignArrayVec2(p);
  }
};
struct VariantArrVec3 : Variant {
  VariantArrVec3(Vector3* const& p) {
    mFlags = 2;
    mType = kTypeVector3;
    AssignArrayVec3(p);
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
  void ModifyResourceKey(IWindow* window, bool bArray);  // 0x0081f0e0
  void ModifyVec2(IWindow* window, bool bArray);         // 0x0081f490
  void ModifyVec3(IWindow* window, bool bArray);         // 0x0081f900
};

// @ 0x0081f0e0
void cPropertyUI::ModifyResourceKey(IWindow* window, bool bArray) {
  AutoRefCount<PropertyList> propList;
  AutoRefCount<IWindow> childWindow;
  AutoRefCount<IWinTextEdit> textEdit;
  EString16 text;
  PropertyManager()->GetPropertyList(mCurrentInstanceID, mCurrentGroupID, propList.AsPPTypeParam());
  if (!bArray) {
    textEdit = window ? (IWinTextEdit*)window->Cast(IWinTextEdit::IID) : 0;
    text = textEdit->GetText();
    ResourceKey key;
    SPKeyFromName(&key, text.c_str(), 0, 0);
    propList->SetProperty(window->GetControlID(), VariantInline<kTypeKey, ResourceKey>(key));
  } else {
    ResourceKey* pValue = (ResourceKey*)VariantValue(propList->GetProperty(window->GetControlID()));
    ResourceKey* pCur = pValue;
    for (ChildIterator it = window->children_begin(); it != window->children_end(); ++it) {
      if ((*it)->GetControlID()) {
        childWindow = *it;
        textEdit = interface_cast<IWinTextEdit>(childWindow);
        text = textEdit->GetText();
        SPKeyFromName(pCur, text.c_str(), 0, 0);
        ++pCur;
      }
    }
    propList->SetProperty(window->GetControlID(), VariantKeyPtr(pValue));
    childWindow = 0;
  }
  textEdit = 0;
  ReloadPropResource();
}

// @ 0x0081f490
void cPropertyUI::ModifyVec2(IWindow* window, bool bArray) {
  AutoRefCount<PropertyList> propList;
  AutoRefCount<IWindow> childWindow;
  AutoRefCount<IWinTextEdit> textEdit;
  EString16 text;
  PropertyManager()->GetPropertyList(mCurrentInstanceID, mCurrentGroupID, propList.AsPPTypeParam());
  if (!bArray) {
    Vector2 v2;
    wchar_t* end;
    for (ChildIterator it = window->children_begin(); it != window->children_end(); ++it) {
      unsigned idx = (*it)->GetControlID();
      if (idx) {
        childWindow = *it;
        textEdit = interface_cast<IWinTextEdit>(childWindow);
        text = textEdit->GetText();
        (&v2.x)[idx - 1] = (float)StrtodW(text.c_str(), &end);
      }
    }
    propList->SetProperty(window->GetControlID(), VariantInline<kTypeVector2, Vector2>(v2));
  } else {
    Vector2* pValue = (Vector2*)VariantValue(propList->GetProperty(window->GetControlID()));
    Vector2* pCur = pValue;
    Vector2 v2;
    unsigned i = 0;
    wchar_t* end;
    for (ChildIterator it = window->children_begin(); it != window->children_end(); ++it) {
      if ((*it)->GetControlID()) {
        childWindow = *it;
        textEdit = interface_cast<IWinTextEdit>(childWindow);
        text = textEdit->GetText();
        (&v2.x)[i] = (float)StrtodW(text.c_str(), &end);
        ++i;
        if (i == 2) {
          ++pCur;
          *pCur = v2;
          i = 0;
        }
      }
    }
    propList->SetProperty(window->GetControlID(), VariantArrVec2(pValue));
  }
  childWindow = 0;
  textEdit = 0;
  ReloadPropResource();
}

// @ 0x0081f900
void cPropertyUI::ModifyVec3(IWindow* window, bool bArray) {
  AutoRefCount<PropertyList> propList;
  AutoRefCount<IWindow> childWindow;
  AutoRefCount<IWinTextEdit> textEdit;
  EString16 text;
  PropertyManager()->GetPropertyList(mCurrentInstanceID, mCurrentGroupID, propList.AsPPTypeParam());
  if (!bArray) {
    Vector3 v3;
    wchar_t* end;
    for (ChildIterator it = window->children_begin(); it != window->children_end(); ++it) {
      unsigned idx = (*it)->GetControlID();
      if (idx) {
        childWindow = *it;
        textEdit = interface_cast<IWinTextEdit>(childWindow);
        text = textEdit->GetText();
        (&v3.x)[idx - 1] = (float)StrtodW(text.c_str(), &end);
      }
    }
    propList->SetProperty(window->GetControlID(), VariantInline<kTypeVector3, Vector3>(v3));
  } else {
    Vector3* pValue = (Vector3*)VariantValue(propList->GetProperty(window->GetControlID()));
    Vector3* pCur = pValue;
    Vector3 v3;
    unsigned i = 0;
    wchar_t* end;
    for (ChildIterator it = window->children_begin(); it != window->children_end(); ++it) {
      if ((*it)->GetControlID()) {
        childWindow = *it;
        textEdit = interface_cast<IWinTextEdit>(childWindow);
        text = textEdit->GetText();
        (&v3.x)[i] = (float)StrtodW(text.c_str(), &end);
        ++i;
        if (i == 3) {
          ++pCur;
          *pCur = v3;
          i = 0;
        }
      }
    }
    propList->SetProperty(window->GetControlID(), VariantArrVec3(pValue));
  }
  childWindow = 0;
  textEdit = 0;
  ReloadPropResource();
}
}  // namespace SP
