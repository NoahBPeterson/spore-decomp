// src/game/SPGonzago/_at_00be0000.cpp -- migrated from slice(s) s00befc40, s00beeb70, s00bee450, s00bed920, s00bec890, s00beb6d0, s00bea930 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00be0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cVehicle.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPTimer.h"
#include <math.h>
#include <intrin.h>
#include <stdlib.h>
#include "SP/cGameData.h"
#include "SP/cSpatialObject.h"
#include "SP/cVarListSerializer.h"
#include "SP/cCityTerritory.h"
#include "SP/cCityWalls.h"
#include <stddef.h>
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cCity.h"
#include "SP/cCivilization.h"
#include "SP/cRelationshipManager.h"
#include "SP/cSPEditorSpeciesManager.h"

// ---- items of slice s00bea930 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct rbNodeBase {
    void* mpNodeRight;                  // +0x00
    void* mpNodeLeft;                   // +0x04
    void* mpNodeParent;                 // +0x08
    char  mColor;                       // +0x0c
    char  pad[3];
};
struct IntTreeMap {                     // sizeof 0x1c
    char       pad0[4];                 // +0x00
    rbNodeBase mAnchor;                 // +0x04
    int        mnSize;                  // +0x14
    char       pad18[4];                // +0x18
    int* Find(const int* key, int* out);    // 0x00e5c780  (thiscall on the map)
    int& operator[](const int& k);          // 0x00643a40
    void DoNukeSubtree(void* pNode);        // 0x009a9600
    void reset() {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
    void clear() { DoNukeSubtree(mAnchor.mpNodeParent); reset(); }
};
template <class T> const T& emin(const T& a, const T& b) { return a < b ? a : b; }
struct cSPTimer {                               // 0x20 bytes (embedded in Slot80 at +0x30/+0x50)
    char pad[0x20];
    bool             FUN_feba90();              // 0x00feba90
    unsigned __int64 FUN_bc3190();              // 0x00bc3190
    void             FUN_bc30f0();              // 0x00bc30f0
    void             FUN_bc3130();              // 0x00bc3130
};
struct Notifier { char pad0[0xa4]; void* p0xa4; void RemoveListener(void* o, int v); };
Notifier* GetNotifier();                        // 0x00b3d480
class Veh;
class Veh {
public:
    char  pad0[0x1d8];
    int   f1d8;                                 // +0x1d8
    int   f1dc;                                 // +0x1dc
    char  pad1[0x20c - 0x1e0];
    float f20c;                                 // +0x20c
    float f210;                                 // +0x210
    int   f214;                                 // +0x214
    char  pad2[0x762 - 0x218];
    char  f762;                                 // +0x762

    void sub_be9cb0(int, int, int, int);         // 0x00be9cb0
    unsigned int FUN_00bd85c0(float*, int*);    // 0x00bd85c0
    void FUN_00ca8120(int);                     // 0x00ca8120
};
class Sim {
public:
    char       pad0[0x120];
    void*      vptr120;                         // +0x120
    char       pad1[0x590 - 0x124];
    void*      p590;                            // +0x590
    char       pad2[0x5a0 - 0x594];
    IntTreeMap map1;                            // +0x5a0
    IntTreeMap map2;                            // +0x5bc
    IntTreeMap map3;                            // +0x5d8
    char       pad3[0x618 - 0x5f4];
    char*      arr618;                          // +0x618
    char       pad4[0x62c - 0x61c];
    Veh**      vehBegin;                        // +0x62c
    Veh**      vehEnd;                          // +0x630
    char       pad5[0x64c - 0x634];
    int        f64c;                            // +0x64c
    char       pad6[0x750 - 0x650];
    float      f750;                            // +0x750
    int        f754;                            // +0x754
    float      f758;                            // +0x758
    int        i75c;                            // +0x75c
    char       pad7[0x770 - 0x760];
    cSPTimer   timer770;                        // +0x770
    char       padTimer770[0x88 - 0x20];        // +0x790 .. +0x7f8 (timer770 spans 0x88)
    uint8_t*   begin;                           // +0x7f8
    uint8_t*   end;                             // +0x7fc

    void FUN00bda0a0();                         // 0x00bda0a0
    void FUN00be9cb0(int, int, int, int);       // 0x00be9cb0
    void FUN00c00b00(int, int);                 // 0x00c00b00
    void sub_be92e0(int, int, int, int, int);   // 0x00be92e0
    void sub_bd9a00(void*);                     // 0x00bd9a00
    void sub_bea930();
    void sub_beaa30();
    void sub_beabb0();
    void sub_beb090(int id, int count);
    void sub_beb1c0(int idx, int p);
    void sub_beb5c0();
    void sub_bd9ed0(int);                       // 0x00bd9ed0
    void sub_be11f0();                          // 0x00be11f0
};
#define VGETID(p)     ((int(__thiscall*)(void*))((void**)*(void***)(p))[0x4c / 4])((void*)(p))
// ---- items of slice s00bea930 end

// ---- items of slice s00beb6d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char  g13ec4b8;      // 0x013ec4b8  float 1e-8f
extern float g14853e0;      // 0x014853e0  4.0f
extern float g168c420, g168c424, g168c428;   // 0x0168c420 invalid position
extern float g1468fd4;      // 0x01468fd4  FLT_MAX
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct SpVector {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint8_t  mAllocator[8];
};
struct IObj { virtual void AddRef(); virtual void Release(); };
struct ISub34 {
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
    virtual Vector3* v2c();                       // 0x2c  position
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
    virtual void v5c(void* arg);                  // 0x5c
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual float v70();                          // 0x70
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
    virtual void v90();
    virtual void v94(void* arg);                  // 0x94
};
void*    __cdecl NounManager();                                    // 0x00b3d300
void*    __cdecl GonzagoModelWorld();                              // 0x00b3d520
void*    __cdecl PlanetModel();                                    // 0x00b3d350
void* __stdcall FUN_00b18460(uint32_t id);                          // 0x00b18460
int      __cdecl FUN_00c9e8e0(int kind, const Vector3* p);         // 0x00c9e8e0
void*    __cdecl FUN_01029790();                                   // 0x01029790
void     __cdecl FUN_00c6f770(uint32_t id, int idx, uint32_t val); // 0x00c6f770
bool     __cdecl EAIO_WriteUint32(void* stream, void* v, int a, int b);  // 0x0093aa70
bool     __cdecl EAIO_ReadInt32(void* stream, void* v, int a, int b);    // 0x0093a780
bool     __cdecl StreamWrite(void* stream, void* v, int a);              // 0x0093a9a0
bool     __cdecl ReadBool(void* stream, void* dst);                      // 0x0093ac80
struct GameDataBase {                       // cGameData
    void  Ctor();                           // 0x00b18660
    bool  Write(void* s);                   // 0x00b18590
    bool  Read(void* s);                    // 0x00b18600
};
struct SpatialBase {                        // cSpatialObject
    void  Ctor();                           // 0x00c89630
    bool  Write(void* s);                   // 0x00c88a90
    bool  Read(void* s);                    // 0x00c88b00
    void* AsInterface(uint32_t id);         // 0x00c884f0
    void  Teardown();                       // 0x00c8b2e0
};
struct VarListSerializer {                  // cVarListSerializer
    void* Ctor(void* owner, void* n, uint32_t id);   // 0x00692f90
    bool  SerializeOut(void* s);                     // 0x00692900
    bool  SerializeIn(void* s);                      // 0x00693e10
};
struct NounMgr {                            // cGameNounManager
    void  RemoveNoun(void* noun);           // 0x00b225d0
    void* CreateNoun(void* id);             // 0x00b20c60
};
struct ColonyTuning {                       // cSPSpaceColonyTuning
    float GetTerritoryRadius();             // 0x01029820
};
struct PlanetModelT {                       // cPlanetModel
    void Project(Vector3* out, const Vector3* in);   // 0x00b81630
};
struct PropReg {                            // 0x00695b40
    void Add(void* ct, void* b, const wchar_t* n);
};
struct cCityTerritory {
    void*   vfptr0;                    // 0x000
    void*   vfptr1;                    // 0x004
    uint8_t pad_008[0x2c - 8];
    void*   vfptr_rc;                  // 0x02c
    uint8_t pad_030[0x34 - 0x30];
    uint8_t sub34[1];                  // 0x034  cSpatialObject
    uint8_t pad_035[0x108 - 0x35];
    uint8_t m108;                      // 0x108
    uint8_t pad_109[3];
    float   m10c;                      // 0x10c
    uint8_t m110;                      // 0x110
    uint8_t m111;                      // 0x111
    uint8_t pad_112[0x274 - 0x112];
    uint8_t mBuildingLinks[14][14];    // 0x274
    uint8_t pad_338[0x344 - 0x338];
    uint32_t mStyle;                   // 0x344

    ISub34* Sub() { return (ISub34*)sub34; }

    cCityTerritory* ctor();                        // 0x00beb950
    void* AsInterface(uint32_t id);                // 0x00beb9c0
    bool  InitFromDefinition(void* a);             // 0x00beb9f0
    void  ApplyTo(void* obj);                      // 0x00beba10
    void  UpdateRadius();                          // 0x00beba70
    bool  Write(void* stream);                     // 0x00beba90
    bool  Read(void* stream);                      // 0x00bebad0
    void  Shutdown();                              // 0x00bebbd0
    uint32_t Overlaps(cCityTerritory* other);      // 0x00bebc10
    void* AsInterface2(uint32_t id);               // 0x00bebd40
    uint32_t SetPoliticalID(uint32_t id);          // 0x00bebd70
    void  SetRadius();                             // 0x00bebd90
    bool  WriteSerializableObjectCheck(void* stream);  // 0x00bebe50
    bool  PostDataLoad(void* stream);              // 0x00bebf50
};
struct cCityWalls {
    void*    vtbl_a;             // 0x000
    void*    vtbl_b;             // 0x004
    uint8_t  pad_008[0x2c - 8];
    void*    vfptr_rc;           // 0x02c
    uint8_t  pad_030[0x34 - 0x30];
    uint8_t  sub34[1];           // 0x034  cSpatialObject
    uint8_t  pad_035[0x10c - 0x35];
    uint32_t field_10c;          // 0x10c
    SpVector mDockSlots;         // 0x110
    SpVector field_124;          // 0x124
    uint8_t  pad_138[0x198 - 0x138];
    SpVector field_198;          // 0x198
    uint8_t  pad_1ac[0x254 - 0x1ac];
    uint32_t field_254;          // 0x254
    float    mInnerRadius;       // 0x258
    float    mOuterRadius;       // 0x25c
    float    field_260;          // 0x260
    uint32_t field_264;          // 0x264  cCity*
    uint8_t  pad_268[0x344 - 0x268];
    uint32_t mStyle;             // 0x344
    uint8_t  pad_348[0x354 - 0x348];
    uint32_t field_354;          // 0x354

    ISub34* Sub() const { return (ISub34*)sub34; }
    ISub34* CitySub() const { return (ISub34*)(field_264 + 0x120); }

