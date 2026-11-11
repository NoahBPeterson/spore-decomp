// src/game/SPGonzago/SPTribe.cpp -- migrated from slice(s) s00c9afb0, s00c9a080, s00c97220, s00c95980, s013551e0, s00c99140, s00c96950, s00c947d0, s00c93a40, s00c92a90, s00c91ca0, s00c91a40, s00c90b40, s00c8fbb0, s00c8ec60, s00c8db30 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribe.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cTotemPole.h"
#include <math.h>
#include "SP/cTribe.h"
#include "SP/cCommunity.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cGameNounManager.h"
#include "SP/cSpatialObject.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cVarListSerializer.h"
#include "SP/cGameData.h"
#include "SP/cPlanetModel.h"
#include "SP/cPropertyManager.h"
#include "SP/cAttachment.h"
#include "SP/cCombatant.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cSpear.h"
#include <float.h>
#include "SP/cRelationshipManager.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cString.h"
#include "SP/cTribePlanner.h"
#include <stddef.h>
#include "SP/cActionCircle.h"
#include "SP/cEmptyBubble.h"
#include "SP/cTextureAsyncQueueEntry.h"
#include "SP/cTribeChatArea.h"
#include "SP/cReservationGrid.h"
#include "SP/cTribeHut.h"
#include "SP/cSPEditorSpeciesManager.h"
#include "SP/cITerrainSphere.h"
#include "cSPVector3.h"
#include <string.h>
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cInteractionTarget.h"
#include "SP/cSPTimer.h"

// ---- items of slice s00c8db30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; };
struct Vec6 { uint32_t w[6]; };
namespace EA {
namespace IO {
bool ReadInt32(void* pStream, void* pData, unsigned int uCount, int nFlags);
}
}
namespace EA {
namespace IO {
bool WriteUint32(void* pStream, const void* pData, unsigned int uCount, int nFlags);
}
}
struct IOObject {
virtual void  v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void  v04();
virtual void v05();
    virtual void* v06();                 // +0x18 -> EA::IO stream
    virtual void  v07();                 // +0x1c -> finish hook
    virtual IOObject* v08();             // +0x20 -> reader/writer
};
struct Grid {
    uint8_t      pad000[0x504];          // +0x000..+0x503
    Vec3         mPos;                   // +0x504
    uint32_t     pad510[0x608 / 4 - 0x510 / 4]; // +0x510..+0x607
    uint32_t     mCountB_608;            // +0x608
    uint32_t     mCountA_60c;            // +0x60c

    bool HasA() const { return mCountA_60c > 0u; }
    bool HasB() const { return mCountB_608 > 0u; }
};
struct TerrainSphere {
    int  GetSubIndex() const;            // 0x00c75420 (thiscall, ret 0)
};
struct Tribe {
    uint32_t     pad000[0x120 / 4];      // +0x000..+0x11f (cCommunity tail)
    void*        mpModelFactory_120;     // +0x120 (slot 0x2c / 0x58 interface)
    uint8_t      pad124[0x334 - 0x124];  // +0x124..+0x333
    uint8_t      mb334;                  // +0x334
    uint8_t      pad335[0x33c - 0x335];  // +0x335..+0x33b
    uint8_t      mb33c;                  // +0x33c
    uint8_t      pad33d[0x550 - 0x33d];  // +0x33d..+0x54f
    uint32_t     mPopSlot_550;           // +0x550
    uint16_t     pad554;                 // +0x554
    uint8_t      mbEditorMode_556;       // +0x556
    uint8_t      pad557[0x1868 - 0x557]; // +0x557..+0x1867
    Vec6         mSegmentTable_1868[3];  // +0x1868 (3 * 0x18 = 0x48)
    uint8_t      pad18b0[0x18cc - 0x18b0]; // +0x18b0..+0x18cb
    void*        mpGrid_18cc;            // +0x18cc
    uint8_t      pad18d0[0x19d4 - 0x18d0]; // +0x18d0..+0x19d3
    void*        mpRel_19d4;             // +0x19d4
    uint32_t     mpRel_19d8;             // +0x19d8

    int          GetPopulationId() const; // 0x00a1ad10 (thiscall, ret 0)
};
struct RelMgr {
    int  GetRelation(int nCensusId) const; // 0x00d00a70 (thiscall, ret 4)
};
typedef void (__thiscall *SlotVoid2)(void*, int, int);
struct NounMgr {
    int*  GetPlayerTribe() const;             // 0x00bfc5f0 (thiscall, ret 0)
    int*  GetCurrentTerrainSphere() const;    // 0x00f67d90 (thiscall, ret 0)
    int   ClassifyById(unsigned int nID) const; // 0x00b20790 (thiscall, ret 4)
    void  AddTribe(int* pTribe) const;        // 0x00b23560 (thiscall, ret 4)
};
struct StarMgr {
    int*  GetTerrainSphere() const;           // 0x00ba6630 (thiscall, ret 0)
};
struct IfaceA { void* Query(unsigned int nID) const; }; // 0x00cee250 (thiscall ret 4) @+0x20c
struct IfaceB { void* Query(unsigned int nID) const; }; // 0x00b6e210 (thiscall ret 4) @+0x230
struct IfaceC { void* Query(unsigned int nID) const; }; // 0x00ac0320 (thiscall ret 4) @+0x1f4
struct IfaceD { void* Query(unsigned int nID) const; }; // 0x00b18460 (thiscall ret 4) @+0x000
struct IfaceE { void* Query(unsigned int nID) const; }; // 0x00c884f0 (thiscall ret 4) @+0x120
struct RelCheckA {
    bool Check() const;                  // 0x00c35d20 (thiscall)
};
struct RelCheckB {
    bool Check() const;                  // 0x00c35d40 (thiscall)
};
void*   Sub_b3d350();                                 // 0x00b3d350 SP::PlanetModel
int*    Sub_b3d300();                                 // 0x00b3d300 SP::NounManager
int*    __stdcall Sub_b3d2a0(int a);                  // 0x00b3d2a0 SP::StarManager (ret 4)
int*    Sub_b20c60(void* pSelf, void* pDef);         // 0x00b20c60 CreateNoun
int*    Sub_b3d260();                                 // 0x00b3d260 SP::BehaviorManager
int*    Sub_b3d240();                                 // 0x00b3d240
void*   Sub_b3d2b0();                                 // 0x00b3d2b0
void*   Sub_ac79d0(void* pSelf);                      // 0x00ac79d0
void    Sub_ac7de0(void* pSelf, void* p);            // 0x00ac7de0
int     Sub_c00ad0(int v);                            // 0x00c00ad0
void __stdcall Sub_c00b00(int a, int b);             // 0x00c00b00 (stdcall, ret 8)
int*    Sub_cee330(void* pSelf);                      // 0x00cee330
struct Cee380 {
    float Get() const;                   // 0x00cee380 (thiscall, ret 0)
};
RelMgr* Sub_b3d2c0();                                 // 0x00b3d2c0 SP::RelationshipManager
// ---- items of slice s00c8db30 end

// ---- items of slice s00c8ec60 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
class cSPVector3_s00c8_ec60 {
public:
    float mx;
    float my;
    float mz;
};
struct cSpeciesKey {
    uint32_t mnA;
    uint32_t mnB;
    uint32_t mnC;
};
void* operator_new(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                   const char* pFile, int32_t nLine);          // 0x00f473a0
class cTransformNode {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual cSPVector3_s00c8_ec60* GetPosition();                      // 0x02c
virtual void v30();
virtual void v34();
    virtual void GetOrientation(cSPVector3_s00c8_ec60* pOut);          // 0x038
    virtual void FUN_00c8f03c(void* pValue);                // 0x03c
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
    virtual cSPVector3_s00c8_ec60* GetScale(cSPVector3_s00c8_ec60* pOut);         // 0x05c
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual void v70();
    virtual float GetRadius();                              // 0x074

    bool Write(void* pStream);                              // 0x00c88a90
};
class cRefCounted_s00c8_ec60 {
public:
    virtual void v00();
    virtual void Release();                                 // 0x004
    virtual void v08();
    virtual void Disable(int32_t nA);                       // 0x00c
};
class cRefCountedNode {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c(int32_t nA);
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
    virtual void AddRef();                                  // 0x0bc
    virtual void Release();                                 // 0x0c0
};
struct cPointerBlockIter {
    void** mpCur;                                           // 0x00
    void** mpBegin;                                         // 0x04
    void** mpEnd;                                           // 0x08
    void** mpBlockIt;                                       // 0x0c
};
class cPointerVector {
public:
    cPointerVector* Init(int32_t nCount, int32_t nUnused);  // 0x00c8ed30

    void** mpBegin;                                         // 0x00
    void** mpEnd;                                           // 0x04
    void** mpCapEnd;                                        // 0x08
};
class cSpatialThing {
public:
    uint8_t mPad000[0x34];                                  // 0x000
    cTransformNode mNode;                                   // 0x034
};
class cCombatantNode {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
    virtual float GetValue58();                             // 0x058

    void SetValue(float fValue);                            // 0x00f924e0
};
class cTreeStimuli {
public:
    void* Play(int32_t nA, void* pB, float fC, void* pD);   // 0x00bc97f0
    void ClearAll(int32_t nA, int32_t nB);                  // 0x00bc98f0

    uint8_t mPad000[0x1c0];                                 // 0x000
    uint32_t mnField1C0;                                    // 0x1c0
};
class cBehaviorTree {
public:
    uint8_t mPad000[0x08];                                  // 0x000
    cTreeStimuli mStimuli;                                  // 0x008
};
class cStimulusEntry {
public:
    uint8_t mPad000[0x0c];                                  // 0x000
    int32_t mnField0C;                                      // 0x00c
    int32_t mnField10;                                      // 0x010
    cSPVector3_s00c8_ec60 mPosition;                                   // 0x014
};
class cCreature {
public:
    uint8_t mPad000[0xc0];                                  // 0x000
    cTransformNode mNode;                                   // 0x0c0
    uint8_t mPad0C4[0x4e4];                                 // 0x0c4
    cCombatantNode mCombatant;                              // 0x5a8
    uint8_t mPad5AC[0x5a0];                                 // 0x5ac
    cBehaviorTree* mpBehaviorTree;                          // 0xb4c

    bool IsLeader();                                        // 0x00c232d0
    void FUN_00c0b9d0(float fValue);                        // 0x00c0b9d0
};
class cGameNounManager_s00c8_ec60 {
public:
    void RemoveNoun(void* pNoun);                           // 0x00b225d0
};
cGameNounManager_s00c8_ec60* __stdcall NounManagerOf(void* pNoun);     // 0x00b3d300
class cValueNode {
public:
virtual void w00();
virtual void w04();
virtual void w08();
virtual void w0c();
virtual void w10();
virtual void w14();
virtual void w18();
virtual void w1c();
virtual void w20();
virtual void w24();
virtual void w28();
    virtual void* SetValue(float fValue);                   // 0x02c
virtual void w30();
virtual void w34();
virtual void w38();
virtual void w3c();
virtual void w40();
virtual void w44();
virtual void w48();
virtual void w4c();
virtual void w50();
virtual void w54();
virtual void w58();
virtual void w5c();
virtual void w60();
virtual void w64();
virtual void w68();
virtual void w6c();
    virtual void w70();
    virtual float FUN_00c8f074(float fValue, void* pValue);    // 0x074
};
class cValueOwner {
public:
virtual void x00();
virtual void x04();
virtual void x08();
    virtual void* GetChild();                               // 0x008
    virtual void* GetValue(void* pThis);                    // 0x00c
};
class cStreamHolder {
public:
virtual void z00();
virtual void z04();
virtual void z08();
virtual void z0c();
virtual void z10();
virtual void z14();
    virtual void* GetStream();                              // 0x018
};
class cOutStream {
public:
virtual void y00();
virtual void y04();
virtual void y08();
virtual void y0c();
virtual void y10();
virtual void y14();
virtual void y18();
virtual void y1c();
    virtual cStreamHolder* GetHolder();                     // 0x020
};
class cResultOwner {
public:
    void FUN_00bc8400();                                    // 0x00bc8400
};
class cTribe {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
    virtual void** GetAgents();                             // 0x090
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
    virtual void vb0();
    virtual cSpatialThing* GetThing(int32_t nType);         // 0x0b4

    class cCreature* PickAPeon();
    class cTool* GetToolOfType(int32_t nType);
    int32_t GetAdultPopulation();
    int32_t FUN_00c8f3a0();
    void FUN_00c8f3d0(int32_t nA1, void* pA2, float fA3, void* pA4,
                      cSPVector3_s00c8_ec60* pA5, uint32_t nA6);
    void SetStimuli(int32_t nA1, int32_t nA2, float fA3, void* pA4);
    void FUN_00c8f540(cSPVector3_s00c8_ec60* pPosition, float fRadius, int32_t nA, void* pB,
                      void* pC, void* pD);
    void FUN_00c8f660(int32_t nValue);
    bool FUN_00c8f730(int32_t nId);
    void ResetDefaultToolPlacement(int32_t nType);
    bool Write(void* pStream);
    bool FUN_00c8fa60();
    void FUN_00c8fb50();

    uint32_t FUN_00c8e990();                                // 0x00c8e990

    uint8_t mPad004[0x11c];                                 // 0x004
    cTransformNode mNode;                                   // 0x120
    uint8_t mPad124[0xe8];                                  // 0x124
    cTransformNode mNode2;                                  // 0x20c
    uint8_t mPad210[0x20];                                  // 0x210
    cTransformNode mNode3;                                  // 0x230
    uint8_t mPad234[0x94];                                  // 0x234
    float mfField2C8;                                       // 0x2c8
    uint8_t mPad2CC[0x68];                                  // 0x2cc
    uint8_t mbField334;                                     // 0x334
    uint8_t mPad335[0x03];                                  // 0x335
    int32_t mnField338;                                     // 0x338
    uint8_t mbField33C;                                     // 0x33c
    uint8_t mPad33D[0x03];                                  // 0x33d
    cCreature** mppPeonBegin;                               // 0x340
    cCreature** mppPeonEnd;                                 // 0x344
    uint8_t mPad348[0x0c];                                  // 0x348
    uint32_t mnField354;                                    // 0x354
    uint32_t mnField358;                                    // 0x358
    uint8_t mPad35C[0x10];                                  // 0x35c
    void** mppToolBegin;                                    // 0x36c
    void** mppToolEnd;                                      // 0x370
    uint8_t mPad374[0x1558];                                // 0x374
    void* mpField18CC;                                      // 0x18cc
    void* mpField18D0[14];                                  // 0x18d0
    cSpeciesKey* mpKeys;                                    // 0x1904
    uint8_t mPad1908[0xbc];                                 // 0x1908
    cRefCountedNode* mpField19C4;                           // 0x19c4
    cRefCountedNode* mpField19C8;                           // 0x19c8
    cRefCountedNode* mpField19CC;                           // 0x19cc
    cRefCountedNode* mpField19D0;                           // 0x19d0
};
class cTool {
public:
virtual void t00();
virtual void t04();
virtual void t08();
virtual void t0c();
virtual void t10();
virtual void t14();
virtual void t18();
virtual void t1c();
virtual void t20();
virtual void t24();
virtual void t28();
virtual void t2c();
virtual void t30();
virtual void t34();
virtual void t38();
virtual void t3c();
virtual void t40();
virtual void t44();
virtual void t48();
virtual void t4c();
virtual void t50();
virtual void t54();
    virtual int32_t GetType();                              // 0x058

    int32_t GetId();                                        // 0x00c9d110
};
class cCommunity {
public:
    void func58h(int32_t nA);                               // 0x00c8f2b0
    void func58hBase(int32_t nA);                           // 0x00c886d0

    uint8_t mPad000[0x248];                                 // 0x000
    cSpatialThing* mpField248;                              // 0x248
};
class cSpeciesManager {
public:
    bool GetReplacementKey(const cSpeciesKey& key, uint32_t nId, cSpeciesKey* pOut);   // 0x004df7d0
    void* GetProfile(const cSpeciesKey& key);                                           // 0x004df550
};
class cVarListSerializer {
public:
    cVarListSerializer(cTribe* pOwner, const void* pVarList, int32_t nFlags);   // 0x00692f90
    bool Serialize(void* pStream);                                             // 0x00692900

    uint8_t mPad000[0xa00];                                 // 0x000
};
class cValueSink {
public:
    void FUN_00ac7ab0();                                    // 0x00ac7ab0
    float FUN_00ac7d10();                                   // 0x00ac7d10
};
void* __stdcall FUN_00b3d2b0(float fValue, void* pTarget, uint32_t nId);   // 0x00b3d2b0
void* FUN_00bc8000(uint32_t nId, void* pValue);                     // 0x00bc8000
void* FUN_00bc8400(uint32_t nId, void* pValue);                     // 0x00bc8400
void* FUN_00ba5df0(void* pKeys, cSpeciesKey* pKey);                 // 0x00ba5df0
void* PlanetModel(void* pOut, const void* pElement, const void* pExtra);   // 0x00b3d350
void* GetSetting9();                                                // 0x00401090
bool FUN_00c24560(cCreature* pCreature);                            // 0x00c24560
bool FUN_00c005b0(cTribe* pTribe, void* pStream);                   // 0x00c005b0
bool FUN_00b6e2d0(cTransformNode* pNode, void* pStream);            // 0x00b6e2d0
bool FUN_00cee3d0(cTransformNode* pNode, void* pStream);            // 0x00cee3d0
void* EA_WriteUint32(void* pStream, const uint32_t* pValue, int32_t nCount, int32_t nA);   // 0x0093aa70
float g_fHotSpotValue = 1.0f;
const char g_szSimulator[] = "Simulator";
const char g_szAllocatorFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
// ---- items of slice s00c8ec60 end

// ---- items of slice s00c8fbb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
struct tVec3 {
    float mX;                                           // +0x00
    float mY;                                           // +0x04
    float mZ;                                           // +0x08
};
}
namespace SP {
class cPositionSource {
public:
virtual void p000();
virtual void p004();
virtual void p008();
virtual void p00c();
virtual void p010();
virtual void p014();
virtual void p018();
virtual void p01c();
virtual void p020();
virtual void p024();
virtual void p028();
    virtual tVec3* GetPosition();                        // +0x2c
};
}
namespace SP {
class cGameNounManager_s00c8_fbb0;
}
namespace SP {
cGameNounManager_s00c8_fbb0* __cdecl NounManager();                 // 0x00b3d300
}
namespace SP {
class cGameNounManager_s00c8_fbb0 {
public:
    void RemoveNoun(void* pNoun);                        // 0x00b225d0
};
}
namespace SP {
class cNounRef {
public:
    virtual void n00();
    virtual void Release();                              // +0x04
};
}
namespace SP {
struct cPointerVector_s00c8_fbb0 {
    char* mpBegin;                                       // +0x00
    char* mpEnd;                                         // +0x04
};
}
namespace SP {
struct cFileList {
    int GetFileCount();                                  // 0x008e7f80
};
}
namespace SP {
class cLeaderObject {
public:
virtual void l00();
virtual void l04();
virtual void l08();
    virtual void* QueryInterface(uint32_t interfaceId);  // +0x0c
};
}
namespace SP {
class cCommunity_s00c8_fbb0 {
public:
    uint8_t         pad000[0x34];                        // +0x000 .. +0x033
    cPositionSource mPosition;                           // +0x034
    uint8_t         pad048[0xe8];                        // +0x048 .. +0x11f
    cFileList       mFileList;                           // +0x120
};
}
namespace SP {
class cTribe_s00c8_fbb0 {
public:
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
    virtual tVec3* GetPoliticalCenterOrCenter(tVec3* pOut); // +0x58
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void v080();
virtual void v084();
virtual void v088();
    virtual void v08c();
    virtual cPointerVector_s00c8_fbb0* GetPointerList();            // +0x90
virtual void v094();
virtual void v098();
virtual void v09c();
    virtual void ClearPointer(void* pEntry);             // +0xa0

    uint8_t         pad004[0x11c];                       // +0x004 .. +0x11f
    cPositionSource mPosition;                           // +0x120
    uint8_t         pad124[0x210];                       // +0x124 .. +0x333
    bool            mb334;                               // +0x334
    uint8_t         pad335[3];                           // +0x335 .. +0x337
    int32_t         mPointerCount;                       // +0x338
    bool            mPointersDirty;                      // +0x33c
    uint8_t         pad33d[3];                           // +0x33d .. +0x33f
    void**          mpPointerStackBegin;                 // +0x340
    void**          mpPointerStackEnd;                   // +0x344
    uint8_t         pad348[0x20];                        // +0x348 .. +0x367
    cCommunity_s00c8_fbb0*     mpCommunity;                         // +0x368
    uint8_t         pad36c[0x1664];                      // +0x36c .. +0x19cf
    cNounRef*       mpAttachedNoun;                      // +0x19d0

    void  UpdateRoboTribeness();  // 0x00c8fbb0 (SP::cTribe::UpdateRoboTribeness)
    tVec3* GetCenter(tVec3* pOut);  // 0x00c8fcc0 (SP::cTribe::GetCenter)
    tVec3* GetPoliticalCenter(tVec3* pOut);  // 0x00c8fcf0 (SP::cTribe::GetPoliticalCenter)
    void* GetChieftain();  // 0x00c8fd30 (SP::cTribe::GetChieftain)
    void  PromoteChieftain(uint32_t civId);  // 0x00c8fd50 (SP::cTribe::PromoteChieftain)
    tVec3* GetClosestWater();  // 0x00c8fe20 (SP::cTribe::GetClosestWater)
    void  InitDomesticatedAnimalsHerd(uint32_t speciesId);  // 0x00c8fef0 (SP::cTribe::InitDomesticatedAnimalsHerd)
    void  FUN_00c8fc50(bool flag);
    void  FUN_00c90470();
    bool  FUN_00c905a0();

    // Community queries reached through the tribe's shared base.
    void* GetLeader();                                   // 0x00c00650
};
}
// ---- items of slice s00c8fbb0 end

// ---- items of slice s00c90b40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sin(double);              // x87 fsin in retail
extern "C" double __cdecl cos(double);              // x87 fcos in retail
extern "C" double __cdecl sqrt(double);
extern "C" void*  __cdecl GetCurrentGameMode();              // 0x00b5b800
extern "C" void*  __cdecl PlanetModel();                     // 0x00b3d350
extern "C" void*  __cdecl ModeStrategyInstance();            // 0x00cd40b0
extern "C" void*  __cdecl FUN_00cc9740(void* self);                         // 0x00cc9740
typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;
typedef unsigned short u16;
struct Quat { float x, y, z, w; };
struct Matrix33 { float m[9]; };
struct Elem14 {
  float mX, mY, mZ, mW;                  // 0x00
  u8    mB_10;                           // 0x10
  u8    mPad_11[3];                      // 0x11
};
struct RefCnt {
  virtual void AddRef();                 // 0x00
  virtual void Release();                // 0x04
};
struct cSpatial {
  virtual void  v00();                   // 0x00
  virtual void  v04();                   // 0x04
  virtual void  v08();                   // 0x08
  virtual void  v0c();                   // 0x0c
  virtual void  v10();                   // 0x10
  virtual void  v14();                   // 0x14
  virtual void  v18();                   // 0x18
  virtual void  v1c();                   // 0x1c
  virtual void  v20();                   // 0x20
  virtual void  v24();                   // 0x24
  virtual void  v28();                   // 0x28
  virtual Vec3* GetPosition();           // 0x2c
  virtual Quat* GetRotation();           // 0x30
  virtual void  v34();                   // 0x34
  virtual void  SetPosition(Vec3* p);    // 0x38
  virtual void  v3c();                   // 0x3c
  virtual void  v40();                   // 0x40
  virtual void  v44();                   // 0x44
  virtual void  v48();                   // 0x48
  virtual void  v4c();                   // 0x4c
  virtual void  v50();                   // 0x50
  virtual s32   v54();                   // 0x54
  virtual u8    IsValid();               // 0x58
  virtual void  v5c(Vec3* out);          // 0x5c
virtual void  v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void  v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void  v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void  v90();
virtual void v94();
virtual void v98();
virtual void v9c();
  virtual void  va0();
  virtual s32   vA4();                   // 0xa4 (tribe money getter)
  u8 mBody_04[0x5c];                     // 0x04
};
struct cPlanetBody {
  virtual void v00();                    // 0x00
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
  virtual void v50();
  virtual u32  AddTransform(void* xform, u32 id);   // 0x54
};
struct cPlanetModel {
  u8           mPad_00[0x24];           // 0x00
  cPlanetBody* mpBody_24;                // 0x24
};
struct cTransform {
  u16      mFlags_00;                    // 0x00
  u16      mStamp_02;                    // 0x02
  Vec3     mPos_04;                      // 0x04
  float    mScale_10;                    // 0x10
  Matrix33 mRot_14;                      // 0x14
};
struct Matrix33Obj {
  Matrix33 mMat_00;                      // 0x00
  void ctor(const void* preset);         // 0x0041cb40
};
struct cInteractable {
  virtual void  AddRef();                // 0x00
  virtual void  Release();               // 0x04
  virtual void* QueryInterface(u32 id);  // 0x08
  virtual void  v0c();                   // 0x0c
  void SetAreaData(Vec3* pos, float radius);   // 0x00c3f160
  void SetParams(float a, float b);            // 0x00c3f1b0
  void AttachEffect(void* effect);             // 0x00c3f2d0
};
struct cSplashEffect {
  virtual void  AddRef();                // 0x00
  virtual void  Release();               // 0x04
virtual void  v08();
virtual void v0c();
virtual void  v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void  v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void  v30();
virtual void v34();
  virtual void  SetPosition(Vec3* p);    // 0x38
  u8        mPad_04[0x70 - 0x04];        // 0x04
  cSpatial  mPlacement_70;               // 0x70
  u8        mPad_d0[0xe1 - 0xd0];        // 0xd0
  u8        mVisible_e1;                 // 0xe1
};
struct cTool_s00c9_0b40 {
  u8       mPad_00[0x34];                // 0x00
  cSpatial mAnchor_34;                   // 0x34
};
struct cPlacementArea {
  u8       mPad_00[0x34];                // 0x00
  cSpatial mAnchor_34;                   // 0x34
  u8       mPad_94[0xa3 - 0x94];         // 0x94
  u8       mB_a3;                        // 0xa3
  u8       mPad_a4[0x12c - 0xa4];        // 0xa4
  u32      mFlags_12c;                   // 0x12c (0 means "3")
  u32      mConnected_130;               // 0x130
};
struct cTribe_s00c9_0b40 : cSpatial {
  u8       mPad_60[0x120 - 0x60];        // 0x60
  cSpatial mSpatial_120;                 // 0x120
  u8       mPad_180[0x1d4 - 0x180];      // 0x180
  s32      mMoney_1d4;                   // 0x1d4 (tribe funds)
  u8       mPad_1d8[0x2d4 - 0x1d8];      // 0x1d8
  u32      mEffectId_2d4;                // 0x2d4
  u8       mPad_2d8[4];                  // 0x2d8
  Vec3     mToolSlots_2dc[3];            // 0x2dc (per-kind tool anchors)
  u8       mPad_300[0x504 - 0x300];     // 0x300
  Vec3     mToolAnchor_504;              // 0x504 (kind-0 anchor)
  u8       mPad_510[0x19d4 - 0x510];     // 0x510
  u32      mAreaEffect_19d4;             // 0x19d4

  cTool_s00c9_0b40* GetToolOfType(s32 type);                 // 0x00c8f6e0
  float* GetToolPosition(float* out, s32 kind);    // 0x00c91190
  void   UpdateToolPositions();                   // 0x00c91250
  void   UpgradeHut();                            // 0x00c919e0
  void   CheckFoodTutorialComplete();             // 0x00c91970
  void   FUN_00c8f3d0(s32 a, void* b, float c, s32 d, Vec3* e, u32 f); // 0x00c8f3d0
  void   RefreshAreaEffect();                     // 0x00c91700
};
struct cToolPlacement {
  virtual void  v00();                   // 0x00
virtual void  v04();
virtual void v08();
virtual void v0c();
virtual void  v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void  v20();
virtual void v24();
virtual void v28();
virtual void v2c();
  virtual void  v30(cPlacementArea* area);   // 0x30
  u8     mPad_04[0xdc - 0x04];           // 0x04
  Vec3   mOffset_dc;                     // 0xdc
  u8     mPad_e8[0x100 - 0xe8];          // 0xe8

  void SetPlacementArea(cPlacementArea* area);     // 0x00c91800
  cTribe_s00c9_0b40* Tribe() { return (cTribe_s00c9_0b40*)((u8*)this - 0xec); }
};
struct cFishingHotSpot_s00c9_0b40 {
  u8              mPad_00[0x24];         // 0x00
  cInteractable*  mpInteractable_24;     // 0x24
  cSplashEffect*  mpSplashEffect_28;     // 0x28
  u8              mPad_2c[0x3c - 0x2c];  // 0x2c

  void SetupArea(Vec3* pos, float radius);    // 0x00c91030
};
struct cGameNounManager_s00c9_0b40 {
  void* CreateNoun(u32 id);              // 0x00b20c60
};
struct cTribeModeStrategy {
virtual void* v00();
virtual void* v04();
virtual void* v08();
virtual void* v0c();
virtual void* v10();
virtual void* v14();
virtual void* v18();
virtual void* v1c();
virtual void* v20();
virtual void* v24();
virtual void* v28();
virtual void* v2c();
virtual void* v30();
virtual void* v34();
virtual void* v38();
virtual void* v3c();
virtual void* v40();
virtual void* v44();
virtual void* v48();
virtual void* v4c();
virtual void* v50();
virtual void* v54();
virtual void* v58();
virtual void* v5c();
virtual void* v60();
virtual void* v64();
virtual void* v68();
  virtual void* v6c(void* splash, Vec3 v, s32 a, s32 b);   // 0x6c
  u8   TerrainHasKey(u32 key);           // 0x00cd4460
  void SignalTribeEvent(u32 key);        // 0x00cd6980
};
struct cGameData {
  void* GetPlayerTribe();                // 0x00bfc5f0
};
extern "C" void*  __cdecl NounManager_s00c9_0b40();                     // 0x00b3d300
extern "C" s32    __cdecl GetTutorialToolPrice(u32 tbl, u32 key, s32 idx);  // 0x004e1c30
extern "C" void*  __cdecl FUN_00c6f770(void* self, u32 key, s32 a, s32 b);  // 0x00c6f770
extern "C" void*  __cdecl Matrix3FromQuaternion(void* out, const Quat* q);  // 0x0059c190
extern "C" void*  __cdecl FUN_0059aed0(void* out, const void* m, const Quat* q); // 0x0059aed0
extern "C" Vec3*  __cdecl DirectionToSurfacePosition(cPlanetModel* model, Vec3* out,
Vec3* dir);            // 0x00b815a0
extern "C" u8     __cdecl GetPropertyAsVector3(void* obj, u32 key, Vec3* out); // 0x00b81d50
struct SegIter {
  RefCnt**  mpCur;                       // 0x00
  RefCnt**  mpBegin;                     // 0x04
  RefCnt**  mpEnd;                       // 0x08
  RefCnt*** mppPage;                     // 0x0c (slot holding the next page)
};
// ---- items of slice s00c90b40 end

// ---- items of slice s00c91a40 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int           i32;
typedef float         f32;
namespace eastl {
    class sp_vector_allocator_s00c9_1a40 {};
}
namespace eastl {
    template <class Elem, class Alloc>
    class vector_s00c9_1a40 {
    public:
        Elem *mBegin;         // first element
        u32   mCount;         // number of elements
        u32   mCapacity;      // allocated capacity
    };
}
namespace eastl {
    template <class Elem, class Alloc>
    bool reserve(vector_s00c9_1a40<Elem, Alloc> *self, u32 id, u32 *count, Elem **begin);
}
namespace SP {
class cTool_s00c9_1a40;
}
namespace SP {
class cMWModel_s00c9_1a40;
}
namespace SP {
class cRefCounted {
public:
    virtual void AddRef(void);           // 0x00
    virtual void Release(void);          // 0x04
};
}
namespace SP {
class cMWModel_s00c9_1a40 : public cRefCounted {
public:
};
}
namespace SP {
template <class T>
class AutoRefCount {
public:
    T *mPtr;
    AutoRefCount &operator=(T *p)
    {
        T *old = mPtr;
        if (p != old) {
            p->AddRef();
            mPtr = p;
            if (old != 0)
                old->Release();
        }
        return *this;
    }
};
}
namespace SP {
class cModel {
public:
virtual void vm00(void);
virtual void vm01(void);
virtual void vm02(void);
virtual void vm03(void);
virtual void vm04(void);
virtual void vm05(void);
virtual void vm06(void);
virtual void vm07(void);
virtual void vm08(void);
virtual void vm09(void);
virtual void vm10(void);
virtual void vm11(void);
virtual void vm12(void);
virtual void vm13(void);
virtual void vm14(void);
virtual void vm15(void);
virtual void vm16(void);
virtual void vm17(void);
virtual void vm18(void);
virtual void vm19(void);
virtual void vm20(void);
virtual void vm21(void);
virtual void vm22(void);
virtual void vm23(void);
virtual void vm24(void);
virtual void vm25(void);
virtual void vm26(void);
virtual void vm27(void);
virtual void vm28(void);
virtual void vm29(void);
virtual void vm30(void);
virtual void vm31(void);
virtual void vm32(void);
virtual void vm33(void);
virtual void vm34(void);
virtual void vm35(void);
    virtual void vm36(void);
    virtual void SetDesc(const void *desc);          // 0x94
virtual void vm38(void);
virtual void vm39(void);
    virtual void SetWorld(void *world);              // 0xa0
virtual void vm41(void);
virtual void vm42(void);
    virtual void *GetOwner(void);                    // 0xac
};
}
namespace SP {
class cToolDef {
public:
virtual void vd00(void);
virtual void vd01(void);
virtual void vd02(void);
virtual void vd03(void);
virtual void vd04(void);
virtual void vd05(void);
virtual void vd06(void);
virtual void vd07(void);
virtual void vd08(void);
virtual void vd09(void);
virtual void vd10(void);
virtual void vd11(void);
virtual void vd12(void);
virtual void vd13(void);
virtual void vd14(void);
virtual void vd15(void);
virtual void vd16(void);
virtual void vd17(void);
virtual void vd18(void);
virtual void vd19(void);
virtual void vd20(void);
    virtual void vd21(void);
    virtual bool IsActive(void);                     // 0x58
};
}
namespace SP {
class cTool_s00c9_1a40 : public cRefCounted {
public:
    unsigned char pad_04[0x34 - 4];
    cModel        mModel;                // 0x34  the tool's rendered model
    unsigned char pad_38[0x120 - 0x38];
    cToolDef      mDef;                  // 0x120 the tool's definition

    void RefreshModel(void);             // 0x00c9d030  thiscall
    void UpdateTransform(void);          // 0x00c9dd50  thiscall
};
}
namespace SP {
class cHutModelState {
public:
    unsigned char pad_00[0x608];
    i32           m608;                  // 0x608
    i32           m60c;                  // 0x60c
};
}
namespace SP {
class cPropertyManager_s00c9_1a40 {
public:
virtual void pm00(void);
virtual void pm01(void);
virtual void pm02(void);
virtual void pm03(void);
virtual void pm04(void);
virtual void pm05(void);
virtual void pm06(void);
virtual void pm07(void);
virtual void pm08(void);
virtual void pm09(void);
virtual void pm10(void);
    virtual bool Query(u32 a, u32 b, void *out);     // 0x2c
};
}
namespace SP {
class cTribe_s00c9_1a40 {
public:
    cTool_s00c9_1a40 *GetToolOfType(int toolType);  // 0x00c8f6e0
    i32    GetModeVariant(void);         // 0x00a1ad10
    void   GetClosestWater(void);        // 0x00c8fe20
};
}
namespace SP {
class cTribeToolView : public cTribe_s00c9_1a40 {
public:
    unsigned char pad_00[0x120];         // (the empty cTribe base occupies no bytes)
    cToolDef      mDef;                  // 0x120
    unsigned char pad_124[0x300 - 0x124];
    u8            m300;                  // 0x300  water-query dirty/valid byte
    unsigned char pad_301[0x310 - 0x301];
    f32           m310;                  // 0x310  closest-water / ground height
    unsigned char pad_314[0x18cc - 0x314];
    cHutModelState *m18cc;               // 0x18cc

    void UpdateModel(void);              // 0x00c91a40
    void *ChooseNewHutModel(void);       // 0x00c91b60
    f32  GetWaterOrHeight(void);         // 0x00c91c80
};
}
namespace SP {
    void  *PropertyManager_s00c9_1a40(void);        // 0x0067de30
}
// ---- items of slice s00c91a40 end

