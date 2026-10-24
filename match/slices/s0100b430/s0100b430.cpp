// s0100b430 - UFO galaxy update (gold6 worker 36)
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

struct cVector3 {
    float x;                                                            // 0x00
    float y;                                                            // 0x04
    float z;                                                            // 0x08
};

// ---------------------------------------------------------------------------
// Update context reached through cSPSimulatorSpaceGame::mpUpdateContext
// ---------------------------------------------------------------------------
struct cUpdateContext {
    uint32_t mUnk000[0x1a];                                             // 0x00
    void** mpBegin;                                                     // 0x68
    void** mpEnd;                                                       // 0x6c
};

// ---------------------------------------------------------------------------
// One simulated planet / UFO carrier living in the high-LOD list
// ---------------------------------------------------------------------------
class cSPSimPlanetUFO {
public:
    uint32_t mUnk000[0x1ac];                                            // 0x000
    uint32_t mnListIndex;                                               // 0x6b0
    uint32_t mUnk6b4[0x18];                                             // 0x6b4
    uint32_t mnKind;                                                    // 0x714
    cVector3 mStart;                                                    // 0x718
    uint32_t mUnk724[7];                                                // 0x724
    cVector3 mEnd;                                                      // 0x740
    uint32_t mnActive;                                                  // 0x74c
    cVector3 mCurrent;                                                  // 0x750
    uint32_t mUnk75c[8];                                                // 0x75c
    uint8_t mbUpdateFlag;                                               // 0x77e
    uint8_t mUnk77f[0x31];                                              // 0x77f
    void* mpOwnerRecord;                                                // 0x7b0
};

class cGameNounManager;
class cSPSimulatorSpaceGame;
class cPlayerInventory;

// ---------------------------------------------------------------------------
// The simulator space game object (this)
// ---------------------------------------------------------------------------
class cSPSimulatorSpaceGame {
public:
    uint32_t mUnk000[0xc];                                              // 0x000
    cUpdateContext* mpUpdateContext;                                    // 0x030
    uint32_t mUnk034[0x11];                                             // 0x034
    cSPSimPlanetUFO** mpPlanetBegin;                                    // 0x078
    cSPSimPlanetUFO** mpPlanetEnd;                                      // 0x07c
    cSPSimPlanetUFO** mpPlanetCapacity;                                 // 0x080

public:
    void GalaxyUpdateNPC_UFOs(uint32_t nDeltaTicks);
    cPlayerInventory* GetPlayerInventory();                             // 0x00a1ad60
};

// ---------------------------------------------------------------------------
// Imports
// ---------------------------------------------------------------------------
void GalaxyUpdateNPC_Prepass();                                         // 0x0100b0a0
cGameNounManager* GetNounManager();                                     // 0x01021240
void StarManager();                                                     // 0x00b3d2a0
int  StarManager_GetEmpireByID();                                       // 0x00ba9370
int  SimulatorUniverse_IsPaused();                                      // 0x00c31640
float Property_GetFloat();                                              // 0x0041ea70
void RelationshipManager();                                             // 0x00b3d2c0
int  LivingUniverse_GetPlayerEmpireID();                                // 0x01021090
cSPSimulatorSpaceGame* GetUFOSimulator();                               // 0x00ffbe50
int  IsAllied(int nEmpireA, int nEmpireB);                              // 0x00d01fb0
void SimUniverse_UpdatePosition(cVector3* pPosition);                   // 0x00c381e0
int  SimUniverse_IsObjectVisible(cSPSimPlanetUFO* pUFO, uint32_t nFlags);  // 0x01003df0
void* StarMap_Find(void* pRecord, uint32_t nFlags, int nArg2, int nArg3);  // 0x01046fc0
void StarMap_RemoveVisual(void* pStarMap, void* pRecord, uint32_t nFlags,
                          int nArg2, int nArg3);                        // 0x01045ae0
int  SimUniverse_CanDestroy();                                          // 0x00c370e0
void DestroyCreature(cSPSimPlanetUFO* pUFO, uint32_t nFlags);           // 0x0102c340
void PlanetList_CopyOver(cSPSimPlanetUFO** pSrc, cSPSimPlanetUFO** pEnd,
                         cSPSimPlanetUFO** pDst);                       // 0x006782c0

