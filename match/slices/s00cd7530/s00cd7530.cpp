// Slice s00cd7530 -- SP::cTribeModeStrategy::OnMouseWheel.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Retail signature: thiscall, (int delta, float x, float y, int flags), ret 0x10.
// It first feeds the strategy's embedded input state (+0x1e0), then (when the current
// terrain sphere reports the right key combination) raises the camera-rotate tribe
// event 0x64c010f, and finally forwards the wheel to the global input dispatcher.
#include "types.h"

// The strategy's local input state (cLocalInputState, +0x1e0 inside the strategy).
struct cLocalInputState {
    char mPad00[0x40];

    void OnMouseWheel(int delta, float x, float y, int flags);   // 0x00697b40
};

// Terrain-sphere key set; Contains() reports whether a key is present.
struct cTerrainSphere {
    bool Contains(uint32_t key);                                 // 0x00c772c0
};

struct cGameNounManager {
    cTerrainSphere* GetCurrentTerrainSphere();                   // 0x00f67d90
};

cGameNounManager* NounManager();                                 // 0x00b3d300

// Global input dispatcher. OnMouseWheel is vtable slot +0x60 (index 24).
struct cGameInputManager {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void OnMouseWheel(int delta, float x, float y, int flags);   // +0x60
};

cGameInputManager* GameInputManager();                           // 0x00b3d250

class cTribeModeStrategy {
public:
    char              mPad00[0x1e0];
    cLocalInputState  mInput;            // +0x1e0

    void OnMouseWheel(int delta, float x, float y, int flags);
    void SignalTribeEvent(uint32_t key);                             // 0x00cd6980
};

// @ 0x00cd7530
void cTribeModeStrategy::OnMouseWheel(int delta, float x, float y, int flags)
{
    mInput.OnMouseWheel(delta, x, y, flags);

    // Camera-rotate trigger: not while key 0x56d1871 is set, only with 0x64be5ff,
    // and only when 0x64c010f is not already active.
    cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
    if (sphere == 0 || !sphere->Contains(0x56d1871u)) {
        cTerrainSphere* sphere2 = NounManager()->GetCurrentTerrainSphere();
        if (sphere2 != 0 && sphere2->Contains(0x64be5ffu)) {
            cTerrainSphere* sphere3 = NounManager()->GetCurrentTerrainSphere();
            if (sphere3 == 0 || !sphere3->Contains(0x64c010fu))
                SignalTribeEvent(0x64c010fu);
        }
    }

    GameInputManager()->OnMouseWheel(delta, x, y, flags);
}
