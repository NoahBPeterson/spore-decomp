// src/game/SPGonzago/SPBuildings.cpp -- migrated from slice(s) s00bd5ea0, s00bd2840, s00bd1820, s00bcf6f0, s00bcd2a0, s0132abc0, s00bce1e0, s00bcc010 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPBuildings.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCity.h"
#include "SP/cCombatant.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cSPTimer.h"
#include "SP/cSpatialObject.h"
#include "SP/cTribeTool.h"
#include "SP/cVarListSerializer.h"
#include "SP/cVehicle.h"
#include "SP/cBuilding.h"
#include "SP/cCommunity.h"
#include <math.h>
#include "SP/cBuildingCityHall.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cSPCreatureCitizen.h"
#include "cSPMatrix3.h"
#include "cSPVector3.h"
#include "SP/cPlanetModel.h"
#include "cSPTransform.h"
#include "SP/FunctionalMatch/Constraint.h"
#include "SP/cCelestialBody.h"
#include "SP/cEllipticalOrbit.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cInteractionTarget.h"
#include "EA/Random/RandomLinearCongruential.h"

// ---- items of slice s00bcc010 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VF(obj, slot) (*(void**)((char*)*(void**)(obj) + (slot) * 4))
void  __cdecl FUN_0093aa70(void* w, void* p, int n, int b);    // 0x0093aa70 EA::IO::WriteUint32
void  __cdecl FUN_0093a780(void* r, void* p, int n, int b);    // 0x0093a780 EA::IO::ReadInt32
void  __cdecl FUN_00be2440(void* a, int b, int c);             // 0x00be2440
void* __cdecl FUN_00b3d240();                                  // 0x00b3d240
void* __cdecl FUN_00b5b800();                                  // 0x00b5b800 SP::GetCurrentGameMode
void* __cdecl FUN_00cf74c0();                                  // 0x00cf74c0 SP::cCivModeStrategy::Get
struct CCivStrat { void __thiscall M7480(); };                 // 0x00cf7480 thiscall
void* __cdecl FUN_00b3d300();                                 // 0x00b3d300 SP_NounManager
struct cVarListSerializer {
    uint32_t mData[0xa14 / 4];
    void __thiscall Construct(void* obj, int idA, int idB);    // 0x00692f90 ret 0xc
    char __thiscall Serialize(void* s);                        // 0x00692900 ret 4
    char __thiscall Deserialize(void* s);                      // 0x00693e10 ret 4
    int  __thiscall GetFields(void* s);                        // 0x00695960 ret 4
};
class cGameData {
 public:
    void __thiscall Write(void* s);                            // 0x00b18590 ret 4
    void __thiscall Read(void* s);                             // 0x00b18600 ret 4
    void __thiscall WriteAsText(void* s);                      // 0x00b18420 ret 4
    void __thiscall IsDestroyed(int a);                        // 0x00bfd0d0 ret 4
    void* __thiscall GetProperty(int iid);                     // 0x00b18460 ret 4
};
class cSpatialObject {
 public:
    char __thiscall Write(void* s);                            // 0x00c88a90 ret 4
    char __thiscall Read(void* s);                             // 0x00c88b00 ret 4
    void __thiscall SetLocalExtents(int a, float f);           // 0x00c89160 ret 8
    char __thiscall bcc570();                                  // 0x00bcc570
    void __thiscall bcc5e0(int a, float f);                    // 0x00bcc5e0
    char __thiscall bccdc0();                                  // 0x00bccdc0
    void __thiscall bcc6e0(char v);                            // 0x00bcc6e0
    float __thiscall bcc640();                                 // 0x00bcc640
};
class cLocomotiveObject {
 public:
    char __thiscall Write(void* s);                            // 0x00c448a0 ret 4
};
class cCombatant {
 public:
    char __thiscall Write(void* s);                            // 0x00bfc4a0 ret 4
    char __thiscall Read(void* s);                             // 0x00bfc540 ret 4
    char __thiscall IsSomething();                             // 0x00bfc600 ret
    void __thiscall Do(void* p);                               // 0x00bd7f20 ret 4
};
class cCity_s00bc_c010 {
 public:
    void* __thiscall GetCivilization();                        // 0x00bd9bf0 ret
};
class cSPTimer {
 public:
    char __thiscall IsRunning();                               // 0x00feba90 ret
    int  __thiscall GetElapsedTime();                          // 0x00bc3190 ret
};
class cGameNounManager_s00bc_c010 {
 public:
    int*  __thiscall GetGameDataVector(void* a, void* b, void* c, void* d, int e); // 0x00b21340 ret 0x14
    void  __thiscall RemoveNoun(void* noun);                   // 0x00b225d0 ret 4
    void* __thiscall GetPlayerCivilization();                  // 0x00b25fb0 ret
    void* __thiscall Unk25f40(void* p);                        // 0x00b25f40 ret 4
};
class PropHost {
 public:
    void* __thiscall Get108(int iid);                          // 0x00ac0320 ret 4
    void* __thiscall Get51C(int iid);                          // 0x00abf740 ret 4
    void* __thiscall GetBase(int iid);                         // 0x00b18460 ret 4
    void* __thiscall Get120(int iid);                          // 0x00bfc380 ret 4
    void* __thiscall Get34a(int iid);                          // 0x00c884f0 ret 4
    void* __thiscall Get1E8(int iid);                          // 0x00c751c0 ret 4
    void* __thiscall Get34b(int iid);                          // 0x00c41d00 ret 4
};
class cSerializableNoun {
 public:
    char __thiscall WriteBase(void* s);                        // 0x00bcc350
    char __thiscall ReadBase(void* s);                         // 0x00bcc400
};
class cTribeTool : public cSerializableNoun {
 public:
    void __thiscall bcc010();
    void __thiscall bcc230(int elapsed);
    void __thiscall bcc760(int v);
    void __thiscall bcc7e0(int delta);
    int  __thiscall bcc800();
    int  __thiscall bcc820();
    void __thiscall bcc860(int unused);
    void* __thiscall bcc500(int iid);
    void __thiscall ResetTool();                               // 0x00bcbc80 ret
};
class cVehicle : public cSerializableNoun {
 public:
    void __thiscall Write1(void* s);                           // 0x00bcc8b0
    void __thiscall Read1(void* s);                            // 0x00bcc920
    void __thiscall Write2(void* s);                           // 0x00bcc9f0
    void __thiscall Read2(void* s);                            // 0x00bcca60
    void __thiscall Write3(void* s);                           // 0x00bccb30
    void __thiscall Read3(void* s);                            // 0x00bccba0
    bool __thiscall Write4(void* s);                           // 0x00bccc70
    bool __thiscall Read4(void* s);                            // 0x00bccd10
    void* __thiscall GetProp(int iid);                         // 0x00bcce20
    void __thiscall bccf20();
    bool __thiscall Write5(void* s);                           // 0x00bccf80
    void __thiscall WriteAsText(void* s);                      // 0x00bcd030
    void __thiscall bcd130(int delta);                         // 0x00bcd130
    int  __thiscall bcd250();
};
class cToolExtra {
 public:
    void __thiscall bcc650(int param);
};
// ---- items of slice s00bcc010 end

// ---- items of slice s00bce1e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_f169c1b0;   // 0x0169c1b0
extern float g_f169c1b4;   // 0x0169c1b4
extern float g_f15d9c6c;   // 0x015d9c6c
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int   u32;
#define VS(o, off)   (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)  ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1) \
    ((R (__thiscall*)(void*, T1))VS(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VS(o, off))((void*)(o), (a1), (a2))
#define VC3(R, o, off, T1, a1, T2, a2, T3, a3) \
    ((R (__thiscall*)(void*, T1, T2, T3))VS(o, off))((void*)(o), (a1), (a2), (a3))
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
};
struct Vec3u   { u32 x, y, z; };
struct cGameNounManager {
    void* mVtbl;                  // +0
    void RemoveNoun(void* noun);  // 0x00b225d0
    void* CreateNoun(u32 id);     // 0x00b20c60
};
cGameNounManager* SP_NounManager();                          // 0x00b3d300
void* PropertyManager();                                    // 0x0067de30
bool  GetPropertyAsVector3(void* list, u32 id, void* out);  // 0x006a1110
struct Sub34 {                       // +0x34
    void* mVtbl;                     // +0x00
    u8    d[0x64];
    void FUN_00c8b2e0();             // 0x00c8b2e0
    bool Read(void* stream);         // 0x00c88b00
    bool ReadBig(void* stream);      // 0x00c43c10
    void FUN_00c43f90(void);         // 0x00c43f90  (Shutdown)
    void FUN_00c421b0(void* p);      // 0x00c421b0
};
struct SubC4  { u8 d[0x3c]; };                              // +0xc4
struct Sub108 { u8 d[0x18]; void FUN_00ac0450(); };         // +0x108
struct Sub120 {                                             // +0x120
    u8 d[0xcc];
    void FUN_00bfc720();                                     // 0x00bfc720
    void FUN_00bfc470(u8 b);                                 // 0x00bfc470
};
struct Sub504 { u8 d[0x18]; void FUN_00ac0450(); };         // +0x504
struct Sub51C { u8 d[0x6c]; void FUN_00abf710(); };         // +0x51c
struct Sub588 {                                             // +0x588
    u8   d[0xf8];
    bool FUN_00bfc540(void* stream);                         // 0x00bfc540
    void FUN_00bfc720();                                     // 0x00bfc720
};
struct cToolData {
    bool FUN_0104bd50();         // 0x0104bd50
    void UseToolStop();          // 0x0104fa90
};
cToolData* __stdcall FUN_00b3d390(cToolData* p);   // 0x00b3d390
void FUN_00bcd480(void* p, float a, float b); // 0x00bcd480
struct cCity;
struct Sub508 {
    void* mVtbl;          // +0x000
    u8    d[0x614];       // +0x004 .. +0x618
    int   FUN_00vt10();   // vtable slot 0x10
};
struct RType660 {
    void*  mVtbl;         // +0x000
    u8     m04[0x504];    // +0x004 .. +0x508
    Sub508 m508;          // +0x508 .. +0xb20
    u32    mB20;          // +0xb20
};
struct cVt8Obj {
    void*    mVtbl;       // +0
    Vector3* FUN_00vt2c();    // vtable slot 0x2c
};
struct cCiv {
    void* mVtbl;
    void FUN_00bf02b0();      // 0x00bf02b0
};
struct cCity {
    void* mVtbl;
    cCiv* GetCivilization(int uVar5, Vector3 v);   // 0x00bd9bf0
    void  FUN_00c00b00(int a, int b);              // 0x00c00b00
};
struct cBuilding {
    u8             m00[0x2c];
    void*          mpRef2c;      // +0x2c
    u8             m30[0x04];
    Sub34          m34;          // +0x34 .. +0x9c
    u8             m9c[0x28];    // +0x9c .. +0xc4
    SubC4          mC4;          // +0xc4 .. +0x100
    cCity*         mp100;        // +0x100  (cCity)
    u8             m104[0x04];
    Sub108         m108;         // +0x108 .. +0x120
    Sub120         m120;         // +0x120 .. +0x1ec
    void*          mp1ec;        // +0x1ec  (space inventory)
    void*          mp1f0;        // +0x1f0  (owner city)
    u8             m1f4[0x30];   // +0x1f4 .. +0x224
    u32            m224;         // +0x224
    u8             m228[0xe4];   // +0x228 .. +0x30c
    u8             m30c;         // +0x30c
    u8             m30d[0x1f7];  // +0x30d .. +0x504
    Sub504         m504;         // +0x504 .. +0x51c
    Sub51C         m51C;         // +0x51c .. +0x588
    Sub588         m588;         // +0x588 .. +0x680
    void*          mp680;        // +0x680
    u8             m684[0x04];
    void*          mp688;        // +0x688
    void*          mp68c;        // +0x68c
    cToolData*     mp690;        // +0x690
    cToolData*     mp694;        // +0x694
    cToolData*     mp698;        // +0x698
    cToolData*     mp69c;        // +0x69c
    void*          mp6a0;        // +0x6a0
    void*          mp6a4;        // +0x6a4

    float GetCost();                       // 0x00bce9a0
    int   FUN_00bce5d0();                  // 0x00bce5d0
    void  FUN_00bce970();                  // 0x00bce970
    void  FUN_00bce9b0();                  // 0x00bce9b0
    void  SetOwnerCity1(void* param_2);    // 0x00bce8e0
    void  FUN_00bcea10(u32 param_2);       // 0x00bcea10
    void  FUN_00bce660(void* param_2);     // 0x00bce660
    void  FUN_00bce1e0();                  // 0x00bce1e0
    void  SetGameDataOwner2(void* p);      // 0x00b18550
    void  FUN_00bcd4e0(u32 param_2);       // 0x00bcd4e0
};
struct cSpatialObject_s00bc_e1e0 {
    void* mVtbl;        // +0x00
    u8    m04[0x98];    // +0x04 .. +0x9c
    void* mp9c;         // +0x9c
    u8    mA0[0x580];   // +0xa0 .. +0x620
    Vec3u m620;         // +0x620
    bool LoadModel(u32 id);        // 0x00c8a550
    bool FUN_00bce5f0(u32 param_2);  // 0x00bce5f0 (cSpatialObject::FUN_00bce5f0)
};
struct RType { u8 m00; u8 m01; };
struct F3F950Target {
    RType* FUN_00f3f950(void* arg);   // 0x00f3f950
};
struct GlobalsTable {
    u8              m00[0x74];
    F3F950Target*   mp74;             // +0x74
};
extern GlobalsTable* g_globals16c7aa4;   // 0x016c7aa4
struct cCommunity {
    u8    m00[0x66c];
    void* mp66c;                     // +0x66c
    void  func54h(void* param_2);    // 0x00c88670
    void  FUN_00bce8b0(u32 param_2);
};
struct cVariant {
    void* mPtr;         // +0x000
    u8    m04[0x0c];    // +0x004 .. +0x010
    u8    mFlags;       // +0x010
    u8    m11;          // +0x011
    u16   mType;        // +0x012
};
extern Vector3 g_v756d754;   // 0x0156d754
extern Vector3 g_v756d760;   // 0x0156d760
// ---- items of slice s00bce1e0 end

