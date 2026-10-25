// src/game/SPGonzago/SPSimulatorPlayerUFO.cpp -- migrated from slice(s) s01000740, s00fff8e0, s00ffe130, s00ffd220, s00ffb180 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSimulatorPlayerUFO.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cEmpire.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cPlanetRecord.h"
#include "SP/cRelationshipManager.h"
#include "SP/cSPTimer.h"
#include "SP/cCity.h"
#include "SP/cStarManager.h"
#include "SP/cTerrainSphere.h"
#include "SP/cVarListSerializer.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cSPGameDataUFO.h"
#include "SP/cCivData.h"
#include "SP/cSpatialObject.h"
#include <math.h>
#include "SP/cGonzagoTimer.h"
#include "SP/cMWModel.h"
#include <stddef.h>
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern char g_nounListUFO[];           // 0x018ebadc
extern char     g_varListUFO[];        // 0x015b6378
extern void*    g_ufoListenerVtable[]; // 0x014950d0

// ---- items of slice s00ffb180 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_nounListUFO[];           // 0x018ebadc
extern char     g_varListUFO[];        // 0x015b6378
extern void*    g_ufoListenerVtable[]; // 0x014950d0
class cOutStream;
class cSimGameData;
class cCityHall;
class tEffectHandle;
class tUFOData;
struct tPtrVector {
    void** mpBegin;                 // +0x00
    void** mpEnd;                   // +0x04
};
struct tGameDataList {
    void*      mPad00;              // +0x00
    tPtrVector mData;               // +0x04
    void*      mPad0c;              // +0x0c
    void*      mPad10;              // +0x10
};
class cGameNounManager {
public:
    uint8_t mPad00[0x54];           // +0x000
    void*   mpAvatar;               // +0x054

    tGameDataList* GetGameDataVector(void* pF1, void* pF2, void* pF3, void* pF4, void* pAlloc); // 0x00b21340
    void*          GetCurrentTerrainSphere();                                                  // 0x00f67d90
    tUFOData*      CreateNoun(void* pNoun);                                                    // 0x00b20c60
    void*          GetAvatar();                                                                // 0x00b1fdb0
};
cGameNounManager* __cdecl NounManager();        // 0x00b3d300
class tRefObject {
public:
    virtual void AddRef();                      // +0x00
    virtual void Release();                     // +0x04
};
void*          __cdecl GetPlayerEmpire();   // 0x01021300
class tCityObj {                    // a polymorphic sub-object embedded in a noun
public:
    virtual void  v00();            // +0x00
    virtual void  v04();            // +0x04
    virtual void  v08();            // +0x08
    virtual void  v0c();            // +0x0c
    virtual void  v10();            // +0x10
    virtual void  v14();            // +0x14
    virtual void  v18();            // +0x18
    virtual void  v1c();            // +0x1c
    virtual void  v20();            // +0x20
    virtual void  v24();            // +0x24
    virtual void  v28();            // +0x28
    virtual void* v2c();            // +0x2c
    virtual void* v30();            // +0x30

    int32_t FUN_008e7f80();         // 0x008e7f80
};
class tCityInner {
public:
    uint8_t  mPad00[0x5fc];         // +0x000
    uint32_t mn5fc;                 // +0x5fc visibility/flag word
};
class cCityHall {
public:
    uint8_t    mPad00[0x120];       // +0x000
    tCityObj   mObj120;             // +0x120
    uint8_t    mPad124[0x38];       // +0x124
    int32_t    mn15c;               // +0x15c owning empire
};
class cSimGameData : public tRefObject {    // vptr +0x00, AddRef +0x00, Release +0x04
public:
    virtual void    v08();          // +0x08
    virtual void    v0c();          // +0x0c
    virtual void    v10();          // +0x10
    virtual void    v14();          // +0x14
    virtual void    v18();          // +0x18
    virtual void    v1c();          // +0x1c
    virtual void    v20();          // +0x20
    virtual void    v24();          // +0x24
    virtual void    v28();          // +0x28
    virtual void    v2c();          // +0x2c
    virtual void    v30();          // +0x30
    virtual void    v34();          // +0x34
    virtual void    v38();          // +0x38
    virtual void    v3c();          // +0x3c
    virtual void    v40();          // +0x40
    virtual void    v44();          // +0x44
    virtual void    v48();          // +0x48
    virtual int32_t v4c();          // +0x4c owning empire

    uint8_t        mPad04[0x30];    // +0x004
    tCityObj       mObj34;          // +0x034
    uint8_t        mPad38[0xe8];    // +0x038
    tCityObj       mObj120;         // +0x120
    uint8_t        mPad124[0xfc];   // +0x124
    float          mf220;           // +0x220
    uint8_t        mPad224[0x48c];  // +0x224
    int32_t        mn6b0;           // +0x6b0
    uint8_t        mPad6b4[0x14];   // +0x6b4
    tCityInner*    mp6c8;           // +0x6c8
    uint8_t        mPad6cc[0x48];   // +0x6cc
    int32_t        mn714;           // +0x714 noun type

    cCityHall* GetCityHall();                               // 0x00bd9b40
    bool       FUN_00c38990(int32_t nIndex);                // 0x00c38990
    void       FUN_00c38740(float fA, double fB);           // 0x00c38740
    void       FUN_00bdbf10();                              // 0x00bdbf10
};
class tEffectHandle {
public:
    virtual void v00();             // +0x00
    virtual void Release();         // +0x04
    virtual void v08(int32_t nValue);   // +0x08
    virtual void v0c(int32_t nValue);   // +0x0c
};
class tEffectsManager {
public:
    virtual void v00();             // +0x00
    virtual void v04();             // +0x04
    virtual void v08();             // +0x08
    virtual void v0c();             // +0x0c
    virtual void v10();             // +0x10
    virtual void v14();             // +0x14
    virtual void v18();             // +0x18
    virtual void v1c();             // +0x1c
    virtual void v20();             // +0x20
    virtual void v24();             // +0x24
    virtual void v28();             // +0x28
    virtual bool v2c(uint32_t nKey, int32_t nFlags, tEffectHandle** ppEffect);   // +0x2c
};
class cEffects {
public:
    void Tick(float fSeconds);      // 0x00ebe3e0
};
class cSPTimer {
public:
    uint64_t GetElapsedTime();      // 0x00bc3190
    void     Restart();             // 0x00bc3130
    uint32_t mPad00[8];             // +0x00
};
class tMessageServer {
public:
    virtual void v00();             // +0x00
    virtual void v04();             // +0x04
    virtual void v08();             // +0x08
    virtual void v0c();             // +0x0c
    virtual void v10();             // +0x10
    virtual void v14(uint32_t nKey, void* pPayload, int32_t nFlags);    // +0x14
    virtual void v18(uint32_t nKey, int32_t nA, int32_t nB, int32_t nC); // +0x18
    virtual void v1c();             // +0x1c
    virtual void v20();             // +0x20
    virtual void v24(void* pListener, uint32_t nKey);                   // +0x24
    virtual void v28();             // +0x28
    virtual void v2c();             // +0x2c
    virtual void v30();             // +0x30
    virtual void v34();             // +0x34
    virtual void v38();             // +0x38
    virtual void v3c();             // +0x3c
    virtual void v40();             // +0x40
    virtual void v44();             // +0x44
    virtual void v48();             // +0x48
    virtual void v4c();             // +0x4c
    virtual void v50(void* pListener);  // +0x50
};
namespace EA {
namespace Messaging {
 tMessageServer* __cdecl GetServer(); 
}  // 0x00883860
}
tMessageServer* __cdecl SimTicker();                // 0x00b3d330
class tUFOData : public tRefObject {        // vptr +0x00
public:
    virtual void  v08();            // +0x08
    virtual void* v0c(uint32_t nSub);   // +0x0c

