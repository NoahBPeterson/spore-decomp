// slice s005aad00 — SP::cSPEditorManipulationCellPinning (Editor block pinning):
// complete object destructor, GetPileList (virtual slot 11), OnMouseUp, RecalculateMouseOffset
// and DoOnMouseDown.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "s005aad00.h"
#include "s005aad00_ext.h"

using namespace SP;

namespace {
// Row vector times a row-major 3x3 (Matrix33_Convert output).
inline cSPVector3 MulRow(const cSPVector3& v, const float* m) {
  return cSPVector3(v.x * m[0] + v.y * m[3] + v.z * m[6],
                    v.x * m[1] + v.y * m[4] + v.z * m[7],
                    v.x * m[2] + v.y * m[5] + v.z * m[8]);
}
}  // namespace

// @ 0x005aad00
cSPEditorManipulationCellPinning::~cSPEditorManipulationCellPinning() {}

// @ 0x005ab1b0
eastl::sp_vector<EA::AutoRefCount<cSPEditorBlock> > cSPEditorManipulationCellPinning::GetPileList() {
  return mPileList;
}

// @ 0x005aada0
bool cSPEditorManipulationCellPinning::OnMouseUp(int, float, float, int) {
  if (mBlock && mBlock->mSocketConnector) {
    uint32_t key[3];
    mBlock->F40b90(key);
    if (key[2] == 0xdfad9f51 && key[0] == 0x3c2a2452 && mBlock->mOrientation != kIdentity)
      FindUIHint(0x44f89e14)->Show();
  }
  if (mBlock->mFlags.test(56)) {
    cSPMatrix3 orientation(mBlock->mOrientation);
    cSPVector3 normal(mBlock->mSurfaceNormal);
    cSPMatrix3 placement;
    EditorUtils::FUN_49c210(&placement, mBlock, normal);
    float converted[9];
    Matrix33_Convert(converted, &placement);
    cSPMatrix3 combined;
    combined.xAxis = MulRow(orientation.xAxis, converted);
    combined.yAxis = MulRow(orientation.yAxis, converted);
    combined.zAxis = MulRow(orientation.zAxis, converted);
    mBlock->SetUserOrientation(combined);
    mBlock->SetOrientation(placement, false);
  }
  if (mBlock && mBlock->mSocketConnector && !mHadParentOnMouseDown) {
    EA::AutoRefCount<cSPEditorAnimatedEventInfo> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo());
    info->MessagePost(0x8e04ce1a, mBlock, mBlock ? mBlock->mEditorModel : 0, 0, 0, 0.0f, 0, -1, 1.0f);
  }
  if (mBlock && !mBlock->mSocketConnector && mHadParentOnMouseDown) {
    EA::AutoRefCount<cSPEditorAnimatedEventInfo> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo());
    info->MessagePost(0x428e920, mBlock, mBlock ? mBlock->mEditorModel : 0, 0, 0, 0.0f, 0, -1, 1.0f);
  }
  EditorUtils::DeleteInvalidBlocks(mBlock, 0);
  if (mInflatedMesh)
    mInflatedMesh->Destroy(1);
  return true;
}

// @ 0x005ab220
void cSPEditorManipulationCellPinning::RecalculateMouseOffset(float x, float y) {
  cSPVector3 offset = kZero;
  BlockVector ignore;
  ignore.push_back(mBlock);
  bool bHit = false;
  cSPVector3 origin, dir;
  App()->GetViewer()->GetWorldRayFromScreenCoords(x, y, origin, dir);
  cSPVector3 hitPos, hitNormal;
  int index;
  cSPEditorBlock* hit =
      EditorUtils::PickBlocks(&ignore, origin, dir, &hitPos, &hitNormal, &index, bHit, 0);
  if (hit) {
    offset.x = mBlock->mPosition.x - hitPos.x;
    offset.y = mBlock->mPosition.y - hitPos.y;
    offset.z = mBlock->mPosition.z - hitPos.z;
    mMouseOffset = offset;
    cSPMatrix3 orientation(mBlock->mOrientation);
    float converted[9];
    Matrix33_Convert(converted, &orientation);
    offset = MulRow(offset, converted);
  }
  if (dir.z != 0.0f) {
    float t = -((origin.z + 0.1f) / dir.z);
    if (t >= 0.0f) {
      offset.x = mBlock->mPosition.x - (origin.x + t * dir.x);
      offset.y = mBlock->mPosition.y - (origin.y + t * dir.y);
      offset.z = 0.0f;
      cSPMatrix3 orientation(mBlock->mOrientation);
      float converted[9];
      Matrix33_Convert(converted, &orientation);
      offset = MulRow(offset, converted);
      mMouseOffset = offset;
    }
  }
  CalculateInflatedMesh();
}

// @ 0x005ab5c0
bool cSPEditorManipulationCellPinning::DoOnMouseDown(int, float x, float y, int modifiers) {
  cSPEditorModel* model = mBlock->mEditorModel;
  if (mBlock->mFlags.test(56)) {
    cSPMatrix3 orientation(mBlock->mOrientation);
    mBlock.mpObject->SetUserOrientation(kIdentity);
    mBlock->SetOrientation(orientation, false);
  }
  mPileList.erase(mPileList.begin(), mPileList.end());
  BuildPileList(mBlock, &mPileList, 0);
  EA::AutoRefCount<cSPEditorBlock>* last = mPileList.end();
  EA::AutoRefCount<cSPEditorBlock>* it = mPileList.begin();
  while (it != last) {
    if (*it == mBlock)
      break;
    ++it;
  }
  if (it != last)
    it = RemoveCopyBlocks(it + 1, last, it, &mBlock);
  mPileList.erase(it, last);
  PreparePileForRig(mBlock, &mPileList);
  if (!model->UsingSymmetry())
    ReleaseRefs(mBlock, &mPileList);
  EditorUtils::SetSymmetricBlocksUIState(mBlock, &mPileList, 0);
  cSPEditorBlock* block = mBlock;
  mY = y;
  mX = x;
  mHadParentOnMouseDown = block->mSocketConnector != 0;
  mUnTransformedPosition = block->mPosition;
  mUnTransformedOrientation = block->mOrientation;
  if (mSkin && mSkin->GetSkinPart(0)) {
    Factory* mesh = mSkin->GetSkinPart(0)->mMesh;
    if (mesh) {
      mInflatedMesh = mesh->Make();
      if (mRecalculateMouseOffset)
        RecalculateMouseOffset(x, y);
      else
        CalculateInflatedMesh();
      OnMouseMove(x, y, modifiers);
    }
  }
  mBumpedBlock.Reset();
  return true;
}