// ---- items of slice s0132abc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0132_abc0; 
}
typedef eastl::string8_s0132_abc0 string8_s0132_abc0;
typedef bool (*ReadFunction_t)(void*, void*);
typedef bool (*WriteFunction_t)(void*, void*);
typedef void (*ReadTextFunction_t)(const string8_s0132_abc0&, void*);
typedef void (*WriteTextFunction_t)(char*, void*);
typedef bool (*ValidateFunction_t)();
typedef bool (*ToXmlFunction_t)(void*, const char*, int);
typedef void* (*OffsetFunction_t)(void*);
typedef void (*SetDefaultFunction_t)(void*);
void* DefaultOffset(void* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
struct Attribute
{
    // Offset is written last, after every callback slot -- matches the binary.
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
    /* 0Ch */ int field_0C;   // not initialized by the constructor
    /* 10h */ int field_10;   // not initialized by the constructor
    /* 14h */ int field_14;   // not initialized by the constructor
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
template<typename T> bool Valid();                                    // 0x00b1fbf0
template<typename T> bool Read4(void*, void*);                        // 0x00572810
template<typename T> bool Write4(void*, void*);                       // 0x00572840
template<typename T> void ReadTextT(const string8_s0132_abc0&, void*);           // 0x00692ff0
template<typename T> void WriteTextT(char*, void*);                   // 0x00694ee0
template<typename T> bool ToXmlT(void*, const char*, int);            // 0x0057cde0
bool Valid_00b1fbf0();                                                // 0x00b1fbf0
bool ToXml_0057cde0(void*, const char*, int);                         // 0x0057cde0
struct TBld0{}; struct TBld1{}; struct TBld2{}; struct TBld3{}; struct TBld4{}; struct TBld5{};
struct TBld6{}; struct TBld7{}; struct TBld8{}; struct TBld9{}; struct TBld10{}; struct TBld11{}; struct TBld12{};
void ReadText_00c2e4e0(const string8_s0132_abc0&, void*);                        // 0x00c2e4e0
void WriteText_00692fb0(char*, void*);                                // 0x00692fb0
bool ToXml_00ac8050(void*, const char*, int);                         // 0x00ac8050
struct AttrSlot { uint32_t d[15]; };
#define ADD_ATTR(TABLE, IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&TABLE[IDX] = a; }
extern AttrSlot sBuildingsAttributes[13];
struct TW0{}; struct TW1{}; struct TW2{}; struct TW3{}; struct TW4{};
struct TW5{}; struct TW6{}; struct TW7{}; struct TW8{}; struct TW9{};
extern AttrSlot sBuildingWeaponsAttributes[10];
// ---- items of slice s0132abc0 end

// ---- items of slice s00bcd2a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*  PTR_s_field_name_0156deb4;   // 0x156deb4  serializer field-name row
extern void*  DAT_01570858;                // 0x1570858  set-class payload
extern void*  DAT_01601760;                // 0x1601760  cRandomGlobal
extern void*  DAT_01654c05;                // 0x1654c05  SPACE game-mode tag
extern float  DAT_0168b66c, DAT_0168b670, DAT_0168b674;  // default offset triplet
extern float  DAT_0169c0fc, DAT_0169c100;  // wrapper constants (a)
extern float  DAT_0169c07c, DAT_0169c080;  // wrapper constants (b)
extern float  DAT_0169c0a8, DAT_0169c0ac;  // wrapper constants (c)
extern float  DAT_0156def0;                // model direction scale
extern void*  PTR_FUN_01466c14;
extern void*  vtbl_Simulator_cTurret;      // 0x1466e90
extern void*  PTR_FUN_01466e7c;            // 0x1466e7c
extern void*  PTR_FUN_01466d80;            // 0x1466d80
extern void*  PTR_FUN_01466d74;            // 0x1466d74
extern void*  PTR_FUN_01466d58;            // 0x1466d58
extern void*  PTR_FUN_01466cf0;            // 0x1466cf0
extern void*  PTR_FUN_01466c88;            // 0x1466c88
extern void*  PTR_FUN_01466c60;            // 0x1466c60
struct Vec3 { float x, y, z, w; };
struct Vec3f { float x, y, z; };                 // 12-byte position/offset vector
struct WaterBody {                               // 0x14-stride element of the water-body list
    u32   mField_00;
    u32   mField_04;
    u32   mField_08;
    float mRadius_0c;
    u32   mField_10;
};
static void* vc(void* obj, int off) { return ((void**)*(void**)obj)[off / 4]; }
void*  __cdecl FUN_0093aa70(void* a, void* b, void* c, void* d); // 0x93aa70 EA::IO::WriteUint32
void*  __cdecl FUN_0093a780(void* a, void* b, void* c, void* d); // 0x93a780 EA::IO::ReadInt32
void*  __cdecl FUN_00692f90(void* a, void* b, void* c, void* d); // 0x692f90 cVarListSerializer ctor
void*  __cdecl FUN_00692900(void* a, void* b);                   // 0x692900 cVarListSerializer::Serialize
void*  __cdecl FUN_00693e10(void* a, void* b);                   // 0x693e10 cVarListSerializer::Read
void*  __cdecl FUN_00bcc350(void* a);                            // 0xbcc350 ISimulatorSerializable Write helper
void*  __cdecl FUN_00bcc400(void* a);                            // 0xbcc400 ISimulatorSerializable Read helper
struct cCommunityBase { void func5Ch(float v); };
void*  __cdecl FUN_00695b40(void* a, void* b, void* c);          // 0x695b40 set-class helper
void*  __cdecl FUN_01021090();                                   // 0x1021090 GetPlayerEmpireID
void*  __cdecl FUN_01021260();                                   // 0x1021260 cSPLivingUniverse::GetActivePlanet
void*  __cdecl FUN_01021370();                                   // 0x1021370 cSPLivingUniverse::GetPlayerHomePlanet
void*  __cdecl FUN_0102f810();                                   // 0x102f810 economy tuning singleton
void*  __cdecl FUN_0102fb70(void* a);                            // 0x102fb70 GetHomeWorldBuildingMultiplier
void*  __cdecl FUN_00c88810(void* a, void* b);                   // 0xc88810 Simulator::cSpatialObject::SetModelKey
void*  __cdecl FUN_00bd9e50(void* a);                            // 0xbd9e50 model-key refresh
void*  __cdecl FUN_00b18550(void* a, void* b);                   // 0xb18550 SP::cGameData::SetGameDataOwner2
void*  __cdecl FUN_00bfc720(void* a);                            // 0xbfc720
void*  __cdecl FUN_00ac0450(void* a);                            // 0xac0450
void*  __cdecl FUN_00c8b2e0(void* a);                            // 0xc8b2e0 Simulator::cSpatialObject
void*  __cdecl FUN_00bd9bf0(void* a);                            // 0xbd9bf0 SP::cCity::GetCivilization
void*  __cdecl FUN_00b25f40(void* a, void* b);                   // 0xb25f40 cGameNounManager lookup
double __cdecl FUN_0059da80(float a);                            // 0x59da80 RandomRange
void*  __cdecl FUN_00a68fb0(void* a, u32 b);                     // 0xa68fb0 RandomUint32Uniform
void*  __cdecl FUN_00b3d480(float a, float b, float c, float d, float e, float f); // 0xb3d480
void*  __cdecl FUN_00d5cfd0(void* a, void* b, void* c, void* d, void* e, void* f); // 0xd5cfd0
void*  __cdecl FUN_00b3d350(void* a);                            // 0xb3d350 SP::PlanetModel
char   __fastcall FUN_00b8bb70(void* self, int, void* planet, float dist, void* out); // 0xb8bb70 cPlanetModel::FindClosestWater
void*  __fastcall FUN_0108db30(void* self, int);                 // 0x108db30 water-body list
float  __fastcall FUN_00b81470(void* self, int, void* planet, void* point); // 0xb81470 cPlanetModel::DistanceBetweenPoints
void*  __cdecl FUN_00c00b00(void* a, void* b, void* c);          // 0xc00b00
void*  __cdecl FUN_00bf02b0(void* a, void* b);                   // 0xbf02b0 city_flags_update
void*  __cdecl FUN_00c6f660(void* a);                            // 0xc6f660
void*  __cdecl FUN_00b3d310(void* a, void* b, void* c);          // 0xb3d310
void*  __cdecl FUN_00b452f0(void* a, void* b, void* c);          // 0xb452f0
void*  __cdecl FUN_00b4c600(void* a, void* b, void* c);          // 0xb4c600
void*  __cdecl FUN_00b225d0(void* a, void* b);                   // 0xb225d0 cGameNounManager::RemoveNoun
void*  __cdecl FUN_00b18660(void* a);                            // 0xb18660 SP::cGameData::cGameData
void*  __cdecl FUN_00b184c0(void* a);                            // 0xb184c0 SP::cGameData::~cGameData
void*  __cdecl FUN_00c43860(void* a);                            // 0xc43860
void*  __cdecl FUN_00c432e0(void* a);                            // 0xc432e0
void*  __cdecl FUN_00ac03d0(void* a);                            // 0xac03d0 SP::cInteractionTarget ctor
void*  __cdecl FUN_00ac0520(void* a);                            // 0xac0520 SP::cInteractionTarget dtor
void*  __cdecl FUN_00abfe50(void* a);                            // 0xabfe50
void*  __cdecl FUN_00abfec0(void* a);                            // 0xabfec0
void*  __cdecl FUN_00bfd4e0(void* a);                            // 0xbfd4e0 SP::cCombatant::cCombatant
void*  __cdecl FUN_00bfcd00(void* a);                            // 0xbfcd00 SP::cCombatant::~cCombatant
void*  __cdecl FUN_00b63890(void* a);                            // 0xb63890 SP::cGonzagoTimer ctor
void*  __cdecl FUN_00b638b0(void* a);                            // 0xb638b0 SP::cGonzagoTimer dtor
struct VarListSerializer { u8 mData_000[0xa14]; };
struct cGameData_s00bc_d2a0 {
    u8   pad_000[0x34];
    u8   pad_034[0xd4];        // 0x34..0x108  embedded cSpatialObject
    void* mpVftbl_108;         // 0x108
    u8   pad_10c[0x14];        // 0x10c..0x120
    void* mpField_120;         // 0x120
    u8   pad_124[0xc8];        // 0x124..0x1ec
    void* mpField_1ec;         // 0x1ec  sub-container
    void* mpOwner_1f0;         // 0x1f0  owned object (city)
    u8   pad_1f4[0x8];         // 0x1f4..0x1fc
    u8   mbField_1fc;          // 0x1fc

    bool Write(void* pArchive);            // 0x00bcd2a0
    bool Read(void* pArchive);             // 0x00bcd340
};
struct cCommunityT {
    u8    pad_000[0x64];
    float mField_64;           // 0x64  compared against the incoming float
    u8    pad_068[0x2a4];      // 0x68..0x30c
    u8    mbField_30c;         // 0x30c  set to 1 after func5Ch

    void SetFloat(float v);    // 0x00bcd3f0
};
struct cOwnerT {
    u8    pad_000[0x34];       // 0x00..0x34 cGameData
    u8    pad_034[0xd4];       // 0x34..0x108
    void* mpVftbl_108;         // 0x108
    u8    pad_10c[0x14];       // 0x10c..0x120
    void* mpField_120;         // 0x120
    u8    pad_124[0xc8];       // 0x124..0x1ec
    void* mpField_1ec;         // 0x1ec
    void* mpOwner_1f0;         // 0x1f0  owned object (city)
    u8    pad_1f4[0x8];        // 0x1f4..0x1fc
    u8    mbField_1fc;         // 0x1fc
    u8    pad_1fd[0x27];       // 0x1fd..0x224
    u8    mModelKey_224[0xc];  // 0x224..0x230 model key (12 bytes)
    u8    mbFlag_230;          // 0x230

    void  SetOwnerCity2(void* pCity);    // 0x00bcd5b0
    void  RemoveOwner();                 // 0x00bcd5f0
    void  RemoveOwnerFull();             // 0x00bcddc0
    void  SetFlag(char on);              // 0x00bcd550
    void  SetModelKey2(void* pKey);      // 0x00bcd4e0
    void* GetOwnerCivilization();        // 0x00bcd630
    void  UpdateCityFlags(void* pObj);   // 0x00bcd890
    bool  func7Ch(void* pPlanet);                                // 0x00bcda00
    void  RefreshModelKeys();            // 0x00bcda90
    void  GetNextWanderNode(char mode, int count); // 0x00bcd690
};
struct cTurret {
    u8 mBase_000[0x7a0];
    cTurret();                 // 0x00bcded0
    ~cTurret();                // 0x00bce0a0
};
// ---- items of slice s00bcd2a0 end

// ---- items of slice s00bcf6f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
typedef unsigned long long uint64;
struct Vector3_s00bc_f6f0 { float x, y, z; };
struct Matrix3 { float m[9]; };
struct BBox { Vector3_s00bc_f6f0 lo, hi; };
struct XformMsg {                        // 0x38 bytes; ctor 0x00434040
    uint16_t flags;                      // |4 position, |2 matrix
    int16_t count;
    Vector3_s00bc_f6f0 pos;
    float scale;
    Matrix3 rot;
    XformMsg();
    void SetPos(const Vector3_s00bc_f6f0& v) { pos = v; flags |= 4; ++count; }
    void SetRot(const Matrix3& m) { rot = m; flags |= 2; ++count; }
    void SetScale(float s)        { scale = s; ++count; }
};
struct IEffect {                         // EA::Swarm::cIVisualEffect (slots used here)
    virtual void v00();
    virtual void Release();              // 0x04
    virtual void Start(int flag);        // 0x08
    virtual void Stop(int flag);         // 0x0c
    virtual bool IsPlaying();            // 0x10
    virtual void v14();
    virtual void SetTransform(XformMsg* xf);   // 0x18
};
struct EffectRef {                       // EA::AutoRefCount<cIVisualEffect>
    IEffect* p;
    IEffect** AsPPTypeParam();           // 0x00a16f40
    ~EffectRef() { if (p) p->Release(); }
};
struct EffectsMgr {
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
    virtual bool CreateEffect(uint id, int unused, IEffect** out);   // 0x2c
};
EffectsMgr* __cdecl EffectsManager();                                // 0x0067ddd0
struct Timer {                           // SP::cSPTimer
    char d[0x20];
    void Restart();                      // 0x00bc3130
    bool IsRunning();                    // 0x00feba90
    uint64 GetElapsedTime();             // 0x00bc3190
};
struct Civ { char pad[0x4b8]; int mCounter; };
struct City {
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
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
    virtual unsigned GetPoliticalID();   // 0x4c
    char pad[0x230 - 4];
    Timer mTimer230;                     // +0x230
    char pad2[0x748 - 0x250];
    float mField748;
    int   mField74c;
    Civ* GetCivilization();              // 0x00bd9bf0
    void F00bd8300(int amount);          // 0x00bd8300 (ret 4)
    void F00bdbf10();   // 0x00bdbf10
    bool F00bd9d20();   // 0x00bd9d20
    int  F00bd81f0();   // 0x00bd81f0
    int  F00bd9bb0();   // 0x00bd9bb0
    void F00c00b00(int a, int b);        // 0x00c00b00 (ret 8)
    void F00be2bb0(float damage, int empire);   // 0x00be2bb0 (ret 8)
};
struct Planet { int F00c70e00(); };   // 0x00c70e00
struct PlanetRec;
struct ShipInfo { char pad[0x714]; int mKind; };
struct Combatant {
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
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
    virtual void* Cast(uint typeId);     // 0x5c
};
struct Inventory { char pad[0x508]; };
struct UFOSim {
    Inventory* GetPlayerInventory();     // 0x00a1ad60
    void F00ffd830(City* city);          // 0x00ffd830 (ret 4)
};
struct Tuning {
    float F0102a4f0();   // 0x0102a4f0
    float F0102a540();   // 0x0102a540
    float GetCityCaptureFactor();        // 0x01029be0
};
struct RelMgr { float RecordFoughtEnemyEvent(uint pid, uint att, uint ev, float w); };   // 0x00d06270, ret 0x10
struct NounMgr { int F00b1f9d0(); };                                                      // 0x00b1f9d0 player empire or -1
namespace SP {
unsigned __cdecl GetCurrentGameMode();                         // 0x00b5b800
}
namespace SP {
int __cdecl GetPlayerEmpireID();                               // 0x01021090 (cSPLivingUniverse)
}
namespace SP {
Planet* __cdecl GetActivePlanet();                             // 0x01021260
}
namespace SP {
PlanetRec* __cdecl GetActivePlanetRecord();                    // 0x010212a0
}
namespace SP {
Tuning* __cdecl GetSpaceCombatTuning();                        // 0x01029940
}
namespace SP {
UFOSim* __cdecl GetUFOSimulator();                             // 0x00ffbe50
}
namespace SP {
RelMgr* __cdecl RelationshipManager();                         // 0x00b3d2c0
}
namespace SP {
NounMgr* __cdecl NounManager();                                // 0x00b3d300
}
namespace SP {
Vector3_s00bc_f6f0 __cdecl normalized_safe(const Vector3_s00bc_f6f0& v);             // 0x00449c20
}
namespace SP {
const Matrix3* __cdecl Matrix3FromFacingAndUp(Matrix3* out, const Vector3_s00bc_f6f0* facing, const Vector3_s00bc_f6f0* up);   // 0x0069b440
}
ShipInfo* __cdecl F00ae3370(Combatant* c);                     // 0x00ae3370
bool __cdecl F01029a10(int empire, PlanetRec* rec);            // 0x01029a10
struct Flag44 { char pad[0x44]; bool mFlag; };
Flag44* __cdecl F01021230();                                   // 0x01021230
void __cdecl F00be9b20(PlanetRec* rec, City* city, int a, uint ownerID, float damage, int attacker, bool b);   // 0x00be9b20
struct Building {
    void F00bcd690(int a, int type);   // 0x00bcd690 (ret 8)
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
    virtual bool IsDestroyed();                 // 0x2c
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual unsigned GetPoliticalID();            // 0x4c
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual City* GetOwnerCity();                  // 0x84
};
struct Spatial {
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
    virtual const Vector3_s00bc_f6f0& GetPosition();         // 0x2c
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual bool IsOnView();                       // 0x48
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual Vector3_s00bc_f6f0 GetDirection();               // 0x5c
    virtual void s60();
    virtual void s64();
    virtual const BBox& GetLocalExtents();        // 0x68
};
struct BldCombatant {
    // BldCombatant is a Combatant subobject (vptr at +0); only the offsets the function needs are modelled.
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
    virtual void TakeDamage(float damage, uint attackerID, int damageType, const Vector3_s00bc_f6f0& pos, Combatant* src);   // 0x18
    char pad[0x238 - 0x20];
    Timer mAttackTimer;                  // +0x238
    void TakeDamageBase(float damage, uint attackerID, int damageType, const Vector3_s00bc_f6f0& pos, Combatant* src);   // 0x00bcece0 (ret 0x14)
    void SpawnTurretHitEffect();
};
// ---- items of slice s00bcf6f0 end

// ---- items of slice s00bd1820 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gExtentMin;           // 0x01437c88
extern float gExtentMax;           // 0x013eeda0
extern float gPropDefault;         // 0x013ec5b4
extern wchar_t gEmptyString16[];   // 0x01667bac (static empty eastl wide string)
extern const wchar_t gBuildingName[]; // 0x01467a64 L"UNINITIALIZED BUILDING NAME"
extern char cBuilding_vtable0[];                 // 0x014670b8
extern char cBuilding_vtable1[];                 // 0x014670a4
extern char cBuilding_vtable2[];                 // 0x01466fe0
extern char cBuilding_vtable3[];                 // 0x01466fc0
extern char cBuilding_vtable4[];                 // 0x01466f58
extern char cBuilding_vtable5[];                 // 0x01466f30
extern char cPlaceableStructure_baseVtable[];    // 0x01466c14 (interim vptr)
extern char cBuildingScenario_vtable0[];         // 0x01467c30
extern char cBuildingScenario_vtable1[];         // 0x01467c1c
extern char cBuildingScenario_vtable2[];         // 0x01467b58
extern char cBuildingScenario_vtable3[];         // 0x01467b38
extern char cBuildingScenario_vtable4[];         // 0x01467ad0
extern char cBuildingScenario_vtable5[];         // 0x01467aac
extern "C" void __fastcall ctor_cGameData(void* p);          // 0x00b18660
extern "C" void __fastcall ctor_cSpatialObject(void* p);     // 0x00c89630
extern "C" void __fastcall ctor_cInteractionTarget(void* p); // 0x00ac03d0
extern "C" void __fastcall ctor_cCombatant(void* p);         // 0x00bfd4e0
extern "C" void __fastcall ctor_cGonzagoTimer(void* p);      // 0x00b63890
extern "C" void __fastcall dtor_cBuilding(void* p);          // 0x00bd0dd0
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct AABB { float minx, miny, minz, maxx, maxy, maxz; };
void  DestroyRange(void* pFirst, void* pLast);               // 0x00bd17e0
void  FreeObj(void* p);                                      // 0x00f47380 operator delete
float GetPropertyFloat(u32 id, int a, void* b, float fDef);  // 0x00bcea30
void  Fn_00bcebc0(void);                                     // 0x00bcebc0
struct cGonzagoTimer {
    u32 mData[8];
};
struct cWString {
    wchar_t* mpBegin;    // +0x00
    wchar_t* mpEnd;      // +0x04
    wchar_t* mpCapacity; // +0x08
    void*    mpPool;     // +0x0c
    cWString& assign(const wchar_t* pFirst, const wchar_t* pLast);  // 0x00423650
};
struct cSPMatrix3_s00bd_1820 {
    float m[9];
    void Assign(const float* pSrc);     // 0x0041cb40
};
struct cCoordArray {
    u32  mInline[6];     // +0x00 .. +0x17
    u32* mpCurrent;      // +0x18
    u32* mpUnused1c;     // +0x1c
    u32* mpCapacity;     // +0x20
    u32* mpUnused24;     // +0x24
    u32* mpUnused28;     // +0x28
    void Init(u32 nCapacity);   // 0x004ab350
    void Grow(u32* pValue);     // 0x00502dd0
};
struct cCoordVec {
    u32* mpBegin;        // +0x00
    u32* mpEnd;          // +0x04
    u32* mpCap;          // +0x08
    void DestroyRange(u32* pFirst, u32* pLast);   // 0x00bd17e0 (thiscall)
};
struct cSpatialObjectABI {
    void* mpVtbl;                                             // +0x00
    void SetLocalExtents(const AABB& bounds, float fScale);   // 0x00c89160
};
struct cInteractionABI { void* mpVtbl; };
struct cCombatABI      { void* mpVtbl; };
struct cPlaceABI       { void* mpVtbl; };
struct cBuilding_s00bd_1820 {
    void* mpVtbl0;           // +0x000  cBuilding vtable
    void* mpVtbl1;           // +0x004  cBuilding vtable (DefaultRefCounted half)
    char  mData08[0x34 - 0x08];      // +0x008 .. +0x033 (cGameData tail)
    union { void* mpVtblSpatial; cSpatialObjectABI mSpatial; };  // +0x034
    char  mData38[0x88 - 0x38];      // +0x038 .. +0x087
    u32   mField88;          // +0x088
    char  mData8c[0xa4 - 0x8c];      // +0x08c .. +0x0a3
    u8    mbFlagA4;          // +0x0a4
    u8    mbFlagA5;          // +0x0a5
    char  mDataA6[0xda - 0xa6];      // +0x0a6 .. +0x0d9
    u8    mbFlagDa;          // +0x0da
    char  mDataDb[0x108 - 0xdb];     // +0x0db .. +0x107
    union { void* mpVtblInteraction; cInteractionABI mInteraction; };  // +0x108
    char  mData10c[0x120 - 0x10c];   // +0x10c .. +0x11f
    union { void* mpVtblCombatant; cCombatABI mCombatant; };       // +0x120
    char  mData124[0x14c - 0x124];   // +0x124 .. +0x14b
    float mField14c;         // +0x14c
    char  mData150[0x158 - 0x150];   // +0x150 .. +0x157
    float mField158;         // +0x158
    char  mData15c[0x1e8 - 0x15c];   // +0x15c .. +0x1e7
    union { void* mpVtblPlaceable; cPlaceABI mPlace; };             // +0x1e8
    u32   mF1ec;             // +0x1ec
    u32   mF1f0;             // +0x1f0
    u8    mF1f4;             // +0x1f4
    char  mF1f5[3];          // +0x1f5 .. +0x1f7
    cCoordArray mCoords;     // +0x1f8
    u32   mF224;             // +0x224
    u32   mF228;             // +0x228
    u32   mF22c;             // +0x22c
    u8    mF230;             // +0x230
    char  mF231[0x238 - 0x231];      // +0x231 .. +0x237
    cGonzagoTimer mTimer1;   // +0x238
    cGonzagoTimer mTimer2;   // +0x258
    cWString mName;          // +0x278
    u8    mF288;             // +0x288
    u8    mF289;             // +0x289
    char  mF28a[2];          // +0x28a .. +0x28b
    u32   mF28c;             // +0x28c
    u32   mF290;             // +0x290
    u32   mF294;             // +0x294
    u32   mF298;             // +0x298
    u32   mF29c;             // +0x29c
    u32   mF2a0;             // +0x2a0
    u32   mF2a4;             // +0x2a4
    u32   mF2a8;             // +0x2a8
    char  mF2ac[8];          // +0x2ac .. +0x2b3 (untouched subobject)
    u32   mF2b4;             // +0x2b4
    u32   mF2b8;             // +0x2b8
    u32   mF2bc;             // +0x2bc
    char  mF2c0[8];          // +0x2c0 .. +0x2c7 (untouched subobject)
    u32   mF2c8;             // +0x2c8
    u32   mF2cc;             // +0x2cc
    u32   mF2d0;             // +0x2d0
    char  mF2d4[8];          // +0x2d4 .. +0x2db (untouched subobject)
    u32   mF2dc;             // +0x2dc
    u32   mF2e0;             // +0x2e0
    u32   mF2e4;             // +0x2e4
    char  mF2e8[8];          // +0x2e8 .. +0x2ef (untouched subobject)
    u8    mF2f0;             // +0x2f0
    char  mF2f1[3];          // +0x2f1 .. +0x2f3
    u32   mF2f4;             // +0x2f4
    u32   mF2f8;             // +0x2f8
    u32   mF2fc;             // +0x2fc
    char  mF300[8];          // +0x300 .. +0x307 (untouched subobject)
    u32   mF308;             // +0x308
    u32   mF30c;             // +0x30c
    u32   mF310;             // +0x310
    char  mF314[0x320 - 0x314];      // +0x314 .. +0x31f
    cGonzagoTimer mTimer3;   // +0x320
    u8    mF340;             // +0x340 (CityHall: mbMoneyAddedThisTick)
    u8    mF341;             // +0x341 (CityHall: field_341)
    char  mF342[2];          // +0x342 .. +0x343
    cCoordVec mTailVec;      // +0x344 (Scenario coord vector / CityHall hit-sphere ptr)
    char  mF350[0x358 - 0x350];      // +0x350 .. +0x357
    cGonzagoTimer mTimerHit; // +0x358 (CityHall)
    char  mF378[0x388 - 0x378];      // +0x378 .. +0x387
    u16   mF388;             // +0x388 (Scenario: mnFlags)
    u16   mF38a;             // +0x38a (Scenario: mnTransformCount)
    float mF38c;             // +0x38c (Scenario: mOffset.x)
    float mF390;             // +0x390 (Scenario: mOffset.y)
    float mF394;             // +0x394 (Scenario: mOffset.z)
    float mF398;             // +0x398 (Scenario: mfScale)
    cSPMatrix3_s00bd_1820 mMatrix;      // +0x39c (Scenario: mRotation)

    cBuilding_s00bd_1820();                        // 0x00bd1820
    void PushCoord(u32 value);          // 0x00bd1ab0
};
// ---- items of slice s00bd1820 end

// ---- items of slice s00bd2840 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_f1486110;  // 0x01486110  5.0f
extern const float g_f13ec4b8;  // 0x013ec4b8  +1e-08f
extern const wchar_t kWUint32[];    // 0x01401158  L"uint32_t"
extern "C" float __fastcall SampleChildField260(void* child);       // 0x00bebe40
extern "C" void* __fastcall CommunityKey(void* self);              // 0x00c9fee0
extern "C" void* __cdecl FUN_00cd7d10();                           // 0x00cd7d10
extern "C" void* __cdecl FUN_00d3d420();                           // 0x00d3d420
extern "C" void* __cdecl FUN_00ae72d0();                           // 0x00ae72d0
extern "C" void* __cdecl FUN_00b1e500();                           // 0x00b1e500
extern "C" void* __cdecl EA_ConvertToString16(void* out, const char* src, int len);  // 0x0093c5a0
extern "C" void  __fastcall WStringRangeInitialize(void* self, void* a, void* b);    // 0x00579a90
extern "C" void  __fastcall WStringConstruct(void* self, const void* src);           // 0x0056e2d0
extern "C" void* __cdecl operator_delete(void* p);                                   // 0x00f47380
extern "C" char  __fastcall TypedValueToStringShort(void* self, int a, int b, const wchar_t* t);  // 0x00675990
struct Vector3_s00bd_2840 { float x, y, z; };                       // plain copies go through integer registers
struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(const Quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
};
struct cSPTransform_s00bd_2840 {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3_s00bd_2840 mOffset;
    float mScale;
    Matrix3 mRotation;

    cSPTransform_s00bd_2840() : mFlags(0), mModificationCount(0) {}
    cSPTransform_s00bd_2840& operator=(const cSPTransform_s00bd_2840& o);      // 0x00537dc0
    void Accumulate(const cSPTransform_s00bd_2840* other);          // 0x0040ccb0
    void SetOffset(const Vector3_s00bd_2840& v) { mOffset = v; mFlags |= 4; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
    void SetRotation(const Matrix3& r) { mRotation = r; mFlags |= 2; mModificationCount++; }
};
namespace SP {
 Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quaternion& q);   // 0x0059c190 (cdecl)
}
template <class T> struct SpVector {                     // eastl::vector with sp_vector_allocator (0x14 bytes)
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void resize(int n);
};
template <> void SpVector<Vector3_s00bd_2840>::resize(int n);       // 0x00473810
template <> void SpVector<cSPTransform_s00bd_2840>::resize(int n);  // 0x0041e3b0
class cLocomotiveObject_s00bd_2840 {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
    /* 2ch */ virtual const Vector3_s00bd_2840& GetPosition();
    /* 30h */ virtual const Quaternion& GetOrientation();
    /* 34h */ virtual float GetScale();
};
struct cPlanetModel_s00bd_2840 {
    Vector3_s00bd_2840* DirectionToSurfacePosition(Vector3_s00bd_2840* out, Vector3_s00bd_2840* dir);   // 0x00b815a0
};
namespace SP {
 cPlanetModel_s00bd_2840* __cdecl PlanetModel();   // 0x00b3d350
}
struct cHelperObject { void Update(); };                               // 0x00be0020 (thiscall)
class cPlacedModelBase {
public:
virtual void b00();
virtual void b04();
virtual void b08();
virtual void b0c();
virtual void b10();
virtual void b14();
virtual void b18();
virtual void b1c();
virtual void b20();
virtual void b24();
virtual void b28();
virtual void b2c();
    virtual void* GetWorld();                       // +0x30
virtual void b34();
virtual void b38();
virtual void b3c();
virtual void b40();
virtual void b44();
virtual void b48();
virtual void b4c();
virtual void b50();
virtual void b54();
virtual void b58();
virtual void b5c();
virtual void b60();
virtual void b64();
virtual void b68();
virtual void b6c();
virtual void b70();
virtual void b74();
virtual void b78();
virtual void b7c();
virtual void b80();
    virtual void* Slot84();                         // +0x84
};
class cPlacedModel : public cPlacedModelBase {
public:
    char _pad00[0x30];
    cLocomotiveObject_s00bd_2840 mLocomotive;           // +0x34
    char _pad38[0x1f0 - 0x38];
    cHelperObject* mpHelper;                 // +0x1f0
    char _pad1f4[0x2a0 - 0x1f4];
    SpVector<Vector3_s00bd_2840> mLocalPoints;          // +0x2a0
    SpVector<Vector3_s00bd_2840> mLocalNormals;         // +0x2b4
    SpVector<Vector3_s00bd_2840> mWorldPoints;          // +0x2c8
    SpVector<Vector3_s00bd_2840> mWorldNormals;         // +0x2dc
    uint8_t mWorldDirty;                     // +0x2f0
    char _pad2f1[3];
    SpVector<cSPTransform_s00bd_2840> mLocalTransforms; // +0x2f4
    SpVector<cSPTransform_s00bd_2840> mWorldTransforms; // +0x308

    void UpdateWorldGeometry();
};
static __forceinline Vector3_s00bd_2840 Rotate(const Quaternion& q, const Vector3_s00bd_2840& v)
{
    float yy = q.y * q.y;
    float xy = q.y * q.x;
    float zz = q.z * q.z;
    float zx = q.z * q.x;
    float zy = q.z * q.y;
    float zw = q.z * q.w;
    float xx = q.x * q.x;
    float wx = q.w * q.x;
    float wy = q.w * q.y;
    Vector3_s00bd_2840 r;
    r.x = ((xy - zw) * v.y + (wy + zx) * v.z) * 2.0f + (1.0f - (zz + yy) * 2.0f) * v.x;
    r.y = ((zw + xy) * v.x + (zy - wx) * v.z) * 2.0f + (1.0f - (zz + xx) * 2.0f) * v.y;
    r.z = ((zx - wy) * v.x + (wx + zy) * v.y) * 2.0f + (1.0f - (yy + xx) * 2.0f) * v.z;
    return r;
}
struct Vec20B {
    uint8_t mData[0x20];
    Vec20B& operator=(const Vec20B& o);           // 0x00473500
};
struct Record {                                   // 0x0c64 bytes
    cSPTransform_s00bd_2840 mTransform;                      // +0x00
    float        mField38;                        // +0x38
    float        mField3c;                        // +0x3c
    uint32_t     mField40;                        // +0x40
    uint32_t     mField44;                        // +0x44
    uint32_t     mField48;                        // +0x48
    Vec20B       mVec4c;                          // +0x4c
    uint8_t      mRest[0x0c64 - 0x6c];
};
struct cSPTransformOps {
    void* mRaw;
    cSPTransformOps* Assign(const void* src);     // 0x00537dc0
};
class cCommunity_s00bd_2840 {
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
    virtual void* GetWorld();                     // +0x30  (owner world / geometry object)
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
    virtual void* Slot84();                       // +0x84

    Vector3_s00bd_2840    mPosition;                         // +0x04
    Quaternion mOrientation;                      // +0x10
    char       _pad20[0x30c - 0x20];
    uint8_t    mDirty30c;                         // +0x30c
    char       _pad30d[3];
    void*      mpChild310;                        // +0x310
    Vector3_s00bd_2840    mDir314;                           // +0x314
    char       _pad320[4];
    void*      mpField324;                        // +0x324

    void func54h(float* dir);                     // 0x00c88670 (ret 4)
    void func58h(void* arg);                      // 0x00c886d0 (ret 4)

    void    CallFunc58(void* arg);                // 0x00bd3230
    void    CallFunc54(float* dir);               // 0x00bd3500
    uint8_t FindPeerA(cCommunity_s00bd_2840* other);         // 0x00bd3280
    uint8_t FindPeerB(cCommunity_s00bd_2840* other);         // 0x00bd3550
    void    SetDirection(float* dir);             // 0x00bd3380
    void    SetPosition(float* v);                // 0x00bd3640
    void    SetOrientation(float* v);             // 0x00bd36c0

    cPlacedModel* Owner() { return (cPlacedModel*)((char*)this - 0x34); }
};
class cObject {
public:
virtual void o00();
virtual void o04();
virtual void o08();
virtual void o0c();
virtual void o10();
virtual void o14();
virtual void o18();
virtual void o1c();
    virtual void* TypeId();                       // +0x20
virtual void o24();
virtual void o28();
virtual void o2c();
virtual void o30();
virtual void o34();
virtual void o38();
virtual void o3c();
virtual void o40();
virtual void o44();
virtual void o48();
    virtual int  Slot4c();                        // +0x4c
    virtual void o50();
    virtual void* Slot54();                       // +0x54

    void SetOwner(void* owner);                   // 0x00bd7f20 (ret 4): byte [this+0x6c] = 1
};
class cObjectHeader {
public:
virtual void h00();
virtual void h04();
virtual void h08();
virtual void h0c();
virtual void h10();
virtual void h14();
virtual void h18();
virtual void h1c();
virtual void h20();
virtual void h24();
virtual void h28();
virtual void h2c();
virtual void h30();
virtual void h34();
virtual void h38();
virtual void h3c();
virtual void h40();
virtual void h44();
virtual void h48();
virtual void h4c();
    virtual void h50();
    virtual void* Slot54();                       // +0x54
};
namespace SP {
 void* GetCurrentGameMode_s00bd_2840();   // 0x00b5b800
}
class cGameNounManager_s00bd_2840 {
public:
    void* GetGameDataVector(void* f0, void* f1, void* f2, void* f3, void* type);  // 0x00b21340 (ret 0x14)
};
extern "C" void* __cdecl SP_NounManager_s00bd_2840();                         // 0x00b3d300
struct PropBlock {
    int* mpFirst;               // +0x00
    int* mpLast;                // +0x04
    int* mpCur;                 // +0x08
    int* mpNextArray;           // +0x0c
    int* mpIter;                // +0x10
    int* mpChunkBase;           // +0x14
    int* mpEnd;                 // +0x18
};
class PropVisitor {
public:
    virtual void SetName(const wchar_t* name);   // +0x00
    virtual void SetValue(const wchar_t* name);  // +0x04
};
static __forceinline void RefreshTail(cCommunity_s00bd_2840* self)
{
    cPlacedModel* owner = (cPlacedModel*)((char*)self - 0x34);
    owner->UpdateWorldGeometry();
    cObject* obj = (cObject*)owner->GetWorld();
    if (obj != 0 && obj->TypeId() == (void*)0x018c43e8)
        obj->SetOwner(owner);
}
// ---- items of slice s00bd2840 end

// ---- items of slice s00bd5ea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gTemplateSlotTable[];   // 0x0168caf0, stride 0x1c up to 0x0168cb44
extern char gTemplateSlotEnd[];     // 0x0168cb44
#pragma warning(disable: 4100)
typedef void* (__thiscall* Fn_p_v)(void*);
struct IV {  // pure vtable stub (48 slots covers every call site here)
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
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
virtual void v46();
virtual void v47();
};
#define VT(p, off)     (*(void**)((char*)(*(void**)(p)) + (off)))
void* __cdecl SP_ObjectTemplateDB();                         // 0x0067cb40
void* __cdecl SP_NounManager(int id);                        // 0x00b3d300
void* __cdecl SP_ResourceMan_GetManager();                   // 0x0067dcd0
void* __cdecl FUN_00b25f40(void* nounMgr, uint id);          // 0x00b25f40
void  __cdecl FUN_00ba5df0(void* a, void* b);                // 0x00ba5df0
bool  __cdecl FUN_00bf2c80(void* a, void* b);                // 0x00bf2c80
void* __cdecl FUN_00bf9700(void* a, void* b);                // 0x00bf9700
void  __cdecl FUN_00bf4a60(void* a, void* b, void* c);       // 0x00bf4a60
void* __cdecl FUN_00bf9770(void* a, void* b);                // 0x00bf9770
void  __cdecl FUN_00bf4b10(void* a, void* b, void* c);       // 0x00bf4b10
struct IRef {
  virtual int AddRef();
  virtual int Release();
};
struct GameDataVec { void* mpBegin; void* mpEnd; void* mpCapacity; };
struct cGameNounManager_s00bd_5ea0 {
  void RemoveNoun(void* noun);                               // 0x00b225d0
  void RemoveNounsOfType(int type);                          // 0x00b22650
  GameDataVec* GetGameDataVector(void* f1, void* f2, void* f3, void* f4, uint tag);  // 0x00b21340
};
cGameNounManager_s00bd_5ea0* __cdecl NounManager_s00bd_5ea0();                     // 0x00b3d300
namespace SP {
namespace FunctionalMatch {
 struct Constraint_s00bd_5ea0; 
}
}
struct ConstraintVector {
  SP::FunctionalMatch::Constraint_s00bd_5ea0* mpBegin;   // +0x00
  SP::FunctionalMatch::Constraint_s00bd_5ea0* mpEnd;     // +0x04
  SP::FunctionalMatch::Constraint_s00bd_5ea0* mpCapacity;// +0x08
  uint mAllocator;                            // +0x0c
  ConstraintVector() : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(0) {}
  void push_back(const SP::FunctionalMatch::Constraint_s00bd_5ea0& v);   // 0x004e18e0
};
namespace SP {
class cGameData_s00bd_5ea0 : public IRef {
 public:
  char  pad04[8];
  void* mpNext;                  // +0x0c
  void* mpPrev;                  // +0x10
  bool  mIsDestroyed;            // +0x14
  char  pad15[3];
  uint  mID;                     // +0x18
  uint  mDefinitionID;           // +0x1c
  bool  mb20;                    // +0x20
  bool  mb21;                    // +0x21
  char  pad22[2];
  uint  m24;                     // +0x24
  void* mView;                   // +0x28
  IRef* mpGameDataOwner;         // +0x2c
  uint  mPoliticalID;            // +0x30

  cGameData_s00bd_5ea0();                                            // 0x00b18660
  int GetFieldValues(void* vec);                         // 0x00b18420
  uint GetPoliticalID() const;                            // 0x00804830
  uint GetNounID() const;                                 // vtable slot 0x20
  uint GetNounKey() const;                                // vtable slot 0x4c
  void WriteData(void* s) const;                          // 0x00b18590
  void ReadData(void* s);                                 // 0x00b18600
  void WriteTagged(void* s);                              // 0x00bd6230
  void DtorBody();                                        // 0x00b184c0
  void* AsInterfaceQuery(uint id);                        // 0x00b18460
};
}
namespace SP {
namespace FunctionalMatch {
struct Constraint_s00bd_5ea0 {   // 0x24 bytes
  Constraint_s00bd_5ea0(uint property, uint op, uint value);   // 0x00558960
  uint mData[4];
  uint mSub[4];
  uint mFlags;
};
}
}
namespace SP {
class cSpatialObject_s00bd_5ea0 {
 public:
  virtual ~cSpatialObject_s00bd_5ea0();
  bool WriteSpatial(void* s) const;                 // 0x00c88a90
  bool ReadSpatial(void* s);                        // 0x00c88b00
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();

  cSpatialObject_s00bd_5ea0();                                 // 0x00c89630
  void DtorBody();                                  // 0x00c8a420
  void* AsInterfaceQuery(uint id);                  // 0x00c884f0
  char pad80[0x6c];
  bool mbSpatialFlag;                               // +0x70 (retail)
  char pad71[0x63];                                 // -> retail size 0xd4
};
}
namespace SP {
class cInteractionTarget_s00bd_5ea0 {
 public:
  virtual ~cInteractionTarget_s00bd_5ea0();
  virtual void* AsInterface(uint id);
  virtual void RemoveInteraction(void* i);
  virtual void AddInteraction(void* i);
  virtual void Shutdown();
  virtual int Release();
  cInteractionTarget_s00bd_5ea0();                             // 0x00ac03d0
  void DtorBody();                                  // 0x00ac0520
  void* QueryInterfaceHere(uint id);                // 0x00ac0320
  char pad04[0x14];                                 // -> retail size 0x18
};
}
namespace SP {
class cCheatObject : public cGameData_s00bd_5ea0, public cSpatialObject_s00bd_5ea0, public cInteractionTarget_s00bd_5ea0 {
 public:
  cCheatObject();                                   // 0x00bd6a80
  ~cCheatObject();                                  // 0x00bd6c10
  void BindCheatHandlers();                         // 0x00bd6c60
  void DtorBases();                                 // 0x00bd6750
  void* QueryInterface(uint id);                    // 0x00bd6770
  void WriteBody(void* s) const;                    // 0x00bd67c0
  void ReadBody(void* s);                           // 0x00bd6810
  int GetFieldValuesAll(void* vec);                 // 0x00bd6b10
  IRef* mpDataObject;                               // +0x120
  bool  mFlag124;                                   // +0x124
  char  pad125[3];
};
}
using SP::cGameData_s00bd_5ea0;
using SP::cCheatObject;
using SP::FunctionalMatch::Constraint_s00bd_5ea0;
void FUN_00bd40a0(void* p);   // 0x00bd40a0
// ---- items of slice s00bd5ea0 end

// @ 0x00bcc350
char __thiscall cSerializableNoun::WriteBase(void* s)
{
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    int   ver = 0xe9cb8ba;
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    FUN_0093aa70(w, &ver, 1, 0);
    ((cGameData*)this)->Write(s);
    bool ok = ((cSpatialObject*)((char*)this + 0x34))->Write(s) != 0 &&
              ((cCombatant*)((char*)this + 0x120))->Write(s) != 0;
    cVarListSerializer vl;
    vl.Construct(this, 0x156d770, 0x1a80d26);
    if (ok && vl.Serialize(s) != 0)
        return 1;
    return 0;
}

// @ 0x00bcc400
char __thiscall cSerializableNoun::ReadBase(void* s)
{
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    int   ver;
    FUN_0093a780(w, &ver, 1, 0);
    char* sub = (char*)this + 0x34;
    ((cGameData*)this)->Read(s);
    bool ok = false;
    if (((cSpatialObject*)sub)->Read(s) != 0 &&
        ((cCombatant*)((char*)this + 0x120))->Read(s) != 0)
        ok = true;
    cVarListSerializer vl;
    vl.Construct(this, 0x156d770, 0x1a80d26);
    char res = 0;
    if (ok && vl.Deserialize(s) != 0) {
        res = 1;
        if (*(char*)((char*)this + 0x230) != 0) {
            int vv[3];
            vv[0] = 0xd1bf030c;
            vv[1] = 0;
            vv[2] = 0;
            ((void(__thiscall*)(void*, int*))VF(sub, 0x94 / 4))(sub, vv);
        } else {
            ((void(__thiscall*)(void*, void*))VF(sub, 0x94 / 4))(sub, (char*)this + 0xc4);
        }
    }
    return res;
}

// @ 0x00bcc500
void* __thiscall cTribeTool::bcc500(int iid)
{
    if (iid == 0xe9cb8ba) return this;
    void* r = ((PropHost*)((char*)this + 0x108))->Get108(iid);
    if (r == 0) r = ((PropHost*)this)->GetBase(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x120))->Get120(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x34))->Get34a(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x1e8))->Get1E8(iid);
    return r;
}

