// src/game/SPGonzago/_at_00ba0000.cpp -- migrated from slice(s) s00ba9810, s00ba8830, s00ba7720, s00ba6750, s00ba47b0, s00ba3860, s00ba2590, s00ba0770, s00b9f9b0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00ba0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cPlanetModel.h"
#include "SP/cITerrainSphere.h"
#include "SP/cPlanetRecord.h"
#include "SP/cPropertyManager.h"
#include "SP/cStarClue.h"
#include "SP/cStarRecord.h"
#include "SP/cTerrainSphere.h"
#include "SP/cTelemetry.h"
#include <math.h>
#include "EA/Random/RandomLinearCongruential.h"

// unnamed retail callees and globals (address in the comment)
extern float g_flt10000;                        // 0x013f0620
extern float g_flt2;                            // 0x01470f1c
extern float g_identityMatrix;   // 0x01688924  identity basis copied into the placement

// ---- items of slice s00b9f9b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_00b974c0(void* a, void* b, void* c);               // 0x00b974c0
void  __cdecl operator_delete(void* p);                               // 0x00f47380
struct Call2 { void f(void* a, void* b); };
struct Call1 { void f(void* a); };
struct ElemVec18
{
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    void push_back_uninitialised();
    void clear();
};
struct GrowTemp
{
    int    mPad0;
    void*  mpPtr;      // +0x04
    void*  mPad1;
    void*  mPad2;
    int    mPad3[2];
};
struct Elem34
{
    int   mPad0;          // +0x00
    int   mPad4;
    int   mPad8;
    int   mPadC;
    int   mPad10;
    int   mPad14;
    int   mPad18;
    void* mpBegin;        // +0x1c  tree head, points at itself when empty
    void* mpEnd;          // +0x20
    void* mpCap;          // +0x24
    unsigned char mFlag;  // +0x28
    unsigned char mPad29;
    unsigned char mPad2A;
    unsigned char mPad2B;
    int   mVal;           // +0x2c
    int   mPad30;         // +0x30
    void InitTree()
    {
        void** h = &mpBegin;
        mpBegin = 0;
        mpEnd = 0;
        mpCap = 0;
        h[0] = h;
        h[1] = h;
        mFlag = 0;
        mVal = 0;
    }
};
struct ElemVec34
{
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    void push_back_uninitialised();
};
extern float g_flt10000;                        // 0x013f0620
extern float g_flt2;                            // 0x01470f1c
void* __cdecl FUN_00921340(int id);             // 0x00921340
struct Call7 { void f(void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7); };
struct FixedPool
{
    int    mHead;      // +0x00
    int    mPad4;      // +0x04
    char*  mpBegin;    // +0x08
    char*  mpEnd;      // +0x0c
    int    mElemSize;  // +0x10
    void*  mpOwner;    // +0x14
    void init(void* base, int bytes, int elemSize, int align, int flags);
};
struct PoolProbe
{
    int mPad0[6];
    unsigned grow(float f);
};
struct Vec2 { float x, y; };
struct SimObj
{
    int      mPad0[2];   // +0x00
    unsigned mMax8;      // +0x08
    char*    mpEndC;     // +0x0c
    Vec2     mVec10;     // +0x10
    int      m18;        // +0x18
    int      mPad1C[6];  // +0x1c
    void*    mpCtx34;    // +0x34
    int      mPad38[17]; // +0x38
    int      mPool7C[0x120];
    SimObj*  setup(void* a2, void* a3);
};
struct Vector3
{
    float x, y, z;
    Vector3* Self();
};
struct ChildVec
{
    int* mpBegin;      // +0x00
    int* mpEnd;        // +0x04
    unsigned size() { return (unsigned)((char*)mpEnd - (char*)mpBegin) >> 2; }
};
struct iSurfaceShape
{
    virtual void*  v00();
    virtual void*  v04();
    virtual void*  v08();
    virtual void*  v0c();
    virtual void*  v10();
    virtual void*  v14();
    virtual void*  v18();
    virtual void*  v1c();
    virtual void*  v20();
    virtual void*  v24();
    virtual void*  v28();
    virtual float* GetPosition();             // slot 0x2c
    virtual unsigned GetSurfaceID();          // slot 0x30
};
struct StarRec
{
    int            mPad0[13];   // +0x00
    iSurfaceShape* mpShape;     // +0x34
    int            mPad38[1];   // +0x38
    ChildVec       mChildren;   // +0x3c
    int            mPad44[49];  // +0x44
    int            mType;       // +0x108
    int            mPad10C;     // +0x10c
    int            mSubType;    // +0x110
};
struct RandomLCG
{
    unsigned RandomUint32Uniform(unsigned a, unsigned b = 0);
};
extern Vector3 g_starPos;                       // 0x01688890
extern RandomLCG g_random;                      // 0x01601760
void __cdecl FUN_00b9fa40();                    // 0x00b9fa40
struct cEmpireRef                           // object reachable through SimCtx+0xd4
{
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c();
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();
    virtual void* v1c();
    virtual void* v20();
    virtual void* v24();
    virtual void* v28();
    virtual void* v2c();
    virtual void* v30();
    virtual void* v34();
    virtual void* v38();
    virtual void* v3c();
    virtual void* v40();
    virtual void* v44();
    virtual void* v48();
    virtual unsigned GetEmpireID();         // slot 0x4c
};
struct SimCtx
{
    int         mPad0[15];   // +0x00
    void*       mp3C;        // +0x3c
    int         mPad40[38];  // +0x40
    cEmpireRef  mEmpire;     // +0xd4
    int         mPadD8[25];  // +0xd8
    int         mPlanetId;   // +0x13c
    void* getMgr();
    void* GetCivData(int which);   // 0x00c71030
    int   GetCityEconomy();        // 0x00c70e00
};
void* __cdecl EAAllocate(unsigned size, const char* file, int a, int b, int c, int d,
                         ...);                             // 0x00f473a0
struct cArithmeticaProgram
{
    int   mStorage[0x24];
    void  ctor();                              // 0x007f1e60
    void  Destroy();                           // 0x007f1d90
    void  ArithReset();                        // 0x007f2500
    void  SetVar(const char* name, float v);   // 0x007f25c0
    float GetVar(const char* name);            // 0x007f2590
};
bool __cdecl LoadArithmeticaFile(unsigned a, unsigned b, cArithmeticaProgram* p); // 0x007f2240
struct cTerrainInfo                           // object reached through planet model +0x24
{
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual float* GetTerrain();              // slot 0x0c
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();
    virtual void* v1c();
    virtual void* v20();
    virtual void* v24();
    virtual void* v28();
    virtual void* v2c();
    virtual void* v30();
    virtual void* v34();
    virtual void* v38();
    virtual void* v3c();
    virtual void* v40();
    virtual void* v44();
    virtual void* v48();
    virtual void* v4c();
    virtual void* v50();
    virtual void  ApplySurfaceDetail(void* placement, void* prop);   // slot 0x54
};
struct cPlanetModel
{
    int          mPad0[9];     // +0x00
    cTerrainInfo* mpTerrain;   // +0x24
    int          mPad28[15];   // +0x28
    int          mEmpireIndex; // +0x64
    float water_fraction();                                        // 0x00b7ec50
    bool  FindClosestWater(float* pos, float radius, void* out);   // 0x00b8bb70
    void  BuildSurfaceOrientation2(float* rotation, float* quat, float* scale); // 0x00b7f250
};
cPlanetModel* __cdecl SP_PlanetModel();              // 0x00b3d350
void*         __cdecl SP_NounManager();              // 0x00b3d300
void*         __cdecl SP_TerraformingManager();      // 0x00b3d430
void*         __cdecl SP_StarManager(unsigned id);   // 0x00b3d2a0
void*         __cdecl SP_PropertyManager();          // 0x0067de30
void*         __cdecl SP_LivingUniverse_GetPlayerEmpire();   // 0x01021300
struct GameData
{
    int       mPad0;
    StarRec** mpBegin;      // +0x04
    StarRec** mpEnd;        // +0x08
    int       mPadC;
    void*     mpExtra;      // +0x10
};
struct cGameNounManager
{
    GameData* GetGameDataVector(int a1, int a2, int a3, int a4, int a5);  // 0x00b21340
    void      RemoveNounsOfType(int type);                                // 0x00b22650
};
struct iRefCounted
{
    virtual void* v00();
    virtual void  Release();                   // slot 0x04
};
struct cEmpire
{
    int      GetHomePlanet();          // 0x00c31730
    bool     IsPlayerEmpire();         // 0x00c308b0
    unsigned GetColor(void* out);      // 0x00c32cd0
};
struct cStarManager
{
    cEmpire* GetEmpireByID(unsigned id);      // 0x00ba9370
};
struct cTerraformingManager
{
    int GetUnlockedCount(int flag);           // 0x00bbe470
};
struct cCity
{
    float* Self();                    // 0x00572590
    void   ctor();                    // 0x00ff1cb0
    void   SetID(unsigned id);        // 0x00ff0380
    void   SetSize(int size);         // 0x009879d0
    void   SetPosition(float* pos);   // 0x00ff0430
    void   SetStyle(unsigned style);  // 0x00bfc460
};
struct cCivData
{
    int      mPad0[15];        // +0x00
    cCity**  mpCitiesBegin;    // +0x3c
    cCity**  mpCitiesEnd;      // +0x40
    void     SetElementAlignment(unsigned style);      // 0x00fcc200
    cCity*   AddCity(cCity* city);                     // 0x00ff2c70
    void     EraseCity(int index);                     // 0x00ff1fb0
};
struct Matrix3
{
    float m[9];
    void Assign(const float* src);            // 0x0041cb40
};
struct cPropertyManager
{
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c();
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();
    virtual void* v1c();
    virtual void* v20();
    virtual void* v24();
    virtual void* v28();
    virtual bool  GetProperty(unsigned key, float def, void** out);   // slot 0x2c
};
void*    __cdecl FUN_00b6e3d0(unsigned color);          // 0x00b6e3d0
unsigned __cdecl FUN_00bef920(unsigned value);          // 0x00bef920
int      __cdecl FUN_00b93550(cCity* city, void* ctx);  // 0x00b93550
void     __cdecl FUN_0059c190(Matrix3* out, const float* quat);  // Matrix3FromQuaternion
extern float g_identityMatrix;   // 0x01688924  identity basis copied into the placement
struct SurfacePlacement
{
    unsigned short mFlags;        // +0x00
    unsigned short mStep;         // +0x02
    float          mPosition[3];  // +0x04
    float          mRadius;       // +0x10
    Matrix3        mRotation;     // +0x14
    float          mQuat[4];      // +0x38
    float          mScale[3];     // +0x48
};
// ---- items of slice s00b9f9b0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern Vector3 g_starPos;                       // 0x01688890
extern RandomLCG g_random;                      // 0x01601760

// ---- items of slice s00ba0770 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool         g_bFillRegions;    // 0x168888c
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
inline void* operator new(unsigned, void* p) throw() { return p; }
struct Vector3_s00ba_0770 { float x, y, z; };
struct Property {
    void*  mpData;      // +0x00 (value inline, or pointer when flags & 0x30)
    u32    pad04[3];
    u16    mnFlags;     // +0x10
    u16    mnType;      // +0x12
    bool* GetValueBool();   // 0x41e920

    void* Value() { return (mnFlags & 0x30) ? mpData : (void*)this; }
};
struct PropertyList {
    virtual int AddRef();
    virtual int Release();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
    virtual bool GetProperty(u32 id, Property*& out);   // 0x24
};
struct PropertyListPtr {
    PropertyList* mpObject;
    PropertyListPtr() : mpObject(0) {}
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    PropertyList** operator&() {
        if (mpObject) {
            PropertyList* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
    PropertyList* operator->() const { return mpObject; }
    operator PropertyList*() const { return mpObject; }
};
struct cPropertyManager_s00ba_0770 {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
    virtual void m10();
    virtual bool GetPropertyList(u32 instanceID, u32 groupID, PropertyList** dst);   // 0x2c
};
inline bool GetFloat(PropertyList* pl, u32 id, float& out) {
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->mnType == 0xd) {
        out = *(float*)p->Value();
        return true;
    }
    return false;
}
inline bool GetBool(PropertyList* pl, u32 id, bool& out) {
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->mnType == 1) {
        out = *(bool*)p->Value();
        return true;
    }
    return false;
}
struct ResourceKey { u32 instanceID, typeID, groupID; };
struct cPlacedObject { u32 pad0; Vector3_s00ba_0770 mPosition; u32 pad10[10]; };   // size 0x38
struct cPlanetObjects {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual int GetSeed();                                                  // 0x0c
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
    virtual int GetObjects(const ResourceKey** keys, const cPlacedObject** objects);   // 0xb4
};
struct cSpot {                 // size 0x34
    Vector3_s00ba_0770 mPosition;         // +0x00
    float   mRadius;           // +0x0c
    bool    mbClustered;       // +0x10
    u32     mContinent;        // +0x14
    u32     pad18[7];
};
struct cPlanetModel_s00ba_0770 {
    u32 pad00[9];
    cPlanetObjects* mpObjects;          // +0x24
    u32 GetContinent(const cSpot* spot);   // 0xb88590
};
struct cTerrainSphere_s00ba_0770 { int GetType(); };                  // 0xc75420
class cStarRecord_s00ba_0770;
struct NounVector {                                        // noun manager game-data view
    void* mpUnused;          // +0x00
    cStarRecord_s00ba_0770** mpBegin;   // +0x04
    cStarRecord_s00ba_0770** mpEnd;     // +0x08
};
struct cTerrainSphereOwner {
    cTerrainSphere_s00ba_0770* GetCurrentTerrainSphere();                              // 0xf67d90
    NounVector* GetGameDataVector(u32, u32, u32, u32, u32);                 // 0xb21340
};
struct cRecordEntry { u32 pad0; Vector3_s00ba_0770 mPosition; u32 pad10[6]; u8 mFlags; u8 pad29[3]; };   // 0x2c
template <class T> struct Vec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    u32 mAllocator;
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
};
struct cPlanetRecord_s00ba_0770 {
    u32 pad[0x134 / 4];
    Vec<cRecordEntry> mEntries;   // +0x134
};
struct Sphere { Vector3_s00ba_0770 mCenter; float mRadius; };
struct cSphereOwner { u32 pad[2]; Sphere mSphere; u32 rest[(0x19a8 - 0x18) / 4]; };   // 0x19a8
struct cSphereManager {
    u32 pad[0x1e5f0 / 4];
    Vec<cSphereOwner> mOwners;   // +0x1e5f0
};
namespace SP {
cPlanetModel_s00ba_0770* __cdecl PlanetModel();                       // 0xb3d350
}
namespace SP {
cPropertyManager_s00ba_0770* __cdecl PropertyManager();               // 0x67de30
}
namespace SP {
cTerrainSphereOwner* __cdecl TerrainSphereOwner();         // 0xb3d300
}
namespace SP {
cSphereManager* __cdecl SphereManager();                   // 0xb3d440
}
namespace SP {
namespace cSPLivingUniverse {
 cPlanetRecord_s00ba_0770* __cdecl GetActivePlanetRecord();   // 0x10212a0
}
}
inline bool IsValid(float f) {
    u32 u = *(u32*)&f;
    return (u & 0x7fffffff) == 0 || ((u - 0x800000) & 0x7f800000) < 0x7f000000;
}
template <class T> inline const T& max_(const T& a, const T& b) { return (a < b) ? b : a; }
cSpot* __cdecl CopySpots(cSpot* first, cSpot* last, cSpot* dest);   // 0xb97540 (eastl::copy)
struct SpotVector {
    cSpot* mpBegin;
    cSpot* mpEnd;
    cSpot* mpCapacity;
    void DestroyRange(cSpot* first, cSpot* last);   // 0xb970f0
    void push_back();                               // 0xba06f0
    cSpot& back() { return *(mpEnd - 1); }
    int size() const { return (int)(mpEnd - mpBegin); }
    cSpot* erase(cSpot* first, cSpot* last) {
        cSpot* const position = CopySpots(last, mpEnd, first);
        DestroyRange(position, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};
struct false_type {};
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char              mColor;
};
struct ContinentPair {
    u32 first;
    int second;
    ContinentPair(const u32& a, const int& b) : first(a), second(b) {}
};
struct rbtree_iterator {
    rbtree_node_base* mpNode;
    rbtree_iterator() : mpNode(0) {}
    rbtree_iterator(const rbtree_iterator& x) : mpNode(x.mpNode) {}
};
struct ContinentMap {
    u32 mCompare;
    rbtree_node_base mAnchor;
    u32 mnSize;
    void DoNukeSubtree(rbtree_node_base* pNode);                                // 0x9a9600
    rbtree_iterator DoInsertValue(const ContinentPair& value, false_type);       // 0xb96180
    void reset() {
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
    void clear() { DoNukeSubtree(mAnchor.mpNodeParent); reset(); }
    rbtree_iterator insert(const ContinentPair& value) { return DoInsertValue(value, false_type()); }
};
struct cRegion {               // size 0x18
    u8    mbDone;              // +0x00
    char  mFace;               // +0x01
    u16   pad02[3];
    short mEndX;               // +0x08
    u16   pad0a[7];
};
struct cCell { cRegion* mpRegion; u32 pad[2]; };   // size 0xc
struct GridCoord { int x, y, face; };
struct RegionVector {
    const cRegion** mpBegin;
    const cRegion** mpEnd;
    const cRegion** mpCapacity;
    void DoInsertValue(const cRegion** position, const cRegion* const& value);   // 0xb96600
    void push_back(const cRegion* const& value) {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) const cRegion*(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
struct cSpotGrid {
    u32 pad00[2];
    RegionVector mRegionList;   // +0x08
    u32 pad14[4];
    int mnSize;                 // +0x24
    u32 pad28[3];
    cCell* mpCells;             // +0x34
    u32 pad38[6];
    int mnRegions;              // +0x50
    cRegion* mpRegions;         // +0x54

    void Read(int seed, int count, float spacing);                        // 0xb9c630
    void AddSpot(const Vector3_s00ba_0770* pos, float radius, int kind);              // 0xb91320
    void AddRings(const Vector3_s00ba_0770* pos, float r0, float r1, float r2);       // 0xb90ea0
    bool StartRegion(int index, int face, int x, int y);                   // 0xb907f0
    void FillRegion(GridCoord* coord, cRegion* region);                    // 0xb91810
    void FinishRegions();                                                  // 0xb983b0

    cRegion* AllocRegion() {
        cRegion* region = &mpRegions[mnRegions++];
        region->mbDone = 0;
        return region;
    }
};
extern SpotVector   g_Spots;           // 0x16888ec
extern ContinentMap g_ContinentSpots;  // 0x156c040
extern cSpotGrid    g_SpotGrid;        // 0x156c060
static const float kEpsilon = 1.5258789e-05f;
extern const u32    kSpotPropertyIDs[5][3];   // 0x146598c
void __cdecl ResetSpotState();         // 0xb95500
struct ObjKey { u32 mLo; u32 mHi; };
struct ObjVec {
    cStarRecord_s00ba_0770** mpBegin;      // +0x00
    cStarRecord_s00ba_0770** mpEnd;        // +0x04
    cStarRecord_s00ba_0770** mpCapacity;   // +0x08
    void reserve(unsigned n);                                             // 0x00d01790
    void DoInsertPtr(cStarRecord_s00ba_0770** pos, cStarRecord_s00ba_0770* const& value);       // 0x00aea5d0
};
struct HashNode {
    u32        mUnk00;          // +0x00
    u32        mUnk04;          // +0x04
    ObjVec     mVec;            // +0x08
    u32        mUnk14[11];      // +0x14..+0x3f
    HashNode*  mpNext;          // +0x40
    u32        mUnk44;          // +0x44
};
struct SimObj_s00ba_0770 {
    u32         mUnk00;                 // +0x00
    HashNode**  mpBuckets;              // +0x04
    u32         mnBucketCount;          // +0x08
    u32         mnElementCount;         // +0x0c
    u32         mUnk10[3];              // +0x10..+0x1b
    HashNode*   mpFreeList;             // +0x1c
    u32         mUnk20;                 // +0x20
    char*       mpPoolBegin;            // +0x24
    char*       mpPoolEnd;              // +0x28
    u32         mPoolChunkSize;         // +0x2c
    HashNode**  mpInlineBuckets;        // +0x30
    u32         mInlineBuckets[0x48/4]; // +0x34..+0x7b
    u32         mPool[0x480/4];         // +0x7c..+0x4fb
    u32         mTail[0x80/4];          // +0x4fc..+0x57b

    SimObj_s00ba_0770* setup(void* a2, void* a3);                              // 0x00ba0570
    ObjVec* FindOrAdd(const ObjKey* key);                           // 0x00b9c180
    void DestroyNodes(HashNode** buckets, u32 bucketCount);         // 0x00b982e0
};
class cStarRecord_s00ba_0770 {
public:
    virtual void AddRef();          // slot 0
    virtual void Release();         // slot 1
    char         mPad04[0x104];     // +0x04..+0x107
    u32          mType;             // +0x108
    char         mPad10c[8];        // +0x10c..+0x113
    u32          mKey0;             // +0x114
    char         mPad118[4];        // +0x118..+0x11b
    int          mIndex;            // +0x11c
    char         mPad120[4];        // +0x120..+0x123
    u32          mKey1;             // +0x124
    char         mPad128[0x74];     // +0x128..+0x19b
    cStarRecord_s00ba_0770* mLink;             // +0x19c
    cStarRecord_s00ba_0770* mFirst;            // +0x1a0
};
void __cdecl IntroSelect(void* first, void* last, int depth, void* compare);   // 0x00e26410
void __cdecl InsertionSort(void* first, void* last, void* compare);            // 0x00bbe970
void __cdecl MergeSort(void* first, void* last, void* compare);                // 0x00b90a40
void __cdecl FreeBuckets(void* p);                                            // 0x00f47380
// ---- items of slice s00ba0770 end

// ---- items of slice s00ba2590 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_156c198;   // 0x156c198
extern int g_156c194;   // 0x156c194
void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int); // 0xf473a0
void  __cdecl operator_delete__(void*);                    // 0xf47380
void* __cdecl EA_Messaging_GetServer();                    // 0x883860
void  __cdecl EA_IO_WriteUint32(void*, void*, int, int);   // 0x93aa70
void  __cdecl EA_IO_ReadInt32(void*, void*, int, int);     // 0x93a780
struct RelCmp {
  int __thiscall Cmp(void* b);                             // 0xc0b8e0
};
struct RelFlagA {
  bool __thiscall Get();                                   // 0xc0b780
};
struct RelFlagB {
  bool __thiscall Get();                                   // 0xc0b7a0
};
void  __cdecl FUN_00ba2980(int, int);                      // 0xba2980 (partial 33e0 only)
struct VecHdr {
  int pad0; void* data; unsigned size; int fieldC;
  void __thiscall FreeInts(int* arr, unsigned n);          // 0xba2980
  __declspec(noinline) void FreeNodes(void* arr, unsigned n);   // 0xba2e00
};
struct PosseReload {
  void __thiscall Run();                                    // 0xba2af0
};
void* __cdecl FUN_00bc3e60(unsigned, int, int);            // 0xbc3e60
void  __cdecl FUN_00ac4440(void*, void*, void*);           // 0xac4440
struct cVarListSerializer { char storage[0xa14]; };
cVarListSerializer* __fastcall cVarListSerializer_ctor(cVarListSerializer* self, ...);
void __fastcall cVarListSerializer_Serialize(cVarListSerializer* self, ...);
struct SaveBlob {
  uint32_t magic;                 // +0x00
  cVarListSerializer ser;         // +0x04
};
struct CGZSub { void __thiscall Dtor(); };
struct CGZTimer { void __thiscall Dtor(); };
static inline void Release(void* p) { if (p) (*(void(__thiscall*)(void*))((*(void***)p)[1]))(p); }
struct W {
  void __thiscall Run_00ba2590(void* obj);
  void __thiscall Run_00ba2670(void* p);
  void __thiscall Run_00ba2750();
  void __thiscall Run_00ba2ca0(void* p2);
  char __thiscall Run_00ba2d80(void* p2);
  void __thiscall Run_00ba2f20();
  void* __thiscall Run_00ba2f90();
  void __thiscall Run_00ba3010();
  void* __thiscall Run_00ba30c0(void* out, uint32_t* key, int);
  void* __thiscall Run_00ba31d0(void* out, void* node, void** head);
  void __thiscall Run_00ba3310();
  void __thiscall Run_00ba3350();
  void* __thiscall Run_00ba3550(void* src);
  void* __thiscall Run_00ba3620(void* src);
  void __thiscall Run_00ba37a0();
};
struct RelCell { char pad00[0x4a8]; int f4a8; int f4ac; char pad4b0[0x18]; uint8_t f4c8; char pad4c9[3]; void* f4cc; void* f4d0; };
struct HashNode_s00ba_2590 { int key[8]; HashNode_s00ba_2590* next; };
struct HashPolicy {
  float f0; float f4; unsigned cap;
  void __thiscall CheckSize(void* out, unsigned mask, unsigned count, int grow);  // 0x00921440
};
struct HashSet {
  int pad0; HashNode_s00ba_2590** buckets; unsigned mask; int count;
  float f10; float f14; unsigned cap;
  void __thiscall Rehash(unsigned newmask);   // 0x00ba29d0
};
struct InsertRes { unsigned char flag; char pad[3]; unsigned size; };
// ---- items of slice s00ba2590 end

// ---- items of slice s00ba3860 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_vtbl_PPD1;   // 0x01465d64
extern void* g_vtbl_TimerA; // 0x01465d54
extern void* g_vtbl_TimerB; // 0x01464450
extern void* g_vtbl_GB1a;   // 0x013eb384
extern void* g_vtbl_GB1b;   // 0x01465dc8
extern void* g_vtbl_GB1c;   // 0x01465d78
extern void* g_vtbl_GB1d;   // 0x01465d70
typedef unsigned int  uint;
void* __cdecl SP_GetActivePlanet();                         // 0x00b3d240
void* __cdecl SP_GetCurrentGameMode();                      // 0x00b5b800
void* __cdecl SP_AchievementsController();                  // 0x00675250
void* __cdecl FUN_0067cb30();                               // 0x0067cb30
void* __cdecl FUN_00c0bc00();                               // 0x00c0bc00
void* __cdecl FUN_00c04590(void* o);                        // 0x00c04590
void  __cdecl FUN_00ba5e10(void* o, int v);                 // 0x00ba5e10
void* __cdecl FUN_00b21340(void* mgr, int, int, int, int, int); // 0x00b21340
void  __cdecl EA_ConvertToString16(void* out, const char* s, uint n); // 0x0093c5a0
char  __cdecl FUN_00ac8050(void* iface, int a, void* e);    // 0x00ac8050
void* __cdecl UninitCopy16(char* const* dstEnd, const void* src, const void* srcEnd, void* dst, void* tag); // 0x007f1890
void* __cdecl Copy8(char* const* dstEnd, const void* src, const void* srcEnd, void* dst, void* tag);        // 0x0076ffd0
char  g_1654c10;                                            // 0x01654c10
float g_f1485720 = 1.0f;                                    // 0x01485720
float g_f1470f1c = 2.0f;                                    // 0x01470f1c
void* g_154df28;                                            // 0x0154df28
wchar_t g_wEmpty[];                                         // 0x013f6254
struct CGZSub_s00ba_3860 { void __thiscall Ctor(); };                  // 0x00b5b960
void* __fastcall FUN_00c0c1a0(void* o);                     // 0x00c0c1a0
struct ContObj { void __thiscall AutoTest(uint, int); };    // 0x00676e90
struct ThingIn  { char pad[0xa4]; int f0a4; void __thiscall Set0x120(); }; // 0x00c6ad30
struct ThingIn2 { char pad[0x191]; u8 f191; void __thiscall Set(u8); };    // 0x00c6a070
struct PropObj  { void __thiscall UpdateProperty(uint, const void*); };    // 0x0060d860
struct AnimCtx  { int f00, f04, f08; };                     // built at +0xb28
struct GameData_s00ba_3860 { char pad[0xb20]; int f0b20; char pad2[4]; int f0b28, f0b2c, f0b30; };
struct HtNode {
    uint k0, k1, k2;                                        // +0x00
    char pad0c[0x14];
    HtNode* next;                                           // +0x20
};
struct HIter { HtNode* node; HtNode** bucket; u8 inserted; char pad[3]; };
struct Ht {
    char    pad00[4];
    HtNode** bucket;                                        // +0x04
    uint    bucketCount;                                    // +0x08
    uint    size;                                           // +0x0c
    char    pad10[0x10];

