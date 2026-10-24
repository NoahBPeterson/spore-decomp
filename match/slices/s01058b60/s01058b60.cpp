// s01058b60 - colony tool strategy (gold6 worker 36)
typedef unsigned int uint32_t;

inline void* operator new(unsigned int, void* pWhere) { return pWhere; }

float sqrtf_c(float fValue);

// ---------------------------------------------------------------------------
// Foreign objects
// ---------------------------------------------------------------------------
class cGameNounManager {
public:
    void* GetGameDataVector(uint32_t nFilter, uint32_t nTypeA, uint32_t nTypeB,
                            uint32_t nTypeC, const void* pFilterData);   // 0x00b21340
};

cGameNounManager* NounManager();                                     // 0x00b3d300

struct cGameDataList {
    uint32_t mnUnk00;                                               // 0x00
    void** mpBegin;                                                 // 0x04
    void** mpEnd;                                                   // 0x08
};

// ---------------------------------------------------------------------------
// Bubble list carried by every object that can show a colony bubble
// ---------------------------------------------------------------------------
struct cVector3 {
    float x;                                                        // 0x00
    float y;                                                        // 0x04
    float z;                                                        // 0x08
};

struct cEmptyBubble {
    cVector3 mPosition;                                             // 0x00
    float mfFade;                                                   // 0x0c
    int mnFlags;                                                    // 0x10

    cEmptyBubble() : mfFade(0.0f), mnFlags(0) {}
};

class cBubbleVector {
public:
    cEmptyBubble* mpBegin;                                          // 0x00
    cEmptyBubble* mpEnd;                                            // 0x04
    cEmptyBubble* mpCapacity;                                       // 0x08

    void push_back()
    {
        if (mpEnd < mpCapacity) {
            cEmptyBubble* pSlot = mpEnd++;
            if (pSlot != 0)
                new (pSlot) cEmptyBubble();
        } else {
            cEmptyBubble value;
            DoInsertValue(mpEnd, &value);
        }
    }

    void DoInsertValue(cEmptyBubble* pEnd,
                       const cEmptyBubble* pValue);                 // 0x00bde910
};

struct cBubbleSource {
    void* mpVtable;                                                 // 0x00
};

class cGameObject {
public:
    uint32_t mUnk000[0x45];                                         // 0x000
    void* mpUnk114;                                                 // 0x114
    uint32_t mUnk118[2];                                            // 0x118
    cBubbleSource mBubbleSource;                                    // 0x120
    uint32_t mUnk124[0x65];                                         // 0x124
    cBubbleVector mBubbles;                                         // 0x2b8
    uint32_t mUnk2c4[2];                                            // 0x2c4
    uint32_t mnUnk2cc;                                              // 0x2cc
    uint32_t mnUnk2d0;                                              // 0x2d0
};

extern float gEmptyBubbleFade;                                      // 0x013ec5b4
extern const void* gDataFilter;                                     // 0x018c43e8
extern const void* gTribeDataFilter;                                // 0x018c6d19
extern void* gInteractionAgentTypeInfo;                             // 0x013f94d4

// tool strategy base
class cSPToolStrategy {
public:
    bool StartTool(uint32_t nArg1, uint32_t nArg2, uint32_t* pnResult);   // 0x010568b0
    bool CanUseTool(uint32_t nArg1, uint32_t nArg2, uint32_t* pnResult);  // 0x010568b0
};

int  ToolStrategy_IsValid();                                        // 0x01021230
int  ToolStrategy_GetCount();                                       // 0x00c8b5a0
int  ToolStrategy_GetOwner();                                       // 0x00c8b5b0
int  ToolStrategy_GetLimit();                                       // 0x00bbe470
void cSPLivingUniverse_GetPlayerEmpire();
int  cSPLivingUniverse_GetActivePlanetRecord();                     // 0x01021260
void ToolStrategy_Fail(uint32_t nArg1, uint32_t nReason, uint32_t nArg2);  // 0x010527f0
uint32_t ToolStrategy_MakeResult(uint32_t nReason);                 // 0x0104c4f0
float ToolStrategy_GetRadius();                                     // 0x0104bdc0
int  ToolStrategy_GetTargetId();                                    // 0x0104bd80
float ToolStrategy_GetScore(uint32_t nId);                          // 0x00ce6930
void ToolStrategy_SpawnBubble(float* pPosition, float fScore, uint32_t nId);  // 0x00bdff50

class cSPPlaceColonyToolStrategy : public cSPToolStrategy {
public:
    bool CanUseTool(uint32_t nArg1, uint32_t nArg2, uint32_t* pnResult);
    bool StartTool(uint32_t nArg1, uint32_t nArg2, uint32_t* pnResult);
};

class cTribe {
public:
    void* mpUnk114;                                                 // 0x114
    cBubbleSource mBubbleSource;                                    // 0x120
};

