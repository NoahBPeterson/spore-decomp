// src/game/SPGonzago/SPMission.cpp -- migrated from slice(s) s00c45860, s00b9bed0, s00c4a850, s00c498e0, s00c48970, s00c47a10, s00c46ab0, s00c44a20, s00c44080 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMission.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// Hand guard (kept by merge_preamble on re-apply): the generated tm.h defines `struct tm` unguarded, so it
// collides with <wchar.h>'s own `struct tm` (C2011) as soon as a slice of this module needs <wchar.h>.
// Defining the CRT guard first makes <wchar.h> skip its copy; tm.h (via SP/cStarRecord.h) still supplies
// `struct tm` for cStarRecord::savedGameTimeStamp (same 9-int layout).
#define _TM_DEFINED

#include "game/types.h"
#include "SP/cSPMission.h"
#include "SP/cEmpire.h"
#include "SP/cPlanet.h"
#include "SP/cPropertyList.h"
#include "SP/cStarManager.h"
#include "SP/cStarRecord.h"
#include "SP/cSPTimer.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cString.h"
#include <intrin.h>
#include "SP/cCivData.h"
#include <wchar.h>
#include <string.h>
#include <xmmintrin.h>
#include <math.h>
#include "SP/cGameData.h"
#include "EA/Variant.h"
#include "SP/cVarListSerializer.h"
#include "SP/cStarClue.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cPlanetModel.h"
#include <new>
#include "SP/cRelationshipManager.h"
#include "SP/cTerrainSphere.h"

// ---- items of slice s00c44080 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
struct cStarRecord {
    u32 GetStarID();        // 0x00b8de30
    int GetCommContext();   // 0x00ce6950
};
struct cPlanet {
    u8            mPad0000[0x13c];
    cStarRecord*  mpStarRecord13c;   // 0x13c
};
struct cEmpire {
    u8   mPad0000[0x84];
    u32  mEmpireID84;                // 0x84
};
struct cStarManager {
    cEmpire* GetEmpireByID();        // 0x00ba9370
    void SetPlanetRef(u32 planetId, void** out);  // 0x00bb59b0
};
struct cUFO {
    int   ComputeCost(u32 starID);   // 0x00ffc4e0
    float ComputeCostFloat(u32 starID);  // 0x00ffc490
};
cStarManager* __stdcall GetStarManager(u32 empireID);  // 0x00b3d2a0
cUFO*         __stdcall GetUFOSimulator(u32 starID);   // 0x00ffbe50
void __cdecl SP_GetPropertyAsString16(void* prop, int key, int value);  // 0x006a1400
struct cProperty {
    u8    mPad0000[0x12];
    u16   mType12;                   // 0x12  property data type (1 = bool)
    bool* GetBool();                 // 0x0041e920
};
struct cPropertyList {
    // vtable slot 9 (offset 0x24), returns whether the key was found
    bool GetProperty(int key, cProperty** out);
};
inline bool cPropertyList::GetProperty(int key, cProperty** out)
{
    return ((bool (__thiscall*)(cPropertyList*, int, cProperty**))
            (*(void***)this)[9])(this, key, out);
}
static inline void VT_00_0(void* p) { ((void (__thiscall*)(void*))(*(void***)p)[0])(p); }
static inline void VT_04_0(void* p) { ((void (__thiscall*)(void*))(*(void***)p)[1])(p); }
static inline int  VT_60_0(void* p) { return ((int (__thiscall*)(void*))(*(void***)p)[0x18])(p); }
struct cSPMission {
    u8            mPad0000[0x7c];
    int           mUsed7c;                 // 0x7c
    int           mTotal80;                // 0x80
    u8            mPad0084[0x8c - 0x84];
    int           mEmpireID8c;             // 0x8c
    u8            mPad0090[0x94 - 0x90];
    int           mCachedEmpireID94;       // 0x94  (-1 when unset)
    cEmpire*      mpEmpire98;              // 0x98  ref-counted, cached
    cPlanet*      mpOriginPlanet9c;        // 0x9c
    u8            mPad00a0[0x130 - 0xa0];
    u8            mFlags130;               // 0x130
    u8            mPad0131[0x180 - 0x131];
    cPropertyList* mpPropertyList180;      // 0x180
    u8            mPad0184[0x1e8 - 0x184];
    cPlanet*      mpTargetPlanet1e8;       // 0x1e8

    void        SetEmpire(cEmpire* p);                    // 0x00c45250
    cEmpire*    GetEmpire();                              // 0x00c452a0
    int         SetUITextValue(int value);                // 0x00c45310
    bool        IsVisibleInUI();                          // 0x00c45340
    int         GetNumAvailable();                        // 0x00c45380
    int         GetTotalTravelCost();                     // 0x00c45510
    float       GetTotalTravelCostFloat();                // 0x00c45560
    bool        IsAtStar(int empireID, int commContext);  // 0x00c455b0
    int         GetDynamicResponseID(int a, int b);       // 0x00c45740
};
static inline const int& max_ref(const int& a, const int& b) { return (a < b) ? b : a; }
// ---- items of slice s00c44080 end

// ---- items of slice s00c44a20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char DAT_015745f0[];
struct ResourceKey {
  uint32_t instance, type, group;
  ResourceKey() : instance(0), type(0), group(0) {}
};
struct Resource {
  char pad[0x504];
  ResourceKey key;
  void FUN_004da330(void* p);
};
struct ResourceManager {
  Resource* FUN_004df550(const ResourceKey* key);
};
ResourceManager* FUN_00401090();
struct LocalSerializer {
  uint32_t buf[0xa14 / 4];
  LocalSerializer(void* owner, const void* table, uint32_t id);
  bool FUN_00692900(void* stream);
  bool FUN_00693e10(void* stream);
  void FUN_00695960(void* stream);
};
#define PV(n) virtual void pv##n();
class GameObj {
public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
  PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41)
  virtual uint32_t v42();
  PV(43) PV(44) PV(45) PV(46) PV(47)
  virtual int v48(int a);
  PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
  PV(59) PV(60) PV(61)
  virtual bool v62();
  virtual bool v63();
  virtual bool v64();
  PV(65) PV(66) PV(67) PV(68) PV(69) PV(70) PV(71) PV(72) PV(73) PV(74)
  PV(75) PV(76) PV(77) PV(78) PV(79) PV(80) PV(81) PV(82)
  virtual void v83(uint32_t id);
  virtual void v84(uint32_t id);

  bool FUN_00b18590(void* stream);
  bool FUN_00b18600(void* stream);

  int Read_c44a20(void* stream);
  bool Write_c44ad0(void* stream);
  void Serialize_c44b40(void* stream);
  void RegisterIds_c44b80();
  void UnregisterIds_c44bd0();
  void ForwardToResource_c44c40(void* p);
  int CallV48_c44c60(int a);
  bool CallV42_c44c90();
  uint32_t GetTypeId_c44cb0();

  char pad[0x16c - 4];
  Resource* mpResource;  // 0x16C
  ResourceKey mKey;      // 0x170
};
struct Thing {
  char pad[0x2c];
  uint32_t flags;  // 0x2C
  bool FUN_00b8d970();
  int FUN_00b8d9b0();
  void* FUN_00b8de30();
};
struct ThingMgr { bool FUN_00fee110(Thing* t); };
ThingMgr* FUN_00feb9f0();
struct IndexTable { int FUN_00b1fdb0(); };
struct Relations { bool FUN_00c31bf0(int i); bool FUN_00c31b10(int i); };
Relations* FUN_01021300();
// ---- items of slice s00c44a20 end

// ---- items of slice s00c46ab0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
class cSPMissionManager;
}
namespace SP {
class cSPTimer_s00c4_6ab0;
}
namespace SP {
class cSPTimer_s00c4_6ab0 {
public:
    void Restart();                                     // 0x00bc3130

    uint32_t mStorage;                                  // +0x00
};
}
namespace SP {
class ISpaceObject {
public:
virtual void o000();
virtual void o004();
virtual void o008();
    virtual void* QueryInterface(uint32_t interfaceId); // +0x0c
virtual void o010();
virtual void o014();
virtual void o018();
virtual void o01c();
virtual void o020();
virtual void o024();
virtual void o028();
virtual void o02c();
virtual void o030();
virtual void o034();
virtual void o038();
virtual void o03c();
virtual void o040();
virtual void o044();
virtual void o048();
virtual void o04c();
virtual void o050();
virtual void o054();
virtual void o058();
virtual void o05c();
virtual void o060();
virtual void o064();
virtual void o068();
    virtual void OnMissionCompleted();                  // +0x6c
    PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35)
    PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43)
    PV(44) PV(45) PV(46) PV(47)
    virtual void ReleaseObject();                       // +0xc0
};
}
namespace SP {
class ISpeciesExport {
public:
    virtual void* v0(int a, void* b);                  // +0x00
    virtual void* Export(int flags, const void* pPayload);  // 0x00c59fd0
};
struct cSpeciesExportImpl {
    void v0(int a, void* b);                           // 0x00c59f90 (non-virtual)
};
}
namespace SP {
struct tGridPos {
    uint32_t mA;                                        // +0x00
    uint32_t mB;                                        // +0x04
    uint32_t mC;                                        // +0x08
};
}
namespace SP {
struct cSpeciesData {
    uint8_t pad0000[0x504];                             // +0x0000
    tGridPos mSpeciesKey;                               // +0x0504
};
}
namespace SP {
struct cAudioSystem {
virtual void a00();
virtual void a04();
virtual void a08();
virtual void a0c();
virtual void a10();
virtual void a14();
virtual void a18();
virtual void a1c();
    virtual void* GetOutputDevice();                    // +0x20
};
}
namespace SP {
cAudioSystem* __cdecl GetSystemAT();                     // 0x00a206f0
}
namespace SP {
void __cdecl KillSetiEffects(uint32_t effectId, void* pDevice);  // 0x00435ed0
}
namespace SP {
cSPMissionManager* __stdcall GetMissionManager(void* pOwner);                  // 0x00feb9f0
}
namespace SP {
cSPMissionManager* __stdcall GetMissionManagerOf(void* pOwner, void* pUnused); // same routine, extra arg
}
namespace SP {
class cSPMissionManager {
public:
    bool FUN_00febf80();                                // 0x00febf80
    bool IsCompletedFeedbackActive();                   // 0x00febe50
    void Event();                                       // 0x00fecbb0
    void FUN_00febde0(uint32_t a, void* b);             // 0x00febde0
};
}
namespace SP {
class cSPMission_s00c4_6ab0 {
public:
virtual void m000();
virtual void m004();
virtual void m008();
    virtual void* QueryInterface(uint32_t interfaceId); // +0x0c
virtual void m010();
virtual void m014();
virtual void m018();
virtual void m01c();
virtual void m020();
virtual void m024();
virtual void m028();
virtual void m02c();
virtual void m030();
virtual void m034();
virtual void m038();
virtual void m03c();
virtual void m040();
virtual void m044();
virtual void m048();
virtual void m04c();
virtual void m050();
virtual void m054();
virtual void m058();
virtual void m05c();
virtual void m060();
virtual void m064();
virtual void m068();
    virtual void OnMissionCompleted();                  // +0x6c
    PV(28) PV(29) PV(30) PV(31) PV(32)
    virtual void v84();                                 // +0x84
    PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40)
    virtual uint32_t vA4();                             // +0xa4
    PV(42) PV(43)
    virtual void* vB0();                                // +0xb0
    PV(45) PV(46) PV(47) PV(48)
    PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56)
    virtual void* vE4();                                // +0xe4
    virtual void* vE8();                                // +0xe8
    PV(59) PV(60) PV(61)
    virtual bool vF8();                                 // +0xf8
    virtual bool vFC();                                 // +0xfc
    PV(64) PV(65) PV(66)
    virtual void* v10C();                               // +0x10c
    PV(68) PV(69) PV(70) PV(71) PV(72) PV(73) PV(74)
    virtual bool v12C();                                // +0x12c
    virtual bool v130();                                // +0x130
    PV(77) PV(78) PV(79) PV(80) PV(81) PV(82) PV(83) PV(84)
    PV(85) PV(86) PV(87) PV(88) PV(89) PV(90) PV(91) PV(92)
    PV(93) PV(94) PV(95) PV(96) PV(97) PV(98) PV(99) PV(100)
    PV(101)
    virtual void v198(bool a);                          // +0x198
    virtual void v19C();                                // +0x19c

    uint8_t      pad004[0x34];                          // +0x004 .. +0x037 (after the vfptr)
    cSPTimer_s00c4_6ab0     mFeedbackTimer;                        // +0x038
    uint8_t      pad03c[0x3c];                          // +0x03c .. +0x077
    uint32_t     mMissionId;                            // +0x078
    uint8_t      pad07c[0x20];                          // +0x07c .. +0x09b
    ISpaceObject* mpPlanet;                             // +0x09c
    uint8_t      pad0a0[0x60];                          // +0x0a0 .. +0x0ff
    void*        mpPlanetVisual;                        // +0x100
    uint8_t      pad104[0x2c];                          // +0x104 .. +0x12f
    union {
        uint32_t     mFlags;                            // +0x130
        struct {
            uint32_t mBit0 : 1;
            uint32_t mBit1 : 1;
            uint32_t mBit2 : 1;
            uint32_t mBit3 : 1;
            uint32_t mBitRest : 28;
        };
    };
    uint8_t      pad134[0x48];                          // +0x134 .. +0x17b
    cSPMission_s00c4_6ab0*  mpMissionManager;                      // +0x17c
    void*        mpMissionKey;                          // +0x180
    uint8_t      pad184[0x64];                          // +0x184 .. +0x1e7
    ISpaceObject* mpPlanet1E8;                          // +0x1e8
    uint8_t      pad1ec[0x318];                         // +0x1ec .. +0x503
    cSpeciesData mSpecies;                              // +0x504

    ~cSPMission_s00c4_6ab0();
    void* GetOwnerEmpire();                             // 0x00c451e0
    float FUN_00c459c0();                               // 0x00c459c0
    void UpdateHints(uint32_t param);                   // 0x00c45f90
    void FUN_00c46ab0();
    void FUN_00c46b80();
    void GiveOnAcceptItems();  // 0x00c46e20 (SP::cSPMission::GiveOnAcceptItems)
    uint32_t GetConversationFileID();  // 0x00c47040 (SP::cSPMission::GetConversationFileID)
    bool FUN_00c470a0();
    void SetMissionID(uint32_t missionId);  // 0x00c470f0 (SP::cSPMission::SetMissionID)
    void FUN_00c47140(uint32_t planetId);
    void FUN_00c47180(uint32_t planetId);
    void FUN_00c471c0();
    void FUN_00c47240();
    bool FUN_00c472c0();
    void FUN_00c472e0();
    void ExportPlanet(uint32_t targetType, void* pOut);  // 0x00c47350 (SP::cSPMission::ExportPlanet)
    void ExportSpecies(uint32_t itemType, uint32_t flags);  // 0x00c473f0 (SP::cSPMission::ExportSpecies)
    void StartCompletedFeedbackTimer();  // 0x00c47440 (SP::cSPMission::StartCompletedFeedbackTimer)
    void* FUN_00c474b0(uint32_t nType);
    void FUN_00c47610();
    void Update(int deltaMs);  // 0x00c478b0 (SP::cSPMission::Update)
};
}
// ---- items of slice s00c46ab0 end

// ---- items of slice s00c47a10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_FloatOne;                          // 0x0146d130  1.0f
#pragma intrinsic(_InterlockedExchange)
struct cSPUIEventLog {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    void PostFeedbackEvent();                           // 0x00dd8640
};
struct MessageServer;
struct cSPMission_s00c4_7a10;
namespace SP {
    void* GetMissionManager();                          // 0x00feb9f0
}
namespace SP {
    void* SpaceGameGet();                               // 0x01002bd0
}
namespace SP {
    cSPUIEventLog* __stdcall EventLog(uint32_t a, uint32_t b, uint32_t c,
                                      uint32_t d, uint32_t e, uint32_t f); // 0x00b3d3e0
}
namespace SP {
    void  GetPropertyAsKeyInstance(void* props, uint32_t id, void* out); // 0x006a12a0
}
MessageServer* GetMessageServer();                      // 0x0067dcc0
void  SortPlanetsByRadius(void* range);                 // 0x01022530
void* FUN_01021260();                                   // 0x01021260
void* FUN_01021300_s00c4_7a10();                                   // 0x01021300
void* FUN_00aed4d0();                                   // 0x00aed4d0
struct WString {                                        // eastl::wstring (0x10 bytes)
    wchar_t* mBegin;                                    // +0x00
    wchar_t* mEnd;                                      // +0x04
    uint32_t mCapacity;                                 // +0x08
    uint32_t mPad0C;                                    // +0x0c
    void assign(const wchar_t* first, const wchar_t* last);     // 0x00423650
    void clear() {
        if (mBegin != mEnd) {
            *mBegin = 0;
            mEnd = mBegin;
        }
    }
};
struct cString_s006b_47a0 {                             // SP::cString (0x18 bytes)
    uint32_t mPad00[6];
    void Construct();                                   // 0x006b5060
    void Destruct();                                    // 0x006b5240
    const wchar_t* GetText();                           // 0x006b55c0
};
struct cTextFormatter {                                 // localized text builder
    PV(0) PV(1) PV(2)
    virtual void* v3(void* a, void* b, void* c, void* d);           // +0x0c
    PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual void* v9(void* a, void* b, void* c, void* d, void* e, void* f); // +0x24
};
namespace SP {
struct IntVector {
    int32_t* mBegin;                                    // +0x00
    int32_t* mEnd;                                      // +0x04
    int32_t* mCapacity;                                 // +0x08
    uint8_t* mData;                                     // +0x0c
    void resize(uint32_t count);                        // 0x007eb820
};
}
struct SimGame {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
    void* f5180(int a);                                 // 0x01005180
};
struct GuildRecord {                                    // record behind SP::IntVector::mData
    uint8_t mPad00[0x1c];
    int32_t mField1C;                                   // +0x1c
    float   mField20;                                   // +0x20
    int32_t mField24;                                   // +0x24
    float   mField28;                                   // +0x28
};
struct cMessageHeader {                                 // non-polymorphic message header
    uint32_t mParam0;                                   // +0x08
    uint32_t mParam1;                                   // +0x0c
    uint32_t mField10[8];                               // +0x10
    uint32_t mMessageID;                                // +0x30
    uint32_t mField34;                                  // +0x34
    cMessageHeader(uint32_t id) : mMessageID(id) {}
};
class RefBaseA22 {                                      // ??_7RefBaseA22@@6B@ (+0)
public:
    virtual void _v00();
    volatile long mnRefCount;                           // +0x04
    RefBaseA22() { _InterlockedExchange(&mnRefCount, 0); }
};
class cMissionUpdateMessage : public cMessageHeader, public RefBaseA22 {
public:
    void* mpData;                                       // +0x38
    uint32_t mField3C;                                  // +0x3c
    cMissionUpdateMessage() : cMessageHeader(0x38cf2fd), mpData(0) {}
    virtual void _v00();
    void Destruct();                                    // 0x00421cf0
};
struct MessageServer {
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void PostMessage(uint32_t id, void* msg, uint32_t flags);   // +0x14
};
struct cSPMission_s00c4_7a10 {
    // ---- vtable ----
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40)
    virtual void* pv41();                               // +0xa4  current mission context object
    PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
    PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59)
    virtual float pv60();                               // +0xf0  reward timer base
    PV(61) PV(62) PV(63) PV(64) PV(65) PV(66) PV(67) PV(68) PV(69)
    PV(70) PV(71) PV(72) PV(73) PV(74) PV(75) PV(76) PV(77) PV(78) PV(79)
    PV(80)
    virtual void pv81();                                // +0x144
    PV(82) PV(83) PV(84) PV(85) PV(86) PV(87)
    virtual bool pv88();                                // +0x160
    virtual bool pv89();                                // +0x164
    PV(90) PV(91) PV(92) PV(93) PV(94) PV(95) PV(96) PV(97) PV(98)
    virtual bool pv99();                                // +0x18c
    PV(100)
    virtual void pv101();                               // +0x194

    // ---- data ----
    uint8_t  mPad04[0x78 - 0x04];                       // +0x04
    int32_t  mField78;                                  // +0x78  beacon/reward window id
    uint8_t  mPad7C[0x84 - 0x7c];                       // +0x7c
    uint32_t mState84;                                  // +0x84  mission state
    uint8_t  mPad88[0x8c - 0x88];                       // +0x88
    int32_t  mField8C;                                  // +0x8c
    uint8_t  mPad90[0x94 - 0x90];                       // +0x90
    int32_t  mField94;                                  // +0x94
    uint8_t  mPad98[0x9c - 0x98];                       // +0x98
    void*    mPlanet9C;                                 // +0x9c  target planet
    float    mFieldA0;                                  // +0xa0
    int32_t  mFieldA4;                                  // +0xa4
    uint8_t  mPadA8[0xf4 - 0xa8];                       // +0xa8
    int32_t  mFieldF4;                                  // +0xf4  clue kind
    int32_t  mFieldF8;                                  // +0xf8
    int32_t  mFieldFC;                                  // +0xfc  clue planet index
    void*    mField100;                                 // +0x100
    void*    mField104;                                 // +0x104
    void**   mVec108;                                   // +0x108
    void**   mVec10C;                                   // +0x10c
    uint8_t  mPad110[0x130 - 0x110];                    // +0x110
    uint32_t mFlags130;                                 // +0x130
    uint8_t  mPad134[0x14c - 0x134];                    // +0x134
    WString  mStr14C;                                   // +0x14c
    WString  mStr15C;                                   // +0x15c
    void*    mField16C;                                 // +0x16c
    void*    mKey170;                                   // +0x170
    void*    mKey174;                                   // +0x174
    void*    mKey178;                                   // +0x178
    void*    mField17C;                                 // +0x17c
    void*    mProps180;                                 // +0x180  mission property list
    int32_t  mField184;                                 // +0x184
    uint8_t  mPad188[0x1e8 - 0x188];                    // +0x188
    void*    mField1E8;                                 // +0x1e8  export planet

    // ---- recovered methods ----
    void   OnAccept();                                  // 0x00c47a10
    void   FUN_00c47b10(int32_t flag);                  // 0x00c47b10
    void   SetState(uint32_t state);                    // 0x00c47cc0
    void   TriggerUIUpdate();                           // 0x00c47d80
    void   DataExportOnInit();                          // 0x00c483d0
    void   FUN_00c48470(int32_t* key);                  // 0x00c48470
    bool   Validate();                                  // 0x00c484e0
    bool   PickPlanetClue();                            // 0x00c48600
    void   FUN_00c486f0(WString* out);                  // 0x00c486f0
    void   FUN_00c48740(WString* out);                  // 0x00c48740
    void   FUN_00c48790(WString* out);                  // 0x00c48790
    void   GetText(WString* out, int a);                // 0x00c487d0
    void   FUN_00c48900(WString* out);                  // 0x00c48900
    void   FUN_00c48940(WString* out);                  // 0x00c48940
    void*  FUN_00c452a0();                              // 0x00c452a0
    void*  GetOwnerEmpire();                            // 0x00c451e0
    void   GiveOnAcceptItems(bool on);                  // 0x00c46e20
    void   ExportPlanet(void* planet, uint32_t key);    // 0x00c47350
    void   ExportSpecies(void* species, uint32_t key);  // 0x00c473f0
};
struct TokenTranslator {                                // *0x016e0d08
    uint8_t  mPad00[0x18];
    void*    mField18;                                  // +0x18  current mission context
    int32_t  mField1C;                                  // +0x1c
    uint8_t  mPad20[0x48 - 0x20];
    void*    mField48;                                  // +0x48
};
extern TokenTranslator* g_pTokenTranslator;             // 0x016e0d08
extern cString_s006b_47a0 g_MissionLabel010030;         // 0x0168f010
extern cString_s006b_47a0 g_MissionLabel01002F;         // 0x0168ef34
struct RandomLinearCongruential {
    uint32_t RandomUint32Uniform(uint32_t range);       // 0x00a68fb0
};
extern RandomLinearCongruential g_Random;               // 0x01601760
struct cPlanetList;                                     // raw planet record range
struct PlanetNameHolder {                               // *(*cPlanet+0x13c)
    WString* FUN_00bb9de0();                            // 0x00bb9de0
    cPlanetList* FUN_00bba790();                        // 0x00bba790
    void     FUN_00bb9c10(int a);                       // 0x00bb9c10
};
struct cStarRecord_s00c4_7a10 {                                    // *(*cPlanet+0x13c)
    bool              FUN_00b8d970();                   // 0x00b8d970
    PlanetNameHolder* FUN_00b8de30();                   // 0x00b8de30
};
struct cPlanet_s00c4_7a10 {
    uint8_t      mPad00[0x13c];
    cStarRecord_s00c4_7a10* mField13C;                             // +0x13c
    WString*     GetName();                             // 0x00c707e0
    int32_t      FUN_00c70880();                        // 0x00c70880
};
struct Empire {
    void* FUN_00c30c60();                               // 0x00c30c60
};
struct Species {
    WString* FUN_00bb9de0();                            // 0x00bb9de0
};
struct cPlanetList {                                    // raw planet record range
    void** mBegin;                                      // +0x00
    void** mEnd;                                        // +0x04
};
struct cPlanetRange {                                   // radius-sorted planet vector (0x14 bytes)
    void** mBegin;                                      // +0x00
    void** mEnd;                                        // +0x04
    void*  mCapacity;                                   // +0x08
    void*  mAllocator;                                  // +0x0c
    void*  mField10;                                    // +0x10
    void Construct(cPlanetList* src);                   // 0x00ba95a0
    void Destroy();                                     // 0x00ae6970
};
struct MissionManager {
    uint8_t  mPad00[0x1c];
    int32_t  mField1C;                                  // +0x1c
    void     FUN_00fede40(int32_t a);                   // 0x00fede40
    void     FUN_00feba10();                            // 0x00feba10
    void     FUN_00feca20(void* mission);               // 0x00feca20
    uint32_t FUN_00febf80(int32_t a);                   // 0x00febf80
    void     FUN_00bb9c10();                            // 0x00bb9c10
    void     FUN_00c31a00(int32_t a);                   // 0x00c31a00
};
struct PropertyList {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
    virtual bool v7(uint32_t key);                      // +0x1c  HasKey
};
static uint32_t WcsLen(const wchar_t* p)
{
    const wchar_t* start = p;
    while (*p != 0) {
        ++p;
    }
    return (uint32_t)(p - start);
}
// ---- items of slice s00c47a10 end

