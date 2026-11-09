// src/game/SPGonzago/SPTribeTool.cpp -- migrated from slice(s) s00c9de50, s00c9c1b0, s00c9d230, s004e12c0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeTool.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cTribeTool.h"
#include "SP/cITerrainSphere.h"
#include "SP/cCombatant.h"
#include "SP/cGameData.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cInteractionTarget.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPTimer.h"
#include "SP/cSpatialObject.h"
#include "SP/cVarListSerializer.h"
#include "SP/cCommunity.h"
#include "SP/cGameNounManager.h"
#include "SP/cRelationshipManager.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cTribeHut.h"
#include <math.h>
#include "SP/cAttachment.h"
#include "SP/cCivilization.h"
#include "SP/cConfigManager.h"
#include "SP/cCreatureAbility.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cString.h"
#include "SP/cVehicle.h"

// ---- items of slice s004e12c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PropertyHolder {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual bool GetProperty(int key, void* out); // +0x24
};
void* __fastcall ResolveIntValue(int v);    // 0x004e41c0
// ---- items of slice s004e12c0 end

// ---- items of slice s00c9d230 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
struct Vec3 { float x, y, z; };
struct DefObj {                        // object stored at combatant +0xa4 / +0xd8
    virtual void vf0();                // +0x00 (AddRef)
    virtual void Release();            // +0x04
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18)
    virtual void* vf4c();              // +0x4c  (no-argument form, used by Init)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28)
    PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35)
    virtual void* vf90();              // +0x90
    void FUN_00c987b0(uint32_t v);     // 0x00c987b0
};
struct DefObj3 {                       // same slot layout, three-argument vf4c
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18)
    virtual void* vf4c(int a, uint32_t b, float c);
};
struct StimObj {                       // object with slots +0x08 / +0x0c (FUN_00c9d670 param 5)
    PV(0) PV(1)
    virtual void* vf08();              // +0x08
    virtual void* vf0c(void* a);       // +0x0c
};
struct AnimCtl {
    void FUN_00bc97f0(int a, int b, float c, int d);   // 0x00bc97f0, ret 0x10
};
struct AnimOwner {
    uint8_t  pad[8];
    AnimCtl  mCtl;                     // +0x08
};
struct SubStream {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
    virtual void* vf18();              // +0x18
};
struct Stream {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
    virtual SubStream* vf20();                          // +0x20
    PV(9)
    virtual bool vf28(uint32_t hash, void* p, int n);   // +0x28
    virtual bool vf2c(void* p);                         // +0x2c
};
void EA_WriteUint32(void* stream, const uint32_t* p, int a, int b);   // 0x0093aa70
void EA_ReadInt32(void* stream, uint32_t* p, int a, int b);           // 0x0093a780
struct cVarListSerializer {
    cVarListSerializer(void* owner, void* vtbl, uint32_t hash);       // 0x00692f90
    bool Serialize(Stream* s);                                        // 0x00692900 (writer variant)
    bool SerializeRead(Stream* s);                                    // 0x00693e10 (reader variant)
    uint8_t pad[0xa14];
};
uint32_t GetCurrentGameMode();                     // 0x00b5b800
struct Worm {                                      // object at cPlanetModel +0x24
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
    virtual void* vf54(void* a, void* b);          // +0x54
    virtual void  vf58(void* a, int b);            // +0x58
};
struct cPlanetModel {
    uint8_t pad04[0x24];                           // +0x00 .. +0x23
    Worm*   mp24;                                  // +0x24
    void* BuildSurfaceOrientation2(void* a, void* b);   // 0x00b7f250
};
struct PmBuf {                                     // the 16-byte scratch handed to PlanetModel
    cPlanetModel* Init(void* v);                   // 0x00b3d350
};
cPlanetModel* PlanetModel();                       // 0x00b3d350 (singleton accessor)
struct LocExt {                                    // box returned by the spatial +0xac slot
    uint8_t pad00[0x90];
    void*   mp90;                                  // +0x90
};
struct cSPTimer {                                  // 8 bytes (lives at spatial +0xcc / abs 0x100)
    uint8_t pad[8];
    void Stop();                                   // 0x00bc3110
    void Restart();                                // 0x00bc3130
};
struct cGonzagoTimer {                             // 0x20 bytes
    uint8_t pad[0x20];
    void Ctor();                                   // 0x00b63890
    void Dtor();                                   // 0x00b638b0
    void Restart();                                // 0x00bc3130
};
struct cGameData {
    void*    vft0;                                 // +0x00
    void*    vft1;                                 // +0x04
    uint8_t  pad08[0x24];
    void*    mp2c;                                 // +0x2c
    uint8_t  pad30[0x04];
    void Ctor();                                   // 0x00b18660
    void Dtor();                                   // 0x00b184c0
    bool Write(Stream* s);                         // 0x00b18590
    bool Read(Stream* s);                          // 0x00b18600
    void IsDestroyed(uint32_t p);                  // 0x00bfd0d0
};
struct cSpatialObject {
    void*    vft;                                  // +0x00
    uint8_t  pad04[0x8c];
    uint32_t m90;                                  // +0x90 (abs 0xc4)
    uint32_t m94;                                  // +0x94 (abs 0xc8)
    uint32_t m98;                                  // +0x98 (abs 0xcc)
    uint8_t  pad9c[0x08];
    uint32_t m0a4;                                 // +0xa4 (abs 0xd8)
    uint32_t m0a8;                                 // +0xa8 (abs 0xdc)
    uint8_t  pad0ac[0x20];
    cSPTimer timer;                                // +0xcc (abs 0x100)
    void Ctor();                                   // 0x00c89630
    void SetLocalExtents(uint32_t a, float b);     // 0x00c89160, ret 8
    bool Write(Stream* s);                         // 0x00c88a90
    bool Read(Stream* s);                          // 0x00c88b00
    void FUN_00c8a420();                           // 0x00c8a420
    void FUN_00c8b2e0();                           // 0x00c8b2e0
};
struct cSpatialObjectV {                           // no-argument +0x2c form
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual void* vf2c();                          // +0x2c
    virtual void* vf30();                          // +0x30
    PV(13) PV(14)
    virtual void  vf3c(void* v);                   // +0x3c
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25)
    PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35)
    PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
    virtual LocExt* vfac();                        // +0xac
};
struct cSpatialObjectV2 {                          // one-argument +0x2c / +0x3c form
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual void* vf2c(void* p);                   // +0x2c
    PV(12) PV(13) PV(14)
    virtual void  vf3c(void* v);                   // +0x3c
};
struct cInteractionTarget {
    void*    vft;                                  // +0x00
    uint8_t  pad04[0x14];
    void Ctor();                                   // 0x00ac03d0
    void FUN_00ac0450();                           // 0x00ac0450
    void FUN_00ac0520();                           // 0x00ac0520
};
struct cCombatant {
    void*    vft;                                  // +0x000
    uint8_t  pad04[0x34];
    float    m38;                                  // +0x038
    uint8_t  pad3c[0x68];
    DefObj*  mDefObj;                              // +0x0a4 (abs 0x1c4)
    uint32_t mDefID;                               // +0x0a8 (abs 0x1c8)
    uint8_t  padac[0x14];
    void*    vftC0;                                // +0x0c0 (abs 0x1e0)
    uint8_t  padc4[0x04];
    void*    vftC8;                                // +0x0c8 (abs 0x1e8)
    float    mCc;                                  // +0x0cc (abs 0x1ec)
    uint32_t mD0;                                  // +0x0d0 (abs 0x1f0)
    uint32_t mD4;                                  // +0x0d4 (abs 0x1f4)
    DefObj*  mpOwner;                              // +0x0d8 (abs 0x1f8)
    uint32_t mDc;                                  // +0x0dc (abs 0x1fc)
    cGonzagoTimer timer1;                          // +0x0e0 (abs 0x200)
    cGonzagoTimer timer2;                          // +0x100 (abs 0x220)
    uint32_t m120;                                 // +0x120 (abs 0x240)
    uint32_t m124;                                 // +0x124 (abs 0x244)
    uint32_t m128;                                 // +0x128 (abs 0x248)
    uint8_t  pad12c[0xa20];
    AnimOwner* mpAnim;                             // +0xb4c (abs 0xc6c)
    void Ctor();                                   // 0x00bfd4e0
    bool Write(Stream* s);                         // 0x00bfc4a0
    bool Read(Stream* s);                          // 0x00bfc540
    void FUN_00bfc720();                           // 0x00bfc720
    void FUN_00bfcd00();                           // 0x00bfcd00
    void TakeHit(float dmg, int a, uint32_t b, uint32_t c, void* d);   // 0x00bfcdd0, ret 0x14
};
struct cTribeToolV {                               // the tool's own virtual slots
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual void* vf2c();                          // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    virtual void  vf48(void* a);                   // +0x48
    PV(19) PV(20) PV(21) PV(22)
    virtual void* vf5c(void* a);                   // +0x5c
};
struct Found {                                     // object returned by FUN_00b3d240
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23)
    virtual void* vf60(uint32_t a, void* b, void* c);   // +0x60
};
Found* FUN_00b3d240();                             // 0x00b3d240
struct cTribeTool {
    cGameData          gameData;                   // +0x000
    cSpatialObject     spatial;                    // +0x034
    cInteractionTarget interact;                   // +0x108
    cCombatant         combatant;                  // +0x120

