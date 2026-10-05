// Slice s005e4db0: mostly SP::cSPEditorVerbIconData / cSPCreatureVerbIconData.
// Retail layout recovered from the constructor at 0x005e5a70 (PDB offsets differ).
#include "types.h"

#define PV(n) virtual void _pv##n();

namespace Math {
struct Rectangle {
  float x1, y1, x2, y2;
  float Width() const { return x2 - x1; }
  float Height() const { return y2 - y1; }
};
}  // namespace Math

extern "C" void EASTL_allocator_deallocate(void* p);
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);

namespace eastl {
union EmptyString {
  uint32_t mUint32;
  wchar_t mEmpty16[1];
};
extern EmptyString gEmptyString;

struct allocator {
  allocator() {}
};

class wstring {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  allocator mAllocator;
  wstring() { AllocateSelf(); }
  void AllocateSelf() {
    mpBegin = gEmptyString.mEmpty16;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1)
      EASTL_allocator_deallocate(mpBegin);
  }
  void assign(const wchar_t* b, const wchar_t* e);
  ~wstring() { DeallocateSelf(); }
};
}  // namespace eastl

void WStr_Format(eastl::wstring* out, const wchar_t* format, ...);

class cString {
 public:
  cString();
  cString(uint32_t a, uint32_t b, const wchar_t* c);
  ~cString();
  const wchar_t* GetText() const;
  uint32_t mData[5];
};

namespace EA {
template <typename T>
class RefCountVTemplate {
 public:
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};

namespace COM {
class IUnknown32 {
 public:
  virtual int AddRef();
  virtual int Release();
};
}  // namespace COM
}  // namespace EA

namespace SP {
// Refcounted payload stored at cSPCreatureVerbIconData::mData (+0xc4).
class cRefObj {
 public:
  virtual void Release(int value);
  int mRefCount;
};

class cSPEditorVerbIconData : public EA::COM::IUnknown32, public EA::RefCountVTemplate<int> {
 public:
  cSPEditorVerbIconData();
  virtual ~cSPEditorVerbIconData();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  bool mUseDescription;  // +0x0c
  bool mShowLevel;       // +0x0d
  bool mShowHotKey;      // +0x0e
  bool mShowZeroLevel;   // +0x0f
  bool mField10;         // +0x10
  bool mField11;         // +0x11
  short mPad12;          // +0x12
  int mField14;          // +0x14
  float mMaxLevel;       // +0x18
  float mType;           // +0x1c
  uint32_t mPad20;       // +0x20
  uint32_t mPad24;       // +0x24
  int mField28;          // +0x28
  uint32_t mPad2c[5];    // +0x2c..0x3f
  int mField40;          // +0x40
  int mField44;          // +0x44
  int mField48;          // +0x48
  uint32_t mField4c;     // +0x4c
  uint32_t mPad50;       // +0x50
  cString mName;         // +0x54..0x67
  eastl::wstring mHotKeyString;  // +0x68..0x77
  uint32_t mHotKeyID;    // +0x78
  int mField7c;          // +0x7c
  int mField80;          // +0x80
  uint32_t mPad84;       // +0x84
  uint32_t mPad88;       // +0x88
  uint32_t mPad8c;       // +0x8c
  uint32_t mPad90;       // +0x90
  uint32_t mPad94;       // +0x94
  uint32_t mPad98;       // +0x98
  uint32_t mPad9c;       // +0x9c
  uint32_t mPadA0;       // +0xa0
  uint32_t mPadA4;       // +0xa4
  uint32_t mPadA8;       // +0xa8
  uint32_t mPadAc;       // +0xac
  uint32_t mPadB0;       // +0xb0
  uint32_t mPadB4;       // +0xb4
  uint32_t mPadB8;       // +0xb8
  uint32_t mPadBc;       // +0xbc
  uint32_t mPadC0;       // +0xc0
  void Init(uint32_t level);
  void SetHotKey(uint32_t key);
  eastl::wstring GetIconName(bool withLevel);
};

class cSPCreatureVerbIconData : public cSPEditorVerbIconData {
 public:
  cSPCreatureVerbIconData();
  virtual ~cSPCreatureVerbIconData();
  cRefObj* mData;  // +0xc4
  int mFieldC8;    // +0xc8
  void Init(uint32_t type, cSPCreatureVerbIconData* data);
  void ReleaseData();
};

// @ 0x005e5910
void cSPCreatureVerbIconData::ReleaseData() {
  cRefObj* object = mData;
  if (object) {
    mData = 0;
    if ((object->mRefCount += -1) == 0) {
      object->mRefCount = 1;
      object->Release(1);
    }
  }
}

// @ 0x005e5b60
cSPCreatureVerbIconData::cSPCreatureVerbIconData() : mData(0), mFieldC8(-1) {}

// @ 0x005e5ba0
cSPCreatureVerbIconData::~cSPCreatureVerbIconData() {
  cRefObj* object = mData;
  if (object) {
    if ((object->mRefCount += -1) == 0) {
      object->mRefCount = 1;
      object->Release(1);
    }
  }
}

// @ 0x005e5a70
cSPEditorVerbIconData::cSPEditorVerbIconData() {
  mUseDescription = true;
  mShowLevel = true;
  mShowHotKey = true;
  mShowZeroLevel = true;
  mField10 = false;
  mField11 = false;
  mField14 = -2;
  mMaxLevel = 0.0f;
  mType = 5.0f;
  mField28 = -1;
  mField40 = 0;
  mField44 = 0;
  mField48 = 0;
  mField4c = 0;
  mHotKeyID = 0;
  mField7c = -1;
  mField80 = -1;
}

// @ 0x005e5470
void cSPEditorVerbIconData::Init(uint32_t level) {
  (void)level;
}

// @ 0x005e4db0
float GetLevelForType(uint32_t type, uint32_t index) {
  (void)type;
  (void)index;
  return 0.0f;
}

// @ 0x005e5950
void cSPCreatureVerbIconData::Init(uint32_t type, cSPCreatureVerbIconData* data) {
  (void)type;
  (void)data;
}

// @ 0x005e5c00
void cSPEditorVerbIconData::SetHotKey(uint32_t key) {
  mHotKeyID = key;
  cString first(0x841536d5, key, L"<Key>");
  cString second(0xd1726890, 0x4dacd21, L"<Key>");
  WStr_Format(&mHotKeyString, L"%ls: %ls", second.GetText(), first.GetText());
}

// @ 0x005e5c80
eastl::wstring cSPEditorVerbIconData::GetIconName(bool withLevel) {
  eastl::wstring result;
  cString label(0xd1726890, 0x4ace6b0, L"Level");
  if (!withLevel) {
    const wchar_t* text = mName.GetText();
    const wchar_t* end = text;
    while (*end)
      ++end;
    result.assign(text, end);
  } else {
    WStr_Format(&result, L"%ls - %ls %d", label.GetText(), mName.GetText(), (int)mMaxLevel);
  }
  return result;
}
}  // namespace SP