// ---- items of slice s00c48970 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct WStr;
struct CStr;
struct SPObject;
void __cdecl EAFree(void* p);                                    // 0x00f47380  operator delete[]
void* __cdecl MessageServer();                                   // 0x0067dcc0
extern "C" void __cdecl WStr3(WStr* out, const wchar_t* fmt, int a);         // 0x0041e050
extern "C" void __cdecl WStr4(WStr* out, const wchar_t* fmt, int a, float b);// 0x0041e050
void __cdecl FUN_00881730(int a, int b, int c, wchar_t* buf, int n, const wchar_t* fmt); // 0x00881730
void __cdecl FUN_00c48900(WStr* out);                            // 0x00c48900
void __cdecl FUN_00c48940(WStr* out);                            // 0x00c48940
void __cdecl FUN_00c486f0(WStr* out);                            // 0x00c486f0
void __cdecl FUN_00c48740(WStr* out);                            // 0x00c48740
void* __cdecl FUN_00bb9de0(void* p);                             // 0x00bb9de0
struct Timer {
    char pad[0x20];
    void TimerCtor();                                            // 0x00b63890
};
struct CStr {
    char pad[0x14];
    const wchar_t* GetText();                                    // 0x006b55c0
    void CStrCtor();                                             // 0x006b5060
};
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mpAllocator;

    WStr& append(const wchar_t* p);                              // 0x005c3d90
    WStr& assign(const wchar_t* first, const wchar_t* last);     // 0x00423650
    WStr& Append(const wchar_t* first, const wchar_t* last);     // 0x00429580
    void  RangeInitialize(const wchar_t* p);                     // 0x00579a90
};
struct Entry12 {                  // 12-byte eastl::vector<EA::ResourceMan::Key> element
    u32 mKey;
    u32 mField4;
    u32 mField8;
};
struct Vec12 {                    // eastl::sp_vector<EA::ResourceMan::Key>
    Entry12* mpBegin;
    Entry12* mpEnd;
    Entry12* mpCapacity;

    void Reserve(int n);                                         // 0x0041e4d0
    void DoInsertValue(Entry12* pos, const Entry12& value);       // 0x004e3e10

    void push_back(const Entry12& v) {
        if (mpEnd < mpCapacity) {
            Entry12* p = mpEnd;
            mpEnd = p + 1;
            if (p)
                *p = v;
            return;
        }
        DoInsertValue(mpEnd, v);
    }
};
struct VecU32 {                   // eastl::vector<unsigned int>
    u32* mpBegin;
    u32* mpEnd;
    u32* mpCapacity;

    void Insert(u32* pos, const u32& value);                     // 0x004558a0

    void push_back(const u32& v) {
        if (mpEnd < mpCapacity) {
            u32* p = mpEnd;
            mpEnd = p + 1;
            if (p)
                *p = v;
            return;
        }
        Insert(mpEnd, v);
    }
};
struct Translator {
    char pad00[0x10];
    int  mField10;                                               // 0x10
    char pad14[0x2c];
    int  mField40;                                               // 0x40
};
struct SPObject {
    void*  mpVtbl0;            // 0x000
    void*  mpVtbl4;            // 0x004
    char   pad08[0x2c];        // 0x008
    void*  mpVtbl34;           // 0x034
    Timer  mTimer38;           // 0x038
    Timer  mTimer58;           // 0x058
    u32    mField78;           // 0x078
    u32    mField7C;           // 0x07c
    u32    mField80;           // 0x080
    u32    mGroup84;           // 0x084
    u8     mField88;           // 0x088
    char   pad89[3];           // 0x089
    int    mField8C;           // 0x08c
    u32    mField90;           // 0x090
    int    mField94;           // 0x094
    u32    mField98;           // 0x098
    u32    mField9C;           // 0x09c
    float  mFieldA0;           // 0x0a0
    u32    mStarClueA4;        // 0x0a4
    u32    mStarClueA8;        // 0x0a8
    u32    mStarClueAC;        // 0x0ac
    CStr   mStrB0;             // 0x0b0 (0x14)
    int    mFieldC4;           // 0x0c4
    float  mFieldC8;           // 0x0c8
    u32*   mArrCC;             // 0x0cc
    u32*   mArrD0;             // 0x0d0
    u32*   mArrD4;             // 0x0d4
    char   padD8[8];           // 0x0d8
    u32*   mArrE0;             // 0x0e0
    u32*   mArrE4;             // 0x0e4
    u32*   mArrE8;             // 0x0e8
    char   padEC[8];           // 0x0ec
    int    mFieldF4;           // 0x0f4
    int    mKindF8;            // 0x0f8
    int    mFieldFC;           // 0x0fc
    int    mField100;          // 0x100
    int    mField104;          // 0x104
    u32    mField108;          // 0x108
    u32    mField10C;          // 0x10c
    u32    mField110;          // 0x110
    char   pad114[8];          // 0x114
    Vec12  mVec11C;            // 0x11c
    char   pad128[8];          // 0x128
    u32    mFlags130;          // 0x130
    VecU32 mVec134;            // 0x134
    char   pad140[8];          // 0x140
    int    mField148;          // 0x148
    WStr   mStr14C;            // 0x14c (16 bytes)
    WStr   mStr15C;            // 0x15c (16 bytes)
    u32    mField16C;          // 0x16c
    u32    mField170;          // 0x170
    u32    mField174;          // 0x174
    u32    mField178;          // 0x178
    u32    mField17C;          // 0x17c
    void*  mpField180;         // 0x180
    int    mField184;          // 0x184
    u32    mField188;          // 0x188
    u8     mField18C;          // 0x18c
    char   pad18D[3];          // 0x18d
    u32    mField190;          // 0x190
    u32    mField194;          // 0x194
    u32    mField198;          // 0x198
    u32    mField19C;          // 0x19c
    char   pad1A0[8];          // 0x1a0
    u32    mField1A8;          // 0x1a8
    u32    mField1AC;          // 0x1ac
    u32    mField1B0;          // 0x1b0
    char   pad1B4[8];          // 0x1b4
    u32    mField1BC;          // 0x1bc
    u32    mField1C0;          // 0x1c0
    u32    mField1C4;          // 0x1c4
    char   pad1C8[8];          // 0x1c8
    VecU32 mVec1D0;            // 0x1d0
    char   pad1DC[8];          // 0x1dc
    u32    mField1E4;          // 0x1e4
    void*  mpTargetPlanet;     // 0x1e8

    // this-class helpers
    void BaseCtor();                                         // 0x00b18660  SP::cGameData::cGameData
    void GetText(u32 key, WStr* out);                        // 0x00c487d0
    void* GetCivData();                                      // 0x00c452a0
    void* GetOwnerEmpire();                                  // 0x00c451e0
    void  GetRewardsNames(WStr* out);                        // 0x00c48c20
    void  FUN_00c48970(int idx, WStr* out);                  // 0x00c48970
    void  FUN_00c48a90(WStr* out);                           // 0x00c48a90
    void  FUN_00c48ae0(WStr* out);                           // 0x00c48ae0
    void  FUN_00c48ba0(int arg);                             // 0x00c48ba0
    void  GetUITitle(WStr* out);                             // 0x00c48d40
    void  FUN_00c48db0(WStr* out);                           // 0x00c48db0
    void  FUN_00c48e00(WStr* out);                           // 0x00c48e00
    void  FUN_00c490e0(u32 arg);                             // 0x00c490e0
    void  FUN_00c49140(WStr* out);                           // 0x00c49140
    void  FUN_00c49180(WStr* out);                           // 0x00c49180
    int   GetTagString(u32 tag, WStr* out);                  // 0x00c491c0
    void  PickRewardUnlockTools();                           // 0x00c495c0
    void  FUN_00c49800(WStr* out);                           // 0x00c49800
    void  FUN_00c49840(WStr* out);                           // 0x00c49840
    void  FUN_00c49890(WStr* out);                           // 0x00c49890
    SPObject();                                              // 0x00c48e90
};
typedef char (__thiscall *FnChar)(void*);
typedef char (__thiscall *FnCharArg)(void*, int);
typedef void (__thiscall *FnVoid2)(void*, void*, int);
static inline char VT_F8(void* p) {
    return ((FnChar*)*(void**)p)[0xf8 / 4](p);
}
static inline char VT_154(void* p, int a) {
    return ((FnCharArg*)*(void**)p)[0x154 / 4](p, a);
}
static inline void VT_20(void* p, void* a, int b) {
    ((FnVoid2*)*(void**)p)[0x20 / 4](p, a, b);
}
static inline void VT_2C(void* p, void* a, int b, int c) {
    ((void (__thiscall*)(void*, void*, int, int))*((void***)*(void**)p + 0x2c / 4))(p, a, b, c);
}
static inline void VT_B4(void* p, WStr* out) {
    ((void (__thiscall*)(void*, WStr*))*((void***)*(void**)p + 0xb4 / 4))(p, out);
}
static inline void VT_CC(void* p, int a, WStr* out) {
    ((void (__thiscall*)(void*, int, WStr*))*((void***)*(void**)p + 0xcc / 4))(p, a, out);
}
static inline void VT_D0(void* p, WStr* out) {
    ((void (__thiscall*)(void*, WStr*))*((void***)*(void**)p + 0xd0 / 4))(p, out);
}
static inline void VT_D4(void* p, WStr* out) {
    ((void (__thiscall*)(void*, WStr*))*((void***)*(void**)p + 0xd4 / 4))(p, out);
}
static inline void VT_D8(void* p, WStr* out) {
    ((void (__thiscall*)(void*, WStr*))*((void***)*(void**)p + 0xd8 / 4))(p, out);
}
static inline void VT_DC(void* p, WStr* out) {
    ((void (__thiscall*)(void*, WStr*))*((void***)*(void**)p + 0xdc / 4))(p, out);
}
static inline void VT_E0(void* p, WStr* out) {
    ((void (__thiscall*)(void*, WStr*))*((void***)*(void**)p + 0xe0 / 4))(p, out);
}
static inline u32 VT_AC(void* p) {
    return ((u32 (__thiscall*)(void*))*((void***)*(void**)p + 0xac / 4))(p);
}
static inline u32 WStrLen(const wchar_t* s)
{
    const wchar_t* e = s;
    if (*e) {
        do {
            ++e;
        } while (*e);
    }
    return (u32)(e - s);
}
struct CivData {
    void  FUN_c30c80();                                          // 0x00c30c80
    int*  GetCities();                                           // 0x005c65e0
};
struct SorterObj {
    void* operator()();                                          // 0x00b8de30
    WStr* FUN_00bb9de0();                                        // 0x00bb9de0
};
struct PlanetObj {
    WStr* GetName();                                             // 0x00c707e0
};
struct ToolSet {
    char  HasTag(u32 tag) {                                      // vtable +0x1c
        return ((char (__thiscall*)(void*, u32))*((void***)*(void**)this + 0x1c / 4))(this, tag);
    }
    char  GetEntry(u32 tag, void* out) {                         // vtable +0x24
        return ((char (__thiscall*)(void*, u32, void*))*((void***)*(void**)this + 0x24 / 4))(this, tag, out);
    }
    void* GetList(u32 tag) {                                     // vtable +0x28
        return ((void* (__thiscall*)(void*, u32))*((void***)*(void**)this + 0x28 / 4))(this, tag);
    }
};
struct Property {
    int* GetInt();                                               // 0x0041e990
};
struct UnlockEntry {                // 0x18-byte record written by ToolSet::GetEntry
    Property* mpProperty;           // 0x00
    u32    mField4;
    u32    mField8;
    u32    mFieldC;
    u16    mField10;
    u16    mField12;                // must equal 9
    u16    mField14;
    u16    mField16;
};
struct KeyList {                    // list returned by ToolSet::GetList
    Entry12* mpData;                // 0x00
    u32    mField4;                 // 0x04
    int    mCount;                  // 0x08
    u16    mFieldC;                 // 0x0c
    u16    mFieldE;                 // 0x0e
    u16    mFlags10;                // 0x10  (bit 0x30 set => vector payload)
    u16    mField12;                // 0x12
};
struct RandomLC {
    u32 RandomUint32Uniform(u32 n);                              // 0x00a68fb0
};
extern RandomLC gRandom;                                         // 0x01601760
static inline int Rt(const float& f)
{
    return _mm_cvt_ss2si(_mm_load_ss(&f));
}
// ---- items of slice s00c48970 end

// ---- items of slice s00c498e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memcpy(void* d, const void* s, unsigned n);
#pragma warning(disable: 4100)
void* __cdecl FUN_01046fc0(void* key, u32 a);                          // 0x01046fc0
void* __cdecl FUN_01045120(void* a, u32 b);                             // 0x01045120
void* __cdecl FUN_01044d70(void* a, u32 b);                             // 0x01044d70
void* __cdecl CreateStarRecordVisual(void* a, u32 b, u32 c);            // 0x010458f0
void  __cdecl RemoveVisual(void* a, u32 b, u32 c);                      // 0x01045a60
void* __cdecl ColorToVector3(void* out, u32 color);                     // 0x00576ab0
void  __cdecl VectorInsertU32(void* a, void* b, u32 c);                 // 0x004558a0
void  __cdecl VectorPushBack3(void* a, void* b, void* c);               // 0x00455660
void  __cdecl SimpleVectorPushBack(void* self, const u32* v);           // 0x00454860
void* __cdecl GetMissionManager(void* m);                               // 0x00feb9f0
u32   __cdecl FUN_00febf80(void* mgr);                                  // 0x00febf80
void  __cdecl FUN_00febf20(void* mgr, void* m);                         // 0x00febf20
void* __cdecl GetUniverseContext();                                     // 0x01021080
void* __cdecl FUN_00bddd00(void* mgr);                                  // 0x00bddd00
void* __cdecl SP_PropertyManager();                                     // 0x0067de30
u32   __cdecl GetPropertyAsText(void* p, u32 key, void* out);           // 0x006a1360
void* __cdecl FUN_006c0200(void* a, void* b);                           // 0x006c0200
void  __cdecl E12_Init(void* out, void* a);                             // 0x00ae9640
void  __cdecl FUN_00ae9670(void* a);                                    // 0x00ae9670
void  __cdecl FUN_00aeb5b0(void* a, void* b);                           // 0x00aeb5b0
void* __cdecl FUN_00c472c0(void* self);                                 // 0x00c472c0
void* __cdecl FUN_010434e0(void* a, void* b);                           // 0x010434e0
void* __cdecl FUN_00b8de30(void* a);                                    // 0x00b8de30
void  __cdecl FUN_00b96130(void* a, void* b, void* c);                  // 0x00b96130
void* __cdecl FUN_00bb1080(void* a, void* b, void* c);                  // 0x00bb1080
void* __cdecl Property_GetFloat(void* prop);                           // 0x0041ea70
void* __cdecl GetCities(void* civ, void* a, void* b);                  // 0x005c65e0
void* __cdecl SP_StarManager();                                        // 0x00b3d2a0
void* __cdecl FUN_00bb1080b(void* a);                                   // 0x00bb1080
void  __cdecl FUN_00c072f0(void* self, const void* v);                  // 0x00c072f0
void* __cdecl FUN_00e1c7f0(void* vec, void* val);                       // 0x00e1c7f0
void  __cdecl FUN_00ae6970(void* v);                                    // 0x00ae6970
void* __cdecl AutoRefCountCtor(void* self, void* p);                    // 0x00572660
u32   __cdecl FUN_00801920(void* p);                                    // 0x00801920 (AddRef kind)
u32   __cdecl RandomUint32Uniform(void* rng, u32 n);                    // 0x00a68fb0
struct RandomLCG {
    u32 RandomUint32Uniform(u32 n);   // 0x00a68fb0
};
#define gRandom_s00c4_98e0 (*(RandomLCG*)0x1601760)
void* __cdecl FUN_00c453b0();                                           // 0x00c453b0 GetRewardProfit
void  __cdecl FUN_00c45760(void* self, void* out);                      // 0x00c45760 PickRewardTool
void  __cdecl FUN_00c495c0(void* self);                                 // 0x00c495c0 PickRewardUnlockTools
class cSPMission_s00c4_98e0 {
public:
virtual void vf00();
virtual void vf04();
virtual void vf08();
    virtual void* Cast(u32 type);                     // +0x0c
virtual void vf10();
virtual void vf14();
virtual void vf18();
virtual void vf1c();
virtual void vf20();
virtual void vf24();
virtual void vf28();
virtual void vf2c();
virtual void vf30();
virtual void vf34();
virtual void vf38();
virtual void vf3c();
virtual void vf40();
virtual void vf44();
virtual void vf48();
virtual void vf4c();
virtual void vf50();
virtual void vf54();
virtual void vf58();
virtual void vf5c();
virtual void vf60();
virtual void vf64();
virtual void vf68();
virtual void vf6c();
virtual void vf70();
virtual void vf74();
virtual void vf78();
virtual void vf7c();
virtual void vf80();
virtual void vf84();
virtual void vf88();
virtual void vf8c();
virtual void vf90();
virtual void vf94();
virtual void vf98();
virtual void vf9c();
virtual void vfa0();
virtual void vfa4();
virtual void vfa8();
virtual void vfac();
virtual void vfb0();
virtual void vfb4();
virtual void vfb8();
virtual void vfbc();
virtual void vfc0();
virtual void vfc4();
virtual void vfc8();
virtual void vfcc();
virtual void vfd0();
virtual void vfd4();
virtual void vfd8();
virtual void vfdc();
virtual void vfe0();
virtual void vfe4();
virtual void vfe8();
virtual void vfec();
    virtual int  vf100();                             // +0x100
virtual void vf104();
virtual void vf108();
virtual void vf10c();
    virtual int  vf110(void* m);                      // +0x110
virtual void vf114();
virtual void vf118();
virtual void vf11c();
virtual void vf120();
virtual void vf124();
virtual void vf128();
virtual void vf12c();
virtual void vf130();
virtual void vf134();
    virtual bool vf138(void* m);                      // +0x138
virtual void vf13c();
virtual void vf140();
virtual void vf144();
virtual void vf148();
virtual void vf14c();
virtual void vf150();
virtual void vf154();
    virtual int  vf158();                             // +0x158
virtual void vf15c();
virtual void vf160();
virtual void vf164();
virtual void vf168();
virtual void vf16c();
virtual void vf170();
virtual void vf174();
virtual void vf178();
virtual void vf17c();
virtual void vf180();
virtual void vf184();
virtual void vf188();
virtual void vf18c();
    virtual void vf190(void* p);                      // +0x190
virtual void vf194();
virtual void vf198();
virtual void vf19c();
virtual void vfa0x();
virtual void vfa4x();
virtual void vfa8x();
virtual void vf1a4();
virtual void vf1a8();
virtual void vf1ac();
virtual void vf1b0();
virtual void vf1b4();
virtual void vf1b8();
virtual void vf1bc();
virtual void vf1c0();
virtual void vf1c4();
virtual void vf1c8();
virtual void vf1cc();
virtual void vf1d0();
virtual void vf1d4();
virtual void vf1d8();
virtual void vf1dc();
virtual void vf1e0();
virtual void vf1e4();
virtual void vf1e8();
virtual void vf1ec();
    virtual int  vf1f0();                             // +0x1f0