    void Init(void* pA, void* pB);  // 0x00c3e0b0
};
class cEmpireKey {
public:
    uint32_t mn00;                  // +0x00
    void SetUFOKey(void** ppKey);   // 0x00c35740
};
class tMessageThing {
public:
    void* FUN_01067e60();           // 0x01067e60
    void  FUN_01065d20();           // 0x01065d20
};
tMessageThing* __cdecl FUN_010666a0();  // 0x010666a0
class cTerrainSphere {
public:
    void FUN_00c77bf0(uint32_t nKey);   // 0x00c77bf0
    bool Check();                       // 0x00c75650
};
class tEffectsGlobal {
public:
    uint8_t       mPad00[0x4c];     // +0x000
    tEffectsManager* mp4c;          // +0x04c
    bool FUN_0067c8c0(uint32_t nKey, int32_t nValue);   // 0x0067c8c0
};
tEffectsGlobal* __cdecl FUN_0067cac0();     // 0x0067cac0
class tRenderConsumer {
public:
    virtual void v00();                             // +0x00
    virtual void v04();                             // +0x04
    virtual void v08();                             // +0x08
    virtual void v0c();                             // +0x0c
    virtual void v10(uint32_t nTimeLo, uint32_t nTimeHi, void* pValue);   // +0x10
};
class cSPSimPlanetHighLOD {
public:
    uint8_t      mPad00[0x28];      // +0x000
    tRenderConsumer* mp28;          // +0x028 render consumer (v10)
    void*        mp2c;              // +0x02c drawn UFO / message-server handle
    void*        mp30;              // +0x030 message listener
    void*        mp34;              // +0x034 listener vtable
    int32_t      mn38;              // +0x038
    int32_t      mn3c;              // +0x03c
    tUFOData*    mp40;              // +0x040 UFO game data
    uint8_t      mPad44[0x3c];      // +0x044
    cSPTimer     mTimer80;          // +0x080
    int32_t      mnA0;              // +0x0a0
    uint8_t      mPadA4[0xb4];      // +0x0a4
    bool         mb158;             // +0x158
    uint8_t      mPad159[0x57];     // +0x159
    cEffects*    mp1b0;             // +0x1b0
    uint8_t      mPad1b4[0x04];     // +0x1b4
    int32_t      mn1b8;             // +0x1b8 threshold
    tEffectHandle* mp1bc;           // +0x1bc terrain effect
    uint8_t      mPad1c0[0x1c];     // +0x1c0
    tEffectHandle* mp1dc;           // +0x1dc
    bool         mb1e0;             // +0x1e0

    void FUN_00ffb180();                                            // 0x00ffb180
    void SolarSystemUpdateNPC_UFOs(uint32_t nElapsedMS);            // 0x00ffb270
    void CheckForCityDestruction();                                 // 0x00ffb830
    void OnTick(uint32_t nTimeLo, uint32_t nTimeHi);                // 0x00ffbb20
    void Init();                                                    // 0x00ffbf60
    bool FUN_00ffbfe0();                                            // 0x00ffbfe0
    void FUN_00ffc030();                                            // 0x00ffc030
    bool CheckAndReplaceData(void* pKey, void* pB, void* pC);       // 0x00ffc160
    void CreateReplacement();                                       // 0x00ffa780
    void FUN_00ff8ad0();                                            // 0x00ff8ad0
    void FUN_00ffabc0();                                            // 0x00ffabc0
    void FUN_00ffaf20(uint32_t nTimeLo);                            // 0x00ffaf20
    void FUN_00ffa690();                                            // 0x00ffa690
    void FUN_00ffab60();                                            // 0x00ffab60
    void FUN_00ff7530(uint32_t nTimeLo, uint32_t nTimeHi);          // 0x00ff7530
    void FUN_00ffa900(cSimGameData* pNoun, int32_t nEmpire);        // 0x00ffa900
};
class cSPSimulatorPlayerUFO {
public:
    bool Write(cOutStream* pStream);    // 0x00ffbe60
};
class tIStream {
public:
    virtual void v00();                                     // +0x00
};
class tStreamInner {
public:
    virtual void v00();                                     // +0x00
    virtual void v04();                                     // +0x04
    virtual void v08();                                     // +0x08
    virtual void v0c();                                     // +0x0c
    virtual void v10();                                     // +0x10
    virtual void v14();                                     // +0x14
    virtual tIStream* v18();                                // +0x18
};
class cOutStream {
public:
    virtual void v00();                                     // +0x00
    virtual void v04();                                     // +0x04
    virtual void v08();                                     // +0x08
    virtual void v0c();                                     // +0x0c
    virtual void v10();                                     // +0x10
    virtual void v14();                                     // +0x14
    virtual void v18();                                     // +0x18
    virtual void v1c();                                     // +0x1c
    virtual tStreamInner* v20();                            // +0x20
};
class cVarListSerializer {
public:
    uint32_t mPad00[0x05];                                          // +0x00
    void Construct(void* pOwner, void* pVarList, int32_t nLine);    // 0x00692f90
    bool Serialize(cOutStream* pStream);                            // 0x00692900
};
struct tVarListFrame {
    uint32_t            mnValue;            // +0x000
    cVarListSerializer  mSerializer;        // +0x004
    uint32_t            mPad18[0x280];      // +0x018
};
bool __cdecl EA_IO_WriteUint32(tIStream* pStream, const uint32_t* pValue, int32_t nCount, int32_t nFlags); // 0x0093aa70
// ---- items of slice s00ffb180 end

