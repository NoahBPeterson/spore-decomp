// src/game/SPGonzago/SPGonzagoDebug.cpp -- migrated from slice(s) s0061d240 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGonzagoDebug.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/CustomWinProc.h"
#include "EA/UTFWin/ISerializable.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/MultiHeapObject.h"
#include "SP/cPollinator.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "SP/cStringTokenTranslator.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" unsigned int __cdecl strlen(const char*);
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(strlen)
#pragma intrinsic(memmove)

// ---- items of slice s0061d240 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
namespace SP {
namespace Pollen {
struct String8 {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  void* mAllocator;
  String8* erase(unsigned int position, unsigned int n);
};
}
}
// ---- items of slice s0061d240 end

// @ 0x0061e200
namespace SP { namespace Pollen {
String8* String8::erase(unsigned int position, unsigned int n)
{
  unsigned int nRemaining = (unsigned int)(mpEnd - mpBegin) - position;
  if (n > nRemaining) n = nRemaining;
  char* pDst = mpBegin + position;
  char* pSrc = pDst + n;
  if (pDst != pSrc) {
    memmove(pDst, pSrc, (mpEnd - pSrc) + 1);
    mpEnd = (char*)mpEnd + (pDst - pSrc);
  }
  return this;
}
}}  // namespace SP::Pollen