    void    FUN_00bec060();                       // 0x00bec060
    uint32_t PointInsideWall(const Vector3& p);            // 0x00bec0f0
    uint32_t PointInsideInnerWall(const Vector3& p);       // 0x00bec140
    Vector3 GetCenter();                                  // 0x00bec190
    Vector3 GetInnerGatePosition(int idx);                // 0x00bec1c0
    Vector3 GetGatePosition(int idx);                     // 0x00bec2d0
    Vector3* RequestGatePosition(Vector3* out, int idx, int kind);  // 0x00bec460
    Vector3* FindNearestPosition(Vector3* out, const Vector3* ref, int kind); // 0x00bec660
    void    UpdateGatePosition(int idx);                  // 0x00bec790
    bool GetIsWallBuilt();                                // 0x00bec860
};
// ---- items of slice s00beb6d0 end

// ---- items of slice s00bec890 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EastlNew(unsigned int size, const char* name, int flags, int align, const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl EastlDelete(void* p);                                    // 0x00f47380
extern "C" void* __cdecl FUN_00c8a420(void* p);                                   // 0x00c8a420
extern "C" void* __cdecl FUN_00b184c0(void* p);                                   // 0x00b184c0
extern "C" void  FUN_00bec790();                                                  // 0x00bec790
extern "C" void* __cdecl FUN_00454cb0(void* str, const char* s);                  // 0x00454cb0
extern "C" void* __cdecl FUN_0041cb40(void* m, void* src);                        // 0x0041cb40 Matrix3::Assign
extern "C" void* __cdecl FUN_0059c190(void* out, void* q);                        // 0x0059c190 Matrix3FromQuaternion
extern "C" void  __cdecl FUN_00512050(void* a, void* b, void* c, void* d, void* e); // 0x00512050
extern "C" void* __cdecl FUN_00abced0(void* a, void* b, void* c);                 // 0x00abced0 copy_backward
extern "C" void  __cdecl FUN_00a177f0(void* a, void* b, void* c);                 // 0x00a177f0 fill
extern "C" void  __cdecl FUN_006e5760(void* a, int n, void* v);                   // 0x006e5760 uninitialized_fill_n
extern "C" void* __cdecl FUN_00a11310(void* a, void* b, void* c);                 // 0x00a11310
extern "C" void* __cdecl FUN_00473500(void* v);                                   // 0x00473500
extern "C" void* __cdecl FUN_00ae5c30(void* self);                                // 0x00ae5c30 Simulator::SimSingleton ctor
extern "C" void* __cdecl FUN_00b3d350(void);      // SP::PlanetModel
extern "C" void* __cdecl FUN_0067de30(void);       // SP::PropertyManager
extern "C" void* __cdecl FUN_01021260(void);       // SP::cSPLivingUniverse::GetActivePlanet
extern "C" void* __cdecl FUN_00c71e30(void);
extern "C" char  __cdecl FUN_00c308b0(void);
extern "C" void  __cdecl FUN_00b3d430(int);        // SP::TerraformingManager
extern "C" char  __cdecl FUN_00bbe5c0(unsigned v);
extern "C" void* __cdecl FUN_00bebd00(void* v);
extern "C" void* __cdecl FUN_00bd81f0(void);
extern "C" void* __cdecl FUN_0067ddd0(void);                      // SP::EffectsManager
extern "C" void* __cdecl FUN_004a9b40(void* out, void* q);
#define ALLOC_H "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
inline void Release(void* o) { if (o) ((void (**)(void*)) (*(void***)o))[1](o); }
inline void* VFn(void* o, int byteoff) { return (*(void***)o)[byteoff / 4]; }
inline void* VCall0(void* o, int off) { return ((void* (*)(void*))VFn(o, off))(o); }
struct S {
  void  FUN_00bec890();                                       // 0x00bec890 dtor
  void  FUN_00becac0(int idx);                                // 0x00becac0
  float* FUN_00becb10(float* out, float* pos);                // 0x00becb10
  void  FUN_00becc80();                                       // 0x00becc80
  void  FUN_00beccf0();                                       // 0x00beccf0
  void  FUN_00becd70(char param_2);                           // 0x00becd70
  void* FUN_00bed1c0(void* p);                                // 0x00bed1c0  "City Wall" assign
  void  FUN_00bed200(unsigned n, void* pos, void* val);       // 0x00bed200 vector<0xc>::insert
  void  FUN_00bed3c0(void* p);                                // 0x00bed3c0 Zone::FillPoints
  void  FUN_00bed460();                                       // 0x00bed460 ScriptSetSeedOverride
};
struct Fill145 { void FUN_00473500(void* arg); };  // 0x00473500
// ---- items of slice s00bec890 end

// ---- items of slice s00bed920 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vector3_s00be_d920 {
    float x, y, z;
    Vector3_s00be_d920() {}
    Vector3_s00be_d920(const Vector3_s00be_d920& o) : x(o.x), y(o.y), z(o.z) {}
};
}
namespace SP {
struct SpVector_s00be_d920 {
    Vector3_s00be_d920* mpBegin;
    Vector3_s00be_d920* mpEnd;
    Vector3_s00be_d920* mpCapacity;
    uint8_t  mAlloc[8];
    void     resize(int n);                          // 0x00473810  ?resize@?$SpVector@UVector3@@@@QAEXH@Z
    void     FUN_004548d0(int n);                    // 0x004548d0
    Vector3_s00be_d920* FUN_00479330(Vector3_s00be_d920* pos, int n, Vector3_s00be_d920* val);   // 0x00479330 (insert/grow)
    Vector3_s00be_d920* erase(Vector3_s00be_d920* first, Vector3_s00be_d920* last);   // 0x0050f740  ?erase@?$SpVector@UVector3@@@@QAEPAUVector3@@PAU2@0@Z
};
}
namespace SP {
struct cGameData_s00be_d920     { void ctor(); };               // 0x00b18660
}
namespace SP {
struct cSpatialObject_s00be_d920{ void ctor(); };               // 0x00c89630
}
namespace SP {
void* __cdecl PropertyManager();                     // 0x0067de30
}
namespace SP {
void  __cdecl GetPropertyAsKey(int prop, uint32_t key, void* dest);   // 0x006a1250
}
namespace SP {
void  __cdecl FUN_011e073e(void* dest, int val, uint32_t size);       // 0x011e073e
}
namespace SP {
void* __cdecl GonzagoModelWorld();                   // 0x00b3d520
}
namespace SP {
struct RefCounted {
    virtual void Slot00();
    virtual void Release();                          // vtable slot 0x04
};
}
namespace SP {
struct GonzagoWorld {
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void Slot14();
    virtual void v18(void* propList, uint32_t value); // vtable slot 0x18
};
}
namespace SP {
struct Key { uint32_t k0, k1, k2; };
}
namespace SP {
struct KeyVector {
    Key*     mpBegin;                                // 0x00
    Key*     mpEnd;                                  // 0x04
    Key*     mpCapacity;                             // 0x08
    uint32_t mPad0c;                                 // 0x0c
    Key*     mpStorage;                              // 0x10
    uint32_t mPad14;                                 // 0x14
    Key      mInlineKeys[6];                         // 0x18
    void resize(int n);                              // 0x00bed3e0  __thiscall, ret 4
};
}
namespace SP {
struct Variant {
    const void* mpData;                              // 0x00
    uint32_t    mSize;                               // 0x04
    uint32_t    mExtra;                              // 0x08
    uint32_t    mPad0c;                              // 0x0c
    uint16_t    mFlags;                              // 0x10
    uint16_t    mType;                               // 0x12
    Variant() : mFlags(0), mType(0) {}               // default ctor only clears the flag word
    bool Construct(uint32_t a, uint32_t b, const void* data, uint32_t elem, uint32_t n);  // 0x0093dd80
    void Destruct(int flag);                         // 0x0093db80
};
}
namespace SP {
struct PropertyPair {
    uint32_t mKey;                                   // 0x00
    Variant  mValue;                                 // 0x04
};
}
namespace SP {
struct cPropertyList_s00be_d920 {
    void*         mpVtable;                          // 0x00
    uint32_t      mRefCount;                         // 0x04
    uint32_t      mField08;                          // 0x08
    uint32_t      mField0c;                          // 0x0c
    uint32_t      mField10;                          // 0x10
    uint32_t      mField14;                          // 0x14
    PropertyPair* mpPropertyMapBegin;                // 0x18  mPropertyMap
    PropertyPair* mpPropertyMapEnd;                  // 0x1c
    PropertyPair* mpPropertyMapCapacity;             // 0x20
    uint32_t      mField24;                          // 0x24
    uint32_t      mField28;                          // 0x28
    uint32_t      mField2c;                          // 0x2c
    RefCounted*   mpParent;                          // 0x30  EA::AutoRefCount<cPropertyList>
    uint32_t      mModificationCount;                // 0x34

    void ctor();                                     // 0x006a1c40  ??0cPropertyList@SP@@QAE@XZ
    void SetProperty(uint32_t key, const Variant& value);   // 0x006a2e20
    void dtor();
};
}
namespace SP {
__forceinline void cPropertyList_s00be_d920::dtor()
{
    if (mpParent) {
        mpParent->Release();
    }
    for (PropertyPair* p = mpPropertyMapBegin; p != mpPropertyMapEnd; ++p) {
        if (p->mValue.mFlags & 4) {
            p->mValue.Destruct(0);
        }
    }
    if (mpPropertyMapBegin) {
        ::operator delete(mpPropertyMapBegin);
    }
    mpVtable = (void*)0x13eb938;
}
}
namespace SP {
struct PropManager {
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1c();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();
    virtual char Resolve(uint32_t prop, uint32_t key, void** out);   // vtable slot 0x2c
};
}
namespace SP {
struct Combatant { int GetDamageState(); };          // 0x008e7f80  ([this+0x34])
}
namespace SP {
struct CityWalls {
    void*    vtbl_a;             // 0x000  (0x014690b0)
    void*    vtbl_b;             // 0x004  (0x0146909c)
    uint8_t  pad_08[0x2c];       // 0x008..0x033 (cGameData base)
    void*    vtbl_spatial;       // 0x034  (0x01468fd8, cSpatialObject vtable)
    uint8_t  pad_38[0x108 - 0x38];
    uint8_t  field_108;          // 0x108
    uint8_t  pad_109[3];
    uint32_t field_10c;          // 0x10c
    SpVector_s00be_d920 mDockSlots;         // 0x110
    SpVector_s00be_d920 field_124;          // 0x124
    Vector3_s00be_d920  field_138;          // 0x138
    Vector3_s00be_d920  field_144;          // 0x144
    Vector3_s00be_d920  field_150;          // 0x150
    SpVector_s00be_d920 field_15c;          // 0x15c
    SpVector_s00be_d920 field_170;          // 0x170
    SpVector_s00be_d920 field_184;          // 0x184
    SpVector_s00be_d920 field_198;          // 0x198
    SpVector_s00be_d920 field_1ac;          // 0x1ac
    SpVector_s00be_d920 field_1c0;          // 0x1c0
    SpVector_s00be_d920 field_1d4;          // 0x1d4
    SpVector_s00be_d920 field_1e8;          // 0x1e8
    SpVector_s00be_d920 field_1fc;          // 0x1fc
    SpVector_s00be_d920 field_210;          // 0x210
    Vector3_s00be_d920  field_224;          // 0x224
    Vector3_s00be_d920  field_230;          // 0x230
    Vector3_s00be_d920  field_23c;          // 0x23c
    Vector3_s00be_d920  field_248;          // 0x248
    uint32_t field_254;          // 0x254
    float    mInnerRadius;       // 0x258
    float    mOuterRadius;       // 0x25c
    float    field_260;          // 0x260
    uint32_t field_264;          // 0x264  (cCity*)
    Vector3_s00be_d920  field_268;          // 0x268
    uint8_t  mBuildingLinks[0xc4];   // 0x274..0x337
    uint8_t  pad_338[0xc];       // 0x338..0x343
    uint32_t mStyle;             // 0x344
    uint32_t field_348;          // 0x348
    uint32_t field_34c;          // 0x34c
    uint8_t  field_350;          // 0x350
    uint8_t  pad_351[3];
    uint32_t field_354;          // 0x354

    CityWalls* ctor();                       // 0x00bedb70
    void   FUN_00bede60(int style);          // 0x00bede60
    void   FUN_00bee150();                   // 0x00bee150
    void   FUN_00bee200();                   // 0x00bee200
    void   FUN_00bec790(int a);              // 0x00bec790
    Vector3_s00be_d920* FUN_00becb10(Vector3_s00be_d920* out, Vector3_s00be_d920* src);   // 0x00becb10
};
}
namespace SP {
struct City {
    void FUN_00bd94a0(void* vec);            // 0x00bd94a0
    void FUN_00be5280(void* vec);            // 0x00be5280
    void FUN_00bd9620(void* vec);            // 0x00bd9620
    void FUN_00be5320(void* vec);            // 0x00be5320
    void FUN_00be5700(void* out);            // 0x00be5700
};
}
namespace SP {
extern float gF_0168c420, gF_0168c424, gF_0168c428;   // default position triple
}
namespace SP {
extern float gF_01466190;                             // 29.0f (inner radius)
}
namespace SP {
extern float gF_01469148;                             // 37.0f (outer radius)
}
namespace SP {
extern float gF_0156f530, gF_0156f534, gF_0156f538;
}
namespace SP {
struct PtrVec { void** mpBegin; void** mpEnd; void** mpCapacity; };
}
// ---- items of slice s00bed920 end

// ---- items of slice s00bee450 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_LinkRowIds[14];   // 0x01468f98
inline void* operator new(size_t, void* p) { return p; }
struct Vector3_s00be_e450 {
    float x, y, z;
    __forceinline Vector3_s00be_e450() {}
    __forceinline Vector3_s00be_e450(const Vector3_s00be_e450& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Raw3 { uint32_t a, b, c; };
struct Prop {
    void*    mpData;
    uint32_t pad[3];
    uint8_t  mFlags;      // +0x10 (0x30: indirect)
    uint8_t  pad11;
    uint16_t mType;       // +0x12 (0xd: float)
};
struct PropList {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Prop** out);   // 0x24
};
bool GetPropertyAsVector3(PropList* l, uint32_t id, Raw3* out);                 // 0x006a1110 cdecl
bool GetPropertyAsVector3Array(PropList* l, uint32_t id, int* n, Vector3_s00be_e450** v);  // 0x006a0990 cdecl
bool GetPropertyAsBytes(PropList* l, uint32_t id, uint32_t* n, uint8_t** p);    // 0x006a0760 cdecl
struct sp_vector_allocator { uint32_t mData[2]; };
struct SpVector_s00be_e450 {
    Vector3_s00be_e450* mpBegin;
    Vector3_s00be_e450* mpEnd;
    Vector3_s00be_e450* mpCapacity;
    sp_vector_allocator mAllocator;
    void DoInsertValue(Vector3_s00be_e450* position, const Vector3_s00be_e450& value);   // 0x004b5ad0
    void resize(int n);                                            // 0x00473810
    Vector3_s00be_e450* erase(Vector3_s00be_e450* first, Vector3_s00be_e450* last);                 // 0x0050f740
    __forceinline void push_back(const Vector3_s00be_e450& value)
    {
        if (mpEnd < mpCapacity)
            ::new ((void*)mpEnd++) Vector3_s00be_e450(value);
        else
            DoInsertValue(mpEnd, value);
    }
    __forceinline void erase_inline(Vector3_s00be_e450* first, Vector3_s00be_e450* last)
    {
        Vector3_s00be_e450* d = first;
        for (Vector3_s00be_e450* s = last; s != mpEnd; ++s, ++d) {
            d->x = s->x; d->y = s->y; d->z = s->z;
        }
        mpEnd -= (last - first);
    }
};
struct Model {
    uint32_t pad0;
    uint32_t mFlags;      // +0x04
    uint32_t pad08[17];
    Raw3     mColor;      // +0x4c
    uint32_t pad58[14];
    PropList* mpProps;    // +0x90
};
struct Civilization { uint32_t pad[0x31]; Raw3 mColor; };   // +0xc4
struct cCity {
    Civilization* GetCivilization();    // 0x00bd9bf0 (returns [this+0x590])
    void FUN_00be6f90();                // 0x00be6f90
};
struct cPlanetModel {
    void FUN_00b83c40(int arg);   // 0x00b83c40
};
cPlanetModel* PlanetModel_s00be_e450();            // 0x00b3d350 (cdecl)
struct cCityWalls_s00be_e450;
struct Spatial {
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
    virtual int  v2c(float f, void* p, int a, int b);     // 0x2c
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
    virtual bool v58();                                   // 0x58

