// src/game/SPGonzago/SPSolarSystem.cpp -- migrated from slice(s) s00c86aa0, s00c85a30, s00c84d60, s00c830f0, s01351ae0, s00c84120, s00423960, s00423110 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSolarSystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include <stdarg.h>
#include "SP/cSolarSystem.h"
#include "SP/cCelestialBody.h"
#include "SP/cEmpire.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cHitSphere.h"
#include "SP/cPlanet.h"
#include "SP/cPlanetRecord.h"
#include "SP/cPropertyList.h"
#include "SP/cRelationshipManager.h"
#include "SP/cSPTimer.h"
#include "SP/cTerrainSphere.h"
#include "SP/cTribe.h"
#include "SP/cVarListSerializer.h"
#include "SP/cISerializableObject.h"
#include <math.h>
#include "SP/cString.h"
#include <wctype.h>
#include "SP/cEllipticalOrbit.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cLocalizedString.h"
#include "SP/cMWModel.h"
#include "SP/cIModelWorld.h"

// ---- items of slice s00423110 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Elem38 {
    int data[14];
    void Assign(const Elem38* other);   // 0x00537dc0
};
inline Elem38* CopyElems(Elem38* first, Elem38* last, Elem38* result)
{
    const bool b0 = false;
    const bool b1 = false;
    const bool b2 = false;
    for (; first != last; ++first, ++result)
        result->Assign(first);
    return result;
}
struct Elem38Vector {
    Elem38* mpBegin;
    Elem38* mpEnd;
    Elem38* erase(Elem38* first, Elem38* last);   // 0x004238c0
};
// ---- items of slice s00423110 end

// ---- items of slice s00423960 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, uint32_t);
#pragma intrinsic(memcpy)
#pragma intrinsic(_InterlockedIncrement)
struct Allocator { const char* mpName; };
void* __cdecl AllocatorAllocate(Allocator* alloc, uint32_t size, uint32_t align, uint32_t offset);  // FUN_0042dee0
void  __cdecl AllocatorDeallocate(void* block);                                                    // EASTL_allocator_deallocate
struct Counted { char pad[0x40]; int mnRefCount; void Release(); };  // count at +0x40, plain; Release = FUN_0040f360
typedef Counted* CountedPtr;
struct ByteBuffer
{
    char* mBegin;
    char* mEnd;
    char* mCapacity;
    Allocator mAllocator;

    ByteBuffer(uint32_t n, const Allocator* /*alloc*/);
};
CountedPtr* __cdecl CopyBackwardCounted(CountedPtr* first, CountedPtr* last, CountedPtr* destEnd);  // FUN_0042e6e0
struct CountedPtrVector
{
    CountedPtr* mBegin;
    CountedPtr* mEnd;
    CountedPtr* mCapacity;
    Allocator mAllocator;

    void DoInsertValue(CountedPtr* pos, CountedPtr* value);
};
struct Record56
{
    uint32_t data[14];
    Record56* CopyConstruct(const Record56* src);   // FUN_0040ce80
    void Assign(const Record56* src);               // FUN_00537dc0
};
Record56* __cdecl   UninitializedCopyRecords(Record56* first, Record56* last, Record56* dest);  // FUN_00429ce0
struct Record56Vector
{
    Record56* mBegin;
    Record56* mEnd;
    Record56* mCapacity;
    Allocator mAllocator;

    void DoInsertValue(Record56* pos, const Record56* value);
};
// ---- items of slice s00423960 end

// ---- items of slice s00c84120 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace Simulator {
struct cPtrVector {
    void* mpBegin;                                           // +0x00
    void* mpEnd;                                             // +0x04
    void* mpCapacity;                                        // +0x08
};
}
namespace Simulator {
struct cSolarSystem {
    void*       mpVtable0;                                   // +0x00
    uint32_t    mRefCount;                                   // +0x04
    void*       mpVtable1;                                   // +0x08
    void*       mpOwnerStar;                                 // +0x0c
    cPtrVector  mPlanets;                                    // +0x10
    uint32_t    mPad1c;                                      // +0x1c
    uint32_t    mPad20;                                      // +0x20
    cPtrVector  mCelestialBodies;                            // +0x24
    uint32_t    mPad30;                                      // +0x30
    uint32_t    mPad34;                                      // +0x34
    cPtrVector  mModels;                                     // +0x38
    void*       mpStar1;                                     // +0x44
    void*       mpStar2;                                     // +0x48

    cSolarSystem();
};
}
// ---- items of slice s00c84120 end

// ---- items of slice s01351ae0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
struct PropDesc {
    const char* mName;   // +0x00
    u32 mHash;   // +0x04
    u32 mType;   // +0x08
    u32 mPad0C;   // +0x0c
    u32 mPad10;   // +0x10
    u32 mPad14;   // +0x14
    u32 mZero18;   // +0x18
    u32 mZero1C;   // +0x1c
    void* mDefault;   // +0x20
    void* mFn24;   // +0x24
    void* mFn28;   // +0x28
    void* mFn2C;   // +0x2c
    void* mFn30;   // +0x30
    void* mFn34;   // +0x34
    void* mFn38;   // +0x38
};
// ---- items of slice s01351ae0 end

// ---- items of slice s00c830f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" uint8_t g_1579d78;                             // 0x01579d78
extern float g_147346c;                                   // 0x0147346c
void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);                                   // 0x00f473a0
void operator delete[](void* p);                                                 // 0x00f47380
template <class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    intrusive_ptr& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    // releases the current object and hands out the slot for an out parameter
    T** reset_out()
    {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};
struct cEmpire {
    uint32_t pad00[0x84 / 4];
    uint32_t mPoliticalID;      // +0x84
};
struct cPlanetRecord {
    struct Elem12 { uint32_t a, b, c; };
    uint32_t pad00[0x2c / 4];
    uint32_t mFlags;            // +0x2c
    uint32_t pad30[(0xd0 - 0x30) / 4];
    Elem12*  mpPlantsBegin;     // +0xd0
    Elem12*  mpPlantsEnd;       // +0xd4
    uint32_t GetID();           // 0x00ce6950
    uint32_t PlantCount() { return (uint32_t)(mpPlantsEnd - mpPlantsBegin); }
};
struct ByteVector {                                          // eastl::vector, sp_vector_allocator
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    const char* mpAllocName;
    ~ByteVector() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin); }
};
struct ResourceKey;
struct cPlanet {
    uint32_t pad00[0x13c / 4];
    cPlanetRecord* mpPlanetRecord;   // +0x13c
    ResourceKey* FUN_00c713e0();     // 0x00c713e0
    int      GetTScore();             // 0x00c70880
    float    GetAtmosphereScore();    // 0x00c709d0
    float    GetTemperatureScore();   // 0x00c70a20
    bool     FUN_00c70a70();          // 0x00c70a70
    void     FUN_00c70aa0(float f);   // 0x00c70aa0
    void     SetNeedsReset(int b);    // 0x00c70de0
    int      GetTechLevel();          // 0x00c70e00
    void     SetEcosystemStage(int s);// 0x00c71550
    float    GetWaterScore();         // 0x00c71d30
    cEmpire* GetOwner();              // 0x00c71e30
    ByteVector GetCities();           // 0x00c73520
};
struct cTerrainEntry {
    uint32_t pad00[0xa0 / 4];
    signed char mInitialLevel;        // +0xa0
    signed char mInitialPlants;       // +0xa1
};
struct cTerrainEntryMap {
    cTerrainEntry& operator[](const uint32_t& key);   // 0x00ba4e60
};
struct cTerrainSphere {
    uint32_t pad00[0x11c0 / 4];
    cTerrainEntryMap mEntries;        // +0x11c0
    void SetTerraformLevel(uint32_t planetID, int level);   // 0x00c83090
    bool HasMusic(uint32_t id);       // 0x00c772c0
    void PlayMusic(uint32_t id);      // 0x00c77bf0
};
struct cGameData;
struct ILocatorSub {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
    virtual void v14();
    virtual void SetTerraformState(float f, uint32_t empireID, int a, void* reason, int b);   // +0x18
};
struct cCreatureLike {
    uint32_t pad00[0x120 / 4];
    ILocatorSub mSub;                 // +0x120
    uint32_t pad124[(0x158 - 0x124) / 4];
    float    mF158;                   // +0x158
};
struct cGameData {
    virtual int AddRef();
    virtual int Release();            // +0x04
virtual void v08();
virtual void* v0c(uint32_t type);
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
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
    virtual void va8();
    virtual cCreatureLike* AsCreature();   // +0xac
    void FUN_00bdc050();              // 0x00bdc050
};
struct GDIter {
    cGameData** mp;
    __forceinline GDIter(cGameData** p) : mp(p) {}
    __forceinline GDIter(const GDIter& x) : mp(x.mp) {}
};
struct false_type {};
GDIter FUN_00829110(GDIter first, GDIter last, GDIter dest, false_type);   // 0x00829110 uninitialized_copy (AddRefs)
struct sp_allocator { const char* mpName; };
struct GameDataPtrVector {
    cGameData** mpBegin;
    cGameData** mpEnd;
    cGameData** mpCapacity;
    sp_allocator mAllocator;

    void DoInit(int n, const sp_allocator& a);   // 0x00b93c60 (VectorBase(n, allocator), out of line)

