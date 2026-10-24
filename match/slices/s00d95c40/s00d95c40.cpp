// s00d95c40 -- gate-citizen tick and the extinguish-building hooks it shares a
// behavior dispatch row with.  Rows live in .data as (id, activate, tick,
// deactivate):
//
//   0x015915d0  0x4eff1b6   0xd90f90  0xd95c40  0xd90ff0
//   0x015913f0  0x4c0492c   0xd960b0  0xd91080  0xd91090
//   0x01591070  0x5303235   0xd961b0  0xd990a0  0xd963d0
//
//  0x00d95c40  GateCitizen_Tick                (tick column)
//  0x00d960b0  ExtinguishCitizen_Activate      (activate column)
//  0x00d961b0  ExtinguishBuilding_Activate     (activate column)
//  0x00d963d0  ExtinguishBuilding_Deactivate   (deactivate column)
//
// Every receiver here is the "gate citizen" record: spatial sub-object at
// +0xc0, gate flag at +0x135, animating-creature pointer at +0xb54, city
// visualizer at +0xfb8 and city at +0x1010.
#include "types.h"

#define nullptr 0

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV  virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

struct cVector3 {
    float m_fX;
    float m_fY;
    float m_fZ;
};

struct cVector4 {
    float m_fX;
    float m_fY;
    float m_fZ;
    float m_fW;
};

class cGateCitizen;
class cCity;
class cCityVisualizer;
class cCityBuilding;
class cActionCircle;
class cActionSlot;
class cBuildingData;
class cBuildingState;
class cPlanetModel;
class cLocomotionRequest;
class cAnimatingCreature;
class cExtinguishMemory;
class IWinText;

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------
// the shared gate-slot frame (three floats of slot position + four floats of
// facing); the retail image keeps it in writable .data, past the analysed image.
extern float g169f20c;   // 0x0169f20c
extern float g169f210;   // 0x0169f210
extern float g169f214;   // 0x0169f214
extern float g169f218;   // 0x0169f218
extern float g169f21c;   // 0x0169f21c
extern float g169f220;   // 0x0169f220
extern float g169f224;   // 0x0169f224
extern float g1470f1c;   // 0x01470f1c  2.0f
extern float g13ec4b4;   // 0x013ec4b4  0.9f
extern float g147c0f4;   // 0x0147c0f4  FLT_MAX
extern float g13f6a20;   // 0x013f6a20  0.85f
extern float g1471064;   // 0x01471064  0.5f
extern float g1485720;   // 0x01485720  1.0f
extern const uint32_t g_anGateAnimIds[4];   // 0x0147c120

// ---------------------------------------------------------------------------
// small services
// ---------------------------------------------------------------------------
class cRandom {                                      // 0x01601760
public:
    double   RandomDoubleUniform();                  // 0x009360d0
    uint32_t RandomUint32Uniform(uint32_t nMax);     // 0x00a68fb0
};

extern cRandom gMathRandom;

class cPlanetModel {
public:
    cVector4* BuildSurfaceOrientation();             // 0x00b7f250
};

cPlanetModel* __cdecl PlanetModel(cVector3& vOut, const cVector3& vPosition,
                                  const cVector3& vDirection);        // 0x00b3d350
void __cdecl NormalizedSafe(cVector3& vOut, const cVector3& vDirection);  // 0x00449c20
cBuildingData* __cdecl FUN_00d94d10(void* pMembers);                  // 0x00d94d10

// ---------------------------------------------------------------------------
// eastl-style buffer: the block capacity sits in the four bytes in front of
// the payload, which is what the inlined destructor tests before freeing.
// ---------------------------------------------------------------------------
struct cAllocationHeader {
    int32_t m_nCapacity;
};

class cBuffer {
public:
    ~cBuffer()
    {
        if (m_pData != nullptr) {
            cAllocationHeader* pHeader = (cAllocationHeader*)m_pData - 1;
            if (pHeader->m_nCapacity != 0)
                delete[] m_pData;
        }
    }
    uint8_t* m_pData;                                // +0x00
};

// ---------------------------------------------------------------------------
// action circles
// ---------------------------------------------------------------------------
class cActionSlot {                                  // stride 0x18
public:
    void Reserve(cGateCitizen* pAgent);              // 0x00afa030
    bool m_bReserved;                                // +0x00
    uint8_t m_pad001[0x0b];                          // +0x01
    cVector3 m_vPosition;                            // +0x0c
};

