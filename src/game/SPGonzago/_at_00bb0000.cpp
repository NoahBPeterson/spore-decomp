// src/game/SPGonzago/_at_00bb0000.cpp -- migrated from slice(s) s00bbf630, s00bbe5f0, s00bbd730, s00bbca30, s00bbb9d0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00bb0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCityData.h"
#include "SP/cCivData.h"
#include "SP/cPlanetModel.h"
#include <math.h>
#include "SP/cGameNounManager.h"
#include "SP/cPropertyList.h"
#include "SP/cSPGameDataUFO.h"
#pragma warning(disable: 4100)

// ---- items of slice s00bbb9d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct CityObj {
    int GetNumBuildings();             // 0xff0870
    int GetNumTurrets();               // 0xff0760
};
bool RecordKeyLess(void* a, void* b);      // 0xac0730
// ---- items of slice s00bbb9d0 end

// ---- items of slice s00bbca30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_01021260();                       // SP::cSPLivingUniverse::GetActivePlanet
extern "C" void  __cdecl FUN_01043c60(void*, void*);           // cZooMarkerMgr helper
extern "C" void  __cdecl FUN_00f47380(void*);                  // operator_delete_array
extern "C" void __cdecl FUN_00d52cb0(void*, int, int, int, void*);   // 0xd52cb0  push_heap-ish
extern "C" void* __cdecl FUN_00b3d3b0();                       // 0xb3d3b0  PlanetModel (0 args)
extern "C" void* __cdecl FUN_00b3d3b0b(int);                    // 0xb3d3b0  PlanetModel (1 arg)
extern "C" void  __cdecl FUN_00bbd2a0(void*, float, void*);     // 0xbbd2a0
#define VF(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))
extern uint32_t DAT_0168a488, DAT_0168a48c, DAT_0168a490;
class TObj {
public:
    // ---- reused __thiscall callees (addresses in comments) -------------------
    void* F_4df550(void*);              // 0x4df550  GetProfile(const Key&)
    void* F_c745d0(int, void*);         // 0xc745d0
    void* F_8414c0();                   // 0x8414c0
    void  F_c80680(int, void*);         // 0xc80680
    void  F_f921d0(int, int);           // 0xf921d0
    void  F_b2a750();                   // 0xb2a750
    void  F_bbc870(void* out, int a, void* b, int c);   // 0xbbc870
    void  F_bbc540(void* out, void* p);                 // 0xbbc540  UpdateCargoSlots
    void  F_bbc950(void* out, int a, int b, int c);     // 0xbbc950
    void  F_c70a00(float);                              // 0xc70a00
    void  F_c70a50(float);                              // 0xc70a50
    float F_c71d30();                                   // 0xc71d30
    void  F_c71da0(float);                              // 0xc71da0
    char  F_c70a70();                                   // 0xc70a70
    void  F_c70aa0(float);                              // 0xc70aa0
    void* F_c71e30();                                   // 0xc71e30
    void  F_c70de0(int);                                // 0xc70de0
    float F_fbda80();                                   // 0xfbda80
    void  F_fbddb0(float, float, void*);                // 0xfbddb0
    int   F_bbc670(int);                                // 0xbbc670
    char  F_c308b0();                                   // 0xc308b0
    void  F_ffaa90();                                   // 0xffaa90
    void  F_dd8640(int, int, int, int, int, int);       // 0xdd8640
    void* F_b1fdb0();                                   // 0xb1fdb0
    void  F_01034880();                                 // 0x1034880

    // ---- slice targets -------------------------------------------------------
    int*  FUN_00bbca30(int* out, int index, int planet);   // 0xbbca30
    void  FUN_00bbcb10(void* key, void* planet);           // 0xbbcb10
    char  FUN_00bbcb90(int param_1, int param_2);          // 0xbbcb90
    void  FUN_00bbcf00(void* planet, float f2, float f3, int param_4);  // 0xbbcf00
    void  FUN_00bbd0a0(int delta);                         // 0xbbd0a0
    int*  FUN_00bbd0e0(int* node, int param_3, int** param_4);  // 0xbbd0e0
};
bool __cdecl FUN_00bbcd40(int param_1, int param_2);       // 0xbbcd40
typedef bool (__cdecl *CmpFn)(int, int);
void __cdecl FUN_00bbd180(int* first, int param_2, int param_3, int hole, int param_5, CmpFn cmp);   // 0xbbd180
void __cdecl FUN_00bbd1f0(int* arr, int param_2, int param_3, void* param_4, CmpFn cmp);             // 0xbbd1f0
static inline int CountFaces(int p) {
    return (*(int*)(p + 0x358) - *(int*)(p + 0x354) >> 2) +
           (*(int*)(p + 0x344) - *(int*)(p + 0x340) >> 2);
}
// ---- items of slice s00bbca30 end

// ---- items of slice s00bbd730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_010212a0();   // GetActivePlanetRecord
extern "C" int   TerraDistClass(float x, float y);        // 0xfc2080
extern "C" extern unsigned char DAT_014665e0[];
extern "C" extern unsigned char DAT_014665e1[];
extern "C" extern unsigned char DAT_014665e2[];
#pragma intrinsic(sqrt)
#pragma intrinsic(fabs)
typedef unsigned char byte;
struct DebugDrawObj;
struct PlanetModelObj;
struct TerraObj;
struct PlanetModelObj {
    float get_radius();            // 0xb7e4d0
    void* get_scene();             // unused here
};
struct DebugDrawObj {
    void begin(float* pos, float radius);   // 0xb2d870
    void flush(unsigned flags);             // 0xb2a750
};
extern "C" PlanetModelObj* FUN_00b3d350();   // SP::PlanetModel
extern "C" DebugDrawObj* FUN_00b3d3b0_s00bb_d730();     // debug-draw singleton
extern "C" extern int DAT_0168a488_s00bb_d730;
extern "C" extern int DAT_0168a48c_s00bb_d730;
extern "C" extern int DAT_0168a490_s00bb_d730;
struct PlanetSceneObj {
    int  field_38;                 // +0x38
};
struct GridObj {
    char* data;                    // +0x10
};
struct DrawBucketObj {
    int* lookup(int* key);         // 0xc7e1a0
    void first(void* out);         // 0xc7ead0
    void next(void* out);          // 0xc7e160
};
struct SurfaceObj {
    float* DirectionToSurfacePosition(void* out, float* dir);  // 0xb815a0
    void first(void* out);         // 0xc7ead0
    void next(void* out);          // 0xc7e160
};
struct RenderObj {
    int unk();                     // 0x8414c0
};
struct TerraObj {
    RenderObj* fn_8414c0();        // 0x8414c0
};
struct CityHolder {
    int  fn_b8de30();              // 0xb8de30
    float* GetCities();            // 0x5c65e0
};
struct AvatarObj {
    int fn_b1fdb0();               // 0xb1fdb0
    int fn_c30c60();               // 0xc30c60
};
struct CombatTuning {
    float* GetModelOffset();       // 0x102a3e0
};
struct StarMgr {
    int  fn_885c90();              // 0x885c90
    void* fn_00ba93b0();           // 0xba93b0
    float field_1bc;
};
extern "C" StarMgr* FUN_00b3d2a0();       // SP_StarManager
extern "C" CombatTuning* FUN_01029940();  // SP::GetSpaceCombatTuning
class TerraformingManager;
class TerraformingManager {
public:
    bool check_requirements(int param);
    int  unlocked_count(int param);
    bool has_unlocks(int param);
    int* query(int* out, int dist, unsigned code, int param);   // 0xbbc870
    int  fn_bbce40(int param);                                  // 0xbbce40
};
// ---- items of slice s00bbd730 end