    void Find(HIter* it, const void* key);                  // 0x00ba3040
    void Insert(HIter* it, const void* val, uint tag);      // 0x00ba30c0
    void Insert2(HIter* it, const void* key, uint tag);     // 0x00ba3250
    void* GetOrAdd1(const void* key);                       // 0x00ba39f0
    void* GetOrAdd2(const void* key);                       // 0x00ba3a80
};
struct Eh {
    char     pad00[4];
    HtNode** bucket;                                        // +0x04
    uint     bucketCount;                                   // +0x08
    uint     size;                                          // +0x0c
    char     pad10[0x10];
    void Find(HIter* it, const void* key);                  // 0x00645ed0
    void Insert2(HIter* it, const void* key, uint tag);     // 0x00ba3250
    void* GetOrAdd2(const void* key);                       // 0x00ba3a80
};
struct VBlk8 {
    char* begin; char* end; char* cap; char pad0c[8]; u8 flag; char pad15[3];
    void* __thiscall Assign(VBlk8* src);                    // 0x00ba3620
    void* __thiscall Reserve(uint n, void* flags);          // 0x00ac20d0
};
struct WKey { uint k0, k1, k2; };
struct VBlk {
    char* begin; char* end; char* cap; char pad0c[8]; u8 flag; char pad15[3];
    void* __thiscall Assign(VBlk* src);                      // 0x00ba3550
    void* __thiscall Reserve(uint n, void* flags);           // 0x00ba2ec0
    __declspec(noinline) void* __thiscall InsertAt(char* pos, const WKey* key);   // 0x00ba43b0
    void* __thiscall FindOrAdd2(const WKey* key);            // 0x00ba4520
};
struct Vec16 { void* __thiscall InsertSorted(void* pos, void* val); };        // 0x00b97140
struct WString {
    wchar_t* begin; wchar_t* end; wchar_t* cap; int alloc;
    void __thiscall RangeInitialize(const wchar_t* s);      // 0x00579a90
    void __thiscall CopyFrom(const WString* src);           // 0x0056e2d0
};
struct PPD {
    void* vftbl;                                            // +0x00
    void* f04;                                              // +0x04
    VBlk  b0;                                               // +0x08
    VBlk  b1;                                               // +0x20
    VBlk  b2;                                               // +0x38
    VBlk  b3;                                               // +0x50
    VBlk8 b4;                                               // +0x68
    void* timerVtbl;                                        // +0x80
    void* f84;                                              // +0x84
    int   f88, f8c, f90, f94;                               // +0x88
    u8    f98; char pad99[3];                               // +0x98
    int   f9c;                                              // +0x9c
    u8    fa0, fa1, fa2; char padA3;                        // +0xa0

    PPD* CopyCtor(const PPD& src);                          // 0x00ba3ca0
    PPD* Assign(const PPD& src);                            // 0x00ba4430
};
struct Goal {
    char pad00[0x20];
    Ht map1;                                                // +0x20
    Eh map2;                                                // +0x40

    int  Field4(const void* key);                           // 0x00ba4270
    int  AddCount(const void* key, void* obj);              // 0x00ba4290
    void Clear0c(const void* key);                          // 0x00ba4330
    void Set10(const void* key, int v);                     // 0x00ba4350
    int  Field8(const void* key);                           // 0x00ba4370
    int  Field0c(const void* key);                          // 0x00ba4390
    int  Resolve(const void* key, void* a, void* b);        // 0x00ba3f90
};
static inline bool WKeyLess(const WKey* a, const WKey* b) {
    if (a->k0 != b->k0) return a->k0 < b->k0;
    if (a->k2 != b->k2) return a->k2 < b->k2;
    return a->k1 < b->k1;
}
__declspec(noinline) void* __cdecl LowerBound16(void* begin, void* end, const WKey* key, u8 flag); // 0x00ba2e50
// ---- items of slice s00ba3860 end

// ---- items of slice s00ba47b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char DAT_01654c10;
extern char DAT_01654c01;
extern char DAT_01654c02;
struct Vec4i { int a, b, c, d; };
struct MapNode {
    MapNode* next;                        // +0x00
    MapNode* prev;                        // +0x04
    char pad08[0xc];
    void* value;                          // +0x14
};
struct HashTable {
    char pad00[4];
    MapNode** buckets;                    // +0x04
    int bucketCount;                      // +0x08
    void Find(MapNode** out, uint* key);  // 0x00db4780
};
struct CursorProvider {
    char pad00[0xc];
    HashTable table;                      // +0x0c

    char* FindByField10(uint key, int match);
    char* FindFirst10(uint* key, int a, int b, int c);
    char* FindFirst24(uint* key, int a, int b, int c);
    char* FindByField24(uint key, int match);
    void UpdateEntry(uint key, int a, int b, int c, int d, int e, int f);
};
struct CModeObj {
    void Update(int* key);
    void Method(int a, uint b, void* c);
};
struct StateBlock {
    int* Get(int* key);                   // 0x00ba39f0
};
struct GoalVec {
    char* begin;                          // +0x00
    char* end;                            // +0x04
    char* cap;                            // +0x08
    char pad0c[8];
    bool  flags14;                        // +0x14

    void Insert(char* pos, char* src);
    int* Emplace(char* pos, char* src);
    char* FindOrAdd(uint* key);
};
struct Telemetry {
    void Reset(int);                      // 0x007ebb60
};
struct ResMgr { int* Get(); };
struct IntVector { void resize(uint); };
struct TimeMgr { unsigned __int64 Get(); };
struct CommRef { void* GetCommContext(); };
struct Obj94 { void* Get(); };
struct VecElem {
    void CopyFrom(void* src);             // 0x00ba3ca0
};
int __cdecl FUN_00b21340(...);                              // 0x00b21340 (thiscall, 5 args)
void __cdecl FUN_00b93c60(...);                             // 0x00b93c60
void __cdecl FUN_00829110(...);                             // 0x00829110
void __cdecl FUN_00f47380(void* p);                      // 0x00f47380  operator delete
int __cdecl SP_GetCurrentGameMode_s00ba_47b0();                     // 0x00b5b800
int __cdecl FUN_00ba3f90(int, int*, int);                // 0x00ba3f90
void* __cdecl FUN_00675250(uint, int);                   // 0x00675250
void* __cdecl FUN_00d37cb0();                            // 0x00d37cb0
void* __cdecl FUN_00cd3440();                            // 0x00cd3440
void* __cdecl FUN_0067de90(...);                         // 0x0067de90
void* __cdecl FUN_00ba2f90();                            // 0x00ba2f90
void __cdecl FUN_00ba2f20(void* self);                   // 0x00ba2f20
int __cdecl FUN_00c72540(void*, void*, void*, char);     // 0x00c72540
void __cdecl FUN_00ba3ca0(void*);                        // 0x00ba3ca0
void __cdecl FUN_00ba45a0(void*, void*, void*);          // 0x00ba45a0
void* __cdecl operator_new(int);                         // 0x00f473a0
void __cdecl FUN_00ba4430(void*);                        // 0x00ba4430
void* __cdecl FUN_00ba3ea0(void*, void*, void*);         // 0x00ba3ea0
void __cdecl FUN_00ba36f0(void*, void*, void*);          // 0x00ba36f0
void* __cdecl FUN_00ba4520(void*);                       // 0x00ba4520
void* __cdecl SP_GameTimeManager();                      // 0x00b3d380
void* __cdecl GetCommContext(void* self);                // 0x00ce6950
void __cdecl FUN_00b3d4c0(void*);                        // 0x00b3d4c0
void __cdecl FUN_00b3d4f0(void*);                        // 0x00b3d4f0
void __cdecl FUN_00e30d20(void*);                        // 0x00e30d20
void __cdecl FUN_00675370();                             // 0x00675370
char __cdecl FUN_00675e80(uint);                         // 0x00675e80
void __cdecl FUN_00675770();                             // 0x00675770
char __cdecl SetSpeciesAsScanned(void* planet);          // 0x00b3d520
void* __cdecl SP_GetTerrainSphere(void* mgr);            // 0x00c3b0f0
// ---- items of slice s00ba47b0 end

// ---- items of slice s00ba6750 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned char g_1689df8;                        // 0x1689df8 re-entry guard
extern float g_13eb1bc;                                // 0x13eb1bc -1.0f
extern float g_1459c40;                                // 0x1459c40 64
extern float g_156c638;                                // 0x156c638
extern unsigned char g_1654c05;                        // 0x1654c05 game-mode tag
void*    __cdecl FUN_005c65e0(void*);                  // 0x5c65e0 cCivData::GetCities
void*    __cdecl FUN_00b5b800();                       // 0xb5b800 GetCurrentGameMode
void*    __cdecl FUN_01021300();                       // 0x1021300 GetPlayerEmpire
void*    __cdecl FUN_00921580(void*);                  // 0x921580 RBTreeIncrement
bool     __cdecl FUN_0093aa70(void*, const void*, int, int); // 0x93aa70 WriteUint32
unsigned char __cdecl FUN_00692e00(void*);             // 0x692e00 WriteBlob32
unsigned char __cdecl FUN_00692e50(void*);             // 0x692e50 WriteBlob16
struct GameObj {
  int  AddRef();                    // 0x801920
  int  Kind();                      // 0xbb9ae0
  int  Q9c60();                     // 0xbb9c60
  int  Qa900();                     // 0xbba900
  int  Flag(int mask);              // 0xbb9af0
  void OnBan();                     // 0xbba2a0
  int  Pop(int a, int b);           // 0xbb9b00
  int  Kind2(int a);                // 0xbbaa60
  int  Match(void* arg);            // 0xbbaa80
};
struct Rng {
  double Next();        // 0x9360d0 RandomDoubleUniform
  unsigned NextU(unsigned n); // 0xa68fb0 RandomUint32Uniform
};
struct IStream {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
  virtual void* GetData();      // +0x1c
  virtual void* S20();          // +0x20
  virtual void* S18();          // +0x18
};
struct IWriter {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
  virtual void* S18();          // +0x18
};
struct StarSearchCriteria {
  int   m0;    // +0x00
  int   m4;    // +0x04
  int   m8;    // +0x08
  float mC;    // +0x0c
  float m10;   // +0x10
  float m14;   // +0x14
  int   m18;   // +0x18
  StarSearchCriteria();
};
struct BannerList {
  char pad000[0xc8];
  void* mC8;   // +0xc8 vector begin (stride 0x14)
  void* mCC;   // +0xcc vector end
  char padD0[0x14c - 0xd0];
  void* m14C;  // +0x14c
};
struct GMStub {
  void M50(int a, int b);   // 0xb5b800-dispatch: vt[3]
  void M80(int a, int b);   // empire-dispatch:    vt[4]
  static void* GetEmpire(); // 0x1021300
};
struct EmpireStub {
  void Prep();              // 0xc30c60, __thiscall
};
struct Vec50Obj {
  char pad000[0x50];
  int* m50;   // +0x50
  int* m54;   // +0x54
  void Erase(int value);
};
struct StarManagerCore {
  char pad000[0xc8];
  void* mC8;   // +0xc8
  void* mCC;   // +0xcc
};
// ---- items of slice s00ba6750 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
int FUN_00ba6b40(int* vec, int start, void* civ, float threshold);  // 0x00ba6b40 (stays in the slice: not this object's)

// ---- items of slice s00ba7720 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_01689c4c;
extern float DAT_01471064;
extern float DAT_0156c52c, DAT_0156c530, DAT_0156c534;
extern float DAT_0156c538, DAT_0156c53c, DAT_0156c540;
void* operator_new(uint size, const char* pName, int a, int b, int c, int d); // 0x00f473a0
struct RBNode;
RBNode* RBTreeIncrement(RBNode* p);                                           // 0x00921580
struct ElemC {
    float x;                    // +0x00
    float y;                    // +0x04
    uint  z;                    // +0x08
};
struct RefObj {
    virtual void AddRef();
    virtual void Release();
    char m[0x28 - 4];           // padding to +0x28
    int m28;                    // +0x28  key
};
struct Elem16 {
    float a, b, c;              // +0x00, +0x04, +0x08
    uint  d;                    // +0x0c
};
void RefPromoteHeap(RefObj** self, uint topPosition, uint position, RefObj* value); // 0x00ba6750
void ElemCPromoteHeapHelper(ElemC* first, uint topPosition, uint position, ElemC value,
                            bool (*compare)(const ElemC*, const ElemC*)); // 0x00ba6800
struct HashTableCtl {
    int   m00;      // +0x00
    int   m04;      // +0x04
    int   m08;      // +0x08
    char  m0c;      // +0x0c
    char  m0d;      // +0x0d
    char  m0e;      // +0x0e
    char  m0f;      // +0x0f
    int   m10;      // +0x10
    int   m14;      // +0x14
    int   m18;      // +0x18
    int   m1c;      // +0x1c
    int   m20;      // +0x20
    int   m24;      // +0x24
    int   m28;      // +0x28
    int   pad2c;    // +0x2c (untouched)
    int   pad30;    // +0x30 (untouched)
    int   m34;      // +0x34
    int   m38;      // +0x38
    int   m3c;      // +0x3c

