// Slice s005c53c0 -- SP::cSPPaletteCategoryUI / SP::cSPPalette methods (Spore UI)
// Flags for this region: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {

class cSPPaletteCategory;

class cSPPaletteCategoryUI {
 public:
  char pad0[0xc];
  cSPPaletteCategory** mBegin;  // +0xc
  cSPPaletteCategory** mEnd;    // +0x10

  // @ 0x005c5c20
  void ShutdownChildren();
  // @ 0x005c5df0
  cSPPaletteCategory* FindCategory(int id);
};

class cSPPaletteCategory {
 public:
  char pad0[0x74];
  int mId;  // +0x74
  void Shutdown();                              // FUN_005c2230
  cSPPaletteCategory* FindSubCategory(int id);  // FUN_005c1d70
};

// @ 0x005c5c20
void cSPPaletteCategoryUI::ShutdownChildren() {
  int count = (int)(mEnd - mBegin);
  for (int i = 0; i < count; i++)
    mBegin[i]->Shutdown();
}

// @ 0x005c5df0
cSPPaletteCategory* cSPPaletteCategoryUI::FindCategory(int id) {
  cSPPaletteCategory** end = mEnd;
  for (cSPPaletteCategory** it = mBegin; it != end; ++it) {
    cSPPaletteCategory* c = *it;
    if (c->mId == id)
      return c;
    cSPPaletteCategory* r = c->FindSubCategory(id);
    if (r)
      return r;
  }
  return 0;
}

}  // namespace SP

// @ 0x005c53c0 -- PARTIAL (Init)
void FUN_005c53c0() {}
// @ 0x005c5c50 -- PARTIAL
void FUN_005c5c50() {}
// @ 0x005c5cc0 -- PARTIAL
void FUN_005c5cc0() {}
// @ 0x005c5e30 -- PARTIAL
void FUN_005c5e30() {}
// @ 0x005c5e90 -- PARTIAL
void FUN_005c5e90() {}
// @ 0x005c5f00 -- PARTIAL
void FUN_005c5f00() {}
// @ 0x005c6010 -- PARTIAL (cSPPalette::LoadDefinitionPart)
void FUN_005c6010() {}