// @ 0x00bcc570
char __thiscall cSpatialObject::bcc570()
{
    if (FUN_00b5b800() == (void*)0x1654c10) return 1;
    char* obj = (char*)this - 0x34;
    void* a = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
    if (a != 0) {
        void* b = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
        if (b != 0) {
            if (((int(__thiscall*)(void*))VF(b, 8))(b) == 0x18c43e8)
                if (!((char(__thiscall*)(void*))VF(b, 11))(b))
                    return ((char(__thiscall*)(void*))VF((char*)b + 0x120, 0x16))((char*)b + 0x120);
        }
    }
    return 0;
}

// @ 0x00bcc5e0
void __thiscall cSpatialObject::bcc5e0(int a, float f)
{
    ((cSpatialObject*)this)->SetLocalExtents(a, f);
    char* obj = (char*)this - 0x34;
    void* x = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
    if (x != 0) {
        void* y = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
        if (y != 0 && ((int(__thiscall*)(void*))VF(y, 8))(y) == 0x18c43e8)
            ((cCombatant*)y)->Do(obj);
    }
}

// @ 0x00bcc640
float __thiscall cSpatialObject::bcc640()
{
    float c = ((float(__thiscall*)(void*))VF(this, 0x5c / 4))(this);
    return c * *(float*)0x1485544;
}

