// src/game/SPEditors/SPPaletteItemRollover.cpp -- migrated from slice(s) s005ecf80 by tools/migrate/rewrite.py
// Object file: SPEditors/SPPaletteItemRollover.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// Declaration-only base view. No object or vtable is emitted here.
class cSPUIPropertyLayout {
 public:
  virtual bool Shutdown();  // 0x00828be0; ECX receiver, AL result, no stack arguments.
};

// ---- items of slice s005ecf80 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cSPPaletteItemRollover_s005e_cf80 {
 public:
  char pad00[0x1c];
  int mField1c;   // +0x1c
  int mField20;   // +0x20
  char pad24[0x78 - 0x24];
  void* mField78;  // +0x78
  char pad7c[0xb0 - 0x7c];
  void* mFieldB0;  // +0xb0
  void* mFieldB4;  // +0xb4
  bool mFieldB8;   // +0xb8
  char padB9[3];
  float mFieldBc;  // +0xbc

  void AddBox(int arg);
  void GetAreaPair(int* out);
  void ResetRollover();
  void ShutdownRollover();
  bool Shutdown();
};  // namespace SP
}
// ---- items of slice s005ecf80 end

// @ 0x005ed360
namespace SP {
void cSPPaletteItemRolloverCtor(cSPPaletteItemRollover_s005e_cf80* self, bool flag)
{
  (void)self;
  (void)flag;
}
}  // namespace SP

// @ 0x005ed420
namespace SP {
void cSPPaletteItemRolloverInit(cSPPaletteItemRollover_s005e_cf80* self)
{ (void)self; }
}  // namespace SP

// @ 0x005ed650
namespace SP {
bool cSPPaletteItemRollover_s005e_cf80::Shutdown()
{
  if (mField78 != 0) {
    if (((void* (__thiscall*)(void*))(*(void***)mField78)[4])(mField78) != 0) {
      void* parent = ((void* (__thiscall*)(void*))(*(void***)mField78)[4])(mField78);
      ((void (__thiscall*)(void*, void*))(*(void***)parent)[55])(parent, mField78);
    }
  }
  mFieldB8 = true;
  if (mFieldB4 != 0) {
    void* previous = *(void* volatile*)&mFieldB4;
    if (previous != 0) {
      mFieldB4 = 0;
      ((int (__thiscall*)(void*))(*(void***)previous)[2])(previous);
    }
  }
  return ((cSPUIPropertyLayout*)this)->cSPUIPropertyLayout::Shutdown();
}
}  // namespace SP

// @ 0x005ed700
namespace SP {
void cSPPaletteItemRolloverDtor(cSPPaletteItemRollover_s005e_cf80* self, unsigned int flags)
{
  (void)self;
  (void)flags;
}
}  // namespace SP
