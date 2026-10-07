// Slice s00be7bf0: the single function in this slice is
//   0x00BE7BF0  Simulator::cCity::Initialize  (2696 bytes, __thiscall, 4 args, ret 0x10)
//   (class from the ModAPI cCity layout: cCommunity base at 0, cSpatialObject at +0x120,
//    mpCityHall +0x320, mpCityWalls +0x324, mpCityTerritory +0x328, mCultureTargetInfo +0x618,
//    mCulturalTargets +0x62c; the method name is Claude-coined.)
//
// What it does (civ-stage city set-up):
//   1. clears the game-data owner, sets a global "dirty" flag, sets field_519 (not space stage and
//      the civilization's byte +0x8a);
//   2. creates the four cCulturalTarget nouns, initialises each (index, city), appends them to
//      mCulturalTargets and stores each one's cSpatialObject in mCultureTargetInfo[i];
//   3. lays out the buildings (+0x3ec) and decorations (+0x450) cCommunityLayouts;
//   4. creates the city walls, finds the closest water and walks the water point up to ten
//      8-unit steps away from the walls, snaps it to the planet and sets the walls' mode;
//   5. (not space stage, arg4) applies the walls' terrain modifications (level + texture);
//   6. creates the city territory and city hall, then refreshes the city;
//   7. picks three random building-model keys from property list 0x44a98658;
//   8. in space stage, for a non-player city on a planet without (a valid) record, calls 0x00be6900;
//   9. tells the planet model about the city's position.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc: RAII locals but no EH frame).
#include "types.h"

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }
void* operator new(size_t size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                          // 0x00f473a0
void operator delete[](void* p);                                         // 0x00f47380
#include <math.h>

// ---------------------------------------------------------------------------------------
// Math
struct Vector3 {
    float x, y, z;
    __forceinline Vector3() {}
    __forceinline Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    __forceinline Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    __forceinline Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    __forceinline Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    __forceinline Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
};

__forceinline Vector3 Normalized(const Vector3& v)
{
    float inv = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + 1e-8f);
    return Vector3(v.x * inv, v.y * inv, v.z * inv);
}

struct Matrix3 {
    Vector3 row[3];
};

extern Vector3 g_ZeroVector;        // 0x0168bd70  (Vector3::ZERO)
extern Matrix3 g_IdentityMatrix3;   // 0x0168c360  (Matrix3::IDENTITY)

struct Transform {
    uint16_t mFlags;              // +0x0
    uint16_t mModificationCount;  // +0x2
    Vector3  mTranslation;        // +0x4
    float    mScale;              // +0x10
    Matrix3  mRotation;           // +0x14

    __forceinline Transform() : mFlags(0), mModificationCount(0), mTranslation(g_ZeroVector),
                                mScale(1.0f)
    {
        mRotation.row[0] = Vector3(g_IdentityMatrix3.row[0]);
        mRotation.row[1] = Vector3(g_IdentityMatrix3.row[1]);
        mRotation.row[2] = Vector3(g_IdentityMatrix3.row[2]);
    }
};

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
    __forceinline ResourceKey() {}
    __forceinline ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};

// ---------------------------------------------------------------------------------------
// EASTL pieces
template <class T> struct intrusive_ptr {
    T* mpObject;
    __forceinline intrusive_ptr() : mpObject(0) {}
    __forceinline intrusive_ptr(const intrusive_ptr& x) : mpObject(x.mpObject) { if (mpObject) intrusive_ptr_add_ref(mpObject); }
    __forceinline ~intrusive_ptr() { if (mpObject) intrusive_ptr_release(mpObject); }
    __forceinline T* get() const { return mpObject; }
    __forceinline T* operator->() const { return mpObject; }
    __forceinline intrusive_ptr& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) intrusive_ptr_add_ref(pObject);
            mpObject = pObject;
            if (pTemp) intrusive_ptr_release(pTemp);
        }
        return *this;
    }
};

// SP's vector allocator keeps a header word in front of each block.
struct sp_vector_allocator {
    uint32_t mData[2];
};
__forceinline void SpFree(void* p)
{
    if (((uint32_t*)p)[-1] != 0)
        operator delete[](p);
}

