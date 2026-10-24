// Slice s0105f2d0: SP::cUFOLocomotion solar/galaxy locomotion.
//
// All three routines are large (>1 KB) state evaluators that need the shipping
// cSPGameDataUFO / cUFOKinestheticsTuning hierarchies; only the surrounding
// model and the entry conditions are reconstructed here (see partial.txt).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

#define VSLOT(n) virtual void _v##n();

// ---------------------------------------------------------------------------
// small value types touched by the locomotion code
// ---------------------------------------------------------------------------
class cSPVector3 {
public:
    float mX;                    // +0x00
    float mY;                    // +0x04
    float mZ;                    // +0x08
};

class cSPVector4 {
public:
    float mX;                    // +0x00
    float mY;                    // +0x04
    float mZ;                    // +0x08
    float mW;                    // +0x0c
};

// ---------------------------------------------------------------------------
// SP::cUFOLocomotion (only the fields observed by this slice)
// ---------------------------------------------------------------------------
class cUFOLocomotion;

class cUFOSolarState {
public:
    uint8_t mnPad000[0x690];     // +0x000
    bool mbSolarActive;          // +0x690
    uint8_t mnPad691[0x83];      // +0x691
    uint32_t mnSolarTarget;      // +0x714
    cSPVector3 mSolarOrigin;     // +0x718
    uint8_t mnPad724[0x2c];      // +0x724
    cSPVector4 mSolarPosition;   // +0x750
};

class cUFOLocomotion : public cUFOSolarState {
public:
    VSLOT(0) VSLOT(1)
    void UpdateSolarGalaxyLocomotion(uint32_t nDeltaTime, void* pUniverse);
    void UpdateSolarAvoidance(uint32_t nDeltaTime, void* pUniverse);
};

void __stdcall UpdateSolarBody(cUFOLocomotion* pLocomotion, cSPVector3* pOut);

// ---------------------------------------------------------------------------
// SP::cUFOLocomotion::UpdateSolarGalaxyLocomotion
// @ 0x0105f2d0
// ---------------------------------------------------------------------------
void cUFOLocomotion::UpdateSolarGalaxyLocomotion(uint32_t nDeltaTime,
                                                 void* pUniverse)
{
    (void)nDeltaTime;
    (void)pUniverse;
}

// ---------------------------------------------------------------------------
// SP::cUFOLocomotion::UpdateSolarAvoidance
// @ 0x0105f760
// ---------------------------------------------------------------------------
void cUFOLocomotion::UpdateSolarAvoidance(uint32_t nDeltaTime, void* pUniverse)
{
    (void)nDeltaTime;
    (void)pUniverse;
}

// ---------------------------------------------------------------------------
// UpdateSolarBody
// @ 0x0105fbc0
// ---------------------------------------------------------------------------
void __stdcall UpdateSolarBody(cUFOLocomotion* pLocomotion, cSPVector3* pOut)
{
    pOut->mX = pLocomotion->mSolarPosition.mX;
    pOut->mY = pLocomotion->mSolarPosition.mY;
    pOut->mZ = pLocomotion->mSolarPosition.mZ;
}
