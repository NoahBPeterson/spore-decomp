// src/game/SPEditors/SPEditorsTokenTranslator.cpp -- migrated from slice(s) s005d53e0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorsTokenTranslator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cStringTokenTranslator.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p);                       // 0x00f47380
#include <new>
#include <math.h>
#include "SP/cEditorsTokenTranslator.h"

// ---- items of slice s005d53e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
class string16_s005d_53e0 {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  int mAllocator;
  string16_s005d_53e0(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
  ~string16_s005d_53e0() {
    if (((mpCapacity - mpBegin) > 1) && mpBegin)
      EASTL_allocator_deallocate(mpBegin);
  }
  void RangeInitialize(const wchar_t* p);         // 0x00579a90
  string16_s005d_53e0& operator=(const string16_s005d_53e0& x);         // 0x0057cb60
  string16_s005d_53e0& operator=(const wchar_t* p);          // 0x005c3d90
  string16_s005d_53e0& assign(const wchar_t* first, const wchar_t* last);  // 0x00423650
  string16_s005d_53e0& assign(const wchar_t* p) {
    const wchar_t* end = p;
    while (*end)
      ++end;
    return assign(p, p + (end - p));
  }
};  // namespace eastl
}
namespace EA {
namespace Hash {
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int caseMode);  // 0x00932f30
}
}
namespace EA {
namespace Locale {
int SetNumberString(double value, wchar_t* buffer, int bufferSize, int flags);  // 0x00881ea0
}
}
namespace SP {
class cStringTokenTranslator_s005d_53e0 {
 public:
  cStringTokenTranslator_s005d_53e0();           // 0x006b5870
  virtual ~cStringTokenTranslator_s005d_53e0();  // 0x005725a0
  virtual int AddRef();
  virtual int Release();
  virtual bool TranslateToken(const wchar_t* token, eastl::string16_s005d_53e0& result);
  int mRefCount;
};
}
namespace SP {
class cEditorsTokenTranslator_s005d_53e0 : public cStringTokenTranslator_s005d_53e0 {
 public:
  cEditorsTokenTranslator_s005d_53e0();
  virtual ~cEditorsTokenTranslator_s005d_53e0();
  virtual bool TranslateToken(const wchar_t* token, eastl::string16_s005d_53e0& result);  // 0x005d5ef0 (SP::cEditorsTokenTranslator::TranslateToken)

  unsigned int mAmount;               // +0x8
  eastl::string16_s005d_53e0 mOldModelName;      // +0xc
  eastl::string16_s005d_53e0 mNewModelName;      // +0x1c
  const wchar_t* mUserName;           // +0x2c
  const wchar_t* mYear;               // +0x30
  const wchar_t* mMonth;              // +0x34
  const wchar_t* mDayOfMonth;         // +0x38
  const wchar_t* mTime;               // +0x3c
};
}
// ---- items of slice s005d53e0 end

// @ 0x005d5ef0
namespace SP {
bool cEditorsTokenTranslator_s005d_53e0::TranslateToken(const wchar_t* token, eastl::string16_s005d_53e0& result)
{
  switch (EA::Hash::FNV1_String16(token, 0x811c9dc5, 1)) {
    case 0x37f56d0a:
      result = mOldModelName;
      return true;
    case 0xe736e65:
      result = mMonth;
      return true;
    case 0x540e2100:
      result.assign(mTime);
      return true;
    case 0xda3ea6ed:
      result = mNewModelName;
      return true;
    case 0xc534734a:
      result = mYear;
      return true;
    case 0xe7d52113:
      result = mDayOfMonth;
      return true;
    case 0xed0db5e3:
      result = mUserName;
      return true;
    case 0xef91ad29: {
      result = L"";
      wchar_t buffer[64];
      EA::Locale::SetNumberString((double)mAmount, buffer, 64, 0);
      buffer[63] = 0;
      result = buffer;
      return true;
    }
  }
  return false;
}
}  // namespace SP
