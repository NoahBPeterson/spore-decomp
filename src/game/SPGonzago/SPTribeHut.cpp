// src/game/SPGonzago/SPTribeHut.cpp -- migrated from slice(s) s00c9c1b0, s00c9afb0, s01355f90, s005718f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeHut.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <new>
#include <string.h>
#include <math.h>
#include <intrin.h>
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cCombatant.h"
#include "SP/cGameData.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cInteractionTarget.h"
#include "SP/cSPTimer.h"
#include "SP/cSpatialObject.h"
#include "SP/cTribeHut.h"
#include "SP/cVarListSerializer.h"
#include "SP/cCommunity.h"
#include "SP/cRelationshipManager.h"
#include "SP/cSPCreatureCitizen.h"

// ---- items of slice s005718f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
namespace EA {
namespace Audio {
struct SystemAT {
    PV8 PV4 PV2
    virtual void BeginMessage(uint32_t id);                 // +0x38
    virtual void SetFloat(uint32_t id, float v);            // +0x3c
    virtual void SetInt(uint32_t id, uint32_t v);           // +0x40
    virtual void pv41();
    virtual void pv42();
    virtual void SetString(uint32_t id, const char* s, uint32_t len);   // +0x4c
    virtual void pv44();
    virtual void pv45();
    virtual void SendMessage();                             // +0x58
};
}
}
namespace EA {
namespace Audio {
SystemAT* __cdecl GetSystemAT();
}
}
// ---- items of slice s005718f0 end

// ---- items of slice s01355f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void E209_1_24();   // 0x00aca090
extern void E209_1_28();   // 0x00bca960
extern void E209_1_2C();   // 0x00c2e4e0
extern void E209_1_30();   // 0x00692fb0
extern void E209_1_34();   // 0x00b6f550
extern void E209_1_38();   // 0x00ac8050
extern void E209_2_24();   // 0x00ae3430
extern void E209_2_28();   // 0x00ae3450
extern void E209_2_2C();   // 0x00693150
extern void E209_2_30();   // 0x00695080
extern void E209_3_24();   // 0x00ae3430
extern void E209_3_28();   // 0x00ae3450
extern void E209_3_2C();   // 0x00693150
extern void E209_3_30();   // 0x00695080
extern void E209_4_24();   // 0x00ae3430
extern void E209_4_28();   // 0x00ae3450
extern void E209_4_2C();   // 0x00693150
extern void E209_4_30();   // 0x00695080
extern void E209_5_24();   // 0x00ae3430
extern void E209_5_28();   // 0x00ae3450
extern void E209_5_2C();   // 0x00693150
extern void E209_5_30();   // 0x00695080
extern void E209_F34();    // 0x00b1fbf0
extern void E209_F38();    // 0x00ae5720
extern void E209_6_24();   // 0x00bd0cb0
extern void E209_6_28();   // 0x00bca960
extern void E209_6_2C();   // 0x00c2e4e0
extern void E209_6_30();   // 0x00692fb0
extern void E209_6_34();   // 0x00b6f550
extern void E209_6_38();   // 0x00ac8050
typedef unsigned int   u32;
struct PropDesc {
    const char* mName;    // +0x00
    u32 mHash;            // +0x04
    u32 mType;            // +0x08
    u32 mPad0C;           // +0x0c
    u32 mPad10;           // +0x10
    u32 mPad14;           // +0x14
    u32 mZero18;          // +0x18
    u32 mZero1C;          // +0x1c
    void* mDefault;       // +0x20
    void* mFn24;          // +0x24
    void* mFn28;          // +0x28
    void* mFn2C;          // +0x2c
    void* mFn30;          // +0x30
    void* mFn34;          // +0x34
    void* mFn38;          // +0x38
};
// ---- items of slice s01355f90 end

// ---- items of slice s00c9afb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t g_TribeGameMode;                                  // 0x01654c02
extern void* g_01699998;                                         // 0x01699998
extern void* g_TribeCullExtents;                                 // 0x0157c3b4
struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
struct PlanetModelT {
    int     ClassifyPoint(const Vector3* dir);                               // 0x00b82fc0 (ret 4)
    Vector3 SurfacePoint(const Vector3& dir);                                // 0x00b81630 (ret 8, sret)
    bool    IsWaterPoint(const Vector3* pos);                                // 0x00b7e3e0 (ret 4)
    Quaternion BuildSurfaceOrientation(const Vector3& pos);                  // 0x00b7f190 (ret 4, sret)
};
PlanetModelT* __cdecl PlanetModel();                                         // 0x00b3d350
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
struct SimSerializable {
    virtual void  w00();
    virtual void  w04();
    virtual void  w08();
    virtual void  w0c();
};
struct cGameData : RefCounted, SimSerializable {
    cGameData();                                        // 0x00b18660
    ~cGameData();                                       // 0x00b184c0
    bool  IsDestroyed(void* ctx);                       // 0x00bfd0d0
    bool  Write(void* io);                              // 0x00b18590
    void  SetGameDataOwner2(void* owner);               // 0x00b18550
    void* Cast(int type);                               // 0x00b18460
    void  Func80();                                     // 0x00c88510
    void  TribalEvent(int arg);                         // 0x00c9be90
    char  mData[0x34 - 8];
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
struct cSpatialObject {
    virtual void s00();
    cSpatialObject();                                   // 0x00c89630
    ~cSpatialObject();                                  // 0x00c8a420
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
struct cInteractionTarget {
    virtual void i00();
    cInteractionTarget();                               // 0x00ac03d0
    ~cInteractionTarget();                              // 0x00ac0520
    void* Cast(int type);                               // 0x00ac0320
    char  mData[0x14];
};
struct cCombatant {
    virtual void c00();
    cCombatant();                                       // 0x00bfd4e0
    ~cCombatant();                                      // 0x00bfcd00
    void* Cast(int type);                               // 0x00bfc380
    float mf04;                                         // +0x004 (abs +0x124)
    char  mData[0xc0];
};
template <class T>
struct RefPtr {
    T* p;
    RefPtr() : p(0) {}
    ~RefPtr() { if (p) ((RefCounted*)p)->Release(); }
};
struct cGonzagoTimer {
    cGonzagoTimer();                                    // 0x00b63890
    ~cGonzagoTimer();                                   // 0x00b638b0
    char mData[0x10];
};
struct cTribeHut : cGameData, cSpatialObject, cInteractionTarget, cCombatant {
    cTribeHut();                                        // 0x00c9bf90
    virtual ~cTribeHut();                               // 0x00c9c120
    void* Cast(int type);                               // 0x00c9bdf0
    void  SetRefCountDelta(char on);                    // 0x00c9bef0
    void  UpdateEmpireColor();                          // 0x00c9bf30

