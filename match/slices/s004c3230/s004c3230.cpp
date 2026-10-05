// Slice s004c3230: SP::cSPEditorSkinManager::UpdateTorso (1702 bytes, /Od).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

#pragma pack(push, 4)

namespace SP {

class cSPEditorSkinPart;
class cSPEditorModel;
class cIModelWorld;
class cSPEditorBlock;
class cSPTransform;

// Layout from the 2008 dev PDB (size 0x7c).
class cSPEditorSkinManager {
public:
    char pad0[0xc];
    void* mApp;                       // +0xc
    cSPEditorModel* mModel;           // +0x10
    cIModelWorld* mSceneObjectModelWorld;  // +0x14
    void* mTorsoSkin;                 // +0x18  (EA::AutoRefCount<cSPEditorSkinPart>)
    void* mCompleteSkin;              // +0x1c
    void* mPreviousTorsoBlockTransforms;   // +0x20 (eastl::vector<cSPTransform>)
    void* mPreviousTorsoBlockPointers;     // +0x30 (eastl::vector<cSPEditorBlock*>)
    void* mLimbSkins;                 // +0x40
    void* mPaintRequest;              // +0x50
    uint32_t mDefaultMaterial;        // +0x54
    uint32_t mTextureKey[3];          // +0x58 (ResourceMan::Key)
    void* mDiffuseTex;                // +0x64
    void* mNormalTex;                 // +0x68
    float mPaintResolution;           // +0x6c
    float mRealtimeResolution;        // +0x70
    float mHighQualityResolution;     // +0x74
    bool mPaintEnabled;               // +0x78
    bool mHairEnabled;                // +0x79

    void UpdateTorso(uint32_t flags);
};

// @ 0x004c3230
// PARTIAL skeleton: guards on mModel/mTorsoSkin/mSceneObjectModelWorld, snapshots the
// model's block list, compares block pointers + transforms against the previous torso
// snapshot, rebuilds the transform vector (scale/translation/rotation flag updates),
// calls cSPEditorSkinPart::UpdateSceneObject, and finally drives the skin-identifier
// and paint state from the flags argument.
void cSPEditorSkinManager::UpdateTorso(uint32_t flags)
{
    (void)flags;
    if (mModel == 0 || mTorsoSkin == 0 || mSceneObjectModelWorld == 0)
        return;
    // PARTIAL: full rebuild/compare path omitted.
}

} // namespace SP

#pragma pack(pop)
