// src/game/SPGonzago/SPEmpire.cpp -- migrated from slice(s) s01336df0, s00c32980, s01064990, s00c349e0, s00c33ab0, s00c31960, s00c308b0, s00c2f830 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPEmpire.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cString.h"
#include <intrin.h>
#include "SP/cEmpire.h"
#include "SP/cSPTimer.h"
#include "SP/cVarListSerializer.h"
#include <math.h>
#include "SP/cSPIdentity.h"
#include <string.h>
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/ResourceMan/Key.h"

// ---- items of slice s00c2f830 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __stdcall FUN_00401090(void*);  // species profile lookup (setting)
extern "C" void* FUN_004df550(void*);            // species profile lookup
extern "C" void* __fastcall GetCurrentTerrainSphere(void*); // 0x00f67d90 ecx=obj, returns [ecx+0x74]
struct ThiscallStub {
    void FUN_00c2ed20(int*, int*);      // 0x00c2ed20 load two AutoRefCount slots
    void FUN_00c2fd20(int);             // 0x00c2fd20 tutorial mission Init
    void FUN_00d00a10(int, int);
    int  FUN_00d00780();
    void FUN_00c8f3a0();
    char FUN_00c905a0();
    void FUN_00c7bbc0(int member, int param);
    void FUN_00c7a7d0(int member);
    void FUN_00ac9480(int* src);
    void* FUN_004df550();
    void FUN_00401090();
    void FUN_00ac9480();
    int  FUN_00d2e490();
};
extern "C" void* SP_NounManager_s00c2_f830();
struct Mission {
    char FUN_00c2fc00(int param);
    void FUN_00c2fc10();
    void FUN_00c2fc80();
    int* FUN_00c2fcc0(unsigned int flags);
    void FUN_00c2fd20(int id);
    char FUN_00c2fdd0(int param);
    void FUN_00c2fde0();
    void FUN_00c2fea0();
    int* FUN_00c2fb30();
    int* FUN_00c2ffb0();
    char FUN_00c30090(int param);
    int* FUN_00c300a0(unsigned int flags);
    void FUN_00c30100(int id);
    char FUN_00c30150(int param);
    void FUN_00c301c0(int src);
    void FUN_00c30270(int obj);
    void FUN_00c302b0(char* out);
    void FUN_00c30350(char* out);
    void GetTitleText(char* out);
    void GetBodyText(char* out);
    void GetSummaryText(char* out);
    void GetRewardText(char* out);
    void GetStatusText(char* out);
    void GetSubTitleText(char* out);
    void GetProgressText(char* out);
    void FUN_00c307f0(char* out);
    int* FUN_00c30820(int key);
    void FUN_00c30860(int param);
    void FUN_00c30890();
};
// ---- items of slice s00c2f830 end

// ---- items of slice s00c308b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char DAT_01572b60[];   // 0x01572b60
typedef unsigned int uint;
struct Vec3 { float x, y, z; };
struct Obj;
struct MsgObj;
Obj* __cdecl SP_NounManager();                       // 0x00b3d300
Obj* __cdecl SP_StarManager();                       // 0x00b3d2a0
Obj* __cdecl SP_RelationshipManager();               // 0x00b3d2c0
Obj* __cdecl SP_CommManager();                       // 0x00b3d4a0
MsgObj* __cdecl SP_MessageServer();                  // 0x0067dcc0
Obj* __cdecl EA_ResourceMan_GetManager();            // 0x0067dcd0
Obj* __cdecl SP_GetSpaceRelationshipTuning();        // 0x010407c0
Obj* __cdecl SP_GetSpaceCombatTuning();              // 0x01029940
int  __cdecl SP_PlayerEmpireID();                    // 0x01021090
int  __cdecl SP_UniverseContext();                   // 0x01021080
Obj* __cdecl SP_GetAvatar();                         // 0x00b1fdb0
void* __cdecl EA_Allocate(uint size, const char* owner, int a, int b, int c, int d);  // 0x00f473a0
bool  __cdecl IO_WriteUint32(void* stream, const uint* p, int n, int mode);            // 0x0093aa70
bool  __cdecl IO_ReadInt32(void* stream, uint* p, int n, int mode);                    // 0x0093a780
void  __cdecl FUN_0102c7f0(void* p, int v);                                            // 0x0102c7f0
char  __cdecl FUN_00c70150(Obj* p, Obj* self, int b);                                  // 0x00c70150
Obj*  __cdecl SP_FUN_01021300();                                                       // 0x01021300
Obj*  __cdecl SP_FUN_01021240();                                                       // 0x01021240
int   __cdecl SP_GetCurrentGameMode();                                                 // 0x00b5b800
void  __cdecl GetPropertyAsIntArray(void* prop, int key, int* a, int* b);              // 0x006a07d0
struct OutStream {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual void* m18();                    // +0x18
};
struct IStream {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual OutStream* m20();               // +0x20
};
struct cTail {
    bool m_b6e2d0(Obj* p);                  // 0x00b6e2d0 (ret 4) write
    bool m_b6e340(Obj* p);                  // 0x00b6e340 (ret 4) read
};
struct Obj {
    int   m_885c90();                       // 0x00885c90
    int   m_ba6d80(uint starID);            // 0x00ba6d80
    int   m_ba6dc0(uint starID);            // 0x00ba6dc0
    Obj*  m_bba500();                       // 0x00bba500
    Obj*  m_bba790();                       // 0x00bba790
    void  m_bb4af0(int a, int b);           // 0x00bb4af0 (ActivatePlanetRecordsForQuery, ret 8)
    Obj*  m_bb5ae0(int a);                  // 0x00bb5ae0
    Obj*  m_ce6950();                       // 0x00ce6950 cStarRecordRef::GetCommContext
    void  m_baf630(int a, int b);           // 0x00baf630 (ret 8)
    void  m_aeb3e0(int a, int b, int c, int d, int e, int f, int g, int h); // 0x00aeb3e0
    Obj*  m_b8de30();                       // 0x00b8de30
    // cTerrainEditor
    Obj*  m_f67d90();                       // 0x00f67d90 GetCurrentTerrainSphere
    bool  m_c7a710(uint id);                // 0x00c7a710 (ret 4)
    bool  m_c7a770(uint id);                // 0x00c7a770 (ret 4)
    void  m_c7a830(uint id);                // 0x00c7a830 (ret 4)
    void  m_c7bba0(uint id);                // 0x00c7bba0 (ret 4)
    void  m_c7bb80(uint id);                // 0x00c7bb80 (ret 4)
    void  m_c7bbf0(uint id, uint v);        // 0x00c7bbf0 (ret 8)
    int   m_c75420();                       // 0x00c75420
    void  m_c759a0();                       // 0x00c759a0
    // relationship manager
    bool  m_d01f20(int a, int b);           // 0x00d01f20 (ret 8)
    bool  m_d01fb0(int a, int b);           // 0x00d01fb0 (ret 8)
    float m_d01b80(int a, int b, int key);  // 0x00d01b80 (ret 0xc)
    float m_d00a10(int a, int b, int c);    // 0x00d00a10 (ret 0xc)
    // tuning
    float m_1040860();                      // 0x01040860
    float m_0097eeb0();                     // 0x0097eeb0
    float m_00fb8a00();                     // 0x00fb8a00
    int   m_102a360();                      // 0x0102a360 cSPSpaceCombatTuning::GetWeaponLevel
    float m_1029cc0(int lvl);               // 0x01029cc0 GetBackgroundFighterDPS
    float m_1029d50(int lvl);               // 0x01029d50 GetBackgroundBomberDPS
    float m_1029de0(int lvl);               // 0x01029de0 GetBackgroundTurretDPS
    float m_102a630(int idx, int lvl);      // 0x0102a630 GetUFOHealth
    // player-city music / win-text / misc
    Obj*  m_eb0ea0();                       // 0x00eb0ea0 cPlayerCityMusic ctor (returns this)
    Obj*  m_eab410(int v);                  // 0x00eab410 (ret 4)
    int   m_10107b0(int id);                // 0x010107b0 (ret 4)
    // resource manager (0x0067dcd0): vtable slot 3
    virtual void v0();
    virtual void v4();
    virtual void v8();
    virtual bool Query(void* p, int a, int b, int c, int d, int e);
};
struct MsgObj {
virtual void mv0();
virtual void mv1();
virtual void mv2();
virtual void mv3();
virtual void mv4();
virtual void mv5();
    virtual int send(int a, int b, int c, int d);   // vtable[0x18]
};
struct cCivData;
Vec3* __fastcall cCivData_GetCities(cCivData* self);  // 0x005c65e0
class cVarListSerializer {
public:
    cVarListSerializer(void* pOwner, const void* pKey, uint id);  // 0x00692f90 (ret 0xc)
    bool Serialize(IStream* s);                                   // 0x00692900 (ret 4)
    bool SerializeStream(IStream* s);                             // 0x00693e10 (ret 4)
};
struct cSPTimer {
    uint8_t m18;                  // +0x18 running flag
    int64_t GetElapsedTime();     // 0x00bc3190
    void    Stop();               // 0x00bc3110
    void    FUN_00bc3170();       // 0x00bc3170
};
struct WinTextRef {
    void** m_assign(void* value);       // 0x00b5f950 (ret 4)
};
struct cEmpire {
    uint8_t  pad00[0x58];
    uint32_t mArchetype;                 // +0x58
    uint8_t  pad5c[0x84 - 0x5c];
    uint32_t mEmpireID;                  // +0x84
    cCivData** mCitiesBegin;             // +0x88
    cCivData** mCitiesEnd;               // +0x8c
    uint8_t  pad90[0xb0 - 0x90];
    int32_t  mUFOKey;                    // +0xb0
    int32_t  mEmpireMoney;               // +0xb4
    uint8_t  padb8[0xc4 - 0xb8];
    float    mPosX;                      // +0xc4
    float    mPosY;                      // +0xc8
    float    mPosZ;                      // +0xcc
    uint8_t  padd0[0xd8 - 0xd0];
    int32_t  mWeaponryLevel;             // +0xd8
    uint8_t  paddc[0xe0 - 0xdc];
    float    mBgFighterDPS;              // +0xe0
    float    mBgBomberDPS;               // +0xe4
    float    mBgTurretDPS;               // +0xe8
    uint8_t  padec[0xf0 - 0xec];
    float*   mUFOHealth;                 // +0xf0
    uint8_t  padf4[0x104 - 0xf4];
    void*    mMusic;                     // +0x104
    uint8_t  pad108[0x128 - 0x108];
    cSPTimer mRelationshipTimer;         // +0x128
    // __thiscall members (ret N): declared here so the first stack argument lands on the stack.
    int   FUN_00c308e0(Obj* p);          // 0x00c308e0 (ret 4)
    void  FUN_00c309b0(uint arg);        // 0x00c309b0 (ret 4)
    float GetUFOHealth(int idx);         // 0x00c31920 (ret 4)
    void  FUN_00c30c10(Obj* p);          // 0x00c30c10 (ret 4)
    void  FUN_00c30fa0(const Vec3* p);   // 0x00c30fa0 (ret 4)
    bool  FUN_00c31470(cCivData* c);     // 0x00c31470 (ret 4)
    void  SetHomePlanet(Obj* p);         // 0x00c316c0 (ret 4)
};
cCivData* __fastcall cEmpireFindNearestCity(cEmpire* self, Vec3 pos);
// ---- items of slice s00c308b0 end

// ---- items of slice s00c31960 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
typedef          int   s32;
typedef          short s16;
typedef float  (__thiscall *TFF)(void*);
typedef void*  (__thiscall *TFVP)(void*);
typedef u8     (__thiscall *TFBU)(void*, u32);
typedef s32    (__thiscall *TFIP)(void*);
float  __cdecl FUN_00c317a0(void* self);               // 0x00c317a0 cEmpire::GetWeaponryLevel (thiscall)
void*  __cdecl FUN_00c31730(void* self);               // 0x00c31730 cEmpire::GetHomePlanet (thiscall)
void*  __stdcall FUN_01029940(u32 level);              // 0x01029940 SP::GetSpaceCombatTuning
float  __cdecl FUN_0102a780(void* self);               // 0x0102a780 GetTurretHealth (thiscall)
u32    __cdecl FUN_00a68fb0(void* self, u32 n);        // 0x00a68fb0 RandomUint32Uniform (ecx=0x1601760)
void*  __cdecl FUN_01002bd0(void);                     // 0x01002bd0 SP::SpaceGameGet
s32    __cdecl FUN_00c702f0(u32 key);                 // 0x00c702f0
u32    __cdecl FUN_005c65e0(void* self);               // 0x005c65e0 SP::cCivData::GetCities (thiscall)
char   __cdecl FUN_00c31080(void* a, void* b);         // 0x00c31080
void*  __cdecl FUN_01021300(void);                     // 0x01021300
void*  __cdecl FUN_00b3d300(u32 id);                   // 0x00b3d300 SP::NounManager
void*  __cdecl FUN_00f67d90(void* self);               // 0x00f67d90 cTerrainEditor::GetCurrentTerrainSphere (thiscall)
char   __cdecl FUN_00c7a890(void* self);               // 0x00c7a890
char   __cdecl FUN_00c7bc20(void* self, u32 a);        // 0x00c7bc20
s32    __cdecl FUN_01021090(void);                     // 0x01021090 GetPlayerEmpireID
void*  __cdecl FUN_00b3d2c0(void);                     // 0x00b3d2c0 SP::RelationshipManager
void*  __cdecl FUN_00b3d2a0(void);                     // 0x00b3d2a0 SP::StarManager
float  __cdecl FUN_00d01b80(void* self, u32 a, u32 b, u32 c); // 0x00d01b80 (thiscall ecx=relmgr)
void   __cdecl FUN_00d06240(void* self, u32 a, u32 b, u32 c, float f); // 0x00d06240 RecordEvent (thiscall)
void*  __cdecl FUN_00ba9370(void* self, u32 id);       // 0x00ba9370 cStarManager::GetEmpireByID (thiscall)
void*  __cdecl FUN_00baf700(void* self);               // 0x00baf700 (thiscall)
void*  __cdecl FUN_00885c90(void* self);               // 0x00885c90 (thiscall)
char   __cdecl FUN_00d01b50(void* self, u32 a, u32 b); // 0x00d01b50 (thiscall ecx=relmgr)
char   __cdecl FUN_00d01fb0(void* self, u32 a, u32 b); // 0x00d01fb0 (thiscall ecx=relmgr)
void*  __cdecl FUN_00bc3170(void* self);               // 0x00bc3170 (thiscall)
s32    __cdecl FUN_00ba6d80(void* self, u32 a);        // 0x00ba6d80 BannerList helper (thiscall)
void*  __cdecl FUN_0106ac90(void* self, u32 a);        // 0x0106ac90 (thiscall)
void*  __cdecl FUN_00ce6950(void* self);               // 0x00ce6950 GetCommContext (thiscall)
void*  __cdecl FUN_00b3d4a0(u32 a, void* b);           // 0x00b3d4a0 CommManager
void   __cdecl FUN_00aeaa80(void* self, u32 a, u32 b, u32 c); // 0x00aeaa80 SpaceTool::RemoveMatching2 (thiscall)
void*  __cdecl FUN_0067de30(void);                     // 0x0067de30 SP::PropertyManager
char   __cdecl FUN_00410370(void* a, u32 b, void* c);  // 0x00410370 TryGetUIntProperty
void*  __cdecl FUN_00fd9c60(void);                     // 0x00fd9c60
float  __cdecl FUN_0102f660(void* self, void* a);      // 0x0102f660 (thiscall)
void*  __cdecl FUN_005bf0e0(void* a, void* b);         // 0x005bf0e0 GetEditorPropertyList
char   __cdecl FUN_006a1250(void* a, u32 b, void* c);  // 0x006a1250 SP::GetPropertyAsKey
#define VT(obj, off) (*(void***)(obj))[(off) / 4]
// ---- items of slice s00c31960 end

// ---- items of slice s00c33ab0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*    g_16dda8c;   // 0x016dda8c
extern void*    g_16e0d08;   // 0x016e0d08
extern char     g_13ebb38[]; // 0x013ebb38  allocator name
extern float    g_13eb1bc;   // 0x013eb1bc  (-1.0f)
typedef unsigned int uintptr_t;
void* __cdecl operator_new_sp(unsigned size, const char* name,
                              int a, int b, void* c, int d);   // 0x00f473a0