    void* mpModel1e8;                                   // +0x1e8
    void* mpModel1ec;                                   // +0x1ec
    void* mpModel1f0;                                   // +0x1f0
    void* mpModel1f4;                                   // +0x1f4
    void* mpModel1f8;                                   // +0x1f8
    void* mpModel1fc;                                   // +0x1fc
    void* mpModel200;                                   // +0x200
    void* mpModel204;                                   // +0x204
    void* mpModel208;                                   // +0x208
    void* mpModel20c;                                   // +0x20c
    void* mpModel210;                                   // +0x210
    void* mpModel214;                                   // +0x214
    bool  mFlag218;                                     // +0x218
    char  mPad219[3];
    void* mp218;                                        // +0x21c
    bool  mFlag220;                                     // +0x220
    bool  mFlag221;                                     // +0x221
    char  mPad222[2];
    char  mPad224[4];
    void* mp228;                                        // +0x228
    void* mp22c;                                        // +0x22c
    RefPtr<RefCounted> mpTribe230;                      // +0x230
    RefPtr<RefCounted> mpHitSphere234;                  // +0x234
    int   mRef238;                                      // +0x238
    char  mPad23c[4];
    cGonzagoTimer mTimer;                               // +0x240
};
struct EventMgr {
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
virtual void h54();
virtual void h58();
virtual void h5c();
    virtual void h60(int id, void* a, void* b);                   // +0x60
};
void* __cdecl GetCurrentGameMode();                              // 0x00b5b800
EventMgr* __cdecl FUN_00b3d240();                                // 0x00b3d240
int   __stdcall GetPlayerEmpireID(int a, void* b, int c);       // 0x01021090
// ---- items of slice s00c9afb0 end

// ---- items of slice s00c9c1b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint32_t kHutDamageHi;                  // 0157c3a0
extern const uint32_t kHutDamageMd;                  // 0157c39c
extern const uint32_t kHutDamageLo;                  // 0157c398
extern const uint32_t kGameModeHut;                  // 01654c04
extern const uint32_t kGameMode1654c02;              // 01654c02
extern const uint32_t kGameMode1654c05;              // 01654c05
namespace EA {
namespace IO {
    void WriteUint32(void* pStream, const void* pData, int count, int flags);  // 0093aa70
}
}
namespace EA {
namespace IO {
    void ReadInt32(void* pStream, const void* pData, int count, int flags);    // 0093a780
}
}
struct IRefCounted {
    virtual void AddRef();                           // +0x00
    virtual void Release();                          // +0x04
};
struct ResourceKey {
    uint32_t instance, type, group;
};
struct Property {
    void*    mpData;                                 // +0x00
    uint32_t pad04[3];
    uint16_t mnFlags;                                // +0x10
    uint16_t mnType;                                 // +0x12
    void* GetValuePtr()
    {
        if (mnFlags & 0x30)
            return mpData;
        if (mnType != 0)
            return this;
        return 0;
    }
};
struct PropertyList {
    virtual int AddRef();                            // +0x00
    virtual int Release();                           // +0x04
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual bool HasProperty(uint32_t id);           // +0x1c
virtual void v8();
virtual void v9();
    virtual Property* GetProperty(uint32_t id);      // +0x28
};
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
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppOut); // +0x2c
};
struct cVarListSerializer {
    uint8_t pad00[0xa10];
    cVarListSerializer(void* owner, const void* key, uint32_t group);          // 00692f90
    bool Serialize(void* pStream);                                              // 00692900
    bool Read(void* pStream);                                                   // 00693e10
};
struct IStreamWriter {
virtual void w00();
virtual void w01();
virtual void w02();
virtual void w03();
virtual void w04();
virtual void w05();
    virtual void* GetWriter();                       // +0x18
};
struct ISerializerStream {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
    virtual IStreamWriter* GetWriterSerializer();    // +0x20
};
struct cGameDataBase {
    bool Write(void* pStream);                       // 00b18590
    bool Read(void* pStream);                        // 00b18600
};
struct cSpatialObjectBase {
    bool Write(void* pStream);                       // 00c88a90
    bool Read(void* pStream);                        // 00c88b00
};
struct cCombatantBase {
    bool Write(void* pStream);                       // 00bfc4a0
    bool Read(void* pStream);                        // 00bfc540
};
struct ISpatialRef {
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
virtual void s0a();
    virtual void* v2c();                             // +0x2c
virtual void s0c();
virtual void s0d();
    virtual void  v38(void* arg);                    // +0x38
virtual void s0f();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s1a();
virtual void s1b();
virtual void s1c();
virtual void s1d();
virtual void s1e();
virtual void s1f();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
    virtual const ResourceKey* GetModelKey();        // +0x98
};
struct cSPTimer {
    uint8_t pad00[0x10];
    bool  IsRunning();                                                          // 00feba90
    unsigned long long GetElapsedTime();                                        // 00bc3190
};
extern const ResourceKey gDefaultResourceKey;        // 01699a04 (default position)
extern ResourceKey gSerializableKey;                 // 0157c3d0
float   FUN_00bfc490(void* p);                      // 00bfc490
void  FUN_00bfc720(void* p);                         // 00bfc720
void  FUN_00c3f2d0(void* p);                         // 00c3f2d0
void* FUN_00ac0450(void* p);                         // 00ac0450
void  FUN_00c8b2e0(void* p);                         // 00c8b2e0
void  FUN_00c987b0(void);                            // 00c987b0
void  FUN_00c3f160(void* pObj, int id);              // 00c3f160  SetEffectId
void* FUN_0059aed0(void* pOut, const void* pKey, void* pIn);  // 0059aed0
bool  FUN_0059ab70(const void* p);                   // 0059ab70
void* NounManager();                                 // 00b3d300
void* PlanetModel_s00c9_c1b0();                                 // 00b3d350
void* PropertyManager();                             // 0067de30
struct cGameNounManager {
    void* CreateNoun(const void* key);               // 00b20c60
    void  RemoveNoun(void* pNoun);                   // 00b225d0
};
struct cCommunity {
    void func54h(int arg);                           // 00c88670
};
class cTribeTool {
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
    virtual uint32_t GetToolType();                  // +0x58
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
            cSPTimer mTimer200;                      // +0x200  (creation timer)
            uint8_t  pad210[0x220 - 0x210];
        };
    };
    cSPTimer mTimer220;                              // +0x220  (last-use timer)
    void*    mpNoun;                                 // +0x230
    void*    mpOwner234;                             // +0x234
    uint8_t  pad238[0x240 - 0x238];
    int      mStrikeCount240;                        // +0x240
    int      mStrikeCount244;                        // +0x244
    void*    mpField248;                             // +0x248

    // --- methods
    void  RemoveOwner();                             // 00c9c1b0
    void  SetOwnerIface(void* p);                    // 00c9c250
    bool  Serialize_Write(void* pStream);            // 00c9c310
    bool  Serialize_Read(void* pStream);             // 00c9c3c0
    void  SetupTribeHut(int arg);                    // 00c9c500
    uint32_t GetToolPosition(void* pOut);            // 00c9c5e0
    bool  HasToolNoun();                             // 00c9c2e0
    void  RefreshModelProps();                       // 00c9c680
    void* AsInterface(void* pIID);                   // 00c9cee0
    void  AddStrikePoint(bool b);                    // 00c9cf90
    uint32_t SpawnToolIcon();                        // 00c9cfd0
    void  ReleaseToolIcon();                         // 00c9d030
    const char* GetToolTypeAsCharStar();             // 00c9d090
    uint32_t GetToolIconKey();                       // 00c9d110
    float GetTimeSinceCreation();                    // 00c9d160
    float GetTimeSinceLastUse();                     // 00c9d1c0
};
struct cToolNounSpawner {
virtual void n00();
virtual void n01();
virtual void n02();
virtual void n03();
virtual void n04();
virtual void n05();
virtual void n06();
virtual void n07();
virtual void n08();
virtual void n09();
virtual void n0a();
virtual void n0b();
virtual void n0c();
virtual void n0d();
virtual void n0e();
virtual void n0f();
virtual void n10();
virtual void n11();
virtual void n12();
virtual void n13();
virtual void n14();
virtual void n15();
virtual void n16();
virtual void n17();
virtual void n18();
virtual void n19();
virtual void n1a();
virtual void n1b();
virtual void n1c();
virtual void n1d();
virtual void n1e();
virtual void n1f();
virtual void n20();
virtual void n21();
virtual void n22();
virtual void n23();
virtual void n24();
virtual void n25();
virtual void n26();
virtual void n27();
virtual void n28();
virtual void n29();
virtual void n2a();
virtual void n2b();
virtual void n2c();
virtual void n2d();
virtual void n2e();
virtual uint32_t GetOwnerNoun();
};
struct cByteBuffer {
    uint8_t* mpBegin;                                // +0x00
    uint8_t* mpEnd;                                  // +0x04
};
struct HutVec3 { float x, y, z; };
struct HutQuat { float x, y, z, w; };
struct HutMat33 { float m[9]; };
struct IHutSpatial {
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
virtual void s0a();
    virtual HutVec3* GetPosition();                  // +0x2c
    virtual HutQuat* GetOrientation();               // +0x30
virtual void s0d();
virtual void s0e();
virtual void s0f();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s1a();
virtual void s1b();
virtual void s1c();
    virtual float    GetRadius();                    // +0x74
virtual void s1e();
virtual void s1f();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
    virtual HutVec3* GetWorldPosition();             // +0x98
};
struct cHutCombatant {
    uint8_t mPad00[0x34];
    int     mnFlag34;                                // hut+0x154  knocked-out flag
    float   mfField38;                               // hut+0x158  0 while intact
    uint8_t mPad3c[0x110 - 0x3c];
};
struct IHutNoun {
virtual void n00();
virtual void n01();
virtual void n02();
virtual void n03();
virtual void n04();
virtual void n05();
virtual void n06();
virtual void n07();
virtual void n08();
virtual void n09();
virtual void n0a();
virtual void n0b();
virtual void n0c();
virtual void n0d();
virtual void n0e();
virtual void n0f();
virtual void n10();
virtual void n11();
virtual void n12();
    virtual uint32_t HandleHit(int nSource, uint32_t nTag, float fScale);  // +0x4c
virtual void n14();
virtual void n15();
virtual void n16();
virtual void n17();
virtual void n18();
virtual void n19();
virtual void n1a();
virtual void n1b();
virtual void n1c();
virtual void n1d();
virtual void n1e();
virtual void n1f();
virtual void n20();
virtual void n21();
virtual void n22();
virtual void n23();
    virtual void* GetCitizenList();                  // +0x90
};
struct HutCitizenList {
    void** mpBegin;                                  // +0x00
    void** mpEnd;                                    // +0x04
};
struct IHutCitizenTarget {
virtual void c00();
virtual void c01();
virtual void c02();
virtual void c03();
virtual void c04();
virtual void c05();
virtual void c06();
virtual void c07();
virtual void c08();
virtual void c09();
virtual void c0a();
virtual void c0b();
virtual void c0c();
virtual void c0d();
virtual void c0e();
virtual void c0f();
virtual void c10();
virtual void c11();
virtual void c12();
virtual void c13();
virtual void c14();
virtual void c15();
    virtual bool IsEngaged();                        // +0x58
};
struct IHutCitizen {
virtual void c00();
virtual void c01();
virtual void c02();
virtual void c03();
virtual void c04();
virtual void c05();
virtual void c06();
virtual void c07();
virtual void c08();
virtual void c09();
virtual void c0a();
    virtual HutVec3* GetPosition();                  // +0x2c
virtual void c0c();
virtual void c0d();
virtual void c0e();
virtual void c0f();
virtual void c10();
virtual void c11();
virtual void c12();
virtual void c13();
virtual void c14();
virtual void c15();
virtual void c16();
virtual void c17();
virtual void c18();
virtual void c19();
virtual void c1a();
virtual void c1b();
    virtual void c1c();
    virtual float GetRadius();                       // +0x74
virtual void c1e();
virtual void c1f();
virtual void c20();
virtual void c21();
virtual void c22();
virtual void c23();
virtual void c24();
virtual void c25();