    HashTableCtl* Reset();      // 0x00ba7bd0
};
void* EA_ResourceMan_GetManager();          // 0x0067dcd0
void* SP_IDGenerator();                     // 0x0067de60
void* SP_PropertyList_ctor(void* p);        // 0x006a1c40
void  SP_PropertyList_SetParent(void* self, void* parent); // 0x006a1710
void  FUN_006a3dd0(void* p);                // 0x006a3dd0
void  FUN_00b8dde0(void* out, int x);       // 0x00b8dde0
void* SP_StarManager();                     // 0x00b3d2a0
void  FUN_00c71910(void* p);                 // 0x00c71910
void  FUN_00c8b7d0(void* p);                 // 0x00c8b7d0
void  FUN_00c33580(void* p);                 // 0x00c33580
void* SP_NounManager_GetCurrentTerrainSphere(void* nm); // 0x00f67d90
void  FUN_00ba6cf0(void* self);              // 0x00ba6cf0
void  FUN_00bb9bb0(void* p, int x);          // 0x00bb9bb0
void  FUN_00bb9be0(void* p, int x);          // 0x00bb9be0
int   FUN_00801920(void* p);                 // 0x00801920
void  FUN_00c7a160(void* a, void* b);        // 0x00c7a160
void  FUN_00bb9b00(void* p, int x, int y);   // 0x00bb9b00
void* SP_cSPLivingUniverse_GetPlayerEmpire();// 0x01021300
void* FUN_00c30c60();                        // 0x00c30c60
extern uint g_0168964c;                      // compared against 0x21000f
struct TypeTagger {
    char pad0[0x14c];
    RefObj* mp14c;              // +0x14c
    char pad1[0x1dc - 0x150];
    RefObj* mp1dc;              // +0x1dc
    void SetIfType(void* typeTag);   // 0x00ba8160
};
struct LookupObj {
    void* Hash(void* k);        // 0x00bb9de0 (declared, not defined)
};
bool  FUN_006ab760(void* a, const wchar_t* b);// 0x006ab760
struct HashOwner {
    char pad0[0xc8];
    void** mp0c8;               // +0xc8
    void** mp0cc;               // +0xcc
    void* Lookup(void* key);    // 0x00ba81b0
};
struct TwoArrayOwner {
    char pad0[0x20];
    void* mp20;                 // +0x20
    char pad1[0x34 - 0x24];
    void* mp34;                 // +0x34
    void Free();                // 0x00ba8220
};
struct RandomLCG_s00ba_7720 { void* vtbl; };
double RandomDoubleUniform(RandomLCG_s00ba_7720* r);    // 0x009360d0
void*  FUN_0059aed0(void* a, void* b, void* c);// 0x0059aed0
extern RandomLCG_s00ba_7720 g_sMathRandom;              // 0x01601760
// ---- items of slice s00ba7720 end

// ---- items of slice s00ba8830 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t g_emptyWString[];    // 0x1667bac
extern uint32_t g_initA;            // 0x1689e0c
extern uint32_t g_initB;            // 0x1689e20
extern "C" int __cdecl atexit(void (__cdecl*)(void));
extern "C" void* __cdecl FUN_004010a0();                              // 0x4010a0
extern "C" void  __cdecl FUN_00ba61b0(uint32_t key, void** out);       // 0xba61b0
extern "C" void* __fastcall FUN_005ecf80(void* self, int, void* out, int hash);          // 0x5ecf80
extern "C" void  __fastcall FUN_00ba64a0(void* self, int, void* o, void* star, int x);   // 0xba64a0
extern "C" void  __fastcall FUN_00ba6310(void* self, int, void* o, int a, int b);         // 0xba6310
extern "C" int   __fastcall FUN_00989360(void* self, int);              // 0x989360
extern "C" void* __fastcall FUN_00ba8010(void* self, int, void* out, int x);              // 0xba8010
extern "C" void  __fastcall FUN_00b8dde0(void* self, int, void* x, int y); // 0xb8dde0
extern "C" void* __cdecl FUN_00f48a80();                               // 0xf48a80
extern "C" void* __fastcall FUN_00b8d8e0(void* self, int, void* out);  // 0xb8d8e0
extern "C" void* __cdecl FUN_00b3d3d0(void* o, int x);                 // 0xb3d3d0
extern "C" void  __fastcall FUN_0103ca40(void* self, int);             // 0x103ca40
extern "C" bool  __fastcall FUN_00bb9af0(void* self, int, int x);      // 0xbb9af0
extern "C" void  __fastcall FUN_00bb9b00(void* self, int, int a, int b); // 0xbb9b00
extern "C" void  __cdecl FUN_00b2af00(int* a, int* b);                 // 0xb2af00
extern "C" void  __cdecl FUN_00ba79a0(void* a, int b, int c, int d);   // 0xba79a0
extern "C" void  __cdecl FUN_00ba84b0(void* a, void* b, void* c);      // 0xba84b0
extern "C" void  __cdecl FUN_00ba8500(void* a, void* b, void* c);      // 0xba8500
extern "C" float __cdecl FUN_010431e0(void* props, int id);            // 0x10431e0
extern "C" void* __cdecl FUN_00ba8650(void* out, float angle);         // 0xba8650
extern "C" void* __fastcall FUN_00801920(void* self, int);             // 0x801920
extern "C" float __cdecl FUN_00c841a0(void* star);                     // 0xc841a0 (GetStarMass)
extern "C" float* __fastcall FUN_0041ea70(void* prop, int);            // 0x41ea70 (Property::GetFloat)
extern "C" void  __fastcall FUN_00fe8450(void* out, int);              // 0xfe8450
extern float g_RandomTurns;                     // 0x1689c4c
#pragma warning(disable: 4100)
#pragma intrinsic(sin, cos, sqrt)
struct RBNodeBase {
    RBNodeBase* mpNodeLeft;   // +0x00
    RBNodeBase* mpNodeRight;  // +0x04
    RBNodeBase* mpNodeParent; // +0x08
    uint8_t     mColor;       // +0x0c
    uint8_t     pad[3];
};
struct RBNode_s00ba_8830 {
    RBNode_s00ba_8830* mpNodeLeft;   // +0x00
    RBNode_s00ba_8830* mpNodeRight;  // +0x04
    RBNode_s00ba_8830* mpNodeParent; // +0x08
    uint8_t mColor;       // +0x0c
    uint8_t pad[3];
    uint32_t first;       // +0x10  (pair.first)
    void*    second;      // +0x14  (pair.second, first dword of value)
};
struct TreeIterator {
    RBNode_s00ba_8830* mpNode;
    TreeIterator(RBNode_s00ba_8830* p = 0) : mpNode(p) {}
    TreeIterator(const TreeIterator& o);
    RBNode_s00ba_8830* operator->() const { return mpNode; }
    bool operator!=(const TreeIterator& o) const { return mpNode != o.mpNode; }
};
struct UnsignedVoidMap {
    char mCompare[4];       // +0x00
    RBNodeBase mAnchor;     // +0x04
    uint32_t mnSize;        // +0x14
    char mAllocator;        // +0x18
    TreeIterator find(const uint32_t& key) const;       // out-of-line
    TreeIterator end() const { return TreeIterator((RBNode_s00ba_8830*)&mAnchor); }
};
struct cStarManager_s00ba_8830 {
    char pad_0000[0x150];
    UnsignedVoidMap mEmpires;  // +0x150
    char pad_016c[0x1a4 - 0x16c];
    void* mpProperties;        // +0x1a4  (property table)
    char pad_01a8[0x1d8 - 0x1a8];
    int mEmpireID;             // +0x1d8

    int   GetEmpireByID(unsigned int empireID);
    void* GetByFieldID();
    void  GenerateStarField(void* star);
    void  BuildPlanet(void* system, void* out, float p4, float p5, void* p6);
};
extern "C" void* __cdecl RBTreeIncrement_s00ba_8830(void* node);                  // 0x921580
struct WStr {
    wchar_t* mpBegin;     // +0x00
    wchar_t* mpEnd;       // +0x04
    wchar_t* mpCapacity;  // +0x08
    void Assign(const wchar_t* b, const wchar_t* e);   // 0x423650
};
extern WStr    g_WStrA;             // 0x1689dfc
extern WStr    g_WStrB;             // 0x1689e10
extern WStr    g_CachedName;        // 0x156c63c
struct StarSystem {
    char     pad_0000[0x70];
    uint32_t mnBaseKey;                       // +0x70
    char     pad_0074[0xac - 0x74];
    uint8_t  mnBodyIndex;                     // +0xac
};
struct StarBody {
    char     pad_0000[0x18];
    WStr     mName;                           // +0x18
    char     pad_0024[0x28 - 0x24];
    int      mnKind;                          // +0x28
    int      mnSubKind;                       // +0x2c
    char     pad_0030[0x4c - 0x30];
    uint8_t  mb4c;                            // +0x4c
    char     pad_004d[0xb0 - 0x4d];
    float    mfB0;                            // +0xb0
    float    mfB4;                            // +0xb4
    char     pad_00b8[0x130 - 0xb8];
    uint8_t  mb130;                           // +0x130
    char     pad_0131[0x194 - 0x131];
    int      mn194;                           // +0x194
};
typedef WStr* (__cdecl* GetWStrFn)(void*);
extern "C" int   __cdecl EA_IO_WriteUint32_s00ba_8830(void* w, void* p, int n, int x); // EA::IO::WriteUint32 (reloc)
namespace EA {
namespace Random {
class RandomLinearCongruential_s00ba_8830 {
public:
    double RandomDoubleUniform();   // 0x009360d0
};
}
}
namespace SP {
 extern EA::Random::RandomLinearCongruential_s00ba_8830 sMathRandom; 
}
struct VRandom { double RandomDoubleUniform(); };
extern VRandom sMathRandom;   // 0x16... _sMathRandom
static const float kAxisX[3] = { 1.0f, 0.0f, 0.0f };   // 0x156c52c
static const float kAxisZ[3] = { 0.0f, 0.0f, 1.0f };   // 0x156c538
static const float kfDegToRad = 0.017453292f;   // 0x1465eb0
static const float kfHalf = 0.5f;               // 0x1471064
static const float kfMaxInclination = 89.0f;    // 0x1466024
static const float kfWeightMax = 0.99f;         // 0x13ef480
static const float kfEpsilon = 1e-8f;           // 0x13ec4b8
static const float kfDensityDefault = 100.0f;   // 0x13ec4d0
static const float kfDensityGas = 10.0f;        // 0x1473c70
static const float kfVolumeScaleRocky = 0.001f; // 0x13f9428
static const float kfVolumeScaleStar = 1e-6f;   // 0x13f11c8
typedef void (__thiscall* VCall1)(void*);
static inline void RefRelease(void* o) { if (o) ((VCall1)(*(void***)o)[1])(o); }
static inline void StarBody_Release(void* o)
{
    (*(void (__thiscall**)(void*))((char*)*(void**)o + 4))(o);
}
static void* MakeStarBody(cStarManager_s00ba_8830* self, StarSystem* star, void* nameGen,
                          int kind, int subKind, int flag194, bool useCached)
{
    void* obj = 0;
    FUN_00ba61b0((uint32_t)star->mnBodyIndex * 0x1000000u + star->mnBaseKey, &obj);

    WStr  tmp = { 0, 0, 0 };
    WStr* name;
    bool  usedTemp = false;
    if (useCached && g_CachedName.mpBegin != g_CachedName.mpEnd) {
        name = &g_CachedName;
    } else {
        name = (WStr*)FUN_005ecf80(nameGen, 0, &tmp, 0x7e1310a);
        usedTemp = true;
    }

    StarBody* body = (StarBody*)obj;
    if (name != &body->mName)
        body->mName.Assign(name->mpBegin, name->mpEnd);
    if (usedTemp && (((char*)tmp.mpCapacity - (char*)tmp.mpBegin) & 0xfffffffe) > 2 &&
        tmp.mpBegin != 0)
        operator_delete(tmp.mpBegin);

    body->mnKind   = kind;      // +0x28
    body->mnSubKind = subKind;  // +0x2c
    body->mn194    = flag194;   // +0x194
    return obj;
}
struct PropertyObject {
    char     pad_0000[0x12];
    uint16_t mnType;   // +0x12  (0xd == float)
};
typedef bool (__thiscall* GetPropertyFn)(void* self, uint32_t id, void** out);
static float GetPropertyFloat(void* props, uint32_t id, float fallback)
{
    if (props != 0) {
        void* prop = 0;
        GetPropertyFn fn = (GetPropertyFn)(*(void***)props)[9];
        if (fn(props, id, &prop) && ((PropertyObject*)prop)->mnType == 0xd)
            return *FUN_0041ea70(prop, 0);
    }
    return fallback;
}
static __forceinline int CompareWStrRec(int* rec, int* value)
{
    const uint16_t* a = (const uint16_t*)rec[0];
    const uint16_t* b = (const uint16_t*)value[0];
    int alen = (rec[1] - rec[0]) >> 1;
    int blen = (value[1] - value[0]) >> 1;
    int n = alen <= blen ? alen : blen;
    for (; n != 0; --n, ++a, ++b) {
        if (*a != *b)
            return *a < *b ? -1 : 1;
    }
    if (alen < blen) return -1;
    if (alen > blen) return 1;
    return 0;
}
static inline int RecKey(int* rec) { return *(int*)((char*)rec + 0x28); }
// ---- items of slice s00ba8830 end

// ---- items of slice s00ba9810 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char gSimulatorName[];                                      // 0x013f09b4  "Simulator"
extern const char gAllocatorFile[];                                      // 0x013ebb38  EASTL/allocator.h
typedef unsigned short wchar_t16;
void* operator_new(uint32_t nSize, const char* pName, int a, int b, const char* pFile, int nLine); // 0x00f473a0
void operator_delete_array(void* pMem);                                  // 0x00f47380
void* OfflineAlloc(int nSize, const char* pName, int a, int b, int c, int d); // 0x00f473a0
extern const wchar_t16 gEmptyString16[];                                // 0x01667bac
extern uint8_t gbTypeCheckEnabled;                                       // 0x015d8b58
extern const wchar_t16 gTypeName[];                                      // 0x013f36bc  L"type"
extern const wchar_t16 gDbReadInitiated[];                               // 0x0145fc38  L"dbreadinitiated"
extern const wchar_t16 gDbReadCompleted[];                               // 0x0145fc18  L"dbreadcompleted"
extern const wchar_t16 gUnknownString[];                                 // 0x013f6254
struct cSortTriple {                                                    // 12-byte sort / run key
    float mX;                                                           // +0x00
    float mY;                                                           // +0x04
    uint32_t mZ;                                                        // +0x08 (third word copied as an integer)
};
struct cRunInfo {                                                       // 16-byte typesetter run
    float mX;                                                           // +0x00
    float mY;                                                           // +0x04
    float mZ;                                                           // +0x08
    uint32_t mExtra;                                                    // +0x0c
};
struct cIntVector {                                                     // eastl::vector<int>
    int* mpBegin;                                                       // +0x00
    int* mpEnd;                                                         // +0x04
    int* mpCapacityEnd;                                                 // +0x08
};
struct cIntVectorElement {                                              // 0x14-byte element
    cIntVector mVector;                                                 // +0x00
    uint32_t mExtra0;                                                   // +0x0c
    uint32_t mExtra1;                                                   // +0x10
};
struct cRbNodeBase {                                                    // eastl rbtree node header
    void* mpLeft;                                                       // +0x00
    void* mpRight;                                                      // +0x04
    void* mpParent;                                                     // +0x08
    uint32_t mnColor;                                                   // +0x0c
};
struct cFeedbackTree {                                                  // eastl::rbtree<uint32,...>
    void* mpAnchor;                                                     // +0x00
    cRbNodeBase mHead;                                                  // +0x04
    uint32_t mnSize;                                                    // +0x14
    void Find(void* pOut, uint32_t nKey);                               // 0x00e5c780
    int EraseKey(uint32_t nKey);                                        // 0x00baa110
};
struct cFeedbackNode {                                                  // tree node with value
    cRbNodeBase mBase;                                                  // +0x00
    uint32_t mnKey;                                                     // +0x10
    void* mpValue;                                                      // +0x14
};
void FUN_00ba8550(void* pBegin, void* pMiddle, void* pPred);            // 0x00ba8550
void FUN_00ba85c0(void* pBegin, void* pMiddle, void* pPred);            // 0x00ba85c0
void FUN_00ba7a80(void* pBegin, int a, int nCount, int b, cSortTriple value, void* pPred); // 0x00ba7a80
void FUN_00829110(void* pOut, const int* pFirst, const int* pLast, int* pDest,
                  const void* pSource);                                 // 0x00829110
void* RBTreeIncrement(void* pNode);                                     // 0x00921580
void RBTreeErase(void* pNode, void* pHead);                             // 0x00921880
bool FUN_00ac8050_s00ba_9810(void* pVisitor, int nFlags, void* pValue);            // 0x00ac8050
const cSortTriple* FUN_00bb9b80(void* pObject);                         // 0x00bb9b80
int FUN_00bb9ae0(void* pObject);                                        // 0x00bb9ae0
int GetAvatar(void* pNoun);                                             // 0x00b1fdb0
const cSortTriple* GetUFOKey(void* pEmpire);                            // 0x00c326b0
bool EmpireHasKey(void* pEmpire, const cSortTriple* pKey);              // 0x00c328c0
struct cWideString {
    wchar_t16* mpBegin;                                                 // +0x00
    wchar_t16* mpEnd;                                                   // +0x04
    wchar_t16* mpCapacityEnd;                                           // +0x08

