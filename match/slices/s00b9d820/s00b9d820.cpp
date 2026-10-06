// Slice s00b9d820: FUN_00b9d820, civilization-stage city setup (~8.6 KB, __cdecl, no args).
//
// Runs the Arithmetica program 0x18657795 (water_fraction -> num_cities,
// num_npc_cities_on_player_continent, population/wealth ranges), turns the planet's
// city-site nouns (0x36be27e with definition 0x91fe517b) into new city nouns, picks the
// player's capital site, distributes the remaining NPC cities over the continents, fills
// SimSingleton's city-info vector, places the city models / terrain, and finally spawns
// the start effects.
//
// PDB name candidates (SP::cTerrainSphere::RequestModelFootprint / SP::TrySueForPeace)
// do not fit the body; the function is left unnamed.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (movss/cvttss2si; no EH frame although
// cArithmeticaProgram has a dtor, so no /EHsc).
#include "types.h"

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }
// EA operator new (0x00f473a0): (size, name, flags, debugFlags, file, line)
void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);                                     // 0x00f47380
extern "C" void* __cdecl memmove(void* dst, const void* src, size_t n); // 0x011e0744 thunk

// ---------------------------------------------------------------------------------------
// Math
struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
struct Matrix3 { float m[3][3]; };

extern Vector3 g_ZeroVector;        // 0x01688890  (Vector3::ZERO)
extern Matrix3 g_IdentityMatrix3;   // 0x01688924  (Matrix3::IDENTITY)

__forceinline void QuaternionToMatrix(Matrix3& m, const Quaternion& q)
{
    float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
    float xy = q.y * q.x, xz = q.z * q.x, yz = q.z * q.y;
    float wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;
    m.m[0][0] = 1.0f - (zz + yy) * 2.0f;
    m.m[0][1] = (wz + xy) * 2.0f;
    m.m[0][2] = (xz - wy) * 2.0f;
    m.m[1][0] = (xy - wz) * 2.0f;
    m.m[1][1] = 1.0f - (zz + xx) * 2.0f;
    m.m[1][2] = (wx + yz) * 2.0f;
    m.m[2][0] = (wy + xz) * 2.0f;
    m.m[2][1] = (yz - wx) * 2.0f;
    m.m[2][2] = 1.0f - (yy + xx) * 2.0f;
}

struct cSPTransform {
    uint16_t mFlags;              // +0x0
    uint16_t mModificationCount;  // +0x2
    Vector3  mTranslation;        // +0x4
    float    mScale;              // +0x10
    Matrix3  mRotation;           // +0x14

    __forceinline cSPTransform() : mFlags(0), mModificationCount(0), mTranslation(g_ZeroVector),
                     mScale(1.0f), mRotation(g_IdentityMatrix3) {}
    __forceinline void SetTranslation(const Vector3& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
    __forceinline void SetRotation(const Quaternion& q)
    {
        Matrix3 m;
        QuaternionToMatrix(m, q);
        mRotation = m;
        mFlags |= 2;
        mModificationCount++;
    }
    cSPTransform& operator=(const cSPTransform& x);  // 0x00537dc0
};

struct ResourceKey { uint32_t instanceID, typeID, groupID; };

// ---------------------------------------------------------------------------------------
// Ref-counted pointer (EA::AutoRefCount / intrusive_ptr): AddRef = slot 0, Release = slot 1.
template<class T> struct RefPtr {
    T* mp;
    __forceinline RefPtr() : mp(0) {}
    __forceinline ~RefPtr() { if (mp) mp->Release(); }
    __forceinline RefPtr& operator=(T* p)
    {
        if (p != mp) {
            if (p) p->AddRef();
            T* old = mp;
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
    __forceinline void reset() { if (mp) { T* t = mp; mp = 0; t->Release(); } }
    __forceinline T* get() const { return mp; }
    __forceinline T* operator->() const { return mp; }
    __forceinline operator bool() const { return mp != 0; }
};

// ---------------------------------------------------------------------------------------
// Properties
struct Property {
    void*    mpData;   // +0x0  (array/pointer storage when mnFlags & 0x30)
    uint32_t pad04;
    int      mnCount;  // +0x8
    uint32_t pad0c;
    uint16_t mnFlags;  // +0x10
    uint16_t mnType;   // +0x12  (0xd = float)
};

__forceinline int PropertyItemCount(const Property* p)
{
    return (p->mnFlags & 0x30) ? p->mnCount : (p->mnType != 0);
}
__forceinline const void* PropertyItems(const Property* p)
{
    return (p->mnFlags & 0x30) ? p->mpData : (p->mnType ? p : 0);
}

class PropertyList {
public:
    virtual int  AddRef();
    virtual int  Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasProperty(uint32_t id);                       // 0x1c
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& out);       // 0x24
    virtual Property* GetPropertyObject(uint32_t id);            // 0x28
};
typedef RefPtr<PropertyList> PropertyListPtr;

__forceinline bool GetPropertyFloat(PropertyList* list, uint32_t id, float& value)
{
    Property* p;
    if (list->GetProperty(id, p) && p->mnType == 0xd) {
        value = *(float*)((p->mnFlags & 0x30) ? p->mpData : p);
        return true;
    }
    return false;
}

class IPropManager {
public:
    virtual int  AddRef();
    virtual int  Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst);  // 0x2c
};

__forceinline bool GetPropList(IPropManager* pm, uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst)
{
    dst.reset();
    return pm->GetPropertyList(instanceID, groupID, dst);
}

class cDirectPropertyList {
public:
    int GetIntProperty(uint32_t id);   // 0x006a2660
};

bool GetPropertyAsKey(PropertyList* list, uint32_t id, ResourceKey& out);   // 0x006a1250

// ---------------------------------------------------------------------------------------
// Game data
class ILocator {   // cGameData + 0x34
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3*    GetPosition();                       // 0x2c
    virtual const Quaternion* GetOrientation();                    // 0x30
    virtual void v34();
    virtual void SetPosition(const Vector3& v);                    // 0x38
    virtual void SetOrientation(const Quaternion& q);              // 0x3c
};

class cGameData {
public:
    virtual int   AddRef();
    virtual int   Release();
    virtual void  v08();
    virtual void* Cast(uint32_t typeID);   // 0x0c