    u8   pad_0000[0x2c];
    void* mGlobalPtr2C;          // +0x2c
    u8   pad_0030[0x88 - 0x30];
    u8   mField88;               // +0x88
    u8   pad_0089[0x8c - 0x89];
    int  mField8C;               // +0x8c
    void* mField90;              // +0x90
    int  mField94;               // +0x94
    void* mField98;              // +0x98
    void* mRewardToolName;       // +0x9c   (mTableId guard)
    u8   pad_00a0[0xc4 - 0xa0];
    int  mFieldC4;               // +0xc4
    float mFieldC8;              // +0xc8
    void* mEventLogs;            // +0xcc (vector begin)
    void* mEventLogsEnd;         // +0xd0
    u8   pad_00d4[0xe0 - 0xd4];
    void* mStarMapEffects;       // +0xe0 (vector begin)
    u8   pad_00e4[0x104 - 0xe4];
    int  mField104;              // +0x104
    u32  mVec108_0;              // +0x108 (vector begin)
    u32  mVec108_1;              // +0x10c
    u32  mVec108_2;              // +0x110
    u8   pad_0114[0x11c - 0x114];
    u32  mVec11c_0;              // +0x11c
    u32  mVec11c_1;              // +0x120
    u8   pad_0124[0x130 - 0x124];
    u32  mFlags130;              // +0x130
    u8   pad_0134[0x17c - 0x134];
    cSPMission_s00c4_98e0* mpParentMission; // +0x17c
    void* mField180;             // +0x180
    u8   pad_0184[0x1e4 - 0x184];
    void* mField1e4;             // +0x1e4
    void* mField1e8;             // +0x1e8

    void ShowStarMapDestinationIndicator(char param);     // 0x00c498e0
    void ShowStarMapStarClues();                          // 0x00c49d10
    void FUN_00c49f90();                                  // 0x00c49f90
    void PickRewards();                                   // 0x00c4a0c0
    int  PickStarClue();                                  // 0x00c4a220
    bool HandleMessage(u32 msg, void* m);                 // 0x00c4a6b0
};
static inline int   ld32(const void* p, int o)  { return *(const int*)((const char*)p + o); }
static inline u32   ldu32(const void* p, int o) { return *(const u32*)((const char*)p + o); }
static inline void  st32(void* p, int o, int v){ *(int*)((char*)p + o) = v; }
static inline void** vtbl(const void* p)        { return *(void***)p; }
struct VecHeader { void* begin; void* end; void* cap; };
struct SpVecE0 {
    void* mpBegin; void* mpEnd; void* mpCap;
    void erase(void* first, void* last);   // 0x00e25bd0
};
struct SpVec11C {
    void* mpBegin; void* mpEnd; void* mpCap;
    void erase(void* first, void* last);   // 0x0050f740
};
// ---- items of slice s00c498e0 end

// ---- items of slice s00c4a850 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t    g_missionKeyGroup;                       // 0x01574e28
struct ResourceKey_s00c4_a850 {
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
struct cGameData {
    virtual void       AddRef();                            // +0x00
    virtual void       Release();                           // +0x04
    virtual void       v08();                               // +0x08
    virtual cGameData* Cast(uint32_t nType);                // +0x0c
};
template <class T>
struct AutoRefCount {
    T* mpObject;                                            // +0x00

    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* pObject) : mpObject(pObject) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& rOther) : mpObject(rOther.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }

    // Copy-assignment used by the banner vector: stores the pointer and takes a
    // reference (the destination is always a fresh slot, so nothing to release).
    AutoRefCount& operator=(const AutoRefCount& rOther)
    {
        mpObject = rOther.mpObject;
        if (mpObject) mpObject->AddRef();
        return *this;
    }

    T* operator->() const { return mpObject; }
};
struct cPlanet_s00c4_a850 {
    char     mPad000[0x13c];                                // +0x000
    void*    mpData13C;                                     // +0x13c
    char     mPad140[0x2c];                                 // +0x140
};
struct cPlanetRecord;
struct cProperty_s00c4_a850 {
    void*     mpValue;                                      // +0x00
    uint32_t  mPad04;                                       // +0x04
    uint32_t  mCount;                                       // +0x08
    uint32_t  mPad0c;                                       // +0x0c
    uint16_t  mFlags;                                       // +0x10
    uint16_t  mType;                                        // +0x12

    bool*     GetBool();                                    // 0x0041e920
    int32_t*  GetInt();                                     // 0x0041e990
};
struct cPropertyList_s00c4_a850 {
    virtual void        v00();                              // +0x00
    virtual void        v04();                              // +0x04
    virtual void        v08();                              // +0x08
    virtual void        v0c();                              // +0x0c
    virtual void        v10();                              // +0x10
    virtual void        v14();                              // +0x14
    virtual void        v18();                              // +0x18
    virtual void        v1c();                              // +0x1c
    virtual void        v20();                              // +0x20
    virtual bool        Find(uint32_t nKey, cProperty_s00c4_a850** ppOut);   // +0x24
    virtual cProperty_s00c4_a850*  Get(uint32_t nKey);                 // +0x28
};
struct cSPMission_s00c4_a850;
struct cSPMissionMultiDelivery;
struct cPlanetSearch;
struct cSPMission_s00c4_a850 {
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
    cPropertyList_s00c4_a850* mpPropertyList;                          // +0x180
    int32_t        mField184;                               // +0x184
    int32_t        mField188;                               // +0x188
    char           mPad18c[4];                              // +0x18c
    int32_t        mField190;                               // +0x190
    cVec<ResourceKey_s00c4_a850> mKeys194;                             // +0x194
    cVec<ResourceKey_s00c4_a850> mKeys1a8;                             // +0x1a8
    cVec<ResourceKey_s00c4_a850> mKeys1bc;                             // +0x1bc
    char           mPad1d0[0x20];                           // +0x1d0 .. +0x1ef
    int32_t        mStatus;                                 // +0x1f0
    void*          mpData1f4;                               // +0x1f4
    char           mPad1f8[0xc];                            // +0x1f8 .. +0x203
    int32_t        mField204;                               // +0x204
    int32_t        mField208;                               // +0x208

    char           Init();                                  // 0x00c4ad50
    void           PickGiveOnAcceptItems();                 // 0x00c4a980
    cPlanet_s00c4_a850*       GetTargetPlanet();                       // 0x00970b30
    void           SetTargetPlanet(void* pPlanet);          // 0x00c47180
    void           SetInitialized();                        // 0x00c4a0c0
    void           TriggerUIUpdate();                       // 0x00c47d80
    int32_t        Update(void* pArg);                      // 0x00c478b0
    void*          PickPlanet(cPlanetSearch* pSearch);      // 0x00c47e20
    uint32_t       ReadTargetPlanetType();                  // 0x00c45b40
    cPlanetRecord* GetPlanetRecordFromTargetType(uint32_t nType);   // 0x00c474b0
};
struct cSPMissionMultiDelivery : cSPMission_s00c4_a850 {
    void    ReturnForRewards();                             // 0x00c4b760
    int32_t Update(void* pArg);                             // 0x00c4b7a0
    bool    IsAtDeliveryTarget(void* pPlanet, ResourceKey_s00c4_a850* pKey);   // 0x00c4bb60
    bool    InitWrapper();                                  // 0x00c4baa0
    int32_t GetCountA();                                    // 0x00c4bba0
    int32_t GetCountB();                                    // 0x00c4bbc0
};
struct cMissionMessageHandler {
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
virtual void v128();
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
virtual void v16c();
virtual void v170();
virtual void v174();
virtual void v178();
virtual void v17c();
virtual void v180();
virtual void v184();
virtual void v188();
virtual void v18c();
virtual void v190();
virtual void v194();
virtual void v198();
virtual void v19c();
virtual void v1a0();
virtual void v1a4();
virtual void v1a8();
virtual void v1ac();
virtual void v1b0();
virtual void v1b4();
virtual void v1b8();
    virtual void HandleMessage(uint32_t nMessage, void* pMessage);

    int32_t    mStatus;                                     // +0x1bc (cSPMission +0x1f0)
    void*      mpData1f4;                                   // +0x1c0 (cSPMission +0x1f4)

    void BaseHandleMessage(uint32_t nMessage, void* pMessage);   // 0x00c4a6b0
    cSPMissionMultiDelivery* GetMission() { return (cSPMissionMultiDelivery*)((char*)this - 0x34); }
};
struct cMissionMessage {
    uint32_t mPad00;
    uint32_t mPad04;
    void*    mpPlanetRef;                                   // +0x08
    uint32_t mPad0c;
    uint32_t mField10;                                      // +0x10
    uint32_t mPad14;
    uint32_t mField18;                                      // +0x18
};
struct cPlanetSearch {                                      // pick request built by cMissionBalance::Init
    uint32_t mKind;                                         // +0x00 (0x20 / 0x38)
    char     mPad004[0x40];                                 // +0x004

    cPlanetSearch();                                        // 0x00ba7bd0
    ~cPlanetSearch();                                       // 0x00ba8220
};
struct cSPMissionAdventureBase : cSPMission_s00c4_a850 {
    void* PickAdventureAsset();                             // 0x00c4b220
    bool  RerollAdventureAsset();                           // 0x00c4b250
    void  InitAdventure();                                  // 0x00c4b2b0
};
struct cMissionBalance : cSPMission_s00c4_a850 {
    bool Init();                                            // 0x00c4b7f0
};
struct cBannerListHost {
    char mPad000[0x1c];                                     // +0x000
    cVec<AutoRefCount<cGameData> > mEntries;                // +0x01c
    bool ReadBannerList(void* pArchive);                    // 0x00c4a850
};
namespace Simulator {
struct cMissionAdventure {
    void**  mpVtbl;                                         // +0x000
    void**  mpVtbl04;                                       // +0x004
    char    mPad008[0x2c];                                  // +0x008 .. +0x033
    void**  mpVtbl34;                                       // +0x034
    char    mPad038[0x1b8];                                 // +0x038 .. +0x1ef
    int32_t mField1f0;                                      // +0x1f0
    void*   mpData1f4;                                      // +0x1f4

    cMissionAdventure();                                    // 0x00c4af60
    bool InitMission();                                     // 0x00c4b440
};
}
namespace Simulator {
struct cMissionBalance {
    void**  mpVtbl;                                         // +0x000
    void**  mpVtbl04;                                       // +0x004
    char    mPad008[0x2c];                                  // +0x008 .. +0x033
    void**  mpVtbl34;                                       // +0x034
    char    mPad038[0x1b8];                                 // +0x038 .. +0x1ef
    int32_t mField1f0;                                      // +0x1f0
    int32_t mThreshold;                                     // +0x1f4

    cMissionBalance();                                      // 0x00c4b570
    long double GetBalanceFactor(void* pA, void* pB);       // 0x00c4b6c0
};
}
struct cStarManager_s00c4_a850 {
    bool PickRandomAsset();                                 // 0x00bb7940
    cGameData* GetBannerByID(uint32_t nID);                 // 0x00ba6d80
    void* GetEmpireByID();                                  // 0x00ba9370
};
struct cMissionManager_s00c4_a850 {
    bool IsAdventureActive();                               // 0x00fee110
};
namespace Achievements {
struct Controller {
    void AwardAchievement();                                // 0x00676710
    void AutoTest();                                        // 0x00676e90
};
}
namespace Achievements {
Controller* __stdcall GetController(uint32_t nID);                              // 0x00675250
}
namespace Achievements {
Controller* __stdcall GetController(uint32_t nID, int32_t nFlag);               // 0x00675250
}
void __fastcall Simulator_cGenericPressureEvent_ctor(void* pThis);      // 0x00c48e90
cStarManager_s00c4_a850*          __stdcall StarManager(uint32_t nID);             // 0x00b3d2a0
cStarManager_s00c4_a850*          __stdcall StarManager(void* pObject);            // 0x00b3d2a0
cStarManager_s00c4_a850*          __stdcall StarManager(void* pOut, int32_t nKind);   // 0x00b3d2a0
cStarManager_s00c4_a850*          __stdcall StarManager(void* pA, void* pB);       // 0x00b3d2a0
cMissionManager_s00c4_a850*       __stdcall GetMissionManager_s00c4_a850(void* pPlanet);      // 0x00feb9f0
void*  __stdcall FUN_01021300(void* pAsset);                            // 0x01021300
void   __fastcall FUN_00baf790(cStarManager_s00c4_a850* pThis);                    // 0x00baf790
void*  __stdcall FUN_00b3d360(void* pPlanet);                           // 0x00b3d360
void   __fastcall FUN_00b7d580(void* pThis);                            // 0x00b7d580
void   __fastcall FUN_00c47a10(cSPMission_s00c4_a850* pThis);                      // 0x00c47a10
bool   __fastcall FUN_00c46b80(void* pThis);                            // 0x00c46b80
void   __cdecl EA_IO_ReadInt32(void* pStream, int32_t* pValue, int32_t nCount, int32_t nFlags);   // 0x0093a780
long double __stdcall FUN_00c44d00(void* pA, void* pB);                 // 0x00c44d00
char   __fastcall FUN_00bb9bd0(void* pThis);                            // 0x00bb9bd0
int32_t __fastcall FUN_00b8dab0(void* pThis);                           // 0x00b8dab0
bool   __fastcall FUN_00bba100(void* pThis);                            // 0x00bba100
bool   __fastcall FUN_00bb9d90(void* pThis);                            // 0x00bb9d90
bool   __fastcall FUN_00bb9c30(void* pThis);                            // 0x00bb9c30
void   __cdecl FUN_00e39ab0(uint32_t nKey, int32_t nFlags, ResourceKey_s00c4_a850* pOut3, ResourceKey_s00c4_a850* pOut2,
                            void* pData, int32_t nFlags2, ResourceKey_s00c4_a850* pOut1, ResourceKey_s00c4_a850* pOut0);   // 0x00e39ab0
void   __cdecl FUN_00f27e00(ResourceKey_s00c4_a850* pKey);                         // 0x00f27e00
struct cVarListSerializer {
    char mData[0xa08];                                      // +0x000

    void Construct(void* pOwner, uint32_t nKey, uint32_t nID);   // 0x00692f90
    bool Serialize(void* pArchive);                         // 0x00693e10
};
struct cIOStream;
struct cStreamHost {
    void** mpVtbl;                                          // +0x00
};
struct cStreamHostVtbl {
    void* mpSlots00[6];                                     // +0x00 .. +0x17
    cIOStream* (__fastcall* pGetStream)(cStreamHost* pThis);   // +0x18
};
struct cArchive {
    void** mpVtbl;                                          // +0x00
};
struct cArchiveVtbl {
    void* mpSlots00[8];                                     // +0x00 .. +0x1f
    cStreamHost* (__fastcall* pGetStreamHost)(cArchive* pThis);   // +0x20
};
static bool GetBoolProperty(cPropertyList_s00c4_a850* pList, uint32_t nKey)
{
    cProperty_s00c4_a850* pProperty;
    if (!pList)
        return false;
    if (!pList->Find(nKey, &pProperty))
        return false;
    if (pProperty->mType != 1)
        return false;
    return *pProperty->GetBool();
}
static int32_t GetIntProperty(cPropertyList_s00c4_a850* pList, uint32_t nKey)
{
    cProperty_s00c4_a850* pProperty;
    if (!pList)
        return 0;
    if (!pList->Find(nKey, &pProperty))
        return 0;
    if (pProperty->mType != 9)
        return 0;
    return *pProperty->GetInt();
}
struct cAdventurePlanet {
    char    mPad000[0x28];                                  // +0x00
    int32_t mField28;                                       // +0x28
};
// ---- items of slice s00c4a850 end

// ---- items of slice s00b9bed0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char kProcLevelGenName[];        // 0x01465be0  "Simulator/ProcLevelGen"
extern "C" void __cdecl FUN_00b90720();                               // 0x00b90720
extern "C" void __stdcall FUN_00401930(void* ptr, unsigned stride,
                                       unsigned count, void* ctor);   // 0x00401930
extern const int   kMaxClueCount;             // 0x0146596c  = 128
extern const float kNegOne;                   // 0x013eb1bc  = -1.0f
extern const float kI16Scale;                 // 0x01449540  = 32767.0f
void* __cdecl operator_new(unsigned size, const char* name, int a, int b,
                           const void* allocator, int line);            // 0x00f473a0
struct Elem12 { int m00; int m04; float m08; };
struct Container14 {                          // 0x14-byte owned container at clue+8
    int m00, m04, m08, m0c, m10;
    void Init(int count);                     // 0x00d01790
};
struct GenRecord {                            // ref-counted record
    void** mVtable;                           // +0x00
    int    mRefCount;                         // +0x04
    int    mSize;                             // +0x08
    int    m0c;                               // +0x0c
    int    mValue10;                          // +0x10
};
struct GenParams {
    int m00;                                  // +0x00
    int m04;                                  // +0x04
    GenRecord* mA08;                          // +0x08
    GenRecord* mB0c;                          // +0x0c
    int m10, m14, m18, m1c, m20, m24, m28, m2c, m30;
    float m34;                                // +0x34
    float m38;                                // +0x38
    float m3c;                                // +0x3c
};
struct cDirectPropertyList {
    int GetIntProperty(unsigned id);          // 0x006a2660
};
extern cDirectPropertyList* g_pAppProperties; // 0x015fd918
struct Clue {
    int  mType00;                             // +0x00
    unsigned char mFlag04;                    // +0x04
    char mPad05[3];                           // +0x05
    Container14 mC08;                         // +0x08
    GenRecord* mRef1c;                        // +0x1c
    GenRecord* mRef20;                        // +0x20
    int    m24;                               // +0x24
    float  m28;                               // +0x28
    int    m2c;                               // +0x2c
    int    m30;                               // +0x30
    Elem12* m34;                              // +0x34
    int    m38;                               // +0x38
    int    m3c;                               // +0x3c
    int    m40;                               // +0x40
    float  m44;                               // +0x44
    int    m48;                               // +0x48
    float  m4c;                               // +0x4c
    int    m50;                               // +0x50
    unsigned char* mProc54;                   // +0x54

    void Reset();                             // 0x00b9a630
    void Read(GenParams* src, int count, float value);
};
// ---- items of slice s00b9bed0 end