class cActionCircle {                                // stride 0x64
public:
    cActionSlot* GetFreeSlot();                      // 0x00aff070
    void RemoveAgent(cGateCitizen* pAgent);           // 0x00afae50
    int32_t CountOccupiedSlots();                    // 0x00af9fa0
    cActionSlot* SlotAt(uint32_t nSlot);             // 0x00af9ff0
    uint8_t m_pad000[0x64];                          // +0x00
};

// one building record of the visualizer (stride 0x198, action circle at +0x30)
class cCityBuilding {
public:
    uint8_t m_pad000[0x30];                          // +0x000
    cActionCircle m_actionCircle;                    // +0x030
    uint8_t m_pad094[0x198 - 0x94];                  // +0x094
};

class cCityVisualizer {
public:
    int32_t FindBuildingIndex(cBuildingData* pData); // 0x00d58130
    uint8_t m_pad000[0x220];                         // +0x000
    cActionCircle* m_pCircleBegin;                   // +0x220
    cActionCircle* m_pCircleEnd;                     // +0x224
    uint8_t m_pad228[0x390 - 0x228];                 // +0x228
    cCityBuilding m_buildings[1];                    // +0x390
    uint8_t m_pad528[0xa10 - 0x528];                 // +0x528
    bool m_bSimulateInProgress;                      // +0xa10
};

// spatial sub-object embedded in the per-building city data (vptr at +0x100)
class cPositionSource {
public:
    PV8 PV2 PV                                       // +0x00 .. +0x28
    virtual cVector3* GetPosition();                 // +0x2c
};

class cBuildingState {
public:
    void FUN_00bd7c80();                             // 0x00bd7c80
    uint8_t m_pad000[0x100];                         // +0x000
    cPositionSource m_position;                      // +0x100
    uint8_t m_pad104[0x1d8 - 0x104];                 // +0x104
    int32_t m_nState;                                // +0x1d8
};

// the creature spatial/locomotion sub-object at gate-citizen +0xc0
class cSpatial {
public:
    PV8 PV2 PV                                       // +0x00 .. +0x28
    virtual void FindLaneNode(void* pfnIsDamaged);   // +0x2c
    PV2                                              // +0x30 .. +0x34
    virtual void SetPosition(const cVector3* pPosition);        // +0x38
    virtual void SetOrientation(const cVector4* pOrientation);  // +0x3c
    PV16 PV16 PV4 PV2 PV                             // +0x40 .. +0xd8
    virtual void RequestMove(void* pRequest);        // +0xdc
};

class cAnimatingCreature {
public:
    void Detach(int32_t nMode);                      // 0x00a02b00
    uint8_t m_pad000[0x64];                          // +0x00
    bool m_bFlag64;                                  // +0x64
};

class cLocomotionRequest {
public:
    cLocomotionRequest();                            // 0x00ac9850
    cBuffer m_buffer;                                // +0x00
    uint8_t m_pad004[0x74 - 0x04];                   // +0x04
};

class cCity {
public:
    void* GetMembers();                              // 0x00c8e810 (cTribe::GetMembers)
    cBuildingState* GetBuildingState(int32_t nIndex); // 0x00bd8d60
};

// ---------------------------------------------------------------------------
// the gate citizen
// ---------------------------------------------------------------------------
class cGateCitizen {
public:
    int32_t GetBuildingIndex();                      // 0x00c227b0
    cCity* GetCity();                                // 0x00c23e40
    void FUN_00c0cff0(int32_t nMode);                // 0x00c0cff0
    void Hide();                                     // 0x00c0f280
    bool AnimationFinished(uint32_t nAnim);          // 0x00c123f0
    void InterruptAnimation(uint32_t nAnim, int32_t nBlend, int32_t nFlags);  // 0x00c12310
    void SetSprinting(bool bSprint);                 // 0x00c1ad10
    void MoveToPointAndFacingAtSpeed(uint32_t nMode, const cVector3* pPoint,
                                     const cVector3* pFacing, float fSpeed,
                                     float fTurn);   // 0x00c1c5c0
    uint8_t m_pad000[0xc0];                          // +0x000
    cSpatial m_spatial;                              // +0x0c0
    uint8_t m_pad0c4[0x135 - 0xc4];                  // +0x0c4
    bool m_bGateActive;                              // +0x135
    uint8_t m_pad136[0xb54 - 0x136];                 // +0x136
    cAnimatingCreature* m_pAnimatingCreature;        // +0xb54
    uint8_t m_padB58[0xf90 - 0xb58];                 // +0xb58
    bool m_bFlagF90;                                 // +0xf90
    uint8_t m_padF91[0xfb8 - 0xf91];                 // +0xf91
    cCityVisualizer* m_pVisualizer;                  // +0xfb8
    bool m_bFlagFBC;                                 // +0xfbc
    uint8_t m_padFBD[0x1010 - 0xfbd];                // +0xfbd
    cCity* m_pCity;                                  // +0x1010
};