    uint32_t pad04[8];
    int      mPoliticalID;     // +0x24
    uint32_t pad28[3];
    ILocator mLocator;         // +0x34
    uint32_t pad38[0x34];
    uint32_t mDefinitionID;    // +0x108
    uint32_t mNounID;          // +0x10c
    uint32_t mSubType;         // +0x110
    uint32_t mField114;        // +0x114

    void FUN_00c6ace0(int a);  // 0x00c6ace0
    void FUN_00c6b540();       // 0x00c6b540
};

struct GDIter {
    cGameData** mp;
    __forceinline GDIter(cGameData** p) : mp(p) {}
    __forceinline GDIter(const GDIter& x) : mp(x.mp) {}
};
struct false_type {};
// eastl::uninitialized_copy_impl<AutoRefCount<cGameData>> (AddRefs each element)
GDIter FUN_00829110(GDIter first, GDIter last, GDIter dest, false_type);

// eastl::vector<AutoRefCount<cGameData>, sp_vector_allocator("Simulator")>
struct GameDataPtrVector {
    cGameData** mpBegin;
    cGameData** mpEnd;
    cGameData** mpCapacity;
    const char* mpAllocName;

    __forceinline GameDataPtrVector(const GameDataPtrVector& x)
    {
        int n = (int)(x.mpEnd - x.mpBegin);
        mpBegin = n ? (cGameData**)operator new(n * sizeof(cGameData*), "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1) : 0;
        mpEnd = FUN_00829110(GDIter(x.mpBegin), GDIter(x.mpEnd), GDIter(mpBegin), false_type()).mp;
        mpCapacity = mpBegin + n;
    }
    __forceinline ~GameDataPtrVector()
    {
        for (cGameData** p = mpBegin; p < mpEnd; ++p)
            if (*p) (*p)->Release();
        if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin);
    }
};

struct tGameDataVector {
    bool              mbDirty;   // +0x0
    GameDataPtrVector mData;     // +0x4
};

// Fixed-capacity vector with inline storage (fixed_vector + sp allocator): the word before
// the inline buffer is 0, a heap block has a non-zero header there.
template<class T, int N> struct FixedVector {
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator[2];
    int      mBufferHeader;
    T        mBuffer[N];

    __forceinline FixedVector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + N), mBufferHeader(0) {}
    __forceinline ~FixedVector() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin); }

    __forceinline uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void DoInsertValue(T* pos, const T& value);   // out of line
    __forceinline void push_back(const T& value)
    {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            if (p) *p = value;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
    __forceinline T* erase(T* p)
    {
        if (p + 1 < mpEnd) memmove(p, p + 1, (char*)mpEnd - (char*)(p + 1));
        --mpEnd;
        return p;
    }
    __forceinline T* erase(T* first, T* last)
    {
        memmove(first, last, (char*)mpEnd - (char*)last);
        mpEnd = mpEnd - (last - first);
        return first;
    }
};

typedef FixedVector<cGameData*, 32> CityVector;     // DoInsertValue = 0x00b96600

struct ContinentInfo {
    int continent;   // +0x0
    int area;        // +0x4  (cPlanetModel FUN_00b7ea00)
    int numCities;   // +0x8
};

// ---------------------------------------------------------------------------------------
// Managers
class cTribe {
public:
    uint32_t pad00[0x48];
    ILocator mLocator;              // +0x120
    void FUN_00c8e490();            // 0x00c8e490
    void FUN_00c8eb50(Vector3* v);  // 0x00c8eb50
};

struct cTerrainInfo {
    uint32_t pad[0x441];
    uint32_t mPlanetType;    // +0x1104
    uint32_t pad1108[0x1b];
    int      mTerrainKind;   // +0x1174
    int FUN_00c75420();      // 0x00c75420
};