// ---- items of slice s00c45860 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int                i32;
typedef float              f32;
typedef unsigned long long u64;
typedef long long          i64;
template <class T>
struct Vec {
    T*  mpBegin;      // 0x00
    T*  mpEnd;        // 0x04
    T*  mpCap;        // 0x08
};
typedef Vec<u32> VecU32_s00c4_5860;
struct Timer20 {                 // cSPMission + 0x38 / +0x58
    u32 raw[8];
    void Ctor();                 // 0x00b63890
    void Dtor();                 // 0x00b638b0
};
struct Key12 { u32 a, b, c; };
typedef Vec<Key12> VecKey12;
struct cProperty_s00c4_5860 {
    void*  mpValue;    // 0x00
    u32    pad04;      // 0x04
    i32    mCount;     // 0x08
    u32    pad0c;      // 0x0c
    u16    mFlags;     // 0x10
    u16    mType;      // 0x12
    u8*    GetBool();  // 0x0041e920  ?GetBool@cProperty@@QAEPA_NXZ
    f32*   GetFloat(); // 0x0041ea70  Property::GetFloat
};
struct MissionPropList {
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0c();
virtual void vf10();
virtual void vf14();
    virtual void vf18();
    virtual bool HasProperty(u32 key);                    // slot +0x1c
    virtual void vf20();
    virtual bool GetProperty(u32 key, cProperty_s00c4_5860** out);   // slot +0x24
    virtual cProperty_s00c4_5860* GetPropertyByKey(u32 key);         // slot +0x28
};
struct cEntity {
    u32 pad000[0x15];        // 0x00
    u32 mRelation;           // 0x54
    u32 pad058[0xb];         // 0x58
    u32 mEmpireID;           // 0x84
    u32 GetWeaponryLevel();  // 0x00c317a0
    u8  EmpireCommAllowed(void* planetClue);  // 0x00c308e0
};
struct cPlanetClueObj {
    cPlanetClueObj* SortBanners(u32 zero);               // 0x00b8de30
    void FUN_00bb9c10();                                 // 0x00bb9c10
    void* GetCommContext();                              // 0x00ce6950 (returns [this+0x184])
};
struct cPlanet_s00c4_5860 {
    u32 pad000[0x4f];        // 0x00
    cPlanetClueObj* mpPlanetClue;     // 0x13c
    void* GetRandomAnimalSpecies();   // 0x00c70c10
    void* FUN_00c71e30();             // 0x00c71e30
};
struct cPlayerInventory {
    void* GetToolByKeySlot68(void* key);        // vtable +0x68 (this, key)
    void* GetToolByKey(u32 which, void* key);   // vtable +0x64 (this, which, key)
    void* ResolveTool(void* item);              // vtable +0x60 (this, item)
    void  AddTool(Key12* key);                  // 0x00ff45e0
};
struct cSimSpaceGame {
    cPlayerInventory* GetPlayerInventory();     // 0x00a1ad60
};
struct cGameDataBase {
    void Ctor();           // 0x00b18660
    void Dtor();           // 0x00b184c0
};
class cGenericPressureEvent : public cGameDataBase {
 public:
    void* mpVtbl;          // 0x000
    void* mpVtbl4;         // 0x004
    u32   pad008[0xb];     // 0x008
    void* mpVtbl34;        // 0x034
    Timer20 mTimer38;      // 0x038
    Timer20 mTimer58;      // 0x058

    cGenericPressureEvent* ctor();           // 0x00c46500
    void* ScalarDeletingDtor(u32 flags);     // 0x00c46540
};
class cSPMission_s00c4_5860 {
 public:
    void* mpVtbl0;             // 0x000
    void* mpVtbl4;             // 0x004
    u32   pad008[5];           // 0x008
    VecU32_s00c4_5860 mVec1c;             // 0x01c
    u32   pad028[3];           // 0x028
    void* mpVtbl34;            // 0x034
    Timer20 mTimer38;          // 0x038
    Timer20 mTimer58;          // 0x058
    f32   mRewardMoney;        // 0x078
    u32   pad07c;              // 0x07c
    u32   mDuration;           // 0x080
    u32   mState;              // 0x084  (eMissionState)
    u8    mSystemsShutdown;    // 0x088
    u8    pad089[3];           // 0x089
    u32   mOwnerEmpireID;      // 0x08c
    void* mpOwnerEmpire;       // 0x090
    u32   pad094[2];           // 0x094
    cPlanet_s00c4_5860* mpSourcePlanet;   // 0x09c
    u32   pad0a0[0x18];        // 0x0a0
    u32   mStarMapIconEffect;  // 0x100
    u32   mStarMapDestEffect;  // 0x104
    VecU32_s00c4_5860 mStarMapEffects;    // 0x108
    u32   pad114[7];           // 0x114
    u32   mFlags130;           // 0x130
    VecU32_s00c4_5860 mEventLogsToRemove; // 0x134
    u32   pad140[2];           // 0x140
    u32   mProgressEventID;    // 0x148
    u32   pad14c[8];           // 0x14c
    void* mTargetAnimalSpecies;// 0x16c
    u32   mTargetSpeciesKey[3];// 0x170
    u32   pad17c;              // 0x17c
    void* mpMissionPropList;   // 0x180
    u32   mRewardToolKey;      // 0x184
    u32   pad188[3];           // 0x188
    VecKey12 mVec194;          // 0x194
    u32   pad1a0[2];           // 0x1a0
    VecKey12 mVec1a8;          // 0x1a8
    u32   pad1b4[2];           // 0x1b4
    VecKey12 mVec1bc;          // 0x1bc
    u32   pad1c8[7];           // 0x1c8
    u32   mField1e4;           // 0x1e4
    cPlanet_s00c4_5860* mpTargetPlanet;   // 0x1e8

    // helpers defined in the same object elsewhere
    void* GetOwnerEmpire();                 // 0x00c451e0
    f32   GetPunishmentRelation();          // 0x00c45920
    f32   FUN_00c45970();                   // 0x00c45970

    // this slice
    f32   GetRewardRelation();              // 0x00c45860
    u32   CalculateDuration();              // 0x00c45a10
    u32   ReadTargetPlanetType();           // 0x00c45b40
    u32   ReadTargetAnimalSpeciesType();    // 0x00c45b60
    u8    ReadPickClosestStar();            // 0x00c45c60
    Key12* GetMessageVector(Key12* out);    // 0x00c45ca0
    void  SetOwnerEmpire(cEntity* empire);  // 0x00c45d30
    u32   IsTargetPlanetClue(u32 clue);     // 0x00c45d80
    u32   GetMissionIconEffect();           // 0x00c45db0
    u32   GetMissionIconEffectGroup();      // 0x00c45de0
    void  UpdateStarMapEffects(u8 useZero);// 0x00c45e10
    u8    IsTutorialMission();              // 0x00c45f80
    void  UpdateHints(u8 param);            // 0x00c45f90
    bool  CanShowOnMap();                   // 0x00c460f0
    u32   HasValidDescription();            // 0x00c46120
    void  RemoveToolVector194();            // 0x00c46160
    void  RemoveToolVector1bc();            // 0x00c461d0
    void  RemoveToolVector1a8();            // 0x00c46250
    u8    SerializeVarList(void* stream);   // 0x00c46310
    void  WriteUintVector(VecU32_s00c4_5860* vec, void* stream); // 0x00c46470
    void  ShutdownSystems();                // 0x00c46590
    void  PostLoad();                       // 0x00c466d0
    u8    PickTargetAnimalSpecies();        // 0x00c46790
    u32   QueueConversation();              // 0x00c46800
    u32   CanAccept();                      // 0x00c46840
    void  OnReject();                       // 0x00c468b0
    void  OnFail();                         // 0x00c469f0
};
extern "C" extern f32 g_missionTimeScale;    // 0x013ec5b4
extern "C" extern f32 g_oneHalf;             // 0x013f9428
extern "C" extern f32 g_defaultHintValue;    // 0x0146d130
extern "C" extern u32 g_zeroSpeciesKey[3];   // 0x0168e844
struct cStarMap {
    void RemoveVisual(u32 handle, u32 flag);             // 0x01045a60
    void* Lookup(u32 a, u32 b);                          // 0x01045120
    void* CreatePlanetRecordVisual(void* star, void* planet, void* extra, bool a, bool b); // 0x01045910
    void  FUN_01044d70(void* visual, u32 flag);         // 0x01044d70
    void  FilterHelperRebuildAll();                      // 0x01048ce0
};
struct cSPUIEventLog_s00c4_5860 {
    void RemoveEvent(u32 id, u32 flag);                  // 0x00dd6d10
};
struct cCommManager {
    void RemoveMatching(i32 a, i32 b, void* mission);    // 0x00aea720
    void* FindEntry(u32 a, u32 b, u32 c, u32 d, u32 e);  // 0x00ae93f0
    void  RemoveByPtr(void* entry);                      // 0x00aea7f0
    void  Add(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g); // 0x00aeb7a0
};
u32   __cdecl GetPlayerEmpireID();                       // 0x01021090
void* __cdecl GetPlayerEmpire();                         // 0x01021300
void  __cdecl GetPropertyAsFloatArray(void* list, u32 key, i32* count, void** out); // 0x006a08b0
u8    __cdecl GetPropertyAsKeyInstance(void* list, u32 key, void** out);          // 0x006a12a0
void* __cdecl NounManager();                             // 0x00b3d300
struct cGameTimeManager {
    u64 GetTime();                                       // 0x00b316c0 ([this+0x38])
};
cGameTimeManager* __cdecl GameTimeManager();             // 0x00b3d380
cStarMap* __cdecl GetStarMap();                          // 0x01046fc0 (no args, returns singleton)
struct cTerrainSphere {
    f32 GetValue(u32 key);                               // 0x00c75c30
};
struct cNounManager {
    cTerrainSphere* GetCurrentTerrainSphere();           // 0x00f67d90 ([this+0x74])
};
void* __cdecl SpaceGameGet();                            // 0x01002bd0
void* __cdecl SpaceGameGet(int a);                       // 0x01002bd0
void* __cdecl FUN_010666a0(void* p);                     // 0x010666a0
void  __cdecl FUN_0106f120(void* p);                     // 0x0106f120
void* __cdecl FUN_01005180(u32 a);                       // 0x01005180
void  __cdecl IntVectorResize(void* v, u32 n);           // 0x007eb820
void* __cdecl GetMissionManager();                       // 0x00feb9f0 (no push: arg in ecx)
void* __stdcall GetMissionManager(u32 a);                // 0x00feb9f0 (arg on stack)
struct cMissionManager {
    void  RemoveMission();                               // 0x00febe00
    void  Event();                                       // 0x00fecbb0
    void* GetOtherVec();                                 // 0x00897670
    void* GetVec();                                      // 0x00febaa0
};
void* __cdecl PropertyManager();                         // 0x0067de30
cSPUIEventLog_s00c4_5860* __cdecl EventLog();                       // 0x00b3d3e0
cCommManager* __cdecl CommManager();                     // 0x00b3d4a0
void  __cdecl WriteUint32(void* stream, void* value, u32 count, u32 flag); // 0x0093aa70
void  __cdecl cSPUILayoutCtor();                         // 0x00dd1ca0
void  __cdecl cSPUILayoutAdd();                          // 0x00dd27c0
struct cTerraformingManager {
    void  AddPlanet();                                   // 0x00bc1b10
};
cTerraformingManager* __stdcall TerraformingManager(void* planet);  // 0x00b3d430
struct cRelationshipManager {
    float RecordEvent(u32 a, u32 b, u32 ev, f32 v);      // 0x00d06240
    f32 RelGetRelation(u32 a, u32 b, u32 c);             // 0x00d00a10
};
cRelationshipManager* __cdecl RelationshipManager();     // 0x00b3d2c0
struct cSpaceRelationshipTuning {
    f32 TuningGetThreshold();                            // 0x01040860
};
cSpaceRelationshipTuning* __cdecl GetSpaceRelationshipTuning();  // 0x010407c0
void  __cdecl OperatorDeleteArray(void* p);              // 0x00f47380
struct cVarListSerializer_s00c4_5860 {
    void Ctor(void* self, void* mission, const char* name, u32 id);  // 0x00692f90
    u8   Serialize(void* stream);                                    // 0x00692900
};
// ---- items of slice s00c45860 end

// @ 0x00b9c630
void Clue::Read(GenParams* src, int count, float value)
{
    Reset();                                                          // 0xb9a630
    mFlag04 = 1;
    mType00 = g_pAppProperties->GetIntProperty(0x4f421d6);             // 0x6a2660
    if (mType00 < 0 || mType00 > 2) mType00 = 0;

    mC08.Init(0xc000);                                                // 0xd01790

    unsigned char* proc = (unsigned char*)operator_new(
        0x120000, kProcLevelGenName, 0, 0, 0, 0);                     // 0xf473a0
    if (proc != 0) {
        FUN_00401930(proc, 0x18, 0xc000, (void*)&FUN_00b90720);       // 0x401930
    }
    mProc54 = proc;
    for (int i = 0; i < 0xc000; i++) {
        mProc54[i * 0x18] = 0;
    }

    m24 = (count < 0x80) ? count : kMaxClueCount;
    m28 = value;

    float scaled = src->m3c * kI16Scale;
    int biased = _mm_cvt_ss2si(*(__m128*)&scaled) + 0x8000;
    m40 = (biased > 0) ? (int)(unsigned short)biased : 0;
    m44 = src->m38;
    m4c = src->m34;

    GenRecord* recA = src->mA08;
    int size = recA->mSize;
    m38 = size;
    m3c = size * size;
    m48 = (int)(((unsigned)size / (unsigned)(2 * count)) *
                (unsigned)(size + 1));

    if (recA != mRef1c) {
        recA->mRefCount += 1;
        GenRecord* old = mRef1c;
        mRef1c = recA;
        if (old != 0) {
            int c = old->mRefCount - 1;
            old->mRefCount = c;
            if (c == 0) {
                old->mRefCount = 1;
                ((void(__thiscall*)(GenRecord*, int))
                    old->mVtable[0])(old, 1);
            }
        }
    }
    GenRecord* recB = src->mB0c;
    if (recB != mRef20) {
        if (recB != 0) recB->mRefCount += 1;
        GenRecord* old = mRef20;
        mRef20 = recB;
        if (old != 0) {
            int c = old->mRefCount - 1;
            old->mRefCount = c;
            if (c == 0) {
                old->mRefCount = 1;
                ((void(__thiscall*)(GenRecord*, int))
                    old->mVtable[0])(old, 1);
            }
        }
    }
    m2c = mRef1c->mValue10;
    m30 = mRef20->mValue10;

    int total = count * count * 6;
    unsigned bytes = (unsigned)total * 12u;
    if (bytes / 12u != (unsigned)total) bytes = 0xffffffffu;
    Elem12* arr = (Elem12*)operator_new(bytes, kProcLevelGenName,
                                        0, 0, 0, 0);                  // 0xf473a0
    if (arr != 0) {
        for (int i = 0; i < total; i++) {
            arr[i].m00 = 0;
            arr[i].m04 = 0;
            arr[i].m08 = kNegOne;
        }
    }
    m34 = arr;
}

// @ 0x00c44a20
int GameObj::Read_c44a20(void* stream)
{
  if (mpResource)
    mKey = mpResource->key;
  else
    mKey = ResourceKey();
  bool ok = FUN_00b18590(stream);
  LocalSerializer s(this, DAT_015745f0, 0x1a80d26);
  if (s.FUN_00692900(stream) && ok)
    return 1;
  return 0;
}

// @ 0x00c44ad0
bool GameObj::Write_c44ad0(void* stream)
{
  bool ok = FUN_00b18600(stream);
  LocalSerializer s(this, DAT_015745f0, 0x1a80d26);
  ok &= s.FUN_00693e10(stream);
  if (mKey.instance != 0)
    mpResource = FUN_00401090()->FUN_004df550(&mKey);
  return ok;
}

// @ 0x00c44b40
void GameObj::Serialize_c44b40(void* stream)
{
  LocalSerializer s(this, DAT_015745f0, 0x1a80d26);
  s.FUN_00695960(stream);
}

// @ 0x00c44b80
void GameObj::RegisterIds_c44b80()
{
  v83(0x35ec3de);
  v83(0x248975f);
  v83(0x2489760);
  v83(0x4249453);
}

// @ 0x00c44bd0
void GameObj::UnregisterIds_c44bd0()
{
  v84(0x35ec3de);
  v84(0x248975f);
  v84(0x2489760);
  v84(0x4249453);
}

// @ 0x00c44c40
void GameObj::ForwardToResource_c44c40(void* p)
{
  if (mpResource)
    mpResource->FUN_004da330(p);
}

// @ 0x00c44c60
int GameObj::CallV48_c44c60(int a)
{
  return v48(a);
}

// @ 0x00c44c90
bool GameObj::CallV42_c44c90()
{
  return 0 < v42();
}

// @ 0x00c44cb0
uint32_t GameObj::GetTypeId_c44cb0()
{
  if (v62())
    return 0x11965a4d;
  if (v63())
    return v64() ? 0x11fd3bf3 : 0xe22e5c17;
  return 0x1a2b6f64;
}

// @ 0x00c44d00
float __stdcall GetFactor_c44d00(Thing* t, const bool* mode)
{
  if (t->FUN_00b8d970() || t->FUN_00b8d9b0() != 0 || (t->flags & 0x800))
    return -1.0f;
  bool m = FUN_00feb9f0()->FUN_00fee110(t);
  if (mode[0] || mode[1]) {
    Relations* r = FUN_01021300();
    int i = ((IndexTable*)t->FUN_00b8de30())->FUN_00b1fdb0();
    bool a, b;
    if (i != -1) {
      a = r->FUN_00c31bf0(i);
      b = r->FUN_00c31b10(i);
    } else {
      a = false;
      b = false;
    }
    if (mode[0]) {
      if (a) return m ? 0.07f : 1.5f;
      if (b) return 0.0f;
      return m ? 0.05f : 0.5f;
    }
    if (mode[1]) {
      if (a) return 0.0f;
      if (b) return m ? 0.07f : 1.5f;
      return m ? 0.05f : 0.5f;
    }
  }
  return m ? 0.1f : 1.0f;
}

// @ 0x00c45250
void cSPMission::SetEmpire(cEmpire* p)
{
    mCachedEmpireID94 = (p != 0) ? (int)p->mEmpireID84 : -1;
    cEmpire* old = mpEmpire98;
    if (p != old) {
        if (p != 0)
            VT_00_0(p);
        mpEmpire98 = p;
        if (old != 0)
            VT_04_0(old);
    }
}

// @ 0x00c452a0
cEmpire* cSPMission::GetEmpire()
{
    if (mpEmpire98 != 0)
        return mpEmpire98;
    int id = mCachedEmpireID94;
    if (id == -1)
        return mpEmpire98;
    cStarManager* mgr = GetStarManager((u32)id);
    cEmpire* e = mgr->GetEmpireByID();
    cEmpire* old = mpEmpire98;
    if (e == old)
        return old;
    if (e != 0)
        VT_00_0(e);
    mpEmpire98 = e;
    if (old != 0) {
        VT_04_0(old);
        return mpEmpire98;
    }
    return e;
}

// @ 0x00c45310
int cSPMission::SetUITextValue(int value)
{
    if (value != 0 && mpPropertyList180 != 0)
        SP_GetPropertyAsString16(mpPropertyList180, 0x00b2ccca, value);
    return value;
}

// @ 0x00c45340
bool cSPMission::IsVisibleInUI()
{
    bool visible = true;
    if (mpPropertyList180 != 0) {
        cProperty* prop = 0;
        if (mpPropertyList180->GetProperty(0x05590946, &prop)) {
            if (prop->mType12 == 1)
                visible = *prop->GetBool();
        }
    }
    return visible;
}

// @ 0x00c45380
int cSPMission::GetNumAvailable()
{
    u32 total = mTotal80;
    if (total > 0) {
        int zero = 0;
        int d = (int)(total - (u32)mUsed7c);
        return max_ref(d, zero);
    }
    return 0;
}

// @ 0x00c45510
int cSPMission::GetTotalTravelCost()
{
    cPlanet* origin = mpOriginPlanet9c;
    if (origin == 0)
        return 0;
    cPlanet* target = mpTargetPlanet1e8;
    if (target == 0)
        return 0;
    cStarRecord* targetRec = target->mpStarRecord13c;
    cStarRecord* originRec = origin->mpStarRecord13c;
    u32 targetID = targetRec->GetStarID();
    u32 originID = originRec->GetStarID();
    return 2 * GetUFOSimulator(originID)->ComputeCost(targetID);
}

// @ 0x00c45560
float cSPMission::GetTotalTravelCostFloat()
{
    cPlanet* origin = mpOriginPlanet9c;
    if (origin == 0)
        return 0.0f;
    cPlanet* target = mpTargetPlanet1e8;
    if (target == 0)
        return 0.0f;
    cStarRecord* targetRec = target->mpStarRecord13c;
    cStarRecord* originRec = origin->mpStarRecord13c;
    u32 targetID = targetRec->GetStarID();
    u32 originID = originRec->GetStarID();
    return GetUFOSimulator(originID)->ComputeCostFloat(targetID) * 2.0f;
}

// @ 0x00c455b0
bool cSPMission::IsAtStar(int empireID, int commContext)
{
    int state = VT_60_0(this);
    if (state != 3) {
        if (VT_60_0(this) != 5)
            return false;
    }
    if (mpOriginPlanet9c->mpStarRecord13c->GetCommContext() != commContext)
        return 0;
    if (empireID != mEmpireID8c)
        return 0;
    return 1;
}

// @ 0x00c45740
int cSPMission::GetDynamicResponseID(int a, int b)
{
    (void)a;
    (void)b;
    return (mFlags130 & 1) ? -1 : 0xb6a7851e;
}

// @ 0x00c45860
f32 cSPMission_s00c4_5860::GetRewardRelation()
{
    u32 relation = 0;
    cEntity* owner = (cEntity*)GetOwnerEmpire();
    if (owner != 0)
        relation = owner->mRelation;
    f32 result = 0.0f;
    if (mpMissionPropList == 0)
        return result;
    u32 key = 0x6fa6f0f4;
    MissionPropList* list = (MissionPropList*)mpMissionPropList;
    if (relation >= 1 && relation <= 3) {
        u32 alt = relation == 1 ? 0x5cf5e5e0 : (relation == 2 ? 0xaef74c9a : 0xe3833365);
        if (list->HasProperty(alt))
            key = alt;
    }
    if (list->HasProperty(key) && mpMissionPropList != 0) {
        cProperty_s00c4_5860* prop = 0;
        if (list->GetProperty(key, &prop) && prop->mType == 0xd) {
            result = *prop->GetFloat();
        }
    }
    return result;
}