// ---------------------------------------------------------------------------
// the extinguish-building memory block and its ref-counted window slots
// ---------------------------------------------------------------------------
class IWinText {
public:
    virtual void V00();                              // +0x00
    virtual void Release();                          // +0x04
    virtual void V08();                              // +0x08
    virtual void Detach(int32_t nMode);              // +0x0c
};

// EA::AutoRefCount<IWinText>; the retail build inlines the reset-to-null path
// into the deactivation hook and keeps operator= out of line for the assign.
class cWinTextRef {
public:
    void Assign(void* pText);                        // 0x00b5f950
    void Reset()
    {
        if (m_pText != nullptr) {
            m_pText->Detach(0);
            IWinText* pOld = m_pText;
            m_pText = nullptr;
            if (pOld != nullptr)
                pOld->Release();
        }
    }
    IWinText* m_pText;                               // +0x00
};

class cExtinguishMemory {
public:
    ~cExtinguishMemory();                            // 0x00d95020
    uint32_t m_n000;                                 // +0x00
    int32_t m_nBuildingIndex;                        // +0x04
    int32_t m_nSlotIndex;                            // +0x08
    cWinTextRef m_ref00C;                            // +0x0c
    cWinTextRef m_ref010;                            // +0x10
    cWinTextRef m_ref014;                            // +0x14
    cWinTextRef m_ref018;                            // +0x18
    uint8_t m_pad01C[0x28 - 0x1c];                   // +0x1c
    uint32_t m_n028;                                 // +0x28
    uint32_t m_n02C;                                 // +0x2c
    uint32_t m_n030;                                 // +0x30
    uint8_t m_pad034[0x3c - 0x34];                   // +0x34
    uint32_t m_n03C;                                 // +0x3c
    uint32_t m_n040;                                 // +0x40
    uint32_t m_n044;                                 // +0x44
    uint8_t m_pad048[0x50 - 0x48];                   // +0x48
    float m_f050;                                    // +0x50
};

// the request block that 0x00d960b0 builds in place and hands to RequestMove
struct cMoveRequest {
    cBuffer m_buffer;                                // +0x00
    uint32_t m_n004;                                 // +0x04
    uint32_t m_n008;                                 // +0x08
    uint8_t m_pad00C[4];                             // +0x0c
    float m_f010;                                    // +0x10
    uint32_t m_n014;                                 // +0x14
    float m_f018;                                    // +0x18
    float m_f01C;                                    // +0x1c
    float m_f020;                                    // +0x20
    uint32_t m_n024;                                 // +0x24
    uint8_t m_pad028[0x24];                          // +0x28
    bool m_b04C;                                     // +0x4c
    uint8_t m_pad04D[3];                             // +0x4d
    float m_f050;                                    // +0x50
    float m_f054;                                    // +0x54
    float m_f058;                                    // +0x58
    uint32_t m_n05C;                                 // +0x5c
    float m_f060;                                    // +0x60
    float m_f064;                                    // +0x64
    float m_f068;                                    // +0x68
    float m_f06C;                                    // +0x6c
    uint32_t m_n070;                                 // +0x70
};