class cGameNounManager {
public:
    tGameDataVector* GetGameDataVector(void* create, void* f2, void* filter, void* f4, uint32_t typeID); // 0x00b21340
    cTribe*       GetPlayerTribe();             // 0x00bfc5f0
    cGameData*    CreateNoun(uint32_t typeID);  // 0x00b20c60
    cTerrainInfo* FUN_00f67d90();               // 0x00f67d90
    int           GetPlayerEmpireOrMinus1();    // 0x00b1f9d0
};

class cPlanetModelRenderer {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50();
    virtual int  CreateModel(const cSPTransform& transform, PropertyList* list);   // 0x54
};

class cPlanetModel {
public:
    uint32_t pad00[9];
    cPlanetModelRenderer* mpRenderer;   // +0x24

    float      FUN_00b7ec50();                                         // water fraction
    int        GetContinent(const Vector3& pos);                       // 0x00b88590
    int        FUN_00b7ea00(int continent);                            // continent area
    bool       FindClosestWater(const Vector3& pos, float radius, Vector3* out);         // 0x00b8bb70
    Quaternion BuildSurfaceOrientation(const Vector3& pos);                              // 0x00b7f190
    Quaternion BuildSurfaceOrientation(const Vector3& pos, const Vector3& dir);          // 0x00b7f250
    Vector3    DirectionToSurfacePosition(const Vector3& dir);                           // 0x00b815a0
};

class cTerraformingManager {
public:
    void FUN_00bbf730(const Vector3* pos, float radius);   // 0x00bbf730
};

#define VPAD4(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3();
struct cCityModel;
class cModelWorld {   // cCityModel::mpOwner
public:
    VPAD4(a) VPAD4(b) VPAD4(c) VPAD4(d) VPAD4(e) VPAD4(f) VPAD4(g) VPAD4(h)
    VPAD4(i) VPAD4(j) VPAD4(k) VPAD4(l) VPAD4(m) VPAD4(n) VPAD4(o) VPAD4(p)
    VPAD4(q) VPAD4(r) VPAD4(s) VPAD4(t) VPAD4(u) VPAD4(v) VPAD4(w)
    virtual void UpdateModel(cCityModel* model, bool flag);   // 0x170
};

struct cCityModel {
    cModelWorld* mpOwner;        // +0x0
    uint32_t     mFlags;         // +0x4
    cSPTransform mTransform;     // +0x8
    int          mUpdateCount;   // +0x40
};

struct cCivState {           // FUN_00cf74c0()
    uint8_t  pad00[0x29];
    bool     mbFlag29;       // +0x29
    uint8_t  pad2a[0xda];
    cCityModel* mpModel;     // +0x104
    void FUN_00cf8920(const Vector3* pos);   // 0x00cf8920
    void FUN_00cf8ba0(int continent);        // 0x00cf8ba0
};

struct CityObject {          // FUN_00b99ed0 result
    uint32_t pad[0xba];
    int      mModelID;       // +0x2e8
    struct Sub { uint32_t pad[0x2f]; int mBC; int mC0; }* FUN_00bd81f0();   // 0x00bd81f0
};

struct CityInfo {            // 0x64 bytes, SimSingleton city table entry
    int         mPoliticalID;   // +0x0
    Vector3     mPosition;      // +0x4
    Quaternion  mOrientation;   // +0x10
    int         mContinent;     // +0x20
    bool        mbPlaced;       // +0x24
    bool        mb25;           // +0x25
    uint8_t     pad26[2];
    int         mTerrainKind;   // +0x28
    uint32_t    pad2c;
    bool        mb30;           // +0x30
    bool        mbNearWater;    // +0x31
    uint8_t     pad32[2];
    int         mStyle;         // +0x34
    uint32_t    pad38;
    int         mEmpireID;      // +0x3c
    uint32_t    pad40;
    uint32_t    mField44;       // +0x44
    ResourceKey mModelKey;      // +0x48
    ResourceKey mModelKey2;     // +0x54
    uint32_t    pad60;

    CityInfo();                         // 0x00ae4230
    ~CityInfo();                        // 0x00ae42a0
    void FUN_00ae38f0(cTribe* tribe);   // 0x00ae38f0
};

struct CityInfoVector {
    CityInfo* mpBegin;
    CityInfo* mpEnd;
    CityInfo* mpCapacity;

    __forceinline int size() const { return (int)(mpEnd - mpBegin); }
    CityInfo* erase(CityInfo* first, CityInfo* last);           // 0x00ae5d10
    void DoInsertValue(CityInfo* pos, const CityInfo& value);   // 0x00ae5d60
    __forceinline void clear() { erase(mpBegin, mpEnd); }
    __forceinline void push_back()
    {
        if (mpEnd < mpCapacity) {
            CityInfo* p = mpEnd++;
            if (p) new(p) CityInfo();
        } else {
            DoInsertValue(mpEnd, CityInfo());
        }
    }
    __forceinline CityInfo& back() { return mpEnd[-1]; }
};

namespace Simulator {
class SimSingleton {
public:
    uint32_t       pad00[5];
    CityInfoVector mCities;        // +0x14
    uint32_t       pad20[0x23];
    int            mNumPlacedCities;   // +0xac
    int            mLastCityIndex;     // +0xb0