    cTribeTool();
    ~cTribeTool();

    void Init(DefObj* p);
    void FUN_00c9d4d0();
    void SetLocalExtents(uint32_t a, float b);
    void FUN_00c9d5b0(uint32_t p);
    void FUN_00c9d670(float dmg, int a, uint32_t b, uint32_t c, void* d);
    bool GetIsPlayerOwned();
    void GetCastID(int p);
    bool Write(Stream* s);
    bool Read(Stream* s);
    void FUN_00c9dd50();

    void FUN_43c0(int p);                          // 0x00c88670
    void SetLocalExtentsRaw(uint32_t a, float b);  // same body as cSpatialObject::SetLocalExtents
};
struct GameNounManager { uint32_t GetPlayerTribe(); };   // 0x00bfc5f0
GameNounManager* NounManager();                          // 0x00b3d300
// ---- items of slice s00c9d230 end

// ---- items of slice s00c9c1b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_13f9428;                              // 0.001
extern float g_14745d8;                              // FLT_MAX
extern void** g_13f94d4;                             // cCombatant interface id (address)
struct IRefCounted {
    virtual void AddRef();                           // +0x00
    virtual void Release();                          // +0x04
};
struct cSPTimer_s00c9_c1b0 {
    uint8_t pad00[0x10];
    bool  IsRunning();                                                          // 00feba90 0x00feba90
    unsigned long long GetElapsedTime();                                        // 00bc3190 0x00bc3190
};
struct cTribeToolData {
    uint8_t  pad00[0x10];
    int      mField10;                               // +0x10
    int      mField14;                               // +0x14
    uint8_t  pad18[0x38 - 0x18];
    int      mField38;                               // +0x38
    bool IsNotType10();                              // 00c9cf70
};
extern cTribeToolData* gTribeTools[12];              // 01699a14
float   FUN_00bfc490(void* p);                      // 00bfc490
void* FUN_00b18460(void* p);                         // 00b18460
uint32_t FUN_011e0810(float f);                      // 011e0810
void* PlanetModel_s00c9_c1b0();                                 // 00b3d350
class cTribeTool_s00c9_c1b0 {
public:
    // --- vtable (this+0x00)
    virtual void     v00(); // +0x00
virtual void     v01();
virtual void     v02();
virtual void     v03();
virtual void     v04();
virtual void     v05();
virtual void     v06();
virtual void     v07();
virtual void     v08();
virtual void     v09();
virtual void     v0a();
virtual void     v0b();
    virtual uint32_t GetPositionKey();               // +0x30
virtual void     v0d();
virtual void     v0e();
virtual void     v0f();
virtual void     v10();
virtual void     v11();
    virtual void     SetOwnerKey(uint32_t key);      // +0x48
    virtual uint32_t GetOwnerKey();                  // +0x4c
virtual void     v14();
virtual void     v15();
    virtual uint32_t GetToolType();                  // +0x58 0x00c9d080
    virtual const void* GetModelKey();               // +0x5c
virtual void     v18();
virtual void     v19();