    cWideString();                                                      // empty ctor
    cWideString(const cWideString& other);                              // 0x0056e2d0
    void RangeInitialize(const wchar_t16* pStr);                        // 0x00579a90
    void assign(const wchar_t16* pFirst, const wchar_t16* pLast);       // 0x00423650
};
void ParseCommandLine(cWideString* pOut, const char* pCommandLine);     // 0x00694bf0
cWideString* ConvertToString16(cWideString* pOut, const char* pText, int nLength);  // 0x0093c5a0
cWideString* ConvertToString16(cWideString* pOut, const cWideString* pText);        // 0x0093c6d0
cWideString* PathJoin(cWideString* pOut, const cWideString* pBase,
                      const wchar_t16* pName);                          // 0x0057cba0
bool FileExists(const wchar_t16* pPath);                                // 0x00931fa0
struct ISaveStream;
struct IGameSave {                                                      // save-area object
    virtual char v00(uint32_t nId);
    virtual char v04(uint32_t nId);
    virtual char v08(const wchar_t16* pTypeName, void* pArg);
    virtual char v0C(const wchar_t16* pName);
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual ISaveStream* v24();
    virtual const wchar_t16* v28();
};
IGameSave* GetSaveArea(uint32_t nId);                                   // 0x006b1f90
struct ISaveStream {                                                    // save-area reader
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual char v18(int a, int b, int c);
    virtual int  v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual int  v30(void* pDst, int nMax);
    virtual char v34(const char* pName, int a, int b, int c, void* pOut, int nUnused);
    virtual void v38();
    virtual void v3C(void* pArg);
};
struct IPackedDatabase {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual char v18(int a, int b, int c);
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30(void* pDst, int nMax);
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50(void* pStream);
    virtual void v54();
};
struct cMemoryStream {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28(int a, int b);
    void SetData(const void* pData, int nSize);                          // 0x0093b8e0
};
cMemoryStream* ConstructMemoryStream(uint32_t nSize);                    // 0x0093ba40
IPackedDatabase* ConstructDatabasePackedFile(int a, int b);              // 0x008d9f80
struct IResourceKeyVisitor {
    virtual void v00(const wchar_t16* pName);
    virtual void v04(const wchar_t16* pName);
};
struct cStarPickState {
    uint8_t mPad000[0xf0];                                              // +0x000
    void** mpObjects;                                                   // +0x0f0
    void** mpObjectsEnd;                                                // +0x0f4
    uint8_t mPad0F8[0x150 - 0xf8];                                      // +0x0f8
    cFeedbackTree mEmpiresByKey;                                        // +0x150
    bool HasKey(const cSortTriple* pKey);                               // 0x00ba9f80
};
__forceinline void FreeWideString(cWideString& str)
{
    if ((int)((((uint32_t)str.mpCapacityEnd - (uint32_t)str.mpBegin) & 0xfffffffeu)) > 2 &&
        str.mpBegin) {
        operator_delete_array(str.mpBegin);
    }
}
void* FUN_00ba7920(void* pFirst, const void* pMiddle, void* pDest);      // 0x00ba7920
void FUN_00edba80(void* pDest, const void* pFirst, const void* pLast);  // 0x00edba80
struct cRunInfoVector {
    cRunInfo* mpBegin;                                                  // +0x00
    cRunInfo* mpEnd;                                                    // +0x04
    cRunInfo* mpCapacityEnd;                                            // +0x08
    void Insert(cRunInfo* pPosition, const cRunInfo* pValue);           // 0x00baa410
};
void* FUN_00ba7960(void* pFirst, const void* pMiddle, void* pDest);      // 0x00ba7960
struct cTripleVector {
    cSortTriple* mpBegin;                                               // +0x00
    cSortTriple* mpEnd;                                                 // +0x04
    cSortTriple* mpCapacityEnd;                                         // +0x08
    void Insert(cSortTriple* pPosition, const cSortTriple* pValue);     // 0x00baa530
};
// ---- items of slice s00ba9810 end

// @ 0x00ba0080
void FUN_00ba0080(SimCtx* ctx)
{
    if (SP_NounManager() == 0)
        return;
    cPlanetModel* planet = SP_PlanetModel();
    if (planet == 0)
        return;

    cArithmeticaProgram arith;
    arith.ctor();
    LoadArithmeticaFile(0x9dd95c4, 0x24a4f5a, &arith);
    arith.ArithReset();

    unsigned empireID = ctx->mEmpire.GetEmpireID();
    cEmpire* empire = ((cStarManager*)SP_StarManager(empireID))->GetEmpireByID(empireID);
    if (empire == 0)
    {
        arith.Destroy();
        return;
    }

    bool isHomePlanet = empire->GetHomePlanet() == ctx->mPlanetId;

    cTerraformingManager* terra = (cTerraformingManager*)SP_TerraformingManager();
    cCivData* civ = (cCivData*)ctx->GetCivData(0);
    int numCities = (int)(civ->mpCitiesEnd - civ->mpCitiesBegin);
    int budget = numCities;
    if (!isHomePlanet)
    {
        int unlocked = terra->GetUnlockedCount(0);
        budget = unlocked < numCities ? unlocked : numCities;
    }

    unsigned style;
    if (empire == (cEmpire*)SP_LivingUniverse_GetPlayerEmpire() || !empire->IsPlayerEmpire())
    {
        unsigned rgb;
        style = (unsigned)FUN_00b6e3d0(empire->GetColor(&rgb));
    }
    else
        style = 0x53dbcf9;
    civ->SetElementAlignment(style);

    FUN_00b9fa40();

    cGameNounManager* nouns = (cGameNounManager*)SP_NounManager();
    GameData* game = nouns->GetGameDataVector(0xcd7d10, 0xd3d420, 0xace070,
                                             0xb1e500, 0x36be27e);
    StarRec** pp = game->mpBegin;
    int i = 0;
    while (pp != game->mpEnd)
    {
        if (i >= budget)
            break;
        StarRec* star = *pp;
        if (star->mType == (int)0xd18d25cd)
        {
            cCity* city = civ->mpCitiesBegin[i];
            i++;
            int size = FUN_00b93550(city, ctx);
            if (size != 0)
            {
                city->SetSize(size);
                city->SetPosition(star->mpShape->GetPosition());
                int economy = ctx->GetCityEconomy();
                unsigned s = (economy == 5) ? 0 : g_random.RandomUint32Uniform(3);
                city->SetStyle(FUN_00bef920(s));
            }
        }
        ++pp;
    }

    nouns->RemoveNounsOfType(0x36be27e);

    i = 0;
    while (i < (int)(civ->mpCitiesEnd - civ->mpCitiesBegin))
    {
        float* pos = civ->mpCitiesBegin[i]->Self();
        if (pos[0] == g_starPos.x && pos[1] == g_starPos.y && pos[2] == g_starPos.z)
            civ->EraseCity(i);
        else
            i++;
    }

    // No city survived on this planet: seed one at the surface directly below the star.
    if (civ->mpCitiesEnd == civ->mpCitiesBegin)
    {
        float* terrain = planet->mpTerrain->GetTerrain();
        float height = terrain[0x3c] * terrain[0x38] + terrain[0x34];

        SurfacePlacement place;
        place.mFlags = 0;
        place.mStep = 0;
        place.mPosition[0] = g_starPos.x;
        place.mPosition[1] = g_starPos.y;
        place.mPosition[2] = g_starPos.z;
        place.mRadius = 1.0f;
        place.mRotation.Assign(&g_identityMatrix);
        place.mFlags |= 4;
        place.mPosition[0] = 0.0f;
        place.mPosition[1] = height + 10.0f;
        place.mPosition[2] = 0.0f;

        float unit[3];
        unit[0] = unit[1] = unit[2] = 1.0f;
        place.mScale[0] = 0.0f;
        place.mScale[1] = 600.0f;
        place.mScale[2] = 0.0f;
        place.mStep++;
        planet->BuildSurfaceOrientation2(place.mRotation.m, place.mQuat, unit);

        Matrix3 basis;
        FUN_0059c190(&basis, place.mQuat);
        place.mRotation = basis;
        place.mFlags |= 2;
        place.mStep++;

        void* prop = 0;
        cPropertyManager* props = (cPropertyManager*)SP_PropertyManager();
        if (prop != 0)
        {
            void* dead = prop;
            prop = 0;
            ((iRefCounted*)dead)->Release();
        }
        if (props->GetProperty(0xbb1951ef, 4.0782470703125f, &prop))
            planet->mpTerrain->ApplySurfaceDetail(&place, prop);

        cCity* city = (cCity*)EAAllocate(0xc4, "Simulator/cCityData", 0, 0, 0, 0);
        if (city != 0)
            city->ctor();
        civ->AddCity(city);
        city->SetID(0xfd701f6f);
        city->SetSize(2);
        float pos[3];
        pos[0] = 0.0f;
        pos[1] = 600.0f;
        pos[2] = 0.0f;
        city->SetPosition(pos);
        city->SetStyle(FUN_00bef920(g_random.RandomUint32Uniform(3)));
        if (prop != 0)
            ((iRefCounted*)prop)->Release();
    }

    arith.Destroy();
}

// @ 0x00ba0570
SimObj* SimObj::setup(void* a2, void* a3)
{
    {
        FixedPool pool;
        pool.mHead = 0;
        pool.init((char*)this + 0x7c, 0x480, 0x48, 8, 0);
        pool.mpBegin = (char*)this + 0x7c;
        pool.mpEnd = (char*)this + 0x4fc;
        pool.mElemSize = 0x48;
        pool.mpOwner = (char*)this + 0x34;
        void* p = FUN_00921340(0x11);
        ((Call7*)this)->f(p, a2, &a3, &a3, a3, &a3, &pool);
    }
    Vec2 v;
    v.x = g_flt10000;
    v.y = g_flt2;
    mVec10 = v;
    int zero = 0;
    m18 = zero;
    unsigned n;
    {
        PoolProbe probe;
        n = probe.grow(*(float*)&mpEndC);
    }
    if (mMax8 < n)
        ((Call1*)this)->f((void*)n);
    return this;
}

// @ 0x00ba0640
void ElemVec18::push_back_uninitialised()
{
    char* p = mpEnd;
    if ((unsigned)p < (unsigned)mpCap)
    {
        mpEnd = p + 0x18;
        if (p != 0)
        {
            ((int*)p)[1] = 0;
            ((int*)p)[2] = 0;
            ((int*)p)[3] = 0;
            return;
        }
    }
    else
    {
        GrowTemp tmp;
        tmp.mpPtr = 0;
        tmp.mPad1 = 0;
        tmp.mPad2 = 0;
        ((Call2*)this)->f(p, &tmp);
        if (tmp.mpPtr != 0 && *(int*)((char*)tmp.mpPtr - 4) != 0)
            operator_delete(tmp.mpPtr);
    }
}

// @ 0x00ba06a0
void ElemVec18::clear()
{
    char* b = mpBegin;
    char* e = mpEnd;
    void* r = FUN_00b974c0(e, e, b);
    ((Call2*)this)->f(r, mpEnd);
    mpEnd -= (e - b) / 0x18 * 0x18;
}

// @ 0x00ba06f0
void ElemVec34::push_back_uninitialised()
{
    Elem34* p = (Elem34*)mpEnd;
    if ((unsigned)p < (unsigned)mpCap)
    {
        mpEnd = (char*)p + 0x34;
        if (p != 0)
        {
            p->InitTree();
            return;
        }
    }
    else
    {
        Elem34 tmp;
        tmp.InitTree();
        ((Call2*)this)->f(p, &tmp);
        ((Call1*)((char*)&tmp + 0x18))->f(tmp.mpCap);
    }
}

// @ 0x00ba0770
void __cdecl SetupPlanetSpots(u32 planetType, bool bFillRegions)
{
    ResetSpotState();
    g_Spots.clear();
    g_ContinentSpots.clear();

    cPlanetModel_s00ba_0770* planet = SP::PlanetModel();
    if (planet) {
        cPropertyManager_s00ba_0770* propManager = SP::PropertyManager();
        const ResourceKey* keys = 0;
        const cPlacedObject* objects = 0;
        cPlanetObjects* planetObjects = planet->mpObjects;
        int seed = planetObjects->GetSeed();
        int count = planetObjects->GetObjects(&keys, &objects);
        int numClustered = 0;
        for (int i = 0; i < count; i++) {
            PropertyListPtr propList;
            if (propManager->GetPropertyList(keys[i].instanceID, keys[i].groupID, &propList)) {
                float radius0 = 0.0f;
                bool has0 = GetFloat(propList, 0x254cf89, radius0);
                float radius1 = 0.0f;
                bool has1 = GetFloat(propList, 0x4ee9f45, radius1);
                if (!has0 && !has1)
                    continue;
                bool bClustered = false;
                Property* prop;
                if (propList && propList->GetProperty(0x3f6d22a, prop) && prop->mnType == 1)
                    bClustered = *prop->GetValueBool();
                const float& radius = max_(radius0, radius1);
                g_Spots.push_back();
                cSpot& spot = g_Spots.back();
                spot.mPosition = objects[i].mPosition;
                spot.mRadius = radius;
                spot.mbClustered = bClustered;
                spot.mContinent = planet->GetContinent(&spot);
                if (bClustered) {
                    g_ContinentSpots.insert(ContinentPair(spot.mContinent, numClustered++));
                }
            }
        }

        float spacing = 32.0f;
        float ringA0 = 0.0f;
        float ringA1 = 0.0f;
        float ringA2 = 0.0f;
        float minRadius = 56.0f;
        bool bSphereRings = false;
        float ringB0 = 0.0f;
        float ringB1 = 0.0f;
        float ringB2 = 0.0f;
        g_bFillRegions = bFillRegions;

        u32 tuningID;
        if (planetType >= 0x1654c01 && planetType <= 0x1654c05)
            tuningID = kSpotPropertyIDs[planetType - 0x1654c01]
                [SP::TerrainSphereOwner()->GetCurrentTerrainSphere()->GetType()];
        else
            tuningID = 0;

        PropertyListPtr tuning;
        cPropertyManager_s00ba_0770* pm = SP::PropertyManager();
        switch (planetType) {
        case 0x1654c01:
            pm->GetPropertyList(tuningID, 0x302a1c9, &tuning);
            break;
        case 0x1654c02:
            ringA0 = 16.0f;
            ringA1 = 32.0f;
            ringA2 = 96.0f;
            bSphereRings = true;
            ringB1 = 16.0f;
            pm->GetPropertyList(tuningID, 0x302a1c9, &tuning);
            break;
        case 0x1654c04:
        case 0x1654c05:
            ringA0 = 16.0f;
            ringA1 = 32.0f;
            ringA2 = 96.0f;
            pm->GetPropertyList(tuningID, 0x302a1c9, &tuning);
            spacing = 90.0f;
            break;
        }

        GetFloat(tuning, 0xb0111ed1, ringA0);
        GetFloat(tuning, 0x87ddd867, ringA1);
        GetFloat(tuning, 0x2f508b9, ringA2);
        GetFloat(tuning, 0x231eb8cd, minRadius);
        GetBool(tuning, 0x4cfe50d0, bSphereRings);
        GetFloat(tuning, 0xa63177bd, ringB0);
        GetFloat(tuning, 0xea319a1b, ringB1);
        GetFloat(tuning, 0x15d94435, ringB2);
        GetFloat(tuning, 0xfbc81b2, spacing);

        g_SpotGrid.Read(seed, 0x80, spacing);

        int numSpots = g_Spots.size();
        for (int i = 0; i < numSpots; i++) {
            cSpot& spot = g_Spots.mpBegin[i];
            float radius = spot.mRadius;
            if (spot.mbClustered)
                radius = max_(spot.mRadius, minRadius);
            g_SpotGrid.AddSpot(&spot.mPosition, radius, 4);
            if (ringA0 > kEpsilon || ringA1 > kEpsilon || ringA2 > kEpsilon)
                g_SpotGrid.AddRings(&spot.mPosition,
                                    ringA0 > kEpsilon ? radius + ringA0 : 0.0f,
                                    ringA1 > kEpsilon ? radius + ringA1 : 0.0f,
                                    ringA2 > kEpsilon ? radius + ringA2 : 0.0f);
        }

        cPlanetRecord_s00ba_0770* record = SP::cSPLivingUniverse::GetActivePlanetRecord();
        Vec<cRecordEntry>& entries = record->mEntries;
        for (cRecordEntry* it = entries.begin(), *end = entries.end(); it != end; ++it) {
            if (it->mFlags & 0x80)
                g_SpotGrid.AddSpot(&it->mPosition, minRadius, 4);
        }

        if (bSphereRings && (ringB0 > kEpsilon || ringB1 > kEpsilon || ringB2 > kEpsilon)) {
            cSphereManager* spheres = SP::SphereManager();
            Vec<cSphereOwner>& owners = spheres->mOwners;
            for (cSphereOwner* it = owners.begin(), *end = owners.end(); it != end; ++it) {
                Sphere& s = it->mSphere;
                if (IsValid(s.mCenter.x) && IsValid(s.mCenter.y) && IsValid(s.mCenter.z) &&
                    IsValid(s.mRadius)) {
                    float r = s.mRadius;
                    g_SpotGrid.AddRings(&s.mCenter,
                                        ringB0 > kEpsilon ? r + ringB0 : 0.0f,
                                        ringB1 > kEpsilon ? r + ringB1 : 0.0f,
                                        ringB2 > kEpsilon ? r + ringB2 : 0.0f);
                }
            }
        }

        if (g_bFillRegions) {
            GridCoord coord;
            for (int face = 0; face < 6; face++) {
                coord.face = face;
                for (int y = 0; y < 0x80; y++) {
                    coord.y = y;
                    for (int x = 0; x < 0x80; ) {
                        int index = (face * g_SpotGrid.mnSize + y) * g_SpotGrid.mnSize + x;
                        cRegion* region = g_SpotGrid.mpCells[index].mpRegion;
                        coord.x = x;
                        x++;
                        if (!region) {
                            if (!g_SpotGrid.StartRegion(index, face, x, y))
                                continue;
                            do {
                                cRegion* newRegion = g_SpotGrid.AllocRegion();
                                g_SpotGrid.mRegionList.push_back(newRegion);
                                newRegion->mbDone = 0;
                                region = newRegion;
                                g_SpotGrid.FillRegion(&coord, region);
                            } while (!g_SpotGrid.mpCells[index].mpRegion);
                        }
                        if (face == region->mFace)
                            x = region->mEndX + 1;
                    }
                }
            }
            g_SpotGrid.FinishRegions();
        }
    }
}

// @ 0x00ba1280
void FUN_00ba1280()
{
    SimObj_s00ba_0770 sim;
    u8 flag = 0;
    sim.setup(&flag, &flag);

    cTerrainSphereOwner* manager = SP::TerrainSphereOwner();
    NounVector* nouns = manager->GetGameDataVector(0xcd7d10, 0xd3d420, 0xace070,
                                                   0xb1e500, 0x36be27e);
    for (cStarRecord_s00ba_0770** it = nouns->mpBegin; it != nouns->mpEnd; ++it)
    {
        cStarRecord_s00ba_0770* obj = *it;
        if (obj->mType != 0xc012ae1f)
            continue;

        ObjKey key;
        key.mLo = obj->mKey0;
        key.mHi = obj->mKey1;
        ObjVec* vec = sim.FindOrAdd(&key);

        int count = (int)(vec->mpEnd - vec->mpBegin);
        int hint = count;
        if (count < obj->mIndex)
            hint = obj->mIndex;
        vec->reserve((unsigned)hint);

        cStarRecord_s00ba_0770* local = obj;
        obj->AddRef();
        cStarRecord_s00ba_0770** pos = vec->mpEnd;
        if (pos < vec->mpCapacity)
        {
            vec->mpEnd = pos + 1;
            if (pos)
            {
                *pos = obj;
                obj->AddRef();
            }
        }
        else
        {
            vec->DoInsertPtr(pos, local);
            obj = local;
        }
        if (obj)
            obj->Release();
    }

    HashNode** bucket = sim.mpBuckets;
    HashNode* node = *bucket;
    if (!node)
    {
        do
        {
            ++bucket;
        } while (!*bucket);
        node = *bucket;
    }
    HashNode* endNode = sim.mpBuckets[sim.mnBucketCount];

    while (node != endNode)
    {
        cStarRecord_s00ba_0770** begin = node->mVec.mpBegin;
        cStarRecord_s00ba_0770** last = node->mVec.mpEnd;
        if (begin != last)
        {
            int count = (int)(last - begin);
            int depth = 0;
            for (int v = count; v != 0; v >>= 1)
                ++depth;
            IntroSelect(begin, last, depth * 2 - 2, (void*)0xb908a0);
            if (count <= 0x1c)
            {
                InsertionSort(begin, last, (void*)0xb908a0);
            }
            else
            {
                cStarRecord_s00ba_0770** mid = begin + 0x1c;
                InsertionSort(begin, mid, (void*)0xb908a0);
                MergeSort(mid, last, (void*)0xb908a0);
            }
        }

        cStarRecord_s00ba_0770** p = node->mVec.mpBegin;
        cStarRecord_s00ba_0770** vecEnd = node->mVec.mpEnd;
        cStarRecord_s00ba_0770* prev = 0;
        cStarRecord_s00ba_0770* first = 0;
        int index = 0;
        if (p != vecEnd)
        {
            do
            {
                cStarRecord_s00ba_0770* cur = *p;
                cur->mIndex = index;
                if (prev)
                {
                    cStarRecord_s00ba_0770* old = prev->mLink;
                    if (cur != old)
                    {
                        cur->AddRef();
                        prev->mLink = cur;
                        if (old)
                            old->Release();
                    }
                }
                if (index == 0)
                    first = cur;
                cStarRecord_s00ba_0770* oldFirst = cur->mFirst;
                if (first != oldFirst)
                {
                    if (first)
                        first->AddRef();
                    cur->mFirst = first;
                    if (oldFirst)
                        oldFirst->Release();
                }
                cStarRecord_s00ba_0770* oldLink = cur->mLink;
                if (oldLink)
                {
                    cur->mLink = 0;
                    oldLink->Release();
                }
                ++index;
                ++p;
                prev = cur;
            } while (p != vecEnd);
        }

        node = node->mpNext;
        while (!node)
        {
            ++bucket;
            node = *bucket;
        }
    }

    sim.DestroyNodes(sim.mpBuckets, sim.mnBucketCount);
    sim.mnElementCount = 0;
    if (sim.mnBucketCount > 1 && (void*)sim.mpBuckets != (void*)sim.mpInlineBuckets)
    {
        if ((char*)sim.mpBuckets >= sim.mpPoolBegin && (char*)sim.mpBuckets < sim.mpPoolEnd)
        {
            *sim.mpBuckets = sim.mpFreeList;
            sim.mpFreeList = (HashNode*)sim.mpBuckets;
        }
        else
        {
            FreeBuckets(sim.mpBuckets);
        }
    }
}

// @ 0x00ba2590
void __thiscall W::Run_00ba2590(void* obj)
{
  void* self = this;
  if (obj) (*(void(__thiscall*)(void*))((*(void***)obj)[1]))(obj);
  void* node = operator_new(0xc, "Simulator", 0, 0,
     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  void* head = (char*)self + 0x34;
  *(void**)((char*)node + 8) = obj;
  if (obj) (*(void(__thiscall*)(void*))((*(void***)obj)[1]))(obj);
  *(void**)node = head;
  *(void**)((char*)node + 4) = *(void**)((char*)head + 4);
  **(void***)((char*)head + 4) = node;
  *(void**)((char*)head + 4) = node;
  if (obj) (*(void(__thiscall*)(void*))((*(void***)obj)[2]))(obj);
  *(uint8_t*)((char*)obj + 0xe) = 1;
}

// @ 0x00ba2670
void __thiscall W::Run_00ba2670(void* p)
{
  SaveBlob blob;
  blob.magic = 0xf2dcc8bc;
  void* io = (*(void*(__thiscall*)(void*))((*(void***)p)[0x20 / 4]))(p);
  void* wr = (*(void*(__thiscall*)(void*))((*(void***)io)[0x18 / 4]))(io);
  EA_IO_WriteUint32(wr, &blob.magic, 1, 0);
  cVarListSerializer_ctor(&blob.ser, (char*)this - 4, 0x156c370, 0x1a80d26);
  cVarListSerializer_Serialize(&blob.ser, p);
}

// @ 0x00ba2750
void __thiscall W::Run_00ba2750()
{
  void* srv = EA_Messaging_GetServer();
  (*(void(__thiscall*)(void*, void*, int, int))((*(void***)srv)[0x2c / 4]))(srv, (char*)this - 4, 0xf62def, 0xffffd8f1);
}

// @ 0x00ba27b0
int __stdcall FUN_00ba27b0(void* a, void* b)
{
  int s = ((RelCmp*)a)->Cmp(b);
  int v;
  if (s < g_156c198) v = (s >= g_156c194) ? 1 : 0;
  else v = 2;
  if (*(int*)((char*)a + 0xb20) == *(int*)((char*)b + 0xb20)) return 6;
  if (((RelFlagA*)a)->Get() && v >= 1) return 2;
  if (((RelFlagA*)b)->Get()) {
    if (((RelFlagA*)a)->Get() && v < 1) return 1;
    if (((RelFlagB*)a)->Get() && v < 2) return 1;
  }
  if (((RelFlagA*)a)->Get() && ((RelFlagB*)b)->Get() && v < 1) return 3;
  if (((RelFlagB*)a)->Get() && ((RelFlagA*)b)->Get() && v > 1) return 3;
  return 4;
}

// @ 0x00ba28a0
int __cdecl FUN_00ba28a0(void* mgr, int idx, void* other)
{
  if (mgr == 0) return 0;
  RelCell* c = (RelCell*)((char*)*(void**)((char*)mgr + 0x70) + idx * 0x4e0);
  int state = c->f4a8;
  if (other != 0 && ((*(uint32_t*)((char*)other + 0xb58) >> 8) & 1)) state = 2;
  switch (state) {
    case 1:
      if (c->f4c8 == 0) return ((unsigned)(c->f4ac - 1) <= 1u) ? 3 : 5;
      {
        int n = (int)(((char*)c->f4d0 - (char*)c->f4cc) >> 5);
        int32_t* p = (int32_t*)((char*)c->f4cc + 0xc);
        for (int i = 0; i < n; ++i) { if (*p == 0xb) return 3; p += 8; }
        return 5;
      }
    case 2: return (c->f4ac != 3 || c->f4c8 != 0) ? 6 : 5;
    case 3: case 4: case 5: return 5;
    default: return 0;
  }
}

// @ 0x00ba2a80
void* __stdcall FUN_00ba2a80(void** src)
{
  void* n = operator_new(0xc, "Simulator", 0, 0,
     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  if (n) {
    void* o = *src;
    *(void**)n = o;
    if (o) (*(void(__thiscall*)(void*))((*(void***)o)[0]))(o);
    *(void**)((char*)n + 4) = src[1];
  }
  *(void**)((char*)n + 8) = 0;
  return n;
}

// @ 0x00ba3010
void __thiscall W::Run_00ba3010()
{
  ((PosseReload*)((char*)this - 4))->Run();
  void* srv = EA_Messaging_GetServer();
  (*(void(__thiscall*)(void*, void*, int))((*(void***)srv)[0x20 / 4]))(srv, (char*)this - 4, 0xf62def);
}

// @ 0x00ba30c0
void* __thiscall W::Run_00ba30c0(void* out, uint32_t* key, int)
{
  HashSet* self = (HashSet*)this;
  uint32_t h = key[0] ^ key[2];
  unsigned b = h % self->mask;
  HashNode_s00ba_2590* n = self->buckets[b];
  while (n) {
    if (n->key[0] == (int)key[0] && n->key[1] == (int)key[1] && n->key[2] == (int)key[2]) {
      *(void**)out = n; *(void**)((char*)out + 4) = &self->buckets[b]; *(char*)((char*)out + 8) = 0;
      return out;
    }
    n = n->next;
  }
  InsertRes res;
  ((HashPolicy*)((char*)self + 0x10))->CheckSize(&res, self->mask, (unsigned)self->count, 1);
  n = (HashNode_s00ba_2590*)operator_new(0x24, "Simulator", 0, 0,
     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  for (int i = 0; i < 8; ++i) n->key[i] = (int)key[i];
  n->next = 0;
  if (res.flag) {
    unsigned nb = h % res.size;
    self->Rehash(res.size);
    b = nb;
  }
  n->next = self->buckets[b];
  self->buckets[b] = n;
  ++self->count;
  *(void**)out = n; *(void**)((char*)out + 4) = &self->buckets[b]; *(char*)((char*)out + 8) = 1;
  return out;
}

// @ 0x00ba31d0
void* __thiscall W::Run_00ba31d0(void* out, void* nodev, void** head)
{
  HashSet* self = (HashSet*)this;
  HashNode_s00ba_2590* node = (HashNode_s00ba_2590*)nodev;
  HashNode_s00ba_2590* prev = (HashNode_s00ba_2590*)*head;
  *(void**)((char*)out + 4) = head;
  *(void**)out = node->next;
  if (prev == node) *head = node->next;
  else { HashNode_s00ba_2590* p = prev->next; while (p != node) { prev = p; p = p->next; } prev->next = p->next; }
  if (*(void**)node) Release(*(void**)node);
  operator_delete__(node);
  --self->count;
  return out;
}

// @ 0x00ba3310
void __thiscall W::Run_00ba3310()
{
  char* s = (char*)this;
  VecHdr* a = (VecHdr*)(s + 0x20);
  a->FreeInts((int*)a->data, a->size);
  a->fieldC = 0;
  VecHdr* b = (VecHdr*)(s + 0x40);
  b->FreeNodes(b->data, b->size);
  b->fieldC = 0;
}

// @ 0x00ba3350
void __thiscall W::Run_00ba3350()
{ }

// @ 0x00ba33e0
void __cdecl FUN_00ba33e0(void* p1, void* p2)
{
  FUN_00ba2980(*(int*)((char*)p2 + 4), *(int*)((char*)p2 + 8));
  *(int*)((char*)p2 + 0xc) = 0;
  uint32_t count = 0;
  void* io = (*(void*(__thiscall*)(void*))((*(void***)p1)[0x20 / 4]))(p1);
  void* rd = (*(void*(__thiscall*)(void*))((*(void***)io)[0x18 / 4]))(io);
  EA_IO_ReadInt32(rd, &count, 1, 0);
}

// @ 0x00ba3550
void* __thiscall W::Run_00ba3550(void* src)
{
  if (src == this) return this;
  char* sb = *(char**)src; char* se = *((char**)src + 1);
  unsigned n = (unsigned)((se - sb) >> 4);
  char* db = *(char**)this;
  unsigned cap = (unsigned)((*((char**)this + 2) - db) >> 4);
  if (cap < n) {
    char* nb = (char*)FUN_00bc3e60(n, (int)sb, (int)se);
    if (db) operator_delete__(db);
    *(char**)this = nb; *((char**)this + 1) = nb + n * 0x10; *((char**)this + 2) = nb + n * 0x10;
    return this;
  }
  unsigned have = (unsigned)((*((char**)this + 1) - db) >> 4);
  if (have < n) { FUN_00ac4440(sb, sb + have * 0x10, db); *((char**)this + 1) = db + n * 0x10; return this; }
  FUN_00ac4440(sb, se, db);
  *((char**)this + 1) = db + n * 0x10;
  return this;
}

// @ 0x00ba3620
void* __thiscall W::Run_00ba3620(void* src)
{
  if (src == this) return this;
  char* sb = *(char**)src; char* se = *((char**)src + 1);
  unsigned n = (unsigned)((se - sb) >> 3);
  char* db = *(char**)this;
  unsigned cap = (unsigned)((*((char**)this + 2) - db) >> 3);
  if (cap < n) {
    if (db) operator_delete__(db);
    char* nb = 0;
    *(char**)this = nb; *((char**)this + 1) = nb + n * 8; *((char**)this + 2) = nb + n * 8;
    return this;
  }
  unsigned have = (unsigned)((*((char**)this + 1) - db) >> 3);
  if (have < n) { FUN_00ac4440(sb, sb + have * 8, db); *((char**)this + 1) = db + n * 8; return this; }
  FUN_00ac4440(sb, se, db);
  *((char**)this + 1) = db + n * 8;
  return this;
}

// @ 0x00ba36f0
int __cdecl FUN_00ba36f0(void* buf, int end, int ret)
{
  char* p = (char*)buf;
  if ((int)buf != end) {
    do {
      *(void**)(p + 0x08) = (void*)0x1465dc8;
      ((CGZTimer*)(p + 0x90))->Dtor();
      if (*(void**)(p + 0x70)) operator_delete__(*(void**)(p + 0x70));
      if (*(void**)(p + 0x58)) operator_delete__(*(void**)(p + 0x58));
      if (*(void**)(p + 0x40)) operator_delete__(*(void**)(p + 0x40));
      if (*(void**)(p + 0x28)) operator_delete__(*(void**)(p + 0x28));
      if (*(void**)(p + 0x10)) operator_delete__(*(void**)(p + 0x10));
      p += 0xb0;
    } while ((int)p != end);
  }
  return ret;
}

// @ 0x00ba37a0
void __thiscall W::Run_00ba37a0()
{
  char* s = (char*)this;
  *(void**)s = (void*)0x1465dc8;
  *(void**)(s + 4) = (void*)0x1465d78;
  *(void**)(s + 8) = (void*)0x1465d70;
  VecHdr* b = (VecHdr*)(s + 0x40);
  b->FreeNodes(b->data, b->size);
  b->fieldC = 0;
  if (b->size > 1) operator_delete__(b->data);
  VecHdr* a = (VecHdr*)(s + 0x20);
  a->FreeInts((int*)a->data, a->size);
  a->fieldC = 0;
  if (a->size > 1) operator_delete__(a->data);
  ((CGZSub*)(s + 4))->Dtor();
  *(void**)s = (void*)0x13eb394;
}

// @ 0x00ba3860
void __stdcall FUN_00ba3860(void* self)
{
    if (self == 0) return;
    void* ctx = (*(void*(__thiscall**)(void*, uint))((char*)*(void**)self + 0xc))(self, 0xd0036e08);
    if (ctx == 0) return;
    void* planet = SP_GetActivePlanet();
    void* out[9];
    void** vec = out;                       // local vector {begin, end, cap}
    vec[0] = (void*)&out[4];                // begin = inline buffer
    vec[1] = (void*)&out[4];                // end   = inline buffer (empty)
    vec[2] = (void*)&out[8];                // cap   = inline buffer end
    int n = (*(int(__thiscall**)(void*, int, int, void**, int, void*, void*))
             ((char*)*(void**)((char*)ctx + 0xc0) + 0x2c))((char*)ctx + 0xc0, 0x41f00000,
                                                           (int)out, vec + 0, 0,
                                                           (void*)0xd9a9c0, ctx);
    if (!(*(char(__thiscall**)(void*, int))((char*)*(void**)planet + 0x48))(planet, n)) return;
    int count = (int)((char*)vec[1] - (char*)vec[0]) >> 2;
    if (count <= 0) return;
    for (int i = 0; i < count; ++i) {
        void* e = ((void**)vec[0])[i];
        if (e == 0) continue;
        void* o = (*(void*(__thiscall**)(void*, uint))((char*)*(void**)e + 0xb8))(e, 0xd0036e08);
        if (o == 0) continue;
        if (*(int*)((char*)o + 0xb20) == *(int*)((char*)ctx + 0xb20)) {
            FUN_00ac8050(o, 0x10000, (char*)*(void**)((char*)o + 0xb4c) + 8);
            (*(void(__thiscall**)(void*, int))((char*)*(void**)ctx + 4))(ctx, 0);
        }
        (*(void(__thiscall**)(void*))((char*)*(void**)e + 0xc0))(e);
    }
}

// @ 0x00ba39f0
void* Ht::GetOrAdd1(const void* key)
{
    HIter it;
    Find(&it, key);
    if (it.node == this->bucket[this->bucketCount]) {
        const uint* k = (const uint*)key;
        uint e[8];
        e[0] = k[0]; e[1] = k[1]; e[2] = k[2];
        e[3] = 0; e[4] = 0; e[5] = 0; e[6] = 0; e[7] = 0xffffffff;
        uint tag = (uint)(size_t)key;
        Insert(&it, e, tag);
    }
    return (char*)it.node + 0xc;
}

// @ 0x00ba3a80
void* Eh::GetOrAdd2(const void* key)
{
    HIter it;
    Find(&it, key);
    if (it.node != this->bucket[this->bucketCount])
        return (char*)it.node + 4;
    void* ref = *(void**)key;
    if (ref) (*(void(__thiscall**)(void*))(*(void**)ref))(ref);
    // The table maps uint -> int; the stored pair is {key, value} (8 bytes, value starts at 0).
    uint pair[2];
    pair[0] = (uint)(size_t)ref;
    pair[1] = 0;
    uint tag = (uint)(size_t)key & 0xffffff00u;
    HIter out;
    Insert2(&out, pair, tag);
    if (ref) (*(void(__thiscall**)(void*))((char*)*(void**)ref + 4))(ref);
    return (char*)out.node + 4;
}

// @ 0x00ba3b10
u8 __cdecl FUN_00ba3b10(void* iface, const char* name, Goal* g)
{
    u8 result = 1;
    if (g->map1.size == 0) return result;
    Ht* map = &g->map1;
    WString tmp;
    bool converted = false;
    if (name != 0) {
        EA_ConvertToString16(&tmp, name, 0xffffffff);
        converted = true;
    } else {
        tmp.begin = 0; tmp.end = 0; tmp.cap = 0; tmp.alloc = 0;
        tmp.RangeInitialize(0);
    }
    WString dst;
    dst.CopyFrom(&tmp);
    if (converted) {
        if (((int)(tmp.end - tmp.begin) & ~1) > 2 && tmp.begin != 0)
            operator_delete__(tmp.begin);
    } else {
        if (((int)(dst.end - dst.begin) & ~1) > 2 && dst.begin != 0)
            operator_delete__(dst.begin);
    }
    {
        wchar_t* s = dst.begin;
        if (s == dst.end) s = g_wEmpty;
        (*(void(__thiscall**)(void*, wchar_t*))*(void**)iface)(iface, s);
    }
    {
        HtNode* first = map->bucket[0];
        HtNode** slot = map->bucket;
        if (first == 0) {
            slot = map->bucket + 1;
            first = map->bucket[1];
            while (first == 0) { ++slot; first = *slot; }
        }
        HtNode* end = map->bucket[map->bucketCount];
        u8 changed = 0;
        while (first != end) {
            if (changed) {
                changed = FUN_00ac8050(iface, 0, (char*)first + 0xc) ? 1 : 0;
            } else {
                changed = 0;
            }
            first = first->next;
            while (first == 0) { ++slot; first = *slot; }
        }
    }
    {
        wchar_t* s = tmp.begin;
        if (s == dst.begin) s = g_wEmpty;
        (*(void(__thiscall**)(void*, wchar_t*))((char*)*(void**)iface + 4))(iface, s);
    }
    if (((int)(dst.end - dst.begin) & ~1) > 2 && dst.begin != 0)
        operator_delete__(dst.begin);
    return result;
}

// @ 0x00ba3ca0
PPD* PPD::CopyCtor(const PPD& src)
{
    PPD* s = this;
    const PPD& o = src;
    s->vftbl = g_vtbl_PPD1;
    s->b0.Reserve((uint)((o.b0.end - o.b0.begin) >> 4), (void*)&o.b0.cap);
    UninitCopy16(&o.b0.begin, o.b0.begin, o.b0.end, s->b0.begin, (void*)&o.b0.begin);
    s->b0.end = o.b0.begin;
    s->b0.flag = o.b0.flag;
    s->b1.Reserve((uint)((o.b1.end - o.b1.begin) >> 4), (void*)&o.b1.cap);
    UninitCopy16(&o.b1.begin, o.b1.begin, o.b1.end, s->b1.begin, (void*)&o.b1.begin);
    s->b1.end = o.b1.begin;
    s->b1.flag = o.b1.flag;
    s->b2.Reserve((uint)((o.b2.end - o.b2.begin) >> 4), (void*)&o.b2.cap);
    UninitCopy16(&o.b2.begin, o.b2.begin, o.b2.end, s->b2.begin, (void*)&o.b2.begin);
    s->b2.end = o.b2.begin;
    s->b2.flag = o.b2.flag;
    s->b3.Reserve((uint)((o.b3.end - o.b3.begin) >> 4), (void*)&o.b3.cap);
    UninitCopy16(&o.b3.begin, o.b3.begin, o.b3.end, s->b3.begin, (void*)&o.b3.begin);
    s->b3.end = o.b3.begin;
    s->b3.flag = o.b3.flag;
    ((VBlk8*)&s->b4)->Reserve((uint)((o.b4.end - o.b4.begin) >> 3), (void*)&o.b4.cap);
    Copy8(&o.b4.begin, o.b4.begin, o.b4.end, s->b4.begin, (void*)&o.b4.begin);
    s->b4.end = o.b4.begin;
    s->b4.flag = o.b4.flag;
    *(void* volatile*)&s->timerVtbl = g_vtbl_TimerA;
    s->f84 = 0;
    s->f88 = o.f88; s->f8c = o.f8c; s->f90 = o.f90; s->f94 = o.f94;
    s->f98 = o.f98;
    s->f9c = o.f9c;
    s->timerVtbl = g_vtbl_TimerB;
    s->fa0 = o.fa0; s->fa1 = o.fa1; s->fa2 = o.fa2;
    return s;
}

// @ 0x00ba3ef0
void* __fastcall FUN_00ba3ef0(void* self_)
{
    char* s = (char*)self_;
    *(void**)s = &g_vtbl_GB1a;
    ((CGZSub_s00ba_3860*)(s + 4))->Ctor();
    float one = g_f1485720;
    float two = g_f1470f1c;
    *(void**)s = &g_vtbl_GB1b;
    *(void**)(s + 4) = &g_vtbl_GB1c;
    *(void**)(s + 8) = &g_vtbl_GB1d;
    *(float*)(s + 0x30) = one;
    *(float*)(s + 0x34) = two;
    *(int*)(s + 0x2c) = 0;
    *(int*)(s + 0x38) = 0;
    *(int*)(s + 0x28) = 1;
    *(void**)(s + 0x24) = &g_154df28;
    *(float*)(s + 0x50) = one;
    *(float*)(s + 0x54) = two;
    *(int*)(s + 0x4c) = 0;
    *(int*)(s + 0x58) = 0;
    *(int*)(s + 0x48) = 1;
    *(void**)(s + 0x44) = &g_154df28;
    return s;
}

// @ 0x00ba3f90
int Goal::Resolve(const void* key, void* a_, void* b_)
{
    Goal* self = this;
    char* a = (char*)a_;
    char* b = (char*)b_;
    const uint* k = (const uint*)key;
    void* mode = SP_GetCurrentGameMode();
    if (mode == &g_1654c10) {
        if ((a == 0 || ((*(uint*)(a + 0xb58) >> 9) & 1)) &&
            (b == 0 || ((*(uint*)(b + 0xb58) >> 9) & 1)))
            return 6;
        a = 0;
        if (b == 0 || ((*(uint*)(b + 0xb58) >> 9) & 1)) {
            if (a_ == 0) return 0;
            a = (char*)a_;
            if ((*(uint*)(a + 0xb58) >> 9) & 1) return 0;
        }
        if (a == 0) return 0;
        char ok = (*(char(__thiscall**)(char*))((char*)*(void**)a + 0x2c))(a);
        if (ok == 0 && *(char*)(a + 0xb5e) == 0) {
            HIter it;
            self->map2.Find(&it, &a);
            if (it.node == self->map2.bucket[self->map2.bucketCount]) {
                void* mgr = *(void**)0x016c7aa4;    // cThingManager singleton
                void* thing = (*(void*(__thiscall**)(void*))((char*)*(void**)mgr + 0x74))(mgr);
                int val;
                if (((*(uint*)(a + 0xb58) >> 8) & 1) == 0) {
                    void* gd = ((GameData_s00ba_3860*(*)(char*, void*))0x00b18530)(a, thing);
                    val = ((int(__cdecl*)(void*, int, void*))0x00ba28a0)(gd, 0, a);
                } else {
                    val = 6;
                }
                void* slot = self->map2.GetOrAdd2(&a);
                *(int*)slot = val;
                (*(void(__thiscall**)(char*))((char*)*(void**)a + 4))(a);
                return val;
            }
            int r = *(int*)((char*)it.node + 4);
            (*(void(__thiscall**)(char*))((char*)*(void**)a + 4))(a);
            return r;
        }
        (*(void(__thiscall**)(char*))((char*)*(void**)a + 4))(a);
        return 0;
    }
    if (a != 0) {
        if (b != 0) {
            char c1 = (*(char(__thiscall**)(char*))((char*)*(void**)a + 0xd0))(a);
            if (c1 == 0) {
                char c2 = (*(char(__thiscall**)(char*))((char*)*(void**)b + 0xd0))(b);
                if (c2 == 0) goto lab_424d;
            }
        }
        if ((*(char(__thiscall**)(char*))((char*)*(void**)a + 0xd0))(a) != 0) {
            if (b == 0) return 6;
            if ((*(char(__thiscall**)(char*))((char*)*(void**)b + 0xd0))(b) != 0) return 6;
        }
    }
    {
        uint local[3];
        local[0] = k[0]; local[1] = k[1]; local[2] = k[2];
        if (a == 0 || (*(char(__thiscall**)(char*))((char*)*(void**)a + 0xd0))(a) != 0) {
            if (b != 0 && (*(char(__thiscall**)(char*))((char*)*(void**)b + 0xd0))(b) == 0) {
                local[0] = *(uint*)(b + 0xb28);
                local[1] = *(uint*)(b + 0xb2c);
                local[2] = *(uint*)(b + 0xb30);
            }
        } else {
            local[0] = *(uint*)(a + 0xb28);
            local[1] = *(uint*)(a + 0xb2c);
            local[2] = *(uint*)(a + 0xb30);
        }
        HIter it;
        self->map1.Find(&it, local);
        if (it.node != self->map1.bucket[self->map1.bucketCount] &&
            *(int*)((char*)it.node + 0xc) != 0)
            return *(int*)((char*)it.node + 0xc);
    }
    {
        if (a != 0 && ((*(uint*)(a + 0xb58) >> 9) & 1) == 0) {
            void* c = FUN_00c0c1a0(a);
            if (c) return *(int*)((char*)c + 0x390);
        }
        if (b != 0 && ((*(uint*)(b + 0xb58) >> 9) & 1) == 0) {
            void* c = FUN_00c0c1a0(b);
            if (c) return *(int*)((char*)c + 0x390);
        }
    }
lab_424d:
    if (a != 0 && b != 0)
        return ((int(__cdecl*)(char*, char*))0x00ba27b0)(a, b);
    return 0;
}

// @ 0x00ba4270
int Goal::Field4(const void* key)
{
    int* e = (int*)this->map1.GetOrAdd1(key);
    return e[1];
}

// @ 0x00ba4290
int Goal::AddCount(const void* key, void* obj)
{
    int* e = (int*)this->map1.GetOrAdd1(key);
    e[2] = e[2] + 1;
    uint n = (uint)e[2];
    if (obj == 0) return 3;
    void* cm = (*(void*(__thiscall**)(void*, uint))((char*)*(void**)obj + 0xc))(obj, 0xd0036e08);
    if (cm == 0) return 3;
    if (n >= *(uint*)((char*)FUN_00c0c1a0(cm) + 0x40c)) return 6;
    if (n >= *(uint*)((char*)FUN_00c0c1a0(cm) + 0x408)) return 4;
    if (n < *(uint*)((char*)FUN_00c0c1a0(cm) + 0x404))
        return this->Resolve(key, obj, 0);
    return 3;
}

// @ 0x00ba4330
void Goal::Clear0c(const void* key)
{
    int* e = (int*)this->map1.GetOrAdd1(key);
    e[3] = 0;
}

// @ 0x00ba4350
void Goal::Set10(const void* key, int v)
{
    int* e = (int*)this->map1.GetOrAdd1(key);
    e[4] = v;
}

// @ 0x00ba4370
int Goal::Field8(const void* key)
{
    int* e = (int*)this->map1.GetOrAdd1(key);
    return e[2];
}

// @ 0x00ba4390
int Goal::Field0c(const void* key)
{
    int* e = (int*)this->map1.GetOrAdd1(key);
    return e[3];
}

// @ 0x00ba43b0
void* __thiscall VBlk::InsertAt(char* pos, const WKey* key)
{
    VBlk* self = this;
    char* end = self->end;
    char* at = pos;
    if (pos != end && WKeyLess(key, (const WKey*)pos))
        at = self->begin;
    at = (char*)LowerBound16(at, end, key, self->flag);
    if (at == end || WKeyLess((const WKey*)at, key))
        at = (char*)((Vec16*)self)->InsertSorted(at, (void*)key);
    return at;
}

// @ 0x00ba4430
PPD* PPD::Assign(const PPD& src)
{
    PPD* s = this;
    const PPD& o = src;
    s->b0.Assign((VBlk*)&o.b0); s->b0.flag = o.b0.flag;
    s->b1.Assign((VBlk*)&o.b1); s->b1.flag = o.b1.flag;
    s->b2.Assign((VBlk*)&o.b2); s->b2.flag = o.b2.flag;
    s->b3.Assign((VBlk*)&o.b3); s->b3.flag = o.b3.flag;
    s->b4.Assign((VBlk8*)&o.b4); s->b4.flag = o.b4.flag;
    s->f88 = o.f88; s->f8c = o.f8c; s->f90 = o.f90; s->f94 = o.f94;
    s->f98 = o.f98;
    s->f9c = o.f9c;
    s->fa0 = o.fa0; s->fa1 = o.fa1; s->fa2 = o.fa2;
    return s;
}

// @ 0x00ba4520
void* __thiscall VBlk::FindOrAdd2(const WKey* key)
{
    VBlk* self = this;
    char* end = self->end;
    char* at = (char*)LowerBound16(self->begin, end, key, self->flag);
    if (at == end || WKeyLess(key, (const WKey*)at)) {
        WKey tmp = *key;
        at = (char*)self->InsertAt(at, &tmp);
    }
    return at + 0xc;
}

// @ 0x00ba45a0
void* __cdecl FUN_00ba45a0(char* begin, char* end, char* dst)
{
    char* d = dst;
    char* e = end;
    if (e != begin) {
        do {
            e -= 0xb0;
            d -= 0xb0;
            *(int*)d = *(int*)(e + 0);
            ((PPD*)(d + 8))->Assign(*(PPD*)(e + 8));
        } while (e != begin);
    }
    return d;
}

// @ 0x00ba4600
void __cdecl FUN_00ba4600(void* obj)
{
    if (obj == 0) return;
    void* o = (*(void*(__thiscall**)(void*, uint))((char*)*(void**)obj + 0xc))(obj, 0xd0036e08);
    if (o == 0) return;
    ((ContObj*)SP_AchievementsController())->AutoTest(0x94f5e078, 1);
    FUN_00ba5e10(obj, 6);
    char* cm = (char*)FUN_00c04590(o);
    ((void(__cdecl*)(int, int, int, int))0x00b97600)(
        *(int*)(cm + 0x8c), *(int*)(cm + 0x88), *(int*)(cm + 0xf0),
        *(int*)((char*)obj + 0xb20));
    void* nm = SP_NounManager();
    AnimCtx* vec = (AnimCtx*)FUN_00b21340(nm, 0xcd7d10, 0xd3d420, 0xaccc30, 0xb1e500, 0x1be418e);
    char** end = (char**)((char*)vec + 8);
    for (char** v = (char**)*(void**)((char*)vec + 4); v != end; ++v) {
        char* e = *v;
        if (*(int*)(e + 0xa4) == *(int*)(cm + 0xa4))
            ((ThingIn*)e)->Set0x120();
    }
    void* k = FUN_00c0bc00();
    ((PropObj*)FUN_0067cb30())->UpdateProperty(0xaba34d01, k);
}

// @ 0x00ba46f0
void __cdecl FUN_00ba46f0(void* obj, int flag)
{
    if (obj == 0) return;
    void* o = (*(void*(__thiscall**)(void*, uint))((char*)*(void**)obj + 0xc))(obj, 0xd0036e08);
    if (o == 0) return;
    if ((char)flag != 0 && SP_GetCurrentGameMode() == (void*)0x01654c01)
        ((ContObj*)SP_AchievementsController())->AutoTest(0x19d844e6, 1);
    char* cm = (char*)FUN_00c04590(o);
    void* nm = SP_NounManager();
    AnimCtx* vec = (AnimCtx*)FUN_00b21340(nm, 0xcd7d10, 0xd3d420, 0xaccc30, 0xb1e500, 0x1be418e);
    char** end = (char**)((char*)vec + 8);
    for (char** v = (char**)*(void**)((char*)vec + 4); v != end; ++v) {
        char* e = *v;
        if (*(int*)(e + 0xa4) == *(int*)(cm + 0xa4))
            ((ThingIn2*)e)->Set((u8)flag);
    }
}

// @ 0x00ba47b0
void CModeObj::Update(int* key)
{
    void* self = this;
    StateBlock* sb = (StateBlock*)((char*)self + 0x20);
    int* st = sb->Get(key);
    *(int*)((char*)st + 8) = 0;
    void* mgr = SP_NounManager();
    Vec4i* vec = (Vec4i*)FUN_00b21340();
    int* base = (int*)vec->a;
    FUN_00b93c60();
    int* out;
    FUN_00829110();
    int* p = (int*)vec->a;
    int* q = base;
    int* end = (int*)vec->b;
    for (; q != end; q++) {
        int* obj = (int*)*q;
        if (obj[0x2ca] == key[0] && obj[0x2cb] == key[1] && obj[0x2cc] == key[2])
            obj[0x2d6] &= 0xffffff7f;
    }
    for (; p < end; p++) {
        int* obj = (int*)*p;
        if (obj)
            ((void(__thiscall*)(void*))((void**)*obj)[1])(obj);
    }
    if (base && base[-1])
        FUN_00f47380(base);
}

// @ 0x00ba4c70
void GoalVec::Insert(char* pos, char* src)
{
    GoalVec* self = this;
    char* end = self->end;
    if (end != self->cap) {
        if (pos <= src && src < end)
            src += 0xb0;
        if (end) {
            *(int*)end = *(int*)(end - 0xb0);
            FUN_00ba3ca0(end - 0xa8);
        }
        FUN_00ba45a0(pos, self->end - 0xb0, self->end);
        *(int*)pos = *(int*)src;
        FUN_00ba4430(src + 8);
        self->end += 0xb0;
        return;
    }
    int n = (end - self->begin) / 0xb0;
    if (n == 0)
        n = 1;
    else
        n *= 2;
    char* mem = 0;
    if (n)
        mem = (char*)operator_new(n * 0xb0);
    char* begin = self->begin;
    char* mid = (char*)FUN_00ba3ea0(begin, pos, mem);
    FUN_00ba36f0(begin, pos, mem);
    if (mid) {
        *(int*)mid = *(int*)src;
        FUN_00ba3ca0(src + 8);
    }
    char* oldEnd = self->end;
    char* last = (char*)FUN_00ba3ea0(pos, oldEnd, mid + 0xb0);
    FUN_00ba36f0(pos, oldEnd, mid + 0xb0);
    if (self->begin)
        FUN_00f47380(self->begin);
    self->begin = mem;
    self->end = last;
    self->cap = mem + n * 0xb0;
}

// @ 0x00ba4de0
int* GoalVec::Emplace(char* pos, char* src)
{
    GoalVec* self = this;
    int idx = (pos - self->begin) / 0xb0;
    char* end = self->end;
    if (pos == end && end != self->cap) {
        self->end = end + 0xb0;
        if (end) {
            *(int*)end = *(int*)src;
            ((VecElem*)(end + 8))->CopyFrom(src + 8);
            return (int*)(self->begin + idx * 0xb0);
        }
    } else {
        self->Insert(pos, src);
    }
    return (int*)(self->begin + idx * 0xb0);
}

// @ 0x00ba4e60
char* GoalVec::FindOrAdd(uint* key)
{
    GoalVec* self = this;
    MapNode* end = (MapNode*)self->end;
    MapNode* found = (MapNode*)FUN_00c72540(self->begin, end, key, self->flags14);
    if (found == end || *key < *(uint*)found) {
        char* tmp = (char*)FUN_00ba2f90();
        uint k = *key;
        FUN_00ba3ca0(tmp);
        end = (MapNode*)self->end;
        MapNode* lo = (found == end || *(uint*)found <= k) ? found : (MapNode*)self->begin;
        MapNode* hi = (found == end || *(uint*)found <= k) ? end : found;
        found = (MapNode*)FUN_00c72540(lo, hi, &k, self->flags14);
        if (found == end || k < *(uint*)found)
            found = (MapNode*)self->Emplace((char*)found, (char*)&k);
        FUN_00ba2f20(tmp);
        FUN_00ba2f20(tmp + 0xc0);
    }
    return (char*)found + 8;
}

// @ 0x00ba4f30
int __cdecl FUN_00ba4f30(int* obj)
{
    SP_GetActivePlanet();
    if (obj) {
        void* p = (void*)((int(__thiscall*)(void*, uint))((void**)*obj)[3])(obj, 0xd0036e08);
        if (p) {
            void* s = FUN_00c04590(p);
            if (s && *(int*)((char*)s + 0x160))
                *(uint*)(*(int*)((char*)s + 0x160) + 0x124) |= 1;
        }
    }
    void* planet = FUN_00c0bc00();
    char scanned = SetSpeciesAsScanned(planet);
    if (scanned)
        return 0;
    void* mode = (void*)SP_GetCurrentGameMode_s00ba_47b0();
    if (mode == &DAT_01654c10)
        return 0;
    char c = (char)((int(__thiscall*)(void*))((void**)*(void**)((char*)obj + 0xc0))[0x16])((char*)obj + 0xc0);
    int st = FUN_00ba3f90((int)obj, obj, 0);
    void* terr = SP_GetTerrainSphere(SP_NounManager());
    ((GoalVec*)&st)->FindOrAdd((uint*)&terr);
    void* p2 = FUN_00c0bc00();
    char* f = (char*)FUN_00ba4520(p2);
    *f = 1;
    void* p3 = FUN_00c0bc00();
    FUN_00b3d4c0(p3);
    int state = FUN_00ba3f90((int)p3, obj, 0);
    void* mode2 = (void*)SP_GetCurrentGameMode_s00ba_47b0();
    if (mode2 == &DAT_01654c10) {
        ((void(__thiscall*)(void*))((void**)*obj)[0xb])(obj);
    } else {
        char d = (char)((int(__thiscall*)(void*))((void**)*obj)[0x34])(obj);
        if (d == 0) {
            if (FUN_00c0c1a0(p3)) {
                if (state == 3) {
                    int* s = ((StateBlock*)((char*)obj + 0x20))->Get((int*)&p3);
                    s[3] = 0;
                } else if (state == 4) {
                    int* s = ((StateBlock*)((char*)obj + 0x20))->Get((int*)&p3);
                    s[1]++;
                }
                int* s = ((StateBlock*)((char*)obj + 0x20))->Get((int*)&p3);
                *s = state;
                FUN_00ba5e10(obj, 5);
                void* mode3 = (void*)SP_GetCurrentGameMode_s00ba_47b0();
                if (mode3 == &DAT_01654c01) {
                    void* q = FUN_00d37cb0();
                    ((void(__thiscall*)(void*, int))((void**)*(void**)q)[0xa])(q, 0);
                } else if (mode3 == &DAT_01654c02) {
                    void* q = FUN_00cd3440();
                    ((void(__thiscall*)(void*, int))((void**)*(void**)q)[0xa])(q, 0);
                }
            }
        } else {
            int* s = ((StateBlock*)((char*)obj + 0x20))->Get((int*)&p3);
            *s = state;
            FUN_00ba5e10(obj, 7);
        }
    }
    char e = (char)((int(__thiscall*)(void*))((void**)*(void**)((char*)obj + 0xc0))[0x16])((char*)obj + 0xc0);
    FUN_00ba5e10(obj, (e ? 6 : 0) + 1);
    FUN_00b3d4f0(p3);
    FUN_00e30d20(p3);
    void* mode4 = (void*)SP_GetCurrentGameMode_s00ba_47b0();
    if (mode4 == &DAT_01654c01) {
        FUN_00675250(0xd35d68dd, 1);
        FUN_00675370();
        if (!FUN_00675e80(0xd35d68dd)) {
            void* q = FUN_00c0bc00();
            uint val = *(uint*)q;
            // hashtable insert not reconstructed
            (void)val;
        } else {
            FUN_00675770();
        }
    }
    return 1;
}

// @ 0x00ba51f0
void __cdecl FUN_00ba51f0()
{
    Telemetry* t = (Telemetry*)FUN_0067de90();
    for (int i = 7; i <= 0xb; i++)
        t->Reset(i);
}

// @ 0x00ba5220
int __cdecl FUN_00ba5220()
{
    int mode = SP_GetCurrentGameMode_s00ba_47b0();
    switch (mode) {
    case 0x1654c00: return 7;
    case 0x1654c01: return 8;
    case 0x1654c02: return 9;
    case 0x1654c04: return 10;
    case 0x1654c05: return 11;
    default:        return 11;
    }
}

// @ 0x00ba5270
int* __cdecl FUN_00ba5270(int obj, uint arg)
{
    if (obj == 0)
        return 0;
    void* res = FUN_0067de90(FUN_00ba5220(), 0);
    int* vec = (int*)((ResMgr*)res)->Get();
    if (vec == 0)
        return 0;
    ((IntVector*)vec)->resize(0xc);
    void* gt = SP_GameTimeManager();
    unsigned __int64 t = ((TimeMgr*)gt)->Get();
    int* p = (int*)vec[3];
    p[0] = (int)(t / 1000);
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = arg;
    p[5] = (int)((CommRef*)(obj + 0x13c))->GetCommContext();
    p[6] = 5;
    void* x = ((Obj94*)(void*)obj)->Get();
    p[7] = x ? *(int*)((char*)x + 0x10) : 0xff576f79;
    p[8] = 0;
    p[9] = ((int(__thiscall*)(void*))((void**)*(void**)(obj + 0xd4))[0x13])((void*)(obj + 0xd4));
    p[10] = 0xf4c9dc5a;
    return vec;
}

// @ 0x00ba5350
void __cdecl FUN_00ba5350_impl(int** out, int* begin, int* end, int a, int b, int c)
{
    if (begin == end) {
        *out = begin;
        return;
    }
    while (begin != end) {
        int* node = (int*)begin[5];
        if (node[2] == a && node[1] == b && node[3] == c && node[9] == -1)
            break;
        begin = (int*)*begin;
    }
    *out = begin;
}

// @ 0x00ba53b0
void __cdecl FUN_00ba53b0_impl(int** out, int* begin, int* end, int a, int b, int c)
{
    if (begin == end) {
        *out = begin;
        return;
    }
    while (begin != end) {
        int* node = (int*)begin[5];
        if (node[2] == a && node[1] == b && node[3] == c)
            break;
        begin = (int*)*begin;
    }
    *out = begin;
}

// @ 0x00ba5410
char* CursorProvider::FindByField10(uint key, int match)
{
    CursorProvider* self = this;
    MapNode* found[2];
    char* result = 0;
    HashTable* t = &self->table;
    t->Find(found, &key);
    MapNode** buckets = t->buckets;
    if (found[0] != buckets[t->bucketCount]) {
        MapNode* head = (MapNode*)((char*)found[0] + 4);
        for (MapNode* n = head->next; n != head; n = n->next) {
            if (*(int*)((char*)n->value + 0x10) == match) {
                if (n != head)
                    result = (char*)n + 8;
                break;
            }
        }
    }
    return result;
}

// @ 0x00ba5470
char* CursorProvider::FindFirst10(uint* key, int a, int b, int c)
{
    CursorProvider* self = this;
    MapNode* found[2];
    char* result = 0;
    HashTable* t = &self->table;
    t->Find(found, key);
    MapNode** buckets = t->buckets;
    if (found[0] != buckets[t->bucketCount]) {
        MapNode* head = (MapNode*)((char*)found[0] + 4);
        void* res;
        FUN_00ba5350_impl((int**)&res, (int*)head->next, (int*)head, a, b, c);
        if (res != head)
            result = (char*)res + 8;
    }
    return result;
}

// @ 0x00ba54f0
char* CursorProvider::FindFirst24(uint* key, int a, int b, int c)
{
    CursorProvider* self = this;
    MapNode* found[2];
    char* result = 0;
    HashTable* t = &self->table;
    t->Find(found, key);
    MapNode** buckets = t->buckets;
    if (found[0] != buckets[t->bucketCount]) {
        MapNode* head = (MapNode*)((char*)found[0] + 4);
        void* res;
        FUN_00ba53b0_impl((int**)&res, (int*)head->next, (int*)head, a, b, c);
        if (res != head)
            result = (char*)res + 8;
    }
    return result;
}

// @ 0x00ba5570
char* CursorProvider::FindByField24(uint key, int match)
{
    CursorProvider* self = this;
    MapNode* found[2];
    char* result = 0;
    HashTable* t = &self->table;
    t->Find(found, &key);
    MapNode** buckets = t->buckets;
    if (found[0] != buckets[t->bucketCount]) {
        MapNode* head = (MapNode*)((char*)found[0] + 4);
        for (MapNode* n = head->next; n != head; n = n->next) {
            if (*(int*)((char*)n->value + 0x24) == match) {
                if (n != head)
                    result = (char*)n + 8;
                break;
            }
        }
    }
    return result;
}

// @ 0x00ba55d0
void CursorProvider::UpdateEntry(uint key, int a, int b, int c, int d, int e, int f)
{
    CursorProvider* self = this;
    MapNode* found[2];
    HashTable* t = &self->table;
    t->Find(found, &key);
    MapNode** buckets = t->buckets;
    if (found[0] != buckets[t->bucketCount]) {
        MapNode* head = (MapNode*)((char*)found[0] + 4);
        for (MapNode* n = head->next; n != head; n = n->next) {
            int* v = (int*)n->value;
            if (v[2] == a && v[1] == b && v[3] == c) {
                v[1] = d;
                v[2] = e;
                v[3] = f;
            }
        }
    }
}

// @ 0x00ba6800
void FUN_00ba6800(void* base, int lo, int hi, int a4, int a5, int a6, char (__cdecl *cmp)(void*, void*))
{
  while (lo < hi) {
    int parent = (hi - 1) >> 1;
    char* p = (char*)base + parent * 0xc;
    if (!cmp(p, &a4)) break;
    char* cur = (char*)base + hi * 0xc;
    *(int*)(cur + 0) = *(int*)(p + 0);
    *(int*)(cur + 4) = *(int*)(p + 4);
    *(int*)(cur + 8) = *(int*)(p + 8);
    hi = parent;
  }
  char* dst = (char*)base + hi * 0xc;
  *(int*)(dst + 0) = a4;
  *(int*)(dst + 4) = a5;
  *(int*)(dst + 8) = a6;
}

// @ 0x00ba6880
StarSearchCriteria::StarSearchCriteria()
{
  m0 = 0x1fff;
  m4 = 0x3f;
  m8 = 0;
  mC = g_13eb1bc;
  m10 = g_13eb1bc;
  m14 = g_13eb1bc;
  m18 = 0;
}

// @ 0x00ba6a40
void FUN_00ba6a40(unsigned which, unsigned* bits)
{
  *bits &= 0xffffffbc;
  for (unsigned i = 0; i <= 3; ++i) {
    int bit;
    switch (i) {
    case 1:  bit = 3; break;
    case 2:  bit = 4; break;
    case 3:  bit = 5; break;
    default: bit = 2; break;
    }
    if (i == which) *bits |= 1u << bit;
    else            *bits &= ~(1u << bit);
  }
}

// @ 0x00ba6ab0
int FUN_00ba6ab0(unsigned* flags)
{
  unsigned f = *flags;
  int n = (f & 1) != 0;
  if ((f >> 1) & 1) n++;
  if ((f >> 2) & 1) n++;
  if ((f >> 3) & 1) n++;
  int pick = (n > 1) ? (int)((Rng*)0x1601760)->NextU((unsigned)n) : 0;
  f = *flags;
  if (f & 1) { if (pick == 0) return 0; --pick; }
  if (f & 2) { if (pick == 0) return 1; --pick; }
  if (f & 4) { if (pick == 0) return 2; --pick; }
  return (f & 8) ? 3 : 0;
}

// @ 0x00ba6cf0
void FUN_00ba6cf0(BannerList* self)
{
  int n = (int)(((char*)self->mCC - (char*)self->mC8)) / 0x14;
  for (int i = 0; i < n; ++i) {
    char* grp = (char*)self->mC8 + i * 0x14;
    void** begin = *(void***)(grp + 0);
    int cnt = ((int)*(void***)(grp + 4) - (int)begin) >> 2;
    for (int j = 0; j < cnt; ++j) {
      ((GameObj*)begin[j])->Pop(0x10030, 0);
    }
  }
}

// @ 0x00ba6d80
int FUN_00ba6d80(BannerList* self, unsigned id)
{
  if (id == 0) return *(int*)&self->m14C;
  if (id == 0xffffffff) return 0;
  void** inner = (void**)self->mC8;
  void* row = inner[(id >> 0xc) * 5];
  return *(int*)((char*)row + (id & 0xfff) * 4);
}

// @ 0x00ba6e00
int FUN_00ba6e00(BannerList* self, void* arg)
{
  if (*(char*)((char*)self + 0x64) != 0) return 1;
  if (g_1689df8 != 0) return 1;
  int cnt = (int)(*(int*)((char*)self + 0xe0) - *(int*)((char*)self + 0xdc)) >> 2;
  g_1689df8 = 1;
  int all = 1;
  for (int i = 0; i < cnt; ++i) {
    void** elems = *(void***)((char*)self + 0xdc);
    if (!((GameObj*)elems[i])->Match(arg) || !all) all = 0;
    else all = 1;
  }
  g_1689df8 = 0;
  return all;
}

// @ 0x00ba6e80
int __stdcall FUN_00ba6e80(int* vec, void* civ, float threshold, int maxGroups)
{
  int n = (vec[1] - vec[0]) >> 2;
  int w = FUN_00ba6b40(vec, 0, civ, threshold);
  int group = 1;
  int boundary = w;
  if (maxGroups == 0 || maxGroups > 1) {
    for (int i = 0; i < n; ++i) {
      if (i >= w) return w;
      if (i == boundary) {
        ++group;
        boundary = w;
        if (maxGroups != 0 && group > maxGroups) return w;
      }
      void* cities = FUN_005c65e0((void*)vec[i]);
      w = FUN_00ba6b40(vec, w, cities, threshold);
    }
  }
  return w;
}

// @ 0x00ba6f20
int FUN_00ba6f20(BannerList* self, int obj)
{
  if (((GameObj*)obj)->AddRef() != 2) return 0;
  int* begin = *(int**)((char*)self + 0x104);
  int* end = *(int**)((char*)self + 0x108);
  int* p = begin;
  while (p != end && *p != obj) ++p;
  int idx = (int)(p - begin);
  if (((GameObj*)obj)->Flag(0x400) == 0) {
    --idx;
    if (((GameObj*)obj)->Flag(0x400) != 0) {
      while (idx >= 0 && ((GameObj*)*(begin + idx))->Flag(0x400) != 0) --idx;
    }
  }
  return *(int*)((char*)begin + (idx + 1) * 4);
}

// @ 0x00ba7050
void GMStub::M50(int a, int b)
{
  if ((void*)FUN_00b5b800() == &g_1654c05) {
    void* o = *(void**)((char*)this + 0x204);
    int* vt = *(int**)o;
    ((void(__thiscall*)(void*, int, int))vt[3])(o, a, b);
  }
}

// @ 0x00ba7080
void GMStub::M80(int a, int b)
{
  EmpireStub* o = (EmpireStub*)FUN_01021300();
  o->Prep();
  void* q = *(void**)((char*)this + 0x204);
  int* vt = *(int**)q;
  ((void(__thiscall*)(void*, int, int))vt[4])(q, a, b);
}

// @ 0x00ba70d0
void Vec50Obj::Erase(int value)
{
  int* p = m50;
  int* end = m54;
  while (p != end) {
    if (*p == value) {
      *p = end[-1];
      m54 -= 1;
      return;
    }
    ++p;
  }
}

// @ 0x00ba7100
void FUN_00ba7100(float* pos, int* outx, int* outy)
{
  float s = 64.0f / g_156c638;
  int x = (int)(pos[0] * s) + 0x20;
  int y = (int)(pos[1] * s) + 0x20;
  int z = 0;
  int* px = (x < 0x3f) ? &x : (int*)&g_1459c40;
  if (*px <= 0) px = &z;
  *outx = *px;
  int* py = (y < 0x3f) ? &y : (int*)&g_1459c40;
  if (*py > 0) { *outy = *py; return; }
  *outy = 0;
}

// @ 0x00ba7220
void FUN_00ba7220(StarManagerCore* self, int* key)
{
  char* grp = (char*)self->mC8;
  char* end = (char*)self->mCC;
  if (grp == end) return;
  do {
    int* p = *(int**)grp;
    int* e = *(int**)(grp + 4);
    if (p != e) {
      do {
        int obj = *p;
        if (*(int*)(obj + 0x74) == key[0] &&
            *(int*)(obj + 0x78) == key[1] &&
            *(int*)(obj + 0x7c) == key[2]) {
          ((GameObj*)obj)->OnBan();
        }
        ++p;
      } while (p != e);
    }
    grp += 0x14;
  } while (grp != end);
}

// @ 0x00ba72c0
void* FUN_00ba72c0(void* writer, int* vec)
{
  int count = (vec[1] - vec[0]) >> 2;
  IStream* s = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
  IWriter* w = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s)[6])(s);
  FUN_0093aa70(w, &count, 1, 0);
  for (int i = 0; i < count; ++i) {
    ((void(__thiscall*)(void*, int))(*(int**)writer)[11])(writer, ((int*)vec[0])[i]);
  }
  return writer;
}

// @ 0x00ba7320
int FUN_00ba7320(int* vec)
{
  int* p = (int*)vec[0];
  int* e = (int*)vec[1];
  double total = 0.0;
  if (p == e) return (int)((int)e - (int)p) >> 2;
  for (; p != e; ++p) total += (double)*p;
  if (total <= 0.0) return (int)((int)e - (int)(int*)vec[0]) >> 2;
  double r = ((Rng*)0x1601760)->Next() * total;
  if (r < total) {
    double acc = 0.0;
    int idx = 0;
    for (int* q = (int*)vec[0]; q != (int*)vec[1]; ++q, ++idx) {
      acc += (double)*q;
      if (r < acc) return idx;
    }
  }
  return ((vec[1] - vec[0]) >> 2) - 1;
}

// @ 0x00ba73b0
void FUN_00ba73b0(void* writer, int* vec)
{
  int count = (vec[1] - vec[0]) / 0x14;
  IStream* s = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
  IWriter* w = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s)[6])(s);
  FUN_0093aa70(w, &count, 1, 0);
  char* p = (char*)vec[0];
  char* e = (char*)vec[1];
  for (; p != e; p += 0x14) FUN_00ba72c0(writer, (int*)p);
  ((void(__thiscall*)(void*))(*(int**)writer)[7])(writer);
}

// @ 0x00ba7450
char FUN_00ba7450(int arg, char* node)
{
  char* e = node + 4;
  for (char* n = *(char**)(node + 8); n != e; n = (char*)FUN_00921580(n)) {
    void* o = *(void**)(n + 0x14);
    if (o) ((void(__thiscall*)(void*, int))(*(int**)o)[7])(o, arg);
  }
  return 1;
}

// @ 0x00ba7490
void FUN_00ba7490(void* writer, int* vec)
{
  int count = (vec[1] - vec[0]) >> 4;
  IStream* s = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
  IWriter* w = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s)[6])(s);
  FUN_0093aa70(w, &count, 1, 0);
  char* p = (char*)vec[0];
  char* e = (char*)vec[1];
  for (; p != e; p += 0x10) {
    IStream* s2 = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
    IWriter* w2 = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s2)[6])(s2);
    FUN_00692e00(((void*(__thiscall*)(void*, char*))(*(int**)w2)[6])(w2, p));
  }
  ((void(__thiscall*)(void*))(*(int**)writer)[7])(writer);
}

