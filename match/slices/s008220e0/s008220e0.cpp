// Slice s008220e0 -- SP::cPropertyUI::SavePropFile.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (UI module: no /EHsc, AutoRefCount locals get no EH frame)
//
// SavePropFile walks the children of mHolderWindow (one row window per property; its control ID is
// the property ID), reads each row's control(s) back (button state, text-edit text, or the text of
// each child text edit for vector/color rows) and writes the value into the instance's
// PropertyList, then writes the list with the resource manager and reloads it.
// App::Property is written here as EA::Variant (the retail names of its helpers).
// Retail cPropertyUI layout: see s00825930 (+0xc after mLayout vs the 2008 PDB).
#include "types.h"
#include <stdlib.h>
#include <stddef.h>

// ---------------------------------------------------------------- strings

extern wchar_t gEmptyString16[2];  // 0x01667bac (EASTL empty-string buffer)

struct EString16 {  // eastl::string16, 0x10 bytes
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
  EString16& operator=(const wchar_t* p);      // 0x005c3d90 (assign(p, p + wcslen(p)))
  EString16& operator=(const EString16& x);    // 0x0057cb60
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
EString8 ConvertToString8(const EString16& s);           // 0x0093c570
}

float ParseFloat(const wchar_t* s);  // 0x00671b80 (StrtodW wrapper, end pointer discarded)

// ---------------------------------------------------------------- math / keys

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Vector4 { float x, y, z, w; };
struct ColorRGB { float r, g, b; };
struct ColorRGBA { float r, g, b, a; };
struct ResourceKey {
  unsigned instanceID, typeID, groupID;
  ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
};
ResourceKey* SPKeyFromName(ResourceKey* out, const wchar_t* name, unsigned type, unsigned group);  // 0x0068d840

// ---------------------------------------------------------------- EA::Variant (App::Property)

enum {
  kTypeBool = 1, kTypeInt32 = 9, kTypeUInt32 = 0xa, kTypeFloat = 0xd, kTypeString8 = 0x12,
  kTypeString16 = 0x13, kTypeKey = 0x20, kTypeVector2 = 0x30, kTypeVector3 = 0x31,
  kTypeColorRGB = 0x32, kTypeVector4 = 0x33, kTypeColorRGBA = 0x34
};
static const unsigned kTypeArray = 0x80000000u;

struct Variant {  // 0x14 bytes
  unsigned mData[4];
  unsigned short mFlags;  // +0x10
  unsigned short mType;   // +0x12
  Variant() {}
  ~Variant() {
    if (mFlags & 4) Destruct(0);
  }
  void Destruct(int);                                                      // 0x0093db80
  bool Set(int type, int flags, const void* p, unsigned size, unsigned n);  // 0x0093dd80
  Variant& operator=(const Variant& x);                                    // 0x00542b80
  void* GetValue();                                                        // 0x00446ff0
  // typed setters (out of line in the binary)
  Variant& Assign(const bool& v);         // 0x00422e20
  Variant& Assign(const ResourceKey& v);  // 0x00422f40
  Variant& Assign(const Vector2& v);      // 0x006a3510
  Variant& Assign(const Vector3& v);      // 0x006a3570
  Variant& Assign(const ColorRGB& v);     // 0x006a3610
  Variant& Assign(Vector4* p);            // 0x0081dc60 (by reference, flag 0x20)
  Variant& AssignArray(bool* p);          // 0x0081d7a0
  Variant& AssignArray(int* p);           // 0x0081d800
  Variant& AssignArray(unsigned* p);      // 0x0081d870
  Variant& AssignArray(float* p);         // 0x0081d8e0
  Variant& AssignArray(EString8* p);      // 0x0081d950
  Variant& AssignArray(EString16* p);     // 0x0081d9c0
  Variant& AssignArray(ResourceKey* p);   // 0x0081da30
  Variant& AssignArray(Vector2* p);       // 0x0081daa0
  Variant& AssignArray(Vector3* p);       // 0x0081db10
  Variant& AssignArray(ColorRGB* p);      // 0x0081db80
  Variant& AssignArray(ColorRGBA* p);     // 0x0081dbf0
};

