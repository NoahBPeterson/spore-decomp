// src/game/SPEditors/SPEditorShoppingTokenTranslator.cpp -- migrated from slice(s) s005cbfd0, s005ccc90 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorShoppingTokenTranslator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <new>
#include "EA/UTFWin/IWindow.h"
#include "SP/cSPEditorSellBackDetachedRollover.h"
#include "SP/cSPEditorSellBackRollover.h"
#include "SP/cSPEditorShoppingTokenTranslator.h"
#include "cSPUICursorAttachmentLayout.h"
#include "cSPUILayout.h"
#include "cSPUILayoutManager.h"
#include "SP/cStringTokenTranslator.h"
#include <intrin.h>

// ---- items of slice s005cbfd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern char    vtbl_013f8798[];
extern wchar_t g_01667bac[2];
class cStringTokenTranslator {
 public:
  cStringTokenTranslator();        // 0x006b5870
  ~cStringTokenTranslator();       // 0x005725a0
};
class cEAWString16 {
 public:
  __forceinline void InitializeEmpty() {
    mpBegin = g_01667bac; mpEnd = g_01667bac; mpCap = g_01667bac + 1;
  }
  void* mpBegin;                     // +0x00
  void* mpEnd;                       // +0x04
  void* mpCap;                       // +0x08
  void* mpAllocator;                 // +0x0c
  __forceinline void Initialize(const wchar_t* s) {
    mpBegin = 0; mpEnd = 0; mpCap = 0; range_initialize(s);
  }
  void range_initialize(const wchar_t* s);   // 0x00579a90
};
class cSPEditorShoppingTokenTranslator : public cStringTokenTranslator {
 public:
  void*        mpVftable;            // +0x00
  char         pad4[0x08 - 4];
  cEAWString16 mStr1;                // +0x08
  cEAWString16 mStr2;                // +0x18
  char         pad28[0x68 - 0x28];
  cEAWString16 mStr3;                // +0x68

  cSPEditorShoppingTokenTranslator();          // 0x005ccbb0
  ~cSPEditorShoppingTokenTranslator();         // 0x005ccc00
};
// ---- items of slice s005cbfd0 end

// @ 0x005ccbb0
cSPEditorShoppingTokenTranslator::cSPEditorShoppingTokenTranslator()
{
  mpVftable = vtbl_013f8798;
  mStr1.Initialize(L"UnsetName");
  mStr2.InitializeEmpty();
  mStr3.InitializeEmpty();
}

// @ 0x005ccc00
cSPEditorShoppingTokenTranslator::~cSPEditorShoppingTokenTranslator()
{
  mpVftable = vtbl_013f8798;
  _ReadWriteBarrier();
  if (((int)((char*)mStr3.mpCap - (char*)mStr3.mpBegin) & ~1) > 2 && mStr3.mpBegin)
    EASTL_allocator_deallocate(mStr3.mpBegin);
  if (((int)((char*)mStr2.mpCap - (char*)mStr2.mpBegin) & ~1) > 2 && mStr2.mpBegin)
    EASTL_allocator_deallocate(mStr2.mpBegin);
  if (((int)((char*)mStr1.mpCap - (char*)mStr1.mpBegin) & ~1) > 2 && mStr1.mpBegin)
    EASTL_allocator_deallocate(mStr1.mpBegin);
}

// @ 0x005ccc90
void TranslateTokenStub(void* a, void* b, void* c)
{
  (void)a;
  (void)b;
  (void)c;
}

// @ 0x005cd190
void GetDayOfWeekStringStub(int day, void* out)
{
  (void)day;
  (void)out;
}

// @ 0x005cd340
void GetTimeStringStub(void* a, void* b)
{
  (void)a;
  (void)b;
}
