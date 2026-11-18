// @ 0x00c6a4d0
// SP::cEgg shutdown: drop the egg's four reference-counted pointers (herd, the creature it is
// about to hatch into, whoever is interacting with it, and the game-data interface at +0x2c),
// then clear the spatial object (+0x34), the combatant (+0x120) and the interaction target
// (+0x108).  The last clear is reached with a tail jump.
//
// The generated SP/cEgg.h lays the bases out at the dev PDB offsets (cSpatialObject at +0x2c,
// cInteractionTarget at +0xb0, cCombatant at +0xc8); retail has them at +0x34, +0x108 and
// +0x120 (cGameData's retail size is 0x34), so the retail offsets are used through the local
// views below, as in slices s00c6a100 and s00c6a550.
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "game/types.h"

// A reference-counted object: slot 1 (vtable +0x04) releases one reference.
class RefObj_c6a4d0
{
  public:
    virtual void AddRef();   // +0x00
    virtual void Release();  // +0x04
};

class SpatialObject_c6a4d0
{
  public:
    void Clear();            // 0x00c8b2e0

  private:
    unsigned char mBytes[0xd4];
};

class InteractionTarget_c6a4d0
{
  public:
    void Clear();            // 0x00ac0450

  private:
    unsigned char mBytes[0x18];
};

class Combatant_c6a4d0
{
  public:
    void ReleaseSlots();     // 0x00bfc720

  private:
    unsigned char mBytes[0xc8];
};

class Egg_c6a4d0
{
  public:
    void Shutdown();

  private:
    unsigned char beforeRef2c[0x2c];
    RefObj_c6a4d0* mpRef2c;                              // +0x2c
    unsigned char afterRef2c[0x34 - 0x30];               // cGameData retail size 0x34
    SpatialObject_c6a4d0 mSpatialObject;                 // +0x34
    InteractionTarget_c6a4d0 mInteractionTarget;         // +0x108
    Combatant_c6a4d0 mCombatant;                         // +0x120
    unsigned char beforeHerd[0x1f4 - 0x120 - 0xc8];
    RefObj_c6a4d0* mpHerd;                               // +0x1f4
    unsigned char beforeToHatch[0x218 - 0x1f8];
    RefObj_c6a4d0* mpToHatch;                            // +0x218
    RefObj_c6a4d0* mpWhoIsInteractingWithMe;             // +0x21c
};

// @ 0x00c6a4d0
void Egg_c6a4d0::Shutdown()
{
    if (RefObj_c6a4d0* p = mpHerd) {
        mpHerd = 0;
        p->Release();
    }
    if (RefObj_c6a4d0* p = mpToHatch) {
        mpToHatch = 0;
        p->Release();
    }
    if (RefObj_c6a4d0* p = mpWhoIsInteractingWithMe) {
        mpWhoIsInteractingWithMe = 0;
        p->Release();
    }
    if (RefObj_c6a4d0* p = mpRef2c) {
        mpRef2c = 0;
        p->Release();
    }
    mSpatialObject.Clear();
    mCombatant.ReleaseSlots();
    mInteractionTarget.Clear();
}