    SimSingleton();   // 0x00ae5c30
    struct Spawned { uint32_t pad[0xd]; CityObject* mpCity; }*
        FUN_00ae49d0(void* callback, int empire, const Vector3* pos, int kind, uint32_t typeID,
                     CityInfo* info, const Quaternion* orient, int flag);   // 0x00ae49d0
    void FUN_00ae34b0(const Vector3* pos);                                  // 0x00ae34b0

    static SimSingleton* sInstance;   // 0x0167a60c
    __forceinline static SimSingleton* Get()
    {
        if (!sInstance) sInstance = new("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
        return sInstance;
    }
};
}
using Simulator::SimSingleton;

class RandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t limit);   // 0x00a68fb0
};
extern RandomLinearCongruential g_CityRandom;   // 0x016888e8
extern RandomLinearCongruential g_Random;       // 0x01601760

class cArithmeticaProgram {
public:
    uint32_t pad[0x2b];
    cArithmeticaProgram();    // 0x007f1e60
    ~cArithmeticaProgram();   // 0x007f1d90
    void  SetVar(const char* name, float value);   // VarMap::SetVar 0x007f25c0
    void  Run();                                   // 0x007f2500
    float GetVar(const char* name);                // VarMap::GetVar 0x007f2590
};
void LoadArithmeticaFile(uint32_t instanceID, uint32_t groupID, cArithmeticaProgram* program);   // 0x007f2240

struct cCityEffectHost { void FUN_00b13bb0(const Vector3* pos, int a); };   // 0x00b13bb0

struct cEditorList { uint32_t pad[0x1c]; struct Node { Node* mpNext; Node* mpPrev; } mList; };   // +0x70

// ---------------------------------------------------------------------------------------
// Globals
extern int   g_PopulationMin;   // 0x01688888
extern int   g_PopulationMax;   // 0x01688884
extern float g_WealthMin;       // 0x01688880
extern float g_WealthMax;       // 0x0168887c
extern int   g_PlanetGridSize;  // 0x0156c084
extern cDirectPropertyList* g_DebugProperties;   // 0x015fd918
extern cEditorList*         g_015fd928;          // 0x015fd928

// ---------------------------------------------------------------------------------------
// Callees
cGameNounManager*     NounManager();          // 0x00b3d300
IPropManager*         PropertyManager();      // 0x0067de30
cPlanetModel*         PlanetModel();          // 0x00b3d350
cTerraformingManager* TerraformingManager();  // 0x00b3d430
cCivState*            FUN_00cf74c0();
cCityEffectHost*      FUN_00b3d280();
void        FUN_00bfb8f0();
void        FUN_00b992c0();
void        FUN_00b99760();
void        FUN_00b9d6d0(const Vector3* pos, PropertyList* list);
void        FUN_00b9a8d0(cGameData* city, bool npc);
void        FUN_00b931c0(cGameData* noun, int a, int b);              // "LoadScenario"
CityObject* FUN_00b99ed0(CityInfo* info, const Vector3* pos, const Quaternion* orient);
float       FUN_00b93dc0(uint32_t typeID, int kind);
void        FUN_00b932a0(Vector3* pos, Quaternion* orient, float offset);
int         FUN_00bef920(int terrainKind);
uint32_t    FUN_00bebc90(int a, int style);
uint32_t    FUN_00bebd00(int kind);
Vector3     FUN_00bd8750(const Vector3& pos);
cGameData*  FUN_00b993c0(int politicalID);
void        FUN_00b9b090(const Vector3* pos, const uint32_t* ids, int count, int a, int b);
void        FUN_00b9aa10(const Vector3* pos, const uint32_t* ids, int count, uint32_t groupID);
void        FUN_00b99530(int a, const uint32_t* ids, int count);
void        FUN_00b94150(const Vector3* pos, uint32_t variant, int a, int b);
void        FUN_00afb8a0(cGameData** first, cGameData** last, RandomLinearCongruential* rng);   // random_shuffle
void        FUN_00b90c50();   // city spawn callback

// GetGameDataVector callbacks
void FUN_00cd7d10();
void FUN_00d3d420();
void FUN_00ace070();
void FUN_00acdff0();
void FUN_00accc30();
void FUN_00b1e500();

// remove_if predicates (find_if / remove_copy_if are out-of-line template instances)
struct NotOnContinent {   // keeps cities on one continent
    int mContinent;
    __forceinline bool operator()(cGameData* city) const
    {
        return mContinent != PlanetModel()->GetContinent(*city->mLocator.GetPosition());
    }
};
struct NotNearWater {     // keeps cities within 70 of water
    __forceinline bool operator()(cGameData* city) const
    {
        Vector3 water;
        return !PlanetModel()->FindClosestWater(*city->mLocator.GetPosition(), 70.0f, &water);
    }
};
cGameData** FUN_00b909a0(cGameData** first, cGameData** last, cGameData** dest, NotOnContinent pred); // remove_copy_if
cGameData** FUN_00b93ba0(cGameData** first, cGameData** last, NotNearWater pred);                     // find_if
cGameData** FUN_00b93bf0(cGameData** first, cGameData** last, cGameData** dest, NotNearWater pred);   // remove_copy_if