    // --- data
    uint8_t  pad04[0x2c - 0x04];
    IRefCounted* mpOwner2C;                          // +0x2c
    uint8_t  pad30[0x34 - 0x30];
    uint8_t  mSpatial[0x108 - 0x34];                 // +0x34 spatial object
    uint8_t  pad108[0x120 - 0x108];
    uint8_t  mCombatant[0x1e8 - 0x120];              // +0x120 combatant sub-object
    union {
        struct {
            int      mDamageHi;                      // +0x1e8
            int      mDamageHiP1;                    // +0x1ec
            int      mDamageHiP2;                    // +0x1f0
            int      mDamageMd;                      // +0x1f4
            int      mDamageMdP1;                    // +0x1f8
            int      mDamageMdP2;                    // +0x1fc
            int      mDamageLo;                      // +0x200
            int      mDamageLoP1;                    // +0x204
            int      mDamageLoP2;                    // +0x208
            int      mDamageHiQ1;                    // +0x20c
            int      mDamageHiQ2;                    // +0x210
            int      mDamageHiQ3;                    // +0x214
            uint8_t  pad218[0x220 - 0x218];
        };
        struct {
            uint8_t  pad1e8[0x200 - 0x1e8];
            cSPTimer_s00c9_c1b0 mTimer200;                      // +0x200  (creation timer)
            uint8_t  pad210[0x220 - 0x210];
        };
    };
    cSPTimer_s00c9_c1b0 mTimer220;                              // +0x220  (last-use timer)
    void*    mpNoun;                                 // +0x230
    void*    mpOwner234;                             // +0x234
    uint8_t  pad238[0x240 - 0x238];
    int      mStrikeCount240;                        // +0x240
    int      mStrikeCount244;                        // +0x244
    void*    mpField248;                             // +0x248

    // --- methods
    void  RemoveOwner();                             // 00c9c1b0 0x00c9c1b0
    void  SetOwnerIface(void* p);                    // 00c9c250 0x00c9c250
    bool  Serialize_Write(void* pStream);            // 00c9c310 0x00c9c310
    bool  Serialize_Read(void* pStream);             // 00c9c3c0 0x00c9c3c0
    void  SetupTribeHut(int arg);                    // 00c9c500 0x00c9c500
    uint32_t GetToolPosition(void* pOut);            // 00c9c5e0 0x00c9c5e0
    bool  HasToolNoun();                             // 00c9c2e0 0x00c9c2e0
    void  RefreshModelProps();                       // 00c9c680 0x00c9c680
    void* AsInterface(void* pIID);                   // 00c9cee0 0x00c9cee0
    void  AddStrikePoint(bool b);                    // 00c9cf90
    uint32_t SpawnToolIcon();                        // 00c9cfd0
    void  ReleaseToolIcon();                         // 00c9d030
    const char* GetToolTypeAsCharStar();             // 00c9d090 0x00c9d090
    uint32_t GetToolIconKey();                       // 00c9d110
    float GetTimeSinceCreation();                    // 00c9d160 0x00c9d160
    float GetTimeSinceLastUse();                     // 00c9d1c0
};
// ---- items of slice s00c9c1b0 end

// ---- items of slice s00c9de50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const int      kDefaultInt32Value;   // 015d1160
extern const uint32_t kDefaultUInt32Value;  // 015d1164
extern bool gTribeToolsLoaded;              // 01699a44
extern const uint32_t kPropTypeIndex;       // 0157c578
extern const uint32_t kPropSubIndex;        // 0157c57c
extern const uint32_t kPropKey;             // 0157c580
extern const uint32_t kPropField20;         // 0157c584
extern const uint32_t kPropM28;             // 0157c588
extern const uint32_t kPropM2c;             // 0157c58c
extern const uint32_t kPropM38;             // 0157c590
extern const uint32_t kPropKey1;            // 0157c594
extern const uint32_t kPropKey2;            // 0157c598
extern const uint32_t kPropKey3;            // 0157c59c
extern const uint32_t kPropFloat40;         // 0157c5a0
extern const uint32_t kPropText;            // 0157c5a4
extern const uint32_t kPropAbilityList;     // 0157c5a8
extern const uint32_t kPropM30;             // 0157c5ac
extern const uint32_t kPropM34;             // 0157c5b0
extern const uint32_t kPropM3c;             // 0157c5b4
extern const char kNameFormat[];            // 0x013f5b98
struct ResourceKey {
    uint32_t instance, type, group;
    ResourceKey() {}
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instance(i), type(t), group(g) {}
};
struct Property {
    void*    mpData;       // +0x00 (external data, or the inline value itself)
    uint32_t pad04[3];
    uint16_t mnFlags;      // +0x10 (0x30 = external data)
    uint16_t mnType;       // +0x12

