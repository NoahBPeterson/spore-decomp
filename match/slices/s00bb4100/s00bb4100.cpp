typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;
typedef unsigned char uint8_t;

namespace SP {

struct cSPGameDataUFO;

// 0x00dc-0x00e4 range: vector of cSPGameDataUFO*
struct cUFOList {
    cSPGameDataUFO** mpBegin;                              // +0x00
    cSPGameDataUFO** mpEnd;                                // +0x04
    cSPGameDataUFO** mpCapacity;                           // +0x08

    cSPGameDataUFO** Find(const cSPGameDataUFO* p) const
    {
        cSPGameDataUFO** it = mpBegin;
        while (it != mpEnd) {
            if (*it == p)
                return it;
            ++it;
        }
        return it;
    }

    void erase(cSPGameDataUFO** it);                       // 0x00bf3420
};

struct cSPGameDataUFO {
    uint32_t mField00;                                     // +0x00
    uint32_t mField04;                                     // +0x04
    uint32_t mField08;                                     // +0x08
    uint32_t mTimeMs;                                      // +0x0c
    uint32_t mPad10[39];                                   // +0x10
    uint8_t  mbFlagAC;                                     // +0xac

    int  AddRef();                                         // 0x00801920
    void FUN_00bb9ad0(void* p);                            // 0x00bb9ad0
    void FUN_00bb9b00(int a, int b);                       // 0x00bb9b00
    void FUN_00bba500();                                   // 0x00bba500
};

struct cGameTime;

struct cStarManager {
    uint32_t mPad00[0x37];                                 // +0x000
    cUFOList mPlanets;                                     // +0x0dc

    void ActivatePlanetRecordsForQuery(cSPGameDataUFO* pUFO, int param3);
    void* FUN_00bb3800(int v);                             // 0x00bb3800
    void  FUN_00bb4100(cSPGameDataUFO* pUFO, int a, int b); // 0x00bb4100
};

cGameTime* GameTimeManager();                              // 0x00b3d380

}  // namespace SP

bool FUN_00c8b520(int refCount);                           // 0x00c8b520

struct SP_cGameTime {
    uint64_t FUN_00b316c0();                               // 0x00b316c0
};

uint64_t SP_cGameTime_getTime(void* self);

// @ 0x00bb4af0
void SP::cStarManager::ActivatePlanetRecordsForQuery(cSPGameDataUFO* pUFO, int param3)
{
    if (pUFO->mbFlagAC != 0)
        return;
    if (!FUN_00c8b520(pUFO->AddRef()))
        return;
    pUFO->mTimeMs = (uint32_t)(((SP_cGameTime*)GameTimeManager())->FUN_00b316c0() / 60000);
    cSPGameDataUFO** end = mPlanets.mpEnd;
    cSPGameDataUFO** it = mPlanets.mpBegin;
    while (it != end && *it != pUFO)
        ++it;
    if (it != mPlanets.mpEnd) {
        mPlanets.erase(it);
        pUFO->FUN_00bb9ad0(FUN_00bb3800(0));
    }
    pUFO->FUN_00bb9b00(1, 0);
    pUFO->FUN_00bba500();
    FUN_00bb4100(pUFO, param3, 0);
}
