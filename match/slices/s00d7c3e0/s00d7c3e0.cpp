// Behaviour tree action scripts of the creature brain (celebrate upgrade,
// held-panic, shocked, charmed, nest upgrade, forage destination) plus the
// tribe tool enter/exit helpers and the mine proximity tests.

typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#define nullptr 0

float sinf(float fValue);

// ---------------------------------------------------------------------------
// Small helper types.
// ---------------------------------------------------------------------------
class cSPVector3 {
public:
    float mx;
    float my;
    float mz;
};

// ---------------------------------------------------------------------------
// Behaviour tree stimuli.
// ---------------------------------------------------------------------------
class cStimulus {
public:
    void GetAny();                              // 0x00d997e0

    uint8_t mPad000[0x0c];                      // 0x000
    cSPVector3 mPosition;                       // 0x00c
    int32_t mnField18;                          // 0x018
    int32_t mnField1C;                          // 0x01c
    int32_t mnField20;                          // 0x020
};

class cBehaviorStimuli {
public:
    void ClearAll(int32_t nA, int32_t nFlags);  // 0x00bc98f0
    void* Play(int32_t nA, int32_t nFlags);     // 0x00bc96a0

    uint8_t mPad000[0x1c0];                     // 0x000
    uint32_t mnField1C0;                        // 0x1c0
};

class cBehaviorTree {
public:
    uint8_t mPad000[0x08];                      // 0x000
    cBehaviorStimuli mStimuli;                  // 0x008
};

// ---------------------------------------------------------------------------
// Locomotion sub object (creature + 0xc0).
// ---------------------------------------------------------------------------
class cLocomotiveObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual float* GetPosition();               // 0x02c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void SetSpeed(float fSpeed);        // 0x040
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void v64(); virtual void v68(); virtual void v6c(); virtual void v70();
    virtual void v74(); virtual void v78(); virtual void v7c(); virtual void v80();
    virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual void va4(); virtual void va8(); virtual void vac(); virtual void vb0();
    virtual void vb4(); virtual void vb8(); virtual void vbc(); virtual void vc0();
    virtual void vc4(); virtual void vc8(); virtual void vcc(); virtual void vd0();
    virtual void vd4(); virtual void vd8(); virtual void vdc(); virtual void ve0();
    virtual void ve4(); virtual void ve8(); virtual void vec(); virtual void vf0();
    virtual void vf4();
    virtual bool IsMoving();                    // 0x0f8

    bool IsNearGoal();                          // 0x00c42e20
    float* GetVelocity();                       // 0x00d20610
};

// ---------------------------------------------------------------------------
// Combatant sub object (creature + 0x5a8).
// ---------------------------------------------------------------------------
class cCombatant {
public:
    int32_t GetFileCount();                     // 0x008e7f80
    float GetTargetDistance();                  // 0x00bfc490

    uint8_t mPad000[0x38];                      // 0x000
    float mfHealth;                             // 0x038
    uint8_t mPad03c[0x04];                      // 0x03c
    int32_t mnAnimId;                           // 0x040
    uint8_t mPad044[0x534];                     // 0x044
};

class cCreatureData {
public:
    uint8_t mPad000[0x5e8];                     // 0x000
    int32_t mnAnimId;                           // 0x5e8
};

class cCreaturePart {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50();
    virtual void EnterToolMode(void* pTool);    // 0x054
    virtual void ExitToolMode(void* pTool);     // 0x058

    void SetStimulusTarget(const void* pTarget);    // 0x00c41d60

    uint8_t mPad004[0x73];                      // 0x004
    uint8_t mbField077;                         // 0x077
    uint8_t mPad078[0x178];                     // 0x078
    int32_t mnField1F0;                         // 0x1f0
    uint8_t mPad1F4[0x74];                      // 0x1f4
    uint8_t mbField268;                         // 0x268
};

class cNearNoun {
public:
    float* GetPosition();                       // 0x00c6acc0

    uint8_t mPad000[0x02];                      // 0x000
    uint8_t mbField002;                         // 0x002
};

class cMessageServer {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void Send(int32_t nId, int32_t nA, int32_t nB);   // 0x014
};

// ---------------------------------------------------------------------------
// Creature base.
// ---------------------------------------------------------------------------
class cCreatureBase {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void* v2c();                        // 0x02c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44();
    virtual void AbortAnimation(int32_t nTime); // 0x048
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void v5c(); virtual void v60(); virtual void v64(); virtual void v68();
    virtual void v6c(); virtual void v70(); virtual void v74(); virtual void v78();
    virtual void v7c(); virtual void v80();
    virtual void SetAnimState(cCombatant* pTarget, int32_t nA, int32_t nB);   // 0x084
    virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void AddWalkSpeed(float fSpeed);    // 0x094
    virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
    virtual void* FindPart(uint32_t nPartId);   // 0x0b8
    virtual void vbc(); virtual void vc0(); virtual void vc4();
    virtual void StopMove(int32_t nA);          // 0x0c8
    virtual void vcc(); virtual void vd0(); virtual void vd4(); virtual void vd8();
    virtual void vdc(); virtual void ve0();
    virtual void SetFocusTarget(const void* pTarget);   // 0x0e4

