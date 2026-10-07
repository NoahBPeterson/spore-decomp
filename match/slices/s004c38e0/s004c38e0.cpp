// Slice s004c38e0: SP::cSPEditorSkinManager::Update / UpdatePaintedSkin and helpers (/Od).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

#pragma pack(push, 4)

namespace SP {

class cSPEditorSkinPart;

// +0xe0 holds the scene-object pointer (see 0x004c44c0 / 0x004cc190 layout).
class cSPEditorSkinPartView {
public:
    char pad[0xe0];
    void* mSceneObject;                 // +0xe0
    void* GetSceneObject() { return mSceneObject; }
};

class cSPEditorSkinManager {
public:
    char pad0[0x10];
    void* mModel;                        // +0x10 (asm: cmp [this+0x10],0 in Update)
    void* mSceneObjectModelWorld;        // +0x14 (asm: pushed as 2nd arg of 0x4cc7d0)
    cSPEditorSkinPartView* mTorsoSkin;   // +0x18
    cSPEditorSkinPartView* mCompleteSkin; // +0x1c
    char pad20[0x7c - 0x20];

    void* GetSceneObjectById(uint32_t which);
    void Update(uint32_t p2, char p3, uint32_t p4, uint32_t p5);
    void UpdateTorso(uint32_t a, uint32_t b);
    void UpdatePaintedSkin(uint32_t a, uint32_t b, uint32_t c);
    void UpdatePaintedSkin();            // 0x4c4290 is called with no stack args (asm), see Update
};

// @ 0x004c45d0
void* cSPEditorSkinManager::GetSceneObjectById(uint32_t which)
{
    switch (which) {
    case 0:
        return mTorsoSkin->GetSceneObject();
    case 1:
        return mCompleteSkin->GetSceneObject();
    }
    return 0;
}

// @ 0x004c38e0
// PARTIAL (in progress). Thiscall, 4 stack args (ret 0x10). Implemented so far:
//   - UpdateTorso(p4, p5) call at the top (asm 0x4c38fd, pushes [ebp+0x14] then [ebp+0x10])
//   - mModel null check (asm 0x4c3908) and the tail call to UpdatePaintedSkin (asm 0x4c427a),
//     which runs on both paths.
// MISSING (asm 0x4c3912..0x4c4270, roughly 2 KB): the per-block loop over mBlockList with
// FUN_004accf0 count, FUN_0044c030 / Entity::HasAnyBlockFlag / bitset tests, the
// mLimbSkins find/insert with operator_new(0x130,"Editor") + FUN_004cc190, the
// FUN_004cc470 / cSPEditorSkinPart::UpdateSceneObject / FUN_004cca40 slot calls,
// the CollectPartsRec + push_back paths, the complete-skin update (0x4c3fd8..0x4c4140),
// the limb cleanup loops with FUN_00435a10(9,0), and the FUN_004c64d0 / FUN_00425990
// tail. The mModel branch below is therefore NOT the full behavior.
void cSPEditorSkinManager::Update(uint32_t p2, char p3, uint32_t p4, uint32_t p5)
{
    (void)p2; (void)p3;
    UpdateTorso(p4, p5);
    if (mModel != 0) {
        // PARTIAL: see the note above.
    }
    UpdatePaintedSkin();
}

// @ 0x004c4290
// PARTIAL skeleton: rebuilds the painted-skin texture.
void cSPEditorSkinManager_UpdatePaintedSkin(void* self, uint32_t a, uint32_t b, uint32_t c)
{
    (void)self; (void)a; (void)b; (void)c;
}

// @ 0x004c44c0
// PARTIAL skeleton: per-limb skin scene-object update.
void UpdateLimbSceneObjects(void* self)
{
    (void)self;
}

} // namespace SP

#pragma pack(pop)
