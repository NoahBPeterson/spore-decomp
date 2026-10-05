// Slice s004c4650: SP::cSPEditorSkinManager helpers and related editor tasks (/Od).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

#pragma pack(push, 4)

namespace SP {

class cSPEditorSkinManager {
public:
    char pad0[0x18];
    void* mTorsoSkin;      // +0x18
    void* mCompleteSkin;   // +0x1c
    char pad20[0x7c - 0x20];

    void* GetSkin(uint32_t which);
};

// @ 0x004c49e0
void* cSPEditorSkinManager::GetSkin(uint32_t which)
{
    switch (which) {
    case 0: {
        void* p = mTorsoSkin;
        return p;
    }
    case 1: {
        void* p = mCompleteSkin;
        return p;
    }
    }
    return 0;
}

} // namespace SP

// Remaining slice-25 functions: PARTIAL skeletons.
// @ 0x004c4650  release/cleanup of a refcounted, thread-guarded object
void SkinHelper_Release(void* self, uint32_t flags) { (void)self; (void)flags; }
// @ 0x004c4a30  rebuild torso skin state
void SkinHelper_Rebuild(void* self) { (void)self; }
// @ 0x004c4d30  per-part update
void SkinHelper_UpdatePart(void* self) { (void)self; }
// @ 0x004c4eb0  detach/reset skin parts
void SkinHelper_Detach(void* self) { (void)self; }
// @ 0x004c4f60  skin material helper
void SkinHelper_Material(void* self) { (void)self; }
// @ 0x004c5030  skin texture helper
void SkinHelper_Texture(void* self) { (void)self; }
// @ 0x004c5100  skin transform helper
void SkinHelper_Transform(void* self) { (void)self; }

#pragma pack(pop)