    bool HasAnimation(int32_t nId);             // 0x00c0e0c0
    bool Flag388();                             // 0x00c0c0e0
    bool FUN_00c0b770();                        // 0x00c0b770
    void FUN_00c0b370(int32_t nA);              // 0x00c0b370
    void FUN_00c0d950(int32_t nA);              // 0x00c0d950
    bool FUN_00c0e2c0(uint32_t hAnim);          // 0x00c0e2c0
    bool AnimationFinished(uint32_t hAnim);     // 0x00c12400
    bool AnimationFinishedById(int32_t nAnim);  // 0x00c123f0
    void* InterruptAnimation(int32_t nId, int32_t nA, int32_t nB);   // 0x00c12310
    void* PlayAnimation(int32_t nId, int32_t nA, int32_t nB);        // 0x00c12190
    void Hover(int32_t nA);                     // 0x00c13a30
    void FUN_00c14750(int32_t nA);              // 0x00c14750
    void FUN_00c17350(uint32_t nBitsA, int32_t nB);   // 0x00c17350
    void FUN_00c1d460(uint32_t nBitsA, uint32_t nBitsB);   // 0x00c1d460
    void MoveToPointAtSpeed(int32_t nMode, float* pPoint);           // 0x00c1c1d0
    void SetStealthed(int32_t nA, int32_t nB);  // 0x00c1aed0
    bool WaitForAnimEventOrEnd(int32_t nEvent, uint32_t* phAnim,
                               int32_t nA, int32_t nB, int32_t nC);  // 0x00c14ef0
    void* Get();                                // 0x00c04590
    void* GetInRange(float fA, float fB);       // 0x00c04590
    void* GetFocusTarget();                     // 0x00c04750
    cCreatureBase* ApplyCombatTarget();         // 0x00c0ee90

    uint8_t mPad004[0x4c];                      // 0x004
    uint32_t mnFlags050;                        // 0x050
    uint8_t mPad054[0x23];                      // 0x054
    uint8_t mbField077;                         // 0x077
    uint8_t mPad078[0x48];                      // 0x078
    cLocomotiveObject mLocomotive;              // 0x0c0
    uint8_t mPad0C4[0x4c];                      // 0x0c4
    uint32_t mnFlags110;                        // 0x110
    uint8_t mPad114[0x23];                      // 0x114
    uint8_t mbField137;                         // 0x137
    uint8_t mPad138[0x470];                     // 0x138
    cCombatant mCombatant;                      // 0x5a8
    cCreatureData* mpData;                      // 0xb20
    uint8_t mPadB24[0x24];                      // 0xb24
    void* mpFieldB48;                           // 0xb48
    cBehaviorTree* mpBehaviorTree;              // 0xb4c
    uint8_t mPadB50[0x0e];                      // 0xb50
    uint8_t mbFieldB5E;                         // 0xb5e
    uint8_t mPadB5F[0xb0e];                     // 0xb5f
    uint8_t mbField166D;                        // 0x166d
    uint8_t mPad166E[0x2e];                     // 0x166e
    float mfRadius169C;                         // 0x169c
};

// ---------------------------------------------------------------------------
// Services, order nodes and iterators.
// ---------------------------------------------------------------------------
class cGameModeObject {
public:
    uint8_t mPad000[4];
};

class cGameStateObject {
public:
    uint8_t mPad000[0x78];                      // 0x000
    void* mpField078;                           // 0x078
    uint8_t mPad07C[0x50];                      // 0x07c
    int32_t mnField0CC;                         // 0x0cc
};

class cToolController {
public:
    void OnToolEnter(void* pTool, void* pPart);     // 0x00f1aff0
    void OnToolExit(void* pTool, void* pPart);      // 0x00f1b180
};

class cGameNounManager {
public:
    void* GetAvatar();                          // 0x00b1fdb0
};

class cRandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t nA, uint32_t nB, uint32_t nC);  // 0x00a68fb0
};

class cSpriteEffect {
public:
    void Start(int32_t nA);                     // 0x00d4d5c0
};

class cOrderNode {
public:
    uint8_t mPad000[0x10];                      // 0x000
    uint32_t mnField10;                         // 0x010
};

class cOrderManager {
public:
    cOrderNode* FindNode();                     // 0x00bca620
};

class cAnimFilter {
public:
    bool Accept(uint8_t* pEntry);               // 0x00c02650

    uint8_t mPad000[0x18];                      // 0x000
};