// ---- items of slice s00bbe5f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  operator_delete__(void* p);                                             // 0x00f47380
extern "C" void* g_EAAllocSite;                                                          // 0x013ebb38
extern "C" void* GetUniverseContext();                 // 0x01021080
extern "C" void* GetPlayerEmpire();                    // 0x01021300
extern "C" void* GetCurrentGameMode();                 // 0x00b5b800
extern "C" void* GetSpaceCombatTuning();               // 0x0102940
extern "C" void* FUN_01049a10();                       // TerraformTuning getter
extern "C" void* TerraformingManager();                // 0x00b3d430
extern "C" int FUN_00fc2080(uint32_t a, uint32_t b);
extern "C" int FUN_00c70e00(void* p);
extern "C" void FUN_00c308e0(void* self, void* arg);
extern "C" void FUN_00c73520(void* self, void** out);
extern "C" void FUN_00bbd1f0(void* a, int b, int c, void* d, void* e, void* f);
extern "C" void FUN_00bbcb90(int a, void* b);
extern "C" void FUN_00401090(void* a, ...);
extern "C" int  FUN_004df550(void* p);
extern "C" float g_kOne;          // 0x01485720
extern "C" float g_kTwoThirds2;   // 0x01470f1c
#pragma pack(push, 4)
#pragma pack(push, 1)
#pragma pack(pop)
typedef unsigned int uint;
extern "C" void* EAAllocate(uint size, const char* pName, int a, int b, void* site, int d);  // 0x00f473a0
void* GetStarManager();                               // 0x00b3d2a0
struct PlanetRecord;
extern "C" PlanetRecord* GetActivePlanetRecord();      // 0x010212a0
extern "C" PlanetRecord* GetActivePlanet();            // 0x01021260
struct PlanetRecord {
    uint8_t  pad00[0x2c];
    uint32_t flags2c;              // +0x2c
    uint8_t  pad30[0x80];
    uint32_t p_b0;                 // +0xb0
    uint32_t p_b4;                 // +0xb4
    uint32_t p_bc;                 // +0xbc  (array begin)
    uint32_t p_c0;                 // +0xc0  (array end)
    uint8_t  padc4[0xc];
    uint32_t p_d0;                 // +0xd0
    uint32_t p_d4;                 // +0xd4
    uint8_t  pade0[0x5c];
    uint32_t p_13c;                // +0x13c
};
extern "C" int  FUN_00bbd180_s00bb_e5f0(void* a, int b, int c, int d, void* e, void* f);
extern "C" void* FUN_00bbc870(void* out, int a, uint32_t key, PlanetRecord* r);
extern "C" void FUN_00bbc950(void* out, int a, int b, PlanetRecord* r);
extern "C" void FUN_00bbca30(void* out, int a, PlanetRecord* r);
struct ViewTuning {
    int getT1();   // 0x01049e70
    int getT2();   // 0x01049eb0
    int getT3();   // 0x01049ef0
};
struct ViewVector  { void dtor(); };                       // 0x00ae6970
struct ViewRBTree  { void nuke(void* p); };                // 0x009a9600
struct ViewHash1c  { void* m0; void* m4; uint32_t cnt8; uint32_t n_c;
                     void release(void* a, void* b);       // 0x01068400
                     void find(void* o8, void* o4);        // 0x00a3b2c0
                     void insert(const void* pair8); };    // 0x00bbd0e0
struct ViewGonzago { void ctor();                          // 0x00b5b960
                     void dtor(); };                       // 0x00b5b9a0
struct ViewRecord  {                                     // record methods
    void*       getNoun();                 // 0x00b8de30
    int         FUN_00bbce40();            // 0x00bbce40
};
struct ViewStar    { void* FUN_00885c90(); };             // 0x00885c90
struct ViewNoun    { void* GetAvatar(); };                // 0x00b1fdb0
struct ViewCivData { void* GetCities(); };                // 0x005c65e0
struct ViewSCTuning{ float* GetModelOffset(); };          // 0x0102a3e0
struct ViewCity    { int GetNumBuildings();               // 0x00ff0870
                     int GetNumTurrets();                 // 0x00ff0760
                     void ClampBuildings(int a, void* b); };// 0x00ff1da0
struct ViewTerrMgr { int FUN_00bbe5f0(PlanetRecord* r); }; // 0x00bbe5f0 self call
struct RefObj { virtual void addRef(); virtual void release(); };
struct RefObj2 { virtual void addRef(); virtual void release(); };
struct ViewSpecies {
    void* FUN_00b3d420();     // 0x00b3d420
    void* FUN_00b90410();     // 0x00b90410
    int   FUN_00b8f860();     // 0x00b8f860
};
extern "C" int FUN_00bbcda0(int a, PlanetRecord* r);
extern "C" int FUN_00bbc6a0(int a, PlanetRecord* r);
struct SimSelf {
    int  FUN_00bbe5f0(PlanetRecord* r);
    int  FUN_00bbe740(PlanetRecord* r);
    bool FUN_00bbe850(int n, int t, PlanetRecord* r);
    int  FUN_00bbecc0(int* buildingId, PlanetRecord* r, int key, uint8_t* out);
    int  FUN_00bbee30(int* buildingId, int key, uint8_t flag, PlanetRecord* r, uint8_t* out);
    void FUN_00bbf2b0(PlanetRecord* r);
    void FUN_00bbec40(int a, float b);
};
struct Node18 { int a; float b, c, d, e; };
struct SimAllocHelper { void* FUN_00bbe8c0(const Node18* src); };
struct SimListHelper { void FUN_00bbe910(int head, int* payload); };
struct SimSubDtor { void FUN_00bbebb0(); };
struct SimHashOwner { bool FUN_00bbec60(int key); };
struct SimSaveGame { void* FUN_00bbf1f0(); };
// ---- items of slice s00bbe5f0 end

// ---- items of slice s00bbf630 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_006782c0(void* first, void* last, void* result);                          // 0x006782c0
extern "C" int   FUN_01021080();                                                               // 0x01021080 GetUniverseContext
extern "C" void* FUN_00b3d300();   // 0x00b3d300 SP::NounManager
extern "C" uint  g_0168a478;   // 0x0168a478
extern "C" uint  g_0168a488;   // 0x0168a488
extern "C" uint  g_0168a48c;   // 0x0168a48c
extern "C" uint  g_0168a490;   // 0x0168a490
struct AutoRef {
    virtual void AddRef();     // vtable +0x00
    virtual void Release();    // vtable +0x04
};
struct cPropertyList {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, void** out);          // vtable +0x24
};
struct PtrVector {
    void** mpBegin;    // +0x00
    void** mpEnd;      // +0x04
    void** mpCap;      // +0x08

    void   erase(void* first, void* last);   // 0x00e25bd0
    void   push_back(void* src);             // 0x00aea5d0
};
struct SimHash {
    uint32_t pad00;
    uint32_t mpBuckets;    // +0x04
    uint32_t mnBucket;     // +0x08
    uint32_t mUnknown0c;   // +0x0c

    void           find(void* out, const void* key);                    // 0x00a3b2c0
    void           insert(void* iterOut, const void* value, void* key); // 0x00bbf070
    void           deallocate(uint32_t buckets, uint32_t count);        // 0x01068400
    int*           FUN_00bbf630(const int* key);
};
struct RBNodeBase {
    RBNodeBase* mpNodeRight;    // +0x00
    RBNodeBase* mpNodeLeft;     // +0x04
    RBNodeBase* mpNodeParent;   // +0x08
    uint8_t     mColor;         // +0x0c
};
struct RBTree {
    int         mCompare;     // +0x00
    RBNodeBase  mAnchor;      // +0x04
    uint32_t    mnSize;       // +0x14

    void nuke(void* node);    // 0x009a9600
};
struct KeyIntern {
    uint32_t m0, m4, m8;

    int* intern(const void* elem);   // 0x0103de50
    void nuke(void* node);           // 0x009a9600
};
struct Elem12  { int v0, v1, v2; };
struct AllocNode { void* mpRoot; AllocNode* mpNext; };
struct EntrySub {
virtual void  s00();
virtual void  s04();
virtual void  s08();
virtual void  s0c();
virtual void  s10();
virtual void  s14();
virtual void  s18();
virtual void  s1c();
virtual void  s20();
virtual void  s24();
virtual void  s28();
virtual void* s2c();
virtual void  s30();
virtual void  s34();
virtual void  s38(void* p);
virtual void  s3c(void* p);
    virtual void  s40(float f);
};
struct Entry {
    virtual void  v00();                     // +0x00 AddRef
    virtual void  v04();                     // +0x04 Release
    virtual void  v08();                     // +0x08
    virtual void* v0c(void* a);              // +0x0c
virtual void  v10();
virtual void  v14();
virtual void  v18();
virtual void  v1c();
virtual void  v20();
virtual void  v24();
virtual void  v28();
virtual void  v2c();
virtual void  v30();
virtual void  v34();
virtual void  v38();
virtual void  v3c();
virtual void  v40();
virtual void  v44();
    virtual void  v48(void* a);              // +0x48
    virtual void* v4c();                     // +0x4c
    uint8_t   pad04[0x34 - 0x04];            // data between the vptr and the sub-object
    EntrySub  mSub;                          // +0x34 (own vptr; slots 0x2c/0x38/0x3c/0x40)
    uint8_t   pad38[0x68 - 0x38];
    void**    mpVec;                         // +0x68
    void*     pad6c[2];
    uint8_t   pad74[0x90 - 0x74];
    cPropertyList* mpPropList;               // +0x90
    uint8_t   pad94[0x1ec - 0x94];
    int32_t   m1ec;                          // +0x1ec