// @ 0x00ba7510
void FUN_00ba7510(void* writer, int* vec)
{
  int count = (vec[1] - vec[0]) >> 4;
  IStream* s = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
  IWriter* w = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s)[6])(s);
  FUN_0093aa70(w, &count, 1, 0);
  char* p = (char*)vec[0];
  char* e = (char*)vec[1];
  for (; p != e; p += 0x10) {
    IStream* s2 = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
    IWriter* w2 = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s2)[6])(s2);
    FUN_00692e50(((void*(__thiscall*)(void*, char*))(*(int**)w2)[6])(w2, p));
  }
  ((void(__thiscall*)(void*))(*(int**)writer)[7])(writer);
}

// @ 0x00ba7590
void FUN_00ba7590(void* writer, char* node)
{
  int first = *(int*)(node + 0x14);
  IStream* s = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
  IWriter* w = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s)[6])(s);
  FUN_0093aa70(w, &first, 1, 0);
  char* e = node + 4;
  for (char* n = *(char**)(node + 8); n != e; n = (char*)FUN_00921580(n)) {
    IStream* s2 = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
    IWriter* w2 = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s2)[6])(s2);
    int v = *(int*)(n + 0x10);
    FUN_0093aa70(w2, &v, 1, 0);
    ((void(__thiscall*)(void*))(*(int**)writer)[7])(writer);
    IStream* s3 = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
    IWriter* w3 = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s3)[6])(s3);
    int v2 = *(int*)(n + 0x14);
    FUN_0093aa70(w3, &v2, 1, 0);
    ((void(__thiscall*)(void*))(*(int**)writer)[7])(writer);
  }
  ((void(__thiscall*)(void*))(*(int**)writer)[7])(writer);
}