// @ 0x00bcc650
void __thiscall cToolExtra::bcc650(int param)
{
    ((cGameData*)this)->IsDestroyed(param);
    char* obj = (char*)this - 0xec;
    ((void(__thiscall*)(void*, void*))VF(obj, 37))(obj, (char*)this + 0x104);
    void* h = FUN_00b3d240();
    uint32_t buf[3];
    ((void(__thiscall*)(void*, int, void*, void*))VF(h, 0x60 / 4))(
        h, 0x3704925,
        ((void*(__thiscall*)(void*))VF(obj, 11))(obj),
        ((void*(__thiscall*)(void*, void*))VF(obj, 23))(obj, buf));
}

// @ 0x00bcc6e0
void __thiscall cSpatialObject::bcc6e0(char v)
{
    if (*(char*)((char*)this + 0x289) == v) return;
    char* o = (char*)this + 0x34;
    *(char*)((char*)this + 0x289) = v;
    void* tgt = ((void*(__thiscall*)(void*))VF(o, 0xb0 / 4))(o);
    if (tgt == 0) return;
    if (*(char*)((char*)this + 0x289) != 0)
        ((void(__thiscall*)(void*, void*))VF(tgt, 0xc4 / 4))(tgt,
            ((void*(__thiscall*)(void*, int, int, int))VF(o, 0xac / 4))(o, 1, 1, 0));
    else
        ((void(__thiscall*)(void*, void*))VF(tgt, 0xc4 / 4))(tgt,
            ((void*(__thiscall*)(void*, int, int, int))VF(o, 0xac / 4))(o, 0, 1, 0));
}

// @ 0x00bcc760
void __thiscall cTribeTool::bcc760(int v)
{
    int old = *(int*)((char*)this + 0x290);
    if (old == v) return;
    bool before = old > 0 || ((cCombatant*)((char*)this + 0x120))->IsSomething() != 0;
    *(int*)((char*)this + 0x290) = v;
    if (before != (v > 0 || ((cCombatant*)((char*)this + 0x120))->IsSomething() != 0))
        FUN_00be2440(((void*(__thiscall*)(void*))VF(this, 0x84 / 4))(this), 0, 0);
}

// @ 0x00bcc7e0
void __thiscall cTribeTool::bcc7e0(int delta)
{
    bcc760(*(int*)((char*)this + 0x290) + delta);
}

// @ 0x00bcc800
int __thiscall cTribeTool::bcc800()
{
    cSPTimer* t = (cSPTimer*)((char*)this + 0x258);
    if (t->IsRunning())
        return t->GetElapsedTime();
    return 0;
}

// @ 0x00bcc820
int __thiscall cTribeTool::bcc820()
{
    return *(char*)((char*)this + 0x48) == 0;
}

// @ 0x00bcc860
void __thiscall cTribeTool::bcc860(int unused)
{
    (void)unused;
    cGameNounManager_s00bc_c010* nm = (cGameNounManager_s00bc_c010*)FUN_00b3d300();
    nm->GetPlayerCivilization();
    char* obj = (char*)this - 0x34;
    void* c = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
    if (c != 0)
        ((void(__thiscall*)(void*))VF(c, 8))(c);
    ((CCivStrat*)FUN_00cf74c0())->M7480();
}

// @ 0x00bcc8b0
void __thiscall cVehicle::Write1(void* s)
{
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    int   ver = 0x1007ae63;
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    FUN_0093aa70(w, &ver, 1, 0);
    ((cSerializableNoun*)this)->WriteBase(s);
    cVarListSerializer vl;
    vl.Construct(this, 0x156dab8, 0x1a80d26);
    vl.Serialize(s);
}

// @ 0x00bcc920
void __thiscall cVehicle::Read1(void* s)
{
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    int   ver;
    FUN_0093a780(w, &ver, 1, 0);
    ((cSerializableNoun*)this)->ReadBase(s);
    cVarListSerializer vl;
    vl.Construct(this, 0x156dab8, 0x1a80d26);
    vl.Deserialize(s);
}

// @ 0x00bcc9f0
void __thiscall cVehicle::Write2(void* s)
{
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    int   ver = 0xecade42;
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    FUN_0093aa70(w, &ver, 1, 0);
    ((cSerializableNoun*)this)->WriteBase(s);
    cVarListSerializer vl;
    vl.Construct(this, 0x156db6c, 0x1a80d26);
    vl.Serialize(s);
}

// @ 0x00bcca60
void __thiscall cVehicle::Read2(void* s)
{
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    int   ver;
    FUN_0093a780(w, &ver, 1, 0);
    ((cSerializableNoun*)this)->ReadBase(s);
    cVarListSerializer vl;
    vl.Construct(this, 0x156db6c, 0x1a80d26);
    vl.Deserialize(s);
}

// @ 0x00bccb30
void __thiscall cVehicle::Write3(void* s)
{
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    int   ver = 0xff10521;
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    FUN_0093aa70(w, &ver, 1, 0);
    ((cSerializableNoun*)this)->WriteBase(s);
    cVarListSerializer vl;
    vl.Construct(this, 0x156dba8, 0x1a80d26);
    vl.Serialize(s);
}

// @ 0x00bccba0
void __thiscall cVehicle::Read3(void* s)
{
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    int   ver;
    FUN_0093a780(w, &ver, 1, 0);
    ((cSerializableNoun*)this)->ReadBase(s);
    cVarListSerializer vl;
    vl.Construct(this, 0x156dba8, 0x1a80d26);
    vl.Deserialize(s);
}

// @ 0x00bccc70
bool __thiscall cVehicle::Write4(void* s)
{
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    int   ver = 0x1a55e4d;
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    FUN_0093aa70(w, &ver, 1, 0);
    bool ok = ((cSerializableNoun*)this)->WriteBase(s) != 0 &&
              ((cSerializableNoun*)this)->WriteBase(s) != 0;
    cVarListSerializer vl;
    vl.Construct(this, 0x156dbe4, 0x1a80d26);
    if (ok && vl.Serialize(s) != 0)
        return true;
    return false;
}

// @ 0x00bccd10
bool __thiscall cVehicle::Read4(void* s)
{
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    int   ver;
    FUN_0093a780(w, &ver, 1, 0);
    bool ok = ((cSerializableNoun*)this)->ReadBase(s) != 0 &&
              ((cSerializableNoun*)this)->ReadBase(s) != 0;
    cVarListSerializer vl;
    vl.Construct(this, 0x156dbe4, 0x1a80d26);
    if (ok && vl.Deserialize(s) != 0)
        return true;
    return false;
}