extern void* gSimulatorUniverse;                                        // 0x015b????
extern float gUFOBlend;                                                 // 0x015b68c4
extern float gUFORange;                                                 // 0x015b68c0
extern float gUFOGlide;                                                 // 0x015b68bc
extern float gUFOPlaneA;                                                // 0x015b64d0
extern float gUFOPlaneB;                                                // 0x015b64d4
extern float gUFOPlaneC;                                                // 0x015b64d8
extern int   gUFOProximityPropertyId;                                   // 0x055e7dad

// Avatar/city helpers reached through foreign objects.
class cGameNounManager {
public:
    int GetAvatar();                                                    // 0x00b1fdb0
};

class cCivData {
public:
    cVector3* GetCities();                                              // 0x005c65e0
};

class cPlayerInventory {
public:
    uint32_t mUnk000[0xd];                                              // 0x00
    cVector3* mpOrigin;                                                 // 0x34
};

float sqrtf_c(float fValue);                                            // 0x00ce6930
void UpdatePosseUFO(cSPSimulatorSpaceGame* pGame, cSPSimPlanetUFO* pUFO,
                    uint32_t nDeltaTicks, float fArg1, float fArg2, float fArg3);

// virtual slot helpers
inline uint32_t* VTableOf(void* pObject) { return *(uint32_t**)pObject; }