// @ 0x00c45a10
u32 cSPMission_s00c4_5860::CalculateDuration()
{
    f32 duration = 0.0f;
    if (mpMissionPropList != 0) {
        cProperty_s00c4_5860* prop = 0;
        if (((MissionPropList*)mpMissionPropList)->GetProperty(0xd71a8119, &prop) &&
            prop->mType == 0xd)
            duration = *prop->GetFloat();
    }
    u8 carry = 0;
    if (mpMissionPropList != 0) {
        cProperty_s00c4_5860* prop = 0;
        if (((MissionPropList*)mpMissionPropList)->GetProperty(0xd71a811a, &prop) &&
            prop->mType == 1)
            carry = *prop->GetBool();
    }
    if (carry != 0)
        mFlags130 |= 0x20;
    else
        mFlags130 &= ~0x20;
    if (mOwnerEmpireID != 0xffffffff &&
        mOwnerEmpireID != GetPlayerEmpireID()) {
        i32 count = 0;
        void* array = 0;
        GetPropertyAsFloatArray(mpMissionPropList, 0x5efaf8b, &count, &array);
        if (count > 0) {
            cEntity* owner = (cEntity*)GetOwnerEmpire();
            owner->GetWeaponryLevel();
        }
    }
    cTerrainSphere* sphere = ((cNounManager*)NounManager())->GetCurrentTerrainSphere();
    f32 scale = sphere->GetValue(0x77174715);
    f32 total = (scale * duration) * g_missionTimeScale;
    u32 v = (u32)(i64)total;
    mDuration = v;
    return v;
}

// @ 0x00c45b40
u32 cSPMission_s00c4_5860::ReadTargetPlanetType()
{
    void* out;
    GetPropertyAsKeyInstance(mpMissionPropList, 0x1f7aaaaa, &out);
    return (u32)out;
}

// @ 0x00c45b60
u32 cSPMission_s00c4_5860::ReadTargetAnimalSpeciesType()
{
    void* out;
    GetPropertyAsKeyInstance(mpMissionPropList, 0x1f7aaaab, &out);
    return (u32)out;
}

// @ 0x00c45c60
u8 cSPMission_s00c4_5860::ReadPickClosestStar()
{
    if (mpMissionPropList != 0) {
        cProperty_s00c4_5860* prop;
        if (((MissionPropList*)mpMissionPropList)->GetProperty(0x1f707857, &prop) &&
            prop->mType == 1)
            return *prop->GetBool();
    }
    return 0;
}

// @ 0x00c45ca0
Key12* cSPMission_s00c4_5860::GetMessageVector(Key12* out)
{
    void* vec;
    if ((mFlags130 & 1) != 0) {
        cMissionManager* mgr = (cMissionManager*)GetMissionManager();
        vec = mgr->GetOtherVec();
    } else {
        cMissionManager* mgr = (cMissionManager*)GetMissionManager();
        vec = mgr->GetVec();
    }
    *out = *(Key12*)vec;
    return out;
}

// @ 0x00c45d30
void cSPMission_s00c4_5860::SetOwnerEmpire(cEntity* empire)
{
    mOwnerEmpireID = empire != 0 ? empire->mEmpireID : 0xffffffff;
    void* old = mpOwnerEmpire;
    if (empire != (cEntity*)old) {
        if (empire != 0)
            (*(void(__thiscall**)(void*))*(void**)empire)(empire);
        mpOwnerEmpire = empire;
        if (old != 0)
            (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }
}

// @ 0x00c45d80
u32 cSPMission_s00c4_5860::IsTargetPlanetClue(u32 clue)
{
    if (mpTargetPlanet != 0 && (u32)mpTargetPlanet->mpPlanetClue == clue)
        return 1;
    return 0;
}

// @ 0x00c45db0
u32 cSPMission_s00c4_5860::GetMissionIconEffect()
{
    if (mpMissionPropList != 0) {
        void* out;
        if (GetPropertyAsKeyInstance(mpMissionPropList, 0x45c00672, &out))
            return (u32)out;
    }
    return 0xcda5f5d;
}

// @ 0x00c45de0
u32 cSPMission_s00c4_5860::GetMissionIconEffectGroup()
{
    if (mpMissionPropList != 0) {
        void* out;
        if (GetPropertyAsKeyInstance(mpMissionPropList, 0xf924ebf3, &out))
            return (u32)out;
    }
    return 0x166521a5;
}

// @ 0x00c45e10
void cSPMission_s00c4_5860::UpdateStarMapEffects(u8 useZero)
{
    cGameTimeManager* gt = GameTimeManager();
    u64 time = gt->GetTime();
    u64 rem = time % 1000;
    f32 frac = (f32)((double)rem * g_oneHalf);

    if (mStarMapIconEffect != 0xffffffff) {
        f32 v = useZero != 0 ? g_defaultHintValue : frac;
        void* obj = GetStarMap()->Lookup(0, mStarMapIconEffect);
        if (obj != 0)
            (*(void(__thiscall**)(void*, u32, f32*, u32))((char*)*(void**)obj + 0x44))(obj, 4, &v, 1);
    }
    if (mStarMapDestEffect != 0xffffffff) {
        f32 v = useZero != 0 ? g_defaultHintValue : frac;
        void* obj = GetStarMap()->Lookup(0, mStarMapDestEffect);
        if (obj != 0)
            (*(void(__thiscall**)(void*, u32, f32*, u32))((char*)*(void**)obj + 0x44))(obj, 4, &v, 1);
    }
    if (mStarMapEffects.mpBegin != mStarMapEffects.mpEnd) {
        i32 n = (i32)(mStarMapEffects.mpEnd - mStarMapEffects.mpBegin);
        if (n > 0) {
            i32 i = 0;
            do {
                u32 h = mStarMapEffects.mpBegin[i];
                if (h != 0xffffffff) {
                    f32 v = useZero != 0 ? g_defaultHintValue : frac;
                    void* obj = GetStarMap()->Lookup(0, h);
                    if (obj != 0)
                        (*(void(__thiscall**)(void*, u32, f32*, u32))((char*)*(void**)obj + 0x44))(obj, 4, &v, 1);
                }
                ++i;
            } while (i < n);
        }
    }
}

// @ 0x00c45f80
u8 cSPMission_s00c4_5860::IsTutorialMission()
{
    return (u8)(~(u8)(mFlags130 >> 1)) & 1;
}

// @ 0x00c45f90
void cSPMission_s00c4_5860::UpdateHints(u8 param)
{
    if (mpMissionPropList != 0) {
        cProperty_s00c4_5860* prop;
        if (((MissionPropList*)mpMissionPropList)->GetProperty(0x5590946, &prop)) {
            if (prop->mType == 1 && *prop->GetBool() == 0)
                return;
        }
    }
    {
        u32 e1;
        cEntity* owner1 = (cEntity*)GetOwnerEmpire();
        if (owner1 != 0) {
            owner1 = (cEntity*)GetOwnerEmpire();
            e1 = owner1->mEmpireID;
        } else {
            e1 = 0xffffffff;
        }
        void* ctx1 = mpSourcePlanet->mpPlanetClue->GetCommContext();
        void* entry1 = CommManager()->FindEntry(e1, (u32)ctx1, 0, 0xc8fbf7d7, 0x305a4a16);
        if (entry1 != 0)
            CommManager()->RemoveByPtr(entry1);

        u32 e2;
        cEntity* owner2 = (cEntity*)GetOwnerEmpire();
        if (owner2 != 0) {
            owner2 = (cEntity*)GetOwnerEmpire();
            e2 = owner2->mEmpireID;
        } else {
            e2 = 0xffffffff;
        }
        void* ctx2 = mpSourcePlanet->mpPlanetClue->GetCommContext();
        void* entry2 = CommManager()->FindEntry(e2, (u32)ctx2, 0, 0xc8fbf7d7, 0xa789391d);
        if (entry2 != 0)
            CommManager()->RemoveByPtr(entry2);

        u32 e3;
        cEntity* owner3 = (cEntity*)GetOwnerEmpire();
        if (owner3 != 0) {
            owner3 = (cEntity*)GetOwnerEmpire();
            e3 = owner3->mEmpireID;
        } else {
            e3 = 0xffffffff;
        }
        u32 key = (param != 0 ? 0x88d110f9 : 0) + 0xa789391d;
        void* ctx3 = mpSourcePlanet->mpPlanetClue->GetCommContext();
        CommManager()->Add(e3, (u32)ctx3, 0xc8fbf7d7, key, 0, 1, 0x493e0);
    }
}

// @ 0x00c460f0
bool cSPMission_s00c4_5860::CanShowOnMap()
{
    u32 flags = mFlags130;
    u32 bit5 = flags >> 5;
    if ((bit5 & 1) != 0) {
        u32 bit6 = flags >> 6;
        if ((bit6 & 1) == 0)
            return false;
    }
    u8 r = (*(u8(__thiscall**)(void*))((char*)*(void**)this + 0xf8))(this);
    bool b = (r == 0);
    return b;
}

// @ 0x00c46120
u32 cSPMission_s00c4_5860::HasValidDescription()
{
    u32 n = (*(u32(__thiscall**)(void*))((char*)*(void**)this + 0xa8))(this);
    if (n > 0 && (mFlags130 & 1) == 0) {
        if ((*(u8(__thiscall**)(void*))((char*)*(void**)this + 0x104))(this) != 0)
            return 1;
    }
    return 0;
}

// @ 0x00c46160
void cSPMission_s00c4_5860::RemoveToolVector194()
{
    i32 n = (i32)(mVec194.mpEnd - mVec194.mpBegin);
    if (n > 0) {
        i32 off = 0;
        do {
            cSimSpaceGame* game = (cSimSpaceGame*)SpaceGameGet();
            cPlayerInventory* inv = game->GetPlayerInventory();
            void* key = (void*)((char*)mVec194.mpBegin + off);
            void* item = (*(void*(__thiscall**)(void*, void*))((char*)*(void**)inv + 0x68))(inv, key);
            if (item != 0) {
                void* r = FUN_010666a0(item);
                FUN_0106f120(r);
            }
            off += 0xc;
            --n;
        } while (n != 0);
    }
}

// @ 0x00c461d0
void cSPMission_s00c4_5860::RemoveToolVector1bc()
{
    cSimSpaceGame* game = (cSimSpaceGame*)SpaceGameGet();
    cPlayerInventory* inv = game->GetPlayerInventory();
    i32 n = (i32)(mVec1bc.mpEnd - mVec1bc.mpBegin);
    if (n > 0) {
        i32 off = 0;
        do {
            void* key = (void*)((char*)mVec1bc.mpBegin + off);
            void* item = (*(void*(__thiscall**)(void*, u32, void*))((char*)*(void**)inv + 0x64))(inv, 0, key);
            item = (*(void*(__thiscall**)(void*, void*))((char*)*(void**)inv + 0x60))(inv, item);
            if (item != 0) {
                void* r = FUN_010666a0(item);
                FUN_0106f120(r);
            }
            off += 0xc;
            --n;
        } while (n != 0);
    }
}

// @ 0x00c46250
void cSPMission_s00c4_5860::RemoveToolVector1a8()
{
    cSimSpaceGame* game = (cSimSpaceGame*)SpaceGameGet();
    cPlayerInventory* inv = game->GetPlayerInventory();
    i32 n = (i32)(mVec1a8.mpEnd - mVec1a8.mpBegin);
    if (n > 0) {
        i32 off = 0;
        do {
            void* key = (void*)((char*)mVec1a8.mpBegin + off);
            void* item = (*(void*(__thiscall**)(void*, u32, void*))((char*)*(void**)inv + 0x64))(inv, 1, key);
            item = (*(void*(__thiscall**)(void*, void*))((char*)*(void**)inv + 0x60))(inv, item);
            if (item != 0) {
                void* r = FUN_010666a0(item);
                FUN_0106f120(r);
            }
            off += 0xc;
            --n;
        } while (n != 0);
    }
}

// @ 0x00c46310
u8 cSPMission_s00c4_5860::SerializeVarList(void* stream)
{
    cVarListSerializer_s00c4_5860 ser;
    ser.Ctor(&ser, this, "Mission", 0x1a80d26);
    u8 result = ser.Serialize(stream);
    i32 n = (i32)(mVec1c.mpEnd - mVec1c.mpBegin);
    void* o = (*(void*(__thiscall**)(void*))((char*)*(void**)stream + 0x20))(stream);
    void* s = (*(void*(__thiscall**)(void*))((char*)*(void**)o + 0x18))(o);
    i32 count = n;
    WriteUint32(s, &count, 1, 0);
    for (i32 i = 0; i < n; ++i) {
        i32 field = *(i32*)((char*)mVec1c.mpBegin[i] + 0x70);
        void* o2 = (*(void*(__thiscall**)(void*))((char*)*(void**)stream + 0x20))(stream);
        void* s2 = (*(void*(__thiscall**)(void*))((char*)*(void**)o2 + 0x18))(o2);
        i32 v = field;
        WriteUint32(s2, &v, 1, 0);
    }
    return result;
}

// @ 0x00c463d0
void** __fastcall ReleaseRefMember(void** self)
{
    void* obj = *self;
    if (obj != 0) {
        *self = 0;
        (*(void(__thiscall**)(void*))((char*)*(void**)obj + 8))(obj);
    }
    return self;
}

// @ 0x00c46470
void cSPMission_s00c4_5860::WriteUintVector(VecU32_s00c4_5860* vec, void* stream)
{
    i32 n = (i32)(vec->mpEnd - vec->mpBegin);
    void* o = (*(void*(__thiscall**)(void*))((char*)*(void**)stream + 0x20))(stream);
    void* s = (*(void*(__thiscall**)(void*))((char*)*(void**)o + 0x18))(o);
    i32 count = n;
    WriteUint32(s, &count, 1, 0);
    u32* p = vec->mpBegin;
    u32* end = vec->mpEnd;
    while (p != end) {
        void* o2 = (*(void*(__thiscall**)(void*))((char*)*(void**)stream + 0x20))(stream);
        void* s2 = (*(void*(__thiscall**)(void*))((char*)*(void**)o2 + 0x18))(o2);
        u32 v = *p;
        WriteUint32(s2, &v, 1, 0);
        ++p;
    }
    (*(void(__thiscall**)(void*))((char*)*(void**)stream + 0x1c))(stream);
}

// @ 0x00c46500
cGenericPressureEvent* cGenericPressureEvent::ctor()
{
    Ctor();
    *(void* volatile*)((char*)this + 0x34) = (void*)0x13eb384;
    mpVtbl = (void*)0x146d188;
    mpVtbl4 = (void*)0x146d174;
    mpVtbl34 = (void*)0x146d164;
    mTimer38.Ctor();
    mTimer58.Ctor();
    return this;
}

// @ 0x00c46540
void* cGenericPressureEvent::ScalarDeletingDtor(u32 flags)
{
    mpVtbl = (void*)0x146d188;
    mpVtbl4 = (void*)0x146d174;
    mpVtbl34 = (void*)0x146d164;
    mTimer58.Dtor();
    mTimer38.Dtor();
    mpVtbl34 = (void*)0x13eb394;
    Dtor();
    if ((flags & 1) != 0)
        OperatorDeleteArray(this);
    return this;
}

// @ 0x00c46590
void cSPMission_s00c4_5860::ShutdownSystems()
{
    mSystemsShutdown = 1;
    CommManager()->RemoveMatching(-1, -1, this);
    if (mStarMapIconEffect != 0xffffffff) {
        GetStarMap()->RemoveVisual(mStarMapIconEffect, 0);
        mStarMapIconEffect = 0xffffffff;
    }
    if (mStarMapDestEffect != 0xffffffff) {
        GetStarMap()->RemoveVisual(mStarMapDestEffect, 0);
        mStarMapDestEffect = 0xffffffff;
    }
    i32 n = (i32)(mStarMapEffects.mpEnd - mStarMapEffects.mpBegin);
    if (n > 0) {
        do {
            u32 handle = mStarMapEffects.mpEnd[-1];
            GetStarMap()->RemoveVisual(handle, 0);
            mStarMapEffects.mpEnd -= 1;
            --n;
        } while (n != 0);
    }
    if (mpTargetPlanet != 0) {
        cPlanetClueObj* clue = mpTargetPlanet->mpPlanetClue;
        clue->SortBanners(0)->FUN_00bb9c10();
    }
    if (mProgressEventID != 0xffffffff) {
        EventLog()->RemoveEvent(mProgressEventID, 1);
        mProgressEventID = 0xffffffff;
    }
    (*(void(__thiscall**)(void*))((char*)*(void**)this + 0x148))(this);
    i32 m = (i32)(mEventLogsToRemove.mpEnd - mEventLogsToRemove.mpBegin);
    if (m > 0) {
        do {
            u32 id = mEventLogsToRemove.mpEnd[-1];
            mEventLogsToRemove.mpEnd -= 1;
            EventLog()->RemoveEvent(id, 0);
            --m;
        } while (m != 0);
    }
}

// @ 0x00c466d0
void cSPMission_s00c4_5860::PostLoad()
{
    void* mgr = PropertyManager();
    void* old = mpMissionPropList;
    if (old != 0) {
        mpMissionPropList = 0;
        (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }
    (*(void(__thiscall**)(void*, u32, u32, void**))((char*)*(void**)mgr + 0x2c))(mgr, *(u32*)&mRewardMoney, 0x2ae1a8e, &mpMissionPropList);
    if (mpMissionPropList == 0) {
        mState = 1;
        cMissionManager* mm = (cMissionManager*)GetMissionManager((u32)(void*)this);
        mm->RemoveMission();
        (*(void(__thiscall**)(void*))((char*)*(void**)this + 0x44))(this);
    }
    if (mState == 2 || mState == 3) {
        (*(void(__thiscall**)(void*))((char*)*(void**)this + 0x144))(this);
        (*(void(__thiscall**)(void*))((char*)*(void**)this + 0x194))(this);
    }
    if (mpTargetPlanet != 0)
        TerraformingManager(mpTargetPlanet)->AddPlanet();
    (*(void(__thiscall**)(void*, u32))((char*)*(void**)this + 0x190))(this, 0);
}

// @ 0x00c46790
u8 cSPMission_s00c4_5860::PickTargetAnimalSpecies()
{
    void* species = mpTargetPlanet->GetRandomAnimalSpecies();
    mTargetAnimalSpecies = species;
    if (species == 0) {
        u32 zero0 = g_zeroSpeciesKey[0];
        mTargetSpeciesKey[0] = zero0;
        mTargetSpeciesKey[1] = g_zeroSpeciesKey[1];
        mTargetSpeciesKey[2] = g_zeroSpeciesKey[2];
        return 0;
    }
    *(Key12*)mTargetSpeciesKey = *(Key12*)((char*)species + 0x504);
    return 1;
}

// @ 0x00c46800
u32 cSPMission_s00c4_5860::QueueConversation()
{
    cEntity* owner = (cEntity*)GetOwnerEmpire();
    if (mOwnerEmpireID != 0xffffffff && owner != 0) {
        cPlanet_s00c4_5860* planet = mpSourcePlanet;
        void* clue;
        if (planet != 0) {
            clue = planet->mpPlanetClue;
            if (owner->EmpireCommAllowed(clue) == 0)
                return 0;
        }
    }
    return 1;
}

// @ 0x00c46840
u32 cSPMission_s00c4_5860::CanAccept()
{
    cEntity* owner = (cEntity*)GetOwnerEmpire();
    if (mOwnerEmpireID != 0xffffffff && owner != 0) {
        cEntity* player = (cEntity*)GetPlayerEmpire();
        if (owner != player) {
            player = (cEntity*)GetPlayerEmpire();
            u32 pid = player->mEmpireID;
            u32 oid = owner->mEmpireID;
            f32 relation = RelationshipManager()->RelGetRelation(oid, pid, 0);
            f32 threshold = GetSpaceRelationshipTuning()->TuningGetThreshold();
            if (relation < threshold)
                return 0;
        }
    }
    return 1;
}

// @ 0x00c468b0
void cSPMission_s00c4_5860::OnReject()
{
    if ((mFlags130 & 8) != 0) {
        cMissionManager* mm = (cMissionManager*)GetMissionManager(*(u32*)&mRewardMoney);
        mm->Event();
    }
    cEntity* owner = (cEntity*)GetOwnerEmpire();
    if (owner != 0 && owner != (cEntity*)GetPlayerEmpire()) {
        f32 rel = FUN_00c45970();
        rel = fabsf(rel);
        {
            u32 oid = owner->mEmpireID;
            u32 id = GetPlayerEmpireID();
            cRelationshipManager* rm = RelationshipManager();
            rm->RecordEvent(oid, id, 0x526e51d, rel);
        }
        {
            u32 oid2 = owner->mEmpireID;
            u32 id2 = GetPlayerEmpireID();
            cRelationshipManager* rm2 = RelationshipManager();
            rm2->RelGetRelation(oid2, id2, 0);
        }
        cSPUILayoutCtor();
        cSPUILayoutAdd();
    }
    SpaceGameGet(4);
    void* v = FUN_01005180(4);
    IntVectorResize(v, 8);
    *(f32*)((char*)*(void**)((char*)v + 0xc) + 0x1c) = mRewardMoney;

    cProperty_s00c4_5860* prop = ((MissionPropList*)mpMissionPropList)->GetPropertyByKey(0x1625a62e);
    u16 flags = prop->mFlags & 0x30;
    i32 count;
    if (flags != 0) {
        count = prop->mCount;
        if (count <= 0)
            return;
    } else {
        if (prop->mType == 0)
            return;
        count = 1;
    }
    do {
        Key12 key;
        key.a = *(u32*)prop->mpValue;
        key.b = 0;
        key.c = 0;
        cSimSpaceGame* game = (cSimSpaceGame*)SpaceGameGet();
        cPlayerInventory* inv = game->GetPlayerInventory();
        inv->AddTool(&key);
        --count;
    } while (count != 0);
}

// @ 0x00c469f0
void cSPMission_s00c4_5860::OnFail()
{
    cEntity* owner = (cEntity*)GetOwnerEmpire();
    if (owner != 0 && owner != (cEntity*)GetPlayerEmpire()) {
        f32 rel = GetPunishmentRelation();
        rel = fabsf(rel);
        {
            u32 oid = owner->mEmpireID;
            u32 id = GetPlayerEmpireID();
            cRelationshipManager* rm = RelationshipManager();
            rm->RecordEvent(oid, id, 0x526e51c, rel);
        }
        {
            u32 oid2 = owner->mEmpireID;
            u32 id2 = GetPlayerEmpireID();
            cRelationshipManager* rm2 = RelationshipManager();
            rm2->RelGetRelation(oid2, id2, 0);
        }
        cSPUILayoutCtor();
        cSPUILayoutAdd();
    }
    SpaceGameGet(7);
    void* v = FUN_01005180(7);
    IntVectorResize(v, 8);
    *(f32*)((char*)*(void**)((char*)v + 0xc) + 0x1c) = mRewardMoney;
    if ((mFlags130 & 1) != 0)
        UpdateHints(0);
    (*(void(__thiscall**)(void*))((char*)*(void**)this + 0x84))(this);
}

namespace SP {
::cStarManager* __cdecl GetStarManagerNoArg();           // 0x00b3d2a0 (no-arg getter)
u8 __cdecl GetPropertyAsKey16(void* props, u32 key, void* out); // 0x006a1250
::cStarMap* __cdecl GetStarMapNoArg();                   // 0x01046fc0 (no-arg singleton)
cSPMissionManager* __cdecl GetMissionManagerNoArg();     // 0x00feb9f0 (no-arg getter)
struct cSPUILayout16 { void Add(); };                    // 0x00dd27c0
void* __cdecl cSPUILayoutCtor16();                       // 0x00dd1ca0
}

// @ 0x00c46ab0
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::FUN_00c46ab0()
{
    cEntity* owner = (cEntity*)GetOwnerEmpire();
    if (owner != 0 && owner != (cEntity*)GetPlayerEmpire()) {
        float value = (float)fabs(FUN_00c459c0());
        u32 empireId = owner->mEmpireID;
        RelationshipManager()->RecordEvent(empireId, GetPlayerEmpireID(), 0x526e51e, value);
        empireId = owner->mEmpireID;
        RelationshipManager()->RelGetRelation(empireId, GetPlayerEmpireID(), 0);
        ((cSPUILayout16*)cSPUILayoutCtor16())->Add();
    }
    SP::IntVector* vec = (SP::IntVector*)((SimGame*)::SpaceGameGet())->f5180(7);
    vec->resize(8);
    *(u32*)(vec->mData + 0x1c) = mMissionId;
    u32 shifted = mFlags >> 3;
    _ReadWriteBarrier();
    if ((shifted & 1) != 0) {
        cSPMissionManager* mm = GetMissionManager((void*)(uintptr_t)mMissionId);
        mm->Event();
    }
    if ((mFlags & 1) != 0)
        UpdateHints(0);
    return v84();
}
}  // namespace SP

// @ 0x00c46b80
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::FUN_00c46b80()
{
}
}  // namespace SP