    void* FillPair(void* p);                 // 0x00bfe260
    void  FUN_00bfe220(void* p);             // 0x00bfe220
    void  FUN_00bff6e0(void* p);             // 0x00bff6e0
    void  SetState(int s);                   // 0x00bfdfb0
    void  FUN_00bfeaf0(void* p);             // 0x00bfeaf0
};
struct OtherRec {
    void*   mpNoun;     // +0x00
    int32_t mState;     // +0x04
};
struct OtherVec {
    OtherRec** mpBegin;   // +0x00
    OtherRec** mpEnd;     // +0x04
    OtherRec** mpCap;     // +0x08
};
struct GameDataVector {
    uint32_t m00;
    void**   mpBegin;   // +0x04
    void**   mpEnd;     // +0x08
};
struct cGameNounManager {
    void* GetGameDataVector(void* a, void* b, void* c, void* d, uint32_t type);  // 0x00b21340
    void  RemoveNoun(void* noun);                                                // 0x00b225d0
    void* CreateNoun(uint32_t type);                                             // 0x00b20c60
};
inline cGameNounManager* SP_NounManager() { return (cGameNounManager*)FUN_00b3d300(); }
struct WNode {
    uint8_t  pad00[0x3c];
    void**   mpBegin;   // +0x3c
    void**   mpEnd;     // +0x40

    void* FUN_00ff0420();   // 0x00ff0420
};
struct PlanetRecord_s00bb_f630 {
    uint32_t   flags4;      // +0x04
    uint8_t    pad08[0x0c - 0x08];
    float      f0c[4];      // +0x0c
    uint8_t    p1c;         // +0x1c
    uint8_t    pad1d[0x6c - 0x1d];
    float      f_6c;        // +0x6c
    uint8_t    pad70[0x90 - 0x70];
    cPropertyList* mpPropList;  // +0x90
    uint8_t    pad94[0xb0 - 0x94];
    uint32_t   p_b0;        // +0xb0
    uint32_t   p_b4;        // +0xb4
    uint8_t    padb8[0x13c - 0xb8];
    void*      p_13c;       // +0x13c

    OtherVec* FUN_00c71020();    // 0x00c71020
    int    FUN_00c70e00();       // 0x00c70e00
    int    FUN_00c710c0();       // 0x00c710c0
    WNode* FUN_00c71030(int i);  // 0x00c71030
    void   FUN_00c72dd0(void* node);  // 0x00c72dd0
    void*  FUN_00b8de30();       // 0x00b8de30
};
struct SimSelf_s00bb_f630 {
    uint8_t  pad00[0x1c];
    SimHash  mHash;          // +0x1c
    uint8_t  pad2c[0x3c - 0x2c];
    uint8_t  mb3c;           // +0x3c
    uint8_t  pad3d[3];
    int32_t  m40;            // +0x40
    uint8_t  mb44;           // +0x44
    uint8_t  pad45[3];
    RBTree   mTree;          // +0x48
    uint8_t  pad60[0x68 - 0x60];
    PtrVector mVec;          // +0x68
    uint8_t  pad74[0x7c - 0x74];
    uint32_t m7c, m80, m84;  // +0x7c
    uint32_t m88, m8c, m90;  // +0x88

    int   FUN_00bbf730(const int* src, float f);
    void  FUN_00bbf860();
    void  FUN_00bbcb90(int tier, void* planet);   // 0x00bbcb90
    void  FUN_00bbfe80();
    void  FUN_00bc0180(uint8_t flag);
};
void FUN_00bbfeb0(void* planet);
void FUN_00bbff40(void* planet);
// ---- items of slice s00bbf630 end

// @ 0x00bbc630
bool CityLessBuildings(void* a, void* b)
{
    int x = ((CityObj*)a)->GetNumBuildings() + ((CityObj*)a)->GetNumTurrets();
    int y = ((CityObj*)b)->GetNumBuildings() + ((CityObj*)b)->GetNumTurrets();
    return x < y;
}

// @ 0x00bbc700
void** RecordMinSelect(void** first, void** last)
{
    void** best = first;
    if (first != last) {
        void** it = first;
        while (it = it + 1, it != last) {
            void* ka = *best ? (char*)*best + 0x34 : 0;
            void* kb = *it ? (char*)*it + 0x34 : 0;
            if (RecordKeyLess(kb, ka))
                best = it;
        }
    }
    return best;
}

// @ 0x00bbc760
void RecordInsertionSort(void** first, void** last, bool (__cdecl* cmp)(void*, void*))
{
    for (; first != last; first = first + 1) {
        void* v = *first;
        void** dst = first;
        void** src = first;
        while (cmp(v, src[-1])) {
            *dst = src[-1];
            dst = dst - 1;
            src = src - 1;
        }
        *dst = v;
    }
}

// @ 0x00bbc7c0
void** RecordMedian3(void** a, void** b, void** c, bool (__cdecl* cmp)(void*, void*))
{
    if (cmp(*a, *b)) {
        if (cmp(*b, *c))
            return b;
        if (cmp(*a, *c))
            return c;
        return a;
    }
    if (cmp(*a, *c))
        return a;
    if (cmp(*b, *c))
        return c;
    return b;
}

// @ 0x00bbc840
int __fastcall TerraVectorCount(void* self)
{
    char* s = (char*)self;
    int a = (*(int*)(s + 0x358) - *(int*)(s + 0x354)) >> 2;
    int b = (*(int*)(s + 0x344) - *(int*)(s + 0x340)) >> 2;
    return a + b;
}

// @ 0x00bbcb10
void TObj::FUN_00bbcb10(void* key, void* planet)
{
    uint32_t* k = (uint32_t*)key;
    if (k[0] != DAT_0168a488 || k[1] != DAT_0168a48c || k[2] != DAT_0168a490) {
        if (planet == 0) {
            planet = FUN_01021260();
        }
        ((TObj*)planet)->F_c745d0(0, key);
        TObj* x = (TObj*)((TObj*)planet)->F_8414c0();
        if (x != 0) {
            x->F_c80680(0, key);
        }
        void* p = *(void**)((char*)planet + 0x13c);
        if (*(uint32_t*)((char*)p + 0x2c) & 0x800) {
            FUN_01043c60(p, key);
        }
    }
}

// @ 0x00bbcd40
bool __cdecl FUN_00bbcd40(int param_1, int param_2)
{
    return CountFaces(param_1) < CountFaces(param_2);
}

// @ 0x00bbd0e0
int* TObj::FUN_00bbd0e0(int* node, int param_3, int** param_4)
{
    int iVar1 = *(int*)(param_3 + 0x14);
    node[1] = (int)param_4;
    *node = iVar1;
    while (iVar1 == 0) {
        node[1] += 4;
        iVar1 = *(int*)node[1];
        *node = iVar1;
    }
    int c = (int)*param_4;
    if (c == param_3) {
        *param_4 = (int*)*(int*)(c + 0x14);
        FUN_00f47380((void*)param_3);
        *(int*)((char*)this + 0xc) -= 1;
        return node;
    }
    int t = *(int*)(c + 0x14);
    while (t != param_3) {
        c = t;
        t = *(int*)(t + 0x14);
    }
    *(int*)(c + 0x14) = *(int*)(t + 0x14);
    FUN_00f47380((void*)param_3);
    *(int*)((char*)this + 0xc) -= 1;
    return node;
}

// @ 0x00bbd180
void __cdecl FUN_00bbd180(int* first, int param_2, int param_3, int hole, int param_5, CmpFn cmp)
{
    int iVar3;
    int iVar1;
    while (1) {
        iVar1 = hole * 2;
        iVar3 = iVar1 + 2;
        if (param_3 <= iVar3) {
            break;
        }
        if (cmp(first[iVar3], first[iVar3 - 1])) {
            iVar3 = iVar1 + 1;
        }
        first[hole] = first[iVar3];
        hole = iVar3;
    }
    if (iVar3 == param_3) {
        first[hole] = first[iVar3 - 1];
        hole = iVar1 + 1;
    }
    FUN_00d52cb0(first, param_2, hole, param_5, (void*)cmp);
}