// ---- items of slice s00ffd220 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*        __cdecl FUN_00b3d230(void);   // 0x00b3d230
extern "C" void         __cdecl FUN_010424c0(void* pDst, const void* pSrc); // 0x010424c0
extern "C" void*        __cdecl FUN_0059aed0(void* pOut, const void* pV, const void* pQ); // 0x0059aed0
extern "C" void*        __cdecl QuaternionFromFacingAndUp(void* pOut, const void* pFacing, const void* pUp); // 0x0069b600
extern "C" float        __cdecl sqrtf(float);         // CRT intrinsic -> fsqrt
extern const float kDirEps;          // 0x014950e4
extern const float kNormEps;         // 0x013ec4b8
extern const float kFwdX;            // 0x016dc0c8
extern const float kFwdY;            // 0x016dc0cc
extern const float kFwdZ;            // 0x016dc0d0
extern const float kBaseX;           // 0x016dba18
extern const float kBaseY;           // 0x016dba1c
extern const float kBaseZ;           // 0x016dba20
extern "C" void*        __cdecl FUN_01021260(void);   // 0x01021260 GetActivePlanet
extern "C" void*        __cdecl FUN_01021240(void);   // 0x01021240 GetPlayerCiv
extern "C" void*        __cdecl FUN_01021300(void);   // 0x01021300 GetPlayerEmpire
extern "C" void*        __cdecl FUN_0102f810(void);   // 0x0102f810
extern "C" void*        __cdecl SpaceGameGet(void);   // 0x01002bd0
extern "C" void*        __cdecl App(void);            // 0x0067dd10
extern "C" void*        __cdecl EffectsManagerPtr(void); // 0x0067ddd0
extern "C" void*        __cdecl MessageServer(void);  // 0x0067dcc0
extern "C" void*        __cdecl GetSpaceCombatTuning(void); // 0x01029940
extern "C" bool         __cdecl FUN_0102af80(int uId, void* pObj); // 0x0102af80
extern "C" uint32_t     __cdecl FUN_00932e80(const char* s, uint32_t seed, int flag); // 0x00932e80 FNV
extern const float kRealOne;         // 0x01485720 1.0f
extern const float kRealZero;        // 0x01485378 0.0f
extern const float kFive;            // 0x01486110
extern const float kThousand;        // 0x013ec5b4
extern const float kHundred;         // 0x013ec4d0
extern const float kRefMatrix[9];    // 0x016dc018 Matrix3 source
extern const float kMsgX;            // 0x016dc03c
extern const float kMsgY;            // 0x016dc040
extern const float kMsgZ;            // 0x016dc044
extern uint32_t kInterplanetaryDrive; // 0x016dba90 interplanetary-drive tool key
extern uint32_t kHealthUpgrade10;  // 0x016dbebc
extern uint32_t kHealthUpgrade9;   // 0x016dbeb0
extern uint32_t kHealthUpgrade8;   // 0x016dbea4
extern uint32_t kHealthUpgrade7;   // 0x016dbe98
extern uint32_t kHealthUpgrade6;   // 0x016dbe8c
extern uint32_t kHealthUpgrade5;   // 0x016dbe80
extern uint32_t kHealthUpgrade4;   // 0x016dbe74
extern uint32_t kHealthUpgrade3;   // 0x016dbe68
extern uint32_t kHealthUpgrade2;   // 0x016dbe5c
extern uint32_t kHealthUpgrade1;   // 0x016dbe50
extern uint32_t kEnergyUpgrade10;  // 0x016dbe14
extern uint32_t kEnergyUpgrade9;   // 0x016dbe08
extern uint32_t kEnergyUpgrade8;   // 0x016dbdfc
extern uint32_t kEnergyUpgrade7;   // 0x016dbdf0
extern uint32_t kEnergyUpgrade6;   // 0x016dbde4
extern uint32_t kEnergyUpgrade5;   // 0x016dbdd8
extern uint32_t kEnergyUpgrade4;   // 0x016dbdcc
extern uint32_t kEnergyUpgrade3;   // 0x016dbdc0
extern uint32_t kEnergyUpgrade2;   // 0x016dbdb4
extern uint32_t kEnergyUpgrade1;   // 0x016dbda8
extern char g_szReticleGotoScreen[]; // 0x01495114 "UI_common_reticle_goto_screen"
extern "C" void*        __cdecl NounManager_s00ff_d220(void);    // 0x00b3d300
class tHost {
public:
    void*  __thiscall FUN_00c71e30();                              // 0x00c71e30
    void*  __thiscall FUN_00a1ad60();                              // 0x00a1ad60 GetPlayerInventory
    int    __thiscall FUN_0102f8d0(void* pA, void* pOut);          // 0x0102f8d0
    void   __thiscall FUN_00c31a00(int n);                         // 0x00c31a00
    float  __thiscall FUN_00c389f0(float f);                       // 0x00c389f0
    float  __thiscall FUN_00c75c30(uint32_t key);                  // 0x00c75c30
    float  __thiscall FUN_01005c60(int n);                         // 0x01005c60
    float  __thiscall FUN_0104be30();                              // 0x0104be30
    float  __thiscall FUN_00ce6930();                              // 0x00ce6930
    float* __thiscall FUN_0041ea70();                              // 0x0041ea70 Property::GetFloat
    void*  __thiscall FUN_005c65e0();                              // 0x005c65e0 cCivData::GetCities
    void*  __thiscall FUN_00f67d90();                              // 0x00f67d90 GetCurrentTerrainSphere
    void   __thiscall FUN_00c77bf0(uint32_t key);                  // 0x00c77bf0
    void   __thiscall FUN_00c3c190(void* pPlanet);                 // 0x00c3c190 SetDestination
    void   __thiscall FUN_00bc3130();                              // 0x00bc3130 cSPTimer::Restart
    void   __thiscall FUN_00bc3170();                              // 0x00bc3170
    void   __thiscall FUN_00b5cde0(uint32_t key);                  // 0x00b5cde0
    void   __thiscall FUN_01017000();                              // 0x01017000
    void   __thiscall FUN_010170e0();                              // 0x010170e0
    void*  __thiscall FUN_00bce5c0();                              // 0x00bce5c0
    void   __thiscall FUN_00ffc350(const float* pV, int a, int b, int c, int d); // 0x00ffc350
    void   __thiscall FUN_00ffc6d0();                              // 0x00ffc6d0
    float  __thiscall FUN_00ffc7f0(void* pCities);                 // 0x00ffc7f0
    void   __thiscall FUN_00434040();                              // 0x00434040 XformMsg::XformMsg
    void   __thiscall FUN_0041cb40(const void* pSrc);              // 0x0041cb40 Matrix3::Assign
};
#define VFN(obj, off) (*(void**)((char*)(*(void**)obj) + (off)))
class cSPGameDataUFO {
public:
    uint8_t mPad000[0x5ec];   // +0x000
    float   mf5ec;            // +0x5ec
    uint8_t mPad5f0[0x04];    // +0x5f0
    float   mf5f4;            // +0x5f4 facing x
    float   mf5f8;            // +0x5f8 facing y
    float   mf5fc;            // +0x5fc facing z
    uint8_t mPad600[0x04];    // +0x600
    float   mf604;            // +0x604
    uint8_t mPad608[0x04];    // +0x608
    float   mf60c;            // +0x60c
    float   mf610;            // +0x610
    float   mf614;            // +0x614
    uint8_t mPad618[0x30];    // +0x618
    uint8_t mTimer648[0x1c];  // +0x648 cSPTimer
    uint8_t mPad664[0x04];    // +0x664
    uint8_t mTimer668[0x1c];  // +0x668 cSPTimer
    uint8_t mPad684[0xac];    // +0x684
    float   mf730[4];         // +0x730 quaternion
    uint8_t mPad740[0x08];    // +0x740
};
class tPlanet {
public:
    uint8_t mPad00[0x748];    // +0x000
    float   mf748;            // +0x748
    int32_t mn74c;            // +0x74c empire id
};
struct tXformMsg {
    uint16_t mFlags;   // +0x00
    uint16_t mCount;   // +0x02
    float    mf04;     // +0x04
    float    mf08;     // +0x08
    float    mf0c;     // +0x0c
    float    mf10;     // +0x10
    uint8_t  mMat[0x24]; // +0x14 Matrix3 (9 floats)
};
class cSPSimulatorPlayerUFO_s00ff_d220 {
public:
    void*   mpVtable;         // +0x00
    uint8_t mPad04[0x18];     // +0x04
    void*   mpPlanetRecord;   // +0x1c
    uint8_t mPad20[0x20];     // +0x20
    void*   mpGameDataUFO;    // +0x40
    uint8_t mPad44[0x04];     // +0x44
    float   mf48;             // +0x48
    float   mf4c;             // +0x4c
    uint8_t mPad50[0x08];     // +0x50
    void*   mpHitSphereBegin; // +0x58
    void*   mpHitSphereEnd;   // +0x5c
    uint8_t mPad60[0x48];     // +0x60
    void*   mpEffectA;        // +0xa8
    void*   mpEffectB;        // +0xac
    uint8_t mPadB0[0x08];     // +0xb0
    float   mfb8;             // +0xb8
    float   mfbc;             // +0xbc
    float   mfc0;             // +0xc0
    float   mfc4;             // +0xc4
    float   mfc8;             // +0xc8
    uint8_t mPadCc[0x08];     // +0xcc
    void*   mpD4;             // +0xd4
    void*   mpD8;             // +0xd8
    void*   mpDc;             // +0xdc

    float __thiscall FUN_00ffd220(int nId);  // 0x00ffd220 (cSPSimulatorPlayerUFO::FUN_00ffd220)
    void  __thiscall FUN_00ffd280();  // 0x00ffd280 (cSPSimulatorPlayerUFO::FUN_00ffd280)
    void  __thiscall InitForPlanet();  // 0x00ffd390 (cSPSimulatorPlayerUFO::InitForPlanet)
    void  __thiscall FUN_00ffd710(int nUid, void* pObj);  // 0x00ffd710 (cSPSimulatorPlayerUFO::FUN_00ffd710)
    void  __thiscall FUN_00ffd830(void* pPlanet);  // 0x00ffd830 (cSPSimulatorPlayerUFO::FUN_00ffd830)
    float __thiscall CalculateMaxHealth();  // 0x00ffd8e0 (cSPSimulatorPlayerUFO::CalculateMaxHealth)
    float __thiscall CalculateMaxEnergy();  // 0x00ffda80 (cSPSimulatorPlayerUFO::CalculateMaxEnergy)
    bool  __thiscall FUN_00ffdbb0();  // 0x00ffdbb0 (cSPSimulatorPlayerUFO::FUN_00ffdbb0)
    void  __thiscall FlyToPlanet(void* pPlanet);  // 0x00ffdc20 (cSPSimulatorPlayerUFO::FlyToPlanet)
    void  __thiscall FUN_00ffdde0(int nKind, float fX, float fY, float fZ);  // 0x00ffdde0 (cSPSimulatorPlayerUFO::FUN_00ffdde0)
};
static void* InventoryFind(void* pInv, const uint32_t* pKey)
{
    return ((void*(__thiscall*)(void*, const uint32_t*))VFN(pInv, 0x68))(pInv, pKey);
}
// ---- items of slice s00ffd220 end