class cAnimIterator {
public:
    cAnimIterator* Advance();

    uint8_t** mppCurrent;                       // 0x000
    uint8_t** mppEnd;                           // 0x004
    cAnimFilter mFilter;                        // 0x008
};

class cForageList {
public:
    uint8_t mPad000[0x68];                      // 0x000
    uint8_t* mpBegin;                           // 0x068
    uint8_t* mpEnd;                             // 0x06c
    uint8_t mPad070[0x10];                      // 0x070
    uint32_t mnIndex;                           // 0x080
};

class cPlanetModel {
public:
    cSPVector3* GetPosition();                  // 0x00b81630
};

class cStateBlock {
public:
    float mfField000;                           // 0x000
    float mfField004;                           // 0x004
    float mfField008;                           // 0x008
    float mfField00C;                           // 0x00c
    uint32_t mhAnimation;                       // 0x010
    uint8_t mbField014;                         // 0x014
    uint8_t mPad015[0x03];                      // 0x015
};

struct cStimulusSlot {
    uint8_t mPad000[0x24];                      // 0x000
    int32_t mnValue;                            // 0x024
    uint8_t mPad028[0x1c];                      // 0x028
};

struct cStimulusTable {
    cStimulusSlot mSlots[4];                    // 0x000
    uint8_t mbInitialized;                      // 0x110
};

cGameModeObject g_gameMode;
cGameStateObject* g_pGameState = nullptr;
cRandomLinearCongruential g_random;
cStimulusTable g_stimulusTable;
cSPVector3 g_vStimulusPosition;
cSPVector3 g_vCharmedFocus;

float g_fCelebrateStretch = 1.0f;
float g_fCelebrateRate = 1.0f;
float g_fCelebratePhase = 1.0f;
float g_fCelebrateFreq = 6.2831855f;
float g_fCelebrateMinScale = 1.0f;
float g_fCelebrateMaxScale = 1.0f;
float g_fHeldPanicSpeed = 5.0f;
float g_fChaseTimerStart = 30.0f;
float g_fZero = 0.0f;
float g_fOne = 1.0f;
float g_fTwo = 2.0f;
float g_fMineAlertRadius = 20.0f;
float g_fMineSpeedThreshold = 0.5f;
float g_fMineNearRadius = 5.0f;
float g_fMineInteractRadius = 3.0f;

void* GetCurrentGameMode();                     // 0x00b5b800
int32_t FUN_00efe5c0();                         // 0x00efe5c0
cSpriteEffect* FUN_00d51660();                  // 0x00d51660
void* GetAnimalFromStimulus(void* pStimulus);   // 0x00d99980
void __stdcall FUN_00bc9a30(int32_t nA, void* pTable);    // 0x00bc9a30
void* __stdcall FUN_00bc9b00(uint32_t nId, void* pFn, void* pArg);   // 0x00bc9b00
void* FUN_00d995c0(int32_t nA, int32_t nB, void* pArg);    // 0x00d995c0
cGameNounManager* NounManager();                // 0x00b3d300
cMessageServer* MessageServer();                // 0x0067dcc0
void* __stdcall PlanetModel(void* pOut, const void* pElement);   // 0x00b3d350
void FUN_00d7cdd0(cCreatureBase* pCreature, uint32_t* pState);

// ---------------------------------------------------------------------------
// 0x00d7c3e0  SP::CELEBRATE_BRAIN_UPGRADE_Tick
// ---------------------------------------------------------------------------
// @ 0x00d7c3e0
bool FUN_00d7c3e0(cCreatureBase* pCreature, int32_t nArg2, int32_t nArg3, int32_t nArg4,
                  int32_t nArg5, cStateBlock* pState, float fDelta)
{
    if (pState->mhAnimation == 0) {
        pState->mhAnimation = (uint32_t)pCreature->InterruptAnimation(0x5405ea0, -1, 0);
    }
    else if (pCreature->AnimationFinished(pState->mhAnimation)) {
        cMessageServer* pServer = MessageServer();
        pServer->Send(0x445f729, 0, 0);
        return false;
    }

    if (pState->mbField014 == 0) {
        if (pCreature->WaitForAnimEventOrEnd(0x280852e4, &pState->mhAnimation, -1, 0, 1))
            pState->mbField014 = 1;
        else
            pState->mfField00C = pState->mfField00C - fDelta;

        if (pState->mbField014 == 0)
            return true;
    }

    float fProgress = pState->mfField008;
    float fTotal = pState->mfField00C;
    pState->mfField008 = fDelta + fProgress;

    float fFraction = fTotal - (fDelta + fProgress) * g_fCelebrateStretch;
    if (fFraction <= 0.0f)
        fFraction = 0.0f;
    if (fTotal <= fFraction)
        fFraction = fTotal;
    float fFractionRatio = fFraction / pState->mfField00C;

    float fPhase = g_fCelebratePhase - g_fCelebrateRate * pState->mfField008;
    if (fPhase <= 0.0f)
        fPhase = 0.0f;
    if (g_fCelebratePhase <= fPhase)
        fPhase = g_fCelebratePhase;

    float fInvTotal = 1.0f / pState->mfField00C;
    float fWave = -(sinf((pState->mfField008 * fInvTotal) * g_fCelebrateFreq * fPhase) *
                    fFractionRatio);

    float fScale = g_fCelebrateMinScale;
    if (fWave < g_fZero) {
        fScale = ((pState->mfField00C - pState->mfField008) * fInvTotal) *
                 g_fCelebrateMaxScale;
        if (fScale <= 0.1f)
            fScale = 0.1f;
        if (g_fCelebrateMaxScale <= fScale)
            fScale = g_fCelebrateMaxScale;
    }

    fScale = fScale * fWave;
    if (fFractionRatio <= 0.0f)
        fScale = g_fZero;

    pCreature->mLocomotive.SetSpeed((pState->mfField000 - pState->mfField004) * fScale +
                                    pState->mfField000);

    return true;
}

