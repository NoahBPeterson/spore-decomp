// src/game/SPGonzago/_at_00c80000.cpp -- migrated from slice(s) s00c8c9d0, s00c8bb00, s00c88e30, s00c87be0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00c80000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cViewer.h"
#include "SP/cCommunity.h"
#include "SP/cGameData.h"
#include "SP/cISerializableObject.h"
#include "SP/cSpatialObject.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* memcpy(void*, const void*, unsigned int);
#include <math.h>
#include <intrin.h>
#include "SP/cBuilding.h"
#include "SP/cCombatant.h"
#include "SP/cStar.h"
#include "SP/cString.h"
#include "SP/cTribe.h"
#include <string.h>
#include "SP/cCity.h"
#include "SP/cCivData.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanet.h"
#include "SP/cStarManager.h"
#include "SP/cTerrainSphere.h"
#include "SP/cTotemPole.h"

// ---- items of slice s00c87be0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Ser {
    char pad00[0xbc];
    int  mBC;   // 0xbc
    void Inc(int a);
    void Dec(int a);
};
struct VObj84 {
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
};
struct SpatialA {
    char    pad00[0x64];
    float   f64;   // 0x64
    char    pad68[0x76 - 0x68];
    uint8_t b76;   // 0x76
    char    pad77[0x7c - 0x77];
    float   f7c;   // 0x7c
    char    pad80[0x88 - 0x80];
    float   f88;   // 0x88
    char    pad8c[0xa6 - 0x8c];
    uint8_t bA6;   // 0xa6
    uint8_t bA7;   // 0xa7
    void SetValue(float v);
    void Sync(int v);
    void MaybeCall();
};
struct ObjA0 {
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
virtual void v48();
virtual void v49();
virtual void v50();
virtual void v51();
virtual void v52();
virtual void v53();
virtual void v54();
virtual void v55();
virtual void v56();
virtual void v57();
virtual void v58();
virtual void v59();
virtual void v60();
virtual void v61();
virtual void v62();
virtual void v63();
virtual void v64();
virtual void v65();
virtual void v66();
virtual void v67();
virtual void v68();
virtual void v69();
virtual void v70();
virtual void v71();
virtual void v72();
virtual void v73();
virtual void v74();
virtual void v75();
virtual void v76();
virtual void v77();
virtual void v78();
virtual void v79();
virtual void v80();
virtual void v81();
virtual void v82();
virtual void v83();
virtual void v84();
virtual void v85();
virtual void v86();
virtual void v87();
    virtual void v88();
    virtual void v89();
};
struct GameData {
    char    pad00[0x68];
    float   f68;    // 0x68
    char    pad6c;
    uint8_t m6d;    // 0x6d
    char    pad6e[0x76 - 0x6e];
    uint8_t b76;    // 0x76
    char    pad77[0x9c - 0x77];
    char*   mp9c;   // 0x9c
    void*   mpA0;   // 0xa0
    char    padA4[0xc0 - 0xa4];
    char*   mpBegin; // 0xc0
    char*   mpEnd;   // 0xc4

    void RemoveOwner(bool b);
    float GetValue();
    int  HasFlag();
    int  FindEntry(int id);
    bool HasEffect(int id);
};
struct EffObj3 { virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(int a); };
struct EffObj17 {
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
    virtual void v17(int a, int* b, int c);
};
struct Effects {
    char  pad00[0xc0];
    char* mpBegin;   // 0xc0
    char* mpEnd;     // 0xc4
    int   F40(int id);
    void  StartEffect(int id, int b);
    void  StopEffect(int id, int a);
    void  F00(int id, float v);
    void  F30(int id, int* v);
};
struct VObj8c {
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
    virtual void v8c(int a);
};
struct SpatialModel {
    char     pad00[0x90];
    uint32_t m90;   // 0x90
    uint32_t m94;   // 0x94
    uint32_t m98;   // 0x98
    void SetModelKey3(uint32_t* key);
};
void* SP_PlanetModel();            // 0x00b3d350
void* FUN_00b3d310(void* self);    // 0x00b3d310
struct PlanetCall { void v(); };   // 0x00b3e810
struct SpatialPos {
    char  pad00[4];
    float x;   // 0x04
    float y;   // 0x08
    float z;   // 0x0c
    void Fn();
};
struct VecThing {
    char     pad00[4];
    float    x;    // 0x04
    float    y;    // 0x08
    float    z;    // 0x0c
    float    w;    // 0x10
    float    x2;   // 0x14
    float    y2;   // 0x18
    float    z2;   // 0x1c
    char     pad20[0x50 - 0x20];
    uint32_t f50;  // 0x50
    char     pad54[0x74 - 0x54];
    uint8_t  b74;  // 0x74
    void Set3(float* v);
    void Set4(float* v);
};
extern "C" void* memcpy(void*, const void*, unsigned int);
struct VObj174 {
virtual void     v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void     v010();
virtual void v014();
virtual VObj174* v018();
virtual VObj174* v01c();
virtual VObj174* v020();
virtual void v024();
virtual void v028();
virtual float* v02c();
virtual void     v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void     v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual VObj174* v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void     v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void     v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void     v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual bool     v090(void** out);
virtual void v094();
virtual bool v098(void* r);
virtual void v09c();
virtual void     v0a0();
virtual void v0a4();
virtual void v0a8();
virtual unsigned int v0ac();
virtual void     v0b0();
virtual void v0b4();
virtual VObj174* v0b8(uint32_t id, uint32_t arg);
virtual bool     v0bc();
virtual void v0c0();
virtual void v0c4();
    void GetCameraLocationInfo(void* pos, void* a, void* b, void* c);   // 0x007c3d30
};
void* __stdcall FUN_00b3d310_sc(void* self);    // 0x00b3d310
void  __fastcall FUN_00b48770_tc(void* self);   // 0x00b48770
namespace EA {
namespace IO {
bool WriteUint32(void* pStream, const uint32_t* pData, uint32_t nCount, int endian);  // 0x0093aa70
}
}
namespace EA {
namespace IO {
bool ReadInt32(void* pStream, uint32_t* pData, uint32_t nCount, int endian);          // 0x0093a780
}
}
struct cCommunity {
virtual void     c000();
virtual void c004();
virtual void c008();
virtual void c00c();
virtual void     c010();
virtual void c014();
virtual void c018();
virtual void c01c();
virtual void     c020();
virtual void c024();
virtual void c028();
virtual void c02c();
virtual void     c030();
virtual void c034();
virtual void c038(uint32_t a);
virtual void c03c(uint32_t a);
virtual void     c040();
virtual void c044();
virtual void c048();
virtual void c04c();
virtual void     c050();
virtual void c054();
virtual void c058();
virtual void c05c();
virtual void     c060();
virtual void c064(void* p, float value);
virtual void c068();
virtual void     c06c();
virtual void c070();
virtual void c074();
virtual void c078();
virtual void     c07c();
virtual void c080();
virtual void c084();
virtual void c088();
virtual void     c08c();
virtual void c090();
virtual void c094();
virtual void c098();
virtual void     c09c();
virtual void c0a0();
virtual void c0a4();
virtual void c0a8();
virtual void     c0ac();
virtual void c0b0();
virtual void c0b4();
virtual VObj174* c0b8(uint32_t a, uint32_t b);

