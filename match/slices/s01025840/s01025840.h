// Declarations used by SP::nSpaceCheats::cCommandSpace::Execute (slice s01025840).
//
// Every callee is an external (relocated) call in the original, so most methods
// below are declared only.  Names come from the 2008 dev-build PDB disassembly of
// the same function (dev 0x008d5fb0) where the code lines up, otherwise from
// what the callee does (see the per-line address comments).  Field offsets are
// the retail ones read from the disassembly.
#pragma once
#include "types.h"

typedef unsigned int size_t;

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00F473A0
void  operator delete[](void* p);                                                                                  // 0x00F47380

extern "C" int __cdecl _stricmp(const char* a, const char* b);   // msvcr90 import
extern "C" size_t __cdecl strlen(const char* p);
extern "C" void* __cdecl memcpy(void* d, const void* s, size_t n);
extern "C" int __cdecl strcmp(const char* a, const char* b);
extern "C" double __cdecl fabs(double x);
#pragma intrinsic(strlen, memcpy, strcmp, fabs)

#define EASTL_SIM_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
namespace Math {
// The drone cheat copies through the out-of-line math helpers.
struct Vector3 : public ::Vector3 {
    Vector3(const ::Vector3& v);                                // 0x004098A0
};
struct Quaternion : public ::Quaternion {
    Quaternion() {}
    Quaternion& operator=(const ::Quaternion& q);               // 0x00572600
};
}

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

// Float -> int with the current rounding mode (the /arch:SSE modules use an
// asm helper for this; cvtss2si is the only instruction).
inline int FloatToIntRound(float f)
{
    int r;
    __asm cvtss2si eax, f
    __asm mov r, eax
    return r;
}
// minss/maxss helpers (an unordered compare returns the second operand).
inline float Max(float a, float b) { return a > b ? a : b; }
inline float Min(float a, float b) { return a < b ? a : b; }

// ---------------------------------------------------------------------------
// EASTL (only what this function needs)
// ---------------------------------------------------------------------------
namespace eastl {

extern wchar_t gEmptyString16[2];   // 0x01667BAC

struct allocator {
    allocator() {}
};

// basic_string<char, allocator>: ctor/dtor/compare are out of line in the original.
class string {
public:
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator mAllocator;

    explicit string(const allocator& a = allocator());          // 0x00576750
    string(const char* p, const allocator& a = allocator());    // 0x0057ED80
    ~string();                                                  // 0x00530670
    const char* c_str() const { return mpBegin; }
    void make_lower();                                          // 0x008D4AA0
    int sprintf(const char* fmt, ...);                          // 0x00472FE0
};
bool operator==(const string& a, const char* b);                // 0x00555020
// Bitwise image of a string as the original passes it through "..." (%s / %ls).
struct string_arg { char* mpBegin; char* mpEnd; char* mpCapacity; uint32_t mAllocator; };
inline const string_arg& vararg(const string& s) { return *(const string_arg*)&s; }

// basic_string<wchar_t, allocator>
class string16 {
public:
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    allocator mAllocator;

    string16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    explicit string16(const allocator& a);                         // 0x00576770
    string16(const wchar_t* p, const allocator& a = allocator());  // 0x0041DF50
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf();                                         // 0x00933960
    string16& operator=(const string16& x);                        // 0x0057CB60
    string16& operator=(const wchar_t* p);                         // 0x005C3D90
    const wchar_t* c_str() const { return mpBegin; }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }
};

// The "Simulator" string: its allocator is inlined (operator new[] with the
// "Simulator" name), so the constructor below expands in place.
struct sim_allocator {
    sim_allocator() {}
    void* allocate(size_t n) { return operator new[](n, "Simulator", 0, 0, EASTL_SIM_FILE, 0xd1); }
    void  deallocate(void* p) { operator delete[](p); }
};

class sim_string {
public:
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    sim_allocator mAllocator;

