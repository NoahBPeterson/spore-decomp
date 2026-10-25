// Slice-local retail declarations for s005aad00 (not shared with the other slices that include
// s005aad00.h: they spell these types themselves).  Only the members the retail code touches are named.
#ifndef SP_EDITOR_MANIP_S005AAD00_EXT_H
#define SP_EDITOR_MANIP_S005AAD00_EXT_H
#include "s005aad00.h"

namespace SP {

typedef eastl::sp_vector<EA::AutoRefCount<cSPEditorBlock> > BlockVector;

class cSPEditorModel {
 public:
  bool UsingSymmetry() const;   // 0x004adc40
};

class cMesh {
 public:
  virtual void Destroy(int flags);   // vtable slot 0
};

class Factory {
 public:
  cMesh* Make();   // 0x00523570
};

class cSPEditorSkinPart {
 public:
  char pad_0[0x34];
  Factory* mMesh;   // +0x34
};

class cSPEditorAnimatedEventInfo {
 public:
  cSPEditorAnimatedEventInfo();   // 0x0059d960
  virtual void v0();
  virtual int AddRef();
  virtual int Release();
  void MessagePost(uint32_t id, cSPEditorBlock* block, cSPEditorModel* model, int a, int b, float c,
                   int d, int e, float f);   // 0x0059d840
  char pad_4[0x2c];                          // sizeof == 0x30 (retail `new` size)
};
typedef char cSPEditorAnimatedEventInfo_size_check[sizeof(cSPEditorAnimatedEventInfo) == 0x30 ? 1 : -1];

class cUIHint {
 public:
  void Show();   // 0x0067c830
};
cUIHint* FindUIHint(uint32_t id);   // 0x0067cac0

class cViewer {
 public:
  void GetWorldRayFromScreenCoords(float x, float y, cSPVector3& origin, cSPVector3& dir);   // 0x007c4730
};
class cApp {
 public:
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
  virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21();
  virtual cViewer* GetViewer();   // +0x58
};
cApp* App();   // 0x0067dd10

namespace EditorUtils {
cSPMatrix3* FUN_49c210(cSPMatrix3* out, cSPEditorBlock* block, cSPVector3 normal);            // 0x0049c210
cSPEditorBlock* PickBlocks(BlockVector* ignore, cSPVector3 origin, cSPVector3 dir, cSPVector3* hitPos,
                           cSPVector3* hitNormal, int* pIndex, bool& bHit, int* pState);   // 0x004a4840
void DeleteInvalidBlocks(cSPEditorBlock* block, int a);                                    // 0x004a6f10
void SetSymmetricBlocksUIState(cSPEditorBlock* block, BlockVector* pile, int state);       // 0x004a7f30
}  // namespace EditorUtils

void BuildPileList(cSPEditorBlock* block, BlockVector* pile, int a);   // 0x0048c790
void PreparePileForRig(cSPEditorBlock* block, BlockVector* pile);      // 0x004961d0
void ReleaseRefs(cSPEditorBlock* block, BlockVector* pile);            // 0x004a8860
EA::AutoRefCount<cSPEditorBlock>* RemoveCopyBlocks(EA::AutoRefCount<cSPEditorBlock>* first,
                                                   EA::AutoRefCount<cSPEditorBlock>* last,
                                                   EA::AutoRefCount<cSPEditorBlock>* dest,
                                                   const EA::AutoRefCount<cSPEditorBlock>* value);   // 0x005aa740

}  // namespace SP
#endif  // SP_EDITOR_MANIP_S005AAD00_EXT_H