// @ 0x00d95c40
bool __cdecl GateCitizen_Tick(cGateCitizen* pCitizen, int32_t nArg2, int32_t nArg3,
                              int32_t nArg4, uint32_t nFlags, int32_t* pMode)
{
    int32_t nResultMode = 0;
    bool bResult = true;

    int32_t nBuildingIndex = pCitizen->GetBuildingIndex();
    cCityVisualizer* pVisualizer = pCitizen->m_pVisualizer;
    cCityBuilding& building = pVisualizer->m_buildings[nBuildingIndex];
    cCity* pCity = pCitizen->GetCity();
    cBuildingState* pState = pCity->GetBuildingState(nBuildingIndex);

    pCitizen->m_bGateActive = (pVisualizer->m_bSimulateInProgress == 0);

    if (*pMode != 4 && (pState->m_nState != 2 || (nFlags & 0x200) != 0))
        nResultMode = 4;

    switch (*pMode) {
    case 1:
    case 2: {
        // the shared gate-slot frame is loaded first and then replaced by the
        // reserved slot's own position/facing.
        cVector3 vSlotPos;
        vSlotPos.m_fX = g169f20c;
        vSlotPos.m_fY = g169f210;
        vSlotPos.m_fZ = g169f214;
        cVector4 vOrientation;
        vOrientation.m_fX = g169f218;
        vOrientation.m_fY = g169f21c;
        vOrientation.m_fZ = g169f220;
        vOrientation.m_fW = g169f224;

        cActionSlot* pSlot = building.m_actionCircle.GetFreeSlot();
        if (pSlot == nullptr) {
            nResultMode = 5;
            *pMode = nResultMode;
            return true;
        }
        pSlot->Reserve(pCitizen);
        vSlotPos = pSlot->m_vPosition;

        cVector3 vTargetPos = *pState->m_position.GetPosition();
        cVector3 vDirection;
        vDirection.m_fX = vTargetPos.m_fX - vSlotPos.m_fX;
        vDirection.m_fY = vTargetPos.m_fY - vSlotPos.m_fY;
        vDirection.m_fZ = vTargetPos.m_fZ - vSlotPos.m_fZ;
        cVector3 vUnit;
        NormalizedSafe(vUnit, vDirection);

        cVector3 vSurface;
        cPlanetModel* pModel = PlanetModel(vSurface, vSlotPos, vUnit);
        vOrientation = *pModel->BuildSurfaceOrientation();

        {
            cLocomotionRequest request;
            pCitizen->m_spatial.RequestMove(&request);
        }
        pCitizen->m_spatial.SetPosition(&vSlotPos);
        pCitizen->m_spatial.SetOrientation(&vOrientation);

        cAnimatingCreature* pAnimating = pCitizen->m_pAnimatingCreature;
        if (pAnimating != nullptr)
            pAnimating->m_bFlag64 = true;
        if (nResultMode == 0) {
            nResultMode = 3;
            *pMode = nResultMode;
            return true;
        }
        break;
    }
    case 3: {
        if (pCitizen->AnimationFinished(0)) {
            double dRoll = gMathRandom.RandomDoubleUniform();
            if (g13f6a20 <= dRoll) {
                uint32_t nChoice = gMathRandom.RandomUint32Uniform(4);
                pCitizen->InterruptAnimation(g_anGateAnimIds[nChoice], -1, 0);
            }
            else {
                double dSecond = gMathRandom.RandomDoubleUniform();
                uint32_t nAnim = 0x02d5f9bf;
                if (g1471064 <= dSecond)
                    nAnim = 0x0459365d;
                pState->FUN_00bd7c80();
                pCitizen->InterruptAnimation(nAnim, -1, 0);
            }
        }
        break;
    }
    case 4:
    case 5: {
        cAnimatingCreature* pAnimating = pCitizen->m_pAnimatingCreature;
        if (pAnimating != nullptr)
            pAnimating->m_bFlag64 = false;
        pCitizen->m_pAnimatingCreature->Detach(1);
        building.m_actionCircle.RemoveAgent(pCitizen);
        bResult = false;
        break;
    }
    }
    if (nResultMode != 0)
        *pMode = nResultMode;
    return bResult;
}

// @ 0x00d960b0
bool __cdecl ExtinguishCitizen_Activate(cGateCitizen* pCitizen)
{
    {
        cMoveRequest request;
        request.m_f010 = g169f20c;
        request.m_f060 = g1470f1c;
        request.m_f018 = g169f210;
        request.m_f01C = g169f214;
        request.m_f020 = g1485720;
        request.m_f064 = g13ec4b4;
        request.m_buffer.m_pData = nullptr;
        request.m_n004 = 0;
        request.m_n008 = 0;
        request.m_n024 = 0;
        request.m_b04C = false;
        request.m_f050 = 0.0f;
        request.m_f054 = 0.0f;
        request.m_f058 = 0.0f;
        request.m_n05C = 0;
        request.m_f068 = g147c0f4;
        request.m_f06C = 0.0f;
        request.m_n070 = 0;
        pCitizen->m_spatial.RequestMove(&request);
    }
    pCitizen->FUN_00c0cff0(0);
    pCitizen->m_bGateActive = false;
    pCitizen->m_bFlagF90 = false;
    pCitizen->Hide();
    pCitizen->m_bFlagFBC = false;
    return true;
}