template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    __forceinline SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~SpVector() { if (mpBegin) SpFree(mpBegin); }
    void DoInsertValue(T* position, const T& value);                  // 0x00aea5d0 / 0x004b5ad0
    __forceinline void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

struct KeyVector {
    ResourceKey* mpBegin;
    ResourceKey* mpEnd;
    ResourceKey* mpCapacity;
    sp_vector_allocator mAllocator;

    void DoInsertValues(ResourceKey* position, size_t n, const ResourceKey& value);   // 0x00541030
    __forceinline ResourceKey* erase(ResourceKey* first, ResourceKey* last)
    {
        ResourceKey* d = first;
        for (ResourceKey* s = last; s != mpEnd; ++s, ++d)
            *d = *s;
        mpEnd -= (last - first);
        return first;
    }
    __forceinline void resize(size_t n)
    {
        if (n > (size_t)(mpEnd - mpBegin))
            DoInsertValues(mpEnd, n - (mpEnd - mpBegin), ResourceKey(0, 0, 0));
        else
            erase(mpBegin + n, mpEnd);
    }
    __forceinline ResourceKey& operator[](int i) { return mpBegin[i]; }
};

// ---------------------------------------------------------------------------------------
// App / engine
class PropertyList {
public:
    virtual void AddRef();
    virtual void Release();
};
typedef intrusive_ptr<PropertyList> PropertyListPtr;

__forceinline PropertyListPtr& ResetForOutput(PropertyListPtr& p) { p = 0; return p; }

class IPropManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst);   // 0x2c
};
IPropManager* PropertyManager();                                         // 0x0067de30

// App::Property::GetArrayKey
bool GetArrayKey(const PropertyList* prop, uint32_t propertyID, int& count, ResourceKey*& dst);   // 0x006a0ae0

struct RandomLinearCongruential {
    uint32_t RandomUint32Uniform(uint32_t n);                            // 0x00a68fb0
};
extern RandomLinearCongruential g_Random;                                // 0x01601760

struct DirtyFlags { void Set(); };                                        // 0x00ac1500
DirtyFlags* GetDirtyFlags();                                             // 0x00b3d290

// ---------------------------------------------------------------------------------------
// Simulator
class cSpatialObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();                                // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual bool IsPlayerOwned();                                        // 0x58
    virtual Vector3 GetDirection(float f);                               // 0x5c
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8();
    virtual int SpAddRef();                                              // 0xbc
    virtual int SpRelease();                                             // 0xc0

    void LocalToWorldTransform(Transform& dst);                          // 0x00c897e0
    uint32_t mSpatialData[0xd4 / 4 - 1];
};

class cCity;

class cGameData {
public:
    virtual int AddRef();                                                // 0x00
    virtual int Release();                                               // 0x04
    void SetOwner(cGameData* owner);                                     // 0x00b18550
    uint32_t mGameData[0x34 / 4 - 1];
};

class cCulturalTargetBase : public cGameData {
public:
    uint32_t mCombatant[(0x100 - 0x34) / 4];                             // cCombatant at +0x34
};
class cCulturalTarget : public cCulturalTargetBase, public cSpatialObject {   // cSpatialObject +0x100
public:
    void Init(int index, cCity* city);                                   // 0x00bd8500
};

class cCityWalls : public cGameData {
public:
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void SetCity(cCity* city, int arg);                          // 0x54
    virtual void v58(); virtual void v5c(); virtual void v60(); virtual void v64();
    virtual void SetWallsMode(int mode);                                 // 0x68
    virtual int GetWallLevel();                                          // 0x6c

    Vector3 GetPosition();                                               // 0x00bec190

    cSpatialObject mSpatial;                                             // +0x34
    uint32_t pad108[(0x110 - 0x108) / 4];
    ResourceKey* mpModelKeys;                                            // +0x110 (vector begin)
    uint32_t pad114[(0x254 - 0x114) / 4];
    int mModelIndex;                                                     // +0x254
    uint32_t pad258[(0x34c - 0x258) / 4];
    int field_34C;                                                       // +0x34c
    bool field_350;                                                      // +0x350
};