void  __cdecl operator_delete_arr(void* p);                    // 0x00f47380
void* __cdecl FUN_0067dcc0(void);                              // 0x0067dcc0  MessageServer
void* __cdecl FUN_00b3d300(void);                              // 0x00b3d300  NounManager
void* __cdecl FUN_00b3d3e0(void);                              // 0x00b3d3e0  EventLog
void* __cdecl FUN_01021240(void);                              // 0x01021240
void* __cdecl FUN_01021080(void);                              // 0x01021080  GetUniverseContext
void* __cdecl FUN_01021090_s00c3_3ab0(void);                              // 0x01021090  GetPlayerEmpireID
bool  __cdecl FUN_00c70150(void* a, void* b, void* c);         // 0x00c70150
void  __cdecl FUN_00c737a0(void* planet, uint32_t id);         // 0x00c737a0  cPlanet_LoadModuleData
void* __cdecl FUN_00c8c2a0(void* a);                           // 0x00c8c2a0
void* __cdecl FUN_006782c0(void* first, void* last, void* dst); // 0x006782c0  eastl::copy_impl::do_copy
void* __stdcall SpaceGameGet(int a, int b);                    // 0x01002bd0
void* __cdecl FUN_011e0744(void* dst, void* src, unsigned n);  // import thunk -> memcpy
struct MC {
    int   f_00ce6950();                       // 0x00ce6950  cStarRecordRef::GetCommContext
    int   f_00ba7280();                       // 0x00ba7280
    void  f_00e25bd0(void* first, void* last);// 0x00e25bd0  vector::erase
    void* f_00bba790();                       // 0x00bba790
    void  f_00aea5d0(void* pos, void* v);     // 0x00aea5d0  DoInsertPtr
    void  f_004b0a10(void* pos, int n, void* value);  // 0x004b0a10  vector insert
    void* f_00bf2c60();                       // 0x00bf2c60  cCultureSet ctor
    void* f_00b63890();                       // 0x00b63890  cGonzagoTimer ctor
    void* f_00ba6d80(unsigned id);            // 0x00ba6d80
    void* f_00bb9b80();                       // 0x00bb9b80
    void* f_00bb9b90(void* a);                // 0x00bb9b90
    int   f_00b8dab0();                       // 0x00b8dab0
    void* f_00885c90();                       // 0x00885c90
    bool  f_00d01f50(void* a, void* b);       // 0x00d01f50
    void* f_00f67d90();                       // 0x00f67d90  cTerrainEditor::GetCurrentTerrainSphere
    void* f_00c78450(void* a);                // 0x00c78450  NoteWarEndedWithPlayer
    void* f_00dd8640(uint32_t a, uint32_t b, uint32_t c,
                     uint32_t d, uint32_t e, uint32_t f);  // 0x00dd8640 PostFeedbackEvent
    void* f_00bfc5f0();                       // 0x00bfc5f0  SetGameDataOwner2 / GetPlayerTribe
    void* f_00fe5430();                       // 0x00fe5430
    void  f_00c327a0(void* a);                // 0x00c327a0
    void  f_00c32830(void* a);                // 0x00c32830
    void* f_01022150(void* planet);           // 0x01022150  ActivatePlanet
    void  f_00b6f280();                       // 0x00b6f280  cSPIdentity ctor
    void  f_00579a90(const wchar_t* s);       // 0x00579a90  wstring::range_initialize
    void* f_005c65e0();                       // 0x005c65e0  cCivData::GetCities
    void  f_00babb70(void* pos, int n, void* value);  // 0x00babb70  vector::DoInsertValueN
};
#define VF(o, off)  (*(void**)(*(char**)(o) + (off)))
#define ADDREF(o)   ((void(__thiscall*)(void*))VF(o, 0))(o)
#define RELEASE(o)  ((void(__thiscall*)(void*))VF(o, 4))(o)
struct AutoRef {
    void* mpObject;
    AutoRef(void* o) : mpObject(o) {
        if (mpObject) ((void(__thiscall*)(void*))VF(mpObject, 0))(mpObject);
    }
    ~AutoRef() {
        if (mpObject) ((void(__thiscall*)(void*))VF(mpObject, 4))(mpObject);
    }
    operator void*() const { return mpObject; }
};
struct EVec {                       // eastl vector header (0x14 bytes in retail)
    void*    mBegin;                // +0x00
    void*    mEnd;                  // +0x04
    void*    mCapacity;             // +0x08
    uintptr_t mPad0c;               // +0x0c
    uintptr_t mPad10;               // +0x10

    void Insert_33da0(void* pos, unsigned n, void* value);  // 0x00c33da0
    void Resize_34710(uint32_t n, void* value);             // 0x00c34710
    uint32_t Size() const { return (uint32_t)(((char*)mEnd - (char*)mBegin) >> 2); }
};
struct Key { uint32_t instanceID, typeID, groupID; };   // 12-byte resource key
struct cSPIdentity_s00c3_3ab0 {
    void*    mpVtbl;                // +0x00
    uint32_t mIDColorID;            // +0x04
    uint8_t  mRest[0x28];           // +0x08
    void Construct();               // 0x00b6f280
};
struct ListAnchor {
    void* mpNext;                   // +0x00
    void* mpPrev;                   // +0x04
};
struct ListNode {
    ListNode* mpNext;               // +0x00
    ListNode* mpPrev;               // +0x04
    uint32_t  mValue;               // +0x08
};
struct RefMsg {
    void*    mpVtbl;                // +0x00
    uint32_t mRefCount;             // +0x04
    void*    mEmpire;               // +0x08
    uint8_t  pad0c[0x24];           // +0x0c
    uint32_t mId;                   // +0x30
    uint8_t  pad34[0x4];            // +0x34
    uint32_t mField38;              // +0x38
};
namespace SP {
struct cEmpire_s00c3_3ab0 {
    void*    mpVtbl;                    // +0x00
    void*    mpVtbl2;                   // +0x04
    uint32_t mnRefCount;                // +0x08
    cSPIdentity_s00c3_3ab0 mIdentity;              // +0x0c
    uint8_t     mEmpireName[0x14];      // +0x3c  eastl::wstring
    uint32_t mFlags;                    // +0x50
    uint32_t mTrait;                    // +0x54
    uint32_t mArchetype;                // +0x58
    EVec     mEnemies;                  // +0x5c
    EVec     mAllies;                   // +0x70
    uint32_t mPoliticalID;              // +0x84
    EVec     mStars;                    // +0x88
    EVec     mNextStarTowardsHome;      // +0x9c
    uint32_t mHomeStar;                 // +0xb0
    uint32_t mHomePlanet;               // +0xb4
    Key      mUFOKey;                   // +0xb8
    Key      mCaptainKey;               // +0xc4
    uint32_t mEmpireMoney;              // +0xd0
    uint8_t  mTravelDistance;           // +0xd4
    uint8_t  pad_d5[0x3];               // +0xd5
    uint32_t mFieldD8;                  // +0xd8
    float    mFieldDC;                  // +0xdc
    float    mFieldE0;                  // +0xe0
    float    mFieldE4;                  // +0xe4
    float    mFieldE8;                  // +0xe8
    float    mFieldEC;                  // +0xec
    EVec     mFieldF0;                  // +0xf0  vector<float>, kept at 12 x -1.0f
    void*    mpCityMusic;               // +0x104
    uint8_t  mCultureSet[0x20];         // +0x108
    uint8_t  mDemandForTribute[0x20];   // +0x128
    ListAnchor mAdventureList;          // +0x148

    cEmpire_s00c3_3ab0();                                  // 0x00c34830
    int   AddAdventure_33cc0(void* key, int arg2);        // 0x00c33cc0
    void  Reset_34140();                                   // 0x00c34140
    void  AddStar(void* star);                             // 0x00c341a0
    void  Destroy();                                       // 0x00c34320
    bool  CollectColonizable_344f0(EVec* out, void* arg2); // 0x00c344f0
    void  AddEnemy_345f0(void* p);                         // 0x00c345f0
    void  AddAlly_34680(void* p);                          // 0x00c34680
    void* f_00bba790();                                    // 0x00bba790 (member form)
    void* f_00b8dab0();                                    // 0x00b8dab0 (member form)
    void* f_00bb9b90(void* a);                             // 0x00bb9b90 (member form)
};  // namespace SP
}
struct DistanceToHome { float x, y, z; };
void __cdecl make_heap_stars(void** first, void** middle, DistanceToHome home);   // 0x00c33330
void __cdecl sort_heap_stars(void** first, void** middle, DistanceToHome home);   // 0x00c333a0
void __cdecl adjust_heap_stars(void** first, int a, int b, int c,
                               void* value, DistanceToHome home);                 // 0x00c32a60
// ---- items of slice s00c33ab0 end

// ---- items of slice s00c349e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short u16;
typedef signed   int   i32;
#define VTSLOT(obj, off) ((*(void***)(obj))[(off) / 4])
#define ADDREF_s00c3_49e0(o)  (((Fn_v_p)VTSLOT((o), 0))((void*)(o)))
#define RELEASE_s00c3_49e0(o) (((Fn_v_p)VTSLOT((o), 4))((void*)(o)))
typedef void  (__thiscall *Fn_v_p)(void*);
typedef void  (__thiscall *Fn_v_ppi)(void*, void*, int);
typedef void  (__thiscall *Fn_v_piii)(void*, int, int, void**);
typedef bool  (__thiscall *Fn_b_pi)(void*, int, void**);
typedef int   (__thiscall *Fn_i_p)(void*);
struct Obj_s00c3_49e0;
struct MsgObj_s00c3_49e0;
struct cEmpire_s00c3_49e0;
struct cStarRecord;
extern "C" void* DAT_016dda8c = 0;                 // 0x016dda8c  cSPBackgroundSimManager*
extern "C" u8    DAT_015b7436 = 0;                 // 0x015b7436  debug "always pick" flag
extern "C" float DAT_01485548 = 1.5f;              // 0x01485548  0x3FC00000
extern "C" float DAT_0146b79c = 0.70710678f;       // 0x0146b79c  0x3F34FDF4  cos(45 deg)
extern "C" float DAT_0140f330 = 45.0f;             // 0x0140f330  45.0f
extern "C" float DAT_01485720 = 1.0f;              // 0x01485720  HK_REAL_ONE
extern "C" float DAT_0146b688 = 0.017453292f;      // 0x0146b688  0x3C8EFA35  pi/180
extern "C" float DAT_0146b68c = 3.402823466e38f;   // 0x0146b68c  FLT_MAX (0x7F7FFFFF)
Obj_s00c3_49e0*    __cdecl SP_StarManager_s00c3_49e0();          // 0x00b3d2a0
Obj_s00c3_49e0*    __cdecl SP_NounManager_s00c3_49e0();          // 0x00b3d300
Obj_s00c3_49e0*    __cdecl SP_CommManager_s00c3_49e0();          // 0x00b3d4a0
Obj_s00c3_49e0*    __cdecl SP_PropertyManager();      // 0x0067de30
MsgObj_s00c3_49e0* __cdecl SP_MessageServer_s00c3_49e0();        // 0x0067dcc0
Obj_s00c3_49e0*    __cdecl SP_ObjectTemplateDB();     // 0x0067cb40
void __cdecl ChangeStarEmpireOwnership(cEmpire_s00c3_49e0* self, void* newOwnerAvatar);  // 0x00c35240
void __cdecl UpdatePosseMembers(void* p);                                     // 0x0102c1a0
char __cdecl FUN_00c70150(void* city, void* empire, int flag);                // 0x00c70150
void __cdecl FUN_00ba5bc0(void* empire, int mode);                            // 0x00ba5bc0
int  __cdecl FUN_00ba7320(void* arr);                                         // 0x00ba7320
void __cdecl FUN_00c34060(cStarRecord** begin, cStarRecord** end,
                          float x, float y, float z);                         // 0x00c34060
struct HashMap {
    void* m0;
    void* mBegin;
    void* mEnd;
    void  Build(void* out, int n, void* key);                                 // 0x00c33da0 (ret 0xc)
};
struct RefVector {
    void  Resize(int count, void* out);                                       // 0x00c34710 (ret 8)
};
struct Obj_s00c3_49e0 {
    Vec3*  m_5c65e0();                        // 0x005c65e0  cCivData::GetCities
    int*   m_41e990();                        // 0x0041e990  Property::GetInt
    float* m_41ea70();                        // 0x0041ea70  Property::GetFloat
    void*  m_b1fdb0();                        // 0x00b1fdb0  cGameNounManager::GetAvatar (this+0x54)
    void   m_af0d40(void* p);                 // 0x00af0d40  (ret 4)
    int    m_b8de30();                        // 0x00b8de30
    int    m_b8dab0();                        // 0x00b8dab0
    int    m_885c90();                        // 0x00885c90  (this+0x1d8)
    void*  m_bba790();                        // 0x00bba790  {begin, end, cap} triple
    void   m_bb4af0(void* star, void* flag);  // 0x00bb4af0  (ret 8)
    void   m_bb9c10(int v);                   // 0x00bb9c10  (ret 4)
    int    m_ba6d80(u32 starID);              // 0x00ba6d80  (ret 4)
    int    m_ba6dc0(u32 starID);              // 0x00ba6dc0  (ret 4)
    void*  m_ba9370(void* avatarID);          // 0x00ba9370  cStarManager::GetEmpireByID (ret 4)
    void   m_baf630(int empireID, int flag);  // 0x00baf630  (ret 8)
    void*  m_baf700(void* arg);               // 0x00baf700  (ret 4)
    void*  m_ce6950();                        // 0x00ce6950  cStarRecordRef::GetCommContext
    void   m_aeab40(void* key);               // 0x00aeab40  SpaceTool::RemoveByKey (ret 4)
    void   m_aea720(int key, void* ctx, int v);// 0x00aea720 SpaceTool::RemoveMatching (ret 0xc)
    void   m_1022150(void* planet);           // 0x01022150  cSPBackgroundSimManager::ActivatePlanet (ret 4)
    void   m_1021ab0(void* colony);           // 0x01021ab0  cSPBackgroundSimManager::RemovePlayerColony (ret 4)
    void   m_c37180(void* model, int flag);   // 0x00c37180  cSPGameDataUFO::SetDesiredModel (ret 8)
    void** m_b21340(int a, int b, int c, int d, int e); // 0x00b21340 GetGameDataVector (ret 0x14)
};
struct MsgObj_s00c3_49e0 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
    virtual void slot14(int a, int b, int c);         // vtable[0x14]
    virtual void slot18(int a, int b, int c, int d);  // vtable[0x18]
};
struct RandomLCG {
    float RandomDoubleUniform();              // 0x009360d0  (this in ecx, returns float in st0)
};
struct cEmpire_s00c3_49e0 {
    u8   pad00[0x50];
    u32  mFlags;                              // +0x50
    i32  mTrait;                              // +0x54
    i32  mArchetype;                          // +0x58
    u8   pad5c[0x84 - 0x5c];
    u32  mEmpireID;                           // +0x84
    cStarRecord** mStarsBegin;                // +0x88
    cStarRecord** mStarsEnd;                  // +0x8c
    u8   pad90[0x9c - 0x90];
    cStarRecord** mNextStar;                  // +0x9c
    u8   pada0[0xb0 - 0xa0];
    i32  mUFOKey;                             // +0xb0
    i32  mEmpireMoney;                        // +0xb4
    i32  mUFOKey3[3];                         // +0xb8

    void  AddStar(void* star);                        // 0x00c341a0 (ret 4)
    char  FUN_00c31bf0(u32 empireID);                 // 0x00c31bf0 (ret 4)
    void  SetHomePlanet(Obj_s00c3_49e0* planet);                 // 0x00c316c0 (ret 4)
    void  Destroy();                                  // 0x00c34320
    void* FUN_00c352f0(void* p);                      // 0x00c352f0 (ret 4)
    void  FUN_00c34e70(Obj_s00c3_49e0* p);                       // 0x00c34e70 (ret 4)
    int   RemoveStar(cStarRecord* star, char flag);   // 0x00c34ee0 (ret 8)
    int   UpdateStarGraph();                          // 0x00c349e0
    void  PickRandomPersonality();                    // 0x00c35320
    void  SetUFOKey(int* key);                        // 0x00c35740 (ret 4)
};
// ---- items of slice s00c349e0 end

// ---- items of slice s01064990 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void  (__thiscall *Tc2ii)(void*, int, int);
typedef void  (__thiscall *Tc2pi)(void*, void*, int);
#define VTS(o, off) (*(void**)((char*)*(void**)(o) + (off)))
class RefObj
{
public:
    virtual void AddRef();       // +0x00
    virtual void Release();      // +0x04
    virtual void v08();          // +0x08
    virtual void v0c();          // +0x0c
};
void*  FUN_00b3d3d0();
void*  FUN_00b3d3f0();
void*  MessageServer_67dcc0();
class cString12;
class SimSlot
{
public:
    char  mPad00[0x5c];
    void* mpE30;        // +0x5c
};
class E30Obj
{
public:
    void Method_e30a60(int v);
};
class CLayout
{
public:
    void* FindWindowByID(int id, int flag);
};
class CFeedItem
{
public:
    void  Reserve_666630(int a, int b);
    void  Refresh_6666c0(const wchar_t* text);
    void  FUN_00666660(int a);
    bool  CheckFlag_666680(int a);
    void  Release();
};
class CFeedList
{
public:
    void  FUN_006628d0();
    void  FUN_00662920(int on);
    void* FUN_00662a20(int a);
    void  FUN_00662c10(void* item);
    void  FUN_00663350(int a);
    unsigned FUN_00664600();
    void* FUN_00664610(unsigned idx);
};
class cString12
{
public:
    void* mpBegin;        // +0x00
    void* mpEnd;          // +0x04
    void* mpCap;          // +0x08
    int   mFlag0c;        // +0x0c

    void  Assign_01064d80(const void* begin, const void* end);
    cString12* InsertRange_01064df0(const void* begin, const void* end);
    void  Swap_01065510(cString12* other);
    void  Resize_01065860(uint32_t n);
    void  Assign2_010652d0(const void* begin, const void* end);
    void  Reserve_01065270(uint32_t n);
    void  Init_6b5770(uint32_t a, int b, int c);
    const wchar_t* GetText_6b55c0();
};
class cEmpire_s0106_4990;
struct Sub48
{
    void  Init_00e0a390();
    void  FUN_00e0a5c0();
    void  FUN_00e0a400();
    bool  FUN_00e0a780(int a, void* b);
    void* FUN_00e09c90(int a, int b, int c);
    char  mBody[0x70];
};
struct FilterNode
{
    FilterNode* mpNext;    // +0
    void*       mpPrev;    // +4
    void*       mpKey;     // +8
};
class cEmpire_s0106_4990
{
public:
    void*       mpVtbl0;        // +0x00
    char        mPad04[4];      // +0x04
    void*       mpVtbl1;        // +0x08
    void*       mpVtbl2;        // +0x0c
    char        mPad10[4];      // +0x10
    int         m14;            // +0x14
    CLayout*    mpLayout;       // +0x18
    char        mPad1c[0x34 - 0x1c];
    FilterNode  mFilterHead;    // +0x34
    char        mb40;           // +0x40
    char        mPad41[3];
    void*       m44;            // +0x44
    Sub48       m48;            // +0x48
    void*       mpSFV;          // +0xb8
    void*       mpMsgServer;    // +0xbc
    void*       mpIdentity;     // +0xc0
    int         mMsgId;         // +0xc4
    int         mC8;            // +0xc8
    int         mCC;            // +0xcc
    CFeedList*  mpFeedList;     // +0xd0
    CFeedItem*  mpSelected;     // +0xd4

    void InitBase_00e18bb0();
    void OnWinProcAdd_010829f0(int arg);
    void BaseDestroy_00e18810();
    void BaseDestroy2_00e18980();
    void Show_00e18860(int arg);
    void SetText_00e18890(void* text);

    cEmpire_s0106_4990();
    ~cEmpire_s0106_4990();