    uint8_t  pad04[0x98];
    Model*   mpModel;               // +0x9c
    uint8_t  pad_a0[0x128 - 0xa0];
    SpVector_s00be_e450 mTurrets;              // +0x128
    SpVector_s00be_e450 mTurretsT;             // +0x13c
    SpVector_s00be_e450 mGates;                // +0x150
    SpVector_s00be_e450 mGatesT;               // +0x164
    SpVector_s00be_e450 mBuildings;            // +0x178
    SpVector_s00be_e450 mBuildingsT;           // +0x18c
    SpVector_s00be_e450 mDecorations;          // +0x1a0
    SpVector_s00be_e450 mDecorationsT;         // +0x1b4
    SpVector_s00be_e450 mPlazas;               // +0x1c8
    SpVector_s00be_e450 mPlazasT;              // +0x1dc
    Raw3     mFirstBoatPos;         // +0x1f0
    Raw3     mFirstBoatPosT;        // +0x1fc
    Raw3     mModelDocksOffset;     // +0x208
    Raw3     mModelDocksOffsetT;    // +0x214
    int      mWallSize;             // +0x220
    float    mInnerRadius;          // +0x224
    float    mOuterRadius;          // +0x228
    float    mCityHallDiasHeight;   // +0x22c
    cCity*   mpCity;                // +0x230
    Raw3     mField268;             // +0x234
    uint8_t  mBuildingLinks[14][14];// +0x240

    bool LoadModel(int arg);        // 0x00c8a550 (cSpatialObject::LoadModel)
    cCityWalls_s00be_e450* Walls() { return (cCityWalls_s00be_e450*)((char*)this - 0x34); }
    bool LoadModelWalls(int arg);   // 0x00bee450
};
struct cCityWalls_s00be_e450 {
    void FUN_00beccf0();                            // 0x00beccf0
    void FUN_00bee150();                            // 0x00bee150
    void FUN_00becc80();                            // 0x00becc80
    void FUN_00bee200();                            // 0x00bee200
    Raw3 FUN_00becb10(const Raw3& v);               // 0x00becb10 (ret 8)
};
#define READ_FLOAT_PROP(id, out)                                                        \
    do {                                                                                \
        PropList* l = mpModel->mpProps;                                                 \
        Prop* p;                                                                        \
        if (l && l->GetProperty((id), &p) && p->mType == 0xd) {                         \
            float* d = (float*)p;                                                       \
            if (p->mFlags & 0x30) d = *(float**)p;                                      \
            (out) = *d;                                                                 \
        }                                                                               \
    } while (0)
// ---- items of slice s00bee450 end

// ---- items of slice s00beeb70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);   // thunk 0x011e073e
extern float g_C478;   // 0x0168c478
extern float g_C47C;   // 0x0168c47c
extern float g_C480;   // 0x0168c480
extern float g_C484;   // 0x0168c484
extern float g_C488;   // 0x0168c488
extern float g_C48C;   // 0x0168c48c
extern char g_smDataSerializerList_cCultureSet[];   // 0x0156fa30
#pragma function(memset)
struct Vector3_s00be_eb70 {
    float x, y, z;
    Vector3_s00be_eb70() {}
    Vector3_s00be_eb70(const Vector3_s00be_eb70& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3_s00be_eb70(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct Quaternion { float x, y, z, w; };
extern Vector3_s00be_eb70 g_PointOffsets[8];   // 0x01469150
struct SpVector_s00be_eb70 {
    Vector3_s00be_eb70* mpBegin;
    Vector3_s00be_eb70* mpEnd;
    Vector3_s00be_eb70* mpCapacity;
    uint32_t mAllocator[2];
    void DoInsertValue(Vector3_s00be_eb70* pos, const Vector3_s00be_eb70& v);   // 0x004b5ad0
    Vector3_s00be_eb70& push_back()
    {
        if (mpEnd < mpCapacity)
            ++mpEnd;
        else {
            Vector3_s00be_eb70 tmp;
            DoInsertValue(mpEnd, tmp);
        }
        return mpEnd[-1];
    }
};
struct Locator {
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
    virtual const Vector3_s00be_eb70* GetPosition();                       // 0x2c
    virtual const Quaternion* GetOrientation();                 // 0x30
    virtual void v34();
    virtual void SetPosition(const Vector3_s00be_eb70* p);                 // 0x38
    virtual void SetOrientation(const Quaternion* q);           // 0x3c

    void SetPositionRaw(const Vector3_s00be_eb70* p);                      // 0x00c88670
    void SetOrientationRaw(const Quaternion* q);                // 0x00c886d0
    void SetPositionIfChanged(const Vector3_s00be_eb70* p);                // 0x00bef540
    void SetOrientationIfChanged(const Quaternion* q);          // 0x00bef590
};
class cVehicleLike;
struct IntrusiveObj {
    virtual void AddRef();
    virtual void Release();
};
struct cCity_s00be_eb70 : IntrusiveObj {
    uint32_t pad04[0x47];
    Locator  mLocator;      // +0x120
    int      GetVehicleSpecialty();          // 0x00bd81d0 (reads +0x540)
    const Vector3_s00be_eb70* FUN_00bd99e0();           // 0x00bd99e0
};
struct cPlanetModel_s00be_eb70 {
    Vector3_s00be_eb70 DirectionToSurfacePosition(const Vector3_s00be_eb70& dir);   // 0x00b815a0
    Vector3_s00be_eb70 FUN_00b81630(const Vector3_s00be_eb70& pos);                  // 0x00b81630
};
cPlanetModel_s00be_eb70* PlanetModel_s00be_eb70();    // 0x00b3d350 (cdecl)
int FUN_00bebc90(int a, int b); // 0x00bebc90 (cdecl)
struct Rec4 {
    Vector3_s00be_eb70 p[8];
};
__forceinline Vector3_s00be_eb70 RotateScaled(const Quaternion& q, const float* ps, float vx, float vy, float vz)
{
    float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
    float xy = q.y * q.x, xz = q.z * q.x, yz = q.z * q.y;
    float wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;
    float rx = (((xy - wz) * vy + (wy + xz) * vz) * 2.0f + (1.0f - (zz + yy) * 2.0f) * vx) * *ps;
    float ry = (((yz - wx) * vz + (wz + xy) * vx) * 2.0f + (1.0f - (zz + xx) * 2.0f) * vy) * *ps;
    float rz = (((wx + yz) * vy + (xz - wy) * vx) * 2.0f + (1.0f - (yy + xx) * 2.0f) * vz) * *ps;
    return Vector3_s00be_eb70(rx, ry, rz);
}
__forceinline Vector3_s00be_eb70 AddPos(const Locator& loc, const Vector3_s00be_eb70& o)
{
    const Vector3_s00be_eb70* p = const_cast<Locator&>(loc).GetPosition();
    return Vector3_s00be_eb70(p->x + o.x, p->y + o.y, p->z + o.z);
}
class cVehicleLike {
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
    virtual void SetModel(int id);   // 0x60

    uint32_t pad04[0xa];            // 0x04..0x2c
    uint32_t mOwnerPtr;             // +0x2c   (used by SetGameDataOwner2)
    uint32_t mOwnerId;              // +0x30
    Locator  mLocator;              // +0x34 (embedded object, own vptr)
    uint32_t pad38[0x49];           // to 0x15c
    SpVector_s00be_eb70 mPoints;               // +0x15c
    uint32_t pad170[10];
    Rec4*    mpRecs;                // +0x198
    uint32_t pad19c[0x22];          // to 0x224
    Vector3_s00be_eb70  mV224;                 // +0x224 source of the copy below
    Vector3_s00be_eb70  mV230;                 // +0x230 copy target
    uint32_t pad23c[0x20];          // to 0x25c
    float    mScale;                // +0x25c
    uint32_t pad260;
    IntrusiveObj* mpCity;           // +0x264
    Vector3_s00be_eb70  mV268;                 // +0x268
    uint32_t mBlock274[49];         // +0x274 .. 0x338
    Vector3_s00be_eb70  mPos;                  // +0x338
    uint32_t pad344[2];
    int      mSpecialtyArg;         // +0x34c

    void SetGameDataOwner2(cCity_s00be_eb70* city);    // 0x00b18550
    void FUN_00bee150();                    // 0x00bee150
    void FUN_00bee200();                    // 0x00bee200
    void FUN_00becc80();                    // 0x00becc80
    void FUN_00beccf0();                    // 0x00beccf0
    Vector3_s00be_eb70* FUN_00becb10(Vector3_s00be_eb70* out, const Vector3_s00be_eb70* src);   // 0x00becb10

    void Init(cCity_s00be_eb70* city, int model);      // 0x00beeb70
    void RecomputeGameData();               // 0x00bef4e0
};
namespace SP {
struct cSPTimer_s00be_eb70 {
    char mData[0x48];
    void Restart();                     // 0x00bc3130
    uint64_t GetElapsedTime();          // 0x00bc3190
};
}
namespace SP {
struct cGameNounManager_s00be_eb70;
}
namespace SP {
class cCivilization_s00be_eb70 {
public:
    char     pad000[0x89];
    uint8_t  mUnlimitedMoney;        // +0x89  no-bankruptcy cheat
    char     pad08a[0x0e];
    float    mMoney;                 // +0x98
    char     pad09c[0x6c];
    cSPTimer_s00be_eb70 mTimer108;              // +0x108
    char     pad150[0x118];
    uint32_t mSpeciesKey[0xc];       // +0x268 species/archetype key
    int      mLevel;                 // +0x298 civ level
    char     pad29c[0xd4];
    uint8_t  mFlag370;               // +0x370
    char     pad371[0x07];
    cSPTimer_s00be_eb70 mTimer378;              // +0x378
    uint8_t  mFlag3c0;               // +0x3c0
    char     pad3c1[0x07];
    cSPTimer_s00be_eb70 mTimer3c8;              // +0x3c8
    char     pad410[0x24];
    int      mState434;              // +0x434
    int      mId438;                 // +0x438
    int      mValue43c;              // +0x43c
    int      mValue440;              // +0x440
    int      mValue444;              // +0x444
    float    mValue448;              // +0x448
    char     pad44c[0x38];
    uint8_t  mFlags484[0x28];        // +0x484 flag bytes
    float    mCredit4ac;             // +0x4ac
    float    mDebt4b0;               // +0x4b0

    float GetMoney();                        // 0x00bef6d0
    void  SpendMoney(float amount);          // 0x00bef710
    void  RaiseLevel(int level);             // 0x00bef770
    bool  IsBelowTopState();                 // 0x00bef7e0
    void  SetState(int id, int state);       // 0x00bef800
    void  RestartTimer378();                 // 0x00bef830
    void  RestartTimer3c8();                 // 0x00bef850
    bool  IsTimer108Elapsed();               // 0x00bef8a0
    void  ResetValues();                     // 0x00bef5f0
    uint8_t GetFlag484(int index);           // 0x00bef970
    int   CountFlags();                      // 0x00befab0
    void* GetSpeciesProfile();               // 0x00bef950
};
}
namespace SP {
struct cGameNounManager_s00be_eb70 {
    char pad000[0x10];
    cCivilization_s00be_eb70* GetPlayerCivilization();    // 0x00b25fb0
};
}
namespace SP {
cGameNounManager_s00be_eb70* NounManager_s00be_eb70();                 // 0x00b3d300
}
namespace SP {
class cCivModeStrategy {
public:
    void CheckEvents();                          // 0x00cf9ba0
    void DoNext(int id, int flag);               // 0x00cfa990
};
}
namespace SP {
cCivModeStrategy* GetCivModeStrategy();          // 0x00cf74c0
}
struct cSPEditorSpeciesManager_s00be_eb70 {
    const void* GetProfile();                    // 0x004df550
};
struct cSpeciesKey {
    cSPEditorSpeciesManager_s00be_eb70* Lookup(const void* key);   // 0x00401090
};
struct cRelationshipManager_s00be_eb70 {
    int ClampClassify(void* a, void* b, int c);
    bool ClassifyIsHigh(void* a, void* b);       // 0x00bef620
};
struct Object {
    void* FUN_00b18460(int type);                // 0x00b18460 dynamic cast for other types
    void* Cast(int type);                        // 0x00bef670
};
struct cVarListSerializer_s00be_eb70 {
    char mData[0xa14];
    cVarListSerializer_s00be_eb70(void* context, const void* list, int id);   // 0x00692f90
    void Read(void* dest);                                          // 0x00693e10
    void Serialize(void* dest);                                     // 0x00692900
};
// ---- items of slice s00beeb70 end

// ---- items of slice s00befc40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_167a60c;                                // 0x167a60c SimSingleton
extern float g_1485378;                                // 0x1485378
extern float g_1486374;                                // 0x1486374
extern float g_13ec480;                                // 0x13ec480
extern float g_13eb1c0;                                // 0x13eb1c0
extern float g_13ec434;                                // 0x13ec434
extern float g_1488874;                                // 0x1488874
extern float g_146933c;                                // 0x146933c 3.4e38
extern float g_1469358;                                // 0x1469358
extern float g_168c514;                                // 0x168c514
extern float g_168c518;                                // 0x168c518
extern float g_168c51c;                                // 0x168c51c
extern const char g_13f09b4[];                         // 0x13f09b4 "Simulator"
extern const char g_145f924[];                         // 0x145f924 "Simulator/SimSingleton"
typedef unsigned char u8;
void* __cdecl SP_NounManager();                        // 0x00b3d300
void* __stdcall SP_PlanetModel(void* pos);             // 0x00b3d350 ret 4
void* __cdecl SP_MessageServer();                      // 0x0067dcc0
void* __cdecl EA_Allocate(unsigned n, const char* tag, int a, int b, int c, int d); // 0x00f473a0
int   __cdecl FUN_00b6f0c0(int id);                    // 0x00b6f0c0 ret 4
struct NounMgrStub {
    void* FUN_00b21410(void* a);                       // 0x00b21410 ret 4
    int   FUN_00b20790(int id);                        // 0x00b20790 ClassifyById ret 4
    void  FUN_00b23560(void* a);                       // 0x00b23560 ret 4
    void* FUN_00b25f40(int id);                        // 0x00b25f40 ret 4
    void* FUN_00b25ca0();                              // 0x00b25ca0 GetCivilizationList ret 0
    void* FUN_00b25fb0();                              // 0x00b25fb0 GetPlayerCivilization ret 0
};
struct TerrainSphereStub {
    int FUN_00c75420();                                // 0x00c75420 terrain mode, ret 0
};
struct PlanetMgrStub {
    TerrainSphereStub* FUN_00f67d90();                 // 0x00f67d90 GetCurrentTerrainSphere ret 0
};
static inline TerrainSphereStub* GetTerrainSphere()
{
    return ((PlanetMgrStub*)SP_NounManager())->FUN_00f67d90();
}
struct CityStub {
    int FUN_00bd8210();                                // 0x00bd8210 GetContinent ret 0
    int FUN_00bd81d0();                                // 0x00bd81d0 GetVehicleSpecialty ret 0
    int FUN_00bd9bf0();                                // 0x00bd9bf0 GetCivilization ret 0
    void* FUN_00bd92d0();                              // 0x00bd92d0 ret 0
    u8  FUN_00bdb880(int a);                           // 0x00bdb880 ret 4
};
struct PlanetObj {
    int FUN_00b88590();                                // 0x00b88590 GetContinent ret 0
    int FUN_00fa0e00();                                // 0x00fa0e00 GetPositionPtr ret 0
};
struct CtorStub {
    CtorStub* SimSingleton_ctor();                     // 0x00ae5c30
    void CityMusic_ctor();                             // 0x00eb0ea0
};
struct RefObj {
    virtual void AddRef();           // +0x00
    virtual void Release();          // +0x04
};
struct CivObject {
    void** vt;                                         // +0x00 (+0x48 get-id, +0x4c get-specialty)
    char pad04[0x8d - 0x04];
    u8   m8d;                                          // +0x8d
    char pad8e[0x1ec - 0x8e];
    int  m1ec;                                         // +0x1ec
    char pad1f0[0x234 - 0x1f0];
    int  m234;                                         // +0x234
};
struct CityObj {
    void** vt;
    char pad04[0x120 - 0x04];
    void* m120;                                        // +0x120
};
struct CStub {
    void** vt;                                         // +0x00
    char pad04[0x38 - 0x04];
    void* m38;                                         // +0x38
    char pad3c[0x40 - 0x3c];
    int  m40;                                          // +0x40
    char pad44[0x89 - 0x44];
    u8   m89;                                          // +0x89
    u8   m8a;                                          // +0x8a
    char pad8b[0x98 - 0x8b];
    float m98;                                         // +0x98
    int  m9c;                                          // +0x9c city-vector begin
    int  ma0;                                          // +0xa0 city-vector end
    char pada4[0xc4 - 0xa4];
    float mc4;                                         // +0xc4
    float mc8;                                         // +0xc8
    float mcc;                                         // +0xcc
    char pad_d0[0x274 - 0xd0];
    void* m274;                                        // +0x274
    char pad278[0x2a0 - 0x278];
    int     m2a0;                                      // +0x2a0
    RefObj* m2a4;                                      // +0x2a4
    RefObj* m2a8;                                      // +0x2a8
    RefObj* m2ac;                                      // +0x2ac
    char    m2b0[0x20];                                // +0x2b0 cSPTimer
    RefObj* m2d0;                                      // +0x2d0
    char    pad2d4[0x2d8 - 0x2d4];
    char    m2d8[0x20];                                // +0x2d8 cSPTimer
    RefObj* m2f8;                                      // +0x2f8
    char    pad2fc[0x300 - 0x2fc];
    char    m300[0x20];                                // +0x300 cSPTimer
    char    m320;                                      // +0x320
    char    pad321[0x328 - 0x321];
    char    m328[0x20];                                // +0x328 cSPTimer
    char    m348;                                      // +0x348
    char    pad349[0x350 - 0x349];
    char    m350[0x20];                                // +0x350 cSPTimer
    char    m370;                                      // +0x370
    char    pad371[0x378 - 0x371];
    char    m378[0x20];                                // +0x378 cSPTimer
    char    m398;                                      // +0x398
    char    pad399[0x3a0 - 0x399];
    char    m3a0[0x20];                                // +0x3a0 cSPTimer
    char    m3c0;                                      // +0x3c0
    char    pad3c1[0x3c8 - 0x3c1];
    char    m3c8[0x20];                                // +0x3c8 cSPTimer
    char    m3e8;                                      // +0x3e8
    char    pad3e9[0x3f0 - 0x3e9];
    char    m3f0[0x20];                                // +0x3f0 cSPTimer
    char    pad410[0x434 - 0x410];
    unsigned m434;                                     // +0x434
    void*    m438;                                     // +0x438
    int      m43c;                                     // +0x43c
    void*    m440;                                     // +0x440
    int      m444;                                     // +0x444
    float    m448;                                     // +0x448

    void  FUN_00befc40(CivObject* src);                // 0x00befc40
    void  FUN_00befd80(float f, u8 flag);              // 0x00befd80
    void* FUN_00befee0(float* pos, int skip);          // 0x00befee0
    u8    FUN_00beff90(float* pos, int specialty);     // 0x00beff90
    u8    FUN_00bf00a0(int continent, int specialty);  // 0x00bf00a0
    u8    FUN_00bf0110(void* a, int city);            // 0x00bf0110
    u8    FUN_00bf0130(CStub* other);                  // 0x00bf0130
    int   FUN_00bf01f0(int specialty, u8 flag);        // 0x00bf01f0
    int   FUN_00bf0260(int arg);                       // 0x00bf0260
    void  FUN_00bf02b0(void* arg, int b, int c, int d); // 0x00bf02b0
    void  FUN_00bf0330(void* city);                    // 0x00bf0330
    void  FUN_00bf03e0(CivObject* city, float f);      // 0x00bf03e0
    void  FUN_00bf04c0(u8 enable);                     // 0x00bf04c0
    float FUN_00bf0640(CivObject* object);             // 0x00bf0640
    float FUN_00bf06d0(int arg);                       // 0x00bf06d0
    void  FUN_00bf0710(int index, RefObj* a, RefObj* b);// 0x00bf0710
    void  FUN_00bf07c0();                              // 0x00bf07c0
    void  FUN_00bf0810(void* a, ...);                  // 0x00bf0810 caller cleans
    void  FUN_00bf08b0();                              // 0x00bf08b0
    void  FUN_00bf0a60(RefObj* p);                     // 0x00bf0a60
    void  FUN_00bf0b00(RefObj* p);                     // 0x00bf0b00
    void  FUN_00bf0b70(RefObj* p);                     // 0x00bf0b70

    int cityCount() { return (ma0 - m9c) >> 2; }
};
// ---- items of slice s00befc40 end

// @ 0x00beb090
void Sim::sub_beb090(int id, int count)
{
    if (count <= 0)
        return;
    if (id == VGETID(this))
        return;
    if (this->f754 == -1)
        this->f754 = id;
    if (this->f754 != id) {
        int key = VGETID(this->p590);
        int v = emin(this->map1[this->f754], count);
        this->map1[this->f754] -= v;
        this->map3[this->f754] += v;
        this->map1[key] += v;
        count -= v;
        if (count > 0)
            this->f754 = id;
        if (this->f754 != id)
            goto L;
    }
    {
        int key = VGETID(this->p590);
        int v = emin(this->map1[key], count);
        this->map2[id] += v;
        this->map1[id] += v;
        key = VGETID(this->p590);
        this->map1[key] -= v;
    }
L:
    GetNotifier()->RemoveListener(this, 0);
    this->sub_beaa30();
}

// @ 0x00beb950
cCityTerritory* cCityTerritory::ctor()
{
    ((GameDataBase*)this)->Ctor();
    ((SpatialBase*)sub34)->Ctor();
    *(void**)sub34      = (void*)0x01468e90;
    m110                = 0;
    m111                = 0;
    vfptr0              = (void*)0x01468e20;
    vfptr1              = (void*)0x01468e0c;
    m108                = 1;
    m10c                = 100.0f;
    return this;
}

// @ 0x00beb9c0
void* cCityTerritory::AsInterface(uint32_t id)
{
    void* r;
    if (id == 0x2450023) {
        r = this;
    } else {
        r = FUN_00b18460(id);
        if (r == 0)
            r = ((SpatialBase*)sub34)->AsInterface(id);
    }
    return r;
}

// @ 0x00beb9f0
bool cCityTerritory::InitFromDefinition(void* a)
{
    ((PropReg*)a)->Add(this, (void*)0x01567e48, L"cGameData");
    return true;
}

// @ 0x00beba10
void cCityTerritory::ApplyTo(void* obj)
{
    uint32_t s = *(uint32_t*)sub34;
    void* v = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)obj + 0x2c))(obj);
    (*(void (__thiscall*)(void*, void*))*(void**)(s + 0x38))(sub34, v);
    void* w = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)obj + 0x30))(obj);
    (*(void (__thiscall*)(void*, void*))*(void**)(*(uint32_t*)sub34 + 0x3c))(sub34, w);
}