class cCityTerritory : public cGameData {
public:
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void SetCity(cSpatialObject* city);                          // 0x54
};

class cBuilding : public cGameData {};

class cGameNounManager {
public:
    cGameData* CreateNoun(uint32_t nounID);                              // 0x00b20c60
};
cGameNounManager* NounManager();                                         // 0x00b3d300

uint32_t GetCurrentGameMode();                                           // 0x00b5b800
static const uint32_t kGameSpace = 0x1654c05;

class cTerrainModifier {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50();
    virtual uint32_t AddModification(const Transform& t, PropertyList* prop);   // 0x54
};

class cPlanetModel {
public:
    uint32_t pad0[0x24 / 4];
    cTerrainModifier* mpTerrain;                                         // +0x24
    bool FindClosestWater(const Vector3& pos, float radius, Vector3* dst);   // 0x00b8bb70
    Vector3 ToSurface(const Vector3& pos);                               // 0x00b81630
    int GetCellIndex(const Vector3& pos, int arg);                       // 0x00b7ea80
    void UpdateCell(int cell);                                           // 0x00b841a0
};
cPlanetModel* PlanetModel();                                             // 0x00b3d350

bool IsPointBlocked(int kind, const Vector3* pos);                       // 0x00c9e8e0
uint32_t GetWallsModificationID(int level);                              // 0x00bebd00

class cPlanetRecord { public: bool IsValid(); };                        // 0x00c308b0
class cPlanet { public: cPlanetRecord* GetRecord(); };                  // 0x00c71e30
cPlanet* GetActivePlanet();                                              // 0x01021260