    __forceinline sim_string(const char* p) : mpBegin(0), mpEnd(0), mpCapacity(0)
    {
        const size_t n = strlen(p);
        AllocateSelf(n + 1);
        memcpy(mpBegin, p, n);
        mpEnd = mpBegin + n;
        *mpEnd = 0;
    }
    ~sim_string() { DeallocateSelf(); }
    __forceinline void AllocateSelf(size_t n)
    {
        if (n > 1) {
            mpBegin = (char*)mAllocator.allocate(n);
            mpEnd = mpBegin;
            mpCapacity = mpBegin + n;
        } else {
            mpBegin = mpEnd = (char*)gEmptyString16;
            mpCapacity = (char*)gEmptyString16 + 1;
        }
    }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            mAllocator.deallocate(mpBegin);
    }
    const char* c_str() const { return mpBegin; }
};

// vector: begin/end/size are inline, everything with a body is out of line.
template <typename T>
class vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    const char* mpAllocName;
    uint32_t mAllocFlags;

    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    vector(size_t n, const T& value);
    vector(const vector& x);
    ~vector();
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](size_t i) { return mpBegin[i]; }
    void reserve(size_t n);
    void resize(size_t n);
    void clear();
    void push_back(const T& v);
    T* erase(T* first, T* last);
};

// rbtree-based map/set.  Node: left/right/parent/color then the value at +0x10.
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};
template <typename K, typename V>
struct rbtree_node : public rbtree_node_base {
    K first;
    V second;
};
template <typename K, typename V>
struct rbtree_iterator {
    rbtree_node<K, V>* mpNode;
    rbtree_iterator& operator++();                              // 0x01022B90
};
template <typename K, typename V>
struct pair_iterator_bool {
    rbtree_iterator<K, V> first;
    bool second;
};

template <typename K, typename V>
class map {
public:
    uint32_t mCompare;
    rbtree_node_base mAnchor;
    size_t mnSize;
    allocator mAllocator;

    map() : mnSize(0)
    {
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
    }
    ~map() { DoNuke((rbtree_node<K, V>*)mAnchor.mpNodeParent); }
    void DoNuke(rbtree_node<K, V>* pNode);                      // 0x009A9600
    V& operator[](const K& key);                                // 0x00643A40 / 0x006D95E0
    size_t size() const { return mnSize; }
    rbtree_node<K, V>* begin_node() { return (rbtree_node<K, V>*)mAnchor.mpNodeRight; }
    rbtree_node_base* end_node() { return &mAnchor; }
};

template <typename T>
class set {
public:
    uint32_t mCompare;
    rbtree_node_base mAnchor;
    size_t mnSize;
    allocator mAllocator;
    size_t size() const { return mnSize; }
    pair_iterator_bool<T, int> insert(const T& v);              // 0x007D0A60
};

template <typename RandomAccessIterator, typename Compare>
void sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare);   // 0x01024DF0

} // namespace eastl

namespace EA {
eastl::string16 ConvertToString16(const char* p, int length);   // 0x0093C5A0
eastl::string16 ConvertToString16(const eastl::string& s);      // 0x0093C6D0
eastl::string16 ConvertToString16(const eastl::sim_string& s);  // 0x0093C6D0 (same function, Simulator-allocator string)
namespace Hash { uint32_t FNV1_String16(const wchar_t* p, uint32_t seed, bool bCaseInsensitive); } // 0x00932F30
namespace Locale { bool StringEqualsNoCase(const eastl::string16* a, const eastl::string16* b); }   // 0x0087D9A0
namespace Random {
class RandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t limit);               // 0x00A68FB0
};
}

