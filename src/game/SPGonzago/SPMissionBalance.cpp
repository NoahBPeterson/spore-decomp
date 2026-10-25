// src/game/SPGonzago/SPMissionBalance.cpp -- migrated from slice(s) s00c4a850 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionBalance.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameData.h"
#include "SP/cPlanet.h"
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cSPMission.h"
#include "SP/cStarManager.h"
#include "SP/cVarListSerializer.h"

// ---- items of slice s00c4a850 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ResourceKey {
    uint32_t mInstanceID;                                   // +0x00
    uint32_t mGroupID;                                      // +0x04
    uint32_t mTypeID;                                       // +0x08
};
template <class T>
struct cVec {
    T*       mpBegin;                                       // +0x00
    T*       mpEnd;                                         // +0x04
    T*       mpCapacity;                                    // +0x08
    void*    mpAllocator;                                   // +0x0c
    uint32_t mPad10;                                        // +0x10

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T&       operator[](uint32_t nIndex) const { return mpBegin[nIndex]; }

    void     push_back(const T& rValue)
    {
        if (mpEnd != mpCapacity) {
            T* pSlot = mpEnd;
            ++mpEnd;
            if (pSlot)
                *pSlot = rValue;
            return;
        }
        DoInsertValue(mpEnd, rValue);
    }

    void     DoInsertValue(T* pPos, const T& rValue);       // 0x00aea5d0
};
struct cPlanet {
    char     mPad000[0x13c];                                // +0x000
    void*    mpData13C;                                     // +0x13c
    char     mPad140[0x2c];                                 // +0x140
};
struct cPlanetRecord;
struct cProperty {
    void*     mpValue;                                      // +0x00
    uint32_t  mPad04;                                       // +0x04
    uint32_t  mCount;                                       // +0x08
    uint32_t  mPad0c;                                       // +0x0c
    uint16_t  mFlags;                                       // +0x10
    uint16_t  mType;                                        // +0x12

    bool*     GetBool();                                    // 0x0041e920
    int32_t*  GetInt();                                     // 0x0041e990
};
struct cPropertyList {
    virtual void        v00();                              // +0x00
    virtual void        v04();                              // +0x04
    virtual void        v08();                              // +0x08
    virtual void        v0c();                              // +0x0c
    virtual void        v10();                              // +0x10
    virtual void        v14();                              // +0x14
    virtual void        v18();                              // +0x18
    virtual void        v1c();                              // +0x1c
    virtual void        v20();                              // +0x20
    virtual bool        Find(uint32_t nKey, cProperty** ppOut);   // +0x24
    virtual cProperty*  Get(uint32_t nKey);                 // +0x28
};
struct cSPMission;
struct cSPMissionMultiDelivery;
struct cPlanetSearch;
struct cSPMission {
    // vtable +0x00 (slots used by this slice: +0x6c, +0x128, +0x16c, +0x170, +0x188)
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
    virtual void Abort();                                   // +0x06c
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual void v090();
virtual void v094();
virtual void v098();
virtual void v09c();
virtual void v0a0();
virtual void v0a4();
virtual void v0a8();
virtual void v0ac();
virtual void v0b0();
virtual void v0b4();
virtual void v0b8();
virtual void v0bc();
virtual void v0c0();
virtual void v0c4();
virtual void v0c8();
virtual void v0cc();
virtual void v0d0();
virtual void v0d4();
virtual void v0d8();
virtual void v0dc();
virtual void v0e0();
virtual void v0e4();
virtual void v0e8();
virtual void v0ec();
virtual void v0f0();
virtual void v0f4();
virtual void v0f8();
virtual void v0fc();
virtual void v100();
virtual void v104();
virtual void v108();
virtual void v10c();
virtual void v110();
virtual void v114();
virtual void v118();
virtual void v11c();
virtual void v120();
virtual void v124();
    virtual bool CheckTargetValid();                        // +0x128
virtual void v12c();
virtual void v130();
virtual void v134();
virtual void v138();
virtual void v13c();
virtual void v140();
virtual void v144();
virtual void v148();
virtual void v14c();
virtual void v150();
virtual void v154();
virtual void v158();
virtual void v15c();
virtual void v160();
virtual void v164();
virtual void v168();
    virtual void OnMissionStarted();                        // +0x16c
    virtual void OnMissionSucceeded();                      // +0x170
virtual void v174();
virtual void v178();
virtual void v17c();
virtual void v180();
    virtual void v184();
    virtual void OnPropertiesLoaded();                      // +0x188