class SimSingleton {
public:
    SimSingleton();                                                      // 0x00ae5c30
    uint32_t pad0[4];
    bool field_10;
    uint32_t pad14[(0xc8 - 0x14) / 4];
};
extern SimSingleton* g_SimSingleton;                                     // 0x0167a60c
__forceinline SimSingleton* GetSimSingleton()
{
    if (!g_SimSingleton)
        g_SimSingleton = new ("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
    return g_SimSingleton;
}

class cCommunityLayout {
public:
    void SetCenter(const Vector3& pos, float radius, const Vector3& dir);    // 0x00af9cf0
    void SetSlots(int arg, float spacing);                               // 0x00afef10
    void SetPoints(SpVector<Vector3>* points, float spacing);            // 0x00afec00
    uint32_t data[0x64 / 4];
};

class cCivilization {
public:
    uint32_t pad0[0x88 / 4];
    uint8_t pad88[2];
    bool field_8A;
};

struct tCultureTargetInfo {
    uint32_t pad0[0x78 / 4];
    intrusive_ptr<cSpatialObject> mCultureObject;                        // +0x78
    uint32_t pad7c;
};

struct cTerrainModHolder {
    uint32_t pad0[0xbc / 4];
    uint32_t mLevel;                                                     // +0xbc
    uint32_t mTexture;                                                   // +0xc0
};

class cCommunity : public cGameData {
public:
    uint32_t pad34[(0x120 - 0x34) / 4];
};

class cCity : public cCommunity, public cSpatialObject {                // cSpatialObject +0x120
public:
    virtual void c08(); virtual void c0c(); virtual void c10(); virtual void c14();
    virtual void c18(); virtual void c1c(); virtual void c20(); virtual void c24();
    virtual void c28(); virtual void c2c(); virtual void c30(); virtual void c34();
    virtual void c38(); virtual void c3c(); virtual void c40(); virtual void c44();
    virtual void c48();
    virtual int GetCellArg(cCity* city);                                 // 0x4c
    virtual void c50(); virtual void c54(); virtual void c58(); virtual void c5c();
    virtual void c60(); virtual void c64(); virtual void c68(); virtual void c6c();
    virtual void c70(); virtual void c74(); virtual void c78(); virtual void c7c();
    virtual void c80();
    virtual void Refresh();                                              // 0x84

    __forceinline cSpatialObject* Spatial() { return this; }
    void Initialize(int arg1, int arg2, int arg3, bool arg4);
    void InitCulturalTarget();
    int GetCulturePointCount();                                          // 0x00bd8a00
    void AddBuilding(cBuilding* building, bool b);                       // 0x00be1ef0
    void UpdateBuildings();                                              // 0x00be5180
    void UpdateLayout();                                                 // 0x00c00490
    void SetVisible(int b);                                              // 0x00be6900
    void UpdatePopulation();                                             // 0x00bd8000

    uint32_t pad1f4[(0x2e8 - 0x1f4) / 4];
    uint32_t mModificationHandleLevel;                                   // +0x2e8
    uint32_t mModificationHandleTexture;                                 // +0x2ec
    cTerrainModHolder* field_2F0;                                        // +0x2f0
    uint32_t pad2f4[(0x320 - 0x2f4) / 4];
    intrusive_ptr<cBuilding> mpCityHall;                                 // +0x320
    intrusive_ptr<cCityWalls> mpCityWalls;                               // +0x324
    intrusive_ptr<cCityTerritory> mpCityTerritory;                       // +0x328
    Vector3 field_32C;                                                   // +0x32c
    uint32_t pad338[(0x3ec - 0x338) / 4];
    cCommunityLayout mBuildingsLayout;                                   // +0x3ec
    cCommunityLayout mDecorationsLayout;                                 // +0x450
    uint32_t pad4b4[(0x518 - 0x4b4) / 4];
    bool mbSmallCity;                                                    // +0x518
    bool field_519;                                                      // +0x519
    uint32_t pad51c[3];
    KeyVector field_528;                                                 // +0x528
    uint32_t pad53c[(0x590 - 0x53c) / 4];
    cCivilization* mpCivilization;                                       // +0x590
    uint32_t pad594[(0x618 - 0x594) / 4];
    SpVector<tCultureTargetInfo> mCultureTargetInfo;                     // +0x618
    SpVector<intrusive_ptr<cCulturalTarget> > mCulturalTargets;          // +0x62c
};

__forceinline void intrusive_ptr_add_ref(cGameData* p) { p->AddRef(); }
__forceinline void intrusive_ptr_release(cGameData* p) { p->Release(); }
__forceinline void intrusive_ptr_add_ref(cCulturalTarget* p) { static_cast<cGameData*>(p)->AddRef(); }
__forceinline void intrusive_ptr_release(cCulturalTarget* p) { static_cast<cGameData*>(p)->Release(); }
__forceinline void intrusive_ptr_add_ref(cSpatialObject* p) { p->SpAddRef(); }
__forceinline void intrusive_ptr_release(cSpatialObject* p) { p->SpRelease(); }
__forceinline void intrusive_ptr_add_ref(PropertyList* p) { p->AddRef(); }
__forceinline void intrusive_ptr_release(PropertyList* p) { p->Release(); }

// ---------------------------------------------------------------------------------------
// 0x00BE7BF0
void cCity::Initialize(int arg1, int arg2, int arg3, bool arg4)
{
    SetOwner(0);
    GetDirtyFlags()->Set();

    field_519 = GetCurrentGameMode() != kGameSpace && mpCivilization->field_8A;

    {
        intrusive_ptr<cCulturalTarget> pTarget;
        for (int i = 0; i < 4; i++) {
            pTarget = (cCulturalTarget*)NounManager()->CreateNoun(0x3d5c325);
            pTarget->Init(i, this);
            mCulturalTargets.push_back(pTarget);
            mCultureTargetInfo.mpBegin[i].mCultureObject = pTarget.get();
        }
    }

    mBuildingsLayout.SetCenter(Spatial()->GetPosition(), 60.0f, Spatial()->GetDirection(0.0f));
    mBuildingsLayout.SetSlots(0, 12.0f);
    SpVector<Vector3> points;
    for (int i = 0; i < GetCulturePointCount(); i++)
        points.push_back(Spatial()->GetPosition());
    mBuildingsLayout.SetPoints(&points, 12.0f);

    mDecorationsLayout.SetCenter(Spatial()->GetPosition(), 32.0f, Spatial()->GetDirection(0.0f));
    mDecorationsLayout.SetSlots(0, 4.0f);

    mpCityWalls = (cCityWalls*)NounManager()->CreateNoun(0x18c7c97);
    mpCityWalls->field_34C = arg2;
    mpCityWalls->SetCity(this, arg1);

    if (PlanetModel()->FindClosestWater(Spatial()->GetPosition(), 70.0f, &field_32C)) {
        Vector3 wallsPos = mpCityWalls->GetPosition();
        Vector3 step = Normalized(field_32C - wallsPos) * 8.0f;
        for (int i = 0; i < 10; i++) {
            if (IsPointBlocked(1, &field_32C))
                break;
            field_32C += step;
        }
        field_32C = PlanetModel()->ToSurface(field_32C);
        mpCityWalls->SetWallsMode(field_519 ? 2 : 3);
    } else {
        field_32C = g_ZeroVector;
        mpCityWalls->SetWallsMode(field_519 ? 0 : 1);
    }

    if (GetCurrentGameMode() == kGameSpace) {
        if (!arg4)
            mpCityWalls->field_350 = true;
    } else {
        if (arg4) {
            cCityWalls* walls = mpCityWalls.get();
            ResourceKey key = walls->mpModelKeys[walls->mModelIndex];
            PropertyListPtr propList;
            if (PropertyManager()->GetPropertyList(key.instanceID, key.groupID, ResetForOutput(propList))) {
                Transform transform;
                mpCityWalls->mSpatial.LocalToWorldTransform(transform);
                PropertyListPtr levelProp;
                if (PropertyManager()->GetPropertyList(GetWallsModificationID(mpCityWalls->GetWallLevel()),
                                                       key.groupID, ResetForOutput(levelProp)))
                    mModificationHandleLevel = PlanetModel()->mpTerrain->AddModification(transform, levelProp.get());
                mModificationHandleTexture = PlanetModel()->mpTerrain->AddModification(transform, propList.get());
                if (field_2F0) {
                    field_2F0->mLevel = mModificationHandleLevel;
                    field_2F0->mTexture = mModificationHandleTexture;
                }
            }
            GetSimSingleton()->field_10 = true;
        }
        mpCityWalls->field_350 = true;
    }

    mpCityTerritory = (cCityTerritory*)NounManager()->CreateNoun(0x244fb08);
    mpCityTerritory->SetCity(this);

    mpCityHall = (cBuilding*)NounManager()->CreateNoun(0x18ea1eb);
    AddBuilding(mpCityHall.get(), true);
    UpdateBuildings();
    Refresh();
    UpdateLayout();

    field_528.resize(3);
    field_528[0] = ResourceKey(0x4b44c8c9, 0, 0);
    field_528[1] = ResourceKey(0x14b55883, 0, 0);
    field_528[2] = ResourceKey(0x7c6c1c1b, 0, 0);

    PropertyListPtr modelProp;
    if (PropertyManager()->GetPropertyList(0x44a98658, 0, ResetForOutput(modelProp))) {
        ResourceKey* keys;
        int count;
        if (GetArrayKey(modelProp.get(), 0x4471acd, count, keys) && count > 0)
            field_528[0] = keys[g_Random.RandomUint32Uniform(count)];
        if (GetArrayKey(modelProp.get(), 0x4471ace, count, keys) && count > 0)
            field_528[1] = keys[g_Random.RandomUint32Uniform(count)];
        if (GetArrayKey(modelProp.get(), 0x4471acf, count, keys) && count > 0)
            field_528[2] = keys[g_Random.RandomUint32Uniform(count)];
    }

    if (GetCurrentGameMode() == kGameSpace && !Spatial()->IsPlayerOwned()) {
        cPlanet* planet = GetActivePlanet();
        cPlanetRecord* record;
        if (!planet || !(record = planet->GetRecord()) || !record->IsValid())
            SetVisible(0);
    }

    PlanetModel()->UpdateCell(PlanetModel()->GetCellIndex(Spatial()->GetPosition(), GetCellArg(this)));
    UpdatePopulation();
}