// AutoRefCount / intrusive_ptr: the helpers are out of line in the original.
// Reference whose Release is inlined at scope exit (T::Release is virtual).
template <typename T>
class InlineRef {
public:
    T* mpObject;
    InlineRef() : mpObject(0) {}
    explicit InlineRef(T* p);                                   // 0x00572660
    ~InlineRef() { if (mpObject) mpObject->Release(); }
    T** AsPPTypeParam();                                        // 0x00C463D0 / 0x00AE9790
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    explicit AutoRefCount(T* p);                                // 0x00572660
    AutoRefCount(const AutoRefCount& x);                        // 0x00AC8980
    ~AutoRefCount();                                            // 0x007A9610
    T** AsPPTypeParam();                                        // 0x00C463D0 / 0x00AE9790
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

namespace ArgScript {

class FormatParser {
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
    virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
    virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
    virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C();
    virtual void vf40(); virtual void vf44(); virtual void vf48(); virtual void vf4C();
    virtual void vf50(); virtual void vf54(); virtual void vf58(); virtual void vf5C();
    virtual void vf60(); virtual void vf64(); virtual void vf68(); virtual void vf6C();
    virtual void vf70(); virtual void vf74(); virtual void vf78(); virtual void vf7C();
    virtual void vf80(); virtual void vf84(); virtual void vf88(); virtual void vf8C();
    virtual void vf90();
    virtual bool ParseBool(const char* s) const;                // 0x94
    virtual float ParseFloat(const char* s) const;              // 0x98
    virtual int ParseInt(const char* s) const;                  // 0x9C
    virtual unsigned int ParseUInt(const char* s) const;        // 0xA0
};

class cArguments {
public:
    int NumArguments();                                                         // 0x00837F30
    bool HasFlag(const char* name);                                             // 0x008380B0
    const char** OptionArguments(const char* name, int count);                  // 0x00838330
    const char** OptionArguments(const char* name, int* pCount, int nMin, int nMax); // 0x00838130
};

void Output(FormatParser* parser, const char* fmt, ...);        // 0x00841000

} // namespace ArgScript
} // namespace EA