// ---- items of slice s00c91ca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kHalfPi;            // 0x0157aad4
extern const char kCombatantIID[];     // 0x013f94d4
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
};
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
inline Vector3 operator-(const Vector3& a) { return Vector3(-a.x, -a.y, -a.z); }
struct Quaternion {
    float x, y, z, w;
};
__forceinline Quaternion MulConj(const Quaternion& a, const Quaternion& b)
{
    Quaternion r;
    r.x = a.x * b.w - a.w * b.x + a.y * b.z - a.z * b.y;
    r.y = a.y * b.w - a.w * b.y - a.x * b.z + a.z * b.x;
    r.z = a.x * b.y - a.w * b.z - a.y * b.x + a.z * b.w;
    r.w = a.y * b.y + a.z * b.z + a.w * b.w + a.x * b.x;
    return r;
}
struct Matrix3 {
    float m[9];
};
struct Transform {
    unsigned short mFlags;     // bit0 scaled, bit1 rotated, bit2 translated
    unsigned short mVersion;   // bumped on every change
    Vector3 mPos;
    float mScale;
    Matrix3 mRot;

    Transform();                                // 0x00409930
    void RotateY(float angle);                  // 0x004099b0
    void SetRotation(const Matrix3& m) { mRot = m; mFlags |= 2; mVersion++; }
    void SetOffset(const Vector3& v) { mFlags |= 4; mVersion++; mPos = v; }
    void SetScale(float s) { mScale = s; mVersion++; }
};
Vector3 normalized_safe(const Vector3& v);                                         // 0x00449c20
Quaternion QuaternionFromDirections(const Vector3& from, const Vector3& to);       // 0x00698180
Matrix3 Matrix3FromQuaternion(const Quaternion& q);                                // 0x0059c190
Vector3 RotateByQuaternion(const Quaternion& q, const Vector3& v);                  // 0x0099c310
void Start3dSoundByName(uint32_t name, int system, Vector3 pos);                   // 0x00571f80
extern const Vector3 kXAxis;           // 0x0157aad8
extern const Vector3 kSpearHitDefault; // 0x01695374
static const uint32_t kSpearSlotBase = 0x2735290;   // first body-attachment slot used for spears
struct IAudioSystem {
    PV8
    virtual int GetHandle();                         // +0x20
};
namespace EA {
namespace Audio {
 IAudioSystem* GetSystemAT();   // 0x00a206f0
}
}
struct cSpatialObject;
struct cCombatant;
struct cGameObject {
    PV8 PV8 PV4 PV2 PV
    virtual void* Cast(uint32_t type);               // +0x5c
};
struct IUnknown32_s00c9_1ca0 {
    virtual int AddRef();                            // +0x00
    virtual int Release();                           // +0x04
    PV
    virtual void* AsInterface(const void* iid);      // +0x0c
};
struct cSpatialObject : IUnknown32_s00c9_1ca0 {};
struct cCombatantData {
    uint32_t pad00[0x1d];
    uint8_t pad74;
    bool mbCanBeDamaged;                             // +0x75
};
struct cCombatant {
    PV2
    virtual cCombatantData* GetData();               // +0x08
    PV
    virtual int GetPoliticalID();                    // +0x10
    PV
    virtual void TakeDamage(float damage, int attackerPoliticalID, int damageType,
                            const Vector3* direction, cCombatant* attacker);   // +0x18
    PV8 PV4 PV2 PV2
    virtual void* Cast(uint32_t type);               // +0x5c
    PV
    virtual void Release();                          // +0x64
};
struct cModel_s00c9_1ca0 {
    uint32_t pad00[6];
    Vector3 mPosition;                               // +0x18
    uint32_t pad24[6];
    Quaternion mOrientation;                         // +0x3c
    uint32_t pad4c[0xa6];
    char* mpBones;                                   // +0x2e4, records of 0x2bc bytes
};
struct cBone {
    uint32_t pad00[4];
    Vector3 mOffset;                                 // +0x10
    Quaternion mOrientation;                         // +0x1c
};
struct cAttachedModel {
    uint32_t pad00[0x5f];
    cModel_s00c9_1ca0* mpModel;                                 // +0x17c
};
struct IEffectOwner {
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV2 PV
    virtual void StopEffect(void* effect, int flags); // +0x16c
};
struct cEffect {
    IEffectOwner* mpOwner;
    void Stop();                                      // 0x00571d90
};
struct cAttachment {
    uint32_t pad00[3];
    Vector3 mOffset;                                 // +0x0c
    Quaternion mOrientation;                         // +0x18
    uint32_t pad28[0x1a];
    cEffect* mpEffect;                               // +0x90
    uint32_t pad94[4];
    IUnknown32_s00c9_1ca0* mpObject;                            // +0xa4
};
struct cInteractiveOrnament;
cInteractiveOrnament* interface_cast_Ornament(IUnknown32_s00c9_1ca0* const& p);              // 0x00c8ec90
struct cCreatureBase;
struct cAttachmentOwner {
    cAttachment* GetAttachment(uint32_t slot);                                  // 0x00c0dfb0
    void RemoveAttachment(uint32_t slot, int flags);                            // 0x00c15150
};
struct cSpatialPart {
    PV8 PV8
    virtual void SetScale(float scale);              // +0x40
};
struct cInteractiveOrnament {
    PV8 PV4
    virtual int GetModelKey();                       // +0x30
    virtual void AttachTo(cCreatureBase* creature);  // +0x34
    uint32_t pad04[0xc];
    cSpatialPart mSpatial;                           // +0x34
    uint32_t pad38[0x1b];
    uint8_t padA4;
    bool mbA5;                                       // +0xa5
    uint8_t padA6[3];
    bool mbA9;                                       // +0xa9
    uint8_t padAA[0x196];
    int mPriority;                                   // +0x240
    void SetLifetime(float seconds, int flags);      // 0x00c40830
};
struct sSlotRange {
    uint32_t mFirst;
    int mCount;
};
struct cBehaviorTracker {
    int Find(int a, int b, cCreatureBase* c, int d);                               // 0x00bca0c0
    void Add(int a, int b, cCreatureBase* c, float t, const sSlotRange* r, int d);  // 0x00bca810
};
struct cSPSubC0 {
    PV8 PV8 PV2
    virtual bool IsVisible();                        // +0x48
};
struct cCreatureBase : cAttachmentOwner {
    uint32_t pad00[0x30];
    cSPSubC0 mSubC0;                                 // +0xc0
    uint32_t padC4[0x2a1];
    cBehaviorTracker* mpTracker;                     // +0xb48
    uint32_t padB4C[2];
    cAttachedModel* mpAttachedModel;                 // +0xb54
    uint32_t padB58;
    uint8_t padB5C[2];
    bool mbB5E;                                      // +0xb5e
    uint8_t padB5F;
    uint32_t padB60[0xcb];
    int mE8C;                                        // +0xe8c

    bool IsFlagSet();                                                            // 0x00c0c0e0
    void InterruptAnimation(uint32_t anim, int a, int b);                        // 0x00c12310
    void CreateBodyEffect(int bone, int a, cSpatialPart* obj, uint32_t slot);    // 0x00c11f50
};
cCreatureBase* GetCreatureBase(cCombatant* const& p);                           // 0x00c0c3a0
cAttachmentOwner* FindAttachmentOwner(int modelKey);                            // 0x00f19200
struct cPoliticalPart {
    PV8 PV8 PV4 PV2
    virtual bool GetTribeIndex();                    // +0x58
};
struct cTribe_s00c9_1ca0 {
    uint32_t pad00[0x48];
    cPoliticalPart mPolitical;                       // +0x120
};
struct cCreatureCitizen {
    PV8 PV8 PV2 PV
    virtual int GetPoliticalID();                    // +0x4c
    uint32_t pad04[0x169];
    cCombatant mCombatant;                           // +0x5a8
    cTribe_s00c9_1ca0* GetTribe();                              // 0x00c22f50
};
struct cTribeDisplayStrategy {
    int GetGroundSpearIndex(bool tribe);                                                     // 0x00cc89f0
    void SetGroundSpearTransform(bool tribe, int index, const Transform& t, int lifetimeMs);  // 0x00cca9e0
    cInteractiveOrnament* GetSpearOrnament(cTribe_s00c9_1ca0* tribe);                                   // 0x00cc98e0
};
struct cTribeModeStrategy_s00c9_1ca0 {
    static cTribeModeStrategy_s00c9_1ca0* Instance();           // 0x00cd40b0
    PV8 PV8 PV8 PV2 PV
    virtual cTribeDisplayStrategy* GetDisplayStrategy(); // +0x6c 0x0104bfe0
};
bool CombatLineTest(const Vector3& start, const Vector3& dir, float length, cSpatialObject** ppHit,
                    Vector3* pHitPos, cGameObject* pIgnore, int flags);              // 0x00cb69e0
bool SweepTestModel(const Vector3& start, const Vector3& dir, cModel_s00c9_1ca0* model, int* pBone, int a,
                    Vector3* pHitPos, int b, int c);                                // 0x009b6450