// ---- items of slice s00ffe130 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
#define VT(p) (*(void***)(p))
#define REF_ADD(p) (((void(__thiscall*)(void*))VT(p)[1])(p))
#define REF_REL(p) (((void(__thiscall*)(void*))VT(p)[2])(p))
#define REF_ASSIGN(field, src) \
    do { \
        void* _n = (src); \
        void* _o = (field); \
        if (_n != _o) { \
            if (_n) REF_ADD(_n); \
            (field) = _n; \
            if (_o) REF_REL(_o); \
        } \
    } while (0)
#define REF_CLEAR(field) \
    do { \
        void* _p = (field); \
        if (_p) { \
            (field) = 0; \
            REF_REL(_p); \
        } \
    } while (0)
#define STOP_EFFECT(p) \
    do { \
        void* _e = (p); \
        if (_e) \
            ((void(__thiscall*)(void*, int))VT(_e)[0xc / 4])(_e, 0); \
    } while (0)
#define CLEAR_EFFECT(field) \
    do { \
        void* _e = (field); \
        if (_e) { \
            (field) = 0; \
            ((void(__thiscall*)(void*))VT(_e)[1])(_e); \
        } \
    } while (0)
struct Vector3 {
    f32 x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
};
struct Quaternion { f32 x, y, z, w; };
struct Matrix3 { f32 m[9]; };
struct ResourceKey { u32 a, b, c; };
struct Transform {
    u16 mFlags;
    u16 mChangeCount;
    Vector3 mOffset;
    f32 mScale;
    Matrix3 mRotation;
    void ctor();  // 0x00434040
};
class cSpatialObject_s00ff_e130 {
public:
    void* mVtbl;
    const Vector3* GetPosition()
    {
        return ((const Vector3*(__thiscall*)(cSpatialObject_s00ff_e130*))VT(this)[0x2c / 4])(this);
    }
    const Quaternion* GetOrientation()
    {
        return ((const Quaternion*(__thiscall*)(cSpatialObject_s00ff_e130*))VT(this)[0x30 / 4])(this);
    }
};
struct cInventoryView {
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
    virtual bool IsToolSelected(const ResourceKey* key);  // +0x74
};
class cSPGameDataUFO_s00ff_e130 {
public:
    u8 pad00[0x34];
    cSpatialObject_s00ff_e130 mSpatial;            // +0x34
    u8 pad38[0x94 - 0x38];
    Vector3 mDirection;                 // +0x94
    u8 padA0[0x718 - 0xA0];
    Vector3 mSavedPos;                  // +0x718
    u8 pad724[0x790 - 0x724];
    void* m790;                         // +0x790
    void* m794;                         // +0x794
    void* m798;                         // +0x798
    void* m79c;                         // +0x79c
    void* m7a0;                         // +0x7a0

    void* GetToolFromToolID(const ResourceKey* key);  // 0x00ff3d40
};
class cSPSimulatorSpaceGame {
public:
    cSPGameDataUFO_s00ff_e130* GetPlayerInventory();  // 0x00a1ad60
};
struct cCivData_s00ff_e130 {
    Vector3* GetCities();                  // 0x005c65e0
    u32 FUN_00801920(Vector3 pos);         // 0x00801920
};
struct CombatTuning {
    u8 pad00[8];
    void* mPropertyList;                   // +0x08
};
struct cSmoothCameraController {
    f32 CurrentDistance();                 // 0x00c373f0
};
namespace SP {
class cSPSimulatorPlayerUFO_s00ff_e130 {
public:
    u8 pad00[0x40];
    cSPGameDataUFO_s00ff_e130* mpPlayerUFO;            // +0x40
    u8 pad44[0xb0 - 0x44];
    void* mEffectB0;                       // +0xb0
    void* mEffectB4;                       // +0xb4

    void OnContextChange(int context);                                     // 0x00ffe130
    void FUN_00ffe3a0(int context);                                        // 0x00ffe3a0
    void FUN_00ffe3d0(f32 value, bool flag);                               // 0x00ffe3d0
    void SetPlanetDestinationFromOffset(f32 xOffset, f32 yOffset,
                                        bool a, bool b, bool c,
                                        bool useOrientation, bool e);      // 0x00ffe570
    void SetPlanetDestination(Vector3* pos, bool a, bool b, bool c, bool d); // 0x00ffc350
    void FUN_00ffc030();                                                   // 0x00ffc030
    void FUN_00ffca20();                                                   // 0x00ffca20
    void FUN_00ffdde0(u32 cityID);                                         // 0x00ffdde0
};  // namespace SP
}
bool GetPropertyAsKeyArray(void* list, u32 id, int* count, ResourceKey** array); // 0x006a0ae0
cCivData_s00ff_e130* GetCurrentStar();                    // 0x01021240
cSmoothCameraController* FUN_00c37360();       // 0x00c37360
Vector3* FUN_0059aed0_s00ff_e130(Vector3* out, const Vector3* v, const Quaternion* q); // 0x0059aed0
Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quaternion* q);          // 0x0059c190
extern u32 g16dba60;
extern u32 g16dba64;
extern u32 g16dba68;
extern Vector3 g15b626c;
extern f32 g14950d4;
// ---- items of slice s00ffe130 end

// ---- items of slice s00fff8e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VFN_s00ff_f8e0(p, slot) (((void**)*(void**)p)[(slot)/4])
void  FUN_00fff800(void*, void*, float, float, float);  // 0x00fff800
void  FUN_00fff870(void*, void*, float, float, float);  // 0x00fff870
void  FUN_00fff440(void*, int, int, int);         // 0x00fff440
int   FUN_00ac0810(int, int);                     // 0x00ac0810
// ---- items of slice s00fff8e0 end

// ---- items of slice s01000740 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float    g_013ef548;                        // 0x013ef548
#pragma warning(disable: 4100 4244 4312 4996)
class cGameDataUFO {
public:
    uint32_t pad_00[0x34 / 4];      // 0x00..0x33
    uint32_t mTransform_34;         // 0x34  (embedded transform: its vftable ptr)
    uint8_t  pad_38[0x508 - 0x38];  // 0x38..0x507
    uint32_t mTool_508;             // 0x508 (embedded tool: its vftable ptr)
    uint8_t  pad_50c[0x714 - 0x50c];// 0x50c..0x713
    int32_t  mNounType_714;         // 0x714
    float    mPosition_718[3];      // 0x718
    uint8_t  pad_724[0x76c - 0x724];// 0x724..0x76b
    int32_t  mState_76c;            // 0x76c
};
struct cSPSimulatorSpaceGame_s0100_0740 {
    void* GetPlayerInventory();          // 0xa1ad60
};
struct cSPPlayerInventory {
    void* GetToolFromToolID(const void* key);  // 0xff3d40
};
void*  SP_SpaceGameGet(const void* key);      // 0x1002bd0
int    SP_GetPlayerEmpireID();                // 0x1021090
void*  SP_NounManager();                      // 0xb3d300
void*  SP_NormalizedSafe(void* out, const void* src, int flags); // 0x449c20
#define FUN_00cd7d10 ((void*)0xcd7d10)
#define FUN_00d3d420 ((void*)0xd3d420)
#define FUN_00ad48b0 ((void*)0xad48b0)
#define FUN_00b1e500 ((void*)0xb1e500)
// ---- items of slice s01000740 end

// @ 0x00ffbe60
bool cSPSimulatorPlayerUFO::Write(cOutStream* pStream)
{
    tVarListFrame frame;
    frame.mnValue = 0x02f011e8;
    tIStream* pSink = pStream->v20()->v18();
    EA_IO_WriteUint32(pSink, &frame.mnValue, 1, 0);
    frame.mSerializer.Construct((void*)((char*)this - 8), g_varListUFO, 0x1a80d26);
    return frame.mSerializer.Serialize(pStream);
}

// @ 0x00ffbf60
void cSPSimPlanetHighLOD::Init()
{
    void* pListener = this != 0 ? (void*)((uint8_t*)this + 0x10) : 0;
    tMessageServer* pServer = EA::Messaging::GetServer();
    mp2c = (void*)pServer;
    mp30 = pListener;
    mp34 = g_ufoListenerVtable;
    mn38 = 1;
    mn3c = 0;
    if (pServer != 0 && pListener != 0)
        pServer->v24(pListener, 0x057f3749);
    SimTicker()->v50(this);
}

// @ 0x00ffbfe0
bool cSPSimPlanetHighLOD::FUN_00ffbfe0()
{
    uint64_t nElapsed = mTimer80.GetElapsedTime();
    return nElapsed > (uint64_t)mnA0;
}