    void* GetValuePtr()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
    const int* GetValueInt32()
    {
        if (mnType == 9 || mnType == 0x10)
            return (const int*)GetValuePtr();
        return &kDefaultInt32Value;
    }
    const uint32_t* GetValueUInt32()
    {
        if (mnType == 10 || mnType == 0x10)
            return (const uint32_t*)GetValuePtr();
        return &kDefaultUInt32Value;
    }
    const ResourceKey* GetValueKey();               // inline body below
    const ResourceKey* GetKeyTPTR();                // 00454b10 VariantTypeTraits<Key>::GetTPTR
    const float* GetFloat();                        // 0041ea70
};
const ResourceKey* DefaultResourceKey();            // 006bb640
inline const ResourceKey* Property::GetValueKey()
{
    if (mnType == 0x20 || mnType == 0x10)
        return (const ResourceKey*)GetValuePtr();
    return DefaultResourceKey();
}
struct PropertyList {
    virtual int AddRef();                           // +0x00
    virtual int Release();                          // +0x04
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual bool HasProperty(uint32_t id);          // +0x1c
virtual void v8();
virtual void v9();
    virtual Property* GetProperty(uint32_t id);     // +0x28
    int         mRefCount;                          // +0x04 (shared with the vptr slot view)
    ResourceKey mKey;                               // +0x08
};
struct PropertyListPtr {
    PropertyList* mpObject;
    PropertyListPtr() { mpObject = 0; }
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    PropertyList** AsParam()
    {
        PropertyList* p = mpObject;
        if (p) {
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};
struct UIntVector;
struct IPropManager {
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
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppOut);  // +0x2c
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
    virtual bool GetPropertyListIDs(uint32_t groupID, UIntVector& result);                      // +0x48
};
void __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380   // 00f47380
struct UIntVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    UIntVector() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    ~UIntVector()
    {
        uint32_t* p = mpBegin;
        if (p) {
            if (((uint32_t*)p)[-1]) { void* q = p; EASTL_allocator_deallocate(q); }
        }
    }
};
struct cString_s00c9_de50 {                                     // retail SP::cString (0x14 bytes)
    uint32_t d[5];
    cString_s00c9_de50();                                       // 006b5060
    cString_s00c9_de50(const cString_s00c9_de50& o);                       // 006b56f0
    ~cString_s00c9_de50();                                      // 006b5240
};
struct DefaultRefCounted;
struct DefaultRefCountedPtr {                        // eastl::intrusive_ptr<DefaultRefCounted>
    DefaultRefCounted* mpObject;
    DefaultRefCountedPtr() : mpObject(0) {}
    DefaultRefCountedPtr& operator=(const DefaultRefCountedPtr& o);   // 004e4350
};
struct cCreatureAbility_s00c9_de50 {
    virtual ~cCreatureAbility_s00c9_de50();
    int mnRefCount;                                  // +0x04
    uint32_t pad08[(0x13c - 0x08) / 4];
    cCreatureAbility_s00c9_de50();                              // 004d3760
};
struct AbilityRef {
    cCreatureAbility_s00c9_de50* mpObject;
    AbilityRef(cCreatureAbility_s00c9_de50* p) { mpObject = p; if (mpObject) mpObject->mnRefCount++; }
    ~AbilityRef()
    {
        if (mpObject) {
            int n = mpObject->mnRefCount - 1;
            mpObject->mnRefCount = mpObject->mnRefCount - 1;
            if (n == 0) {
                mpObject->mnRefCount = 1;
                delete mpObject;
            }
        }
    }
};
void* operator new(unsigned int size, const char* name, int flags, unsigned int align,
                   const char* file, int line);      // 00f473a0
struct cTribeToolData_s00c9_de50 {
    ResourceKey mListKey;       // +0x00 key of the property list
    uint32_t mTypeIndex;        // +0x0c
    uint32_t mSubIndex;         // +0x10
    ResourceKey mKey;           // +0x14
    uint32_t m20;               // +0x20
    DefaultRefCountedPtr mAbility;   // +0x24
    uint32_t m28, m2c;          // +0x28
    uint32_t m30, m34;          // +0x30
    int      m38, m3c;          // +0x38
    float    mFloat40;          // +0x40
    ResourceKey mKey1, mKey2, mKey3;   // +0x44
    cString_s00c9_de50  mText;             // +0x68

    cTribeToolData_s00c9_de50(const cString_s00c9_de50& s);
};
__forceinline cTribeToolData_s00c9_de50::cTribeToolData_s00c9_de50(const cString_s00c9_de50& s)
    : mListKey(0, 0, 0), mTypeIndex(0), mSubIndex(0), mKey(0, 0, 0), m20(0), mAbility(), m28(0x2481de5), m2c(0x2481de5),
      m30(0), m34(0), m38(0), m3c(2), mKey1(0, 0, 0), mKey2(0, 0, 0), mKey3(0, 0, 0), mText(s)
{
}
namespace SP {
IPropManager* PropertyManager();                                              // 0067de30
}
namespace SP {
bool GetPropertyAsText(PropertyList* p, uint32_t id, cString_s00c9_de50* pOut);           // 006a1360
}
namespace SP {
bool ReadAbilityData(cCreatureAbility_s00c9_de50* pAbility, PropertyList* pList);         // 004d92b0
}
uint32_t TribeToolIntProperty(PropertyList* p, uint32_t id, int zero);        // 00ac8fa0
extern cTribeToolData_s00c9_de50* gTribeTools_s00c9_de50[12];     // 01699a14
namespace SP {
class cTribeTool_s00c9_de50 { public:
    static bool LoadTribeToolData();  // 0x00c9de50 (SP::cTribeTool::LoadTribeToolData)
};
}
struct Float3 { float x, y, z; };
struct Vt05 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
};
struct Vt10 {
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
};
struct Vt21 {
virtual void x00();
virtual void x04();
virtual void x08();
virtual void x0c();
virtual void x10();
virtual void x14();
virtual void x18();
virtual void x1c();
virtual void x20();
virtual void x24();
virtual void x28();
virtual void x2c();
virtual void x30();
virtual void x34();
virtual void x38();
virtual void x3c();
virtual void x40();
virtual void x44();
virtual void x48();
virtual void x4c();
    virtual void x50();
};
struct cVehicle_s00c9_de50;
struct cLoco : Vt10 {
    virtual void  v28();
    virtual int   Slot2c();                 // +0x2c
    virtual void  v30();
    virtual float Slot34();                 // +0x34
virtual void  v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void  v48();
virtual void v4c();
virtual void v50();
virtual void v54();
    virtual bool  Slot58();                 // +0x58

    void* Find(uint32_t id);                // 0x00c41d00
    bool  Write(void* ar);                  // 0x00c448a0
    void  SetValue(float v, int n);         // 0x00c9ece0
    void  SetProperty(float v, int n);      // 0x00c41d20
    void  FormatName(cString_s00c9_de50* out);         // 0x00c9e5a0
    bool  IsLocalPlayer();                  // 0x00c9e690
};
struct cCombatant_s00c9_de50 : Vt21 {
    virtual float GetFraction();            // +0x58
    uint32_t pad04[(0x38 - 4) / 4];         // +0x04
    float    mValue;                        // +0x38

