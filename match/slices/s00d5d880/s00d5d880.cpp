// s00d5d880 -- SP::cCityVisualizer tick pieces: the allegiance/siren particle
// update, the artifact pickup pass that drives the action circles, the
// space-only tick that repacks and re-sounds a city, and the eastl vector
// insert instantiation used by that code.
//
//   0x00d5d880 SP::cCityVisualizer::AllegianceUpdate
//   0x00d5de40 SP::cCityVisualizer::UpdateArtifacts
//   0x00d5e0c0 SP::cCityVisualizer::SpaceOnlyTick
//   0x00d5e5c0 eastl::vector<CitySlot>::Insert
//
// Layout note: the visualizer keeps the two siren noun-pointer arrays at
// +0xa64/+0xa68, the city pointer at +0xaf0, the artifact flag/packing/audio
// handle at +0xaf6/+0xaf8/+0xafc, the audio system at +0xb4c, the particle
// handle at +0xb5c, the worship countdown at +0xc60 and the artifact timer at
// +0xc68.  The cached/emitted points live at +0x138 and +0x1b0.
#include "types.h"
#include <math.h>

#define nullptr 0

// ---------------------------------------------------------------------------
// engine objects
// ---------------------------------------------------------------------------

// Game-side polymorphic object; every slot is named by its byte offset since
// this file only ever calls through the vtable.
class IGameObject {
public:
    virtual void* Slot00();                         // +0x000
    virtual void Release();                         // +0x004
    virtual void SetActive(bool bActive);           // +0x008
    virtual void* Slot0c(int32_t nFlags);           // +0x00c
    virtual void* Slot10();                         // +0x010
    virtual void Slot14();                          // +0x014
    virtual void Slot18();                          // +0x018
    virtual void Slot1c();                          // +0x01c
    virtual void Slot20();                          // +0x020
    virtual void Slot24();                          // +0x024
    virtual void Slot28();                          // +0x028
    virtual void* Slot2c();                         // +0x02c
    virtual void Slot30();                          // +0x030
    virtual void* Slot34();                         // +0x034
    virtual void Slot38();                          // +0x038
    virtual void Slot3c();                          // +0x03c
    virtual void* Slot40();                         // +0x040
    virtual void Slot44();                          // +0x044
    virtual void Slot48();                          // +0x048
    virtual void* Slot4c();                         // +0x04c
    virtual void Slot50();                          // +0x050
    virtual void Slot54();                          // +0x054
    virtual void Slot58();                          // +0x058
    virtual void* Slot5c();                         // +0x05c
    virtual void Slot60();                          // +0x060
    virtual void Slot64();                          // +0x064
    virtual void Slot68();                          // +0x068
    virtual void Slot6c();                          // +0x06c
    virtual void Slot70();                          // +0x070
    virtual void* Slot74();                         // +0x074
    virtual void Slot78();                          // +0x078
    virtual void Slot7c();                          // +0x07c
    virtual void Slot80();                          // +0x080
    virtual void Slot84();                          // +0x084
    virtual void Slot88();                          // +0x088
    virtual void Slot8c();                          // +0x08c
    virtual void Slot90();                          // +0x090
    virtual void Slot94();                          // +0x094
    virtual void Slot98();                          // +0x098
    virtual void Slot9c();                          // +0x09c
    virtual void SlotA0();                          // +0x0a0
    virtual void SlotA4();                          // +0x0a4
    virtual void SlotA8();                          // +0x0a8
    virtual void SlotAc();                          // +0x0ac
    virtual void SlotB0();                          // +0x0b0
    virtual void SlotB4();                          // +0x0b4
    virtual void SlotB8();                          // +0x0b8
    virtual void SlotBc();                          // +0x0bc
    virtual void* SlotC0();                         // +0x0c0
    virtual void SlotC4();                          // +0x0c4
    virtual void SlotC8();                          // +0x0c8
    virtual void SlotCc();                          // +0x0cc
    virtual void SlotD0();                          // +0x0d0
    virtual void SlotD4();                          // +0x0d4
    virtual void SlotD8();                          // +0x0d8
    virtual void SlotDc();                          // +0x0dc
    virtual void SlotE0();                          // +0x0e0
    virtual void SlotE4();                          // +0x0e4
    virtual void SlotE8();                          // +0x0e8
    virtual void SlotEc();                          // +0x0ec
    virtual void SlotF0();                          // +0x0f0
    virtual void SlotF4();                          // +0x0f4
    virtual void SlotF8();                          // +0x0f8
    virtual void SlotFc();                          // +0x0fc
    virtual void Slot100();                         // +0x100
    virtual void Slot104();                         // +0x104
    virtual void Slot108();                         // +0x108
    virtual void Slot10c();                         // +0x10c
    virtual void Slot110();                         // +0x110
    virtual void Slot114();                         // +0x114
    virtual void Slot118();                         // +0x118
    virtual void Slot11c();                         // +0x11c
    virtual void* Slot120();                        // +0x120
};