// @ 0x00ffc030
void cSPSimPlanetHighLOD::FUN_00ffc030()
{
    cTerrainSphere* pSphere = (cTerrainSphere*)NounManager()->GetCurrentTerrainSphere();
    pSphere->FUN_00c77bf0(0x05c2d1ab);
    tEffectsGlobal* pEffects = FUN_0067cac0();
    if (pEffects->mp4c != 0 && ((uint32_t*)pEffects->mp4c)[2] == (uint32_t)0x43c18587)
    {
        pEffects->FUN_0067c8c0(0x43c18587, 1);
        FUN_010666a0()->FUN_01065d20();
    }
    mTimer80.Restart();
}

// @ 0x00ffc160
bool cSPSimPlanetHighLOD::CheckAndReplaceData(void* pKey, void* pB, void* pC)
{
    cEmpireKey* pOwnKey = (cEmpireKey*)GetPlayerEmpire();
    if (pKey != 0)
        pOwnKey->SetUFOKey(&pKey);

    tUFOData* pNoun = NounManager()->CreateNoun(g_nounListUFO);
    tUFOData* pNew = pNoun != 0 ? (tUFOData*)pNoun->v0c(0xb033b403) : 0;

    tUFOData* pOld = mp40;
    if (pNew != pOld)
    {
        if (pNew != 0)
            pNew->AddRef();
        mp40 = pNew;
        if (pOld != 0)
            pOld->Release();
    }

    tUFOData* pData = mp40;
    pData->Init(0, GetPlayerEmpire());
    SimTicker()->v50(this);

    void* pListener = (void*)((uint8_t*)this + 0x10);
    tMessageServer* pServer = EA::Messaging::GetServer();
    mp2c = (void*)pServer;
    mp30 = pListener;
    mp34 = g_ufoListenerVtable;
    mn38 = 1;
    mn3c = 0;
    if (pServer != 0 && pListener != 0)
        pServer->v24(pListener, 0x057f3749);
    return true;
}

// @ 0x00ffd280
void __thiscall cSPSimulatorPlayerUFO_s00ff_d220::FUN_00ffd280()
{
    void* pObj = ((tHost*)((tHost*)FUN_01021260())->FUN_00c71e30());
    float fLocal = 0.0f;
    int nId = ((tHost*)FUN_0102f810())->FUN_0102f8d0(pObj, &fLocal);
    if (fLocal > kRealZero) {
        ((tHost*)FUN_01021300())->FUN_00c31a00(-nId);
        ((tHost*)mpGameDataUFO)->FUN_00c389f0(fLocal);
    }
}

// @ 0x00ffd390
void __thiscall cSPSimulatorPlayerUFO_s00ff_d220::InitForPlanet()
{
    float vUp[3];
    float vPos[3];
    float vConj[4];
    float vRes[3];
    float vFacing[3];
    float vQuat[4];

    vUp[0] = kRealOne;
    vUp[1] = kRealOne;
    vUp[2] = 0.0f;

    tHost* pApp = (tHost*)App();
    tHost* pA = (tHost*)((void*(__thiscall*)(void*))VFN(pApp, 0x50))(pApp);
    void* pB = ((void*(__thiscall*)(void*))VFN(pA, 0x38))(pA);
    if (pB != 0) {
        void* pC = ((void*(__thiscall*)(void*, uint32_t))VFN(pB, 0x0c))(pB, 0x303154cc);
        if (pC != 0) {
            FUN_010424c0(vPos, (char*)pC + 0x68);

            void* pPlanet = FUN_01021260();
            void* pQuat = ((void*(__thiscall*)(void*))VFN(pPlanet, 0x30))(pPlanet);
            float q0 = *(float*)((char*)pQuat + 0x00);
            float q1 = *(float*)((char*)pQuat + 0x04);
            float q2 = *(float*)((char*)pQuat + 0x08);
            float q3 = *(float*)((char*)pQuat + 0x0c);
            float fInv = kRealOne / (q3 * q3 + q2 * q2 + q1 * q1 + q0 * q0);
            vConj[3] = q3 * fInv;
            vConj[1] = -(q1 * fInv);
            vConj[2] = -(q2 * fInv);
            vConj[0] = -(q0 * fInv);
            FUN_0059aed0(vRes, vPos, vConj);
            if (sqrtf(vRes[0] * vRes[0] + vRes[1] * vRes[1] + vRes[2] * vRes[2]) > kDirEps) {
                vUp[0] = vRes[0];
                vUp[1] = vRes[1];
                vUp[2] = vRes[2];
            }
        }
    }

    float fNorm = kRealOne / sqrtf(vUp[0] * vUp[0] + vUp[1] * vUp[1] + vUp[2] * vUp[2] + kNormEps);
    vUp[0] = fNorm * vUp[0];
    vUp[1] = vUp[1] * fNorm;
    vUp[2] = vUp[2] * fNorm;

    ((tHost*)this)->FUN_00ffc350(vUp, 0, 1, 0, 0);

    float f0 = vUp[2] * kFwdY - vUp[1] * kFwdZ;
    float f1 = kFwdZ * vUp[0] - vUp[2] * kFwdX;
    float f2 = vUp[1] * kFwdX - kFwdY * vUp[0];
    vFacing[0] = f2 * vUp[1] - f1 * vUp[2];
    vFacing[1] = vUp[2] * f0 - f2 * vUp[0];
    vFacing[2] = f1 * vUp[0] - vUp[1] * f0;

    QuaternionFromFacingAndUp(vQuat, vFacing, vUp);

    cSPGameDataUFO* pData = (cSPGameDataUFO*)mpGameDataUFO;
    pData->mf730[0] = vQuat[0];
    pData->mf730[1] = vQuat[1];
    pData->mf730[2] = vQuat[2];
    pData->mf730[3] = vQuat[3];
    pData->mf5f4 = vFacing[0];
    pData->mf5f8 = vFacing[1];
    pData->mf5fc = vFacing[2];

    ((tHost*)&pData->mTimer648)->FUN_00bc3130();
    pData->mf604 = 0.0f;
    pData->mf5ec = 0.0f;
    ((tHost*)&pData->mTimer668)->FUN_00bc3170();
    pData->mf60c = kBaseX;
    pData->mf610 = kBaseY;
    pData->mf614 = kBaseZ;

    ((tHost*)FUN_00b3d230())->FUN_00b5cde0(0x1103193);

    tHost* pApp2 = (tHost*)App();
    tHost* pA2 = (tHost*)((void*(__thiscall*)(void*))VFN(pApp2, 0x50))(pApp2);
    void* pB2 = ((void*(__thiscall*)(void*))VFN(pA2, 0x38))(pA2);
    if (pB2 != 0) {
        void* pC2 = ((void*(__thiscall*)(void*, uint32_t))VFN(pB2, 0x0c))(pB2, 0x303154cd);
        if (pC2 != 0)
            ((tHost*)pC2)->FUN_010170e0();
    }
}

// @ 0x00ffd710
void __thiscall cSPSimulatorPlayerUFO_s00ff_d220::FUN_00ffd710(int nUid, void* pObj)
{
    if (mpD4 != 0) {
        void* pA = ((void*(__thiscall*)(void*))VFN(mpD4, 0x08))(mpD4);
        ((void(__thiscall*)(void*, int))VFN(pA, 0x54))(pA, 0);
    }

    if (pObj == 0)
        goto lbReleaseD8;
    {
        void* pA = ((void*(__thiscall*)(void*))VFN(pObj, 0x08))(pObj);
        ((void(__thiscall*)(void*, int))VFN(pA, 0x54))(pA, 1);
        void* pKey = ((void*(__thiscall*)(void*))VFN(pObj, 0x0c))(pObj);
        if (!FUN_0102af80(nUid, pKey))
            goto lbReleaseD8;
        void* pOld = mpD8;
        if (pObj == pOld)
            goto lbD4;
        ((void(__thiscall*)(void*))VFN(pObj, 0x60))(pObj);
        mpD8 = pObj;
        if (pOld == 0)
            goto lbD4;
        ((void(__thiscall*)(void*))VFN(pOld, 0x64))(pOld);
    }
    goto lbD4;

lbReleaseD8:
    {
        void* pOld = mpD8;
        if (pOld != 0) {
            mpD8 = 0;
            ((void(__thiscall*)(void*))VFN(pOld, 0x64))(pOld);
        }
    }

lbD4:
    {
        void* pOld = mpD4;
        if (pObj != pOld) {
            if (pObj != 0)
                ((void(__thiscall*)(void*))VFN(pObj, 0x60))(pObj);
            mpD4 = pObj;
            if (pOld != 0)
                ((void(__thiscall*)(void*))VFN(pOld, 0x64))(pOld);
        }
    }

    if (mpD4 != 0 && mpDc != 0) {
        if (mpD4 != 0) {
            void* pO = ((void*(__thiscall*)(void*, uint32_t))VFN(mpD4, 0x5c))(mpD4, 0x436f315);
            if (pO != 0 && ((tHost*)pO)->FUN_00bce5c0() == mpDc)
                return;
        }
        void* pHold = mpDc;
        if (pHold != 0) {
            mpDc = 0;
            ((void(__thiscall*)(void*))VFN(pHold, 0x04))(pHold);
        }
    }
}