// ---------------------------------------------------------------------------
// Simulator types
// ---------------------------------------------------------------------------
namespace SP {

// Spatial sub-object (at +0x34 of UFO / vehicles).
class cSpatialObject {
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
    virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
    virtual void vf20(); virtual void vf24(); virtual void vf28();
    virtual const Vector3& GetPosition();                       // 0x2C
    virtual const Quaternion& GetOrientation();                 // 0x30
    virtual void vf34();
    virtual void SetPosition(const Vector3& v);                 // 0x38
    virtual void SetOrientation(const Quaternion& q);           // 0x3C
};

class cSpaceshipUFO {
public:
    char pad0[0x34];
    cSpatialObject mSpatial;                                    // +0x34
    char pad38[0x7f8 - 0x38];
    float mMaxEnergy;                                           // +0x7F8
    float IncrementEnergy(float amount);                        // 0x00C389F0
};

class cSimulatorPlayerUFO {
public:
    cSpaceshipUFO* GetUFO();                                    // 0x00A1AD60
    float GetMaxTravelDistance();                               // 0x00FFBFC0
};
cSimulatorPlayerUFO* GetUFOSimulator();                         // 0x00FFBE50

class cSpaceInventoryItem {
public:
    virtual void vf00();
    virtual int AddRef();
    virtual int Release();                                      // +0x08
    virtual void vf0C();
    uint32_t mInventoryFlags;                                   // +0x10 (? 0x0A written)
};

class cTradeObject {
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
    virtual void vf10(); virtual void vf14();
    virtual uint32_t GetID();                                   // 0x18
};

class cSpaceInventory {
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
    virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
    virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
    virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C();
    virtual void vf40(); virtual void vf44(); virtual void vf48(); virtual void vf4C();
    virtual void vf50(); virtual void vf54(); virtual void vf58(); virtual void vf5C();
    virtual void vf60(); virtual void vf64(); virtual void vf68(); virtual void vf6C();
    virtual void vf70(); virtual void vf74(); virtual void vf78(); virtual void vf7C();
    virtual bool AddItem(cSpaceInventoryItem* item, bool bQuiet, bool bAllowStack); // 0x80
    virtual void vf84();
    virtual int GetCargoSlotCount();                            // 0x88
    virtual void vf8C(); virtual void vf90();
    virtual void AddCargoSlots(int n);                          // 0x94
    const eastl::vector<cTradeObject*>& GetTradeObjects();      // 0x00FF3BA0
    void AddTradeObject(uint32_t id);                           // 0x00FF4840
};

class cSPUIWindow {
public:
    char pad0[0xc];
    struct State { char pad[0x1c]; uint32_t mValue; }* mpState; // +0x0C
    void SetMode(int mode);                                     // 0x007EB820
};

class cSPUISpaceTrade {
public:
    void ToggleTradeScreen();                                   // 0x01077630
};

class cSPSimulatorSpaceGame {
public:
    char pad0[0x18];
    cSPUISpaceTrade mTradeUI;                                   // +0x18
    cSpaceInventory* GetPlayerInventory();                      // 0x00A1AD60
    cSPUIWindow* GetWindow(int id);                             // 0x01005180
};
cSPSimulatorSpaceGame* SpaceGameGet();                          // 0x01002BD0

class cPlanet;
class cStarRecord;
class cEmpire;

class cPlanetRecord {
public:
    char pad0[0x18];
    wchar_t* mpName;                                            // +0x18 (string16 begin)
    char pad1c[0x28 - 0x1c];
    int mType;                                                  // +0x28
    char pad2c[0xbc - 0x2c];
    eastl::vector<ResourceKey> mPlantSpecies;                   // +0xBC
    eastl::vector<ResourceKey> mAnimalSpecies;                  // +0xD0
    bool IsDestroyed();                                         // 0x00B8D970
    const ResourceKey& GetSpiceKey();                           // 0x00B8DAD0
    cStarRecord* GetStarRecord();                               // 0x00B8DE30
    void SetName(const eastl::string16& name);                  // 0x00B8E3F0
    const eastl::string16& GetName();                           // 0x00ECDBA0
    uint32_t GetTerrainID();                                    // 0x00B8D8E0
};

struct cPlanetBuildings {
    void Clear();                                               // 0x00B8E830
};

struct cPlanetData {
    char pad0[0xe4];
    eastl::vector<void*> mpCityList;                            // +0xE4
    char padf8[0x134 - 0xf8];
    cPlanetBuildings mBuildings;                                // +0x134
    uint32_t GetTerrainID();                                    // 0x00B8D8E0
};
void RebuildPlanetData(cPlanetData* data, int techLevel);       // 0x00B96F40

struct cEllipticalOrbit {
    char pad0[0x20];
    float mfPeriod;                                             // +0x20
    char pad24[0x50 - 0x24];
    cEllipticalOrbit(const cEllipticalOrbit& x);                // 0x01022BB0
};

class cPlanet {
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
    virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
    virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
    virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C();
    virtual void vf40(); virtual void vf44(); virtual void vf48(); virtual void vf4C();
    virtual void vf50(); virtual void vf54(); virtual void vf58(); virtual void vf5C();
    virtual void vf60(); virtual void vf64(); virtual void vf68(); virtual void vf6C();
    virtual void vf70(); virtual void vf74(); virtual void vf78(); virtual void vf7C();
    virtual void vf80(); virtual void vf84(); virtual void vf88(); virtual void vf8C();
    virtual void vf90(); virtual void vf94(); virtual void vf98(); virtual void vf9C();
    virtual void vfA0(); virtual void vfA4(); virtual void vfA8(); virtual void vfAC();
    virtual void vfB0(); virtual void vfB4(); virtual void vfB8(); virtual void vfBC();
    virtual int Release();                                      // 0xC0
    char pad4[0x13c - 4];
    cPlanetData* mpPlanetData;                                  // +0x13C