// SP::cSPTimer -- 64-bit elapsed-millisecond counter.
class cSPTimer {
public:
    int64_t GetElapsedTime();       // 0x00bc3190
    void Restart();                 // 0x00bc3130
    uint8_t mPad00[0x10];
};

class cCity {
public:
    IGameObject* GetCivilization();     // 0x00d2f9a0 region
};

class IGameObject;

// the visualizer's city is always a cCity in these paths
static inline cCity* AsCity(IGameObject* pObject)
{
    return (cCity*)pObject;
}

struct Vector3 {
    float x;
    float y;
    float z;
};

// planet model used for the direction-to-surface query
class cPlanetModel {
public:
    Vector3* DirectionToSurfacePosition(Vector3* pOut, const Vector3* pDir);
};

class cActionCircle {
public:
    void RemoveAgent(void* pAgent);
};

class cGameNounManager {
public:
    void** GetGameDataVector(int32_t nFilter, void* pA, void* pB, void* pC, uint32_t nKey);
};

class cSPLivingUniverse {
public:
    int32_t GetPlayerEmpire();
    IGameObject* GetActivePlanet();
};

class cSPSimulatorSpaceGame {
public:
    IGameObject* GetPlayerInventory();
};

class cAudioSystem {
public:
    IGameObject* GetSystemAT();
};

void __cdecl operator_delete(void* pBlock);         // 0x00f47380

// eastl::fixed_vector<Vector3, 100> -- inline buffer, 12-byte elements
class FixedVector3s {
public:
    FixedVector3s()
    {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 100;
    }

    ~FixedVector3s()
    {
        if (mpBegin != mBuffer && mpBegin != nullptr)
            operator_delete(mpBegin);
    }

    void push_back(const Vector3& rValue)
    {
        if (mpEnd < mpCapacity) {
            *mpEnd = rValue;
            ++mpEnd;
        }
    }

    Vector3* mpBegin;           // +0x000
    Vector3* mpEnd;             // +0x004
    Vector3* mpCapacity;        // +0x008
    Vector3 mBuffer[100];       // +0x00c
};

// eastl::vector<int32_t> of the siren noun ids
class IntVector {
public:
    int32_t* mpBegin;
    int32_t* mpEnd;
    int32_t* mpCapacity;
    uint8_t mAllocator[0x0c];
};

void* __cdecl operator_new(size_t nSize, const char* pName, int32_t nA,
                           int32_t nB, const char* pFile, int32_t nLine);   // 0x00f473a0

IGameObject* __cdecl EffectsManager();              // 0x0067ddd0
IGameObject* __cdecl NounManager();                 // 0x00b25f40 region
IGameObject* __cdecl PlanetModel(Vector3* pOut, IGameObject* pTarget);       // 0x00b81630
Vector3* __cdecl FUN_00b81630(const Vector3* pDir, IGameObject* pPlanetModel);  // 0x00b81630
IGameObject* __cdecl GetActivePlanet();             // 0x00c71e30 region