    void Destroy_01064990();
    void OnWinProcAdd_01064a00(int arg);
    void PopulateLeft_01064b60();
    void Init_01064fd0();  // 0x01064fd0 (cEmpire::Init_01064fd0)
    void PopulateFeed_010655a0();  // 0x010655a0 (cEmpire::PopulateFeed_010655a0)
    void Show_01065900(int arg);
};
class cEmpireC
{
public:
    void* mpVtblC;        // this+0x00 = outer+0x0c
    char  mPad04[0x34];   // this+0x04 .. this+0x37
    void* m44;            // this+0x38 = outer+0x44
    char  mPad3c[0x8c];   // this+0x3c .. this+0xc7
    CFeedItem* mpSelected;// this+0xc8 = outer+0xd4
    bool Ret_01065360(int id, void* ev);
    bool BaseHandler_00e18600(int a, void* b);
};
static inline cEmpire_s0106_4990* empireFromC(void* p) { return (cEmpire_s0106_4990*)((char*)p - 0x0c); }
// ---- items of slice s01064990 end

// ---- items of slice s00c32980 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_146b68c;    // 0x0146b68c  FLT_MAX
extern float g_13f1cac;    // 0x013f1cac
extern float g_1572b54;    // 0x01572b54
extern float g_1572b58;    // 0x01572b58
extern float g_1572b5c;    // 0x01572b5c
extern float g_168de78;    // 0x0168de78
extern float g_168de7c;    // 0x0168de7c
extern float g_168de80;    // 0x0168de80
extern void* g_1667bac;    // 0x01667bac  eastl::gEmptyString16 begin
extern void* g_1667bae;    // 0x01667bae  eastl::gEmptyString16 end
extern char  g_13ef094[];  // 0x013ef094  base vtable
extern char  g_13eb938[];  // 0x013eb938  base vtable
extern char  g_146b768[];  // 0x0146b768
extern char  g_146b764[];  // 0x0146b764
extern char  g_146b748[];  // 0x0146b748
void* __cdecl FUN_00b6f0c0(u32 id);                            // 0x00b6f0c0  cSPColorRGB::ColorFromID
bool  __cdecl FUN_005bf0e0(void* key, void** out);             // 0x005bf0e0  GetEditorPropertyList
bool  __cdecl FUN_006a1250_s00c3_2980(void* prop, u32 hash, void* out);   // 0x006a1250  SP::GetPropertyAsKey
void* __cdecl FUN_00f473a0(unsigned size, const char* name,
                           int a, int b, void* c, int d);      // 0x00f473a0  operator new
void  __cdecl FUN_00f47380(void* p);                           // 0x00f47380  operator delete
bool  __cdecl FUN_004232c0(void* a, void* b);                  // 0x004232c0  Vector3Equal
void  __cdecl FUN_00b2af00(void* a, void* b);                  // 0x00b2af00  swap
void  __cdecl FUN_0093aa70(void* io, const void* p, int n, int f);  // 0x0093aa70  EA::IO::WriteUint32
void  __cdecl FUN_0093a780(void* io, void* p, int n, int f);   // 0x0093a780  EA::IO::ReadInt32
struct P {
    void* p;
    P(void* o = 0) : p(o) { if (p) ADDREF(p); }
    P(const P& o) : p(o.p) { if (p) ADDREF(p); }
    ~P() { if (p) RELEASE(p); }
    P& operator=(const P& o) {
        void* n = o.p; void* const t = p;
        if (n != t) { if (n) ADDREF(n); p = n; if (t) RELEASE(t); }
        return *this;
    }
    operator void*() const { return p; }
};
struct EVec_s00c3_2980 {                       // eastl vector header (0x14 bytes in retail)
    void*    mBegin;                // +0x00
    void*    mEnd;                  // +0x04
    void*    mCapacity;             // +0x08
    uintptr_t mPad0c;               // +0x0c
    uintptr_t mPad10;               // +0x10

    uint32_t Size() const { return (uint32_t)(((char*)mEnd - (char*)mBegin) >> 2); }
};
struct cSPColorRGB_s00c3_2980 { float r, g, b; };
struct cSPIdentity_s00c3_2980 {
    void*       mpVtbl;             // +0x00
    uint32_t    mIDColorID;         // +0x04
    uint8_t     mIDNameMap[0x1c];   // +0x08
    cSPColorRGB_s00c3_2980 mColor;             // +0x24  cached colour
};
namespace SP {
struct cEmpire_s00c3_2980 {
    void*       mpVtbl;                 // +0x00
    void*       mpVtbl2;                // +0x04
    uint32_t    mnRefCount;             // +0x08
    cSPIdentity_s00c3_2980 mIdentity;              // +0x0c
    uint8_t     mEmpireName[0x14];      // +0x3c  eastl::wstring
    uint32_t    mFlags;                 // +0x50
    uint32_t    mTrait;                 // +0x54
    uint32_t    mArchetype;             // +0x58
    EVec_s00c3_2980        mEnemies;               // +0x5c
    EVec_s00c3_2980        mAllies;                // +0x70
    uint32_t    mPoliticalID;           // +0x84
    EVec_s00c3_2980        mStars;                 // +0x88
    EVec_s00c3_2980        mNextStarTowardsHome;   // +0x9c
    uint32_t    mHomeStar;              // +0xb0
    uint32_t    mHomePlanet;            // +0xb4
    Key         mUFOKey;                // +0xb8
    Key         mCaptainKey;            // +0xc4
    uint32_t    mEmpireMoney;           // +0xd0
    uint32_t    mTravelDistance;        // +0xd4
    uint32_t    mFieldD8;               // +0xd8
    float       mFieldDC;               // +0xdc
    float       mFieldE0;               // +0xe0
    float       mFieldE4;               // +0xe4
    float       mFieldE8;               // +0xe8
    float       mTurretHealth;          // +0xec
    EVec_s00c3_2980        mUFOHealth;             // +0xf0
    void*       mpCityMusic;            // +0x104
    uint8_t     mCultureSet[0x20];      // +0x108
    uint8_t     mDemandForTribute[0x20];// +0x128
    ListAnchor  mAdventureList;         // +0x148

    void RebindPropertyKey();                    // 0x00c32980
    cSPColorRGB_s00c3_2980 GetColor();                      // 0x00c32cd0
    void  Destroy_33410();                       // 0x00c33410
    void  RefreshName_33580();                   // 0x00c33580
    void  SetSpecies(void* species);             // 0x00c33690
};  // namespace SP
}
struct MC_s00c3_2980 {
    void* f_00ba6d80(u32 id);                   // 0x00ba6d80
    void* f_00bba500();                         // 0x00bba500
    void* f_00bb9b80();                         // 0x00bb9b80
    void* f_00bb9b90(void* a);                  // 0x00bb9b90
    int   f_00bb9ae0();                         // 0x00bb9ae0
    int   f_00885c90();                         // 0x00885c90
    void  f_00bb1080(void* a);                  // 0x00bb1080
    int   f_00b1fdb0();                         // 0x00b1fdb0  GetAvatar
    void* f_00ba9370(u32 id);                   // 0x00ba9370  GetEmpireByID
    void* f_005c65e0();                         // 0x005c65e0  GetCities
    void  f_00b6f380(void* s);                  // 0x00b6f380  cSPIdentity::SetName
    void  f_00bb9b90_(void* a);                 // 0x00bb9b90
    void  f_00bb5b50(void* s);                  // 0x00bb5b50
    void* f_00c30c80(float a, float b);         // 0x00c30c80
    void  f_00f67d90();                         // 0x00f67d90
    void* f_00f67d90v();                        // 0x00f67d90 (returns value)
    void  f_00c759a0();                         // 0x00c759a0
    void  f_00b638b0();                         // 0x00b638b0  ~cGonzagoTimer
    void  f_00ae6970();                         // 0x00ae6970  ~eastl::vector
    void  f_00b6edf0();                         // 0x00b6edf0  ~cSPIdentity
    void  f_009a9600(void* child);              // 0x009a9600  DoNukeSubtree
    float*f_00b6e4b0(void* out, float r, float g, float b);  // 0x00b6e4b0
};
float* __cdecl FUN_00b6e4b0(void* out, float r, float g, float b);  // 0x00b6e4b0
void   __cdecl FUN_00b6f140(float r, float g, float b);             // 0x00b6f140
void   __cdecl FUN_00b6f180(void);                                  // 0x00b6f180
bool   __cdecl FUN_00b6e1e0(u32 idx);                               // 0x00b6e1e0
void*  __cdecl FUN_00e5c780(void* self, void* key);                 // 0x00e5c780  rbtree::find
void   __cdecl FUN_005c3d90(void* str, const wchar_t* s);           // 0x005c3d90  eastl::wstring::append
void   __cdecl FUN_00423650(void* str, const wchar_t* f, const wchar_t* l); // 0x00423650 assign
void   __cdecl FUN_004da330(void* species, void* out);              // 0x004da330  GetUiName
struct RBNode {
    RBNode* mpLeft;      // +0x00
    RBNode* mpRight;     // +0x04
    RBNode* mpParent;    // +0x08
    uint8_t pad0c[0x4];  // +0x0c
    u32     mKey;        // +0x10
    void*   mpValue;     // +0x14
};

void __cdecl promote_heap_stars(P* first, int top, int pos, P value, DistanceToHome home); // 0x00c32160
struct ListNode_s00c3_2980 { ListNode_s00c3_2980* mpNext; ListNode_s00c3_2980* mpPrev; u32 mValue; };
// ---- items of slice s00c32980 end