// @ 0x00bbd1f0
void __cdecl FUN_00bbd1f0(int* arr, int param_2, int param_3, void* param_4, CmpFn cmp)
{
    int iVar3;
    while ((iVar3 = param_3, param_2 < iVar3)) {
        param_3 = (iVar3 - 1) >> 1;
        if (!((bool(__cdecl*)(int, void*))cmp)(arr[param_3], param_4)) {
            break;
        }
        int* piVar1 = (int*)arr[iVar3];
        int* piVar2 = (int*)arr[param_3];
        if (piVar2 != piVar1) {
            if (piVar2 != 0) {
                ((void(__thiscall*)(void*))VF(piVar2, 0))(piVar2);
            }
            arr[iVar3] = (int)piVar2;
            if (piVar1 != 0) {
                ((void(__thiscall*)(void*))VF(piVar1, 4))(piVar1);
            }
        }
    }
    int* piVar1b = (int*)arr[iVar3];
    void* p4 = param_4;
    if (p4 != piVar1b) {
        if (p4 != 0) {
            ((void(__thiscall*)(void*))VF(p4, 0))(p4);
        }
        arr[iVar3] = (int)p4;
        if (piVar1b != 0) {
            ((void(__thiscall*)(void*))VF(piVar1b, 4))(piVar1b);
        }
    }
    if (p4 != 0) {
        ((void(__thiscall*)(void*))VF(p4, 4))(p4);
    }
}

// @ 0x00bbd6c0
void __stdcall FUN_00bbd6c0(int* param_1)
{
    TObj* o = (TObj*)FUN_00b3d3b0();
    TObj* hud = (TObj*)*(void**)((char*)o + 0x38);
    hud->F_f921d0(0x80, 0);
    int n = (param_1[1] - param_1[0]) >> 4;
    if (n != 0) {
        int off = 0;
        do {
            int base = param_1[0];
            FUN_00bbd2a0((void*)(base + off), *(float*)(base + off + 0xc), hud);
            off += 0x10;
            n--;
        } while (n != 0);
    }
    TObj* q = (TObj*)FUN_00b3d3b0b(0xf);
    q->F_b2a750();
}

// @ 0x00bbd730
void __stdcall FUN_00bbd730(int* param_1, char param_2)
{
    if (*param_1 != param_1[1]) {
        bool hit = false;
        float step = ((PlanetModelObj*)FUN_00b3d350())->get_radius() * 0.0078125f;
        PlanetSceneObj* scene = (PlanetSceneObj*)FUN_00b3d3b0_s00bb_d730();
        char* grid = ((GridObj*)scene->field_38)->data;

        float* p = (float*)*param_1;
        float* end = (float*)param_1[1];
        float* next = p + 3;
        if (next == end)
            return;

        do {
            float x = p[0];
            float y = p[1];
            float z = p[2];
            float dx = next[0] - x;
            float dy = next[1] - y;
            float dz = next[2] - z;
            float len = (float)sqrtf(dz * dz + (dx * dx + dy * dy));

            if (1.5258789e-05f < len) {
                float inv = 1.0f / len;
                float t = 0.0f;
                if (0.0f < len) {
                    do {
                        float ax = (float)fabs(x);
                        float ay = (float)fabs(y);
                        float az = (float)fabs(z);
                        int i10, i11, i12;

                        if ((az < ax) || (az < ay)) {
                            if (ay < ax) {
                                i10 = (int)((y / x + 1.0f) * 64.0f);
                                i11 = (int)((z / ax + 1.0f) * 64.0f);
                                i12 = 2;
                                if (x < 0.0f)
                                    i12 = 3;
                            } else {
                                i10 = (int)((z / y + 1.0f) * 64.0f);
                                i11 = (int)((x / ay + 1.0f) * 64.0f);
                                if (y < 0.0f)
                                    i12 = 5;
                                else
                                    i12 = 4;
                            }
                        } else {
                            i10 = (int)((x / z + 1.0f) * 64.0f);
                            i11 = (int)((y / az + 1.0f) * 64.0f);
                            if (z < 0.0f)
                                i12 = 1;
                            else
                                i12 = 0;
                        }
                        if (i10 == 0x80)
                            i10 = 0x7f;
                        if (i11 == 0x80)
                            i11 = 0x7f;

                        char* cell = grid + ((i12 * 0x80 + i11) * 0x80 + i10);
                        if (*cell == 0)
                            hit = true;

                        x = inv * dx * step + x;
                        y = inv * dy * step + y;
                        z = inv * dz * step + z;
                        t = t + step;
                        *cell = (char)0xff;
                    } while (t < len);
                }

                {
                    float ex = next[0];
                    float ey = next[1];
                    float ez = next[2];
                    float ax = (float)fabs(ex);
                    float ay = (float)fabs(ey);
                    float az = (float)fabs(ez);
                    int i10, i11, i12;

                    if ((az < ax) || (az < ay)) {
                        if (ay < ax) {
                            i10 = (int)((ey / ex + 1.0f) * 64.0f);
                            i11 = (int)((ez / ax + 1.0f) * 64.0f);
                            i12 = 2;
                            if (ex < 0.0f)
                                i12 = 3;
                        } else {
                            i10 = (int)((ez / ey + 1.0f) * 64.0f);
                            i11 = (int)((ex / ay + 1.0f) * 64.0f);
                            if (ey < 0.0f)
                                i12 = 5;
                            else
                                i12 = 4;
                        }
                    } else {
                        i10 = (int)((ex / ez + 1.0f) * 64.0f);
                        i11 = (int)((ey / az + 1.0f) * 64.0f);
                        if (ez < 0.0f)
                            i12 = 1;
                        else
                            i12 = 0;
                    }
                    if (i10 == 0x80)
                        i10 = 0x7f;
                    if (i11 == 0x80)
                        i11 = 0x7f;

                    char* cell = grid + ((i12 * 0x80 + i11) * 0x80 + i10);
                    if (*cell == 0)
                        hit = true;
                    *cell = (char)0xff;
                }
            }

            p = next;
            next += 3;
        } while (next != end);

        if (hit && param_2 != 0) {
            ((DebugDrawObj*)FUN_00b3d3b0_s00bb_d730())->flush(0xf);
        }
    }
}

// @ 0x00bbdbf0
void __stdcall FUN_00bbdbf0(float* param_1, float param_2)
{
    float radius2 = param_2 * param_2;

    ((DebugDrawObj*)FUN_00b3d3b0_s00bb_d730())->begin(param_1, radius2);

    void* planet = FUN_01021260();
    if (planet == 0)
        return;
    RenderObj* render = (RenderObj*)((TerraObj*)planet)->fn_8414c0();
    if (render == 0)
        return;

    float cx = param_1[0];
    float cy = param_1[1];
    float cz = param_1[2];
    int key[4];
    byte flags[4];
    flags[0] = 0;
    flags[1] = 0;
    flags[2] = 0;

    float ax = (float)fabs(cx);
    float ay = (float)fabs(cy);
    float az = (float)fabs(cz);

    if ((az < ax) || (az < ay)) {
        if (ay < ax) {
            key[0] = (int)((cy / cx + 1.0f) * 2.0f);
            key[1] = (int)((cz / ax + 1.0f) * 2.0f);
            key[2] = 2;
            if (cx < 0.0f)
                key[2] = 3;
        } else {
            key[0] = (int)((cz / cy + 1.0f) * 2.0f);
            key[1] = (int)((cx / ay + 1.0f) * 2.0f);
            if (cy < 0.0f)
                key[2] = 5;
            else
                key[2] = 4;
        }
    } else {
        key[0] = (int)((cx / cz + 1.0f) * 2.0f);
        key[1] = (int)((cy / az + 1.0f) * 2.0f);
        if (cz < 0.0f)
            key[2] = 1;
        else
            key[2] = 0;
    }
    if (key[0] == 4)
        key[0] = 3;
    if (key[1] == 4)
        key[1] = 3;

    DrawBucketObj* bucket = (DrawBucketObj*)((char*)render + 0x50);
    int* qi = bucket->lookup(key);

    int n = 0;
    do {
        int* qn = qi + 4;
        if (*qn != 0) {
            *qn = 0;
            qi[1] = 0;
            qi[2] = 0;
            qi[3] = 0;
            flags[n] = 1;
        }
        n++;
        qi = qn;
    } while (n < 3);

    SurfaceObj* surface = (SurfaceObj*)FUN_00b3d350();
    int st[4];
    surface->first(st);

    while (st[3] != 0) {
        int idx = (st[2] >> 1) * 4;
        float gx = ((float)st[0] + 0.5f) * 0.5f - 1.0f;
        float gy = ((float)st[1] + 0.5f) * 0.5f - 1.0f;
        float inv = 1.0f / (float)sqrtf((gy * gy + gx * gx) + 1.0f);
        float s = inv;
        if ((st[2] & 1) != 0)
            s = -inv;

        unsigned char b0 = DAT_014665e0[idx];
        unsigned char b1 = DAT_014665e1[idx];
        unsigned char b2 = DAT_014665e2[idx];
        float dir[4];
        dir[b0] = s * gx;
        dir[b1] = inv * gy;
        dir[b2] = s;

        float out[4];
        float* sp = surface->DirectionToSurfacePosition(out, dir);
        dir[0] = sp[0];
        dir[1] = sp[1];
        dir[2] = sp[2];

        float dx = dir[0] - param_1[0];
        float dy = dir[1] - param_1[1];
        float dz = dir[2] - param_1[2];
        if ((dx * dx + dy * dy + dz * dz) < radius2) {
            int off = 0;
            int i = 0;
            do {
                if (*(int*)(off + 0x10 + st[3]) != 0) {
                    *(int*)(off + 0x10 + st[3]) = 0;
                    flags[i] = 1;
                }
                off += 0x10;
                i++;
            } while (off < 0x30);
        }
        surface->next(st);
    }

    unsigned out = (flags[0] != 0) ? 1u : 0u;
    if (flags[1] != 0)
        out |= 2;
    if (flags[2] != 0)
        out |= 4;
    ((DebugDrawObj*)FUN_00b3d3b0_s00bb_d730())->flush(out);
}