// @ 0x00ffd830
void __thiscall cSPSimulatorPlayerUFO_s00ff_d220::FUN_00ffd830(void* pPlanet)
{
    tPlanet* pNew = (tPlanet*)pPlanet;

    if (pNew != 0) {
        cSPGameDataUFO* pData = (cSPGameDataUFO*)mpGameDataUFO;
        int32_t nEmpire = ((int32_t(__thiscall*)(void*))VFN(pData, 0x4c))(pData);
        if (pNew->mn74c == nEmpire && pNew->mf748 >= kHundred)
            return;
    }

    void* pOld = mpDc;
    if (pNew != pOld) {
        if (pNew != 0)
            ((void(__thiscall*)(void*))VFN(pNew, 0x00))(pNew);
        mpDc = pNew;
        if (pOld != 0)
            ((void(__thiscall*)(void*))VFN(pOld, 0x04))(pOld);
    }

    if (mpD4 != 0 && mpDc != 0) {
        if (mpD4 != 0) {
            void* pO = ((void*(__thiscall*)(void*, uint32_t))VFN(mpD4, 0x5c))(mpD4, 0x436f315);
            if (pO != 0 && ((tHost*)pO)->FUN_00bce5c0() == mpDc)
                return;
        }
        FUN_00ffd710(0, 0);
    }
}

// @ 0x00ffd8e0
float __thiscall cSPSimulatorPlayerUFO_s00ff_d220::CalculateMaxHealth()
{
    float fScale = kRealOne;
    float fBonus;

    void* pInv = ((tHost*)SpaceGameGet())->FUN_00a1ad60();
    if (pInv != 0) {
        void* pItem = InventoryFind(pInv, &kHealthUpgrade10);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade9);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade8);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade7);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade6);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade5);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade4);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade3);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade2);
        if (pItem == 0) pItem = InventoryFind(pInv, &kHealthUpgrade1);
        if (pItem != 0) {
            char* pSub = (char*)pItem + 0x0c;
            void* pRes = ((void*(__thiscall*)(void*, uint32_t))VFN(pSub, 0x0c))(pSub, 0x707459f0);
            fScale = ((tHost*)pRes)->FUN_0104be30();
        }
    }

    if ((*(uint8_t*)((char*)SpaceGameGet() + 0xc4) & 8) != 0) {
        fScale = ((tHost*)SpaceGameGet())->FUN_01005c60(3) * fScale;
    }

    float fRate = ((tHost*)((tHost*)NounManager_s00ff_d220())->FUN_00f67d90())->FUN_00c75c30(0xc045ed0d);
    fScale = fRate * fScale;
    fBonus = kThousand;

    void* pTun = GetSpaceCombatTuning();
    void* pSpace = *(void**)((char*)pTun + 0x08);
    if (pSpace != 0) {
        void* pProp;
        if (((bool(__thiscall*)(void*, uint32_t, void**))VFN(pSpace, 0x24))(pSpace, 0x2fa794e, &pProp)) {
            if (*(uint16_t*)((char*)pProp + 0x12) == 0x0d) {
                fBonus = *((tHost*)pProp)->FUN_0041ea70();
            }
        }
    }
    return fBonus * fScale;
}

// @ 0x00ffda80
float __thiscall cSPSimulatorPlayerUFO_s00ff_d220::CalculateMaxEnergy()
{
    float fScale = kRealOne;

    void* pInv = ((tHost*)SpaceGameGet())->FUN_00a1ad60();
    if (pInv != 0) {
        void* pItem = InventoryFind(pInv, &kEnergyUpgrade10);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade9);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade8);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade7);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade6);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade5);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade4);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade3);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade2);
        if (pItem == 0) pItem = InventoryFind(pInv, &kEnergyUpgrade1);
        if (pItem != 0) {
            char* pSub = (char*)pItem + 0x0c;
            void* pRes = ((void*(__thiscall*)(void*, uint32_t))VFN(pSub, 0x0c))(pSub, 0x707459f0);
            fScale = ((tHost*)pRes)->FUN_0104be30();
        }
    }

    uint8_t* pFlags = (uint8_t*)SpaceGameGet() + 0xc4;
    if ((*pFlags & 1) != 0) {
        float fAdd = ((tHost*)SpaceGameGet())->FUN_01005c60(0);
        return (fAdd * fScale) * kHundred;
    }
    return fScale * kHundred;
}

// @ 0x00ffdbb0
bool __thiscall cSPSimulatorPlayerUFO_s00ff_d220::FUN_00ffdbb0()
{
    if (mpPlanetRecord != 0)
        goto haveRecord;
    ((tHost*)this)->FUN_00ffc6d0();
    if (mpPlanetRecord != 0)
        goto haveRecord;
    mf48 = 0.0f;
    mf4c = kFive;
    return false;
haveRecord:
    {
        void* pCities = ((tHost*)FUN_01021240())->FUN_005c65e0();
        mf48 = ((tHost*)this)->FUN_00ffc7f0(pCities);
        mf4c = ((tHost*)mpPlanetRecord)->FUN_00ce6930();
        float fMax = ((tHost*)mpPlanetRecord)->FUN_0104be30();
        return mf48 < fMax;
    }
}

// @ 0x00ffdc20
void __thiscall cSPSimulatorPlayerUFO_s00ff_d220::FlyToPlanet(void* pPlanet)
{
    void* pInv = ((tHost*)SpaceGameGet())->FUN_00a1ad60();
    if (((bool(__thiscall*)(void*, uint32_t))VFN(pInv, 0x74))(pInv, (uint32_t)&kInterplanetaryDrive)) {
        cSPGameDataUFO* pData = (cSPGameDataUFO*)mpGameDataUFO;
        ((tHost*)pData)->FUN_00c3c190(pPlanet);
        ((tHost*)&pData->mTimer648)->FUN_00bc3170();
        ((tHost*)((tHost*)NounManager_s00ff_d220())->FUN_00f67d90())->FUN_00c77bf0(0x56e2b88);

        uint32_t nKey = FUN_00932e80(g_szReticleGotoScreen, 0x811c9dc5, 1);

        tXformMsg msg;
        void* pHandle = 0;
        {
            void* pOld = pHandle;
            if (pOld != 0) {
                pHandle = 0;
                ((void(__thiscall*)(void*))VFN(pOld, 0x04))(pOld);
            }
        }
        void* pEm = EffectsManagerPtr();
        if (((bool(__thiscall*)(void*, uint32_t, int, void**))VFN(pEm, 0x2c))(pEm, nKey, 0, &pHandle)) {
            msg.mf04 = kMsgX;
            msg.mf08 = kMsgY;
            msg.mf0c = kMsgZ;
            msg.mCount = 0;
            msg.mf10 = kRealOne;
            ((tHost*)msg.mMat)->FUN_0041cb40(kRefMatrix);
            msg.mFlags = 0;

            void* pPos = ((void*(__thiscall*)(void*))VFN(pPlanet, 0x2c))(pPlanet);
            msg.mf04 = *(float*)((char*)pPos + 0x00);
            msg.mf08 = *(float*)((char*)pPos + 0x04);
            msg.mf0c = *(float*)((char*)pPos + 0x08);
            msg.mFlags |= 4;
            msg.mCount++;

            ((void(__thiscall*)(void*, tXformMsg*))VFN(pHandle, 0x18))(pHandle, &msg);
            ((void(__thiscall*)(void*, int))VFN(pHandle, 0x08))(pHandle, 0);
        }

        tHost* pApp = (tHost*)App();
        tHost* pA = (tHost*)((void*(__thiscall*)(void*))VFN(pApp, 0x50))(pApp);
        void* pB = ((void*(__thiscall*)(void*, uint32_t))VFN(pA, 0x40))(pA, 0x1103192);
        if (pB != 0) {
            void* pC = ((void*(__thiscall*)(void*, uint32_t))VFN(pB, 0x0c))(pB, 0x303154cc);
            if (pC != 0)
                ((tHost*)pC)->FUN_01017000();
        }

        void* pMsg = MessageServer();
        ((void(__thiscall*)(void*, uint32_t, int, int, int))VFN(pMsg, 0x18))(pMsg, 0x490d429, 0, 0, 0);

        if (pHandle != 0)
            ((void(__thiscall*)(void*))VFN(pHandle, 0x04))(pHandle);
    }
}