bool __cdecl FUN_00cf74c0();                        // 0x00cf74c0
bool __cdecl FUN_00cf7a90();                        // 0x00cf7a90
void __cdecl FUN_00bdf750(IntVector* pIds);         // 0x00bdf750
IGameObject* __cdecl FUN_00b25f40(void* pNoun);     // 0x00b25f40
void* __cdecl FUN_00d5d430(void* pKey);             // 0x00d5d430
IGameObject* __cdecl FUN_01015df0();                // 0x01015df0
int32_t __cdecl FUN_00c71e30();                     // 0x00c71e30
bool __cdecl FUN_00a98020(IGameObject* pNode);      // 0x00a98020
void* __cdecl FUN_00ffbe50();                       // 0x00ffbe50
bool __cdecl FUN_00bec0f0(IGameObject* pOwner);     // 0x00bec0f0
IGameObject* __cdecl FUN_00bd7f50();                // 0x00bd7f50
IGameObject* __cdecl FUN_00af9f60();                // 0x00af9f60
int32_t __cdecl FUN_00afad30(IGameObject* pAgent);  // 0x00afad30
void __cdecl FUN_00c70110(IGameObject* pObject);    // 0x00c70110
void __cdecl FUN_00af9cf0(IGameObject* pOwner, const Vector3* pDir, int32_t nA,
                          void* pOut);              // 0x00af9cf0
void __cdecl FUN_00afd6d0(uint32_t nA, uint32_t nB, int32_t nC);            // 0x00afd6d0
void __cdecl FUN_00bef8e0();                        // 0x00bef8e0
int32_t __cdecl FUN_00fc8380();                     // 0x00fc8380
void __cdecl FUN_00d5ae80();                        // 0x00d5ae80
void __cdecl FUN_00b3d2c0(int32_t nA, int32_t nB, int32_t nC);              // 0x00b3d2c0
double __cdecl FUN_00d00a10(int32_t nA, int32_t nB, int32_t nC);            // 0x00d00a10
void __cdecl ActivateWorshipPosture();              // 0x00d5bf50 region
void __cdecl FUN_00bc97b0();                        // 0x00bc97b0
void __cdecl FUN_00bc97f0(int32_t nA, int32_t nB, uint32_t nC, int32_t nD); // 0x00bc97f0
bool __cdecl FUN_01062ea0(void* pA, void* pB, void* pC);                    // 0x01062ea0
void __cdecl FUN_00bd9480(void* pA);                                        // 0x00bd9480
void __cdecl Start3dSoundByName(int32_t nSoundId, IGameObject* pAudio,
                                int32_t nA, int32_t nB, int32_t nC);        // 0x00bd5b30 region
uint32_t __cdecl RandomUint32Uniform(uint32_t nRange);                      // 0x00b3d360
double __cdecl RandomDoubleUniform();                                       // 0x00b3d3a0

extern Vector3 gEmptyPoint;                     // 0x0169ec28
extern float gGateRadii[7];                     // 0x0147bb94
extern float gWorshipChances[7][3];             // 0x0147bb40

// ---------------------------------------------------------------------------
// the visualizer
// ---------------------------------------------------------------------------
class cCityVisualizer {
public:
    void AllegianceUpdate();            // 0x00d5d880
    void UpdateArtifacts();             // 0x00d5de40
    int32_t SpaceOnlyTick();            // 0x00d5e0c0

    uint8_t mPad000[0x138];         // +0x0000
    float mDestX;                   // +0x0138
    float mDestY;                   // +0x013c
    float mDestZ;                   // +0x0140
    uint8_t mPad144[0x64];          // +0x0144
    int32_t mnArtifactTick;         // +0x01a8
    uint32_t mnSoundId;             // +0x01ac
    float mNewX;                    // +0x01b0
    float mNewY;                    // +0x01b4
    float mNewZ;                    // +0x01b8
    uint8_t mPad1bc[0x8a8];         // +0x01bc
    void** mppSirenIds;             // +0x0a64
    void** mppSirenEnd;             // +0x0a68
    uint8_t mPadA6c[0x84];          // +0x0a6c
    IGameObject* mpCity;            // +0x0af0
    uint8_t mPadAf4[0x02];          // +0x0af4
    bool mbArtifactReady;           // +0x0af6
    uint8_t mPadAf7[0x01];          // +0x0af7
    float mPacking;                 // +0x0af8
    void* mpAudioHandle;            // +0x0afc
    uint8_t mPadB00[0x4c];          // +0x0b00
    cAudioSystem* mpAudioSystem;    // +0x0b4c
    uint8_t mPadB50[0x0c];          // +0x0b50
    IGameObject* mpParticleEffect;  // +0x0b5c
    uint8_t mPadB60[0x100];         // +0x0b60
    int32_t mnWorshipCountdown;     // +0x0c60
    uint8_t mPadC64[0x04];          // +0x0c64
    cSPTimer mArtifactTimer;        // +0x0c68
};