// @ 0x00c46e20
void SP::cSPMission::GiveOnAcceptItems()
{
}

// @ 0x00c47040
namespace SP {
uint32_t __thiscall cSPMission_s00c4_6ab0::GetConversationFileID()
{
    cSPMission_s00c4_6ab0* mgr = mpMissionManager;
    if (mgr != 0)
        return mgr->vA4();
    void* props = mpMissionKey;
    if (props != 0) {
        Key12 key;
        key.a = 0;
        key.b = 0;
        key.c = 0;
        if (GetPropertyAsKey16(props, 0x7c9601b0, &key) != 0)
            return key.a;
    }
    return 0xffffffff;
}
}  // namespace SP

// @ 0x00c470a0
namespace SP {
bool __thiscall cSPMission_s00c4_6ab0::FUN_00c470a0()
{
    u32 shifted = mFlags >> 1;
    _ReadWriteBarrier();
    if ((shifted & 1) != 0) {
        if (!v12C())
            return false;
    }
    shifted = mFlags >> 2;
    _ReadWriteBarrier();
    if ((shifted & 1) != 0) {
        if (!v130())
            return false;
    }
    return true;
}
}  // namespace SP

// @ 0x00c470f0
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::SetMissionID(uint32_t missionId)
{
    mMissionId = missionId;
}
}  // namespace SP

// @ 0x00c47140
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::FUN_00c47140(uint32_t planetId)
{
    ISpaceObject* old = mpPlanet;
    if (old != 0) {
        mpPlanet = 0;
        old->ReleaseObject();
    }
    GetStarManagerNoArg()->SetPlanetRef(planetId, (void**)&mpPlanet);
}
}  // namespace SP

// @ 0x00c47180
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::FUN_00c47180(uint32_t planetId)
{
    ISpaceObject* old = mpPlanet1E8;
    if (old != 0) {
        mpPlanet1E8 = 0;
        old->ReleaseObject();
    }
    GetStarManagerNoArg()->SetPlanetRef(planetId, (void**)&mpPlanet1E8);
}
}  // namespace SP

// @ 0x00c471c0
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::FUN_00c471c0()
{
    bool flag = vF8() || vFC();
    u32 shifted = mFlags >> 1;
    if ((shifted & 1) != 0 && !flag)
        v19C();
    else
        v198(flag);
    GetStarMapNoArg()->FilterHelperRebuildAll();
}
}  // namespace SP

// @ 0x00c47240
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::FUN_00c47240()
{
    if (mpPlanet == 0)
        return;
    void* a = vE4();
    ::cStarRecord* star = ((::cPlanet*)mpPlanet)->mpStarRecord13c;
    void* visual = GetStarMapNoArg()->CreatePlanetRecordVisual(star, a, vE8(), true, true);
    mpPlanetVisual = visual;
    GetStarMapNoArg()->FUN_01044d70(visual, (u32)a == 0x70930c64);
    FUN_00c471c0();
}
}  // namespace SP

// @ 0x00c472c0
namespace SP {
bool __thiscall cSPMission_s00c4_6ab0::FUN_00c472c0()
{
    cSPMission_s00c4_6ab0* pOwner = mpMissionManager ? mpMissionManager : this;
    bool result = GetMissionManager(pOwner)->FUN_00febf80();
    _ReadWriteBarrier();
    return result;
}
}  // namespace SP

// @ 0x00c472e0
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::FUN_00c472e0()
{
    cSPMission_s00c4_6ab0* mgr = mpMissionManager ? mpMissionManager : this;
    ::cStarRecord* star = ((::cPlanet*)mpPlanet)->mpStarRecord13c;
    cEntity* owner = (cEntity*)GetOwnerEmpire();
    u32 empireId = owner->mEmpireID;
    CommManager()->Add(empireId, (u32)star->GetCommContext(),
                       vA4(), (u32)v10C(), (u32)mgr, 0, 0);
}
}  // namespace SP

// @ 0x00c47350
void SP::cSPMission::ExportPlanet(SP::cPlanet * targetType, unsigned int pOut)
{
    ::cPlanet* planet = (::cPlanet*)targetType;
    if (pOut == 0x779436ff) {
        GetMissionManagerNoArg()->FUN_00febde0(0, (void*)planet->mpStarRecord13c->GetCommContext());
        return;
    }
    if (pOut == 0x779436fe) {
        GetMissionManagerNoArg()->FUN_00febde0(1, (void*)planet->mpStarRecord13c->GetCommContext());
        return;
    }
    if (pOut == 0x93e59364) {
        cSPMission_s00c4_6ab0* self = (cSPMission_s00c4_6ab0*)this;
        cSPMission_s00c4_6ab0* mgr = self->mpMissionManager;
        if (mgr != 0) {
            ISpeciesExport* exp = (ISpeciesExport*)mgr->QueryInterface(0x422227c);
            if (exp != 0) {
                void* ctx = (void*)planet->mpStarRecord13c->GetCommContext();
                SP::cSpeciesExportImpl* impl = (SP::cSpeciesExportImpl*)exp;
                impl->v0(0, ctx);
            }
        }
    }
}

// @ 0x00c473f0
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::ExportSpecies(uint32_t itemType, uint32_t flags)
{
    if (itemType == 0x29aa9073)
        return;
    if (itemType != 0xd6dc6ff6)
        return;
    cSPMission_s00c4_6ab0* pOwner = mpMissionManager;
    if (!pOwner)
        return;
    ISpeciesExport* pExport = (ISpeciesExport*)pOwner->QueryInterface(0x422227c);
    if (!pExport)
        return;
    pExport->Export(0, &mSpecies.mSpeciesKey);
}
}  // namespace SP

// @ 0x00c47440
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::StartCompletedFeedbackTimer()
{
    cSPMission_s00c4_6ab0* pManager = mpMissionManager;
    if (pManager) {
        pManager->OnMissionCompleted();
        return;
    }
    mFeedbackTimer.Restart();

    cSPMission_s00c4_6ab0* pOwner = mpMissionManager ? mpMissionManager : this;
    if (!GetMissionManagerOf(pOwner, 0)->IsCompletedFeedbackActive())
        return;

    cAudioSystem* pAudio = GetSystemAT();
    if (pAudio) {
        KillSetiEffects(0x0c871d6e, pAudio->GetOutputDevice());
        return;
    }
    KillSetiEffects(0x0c871d6e, (void*)pAudio);
}
}  // namespace SP

// @ 0x00c474b0
namespace SP {
namespace {
struct cStarSysH474b0 { void* GetSolarSystem(); };       // 0x00c8b770
struct cPlanetH474b0  { int   Count(); };                // 0x00c70fb0
struct cMgrH474b0     { void* FUN_00febdc0(); };         // 0x00febdc0
struct cObjH474b0     { void* FUN_00ba6dc0(); };         // 0x00ba6dc0
struct cExpH474b0     { void* FUN_00c59fb0(int); };      // 0x00c59fb0
void* __cdecl   GetPlayerHomePlanet474b0();              // 0x01021370
void* __cdecl   GetActivePlanet474b0();                  // 0x01021260
void* __cdecl   FUN_01021230_474b0();                    // 0x01021230
void* __cdecl   FUN_00aed3f0_474b0(void*);               // 0x00aed3f0
void* __stdcall FUN_00b3d2a0_474b0(void*);               // 0x00b3d2a0
void* __stdcall GetMissionManager474b0(void*);           // 0x00feb9f0
}
void* __thiscall cSPMission_s00c4_6ab0::FUN_00c474b0(uint32_t nType)
{
    cSPMission_s00c4_6ab0* self = this;
    void* volatile result = 0;
    if (nType == 0x8e718b32) {
        void* r = GetPlayerHomePlanet474b0();
        return r;
    }
    if (nType == 0xa8169426) {
        GetActivePlanet474b0();
        void* star = FUN_01021230_474b0();
        if (star == 0)
            return 0;
        void* solar = ((cStarSysH474b0*)star)->GetSolarSystem();
        if (solar == 0)
            return 0;
        int i = 0;
        int count = (int)(*(u32*)((char*)solar + 0x14) - *(u32*)((char*)solar + 0x10)) >> 2;
        if (count < 1)
            return 0;
        while (i < count) {
            void* planet = (*(void***)((char*)solar + 0x10))[i];
            if (planet != 0) {
                void* rec = *(void**)((char*)planet + 0x13c);
                if (rec != GetPlayerHomePlanet474b0()) {
                    if (((cPlanetH474b0*)planet)->Count() > 0)
                        return rec;
                }
            }
            i++;
        }
        return 0;
    }
    if (nType == 0x779436ff) {
        result = ((cMgrH474b0*)GetMissionManager474b0(0))->FUN_00febdc0();
        goto tail;
    }
    if (nType == 0x779436fe) {
        result = ((cMgrH474b0*)GetMissionManager474b0((void*)1))->FUN_00febdc0();
        goto tail;
    }
    if (nType == 0xac595460) {
        cSPMission_s00c4_6ab0* mgr = self->mpMissionManager;
        if (mgr == 0)
            return 0;
        return *(void**)((char*)mgr->mpPlanet1E8 + 0x13c);
    }
    if (nType == 0x93e59364) {
        cSPMission_s00c4_6ab0* mgr = self->mpMissionManager;
        if (mgr == 0)
            return 0;
        void* x = FUN_00aed3f0_474b0(mgr);
        if (x == 0)
            return 0;
        result = ((cExpH474b0*)x)->FUN_00c59fb0(0);
        goto tail;
    }
    return result;
tail:
    if (result != 0) {
        void* sm = FUN_00b3d2a0_474b0(result);
        result = ((cObjH474b0*)sm)->FUN_00ba6dc0();
    }
    return result;
}
}  // namespace SP

// @ 0x00c47610
void SP::cSPMission::GetAnimalSpeciesFromType(unsigned int a1, EA::ResourceMan::Key & a2)
{
    if (a1 != 0xd4923304)
        return;
    cSPMission_s00c4_6ab0* mgr = *(cSPMission_s00c4_6ab0**)((char*)this + 0x17c);
    if (mgr == 0)
        return;
    void* obj = mgr->vB0();
    if (obj == 0)
        return;
    ((u32*)&a2)[0] = *(u32*)((char*)obj + 0x504);
    ((u32*)&a2)[1] = *(u32*)((char*)obj + 0x508);
    ((u32*)&a2)[2] = *(u32*)((char*)obj + 0x50c);
}

// @ 0x00c478b0
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::Update(int deltaMs)
{
    (void)deltaMs;
}
}  // namespace SP

// @ 0x00c47a10
void cSPMission_s00c4_7a10::OnAccept()
{
    if (((uint8_t)(mFlags130 >> 3) & 1) != 0) {
        ((MissionManager*)SP::GetMissionManager())->FUN_00fede40(mField78);
        ((MissionManager*)SP::GetMissionManager())->FUN_00feba10();
    }
    ((MissionManager*)SP::GetMissionManager())->FUN_00feca20(this);
    pv101();
    SP::IntVector* guild = (SP::IntVector*)((SimGame*)SP::SpaceGameGet())->f5180(5);
    guild->resize(0xc);
    float timer = pv60();
    ((GuildRecord*)guild->mData)->mField1C = mField78;
    ((GuildRecord*)guild->mData)->mField20 = mFieldA0;
    ((GuildRecord*)guild->mData)->mField24 = mFieldA4;
    ((GuildRecord*)guild->mData)->mField28 = timer;
    ((GuildRecord*)guild->mData)->mField28 = timer + g_FloatOne;
    GiveOnAcceptItems(true);
    pv81();
    if (mField1E8 != 0) {
        cStarRecord_s00c4_7a10* record = ((cPlanet_s00c4_7a10*)mField1E8)->mField13C;
        record->FUN_00b8de30()->FUN_00bb9c10(1);
    }
    int32_t count = mField184;
    if (count > 0) {
        void* player = FUN_01021300_s00c4_7a10();
        if (player != 0) {
            ((MissionManager*)player)->FUN_00c31a00(-count);
        }
    }
}

// @ 0x00c47cc0
void cSPMission_s00c4_7a10::SetState(uint32_t state)
{
    if (mState84 == state) {
        return;
    }
    mState84 = state;
    mStr14C.clear();
    mStr15C.clear();
    if (mState84 == 3) {
        cMissionUpdateMessage msg;
        msg.mParam0 = (uint32_t)this;
        GetMessageServer()->PostMessage(msg.mMessageID, &msg, 0);
        msg.Destruct();
    }
}

// @ 0x00c47d80
void cSPMission_s00c4_7a10::TriggerUIUpdate()
{
    mStr14C.clear();
    mStr15C.clear();
    cMissionUpdateMessage msg;
    msg.mParam0 = (uint32_t)this;
    GetMessageServer()->PostMessage(msg.mMessageID, &msg, 0);
    msg.Destruct();
}

// @ 0x00c483d0
void cSPMission_s00c4_7a10::DataExportOnInit()
{
    if (((PropertyList*)mProps180)->v7(0xf924ecff)) {
        uint32_t key = 0;
        SP::GetPropertyAsKeyInstance(mProps180, 0xf924ecff, &key);
        ExportPlanet(mField1E8, key);
    }
    if (((PropertyList*)mProps180)->v7(0xf924ed00)) {
        uint32_t key = 0;
        SP::GetPropertyAsKeyInstance(mProps180, 0xf924ed00, &key);
        ExportSpecies(mField16C, key);
    }
}

// @ 0x00c48470
void cSPMission_s00c4_7a10::FUN_00c48470(int32_t* key)
{
    if ((mKey170 != 0 && mField16C == 0)
        || (key != 0 && (void*)key[0] == mKey170 && (void*)key[1] == mKey174
            && (void*)key[2] == mKey178)) {
        if (!pv99()) {
            mField16C = 0;
            SetState(1);
        }
    }
}

// @ 0x00c484e0
bool cSPMission_s00c4_7a10::Validate()
{
    Empire* empire = (Empire*)GetOwnerEmpire();
    if (mField8C != -1 && empire == 0) {
        goto fail;
    }
    if (!pv88()) {
        goto fail;
    }
    if (mField94 != -1 && FUN_00c452a0() == 0) {
        goto fail;
    }
    if (((cPlanet_s00c4_7a10*)mPlanet9C)->mField13C->FUN_00b8d970()) {
        goto fail;
    }
    if (mField1E8 != 0 && ((cPlanet_s00c4_7a10*)mField1E8)->mField13C->FUN_00b8d970()) {
        goto fail;
    }
    empire = (Empire*)GetOwnerEmpire();
    if (!pv89()) {
        g_pTokenTranslator->mField1C = (int32_t)empire;
        SP::EventLog(0x7bac9736, 0x131a9f54, 0, 0, 1, 0)->PostFeedbackEvent();
        goto fail;
    }
    return true;
fail:
    SetState(1);
    return false;
}

// @ 0x00c48600
bool cSPMission_s00c4_7a10::PickPlanetClue()
{
    if (mField1E8 == 0) {
        return false;
    }
    PlanetNameHolder* holder = ((cPlanet_s00c4_7a10*)mField1E8)->mField13C->FUN_00b8de30();
    if (holder == 0) {
        return false;
    }
    uint32_t kind = g_Random.RandomUint32Uniform(2);
    mFieldF4 = (int32_t)kind;
    switch (kind) {
    case 0: {
        cPlanetList* src = holder->FUN_00bba790();
        if (src->mBegin == src->mEnd) {
            return false;
        }
        cPlanetRange vec;
        vec.Construct(src);
        SortPlanetsByRadius(&vec);
        int32_t index = 1;
        for (void** it = vec.mBegin; it != vec.mEnd; ++it, ++index) {
            if (*it == ((cPlanet_s00c4_7a10*)mField1E8)->mField13C) {
                mFieldFC = index;
                vec.Destroy();
                return true;
            }
        }
        vec.Destroy();
        return true;
    }
    case 1:
        mFieldF8 = ((cPlanet_s00c4_7a10*)mField1E8)->FUN_00c70880();
        return true;
    default:
        return true;
    }
}

// @ 0x00c486f0
void cSPMission_s00c4_7a10::FUN_00c486f0(WString* out)
{
    Empire* empire = (Empire*)FUN_00c452a0();
    if (empire == 0) {
        return;
    }
    Species* species = (Species*)empire->FUN_00c30c60();
    if (species == 0) {
        return;
    }
    WString* name = species->FUN_00bb9de0();
    const wchar_t* text = name->mBegin;
    out->assign(text, text + WcsLen(text));
}

// @ 0x00c48740
void cSPMission_s00c4_7a10::FUN_00c48740(WString* out)
{
    Empire* empire = (Empire*)GetOwnerEmpire();
    if (empire == 0) {
        return;
    }
    Species* species = (Species*)empire->FUN_00c30c60();
    if (species == 0) {
        return;
    }
    WString* name = species->FUN_00bb9de0();
    const wchar_t* text = name->mBegin;
    out->assign(text, text + WcsLen(text));
}

// @ 0x00c48790
void cSPMission_s00c4_7a10::FUN_00c48790(WString* out)
{
    cString_s006b_47a0* label;
    if ((mFlags130 & 1) != 0) {
        label = &g_MissionLabel010030;
    } else {
        label = &g_MissionLabel01002F;
    }
    const wchar_t* text = label->GetText();
    out->assign(text, text + WcsLen(text));
}

// @ 0x00c487d0
void cSPMission_s00c4_7a10::GetText(WString* out, int32_t textStyle)
{
    void* context = pv41();
    void* savedContext = g_pTokenTranslator->mField18;
    void* savedOwner = g_pTokenTranslator->mField48;
    g_pTokenTranslator->mField18 = this;
    g_pTokenTranslator->mField48 = context;

    void* activePlanet = FUN_01021260();
    void* starRecord = activePlanet != 0 ? ((cPlanet_s00c4_7a10*)activePlanet)->mField13C : 0;
    FUN_00c452a0();
    void* empire = GetOwnerEmpire();

    cString_s006b_47a0 text;
    text.Construct();

    void* mission = mField17C;
    if (mission == 0) {
        mission = this;
    }
    cTextFormatter* formatterA = (cTextFormatter*)FUN_00aed4d0();
    cTextFormatter* formatterB = (cTextFormatter*)FUN_00aed4d0();
    void* game = FUN_01021300_s00c4_7a10();
    void* formatted = formatterA->v9(&text, mission, starRecord, game, empire, out);
    formatterB->v3(formatted, out, (void*)(intptr_t)textStyle, game);

    const wchar_t* str = text.GetText();
    out->assign(str, str + WcsLen(str));

    g_pTokenTranslator->mField18 = savedContext;
    g_pTokenTranslator->mField48 = savedOwner;
    text.Destruct();
}

// @ 0x00c48900
void cSPMission_s00c4_7a10::FUN_00c48900(WString* out)
{
    if (mPlanet9C == 0) {
        return;
    }
    PlanetNameHolder* holder = ((cPlanet_s00c4_7a10*)mPlanet9C)->mField13C->FUN_00b8de30();
    if (holder == 0) {
        return;
    }
    WString* name = holder->FUN_00bb9de0();
    out->assign(name->mBegin, name->mEnd);
}