// @ 0x00bbdff0
void __stdcall FUN_00bbdff0(float* param_1, float param_2)
{
    RenderObj* render = (RenderObj*)((TerraObj*)FUN_01021260())->fn_8414c0();
    if (render == 0)
        return;

    float cx = param_1[0];
    float cy = param_1[1];
    float cz = param_1[2];
    int key[4];
    float ax = (float)fabs(cx);
    float ay = (float)fabs(cy);
    float az = (float)fabs(cz);

    if ((az < ax) || (az < ay)) {
        if (ay < ax) {
            key[0] = (int)((cy / cx + 1.0f) * 2.0f);
            key[1] = (int)((cz / ax + 1.0f) * 2.0f);
            key[2] = 2;
            if (cx < 0.0f)
                key[2] = 3;
        } else {
            key[0] = (int)((cz / cy + 1.0f) * 2.0f);
            key[1] = (int)((cx / ay + 1.0f) * 2.0f);
            if (cy < 0.0f)
                key[2] = 5;
            else
                key[2] = 4;
        }
    } else {
        key[0] = (int)((cx / cz + 1.0f) * 2.0f);
        key[1] = (int)((cy / az + 1.0f) * 2.0f);
        if (cz < 0.0f)
            key[2] = 1;
        else
            key[2] = 0;
    }
    if (key[0] == 4)
        key[0] = 3;
    if (key[1] == 4)
        key[1] = 3;

    DrawBucketObj* bucket = (DrawBucketObj*)((char*)render + 0x50);
    int* qi = bucket->lookup(key);
    if (*(int*)((char*)qi + 0x40) != 0)
        *(int*)((char*)qi + 0x40) = 0;
    if (*(int*)((char*)qi + 0x50) != 0)
        *(int*)((char*)qi + 0x50) = 0;

    SurfaceObj* surface = (SurfaceObj*)FUN_00b3d350();
    int st[4];
    surface->first(st);

    float radius2 = param_2 * param_2;

    while (st[3] != 0) {
        int idx = (st[2] >> 1) * 4;
        float gx = ((float)st[0] + 0.5f) * 0.5f - 1.0f;
        float gy = ((float)st[1] + 0.5f) * 0.5f - 1.0f;
        float inv = 1.0f / (float)sqrtf((gy * gy + gx * gx) + 1.0f);
        float s = inv;
        if ((st[2] & 1) != 0)
            s = -inv;

        unsigned char b0 = DAT_014665e0[idx];
        unsigned char b1 = DAT_014665e1[idx];
        unsigned char b2 = DAT_014665e2[idx];
        float dir[4];
        dir[b0] = s * gx;
        dir[b1] = inv * gy;
        dir[b2] = s;

        float out[4];
        float* sp = surface->DirectionToSurfacePosition(out, dir);
        dir[0] = sp[0];
        dir[1] = sp[1];
        dir[2] = sp[2];

        float dx = param_1[0] - dir[0];
        float dy = param_1[1] - dir[1];
        float dz = param_1[2] - dir[2];
        if ((dx * dx + dy * dy + dz * dz) < radius2) {
            int off = 0x40;
            do {
                if (*(int*)(off + st[3]) != 0)
                    *(int*)(off + st[3]) = 0;
                off += 0x10;
            } while (off < 0x60);
        }
        surface->next(st);
    }
}

// @ 0x00bbe370
bool TerraformingManager::check_requirements(int param)
{
    if (param == 0)
        param = (int)FUN_010212a0();
    int rec = param;
    if (rec == 0)
        rec = (int)FUN_010212a0();

    int dist = TerraDistClass(*(float*)(rec + 0xb0), *(float*)(rec + 0xb4));

    int key[3];
    int* a = query(key, dist, 0x6d60a1cc, param);
    if (a[0] == DAT_0168a488_s00bb_d730 && a[1] == DAT_0168a48c_s00bb_d730 && a[2] == DAT_0168a490_s00bb_d730) {
        a = query(key, dist, 0x29c388a, param);
        if (a[0] == DAT_0168a488_s00bb_d730 && a[1] == DAT_0168a48c_s00bb_d730 && a[2] == DAT_0168a490_s00bb_d730) {
            a = query(key, dist, 0x3a8be428, param);
            if (a[0] == DAT_0168a488_s00bb_d730 && a[1] == DAT_0168a48c_s00bb_d730 && a[2] == DAT_0168a490_s00bb_d730)
                return false;
        }
    }
    return true;
}

// @ 0x00bbe470
int TerraformingManager::unlocked_count(int param)
{
    unsigned count;
    float len, scale;
    float* m;
    int sortval, other, av;

    if (param == 0)
        param = *(int*)((char*)FUN_01021260() + 0x13c);

    sortval = ((CityHolder*)param)->fn_b8de30();
    StarMgr* star = FUN_00b3d2a0();
    other = star->fn_885c90();
    av = ((AvatarObj*)sortval)->fn_b1fdb0();

    if (av == other) {
        StarMgr* star2 = FUN_00b3d2a0();
        if (sortval == ((AvatarObj*)star2->fn_00ba93b0())->fn_c30c60())
            return 3;

        float* cities = ((CityHolder*)((CityHolder*)param)->fn_b8de30())->GetCities();
        len = (float)sqrt(cities[0] * cities[0] + cities[1] * cities[1] +
                          cities[2] * cities[2]);
        StarMgr* star3 = FUN_00b3d2a0();
        scale = star3->field_1bc;
        m = FUN_01029940()->GetModelOffset();
        count = (len < m[0] * scale) ? 1u : 0u;
        if (len < m[1] * scale)
            count++;
        if (len < m[2] * scale)
            count++;
    } else {
        if ((*(unsigned*)(param + 0x2c) & 0x800) != 0)
            return 0;
        count = (unsigned)fn_bbce40(param);
    }

    return (int)count > 1 ? (int)count : 1;
}

// @ 0x00bbe5c0
bool TerraformingManager::has_unlocks(int param)
{
    if (param == 0)
        param = *(int*)((char*)FUN_01021260() + 0x13c);
    return fn_bbce40(param) > 0;
}