// @ 0x00ffdde0
void __thiscall cSPSimulatorPlayerUFO_s00ff_d220::FUN_00ffdde0(int nKind, float fX, float fY, float fZ)
{
    {
        void* pE = mpEffectA;
        if (pE != 0 && ((bool(__thiscall*)(void*))VFN(pE, 0x10))(pE)) {
            void* pE2 = mpEffectA;
            ((void(__thiscall*)(void*, int))VFN(pE2, 0x0c))(pE2, 1);
            if (mpEffectA != 0) {
                mpEffectA = 0;
                ((void(__thiscall*)(void*))VFN(pE2, 0x04))(pE2);
            }
        }
    }
    {
        void* pE = mpEffectB;
        if (pE != 0 && ((bool(__thiscall*)(void*))VFN(pE, 0x10))(pE)) {
            void* pE2 = mpEffectB;
            ((void(__thiscall*)(void*, int))VFN(pE2, 0x0c))(pE2, 1);
            if (mpEffectB != 0) {
                mpEffectB = 0;
                ((void(__thiscall*)(void*))VFN(pE2, 0x04))(pE2);
            }
        }
    }

    uint32_t nKey1;
    uint32_t nKey2;
    switch (nKind) {
    case 4:  nKey1 = 0x03d6ef4d; nKey2 = 0;                  break;
    case 5:  nKey1 = 0x03d6ef59; nKey2 = 0;                  break;
    case 6:  nKey1 = 0x03d6ef67; nKey2 = 0;                  break;
    case 7:  nKey1 = 0x03d6ef59; nKey2 = 0x03d6ef59;         break;
    case 8:  nKey1 = 0x03d6ef59; nKey2 = 0x03d6ef59 - 0x0c;  break;
    case 9:  nKey1 = 0x03d6ef59; nKey2 = 0x03d6ef59 + 0x0e;  break;
    case 10: nKey1 = 0x03d6ef4d; nKey2 = 0x03d6ef4d;         break;
    case 11: nKey1 = 0x03d6ef4d; nKey2 = 0x03d6ef4d + 0x1a;  break;
    case 12: nKey1 = 0x03d6ef67; nKey2 = 0x03d6ef67;         break;
    default: return;
    }

    tXformMsg msgA;
    msgA.mf04 = kMsgX;
    msgA.mf08 = kMsgY;
    msgA.mf0c = kMsgZ;
    msgA.mCount = 0;
    msgA.mf10 = kRealOne;
    ((tHost*)msgA.mMat)->FUN_0041cb40(kRefMatrix);
    msgA.mFlags = 0;
    msgA.mf08 = fX;
    msgA.mFlags |= 4;
    msgA.mCount += 2;
    msgA.mf04 = fY;
    msgA.mf0c = fZ;
    msgA.mf10 = mfb8;

    tHost* pEm = (tHost*)EffectsManagerPtr();
    {
        void* pOld = mpEffectA;
        if (pOld != 0) {
            mpEffectA = 0;
            ((void(__thiscall*)(void*))VFN(pOld, 0x04))(pOld);
        }
    }
    if (((bool(__thiscall*)(void*, uint32_t, int, void**))VFN(pEm, 0x2c))(pEm, nKey1, 0, &mpEffectA)) {
        if (nKey2 != 0) {
            tHost* pEm2 = (tHost*)EffectsManagerPtr();
            {
                void* pOld = mpEffectB;
                if (pOld != 0) {
                    mpEffectB = 0;
                    ((void(__thiscall*)(void*))VFN(pOld, 0x04))(pOld);
                }
            }
            if (((bool(__thiscall*)(void*, uint32_t, int, void**))VFN(pEm2, 0x2c))(pEm2, nKey2, 0, &mpEffectB)) {
                tXformMsg msgB;
                ((tHost*)&msgB)->FUN_00434040();
                msgB.mf04 = fY + mfc0;
                msgB.mf08 = fX + mfc4;
                msgB.mf0c = fZ + mfc8;
                msgB.mf10 = mfbc;
                msgB.mFlags |= 4;
                msgB.mCount += 2;
                ((void(__thiscall*)(void*, tXformMsg*))VFN(mpEffectB, 0x14))(mpEffectB, &msgB);
                ((void(__thiscall*)(void*, int))VFN(mpEffectB, 0x08))(mpEffectB, 0);

                msgA.mFlags |= 4;
                msgA.mCount++;
                msgA.mf04 = fY - mfc0;
                msgA.mf08 = fX - mfc4;
                msgA.mf0c = fZ - mfc8;
            }
        }
        ((void(__thiscall*)(void*, tXformMsg*))VFN(mpEffectA, 0x14))(mpEffectA, &msgA);
        ((void(__thiscall*)(void*, int))VFN(mpEffectA, 0x08))(mpEffectA, 0);
    }
}

// @ 0x00ffe130
void SP::cSPSimulatorPlayerUFO_s00ff_e130::OnContextChange(int context)
{
    SP::cSPSimulatorPlayerUFO_s00ff_e130* self = this;
    cSPGameDataUFO_s00ff_e130* state = self->mpPlayerUFO;

    REF_CLEAR(state->m7a0);
    REF_ASSIGN(state->m79c, state->m7a0);
    REF_ASSIGN(state->m798, state->m79c);

    cSPGameDataUFO_s00ff_e130* inventory =
        ((cSPSimulatorSpaceGame*)SpaceGameGet())->GetPlayerInventory();

    ResourceKey* keys = 0;
    int count = 0;

    switch (context) {
    case 0: {
        CombatTuning* tuning = (CombatTuning*)GetSpaceCombatTuning();
        void** list = &tuning->mPropertyList;
        GetPropertyAsKeyArray(*list, 0x6170854, &count, &keys);
        break;
    }
    case 1: {
        CombatTuning* tuning = (CombatTuning*)GetSpaceCombatTuning();
        void** list = &tuning->mPropertyList;
        GetPropertyAsKeyArray(*list, 0x5877fb5, &count, &keys);
        self->FUN_00ffca20();
        break;
    }
    case 2: {
        CombatTuning* tuning = (CombatTuning*)GetSpaceCombatTuning();
        void** list = &tuning->mPropertyList;
        GetPropertyAsKeyArray(*list, 0x5877fc0, &count, &keys);
        cCivData_s00ff_e130* civ = GetCurrentStar();
        self->FUN_00ffdde0(civ->FUN_00801920(*civ->GetCities()));
        break;
    }
    }

    ResourceKey selected = { g16dba60, g16dba64, g16dba68 };
    for (int i = count - 1; i >= 0; --i) {
        if (((cInventoryView*)inventory)->IsToolSelected(&keys[i]))
            selected = keys[i];
    }

    if (selected.a != g16dba60 || selected.b != g16dba64 ||
        selected.c != g16dba68) {
        void* tool = inventory->GetToolFromToolID(&selected);
        REF_ASSIGN(state->m798, tool);
    }

    REF_ASSIGN(state->m790, state->m798);
}