struct cGameDataPart {
    PV8 PV8 PV2 PV
    virtual int GetPoliticalID();                    // +0x4c
};
struct cLocomotivePart {
    PV8 PV2 PV
    virtual const Vector3& GetPosition();            // +0x2c
    virtual const Quaternion& GetOrientation();      // +0x30
    virtual float GetScale();                        // +0x34
    virtual void SetPosition(const Vector3& v);      // +0x38
    PV8 PV4 PV2
    virtual float GetFootprintRadius();              // +0x74
};
struct SpatialRef {
    cSpatialObject* mpObject;
    SpatialRef() : mpObject(0) {}
    ~SpatialRef() { if (mpObject) mpObject->Release(); }
};
struct CombatantRef {
    cCombatant* mpObject;
    __forceinline CombatantRef& operator=(cCombatant* p)
    {
        if (p != mpObject) {
            cCombatant* const pTemp = mpObject;
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    cCombatant* operator->() const { return mpObject; }
    operator cCombatant*() const { return mpObject; }
};
struct cSpear {
    PV4 PV2
    virtual cGameObject* GetOwner();                 // +0x18
    uint32_t pad04[4];
    Vector3 mLastPosition;                           // +0x14 (cArtilleryProjectile 0x518)
    uint32_t pad20[5];
    float mDamage;                                   // +0x34 (cSpear 0x538)
    CombatantRef mpTarget;                           // +0x38 (cSpear 0x53c)

    cGameDataPart* AsGameData() { return (cGameDataPart*)((char*)this - 0x504); }
    cLocomotivePart* AsLocomotive() { return (cLocomotivePart*)((char*)this - 0x4d0); }

    bool Update();
};
// ---- items of slice s00c91ca0 end

// ---- items of slice s00c92a90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_00f47380(void* p);                                                              // operator delete[]
extern "C" const char FUN_00_ALLOC_FILE[];                                                                   // EASTL allocator.h path string
extern int DAT_0157b7d0;                                              // type descriptor handed to the serializer
extern "C" void __cdecl FUN_0093aa70(void* stream, void* value, int n, int flag); // EA::IO::WriteUint32
extern "C" void* __cdecl FUN_00f473a0(uint32_t n, const char* name, int a, int b, const char* file, int line); // operator new
#define VF(p, off) (*(void**)((char*)(*(void**)p) + (off)))
struct Vec3_s00c9_2a90 {
    float x; // @0x00
    float y; // @0x04
    float z; // @0x08
};
struct CmpPos {
    float x; // @0x00
    float y; // @0x04
    float z; // @0x08
};
extern "C" void __cdecl FUN_00c92e20(Vec3_s00c9_2a90* first, int top, int heapSize, int pos, Vec3_s00c9_2a90 value, CmpPos cmp);
extern "C" void __cdecl FUN_00c90f50(Vec3_s00c9_2a90* first, int top, int pos, Vec3_s00c9_2a90 value, CmpPos cmp);
struct Rec60 {
    uint32_t f00;      // @0x00  (comparison key)
    uint8_t  pad04[0x28];
    void*    f2c;      // @0x2c
    void*    f30;      // @0x30
    uint8_t  pad34[0x10];
    void*    f44;      // @0x44
    void*    f48;      // @0x48  (owned array pointer, -4 holds a flag)
};
class cVarListSerializer_s00c9_2a90 {
public:
    void Init(void* list, void* type, int id);  // 0x00692f90
    bool Serialize(void* out);                  // 0x00692900
private:
    unsigned char mData[0x9ec];
};
struct Rec1c {
    uint8_t b0;         // @0x00
    uint8_t pad[3];
    float   f4;         // @0x04
    float   f8;         // @0x08
    float   fc;         // @0x0c
    float   f10;        // @0x10
    float   f14;        // @0x14
    float   f18;        // @0x18
};
struct ActionCircle {           // SP::cActionCircle prefix; only the dtor is called
    void dtor(void);            // 0x00afbad0 - SP::cActionCircle::~cActionCircle
};
class Deque {
public:
    int*   mp00;    // @0x00
    int    mn04;    // @0x04
    int**  mpp08;   // @0x08  current
    int*   mp0c;    // @0x0c  block
    int*   mp10;    // @0x10  block end
    int**  mpp14;   // @0x14  block array cursor
    // second sub-object used by FUN_00c92bd0
    int**  mpp18;   // @0x18
    int*   mp1c;    // @0x1c
    int*   mp20;    // @0x20
    int*   mp24;    // @0x24

    void FUN_01044f80(int, int);            // grow (member)
    void FUN_00c92b70(void);                // pop-like
    void FUN_00c92bd0(int** p);             // push-like
};
struct V4 { uint32_t v0, v1, v2, v3; };
extern "C" cPointerBlockIter* __cdecl FUN_00c908a0(void* local, V4 a, V4 b, V4 c);
class Thing {
public:
    uint32_t f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24; // 0x00..0x27

    void    Init(int, void*);                       // 0x00c8ed30 (member)
    void    FUN_00ca09f0(uint32_t);                 // member
    Thing*  FUN_00c93750(int32_t* p);
    Thing*  FUN_00c93810(int32_t* p);
};
// ---- items of slice s00c92a90 end

// ---- items of slice s00c93a40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl operator_delete__(void* p);
extern const char g_EastlAllocator[];          // 0x013ebb38 (only its address is used)
extern const char g_SimulatorName[];           // 0x013f09b4
extern "C" void* __cdecl FUN_00cd40b0();                                 // 0x00cd40b0
extern "C" void* __cdecl FUN_00829110(void** out, void* first, void* last,
                                      void* dst, void* ctx);             // 0x00829110
extern "C" void* __cdecl FUN_00b3d2c0();                                 // 0x00b3d2c0
extern "C" void* __cdecl FUN_00b3d300();                                 // 0x00b3d300
extern "C" void* __cdecl FUN_00b5b800();                                 // 0x00b5b800
extern "C" void* __cdecl FUN_01021300();                                 // 0x01021300
extern "C" void* __cdecl FUN_00d026d0();                                 // 0x00d026d0
extern "C" void  __cdecl FUN_00472fe0(void* out, const char* fmt, ...);  // 0x00472fe0
extern "C" void  __cdecl FUN_005f9450(void* str, const char* fmt, ...);  // 0x005f9450
struct Vec3_s00c9_3a40 { float x; float y; float z; };
struct IRef {
  virtual void AddRef();
  virtual void Release();
};
struct cPointerVector_s00c9_3a40 {
  void*    mpBegin;       // 0x00
  void*    mpEnd;         // 0x04
  void*    mpCapacity;    // 0x08
  uint32_t mAllocator[3]; // 0x0c

  cPointerVector_s00c9_3a40* CopyFrom(const cPointerVector_s00c9_3a40* src);   // 0x00c93810
};
struct cFishingHotSpot {
  Vec3_s00c9_3a40             mPos;            // 0x00
  float            mFood;           // 0x0c
  float            mMaxFood;        // 0x10
  float            mResupply;       // 0x14
  s32              mCubeIndex[3];   // 0x18
  IRef*            mpEffect;        // 0x24
  IRef*            mpHitSphere;     // 0x28
  u32              mPad_2c;         // 0x2c
  u32              mStartTimeLow;   // 0x30
  u32              mStartTimeHigh;  // 0x34
  bool             mbActive;        // 0x38
  bool             mbRemove;        // 0x39
  u8               mPad_3a[2];      // 0x3a
  IRef*            mpOrnament;      // 0x3c
  cPointerVector_s00c9_3a40   mPointers;       // 0x40

  cFishingHotSpot(const cFishingHotSpot& src);
};
struct HotSpotRow;
extern "C" HotSpotRow* __cdecl HotSpotLowerBound(HotSpotRow* first, HotSpotRow* last,
                                                 u32* key, u8 less);   // 0x00c92d50
extern HotSpotRow* g_HotSpotBegin;   // 0x0157abb0
extern HotSpotRow* g_HotSpotEnd;     // 0x0157abb4
extern u8          g_HotSpotLess;    // 0x0157b7c8
struct HotSpotRow {
  u32             mKey;       // 0x00
  u8              mPad_04[4]; // 0x04
  cFishingHotSpot mSpot;      // 0x08
};
cFishingHotSpot* findHotSpot(u32 key);
extern "C" void __cdecl HeapMake(Vec3_s00c9_3a40* first, Vec3_s00c9_3a40* last, float x, float y, float z);          // 0x00c938f0
extern "C" void __cdecl HeapAdjust(Vec3_s00c9_3a40* first, int top, int heapSize, int pos,
                                   Vec3_s00c9_3a40 value, float x, float y, float z);                    // 0x00c92e20
extern "C" void __cdecl HeapSort(Vec3_s00c9_3a40* first, Vec3_s00c9_3a40* last, float x, float y, float z);          // 0x00c93980
void __cdecl PartitionPositions(Vec3_s00c9_3a40* first, Vec3_s00c9_3a40* last,
                                float px, float py, float pz,
                                float qx, float qy, float qz);
void __cdecl PartialSortPositions(Vec3_s00c9_3a40* first, Vec3_s00c9_3a40* mid, Vec3_s00c9_3a40* last,
                                  float x, float y, float z);
struct cSub34 { void** mpVtable; };                 // embedded at cTribe+0x34
struct cSpatial120Base {
  void** mpVtable;          // 0x000
  u8     mPad_004[0x10c];   // 0x004 .. 0x10f  (total 0x110)
};
struct cString;
struct cSpatialView {
  void** mpVtable;          // 0x000 (cTribe+0x120)
  u8     mPad_004[0x210];   // 0x004 .. 0x213
  bool   mbFlag214;         // 0x214 (cTribe+0x334)

  void GetDebugToolTip(cString* out);   // 0x00c94470
};
struct TreeNode {
  TreeNode* mpLeft;     // 0x00
  TreeNode* mpRight;    // 0x04
  TreeNode* mpParent;   // 0x08
  u32       mColor;     // 0x0c
  u32       mKey;       // 0x10
  u32       mValue;     // 0x14
};
struct TreeHeader {
  TreeNode* mpEnd;      // 0x00
  u32       mSize;      // 0x04
  TreeNode* mpRoot;     // 0x08
  u32       mPad_0c;    // 0x0c
  u32       mPad_10;    // 0x10
  u32       mValue;     // 0x14
};
struct WString {
  wchar_t* mpBegin;      // 0x00
  wchar_t* mpEnd;        // 0x04
  wchar_t* mpCapacity;   // 0x08
};
struct cTribe_s00c9_3a40;
struct cString {
  void* mpBegin;     // 0x00
  void* mpEnd;       // 0x04
  void* mpCapacity;  // 0x08

  void ctor();                                  // 0x006b5060
  void dtor();                                  // 0x006b5240
  bool Load(u32 id, u32 a, int b);              // 0x006b54b0
  const wchar_t* GetText();                     // 0x006b55c0
  void Append(const char* a, const char* b);    // 0x00455d60
};
struct cSpeciesProfile {
  void** mpVtable;
  u8     mPad_04[0x5c];

  void GetUiName(WString* out);                 // 0x004da330
};
struct cGameNounManager {
  void** mpVtable;
  u8     mPad_04[0x100];

  void FinishUpdate();                          // 0x00b6e1f0
  void* GetPlayerTribe();                       // 0x00bfc5f0
  void* GetPlayerCivilization();                // 0x00b25fb0
};
struct cRelationshipManager {
  void* GetPlayerString(void* out, cTribe_s00c9_3a40* tribe, void* player);   // 0x00d01db0
  void* GetDebugString(void* out, u32 id, void* player);           // 0x00d01bb0
  float GetRelationship(void* a);                                  // 0x00d00a10
  float CalculateRelationshipEvent(void* a, void* b);              // 0x00d03d70
};
struct cStrategyResult {
  void Finish();                                // 0x00ccc400
};
struct cTribePlanner {
  u8     mPad_000[0x34];
  void** mpVtable34;       // cTribePlanner+0x34
};
struct cPos4ec {
  u8   mPad_000[0x4ec];
  Vec3_s00c9_3a40 mPos;               // 0x4ec
};
struct cTarget4c {
  u8   mPad_000[0x4c];
  Vec3_s00c9_3a40 mPos;               // 0x4c
};
struct cTarget180 {
  u8            mPad_000[0x180];
  cTarget4c*    mpTarget;  // 0x180
};
struct cCitizen {
  void**         mpVtable;     // 0x000
  u8             mPad_004[0xb1c]; // 0x004
  cPos4ec*       mpB20;        // 0xb20
  u8             mPad_b24[0x30];  // 0xb24
  cTarget180*    mpB54;        // 0xb54

  cSub34* sub() { return (cSub34*)((char*)this + 0x34); }
  u32  ToolEffect();                           // 0x00c22a70
  void SetToolEffect(u32 tool, int slot);      // 0x00c24f40
};
struct CitizenVec {
  cCitizen** mpBegin;      // 0x00
  cCitizen** mpEnd;        // 0x04
};
struct cNameMap230 {
  u32                mPad_00;         // 0x00
  cGameNounManager*  mpNounManager;   // 0x04 (cTribe+0x234)
  u32                mMap;            // 0x08 (cTribe+0x238)

  void Setup(WString* src);           // 0x00b6f380
};
struct cTribe_s00c9_3a40 {
  void**            mpVtable;         // 0x000
  u8                mPad_004[0x30];   // 0x004
  cSub34            mSub34;           // 0x034
  u8                mPad_038[0xe8];   // 0x038 .. 0x11f
  cSpatial120Base   mSpatial120;      // 0x120 .. 0x22f
  cNameMap230       mNameMap230;      // 0x230
  TreeHeader        mTree;            // 0x23c .. 0x253
  u8                mPad_254[0xe0];   // 0x254 .. 0x333
  bool              mbFlag334;        // 0x334
  u8                mPad_335[3];      // 0x335
  u32               mCount338;        // 0x338
  bool              mbFlag33c;        // 0x33c
  u8                mPad_33d[0x2b];   // 0x33d .. 0x367
  cTribePlanner*    mpPlanner;        // 0x368
  u8                mPad_36c[0x1560]; // 0x36c .. 0x18cb
  cSpeciesProfile*  mpSpeciesProfile; // 0x18cc

  cSub34* sub() { return (cSub34*)((char*)this + 0x34); }
  cGameNounManager* nounManager() { return mNameMap230.mpNounManager; }
};
extern "C" Vec3_s00c9_3a40* __cdecl FUN_00b6f0c0(cGameNounManager* mgr);            // 0x00b6f0c0
extern u8 g_GameModeTribe;    // 0x01654c02
extern u8 g_GameModeCiv;      // 0x01654c04
extern u8 g_GameModeSpace;    // 0x01654c05
// ---- items of slice s00c93a40 end

// ---- items of slice s00c947d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(unsigned int, void* p) throw() { return p; }
void* __cdecl operator_new(unsigned size, const char* file, int a, int b, int c, int d);   // 0xf473a0
struct Vector3_s00c9_47d0 {
    float x, y, z;
    Vector3_s00c9_47d0() {}
    Vector3_s00c9_47d0(float fx, float fy, float fz) : x(fx), y(fy), z(fz) {}
    Vector3_s00c9_47d0(const Vector3_s00c9_47d0& o) : x(o.x), y(o.y), z(o.z) {}
};
inline float AbsFloat(float f) { return f < 0.0f ? -f : f; }
struct IRefCounted {
    virtual void AddRef();     // +0x00
    virtual void Release();    // +0x04
};
struct cToolObject : IRefCounted {
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
    virtual void Unload();     // +0xc0
};
struct sp_vector_allocator_s00c9_47d0 {
    const char* mpName;
    uint32_t mFlags;
    sp_vector_allocator_s00c9_47d0() {}
    void deallocate(void* p) { if (((uint32_t*)p)[-1]) operator_delete__(p); }
};
template <class T> inline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}
template <class T> T* __cdecl copy_impl(const T* first, const T* last, T* dest);     // 0xa7a930
template <class T> T* __cdecl uninitialized_copy(const T* first, const T* last, T* dest);  // 0xc92ce0
template <class T> T* __cdecl grow_copy(unsigned n, const T* first, const T* last);  // 0xc93d60
template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s00c9_47d0 mAllocator;

    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector() { destruct(mpBegin, mpEnd); if (mpBegin) mAllocator.deallocate(mpBegin); }
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    unsigned capacity() const { return (unsigned)(mpCapacity - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](unsigned i) { return mpBegin[i]; }
    T& back() { return *(mpEnd - 1); }

    void reserve(unsigned n);                       // out-of-line instance
    T* erase(T* first, T* last);                    // out-of-line instance (0x50f740 / 0xc83c90)
    void DoInsertValue(T* pos, const T& value);     // out-of-line instance
    SpVector& operator=(const SpVector& x);
    void resize(unsigned n);

    T* EraseInline(T* first, T* last)
    {
        T* const pNewEnd = copy_impl(last, mpEnd, first);
        destruct(pNewEnd, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new ((void*)mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void push_back()
    {
        if (mpEnd < mpCapacity)
            ::new ((void*)mpEnd++) T();
        else
            DoInsertValue(mpEnd, T());
    }
};
struct AutoRef {                                        // 4-byte EASTL AutoRefCount
    IRefCounted* mpObject;
    AutoRef() : mpObject(0) {}
    AutoRef(const AutoRef& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRef() { if (mpObject) mpObject->Release(); }
    AutoRef& operator=(const AutoRef& x)
    {
        IRefCounted* const pObject = x.mpObject;
        if (pObject != mpObject) {
            IRefCounted* const pOld = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }
};
struct cToolSlot {                                      // 4-byte tool reference
    cToolObject* mpObject;
    cToolSlot() : mpObject(0) {}
    cToolSlot(const cToolSlot& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~cToolSlot() { if (mpObject) mpObject->Unload(); }
    cToolSlot& operator=(const cToolSlot& x)
    {
        cToolObject* const pObject = x.mpObject;
        if (pObject != mpObject) {
            cToolObject* const pOld = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pOld)
                pOld->Unload();
        }
        return *this;
    }
};
struct cSpatial_s00c9_47d0 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual const Vector3_s00c9_47d0& GetPosition();            // +0x2c
    virtual const Quaternion& GetOrientation();      // +0x30
    virtual void v34();
    virtual void SetPosition(const Vector3_s00c9_47d0& p);      // +0x38
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
    virtual bool IsVisible();                        // +0x58
    virtual bool GetFacing(Vector3_s00c9_47d0* out);            // +0x5c
};
struct cToolNode {                                   // cTribe + 0x260 target
    uint32_t pad00[13];
    cSpatial_s00c9_47d0 mSpatial;                               // +0x34
};
struct cActionCircle_s00c9_47d0 {
    uint8_t mData[0x64];
    void SetAtCenter(const Vector3_s00c9_47d0& center, float altitude, const Vector3_s00c9_47d0* facing, float radius);  // 0xaf9cf0
    void EmitCopy(const Vector3_s00c9_47d0& pos, float radius);                                              // 0xafec00
    void Execute();                                                                                // 0xafaec0
};
struct cEmptyBubble_s00c9_47d0 {                                // 20 bytes
    Vector3_s00c9_47d0 mPosition;
    float mAmount;                                   // +0x0c
    uint32_t mUnused;                                // +0x10
    cEmptyBubble_s00c9_47d0() : mAmount(0.0f), mUnused(0) {}
};
struct cTribeChatArea_s00c9_47d0 { uint32_t mData[5]; };         // 20 bytes
struct cLocaleSeparators {                           // cTribe + 0x18cc target
    uint32_t pad00[0x182];
    uint32_t mDecimalSep;                            // +0x608
    uint32_t mThousandSep;                           // +0x60c
};
struct cTribe_s00c9_47d0 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();

    uint8_t pad00[0x120 - 0x004];                    // +0x004 .. +0x120
    cSpatial_s00c9_47d0 mSpatial;                               // +0x120 (vftable only)
    uint8_t pad184[0x260 - 0x124];                   // +0x124 .. +0x260
    cToolNode* mpToolNode;                           // +0x260
    uint8_t pad264[0x2a8 - 0x264];                   // +0x264 .. +0x2a8
    SpVector<cEmptyBubble_s00c9_47d0> mEmptyBubbles;            // +0x2a8 (0x14 bytes)
    uint8_t pad2bc[0x2d4 - 0x2bc];                   // +0x2bc .. +0x2d4
    void* mpToolLayoutKey;                           // +0x2d4
    uint8_t pad2d8[0x340 - 0x2d8];                   // +0x2d8 .. +0x340
    SpVector<AutoRef> mRefObjects;                   // +0x340 (0x14 bytes)
    SpVector<cToolSlot> mToolSlots;                  // +0x354 (0x14 bytes)
    void* mpToolLayout;                              // +0x368
    uint8_t pad36c[0x3b4 - 0x36c];                   // +0x36c .. +0x3b4
    cActionCircle_s00c9_47d0 mActionCircle;                     // +0x3b4 (0x64 bytes)
    SpVector<Vector3_s00c9_47d0> mHutLocations;                 // +0x418 (0x14 bytes)
    uint8_t pad42c[0x18cc - 0x42c];                  // +0x42c .. +0x18cc
    cLocaleSeparators* mpLocaleSeparators;           // +0x18cc

    void ShowFishingString(float amount, const Vector3_s00c9_47d0* pos);            // 0xc947d0
    void DoShowFishingString(uint32_t effectID, const wchar_t* format,
                             wchar_t sign, wchar_t thousandSep,
                             float amount, const Vector3_s00c9_47d0* pos);
    void SquirtFishingSplash(float radius);                              // 0xc94b50
    void ResetToolLayout();                                              // 0xc951d0
    void AddPanicBubble(const Vector3_s00c9_47d0& pos, float amount, int empireID); // 0xc95540
    void RemoveRefObject(void* key);                                     // 0xc950f0
    void RemoveToolSlot(void* key);                                      // 0xc95150
};
struct cFishingHotSpot_s00c9_47d0 {
    Vector3_s00c9_47d0 mCenter;                                 // +0x00
    float mRadius;                                   // +0x0c
    float mScale;                                    // +0x10
    float mFacing;                                   // +0x14
    Vector3_s00c9_47d0 mDirection;                              // +0x18
    AutoRef mpFirst;                                 // +0x24
    AutoRef mpSecond;                                // +0x28
    uint32_t mCachedCost;                            // +0x2c (derived, not copied)
    uint32_t mField30;                               // +0x30
    uint32_t mField34;                               // +0x34
    bool mbFlag38;                                   // +0x38
    bool mbFlag39;                                   // +0x39
    uint8_t pad3a[2];                                // +0x3a
    AutoRef mpThird;                                 // +0x3c
    SpVector<Vector3_s00c9_47d0> mPoints;                       // +0x40 (0x14 bytes)

    cFishingHotSpot_s00c9_47d0& operator=(const cFishingHotSpot_s00c9_47d0& x);   // 0xc95010
};
namespace SP {
struct cEffectsManager {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual bool CreateEffect(uint32_t effectID, int flags, void** out);   // +0x2c
};
}
namespace SP {
cEffectsManager* __cdecl EffectsManager();                      // 0x67ddd0
}
namespace SP {
struct cEffect_s00c9_47d0 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual void SendMessage(const void* msg);                  // +0x18
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
    virtual void SetText(int slot, void* object);               // +0x4c
};
}
namespace SP {
int __cdecl PlayerEmpireID();                                   // 0x1021090 cSPLivingUniverse::GetPlayerEmpireID
}
struct cCheatObject2 : IRefCounted {
    virtual void v08();            // +0x08
    cCheatObject2();               // 0x57a6d0
    wchar_t mText[8];              // +0x0c
};
struct cXformMsg {                 // 0x38
    uint16_t mFlags;
    uint16_t mVersion;
    Vector3_s00c9_47d0 mTranslation;
    void SetTranslation(const Vector3_s00c9_47d0& t) { mTranslation = t; mFlags |= 4; ++mVersion; }
};
void __cdecl cXformMsg_ctor(cXformMsg* self);                                // 0x434040
namespace EA {
namespace Locale {
void __cdecl SetNumberString(int value, int high, wchar_t* out, int size);   // 0x881ae0
}
}
int __cdecl WStr_Format(wchar_t* out, const wchar_t* format, ...);           // 0x41e050
bool __cdecl ResolveToolData(void* key, uint32_t code, int* count, const Vector3_s00c9_47d0** data);  // 0x6a0990
Vector3_s00c9_47d0 __cdecl XformVector(const Vector3_s00c9_47d0& v, const Quaternion& q);          // 0x59aed0
cToolSlot* __cdecl FindToolSlot(cToolSlot* first, cToolSlot* last, const void* key);  // 0xc93640
void __cdecl InsertFillChatAreas(cTribeChatArea_s00c9_47d0* end, unsigned n, const cTribeChatArea_s00c9_47d0& v);      // 0xc93e60
cTribeChatArea_s00c9_47d0* __cdecl copy_Rec20(const cTribeChatArea_s00c9_47d0* first, const cTribeChatArea_s00c9_47d0* last,
                                   cTribeChatArea_s00c9_47d0* dest);                    // 0x951bf0
void __thiscall cTribe_s00c9_47d0::DoShowFishingString(uint32_t effectID, const wchar_t* format,
                                            wchar_t sign, wchar_t thousandSep,
                                            float amount, const Vector3_s00c9_47d0* pos)
{
    void* pEffect = 0;
    if (!SP::EffectsManager()->CreateEffect(effectID, 0, &pEffect))
        return;

    cXformMsg msg;
    cXformMsg_ctor(&msg);
    msg.SetTranslation(*pos);
    ((SP::cEffect_s00c9_47d0*)pEffect)->SendMessage(&msg);

    cCheatObject2* pCheat = (cCheatObject2*)operator_new(sizeof(cCheatObject2), "Simulator", 0, 0, 0, 0);
    if (pCheat) {
        new (pCheat) cCheatObject2();
        pCheat->AddRef();
    }

    const float magnitude = AbsFloat(amount);
    int value = (int)magnitude;
    if (magnitude < (float)value)
        --value;

    wchar_t text[0x40];
    EA::Locale::SetNumberString(value, value >> 31, text, 0x40);

    cLocaleSeparators* pSeparators = mpLocaleSeparators;
    if (pSeparators && pSeparators->mThousandSep != 0 && pSeparators->mDecimalSep != 0)
        WStr_Format(pCheat->mText, format, thousandSep, sign, text);
    else if (pSeparators && pSeparators->mThousandSep != 0)
        WStr_Format(pCheat->mText, format, 0x268e, sign, text);
    else
        WStr_Format(pCheat->mText, format, 0x268d, sign, text);

    ((SP::cEffect_s00c9_47d0*)pEffect)->SetText(8, pCheat);
    ((SP::cEffect_s00c9_47d0*)pEffect)->v08();

    if (pCheat)
        pCheat->Release();
    if (pEffect)
        ((SP::cEffect_s00c9_47d0*)pEffect)->v04();
}
namespace SP {
namespace {
struct ComparePositions {
    Vector3_s00c9_47d0 mCenter;
    bool operator()(const Vector3_s00c9_47d0& a, const Vector3_s00c9_47d0& b) const;
};
}
}
Vector3_s00c9_47d0* __cdecl SelectPivot(Vector3_s00c9_47d0* first, Vector3_s00c9_47d0* mid, Vector3_s00c9_47d0* last,
                             SP::ComparePositions compare);                  // 0xc90b40
Vector3_s00c9_47d0* __cdecl PartitionRange(Vector3_s00c9_47d0* first, Vector3_s00c9_47d0* last, const Vector3_s00c9_47d0& pivot,
                                SP::ComparePositions compare);               // 0xc940d0
void __cdecl InsertionSort(Vector3_s00c9_47d0* first, Vector3_s00c9_47d0* last, SP::ComparePositions compare);   // 0xc94270
struct DequeIter2 {
    void* mpBlock;       // +0x00
    void* mpCurrent;     // +0x04
    void* mpFirst;       // +0x08
    void* mpLast;        // +0x0c
    DequeIter2& operator+=(int n);     // 0x7a9a80
};
struct cTextureAsyncQueueEntry_s00c9_47d0 { uint32_t mData[4]; };     // 16 bytes
struct cTextureAsyncQueue {
    uint32_t pad00[2];
    cTextureAsyncQueueEntry_s00c9_47d0* mpBegin;        // +0x08
    cTextureAsyncQueueEntry_s00c9_47d0* mpEnd;          // +0x0c
    cTextureAsyncQueueEntry_s00c9_47d0* mpCapacity;     // +0x10
    cTextureAsyncQueueEntry_s00c9_47d0** mpBlocks;      // +0x14
    cTextureAsyncQueueEntry_s00c9_47d0** mpBlockEnd;    // +0x18
    cTextureAsyncQueueEntry_s00c9_47d0** mpBlockBegin;  // +0x1c
    cTextureAsyncQueueEntry_s00c9_47d0** mpFreeBlock;   // +0x20
    cTextureAsyncQueueEntry_s00c9_47d0** mpLastBlock;   // +0x24

    cTextureAsyncQueueEntry_s00c9_47d0* Insert(DequeIter2* pResult, DequeIter2 pos,
                                    const cTextureAsyncQueueEntry_s00c9_47d0& value);   // 0xc95660
};
void __cdecl DequeInsertFront(cTextureAsyncQueueEntry_s00c9_47d0* pos, const cTextureAsyncQueueEntry_s00c9_47d0* value,
                              cTextureAsyncQueueEntry_s00c9_47d0* first);      // 0xbff1b0
void __cdecl DequeInsertBack(cTextureAsyncQueueEntry_s00c9_47d0* pos, const cTextureAsyncQueueEntry_s00c9_47d0* value,
                             cTextureAsyncQueueEntry_s00c9_47d0* last);        // 0xc94e50
void __cdecl DequeOnInsertFront();                                  // 0xc92b70
void __cdecl DequeOnInsertBack();                                   // 0xabf980
struct cResourceReader {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void v1c();                    // +0x1c (finish read)
    virtual void* GetStream();             // +0x20
    virtual void* GetStreamOwner();        // +0x24
    void ReadPositions(SpVector<Vector3_s00c9_47d0>* pOut);      // 0xc95780
};
void __cdecl ReadInt32(void* pStream, int* pValue, int count, int async);   // 0x93a780
void __cdecl Vec3Vec_Reserve(SpVector<Vector3_s00c9_47d0>* pVector, unsigned n);       // 0x41e4d0
void __cdecl ReadPositionValue(cResourceReader* pReader, Vector3_s00c9_47d0* pOut);    // 0xae2ed0
struct cBubbleOwner {                 // sub-object at +0 of every bubble node
    void Destroy();                   // 0xabf900 (thiscall, no arguments)
};
struct cBubbleNode {
    uint32_t mType;                    // +0x00
    cBubbleOwner mOwner;               // +0x04
    uint8_t pad08[0x30 - 0x08];        // +0x08 .. +0x30
    cBubbleNode* mpNext;               // +0x30
};
// ---- items of slice s00c947d0 end

// ---- items of slice s00c96950 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable: 4100 4189 4244 4311 4312 4244)
struct Vec2 { void* pBeg; void* pEnd; void* pCap; };
void* FUN_00c929a0(u32* pOut, void* pArg);                     // 0x00c929a0
void  FUN_00c93750(void* pOut, void* pIn);                     // 0x00c93750
struct CalleeSet {
    void  FUN_00ca09f0(u32 a);                        // 0x00ca09f0
    void  FUN_00c94d60(void* a, void* b, u32 c);      // 0x00c94d60
    void  FUN_00abf900();                             // 0x00abf900  sub-object dtor
    void  FUN_00cee7e0();                             // 0x00cee7e0
    void  FUN_00e25bd0(void* beg, void* end);         // 0x00e25bd0  vector clear
    void  FUN_00b225d0(void* a);                      // 0x00b225d0
    void  FUN_00b48e40(void* beg, void* end);         // 0x00b48e40
    void  FUN_00ac0450();                             // 0x00ac0450
    void  FUN_00afafd0();                             // 0x00afafd0
    void  FUN_00c93700(void* a, void* b);             // 0x00c93700
    void  FUN_00ce0a20(u32 a);                        // 0x00ce0a20
    void  FUN_00c95930(void* beg, void* end);         // 0x00c95930
    void  FUN_00b6ee10();                             // 0x00b6ee10
    void  FUN_00c8b2e0();                             // 0x00c8b2e0
    void  FUN_00c01e80();                             // 0x00c01e80
    void  FUN_00421cf0();                             // 0x00421cf0
    void  FUN_00b21410(void* a);                      // 0x00b21410
    float FUN_00b7e390();                             // 0x00b7e390
    void* FUN_00b09340();                             // 0x00b09340
    void* FUN_00fcc210();                             // 0x00fcc210
    void  FUN_00afa0a0();                             // 0x00afa0a0
    void  FUN_00c95d70(void* a, u32 b);               // 0x00c95d70
    void  FUN_00c96a00(void* pKey);                   // 0x00c96a00
};
#define SELF(o) ((CalleeSet*)(o))
struct HashNode { u32 mKey; u8 mGap04[0x2c]; HashNode* pNext; };
struct CHash {
    u8      mGap00[0x04];      // +0x00
    void*   mpBuckets;         // +0x04
    u32     mW08;              // +0x08  bucket slot count
    u32     mW0c;              // +0x0c  element count

    void* FUN_00c96950(void* pArg);
    u32   FUN_00c96a00(void* pKey);
};
struct Bkt394 { void** mpBuckets; u32 mWSlots; void** mpSentinel; };
struct Sub120 { void** mv; };
struct CRes {
    void**  mv;                // +0x000  vtable
    void*   mp04;              // +0x004
    u32     mW08;              // +0x008
    u32     mW0c;              // +0x00c
    u8      mGap10[0x110];     // +0x010 .. 0x120
    Sub120  mSub120;           // +0x120
    u8      mGap124[0xd0];     // +0x124 .. 0x1f4
    u8      mSub1f4[0x18];     // +0x1f4
    u8      mSub20c[0x24];     // +0x20c .. 0x230
    u8      mSub230[0x30];     // +0x230 .. 0x260
    void*   mp260;             // +0x260
    u8      mGap264[0x2c];     // +0x264 .. 0x290
    void*   mp290;             // +0x290
    u8      mGap294[0x40];     // +0x294 .. 0x2d4
    void*   mp2d4;             // +0x2d4
    u8      mGap2d8[0x29];     // +0x2d8 .. 0x301
    u8      mB301;             // +0x301
    u8      mGap302[0x12];     // +0x302 .. 0x314
    Vec2    mVec314;           // +0x314  Vec3 / ptr list
    u8      mGap320[0x20];     // +0x320 .. 0x340
    Vec2    mVec340;           // +0x340
    u8      mGap34c[0x08];     // +0x34c .. 0x354
    Vec2    mVec354;           // +0x354
    u8      mGap360[0x08];     // +0x360 .. 0x368
    void*   mp368;             // +0x368
    Vec2    mVec36c;           // +0x36c
    u8      mGap378[0x08];     // +0x378 .. 0x380
    Vec2    mVec380;           // +0x380
    u8      mGap38c[0x08];     // +0x38c .. 0x394
    Bkt394  mBkt394;           // +0x394
    u8      mGap3a0[0x14];     // +0x3a0 .. 0x3b4
    u8      mSub3b4[0x50];     // +0x3b4
    Vec2    mVec404;           // +0x404  0x18-stride records
    u8      mGap410[0xd4];     // +0x410 .. 0x4e4
    CHash   mHash4e4;          // +0x4e4  hash-set sub-object
    u8      mGap4f0[0x13dc];   // +0x4f0 .. 0x18cc
    u8      mArr18cc[0x38];    // +0x18cc
    u8      mGap1904[0xc0];    // +0x1904 .. 0x19c4
    void*   mp19c4;            // +0x19c4
    void*   mp19c8;            // +0x19c8
    void*   mp19cc;            // +0x19cc
    void*   mp19d0;            // +0x19d0
    void*   mp19d4;            // +0x19d4

    void* FUN_00c96950(void* pArg);
    u32   FUN_00c96a00(void* pKey);
    void  FUN_00c96a80();
    void  FUN_00c96e80(u32 a);
    void  FUN_00c96e90(void* pArg);
    void* FUN_00c97020();
};
// ---- items of slice s00c96950 end

// ---- items of slice s00c99140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int __cdecl FUN_00a1ad10();                                                      // 0xa1ad10
extern "C" char __cdecl FUN_006a0ae0(void* p, unsigned model, void* a, void* b);            // 0x6a0ae0
extern "C" unsigned __cdecl GetPlayerEmpireID();                                            // 0x1021090
struct WString_s00c9_9140 {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08
    void __thiscall Assign(const WString_s00c9_9140& src);   // 0xb6f380
};
struct VtblObj { void* mpVtbl; };   // start of any object whose first dword is its vtable
struct RefObj  { void* mpVtbl; };   // refcounted object: slot 0 = AddRef, slot 4 = Release
struct VObj94 {
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
virtual void v06c();
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void v080();
virtual void v084();
virtual void v088();
virtual void v08c();
    virtual void v090();
    virtual void OnRequest(void* req);        // +0x94
};
#define VSLOT(p, o) (*(void**)(*(char**)(p) + (o)))
typedef void   (__thiscall* TFnV)(void*);
typedef void*  (__thiscall* TFnP)(void*);
typedef int    (__thiscall* TFnI)(void*);
typedef float  (__thiscall* TFnF)(void*);
typedef char   (__thiscall* TFnC)(void*);
typedef void   (__thiscall* TFnVP)(void*, void*);
typedef void*  (__thiscall* TFnPP)(void*, void*);
typedef char   (__thiscall* TFnCIP)(void*, int, void*);
typedef void*  (__thiscall* TFnPI)(void*, int);
typedef void   (__thiscall* TFnVPPP)(void*, void*, void*, void*);
typedef char   (__thiscall* TFnCPPP)(void*, void*, void*, void*);
typedef void*  (__thiscall* TFnPFI)(void*, float, int);
typedef void   (__thiscall* TFnVPPPP)(void*, void*, void*, void*, void*);
struct TribeToolBody {
    char mData[0x58];
    void __thiscall CopyFrom(const TribeToolBody& src);          // 0xc93dc0
    TribeToolBody& __thiscall operator=(const TribeToolBody& s); // 0xc95010
};
struct TribeToolRef {
    void* mpVtbl;                // +0x00
    int   miUnk04;               // +0x04
    TribeToolBody mBody;         // +0x08
};
struct ToolVec {
    TribeToolRef* mpBegin;       // +0x00
    TribeToolRef* mpEnd;         // +0x04
    TribeToolRef* mpCap;         // +0x08
    void*         mpUnk0C;       // +0x0c
    void*         mpAllocator;   // +0x10
    void __thiscall InsertAt(TribeToolRef* pos, const TribeToolRef* val);
    TribeToolRef* __thiscall PushBackAt(TribeToolRef* pos, const TribeToolRef* val);
};
struct ActionSlot {
    char  mPad00[0x0c];
    float mf0C;                  // +0x0c
    float mf10;                  // +0x10
    float mf14;                  // +0x14
    void __thiscall Clear();                 // 0xafa0a0
    void __thiscall Reserve(void* obj);      // 0xafa030
};
struct ActionCircle_s00c9_9140 {
    char  mPad00[0x14];
    float mfRadius;              // +0x14
    float mf18;                  // +0x18
    float mf1C;                  // +0x1c
    char  mPad20[0x08];
    char  mb28;                  // +0x28
    char  mPad29[0x50 - 0x29];
    void __thiscall Clear();                          // 0xafaec0
    ActionSlot* __thiscall FindSlot(const Vec3* p);   // 0xafad70
    void __thiscall AssignSlot(ActionSlot* s);        // 0xafc410
};
struct TribeHut {
    char     mPad000[0x34];
    VtblObj  mSpatial;           // +0x34
    char     mPad038[0x120 - 0x38];
    struct {
        void* mpVtbl;
        void __thiscall SetHeight(float v);   // 0xf924e0
    } mQueue;                    // +0x120
    char     mPad124[0x14c - 0x124];
    float    mf14C;              // +0x14c
    void __thiscall RefreshModelProps();   // 0xc9c680
};
struct TribeTool {
    char          mPad000[0x34];
    VtblObj       mSpatial;      // +0x34
    char          mPad038[0xa5 - 0x38];
    unsigned char mbA5;          // +0xa5
};
struct cSpeciesProfile_s00c9_9140 {
    char   mPad000[0x52c];
    void*  mp52C;                // +0x52c
    char   mPad530[0x608 - 0x530];
    unsigned mi608;              // +0x608
    unsigned mi60C;              // +0x60c
    void __thiscall GetUiName(WString_s00c9_9140* out);   // 0x4da330
};
struct RbTree {
    void** __thiscall find(void* key, void* out);   // 0xe5c780
};
struct ReservationGrid {
    char    mPad0000[0x984];
    ToolVec mEntries;            // +0x984
    char    mPad0998[0x1374 - 0x998];
    void* __thiscall GetReservedList();                                  // 0xcc7070
    void  __thiscall RemoveReservedByID(void* entries, const void* id);  // 0xcc86a0
    void  __thiscall AddReserved(void* entries, const Vec3* pos, float radius,
                                 const void* id);                        // 0xcc8350
    float __thiscall ComputeGridResolution(float a, float b);            // 0xcc7830
};
struct cPlanetModel_s00c9_9140 {
    void* mpVtbl;
    float* __thiscall DirectionToSurfacePosition(Vec3* out, const Vec3* dir);   // 0xb815a0
    void   __thiscall BuildSurfaceOrientation(Vec3* out, const Vec3* a,
                                              const Vec3* b);                  // 0xb7f250
};
struct cGameNounManager_s00c9_9140 {
    void* mpVtbl;
    void* __thiscall CreateNoun(unsigned type);        // 0xb20c60
    void  __thiscall AttachNoun(void* noun);           // 0xb1fe00
};
struct cPropertyManager {
    void* mpVtbl;
};
struct cTerraformingManager {
    void* mpVtbl;
    void __thiscall InitTerrain();                     // 0xbbc3f0
};
struct cReserveParams {
    float __thiscall GetRadius(void* profile);         // 0xce6a40
    float __thiscall GetHeight(int index);             // 0xce6910
};
struct PtrList { void** mpBegin; void** mpEnd; };
struct cTribe_s00c9_9140 {
    char     mPad0034[0x34];
    VtblObj  mObj34;             // +0x34
    char     mPad0038[0x120 - 0x38];
    VtblObj  mQueue120;          // +0x120
    char     mPad0124[0x230 - 0x124];
    WString_s00c9_9140  mName230;           // +0x230
    RbTree   mTree238;           // +0x238
    char     mPad023C[0x260 - 0x23c];
    TribeHut* mpHut260;          // +0x260
    float     mfRadius268;       // +0x268
    char      mPad026C[0x2d4 - 0x26c];
    RefObj*   mpTool2d4;         // +0x2d4
    char      mPad02D8[0x2e8 - 0x2d8];
    Vec3      mVec2e8;           // +0x2e8
    char      mPad02F4[0x368 - 0x2f4];
    TribeHut* mpHut368;          // +0x368
    char      mPad036C[0x3b4 - 0x36c];
    ActionCircle_s00c9_9140 mCircle3b4;     // +0x3b4
    ActionSlot*  mpSlotsBegin;   // +0x404
    ActionSlot*  mpSlotsEnd;     // +0x408
    ActionSlot*  mpSlotsCap;     // +0x40c
    char         mPad0410[0x558 - 0x410];
    ReservationGrid mRGrid558;   // +0x558
    cSpeciesProfile_s00c9_9140* mpProfile18CC;  // +0x18cc
    char             mPad18D0[0x19c4 - 0x18d0];
    TribeTool* mpTool19C4;       // +0x19c4
    TribeTool* mpTool19C8;       // +0x19c8
    char       mPad19CC[0x19d0 - 0x19cc];
    TribeTool* mpTotem19D0;      // +0x19d0

    bool __thiscall SetupTotemPole();  // 0x00c99140 (cTribe::SetupTotemPole)
    void __thiscall UpdateGridAndHutArea(int unused);  // 0x00c99550 (cTribe::UpdateGridAndHutArea)
    void __thiscall ReserveToolsSlots(bool active);  // 0x00c998c0 (cTribe::ReserveToolsSlots)
    void __thiscall ChooseNewHutModel();  // 0x00c99c30 (cTribe::ChooseNewHutModel)
    void __thiscall NotifyToolSelection();  // 0x00c99840 (cTribe::NotifyToolSelection)
    TribeTool* __thiscall GetToolOfType(int type);      // 0xc8f6e0
    void __thiscall FinishTask(int task);               // 0xc987b0
    void __thiscall FUN_00c91700();                     // 0xc91700
    void __thiscall SetupChatAreas();                   // 0xc95af0
    void __thiscall PromoteChieftain(int level);        // 0xc8fd50
    void __thiscall InitDomesticatedAnimalsHerd();      // 0xc8fef0
};
extern "C" cGameNounManager_s00c9_9140* __cdecl NounManager_s00c9_9140();                                         // 0xb3d300
extern "C" cPropertyManager* __cdecl PropertyManager();                                     // 0x67de30
extern "C" cTerraformingManager* __cdecl TerraformingManager();                             // 0xb3d430
extern "C" cPlanetModel_s00c9_9140* __cdecl PlanetModel_s00c9_9140();                                             // 0xb3d350
struct cSPEditorSpeciesManager {
    cSpeciesProfile_s00c9_9140* __thiscall GetAvatarProfile();                                        // 0x4df420
};
extern "C" cSPEditorSpeciesManager* __cdecl GetSetting9_s00c9_9140();                                  // 0x401090
// ---- items of slice s00c99140 end

// ---- items of slice s013551e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0135_51e0; 
}
typedef eastl::string8_s0135_51e0 string8_s0135_51e0;
namespace Simulator {
class ISerializerReadStream;
}
namespace Simulator {
class ISerializerWriteStream;
}
namespace Simulator {
struct Attribute;
}
namespace Simulator {
typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
}
namespace Simulator {
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
}
namespace Simulator {
typedef void  (*ReadTextFunction_t)(const string8_s0135_51e0&, void*);
}
namespace Simulator {
typedef void  (*WriteTextFunction_t)(char*, void*);
}
namespace Simulator {
typedef bool  (*ValidateFunction_t)();
}
namespace Simulator {
typedef bool  (*ToXmlFunction_t)(void*, const char*, int);
}
namespace Simulator {
typedef void* (*OffsetFunction_t)(Attribute*);
}
namespace Simulator {
typedef void  (*SetDefaultFunction_t)(Attribute*);
}
namespace Simulator {
void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
void* StaticOffset(Attribute* pAttr);    // 0x011874d0: (void*)pAttr->offset
}
namespace Simulator {
struct Attribute
{
    /* 00h */ const char* name;
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized
    /* 10h */ int field_10;   // not initialized
    /* 14h */ int field_14;   // not initialized
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ SetDefaultFunction_t setDefaultFunction;
    /* 20h */ OffsetFunction_t offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};
}
namespace Simulator {
extern char cTribe_sFishHotSpots[];   // 0x0157abb0
}
namespace Simulator {
extern char cTribe_sFishTimer[];      // 0x016953f8
}
namespace Simulator {
extern char cTribe_sFishEndTime[];    // 0x01695368
}
namespace Simulator {
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00aff840(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b20540(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00bed160(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00bf50f0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c41210(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c92a00(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c92a30(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c92a60(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c95780(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c95850(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c9ab30(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ce26c0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00572840(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00aca730(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00aff870(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c40e80(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c43790(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c6adc0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c92a90(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00692fd0(const string8_s0135_51e0& text, void* pData);
}
namespace Simulator {
template<typename T> void ReadTextInt(const string8_s0135_51e0& text, void* pData);
}
namespace Simulator {
void ReadText_006930b0(const string8_s0135_51e0& text, void* pData);
}
namespace Simulator {
void ReadText_006930f0(const string8_s0135_51e0& text, void* pData);
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0135_51e0& text, void* pData);
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694bd0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694ec0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694f00(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694fa0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694fc0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00695010(char* pBuffer, void* pData);
}
namespace Simulator {
bool Validate_00ae3310();
}
namespace Simulator {
template<typename T> bool AlwaysValid();
}
namespace Simulator {
bool Validate_00b6f550();
}
namespace Simulator {
bool Validate_00b6f860();
}
namespace Simulator {
bool Validate_00c9ad90();
}
namespace Simulator {
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00acbb80(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00acbba0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00c41b00(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00c6c390(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00c6c4e0(void* pData, const char* pName, int depth);
}
namespace Simulator {
struct Vector3;
}
namespace Simulator {
struct ResourceKeyVector;
}
namespace Simulator {
struct ForestList;
}
namespace Simulator {
extern Attribute cTribe_sAttributes[36];   // 0x0157ba68
}
namespace Simulator {
#define ATTR(NAME, ID, OFFSET, OFS, RD, WR, RT, WT, VAL, XML, IDX) \
    a.name = NAME; a.id = ID; a.pCurrentObject = 0; a.setDefaultFunction = 0; \
    a.offsetFunction = OFS; a.readFunction = RD; a.writeFunction = WR; \
    a.readTextFunction = RT; a.writeTextFunction = WT; a.validateFunction = VAL; \
    a.toXmlFunction = XML; a.offset = (uint32_t)(OFFSET); \
    cTribe_sAttributes[IDX] = a;
}
// ---- items of slice s013551e0 end

// ---- items of slice s00c95980 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uint;
typedef unsigned char  uchar;
struct SVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* mAllocator;
    void* mpX;
};
namespace SP {
class cTribe_s00c9_5980;
}
namespace SP {
void* __cdecl FUN_00b3d350();                     // 0xb3d350  SP::PlanetModel()
}
namespace SP {
void* __cdecl FUN_00b3d300();                     // 0xb3d300  SP::NounManager()
}
namespace SP {
void* __cdecl FUN_00b3d260();                     // 0xb3d260  SP::BehaviorManager()
}
namespace SP {
void* __cdecl FUN_00b3d480(void* a);              // 0xb3d480
}
namespace SP {
void* __cdecl FUN_00b20c60(void* nounMgr, uint ci);// 0xb20c60  cGameNounManager::CreateNoun
}
namespace SP {
void* __cdecl FUN_00b815a0(void* out, void* in);  // 0xb815a0  DirectionToSurfacePosition
}
namespace SP {
void* __cdecl FUN_0059aed0(void* a, void* b, void* c); // 0x59aed0
}
namespace SP {
void* __cdecl FUN_00c8ec60(void* a, void* b, void* c); // 0xc8ec60
}
namespace SP {
void* __cdecl FUN_00c8f310();                     // 0xc8f310  cTribe::PickAPeon
}
namespace SP {
void* __cdecl FUN_00c0b760();                     // 0xc0b760
}
namespace SP {
void  __cdecl FUN_00e1c7f0(void* a);              // 0xe1c7f0
}
namespace SP {
void  __cdecl FUN_00afc470(void* a);              // 0xafc470
}
namespace SP {
void  __cdecl FUN_00bab900(void* a, void* b);     // 0xbab900
}
namespace SP {
void  __cdecl FUN_00c22ee0(void* a);              // 0xc22ee0
}
namespace SP {
void  __cdecl FUN_00c00660(void* a);              // 0xc00660
}
namespace SP {
void  __cdecl FUN_00c95150(void* a);              // 0xc95150
}
namespace SP {
void  __cdecl FUN_00c950f0(void* a);              // 0xc950f0
}
namespace SP {
void  __cdecl FUN_00c955e0(void* a, int n);       // 0xc955e0  vector<cTribeChatArea>::resize
}
namespace SP {
void  __cdecl FUN_00cc8350(void* a);              // 0xcc8350
}
namespace SP {
void* __cdecl FUN_00cc7070(uint a);               // 0xcc7070
}
namespace SP {
void  __cdecl FUN_006a0990(void* a, uint b, void* c, void* d); // 0x6a0990
}
namespace SP {
void  __cdecl FUN_0050d4e0(void* a, void* b);     // 0x50d4e0  vector<float>::operator=
}
namespace SP {
void  __cdecl FUN_00bdefa0(void* a, void* b, void* c, void* d); // 0xbdefa0
}
namespace SP {
void  __cdecl FUN_00cee440(void* a, void* b);     // 0xcee440
}
namespace SP {
void  __cdecl FUN_00c00530(void* a, void* b);     // 0xc00530
}
namespace SP {
void  __cdecl FUN_00c88b00(void* a, void* b);     // 0xc88b00
}
namespace SP {
int   __cdecl FUN_00c232d0();                     // 0xc232d0  IsLeader
}
namespace SP {
void  __cdecl FUN_00b225d0(void* a, void* b);     // 0xb225d0  RemoveNoun
}
namespace SP {
void  __cdecl FUN_00b7f250(void* a, void* b, void* c); // 0xb7f250  BuildSurfaceOrientation2
}
namespace SP {
int   __cdecl FUN_00acd410(void* a);              // 0xacd410
}
namespace SP {
void* __cdecl FUN_00aea5d0(void* a, void* b);     // 0xaea5d0  DoInsertPtr
}
namespace SP {
void  __cdecl FUN_004548d0(int n);                // 0x4548d0
}
namespace SP {
void  __cdecl FUN_00cc7830(void* a, float b, float c); // 0xcc7830 ComputeGridResolution
}
namespace SP {
void  __cdecl FUN_0067de30();                     // 0x67de30  PropertyManager
}
namespace SP {
class cTribe_s00c9_5980 {
 public:
    uchar pad_000[0x120];              // 0x000..0x120  (cCommunity base)
    uchar mSpatial_120[0x140];         // 0x120..0x260  (cSpatialObject sub-object)
    void* mpHandle_260;                // 0x260  creature-ish handle
    uchar pad_264[0x4];                // 0x264..0x268
    float mfScale_268;                 // 0x268  scale/proximity scalar
    uchar pad_26c[0x28];               // 0x26c..0x294
    void* mpChatAreas_294;             // 0x294  vector<cTribeChatArea>.mpBegin
    void* mpChatAreas_298;             // 0x298  vector<cTribeChatArea>.mpEnd
    uchar pad_29c[0x38];               // 0x29c..0x2d4
    void* mpTools_2d4;                 // 0x2d4  mTools.mpBegin (non-null guard)
    uchar pad_2d8[0x5c];               // 0x2d8..0x334
    uchar mbPacking_334;               // 0x334  enum (kHexPacking)
    uchar pad_335[0x3];                // 0x335..0x338
    int   mnCount_338;                 // 0x338  creature count
    uchar pad_33c[0x4];                // 0x33c..0x340
    SVec  mCreatures_340;              // 0x340  begin / end(0x344) / capacity(0x348)
    SVec  mChatAreaHandles_354;        // 0x354  begin / end(0x358) / capacity(0x35c)
    void* mpObject_368;                // 0x368  object whose +0x34 is a spatial sub-object
    uchar pad_36c[0x4];                // 0x36c..0x370
    void* mpStructVec_370;             // 0x370  arg to FUN_00bdefa0 in GetStructures
    uchar pad_374[0x19c];              // 0x374..0x510
    uchar mTimer_510[0x48];            // 0x510  cSPTimer
    uchar mReservationGrid_558[0x94];  // 0x558  cReservationGrid
    uchar pad_5ec[0x1904 - 0x5ec];     // 0x5ec..0x1904
    void* mpVec1904_begin;             // 0x1904 sp_vector<Vector3>.mpBegin
    void* mpVec1904_end;               // 0x1908 sp_vector<Vector3>.mpEnd

    void  SetupChatAreas();                                 // 0x00c95af0
    void  AddChatArea_5cc0(void* pObj);                     // 0x00c95cc0
    void  AddExistingCreatureInternal(void* pCreature);     // 0x00c95d70
    void  RemoveCreature(void* pCreature, uchar bRemove);   // 0x00c95ee0
    void* SpawnHut_5fe0(void* pArg);                        // 0x00c95fe0
    bool  AddTool_6150(void* pTool);                        // 0x00c96150
    bool  UpdateHut_62b0();                                 // 0x00c962b0
    bool  Read(void* pStream);                              // 0x00c96410
    void* GetStructures();                                  // 0x00c966d0
    void* GetInhabitants();                                 // 0x00c967a0
    void* CopyFrom_6840(void* pOther);                      // 0x00c96840
};
}
using SP::cTribe_s00c9_5980;
static void* vc(void* obj, int off) {
    return ((void**)*(void**)obj)[off / 4];
}
namespace eastl {
template <typename RandomAccessIterator, typename Compare>
void quick_sort_impl(RandomAccessIterator first, RandomAccessIterator last, int kRecursionCount, Compare compare);   // 0x00c94ec0
}
namespace eastl {
template <typename RandomAccessIterator, typename Compare>
void insertion_sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare);   // 0x00c90920
}
namespace eastl {
template <typename RandomAccessIterator, typename Compare>
void insertion_sort_simple(RandomAccessIterator first, RandomAccessIterator last, Compare compare);   // 0x00c90a40
}
namespace eastl {
template <typename Size>
inline Size Log2(Size n) {
    int i;
    for (i = 0; n; ++i)
        n >>= 1;
    return i - 1;
}
}
namespace eastl {
static const int kQuickSortLimit = 28;
}
// ---- items of slice s00c95980 end

// ---- items of slice s00c97220 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_011e0744(void* dst, const void* src, unsigned n);   // memcpy thunk
extern "C" void* __cdecl FUN_011e073e(void* dst, int c, unsigned n);              // memset thunk
extern bool gTribeArchetypesLoaded;                               // 0x01695371
extern float kRegionScale;   // 0x01470f1c
extern float kRegionBias;    // 0x01473c2c
struct Property {
    void*    mpData;      // +0x00 (array data, or the inline value itself)
    uint32_t pad04[3];
    uint16_t mnFlags;     // +0x10 (0x30 = array / external data)
    uint16_t mnType;      // +0x12

    void* GetValuePtr()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
};
class cPropertyList {
public:
    virtual int  AddRef();                                       // 0x00
    virtual int  Release();                                      // 0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& result);    // 0x24
};
struct Vec2_s00c9_7220 { float x, y; };
bool __cdecl GetPropertyAsUint32Array(cPropertyList* pl, uint32_t id, int* count, uint32_t** data);   // 0x006a0840
void __cdecl GetPropertyAsVector2(cPropertyList* pl, uint32_t id, Vec2_s00c9_7220* out);                        // 0x006a10c0
void operator delete[](void* p);                                                 // 0x00f47380
class cPropertyManager_s00c9_7220 {
public:
virtual int  v00();
virtual int v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList** result);   // 0x2c
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
    virtual void v44();
    virtual void GetPropertyListIDs(uint32_t groupID, struct SpVec* ids);                          // 0x48
};
cPropertyManager_s00c9_7220* __cdecl PropertyManager_s00c9_7220();                                                       // 0x0067de30
struct SpVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAllocator;

    void reserve(uint32_t n);                                    // 0x004e0880 (ret 4)
    void DoInsertValue(uint32_t* pos, const uint32_t& v);        // 0x004558a0 (ret 8)
    void clear()
    {
        uint32_t* first = mpBegin;
        uint32_t* last = mpEnd;
        FUN_011e0744(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd = mpEnd - (last - first);
    }
    void push_back(const uint32_t& v)
    {
        if (mpEnd < mpCapacity) {
            uint32_t* p = mpEnd;
            mpEnd = p + 1;
            if (p) *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
    void free()
    {
        if (mpBegin && ((int*)mpBegin)[-1])
            operator delete[](mpBegin);
    }
};
struct PLRef {
    cPropertyList* p;
    PLRef& operator=(cPropertyList* rhs)
    {
        if (p != rhs) {
            cPropertyList* old = p;
            if (rhs) rhs->AddRef();
            p = rhs;
            if (old) old->Release();
        }
        return *this;
    }
};
struct TribeArchetype {
    uint32_t f00, f04, f08;       // +0x00
    uint32_t list[16];            // +0x0c
    uint32_t listCount;           // +0x4c
    uint32_t f50;                 // +0x50
    uint32_t f54;
    float    f58, f5c, f60, f64, f68, f6c, f70, f74, f78;   // +0x58
    uint32_t pad7c[4];            // +0x7c
    uint32_t f8c;                 // +0x8c
    float    f90, f94;            // +0x90
    Vec2_s00c9_7220     v98;                 // +0x98
    SpVec    textures;            // +0xa0
    uint32_t padb0;
    cPropertyList* mpRef;         // +0xb4

    TribeArchetype()
    {
        f00 = 3;
        f04 = 10;
        f08 = 12;
        f50 = 0xb750af68;
        f8c = 0;
        f90 = 10.0f;
        f94 = 10.0f;
        textures.mpBegin = 0;
        textures.mpEnd = 0;
        textures.mpCapacity = 0;
        mpRef = 0;
        FUN_011e073e(list, 0, 0x40);
        listCount = 0;
        FUN_011e073e(&f54, 0, 0x38);
    }
    ~TribeArchetype()
    {
        if (mpRef) mpRef->Release();
        textures.free();
    }
    TribeArchetype& operator=(const TribeArchetype& o);           // 0x00c96840 (ret 4)
};
extern TribeArchetype gTribeArchetypes[96];                       // 0x01695458
struct cRefObj { virtual void AddRef(); virtual void Release(); virtual void Release2(); };
struct SlotPair { uint32_t a, b, c, d; };
struct RegionSlot {
    uint32_t  pad00[2];       // +0x00
    uint32_t* mpBegin;        // +0x08  first bucket entry
    uint32_t  m0c;            // +0x0c
    uint32_t* mpBucketEnd;    // +0x10  end of the current bucket
    uint32_t** mpBuckets;     // +0x14  per-bucket start pointers
    uint32_t* mpEnd;          // +0x18  overall end of the value array
    uint32_t* mpValueBase;    // +0x1c  value array base
    uint32_t* mpCapacity;     // +0x20  value array capacity
    uint32_t  m24;            // +0x24

    SlotPair& Lo() { return *(SlotPair*)&mpBegin; }     // +0x08 .. +0x14
    SlotPair& Hi() { return *(SlotPair*)&mpEnd; }       // +0x18 .. +0x24

    void Update(const SlotPair* out, SlotPair value);   // 0x00c95660
    void Insert(void** value);                          // 0x00c92bd0
};
struct TribeMap {             // cTribe+0x4e4
    uint32_t  m00;            // +0x00
    uint32_t  m04;            // +0x04
    uint32_t  m08;            // +0x08
    uint32_t  m0c;            // +0x0c

    RegionSlot* Find(const uint32_t* key);              // 0x00c96950
    void Destroy(uint32_t a, uint32_t b);               // 0x00c95930
};
struct TribeMapB {
    uint32_t  m00;
    uint32_t  m04;
    uint32_t  m08;
    uint32_t  m0c;

    void Destroy(uint32_t a, uint32_t b);               // 0x00c93700
};
void SlotRehash(SlotPair* out, SlotPair lo, SlotPair hi, uint32_t** extra);   // 0x00c8ecb0
void __fastcall SubDtor_cc7c50(void* p);                  // 0x00cc7c50
void __fastcall SubDtor_b638b0(void* p);                  // 0x00b638b0
void __fastcall SubDtor_afbad0(void* p);                  // 0x00afbad0
void __fastcall SubDtor_ae6970(void* p);                  // 0x00ae6970
void __fastcall SubDtor_ad92d0(void* p);                  // 0x00ad92d0
void __fastcall SubDtor_b6edf0(void* p);                  // 0x00b6edf0
void __fastcall SubDtor_cee7a0(void* p);                  // 0x00cee7a0
void __fastcall SubDtor_ac0520(void* p);                  // 0x00ac0520
void __fastcall SubDtor_c8a420(void* p);                  // 0x00c8a420
void __fastcall SubDtor_c2e4e0(void* p);                  // 0x00c2e4e0
void __fastcall BaseDtor(void* p);                        // 0x00bdd680
struct cTribeSub120 {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
    virtual bool Query();                                 // slot 0x2c
};
typedef SpVec* (__thiscall* cGetValueListFn)(void* self);
struct cTribeVtbl {
    void* mSlots[36];                 // +0x00 .. +0x8c
    cGetValueListFn GetValueList;     // +0x90
};
struct cTribeRandCtx { float Next(uint32_t salt); };      // 0x00ce6a40
extern cTribeRandCtx gTribeRandCtx;                       // 0x01581208
struct cPlanetModel_s00c9_7220 { Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* in); };   // 0x00b815a0
cPlanetModel_s00c9_7220* PlanetModel_s00c9_7220();                              // 0x00b3d350
struct cTribe_s00c9_7220 {
    cTribeVtbl* mpVtbl;           // +0x00
    void*       mpVtbl04;         // +0x04
    char        pad08[0x2c];      // +0x08 .. +0x34
    void*       mpVtbl34;         // +0x34
    char        pad38[0xe8];      // +0x38 .. +0x120
    void*       mpVtbl120;        // +0x120
    char        sub124[0xd0];     // +0x124 .. +0x1f4
    void*       mpVtbl1f4;        // +0x1f4
    char        sub1f8[0x14];     // +0x1f8 .. +0x20c
    void*       mpVtbl20c;        // +0x20c
    char        sub210[0x20];     // +0x210 .. +0x230
    void*       mpVtbl230;        // +0x230
    char        pad234[0x2c];     // +0x234 .. +0x260
    void*       mpRef260;         // +0x260
    char        pad264[0xc];      // +0x264 .. +0x270
    char        sub270[0x20];     // +0x270
    void*       mpRef290;         // +0x290
    void*       mpArray294;       // +0x294
    char        pad298[0x10];     // +0x298 .. +0x2a8
    void*       mpArray2a8;       // +0x2a8
    char        pad2ac[0x24];     // +0x2ac .. +0x2d0
    void*       mpRef2d0;         // +0x2d0
    void*       mpRef2d4;         // +0x2d4
    char        pad2d8[0x38];     // +0x2d8 .. +0x310
    void*       mp310;            // +0x310
    void*       mpArray314;       // +0x314
    char        pad318[0x10];     // +0x318 .. +0x328
    uint32_t    m328;             // +0x328
    uint32_t    m32c;             // +0x32c
    float       m330;             // +0x330
    uint8_t     m334;             // +0x334
    uint8_t     pad335[3];
    uint32_t    m338;             // +0x338
    uint8_t     m33c;             // +0x33c
    uint8_t     pad33d[3];        // +0x33d .. +0x340
    char        sub340[0x14];     // +0x340
    char        sub354[0x14];     // +0x354
    void*       mpRef368;         // +0x368
    char        sub36c[0x14];     // +0x36c
    char        sub380[0x14];     // +0x380
    TribeMapB   map394;           // +0x394
    char        pad3a4[0x10];     // +0x3a4 .. +0x3b4
    char        sub3b4[0x64];     // +0x3b4
    void*       mpArray418;       // +0x418
    char        pad41c[0xc8];     // +0x41c .. +0x4e4
    TribeMap    map4e4;           // +0x4e4
    float       m4f4;             // +0x4f4
    float       m4f8;             // +0x4f8
    uint32_t    m4fc;             // +0x4fc
    char        pad500[0x10];     // +0x500 .. +0x510
    char        sub510[0x20];     // +0x510
    char        sub530[0x28];     // +0x530
    char        sub558[0x18c8 - 0x558];   // +0x558 .. +0x18c8
    void*       mpOwned18c8;      // +0x18c8
    uint32_t    m18cc;            // +0x18cc
    char        pad18d0[0x34];    // +0x18d0 .. +0x1904
    void*       mpArray1904;      // +0x1904
    char        pad1908[0xbc];    // +0x1908 .. +0x19c4
    void*       mpRef19c4;        // +0x19c4
    void*       mpRef19c8;        // +0x19c8
    void*       mpRef19cc;        // +0x19cc
    void*       mpRef19d0;        // +0x19d0

    // Frame query for a region: returns the region origin in a and its extent in b.
    void Frame(uint32_t key, Vec3* a, Vec3* b);           // 0x00c905c0

    Vec3*    RandomRegionPoint(Vec3* out, uint32_t key, int);     // 0x00c979e0
    Vec3*    RandomRegionPointAt(int unused, Vec3* out, uint32_t key);   // 0x00c97b10
    int      FindRegionIndex(uint32_t key, int unused);           // 0x00c97c40
    int      InsertRegionValue(uint32_t key, void* obj);          // 0x00c97ca0
    void     UpdateRegionSlot(uint32_t key, uint32_t* extra);     // 0x00c97d40
    void     Destroy();                                           // 0x00c97de0
    bool     Sub120Query();                                       // 0x00c98080
    uint32_t AllocateRegion(uint32_t key);                        // 0x00c98230

    uint32_t Sub120Count();                                       // 0x00c8eae0
    uint32_t Sub120Index(uint32_t key);                           // 0x00c8e5a0
    void     Sub120Set(uint32_t value, int flag);                 // 0x00c95d70
};
static inline void LoadU32(cPropertyList* pl, uint32_t id, uint32_t* dst)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->mnType == 10)
        *dst = *(uint32_t*)p->GetValuePtr();
}
static inline float PropFloat(Property* p) { return *(float*)p->GetValuePtr(); }
static inline void LoadFloat(cPropertyList* pl, uint32_t id, float* dst)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->mnType == 13)
        *dst = PropFloat(p);
}
// ---- items of slice s00c97220 end

// ---- items of slice s00c9a080 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchange(volatile long* target, long value);
extern float kDefaultFloat;             // 0x015d9c6c
extern float g_ZoningRadius;            // 0x01581268
#pragma intrinsic(_InterlockedExchange)
#define VPAD(n) virtual void vpad##n()
struct Vector3_s00c9_a080 {
    float x, y, z;
    Vector3_s00c9_a080() {}
    Vector3_s00c9_a080(float a, float b, float c) : x(a), y(b), z(c) {}
};
inline Vector3_s00c9_a080 operator-(const Vector3_s00c9_a080& v) { return Vector3_s00c9_a080(-v.x, -v.y, -v.z); }
template <class T> struct AutoRef_s00c9_a080 {
    T* p;
    void Assign(T* n)
    {
        T* old = p;
        if (n != old) {
            if (n) n->AddRef();
            p = n;
            if (old) old->Release();
        }
    }
};
struct Property_s00c9_a080 {
    uint32_t pad0[4];
    uint16_t mFlags;                    // +0x10 (0x30 = data behind a pointer)
    uint16_t mType;                     // +0x12 (0xd float, 0x10 void)
    float* GetValueFloat();
};
inline float* Property_s00c9_a080::GetValueFloat()
{
    if (mType == 0xd || mType == 0x10) {
        if (mFlags & 0x30)
            return *(float**)this;
        return mType ? (float*)this : 0;
    }
    return &kDefaultFloat;
}
struct PropertyList : IRefCounted {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
    virtual bool GetProperty(uint32_t id, Property_s00c9_a080*& out);                     // +0x24
};
struct PropManager {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
    virtual bool GetPropertyList(uint32_t inst, uint32_t group, AutoRef_s00c9_a080<PropertyList>& dst);   // +0x2c
};
PropManager* PropertyManager_s00c9_a080();         // 0x0067de30
struct IMapSet { float GetHeightAt(const Vector3_s00c9_a080* pos); };                     // 0x00f927c0
struct IDistGrid {
VPAD(0);
VPAD(1);
VPAD(2);
    virtual IMapSet* GetMapSet();                                              // +0x0c
};
struct cPlanetModel_s00c9_a080 {
    uint32_t pad[0x24 / 4];
    IDistGrid* mpGrid;                                                         // +0x24
    void DirectionToSurfacePosition(Vector3_s00c9_a080* out, const Vector3_s00c9_a080* dir);         // 0x00b815a0
    Quaternion BuildSurfaceOrientation(const Vector3_s00c9_a080& pos);                    // 0x00b7f190
    Quaternion BuildSurfaceOrientation(const Vector3_s00c9_a080& pos, const Vector3_s00c9_a080& dir);// 0x00b7f250
};
cPlanetModel_s00c9_a080* PlanetModel_s00c9_a080();            // 0x00b3d350
struct cModelWorld;
cModelWorld* GonzagoModelWorld();       // 0x00b3d520
struct cSpatialPart_s00c9_a080 {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
    virtual const Vector3_s00c9_a080& GetPosition();                                      // +0x2c
    virtual const Quaternion& GetOrientation();                                // +0x30
    VPAD(13);
    virtual void SetPosition(const Vector3_s00c9_a080& p);                                // +0x38
    virtual void SetOrientation(const Quaternion& q);                          // +0x3c
VPAD(16);
VPAD(17);
VPAD(18);
VPAD(19);
VPAD(20);
VPAD(21);
    virtual bool IsEditor();                                                   // +0x58
};
struct cPlacedPart {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
    virtual void SetPosition(const Vector3_s00c9_a080* p);                                // +0x38
    virtual void SetOrientation(const Quaternion* q);                          // +0x3c
VPAD(16);
VPAD(17);
VPAD(18);
VPAD(19);
VPAD(20);
VPAD(21);
VPAD(22);
    virtual Vector3_s00c9_a080 GetDirection();                                            // +0x5c
VPAD(24);
VPAD(25);
VPAD(26);
VPAD(27);
VPAD(28);
VPAD(29);
VPAD(30);
VPAD(31);
VPAD(32);
VPAD(33);
VPAD(34);
VPAD(35);
VPAD(36);
VPAD(37);
VPAD(38);
VPAD(39);
    virtual void SetModelWorld(cModelWorld* w);                                // +0xa0
};
struct cTribe_s00c9_a080;
struct cTribeNoun : IRefCounted {                                              // hut or food mat
    VPAD(0);                                                                   // +0x08
    virtual void* Cast(uint32_t id);                                           // +0x0c
    uint32_t pad04[(0x34 - 0x4) / 4];
    cPlacedPart mPart;                                                         // +0x34
};
struct cTribeHut : cTribeNoun {
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
VPAD(18);
VPAD(19);
VPAD(20);
    virtual void SetTribe(cTribe_s00c9_a080* t);                                          // +0x54
};
struct cTribeFoodMat : cTribeNoun {
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
VPAD(18);
VPAD(19);
VPAD(20);
    virtual void SetTribe(cTribe_s00c9_a080* t);                                          // +0x54
};
struct cTimerLike {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
    virtual void SetEnabled(int on);                                           // +0x2c
};
struct BehaviorMgr {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
    virtual void Register(void* p);                                            // +0x38
};
BehaviorMgr* BehaviorManager();         // 0x00b3d260
extern const Vector3_s00c9_a080 kInvalidPos;       // 0x01695374
struct cCitizen_s00c9_a080 : IRefCounted {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
VPAD(18);
VPAD(19);
VPAD(20);
VPAD(21);
VPAD(22);
VPAD(23);
VPAD(24);
VPAD(25);
VPAD(26);
VPAD(27);
VPAD(28);
VPAD(29);
VPAD(30);
VPAD(31);
VPAD(32);
VPAD(33);
VPAD(34);
VPAD(35);
VPAD(36);
VPAD(37);
VPAD(38);
VPAD(39);
VPAD(40);
VPAD(41);
VPAD(42);
VPAD(43);
VPAD(44);
VPAD(45);
VPAD(46);
VPAD(47);
VPAD(48);
VPAD(49);
VPAD(50);
VPAD(51);
VPAD(52);
VPAD(53);
VPAD(54);
VPAD(55);
    virtual void Init(int a, cTribe_s00c9_a080* tribe, int b, const Vector3_s00c9_a080* where);      // +0xe8
};
struct cNounManager { IRefCounted* CreateNoun(uint32_t id); };                  // 0x00b20c60
cNounManager* NounManager_s00c9_a080();            // 0x00b3d300
struct cSpecies { uint32_t pad[0x608 / 4]; uint32_t mCount608; uint32_t mCount60c; };
inline bool HasA(const cSpecies* s) { return s && s->mCount60c > 0; }
inline bool HasB(const cSpecies* s) { return s && s->mCount608 > 0; }
struct cSpeciesGlobals {
    float GetRadius(cSpecies* s);       // 0x00ce6a40
    int GetPopulation();                // 0x0104bd80
    int GetFood();                      // 0x0104c100
};
extern cSpeciesGlobals g_Species;       // 0x01581208
struct cBundle {                        // cGameBundleContainer at +0x20c
    void Init(cTribe_s00c9_a080* owner, int type, float cap, float amount, int mode);     // 0x00cee2c0
};
struct cBundleMgr { void Add(float amount, cBundle* b, int type); };           // 0x00ac7ab0
cBundleMgr* BundleManager();            // 0x00b3d2b0
struct cReservationGrid {
    float ComputeGridResolution(float res, float zero);    // 0x00cc7830
};
struct cTimer {
    uint32_t mData;
    void Restart();                                        // 0x00bc3130
    bool IsRunning();                                      // 0x00feba90
    void Stop();                                           // 0x00bc3110
    void FUN_00bc3170();                                   // 0x00bc3170
    uint64_t GetElapsedTime();                             // 0x00bc3190
};
struct IMsgServer {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
    virtual void Post(uint32_t id, void* msg, int flags);                      // +0x14
};
IMsgServer* MessageServer();            // 0x0067dcc0
struct RefBaseA22 {
    virtual void v0();
    volatile long rc;
    RefBaseA22() { _InterlockedExchange(&rc, 0); }
};
struct MsgTribe : RefBaseA22 {
    cTribe_s00c9_a080* mTribe;                     // +8
    uint32_t pad[9];
    uint32_t mID;                       // +0x30
    uint32_t pad34;
    uint32_t mZero;                     // +0x38
    MsgTribe(cTribe_s00c9_a080* t) : mID(0x1e8c9e0), mZero(0), mTribe(t) {}
    ~MsgTribe();                        // 0x00421cf0 SlotMessage::Destruct
    virtual void v0();
};
struct cIdentity { uint32_t d[12]; void Init(); };                              // 0x00c2e4e0 (cIdentityColorable)
struct cTribe_s00c9_a080 {
    virtual void vp0();
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
VPAD(18);
    virtual int GetPoliticalID();                                              // +0x4c
VPAD(20);
VPAD(21);
VPAD(22);
VPAD(23);
VPAD(24);
VPAD(25);
VPAD(26);
VPAD(27);
VPAD(28);
VPAD(29);
VPAD(30);
VPAD(31);
VPAD(32);
VPAD(33);
VPAD(34);
VPAD(35);
VPAD(36);
VPAD(37);
VPAD(38);
VPAD(39);
VPAD(40);
VPAD(41);
    virtual void funcA8();                                                     // +0xa8

    uint32_t pad04[(0x38 - 0x4) / 4];
    uint32_t mField38;                                                         // +0x38 (FUN_00ff03b0)
    uint32_t pad3c[(0x6c - 0x3c) / 4];
    uint8_t mFlag6c;                                                           // +0x6c
    uint8_t pad6d[3];
    uint32_t pad70[(0x120 - 0x70) / 4];
    cSpatialPart_s00c9_a080 mSpatial;                                                     // +0x120
    uint32_t pad124[(0x20c - 0x124) / 4];
    cBundle mBundle;                                                           // +0x20c
    uint32_t pad20c[(0x230 - 0x20c - 4) / 4];
    // +0x230: identity sub-object (cIdentityColorable)
    cIdentity mIdentity;                                                       // +0x230
    AutoRef_s00c9_a080<cTribeFoodMat> mpFoodMat;                                          // +0x260
    uint32_t pad264;
    float mRSquareSize;                                                        // +0x268
    uint32_t pad26c[(0x2d4 - 0x26c) / 4];
    AutoRef_s00c9_a080<PropertyList> mpPropList;                                          // +0x2d4
    uint32_t pad2d8[(0x2e8 - 0x2d8) / 4];
    Vector3_s00c9_a080 mCenter;                                                           // +0x2e8
    uint32_t pad2f4[(0x300 - 0x2f4) / 4];
    uint8_t mbCheckedForWater;                                                 // +0x300
    uint8_t pad301[0x2f];
    float mZoningRadius;                                                       // +0x330
    uint8_t mbRoboTribe;                                                       // +0x334
    uint8_t pad335[3];
    uint32_t mRoboPopulationCount;                                             // +0x338
    uint8_t mbVisualized;                                                      // +0x33c
    uint8_t pad33d[3];
    uint32_t pad340[(0x354 - 0x340) / 4];
    int* mSelectableBegin;                                                     // +0x354
    int* mSelectableEnd;                                                       // +0x358
    uint32_t pad35c[(0x368 - 0x35c) / 4];
    AutoRef_s00c9_a080<cTribeHut> mpHut;                                                  // +0x368
    uint32_t pad36c[(0x510 - 0x36c) / 4];
    cTimer mPopulationTimer;                                                   // +0x510
    uint32_t pad514[(0x530 - 0x514) / 4];
    cTimer mToolsTimer;                                                        // +0x530
    uint32_t pad534[(0x550 - 0x534) / 4];
    uint32_t mTribeArchetype;                                                  // +0x550
    uint32_t pad554;
    cReservationGrid mRGrid;                                                   // +0x558
    uint32_t pad55c[(0x18cc - 0x55c) / 4];
    cSpecies* mpSpecies0;                                                      // +0x18cc

    // methods (all thiscall)
    void SetOwner(int a);                                                      // 0x00b18550
    Vector3_s00c9_a080* GetClosestWater();                                                // 0x00c8fe20
    void UpdateRoboTribeness();                                                // 0x00c8fbb0
    void SetupChatAreas();                                                     // 0x00c95af0
    void UpdateToolPositions();                                                // 0x00c91250
    void ResetToolLayout();                                                    // 0x00c951d0
    void ResetDefaultToolPlacement(int n);                                     // 0x00c8f770
    int GetMaxPopulation();                                                    // 0x00c8eae0
    void ChooseNewHutModel();                                                  // 0x00c99c30
    void ReserveToolsSlots(int n);                                             // 0x00c998c0
    void UpgradeHut();                                                         // 0x00c919e0
    void UpdateModel();                                                        // 0x00c91a40
    void FUN_00c91700();                                                       // 0x00c91700
    void AddExistingCreatureInternal(cCitizen_s00c9_a080* c, int flag);                   // 0x00c95d70
    void FUN_00ff03b0(int v);                                                  // 0x00ff03b0
    bool CheckToolsTimeout();                                                  // 0x00c9a960

    void Init(const Vector3_s00c9_a080* pos, int numMembers, int foodAmount, bool flag);
};
int FUN_00c00aa0(int n);                // 0x00c00aa0 (cdecl)
extern cTimer g_hotSpotTimer;               // 0x016953f8
struct cHotSpotNode {
    Vector3_s00c9_a080 mPosition;                                             // +0x00
    float   mField0c;                                              // +0x0c
    float   mField10;                                              // +0x10
    uint8_t pad14[0x39 - 0x14];
    uint8_t mField39;                                              // +0x39
    uint8_t pad3a[0x60 - 0x3a];
};
void __fastcall HotSpotGridRelease(void* slot);                    // 0x00c8efc0 (ecx = slot)
struct HotSpotMap {
    cHotSpotNode* mpBegin;                                         // +0x00
    union {
        cHotSpotNode* mpEnd;                                       // +0x04
        uint32_t      mpEndRaw;
    };
    uint8_t pad08[0xc18 - 0x08];
    uint8_t mField0c18;                                            // +0xc18
    void FreeRange(cHotSpotNode* begin, cHotSpotNode* end);        // 0x00c93690 (ret 8)
    cHotSpotNode* operator[](const Vector3_s00c9_a080** key);                 // 0x00c9aa10 (ret 4)
};
extern HotSpotMap g_hotSpots;               // 0x0157abb0
// ---- items of slice s00c9a080 end

// ---- items of slice s00c9afb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
extern const uint8_t kFaceAxes[3][4];                                            // 0x01473bc0
extern float g_DefaultFloat;                                                     // 0x015d9c6c
extern uint8_t g_HotSpotsFlag;                                               // 0x0157b7c8
extern uint64_t g_NextFishTime;                                              // 0x01695368
struct Vector3_s00c9_afb0 { float x, y, z; };
struct CubeIndex { int x, y, face; };
struct CubeCoord { float u, v; int face; };
CubeIndex* __cdecl CoordToIndex(CubeIndex* out, int res, const CubeCoord* in);   // 0x00684bf0
CubeCoord* __cdecl IndexToCoord(CubeCoord* out, int res, const CubeIndex* in);   // 0x00684c50
void __cdecl WrapCubeFace(int res, int* face, int* x, int* y, int a, int b);     // 0x00684ca0
struct Property_s00c9_afb0 {
    void*    mpData;       // +0x00
    uint32_t pad04[3];
    uint16_t mnFlags;      // +0x10
    uint16_t mnType;       // +0x12
};
struct PropertyList_s00c9_afb0 {
    virtual int  AddRef();  // 0x00432be0 (PropertyList::AddRef)
    virtual int  Release();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool GetProperty(uint32_t id, Property_s00c9_afb0*& prop);                      // +0x24
};
extern PropertyList_s00c9_afb0* g_pTribeTuning;                                             // 0x0158128c
struct IRef_s00c9_afb0 {
    virtual void v0();
    virtual void Release();
};
struct HotSpot {
    Vector3_s00c9_afb0   mPos;          // +0x00
    float     mFood;         // +0x0c
    float     mMaxFood;      // +0x10
    float     mResupply;     // +0x14
    CubeIndex mCube;         // +0x18
    IRef_s00c9_afb0*     mpEffect;      // +0x24
    IRef_s00c9_afb0*     mpHitSphere;   // +0x28
    uint32_t  pad2c;
    uint64_t  mStartTime;    // +0x30
    bool      mbActive;      // +0x38
    bool      mbRemove;      // +0x39
    IRef_s00c9_afb0*     mpOrnament;    // +0x3c
    void*     mpArray;       // +0x40
    uint32_t  pad44, pad48, pad4c;

    HotSpot()
        : mFood(30.0f), mMaxFood(30.0f), mResupply(0.0f), mpEffect(0), mpHitSphere(0),
          mStartTime(0), mbActive(false), mbRemove(false), mpOrnament(0), mpArray(0)
    {
        pad44 = 0; pad48 = 0; pad4c = 0;
        mPos.x = 0; mPos.y = 0; mPos.z = 0;
    }
    ~HotSpot()
    {
        if (mpArray && ((int*)mpArray)[-1] != 0)
            operator_delete__(mpArray);
        if (mpOrnament) mpOrnament->Release();
        if (mpHitSphere) mpHitSphere->Release();
        if (mpEffect) mpEffect->Release();
    }
    void Assign(const HotSpot& o);                       // 0x00c95010 (ret 4)
    void SetupArea(const Vector3_s00c9_afb0& pos, float radius);    // 0x00c91030 (ret 8)
};
struct HotSpotElem { uint32_t key; uint32_t pad; HotSpot value; };   // stride 0x60
struct HotSpotMap_s00c9_afb0 {
    HotSpotElem* mpBegin;      // +0
    HotSpotElem* mpEnd;        // +4
    uint32_t     pad[0x3040 / 4 - 2];   // up to the flag at +0xc18 (kept symbolic below)
};
extern HotSpotMap_s00c9_afb0 g_HotSpots;                                                // 0x0157abb0
HotSpotElem* __cdecl HotSpotLowerBound_s00c9_afb0(HotSpotElem* first, HotSpotElem* last, const uint32_t* key, uint8_t flag);   // 0x00c92d50
struct HotSpotMapRef {
    HotSpot* at(const uint32_t* key);                                        // 0x00c9aa10 (thiscall, ret 4)
};
struct PlanetModelT {
    int     ClassifyPoint(const Vector3_s00c9_afb0* dir);                               // 0x00b82fc0 (ret 4)
    Vector3_s00c9_afb0 SurfacePoint(const Vector3_s00c9_afb0& dir);                                // 0x00b81630 (ret 8, sret)
    bool    IsWaterPoint(const Vector3_s00c9_afb0* pos);                                // 0x00b7e3e0 (ret 4)
    Quaternion BuildSurfaceOrientation(const Vector3_s00c9_afb0& pos);                  // 0x00b7f190 (ret 4, sret)
};
PlanetModelT* __cdecl PlanetModel_s00c9_afb0();                                         // 0x00b3d350
struct GameTimeMgr { uint64_t GetTime(); };                                  // 0x00b316c0
GameTimeMgr* __cdecl GameTimeManager();                                      // 0x00b3d380
struct cSPTimer_s00c9_afb0 {
    bool     IsRunning();                                                    // 0x00feba90
    void     Start();                                                        // 0x00bc30f0
    void     Restart();                                                      // 0x00bc3130
    uint64_t GetElapsedTime();                                               // 0x00bc3190
};
extern cSPTimer_s00c9_afb0 g_FishTimer;                                                 // 0x016953f8
extern Vector3_s00c9_afb0  g_FishTarget;                                                // 0x01695374 (last water test point)
inline float ReadFloatProperty(uint32_t id, float def)
{
    Property_s00c9_afb0* p;
    if (g_pTribeTuning && g_pTribeTuning->GetProperty(id, p)) {
        uint16_t t = p->mnType;
        if (t == 0xd || t == 0x10) {
            if (p->mnFlags & 0x30)
                return **(float**)p;
            return *(float*)(t ? (void*)p : (void*)0);
        }
        return g_DefaultFloat;
    }
    return def;
}
struct RefCounted {
    virtual int   AddRef();                 // +0x00
    virtual void  Release();                // +0x04
    virtual void  r08();                    // +0x08
    virtual void  r0c();                    // +0x0c
    virtual void  r10();                    // +0x10
    virtual void  r14();                    // +0x14
    virtual void  r18();                    // +0x18
    virtual void  r1c();                    // +0x1c
    virtual void  r20();                    // +0x20
    virtual void  r24();                    // +0x24
    virtual void  r28();                    // +0x28
    virtual void* GetPosition();            // +0x2c
    virtual void  r30();                    // +0x30
    virtual void  r34();                    // +0x34
    virtual void  r38();                    // +0x38
    virtual void  r3c();                    // +0x3c
    virtual void  r40();                    // +0x40
    virtual void  r44();                    // +0x44
    virtual void  r48();                    // +0x48
    virtual void  r4c();                    // +0x4c
    virtual void  r50();                    // +0x50
    virtual void  r54();                    // +0x54
    virtual void* v58();                    // +0x58
    virtual void* v5c(void* out);           // +0x5c
    virtual void  v60();                    // +0x60
};
struct CompactObj {
    virtual void  k00();                    // +0x00
    virtual void  k04();                    // +0x04
    virtual void  k08();                    // +0x08
    virtual void  k0c();                    // +0x0c
    virtual void  k10();                    // +0x10
    virtual void  k14();                    // +0x14
    virtual void  k18(float value, int id); // +0x18
    virtual void  k1c();                    // +0x1c
    virtual void  k20();                    // +0x20
    virtual void  k24();                    // +0x24
    virtual void  k28();                    // +0x28
    virtual void* k2c();                    // +0x2c
    char mTail[0x18];                       // total 0x1c
};
struct cSpatialObject_s00c9_afb0 {
    virtual void s00();
    cSpatialObject_s00c9_afb0();                                   // 0x00c89630
    ~cSpatialObject_s00c9_afb0();                                  // 0x00c8a420
    void  SetLocalExtents(void* ext, float radius);     // 0x00c89160
    void* Cast(int type);                               // 0x00c884f0
    bool  Write(void* io);                              // 0x00c88a90
    void  func80h();                                    // 0x00c88510
    void  func54h(void* a);                             // 0x00c88670
    void  func58h(void* a);                             // 0x00c886d0
    void  OnExtentsChanged(void* a, float b);           // 0x00c9be50

    char      mPad004[0x50];                            // +0x004
    int       mMaterialType;                            // +0x054 (abs +0x088)
    char      mPad058[0x38];                            // +0x058
    uint32_t  mModelInstance;                           // +0x090 (abs +0x0c4)
    uint32_t  mPad094;                                  // +0x094
    uint32_t  mModelGroup;                              // +0x098 (abs +0x0cc)
    char      mPad09c[8];                               // +0x09c
    void*     mpTribe;                                  // +0x0a4 (abs +0x0d8)
    char      mPad0a8[0x10];                            // +0x0a8
    CompactObj mSub;                                    // +0x0b8 (abs +0x0ec)
};
namespace SP {
class cTribe_s00c9_afb0 { public:
    static uint32_t SetupHotSpot(const Vector3_s00c9_afb0& dir, int force = 0);  // 0x00c9afb0 (SP::cTribe::SetupHotSpot)
    const Vector3_s00c9_afb0* GetClosestWater();                            // 0x00c8fe20
    void func54h(void* a);                                       // 0x00c88670
    bool IsPlayerTribe();                                        // 0x00c9bd30
    void HandleEvent(void* a);                                   // 0x00c9bd50
    char mPad000[0xd8];
    void* mpTribeD8;                                             // +0x0d8
    char mPad0dc[0x120 - 0x0dc];
    CompactObj mSub120;                                          // +0x120
};  // namespace SP
}
struct TribeObj { void Notify(int id); };                                // 0x00c987b0
// ---- items of slice s00c9afb0 end

// @ 0x00c8e310
IOObject* __cdecl F8e310(IOObject* pStream, const uint32_t* pData)
{
    uint32_t v0 = pData[0];
    EA::IO::WriteUint32(pStream->v08()->v06(), &v0, 1, 0);
    uint32_t v1 = pData[1];
    EA::IO::WriteUint32(pStream->v08()->v06(), &v1, 1, 0);
    uint32_t v2 = pData[2];
    EA::IO::WriteUint32(pStream->v08()->v06(), &v2, 1, 0);
    return pStream;
}

// @ 0x00c8e3a0
IOObject* __cdecl F8e3a0(IOObject* pStream, uint32_t* pData)
{
    EA::IO::ReadInt32(pStream->v08()->v06(), &pData[0], 1, 0);
    EA::IO::ReadInt32(pStream->v08()->v06(), &pData[1], 1, 0);
    EA::IO::ReadInt32(pStream->v08()->v06(), &pData[2], 1, 0);
    return pStream;
}

// @ 0x00c8e420
void* __fastcall Tribe_AsInterface(Tribe* pSelf, int, unsigned int nID)
{
    if (nID == 0x4f396a66) {
        return pSelf;
    }
    if (nID == 0xee3f516e) {
        return pSelf;
    }
    {
        void* pRet = ((const IfaceA*)((char*)pSelf + 0x20c))->Query(nID);
        if (pRet != 0) return pRet;
        pRet = ((const IfaceB*)((char*)pSelf + 0x230))->Query(nID);
        if (pRet != 0) return pRet;
        pRet = ((const IfaceC*)((char*)pSelf + 0x1f4))->Query(nID);
        if (pRet != 0) return pRet;
        pRet = ((const IfaceD*)pSelf)->Query(nID);
        if (pRet != 0) return pRet;
        return ((const IfaceE*)((char*)pSelf + 0x120))->Query(nID);
    }
}

// @ 0x00c8e490
void __fastcall Tribe_ReleaseRel(Tribe* pSelf)
{
    int* pObj = 0;
    if (Sub_b3d350() != 0) {
        pObj = *(int**)((char*)Sub_b3d350() + 0x24);
    }
    if (pObj != 0) {
        typedef void (__thiscall *RelFn)(int*, void*, int);
        ((RelFn)(*(void***)pObj)[0x58 / 4])(pObj, pSelf->mpRel_19d4, 0);
        pSelf->mpRel_19d4 = 0;
    }
}

// @ 0x00c8e4d0
bool __fastcall Community_IsPlayer(Tribe* pSelf)
{
    NounMgr* pNM = (NounMgr*)Sub_b3d300();
    int* pTribe = pNM->GetPlayerTribe();
    return pTribe == (int*)((char*)pSelf - 0x120);
}

// @ 0x00c8e4f0
void __fastcall Tribe_InitRelationships(Tribe* pSelf)
{
    NounMgr* pNM = (NounMgr*)Sub_b3d300();
    unsigned int nID = ((unsigned int(__thiscall*)(void*))(*(void***)pSelf)[0x4c / 4])(pSelf);
    if (nID == (unsigned int)-1) {
        void** pVtbl = *(void***)pSelf;
        StarMgr* pSM = (StarMgr*)Sub_b3d2a0(0);
        void* pTerrain = pSM->GetTerrainSphere();
        ((void(__thiscall*)(void*, void*))pVtbl[0x48 / 4])(pSelf, pTerrain);
    }
    nID = ((unsigned int(__thiscall*)(void*))(*(void***)pSelf)[0x4c / 4])(pSelf);
    if (pNM->ClassifyById(nID) <= 2) {
        pNM->AddTribe((int*)pSelf);
    }
}

// @ 0x00c8e570
void __stdcall F8e570(void* p)
{
    *(uint8_t*)((char*)p + 0xa3) = 1;
}

// @ 0x00c8e5a0
int* __fastcall Tribe_CreateCreature(Tribe* pSelf, int, int nArg)
{
    if (pSelf->mb334 != 0 && pSelf->mb33c == 0) {
        return 0;
    }
    int* pCreature = Sub_b20c60(Sub_b3d300(), (void*)0x018eb4b7);
    ((void(__thiscall*)(int*, int, Tribe*, int, void*))(*(void***)pCreature)[0xe8 / 4])(pCreature, 0, pSelf, nArg, (void*)0x01695374);
    ((void(__thiscall*)(void*, int))(*(void***)((char*)pCreature + 0x5a8))[0x2c / 4])((char*)pCreature + 0x5a8, 1);
    {
        int* pBM = Sub_b3d260();
        ((void(__thiscall*)(int*, void*))(*(void***)pBM)[0x38 / 4])(pBM, (char*)pCreature + 0x58);
    }
    if (nArg == 0) {
        void* pOld = *(void**)((char*)pCreature + 0xc0);
        *(uint8_t*)((char*)pCreature + 0xbd) = 0;
        {
            void* pNew = ((void*(__thiscall*)(void*, void*))(*(void***)pSelf->mpModelFactory_120)[0x2c / 4])(pSelf->mpModelFactory_120, (void*)0x01695374);
            ((void(__thiscall*)(void*, void*))(*(void***)pOld)[0x38 / 4])(pOld, pNew);
        }
    }
    return pCreature;
}

// @ 0x00c8e650
int* __fastcall Tribe_GetPlayer(Tribe* pSelf)
{
    NounMgr* pNM = (NounMgr*)Sub_b3d300();
    if (pNM->GetPlayerTribe() == (int*)pSelf) {
        return ((NounMgr*)Sub_b3d300())->GetCurrentTerrainSphere();
    }
    return 0;
}

// @ 0x00c8e680
void __fastcall F8e680(void* pSelf, int, int nArg)
{
    void** pVt = *(void***)pSelf;
    ((SlotVoid2)pVt[0x9c / 4])(pSelf, nArg, 1);
}

// retail inlined the CRT __ftol2_sse helper (`fstp dword; cvttss2si`), which truncates the
// same way a plain (int) cast does; spell the conversion with the asm helper so it stays inline.
inline int TruncToInt_c8e6d0(float f) { __asm cvttss2si eax, f }

// @ 0x00c8e6d0
int __fastcall F8e6d0(void* pSelf)
{
    float f = ((const Cee380*)((char*)pSelf + 0x20c))->Get();
    return TruncToInt_c8e6d0(f);
}

// @ 0x00c8e720
void __stdcall F8e720(int nArg)
{
    Sub_c00b00(0, nArg);
}

// @ 0x00c8e730
void __fastcall Tribe_SetEditorMode(Tribe* pSelf, int, uint8_t bMode)
{
    if (bMode != pSelf->mbEditorMode_556) {
        if (bMode == 1) {
            int* pObj = Sub_b3d240();
            void* pName = ((void*(__thiscall*)(void*, void*))(*(void***)pSelf->mpModelFactory_120)[0x2c / 4])(pSelf->mpModelFactory_120, (void*)0x0169543c);
            ((void(__thiscall*)(int*, int, void*))(*(void***)pObj)[0x60 / 4])(pObj, 0x1046f5ef, pName);
            int* pIter = Sub_cee330((char*)pSelf + 0x20c);
            while (pIter != 0) {
                void* pA = Sub_ac79d0(Sub_b3d2b0());
                Sub_ac7de0((void*)pIter, pA);
                pIter = Sub_cee330((char*)pSelf + 0x20c);
            }
        }
        pSelf->mbEditorMode_556 = bMode;
    }
}

// @ 0x00c8e830
void __fastcall F8e830(Tribe* pSelf, int, void* pValue, int nIndex)
{
    *(void**)((char*)pSelf + 0x18cc + nIndex * 4) = pValue;
}

// @ 0x00c8e850
bool __fastcall F8e850(Tribe* pSelf)
{
    void* pGrid = pSelf->mpGrid_18cc;
    if (pGrid != 0) {
        return *(unsigned int*)((char*)pGrid + 0x60c) > 0u;
    }
    return false;
}

// @ 0x00c8e870
bool __fastcall F8e870(Tribe* pSelf)
{
    void* pGrid = pSelf->mpGrid_18cc;
    if (pGrid != 0) {
        return *(unsigned int*)((char*)pGrid + 0x608) > 0u;
    }
    return false;
}

// @ 0x00c8e890
void __fastcall F8e890(Tribe* pSelf, int, Vec6* pOut, unsigned int nKind, int)
{
    int nRow;
    if (nKind == 7) {
        nRow = 0;
    } else if (nKind == 8) {
        nRow = 1;
    } else if (nKind == 9) {
        nRow = 2;
    } else {
        pOut->w[0] = 0;
        pOut->w[1] = 0;
        pOut->w[2] = 0;
        pOut->w[3] = 0xffffffff;
        pOut->w[4] = 0;
        pOut->w[5] = 0;
        return;
    }
    Vec6* pRow = &pSelf->mSegmentTable_1868[nRow];
    pOut->w[0] = pRow->w[0];
    pOut->w[1] = pRow->w[1];
    pOut->w[2] = pRow->w[2];
    pOut->w[3] = pRow->w[3];
    pOut->w[4] = pRow->w[4];
    pOut->w[5] = pRow->w[5];
}

// @ 0x00c8e930
bool __fastcall F8e930(Tribe* pSelf, int, int* pArg)
{
    Grid* pGrid = (Grid*)pSelf->mpGrid_18cc;
    if (pGrid != 0 && pGrid->HasA()) {
        if (((const RelCheckA*)pArg)->Check()) {
            return true;
        }
    }
    if (pSelf->mpGrid_18cc != 0 && pGrid->HasB()) {
        if (((const RelCheckB*)pArg)->Check()) {
            return true;
        }
    }
    return false;
}

// @ 0x00c8e990
uint32_t __fastcall F8e990(Tribe* pSelf)
{
    Grid* pGrid = (Grid*)pSelf->mpGrid_18cc;
    if (pGrid != 0 && pGrid->HasA()) {
        if (!(pGrid != 0 && pGrid->HasB())) {
            return 1;
        }
    }
    if (!(pGrid != 0 && pGrid->HasB())) {
        return 3;
    }
    if (pGrid != 0 && pGrid->HasA()) {
        return 3;
    }
    return 2;
}

// @ 0x00c8e9f0
uint32_t __fastcall F8e9f0(Tribe* pSelf)
{
    Grid* pGrid = (Grid*)pSelf->mpGrid_18cc;
    if (pGrid != 0 && pGrid->HasB()) {
        if (pGrid != 0 && pGrid->HasA()) {
            return 0x268f;
        }
        return 0x268d;
    }
    return 0x268e;
}

// @ 0x00c8ea70
void* __cdecl F8ea70(unsigned int nSlot)
{
    if (nSlot - 1 <= 0x1e) {
        int nTerrain = ((TerrainSphere*)((NounMgr*)Sub_b3d300())->GetCurrentTerrainSphere())->GetSubIndex();
        return (char*)0x01695458 + (nTerrain * 0x20 + (int)nSlot) * 0xb8;
    }
    int nTerrain = ((TerrainSphere*)((NounMgr*)Sub_b3d300())->GetCurrentTerrainSphere())->GetSubIndex();
    return (char*)0x01695458 + nTerrain * 0x1700;
}

// @ 0x00c8eae0
int __fastcall Tribe_GetMaxPopulation(Tribe* pSelf)
{
    if (pSelf->mPopSlot_550 > 0u && pSelf->mPopSlot_550 < 0x20) {
        int nTerrain = ((TerrainSphere*)((NounMgr*)Sub_b3d300())->GetCurrentTerrainSphere())->GetSubIndex();
        return *(int*)((char*)0x01695460
                       + (nTerrain * 0x20 + (int)pSelf->mPopSlot_550) * 0xb8);
    }
    {
        void* pIface = (char*)pSelf + 0x120;
        if (((char(__thiscall*)(void*))(*(void***)pIface)[0x58 / 4])(pIface) != 0) {
            return Sub_c00ad0(pSelf->GetPopulationId());
        }
    }
    return Sub_c00ad0(2);
}

// @ 0x00c8eb50
bool __fastcall F8eb50(Tribe* pSelf, int, Vec3* pOut)
{
    Grid* pGrid = (Grid*)pSelf->mpGrid_18cc;
    if (pGrid != 0) {
        *pOut = pGrid->mPos;
        return true;
    }
    return false;
}

// @ 0x00c8eb90
bool __fastcall F8eb90(Tribe* pSelf)
{
    int* pPlayer = ((NounMgr*)Sub_b3d300())->GetPlayerTribe();
    if ((int*)pSelf == pPlayer) {
        return false;
    }
    {
        unsigned int a = ((unsigned int(__thiscall*)(int*, int))(*(void***)pPlayer)[0x4c / 4])(pPlayer, 1);
        unsigned int b = ((unsigned int(__thiscall*)(void*, unsigned int))(*(void***)pSelf)[0x4c / 4])(pSelf, a);
        int nRes = Sub_b3d2c0()->GetRelation((int)b);
        return nRes != 4;
    }
}

// @ 0x00c8ebe0
void __fastcall F8ebe0(Tribe* pSelf, int, unsigned int nBit)
{
    pSelf->mpRel_19d8 |= 1u << nBit;
}

// @ 0x00c8ec00
bool __fastcall F8ec00(Tribe* pSelf, int, unsigned int nBit)
{
    uint32_t nFlags = pSelf->mpRel_19d8;
    uint32_t nMask = 1u << nBit;
    return (nFlags & nMask) != 0;
}

// @ 0x00c8ec60
void FUN_00c8ec60(void** pBegin, void** pEnd, void** ppObject)
{
    if (pBegin != pEnd) {
        void* pObject = *ppObject;
        do {
            void* pTarget = (pObject != nullptr) ? (void*)((uint8_t*)pObject + 0xc0) : nullptr;
            if (*pBegin == pTarget)
                break;
            ++pBegin;
        } while (pBegin != pEnd);
    }
}

// @ 0x00c8ecb0
void FUN_00c8ecb0(void** pOut, void** pCurrent, void** pBegin, void** pEnd, void** pBlockIt, void** pStop, void* pA7, void* pA8, void* pUnused9, void** ppValue)
{
    if (pCurrent != pStop) {
        for (;;) {
            if (*pCurrent == *ppValue)
                break;

            ++pCurrent;
            if (pCurrent == pEnd) {
                ++pBlockIt;
                pCurrent = (void**)*pBlockIt;
                pEnd = pCurrent + 0x40;
                pBegin = pCurrent;
            }

            if (pCurrent == pStop)
                break;
        }
    }

    pOut[2] = pEnd;
    pOut[3] = pBlockIt;
    pOut[0] = pCurrent;
    pOut[1] = pBegin;
}

// @ 0x00c8ed30
cPointerVector* cPointerVector::Init(int32_t nCount, int32_t nUnused)
{
    int32_t* pData;
    if (nCount != 0) {
        pData = (int32_t*)operator_new(nCount * 0x1c, g_szSimulator, 0, 0,
                                       g_szAllocatorFile, 0xd1);
    }
    else {
        pData = nullptr;
    }

    mpBegin = (void**)pData;
    mpEnd = (void**)pData;
    mpCapEnd = (void**)(pData + nCount * 7);
    return this;
}

// @ 0x00c8ed90
cPointerBlockIter* FUN_00c8ed90(cPointerBlockIter* pOut, V4 a, V4 b, V4 c, void* pExtra)
{
    (void)pExtra;
    void** pCurrent = (void**)a.v0;
    void*  pA3 = (void*)a.v1;
    void** pEnd = (void**)a.v2;
    void** ppBlock = (void**)a.v3;
    void** pStop = (void**)b.v0;
    void*  pA7 = (void*)b.v1;
    void*  pA8 = (void*)b.v2;
    void*  pA9 = (void*)b.v3;
    void** pBlockCur = (void**)c.v0;
    void** pBlockBegin = (void**)c.v1;
    void** pBlockEnd = (void**)c.v2;
    void** pBlockIt = (void**)c.v3;
    pOut->mpBegin = pBlockBegin;
    pOut->mpCur = pBlockCur;
    pOut->mpEnd = pBlockEnd;
    pOut->mpBlockIt = pBlockIt;

    while (pCurrent != pStop) {
        if (pOut->mpCur != nullptr) {
            void* pValue = *pCurrent;
            *pOut->mpCur = pValue;
            if (pValue != nullptr)
                ((cRefCountedNode*)pValue)->v00();
        }

        ++pCurrent;
        if (pCurrent == pEnd) {
            ++ppBlock;
            pCurrent = (void**)*ppBlock;
            pEnd = pCurrent + 0x40;
        }

        pOut->mpCur = pOut->mpCur + 1;
        if (pOut->mpCur == pOut->mpEnd) {
            pOut->mpBlockIt = pOut->mpBlockIt + 1;
            void** pNext = (void**)*pOut->mpBlockIt;
            pOut->mpBegin = pNext;
            pOut->mpEnd = pNext + 0x40;
            pOut->mpCur = pNext;
        }
    }

    return pOut;
}

// @ 0x00c8ee40
void** FUN_00c8ee40(void** pBegin, void** pEnd, void** pOut)
{
    if (pBegin == pEnd)
        return pOut;

    do {
        cRefCountedNode* pSource = (*pBegin != nullptr)
                                       ? (cRefCountedNode*)((uint8_t*)*pBegin + 0x34)
                                       : nullptr;
        cRefCountedNode* pOld = (cRefCountedNode*)*pOut;
        if (pSource != pOld) {
            if (pSource != nullptr)
                pSource->AddRef();
            *pOut = pSource;
            if (pOld != nullptr)
                pOld->Release();
        }

        ++pBegin;
        ++pOut;
    } while (pBegin != pEnd);

    return pOut;
}

// @ 0x00c8eeb0
void** FUN_00c8eeb0(void** pBegin, void** pEnd, void** pOut)
{
    if (pEnd == pBegin)
        return pOut;

    do {
        --pEnd;
        --pOut;

        cRefCountedNode* pSource = (*pEnd != nullptr)
                                       ? (cRefCountedNode*)((uint8_t*)*pEnd + 0x34)
                                       : nullptr;
        cRefCountedNode* pOld = (cRefCountedNode*)*pOut;
        if (pSource != pOld) {
            if (pSource != nullptr)
                pSource->AddRef();
            *pOut = pSource;
            if (pOld != nullptr)
                pOld->Release();
        }
    } while (pEnd != pBegin);

    return pOut;
}

// @ 0x00c8ef20
void cSpatialThing_FUN_00c8ef20(cSpatialThing* pThis, cSPVector3_s00c8_ec60* pOut)
{
    cTransformNode* pNode = &pThis->mNode;
    float fRadius = pNode->GetRadius();

    cSPVector3_s00c8_ec60 aOrientation;
    cSPVector3_s00c8_ec60* pOrientation = pNode->GetScale(&aOrientation);

    cSPVector3_s00c8_ec60* pPosition = pThis->mNode.GetPosition();

    pOut->mx = pPosition->mx + fRadius * pOrientation->mx;
    pOut->my = pPosition->my + fRadius * pOrientation->my;
    pOut->mz = pPosition->mz + fRadius * pOrientation->mz;
}

// @ 0x00c8efc0
void cTribe_FUN_00c8efc0(cTribe* pThis)
{
    if (pThis->mppToolBegin != nullptr) {
        NounManagerOf(pThis->mppToolBegin)->RemoveNoun(pThis->mppToolBegin);
        if (pThis->mppToolBegin != nullptr) {
            cRefCounted_s00c8_ec60* pNoun = (cRefCounted_s00c8_ec60*)pThis->mppToolBegin;
            pThis->mppToolBegin = nullptr;
            pNoun->Release();
        }
    }

    if (pThis->mppToolEnd != nullptr) {
        NounManagerOf(pThis->mppToolEnd)->RemoveNoun(pThis->mppToolEnd);
        if (pThis->mppToolEnd != nullptr) {
            cRefCounted_s00c8_ec60* pNoun = (cRefCounted_s00c8_ec60*)pThis->mppToolEnd;
            pThis->mppToolEnd = nullptr;
            pNoun->Release();
        }
    }

    if (pThis->mpField19C4 != nullptr) {
        pThis->mpField19C4->v0c(1);
        if (pThis->mpField19C4 != nullptr) {
            cRefCountedNode* pNode = pThis->mpField19C4;
            pThis->mpField19C4 = nullptr;
            pNode->Release();
        }
    }
}

// @ 0x00c8f2b0
void cCommunity::func58h(int32_t nA)
{
    func58hBase(nA);

    cSpatialThing* pThing = mpField248;
    if (pThing != nullptr)
        pThing->mNode.FUN_00c8f03c((void*)nA);
}

// @ 0x00c8f2e0
cSPVector3_s00c8_ec60* __stdcall FUN_00c8f2e0(cSPVector3_s00c8_ec60* pOut, cSpatialThing* pThing)
{
    cSPVector3_s00c8_ec60* pPosition = pThing->mNode.GetPosition();

    pOut->mx = pPosition->mx;
    pOut->my = pPosition->my;
    pOut->mz = pPosition->mz;
    return pOut;
}

// @ 0x00c8f310
cCreature* cTribe::PickAPeon()
{
    for (cCreature** ppIt = mppPeonBegin; ppIt != mppPeonEnd; ++ppIt) {
        cCreature* pPeon = *ppIt;
        if (pPeon != nullptr) {
            if (!pPeon->IsLeader())
                return pPeon;
        }
    }

    cCreature** ppFirst = mppPeonBegin;
    if (ppFirst != mppPeonEnd)
        return *ppFirst;

    return nullptr;
}

// @ 0x00c8f370
int32_t cTribe::GetAdultPopulation()
{
    if (mbField334 != 0 && mbField33C == 0)
        return mnField338;

    return (int32_t)(mnField358 - mnField354) >> 2;
}

// @ 0x00c8f3a0
int32_t cTribe::FUN_00c8f3a0()
{
    if (mbField334 != 0 && mbField33C == 0)
        return mnField338;

    uint32_t* pList = (uint32_t*)GetAgents();
    return (int32_t)(pList[1] - pList[0]) >> 2;
}

// @ 0x00c8f3d0
void cTribe::FUN_00c8f3d0(int32_t nA1, void* pA2, float fA3, void* pA4, cSPVector3_s00c8_ec60* pA5, uint32_t nA6)
{
    uint32_t* pList = (uint32_t*)GetAgents();

    for (uint32_t* pIt = (uint32_t*)pList[0]; pIt != (uint32_t*)pList[1]; ++pIt) {
        cCreature* pCreature = (cCreature*)*pIt;
        if (!FUN_00c24560(pCreature))
            continue;
        if (pCreature->mpBehaviorTree == nullptr)
            continue;

        cStimulusEntry* pEntry =
            (cStimulusEntry*)pCreature->mpBehaviorTree->mStimuli.Play(nA1, pA4, fA3, nullptr);
        pEntry->mnField0C = (int32_t)pA4;
        pEntry->mnField10 = (int32_t)nA6;
        pEntry->mPosition = *pA5;
    }
}

// @ 0x00c8f470
void cTribe::SetStimuli(int32_t nA1, int32_t nA2, float fA3, void* pA4)
{
    uint32_t* pList = (uint32_t*)GetAgents();

    for (uint32_t* pIt = (uint32_t*)pList[0]; pIt != (uint32_t*)pList[1]; ++pIt) {
        cCreature* pCreature = (cCreature*)*pIt;
        pCreature->mpBehaviorTree->mStimuli.Play(nA1, (void*)nA2, fA3, pA4);
    }

    if (pA4 != nullptr && nA1 == 0 && nA2 == 0x4000) {
        cValueOwner* pOwner = (cValueOwner*)pA4;
        cValueOwner* pValue = (cValueOwner*)pOwner->GetValue(this);
        if (pValue != nullptr) {
            cValueNode* pFirst = (cValueNode*)pValue->GetChild();
            cValueNode* pSecond = (cValueNode*)pValue->GetChild();
            void* pAux = pValue->GetValue(this);

            float fScaled = pFirst->FUN_00c8f074(fA3, pAux);
            void* pResult = pSecond->SetValue(fScaled);
            cResultOwner* pOwner = (cResultOwner*)FUN_00bc8000(0xb9d14c31, pResult);
            pOwner->FUN_00bc8400();
        }
    }
}

// @ 0x00c8f540
void cTribe::FUN_00c8f540(cSPVector3_s00c8_ec60* pPosition, float fRadius, int32_t nA, void* pB, void* pC, void* pD)
{
    uint32_t* pList = (uint32_t*)GetAgents();

    for (uint32_t* pIt = (uint32_t*)pList[0]; pIt != (uint32_t*)pList[1]; ++pIt) {
        cCreature* pCreature = (cCreature*)*pIt;
        cTransformNode* pNode = &pCreature->mNode;

        cSPVector3_s00c8_ec60* pMemberPosition = pNode->GetPosition();
        float fDx = pMemberPosition->mx - pPosition->mx;
        float fDy = pMemberPosition->my - pPosition->my;
        float fDz = pMemberPosition->mz - pPosition->mz;

        float fMemberRadius = pNode->GetRadius();
        float fLimit = fMemberRadius + fRadius;

        float fDistSq = fDz * fDz + fDy * fDy + fDx * fDx;
        if (!(fLimit * fLimit > fDistSq))
            continue;

        cStimulusEntry* pEntry =
            (cStimulusEntry*)pCreature->mpBehaviorTree->mStimuli.Play(nA, pB, (float)(int32_t)pC, pD);
        pEntry->mPosition = *pPosition;
        pEntry->mnField0C = (int32_t)fRadius;
        (void)fMemberRadius;
    }
}

// @ 0x00c8f660
void cTribe::FUN_00c8f660(int32_t nValue)
{
    if (nValue > 0) {
        cTransformNode* pNode = (this != nullptr) ? &mNode2 : nullptr;
        uint32_t nId = FUN_00c8e990();
        cValueSink* pSink = (cValueSink*)FUN_00b3d2b0((float)nValue, pNode, nId);
        pSink->FUN_00ac7ab0();
        return;
    }

    if (nValue != 0) {
        cTransformNode* pNode = (this != nullptr) ? &mNode2 : nullptr;
        cValueSink* pSink = (cValueSink*)FUN_00b3d2b0((float)-nValue, pNode, 0);
        pSink->FUN_00ac7d10();
    }
}

// @ 0x00c8f6e0
cTool* cTribe::GetToolOfType(int32_t nType)
{
    for (void** ppIt = mppToolBegin; ppIt != mppToolEnd; ++ppIt) {
        cTool* pTool = (cTool*)*ppIt;
        if (pTool != nullptr) {
            if (nType == pTool->GetType())
                return pTool;
        }
    }

    return nullptr;
}

// @ 0x00c8f730
bool cTribe::FUN_00c8f730(int32_t nId)
{
    for (void** ppIt = mppToolBegin; ppIt != mppToolEnd; ++ppIt) {
        cTool* pTool = (cTool*)*ppIt;
        if (nId == pTool->GetId())
            return true;
    }

    return false;
}

// @ 0x00c8f770
void cTribe::ResetDefaultToolPlacement(int32_t nType)
{
    if (GetToolOfType(nType) != nullptr)
        return;

    cSPVector3_s00c8_ec60 aPosition = *mNode.GetPosition();

    cSpatialThing* pThing = GetThing(nType);
    pThing->mNode.FUN_00c8f03c(this);

    cSPVector3_s00c8_ec60 aScale;
    cSPVector3_s00c8_ec60* pScale = mNode.GetScale(&aScale);

    cSPVector3_s00c8_ec60 aOrientation;
    void* pSurface = PlanetModel(&aOrientation, &aPosition, pScale);
    ((cSpatialThing*)pSurface)->mNode.GetOrientation(&aOrientation);

    cTransformNode* pNode = &pThing->mNode;
    pNode->GetOrientation(&aPosition);
    pNode->FUN_00c8f03c(&aScale);
}

// @ 0x00c8f820
bool cTribe::Write(void* pStream)
{
    cOutStream* pOut = (cOutStream*)pStream;
    uint32_t nMagic = 0x4f396a66;
    EA_WriteUint32(pOut->GetHolder()->GetStream(), &nMagic, 1, 0);

    bool bOk = false;
    if (FUN_00c005b0(this, pStream)) {
        if (mNode.Write(pStream)) {
            if (FUN_00cee3d0(&mNode2, pStream)) {
                if (FUN_00c005b0(this, pStream)) {
                    if (FUN_00b6e2d0(&mNode3, pStream))
                        bOk = true;
                }
            }
        }
    }

    void** ppObjects = &mpField18CC;
    cSpeciesKey* pKeys = mpKeys;
    for (int32_t i = 0; i < 7; ++i) {
        void* pFirst = ppObjects[i * 2];
        void* pSecond = ppObjects[i * 2 + 1];

        if (pFirst != nullptr)
            pKeys[i].mnA = *(uint32_t*)((uint8_t*)pFirst + 0x504);
        else
            pKeys[i].mnA = 0;

        if (pSecond != nullptr) {
            pKeys[i].mnB = *(uint32_t*)((uint8_t*)pSecond + 0x504);
            pKeys[i].mnC = *(uint32_t*)((uint8_t*)pSecond + 0x508);
        }
        else {
            pKeys[i].mnB = 0;
            pKeys[i].mnC = 0;
        }
    }

    cRefCountedNode** apNodes[4];
    apNodes[0] = &mpField19C4;
    apNodes[1] = &mpField19C8;
    apNodes[2] = &mpField19CC;
    apNodes[3] = &mpField19D0;
    for (int32_t i = 0; i < 4; ++i) {
        cRefCountedNode* pNode = *apNodes[i];
        if (pNode == nullptr)
            continue;
        pNode->v2c();
        pNode = *apNodes[i];
        if (pNode == nullptr)
            continue;
        *apNodes[i] = nullptr;
        pNode->Release();
    }

    cVarListSerializer serializer(this, &g_szSimulator, 0x1a80d26);
    if (bOk) {
        if (serializer.Serialize(pStream))
            return true;
    }

    return false;
}

// @ 0x00c8fa60
bool cTribe::FUN_00c8fa60()
{
    cSpeciesManager* pManager = (cSpeciesManager*)GetSetting9();

    if (mpField18CC != nullptr)
        return true;

    cSpeciesKey aKey;
    if (!pManager->GetReplacementKey(*mpKeys, 0xbbaaecee, &aKey))
        return true;

    aKey.mnA = 0;
    aKey.mnB = 0;
    aKey.mnC = 0;
    pManager->GetReplacementKey(*mpKeys, 0xbbaaecee, &aKey);

    FUN_00ba5df0(mpKeys, &aKey);
    *mpKeys = aKey;

    mpField18CC = pManager->GetProfile(aKey);

    for (int32_t i = 1; i < 14; ++i) {
        if (*(uint32_t*)((uint8_t*)mpKeys + i * 0xc) != 0 && mpField18D0[i - 1] == nullptr) {
            *(cSpeciesKey*)((uint8_t*)mpKeys + i * 0xc) = *mpKeys;
            mpField18D0[i - 1] = mpField18CC;
        }
    }

    return true;
}

// @ 0x00c8fb50
void cTribe::FUN_00c8fb50()
{
    cCreature** pPeonEnd = mppPeonEnd;

    for (cCreature** ppIt = mppPeonBegin; ppIt != pPeonEnd; ++ppIt) {
        cCreature* pPeon = *ppIt;
        pPeon->FUN_00c0b9d0(g_fHotSpotValue);

        float fValue = pPeon->mCombatant.GetValue58();
        pPeon->mCombatant.SetValue(fValue);
    }

    mfField2C8 = 0.0f;
}

// @ 0x00c8fbb0
namespace SP {
void __thiscall cTribe_s00c8_fbb0::UpdateRoboTribeness()
{
    if (mb334)
        return;
    if ((uint32_t)FUN_00b5b800() + (-0x01654c01) <= 1)
        return;

    int32_t count;
    if (mb334 && !mPointersDirty) {
        count = mPointerCount;
    } else {
        cPointerVector_s00c8_fbb0* pList = GetPointerList();
        count = (int32_t)(pList->mpEnd - pList->mpBegin) >> 2;
    }
    while (mpPointerStackBegin != mpPointerStackEnd)
        ClearPointer(*(mpPointerStackEnd - 1));
    mPointerCount = count;
    mb334 = 1;
}
}  // namespace SP

// @ 0x00c8fc50
namespace SP {
void __thiscall cTribe_s00c8_fbb0::FUN_00c8fc50(bool flag)
{
    if (!flag && mPointersDirty) {
        cPointerVector_s00c8_fbb0* pList = GetPointerList();
        int32_t count = (int32_t)(pList->mpEnd - pList->mpBegin) >> 2;
        while (mpPointerStackBegin != mpPointerStackEnd) {
            ClearPointer(*(mpPointerStackEnd - 1));
        }
        mPointerCount = count;
    }
    mPointersDirty = flag;
}
}  // namespace SP

// @ 0x00c8fcc0
namespace SP {
tVec3* __thiscall cTribe_s00c8_fbb0::GetCenter(tVec3* pOut)
{
    tVec3* pPosition = mPosition.GetPosition();
    pOut->mX = pPosition->mX;
    pOut->mY = pPosition->mY;
    pOut->mZ = pPosition->mZ;
    return pOut;
}
}  // namespace SP

// @ 0x00c8fcf0
namespace SP {
tVec3* __thiscall cTribe_s00c8_fbb0::GetPoliticalCenter(tVec3* pOut)
{
    if (mpCommunity) {
        cPositionSource* pSource = &mpCommunity->mPosition;
        tVec3* pPosition = pSource->GetPosition();
        pOut->mX = pPosition->mX;
        pOut->mY = pPosition->mY;
        pOut->mZ = pPosition->mZ;
        return pOut;
    }
    GetPoliticalCenterOrCenter(pOut);
    return pOut;
}
}  // namespace SP

// @ 0x00c8fd30
namespace SP {
void* __thiscall cTribe_s00c8_fbb0::GetChieftain()
{
    cLeaderObject* pLeader = (cLeaderObject*)GetLeader();
    if (pLeader)
        return pLeader->QueryInterface(0x4f176642);
    return 0;
}
}  // namespace SP

#include <math.h>
struct WaterVec { float x, y, z; };
struct WaterSub {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual int Query(float a, WaterVec* out, float b, int c, int d); // slot +0x2c
};
struct WaterFace { bool Check(int x); }; // 0x00b88770, pops its one argument
WaterFace* WaterPlanet();                // 0x00b3d350
extern float gWaterScale;                // 0x0158125c
struct WaterView {
    char pad0[0x120];
    WaterSub mSub;
    char pad124[0x300 - 0x124];
    char mFlag;
    char pad301[3];
    WaterVec mPos;
    float mDist;
};
// @ 0x00c8fe20
namespace SP {
// Closest attempt, 162 bytes against 164 under /arch:SSE. SSE2 turns the length into sqrtss.
tVec3* __thiscall cTribe_s00c8_fbb0::GetClosestWater()
{
    WaterView* self = (WaterView*)this;
    if (!self->mFlag) {
        self->mFlag = 1;
        WaterVec* out = &self->mPos;
        WaterSub* s = &self->mSub;
        int r = s->Query(gWaterScale, out, 1.f, 1, 5);
        if (WaterPlanet()->Check(r)) {
            WaterVec* p = ((WaterVec*(__thiscall*)(WaterSub*))(*(void***)s)[11])(s);
            float dx = out->x - p->x;
            float dy = out->y - p->y;
            float dz = out->z - p->z;
            self->mDist = sqrtf(dx * dx + dy * dy + dz * dz);
            return (tVec3*)out;
        }
        self->mDist = 0.f;
    }
    return (tVec3*)&self->mPos;
}
}  // namespace SP

// @ 0x00c8fef0
namespace SP {
void __thiscall cTribe_s00c8_fbb0::InitDomesticatedAnimalsHerd(uint32_t speciesId)
{
    (void)speciesId;
}
}  // namespace SP

// @ 0x00c90470
namespace SP {
void __thiscall cTribe_s00c8_fbb0::FUN_00c90470()
{
    if (mpAttachedNoun) {
        NounManager()->RemoveNoun(mpAttachedNoun);
        cNounRef* pNoun = mpAttachedNoun;
        if (pNoun) {
            mpAttachedNoun = 0;
            pNoun->Release();
        }
    }
}
}  // namespace SP

// @ 0x00c904b0
namespace SP {
void __fastcall FUN_00c904b0(cTribe_s00c8_fbb0* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00c905a0
namespace SP {
bool __thiscall cTribe_s00c8_fbb0::FUN_00c905a0()
{
    return mpCommunity->mFileList.GetFileCount() == 2;
}
}  // namespace SP

// @ 0x00c905c0
namespace SP {
void __fastcall FUN_00c905c0(cTribe_s00c8_fbb0* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00c908a0
cPointerBlockIter* FUN_00c908a0(void* local, V4 a, V4 b, V4 c)
{
    void* extra = local;
    cPointerBlockIter* p = (cPointerBlockIter*)local;
    FUN_00c8ed90(p, a, b, c, extra);
    return p;
}

// @ 0x00c90920
namespace SP {
void __cdecl insertion_sort(tVec3** pFirst, tVec3** pLast, void* pCompare)
{
    (void)pFirst; (void)pLast; (void)pCompare;
}
}  // namespace SP

// @ 0x00c90a40
namespace SP {
void __cdecl insertion_sort(tVec3** pFirst, tVec3** pLast)
{
    (void)pFirst; (void)pLast;
}
}  // namespace SP

// @ 0x00c90b40
float* __cdecl NearestOfThree(float* a, float* b, float* c, float x, float y, float z)
{
  float daY = y - a[1];
  float dbY = y - b[1];
  float dcY = y - c[1];
  float dbX = x - b[0];
  float dbZ = z - b[2];
  float daX = x - a[0];
  float dcX = x - c[0];
  float daZ = z - a[2];
  float dcZ = z - c[2];

  if ((dbX * dbX + dbZ * dbZ) + dbY * dbY <=
      (daX * daX + daY * daY) + daZ * daZ) {
    if ((daX * daX + daZ * daZ) + daY * daY <
        (dcZ * dcZ + dcY * dcY) + dcX * dcX)
      return a;
    if ((dcZ * dcZ + dcY * dcY) + dcX * dcX <=
        (dbZ * dbZ + dbY * dbY) + dbX * dbX)
      return b;
  } else {
    if ((dbX * dbX + dbZ * dbZ) + dbY * dbY <
        (dcX * dcX + dcZ * dcZ) + dcY * dcY)
      return b;
    if ((dcX * dcX + dcZ * dcZ) + dcY * dcY <=
        (daX * daX + daZ * daZ) + daY * daY)
      return a;
  }
  return c;
}

// @ 0x00c90da0
void __cdecl CopyElems14(Elem14** out, const Elem14* first, const Elem14* last, Elem14* dst)
{
  *out = dst;
  if (first != last) {
    do {
      if (dst != 0) {
        dst->mX = first->mX;
        dst->mY = first->mY;
        dst->mZ = first->mZ;
        dst->mW = first->mW;
        dst->mB_10 = first->mB_10;
      }
      first++;
      dst++;
    } while (first != last);
    *out = dst;
  }
}

// @ 0x00c90df0
void __cdecl FillElems14(Elem14* dst, u32 count, const Elem14* value)
{
  if (count != 0) {
    do {
      if (dst != 0) {
        dst->mX = value->mX;
        dst->mY = value->mY;
        dst->mZ = value->mZ;
        dst->mW = value->mW;
        dst->mB_10 = value->mB_10;
      }
      count--;
      dst++;
    } while (count != 0);
  }
}

// @ 0x00c90e40
void __cdecl CopyElems14Range(Elem14* first, const Elem14* last, Elem14* dst)
{
  for (; first != last; first++) {
    if (dst != 0) {
      dst->mX = first->mX;
      dst->mY = first->mY;
      dst->mZ = first->mZ;
      dst->mW = first->mW;
      dst->mB_10 = first->mB_10;
    }
    dst++;
  }
}

// @ 0x00c90e80
void __cdecl AssignRefRange(SegIter* out, SegIter src, SegIter dst, RefCnt*** dstPageSlot)
{
  while (src.mpCur != dst.mpEnd) {
    RefCnt* value = *src.mpCur;
    RefCnt* old   = *dst.mpCur;
    if (value != old) {
      if (value != 0)
        value->AddRef();
      *dst.mpCur = value;
      if (old != 0)
        old->Release();
    }
    dst.mpCur++;
    if (dst.mpCur == dst.mpEnd) {
      dst.mpBegin = (RefCnt**)*dstPageSlot;
      dst.mpEnd   = dst.mpBegin + 0x40;
      dst.mpCur   = dst.mpBegin;
      dstPageSlot++;
    }
    src.mpCur++;
    if (src.mpCur == src.mpEnd) {
      src.mppPage++;
      src.mpBegin = (RefCnt**)*src.mppPage;
      src.mpEnd   = src.mpBegin + 0x40;
      src.mpCur   = src.mpBegin;
    }
  }
  out->mpCur   = dst.mpCur;
  out->mpBegin = dst.mpBegin;
  out->mpEnd   = dst.mpEnd;
  out->mppPage = dst.mppPage;
}

// @ 0x00c90f50
void __cdecl PromoteHeap(Vec3* heap, s32 size, s32 hole, float x, float y, float z, float px, float py, float pz)
{
  while (size < hole) {
    s32 parent = (hole - 1) >> 1;
    Vec3* p = &heap[parent];
    if (((pz - z) * (pz - z) + (py - y) * (py - y)) + (px - x) * (px - x) <=
        ((px - p->x) * (px - p->x) + (pz - p->z) * (pz - p->z)) +
            (py - p->y) * (py - p->y))
      break;
    Vec3* dst = &heap[hole];
    dst->x = p->x;
    dst->y = p->y;
    dst->z = p->z;
    hole = parent;
  }
  Vec3* out = &heap[hole];
  out->x = x;
  out->y = y;
  out->z = z;
}

// @ 0x00c91030
void cFishingHotSpot_s00c9_0b40::SetupArea(Vec3* pos, float radius)
{
  if (GetCurrentGameMode() != (void*)0x1654c02)
    return;

  if (mpSplashEffect_28 == 0) {
    cSplashEffect* noun = (cSplashEffect*)((cGameNounManager_s00c9_0b40*)NounManager_s00c9_0b40())
                              ->CreateNoun(0x18c88e4);
    cSplashEffect* old = mpSplashEffect_28;
    if (noun != old) {
      if (noun != 0)
        noun->AddRef();
      mpSplashEffect_28 = noun;
      if (old != 0)
        old->Release();
    }
  }

  FUN_00c6f770(mpSplashEffect_28, 0x356eb8a, -1, 0);
  mpSplashEffect_28->mPlacement_70.SetPosition(pos);
  mpSplashEffect_28->mVisible_e1 = 1;

  if (mpInteractable_24 == 0) {
    cInteractable* noun = (cInteractable*)((cGameNounManager_s00c9_0b40*)NounManager_s00c9_0b40())
                              ->CreateNoun(0x2e72cae);
    cInteractable* itr = 0;
    if (noun != 0)
      itr = (cInteractable*)noun->QueryInterface(0x2e71a5a);
    cInteractable* old = mpInteractable_24;
    if (itr != old) {
      if (itr != 0)
        itr->AddRef();
      mpInteractable_24 = itr;
      if (old != 0)
        old->Release();
    }
  }

  mpInteractable_24->SetAreaData(pos, radius);
  mpInteractable_24->SetParams(0.0f, *(float*)0x14763b8);
  mpInteractable_24->AttachEffect(mpSplashEffect_28);

  cTribeModeStrategy* strat = (cTribeModeStrategy*)ModeStrategyInstance();
  void* target = strat->v6c(0, Vec3(), 0, 0);
  if (target == 0)
    return;
  cTribeModeStrategy* strat2 = (cTribeModeStrategy*)ModeStrategyInstance();
  void* obj = strat2->v6c(mpSplashEffect_28, *pos, 0, 1);
  FUN_00cc9740(obj);
}

// @ 0x00c91190
float* cTribe_s00c9_0b40::GetToolPosition(float* out, s32 kind)
{
  switch (kind) {
  case 0:
    if (GetToolOfType(10) != 0) {
      out[0] = mToolAnchor_504.x;
      out[1] = mToolAnchor_504.y;
      out[2] = mToolAnchor_504.z;
      return out;
    }
    break;
  case 2:
    {
      cTool_s00c9_0b40* tool = GetToolOfType(9);
      if (tool != 0) {
        Vec3* p = tool->mAnchor_34.GetPosition();
        out[0] = p->x;
        out[1] = p->y;
        out[2] = p->z;
        return out;
      }
    }
    break;
  default:
    {
      Vec3* p = mSpatial_120.GetPosition();
      out[0] = p->x;
      out[1] = p->y;
      out[2] = p->z;
    }
    return out;
  }
  out[0] = mToolSlots_2dc[kind].x;
  out[1] = mToolSlots_2dc[kind].y;
  out[2] = mToolSlots_2dc[kind].z;
  return out;
}

// @ 0x00c91250
void cTribe_s00c9_0b40::UpdateToolPositions()
{
  cPlanetModel* planet = (cPlanetModel*)PlanetModel();

  Vec3 center = *GetPosition();
  Vec3 up;
  v5c(&up);

  float sum = (center.z * center.z + (center.x * center.x + center.y * center.y))
              + 1e-08f;
  float invLen = 1.0f / (float)sqrt((double)sum);
  Vec3 axis = { center.z * invLen, center.x * invLen, center.y * invLen };

  Vec3 ring[3];
  for (s32 i = 0; i < 3; i++) {
    float angle = (float)i * 90.0f;
    float s = (float)sin((double)angle);
    float c = (float)cos((double)angle);
    float ax = axis.x * s;
    float ay = axis.y * s;
    float az = axis.z * s;
    Vec3 dir;
    dir.x = (((c * ay + az * ax) * up.z + (ay * ax - c * az) * up.x) * 2.0f +
             (1.0f - (az * az + ay * ay) * 2.0f) * up.y) * 9.5f + center.x;
    dir.y = (((c * az + ay * ax) * up.y + (az * ay - c * ax) * up.z) * 2.0f +
             (1.0f - (az * az + ax * ax) * 2.0f) * up.x) * 9.5f + center.y;
    dir.z = (((az * ax - c * ay) * up.y + (c * ax + az * ay) * up.x) * 2.0f +
             (1.0f - (ax * ax + ay * ay) * 2.0f) * up.z) * 9.5f + center.z;
    Vec3 projected;
    DirectionToSurfacePosition(planet, &projected, &dir);
    ring[i] = projected;
  }

  Vec3 social;
  if (GetPropertyAsVector3(mToolSlots_2dc, 0x5777f17, &social) != 0) {
    Quat* q = GetRotation();
    float qx = q->x, qy = q->y, qz = q->z, qw = q->w;
    float sx = social.x, sy = social.y, sz = social.z;
    float tx = (qz * qx - qw * qy) * sx;
    float ty = (qw * qz + qy * qx) * sx;
    Vec3 r;
    r.x = ((qy * qx - qw * qz) * sy + (qw * qy + qz * qx) * sz) * 2.0f +
          (1.0f - (qz * qz + qy * qy) * 2.0f) * sx;
    float t2 = (qw * qx + qz * qy) * sy;
    r.y = ((qz * qy - qw * qx) * sz + ty) * 2.0f +
          (1.0f - (qz * qz + qx * qx) * 2.0f) * sy;
    r.z = (t2 + tx) * 2.0f +
          (1.0f - (qy * qy + qx * qx) * 2.0f) * sz;
    Vec3* pos = GetPosition();
    r.x += pos->x;
    r.y += pos->y;
    r.z += pos->z;
    Vec3 out;
    DirectionToSurfacePosition(planet, &out, &r);
    mToolSlots_2dc[1] = out;
  }
}

// @ 0x00c91700
void cTribe_s00c9_0b40::RefreshAreaEffect()
{
  cPlanetModel* planet = (cPlanetModel*)PlanetModel();
  cPlanetBody* body = planet->mpBody_24;
  if (body == 0 || mAreaEffect_19d4 != 0)
    return;

  cTransform t;
  t.mFlags_00 = 0;
  t.mStamp_02 = 0;
  t.mPos_04.x = *(float*)0x1695374;
  t.mPos_04.y = *(float*)0x1695378;
  t.mPos_04.z = *(float*)0x169537c;
  t.mScale_10 = 1.0f;
  ((Matrix33Obj*)&t.mRot_14)->ctor((const void*)0x1695418);

  Vec3* pos = mSpatial_120.GetPosition();
  t.mPos_04 = *pos;
  t.mFlags_00 |= 4;
  t.mStamp_02++;

  Quat* rot = mSpatial_120.GetRotation();
  float* src = (float*)Matrix3FromQuaternion(&t.mRot_14, rot);
  for (s32 i = 0; i < 9; i++)
    t.mRot_14.m[i] = src[i];
  t.mFlags_00 |= 2;
  t.mStamp_02++;

  mAreaEffect_19d4 = body->AddTransform(&t, mEffectId_2d4);
}

// @ 0x00c91800
void cToolPlacement::SetPlacementArea(cPlacementArea* area)
{
  cTribe_s00c9_0b40* tribe = Tribe();
  Vec3 right;
  FUN_0059aed0(&right, (const void*)0x169543c, tribe->GetRotation());

  Vec3 fwd;
  FUN_0059aed0(&fwd, (const void*)0x1695448, tribe->GetRotation());

  u32 flags = area->mFlags_12c;
  if (flags == 0)
    flags = 3;
  float c = *(float*)0x15812f0;
  float sx = (flags & 1) ? c : -c;
  float sz = (flags & 2) ? c : -c;

  Vec3 target;
  target.x = fwd.x * sz + (right.x * sx + mOffset_dc.x);
  target.y = fwd.y * sz + (right.y * sx + mOffset_dc.y);
  target.z = fwd.z * sz + (right.z * sx + mOffset_dc.z);

  area->mAnchor_34.SetPosition(&target);
  v30(area);
  area->mConnected_130 = 1;
  area->mB_a3 = 0;
}

// @ 0x00c91970
void cTribe_s00c9_0b40::CheckFoodTutorialComplete()
{
  cGameData* data = (cGameData*)NounManager_s00c9_0b40();
  if (this != (cTribe_s00c9_0b40*)data->GetPlayerTribe())
    return;

  s32 value = vA4();
  s32 price = GetTutorialToolPrice(*(u32*)0x1581288, 0xb79e0065, 0x28);
  if (value < price)
    return;

  if (((cTribeModeStrategy*)ModeStrategyInstance())->TerrainHasKey(0x14363974) == 0) {
    ((cTribeModeStrategy*)ModeStrategyInstance())->SignalTribeEvent(0x14363974);
  }
}

// @ 0x00c91b60
void *SP::cTribeToolView::ChooseNewHutModel(void)
{
    if (!mDef.IsActive())
        return 0;

    // pick the hut-model id: a fully-built model beats a partially-built one
    u32 id;
    cHutModelState *pState = m18cc;
    if (pState != 0 && pState->m608 > 0 && pState->m60c > 0)
        id = 0x654e036;
    else if (pState != 0 && pState->m60c > 0)
        id = 0x654e034;
    else
        id = 0x654e035;

    // ask the property manager for the model list, then take the variant that
    // matches the current game mode
    SP::AutoRefCount<cMWModel_s00c9_1a40> found;
    found.mPtr = 0;
    cPropertyManager_s00c9_1a40 *pm = (cPropertyManager_s00c9_1a40 *)PropertyManager_s00c9_1a40();
    found = 0;
    if (pm->Query(0xc42e83f6, 0x2be764e2, &found)) {
        eastl::vector_s00c9_1a40<SP::AutoRefCount<cMWModel_s00c9_1a40>, eastl::sp_vector_allocator_s00c9_1a40> list;
        u32 count = 0;
        if (eastl::reserve(&list, id, &count, &list.mBegin)) {
            i32 index = GetModeVariant() - 1;
            if (index < (i32)count) {
                SP::AutoRefCount<cMWModel_s00c9_1a40> chosen = list.mBegin[index];
                found = 0;
                return chosen.mPtr;
            }
        }
    }
    found = 0;
    return 0;
}

// @ 0x00c91c80
f32 SP::cTribeToolView::GetWaterOrHeight(void)
{
    if (m300 == 0)
        GetClosestWater();
    return m310;
}

// @ 0x00c91ca0
bool cSpear::Update()
{
    cLocomotivePart* loco = AsLocomotive();
    Vector3 delta = loco->GetPosition() - mLastPosition;
    float dist = delta.Length();
    Vector3 dir = delta;
    if (dist > 0.0f) {
        dir *= 1.0f / dist;
        Vector3 hitPos = kSpearHitDefault;
        SpatialRef hit;
        int result = CombatLineTest(mLastPosition, dir, dist + loco->GetFootprintRadius(), &hit.mpObject,
                                    &hitPos, GetOwner(), 4);
        if (result != 3) {
            cCombatant* victim = hit.mpObject ? (cCombatant*)hit.mpObject->AsInterface(kCombatantIID) : 0;
            if (!victim) {
                if (result == 1) {
                    cGameObject* owner = GetOwner();
                    cCreatureCitizen* thrower;
                    if (owner && (thrower = (cCreatureCitizen*)owner->Cast(0x4f176642)) != 0) {
                        cTribe_s00c9_1ca0* tribe = thrower->GetTribe();
                        cTribeDisplayStrategy* display = cTribeModeStrategy_s00c9_1ca0::Instance()->GetDisplayStrategy();
                        if (tribe && display) {
                            Vector3 n = normalized_safe(hitPos - loco->GetPosition());
                            Quaternion q = QuaternionFromDirections(kXAxis, -n);
                            int index = display->GetGroundSpearIndex(tribe->mPolitical.GetTribeIndex());
                            if (index >= 0) {
                                Transform t;
                                t.SetRotation(Matrix3FromQuaternion(loco->GetOrientation()));
                                t.RotateY(kHalfPi);
                                t.SetOffset(hitPos);
                                t.SetScale(loco->GetScale());
                                display->SetGroundSpearTransform(tribe->mPolitical.GetTribeIndex(), index, t, 15000);
                            }
                        }
                        Vector3 hitDir = normalized_safe(hitPos - loco->GetPosition());
                        if (mDamage > 0.0f && mpTarget && mpTarget->GetData()->mbCanBeDamaged) {
                            mpTarget->TakeDamage(mDamage, thrower->GetPoliticalID(), 2, &hitDir, &thrower->mCombatant);
                            cCreatureBase* creature = GetCreatureBase(mpTarget.mpObject);
                            if (creature && creature->mE8C == -1 && !creature->mbB5E && !creature->IsFlagSet())
                                creature->InterruptAnimation(0x2c39422, -1, 0);
                            mpTarget = 0;
                        }
                    }
                }
                IAudioSystem* audio = EA::Audio::GetSystemAT();
                Start3dSoundByName(0x3516e5d7, audio ? audio->GetHandle() : 0, hitPos);
                loco->SetPosition(hitPos);
                return false;
            }
            if (AsGameData()->GetPoliticalID() != victim->GetPoliticalID()) {
                int slotCount = 5;
                cGameObject* owner = GetOwner();
                cCreatureCitizen* attacker = owner ? (cCreatureCitizen*)owner->Cast(0x4f176642) : 0;
                cTribe_s00c9_1ca0* tribe = attacker->GetTribe();
                cCreatureBase* creature = (cCreatureBase*)victim->Cast(0xce9f6639);
                if (creature) {
                    if (creature->IsFlagSet())
                        slotCount = 20;
                    Vector3 hitDir = normalized_safe(hitPos - loco->GetPosition());
                    Vector3 start = mLastPosition;
                    Vector3 sweepDir = hitDir;
                    Vector3 bodyHit = hitPos;
                    int bone = 0;
                    bool bHitBody = false;
                    if (creature->mSubC0.IsVisible()) {
                        bHitBody = SweepTestModel(start, sweepDir, creature->mpAttachedModel->mpModel, &bone, 0,
                                                  &bodyHit, 0, 0);
                        if (!bHitBody) {
                            mLastPosition = loco->GetPosition();
                            return true;
                        }
                    }
                    if (cTribeModeStrategy_s00c9_1ca0::Instance()->GetDisplayStrategy()) {
                        cInteractiveOrnament* ornament =
                            cTribeModeStrategy_s00c9_1ca0::Instance()->GetDisplayStrategy()->GetSpearOrnament(tribe);
                        if (ornament) {
                            // detach the ornament from whoever carried it before
                            cAttachmentOwner* prev = FindAttachmentOwner(ornament->GetModelKey());
                            if (prev) {
                                for (uint32_t slot = kSpearSlotBase; slot < kSpearSlotBase + slotCount; slot++) {
                                    cAttachment* a = prev->GetAttachment(slot);
                                    if (a && a->mpObject && ornament == interface_cast_Ornament(a->mpObject)) {
                                        if (a->mpEffect)
                                            a->mpEffect->Stop();
                                        prev->RemoveAttachment(slot, 1);
                                        break;
                                    }
                                }
                            }
                            cSpatialPart* spatial = &ornament->mSpatial;
                            spatial->SetScale(loco->GetScale());

                            // pick a free slot on the victim, else recycle the lowest-priority one
                            uint32_t freeSlot = 0;
                            uint32_t bestSlot = kSpearSlotBase;
                            float bestPriority = FLT_MAX;
                            for (uint32_t slot = kSpearSlotBase; slot < kSpearSlotBase + slotCount; slot++) {
                                cAttachment* a = creature->GetAttachment(slot);
                                if (!a) {
                                    freeSlot = slot;
                                    break;
                                }
                                cInteractiveOrnament* o;
                                if (a->mpObject && (o = interface_cast_Ornament(a->mpObject)) != 0) {
                                    float priority = (float)o->mPriority;
                                    if (priority < bestPriority) {
                                        bestPriority = priority;
                                        bestSlot = slot;
                                    }
                                }
                            }
                            if (!freeSlot)
                                freeSlot = bestSlot;
                            cAttachment* old = creature->GetAttachment(freeSlot);
                            if (old) {
                                cEffect* effect = old->mpEffect;
                                if (effect)
                                    effect->mpOwner->StopEffect(effect, 0);
                                creature->RemoveAttachment(freeSlot, 1);
                            }

                            ornament->AttachTo(creature);
                            ornament->mbA9 = true;
                            ornament->mbA5 = true;
                            ornament->SetLifetime(10.0f, 0);
                            creature->CreateBodyEffect(bone, 0, spatial, freeSlot);

                            cAttachment* att = creature->GetAttachment(freeSlot);
                            if (att) {
                                cModel_s00c9_1ca0* model = creature->mpAttachedModel->mpModel;
                                cBone* b = (cBone*)(model->mpBones + bone * 0x2bc);
                                if (bHitBody) {
                                    Vector3 local = RotateByQuaternion(model->mOrientation, bodyHit - model->mPosition);
                                    Vector3 offset = (local - b->mOffset) * 0.5f;
                                    Vector3 r = RotateByQuaternion(b->mOrientation, offset);
                                    att->mOffset.x = r.x;
                                    att->mOffset.y = r.y;
                                    att->mOffset.z = r.z;
                                }
                                Quaternion q = MulConj(loco->GetOrientation(), model->mOrientation);
                                att->mOrientation = MulConj(q, b->mOrientation);
                            }

                            if (creature->mpTracker && creature->mpTracker->Find(2, 0, creature, 0) == -1) {
                                sSlotRange range;
                                range.mFirst = kSpearSlotBase;
                                range.mCount = slotCount;
                                creature->mpTracker->Add(2, 0, creature, FLT_MAX, &range, 0);
                            }
                        }
                    }
                    if (mDamage > 0.0f && mpTarget) {
                        mpTarget->TakeDamage(mDamage, attacker->GetPoliticalID(), 2, &hitDir,
                                             attacker ? &attacker->mCombatant : 0);
                        mpTarget = 0;
                    }
                    IAudioSystem* audio = EA::Audio::GetSystemAT();
                    Start3dSoundByName(0xaa6d7524, audio ? audio->GetHandle() : 0, hitPos);
                }
                loco->SetPosition(hitPos);
                mpTarget = 0;
                return false;
            }
        }
    }
    mLastPosition = loco->GetPosition();
    return true;
}

// @ 0x00c92a90
void __cdecl FUN_00c92a90(void* p1, int** p2)
{
    int count = (int)((char*)p2[1] - (char*)p2[0]) / 0x60;
    void* s = ((void*(__thiscall*)(void*))VF(p1, 0x20))(p1);
    void* w = ((void*(__thiscall*)(void*))VF(s, 0x18))(s);
    FUN_0093aa70(w, &count, 1, 0);
    int* cur = p2[0];
    for (; cur != p2[1]; cur += 0x18) {
        void* s2 = ((void*(__thiscall*)(void*))VF(p1, 0x20))(p1);
        count = *cur;
        void* w2 = ((void*(__thiscall*)(void*))VF(s2, 0x18))(s2);
        FUN_0093aa70(w2, &count, 1, 0);
        ((void(__thiscall*)(void*))VF(p1, 0x1c))(p1);
        cVarListSerializer_s00c9_2a90 ser;
        ser.Init(cur + 2, &DAT_0157b7d0, 0x1a80d26);
        ser.Serialize(p1);
        ((void(__thiscall*)(void*))VF(p1, 0x1c))(p1);
    }
    ((void(__thiscall*)(void*))VF(p1, 0x1c))(p1);
}

// @ 0x00c92b70
void __thiscall Deque::FUN_00c92b70(void)
{
    int** cur = mpp08;
    if (cur + 1 != (int**)mp10) {
        mpp08 = cur + 1;
        int* v = *cur;
        if (v)
            ((void(__thiscall*)(int*))VF(v, 4))(v);
    } else {
        int* v = *cur;
        if (v)
            ((void(__thiscall*)(int*))VF(v, 4))(v);
        if (mp0c)
            FUN_00f47380(mp0c);
        int** arr = (int**)((char*)mpp14 + 4);
        mpp14 = arr;
        mp0c = (int*)*arr;
        mp10 = (int*)((char*)mp0c + 0x100);
        mpp08 = (int**)mp0c;
    }
}

// @ 0x00c92bd0
void __thiscall Deque::FUN_00c92bd0(int** p)
{
    int* v = *p;
    if (v)
        ((void(__thiscall*)(int*))VF(v, 0))(v);
    if ((((int)((char*)mp24 - (char*)mp00) >> 2) + 1) >= mn04)
        FUN_01044f80(1, 1);
    void* blk = FUN_00f473a0(0x100, "Simulator", 0, 0, FUN_00_ALLOC_FILE, 0xd1);
    *(void**)((char*)mp24 + 4) = blk;
    if (mpp18 != 0) {
        *mpp18 = v;
        if (v)
            ((void(__thiscall*)(int*))VF(v, 0))(v);
    }
    mp24 = (int*)((char*)mp24 + 4);
    int* b = *(int**)mp24;
    mp1c = b;
    mp20 = (int*)((char*)b + 0x100);
    mpp18 = (int**)mp1c;
    if (v)
        ((void(__thiscall*)(int*))VF(v, 4))(v);
}

// @ 0x00c92c70
int** __cdecl FUN_00c92c70(int** first, int** last, int** out, int** blockptr)
{
    while (first != last) {
        char* b = (char*)*blockptr;
        int* end = b ? (int*)(b + 0xc0) : 0;
        int* cur = *first;
        if (cur != end) {
            int* old = *out;
            if (cur != old) {
                if (cur)
                    ((void(__thiscall*)(int*))VF(cur, 0xbc))(cur);
                *out = cur;
                if (old)
                    ((void(__thiscall*)(int*))VF(old, 0xc0))(old);
            }
            ++out;
        }
        ++first;
    }
    return out;
}

// @ 0x00c92ce0
void* __cdecl FUN_00c92ce0(void* out, void* first, void* last, void* dst, void* extra)
{
    Rec1c* d = (Rec1c*)dst;
    Rec1c* f = (Rec1c*)first;
    Rec1c* l = (Rec1c*)last;
    *(void**)out = dst;
    if (f != l) {
        do {
            if (d != 0) {
                d->b0  = f->b0;
                d->f4  = f->f4;
                d->f8  = f->f8;
                d->fc  = f->fc;
                d->f10 = f->f10;
                d->f14 = f->f14;
                d->f18 = f->f18;
            }
            f = (Rec1c*)((char*)f + 0x1c);
            d = (Rec1c*)((char*)d + 0x1c);
        } while (f != l);
        *(void**)out = d;
    }
    return out;
}

// @ 0x00c92d50
Rec60* __cdecl FUN_00c92d50(Rec60* first, Rec60* last, uint32_t* key)
{
    int n = (int)((char*)last - (char*)first) / 0x60;
    while (n > 0) {
        int half = n >> 1;
        Rec60* mid = (Rec60*)((char*)first + half * 0x60);
        if (mid->f00 < *key) {
            first = (Rec60*)((char*)mid + 0x60);
            half = n + (-1 - half);
        }
        n = half;
    }
    return first;
}

// @ 0x00c92e20
void __cdecl FUN_00c92e20(Vec3_s00c9_2a90* first, int top, int heapSize, int pos, Vec3_s00c9_2a90 value, CmpPos cmp)
{
    int child = 2 * pos + 2;
    for (; child < heapSize; child = 2 * child + 2) {
        float ax = cmp.x - first[child].x;
        float ay = cmp.y - first[child].y;
        float az = cmp.z - first[child].z;
        float da = ax * ax + ay * ay + az * az;
        float bx = cmp.x - first[child - 1].x;
        float by = cmp.y - first[child - 1].y;
        float bz = cmp.z - first[child - 1].z;
        float db = bx * bx + by * by + bz * bz;
        if (db > da)
            --child;
        first[pos] = first[child];
        pos = child;
    }
    if (child == heapSize) {
        first[pos] = first[child - 1];
        pos = child - 1;
    }
    FUN_00c90f50(first, top, pos, value, cmp);
}

// @ 0x00c92f80
char* __cdecl FUN_00c92f80(char* first, char* last, char* out)
{
    char* p = first + 0x44;
    while (first != last) {
        void* a = *(void**)(p + 4);
        if (a != 0 && *(int*)((char*)a - 4) != 0)
            FUN_00f47380(a);
        void* b = *(void**)p;
        if (b)
            ((void(__thiscall*)(void*))VF(b, 4))(b);
        void* c = *(void**)(p - 0x14);
        if (c)
            ((void(__thiscall*)(void*))VF(c, 4))(c);
        void* e = *(void**)(p - 0x18);
        if (e)
            ((void(__thiscall*)(void*))VF(e, 4))(e);
        first += 0x60;
        p += 0x60;
        out += 0x60;
    }
    return out;
}

// @ 0x00c93640
void __cdecl FUN_00c93640(int** first, int** last, int** blockptr)
{
    for (; first != last; ++first) {
        char* b = (char*)*blockptr;
        int* end = b ? (int*)(b + 0xc0) : 0;
        if (*first == end)
            break;
    }
    if (first != last)
        FUN_00c92c70(first + 1, last, first, blockptr);
}

// @ 0x00c93690
void __stdcall FUN_00c93690(uint32_t first, uint32_t last)
{
    if (first < last) {
        char* p = (char*)first + 0x44;
        uint32_t count = (last - first - 1) / 0x60 + 1;
        do {
            void* a = *(void**)(p + 4);
            if (a != 0 && *(int*)((char*)a - 4) != 0)
                FUN_00f47380(a);
            void* b = *(void**)p;
            if (b)
                ((void(__thiscall*)(void*))VF(b, 4))(b);
            void* c = *(void**)(p - 0x14);
            if (c)
                ((void(__thiscall*)(void*))VF(c, 4))(c);
            void* e = *(void**)(p - 0x18);
            if (e)
                ((void(__thiscall*)(void*))VF(e, 4))(e);
            p += 0x60;
            --count;
        } while (count != 0);
    }
}

// @ 0x00c93700
void __stdcall FUN_00c93700(uint32_t array, uint32_t count)
{
    for (uint32_t i = 0; i < count; ++i) {
        char* p = *(char**)(array + i * 4);
        while (p != 0) {
            char* next = *(char**)(p + 0x68);
            ((ActionCircle*)(p + 4))->dtor();
            FUN_00f47380(p);
            p = next;
        }
        *(uint32_t*)(array + i * 4) = 0;
    }
}

// @ 0x00c93750
Thing* __thiscall Thing::FUN_00c93750(int32_t* p2)
{
    uint32_t local[4];
    f00 = 0; f04 = 0; f08 = 0; f0c = 0; f10 = 0;
    f14 = 0; f18 = 0; f1c = 0; f20 = 0; f24 = 0;
    int size = ((((p2[9] - p2[5]) >> 2) - 1) * 0x40)
             + ((p2[6] - p2[7]) >> 2)
             + ((p2[4] - p2[2]) >> 2);
    ((Thing*)this)->FUN_00ca09f0((uint32_t)size);
    V4 s1 = { f08, f0c, f10, f14 };
    V4 s2 = { (uint32_t)p2[6], (uint32_t)p2[7], (uint32_t)p2[8], (uint32_t)p2[9] };
    V4 s3 = { (uint32_t)p2[2], (uint32_t)p2[3], (uint32_t)p2[4], (uint32_t)p2[5] };
    FUN_00c908a0(local, s3, s2, s1);
    return this;
}

// @ 0x00c93810
Thing* __thiscall Thing::FUN_00c93810(int32_t* p2)
{
    ((Thing*)this)->Init((int32_t)((p2[1] - p2[0]) / 0x1c), p2 + 3);
    FUN_00c92ce0(&p2, (void*)p2[0], (void*)p2[1], (void*)f00, p2);
    f04 = (uint32_t)p2;
    return this;
}

// @ 0x00c938f0
void __cdecl FUN_00c938f0(Vec3_s00c9_2a90* first, Vec3_s00c9_2a90* last, CmpPos cmp)
{
    int n = (int)((char*)last - (char*)first) / 0xc;
    for (int i = (n - 2) >> 1; i >= 0; --i)
        FUN_00c92e20(first, i, n, i, first[i], cmp);
}

// @ 0x00c93980
void __cdecl FUN_00c93980(Vec3_s00c9_2a90* first, Vec3_s00c9_2a90* last, CmpPos cmp)
{
    Vec3_s00c9_2a90* p = last;
    while ((p - first) > 1) {
        --p;
        Vec3_s00c9_2a90 t = *p;
        *p = *first;
        FUN_00c92e20(first, 0, (int)(p - first), 0, t, cmp);
    }
}

// @ 0x00c93a40
void __fastcall TribeUpdate(cTribe_s00c9_3a40* self)
{
  typedef bool (__thiscall* IsValidFn)(void*);
  IsValidFn isValid = (IsValidFn)VF(&self->mSpatial120, 0x58);
  bool valid = isValid(&self->mSpatial120);

  if (!valid) {
    CitizenVec* vec = (CitizenVec*)((void*(__thiscall*)(cTribe_s00c9_3a40*))VF(self, 0x90))(self);
    cCitizen** p = vec->mpBegin;
    while (p != vec->mpEnd) {
      cCitizen* c = *p;
      if (c != 0 && c->mpB20 != 0) {
        Vec3_s00c9_3a40* pos = FUN_00b6f0c0(self->nounManager());
        ((void(__thiscall*)(cCitizen*, Vec3_s00c9_3a40*))VF(c, 0xe4))(c, pos);

        if (c->mpB54 != 0 && c->mpB54->mpTarget != 0) {
          c->mpB54->mpTarget->mPos = c->mpB20->mPos;
        }

        u32 tool = c->ToolEffect();
        c->SetToolEffect(0, -1);
        c->SetToolEffect(tool, -1);

        void* strategy = FUN_00cd40b0();
        cStrategyResult* result = (cStrategyResult*)((void*(__thiscall*)(void*, cCitizen*))VF(strategy, 0x6c))(strategy, c);
        result->Finish();
      }
      ++p;
    }
  }

  if (self->mpPlanner != 0) {
    cSub34* sub = (cSub34*)((char*)self->mpPlanner + 0x34);
    cTarget4c* target = (cTarget4c*)((void*(__thiscall*)(void*))VF(sub, 0xac))(sub);
    if (target != 0) {
      Vec3_s00c9_3a40* pos = FUN_00b6f0c0(self->nounManager());
      cSub34* sub2 = (cSub34*)((char*)self->mpPlanner + 0x34);
      cTarget4c* target2 = (cTarget4c*)((void*(__thiscall*)(void*))VF(sub2, 0xac))(sub2);
      target2->mPos = *pos;
    }
  }

  CitizenVec* sel = (CitizenVec*)((void*(__thiscall*)(cTribe_s00c9_3a40*))VF(self, 0xbc))(self);
  u32 count = (u32)(sel->mpEnd - sel->mpBegin);
  cCitizen** arr = 0;
  if (count != 0) {
    arr = (cCitizen**)operator_new(count * 4, g_SimulatorName, 0, 0,
                                   g_EastlAllocator, 0xd1);
  }
  cCitizen** out = 0;
  FUN_00829110((void**)&out, sel->mpBegin, sel->mpEnd, arr, sel);

  for (cCitizen** q = arr; q != out; ++q) {
    cCitizen* c = *q;
    cSub34* sub = c->sub();
    cTarget4c* target = (cTarget4c*)((void*(__thiscall*)(void*))VF(sub, 0xac))(sub);
    if (target != 0) {
      Vec3_s00c9_3a40* pos = FUN_00b6f0c0(self->nounManager());
      cSub34* sub2 = c->sub();
      cTarget4c* target2 = (cTarget4c*)((void*(__thiscall*)(void*))VF(sub2, 0xac))(sub2);
      target2->mPos = *pos;
    }
  }

  wchar_t* empty = (wchar_t*)0x01667bac;
  WString name;
  name.mpBegin = empty;
  name.mpEnd = empty;
  name.mpCapacity = (wchar_t*)0x01667bae;
  self->mpSpeciesProfile->GetUiName(&name);
  self->mNameMap230.Setup(&name);

  IsValidFn isValid2 = (IsValidFn)VF(&self->mSpatial120, 0x58);
  u32 key = isValid2(&self->mSpatial120) ? 0 : 0xe;

  TreeNode* node = self->mTree.mpRoot;
  TreeNode* end = (TreeNode*)&self->mTree;
  TreeNode* candidate = end;
  while (node != 0) {
    if (node->mKey < key)
      node = node->mpLeft;
    else {
      node = node->mpRight;
      candidate = node;
    }
  }
  if (candidate == end || key < candidate->mKey)
    candidate = end;

  ((void(__thiscall*)(cSub34*, u32))VF(&self->mSub34, 0))(&self->mSub34, candidate->mValue);
  self->nounManager()->FinishUpdate();

  if ((char*)name.mpEnd - (char*)name.mpBegin > 2 && name.mpBegin != 0)
    operator_delete__(name.mpBegin);

  if (arr != 0) {
    for (cCitizen** q = arr; q != out; ++q) {
      cCitizen* c = *q;
      if (c != 0)
        ((void(__thiscall*)(cCitizen*))VF(c, 4))(c);
    }
    if (((s32*)arr)[-1] != 0)
      operator_delete__(arr);
  }
}

// @ 0x00c93dc0
cFishingHotSpot::cFishingHotSpot(const cFishingHotSpot& src)
{
  mPos.x = src.mPos.x;
  mPos.y = src.mPos.y;
  mPos.z = src.mPos.z;
  mFood = src.mFood;
  mMaxFood = src.mMaxFood;
  mResupply = src.mResupply;

  mCubeIndex[0] = src.mCubeIndex[0];
  mCubeIndex[1] = src.mCubeIndex[1];
  mCubeIndex[2] = src.mCubeIndex[2];

  mpEffect = src.mpEffect;
  if (mpEffect != 0)
    mpEffect->AddRef();

  mpHitSphere = src.mpHitSphere;
  if (mpHitSphere != 0)
    mpHitSphere->AddRef();

  mStartTimeLow = src.mStartTimeLow;
  mStartTimeHigh = src.mStartTimeHigh;
  mbActive = src.mbActive;
  mbRemove = src.mbRemove;

  mpOrnament = src.mpOrnament;
  if (mpOrnament != 0)
    mpOrnament->AddRef();

  mPointers.CopyFrom(&src.mPointers);
}

// @ 0x00c940d0
void __cdecl PartitionPositions(Vec3_s00c9_3a40* first, Vec3_s00c9_3a40* last, float px, float py, float pz, float qx, float qy, float qz)
{
  float dx = qx - px;
  float dy = qy - py;
  float dz = qz - pz;

  for (;;) {
    for (;;) {
      float ax = qx - first->x;
      float ay = qy - first->y;
      float az = qz - first->z;
      if (dx * dx + dy * dy + dz * dz <= ax * ax + ay * ay + az * az)
        break;
      ++first;
    }
    do {
      --last;
      float bx = qx - last->x;
      float by = qy - last->y;
      float bz = qz - last->z;
      if (dx * dx + dy * dy + dz * dz >= bx * bx + by * by + bz * bz)
        break;
    } while (true);

    if (last <= first)
      break;

    float tx = first->x, ty = first->y, tz = first->z;
    first->x = last->x;
    first->y = last->y;
    first->z = last->z;
    last->x = tx;
    last->y = ty;
    last->z = tz;
    ++first;
  }
}

// @ 0x00c94270
void __cdecl PartialSortPositions(Vec3_s00c9_3a40* first, Vec3_s00c9_3a40* mid, Vec3_s00c9_3a40* last, float x, float y, float z)
{
  HeapMake(first, mid, x, y, z);

  for (Vec3_s00c9_3a40* p = mid; p < last; ++p) {
    float ax = x - p->x;
    float ay = y - p->y;
    float az = z - p->z;
    float da = ax * ax + ay * ay + az * az;

    float bx = x - first->x;
    float by = y - first->y;
    float bz = z - first->z;
    float db = bx * bx + by * by + bz * bz;

    if (da < db) {
      Vec3_s00c9_3a40 tmp = *p;
      *p = *first;
      HeapAdjust(first, 0, (int)(mid - first), 0, tmp, x, y, z);
    }
  }

  HeapSort(first, mid, x, y, z);
}

// @ 0x00c94430
cFishingHotSpot* findHotSpot(u32 key)
{
  HotSpotRow* end = g_HotSpotEnd;
  HotSpotRow* it = HotSpotLowerBound(g_HotSpotBegin, end, &key, g_HotSpotLess);
  if (it != end && key >= it->mKey) {
    HotSpotRow* stop = &it[1];
    if (it != stop)
      return &it->mSpot;
  }
  return 0;
}

// @ 0x00c94470
void cSpatialView::GetDebugToolTip(cString* out)
{
  cTribe_s00c9_3a40* tribe = (cTribe_s00c9_3a40*)((char*)this - offsetof(cTribe_s00c9_3a40, mSpatial120));

  cString text;
  text.ctor();

  void* relMgr = FUN_00b3d2c0();
  void* mode = FUN_00b5b800();

  char* selected = 0;
  char* selectedEnd = 0;
  if (mode == &g_GameModeTribe) {
    void* nouns = FUN_00b3d300();
    void* player = ((cGameNounManager*)nouns)->GetPlayerTribe();
    void* s = ((cRelationshipManager*)relMgr)->GetPlayerString(&text, tribe, player);
    if (s != &text) {
      selected = *(char**)s;
      selectedEnd = *((char**)s + 1);
    }
  } else if (mode == &g_GameModeCiv) {
    void* nouns = FUN_00b3d300();
    void* player = ((cGameNounManager*)nouns)->GetPlayerCivilization();
    void* s = ((cRelationshipManager*)relMgr)->GetPlayerString(&text, tribe, player);
    if (s != &text) {
      selected = *(char**)s;
      selectedEnd = *((char**)s + 1);
    }
  } else if (mode == &g_GameModeSpace) {
    void* empire = FUN_01021300();
    void* player = *(void**)((char*)empire + 0x84);
    u32 id = ((u32(__thiscall*)(cTribe_s00c9_3a40*))VF(tribe, 0x4c))(tribe);
    void* s = ((cRelationshipManager*)relMgr)->GetDebugString(&text, id, player);
    if (s != &text) {
      selected = *(char**)s;
      selectedEnd = *((char**)s + 1);
    }
  }

  if (selectedEnd - selected > 1 && selected != 0)
    operator_delete__(selected);

  u32 count;
  if (this->mbFlag214 != 0 && tribe->mbFlag33c == 0)
    count = tribe->mCount338;
  else {
    CitizenVec* v = (CitizenVec*)((void*(__thiscall*)(cTribe_s00c9_3a40*))VF(tribe, 0x90))(tribe);
    count = (u32)(v->mpEnd - v->mpBegin);
  }

  u32 food = ((u32(__thiscall*)(cTribe_s00c9_3a40*))VF(tribe, 0xa4))(tribe);
  FUN_00472fe0(out, "Tribe\n%s\nPopulation = %d\nFood = %d", &text, count, food);

  if (mode == &g_GameModeTribe) {
    bool valid = ((bool(__thiscall*)(cSpatialView*))VF(this, 0x58))(this);
    if (!valid) {
      out->Append("\nRelationship Events:", "");

      cString line;
      line.ctor();

      void* nouns = FUN_00b3d300();
      void* playerTribe = ((cGameNounManager*)nouns)->GetPlayerTribe();
      u32 a = ((u32(__thiscall*)(void*))VF(playerTribe, 0x4c))(playerTribe);
      u32 b = ((u32(__thiscall*)(cTribe_s00c9_3a40*))VF(tribe, 0x4c))(tribe);
      relMgr = FUN_00b3d2c0();
      float f = ((cRelationshipManager*)relMgr)->GetRelationship((void*)a);
      FUN_005f9450(out, "\n  This Tribe Feelings for Player [%.3f]:", (double)f);

      CitizenVec* events = (CitizenVec*)FUN_00d026d0();
      for (cCitizen** p = events->mpBegin; p != events->mpEnd; ++p) {
        u32 ev = (u32)*p;
        u32 c = ((u32(__thiscall*)(void*))VF(playerTribe, 0x4c))(playerTribe);
        u32 d = ((u32(__thiscall*)(cTribe_s00c9_3a40*))VF(tribe, 0x4c))(tribe);
        relMgr = FUN_00b3d2c0();
        float val = ((cRelationshipManager*)relMgr)->CalculateRelationshipEvent((void*)c, (void*)d);
        float absVal = val < 0 ? -val : val;
        if (absVal >= 0.1f) {
          line.Load(0xa14ee9b6, ev, 0);
          const wchar_t* s = line.GetText();
          FUN_005f9450(out, "\n    %ls [%.3f]", s, (double)val);
        }
      }

      for (cCitizen** p = events->mpBegin; p != events->mpEnd; ++p) {
        u32 ev = (u32)*p;
        u32 c = ((u32(__thiscall*)(void*))VF(tribe, 0x4c))(tribe);
        u32 d = ((u32(__thiscall*)(void*))VF(playerTribe, 0x4c))(playerTribe);
        relMgr = FUN_00b3d2c0();
        float val = ((cRelationshipManager*)relMgr)->CalculateRelationshipEvent((void*)c, (void*)d);
        float absVal = val < 0 ? -val : val;
        if (absVal >= 0.1f) {
          line.Load(0xa14ee9b6, ev, 0);
          const wchar_t* s = line.GetText();
          FUN_005f9450(out, "\n    %ls [%.3f]", s, (double)val);
        }
      }

      line.GetText();
      line.dtor();
    }
  }

  text.dtor();
}

// @ 0x00c947d0
void __thiscall cTribe_s00c9_47d0::ShowFishingString(float amount, const Vector3_s00c9_47d0* pos)
{
    if (!mSpatial.IsVisible())
        return;

    if (amount > 0.0f)
        DoShowFishingString(0xdbf1ae1f, L"%lc%lc%s", L'+', 0x268f, amount, pos);
    else
        DoShowFishingString(0xd2bf5747, L"%lc%lc%ls", L'-', 0x268f, amount, pos);
}

// @ 0x00c94b50
void __thiscall cTribe_s00c9_47d0::SquirtFishingSplash(float radius)
{
    if (!mSpatial.IsVisible())
        return;

    cSpatial_s00c9_47d0* pCasting = &mpToolNode->mSpatial;
    const Vector3_s00c9_47d0& facing = pCasting->GetPosition();
    const float x = facing.x;
    const float y = facing.y;
    const float z = facing.z;
    const float invLen = 1.0f / sqrtf(y * y + (z * z + x * x) + 1e-08f);

    Vector3_s00c9_47d0 pos;
    pos.x = invLen * x * 2.0f + x;
    pos.y = invLen * y * 2.0f + y;
    pos.z = invLen * z * 2.0f + z;
    ShowFishingString(radius, &pos);
}

// @ 0x00c94c30
template <> SpVector<Vector3_s00c9_47d0>& SpVector<Vector3_s00c9_47d0>::operator=(const SpVector<Vector3_s00c9_47d0>& x)
{
    if (this != &x) {
        const unsigned n = (unsigned)(x.mpEnd - x.mpBegin);
        if (capacity() < n) {
            Vector3_s00c9_47d0* pNew = grow_copy(n, x.mpBegin, x.mpEnd);
            if (mpBegin && ((uint32_t*)mpBegin)[-1])
                operator_delete__(mpBegin);
            mpBegin = pNew;
            mpCapacity = pNew + n;
        } else if (size() < n) {
            copy_impl(x.mpBegin, x.mpBegin + size(), mpBegin);
            uninitialized_copy(x.mpBegin + size(), x.mpEnd, mpEnd);
        } else {
            copy_impl(x.mpBegin, x.mpEnd, mpBegin);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x00c94ec0
namespace eastl {
Vector3_s00c9_47d0* quick_sort_impl(Vector3_s00c9_47d0* first, Vector3_s00c9_47d0* last, int depth, SP::ComparePositions compare)
{
    while (last - first > 0x1c && depth > 0) {
        Vector3_s00c9_47d0* pPivot = SelectPivot(first, first + (last - first) / 2, last - 1, compare);
        const Vector3_s00c9_47d0 pivot = *pPivot;
        Vector3_s00c9_47d0* pCut = PartitionRange(first, last, pivot, compare);
        --depth;
        quick_sort_impl(pCut, last, depth, compare);
        last = pCut;
    }
    if (depth == 0)
        InsertionSort(first, last, compare);
    return first;
}
}  // namespace eastl

// @ 0x00c95010
cFishingHotSpot_s00c9_47d0& cFishingHotSpot_s00c9_47d0::operator=(const cFishingHotSpot_s00c9_47d0& x)
{
    mCenter = x.mCenter;
    mRadius = x.mRadius;
    mScale = x.mScale;
    mFacing = x.mFacing;
    mDirection = x.mDirection;

    mpFirst = x.mpFirst;
    mpSecond = x.mpSecond;
    mField30 = x.mField30;
    mField34 = x.mField34;
    mbFlag38 = x.mbFlag38;
    mbFlag39 = x.mbFlag39;
    mpThird = x.mpThird;
    mPoints = x.mPoints;
    return *this;
}

// @ 0x00c950f0
void __thiscall cTribe_s00c9_47d0::RemoveRefObject(void* key)
{
    cToolSlot* const pFound = FindToolSlot(mToolSlots.mpBegin, mToolSlots.mpEnd, &key);
    if (pFound != mToolSlots.mpEnd) {
        if (pFound + 1 < mToolSlots.mpEnd)
            copy_impl<cToolSlot>(pFound + 1, mToolSlots.mpEnd, pFound);
        mToolSlots.mpEnd -= 1;
        mToolSlots.mpEnd->~cToolSlot();
    }
}

// @ 0x00c95150
void __thiscall cTribe_s00c9_47d0::RemoveToolSlot(void* key)
{
    AutoRef* pSlot = mRefObjects.mpBegin;
    AutoRef* const pEnd = mRefObjects.mpEnd;
    while (pSlot != pEnd && pSlot->mpObject != key)
        ++pSlot;
    if (pSlot != pEnd)
        mRefObjects.EraseInline(pSlot, pSlot + 1);
}

// @ 0x00c951d0
void __thiscall cTribe_s00c9_47d0::ResetToolLayout()
{
    int count = 0;
    const Vector3_s00c9_47d0* pData = 0;
    if (!mpToolLayout)
        return;

    if (mpToolLayoutKey && ResolveToolData(mpToolLayoutKey, 0x73326b2, &count, &pData)) {
        SpVector<Vector3_s00c9_47d0> offsets;
        for (int i = 0; i < count; ++i) {
            Vector3_s00c9_47d0 pos = XformVector(pData[i], mSpatial.GetOrientation());
            const Vector3_s00c9_47d0& origin = mSpatial.GetPosition();
            pos.x += origin.x;
            pos.y += origin.y;
            pos.z += origin.z;
            if (i == 0)
                mpToolNode->mSpatial.SetPosition(pos);
            else
                offsets.push_back(pos);
        }

        Vector3_s00c9_47d0 center;
        float facing = 0.0f;
        if (mSpatial.GetFacing(&center))
            facing = center.x;
        const Vector3_s00c9_47d0& origin = mSpatial.GetPosition();
        mActionCircle.SetAtCenter(origin, 0.0f, &center, 10.0f);
        mActionCircle.EmitCopy(origin, 3.0f);
        mActionCircle.Execute();
    }

    if (mpToolLayoutKey && ResolveToolData(mpToolLayoutKey, 0x6303995, &count, &pData)) {
        mHutLocations.erase(mHutLocations.mpBegin, mHutLocations.mpEnd);
        const int limit = count > 15 ? 15 : count;
        for (int i = 0; i < limit; ++i) {
            Vector3_s00c9_47d0 pos = XformVector(pData[i], mpToolNode->mSpatial.GetOrientation());
            const Vector3_s00c9_47d0& origin = mpToolNode->mSpatial.GetPosition();
            pos.x += origin.x;
            pos.y += origin.y;
            pos.z += origin.z;
            mHutLocations.push_back(pos);
        }
    }
}

// @ 0x00c95540
void __thiscall cTribe_s00c9_47d0::AddPanicBubble(const Vector3_s00c9_47d0& pos, float amount, int empireID)
{
    if (empireID != SP::PlayerEmpireID())
        return;
    mEmptyBubbles.push_back();
    mEmptyBubbles.back().mPosition = pos;
    mEmptyBubbles.back().mAmount = amount;
}

// @ 0x00c955e0
template <> void SpVector<cTribeChatArea_s00c9_47d0>::resize(unsigned n)
{
    const unsigned current = size();
    if (current < n) {
        InsertFillChatAreas(mpEnd, n - current, cTribeChatArea_s00c9_47d0());
        return;
    }
    cTribeChatArea_s00c9_47d0* const pNewEnd = mpBegin + n;
    copy_Rec20(mpEnd, mpEnd, pNewEnd);
    mpEnd = pNewEnd;
}

// @ 0x00c95660
cTextureAsyncQueueEntry_s00c9_47d0* __thiscall cTextureAsyncQueue::Insert(DequeIter2* pResult, DequeIter2 pos, const cTextureAsyncQueueEntry_s00c9_47d0& value)
{
    if (pos.mpCurrent == pos.mpLast) {
        // the iterator sits past the end of its block: move to the start of the next one
        pos.mpBlock = *(void**)pos.mpBlock;
        pos.mpFirst = pos.mpBlock;
        pos.mpCurrent = pos.mpBlock;
        pos.mpLast = (char*)pos.mpBlock + 0x100;
    }

    const int index = ((int)((char*)mpBlocks - (char*)mpBlockEnd) >> 2) * 0x40
                    + ((int)((char*)mpEnd - (char*)mpBegin) >> 2) - 0x40
                    + ((int)((char*)pos.mpCurrent - (char*)pos.mpBlock) >> 2);

    const int lastIndex = ((int)((char*)mpLastBlock - (char*)mpBlockEnd) >> 2) * 0x40
                        + ((int)((char*)mpBlockBegin - (char*)mpBlocks) >> 2)
                        + ((int)((char*)mpEnd - (char*)mpBegin) >> 2);

    if (index < lastIndex / 2) {
        DequeInsertFront((cTextureAsyncQueueEntry_s00c9_47d0*)pos.mpCurrent, &value, mpBegin);
        DequeOnInsertFront();
    } else {
        cTextureAsyncQueueEntry_s00c9_47d0 first = *mpBegin;
        DequeInsertBack((cTextureAsyncQueueEntry_s00c9_47d0*)pos.mpCurrent, &value, mpEnd);
        DequeOnInsertBack();
        (void)first;
    }

    DequeIter2 result;
    result.mpBlock = mpBegin;
    result.mpFirst = mpCapacity;
    result.mpCurrent = mpEnd;
    result.mpLast = mpBlocks;
    result += index;
    pResult->mpBlock = result.mpBlock;
    pResult->mpCurrent = result.mpCurrent;
    pResult->mpFirst = result.mpFirst;
    pResult->mpLast = result.mpLast;
    return (cTextureAsyncQueueEntry_s00c9_47d0*)pResult;
}

// @ 0x00c95780
void __thiscall cResourceReader::ReadPositions(SpVector<Vector3_s00c9_47d0>* pOut)
{
    pOut->erase(pOut->mpBegin, pOut->mpEnd);

    int count = 0;
    ReadInt32(GetStream(), &count, 1, 0);
    Vec3Vec_Reserve(pOut, count);

    const unsigned n = (unsigned)count;
    for (unsigned i = 0; i < n; ++i) {
        Vector3_s00c9_47d0 pos(0.0f, 0.0f, 0.0f);
        ReadPositionValue(this, &pos);
        pOut->push_back(pos);
    }

    v1c();      // finish the read (tail call in the original)
}

// @ 0x00c95930
void __stdcall FreeBubbleLists(cBubbleNode** pLists, unsigned count)
{
    for (unsigned i = 0; i < count; ++i) {
        cBubbleNode* pNode = pLists[i];
        while (pNode) {
            cBubbleNode* const pFree = pNode;
            pNode = pNode->mpNext;
            pFree->mOwner.Destroy();
            operator_delete__(pFree);
        }
        pLists[i] = 0;
    }
}

// @ 0x00c95980
namespace eastl {
template <typename RandomAccessIterator, typename Compare> void quick_sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    if (first != last) {
        quick_sort_impl<RandomAccessIterator, Compare>(first, last, 2 * Log2((int)(last - first)), compare);
        if ((int)(last - first) > kQuickSortLimit) {
            insertion_sort<RandomAccessIterator, Compare>(first, first + kQuickSortLimit, compare);
            insertion_sort_simple<RandomAccessIterator, Compare>(first + kQuickSortLimit, last, compare);
        } else
            insertion_sort<RandomAccessIterator, Compare>(first, last, compare);
    }
}
}  // namespace eastl

// @ 0x00c95af0
void SP::cTribe_s00c9_5980::SetupChatAreas()
{
    if (!mpTools_2d4) return;
    (void)mpChatAreas_298;
    (void)mfScale_268;
    (void)mTimer_510;
    (void)mpVec1904_begin;
    (void)mpVec1904_end;
    (void)mpStructVec_370;

    void* id = FUN_00cc7070(0x60ba14a);
    FUN_00cc8350((void*)(size_t)0);
    (void)id;

    int local_40 = 0;
    int local_34 = 0;
    FUN_006a0990(mpTools_2d4, 0x5786667, &local_40, &local_34);

    void* planet = FUN_00b3d350();
    (void)planet;

    FUN_00c955e0((void*)((uchar*)this + 0x294), local_40);

    for (int i = 0; i < local_40; ++i) {
        uchar* area = (uchar*)(size_t)mpChatAreas_294 + i * 0x14;
        area[0x10] = 0;
        *(float*)(area + 0) = 0.0f;
        *(float*)(area + 4) = 0.0f;
        *(float*)(area + 8) = 0.0f;
        *(float*)(area + 0xc) = *(float*)(area + 8);
        *(float*)(area + 8) = 0.0f;

        float tmp[3];
        float* pf = (float*)FUN_0059aed0(tmp, area, (void*)(size_t)mpHandle_260);
        (void)pf;

        float p[3];
        p[0] = tmp[0]; p[1] = tmp[1]; p[2] = tmp[2];
        float surf[3];
        FUN_00b815a0(surf, p);
        *(float*)(area + 0) = surf[0];
        *(float*)(area + 4) = surf[1];
        *(float*)(area + 8) = surf[2];

        void* id2 = FUN_00cc7070(0x60ba14a);
        FUN_00cc8350(id2);
    }
}

// @ 0x00c95cc0
void SP::cTribe_s00c9_5980::AddChatArea_5cc0(void* pObj)
{
    void** begin = (void**)mChatAreaHandles_354.mpBegin;
    void** end   = (void**)mChatAreaHandles_354.mpEnd;
    void** it = begin;
    for (; it != end; ++it) {
        void* want = pObj ? (void*)((uchar*)pObj + 0xc0) : 0;
        if (*it == want) break;
    }
    if (it != end) return;

    void* val = pObj ? (void*)((uchar*)pObj + 0xc0) : 0;
    if (val) ((void(__thiscall*)(void*))vc(val, 0xbc))(val);

    void** slot = (void**)mChatAreaHandles_354.mpEnd;
    if (slot < (void**)mChatAreaHandles_354.mpCapacity) {
        mChatAreaHandles_354.mpEnd = (uchar*)slot + 4;
        if (slot) {
            *slot = val;
            if (!val) return;
            ((void(__thiscall*)(void*))vc(val, 0xbc))(val);
        }
    } else {
        FUN_00bab900(slot, &val);
    }
    if (val) ((void(__thiscall*)(void*))vc(val, 0xc0))(val);
}

// @ 0x00c95d70
void SP::cTribe_s00c9_5980::AddExistingCreatureInternal(void* pCreature)
{
    if (!pCreature) { ++mnCount_338; return; }

    void** begin = (void**)mCreatures_340.mpBegin;
    void** end   = (void**)mCreatures_340.mpEnd;
    void** it = begin;
    for (; it != end; ++it) { if (*it == pCreature) break; }
    if (it != end) return;

    void** slot = (void**)FUN_00c8ec60(begin, end, &pCreature);
    if (slot != end) return;

    ((void(__thiscall*)(void*))vc(pCreature, 0))(pCreature);
    void* held = pCreature;
    FUN_00e1c7f0(&held);
    if (held) ((void(__thiscall*)(void*))vc(held, 4))(held);

    if (FUN_00c0b760()) {
        void* val = (void*)((uchar*)pCreature + 0xc0);
        void* hold = val;
        if (hold) ((void(__thiscall*)(void*))vc(hold, 0xbc))(hold);
        FUN_00afc470(&hold);
        if (hold) ((void(__thiscall*)(void*))vc(hold, 0xc0))(hold);
    }
}

// @ 0x00c95ee0
void SP::cTribe_s00c9_5980::RemoveCreature(void* pCreature, uchar bRemove)
{
    uchar packing = mbPacking_334;
    if (packing != 0 && mnCount_338 != 0) --mnCount_338;

    void* cr = pCreature;
    if (!cr) {
        if (packing != 0) return;
        cr = (void*)FUN_00c8f310();
        if (!cr) return;
    }

    if (FUN_00c232d0()) {
        FUN_00c00660((void*)0);
    }

    void* spatial = (void*)((uchar*)cr + 0x58);
    if (bRemove) {
        void* bm = (void*)FUN_00b3d260();
        ((void(__thiscall*)(void*, void*))vc(bm, 0x3c))(bm, spatial);
    } else {
        ((void(__thiscall*)(void*))vc(spatial, 0x34))(spatial);
    }

    uchar hadInteraction = ((uchar*)cr)[0xb5e];
    ((uchar*)cr)[0x130] = 0;
    ((uchar*)cr)[0x12f] = 0;
    if (!hadInteraction) {
        ((void(__thiscall*)(void*))vc(cr, 0x8c))(cr);
    }

    FUN_00c95150(cr);
    FUN_00c950f0(cr);

    if (bRemove) {
        if (((uchar*)cr)[0xb67]) {
            void* nm = (void*)FUN_00b3d480(cr);
            if ((bool)(uint)(size_t)FUN_00acd410(nm)) return;
        }
        void* nm = (void*)FUN_00b3d300();
        FUN_00b225d0(nm, cr);
    } else {
        FUN_00c22ee0(cr);
    }
}

// @ 0x00c95fe0
void* SP::cTribe_s00c9_5980::SpawnHut_5fe0(void* pArg)
{
    (void)pArg;
    void* nounMgr = (void*)FUN_00b3d300();
    void* noun = (void*)FUN_00b20c60(nounMgr, 0x18c8f0c);
    return noun;
}

// @ 0x00c96150
bool SP::cTribe_s00c9_5980::AddTool_6150(void* pTool)
{
    (void)pTool;
    return mpTools_2d4 != 0;
}

// @ 0x00c962b0
bool SP::cTribe_s00c9_5980::UpdateHut_62b0()
{
    bool r = false;
    (void)r;
    if (!mpObject_368) return false;

    void* nounMgr = (void*)FUN_00b3d300();
    void* noun = (void*)FUN_00b20c60(nounMgr, 0x629bafe);
    void* tool = 0;
    if (noun) tool = ((void*(__thiscall*)(void*, uint))vc(noun, 0xc))(noun, 0x629baec);

    void* prev = mpHandle_260;
    if (tool != prev) {
        if (tool) ((void(__thiscall*)(void*))vc(tool, 0))(tool);
        mpHandle_260 = tool;
        if (prev) ((void(__thiscall*)(void*))vc(prev, 4))(prev);
    }

    ((void(__thiscall*)(void*, void*))vc(mpHandle_260, 0x54))(mpHandle_260, this);

    void* o = mpObject_368;
    void* sub = (void*)((uchar*)o + 0x34);
    ((void(__thiscall*)(void*, void*))vc(sub, 0x38))(sub, (void*)0);

    float v[3];
    void* res = ((void*(__thiscall*)(void*, float*))vc(sub, 0x5c))(sub, v);

    float nv[3];
    nv[0] = ((float*)res)[0] * -1.0f;
    nv[1] = ((float*)res)[1] * -1.0f;
    nv[2] = ((float*)res)[2] * -1.0f;

    float out[3];
    void* planet = (void*)FUN_00b3d350();
    FUN_00b7f250(planet, nv, out);

    ((void(__thiscall*)(void*, void*))vc(sub, 0x3c))(sub, out);
    return true;
}

// @ 0x00c96410
bool SP::cTribe_s00c9_5980::Read(void* pStream)
{
    void* reader = (void*)((void*(__thiscall*)(void*))vc(pStream, 0x20))(pStream);
    void* handle = (void*)((void*(__thiscall*)(void*))vc(reader, 0x18))(reader);
    int tmp = 0;
    (void)handle; (void)tmp;

    bool ok = true;
    FUN_00c00530(this, pStream);
    FUN_00c88b00(this, pStream);
    FUN_00cee440(this, pStream);
    (void)ok;

    FUN_00c955e0((void*)((uchar*)this + 0x1904), 0xe);
    FUN_00b7f250((void*)((uchar*)this + 0x510), 0, 0);
    FUN_004548d0(0xe);
    FUN_0067de30();

    float g = 0.0f;
    FUN_00cc7830((void*)((uchar*)this + 0x558), mfScale_268, g);
    return true;
}

// @ 0x00c966d0
void* SP::cTribe_s00c9_5980::GetStructures()
{
    void* o = mpObject_368;
    if (o) {
        void* sub = (void*)((uchar*)o + 0x120);
        void* r = (void*)((void*(__thiscall*)(void*))vc(sub, 8))(sub);
        void* val = r;
        if (val) ((void(__thiscall*)(void*))vc(val, 0xbc))(val);

        void** end = (void**)mChatAreaHandles_354.mpEnd;
        if (end < (void**)mChatAreaHandles_354.mpCapacity) {
            mChatAreaHandles_354.mpEnd = (uchar*)end + 4;
            if (end) *end = val;
        } else {
            FUN_00bab900(end, &val);
        }
        if (val) ((void(__thiscall*)(void*))vc(val, 0xc0))(val);
    }

    FUN_00bdefa0(mChatAreaHandles_354.mpBegin, mpObject_368, mpStructVec_370, (uchar*)this + 0x36c);
    return (void*)&mChatAreaHandles_354;
}

// @ 0x00c967a0
void* SP::cTribe_s00c9_5980::GetInhabitants()
{
    void** it = (void**)mCreatures_340.mpBegin;
    void** end = (void**)mCreatures_340.mpEnd;
    for (; it != end; ++it) {
        void* cr = *it;
        if (FUN_00c0b760()) {
            void* hold = cr;
            if (hold) ((void(__thiscall*)(void*))vc(hold, 0))(hold);

            void** e2 = (void**)mChatAreaHandles_354.mpEnd;
            if (e2 < (void**)mChatAreaHandles_354.mpCapacity) {
                mChatAreaHandles_354.mpEnd = (uchar*)e2 + 4;
                if (e2) {
                    *e2 = cr;
                    if (cr) ((void(__thiscall*)(void*))vc(cr, 0))(cr);
                }
            } else {
                FUN_00aea5d0(e2, &cr);
            }
            if (cr) ((void(__thiscall*)(void*))vc(cr, 4))(cr);
        }
    }
    return (void*)&mCreatures_340;
}

// @ 0x00c96840
void* SP::cTribe_s00c9_5980::CopyFrom_6840(void* pOther)
{
    uchar* d = (uchar*)this;
    uchar* s = (uchar*)pOther;
    *(uint*)(d + 0)  = *(uint*)(s + 0);
    *(uint*)(d + 4)  = *(uint*)(s + 4);
    *(uint*)(d + 8)  = *(uint*)(s + 8);
    for (int i = 0; i < 0x10; ++i) *(uint*)(d + 0xc + i * 4) = *(uint*)(s + 0xc + i * 4);
    *(uint*)(d + 0x4c) = *(uint*)(s + 0x4c);
    *(uint*)(d + 0x50) = *(uint*)(s + 0x50);
    for (int i = 0; i < 2; ++i) {
        uchar* de = d + 0x54 + i * 0x1c;
        uchar* se = s + 0x54 + i * 0x1c;
        for (int j = 0; j < 7; ++j) *(uint*)(de + j * 4) = *(uint*)(se + j * 4);
    }
    *(uint*)(d + 0x8c)  = *(uint*)(s + 0x8c);
    *(float*)(d + 0x90) = *(float*)(s + 0x90);
    *(float*)(d + 0x94) = *(float*)(s + 0x94);
    *(uint*)(d + 0x98)  = *(uint*)(s + 0x98);
    *(uint*)(d + 0x9c)  = *(uint*)(s + 0x9c);
    FUN_0050d4e0(d + 0xa0, s + 0xa0);

    void* so  = *(void**)(s + 0xb4);
    void* dof = *(void**)(d + 0xb4);
    if (so != dof) {
        if (so) ((void(__thiscall*)(void*))vc(so, 0))(so);
        *(void**)(d + 0xb4) = so;
        if (dof) ((void(__thiscall*)(void*))vc(dof, 4))(dof);
    }
    return this;
}

// @ 0x00c96950
void* CHash::FUN_00c96950(void* pArg)
{
    u32 slot = 0;
    void* r = FUN_00c929a0(&slot, pArg);
    if (slot != (u32)(size_t)((u8**)mpBuckets)[mW08])
        return (u8*)r + 4;

    u8 probe[0x2c];
    for (int i = 0; i < 0x2c; ++i)
        probe[i] = 0;
    SELF(probe)->FUN_00ca09f0(0);

    u8 keyBlob[0x40];
    for (int i = 0; i < 0x40; ++i)
        keyBlob[i] = 0;
    *(u32*)keyBlob = *(u32*)pArg;
    FUN_00c93750(&keyBlob[0x34], &keyBlob[0x00]);

    u8 outBlob[0x2c];
    SELF(probe)->FUN_00c94d60(&outBlob[0x00], &keyBlob[0x00], 0);
    SELF(&keyBlob[0x34])->FUN_00abf900();
    SELF(&keyBlob[0x00])->FUN_00abf900();
    return (u8*)&outBlob[0x00];
}

// @ 0x00c96a00
u32 CHash::FUN_00c96a00(void* pKey)
{
    u32 before = mW0c;
    u32 key = *(u32*)pKey;
    u32 b = key % mW08;
    HashNode** buckets = (HashNode**)mpBuckets;
    HashNode** link = &buckets[b];
    if (*link == 0)
        return before - mW0c;

    while ((u32)(size_t)*link != 0 && (*link)->mKey != key)
        link = &(*link)->pNext;
    if (*link == 0)
        return before - mW0c;

    while ((u32)(size_t)*link != 0) {
        HashNode* cur = *link;
        if (cur->mKey != key)
            break;
        *link = cur->pNext;
        SELF(&cur->mGap04[0x00])->FUN_00abf900();
        FUN_00f47380(cur);
        --mW0c;
    }
    return before - mW0c;
}

// @ 0x00c96e80
void CRes::FUN_00c96e80(u32 a)
{
    SELF(this)->FUN_00c95d70((void*)(size_t)a, 1);
}

// @ 0x00c97220
bool LoadTribeArchetypeData()
{
    if (gTribeArchetypesLoaded)
        return true;

    bool loadedAny = false;
    cPropertyManager_s00c9_7220* pm = PropertyManager_s00c9_7220();
    uint32_t groupIDs[3];
    groupIDs[0] = 0xab83a874;
    groupIDs[1] = 0x27adfe33;
    groupIDs[2] = 0xf29db649;

    int cnt1, cnt2;
    uint32_t* data1;
    uint32_t* data2;
    for (uint32_t g = 0; g < 3; g++) {
        uint32_t groupID = groupIDs[g];
        for (int i = 0; i < 32; i++)
            gTribeArchetypes[g * 32 + i] = TribeArchetype();

        PLRef pl;
        pl.p = 0;
        struct IdVec : SpVec { uint32_t extra; } ids;
        ids.mpBegin = 0;
        ids.mpEnd = 0;
        ids.mpCapacity = 0;
        PropertyManager_s00c9_7220()->GetPropertyListIDs(groupID, &ids);

        uint32_t* it = ids.mpBegin;
        uint32_t* itEnd = ids.mpEnd;
        if (it == itEnd) {
            ids.free();
            if (pl.p) pl.p->Release();
        } else {
            for (; it != itEnd; it++) {
                uint32_t instanceID = *it;
                if (pl.p) {
                    cPropertyList* old = pl.p;
                    pl.p = 0;
                    old->Release();
                }
                Property* p;
                if (pm->GetPropertyList(instanceID, groupID, &pl.p) && pl.p &&
                    pl.p->GetProperty(0x64aaf64e, p) && p->mnType == 10) {
                    uint32_t idx = *(uint32_t*)p->GetValuePtr();
                    if (idx - 1 <= 0x1e) {
                        TribeArchetype* a = &gTribeArchetypes[(g << 5) + idx];
                        loadedAny = true;
                        {
                            cPropertyList* cur = pl.p;
                            if (cur != a->mpRef) {
                                cPropertyList* old = a->mpRef;
                                if (cur) cur->AddRef();
                                a->mpRef = cur;
                                if (old) old->Release();
                            }
                        }
                        LoadU32(pl.p, 0x2857b21e, &a->f00);
                        LoadU32(pl.p, 0x80fe0f1b, &a->f04);
                        LoadU32(pl.p, 0xb0eb1e38, &a->f08);
                        LoadU32(pl.p, 0x982c7059, &a->f8c);
                        LoadFloat(pl.p, 0xe0be991f, &a->f90);
                        LoadFloat(pl.p, 0x1570506e, &a->f94);
                        GetPropertyAsVector2(pl.p, 0xd164f429, &a->v98);
                        {
                            cnt1 = 0;
                            data1 = 0;
                            if (GetPropertyAsUint32Array(pl.p, 0xa9a2d5e0, &cnt1, &data1)) {
                                a->textures.clear();
                                a->textures.reserve(cnt1);
                                for (int k = 0; k < cnt1; k++)
                                    a->textures.push_back(data1[k]);
                            }
                        }
                        LoadU32(pl.p, 0x91fe517b, &a->f50);
                        a->listCount = 0;
                        {
                            cnt2 = 0;
                            data2 = 0;
                            if (GetPropertyAsUint32Array(pl.p, 0x7862aee7, &cnt2, &data2)) {
                                for (int k = 0; k < cnt2; k++) {
                                    uint32_t v = data2[k];
                                    if (v - 1 <= 9)
                                        a->list[a->listCount++] = v;
                                }
                            }
                        }
                        LoadFloat(pl.p, 0x80a52ac0, &a->f58);
                        LoadFloat(pl.p, 0xd5291551, &a->f5c);
                        LoadFloat(pl.p, 0x58a47b38, &a->f60);
                        LoadFloat(pl.p, 0x27df57be, &a->f64);
                        LoadFloat(pl.p, 0xac245f82, &a->f68);
                        LoadFloat(pl.p, 0x2df9a743, &a->f6c);
                        LoadFloat(pl.p, 0xf74c0eb9, &a->f70);
                        LoadFloat(pl.p, 0xa3102906, &a->f74);
                        LoadFloat(pl.p, 0x2b793112, &a->f78);
                    }
                }
            }
            ids.free();
            if (pl.p) pl.p->Release();
        }
    }

    if (loadedAny)
        gTribeArchetypesLoaded = true;
    return loadedAny;
}

// @ 0x00c979e0
Vec3* cTribe_s00c9_7220::RandomRegionPoint(Vec3* out, uint32_t key, int)
{
    RegionSlot* slot = this->map4e4.Find(&key);

    Vec3 a, b;
    Frame(key, &a, &b);

    if (slot->mpBegin == slot->mpEnd) {
        out->x = a.x;
        out->y = a.y;
        out->z = a.z;
        return out;
    }

    int d0 = (int)(slot->m24 - (uint32_t)slot->mpBuckets) >> 2;
    int d1 = (int)((uint32_t)slot->mpEnd - (uint32_t)slot->mpValueBase) >> 2;
    int d2 = (int)((uint32_t)slot->mpBucketEnd - (uint32_t)slot->mpBegin) >> 2;
    int n = ((d0 << 6) + d1 + d2) - 0x40;

    float r = gTribeRandCtx.Next(this->m18cc);
    float s = (float)n * (r * kRegionScale + kRegionBias);

    Vec3 t;
    t.x = b.x * s + a.x;
    t.y = b.y * s + a.y;
    t.z = b.z * s + a.z;
    PlanetModel_s00c9_7220()->DirectionToSurfacePosition(out, &t);
    return out;
}

// @ 0x00c97b10
Vec3* cTribe_s00c9_7220::RandomRegionPointAt(int, Vec3* out, uint32_t key)
{
    Vec3 a, b;
    Frame(key, &a, &b);

    RegionSlot* slot = this->map4e4.Find(&key);

    uint32_t* it = slot->mpBegin;
    uint32_t* end = slot->mpEnd;
    uint32_t* bucketEnd = slot->mpBucketEnd;
    uint32_t** buckets = slot->mpBuckets;
    int idx = 0;
    if (it != end) {
        do {
            if (*it == key)
                break;
            ++it;
            if (it == bucketEnd) {
                it = buckets[1];
                ++buckets;
                bucketEnd = it + 0x40;
            }
            ++idx;
        } while (it != end);
    }

    if (idx == 0) {
        out->x = a.x;
        out->y = a.y;
        out->z = a.z;
        return out;
    }

    float r = gTribeRandCtx.Next(this->m18cc);
    float s = (2.0f * r + kRegionBias) * (float)idx;

    Vec3 t;
    t.x = b.x * s + a.x;
    t.y = b.y * s + a.y;
    t.z = b.z * s + a.z;
    PlanetModel_s00c9_7220()->DirectionToSurfacePosition(out, &t);
    return out;
}

// @ 0x00c97c40
int cTribe_s00c9_7220::FindRegionIndex(uint32_t key, int)
{
    uint32_t k = key;
    RegionSlot* slot = this->map4e4.Find(&k);

    uint32_t* it = slot->mpBegin;
    uint32_t** buckets = slot->mpBuckets;
    uint32_t* bucketEnd = slot->mpBucketEnd;
    uint32_t* end = slot->mpEnd;
    int idx = 0;
    while (it != end) {
        if (*it == k)
            return idx;
        ++it;
        if (it == bucketEnd) {
            it = *++buckets;
            bucketEnd = it + 0x40;
        }
        ++idx;
    }
    return -1;
}

// @ 0x00c97ca0
int cTribe_s00c9_7220::InsertRegionValue(uint32_t key, void* obj)
{
    uint32_t k = key;
    RegionSlot* slot = this->map4e4.Find(&k);
    cRefObj* o = (cRefObj*)obj;

    if (o)
        o->AddRef();

    uint32_t* pos = slot->mpEnd;
    uint32_t* next = pos + 1;
    if (next != slot->mpCapacity) {
        slot->mpEnd = next;
        if (pos) {
            *pos = (uint32_t)obj;
            if (o)
                o->AddRef();
        }
    } else {
        slot->Insert(&obj);
    }

    if (o)
        o->Release();

    int d0 = (int)(slot->m24 - (uint32_t)slot->mpBuckets) >> 2;
    int d1 = (int)((uint32_t)slot->mpEnd - (uint32_t)slot->mpValueBase) >> 2;
    int d2 = (int)((uint32_t)slot->mpBucketEnd - (uint32_t)slot->mpBegin) >> 2;
    return ((d0 << 6) + d1 + d2) - 0x40;
}

// @ 0x00c97d40
void cTribe_s00c9_7220::UpdateRegionSlot(uint32_t key, uint32_t* extra)
{
    uint32_t k = key;
    RegionSlot* slot = this->map4e4.Find(&k);

    SlotPair out;
    SlotPair lo = slot->Lo();
    SlotPair hi = slot->Hi();
    SlotRehash(&out, lo, hi, &extra);
    if (out.a != (uint32_t)slot->mpEnd)
        slot->Update(&out, out);
}

// @ 0x00c97de0
void cTribe_s00c9_7220::Destroy()
{
    void* owned = this->mpOwned18c8;

    this->mpVtbl    = (cTribeVtbl*)0x1473e58;
    this->mpVtbl04  = (void*)0x1473e44;
    this->mpVtbl34  = (void*)0x1469cc0;
    this->mpVtbl120 = (void*)0x1473d80;
    this->mpVtbl1f4 = (void*)0x1473d64;
    this->mpVtbl20c = (void*)0x1473d20;
    this->mpVtbl230 = (void*)0x1473d00;

    if (owned) {
        SubDtor_c2e4e0(owned);
        operator delete[](owned);
    }
    this->mpOwned18c8 = 0;

    if (this->mpRef19d0) ((cRefObj*)this->mpRef19d0)->Release();
    if (this->mpRef19cc) ((cRefObj*)this->mpRef19cc)->Release();
    if (this->mpRef19c8) ((cRefObj*)this->mpRef19c8)->Release();
    if (this->mpRef19c4) ((cRefObj*)this->mpRef19c4)->Release();

    if (this->mpArray1904 && ((int*)this->mpArray1904)[-1])
        operator delete[](this->mpArray1904);

    SubDtor_cc7c50(&this->sub558[0]);
    SubDtor_b638b0(&this->sub530[0]);
    SubDtor_b638b0(&this->sub510[0]);

    this->map4e4.Destroy(this->map4e4.m04, this->map4e4.m08);
    {
        uint32_t cap = this->map4e4.m08;
        this->map4e4.m0c = 0;
        if (cap > 1)
            operator delete[]((void*)this->map4e4.m04);
    }

    if (this->mpArray418 && ((int*)this->mpArray418)[-1])
        operator delete[](this->mpArray418);

    SubDtor_afbad0(&this->sub3b4[0]);

    this->map394.Destroy(this->map394.m04, this->map394.m08);
    {
        uint32_t cap = this->map394.m08;
        this->map394.m0c = 0;
        if (cap > 1)
            operator delete[]((void*)this->map394.m04);
    }

    SubDtor_ae6970(&this->sub380[0]);
    SubDtor_ae6970(&this->sub36c[0]);

    if (this->mpRef368) ((cRefObj*)this->mpRef368)->Release();

    SubDtor_ad92d0(&this->sub354[0]);
    SubDtor_ae6970(&this->sub340[0]);

    if (this->mpArray314 && ((int*)this->mpArray314)[-1])
        operator delete[](this->mpArray314);

    if (this->mpRef2d4) ((cRefObj*)this->mpRef2d4)->Release();
    if (this->mpRef2d0) ((cRefObj*)this->mpRef2d0)->Release();

    if (this->mpArray2a8 && ((int*)this->mpArray2a8)[-1])
        operator delete[](this->mpArray2a8);

    if (this->mpArray294 && ((int*)this->mpArray294)[-1])
        operator delete[](this->mpArray294);

    if (this->mpRef290) ((cRefObj*)this->mpRef290)->Release2();

    SubDtor_b638b0(&this->sub270[0]);

    if (this->mpRef260) ((cRefObj*)this->mpRef260)->Release();

    SubDtor_b6edf0(&this->mpVtbl230);
    SubDtor_cee7a0(&this->mpVtbl20c);
    SubDtor_ac0520(&this->mpVtbl1f4);
    SubDtor_c8a420(&this->mpVtbl120);

    BaseDtor(this);
}

// @ 0x00c98080
bool cTribe_s00c9_7220::Sub120Query()
{
    return ((cTribeSub120*)&this->mpVtbl120)->Query();
}

// @ 0x00c98230
uint32_t cTribe_s00c9_7220::AllocateRegion(uint32_t key)
{
    uint32_t count;
    if (this->m334 && !this->m33c) {
        count = this->m338;
    } else {
        SpVec* v = this->mpVtbl->GetValueList(this);
        count = (uint32_t)(((int)(uint32_t)v->mpEnd - (int)(uint32_t)v->mpBegin) >> 2);
    }

    if (count < this->Sub120Count()) {
        uint32_t idx = this->Sub120Index(key);
        this->Sub120Set(idx, 1);
        return idx;
    }
    return 0;
}

// @ 0x00c99550
void __thiscall cTribe_s00c9_9140::UpdateGridAndHutArea(int unused)
{
    cPropertyManager* mgr = PropertyManager();
    if (this->mpTool2d4 != 0) {
        RefObj* old = this->mpTool2d4;
        this->mpTool2d4 = 0;
        ((TFnV)VSLOT(old, 4))(old);
    }
    ((TFnVPPP)VSLOT(mgr, 0x2c))(mgr, (void*)0x535dc193, (void*)0x2be764e2,
                                &this->mpTool2d4);

    this->SetupChatAreas();
    float base = ((cReserveParams*)0x1581208)->GetRadius(this->mpProfile18CC);

    float scale;
    if (this->mpTool2d4 == 0) {
        scale = 1.5f;
    } else {
        void* prop = 0;
        char ok = ((TFnCIP)VSLOT(this->mpTool2d4, 0x24))(this->mpTool2d4, 0x1fb2b4e, &prop);
        if (ok == 0) {
            scale = 1.5f;
        } else {
            unsigned short type = *(unsigned short*)((char*)prop + 0x12);
            if (type == 0xd || type == 0x10) {
                if ((*(unsigned char*)((char*)prop + 0x10) & 0x30) == 0)
                    scale = *(float*)(-(int)(type != 0) & (int)prop);
                else
                    scale = *(float*)*(void**)prop;
            } else {
                scale = *(float*)0x015d9c6c;
            }
        }
    }

    float radius = scale * base * 2.0f;
    this->mfRadius268 = radius;
    ReservationGrid* grid = &this->mRGrid558;
    grid->ComputeGridResolution(radius, base);
    this->FinishTask(0xc);
    this->FinishTask(0xd);
    this->FUN_00c91700();

    Vec3 pos;
    if (this->mpHut368 != 0) {
        VtblObj* spatial = &this->mpHut368->mSpatial;
        float height = ((TFnF)VSLOT(spatial, 0x74))(spatial) + 3.0f;
        Vec3 scratch;
        float* d = (float*)((TFnPP)VSLOT(spatial, 0x5c))(spatial, &scratch);
        Vec3 off;
        off.x = d[0] * height;
        off.y = d[1] * height;
        off.z = d[2] * height;
        float* p = (float*)((TFnP)VSLOT(spatial, 0x2c))(spatial);
        pos.x = p[0] + off.x;
        pos.y = p[1] + off.y;
        pos.z = p[2] + off.z;
        grid->RemoveReservedByID(grid->GetReservedList(), (const void*)0x58cac6e);
        grid->AddReserved(grid->GetReservedList(), &pos, *(float*)0x0147b9f0,
                          (const void*)0x58cac6e);
    }

    if (this->mpTool19C4 != 0) {
        grid->RemoveReservedByID(grid->GetReservedList(), (const void*)0x55cee67);
        float rad = *(float*)0x01486110;
        VtblObj* obj = (VtblObj*)((char*)this->mpTool19C4 + 0x70);
        Vec3* p = (Vec3*)((TFnPFI)VSLOT(obj, 0x2c))(obj, rad, 0x55cee67);
        grid->AddReserved(grid->GetReservedList(), p, rad, (const void*)0x55cee67);
    }
    if (this->mpTool19C8 != 0) {
        grid->RemoveReservedByID(grid->GetReservedList(), (const void*)0x5b9a134);
        float rad = *(float*)0x01486110;
        VtblObj* obj = (VtblObj*)((char*)this->mpTool19C8 + 0x70);
        Vec3* p = (Vec3*)((TFnPFI)VSLOT(obj, 0x2c))(obj, rad, 0x5b9a134);
        grid->AddReserved(grid->GetReservedList(), p, rad, (const void*)0x5b9a134);
    }

    if (this->mpTotem19D0 != 0) {
        grid->RemoveReservedByID(grid->GetReservedList(), (const void*)0x55cee70);
        float rad = *(float*)0x01470f1c;
        VtblObj* obj = &this->mpTotem19D0->mSpatial;
        Vec3* p = (Vec3*)((TFnPFI)VSLOT(obj, 0x2c))(obj, rad, 0x55cee70);
        grid->AddReserved(grid->GetReservedList(), p, rad, (const void*)0x55cee70);
    }
}

// @ 0x00c99840
void __thiscall cTribe_s00c9_9140::NotifyToolSelection()
{
    unsigned req[3];
    req[0] = 0x093256ba;
    req[1] = 0;
    req[2] = 0xf37c24e6;

    switch (FUN_00a1ad10()) {
    case 0:
        req[0] = 0x093256ba;
        break;
    case 1:
        req[0] = 0x093256b9;
        break;
    case 2:
        req[0] = 0x093256b8;
        break;
    }

    TribeTool* totem = this->mpTotem19D0;
    ((VObj94*)&totem->mSpatial)->OnRequest(req);
    this->FinishTask(0xd);
}

// @ 0x00c998c0
void __thiscall cTribe_s00c9_9140::ReserveToolsSlots(bool active)
{
    ActionCircle_s00c9_9140* circle = &this->mCircle3b4;
    if (circle->mfRadius != *(float*)0x01695374 ||
        circle->mf18 != *(float*)0x01695378 ||
        circle->mf1C != *(float*)0x0169537c ||
        circle->mb28 != 0) {

        circle->Clear();
        int count = (int)(this->mpSlotsEnd - this->mpSlotsBegin);
        for (int i = 0; i < count; ++i)
            this->mpSlotsBegin[i].Clear();

        if (active != 0) {
            TribeTool* tool = this->GetToolOfType(10);
            VtblObj* spatial = &tool->mSpatial;
            float* p = (float*)((TFnP)VSLOT(spatial, 0x2c))(spatial);
            Vec3 pos;
            pos.x = p[0];
            pos.y = p[1];
            pos.z = p[2];
            ActionSlot* slot = circle->FindSlot(&pos);
            if (slot != 0) {
                slot->Reserve(tool);
                pos.x = slot->mf0C;
                pos.y = slot->mf10;
                pos.z = slot->mf14;
                circle->AssignSlot(slot);

                Vec3 scratch;
                float* d = (float*)((TFnPP)VSLOT(spatial, 0x5c))(spatial, &scratch);
                Vec3 orient;
                Vec3 basis;
                cPlanetModel_s00c9_9140* pm = PlanetModel_s00c9_9140();
                pm->BuildSurfaceOrientation(&orient, &pos, (const Vec3*)d);
                ((TFnVP)VSLOT(spatial, 0x38))(spatial, &orient);
                ((TFnVP)VSLOT(spatial, 0x3c))(spatial, &basis);
            }

            if (this->mpHut260 != 0) {
                VtblObj* hutSpatial = &this->mpHut260->mSpatial;
                float* hp = (float*)((TFnP)VSLOT(hutSpatial, 0x2c))(hutSpatial);
                pos.x = hp[0];
                pos.y = hp[1];
                pos.z = hp[2];
                ActionSlot* hutSlot = circle->FindSlot(&pos);
                if (hutSlot != 0) {
                    pos.x = hutSlot->mf0C;
                    pos.y = hutSlot->mf10;
                    pos.z = hutSlot->mf14;
                    circle->AssignSlot(hutSlot);
                }

                VtblObj* dirObj = &this->mpHut368->mSpatial;
                Vec3 scratch2;
                float* hd = (float*)((TFnPP)VSLOT(dirObj, 0x5c))(dirObj, &scratch2);
                Vec3 neg;
                neg.x = -hd[0];
                neg.y = -hd[1];
                neg.z = -hd[2];
                Vec3 orient2;
                Vec3 basis2;
                cPlanetModel_s00c9_9140* pm2 = PlanetModel_s00c9_9140();
                pm2->BuildSurfaceOrientation(&orient2, &pos, &neg);
                ((TFnVP)VSLOT(hutSpatial, 0x38))(hutSpatial, &orient2);
                ((TFnVP)VSLOT(hutSpatial, 0x3c))(hutSpatial, &basis2);
                this->FinishTask(0xd);
                this->mVec2e8 = pos;
            }
        }

        PtrList* list = (PtrList*)((TFnP)VSLOT(this, 0xbc))(this);
        void** it = list->mpBegin;
        void** end = list->mpEnd;
        while (it != end) {
            void* obj = *it;
            if (obj != 0 && ((TFnI)VSLOT(obj, 0x58))(obj) != 10) {
                VtblObj* objSpatial = (VtblObj*)((char*)obj + 0x34);
                float* p = (float*)((TFnP)VSLOT(objSpatial, 0x2c))(objSpatial);
                Vec3 pos2;
                pos2.x = p[0];
                pos2.y = p[1];
                pos2.z = p[2];
                ActionSlot* slot = circle->FindSlot(&pos2);
                if (slot != 0) {
                    slot->Reserve(obj);
                    pos2.x = slot->mf0C;
                    pos2.y = slot->mf10;
                    pos2.z = slot->mf14;
                }
                Vec3 scratch3;
                float* d = (float*)((TFnPP)VSLOT(objSpatial, 0x5c))(objSpatial, &scratch3);
                Vec3 orient;
                Vec3 basis;
                cPlanetModel_s00c9_9140* pm = PlanetModel_s00c9_9140();
                pm->BuildSurfaceOrientation(&orient, &pos2, (const Vec3*)d);
                ((TFnVP)VSLOT(objSpatial, 0x38))(objSpatial, &orient);
                ((TFnVP)VSLOT(objSpatial, 0x3c))(objSpatial, &basis);
            }
            ++it;
        }
    }
}

// @ 0x00c99c30
void __thiscall cTribe_s00c9_9140::ChooseNewHutModel()
{
    unsigned model;
    if (((TFnC)VSLOT(&this->mQueue120, 0x58))(&this->mQueue120) == 0) {
        model = 0x653f6b9;
    } else {
        cSpeciesProfile_s00c9_9140* profile = this->mpProfile18CC;
        bool hasFirst = false;
        if (profile != 0)
            hasFirst = profile->mi608 > 0;
        if (hasFirst) {
            bool hasSecond = false;
            if (profile != 0)
                hasSecond = profile->mi60C > 0;
            if (hasSecond) {
                model = 0x653f6b8;
                goto selected;
            }
        }
        {
            bool hasSecond = false;
            if (profile != 0)
                hasSecond = profile->mi60C > 0;
            if (hasSecond)
                model = 0x653f6b6;
            else
                model = 0x653f6b7;
        }
    }
selected:
    RefObj* modelRef = 0;
    cPropertyManager* mgr = PropertyManager();
    char got = ((TFnCPPP)VSLOT(mgr, 0x2c))(mgr, (void*)0xc42e83f6, (void*)0x2be764e2,
                                           &modelRef);
    if (got != 0) {
        void* vecBase = 0;
        void* other = 0;
        char reserved = FUN_006a0ae0(modelRef, model, &vecBase, &other);
        if (reserved != 0) {
            int index = FUN_00a1ad10();
            float* sel = (float*)((char*)vecBase + index * 0xc);
            Vec3 v;
            v.x = sel[0];
            v.y = sel[1];
            v.z = sel[2];
            TribeHut* hut = this->mpHut368;
            ((TFnVP)VSLOT(&hut->mSpatial, 0x94))(&hut->mSpatial, &v);
            hut->RefreshModelProps();
            hut->mf14C = ((cReserveParams*)0x1581208)->GetHeight(index);
            float h = ((TFnF)VSLOT(&hut->mQueue, 0x58))(&hut->mQueue);
            hut->mQueue.SetHeight(h);
        }
    }
    this->FinishTask(0xc);
    if (modelRef != 0)
        ((TFnV)VSLOT(modelRef, 4))(modelRef);
}

// @ 0x00c99dc0
cTribe_s00c9_9140* __cdecl CreatePlayerTribe(int a, int b, int c, cSpeciesProfile_s00c9_9140* profile)
{
    if (profile == 0) {
        profile = GetSetting9_s00c9_9140()->GetAvatarProfile();
    }

    void* noun = NounManager_s00c9_9140()->CreateNoun(0x18c6d19);
    cTribe_s00c9_9140* tribe;
    if (noun == 0)
        tribe = 0;
    else
        tribe = (cTribe_s00c9_9140*)((TFnPI)VSLOT(noun, 0x0c))(noun, 0x4f396a66);

    NounManager_s00c9_9140()->AttachNoun(tribe);
    ((TFnVP)VSLOT(tribe, 0x48))(tribe, (void*)GetPlayerEmpireID());
    ((TFnV)VSLOT(tribe, 0xa8))(tribe);

    tribe->mpProfile18CC = profile;
    ((TFnVPPPP)VSLOT(tribe, 0x8c))(tribe, (void*)a, (void*)b, (void*)c, (void*)1);

    WString_s00c9_9140 name;
    name.mpBegin = (wchar_t*)0x01667bac;
    name.mpEnd = (wchar_t*)0x01667bac;
    name.mpCap = (wchar_t*)0x01667bae;
    profile->GetUiName(&name);
    tribe->mName230.Assign(name);

    unsigned key = 0xe;
    void* node = 0;
    void** it = tribe->mTree238.find(&key, &node);
    unsigned value = *(unsigned*)((char*)*it + 0x14);
    ((TFnVP)VSLOT(&tribe->mObj34, 0x00))(&tribe->mObj34, (void*)value);
    ((TFnVP)VSLOT(&tribe->mObj34, 0x08))(&tribe->mObj34, profile->mp52C);

    TerraformingManager()->InitTerrain();
    tribe->PromoteChieftain(0);
    tribe->InitDomesticatedAnimalsHerd();
    tribe->SetupTotemPole();

    void* hut = ((TFnP)VSLOT(tribe, 0xac))(tribe);
    if (hut != 0) {
        hut = ((TFnP)VSLOT(tribe, 0xac))(tribe);
        VtblObj* spatial = (VtblObj*)((char*)hut + 0x34);
        float height = ((TFnF)VSLOT(spatial, 0x74))(spatial) + 3.0f;
        Vec3 scratch;
        float* d = (float*)((TFnPP)VSLOT(spatial, 0x5c))(spatial, &scratch);
        Vec3 off;
        off.x = d[0] * height;
        off.y = d[1] * height;
        off.z = d[2] * height;
        float* p = (float*)((TFnP)VSLOT(spatial, 0x2c))(spatial);
        Vec3 pos;
        pos.x = p[0] + off.x;
        pos.y = p[1] + off.y;
        pos.z = p[2] + off.z;
        ReservationGrid* grid = &tribe->mRGrid558;
        grid->RemoveReservedByID(grid->GetReservedList(), (const void*)0x58cac6e);
        grid->AddReserved(grid->GetReservedList(), &pos, *(float*)0x0147b9f0,
                          (const void*)0x58cac6e);
    }

    if (((unsigned)name.mpCap - (unsigned)name.mpBegin & 0xfffffffe) > 2 &&
        name.mpBegin != 0)
        FUN_00f47380(name.mpBegin);

    return tribe;
}

// @ 0x00c9a000
TribeToolRef* __thiscall ToolVec::PushBackAt(TribeToolRef* pos, const TribeToolRef* val)
{
    int index = (int)(pos - this->mpBegin);
    if (pos == this->mpEnd && this->mpEnd != this->mpCap) {
        TribeToolRef* end = this->mpEnd;
        this->mpEnd = end + 1;
        if (end != 0) {
            end->mpVtbl = val->mpVtbl;
            end->mBody.CopyFrom(val->mBody);
        }
        return (TribeToolRef*)((char*)this->mpBegin + index * 0x60);
    }
    this->InsertAt(pos, val);
    return (TribeToolRef*)((char*)this->mpBegin + index * 0x60);
}

// @ 0x00c9a080
void HotSpotsShutdown()
{
    if (g_hotSpotTimer.IsRunning())
    {
        g_hotSpotTimer.FUN_00bc3170();
        g_hotSpotTimer.Stop();
    }
    cHotSpotNode* begin = g_hotSpots.mpBegin;
    cHotSpotNode* end = g_hotSpots.mpEnd;
    while (begin != end)
    {
        HotSpotGridRelease(&begin->mPosition.z);
        ++begin;
    }
    begin = g_hotSpots.mpBegin;
    end = g_hotSpots.mpEnd;
    g_hotSpots.FreeRange(begin, end);
    g_hotSpots.mpEndRaw += ((char*)end - (char*)begin) / 0x60 * 0x60;
}

// @ 0x00c9a100
void cTribe_s00c9_a080::Init(const Vector3_s00c9_a080* pos, int numMembers, int foodAmount, bool flag)
{
    SetOwner(0);
    mIdentity.Init();
    mZoningRadius = g_ZoningRadius;
    PlanetModel_s00c9_a080()->mpGrid->GetMapSet()->GetHeightAt(pos);
    Vector3_s00c9_a080 surfPos;
    PlanetModel_s00c9_a080()->DirectionToSurfacePosition(&surfPos, pos);
    cSpatialPart_s00c9_a080* sp = &mSpatial;
    sp->SetPosition(surfPos);
    Quaternion orient;
    if (sp->IsEditor()) {
        const Vector3_s00c9_a080* w = GetClosestWater();
        if (w->x == kInvalidPos.x && w->y == kInvalidPos.y && w->z == kInvalidPos.z) {
            orient = PlanetModel_s00c9_a080()->BuildSurfaceOrientation(surfPos);
        } else {
            const Vector3_s00c9_a080& c = sp->GetPosition();
            Vector3_s00c9_a080 d(w->x - c.x, w->y - c.y, w->z - c.z);
            float inv = 1.0f / sqrtf(d.x * d.x + d.y * d.y + d.z * d.z + 1e-8f);
            Vector3_s00c9_a080 dir(d.x * inv, d.y * inv, d.z * inv);
            orient = PlanetModel_s00c9_a080()->BuildSurfaceOrientation(surfPos, dir);
            mbCheckedForWater = 0;
        }
    } else {
        orient = PlanetModel_s00c9_a080()->BuildSurfaceOrientation(surfPos);
    }
    sp->SetOrientation(orient);
    UpdateRoboTribeness();
    if (GetPoliticalID() == -1)
        funcA8();
    mpHut.Assign((cTribeHut*)NounManager_s00c9_a080()->CreateNoun(0x1e4daae));
    {
        cTribeHut* hut = mpHut.p;
        hut->mPart.SetModelWorld(GonzagoModelWorld());
        hut->SetTribe(this);
        hut = mpHut.p;
        hut->mPart.SetOrientation(&sp->GetOrientation());
        hut = mpHut.p;
        hut->mPart.SetPosition(&sp->GetPosition());
        (void)sp->GetPosition();
    }
    PropManager* pm = PropertyManager_s00c9_a080();
    if (mpPropList.p) {
        PropertyList* old = mpPropList.p;
        mpPropList.p = 0;
        old->Release();
    }
    pm->GetPropertyList(0x535dc193, 0x2be764e2, mpPropList);
    SetupChatAreas();
    UpdateToolPositions();
    mFlag6c = 1;
    float scale = g_Species.GetRadius(mpSpecies0);
    float base;
    Property_s00c9_a080* prop;
    if (mpPropList.p && mpPropList.p->GetProperty(0x1fb2b4e, prop))
        base = *prop->GetValueFloat();
    else
        base = 1.5f;
    float r = base * scale * 2.0f;
    mRSquareSize = r;
    mRGrid.ComputeGridResolution(r, 0.0f);
    mPopulationTimer.Restart();
    Vector3_s00c9_a080 center = mCenter;
    {
        cTribeFoodMat* fm = (cTribeFoodMat*)0;
        IRefCounted* n = NounManager_s00c9_a080()->CreateNoun(0x629bafe);
        if (n) fm = (cTribeFoodMat*)((cTribeNoun*)n)->Cast(0x629baec);
        mpFoodMat.Assign(fm);
    }
    mpFoodMat.p->SetTribe(this);
    mpFoodMat.p->mPart.SetPosition(&center);
    {
        Vector3_s00c9_a080 nd = -mpHut.p->mPart.GetDirection();
        Quaternion q = PlanetModel_s00c9_a080()->BuildSurfaceOrientation(center, nd);
        mpFoodMat.p->mPart.SetOrientation(&q);
    }
    ResetToolLayout();
    ResetDefaultToolPlacement(10);
    if (!sp->IsEditor()) {
        int n = mTribeArchetype ? GetMaxPopulation() : numMembers;
        FUN_00ff03b0(FUN_00c00aa0(n));
    }
    ChooseNewHutModel();
    ReserveToolsSlots(1);
    if (!sp->IsEditor()) {
        int n = mTribeArchetype ? GetMaxPopulation() : numMembers;
        FUN_00ff03b0(FUN_00c00aa0(n));
        UpgradeHut();
    }
    UpdateModel();
    if (flag)
        FUN_00c91700();
    if (numMembers == 0x29a)
        numMembers = g_Species.GetPopulation();
    UpdateRoboTribeness();
    if (mbRoboTribe) {
        mRoboPopulationCount = numMembers;
    } else {
        int have = mSelectableEnd - mSelectableBegin;
        if (have < numMembers) {
            int n = numMembers - have;
            do {
                cCitizen_s00c9_a080* c;
                if (mbRoboTribe && !mbVisualized) {
                    c = 0;
                } else {
                    c = (cCitizen_s00c9_a080*)NounManager_s00c9_a080()->CreateNoun(0x18eb4b7);
                    c->Init(0, this, 1, &kInvalidPos);
                    ((cTimerLike*)((char*)c + 0x5a8))->SetEnabled(1);
                    BehaviorManager()->Register((char*)c + 0x58);
                }
                AddExistingCreatureInternal(c, 0);
            } while (--n);
        }
    }
    if (foodAmount == 0x29a)
        foodAmount = g_Species.GetFood();
    int mode;
    cSpecies* spc = mpSpecies0;
    if (spc && HasA(spc) && !HasB(spc)) mode = 1;
    else if (spc && HasB(spc) && !HasA(spc)) mode = 2;
    else mode = 3;
    float f = (float)foodAmount;
    mBundle.Init(this, 8, 1000.0f, f * 0.85f, mode);
    BundleManager()->Add(f * 0.15f, &mBundle, 4);
    MsgTribe msg(this);
    MessageServer()->Post(msg.mID, &msg, 0);
}

// @ 0x00c9a960
bool cTribe_s00c9_a080::CheckToolsTimeout()
{
    if (mToolsTimer.IsRunning())
    {
        if (mToolsTimer.GetElapsedTime() > 1000)
        {
            ReserveToolsSlots(false);
            mToolsTimer.FUN_00bc3170();
            return true;
        }
    }
    return false;
}

// @ 0x00c9af30
void GetHotSpotValues(const Vector3_s00c9_a080* pos, float* out0c, float* out10, uint8_t* outFlag)
{
    *out0c = g_hotSpots[&pos]->mField0c;
    *out10 = g_hotSpots[&pos]->mField10;
    *outFlag = g_hotSpots[&pos]->mField39;
}

// @ 0x00c9af80
Vector3_s00c9_a080* GetHotSpotPosition(Vector3_s00c9_a080* out, const Vector3_s00c9_a080* pos)
{
    cHotSpotNode* node = g_hotSpots[&pos];
    out->x = node->mPosition.x;
    out->y = node->mPosition.y;
    out->z = node->mPosition.z;
    return out;
}

// @ 0x00c9afb0
namespace SP {
uint32_t cTribe_s00c9_afb0::SetupHotSpot(const Vector3_s00c9_afb0& dir, int force)
{
    (void)force;
    float x = dir.x, y = dir.y, z = dir.z;
    float ax = (float)fabs(x), ay = (float)fabs(y), az = (float)fabs(z);
    CubeCoord coord;
    if (ax > az || ay > az) {
        if (ax > ay) {
            coord.u = (y / x + 1.0f) * 0.5f;
            coord.v = (z / ax + 1.0f) * 0.5f;
            coord.face = 2;
            if (x < 0.0f) coord.face = 3;
        } else {
            coord.u = (z / y + 1.0f) * 0.5f;
            coord.v = (x / ay + 1.0f) * 0.5f;
            if (y < 0.0f) coord.face = 5;
            else coord.face = 4;
        }
    } else {
        coord.u = (x / z + 1.0f) * 0.5f;
        coord.v = (y / az + 1.0f) * 0.5f;
        if (z < 0.0f) coord.face = 1;
        else coord.face = 0;
    }

    CubeIndex idx;
    CoordToIndex(&idx, 0x80, &coord);
    int xStart = idx.x - 4, xEnd = idx.x + 4;
    int yStart = idx.y - 4, yEnd = idx.y + 4;

    HotSpot spot;
    bool bFound = false;
    bool bWater = false;
    uint32_t result = 0xffffffff;
    Vector3_s00c9_afb0 d;
    uint64_t now = GameTimeManager()->GetTime();

    for (int i = xStart; i < xEnd; ++i) {
        if (bFound) goto done;
        for (int j = yStart; j < yEnd; ++j) {
            if (bFound) break;
            int face = idx.face, wx = i, wy = j;
            WrapCubeFace(0x80, &face, &wx, &wy, 0, 0);
            CubeIndex cell;
            cell.x = wx; cell.y = wy; cell.face = face;
            uint32_t key = (((wx & 0xffff8fff) + (face << 13)) << 16) + wy;
            HotSpotElem* it = HotSpotLowerBound_s00c9_afb0(g_HotSpots.mpBegin, g_HotSpots.mpEnd, &key, g_HotSpotsFlag);
            if (it != g_HotSpots.mpEnd && key >= it->key) {
                bFound = true;
                result = key;
                d = ((HotSpotMapRef*)&g_HotSpots)->at(&key)->mPos;
                ((HotSpotMapRef*)&g_HotSpots)->at(&key)->mStartTime = now;
            } else {
                CubeCoord uv;
                IndexToCoord(&uv, 0x80, &cell);
                float up = (float)((double)uv.u * 2.0 - 1.0);
                float vp = (float)((double)uv.v * 2.0 - 1.0);
                float k = (float)(1.0 / sqrt((double)(vp * vp + up * up) + 1.0));
                float kn = (uv.face & 1) ? -k : k;
                const uint8_t* axes = kFaceAxes[uv.face >> 1];
                float* dv = &d.x;
                dv[axes[0]] = kn * up;
                dv[axes[1]] = k * vp;
                dv[axes[2]] = kn;
                if (PlanetModel_s00c9_afb0()->ClassifyPoint(&d) == 3) {
                    spot.mCube = cell;
                    spot.mPos = PlanetModel_s00c9_afb0()->SurfacePoint(d);
                    bWater = true;
                }
            }
        }
    }
    if (!bFound && bWater) {
        float food = ReadFloatProperty(0xd1e9eaf0, 15.0f);
        float resupply = ReadFloatProperty(0x3c8e6fb2, 0.05f);
        spot.mbActive = true;
        float v = (food > 1.0f) ? food : 1.0f;
        spot.mFood = v;
        spot.mMaxFood = v;
        spot.mResupply = resupply;
        result = (((spot.mCube.x & 0xffff8fff) + (spot.mCube.face << 13)) << 16) + spot.mCube.y;
        spot.mStartTime = now;
        ((HotSpotMapRef*)&g_HotSpots)->at(&result)->Assign(spot);
        ((HotSpotMapRef*)&g_HotSpots)->at(&result)->SetupArea(spot.mPos, 10.0f);
    }
done:
    if (!g_FishTimer.IsRunning()) {
        g_FishTimer.Start();
        g_NextFishTime = 240000;
    } else {
        g_NextFishTime = g_FishTimer.GetElapsedTime() + 240000;
    }
    return result;
}
}  // namespace SP

// @ 0x00c9b6d0
void __cdecl FUN_00c9b6d0(SP::cTribe_s00c9_afb0* self)
{
    if (!self)
        return;
    if (!g_FishTimer.IsRunning())
        return;
    const Vector3_s00c9_afb0* p = self->GetClosestWater();
    if (p->x != g_FishTarget.x || p->y != g_FishTarget.y || p->z != g_FishTarget.z)
        SP::cTribe_s00c9_afb0::SetupHotSpot(*p, 1);
}

// @ 0x00c9bd50
void SP::cTribe_s00c9_afb0::HandleEvent(void* a)
{
    func54h(a);
    ((TribeObj*)mpTribeD8)->Notify(0xd);
}

// @ 0x00c9be50
void cSpatialObject_s00c9_afb0::OnExtentsChanged(void* a, float b)
{
    SetLocalExtents(a, b);
    RefCounted* outer = (RefCounted*)((char*)this - 0x34);
    void* r = outer->v58();
    if (r)
        ((TribeObj*)r)->Notify(0xc);
}

// @ 0x013551e0
namespace Simulator {
void InitTribeAttributes()
{
    Attribute a;
    ATTR("mbMotiveCheatOn", 0x02fab837, 0x264, DefaultOffset,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 0)
    ATTR("mbRoboTribe", 0x02fab839, 0x334, DefaultOffset,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 1)
    ATTR("mbVisualized", 0x0510d72a, 0x33c, DefaultOffset,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 2)
    ATTR("mUpgradeLevel", 0x02fab83e, 0x32c, DefaultOffset,
         Read4<uint32_t>, Write_00572840, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0, 3)
    ATTR("mRoboPopulationCount", 0x02fab83f, 0x338, DefaultOffset,
         Read4<uint32_t>, Write_00572840, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0, 4)
    ATTR("mSpeciesKeys", 0x041171cc, 0x1904, DefaultOffset,
         Read_00c95780, Write_00c6adc0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<ResourceKeyVector>, ToXml_00c6c4e0, 5)
    ATTR("mpHut", 0x02fab843, 0x368, DefaultOffset,
         Read_00c92a00, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050, 6)
    ATTR("mTribeMembers", 0x02fab844, 0x340, DefaultOffset,
         Read_00ce26c0, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390, 7)
    ATTR("mSelectableMembers", 0x02fab845, 0x354, DefaultOffset,
         Read_00bf50f0, Write_00c43790, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390, 8)
    ATTR("mTools", 0x02fab847, 0x36c, DefaultOffset,
         Read_00c95850, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390, 9)
    ATTR("mSocialTools", 0x34474cfa, 0x380, DefaultOffset,
         Read_00c95850, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390, 10)
    ATTR("mZoningRadius", 0x02fab849, 0x330, DefaultOffset,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 11)
    ATTR("mRSquareSize", 0x02fab854, 0x268, DefaultOffset,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 12)
    ATTR("mbCheckedForWater", 0x05107b10, 0x300, DefaultOffset,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 13)
    ATTR("mbCheckedForForests", 0x05108592, 0x301, DefaultOffset,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 14)
    ATTR("mClosestWater", 0x05107b15, 0x304, DefaultOffset,
         Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, AlwaysValid<Vector3>, ToXml_00acbba0, 15)
    ATTR("mhFootprint", 0xc807312a, 0x19d4, DefaultOffset,
         Read4<uint32_t>, Write_00572840, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0, 16)
    ATTR("mpDomesticatedAnimalsHerd", 0x051cc74e, 0x19cc, DefaultOffset,
         Read_00b20540, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050, 17)
    ATTR("mpDomesticatedAnimalsPen", 0x053d8e28, 0x19c4, DefaultOffset,
         Read_00bed160, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050, 18)
    ATTR("mpEggPen", 0x05b9a1a7, 0x19c8, DefaultOffset,
         Read_00bed160, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050, 19)
    ATTR("mEggPenFoodValue", 0x05b9a1ae, 0x2c0, DefaultOffset,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 20)
    ATTR("mpTotemPole", 0x055cef22, 0x19d0, DefaultOffset,
         Read_00c92a30, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050, 21)
    ATTR("mClosestForests", 0x051089f5, 0x314, DefaultOffset,
         Read_00c41210, Write_00c40e80, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<ForestList>, ToXml_00c41b00, 22)
    ATTR("mpFoodMat", 0x062daeed, 0x260, DefaultOffset,
         Read_00c92a60, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050, 23)
    ATTR("mTribeArchetype", 0x02fab853, 0x550, DefaultOffset,
         Read4<uint32_t>, Write_00572840, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0, 24)
    ATTR("mPopulationTimer", 0x056591e5, 0x510, DefaultOffset,
         Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae3310, ToXml_00ac8050, 25)
    ATTR("mTimer", 0x056591e6, 0x530, DefaultOffset,
         Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae3310, ToXml_00ac8050, 26)
    ATTR("mVignetteTimer", 0x056591e7, 0x270, DefaultOffset,
         Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae3310, ToXml_00ac8050, 27)
    ATTR("mInitialRelationship", 0x05ecc770, 0x2c4, DefaultOffset,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 28)
    ATTR("mPurchasedTools", 0x06612ff8, 0x19d8, DefaultOffset,
         Read4<uint32_t>, Write_00572840, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0, 29)
    ATTR("mGoodyPopped", 0x0674d16a, 0x557, DefaultOffset,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 30)
    ATTR("mChieftainRespawnTimer", 0x0682e28e, 0x2c8, DefaultOffset,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 31)
    ATTR("mGiftRelationshipDecayTimer", 0x95701374, 0x2cc, DefaultOffset,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 32)
    ATTR("cTribe::sFishHotSpots", 0x06a7f44e, cTribe_sFishHotSpots, StaticOffset,
         Read_00c9ab30, Write_00c92a90, ReadText_00c2e4e0, WriteText_00694bd0, Validate_00c9ad90, 0, 33)
    ATTR("cTribe::sFishTimer", 0x06c250f5, cTribe_sFishTimer, StaticOffset,
         Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae3310, 0, 34)
    ATTR("cTribe::sFishEndTime", 0x06c25111, cTribe_sFishEndTime, StaticOffset,
         Read_00aff840, Write_00aff870, ReadText_00692fd0, WriteText_00694ec0, AlwaysValid<int64_t>, 0, 35)
}
}  // namespace Simulator
