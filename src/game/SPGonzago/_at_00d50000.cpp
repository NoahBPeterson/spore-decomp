// src/game/SPGonzago/_at_00d50000.cpp -- migrated from slice(s) s00d56c30 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00d50000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cCity.h"
#include "SP/cCityVisualizer.h"
#include "SP/cDirectPropertyList.h"

// unnamed retail callees and globals (address in the comment)
extern bool g_bTribeQueueInit;                   // 0x0169ec24

// ---- items of slice s00d56c30 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
namespace EA {
struct RandomLinearCongruential {
    uint   RandomUint32Uniform(uint nRange);     // 0x00a68fb0
    double RandomDouble();                       // 0x009360d0
};
}
extern EA::RandomLinearCongruential g_random;    // 0x01601760
struct CGridQueue;                               // 0x01593270 (s_TribeQueue)
struct CModel {
    char mPad00[4];
    uint mFlags;                                 // +0x04, 0x800 = hidden
};
struct CAnimatingCreature {                      // CCitizen::mpAnim (+0xb54)
    char mPad00[0x64];
    bool mbField64;                              // +0x64
    char mPad65[0x180 - 0x65];
    CModel* mpModel;                             // +0x180
    bool Detach(int nMode);                      // 0x00a02b00
};
struct CVisualSub;                               // CCitizen sub-object at +0xc0
struct CCitizenBase {                            // virtual slots 0x00..0xe8
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
    virtual void SetState(int nState);                                               // +0x48
    virtual int  GetState();                                                         // +0x4c
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
virtual void s44();
virtual void s45();
virtual void s46();
virtual void s47();
virtual void s48();
virtual void s49();
virtual void s50();
virtual void s51();
virtual void s52();
virtual void s53();
virtual void s54();
virtual void s55();
    virtual void s56();                                                              // +0xe0
    virtual void SetInfo(void* pInfo);                                               // +0xe4
    virtual void InitFrom(void* pCity, int nMode, int nFlags, int nExtra);            // +0xe8
};
struct CVisualSub {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
    virtual void* Resolve();                                                         // +0x2c
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
    virtual void SetAngle(float fAngle);                                             // +0x40
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
    virtual void s21();                                                              // +0x54
    virtual bool IsReady();                                                          // +0x58
    char mData[0x4c];
};
struct CEntry {
    char mPad00[4];
    int  mnCount;                                // +0x04
    char mPad08[0x198 - 0x08];
};
struct CBehaviorOwner { char mData[0x68]; };
struct CGrid;
struct CTribe;
struct CCitizen : CCitizenBase {
    char mPad004[0x58 - 0x04];                   // +0x004
    CBehaviorOwner mBehavior;                    // +0x058
    CVisualSub mVisual;                          // +0x0c0
    uint mFlags;                                 // +0x110
    char mPad114[0xb4c - 0x114];
    CGrid* mpGrid;                               // +0xb4c
    char mPadB50[4];
    CAnimatingCreature* mpAnim;                  // +0xb54
    char mPadB58[0xf90 - 0xb58];
    bool mbFieldF90;                             // +0xf90
    char mPadF91[0xfb8 - 0xf91];
    CTribe* mpTribe;                             // +0xfb8
    bool mbFieldFBC;                             // +0xfbc
    char mPadFBD[0xff0 - 0xfbd];
    int  mnState;                                // +0xff0 (last state applied to the model)

    void SetSpecializedTool(int nTool);          // 0x00c279a0
    void SetFlag(int nFlag);                     // 0x00c0d950
    void UpdateEntry(int nEntry);                // 0x00c227a0
    void ClearEntry();                           // 0x00c227c0
};
struct CTribe {
    char mPad000[0x390];
    CEntry mEntries[4];                          // +0x390, stride 0x198
    char mPad9F0[0xaf0 - 0x9f0];
    void* mpCity;                                // +0xaf0

    CEntry* GetEntry(int nIndex);                // 0x00d576b0
};
struct CGridRange {
    char mData[0x14];
    void SetRange(uint nId, int nArg, float fMax, int nArg2);   // 0x00bc97f0
};
struct CGrid {
    char mPad00[8];
    CGridRange mRange;                           // +0x08
    char mPad1C[0x5fc - 0x1c];
    int  mnField5fc;                             // +0x5fc
    void ResetQueue(CGridQueue* pQueue);         // 0x00bcb660
    void ResetQueue();                           // 0x00bcb3d0
};
extern CGridQueue g_tribeQueue;                  // 0x01593270
extern bool g_bTribeQueueInit;                   // 0x0169ec24
void __cdecl GridInitQueue(CGridQueue* pQueue);                     // 0x00bc8fa0
void __cdecl UpdateTimeScaled(CCitizen* pCitizen);                  // 0x00c0d3a0
// ---- items of slice s00d56c30 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern EA::RandomLinearCongruential g_random;    // 0x01601760
extern CGridQueue g_tribeQueue;                  // 0x01593270

// @ 0x00d576b0
CEntry* CTribe::GetEntry(int nIndex)
{
    return &mEntries[nIndex];
}

// @ 0x00d576d0
void __cdecl SeedCitizenTool(CCitizen* pCitizen)
{
    if (!g_bTribeQueueInit) {
        GridInitQueue(&g_tribeQueue);
        g_bTribeQueueInit = true;
    }
    UpdateTimeScaled(pCitizen);
    pCitizen->mpGrid->ResetQueue(&g_tribeQueue);
    pCitizen->mpGrid->mRange.SetRange(0x1000, 0, 3.402823466e+38F, 0);
    pCitizen->SetSpecializedTool((int)g_random.RandomUint32Uniform(3) + 1);
}