__forceinline cGameData** RemoveIf(cGameData** first, cGameData** last, NotOnContinent pred)
{
    for (; first != last; ++first)
        if (pred(*first)) break;
    if (first != last) {
        cGameData** i = first;
        return FUN_00b909a0(++i, last, first, pred);
    }
    return first;
}
__forceinline cGameData** RemoveIf(cGameData** first, cGameData** last, NotNearWater pred)
{
    first = FUN_00b93ba0(first, last, pred);
    if (first != last) {
        cGameData** i = first;
        return FUN_00b93bf0(++i, last, first, pred);
    }
    return first;
}

// Cube-face grid coordinates of a direction; the original computes and discards them.
__forceinline void CubeFaceCoords(const Vector3& p, float half, int& u, int& v)
{
    float ax = p.x < 0 ? -p.x : p.x;
    float ay = p.y < 0 ? -p.y : p.y;
    float az = p.z < 0 ? -p.z : p.z;
    if (az >= ax && az >= ay) {
        u = (int)((p.x / p.z + 1.0f) * half);
        v = (int)((p.y / az + 1.0f) * half);
    } else if (ay >= ax) {
        u = (int)((p.z / p.y + 1.0f) * half);
        v = (int)((p.x / ay + 1.0f) * half);
    } else {
        u = (int)((p.y / p.x + 1.0f) * half);
        v = (int)((p.z / ax + 1.0f) * half);
    }
}

static const uint32_t kCitySiteNoun    = 0x036be27e;
static const uint32_t kCitySiteDef     = 0x91fe517b;
static const uint32_t kPlayerSite      = 0xd8c67022;
static const uint32_t kNpcSite         = 0xaed08dd4;

