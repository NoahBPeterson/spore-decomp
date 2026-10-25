// src/game/SPGonzago/SPSpaceCheats.cpp -- migrated from slice(s) s01025840, s01024fd0, s01021e50 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpaceCheats.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cCivilization.h"
#include "SP/cEmpire.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanet.h"
#include "SP/cPlanetRecord.h"
#include "SP/cPlayer.h"
#include "SP/cRelationshipManager.h"
#include "SP/cSpatialObject.h"
#include "SP/cStar.h"
#include "SP/cStarManager.h"
#include "SP/cStarRecord.h"
#include "SP/cVehicle.h"

// ---- items of slice s01021e50 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
class cRefCounted {
public:
    virtual void AddRef();                      // slot 0x00
    virtual void Release();                     // slot 0x04
};
class cAutoRef {
public:
    void Assign(cRefCounted* pObject);
    cRefCounted* mpObject;                      // 0x000
};
void cAutoRef::Assign(cRefCounted* pObject)
{
    cRefCounted* pOld = mpObject;
    if (pObject == pOld)
        return;
    if (pObject != nullptr)
        pObject->AddRef();
    mpObject = pObject;
    if (pOld != nullptr)
        pOld->Release();
}
typedef int (__cdecl *cPointerCompare)(void*, void*);
class cObjectKey {
public:
    cObjectKey& Init(void* pFirst, void* pSecond);
    int32_t Matches(cObjectKey* pOther);

    void* mnType;                               // 0x000
    void* mpFirst;                              // 0x004
    void* mpSecond;                             // 0x008
};
class cStarVisualParams {
public:
    cStarVisualParams& CopyFrom(const cStarVisualParams& rOther);

    uint8_t mbFlag;                             // 0x000
    uint8_t mPad001[0x03];                      // 0x001
    float mafValues[25];                        // 0x004
};
struct cVector3 {
    float mfX;                                  // 0x000
    float mfY;                                  // 0x004
    float mfZ;                                  // 0x008
};
class cCivData {
public:
    cVector3* GetCities();
};
cVector3* g_pCityReferencePoint = nullptr;                  // 0x16ddb34
// ---- items of slice s01021e50 end

// ---- items of slice s01024fd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memcpy(void*, const void*, unsigned);
extern void* gSimUniverse;                                    // 0x16dc798
extern float g_f100;                                          // 0x13ec4d0  100.0f
extern float g_f50;                                           // 0x13ebc5c   50.0f
extern float g_f1_1;                                          // 0x13ef54c    1.1f
typedef unsigned int  u32;
typedef unsigned char u8;
inline void* operator new(unsigned, void* p) { return p; }
struct RBNodeBase {
    RBNodeBase* mpNodeRight;
    RBNodeBase* mpNodeLeft;
    RBNodeBase* mpNodeParent;
    char        mColor;
};
struct SetInt {                                  // eastl::set<int>  (0x1c)
    int          mCompare;                       // +0x00 eastl::less<int>
    RBNodeBase   mAnchor;                        // +0x04
    u32          mnSize;                         // +0x14
    u32          mAllocator;                     // +0x18
    void DoNukeSubtree(RBNodeBase* p);           // 0x9a9600
    SetInt() : mAnchor()
    {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
    ~SetInt() { DoNukeSubtree(mAnchor.mpNodeParent); }
};
struct VecSet {                                  // eastl::vector<eastl::set<int> >
    SetInt* mpBegin;
    SetInt* mpEnd;
    SetInt* mpCapacity;
    void DoFillInsert(SetInt* position, u32 n, const SetInt& value);   // 0x1024fd0
    void erase(SetInt* first, SetInt* last);                           // 0x1024f70 (external)
    void resize(u32 n);                                                // 0x1025750
};
struct cArguments {
    void** OptionArguments(const char* name, int* out, int a, int b); // 0x838130
    int    NumArguments();                                            // 0x837f30
    char   HasFlag(const char* name);                                 // 0x8380b0
};
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};
struct ParserBase {};
struct Parser : VPad<39, ParserBase> {             // slot 0x9c
    virtual u32 Convert(void* arg);
};
struct cCommandRaidCheat {
    void*   mPad0;                                // +0x00
    Parser* mParser;                              // +0x04
    void Execute(cArguments* args);               // 0x10251e0
};
void* FUN_01021260();                                         // 0x1021260  GetActivePlanet
int   FUN_01021080();                                         // 0x1021080  GetUniverseContext
int   FUN_01021090();                                         // 0x1021090  GetPlayerEmpireID
void* FUN_01021240(int a);                                    // 0x1021240  cSPMission::IsArchived
void* FUN_01021300();                                         // 0x1021300  GetPlayerEmpire
void* FUN_00fd9c60();                                         // 0xfd9c60
void* FUN_0102f660(void* p);                                  // 0x102f660
void* FUN_0102acb0(int a, void* b, void* c);                  // 0x102acb0  CreateUFO
void  FUN_00c3aa40(void* a, u32 b);                           // 0xc3aa40
u32   FUN_00c37120();                                         // 0xc37120
void  FUN_00c3daa0(float f);                                  // 0xc3daa0
void* FUN_00b3d2a0(void* p);                                  // 0xb3d2a0  StarManager
void* FUN_00b3d300();                                         // 0xb3d300  NounManager
void* FUN_00b3d350();                                         // 0xb3d350  PlanetModel
void* FUN_00ffbe50();                                         // 0xffbe50  GetUFOSimulator
void* FUN_00bb57b0(void* p);                                  // 0xbb57b0
void* FUN_00bba790(void* p);                                  // 0xbba790
u32   FUN_00b8dab0(void* p);                                  // 0xb8dab0
void* FUN_00b8de30(void* p);                                  // 0xb8de30  cBioElemSort
void* FUN_00b1fdb0(void* p);                                  // 0xb1fdb0  GetAvatar
void* FUN_00ba9370(void* p, void* a);                         // 0xba9370  GetEmpireByID
void  FUN_00b5f950(void* p, void* v);                         // 0xb5f950  AutoRefCount::operator=
void* FUN_00b81780(void* p, void* a, void* b);                // 0xb81780  MakeRandomWorldPosition
u32   FUN_00b7f190(void* p, void* a, void* b);                // 0xb7f190  BuildSurfaceOrientation
void* FUN_00b21340(void*, void*, void*, void*, void*, void*); // 0xb21340  GetGameDataVector
void* FUN_00a1ad60(void* p);                                  // 0xa1ad60  GetPlayerInventory
void* FUN_00c8e810(void* p);                                  // 0xc8e810  cTribe::GetMembers
void  FUN_00be3850(void* p);                                  // 0xbe3850
void  FUN_00c5b370(void* p, int t);                           // 0xc5b370  SetTarget
void  FUN_00c47180(void* p, void* a);                         // 0xc47180
int   FUN_00c5b530(void* p);                                  // 0xc5b530  GenerateBomberCount
void  FUN_00c5b390(void* p, int n);                           // 0xc5b390
void  FUN_00c485b0(void* p);                                  // 0xc485b0  Accept
void* GetMissionManager(void*, void*, void*, void*);          // 0xfeb9f0
void* FUN_00fec590(void*, void*, void*, void*);               // 0xfec590  CreateMissionFromID
struct PtrVecT {                                              // eastl::vector<T*> view
    u32    pad0;                                              // +0x00
    void** mpBegin;                                           // +0x04
    void** mpEnd;                                             // +0x08
};
struct cActivePlanetT {                                       // active planet (partial)
    u8  pad0[0x13c];
    u32 mRaidID;                                              // +0x13c
};
struct cUfoT {                                                // created UFO (partial)
    u8    pad0[0x68c];
    void* mRefCounted68c;                                     // +0x68c
};
struct cSimulatorUniverseT {
    void RemoveRaid(int a, u32 id, u32 what);                 // 0x100e780
    void FUN_01012aa0(void* empire, u32 id);                  // 0x1012aa0
};
struct Field34Base {};
struct Field34 : VPad<11, Field34Base> {                      // vtable slot 0x2c
    virtual u32 Axis(float, float);
};
struct Vt120Base {};
struct Vt120 : VPad<11, Vt120Base> {                          // vtable slot 0x2c
    virtual void f(int);
};
struct MissionBase {};
struct Mission : VPad<3, MissionBase> {                       // vtable slot 0x0c
    virtual void* GetEvent(void* id);
};
struct T14 {
    int d[5];
    T14(const T14&);                        // 0x50d440 (copy ctor)
    T14& operator=(const T14&);             // 0x50d4e0
};
void  MoveBackward14(T14* first, T14* last, T14* dest);        // 0x758b20
void* DoAlloc14(u32 n, const char*, int, int, const char*, int); // 0xf473a0
void  DoFree14(void* p);                                       // 0xf47380
inline T14* AllocT14(u32 n)
{
    return n ? (T14*)DoAlloc14(n * 0x14, "Simulator", 0, 0,
                    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
             : 0;
}
inline T14* UninitMove14(T14* first, T14* last, T14* dest)
{
    memcpy(dest, first, (unsigned)((char*)last - (char*)first));
    return dest + (last - first);
}
struct Vec14 {
    T14*  mpBegin;
    T14*  mpEnd;
    T14*  mpCapacity;
    u32   mAlloc[2];
    void DoInsertValue(T14* position, const T14& value);           // 0x10255f0
};
// ---- items of slice s01024fd0 end

// ---- items of slice s01025840 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int __cdecl _stricmp(const char* a, const char* b);   // msvcr90 import
extern "C" int __cdecl strcmp(const char* a, const char* b);
extern "C" double __cdecl fabs(double x);
#pragma intrinsic(strlen, memcpy, strcmp, fabs)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00F473A0
void  operator delete[](void* p);                                                                                  // 0x00F47380
extern "C" size_t __cdecl strlen(const char* p);
#define EASTL_SIM_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
namespace Math {
struct Vector3 : public ::Vector3 {
    Vector3(const ::Vector3& v);                                // 0x004098A0
};
}
namespace Math {
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
inline int FloatToIntRound(float f)
{
    int r;
    __asm cvtss2si eax, f
    __asm mov r, eax
    return r;
}
inline float Max(float a, float b) { return a > b ? a : b; }
inline float Min(float a, float b) { return a < b ? a : b; }
namespace eastl {
extern wchar_t gEmptyString16[2];   // 0x01667BAC
}
namespace eastl {
class allocator_s0102_5840 { public:
    allocator_s0102_5840() {}
};
}
namespace eastl {
class string {
public:
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator_s0102_5840 mAllocator;

    explicit string(const allocator_s0102_5840& a = allocator_s0102_5840());          // 0x00576750
    string(const char* p, const allocator_s0102_5840& a = allocator_s0102_5840());    // 0x0057ED80
    ~string();                                                  // 0x00530670
    const char* c_str() const { return mpBegin; }
    void make_lower();                                          // 0x008D4AA0
    int sprintf(const char* fmt, ...);                          // 0x00472FE0
};
}
namespace eastl {
bool operator==(const string& a, const char* b);                // 0x00555020
}
namespace eastl {
struct string_arg { char* mpBegin; char* mpEnd; char* mpCapacity; uint32_t mAllocator; };
}
namespace eastl {
inline const string_arg& vararg(const string& s) { return *(const string_arg*)&s; }
}
namespace eastl {
class string16_s0102_5840 {
public:
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    allocator_s0102_5840 mAllocator;

    string16_s0102_5840() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    explicit string16_s0102_5840(const allocator_s0102_5840& a);                         // 0x00576770
    string16_s0102_5840(const wchar_t* p, const allocator_s0102_5840& a = allocator_s0102_5840());  // 0x0041DF50
    ~string16_s0102_5840() { DeallocateSelf(); }
    void DeallocateSelf();                                         // 0x00933960
    string16_s0102_5840& operator=(const string16_s0102_5840& x);                        // 0x0057CB60
    string16_s0102_5840& operator=(const wchar_t* p);                         // 0x005C3D90
    const wchar_t* c_str() const { return mpBegin; }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }
};
}
namespace eastl {
struct sim_allocator {
    sim_allocator() {}
    void* allocate(size_t n) { return operator new[](n, "Simulator", 0, 0, EASTL_SIM_FILE, 0xd1); }
    void  deallocate(void* p) { operator delete[](p); }
};
}
namespace eastl {
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
}
namespace eastl {
template <typename T>
class vector_s0102_5840 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    const char* mpAllocName;
    uint32_t mAllocFlags;

    vector_s0102_5840() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    vector_s0102_5840(size_t n, const T& value);
    vector_s0102_5840(const vector_s0102_5840& x);
    ~vector_s0102_5840();
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](size_t i) { return mpBegin[i]; }
    void reserve(size_t n);
    void resize(size_t n);
    void clear();
    void push_back(const T& v);
    T* erase(T* first, T* last);  // 0x00621f50 (eastl::vector::erase)
};
}
namespace eastl {
struct rbtree_node_base_s0102_5840 {
    rbtree_node_base_s0102_5840* mpNodeRight;
    rbtree_node_base_s0102_5840* mpNodeLeft;
    rbtree_node_base_s0102_5840* mpNodeParent;
    char mColor;
};
}
namespace eastl {
template <typename K, typename V>
struct rbtree_node_s0102_5840 : public rbtree_node_base_s0102_5840 {
    K first;
    V second;
};
}
namespace eastl {
template <typename K, typename V>
struct rbtree_iterator_s0102_5840 {
    rbtree_node_s0102_5840<K, V>* mpNode;
    rbtree_iterator_s0102_5840& operator++();                              // 0x01022B90
};
}
namespace eastl {
template <typename K, typename V>
struct pair_iterator_bool {
    rbtree_iterator_s0102_5840<K, V> first;
    bool second;
};
}
namespace eastl {
template <typename K, typename V>
class map_s0102_5840 {
public:
    uint32_t mCompare;
    rbtree_node_base_s0102_5840 mAnchor;
    size_t mnSize;
    allocator_s0102_5840 mAllocator;