    char           mPad004[0x12c];                          // +0x004 .. +0x12f
    uint32_t       mFlags;                                  // +0x130
    char           mPad134[0x4c];                           // +0x134 .. +0x17f
    cPropertyList* mpPropertyList;                          // +0x180
    int32_t        mField184;                               // +0x184
    int32_t        mField188;                               // +0x188
    char           mPad18c[4];                              // +0x18c
    int32_t        mField190;                               // +0x190
    cVec<ResourceKey> mKeys194;                             // +0x194
    cVec<ResourceKey> mKeys1a8;                             // +0x1a8
    cVec<ResourceKey> mKeys1bc;                             // +0x1bc
    char           mPad1d0[0x20];                           // +0x1d0 .. +0x1ef
    int32_t        mStatus;                                 // +0x1f0
    void*          mpData1f4;                               // +0x1f4
    char           mPad1f8[0xc];                            // +0x1f8 .. +0x203
    int32_t        mField204;                               // +0x204
    int32_t        mField208;                               // +0x208

    char           Init();                                  // 0x00c4ad50
    void           PickGiveOnAcceptItems();                 // 0x00c4a980
    cPlanet*       GetTargetPlanet();                       // 0x00970b30
    void           SetTargetPlanet(void* pPlanet);          // 0x00c47180
    void           SetInitialized();                        // 0x00c4a0c0
    void           TriggerUIUpdate();                       // 0x00c47d80
    int32_t        Update(void* pArg);                      // 0x00c478b0
    void*          PickPlanet(cPlanetSearch* pSearch);      // 0x00c47e20
    uint32_t       ReadTargetPlanetType();                  // 0x00c45b40
    cPlanetRecord* GetPlanetRecordFromTargetType(uint32_t nType);   // 0x00c474b0
};
struct cSPMissionMultiDelivery : cSPMission {
    void    ReturnForRewards();                             // 0x00c4b760
    int32_t Update(void* pArg);                             // 0x00c4b7a0
    bool    IsAtDeliveryTarget(void* pPlanet, ResourceKey* pKey);   // 0x00c4bb60
    bool    InitWrapper();                                  // 0x00c4baa0
    int32_t GetCountA();                                    // 0x00c4bba0
    int32_t GetCountB();                                    // 0x00c4bbc0
};
struct cPlanetSearch {                                      // pick request built by cMissionBalance::Init
    uint32_t mKind;                                         // +0x00 (0x20 / 0x38)
    char     mPad004[0x40];                                 // +0x004

    cPlanetSearch();                                        // 0x00ba7bd0
    ~cPlanetSearch();                                       // 0x00ba8220
};
struct cTerraformingManager {
    ResourceKey* GetKey(ResourceKey* pOut, int32_t nLevel, int32_t nIndex, void* pPlanet);   // 0x00bbc950
    ResourceKey* GetKeyC(ResourceKey* pOut, int32_t nLevel, void* pPlanet);                  // 0x00bbca30
    int32_t      GetLevel();                                // 0x00bbce40
};
cTerraformingManager*  __stdcall TerraformingManager();                 // 0x00b3d430
cTerraformingManager*  __stdcall TerraformingManager(void* pPlanet);    // 0x00b3d430
// ---- items of slice s00c4a850 end

// @ 0x00c4b7a0
int32_t cSPMissionMultiDelivery::Update(void* pArg)
{
    int32_t nResult = cSPMission::Update(pArg);
    if (nResult == 3 && mStatus == 0) {
        void* pPlanetData = GetTargetPlanet()->mpData13C;
        int32_t nLevel = TerraformingManager(pPlanetData)->GetLevel();
        if (nLevel >= (int32_t)(uint32_t)mpData1f4)
            ReturnForRewards();
    }
    return nResult;
}