// @ 0x00d5d880
void cCityVisualizer::AllegianceUpdate()
{
    if (mpParticleEffect == nullptr) {
        IGameObject* pEffects = EffectsManager();
        IGameObject* pOld = mpParticleEffect;
        if (pOld != nullptr) {
            mpParticleEffect = nullptr;
            pOld->Release();
        }
        if (pEffects->Slot2c() != 0) {
            FixedVector3s points;
            points.push_back(gEmptyPoint);
            mpParticleEffect->Slot40();
            mpParticleEffect->Slot40();
        }
        if (mpParticleEffect == nullptr)
            return;
    }

    int32_t nSirens = 0;
    FUN_00cf74c0();
    if (!FUN_00cf7a90() && mppSirenIds != mppSirenEnd) {
        IntVector sirenIds;
        FUN_00bdf750(&sirenIds);
        FixedVector3s positions;
        FixedVector3s targets;
        for (int32_t i = 0; i < (int32_t)((uint8_t*)sirenIds.mpEnd - (uint8_t*)sirenIds.mpBegin) / 8; ++i) {
            void* pNoun = (void*)((int32_t*)sirenIds.mpBegin)[i * 2];
            IGameObject* pObject = FUN_00b25f40(pNoun);
            if (pObject != nullptr) {
                Vector3* pPoint = (Vector3*)FUN_00d5d430((uint8_t*)sirenIds.mpBegin + i * 8);
                pPoint->x = *(float*)((uint8_t*)pObject + 0xc4);
                pPoint->y = *(float*)((uint8_t*)pObject + 0xc8);
                pPoint->z = *(float*)((uint8_t*)pObject + 0xcc);
            }
        }

        int32_t nCount = 0;
        IGameObject* pCiv = AsCity(mpCity)->GetCivilization();
        IGameObject* pEmpire = (IGameObject*)pCiv->Slot4c();
        int32_t* pSiren = (int32_t*)mppSirenIds;
        int32_t* pSirenEnd = (int32_t*)mppSirenEnd;
        FixedVector3s targets2;
        while (pSiren != pSirenEnd && nCount < 100) {
            int32_t nNoun = *pSiren;
            IGameObject* pObject = *(IGameObject**)(nNoun + 0xff0);
            if (pObject != pEmpire) {
                Vector3 pos;
                pos.x = *(float*)((uint8_t*)pObject + 0xc4);
                pos.y = *(float*)((uint8_t*)pObject + 0xc8);
                pos.z = *(float*)((uint8_t*)pObject + 0xcc);
                float fRadius = *(float*)((uint8_t*)pObject + 0xd0)
                              - *(float*)((uint8_t*)pObject + 0xd4) + 2.0f;
                float fScale = 1.0f / (float)(sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z) + 1e-08);
                Vector3 target;
                target.x = fScale * pos.x * fRadius + pos.x;
                target.y = fScale * pos.y * fRadius + pos.y;
                target.z = fScale * pos.z * fRadius + pos.z;
                positions.push_back(target);
                targets2.push_back(*(const Vector3*)FUN_00d5d430(&pObject));
                nCount = nCount + 1;
            }
            ++pSiren;
        }

        int32_t nFill = 100 - nCount;
        while (nFill != 0) {
            positions.push_back(gEmptyPoint);
            targets2.push_back(gEmptyPoint);
            --nFill;
        }
        if (nCount > 0) {
            mpParticleEffect->Slot40();
            mpParticleEffect->Slot40();
        }
        if (nCount > 0) {
            if (mpParticleEffect->Slot10())
                return;
            mpParticleEffect->SetActive(false);
            return;
        }
    }
    mpParticleEffect->Slot0c(0);
}