// @ 0x00bbe5f0
int SimSelf::FUN_00bbe5f0(PlanetRecord* record)
{
    if (record == 0)
        record = GetActivePlanetRecord();

    void* noun = ((ViewRecord*)record)->getNoun();
    void* star = GetStarManager();
    void* gang0 = ((ViewStar*)star)->FUN_00885c90();
    void* avatar = ((ViewNoun*)noun)->GetAvatar();

    if (avatar == gang0) {
        void* civ = ((ViewRecord*)record)->getNoun();
        float* cities = (float*)((ViewCivData*)civ)->GetCities();
        float fVar2 = (float)sqrt(cities[0] * cities[0] + cities[1] * cities[1] + cities[2] * cities[2]);
        void* tm = GetStarManager();
        float fVar1 = *(float*)((char*)tm + 0x1bc);
        GetSpaceCombatTuning();
        float* lim = ((ViewSCTuning*)GetSpaceCombatTuning())->GetModelOffset();
        int cVar10 = fVar2 < lim[0] * fVar1;
        if (fVar2 < lim[1] * fVar1)
            cVar10 += 1;
        if (fVar2 < lim[2] * fVar1)
            cVar10 += 1;
        switch (cVar10) {
        case 0: return 1;
        case 1: return ((ViewTuning*)FUN_01049a10())->getT1();
        case 2: return ((ViewTuning*)FUN_01049a10())->getT2();
        case 3: return ((ViewTuning*)FUN_01049a10())->getT3();
        }
    }

    if ((record->flags2c & 0x800) != 0)
        return 1;
    int tier = ((ViewRecord*)record)->FUN_00bbce40();
    if (tier == 1) return ((ViewTuning*)FUN_01049a10())->getT1();
    if (tier == 2) return ((ViewTuning*)FUN_01049a10())->getT2();
    if (tier != 3) return 1;
    return ((ViewTuning*)FUN_01049a10())->getT3();
}

// @ 0x00bbe740
int SimSelf::FUN_00bbe740(PlanetRecord* record)
{
    int total = 0;
    if (record == 0)
        record = GetActivePlanet();

    if (FUN_00c70e00(record) == 5 && GetCurrentGameMode() == (void*)0x01654c05) {
        void* emp = GetPlayerEmpire();
        FUN_00c308e0(emp, (void*)record->p_13c);
        PlanetRecord* active = GetActivePlanet();
        if (record != active || GetUniverseContext() != 0) {
            void* begin = 0; void* end = 0;
            FUN_00c73520(record, &begin);
            for (void** it = (void**)begin; it != (void**)end; ++it) {
                void* city = *it;
                int n = ((ViewCity*)city)->GetNumBuildings();
                int t = ((ViewCity*)city)->GetNumTurrets();
                void* arg = (void*)record->p_13c;
                TerraformingManager();
                int mx = ((ViewTerrMgr*)arg)->FUN_00bbe5f0(arg ? record : record);
                (void)mx;
                if (mx < n + t) {
                    ((ViewCity*)city)->ClampBuildings(mx, (void*)record->p_13c);
                    total += (n + t) - mx;
                }
            }
            if (begin != 0 && ((int*)begin)[-1] != 0)
                operator_delete__(begin);
        }
        return total;
    }
    return 0;
}

// @ 0x00bbe850
bool SimSelf::FUN_00bbe850(int param_1, int param_2, PlanetRecord* record)
{
    if (record == 0)
        record = GetActivePlanetRecord();
    if (param_1 != 1) {
        if (FUN_00bbcda0(param_1 - 1, record) == 0)
            return false;
    }
    if (param_2 < 4)
        return true;
    return param_1 * 3 <= (int)(record->p_c0 - record->p_bc) / 0xc;
}

// @ 0x00bbe8c0
void* SimAllocHelper::FUN_00bbe8c0(const Node18* src)
{
    Node18* p = (Node18*)EAAllocate(0x18, "Simulator", 0, 0, &g_EAAllocSite, 0xd1);
    if (p != 0) {
        p->a = src->a;
        p->b = src->b;
        p->c = src->c;
        p->d = src->d;
        p->e = src->e;
    }
    *(int*)((char*)p + 0x14) = 0;
    return p;
}

// @ 0x00bbe910
void SimListHelper::FUN_00bbe910(int head, int* payload)
{
    int* node = (int*)EAAllocate(0x14, "Simulator", 0, 0, &g_EAAllocSite, 0xd1);
    int* dst = node + 2;
    if (dst != 0) {
        dst[0] = payload[0];
        dst[1] = payload[1];
        dst[2] = payload[2];
    }
    node[0] = head;
    node[1] = *(int*)(head + 4);
    **(int**)(head + 4) = (int)node;
    *(int**)(head + 4) = node;
}

// @ 0x00bbe970
void FUN_00bbe970(RefObj** begin, RefObj** end, bool (*cmp)(RefObj*, RefObj*))
{
    for (RefObj** cur = begin + 1; cur != end; ++cur) {
        RefObj* val = *cur;
        if (val != 0)
            val->addRef();
        RefObj** pos = cur;
        while (pos != begin && cmp(val, pos[-1])) {
            RefObj* prev = pos[-1];
            RefObj* here = *pos;
            if (prev != here) {
                if (prev != 0) prev->addRef();
                *pos = prev;
                if (here != 0) here->release();
            }
            --pos;
        }
        RefObj* at = *pos;
        if (val != at) {
            if (val != 0) val->addRef();
            *pos = val;
            if (at != 0) at->release();
        }
        if (val != 0) val->release();
    }
}

// @ 0x00bbea40
void FUN_00bbea40(RefObj2** a, int lo, int hi, int hole, RefObj2* value, bool (*cmp)(void*, void*))
{
    int i = hole;
    for (;;) {
        int child = i * 2 + 2;
        if (hi <= child) break;
        if (cmp(a[child], a[child - 1]))
            --child;
        RefObj2* cur = a[i];
        RefObj2* nxt = a[child];
        if (nxt != cur) {
            if (nxt != 0) nxt->addRef();
            a[i] = nxt;
            if (cur != 0) cur->release();
        }
        i = child;
    }
    if (i == hi) {
        RefObj2* cur = a[i];
        RefObj2* nxt = a[i - 1];
        if (nxt != cur) {
            if (nxt != 0) nxt->addRef();
            a[i] = nxt;
            if (cur != 0) cur->release();
        }
        ++i;
    }
    if (value != 0)
        value->addRef();
    FUN_00bbd1f0(a, lo, i, value, cmp, value);
    if (value != 0)
        value->release();
}

// @ 0x00bbeb20
void FUN_00bbeb20(RefObj** a, RefObj** end, bool (*cmp)(void*, void*))
{
    int n = (int)((char*)end - (char*)a) >> 2;
    if (1 < n) {
        int i = ((n - 2) >> 1) + 1;
        do {
            int v = (int)a[i - 1];
            --i;
            FUN_00bbd180_s00bb_e5f0(a, i, n, i, (void*)v, (void*)cmp);
        } while (i != 0);
    }
}

// @ 0x00bbeb60
void FUN_00bbeb60(RefObj** a, RefObj** end, bool (*cmp)(void*, void*))
{
    int n = (int)((char*)end - (char*)a) >> 2;
    if (1 < n) {
        RefObj** p = end - 1;
        do {
            int v = (int)*p;
            *p = *a;
            FUN_00bbd180_s00bb_e5f0(a, 0, n - 1, 0, (void*)v, (void*)cmp);
            --p;
            n = (int)((char*)p - (char*)a) >> 2;
        } while (1 < n);
    }
}

// @ 0x00bbebb0
void SimSubDtor::FUN_00bbebb0()
{
    ViewHash1c* h = (ViewHash1c*)((char*)this + 0x1c);
    char* p = (char*)this;
    *(void**)p = (void*)0x01466670;
    *(void**)(p + 4) = (void*)0x0146666c;
    ((ViewVector*)(p + 0x68))->dtor();
    ((ViewRBTree*)(p + 0x48))->nuke(*(void**)(p + 0x54));
    h->release(*(void**)(p + 0x20), *(void**)(p + 0x24));
    uint cnt = h->cnt8;
    h->n_c = 0;
    if (cnt > 1)
        operator_delete__(h->m4);
    ((ViewGonzago*)p)->dtor();
}

// @ 0x00bbec60
bool SimHashOwner::FUN_00bbec60(int key)
{
    char* p = (char*)this;
    int local_8 = 0;
    int local_4 = 0;
    ViewHash1c* ht = (ViewHash1c*)(p + 0x1c);
    ht->find(&local_8, &key);
    if (local_8 == *(int*)(*(int*)(p + 0x20) + *(int*)(p + 0x24) * 4))
        return false;
    struct Pair8 { int a; int b; } pair;
    pair.a = local_8;
    pair.b = local_4;
    ht->insert(&pair);
    *(uint8_t*)(p + 0x3c) = 1;
    return true;
}