    uint8_t           mPad04[0xc0 - 0x04];
    IHutCitizenTarget mHitTarget;                    // +0xc0
    uint8_t           mPadC4[0xb4c - 0xc4];
    void*             mpBehaviorTree;                // +0xb4c
};
struct IHutInteractor {
    virtual void  i00();
    virtual void  Release();                         // +0x04
    virtual void* GetProbe();                        // +0x08
    virtual void* AttachTo(void* pOwner);            // +0x0c
virtual void  i04();
virtual void i05();
virtual void i06();
virtual void i07();
virtual void  i08();
virtual void i09();
virtual void i0a();
virtual void i0b();
virtual void  i0c();
virtual void i0d();
virtual void i0e();
virtual void i0f();
virtual void  i10();
virtual void i11();
virtual void i12();
virtual void i13();
virtual void  i14();
virtual void i15();
virtual void i16();
    virtual void* GetKey(uint32_t nKey);             // +0x5c
};
struct HutXformMsg;
struct IHutEffect {
    virtual void e00();
    virtual void Release();                          // +0x04
    virtual void e02();                              // +0x08
virtual void e03();
virtual void e04();
virtual void e05();
    virtual void Send(HutXformMsg* pMsg);            // +0x18
virtual void e07();
virtual void e08();
virtual void e09();
virtual void e0a();
virtual void e0b();
virtual void e0c();
virtual void e0d();
virtual void e0e();
virtual void e0f();
virtual void e10();
virtual void e11();
    virtual void SetTransform(int nKind, const HutVec3* pPos, int nArg);  // +0x48
};
struct IHutEffects {
virtual void f00();
virtual void f01();
virtual void f02();
virtual void f03();
virtual void f04();
virtual void f05();
virtual void f06();
virtual void f07();
virtual void f08();
virtual void f09();
virtual void f0a();
    virtual bool CreateEffect(uint32_t nKey, void* pArg, void** ppOut);   // +0x2c
};
struct IHutMessageServer {
virtual void m00();
virtual void m01();
virtual void m02();
virtual void m03();
virtual void m04();
    virtual void Send(uint32_t nTag, void* pMsg, void* pArg);              // +0x14
};
struct HutMessage {
    void*    mpVtable;                               // +0x00
    uint8_t  mPad04[0x04];
    void*    mpRefs[6];                              // +0x08 (three pairs)
    uint8_t  mPad20[0x10];
    uint32_t mnTag;                                  // +0x30
    uint8_t  mPad34[0x04];
    uint32_t mnMask;                                 // +0x38
    uint8_t  mPad3c[0x04];
    uint32_t mnField40;                              // +0x40

