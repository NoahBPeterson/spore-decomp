// src/game/SPEditors/SPEditorVerbTrayCollection.cpp -- migrated from slice(s) s005e8470 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorVerbTrayCollection.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "eastl/allocator.h"
#include "SP/cSPEditorVerbTrayCollection.h"
#include "cSPUILayout.h"
#include "SP/cSPVerbTrayCollection.h"
#include <string.h>
#include <ctype.h>
#include "EA/RectT.h"
#include "EA/UTFWin/IWindow.h"

// ---- items of slice s005e8470 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
struct rbtree_node_base_s005e_8470 {
  rbtree_node_base_s005e_8470* mpNodeRight;
  rbtree_node_base_s005e_8470* mpNodeLeft;
  rbtree_node_base_s005e_8470* mpNodeParent;
  char mColor;
};
}
namespace EA {
namespace ResourceMan {
struct Key_s005e_8470 { uint32_t instance, type, group; };
}
}
namespace SP {
class cSPVerbTrayCollection_s005e_8470 {
 public:
  void InitTrays(EA::ResourceMan::Key_s005e_8470 key, int a, int b);  // 0x00605f90
  void FUN_00605980(int a, EA::ResourceMan::Key_s005e_8470 key, int b, int c, int d);
};
}
namespace SP {
class cSPEditorVerbTrayCollection_s005e_8470 : public cSPVerbTrayCollection_s005e_8470 {
 public:
  void Init(EA::ResourceMan::Key_s005e_8470 key, int a, int b);
  void FUN_005e8940(int a, EA::ResourceMan::Key_s005e_8470 key, int b, int c, int d);
  void LayoutCollection();  // 0x005e89f0 (SP::cSPEditorVerbTrayCollection::LayoutCollection)
  char pad00[0x28];
  char mCompare[4];                   // +0x28 (mWindowsToVerbTrays)
  eastl::rbtree_node_base_s005e_8470 mAnchor;    // +0x2c
  unsigned int mnSize;                // +0x3c
  char pad40[4];
  uint32_t mLayoutStyle;              // +0x44
  char pad48[4];
  uint32_t mJustification;            // +0x4c
};
}
// ---- items of slice s005e8470 end

// @ 0x005e8940
namespace SP {
void cSPEditorVerbTrayCollection_s005e_8470::FUN_005e8940(int a, EA::ResourceMan::Key_s005e_8470 key, int b, int c, int d)
{ FUN_00605980(a, key, b, c, d); }
}  // namespace SP

// @ 0x005e8980
namespace SP {
void cSPEditorVerbTrayCollection_s005e_8470::Init(EA::ResourceMan::Key_s005e_8470 key, int a, int b)
{ InitTrays(key, a, b); }
}  // namespace SP