// Variant holding a string16 (0x005a74a0)
struct VariantString : Variant {
  VariantString(const EString16& s) {
    mType = 0;
    mFlags = 0;
    Set(kTypeString16, 9, &s, 0x10, 1);
  }
};
// Variant holding a Vector4 array by reference (0x0081e690)
struct VariantPtr : Variant {
  VariantPtr(Vector4* p) {
    mType = 0;
    mFlags = 0;
    Assign(p);
  }
};
// VariantT<T> converted from another Variant (0x0081e390 uint32, 0x006a1a10 float, 0x0081e510 Vector3)
template <int kType> struct VariantConv : Variant {
  VariantConv(const Variant& v) {
    mFlags = 2;
    mType = kType;
    Variant::operator=(v);
  }
};
// VariantT<T>(const T&) for the types with a typed setter
template <int kType, class T> struct VariantT : Variant {
  VariantT(const T& v) {
    mFlags = 2;
    mType = kType;
    Assign(v);
  }
};
// VariantT<T>(const T&) for the 16-byte types (0x0081ddd0 Vector4, 0x0081de30 ColorRGBA)
template <int kType, class T> struct VariantT16 : Variant {
  VariantT16(const T& v) {
    mFlags = 2;
    mType = kType;
    Set(kType, 0, &v, 0x10, 1);
  }
};
// VariantT<string> (0x00820b50 string8, 0x00820b80 string16)
template <int kType, class S> struct VariantStr : Variant {
  VariantStr(const S& s) {
    mFlags = 0xb;
    mType = kType;
    Set(kType, 9, &s, 0x10, 1);
  }
};
// VariantT<T*> array (0x0081e330 ... 0x0081e570)
template <int kType, class T> struct VariantArr : Variant {
  VariantArr(T* const& p) {
    mFlags = 2;
    mType = kType;
    AssignArray(p);
  }
};

// ---------------------------------------------------------------- UTFWin

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
struct ListNode {
  ListNode* mpNext;
};
extern int gWindowListNodeOffset;  // 0x01440aec: offset from a child-list node to its IWindow
struct ChildIterator {
  ListNode* mpNode;
  ChildIterator() {}
  ChildIterator(const ChildIterator& x) : mpNode(x.mpNode) {}
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
  virtual ChildIterator children_begin();  // slot 51
  virtual ChildIterator children_end();    // slot 52
};

struct IWinButton {
  enum { IID = 0x8ed27e7a };
  virtual int AddRef();
  virtual int Release();
  virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5();
  virtual void b6(); virtual void b7();
  virtual unsigned GetButtonStateFlags() const;  // slot 8
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

template <class T> inline T* interface_cast(const AutoRefCount<IWindow>& w) {  // 0x0081d780 / 0x005c2570
  return w.mpObject ? (T*)w.mpObject->Cast(T::IID) : 0;
}

// ---------------------------------------------------------------- property / resource managers

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

struct PropertyList {
  virtual int AddRef();
  virtual int Release();
  virtual void l2(); virtual void l3(); virtual void l4();
  virtual void SetProperty(unsigned id, const Variant& v);  // slot 5
  virtual void l6(); virtual void l7(); virtual void l8(); virtual void l9();
  virtual Variant* GetProperty(unsigned id);  // slot 10
  virtual void l11(); virtual void l12(); virtual void l13(); virtual void l14();
  virtual void l15(); virtual void l16();
  virtual void GetPropertyIDs(PropertyIDList& out);  // slot 17
};

struct IPropManager {
  virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
  virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
  virtual void m8(); virtual void m9(); virtual void m10();
  virtual bool GetPropertyList(unsigned instanceID, unsigned groupID, PropertyList** out);  // slot 11
};

struct IResourceManager {
  virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3();
  virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7();
  virtual bool WriteResource(PropertyList* res, int a, int b, int c, int d);  // slot 8
};

namespace SP {
IPropManager* PropertyManager();  // 0x0067de30
}
IResourceManager* ResourceManager();  // 0x008de1a0

// ---------------------------------------------------------------- cPropertyUI

namespace SP {
class cPropertyUI {
 public:
  unsigned mPad0[3];
  unsigned mCurrentGroupID;     // +0xc
  unsigned mCurrentInstanceID;  // +0x10
  unsigned mPad1[0x14];
  AutoRefCount<IWindow> mHolderWindow;  // +0x64