    map_s0102_5840() : mnSize(0)
    {
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
    }
    ~map_s0102_5840() { DoNuke((rbtree_node_s0102_5840<K, V>*)mAnchor.mpNodeParent); }
    void DoNuke(rbtree_node_s0102_5840<K, V>* pNode);                      // 0x009A9600
    V& operator[](const K& key);                                // 0x00643A40 / 0x006D95E0
    size_t size() const { return mnSize; }
    rbtree_node_s0102_5840<K, V>* begin_node() { return (rbtree_node_s0102_5840<K, V>*)mAnchor.mpNodeRight; }
    rbtree_node_base_s0102_5840* end_node() { return &mAnchor; }
};
}
namespace eastl {
template <typename T>
class set_s0102_5840 {
public:
    uint32_t mCompare;
    rbtree_node_base_s0102_5840 mAnchor;
    size_t mnSize;
    allocator_s0102_5840 mAllocator;
    size_t size() const { return mnSize; }
    pair_iterator_bool<T, int> insert(const T& v);              // 0x007D0A60
};
}
namespace eastl {
template <typename RandomAccessIterator, typename Compare>
void sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare);   // 0x01024DF0
}
namespace EA {
eastl::string16_s0102_5840 ConvertToString16(const char* p, int length);   // 0x0093C5A0
}
namespace EA {
eastl::string16_s0102_5840 ConvertToString16(const eastl::string& s);      // 0x0093C6D0
}
namespace EA {
eastl::string16_s0102_5840 ConvertToString16(const eastl::sim_string& s);  // 0x0093C6D0 (same function, Simulator-allocator string)
}
namespace EA {
namespace Hash {
 uint32_t FNV1_String16(const wchar_t* p, uint32_t seed, bool bCaseInsensitive);   // 0x00932F30
}
}
namespace EA {
namespace Locale {
 bool StringEqualsNoCase(const eastl::string16_s0102_5840* a, const eastl::string16_s0102_5840* b);   // 0x0087D9A0
}
}
namespace EA {
namespace Random {
class RandomLinearCongruential_s0102_5840 {
public:
    uint32_t RandomUint32Uniform(uint32_t limit);               // 0x00A68FB0
};
}
}
namespace EA {
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
}
namespace EA {
template <typename T>
class AutoRefCount_s0102_5840 {
public:
    T* mpObject;
    AutoRefCount_s0102_5840() : mpObject(0) {}
    explicit AutoRefCount_s0102_5840(T* p);                                // 0x00572660
    AutoRefCount_s0102_5840(const AutoRefCount_s0102_5840& x);                        // 0x00AC8980
    ~AutoRefCount_s0102_5840();                                            // 0x007A9610
    T** AsPPTypeParam();                                        // 0x00C463D0 / 0x00AE9790
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
}
namespace EA {
namespace ArgScript {
class FormatParser {
public:
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0C();
virtual void vf10();
virtual void vf14();
virtual void vf18();
virtual void vf1C();
virtual void vf20();
virtual void vf24();
virtual void vf28();
virtual void vf2C();
virtual void vf30();
virtual void vf34();
virtual void vf38();
virtual void vf3C();
virtual void vf40();
virtual void vf44();
virtual void vf48();
virtual void vf4C();
virtual void vf50();
virtual void vf54();
virtual void vf58();
virtual void vf5C();
virtual void vf60();
virtual void vf64();
virtual void vf68();
virtual void vf6C();
virtual void vf70();
virtual void vf74();
virtual void vf78();
virtual void vf7C();
virtual void vf80();
virtual void vf84();
virtual void vf88();
virtual void vf8C();
    virtual void vf90();
    virtual bool ParseBool(const char* s) const;                // 0x94
    virtual float ParseFloat(const char* s) const;              // 0x98
    virtual int ParseInt(const char* s) const;                  // 0x9C
    virtual unsigned int ParseUInt(const char* s) const;        // 0xA0
};
}
}
namespace EA {
namespace ArgScript {
class cArguments_s0102_5840 {
public:
    int NumArguments();                                                         // 0x00837F30
    bool HasFlag(const char* name);                                             // 0x008380B0
    const char** OptionArguments(const char* name, int count);                  // 0x00838330
    const char** OptionArguments(const char* name, int* pCount, int nMin, int nMax); // 0x00838130
};
}
}
namespace EA {
namespace ArgScript {
void Output(FormatParser* parser, const char* fmt, ...);        // 0x00841000
}
}
namespace SP {
class cSpatialObject_s0102_5840 {
public:
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0C();
virtual void vf10();
virtual void vf14();
virtual void vf18();
virtual void vf1C();
virtual void vf20();
virtual void vf24();
virtual void vf28();
    virtual const Vector3& GetPosition();                       // 0x2C
    virtual const Quaternion& GetOrientation();                 // 0x30
    virtual void vf34();
    virtual void SetPosition(const Vector3& v);                 // 0x38
    virtual void SetOrientation(const Quaternion& q);           // 0x3C
};
}
namespace SP {
class cSpaceshipUFO {
public:
    char pad0[0x34];
    cSpatialObject_s0102_5840 mSpatial;                                    // +0x34
    char pad38[0x7f8 - 0x38];
    float mMaxEnergy;                                           // +0x7F8
    float IncrementEnergy(float amount);                        // 0x00C389F0
};
}
namespace SP {
class cSimulatorPlayerUFO {
public:
    cSpaceshipUFO* GetUFO();                                    // 0x00A1AD60
    float GetMaxTravelDistance();                               // 0x00FFBFC0
};
}
namespace SP {
cSimulatorPlayerUFO* GetUFOSimulator();                         // 0x00FFBE50
}
namespace SP {
class cSpaceInventoryItem {
public:
    virtual void vf00();
    virtual int AddRef();
    virtual int Release();                                      // +0x08
    virtual void vf0C();
    uint32_t mInventoryFlags;                                   // +0x10 (? 0x0A written)
};
}
namespace SP {
class cTradeObject {
public:
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0C();
virtual void vf10();
virtual void vf14();
    virtual uint32_t GetID();                                   // 0x18
};
}
namespace SP {
class cSpaceInventory {
public:
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0C();
virtual void vf10();
virtual void vf14();
virtual void vf18();
virtual void vf1C();
virtual void vf20();
virtual void vf24();
virtual void vf28();
virtual void vf2C();
virtual void vf30();
virtual void vf34();
virtual void vf38();
virtual void vf3C();
virtual void vf40();
virtual void vf44();
virtual void vf48();
virtual void vf4C();
virtual void vf50();
virtual void vf54();
virtual void vf58();
virtual void vf5C();
virtual void vf60();
virtual void vf64();
virtual void vf68();
virtual void vf6C();
virtual void vf70();
virtual void vf74();
virtual void vf78();
virtual void vf7C();
    virtual bool AddItem(cSpaceInventoryItem* item, bool bQuiet, bool bAllowStack); // 0x80
    virtual void vf84();
    virtual int GetCargoSlotCount();                            // 0x88
virtual void vf8C();
virtual void vf90();
    virtual void AddCargoSlots(int n);                          // 0x94
    const eastl::vector_s0102_5840<cTradeObject*>& GetTradeObjects();      // 0x00FF3BA0
    void AddTradeObject(uint32_t id);                           // 0x00FF4840
};
}
namespace SP {
class cSPUIWindow {
public:
    char pad0[0xc];
    struct State { char pad[0x1c]; uint32_t mValue; }* mpState; // +0x0C
    void SetMode(int mode);                                     // 0x007EB820
};
}
namespace SP {
class cSPUISpaceTrade {
public:
    void ToggleTradeScreen();                                   // 0x01077630
};
}
namespace SP {
class cSPSimulatorSpaceGame {
public:
    char pad0[0x18];
    cSPUISpaceTrade mTradeUI;                                   // +0x18
    cSpaceInventory* GetPlayerInventory();                      // 0x00A1AD60
    cSPUIWindow* GetWindow(int id);                             // 0x01005180
};
}
namespace SP {
cSPSimulatorSpaceGame* SpaceGameGet();                          // 0x01002BD0
}
namespace SP {
class cPlanet_s0102_5840;
}
namespace SP {
class cStarRecord_s0102_5840;
}
namespace SP {
class cEmpire_s0102_5840;
}
namespace SP {
class cPlanetRecord_s0102_5840 {
public:
    char pad0[0x18];
    wchar_t* mpName;                                            // +0x18 (string16 begin)
    char pad1c[0x28 - 0x1c];
    int mType;                                                  // +0x28
    char pad2c[0xbc - 0x2c];
    eastl::vector_s0102_5840<ResourceKey> mPlantSpecies;                   // +0xBC
    eastl::vector_s0102_5840<ResourceKey> mAnimalSpecies;                  // +0xD0
    bool IsDestroyed();                                         // 0x00B8D970
    const ResourceKey& GetSpiceKey();                           // 0x00B8DAD0
    cStarRecord_s0102_5840* GetStarRecord();                               // 0x00B8DE30
    void SetName(const eastl::string16_s0102_5840& name);                  // 0x00B8E3F0
    const eastl::string16_s0102_5840& GetName();                           // 0x00ECDBA0
    uint32_t GetTerrainID();                                    // 0x00B8D8E0
};
}
namespace SP {
struct cPlanetBuildings {
    void Clear();                                               // 0x00B8E830
};
}
namespace SP {
struct cPlanetData {
    char pad0[0xe4];
    eastl::vector_s0102_5840<void*> mpCityList;                            // +0xE4
    char padf8[0x134 - 0xf8];
    cPlanetBuildings mBuildings;                                // +0x134
    uint32_t GetTerrainID();                                    // 0x00B8D8E0
};
}
namespace SP {
void RebuildPlanetData(cPlanetData* data, int techLevel);       // 0x00B96F40
}
namespace SP {
class cEllipticalOrbit_s0102_5840 { public:
    char pad0[0x20];
    float mfPeriod;                                             // +0x20
    char pad24[0x50 - 0x24];
    cEllipticalOrbit_s0102_5840(const cEllipticalOrbit_s0102_5840& x);                // 0x01022BB0
};
}
namespace SP {
class cPlanet_s0102_5840 {
public:
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0C();
virtual void vf10();
virtual void vf14();
virtual void vf18();
virtual void vf1C();
virtual void vf20();
virtual void vf24();
virtual void vf28();
virtual void vf2C();
virtual void vf30();
virtual void vf34();
virtual void vf38();
virtual void vf3C();
virtual void vf40();
virtual void vf44();
virtual void vf48();
virtual void vf4C();
virtual void vf50();
virtual void vf54();
virtual void vf58();
virtual void vf5C();
virtual void vf60();
virtual void vf64();
virtual void vf68();
virtual void vf6C();
virtual void vf70();
virtual void vf74();
virtual void vf78();
virtual void vf7C();
virtual void vf80();
virtual void vf84();
virtual void vf88();
virtual void vf8C();
virtual void vf90();
virtual void vf94();
virtual void vf98();
virtual void vf9C();
virtual void vfA0();
virtual void vfA4();
virtual void vfA8();
virtual void vfAC();
virtual void vfB0();
virtual void vfB4();
virtual void vfB8();
virtual void vfBC();
    virtual int Release();                                      // 0xC0
    char pad4[0x13c - 4];
    cPlanetData* mpPlanetData;                                  // +0x13C

