// Slice s006b27f0: SP save-area registration / teardown.
// Compiled with /O2 /MD /Gy /EHsc /TP /GS-.
#include "s006b27f0.h"

// @ 0x6b2aa0
void SaveMap5::Nuke(RBNode5* n) {
  while (n != 0) {
    Nuke(n->left);
    RBNode5* right = n->right;
    if (n->val.b != 0) {
      n->val.b->Release();
    }
    if (n->val.a != 0) {
      n->val.a->ref.Release();
    }
    EFree5(n);
    n = right;
  }
}

// @ 0x6b3610
void FUN_006b3610() {
  for (uint32_t* it = (uint32_t*)g_m5.root; it != &g_m5.head;
       it = (uint32_t*)RBTreeIncrement(it)) {
    ((SaveObj5*)it[5])->Call1c();
    ((SaveObj5*)it[5])->Call08();
  }
  g_m5.Nuke((RBNode5*)g_m5.nukep);
  g_m5.head = (uint32_t)&g_m5.head;
  g_m5.root = (uint32_t)&g_m5.head;
  g_m5.nukep = 0;
  *(uint8_t*)&g_m5.f10 = 0;
  g_m5.f14 = 0;
}

// @ 0x6b27f0  (partial)
void SP_cAppSystem_CreateHTTPServer() {}

// @ 0x6b2b30  (partial)
void OpenPreCommitFile() {}

// @ 0x6b2dc0  (partial)
void SP_CreateCachedDirectorySave() {}

// @ 0x6b3050  (partial)
void cDirectoriesCheat_Execute() {}

// @ 0x6b3240  (partial)
void SP_CreatePackageSave() {}

// @ 0x6b3430  (partial)
void SP_CreateLocationSave() {}

// @ 0x6b3680  (partial)
void MapIndexOp6() {}

// @ 0x6b3760  (partial)
void SP_RegisterSaveArea() {}