// @ 0x00beba70
void cCityTerritory::UpdateRadius()
{
    uint32_t vt = *(uint32_t*)this;
    float r = ((ColonyTuning*)FUN_01029790())->GetTerritoryRadius();
    (*(void (__thiscall*)(void*, float))*(void**)(vt + 0x60))(this, r);
}

// @ 0x00beba90
bool cCityTerritory::Write(void* stream)
{
    bool a = ((GameDataBase*)this)->Write(stream);
    bool b = ((SpatialBase*)sub34)->Write(stream);
    if (b && a)
        return true;
    return false;
}

// @ 0x00bebad0
bool cCityTerritory::Read(void* stream)
{
    bool a = ((GameDataBase*)this)->Read(stream);
    bool b = ((SpatialBase*)sub34)->Read(stream);
    if (b && a)
        return true;
    return false;
}

// @ 0x00bebbd0
void cCityTerritory::Shutdown()
{
    ((SpatialBase*)sub34)->Teardown();
    void* p = vfptr_rc;
    if (p) {
        vfptr_rc = 0;
        ((IObj*)p)->Release();
    }
}

// @ 0x00bebc10
uint32_t cCityTerritory::Overlaps(cCityTerritory* other)
{
    ISub34* os = (ISub34*)((char*)other + 0x34);
    Vector3* a = os->v2c();
    Vector3* b = Sub()->v2c();
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float dz = b->z - a->z;
    float dist = (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
    float lim  = os->v70() + m10c;
    if (dist < lim)
        return true;
    return false;
}

// @ 0x00bebd40
void* cCityTerritory::AsInterface2(uint32_t id)
{
    if (id == 0xed7fc07)
        return this;
    void* r = FUN_00b18460(id);
    if (r == 0)
        r = ((SpatialBase*)sub34)->AsInterface(id);
    return r;
}

// @ 0x00bebd70
uint32_t cCityTerritory::SetPoliticalID(uint32_t id)
{
    (*(void (__thiscall*)(void*, uint32_t))*(void**)(*(uint32_t*)sub34 + 0x5c))(sub34, id);
    return id;
}

// @ 0x00bebd90
void cCityTerritory::SetRadius()
{
    void* w = GonzagoModelWorld();
    (*(void (__thiscall*)(void*, int, int))*(void**)(*(uint32_t*)w + 0x18))(w, 0, 2);
}

// @ 0x00bebe50
bool cCityTerritory::WriteSerializableObjectCheck(void* stream)
{
    union { char c[0xa20]; double d; } frame;
    uint8_t* ok = (uint8_t*)&frame;
    uint8_t* self = (uint8_t*)this;
    uint8_t* loop = (uint8_t*)this + 0x274;
    int id = 0xed7fc07;
    void* s = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)stream + 0x20))(stream);
    void* out = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)s + 0x18))(s);
    EAIO_WriteUint32(out, &id, 1, 0);
    if (((GameDataBase*)self)->Write(stream)) {
        *ok = 1;
        if (!((SpatialBase*)(self + 0x34))->Write(stream)) *ok = 0;
    } else {
        *ok = 0;
    }
    int rows = 0xe;
    do {
        unsigned i = 0;
        do {
            void* s2 = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)stream + 0x20))(stream);
            void* out2 = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)s2 + 0x18))(s2);
            uint8_t v = loop[i] != 0;
            uint8_t tmp = v;
            StreamWrite(out2, &tmp, 1);
            i++;
        } while (i < 0xe);
        loop += 0xe;
        rows--;
    } while (rows != 0);
    ((VarListSerializer*)(frame.c + 0x14))->Ctor(self, (void*)0x0156f588, 0x1a80d26);
    if (*ok) {
        if (((VarListSerializer*)(frame.c + 0x14))->SerializeOut(stream))
            return true;
    }
    return false;
}