// @ 0x00d5de40
void cCityVisualizer::UpdateArtifacts()
{
    mpCity->Slot6c();

    IGameObject* pEvent = *(IGameObject**)((uint8_t*)this + 0x0c70);
    if (pEvent != nullptr) {
        if (!FUN_00bec0f0((IGameObject*)pEvent->Slot2c())) {
            pEvent = *(IGameObject**)((uint8_t*)this + 0x0c70);
            *(IGameObject**)((uint8_t*)this + 0x0c70) = nullptr;
            if (pEvent != nullptr)
                pEvent->Release();
        }
    }

    cActionCircle* pCircles = (cActionCircle*)FUN_00bd7f50();
    if (FUN_00af9f60() == 0)
        return;

    void** pList = ((cGameNounManager*)NounManager())->GetGameDataVector(
        (int32_t)0xcd7d10, (void*)0xd3d420, (void*)0xad4930, (void*)0xb1e500, 0x2dd8c42);
    void** ppAgentsEnd = *(void***)((uint8_t*)pList + 8);
    void** ppAgents = *(void***)((uint8_t*)pList + 4);
    int32_t nCount = (int32_t)(ppAgentsEnd - ppAgents);
    for (int32_t i = 0; i < nCount; ++i) {
        int32_t* pAgent = (int32_t*)ppAgents[i];
        if (pAgent[0x658 / 4] != 4)
            continue;

        IGameObject* pAgentObject = (IGameObject*)((uint8_t*)pAgent + 0x34);
        bool bAlive = FUN_00bec0f0((IGameObject*)pAgentObject->Slot2c());
        int32_t nSlot = FUN_00afad30((IGameObject*)pAgent);
        bool bHasSlot = nSlot != -1;

        if (!bAlive) {
            if (bHasSlot)
                pCircles->RemoveAgent(pAgent);
        } else if (*(IGameObject**)((uint8_t*)this + 0x0c70) == nullptr) {
            if (bHasSlot) {
                if (mPacking == 0.0f && RandomDoubleUniform() < 0.1) {
                    FUN_00c70110((IGameObject*)pAgent);
                    Vector3 dir;
                    IGameObject* pCircle = mpCity;
                    pCircle->Slot5c();
                    Vector3 out;
                    out.x = -dir.x;
                    out.y = -dir.y;
                    out.z = -dir.z;
                    float fRadius = (float)(size_t)((IGameObject*)pCircle)->Slot74() + 1.0f;
                    FUN_00af9cf0((IGameObject*)pCircle->Slot2c(), &out, 0, &dir);
                    FUN_00afd6d0(0x40000000, 0x3f000000, 4);
                    (void)fRadius;
                }
            } else {
                IGameObject* pOwner = (IGameObject*)pAgentObject->Slot2c();
                Vector3 out;
                Vector3* pSurface = ((cPlanetModel*)PlanetModel(&out, pOwner))
                                        ->DirectionToSurfacePosition(&out, (const Vector3*)pOwner->Slot2c());
                const Vector3* pPos = (const Vector3*)pAgentObject->Slot2c();
                float dx = pPos->x - pSurface->x;
                float dy = pPos->y - pSurface->y;
                float dz = pPos->z - pSurface->z;
                if (sqrtf(dx * dx + dy * dy + dz * dz) < 0.1f)
                    ((IGameObject*)pAgent)->Slot00();
            }
        }
    }
}