    void SetIRefCount(int nIndex, void* pValue);     // 005726e0
    void Destruct();                                 // 00421cf0
};
struct HutXformMsg {
    uint16_t mFlags00;                               // +0x00
    uint16_t mCount02;                               // +0x02
    HutVec3  mPosition;                              // +0x04
    uint16_t mFlags08;                               // +0x08
    uint16_t mCount0a;                               // +0x0a
    uint8_t  mPad0c[0x10];
    HutMat33 mMatrix;                                // +0x1c
};
struct cRelationshipManager {
    float RecordEvent(uint32_t nEvent, int nSource, uint32_t nTag, float fValue);  // 00d06240
};
struct cSPCreatureCitizen {
    uint32_t GetTribe();                             // 00c22f50
};
static void* const kMsgVtable  = (void*)0x013eb844;
static const void* const kCitizenKey = (const void*)0x018eb4b7;
void __fastcall Combatant_TakeHit(void* pCombatant, int nFlags, float fDamage,
                                  void* pSource, int nType, void* pArg4,
                                  void* pArg5);      // 00bfcdd0
void        FUN_00c8e720(int nId);                                   // 00c8e720
void*       FUN_00b26930(void* pNoun);                               // 00b26930
bool        FUN_00ae3d40(void* pObj);                                // 00ae3d40
void*       EffectsManager();                                        // 0067ddd0
void*       MessageServer();                                         // 0067dcc0
void*       RelationshipManager();                                   // 00b3d2c0
void*       FUN_00ac80d0(void* pObj, const void* pKey);               // 00ac80d0
void*       FUN_00bc8000(uint32_t nKey, void* pArg);                  // 00bc8000
void*       FUN_00bc8400(void* pThis);                                // 00bc8400
void        FUN_00bc97f0(void* pStimuli, unsigned long long nFlags,
                         float fValue, void* pTarget);                // 00bc97f0
