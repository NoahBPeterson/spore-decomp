// slice s006960f0 — SP locale manager (cLocaleManager), App::cLocaleChangeMessage and the
// eastl::fixed_string<wchar_t,16,1> helpers they use.
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"
#include <intrin.h>

void* operator new(size_t n, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete(void* p);

namespace eastl {

struct allocator {
  void deallocate(void* p) { ::operator delete(p); }
  void* allocate(size_t n, const char* pName, int flags, unsigned debugFlags, const char* file, int line) {
    return ::operator new(n, pName, flags, debugFlags, file, line);
  }
};
typedef unsigned int size_type;

// ---------------------------------------------------------------------------------------------
// eastl::basic_string<wchar_t, fixed_vector_allocator<2,16,2,0,1>> — the base of fixed_string.
// Layout: 0 mpBegin, 4 mpEnd, 8 mpCapacity, 0xc empty overflow allocator, 0x10 mpPoolBegin.
struct FixedStringBase {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  allocator mOverflowAllocator;
  void* mpPoolBegin;

  FixedStringBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  FixedStringBase(void* pool) : mpBegin(0), mpEnd(0), mpCapacity(0) { mpPoolBegin = pool; }
  FixedStringBase& append(const wchar_t* pBegin, const wchar_t* pEnd);  // 0x68cc10

  void clear() {
    if (mpBegin != mpEnd) {
      *mpBegin = 0;
      mpEnd = mpBegin;
    }
  }
  void DeallocateSelf() {
    if ((((size_t)((char*)mpCapacity - (char*)mpBegin)) & ~(size_t)1) > 2) {
      if (mpPoolBegin != mpBegin) mOverflowAllocator.deallocate(mpBegin);
    }
  }
  ~FixedStringBase() { DeallocateSelf(); }
};

inline size_t CharStrlenW(const wchar_t* p) {
  const wchar_t* q = p;
  while (*q) ++q;
  return (size_t)(q - p);
}

// eastl::fixed_string<wchar_t,16,1>: 0x34 bytes, inline buffer at +0x14 (16 wchar_t).
struct FixedString16 : FixedStringBase {
  union {
    wchar_t mArray[1];
    char mBuffer[32];
  };

  FixedString16(const wchar_t* p);
  FixedString16(const FixedString16& x);
  FixedString16& operator=(const FixedString16& x);
};

// @ 0x006962a0
FixedString16::FixedString16(const wchar_t* p) : FixedStringBase(mBuffer) {
  mpBegin = mpEnd = mArray;
  mpCapacity = mpBegin + 16;
  *mpBegin = 0;
  append(p, p + CharStrlenW(p));
}

// @ 0x00696230
FixedString16::FixedString16(const FixedString16& x) : FixedStringBase(mBuffer) {
  mpBegin = mpEnd = mArray;
  mpCapacity = mpBegin + 16;
  *mpBegin = 0;
  append(x.mpBegin, x.mpEnd);
}

// @ 0x00696320
FixedString16& FixedString16::operator=(const FixedString16& x) {
  if (this != &x) {
    clear();
    append(x.mpBegin, x.mpEnd);
  }
  return *this;
}

}  // namespace eastl

namespace EA {
struct AtomicInt {
  int mValue;
  AtomicInt() { _InterlockedExchange((long*)&mValue, 0); }
};
template <typename T>
struct RefCountVTemplate {
  virtual ~RefCountVTemplate() {}
  T mRefCount;
  RefCountVTemplate() : mRefCount() {}
};
namespace Messaging {
struct IMessageRC {
  virtual ~IMessageRC() {}
};
}  // namespace Messaging
namespace Allocator {
class ICoreAllocator {
 public:
  static ICoreAllocator* GetDefaultAllocator();  // 0x925cb0
};
}  // namespace Allocator
}  // namespace EA

namespace App {
using eastl::FixedString16;

// vtables 0x013eb918 / 0x013f65b4 (base), 0x01403d6c / 0x01403d5c (derived).
// Layout: 0 IMessageRC vftable, 4 RefCountVTemplate vftable + 8 mRefCount, 0xc mLocaleId.
class cLocaleChangeMessage : public EA::Messaging::IMessageRC, public EA::RefCountVTemplate<EA::AtomicInt> {
 public:
  FixedString16 mLocaleId;  // +0xc
  cLocaleChangeMessage(const FixedString16& id);
};

// @ 0x00696350
cLocaleChangeMessage::cLocaleChangeMessage(const FixedString16& id) : mLocaleId(id) {}

// Forces cl to emit the compiler-generated scalar deleting destructor (??_G).
void DestroyLocaleChangeMessage(cLocaleChangeMessage* p) { delete p; }

}  // namespace App

namespace SP {
using eastl::FixedString16;

struct List16 {
  void* mNext;
  void* mPrev;
  void* mAlloc;
  void* mZero;
};

class cLocaleManager;
class cStringManager;

// cLocaleManager layout (retail): 0 vftable, 4 mRefCount, 8 mbInit, 9 field9, 0xa fieldA,
// 0xc fieldC, 0x10 field10(2), 0x14 field14(2), 0x18 mLocaleId, 0x4c mpStringManager,
// 0x50 list50, 0x60 list60.
extern "C" cLocaleManager* g_localeManagerDummy;
class cLocaleManager : public EA::RefCountVTemplate<int> {
 public:
  bool mbInit;             // +8
  bool field9;             // +9
  bool fieldA;             // +0xa
  char padB;               // +0xb
  int fieldC;              // +0xc
  int field10;             // +0x10
  int field14;             // +0x14
  FixedString16 mLocaleId;  // +0x18
  void* mpStringManager;   // +0x4c
  List16 mList50;          // +0x50
  List16 mList60;          // +0x60

  cLocaleManager();

  virtual bool ApplyLocaleId(const FixedString16& id) { return mbInit; }  // vtable +0x10
  bool Init(void* pCommandLine, void* pUnknown);         // 0x6964c0
  bool SetFromMatch(const FixedString16& id);            // 0x6968f0
  const wchar_t* FindMatchingLocale();                   // 0x6969b0
};

// @ 0x00696420
cLocaleManager::cLocaleManager()
    : mbInit(false), field9(false), fieldA(false), fieldC(0), field10(2), field14(2),
      mLocaleId(L"**-**") {
  mpStringManager = 0;
  mList50.mAlloc = EA::Allocator::ICoreAllocator::GetDefaultAllocator();
  mList50.mZero = 0;
  mList50.mNext = &mList50;
  mList50.mPrev = &mList50;
  mList60.mAlloc = EA::Allocator::ICoreAllocator::GetDefaultAllocator();
  mList60.mZero = 0;
  mList60.mNext = &mList60;
  mList60.mPrev = &mList60;
}

// The two range-comparison tables used by the locale matchers.
extern const wchar_t* g_localeNames[24];   // 0x152d6c8
extern const wchar_t* g_localeCodes[24];   // 0x152d6cc

int LocaleCommonPrefix(const wchar_t* a, const wchar_t* b);  // 0x695c70

// @ 0x006964c0 (partial: skeleton; full locale/registry bootstrap not reconstructed)
bool cLocaleManager::Init(void* pCommandLine, void* pUnknown) {
  (void)pCommandLine;
  (void)pUnknown;
  return mbInit;
}

// @ 0x006968f0 (partial: skeleton)
bool cLocaleManager::SetFromMatch(const FixedString16& id) {
  int best = 0;
  int bestScore = 0;
  for (int i = 0; i < 24; ++i) {
    int score = LocaleCommonPrefix(id.mpBegin, g_localeNames[i]);
    if (bestScore < score) {
      best = i;
      bestScore = score;
    }
  }
  FixedString16 code(g_localeCodes[best]);
  return ApplyLocaleId(code);
}

// @ 0x006969b0 (partial: skeleton)
const wchar_t* cLocaleManager::FindMatchingLocale() {
  for (int i = 0; i < 24; ++i) {
    FixedString16 code(g_localeCodes[i]);
    if (ApplyLocaleId(code)) return g_localeNames[i];
  }
  return 0;
}

}  // namespace SP

// ---------------------------------------------------------------------------------------------
// @ 0x006960f0 (partial: skeleton) — resource-list broadcast used by the paint system.
namespace EA {
namespace ResourceMan {
void* GetManager();  // 0x67dcd0
}
}  // namespace EA

extern "C" int __stdcall LocaleBroadcast(const wchar_t* name, void** list) {
  (void)name;
  (void)list;
  return 0;
}

// @ 0x00696a60 (partial: skeleton) — language-string resolution.
extern "C" bool __stdcall LocaleResolveLanguage(const void* pArg) {
  (void)pArg;
  return false;
}