    int GetType();                                              // 0x00C70880
    const cEllipticalOrbit_s0102_5840& GetOrbit();                         // 0x00C708A0
    void SetOrbit(const cEllipticalOrbit_s0102_5840& orbit);               // 0x00C708C0
    void SetRotationNull(bool b);                               // 0x00C70910
    void SetRotationPeriod(float seconds);                      // 0x00C709B0
    void SetDirty(bool b);                                      // 0x00C70BF0
    int GetTechLevel();                                         // 0x00C70E00
    uint32_t GetSeed();                                         // 0x00C70FB0
    void ClearCities();                                         // 0x00C710E0
    void ClearVehicles();                                       // 0x00C71100
    cEmpire_s0102_5840* GetEmpire();                                       // 0x00C71E30
};
}
namespace SP {
class cStarRecord_s0102_5840 {
public:
    virtual void vf00();
    virtual int Release();                                      // +0x04
    uint32_t GetEmpireID();                                     // 0x00B1FDB0
    const Vector3& GetPosition();                               // 0x005C65E0
    int GetTechLevel();                                         // 0x00BB9AE0
    void SetPlanetsDirty(bool b);                               // 0x00BB9BE0
    const eastl::string16_s0102_5840& GetName();                           // 0x00BB9DE0
    void SetName(const eastl::string16_s0102_5840& name);                  // 0x00BBA4B0
    eastl::vector_s0102_5840<cPlanetRecord_s0102_5840*>& GetPlanetRecords();          // 0x00BBA790
    int GetValue();                                             // 0x00BBA990
};
}
namespace SP {
class cStar_s0102_5840 {
public:
    char pad0[0x48];
    cStarRecord_s0102_5840* mpStarRecord;                                  // +0x48
    const Vector3& GetPosition();                               // 0x00C8B360
    int GetType();                                              // 0x00C8B550
};
}
namespace SP {
bool CompareStarRecordDistance(const EA::InlineRef<cStarRecord_s0102_5840>& a, const EA::InlineRef<cStarRecord_s0102_5840>& b);   // 0x01022F00
}
namespace SP {
extern const Vector3* gpCompareStarPosition;                   // 0x016DDB34
}
namespace SP {
struct tStringArg { wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator; };
}
namespace SP {
class cEmpire_s0102_5840 {
public:
    char pad0[0x54];
    int mTrait;                                                 // +0x54
    int mArchetype;                                             // +0x58
    char pad5c[0x84 - 0x5c];
    uint32_t mPoliticalID;                                      // +0x84
    eastl::vector_s0102_5840<cStarRecord_s0102_5840*>& GetStars();                    // 0x00C308D0
    bool OwnsPlanet(cPlanetRecord_s0102_5840* p);                          // 0x00C308E0
    cStarRecord_s0102_5840* GetHomeStarRecord();                           // 0x00C30C60
    void AddMoney(unsigned int amount);                         // 0x00C31A60
    void SetStarGraphUpdate(bool b);                            // 0x00C31C30
    void UpdateStarGraph();                                     // 0x00C349E0
    const tStringArg& GetName();                                // 0x005C65E0
};
}
namespace SP {
struct tStarSearchCriteria_s0102_5840 {
    uint32_t mStarTypes;                                        // +0x00
    uint32_t mTechLevels;                                       // +0x04
    uint32_t mFlags;                                            // +0x08
    float mMinDistance;                                         // +0x0C
    float mMaxDistance;                                         // +0x10
    char pad14[0x3c - 0x14];
    tStarSearchCriteria_s0102_5840();                                      // 0x00BA6880
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
}
namespace SP {
struct tEmpireStarBucket { eastl::vector_s0102_5840<cStarRecord_s0102_5840*> mStars; };
}
namespace SP {
class cStarManager_s0102_5840 {
public:
    char pad0[0x3c];
    eastl::vector_s0102_5840<cStar_s0102_5840*> mStars;                               // +0x3C
    eastl::vector_s0102_5840<cPlanet_s0102_5840*> mPlanets;                           // +0x50
    char pad64[0xc8 - 0x64];
    eastl::vector_s0102_5840<tEmpireStarBucket> mStarBuckets;              // +0xC8
    char paddc[0xf0 - 0xdc];
    eastl::vector_s0102_5840<cStarRecord_s0102_5840*> mSaveStars;                     // +0xF0
    char pad104[0x12c - 0x104];
    eastl::map_s0102_5840<uint32_t, cEmpire_s0102_5840*> mEmpires;                    // +0x12C

