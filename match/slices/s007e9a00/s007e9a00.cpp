// Slice s007e9a00.
#include "../s007e5220/s007e5220.h"

// @ 0x007E9D00  (cAppSystem::OpenURL)
void cAppSystem::OpenURL(const wchar_t* url) {
    {
        WString s(url);
        mURLsToOpen.push_back(s);
    }
    if (mLockCount)
        SP_MessageServer()->SendMessage(0x462dde3, 0, 0, 0);
}

// @ 0x007E9A00  (cAppSystem::LoadEffectCollections)
int cAppSystemLoadEffectCollections(void* self) {
    // Effect-collection loading not reconstructed; see partial.txt.
    (void)self;
    return 0;
}

// @ 0x007E9DB0  (cAppSystem::Update)
void cAppSystemUpdate(void* self) {
    // Main per-frame update not reconstructed; see partial.txt.
    (void)self;
}

// @ 0x007EA2F0  (cheat constructor registering arg specs)
void FUN_007ea2f0(void* self) { (void)self; }