// ---------------------------------------------------------------------------
// @ 0x0100b430  cSPSimulatorSpaceGame::GalaxyUpdateNPC_UFOs
// ---------------------------------------------------------------------------
void cSPSimulatorSpaceGame::GalaxyUpdateNPC_UFOs(uint32_t nDeltaTicks)
{
    GalaxyUpdateNPC_Prepass();
    uint32_t nFlags = 0;
    int nAvatar = 0;
    cGameNounManager* pNounManager = GetNounManager();
    if (pNounManager != 0) {
        nAvatar = pNounManager->GetAvatar();
        StarManager();
        int nEmpire = StarManager_GetEmpireByID();
        if (nEmpire != 0 && SimulatorUniverse_IsPaused())
            goto PlanetLoop;
    }
    {
        float fProximity = 10.0f;
        cUpdateContext* pUniverse = *(cUpdateContext**)gSimulatorUniverse;
        if (pUniverse != 0) {
            uint32_t nProperty = 0;
            const void* pDescriptor = (const void*)0x055e7dad;
            if (!((bool (__thiscall*)(cUpdateContext*, const void*,
                                      uint32_t*))VTableOf(pUniverse)[0x24 / 4])(
                    pUniverse, pDescriptor, &nProperty))
                fProximity = 10.0f;
            else if (*(short*)(nProperty + 0x12) != 0x0d)
                fProximity = 10.0f;
            else
                fProximity = Property_GetFloat();
        }
        fProximity = fProximity * fProximity;
        RelationshipManager();
        int nPlayerEmpire = LivingUniverse_GetPlayerEmpireID();
        cSPSimulatorSpaceGame* pSimulator = GetUFOSimulator();
        cPlayerInventory* pInventory = pSimulator->GetPlayerInventory();
        cVector3* pOrigin = pInventory->mpOrigin;
        cUpdateContext* pContext = mpUpdateContext;
        for (void** ppEntry = pContext->mpBegin; ppEntry != pContext->mpEnd;
             ++ppEntry) {
            cGameNounManager* pEntryManager = (cGameNounManager*)*ppEntry;
            int nEntryEmpire = pEntryManager->GetAvatar();
            if (nEntryEmpire != nPlayerEmpire &&
                !IsAllied(nEntryEmpire, nPlayerEmpire))
                continue;
            cVector3* pCity = ((cCivData*)pEntryManager)->GetCities();
            float fDX = pCity->x - pOrigin->x;
            float fDY = pCity->y - pOrigin->y;
            float fDZ = pCity->z - pOrigin->z;
            if (fDY * fDY + fDX * fDX + fDZ * fDZ < fProximity) {
                nFlags |= 1;
                break;
            }
        }
    }

PlanetLoop:
    cSPSimPlanetUFO** ppPlanet = mpPlanetBegin;
    int nKind3Count = 0;
    int nKind8Count = 0;
    if (ppPlanet == mpPlanetEnd)
        return;
    cSPSimPlanetUFO** ppSlot = ppPlanet;
    do {
        cSPSimPlanetUFO* pUFO = *ppSlot;
        bool bKeep = false;
        switch (pUFO->mnKind) {
        case 3:
            pUFO->mnListIndex = (uint32_t)nKind3Count;
            ++nKind3Count;
            UpdatePosseUFO(this, pUFO, nDeltaTicks, 10.0f, 0.0079999999f, 10.0f);
            bKeep = ((char)pUFO->mnActive) != 0;
            break;
        case 4:
            bKeep = ((char)pUFO->mnActive) != 0;
            break;
        case 8: {
            pUFO->mnListIndex = (uint32_t)nKind8Count;
            ++nKind8Count;
            if (!SimUniverse_IsObjectVisible(pUFO, nFlags)) {
                bKeep = ((char)pUFO->mnActive) != 0;
                break;
            }
            void* pRecord = *(void**)((char*)pUFO->mpOwnerRecord + 0x70);
            void* pStarMap = StarMap_Find(pRecord, 0x0b7735c3, 0, 0);
            StarMap_RemoveVisual(pStarMap, pRecord, 0x0b7735c3, 0, 0);
            bKeep = ((char)pUFO->mnActive) != 0;
            break;
        }
        case 9: {
            cVector3 vDelta;
            vDelta.x = (float)pUFO->mEnd.x - (float)pUFO->mStart.x;
            vDelta.y = (float)pUFO->mEnd.y - (float)pUFO->mStart.y;
            vDelta.z = (float)pUFO->mEnd.z - (float)pUFO->mStart.z;
            float fLength = sqrtf_c(vDelta.y * vDelta.y +
                                           vDelta.z * vDelta.z +
                                           vDelta.x * vDelta.x) * gUFOBlend;
            float fRange = gUFORange <= fLength ? gUFORange : fLength;
            float fSlide = 0.0f;
            if ((float)nDeltaTicks * gUFOGlide < 1.0f)
                fSlide = (float)nDeltaTicks * gUFOGlide;
            else
                fSlide = 1.0f;
            cVector3 vDirection;
            vDirection.x = vDelta.y * gUFOPlaneC - vDelta.z * gUFOPlaneB;
            vDirection.y = vDelta.z * gUFOPlaneA - vDelta.x * gUFOPlaneC;
            vDirection.z = vDelta.x * gUFOPlaneB - vDelta.y * gUFOPlaneA;
            float fNorm = 1.0f / sqrtf_c(
                                    vDirection.z * vDirection.z +
                                    vDirection.y * vDirection.y +
                                    vDirection.x * vDirection.x + 1e-08f);
            cVector3 vTarget;
            vTarget.x = (vDirection.x * fNorm * fRange - (float)pUFO->mCurrent.x) *
                            fSlide + (float)pUFO->mCurrent.x;
            vTarget.y = (vDirection.y * fNorm * fRange - (float)pUFO->mCurrent.y) *
                            fSlide + (float)pUFO->mCurrent.y;
            vTarget.z = (vDirection.z * fNorm * fRange - (float)pUFO->mCurrent.z) *
                            fSlide + (float)pUFO->mCurrent.z;
            SimUniverse_UpdatePosition(&vTarget);
            bKeep = ((char)pUFO->mnActive) != 0;
            break;
        }
        default:
            bKeep = ((char)pUFO->mnActive) != 0;
            break;
        }
        if (bKeep) {
            pUFO->mbUpdateFlag = 1;
            if (SimUniverse_CanDestroy()) {
                if (((bool (__thiscall*)(cSPSimPlanetUFO*))VTableOf(pUFO)[0x2c / 4])(pUFO)) {
                    DestroyCreature(pUFO, 0);
                    if (ppSlot < mpPlanetEnd)
                        PlanetList_CopyOver(ppSlot + 1, mpPlanetEnd, ppSlot);
                    --mpPlanetEnd;
                    if (*mpPlanetEnd != 0)
                        ((void (__thiscall*)(cSPSimPlanetUFO*))VTableOf(
                            *mpPlanetEnd)[1])(*mpPlanetEnd);
                    continue;
                }
            }
        }
        ++ppSlot;
    } while (ppSlot != mpPlanetEnd);
}