    void* Find(uint32_t id);                // 0x00bfc380
    bool  Write(void* ar);                  // 0x00bfc4a0
    float GetValue();                       // 0x00bfc490
};
struct cChild5d0 { uint32_t mWord; void* Find(uint32_t id); };   // 0x00abf740
struct cChild638 { uint32_t mWord; void* Find(uint32_t id); };   // 0x00ac0320
struct cChild650 { uint32_t mWord; void* Find(uint32_t id); };   // 0x00c7d050
struct cAttachmentChild {
    uint32_t pad00[(0x5f4) / 4];            // +0x000
    uint32_t mFlags;                        // +0x5f4 (attachment + 0x5fc)
    void Func(int a, int b, float c, int d);    // 0x00bc97f0
};
struct cAttachmentFlags {
    uint32_t pad00[(0x5fc - 0x08) / 4];     // +0x008
    uint32_t mFlags;                        // +0x5fc
};
struct cAttachment_s00c9_de50 {
    uint32_t pad00[2];                      // +0x00
    union {
        cAttachmentChild mChild;            // +0x08
        cAttachmentFlags mFlagsView;        // +0x08
    };
};
struct cGameDataInner {
    uint32_t pad00[(0x1c8) / 4];            // +0x000
    uint32_t mBits;                         // +0x1c8
};
struct cArchiveStream : Vt05 {
    virtual void z14();
    virtual uint32_t GetHandle();           // +0x18
};
struct cArchive : Vt05 {
virtual void y14();
virtual void y18();
virtual void y1c();
    virtual cArchiveStream* Slot20();       // +0x20
};
struct cVehicle_s00c9_de50 : Vt05 {
    virtual void* Slot14();                 // +0x14
virtual void  v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void  v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void  v38();
virtual void v3c();
virtual void v40();
virtual void v44();
    virtual void  v48();
    virtual int   Slot4c();                 // +0x4c
virtual void  v50();
virtual void v54();
virtual void v58();
    virtual const char* Slot5c();           // +0x5c

    uint32_t pad04[(0x34 - 0x04) / 4];      // +0x004
    cLoco    mLoco;                         // +0x034 (only the vptr is modelled)
    uint32_t pad38[(0xc4 - 0x38) / 4];      // +0x038
    uint32_t mPairIdA;                      // +0x0c4
    uint32_t mPairIdB;                      // +0x0c8
    uint32_t padCC[(0x508 - 0xcc) / 4];     // +0x0cc
    cCombatant_s00c9_de50 mCombatant;                  // +0x508
    uint32_t pad544[(0x5d0 - 0x544) / 4];   // +0x544
    cChild5d0 mChild5d0;                    // +0x5d0
    uint32_t pad5d4[(0x5e8 - 0x5d4) / 4];   // +0x5d4
    cGameDataInner* mpField5e8;             // +0x5e8
    uint32_t pad5ec[(0x638 - 0x5ec) / 4];   // +0x5ec
    cChild638 mChild638;                    // +0x638
    uint32_t pad63c[(0x650 - 0x63c) / 4];   // +0x63c
    cChild650 mChild650;                    // +0x650
    uint32_t pad654[(0x774 - 0x654) / 4];   // +0x654
    uint32_t mField774;                     // +0x774
    uint32_t mField778;                     // +0x778
    uint32_t mField77c;                     // +0x77c
    uint32_t pad780[(0xaf0 - 0x780) / 4];   // +0x780
    cAttachment_s00c9_de50* mpFieldAF0;                // +0xaf0
    uint32_t mFieldAF4;                     // +0xaf4
    uint32_t mFieldAF8;                     // +0xaf8
    uint32_t padAfc[(0xb1c - 0xafc) / 4];   // +0xafc
    int      mFieldB1c;                     // +0xb1c
    uint32_t mFieldB20;                     // +0xb20
    uint32_t padB24[(0xb90 - 0xb24) / 4];   // +0xb24
    int      mFieldB90;                     // +0xb90
    uint8_t  padB94[0xbce - 0xb94];         // +0xb94
    uint8_t  mFieldBCE;                     // +0xbce
    uint8_t  padBcf[0xc3c - 0xbcf];         // +0xbcf
    Float3   mVecC3c;                       // +0xc3c
    float    mFieldC48;                     // +0xc48
    float    mFieldC4C;                     // +0xc4c
    uint32_t padC50[(0xd04 - 0xc50) / 4];   // +0xc50
    int      mFieldD04;                     // +0xd04
    uint32_t padD08[(0xd24 - 0xd08) / 4];   // +0xd08
    uint32_t mFieldD24;                     // +0xd24
    uint32_t mFieldD28;                     // +0xd28

    void*  BaseFind(uint32_t id);           // 0x00b18460
    bool   BaseWriteAsText(void* ar);       // 0x00bfc860
    char   BaseRemoveOwner();               // 0x00bfc3a0
    bool   BaseWrite(void* ar);             // 0x00b18590

    cVehicle_s00c9_de50* Find(uint32_t id);            // 0x00c9e610
    void UpdateDamageState();               // 0x00c9e700
    void WriteAsText(void* ar);             // 0x00c9e760
    bool RemoveOwner(int owner);            // 0x00c9e790
    float GetHealthFraction();              // 0x00c9e7c0
    void GetC3C(Float3* out, float* a, float* b);   // 0x00c9e8a0
    float GetFraction();                    // 0x00c9ec00
    bool CanOccupyTerrain(int data);        // 0x00c9e960
    bool Write(cArchive* ar);               // 0x00c9e9e0
    int  GetMode();                         // 0x00c9eaf0
    float GetModeRadius();                  // 0x00c9eb80
    float GetArea();                        // 0x00c9ec50
    void SetDrone(bool on);                 // 0x00c9ec80
    void SetJustEyeCandy(bool on);          // 0x00c9ecb0
    void SetTimer(int v);                   // 0x00c9ee30
    void ConsumeTimer();                    // 0x00c9ee50
    void PlaySomething();                   // 0x00c9eea0
    bool HasBit2000();                      // 0x00c9eed0
    bool IsFlying();                        // 0x00c9eef0
};
void StringSprintf(cString_s00c9_de50* out, const char* fmt, ...);                  // 0x00472fe0
struct DefaultRefCounted {
    virtual ~DefaultRefCounted();           // +0x00 (scalar deleting destructor)
    int mnRefCount;                         // +0x04
};
// ---- items of slice s00c9de50 end