    __forceinline GameDataPtrVector(const GameDataPtrVector& x, int)
    {
        DoInit((int)(x.mpEnd - x.mpBegin), x.mAllocator);
        mpEnd = FUN_00829110(GDIter(x.mpBegin), GDIter(x.mpEnd), GDIter(mpBegin), false_type()).mp;
    }
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
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct tGameDataVector {
    bool              mbDirty;   // +0x0
    GameDataPtrVector mData;     // +0x4
};
struct cGameNounManager {
    tGameDataVector* GetGameDataVector(void (*create)(), void (*f2)(), void (*filter)(), void (*f4)(),
                                       uint32_t typeID);   // 0x00b21340
    void RemoveNoun(cGameData* noun);                       // 0x00b225d0
    cGameData* CreateNoun(uint32_t typeID);                 // 0x00b20c60
    void RemoveNounsOfType(uint32_t typeID);                // 0x00b22650
    void FUN_00b25ee0();                                    // 0x00b25ee0
    cTerrainSphere* GetCurrentTerrainSphere();              // 0x00f67d90
};
cGameNounManager* NounManager();                            // 0x00b3d300
namespace EA {
namespace COM {
struct IUnknown32_s00c8_30f0 {
    virtual int AddRef();
    virtual int Release();
};  // namespace COM
}
}
namespace EA {
namespace Swarm {
struct cIVisualEffect_s00c8_30f0 {
    virtual int AddRef();
    virtual int Release();
    virtual bool Start(int flags);
    virtual void v0c();
    virtual bool IsRunning();
};  // namespace Swarm
}
}
namespace EA {
template <typename T> struct AutoRefCount_s00c8_30f0 {
    T* mpObject;
    AutoRefCount_s00c8_30f0* AsPPTypeParam();                        // 0x00a16f40
    T* operator->() const { return mpObject; }
};
}
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
struct cSPVector3_s00c8_30f0 { float x, y, z; };
struct cHitSphere {
    virtual int AddRef();
    virtual int Release();
    void SetTransform(cSPVector3_s00c8_30f0* position, float size);  // 0x00c3f160
    void SetRange(float minValue, float maxValue);        // 0x00c3f1b0
    void SetOwner(void* owner);                           // 0x00c3f2d0
};
struct cCelestialBody : cGameData {
    uint8_t    pad004[0xa0 - 4];
    cSPVector3_s00c8_30f0 mPosition;                                 // +0xa0
    uint8_t    pad0ac[0xc0 - 0xac];
    void*      mEffect;                                   // +0xc0
    intrusive_ptr<cHitSphere> mHitSphere;                 // +0xc4
    float      mHitSphereSize;                            // +0xc8
};
struct cPropertyList : EA::COM::IUnknown32_s00c8_30f0 {
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual bool HasKey(uint32_t instanceID, uint32_t groupID);                   // +0x28
    virtual void QueryObject(uint32_t instanceID, uint32_t groupID,
                             EA::COM::IUnknown32_s00c8_30f0** result);                       // +0x2c
};
cPropertyList* PropertyManager();                                         // 0x0067de30
bool GetPropertyAsKey(cPropertyList* list, uint32_t id, ResourceKey& value);  // 0x006a1250
struct StreamSub {
    void* GetIO() { return (**(void* (__thiscall**)(void*))(*(void***)this + 6))(this); }
};
struct StreamObj {
    StreamSub* GetSub() { return (**(StreamSub* (__thiscall**)(void*))(*(void***)this + 8))(this); }
};
struct cVarListSerializer {
    uint32_t mData[0xa14 / 4];
    void Ctor(void* owner, void* name, uint32_t tag);     // 0x00692f90
    bool Serialize(void* stream);                         // 0x00692900
};
bool __cdecl EA_IO_WriteUint32(void* io, const void* p, uint32_t count,
                               int32_t flags);            // 0x0093aa70
struct cISerializableObject {
    virtual int AddRef();
    virtual int Release();
    virtual void vDtor();
    virtual void* AsInterface(uint32_t id);
    virtual bool Write(void* stream);
    virtual void Read(void* stream);
    void* mpOwner;                                        // +0x04
};
struct cSolarSystemPrimary {
    virtual int AddRef();
    virtual int Release();
    uint32_t mRefCount;                                   // +0x04
};
struct cSolarSystem_s00c8_30f0 : cSolarSystemPrimary, cISerializableObject {
    void* mpPlanetsBegin;                                 // +0x10
    void* mpPlanetsEnd;                                   // +0x14
    void* mpPlanetsCapacity;                              // +0x18
    uint32_t mPad1c;                                      // +0x1c
    uint32_t mPad20;                                      // +0x20
    cCelestialBody** mpCelestialBodiesBegin;              // +0x24
    cCelestialBody** mpCelestialBodiesEnd;                // +0x28
    cCelestialBody** mpCelestialBodiesCapacity;           // +0x2c
    uint32_t mPad30;                                      // +0x30
    uint32_t mPad34;                                      // +0x34
    cCelestialBody* mStar1;                               // +0x38
    cCelestialBody* mStar2;                               // +0x3c
    void* mpPtolemaicBegin;                               // +0x40
    void* mpPtolemaicEnd;                                 // +0x44
    void* mpPtolemaicCapacity;                            // +0x48

    cCelestialBody* GetStar(bool primary);
    void ActivateHitSpheres(bool activate);  // 0x00c83fd0 (cSolarSystem::ActivateHitSpheres)
};
struct cStarEffectHost {
    virtual int AddRef();
    virtual int Release();
    virtual void StartEffect(uint32_t id, int flags,
                             EA::AutoRefCount_s00c8_30f0<EA::Swarm::cIVisualEffect_s00c8_30f0>* effect);
};
// ---- items of slice s00c830f0 end

// ---- items of slice s00c84d60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void __cdecl FreeRawBlock(void* block);                                        // 0x00f47380
extern void* __cdecl FUN_00f473a0(uint32_t size, const char* name, int, int, int, int); // 0x00f473a0
extern void* __cdecl FUN_00bd6410(void* memory, int kind);                            // 0x00bd6410
extern void __cdecl FUN_00aea5d0(void* dst, void* src);                               // 0x00aea5d0
extern float __cdecl GetStarRotationRate(void* star);                                 // 0x00c842a0
extern float __cdecl GetStarRadius(void* star);                                       // 0x00c84120
extern float __cdecl GetStarMass(void* star);
extern float __cdecl RandomDoubleUniform();                                           // 0x00e1a5a0
extern int   __cdecl FUN_00b5b800();                            // 0x00b5b800
extern void* __cdecl FUN_00b3d300();                            // 0x00b3d300
extern void* __cdecl FUN_00b1fdb0(void* mgr);                    // 0x00b1fdb0
extern void  __cdecl FUN_00c72770(float f);                     // 0x00c72770
extern void  __cdecl FUN_00c719d0(int mode);                    // 0x00c719d0
extern void* __cdecl FUN_00c71530();                            // 0x00c71530
extern void  __cdecl FUN_00bc30b0(void* v);                     // 0x00bc30b0
extern float __cdecl FUN_00bc2b60(void* v);                     // 0x00bc2b60
extern void  __cdecl FUN_00bc28c0(float f);                     // 0x00bc28c0
extern void  __cdecl FUN_01021740();                            // 0x01021740
extern void* __cdecl FUN_0041ea70(void* prop);                  // 0x0041ea70 (Property::GetFloat)
extern void* __cdecl FUN_00fe8450();                            // 0x00fe8450
extern int*  g_p01694c68;                                       // 0x01694c68
extern int   g_mode_01654c01;                                   // 0x01654c01
extern float g_f01579ea4;                                       // 0x01579ea4
extern float g_f01579d58;                                       // 0x01579d58
extern float g_f01579d5c;                                       // 0x01579d5c
extern float g_f01579d60;                                       // 0x01579d60
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define PAD1 virtual void CAT(pad, __COUNTER__)();
#define PAD4 PAD1 PAD1 PAD1 PAD1
#define PAD8 PAD4 PAD4
#define PAD16 PAD8 PAD8
struct Vector3 {
    float x, y, z;
};
struct WString {                            // eastl::basic_string<wchar_t>
    wchar_t* mpBegin;                       // +0x00
    wchar_t* mpEnd;                         // +0x04
    wchar_t* mpCap;                         // +0x08
    void*    mpPad0c;                       // +0x0c
    void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
};
struct cString_s00c8_4d60 {                            // SP::cString
    uint8_t mData[0x14];
    cString_s00c8_4d60(uint32_t a, uint32_t b, const wchar_t* text);     // 0x006b5770
    const wchar_t* GetText();                                 // 0x006b55c0
    ~cString_s00c8_4d60();                                               // 0x006b5240
};
extern WString* __cdecl PathJoin(WString* out, WString* name, const wchar_t* text);  // 0x0057cba0
struct WString;
struct cGameData_s00c8_4d60 {                          // star-system description shared by the solar system
    uint8_t  pad00[0x34];                   // +0x00 .. +0x33
    void*    mpStarA;                       // +0x34
    void*    mpStarB;                       // +0x38
    bool  IsBinary();                       // 0x00c8b7e0
    WString* GetName();                     // 0x00c8b540
};
struct cAvatar {
    uint8_t pad00[0xc0];                    // +0x00 .. +0xbf
    Vector3 mPosC0;                         // +0xc0
};
struct cProperty {
    uint8_t  pad00[0x12];                   // +0x00 .. +0x11
    uint16_t mType12;                       // +0x12
};
struct cCelestialBody_s00c8_4d60;
struct IBodyComponent {                     // component found by type key on a body
    PAD8 PAD1 PAD1 PAD1
    virtual const Vector3& GetPosition();                 // vtable +0x2c
    int GetState();                                       // 0x00c6ff90
};
struct IBodyData {                          // payload object held at cCelestialBody::mpData64
    PAD1 PAD1 PAD1
    virtual void* QueryComponent(const void* typeKey);    // vtable +0x0c
};
struct IBodyInterface {                     // interface held at cCelestialBody::mpIface0
    virtual void AddRef();                                  // vtable +0x00
    virtual void Release();                                 // vtable +0x04
    PAD16 PAD16 PAD16 PAD16 PAD16 PAD8 PAD1
    virtual void SetVisible(cCelestialBody_s00c8_4d60* body, int on);   // vtable +0x16c
};
struct cCelestialBody_s00c8_4d60 {
    IBodyInterface* mpIface0;               // +0x00
    uint32_t  mBits4;                       // +0x04   bit 15 marks the secondary star
    uint16_t  mFlags8;                      // +0x08
    uint16_t  mCounterA;                    // +0x0a
    Vector3   mPosition;                    // +0x0c
    uint8_t   pad18[0x20];                  // +0x18 .. +0x37
    uint8_t   mKind38;                      // +0x38
    Vector3   mAxis3c;                      // +0x3c
    float     mSwing48;                     // +0x48
    Vector3   mOffset4c;                    // +0x4c
    float     mInclination58;               // +0x58
    uint8_t   pad5c[0x08];                  // +0x5c .. +0x63
    IBodyData* mpData64;                    // +0x64
    uint8_t   pad68[0x38];                  // +0x68 .. +0x9f
    Vector3   mVelocityA0;                  // +0xa0
    float     mRotationAc;                  // +0xac
    WString   mName;                        // +0xb0
    uint8_t   padc0[0x08];                  // +0xc0 .. +0xc7
    float     mRadiusC8;                    // +0xc8
};
struct cPlanet_s00c8_4d60 {
    PAD8 PAD1 PAD1 PAD1                                         // slots 0..10
    virtual const Vector3& GetPosition();                       // vtable +0x2c
    PAD1 PAD1                                                   // slots 12..13
    virtual void SetPosition(const Vector3& p);                 // vtable +0x38
    uint8_t  pad04[0x20];                                       // +0x04 .. +0x23
    void*    mpObj24;                                           // +0x24
    uint8_t  pad28[0x08];                                       // +0x28 .. +0x2f
    Vector3  mPosition30;                                       // +0x30
    uint8_t  pad3c[0x6c];                                       // +0x3c .. +0xa7
    void GetPtolemaicPosition(Vector3& out);                    // 0x00c83a10
};
namespace SP {
class cSPLivingUniverse {
public:
    static cPlanet_s00c8_4d60* GetActivePlanet();                          // 0x01021260
    static int GetUniverseContext();                            // 0x01021080
};
}
namespace SP {
class cSolarSystem_s00c8_4d60 {
public:
    void UpdatePlanet(cPlanet_s00c8_4d60* planet, float dt);               // 0x00c84d60
    void UpdatePlanets(float dt);                               // 0x00c85380
    void InitBinarySystem(WString* name);                       // 0x00c85200
    void GetBinarySuffix();                                     // 0x00c85540

