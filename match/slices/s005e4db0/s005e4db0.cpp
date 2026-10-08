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

// Reads one creature-capability stat out of the stats block (+0x590..+0x6ac), keyed by the
// capability property id (FNV hash of "bite", "sprint", ...).  Counts are uint32 and converted to float.
struct CreatureStats {
  uint32_t w[0x6b0 / 4];
  float F(unsigned off) const { return *(const float*)&w[off / 4]; }
  float U(unsigned off) const { return (float)w[off / 4]; }
  float I(unsigned off) const { return (float)(int)w[off / 4]; }
};

// @ 0x005e4db0
float GetLevelForType(const CreatureStats* obj, int type) {
  switch (type) {
    case 0x93a8cfc8: return obj->F(0x640);
    case 0x99f85c5b: return obj->U(0x6a4);
    case 0x9e3f42cb: return obj->U(0x688);
    case 0xa09e2868: return obj->U(0x670);
    case 0xb0f439a4: return obj->U(0x61c);   // glide
    case 0xad68447a: return obj->U(0x5f4);   // stealth
    case 0xbe1409e9: return obj->U(0x638);
    case 0xb3ed313f: return obj->U(0x68c);
    case 0xc1e9f31c: return obj->U(0x634);
    case 0xcfa9bdb5: return obj->U(0x690);
    case 0xcaaf9176: return obj->U(0x65c);
    case 0xc3d98d60: return obj->U(0x680);
    case 0x2dfb4f9f: return -1.0f;
    case 0x31ccd0d2: return -1.0f;
    case 0x45a6f219: return -1.0f;
    case 0x57a3bd5a: return -1.0f;
    case 0x5f6fac4c: return -1.0f;
    case 0x811328b0: return -1.0f;
    case 0xa28a67e8: return -1.0f;
    case 0xb39f7db3: return -1.0f;
    case 0xb4074212: return -1.0f;
    case 0xd89d2d9e: return -1.0f;
    case 0xd9bcb9f0: return -1.0f;
    case 0xdfa0d6bf: return -1.0f;
    case 0x41a6ec56: return -1.0f;
    default: return -1.0f;
    case 0xdb2d51a3: return obj->U(0x604);   // health
    case 0xdfb699f5: return obj->U(0x5fc);   // call
    case 0xe480e089: return obj->U(0x610);   // jump
    case 0xe2654048: return obj->F(0x644);
    case 0xdfbb4a45: return obj->U(0x698);
    case 0xee8347b0: return obj->U(0x5f8);
    case 0xf2967c99: return obj->U(0x618);   // sense
    case 0xf1cb44c4: return obj->U(0x660);
    case 0xf01a9fc2: return obj->U(0x6ac);
    case 0xf502dd07: return obj->U(0x5e0);   // strike
    case 0x056b2e45: return obj->U(0x668);
    case 0xff6bafa5: return obj->U(0x5d8);   // charge
    case 0xfd3d2eda: return obj->F(0x590);   // grasp
    case 0x0ac4aeed: return obj->U(0x628);   // attack
    case 0x19e2694a: return obj->U(0x5ec);
    case 0x1765233b: return obj->U(0x64c);
    case 0x1c9ad396: return obj->U(0x684);
    case 0x1f0deaf6: return obj->U(0x6a0);
    case 0x2070fea8: return obj->U(0x664);
    case 0x27785bd2: return obj->U(0x630);   // armor
    case 0x26341ede: return obj->U(0x600);   // speed
    case 0x21d4870e: return obj->U(0x654);
    case 0x28ebaf02: return obj->F(0x66c);
    case 0x30e7f354: return obj->U(0x674);
    case 0x2ffeb19c: return obj->U(0x5e4);   // sing
    case 0x310ffcdb: return obj->U(0x5dc);   // spit
    case 0x39fc121d: return obj->U(0x650);
    case 0x42d64108: return obj->U(0x6a8);
    case 0x4d467cc1: return obj->U(0x614);   // sprint
    case 0x5577a531: return obj->I(0x648);
    case 0x5ec025c8: return obj->U(0x62c);   // social
    case 0x597bcd8d: return obj->U(0x694);
    case 0x66f29bd3: return obj->U(0x678);
    case 0x620d5edf: return obj->U(0x5d4);   // bite
    case 0x60e2831a: return obj->U(0x5f0);   // pose
    case 0x72b9fc4e: return obj->U(0x5e8);   // dance
    case 0x7c0badbe: return obj->U(0x69c);
    case 0x795819d8: return obj->U(0x658);
    case 0x752bd435: return obj->U(0x67c);
  }
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