    eastl::vector_s0102_5840<cStarRecord_s0102_5840*>& GetStarRecordList();           // 0x00BA6300
    eastl::map_s0102_5840<uint32_t, cEmpire_s0102_5840*>& GetEmpireMap();             // 0x00BA6430
    cPlanetRecord_s0102_5840* GetPlanetRecord(uint32_t id);                // 0x00BA6DC0
    cStarRecord_s0102_5840* GetHomeStar();                                 // 0x00BA70A0
    cStarRecord_s0102_5840* FindStarByName(const wchar_t* name);           // 0x00BA81B0
    cEmpire_s0102_5840* GetEmpireByID(uint32_t id);                        // 0x00BA9370
    cEmpire_s0102_5840* GetGrox();                                         // 0x00BA93B0
    cStarRecord_s0102_5840* FindClosestStar(const Vector3& pos, const tStarSearchCriteria_s0102_5840& criteria); // 0x00BB0E90
    void GetStarRecords(const Vector3& pos, const tStarSearchCriteria_s0102_5840& criteria,
                        eastl::vector_s0102_5840<cStarRecord_s0102_5840*>& out);       // 0x00BB1080
    void ActivatePlanetRecordsForQuery(cStarRecord_s0102_5840* star, int flags);    // 0x00BB4AF0
    void ActivatePlanet(cPlanetRecord_s0102_5840* planet, int flags);               // 0x00BB5930
    void GetOrActivatePlanet(cPlanetRecord_s0102_5840* planet, cPlanet_s0102_5840** out);      // 0x00BB59B0
    void TestIfAllStarsAreReachable(const Vector3& from, float distance, bool repeat); // 0x00BB4F30
};
}
namespace SP {
class cRelationshipManager_s0102_5840 {
public:
    float ApplyRelationship(uint32_t politicalID1, uint32_t politicalID2, uint32_t eventID, float amount); // 0x00D06240
};
}
namespace SP {
class cPlayer_s0102_5840 {
public:
    int GetPeacePriceForPlayer(cEmpire_s0102_5840* e);                     // 0x00C76800
    float GetPlayerWarElapsedSeconds(cEmpire_s0102_5840* e);               // 0x00C769B0
    int GetPlayerWarCaptureDelta(cEmpire_s0102_5840* e);                   // 0x00C76A30
};
}
namespace SP {
class cVehicle_s0102_5840 {
public:
    char pad0[0x34];
    cSpatialObject_s0102_5840 mSpatial;                                    // +0x34
    void SetDrone(bool b);                                      // 0x00C9EC80
    void Init(int locomotion, int purpose, ResourceKey modelKey); // 0x00CA6630
};
}
namespace SP {
class cCivilization_s0102_5840 {
public:
    const ResourceKey& GetModelTypeKey(int vehicleType);        // 0x00BF9770
    void AddVehicle(cVehicle_s0102_5840* v);                               // 0x00BF5630
};
}
namespace SP {
int GetVehicleType(int locomotion, int purpose);                // 0x00C9E6D0
}
namespace SP {
class cGameNounManager_s0102_5840 {
public:
    cPlayer_s0102_5840* GetPlayer();                                       // 0x00F67D90
    cCivilization_s0102_5840* GetPlayerCivilization();                     // 0x00B25FB0
    cVehicle_s0102_5840* CreateVehicle();                                  // 0x00BF1BA0
    eastl::string GetTechLevelName(int level);                  // 0x00B20EE0
};
}
namespace SP {
class cTerraformingManager {
public:
    int GetTScore(cPlanetRecord_s0102_5840* planet);                       // 0x00BBC670
};
}
namespace SP {
class cPlantSpecies {
public:
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0C();
virtual void vf10();
virtual void vf14();
virtual void vf18();
virtual void vf1C();
    virtual void vf20();
    virtual void MakeInventoryItem(cSpaceInventoryItem** out);  // 0x24
};
}
namespace SP {
class cPlantSpeciesManager {
public:
    cPlantSpecies* GetSpeciesFromID(const ResourceKey& key);    // 0x00B90410
};
}
namespace SP {
class cAnimalSpeciesManager {
public:
    void MakeInventoryItemFromSpecies(cSpaceInventoryItem** out, const ResourceKey& key, bool b, int n); // 0x00AC0CB0
};
}
namespace SP {
class cSpaceTrading {
public:
    ResourceKey GetRareKey(int category, int index);            // 0x01039FB0
    unsigned int GetRareCount(unsigned int category);           // 0x01039FF0
    unsigned int GetRareCategoryCount();                        // 0x0103A020
    void CreateCommodityFromID(cSpaceInventoryItem** out, const ResourceKey& key, bool b, float amount); // 0x0103A480
    void FindRare(const ResourceKey& key, int n);               // 0x0103FBA0
    void AddCommodityToInventory(const ResourceKey& key, int n); // 0x0103FC10
};
}
namespace SP {
class cTimeOfDay {
public:
    void SetDayLength(float seconds);                           // 0x00BC2830
};
}
namespace SP {
cTimeOfDay* TimeOfDay();                                        // 0x00BC30B0
}
namespace SP {
class cCinematicManager {
public:
    void PlayCinematic(const char* name, int a, int b, int c, int d, int e);  // 0x00AE0930
};
}
namespace SP {
class cMission;
}
namespace SP {
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
}
namespace SP {
class cMission {
public:
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0C();
virtual void vf10();
virtual void vf14();
virtual void vf18();
virtual void vf1C();
virtual void vf20();
virtual void vf24();
virtual void vf28();
virtual void vf2C();
virtual void vf30();
virtual void vf34();
virtual void vf38();
virtual void vf3C();
virtual void vf40();
virtual void vf44();
virtual void vf48();
virtual void vf4C();
virtual void vf50();
virtual void vf54();
virtual void vf58();
virtual void vf5C();
virtual void vf60();
virtual void vf64();
virtual void vf68();
virtual void vf6C();
virtual void vf70();
virtual void vf74();
virtual void vf78();
virtual void vf7C();
virtual void vf80();
virtual void vf84();
virtual void vf88();
virtual void vf8C();
virtual void vf90();
virtual void vf94();
virtual void vf98();
virtual void vf9C();
    virtual void GetName(eastl::string16_s0102_5840& out);                 // 0xA0
};
}
namespace SP {
class cCommManager {
public:
    char pad0[0x24];
    eastl::vector_s0102_5840<cCommEvent*> mEvents;                         // +0x24
};
}
namespace SP {
class cPlanetGenerator {
public:
virtual void vf00();
virtual void vf04();
virtual void vf08();
    virtual void RemoveTerrain(uint32_t terrainID);             // 0x0C
virtual void vf10();
virtual void vf14();
virtual void vf18();
virtual void vf1C();
virtual void vf20();
virtual void vf24();
    virtual uint32_t GetTerrainScript(uint32_t seed);           // 0x28
};
}
namespace SP {
cPlanetGenerator* PlanetGenerator();                            // 0x00F48A80
}
namespace SP {
class cPlanetTurnUpdater {
public:
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0C();
    virtual void Update(uint64_t time);                         // 0x10
    char pad4[0x48 - 4];
    bool mbTurnPending;                                         // +0x48
    bool mbTurnStarted;                                         // +0x49
};
}
namespace SP {
class cAppModeSpace {
public:
    char pad0[0x188];
    cPlanetTurnUpdater* mpTurnUpdater;                          // +0x188
    void TransitionThroughWormhole();                           // 0x00FDD4F0
};
}
namespace SP {
cAppModeSpace* AppModeSpace();                                  // 0x00FD9C60
}
namespace SP {
struct cAllEmpiresFlag { bool mbShowAll; };
}
namespace SP {
cAllEmpiresFlag* AllEmpiresFlag();                              // 0x01046FC0
}
namespace SP {
class cPropertyList_s0102_5840;
}
namespace SP {
bool GetFloatProperty(cPropertyList_s0102_5840* props, uint32_t id, float& out);   // 0x0040CF10
}
namespace SP {
class cEventManager {
public:
    char pad0[0x10];
    cPropertyList_s0102_5840* mpProps;                                     // +0x10
    char pad14[0x48 - 0x14];
    uint64_t mPirateRaidTimeMS;                                 // +0x48
    char pad50[0x60 - 0x50];
    uint64_t mRaidPlunderTimeMS;                                // +0x60
    char pad68[0xe0 - 0x68];
    float mBioDisasterTime;                                     // +0xE0
    bool StartEvent(uint32_t id);                               // 0x01013D20
};
}
namespace SP {
extern cEventManager* gpEventManager;                           // 0x016DC798
}
namespace SP {
extern bool gbEnableGetOut;          // 0x015B743D
}
namespace SP {
extern bool gbSolarRollover;         // 0x015B7430
}
namespace SP {
extern bool gbDebugPicking;          // 0x015B7434
}
namespace SP {
extern bool gbDebugZones;            // 0x015B7435
}
namespace SP {
extern bool gbDemoTrade;             // 0x015B7436
}
namespace SP {
extern bool gbDebugAsteroids;        // 0x015B7437
}
namespace SP {
extern bool gbDebugExplosions;       // 0x015B7438
}
namespace SP {
extern bool gbDebugCounts;           // 0x015B7439
}
namespace SP {
extern bool gbDebugRelationships;    // 0x015B743A
}
namespace SP {
extern bool gbDebugPlanets;          // 0x015B743B
}
namespace SP {
extern bool gbDebugPowerLevel;       // 0x015B743C
}
namespace SP {
extern bool gbForceAutosave;         // 0x015B743E
}
namespace SP {
extern bool gbDebugAwareness;        // 0x015B743F
}
namespace SP {
extern bool gbDebugHazards;          // 0x015B7440
}
namespace SP {
extern bool gbAlexCheat;             // 0x015B7432
}
namespace SP {
extern ResourceKey gForcedPlanetScript;   // 0x015B7444
}
namespace SP {
extern uint32_t gForcedPlanetScriptFlags; // 0x015B7450
}
namespace SP {
extern const char* gArchetypeNames[8];    // 0x015B747C
}
namespace SP {
extern bool gbVTune;                 // 0x016DDB38
}
namespace SP {
extern float gReachMin;              // 0x016DDB3C
}
namespace SP {
extern float gReachMax;              // 0x016DDB40
}
namespace SP {
extern const Vector3 gGalacticCorePosition;   // 0x016DDB44
}
namespace SP {
extern EA::Random::RandomLinearCongruential_s0102_5840 gRandom;   // 0x01601760
}
namespace SP {
cStarManager_s0102_5840* StarManager();                    // 0x00B3D2A0
}
namespace SP {
cRelationshipManager_s0102_5840* RelationshipManager();    // 0x00B3D2C0
}
namespace SP {
cGameNounManager_s0102_5840* GameNounManager();            // 0x00B3D300
}
namespace SP {
cSpaceTrading* SpaceTrading();                  // 0x00B3D3D0
}
namespace SP {
cPlantSpeciesManager* PlantSpeciesManager();    // 0x00B3D420
}
namespace SP {
cTerraformingManager* TerraformingManager();    // 0x00B3D430
}
namespace SP {
cAnimalSpeciesManager* AnimalSpeciesManager();  // 0x00B3D450
}
namespace SP {
cCommManager* CommManager();                    // 0x00B3D4A0
}
namespace SP {
cCinematicManager* CinematicManager();          // 0x00B3D4D0
}
namespace SP {
namespace cSPLivingUniverse {
int GetUniverseContext();                       // 0x01021080
}
}
namespace SP {
namespace cSPLivingUniverse {
uint32_t GetPlayerEmpireID();                   // 0x01021090
}
}
namespace SP {
namespace cSPLivingUniverse {
cStar_s0102_5840* GetActiveStar();                         // 0x01021230
}
}
namespace SP {
namespace cSPLivingUniverse {
cStarRecord_s0102_5840* GetActiveStarRecord();             // 0x01021240
}
}
namespace SP {
namespace cSPLivingUniverse {
cPlanet_s0102_5840* GetActivePlanet();                     // 0x01021260
}
}
namespace SP {
namespace cSPLivingUniverse {
cPlanetRecord_s0102_5840* GetActivePlanetRecord();         // 0x010212A0
}
}
namespace SP {
namespace cSPLivingUniverse {
cEmpire_s0102_5840* GetPlayerEmpire();                     // 0x01021300
}
}
namespace SP {
void CaptureStar(cStarRecord_s0102_5840* star, uint32_t empireID);            // 0x00C8D000
}
namespace SP {
void GetTurretAndBuildingCounts(cPlanetRecord_s0102_5840* p, int* buildings, int* turrets); // 0x00C70380
}
namespace SP {
void GoToStar(cStarRecord_s0102_5840* star);                                   // 0x010229D0
}
namespace SP {
void GalaxyCoordsToPosition(float x, float y, Vector3& out);        // 0x01065A50
}
namespace SP {
uint32_t HashString16(const wchar_t* s);                            // 0x00572C50
}
namespace SP {
ResourceKey GetValidatedSpeciesKey(uint32_t id, int flags);         // 0x004DA3D0
}
namespace SP {
uint32_t SPIDFromName(const char* name);                            // 0x00571CF0
}
namespace SP {
int RandomInt(int range);                                           // 0x00571ED0
}
namespace SP {
class cCheatMessage {
public:
    void* vftable;
    eastl::string16_s0102_5840 mText;
    int mnRefCount;
    cCheatMessage(const wchar_t* text, size_t length);  // 0x006BB6C0
    ~cCheatMessage();                                   // 0x006BB690
};
}
namespace SP {
class IMessageServer {
public:
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0C();
    virtual void vf10();
    virtual bool PostMSG(uint32_t messageID, void* pMessage, void* pSender);   // 0x14
};
}
namespace SP {
IMessageServer* MessageServer();                        // 0x0067DCC0
}
namespace SP {
const uint32_t kMsgCheat = 0x8f287f39;
}
namespace SP {
class ICheatManager {
public:
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0C();
virtual void vf10();
virtual void vf14();
virtual void vf18();
virtual void vf1C();
    virtual void ExecuteCommand(const char* command);   // 0x20
};
}
namespace SP {
ICheatManager* CheatManager();                          // 0x0067DE20
}
namespace SP {
class cTypeGroupFilter {
public:
    void* vftable;
    uint32_t mTypeID;
    uint32_t mGroupID;
    cTypeGroupFilter(uint32_t typeID, uint32_t groupID);  // 0x01022990
    ~cTypeGroupFilter() { vftable = gFilterBaseVftable; }
    static void* gFilterBaseVftable;                      // 0x013EB394
};
}
namespace SP {
class IResourceManager {
public:
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0C();
virtual void vf10();
virtual void vf14();
virtual void vf18();
virtual void vf1C();
virtual void vf20();
virtual void vf24();
virtual void vf28();
virtual void vf2C();
virtual void vf30();
virtual void vf34();
    virtual int GetResourceKeyList(eastl::vector_s0102_5840<ResourceKey>& out, cTypeGroupFilter* filter, int flags); // 0x38
virtual void vf3C();
virtual void vf40();
virtual void vf44();
virtual void vf48();
virtual void vf4C();
virtual void vf50();
virtual void vf54();
virtual void vf58();
virtual void vf5C();
virtual void vf60();
virtual void vf64();
virtual void vf68();
virtual void vf6C();
virtual void vf70();
virtual void vf74();
virtual void vf78();
    virtual bool GetFileName(const ResourceKey& key, eastl::string16_s0102_5840& out);  // 0x7C
};
}
namespace SP {
IResourceManager* ResourceManager();                    // 0x0067DCD0
}
namespace SP {
namespace nSpaceCheats {
struct cCommandSpace { private:
public:
    virtual void ParseLine(EA::ArgScript::cArguments_s0102_5840* args);
    EA::ArgScript::FormatParser* mpFormatParser;        // +0x04
    void Execute(EA::ArgScript::cArguments_s0102_5840* args);
};  // namespace nSpaceCheats
}
}
// ---- items of slice s01025840 end

// @ 0x01022990
cObjectKey& cObjectKey::Init(void* pFirst, void* pSecond)
{
    mnType = (void*)0x1495c98;
    mpFirst = pFirst;
    mpSecond = pSecond;
    return *this;
}

// @ 0x01022bb0
cStarVisualParams& cStarVisualParams::CopyFrom(const cStarVisualParams& rOther)
{
    mbFlag = rOther.mbFlag;
    mafValues[0] = rOther.mafValues[0];
    mafValues[1] = rOther.mafValues[1];
    mafValues[2] = rOther.mafValues[2];
    mafValues[3] = rOther.mafValues[3];
    mafValues[4] = rOther.mafValues[4];
    mafValues[5] = rOther.mafValues[5];
    mafValues[6] = rOther.mafValues[6];
    mafValues[7] = rOther.mafValues[7];
    mafValues[8] = rOther.mafValues[8];
    mafValues[9] = rOther.mafValues[9];
    mafValues[10] = rOther.mafValues[10];
    mafValues[11] = rOther.mafValues[11];
    mafValues[12] = rOther.mafValues[12];
    mafValues[13] = rOther.mafValues[13];
    mafValues[14] = rOther.mafValues[14];
    mafValues[15] = rOther.mafValues[15];
    mafValues[16] = rOther.mafValues[16];
    mafValues[17] = rOther.mafValues[17];
    mafValues[18] = rOther.mafValues[18];
    mafValues[19] = rOther.mafValues[19];
    mafValues[20] = rOther.mafValues[20];
    mafValues[21] = rOther.mafValues[21];
    mafValues[22] = rOther.mafValues[22];
    mafValues[23] = rOther.mafValues[23];
    mafValues[24] = rOther.mafValues[24];
    return *this;
}

// @ 0x01022cb0
void SortPlanetArray(cAutoRef* pBegin, cAutoRef* pEnd, void* pUnused, cPointerCompare pCompare)
{
    if (pBegin == pEnd)
        return;
    for (cAutoRef* pSlot = pBegin + 1; pSlot != pEnd; ++pSlot) {
        cRefCounted* pValue = pSlot->mpObject;
        if (pValue != nullptr)
            pValue->AddRef();
        cAutoRef* pScan = pSlot;
        while (pScan != pBegin && pCompare(pValue, (pScan - 1)->mpObject) != 0) {
            cRefCounted* pOld = (pScan - 1)->mpObject;
            cRefCounted* pMoved = pScan->mpObject;
            if (pOld != pMoved) {
                if (pOld != nullptr)
                    pOld->AddRef();
                pScan->mpObject = pOld;
                if (pMoved != nullptr)
                    pMoved->Release();
            }
            --pScan;
        }
        pScan->Assign(pValue);
        if (pValue != nullptr)
            pValue->Release();
    }
}

// @ 0x01022d80
void InsertPlanetSorted(cAutoRef* pBegin, cAutoRef* pEnd, cPointerCompare pCompare)
{
    if (pBegin == pEnd)
        return;
    cRefCounted* pValue = pBegin->mpObject;
    if (pValue != nullptr)
        pValue->AddRef();
    cAutoRef* pScan = pBegin;
    while (pScan != pBegin && pCompare((pScan - 1)->mpObject, pValue) != 0) {
        cRefCounted* pOld = pScan->mpObject;
        cRefCounted* pMoved = (pScan - 1)->mpObject;
        if (pMoved != pOld) {
            if (pMoved != nullptr)
                pMoved->AddRef();
            pScan->mpObject = pMoved;
            if (pOld != nullptr)
                pOld->Release();
        }
        --pScan;
    }
    pScan->Assign(pValue);
    if (pValue != nullptr)
        pValue->Release();
}

// @ 0x01022e50
void SiftPlanetHeap(cAutoRef* pBegin, cAutoRef* pEnd, int32_t nLowBound, int32_t nIndex, cRefCounted* pValue, cPointerCompare pCompare)
{
    int32_t nParent = (nIndex - 1) >> 1;
    while (nIndex > nLowBound) {
        if (pCompare(pValue, pBegin[nParent].mpObject) == 0)
            break;
        pBegin[nIndex].Assign(pBegin[nParent].mpObject);
        nIndex = nParent;
        nParent = (nIndex - 1) >> 1;
    }
    pBegin[nIndex].Assign(pValue);
    if (pValue != nullptr)
        pValue->Release();
}

// @ 0x01022f00
int32_t CompareCityDistance(cCivData* pLhs, cCivData* pRhs)
{
    const cVector3& rOrigin = *g_pCityReferencePoint;

    const cVector3* pLhsCity = pLhs->GetCities();
    cVector3 vLhs;
    vLhs.mfX = pLhsCity->mfX - rOrigin.mfX;
    vLhs.mfY = pLhsCity->mfY - rOrigin.mfY;
    vLhs.mfZ = pLhsCity->mfZ - rOrigin.mfZ;

    const cVector3* pRhsCity = pRhs->GetCities();
    cVector3 vRhs;
    vRhs.mfX = pRhsCity->mfX - rOrigin.mfX;
    vRhs.mfY = pRhsCity->mfY - rOrigin.mfY;
    vRhs.mfZ = pRhsCity->mfZ - rOrigin.mfZ;

    float fRhsLength = vRhs.mfZ * vRhs.mfZ + vRhs.mfY * vRhs.mfY + vRhs.mfX * vRhs.mfX;
    float fLhsLength = vLhs.mfZ * vLhs.mfZ + vLhs.mfY * vLhs.mfY + vLhs.mfX * vLhs.mfX;
    return fRhsLength > fLhsLength;
}

// @ 0x010251e0
void cCommandRaidCheat::Execute(cArguments* args)
{
    cActivePlanetT* planet = (cActivePlanetT*)FUN_01021260();
    if (planet != 0) {
        int local38 = 0;
        void** puVar3 = args->OptionArguments("start", &local38, 0, 1);
        if (puVar3 != 0 && gSimUniverse != 0) {
            u32 uVar12 = 2;
            if (args->NumArguments() == 3)
                uVar12 = mParser->Convert(*puVar3);
            ((cSimulatorUniverseT*)gSimUniverse)->RemoveRaid(0, planet->mRaidID, uVar12);
        }

        if (args->HasFlag("test") && FUN_01021080() == 0) {
            int v18 = 0, v1c = 0, v20 = 0;
            void* pcVar5 = FUN_00fd9c60();
            FUN_0102f660((char*)pcVar5 + 0x160);
            cUfoT* iVar4 = (cUfoT*)FUN_0102acb0(10, (void*)0x1495c6c, &v18);
            void* inv = FUN_00a1ad60(FUN_00ffbe50());
            FUN_00b5f950((char*)iVar4 + 0x68c, inv);
            void* pcVar6 = FUN_00b3d350();
            void* ref = iVar4->mRefCounted68c;
            u32 uVar12 = ((Field34*)((char*)ref + 0x34))->Axis(g_f50, g_f100);
            float f28, f24, f20;
            FUN_00b81780(pcVar6, &f28, (void*)uVar12);
            float f1c = f28 * g_f1_1;
            float f18 = f24 * g_f1_1;
            float f14 = f20 * g_f1_1;
            u8 auStack_10[16];
            u32 uVar13 = FUN_00b7f190(pcVar6, auStack_10, &f28);
            FUN_00c3aa40(&f1c, uVar13);
            FUN_00a1ad60(FUN_00ffbe50());
            float f = (float)FUN_00c37120();
            FUN_00c3daa0(f);
        }

        if (args->HasFlag("brad")) {
            void* a = FUN_01021240(0);
            FUN_00b3d2a0(a);
            FUN_00bb57b0(a);
            PtrVecT* list = (PtrVecT*)FUN_00bba790(FUN_01021240(0));
            u32 i = 0;
            u32 n = (u32)(list->mpEnd - list->mpBegin);
            void* found = args;
            if (n != 0) {
                do {
                    found = list->mpBegin[i];
                    if (FUN_00b8dab0(found) == 5)
                        break;
                    ++i;
                    found = args;
                } while (i < n);
            }
            if (found != 0) {
                void* nm = FUN_00b1fdb0(FUN_00b8de30(found));
                void* emp = FUN_00ba9370(FUN_00b3d2a0(nm), 0);
                GetMissionManager((void*)0xbbae6b99, found, emp, 0);
                Mission* mgr = (Mission*)FUN_00fec590((void*)0xbbae6b99, found, emp, 0);
                void* ev = (mgr != 0) ? mgr->GetEvent((void*)0x3960c0a) : 0;
                if (ev != 0) {
                    u32 pe = (u32)FUN_01021300();
                    FUN_00c5b370(ev, (int)pe);
                    FUN_00c47180(ev, found);
                    int n2 = FUN_00c5b530(ev);
                    FUN_00c5b390(ev, n2);
                    void* av = FUN_00b1fdb0(FUN_01021240(0));
                    int id = FUN_01021090();
                    if ((int)av != id)
                        ((u8*)ev)[0x21e] = 0;
                    FUN_00c485b0(ev);
                }
            }
        }

        if (args->HasFlag("plunder") && gSimUniverse != 0) {
            void* av = FUN_00b1fdb0(FUN_01021240(0));
            void* emp = FUN_00ba9370(FUN_00b3d2a0(av), 0);
            ((cSimulatorUniverseT*)gSimUniverse)->FUN_01012aa0(emp, planet->mRaidID);
        }
    }

    if (args->HasFlag("repair") && FUN_01021080() == 0) {
        PtrVecT* vec = (PtrVecT*)FUN_00b21340(FUN_00b3d300(),
                        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xacdff0,
                        (void*)0xb1e500, (void*)0x18c43e8);
        int local38 = (int)(vec->mpEnd - vec->mpBegin);
        int local3c = 0;
        if (local38 > 0) {
            do {
                PtrVecT* members = (PtrVecT*)FUN_00c8e810(vec->mpBegin[local3c]);
                int n = (int)(members->mpEnd - members->mpBegin);
                for (int j = 0; j < n; ++j) {
                    void* obj = members->mpBegin[j];
                    ((Vt120*)((char*)obj + 0x120))->f(0);
                }
                ++local3c;
            } while (local3c < local38);
        }
    }

    if (args->HasFlag("turrets") && FUN_01021080() == 0) {
        PtrVecT* vec = (PtrVecT*)FUN_00b21340(FUN_00b3d300(),
                        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xacdff0,
                        (void*)0xb1e500, (void*)0x18c43e8);
        int n = (int)(vec->mpEnd - vec->mpBegin);
        for (int i = 0; i < n; ++i)
            FUN_00be3850(vec->mpBegin[i]);
    }
}

// @ 0x010255f0
void Vec14::DoInsertValue(T14* position, const T14& value)
{
    T14* const destPosition = position;
    if (mpEnd != mpCapacity) {
        const T14* pValue = &value;
        if ((pValue >= destPosition) && (pValue < mpEnd))
            ++pValue;
        ::new ((void*)mpEnd) T14(*(mpEnd - 1));
        MoveBackward14(destPosition, mpEnd - 1, mpEnd);
        *destPosition = *pValue;
        ++mpEnd;
    } else {
        const u32 nPosSize  = (u32)(destPosition - mpBegin);
        const u32 nPrevSize = (u32)(mpEnd - mpBegin);
        const u32 nNewSize  = nPrevSize ? (2 * nPrevSize) : 1;
        T14* const pNewData = AllocT14(nNewSize);
        ::new ((void*)(pNewData + nPosSize)) T14(value);
        T14* pNewEnd = UninitMove14(mpBegin, destPosition, pNewData);
        pNewEnd = UninitMove14(destPosition, mpEnd, ++pNewEnd);
        if (mpBegin && ((int*)mpBegin)[-1])
            DoFree14(mpBegin);
        mpBegin    = pNewData;
        mpEnd      = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x01025750
void VecSet::resize(u32 n)
{
    if (n > (u32)(mpEnd - mpBegin)) {
        SetInt v;
        DoFillInsert(mpEnd, n - (u32)(mpEnd - mpBegin), v);
    } else
        erase(mpBegin + n, mpEnd);
}

// @ 0x01025840
namespace SP { namespace nSpaceCheats {
void cCommandSpace::Execute(EA::ArgScript::cArguments_s0102_5840* args)
{
    bool handled = false;
    int numArgs = args->NumArguments();
    (void)numArgs;

    // ---- options that can be combined ------------------------------------
    if (args->HasFlag("energy")) {
        handled = true;
        cSpaceshipUFO* ufo = GetUFOSimulator()->GetUFO();
        if (ufo)
            ufo->IncrementEnergy(ufo->mMaxEnergy);
    }

    if (args->HasFlag("capture")) {
        handled = true;
        CaptureStar(cSPLivingUniverse::GetActiveStarRecord(), cSPLivingUniverse::GetPlayerEmpireID());
    }

    if (args->HasFlag("warValue")) {
        handled = true;
        if (cSPLivingUniverse::GetActiveStar() && cSPLivingUniverse::GetActiveStarRecord()) {
            cEmpire_s0102_5840* empire = StarManager()->GetEmpireByID(cSPLivingUniverse::GetActiveStarRecord()->GetEmpireID());
            cEmpire_s0102_5840* playerEmpire = cSPLivingUniverse::GetPlayerEmpire();
            if (empire && empire != playerEmpire) {
                cPlayer_s0102_5840* player = GameNounManager()->GetPlayer();
                int value = player->GetPeacePriceForPlayer(empire);
                if (value != -1) {
                    float elapsed = player->GetPlayerWarElapsedSeconds(empire);
                    int captureDelta = player->GetPlayerWarCaptureDelta(empire);
                    int playerStars = (int)playerEmpire->GetStars().size();
                    int enemyStars = (int)empire->GetStars().size();
                    EA::ArgScript::Output(mpFormatParser, "Value: %d\n", value);
                    EA::ArgScript::Output(mpFormatParser, "Player Stars: %d\n", playerStars);
                    EA::ArgScript::Output(mpFormatParser, "Enemy Stars: %d\n", enemyStars);
                    EA::ArgScript::Output(mpFormatParser, "Capture Delta: %d\n", captureDelta);
                    EA::ArgScript::Output(mpFormatParser, "Elapsed Seconds: %.0f\n", (double)elapsed);
                } else {
                    EA::ArgScript::Output(mpFormatParser, "No war is ongoing with this empire");
                }
            } else {
                EA::ArgScript::Output(mpFormatParser, "No valid empire detected at this star.");
            }
        }
    }

    if (args->HasFlag("starValue")) {
        handled = true;
        if (cSPLivingUniverse::GetActiveStar() && cSPLivingUniverse::GetActiveStarRecord()) {
            cStarRecord_s0102_5840* star = cSPLivingUniverse::GetActiveStarRecord();
            eastl::vector_s0102_5840<cPlanetRecord_s0102_5840*>& planets = star->GetPlanetRecords();
            cTerraformingManager* terraforming = TerraformingManager();
            int planetCount = (int)planets.size();
            int inhabitable = 0;
            int buildings = 0;
            int turrets = 0;
            float tscore = 0.0f;
            for (int i = 0; i < planetCount; i++) {
                cPlanetRecord_s0102_5840* planet = planets[i];
                if (planet->mType != 1 && planet->mType != 0 && !planet->IsDestroyed()) {
                    GetTurretAndBuildingCounts(planet, &buildings, &turrets);
                    inhabitable++;
                    tscore += (float)terraforming->GetTScore(planet);
                }
            }
            EA::ArgScript::Output(mpFormatParser, "Value: %d\n", star->GetValue());
            EA::ArgScript::Output(mpFormatParser, "Planet Count: %d\n", planetCount);
            EA::ArgScript::Output(mpFormatParser, "Inhabitable: %d\n", inhabitable);
            EA::ArgScript::Output(mpFormatParser, "Buildings: %d\n", buildings);
            EA::ArgScript::Output(mpFormatParser, "Turrets: %d\n", turrets);
            EA::ArgScript::Output(mpFormatParser, "Average T-Score: %f\n", (double)(tscore / (float)inhabitable));
        }
    }

    const char** opt;
    if ((opt = args->OptionArguments("year", 1)) != 0) {
        handled = true;
        float year = mpFormatParser->ParseFloat(opt[0]);
        cPlanet_s0102_5840* planet = cSPLivingUniverse::GetActivePlanet();
        if (planet) {
            cEllipticalOrbit_s0102_5840 orbit(planet->GetOrbit());
            orbit.mfPeriod = year;
            planet->SetOrbit(orbit);
        }
    }

    if ((opt = args->OptionArguments("siderealDay", 1)) != 0) {
        handled = true;
        float day = mpFormatParser->ParseFloat(opt[0]);
        int ms = FloatToIntRound(day * 1000.0f);
        cPlanet_s0102_5840* planet = cSPLivingUniverse::GetActivePlanet();
        if (planet && ms >= 0) {
            planet->SetRotationPeriod(day);
            planet->SetRotationNull(day == 0.0f);
        }
    }

    if ((opt = args->OptionArguments("day", 1)) != 0) {
        handled = true;
        float length = mpFormatParser->ParseFloat(opt[0]);
        if (cSPLivingUniverse::GetActivePlanet() && length >= 0.0f)
            TimeOfDay()->SetDayLength(length);
    }

    const Vector3& ufoPosition = GetUFOSimulator()->GetUFO()->mSpatial.GetPosition();

    if (handled)
        return;

    // ---- exclusive options ------------------------------------------------
    if (args->HasFlag("listPlants")) {
        EA::ArgScript::Output(mpFormatParser, "Disabled");
        return;
    }

    if ((opt = args->OptionArguments("startEvent", 1)) != 0) {
        eastl::sim_string eventName(opt[0]);
        uint32_t eventID = EA::Hash::FNV1_String16(EA::ConvertToString16(eventName).c_str(), 0x811c9dc5, true);
        if (!gpEventManager->StartEvent(eventID))
            EA::ArgScript::Output(mpFormatParser, "failed to create event\n");
        return;
    }

    if ((opt = args->OptionArguments("setRelationship", 1)) != 0) {
        float amount = mpFormatParser->ParseFloat(opt[0]);
        const float kMinRelationship = -10.0f;
        const float kMaxRelationship = 10.0f;
        amount = Min(Max(amount, kMinRelationship), kMaxRelationship);
        cStarRecord_s0102_5840* star = cSPLivingUniverse::GetActiveStar()->mpStarRecord;
        if (star->GetTechLevel() != 5)
            return;
        cEmpire_s0102_5840* empire = StarManager()->GetEmpireByID(star->GetEmpireID());
        if (!empire || empire == cSPLivingUniverse::GetPlayerEmpire())
            return;
        uint32_t politicalID = empire->mPoliticalID;
        uint32_t eventID;
        if (amount > 0.0f) {
            eventID = 0x526e5dc;   // positive relationship event
        } else {
            eventID = 0x526e5f3;   // negative relationship event
            amount = (float)fabs(amount);
        }
        RelationshipManager()->ApplyRelationship(politicalID, cSPLivingUniverse::GetPlayerEmpireID(), eventID, amount);
        return;
    }

    if (args->HasFlag("listAnimals")) {
        EA::ArgScript::Output(mpFormatParser, "obsolete\n");
        return;
    }

    if ((opt = args->OptionArguments("addCargo", 2)) != 0) {
        if (strcmp(opt[0], "slot") == 0) {
            unsigned int slots = mpFormatParser->ParseUInt(opt[1]);
            SpaceGameGet()->GetPlayerInventory()->AddCargoSlots(slots);
        }
        EA::InlineRef<cSpaceInventoryItem> item;
        if (strcmp(opt[0], "animal") == 0) {
            eastl::string name(opt[1]);
            uint32_t id = HashString16(EA::ConvertToString16(name).c_str());
            ResourceKey key = GetValidatedSpeciesKey(id, 0);
            AnimalSpeciesManager()->MakeInventoryItemFromSpecies(item.AsPPTypeParam(), key, true, 0);
        } else if (strcmp(opt[0], "plant") == 0) {
            ResourceKey key;
            key.instanceID = mpFormatParser->ParseUInt(opt[1]);
            key.typeID = 0;
            key.groupID = 0;
            cPlantSpecies* species = PlantSpeciesManager()->GetSpeciesFromID(key);
            if (species)
                species->MakeInventoryItem(item.AsPPTypeParam());
        } else if (strcmp(opt[0], "rare") == 0) {
            eastl::string name(opt[1]);
            ResourceKey key;
            key.instanceID = HashString16(EA::ConvertToString16(name).c_str());
            key.typeID = 0;
            key.groupID = 0;
            SpaceTrading()->CreateCommodityFromID(item.AsPPTypeParam(), key, true, 1.0f);
        } else {
            return;
        }
        if (item.get()) {
            cSpaceInventory* inventory = SpaceGameGet()->GetPlayerInventory();
            item->mInventoryFlags = 10;
            inventory->AddItem(item.get(), false, true);
        }
        return;
    }

    if (args->HasFlag("findAllRares")) {
        unsigned int categories = SpaceTrading()->GetRareCategoryCount();
        for (unsigned int category = 0; category < categories; category++) {
            unsigned int count = SpaceTrading()->GetRareCount(category);
            for (unsigned int index = 0; index < count; index++)
                SpaceTrading()->FindRare(SpaceTrading()->GetRareKey(category, index), 1);
        }
        return;
    }

    if (args->HasFlag("enableGetOut")) {
        gbEnableGetOut = !gbEnableGetOut;
        return;
    }
    if (args->HasFlag("solarrollover")) {
        gbSolarRollover = !gbSolarRollover;
        return;
    }
    if (args->HasFlag("picking")) {
        gbDebugPicking = !gbDebugPicking;
        return;
    }

    int count;
    if ((opt = args->OptionArguments("testTravel", &count, 0, 3)) != 0) {
        float distance;
        if (count <= 0 || !(0.0f < (distance = mpFormatParser->ParseFloat(opt[0]))))
            distance = GetUFOSimulator()->GetMaxTravelDistance();
        if (!(distance > 0.0f))
            return;
        bool toCore = count > 1 ? strcmp(opt[1], "core") == 0 : false;
        bool repeat = count > 2 ? strcmp(opt[2], "repeat") == 0 : false;
        const Vector3* from = toCore ? &gGalacticCorePosition : &cSPLivingUniverse::GetActiveStar()->GetPosition();
        Vector3 position = *from;
        StarManager()->TestIfAllStarsAreReachable(position, distance, repeat);
        return;
    }

    if (args->HasFlag("zones")) {
        gbDebugZones = !gbDebugZones;
        return;
    }

    if (args->HasFlag("trade")) {
        SpaceGameGet()->mTradeUI.ToggleTradeScreen();
        return;
    }

    if (args->HasFlag("demotrade")) {
        gbSolarRollover = !gbSolarRollover;
        eastl::vector_s0102_5840<cTradeObject*> objects(SpaceGameGet()->GetPlayerInventory()->GetTradeObjects());
        for (cTradeObject** it = objects.begin(); it != objects.end(); ++it)
            SpaceGameGet()->GetPlayerInventory()->AddTradeObject((*it)->GetID());
        gbDemoTrade = true;
        return;
    }

    if (args->HasFlag("allEmpires")) {
        AllEmpiresFlag()->mbShowAll = !AllEmpiresFlag()->mbShowAll;
        return;
    }

    if (args->HasFlag("vtune")) {
        gbVTune = true;
        return;
    }

    if ((opt = args->OptionArguments("reach", &count, 2, 2)) != 0) {
        gReachMin = mpFormatParser->ParseFloat(opt[0]);
        gReachMax = mpFormatParser->ParseFloat(opt[1]);
        return;
    }

    if (args->HasFlag("dumpEventTimes")) {
        float elapsed = 0.0f;
        GetFloatProperty(gpEventManager->mpProps, 0x31e761f, elapsed);
        EA::ArgScript::Output(mpFormatParser, "PirateRaid : %d secs\n", (int)((float)(gpEventManager->mPirateRaidTimeMS / 1000) - elapsed));
        GetFloatProperty(gpEventManager->mpProps, 0x397a073, elapsed);
        EA::ArgScript::Output(mpFormatParser, "RaidPlunder : %d secs\n", (int)((float)(gpEventManager->mRaidPlunderTimeMS / 1000) - elapsed));
        GetFloatProperty(gpEventManager->mpProps, 0x4488192, elapsed);
        EA::ArgScript::Output(mpFormatParser, "BioDisaster : %d secs\n", (int)(gpEventManager->mBioDisasterTime - elapsed));
        return;
    }

    if (args->HasFlag("demo")) {
        IMessageServer* server = MessageServer();
        eastl::string16_s0102_5840 command;
        command = L"tool enable all";
        cCheatMessage msg1(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg1, 0);
        command = L"space -allEmpires";
        cCheatMessage msg2(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg2, 0);
        cSpaceInventory* inventory = SpaceGameGet()->GetPlayerInventory();
        int slots = inventory->GetCargoSlotCount();
        if (slots < 50)
            inventory->AddCargoSlots(50 - slots);
        return;
    }

    if (args->HasFlag("alex")) {
        IMessageServer* server = MessageServer();
        eastl::string16_s0102_5840 command;
        gbAlexCheat = !gbAlexCheat;
        for (int i = 0; i < 10; i++)
            SpaceTrading()->AddCommodityToInventory(SpaceTrading()->GetRareKey(0, i), 1);
        for (int i = 0; i < 10; i += 2)
            SpaceTrading()->AddCommodityToInventory(SpaceTrading()->GetRareKey(1, i), 1);
        SpaceTrading()->AddCommodityToInventory(cSPLivingUniverse::GetActivePlanetRecord()->GetSpiceKey(), 0x62);
        command = L"tool enable interplanetarydrive";
        cCheatMessage msg1(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg1, 0);
        command = L"tool enable interstellardrive";
        cCheatMessage msg2(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg2, 0);
        command = L"space -solarrollover";
        cCheatMessage msg3(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg3, 0);
        command = L"space -allEmpires";
        cCheatMessage msg4(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg4, 0);
        return;
    }

    if (args->HasFlag("baris")) {
        IMessageServer* server = MessageServer();
        eastl::string16_s0102_5840 command;
        command = L"tool enable all";
        cCheatMessage msg1(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg1, 0);
        command = L"space -solarrollover";
        cCheatMessage msg2(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg2, 0);
        command = L"space -allEmpires";
        cCheatMessage msg3(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg3, 0);
        command = L"mission dd";
        cCheatMessage msg4(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg4, 0);
        command = L"space -debug r";
        cCheatMessage msg5(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg5, 0);
        return;
    }

    if (args->HasFlag("cricket")) {
        // Monte-Carlo: how many random rares until all 8 collections of 10 are complete.
        opt = args->OptionArguments("cricket", 1);
        if (!opt)
            return;
        if (opt[0] != "rares")   // pointer compare (pooled literal), as in the original
            return;
        eastl::vector_s0102_5840<eastl::set_s0102_5840<int> > collections;
        collections.reserve(8);
        eastl::vector_s0102_5840<int> completedAfter;
        completedAfter.reserve(8);
        int zero = 0;
        eastl::vector_s0102_5840<int> totals(8, zero);
        int totalRares = 0;
        int totalRepeats = 0;
        int runs = 100;
        do {
            collections.erase(collections.begin(), collections.end());
            collections.resize(8);
            completedAfter.clear();
            int rares = 0;
            int repeats = 0;
            for (;;) {
                int roll = (int)gRandom.RandomUint32Uniform(80);
                int item = roll % 10;
                eastl::set_s0102_5840<int>& collection = collections[roll / 10];
                size_t before = collection.size();
                collection.insert(item);
                size_t after = collection.size();
                rares++;
                if (before == after) {
                    repeats++;
                    continue;
                }
                if (after != 10)
                    continue;
                completedAfter.push_back(rares);
                if (completedAfter.size() == 8)
                    break;
            }
            totalRares += rares;
            totalRepeats += repeats;
            for (int i = 0; i < 8; i++)
                totals[i] += completedAfter[i];
        } while (--runs);
        EA::ArgScript::Output(mpFormatParser, "Found %.1f rares with %.1f repeats\n", totalRares * 0.01, totalRepeats * 0.01);
        EA::ArgScript::Output(mpFormatParser, "Collections completed: ");
        for (int i = 0; i < 8; i++)
            EA::ArgScript::Output(mpFormatParser, "%.1f ", totals[i] * 0.01);
        EA::ArgScript::Output(mpFormatParser, "\n");
        return;
    }

    if ((opt = args->OptionArguments("money", 1)) != 0) {
        cSPLivingUniverse::GetPlayerEmpire()->AddMoney(mpFormatParser->ParseUInt(opt[0]));
        cSPUIWindow* window = SpaceGameGet()->GetWindow(0xb);
        window->SetMode(8);
        window->mpState->mValue = 0;
        return;
    }

    if (args->OptionArguments("lategame", 1)) {
        EA::ArgScript::Output(mpFormatParser, "LateGame cheat has been supersceded by the testscript system.\n");
        EA::ArgScript::Output(mpFormatParser, "example:  tester -run TestScript lategame\\stage1 \n");
        return;
    }

    if ((opt = args->OptionArguments("initPlanetRecords", 1)) != 0) {
        float radius = mpFormatParser->ParseFloat(opt[0]);
        eastl::vector_s0102_5840<cStarRecord_s0102_5840*> stars;
        tStarSearchCriteria_s0102_5840 criteria;
        if (radius > 0.0f)
            criteria.mMaxDistance = radius;
        StarManager()->GetStarRecords(ufoPosition, criteria, stars);
        int starCount = (int)stars.size();
        for (int i = 0; i < starCount; i++) {
            cStarRecord_s0102_5840* star = stars[i];
            StarManager()->ActivatePlanetRecordsForQuery(star, 0);
            eastl::vector_s0102_5840<cPlanetRecord_s0102_5840*>& planets = star->GetPlanetRecords();
            int planetCount = (int)planets.size();
            for (int j = 0; j < planetCount; j++) {
                cPlanetRecord_s0102_5840* planetRecord = planets[j];
                EA::InlineRef<cPlanet_s0102_5840> planet;
                StarManager()->GetOrActivatePlanet(planetRecord, planet.AsPPTypeParam());
            }
        }
        return;
    }

    if ((opt = args->OptionArguments("initStarRecords", 1)) != 0) {
        float radius = mpFormatParser->ParseFloat(opt[0]);
        eastl::vector_s0102_5840<cStarRecord_s0102_5840*> stars;
        tStarSearchCriteria_s0102_5840 criteria;
        if (radius > 0.0f)
            criteria.mMaxDistance = radius;
        StarManager()->GetStarRecords(ufoPosition, criteria, stars);
        int starCount = (int)stars.size();
        for (int i = 0; i < starCount; i++) {
            stars[i]->SetPlanetsDirty(true);
            if (i % 1000 == 0)
                EA::ArgScript::Output(mpFormatParser, "%d,%d\n", i, starCount);
        }
        eastl::map_s0102_5840<uint32_t, cEmpire_s0102_5840*>& empires = StarManager()->GetEmpireMap();
        eastl::rbtree_iterator_s0102_5840<uint32_t, cEmpire_s0102_5840*> it;
        for (it.mpNode = empires.begin_node(); it.mpNode != empires.end_node(); ++it) {
            it.mpNode->second->SetStarGraphUpdate(true);
            it.mpNode->second->UpdateStarGraph();
        }
        return;
    }

    if (args->HasFlag("listempires")) {
        eastl::map_s0102_5840<uint32_t, cEmpire_s0102_5840*>& empires = StarManager()->GetEmpireMap();
        eastl::rbtree_iterator_s0102_5840<uint32_t, cEmpire_s0102_5840*> it;
        for (it.mpNode = empires.begin_node(); it.mpNode != empires.end_node(); ++it) {
            cEmpire_s0102_5840* empire = it.mpNode->second;
            EA::ArgScript::Output(mpFormatParser, "Empire: %ls\n", empire->GetName());
            eastl::vector_s0102_5840<cStarRecord_s0102_5840*>& stars = empire->GetStars();
            int starCount = (int)stars.size();
            for (int i = 0; i < starCount; i++) {
                cStarRecord_s0102_5840* star = stars[i];
                if (!star)
                    continue;
                EA::ArgScript::Output(mpFormatParser, "\tStar: %ls\n", star->GetName().mpBegin);
                eastl::vector_s0102_5840<cPlanetRecord_s0102_5840*>& planets = star->GetPlanetRecords();
                int planetCount = (int)planets.size();
                for (int j = 0; j < planetCount; j++) {
                    cPlanetRecord_s0102_5840* planet = planets[j];
                    if (empire->OwnsPlanet(planet))
                        EA::ArgScript::Output(mpFormatParser, "\t\tPlanet: %ls\n", planet->mpName);
                }
            }
        }

        // "listempires record": star-record ownership report.
        if (!args->HasFlag("record"))
            return;
        eastl::map_s0102_5840<uint32_t, cEmpire_s0102_5840*>& empireMap = StarManager()->mEmpires;
        eastl::map_s0102_5840<uint32_t, uint32_t> starsPerEmpire;
        eastl::vector_s0102_5840<tEmpireStarBucket>& buckets = StarManager()->mStarBuckets;
        for (tEmpireStarBucket* bucket = buckets.begin(); bucket != StarManager()->mStarBuckets.end(); bucket++) {
            unsigned int n = bucket->mStars.size();
            for (unsigned int i = 0; i < n; i++) {
                cStarRecord_s0102_5840* star = bucket->mStars[i];
                if (star->GetEmpireID() != (uint32_t)-1 && star->GetEmpireID() != 0) {
                    uint32_t empireID = star->GetEmpireID();
                    starsPerEmpire[empireID]++;
                }
            }
        }
        EA::ArgScript::Output(mpFormatParser, "Star Record Report\n==================\n");
        EA::ArgScript::Output(mpFormatParser, "Number of empires: %d\n", empireMap.size());
        EA::ArgScript::Output(mpFormatParser, "Number of uniques empire ids found: %d\n", starsPerEmpire.size());
        int minSize = 999999;
        int maxSize = 0;
        unsigned int total = 0;
        eastl::rbtree_iterator_s0102_5840<uint32_t, uint32_t> rit;
        for (rit.mpNode = starsPerEmpire.begin_node(); rit.mpNode != starsPerEmpire.end_node(); ++rit) {
            uint32_t empireID = rit.mpNode->first;
            int size = (int)rit.mpNode->second;
            if (empireID == (uint32_t)-1 || empireID == 0)
                continue;
            if (size != 0 && size != 1) {
                if (minSize > size)
                    minSize = size;
                if (maxSize < size)
                    maxSize = size;
            }
            total += size;
        }
        EA::ArgScript::Output(mpFormatParser, "Average Empire Size: %d\n", starsPerEmpire.size() ? total / starsPerEmpire.size() : 0);
        EA::ArgScript::Output(mpFormatParser, "Min Empire Size: %d\n", empireMap.size());   // (sic) prints the empire count
        eastl::map_s0102_5840<int, int> histogram;
        for (rit.mpNode = starsPerEmpire.begin_node(); rit.mpNode != starsPerEmpire.end_node(); ++rit) {
            int size = (int)rit.mpNode->second;
            histogram[size]++;
        }
        eastl::rbtree_iterator_s0102_5840<int, int> hit;
        for (hit.mpNode = histogram.begin_node(); hit.mpNode != histogram.end_node(); ++hit)
            EA::ArgScript::Output(mpFormatParser, "%d empires with %d stars\n", hit.mpNode->second, hit.mpNode->first);
        for (hit.mpNode = histogram.begin_node(); hit.mpNode != histogram.end_node(); ++hit)
            EA::ArgScript::Output(mpFormatParser, "%d,%d\n", hit.mpNode->first, hit.mpNode->second);
        (void)maxSize;
        (void)minSize;
        return;
    }

    if (args->HasFlag("dumprel"))
        return;

    if (args->HasFlag("asteroids")) {
        gbDebugAsteroids = !gbDebugAsteroids;
        return;
    }

    if ((opt = args->OptionArguments("debug", 1)) != 0) {
        eastl::string what(opt[0]);
        if (what == "count" || what == "counts" || what == "c")
            gbDebugCounts = !gbDebugCounts;
        else if (what == "relationship" || what == "relationships" || what == "r")
            gbDebugRelationships = !gbDebugRelationships;
        else if (what == "planet" || what == "planets" || what == "p")
            gbDebugPlanets = !gbDebugPlanets;
        else if (what == "powerLevel" || what == "power")
            gbDebugPowerLevel = !gbDebugPowerLevel;
        else if (what == "awareness" || what == "a")
            gbDebugAwareness = !gbDebugAwareness;
        else if (what == "explosions" || what == "e")
            gbDebugExplosions = !gbDebugExplosions;
        else if (what == "hazards" || what == "hazard" || what == "h")
            gbDebugHazards = !gbDebugHazards;
        return;
    }

    if ((opt = args->OptionArguments("wildlife", 1)) != 0) {
        float radius = mpFormatParser->ParseFloat(opt[0]);
        eastl::sim_string typeNames[7] = { "Astrd", "Gas G", "Barren", "t1", "t2", "t3", "ArtDir" };
        eastl::vector_s0102_5840<eastl::vector_s0102_5840<int> > plants;
        eastl::vector_s0102_5840<eastl::vector_s0102_5840<int> > animals;
        for (int k = 7; k; k--) {
            plants.push_back(eastl::vector_s0102_5840<int>(10, 0));
            animals.push_back(eastl::vector_s0102_5840<int>(10, 0));
        }
        eastl::vector_s0102_5840<cStarRecord_s0102_5840*> stars;
        tStarSearchCriteria_s0102_5840 criteria;
        criteria.mMaxDistance = radius;
        StarManager()->GetStarRecords(cSPLivingUniverse::GetActiveStar()->GetPosition(), criteria, stars);
        int starCount = (int)stars.size();
        for (int i = 0; i < starCount; i++) {
            cStarRecord_s0102_5840* star = stars[i];
            StarManager()->ActivatePlanetRecordsForQuery(star, 0);
            eastl::vector_s0102_5840<cPlanetRecord_s0102_5840*>& planets = star->GetPlanetRecords();
            int planetCount = (int)planets.size();
            for (int j = 0; j < planetCount; j++) {
                StarManager()->ActivatePlanet(planets[j], 0);
                cPlanetRecord_s0102_5840* planet = planets[j];
                plants[planet->mType][planet->mPlantSpecies.size()]++;
                planet = planets[j];
                animals[planet->mType][planet->mAnimalSpecies.size()]++;
            }
        }
        EA::ArgScript::Output(mpFormatParser, "\n");
        EA::ArgScript::Output(mpFormatParser, "                             plants                               creatures  \n");
        EA::ArgScript::Output(mpFormatParser, "type  |#    |  0   1   2   3   4   5   6   7   8   9|  0   1   2   3   4   5   6   7   8   9\n");
        EA::ArgScript::Output(mpFormatParser, "------+-----+---------------------------------------+----------------------------------------\n");
        for (int type = 0; type < 7; type++) {
            int* p = plants[type].mpBegin;
            int* a = animals[type].mpBegin;
            int planetCount = p[2] + p[3] + p[4] + p[5] + p[6] + p[7] + p[8] + p[9] + p[0] + p[1];
            EA::ArgScript::Output(mpFormatParser,
                   "%6s|%5d|%3d %3d %3d %3d %3d %3d %3d %3d %3d %3d|%3d %3d %3d %3d %3d %3d %3d %3d %3d %3d\n",
                   typeNames[type].c_str(), planetCount,
                   p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9],
                   a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]);
        }
        EA::ArgScript::Output(mpFormatParser, "------+-----+---------------------------------------+----------------------------------------\n");
        return;
    }

    if ((opt = args->OptionArguments("dump", 1)) != 0) {
        eastl::string what(opt[0]);
        if (what == "planets") {
            int zero = 0;
            eastl::vector_s0102_5840<int> starsPerTech(6, zero);
            eastl::vector_s0102_5840<cStar_s0102_5840*>& allStars = StarManager()->mStars;
            int starCount = (int)allStars.size();
            for (int i = 0; i < starCount; i++)
                starsPerTech[allStars[i]->mpStarRecord->GetTechLevel()]++;

            zero = 0;
            eastl::vector_s0102_5840<int> planetsPerType(7, zero);
            zero = 0;
            eastl::vector_s0102_5840<int> planetsPerTech(6, zero);
            eastl::vector_s0102_5840<eastl::vector_s0102_5840<int> > typePerTech;
            for (int k = 7; k; k--) {
                eastl::vector_s0102_5840<int> row(6, 0);
                typePerTech.push_back(row);
            }
            eastl::vector_s0102_5840<cPlanet_s0102_5840*>& allPlanets = StarManager()->mPlanets;
            int planetCount = (int)allPlanets.size();
            for (int i = 0; i < planetCount; i++) {
                cPlanet_s0102_5840* planet = allPlanets[i];
                int type = planet->GetType();
                int tech = planet->GetTechLevel();
                planetsPerType[type]++;
                planetsPerTech[tech]++;
                typePerTech[type][tech]++;
            }
            EA::ArgScript::Output(mpFormatParser, "\n");
            EA::ArgScript::Output(mpFormatParser, "Tech level   |  Stars Planets | Asteroids Gas Giants     T0     T1     T2     T3\n");
            EA::ArgScript::Output(mpFormatParser, "-------------+----------------+-------------------------------------------------\n");
            for (int tech = 0; tech < 6; tech++) {
                eastl::string name = GameNounManager()->GetTechLevelName(tech);
                EA::ArgScript::Output(mpFormatParser, "%12s | %6d %7d | %9d %10d %6d %6d %6d %6d\n",
                       name.c_str(), starsPerTech[tech], planetsPerTech[tech],
                       typePerTech[0][tech], typePerTech[1][tech], typePerTech[2][tech],
                       typePerTech[3][tech], typePerTech[4][tech], typePerTech[5][tech]);
            }
            EA::ArgScript::Output(mpFormatParser, "-------------+----------------+-------------------------------------------------\n");
            EA::ArgScript::Output(mpFormatParser, "Totals       | %6d %7d | %9d %10d %6d %6d %6d %6d\n",
                   starCount, planetCount,
                   planetsPerType[0], planetsPerType[1], planetsPerType[2],
                   planetsPerType[3], planetsPerType[4], planetsPerType[5]);
            EA::ArgScript::Output(mpFormatParser, "-------------+----------------+-------------------------------------------------\n");
            EA::ArgScript::Output(mpFormatParser, "                                Asteroids Gas Giants     T0     T1     T2     T3\n");
            EA::ArgScript::Output(mpFormatParser, "\n");
        }
        return;
    }

    if ((opt = args->OptionArguments("gotoSave", 1)) != 0) {
        if (cSPLivingUniverse::GetUniverseContext() != 2)
            return;
        int index = mpFormatParser->ParseInt(opt[0]);
        if (index >= (int)StarManager()->mSaveStars.size())
            return;
        cStarRecord_s0102_5840* star = StarManager()->mSaveStars[index];
        if (star)
            GoToStar(star);
        return;
    }

    if (args->HasFlag("oursystem") || args->HasFlag("sol")) {
        if (cSPLivingUniverse::GetUniverseContext() == 2)
            GoToStar(StarManager()->GetHomeStar());
        return;
    }

    if ((opt = args->OptionArguments("flyto", &count, 1, 0x7fffffff)) != 0) {
        if (cSPLivingUniverse::GetUniverseContext() != 2)
            return;
        int starType = 0;
        int techLevel = 0;
        eastl::string where(opt[0]);
        where.make_lower();

        if (where == "pos") {
            float x = mpFormatParser->ParseFloat(opt[1]);
            float y = mpFormatParser->ParseFloat(opt[2]);
            Vector3 position;
            GalaxyCoordsToPosition(x, y, position);
            tStarSearchCriteria_s0102_5840 criteria;
            criteria.mStarTypes &= ~0xeu;
            cStarRecord_s0102_5840* star = StarManager()->FindClosestStar(position, criteria);
            if (star)
                GoToStar(star);
        }

        if (where == "archetype") {
            eastl::string archetype(opt[1]);
            archetype.make_lower();
            unsigned int index;
            for (index = 0; index < 8; index++) {
                if (strcmp(archetype.c_str(), gArchetypeNames[index]) == 0)
                    break;
            }
            if (index < 8) {
                eastl::vector_s0102_5840<EA::InlineRef<cStarRecord_s0102_5840> > homes;
                eastl::map_s0102_5840<uint32_t, cEmpire_s0102_5840*>& empires = StarManager()->GetEmpireMap();
                eastl::rbtree_iterator_s0102_5840<uint32_t, cEmpire_s0102_5840*> it;
                for (it.mpNode = empires.begin_node(); it.mpNode != empires.end_node(); ++it) {
                    cEmpire_s0102_5840* empire = it.mpNode->second;
                    if (empire->mArchetype == (int)index) {
                        EA::InlineRef<cStarRecord_s0102_5840> home(empire->GetHomeStarRecord());
                        homes.push_back(home);
                    }
                }
                if (!homes.empty()) {
                    gpCompareStarPosition = &cSPLivingUniverse::GetActiveStarRecord()->GetPosition();
                    eastl::sort(homes.begin(), homes.end(), CompareStarRecordDistance);
                    GoToStar(homes[0].get());
                }
            }
        }

        if (where == "starter") {
            eastl::string16_s0102_5840 name = EA::ConvertToString16(opt[1], -1);
            eastl::vector_s0102_5840<cStarRecord_s0102_5840*>& stars = StarManager()->GetStarRecordList();
            int starCount = (int)stars.size();
            for (int i = 0; i < starCount; i++) {
                cStarRecord_s0102_5840* star = stars[i];
                if (EA::Locale::StringEqualsNoCase(&star->GetName(), &name)) {
                    GoToStar(star);
                    break;
                }
            }
        }

        if (where == "sol" || where == "oursystem") {
            GoToStar(StarManager()->GetHomeStar());
            return;
        }
        if (where == "home") {
            GoToStar(cSPLivingUniverse::GetPlayerEmpire()->GetHomeStarRecord());
            return;
        }
        if (where == "star") {
            if (count > 1) {
                eastl::string16_s0102_5840 name = EA::ConvertToString16(opt[1], -1);
                cStarRecord_s0102_5840* star = StarManager()->FindStarByName(name.c_str());
                if (star)
                    GoToStar(star);
            }
            return;
        }

        if (where == "blackhole" || where == "bh")
            starType = 2;
        else if (where == "protoplanetary" || where == "pp")
            starType = 3;
        else if (where == "galacticcore" || where == "gc" || where == "core")
            starType = 1;
        else if (where == "oo")
            starType = 7;
        else if (where == "og" || where == "go")
            starType = 8;
        else if (where == "om" || where == "mo")
            starType = 9;
        else if (where == "gg")
            starType = 10;
        else if (where == "gm" || where == "mg")
            starType = 11;
        else if (where == "mm")
            starType = 12;
        else if (where == "civilization" || where == "civ")
            techLevel = 4;
        else if (where == "tribe")
            techLevel = 2;
        else if (where == "empire" || where == "space")
            techLevel = 5;
        else if (where == "grob" || where == "grox") {
            const Vector3& here = cSPLivingUniverse::GetActiveStarRecord()->GetPosition();
            eastl::vector_s0102_5840<cStarRecord_s0102_5840*>& groxStars = StarManager()->GetGrox()->GetStars();
            cStarRecord_s0102_5840* closest = 0;
            float closestDistance = 3.402823466e+38F;
            for (cStarRecord_s0102_5840** it = groxStars.mpBegin; it != groxStars.mpEnd; it++) {
                cStarRecord_s0102_5840* star = *it;
                const Vector3& p = star->GetPosition();
                float dx = p.x - here.x;
                float dy = p.y - here.y;
                float dz = p.z - here.z;
                float distance = dz * dz + dy * dy + dx * dx;
                if (closestDistance > distance) {
                    closestDistance = distance;
                    closest = star;
                }
            }
            if (closest)
                GoToStar(closest);
        }

        if (starType || techLevel) {
            cSpaceshipUFO* ufo = GetUFOSimulator()->GetUFO();
            tStarSearchCriteria_s0102_5840 criteria;
            criteria.mMinDistance = 0.0f;
            if (starType)
                criteria.SetStarType(starType);
            if (techLevel)
                criteria.SetTechLevel(techLevel);
            cStarRecord_s0102_5840* star = StarManager()->FindClosestStar(ufo->mSpatial.GetPosition(), criteria);
            if (star)
                GoToStar(star);
        }

        if (where == "rare") {
            cSpaceshipUFO* ufo = GetUFOSimulator()->GetUFO();
            tStarSearchCriteria_s0102_5840 criteria;
            criteria.mMinDistance = 0.0f;
            criteria.mFlags = 2;
            cStarRecord_s0102_5840* star = StarManager()->FindClosestStar(ufo->mSpatial.GetPosition(), criteria);
            if (star)
                GoToStar(star);
        }
        return;
    }

    if (args->HasFlag("wormhole")) {
        if (cSPLivingUniverse::GetUniverseContext() != 1)
            return;
        if (cSPLivingUniverse::GetActiveStar()->GetType() != 2)
            return;
        AppModeSpace()->TransitionThroughWormhole();
        return;
    }

    if ((opt = args->OptionArguments("setarchetype", 1)) != 0) {
        cPlanet_s0102_5840* planet = cSPLivingUniverse::GetActivePlanet();
        if (planet->GetTechLevel() != 5) {
            EA::ArgScript::Output(mpFormatParser, "This command is usable only when you are at empire planets\n");
            return;
        }
        cEmpire_s0102_5840* empire = planet->GetEmpire();
        int archetype;
        if (_stricmp(opt[0], "warrior") == 0)
            archetype = 0;
        else if (_stricmp(opt[0], "trader") == 0)
            archetype = 1;
        else if (_stricmp(opt[0], "scientist") == 0)
            archetype = 2;
        else if (_stricmp(opt[0], "shaman") == 0)
            archetype = 3;
        else if (_stricmp(opt[0], "bard") == 0)
            archetype = 4;
        else if (_stricmp(opt[0], "zealot") == 0)
            archetype = 5;
        else if (_stricmp(opt[0], "diplomat") == 0)
            archetype = 6;
        else if (_stricmp(opt[0], "ecologist") == 0)
            archetype = 7;
        else if (_stricmp(opt[0], "grob") == 0 || _stricmp(opt[0], "grox") == 0)
            archetype = 8;
        else {
            EA::ArgScript::Output(mpFormatParser, "Valid archetypes: warrior, trader, scientist, shaman, bard, zealot, diplomat, ecologist, grob,\n");
            return;
        }
        empire->mArchetype = archetype;
        EA::ArgScript::Output(mpFormatParser, "Succesfully changed archetype of %ls to %s\n", empire->GetName(), opt[0]);
        return;
    }

    if ((opt = args->OptionArguments("setempiretrait", 1)) != 0) {
        cPlanet_s0102_5840* planet = cSPLivingUniverse::GetActivePlanet();
        if (planet->GetTechLevel() != 5) {
            EA::ArgScript::Output(mpFormatParser, "This command is usable only when you are at empire planets\n");
            return;
        }
        cEmpire_s0102_5840* empire = planet->GetEmpire();
        int trait;
        if (_stricmp(opt[0], "Stingy") == 0)
            trait = 1;
        else if (_stricmp(opt[0], "Generous") == 0)
            trait = 2;
        else if (_stricmp(opt[0], "AccidentProne") == 0)
            trait = 3;
        else {
            EA::ArgScript::Output(mpFormatParser, "Valid traits: Stingy, Generous, AccidentProne\n");
            return;
        }
        empire->mTrait = trait;
        EA::ArgScript::Output(mpFormatParser, "Succesfully changed trait of %ls to %s\n", empire->GetName(), opt[0]);
        return;
    }

    if (args->OptionArguments("drone", 0)) {
        if (cSPLivingUniverse::GetUniverseContext() != 0)
            return;
        cCivilization_s0102_5840* civ = GameNounManager()->GetPlayerCivilization();
        if (!civ)
            return;
        ResourceKey modelKey = civ->GetModelTypeKey(GetVehicleType(0, 2));
        Math::Vector3 position(GetUFOSimulator()->GetUFO()->mSpatial.GetPosition());
        Math::Quaternion orientation;
        orientation = GetUFOSimulator()->GetUFO()->mSpatial.GetOrientation();
        for (int i = 4; i; i--) {
            EA::AutoRefCount_s0102_5840<cVehicle_s0102_5840> vehicle(GameNounManager()->CreateVehicle());
            cVehicle_s0102_5840* v = vehicle.get();
            if (v) {
                v->Init(2, 0, modelKey);
                v->SetDrone(true);
                v->mSpatial.SetPosition(position);
                v->mSpatial.SetOrientation(orientation);
                civ->AddVehicle(v);
            }
        }
        return;
    }

    if (args->OptionArguments("forceautosave", 0)) {
        gbForceAutosave = !gbForceAutosave;
        return;
    }

    if (args->HasFlag("clearplanet")) {
        cPlanet_s0102_5840* planet = cSPLivingUniverse::GetActivePlanet();
        if (planet && cSPLivingUniverse::GetUniverseContext() != 0) {
            cPlanetGenerator* generator = PlanetGenerator();
            generator->RemoveTerrain(planet->mpPlanetData->GetTerrainID());
            planet->ClearCities();
            planet->ClearVehicles();
            planet->mpPlanetData->mBuildings.Clear();
            eastl::vector_s0102_5840<void*>& cities = planet->mpPlanetData->mpCityList;
            while (cities.mpBegin != cities.mpEnd) {
                operator delete[](cities.mpEnd[-1]);
                cities.mpEnd--;
            }
            RebuildPlanetData(planet->mpPlanetData, planet->GetTechLevel());
            planet->SetDirty(true);
            return;
        }
        cSPLivingUniverse::GetUniverseContext();   // result unused (stripped debug output)
        return;
    }

    if (args->HasFlag("taketurn")) {
        AppModeSpace()->mpTurnUpdater->mbTurnPending = false;
        AppModeSpace()->mpTurnUpdater->mbTurnStarted = false;
        AppModeSpace()->mpTurnUpdater->Update(100000000);
        return;
    }

    if ((opt = args->OptionArguments("runcinematic", &count, 1, 2)) != 0) {
        eastl::string name(opt[0]);
        CinematicManager()->PlayCinematic(name.c_str(), 1, 1, 0, 0, 0);
        return;
    }

    if ((opt = args->OptionArguments("rename", &count, 2, 2)) != 0) {
        eastl::string what(opt[0]);
        eastl::string newName(opt[1]);
        if (what == "planet") {
            cPlanetRecord_s0102_5840* planet = cSPLivingUniverse::GetActivePlanetRecord();
            if (planet)
                planet->SetName(EA::ConvertToString16(newName));
        } else if (what == "star") {
            cStarRecord_s0102_5840* star = cSPLivingUniverse::GetActiveStarRecord();
            if (star)
                star->SetName(EA::ConvertToString16(newName));
        }
        return;
    }

    if ((opt = args->OptionArguments("planet", &count, 1, 1)) != 0) {
        eastl::string name(opt[0]);
        cTypeGroupFilter filter(0xb1b104, SPIDFromName(name.c_str()));
        eastl::vector_s0102_5840<ResourceKey> keys;
        ResourceManager()->GetResourceKeyList(keys, &filter, 0);
        if (keys.mpBegin == keys.mpEnd) {
            EA::ArgScript::Output(mpFormatParser, "Planet script %s not found\n", eastl::vararg(name));
        } else {
            gForcedPlanetScript = keys.mpBegin[0];
            gForcedPlanetScriptFlags = 0;
            gbDebugPlanets = true;
            EA::ArgScript::Output(mpFormatParser, "Planet script %s is on deck\n", eastl::vararg(name));
        }
        return;
    }

    if (args->HasFlag("regen_planet")) {
        if (!cSPLivingUniverse::GetActivePlanet())
            return;
        if (cSPLivingUniverse::GetUniverseContext() != 1)
            return;
        uint32_t seed = cSPLivingUniverse::GetActivePlanet()->GetSeed();
        int script = RandomInt(PlanetGenerator()->GetTerrainScript(seed));
        eastl::string command;
        command.sprintf("forceplanet %d %d %u", seed, script, RandomInt(0xfffffff));
        CheatManager()->ExecuteCommand(command.c_str());
        command.sprintf("space -clearplanet");
        CheatManager()->ExecuteCommand(command.c_str());
        return;
    }

    if (args->HasFlag("listcomm")) {
        cCommManager* comm = CommManager();
        int eventCount = (int)comm->mEvents.size();
        for (int i = 0; i < eventCount; i++) {
            EA::AutoRefCount_s0102_5840<cCommEvent> event(*(EA::AutoRefCount_s0102_5840<cCommEvent>*)&comm->mEvents.mpBegin[i]);
            cCommEvent* e = event.get();
            if (!e)
                continue;

            eastl::string16_s0102_5840 planetName((eastl::allocator_s0102_5840()));
            cPlanetRecord_s0102_5840* planet = StarManager()->GetPlanetRecord(e->mPlanetID);
            planetName = planet ? planet->GetName() : eastl::string16_s0102_5840(L"None");

            eastl::string16_s0102_5840 starName((eastl::allocator_s0102_5840()));
            cStarRecord_s0102_5840* star;
            starName = (planet && (star = planet->GetStarRecord()) != 0) ? star->GetName() : eastl::string16_s0102_5840(L"None");

            eastl::string16_s0102_5840 empireName((eastl::allocator_s0102_5840()));
            cEmpire_s0102_5840* empire = StarManager()->GetEmpireByID(e->GetSourceEmpireID());
            empireName = empire ? *(const eastl::string16_s0102_5840*)&empire->GetName() : eastl::string16_s0102_5840(L"None");

            eastl::string16_s0102_5840 missionName((eastl::allocator_s0102_5840()));
            if (e->mpMission)
                e->mpMission->GetName(missionName);

            eastl::string16_s0102_5840 fileName((eastl::allocator_s0102_5840()));
            ResourceKey fileKey;
            fileKey.instanceID = 0;
            fileKey.typeID = 0x55ada24;
            fileKey.groupID = 0x55ada23;
            fileKey.instanceID = e->mFileID;
            ResourceManager()->GetFileName(fileKey, fileName);

            eastl::string16_s0102_5840 galaxy((eastl::allocator_s0102_5840()));
            galaxy = e->mbGalaxy ? L"Y" : L"-";

            EA::ArgScript::Output(mpFormatParser, "%d.\t Planet: %ls \t Star: %ls \t Empire: %ls \n",
                   i, planetName.c_str(), starName.c_str(), empireName.c_str());
            EA::ArgScript::Output(mpFormatParser, "\t Pri: %d \t Galaxy: %ls\n", e->mPriority, galaxy.c_str());
            EA::ArgScript::Output(mpFormatParser, "\t FileID: %ls\t DialogID: 0x%X\n\t Mission: %ls\n",
                   fileName.c_str(), e->mDialogID, missionName.c_str());
            EA::ArgScript::Output(mpFormatParser, "\t Duration (sec): %d \t Elapsed (sec): %d\n",
                   e->mDurationMS / 1000, e->mElapsedMS / 1000);
        }
        return;
    }

    EA::ArgScript::Output(mpFormatParser, "Unknown argument");
}
}}  // namespace SP::nSpaceCheats