// ---------------------------------------------------------------------------
// 0x01058b60  cSPPlaceColonyToolStrategy::CanUseTool
// ---------------------------------------------------------------------------
// @ 0x01058b60
bool cSPPlaceColonyToolStrategy::CanUseTool(uint32_t nArg1, uint32_t nArg2,
                                            uint32_t* pnResult)
{
    if (!cSPToolStrategy::CanUseTool(nArg1, nArg2, pnResult))
        return false;
    int nTarget = ToolStrategy_IsValid();
    if (nTarget != 0 && ToolStrategy_GetCount() > 1) {
        int nOwner = ToolStrategy_GetOwner();
        if (ToolStrategy_GetOwner() != nOwner)
            return false;
    }
    cGameNounManager* pNounManager = NounManager();
    cGameDataList* pData = (cGameDataList*)pNounManager->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00acdff0, 0x00b1e500, &gDataFilter);
    int nCount = (int)((char*)pData->mpEnd - (char*)pData->mpBegin) >> 2;
    int nLimit = ToolStrategy_GetLimit();
    if (nCount >= 1 && nCount >= nLimit) {
        ToolStrategy_Fail(nArg1, 0xc4a882d7, nArg2);
        if (pnResult != 0)
            *pnResult = ToolStrategy_MakeResult(0x19);
        return false;
    }
    int nRecord = cSPLivingUniverse_GetActivePlanetRecord();
    if (nRecord == 0 || (nRecord & 0x800) == 0)
        return true;
    return false;
}

// ---------------------------------------------------------------------------
// 0x01059040  cSPPlaceColonyToolStrategy::StartTool
// ---------------------------------------------------------------------------
// @ 0x01059040
bool cSPPlaceColonyToolStrategy::StartTool(uint32_t nArg1, uint32_t nArg2,
                                           uint32_t* pnResult)
{
    if (cSPToolStrategy::StartTool(nArg1, nArg2, pnResult)) {
        cGameNounManager* pNounManager = NounManager();
        cGameDataList* pData = (cGameDataList*)pNounManager->GetGameDataVector(
            0x00cd7d10, 0x00d3d420, 0x00acdff0, 0x00b1e500, &gDataFilter);
        int nCount = (int)(pData->mpEnd - pData->mpBegin);
        for (unsigned int i = 0; i < (unsigned int)nCount; ++i) {
            cGameObject* pObject = (cGameObject*)pData->mpBegin[i];
            pObject->mBubbles.push_back();
            const cVector3* pPosition =
                ((const cVector3* (__thiscall*)(cBubbleSource*))
                     ((void**)pObject->mBubbleSource.mpVtable)[0x2c / 4])(
                    &pObject->mBubbleSource);
            pObject->mBubbles.mpEnd[-1].mPosition = *pPosition;
            pObject->mBubbles.mpEnd[-1].mfFade = gEmptyBubbleFade;
            pObject->mnUnk2d0 = 0;
            pObject->mnUnk2cc = 0;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x01059170  CreatePanicBubbleForTool
// ---------------------------------------------------------------------------
// @ 0x01059170
void CreatePanicBubbleForTool(uint32_t nTool, float fX, float fY, float fZ)
{
    if (ToolStrategy_GetRadius() <= 0.0f)
        return;
    cGameNounManager* pNounManager = NounManager();
    cGameDataList* pData = (cGameDataList*)pNounManager->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00acdff0, 0x00b1e500, &gDataFilter);
    int nCount = (int)((char*)pData->mpEnd - (char*)pData->mpBegin) >> 2;
    for (int i = 0; i < nCount; ++i) {
        cGameObject* pObject = (cGameObject*)pData->mpBegin[i];
        const cVector3* pPosition =
            ((const cVector3* (__thiscall*)(cBubbleSource*))
                 ((void**)pObject->mBubbleSource.mpVtable)[0x2c / 4])(
                &pObject->mBubbleSource);
        float fDX = pPosition->x - fX;
        float fDY = pPosition->y - fY;
        float fDZ = pPosition->z - fZ;
        if (sqrtf_c(fDX * fDX + fDY * fDY + fDZ * fDZ) < 100.0f) {
            uint32_t nId = ToolStrategy_GetTargetId();
            ToolStrategy_SpawnBubble(&fX, ToolStrategy_GetScore(nId), nId);
        }
    }
    pNounManager = NounManager();
    pData = (cGameDataList*)pNounManager->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00accbb0, 0x00b1e500, &gTribeDataFilter);
    nCount = (int)((char*)pData->mpEnd - (char*)pData->mpBegin) >> 2;
    for (int i = 0; i < nCount; ++i) {
        cTribe* pTribe = (cTribe*)pData->mpBegin[i];
        const cVector3* pPosition =
            ((const cVector3* (__thiscall*)(cBubbleSource*))
                 ((void**)pTribe->mBubbleSource.mpVtable)[0x2c / 4])(
                &pTribe->mBubbleSource);
        float fDX = pPosition->x - fX;
        float fDY = pPosition->y - fY;
        float fDZ = pPosition->z - fZ;
        if (sqrtf_c(fDX * fDX + fDY * fDY + fDZ * fDZ) < 100.0f) {
            uint32_t nId = ToolStrategy_GetTargetId();
            ToolStrategy_SpawnBubble(&fX, ToolStrategy_GetScore(nId), nId);
        }
    }
}