// @ 0x00ba7720
void RefPushHeap(RefObj** param_1, RefObj** param_2)
{
    for (RefObj** piVar5 = param_1; piVar5 != param_2; piVar5 = piVar5 + 1) {
        RefObj* piVar1 = *piVar5;
        if (piVar1 != 0) {
            piVar1->AddRef();
        }
        RefObj** piVar4 = piVar5;
        param_1 = piVar5;
        RefObj** piVar2 = piVar5 - 1;
        if (piVar1->m28 < (*(piVar5 - 1))->m28) {
            do {
                param_1 = piVar2;
                RefObj* newObj = *param_1;
                RefObj* oldObj = *piVar4;
                if (newObj != oldObj) {
                    if (newObj != 0) {
                        newObj->AddRef();
                    }
                    *piVar4 = newObj;
                    if (oldObj != 0) {
                        oldObj->Release();
                    }
                }
                piVar4 = param_1;
                piVar2 = param_1 - 1;
            } while (piVar1->m28 < (*(param_1 - 1))->m28);
        }
        RefObj* piVar4b = *param_1;
        if (piVar1 != piVar4b) {
            piVar1->AddRef();
            *param_1 = piVar1;
            if (piVar4b != 0) {
                piVar4b->Release();
            }
        }
        piVar1->Release();
    }
}