// @ 0x00d5e0c0
int32_t cCityVisualizer::SpaceOnlyTick()
{
    int32_t nResult = 0;

    if ((int32_t)(mArtifactTimer.GetElapsedTime() >> 32) != 0
        || (uint32_t)mArtifactTimer.GetElapsedTime() > 1000) {
        mArtifactTimer.Restart();
        UpdateArtifacts();
    }

    IGameObject* pNode = (IGameObject*)FUN_01015df0();
    if (FUN_00a98020(pNode)) {
        IGameObject* pParent = (IGameObject*)((IGameObject*)FUN_01015df0())->Slot00();
        if (pParent == nullptr)
            goto use_player_inventory;
        pParent = (IGameObject*)((IGameObject*)FUN_01015df0())->Slot00();
        Vector3* pPos = (Vector3*)pParent->SlotC0();
        mDestX = pPos->x;
        mDestY = pPos->y;
        mDestZ = pPos->z;
    } else {
    use_player_inventory:
        IGameObject* pGame = (IGameObject*)FUN_00ffbe50();
        IGameObject* pInventory = ((cSPSimulatorSpaceGame*)pGame)->GetPlayerInventory();
        IGameObject* pItem = (IGameObject*)pInventory->Slot34();
        Vector3 pos;
        IGameObject* pModel = PlanetModel(&pos, (IGameObject*)pItem->Slot2c());
        Vector3* pPoint = (Vector3*)FUN_00b81630(&pos, pModel);
        mDestX = pPoint->x;
        mDestY = pPoint->y;
        mDestZ = pPoint->z;
    }

    int32_t nPackingMode = -1;
    Vector3* pCityPos = (Vector3*)mpCity->Slot120();
    float dx = pCityPos->x - mDestX;
    float dy = pCityPos->y - mDestY;
    float dz = pCityPos->z - mDestZ;
    if (sqrtf(dx * dx + dy * dy + dz * dz) < 60.0f) {
        IGameObject* pCiv = AsCity(mpCity)->GetCivilization();
        FUN_00bef8e0();
        int32_t nState = FUN_00fc8380();
        if (nState == 0) {
            nPackingMode = 2;
            nResult = nPackingMode;
        } else if (nState == 1) {
            nPackingMode = 0x10;
            nResult = nPackingMode;
        }
    }

    FUN_00d5ae80();
    if ((int32_t)(((cSPTimer*)((uint8_t*)this + 0x0c80))->GetElapsedTime() >> 32) != 0
        || (uint32_t)((cSPTimer*)((uint8_t*)this + 0x0c80))->GetElapsedTime() > 5000) {
        mPacking = (float)RandomUint32Uniform(3);
        ((cSPTimer*)((uint8_t*)this + 0x0c80))->Restart();
    }

    int32_t nOwner = (int32_t)mpCity->Slot4c();
    int32_t nPlayer = ((cSPLivingUniverse*)GetActivePlanet())->GetPlayerEmpire();
    nPlayer = *(int32_t*)((uint8_t*)nPlayer + 0x84);
    float fChance;
    if (nOwner == nPlayer) {
        fChance = 10.0f;
    } else {
        FUN_00b3d2c0(nOwner, nPlayer, 0);
        fChance = (float)FUN_00d00a10(nOwner, nPlayer, 0);
    }

    if (nPackingMode == 2) {
        if (fabsf(mPacking - fChance) <= 0.5f)
            goto worship_countdown;
        mPacking = fChance;
    } else {
        if (mPacking == 0.0f)
            goto worship_countdown;
        mPacking = 1.0f;
        mnWorshipCountdown = 3;
    }

worship_countdown:
    if (mnWorshipCountdown >= 0) {
        if (mnWorshipCountdown == 3) {
            ActivateWorshipPosture();
            ((cSPTimer*)((uint8_t*)this + 0x0c68 + 0x18))->Restart();
        }

        int32_t nStage = 0;
        int32_t nIndex = 0;
        do {
            nStage = nIndex;
            if (fChance <= gGateRadii[nIndex])
                break;
            ++nIndex;
            nStage = 0;
        } while (nIndex < 7);

        int32_t nSirens = (int32_t)(mppSirenEnd - mppSirenIds);
        IGameObject* pPlanet = ((cSPLivingUniverse*)GetActivePlanet())->GetActivePlanet();
        int32_t nAudio = FUN_00c71e30() != 0;

        for (int32_t i = 0; i < nSirens; ++i) {
            if ((float)(i & 0xf) == (float)mnWorshipCountdown) {
                float fRand = (float)RandomDoubleUniform();
                int32_t nSlot = 0;
                if (gWorshipChances[nStage][0] <= fRand) {
                    if (gWorshipChances[nStage][0] + gWorshipChances[nStage][1] <= fRand)
                        nSlot = nAudio == 0 ? 0x80 : 0x20;
                    else
                        nSlot = 0;
                } else {
                    nSlot = nAudio == 0 ? 0x10 : 0x40;
                }
                FUN_00bc97b0();
                if (nSlot != 0)
                    FUN_00bc97f0(nSlot, 0, 0x7f7fffff, 0);
            }
        }
        --mnWorshipCountdown;
    }

    Vector3 outPos;
    int32_t nType = 0;
    AsCity(mpCity)->GetCivilization();
    FUN_00bef8e0();
    if (FUN_01062ea0(&nType, &outPos, nullptr)) {
        if (mpAudioSystem == nullptr) {
            mpAudioHandle = nullptr;
        } else {
            mpAudioHandle = mpAudioSystem->GetSystemAT();
        }
        FUN_00bd9480(&mpAudioHandle);
        Start3dSoundByName((int32_t)mnSoundId, mpAudioSystem->GetSystemAT(), 0, 0, 0);
    }
    return nResult;
}