// @ 0x004e1c30
int GetTutorialToolPrice(PropertyHolder* pHolder, int key, int defaultValue)
{
    int value;
    int dummy;
    if (pHolder != 0 && pHolder->GetProperty(key, &value))
        return *(int*)ResolveIntValue(value);
    return defaultValue;
}

// @ 0x00c9cee0
void* cTribeTool_s00c9_c1b0::AsInterface(void* pIID)
{
    if ((int)pIID <= (int)g_13f94d4) {
        if (pIID == (void*)g_13f94d4) {
            if (this != 0)
                return mCombatant + (0x1e8 - 0x120);
            return 0;
        }
        if (pIID == (void*)0xe89adf71) {
            if (this != 0)
                return mCombatant + (0x120 - 0x120);
            return 0;
        }
        if (pIID != (void*)0x0116d858) {
            void* p = FUN_00b18460(pIID);
            if (p != 0)
                return p;
            return 0;
        }
        return this;
    }
    if (pIID == (void*)0x102a041a) {
        if (this != 0)
            return mSpatial + (0x108 - 0x34);
        return 0;
    }
    {
        void* p = FUN_00b18460(pIID);
        if (p != 0)
            return p;
    }
    return 0;
}

// @ 0x00c9cf70
bool cTribeToolData::IsNotType10()
{
    return mField14 != 10;
}

// @ 0x00c9cf90
void cTribeTool_s00c9_c1b0::AddStrikePoint(bool b)
{
    if (b) {
        mStrikeCount240++;
        mStrikeCount244++;
    } else {
        mStrikeCount240--;
        mStrikeCount244--;
    }
}

// @ 0x00c9cfd0
uint32_t cTribeTool_s00c9_c1b0::SpawnToolIcon()
{
    (void)0;
    int type = mDamageMdP2;                          // +0x1fc (tool type)
    cTribeToolData* data;
    if ((unsigned)(type - 1) <= 0xa)
        data = gTribeTools[type];
    else
        data = gTribeTools[0];
    float t = 1.0f - FUN_00bfc490(mCombatant);
    float v = t * (float)data->mField38;
    return FUN_011e0810(v * g_13f9428);
}

// @ 0x00c9d030
void cTribeTool_s00c9_c1b0::ReleaseToolIcon()
{
    IRefCounted* p = 0;
    if (PlanetModel_s00c9_c1b0() != 0)
        p = *(IRefCounted**)((uint8_t*)PlanetModel_s00c9_c1b0() + 0x24);
    if (p != 0 && mpField248 != 0) {
        void* vt = *(void**)p;
        ((void (*)(void*, int))(*(void**)((uint8_t*)vt + 0x58)))(mpField248, 1);
        mpField248 = 0;
    }
}

// @ 0x00c9d090
const char* cTribeTool_s00c9_c1b0::GetToolTypeAsCharStar()
{
    switch (mDamageMdP2) {                           // +0x1fc (tool type)
    case 1:  return "Torch Tool";
    case 2:  return "Axe Tool";
    case 3:  return "Spear Tool";
    case 4:  return "Recruiting Horn";
    case 5:  return "Recruiting Shakable Percussion Instrument";
    case 6:  return "Recruiting Didgeridoo";
    case 7:  return "Heal Tool";
    case 8:  return "Gather Tool";
    case 9:  return "Firepit - Throw Party $5";
    case 10: return "Fish Tool";
    default: return "";
    }
}

// @ 0x00c9d110
uint32_t cTribeTool_s00c9_c1b0::GetToolIconKey()
{
    uint32_t type = GetToolType();
    cTribeToolData* data;
    if ((unsigned)(type - 1) <= 0xa)
        data = gTribeTools[type];
    else
        data = gTribeTools[0];
    return (uint32_t)data->mField10;
}

// @ 0x00c9d160
float cTribeTool_s00c9_c1b0::GetTimeSinceCreation()
{
    if (mTimer200.IsRunning()) {
        unsigned long long t = mTimer200.GetElapsedTime();
        return (float)t * g_13f9428;
    }
    return g_14745d8;
}

// @ 0x00c9d1c0
float cTribeTool_s00c9_c1b0::GetTimeSinceLastUse()
{
    if (mTimer220.IsRunning()) {
        unsigned long long t = mTimer220.GetElapsedTime();
        return (float)t * g_13f9428;
    }
    return 0.0f;
}

// @ 0x00c9d230
cTribeTool::cTribeTool()
{
    gameData.Ctor();
    spatial.Ctor();
    interact.Ctor();
    combatant.Ctor();

    combatant.vftC8 = (void*)0x1466c14;
    spatial.vft     = (void*)0x14747c0;
    gameData.vft0   = (void*)0x1474758;
    gameData.vft1   = (void*)0x1474744;
    interact.vft    = (void*)0x1474728;
    combatant.vft   = (void*)0x14746c0;
    combatant.vftC8 = (void*)0x1474698;

    combatant.mCc   = 0.0f;
    combatant.mD0   = 0;
    combatant.mD4   = 0;
    combatant.mpOwner = 0;
    combatant.mDc   = 0;

    combatant.timer1.Ctor();
    combatant.timer2.Ctor();

    combatant.m120  = 0;
    combatant.m124  = 0;
    combatant.m128  = 0;
}

// @ 0x00c9d3b0
cTribeTool::~cTribeTool()
{
    gameData.vft0   = (void*)0x1474758;
    gameData.vft1   = (void*)0x1474744;
    spatial.vft     = (void*)0x14747c0;
    interact.vft    = (void*)0x1474728;
    combatant.vft   = (void*)0x14746c0;
    combatant.vftC8 = (void*)0x1474698;

    combatant.timer2.Dtor();
    combatant.timer1.Dtor();

    if (combatant.mpOwner)
        combatant.mpOwner->Release();

    combatant.vftC8 = (void*)0x1466c14;
    combatant.FUN_00bfcd00();
    interact.FUN_00ac0520();
    spatial.FUN_00c8a420();
    gameData.Dtor();
}

