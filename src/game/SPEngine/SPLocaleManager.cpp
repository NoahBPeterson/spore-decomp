// src/game/SPEngine/SPLocaleManager.cpp -- migrated from slice(s) s00696c80, s006960f0, s00695140 by tools/migrate/rewrite.py
// Object file: SPEngine/SPLocaleManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* GetManager();         // 0x67dcd0
#include <wchar.h>
#include "EA/Allocator/ICoreAllocator.h"
#include <intrin.h>
#include "EA/Thread/Mutex.h"
#include "EA/Trace/Server.h"
#include <string.h>

// ---- items of slice s00695140 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VFN(o,off) (*(void***)(o))[(off)/4]
extern "C" void* GetManager();         // 0x67dcd0
struct Ctl {
    char pad0[4];
    void* head;      // +4
    bool check(void* arg);
    void addThing(void* a, void* b);
};
// ---- items of slice s00695140 end

// ---- items of slice s006960f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(size_t n, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete(void* p);
namespace eastl {
struct allocator_s0069_60f0 {
  void deallocate(void* p) { ::operator delete(p); }
  void* allocate(size_t n, const char* pName, int flags, unsigned debugFlags, const char* file, int line) {
    return ::operator new(n, pName, flags, debugFlags, file, line);
  }
};
}
namespace eastl {
struct FixedStringBase {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  allocator_s0069_60f0 mOverflowAllocator;
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
}
namespace eastl {
struct FixedString16 : FixedStringBase {
  union {
    wchar_t mArray[1];
    char mBuffer[32];
  };

  FixedString16(const wchar_t* p);
  FixedString16(const FixedString16& x);
  FixedString16& operator=(const FixedString16& x);
};
}
namespace EA {
template <typename T>
struct RefCountVTemplate_s0069_60f0 {
  virtual ~RefCountVTemplate_s0069_60f0() {}
  T mRefCount;
  RefCountVTemplate_s0069_60f0() : mRefCount() {}
};
}
namespace EA {
namespace Allocator {
class ICoreAllocator_s0069_60f0 {
 public:
  static ICoreAllocator_s0069_60f0* GetDefaultAllocator();  // 0x925cb0
};  // namespace Allocator
}
}
namespace App {
using eastl::FixedString16;
}
namespace SP {
using eastl::FixedString16;
}
namespace SP {
struct List16 {
  void* mNext;
  void* mPrev;
  void* mAlloc;
  void* mZero;
};
}
namespace SP {
class cLocaleManager;
}
namespace SP {
class cLocaleManager : public EA::RefCountVTemplate_s0069_60f0<int> {
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
}
namespace SP {
extern const wchar_t* g_localeNames[24];   // 0x152d6c8
}
namespace SP {
extern const wchar_t* g_localeCodes[24];   // 0x152d6cc
}
namespace SP {
int LocaleCommonPrefix(const wchar_t* a, const wchar_t* b);  // 0x695c70
}
// ---- items of slice s006960f0 end

// @ 0x00695c70
extern "C" int FUN_00695c70(const wchar_t* a, const wchar_t* b)
{
    int i = 0;
    if (a[0] != 0)
    {
        do
        {
            if (b[i] == 0)
                break;
            if ((wint_t)towlower(a[i]) != (wint_t)towlower(b[i]))
                break;
            ++i;
        } while (a[i] != 0);
    }
    return i;
}

// @ 0x00695cd0
extern "C" int __fastcall FUN_00695cd0(void* self)
{
    if (*(void**)((char*)self + 0x4c) != 0)
        return ((int(__thiscall*)(void*))VFN(*(void**)((char*)self + 0x4c), 0x10))
                   (*(void**)((char*)self + 0x4c));
    return 0;
}

// @ 0x00695d10
void Ctl::addThing(void* a, void* b)
{
    void* m = GetManager();
    bool ok = ((bool(__thiscall*)(void*, void*, void*, int, int, int, int))VFN(m, 0xc))
                  (m, a, b, 0, 0, 0, 0);
    if (!ok)
    {
        char* end = (char*)this + 0x60;
        void* n = *(void**)((char*)this + 0x60);
        while (n != end && !ok)
        {
            m = GetManager();
            ok = ((bool(__thiscall*)(void*, void*, void*, int, void*, int, int))VFN(m, 0xc))
                     (m, a, b, 0, *(void**)((char*)n + 8), 0, 0);
            n = *(void**)n;
        }
    }
}

// @ 0x00696420
namespace SP {
cLocaleManager::cLocaleManager()
: mbInit(false), field9(false), fieldA(false), fieldC(0), field10(2), field14(2),
      mLocaleId(L"**-**") {
  mpStringManager = 0;
  mList50.mAlloc = EA::Allocator::ICoreAllocator_s0069_60f0::GetDefaultAllocator();
  mList50.mZero = 0;
  mList50.mNext = &mList50;
  mList50.mPrev = &mList50;
  mList60.mAlloc = EA::Allocator::ICoreAllocator_s0069_60f0::GetDefaultAllocator();
  mList60.mZero = 0;
  mList60.mNext = &mList60;
  mList60.mPrev = &mList60;
}
}  // namespace SP

// @ 0x006964c0
namespace SP {
bool cLocaleManager::Init(void* pCommandLine, void* pUnknown)
{
  (void)pCommandLine;
  (void)pUnknown;
  return mbInit;
}
}  // namespace SP

// @ 0x006968f0
namespace SP {
bool cLocaleManager::SetFromMatch(const FixedString16& id)
{
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
}  // namespace SP

// @ 0x006969b0
namespace SP {
const wchar_t* cLocaleManager::FindMatchingLocale()
{
  for (int i = 0; i < 24; ++i) {
    FixedString16 code(g_localeCodes[i]);
    if (ApplyLocaleId(code)) return g_localeNames[i];
  }
  return 0;
}
}  // namespace SP

// @ 0x00697710
namespace SP {
bool cLocaleManagerSetLocale(void* self, void* arg)
{
  (void)self;
  (void)arg;
  return true;
}
}  // namespace SP