// @ 0x00c48940
void cSPMission_s00c4_7a10::FUN_00c48940(WString* out)
{
    if (mPlanet9C == 0) {
        return;
    }
    WString* name = ((cPlanet_s00c4_7a10*)mPlanet9C)->GetName();
    if (name == out) {
        return;
    }
    out->assign(name->mBegin, name->mEnd);
}

// @ 0x00c48970
void SPObject::FUN_00c48970(int idx, WStr* out)
{
    int v = (int)mArrE0[idx];
    if (v == 0)
        return;
    switch (mArrCC[idx]) {
    case 0:
        out->append(((CStr*)0x168ee08)->GetText());
        return;
    case 1:
        (*(Translator**)0x16e0d08)->mField10 = v;
        out->append(((CStr*)0x168ee1c)->GetText());
        return;
    case 2:
        (*(Translator**)0x16e0d08)->mField10 = v;
        out->append(((CStr*)0x168ee30)->GetText());
        return;
    case 3:
        (*(Translator**)0x16e0d08)->mField10 = v;
        out->append(((CStr*)0x168ee44)->GetText());
        return;
    case 4:
        (*(Translator**)0x16e0d08)->mField10 = v;
        out->append(((CStr*)0x168ee58)->GetText());
        return;
    case 5:
        (*(Translator**)0x16e0d08)->mField10 = v;
        out->append(((CStr*)0x168ee6c)->GetText());
        return;
    case 6:
        out->append(((CStr*)0x168ee80)->GetText());
        return;
    }
}

// @ 0x00c48a90
void SPObject::FUN_00c48a90(WStr* out)
{
    int i = mFieldFC;
    if (i >= 0 && i < 10) {
        const wchar_t* p = ((CStr*)(0x168ef48 + i * 0x14))->GetText();
        out->assign(p, p + WStrLen(p));
    }
}

// @ 0x00c48ae0
void SPObject::FUN_00c48ae0(WStr* out)
{
    switch (mKindF8) {
    case 0:
        out->append(((CStr*)0x168ee94)->GetText());
        break;
    case 1:
        out->append(((CStr*)0x168eea8)->GetText());
        return;
    case 2:
        out->append(((CStr*)0x168eebc)->GetText());
        return;
    case 3:
        out->append(((CStr*)0x168eed0)->GetText());
        return;
    case 4:
        out->append(((CStr*)0x168eee4)->GetText());
        return;
    case 5:
        out->append(((CStr*)0x168eef8)->GetText());
        return;
    }
}

// @ 0x00c48ba0
void SPObject::FUN_00c48ba0(int arg)
{
    u32* p = mVec1D0.mpBegin;
    while (p != mVec1D0.mpEnd) {
        if ((int)*p == arg) {
            VT_2C(MessageServer(), (char*)this + 0x34, arg, -10000);
            u32* next = p + 1;
            if (next < mVec1D0.mpEnd)
                memcpy(p, next, (char*)mVec1D0.mpEnd - (char*)next);
            mVec1D0.mpEnd = (u32*)((char*)mVec1D0.mpEnd - 4);
        } else {
            p++;
        }
    }
}

// @ 0x00c48c20
void SPObject::GetRewardsNames(WStr* out)
{
    bool b3 = !(mStarClueA4 == *(u32*)0x168e844 &&
                mStarClueA8 == *(u32*)0x168e848 &&
                mStarClueAC == *(u32*)0x168e84c);
    bool b2 = mFieldA0 > 0.0f;
    if (b3) {
        WStr temp;
        temp.mpBegin = 0;
        temp.mpEnd = 0;
        temp.mpCapacity = 0;
        temp.RangeInitialize(mStrB0.GetText());
        out->Append(temp.mpBegin, temp.mpEnd);
        if (temp.mpCapacity - temp.mpBegin > 1 && temp.mpBegin)
            EAFree(temp.mpBegin);
        if (!b2)
            return;
        out->Append(L" %s ", ((CStr*)0x168ef0c)->GetText());
    }
    if (b2) {
        (*(Translator**)0x16e0d08)->mField40 = *(int*)&mFieldA0;
        const wchar_t* p = ((CStr*)0x168ef20)->GetText();
        out->assign(p, p + wcslen(p));
    }
}

// @ 0x00c48d40
void SPObject::GetUITitle(WStr* out)
{
    if (mStr14C.mpBegin == mStr14C.mpEnd) {
        if (VT_F8(this) == 0)
            GetText(0xaad9c0b3, out);
        else
            GetText(0x4e1f8fa8, out);
        if (out != &mStr14C)
            mStr14C.assign(out->mpBegin, out->mpEnd);
    } else if (out != &mStr14C) {
        out->assign(mStr14C.mpBegin, mStr14C.mpEnd);
    }
}

// @ 0x00c48db0
void SPObject::FUN_00c48db0(WStr* out)
{
    if (mGroup84 == 3) {
        if (VT_F8(this) == 0)
            GetText(0xd79a86a8, out);
        else
            GetText(0x81128ae1, out);
    }
}

// @ 0x00c48e00
void SPObject::FUN_00c48e00(WStr* out)
{
    if (mGroup84 == 3) {
        if (VT_F8(this) == 0)
            GetText(0x247d8d51, out);
        else
            GetText(0xba93258e, out);
    }
}

// @ 0x00c48e90
SPObject::SPObject()
{
    BaseCtor();
    mpVtbl34 = (void*)0x13eb384;
    mpVtbl0  = (void*)0x146d188;
    mpVtbl4  = (void*)0x146d174;
    mpVtbl34 = (void*)0x146d164;
    mTimer38.TimerCtor();
    mTimer58.TimerCtor();
    mpVtbl0  = (void*)0x146d200;
    mpVtbl4  = (void*)0x146dfb4;
    mpVtbl34 = (void*)0x146fbf0;
    mField78 = 0;
    mField7C = 0;
    mField80 = 0;
    mGroup84 = 0;
    mField88 = 0;
    mField8C = -1;
    mField90 = 0;
    mField94 = -1;
    mField98 = 0;
    mField9C = 0;
    mFieldA0 = 0.0f;
    mStarClueA4 = *(u32*)0x168e844;
    mStarClueA8 = *(u32*)0x168e848;
    mStarClueAC = *(u32*)0x168e84c;
    mStrB0.CStrCtor();
    mFieldC4 = -1;
    mFieldC8 = 0.0f;
    mArrCC = 0;
    mArrD0 = 0;
    mArrD4 = 0;
    mArrE0 = 0;
    mArrE4 = 0;
    mArrE8 = 0;
    mFieldF4 = -1;
    mKindF8 = -1;
    mFieldFC = -1;
    mField100 = -1;
    mField104 = -1;
    mField108 = 0;
    mField10C = 0;
    mField110 = 0;
    mVec11C.mpBegin = 0;
    mVec11C.mpEnd = 0;
    mVec11C.mpCapacity = 0;
    mFlags130 = 0;
    mVec134.mpBegin = 0;
    mVec134.mpEnd = 0;
    mVec134.mpCapacity = 0;
    mField148 = -1;
    mStr14C.mpBegin = (wchar_t*)0x1667bac;
    mStr14C.mpEnd = (wchar_t*)0x1667bac;
    mStr14C.mpCapacity = (wchar_t*)0x1667bae;
    mStr15C.mpBegin = (wchar_t*)0x1667bac;
    mStr15C.mpEnd = (wchar_t*)0x1667bac;
    mStr15C.mpCapacity = (wchar_t*)0x1667bae;
    mField16C = 0;
    mField170 = 0;
    mField174 = 0;
    mField178 = 0;
    mField17C = 0;
    mpField180 = 0;
    mField184 = 0;
    mField188 = 0;
    mField18C = 0;
    mField190 = 0;
    mField194 = 0;
    mField198 = 0;
    mField19C = 0;
    mField1A8 = 0;
    mField1AC = 0;
    mField1B0 = 0;
    mField1BC = 0;
    mField1C0 = 0;
    mField1C4 = 0;
    mVec1D0.mpBegin = 0;
    mVec1D0.mpEnd = 0;
    mVec1D0.mpCapacity = 0;
    mField1E4 = 0;
    mpTargetPlanet = 0;
    mVec11C.Reserve(5);
    {
        u32* first = mVec134.mpBegin;
        u32* last  = mVec134.mpEnd;
        u32* end   = mVec134.mpEnd;
        memcpy(first, last, (char*)end - (char*)last);
        mVec134.mpEnd = end - (last - first);
    }
}

// @ 0x00c490e0
void SPObject::FUN_00c490e0(u32 arg)
{
    if (VT_154(this, arg) == 0) {
        VT_20(MessageServer(), (char*)this + 0x34, arg);
        mVec1D0.push_back(arg);
    }
}

// @ 0x00c49140
void SPObject::FUN_00c49140(WStr* out)
{
    CivData* o = (CivData*)GetCivData();
    if (o) {
        o->FUN_c30c80();
        WStr3(out, (const wchar_t*)0x13f5c04, *o->GetCities());
    }
}

// @ 0x00c49180
void SPObject::FUN_00c49180(WStr* out)
{
    CivData* o = (CivData*)GetOwnerEmpire();
    if (o) {
        o->FUN_c30c80();
        WStr3(out, (const wchar_t*)0x13f5c04, *o->GetCities());
    }
}

// @ 0x00c491c0
int SPObject::GetTagString(u32 tag, WStr* out)
{
    wchar_t buf[64];

    if (tag == 0xa593874e) {
        if (mpTargetPlanet) {
            void* sorter = *(void**)((char*)mpTargetPlanet + 0x13c);
            if (sorter) {
                void* r = ((SorterObj*)sorter)->operator()();
                if (r) {
                    WStr* w = ((SorterObj*)r)->FUN_00bb9de0();
                    out->assign(w->mpBegin, w->mpEnd);
                }
            }
        }
        return 1;
    }

    if (tag == 0xa499e2f0) {
        if (mpTargetPlanet) {
            WStr* name = ((PlanetObj*)mpTargetPlanet)->GetName();
            if (name != out)
                out->assign(name->mpBegin, name->mpEnd);
        }
        return 1;
    }

    if (tag == 0xcaf36e4a) { FUN_00c48900(out); return 1; }
    if (tag == 0x8b0eb564) { FUN_00c48940(out); return 1; }
    if (tag == 0x200cc87d) { VT_B4(this, out);  return 1; }
    if (tag == 0xe3224d84) { GetRewardsNames(out); return 1; }
    if (tag == 0x68e2e9c6) { FUN_00c49140(out); return 1; }
    if (tag == 0xc2efec3f) { FUN_00c486f0(out); return 1; }
    if (tag == 0xfb301e72) { FUN_00c49180(out); return 1; }

    if (tag != 0x4434801b) {
        if (tag == 0x85f50ff7) {
            if ((mFlags130 >> 1) & 1) { VT_CC(this, 0, out); return 1; }
        }
        else if (tag == 0x85f50ff4) {
            if ((mFlags130 >> 1) & 1) { VT_CC(this, 1, out); return 1; }
        }
        else if (tag == 0x3eae770b) {
            if ((mFlags130 >> 1) & 1) { VT_D0(this, out); return 1; }
        }
        else if (tag == 0x4bf8f3dc) {
            if ((mFlags130 >> 1) & 1) { VT_D4(this, out); return 1; }
        }
        else {
            if (tag != 0x53f90032) {
                if (tag == 0xd1c3d278) {
                    if ((mFlags130 >> 2) & 1) { VT_DC(this, out); return 1; }
                }
                else {
                    if (tag != 0x39e8da5f) {
                        if (tag == 0xd1ce9de3) {
                            u32 ms = VT_AC(this);
                            u32 total = ms / 1000;
                            FUN_00881730(0, (int)(total / 60), (int)(total % 60), buf, 0x40,
                                         (const wchar_t*)0x146d3c4);
                            out->append(buf);
                            return 1;
                        }
                        if (tag == 0x22e33d08) {
                            (*(Translator**)0x16e0d08)->mField40 = (float)mField184;
                        }
                        else {
                            if (tag != 0xad9e5ea2 && tag != 0xc22d2221)
                                return 0;
                            (*(Translator**)0x16e0d08)->mField40 = (float)mField188;
                        }
                        out->append(((CStr*)0x168ef20)->GetText());
                        return 1;
                    }
                    if ((mFlags130 >> 2) & 1) { VT_E0(this, out); return 1; }
                }
                out->append(L"ERROR: PLANET NAME IS NOT HIDDEN");
                return 1;
            }
            if ((mFlags130 >> 1) & 1) { VT_D8(this, out); return 1; }
        }
        out->append(L"ERROR: STAR NAME IS NOT HIDDEN");
        return 1;
    }
    FUN_00c48740(out);
    return 1;
}

// @ 0x00c495c0
void SPObject::PickRewardUnlockTools()
{
    int group = 0;
    void* empire = GetOwnerEmpire();
    if (empire)
        group = *(int*)((char*)empire + 0x54);

    ToolSet* tools = (ToolSet*)mpField180;
    if (!tools)
        return;

    u32 tag = 0x7895f232;
    if (group == 1) {
        u32 alt = 0xefc800f5;
        if (tools->HasTag(alt)) tag = alt;
    }
    else if (group == 2) {
        u32 alt = 0xb1fc43;
        if (tools->HasTag(alt)) tag = alt;
    }
    else if (group == 3) {
        u32 alt = 0xb3fef39a;
        if (tools->HasTag(alt)) tag = alt;
    }

    if (!tools->HasTag(tag))
        return;

    tools = (ToolSet*)mpField180;
    if (!tools)
        return;

    UnlockEntry entry;
    if (!tools->GetEntry(tag, &entry))
        return;
    if (entry.mField12 != 9)
        return;

    int* pCount = entry.mpProperty ? entry.mpProperty->GetInt() : 0;
    if (!pCount || *pCount < 1)
        return;

    u32 tag2 = 0x828f44dc;
    if (group == 1) {
        u32 alt = 0xeaaaac60;
        if (tools->HasTag(alt)) tag2 = alt;
    }
    else if (group == 2) {
        u32 alt = 0x8aa0ab86;
        if (tools->HasTag(alt)) tag2 = alt;
    }
    else if (group == 3) {
        u32 alt = 0x1625a62d;
        if (tools->HasTag(alt)) tag2 = alt;
    }

    if (!tools->HasTag(tag2))
        return;

    KeyList* list = (KeyList*)tools->GetList(tag2);
    if (!list)
        return;

    int n;
    Entry12* src;
    if ((list->mFlags10 & 0x30) == 0) {
        if (list->mField12 == 0)
            return;
        n = 1;
        src = (Entry12*)list;
    }
    else {
        n = list->mCount;
        if (n < 1)
            return;
        src = list->mpData;
    }

    int oldCount = (int)(mVec11C.mpEnd - mVec11C.mpBegin);
    for (int i = 0; i < n; ++i) {
        Entry12 e;
        e.mKey = src[i].mKey;
        e.mField4 = 0;
        e.mField8 = 0;
        mVec11C.push_back(e);
    }

    int rem = n - oldCount;
    for (int i = 0; i < rem; ++i) {
        int count = (int)(mVec11C.mpEnd - mVec11C.mpBegin);
        u32 idx = gRandom.RandomUint32Uniform((u32)count);
        if ((int)idx != count - 1) {
            Entry12* last = mVec11C.mpEnd - 1;
            mVec11C.mpBegin[idx] = *last;
        }
        mVec11C.mpEnd -= 1;
    }
}

// @ 0x00c49800
void SPObject::FUN_00c49800(WStr* out)
{
    float f = mFieldC8;
    int i = Rt(f);
    if ((float)i < f)
        i++;
    WStr3(out, (const wchar_t*)0x13f01bc, i);
}

// @ 0x00c49840
void SPObject::FUN_00c49840(WStr* out)
{
    float f = mFieldC8 - 0.5f;
    int i = Rt(f);
    WStr4(out, (const wchar_t*)0x13f01bc, i, mFieldC8 + 0.5f);
}

// @ 0x00c49890
void SPObject::FUN_00c49890(WStr* out)
{
    float f = mFieldC8 + 0.5f;
    int i = Rt(f);
    WStr3(out, (const wchar_t*)0x13f01bc, i);
}

// @ 0x00c498e0
void cSPMission_s00c4_98e0::ShowStarMapDestinationIndicator(char param)
{
    u8* p = (u8*)this;
    if ((*(char(__thiscall**)(void*))((char*)vtbl(this) + 0x158))(this) != 0) {
        return;
    }
    if (param == 0) {
        u32 f = ldu32(p, 0x130);
        if (((f >> 1) & 1) != 0) {
            return;
        }
    }

    // pop the event-log vector (this+0xcc), removing each visual
    int cnt = (ld32(p, 0xd0) - ld32(p, 0xcc)) >> 2;
    for (int i = cnt; i != 0; i--) {
        int tail = ld32(p, 0xd0);
        u32 v = *(u32*)(tail - 4);
        void* vis = FUN_01046fc0((void*)v, 0);
        RemoveVisual(vis, v, 0);
        st32(p, 0xd0, ld32(p, 0xd0) - 4);
    }

    if (ldu32(p, 0x9c) == 0) {
        return;
    }
    if (ld32(p, 0x1e8) == 0) {
        return;
    }
    void* a = FUN_00b8de30((void*)(ld32(*(void**)((char*)p + 0x9c), 0x13c)));
    int local10 = (int)a;
    if (a == 0) {
        return;
    }
    void* b = FUN_00b8de30((void*)(ld32(*(void**)((char*)p + 0x1e8), 0x13c)));
    int ebx = (int)b;
    if (b == 0) {
        return;
    }
    if (ebx == local10) {
        return;
    }
    if (ld32(p, 0x104) != -1) {
        u32 v = ldu32(p, 0x104);
        void* vis = FUN_01046fc0((void*)v, 0);
        RemoveVisual(vis, v, 0);
        st32(p, 0x104, -1);
    }

    int r = (*(int(__thiscall**)(void*, u32))((char*)vtbl(this) + 0xc))(this, 0x463329e);
    u32 off = (r != 0) ? 0xad67641f : 0;
    u32 color = off + 0x9d157d80;
    void* vis = CreateStarRecordVisual(FUN_01046fc0((void*)ebx, 0x166521a5), (u32)ebx, color);
    int local14 = (int)vis;
    if (vis != 0) {
        FUN_01044d70(FUN_01046fc0(vis, 0), 0);
        SimpleVectorPushBack((char*)p + 0x108, (const u32*)&local14);
    }

    int sel;
    if (param != 0) {
        int t = local10; local10 = ebx; sel = t;
    } else {
        sel = local10; local10 = ebx;
    }
    ebx = sel;

    u32 v = ldu32(p, 0x104);
    void* vis2 = CreateStarRecordVisual(FUN_01046fc0((void*)ebx, 0x166521a5), (u32)ebx, 0x49ca7b6);
    st32(p, 0x104, (int)vis2);
    void* inner = FUN_01045120(FUN_01046fc0((void*)(ld32((void*)ebx, 0x70)), (u32)vis2), (u32)vis2);
    int edi = (int)inner;
    FUN_01044d70(FUN_01046fc0((void*)ldu32(p, 0x104), 0), 0);
    u32 colv = (u32)FUN_00c472c0(this);
    u8 vec[12];
    ColorToVector3(vec, colv);
    (*(void(__thiscall**)(void*, int, u8*, int))((char*)vtbl((void*)edi) + 0x40))((void*)edi, 5, vec, 1);

    void* cities = FUN_00b8de30((void*)(ld32((void*)ebx, 0x13c)));
    float* c0 = (float*)FUN_00bb1080b(cities);
    float baseX = c0[0], baseY = c0[1], baseZ = c0[2];
    float* c1 = (float*)FUN_00bb1080b((void*)local10);
    float dX = c1[0] - baseX;
    float dY = c1[1] - baseY;
    float dZ = c1[2] - baseZ;
    int steps = (int)(long long)(sqrtf(dX*dX + dY*dY + dZ*dZ) * 10.0f);
    int n = steps + 1;
    float len = (float)n;
    float inv = 1.0f / len;
    float stepX = dX * inv, stepY = dY * inv, stepZ = dZ * inv;
    float px = baseX, py = baseY, pz = baseZ;
    u8 pv[12];
    int total = 0;
    for (int i = steps + 1; i != 0; i--) {
        *(float*)(pv) = px; *(float*)(pv+4) = py; *(float*)(pv+8) = pz;
        VectorPushBack3((char*)p + 0x108, &total, pv);
        px += stepX; py += stepY; pz += stepZ;
        total = 0;
    }

    int n2 = (steps + 1) * 3;
    void* vis3 = FUN_01045120(FUN_01046fc0((void*)(ld32((void*)ebx, 0x70)), ldu32(p, 0x104)), ldu32(p, 0x104));
    if (vis3 == 0) {
        return;
    }
    u8 tmp[12];
    (*(void(__thiscall**)(void*, int, u8*, int))((char*)vtbl(vis3) + 0x44))(vis3, 0xd, tmp, n2);
}