bool        FUN_00c11480(void* pCreature, void* pPos, float fRange,
                         float fScale);                               // 00c11480
bool        FUN_00c0d560(void* pCreature, void* pArg, float fA,
                         float fB);                                   // 00c0d560
void*       GetActivePlanet();                                        // 01021260
void*       FUN_00c8ea40(void* pNoun);                                // 00c8ea40
void        FUN_00c71370(void* pPlanet, void* pObj);                  // 00c71370
int         FUN_00c70e00(void* pPlanet);                              // 00c70e00
void*       FUN_00c71120(void* pPlanet);                              // 00c71120
void        FUN_00c70de0(void* pPlanet, int nMode);                   // 00c70de0
HutMat33*   Matrix3FromQuaternion(HutMat33* pOut, const HutQuat* pQuat); // 0059c190
void        XformMsg_ctor(void* pThis);                               // 00434040
struct cTribeHut_s00c9_c1b0 {
    uint32_t      mPad00[13];                        // +0x000
    IHutSpatial   mSpatial;                          // +0x034
    uint8_t       mPad38[0x120 - 0x38];
    cHutCombatant mCombatant;                        // +0x120
    IHutNoun*     mpNoun;                            // +0x230

    void TakeHit(float fDamage, int nSource, uint32_t nParam3,
                 uint32_t nParam4, IHutInteractor* pInteract);   // 00c9c8a0
};
// ---- items of slice s00c9c1b0 end

// @ 0x00571f80
void __cdecl Start3dSoundByName(uint32_t soundId, uint32_t objectId, float x, float y, float z)
{
    EA::Audio::SystemAT* sys = EA::Audio::GetSystemAT();
    if (sys) {
        sys->BeginMessage(0x3475365);
        sys->SetInt(0x3475381, soundId);
        sys->SetInt(0x3475385, objectId);
        sys->SetFloat(0x3475391, x);
        sys->SetFloat(0x3475395, y);
        sys->SetFloat(0x3475398, z);
        sys->SendMessage();
    }
}

// @ 0x00c9be90
void cGameData::TribalEvent(int arg)
{
    IsDestroyed((void*)arg);
    char local[12];
    FUN_00b3d240()->h60(0x498ef27,
        ((RefCounted*)((char*)this - 0xec))->GetPosition(),
        ((RefCounted*)((char*)this - 0xec))->v5c(local));
}

// @ 0x00c9bef0
void cTribeHut::SetRefCountDelta(char on)
{
    if (on)
        ++mRef238;
    else
        --mRef238;
}

// @ 0x00c9bf30
void cTribeHut::UpdateEmpireColor()
{
    cGameData::Func80();
    if (GetCurrentGameMode() == &g_TribeGameMode)
        return;
    const Vector3* pos = (const Vector3*)GetPosition();
    if (!PlanetModel()->IsWaterPoint(pos))
        return;
    mSub.k18(mf04, GetPlayerEmpireID(0, &g_01699998, 0));
}

// @ 0x00c9bf90
cTribeHut::cTribeHut()
: mpModel1e8(0), mpModel1ec(0), mpModel1f0(0), mpModel1f4(0),
      mpModel1f8(0), mpModel1fc(0), mpModel200(0), mpModel204(0),
      mpModel208(0), mpModel20c(0), mpModel210(0), mpModel214(0),
      mFlag218(false), mp218(0), mFlag220(false), mFlag221(false),
      mp228(0), mp22c(0), mRef238(0)
{
    ((cSpatialObject*)this)->func58h(&g_TribeCullExtents);
}

// @ 0x00c9c120
cTribeHut::~cTribeHut()
{
}

// @ 0x00c9c1b0
void cTribeTool::RemoveOwner()
{
    if (mpNoun != 0) {
        IRefCounted* p = (IRefCounted*)mpNoun;
        mpNoun = 0;
        p->Release();
    }
    FUN_00bfc720(mCombatant);
    if (mpOwner234 != 0) {
        FUN_00c3f2d0(0);
        ((cGameNounManager*)NounManager())->RemoveNoun(mpOwner234);
        void* p = mpOwner234;
        mpOwner234 = 0;
        if (p != 0)
            ((IRefCounted*)p)->Release();
    }
    if (mpOwner2C != 0) {
        IRefCounted* p = mpOwner2C;
        mpOwner2C = 0;
        p->Release();
    }
    FUN_00ac0450(mSpatial + (0x108 - 0x34));
    FUN_00c8b2e0(mSpatial);
}

// @ 0x00c9c250
void cTribeTool::SetOwnerIface(void* p)
{
    void* old = mpNoun;
    if (p != old) {
        if (p != 0)
            ((IRefCounted*)p)->AddRef();
        mpNoun = p;
        if (old != 0)
            ((IRefCounted*)old)->Release();
    }
    if (mpNoun != 0) {
        SetOwnerKey(((cTribeTool*)mpNoun)->GetOwnerKey());
    }
}