    int GetType();                                              // 0x00C70880
    const cEllipticalOrbit& GetOrbit();                         // 0x00C708A0
    void SetOrbit(const cEllipticalOrbit& orbit);               // 0x00C708C0
    void SetRotationNull(bool b);                               // 0x00C70910
    void SetRotationPeriod(float seconds);                      // 0x00C709B0
    void SetDirty(bool b);                                      // 0x00C70BF0
    int GetTechLevel();                                         // 0x00C70E00
    uint32_t GetSeed();                                         // 0x00C70FB0
    void ClearCities();                                         // 0x00C710E0
    void ClearVehicles();                                       // 0x00C71100
    cEmpire* GetEmpire();                                       // 0x00C71E30
};

class cStarRecord {
public:
    virtual void vf00();
    virtual int Release();                                      // +0x04
    uint32_t GetEmpireID();                                     // 0x00B1FDB0
    const Vector3& GetPosition();                               // 0x005C65E0
    int GetTechLevel();                                         // 0x00BB9AE0
    void SetPlanetsDirty(bool b);                               // 0x00BB9BE0
    const eastl::string16& GetName();                           // 0x00BB9DE0
    void SetName(const eastl::string16& name);                  // 0x00BBA4B0
    eastl::vector<cPlanetRecord*>& GetPlanetRecords();          // 0x00BBA790
    int GetValue();                                             // 0x00BBA990
};

class cStar {
public:
    char pad0[0x48];
    cStarRecord* mpStarRecord;                                  // +0x48
    const Vector3& GetPosition();                               // 0x00C8B360
    int GetType();                                              // 0x00C8B550
};
// Comparator used by "flyto archetype" (sorts by distance to the active star).
bool CompareStarRecordDistance(const EA::InlineRef<cStarRecord>& a, const EA::InlineRef<cStarRecord>& b);   // 0x01022F00
extern const Vector3* gpCompareStarPosition;                   // 0x016DDB34

// Name as it is passed through varargs (bitwise copy of the string16).
struct tStringArg { wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator; };

class cEmpire {
public:
    char pad0[0x54];
    int mTrait;                                                 // +0x54
    int mArchetype;                                             // +0x58
    char pad5c[0x84 - 0x5c];
    uint32_t mPoliticalID;                                      // +0x84
    eastl::vector<cStarRecord*>& GetStars();                    // 0x00C308D0
    bool OwnsPlanet(cPlanetRecord* p);                          // 0x00C308E0
    cStarRecord* GetHomeStarRecord();                           // 0x00C30C60
    void AddMoney(unsigned int amount);                         // 0x00C31A60
    void SetStarGraphUpdate(bool b);                            // 0x00C31C30
    void UpdateStarGraph();                                     // 0x00C349E0
    const tStringArg& GetName();                                // 0x005C65E0
};

struct tStarSearchCriteria {
    uint32_t mStarTypes;                                        // +0x00
    uint32_t mTechLevels;                                       // +0x04
    uint32_t mFlags;                                            // +0x08
    float mMinDistance;                                         // +0x0C
    float mMaxDistance;                                         // +0x10
    char pad14[0x3c - 0x14];
    tStarSearchCriteria();                                      // 0x00BA6880
    __forceinline void SetStarType(int type)
    {
        mStarTypes = 0;
        if ((unsigned)type < 13)
            mStarTypes = 1u << (type & 0x1f);
    }
    __forceinline void SetTechLevel(int level)
    {
        mTechLevels = 0;
        if ((unsigned)level < 6)
            mTechLevels = 1u << (level & 0x1f);
    }
};

struct tEmpireStarBucket { eastl::vector<cStarRecord*> mStars; };

class cStarManager {
public:
    char pad0[0x3c];
    eastl::vector<cStar*> mStars;                               // +0x3C
    eastl::vector<cPlanet*> mPlanets;                           // +0x50
    char pad64[0xc8 - 0x64];
    eastl::vector<tEmpireStarBucket> mStarBuckets;              // +0xC8
    char paddc[0xf0 - 0xdc];
    eastl::vector<cStarRecord*> mSaveStars;                     // +0xF0
    char pad104[0x12c - 0x104];
    eastl::map<uint32_t, cEmpire*> mEmpires;                    // +0x12C