// ---------------------------------------------------------------------------
// 0x00d7c5e0  celebrate brain upgrade exit
// ---------------------------------------------------------------------------
// @ 0x00d7c5e0
void FUN_00d7c5e0(cCreatureBase* pCreature, int32_t nArg2, int32_t nArg3, int32_t nArg4,
                  int32_t nArg5, float* pfValue)
{
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0, 0x1000);
    pCreature->mLocomotive.SetSpeed(*pfValue);
}

// ---------------------------------------------------------------------------
// 0x00d7c620  SP::HELD_PANIC_Tick
// ---------------------------------------------------------------------------
// @ 0x00d7c620
bool FUN_00d7c620(cCreatureBase* pCreature)
{
    uint32_t nFlags = pCreature->mnFlags110;

    if ((nFlags & 0x100) != 0) {
        if (!pCreature->HasAnimation(0x48601c0))
            pCreature->PlayAnimation(0x48601c0, 1, -1);
        return true;
    }

    if (pCreature->mbField137 == 0 && (nFlags & 0x1000) == 0) {
        if (!pCreature->HasAnimation(0x493840c))
            pCreature->PlayAnimation(0x493840c, 1, -1);
        return true;
    }

    pCreature->AddWalkSpeed(g_fHeldPanicSpeed);
    return false;
}

// ---------------------------------------------------------------------------
// 0x00d7c6b0  held panic exit
// ---------------------------------------------------------------------------
// @ 0x00d7c6b0
void FUN_00d7c6b0(cCreatureBase* pCreature)
{
    pCreature->Hover(0);

    if (pCreature->mbFieldB5E == 0) {
        pCreature->FUN_00c14750(0);
        pCreature->SetAnimState(nullptr, 0, 0);
    }
}

// ---------------------------------------------------------------------------
// 0x00d7c6f0  SP::SHOCKED_Activate
// ---------------------------------------------------------------------------
// @ 0x00d7c6f0
bool FUN_00d7c6f0(cCreatureBase* pCreature, int32_t nArg2, int32_t nArg3, int32_t nArg4,
                  int32_t nArg5, uint32_t* phAnim)
{
    void* pStimulus = pCreature->mpBehaviorTree->mStimuli.Play(0, 0x800);
    void* pAnimal = GetAnimalFromStimulus(pStimulus);

    if (pStimulus != nullptr) {
        if (pAnimal != nullptr)
            pCreature->SetAnimState((cCombatant*)((uint8_t*)pAnimal + 0x5a8), 1, 0);

        *phAnim = (uint32_t)pCreature->InterruptAnimation(0xd37174e6, -1, 0);
        pCreature->FUN_00c1d460(0x3e2b4e6c, 0x3e2b4e6c);
        return true;
    }

    return false;
}

// ---------------------------------------------------------------------------
// 0x00d7c770  shocked exit
// ---------------------------------------------------------------------------
// @ 0x00d7c770
void FUN_00d7c770(cCreatureBase* pCreature)
{
    pCreature->SetAnimState(nullptr, 0, 0);
    pCreature->FUN_00c17350(0x3e2b4e6c, 0);
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0, 0x800);
}

// ---------------------------------------------------------------------------
// 0x00d7c7b0  shocked wait condition
// ---------------------------------------------------------------------------
// @ 0x00d7c7b0
bool FUN_00d7c7b0(cCreatureBase* pCreature, int32_t nArg2, int32_t nArg3, int32_t nArg4,
                  int32_t nArg5, uint32_t* phAnim)
{
    return !pCreature->AnimationFinished(*phAnim);
}