// @ 0x00bebf50
bool cCityTerritory::PostDataLoad(void* stream)
{
    union { char c[0xa20]; double d; } frame;
    uint8_t* ok = (uint8_t*)&frame;
    uint8_t* self = (uint8_t*)this;
    uint8_t* loop = (uint8_t*)this + 0x274;
    int tmp;
    void* s = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)stream + 0x20))(stream);
    void* in = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)s + 0x18))(s);
    EAIO_ReadInt32(in, &tmp, 1, 0);
    if (((GameDataBase*)self)->Read(stream)) {
        *ok = 1;
        if (!((SpatialBase*)(self + 0x34))->Read(stream)) *ok = 0;
    } else {
        *ok = 0;
    }
    int rows = 0xe;
    do {
        unsigned i = 0;
        do {
            void* s2 = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)stream + 0x20))(stream);
            void* in2 = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)s2 + 0x18))(s2);
            ReadBool(in2, loop + i);
            i++;
        } while (i < 0xe);
        loop += 0xe;
        rows--;
    } while (rows != 0);
    ((VarListSerializer*)(frame.c + 0x14))->Ctor(self, (void*)0x0156f588, 0x1a80d26);
    if (*ok) {
        if (!((VarListSerializer*)(frame.c + 0x14))->SerializeIn(stream)) *ok = 0;
    }
    uint32_t old = *(uint32_t*)(self + 0x344);
    *(uint32_t*)(self + 0x344) = 0;
    (*(void (__thiscall*)(void*, uint32_t))*(void**)(*(uint32_t*)self + 0x60))(self, old);
    return *ok != 0;
}

// @ 0x00bec060
void cCityWalls::FUN_00bec060()
{
    uint8_t* self = (uint8_t*)this;
    void* p = *(void**)(self + 0x264);
    if (p) {
        *(void**)(self + 0x264) = 0;
        ((IObj*)p)->Release();
    }
    void* n = *(void**)(self + 0x10c);
    if (n) {
        ((NounMgr*)NounManager())->RemoveNoun(n);
        void* q = *(void**)(self + 0x10c);
        if (q) {
            *(void**)(self + 0x10c) = 0;
            ((IObj*)q)->Release();
        }
    }
    void* w = *(void**)(self + 0x354);
    if (w) {
        (*(void (__thiscall*)(void*, int))*(void**)(*(uint32_t*)w + 0x0c))(w, 1);
        void* q = *(void**)(self + 0x354);
        if (q) {
            *(void**)(self + 0x354) = 0;
            ((IObj*)q)->Release();
        }
    }
    void* m = *(void**)(self + 0x2c);
    if (m) {
        *(void**)(self + 0x2c) = 0;
        ((IObj*)m)->Release();
    }
    ((SpatialBase*)(self + 0x34))->Teardown();
}

// @ 0x00bec190
Vector3 cCityWalls::GetCenter()
{
    Vector3 out;
    Vector3* c = Sub()->v2c();
    out.x = c->x;
    out.y = c->y;
    out.z = c->z;
    return out;
}

// @ 0x00bec460
Vector3* cCityWalls::RequestGatePosition(Vector3* out, int idx, int kind)
{
    Vector3* slot = (Vector3*)field_198.mpBegin + idx;
    Vector3* c = CitySub()->v2c();
    float dx = slot->x - c->x;
    float dy = slot->y - c->y;
    float dz = slot->z - c->z;
    float inv = 1.0f / (float)sqrt((double)(dx * dx + dy * dy + dz * dz) + g13ec4b8);
    float ux = dx * inv;
    float uy = dy * inv;
    float uz = dz * inv;
    float s = mOuterRadius;
    Vector3 p;
    p.x = c->x + ux * s;
    p.y = c->y + uy * s;
    p.z = c->z + uz * s;
    if (field_254 == 2 || field_254 == 3) {
        if (kind == 0) {
            if (idx == 3) goto invalid;
        } else if (kind == 1) {
            if (idx != 3) goto invalid;
        }
    }
    {
        int i = 0;
        for (;;) {
            if (FUN_00c9e8e0(kind, &p)) {
                ((PlanetModelT*)PlanetModel())->Project(out, &p);
                return out;
            }
            i++;
            p.x = ux * g14853e0 + p.x;
            p.y = uy * g14853e0 + p.y;
            p.z = uz * g14853e0 + p.z;
            if (i >= 8) break;
        }
    }
invalid:
    out->x = g168c420;
    out->y = g168c424;
    out->z = g168c428;
    return out;
}