// @ 0x00ba77e0
void InsertionSortC(ElemC* first, ElemC* last, bool (*compare)(const ElemC*, const ElemC*))
{
    if (first == last)
        return;
    for (ElemC* iNext = first + 1; iNext != last; ++iNext) {
        ElemC temp = *iNext;
        ElemC* p = iNext;
        while (p != first) {
            ElemC* prev = p - 1;
            if (!compare(&temp, prev))
                break;
            *p = *prev;
            p = prev;
        }
        *p = temp;
    }
}

// @ 0x00ba7880
void InsertionSortSimpleC(ElemC* first, ElemC* last, bool (*compare)(const ElemC*, const ElemC*))
{
    if (first == last)
        return;
    for (ElemC* iNext = first + 1; iNext != last; ++iNext) {
        ElemC temp = *iNext;
        ElemC* p = iNext - 1;
        if (!compare(&temp, p)) {
            *iNext = temp;
            continue;
        }
        do {
            *(*((ElemC**)&p + 1)) = *p;
        } while (compare(&temp, --p));
        *(p + 1) = temp;
    }
}

// @ 0x00ba7920
void UninitMove16(Elem16* first, Elem16* last, Elem16* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst != 0) {
            dst->a = first->a;
            dst->b = first->b;
            dst->c = first->c;
            dst->d = first->d;
        }
    }
}

// @ 0x00ba7960
void UninitMove12(ElemC* first, ElemC* last, ElemC* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst != 0) {
            dst->x = first->x;
            dst->y = first->y;
            dst->z = first->z;
        }
    }
}

// @ 0x00ba79a0
void RefAdjustHeap(RefObj** first, uint topPosition, uint heapSize, uint position, RefObj* value)
{
    uint childPosition = (2 * position) + 2;
    while (childPosition < heapSize) {
        if ((*(first + childPosition))->m28 < (*(first + childPosition - 1))->m28)
            --childPosition;
        RefObj* old = *(first + position);
        RefObj* moved = *(first + childPosition);
        if (moved != old) {
            if (moved)
                moved->AddRef();
            *(first + position) = moved;
            if (old)
                old->Release();
        }
        position = childPosition;
        childPosition = (2 * childPosition) + 2;
    }
    if (childPosition == heapSize) {
        RefObj* old = *(first + position);
        RefObj* moved = *(first + childPosition - 1);
        if (moved != old) {
            if (moved)
                moved->AddRef();
            *(first + position) = moved;
            if (old)
                old->Release();
        }
        position = childPosition - 1;
    }
    if (value)
        ;
    RefPromoteHeap(first, topPosition, position, value);
}

// @ 0x00ba7a80
void ElemCAdjustHeap(ElemC* first, uint topPosition, int heapSize, int position, ElemC value, bool (*compare)(const ElemC*, const ElemC*))
{
    int iVar6;
    for (;;) {
        iVar6 = position * 2 + 2;
        if (iVar6 >= heapSize)
            break;
        if (compare(&first[iVar6], &first[iVar6 - 1]))
            --iVar6;
        first[position] = first[iVar6];
        position = iVar6;
    }
    if (iVar6 == heapSize) {
        first[position] = first[iVar6 - 1];
        position = iVar6 - 1;
    }
    ElemCPromoteHeapHelper(first, topPosition, (uint)position, value, compare);
}

// @ 0x00ba7bd0
HashTableCtl* HashTableCtl::Reset()
{
    m00 = 0x7f;
    m04 = 0x3f;
    m08 = 0x3f;
    m0c = 0;
    m0d = 0;
    m0e = 0;
    m0f = 1;
    m10 = 0xf;
    m14 = 0xf;
    m18 = 0;
    m1c = 0;
    m20 = 0;
    m24 = 0;
    m28 = 0;
    m34 = 0;
    m38 = 0;
    m3c = 0;
    m18 |= 7;
    m1c |= 3;
    return this;
}

// @ 0x00ba7c20
void LoadAndRegisterPropertyList(void* self, uint param2)
{
    void* mgr = EA_ResourceMan_GetManager();
    // resource handle triple { param2, 0x366a930d, g_0156c5f4 }
    struct Key { uint a, b, c; } key;
    key.a = param2;
    key.b = 0x366a930d;
    key.c = *(uint*)0x0156c5f4;

    void* res = 0;
    ((void(*)(void*, void*, void*, void*, void*, void*, void*))(*(void***)mgr)[3])
        (mgr, &key, &key, 0, 0, 0, 0);
    void* handle = 0;
    (void)res;
    if (handle) {
        void* table = ((void*(*)(void*, uint))(*(void***)handle)[3])(handle, 0xe742574a);
        if (table) {
            void* pl = operator_new(0x38, "Simulator", 0, 0, 0, 0);
            if (pl)
                pl = SP_PropertyList_ctor(pl);
            void* idg = SP_IDGenerator();
            uint id3 = 0;
            ((void(*)(void*, uint*, uint, uint, uint, uint))(*(void***)idg)[1])
                (idg, &id3, 0xb1b104, 0x84, 0, 0xa0);
            (void)id3;
            void* pm = SP_PropertyManager();
            ((void(*)(void*, void*, uint, uint, uint, uint))(*(void***)pm)[0x34/4])(pm, pl, 0, 0, 0, 0);
            void* sub = (char*)table + 0x18;
            void* pm2 = SP_PropertyManager();
            FUN_006a3dd0(sub);
            (void)pm2;
            ((void(*)(void*, void*))(*(void***)pl)[0x2c/4])(pl, sub);
            SP_PropertyList_SetParent(pl, *(void**)((char*)table + 0x48));
            FUN_00b8dde0(&key, 0);
        }
    }
}

// @ 0x00ba7d60
void StarManagerTreeWalk()
{
    char* sm = (char*)SP_StarManager();
    char* tree = sm + 0x150;
    for (RBNode* n = *(RBNode**)(tree + 8);
         n != (RBNode*)(tree + 4);
         n = RBTreeIncrement(n)) {
    }
}

// @ 0x00ba7dc0
void ModelWorldCheatExecute(char* self)
{
    uint n1 = (uint)((*(int*)(self + 0x54) - *(int*)(self + 0x50)) >> 2);
    for (uint i = 0; i < n1; ++i)
        FUN_00c71910(*(void**)(*(int*)(self + 0x50) + i * 4));

    int n2 = (*(int*)(self + 0x40) - *(int*)(self + 0x3c)) >> 2;
    for (int i = 0; i < n2; ++i)
        FUN_00c8b7d0(*(void**)(*(int*)(self + 0x3c) + i * 4));

    for (RBNode* n = *(RBNode**)(self + 0x158);
         n != (RBNode*)(self + 0x154);
         n = RBTreeIncrement(n))
        FUN_00c33580(*(void**)((char*)n + 0x14));

    void* nm = SP_NounManager();
    char* sphere = (char*)SP_NounManager_GetCurrentTerrainSphere(nm);
    FUN_00ba6cf0(self);

    bool cond = g_0168964c < 0x21000f;

    uint m1 = (uint)((*(int*)(sphere + 0x1188) - *(int*)(sphere + 0x1184)) >> 2);
    for (uint i = 0; i < m1; ++i) {
        uint u = *(uint*)(*(int*)(sphere + 0x1184) + i * 4);
        void* obj;
        if (u == 0)
            obj = *(void**)(self + 0x14c);
        else if (u == 0xffffffff)
            obj = 0;
        else
            obj = *(void**)(*(int*)(*(int*)(self + 0xc8) + (u >> 0xc) * 0x14) + (u & 0xfff) * 4);
        FUN_00bb9bb0(obj, 1);
        FUN_00bb9be0(obj, 1);
        if (cond && FUN_00801920(obj) == 2)
            FUN_00c7a160(sphere, obj);
    }

    uint m2 = (uint)((*(int*)(sphere + 0x119c) - *(int*)(sphere + 0x1198)) >> 2);
    for (uint i = 0; i < m2; ++i) {
        uint u = *(uint*)(*(int*)(sphere + 0x1198) + i * 4);
        void* obj;
        if (u == 0)
            obj = *(void**)(self + 0x14c);
        else if (u == 0xffffffff)
            obj = 0;
        else
            obj = *(void**)(*(int*)(*(int*)(self + 0xc8) + (u >> 0xc) * 0x14) + (u & 0xfff) * 4);
        FUN_00bb9be0(obj, 1);
    }

    uint m3 = (uint)((*(int*)(sphere + 0x11b0) - *(int*)(sphere + 0x11ac)) >> 2);
    for (uint i = 0; i < m3; ++i) {
        uint u = *(uint*)(*(int*)(sphere + 0x11ac) + i * 4);
        void* obj;
        if (u == 0)
            obj = *(void**)(self + 0x14c);
        else if (u == 0xffffffff)
            obj = 0;
        else
            obj = *(void**)(*(int*)(*(int*)(self + 0xc8) + (u >> 0xc) * 0x14) + (u & 0xfff) * 4);
        FUN_00bb9b00(obj, 0x10000, 1);
    }

    char* empire = (char*)SP_cSPLivingUniverse_GetPlayerEmpire();
    *(uint*)(empire + 0x50) |= 0x40;

    void* obj = FUN_00c30c60();
    void* old = *(void**)(self + 0x1dc);
    if (obj != old) {
        if (obj)
            (*(void(**)(void*))(*(void***)obj)[0])(obj);
        *(void**)(self + 0x1dc) = obj;
        if (old)
            (*(void(**)(void*))(*(void***)old)[1])(old);
    }
}

// @ 0x00ba8010
void* GetPropertyTriple(void* self, void* out, uint key, void* propId)
{
    (void)self;
    uint a = 0, b = 0, c = 0;
    void* prop = 0;
    void* pm = SP_PropertyManager();
    bool found = ((bool(*)(void*, void*, uint, uint, uint, uint))(*(void***)pm)[0x2c/4])
        (pm, propId, 0xe38475d9, 0, 0, 0);
    (void)found;
    (void)a; (void)b; (void)c;
    *(uint*)out = a;
    *(uint*)((char*)out + 4) = b;
    *(uint*)((char*)out + 8) = c;
    (void)key;
    return out;
}

// @ 0x00ba8160
void TypeTagger::SetIfType(void* typeTag)
{
    if (typeTag == &DAT_01654c10) {
        RefObj* src = mp14c;
        RefObj* old = mp1dc;
        if (src != old) {
            if (src)
                src->AddRef();
            mp1dc = src;
            if (old)
                old->Release();
        }
    }
}

// @ 0x00ba81b0
void* HashOwner::Lookup(void* key)
{
    void* k = key;
    void** p = mp0c8;
    if (p != mp0cc) {
        do {
            void** e = (void**)*p;
            void** eEnd = (void**)p[1];
            if (e != eEnd) {
                do {
                    void* obj = *e;
                    if (FUN_006ab760(((LookupObj*)obj)->Hash(k), (const wchar_t*)k))
                        return obj;
                    ++e;
                } while (e != eEnd);
            }
            p += 5;
        } while (p != mp0cc);
    }
    return 0;
}

// @ 0x00ba8220
void TwoArrayOwner::Free()
{
    if (mp34 && *(int*)((char*)mp34 - 4) != 0)
        operator_delete__(mp34);
    if (mp20 && *(int*)((char*)mp20 - 4) != 0)
        operator_delete__(mp20);
}

// @ 0x00ba8340
void __stdcall DestroyBucketRange(char* first, char* last)
{
    for (; first < last; first += 0x14) {
        void** eEnd = *(void***)(first + 4);
        void** e = *(void***)first;
        for (; e < eEnd; ++e) {
            RefObj* obj = (RefObj*)*e;
            if (obj)
                obj->Release();
        }
        void* mem = *(void**)first;
        if (mem && *(int*)((char*)mem - 4) != 0)
            operator_delete__(mem);
    }
}

// @ 0x00ba8550
int ElemCMakeHeap(ElemC* first, ElemC* last, bool (*compare)(const ElemC*, const ElemC*))
{
    int n = (int)((char*)last - (char*)first) / 0xc;
    if (n >= 2) {
        int position = ((n - 2) >> 1) + 1;
        ElemC* p = first + position;
        do {
            --position;
            --p;
            ElemC value = *p;
            ElemCAdjustHeap(first, (uint)position, n, position, value, compare);
        } while (position != 0);
    }
    return n;
}

// @ 0x00ba85c0
void ElemCSortHeap(ElemC* first, ElemC* last, bool (*compare)(const ElemC*, const ElemC*))
{
    int n = (int)((char*)last - (char*)first) / 0xc;
    while (n > 1) {
        ElemC* tail = last - 1;
        ElemC value = *tail;
        *tail = *first;
        ElemCAdjustHeap(first, 0, (int)(n - 1), 0, value, compare);
        last = tail;
        n = (int)((char*)last - (char*)first) / 0xc;
    }
}

// @ 0x00ba8650
float* RandomConeDirection(float* out, float spread)
{
    float r1 = DAT_01689c4c * (float)RandomDoubleUniform(&g_sMathRandom);
    float a = (float)RandomDoubleUniform(&g_sMathRandom) * spread * 0.5f;
    float b = r1 * DAT_01471064;

    float sinA = sinf(a);
    float cosA = cosf(a);
    float sinB = sinf(b);
    float cosB = cosf(b);

    float x = DAT_0156c538 * sinB;
    float y = DAT_0156c53c * sinB;
    float z = DAT_0156c540 * sinB;
    float w = sinA * DAT_0156c52c;
    float u = sinA * DAT_0156c530;
    float v = sinA * DAT_0156c534;

    float c0 = z * u - y * v;
    float c1 = x * v - z * w;
    float c2 = y * w - x * u;

    out[0] = (x * cosA + cosB * w) + c0;
    out[1] = (y * cosA + cosB * u) + c1;
    out[2] = (z * cosA + cosB * v) + c2;
    out[3] = cosB * cosA - ((z * v + y * u) + x * w);

    void* r = FUN_0059aed0(&c0, &DAT_0156c538, out);
    float* rr = (float*)r;
    out[0] = rr[0];
    out[1] = rr[1];
    out[2] = rr[2];
    return out;
}