// @ 0x00ffe3a0
void SP::cSPSimulatorPlayerUFO_s00ff_e130::FUN_00ffe3a0(int context)
{
    void* server = MessageServer();
    ((void(__thiscall*)(void*, u32, int, int, int))VT(server)[0x18 / 4])(
        server, 0x490d429, 0, 0, 0);
    this->OnContextChange(context);
}

// @ 0x00ffe3d0
void SP::cSPSimulatorPlayerUFO_s00ff_e130::FUN_00ffe3d0(f32 value, bool flag)
{
    void** field;

    if (flag) {
        STOP_EFFECT(this->mEffectB4);

        if (value <= 0.0f) {
            STOP_EFFECT(this->mEffectB0);
            return;
        }

        field = &this->mEffectB0;
        if (!*field) {
            void* mgr = EffectsManagerPtr();
            CLEAR_EFFECT(*field);
            ((void(__thiscall*)(void*, u32, int, void**))VT(mgr)[0x2c / 4])(
                mgr, 0x7a564da0, 0, field);
        }
    } else {
        STOP_EFFECT(this->mEffectB0);

        if (value <= 0.0f) {
            STOP_EFFECT(this->mEffectB4);
            return;
        }

        field = &this->mEffectB4;
        if (!*field) {
            void* mgr = EffectsManagerPtr();
            CLEAR_EFFECT(*field);
            ((void(__thiscall*)(void*, u32, int, void**))VT(mgr)[0x2c / 4])(
                mgr, 0x2796d2d5, 0, field);
        }
    }

    if (!*field)
        return;

    if (!((bool(__thiscall*)(void*))VT(*field)[0x10 / 4])(*field))
        ((void(__thiscall*)(void*, int))VT(*field)[8 / 4])(*field, 0);

    ((void(__thiscall*)(void*, int, const f32*, int))VT(*field)[0x44 / 4])(
        *field, 4, &value, 1);

    Matrix3 scratch;
    Transform msg;
    msg.ctor();

    cSPGameDataUFO_s00ff_e130* ufo = this->mpPlayerUFO;
    msg.mOffset = *ufo->mSpatial.GetPosition();
    msg.mFlags |= 4;
    msg.mChangeCount++;

    Matrix3* mat = Matrix3FromQuaternion(&scratch, ufo->mSpatial.GetOrientation());
    msg.mRotation = *mat;
    msg.mFlags |= 2;
    msg.mChangeCount++;

    ((void(__thiscall*)(void*, Transform*))VT(*field)[0x18 / 4])(*field, &msg);
}

// @ 0x00ffe570
void SP::cSPSimulatorPlayerUFO_s00ff_e130::SetPlanetDestinationFromOffset( f32 xOffset, f32 yOffset, bool a, bool b, bool c, bool useOrientation, bool e)
{
    void* app = App();
    void* mode = ((void*(__thiscall*)(void*))VT(app)[0x50 / 4])(app);
    void* world = ((void*(__thiscall*)(void*))VT(mode)[0x38 / 4])(mode);
    if (!world)
        return;

    void* obj = ((void*(__thiscall*)(void*, u32))VT(world)[0xc / 4])(
        world, 0x303154cd);
    if (!obj)
        return;

    cSPGameDataUFO_s00ff_e130* data = (cSPGameDataUFO_s00ff_e130*)obj;
    Vector3 dir;

    if (useOrientation) {
        cSpatialObject_s00ff_e130* spatial = &this->mpPlayerUFO->mSpatial;
        FUN_0059aed0_s00ff_e130(&dir, &g15b626c, spatial->GetOrientation());
    } else {
        f32 inv = 1.0f / sqrtf(data->mDirection.x * data->mDirection.x +
                              data->mDirection.y * data->mDirection.y +
                              data->mDirection.z * data->mDirection.z);
        dir.x = data->mDirection.x * inv;
        dir.y = data->mDirection.y * inv;
        dir.z = data->mDirection.z * inv;
    }

    Vector3 base = dir;
    cSmoothCameraController* camera = FUN_00c37360();
    f32 angle = camera->CurrentDistance() * g14950d4;

    cSPGameDataUFO_s00ff_e130* ufo = this->mpPlayerUFO;
    Vector3 axis;
    axis.x = ufo->mSavedPos.y * dir.z - ufo->mSavedPos.z * dir.y;
    axis.y = ufo->mSavedPos.z * dir.x - ufo->mSavedPos.x * dir.z;
    axis.z = ufo->mSavedPos.x * dir.y - ufo->mSavedPos.y * dir.x;

    f32 invAxis = 1.0f / sqrtf(axis.x * axis.x + axis.y * axis.y +
                               axis.z * axis.z);
    f32 half1 = angle * yOffset * 0.5f;
    f32 sin1 = sinf(half1);
    f32 cos1 = cosf(half1);
    Quaternion q1;
    q1.x = axis.x * invAxis * sin1;
    q1.y = axis.y * invAxis * sin1;
    q1.z = axis.z * invAxis * sin1;
    q1.w = cos1;

    Vector3 rotated;
    FUN_0059aed0_s00ff_e130(&rotated, &ufo->mSavedPos, &q1);

    f32 half2 = angle * xOffset * 0.5f;
    f32 sin2 = sinf(half2);
    f32 cos2 = cosf(half2);
    Quaternion q2;
    q2.x = base.x * sin2;
    q2.y = base.y * sin2;
    q2.z = base.z * sin2;
    q2.w = cos2;

    Vector3 dest;
    FUN_0059aed0_s00ff_e130(&dest, &rotated, &q2);

    this->SetPlanetDestination(&dest, a, b, c, e);
    this->FUN_00ffc030();
}

// @ 0x00fffc90
void FUN_00fffc90(int* param_1, int* param_2, int* param_3, float f1, float f2, float f3)
{
    FUN_00fff800(param_1, param_2, f1, f2, f3);
    for (int* it = param_2; it < param_3; ++it) {
        if (FUN_00ac0810(*it, *param_1)) {
            int* old = (int*)*it;
            if (old != 0)
                ((void(__thiscall*)(void*))VFN_s00ff_f8e0(old, 0))(old);
            int* src = (int*)*param_1;
            if (src != old) {
                if (src != 0)
                    ((void(__thiscall*)(void*))VFN_s00ff_f8e0(src, 0))(src);
                *it = (int)src;
                if (old != 0)
                    ((void(__thiscall*)(void*, int))VFN_s00ff_f8e0(old, 4))(old, 1);
            }
            FUN_00fff440(param_1, 0, (int)param_2 - (int)param_1 >> 2, 0);
            if (old != 0)
                ((void(__thiscall*)(void*, int))VFN_s00ff_f8e0(old, 4))(old, 1);
        }
    }
    FUN_00fff870(param_1, param_2, f1, f2, f3);
}

// @ 0x01000dc0
void FUN_01000dc0(void)
{
    void* sg = SP_SpaceGameGet((void*)0x16dbf04);
    void* inv = ((cSPSimulatorSpaceGame_s0100_0740*)sg)->GetPlayerInventory();
    void* tool = ((cSPPlayerInventory*)inv)->GetToolFromToolID((void*)0x16dbf04);
    if (tool == 0) return;
    if (((bool(__thiscall*)(void*))0x104ff10)(tool)) return;

    int empireID = SP_GetPlayerEmpireID();

    void* nm = SP_NounManager();
    char* vec = (char*)((void*(__thiscall*)(void*, void*, void*, void*, void*, void*))0xb21340)
                    (nm, FUN_00cd7d10, FUN_00d3d420, FUN_00ad48b0, FUN_00b1e500, (void*)0x18ebadc);
    void** begin = *(void***)(vec + 4);
    int count = (int)((*(char**)(vec + 8) - (char*)begin) >> 2);

    for (int i = 0; i < count; ++i) {
        cGameDataUFO* noun = (cGameDataUFO*)begin[i];
        if (noun == 0) continue;
        if (noun->mNounType_714 != 3) continue;
        if (((int(__thiscall*)(void*))VT(noun)[0x4c / 4])(noun) != empireID) continue;

        void* toolp = &noun->mTool_508;
        float buf[3];
        void* t = SP_NormalizedSafe(buf, noun->mPosition_718, 0);
        ((void(__thiscall*)(void*, float, int, int, void*, int))VT(toolp)[0x18 / 4])
            (toolp, g_013ef548, -1, 0, t, 0);
        return;
    }
}