// @ 0x00c49d10
void SP::cSPMission::ShowStarMapStarClues()
{
    u8* p = (u8*)this;
    int mode = ld32(p, 0xc4) - 0;
    if (mode == 0) {
        goto mode0;
    }
    if (mode - 1 != 0) {
        return;
    }
    {
        u32 v = ldu32(*(void**)((char*)p + 0xe0), 0);
        void* vis = CreateStarRecordVisual(FUN_01046fc0((void*)v, 0x166521a5), v, 0xb7355b47);
        int edi = (int)vis;
        if (vis == 0) return;
        void* inner = FUN_01045120(FUN_01046fc0((void*)(ld32((void*)v, 0x70)), (u32)vis), (u32)vis);
        int vbx = (int)inner;
        FUN_01044d70(FUN_01046fc0(vis, 0), 0);
        VecHeader* vec = (VecHeader*)((char*)p + 0x108);
        if (vec->end < vec->cap) {
            void* old = vec->end;
            vec->end = (char*)vec->end + 4;
            if (old != 0) *(int*)old = edi;
        } else {
            VectorInsertU32(vec->end, &edi, (u32)vec->end);
        }
        float f = *(float*)((char*)p + 0xc8);
        *(float*)0 = 0; (void)f;
        u8 cbuf[4];
        *(float*)cbuf = f;
        (*(void(__thiscall**)(void*, int, u8*, int))((char*)vtbl((void*)vbx) + 0x44))((void*)vbx, 1, cbuf, 1);
        void* mgr = GetMissionManager(ld32(p, 0x17c) ? *(void**)((char*)p + 0x17c) : (void*)p);
        u32 colv = FUN_00febf80(mgr);
        u8 vec2[12];
        ColorToVector3(vec2, colv);
        (*(void(__thiscall**)(void*, int, u8*, int))((char*)vtbl((void*)vbx) + 0x40))((void*)vbx, 5, vec2, 1);
        return;
    }
mode0:
    {
        float f = *(float*)((char*)p + 0xc8);
        u32 v = ldu32(*(void**)((char*)p + 0xe0), 0);
        float eps = *(float*)0x1471064;
        int lo = (int)(f - eps);
        int hi = (int)(f + eps);
        float flo = (float)lo;
        float fhi = (float)hi;
        void* visA = CreateStarRecordVisual(FUN_01046fc0((void*)v, 0x166521a5), v, 0xb7355b47);
        int ebp = (int)visA;
        int local18 = (int)CreateStarRecordVisual(FUN_01046fc0((void*)v, 0x166521a5), v, 0x7ec3db0a);
        if (ebp == 0 || local18 == 0) return;
        void* inner = FUN_01045120(FUN_01046fc0((void*)(ld32((void*)v, 0x70)), (u32)ebp), (u32)ebp);
        int vbx = (int)inner;
        FUN_01044d70(FUN_01046fc0((void*)ebp, 0), 0);
        VecHeader* vec = (VecHeader*)((char*)p + 0x108);
        int iv = ebp;
        SimpleVectorPushBack(vec, (const u32*)&iv);
        u8 fb[4]; *(float*)fb = flo;
        (*(void(__thiscall**)(void*, int, u8*, int))((char*)vtbl((void*)vbx) + 0x44))((void*)vbx, 1, fb, 1);
        (void)fhi;
        int edi2 = (int)FUN_01045120(FUN_01046fc0((void*)(ld32((void*)v, 0x70)), (u32)local18), (u32)local18);
        FUN_01044d70(FUN_01046fc0((void*)local18, 0), 0);
        int iv2 = local18;
        SimpleVectorPushBack(vec, (const u32*)&iv2);
        (*(void(__thiscall**)(void*, int, u8*, int))((char*)vtbl((void*)edi2) + 0x44))((void*)edi2, 1, fb, 1);
        void* mgr = GetMissionManager(ld32(p, 0x17c) ? *(void**)((char*)p + 0x17c) : (void*)p);
        u32 colv = FUN_00febf80(mgr);
        u8 vec2[12];
        ColorToVector3(vec2, colv);
        (*(void(__thiscall**)(void*, int, u8*, int))((char*)vtbl((void*)vbx) + 0x40))((void*)vbx, 5, vec2, 1);
        (*(void(__thiscall**)(void*, int, u8*, int))((char*)vtbl((void*)edi2) + 0x40))((void*)edi2, 5, vec2, 1);
    }
}

// @ 0x00c49f90
void cSPMission_s00c4_98e0::FUN_00c49f90()
{
    u8* p = (u8*)this;
    if (*(u8*)((char*)p + 0x88) == 0) {
        (*(void(__thiscall**)(void*))((char*)vtbl(this) + 0x84))(this);
    }
    int minus1 = -1;
    st32(p, 0x8c, minus1);
    st32(p, 0x94, minus1);
    void* q = *(void**)((char*)p + 0x90);
    if (q != 0) { st32(p, 0x90, 0); (*(void(__thiscall**)(void*))((char*)vtbl(q) + 4))(q); }
    q = *(void**)((char*)p + 0x98);
    if (q != 0) { st32(p, 0x98, 0); (*(void(__thiscall**)(void*))((char*)vtbl(q) + 4))(q); }
    q = *(void**)((char*)p + 0x9c);
    if (q != 0) { st32(p, 0x9c, 0); (*(void(__thiscall**)(void*))((char*)vtbl(q) + 0xc0))(q); }
    q = *(void**)((char*)p + 0x1e8);
    if (q != 0) { st32(p, 0x1e8, 0); (*(void(__thiscall**)(void*))((char*)vtbl(q) + 0xc0))(q); }

    // eastl vector<unsigned>::erase(begin, end) fully inlined.
    {
        VecHeader* vec = (VecHeader*)((char*)p + 0xcc);
        void* first = vec->begin;
        void* last  = vec->end;
        void* pEnd  = vec->end;
        memcpy(vec->begin, last, (unsigned)((char*)pEnd - (char*)last));
        int n = (int)((char*)last - (char*)first) >> 2;
        vec->end = (char*)vec->end + (n * -4);
    }
    ((SpVecE0*)((char*)p + 0xe0))->erase(((SpVecE0*)((char*)p + 0xe0))->mpBegin, ((SpVecE0*)((char*)p + 0xe0))->mpEnd);
    ((SpVec11C*)((char*)p + 0x11c))->erase(((SpVec11C*)((char*)p + 0x11c))->mpBegin, ((SpVec11C*)((char*)p + 0x11c))->mpEnd);

    q = *(void**)((char*)p + 0x180);
    if (q != 0) { st32(p, 0x180, 0); (*(void(__thiscall**)(void*))((char*)vtbl(q) + 4))(q); }
    q = *(void**)((char*)p + 0x1e4);
    if (q != 0) { st32(p, 0x1e4, 0); (*(void(__thiscall**)(void*))((char*)vtbl(q) + 4))(q); }
    q = *(void**)((char*)p + 0x2c);
    if (q != 0) { st32(p, 0x2c, 0); (*(void(__thiscall**)(void*))((char*)vtbl(q) + 4))(q); }
}

// @ 0x00c4a0c0
void SP::cSPMission::PickRewards()
{
    u8* p = (u8*)this;
    typedef float (__thiscall* GetProfitFn)();
    float profit = ((GetProfitFn)FUN_00c453b0)();
    u32 toolKey[3] = { 0, 0, 0 };
    FUN_00c45760(this, toolKey);
    bool positive = (profit > 0.0f);
    int a = (int)toolKey[0];
    int b = (int)toolKey[1];
    int c = (int)toolKey[2];
    u8 differs;
    if (a == *(int*)0x168e844 && b == *(int*)0x168e848 && c == *(int*)0x168e84c) {
        differs = 0;
    } else {
        differs = 1;
    }
    int percent;
    if (positive && differs) percent = 0x32; else percent = 0x64;
    u8 rollA;
    if (positive) {
        u32 rv = gRandom_s00c4_98e0.RandomUint32Uniform(100);
        rollA = (rv < (u32)percent) ? 1 : 0;
        if (rollA) percent = 0x64;
    } else {
        rollA = 0;
        percent = 0x64;
    }
    u8 rollB = 0;
    if (differs) {
        u32 rv = gRandom_s00c4_98e0.RandomUint32Uniform(100);
        rollB = (rv < (u32)percent) ? 1 : 0;
    }
    if (rollA) {
        *(float*)((char*)p + 0xa0) = profit;
        if (ld32(p, 0x9c) != 0 && ld32(p, 0x1e8) != 0) {
            int r = (*(int(__thiscall**)(void*))((char*)vtbl(this) + 0xec))(this);
            *(float*)((char*)p + 0xa0) = *(float*)((char*)p + 0xa0) + (float)(r * 2);
        }
    }
    if (rollB) {
        st32(p, 0xa4, a);
        st32(p, 0xa8, b);
        st32(p, 0xac, c);
        void* mgr = SP_PropertyManager();
        void* out = 0;
        (*(void(__thiscall**)(void*, int, u32, void**))((char*)vtbl(mgr) + 0x2c))(mgr, ld32(p, 0xa4), 0x30608f0b, &out);
        GetPropertyAsText(out, 0x3068d95d, (char*)p + 0xb0);
    }
    FUN_00c495c0(this);
}

// @ 0x00c4a220
bool SP::cSPMission::PickStarClue()
{
    u8* p = (u8*)this;
    if (*(void**)((char*)p + 0x1e8) == 0) {
        return 0;
    }
    void* civ = FUN_00b8de30((void*)(ld32(*(void**)((char*)p + 0x1e8), 0x13c)));
    if (civ == 0) {
        return 0;
    }
    int iVar7 = 0;
    void* prop = *(void**)((char*)p + 0x180);
    float sv = *(float*)0x1470f1c;
    int fv = (int)sv;
    if (prop != 0) {
        void* out = 0;
        if ((*(char(__thiscall**)(void*, u32, void**))((char*)vtbl(prop) + 0x24))(prop, 0x6f1f48ff, &out) != 0) {
            if (*(u16*)((char*)out + 0x12) == 0xd) {
                fv = *(int*)Property_GetFloat(out);
            }
        }
    }

    // clue search record (locals at esp+0x34..)
    u8 rec[0x34];
    for (int i = 0; i < 0x34; i++) rec[i] = 0;
    *(u32*)(rec + 0x14) = 0x1fff;
    *(u32*)(rec + 0x18) = 0x3f;
    *(u32*)(rec + 0x20) = 0xbf800000;
    *(u32*)(rec + 0x24) = 0xbf800000;
    *(u32*)(rec + 0x28) = 0xbf800000;
    if (0.0f < (float)fv) {
        *(u32*)(rec + 0x20) = (u32)fv;
    }
    GetCities(civ, rec + 0x1c, rec + 0x0);
    void* star = SP_StarManager();
    FUN_00bb1080(star, rec + 0x1c, rec + 0x0);
    FUN_00b96130(*(void**)(rec + 0x4), *(void**)(rec + 0x8), 0);

    void* pEnd = *(void**)(rec + 0x8);
    void* it = *(void**)(rec + 0x4);
    int local14 = 0;
    int local10 = -1;
    if (it == pEnd) {
        goto LAB_afterloop;
    }
    do {
        void* pc = *(void**)it;
        if (pc == civ) {
            goto LAB_next;
        }
        u32 kind = (u32)FUN_00801920(pc);
        switch (kind) {
        case 1:
            *(u32*)(rec + 0x30) = 6;
            FUN_00c072f0(p, 0);
            AutoRefCountCtor((char*)p + 0x18, pc);
            FUN_00e1c7f0((char*)p + 0xe0, (char*)p + 0x18);
            FUN_01044d70(0, 0);
            iVar7++;
            break;
        case 2:
            break;
        case 3:
            break;
        case 4: case 7: case 8: case 9: case 10: case 0xb: case 0xc:
            local10 = 1;
            local14 = (int)pc;
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            break;
        }
LAB_next:
        if (iVar7 > 0) goto LAB_done;
        it = (char*)it + 4;
    } while (it != pEnd);

LAB_afterloop:
    if (*(void**)((char*)p + 0x9c) == 0) goto LAB_cleanup0;
    if (local14 == 0 || local10 == 0) {
        // add a fresh visual
    } else {
        // add using local14
    }
LAB_done:
    if (ld32(p, 0xc4) == -1) {
        void* a = *(void**)((char*)p + 0xe0);
        if (a == 0) goto LAB_cleanup0;
        float d = 0.0f;
        (void)d;
        FUN_010434e0(civ, a);
        if (0) { *(void**)((char*)p + 0xcc) = 0; }
    }
LAB_cleanup0:
    FUN_00ae6970((char*)p + 0xe0);
    return 1;
}

// @ 0x00c4a6b0
bool SP::cSPMission::HandleMessage(unsigned int msg, void * m)
{
    u8* p = (u8*)this;
    if (msg > 0x35ec3de) {
        if (msg != 0x4249453) {
            return false;
        }
        u8* a = *(u8**)((char*)m + 0x1c);
        cSPMission* mis = (cSPMission*)((char*)this - 0x34);
        (*(void(__thiscall**)(void*, u8*))((char*)vtbl(mis) + 0x190))(mis, a);
        return true;
    }
    if (msg == 0x35ec3de) {
        if (ld32(p, 0x148) != 0) return true;
        void* c = *(void**)((char*)m + 8);
        if (c == 0) return true;
        if (ld32(c, 0xc) != 0) return true;
        if (ld32(c, 0x38) != (int)0xc8fbf7d7) return true;
        if (ld32(c, 0x3c) != 0x49aa3a54) return true;
        u32 r = (u32)FUN_006c0200(c, (void*)ld32(c, 0x34));
        if ((*(char(__thiscall**)(void*, u32))((char*)vtbl(this) + 0x134))(this, r) == 0) return true;
        u32 r2 = (u32)FUN_006c0200(c, (void*)ld32(c, 0x34));
        int idx = (*(int(__thiscall**)(void*, u32))((char*)vtbl(this) + 0x110))(this, r2);
        if (idx != -1) {
            void* s = (*(void*(__thiscall**)(void*, int))((char*)vtbl(this) + 0xa4))(this, idx);
            u8 buf[12];
            E12_Init(buf, s);
            FUN_00aeb5b0((char*)c + 0x50, buf);
            FUN_00ae9670(buf);
        }
        return true;
    }
    if (msg == 0x248975f) {
        if (GetUniverseContext() != 0) return true;
        if (ld32(p, 0x1b4) != (int)FUN_01021260()) return true;
        cSPMission* mis = (cSPMission*)((char*)this - 0x34);
        void* mgr = GetMissionManager(mis);
        FUN_00febf20(mgr, mis);
        st32(p, 0xfc, ld32(p, 0xfc) | 0x40);
        return true;
    }
    if (msg == 0x2489760) {
        cSPMission* mis = (cSPMission*)((char*)this - 0x34);
        void* mgr = GetMissionManager(mis);
        if (FUN_00bddd00(mgr) != mis) return true;
        void* mgr2 = GetMissionManager(mis);
        FUN_00febf20(mgr2, 0);
        return true;
    }
    return false;
}

// @ 0x00c4a850
bool cBannerListHost::ReadBannerList(void* pArchive)
{
    cVarListSerializer serializer;
    serializer.Construct(this, 0x1574c48, 0x1a80d26);
    bool bResult = serializer.Serialize(pArchive);

    cArchive* pArchiveObject = (cArchive*)pArchive;
    cStreamHost* pHost = ((cArchiveVtbl*)pArchiveObject->mpVtbl)->pGetStreamHost(pArchiveObject);
    cIOStream* pStream = ((cStreamHostVtbl*)pHost->mpVtbl)->pGetStream(pHost);

    int32_t nCount = 0;
    EA_IO_ReadInt32(pStream, &nCount, 1, 0);
    for (int32_t i = 0; i < nCount; ++i) {
        cStreamHost* pEntryHost = ((cArchiveVtbl*)pArchiveObject->mpVtbl)->pGetStreamHost(pArchiveObject);
        cIOStream* pEntryStream = ((cStreamHostVtbl*)pEntryHost->mpVtbl)->pGetStream(pEntryHost);

        int32_t nID = 0;
        EA_IO_ReadInt32(pEntryStream, &nID, 1, 0);

        AutoRefCount<cGameData> pBanner = StarManager((uint32_t)nID)->GetBannerByID((uint32_t)nID);
        mEntries.push_back(pBanner);
    }
    return bResult;
}

// @ 0x00c4a980
void cSPMission_s00c4_a850::PickGiveOnAcceptItems()
{
    if (!mpPropertyList)
        return;

    if (GetBoolProperty(mpPropertyList, 0xf924ebf6)) {
        static const uint32_t kSpeciesTables[3] = { 0xbcd73e89, 0xb8669ec9, 0x37148141 };
        for (uint32_t i = 0; i < 3; ++i) {
            cVec<uint32_t> profiles;
            uint32_t nCount = static_cast<uint32_t>((int32_t)0);
            if (nCount > 0) {
                profiles.mpBegin = 0;
            }
            int32_t nFound = 0;
            (void)nFound;
            (void)kSpeciesTables;
        }
    }
    if (GetBoolProperty(mpPropertyList, 0xf924ebf7)) {
        for (uint32_t i = 0; i < 2; ++i) {
            (void)i;
        }
    }
    if (GetIntProperty(mpPropertyList, 0xf924ebf5) != 0)
        mField190 = 0;
}

// @ 0x00c4ad50
char cSPMission_s00c4_a850::Init()
{
    if (GetBoolProperty(mpPropertyList, 0x874b25b7))
        mFlags |= 1;
    if (GetBoolProperty(mpPropertyList, 0x874b25b8))
        mFlags |= 8;
    if (GetBoolProperty(mpPropertyList, 0x0767624b))
        mFlags |= 0x80;
    if (GetBoolProperty(mpPropertyList, 0xf924ebfd))
        mFlags |= 2;
    if (GetBoolProperty(mpPropertyList, 0xf924ebfe))
        mFlags |= 4;

    bool bValue = true;
    {
        cProperty_s00c4_a850* pProperty;
        if (mpPropertyList && mpPropertyList->Find(0xfa24ee00, &pProperty) && pProperty->mType == 1)
            bValue = *pProperty->GetBool();
    }
    if (!bValue)
        mFlags |= 0x10;
    else
        mFlags &= ~0x10;

    if (mpPropertyList) {
        cProperty_s00c4_a850* pProperty;
        if (mpPropertyList->Find(0x874b25ba, &pProperty) && pProperty->mType == 9)
            mField184 = *pProperty->GetInt();
    }
    if (mpPropertyList) {
        cProperty_s00c4_a850* pProperty;
        if (mpPropertyList->Find(0xf924eeee, &pProperty) && pProperty->mType == 9)
            mField188 = *pProperty->GetInt();
    }
    OnPropertiesLoaded();
    PickGiveOnAcceptItems();
    return 1;
}

// @ 0x00c4af60
Simulator::cMissionAdventure::cMissionAdventure()
{
    Simulator_cGenericPressureEvent_ctor(this);
    mField1f0 = 0;
    mpData1f4 = 0;
    mpVtbl = (void**)0x146d638;
    mpVtbl04 = (void**)0x146dfb4;
    mpVtbl34 = (void**)0x146d624;
}

// @ 0x00c4b0c0
long double __stdcall Simulator_GetAdventurePressureFactor(cAdventurePlanet* pPlanet, void* pArg)
{
    long double fResult = FUN_00c44d00(pPlanet, pArg);
    if (fResult > 0.0) {
        if (GetMissionManager_s00c4_a850(pPlanet)->IsAdventureActive())
            return -1.0f;
        void* pObject = FUN_00b8de30(pPlanet);
        char cFlag = FUN_00bb9bd0(pObject);
        if (FUN_00b8dab0(pPlanet) < 2) {
            if (!FUN_00bba100(pPlanet) && !FUN_00bb9d90(pPlanet) && !FUN_00bb9c30(pObject)) {
                int32_t nKind = pPlanet->mField28;
                if (nKind == 2)
                    return cFlag ? 0.5f : 1.0f;
                if (nKind == 3 || nKind == 4)
                    return 0.25f;
            }
        }
        fResult = -1.0f;
    }
    return fResult;
}

// @ 0x00c4b2b0
void cSPMissionAdventureBase::InitAdventure()
{
    FUN_00c47a10(this);
    StarManager(&mpData1f4, 1)->PickRandomAsset();
    if (mpData1f4) {
        cPlanet_s00c4_a850* pPlanet = GetTargetPlanet();
        void* pPlanetData = pPlanet->mpData13C;
        void* pAssetRef = FUN_01021300(mpData1f4);
        FUN_00baf790(StarManager(pPlanetData, pAssetRef));
        FUN_00b7d580(FUN_00b3d360(pPlanet));
    }
}

// @ 0x00c4b310
void __fastcall Simulator_StartMission(Simulator::cMissionAdventure* pMission)
{
    FUN_00c46b80(pMission);
    ResourceKey_s00c4_a850 aKeys[4] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
    FUN_00e39ab0(0x1af2f7b7, 0, &aKeys[3], &aKeys[2], pMission->mpData1f4, 0, &aKeys[1], &aKeys[0]);
    Achievements::GetController(0x51684fd3)->AwardAchievement();
    Achievements::GetController(0x9c119e6b, 1)->AutoTest();
    if (pMission->mpData1f4) {
        ResourceKey_s00c4_a850 key;
        key.mInstanceID = (uint32_t)pMission->mpData1f4;
        key.mGroupID = 0x366a930d;
        key.mTypeID = g_missionKeyGroup;
        FUN_00f27e00(&key);
    }
}

// @ 0x00c4b3d0
void cMissionMessageHandler::HandleMessage(uint32_t nMessage, void* pMessage)
{
    if (nMessage == 0x43f2592 && GetMission()->mStatus != 1) {
        cMissionMessage* pBody = (cMissionMessage*)pMessage;
        uint32_t nField18 = pBody->mField18;
        uint32_t nField10 = pBody->mField10;
        void* pPlanetRef = pBody->mpPlanetRef;
        cSPMissionMultiDelivery* pMission = GetMission();
        if (pPlanetRef == pMission->GetTargetPlanet()->mpData13C &&
            nField10 == (uint32_t)pMission->mpData1f4 &&
            nField18 == 1)
            pMission->ReturnForRewards();
    }
    BaseHandleMessage(nMessage, pMessage);
}

// @ 0x00c4b440
bool Simulator::cMissionAdventure::InitMission()
{
    (void)0;
    return false;
}

// @ 0x00c4b570
Simulator::cMissionBalance::cMissionBalance()
{
    Simulator_cGenericPressureEvent_ctor(this);
    mField1f0 = 0;
    mThreshold = 0;
    mpVtbl = (void**)0x146d840;
    mpVtbl04 = (void**)0x146dfb4;
    mpVtbl34 = (void**)0x146fbf0;
}