// @ 0x00c9d440
void cTribeTool::Init(DefObj* p)
{
    DefObj* old = combatant.mpOwner;
    if (p != old) {
        if (p)
            p->vf0();
        combatant.mpOwner = p;
        if (old)
            old->Release();
    }

    uint8_t      buf[16];
    void*        v  = ((cSpatialObjectV2*)&spatial)->vf2c((void*)0x1699a84);
    cPlanetModel* pm = ((PmBuf*)&buf)->Init(v);
    void*        r  = pm->BuildSurfaceOrientation2((void*)&buf, v);
    ((cSpatialObjectV2*)&spatial)->vf3c(r);

    if (combatant.mpOwner) {
        void* x = combatant.mpOwner->vf4c();
        ((cTribeToolV*)this)->vf48(x);
    }
}

// @ 0x00c9d4d0
void cTribeTool::FUN_00c9d4d0()
{
    if (combatant.mpOwner) {
        DefObj* t = combatant.mpOwner;
        combatant.mpOwner = 0;
        t->Release();
    }

    if (combatant.m128) {
        Worm* w = 0;
        if (PlanetModel())
            w = PlanetModel()->mp24;
        if (w && combatant.m128) {
            w->vf58((void*)combatant.m128, 1);
            combatant.m128 = 0;
        }
    }

    combatant.FUN_00bfc720();
    interact.FUN_00ac0450();

    if (gameData.mp2c) {
        void* t = gameData.mp2c;
        gameData.mp2c = 0;
        ((DefObj*)t)->Release();
    }

    spatial.FUN_00c8b2e0();
}

// @ 0x00c9d570
void cTribeTool::SetLocalExtents(uint32_t a, float b)
{
    SetLocalExtentsRaw(a, b);
    if (combatant.mDefObj)
        combatant.mDefObj->FUN_00c987b0(combatant.mDefID);
}

// @ 0x00c9d5b0
void cTribeTool::FUN_00c9d5b0(uint32_t p)
{
    gameData.IsDestroyed(p);
    ((cSPTimer*)&combatant.mCc)->Stop();

    int st = (int)combatant.mDefID;
    uint32_t tag;
    if (st >= 4 && (st <= 6 || st == 9))
        tag = 0x498ef2b;
    else
        tag = 0x498ef2a;

    uint8_t here[12];
    Found*  ebx = FUN_00b3d240();
    void*   r   = ((cTribeToolV*)this)->vf5c(here);
    void*   pos = ((cTribeToolV*)this)->vf2c();
    ebx->vf60(tag, pos, r);
}

// @ 0x00c9d670
void cTribeTool::FUN_00c9d670(float dmg, int a, uint32_t b, uint32_t c, void* d)
{
    if (combatant.mDc == 0xa)
        return;

    bool bl = combatant.m38 > *(float*)0x14745dc;

    combatant.TakeHit(dmg, a, b, c, d);

    if (GetCurrentGameMode() != 0x1654c02)
        return;
    if (!combatant.mpOwner)
        return;

    if (combatant.m38 > 0.0f) {
        if (a != -1) {
            ((DefObj3*)combatant.mpOwner)->vf4c(a, 0x530cf04, 1.0f);
        }
        if (!d)
            return;

        StimObj* so = (StimObj*)d;
        void*    ebx = so->vf08();
        void*    ea  = so->vf0c((void*)&combatant);
        (void)ea;
        (void)ebx;
    } else {
        if (!bl)
            return;
        if (a != -1) {
            ((DefObj3*)combatant.mpOwner)->vf4c(a, 0x530cf05, 1.0f);
        }

        combatant.timer2.Restart();

        long* vec = (long*)combatant.mpOwner->vf90();
        long* beg = (long*)*vec;
        long* end = (long*)*(vec + 1);
        for (long* it = beg; it != end; it += 1) {
            void* cit = (void*)*it;
            (void)cit;
        }
    }
}

// @ 0x00c9d9c0
bool cTribeTool::GetIsPlayerOwned()
{
    uint32_t owner = (uint32_t)combatant.mDefObj;
    return NounManager()->GetPlayerTribe() == owner;
}

// @ 0x00c9d9f0
void cTribeTool::GetCastID(int p)
{
    FUN_43c0(p);
    if (combatant.mDefObj)
        combatant.mDefObj->FUN_00c987b0(combatant.mDefID);
}

// @ 0x00c9da20
bool cTribeTool::Write(Stream* s)
{
    uint32_t tmp = 0x116d858;
    EA_WriteUint32(s->vf20()->vf18(), &tmp, 1, 0);

    bool ok;
    if (gameData.Write(s) && spatial.Write(s) && combatant.Write(s)) {
        if (s->vf2c(combatant.mpOwner))
            ok = true;
        else
            ok = false;
    }
    else
        ok = false;

    tmp = spatial.m98;
    EA_WriteUint32(s->vf20()->vf18(), &tmp, 1, 0);
    tmp = spatial.m90;
    EA_WriteUint32(s->vf20()->vf18(), &tmp, 1, 0);
    tmp = spatial.m94;
    EA_WriteUint32(s->vf20()->vf18(), &tmp, 1, 0);

    cVarListSerializer ser(this, (void*)0x157c5d0, 0x1a80d26);
    if (ok) {
        if (ser.Serialize(s))
            return true;
    }
    return false;
}

// @ 0x00c9db70
bool cTribeTool::Read(Stream* s)
{
    uint32_t tmp;
    EA_ReadInt32(s->vf20()->vf18(), &tmp, 1, 0);

    bool ok;
    if (gameData.Read(s) && spatial.Read(s) && combatant.Read(s)) {
        if (combatant.mpOwner) {
            DefObj* t = combatant.mpOwner;
            combatant.mpOwner = 0;
            t->Release();
        }
        if (s->vf28(0x4f396a66, &combatant.mpOwner, 0))
            ok = true;
        else
            ok = false;
    }
    else
        ok = false;

    EA_ReadInt32(s->vf20()->vf18(), &spatial.m98, 1, 0);
    EA_ReadInt32(s->vf20()->vf18(), &spatial.m90, 1, 0);
    EA_ReadInt32(s->vf20()->vf18(), &spatial.m94, 1, 0);

    cVarListSerializer ser(this, (void*)0x157c5d0, 0x1a80d26);
    if (ok) {
        if (ser.SerializeRead(s))
            return true;
    }
    return false;
}

