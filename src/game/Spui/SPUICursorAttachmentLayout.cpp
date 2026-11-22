// src/game/Spui/SPUICursorAttachmentLayout.cpp -- migrated from slice(s) s007ffc70 by tools/migrate/rewrite.py
// Object file: Spui/SPUICursorAttachmentLayout.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUICursorAttachmentLayout.h"
#include "cSPUILayout.h"

// unnamed retail callees and globals (address in the comment)
extern char ca_a[], ca_b[], ca_c[];
extern char cl_a[], cl_b[], cl_c[], cl_d[];
#include <new>
#include <intrin.h>

// ---- items of slice s007ffc70 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cSPUILayout_s007f_fc70 { public:
  void* Ctor();                                   // 0x00810000
  void* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
  bool  Init(const wchar_t* name, int group, int b, unsigned id);   // 0x00812160
  void  SetVisibility(bool v);                    // 0x00810590
};
extern char ca_a[], ca_b[], ca_c[];
extern char cl_a[], cl_b[], cl_c[], cl_d[];
struct cSPUIPropertyLayoutBase { void BaseDtor(); };
struct C_8011f0 : cSPUIPropertyLayoutBase { void Dtor(); };
struct C_801210 { void* Thunk(); };
struct cSPUIPropertyLayoutCtor { void BaseCtor(); };
struct C_801280 : cSPUIPropertyLayoutCtor { void* Ctor(); };
// ---- items of slice s007ffc70 end

// @ 0x008011f0
void C_8011f0::Dtor()
{
  *(void**)this = (void*)ca_a;
  *(void**)((char*)this + 4) = (void*)ca_b;
  *(void**)((char*)this + 0x78) = (void*)ca_c;
  BaseDtor();
}

// @ 0x00801210
void* C_801210::Thunk()
{
  return ((cSPUILayout_s007f_fc70*)((char*)this - 0x6c))
      ->FindWindowByID(*(uint32_t*)((char*)this - 0x30), true);
}

// @ 0x00801280
void* C_801280::Ctor()
{
  BaseCtor();
  *(void* volatile*)((char*)this + 0x78) = (void*)cl_a;
  *(void* volatile*)this = (void*)cl_b;
  *(void* volatile*)((char*)this + 4) = (void*)cl_c;
  *(void* volatile*)((char*)this + 0x78) = (void*)cl_d;
  return this;
}