// @ 0x00c9c2c0
void __stdcall FUN_00c9c2c0(cByteBuffer* pBuf)
{
    if (pBuf->mpBegin != pBuf->mpEnd) {
        *pBuf->mpBegin = 0;
        pBuf->mpEnd = pBuf->mpBegin;
    }
}

// @ 0x00c9c2e0
bool cTribeTool::HasToolNoun()
{
    if (mDamageMdP2 == 0)                            // +0x1fc (tool type)
        return false;
    cToolNounSpawner* spawner = (cToolNounSpawner*)((uint8_t*)this - 0x34);
    uint32_t noun = spawner->GetOwnerNoun();         // vtable +0x5c
    return ((cTribeTool*)noun)->GetToolType() != 0;  // vtable +0x58 on noun+0x120
}

// @ 0x00c9c310
bool cTribeTool::Serialize_Write(void* pStream)
{
    IStreamWriter* pWriter = ((ISerializerStream*)pStream)->GetWriterSerializer();
    uint32_t version = 0xee02c7;
    void* pIO = pWriter->GetWriter();
    EA::IO::WriteUint32(pIO, &version, 1, 0);
    bool ok = ((cGameDataBase*)this)->Write(pStream)
           && ((cSpatialObjectBase*)mSpatial)->Write(pStream)
           && ((cCombatantBase*)mCombatant)->Write(pStream);
    cVarListSerializer vs(this, &gSerializableKey, 0x1a80d26);
    if (ok) {
        if (vs.Serialize(pStream))
            return true;
    }
    return false;
}

// @ 0x00c9c3c0
bool cTribeTool::Serialize_Read(void* pStream)
{
    IStreamWriter* pWriter = ((ISerializerStream*)pStream)->GetWriterSerializer();
    void* pIO = pWriter->GetWriter();
    uint32_t version = 0;
    EA::IO::ReadInt32(pIO, &version, 1, 0);
    bool ok = ((cGameDataBase*)this)->Read(pStream)
           && ((cSpatialObjectBase*)mSpatial)->Read(pStream)
           && ((cCombatantBase*)mCombatant)->Read(pStream);
    cVarListSerializer vs(this, &gSerializableKey, 0x1a80d26);
    if (ok) {
        if (vs.Read(pStream)) {
            ok = true;
            goto done;
        }
    }
    ok = false;
done:
    {
        void* pm = PlanetModel_s00c9_c1b0();
        if (*(void**)((uint8_t*)pm + 0x24) != 0) {
            ISpatialRef* pSpatial = (ISpatialRef*)mSpatial;
            pSpatial->v38(pSpatial->v2c());
        }
    }
    return ok;
}

// @ 0x00c9c500
void cTribeTool::SetupTribeHut(int arg)
{
    if (GetCurrentGameMode() == &kGameModeHut && mStrikeCount240 == 0) {
        void* pNoun = ((cGameNounManager*)NounManager())->CreateNoun((const void*)0x2e72cae);
        void* pHut = 0;
        if (pNoun != 0)
            pHut = (void*)((void* (*)(void*, int))(*(void**)((uint8_t*)*(void**)pNoun + 0xc)))(pNoun, 0x2e71a5a);
        mpNoun = pHut;
        if (mpNoun != 0)
            FUN_00c3f2d0(mSpatial);
    }
    ((cCommunity*)this)->func54h(arg);
    if (GetCurrentGameMode() == &kGameModeHut) {
        FUN_00c3f160(mpNoun, 0);
    }
    if (mDamageMdP2 != 0) {
        FUN_00c987b0();
    }
}

// @ 0x00c9c5e0
uint32_t cTribeTool::GetToolPosition(void* pOut)
{
    uint32_t key = GetPositionKey();                 // vtable +0x30
    (void)key;
    float v[3];
    float* p = (float*)FUN_0059aed0(&v[0], &gDefaultResourceKey, (void*)key);
    v[0] = p[0]; v[1] = p[1]; v[2] = p[2];
    float* dst = (float*)pOut;
    if (FUN_0059ab70(&v[0])) {
        dst[0] = v[0]; dst[1] = v[1]; dst[2] = v[2];
    } else {
        dst[0] = ((const float*)&gDefaultResourceKey)[0];
        dst[1] = ((const float*)&gDefaultResourceKey)[1];
        dst[2] = ((const float*)&gDefaultResourceKey)[2];
    }
    return 0;
}

// @ 0x00c9c680
void cTribeTool::RefreshModelProps()
{
    const ResourceKey* pKey = ((ISpatialRef*)mSpatial)->GetModelKey();  // vtable +0x98
    uint32_t key0 = ((const uint32_t*)pKey)[0];
    uint32_t key1 = ((const uint32_t*)pKey)[1];
    uint32_t key2 = ((const uint32_t*)pKey)[2];
    mDamageLo  = key0; mDamageMd  = key0; mDamageHi  = key0; mDamageHiQ1 = key0;
    mDamageLoP1 = key1; mDamageMdP1 = key1; mDamageHiP1 = key1; mDamageHiQ2 = key1;
    mDamageLoP2 = key2; mDamageMdP2 = key2; mDamageHiP2 = key2; mDamageHiQ3 = key2;

    PropertyList* pList = 0;
    IPropManager* pm = (IPropManager*)PropertyManager();
    if (!pm->GetPropertyList(key0, key2, &pList))
        goto done;

    if (pList->HasProperty(kHutDamageHi)) {
        Property* p = pList->GetProperty(kHutDamageHi);
        uint32_t* v = (uint32_t*)p->GetValuePtr();
        mDamageLo = v[0]; mDamageLoP1 = v[1]; mDamageLoP1 = 0xb1b104; mDamageLoP2 = 0x2be764e2;
    }
    if (pList->HasProperty(kHutDamageMd)) {
        Property* p = pList->GetProperty(kHutDamageMd);
        uint32_t* v = (uint32_t*)p->GetValuePtr();
        mDamageMd = v[0]; mDamageMdP1 = v[1]; mDamageMdP1 = 0xb1b104; mDamageMdP2 = 0x2be764e2;
    }
    if (pList->HasProperty(kHutDamageLo)) {
        Property* p = pList->GetProperty(kHutDamageLo);
        uint32_t* v = (uint32_t*)p->GetValuePtr();
        mDamageHi = v[0]; mDamageHiP1 = v[1]; mDamageHiP1 = 0xb1b104; mDamageHiP2 = 0x2be764e2;
    }
done:
    if (pList != 0)
        pList->Release();
}