// @ 0x00c9dd50
void cTribeTool::FUN_00c9dd50()
{
    Worm* w = PlanetModel()->mp24;
    if (!w)
        return;
    if (combatant.m128)
        return;

    LocExt* a = ((cSpatialObjectV*)&spatial)->vfac();
    if (!a)
        return;

    LocExt* bb = ((cSpatialObjectV*)&spatial)->vfac();
    if (!bb->mp90)
        return;

    uint8_t t[0x40];
    ((void**)t)[0] = 0;

    const Vec3* p = (const Vec3*)((cSpatialObjectV*)&spatial)->vf2c();
    (void)p;

    LocExt* cc = ((cSpatialObjectV*)&spatial)->vfac();
    w->vf54(t, cc->mp90);
    combatant.m128 = 1;
}

// @ 0x00c9de50
namespace SP {
bool cTribeTool_s00c9_de50::LoadTribeToolData()
{
    PropertyListPtr pList;
    if (!gTribeToolsLoaded) {
        IPropManager* pPropManager = PropertyManager();
        for (unsigned i = 0; i < 12; i++) {
            gTribeTools_s00c9_de50[i] = new("Simulator/cTribeToolData", 0, 0, 0, 0) cTribeToolData_s00c9_de50(cString_s00c9_de50());
        }
        UIntVector ids;
        PropertyManager()->GetPropertyListIDs(0x04292f52, ids);
        uint32_t* it = ids.mpBegin;
        uint32_t* end = ids.mpEnd;
        if (it == end)
            return false;
        for (; it != end; ++it) {
            uint32_t id = *it;
            if (!pPropManager->GetPropertyList(id, 0x04292f52, pList.AsParam()))
                return false;
            if (pList.mpObject->HasProperty(kPropTypeIndex) && pList.mpObject->HasProperty(kPropSubIndex)) {
                uint32_t typeIndex = *pList.mpObject->GetProperty(kPropTypeIndex)->GetValueUInt32();
                uint32_t subIndex = *pList.mpObject->GetProperty(kPropSubIndex)->GetValueUInt32();
                if (typeIndex - 1 <= 10) {
                    cTribeToolData_s00c9_de50* t = gTribeTools_s00c9_de50[typeIndex];
                    t->mListKey = pList.mpObject->mKey;
                    t->mTypeIndex = typeIndex;
                    t->mSubIndex = subIndex;
                    if (pList.mpObject->HasProperty(kPropKey))
                        t->mKey = *pList.mpObject->GetProperty(kPropKey)->GetKeyTPTR();
                    t->mKey.type = 0xb1b104;
                    t->mKey1 = t->mKey2 = t->mKey3 = t->mKey;
                    if (pList.mpObject->HasProperty(kPropKey1))
                        t->mKey1 = *pList.mpObject->GetProperty(kPropKey1)->GetKeyTPTR();
                    t->mKey1.type = 0xb1b104;
                    if (pList.mpObject->HasProperty(kPropKey2))
                        t->mKey2 = *pList.mpObject->GetProperty(kPropKey2)->GetKeyTPTR();
                    t->mKey2.type = 0xb1b104;
                    if (pList.mpObject->HasProperty(kPropKey3))
                        t->mKey3 = *pList.mpObject->GetProperty(kPropKey3)->GetKeyTPTR();
                    t->mKey3.type = 0xb1b104;
                    if (pList.mpObject->HasProperty(kPropFloat40))
                        t->mFloat40 = *pList.mpObject->GetProperty(kPropFloat40)->GetFloat();
                    t->m20 = TribeToolIntProperty(pList.mpObject, kPropField20, 0);
                    t->m28 = *pList.mpObject->GetProperty(kPropM28)->GetValueUInt32();
                    t->m2c = *pList.mpObject->GetProperty(kPropM2c)->GetValueUInt32();
                    t->m30 = *pList.mpObject->GetProperty(kPropM30)->GetValueUInt32();
                    t->m34 = *pList.mpObject->GetProperty(kPropM34)->GetValueUInt32();
                    t->m38 = *pList.mpObject->GetProperty(kPropM38)->GetValueInt32();
                    t->m3c = *pList.mpObject->GetProperty(kPropM3c)->GetValueInt32();
                    GetPropertyAsText(pList.mpObject, kPropText, &t->mText);
                    ResourceKey abilityKey = *pList.mpObject->GetProperty(kPropAbilityList)->GetValueKey();
                    PropertyListPtr pAbilityList;
                    if (pPropManager->GetPropertyList(abilityKey.instance, abilityKey.group, &pAbilityList.mpObject)) {
                        AbilityRef ability(new("Simulator/cCreatureAbility", 0, 0, 0, 0) cCreatureAbility_s00c9_de50());
                        ReadAbilityData(ability.mpObject, pAbilityList.mpObject);
                        t->mAbility = *(DefaultRefCountedPtr*)&ability;
                    }
                }
            }
        }
    }
    gTribeToolsLoaded = true;
    return true;
}
}  // namespace SP

// @ 0x00c9e530
void DestroyTribeToolData()
{
    if (!gTribeToolsLoaded)
        return;
    for (unsigned i = 0; i < 12; ++i) {
        cTribeToolData_s00c9_de50* pTool = gTribeTools_s00c9_de50[i];
        if (pTool) {
            pTool->mText.~cString_s00c9_de50();
            DefaultRefCounted* pAbility = pTool->mAbility.mpObject;
            if (pAbility) {
                int refs = pAbility->mnRefCount;
                --refs;
                pAbility->mnRefCount = refs;
                if (refs == 0) {
                    pAbility->mnRefCount = 1;
                    delete pAbility;
                }
            }
            EASTL_allocator_deallocate(pTool);
        }
        gTribeTools_s00c9_de50[i] = 0;
    }
    gTribeToolsLoaded = false;
}

// @ 0x00c9e5a0
void cLoco::FormatName(cString_s00c9_de50* out)
{
    // mLoco sits at +0x34 of the complete vehicle object.
    cVehicle_s00c9_de50* pOwner = (cVehicle_s00c9_de50*)((char*)this - 0x34);
    StringSprintf(out, kNameFormat, pOwner->Slot5c());
}