    char     pad04[0x20 - 0x04];
    char     m20;                       // 0x20
    char     pad21[0x50 - 0x21];
    uint32_t mFlags50;                  // 0x50
    char     pad54[0x64 - 0x54];
    float    m64;                       // 0x64
    char     pad68[0x74 - 0x68];
    uint8_t  m74;                       // 0x74
    char     pad75[0x7c - 0x75];
    float    m7c;                       // 0x7c

    void func5Ch(float value);
    void func60h(uint32_t a, uint32_t b);
};
// ---- items of slice s00c87be0 end

// ---- items of slice s00c88e30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; };
struct Transform;
struct cSPVector3_s00c8_8e30 {
    float x, y, z;
    cSPVector3_s00c8_8e30() {}
    cSPVector3_s00c8_8e30(const cSPVector3_s00c8_8e30& o) { x = o.x; y = o.y; z = o.z; }
    cSPVector3_s00c8_8e30& operator=(const cSPVector3_s00c8_8e30& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Quat { float x, y, z, w; };
struct BBox { Vec3 mn; Vec3 mx; };
struct Matrix3 { float m[9]; };
struct Transform {
    uint16_t flags;
    uint16_t version;
    Vec3     pos;
    float    scale;
    Matrix3  rot;
};
extern cSPVector3_s00c8_8e30 g_vec1695294;   // 0x01695294
extern cSPVector3_s00c8_8e30 g_vec16952a0;   // 0x016952a0
void*         FUN_0059aed0(void* out, void* key, void* owner);  // 0x0059aed0
unsigned char FUN_0059ab70(void* v);                            // 0x0059ab70
struct cSO;
#define VT(slot) (*(void***)this)[(slot) / 4]
struct cSO {
    void**   vt;            // +0x00
    Vec3     mPosition;     // +0x04
    Quat     mOrientation;  // +0x10
    BBox     mLocalExtents; // +0x20
    BBox     mWorldExtents; // +0x38
    uint32_t mFlags;        // +0x50
    uint32_t m54;           // +0x54
    uint32_t m58;           // +0x58
    float    m5c;           // +0x5c
    float    m60;           // +0x60
    float    f64;           // +0x64
    float    f68;           // +0x68
    uint8_t  b6c, b6d, b6e, b6f, b70, b71, b72, b73, b74, b75, b76, b77, b78;
    uint8_t  pad79[3];      // +0x79
    float    f7c;           // +0x7c
    float    f80;           // +0x80
    float    f84;           // +0x84
    float    f88;           // +0x88
    float    f8c;           // +0x8c
    uint32_t m90, m94, m98; // +0x90
    void*    mp9c;          // +0x9c  (mpModel)
    void*    mpA0;          // +0xa0  (mpModelWorld)
    uint8_t  bA4, bA5, bA6, bA7;
    uint32_t mA8, mAC, mB0;
    float    fB4;
    uint32_t mB8, mBC;
    void*    mpC0;          // +0xc0
    void*    mpC4;          // +0xc4
    uint32_t mC8;           // +0xc8

    bool funcE30();
    void func78h(cSPVector3_s00c8_8e30* out);
    void GetCommunityName(cSPVector3_s00c8_8e30* out);
    void SetLocalExtents(float* e, float scale);
    bool func9C();
    void func93F0(float* a, float* b);
    cSO();
    void LocalToWorldTransform(Transform* out);
    void SetModel(int a1, void* b);
    void funcA4h();
    bool func7Ch(char a4, float* out);
};
// ---- items of slice s00c88e30 end

// ---- items of slice s00c8bb00 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;
struct MapNodeF {
  MapNodeF* mpRight_00;          // 0x00
  MapNodeF* mpLeft_04;           // 0x04
  MapNodeF* mpParent_08;         // 0x08
  u32       mColor_0c;           // 0x0c
  u32       mKey_10;             // 0x10
  float     mValue_14;           // 0x14
};
struct KeyFloat {                // the value_type passed to DoInsertValue
  u32   mKey_00;
  float mValue_04;
};
struct InsertRet {               // pair<Node*, bool> returned in memory
  MapNodeF* mpNode_00;
  u32       mIsNew_04;
};
struct FloatMap {                // eastl::map<u32, float>
  u32       mPad_00;             // 0x00
  MapNodeF  mAnchor_04;          // 0x04
  MapNodeF* Beg()  { return mAnchor_04.mpLeft_04; }
  MapNodeF* End()  { return &mAnchor_04; }
  MapNodeF* Root() { return mAnchor_04.mpParent_08; }
  InsertRet DoInsertValue(MapNodeF* pos, const KeyFloat* value, bool flag);  // 0x00baa660
  float*    Insert(const u32& key);        // 0x00c8c550
  float*    Find(const u32& key);
};
void      __cdecl DoNukeSubtree(MapNodeF* node);              // 0x009a9600
void      __cdecl operator_delete_array(void* p);             // 0x00f47380
struct cBuilding {
  s32    GetEmpireID();          // 0x00a1ad10
  double GetValue();             // 0x00b7e0a0
};
struct cDistrict {
  u8         mPad_00[0x3c];
  cBuilding** mpBegin_3c;        // 0x3c  eastl::vector<cBuilding*>
  cBuilding** mpEnd_40;          // 0x40
  cBuilding** mpCap_44;          // 0x44
  void FUN_00ff2d80();           // 0x00ff2d80
  void FUN_00ff2e30();           // 0x00ff2e30
};
struct cFieldObject {            // elements of the +0x170 vector
  void FUN_00c2e4e0();           // 0x00c2e4e0
};
struct cNoun {
  void**        mpVtbl_00;       // 0x00
  u8            mPad_04[0x24];
  u32           mKind_28;        // 0x28  kind/class (1 and 0 are skipped)
  u8            mPad_2c[0x130];
  cDistrict**   mpDistricts_15c; // 0x15c eastl::vector<cDistrict*>
  cDistrict**   mpDistricts_160; // 0x160
  cDistrict**   mpDistricts_164; // 0x164
  u8            mPad_168[0x08];
  cFieldObject** mpFields_170;   // 0x170 eastl::vector<cFieldObject*>
  cFieldObject** mpFields_174;   // 0x174
  cFieldObject** mpFields_178;   // 0x178
  u8            mPad_17c[0x18];
  u32           mFlag_194;       // 0x194
  bool          FUN_00b8d970();            // 0x00b8d970
  s32           GetMode();                 // 0x00b8dab0
  void          FUN_00b8d920(u32 mode);    // 0x00b8d920
  cDistrict*    GetDistrict(u32 index);    // 0x00b8dec0
  void          FUN_00b8de60();            // 0x00b8de60
  void          FUN_00b8df20();            // 0x00b8df20
  u32*          FUN_00b8e090();            // 0x00b8e090
  void          AddRef() { ((void (__thiscall*)(cNoun*))mpVtbl_00[0])(this); }
  void          Release() { ((void (__thiscall*)(cNoun*))mpVtbl_00[1])(this); }
};
struct PtrVec {                  // eastl::vector<T*> (simulator noun list)
  void** mpBegin;
  void** mpEnd;
  void** mpCap;
};
struct cNounVec {                // eastl::vector<cNoun*> with intrusive refcounts
  cNoun** mpBegin_00;
  cNoun** mpEnd_04;
  cNoun** mpCap_08;
  void Grow(cNoun** value);                     // 0x00aea5d0
  void Push(cNoun* item) {
    if (mpEnd_04 < mpCap_08) {
      cNoun** slot = mpEnd_04++;
      if (slot) {
        *slot = item;
        if (item)
          item->AddRef();
      }
    } else {
      Grow(&item);
    }
  }
};
struct cSim {
  u8      mPad_00[0x0c];
  u32     mLastMinute_0c;        // 0x0c  last processed game minute
  u8      mPad_10[0x4f4];
  u8      mBuffer_504[1];        // 0x504 pointer passed to FUN_00bb9b90
  PtrVec* GetNouns();            // 0x00bba790
  bool    FUN_00bb9c30();        // 0x00bb9c30
  s32     FUN_00bb9ae0();        // 0x00bb9ae0
  void    FUN_00bb9ad0(s32 a);   // 0x00bb9ad0
  void    FUN_00bb9b00(s32 a, s32 b);  // 0x00bb9b00
  void    FUN_00bb9b90(void* p); // 0x00bb9b90
  void    FUN_00a16a90(s32 a);   // 0x00a16a90
};
struct RandomLCG {
  double NextDouble();                           // 0x009360d0
  u32    NextUint32(u32 range);                  // 0x00a68fb0
};
extern RandomLCG gMathRandom;                    // 0x01601760
struct cCombatant {
  u32 GetDamageState();          // 0x008e7f80
};
struct cMember {
  void**      mpVtbl_00;         // 0x00
  u8          mPad_04[0x11c];
  cCombatant  mCombat_120;       // 0x120
  void Release() { ((void (__thiscall*)(cMember*))mpVtbl_00[1])(this); }
};
struct MemberPool {              // SP::cTribe::GetMembers() result
  cMember** mpBegin_00;
  cMember** mpEnd_04;
  u32       mPad_08;
  void*     mpAlloc_0c;          // 0x0c
};
struct MemberVec {               // temporary refcounted pointer vector
  cMember** mpBegin_00;
  cMember** mpEnd_04;
  cMember** mpCap_08;
  void Init(s32 count, void* alloc);             // 0x00b93c60
};
struct cTribe {
  s32      GetSizeY();           // 0x00bd9b70
  s32      GetSizeX();           // 0x00bd9bb0
  void*    GetCityHall();        // 0x00bd9b40
  void     FUN_00be2070(s32 a, s32 b);           // 0x00be2070
  MemberPool* GetMembers();      // 0x00c8e810
};
struct CityHall {
  void** mpVtbl_00;
  void*  GetMayor(u32 role);     // vtable slot 0x0c
};
void __cdecl FUN_00829110(MemberVec* out, cMember** begin, cMember** end,
                          cMember** pool, void* hall);     // 0x00829110
void __cdecl FUN_00be33e0(cMember* member);                // 0x00be33e0
float* FloatMap::Insert(const u32& key)
{
  MapNodeF* node = mAnchor_04.mpParent_08;
  MapNodeF* lower = &mAnchor_04;
  while (node) {
    if (node->mKey_10 < key)
      node = node->mpRight_00;
    else {
      lower = node;
      node = node->mpLeft_04;
    }
  }
  if (lower != &mAnchor_04 && !(key < lower->mKey_10))
    return &lower->mValue_14;

  KeyFloat value;
  value.mKey_00 = key;
  value.mValue_04 = 0.0f;
  return &DoInsertValue(lower, &value, false).mpNode_00->mValue_14;
}
// ---- items of slice s00c8bb00 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
float FUN_00c8bee0(FloatMap* map, s32 count, s32* outKey);  // 0x00c8bee0 (stays in the slice: not this object's)

// ---- items of slice s00c8c9d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl operator_new(uint32_t nSize, const char* pTag, int nA, int nB, const char* pFile, int nLine); // 0x00f473a0
extern char g_szSimulator[];        // 0x013f09b4 "Simulator"
extern char g_szEastlFile[];        // 0x013ebb38 ".../EASTL/allocator.h"
extern char g_nounListPlanet[];     // 0x018c43e8
extern char g_nounListTribe[];      // 0x018c816a
void __cdecl FUN_00cd7d10();       // 0x00cd7d10
void __cdecl FUN_00d3d420();        // 0x00d3d420
void __cdecl FUN_00acdff0();        // 0x00acdff0
void __cdecl FUN_00b1e500();        // 0x00b1e500
void __cdecl FUN_00b21080();        // 0x00b21080
void __cdecl FUN_00b236c0();        // 0x00b236c0
class cPlanet;
class cCivData;
class cCity;
struct tPtrVector {                 // plain vector of 4-byte pointers
    void** mpBegin;                 // +0x00
    void** mpEnd;                   // +0x04
};
struct tGameDataList {              // the noun manager's game-data vector (begin/end at +4/+8)
    void*      mPad00;              // +0x00
    tPtrVector mData;               // +0x04
    void*      mPad0c;              // +0x0c
    void*      mPad10;              // +0x10
};
class tRefObject {
public:
    virtual void AddRef();          // 0x00
    virtual void Release();         // 0x04
};
class cGameDataNoun : public tRefObject {
public:
    uint8_t mPad04[0x98];           // +0x004
    tPtrVector mData;               // +0x09c
    uint8_t mPadA4[0x6a8];          // +0x0a4
    int32_t mn74c;                  // +0x74c
    float   mf748;                  // +0x748

    tPtrVector* GetDataVector();                            // 0x00bef6c0
    void FUN_00bd7d10(int32_t nValue, float fValue);        // 0x00bd7d10
};
class cCity {
public:
    uint8_t mPad00[0x24];           // +0x000
    int32_t mn24;                   // +0x024 population
    uint8_t mPad28[0x10];           // +0x028
    int32_t mn38;                   // +0x038 owning empire
    float   mf3c;                   // +0x03c

    int32_t GetPopulation();                            // 0x00ff35d0
    void    SetPopulation(int32_t nAmount, void* pOwner); // 0x00ff1da0
    void    FUN_00ff03b0(int32_t nValue);               // 0x00ff03b0 (mn38)
    void    FUN_00ff03c0(float fValue);                 // 0x00ff03c0 (mf3c)
    float   FUN_00b7e0a0();                             // 0x00b7e0a0 (mf3c)
    int32_t FUN_00a1ad10();                             // 0x00a1ad10 (mn38)
};
class cCivData {
public:
    uint8_t  mPad00[0x3c];          // +0x000
    cCity**  mpCityBegin;           // +0x03c
    cCity**  mpCityEnd;             // +0x040

    void EraseCity(int32_t nIndex); // 0x00ff1fb0
};
class cPlanet {
public:
    virtual void AddRef();          // +0x00
    virtual void Release();         // +0x04
    uint8_t   mPad00[0x24];         // +0x004
    int32_t   mn28;                 // +0x028
    uint32_t  mnFlags;              // +0x02c
    uint8_t   mPad30[0x24];         // +0x030
    void*     mpAvatar;             // +0x054
    uint8_t   mPad58[0x104];        // +0x058
    cCivData** mpCivBegin;          // +0x15c
    cCivData** mpCivEnd;            // +0x160
    uint8_t   mPad164[0x20];        // +0x164
    int32_t   mn184;                // +0x184 empire reference
    uint8_t   mPad188[0x0c];        // +0x188
    int32_t   mn194;                // +0x194 noun type

    tPtrVector* GetRelatedPlanets();        // 0x00bba790
    void*       GetAvatar();                // 0x00b1fdb0
    cCivData*   GetCiv(int32_t nIndex);     // 0x00b8dec0
    void        RemoveCiv(int32_t nIndex);  // 0x00b8df80
    int32_t     GetNounType();              // 0x00b8dab0 (mn194)
    bool        FUN_00b8d970();             // 0x00b8d970 (flag bit 8 of mnFlags)
    int32_t     GetOwnerID();               // 0x00b8de30
    void        FUN_00c8d060();             // 0x00c8d060
};
class cGameNounManager {
public:
    uint8_t mPad00[0x54];           // +0x000
    void*   mpAvatar;               // +0x054

    void* GetAvatar();                                              // 0x00b1fdb0
    tGameDataList* GetGameDataVector(void* pF1, void* pF2, void* pF3, void* pF4, void* pAlloc); // 0x00b21340
    void  RemoveNoun(void* pNoun);                                  // 0x00b225d0
    void* GetCurrentTerrainSphere();                                // 0x00f67d90
};
class cStarManager {
public:
    void* GetEmpireByID(void* pAvatar);             // 0x00ba9370
};
cGameNounManager* __cdecl NounManager();            // 0x00b3d300
cStarManager*     __cdecl StarManager();            // 0x00b3d2a0
cGameNounManager* __cdecl SpaceGameGet();           // 0x01002bd0
int32_t  __cdecl GetPlayerEmpireID();               // 0x01021090
void*    __cdecl GetUniverseContext();              // 0x01021080
cPlanet* __cdecl GetActivePlanetRecord();           // 0x010212a0
class tRefRange {
public:
    void** mpBegin;                 // +0x00
    void** mpEnd;                   // +0x04
    void Assign(void*** ppList);    // 0x00ba95a0
};
class tEntryVector {
public:
    void** mpBegin;                 // +0x00
    void** mpEnd;                   // +0x04
    void** mpCapacity;              // +0x08

    tEntryVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoInsertValue(void** pEnd, void* const& pValue);   // 0x00aea5d0
};
int32_t __cdecl FUN_00c70420(cPlanet* pPlanet);                    // 0x00c70420
void*   __cdecl FUN_00829110(void** ppOut, void** pBegin, void** pEnd, void** pDst, int32_t nHint); // 0x00829110
void    __cdecl FUN_00c8c0f0(void* pEntry, float fRatio, int32_t nMin); // 0x00c8c0f0
void    __cdecl FUN_00c35240(cPlanet* pPlanet, int32_t nEmpire);    // 0x00c35240
bool    __cdecl FUN_00c35810(void* pEntry, int32_t nEmpire);        // 0x00c35810 (thiscall style)
void    __cdecl FUN_00c8c9d0(cPlanet* pPlanet);
void    __cdecl FUN_00c8cb20(cPlanet* pPlanet, float fRatio, int32_t nMin, float fCityRatio, int32_t nCityMin);
void    __cdecl FUN_00c8ce40(cPlanet* pPlanet, float fRatio, int32_t nMin, float fCityRatio, int32_t nCityMin,
                             float fCityRatio2, int32_t nCityMin2);
void    __cdecl FUN_00c8d000(cPlanet* pPlanet, int32_t nEmpire);
class cSPSpaceCombatTuning {
public:
    float GetMilitaryCaptureRemainingCityRatio();    // 0x01029f10
    float GetMilitaryCaptureRemainingPlanetRatio();  // 0x01029ec0
};
cSPSpaceCombatTuning* __cdecl GetSpaceCombatTuning(); // 0x01029940
class tAudioSystem {
public:
    virtual void v00();     // 0x00
    virtual void v04();     // 0x04
    virtual void v08();     // 0x08
    virtual void v0c();     // 0x0c
    virtual void v10();     // 0x10
    virtual void v14();     // 0x14
    virtual void v18();     // 0x18
    virtual void v1c();     // 0x1c
    virtual int32_t v20();  // 0x20
    virtual void v24();     // 0x24
    virtual void v28();     // 0x28
    virtual void v2c();     // 0x2c
    virtual void v30();     // 0x30
    virtual void v34();     // 0x34
    virtual void v38(int32_t nEvent);                // 0x38
    virtual void v3c(int32_t nEvent);                // 0x3c
    virtual void v40(int32_t nEvent, int32_t nValue); // 0x40
    virtual void v44();     // 0x44
    virtual void v48();     // 0x48
    virtual void v4c();     // 0x4c
    virtual void v50();     // 0x50
    virtual void v54();     // 0x54
    virtual void v58();     // 0x58
};
tAudioSystem* __cdecl GetSystemAT();                // 0x00a206f0
void* __cdecl FUN_010666a0(uint32_t nKey);          // 0x010666a0
void  __cdecl FUN_0106dcd0(void* pObject);          // 0x0106dcd0 (thiscall on the returned object)
class cTerrainSphere {
public:
    bool FUN_00c772c0(uint32_t nKey);               // 0x00c772c0
    void FUN_00c77bf0(uint32_t nKey);               // 0x00c77bf0
};
int32_t __cdecl FUN_00ff5930(cPlanet* pPlanet);     // 0x00ff5930
class cSimPlanetHighLOD {
public:
    void CreateReplacement();                       // 0x00ffa780
};
// ---- items of slice s00c8c9d0 end

// @ 0x00c88480
void Ser::Inc(int a)
{ (void)a; mBC++; }

// @ 0x00c88490
void Ser::Dec(int a)
{ (void)a; mBC--; }

// @ 0x00c884a0
void cCommunity::func5Ch(float value)
{
    if (value != m64) {
        m64 = value;
        m7c = value;
        c064(&m20, value);
        mFlags50 |= 1;
        m74 = 1;
    }
}

// @ 0x00c88510
void SpatialA::MaybeCall()
{ if (bA7 || bA6) ((VObj84*)this)->v84(); }

// @ 0x00c88530
void SpatialA::SetValue(float v)
{ f7c = v; f88 = 0.0f; }

// @ 0x00c885b0
VObj174* FUN_00c885b0(VObj174* pObj, uint32_t* pData)
{
    VObj174* pIo = pObj->v020()->v018();
    EA::IO::WriteUint32(pIo, pData, 3, 0);
    pIo = pObj->v020()->v018();
    EA::IO::WriteUint32(pIo, pData + 3, 3, 0);
    return pObj;
}

// @ 0x00c88610
VObj174* FUN_00c88610(VObj174* pObj, uint32_t* pData)
{
    VObj174* pIo = pObj->v020()->v018();
    EA::IO::ReadInt32(pIo, pData, 3, 0);
    pIo = pObj->v020()->v018();
    EA::IO::ReadInt32(pIo, pData + 3, 3, 0);
    return pObj;
}

// @ 0x00c88670
void VecThing::Set3(float* v)
{
    bool changed = !(x == v[0] && y == v[1] && z == v[2]);
    memcpy(&x, v, 12);
    if (changed) {
        f50 |= 1;
        b74 = 1;
    }
}

// @ 0x00c886d0
void VecThing::Set4(float* v)
{
    bool changed = !(w == v[0] && x2 == v[1] && y2 == v[2] && z2 == v[3]);
    memcpy(&w, v, 16);
    if (changed) {
        f50 |= 1;
        b74 = 1;
    }
}

// @ 0x00c88740
void cCommunity::func60h(uint32_t a, uint32_t b)
{
    c038(a);
    c03c(b);
    VObj174* p = c0b8(0x17f243b, 0);
    FUN_00b48770_tc(FUN_00b3d310_sc(p));
}

// @ 0x00c88790
void GameData::RemoveOwner(bool b)
{
    m6d = b;
    if (mpA0 && b)
        ((ObjA0*)mpA0)->v89();
}

// @ 0x00c887c0
float GameData::GetValue()
{
    if (mp9c)
        return *(float*)(mp9c + 0x88);
    return f68;
}

// @ 0x00c887e0
int GameData::HasFlag()
{
    if (mp9c == 0)
        return b76;
    if (*(float*)(mp9c + 0x8c) > 0.0f)
        return 0;
    return 1;
}

// @ 0x00c88810
void SpatialModel::SetModelKey3(uint32_t* key)
{
    if (m90 == key[0] && m94 == key[1] && m98 == key[2])
        return;
    m90 = key[0];
    m94 = key[1];
    m98 = key[2];
    ((VObj8c*)this)->v8c(1);
}

// @ 0x00c88870
void SpatialPos::Fn()
{
    if (SP_PlanetModel()) {
        float x = this->x;
        float y = this->y;
        float z = this->z;
        if (x * x + y * y + z * z > 0.001f) {
            void* r = FUN_00b3d310(this);
            ((PlanetCall*)r)->v();
        }
    }
}

// @ 0x00c889c0
void Effects::StopEffect(int id, int a)
{
    char* p = mpBegin;
    char* end = mpEnd;
    if (p == end)
        return;
    do {
        if (*(int*)p == id) {
            p[8] = 0;
            EffObj3* obj = *(EffObj3**)(p + 0x38);
            if (obj)
                obj->v03(a);
            return;
        }
        p += 0x3c;
    } while (p != end);
}

// @ 0x00c88a00
void Effects::F00(int id, float v)
{
    char* p = mpBegin;
    char* end = mpEnd;
    if (p == end)
        return;
    do {
        if (*(int*)p == id) {
            *(float*)(p + 0xc) = v;
            return;
        }
        p += 0x3c;
    } while (p != end);
}

// @ 0x00c88a30
void Effects::F30(int id, int* v)
{
    char* p = mpBegin;
    char* end = mpEnd;
    if (p == end)
        return;
    do {
        if (*(int*)p == id) {
            p[0x28] = 1;
            *(int*)(p + 0x2c) = v[0];
            *(int*)(p + 0x30) = v[1];
            *(int*)(p + 0x34) = v[2];
            EffObj17* obj = *(EffObj17**)(p + 0x38);
            if (obj)
                obj->v17(5, v, 3);
            return;
        }
        p += 0x3c;
    } while (p != end);
}

// @ 0x00c89020
void cSO::func78h(cSPVector3_s00c8_8e30* out)
{
    void* owner = (void*)((void*(__thiscall*)(cSO*))VT(0x30))(this);
    cSPVector3_s00c8_8e30 v;
    cSPVector3_s00c8_8e30* r = (cSPVector3_s00c8_8e30*)FUN_0059aed0(&v, (void*)0x01695294, owner);
    cSPVector3_s00c8_8e30 tmp = *r;
    if (FUN_0059ab70(&tmp))
        *out = tmp;
    else
        *out = g_vec1695294;
}

// @ 0x00c890c0
void cSO::GetCommunityName(cSPVector3_s00c8_8e30* out)
{
    void* owner = (void*)((void*(__thiscall*)(cSO*))VT(0x30))(this);
    cSPVector3_s00c8_8e30 v;
    cSPVector3_s00c8_8e30* r = (cSPVector3_s00c8_8e30*)FUN_0059aed0(&v, (void*)0x016952a0, owner);
    cSPVector3_s00c8_8e30 tmp = *r;
    if (FUN_0059ab70(&tmp))
        *out = tmp;
    else
        *out = g_vec16952a0;
}

// @ 0x00c8c0f0
void FUN_00c8c0f0(cTribe* tribe, float frac, s32 minKeep)
{
  s32 total = tribe->GetSizeX() + tribe->GetSizeY() - 1;
  if (total <= 0)
    return;

  float totalf = (float)total;
  s32 cut = (s32)(totalf * frac);
  s32 keep = total - cut;
  if (total - keep < minKeep)
    keep = total - minKeep;

  float keepY = (float)(tribe->GetSizeY() * keep) / totalf;
  s32 roomY = tribe->GetSizeY() - (s32)keepY;
  float keepX = (float)((tribe->GetSizeX() - 1) * keep) / totalf;
  s32 roomX = tribe->GetSizeX() - (s32)keepX - 1;

  void* hall = 0;
  CityHall* cityHall = (CityHall*)tribe->GetCityHall();
  if (cityHall)
    hall = ((void* (__thiscall*)(CityHall*, u32))
        cityHall->mpVtbl_00[3])(cityHall, 0xe9cb8ba);

  for (s32 i = 0; i < roomY; ++i)
    tribe->FUN_00be2070(0, 0);

  MemberPool* members = tribe->GetMembers();
  MemberVec pool;
  pool.Init(members->mpEnd_04 - members->mpBegin_00, members->mpAlloc_0c);

  MemberVec kept;
  FUN_00829110(&kept, members->mpBegin_00, members->mpEnd_04,
               pool.mpBegin_00, hall);

  s32 index = kept.mpEnd_04 - kept.mpBegin_00;
  while (--index >= 0 && roomX > 0) {
    cMember* member = kept.mpBegin_00[index];
    if (member != hall && member->mCombat_120.GetDamageState() == 0) {
      FUN_00be33e0(member);
      --roomX;
    }
  }

  for (cMember** p = kept.mpBegin_00; p < kept.mpEnd_04; ++p) {
    if (*p)
      (*p)->Release();
  }
  if (kept.mpBegin_00 && kept.mpBegin_00[-1])
    operator_delete_array(kept.mpBegin_00);
}

// @ 0x00c8c2a0
void FUN_00c8c2a0(cSim* sim)
{
  sim->FUN_00bb9ad0(1);
  sim->FUN_00a16a90(-1);
  sim->FUN_00bb9b00(4, 0);

  PtrVec* nouns = sim->GetNouns();
  s32 nounCount = nouns->mpEnd - nouns->mpBegin;
  for (s32 i = 0; i < nounCount; ++i) {
    cNoun* noun = (cNoun*)nouns->mpBegin[i];
    noun->FUN_00b8d920(0);
    if (noun->GetMode() > 1) {
      noun->mFlag_194 = 1;

      s32 districtCount = noun->mpDistricts_160 - noun->mpDistricts_15c;
      for (s32 d = 0; d < districtCount; ++d) {
        cDistrict* district = noun->mpDistricts_15c[d];
        district->FUN_00ff2d80();
        if (district) {
          district->FUN_00ff2e30();
          operator_delete_array(district);
        }
      }
      memcpy(noun->mpDistricts_15c, noun->mpDistricts_160,
             (char*)noun->mpDistricts_160 - (char*)noun->mpDistricts_160);
      noun->mpDistricts_160 = noun->mpDistricts_15c;

      s32 fieldCount = noun->mpFields_174 - noun->mpFields_170;
      for (s32 f = 0; f < fieldCount; ++f) {
        cFieldObject* field = noun->mpFields_170[f];
        if (field) {
          field->FUN_00c2e4e0();
          operator_delete_array(field);
        }
      }
      memcpy(noun->mpFields_170, noun->mpFields_174,
             (char*)noun->mpFields_174 - (char*)noun->mpFields_174);
      noun->mpFields_174 = noun->mpFields_170;
    }
  }
}

// @ 0x00c8c420
cNoun* FUN_00c8c420(cSim* sim)
{
  PtrVec* nouns = sim->GetNouns();
  s32 nounCount = nouns->mpEnd - nouns->mpBegin;

  cNounVec picked;
  picked.mpBegin_00 = 0;
  picked.mpEnd_04 = 0;
  picked.mpCap_08 = 0;

  for (s32 i = 0; i < nounCount; ++i) {
    cNoun* noun = (cNoun*)nouns->mpBegin[i];
    if (noun->GetMode() == 5 && !noun->FUN_00b8d970())
      picked.Push(noun);
  }

  if (picked.mpBegin_00 != picked.mpEnd_04) {
    u32 index = gMathRandom.NextUint32((u32)(picked.mpEnd_04 - picked.mpBegin_00));
    cNoun* noun = picked.mpBegin_00[index];
    for (cNoun** p = picked.mpBegin_00; p < picked.mpEnd_04; ++p) {
      if (*p)
        (*p)->Release();
    }
    if (picked.mpBegin_00 && picked.mpBegin_00[-1])
      operator_delete_array(picked.mpBegin_00);
    return noun;
  }
  if (picked.mpBegin_00 && picked.mpBegin_00[-1])
    operator_delete_array(picked.mpBegin_00);
  return 0;
}

// @ 0x00c8c550
float* FloatMap::Find(const u32& key)
{
  MapNodeF* node = mAnchor_04.mpParent_08;
  MapNodeF* lower = &mAnchor_04;
  while (node) {
    if (node->mKey_10 < key)
      node = node->mpRight_00;
    else {
      lower = node;
      node = node->mpLeft_04;
    }
  }
  if (lower != &mAnchor_04 && !(key < lower->mKey_10))
    return &lower->mValue_14;
  return 0;
}

// @ 0x00c8c5d0
float FUN_00c8c5d0(cSim* sim, s32* outKey)
{
  PtrVec* nouns = sim->GetNouns();
  FloatMap map;
  map.mAnchor_04.mpParent_08 = 0;
  map.mAnchor_04.mpLeft_04 = &map.mAnchor_04;
  map.mAnchor_04.mpRight_00 = &map.mAnchor_04;
  map.mAnchor_04.mColor_0c = 0;
  map.mAnchor_04.mKey_10 = 0;

  float fNounCount = (float)(s32)(nouns->mpEnd - nouns->mpBegin);
  s32 total = 0;
  for (s32 i = 0; i < (s32)fNounCount; ++i) {
    cNoun* noun = (cNoun*)nouns->mpBegin[i];
    if (noun->mKind_28 == 1 || noun->mKind_28 == 0)
      continue;
    if (noun->FUN_00b8d970())
      continue;
    s32 districtCount = noun->mpDistricts_160 - noun->mpDistricts_15c;
    for (s32 d = 0; d < districtCount; ++d) {
      cDistrict* district = noun->GetDistrict(d);
      s32 buildingCount = district->mpEnd_40 - district->mpBegin_3c;
      total += buildingCount;
      for (s32 b = 0; b < buildingCount; ++b) {
        cBuilding* building = district->mpBegin_3c[b];
        if (building->GetEmpireID() != -1) {
          float* slot = map.Find(building->GetEmpireID());
          if (!slot)
            slot = map.Insert(building->GetEmpireID());
          *slot = *slot + (float)building->GetValue();
        }
      }
    }
  }

  s32 key = -1;
  float result = FUN_00c8bee0(&map, total, &key);
  *outKey = key;

  MapNodeF* node = map.mAnchor_04.mpParent_08;
  while (node) {
    DoNukeSubtree(node->mpRight_00);
    MapNodeF* next = node->mpLeft_04;
    operator_delete_array(node);
    node = next;
  }
  return result;
}

// @ 0x00c8c7f0
float FUN_00c8c7f0(cNoun* noun, s32* outKey)
{
  FloatMap map;
  map.mAnchor_04.mpParent_08 = 0;
  map.mAnchor_04.mpLeft_04 = &map.mAnchor_04;
  map.mAnchor_04.mpRight_00 = &map.mAnchor_04;
  map.mAnchor_04.mColor_0c = 0;
  map.mAnchor_04.mKey_10 = 0;

  s32 total = 0;
  if (noun->mKind_28 != 1 && noun->mKind_28 != 0 && !noun->FUN_00b8d970()) {
    float fDistrictCount = (float)(s32)(noun->mpDistricts_160 - noun->mpDistricts_15c);
    for (s32 d = 0; d < (s32)fDistrictCount; ++d) {
      cDistrict* district = noun->GetDistrict(d);
      s32 buildingCount = district->mpEnd_40 - district->mpBegin_3c;
      total += buildingCount;
      for (s32 b = 0; b < buildingCount; ++b) {
        cBuilding* building = district->mpBegin_3c[b];
        if (building->GetEmpireID() != -1) {
          float* slot = map.Find(building->GetEmpireID());
          if (!slot)
            slot = map.Insert(building->GetEmpireID());
          *slot = *slot + (float)building->GetValue();
        }
      }
    }
  }

  s32 key = -1;
  float result = FUN_00c8bee0(&map, total, &key);
  *outKey = key;

  MapNodeF* node = map.mAnchor_04.mpParent_08;
  while (node) {
    DoNukeSubtree(node->mpRight_00);
    MapNodeF* next = node->mpLeft_04;
    operator_delete_array(node);
    node = next;
  }
  return result;
}

// @ 0x00c8c9d0
void FUN_00c8c9d0(cPlanet* pPlanet)
{
    tPtrVector* pPlanets = pPlanet->GetRelatedPlanets();
    int32_t nCount = (int32_t)(pPlanets->mpEnd - pPlanets->mpBegin);
    int32_t i = 0;
    if (nCount > 0)
    {
        do
        {
            cPlanet* pCur = (cPlanet*)pPlanets->mpBegin[i];
            if (GetUniverseContext() == 0 && GetActivePlanetRecord() == pCur)
            {
                cGameNounManager* pManager = NounManager();
                tGameDataList* pList = pManager->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                                   (void*)FUN_00acdff0, (void*)FUN_00b1e500,
                                                                   g_nounListPlanet);
                tPtrVector* pNouns = &pList->mData;
                int32_t nNouns = (int32_t)(pNouns->mpEnd - pNouns->mpBegin);
                for (int32_t j = 0; j < nNouns; ++j)
                    ((cGameDataNoun*)pNouns->mpBegin[j])->FUN_00bd7d10(-1, 0.0f);
            }
            else if (pCur->mn28 != 1 && pCur->mn28 != 0 && !pCur->FUN_00b8d970())
            {
                int32_t c = 0;
                int32_t nCivs = (int32_t)(pCur->mpCivEnd - pCur->mpCivBegin);
                for (; c < nCivs; ++c)
                {
                    cCivData* pCiv = pCur->GetCiv(c);
                    int32_t nCities = (int32_t)(pCiv->mpCityEnd - pCiv->mpCityBegin);
                    for (int32_t k = 0; k < nCities; ++k)
                    {
                        cCity* pCity = pCiv->mpCityBegin[k];
                        pCity->FUN_00ff03b0(-1);
                        pCity->FUN_00ff03c0(0.0f);
                    }
                }
            }
            ++i;
        } while (i < nCount);
    }
}

// @ 0x00c8cb20
void FUN_00c8cb20(cPlanet* pPlanet, float fRatio, int32_t nMin, float fCityRatio, int32_t nCityMin)
{
    int32_t nTotal = FUN_00c70420(pPlanet);
    int32_t nRemaining = nTotal - (int32_t)((float)nTotal * fRatio);
    if (nTotal - nRemaining < nMin)
        nRemaining = nTotal - nMin;

    if (pPlanet == GetActivePlanetRecord() && GetUniverseContext() == 0)
    {
        cGameNounManager* pManager = NounManager();
        tGameDataList* pList = pManager->GetGameDataVector((void*)FUN_00b21080, (void*)FUN_00d3d420,
                                                           (void*)FUN_00b236c0, (void*)FUN_00b1e500,
                                                           g_nounListTribe);
        tRefRange range;
        range.Assign(&pList->mData.mpBegin);
        void** pBegin = range.mpBegin;
        void** pEnd = range.mpEnd;
        int32_t nNouns = (int32_t)(pEnd - pBegin);
        for (int32_t i = 0; i < nNouns; ++i)
        {
            cGameDataNoun* pNoun = (cGameDataNoun*)pBegin[i];
            tPtrVector* pData = pNoun->GetDataVector();
            int32_t nEntries = (int32_t)(pData->mpEnd - pData->mpBegin);
            void** pNew = 0;
            if (nEntries != 0)
                pNew = (void**)operator_new((uint32_t)nEntries * 4, g_szSimulator, 0, 0, g_szEastlFile, 0xd1);
            void* pNewEnd = 0;
            FUN_00829110(&pNewEnd, pData->mpBegin, pData->mpEnd, pNew, i);
            int32_t nCopied = (int32_t)((void**)pNewEnd - pNew);
            for (int32_t k = 0; k < nCopied; ++k)
            {
                void* pEntry = pNew[k];
                if (nRemaining > 0)
                {
                    NounManager()->RemoveNoun(pEntry);
                    --nRemaining;
                }
                else
                {
                    FUN_00c8c0f0(pEntry, fCityRatio, nCityMin);
                }
            }
            void** pSlot = pNew;
            while (pSlot < (void**)pNewEnd)
            {
                if (*pSlot != 0)
                    ((tRefObject*)*pSlot)->Release();
                ++pSlot;
            }
            if (pNew != 0 && ((int32_t*)pNew)[-1] != 0)
                operator_delete_array(pNew);
        }
        void** pSlot = pBegin;
        while (pSlot < pEnd)
        {
            if (*pSlot != 0)
                ((tRefObject*)*pSlot)->Release();
            ++pSlot;
        }
        if (pBegin != 0 && ((int32_t*)pBegin)[-1] != 0)
            operator_delete_array(pBegin);
    }
    else
    {
        int32_t nCivs = (int32_t)(pPlanet->mpCivEnd - pPlanet->mpCivBegin);
        for (int32_t c = 0; c < nCivs; ++c)
        {
            cCivData* pCiv = pPlanet->GetCiv(c);
            int32_t nCities = (int32_t)(pCiv->mpCityEnd - pCiv->mpCityBegin);
            for (int32_t k = 0; k < nCities; ++k)
            {
                if (nRemaining > 0)
                {
                    pCiv->EraseCity(k);
                    --nRemaining;
                }
                else
                {
                    cCity* pCity = pCiv->mpCityBegin[k];
                    int32_t nCur = pCity->GetPopulation();
                    int32_t nCut = (int32_t)((float)nCur * fCityRatio);
                    int32_t nNew = pCity->GetPopulation() - nCut;
                    if (pCity->GetPopulation() - nNew < nCityMin)
                        nNew = pCity->GetPopulation() - nCityMin;
                    if (nNew > 0)
                        pCity->SetPopulation(pCity->GetPopulation() - nNew, pPlanet);
                }
            }
        }
        for (int32_t c = 0; c < (int32_t)(pPlanet->mpCivEnd - pPlanet->mpCivBegin); )
        {
            cCivData* pCiv = pPlanet->mpCivBegin[c];
            if (pCiv->mpCityEnd == pCiv->mpCityBegin)
                pPlanet->RemoveCiv(c);
            else
                ++c;
        }
    }
}

// @ 0x00c8ce40
void FUN_00c8ce40(cPlanet* pPlanet, float fRatio, int32_t nMin, float fCityRatio, int32_t nCityMin, float fCityRatio2, int32_t nCityMin2)
{
    void* pRef;
    tEntryVector vec;
    tPtrVector* pPlanets = pPlanet->GetRelatedPlanets();
    int32_t nPlanets = (int32_t)(pPlanets->mpEnd - pPlanets->mpBegin);
    for (int32_t i = 0; i < nPlanets; ++i)
    {
        cPlanet* pCur = (cPlanet*)pPlanets->mpBegin[i];
        if (pCur->GetNounType() == 5 && pCur->mpCivBegin != pCur->mpCivEnd)
        {
            pRef = pCur;
            if (pCur != 0)
                pCur->AddRef();
            if (vec.mpEnd < vec.mpCapacity)
            {
                *vec.mpEnd = pCur;
                ++vec.mpEnd;
                if (pCur != 0)
                    pCur->AddRef();
            }
            else
            {
                vec.DoInsertValue(vec.mpEnd, pRef);
            }
            if (pRef != 0)
                ((tRefObject*)pRef)->Release();
        }
    }

    int32_t nCount = (int32_t)(vec.mpEnd - vec.mpBegin);
    int32_t nRemaining = nCount - (int32_t)((float)nCount * fRatio);
    if (nCount - nRemaining < nMin)
        nRemaining = nCount - nMin;

    void* pAvatar = pPlanet->GetAvatar();
    StarManager()->GetEmpireByID(pAvatar);

    for (int32_t i = 0; i < nCount; ++i)
    {
        cPlanet* pCur = (cPlanet*)vec.mpBegin[i];
        if ((pCur == GetActivePlanetRecord() && GetUniverseContext() == 0) || nRemaining <= 0)
        {
            FUN_00c8cb20(pCur, fCityRatio, nCityMin, fCityRatio2, nCityMin2);
        }
        else
        {
            FUN_00c8cb20(pCur, 0.0f, 0, 0.0f, 0);
            FUN_00c35810(pCur, 0);
            --nRemaining;
        }
    }

    void** pSlot = vec.mpBegin;
    while (pSlot < vec.mpEnd)
    {
        if (*pSlot != 0)
            ((tRefObject*)*pSlot)->Release();
        ++pSlot;
    }
    if (vec.mpBegin != 0 && ((int32_t*)vec.mpBegin)[-1] != 0)
        operator_delete_array(vec.mpBegin);
}

// @ 0x00c8d000
void FUN_00c8d000(cPlanet* pPlanet, int32_t nEmpire)
{
    FUN_00c8c9d0(pPlanet);
    if (nEmpire == GetPlayerEmpireID())
    {
        FUN_00c8ce40(pPlanet, GetSpaceCombatTuning()->GetMilitaryCaptureRemainingPlanetRatio(), 1,
                     GetSpaceCombatTuning()->GetMilitaryCaptureRemainingCityRatio(), 1, 1.0, 1);
    }
    FUN_00c35240(pPlanet, nEmpire);
}

// @ 0x00c8d060
void cPlanet::FUN_00c8d060()
{
    tPtrVector* pPlanets = GetRelatedPlanets();
    int32_t nPlanets = (int32_t)(pPlanets->mpEnd - pPlanets->mpBegin);
    int32_t nEmpire = -1;
    int32_t i = 0;
    if (nPlanets > 0)
    {
        do
        {
            cPlanet* pCur = (cPlanet*)pPlanets->mpBegin[i];
            if (pCur->GetNounType() == 5 && pCur->mn28 != 1 && pCur->mn28 != 0 && !pCur->FUN_00b8d970())
            {
                int32_t nCivs = (int32_t)(pCur->mpCivEnd - pCur->mpCivBegin);
                if (nCivs == 0)
                    return;
                for (int32_t c = 0; c < nCivs; ++c)
                {
                    cCivData* pCiv = pCur->GetCiv(c);
                    int32_t nCities = (int32_t)(pCiv->mpCityEnd - pCiv->mpCityBegin);
                    if (nCities == 0)
                        return;
                    for (int32_t k = 0; k < nCities; ++k)
                    {
                        cCity* pCity = pCiv->mpCityBegin[k];
                        if (pCity->FUN_00b7e0a0() < 100.0f)
                            return;
                        if (nEmpire == -1)
                            nEmpire = pCity->FUN_00a1ad10();
                        if (nEmpire != pCity->FUN_00a1ad10())
                            return;
                    }
                }
            }
            ++i;
        } while (i < nPlanets);
    }
    if (nEmpire == -1)
        return;

    if (nEmpire == GetPlayerEmpireID())
    {
        if (GetActivePlanetRecord() == 0)
            return;
        tAudioSystem* pAudio = GetSystemAT();
        int32_t nHandle = pAudio != 0 ? pAudio->v20() : 0;
        pAudio = GetSystemAT();
        if (pAudio != 0)
        {
            pAudio->v38(0x03475365);
            pAudio->v40(0x03475381, 0xef7f5479);
            pAudio->v40(0x03475385, nHandle);
            pAudio->v58();
        }
        cTerrainSphere* pSphere = (cTerrainSphere*)NounManager()->GetCurrentTerrainSphere();
        if (pSphere != 0 && !pSphere->FUN_00c772c0(0x06627823))
        {
            pSphere->FUN_00c77bf0(0x06627823);
            FUN_0106dcd0(FUN_010666a0(0xee98e353));
        }
        return;
    }

    FUN_00c8d000(this, nEmpire);
    cPlanet* pActive = GetActivePlanetRecord();
    if (GetUniverseContext() == 0 && pActive->GetNounType() == 5 && pActive->GetOwnerID() == (int32_t)this)
    {
        int32_t nReplacements = FUN_00ff5930(GetActivePlanetRecord());
        if (nReplacements > 0)
        {
            do
            {
                cGameNounManager* pGame = SpaceGameGet();
                ((cSimPlanetHighLOD*)pGame->GetAvatar())->CreateReplacement();
            } while (--nReplacements != 0);
        }
    }
}