// @ 0x00bbecc0
int SimSelf::FUN_00bbecc0(int* buildingId, PlanetRecord* record, int param_2, uint8_t* out)
{
    if (record == 0)
        record = GetActivePlanetRecord();
    PlanetRecord* r2 = record ? record : GetActivePlanetRecord();
    if (FUN_00fc2080(r2->p_b0, r2->p_b4) == 0)
        return 0;

    int count = (int)(record->p_c0 - record->p_bc) / 0xc;
    int i = 0, matches = 0;
    for (int off = 0; i < count; ++i, off += 0xc) {
        int* e = (int*)(record->p_bc + off);
        if (buildingId[0] == e[0] && buildingId[1] == e[1] && buildingId[2] == e[2])
            return 1;
        void* s1 = ((ViewSpecies*)e)->FUN_00b3d420();
        (void)s1;
        ((ViewSpecies*)e)->FUN_00b90410();
        if (((ViewSpecies*)e)->FUN_00b8f860() == param_2)
            ++matches;
    }
    ++matches;

    uint8_t cVar2;
    if (param_2 == 0x6d60a1cc) cVar2 = 1;
    else cVar2 = (uint8_t)((param_2 != 0x29c388a) + 2);

    bool bVar1 = false;
    if (matches < 4) {
        PlanetRecord* r3 = record ? record : GetActivePlanetRecord();
        r3 = r3 ? r3 : GetActivePlanetRecord();
        int lim = FUN_00fc2080(r3->p_b0, r3->p_b4);
        if (matches <= lim) {
            bVar1 = true;
            if (FUN_00bbe850(matches, cVar2, record) != 0)
                return 1;
        }
    }
    if (out) *out = !bVar1;
    return 0;
}

// @ 0x00bbee30
int SimSelf::FUN_00bbee30(int* buildingId, int param_2, uint8_t param_3, PlanetRecord* record, uint8_t* out)
{
    uint8_t flag = param_3;
    if (record == 0)
        record = GetActivePlanetRecord();
    PlanetRecord* r2 = record ? record : GetActivePlanetRecord();
    if (FUN_00fc2080(r2->p_b0, r2->p_b4) == 0) {
        if (out) *out = 1;
        return 0;
    }

    if ((record->flags2c & 0x800) != 0) {
        if (out) *out = 0;
        int limit = 100;
        void* tun = FUN_01049a10();
        void* sub = *(void**)tun;
        if (sub != 0) {
            int ok = (*(int(**)(void*, uint8_t*, int))(*(int*)sub + 0x24))(sub, &flag, 0x05469bf8);
            if (ok && *(short*)((char*)buildingId + 0x12) == 9) {
                int* v = (int*)0;
                (void)v;
                limit = 0;
                if (limit < 1) return 1;
            }
        }
        if ((int)(record->p_d4 - record->p_d0) / 0xc < limit)
            return 1;
        return 0;
    }

    int off = 0, a = 0, b = 0, n = 0;
    FUN_00401090((void*)0);
    int count = (int)(record->p_d4 - record->p_d0) / 0xc;
    int i = 0;
    for (; i < count; ++i, off += 0xc) {
        int* e = (int*)(record->p_d0 + off);
        if (buildingId[0] == e[0] && buildingId[1] == e[1] && buildingId[2] == e[2])
            return 1;
        int o = FUN_004df550(e);
        if (o != 0) {
            if (*(int*)(o + 0x608) == 0) ++a;
            else ++b;
        }
        n = a;
    }
    (void)n;

    if (flag == 0) {
        int half = a / 2 + 1;
        uint urem = (uint)a & 0x80000001u;
        if ((int)urem < 0) urem = (urem - 1 | 0xfffffffeu) + 1;
        if (half < 4 && FUN_00bbc6a0(half, record) != 0) {
            flag = 1;
            if (FUN_00bbe850(half, (int)urem + 4, record) != 0)
                return 1;
        } else {
            flag = 0;
        }
        if (out) *out = (flag == 0);
    } else {
        ++b;
        bool bVar1 = false;
        if (b < 4 && FUN_00bbc6a0(b, record) != 0) {
            bVar1 = true;
            if (FUN_00bbe850(b, 6, record) != 0)
                return 1;
        }
        if (out) { *out = !bVar1; return 0; }
    }
    return 0;
}

// @ 0x00bbf130
void FUN_00bbf130(RefObj** a, RefObj** mid, RefObj** end, bool (*cmp)(void*, void*))
{
    FUN_00bbeb20(a, mid, cmp);
    for (RefObj** it = mid; it < end; ++it) {
        if (cmp(*it, *a)) {
            RefObj* v = *it;
            *it = *a;
            FUN_00bbd180_s00bb_e5f0(a, 0, (int)((char*)mid - (char*)a) >> 2, 0, (void*)v, (void*)cmp);
        }
    }
    FUN_00bbeb60(a, mid, cmp);
}

// @ 0x00bbf1a0
void FUN_00bbf1a0(RefObj2** a, RefObj2** end, bool (*cmp)(void*, void*))
{
    int n = (int)((char*)end - (char*)a) >> 2;
    if (1 < n) {
        int i = ((n - 2) >> 1) + 1;
        do {
            --i;
            RefObj2* v = a[i];
            if (v != 0)
                v->addRef();
            FUN_00bbea40(a, i, n, i, v, cmp);
        } while (i != 0);
    }
}

// @ 0x00bbf1f0
void* SimSaveGame::FUN_00bbf1f0()
{
    char* p = (char*)this;
    ((ViewGonzago*)p)->ctor();
    float kOne = g_kOne;
    float kTwo = g_kTwoThirds2;
    *(void**)p = (void*)0x01466670;
    *(void**)(p + 4) = (void*)0x0146666c;
    *(float*)(p + 0x2c) = kOne;
    *(float*)(p + 0x30) = kTwo;
    *(int*)(p + 0x28) = 0;
    *(int*)(p + 0x34) = 0;
    *(void**)(p + 0x20) = (void*)0x0154df28;
    *(int*)(p + 0x24) = 1;
    *(uint8_t*)(p + 0x3c) = 1;
    *(uint8_t*)(p + 0x44) = 0;
    *(int*)(p + 0x40) = -1;
    *(int*)(p + 0x50) = 0;
    *(int*)(p + 0x54) = 0;
    *(int*)(p + 0x58) = 0;
    *(int*)(p + 0x54) = 0;
    *(uint8_t*)(p + 0x58) = 0;
    *(int*)(p + 0x5c) = 0;
    *(void**)(p + 0x50) = p + 0x4c;
    *(void**)(p + 0x4c) = p + 0x4c;
    *(int*)(p + 0x64) = 0;
    *(int*)(p + 0x68) = 0;
    *(int*)(p + 0x6c) = 0;
    *(int*)(p + 0x70) = 0;
    *(int*)(p + 0x7c) = 0;
    *(int*)(p + 0x80) = 0;
    *(int*)(p + 0x84) = 0;
    *(int*)(p + 0x88) = 0;
    *(int*)(p + 0x8c) = 0;
    *(int*)(p + 0x90) = 0;
    return p;
}

// @ 0x00bbf2b0
void SimSelf::FUN_00bbf2b0(PlanetRecord* record)
{
    if (record == 0)
        record = GetActivePlanet();

    PlanetRecord* r0 = (PlanetRecord*)record->p_13c;
    if (r0 == 0)
        r0 = GetActivePlanetRecord();
    int lim = FUN_00fc2080(r0->p_b0, r0->p_b4);
    uint uVar2 = *(uint*)(record->p_13c + 0x2c);

    for (int tier = 3; tier >= 1; --tier) {
        if (lim < tier) {
            FUN_00bbcb90(tier, record);
        } else {
            PlanetRecord* r1 = (PlanetRecord*)record->p_13c;
            if (r1 == 0)
                r1 = GetActivePlanetRecord();
            if (r1 == 0)
                r1 = GetActivePlanetRecord();
            int lim2 = FUN_00fc2080(r1->p_b0, r1->p_b4);
            if (lim2 < tier) {
                FUN_00bbcb90(tier, record);
            } else {
                int tmp[3];
                void* p = FUN_00bbc870(tmp, tier, 0x6d60a1cc, record);
                int uVar10 = (p != 0) ? 1 : 1;
                (void)uVar10;
                FUN_00bbc870(tmp, tier, 0x29c388a, record);
                FUN_00bbc870(tmp, tier, 0x3a8be428, record);
                if (((uVar2 >> 0xb) & 1) == 0) {
                    int out[3];
                    FUN_00bbc950(out, tier, 1, record);
                    FUN_00bbc950(out, tier, 0, record);
                    FUN_00bbca30(out, tier, record);
                }
            }
        }
    }
}