// ---------------------------------------------------------------------------
// 0x00d7c7d0  shocked resume
// ---------------------------------------------------------------------------
// @ 0x00d7c7d0
void FUN_00d7c7d0(cCreatureBase* pCreature)
{
    if (pCreature->mbFieldB5E == 0) {
        pCreature->FUN_00c14750(1);
        pCreature->SetAnimState(nullptr, 0, 0);
    }
}

// ---------------------------------------------------------------------------
// 0x00d7c800  shocked wait condition (integer form)
// ---------------------------------------------------------------------------
// @ 0x00d7c800
bool FUN_00d7c800(cCreatureBase* pCreature, int32_t nArg2, int32_t nArg3, int32_t nArg4,
                  int32_t nArg5, uint32_t* phAnim)
{
    return (pCreature->AnimationFinished(*phAnim) == false);
}

// ---------------------------------------------------------------------------
// 0x00d7c820  chase target activate
// ---------------------------------------------------------------------------
// @ 0x00d7c820
bool FUN_00d7c820(cCreatureBase* pCreature, int32_t nArg2, int32_t nArg3, int32_t nArg4,
                  int32_t nArg5, float* pfTimer)
{
    cNearNoun* pNearNoun = (cNearNoun*)pCreature->GetInRange(1.0f, 2.0f);
    float* pPosition = pNearNoun->GetPosition();
    pCreature->MoveToPointAtSpeed(2, pPosition);
    pCreature->SetStealthed(1, 1);
    *pfTimer = g_fChaseTimerStart;

    cSpriteEffect* pChase = FUN_00d51660();
    if (pChase != nullptr)
        pChase->Start(1);
    return true;
}