// @ 0x00bccdc0
char __thiscall cSpatialObject::bccdc0()
{
    char* obj = (char*)this - 0x34;
    void* a = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
    if (a != 0) {
        void* b = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
        if (b != 0) {
            if (((int(__thiscall*)(void*))VF(b, 8))(b) == 0x18c43e8)
                if (!((char(__thiscall*)(void*))VF(b, 11))(b))
                    return ((char(__thiscall*)(void*))VF((char*)b + 0x120, 0x16))((char*)b + 0x120);
        }
    }
    return 0;
}

// @ 0x00bcce20
void* __thiscall cVehicle::GetProp(int iid)
{
    if (iid == 0x436f315) return this;
    void* r = ((PropHost*)((char*)this + 0x504))->Get108(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x51c))->Get51C(iid);
    if (r == 0) r = ((PropHost*)this)->GetBase(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x588))->Get120(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x34))->Get34b(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x650))->Get1E8(iid);
    return r;
}

// @ 0x00bccf20
void __thiscall cVehicle::bccf20()
{
    void* c = ((void*(__thiscall*)(void*))VF(this, 12))(this);
    void* city = c;
    if (c == 0 || ((int(__thiscall*)(void*))VF(c, 8))(c) != 0x18c43e8)
        city = 0;
    if (((int(__thiscall*)(void*))VF(this, 0x4c / 4))(this) == -1)
        ((cCity_s00bc_c010*)city)->GetCivilization();
    else
        ((cGameNounManager_s00bc_c010*)FUN_00b3d300())->Unk25f40(
            (void*)((int(__thiscall*)(void*))VF(this, 0x4c / 4))(this));
}

// @ 0x00bccf80
bool __thiscall cVehicle::Write5(void* s)
{
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    int   ver = 0x436f315;
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    FUN_0093aa70(w, &ver, 1, 0);
    ((cGameData*)this)->Write(s);
    bool ok = ((cLocomotiveObject*)((char*)this + 0x34))->Write(s) != 0 &&
              ((cCombatant*)((char*)this + 0x588))->Write(s) != 0;
    cVarListSerializer vl;
    vl.Construct(this, 0x156dc20, 0x1a80d26);
    if (ok && vl.Serialize(s) != 0)
        return true;
    return false;
}

// @ 0x00bcd030
void __thiscall cVehicle::WriteAsText(void* s)
{
    ((cGameData*)this)->WriteAsText(s);
    cVarListSerializer v1;
    cVarListSerializer v2;
    v1.Construct((char*)this + 0x34, 0x157a1f8, 0x1a80d26);
    v1.GetFields(s);
    v1.Construct((char*)this + 0x120, 0x1570858, 0x1a80d26);
    v1.GetFields(s);
    v2.Construct(this, 0x156d770, 0x1a80d26);
    v2.GetFields(s);
}

// @ 0x00bcd130
void __thiscall cVehicle::bcd130(int delta)
{
    bool before = *(int*)((char*)this + 0x684) > 0 ||
                  ((cCombatant*)((char*)this + 0x588))->IsSomething() != 0;
    *(int*)((char*)this + 0x684) += delta;
    int  after  = *(int*)((char*)this + 0x684) > 0 ||
                  ((cCombatant*)((char*)this + 0x588))->IsSomething() != 0;
    if (before != (after != 0)) {        char* o = (char*)this + 0x34;
        if (*(int*)((char*)this + 0x684) > 0 ||
            ((cCombatant*)((char*)this + 0x588))->IsSomething() != 0) {
            ((void(__thiscall*)(void*, int))VF((char*)this + 0x588, 0x50 / 4))((char*)this + 0x588, 0);
            void* tgt = ((void*(__thiscall*)(void*))VF(o, 0xb0 / 4))(o);
            if (tgt != 0) {
                void* t2 = ((void*(__thiscall*)(void*))VF(o, 0xb0 / 4))(o);
                ((void(__thiscall*)(void*, void*))VF(t2, 0xc4 / 4))(t2,
                    ((void*(__thiscall*)(void*, int, int, int))VF(o, 0xac / 4))(o, 0, 1, 0));
            }
        } else {
            void* tgt = ((void*(__thiscall*)(void*))VF(o, 0xb0 / 4))(o);
            if (tgt != 0) {
                void* t2 = ((void*(__thiscall*)(void*))VF(o, 0xb0 / 4))(o);
                ((void(__thiscall*)(void*, void*))VF(t2, 0xc4 / 4))(t2,
                    ((void*(__thiscall*)(void*, int, int, int))VF(o, 0xac / 4))(o, 1, 1, 0));
            }
        }
    }
}

// @ 0x00bcd250
int __thiscall cVehicle::bcd250()
{
    cSPTimer* t = (cSPTimer*)((char*)this + 0x660);
    if (t->IsRunning())
        return t->GetElapsedTime();
    return 0;
}

// @ 0x00bcd2a0
bool cGameData_s00bc_d2a0::Write(void* pArchive)
{
    void* v1 = ((void* (__thiscall*)(void*))vc(pArchive, 0x20))(pArchive);
    u32 id = 0x70704db;
    u32 handle = ((u32 (__thiscall*)(void*))vc(v1, 0x18))(v1);
    FUN_0093aa70((void*)handle, &id, (void*)1, 0);

    bool b = ((bool (__thiscall*)(void*))FUN_00bcc350)(pArchive) != 0;
    if (b) {
        b = ((bool (__thiscall*)(void*))FUN_00bcc350)(pArchive) != 0;
    }
    VarListSerializer ser;
    FUN_00692f90(&ser, this, &PTR_s_field_name_0156deb4, (void*)0x1a80d26);
    if (b) {
        if (FUN_00692900(&ser, pArchive)) return true;
    }
    return false;
}

// @ 0x00bcd340
bool cGameData_s00bc_d2a0::Read(void* pArchive)
{
    void* v1 = ((void* (__thiscall*)(void*))vc(pArchive, 0x20))(pArchive);
    u32 id;
    u32 handle = ((u32 (__thiscall*)(void*))vc(v1, 0x18))(v1);
    FUN_0093a780((void*)handle, &id, (void*)1, 0);

    bool b = ((bool (__thiscall*)(void*))FUN_00bcc400)(pArchive) != 0;
    if (b) {
        b = ((bool (__thiscall*)(void*))FUN_00bcc400)(pArchive) != 0;
    }
    VarListSerializer ser;
    FUN_00692f90(&ser, this, &PTR_s_field_name_0156deb4, (void*)0x1a80d26);
    if (b) {
        if (FUN_00693e10(&ser, pArchive)) return true;
    }
    return false;
}

// @ 0x00bcd3f0
void cCommunityT::SetFloat(float v)
{
    if (v != mField_64) {
        ((cCommunityBase*)this)->func5Ch(v);
        mbField_30c = 1;
    }
}

// @ 0x00bcd450
bool __cdecl FUN_00bcd450(u32 param_1, u32* param_2)
{
    if (*param_2 != 0) {
        ((void (__thiscall*)(void*, void*, void*, void*))FUN_00695b40)(
            (void*)param_1, (void*)*param_2, &DAT_01570858, (void*)L"cCombatant");
    }
    return true;
}

// @ 0x00bcd480
float __cdecl FUN_00bcd480_(int empireID, float fallback, float value)
{
    if (FUN_00b5b800() == (void*)&DAT_01654c05) {
        if (empireID == (int)FUN_01021090()) {
            int divisor = 1;
            int activePlanet = *(int*)((u8*)FUN_01021260() + 0x13c);
            if ((int)FUN_01021370() == activePlanet) {
                divisor = ((int (__thiscall*)(void*))FUN_0102fb70)(FUN_0102f810());
            }
            return value / (float)divisor;
        }
    }
    return fallback;
}

// @ 0x00bcd4e0
void cOwnerT::SetModelKey2(void* pKey)
{
    u32* k = (u32*)pKey;
    (void)k;
    if (((u32*)pKey)[0] != *(u32*)((u8*)this + 0x90) ||
        ((u32*)pKey)[1] != *(u32*)((u8*)this + 0x94) ||
        ((u32*)pKey)[2] != *(u32*)((u8*)this + 0x98)) {
        if ((((u32*)pKey)[2] & 0xff00) != 0x7e00) {
            *(u32*)((u8*)this + 0x1f0) = ((u32*)pKey)[0];
            *(u32*)((u8*)this + 0x1f4) = ((u32*)pKey)[1];
            *(u32*)((u8*)this + 0x1f8) = ((u32*)pKey)[2];
        }
        if (*(u8*)((u8*)this + 0x1fc) == 0) {
            return ((void (__thiscall*)(void*, void*))FUN_00c88810)(this, pKey);
        }
    }
}

// @ 0x00bcd550
void cOwnerT::SetFlag(char on)
{
    if (on != (char)mbFlag_230) {
        void* pKey;
        u32 key[3];
        if (on != 0) {
            key[1] = 0;
            key[2] = 0;
            pKey = key;
            key[0] = 0xd1bf030c;
        } else {
            pKey = (u8*)this + 0x224;
        }
        ((void (__thiscall*)(void*, void*))FUN_00c88810)((u8*)this + 0x34, pKey);
        void* owner = mpOwner_1f0;
        mbFlag_230 = (u8)on;
        if (owner != 0) {
            ((void (__thiscall*)(void*))FUN_00bd9e50)(owner);
        }
    }
}

// @ 0x00bcd5b0
void cOwnerT::SetOwnerCity2(void* pCity)
{
    ((void (__thiscall*)(void*, void*))FUN_00b18550)(this, pCity);
    void* prev = mpOwner_1f0;
    if (pCity != prev) {
        if (pCity != 0) {
            ((void (__thiscall*)(void*))vc(pCity, 0))(pCity);   // AddRef
        }
        mpOwner_1f0 = pCity;
        if (prev != 0) {
            ((void (__thiscall*)(void*))vc(prev, 4))(prev);     // Release
        }
    }
}

// @ 0x00bcd5f0
void cOwnerT::RemoveOwner()
{
    ((void (__thiscall*)(void*))FUN_00bfc720)((u8*)this + 0x120);
    ((void (__thiscall*)(void*))FUN_00ac0450)((u8*)this + 0x108);
    ((void (__thiscall*)(void*))FUN_00c8b2e0)((u8*)this + 0x34);
    void* p = mpOwner_1f0;
    if (p != 0) {
        mpOwner_1f0 = 0;
        ((void (__thiscall*)(void*))vc(p, 4))(p);
    }
}

// @ 0x00bcd630
void* cOwnerT::GetOwnerCivilization()
{
    if (mpOwner_1f0 == 0) return 0;
    void* pCity = ((void* (__thiscall*)(void*))vc(this, 0x30))(this);
    if (pCity != 0) {
        void* type = ((void* (__thiscall*)(void*))vc(pCity, 0x20))(pCity);
        if (type != (void*)0x018c43e8) pCity = 0;
    } else {
        pCity = 0;
    }
    int id = ((int (__thiscall*)(void*))vc(this, 0x4c))(this);
    if (id == -1) {
        return ((void* (__thiscall*)(void*))FUN_00bd9bf0)(pCity);
    }
    int id2 = ((int (__thiscall*)(void*))vc(this, 0x4c))(this);
    return ((void* (__thiscall*)(void*, void*))FUN_00b25f40)(FUN_00b3d300(), (void*)id2);
}

// @ 0x00bcd690
void cOwnerT::GetNextWanderNode(char mode, int count)
{
    if (!((bool (__thiscall*)(void*))vc((u8*)this + 0x34, 0x48))((u8*)this + 0x34))
        return;

    u32 kind;
    if (mode == 0) {
        if (count != 0) return;
        if ((float)FUN_0059da80(1.0f) >= 0.33f) return;
        kind = 1;
        count = 2;
    } else {
        kind = 2;
        count = 5;
    }

    float ox = DAT_0168b66c;
    float oy = DAT_0168b670;
    float oz = DAT_0168b674;
    float px = ox, py = oy, pz = oz;

    if (mode != 1 && *(u32*)((u8*)this + 0x308) != *(u32*)((u8*)this + 0x30c)) {
        u32 span = *(u32*)((u8*)this + 0x30c) - *(u32*)((u8*)this + 0x308);
        u32 i = (u32)FUN_00a68fb0(&DAT_01601760, span / 0x38);
        u8* e = (u8*)(*(u32*)((u8*)this + 0x308) + i * 0x38);
        px = *(float*)(e + 4);
        py = *(float*)(e + 8);
        pz = *(float*)(e + 0xc);
        float s = (float)FUN_0059da80(5.0f) + 4.0f;
        ox = *(float*)(e + 0x20) * s;
        oy = *(float*)(e + 0x24) * s;
        oz = *(float*)(e + 0x28) * s;
    } else {
        Vec3 tmp;
        float* r = (float*)((void* (__thiscall*)(void*, Vec3*))vc((u8*)this + 0x120, 0x20))(
            (u8*)this + 0x120, &tmp);
        float* q = (float*)((void* (__thiscall*)(void*))vc((u8*)this + 0x34, 0x2c))((u8*)this + 0x34);
        px = r[0] + q[0];
        py = r[1] + q[1];
        pz = r[2] + q[2];
    }

    void* eff = FUN_00b3d480(px, py, pz, ox, oy, oz);
    u32 id = ((u32 (__thiscall*)(void*))vc(this, 0x4c))(this);
    FUN_00d5cfd0((void*)kind, (void*)count, (void*)id, &eff, &eff, &eff);
}

// @ 0x00bcd890
void cOwnerT::UpdateCityFlags(void* pObj)
{
    u8 found = 0;
    void* value = (void*)0xffffffff;
    if (pObj == 0) return;

    void* a = ((void* (__thiscall*)(void*, void*))vc(pObj, 0x5c))(pObj, (void*)0x137e8e0);
    if (a != 0 && *(int*)((u8*)a + 0xb20) == 0) {
        found = 1;
        value = ((void* (__thiscall*)(void*))vc((u8*)a + 0x508, 0x10))((u8*)a + 0x508);
    }
    void* b = ((void* (__thiscall*)(void*, void*))vc(pObj, 0x5c))(pObj, (void*)0xb033b403);
    if (b != 0) {
        found = 1;
        value = ((void* (__thiscall*)(void*))vc(b, 0x4c))(b);
    }
    void* c = ((void* (__thiscall*)(void*, void*))vc(pObj, 0x5c))(pObj, (void*)0xd0036e08);
    if (c == 0) {
        if (!found) return;
    } else {
        value = ((void* (__thiscall*)(void*))vc(c, 0x4c))(c);
    }
    if (*(int*)((u8*)this + 0xd0) == 0) return;

    void* s = ((void* (__thiscall*)(void*))vc(pObj, 8))(pObj);
    float* pos = (float*)((void* (__thiscall*)(void*))vc(s, 0x2c))(s);
    Vec3 v;
    v.x = pos[0]; v.y = pos[1]; v.z = pos[2]; v.w = pos[3];
    void* civ = FUN_00bd9bf0(*(void**)((u8*)this + 0xd0));
    FUN_00bf02b0(civ, value);
    FUN_00c00b00((void*)0, value, &v);
}

// @ 0x00bcd970
bool __cdecl FUN_00bcd970(void* pPlanet, float dist, void* pPoint)
{
    if (pPoint == 0) return false;
    dist = dist + 2.0f;

    Vec3f tmp;
    void* model = FUN_00b3d350(pPlanet);
    if (FUN_00b8bb70(model, 0, pPlanet, dist, &tmp)) return false;

    void** p = (void**)FUN_0108db30(pPoint, 0);   // {begin, end} of the body list
    WaterBody* cur = (WaterBody*)p[0];
    WaterBody* end = (WaterBody*)p[1];
    if (cur == end) return true;
    do {
        void* m = FUN_00b3d350(pPlanet);
        float d = FUN_00b81470(m, 0, pPlanet, cur);
        if (cur->mRadius_0c > d) return false;
        ++cur;
    } while (cur != end);
    return true;
}

// @ 0x00bcda00
bool cOwnerT::func7Ch(void* pPlanet)
{
    u8* pOwner = (u8*)mpOwner_1f0;
    if (pOwner == 0) return false;
    Vec3f key;
    Vec3f* k = ((Vec3f* (__thiscall*)(u8*, Vec3f*))vc(pOwner, 0x5c))(pOwner, &key);
    void* model = FUN_00b3d350(pPlanet);
    float dist = FUN_00b81470(model, 0, pPlanet, k);
    float radius = ((float (__thiscall*)(u8*))vc(pOwner, 0x60))(pOwner);
    if (radius > dist) {
        float t = ((float (__thiscall*)(u8*))vc((u8*)this + 0x34, 0x70))((u8*)this + 0x34);
        return FUN_00bcd970(pPlanet, t, pOwner);
    }
    return false;
}

