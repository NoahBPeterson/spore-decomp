// src/game/SPGonzago/SPMission.cpp -- migrated from slice(s) s00c47a10, s00c46ab0, s00c44a20, s00c44080 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMission.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

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

  bool FUN_00b18590(void* stream);
  bool FUN_00b18600(void* stream);

  int Read_c44a20(void* stream);
  bool Write_c44ad0(void* stream);
  void Serialize_c44b40(void* stream);
  void RegisterIds_c44b80();
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
};
}
namespace SP {
class ISpeciesExport {
public:
    virtual void* Export(int flags, const void* pPayload);  // 0x00c59fd0
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

    uint8_t      pad004[0x34];                          // +0x004 .. +0x037 (after the vfptr)
    cSPTimer_s00c4_6ab0     mFeedbackTimer;                        // +0x038
    uint8_t      pad03c[0x3c];                          // +0x03c .. +0x077
    uint32_t     mMissionId;                            // +0x078
    uint8_t      pad07c[0x20];                          // +0x07c .. +0x09b
    ISpaceObject* mpPlanet;                             // +0x09c
    uint8_t      pad0a0[0x60];                          // +0x0a0 .. +0x0ff
    void*        mpPlanetVisual;                        // +0x100
    uint8_t      pad104[0x2c];                          // +0x104 .. +0x12f
    uint32_t     mFlags;                                // +0x130
    uint8_t      pad134[0x48];                          // +0x134 .. +0x17b
    cSPMission_s00c4_6ab0*  mpMissionManager;                      // +0x17c
    void*        mpMissionKey;                          // +0x180
    uint8_t      pad184[0x380];                         // +0x184 .. +0x503
    cSpeciesData mSpecies;                              // +0x504

    ~cSPMission_s00c4_6ab0();
    void FUN_00c46ab0();
    void FUN_00c46b80();
    void GiveOnAcceptItems();  // 0x00c46e20 (SP::cSPMission::GiveOnAcceptItems)
    uint32_t GetConversationFileID();  // 0x00c47040 (SP::cSPMission::GetConversationFileID)
    void FUN_00c470a0();
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
    void FUN_00c474b0();
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

// @ 0x00c46ab0
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::FUN_00c46ab0()
{
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
    return 0xffffffff;
}
}  // namespace SP

// @ 0x00c470a0
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::FUN_00c470a0()
{
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
    (void)planetId;
}
}  // namespace SP

// @ 0x00c47180
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::FUN_00c47180(uint32_t planetId)
{
    (void)planetId;
}
}  // namespace SP

// @ 0x00c471c0
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::FUN_00c471c0()
{
}
}  // namespace SP

// @ 0x00c47240
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::FUN_00c47240()
{
}
}  // namespace SP

// @ 0x00c472c0
namespace SP {
bool __thiscall cSPMission_s00c4_6ab0::FUN_00c472c0()
{
    cSPMission_s00c4_6ab0* pOwner = mpMissionManager ? mpMissionManager : this;
    return GetMissionManager(pOwner)->FUN_00febf80();
}
}  // namespace SP

// @ 0x00c472e0
namespace SP {
void __thiscall cSPMission_s00c4_6ab0::FUN_00c472e0()
{
}
}  // namespace SP

// @ 0x00c47350
void SP::cSPMission::ExportPlanet(SP::cPlanet * targetType, unsigned int pOut)
{
    uint32_t targetType_v = (uint32_t)targetType;
    (void)targetType_v;
    (void)pOut;
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
void __thiscall cSPMission_s00c4_6ab0::FUN_00c474b0()
{
}
}  // namespace SP

// @ 0x00c47610
void SP::cSPMission::GetAnimalSpeciesFromType(unsigned int a1, EA::ResourceMan::Key & a2)
{
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