// ---- items of slice s01336df0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0133_6df0; 
}
typedef eastl::string8_s0133_6df0 string8_s0133_6df0;
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
typedef void  (*ReadTextFunction_t)(const string8_s0133_6df0&, void*);
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
struct Attribute
{
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault = 0)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }

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
bool Read_00572810(ISerializerReadStream* pStream, void* pData);  // 0x00572810
}
namespace Simulator {
bool Read_00ac87c0(ISerializerReadStream* pStream, void* pData);  // 0x00ac87c0
}
namespace Simulator {
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);  // 0x00ae3430
}
namespace Simulator {
bool Write_00572840(ISerializerWriteStream* pStream, void* pData);  // 0x00572840
}
namespace Simulator {
bool Write_00ac87f0(ISerializerWriteStream* pStream, void* pData);  // 0x00ac87f0
}
namespace Simulator {
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);  // 0x00ae3450
}
namespace Simulator {
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);  // 0x00bca960
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0133_6df0& text, void* pData);  // 0x00692ff0
}
namespace Simulator {
void ReadText_00693090(const string8_s0133_6df0& text, void* pData);  // 0x00693090
}
namespace Simulator {
void ReadText_00693150(const string8_s0133_6df0& text, void* pData);  // 0x00693150
}
namespace Simulator {
void ReadText_00694c80(const string8_s0133_6df0& text, void* pData);  // 0x00694c80
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0133_6df0& text, void* pData);  // 0x00c2e4e0
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);  // 0x00692fb0
}
namespace Simulator {
void WriteText_00694c10(char* pBuffer, void* pData);  // 0x00694c10
}
namespace Simulator {
void WriteText_00694ee0(char* pBuffer, void* pData);  // 0x00694ee0
}
namespace Simulator {
void WriteText_00694f00(char* pBuffer, void* pData);  // 0x00694f00
}
namespace Simulator {
void WriteText_00695080(char* pBuffer, void* pData);  // 0x00695080
}
namespace Simulator {
bool Validate_00b1fbf0();  // 0x00b1fbf0
}
namespace Simulator {
bool Validate_00b6f550();  // 0x00b6f550
}
namespace Simulator {
bool ToXml_0057cde0(void* pData, const char* pName, int depth);  // 0x0057cde0
}
namespace Simulator {
bool ToXml_00675ca0(void* pData, const char* pName, int depth);  // 0x00675ca0
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);  // 0x00ac8050
}
namespace Simulator {
bool ToXml_00acbbc0(void* pData, const char* pName, int depth);  // 0x00acbbc0
}
namespace Simulator {
bool ToXml_00ae5720(void* pData, const char* pName, int depth);  // 0x00ae5720
}
namespace Simulator {
bool Read_00bb9cd0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00bf26b0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c31c80(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00bf1c70(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c34750(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00badf20(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c33820(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00bb9d00(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c32a40(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00bf1cb0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00aca730(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c332a0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00693070(const string8_s0133_6df0& text, void* pData);
}
namespace Simulator {
void WriteText_00694f80(char* pBuffer, void* pData);
}
namespace Simulator {
bool Validate_00b6f860();
}
namespace Simulator {
bool Validate_00befb00();
}
namespace Simulator {
bool Validate_00c31ca0();
}
namespace Simulator {
bool ToXml_00c6c390(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00eafcf0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00595a50(void* pData, const char* pName, int depth);
}
namespace Simulator {
struct AttrStorage { char data[sizeof(Attribute)]; };
}
namespace Simulator {
AttrStorage cEmpire_sAttributes[19];   // 0x01572b60
}
// ---- items of slice s01336df0 end

// @ 0x00c30820
int* Mission::FUN_00c30820(int key)
{
    int* self = (int*)this;
    if (key == 0x179c807 || key == 0x1805e75)
        return self;
    if (key == 0x5593a1a && self != 0)
        return (int*)((char*)self + 0xc);
    return 0;
}

// @ 0x00c30860
void Mission::FUN_00c30860(int param)
{
    int member = ((int*)this)[0x21];
    void* sphere = GetCurrentTerrainSphere(SP_NounManager_s00c2_f830());
    ((ThiscallStub*)sphere)->FUN_00c7bbc0(member, param);
}

// @ 0x00c30890
void Mission::FUN_00c30890()
{
    int member = ((int*)this)[0x21];
    void* sphere = GetCurrentTerrainSphere(SP_NounManager_s00c2_f830());
    ((ThiscallStub*)sphere)->FUN_00c7a7d0(member);
}

// @ 0x00c308b0
bool __fastcall cEmpireIsPlayerCurrentStar(cEmpire* self)
{
    return SP_StarManager()->m_885c90() == (int)self->mEmpireID;
}

// @ 0x00c308e0
int cEmpire::FUN_00c308e0(Obj* p)
{
    if (p != 0)
        if (FUN_00c70150(p, (Obj*)this, 0))
            return 1;
    return 0;
}

// @ 0x00c30910
void __fastcall cEmpireFUN_00c30910(cEmpire* self)
{
    uint id = self->mEmpireID;
    SP_NounManager()->m_f67d90()->m_c7a710(id);
}

// @ 0x00c30930
void __fastcall cEmpireFUN_00c30930(cEmpire* self)
{
    uint id = self->mEmpireID;
    SP_NounManager()->m_f67d90()->m_c7bb80(id);
    id = self->mEmpireID;
    SP_NounManager()->m_f67d90()->m_c7bba0(id);
}

// @ 0x00c30970
void __fastcall cEmpireFUN_00c30970(cEmpire* self)
{
    uint id = self->mEmpireID;
    SP_NounManager()->m_f67d90()->m_c7a770(id);
}

// @ 0x00c30990
void __fastcall cEmpireFUN_00c30990(cEmpire* self)
{
    uint id = self->mEmpireID;
    SP_NounManager()->m_f67d90()->m_c7a830(id);
}

// @ 0x00c309b0
void cEmpire::FUN_00c309b0(uint arg)
{
    uint id = this->mEmpireID;
    SP_NounManager()->m_f67d90()->m_c7bbf0(id, arg);
}

// @ 0x00c309e0
bool __fastcall cEmpireIsHostileToPlayer(cEmpire* self)
{
    Obj* rels = SP_RelationshipManager();
    uint player = (uint)SP_PlayerEmpireID();
    if (self->mEmpireID == player)
        return false;
    uint myId = self->mEmpireID;
    if (myId == (uint)SP_StarManager()->m_885c90()) {
        if (rels->m_d01f20(myId, player))
            return true;
        if (((Obj*)0x16dc798)->m_10107b0(myId) >= 3)
            if (!rels->m_d01fb0(myId, player))
                return true;
        return false;
    }
    if (rels->m_d01b80(myId, player, 0x5b6ce81) > 0.0f) {
        float f = rels->m_d00a10(myId, player, 0);
        if (f >= SP_GetSpaceRelationshipTuning()->m_1040860())
            return false;
    }
    if (rels->m_d01f20(myId, player))
        return true;
    if (((Obj*)0x16dc798)->m_10107b0(myId) >= 3) {
        float f = rels->m_d00a10(myId, player, 0);
        if (f <= SP_GetSpaceRelationshipTuning()->m_0097eeb0())
            return true;
    }
    return false;
}

// @ 0x00c30b40
bool __fastcall cEmpireHasDemandForTributeExpired(cEmpire* self)
{
    int64_t elapsed = self->mRelationshipTimer.GetElapsedTime();
    float t = (float)elapsed * 0.001f;
    return t > *(float*)((char*)SP_GetSpaceRelationshipTuning() + 0x98);
}

// @ 0x00c30bb0
void __fastcall cEmpireFUN_00c30bb0(cEmpire* self)
{
    cSPTimer* t = &self->mRelationshipTimer;
    t->Stop();
    t->FUN_00bc3170();
}

// @ 0x00c30bd0
void* __fastcall cEmpireFUN_00c30bd0(cEmpire* self)
{
    Obj* m = EA_ResourceMan_GetManager();
    void* p = (char*)self + 0xb8;
    if (!m->Query(p, 0, 0, 0, 0, 0))
        FUN_0102c7f0(p, 1);
    return p;
}

// @ 0x00c30c10
void cEmpire::FUN_00c30c10(Obj* p)
{
    int v;
    if (p != 0)
        v = *(int*)((char*)p + 0x70);
    else
        v = -1;
    this->mUFOKey = v;
    SP_StarManager()->m_baf630(*(int*)&this->mEmpireID, (int)p);
    MsgObj* msg = SP_MessageServer();
    msg->send(0x43f2586, 0, 0, 0);
}

// @ 0x00c30c60
int __fastcall cEmpireFUN_00c30c60(cEmpire* self)
{
    int id = self->mUFOKey;
    if (id == -1)
        return 0;
    return SP_StarManager()->m_ba6d80((uint)id);
}

// @ 0x00c30c80
void* __fastcall cEmpireFUN_00c30c80(cEmpire* self)
{
    int id = self->mUFOKey;
    if (id != -1) {
        int v = SP_StarManager()->m_ba6d80((uint)id);
        if (v != 0)
            return ((Obj*)v)->m_bba500();
    }
    return 0;
}

// @ 0x00c30cc0
uint __cdecl FUN_00c30cc0(uint a, int b)
{
    uint r = 0x4e5855b9;
    switch (a) {
    case 0: case 9: case 0x12:
        if (b == 0) return 0xacb9635d;
        if (b == 1) return 0x4fede4a6;
        if (b == 2) return 0xed2bbcc8;
        break;
    case 1: case 10:
        if (b == 0) return 0x04a83b77;
        if (b == 1) return 0x250f78b4;
        if (b == 2) return 0x12486202;
        break;
    case 2: case 0xb:
        if (b == 0) return 0x5d054a25;
        if (b == 1) return 0x076b1a6e;
        if (b == 2) return 0x8aa5a470;
        break;
    case 3: case 0xc:
        if (b == 0) return 0xdf83b46d;
        if (b == 1) return 0xb308c5d6;
        if (b == 2) return 0x21d2a5b8;
        break;
    case 4: case 0xd:
        if (b == 0) return 0x59878688;
        if (b == 1) return 0xacd3a4cf;
        if (b == 2) return 0xf9b2cbad;
        break;
    case 5: case 0xe:
        if (b == 0) return 0xb8196164;
        if (b == 1) return 0x62166b9b;
        if (b == 2) return 0x01100719;
        break;
    case 6: case 0xf: case 0x11:
        if (b == 0) return 0xe80abf05;
        if (b == 1) return 0x901a654e;
        if (b == 2) return 0x18271550;
        break;
    case 7: case 0x10:
        if (b == 0) return 0x401c6160;
        if (b == 1) return 0x86a04027;
        if (b == 2) return 0x3001d0a5;
        break;
    case 8:
        if (b == 0) r = 0x25885eaf;
        else if (b == 1) return 0x7e56d6cc;
        else if (b == 2) return 0x87d7829a;
        break;
    }
    return r;
}

// @ 0x00c30e80
uint __fastcall cEmpireFUN_00c30e80(cEmpire* self)
{
    Obj* sphere = SP_NounManager()->m_f67d90();
    int sel = 1;
    if (sphere != 0)
        sel = sphere->m_c75420();
    return FUN_00c30cc0(self->mArchetype, sel);
}

// @ 0x00c30eb0
const char* __fastcall cEmpireDebugArchetype(cEmpire* self)
{
    switch (self->mArchetype) {
    case 0:  return "Warrior";
    case 1:  return "Trader";
    case 2:  return "Scientist";
    case 3:  return "Shaman";
    case 4:  return "Bard";
    case 5:  return "Zealot";
    case 6:  return "Diplomat";
    case 7:  return "Ecologist";
    case 8:  return "gRob";
    case 9:  return "PlayerWarrior";
    case 10: return "PlayerTrader";
    case 11: return "PlayerScientist";
    case 12: return "PlayerShaman";
    case 13: return "PlayerBard";
    case 14: return "PlayerZealot";
    case 15: return "PlayerDiplomat";
    case 16: return "PlayerEcologist";
    case 17: return "PlayerWanderer";
    case 18: return "PlayerKnight";
    default: return "unknown_archetype";
    }
}

// @ 0x00c30fa0
void cEmpire::FUN_00c30fa0(const Vec3* p)
{
    *(uint*)&this->mPosX = *(const uint*)&p->x;
    *(uint*)&this->mPosY = *(const uint*)&p->y;
    *(uint*)&this->mPosZ = *(const uint*)&p->z;
    SP_NounManager()->m_f67d90()->m_c759a0();
}

// @ 0x00c31080
bool __fastcall cEmpireFUN_00c31080(cEmpire* self, cCivData* a, cCivData* b)
{
    Vec3* ca = cCivData_GetCities(a);
    float ax = ca->x - self->mPosX;
    float ay = ca->y - self->mPosY;
    float az = ca->z - self->mPosZ;
    Vec3* cb = cCivData_GetCities(b);
    float bx = cb->x - self->mPosX;
    float by = cb->y - self->mPosY;
    float bz = cb->z - self->mPosZ;
    return (ay * ay + ax * ax) + az * az < (bz * bz + by * by) + bx * bx;
}

// @ 0x00c31150
bool __fastcall cEmpireWrite(cEmpire* self, IStream* p)
{
    OutStream* out = p->m20();
    uint magic = 0x1805e75;
    IO_WriteUint32(out->m18(), &magic, 1, 0);
    bool ok = ((cTail*)((char*)self + 0xc))->m_b6e2d0((Obj*)p);
    switch (SP_GetCurrentGameMode()) {
    case 0x1654c00: *(int*)((char*)self + 0x4c) = 0; break;
    case 0x1654c01: *(int*)((char*)self + 0x4c) = 1; break;
    case 0x1654c02: *(int*)((char*)self + 0x4c) = 2; break;
    case 0x1654c04: *(int*)((char*)self + 0x4c) = 4; break;
    case 0x1654c05: *(int*)((char*)self + 0x4c) = 5; break;
    }
    cVarListSerializer ser(self, &DAT_01572b60, 0x1a80d26);
    if (ok && ser.Serialize(p))
        return true;
    return false;
}

// @ 0x00c31240
bool __fastcall cEmpireRead(cEmpire* self, IStream* p)
{
    OutStream* out = p->m20();
    uint magic;
    IO_ReadInt32(out->m18(), &magic, 1, 0);
    bool bl = ((cTail*)((char*)self + 0xc))->m_b6e340((Obj*)p);
    cVarListSerializer ser(self, &DAT_01572b60, 0x1a80d26);
    if (bl && ser.SerializeStream(p))
        bl = true;
    else
        bl = false;
    if (*(void**)((char*)self + 0x104) != 0)
        return bl;
    if ((void*)self == (void*)SP_FUN_01021300()) {
        void* pc = EA_Allocate(0x220, "Simulator", 0, 0, 0, 0);
        void* nw;
        if (pc != 0)
            nw = ((Obj*)pc)->m_eb0ea0();
        else
            nw = 0;
        void* old = *(void**)((char*)self + 0x104);
        if (nw == old)
            return bl;
        if (nw != 0)
            (*(void(__thiscall**)(void*))*(void**)nw)(nw);
        *(void**)((char*)self + 0x104) = nw;
        if (old != 0)
            (*(void(__thiscall**)(void*))((*(void***)old)[1]))(old);
        return bl;
    }
    int avatar = SP_StarManager()->m_885c90();
    void* obj;
    if (avatar == (int)self->mEmpireID) {
        void* q = EA_Allocate(0x28, "Simulator", 0, 0, 0, 0);
        obj = (q != 0) ? ((Obj*)q)->m_eab410(4) : 0;
    } else {
        void* q = EA_Allocate(0x28, "Simulator", 0, 0, 0, 0);
        obj = (q != 0) ? ((Obj*)q)->m_eab410(3) : 0;
    }
    ((WinTextRef*)((char*)self + 0x104))->m_assign(obj);
    return bl;
}

// @ 0x00c313d0
cCivData* __fastcall cEmpireFindNearestCity(cEmpire* self, Vec3 pos)
{
    cCivData* best = 0;
    int n = (int)(self->mCitiesEnd - self->mCitiesBegin);
    float bestD = -1.0f;
    for (int i = 0; i < n; i++) {
        Vec3* c = cCivData_GetCities(self->mCitiesBegin[i]);
        float dx = pos.x - c->x;
        float dy = pos.y - c->y;
        float dz = pos.z - c->z;
        float d = sqrtf(dz * dz + dy * dy + dx * dx);
        if (best == 0 || d < bestD) {
            best = self->mCitiesBegin[i];
            bestD = d;
        }
    }
    return best;
}

// @ 0x00c31470
bool cEmpire::FUN_00c31470(cCivData* c)
{
    cCivData** end = this->mCitiesEnd;
    cCivData** p = this->mCitiesBegin;
    while (p != end && *p != c)
        p++;
    return p != end;
}

// @ 0x00c314a0
void __fastcall cEmpireWarnPlayer(cEmpire* self)
{
    if (!SP_NounManager()->m_f67d90()->m_c7a770(self->mEmpireID)) {
        SP_NounManager()->m_f67d90()->m_c7bba0(self->mEmpireID);
        Vec3* c = cCivData_GetCities((cCivData*)SP_FUN_01021240());
        cCivData* city = cEmpireFindNearestCity(self, *c);
        Obj* sr = (Obj*)SP_StarManager()->m_bb5ae0((int)city);
        Obj* ctx = sr->m_ce6950();
        SP_CommManager()->m_aeb3e0((int)self->mEmpireID, (int)city, (int)ctx,
                                    0x95bbbbfc, 0xde4b97ed, 1, 0, 0);
    }
}

// @ 0x00c31550
void __fastcall cEmpireWelcomePlayer(cEmpire* self)
{
    if (SP_NounManager()->m_f67d90()->m_c7a770(self->mEmpireID))
        return;
    SP_FUN_01021240();
    if (SP_UniverseContext() != 2) {
        if ((void*)SP_GetAvatar() == (void*)&self->mEmpireID)
            return;
    }
    SP_NounManager()->m_f67d90()->m_c7bba0(self->mEmpireID);
    if (SP_NounManager()->m_f67d90()->m_c7a710(self->mEmpireID))
        return;
    Vec3* c = cCivData_GetCities((cCivData*)SP_FUN_01021240());
    cCivData* city = cEmpireFindNearestCity(self, *c);
    void* sr = SP_StarManager()->m_bb5ae0((int)city);
    void* ctx = ((Obj*)sr)->m_ce6950();
    SP_CommManager()->m_aeb3e0((int)self->mEmpireID, (int)city, (int)ctx,
                                0x95bbbbfc, 0xaf301a2c, 1, 0, 0);
}

// @ 0x00c31640
bool __fastcall cEmpireFUN_00c31640(cEmpire* self)
{
    if (cEmpireIsHostileToPlayer(self))
        return true;
    uint player = (uint)SP_PlayerEmpireID();
    if (self->mEmpireID == player)
        return false;
    if (((Obj*)0x16dc798)->m_10107b0(self->mEmpireID) >= 2) {
        Obj* rels = SP_RelationshipManager();
        float f = rels->m_d00a10(self->mEmpireID, player, 0);
        if (f <= SP_GetSpaceRelationshipTuning()->m_00fb8a00())
            return true;
    }
    return false;
}

// @ 0x00c316c0
void cEmpire::SetHomePlanet(Obj* p)
{
    int v;
    if (p != 0)
        v = (int)p->m_ce6950();
    else
        v = -1;
    this->mEmpireMoney = v;
    Obj* q = (p != 0) ? p->m_b8de30() : 0;
    int v2;
    if (p != 0 && q != 0)
        v2 = *(int*)((char*)q + 0x70);
    else
        v2 = -1;
    this->mUFOKey = v2;
    SP_StarManager()->m_baf630(*(int*)&this->mEmpireID, (int)q);
    MsgObj* msg = SP_MessageServer();
    msg->send(0x43f2586, 0, 0, 0);
}

// @ 0x00c31730
Obj* __fastcall cEmpireGetHomePlanet(cEmpire* self)
{
    int star = SP_StarManager()->m_ba6d80((uint)self->mUFOKey);
    if (self->mEmpireMoney == -1 && star != 0) {
        Obj* s = (Obj*)star;
        SP_StarManager()->m_bb4af0(star, 0);
        Obj* rec = s->m_bba790();
        self->SetHomePlanet((Obj*)(*(int*)(*(int*)rec)));
    }
    if (self->mEmpireMoney == -1)
        return 0;
    return (Obj*)SP_StarManager()->m_ba6dc0((uint)self->mEmpireMoney);
}

// @ 0x00c317a0
int __fastcall cEmpireGetWeaponryLevel(cEmpire* self)
{
    if (self->mWeaponryLevel >= 0)
        return self->mWeaponryLevel;
    self->mWeaponryLevel = 0;
    cCivData* cd;
    if (self->mUFOKey == -1)
        cd = 0;
    else
        cd = (cCivData*)SP_StarManager()->m_ba6d80((uint)self->mUFOKey);
    Vec3* c = cCivData_GetCities(cd);
    self->mWeaponryLevel = SP_GetSpaceCombatTuning()->m_102a360();
    int a = 0, b = 0;
    SP_GetSpaceCombatTuning();
    Obj* tun = SP_GetSpaceCombatTuning();
    GetPropertyAsIntArray(*(void**)((char*)tun + 8), 0x5e526ce, &b, &a);
    int n = (int)(self->mCitiesEnd - self->mCitiesBegin);
    if (a > 0) {
        int* arr = (int*)b;
        for (int i = a - 1; i > 0; ) {
            a = i;
            if (n >= arr[i])
                self->mWeaponryLevel++;
            i--;
        }
    }
    if (SP_StarManager()->m_885c90() == (int)self->mEmpireID)
        self->mWeaponryLevel++;
    return self->mWeaponryLevel;
}

// @ 0x00c31890
float __fastcall cEmpireGetBackgroundFighterDPS(cEmpire* self)
{
    if (self->mBgFighterDPS <= 0.0f)
        self->mBgFighterDPS = SP_GetSpaceCombatTuning()->m_1029cc0(cEmpireGetWeaponryLevel(self));
    return self->mBgFighterDPS;
}

// @ 0x00c318c0
float __fastcall cEmpireGetBackgroundBomberDPS(cEmpire* self)
{
    if (self->mBgBomberDPS <= 0.0f)
        self->mBgBomberDPS = SP_GetSpaceCombatTuning()->m_1029d50(cEmpireGetWeaponryLevel(self));
    return self->mBgBomberDPS;
}

// @ 0x00c318f0
float __fastcall cEmpireGetBackgroundTurretDPS(cEmpire* self)
{
    if (self->mBgTurretDPS <= 0.0f)
        self->mBgTurretDPS = SP_GetSpaceCombatTuning()->m_1029de0(cEmpireGetWeaponryLevel(self));
    return self->mBgTurretDPS;
}

// @ 0x00c31920
float __thiscall cEmpire::GetUFOHealth(int idx)
{
    float* p = &this->mUFOHealth[idx];
    if (*p < 0.0f)
        *p = SP_GetSpaceCombatTuning()->m_102a630(idx, cEmpireGetWeaponryLevel(this));
    return *p;
}

// @ 0x00c31960
float __fastcall FUN_00c31960(void* self, void* dummy)
{
  (void)dummy;
  if (0.0f >= *(float*)((char*)self + 0xec)) {
    s32 lvl = ((TFIP)FUN_00c317a0)(self);
    void* tuning = FUN_01029940((u32)lvl);
    *(float*)((char*)self + 0xec) = ((TFF)FUN_0102a780)(tuning);
  }
  return *(float*)((char*)self + 0xec);
}

// @ 0x00c31990
float __fastcall FUN_00c31990(void* self, void* dummy)
{
  (void)dummy;
  if (((*(u32*)((char*)self + 0x50) >> 6) & 1) == 0) {
    s32 v = ((TFIP)FUN_00c317a0)(self) + 1;
    return (float)v + (float)v;
  }
  s32 sum = 0;
  void* home = FUN_00c31730(self);
  void* sg = FUN_01002bd0();
  int* end = (int*)(*(int*)((char*)sg + 0x30) + 0x2c);
  int* cur = (int*)*end;
  int* last = (int*)end[1];
  while (cur != last) {
    if ((void*)*cur != home) {
      sum += FUN_00c702f0((u32)*cur);
    }
    cur++;
  }
  return (float)sum * 0.125f;
}

// @ 0x00c31a00
void __fastcall FUN_00c31a00(void* self, void* dummy, s32 amount)
{
  (void)dummy;
  if (99999999 - *(s32*)((char*)self + 0xd0) < amount) {
    *(s32*)((char*)self + 0xd0) = 99999999;
  } else {
    *(s32*)((char*)self + 0xd0) += amount;
  }
  s32 v = *(s32*)((char*)self + 0xd0);
  if (v < 0) {
    v = 0;
    *(s32*)((char*)self + 0xd0) = v;
    return;
  }
  if (v > 99999999) v = 99999999;
  *(s32*)((char*)self + 0xd0) = v;
}

// @ 0x00c31a60
void __fastcall FUN_00c31a60(void* self, void* dummy, s32 v)
{
  (void)dummy;
  if (v < 0) {
    v = 0;
  } else if (v > 99999999) {
    v = 99999999;
  }
  *(s32*)((char*)self + 0xd0) = v;
}

// @ 0x00c31a90
void* __fastcall FUN_00c31a90(void* self, void* dummy, u8 filter)
{
  (void)dummy;
  int n = (int)((*(int*)((char*)self + 0x60) - *(int*)((char*)self + 0x5c)) >> 2);
  if (n <= 0) return 0;
  u32 idx = FUN_00a68fb0((void*)0x01601760, (u32)n);
  int* begin = (int*)*(int*)((char*)self + 0x5c);
  void* cand = (void*)begin[idx];
  if (filter != 0) {
    int i = 0;
    while (((*(u32*)((char*)cand + 0x50) >> 6) & 1) != 0) {
      if (i == n) return 0;
      i++;
      idx = (idx + 1) & (u32)(-((s32)(idx + 1) >= n));
      cand = (void*)begin[idx];
    }
    if (i == n) return 0;
  }
  return cand;
}

// @ 0x00c31b10
bool __fastcall FUN_00c31b10(void* self, void* dummy, s32 id)
{
  (void)dummy;
  int n = (int)((*(int*)((char*)self + 0x60) - *(int*)((char*)self + 0x5c)) >> 2);
  if (n > 0) {
    int* p = (int*)*(int*)((char*)self + 0x5c);
    int i = 0;
    while (*(s32*)((char*)(void*)*p + 0x84) != id) {
      i++;
      p++;
      if (i >= n) return false;
    }
    return true;
  }
  return false;
}

// @ 0x00c31b50
void* __fastcall FUN_00c31b50(void* self, void* dummy, u8 filter)
{
  (void)dummy;
  int n = (int)((*(int*)((char*)self + 0x74) - *(int*)((char*)self + 0x70)) >> 2);
  if (n <= 0) return 0;
  u32 idx = FUN_00a68fb0((void*)0x01601760, (u32)n);
  int* begin = (int*)*(int*)((char*)self + 0x70);
  void* cand = (void*)begin[idx];
  if (filter != 0) {
    if (cand == FUN_01021300()) {
      if (n < 2) return 0;
      cand = (void*)begin[(idx + 1) & (u32)(-((s32)(idx + 1) >= n))];
    }
  }
  return cand;
}

// @ 0x00c31bc0
bool __fastcall FUN_00c31bc0(void* self, void* dummy, void* target)
{
  (void)dummy;
  void* end = (void*)*(int*)((char*)self + 0x74);
  void* p = (void*)*(int*)((char*)self + 0x70);
  while (p != end && *(void**)p != target) p = (char*)p + 4;
  return p != end;
}

// @ 0x00c31bf0
bool __fastcall FUN_00c31bf0(void* self, void* dummy, s32 id)
{
  (void)dummy;
  int n = (int)((*(int*)((char*)self + 0x74) - *(int*)((char*)self + 0x70)) >> 2);
  int i = 0;
  if (n > 0) {
    int* p = (int*)*(int*)((char*)self + 0x70);
    do {
      if (*(s32*)((char*)(void*)*p + 0x84) == id) return 1;
      i++;
      p++;
    } while (i < n);
  }
  return 0;
}

// @ 0x00c31ca0
u8 __cdecl FUN_00c31ca0(u32, void* list)
{
  void* p = *(void**)list;
  while (p != list) p = *(void**)p;
  return 1;
}

// @ 0x00c31d50
void __cdecl FUN_00c31d50(void** first, void** last, float px, float py, float pz)
{
  void** piVar9 = first;
  if (first != last) {
    while (1) {
      piVar9 = piVar9 + 1;
      if (piVar9 == last) break;
      void* pcVar4 = *piVar9;
      void** piVar8 = piVar9;
      if (pcVar4 != 0) {
        (*(void(__thiscall**)(void*))VT(pcVar4, 0))(pcVar4);
      }
      for (; piVar8 != first; piVar8 = piVar8 - 1) {
        void* pcVar5 = piVar8[-1];
        float* c4 = (float*)FUN_005c65e0(pcVar4);
        float f1 = c4[0], f2 = c4[1], f3 = c4[2];
        float* c5 = (float*)FUN_005c65e0(pcVar5);
        if (((c5[2] - pz) * (c5[2] - pz) + (c5[1] - py) * (c5[1] - py)) +
            (c5[0] - px) * (c5[0] - px) <=
            ((f3 - pz) * (f3 - pz) + (f1 - px) * (f1 - px)) +
            (f2 - py) * (f2 - py)) break;
        void* piVar6 = piVar8[-1];
        void* piVar7 = *piVar8;
        if (piVar6 != piVar7) {
          if (piVar6 != 0) {
            (*(void(__thiscall**)(void*))VT(piVar6, 0))(piVar6);
          }
          *piVar8 = piVar6;
          if (piVar7 != 0) {
            (*(void(__thiscall**)(void*))(VT(piVar7, 4)))(piVar7);
          }
        }
      }
      void* pcVar5 = *piVar8;
      if (pcVar4 != pcVar5) {
        if (pcVar4 != 0) {
          (*(void(__thiscall**)(void*))VT(pcVar4, 0))(pcVar4);
        }
        *piVar8 = pcVar4;
        if (pcVar5 != 0) {
          (*(void(__thiscall**)(void*))VT(pcVar5, 0))(pcVar5);
        }
      }
      if (pcVar4 != 0) {
        (*(void(__thiscall**)(void*))(VT(pcVar4, 4)))(pcVar4);
      }
    }
  }
}

// @ 0x00c31ed0
void __cdecl FUN_00c31ed0(void** first, void** last, float px, float py, float pz)
{
  void** p = first;
  for (; p != last; p = p + 1) {
    void* pcVar4 = *p;
    void** piVar9 = p;
    if (pcVar4 != 0) {
      (*(void(__thiscall**)(void*))VT(pcVar4, 0))(pcVar4);
    }
    while (1) {
      void* pcVar5 = piVar9[-1];
      float* c4 = (float*)FUN_005c65e0(pcVar4);
      float f1 = c4[0], f2 = c4[1], f3 = c4[2];
      float* c5 = (float*)FUN_005c65e0(pcVar5);
      if (((c5[2] - pz) * (c5[2] - pz) + (c5[1] - py) * (c5[1] - py)) +
          (c5[0] - px) * (c5[0] - px) <=
          ((f3 - pz) * (f3 - pz) + (f1 - px) * (f1 - px)) +
          (f2 - py) * (f2 - py)) break;
      void* piVar6 = piVar9[-1];
      void* piVar7 = *piVar9;
      if (piVar6 != piVar7) {
        if (piVar6 != 0) {
          (*(void(__thiscall**)(void*))VT(piVar6, 0))(piVar6);
        }
        *piVar9 = piVar6;
        if (piVar7 != 0) {
          (*(void(__thiscall**)(void*))VT(piVar7, 4))(piVar7);
        }
      }
      piVar9 = piVar9 - 1;
    }
    void* pcVar5 = *piVar9;
    if (pcVar4 != pcVar5) {
      if (pcVar4 != 0) {
        (*(void(__thiscall**)(void*))VT(pcVar4, 0))(pcVar4);
      }
      *piVar9 = pcVar4;
      if (pcVar5 != 0) {
        (*(void(__thiscall**)(void*))VT(pcVar5, 4))(pcVar5);
      }
    }
    if (pcVar4 != 0) {
      (*(void(__thiscall**)(void*))VT(pcVar4, 4))(pcVar4);
    }
  }
}

// @ 0x00c32030
void** __cdecl FUN_00c32030(void** pa, void** pb, void** pc, float px, float py, float pz)
{
  void* cb0 = *pb;
  float* cA = (float*)FUN_005c65e0(*pa);
  float f1 = cA[0], f2 = cA[1], f3 = cA[2];
  float* cB = (float*)FUN_005c65e0(cb0);
  if (((cB[2] - pz) * (cB[2] - pz) + (cB[1] - py) * (cB[1] - py)) + (cB[0] - px) * (cB[0] - px) <=
      ((f3 - pz) * (f3 - pz) + (f2 - py) * (f2 - py)) + (f1 - px) * (f1 - px)) {
    if (FUN_00c31080(*pa, *pc)) return pa;
    if (FUN_00c31080(*pb, *pc)) return pb;
  } else {
    if (FUN_00c31080(*pb, *pc)) return pb;
    if (FUN_00c31080(*pa, *pc)) return pb;
    return pa;
  }
  return 0;
}

// @ 0x00c32160
void __cdecl FUN_00c32160(void** base, s32 holeIndex, s32 length, void* cmp, float px, float py, float pz)
{
  s32 parent = (holeIndex - 1) >> 1;
  while (holeIndex > length) {
    float* cA = (float*)FUN_005c65e0(base[parent]);
    float f1 = cA[0], f2 = cA[1], f3 = cA[2];
    float* cB = (float*)FUN_005c65e0((void*)cmp);
    if (((cB[2] - pz) * (cB[2] - pz) + (cB[1] - py) * (cB[1] - py)) + (cB[0] - px) * (cB[0] - px) <=
        ((f3 - pz) * (f3 - pz) + (f1 - px) * (f1 - px)) + (f2 - py) * (f2 - py)) break;
    void* t = base[holeIndex];
    void* v = base[parent];
    if (v != t) {
      if (v != 0) (*(void(__thiscall**)(void*))VT(v, 0))(v);
      base[holeIndex] = v;
      if (t != 0) (*(void(__thiscall**)(void*))VT(t, 4))(t);
    }
    holeIndex = parent;
    parent = (holeIndex - 1) >> 1;
  }
  void* cur = base[holeIndex];
  if ((void*)cmp != cur) {
    if (cmp != 0) (*(void(__thiscall**)(void*))VT(cmp, 0))((void*)cmp);
    base[holeIndex] = (void*)cmp;
    if (cur != 0) (*(void(__thiscall**)(void*))VT(cur, 4))(cur);
  }
  if (cmp != 0) (*(void(__thiscall**)(void*))VT(cmp, 4))((void*)cmp);
}

// @ 0x00c322c0
u8 __fastcall FUN_00c322c0(void* self, void* dummy, u32 bit)
{
  (void)dummy;
  u32 mask = 1u << (bit & 0x1f);
  u32 v = *(u32*)((char*)self + 0xc4) & mask;
  return (u8)(v != 0);
}

// @ 0x00c322f0
void __fastcall FUN_00c322f0(void* self, void* dummy, s32 arg)
{
  (void)dummy;
  void* ren = FUN_00b3d300(*(u32*)((char*)self + 0x84));
  void* sphere = ((TFVP)FUN_00f67d90)(ren);
  if (FUN_00c7a890(sphere) != 0) return;
  ren = FUN_00b3d300(*(u32*)((char*)self + 0x84));
  sphere = ((TFVP)FUN_00f67d90)(ren);
  FUN_00c7bc20(sphere, 1);
  s32 player = FUN_01021090();
  if (*(s32*)((char*)self + 0x84) == player) return;
  void* rel = FUN_00b3d2c0();
  float a = FUN_00d01b80(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x5b6fcc9);
  float b = FUN_00d01b80(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x5b6fcd4);
  if (0.0f < a) return;
  if (0.0f < b) return;
  FUN_00d06240(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x5b6fcc9, 1.0f);
  FUN_00d06240(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x5b6fcd4, 1.0f);
  void* sm = FUN_00b3d2a0();
  void* emp = FUN_00ba9370(sm, *(u32*)((char*)self + 0x84));
  void* sm2 = FUN_00b3d2a0();
  void* rec = FUN_00baf700(sm2);
  void* props = (*(void*(__thiscall**)(void*, u32))VT(rec, 0x28))(rec, 0x5ff85b4);
  float* fp;
  if ((*(u8*)((char*)props + 0x10) & 0x30) == 0) {
    fp = (float*)(-(u32)(*(s16*)((char*)props + 0x12) != 0) & (u32)props);
  } else {
    fp = (float*)*(void**)props;
  }
  (void)emp;
  s32 mode = *(s32*)((char*)FUN_01021300() + 0x58);
  float fv;
  switch (mode) {
    case 9:  fv = fp[0]; break;
    case 10: fv = fp[1]; break;
    case 11: fv = fp[2]; break;
    case 12: fv = fp[3]; break;
    case 13: fv = fp[4]; break;
    case 14: fv = fp[5]; break;
    case 15: fv = fp[6]; break;
    case 16: fv = fp[7]; break;
    default: goto after;
  }
  if (0.0f < fv &&
      FUN_00d01b80(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x5ff85b2) == 0.0f) {
    FUN_00d06240(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x5ff85b2, fv);
  }
  if (fv < 0.0f &&
      FUN_00d01b80(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x5ff85b3) == 0.0f) {
    FUN_00d06240(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x5ff85b3, -fv);
  }
after:
  if (FUN_01002bd0() != 0) {
    void* sg = FUN_01002bd0();
    if (((TFBU)FUN_00c322c0)(sg, 7) != 0 &&
        FUN_00d01b80(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x601df2a) == 0.0f) {
      FUN_00d06240(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x601df2a, 1.0f);
    }
  }
  if (arg != 1 && FUN_00b3d2a0() != 0) {
    void* sm3 = FUN_00b3d2a0();
    void* other = FUN_00885c90(sm3);
    if (*(s32*)((char*)self + 0x84) != (s32)other &&
        FUN_00d01b50(rel, (u32)other, (u32)player) != 0 &&
        FUN_00d01fb0(rel, (u32)other, (u32)player) != 0) {
      FUN_00d01b80(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x601df2a);
      FUN_00d06240(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x68b2938, 1.0f);
    }
  }
}

// @ 0x00c32610
void __fastcall FUN_00c32610(void* self, void* dummy)
{
  (void)dummy;
  FUN_00bc3170((char*)self + 0x128);
  s32 player = FUN_01021090();
  void* rel = FUN_00b3d2c0();
  FUN_00d06240(rel, *(u32*)((char*)self + 0x84), (u32)player, 0x594afff, 1.0f);
  s32 ufo = *(s32*)((char*)self + 0xb0);
  s32 idx;
  if (ufo == -1) {
    idx = 0;
  } else {
    void* sm = FUN_00b3d2a0();
    idx = FUN_00ba6d80(sm, (u32)ufo);
  }
  void* sg = FUN_01002bd0();
  FUN_0106ac90((char*)sg + 0x14, (u32)idx);
  void* home = FUN_00c31730(self);
  void* ctx = FUN_00ce6950(home);
  void* cm = FUN_00b3d4a0(*(u32*)((char*)self + 0x84), ctx);
  FUN_00aeaa80(cm, 0x95bbbbfc, 0x7fc02fbc, (u32)ctx);
}

// @ 0x00c326b0
void* __fastcall FUN_00c326b0(void* self, void* dummy)
{
  (void)dummy;
  char* out = (char*)self + 0xb8;
  if (*(s32*)out != 0) return out;
  void* sm = FUN_00b3d2a0();
  void* player = FUN_00885c90(sm);
  if ((s32)player != *(s32*)((char*)self + 0x84)) {
    void* x = FUN_00fd9c60();
    FUN_0102f660((void*)*(u32*)((char*)x + 0x160), out);
    return out;
  }
  void* held = 0;
  void* pm = FUN_0067de30();
  void* pk = held;
  if (held != 0) {
    held = 0;
    (*(void(__thiscall**)(void*))VT(pk, 4))(pk);
  }
  (*(void(__thiscall**)(void*, u32, u32, void**))VT(pm, 0x2c))(pm, 0x280852f1, 0x2ae0c7e, &held);
  if (held != 0) {
    u32 uval = 0;
    FUN_00410370(held, 0x4ea8a07, &uval);
    *(u32*)out = uval;
    *(u32*)(out + 4) = (u32)0x476a98c7;
    *(u32*)(out + 8) = (u32)0x40656200;
  } else {
    void* x = FUN_00fd9c60();
    FUN_0102f660((void*)*(u32*)((char*)x + 0x160), out);
  }
  if (held != 0) {
    (*(void(__thiscall**)(void*))VT(held, 4))(held);
  }
  return out;
}

// @ 0x00c327a0
void __fastcall FUN_00c327a0(void* self, void* dummy, s32 id)
{
  (void)dummy;
  int n = (int)((*(int*)((char*)self + 0x60) - *(int*)((char*)self + 0x5c)) >> 2);
  int i = 0;
  if (n > 0) {
    int* p = (int*)*(int*)((char*)self + 0x5c);
    while (*(s32*)((char*)(void*)*p + 0x84) != id) {
      i++;
      p++;
      if (i >= n) return;
    }
    if (i != n - 1) {
      int* base = (int*)*(int*)((char*)self + 0x5c);
      int* oldv = (int*)base[i];
      int* newv = (int*)base[n - 1];
      if (newv != oldv) {
        if (newv != 0) (*(void(__thiscall**)(void*))VT(newv, 0))(newv);
        base[i] = (int)newv;
        if (oldv != 0) (*(void(__thiscall**)(void*))VT(oldv, 4))(oldv);
      }
    }
    *(int*)((char*)self + 0x60) -= 4;
    int* tailp = (int*)*(int*)((char*)self + 0x60);
    if (*tailp != 0) {
      (*(void(__thiscall**)(void*))VT(*tailp, 4))((void*)*tailp);
    }
  }
}

// @ 0x00c32830
void __fastcall FUN_00c32830(void* self, void* dummy, s32 id)
{
  (void)dummy;
  int n = (int)((*(int*)((char*)self + 0x74) - *(int*)((char*)self + 0x70)) >> 2);
  int i = 0;
  if (n > 0) {
    int* p = (int*)*(int*)((char*)self + 0x70);
    while (*(s32*)((char*)(void*)*p + 0x84) != id) {
      i++;
      p++;
      if (i >= n) return;
    }
    if (i != n - 1) {
      int* base = (int*)*(int*)((char*)self + 0x70);
      int* oldv = (int*)base[i];
      int* newv = (int*)base[n - 1];
      if (newv != oldv) {
        if (newv != 0) (*(void(__thiscall**)(void*))VT(newv, 0))(newv);
        base[i] = (int)newv;
        if (oldv != 0) (*(void(__thiscall**)(void*))VT(oldv, 4))(oldv);
      }
    }
    *(int*)((char*)self + 0x74) -= 4;
    int* tailp = (int*)*(int*)((char*)self + 0x74);
    if (*tailp != 0) {
      (*(void(__thiscall**)(void*))VT(*tailp, 4))((void*)*tailp);
    }
  }
}

// @ 0x00c328c0
u8 __fastcall FUN_00c328c0(void* self, void* dummy, u32* key)
{
  (void)dummy;
  u32 a = *(u32*)((char*)self + 0xc4);
  u32 b = *(u32*)((char*)self + 0xc8);
  u32 c = *(u32*)((char*)self + 0xcc);
  u32* held = 0;
  for (;;) {
    if (a == key[0] && b == key[1] && c == key[2]) {
      if (held != 0) (*(void(__thiscall**)(void*))VT(held, 4))(held);
      return 1;
    }
    if (held != 0) {
      u32* tmp = held;
      held = 0;
      (*(void(__thiscall**)(void*))VT(tmp, 4))(tmp);
    }
    if (FUN_005bf0e0(&a, &held) == 0) break;
    if (FUN_006a1250(held, 0xd8a4bc9, &a) == 0) break;
  }
  if (held != 0) (*(void(__thiscall**)(void*))VT(held, 4))(held);
  return 0;
}

// @ 0x00c32980
void SP::cEmpire_s00c3_2980::RebindPropertyKey()
{
    Key key = mCaptainKey;
    void* prop = 0;
    for (;;) {
        if (prop) {
            void* old = prop;
            prop = 0;
            RELEASE(old);
        }
        if (!FUN_005bf0e0(&key, &prop)) break;
        mCaptainKey = key;
        if (!FUN_006a1250_s00c3_2980(prop, 0xd8a4bc9, &key)) break;
    }
    MC_s00c3_2980* nm = (MC_s00c3_2980*)FUN_00b3d300();
    MC_s00c3_2980* te = (MC_s00c3_2980*)nm->f_00f67d90v();
    te->f_00c759a0();
    if (prop) RELEASE(prop);
}

// @ 0x00c32a60
void __cdecl FUN_00c32a60(P* first, int top, int heap, int position, P value, DistanceToHome home)
{
    int child = 2 * position + 2;
    while (child < heap) {
        float* a = (float*)((MC_s00c3_2980*)first[child].p)->f_005c65e0();
        float ax = a[0] - home.x, ay = a[1] - home.y, az = a[2] - home.z;
        float* b = (float*)((MC_s00c3_2980*)first[child - 1].p)->f_005c65e0();
        float bx = b[0] - home.x, by = b[1] - home.y, bz = b[2] - home.z;
        if (ax * ax + ay * ay + az * az < bx * bx + by * by + bz * bz) --child;
        first[position] = first[child];
        position = child;
        child = 2 * child + 2;
    }
    if (child == heap) {
        first[position] = first[child - 1];
        position = child - 1;
    }
    promote_heap_stars(first, top, position, value, home);
}

// @ 0x00c32cd0
cSPColorRGB_s00c3_2980 SP::cEmpire_s00c3_2980::GetColor()
{
    u32 id = mIdentity.mIDColorID;
    if (id - 0x53dbcf3 <= 0xb) {
        float* c = (float*)FUN_00b6f0c0(id);
        cSPColorRGB_s00c3_2980 r; r.r = c[0]; r.g = c[1]; r.b = c[2];
        return r;
    }
    SP::cEmpire_s00c3_2980* pe = (SP::cEmpire_s00c3_2980*)FUN_01021300();
    if (pe != this) {
        if (((mFlags >> 6) & 1) != 0) {
            MC_s00c3_2980* banner = 0;
            if (mUFOKey.groupID != 0xffffffff) {
                banner = (MC_s00c3_2980*)((MC_s00c3_2980*)FUN_00b3d2a0())->f_00ba6d80(mUFOKey.groupID);
            }
            if (banner && banner->f_00bb9ae0() == 5 && mIdentity.mIDColorID == 0x53dbcf1) {
                if (FUN_004232c0(&mIdentity.mColor, &g_168de78)) {
                    MC_s00c3_2980* sph = (MC_s00c3_2980*)((MC_s00c3_2980*)this)->f_00c30c80(0.5f, 0.5f);
                    float* src = (float*)((char*)sph + 0x4ec);
                    float* res = FUN_00b6e4b0(&mIdentity.mColor, src[0], src[1], src[2]);
                    mIdentity.mColor.r = res[0];
                    mIdentity.mColor.g = res[1];
                    mIdentity.mColor.b = res[2];
                }
                return mIdentity.mColor;
            }
        }
        MC_s00c3_2980* sm = (MC_s00c3_2980*)FUN_00b3d2a0();
        if (sm->f_00885c90() == (int)mPoliticalID) {
            cSPColorRGB_s00c3_2980 r;
            r.r = g_1572b54; r.g = g_1572b58; r.b = g_1572b5c;
            return r;
        }
        float slots[12];
        for (u32 i = 0; i < 12; ++i)
            slots[i] = FUN_00b6e1e0(i) ? 0.0f : g_146b68c;
        {
            Key key = mUFOKey;
            u32 pad34 = 0, pad38 = 0, pad3c = 0;
            int arr0 = 0, arr1 = 0, arr2 = 0;
            int f48 = 0x1fff;
            int f4c = 0x20;
            float f50 = 0.0f;
            float f54 = g_13eb1bc;
            float f58 = g_13f1cac;
            float f5c = g_13eb1bc;
            int f60 = 0;
            (void)pad34; (void)pad38; (void)pad3c;
            void* banner = 0;
            if (key.groupID != 0xffffffff) {
                banner = ((MC_s00c3_2980*)FUN_00b3d2a0())->f_00ba6d80(key.groupID);
            }
            ((MC_s00c3_2980*)banner)->f_005c65e0();
            // the array header passed to GetCities is an eastl vector header
            struct { int* b; int* e; int* c; int pad; } list;
            list.b = &arr0; list.e = &arr0; list.c = &arr0;
            (void)f48; (void)f4c; (void)f50; (void)f54; (void)f58; (void)f5c; (void)f60;
            MC_s00c3_2980* sm2 = (MC_s00c3_2980*)FUN_00b3d2a0();
            sm2->f_00bb1080(&list);
            for (int* it = list.b; it != list.e; ++it) {
                MC_s00c3_2980* star = (MC_s00c3_2980*)*it;
                int av = star->f_00b1fdb0();
                if (av == -1) continue;
                int av2 = star->f_00b1fdb0();
                MC_s00c3_2980* sm3 = (MC_s00c3_2980*)FUN_00b3d2a0();
                MC_s00c3_2980* emp = (MC_s00c3_2980*)sm3->f_00ba9370(av2);
                if (!emp) continue;
                u32 ci = (u32)(*(u32*)((char*)emp + 0x10) - 0x53dbcf3);
                if (ci > 0xb) continue;
                void* b1 = 0;
                if (*(u32*)((char*)emp + 0xb0) != 0xffffffff) {
                    b1 = ((MC_s00c3_2980*)FUN_00b3d2a0())->f_00ba6d80(*(u32*)((char*)emp + 0xb0));
                }
                void* b2 = 0;
                if (mUFOKey.groupID != 0xffffffff) {
                    b2 = ((MC_s00c3_2980*)FUN_00b3d2a0())->f_00ba6d80(mUFOKey.groupID);
                }
                float* p1 = (float*)((MC_s00c3_2980*)b2)->f_005c65e0();
                float* p2 = (float*)((MC_s00c3_2980*)b1)->f_005c65e0();
                float dx = p1[0] - p2[0], dy = p1[1] - p2[1], dz = p1[2] - p2[2];
                float d = dx * dx + dy * dy + dz * dz;
                if (d < slots[ci] || d == slots[ci]) slots[ci] = d;
            }
        }
        float best = 0.0f;
        int bestIdx = 0;
        for (u32 i = 0; i < 12; ++i) {
            if (slots[i] > best) { bestIdx = (int)i; best = slots[i]; }
        }
        u32 newID = (u32)bestIdx + 0x53dbcf3;
        if ((u32)bestIdx >= 0xc) newID = 0x53dbcf3;
        mIdentity.mIDColorID = newID;
        float* c = (float*)FUN_00b6f0c0(newID);
        cSPColorRGB_s00c3_2980 r; r.r = c[0]; r.g = c[1]; r.b = c[2];
        return r;
    }
    if (mIdentity.mIDColorID != 0x53dbcf1) {
        int hs = (int)((SP::cEmpire_s00c3_2980*)FUN_01021300())->mHomeStar;
        MC_s00c3_2980* spec = 0;
        if (hs != -1) {
            MC_s00c3_2980* b = (MC_s00c3_2980*)((MC_s00c3_2980*)FUN_00b3d2a0())->f_00ba6d80((u32)hs);
            if (b) spec = (MC_s00c3_2980*)b->f_00bba500();
        }
        float* src = (float*)((char*)spec + 0x4ec);
        float* res = FUN_00b6e4b0(&mIdentity.mColor, src[0], src[1], src[2]);
        FUN_00b6f140(res[0], res[1], res[2]);
        FUN_00b6f180();
        mIdentity.mColor.r = res[0];
        mIdentity.mColor.g = res[1];
        mIdentity.mColor.b = res[2];
        mIdentity.mIDColorID = 0x53dbcf1;
    }
    if (mIdentity.mColor.r == g_168de78 && mIdentity.mColor.g == g_168de7c && mIdentity.mColor.b == g_168de80) {
        float* c = (float*)FUN_00b6f0c0(mIdentity.mIDColorID);
        mIdentity.mColor.r = c[0];
        mIdentity.mColor.g = c[1];
        mIdentity.mColor.b = c[2];
    }
    float* c = (float*)FUN_00b6f0c0(mIdentity.mIDColorID);
    cSPColorRGB_s00c3_2980 r; r.r = c[0]; r.g = c[1]; r.b = c[2];
    return r;
}

// @ 0x00c332a0
void __cdecl FUN_00c332a0(void* stream, ListAnchor* list)
{
    int count = 0;
    for (void* n = list->mpNext; n != (void*)list; n = *(void**)n) ++count;
    int c = count;
    void* io = ((TFVP)((*(void***)stream)[8]))(stream);
    void* w = ((TFVP)((*(void***)io)[6]))(io);
    FUN_0093aa70(w, &c, 1, 0);
    for (void* n = list->mpNext; n != (void*)list; n = *(void**)n) {
        void* io2 = ((TFVP)((*(void***)stream)[8]))(stream);
        int v = (int)((ListNode_s00c3_2980*)n)->mValue;
        void* w2 = ((TFVP)((*(void***)io2)[6]))(io2);
        FUN_0093aa70(w2, &v, 1, 0);
    }
    ((TFVP)((*(void***)stream)[7]))(stream);
}

// @ 0x00c33410
void SP::cEmpire_s00c3_2980::Destroy_33410()
{
    mpVtbl = g_146b768;
    mpVtbl2 = g_146b764;
    mIdentity.mpVtbl = g_146b748;
    ListAnchor* anchor = &mAdventureList;
    void* n = anchor->mpNext;
    while (n != (void*)anchor) {
        void* cur = n;
        n = *(void**)n;
        FUN_00f47380(cur);
    }
    ((MC_s00c3_2980*)mDemandForTribute)->f_00b638b0();
    MC_s00c3_2980* culture = (MC_s00c3_2980*)mCultureSet;
    culture->f_009a9600(*(void**)((char*)culture + 0x0c));
    if (mpCityMusic) RELEASE(mpCityMusic);
    void* ufoHealth = mUFOHealth.mBegin;
    if (ufoHealth && *(int*)((char*)ufoHealth - 4) != 0) FUN_00f47380(ufoHealth);
    ((MC_s00c3_2980*)&mNextStarTowardsHome)->f_00ae6970();
    ((MC_s00c3_2980*)&mStars)->f_00ae6970();
    ((MC_s00c3_2980*)&mAllies)->f_00ae6970();
    ((MC_s00c3_2980*)&mEnemies)->f_00ae6970();
    void* nameBegin = *(void**)(mEmpireName + 0);
    void* nameCap = *(void**)(mEmpireName + 8);
    if ((int)(((char*)nameCap - (char*)nameBegin) & 0xfffffffe) > 2 && nameBegin) FUN_00f47380(nameBegin);
    ((MC_s00c3_2980*)&mIdentity)->f_00b6edf0();
    mpVtbl2 = g_13ef094;
    mpVtbl = g_13eb938;
}

// @ 0x00c33580
void SP::cEmpire_s00c3_2980::RefreshName_33580()
{
    if ((int)mHomeStar == -1) return;
    MC_s00c3_2980* banner = (MC_s00c3_2980*)((MC_s00c3_2980*)FUN_00b3d2a0())->f_00ba6d80(mHomeStar);
    if (!banner) return;
    int* p = (int*)banner->f_00bb9b80();
    Key kk = *(Key*)p;
    if (kk.instanceID == 0) return;
    if ((int)mHomeStar == -1) return;
    MC_s00c3_2980* b2 = (MC_s00c3_2980*)((MC_s00c3_2980*)FUN_00b3d2a0())->f_00ba6d80(mHomeStar);
    if (!b2) return;
    MC_s00c3_2980* spec = (MC_s00c3_2980*)b2->f_00bba500();
    if (!spec) return;
    cSPColorRGB_s00c3_2980 col = GetColor();
    (void)col;
    wchar_t* nameBuf[3];
    nameBuf[0] = (wchar_t*)g_1667bac;
    nameBuf[1] = (wchar_t*)g_1667bac;
    nameBuf[2] = (wchar_t*)g_1667bae;
    FUN_004da330(spec, nameBuf);
    ((MC_s00c3_2980*)&mIdentity)->f_00b6f380(nameBuf);
    int key = 2;
    RBNode** pp = (RBNode**)FUN_00e5c780(&mIdentity.mIDNameMap, &key);
    RBNode* node = *pp;
    FUN_005c3d90(mEmpireName, (const wchar_t*)node->mpValue);
    wchar_t* nb = nameBuf[0];
    wchar_t* ne = nameBuf[2];
    if ((int)(((char*)ne - (char*)nb) & 0xfffffffe) > 2 && nb) FUN_00f47380(nb);
}

// @ 0x00c33690
void SP::cEmpire_s00c3_2980::SetSpecies(void* speciesp)
{
    void* pe = FUN_01021300();
    if (pe == (void*)this && speciesp) {
        wchar_t* nameBuf[3];
        void* g = g_1667bac;
        nameBuf[0] = (wchar_t*)g;
        nameBuf[1] = (wchar_t*)g;
        nameBuf[2] = (wchar_t*)g_1667bae;
        FUN_004da330(speciesp, nameBuf);
        ((MC_s00c3_2980*)FUN_00b3d2a0())->f_00bb5b50(nameBuf);
        wchar_t* nb = nameBuf[0];
        wchar_t* ne = nameBuf[2];
        if ((int)(((char*)ne - (char*)nb) & 0xfffffffe) > 2 && nb) FUN_00f47380(nb);
    }
    Key speciesKey = {0, 0, 0};
    if (speciesp) {
        speciesKey.instanceID = *(u32*)((char*)speciesp + 0x504);
        speciesKey.typeID     = *(u32*)((char*)speciesp + 0x508);
        speciesKey.groupID    = *(u32*)((char*)speciesp + 0x50c);
    }
    int n = (int)mStars.Size();
    for (int i = 0; i < n; ++i) {
        void* star = ((void**)mStars.mBegin)[i];
        ((MC_s00c3_2980*)star)->f_00bb9b90(&speciesKey);
    }
    if (speciesp) {
        cSPColorRGB_s00c3_2980 col = GetColor();
        (void)col;
        wchar_t* nameBuf[3];
        void* g = g_1667bac;
        nameBuf[0] = (wchar_t*)g;
        nameBuf[1] = (wchar_t*)g;
        nameBuf[2] = (wchar_t*)g_1667bae;
        FUN_004da330(speciesp, nameBuf);
        ((MC_s00c3_2980*)&mIdentity)->f_00b6f380(nameBuf);
        RBNode* root = (RBNode*)mIdentity.mIDNameMap;
        RBNode* cur = root->mpParent;
        while (cur) {
            if (cur->mKey < 2u) cur = cur->mpRight;
            else { cur = cur->mpLeft; root = cur; }
        }
        // find() inlined rbtree lookup for key == 2
        RBNode* found = (RBNode*)FUN_00e5c780(mIdentity.mIDNameMap, (void*)2);
        const wchar_t* s = (const wchar_t*)found->mpValue;
        const wchar_t* e = s;
        while (*e) ++e;
        FUN_00423650(mEmpireName, s, e);
        (void)cur;
        wchar_t* nb = nameBuf[0];
        wchar_t* ne = nameBuf[2];
        if ((int)(((char*)ne - (char*)nb) & 0xfffffffe) > 2 && nb) FUN_00f47380(nb);
    }
}

// @ 0x00c33820
void __cdecl FUN_00c33820(void* stream, ListAnchor* list)
{
    void* n = list->mpNext;
    while (n != (void*)list) {
        void* cur = n;
        n = *(void**)n;
        FUN_00f47380(cur);
    }
    list->mpNext = list;
    list->mpPrev = list;
    int count = 0;
    void* io = ((TFVP)((*(void***)stream)[8]))(stream);
    void* w = ((TFVP)((*(void***)io)[6]))(io);
    FUN_0093a780(w, &count, 1, 0);
    u32 i = 0;
    while (i < (u32)count) {
        int v;
        void* io2 = ((TFVP)((*(void***)stream)[8]))(stream);
        void* w2 = ((TFVP)((*(void***)io2)[6]))(io2);
        FUN_0093a780(w2, &v, 1, 0);
        ListNode_s00c3_2980* node = (ListNode_s00c3_2980*)FUN_00f473a0(0xc, "Simulator", 0, 0, g_13ebb38, 0xd1);
        if ((char*)node + 8) node->mValue = (u32)v;
        node->mpNext = (ListNode_s00c3_2980*)list;
        node->mpPrev = (ListNode_s00c3_2980*)list->mpPrev;
        ((ListNode_s00c3_2980*)list->mpPrev)->mpNext = node;
        ++i;
        ((ListNode_s00c3_2980*)list)->mpPrev = node;
    }
    ((TFVP)((*(void***)stream)[7]))(stream);
}

// @ 0x00c338f0
void** __cdecl FUN_00c338f0(void** first_, void** last_, void* pivotp, float px, float py, float pz)
{
    void** first = first_;
    void** last = last_;
    for (;;) {
        for (;;) {
            float* a = (float*)((MC_s00c3_2980*)*first)->f_005c65e0();
            float ax = a[0] - px, ay = a[1] - py, az = a[2] - pz;
            float* b = (float*)((MC_s00c3_2980*)pivotp)->f_005c65e0();
            float bx = b[0] - px, by = b[1] - py, bz = b[2] - pz;
            if (bx * bx + by * by + bz * bz <= ax * ax + ay * ay + az * az) break;
            ++first;
        }
        void* p;
        do {
            p = *(last - 1);
            --last;
            float* c = (float*)((MC_s00c3_2980*)pivotp)->f_005c65e0();
            float cx = c[0] - px, cy = c[1] - py, cz = c[2] - pz;
            float* d = (float*)((MC_s00c3_2980*)p)->f_005c65e0();
            float dx = d[0] - px, dy = d[1] - py, dz = d[2] - pz;
            if (!(cx * cx + cy * cy + cz * cz < dx * dx + dy * dy + dz * dz)) break;
        } while (true);
        if (last <= first) break;
        FUN_00b2af00(first, last);
        ++first;
    }
    if (pivotp) RELEASE(pivotp);
    return first;
}

// @ 0x00c33ab0
void eastl_partial_sort_stars(void** first, void** middle, void** last, DistanceToHome home)
{
    make_heap_stars(first, middle, home);
    for (void** it = middle; it < last; ++it) {
        void* pfirst = *first;
        float* a = (float*)((MC*)*it)->f_005c65e0();
        float ax = a[0] - home.x, ay = a[1] - home.y, az = a[2] - home.z;
        float* b = (float*)((MC*)pfirst)->f_005c65e0();
        float bx = b[0] - home.x, by = b[1] - home.y, bz = b[2] - home.z;
        float da = ax * ax + ay * ay + az * az;
        float db = bx * bx + by * by + bz * bz;
        if (da < db) {
            void* tmp = *it;
            if (tmp) ADDREF(tmp);
            void* f = *first;
            void* i = *it;
            if (f != i) {
                if (f) ADDREF(f);
                *it = f;
                if (i) RELEASE(i);
            }
            int n = (int)(((char*)middle - (char*)first) >> 2);
            adjust_heap_stars(first, 0, n, 0, tmp, home);
            if (tmp) RELEASE(tmp);
        }
    }
    sort_heap_stars(first, middle, home);
}

// @ 0x00c33cc0
int SP::cEmpire_s00c3_3ab0::AddAdventure_33cc0(void* key, int)
{
    int v = ((MC*)key)->f_00ce6950();
    ListNode* anchor = (ListNode*)&mAdventureList;
    ListNode* node = anchor->mpNext;
    if (node != anchor) {
        do {
            if (node->mValue == (uint32_t)v) break;
            node = node->mpNext;
        } while (node != anchor);
        if (node != anchor) {
            ListNode* del = node->mpNext->mpPrev;
            del->mpPrev->mpNext = del->mpNext;
            del->mpNext->mpPrev = del->mpPrev;
            operator_delete_arr(del);
        }
    }
    ListNode* p = (ListNode*)operator_new_sp(0xc, "Simulator", 0, 0, g_13ebb38, 0xd1);
    if ((char*)p + 8 != 0) *(uint32_t*)((char*)p + 8) = (uint32_t)v;
    p->mpNext = anchor;
    p->mpPrev = anchor->mpPrev;
    anchor->mpPrev->mpNext = p;
    anchor->mpPrev = p;
    int count = 0;
    for (ListNode* q = anchor->mpNext; q != anchor; q = q->mpNext) ++count;
    void* sm = FUN_00b3d2a0();
    int limit = ((MC*)sm)->f_00ba7280();
    if (count > limit) {
        ListNode* first = anchor->mpNext;
        int out = (int)first->mValue;
        first->mpPrev->mpNext = first->mpNext;
        first->mpNext->mpPrev = first->mpPrev;
        operator_delete_arr(first);
        return out;
    }
    return 0;
}

// @ 0x00c33da0
void EVec::Insert_33da0(void* pos_, unsigned n, void* value_)
{
    char* pos = (char*)pos_;
    char* end = (char*)mEnd;
    unsigned capLeft = (unsigned)(((char*)mCapacity - end) >> 2);
    if (n > capLeft) {
        char* begin = (char*)mBegin;
        unsigned size = (unsigned)((end - begin) >> 2);
        unsigned newCap = size * 2;
        if (size == 0) newCap = 1;
        if (newCap <= size + n) newCap = size + n;
        char* p = (char*)FUN_011e0744(0, begin, (unsigned)(pos - begin));
        unsigned before = (unsigned)((pos - begin) >> 2);
        char* dst = p + before * 4;
        uint32_t v = *(uint32_t*)value_;
        for (unsigned i = 0; i < n; ++i) ((uint32_t*)dst)[i] = v;
        char* p2 = (char*)FUN_011e0744(dst + n * 4, pos, (unsigned)((char*)mEnd - pos));
        uint32_t after = (uint32_t)((end - pos) >> 2);
        mBegin = 0;
        mEnd = p2 + after * 4;
        mCapacity = (void*)(newCap * 4);
        return;
    }
    if (n == 0) return;
    uint32_t v = *(uint32_t*)value_;
    unsigned after = (unsigned)((end - pos) >> 2);
    if (n < after) {
        char* src = end - n * 4;
        memcpy(end, src, n * 4);
        mEnd = (char*)mEnd + n * 4;
        unsigned bytes = (unsigned)((src - pos) >> 2) * 4;
        char* dst = end - bytes;
        memmove(dst, pos, (unsigned)(src - pos));
        for (char* q = pos; q != pos + n * 4; q += 4) *(uint32_t*)q = v;
        return;
    }
    unsigned extra = n - after;
    if (extra != 0) {
        uint32_t* q = (uint32_t*)end;
        for (unsigned i = 0; i < extra; ++i) q[i] = v;
    }
    mEnd = (char*)mEnd + extra * 4;
    memcpy(mEnd, pos, (unsigned)(end - pos));
    mEnd = (char*)mEnd + after * 4;
    for (char* q = pos; q != end; q += 4) *(uint32_t*)q = v;
}

// @ 0x00c34140
void SP::cEmpire_s00c3_3ab0::Reset_34140()
{
    ((MC*)&mStars)->f_00e25bd0(mStars.mBegin, mStars.mEnd);
    ((MC*)&mNextStarTowardsHome)->f_00e25bd0(mNextStarTowardsHome.mBegin, mNextStarTowardsHome.mEnd);
    void* p = mpCityMusic;
    if (p != 0) {
        mpCityMusic = 0;
        RELEASE(p);
    }
}

// @ 0x00c341a0
void SP::cEmpire_s00c3_3ab0::AddStar(void* star)
{
    if (star == 0) return;
    void** first = (void**)mStars.mBegin;
    void** last = (void**)mStars.mEnd;
    for (void** it = first; it != last; ++it) {
        if (*it == star) return;
    }

    void* tmp = star;
    if (tmp) ADDREF(tmp);
    if ((char*)mStars.mEnd < (char*)mStars.mCapacity) {
        void** slot = (void**)mStars.mEnd;
        mStars.mEnd = slot + 1;
        if (slot != 0) {
            *slot = tmp;
            if (tmp) ADDREF(tmp);
        }
    } else {
        ((MC*)&mStars)->f_00aea5d0(mStars.mEnd, &tmp);
    }
    if (tmp) RELEASE(tmp);

    mFlags |= 0x10;
    if (mHomeStar != 0xffffffffu) {
        void* p = ((MC*)FUN_00b3d2a0())->f_00ba6d80(mHomeStar);
        if (p != 0) {
            ((MC*)star)->f_00bb9b90(((MC*)p)->f_00bb9b80());
            void* ms = FUN_01021240();
            if (ms == star && FUN_01021080() == 0) {
                void* srv = FUN_0067dcc0();
                ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))VF(srv, 0x18))
                    (srv, 0x490d429, 0, 0, 0);
            }
        }
    }

    EVec* planets = (EVec*)((MC*)this)->f_00bba790();
    int np = (int)(((char*)planets->mEnd - (char*)planets->mBegin) >> 2);
    for (int i = 0; i < np; ++i) {
        void* planet = ((void**)planets->mBegin)[i];
        if (((MC*)planet)->f_00b8dab0() == 5) {
            FUN_00c737a0(planet, mPoliticalID);
            if (mPoliticalID == (uint32_t)(uintptr_t)FUN_01021090_s00c3_3ab0()) {
                ((MC*)g_16dda8c)->f_01022150(planet);
            }
        }
    }

    mFieldD8 = 0xffffffff;
    void* srv = FUN_0067dcc0();
    ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t))VF(srv, 0x14))(srv, 0x55bd8f7, 0, 0);
}

// @ 0x00c34320
void SP::cEmpire_s00c3_3ab0::Destroy()
{
    if (((MC*)FUN_00b3d2a0())->f_00885c90() == (void*)mPoliticalID) {
        void* a = SpaceGameGet(0xf, 1);
        void* b = ((MC*)a)->f_00bfc5f0();
        ((MC*)b)->f_00fe5430();
    }

    RefMsg* p = (RefMsg*)operator_new_sp(0x40, "App", 0, 0, 0, 0);
    if (p != 0) {
        p->mId = 0;
        p->mpVtbl = (void*)0x13eb90c;
        _InterlockedExchange((volatile long*)&p->mRefCount, 0);
        p->mpVtbl = (void*)0x13eb844;
        p->mField38 = 0;
        ((void(__thiscall*)(void*))VF(p, 4))(p);
    }
    p->mId = 0x4b33711;
    p->mEmpire = this;
    {
        void* srv = FUN_0067dcc0();
        ((void(__thiscall*)(void*, uint32_t, void*, uint32_t, uint32_t))VF(srv, 0x18))
            (srv, p->mId, p, 0, 0);
    }

    int ne = (int)(((char*)mEnemies.mEnd - (char*)mEnemies.mBegin) >> 2);
    for (int i = 0; i < ne; ++i) {
        void* e = ((void**)mEnemies.mBegin)[i];
        ((MC*)e)->f_00c327a0(this);
    }
    int na = (int)(((char*)mAllies.mEnd - (char*)mAllies.mBegin) >> 2);
    for (int i = 0; i < na; ++i) {
        void* a = ((void**)mAllies.mBegin)[i];
        ((MC*)a)->f_00c32830(this);
    }

    void* player = FUN_01021300();
    if (this != player) {
        void* rm = FUN_00b3d2c0();
        if (((MC*)rm)->f_00d01f50(this, player)) {
            void* nm = FUN_00b3d300();
            void* te = ((MC*)nm)->f_00f67d90();
            ((MC*)te)->f_00c78450(this);
        }
    }

    if (g_16e0d08 != 0) *(void**)((char*)g_16e0d08 + 0x1c) = this;

    {
        void* log = FUN_00b3d3e0();
        ((MC*)log)->f_00dd8640(0x88426556, 0x131a9f54, 0, 0, 1, 0);
    }

    int ns = (int)(((char*)mStars.mEnd - (char*)mStars.mBegin) >> 2);
    for (int i = 0; i < ns; ++i) {
        FUN_00c8c2a0(((void**)mStars.mBegin)[i]);
    }
    {
        char* beg = (char*)mStars.mBegin;
        void** it = (void**)FUN_006782c0(mStars.mEnd, mStars.mEnd, beg);
        void** e = (void**)mStars.mEnd;
        for (; it < e; ++it) {
            if (*it) RELEASE(*it);
        }
        mStars.mEnd = beg;
    }

    ((void(__thiscall*)(void*))VF(p, 8))(p);
}

// @ 0x00c344f0
bool SP::cEmpire_s00c3_3ab0::CollectColonizable_344f0(EVec* out, void* arg2)
{
    int ns = (int)(((char*)mStars.mEnd - (char*)mStars.mBegin) >> 2);
    for (int i = 0; i < ns; ++i) {
        void* star = ((void**)mStars.mBegin)[i];
        if (star == 0) continue;
        EVec* list = (EVec*)((MC*)star)->f_00bba790();
        int nm = (int)(((char*)list->mEnd - (char*)list->mBegin) >> 2);
        for (int j = 0; j < nm; ++j) {
            void* item = ((void**)list->mBegin)[j];
            if (item == 0) continue;
            if (FUN_00c70150(item, this, arg2)) {
                if (item) ADDREF(item);
                if ((char*)out->mEnd < (char*)out->mCapacity) {
                    void** slot = (void**)out->mEnd;
                    out->mEnd = slot + 1;
                    if (slot != 0) {
                        *slot = item;
                        if (item) ADDREF(item);
                    }
                } else {
                    ((MC*)out)->f_00aea5d0(out->mEnd, &item);
                }
                if (item) RELEASE(item);
            }
        }
    }
    return out->mBegin != out->mEnd;
}

// @ 0x00c345f0
void SP::cEmpire_s00c3_3ab0::AddEnemy_345f0(void* p)
{
    EVec* v = &mEnemies;
    int n = (int)(((char*)v->mEnd - (char*)v->mBegin) >> 2);
    void** it = (void**)v->mBegin;
    for (int i = 0; i < n; ++i) {
        if (*it == p) return;
        ++it;
    }
    AutoRef ref(p);
    if ((char*)v->mEnd < (char*)v->mCapacity) {
        void** slot = (void**)v->mEnd;
        v->mEnd = slot + 1;
        if (slot != 0) {
            *slot = ref.mpObject;
            if (ref.mpObject) ADDREF(ref.mpObject);
        }
    } else {
        ((MC*)v)->f_00aea5d0(v->mEnd, &ref);
    }
}

// @ 0x00c34680
void SP::cEmpire_s00c3_3ab0::AddAlly_34680(void* p)
{
    EVec* v = &mAllies;
    int n = (int)(((char*)v->mEnd - (char*)v->mBegin) >> 2);
    void** it = (void**)v->mBegin;
    for (int i = 0; i < n; ++i) {
        if (*it == p) return;
        ++it;
    }
    AutoRef ref(p);
    if ((char*)v->mEnd < (char*)v->mCapacity) {
        void** slot = (void**)v->mEnd;
        v->mEnd = slot + 1;
        if (slot != 0) {
            *slot = ref.mpObject;
            if (ref.mpObject) ADDREF(ref.mpObject);
        }
    } else {
        ((MC*)v)->f_00aea5d0(v->mEnd, &ref);
    }
}

// @ 0x00c34710
void EVec::Resize_34710(uint32_t n, void* value)
{
    if (n > Size()) {
        ((MC*)this)->f_00babb70(mEnd, (int)(n - Size()), value);
        return;
    }
    ((MC*)this)->f_00e25bd0((char*)mBegin + n * 4, mEnd);
}

// @ 0x00c34830
SP::cEmpire_s00c3_3ab0::cEmpire_s00c3_3ab0()
{
    mpVtbl = (void*)0x1444434;
    mpVtbl2 = (void*)0x13ef094;
    mnRefCount = 0;
    mIdentity.Construct();
    mpVtbl = (void*)0x146b768;
    mpVtbl2 = (void*)0x146b764;
    mIdentity.mpVtbl = (void*)0x146b748;
    {
        MC* s = (MC*)mEmpireName;
        *(void**)((char*)mEmpireName + 0) = 0;
        *(void**)((char*)mEmpireName + 4) = 0;
        *(void**)((char*)mEmpireName + 8) = 0;
        s->f_00579a90(L"unknown");
    }
    mFlags = 0;
    mTrait = 0;
    mArchetype = 0x11;
    mEnemies.mBegin = 0; mEnemies.mEnd = 0; mEnemies.mCapacity = 0;
    mAllies.mBegin = 0;  mAllies.mEnd = 0;  mAllies.mCapacity = 0;
    mPoliticalID = 0xffffffffu;
    mStars.mBegin = 0; mStars.mEnd = 0; mStars.mCapacity = 0;
    mNextStarTowardsHome.mBegin = 0; mNextStarTowardsHome.mEnd = 0; mNextStarTowardsHome.mCapacity = 0;
    mHomeStar = 0xffffffffu;
    mHomePlanet = 0xffffffffu;
    mUFOKey.instanceID = 0; mUFOKey.typeID = 0; mUFOKey.groupID = 0;
    mCaptainKey.instanceID = 0; mCaptainKey.typeID = 0; mCaptainKey.groupID = 0;
    mEmpireMoney = 0;
    mTravelDistance = 3;
    mFieldD8 = 0xffffffff;
    mFieldDC = g_13eb1bc;
    mFieldE0 = g_13eb1bc;
    mFieldE4 = g_13eb1bc;
    mFieldE8 = g_13eb1bc;
    mFieldEC = g_13eb1bc;
    mFieldF0.mBegin = 0; mFieldF0.mEnd = 0; mFieldF0.mCapacity = 0;
    mpCityMusic = 0;
    ((MC*)mCultureSet)->f_00bf2c60();
    ((MC*)mDemandForTribute)->f_00b63890();
    mAdventureList.mpNext = &mAdventureList;
    mAdventureList.mpPrev = &mAdventureList;

    uint32_t sz = (uint32_t)(((char*)mFieldF0.mEnd - (char*)mFieldF0.mBegin) >> 2);
    float v = -1.0f;
    if (sz < 0xc) {
        ((MC*)&mFieldF0)->f_004b0a10(mFieldF0.mEnd, (int)(0xc - sz), &v);
    } else {
        memcpy((char*)mFieldF0.mBegin + 0x30, mFieldF0.mEnd, 0);
        mFieldF0.mEnd = (char*)mFieldF0.mBegin + 0x30;
    }
    mIdentity.mIDColorID = 0x53dbcf2;
}

// @ 0x00c349e0
int cEmpire_s00c3_49e0::UpdateStarGraph()
{
    if ((this->mFlags & 0x10) == 0)
        return 0;

    float cosThreshold = DAT_0146b79c;
    float scaleLimit = DAT_01485548;

    Obj_s00c3_49e0* prop = 0;
    Obj_s00c3_49e0* pm = SP_PropertyManager();
    if (prop != 0) {
        RELEASE_s00c3_49e0(prop);
        prop = 0;
    }
    ((Fn_v_piii)VTSLOT(pm, 0x2c))(pm, 0xcdf8d12f, 0x2ae0c7e, (void**)&prop);

    if (prop != 0) {
        Obj_s00c3_49e0* out = 0;
        float angle = DAT_0140f330;                       // 45 degrees
        if (((Fn_b_pi)VTSLOT(prop, 0x24))(prop, 0x4bf0dac, (void**)&out)
            && *(u16*)((char*)out + 0x12) == 0xd)
            angle = ((Obj_s00c3_49e0*)out)->m_41ea70()[0];
        cosThreshold = cosf(angle * DAT_0146b688);

        if (((Fn_b_pi)VTSLOT(prop, 0x24))(prop, 0x4bf0dbd, (void**)&out)
            && *(u16*)((char*)out + 0x12) == 0xd) {
            scaleLimit = ((Obj_s00c3_49e0*)out)->m_41ea70()[0];
            if (scaleLimit < DAT_01485720)
                scaleLimit = DAT_01485720;
        }
    }

    cStarRecord* home = (cStarRecord*)((Obj_s00c3_49e0*)SP_StarManager_s00c3_49e0())->m_ba6d80((u32)this->mUFOKey);
    if (home == 0) {
        if (prop != 0)
            RELEASE_s00c3_49e0(prop);
        return 0;
    }

    Vec3* hc = ((Obj_s00c3_49e0*)home)->m_5c65e0();
    float hx = hc->x, hy = hc->y, hz = hc->z;
    FUN_00c34060(this->mStarsBegin, this->mStarsEnd, hx, hy, hz);

    i32 n = (i32)(this->mStarsEnd - this->mStarsBegin);
    i32 sel = 0;
    ((RefVector*)&this->mNextStar)->Resize(n, &sel);

    for (i32 i = 0; i < n; ++i) {
        cStarRecord* si = this->mStarsBegin[i];
        if (si == home)
            continue;

        Vec3* a = ((Obj_s00c3_49e0*)si)->m_5c65e0();
        float dx = a->x - hx, dy = a->y - hy, dz = a->z - hz;
        float bestDist = sqrtf(dx * dx + dy * dy + dz * dz);
        i32 bestIdx = 0;

        for (i32 j = 1; j < i; ++j) {
            Vec3* b = ((Obj_s00c3_49e0*)this->mStarsBegin[j])->m_5c65e0();
            float ex = b->x - hx, ey = b->y - hy, ez = b->z - hz;
            float dist = sqrtf(ex * ex + ey * ey + ez * ez);
            float ux = dx - ex, uy = dy - ey, uz = dz - ez;
            float ulen = sqrtf(ux * ux + uy * uy + uz * uz);
            if (ulen > 0.0f && dist < bestDist && dist > 0.0f) {
                float dot = (dx * ex + dy * ey + dz * ez) / (bestDist * dist);
                if (dot >= cosThreshold * scaleLimit) {
                    bestDist = dist;
                    bestIdx = j;
                    dx = ex; dy = ey; dz = ez;
                }
            }
        }

        cStarRecord** slot = &this->mNextStar[i];
        cStarRecord* chosen = this->mStarsBegin[bestIdx];
        cStarRecord* old = *slot;
        if (chosen != old) {
            if (chosen)
                ADDREF_s00c3_49e0(chosen);
            *slot = chosen;
            if (old)
                RELEASE_s00c3_49e0(old);
        }
    }

    this->mFlags &= ~0x10u;
    if (prop != 0)
        RELEASE_s00c3_49e0(prop);
    return 1;
}

// @ 0x00c34e70
void cEmpire_s00c3_49e0::FUN_00c34e70(Obj_s00c3_49e0* p)
{
    if (p == 0)
        return;
    if (this->mEmpireID == (u32)SP_PlayerEmpireID())
        ((Obj_s00c3_49e0*)DAT_016dda8c)->m_1022150(p);
    this->AddStar((void*)(u32)((Obj_s00c3_49e0*)p)->m_b8de30());
    if (this->FUN_00c31bf0((u32)SP_PlayerEmpireID()) != 0) {
        MsgObj_s00c3_49e0* msg = SP_MessageServer_s00c3_49e0();
        msg->slot18(0x43f2585, 0, 0, 0);
    }
}

// @ 0x00c34ee0
int cEmpire_s00c3_49e0::RemoveStar(cStarRecord* star, char flag)
{
    i32 count = (i32)(this->mStarsEnd - this->mStarsBegin);
    i32 index = 0;
    char changed = 0;

    if (count <= 0)
        return 0;
    cStarRecord** p = this->mStarsBegin;
    for (;;) {
        if (*p == star)
            break;
        ++index;
        ++p;
        if (index >= count)
            return 0;
    }

    if (flag != 0) {
        FUN_00c8c2a0(star);
    } else if (this->mEmpireID == (u32)SP_PlayerEmpireID()) {
        void* v = ((Obj_s00c3_49e0*)star)->m_bba790();
        void** begin = *(void***)v;
        void** end = *(void***)((char*)v + 4);
        for (void** it = begin; it != end; ++it) {
            void* colony = *it;
            if (((Obj_s00c3_49e0*)colony)->m_b8dab0() == 5)
                ((Obj_s00c3_49e0*)DAT_016dda8c)->m_1021ab0(colony);
        }
    }

    // erase at <index>: move the tail element over it, then release the vacated slot.
    if (index != count - 1) {
        cStarRecord** b = this->mStarsBegin;
        cStarRecord* cur = b[index];
        cStarRecord* tail = b[count - 1];
        if (tail != cur) {
            if (tail)
                ADDREF_s00c3_49e0(tail);
            b[index] = tail;
            if (cur)
                RELEASE_s00c3_49e0(cur);
        }
    }
    this->mStarsEnd -= 1;
    {
        cStarRecord* stale = *this->mStarsEnd;
        if (stale)
            RELEASE_s00c3_49e0(stale);
    }

    {
        MsgObj_s00c3_49e0* msg = SP_MessageServer_s00c3_49e0();
        msg->slot14(0x55bd8f7, 0, 0);
    }
    this->mFlags |= 0x10;

    if (*(i32*)((char*)star + 0x70) == this->mUFOKey || this->mUFOKey == -1)
        changed = 1;

    if (((Obj_s00c3_49e0*)SP_StarManager_s00c3_49e0())->m_885c90() == (i32)this->mEmpireID)
        ((Obj_s00c3_49e0*)star)->m_bb9c10(0);

    if (changed) {
        i32 n = (i32)(this->mStarsEnd - this->mStarsBegin);
        float bestDist = DAT_0146b68c;
        cStarRecord* bestStar = 0;
        Vec3* sc = ((Obj_s00c3_49e0*)star)->m_5c65e0();
        for (i32 i = 0; i < n; ++i) {
            cStarRecord* s = this->mStarsBegin[i];
            Vec3* c = ((Obj_s00c3_49e0*)s)->m_5c65e0();
            float dx = c->x - sc->x;
            float dy = c->y - sc->y;
            float dz = c->z - sc->z;
            float d = dx * dx + dy * dy + dz * dz;
            if (bestDist > d) {
                bestDist = d;
                bestStar = s;
            }
        }
        if (bestStar != 0) {
            ((Obj_s00c3_49e0*)SP_StarManager_s00c3_49e0())->m_bb4af0(bestStar, 0);
            void* v = ((Obj_s00c3_49e0*)bestStar)->m_bba790();
            void** begin = *(void***)v;
            void** end = *(void***)((char*)v + 4);
            for (void** it = begin; it != end; ++it) {
                void* city = *it;
                if (city != 0 && FUN_00c70150(city, this, 0)) {
                    this->SetHomePlanet((Obj_s00c3_49e0*)city);
                    return 1;
                }
            }
        }
    }

    {
        i32 planet = ((Obj_s00c3_49e0*)SP_StarManager_s00c3_49e0())->m_ba6d80((u32)this->mUFOKey);
        if (this->mEmpireMoney == -1 && planet != 0) {
            ((Obj_s00c3_49e0*)SP_StarManager_s00c3_49e0())->m_bb4af0((void*)planet, 0);
            void* v = ((Obj_s00c3_49e0*)planet)->m_bba790();
            void* home = *(void**)*(void**)v;
            this->SetHomePlanet((Obj_s00c3_49e0*)home);
        }
    }
    if (this->mEmpireMoney != -1) {
        if (((Obj_s00c3_49e0*)SP_StarManager_s00c3_49e0())->m_ba6dc0((u32)this->mEmpireMoney) != 0)
            FUN_00ba5bc0(this, 6);
    }

    {
        i32 id = (i32)this->mEmpireID;
        this->mEmpireMoney = -1;
        this->mUFOKey = -1;
        ((Obj_s00c3_49e0*)SP_StarManager_s00c3_49e0())->m_baf630(id, 0);
        MsgObj_s00c3_49e0* msg = SP_MessageServer_s00c3_49e0();
        msg->slot18(0x43f2586, 0, 0, 0);
    }

    if (this->mStarsBegin == this->mStarsEnd)
        this->Destroy();
    return 1;
}

// @ 0x00c35240
void __cdecl ChangeStarEmpireOwnership(cEmpire_s00c3_49e0* self, void* newOwnerAvatar)
{
    void* av = ((Obj_s00c3_49e0*)self)->m_b1fdb0();
    cEmpire_s00c3_49e0* oldEmpire = (cEmpire_s00c3_49e0*)((Obj_s00c3_49e0*)SP_StarManager_s00c3_49e0())->m_ba9370(av);
    cEmpire_s00c3_49e0* newEmpire = (cEmpire_s00c3_49e0*)((Obj_s00c3_49e0*)SP_StarManager_s00c3_49e0())->m_ba9370(newOwnerAvatar);

    oldEmpire->RemoveStar((cStarRecord*)self, 0);
    newEmpire->AddStar(self);
    UpdatePosseMembers(self);

    void* v = ((Obj_s00c3_49e0*)self)->m_bba790();
    void** begin = *(void***)v;
    void** end = *(void***)((char*)v + 4);
    for (void** it = begin; it != end; ++it) {
        void* ctx = ((Obj_s00c3_49e0*)*it)->m_ce6950();
        ((Obj_s00c3_49e0*)SP_CommManager_s00c3_49e0())->m_aeab40(ctx);
        ((Obj_s00c3_49e0*)SP_CommManager_s00c3_49e0())->m_aea720((int)oldEmpire->mEmpireID, ctx, 0);
    }
}

// @ 0x00c352f0
void* cEmpire_s00c3_49e0::FUN_00c352f0(void* p)
{
    ((Obj_s00c3_49e0*)p)->m_af0d40((char*)this + 0x108);
    return p;
}

// @ 0x00c35320
void cEmpire_s00c3_49e0::PickRandomPersonality()
{
    if (((Obj_s00c3_49e0*)SP_StarManager_s00c3_49e0())->m_885c90() == (i32)this->mEmpireID) {
        this->mArchetype = 8;
        this->mTrait = 0;
        this->mFlags &= ~4u;
        return;
    }

    Obj_s00c3_49e0* prop = 0;
    Obj_s00c3_49e0* pm = SP_PropertyManager();
    if (prop != 0) {
        RELEASE_s00c3_49e0(prop);
        prop = 0;
    }
    ((Fn_v_piii)VTSLOT(pm, 0x2c))(pm, 0x40020b6f, 0x2ae0c7e, (void**)&prop);
    if (prop == 0)
        return;

    {
        HashMap map;
        u32 arche[9];
        static const int kArch[8] = {
            0x55500bf, 0x55500cd, 0x55500d5, 0x55500dc,
            0x55500e2, 0x55500e9, 0x55500ee, 0x55500f6
        };
        map.Build(arche, 9, &prop);
        for (int k = 0; k < 8; ++k) {
            Obj_s00c3_49e0* out = 0;
            if (prop != 0
                && ((Fn_b_pi)VTSLOT(prop, 0x24))(prop, kArch[k], (void**)&out)
                && *(u16*)((char*)out + 0x12) == 9) {
                arche[k] = (u32)((Obj_s00c3_49e0*)out)->m_41e990()[0];
            }
        }
        this->mArchetype = FUN_00ba7320(arche);
    }

    {
        HashMap map;
        u32 trait[4];
        static const int kTrait[4] = { 0x2f98dae, 0x2f98db1, 0x2f98db3, 0x2f98db5 };
        map.Build(trait, 4, &prop);
        for (int k = 0; k < 4; ++k) {
            Obj_s00c3_49e0* out = 0;
            if (prop != 0
                && ((Fn_b_pi)VTSLOT(prop, 0x24))(prop, kTrait[k], (void**)&out)
                && *(u16*)((char*)out + 0x12) == 9) {
                trait[k] = (u32)((Obj_s00c3_49e0*)out)->m_41e990()[0];
            }
        }
        this->mTrait = FUN_00ba7320(trait);
    }

    {
        float v = 0.0f;
        Obj_s00c3_49e0* p2 = (Obj_s00c3_49e0*)((Obj_s00c3_49e0*)SP_StarManager_s00c3_49e0())->m_baf700(this);
        Obj_s00c3_49e0* out = 0;
        if (p2 != 0
            && ((Fn_b_pi)VTSLOT(p2, 0x24))(p2, 0x576373a, (void**)&out)
            && *(u16*)((char*)out + 0x12) == 0xd)
            v = ((Obj_s00c3_49e0*)out)->m_41ea70()[0];

        float r = ((RandomLCG*)0x1601760)->RandomDoubleUniform();
        if (v > r || DAT_015b7436 != 0)
            this->mFlags |= 4;
        else
            this->mFlags &= ~4u;
    }

    if (prop != 0)
        RELEASE_s00c3_49e0(prop);
}

// @ 0x00c35740
void cEmpire_s00c3_49e0::SetUFOKey(int* key)
{
    if (this->mUFOKey3[0] == key[0]
        && this->mUFOKey3[1] == key[1]
        && this->mUFOKey3[2] == key[2])
        return;
    this->mUFOKey3[0] = key[0];
    this->mUFOKey3[1] = key[1];
    this->mUFOKey3[2] = key[2];

    {
        Obj_s00c3_49e0* db = SP_ObjectTemplateDB();
        ((Fn_v_ppi)VTSLOT(db, 0x58))(db, key, 1);
    }

    {
        void** vec = ((Obj_s00c3_49e0*)SP_NounManager_s00c3_49e0())->m_b21340(0xcd7d10, 0xd3d420, 0xad48b0,
                                                        0xb1e500, 0x18ebadc);
        void** begin = (void**)((void**)vec)[1];
        void** end = (void**)((void**)vec)[2];
        for (void** p = begin; p != end; ++p) {
            void* item = *p;
            if (((Fn_i_p)VTSLOT(item, 0x4c))(item) == (int)this->mEmpireID)
                ((Obj_s00c3_49e0*)item)->m_c37180(key, 1);
        }
    }
}

// @ 0x01064fd0
void cEmpire_s0106_4990::Init_01064fd0()
{
    if (mpSelected == 0)
        return;

    bool differ = (*(int*)((char*)mpSelected + 0x17c) != 0x56624a99);

    void* w1 = mpLayout->FindWindowByID(0x6032b88, 1);
    ((Tc2ii)VTS(w1, 0x7c))(w1, 1, (int)mpLayout);

    void* w2 = mpLayout->FindWindowByID(0x6032bd8, 1);
    ((Tc2ii)VTS(w2, 0x7c))(w2, 1, differ ? 0 : 1);

    if (!differ)
        return;

    FUN_00b3d3d0();
    mpFeedList->FUN_00662920(0);
    (void)0;

    if (!m48.FUN_00e0a780(0x16e2224, 0))
        return;

    PopulateLeft_01064b60();
}

// @ 0x01065360
bool cEmpireC::Ret_01065360(int id, void* ev)
{
    if (id == (int)0xb3d53f95)
    {
        int v = *(int*)((char*)mpSelected + 0x17c);
        void* sim = FUN_00b3d3f0();
        ((E30Obj*)((SimSlot*)sim)->mpE30)->Method_e30a60(v);

        void* nw = *(void**)((char*)ev + 0x10);
        void* old = mpSelected;
        if (nw != old)
        {
            if (nw != 0)
                ((RefObj*)nw)->AddRef();
            mpSelected = (CFeedItem*)nw;
            if (old != 0)
                ((RefObj*)old)->Release();
        }
        m44 = 0;
        empireFromC(this)->Init_01064fd0();
        return true;
    }
    return BaseHandler_00e18600(id, ev);
}

// @ 0x01065900
void cEmpire_s0106_4990::Show_01065900(int arg)
{
    if (mb40 != 0)
        return;

    Show_00e18860(arg);

    cString12 s;
    s.Init_6b5770(0xf5e156f8, 0x6038566, 0);
    SetText_00e18890((void*)s.GetText_6b55c0());

    mb40 = 1;
    PopulateFeed_010655a0();
    Init_01064fd0();
    mpFeedList->FUN_00662920(1);

    void* srv = MessageServer_67dcc0();
    mpMsgServer = srv;
    mpIdentity = (void*)((char*)this + 0x0c);
    mMsgId = 0x1400244;
    mC8 = 1;
    mCC = 0;
    if (srv != 0 && mpIdentity != 0)
        ((Tc2pi)VTS(srv, 0x24))(srv, mpIdentity, 0xb3d53f95);
}

// @ 0x01336df0
namespace Simulator {
void InitEmpireAttributes()
{
    {
        Attribute a("mEmpireName", 0x03477139, 0x3c,
                  Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10,
                  Validate_00b1fbf0, ToXml_00acbbc0);
        *(Attribute*)&cEmpire_sAttributes[0] = a;
    }
    {
        Attribute a("mEmpireMoney", 0x021e6db7, 0xd0,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cEmpire_sAttributes[1] = a;
    }
    {
        Attribute a("mTravelDistance", 0x051e6db7, 0xd4,
                  Read_00bb9cd0, Write_00bb9d00, ReadText_00693070, WriteText_00694f80,
                  Validate_00b1fbf0, ToXml_00595a50);
        *(Attribute*)&cEmpire_sAttributes[2] = a;
    }
    {
        Attribute a("mTrait", 0x03477338, 0x54,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cEmpire_sAttributes[3] = a;
    }
    {
        Attribute a("mArchetype", 0x0554279e, 0x58,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cEmpire_sAttributes[4] = a;
    }
    {
        Attribute a("mCurrentGameMode", 0x0362ab2e, 0x4c,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cEmpire_sAttributes[5] = a;
    }
    {
        Attribute a("mUFOKey", 0x03ab8a62, 0xb8,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cEmpire_sAttributes[6] = a;
    }
    {
        Attribute a("mCaptainKey", 0x07f55dbf, 0xc4,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cEmpire_sAttributes[7] = a;
    }
    {
        Attribute a("mHomePlanet", 0x021e6dbb, 0xb4,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cEmpire_sAttributes[8] = a;
    }
    {
        Attribute a("mHomeStar", 0x021e6dba, 0xb0,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cEmpire_sAttributes[9] = a;
    }
    {
        Attribute a("mPoliticalID", 0x021e6dbc, 0x84,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cEmpire_sAttributes[10] = a;
    }
    {
        Attribute a("mCityMusic", 0x042a0f35, 0x104,
                  Read_00bf26b0, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f550, ToXml_00ac8050);
        *(Attribute*)&cEmpire_sAttributes[11] = a;
    }
    {
        Attribute a("mFlags", 0x035d5a51, 0x50,
                  Read_00c31c80, Write_00c32a40, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00ac8050);
        *(Attribute*)&cEmpire_sAttributes[12] = a;
    }
    {
        Attribute a("mCultureSet", 0x05624e2e, 0x108,
                  Read_00bf1c70, Write_00bf1cb0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00befb00, ToXml_00ac8050);
        *(Attribute*)&cEmpire_sAttributes[13] = a;
    }
    {
        Attribute a("mEnemies", 0x03477390, 0x5c,
                  Read_00c34750, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f860, ToXml_00c6c390);
        *(Attribute*)&cEmpire_sAttributes[14] = a;
    }
    {
        Attribute a("mAllies", 0x03868491, 0x70,
                  Read_00c34750, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f860, ToXml_00c6c390);
        *(Attribute*)&cEmpire_sAttributes[15] = a;
    }
    {
        Attribute a("mStars", 0x03868492, 0x88,
                  Read_00badf20, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f860, ToXml_00c6c390);
        *(Attribute*)&cEmpire_sAttributes[16] = a;
    }
    {
        Attribute a("mNextStarTowardsHome", 0x03868493, 0x9c,
                  Read_00badf20, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f860, ToXml_00c6c390);
        *(Attribute*)&cEmpire_sAttributes[17] = a;
    }
    {
        Attribute a("mAdventureList", 0x07995682, 0x148,
                  Read_00c33820, Write_00c332a0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00c31ca0, ToXml_00eafcf0);
        *(Attribute*)&cEmpire_sAttributes[18] = a;
    }
}
}  // namespace Simulator
