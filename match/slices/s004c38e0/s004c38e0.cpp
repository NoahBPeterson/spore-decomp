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
    char pad0[0x18];
    cSPEditorSkinPartView* mTorsoSkin;   // +0x18
    cSPEditorSkinPartView* mCompleteSkin; // +0x1c
    char pad20[0x7c - 0x20];

    void* GetSceneObjectById(uint32_t which);
    void UpdatePaintedSkin(uint32_t a, uint32_t b, uint32_t c);
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
// PARTIAL skeleton: periodic skin refresh (validates content, updates torso,
// painted skin and texture bindings).
void cSPEditorSkinManager_Update(void* self)
{
    (void)self;
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