// @ 0x00bcda90
void cOwnerT::RefreshModelKeys()
{
    if (mpField_1ec == 0) return;
    for (;;) {
        int idx = ((int (__thiscall*)(void*, int, int))vc(mpField_1ec, 0x6c))(mpField_1ec, 0, 8);
        if (idx == -1) break;
        void* entry = ((void* (__thiscall*)(void*, int))vc(mpField_1ec, 0x60))(mpField_1ec, idx);
        if (entry == 0) continue;
        void* obj = ((void* (__thiscall*)(void*, void*))vc(*(void**)((u8*)entry + 0xc), 0xc))(
            *(void**)((u8*)entry + 0xc), (void*)0x73905ae);
        if (obj == 0) continue;
        ((void (__thiscall*)(void*))vc(obj, 4))(obj);
        ((void (__thiscall*)(void*, void*))vc(mpField_1ec, 0x78))(mpField_1ec, obj);
        void* a = FUN_00c6f660(obj);
        if (a == 0) {
            ((void (__thiscall*)(void*))vc(obj, 8))(obj);
            continue;
        }
        void* t = ((void* (__thiscall*)(void*, void*))vc(a, 0xc))(a, (void*)0x01186577);
        if (t == 0) {
            ((void (__thiscall*)(void*))vc(obj, 8))(obj);
            continue;
        }
        u8* self34 = (u8*)this + 0x34;
        ((void (__thiscall*)(void*, void*))vc(t, 0x38))(t,
            ((void* (__thiscall*)(void*))vc(self34, 0x2c))(self34));
        ((void (__thiscall*)(void*, void*))vc(t, 0x3c))(t,
            ((void* (__thiscall*)(void*))vc(self34, 0x30))(self34));
        *(u8*)((u8*)t + 0x71) = 0;
        float* v = (float*)((void* (__thiscall*)(void*))vc(self34, 0x2c))(self34);
        float inv = 1.0f / (float)sqrt((double)(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + 1e-8f));
        Vec3 n;
        ((void (__thiscall*)(void*, Vec3*))vc(self34, 0x5c))(self34, &n);
        Vec3 n2;
        ((void (__thiscall*)(void*, Vec3*))vc(self34, 0x5c))(self34, &n2);
        float ax = n2.x + n.x;
        float ay = n2.y + n.y;
        float az = n2.z + n.z;
        float inv2 = 1.0f / (float)sqrt((double)(ax * ax + ay * ay + az * az + 1e-8f));
        Vec3 dir;
        dir.x = (ax * inv2) * DAT_0156def0;
        dir.y = (ay * inv2) * DAT_0156def0;
        dir.z = (az * inv2) * DAT_0156def0;
        dir.w = 0.0f;
        FUN_00b3d310(t, &dir, 0);
        FUN_00b452f0(t, &dir, 0);
        FUN_00b3d310(self34, t, (void*)0x40000000);
        FUN_00b4c600(self34, t, (void*)0x40000000);
        (void)inv;
        ((void (__thiscall*)(void*))vc(obj, 8))(obj);
    }
}

// @ 0x00bcddc0
void cOwnerT::RemoveOwnerFull()
{
    if (*(void**)((u8*)this + 0x344) != 0) {
        ((void (__thiscall*)(void*, void*))FUN_00b225d0)(FUN_00b3d300(), *(void**)((u8*)this + 0x344));
        void* n2 = *(void**)((u8*)this + 0x344);
        *(void**)((u8*)this + 0x344) = 0;
        if (n2 != 0) {
            ((void (__thiscall*)(void*))vc(n2, 4))(n2);
        }
    }
    ((void (__thiscall*)(void*))FUN_00bfc720)((u8*)this + 0x120);
    ((void (__thiscall*)(void*))FUN_00ac0450)((u8*)this + 0x108);
    ((void (__thiscall*)(void*))FUN_00c8b2e0)((u8*)this + 0x34);
    void* p = *(void**)((u8*)this + 0x1f0);
    if (p != 0) {
        *(void**)((u8*)this + 0x1f0) = 0;
        return ((void (__thiscall*)(void*))vc(p, 4))(p);
    }
}

// @ 0x00bcde40
float __cdecl FUN_00bcde40(u32 param_1)
{
    return FUN_00bcd480_(param_1, DAT_0169c0fc, DAT_0169c100);
}

// @ 0x00bcde70
float __cdecl FUN_00bcde70(u32 param_1)
{
    return FUN_00bcd480_(param_1, DAT_0169c07c, DAT_0169c080);
}

// @ 0x00bcdea0
float __cdecl FUN_00bcdea0(u32 param_1)
{
    return FUN_00bcd480_(param_1, DAT_0169c0a8, DAT_0169c0ac);
}

// @ 0x00bcded0
cTurret::cTurret()
{
    u8* self = (u8*)this;
    ((void (__thiscall*)(void*))FUN_00b18660)(self);
    ((void (__thiscall*)(void*))FUN_00c43860)(self + 0x34);
    ((void (__thiscall*)(void*))FUN_00ac03d0)(self + 0x504);
    ((void (__thiscall*)(void*))FUN_00abfe50)(self + 0x51c);
    ((void (__thiscall*)(void*))FUN_00bfd4e0)(self + 0x588);
    *(void**)(self + 0x650) = &PTR_FUN_01466c14;
    ((void (__thiscall*)(void*))FUN_00b63890)(self + 0x660);
    *(void**)(self)         = &vtbl_Simulator_cTurret;
    *(void**)(self + 4)     = &PTR_FUN_01466e7c;
    *(void**)(self + 0x34)  = &PTR_FUN_01466d80;
    *(void**)(self + 0x108) = &PTR_FUN_01466d74;
    *(void**)(self + 0x504) = &PTR_FUN_01466d58;
    *(void**)(self + 0x51c) = &PTR_FUN_01466cf0;
    *(void**)(self + 0x588) = &PTR_FUN_01466c88;
    *(void**)(self + 0x650) = &PTR_FUN_01466c60;
    *(u32*)(self + 0x680) = 0;
    *(u32*)(self + 0x684) = 0;
    *(u32*)(self + 0x688) = 0;
    *(u32*)(self + 0x68c) = 0;
    *(u32*)(self + 0x690) = 0;
    *(u32*)(self + 0x694) = 0;
    *(u32*)(self + 0x698) = 0;
    *(u32*)(self + 0x69c) = 0;
    *(u32*)(self + 0x6a0) = 0;
    *(u32*)(self + 0x6a4) = 0;
    *(u32*)(self + 0x6a8) = 0xffffffff;
    ((void (__thiscall*)(void*))FUN_00b63890)(self + 0x6b0);
}

// @ 0x00bce0a0
cTurret::~cTurret()
{
    u8* self = (u8*)this;
    *(void**)(self)         = &vtbl_Simulator_cTurret;
    *(void**)(self + 4)     = &PTR_FUN_01466e7c;
    *(void**)(self + 0x34)  = &PTR_FUN_01466d80;
    *(void**)(self + 0x108) = &PTR_FUN_01466d74;
    *(void**)(self + 0x504) = &PTR_FUN_01466d58;
    *(void**)(self + 0x51c) = &PTR_FUN_01466cf0;
    *(void**)(self + 0x588) = &PTR_FUN_01466c88;
    *(void**)(self + 0x650) = &PTR_FUN_01466c60;
    ((void (__thiscall*)(void*))FUN_00b638b0)(self + 0x6b0);
    void* p1 = *(void**)(self + 0x6a4);
    if (p1 != 0) ((void (__thiscall*)(void*))vc(p1, 0x64))(p1);
    void* p2 = *(void**)(self + 0x6a0);
    if (p2 != 0) ((void (__thiscall*)(void*))vc(p2, 4))(p2);
    void* p3 = *(void**)(self + 0x69c);
    if (p3 != 0) ((void (__thiscall*)(void*))vc(p3, 8))(p3);
    void* p4 = *(void**)(self + 0x698);
    if (p4 != 0) ((void (__thiscall*)(void*))vc(p4, 8))(p4);
    void* p5 = *(void**)(self + 0x694);
    if (p5 != 0) ((void (__thiscall*)(void*))vc(p5, 8))(p5);
    void* p6 = *(void**)(self + 0x690);
    if (p6 != 0) ((void (__thiscall*)(void*))vc(p6, 8))(p6);
    void* p7 = *(void**)(self + 0x68c);
    if (p7 != 0) ((void (__thiscall*)(void*))vc(p7, 8))(p7);
    void* p8 = *(void**)(self + 0x688);
    if (p8 != 0) ((void (__thiscall*)(void*))vc(p8, 4))(p8);
    void* p9 = *(void**)(self + 0x680);
    if (p9 != 0) ((void (__thiscall*)(void*))vc(p9, 4))(p9);
    ((void (__thiscall*)(void*))FUN_00b638b0)(self + 0x660);
    *(void**)(self + 0x650) = &PTR_FUN_01466c14;
    ((void (__thiscall*)(void*))FUN_00bfcd00)(self + 0x588);
    ((void (__thiscall*)(void*))FUN_00abfec0)(self + 0x51c);
    ((void (__thiscall*)(void*))FUN_00ac0520)(self + 0x504);
    ((void (__thiscall*)(void*))FUN_00c432e0)(self + 0x34);
    ((void (__thiscall*)(void*))FUN_00b184c0)(self);
}

// @ 0x00bce1e0
void cBuilding::FUN_00bce1e0()
{
    if (mp690 != 0 && mp690->FUN_0104bd50()) {
        cToolData* r = FUN_00b3d390(mp690);
        r->UseToolStop();
    }
    if (mp694 != 0 && mp694->FUN_0104bd50()) {
        cToolData* r = FUN_00b3d390(mp694);
        r->UseToolStop();
    }
    if (mp698 != 0 && mp698->FUN_0104bd50()) {
        cToolData* r = FUN_00b3d390(mp698);
        r->UseToolStop();
    }
    if (mp69c != 0 && mp69c->FUN_0104bd50()) {
        cToolData* r = FUN_00b3d390(mp69c);
        r->UseToolStop();
    }

    {
        void* p = mp68c;
        if (p != 0) {
            mp68c = 0;
            VC0(void, p, 8);
        }
    }
    {
        void* p = mp690;
        if (p != 0) {
            mp690 = 0;
            VC0(void, p, 8);
        }
    }
    {
        void* p = mp694;
        if (p != 0) {
            mp694 = 0;
            VC0(void, p, 8);
        }
    }
    {
        void* p = mp698;
        if (p != 0) {
            mp698 = 0;
            VC0(void, p, 8);
        }
    }
    {
        void* p = mp69c;
        if (p != 0) {
            mp69c = 0;
            VC0(void, p, 8);
        }
    }
    {
        void* p = mp6a4;
        if (p != 0) {
            mp6a4 = 0;
            VC0(void, p, 0x64);
        }
    }

    if (mp680 != 0) {
        if (VC0(bool, mp680, 0x10))
            VC1(void, mp680, 0xc, void*, 0);
    }
    {
        void* p = mp680;
        if (p != 0) {
            mp680 = 0;
            VC0(void, p, 4);
        }
    }

    if (mp6a0 != 0) {
        SP_NounManager()->RemoveNoun(mp6a0);
        void* p = mp6a0;
        mp6a0 = 0;
        if (p != 0)
            VC0(void, p, 4);
    }
    {
        void* p = mp688;
        mp688 = 0;
        if (p != 0)
            VC0(void, p, 4);
    }

    m588.FUN_00bfc720();
    m504.FUN_00ac0450();
    m51C.FUN_00abf710();

    {
        void* p = mpRef2c;
        if (p != 0) {
            mpRef2c = 0;
            VC0(void, p, 4);
        }
    }

    m34.FUN_00c43f90();
}

// @ 0x00bce400
void FUN_00bce400(void* param_1)
{
    FUN_00bcd480(param_1, g_f169c1b0, g_f169c1b4);
}

// @ 0x00bce5d0
int cBuilding::FUN_00bce5d0()
{
    void* p = mp100;
    if (p == 0)
        return -1;
    return VC0(int, p, 0x4c);
}

// @ 0x00bce5f0
bool cSpatialObject_s00bc_e1e0::FUN_00bce5f0(u32 param_2)
{
    if (LoadModel(param_2)) {
        void* p = mp9c;
        void* q = *(void**)((char*)p + 0x90);
        if (q != 0) {
            Vec3u v;
            if (GetPropertyAsVector3(q, 0x475062du, &v))
                m620 = v;
        }
        return true;
    }
    return false;
}

// @ 0x00bce660
void cBuilding::FUN_00bce660(void* param_2)
{
    bool bVar1 = false;
    int uVar5 = -1;

    if (param_2 == 0)
        return;

    RType660* r = VC1(RType660*, param_2, 0x5c, u32, 0x137e8e0u);
    if (r != 0 && r->mB20 == 0) {
        bVar1 = true;
        uVar5 = VC0(int, &r->m508, 0x10);
    }

    void* p = VC1(void*, param_2, 0x5c, u32, 0xb033b403u);
    if (p != 0) {
        bVar1 = true;
        uVar5 = VC0(int, p, 0x4c);
    }

    void* q = VC1(void*, param_2, 0x5c, u32, 0xd0036e08u);
    if (q != 0) {
        uVar5 = VC0(int, q, 0x4c);
    } else if (!bVar1) {
        return;
    }

    cVt8Obj* r2 = VC0(cVt8Obj*, param_2, 8);
    Vector3* pv = VC0(Vector3*, r2, 0x2c);

    cCiv* civ = mp100->GetCivilization(uVar5, *pv);
    civ->FUN_00bf02b0();
    mp100->FUN_00c00b00(0, uVar5);
}

// @ 0x00bce8b0
void cCommunity::FUN_00bce8b0(u32 param_2)
{
    func54h((void*)param_2);
    void* p = mp66c;
    if (p != 0)
        VC1(void, (char*)p + 0x70, 0x38, u32, param_2);
}

// @ 0x00bce8e0
void cBuilding::SetOwnerCity1(void* param_2)
{
    SetGameDataOwner2(param_2);

    void* oldCity = mp1f0;
    if (param_2 != oldCity) {
        if (param_2 != 0)
            VC0(void, param_2, 0);
        mp1f0 = param_2;
        if (oldCity != 0)
            VC0(void, oldCity, 4);
    }

    void* noun = SP_NounManager()->CreateNoun(0x21ffa3fu);

    void* inv;
    if (noun != 0)
        inv = VC1(void*, noun, 0xc, u32, 0xb075dec5u);
    else
        inv = 0;

    void* oldInv = mp1ec;
    if (inv != oldInv) {
        if (inv != 0)
            VC0(void, inv, 0);
        mp1ec = inv;
        if (oldInv != 0)
            VC0(void, oldInv, 4);
    }
}

// @ 0x00bce970
void cBuilding::FUN_00bce970()
{
    RType* r = g_globals16c7aa4->mp74->FUN_00f3f950(this);
    if (r != 0)
        m120.FUN_00bfc470(r->m01);
}

// @ 0x00bce9a0
float cBuilding::GetCost()
{
    VC0(void, this, 0x4c);
    return 0.0f;
}

// @ 0x00bce9b0
void cBuilding::FUN_00bce9b0()
{
    m120.FUN_00bfc720();
    m108.FUN_00ac0450();
    m34.FUN_00c8b2e0();

    void* p = mp1f0;
    if (p != 0) {
        mp1f0 = 0;
        VC0(void, p, 4);
    }
    if (mp1ec != 0)
        SP_NounManager()->RemoveNoun(mp1ec);
}

// @ 0x00bcea10
void cBuilding::FUN_00bcea10(u32 param_2)
{
    FUN_00bcd4e0(param_2);
    m30c = 1;
}

// @ 0x00bcea30
float FUN_00bcea30(u32 a, u32 b, u32 c, float def)
{
    void* local = 0;
    void* pm = PropertyManager();
    if (local != 0) {
        void* old = local;
        local = 0;
        VC0(void, old, 4);
    }
    if (VC3(bool, pm, 0x2c, u32, a, u32, b, void**, &local)) {
        cVariant* out;
        if (VC2(bool, local, 0x24, u32, c, cVariant**, &out)) {
            u16 t = out->mType;
            float* pf;
            if (t == 0xd || t == 0x10) {
                if ((out->mFlags & 0x30) != 0)
                    pf = (float*)out->mPtr;
                else
                    pf = (t != 0) ? (float*)out : 0;
            } else {
                pf = &g_f15d9c6c;
            }
            float f = *pf;
            if (local != 0)
                VC0(void, local, 4);
            return f;
        }
    }
    if (local != 0)
        VC0(void, local, 4);
    return def;
}

// @ 0x00bcebc0
Vector3* FUN_00bcebc0()
{
    if (g_v756d754.x == -1.0f) {
        void* local = 0;
        void* pm = PropertyManager();
        if (local != 0) {
            void* old = local;
            local = 0;
            VC0(void, old, 4);
        }
        if (VC3(bool, pm, 0x2c, u32, 0x4529f96fu, u32, 0x40636200u,
                void**, &local))
            GetPropertyAsVector3(local, 0x48f5b53u, &g_v756d754);
        if (local != 0)
            VC0(void, local, 4);
    }
    return &g_v756d754;
}

