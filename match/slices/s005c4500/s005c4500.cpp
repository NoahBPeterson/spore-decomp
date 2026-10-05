// Slice s005c4500 -- SP::cSPPaletteCategoryUI methods (Spore UI)
// Flags for this region: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {

class cSPPalette {
 public:
  void Detach();  // FUN_005c8cc0
};

struct PaletteRef {
  cSPPalette* p;
  void* q;
};

struct PaletteVec {
  PaletteRef* mpBegin;
  PaletteRef* mpEnd;
  PaletteRef* mpCapacity;
  void erase(PaletteRef* first, PaletteRef* last);  // FUN_005c4330
};

class cSPPaletteCategoryUI {
 public:
  char pad0[0x88];
  PaletteVec mPalettes;  // +0x88
  char pad94[0xa0 - 0x94];
  int mUnkA0;  // +0xa0

  // @ 0x005c4df0
  void ClearPalettes();
};

// @ 0x005c4df0
void cSPPaletteCategoryUI::ClearPalettes() {
  PaletteVec& v = mPalettes;
  int count = (int)(v.mpEnd - v.mpBegin);
  for (int i = 0; i < count; i++)
    v.mpBegin[i].p->Detach();
  v.erase(v.mpBegin, v.mpEnd);
  mUnkA0 = 0;
}

}  // namespace SP

// @ 0x005c4500 -- PARTIAL (PopulateExpansionPackPane)
void FUN_005c4500() {}
// @ 0x005c4e40 -- PARTIAL (Shutdown)
void FUN_005c4e40() {}
// @ 0x005c50b0 -- PARTIAL
void FUN_005c50b0() {}
// @ 0x005c51e0 -- PARTIAL
void FUN_005c51e0() {}