// @ 0x00d961b0
bool __cdecl ExtinguishBuilding_Activate(cGateCitizen* pCitizen, int32_t nArg2,
                                         int32_t nArg3, uint32_t nFlags, int32_t nArg5,
                                         cExtinguishMemory* pMem)
{
    if (pMem != nullptr) {
        pMem->m_nBuildingIndex = -1;
        pMem->m_nSlotIndex = -1;
        pMem->m_ref00C.m_pText = nullptr;
        pMem->m_ref010.m_pText = nullptr;
        pMem->m_ref014.m_pText = nullptr;
        pMem->m_ref018.m_pText = nullptr;
        pMem->m_n028 = 0;
        pMem->m_n02C = 0;
        pMem->m_n030 = 0;
        pMem->m_n03C = 0;
        pMem->m_n040 = 0;
        pMem->m_n044 = 0;
        pMem->m_f050 = 0.0f;
    }

    // CitizenTree::IsDamaged (0x00d91320) is the damage filter handed to the
    // spatial lookup; the lookup result itself is discarded.
    pCitizen->m_spatial.FindLaneNode((void*)0x00d91320);
    cCity* pCity = pCitizen->GetCity();
    void* pMembers = pCity->GetMembers();
    cBuildingData* pData = FUN_00d94d10(pMembers);
    if (pData == nullptr)
        return false;

    cCityVisualizer* pVisualizer = pCitizen->m_pVisualizer;
    int32_t nIndex = pVisualizer->FindBuildingIndex(pData);
    if (nIndex == -1)
        return false;

    cActionCircle* pCircle = pVisualizer->m_pCircleBegin + nIndex;
    if (pCircle->CountOccupiedSlots() >= 2)
        return false;

    int32_t nSlot = pCircle->SlotAt(0)->m_bReserved != 0;
    if (pCircle->SlotAt(nSlot)->m_bReserved)
        return false;

    cActionSlot* pSlot = pCircle->SlotAt(nSlot);
    pSlot->Reserve(pCitizen);
    cVector3 vSlotPos = pSlot->m_vPosition;
    cActionSlot* pFacingSlot = pCircle->SlotAt(pMem == nullptr ? 1 : 0);
    cVector3 vDirection;
    vDirection.m_fX = pFacingSlot->m_vPosition.m_fX - vSlotPos.m_fX;
    vDirection.m_fY = pFacingSlot->m_vPosition.m_fY - vSlotPos.m_fY;
    vDirection.m_fZ = pFacingSlot->m_vPosition.m_fZ - vSlotPos.m_fZ;
    cVector3 vFacing;
    NormalizedSafe(vFacing, vDirection);
    pCitizen->SetSprinting(true);

    if ((nFlags & 1) == 0) {
        pCitizen->MoveToPointAndFacingAtSpeed(2, &vSlotPos, &vFacing, g1471064, g1470f1c);
    }
    else {
        pCitizen->m_spatial.SetPosition(&vSlotPos);
        cVector3 vSurface;
        cPlanetModel* pModel = PlanetModel(vSurface, vSlotPos, vFacing);
        pCitizen->m_spatial.SetOrientation(pModel->BuildSurfaceOrientation());
    }

    pMem->m_n000 = 0;
    pMem->m_ref00C.Assign(pData);
    pMem->m_nBuildingIndex = nIndex;
    pMem->m_nSlotIndex = nSlot;
    return true;
}

// @ 0x00d963d0
void __cdecl ExtinguishBuilding_Deactivate(cGateCitizen* pCitizen, int32_t nArg2,
                                           int32_t nArg3, int32_t nArg4, int32_t nArg5,
                                           cExtinguishMemory* pMem)
{
    if (pMem->m_nBuildingIndex != -1) {
        cCityVisualizer* pVisualizer = pCitizen->m_pVisualizer;
        int32_t nCircles = (int32_t)(pVisualizer->m_pCircleEnd - pVisualizer->m_pCircleBegin);
        if (pMem->m_nBuildingIndex < nCircles)
            (pVisualizer->m_pCircleBegin + pMem->m_nBuildingIndex)->RemoveAgent(pCitizen);
    }
    pCitizen->SetSprinting(false);
    pCitizen->InterruptAnimation(0x02481db0, -1, 0);
    pMem->m_ref010.Reset();
    pMem->m_ref014.Reset();
    pMem->m_ref018.Reset();
    pMem->~cExtinguishMemory();
}