// @ 0x00bcec50
Vector3* FUN_00bcec50()
{
    if (g_v756d760.x == -1.0f) {
        void* local = 0;
        void* pm = PropertyManager();
        if (local != 0) {
            void* old = local;
            local = 0;
            VC0(void, old, 4);
        }
        if (VC3(bool, pm, 0x2c, u32, 0x4529f96fu, u32, 0x40636200u,
                void**, &local))
            GetPropertyAsVector3(local, 0x48f5b54u, &g_v756d760);
        if (local != 0)
            VC0(void, local, 4);
    }
    return &g_v756d760;
}

// @ 0x00bcf6f0
void BldCombatant::TakeDamage(float damage, uint att, int type, const Vector3_s00bc_f6f0& v, Combatant* src)
{
    Building* b = (Building*)((char*)this - 0x120);
    Spatial* sp = (Spatial*)((char*)this - 0xec);
    if (b->IsDestroyed())
        return;

    bool flag;
    if (type == 0xc || type == 0xa || type == 0x10 || type == 4) {
        flag = false;
    } else {
        flag = true;
        if (type == 0xf)
            flag = false;
    }

    if (type == 0xb) {
        b->GetOwnerCity()->mTimer230.Restart();
        return;
    }
    if (type == 0xc) {
        if ((int)att != (int)b->GetPoliticalID()) {
            b->GetOwnerCity()->F00be2bb0(damage, att);
            return;
        }
    } else if (type == 0x10) {
        IEffect* eff = 0;
        EffectsMgr* mgr = EffectsManager();
        if (eff) {
            IEffect* o = eff;
            eff = 0;
            o->Release();
        }
        if (mgr->CreateEffect(0xa14e0379, 0, &eff)) {
            XformMsg msg;
            float h = sp->GetLocalExtents().hi.z + 0.2f;
            Vector3_s00bc_f6f0 n = SP::normalized_safe(sp->GetPosition());
            Vector3_s00bc_f6f0 off;
            off.x = h * n.x;
            off.y = n.y * h;
            off.z = n.z * h;
            const Vector3_s00bc_f6f0& p0 = sp->GetPosition();
            Vector3_s00bc_f6f0 p;
            p.x = p0.x + off.x;
            p.y = p0.y + off.y;
            p.z = p0.z + off.z;
            msg.SetPos(p);
            Matrix3 m0;
            Vector3_s00bc_f6f0 dir = sp->GetDirection();
            msg.SetRot(*SP::Matrix3FromFacingAndUp(&m0, &dir, &sp->GetPosition()));
            msg.SetScale(4.0f);
            eff->SetTransform(&msg);
            eff->Start(0);
        }
        int dmg = (int)damage;
        b->GetOwnerCity()->F00bd8300(dmg);
        b->GetOwnerCity()->GetCivilization()->mCounter += dmg;
        if (eff)
            eff->Release();
        return;
    }

    if (src && src->Cast(0x436f315))
        return;
    if (SP::GetCurrentGameMode() == 0x1654c05) {
        ShipInfo* si = F00ae3370(src);
        if (si && si->mKind == 3)
            att = SP::GetPlayerEmpireID();
    }
    if (!flag)
        goto base;

    if (att == (uint)SP::GetPlayerEmpireID())
        b->GetOwnerCity()->F00bdbf10();

    if (SP::GetCurrentGameMode() == 0x1654c05) {
        Inventory* inv = SP::GetUFOSimulator()->GetPlayerInventory();
        Combatant* pc = inv ? (Combatant*)((char*)inv + 0x508) : 0;
        if (src == pc) {
            if ((int)b->GetPoliticalID() != SP::GetPlayerEmpireID())
                SP::GetUFOSimulator()->F00ffd830(b->GetOwnerCity());
        }
    }

    if (SP::GetCurrentGameMode() == 0x1654c05) {
        if (SP::GetActivePlanet()->F00c70e00() != 4 || (int)att == SP::GetPlayerEmpireID()) {
            City* city = b->GetOwnerCity();
            int player = SP::GetPlayerEmpireID();
            if (SP::GetCurrentGameMode() == 0x1654c05 && SP::GetActivePlanet()->F00c70e00() == 4 && (int)att == player)
                goto base;
            if (city->mField74c == (int)att && !(city->mField748 < 100.0f))
                goto base;
            if (!F01029a10(att, SP::GetActivePlanetRecord()))
                goto base;
            bool inRange;
            if ((int)b->GetPoliticalID() == player) {
                inRange = ((int)att == player);
            } else {
                if ((int)att != player)
                    goto capture;
                inRange = !F01021230()->mFlag;
            }
            if (inRange)
                goto base;
        capture:
            float n = (float)city->F00bd9bb0() * 0.083333336f;
            float lo = SP::GetSpaceCombatTuning()->F0102a4f0();
            float hi = SP::GetSpaceCombatTuning()->F0102a540();
            float t = (hi - lo) * n + lo;
            city->F00c00b00(0, att);
            F00be9b20(SP::GetActivePlanetRecord(), city, city->F00bd81f0(), city->GetPoliticalID(),
                      SP::GetSpaceCombatTuning()->GetCityCaptureFactor() * t * damage, att, false);
            return;
        }
    }

    if ((int)att != -1 && SP::GetCurrentGameMode() == 0x1654c04 && 0.0f < damage
        && (int)b->GetPoliticalID() != (int)att) {
        SP::RelationshipManager()->RecordFoughtEnemyEvent(b->GetPoliticalID(), att, 0x526e501, 1.0f);
        if ((int)att == SP::NounManager()->F00b1f9d0()) {
            Timer* t = &mAttackTimer;
            bool skip = false;
            if (t->IsRunning()) {
                uint64 el = t->GetElapsedTime();
                if (el <= 0x1388)
                    skip = true;
            }
            if (!skip && sp->IsOnView()) {
                EffectRef ref;
                ref.p = 0;
                if (EffectsManager()->CreateEffect(0x69a49c25, 0, ref.AsPPTypeParam())) {
                    XformMsg msg;
                    float h = sp->GetLocalExtents().hi.z + 2.0f;
                    Vector3_s00bc_f6f0 n = SP::normalized_safe(sp->GetPosition());
                    Vector3_s00bc_f6f0 off;
                    off.x = n.x * h;
                    off.y = n.y * h;
                    off.z = n.z * h;
                    const Vector3_s00bc_f6f0& p0 = sp->GetPosition();
                    Vector3_s00bc_f6f0 p;
                    p.x = p0.x + off.x;
                    p.y = p0.y + off.y;
                    p.z = p0.z + off.z;
                    msg.SetPos(p);
                    Matrix3 m0;
                    Vector3_s00bc_f6f0 dir = sp->GetDirection();
                    msg.SetRot(*SP::Matrix3FromFacingAndUp(&m0, &dir, &sp->GetPosition()));
                    msg.SetScale(4.0f);
                    ref.p->SetTransform(&msg);
                    ref.p->Start(0);
                }
                t->Restart();
            }
        }
    }

    if (!b->GetOwnerCity()->F00bd9d20() && type != 0xd)
        return;
    b->F00bcd690(0, type);
    F00be9b20(SP::GetActivePlanetRecord(), b->GetOwnerCity(), b->GetOwnerCity()->F00bd81f0(),
              b->GetOwnerCity()->GetPoliticalID(), damage, att, type == 0xd);
    return;
base:
    TakeDamageBase(damage, att, type, v, src);
}

// @ 0x00bd1820
cBuilding_s00bd_1820::cBuilding_s00bd_1820()
{
    ctor_cGameData(this);

    cSpatialObjectABI* pSpatial = &mSpatial;
    ctor_cSpatialObject(pSpatial);
    cInteractionABI* pInteraction = &mInteraction;
    ctor_cInteractionTarget(pInteraction);
    cCombatABI* pCombatant = &mCombatant;
    ctor_cCombatant(pCombatant);

    // Interim cPlaceableStructure-half vptr, then the full base vptr set.
    mpVtblPlaceable = (void*)&cPlaceableStructure_baseVtable;
    pCombatant->mpVtbl = (void*)&cBuilding_vtable4;
    mpVtbl0 = (void*)&cBuilding_vtable0;
    mpVtbl1 = (void*)&cBuilding_vtable1;
    pSpatial->mpVtbl = (void*)&cBuilding_vtable2;
    pInteraction->mpVtbl = (void*)&cBuilding_vtable3;
    mpVtblPlaceable = (void*)&cBuilding_vtable5;

    mF1ec = 0;
    mF1f0 = 0;
    mF1f4 = 1;

    // Zero the inline coordinate-array header, then initialise it with capacity 0.
    cCoordArray* pCoords = &mCoords;
    pCoords->mInline[0] = 0;
    pCoords->mInline[1] = 0;
    pCoords->mInline[2] = 0;
    pCoords->mInline[3] = 0;
    pCoords->mInline[4] = 0;
    pCoords->mInline[5] = 0;
    pCoords->mpCurrent = 0;
    pCoords->mpUnused1c = 0;
    pCoords->mpCapacity = 0;
    pCoords->mpUnused24 = 0;
    pCoords->Init(0);

    mF224 = 0;
    mF228 = 0;
    mF22c = 0;
    mF230 = 0;
    ctor_cGonzagoTimer(&mTimer1);
    ctor_cGonzagoTimer(&mTimer2);

    mName.mpBegin = gEmptyString16;
    mName.mpEnd = gEmptyString16;
    mName.mpCapacity = gEmptyString16 + 1;
    mF288 = 1;
    mF289 = 1;
    mF28c = 0;
    mF290 = 0;
    mF294 = 0;
    mF298 = 0;
    mF29c = 0;
    mF2a0 = 0;
    mF2a4 = 0;
    mF2a8 = 0;
    mF2b4 = 0;
    mF2b8 = 0;
    mF2bc = 0;
    mF2c8 = 0;
    mF2cc = 0;
    mF2d0 = 0;
    mF2dc = 0;
    mF2e0 = 0;
    mF2e4 = 0;
    mF2f0 = 0;
    mF2f4 = 0;
    mF2f8 = 0;
    mF2fc = 0;
    mF308 = 0;
    mF30c = 0;
    mF310 = 0;
    ctor_cGonzagoTimer(&mTimer3);

    mField88 = 7;
    mbFlagA5 = 1;

    AABB bounds;
    bounds.minx = gExtentMin;
    bounds.miny = gExtentMin;
    bounds.minz = gExtentMin;
    bounds.maxx = gExtentMax;
    bounds.maxy = gExtentMax;
    bounds.maxz = gExtentMax;
    pSpatial->SetLocalExtents(bounds, 1.0f);

    mbFlagA4 = 0;
    float fProp = GetPropertyFloat(0xa4c2f6bd, 0, (void*)0x17efa840, gPropDefault);
    mField14c = fProp;
    mField158 = fProp;

    u32 nLen = 0;
    while (gBuildingName[nLen] != 0)
        ++nLen;
    mName.assign(gBuildingName, gBuildingName + nLen);
    Fn_00bcebc0();
}

// @ 0x00bd27d0
void __fastcall Fn_00bd27d0(cBuilding_s00bd_1820* pThis)
{
    cCoordVec* pVec = &pThis->mTailVec;
    pThis->mpVtbl0 = (void*)&cBuildingScenario_vtable0;
    pThis->mpVtbl1 = (void*)&cBuildingScenario_vtable1;
    pThis->mpVtblSpatial = (void*)&cBuildingScenario_vtable2;
    pThis->mpVtblInteraction = (void*)&cBuildingScenario_vtable3;
    pThis->mpVtblCombatant = (void*)&cBuildingScenario_vtable4;
    pThis->mpVtblPlaceable = (void*)&cBuildingScenario_vtable5;

    pVec->DestroyRange(pVec->mpBegin, pVec->mpEnd);
    u32* pBegin = pVec->mpBegin;
    if (pBegin != 0 && pBegin[-1] != 0)
        FreeObj(pBegin);
    dtor_cBuilding(pThis);
}

// @ 0x00bd2840
uint8_t FUN_00bd2840(int* visitor, const char* name, PropBlock* block)
{
    uint8_t result = 1;
    if (block->mpCur == block->mpEnd)
        return result;

    bool noName = (name == 0);
    wchar_t* pName;
    wchar_t  bufA[6];
    wchar_t  bufB[6];

    if (noName) {
        int zeroed[3];
        zeroed[0] = 0; zeroed[1] = 0; zeroed[2] = 0;
        WStringRangeInitialize(zeroed, 0, 0);
        WStringConstruct((void*)zeroed, 0);
        pName = (wchar_t*)zeroed[1];
        if (2 < (int)((char*)zeroed[2] - (char*)zeroed[1] & 0xfffffffe) && zeroed[1] != 0)
            operator_delete((void*)zeroed[1]);
    }
    else {
        void* s = EA_ConvertToString16(bufA, name, -1);
        WStringConstruct(bufB, s);
        if (2 < (int)((char*)bufA[2] - (char*)bufA[0] & 0xfffffffe) && bufA[0] != 0)
            operator_delete((void*)bufA[0]);
        pName = bufB;
    }

    const wchar_t* label = pName;
    ((PropVisitor*)visitor)->SetName(label);

    int* i = block->mpIter;                 // +0x10
    int* chunkEnd = block->mpNextArray;     // +0x0c
    int* chunkBase = block->mpChunkBase;    // +0x14
    int* end = block->mpEnd;                // +0x18

    while (i != end) {
        if (result) {
            if (!TypedValueToStringShort(visitor, 0, *i, kWUint32))
                result = 0;
        }
        ++i;
        if (i == chunkEnd) {
            i = (int*)chunkBase[1];
            chunkBase += 1;
            chunkEnd = (int*)((char*)i + 0x100);
        }
    }

    const wchar_t* lbl = pName;
    ((PropVisitor*)visitor)->SetValue(lbl);
    if (2 < (int)((char*)block->mpCur - (char*)pName & 0xfffffffe) && pName != 0)
        operator_delete(pName);

    return result;
}

// @ 0x00bd2a10
Record* FUN_00bd2a10(Record* begin, Record* end, Record* dst)
{
    if (begin != end) {
        do {
            ((cSPTransformOps*)dst)->Assign(begin);
            dst->mField38 = begin->mField38;
            dst->mField3c = begin->mField3c;
            dst->mField40 = begin->mField40;
            dst->mField44 = begin->mField44;
            dst->mField48 = begin->mField48;
            dst->mVec4c = begin->mVec4c;
            begin = (Record*)((char*)begin + 0x0c64);
            dst   = (Record*)((char*)dst   + 0x0c64);
        } while (begin != end);
    }
    return dst;
}

// @ 0x00bd2a80
Record* FUN_00bd2a80(Record* begin, Record* end, Record* dst)
{
    if (end != begin) {
        do {
            end = (Record*)((char*)end - 0x0c64);
            dst = (Record*)((char*)dst - 0x0c64);
            ((cSPTransformOps*)dst)->Assign(end);
            dst->mField38 = end->mField38;
            dst->mField3c = end->mField3c;
            dst->mField40 = end->mField40;
            dst->mField44 = end->mField44;
            dst->mField48 = end->mField48;
            dst->mVec4c = end->mVec4c;
        } while (end != begin);
    }
    return dst;
}

// @ 0x00bd2af0
void cPlacedModel::UpdateWorldGeometry()
{
    int count = mLocalPoints.size();
    mWorldPoints.resize(count);
    mWorldNormals.resize(count);

    float scale = mLocomotive.GetScale();
    Quaternion q = mLocomotive.GetOrientation();
    const Vector3_s00bd_2840* pPosition = &mLocomotive.GetPosition();

    if (count > 0) {
        float yy = q.y * q.y;
        float xy = q.y * q.x;
        float zz = q.z * q.z;
        float zx = q.z * q.x;
        float zy = q.z * q.y;
        float zw = q.z * q.w;
        float xx = q.x * q.x;
        float wx = q.w * q.x;
        float wy = q.w * q.y;
        float a01 = xy - zw;
        float a02 = wy + zx;
        float m00 = 1.0f - (zz + yy) * 2.0f;
        float a12 = zy - wx;
        float a10 = zw + xy;
        float m11 = 1.0f - (zz + xx) * 2.0f;
        float a21 = wx + zy;
        float a20 = zx - wy;
        float m22 = 1.0f - (yy + xx) * 2.0f;

        for (int i = 0; i < count; ++i) {
            Vector3_s00bd_2840 p = mLocalPoints[i];
            Vector3_s00bd_2840 v;
            v.x = p.x * scale;
            v.y = p.y * scale;
            v.z = p.z * scale;
            Vector3_s00bd_2840 r = Rotate(q, v);
            Vector3_s00bd_2840 dir;
            dir.x = pPosition->x + r.x;
            dir.y = pPosition->y + r.y;
            dir.z = pPosition->z + r.z;
            Vector3_s00bd_2840 tmp;
            dir = *SP::PlanetModel()->DirectionToSurfacePosition(&tmp, &dir);
            mWorldPoints[i] = dir;

            float nx = mLocalNormals[i].x;
            float ny = mLocalNormals[i].y;
            float nz = mLocalNormals[i].z;
            Vector3_s00bd_2840& out = mWorldNormals[i];
            out.x = (a02 * nz + a01 * ny) * 2.0f + m00 * nx;
            out.y = (a10 * nx + a12 * nz) * 2.0f + m11 * ny;
            out.z = (a20 * nx + a21 * ny) * 2.0f + m22 * nz;
        }
    }

    mWorldDirty = 1;

    Matrix3 rotation;
    cSPTransform_s00bd_2840 xf;
    xf.SetOffset(*pPosition);
    xf.SetRotation(*SP::Matrix3FromQuaternion(&rotation, q));

    int numParts = mLocalTransforms.size();
    mWorldTransforms.resize(numParts);
    for (int i = 0; i < numParts; ++i) {
        cSPTransform_s00bd_2840 t;
        t.SetOffset(xf.mOffset);
        t.SetScale(scale);
        t.SetRotation(xf.mRotation);
        t.Accumulate(&mLocalTransforms[i]);
        mWorldTransforms[i] = t;
    }

    if (mpHelper)
        mpHelper->Update();
}