// @ 0x00bbf630
int* SimHash::FUN_00bbf630(const int* key)
{
    int found[4];
    find(found, key);
    if (found[0] == *(int*)(mpBuckets + mnBucket * 4)) {
        int value[5];
        value[0] = key[0];
        value[1] = found[0];
        value[2] = found[1];
        value[3] = found[2];
        value[4] = found[3];
        insert(found, value, (void*)((uint)key & 0xffffff00u));
    }
    return (int*)(found[0] + 4);
}

// @ 0x00bbf730
int SimSelf_s00bb_f630::FUN_00bbf730(const int* src, float f)
{
    ++g_0168a478;
    int* p = mHash.FUN_00bbf630((const int*)&g_0168a478);
    p[0] = src[0];
    p[1] = src[1];
    p[2] = src[2];
    *(float*)(p + 3) = f;
    mb3c = 1;
    return (int)g_0168a478;
}

// @ 0x00bbf860
void SimSelf_s00bb_f630::FUN_00bbf860()
{
    if (mb44 == 0)
        return;

    mHash.deallocate(mHash.mpBuckets, mHash.mnBucket);
    mHash.mUnknown0c = 0;

    mTree.nuke(mTree.mAnchor.mpNodeParent);
    mTree.mAnchor.mpNodeRight  = (RBNodeBase*)&mTree.mAnchor;
    mTree.mAnchor.mpNodeLeft   = (RBNodeBase*)&mTree.mAnchor;
    mTree.mAnchor.mpNodeParent = 0;
    mTree.mAnchor.mColor       = 0;
    mTree.mnSize               = 0;
    mb44                       = 0;

    void* planet = FUN_01021260();
    if (planet != 0) {
        void* rec = *(void**)((char*)planet + 0x13c);
        if (rec == 0)
            rec = FUN_010212a0();
        int lim = FUN_00fc2080(*(float*)((char*)rec + 0xb0), *(float*)((char*)rec + 0xb4));
        for (int tier = 3; tier > lim; --tier)
            FUN_00bbcb90(tier, planet);
    }

    void** it  = mVec.mpBegin;
    void** end = mVec.mpEnd;
    for (; it != end; ++it)
        SP_NounManager()->RemoveNoun(*it);

    void* begin = mVec.mpBegin;
    void* last  = mVec.mpEnd;
    void** p    = (void**)FUN_006782c0(last, last, begin);
    for (void** e = (void**)last; p < e; ++p) {
        AutoRef* o = (AutoRef*)*p;
        if (o != 0)
            o->Release();
    }
    mVec.mpEnd = (void**)begin;

    m7c = g_0168a488;
    m80 = g_0168a48c;
    m84 = g_0168a490;
    m88 = g_0168a488;
    m8c = g_0168a48c;
    m90 = g_0168a490;
}

// @ 0x00bbfa30
void insertion_sort(Elem12* first, Elem12* last, KeyIntern intern, AllocNode* cleanup)
{
    if (first != last) {
        for (Elem12* i = first + 1; i != last; ++i) {
            Elem12 value = *i;
            Elem12* j = i;
            if (j != first) {
                do {
                    Elem12* prev = j - 1;
                    int* kp = intern.intern(prev);
                    int* kv = intern.intern(&value);
                    if (*kv <= *kp)
                        break;
                    *j = *prev;
                    --j;
                } while (j != first);
            }
            *j = value;
        }
    }

    while (cleanup) {
        intern.nuke(cleanup->mpRoot);
        AllocNode* next = cleanup->mpNext;
        operator_delete__(cleanup);
        cleanup = next;
    }
}

// @ 0x00bbfb10
void insertion_sort_simple(Elem12* first, Elem12* last, KeyIntern intern, AllocNode* cleanup)
{
    for (; first != last; ++first) {
        Elem12 value = *first;
        Elem12* prev = first - 1;
        Elem12* at   = first;
        int* kp = intern.intern(prev);
        int* kv = intern.intern(&value);
        if (*kv > *kp) {
            do {
                *at = *prev;
                --prev;
                --at;
                kp = intern.intern(prev);
                kv = intern.intern(&value);
            } while (*kv > *kp);
        }
        *at = value;
    }

    while (cleanup) {
        intern.nuke(cleanup->mpRoot);
        AllocNode* next = cleanup->mpNext;
        operator_delete__(cleanup);
        cleanup = next;
    }
}

// @ 0x00bbfbf0
Elem12* median(Elem12* a, Elem12* b, Elem12* c, KeyIntern intern, AllocNode* cleanup)
{
    if (*intern.intern(a) > *intern.intern(b)) {
        if (*intern.intern(b) > *intern.intern(c)) {
            intern.nuke(cleanup);
            return b;
        }
        if (*intern.intern(a) > *intern.intern(c)) {
            intern.nuke(cleanup);
            return c;
        }
        intern.nuke(cleanup);
        return a;
    } else {
        if (*intern.intern(a) > *intern.intern(c)) {
            intern.nuke(cleanup);
            return a;
        }
        if (*intern.intern(b) > *intern.intern(c)) {
            intern.nuke(cleanup);
            return c;
        }
        intern.nuke(cleanup);
        return b;
    }
}

// @ 0x00bbfce0
Elem12* get_partition(Elem12* first, Elem12* last, Elem12 pivot, KeyIntern intern, AllocNode* cleanup)
{
    for (;;) {
        while (*intern.intern(first) > *intern.intern(&pivot))
            ++first;
        --last;
        while (*intern.intern(&pivot) > *intern.intern(last))
            --last;
        if (first >= last)
            break;
        Elem12 t = *first;
        *first = *last;
        *last = t;
        ++first;
    }

    while (cleanup) {
        intern.nuke(cleanup->mpRoot);
        AllocNode* next = cleanup->mpNext;
        operator_delete__(cleanup);
        cleanup = next;
    }
    return first;
}

// @ 0x00bbfdc0
void sift_down(Elem12* heap, int lo, int hi, Elem12 value, KeyIntern intern, AllocNode* cleanup)
{
    int i = hi;
    int parent = (i - 1) >> 1;
    while (i > lo) {
        Elem12* p = heap + parent;
        if (*intern.intern(p) <= *intern.intern(&value))
            break;
        heap[i] = *p;
        i = parent;
        parent = (i - 1) >> 1;
    }
    heap[i] = value;

    while (cleanup) {
        intern.nuke(cleanup->mpRoot);
        AllocNode* next = cleanup->mpNext;
        operator_delete__(cleanup);
        cleanup = next;
    }
}

// @ 0x00bbfe80
void SimSelf_s00bb_f630::FUN_00bbfe80()
{
    if (FUN_01021080() == 0 || FUN_01021080() == -1)
        FUN_00bbf860();
    m40 = -1;
}

// @ 0x00bbfeb0
void FUN_00bbfeb0(void* planet)
{
    cGameNounManager* nm = SP_NounManager();
    GameDataVector* dv = (GameDataVector*)nm->GetGameDataVector(
        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xae5ea0, (void*)0xb1e500, 0x403df5c);
    int n = (int)(dv->mpEnd - dv->mpBegin);

    for (int i = 0; i < n; ++i) {
        Entry* node = (Entry*)EAAllocate(8, "Simulator/cCommodityNodeData", 0, 0, 0, 0);
        if (node != 0)
            node = (Entry*)node->FillPair(dv->mpBegin[i]);
        ((Entry*)dv->mpBegin[i])->FUN_00bfe220(node);
        ((PlanetRecord_s00bb_f630*)planet)->FUN_00c72dd0(node);
    }
}

// @ 0x00bbff40
void FUN_00bbff40(void* planet)
{
    cGameNounManager* nm = SP_NounManager();
    GameDataVector* dv = (GameDataVector*)nm->GetGameDataVector(
        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xae5ea0, (void*)0xb1e500, 0x403df5c);

    OtherVec* other = ((PlanetRecord_s00bb_f630*)planet)->FUN_00c71020();
    int n = (int)(other->mpEnd - other->mpBegin);
    int m = (int)(dv->mpEnd - dv->mpBegin);
    if (n != m)
        return;

    for (int i = 0; i < n; ++i) {
        Entry*    c = (Entry*)dv->mpBegin[i];
        OtherRec* o = other->mpBegin[i];
        c->FUN_00bfe220(o);
        c->v48(o->mpNoun);
        if (o->mState > 0) {
            if (c->m1ec < 4)
                c->FUN_00bff6e0(c->v4c());
        } else {
            c->SetState(o->mState);
        }
    }
}