// ---------------------------------------------------------------------------
// eastl vector insert
// ---------------------------------------------------------------------------

// the 0x14-byte payload of a city slot (an eastl string-like handle)
class SlotPayload {
public:
    SlotPayload& operator=(const SlotPayload& rOther);      // 0x01011cc0
    uint8_t mPad00[0x14];
};

// one 0x1c-byte vector element
class CitySlot {
public:
    uint32_t mnId;              // +0x00
    bool mbA;                   // +0x04
    bool mbB;                   // +0x05
    bool mbC;                   // +0x06
    SlotPayload mPayload;       // +0x08  (the 0x07 byte is tail padding)
};

void __stdcall DestroySlot(CitySlot* pSlot);                        // 0x00d59630
void __cdecl MoveBackwardSlots(CitySlot* pPos, CitySlot* pFirst, CitySlot* pLast);  // 0x00d5bf50
CitySlot* __cdecl UninitializedCopySlots(CitySlot* pFirst, CitySlot* pLast, CitySlot* pOut);    // 0x00d59890
void __cdecl DestroyRangeSlots(CitySlot* pFirst, CitySlot* pLast, CitySlot* pOut);              // 0x00d598d0

class SlotVector {
public:
    void Insert(CitySlot* pPos, const CitySlot* pValue);    // 0x00d5e5c0

    CitySlot* mpBegin;          // +0x00
    CitySlot* mpEnd;            // +0x04
    CitySlot* mpCapacity;       // +0x08
};

// @ 0x00d5e5c0
void SlotVector::Insert(CitySlot* pPos, const CitySlot* pValue)
{
    if (mpEnd != mpCapacity) {
        const CitySlot* pSource = pValue;
        if (pSource >= pPos && pSource < mpEnd)
            pSource = pSource + 1;

        if (mpEnd != nullptr)
            DestroySlot(&mpEnd[-1]);
        MoveBackwardSlots(pPos, &mpEnd[-1], mpEnd);
        *pPos = *pSource;
        mpEnd = mpEnd + 1;
        return;
    }

    uint32_t nNewCapacity = (uint32_t)(mpEnd - mpBegin);
    if (nNewCapacity == 0) {
        nNewCapacity = 1;
    } else {
        nNewCapacity = nNewCapacity * 2;
    }

    CitySlot* pNew = nullptr;
    if (nNewCapacity != 0) {
        pNew = (CitySlot*)operator_new(nNewCapacity * sizeof(CitySlot), "Simulator", 0, 0,
                                       "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL"
                                       "\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }

    CitySlot* pPrevBegin = mpBegin;
    CitySlot* pGapEnd = UninitializedCopySlots(pPrevBegin, pPos, pNew);
    DestroyRangeSlots(pPrevBegin, pPos, pNew);
    if (pGapEnd != nullptr)
        DestroySlot((CitySlot*)pValue);

    CitySlot* pPrevEnd = mpEnd;
    CitySlot* pNewEnd = UninitializedCopySlots(pPos, pPrevEnd, pGapEnd + 1);
    DestroyRangeSlots(pPos, pPrevEnd, pGapEnd + 1);

    if (mpBegin != nullptr && *(int32_t*)((uint8_t*)mpBegin - 4) != 0)
        operator_delete(mpBegin);

    mpEnd = pNewEnd;
    mpBegin = pNew;
    mpCapacity = (CitySlot*)((uint8_t*)pNew + nNewCapacity * sizeof(CitySlot));
}