    uint8_t  pad00[0x0c];                                       // +0x00
    cGameData_s00c8_4d60* mpGameData;                                      // +0x0c
    cPlanet_s00c8_4d60** mpPlanetsBegin;                                   // +0x10
    cPlanet_s00c8_4d60** mpPlanetsEnd;                                     // +0x14
    uint8_t  pad18[0x0c];                                       // +0x18
    void**   mpBodies0Begin;                                    // +0x24
    void**   mpBodies0End;                                      // +0x28
    void**   mpBodies0Cap;                                      // +0x2c
    uint8_t  pad30[0x08];                                       // +0x30
    cCelestialBody_s00c8_4d60* mpPrimary;                                  // +0x38
    cCelestialBody_s00c8_4d60* mpSecondary;                                // +0x3c
    cCelestialBody_s00c8_4d60** mpBodiesBegin;                             // +0x40
    cCelestialBody_s00c8_4d60** mpBodiesEnd;                               // +0x44
};
}
extern int   __cdecl FUN_00c70880(cPlanet_s00c8_4d60* planet);             // 0x00c70880 (GetPlanetType)
extern void  __cdecl FUN_00c84950(cPlanet_s00c8_4d60* planet);             // 0x00c84950
extern bool  __cdecl FUN_00c83e40(cPlanet_s00c8_4d60* planet);             // 0x00c83e40
struct IConfig {                            // settings object behind 0x01694c68
    PAD8 PAD1
    virtual bool GetProperty(const void* key, void** out);   // vtable +0x24
};
// ---- items of slice s00c84d60 end

// ---- items of slice s00c85a30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kPi;                                          // 0x01579d48
extern float kTwoPi;                                       // 0x01694c6c
extern float gStarCache[13];                                     // 0x01579d10 (-1.0 = not yet computed)
extern float gBodyColorR, gBodyColorG, gBodyColorB;                // 0x01694c94/98/9c
extern const float kOne;                                           // 0x01485720
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0
inline void* operator new(size_t, void* p) { return p; }
namespace EA {
namespace Random {
class RandomLinearCongruential_s00c8_5a30 { public:
    uint32_t mnSeed;
    uint32_t RandomUint32Uniform(uint32_t nLimit);               // 0x00a68fb0
    double   RandomDoubleUniform();                              // 0x009360d0
};
}
}
extern EA::Random::RandomLinearCongruential_s00c8_5a30 gRandom;            // 0x01601760
struct Vec3c { float x, y, z; };
extern Vec3c kAxisX;                                       // 0x01579d4c (1,0,0)
extern Vec3c kAxisZ;                                       // 0x01579d58 (0,0,1)
struct Property {
    char     pad[0x12];
    unsigned short type;                                         // +0x12 (0xd = float)
    float*   GetFloat();                                         // 0x0041ea70
};
struct PropertyList {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool GetProperty(uint32_t id, Property** out);       // slot 9 (+0x24)
};
extern PropertyList** gStarProperties;                           // 0x01694c54
bool  __cdecl IsGasType(int t);                                  // 0x00c8b450
float __cdecl GetGasValue(int t);                                // 0x00c84420
float __cdecl GetStarTemperature(int t);                         // 0x00c84310
__forceinline float CachedStarValue(int t)
{
    float* p = &gStarCache[t];
    if (*p < 0.0f) {
        float v;
        if (IsGasType(t)) {
            v = GetGasValue(t);
        } else {
            v = 30.0f;
            switch (t) {
            case 1: v = 300.0f; break;
            case 2: case 3: v = 100.0f; break;
            case 4: case 5: case 6: {
                Property* pr;
                PropertyList* pl = gStarProperties[t];
                if (pl && pl->GetProperty(0x383cd6f, &pr) && pr->type == 0xd)
                    v = *pr->GetFloat();
                break;
            }
            }
        }
        *p = v;
    }
    return *p;
}
namespace SP {
class cString_s00c8_5a30 {
public:
    cString_s00c8_5a30(uint32_t tableID, uint32_t instanceID, int a);       // 0x006b5770
    ~cString_s00c8_5a30();                                                  // 0x006b5240
    const wchar_t* GetText();                                    // 0x006b55c0
    uint32_t mData[5];
};
}
struct WString_s00c8_5a30 {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAlloc;
    void assign(const wchar_t* first, const wchar_t* last);      // 0x00423650
    void assign(const WString_s00c8_5a30& o) { assign(o.mpBegin, o.mpEnd); }
    void assign(const wchar_t* p)
    {
        const wchar_t* e = p;
        while (*e) ++e;
        assign(p, p + (e - p));
    }
};
class cStarManager_s00c8_5a30;
struct cStar_s00c8_5a30;
struct cStar_s00c8_5a30
{
    int      GetType();                          // 0x00c8b550
    bool     IsKnown();                          // 0x00c8b7e0 (name guessed)
    bool     HasComets();                        // 0x00c8b800 (name guessed)
    WString_s00c8_5a30* GetName();                          // 0x00c8b540
    char     pad0[0x48];
    cStarManager_s00c8_5a30* mpPlanetManager;               // +0x48
};
class cPlanet_s00c8_5a30;
struct cBodyVisual;
struct cBodyEffect;
struct cSPVector3_s00c8_5a30 { float x, y, z; };
struct cCelestialBody_s00c8_5a30;
template <typename T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& o) : mpObject(o.mpObject) { mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p)
    {
        if (mpObject != p) {
            if (p) p->AddRef();
            T* pOld = mpObject;
            mpObject = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};
struct cEllipticalOrbit_s00c8_5a30 {
    bool  mNullOrbit;                                            // +0x00
    float mPlaneNormal[3];                                       // +0x04
    float mEccentricity;                                         // +0x10
    float mPerihelion[3];                                        // +0x14
    float mPeriod;                                               // +0x20
    char  pad[0x68 - 0x24];
    void  Update();                                              // 0x00fe8450
};
struct cCelestialBody_s00c8_5a30 {
    virtual int AddRef();
    virtual int Release();
    char             pad0[0x34 - 4];
    int              mType;                                      // +0x34
    cEllipticalOrbit_s00c8_5a30 mOrbit;                                     // +0x38 (0x68)
    cSPVector3_s00c8_5a30       mPosition;                                  // +0xa0
    float            mRotationRate;                              // +0xac
    WString_s00c8_5a30          mName;                                      // +0xb0
    cBodyVisual*     mpVisual;                                   // +0xc0
    cBodyEffect*     mpEffect;                                   // +0xc4
    float            mHitSphereSize;                             // +0xc8
    cCelestialBody_s00c8_5a30(int type);                                    // 0x00bd6410
    void Setup();                                                // 0x00bd6300
    void SetBrightness(float value);                             // 0x00bd6590
};
template <typename T> struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    void DoInsertValue(T* position, const T& value);             // 0x00aea5d0
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
struct cSolarSystem_s00c8_5a30 {
    char    pad0[0xc];
    cStar_s00c8_5a30*  mpStar;                                              // +0x0c
    vector<AutoRefCount<cPlanet_s00c8_5a30> > mPlanets;                     // +0x10
    char    pad1[0x24 - 0x1c];
    vector<AutoRefCount<cCelestialBody_s00c8_5a30> > mCelestialBodies;      // +0x24
    char    pad2[0x38 - 0x30];
    AutoRefCount<cCelestialBody_s00c8_5a30> mStarBody;                      // +0x38
    void InitComets();  // 0x00c85a30 (cSolarSystem::InitComets)
    static void InitTuning();                                    // 0x00c86640
    void InitStar(cStar_s00c8_5a30* pStar);                                 // 0x00c86760
    void UpdateBodies(float value);                              // 0x00c86390
};
__forceinline double RandomRange(double lo, double hi)
{
    double v = gRandom.RandomDoubleUniform() * (hi - lo) + lo;
    if (v < hi) {
        if (v >= lo)
            return v;
        return lo;
    }
    return hi;
}
class cPlanet_s00c8_5a30
{
public:
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual void v090();
virtual void v094();
virtual void v098();
virtual void v09c();
virtual void v0a0();
virtual void v0a4();
virtual void v0a8();
virtual void v0ac();
virtual void v0b0();
virtual void v0b4();
virtual void v0b8();
    virtual void AddRef();                       // +0xbc
    virtual void Release();                      // +0xc0
    char    pad00[0x2c - 0x04];
    int32_t m_flags;                             // +0x2c
    float   GetValue(int index);                 // 0x00c70f90
};
struct cStarPlanet { cPlanet_s00c8_5a30* mpPlanet; };
class cStarManager_s00c8_5a30
{
public:
    cPlanet_s00c8_5a30* GetOrActivatePlanet();              // 0x00bb59b0
};
cStarManager_s00c8_5a30* __cdecl SP_StarManager(cStarPlanet* pRecord, cPlanet_s00c8_5a30** out);
struct cPlanetVector
{
    cStarPlanet* mpBegin;
    cStarPlanet* mpEnd;
    cStarPlanet* mpCapacity;
};
cPlanetVector* __cdecl cStarManager_planets(cStarManager_s00c8_5a30* pManager);   // 0x00bba790
float __cdecl GetStarRotationRate(int type);     // 0x00c842a0
class PropertyObject
{
public:
    virtual void f0();
    virtual void Release();                      // +0x04
};
struct RefPtrProperty
{
    PropertyObject* mpObject;
    void release()
    {
        PropertyObject* p = mpObject;
        if (p) {
            mpObject = 0;
            p->Release();
        }
    }
};
struct StarPropertyVector                            // EA vector<RefPtr<Property>> @ 0x01694c54
{
    RefPtrProperty* mpBegin;                         // 0x01694c54
    RefPtrProperty* mpEnd;                           // 0x01694c58
    RefPtrProperty* mpCapacity;                      // 0x01694c5c

    void DoInsertValues(RefPtrProperty* position, int count, const RefPtrProperty& value);  // 0x0042aeb0
    void erase(RefPtrProperty* first, RefPtrProperty* last);                               // 0x00533500
    void resize(uint32_t n)
    {
        uint32_t count = (uint32_t)(mpEnd - mpBegin);
        if (n > count) {
            RefPtrProperty empty = { 0 };
            DoInsertValues(mpEnd, (int)(n - count), empty);
        } else {
            erase(mpBegin + n, mpEnd);
        }
    }
};
class PropertyManager_s00c8_5a30
{
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
    virtual void GetProperty(uint32_t propertyId, uint32_t tableId, RefPtrProperty* out);  // +0x2c
};
PropertyManager_s00c8_5a30* __cdecl SP_PropertyManager();   // 0x0067de30
struct cSPMatrix3_s00c8_5a30 { void Assign(const void* pSource); };          // 0x0041cb40
class cViewer_s00c8_5a30
{
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    void GetCameraLocationInfo(cSPVector3_s00c8_5a30* pos, void*, void*, void*);   // 0x007c3d30
};
void* __cdecl SP_App();                                            // 0x0067dd10
void* __cdecl SP_App_GetViewer(void* pApp);                        // SP::App vtable +0x50
void* __cdecl SP_LivingUniverse_Context();                         // 0x01021080
void* __cdecl FUN_01021260();                                      // 0x01021260
float __cdecl FUN_01034630(int a, float b, int c);                 // 0x01034630
void __cdecl UpdateCometVisuals(void* pSystem, float value);       // 0x00c85380
struct cBodyVisual
{
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual bool IsVisible();                                      // +0x10
    virtual void SetColor(const void* pColor);                     // +0x18
    virtual void SetMatrix(const cSPMatrix3_s00c8_5a30* pMatrix);             // +0x20
};
struct cBodyEffect
{
    void SetEffect(float size, const cSPVector3_s00c8_5a30* pPosition);       // 0x00c3f160
};
extern cSPMatrix3_s00c8_5a30 gBodyOrientation;                                // 0x01694c70
float __cdecl GetStarRadius(int type);                             // 0x00c84120
void  __cdecl InitStarBodyHelper(void* pSystem);                   // 0x00c85540
extern cSPVector3_s00c8_5a30 gSunPosition;                                    // 0x01694c10/14/18
extern StarPropertyVector gStarPropertySlots;    // 0x01694c54 (same block as gStarProperties)
extern RefPtrProperty     gDefaultStarProperty;  // 0x01694c68
// ---- items of slice s00c85a30 end

// ---- items of slice s00c86aa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t   kHitSphereModelGroup;          // 0x01694c1c
extern float      kRockyRadius;                  // 0x01579ea8
extern float      kGasGiantRadius;               // 0x01579eac
struct VObj174;
struct cMWModel;
struct ResourceKey_s00c8_6aa0;
struct ResourceKey_s00c8_6aa0 {
    uint32_t mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
};
struct VObj174 {
    virtual void        AddRef();   // 0x00
    virtual void        Release();  // 0x04
    virtual void        v008();   // 0x08
    virtual cMWModel*   v00c(uint32_t type, uint32_t group, uint32_t arg); // 0x0c
    virtual void        v010();
    virtual void        v014();
    virtual VObj174*    v018();   // 0x18
    virtual void        v01c();
    virtual VObj174*    v020();   // 0x20
    virtual bool        v024(uint32_t key, struct cProperty_s00c8_6aa0** out);
    virtual void        v028();
    virtual void        v02c(uint32_t a, uint32_t b = 0, VObj174** out = 0);
    virtual void        v030();
    virtual void        v034();
    virtual void        v038();
    virtual void        v03c();
    virtual void        v040();
    virtual void        v044();
    virtual void        v048();
    virtual void        v04c();
    virtual void        v050();
    virtual void        v054();
    virtual void        v058();
    virtual void        v05c();
    virtual void        v060(const ResourceKey_s00c8_6aa0* pKey);
    virtual void        v064();
    virtual void        v068();
    virtual void        v06c();
    virtual VObj174*    v070();   // 0x70
    virtual void        v074();
    virtual void        v078();
    virtual void        v07c();
    virtual void        v080();
    virtual void        v084();
    virtual void        v088();
    virtual void        v08c();
    virtual void        v090();
    virtual void        v094();
    virtual void        v098();
    virtual void        v09c();
    virtual void        v0a0();
    virtual void        v0a4();
    virtual void        v0a8();
    virtual void        v0ac();
    virtual void        v0b0();
    virtual void        v0b4();
    virtual void        v0b8();
    virtual void        v0bc();
    virtual void        v0c0();
    virtual void        v0c4();
    virtual void        v0c8();
    virtual void        v0cc();
    virtual void        v0d0();
    virtual void        v0d4();
    virtual void        v0d8();
    virtual void        v0dc();
    virtual void        v0e0();
    virtual void        v0e4();
    virtual void        v0e8();
    virtual void        v0ec();
    virtual void        v0f0();
    virtual void        v0f4();
    virtual void        v0f8();
    virtual void        v0fc();
    virtual void        v100();
    virtual void        v104();
    virtual void        v108();
    virtual void        v10c();
    virtual void        v110();
    virtual void        v114();
    virtual void        v118();
    virtual void        v11c();
    virtual void        v120();
    virtual void        v124();
    virtual void        v128();
    virtual void        v12c();
    virtual void        v130();
    virtual void        v134();
    virtual void        v138();
    virtual void        v13c();
    virtual void        v140();
    virtual void        v144();
    virtual void        v148();
    virtual void        v14c();
    virtual void        v150();
    virtual void        v154();
    virtual void        v158();
    virtual void        v15c();
    virtual void        v160();
    virtual void        v164();
    virtual void        v168();
    virtual void        v16c(cMWModel* pModel, bool bVisible);   // 0x16c
    virtual void        v170(cMWModel* pModel, bool bDelete);    // 0x170
};
struct cMWWorld : VObj174 {
};
struct cMWModel {
    cMWWorld*   mpWorld;        // 0x00
    int32_t     mState;         // 0x04
    char        pad08[2];
    uint16_t    mFlags;         // 0x0a
    char        pad0c[0x18 - 0x0c];
    float       mRadius;        // 0x18
    char        pad1c[0x40 - 0x1c];
    uint32_t    mRefCount;      // 0x40
    char        pad44[0x64 - 0x44];
    VObj174*    mpOwner;        // 0x64

    void AddRef() { mRefCount++; }
    void Release();
};
inline void cMWModel::Release()
{
    if (mRefCount > 1) { mRefCount--; return; }
    mpWorld->v170(this, mState < 0);
}
template <typename T>
struct AutoRefCount_s00c8_6aa0 {
    T* mpObject;
    AutoRefCount_s00c8_6aa0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s00c8_6aa0(const AutoRefCount_s00c8_6aa0& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s00c8_6aa0() { T* p = mpObject; if (p) p->Release(); }
};
void ModelVecDoInsertValue(cMWModel** pPos, AutoRefCount_s00c8_6aa0<cMWModel>* pValue);   // 0x00423c40
cMWModel** ModelVecDoCopy(cMWModel** pFirst, cMWModel** pLast, cMWModel** pResult); // 0x005f4e10
void ModelVecDoDestroyValues(cMWModel** pFirst, cMWModel** pLast);            // 0x005f3680
struct ModelVec {
    cMWModel**  mpBegin;
    cMWModel**  mpEnd;
    cMWModel**  mpCapacity;
    struct Alloc { char* mpName; uint32_t mFlags; } mAllocator;

    void push_back(cMWModel* p)
    {
        AutoRefCount_s00c8_6aa0<cMWModel> value(p);
        if (mpEnd < mpCapacity) {
            AutoRefCount_s00c8_6aa0<cMWModel>* pSlot = (AutoRefCount_s00c8_6aa0<cMWModel>*)mpEnd++;
            pSlot->mpObject = p;
            if (p) p->AddRef();
        } else {
            ModelVecDoInsertValue(mpEnd, &value);
        }
    }
    void clear()
    {
        cMWModel** pNewEnd = ModelVecDoCopy(mpEnd, mpEnd, mpBegin);
        ModelVecDoDestroyValues(pNewEnd, mpEnd);
        mpEnd -= (mpEnd - mpBegin);
    }
};
struct RawPtrVec {
    void**      mpBegin;
    void**      mpEnd;
    void**      mpCapacity;
    struct Alloc { char* mpName; uint32_t mFlags; } mAllocator;
    void erase(void** pFirst, void** pLast);   // 0x00e25bd0
};
struct cPlanetSub {
    char        pad00[0x28];
    int32_t     m28;
};
class cPlanet_s00c8_6aa0 {
public:
    char        pad00[0xd4];
    VObj174    mTransform;      // 0xd4
    char        padD8[0x13c - 0xd8];
    cPlanetSub* mp13c;          // 0x13c

    int  GetEntityType();               // 0x00c70880
    void SetPlanetVisibility(int vis);  // 0x00c719d0
};
bool PlanetIsMarkedForRemoval(cPlanet_s00c8_6aa0* pPlanet);  // 0x00c83e40
struct cProperty_s00c8_6aa0 {
    char      pad00[0x12];
    uint16_t  mType;            // 0x12
    uint32_t* GetUInt();        // 0x0041ea00
    float*    GetFloat();       // 0x0041ea70
};
VObj174*     SP_PropertyManager_s00c8_6aa0();                       // 0x0067de30
class cSolarSystem_s00c8_6aa0 {
public:
    char        pad00[0x0c];
    void*       mpStar;         // 0x0c
    RawPtrVec   mPlanets;       // 0x10
    RawPtrVec   mCelestialBodies; // 0x24
    VObj174*    mp38;           // 0x38
    VObj174*    mp3c;           // 0x3c
    ModelVec    mPtolemaicHitSpheres; // 0x40

    void ActivatePtolemaicHitSpheres(bool activate);  // 0x00c86aa0 (cSolarSystem::ActivatePtolemaicHitSpheres)
    void ActivateGraphics(bool activate);  // 0x00c86c70 (cSolarSystem::ActivateGraphics)
    void Destroy();

    void  ActivateHitSpheres(bool activate);            // 0x00c83fd0
    void  ActivateEffects(bool activate, float value);  // 0x00c84620
    VObj174* GetModelManager();                         // 0x00b3d240
};
VObj174*     GetUniverseContext();                      // 0x01021080
cPlanet_s00c8_6aa0*     GetActivePlanet();                         // 0x01021260
// ---- items of slice s00c86aa0 end

// @ 0x004238c0
Elem38* Elem38Vector::erase(Elem38* first, Elem38* last)
{
    Elem38* position = CopyElems(last, mpEnd, first);
    for (Elem38* p = position; p < mpEnd; ++p) {
    }
    mpEnd -= (last - first);
    return first;
}

// @ 0x00423960
void Record56Vector::DoInsertValue(Record56* pos, const Record56* value)
{
    if (mEnd != mCapacity)
    {
        const Record56* v = value;
        if (v >= pos && v < mEnd)
            ++v;

        Record56* slot = mEnd;
        if (slot)
            slot->CopyConstruct(mEnd - 1);

        Record56* dst = mEnd;
        Record56* src = mEnd - 1;
        while (src != pos)
        {
            --src;
            --dst;
            dst->Assign(src);
        }
        pos->Assign(v);
        ++mEnd;
    }
    else
    {
        int count = (int)(mEnd - mBegin);
        uint32_t newCount = count ? count * 2 : 1;
        Record56* newBuf = newCount ? (Record56*)AllocatorAllocate(&mAllocator, newCount * sizeof(Record56), 4, 0) : 0;

        Record56* ins = UninitializedCopyRecords(mBegin, pos, newBuf);
        if (ins)
            ins->CopyConstruct(value);
        ins = ins + 1;
        Record56* newEnd = UninitializedCopyRecords(pos, mEnd, ins);

        int oldCapacity = (int)(mCapacity - mBegin);
        (void)oldCapacity;
        if (mBegin && ((uint32_t*)mBegin)[-1])
            AllocatorDeallocate(mBegin);
        mBegin = newBuf;
        mEnd = newEnd;
        mCapacity = newBuf + newCount;
    }
}

// @ 0x00423be0
ByteBuffer::ByteBuffer(uint32_t n, const Allocator*)
{
    mBegin = n ? (char*)AllocatorAllocate(&mAllocator, n, 1, 0) : 0;
    mEnd = mBegin;
    mCapacity = mBegin + n;
}

// @ 0x00423c40
void CountedPtrVector::DoInsertValue(CountedPtr* pos, CountedPtr* value)
{
    if (mEnd != mCapacity)
    {
        CountedPtr* v = value;
        if (v >= pos && v < mEnd)
            ++v;

        CountedPtr* slot = mEnd;
        if (slot)
        {
            *slot = mEnd[-1];
            if (*slot) ++(*slot)->mnRefCount;
        }

        CopyBackwardCounted(pos, mEnd - 1, mEnd);

        CountedPtr incoming = *v;
        if (incoming != *pos)
        {
            CountedPtr old = *pos;
            if (incoming) ++incoming->mnRefCount;
            *pos = incoming;
            if (old) old->Release();
        }
        ++mEnd;
    }
    else
    {
        int count = (int)(mEnd - mBegin);
        uint32_t newCount = count ? count * 2 : 1;
        CountedPtr* newBuf = newCount ? (CountedPtr*)AllocatorAllocate(&mAllocator, newCount * 4, 4, 0) : 0;

        CountedPtr* head = (CountedPtr*)memcpy(newBuf, mBegin, (char*)pos - (char*)mBegin);
        CountedPtr* ins = head + (pos - mBegin);
        if (ins)
        {
            *ins = *value;
            if (*ins) ++(*ins)->mnRefCount;
        }
        CountedPtr* tail = (CountedPtr*)memcpy(ins + 1, pos, (char*)mEnd - (char*)pos);
        CountedPtr* newEnd = tail + (mEnd - pos);

        if (mBegin && ((uint32_t*)mBegin)[-1])
            AllocatorDeallocate(mBegin);
        mBegin = newBuf;
        mEnd = newEnd;
        mCapacity = newBuf + newCount;
    }
}

// @ 0x00c83b60
void * SP::cSolarSystem::AsInterface(EA::COM::InterfaceId id)
{
    if (id == 0x38cf949)
        return this;
    if (id == 0x179c807)
        return static_cast<cISerializableObject*>((SP::cSolarSystem*)(this));
    if (id == 0xee3f516e)
        return static_cast<cISerializableObject*>((SP::cSolarSystem*)(this));
    return 0;
}

// @ 0x00c83b90
bool cISerializableObject::Write(void* stream)
{
    StreamSub* sub = ((StreamObj*)stream)->GetSub();
    uint32_t tag = 0x38cf949;
    void* io = sub->GetIO();
    EA_IO_WriteUint32(io, &tag, 1, 0);
    cVarListSerializer ser;
    ser.Ctor((char*)this - 8, &g_1579d78, 0x1a80d26);
    return ser.Serialize(stream);
}

// @ 0x00c83c70
cCelestialBody* cSolarSystem_s00c8_30f0::GetStar(bool primary)
{
    if (primary)
        return mStar1;
    return mStar2;
}

// @ 0x00c83cf0
void sStartStarEffect(EA::AutoRefCount_s00c8_30f0<EA::Swarm::cIVisualEffect_s00c8_30f0>* effect, cStarEffectHost* target, uint32_t type)
{
    if (effect->mpObject) {
        if (!effect->mpObject->IsRunning())
            effect->mpObject->Start(0);
        if (target)
            target->Release();
        return;
    }
    switch (type) {
    case 1: target->StartEffect(0x3d6ef7b, 0, effect->AsPPTypeParam()); break;
    case 2: target->StartEffect(0x3d6eef6, 0, effect->AsPPTypeParam()); break;
    case 3: target->StartEffect(0x3d6ef40, 0, effect->AsPPTypeParam()); break;
    case 4: target->StartEffect(0x3d6ef4d, 0, effect->AsPPTypeParam()); break;
    case 5: target->StartEffect(0x3d6ef59, 0, effect->AsPPTypeParam()); break;
    case 6: target->StartEffect(0x3d6ef67, 0, effect->AsPPTypeParam()); break;
    }
    effect->mpObject->Start(0);
    if (target)
        target->Release();
}

// @ 0x00c83e40
bool Execute(cPlanet* planet)
{
    if (planet->FUN_00c713e0()->instanceID == 0)
        return false;
    ResourceKey key = *planet->FUN_00c713e0();
    uint32_t group = (key.groupID & 0xe0ff28ff) | 0x2800;
    key.typeID = 0;
    if (!PropertyManager()->HasKey(key.instanceID, group))
        return false;
    intrusive_ptr<EA::COM::IUnknown32_s00c8_30f0> h1;
    PropertyManager()->QueryObject(key.instanceID, group, h1.reset_out());
    intrusive_ptr<EA::COM::IUnknown32_s00c8_30f0> h2;
    PropertyManager()->QueryObject(0x752f1cd8, 0x40842000, h2.reset_out());
    if (h1.mpObject && h2.mpObject) {
        ResourceKey k1 = { 0, 0, 0 };
        ResourceKey k2 = { 0, 0, 0 };
        bool b1 = GetPropertyAsKey((cPropertyList*)h1.mpObject, 0xf9efbb, k1);
        bool b2 = GetPropertyAsKey((cPropertyList*)h2.mpObject, 0xf9efbb, k2);
        if (b1 && b2 && k1.instanceID != k2.instanceID)
            return true;
    }
    return false;
}

// @ 0x00c83fd0
void cSolarSystem_s00c8_30f0::ActivateHitSpheres(bool activate)
{
    if (activate) {
        for (cCelestialBody** it = mpCelestialBodiesBegin; it != mpCelestialBodiesEnd; ++it) {
            cCelestialBody* body = *it;
            if (!body->mHitSphere.mpObject) {
                cGameNounManager* nouns = NounManager();
                cGameData* noun = nouns->CreateNoun(0x32f9778);
                cHitSphere* sphere = noun ? (cHitSphere*)noun->v0c(0x32f9777) : 0;
                body->mHitSphere = sphere;
                body->mHitSphere->SetTransform(&body->mPosition, body->mHitSphereSize);
                body->mHitSphere->SetRange(0.0f, g_147346c);
                body->mHitSphere->SetOwner(body);
            }
        }
    } else {
        for (cCelestialBody** it = mpCelestialBodiesBegin; it != mpCelestialBodiesEnd; ++it) {
            cCelestialBody* body = *it;
            if (body->mHitSphere.mpObject) {
                NounManager()->RemoveNoun((cGameData*)body->mHitSphere.mpObject);
                body->mHitSphere = 0;
            }
        }
    }
}

// @ 0x00c84b50
namespace Simulator {
cSolarSystem::cSolarSystem()
{
    mRefCount = 0;
    mpVtable1 = (void*)0x01444434;
    mpVtable0 = (void*)0x0147349c;
    mpVtable1 = (void*)0x01473478;
    mpOwnerStar = 0;
    mPlanets.mpBegin = 0;
    mPlanets.mpEnd = 0;
    mPlanets.mpCapacity = 0;
    mCelestialBodies.mpBegin = 0;
    mCelestialBodies.mpEnd = 0;
    mCelestialBodies.mpCapacity = 0;
    mModels.mpBegin = 0;
    mModels.mpEnd = 0;
    mModels.mpCapacity = 0;
    mpStar1 = 0;
    mpStar2 = 0;
}
}  // namespace Simulator

// @ 0x00c84d60
void SP::cSolarSystem_s00c8_4d60::UpdatePlanet(cPlanet_s00c8_4d60* planet, float dt)
{
    cPlanet_s00c8_4d60* active = cSPLivingUniverse::GetActivePlanet();
    int ctx = cSPLivingUniverse::GetUniverseContext();
    bool isActive = (ctx == 0 && planet == active);

    float step = dt;
    if (ctx == 1) {
        float scale = 10.0f;
        if (g_p01694c68) {
            void* prop = 0;
            if (((IConfig*)g_p01694c68)->GetProperty((const void*)0x54fc890, &prop) &&
                ((cProperty*)prop)->mType12 == 0xd)
                scale = *(float*)FUN_0041ea70(prop);
        }
        step = scale * dt;
    }

    if (FUN_00c70880(planet) == 0)
        return;

    Vector3 target;
    if (FUN_00b5b800() == (int)&g_mode_01654c01) {
        void* mgr = FUN_00b3d300();
        void* avatar = mgr ? FUN_00b1fdb0(mgr) : 0;
        if (avatar) {
            const Vector3& p = ((cAvatar*)avatar)->mPosC0;
            target = p;
        } else {
            target = planet->mPosition30;
        }
    } else {
        target = planet->mPosition30;
    }

    if (isActive) {
        FUN_00bc30b0(&target);
        float phase = FUN_00bc2b60(&target);
        FUN_00bc28c0(phase);
    }

    float orbit = step;
    if (FUN_00c70880(planet) == 1)
        orbit = dt;
    FUN_00c72770(orbit);

    Vector3 delta;
    delta.x = target.x - planet->mPosition30.x;
    delta.y = target.y - planet->mPosition30.y;
    delta.z = target.z - planet->mPosition30.z;

    Vector3 pos;
    pos.x = planet->GetPosition().x + delta.x;
    pos.y = planet->GetPosition().y + delta.y;
    pos.z = planet->GetPosition().z + delta.z;
    planet->SetPosition(pos);

    (void)FUN_00c71530();

    if (!isActive) {
        FUN_00c84950(planet);
        if (ctx == 0) {
            Vector3 ptol;
            planet->GetPtolemaicPosition(ptol);
            float near = delta.x * pos.x + delta.y * pos.y + ptol.x * orbit;
            int mode = (near <= g_f01579ea4) ? 3 : 2;
            if (mode == 2 && FUN_00c83e40(planet))
                mode = 3;
            FUN_00c719d0(mode);
        }
        return;
    }

    FUN_01021740();
}

// @ 0x00c85200
void SP::cSolarSystem_s00c8_4d60::InitBinarySystem(WString* name)
{
    if (mpGameData->IsBinary()) {
        wchar_t* pLast = name->mpEnd;
        bool alpha = iswctype(*--pLast, 4) != 0;

        if (mpPrimary) {
            const wchar_t* suffix;
            {
                cString_s00c8_4d60 text(0x2db6dad3, (alpha ? 1 : 0) * 2 + 0x5d66e7c, 0);
                suffix = text.GetText();
            }
            WString tmp;
            cCelestialBody_s00c8_4d60* primary = mpPrimary;
            WString* joined = PathJoin(&tmp, name, suffix);
            if (joined != &primary->mName)
                primary->mName.assign(joined->mpBegin, joined->mpEnd);
            if ((int)(((uint32_t)((uint8_t*)tmp.mpCap - (uint8_t*)tmp.mpBegin)) & 0xfffffffeu) > 2 &&
                tmp.mpBegin)
                FreeRawBlock(tmp.mpBegin);
        }

        if (mpSecondary) {
            const wchar_t* suffix;
            {
                cString_s00c8_4d60 text(0x2db6dad3, (alpha ? 3 : 0) + 0x5d66e7d, 0);
                suffix = text.GetText();
            }
            WString tmp;
            cCelestialBody_s00c8_4d60* secondary = mpSecondary;
            WString* joined = PathJoin(&tmp, name, suffix);
            if (joined != &secondary->mName)
                secondary->mName.assign(joined->mpBegin, joined->mpEnd);
            if ((int)(((uint32_t)((uint8_t*)tmp.mpCap - (uint8_t*)tmp.mpBegin)) & 0xfffffffeu) > 2 &&
                tmp.mpBegin)
                FreeRawBlock(tmp.mpBegin);
        }
    } else {
        if (mpPrimary && name != &mpPrimary->mName)
            mpPrimary->mName.assign(name->mpBegin, name->mpEnd);
    }
}

// @ 0x00c85380
void SP::cSolarSystem_s00c8_4d60::UpdatePlanets(float dt)
{
    cCelestialBody_s00c8_4d60** it;
    int count = (int)(mpPlanetsEnd - mpPlanetsBegin);
    for (int i = 0; i < count; i++)
        UpdatePlanet(mpPlanetsBegin[i], dt);

    if (cSPLivingUniverse::GetUniverseContext() != 0)
        return;

    for (it = mpBodiesBegin; it != mpBodiesEnd; it++) {
        cCelestialBody_s00c8_4d60* body = *it;
        IBodyData* data = body->mpData64;
        if (!data)
            continue;
        IBodyComponent* comp = (IBodyComponent*)data->QueryComponent((const void*)0x3275872);
        if (!comp)
            continue;

        int state = comp->GetState();
        unsigned shifted = body->mBits4 >> 15;
        if (state == 2) {
            if (!(shifted & 1))
                body->mpIface0->SetVisible(body, 1);
            body->mPosition = comp->GetPosition();
            body->mFlags8 = body->mFlags8 | 4;
            body->mCounterA = body->mCounterA + 1;
        } else if (shifted & 1) {
            body->mpIface0->SetVisible(body, 0);
        }
    }
}

// @ 0x00c85540
void SP::cSolarSystem_s00c8_4d60::GetBinarySuffix()
{
    int alpha = iswctype((wint_t)mpGameData->GetName()->mpEnd[-1], 4);

    if (!mpPrimary) {
        cCelestialBody_s00c8_4d60* body =
            (cCelestialBody_s00c8_4d60*)FUN_00f473a0(0xcc, "Simulator/cCelestialBody", 0, 0, 0, 0);
        if (body)
            body = (cCelestialBody_s00c8_4d60*)FUN_00bd6410(body, 0);
        cCelestialBody_s00c8_4d60* old = mpPrimary;
        if (body != old) {
            if (body)
                body->mpIface0->AddRef();
            mpPrimary = body;
            if (old)
                old->mpIface0->Release();
        }
        if (mpBodies0End < mpBodies0Cap) {
            void** slot = mpBodies0End++;
            if (slot) {
                *slot = mpPrimary;
                if (mpPrimary)
                    mpPrimary->mpIface0->AddRef();
            }
        } else {
            FUN_00aea5d0(mpBodies0End, &mpPrimary);
        }
    }

    cCelestialBody_s00c8_4d60* primary = mpPrimary;
    primary->mRotationAc = GetStarRotationRate(mpGameData->mpStarA);
    primary->mRadiusC8 = GetStarRadius(mpGameData->mpStarA);

    if (!mpSecondary) {
        cCelestialBody_s00c8_4d60* body =
            (cCelestialBody_s00c8_4d60*)FUN_00f473a0(0xcc, "Simulator/cCelestialBody", 0, 0, 0, 0);
        if (body)
            body = (cCelestialBody_s00c8_4d60*)FUN_00bd6410(body, 0);
        cCelestialBody_s00c8_4d60* old = mpSecondary;
        if (body != old) {
            if (body)
                body->mpIface0->AddRef();
            mpSecondary = body;
            if (old)
                old->mpIface0->Release();
        }
        if (mpBodies0End < mpBodies0Cap) {
            void** slot = mpBodies0End++;
            if (slot) {
                *slot = mpSecondary;
                if (mpSecondary)
                    mpSecondary->mpIface0->AddRef();
            }
        } else {
            FUN_00aea5d0(mpBodies0End, &mpSecondary);
        }
    }

    cCelestialBody_s00c8_4d60* secondary = mpSecondary;
    secondary->mRotationAc = GetStarRotationRate(mpGameData->mpStarB);
    secondary->mRadiusC8 = GetStarRadius(mpGameData->mpStarB);

    float massA = GetStarMass(mpGameData->mpStarA);
    float massB = GetStarMass(mpGameData->mpStarB);
    float radiusA = GetStarRadius(mpGameData->mpStarA);
    float radiusB = GetStarRadius(mpGameData->mpStarB);
    float distance = ((radiusA + radiusB) * 1.5f) / ((massB / massA) + 1.0f);
    float jitter = (float)RandomDoubleUniform() * ((distance + 10.0f) - distance) + distance;
    float orbit = jitter * (massB / massA);

    float binaryOffset;
    if (mpGameData->mpStarA == mpGameData->mpStarB) {
        float r = (float)RandomDoubleUniform() * 0.2f;
        binaryOffset = r < 0.0f ? 0.0f : (r > 0.2f ? 0.2f : r);
    } else {
        binaryOffset = 0.0f;
    }

    float tilt = (float)RandomDoubleUniform() * 60.0f + 30.0f;
    if (tilt > 90.0f)
        tilt = 90.0f;

    primary->mKind38 = 0;
    primary->mAxis3c.x = g_f01579d58;
    primary->mAxis3c.y = g_f01579d5c;
    primary->mAxis3c.z = g_f01579d60;
    primary->mSwing48 = binaryOffset;
    primary->mVelocityA0.x = orbit;
    primary->mVelocityA0.y = 0.0f;
    primary->mVelocityA0.z = 0.0f;
    primary->mInclination58 = tilt;
    primary->mOffset4c.x = orbit;
    primary->mOffset4c.y = 0.0f;
    primary->mOffset4c.z = 0.0f;
    FUN_00fe8450();

    secondary->mKind38 = 0;
    secondary->mAxis3c.x = g_f01579d58;
    secondary->mAxis3c.y = g_f01579d5c;
    secondary->mAxis3c.z = g_f01579d60;
    secondary->mSwing48 = binaryOffset;
    secondary->mVelocityA0.x = -orbit;
    secondary->mVelocityA0.y = 0.0f;
    secondary->mVelocityA0.z = 0.0f;
    secondary->mInclination58 = tilt;
    secondary->mOffset4c.x = -orbit;
    secondary->mOffset4c.y = 0.0f;
    secondary->mOffset4c.z = 0.0f;
    FUN_00fe8450();
}

// @ 0x00c85a30
void cSolarSystem_s00c8_5a30::InitComets()
{
    AutoRefCount<cCelestialBody_s00c8_5a30>* it = mCelestialBodies.mpBegin;
    AutoRefCount<cCelestialBody_s00c8_5a30>* end = mCelestialBodies.mpEnd;
    for (; it != end; ++it)
        if (it->mpObject->mType == 2)
            return;

    int nComets = (int)gRandom.RandomUint32Uniform(4) + 3;
    if (nComets > 0) do {
        cCelestialBody_s00c8_5a30* pRaw = new("Simulator/cCelestialBody", 0, 0, 0, 0) cCelestialBody_s00c8_5a30(2);
        cCelestialBody_s00c8_5a30* body = pRaw;

        // orientation: tilt about X by a clamped angle, then spin about Z by a random angle
        float angle = (float)(gRandom.RandomDoubleUniform() * kTwoPi);
        double lim = kPi * 0.25f;
        double tilt = RandomRange(-lim, lim) * 0.5f;
        double st = sin(tilt);
        float q1x = kAxisX.x * st, q1y = kAxisX.y * st, q1z = kAxisX.z * st;
        float q1w = (float)cos(tilt);

        double half = 0.5f * angle;
        float sp = (float)sin(half);
        float ax = kAxisZ.x * sp, ay = kAxisZ.y * sp, az = kAxisZ.z * sp;
        float cp = (float)cos(half);

        // q = (ax,ay,az,cp) * (q1x,q1y,q1z,q1w)
        float cxv = ay * q1z - az * q1y;
        float cyv = az * q1x - q1z * ax;
        float czv = q1y * ax - ay * q1x;
        float qx = (cp * q1x + q1w * ax) + cxv;
        float qy = (cp * q1y + ay * q1w) + cyv;
        float qz = (cp * q1z + az * q1w) + czv;
        float qw = cp * q1w - ((ax * q1x + az * q1z) + ay * q1y);

        // radius range from the star type
        int type = mpStar->GetType();
        float r0 = CachedStarValue(type);
        float hiR = r0 + GetStarTemperature(type) * 85.0f;
        type = mpStar->GetType();
        float r1 = CachedStarValue(type);
        GetStarTemperature(type);
        float radius = (float)RandomRange(r1 + 15.0f, hiR);

        float xx = qx * qx, xy = qx * qy, xz = qx * qz;
        float yy = qy * qy, yz = qy * qz, zz = qz * qz;
        float wx = qw * qx, wy = qw * qy, wz = qw * qz;

        body->mOrbit.mNullOrbit = false;
        body->mOrbit.mPlaneNormal[0] = ((xy - wz) * kAxisZ.y + (wy + xz) * kAxisZ.z) * 2.0f + (1.0f - (zz + yy) * 2.0f) * kAxisZ.x;
        body->mOrbit.mPlaneNormal[1] = ((yz - wx) * kAxisZ.z + (wz + xy) * kAxisZ.x) * 2.0f + (1.0f - (zz + xx) * 2.0f) * kAxisZ.y;
        body->mOrbit.mPlaneNormal[2] = ((wx + yz) * kAxisZ.y + (xz - wy) * kAxisZ.x) * 2.0f + (1.0f - (yy + xx) * 2.0f) * kAxisZ.z;

        double e = RandomRange(0.3f, 0.7f);
        body->mOrbit.mEccentricity = (float)e;

        float px = ((xy - wz) * kAxisX.y + (wy + xz) * kAxisX.z) * 2.0f + (1.0f - (zz + yy) * 2.0f) * kAxisX.x;
        float py = ((yz - wx) * kAxisX.z + (wz + xy) * kAxisX.x) * 2.0f + (1.0f - (zz + xx) * 2.0f) * kAxisX.y;
        float pz = ((wx + yz) * kAxisX.y + (xz - wy) * kAxisX.x) * 2.0f + (1.0f - (yy + xx) * 2.0f) * kAxisX.z;
        float inv = 1.0f / sqrtf((px * px + (py * py + pz * pz)) + 1e-8f);
        body->mOrbit.mPerihelion[0] = (inv * px) * radius;
        body->mOrbit.mPerihelion[1] = (py * inv) * radius;
        body->mOrbit.mPerihelion[2] = (pz * inv) * radius;

        body->mOrbit.mPeriod = (float)RandomRange(300.0f, 900.0f);
        body->mOrbit.Update();
        body->Setup();

        {
            SP::cString_s00c8_5a30 name(0x2db6dad3, 0x3f5a128, 0);
            body->mName.assign(name.GetText());
        }
        body->mHitSphereSize = 2.0f;

        AutoRefCount<cCelestialBody_s00c8_5a30> ref(body);
        mCelestialBodies.push_back(ref);
    } while (--nComets != 0);
}

// @ 0x00c86390
void cSolarSystem_s00c8_5a30::UpdateBodies(float value)
{
    AutoRefCount<cCelestialBody_s00c8_5a30>* it = mCelestialBodies.mpBegin;
    AutoRefCount<cCelestialBody_s00c8_5a30>* end = mCelestialBodies.mpEnd;
    if (it != end) {
        do {
            cCelestialBody_s00c8_5a30* pBody = it->mpObject;
            pBody->SetBrightness(value);

            float bright = kOne;
            if (pBody->mType == 0) {
                cSPVector3_s00c8_5a30 cameraPos;
                if (SP_LivingUniverse_Context() == (void*)1) {
                    void* pApp = SP_App();
                    cViewer_s00c8_5a30* pViewer = (cViewer_s00c8_5a30*)SP_App_GetViewer(pApp);
                    pViewer->GetCameraLocationInfo(&cameraPos, 0, 0, 0);
                } else {
                    cSPVector3_s00c8_5a30* pPos = (cSPVector3_s00c8_5a30*)FUN_01021260();
                    cameraPos = *pPos;
                }
                float dx = cameraPos.x - pBody->mPosition.x;
                float dy = cameraPos.y - pBody->mPosition.y;
                float dz = cameraPos.z - pBody->mPosition.z;
                bright = FUN_01034630(3, sqrtf(dx * dx + dy * dy + dz * dz), 0);
            }

            cBodyVisual* pVisual = pBody->mpVisual;
            if (pVisual && pVisual->IsVisible()) {
                struct { uint16_t flags; uint16_t index; float r, g, b; float alpha; } color;
                color.flags = 0;
                color.index = 0;
                color.r = gBodyColorR;
                color.g = gBodyColorG;
                color.b = gBodyColorB;
                color.alpha = kOne;

                cSPMatrix3_s00c8_5a30 matrix;
                matrix.Assign(&gBodyOrientation);
                pVisual->SetMatrix(&matrix);
                ++color.index;
                color.alpha = bright;
                pVisual->SetColor(&color);
            }

            cBodyEffect* pEffect = pBody->mpEffect;
            if (pEffect)
                pEffect->SetEffect(pBody->mHitSphereSize * bright, &pBody->mPosition);

            ++it;
        } while (it != end);
    }
    UpdateCometVisuals(this, value);
}

// @ 0x00c86640
void SP::cSolarSystem::InitTuning()
{
    PropertyManager_s00c8_5a30* pManager = SP_PropertyManager();
    if (gStarPropertySlots.mpBegin == gStarPropertySlots.mpEnd) {
        gStarPropertySlots.resize(13);
        gStarPropertySlots.mpBegin[4].release();
        pManager->GetProperty(0x4c66e1e4, 0x74d2735b, &gStarPropertySlots.mpBegin[4]);
        gStarPropertySlots.mpBegin[5].release();
        pManager->GetProperty(0x4c66e1ec, 0x74d2735b, &gStarPropertySlots.mpBegin[5]);
        gStarPropertySlots.mpBegin[6].release();
        pManager->GetProperty(0x4c66e1ee, 0x74d2735b, &gStarPropertySlots.mpBegin[6]);
    }
    if (!gDefaultStarProperty.mpObject)
        pManager->GetProperty(0x1106d054, 0x2ae0c7e, &gDefaultStarProperty);
}

// @ 0x00c86760
void cSolarSystem_s00c8_5a30::InitStar(cStar_s00c8_5a30* pStar)
{
    mpStar = pStar;
    if (pStar->IsKnown()) {
        InitStarBodyHelper(this);
    } else {
        if (!mStarBody.mpObject) {
            cCelestialBody_s00c8_5a30* pRaw = new("Simulator/cCelestialBody", 0, 0, 0, 0) cCelestialBody_s00c8_5a30(0);
            mStarBody = pRaw;
            mCelestialBodies.push_back(AutoRefCount<cCelestialBody_s00c8_5a30>(pRaw));
        }
        cCelestialBody_s00c8_5a30* pBody = mStarBody.mpObject;
        pBody->mOrbit.mNullOrbit = true;
        pBody->mPosition = gSunPosition;
        pBody->mRotationRate = GetStarRotationRate(pStar->GetType());
        pBody->mName.assign(*pStar->GetName());
        pBody->mHitSphereSize = GetStarRadius(pStar->GetType());
    }

    if (pStar->HasComets())
        InitComets();

    int type = pStar->GetType();
    if (gStarCache[type] < 0.0f)
        gStarCache[type] = IsGasType(type) ? GetGasValue(type) : GetStarRadius(type);
    float hiRadius = gStarCache[type] + GetStarTemperature(type) * 85.0f;

    type = pStar->GetType();
    if (gStarCache[type] < 0.0f)
        gStarCache[type] = IsGasType(type) ? GetGasValue(type) : GetStarRadius(type);
    float loRadius = gStarCache[type] + GetStarTemperature(type) * 15.0f;

    cPlanetVector* pPlanets = cStarManager_planets(pStar->mpPlanetManager);
    const int numPlanets = (int)(pPlanets->mpEnd - pPlanets->mpBegin);
    for (int i = 0; i < numPlanets; ++i) {
        cPlanet_s00c8_5a30* pPlanet = 0;
        cStarManager_s00c8_5a30* pManager = SP_StarManager(&pPlanets->mpBegin[i], &pPlanet);
        pManager->GetOrActivatePlanet();

        if (pPlanet) {
            mPlanets.push_back(AutoRefCount<cPlanet_s00c8_5a30>(pPlanet));
        }

        float size = pPlanet ? pPlanet->GetValue(1) : 0.0f;
        if (size > loRadius && !(pPlanet->m_flags & 1))
            pPlanet->m_flags |= 0x1000;
        if (size > hiRadius && !(pPlanet->m_flags & 1))
            pPlanet->m_flags |= 0x2000;

        if (pPlanet)
            pPlanet->Release();
    }
}

// @ 0x00c86aa0
void cSolarSystem_s00c8_6aa0::ActivatePtolemaicHitSpheres(bool activate)
{
    if (!activate) {
        for (cMWModel** pp = mPtolemaicHitSpheres.mpBegin; pp != mPtolemaicHitSpheres.mpEnd; ++pp) {
            cMWModel* pModel = *pp;
            pModel->mpWorld->v16c(pModel, false);
        }
        return;
    }
    if (mPtolemaicHitSpheres.mpBegin != mPtolemaicHitSpheres.mpEnd) {
        for (cMWModel** pp = mPtolemaicHitSpheres.mpBegin; pp != mPtolemaicHitSpheres.mpEnd; ++pp) {
            cMWModel* pModel = *pp;
            pModel->mpWorld->v16c(pModel, true);
        }
        return;
    }

    VObj174* pModelManager = GetModelManager()->v070();
    cPlanet_s00c8_6aa0** ppPlanet = (cPlanet_s00c8_6aa0**)mPlanets.mpBegin;
    if (ppPlanet == (cPlanet_s00c8_6aa0**)mPlanets.mpEnd)
        return;
    do {
        cPlanet_s00c8_6aa0* pPlanet = *ppPlanet;
        if (pPlanet->GetEntityType() != 0) {
            cMWModel* pModel = pModelManager->v00c(0x2e81370, kHitSphereModelGroup, 0x10);
            VObj174* pTransform = pPlanet ? &pPlanet->mTransform : 0;
            VObj174* pOldOwner = pModel->mpOwner;
            if (pTransform != pOldOwner) {
                if (pTransform) pTransform->AddRef();
                pModel->mpOwner = pTransform;
                if (pOldOwner) pOldOwner->Release();
            }
            pModel->mFlags++;
            pModel->mRadius = (pPlanet->GetEntityType() == 1) ? kGasGiantRadius : kRockyRadius;
            mPtolemaicHitSpheres.push_back(pModel);
        }
        ++ppPlanet;
    } while (ppPlanet != (cPlanet_s00c8_6aa0**)mPlanets.mpEnd);
}

// @ 0x00c86c70
void cSolarSystem_s00c8_6aa0::ActivateGraphics(bool activate)
{
    if (activate) {
        float fValue = 1.0f;
        if (GetUniverseContext() == 0) {
            VObj174* pPropList = 0;
            VObj174* pPropertyManager = SP_PropertyManager_s00c8_6aa0();
            if (pPropList) { VObj174* pOld = pPropList; pPropList = 0; pOld->Release(); }
            pPropertyManager->v02c(0x272ddeda, 0x2ae0c7e, &pPropList);
            if (pPropList) {
                cProperty_s00c8_6aa0* pProp = 0;
                if (pPropList->v024(0x379762b, &pProp) && pProp->mType == 0xd)
                    fValue = *pProp->GetFloat();
            }
            cPlanet_s00c8_6aa0* pActivePlanet = GetActivePlanet();
            ActivateHitSpheres(false);
            ActivatePtolemaicHitSpheres(true);
            for (cPlanet_s00c8_6aa0** pp = (cPlanet_s00c8_6aa0**)mPlanets.mpBegin; pp != (cPlanet_s00c8_6aa0**)mPlanets.mpEnd; ++pp) {
                cPlanet_s00c8_6aa0* pPlanet = *pp;
                int vis;
                if (pPlanet == pActivePlanet) {
                    vis = 0;
                } else {
                    int t = pPlanet->mp13c->m28;
                    if (t != 0 && t != 1) {
                        vis = PlanetIsMarkedForRemoval(pPlanet) ? 2 : 3;
                    } else {
                        vis = 2;
                    }
                }
                pPlanet->SetPlanetVisibility(vis);
            }
            if (pPropList) pPropList->Release();
        } else {
            ActivateHitSpheres(true);
            for (cMWModel** pp = mPtolemaicHitSpheres.mpBegin; pp != mPtolemaicHitSpheres.mpEnd; ++pp) {
                cMWModel* pModel = *pp;
                pModel->mpWorld->v16c(pModel, false);
            }
            for (cPlanet_s00c8_6aa0** pp = (cPlanet_s00c8_6aa0**)mPlanets.mpBegin; pp != (cPlanet_s00c8_6aa0**)mPlanets.mpEnd; ++pp)
                (*pp)->SetPlanetVisibility(1);
        }
        ActivateEffects(true, fValue);
    } else {
        ActivateHitSpheres(false);
        for (cMWModel** pp = mPtolemaicHitSpheres.mpBegin; pp != mPtolemaicHitSpheres.mpEnd; ++pp) {
            cMWModel* pModel = *pp;
            pModel->mpWorld->v16c(pModel, false);
        }
        ActivateEffects(false, 1.0f);
        for (cPlanet_s00c8_6aa0** pp = (cPlanet_s00c8_6aa0**)mPlanets.mpBegin; pp != (cPlanet_s00c8_6aa0**)mPlanets.mpEnd; ++pp)
            (*pp)->SetPlanetVisibility(0);
    }
}

// @ 0x00c86e50
void cSolarSystem_s00c8_6aa0::Destroy()
{
    ActivateGraphics(false);

    for (void** pp = mCelestialBodies.mpBegin; pp != mCelestialBodies.mpEnd; ++pp)
        ((VObj174*)*pp)->v044();
    mCelestialBodies.erase(mCelestialBodies.mpBegin, mCelestialBodies.mpEnd);
    mPlanets.erase(mPlanets.mpBegin, mPlanets.mpEnd);

    mpStar = 0;

    VObj174* p38 = mp38;
    if (p38) {
        mp38 = 0;
        p38->Release();
    }
    VObj174* p3c = mp3c;
    if (p3c) {
        mp3c = 0;
        p3c->Release();
    }

    mPtolemaicHitSpheres.clear();
}

// @ 0x013526b0
void FUN_013526b0(void)
{
    PropDesc d;
    d.mName = (const char*)0x147351c;
    d.mHash = 0x38cfa88;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc86560;
    d.mFn28 = (void*)0xc43790;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)0xb6f860;
    d.mFn38 = (void*)0xc6c390;
    d.mType = 0x10;
    *(PropDesc*)0x1579d78 = d;

    d.mName = (const char*)0x1473508;
    d.mHash = 0x38cfad9;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc85460;
    d.mFn28 = (void*)0xaca730;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)0xb6f860;
    d.mFn38 = (void*)0xc6c390;
    d.mType = 0x24;
    *(PropDesc*)0x1579db4 = d;

    d.mName = (const char*)0x1473500;
    d.mHash = 0x38cfae4;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc843f0;
    d.mFn28 = (void*)0xbca960;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)0xb6f550;
    d.mFn38 = (void*)0xac8050;
    d.mType = 0x38;
    *(PropDesc*)0x1579df0 = d;

    d.mName = (const char*)0x14734f8;
    d.mHash = 0x38cfafe;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc843f0;
    d.mFn28 = (void*)0xbca960;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)0xb6f550;
    d.mFn38 = (void*)0xac8050;
    d.mType = 0x3c;
    *(PropDesc*)0x1579e2c = d;
}