// @ 0x00b9d820
void FUN_00b9d820(void)
{
    cGameNounManager* nm = NounManager();
    IPropManager* pm = PropertyManager();
    FUN_00bfb8f0();
    SimSingleton::Get()->mCities.clear();

    cArithmeticaProgram program;
    LoadArithmeticaFile(0x18657795, 0x024a4f5a, &program);
    cPlanetModel* planet = PlanetModel();
    program.SetVar("water_fraction", planet->FUN_00b7ec50());
    program.Run();
    int numCities    = (int)program.GetVar("num_cities");
    int numNpcCities = (int)program.GetVar("num_npc_cities_on_player_continent");
    g_PopulationMin  = (int)program.GetVar("population_min");
    g_PopulationMax  = (int)program.GetVar("population_max");
    g_WealthMin      = program.GetVar("wealth_min");
    g_WealthMax      = program.GetVar("wealth_max");

    bool fromTribe = FUN_00cf74c0()->mbFlag29;
    FUN_00b992c0();

    PropertyListPtr capitalEffects;
    PropertyListPtr cityEffects;
    pm->GetPropertyList(0xd90671c3, 0x0302a1c9, capitalEffects);
    GetPropList(pm, 0x5e1cef75, 0x0302a1c9, cityEffects);

    CityVector cities;            // new city nouns that may become the capital
    CityVector npcCandidates;     // all new city nouns
    FixedVector<Vector3, 32> sitePositions;
    Vector3 capitalPos = g_ZeroVector;
    int playerContinent = -1;
    RefPtr<cGameData> closestSite;

    if (fromTribe) {
        // Capital goes where the player's tribe was: find the nearest city site.
        capitalPos = *NounManager()->GetPlayerTribe()->mLocator.GetPosition();
        playerContinent = planet->GetContinent(capitalPos);
        FUN_00b9d6d0(&capitalPos, capitalEffects.get());
        NounManager()->GetPlayerTribe()->FUN_00c8e490();
        float bestDist = 3.402823466e+38F;
        tGameDataVector* sites = nm->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                       (void*)FUN_00ace070, (void*)FUN_00b1e500, kCitySiteNoun);
        for (cGameData** it = sites->mData.mpBegin; it != sites->mData.mpEnd; ++it) {
            cGameData* site = *it;
            if (site->mDefinitionID == kCitySiteDef &&
                (site->mSubType == kPlayerSite || site->mSubType == kNpcSite)) {
                const Vector3* p = site->mLocator.GetPosition();
                float dx = p->x - capitalPos.x;
                float dy = p->y - capitalPos.y;
                float dz = p->z - capitalPos.z;
                float d = dz * dz + dy * dy + dx * dx;
                if (d < bestDist) {
                    bestDist = d;
                    closestSite = site;
                }
            }
        }
    }

    {
        GameDataPtrVector sites(nm->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                      (void*)FUN_00ace070, (void*)FUN_00b1e500, kCitySiteNoun)->mData);
        for (cGameData** it = sites.mpBegin; it != sites.mpEnd; ++it) {
            cGameData* site = *it;
            if (site->mDefinitionID == kCitySiteDef &&
                (site->mSubType == kPlayerSite || site->mSubType == kNpcSite)) {
                if (site != closestSite.get()) {
                    ILocator* loc = &site->mLocator;
                    const Vector3& p = *loc->GetPosition();
                    float half = (float)g_PlanetGridSize * 0.5f;
                    int u, v;
                    CubeFaceCoords(p, half, u, v);
                    (void)u; (void)v;

                    const Quaternion* orient = loc->GetOrientation();
                    const Vector3* pos = loc->GetPosition();
                    cGameData* noun = NounManager()->CreateNoun(kCitySiteNoun);
                    cGameData* city = noun ? (cGameData*)noun->Cast(0x036be278) : 0;
                    city->mDefinitionID = 0;
                    city->mField114 = 0;
                    city->mNounID = kCitySiteNoun;
                    city->mSubType = 0xd18d25cd;
                    city->mLocator.SetPosition(*pos);
                    city->mLocator.SetOrientation(*orient);
                    city->mDefinitionID = 0xd18d25cd;
                    FUN_00b931c0(city, -1, -1);
                    cities.push_back(city);
                    npcCandidates.push_back(city);
                    if (site->mSubType == kPlayerSite)
                        playerContinent = planet->GetContinent(*site->mLocator.GetPosition());
                }
                sitePositions.push_back(*site->mLocator.GetPosition());
            }
        }
    }

    nm->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00acdff0,
                          (void*)FUN_00b1e500, 0x018c43e8);

    // Pick the capital.
    cGameData* capital = 0;
    if (!fromTribe) {
        NotOnContinent onContinent;
        onContinent.mContinent = playerContinent;
        cities.erase(RemoveIf(cities.mpBegin, cities.mpEnd, onContinent), cities.mpEnd);
        if (NounManager()->FUN_00f67d90()->FUN_00c75420() <= 0)
            cities.erase(RemoveIf(cities.mpBegin, cities.mpEnd, NotNearWater()), cities.mpEnd);

        int index = g_DebugProperties->GetIntProperty(0x0508662a);
        if (index < 0 || index >= (int)cities.size())
            index = g_CityRandom.RandomUint32Uniform(cities.size());
        capital = cities.mpBegin[index];
        capitalPos = *capital->mLocator.GetPosition();
        playerContinent = planet->GetContinent(capitalPos);
        FUN_00b9d6d0(&capitalPos, capitalEffects.get());
        for (uint32_t i = 0; i < npcCandidates.size(); ++i) {
            if (npcCandidates.mpBegin[i] == capital) {
                npcCandidates.mpBegin[i] = npcCandidates.mpBegin[npcCandidates.size() - 1];
                npcCandidates.mpEnd--;
                break;
            }
        }
    }

    // City table entry for the capital.
    SimSingleton::Get()->mCities.push_back();
    CityInfo& capitalInfo = SimSingleton::Get()->mCities.back();
    capitalInfo.mPoliticalID = fromTribe ? -1 : capital->mPoliticalID;
    capitalInfo.mContinent = playerContinent;
    capitalInfo.mbPlaced = true;
    capitalInfo.mb25 = false;
    capitalInfo.mb30 = true;
    Vector3 water;
    capitalInfo.mbNearWater = PlanetModel()->FindClosestWater(capitalPos, 70.0f, &water);
    capitalInfo.mStyle = g_Random.RandomUint32Uniform(3);
    capitalInfo.mEmpireID = nm->GetPlayerEmpireOrMinus1();
    if (fromTribe) {
        capitalInfo.FUN_00ae38f0(NounManager()->GetPlayerTribe());
        Vector3 tribeVec = { 0, 0, 0 };
        NounManager()->GetPlayerTribe()->FUN_00c8eb50(&tribeVec);
        uint32_t planetType = NounManager()->FUN_00f67d90()->mPlanetType;
        if (planetType == 0xc2ca9495)
            capitalInfo.mTerrainKind = 1;
        else
            capitalInfo.mTerrainKind = (planetType == 0x60a78928) ? 2 : 0;
    } else {
        int kind;
        switch (NounManager()->FUN_00f67d90()->mTerrainKind) {
        case 0:  kind = 0; break;
        case 1:  kind = 2; break;
        case 2:  kind = 1; break;
        default: kind = 0; break;
        }
        capitalInfo.mTerrainKind = kind;
    }

    if (npcCandidates.size() < (uint32_t)numCities)
        numCities = npcCandidates.size();
    uint32_t remaining = numCities - 1;
    FUN_00afb8a0(npcCandidates.mpBegin, npcCandidates.mpEnd, &g_CityRandom);

    // Continents that have candidate sites.
    FixedVector<ContinentInfo, 8> continents;
    for (cGameData** it = npcCandidates.mpBegin; it != npcCandidates.mpEnd; ++it) {
        int c = planet->GetContinent(*(*it)->mLocator.GetPosition());
        ContinentInfo* e = continents.mpBegin;
        for (; e < continents.mpEnd; ++e)
            if (e->continent == c) break;
        if (e == continents.mpEnd) {
            ContinentInfo blank = { 0, 0, 0 };
            continents.push_back(blank);
            ContinentInfo& info = continents.mpEnd[-1];
            info.continent = c;
            info.numCities = (c == playerContinent);
            info.area = planet->FUN_00b7ea00(c);
        }
    }

    // NPC cities on the player's continent.
    int npcLeft = numNpcCities;
    for (cGameData** it = npcCandidates.mpBegin; it != npcCandidates.mpEnd; ) {
        cGameData* city = *it;
        ILocator* loc = &city->mLocator;
        if (playerContinent == planet->GetContinent(*loc->GetPosition())) {
            FUN_00b9d6d0(loc->GetPosition(), cityEffects.get());
            FUN_00b9a8d0(city, true);
            remaining--;
            npcCandidates.erase(it);
            if (--npcLeft == 0) break;
        } else {
            ++it;
        }
    }

    // One coastal city on every other continent.
    for (ContinentInfo* e = continents.mpBegin; e != continents.mpEnd; ++e) {
        int c = e->continent;
        if (c == playerContinent) continue;
        for (cGameData** it = npcCandidates.mpBegin; it != npcCandidates.mpEnd; ++it) {
            cGameData* city = *it;
            ILocator* loc = &city->mLocator;
            if (c == planet->GetContinent(*loc->GetPosition()) &&
                PlanetModel()->FindClosestWater(*loc->GetPosition(), 70.0f, &water)) {
                FUN_00b9d6d0(city->mLocator.GetPosition(), cityEffects.get());
                FUN_00b9a8d0(city, false);
                remaining--;
                npcCandidates.erase(it);
                e->numCities += 1;
                break;
            }
        }
    }

    // The rest go to the continent with the most area per city.
    if (remaining > 0) {
        uint32_t n = remaining;
        ContinentInfo* bestInfo = 0;
        do {
            int best = -1;
            int bestRatio = 0;
            for (ContinentInfo* e = continents.mpBegin; e != continents.mpEnd; ++e) {
                int c = e->continent;
                if (c != playerContinent) {
                    int ratio = e->area / e->numCities;
                    if (ratio > bestRatio) {
                        bestRatio = ratio;
                        best = c;
                        bestInfo = e;
                    }
                }
            }
            for (cGameData** it = npcCandidates.mpBegin; it != npcCandidates.mpEnd; ++it) {
                cGameData* city = *it;
                if (best == planet->GetContinent(*city->mLocator.GetPosition())) {
                    FUN_00b9d6d0(city->mLocator.GetPosition(), cityEffects.get());
                    FUN_00b9a8d0(city, false);
                    remaining--;
                    npcCandidates.erase(it);
                    bestInfo->numCities += 1;
                    break;
                }
            }
        } while (--n != 0);
    }

    // Capital model.
    CityInfo& first = *SimSingleton::Get()->mCities.mpBegin;
    uint32_t capitalType = FUN_00bebc90(FUN_00bef920(first.mTerrainKind), first.mStyle);
    int capitalKind = first.mbNearWater ? (!first.mb25) + 2 : (!first.mb25);
    first.mField44 = 0x053dbcf1;
    if (fromTribe == true &&
        (g_015fd928 == 0 || g_015fd928->mList.mpNext == &g_015fd928->mList)) {
        cCityModel* model = FUN_00cf74c0()->mpModel;
        if (model) {
            if (++model->mUpdateCount > 1)
                --model->mUpdateCount;
            else
                model->mpOwner->UpdateModel(model, ((model->mFlags >> 31) & 1) != 0);
        }
        cSPTransform transform;
        Quaternion q = PlanetModel()->BuildSurfaceOrientation(capitalPos);
        transform.SetTranslation(capitalPos);
        transform.SetRotation(q);
        model->mTransform = transform;
    }

    SimSingleton::Get()->mNumPlacedCities = numCities - remaining;
    capitalPos = PlanetModel()->DirectionToSurfacePosition(capitalPos);
    Quaternion capitalOrient = PlanetModel()->BuildSurfaceOrientation(capitalPos, FUN_00bd8750(capitalPos));
    if (first.mbNearWater == 1)
        FUN_00b932a0(&capitalPos, &capitalOrient, FUN_00b93dc0(capitalType, capitalKind));
    CityObject* capitalCity = FUN_00b99ed0(&first, &capitalPos, &capitalOrient);
    int empire = first.mEmpireID;
    SimSingleton::Get()->FUN_00ae49d0((void*)FUN_00b90c50, empire, &capitalPos, capitalKind, capitalType,
                                      &first, &capitalOrient, 1)->mpCity = capitalCity;
    SimSingleton::Get()->mLastCityIndex = SimSingleton::Get()->mCities.size() - 1;
    FUN_00cf74c0()->FUN_00cf8920(&capitalPos);
    FUN_00cf74c0()->FUN_00cf8ba0(playerContinent);
    SimSingleton::Get()->FUN_00ae34b0(&capitalPos);

    // Models and terrain for every city that is not placed yet.
    int count = SimSingleton::Get()->mCities.size();
    for (int i = 0; i < count; ++i) {
        CityInfo& info = SimSingleton::Get()->mCities.mpBegin[i];
        if (!info.mbPlaced) {
            uint32_t typeID = FUN_00bebc90(FUN_00bef920(info.mTerrainKind), info.mStyle);
            int kind = info.mb25 ? (info.mbNearWater ? 2 : 0) : (info.mbNearWater ? 3 : 1);
            PropertyListPtr cityList;
            if (GetPropList(PropertyManager(), typeID, 0x02e4b4cc, cityList)) {
                ResourceKey key = { 0, 0, 0 };
                switch (kind) {
                case 0: GetPropertyAsKey(cityList.get(), 0x044449ba, key); break;
                case 1: GetPropertyAsKey(cityList.get(), 0x044449bb, key); break;
                case 2: GetPropertyAsKey(cityList.get(), 0x044449bc, key); break;
                case 3: GetPropertyAsKey(cityList.get(), 0x044449bd, key); break;
                }
                key.groupID = 0x40828100;
                PropertyListPtr modelList;
                if (GetPropList(PropertyManager(), key.instanceID, key.groupID, modelList)) {
                    info.mModelKey = key;
                    ResourceKey key2 = { 0, 0, 0 };
                    if (GetPropertyAsKey(modelList.get(), 0x03abc381, key2))
                        info.mModelKey2 = key2;

                    cSPTransform transform;
                    Vector3 pos = *FUN_00b993c0(info.mPoliticalID)->mLocator.GetPosition();
                    pos = PlanetModel()->DirectionToSurfacePosition(pos);
                    Quaternion orient = PlanetModel()->BuildSurfaceOrientation(pos, FUN_00bd8750(pos));
                    if (info.mbNearWater == 1)
                        FUN_00b932a0(&pos, &orient, FUN_00b93dc0(typeID, kind));
                    transform.SetTranslation(pos);
                    transform.SetRotation(orient);

                    PropertyListPtr footprint;
                    if (GetPropList(PropertyManager(), FUN_00bebd00(kind), key.groupID, footprint)) {
                        capitalCity->mModelID = PlanetModel()->mpRenderer->CreateModel(transform, footprint.get());
                        if (capitalCity->FUN_00bd81f0()) {
                            int id = capitalCity->mModelID;
                            CityObject::Sub* sub = capitalCity->FUN_00bd81f0();
                            sub->mBC = id;
                            sub->mC0 = 0;
                        }
                    }
                    float innerRadius = 66.0f;
                    float outerRadius = 48.0f;
                    if (modelList) GetPropertyFloat(modelList.get(), 0x04408ed7, innerRadius);
                    if (modelList) GetPropertyFloat(modelList.get(), 0x05d52e51, outerRadius);
                    TerraformingManager()->FUN_00bbf730(&pos, outerRadius + innerRadius);
                    info.mPosition = pos;
                    info.mOrientation = orient;
                }
            }
        }
    }

    FUN_00b99760();
    uint32_t siteEffect = 0x05f4af23;
    for (Vector3* p = sitePositions.mpBegin; p != sitePositions.mpEnd; ++p)
        FUN_00b9b090(p, &siteEffect, 1, 0, 1);

    tGameDataVector* sites = nm->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                   (void*)FUN_00ace070, (void*)FUN_00b1e500, kCitySiteNoun);
    for (cGameData** it = sites->mData.mpBegin; it != sites->mData.mpEnd; ++it) {
        cGameData* site = *it;
        if (site->mDefinitionID == 0x57f09e5e)
            FUN_00b94150(site->mLocator.GetPosition(), g_Random.RandomUint32Uniform(3), 0, 0);
    }

    PropertyListPtr startEffects;
    if (pm->GetPropertyList(0x3bce99e9, 0x0302a1c9, startEffects)) {
        uint32_t id = fromTribe ? 0xbef97d11 : 0xf7084224;
        if (startEffects->HasProperty(id)) {
            Property* p = startEffects->GetPropertyObject(id);
            FUN_00b9b090(&capitalPos, (const uint32_t*)PropertyItems(p), PropertyItemCount(p), 0, 1);
        }
        if (startEffects->HasProperty(0xa1d6248e)) {
            Property* p = startEffects->GetPropertyObject(0xa1d6248e);
            FUN_00b9aa10(&capitalPos, (const uint32_t*)PropertyItems(p), PropertyItemCount(p), 0x3bce99e9);
        }
    }

    uint32_t cityNoun = 0x01be418e;
    FUN_00b99530(1, &cityNoun, 1);
    tGameDataVector* cityNouns = nm->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                       (void*)FUN_00accc30, (void*)FUN_00b1e500, 0x01be418e);
    for (cGameData** it = cityNouns->mData.mpBegin; it != cityNouns->mData.mpEnd; ++it) {
        cGameData* c = *it;
        c->FUN_00c6ace0(1);
        c->FUN_00c6b540();
    }
    if (FUN_00b3d280())
        FUN_00b3d280()->FUN_00b13bb0(&capitalPos, 0);
}
