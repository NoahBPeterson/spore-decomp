// Slice s00c9a8b0 -- SP::cTribe spawn/activate helper.
// Called on the tribe's spatial part, which sits at cTribe + 0x120; the tribe itself
// is reached at this - 0x120.  Reconstructed from the retail instruction stream.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

struct Vector3 {
    float x, y, z;
};

// --------------------------------------------------------------------- engine pieces
struct cSPTimer {
    char mBytes[0x48];
    void Restart();                                                   // 0x00bc3130
};

struct cPlanetModel {
    Vector3 DirectionToSurfacePosition(Vector3 const &dir) const;     // 0x00b815a0
};
cPlanetModel* PlanetModel();                                          // 0x00b3d350

// --------------------------------------------------------------------- tribe (at this - 0x120)
struct cTribe {
    void SetupChatAreas();                                            // 0x00c95af0
    void ReserveToolsSlots(bool active);                              // 0x00c998c0
    void FinishTask(int task);                                        // 0x00c987b0
};

// --------------------------------------------------------------------- the +0x70 sub-object
#define VPAD(n) virtual void vpad##n()

struct cTribeAspect {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8);
    VPAD(9); VPAD(10);
    virtual Vector3* GetDirection();                                  // +0x2c
    VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19);
    VPAD(20); VPAD(21); VPAD(22); VPAD(23); VPAD(24); VPAD(25); VPAD(26); VPAD(27);
    VPAD(28); VPAD(29); VPAD(30); VPAD(31); VPAD(32);
    virtual void Refresh();                                           // +0x84
};

struct cAspectHolder {
    char pad_000[0x70];
    cTribeAspect mAspect;                                             // +0x70
};

// object that receives the refreshed direction
struct cDirectionTarget {
    char pad_000[0x34];
    Vector3 mDirection;                                               // +0x34
};

// --------------------------------------------------------------------- this
struct cTribeSpawnPart_s00c9_a8b0 {
    void func80h();                                                   // 0x00c88510
    void Activate();

    char pad_000[0x1c8];
    Vector3 mDirection;                                               // +0x1c8
    char pad_1d4[0x410 - 0x1d4];
    cSPTimer mTimer;                                                  // +0x410
    char pad_458[0x18a4 - 0x458];
    cAspectHolder* mpAspect;                                          // +0x18a4
    char gap_18a8[4];
    cDirectionTarget* mpTarget;                                       // +0x18ac
};

// @ 0x00c9a8b0
void cTribeSpawnPart_s00c9_a8b0::Activate()
{
    func80h();
    mTimer.Restart();

    cTribe* tribe = (cTribe*)((char*)this - 0x120);
    tribe->SetupChatAreas();
    tribe->ReserveToolsSlots(false);

    mDirection = PlanetModel()->DirectionToSurfacePosition(mDirection);
    tribe->FinishTask(13);

    if (mpTarget && mpAspect) {
        mpAspect->mAspect.Refresh();
        cAspectHolder* aspect = mpAspect;
        cDirectionTarget* target = mpTarget;
        target->mDirection = *aspect->mAspect.GetDirection();
    }
}