  void ReloadPropResource();  // 0x0081e230
  void SavePropFile();        // 0x008220e0
};
typedef char chk_holder[offsetof(cPropertyUI, mHolderWindow) == 0x64 ? 1 : -1];

// 0x008220e0  SP::cPropertyUI::SavePropFile
void cPropertyUI::SavePropFile() {
  AutoRefCount<PropertyList> propList;
  PropertyIDList ids;
  Vector2 v2;
  Vector3 v3;
  Vector4 v4;
  PropertyManager()->GetPropertyList(mCurrentInstanceID, mCurrentGroupID, propList.AsPPTypeParam());
  bool bValue = false;
  AutoRefCount<IWinButton> button;
  EString16 text;
  AutoRefCount<IWinTextEdit> textEdit;
  AutoRefCount<IWindow> window;
  AutoRefCount<IWinTextEdit> childTextEdit;
  AutoRefCount<IWindow> childWindow;

  if (propList) {
    propList->GetPropertyIDs(ids);
    if (!ids.empty()) {
      for (ChildIterator it = mHolderWindow->children_begin(); it != mHolderWindow->children_end(); ++it) {
        unsigned id = (*it)->GetControlID();
        if (!id) continue;
        Variant* prop = propList->GetProperty(id);
        unsigned short type = prop->mType;

        if (type == kTypeBool) {
          window = *it;
          button = interface_cast<IWinButton>(window);
          if (button->GetButtonStateFlags() & 4)
            bValue = true;
          else
            bValue = false;
          propList->SetProperty(id, VariantT<kTypeBool, bool>(bValue));
        } else if (type == kTypeInt32) {
          window = *it;
          textEdit = interface_cast<IWinTextEdit>(window);
          text = textEdit->GetText();
          propList->SetProperty(id, VariantConv<kTypeInt32>(VariantString(text)));
        } else if (type == kTypeUInt32) {
          window = *it;
          textEdit = interface_cast<IWinTextEdit>(window);
          text = textEdit->GetText();
          propList->SetProperty(id, VariantConv<kTypeUInt32>(VariantString(text)));
        } else if (type == kTypeFloat) {
          window = *it;
          textEdit = interface_cast<IWinTextEdit>(window);
          text = textEdit->GetText();
          propList->SetProperty(id, VariantConv<kTypeFloat>(VariantString(text)));
        } else if (type == kTypeString8) {
          window = *it;
          textEdit = interface_cast<IWinTextEdit>(window);
          text = textEdit->GetText();
          EString8 text8 = EA::ConvertToString8(text.c_str());
          propList->SetProperty(id, VariantStr<kTypeString8, EString8>(text8));
        } else if (type == kTypeString16) {
          window = *it;
          textEdit = interface_cast<IWinTextEdit>(window);
          text = textEdit->GetText();
          propList->SetProperty(id, VariantStr<kTypeString16, EString16>(text));
        } else if (type == kTypeKey) {
          window = *it;
          textEdit = interface_cast<IWinTextEdit>(window);
          text = textEdit->GetText();
          ResourceKey key;
          SPKeyFromName(&key, text.c_str(), 0, 0);
          propList->SetProperty(id, VariantT<kTypeKey, ResourceKey>(key));
        } else if (type == kTypeVector2) {
          window = *it;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            unsigned cid = (*c)->GetControlID();
            if (cid) {
              childWindow = *c;
              childTextEdit = interface_cast<IWinTextEdit>(childWindow);
              text = childTextEdit->GetText();
              (&v2.x)[cid - 1] = ParseFloat(text.c_str());
            }
          }
          propList->SetProperty(id, VariantT<kTypeVector2, Vector2>(v2));
        } else if (type == kTypeVector3) {
          window = *it;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            unsigned cid = (*c)->GetControlID();
            if (cid) {
              childWindow = *c;
              childTextEdit = interface_cast<IWinTextEdit>(childWindow);
              text = childTextEdit->GetText();
              (&v3.x)[cid - 1] = ParseFloat(text.c_str());
            }
          }
          propList->SetProperty(id, VariantT<kTypeVector3, Vector3>(v3));
        } else if (type == kTypeVector4) {
          window = *it;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            unsigned cid = (*c)->GetControlID();
            if (cid) {
              childWindow = *c;
              childTextEdit = interface_cast<IWinTextEdit>(childWindow);
              text = childTextEdit->GetText();
              (&v4.x)[cid - 1] = ParseFloat(text.c_str());
            }
          }
          propList->SetProperty(id, VariantT16<kTypeVector4, Vector4>(v4));
        } else if (type == kTypeColorRGB) {
          ColorRGB color;
          window = *it;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            unsigned cid = (*c)->GetControlID();
            if (cid) {
              childWindow = *c;
              childTextEdit = interface_cast<IWinTextEdit>(childWindow);
              text = childTextEdit->GetText();
              (&color.r)[cid - 1] = ParseFloat(text.c_str());
            }
          }
          propList->SetProperty(id, VariantT<kTypeColorRGB, ColorRGB>(color));
        } else if (type == kTypeColorRGBA) {
          ColorRGBA color;
          window = *it;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            unsigned cid = (*c)->GetControlID();
            if (cid) {
              childWindow = *c;
              childTextEdit = interface_cast<IWinTextEdit>(childWindow);
              text = childTextEdit->GetText();
              (&color.r)[cid - 1] = ParseFloat(text.c_str());
            }
          }
          propList->SetProperty(id, VariantT16<kTypeColorRGBA, ColorRGBA>(color));
        }
        // Array types: mType is 16 bits, so these never match at run time, but the
        // original compiled them (the compares are emitted after a movzx).
        else if (type == (kTypeArray | kTypeBool)) {
          window = *it;
          bool* pStart = (bool*)prop->GetValue();
          bool* p = pStart;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              button = interface_cast<IWinButton>(childWindow);
              *p++ = (button->GetButtonStateFlags() & 4) == 4;
            }
          }
          propList->SetProperty(id, VariantArr<kTypeBool, bool>(pStart));
        } else if (type == (kTypeArray | kTypeInt32)) {
          window = *it;
          int* pStart = (int*)prop->GetValue();
          int* p = pStart;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              *p++ = wcstol(text.c_str(), 0, 0);
            }
          }
          propList->SetProperty(id, VariantArr<kTypeInt32, int>(pStart));
        } else if (type == (kTypeArray | kTypeUInt32)) {
          window = *it;
          unsigned* pStart = (unsigned*)prop->GetValue();
          unsigned* p = pStart;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              *p++ = wcstoul(text.c_str(), 0, 0);
            }
          }
          propList->SetProperty(id, VariantArr<kTypeUInt32, unsigned>(pStart));
        } else if (type == (kTypeArray | kTypeFloat)) {
          window = *it;
          float* pStart = (float*)prop->GetValue();
          float* p = pStart;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              *p++ = ParseFloat(text.c_str());
            }
          }
          propList->SetProperty(id, VariantArr<kTypeFloat, float>(pStart));
        } else if (type == (kTypeArray | kTypeString8)) {
          window = *it;
          EString8* pStart = (EString8*)prop->GetValue();
          EString8* p = pStart;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              *p = EA::ConvertToString8(text);
              ++p;
            }
          }
          propList->SetProperty(id, VariantArr<kTypeString8, EString8>(pStart));
        } else if (type == (kTypeArray | kTypeString16)) {
          window = *it;
          EString16* pStart = (EString16*)prop->GetValue();
          EString16* p = pStart;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              *p = text;
              ++p;
            }
          }
          propList->SetProperty(id, VariantArr<kTypeString16, EString16>(pStart));
        } else if (type == (kTypeArray | kTypeKey)) {
          window = *it;
          ResourceKey* pStart = (ResourceKey*)prop->GetValue();
          ResourceKey* p = pStart;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              SPKeyFromName(p, text.c_str(), 0, 0);
              ++p;
            }
          }
          propList->SetProperty(id, VariantArr<kTypeKey, ResourceKey>(pStart));
        } else if (type == (kTypeArray | kTypeVector2)) {
          window = *it;
          int n = 0;
          Vector2* pStart = (Vector2*)prop->GetValue();
          Vector2* p = pStart;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              (&v2.x)[n] = ParseFloat(text.c_str());
              if (++n == 2) {
                *++p = v2;  // the original pre-increments: the first element is never written
                n = 0;
              }
            }
          }
          propList->SetProperty(id, VariantArr<kTypeVector2, Vector2>(pStart));
        } else if (type == (kTypeArray | kTypeVector3)) {
          window = *it;
          int n = 0;
          Vector3* pStart = (Vector3*)prop->GetValue();
          Vector3* p = pStart;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              (&v3.x)[n] = ParseFloat(text.c_str());
              if (++n == 3) {
                *++p = v3;
                n = 0;
              }
            }
          }
          propList->SetProperty(id, VariantArr<kTypeVector3, Vector3>(pStart));
        } else if (type == (kTypeArray | kTypeVector4)) {
          window = *it;
          int n = 0;
          Vector4* pStart = (Vector4*)prop->GetValue();
          Vector4* p = pStart;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              (&v4.x)[n] = ParseFloat(text.c_str());
              if (++n == 4) {
                *++p = v4;
                n = 0;
              }
            }
          }
          // The original wraps the Vector4 array by reference and converts it to a Vector3 property.
          propList->SetProperty(id, VariantConv<kTypeVector3>(VariantPtr(pStart)));
        } else if (type == (kTypeArray | kTypeColorRGB)) {
          window = *it;
          int n = 0;
          ColorRGB color;
          ColorRGB* pStart = (ColorRGB*)prop->GetValue();
          ColorRGB* p = pStart;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              (&color.r)[n] = ParseFloat(text.c_str());
              if (++n == 3) {
                *++p = color;
                n = 0;
              }
            }
          }
          propList->SetProperty(id, VariantArr<kTypeColorRGB, ColorRGB>(pStart));
        } else if (type == (kTypeArray | kTypeColorRGBA)) {
          window = *it;
          int n = 0;
          ColorRGBA color;
          ColorRGBA* pStart = (ColorRGBA*)prop->GetValue();
          ColorRGBA* p = pStart;
          for (ChildIterator c = window->children_begin(); c != window->children_end(); ++c) {
            if ((*c)->GetControlID()) {
              childWindow = *c;
              textEdit = interface_cast<IWinTextEdit>(childWindow);
              text = textEdit->GetText();
              (&color.r)[n] = ParseFloat(text.c_str());
              if (++n == 4) {
                *++p = color;
                n = 0;
              }
            }
          }
          propList->SetProperty(id, VariantArr<kTypeColorRGBA, ColorRGBA>(pStart));
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
