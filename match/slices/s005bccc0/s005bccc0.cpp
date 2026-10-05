// Slice s005bccc0 -- SP::cSPEditorManipulation* (Spore creature editor)
// Flags for this region: /O2 /MD /Gy /TP /arch:SSE /fp:fast

struct cSPEditorPileList { void* p0; void* p1; void* p2; };

namespace SP {

class cSPEditorManipulationSpineResize {
 public:
  char pad[0x78];
  // @ 0x005bdc80
  cSPEditorPileList GetPileList();
};

// @ 0x005bdc80
cSPEditorPileList cSPEditorManipulationSpineResize::GetPileList() {
  cSPEditorPileList v;
  v.p0 = 0;
  v.p1 = 0;
  v.p2 = 0;
  return v;
}

}  // namespace SP

// @ 0x005bccc0 -- PARTIAL (DoOnMouseMove, 2400 bytes)
void FUN_005bccc0() {}
// @ 0x005bd650 -- PARTIAL (TranslateCreature::OnMouseUp)
void FUN_005bd650() {}
// @ 0x005bd750 -- PARTIAL (setter)
void FUN_005bd750() {}
// @ 0x005bd7c0 -- PARTIAL (TranslateCreature::PickPlaneOfSymmetry)
void FUN_005bd7c0() {}
// @ 0x005bdad0 -- PARTIAL (dtor)
void FUN_005bdad0() {}
// @ 0x005bdb60 -- PARTIAL (rbtree insert helper)
void FUN_005bdb60() {}