// @ 0x00c9c8a0
void cTribeHut_s00c9_c1b0::TakeHit(float fDamage, int nSource, uint32_t nParam3, uint32_t nParam4, IHutInteractor* pInteract)
{
    // "Intact" is captured before the hit is applied: the flag feeds the
    // already-destroyed branch below.
    const bool bIntact = mCombatant.mfField38 > 1.5258789e-05f;   // 01474390

    if (GetCurrentGameMode() == &kGameMode1654c05)
        fDamage *= 20.0f;                                         // 013eecd8

    Combatant_TakeHit(&mCombatant, 0, fDamage, (void*)nSource, (int)nParam3,
                      (void*)nParam4, pInteract);

    if (GetCurrentGameMode() == &kGameMode1654c02)
    {
        if (mpNoun == 0)
            return;

        if (mCombatant.mfField38 > 0.0f)                          // 01485378
        {
            // The hut is still standing: log the hit and let the citizens react.
            if (nSource != -1)
            {
                FUN_00c8e720(nSource);
                const uint32_t nEvent = mpNoun->HandleHit(nSource, 0x530cf04u, 1.0f);
                ((cRelationshipManager*)RelationshipManager())
                    ->RecordEvent(nEvent, nSource, 0x530cf04u, 1.0f);
            }

            if (pInteract != 0)
            {
                IHutEffect* pEffect = 0;

                IHutCitizen* const pProbe =
                    (IHutCitizen*)pInteract->GetProbe();
                pInteract->AttachTo(this);

                const float fProbeRadius = pProbe->GetRadius();

                // Grow the hit volume by the hut's own radius and drop a grid
                // entry for it.
                float fRadius = fProbeRadius;
                fRadius += mSpatial.GetRadius();
                HutVec3* const pAt = mSpatial.GetPosition();
                void* const pEntry = FUN_00bc8000(0xb9d14c31u, (void*)pAt);
                FUN_00bc8400(pEntry);

                HutCitizenList* const pCitizens =
                    (HutCitizenList*)mpNoun->GetCitizenList();
                void* const pStimulus = pInteract->GetKey(0xee3f516eu);
                void* const pAux      = pInteract->GetKey(0xce9f6639u);
                IHutCitizen* const pProbe2 =
                    (IHutCitizen*)pInteract->GetProbe();

                for (void** ppCitizen = pCitizens->mpBegin;
                     ppCitizen != pCitizens->mpEnd; ++ppCitizen)
                {
                    IHutCitizen* const pCitizen = (IHutCitizen*)*ppCitizen;

                    bool bStimulate = !pCitizen->mHitTarget.IsEngaged();

                    if (!bStimulate)
                    {
                        if (fProbeRadius == 0.0f)
                        {
                            const HutVec3* const pSelf = pProbe2->GetPosition();
                            const HutVec3* const pOther = pCitizen->GetPosition();

                            const float fDx = pOther->x - pSelf->x;
                            const float fDy = pOther->y - pSelf->y;
                            const float fDz = pOther->z - pSelf->z;
                            float fDist = fDx * fDx + fDy * fDy + fDz * fDz;
                            fDist = (float)sqrt((double)fDist);

                            fDist -= pCitizen->GetRadius();
                            fDist += pProbe2->GetRadius();
                            if (fDist < 0.0f)
                                fDist = 0.0f;

                            bStimulate = FUN_00c11480(pCitizen, (void*)pOther,
                                                      fDist, 1.0f);
                        }
                        else
                        {
                            bStimulate = FUN_00c0d560(pCitizen, (void*)pAux,
                                                      fProbeRadius, 1.0f);
                        }
                    }

                    if (bStimulate)
                        FUN_00bc97f0((uint8_t*)pCitizen->mpBehaviorTree + 8,
                                     0x20000ull, 10.0f, pStimulus);
                }
            }

            // A hut that is nearly knocked out is flagged for the next hit.
            if (FUN_00bfc490(&mCombatant) < 0.9f)                  // 013ec4b4
                mCombatant.mnFlag34 = 1;
            return;
        }

        // The hut is already down: tell the tribe who hit it.
        if (!bIntact)
            return;

        if (nSource != -1)
        {
            const uint32_t nEvent = mpNoun->HandleHit(nSource, 0x530cf05u, 1.0f);
            ((cRelationshipManager*)RelationshipManager())
                ->RecordEvent(nEvent, nSource, 0x530cf05u, 1.0f);
        }

        void* const pAttacker = (pInteract != 0) ? pInteract->AttachTo(this) : 0;
        void* const pCitizen  = FUN_00ac80d0(pAttacker, kCitizenKey);
        void* const pTribe    = (pCitizen != 0)
                                    ? (void*)((cSPCreatureCitizen*)pCitizen)->GetTribe()
                                    : 0;

        HutMessage msg;
        msg.mpVtable  = kMsgVtable;
        msg.mnTag     = 0x58badddu;
        msg.mnField40 = 0;
        msg.SetIRefCount(0, mpNoun);
        msg.SetIRefCount(1, this);
        msg.SetIRefCount(2, pTribe);
        ((IHutMessageServer*)MessageServer())->Send(msg.mnTag, &msg, 0);
        msg.Destruct();
        return;
    }

    // ---------------------------------------------------------------- modes
    // 0x1654c04 (hut mini-game) and 0x1654c05 (planet tool mode).
    if (GetCurrentGameMode() != &kGameModeHut &&        // 01654c04
        GetCurrentGameMode() != &kGameMode1654c05)
        return;

    if (mCombatant.mfField38 > 0.0f || mpNoun == 0)
        return;

    if (GetCurrentGameMode() == &kGameModeHut)
    {
        if (!FUN_00ae3d40(FUN_00b26930(mpNoun)))
            return;
    }

    IHutEffect* pEffect = 0;
    IHutEffects* const pEffects = (IHutEffects*)EffectsManager();
    if (pEffects->CreateEffect(0x87d89ca9u, 0, (void**)&pEffect))
    {
        // Spawn the destruction effect at the hut's world transform.
        HutVec3* const pWorld = mSpatial.GetWorldPosition();
        pEffect->SetTransform(6, pWorld, 2);

        HutMat33 mat;
        Matrix3FromQuaternion(&mat, mSpatial.GetOrientation());

        HutXformMsg xform;
        XformMsg_ctor(&xform);
        xform.mPosition = *mSpatial.GetPosition();
        xform.mFlags00 |= 4;
        ++xform.mCount02;
        xform.mMatrix    = mat;
        xform.mFlags08 |= 2;
        ++xform.mCount0a;
        pEffect->Send(&xform);

        pEffect->Release();
    }

    if (GetCurrentGameMode() == &kGameMode1654c05)
    {
        void* const pPlanet = GetActivePlanet();
        if (pPlanet != 0)
        {
            void* const pObj = FUN_00c8ea40(mpNoun);
            if (pObj != 0)
            {
                FUN_00c71370(pPlanet, pObj);
                if (FUN_00c70e00(pPlanet) == 2 && FUN_00c71120(pPlanet) == 0)
                    FUN_00c70de0(pPlanet, 1);
            }
        }

        HutMessage msg;
        msg.mpVtable  = kMsgVtable;
        msg.mnTag     = 0x4b3370fu;
        msg.mnField40 = 0;
        msg.mpRefs[0] = mpNoun;
        msg.mnMask    = 0;
        ((IHutMessageServer*)MessageServer())->Send(msg.mnTag, &msg, 0);
        msg.Destruct();
    }

    ((cGameNounManager*)NounManager())->RemoveNoun(mpNoun);
    if (pEffect != 0)
        pEffect->Release();
}