    eastl::vector<cStarRecord*>& GetStarRecordList();           // 0x00BA6300
    eastl::map<uint32_t, cEmpire*>& GetEmpireMap();             // 0x00BA6430
    cPlanetRecord* GetPlanetRecord(uint32_t id);                // 0x00BA6DC0
    cStarRecord* GetHomeStar();                                 // 0x00BA70A0
    cStarRecord* FindStarByName(const wchar_t* name);           // 0x00BA81B0
    cEmpire* GetEmpireByID(uint32_t id);                        // 0x00BA9370
    cEmpire* GetGrox();                                         // 0x00BA93B0
    cStarRecord* FindClosestStar(const Vector3& pos, const tStarSearchCriteria& criteria); // 0x00BB0E90
    void GetStarRecords(const Vector3& pos, const tStarSearchCriteria& criteria,
                        eastl::vector<cStarRecord*>& out);       // 0x00BB1080
    void ActivatePlanetRecordsForQuery(cStarRecord* star, int flags);    // 0x00BB4AF0
    void ActivatePlanet(cPlanetRecord* planet, int flags);               // 0x00BB5930
    void GetOrActivatePlanet(cPlanetRecord* planet, cPlanet** out);      // 0x00BB59B0
    void TestIfAllStarsAreReachable(const Vector3& from, float distance, bool repeat); // 0x00BB4F30
};

class cRelationshipManager {
public:
    float ApplyRelationship(uint32_t politicalID1, uint32_t politicalID2, uint32_t eventID, float amount); // 0x00D06240
};

class cPlayer {
public:
    int GetPeacePriceForPlayer(cEmpire* e);                     // 0x00C76800
    float GetPlayerWarElapsedSeconds(cEmpire* e);               // 0x00C769B0
    int GetPlayerWarCaptureDelta(cEmpire* e);                   // 0x00C76A30
};

class cVehicle {
public:
    char pad0[0x34];
    cSpatialObject mSpatial;                                    // +0x34
    void SetDrone(bool b);                                      // 0x00C9EC80
    void Init(int locomotion, int purpose, ResourceKey modelKey); // 0x00CA6630
};

class cCivilization {
public:
    const ResourceKey& GetModelTypeKey(int vehicleType);        // 0x00BF9770
    void AddVehicle(cVehicle* v);                               // 0x00BF5630
};
int GetVehicleType(int locomotion, int purpose);                // 0x00C9E6D0

class cGameNounManager {
public:
    cPlayer* GetPlayer();                                       // 0x00F67D90
    cCivilization* GetPlayerCivilization();                     // 0x00B25FB0
    cVehicle* CreateVehicle();                                  // 0x00BF1BA0
    eastl::string GetTechLevelName(int level);                  // 0x00B20EE0
};

class cTerraformingManager {
public:
    int GetTScore(cPlanetRecord* planet);                       // 0x00BBC670
};

class cPlantSpecies {
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
    virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
    virtual void vf20();
    virtual void MakeInventoryItem(cSpaceInventoryItem** out);  // 0x24
};

class cPlantSpeciesManager {
public:
    cPlantSpecies* GetSpeciesFromID(const ResourceKey& key);    // 0x00B90410
};

class cAnimalSpeciesManager {
public:
    void MakeInventoryItemFromSpecies(cSpaceInventoryItem** out, const ResourceKey& key, bool b, int n); // 0x00AC0CB0
};

class cSpaceTrading {
public:
    ResourceKey GetRareKey(int category, int index);            // 0x01039FB0
    unsigned int GetRareCount(unsigned int category);           // 0x01039FF0
    unsigned int GetRareCategoryCount();                        // 0x0103A020
    void CreateCommodityFromID(cSpaceInventoryItem** out, const ResourceKey& key, bool b, float amount); // 0x0103A480
    void FindRare(const ResourceKey& key, int n);               // 0x0103FBA0
    void AddCommodityToInventory(const ResourceKey& key, int n); // 0x0103FC10
};

class cTimeOfDay {
public:
    void SetDayLength(float seconds);                           // 0x00BC2830
};
cTimeOfDay* TimeOfDay();                                        // 0x00BC30B0

class cCinematicManager {
public:
    void PlayCinematic(const char* name, int a, int b, int c, int d, int e);  // 0x00AE0930
};

class cMission;
class cCommEvent {
public:
    virtual void vf00();
    virtual int AddRef();
    virtual int Release();
    char pad4[0x30 - 4];
    bool mbGalaxy;                                              // +0x30
    uint32_t mPlanetID;                                         // +0x34
    uint32_t mFileID;                                           // +0x38
    uint32_t mDialogID;                                         // +0x3C
    cMission* mpMission;                                        // +0x40
    int mPriority;                                              // +0x44
    uint32_t mDurationMS;                                       // +0x48
    uint32_t mElapsedMS;                                        // +0x4C
    uint32_t GetSourceEmpireID();                               // 0x006C0200
};
class cMission {
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
    virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
    virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
    virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C();
    virtual void vf40(); virtual void vf44(); virtual void vf48(); virtual void vf4C();
    virtual void vf50(); virtual void vf54(); virtual void vf58(); virtual void vf5C();
    virtual void vf60(); virtual void vf64(); virtual void vf68(); virtual void vf6C();
    virtual void vf70(); virtual void vf74(); virtual void vf78(); virtual void vf7C();
    virtual void vf80(); virtual void vf84(); virtual void vf88(); virtual void vf8C();
    virtual void vf90(); virtual void vf94(); virtual void vf98(); virtual void vf9C();
    virtual void GetName(eastl::string16& out);                 // 0xA0
};
class cCommManager {
public:
    char pad0[0x24];
    eastl::vector<cCommEvent*> mEvents;                         // +0x24
};

class cPlanetGenerator {
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08();
    virtual void RemoveTerrain(uint32_t terrainID);             // 0x0C
    virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
    virtual void vf20(); virtual void vf24();
    virtual uint32_t GetTerrainScript(uint32_t seed);           // 0x28
};
cPlanetGenerator* PlanetGenerator();                            // 0x00F48A80

class cPlanetTurnUpdater {
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
    virtual void Update(uint64_t time);                         // 0x10
    char pad4[0x48 - 4];
    bool mbTurnPending;                                         // +0x48
    bool mbTurnStarted;                                         // +0x49
};
class cAppModeSpace {
public:
    char pad0[0x188];
    cPlanetTurnUpdater* mpTurnUpdater;                          // +0x188
    void TransitionThroughWormhole();                           // 0x00FDD4F0
};
cAppModeSpace* AppModeSpace();                                  // 0x00FD9C60

struct cAllEmpiresFlag { bool mbShowAll; };
cAllEmpiresFlag* AllEmpiresFlag();                              // 0x01046FC0

// Event manager (dumpEventTimes / startEvent).
class cPropertyList;
bool GetFloatProperty(cPropertyList* props, uint32_t id, float& out);   // 0x0040CF10
class cEventManager {
public:
    char pad0[0x10];
    cPropertyList* mpProps;                                     // +0x10
    char pad14[0x48 - 0x14];
    uint64_t mPirateRaidTimeMS;                                 // +0x48
    char pad50[0x60 - 0x50];
    uint64_t mRaidPlunderTimeMS;                                // +0x60
    char pad68[0xe0 - 0x68];
    float mBioDisasterTime;                                     // +0xE0
    bool StartEvent(uint32_t id);                               // 0x01013D20
};
extern cEventManager* gpEventManager;                           // 0x016DC798

// Debug toggles and tuning globals of this module.
extern bool gbEnableGetOut;          // 0x015B743D
extern bool gbSolarRollover;         // 0x015B7430
extern bool gbDebugPicking;          // 0x015B7434
extern bool gbDebugZones;            // 0x015B7435
extern bool gbDemoTrade;             // 0x015B7436
extern bool gbDebugAsteroids;        // 0x015B7437
extern bool gbDebugExplosions;       // 0x015B7438
extern bool gbDebugCounts;           // 0x015B7439
extern bool gbDebugRelationships;    // 0x015B743A
extern bool gbDebugPlanets;          // 0x015B743B
extern bool gbDebugPowerLevel;       // 0x015B743C
extern bool gbForceAutosave;         // 0x015B743E
extern bool gbDebugAwareness;        // 0x015B743F
extern bool gbDebugHazards;          // 0x015B7440
extern bool gbAlexCheat;             // 0x015B7432
extern ResourceKey gForcedPlanetScript;   // 0x015B7444
extern uint32_t gForcedPlanetScriptFlags; // 0x015B7450
extern const char* gArchetypeNames[8];    // 0x015B747C
extern bool gbVTune;                 // 0x016DDB38
extern float gReachMin;              // 0x016DDB3C
extern float gReachMax;              // 0x016DDB40
extern const Vector3 gGalacticCorePosition;   // 0x016DDB44
extern EA::Random::RandomLinearCongruential gRandom;   // 0x01601760

cStarManager* StarManager();                    // 0x00B3D2A0
cRelationshipManager* RelationshipManager();    // 0x00B3D2C0
cGameNounManager* GameNounManager();            // 0x00B3D300
cSpaceTrading* SpaceTrading();                  // 0x00B3D3D0
cPlantSpeciesManager* PlantSpeciesManager();    // 0x00B3D420
cTerraformingManager* TerraformingManager();    // 0x00B3D430
cAnimalSpeciesManager* AnimalSpeciesManager();  // 0x00B3D450
cCommManager* CommManager();                    // 0x00B3D4A0
cCinematicManager* CinematicManager();          // 0x00B3D4D0

namespace cSPLivingUniverse {
int GetUniverseContext();                       // 0x01021080
uint32_t GetPlayerEmpireID();                   // 0x01021090
cStar* GetActiveStar();                         // 0x01021230
cStarRecord* GetActiveStarRecord();             // 0x01021240
cPlanet* GetActivePlanet();                     // 0x01021260
cPlanetRecord* GetActivePlanetRecord();         // 0x010212A0
cEmpire* GetPlayerEmpire();                     // 0x01021300
}

void CaptureStar(cStarRecord* star, uint32_t empireID);            // 0x00C8D000
void GetTurretAndBuildingCounts(cPlanetRecord* p, int* buildings, int* turrets); // 0x00C70380
void GoToStar(cStarRecord* star);                                   // 0x010229D0
void GalaxyCoordsToPosition(float x, float y, Vector3& out);        // 0x01065A50
uint32_t HashString16(const wchar_t* s);                            // 0x00572C50
ResourceKey GetValidatedSpeciesKey(uint32_t id, int flags);         // 0x004DA3D0
uint32_t SPIDFromName(const char* name);                            // 0x00571CF0
int RandomInt(int range);                                           // 0x00571ED0

// App-level messaging and resources.
class cCheatMessage {
public:
    void* vftable;
    eastl::string16 mText;
    int mnRefCount;
    cCheatMessage(const wchar_t* text, size_t length);  // 0x006BB6C0
    ~cCheatMessage();                                   // 0x006BB690
};
class IMessageServer {
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
    virtual void vf10();
    virtual bool PostMSG(uint32_t messageID, void* pMessage, void* pSender);   // 0x14
};
IMessageServer* MessageServer();                        // 0x0067DCC0
const uint32_t kMsgCheat = 0x8f287f39;

class ICheatManager {
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
    virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
    virtual void ExecuteCommand(const char* command);   // 0x20
};
ICheatManager* CheatManager();                          // 0x0067DE20

class cTypeGroupFilter {
public:
    void* vftable;
    uint32_t mTypeID;
    uint32_t mGroupID;
    cTypeGroupFilter(uint32_t typeID, uint32_t groupID);  // 0x01022990
    ~cTypeGroupFilter() { vftable = gFilterBaseVftable; }
    static void* gFilterBaseVftable;                      // 0x013EB394
};
class IResourceManager {
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
    virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
    virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
    virtual void vf30(); virtual void vf34();
    virtual int GetResourceKeyList(eastl::vector<ResourceKey>& out, cTypeGroupFilter* filter, int flags); // 0x38
    virtual void vf3C(); virtual void vf40(); virtual void vf44(); virtual void vf48(); virtual void vf4C();
    virtual void vf50(); virtual void vf54(); virtual void vf58(); virtual void vf5C();
    virtual void vf60(); virtual void vf64(); virtual void vf68(); virtual void vf6C();
    virtual void vf70(); virtual void vf74(); virtual void vf78();
    virtual bool GetFileName(const ResourceKey& key, eastl::string16& out);  // 0x7C
};
IResourceManager* ResourceManager();                    // 0x0067DCD0

namespace nSpaceCheats {

class cCommandSpace {
public:
    virtual void ParseLine(EA::ArgScript::cArguments* args);
    EA::ArgScript::FormatParser* mpFormatParser;        // +0x04
    void Execute(EA::ArgScript::cArguments* args);
};

} // namespace nSpaceCheats
} // namespace SP