// @ 0x00ba8830
void cStarManager_s00ba_8830::GenerateStarField(void* starPtr)
{
    StarSystem* star = (StarSystem*)starPtr;
    if (FUN_00bb9af0(star, 0, 0x8000))
        star->mnBodyIndex = 0;
    if (star->mnBodyIndex != 0)
        return;

    FUN_00bb9b00(star, 0, 0x100, 0);

    void* nameGen = FUN_004010a0();

    // Body 0: kind 2/5/1 plus the orbit / spin / size setup.
    {
        void* obj = MakeStarBody(this, star, nameGen, 5, 2, 1, true);
        StarBody* body = (StarBody*)obj;

        void* dummy = 0;
        void* m = FUN_00ba8010(this, 0, &dummy, FUN_00989360(star, 0));
        FUN_00b8dde0(body, 0, m, 0);
        body->mb130 = 1;

        void* g = FUN_00f48a80();
        float orbit[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        void* v = FUN_00b8d8e0(body, 0, orbit);
        (*(void (__thiscall**)(void*, void*))((char*)*(void**)g + 8))(g, v);
        body->mfB0 = orbit[3];   // +0xb0
        body->mfB4 = orbit[2];   // +0xb4

        void* r = FUN_00b3d3d0(body, 1);
        FUN_0103ca40(r, 0);

        star->mnBodyIndex++;
        StarBody_Release(obj);
    }

    // Body 1: kind 2/4/1.
    {
        void* obj = MakeStarBody(this, star, nameGen, 2, 4, 1, false);
        FUN_00ba64a0(this, 0, obj, star, 0);
        star->mnBodyIndex++;
        StarBody_Release(obj);
    }

    // Body 2: kind 3/0/1 plus the special satellite descriptor.
    {
        void* obj = MakeStarBody(this, star, nameGen, 3, 0, 1, false);
        FUN_00ba64a0(this, 0, obj, star, 0);
        FUN_00ba6310(this, 0, obj, 0x6334d0ad, 0xaf);
        star->mnBodyIndex++;
        StarBody_Release(obj);
    }

    // Body 3: kind 2/0/1.
    {
        void* obj = MakeStarBody(this, star, nameGen, 2, 0, 1, false);
        FUN_00ba64a0(this, 0, obj, star, 0);
        star->mnBodyIndex++;
        StarBody_Release(obj);
    }

    // Body 4: kind 1/2/0.
    {
        void* obj = MakeStarBody(this, star, nameGen, 1, 2, 0, false);
        FUN_00ba64a0(this, 0, obj, star, 0);
        star->mnBodyIndex++;
        StarBody_Release(obj);
    }
}

// @ 0x00ba8c40
void cStarManager_s00ba_8830::BuildPlanet(void* system, void* out, float p4, float p5, void* p6)
{
    unsigned char* o = (unsigned char*)out;
    *o = 0;

    // Split the requested feature amount between p4 and p5.
    float feat = p5 - p4;
    if (feat > 0.0f) {
        float t = (float)(SP::sMathRandom.RandomDoubleUniform() * (double)feat);
        if (t > feat) t = feat;
        if (t < 0.0f) t = 0.0f;
        float rem = feat - t;
        if (rem > 0.0f) {
            float t2 = (float)(SP::sMathRandom.RandomDoubleUniform() * (double)rem);
            if (t2 >= rem) t2 = rem;
            if (t2 < 0.0f) t2 = 0.0f;
            p4 += t2;
        }
        p5 = p4 + t;
    }

    // Inclination (degrees, clamped) converted to radians.
    float incl = FUN_010431e0(mpProperties, 0x1960001);
    if (incl < 0.0f) incl = 0.0f;
    if (incl > kfMaxInclination) incl = kfMaxInclination;
    incl *= kfDegToRad;

    // Random full turn, then a spin angle uniformly inside [-incl, incl].
    float turn = (float)(SP::sMathRandom.RandomDoubleUniform() * (double)g_RandomTurns);
    float lo = -incl;
    float hi = incl;
    float spin = (float)(SP::sMathRandom.RandomDoubleUniform() * ((double)hi - (double)lo) + (double)lo);
    if (spin >= hi) spin = hi;
    else if (spin < lo) spin = lo;
    float half1 = spin * kfHalf;
    float half2 = turn * kfHalf;

    float s1 = (float)sin((double)half1), c1 = (float)cos((double)half1);
    float s2 = (float)sin((double)half2), c2 = (float)cos((double)half2);

    // q = (axisZ * sin2, cos2) * (axisX * sin1, cos1)
    float x0 = kAxisX[0] * s1, x1 = kAxisX[1] * s1, x2 = kAxisX[2] * s1;
    float z0 = kAxisZ[0] * s2, z1 = kAxisZ[1] * s2, z2 = kAxisZ[2] * s2;
    float q[4];
    q[0] = (c2 * x0 + c1 * z0) + (z1 * x2 - z2 * x1);
    q[1] = (c2 * x1 + c1 * z1) + (z2 * x0 - z0 * x2);
    q[2] = (c2 * x2 + c1 * z2) + (z0 * x1 - z1 * x0);
    q[3] = c2 * c1 - ((z0 * x0 + z2 * x2) + z1 * x1);

    // Surface normal: rotate the Z axis; tangent frame: rotate the X axis.
    float up[3];
    FUN_0059aed0(up, (void*)kAxisZ, q);
    *(float*)(o + 4)  = up[0];
    *(float*)(o + 8)  = up[1];
    *(float*)(o + 12) = up[2];

    float side[3];
    FUN_0059aed0(side, (void*)kAxisX, q);
    float lenSq = (side[0] * side[0] + side[2] * side[2]) + side[1] * side[1];
    float inv = (float)(1.0 / sqrt((double)(lenSq + kfEpsilon)));
    *(float*)(o + 0x14) = (inv * side[0]) * p4;
    *(float*)(o + 0x18) = (inv * side[1]) * p4;
    *(float*)(o + 0x1c) = (inv * side[2]) * p4;

    // Density weight: the smaller of the property and the radius ratio.
    float w1 = FUN_010431e0(mpProperties, 0x1960000);
    if (w1 < 0.0f) w1 = 0.0f;
    if (w1 > kfWeightMax) w1 = kfWeightMax;
    float ratio = (p5 - p4) / (p4 + p5);
    if (ratio < 0.0f) ratio = 0.0f;
    if (ratio > kfWeightMax) ratio = kfWeightMax;
    *(float*)(o + 0x10) = (w1 <= ratio) ? w1 : ratio;

    if (p6 == 0) {
        float mass = FUN_00c841a0(FUN_00801920(system, 0));
        float density = GetPropertyFloat(mpProperties, 0x1960021, kfDensityDefault);
        float dm = density / mass;
        *(float*)(o + 0x20) = (float)sqrt((double)(((p4 * p4) * p4) * (dm * dm) * kfVolumeScaleStar));
    } else {
        int kind = *(int*)((char*)p6 + 0x28);
        uint32_t key = 0x1960020u + (kind != 1 ? 0x3bb977bu : 0u);
        float density = GetPropertyFloat(mpProperties, key, kfDensityGas);
        *(float*)(o + 0x20) = (float)sqrt((double)((density * density) * ((p4 * p4) * p4) * kfVolumeScaleRocky));
    }
    FUN_00fe8450(out, 0);
}

// @ 0x00ba91b0
void FUN_00ba91b0(void* self, void* star)
{
    char* p = (char*)star;
    p[0x98] = 0;
    void* props = *(void**)((char*)self + 0x1a4);

    float f = FUN_010431e0(props, 0x1960010);
    float a = f; if (a <= 0.0f) a = 0.0f; if (a >= 89.0f) a = 89.0f;

    double d = 0.0;
    float* v = (float*)FUN_00ba8650(&d, a * 0.017453292f);
    *(float*)(p + 0x9c) = v[0];
    *(float*)(p + 0xa0) = v[1];
    *(float*)(p + 0xa4) = v[2];

    float g = FUN_010431e0(props, 0x1960011);
    float base = g <= 1.0f ? 1.0f : g;
    float lo = base * 0.9f;
    float hi = base * 1.1f;
    float r = (float)(sMathRandom.RandomDoubleUniform() * (hi - lo) + lo);
    *(float*)(p + 0xa8) = r < hi ? (r < lo ? lo : r) : hi;
}

// @ 0x00ba9370
int cStarManager_s00ba_8830::GetEmpireByID(unsigned int empireID)
{
    if (empireID != 0xffffffffu) {
        RBNode_s00ba_8830* n = mEmpires.find(empireID).mpNode;
        if (n != mEmpires.end().mpNode)
            return (int)n->second;
    }
    return 0;
}

// @ 0x00ba93b0
void* cStarManager_s00ba_8830::GetByFieldID()
{
    uint32_t key = (uint32_t)mEmpireID;
    if (key != 0xffffffffu) {
        RBNode_s00ba_8830* n = mEmpires.find(key).mpNode;
        if (n != mEmpires.end().mpNode)
            return n->second;
    }
    return 0;
}

// @ 0x00ba9400
void FUN_00ba9400(void* p)
{
    WStr* r = ((GetWStrFn)*(void**)((char*)p + 0x20))(p);
    if ((g_initA & 1) == 0) {
        g_initA |= 1;
        g_WStrA.mpBegin = g_emptyWString;
        g_WStrA.mpEnd = g_emptyWString;
        g_WStrA.mpCapacity = g_emptyWString + 1;
        atexit((void (__cdecl*)(void))0x13c2f90);
    }
    if (r != &g_WStrA)
        r->Assign(g_WStrA.mpBegin, g_WStrA.mpEnd);
}

// @ 0x00ba9470
void FUN_00ba9470(void* p)
{
    WStr* r = ((GetWStrFn)*(void**)((char*)p + 0x20))(p);
    if ((g_initB & 1) == 0) {
        g_initB |= 1;
        g_WStrB.mpBegin = g_emptyWString;
        g_WStrB.mpEnd = g_emptyWString;
        g_WStrB.mpCapacity = g_emptyWString + 1;
        atexit((void (__cdecl*)(void))0x13c2f60);
    }
    if (r != &g_WStrB)
        r->Assign(g_WStrB.mpBegin, g_WStrB.mpEnd);
}

// @ 0x00ba94e0
void FUN_00ba94e0(int* writer, int* data)
{
    uint32_t v = *(uint32_t*)((char*)data + 0x14);
    void* s0 = (*(void* (__cdecl**)(int*))((char*)*(void**)writer + 0x20))(writer);
    void* w0 = (*(void* (__cdecl**)(void*))((char*)*(void**)s0 + 0x18))(s0);
    EA_IO_WriteUint32_s00ba_8830(w0, &v, 1, 0);

    int* it = *(int**)((char*)data + 8);
    for (int* end = (int*)((char*)data + 4); it != end;
         it = (int*)RBTreeIncrement_s00ba_8830(it)) {
        v = *(uint32_t*)((char*)it + 0x10);
        void* s1 = (*(void* (__cdecl**)(int*))((char*)*(void**)writer + 0x20))(writer);
        void* w1 = (*(void* (__cdecl**)(void*))((char*)*(void**)s1 + 0x18))(s1);
        EA_IO_WriteUint32_s00ba_8830(w1, &v, 1, 0);
        (*(void (__cdecl**)(int*))((char*)*(void**)writer + 0x1c))(writer);
        uint32_t tag = 0;
        void* val = *(void**)((char*)it + 0x14);
        if (val)
            tag = (*(uint32_t (__cdecl**)(int))((char*)*(void**)val + 0xc))(0x179c807);
        (*(void (__cdecl**)(int*))((char*)*(void**)writer + 0x2c))(writer);
        (void)tag;
    }
    (*(void (__cdecl**)(int*))((char*)*(void**)writer + 0x1c))(writer);
}

// @ 0x00ba95f0
int* FUN_00ba95f0(int* begin, int* end, int* value)
{
    int count = (int)((char*)end - (char*)begin) >> 4;
    while (count > 0) {
        int half = count >> 1;
        int* mid = begin + half * 4;
        if (CompareWStrRec(mid, value) < 0) {
            begin = mid + 4;
            count -= half + 1;
        } else {
            count = half;
        }
    }
    return begin;
}

// @ 0x00ba96e0
int* FUN_00ba96e0(int* first, int* last, int* thresh)
{
    int pivot = *(int*)((char*)thresh + 0x28);
    for (;;) {
        while (RecKey(*(int**)first) < pivot) ++first;
        while (pivot < RecKey(*(int**)(last - 1))) --last;
        if (first >= last) break;
        FUN_00b2af00(first, last - 1);
        ++first;
    }
    RefRelease(thresh);
    return first;
}

// @ 0x00ba9740
void FUN_00ba9740(int* a, int* b, int* c, void* d)
{
    FUN_00ba84b0(a, b, d);
    for (int* p = b; p < c; ++p) {
        int* v = (int*)*p;
        if (*(int*)((char*)v + 0x28) < *(int*)((char*)*a + 0x28)) {
            if (v) ((VCall1)(*(void***)v)[0])(v);
            int* cur = (int*)*a;
            if (cur != v) {
                if (cur) ((VCall1)(*(void***)cur)[0])(cur);
                *p = (int)cur;
                if (v) ((VCall1)(*(void***)v)[1])(v);
            }
            if (v) ((VCall1)(*(void***)v)[0])(v);
            FUN_00ba79a0(a, 0, (int)(b - a) / 4, 0);
            if (v) ((VCall1)(*(void***)v)[1])(v);
        }
    }
    FUN_00ba8500(a, b, d);
}

// @ 0x00ba9810
void SortTriples_Finalize(cSortTriple* pBegin, cSortTriple* pMiddle, cSortTriple* pEnd, char (*pPred)(const cSortTriple*, const cSortTriple*))
{
    FUN_00ba8550(pBegin, pMiddle, (void*)pPred);
    for (cSortTriple* pCur = pMiddle; pCur < pEnd; pCur++) {
        if (pPred(pCur, pBegin)) {
            cSortTriple saved = *pCur;
            *pCur = *pBegin;
            FUN_00ba7a80(pBegin, 0, (int)(pMiddle - pBegin), 0, saved, (void*)pPred);
        }
    }
    FUN_00ba85c0(pBegin, pMiddle, (void*)pPred);
}

// @ 0x00ba98b0
cIntVectorElement** CopyIntVectorRange(cIntVectorElement** ppIter, const cIntVectorElement* pFirst, const cIntVectorElement* pLast, int nUnused, const void* pSource)
{
    *ppIter = (cIntVectorElement*)pSource;
    for (; pFirst != pLast; pFirst++) {
        cIntVector* pDest = (cIntVector*)*ppIter;
        if (pDest) {
            int nCount = (int)((char*)pFirst->mVector.mpEnd - (char*)pFirst->mVector.mpBegin) >> 2;
            int* pData;
            if (nCount != 0) {
                pData = (int*)operator_new((uint32_t)(nCount * 4), gSimulatorName, 0, 0,
                                           gAllocatorFile, 0xd1);
            } else {
                pData = 0;
            }
            int* pNewEnd;
            pDest->mpBegin = pData;
            pDest->mpEnd = pData;
            pDest->mpCapacityEnd = pData + nCount;
            FUN_00829110(&pNewEnd, pFirst->mVector.mpBegin, pFirst->mVector.mpEnd, pData, pSource);
            pDest->mpEnd = pNewEnd;
        }
        *ppIter = (cIntVectorElement*)((char*)*ppIter + 0x14);
    }
    return ppIter;
}

// @ 0x00ba9960
void ConstructIntVectorRange(cIntVectorElement* pDest, uint32_t nCount, const cIntVectorElement* pSource)
{
    if (nCount <= 0) return;
    do {
        if (pDest) {
            int nCount2 = (int)((char*)pSource->mVector.mpEnd - (char*)pSource->mVector.mpBegin) >> 2;
            int* pData;
            if (nCount2 != 0) {
                pData = (int*)operator_new((uint32_t)(nCount2 * 4), gSimulatorName, 0, 0,
                                           gAllocatorFile, 0xd1);
            } else {
                pData = 0;
            }
            int* pNewEnd;
            pDest->mVector.mpBegin = pData;
            pDest->mVector.mpEnd = pData;
            pDest->mVector.mpCapacityEnd = pData + nCount2;
            FUN_00829110(&pNewEnd, pSource->mVector.mpBegin, pSource->mVector.mpEnd, pData,
                         pSource);
            pDest->mVector.mpEnd = pNewEnd;
        }
        --nCount;
        pDest = (cIntVectorElement*)((char*)pDest + 0x14);
    } while (nCount > 0);
}

// @ 0x00ba99f0
bool SaveAreaHasType(IGameSave* pSave, const char* pCommandLine, const char* pFileName, void* pArg)
{
    cWideString cmdLine;
    ParseCommandLine(&cmdLine, pCommandLine);
    if (cmdLine.mpBegin == cmdLine.mpEnd) return true;

    cWideString fileName;
    if (pFileName) {
        ConvertToString16(&fileName, pFileName, -1);
    } else {
        fileName.mpBegin = (wchar_t16*)gEmptyString16;
        fileName.mpEnd = (wchar_t16*)gEmptyString16;
        fileName.mpCapacityEnd = (wchar_t16*)gEmptyString16 + 1;
    }
    cWideString name(fileName);
    delete[] fileName.mpBegin;

    cWideString typedName;
    ConvertToString16(&typedName, &cmdLine);

    bool bMatch;
    if (typedName.mpBegin == typedName.mpEnd) {
        bMatch = pSave->v00((uint32_t)name.mpBegin);
        if (!bMatch) return false;
    } else {
        bMatch = pSave->v00((uint32_t)typedName.mpBegin);
        if (gbTypeCheckEnabled) {
            if (bMatch) {
                bMatch = pSave->v08(gTypeName, pArg);
                if (!bMatch) return false;
            } else {
                return false;
            }
        }
        if (!bMatch) return false;
        bMatch = pSave->v0C(typedName.mpBegin);
        if (!bMatch) return false;
    }
    delete[] typedName.mpBegin;
    delete[] name.mpBegin;
    return pSave->v04((uint32_t)name.mpBegin);
}

// @ 0x00ba9bc0
bool StarManager_HasDatabaseFile()
{
    cWideString namesA;
    cWideString namesB;
    namesA.RangeInitialize(GetSaveArea(0x4729a47)->v28());
    namesB.RangeInitialize(GetSaveArea(0x4729a47)->v28());

    cWideString joined;
    cWideString* pResult = PathJoin(&joined, &namesA, gDbReadInitiated);
    if (pResult != &namesA) namesA.assign(pResult->mpBegin, pResult->mpEnd);
    delete[] joined.mpBegin;

    pResult = PathJoin(&joined, &namesB, gDbReadCompleted);
    if (pResult != &namesB) namesB.assign(pResult->mpBegin, pResult->mpEnd);
    delete[] joined.mpBegin;

    if (!FileExists(namesA.mpBegin)) {
        delete[] namesB.mpBegin;
        delete[] namesA.mpBegin;
        return true;
    }
    bool bHasCompleted = FileExists(namesB.mpBegin);
    delete[] namesB.mpBegin;
    delete[] namesA.mpBegin;
    return bHasCompleted;
}

// @ 0x00ba9d60
bool LoadDatabaseFromSave(IGameSave* pSave, uint32_t nVerbose)
{
    cSortTriple key;
    key.mX = 1.0f;
    key.mY = 1.0f;
    key.mZ = 0x3f800000u;

    if (!pSave->v08(gEmptyString16, (void*)nVerbose)) return false;

    ISaveStream* pStream = (ISaveStream*)pSave->v24();
    uint32_t nSize = (uint32_t)pStream->v1C();
    void* pBuffer = OfflineAlloc((int)nSize, gSimulatorName, 0, 0, 0, 0);
    uint32_t nRead = 0;
    pStream->v30(&nRead, 1);
    pStream->v30(pBuffer, pStream->v1C());

    cMemoryStream* pMemory = ConstructMemoryStream(0x18);
    if (pMemory) pMemory->v04();
    pMemory->SetData(pBuffer, pStream->v1C());
    pMemory->v28(0, 0);

    IPackedDatabase* pDatabase = ConstructDatabasePackedFile(0, 0);
    if (pDatabase) pDatabase->v04();
    pDatabase->v50(pMemory);
    pDatabase->v04();
    if (!pDatabase->v18(1, 6, 0)) {
        bool bResult = false;
        pDatabase->v08();
        return bResult;
    }
    cIntVectorElement* pFound = 0;
    pDatabase->v30(&pFound, 0);
    pDatabase->v1C();
    delete[] (int*)pFound;
    pDatabase->v08();
    return true;
}

// @ 0x00ba9f80
bool cStarPickState::HasKey(const cSortTriple* pKey)
{
    uint32_t nCount = (uint32_t)((char*)mpObjectsEnd - (char*)mpObjects) >> 2;
    for (uint32_t i = 0; i < nCount; i++) {
        void* pObject = mpObjects[i];
        const cSortTriple* pObjectKey = FUN_00bb9b80(pObject);
        if (pKey->mX == pObjectKey->mX && pKey->mY == pObjectKey->mY &&
            pKey->mZ == pObjectKey->mZ) {
            return true;
        }
        if (FUN_00bb9ae0(pObject) != 5) continue;
        uint32_t nAvatarKey = (uint32_t)GetAvatar(pObject);
        if ((int)nAvatarKey >= 0) continue;
        if (nAvatarKey == 0xffffffff) continue;
        mEmpiresByKey.Find(&nAvatarKey, nAvatarKey);
        cFeedbackNode* pNode = (cFeedbackNode*)nAvatarKey;
        if (pNode == (cFeedbackNode*)&mEmpiresByKey.mHead) continue;
        void* pEmpire = pNode->mpValue;
        if (!pEmpire) continue;
        const cSortTriple* pUFOKey = GetUFOKey(pEmpire);
        if (pKey->mX == pUFOKey->mX && pKey->mY == pUFOKey->mY && pKey->mZ == pUFOKey->mZ)
            return true;
        if (EmpireHasKey(pEmpire, pKey)) return true;
    }
    return false;
}

// @ 0x00baa110
int cFeedbackTree::EraseKey(uint32_t nKey)
{
    Find(&nKey, nKey);
    void* pNode = (void*)nKey;
    if (pNode != (void*)&mHead) {
        --mnSize;
        RBTreeIncrement(pNode);
        RBTreeErase(pNode, &mHead);
        void* pValue = ((cFeedbackNode*)pNode)->mpValue;
        if (pValue) {
            typedef void (__thiscall *release_fn)(void*);
            void** pVtable = *(void***)pValue;
            ((release_fn)pVtable[1])(pValue);
        }
        delete[] (cFeedbackNode*)pNode;
        return true;
    }
    return false;
}

// @ 0x00baa2b0
bool FeedbackTree_VisitRuns(IResourceKeyVisitor* pVisitor, const char* pName, cFeedbackTree* pTree)
{
    bool bResult = true;
    if (pTree->mnSize == 0) return bResult;

    cWideString name;
    if (pName) {
        ConvertToString16(&name, pName, -1);
    } else {
        name.mpBegin = 0;
        name.mpEnd = 0;
        name.mpCapacityEnd = 0;
        name.RangeInitialize(0);
    }
    cWideString displayName(name);
    FreeWideString(name);

    const wchar_t16* pDisplay = displayName.mpBegin;
    if (displayName.mpBegin == displayName.mpEnd) pDisplay = gUnknownString;
    pVisitor->v00(pDisplay);

    for (cFeedbackNode* pNode = (cFeedbackNode*)pTree->mHead.mpRight;
         pNode != (cFeedbackNode*)&pTree->mHead;
         pNode = (cFeedbackNode*)RBTreeIncrement(pNode)) {
        if (bResult) bResult = FUN_00ac8050_s00ba_9810(pVisitor, 0, &pNode->mpValue);
    }

    pDisplay = displayName.mpBegin;
    if (displayName.mpBegin == displayName.mpEnd) pDisplay = gUnknownString;
    pVisitor->v04(pDisplay);
    FreeWideString(displayName);
    return bResult;
}

// @ 0x00baa410
void cRunInfoVector::Insert(cRunInfo* pPosition, const cRunInfo* pValue)
{
    cRunInfo* pEnd = mpEnd;
    if (pEnd != mpCapacityEnd) {
        if (pPosition <= pValue && pValue < pEnd)
            pValue = (const cRunInfo*)((const char*)pValue + 0x10);
        if (pEnd) {
            pEnd->mX = (pEnd - 1)->mX;
            pEnd->mY = (pEnd - 1)->mY;
            pEnd->mZ = (pEnd - 1)->mZ;
            pEnd->mExtra = (pEnd - 1)->mExtra;
        }
        FUN_00edba80(pPosition, mpEnd - 1, mpEnd);
        *pPosition = *pValue;
        mpEnd++;
        return;
    }
    uint32_t nCount = (uint32_t)((char*)pEnd - (char*)mpBegin) >> 4;
    int nCapacity = nCount > 0 ? (int)(nCount * 2) : 1;
    cRunInfo* pNew = nCapacity ? (cRunInfo*)operator_new((uint32_t)(nCapacity * 0x10),
                                                        gSimulatorName, 0, 0, gAllocatorFile, 0xd1)
                               : 0;
    cRunInfo* pSlot = (cRunInfo*)FUN_00ba7920(mpBegin, pPosition, pNew);
    if (pSlot) {
        pSlot->mX = pValue->mX;
        pSlot->mY = pValue->mY;
        pSlot->mZ = pValue->mZ;
        pSlot->mExtra = pValue->mExtra;
    }
    cRunInfo* pNewEnd = (cRunInfo*)FUN_00ba7920(pPosition, mpEnd, pSlot + 1);
    if (mpBegin && ((int*)mpBegin)[-1] != 0) operator_delete_array(mpBegin);
    mpEnd = pNewEnd;
    mpCapacityEnd = (cRunInfo*)((char*)pNew + (uint32_t)nCapacity * 0x10);
    mpBegin = pNew;
}

// @ 0x00baa530
void cTripleVector::Insert(cSortTriple* pPosition, const cSortTriple* pValue)
{
    cSortTriple* pEnd = mpEnd;
    if (pEnd != mpCapacityEnd) {
        if (pPosition <= pValue && pValue < pEnd)
            pValue = (const cSortTriple*)((const char*)pValue + 0xc);
        if (pEnd) {
            pEnd->mX = (pEnd - 1)->mX;
            pEnd->mY = (pEnd - 1)->mY;
            pEnd->mZ = (pEnd - 1)->mZ;
        }
        for (cSortTriple* pCur = mpEnd - 1; pCur != pPosition; pCur--)
            pCur[0] = pCur[-1];
        *pPosition = *pValue;
        mpEnd++;
        return;
    }
    int nCount = (int)((char*)pEnd - (char*)mpBegin) / 0xc;
    int nCapacity = nCount > 0 ? nCount * 2 : 1;
    cSortTriple* pNew = nCapacity ? (cSortTriple*)operator_new((uint32_t)(nCapacity * 0xc),
                                                              gSimulatorName, 0, 0, gAllocatorFile, 0xd1)
                                  : 0;
    cSortTriple* pSlot = (cSortTriple*)FUN_00ba7960(mpBegin, pPosition, pNew);
    if (pSlot) {
        pSlot->mX = pValue->mX;
        pSlot->mY = pValue->mY;
        pSlot->mZ = pValue->mZ;
    }
    cSortTriple* pNewEnd = (cSortTriple*)FUN_00ba7960(pPosition, mpEnd, pSlot + 1);
    if (mpBegin && ((int*)mpBegin)[-1] != 0) operator_delete_array(mpBegin);
    mpBegin = pNew;
    mpEnd = pNewEnd;
    mpCapacityEnd = (cSortTriple*)((char*)pNew + (uint32_t)nCapacity * 0xc);
}