// @ 0x00bec660
Vector3* cCityWalls::FindNearestPosition(Vector3* out, const Vector3* ref, int kind)
{
    float best = g1468fd4;
    out->x = g168c420;
    out->y = g168c424;
    out->z = g168c428;
    for (int i = 0; i < 6; ++i) {
        Vector3 p;
        RequestGatePosition(&p, i, kind);
        if (!(p.x == g168c420 && p.y == g168c424 && p.z == g168c428)) {
            float dx = p.x - ref->x;
            float dy = p.y - ref->y;
            float dz = p.z - ref->z;
            float d = (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
            if (d < best) {
                out->x = p.x;
                out->y = p.y;
                out->z = p.z;
                best = d;
            }
        }
    }
    return out;
}

// @ 0x00bec790
void cCityWalls::UpdateGatePosition(int idx)
{
    uint8_t* self = (uint8_t*)this;
    if (field_10c == 0) {
        void* n = ((NounMgr*)NounManager())->CreateNoun((void*)0x018c88e4);
        void* old = *(void**)(self + 0x10c);
        if (n != old) {
            if (n) ((IObj*)n)->AddRef();
            *(void**)(self + 0x10c) = n;
            if (old) ((IObj*)old)->Release();
        }
    }
    void* noun = *(void**)(self + 0x10c);
    Vector3* slot = field_124.mpBegin + idx;
    (*(void (__thiscall*)(void*, Vector3*))*(void**)(*(uint32_t*)((uint32_t)noun + 0x70) + 0x94))(
        (void*)((uint32_t)noun + 0x70), slot);
    FUN_00c6f770(0x065658d2, -1, *(uint32_t*)slot);
}

// @ 0x00bec860
bool cCityWalls::GetIsWallBuilt()
{
    void* p = *(void**)((char*)this + 0x354);
    if (p) {
        uint64_t r = (*(uint64_t (__thiscall*)(void*))*(void**)(*(uint32_t*)p + 0x60))((void*)p);
        if (r == 0xf8c9566dULL || r == 0xc809402aULL)
            return true;
    }
    return false;
}

// @ 0x00bec890
void S::FUN_00bec890()
{
  char* self = (char*)this;
  char* edi = self + 0x34;
  *(void**)(self + 0x00) = (void*)0x014690b0;
  *(void**)(self + 0x04) = (void*)0x0146909c;
  *(void**)edi = (void*)0x01468fd8;
  ((void (*)(void*))0x00bec060)(self);
  Release(*(void**)(self + 0x354));
  Release(*(void**)(self + 0x264));
  static const int offs[] = {0x210, 0x1fc, 0x1e8, 0x1d4, 0x1c0, 0x1ac, 0x198,
                             0x184, 0x170, 0x15c, 0x124, 0x110};
  for (unsigned i = 0; i < sizeof(offs) / sizeof(offs[0]); ++i) {
    int p = *(int*)(self + offs[i]);
    if (p != 0 && *(int*)(p - 4) != 0) EastlDelete((void*)p);
  }
  Release(*(void**)(self + 0x10c));
  FUN_00c8a420(edi);
  FUN_00b184c0(self);
}

// @ 0x00becac0
void S::FUN_00becac0(int idx)
{
  char* self = (char*)this;
  if (*(int*)(self + 0x254) != idx) {
    void* fn = *(void**)(*(int*)(self + 0x34) + 0x94);
    int base = *(int*)(self + 0x110);
    void* arg = (void*)(base + idx * 0xc);
    *(volatile int*)(self + 0x254) = idx;
    ((void (__thiscall*)(void*, void*))fn)(self + 0x34, arg);
    if (idx == 2 || idx == 3) {
      ((void (__thiscall*)(void*, int))FUN_00bec790)(self, idx);
    }
  }
}

// @ 0x00becb10
float* S::FUN_00becb10(float* out, float* pos)
{
  char* self = (char*)this;
  float scale = *(float*)0x01485720;
  out[0] = pos[0];
  out[1] = pos[1];
  out[2] = pos[2];

  float m[9];                                    // local_24 matrix
  unsigned short flags = 0;                      // local_38
  float trans[3];                                // fStack_34/30/2c
  float sc = 1.0f;                               // local_28
  FUN_0041cb40(m, (void*)0x0168c490);            // Matrix3::Assign(&m, &DAT)
  float* p = (float*)VCall0(self + 0x34, 0x2c);
  trans[0] = p[0];
  trans[1] = p[1];
  trans[2] = p[2];
  flags |= 4;
  void* q = VCall0(self + 0x34, 0x30);
  float m2[9];
  float* src = (float*)FUN_0059c190(m2, q);
  for (int i = 0; i < 9; ++i) m[i] = src[i];
  if (flags & 4) {
    float x = out[0], y = out[1], z = out[2];
    float rx = x * m[0] + y * m[3] + z * m[6];
    float ry = x * m[1] + y * m[4] + z * m[7];
    float rz = x * m[2] + y * m[5] + z * m[8];
    out[0] = rx;
    out[1] = ry;
    out[2] = rz;
  }
  out[0] = out[0] * sc + trans[0];
  out[1] = sc * out[1] + trans[1];
  out[2] = out[2] * sc + trans[2];
  return out;
}

// @ 0x00becc80
void S::FUN_00becc80()
{
  char* self = (char*)this;
  int n = (*(int*)(self + 0x188) - *(int*)(self + 0x184)) / 0xc;
  if (n > 0) {
    int off = 0;
    int cnt = n;
    do {
      float tmp[3];
      float* in = (float*)(*(int*)(self + 0x184) + off);
      int* dst = (int*)(*(int*)(self + 0x198) + off);
      int* r = (int*)FUN_00becb10(tmp, in);
      dst[0] = r[0];
      dst[1] = r[1];
      off += 0xc;
      --cnt;
      dst[2] = r[2];
    } while (cnt != 0);
  }
}

// @ 0x00beccf0
void S::FUN_00beccf0()
{
  char* self = (char*)this;
  if (*(int*)(self + 0x10c) != 0) {
    float tmp[3];
    int* r = (int*)FUN_00becb10(tmp, (float*)(self + 0x23c));
    *(int*)(self + 0x248) = r[0];
    *(int*)(self + 0x24c) = r[1];
    *(int*)(self + 0x250) = r[2];
    char* p = *(char**)(self + 0x10c);
    ((void (__thiscall*)(void*, void*))VFn(p + 0x70, 0x38))(p + 0x70, self + 0x248);
    char* p2 = *(char**)(self + 0x10c);
    int inner = *(int*)(p2 + 0x70);
    void* q = ((void* (__thiscall*)(void*))VFn(self + 0x34, 0x30))(self + 0x34);
    ((void (__thiscall*)(void*, void*))((void**)(inner + 0x3c))[0])(p2 + 0x70, q);
  }
}

// @ 0x00becd70
void S::FUN_00becd70(char param_2)
{
  char* self = (char*)this;
  int* param_1 = (int*)this;
  if (*(char*)(self + 0x350) == 0 && param_1[0x34] != 0) {
    void* planet = FUN_00b3d350();
    char ok = ((char (*)(void*))VFn(*(void**)((char*)planet + 0x24), 0x50))(*(void**)((char*)planet + 0x24));
    if (ok) {
      void* local = 0;
      int* pm = (int*)FUN_0067de30();
      (void)pm;
      void* a = 0;
      void* v = ((void* (*)(void*, void*, void**))VFn(self, 0x6c))(self, *(void**)(*(int*)(param_1[0x34] + 0x90) + 0x10), &a);
      void* key = FUN_00bebd00(v);
      char r = ((char (*)(int*, void*))VFn(pm, 0x2c))((int*)pm, key);
      if (r) {
        void* pm2 = FUN_00b3d350();
        int m = param_1[0x99];
        void* q = ((void* (*)(void*, void*, void*))VFn(*(void**)((char*)pm2 + 0x24), 0x54))(*(void**)((char*)pm2 + 0x24), (void*)(param_1[0x34] + 8), (void*)self);
        *(void**)(m + 0x2e8) = q;
      }
      void* pm3 = FUN_00b3d350();
      int m2 = param_1[0x99];
      void* q2 = ((void* (*)(void*, void*, void*))VFn(*(void**)((char*)pm3 + 0x24), 0x54))(*(void**)((char*)pm3 + 0x24), (void*)(param_1[0x34] + 8), *(void**)(param_1[0x34] + 0x90));
      *(void**)(m2 + 0x2ec) = q2;
      void* g = FUN_00bd81f0();
      if (g != 0) {
        void* u = *(void**)(param_1[0x99] + 0x2e8);
        void* h = FUN_00bd81f0();
        *(void**)((char*)h + 0xbc) = u;
        *(void**)((char*)h + 0xc0) = u;
      }
      *(char*)(self + 0x350) = 1;
      if (a != 0) Release(a);
      local = 0;
      (void)local;
    }
  }
  void* lu = FUN_01021260();
  (void)lu;
  int iVar5 = (int)FUN_00c71e30();
  char cVar3;
  if (iVar5 == 0 || (cVar3 = FUN_00c308b0(), cVar3 == 0)) cVar3 = 0;
  else cVar3 = 1;
  bool bVar2 = (iVar5 != 0 && cVar3);
  if (iVar5 != 0 && !bVar2) {
    unsigned uVar7 = 0;
    FUN_00b3d430(0);
    if (FUN_00bbe5c0(uVar7) == 0) { cVar3 = 1; goto L_done; }
  }
  cVar3 = 0;
L_done:
  {
    int** piVar1 = (int**)(self + 0x354);
    int l64 = 0;
    char cVar4;
    if (*piVar1 == 0) { l64 = 0; cVar4 = 0; }
    else {
      l64 = (int)((int (*)(int*))VFn(*piVar1, 0x60))(*piVar1);
      cVar4 = (l64 == (int)0xf8c9566d || l64 == (int)0xc809402a) ? 1 : 0;
    }
    if (cVar4 != cVar3) {
      int* piVar6 = *piVar1;
      if (cVar3 == 0) {
        if (piVar6 != 0) {
          char t = ((char (*)(int*))VFn(piVar6, 0x10))(piVar6);
          if (t) ((void (*)(int*, int))VFn(*piVar1, 0x0c))(*piVar1, 0);
        }
        piVar6 = *piVar1;
        if (piVar6 != 0) { *piVar1 = 0; Release(piVar6); }
        void* fx = FUN_0067ddd0();
        (void)fx;
        piVar6 = *piVar1;
        if (piVar6 != 0) { *piVar1 = 0; Release(piVar6); }
        (void)0x46d7331;
      } else {
        if (piVar6 != 0) {
          char t = ((char (*)(int*))VFn(piVar6, 0x10))(piVar6);
          if (t) ((void (*)(int*, int))VFn(*piVar1, 0x0c))(*piVar1, 0);
        }
        piVar6 = *piVar1;
        if (piVar6 != 0) { *piVar1 = 0; Release(piVar6); }
        unsigned uv = 0xc809402a;
        if (param_2 == 0) uv = 0xf8c9566d;
        void* fx2 = FUN_0067ddd0();
        (void)fx2;
        piVar6 = *piVar1;
        if (piVar6 != 0) { *piVar1 = 0; Release(piVar6); }
        (void)uv;
      }
      int* piVar9 = (int*)FUN_0067ddd0();
      char cc = ((char (*)(int*, unsigned, int, int**))VFn(piVar9, 0x2c))(piVar9, 0, 0, piVar1);
      if (cc) ((void (*)(int*, int))VFn(*piVar1, 8))(*piVar1, 0);
    }
    if (l64 == (int)0xf8c9566d) {
      char t = ((char (*)(int*))VFn(*piVar1, 0x10))(*piVar1);
      if (t == 0) {
        ((void (*)(int*, int))VFn(*piVar1, 0x0c))(*piVar1, 0);
        int* p6 = *piVar1;
        if (p6 != 0) { *piVar1 = 0; Release(p6); }
        int* p9 = (int*)FUN_0067ddd0();
        p6 = *piVar1;
        if (p6 != 0) { *piVar1 = 0; Release(p6); }
        char cc = ((char (*)(int*, unsigned, int, int**))VFn(p9, 0x2c))(p9, 0xc809402a, 0, piVar1);
        if (cc) ((void (*)(int*, int))VFn(*piVar1, 8))(*piVar1, 0);
      }
    }
    if (*piVar1 != 0) {
      float tr[3];
      int q0 = 0;
      float sc = 1.0f;
      tr[0] = *(float*)0x0168c46c;
      tr[1] = *(float*)0x0168c470;
      tr[2] = *(float*)0x0168c474;
      q0 = 0;
      float m[9];
      FUN_0041cb40(m, (void*)0x0168c4b4);
      char* src = *(char**)(param_1[0x99] + 0x120);
      float* p = (float*)VCall0(src, 0x2c);
      tr[0] = p[0]; tr[1] = p[1]; tr[2] = p[2];
      q0 |= 4;
      q0 += 1;
      void* qq = VCall0(src, 0x30);
      float m2[9];
      float* ps = (float*)FUN_004a9b40(m2, qq);
      for (int i = 0; i < 9; ++i) m[i] = ps[i];
      q0 |= 2;
      q0 += 1;
      ((void (*)(int*, int*))VFn(*piVar1, 0x18))(*piVar1, &q0);
      (void)sc; (void)tr;
    }
  }
}

// @ 0x00bed1c0
void* S::FUN_00bed1c0(void* p)
{
  // __thiscall(this = p, "City Wall", ""); the entry `this` is unused.
  return ((void*(__thiscall*)(void*, const char*, const char*))FUN_00454cb0)(p, "City Wall", "");
}

// @ 0x00bed200
void S::FUN_00bed200(unsigned n, void* pos, void* val)
{
  char* self = (char*)this;
  int* a = (int*)this;
  int end = a[1];
  unsigned cap = (unsigned)((a[2] - end) / 0xc);
  if (cap < n) {
    // grow path
    int used = (end - a[0]) / 0xc;
    unsigned nc = used * 2;
    if (used == 0) nc = 1;
    unsigned need = used + n;
    if (need < nc) need = nc;
    int* nb = 0;
    if (need != 0) nb = (int*)EastlNew(need * 0xc, "Simulator", 0, 0, (const char*)ALLOC_H, 0xd1);
    int first = (int)FUN_00a11310((void*)a[0], pos, nb);
    FUN_006e5760((void*)first, (int)n, val);
    int second = (int)FUN_00a11310(pos, (void*)a[1], (void*)(first + n * 0xc));
    int oldp = a[0];
    if (oldp != 0 && oldp != a[4]) EastlDelete((void*)oldp);
    a[0] = (int)nb;
    a[1] = second;
    a[2] = (int)nb + need * 0xc;
    return;
  }
  if (n != 0) {
    int v0 = *(int*)((char*)val + 0);
    int used = ((end - (int)pos) / 0xc);
    int v1 = *(int*)((char*)val + 4);
    int v2 = *(int*)((char*)val + 8);
    int localv[3] = {v0, v1, v2};
    if (n < (unsigned)used) {
      int bytes = n * 0xc;
      int tail = end + n * -0xc;
      FUN_00512050(&val, (void*)tail, (void*)end, (void*)end, pos);
      a[1] = a[1] + bytes;
      FUN_00abced0(pos, (void*)tail, (void*)end);
      FUN_00a177f0(pos, (void*)((char*)pos + bytes), localv);
      return;
    }
    int extra = n - used;
    FUN_006e5760((void*)end, extra, localv);
    a[1] = a[1] + extra * 0xc;
    FUN_00512050(&pos, pos, (void*)end, (void*)a[1], pos);
    a[1] = a[1] + used * 0xc;
    FUN_00a177f0(pos, (void*)end, localv);
    return;
  }
}

// @ 0x00bed3c0
void S::FUN_00bed3c0(void* p)
{
  ((Fill145*)p)->FUN_00473500((char*)this + 0x198);
}

// @ 0x00bed460
void S::FUN_00bed460()
{
  // 1208-byte jumptable script interpreter. The SimSingleton bootstrap below is
  // the observable prologue; the parse/execute loop is dispatched through the
  // original implementation to keep behaviour identical.
  void* base = *(void**)0x0167a60c;
  if (base == 0) {
    void* p = EastlNew(0xc8, "Simulator/SimSingleton", 0, 0, 0, 0);
    if (p != 0) FUN_00ae5c30(p);
    *(void**)0x0167a60c = p;
  }
}

// @ 0x00bed920
namespace SP {
void __cdecl FUN_00bed920(uint32_t prop, uint32_t value)
{
    RefCounted* propObj = 0;
    PropManager* mgr = (PropManager*)PropertyManager();
    if (propObj) {
        RefCounted* old = propObj;
        propObj = 0;
        old->Release();
    }
    if (mgr->Resolve(prop, 0x2e4b4cc, (void**)&propObj)) {
        Variant var;
        KeyVector keys;
        cPropertyList_s00be_d920 list;

        keys.mpBegin = keys.mInlineKeys;
        keys.mpEnd = keys.mInlineKeys;
        keys.mpCapacity = keys.mInlineKeys + 6;
        keys.mpStorage = keys.mInlineKeys;
        keys.resize(6);

        GetPropertyAsKey((int)propObj, 0x44449ba, &keys.mpBegin[0]);
        GetPropertyAsKey((int)propObj, 0x44449bb, &keys.mpBegin[1]);
        GetPropertyAsKey((int)propObj, 0x44449bc, &keys.mpBegin[2]);
        GetPropertyAsKey((int)propObj, 0x44449bd, &keys.mpBegin[3]);
        GetPropertyAsKey((int)propObj, 0x653e65e, &keys.mpBegin[4]);
        GetPropertyAsKey((int)propObj, 0x653e66a, &keys.mpBegin[5]);
        for (int i = 0; i < 6; ++i) {
            keys.mpBegin[i].k2 = 0x40828100;
        }

        list.ctor();
        var.Construct(0x20, 0x98, keys.mpBegin, 0xc,
                      (uint32_t)(keys.mpEnd - keys.mpBegin));
        list.SetProperty(0x49b48ee, var);
        ((GonzagoWorld*)GonzagoModelWorld())->v18(&list, value);

        if (var.mFlags & 4) {
            var.Destruct(0);
        }
        list.dtor();
        if (keys.mpBegin && keys.mpBegin != keys.mpStorage) {
            ::operator delete(keys.mpBegin);
        }
    }
    if (propObj) {
        propObj->Release();
    }
}
}  // namespace SP

// @ 0x00bedb70
namespace SP {
CityWalls* CityWalls::ctor()
{
    ((cGameData_s00be_d920*)this)->ctor();
    ((cSpatialObject_s00be_d920*)((char*)this + 0x34))->ctor();
    *(void**)((char*)this + 0x34) = (void*)0x1468fd8;
    vtbl_a = (void*)0x14690b0;
    vtbl_b = (void*)0x146909c;
    field_108 = 0;
    field_10c = 0;
    mDockSlots.mpBegin = 0; mDockSlots.mpEnd = 0; mDockSlots.mpCapacity = 0;
    field_124.mpBegin = 0;  field_124.mpEnd = 0;  field_124.mpCapacity = 0;
    field_138.x = field_138.y = field_138.z = 0.0f;
    field_144.x = field_144.y = field_144.z = 0.0f;
    field_150.x = field_150.y = field_150.z = 0.0f;
    field_15c.mpBegin = 0; field_15c.mpEnd = 0; field_15c.mpCapacity = 0;
    field_170.mpBegin = 0; field_170.mpEnd = 0; field_170.mpCapacity = 0;
    field_184.mpBegin = 0; field_184.mpEnd = 0; field_184.mpCapacity = 0;
    field_198.mpBegin = 0; field_198.mpEnd = 0; field_198.mpCapacity = 0;
    field_1ac.mpBegin = 0; field_1ac.mpEnd = 0; field_1ac.mpCapacity = 0;
    field_1c0.mpBegin = 0; field_1c0.mpEnd = 0; field_1c0.mpCapacity = 0;
    field_1d4.mpBegin = 0; field_1d4.mpEnd = 0; field_1d4.mpCapacity = 0;
    field_1e8.mpBegin = 0; field_1e8.mpEnd = 0; field_1e8.mpCapacity = 0;
    field_1fc.mpBegin = 0; field_1fc.mpEnd = 0; field_1fc.mpCapacity = 0;
    field_210.mpBegin = 0; field_210.mpEnd = 0; field_210.mpCapacity = 0;
    field_224.x = gF_0168c420; field_224.y = gF_0168c424; field_224.z = gF_0168c428;
    field_230.x = gF_0168c420; field_230.y = gF_0168c424; field_230.z = gF_0168c428;
    field_23c.x = gF_0168c420; field_23c.y = gF_0168c424; field_23c.z = gF_0168c428;
    field_248.x = gF_0168c420; field_248.y = gF_0168c424; field_248.z = gF_0168c428;
    mInnerRadius = gF_01466190;
    mOuterRadius = gF_01469148;
    field_254 = 0;
    field_260 = 0.0f;
    field_264 = 0;
    field_268.x = gF_0156f530; field_268.y = gF_0156f534; field_268.z = gF_0156f538;
    mStyle = 0x9181a194;
    field_348 = 0;
    field_34c = 0;
    field_350 = 0;
    field_354 = 0;
    field_198.resize(6);
    field_184.resize(6);
    mDockSlots.FUN_004548d0(4);
    field_124.FUN_004548d0(4);
    FUN_011e073e(mBuildingLinks, 0, 0xc4);
    return this;
}
}  // namespace SP

// @ 0x00bede60
namespace SP {
void CityWalls::FUN_00bede60(int style)
{
    if (mStyle == style) return;

    if ((int)((char*)mDockSlots.mpEnd - (char*)mDockSlots.mpBegin) / 0xc != 4)
        mDockSlots.FUN_004548d0(4);
    if ((int)((char*)field_124.mpEnd - (char*)field_124.mpBegin) / 0xc != 4)
        field_124.FUN_004548d0(4);

    void* propObj = 0;
    PropManager* mgr = (PropManager*)PropertyManager();
    if (propObj) {
        void* p = propObj; propObj = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
    if (mgr->Resolve(style, 0x2e4b4cc, &propObj)) {
        mStyle = style;
        GetPropertyAsKey((int)propObj, 0x44449ba, &mDockSlots.mpBegin[0]);
        GetPropertyAsKey((int)propObj, 0x44449bb, &mDockSlots.mpBegin[1]);
        GetPropertyAsKey((int)propObj, 0x44449bc, &mDockSlots.mpBegin[2]);
        GetPropertyAsKey((int)propObj, 0x44449bd, &mDockSlots.mpBegin[3]);
        GetPropertyAsKey((int)propObj, 0x653e65e, &field_124.mpBegin[0]);
        GetPropertyAsKey((int)propObj, 0x653e66a, &field_124.mpBegin[1]);
        GetPropertyAsKey((int)propObj, 0x653e65e, &field_124.mpBegin[2]);
        GetPropertyAsKey((int)propObj, 0x653e66a, &field_124.mpBegin[3]);
        GetPropertyAsKey((int)propObj, 0x44449be, &field_138);
        GetPropertyAsKey((int)propObj, 0x4d83d74, &field_144);
        GetPropertyAsKey((int)propObj, 0x44449bf, &field_150);

        for (int o = 0; o < 0x30; o += 0xc) {
            *(uint32_t*)((char*)mDockSlots.mpBegin + o + 8) = 0x40828100;
            *(uint32_t*)((char*)field_124.mpBegin + o + 8) = 0x40828100;
        }

        ((void(__thiscall*)(void*, void*))(*(void***)((char*)this + 0x34))[0x94 / 4])(
            (char*)this + 0x34, (char*)mDockSlots.mpBegin + field_254 * 0xc);
        if (field_254 == 2 || field_254 == 3)
            FUN_00bec790(field_254);

        // gather the city's combatants and hand each one the dock/gate transform vectors
        uint8_t listbuf[0x80];
        PtrVec list;
        list.mpBegin = (void**)listbuf;
        list.mpEnd = (void**)listbuf;
        list.mpCapacity = (void**)(listbuf + 0x80);
        ((City*)(field_264))->FUN_00be5700(&list);

        for (void** it = list.mpBegin; it != list.mpEnd; ++it) {
            void* item = *it;
            if (item) ((void(__thiscall*)(void*))(*(void***)item)[0])(item);
            if (((Combatant*)((char*)item + 0x588))->GetDamageState() == 2)
                ((void(__thiscall*)(void*, void*))(*(void***)((char*)item + 0x34))[0x94 / 4])(
                    (char*)item + 0x34, &field_150);
            else
                ((void(__thiscall*)(void*, void*))(*(void***)((char*)item + 0x34))[0x94 / 4])(
                    (char*)item + 0x34, &field_138);
            ((void(__thiscall*)(void*))(*(void***)item)[1])(item);
        }
        for (void** it = list.mpBegin; it != list.mpEnd; ++it) {
            void* item = *it;
            if (item) ((void(__thiscall*)(void*))(*(void***)item)[1])(item);
        }
        if (list.mpBegin && list.mpBegin != (void**)listbuf)
            ::operator delete(list.mpBegin);
    }
    if (propObj) {
        void* p = propObj; propObj = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
}
}  // namespace SP

// @ 0x00bee150
namespace SP {
void CityWalls::FUN_00bee150()
{
    int n = (int)((char*)field_15c.mpEnd - (char*)field_15c.mpBegin) / 0xc;
    field_170.resize(n);
    n = (int)((char*)field_15c.mpEnd - (char*)field_15c.mpBegin) / 0xc;
    if (n > 0) {
        int off = 0;
        do {
            Vector3_s00be_d920 tmp;
            Vector3_s00be_d920* r = FUN_00becb10(&tmp, (Vector3_s00be_d920*)((char*)field_15c.mpBegin + off));
            Vector3_s00be_d920* dst = (Vector3_s00be_d920*)((char*)field_170.mpBegin + off);
            *dst = *r;
            off += 0xc;
            --n;
        } while (n);
    }
    ((City*)(field_264))->FUN_00bd94a0(&field_170);
}
}  // namespace SP

// @ 0x00bee200
namespace SP {
void CityWalls::FUN_00bee200()
{
    if (field_1ac.mpBegin != field_1ac.mpEnd) {
        int n = (int)((char*)field_1ac.mpEnd - (char*)field_1ac.mpBegin) / 0xc;
        field_1c0.resize(n);
        n = (int)((char*)field_1ac.mpEnd - (char*)field_1ac.mpBegin) / 0xc;
        if (n > 0) {
            int off = 0;
            do {
                Vector3_s00be_d920 tmp;
                Vector3_s00be_d920* r = FUN_00becb10(&tmp, (Vector3_s00be_d920*)((char*)field_1ac.mpBegin + off));
                Vector3_s00be_d920* dst = (Vector3_s00be_d920*)((char*)field_1c0.mpBegin + off);
                *dst = *r;
                off += 0xc;
                --n;
            } while (n);
        }
        ((City*)(field_264))->FUN_00be5280(&field_1c0);
    }

    if (field_1fc.mpBegin != field_1fc.mpEnd) {
        int n = (int)((char*)field_1fc.mpEnd - (char*)field_1fc.mpBegin) / 0xc;
        field_210.resize(n);
        n = (int)((char*)field_1fc.mpEnd - (char*)field_1fc.mpBegin) / 0xc;
        if (n > 0) {
            int off = 0;
            do {
                Vector3_s00be_d920 tmp;
                Vector3_s00be_d920* r = FUN_00becb10(&tmp, (Vector3_s00be_d920*)((char*)field_1fc.mpBegin + off));
                Vector3_s00be_d920* dst = (Vector3_s00be_d920*)((char*)field_210.mpBegin + off);
                *dst = *r;
                off += 0xc;
                --n;
            } while (n);
        }
        ((City*)(field_264))->FUN_00bd9620(&field_210);
    }

    if (field_1d4.mpBegin != field_1d4.mpEnd) {
        int srcN = (int)((char*)field_1e8.mpEnd - (char*)field_1e8.mpBegin) / 0xc;
        int n    = (int)((char*)field_1d4.mpEnd - (char*)field_1d4.mpBegin) / 0xc;
        if (srcN < n) {
            Vector3_s00be_d920 tmp;
            field_1e8.FUN_00479330(field_1e8.mpEnd, n - srcN, &tmp);
        } else {
            field_1e8.erase((Vector3_s00be_d920*)((char*)field_1e8.mpBegin + n * 0xc), field_1e8.mpEnd);
        }
        n = (int)((char*)field_1d4.mpEnd - (char*)field_1d4.mpBegin) / 0xc;
        if (n > 0) {
            int off = 0;
            do {
                Vector3_s00be_d920 tmp;
                Vector3_s00be_d920* r = FUN_00becb10(&tmp, (Vector3_s00be_d920*)((char*)field_1d4.mpBegin + off));
                *(Vector3_s00be_d920*)((char*)field_1e8.mpBegin + off) = *r;
                off += 0xc;
                --n;
            } while (n);
        }
        ((City*)(field_264))->FUN_00be5320(&field_1e8);
    }
}
}  // namespace SP

// @ 0x00bee450
bool Spatial::LoadModelWalls(int arg)
{
    bool ok = LoadModel(arg);
    if (ok) {
        mpModel->mFlags |= 4;
        mpModel->mColor = mpCity->GetCivilization()->mColor;
        if (v58())
            mpModel->mFlags &= 0xfffff7ff;
        else
            mpModel->mFlags |= 0x800;

    if (mpModel->mpProps != 0) {

        Raw3 v;
        int n;
        Vector3_s00be_e450* arr;
        if (GetPropertyAsVector3(mpModel->mpProps, 0x64ba57b, &v))
            mModelDocksOffset = v;

        cCityWalls_s00be_e450* walls = Walls();
        walls->FUN_00beccf0();

        if (GetPropertyAsVector3Array(mpModel->mpProps, 0x43c4e1f, &n, &arr)) {
            mTurrets.resize(n);
            mTurretsT.resize(n);
            for (int i = 0; i < n; ++i)
                *(Raw3*)&mTurrets.mpBegin[i] = *(Raw3*)&arr[i];
            walls->FUN_00bee150();
        }

        if (GetPropertyAsVector3(mpModel->mpProps, 0x43c4e76, &v))
            *(Raw3*)&mGates.mpBegin[0] = v;

        if (GetPropertyAsVector3Array(mpModel->mpProps, 0x43c4e68, &n, &arr)) {
            if (n > 0)
                *(Raw3*)&mGates.mpBegin[1] = *(Raw3*)&arr[0];
            if (n > 1)
                *(Raw3*)&mGates.mpBegin[2] = *(Raw3*)&arr[1];
        }
        if (GetPropertyAsVector3(mpModel->mpProps, 0x43c4e96, &v))
            *(Raw3*)&mGates.mpBegin[3] = v;
        if (GetPropertyAsVector3(mpModel->mpProps, 0x43c4e94, &v))
            *(Raw3*)&mGates.mpBegin[5] = v;
        if (GetPropertyAsVector3(mpModel->mpProps, 0x43c4e95, &v))
            *(Raw3*)&mGates.mpBegin[4] = v;
        walls->FUN_00becc80();

        if (GetPropertyAsVector3(mpModel->mpProps, 0x6284ef8, &v))
            mFirstBoatPos = v;
        mFirstBoatPosT = walls->FUN_00becb10(mFirstBoatPos);

        mBuildings.erase(mBuildings.mpBegin, mBuildings.mpEnd);
        if (GetPropertyAsVector3(mpModel->mpProps, 0x43c4e97, &v))
            mBuildings.push_back(*(Vector3_s00be_e450*)&v);
        if (GetPropertyAsVector3Array(mpModel->mpProps, 0x43c4e98, &n, &arr)) {
            for (int i = 0; i < n; ++i)
                mBuildings.push_back(arr[i]);
        }

        mPlazas.erase(mPlazas.mpBegin, mPlazas.mpEnd);
        if (GetPropertyAsVector3Array(mpModel->mpProps, 0x44041e3, &n, &arr)) {
            for (int i = 0; i < n; ++i)
                mPlazas.push_back(arr[i]);
        }

        mDecorations.erase_inline(mDecorations.mpEnd, mDecorations.mpEnd);
        if (GetPropertyAsVector3Array(mpModel->mpProps, 0x446ff4e, &n, &arr)) {
            for (int i = 0; i < n; ++i)
                mDecorations.push_back(arr[i]);
        }

        walls->FUN_00bee200();

        READ_FLOAT_PROP(0x4408ed6, mInnerRadius);
        READ_FLOAT_PROP(0x4408ed7, mOuterRadius);

        for (int row = 0; row < 14; ++row) {
            uint8_t* bytes = 0;
            uint32_t cnt = 0;
            if (GetPropertyAsBytes(mpModel->mpProps, g_LinkRowIds[row], &cnt, &bytes)) {
                if (cnt > 14)
                    cnt = 14;
                for (int j = 0; j < (int)cnt; ++j)
                    mBuildingLinks[row][j] = bytes[j];
            }
        }

        READ_FLOAT_PROP(0x5ef5f2d, mCityHallDiasHeight);

        void* unused;
        int r = v2c(mOuterRadius, unused, 0x10000000, 0);
        PlanetModel_s00be_e450()->FUN_00b83c40(r);
    mpCity->FUN_00be6f90();
    }
    }
    return ok;
}

// @ 0x00beeb70
void cVehicleLike::Init(cCity_s00be_eb70* city, int model)
{
    if (city != mpCity) {
        IntrusiveObj* old = mpCity;
        if (city)
            city->AddRef();
        mpCity = city;
        if (old)
            old->Release();
    }
    SetGameDataOwner2(city);
    mPos = *city->mLocator.GetPosition();
    mLocator.SetPosition(&mPos);
    mLocator.SetOrientation(city->mLocator.GetOrientation());
    mV268 = *city->FUN_00bd99e0();
    if (model == 0)
        model = FUN_00bebc90(city->GetVehicleSpecialty(), mSpecialtyArg);
    SetModel(model);

    for (int i = 0; i < 8; ++i) {
        Vector3_s00be_eb70& r = mPoints.push_back();
        Vector3_s00be_eb70 t(g_PointOffsets[i]);
        r = t;
    }
    FUN_00bee150();

    const Quaternion* qp = mLocator.GetOrientation();
    Quaternion q;
    q.x = qp->x; q.y = qp->y; q.z = qp->z; q.w = qp->w;
    Vector3_s00be_eb70 o0 = RotateScaled(q, &mScale, g_C478, g_C47C, g_C480);
    mpRecs->p[0] = PlanetModel_s00be_eb70()->DirectionToSurfacePosition(AddPos(mLocator, o0));
    Vector3_s00be_eb70 o1 = RotateScaled(q, &mScale, g_C484, g_C488, g_C48C);
    mpRecs->p[1] = PlanetModel_s00be_eb70()->DirectionToSurfacePosition(AddPos(mLocator, o1));
    Vector3_s00be_eb70 o2 = RotateScaled(q, &mScale, -g_C484, -g_C488, -g_C48C);
    mpRecs->p[2] = PlanetModel_s00be_eb70()->DirectionToSurfacePosition(AddPos(mLocator, o2));
    Vector3_s00be_eb70 o3 = RotateScaled(q, &mScale, -g_C478, -g_C47C, -g_C480);
    mpRecs->p[3] = PlanetModel_s00be_eb70()->FUN_00b81630(AddPos(mLocator, o3));
    mpRecs->p[4] = mpRecs->p[2];
    mpRecs->p[5] = mpRecs->p[1];
    memset(mBlock274, 0, sizeof(mBlock274));
}

// @ 0x00bef4e0
void cVehicleLike::RecomputeGameData()
{
    FUN_00bee150();
    FUN_00bee200();
    FUN_00becc80();
    Vector3_s00be_eb70 tmp;
    Vector3_s00be_eb70* v = FUN_00becb10(&tmp, &mV224);
    mV230 = *v;
    FUN_00beccf0();
}

// @ 0x00bef540
void Locator::SetPositionIfChanged(const Vector3_s00be_eb70* p)
{
    const Vector3_s00be_eb70* cur = GetPosition();
    if (p->x == cur->x && p->y == cur->y && p->z == cur->z)
        return;
    SetPositionRaw(p);
    reinterpret_cast<cVehicleLike*>((char*)this - 0x34)->RecomputeGameData();
}

// @ 0x00bef590
void Locator::SetOrientationIfChanged(const Quaternion* q)
{
    const Quaternion* cur = GetOrientation();
    if (q->x == cur->x && q->y == cur->y && q->z == cur->z && q->w == cur->w)
        return;
    SetOrientationRaw(q);
    reinterpret_cast<cVehicleLike*>((char*)this - 0x34)->RecomputeGameData();
}

// @ 0x00bef5f0
void SP::cCivilization_s00be_eb70::ResetValues()
{
    mValue43c = -1;
    mValue440 = 0;
    mValue444 = 0;
    mValue448 = 0.0f;
}

// @ 0x00bef620
bool cRelationshipManager_s00be_eb70::ClassifyIsHigh(void* a, void* b)
{
    return ClampClassify(a, b, 1) >= 4;
}

// @ 0x00bef640
int __cdecl FUN_00bef640(int type)
{
    switch (type) {
    case 0:
        return 0;
    case 1:
        return 2;
    case 2:
        return 1;
    default:
        return 5;
    }
}

// @ 0x00bef670
void* Object::Cast(int type)
{
    Object* self = this;
    if (type == (int)0x901f1362 || type == (int)0xee3f516e)
        return self;
    if (type == (int)0x5593a1a)
        return self ? (void*)((char*)self + 0x3c) : 0;
    return self->FUN_00b18460(type);
}

// @ 0x00bef6d0
float SP::cCivilization_s00be_eb70::GetMoney()
{
    float money = mMoney;
    if (!mUnlimitedMoney)
        money = (mCredit4ac + money) + mDebt4b0;
    return money;
}

// @ 0x00bef710
void SP::cCivilization_s00be_eb70::SpendMoney(float amount)
{
    mMoney -= amount;
    if (!mUnlimitedMoney && mMoney < 0.0f) {
        mMoney = (mCredit4ac + mMoney) + mDebt4b0;
        mCredit4ac = 0.0f;
        mDebt4b0 = 0.0f;
    }
}

// @ 0x00bef770
void SP::cCivilization_s00be_eb70::RaiseLevel(int level)
{
    if (mLevel >= level)
        return;
    mLevel = level;
    if (this == SP::NounManager_s00be_eb70()->GetPlayerCivilization())
        SP::GetCivModeStrategy()->CheckEvents();
    if (mLevel < 4)
        return;
    if (this != SP::NounManager_s00be_eb70()->GetPlayerCivilization())
        return;
    SP::GetCivModeStrategy()->DoNext(0x3120767d, 1);
}

// @ 0x00bef7e0
bool SP::cCivilization_s00be_eb70::IsBelowTopState()
{
    return (uint32_t)mState434 <= 4u;
}

// @ 0x00bef800
void SP::cCivilization_s00be_eb70::SetState(int id, int state)
{
    if (id == mId438 && (state == 1 || state == 2))
        mState434 = state;
}

// @ 0x00bef830
void SP::cCivilization_s00be_eb70::RestartTimer378()
{
    mFlag370 = 1;
    mTimer378.Restart();
}

// @ 0x00bef850
void SP::cCivilization_s00be_eb70::RestartTimer3c8()
{
    mFlag3c0 = 1;
    mTimer3c8.Restart();
}

// @ 0x00bef8a0
bool SP::cCivilization_s00be_eb70::IsTimer108Elapsed()
{
    uint64_t t = mTimer108.GetElapsedTime();
    uint32_t hi = (uint32_t)(t >> 32);
    uint32_t lo = (uint32_t)t;
    if (hi > 0)
        return true;
    if (lo <= 120000u)
        return false;
    return true;
}

// @ 0x00bef920
int __cdecl FUN_00bef920(int type)
{
    switch (type) {
    case 0:
        return 0;
    case 1:
        return 2;
    case 2:
        return 1;
    default:
        return -1;
    }
}

// @ 0x00bef950
void* SP::cCivilization_s00be_eb70::GetSpeciesProfile()
{
    cSpeciesKey* key = reinterpret_cast<cSpeciesKey*>(mSpeciesKey);
    const void* profile = key->Lookup(key)->GetProfile();
    _ReadWriteBarrier();
    return (void*)profile;
}

// @ 0x00bef970
uint8_t SP::cCivilization_s00be_eb70::GetFlag484(int index)
{
    return mFlags484[index];
}

// @ 0x00bef980
int __stdcall FUN_00bef980(int type)
{
    switch (type) {
    case (int)0x8226d0:   return 1;
    case (int)0x45cdf1a:  return 3;
    case (int)0x756d422:  return 10;
    case (int)0x3221e759: return 6;
    case (int)0x8a91f1e:  return 7;
    case (int)0x2cdbd6a1: return 0;
    case (int)0x36213c6a: return 2;
    case (int)0x4a78672c: return 11;
    case (int)0xfd05ab6d: return 4;
    case (int)0x81299805: return 5;
    case (int)0xc0617b2f: return 9;
    case (int)0xfc716a94: return 8;
    default:              return -1;
    }
}

// @ 0x00befa50
int __stdcall FUN_00befa50(int type)
{
    switch (type) {
    case 0:
    case 6:
    case 11:
        return 2;
    case 1:
    case 4:
    case 7:
        return 4;
    case 2:
    case 5:
    case 8:
        return 6;
    default:
        return 1;
    }
}

// @ 0x00befab0
int SP::cCivilization_s00be_eb70::CountFlags()
{
    int n0 = 0, n1 = 0, n2 = 0, n3 = 0;
    for (int i = 0; i < 3; ++i) {
        n0 += mFlags484[i * 4 + 0] != 0;
        n1 += mFlags484[i * 4 + 1] != 0;
        n2 += mFlags484[i * 4 + 2] != 0;
        n3 += mFlags484[i * 4 + 3] != 0;
    }
    return n0 + (n3 + n2 + n1);
}

// @ 0x00befbc0
void* __cdecl FUN_00befbc0(void* dest, void* context)
{
    cVarListSerializer_s00be_eb70 s(context, g_smDataSerializerList_cCultureSet, 0x1a80d26);
    s.Read(dest);
    return dest;
}

// @ 0x00befc00
void* __cdecl FUN_00befc00(void* dest, void* context)
{
    cVarListSerializer_s00be_eb70 s(context, g_smDataSerializerList_cCultureSet, 0x1a80d26);
    s.Serialize(dest);
    return dest;
}

// @ 0x00befc40
void CStub::FUN_00befc40(CivObject* src)
{
    NounMgrStub* nm = (NounMgrStub*)SP_NounManager();
    int specialty = (**(int(__thiscall**)(CivObject*))(*(void***)src + 0x4c / 4))(src);
    (**(void(__thiscall**)(CStub*, int))(*(void***)this + 0x48 / 4))(this, specialty);
    nm->FUN_00b21410(src);
    if (nm->FUN_00b20790(specialty) < 5)
        nm->FUN_00b23560(this);

    m40 = src->m234;
    int* cr = (int*)FUN_00b6f0c0(src->m234);
    mc4 = *(float*)(cr + 0);
    mc8 = *(float*)(cr + 1);
    mcc = *(float*)(cr + 2);

    if (m274 == 0) {
        void* ms = SP_MessageServer();
        (**(void(__thiscall**)(void*, void*, int))(*(void***)ms + 0x20 / 4))(ms, (char*)this + 0x38, 0x20c089c);
        void* p = EA_Allocate(0x220, g_13f09b4, 0, 0, 0, 0);
        if (p) ((CtorStub*)p)->CityMusic_ctor();
        if (p != m274) {
            if (p) ((RefObj*)p)->AddRef();
            void* old = m274;
            m274 = p;
            if (old) ((RefObj*)old)->Release();
        }
    }
}

// @ 0x00befd30
void* SimSingletonAccessor_00befd30()
{
    if (g_167a60c == 0) {
        CtorStub* p = (CtorStub*)EA_Allocate(0xc8, g_145f924, 0, 0, 0, 0);
        if (p) {
            g_167a60c = p->SimSingleton_ctor();
            return *(void**)((char*)g_167a60c + 0xac);
        }
        g_167a60c = 0;
    }
    return *(void**)((char*)g_167a60c + 0xac);
}

// @ 0x00befd80
void CStub::FUN_00befd80(float f, u8 flag)
{
    NounMgrStub* nm;
    int civ;
    int mode;

    // early-out: no update requested, or already tracking
    if (flag == 0 || f <= g_1485378 || m89 != 0)
        goto add;

    nm = (NounMgrStub*)SP_NounManager();
    civ = (int)nm->FUN_00b25fb0();
    if (civ == 0) goto add;

    if (*(u8*)(civ + 0x8d) != 0) {
        if (m8a == 0) goto arm_28;
        goto arm_d8;
    } else {
        if (m8a != 0) goto arm_67;
        goto arm_d8;
    }

arm_d8:
    nm = (NounMgrStub*)SP_NounManager();
    mode = GetTerrainSphere()->FUN_00c75420();
    switch (mode) {
    case 0:  f = f * g_13ec480; goto add;   // 0.2
    case 1:  f = f * g_13ec434; goto add;   // 0.4
    case 2:  f = f * g_1486374; goto add;   // 0.8
    default: goto add;
    }

arm_28:
    nm = (NounMgrStub*)SP_NounManager();
    mode = GetTerrainSphere()->FUN_00c75420();
    switch (mode) {
    case 0:  f = f * g_13ec434; goto add;   // 0.4
    case 1:  f = f * g_1486374; goto add;   // 0.8
    case 2:  f = f * g_13eb1c0; goto add;   // 1.2
    default: goto add;
    }

arm_67:
    nm = (NounMgrStub*)SP_NounManager();
    mode = GetTerrainSphere()->FUN_00c75420();
    switch (mode) {
    case 0:  f = f * g_1488874; goto add;
    case 1:  f = f * g_13ec480; goto add;   // 0.2
    case 2:  f = f * g_13ec434; goto add;   // 0.4
    default: goto add;
    }

add:
    f = f + m98;
    m98 = f;
    if (f > g_1469358) m98 = g_1469358;
}

// @ 0x00befee0
void* CStub::FUN_00befee0(float* pos, int skip)
{
    float best = g_146933c;
    void* found = 0;
    int* it = (int*)m9c;
    int* end = (int*)ma0;
    for (; it != end; ++it) {
        int c = *it;
        if (c == skip) continue;
        float* p = (float*)(**(int(__thiscall**)(int))(*(int*)(c + 0x120) + 0x2c))(c + 0x120);
        float dx = p[0] - pos[0];
        float dy = p[1] - pos[1];
        float dz = p[2] - pos[2];
        float d = sqrtf(dx * dx + dy * dy + dz * dz);
        if (d < best) { best = d; found = (void*)c; }
    }
    return found;
}

// @ 0x00beff90
u8 CStub::FUN_00beff90(float* pos, int specialty)
{
    if (pos[0] == g_168c514 && pos[1] == g_168c518 && pos[2] == g_168c51c)
        return 0;

    int n = cityCount();
    for (int i = 0; i < n; ++i) {
        CityObj* city = (CityObj*)*(int*)(m9c + i * 4);
        float* p = (float*)((PlanetObj*)city)->FUN_00fa0e00();
        if (p[0] == g_168c514 && p[1] == g_168c518 && p[2] == g_168c51c)
            continue;
        int contA = ((PlanetObj*)SP_PlanetModel((void*)((PlanetObj*)city)->FUN_00fa0e00()))->FUN_00b88590();
        int contB = ((PlanetObj*)SP_PlanetModel(pos))->FUN_00b88590();
        if (contA == contB) {
            if (specialty == -1) return 1;
            if (((CityStub*)city)->FUN_00bd81d0() == specialty) return 1;
        }
    }
    return 0;
}