// @ 0x01356230
void FUN_01356230(void)
{
    PropDesc d;

    d.mName = (const char*)0x145a45c;
    d.mHash = 0x33e0b60;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_1_24;
    d.mFn28 = (void*)E209_1_28;
    d.mFn2C = (void*)E209_1_2C;
    d.mFn30 = (void*)E209_1_30;
    d.mFn34 = (void*)E209_1_34;
    d.mFn38 = (void*)E209_1_38;
    d.mType = 0x230;
    *(PropDesc*)0x157c3d0 = d;

    d.mName = (const char*)0x14745ac;
    d.mHash = 0x33e0b61;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_2_24;
    d.mFn28 = (void*)E209_2_28;
    d.mFn2C = (void*)E209_2_2C;
    d.mFn30 = (void*)E209_2_30;
    d.mFn34 = (void*)E209_F34;
    d.mFn38 = (void*)E209_F38;
    d.mType = 0x20c;
    *(PropDesc*)0x157c40c = d;

    d.mName = (const char*)0x1474598;
    d.mHash = 0x33e0b62;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_3_24;
    d.mFn28 = (void*)E209_3_28;
    d.mFn2C = (void*)E209_3_2C;
    d.mFn30 = (void*)E209_3_30;
    d.mFn34 = (void*)E209_F34;
    d.mFn38 = (void*)E209_F38;
    d.mType = 0x200;
    *(PropDesc*)0x157c448 = d;

    d.mName = (const char*)0x1474584;
    d.mHash = 0x33e0b63;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_4_24;
    d.mFn28 = (void*)E209_4_28;
    d.mFn2C = (void*)E209_4_2C;
    d.mFn30 = (void*)E209_4_30;
    d.mFn34 = (void*)E209_F34;
    d.mFn38 = (void*)E209_F38;
    d.mType = 0x1e8;
    *(PropDesc*)0x157c484 = d;

    d.mName = (const char*)0x1474570;
    d.mHash = 0x33e0b64;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_5_24;
    d.mFn28 = (void*)E209_5_28;
    d.mFn2C = (void*)E209_5_2C;
    d.mFn30 = (void*)E209_5_30;
    d.mFn34 = (void*)E209_F34;
    d.mFn38 = (void*)E209_F38;
    d.mType = 0x1f4;
    *(PropDesc*)0x157c4c0 = d;

    d.mName = (const char*)0x1467dac;
    d.mHash = 0x5651e69;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_6_24;
    d.mFn28 = (void*)E209_6_28;
    d.mFn2C = (void*)E209_6_2C;
    d.mFn30 = (void*)E209_6_30;
    d.mFn34 = (void*)E209_6_34;
    d.mFn38 = (void*)E209_6_38;
    d.mType = 0x234;
    *(PropDesc*)0x157c4fc = d;
}