// ---------------------------------------------------------------------------
// 0x00d7c8d0  charmed condition
// ---------------------------------------------------------------------------
// @ 0x00d7c8d0
float FUN_00d7c8d0(cCreatureBase* pCreature)
{
    if (g_fZero < pCreature->mfRadius169C)
        return 1.0f;
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00d7c8f0  SP::CHARMED_Tick
// ---------------------------------------------------------------------------
// @ 0x00d7c8f0
bool FUN_00d7c8f0(cCreatureBase* pCreature)
{
    if (!(g_fZero < pCreature->mfRadius169C))
        return false;

    if (pCreature->mLocomotive.IsNearGoal()) {
        if (pCreature->AnimationFinishedById(0)) {
            uint32_t nAnim = g_random.RandomUint32Uniform(pCreature->mpData->mnAnimId, 1,
                                                          0xffffffff);
            pCreature->PlayAnimation(nAnim + 0x42a1ca0, 1, -1);
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x00d7c960  charmed activate
// ---------------------------------------------------------------------------
// @ 0x00d7c960
void FUN_00d7c960(cCreatureBase* pCreature)
{
    pCreature->SetAnimState(nullptr, 0, 0);
    pCreature->FUN_00c14750(1);
    pCreature->AbortAnimation(-1);
    pCreature->SetFocusTarget(&g_vCharmedFocus);
    pCreature->FUN_00c0d950(0);
}

// ---------------------------------------------------------------------------
// 0x00d7c9b0  charmed exit
// ---------------------------------------------------------------------------
// @ 0x00d7c9b0
void FUN_00d7c9b0(cCreatureBase* pCreature)
{
    pCreature->AbortAnimation(-1);
    pCreature->SetFocusTarget(&g_vCharmedFocus);
    pCreature->FUN_00c0d950(0);
}

// ---------------------------------------------------------------------------
// 0x00d7c9e0  charmed condition
// ---------------------------------------------------------------------------
// @ 0x00d7c9e0
float FUN_00d7c9e0(cCreatureBase* pCreature, int32_t nArg2, int32_t nArg3, int32_t nArg4,
                   cStimulus* pStimulus, uint8_t* pbOut)
{
    if (pCreature->mfRadius169C < 2.0f) {
        if (pStimulus != nullptr)
            pStimulus->GetAny();

        *pbOut = 1;
        pStimulus->mnField18 = pCreature->Flag388() ? (int32_t)0x924525ac + 0x74339a43
                                                    : 0x74339a43;
        pStimulus->mnField1C = 1;
        pStimulus->mnField20 = 0;
        pStimulus->mPosition = g_vStimulusPosition;
        return 1.0f;
    }

    return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00d7ca60  charmed deactivate
// ---------------------------------------------------------------------------
// @ 0x00d7ca60
void FUN_00d7ca60(cCreatureBase* pCreature)
{
    pCreature->SetAnimState(nullptr, 0, 0);
    pCreature->FUN_00c0b370(-1);
    pCreature->FUN_00c14750(1);
}

// ---------------------------------------------------------------------------
// 0x00d7ca90  stimulus table setup
// ---------------------------------------------------------------------------
// @ 0x00d7ca90
void FUN_00d7ca90(cCreatureBase* pCreature)
{
    int32_t nInitialized = 1;

    if (!g_stimulusTable.mbInitialized) {
        g_stimulusTable.mbInitialized = (uint8_t)nInitialized;
        g_stimulusTable.mSlots[0].mnValue = 0;
        g_stimulusTable.mSlots[1].mnValue = nInitialized;
        g_stimulusTable.mSlots[2].mnValue = 2;
        g_stimulusTable.mSlots[3].mnValue = 3;
    }

    void* pController = pCreature->mpFieldB48;
    if (pController != nullptr)
        FUN_00bc9a30(nInitialized, &g_stimulusTable);
}

// ---------------------------------------------------------------------------
// 0x00d7cb20  behaviour flag test
// ---------------------------------------------------------------------------
// @ 0x00d7cb20
int32_t FUN_00d7cb20(cCreatureBase* pCreature)
{
    if ((pCreature->mpBehaviorTree->mStimuli.mnField1C0 & 4) != 0)
        return 1;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00d7cb50  hover state refresh
// ---------------------------------------------------------------------------
// @ 0x00d7cb50
void FUN_00d7cb50(cCreatureBase* pCreature)
{
    if (pCreature->mbFieldB5E == 0)
        pCreature->FUN_00c14750(pCreature->mLocomotive.IsMoving() == false);
}

// ---------------------------------------------------------------------------
// 0x00d7cb90  SP::NEST_UPGRADE_Tick
// ---------------------------------------------------------------------------
// @ 0x00d7cb90
int32_t FUN_00d7cb90(cCreatureBase* pCreature, int32_t nArg2, int32_t nArg3, int32_t nArg4,
                     int32_t nArg5, float* pfTimer, int32_t nArg7, float fDelta)
{
    if (pCreature->mLocomotive.IsNearGoal()) {
        *pfTimer = *pfTimer - fDelta;

        if (!pCreature->HasAnimation(0xf14faa34))
            pCreature->PlayAnimation(0xf14faa34, 1, -1);

        return (0.0f < *pfTimer) ? 1 : 0;
    }

    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d7cc00  tribe tool condition
// ---------------------------------------------------------------------------
// @ 0x00d7cc00
float FUN_00d7cc00(int32_t nToolId)
{
    if (GetCurrentGameMode() == &g_gameMode && g_pGameState->mnField0CC == 1) {
        if (FUN_00efe5c0() == nToolId)
            return 1.0f;
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00d7cc30  play tool animation
// ---------------------------------------------------------------------------
// @ 0x00d7cc30
bool FUN_00d7cc30(cCreatureBase* pCreature)
{
    pCreature->InterruptAnimation(0x7c7b2f5, -1, 0);
    return true;
}

// ---------------------------------------------------------------------------
// 0x00d7cc50  play tool animation (no result)
// ---------------------------------------------------------------------------
// @ 0x00d7cc50
void FUN_00d7cc50(cCreatureBase* pCreature)
{
    pCreature->InterruptAnimation(0x7c7af05, -1, 0);
}

// ---------------------------------------------------------------------------
// 0x00d7cc70  tribe tool condition (integer form)
// ---------------------------------------------------------------------------
// @ 0x00d7cc70
bool FUN_00d7cc70(int32_t nToolId)
{
    if (GetCurrentGameMode() == &g_gameMode && g_pGameState->mnField0CC == 1) {
        if (FUN_00efe5c0() == nToolId)
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00d7cca0  creature focus condition
// ---------------------------------------------------------------------------
// @ 0x00d7cca0
float FUN_00d7cca0(cCreatureBase* pCreature)
{
    if (GetCurrentGameMode() == &g_gameMode && g_pGameState->mnField0CC == 1) {
        cNearNoun* pNearNoun = (cNearNoun*)pCreature->GetFocusTarget();
        if (pNearNoun != nullptr && pNearNoun->mbField002 != 0)
            return 1.0f;
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00d7cce0  nest upgrade animation
// ---------------------------------------------------------------------------
// @ 0x00d7cce0
bool FUN_00d7cce0(cCreatureBase* pCreature)
{
    pCreature->InterruptAnimation(0xf14faa46, -1, 1);
    return true;
}

// ---------------------------------------------------------------------------
// 0x00d7cd00  creature focus condition (integer form)
// ---------------------------------------------------------------------------
// @ 0x00d7cd00
bool FUN_00d7cd00(cCreatureBase* pCreature)
{
    if (GetCurrentGameMode() == &g_gameMode && g_pGameState->mnField0CC == 1) {
        cNearNoun* pNearNoun = (cNearNoun*)pCreature->GetFocusTarget();
        if (pNearNoun != nullptr && pNearNoun->mbField002 != 0)
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00d7cd40  story mode condition
// ---------------------------------------------------------------------------
// @ 0x00d7cd40
float FUN_00d7cd40()
{
    if (GetCurrentGameMode() == &g_gameMode && g_pGameState->mnField0CC == 1)
        return 1.0f;
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00d7cd80  nest upgrade activate
// ---------------------------------------------------------------------------
// @ 0x00d7cd80
bool FUN_00d7cd80(cCreatureBase* pCreature, int32_t nArg2, int32_t nArg3, int32_t nArg4,
                  int32_t nArg5, uint32_t* phAnim)
{
    if (!(GetCurrentGameMode() == &g_gameMode && g_pGameState->mnField0CC == 1))
        return false;

    if (pCreature->FUN_00c0e2c0(*phAnim))
        *phAnim = (uint32_t)pCreature->PlayAnimation(0x7c7a9f7, 0, -1);
    return true;
}

// ---------------------------------------------------------------------------
// 0x00d7cdd0  nest upgrade state selection
// ---------------------------------------------------------------------------
// @ 0x00d7cdd0
void FUN_00d7cdd0(cCreatureBase* pCreature, uint32_t* pState)
{
    if (pCreature->Flag388()) {
        pState[1] = 2;
        *pState = (uint32_t)pCreature->InterruptAnimation(0x7c7a30d, -1, 0);
        return;
    }

    if (!pCreature->FUN_00c0b770()) {
        pState[1] = 0;
        *pState = (uint32_t)pCreature->InterruptAnimation(0x7c7a30c, -1, 0);
        return;
    }

    pState[1] = 1;
    *pState = (uint32_t)pCreature->InterruptAnimation(0x7c7a30b, -1, 0);
}

// ---------------------------------------------------------------------------
// 0x00d7ce70  clear nest stimuli
// ---------------------------------------------------------------------------
// @ 0x00d7ce70
void FUN_00d7ce70(cCreatureBase* pCreature)
{
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0, 0x200000);
}

// ---------------------------------------------------------------------------
// 0x00d7ce90  nest upgrade condition
// ---------------------------------------------------------------------------
// @ 0x00d7ce90
bool FUN_00d7ce90(cCreatureBase* pCreature, int32_t nArg2, int32_t nArg3, int32_t nArg4,
                  int32_t nArg5, uint32_t* pState)
{
    if (pCreature->AnimationFinished(*pState))
        return false;

    if (pCreature->Flag388()) {
        if (pState[1] == 2)
            return true;
    }
    else {
        if (pCreature->FUN_00c0b770() && pState[1] != 1) {
            FUN_00d7cdd0(pCreature, pState);
            return true;
        }
        if (pCreature->FUN_00c0b770())
            return true;
        if (pState[1] == 0)
            return true;
    }

    FUN_00d7cdd0(pCreature, pState);
    return true;
}

// ---------------------------------------------------------------------------
// 0x00d7cef0  nest upgrade damage reaction
// ---------------------------------------------------------------------------
// @ 0x00d7cef0
void FUN_00d7cef0(cCreatureBase* pCreature)
{
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0, 0x20000);

    if (pCreature->mCombatant.GetFileCount() == 2) {
        pCreature->mbField166D = 1;
        pCreature->InterruptAnimation(pCreature->Flag388() ? 0x7a96805 : 0x7a96801, -1, 0);
        return;
    }

    pCreature->FUN_00c14750(0);
}

// ---------------------------------------------------------------------------
// 0x00d7cf50  cAnimIterator::Advance
// ---------------------------------------------------------------------------
// @ 0x00d7cf50
cAnimIterator* cAnimIterator::Advance()
{
    do {
        mppCurrent = mppCurrent + 1;
        if (mppCurrent == mppEnd)
            break;
    } while (!mFilter.Accept(*mppCurrent));

    return this;
}

// ---------------------------------------------------------------------------
// 0x00d7cfb0  SP::FindForageDestination
// ---------------------------------------------------------------------------
// @ 0x00d7cfb0
bool FindForageDestination(cCreatureBase* pCreature, cSPVector3* pOut)
{
    uint8_t aLocal[12];

    cForageList* pList = (cForageList*)pCreature->Get();
    if (pList != nullptr) {
        if (pList->mnIndex < (uint32_t)((int32_t)(pList->mpEnd - pList->mpBegin) / 12)) {
            uint8_t* pElement = pList->mpBegin + pList->mnIndex * 12;
            cPlanetModel* pModel = (cPlanetModel*)PlanetModel(aLocal, pElement);
            *pOut = *pModel->GetPosition();
            return true;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------
// 0x00d7d020  mine proximity test
// ---------------------------------------------------------------------------
// @ 0x00d7d020
bool FUN_00d7d020(cCreatureBase* pCreature)
{
    cCreatureBase* pAvatar = (cCreatureBase*)NounManager()->GetAvatar();
    if (pAvatar == nullptr)
        return false;

    float* pMinePosition = pCreature->mLocomotive.GetPosition();
    float* pAvatarPosition = pAvatar->mLocomotive.GetPosition();

    float fDx = pAvatarPosition[0] - pMinePosition[0];
    float fDy = pAvatarPosition[1] - pMinePosition[1];
    float fDz = pAvatarPosition[2] - pMinePosition[2];
    float fDistanceSq = fDz * fDz + fDx * fDx + fDy * fDy;

    if (!(fDistanceSq < g_fMineAlertRadius * g_fMineAlertRadius))
        return false;

    float* pVelocity = pAvatar->mLocomotive.GetVelocity();
    float fSpeedSq = pVelocity[2] * pVelocity[2] + pVelocity[1] * pVelocity[1] +
                     pVelocity[0] * pVelocity[0];

    bool bApproaching = false;
    if (fSpeedSq > g_fMineSpeedThreshold) {
        float fDot = pVelocity[2] * fDz + pVelocity[0] * fDx + pVelocity[1] * fDy;
        if (fDot > g_fZero)
            bApproaching = true;
    }

    bool bClose = (g_fMineNearRadius * g_fMineNearRadius) > fDistanceSq;

    if (!bApproaching || bClose)
        return true;
    return false;
}

// ---------------------------------------------------------------------------
// 0x00d7d160  mine interact test
// ---------------------------------------------------------------------------
// @ 0x00d7d160
bool FUN_00d7d160(cCreatureBase* pCreature)
{
    if (!FUN_00d7d020(pCreature))
        return false;

    cCreatureBase* pAvatar = (cCreatureBase*)NounManager()->GetAvatar();
    if (pAvatar == nullptr)
        return false;

    void* aQuery[2];
    aQuery[0] = (pCreature != nullptr) ? (void*)&pCreature->mCombatant : nullptr;
    aQuery[1] = nullptr;

    void* pManager = FUN_00bc9b00(0x60995fc, (void*)FUN_00d995c0, aQuery);
    cOrderNode* pNode = ((cOrderManager*)pManager)->FindNode();
    cCreatureBase* pTarget = pCreature->ApplyCombatTarget();

    if (pNode != nullptr) {
        float fDistance = pCreature->mCombatant.GetTargetDistance();
        if (fDistance < g_fMineInteractRadius) {
            if (pNode->mnField10 > 1)
                return false;
            if (pTarget != nullptr && pTarget->mCombatant.mfHealth > pCreature->mCombatant.mfHealth)
                return false;
        }
    }

    return true;
}

// ---------------------------------------------------------------------------
// 0x00d7d220  tribe tool enter
// ---------------------------------------------------------------------------
// @ 0x00d7d220
void FUN_00d7d220(cCreatureBase* pCreature, void* pTool)
{
    pCreature->mnFlags050 = pCreature->mnFlags050 | 0x100;
    pCreature->mbField077 = 0;

    cCreaturePart* pToolPart = (cCreaturePart*)pCreature->FindPart(0x398420d);
    if (pToolPart != nullptr)
        pToolPart->EnterToolMode(pTool);

    cCreaturePart* pHandPart = (cCreaturePart*)pCreature->FindPart(0x116dd1b);
    if (pHandPart != nullptr) {
        pHandPart->mbField268 = 0;
        pHandPart->SetStimulusTarget(&g_vStimulusPosition);
        pHandPart->mnField1F0 = 3;
    }

    if (GetCurrentGameMode() == &g_gameMode) {
        cCreaturePart* pFakePart = (cCreaturePart*)pCreature->FindPart(0x17f243b);
        if (pFakePart != nullptr)
            ((cToolController*)g_pGameState->mpField078)->OnToolEnter(pTool, pFakePart);
    }
}

// ---------------------------------------------------------------------------
// 0x00d7d2c0  tribe tool exit
// ---------------------------------------------------------------------------
// @ 0x00d7d2c0
void FUN_00d7d2c0(cCreatureBase* pCreature, void* pTool)
{
    pCreature->mnFlags050 = pCreature->mnFlags050 & 0xfffffeff;

    cCreaturePart* pToolPart = (cCreaturePart*)pCreature->FindPart(0x398420d);
    if (pToolPart != nullptr)
        pToolPart->ExitToolMode(pTool);

    cCreaturePart* pHandPart = (cCreaturePart*)pCreature->FindPart(0x116dd1b);
    if (pHandPart != nullptr) {
        if (pCreature->FindPart(0xce9f6639) == nullptr)
            pHandPart->mbField268 = 1;
        pHandPart->mbField077 = 0;
        pHandPart->mnField1F0 = 3;
    }

    if (GetCurrentGameMode() == &g_gameMode) {
        cCreaturePart* pFakePart = (cCreaturePart*)pCreature->FindPart(0x17f243b);
        if (pFakePart != nullptr)
            ((cToolController*)g_pGameState->mpField078)->OnToolExit(pTool, pFakePart);
    }
}