// @ 0x00bd3230
void cCommunity_s00bd_2840::CallFunc58(void* arg)
{
    cCommunity_s00bd_2840* self = this;
    self->func58h(arg);
    RefreshTail(self);
}

// @ 0x00bd3280
uint8_t cCommunity_s00bd_2840::FindPeerA(cCommunity_s00bd_2840* other)
{
    cCommunity_s00bd_2840* self = this;
    int* o = (int*)other;
    if (o[0x0b20 / 4] == 1) {
        void* key = (self != 0) ? (void*)((char*)self + 0x34) : 0;
        if (CommunityKey(other) == key)
            return 0;
    }

    int* vec = (int*)((cGameNounManager_s00bd_2840*)SP_NounManager_s00bd_2840())->GetGameDataVector(
        (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00ae72d0, (void*)FUN_00b1e500,
        (void*)0x018c6de8);
    int count = (int)(vec[2] - vec[1]) >> 2;
    for (int i = 0; i < count; ++i) {
        cObject* n = *(cObject**)(vec[1] + i * 4);
        if (n == (cObject*)other)
            continue;
        int a = n->Slot4c();
        int b = ((cObject*)other)->Slot4c();
        if (a != b)
            continue;
        if (*(int*)((char*)n + 0x0b20) != 1)
            continue;
        void* key = (self != 0) ? (void*)((char*)self + 0x120) : 0;
        void* got = ((cObjectHeader*)((char*)n + 0x508))->Slot54();
        if (got == key)
            return 1;
    }
    return 0;
}

// @ 0x00bd3380
void cCommunity_s00bd_2840::SetDirection(float* dir)
{
    cCommunity_s00bd_2840* self = this;
    cPlacedModel* owner = (cPlacedModel*)((char*)self - 0x34);
    float offset = g_f1486110;
    if (SP::GetCurrentGameMode_s00bd_2840() == (void*)0x01654c10)
        offset = 0.0f;

    if (owner->Slot84() != 0) {
        void* s2 = owner->Slot84();
        if (*(void**)((char*)s2 + 0x324) != 0) {
            void* s3 = owner->Slot84();
            offset = SampleChildField260(*(void**)((char*)s3 + 0x324));
        }
    }

    self->mDir314 = *(Vector3_s00bd_2840*)dir;

    Vector3_s00bd_2840 d = *(Vector3_s00bd_2840*)dir;
    float inv = 1.0f / sqrtf((d.x * d.x + d.y * d.y) + d.z * d.z + g_f13ec4b8);
    float t[3];
    t[0] = d.x + (d.x * inv) * offset;
    t[1] = d.y + (d.y * inv) * offset;
    t[2] = d.z + (d.z * inv) * offset;

    self->func54h(t);
    RefreshTail(self);

    void* child = self->mpChild310;
    if (child != 0) {
        void* slot = *(void**)((char*)child + 0x70);
        void (*fn)(void*, float*) = *(void (**)(void*, float*))((char*)slot + 0x38);
        fn((char*)child + 0x70, t);
    }
}

// @ 0x00bd3500
void cCommunity_s00bd_2840::CallFunc54(float* dir)
{
    cCommunity_s00bd_2840* self = this;
    self->func54h(dir);
    RefreshTail(self);
}

// @ 0x00bd3550
uint8_t cCommunity_s00bd_2840::FindPeerB(cCommunity_s00bd_2840* other)
{
    cCommunity_s00bd_2840* self = this;
    int* o = (int*)other;
    if (o[0x0b20 / 4] == 1) {
        void* key = (self != 0) ? (void*)((char*)self + 0x34) : 0;
        if (CommunityKey(other) == key)
            return 0;
    }

    int* vec = (int*)((cGameNounManager_s00bd_2840*)SP_NounManager_s00bd_2840())->GetGameDataVector(
        (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00ae72d0, (void*)FUN_00b1e500,
        (void*)0x018c6de8);
    int count = (int)(vec[2] - vec[1]) >> 2;
    for (int i = 0; i < count; ++i) {
        cObject* n = *(cObject**)(vec[1] + i * 4);
        if (n == (cObject*)other)
            continue;
        int a = n->Slot4c();
        int b = ((cObject*)other)->Slot4c();
        if (a != b)
            continue;
        if (*(int*)((char*)n + 0x0b20) != 1)
            continue;
        void* key = (self != 0) ? (void*)((char*)self + 0x34) : 0;
        if (CommunityKey(n) == key)
            return 1;
    }
    return 0;
}

// @ 0x00bd3640
void cCommunity_s00bd_2840::SetPosition(float* v)
{
    cCommunity_s00bd_2840* self = this;
    if (v[0] != self->mPosition.x || v[1] != self->mPosition.y || v[2] != self->mPosition.z) {
        self->func54h(v);
        RefreshTail(self);
        self->mDirty30c = 1;
    }
}

// @ 0x00bd36c0
void cCommunity_s00bd_2840::SetOrientation(float* v)
{
    cCommunity_s00bd_2840* self = this;
    if (v[0] != self->mOrientation.x || v[1] != self->mOrientation.y ||
        v[2] != self->mOrientation.z || v[3] != self->mOrientation.w) {
        self->func58h(v);
        RefreshTail(self);
        self->mDirty30c = 1;
    }
}

// @ 0x00bd5ea0
bool __fastcall FUN_00bd5ea0(cCheatObject* self)
{
  bool result = true;
  IV* spatial = (IV*)((char*)self + 0x34);
  uint* key = (uint*)((Fn_p_v)VT(spatial, 0x98))(spatial);
  uint kInstance = key[0];
  uint kType     = key[1];
  uint kGroup    = key[2];
  if (kInstance == 0)
    return result;

  IV* rm = (IV*)SP_ResourceMan_GetManager();
  if (((char(__thiscall*)(IV*, const void*, int, int, int, int, int))VT(rm, 0xc))
        (rm, key, 0, 0, 0, 0, 0))
    return result;

  uint nounId = self->GetNounKey();
  SP_NounManager(nounId);
  FUN_00b25f40(SP_NounManager(nounId), nounId);

  ConstraintVector constraints;
  uint prop = 0x4e3f7777;
  uint type = self->GetNounID();
  if (type == 0x1a56aba)
    prop = 0x72c49181;
  else if (type == 0x18ea1eb || type == 0x70703b3)
    prop = 0x99e92f05;
  else if (type == 0x18ea2cc)
    prop = 0x47c10953;
  constraints.push_back(Constraint_s00bd_5ea0(0x2dc9d1e, 0, prop));
  constraints.push_back(Constraint_s00bd_5ea0(0x3cc89b1, 0, 0x913b23be));

  IV* db = (IV*)SP_ObjectTemplateDB();
  uint found = 0, pad = 0, found2 = 0;
  if (!((char(__thiscall*)(IV*, uint*, int, uint*))VT(db, 0x24))(db, &found, 1, &pad)) {
    result = false;
  } else {
    db = (IV*)SP_ObjectTemplateDB();
    ((void(__thiscall*)(IV*, uint, int))VT(db, 0x58))(db, found, 1);
    uint local2[3];
    FUN_00ba5df0(&local2[0], key);
    for (char* slot = gTemplateSlotTable; slot < gTemplateSlotEnd; slot += 0x1c) {
      if (FUN_00bf2c80(slot, (void*)prop)) {
        uint* p = (uint*)FUN_00bf9700(slot, (void*)prop);
        if (p[0] == kInstance && p[1] == kType && p[2] == kGroup)
          FUN_00bf4a60(slot, (void*)prop, (void*)found);
      }
    }
    GameDataVec* v = NounManager_s00bd_5ea0()->GetGameDataVector(
        (void*)0x00b21080, (void*)0x00d3d420, (void*)0x00b236c0, (void*)0x00b1e500, 0x18c816a);
    for (void** it = (void**)v->mpBegin; it != (void**)v->mpEnd; ++it) {
      uint* mk = (uint*)FUN_00bf9770(*it, (void*)prop);
      if (mk[0] == kInstance && mk[1] == kType && mk[2] == kGroup)
        FUN_00bf4b10(*it, (void*)prop, (void*)found);
    }
  }
  return result;
}

// @ 0x00bd6180
void* __fastcall FUN_00bd6180(char* self)
{
  if (self[0x340])
    ((void(__fastcall*)(char*))FUN_00bd40a0)(self);
  return self + 0x344;
}

// @ 0x0132abc0
void FUN_0132abc0()
{
    ADD_ATTR(sBuildingsAttributes, 0, "mIsOn", 0x02416eb8, 0x1f4, Read4<TBld0>, Write4<TBld0>, ReadTextT<TBld0>, WriteTextT<TBld0>, Valid<TBld0>, ToXmlT<TBld0>)              // 0xac8750 0xac8780 0x693090 0x694fa0 0xb1fbf0 0x57ce00
    ADD_ATTR(sBuildingsAttributes, 1, "mpOwnerCity", 0x02416ebb, 0x1f0, Read4<TBld1>, Write4<TBld1>, ReadText_00c2e4e0, WriteText_00692fb0, Valid<TBld1>, ToXmlT<TBld1>)       // 0xae9e00 0xbca960 0xc2e4e0 0x692fb0 0xb6f550 0xac8050
    ADD_ATTR(sBuildingsAttributes, 2, "mEvents", 0x041614aa, 0x1f8, Read4<TBld2>, Write4<TBld2>, ReadText_00c2e4e0, WriteText_00692fb0, Valid<TBld2>, ToXmlT<TBld2>)           // 0xbd16d0 0xbd0bb0 0xc2e4e0 0x692fb0 0xbd0c80 0xbd2840
    ADD_ATTR(sBuildingsAttributes, 3, "mAttackTimer", 0x04ac7af1, 0x238, Read4<TBld3>, Write4<TBld3>, ReadText_00c2e4e0, WriteText_00692fb0, Valid<TBld3>, ToXmlT<TBld3>)       // 0xae3470 0xae3490 0xc2e4e0 0x692fb0 0xae3310 0xac8050
    ADD_ATTR(sBuildingsAttributes, 4, "mDestroyTimer", 0x05b9555b, 0x258, Read4<TBld4>, Write4<TBld4>, ReadText_00c2e4e0, WriteText_00692fb0, Valid<TBld4>, ToXmlT<TBld4>)      // 0xae3470 0xae3490 0xc2e4e0 0x692fb0 0xae3310 0xac8050
    ADD_ATTR(sBuildingsAttributes, 5, "mConnected", 0x04b74e33, 0x289, Read4<TBld5>, Write4<TBld5>, ReadTextT<TBld5>, WriteTextT<TBld5>, Valid<TBld5>, ToXmlT<TBld5>)           // 0xac8750 0xac8780 0x693090 0x694fa0 0xb1fbf0 0x57ce00
    ADD_ATTR(sBuildingsAttributes, 6, "mEffectiveness", 0x04b74e34, 0x28c, Read4<TBld6>, Write4<TBld6>, ReadTextT<TBld6>, WriteTextT<TBld6>, Valid_00b1fbf0, ToXml_0057cde0)     // 0x572810 0x572840 0x692ff0 0x694ee0
    ADD_ATTR(sBuildingsAttributes, 7, "mFreezeCount", 0x04b74e37, 0x290, Read4<TBld7>, Write4<TBld7>, ReadTextT<TBld7>, WriteTextT<TBld7>, Valid_00b1fbf0, ToXml_0057cde0)       // 0x572810 0x572840 0x692ff0 0x694ee0
    ADD_ATTR(sBuildingsAttributes, 8, "mMoneyCount", 0x04efa697, 0x294, Read4<TBld8>, Write4<TBld8>, ReadTextT<TBld8>, WriteTextT<TBld8>, Valid_00b1fbf0, ToXml_0057cde0)        // 0x572810 0x572840 0x692ff0 0x694ee0
    ADD_ATTR(sBuildingsAttributes, 9, "mHappyCount", 0x04efa698, 0x298, Read4<TBld9>, Write4<TBld9>, ReadTextT<TBld9>, WriteTextT<TBld9>, Valid_00b1fbf0, ToXml_0057cde0)        // 0x572810 0x572840 0x692ff0 0x694ee0
    ADD_ATTR(sBuildingsAttributes, 10, "mUnhappyCount", 0x04efa699, 0x29c, Read4<TBld10>, Write4<TBld10>, ReadTextT<TBld10>, WriteTextT<TBld10>, Valid_00b1fbf0, ToXml_0057cde0)  // 0x572810 0x572840 0x692ff0 0x694ee0
    ADD_ATTR(sBuildingsAttributes, 11, "mNormalModelKey", 0x05e4d3d3, 0x224, Read4<TBld11>, Write4<TBld11>, ReadTextT<TBld11>, WriteTextT<TBld11>, Valid<TBld11>, ToXmlT<TBld11>)  // 0xae3430 0xae3450 0x693150 0x695080 0xb1fbf0 0xae5720
    ADD_ATTR(sBuildingsAttributes, 12, "mbIrradiated", 0x05e4d3d4, 0x230, Read4<TBld12>, Write4<TBld12>, ReadTextT<TBld12>, WriteTextT<TBld12>, Valid<TBld12>, ToXmlT<TBld12>)     // 0xac8750 0xac8780 0x693090 0x694fa0 0xb1fbf0 0x57ce00
}

// @ 0x0132b1f0
void FUN_0132b1f0()
{
    ADD_ATTR(sBuildingWeaponsAttributes, 0, "mpCity", 0x044585b1, 0x688, Read4<TW0>, Write4<TW0>, ReadTextT<TW0>, WriteText_00692fb0, Valid<TW0>, ToXml_00ac8050)                    // 0xae9e00 0xbca960 0xc2e4e0 0x692fb0 0xb6f550 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 1, "mpWeapon", 0x044585b2, 0x68c, Read4<TW1>, Write4<TW1>, ReadTextT<TW1>, WriteText_00692fb0, Valid<TW1>, ToXml_00ac8050)                  // 0xbceb00 0xbd1780 0xc2e4e0 0x692fb0 0xc87090 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 2, "mpCivTurretWeapon", 0x04c5a1ef, 0x690, Read4<TW2>, Write4<TW2>, ReadTextT<TW2>, WriteText_00692fb0, Valid<TW2>, ToXml_00ac8050)         // 0xbceb00 0xbd1780 0xc2e4e0 0x692fb0 0xc87090 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 3, "mpSpaceBeamWeapon", 0x04c5a1f5, 0x694, Read4<TW3>, Write4<TW3>, ReadTextT<TW3>, WriteText_00692fb0, Valid<TW3>, ToXml_00ac8050)          // 0xbceb00 0xbd1780 0xc2e4e0 0x692fb0 0xc87090 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 4, "mpSpaceDefenseMissileWeapon", 0x05790752, 0x698, Read4<TW4>, Write4<TW4>, ReadTextT<TW4>, WriteText_00692fb0, Valid<TW4>, ToXml_00ac8050)  // 0xbceb00 0xbd1780 0xc2e4e0 0x692fb0 0xc87090 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 5, "mpSpaceTurretFlak", 0x0579fa14, 0x69c, Read4<TW5>, Write4<TW5>, ReadTextT<TW5>, WriteText_00692fb0, Valid<TW5>, ToXml_00ac8050)           // 0xbceb00 0xbd1780 0xc2e4e0 0x692fb0 0xc87090 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 6, "mDestroyTimer", 0x04161444, 0x660, Read4<TW6>, Write4<TW6>, ReadTextT<TW6>, WriteText_00692fb0, Valid<TW6>, ToXml_00ac8050)             // 0xae3470 0xae3490 0xc2e4e0 0x692fb0 0xae3310 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 7, "mFreezeCount", 0x04161445, 0x684, Read4<TW7>, Write4<TW7>, ReadTextT<TW7>, WriteTextT<TW7>, Valid<TW7>, ToXmlT<TW7>)                    // 0x572810 0x572840 0x692ff0 0x694ee0 0xb1fbf0 0x57cde0
    ADD_ATTR(sBuildingWeaponsAttributes, 8, "mpHitSphere", 0x04161446, 0x6a0, Read4<TW8>, Write4<TW8>, ReadTextT<TW8>, WriteText_00692fb0, Valid<TW8>, ToXml_00ac8050)                // 0xbd0cb0 0xbca960 0xc2e4e0 0x692fb0 0xb6f550 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 9, "mpFacingTarget", 0x04161447, 0x6a4, Read4<TW9>, Write4<TW9>, ReadTextT<TW9>, WriteText_00692fb0, Valid<TW9>, ToXml_00ac8050)             // 0xbd0d50 0xbd17b0 0xc2e4e0 0x692fb0 0xbcd450 0xac8050
}
