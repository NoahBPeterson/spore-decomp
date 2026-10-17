// src/game/SPEditors/SPObjectTemplateDB.cpp -- migrated from slice(s) s00569690, s005634e0, s005628d0, s00561970, s0055ec70, s0055dce0, s0055ce80, s0055beb0, s0055a550, s005598b0, s00559050, s005580e0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPObjectTemplateDB.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/FunctionalMatch/Constraint.h"
#include "SP/FunctionalMatch/DeclareParam.h"
#include "EA/ResourceMan/DatabasePackedFile.h"
#include "EA/ResourceMan/PFRecordRead.h"
#include "EA/Audio/Group.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cSPObjectTemplateDB.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include "EA/Variant.h"
#include "SP/cDirectPropertyList.h"
#include "EA/Allocator/ZoneObject.h"
#include "SP/cISPObjectTemplateDB.h"
#include "EA/AutoRefCount.h"
#include "SP/cFunctionalTestCheat.h"
#include "eastl/allocator.h"
#include "SP/FunctionalMatch/cISummarizer.h"
#include "EA/LimitStopwatch.h"
#include "EA/Stopwatch.h"
#include "SP/cJob.h"
#include "SP/cJobManager.h"
#include "eastl/vector.h"

// ---- items of slice s005580e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
namespace eastl {
struct allocator_tag { allocator_tag() {} };
}
namespace eastl {
struct allocator_s0055_80e0 {
    allocator_s0055_80e0() {}
    allocator_s0055_80e0(const allocator_tag& tag);
    const char* mpName;
    uint32_t mFlags;
};
}
namespace eastl {
struct sp_vector_allocator_s0055_80e0 : public allocator_s0055_80e0 { sp_vector_allocator_s0055_80e0() {} };
}
namespace eastl {
template<typename T, typename A>
struct VectorBase_s0055_80e0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;
    VectorBase_s0055_80e0() : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator() {}
    VectorBase_s0055_80e0(const allocator_tag& a) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
    ~VectorBase_s0055_80e0();
};
}
namespace eastl {
template<typename T, typename A>
class vector_s0055_80e0 : public VectorBase_s0055_80e0<T, A> {
public:
    vector_s0055_80e0() { ScratchSlots<1>(); }
    vector_s0055_80e0(const vector_s0055_80e0& x);
    ~vector_s0055_80e0();
    void push_back(const T& value);
};
}
namespace eastl {
template<typename T>
inline void destruct(T* first, T* last) {
    for (; first < last; ++first)
        first->~T();
}
}
namespace eastl {
template<typename T>
class vector_s0055_80e0<T, allocator_s0055_80e0> : public VectorBase_s0055_80e0<T, allocator_s0055_80e0> {
public:
    typedef VectorBase_s0055_80e0<T, allocator_s0055_80e0> base_type;
    vector_s0055_80e0(const allocator_tag& a = allocator_tag()) : base_type(a) { ScratchSlots<10>(); }
    ~vector_s0055_80e0() { ScratchSlots<2>(); destruct(base_type::mpBegin, base_type::mpEnd); }
    size_t size() const { return (size_t)(base_type::mpEnd - base_type::mpBegin); }
    T& operator[](size_t n) { return *(base_type::mpBegin + n); }
};
}
namespace SP {
namespace FunctionalMatch {
enum eType_s0055_80e0 {
    kInteger_s0055_80e0 = 48342877,
    kFloat_s0055_80e0 = 48343039,
    kTerminal_s0055_80e0 = 48343507,
    kNotEqual_s0055_80e0 = 0xcba453f7
};
}
}
namespace SP {
namespace FunctionalMatch {
enum Sentinel_s0055_80e0 { kEndConstraint_s0055_80e0 = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
enum EqualConstraint_s0055_80e0 { kEquals_s0055_80e0 = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
enum RangeConstraint_s0055_80e0 { kBetween_s0055_80e0 = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
enum ToleranceConstraint { kWithin = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
enum NotEqualConstraint { kNotEquals = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
enum AnyConstraint { kAny = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
struct Constraint_s0055_80e0 {
    unsigned int mParameter;
    eType_s0055_80e0 mType;
    union {
        struct { int mMin; int mMax; } mIntVal;
        struct { float mMin; float mMax; } mFloatVal;
    };
    eastl::vector_s0055_80e0<Constraint_s0055_80e0, eastl::sp_vector_allocator_s0055_80e0> mConstraints;

    Constraint_s0055_80e0();
    Constraint_s0055_80e0(Sentinel_s0055_80e0);
    Constraint_s0055_80e0(unsigned int param, ToleranceConstraint, float value, float tolerance);
    Constraint_s0055_80e0(unsigned int param, RangeConstraint_s0055_80e0, float minVal, float maxVal);
    Constraint_s0055_80e0(unsigned int param, EqualConstraint_s0055_80e0, int value);
    Constraint_s0055_80e0(unsigned int param, RangeConstraint_s0055_80e0, int minVal, int maxVal);
    Constraint_s0055_80e0(unsigned int param, NotEqualConstraint, int value);
    Constraint_s0055_80e0(AnyConstraint, eastl::vector_s0055_80e0<Constraint_s0055_80e0, eastl::sp_vector_allocator_s0055_80e0> constraints);
    bool IsCompound() const;
};
}
}
struct ResourceKey {
    uint32_t mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
    ResourceKey() : mInstanceID(0), mTypeID(0), mGroupID(0) {}
    ResourceKey(uint32_t instance, uint32_t type, uint32_t group)
        : mInstanceID(instance), mTypeID(type), mGroupID(group) {}
};
namespace EA {
namespace IO {
struct IStream_s0055_80e0;
}
}
namespace EA {
namespace IO {
bool ReadInt32(IStream_s0055_80e0* pIS, int32_t* value, size_t count, int endian);
}
}
namespace EA {
namespace IO {
bool WriteUint32(IStream_s0055_80e0* pIS, const uint32_t* value, size_t count, int endian);
}
}
namespace EA {
namespace IO {
inline bool WriteUint32(IStream_s0055_80e0* pIS, uint32_t value, int endian) { return WriteUint32(pIS, &value, 1, endian); }
}
}
struct IPFRecord {
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    virtual void v3();
    virtual ResourceKey& GetKey();
    virtual void v5();
    virtual EA::IO::IStream_s0055_80e0* GetStream();
};
template<typename T>
struct IntrusivePtr {
    T* mpObject;
    IntrusivePtr() : mpObject(0) {}
    ~IntrusivePtr() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* detach() {
        T* const pTemp = mpObject;
        mpObject = 0;
        return pTemp;
    }
    IntrusivePtr& operator=(T* pObject) {
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
    T** operator&() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};
struct DatabasePackedFile_s0055_80e0 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c();
    virtual bool OpenRecord(const ResourceKey& key, IPFRecord** ppRecord, int accessFlags, int a, int b, int c);  // 0x008da3d0 (DatabasePackedFile::OpenRecord)
    virtual void v0e();
    virtual bool CloseRecord(IPFRecord* pRecord);  // 0x008d9a10 (DatabasePackedFile::CloseRecord)
};
namespace SP {
 struct ResourceObject; 
}
struct IResourceManager {
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual bool GetResource(const ResourceKey& key, SP::ResourceObject** ppResource, int a, int b, int c, int d);
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15();
    virtual DatabasePackedFile_s0055_80e0* FindDatabase(const ResourceKey& key);
};
namespace EA {
namespace ResourceMan {
 IResourceManager* GetManager(); 
}
}
namespace SP {
DatabasePackedFile_s0055_80e0* GetSaveArea(uint32_t groupID);
}
void* operator new(size_t size, const char* pName, int flags = 0, unsigned debugFlags = 0, const char* file = 0, int line = 0);
namespace SP {
struct ResourceObject {
    virtual int AddRef();
    virtual int Release();
};
}
namespace SP {
struct cResourceBase_s0055_80e0 : public ResourceObject {
    int mnRefCount;
    ResourceKey mKey;
    cResourceBase_s0055_80e0();
    void* AsInterface(uint32_t iid);  // 0x006abe20 (SP::cResourceBase::AsInterface)
    void SetResourceKey(const ResourceKey& key) { mKey = key; }
};
}
namespace SP {
struct cCachedResource : public cResourceBase_s0055_80e0 {
    uint32_t mField14;
    cCachedResource() : mField14(0) {}
};
}
namespace SP {
struct ParamAllocator { ParamAllocator() {} };
}
namespace SP {
struct ParamTable {
    uint32_t mData[5];
    ParamTable(const ParamAllocator& allocator_s0055_80e0 = ParamAllocator());
};
}
namespace SP {
class cParameterResource : public cCachedResource {
public:
    __forceinline cParameterResource() {}
    void* AsInterface(uint32_t iid);
    ParamTable mParams;
};
}
namespace SP {
struct cResourceFactoryBase {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual bool Read(IPFRecord* pRecord, ResourceObject* pResource, int flags, uint32_t typeID);
};
}
namespace SP {
class cParameterResourceFactory : public cResourceFactoryBase {
public:
    size_t GetSupportedTypes(uint32_t* types, size_t count);
    bool IsValid(uint32_t typeID, uint32_t subtypeID);
    bool CreateResource(IPFRecord* pRecord, ResourceObject*& pDst, int flags, uint32_t typeID);
};
}
template<> struct IntrusivePtr<SP::ResourceObject> {
    SP::ResourceObject* mpObject;
    IntrusivePtr() : mpObject(0) {}
    IntrusivePtr(SP::ResourceObject* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~IntrusivePtr() { if (mpObject) mpObject->Release(); }
    SP::ResourceObject* get() const { return mpObject; }
    SP::ResourceObject** GetAddressForUpdate();
    SP::ResourceObject** AsPPTypeParam() { return GetAddressForUpdate(); }
};
namespace SP {
using namespace FunctionalMatch;
}
// ---- items of slice s005580e0 end

// ---- items of slice s005598b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_pOTDBService;              // 0x015e3f00
extern const uint32_t kOTDBTypeA;         // 0x013f4308
extern const uint32_t kOTDBTypeB;         // 0x013f4318
template <int N> inline void ScratchSlots_s0055_98b0() { uint32_t s[N]; }
void* operator new(unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line);   // 0x00f473a0
void* operator new(unsigned int n);   // 0x006abeb0
namespace EA {
namespace Allocator {
struct ZoneObject_s0055_98b0 {
    static void* operator new(unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line);   // 0x00926020
};
}
}
struct Property {
    void*    mpData;      // +0x00 (data pointer when mnFlags & 0x30, else inline data)
    uint32_t pad04;
    uint32_t mnCount;     // +0x08
    uint32_t pad0c;
    uint16_t mnFlags;     // +0x10
    uint16_t mnType;      // +0x12

    void* GetValue()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
    uint32_t GetItemCount()
    {
        if (mnFlags & 0x30)
            return mnCount;
        else if (mnType != 0)
            return 1;
        return 0;
    }
};
struct PropertyList {
    virtual int AddRef();
    virtual int Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property*& prop);   // +0x24
};
struct IPropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppList);   // +0x2c
};
namespace EA {
template <typename T> class AutoRefCount_s0055_98b0 {
public:
    T* mpObject;
    AutoRefCount_s0055_98b0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s0055_98b0() { if (mpObject) mpObject->Release(); }
    void** AsPPVoidParam();
    T** AsPP() { return (T**)AsPPVoidParam(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
}
template <typename T> class RefPtr {
public:
    T* mpObject;
    RefPtr() : mpObject(0) {}
    ~RefPtr() { if (mpObject) mpObject->Release(); }
    T** AsPP()
    {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
struct IRefObj { virtual void v0(); virtual int AddRef(); virtual int Release(); };
struct cResBase1 : IRefObj {
    int mnRefCount;
    virtual ~cResBase1() {}
};
struct cResFinal : cResBase1, EA::Allocator::ZoneObject_s0055_98b0 {
    cResFinal();          // 0x0055bf10
    virtual ~cResFinal() {}
};
struct cOTDBResourceFactory : cResFinal {   // vtable 0x013f464c
    cOTDBResourceFactory() {}
    virtual ~cOTDBResourceFactory() {}
};
struct cSummarizerFinal {
    int mField;
    cSummarizerFinal();   // 0x0055bf50
    virtual ~cSummarizerFinal() {}
};
struct cSummarizerA : cSummarizerFinal {    // vtable 0x013f4628
    cSummarizerA() {}
    virtual ~cSummarizerA() {}
};
struct cSummarizerB : cSummarizerFinal {    // vtable 0x013f4604
    cSummarizerB() {}
    virtual ~cSummarizerB() {}
};
namespace Editor {
struct OTDB {   // the "Editor/OTDB" cheat; registers itself
    OTDB();     // 0x005640d0
    virtual ~OTDB();
    uint32_t pad[3];
};
}
struct cOTDBCheat : Editor::OTDB {          // vtable 0x013f4688
    cOTDBCheat() {}
    virtual ~cOTDBCheat() {}
};
template <typename T> struct ARC {   // EA::AutoRefCount with inline assignment
    T* mp;
    ARC& operator=(T* p)
    {
        if (p != mp) {
            T* old = mp;
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
    T* get() const { return mp; }
};
struct IHandlerRC_s0055_98b0 { virtual bool HandleMessage(uint32_t msgID, void* msg); };
struct IMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void AddHandler(IHandlerRC_s0055_98b0* handler, uint32_t id);   // +0x20
};
struct ICommandServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void AddCommands(const void* table, int count);       // +0x20
};
struct IResourceManager_s0055_98b0 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16();
    virtual bool RegisterFactory(bool add, IRefObj* factory, uint32_t a3);   // +0x44
};
struct ICheatManager;
namespace SP {
ICheatManager* CheatManager();            // 0x0067de20
}
namespace SP {
IPropertyManager* PropertyManager();      // 0x0067de30
}
namespace SP {
bool GetPropertyAsUint32(PropertyList* list, uint32_t id, uint32_t* value);   // 0x004af210
}
namespace SP {
bool IsPillRecordStale(uint32_t instanceID, int expectedValue);              // 0x00558bf0
}
namespace SP {
void WritePillRecord(uint32_t instanceID, uint32_t value);                    // 0x00558d50
}
namespace SP {
void TouchAsset(uint32_t instanceID, int flag);                               // 0x00570480
}
namespace EA {
namespace Messaging {
 IMessageServer* GetServer();   // 0x00883860
}
}
namespace EA {
namespace ResourceMan {
 IResourceManager_s0055_98b0* GetManager_s0055_98b0();   // 0x0067dcd0
}
}
ICommandServer* GetCommandServer();       // 0x006895b0
void* GetOTDBService();                   // 0x008de1a0 (returns the global at 0x01667aa0)
struct CommandInfo { uint32_t id; const char* name; const char* description; };
extern CommandInfo sCommandInfos[];       // 0x0150cbc0
namespace eastl {
template <typename T1, typename T2> struct pair_s0055_98b0 {
    T1 first;
    T2 second;
    pair_s0055_98b0(const T1& a, const T2& b) : first(a), second(b) {}
};
}
namespace eastl {
template <typename T1, typename T2> inline pair_s0055_98b0<T1, T2> make_pair(T1 a, T2 b) { return pair_s0055_98b0<T1, T2>(a, b); }
}
struct InsertResult { void* it; bool inserted; InsertResult() {} };
struct U32Set {                 // eastl::vector_set<uint32_t>
    uint32_t pad[5];
    InsertResult insert(const uint32_t& v);                       // 0x00554020
};
struct U32U32Map {              // eastl::vector_map<uint32_t, uint32_t>
    uint32_t pad[5];
    InsertResult insert(const eastl::pair_s0055_98b0<uint32_t, uint32_t>& v); // 0x00564960
};
struct U32FloatMap {            // eastl::vector_map<uint32_t, float>
    uint32_t pad[5];
    InsertResult insert(const eastl::pair_s0055_98b0<uint32_t, float>& v);    // 0x00564960 (folded)
};
struct AssetTable {             // hash_map<uint32_t, AutoRefCount<cIResource>>
    uint32_t pad[0x1b];
    bool Rebuild();                                   // 0x0056df80
    bool Find(uint32_t id, IRefObj** out);            // 0x0056def0
};
namespace SP {
namespace FunctionalMatch {
enum EqualConstraint_s0055_98b0 { kEquals_s0055_98b0 = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
struct ConstraintVec {
    void* mpBegin; void* mpEnd; void* mpCapacity; uint32_t mAllocator;
    ~ConstraintVec();                                 // 0x004e1780
};
}
}
namespace SP {
namespace FunctionalMatch {
struct Constraint_s0055_98b0 {
    unsigned int mParameter;
    int mType;
    int mMin, mMax;
    ConstraintVec mConstraints;
    uint32_t pad20;
    Constraint_s0055_98b0(unsigned int param, EqualConstraint_s0055_98b0, int value);   // 0x00558960
};
}
}
namespace SP {
struct cISPObjectTemplateDB_s0055_98b0 {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30();
    virtual void AddSummarizer(cSummarizerFinal* summarizer);   // +0x7c
};
}
namespace SP {
struct cIMatchTuning { virtual void m0(); };
}
namespace SP {
class cSPObjectTemplateDB_s0055_98b0 : public cISPObjectTemplateDB_s0055_98b0, public cIMatchTuning, public IHandlerRC_s0055_98b0 {
public:
    int mRefCount;                              // +0x0c
    uint32_t pad010[(0x94 - 0x10) / 4];
    U32Set mResourceTypesToReindex;             // +0x094
    uint32_t pad0a8[(0xc4 - 0xa8) / 4];
    U32U32Map mPopulationCount;                 // +0x0c4
    uint32_t pad0d8[(0x1d4 - 0xd8) / 4];
    AssetTable mAssets;                         // +0x1d4
    U32FloatMap mClassifierWeights;             // +0x240
    uint32_t pad254[(0x26c - 0x254) / 4];
    ARC<IRefObj> mpFactory;                     // +0x26c

    bool Init();  // 0x005598b0 (SP::cSPObjectTemplateDB::Init)
    bool LoadAssetParameters(IRefObj* asset, uint32_t count, void* data, bool stale);   // 0x0055d9e0
    void AddPriorityConstraint(const FunctionalMatch::Constraint_s0055_98b0& c, int priority);      // 0x00562680
    bool LoadDatabase();                                                                 // 0x0055ff10
};
}
// ---- items of slice s005598b0 end

// ---- items of slice s0055a550 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
namespace Audio {
class cCityMusicSummarizer {
public:
    uint32_t GetParamId(uint32_t index);
    uint32_t GetParamType(uint32_t index);
    bool ExtractParameters(int a, void* b);   // @ 0x0055AA00 (partial)
};
}
}
// ---- items of slice s0055a550 end

// ---- items of slice s0055beb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
namespace Editor {
class ObjectTemplateDB {
public:
    ObjectTemplateDB();
    uint32_t pad[0x270 / 4];
};
}
namespace SP {
class cFunctionalTestCheat_s0055_beb0 {
public:
    const char* Description(int index);  // 0x0055beb0 (SP::cFunctionalTestCheat::Description)
    bool IsEnabled();
};  // namespace SP
}
template <int N> inline void ScratchSlots_s0055_beb0() { uint32_t slots[N]; }
template <typename T> struct ARC_s0055_beb0 {   // EA::AutoRefCount
    T* mp;
    ARC_s0055_beb0() : mp(0) {}
    ~ARC_s0055_beb0() { if (mp) mp->Release(); }
    ARC_s0055_beb0& operator=(T* p)
    {
        if (p != mp) {
            T* old = mp;
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
    void Reset()
    {
        if (mp) {
            T* p = mp;
            mp = 0;
            p->Release();
        }
    }
    T* operator->() const { return mp; }
};
template <typename T> struct ParamVec {   // eastl::vector<T>, 12-byte elements
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const;                          // 0x00526430 (ICF alias)
    void resize(uint32_t n);                     // 0x00564350
    void erase(T* first, T* last);               // 0x0050f740
    void truncate(uint32_t n);                   // 0x004548d0
};
struct Key3 { uint32_t a, b, c; };
struct cISPObjectTemplateDB_s0055_beb0 {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual bool IsObjectKnown(const Key3* key);                    // +0x70
    virtual void s29();
    virtual void Reload(const Key3* key, int flag);                 // +0x78
};
struct cIMatchTuning_s0055_beb0 { virtual void m0(); };
struct IMessageServer_s0055_beb0 {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void Post(uint32_t id, void* data, int flag);        // +0x14
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10();
    virtual void RemoveHandler(void* handler, uint32_t id, int pri);   // +0x2c
};
struct IHandlerRC_s0055_beb0 {
    virtual bool HandleMessage(uint32_t msgID, void* msg);  // 0x007c1170 (IHandlerRC::HandleMessage)
};
struct ICheatManager_s0055_beb0 {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4();
    virtual void c5(); virtual void c6();
    virtual void Remove(const char* name);   // +0x1c
};
struct ICommandServer_s0055_beb0 {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual void RegisterCommands(const void* table, int count);   // +0x2c
};
namespace SP {
ICheatManager_s0055_beb0* CheatManager_s0055_beb0();            // 0x0067de20
}
namespace EA {
namespace Messaging {
 IMessageServer_s0055_beb0* GetServer_s0055_beb0();   // 0x00883860
}
}
ICommandServer_s0055_beb0* GetCommandServer_s0055_beb0();       // 0x006895b0
extern char sCommandInfos_s0055_beb0[];              // 0x0150cbc0, 12-byte entries
struct U32Vec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    bool empty() const;                     // 0x00526430
    void clear() { erase(mpBegin, mpEnd); }
    void erase(uint32_t* a, uint32_t* b);   // 0x004769b0
};
struct U32Set_s0055_beb0 {
    uint32_t pad[5];
    void insert(void* pairOut, const uint32_t* v);    // 0x00554020
};
struct Rng { uint32_t seed; uint32_t RandomUint32Uniform(uint32_t n); };   // 0x00a68fb0
struct ClearableTable { uint32_t pad[0x20]; void Clear(); };              // 0x00564cd0
namespace SP {
class cSPObjectTemplateDB_s0055_beb0 : public cISPObjectTemplateDB_s0055_beb0, public cIMatchTuning_s0055_beb0, public IHandlerRC_s0055_beb0 {
public:
    int mRefCount;                             // +0x0c
    uint32_t pad10[(0x40 - 0x10) / 4];
    uint8_t mFlag40;                           // +0x40
    uint8_t pad41[3];
    uint32_t pad44[(0x64 - 0x44) / 4];
    U32Set_s0055_beb0 mSet;                               // +0x64
    uint32_t pad78[(0x7c - 0x78) / 4];
    U32Vec mVec;                               // +0x7c
    uint32_t pad88[(0x1cc - 0x88) / 4];
    Rng mRandom;                               // +0x1cc
    uint8_t mDirty;                            // +0x1d0
    uint8_t pad1d1[3];
    uint32_t pad1d4[(0x1ec - 0x1d4) / 4];
    ClearableTable mTable;                     // +0x1ec
    ARC_s0055_beb0<IRefObj> mpAuto;                       // +0x26c

    virtual bool HandleMessage(uint32_t msgID, void* msg);  // 0x0055c3c0 (SP::cSPObjectTemplateDB::HandleMessage)
    bool Shutdown();  // 0x0055bfb0 (SP::cSPObjectTemplateDB::Shutdown)
    bool RandomizeFirstN(ParamVec<Key3>* v, int n);
    void* AsInterface(uint32_t type);  // 0x0055c690 (SP::cSPObjectTemplateDB::AsInterface)
    void CheckForMinPopulations();      // 0x00561bd0
    void FUN_00561220(void* p);
    void FUN_0055e190(int a, int b);
    void FUN_00560470();
    void SetMode(const char* name);   // 0x0052e650
};
}
struct cResBase0 { virtual ~cResBase0() {} };
struct AtomicInt32 {
    long mValue;
    void SetValue(long v) { long* p = &mValue; _InterlockedExchange(p, v); }
};
struct cResBase1_s0055_beb0 : cResBase0 {
    AtomicInt32 mnRefCount;
    cResBase1_s0055_beb0() { mnRefCount.SetValue(0); }
    virtual ~cResBase1_s0055_beb0() {}
};
struct cResFinal_s0055_beb0 : cResBase1_s0055_beb0 {
    cResFinal_s0055_beb0();
    virtual ~cResFinal_s0055_beb0() {}
};
struct cSummarizerBase {
    int mField;
    cSummarizerBase() : mField(0) {}
    virtual ~cSummarizerBase() {}
};
struct cSummarizerFinal_s0055_beb0 : cSummarizerBase {
    cSummarizerFinal_s0055_beb0();
    virtual ~cSummarizerFinal_s0055_beb0() {}
};
// ---- items of slice s0055beb0 end

// ---- items of slice s0055ce80 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<typename T> struct EraseFrame { enum { kSlots = 6 }; };
template<> struct EraseFrame<uint32_t> { enum { kSlots = 4 }; };
template<> struct EraseFrame<int> { enum { kSlots = 4 }; };
template<> struct EraseFrame<float> { enum { kSlots = 4 }; };
namespace eastl {
 template<typename T1, typename T2> struct pair_s0055_ce80; 
}
template<> struct EraseFrame<eastl::pair_s0055_ce80<uint32_t, float> > { enum { kSlots = 4 }; };
namespace eastl {
struct allocator_s0055_ce80 { allocator_s0055_ce80() {} };
}
namespace eastl {
struct sp_vector_allocator_s0055_ce80;
}
namespace eastl {
void EASTL_allocator_deallocate(void* p); // 0x00f47380
}
namespace eastl {
inline void EASTLFree(void* p) { EASTL_allocator_deallocate(p); }
}
namespace eastl {
struct sp_vector_allocator_s0055_ce80 : public allocator_s0055_ce80 {
    sp_vector_allocator_s0055_ce80() {}
    sp_vector_allocator_s0055_ce80(const allocator_s0055_ce80& a);
    void deallocate(void* p, size_t n) { void* pMem = p; EASTLFree(pMem); }
    const char* mpName;
    uint32_t mFlags;
};
}
namespace eastl {
template<typename T> struct less_s0055_ce80 {
    less_s0055_ce80() {}
    bool operator()(const T& a, const T& b) const { return a < b; }
};
}
namespace eastl {
struct random_access_iterator_tag { random_access_iterator_tag() {} };
}
namespace eastl {
struct false_type { false_type() {} };
}
namespace eastl {
template<typename I, typename T>
inline I find(I first, I last, const T& value) {
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}
}
namespace eastl {
template<typename T1, typename T2>
struct pair_s0055_ce80 {
    T1 first;
    T2 second;
    pair_s0055_ce80() {}
    pair_s0055_ce80(const T1& x, const T2& y) : first(x), second(y) {}
    template<typename U, typename W>
    pair_s0055_ce80(const pair_s0055_ce80<U, W>& p) : first(p.first), second(p.second) {}
};
}
namespace eastl {
template<typename T, typename A = allocator_s0055_ce80>
class vector_s0055_ce80 {
public:
    typedef T* iterator;
    typedef T value_type;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;

    vector_s0055_ce80() : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator() { ScratchSlots<1>(); }
    vector_s0055_ce80(const vector_s0055_ce80& x);
    ~vector_s0055_ce80();
    iterator begin() { return mpBegin; }
    iterator end() { return mpEnd; }
    size_t size() const { return mpEnd - mpBegin; }
    T& operator[](size_t n) { return *(mpBegin + n); }
    const T& operator[](size_t n) const { return *(mpBegin + n); }
    iterator erase(iterator first, iterator last);
    iterator erase(iterator position);
    void clear() { ScratchSlots<EraseFrame<T>::kSlots>(); erase(mpBegin, mpEnd); }
    void clear_noframe() { erase(mpBegin, mpEnd); }
    bool empty() const;
    void swap(vector_s0055_ce80& x);
    template<typename It> void DoAssignFromIterator(It first, It last, random_access_iterator_tag);
    template<typename It> void assign(It first, It last) {
        false_type bIsIntegral;
        false_type bIsPOD;
        DoAssignFromIterator(first, last, random_access_iterator_tag());
    }
    void reserve(size_t n);
    void push_back(const T& value);
    iterator insert(iterator position, const T& value);
    void DoInsertValues(iterator position, size_t n, const T& value);
    void insert(iterator position, size_t n, const T& value) { DoInsertValues(position, n, value); }
    void resize(size_t n);
};
}
namespace eastl {
template<typename T, typename A>
vector_s0055_ce80<T, A>::~vector_s0055_ce80() {
    for (T* p = mpBegin; p < mpEnd; ++p)
        p->~T();
    if (mpBegin)
        mAllocator.deallocate(mpBegin, (mpCapacity - mpBegin) * sizeof(T));
}
}
namespace eastl {
template<typename In, typename Out>
inline Out copy_impl3(In first, In last, Out result) {
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}
}
namespace eastl {
template<typename In, typename Out>
inline Out copy_n3(In first, In last, Out result) {
    const bool isPOD = false;
    const bool isScalar = false;
    const bool isTrivial = false;
    return copy_impl3(first, last, result);
}
}
namespace eastl {
template<typename T, typename A>
typename vector_s0055_ce80<T, A>::iterator vector_s0055_ce80<T, A>::erase(iterator position) {
    if ((position + 1) < mpEnd)
        copy_n3(position + 1, mpEnd, position);
    --mpEnd;
    mpEnd->~T();
    return position;
}
}
namespace eastl {
template<typename T, typename A>
void vector_s0055_ce80<T, A>::resize(size_t n) {
    if (n > (size_t)(mpEnd - mpBegin))
        insert(mpEnd, n - (size_t)(mpEnd - mpBegin), value_type());
    else
        erase(mpBegin + n, mpEnd);
    ScratchSlots<6>();
}
}
namespace eastl {
template<typename K, typename C = less_s0055_ce80<K>, typename A = sp_vector_allocator_s0055_ce80>
class vector_set_s0055_ce80 : public vector_s0055_ce80<K, A> {
public:
    typedef vector_s0055_ce80<K, A> base_type;
    typedef K* iterator;
    C mCompare;
    vector_set_s0055_ce80(const vector_set_s0055_ce80& x);
    ~vector_set_s0055_ce80();
    pair_s0055_ce80<iterator, iterator> equal_range(const K& k);
    iterator find(const K& k) {
        const pair_s0055_ce80<iterator, iterator> pairIts(equal_range(k));
        ScratchSlots<5>();
        if (pairIts.first != pairIts.second)
            return pairIts.first;
        return base_type::end();
    }
};
}
namespace eastl {
template<typename K, typename V, typename C = less_s0055_ce80<K>, typename A = sp_vector_allocator_s0055_ce80>
class vector_map_s0055_ce80 : public vector_s0055_ce80<pair_s0055_ce80<K, V>, A> {
public:
    typedef vector_s0055_ce80<pair_s0055_ce80<K, V>, A> base_type;
    typedef pair_s0055_ce80<K, V> value_type;
    typedef pair_s0055_ce80<K, V>* iterator;
    C mCompare;
    pair_s0055_ce80<iterator, iterator> equal_range(const K& k);
    iterator find(const K& k) {
        const pair_s0055_ce80<iterator, iterator> pairIts(equal_range(k));
        ScratchSlots<5>();
        if (pairIts.first != pairIts.second)
            return pairIts.first;
        return base_type::end();
    }
    // Same as find(); this instance reserves a smaller declined-inline frame.
    iterator find_(const K& k) {
        const pair_s0055_ce80<iterator, iterator> pairIts(equal_range(k));
        ScratchSlots<3>();
        if (pairIts.first != pairIts.second)
            return pairIts.first;
        return base_type::end();
    }
    V& operator[](const K& k);
};
}
namespace eastl {
template<typename I, typename T, typename C>
I lower_bound(I first, I last, const T& value, C compare);
}
namespace eastl {
template<typename K, typename V, typename C, typename A>
V& vector_map_s0055_ce80<K, V, C, A>::operator[](const K& k) {
    iterator pos;   // unused in the original as well (it occupies a frame slot)
    iterator itLB = lower_bound(base_type::begin(), base_type::end(), k, mCompare);
    if ((itLB == base_type::end()) || mCompare(k, (*itLB).first)) {
        itLB = base_type::insert(itLB, value_type(k, V()));
    }
    return (*itLB).second;
}
}
namespace eastl {
struct rbtree_node_base_s0055_ce80 {
    rbtree_node_base_s0055_ce80* mpNodeRight;
    rbtree_node_base_s0055_ce80* mpNodeLeft;
    rbtree_node_base_s0055_ce80* mpNodeParent;
    char mColor;
};
}
namespace eastl {
template<typename V>
struct rbtree_iterator_s0055_ce80 {
    rbtree_node_base_s0055_ce80* mpNode;
    rbtree_iterator_s0055_ce80(const rbtree_node_base_s0055_ce80* pNode);
    rbtree_iterator_s0055_ce80(const rbtree_iterator_s0055_ce80& x) : mpNode(x.mpNode) {}
    V& operator*() const;
    rbtree_iterator_s0055_ce80& operator++();
    bool operator!=(const rbtree_iterator_s0055_ce80& x) const { return mpNode != x.mpNode; }
};
}
namespace eastl {
template<typename K, typename V, typename C = less_s0055_ce80<K>, typename A = allocator_s0055_ce80>
class map_s0055_ce80 {
public:
    typedef pair_s0055_ce80<const K, V> value_type;
    typedef rbtree_iterator_s0055_ce80<value_type> iterator;
    C mCompare;
    rbtree_node_base_s0055_ce80 mAnchor;
    size_t mnSize;
    A mAllocator;
    iterator begin() { return iterator(mAnchor.mpNodeLeft); }
    iterator end() { return iterator(&mAnchor); }
    size_t size() const { return mnSize; }
    iterator find(const K& k);
    pair_s0055_ce80<iterator, iterator> equal_range(const K& k);

    struct const_iterator {
        rbtree_node_base_s0055_ce80* mpNode;
        const_iterator(const iterator& x);
        const value_type& operator*() const;
        const_iterator& operator++();
        bool operator!=(const const_iterator& x) const { return mpNode != x.mpNode; }
    };

    struct key_iterator {
        rbtree_node_base_s0055_ce80* mpNode;
        key_iterator(const rbtree_node_base_s0055_ce80* pNode);
        const K& operator*() const;
        key_iterator& operator++();
        bool operator!=(const key_iterator& x) const { return mpNode != x.mpNode; }
    };
    key_iterator key_begin() { return key_iterator(mAnchor.mpNodeLeft); }
    key_iterator key_end() { return key_iterator(&mAnchor); }
};
}
namespace eastl {
struct true_type {};
}
namespace eastl {
struct prime_rehash_policy_s0055_ce80 {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
};
}
namespace eastl {
template<typename V>
struct hash_node_s0055_ce80 {
    V mValue;
    hash_node_s0055_ce80* mpNext;
};
}
namespace eastl {
template<typename V>
struct hashtable_iterator_base {
    hash_node_s0055_ce80<V>* mpNode;
    hash_node_s0055_ce80<V>** mpBucket;
    hashtable_iterator_base(hash_node_s0055_ce80<V>* pNode, hash_node_s0055_ce80<V>** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
    void increment_bucket();
};
}
namespace eastl {
template<typename V>
struct hashtable_iterator : public hashtable_iterator_base<V> {
    typedef hashtable_iterator_base<V> base_type;
    hashtable_iterator(hash_node_s0055_ce80<V>** pBucket) : base_type(*pBucket, pBucket) {}
    hashtable_iterator(const hashtable_iterator& x) : base_type(x.mpNode, x.mpBucket) {}
    V* operator->() const { return &base_type::mpNode->mValue; }
    hashtable_iterator& operator++() {
        base_type::mpNode = base_type::mpNode->mpNext;
        while (!base_type::mpNode)
            base_type::mpNode = *++base_type::mpBucket;
        return *this;
    }
    bool operator!=(const hashtable_iterator& x) const { return base_type::mpNode != x.mpNode; }
};
}
namespace eastl {
template<typename K, typename V, typename A, typename ExtractKey, typename Equal, typename H1, typename H2, typename H>
class hashtable_s0055_ce80 {
public:
    typedef V value_type;
    typedef hashtable_iterator<V> iterator;
    typedef hash_node_s0055_ce80<V> node_type;
    typedef A allocator_type;

    uint32_t mFunctorPad;   // empty hash/compare functor bases
    node_type** mpBucketArray;
    size_t mnBucketCount;
    size_t mnElementCount;
    prime_rehash_policy_s0055_ce80 mRehashPolicy;
    A mAllocator;

    hashtable_s0055_ce80(size_t nBucketCount, const H1& h1, const H2& h2, const H& h, const Equal& eq, const ExtractKey& ek, const A& a);
    ~hashtable_s0055_ce80();
    iterator begin();
    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
    pair_s0055_ce80<iterator, bool> DoInsertValue(const value_type& value, true_type);
    pair_s0055_ce80<iterator, bool> insert(const value_type& value) { return DoInsertValue(value, true_type()); }
};
}
namespace eastl {
template<typename K, typename V, typename A, typename ExtractKey, typename Equal, typename H1, typename H2, typename H>
typename hashtable_s0055_ce80<K, V, A, ExtractKey, Equal, H1, H2, H>::iterator hashtable_s0055_ce80<K, V, A, ExtractKey, Equal, H1, H2, H>::begin() {
    iterator i(mpBucketArray);
    if (!i.mpNode)
        i.increment_bucket();
    return i;
}
}
struct ResourceKey_s0055_ce80 {
    uint32_t mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
};
namespace eastl {
 template<typename T> class basic_vector; template<typename T> class key_vector; 
}
namespace eastl {
template<typename T>
struct VectorBase_s0055_ce80 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s0055_ce80 mAllocator;
    VectorBase_s0055_ce80() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase_s0055_ce80();
};
}
namespace eastl {
template<typename T>
struct KeyVectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s0055_ce80 mAllocator;
    KeyVectorBase(const allocator_s0055_ce80& a) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
    ~KeyVectorBase();
};
}
namespace eastl {
template<typename T>
class key_vector : public KeyVectorBase<T> {
public:
    typedef KeyVectorBase<T> base_type;
    key_vector(const allocator_s0055_ce80& a = allocator_s0055_ce80()) : base_type(a) {}
    ~key_vector() { destruct(base_type::mpBegin, base_type::mpEnd); ScratchSlots<3>(); }
    size_t size() const { return base_type::mpEnd - base_type::mpBegin; }
    T& operator[](size_t n) { return base_type::mpBegin[n]; }
    T* begin() { return base_type::mpBegin; }
    T* end() { return base_type::mpEnd; }
    T* erase(T* first, T* last);
    void clear() { ScratchSlots<4>(); erase(base_type::mpBegin, base_type::mpEnd); }
};
}
namespace eastl {
template<typename T>
class basic_vector : public VectorBase_s0055_ce80<T> {
public:
    T& operator[](size_t n) { return VectorBase_s0055_ce80<T>::mpBegin[n]; }
    basic_vector() {}
    ~basic_vector() { destruct(VectorBase_s0055_ce80<T>::mpBegin, VectorBase_s0055_ce80<T>::mpEnd); ScratchSlots<3>(); }
};
}
namespace SP {
 class cEditorResource_s0055_ce80; 
}
namespace SP {
namespace Traits {
class cFeatureVector_s0055_ce80 {
public:
    bool IsEmpty() const;
    cFeatureVector_s0055_ce80& operator=(const cFeatureVector_s0055_ce80& x);
    char pad[0x1c];
};
}
}
namespace SP {
namespace Traits {
class cIClassifier_s0055_ce80 {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual uint32_t GetID();
    virtual uint32_t GetGroup();
    virtual void v06();
};
}
}
namespace SP {
namespace FunctionalMatch {
class cISummarizer_s0055_ce80 {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual uint32_t GetID();
    virtual uint32_t GetGroup();
    virtual void* GetSummary();
    virtual void v07();
    virtual bool Validate(cEditorResource_s0055_ce80* pResource, eastl::basic_vector<uint32_t>& blockIDs, int flags);
};
}
}
namespace SP {
class cISPObjectTemplateDB_s0055_ce80 {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c();
    virtual void OnAssetBanned(const ResourceKey_s0055_ce80& key, bool permanent);
};
}
namespace SP {
class cIMatchTuning_s0055_ce80 {
public:
    virtual void m00();
    virtual bool GetFeatureVector(uint32_t assetID, Traits::cFeatureVector_s0055_ce80& features);
    virtual void* FindSummaryByID(const uint32_t& id);
    virtual void* FindSummary(uint32_t id);
    virtual void SetClassifierWeights(const eastl::vector_map_s0055_ce80<uint32_t, float>& weights);
    virtual void GetDefaultClassifierWeights(eastl::vector_map_s0055_ce80<uint32_t, float>& weights);
    virtual bool ValidateResource(const ResourceKey_s0055_ce80& key, int flags);
};
}
namespace SP {
template<typename T> struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
};
}
namespace SP {
class cSPObjectTemplateDB_s0055_ce80 : public cISPObjectTemplateDB_s0055_ce80, public cIMatchTuning_s0055_ce80 {
public:
    struct AssetInfo {
        ResourceKey_s0055_ce80 mKey;
        uint32_t mnModelSubtype;
        Traits::cFeatureVector_s0055_ce80 mFeatureVector;
        eastl::vector_set_s0055_ce80<uint32_t> mGroupIDs;
        char pad44[0x50 - 0x44];
    };
    typedef eastl::vector_map_s0055_ce80<uint32_t, float> WeightMap;

    char pad08[0x14 - 0x08];
    eastl::vector_s0055_ce80<AssetInfo, eastl::sp_vector_allocator_s0055_ce80> mAssetList;    // +0x14
    char pad28[0x1ac - 0x28];
    WeightMap mClassifierWeights;                                        // +0x1ac
    bool mbUseClassifierWeights;                                         // +0x1c4
    char pad1c5[0x1ec - 0x1c5];
    eastl::map_s0055_ce80<uint32_t, AutoRefCount<Traits::cIClassifier_s0055_ce80> > mClassifierTable;            // +0x1ec
    eastl::map_s0055_ce80<uint32_t, AutoRefCount<FunctionalMatch::cISummarizer_s0055_ce80> > mSummarizerTable;   // +0x208
    char pad224[0x240 - 0x224];
    WeightMap mDefaultClassifierWeights;                                 // +0x240

    int FindAssetIndex(uint32_t assetID);
    virtual bool GetFeatureVector(uint32_t assetID, Traits::cFeatureVector_s0055_ce80& features);
    virtual void* FindSummaryByID(const uint32_t& id);
    virtual void* FindSummary(uint32_t id);
    virtual void SetClassifierWeights(const eastl::vector_map_s0055_ce80<uint32_t, float>& weights);
    virtual void GetDefaultClassifierWeights(eastl::vector_map_s0055_ce80<uint32_t, float>& weights);
    virtual bool ValidateResource(const ResourceKey_s0055_ce80& key, int flags);
    void SaveGroupRecords();
    uint32_t GetGroupForAssetGroup(uint32_t groupID);
    void BanAsset(const ResourceKey_s0055_ce80& key, bool permanent);

    // ---- unnamed/extra methods (slices s0055ce80..s00567a90) ----
    bool FUN_0055cff0(void* pKey);
    char FUN_0055d230(int index, void* pList);
    bool FUN_0055d790(void* pKey, void* pList);
    char FUN_0055d9e0(void* pObj, int count, void* pItems, char flag);
    char FUN_0055db30(void* pObj);
    bool FUN_0055cd90(void* pKey, void* pOut, void* pIn);
    int  FUN_00560c30(void* pKey);
    void FUN_00561850(int index);
    bool FUN_00558bf0(int a, int b);
};
}
namespace SP {
struct DBSub {
    bool GetResType();
    void Find(void* outIt, void* key);
    void End(void* outIt);
    void* Deref(void* it);
    void Insert(void* out, void* val);
    void AddVal(int a, void* p, unsigned value);
    void AddKey0(void* out, void* val, char flag);
    void AddKey1(void* out, void* val);
    void Destroy();
    void AddIter(void* outIt, void* it);
};
}
struct IRefObj_s0055_ce80 {
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    virtual void v3();
    virtual int GetA();
    virtual int GetB();
    virtual int GetCount();
    virtual int GetItem(int i);
};
// ---- items of slice s0055ce80 end

// ---- items of slice s0055dce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PaintStub {
    unsigned char FUN_0055dfe0();
    void* FUN_0055eae0(int* first, int count);
    char FUN_0055eb70(int* p);
    void* FUN_0055ec10(unsigned flags);
};
void FUN_0050f0d0(void* p, void* q);
void FUN_00568740(int* dst, int* first, int* last, uint32_t flag);
// ---- items of slice s0055dce0 end

// ---- items of slice s0055ec70 begin (TODO(rewrite): local stubs, replace by canonical classes)
unsigned DateTime_Set(int a);
namespace SP {
struct EcxStub70 {
    unsigned char FUN_0055f7a0();
    unsigned char FUN_0055f8e0();
    void FUN_0055f9e0();
    unsigned char FUN_0055fa20(void* key, char flag);
    unsigned char FUN_0055fb30(void* key);
    unsigned char FUN_0055fbb0(void* key);
};
}
namespace SP {
void FUN_00561850(int index);
}
namespace SP {
void FUN_00561970(int index);
}
namespace SP {
void FUN_005631e0(void* self, void* out);
}
namespace SP {
void FUN_00555980(void* out, void* key);
}
namespace SP {
void FUN_0048c720(void* it);
}
namespace SP {
void FUN_006926b0(void* obj);
}
namespace SP {
void* FUN_00554020(void* out, void* val);
}
// ---- items of slice s0055ec70 end

// ---- items of slice s00561970 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<typename T> struct EraseFrame_s0056_1970 { enum { kSlots = 6 }; };
template<> struct EraseFrame_s0056_1970<uint32_t> { enum { kSlots = 4 }; };
template<> struct EraseFrame_s0056_1970<int> { enum { kSlots = 4 }; };
template<> struct EraseFrame_s0056_1970<float> { enum { kSlots = 4 }; };
namespace eastl {
struct allocator_s0056_1970 { allocator_s0056_1970() {} };
}
namespace eastl {
struct sp_vector_allocator_s0056_1970 : public allocator_s0056_1970 {
    sp_vector_allocator_s0056_1970() {}
    const char* mpName;
    uint32_t mFlags;
};
}
namespace eastl {
template<typename T> struct less_s0056_1970 { less_s0056_1970() {} };
}
namespace eastl {
template<typename Container>
struct insert_iterator {
    Container* container;
    typename Container::iterator it;
    insert_iterator(Container& x, typename Container::iterator i) : container(&x), it(i) {}
    insert_iterator& operator=(const typename Container::value_type& value) {
        it = container->insert(it, value);
        ++it;
        return *this;
    }
    insert_iterator& operator*() { return *this; }
    insert_iterator& operator++(int) { return *this; }
};
}
namespace eastl {
template<typename Container>
struct key_insert_iterator {
    Container* container;
    typename Container::iterator it;
    key_insert_iterator(Container& x, typename Container::iterator i) : container(&x), it(i) {}
    template<typename Pair>
    key_insert_iterator& operator=(const Pair& value) {
        it = container->insert(it, value.first);
        ++it;
        return *this;
    }
    key_insert_iterator& operator*() { return *this; }
    key_insert_iterator& operator++(int) { return *this; }
};
}
namespace eastl {
template<typename Container>
inline key_insert_iterator<Container> key_inserter(Container& x, typename Container::iterator i) {
    return key_insert_iterator<Container>(x, i);
}
}
namespace eastl {
template<typename Container>
inline insert_iterator<Container> inserter(Container& x, typename Container::iterator i) {
    return insert_iterator<Container>(x, i);
}
}
namespace eastl {
template<typename I1, typename I2, typename O>
O set_difference(I1 first1, I1 last1, I2 first2, I2 last2, O result);
}
namespace eastl {
template<typename T1, typename T2>
struct pair_s0056_1970 {
    T1 first;
    T2 second;
};
}
namespace eastl {
template<typename T, typename A = allocator_s0056_1970>
class vector_s0056_1970 {
public:
    typedef T* iterator;
    typedef T value_type;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;

    vector_s0056_1970() : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator() { ScratchSlots<1>(); }
    vector_s0056_1970(const vector_s0056_1970& x);
    ~vector_s0056_1970();
    iterator begin() { return mpBegin; }
    iterator end() { return mpEnd; }
    size_t size() const { return mpEnd - mpBegin; }
    T& operator[](size_t n) { return *(mpBegin + n); }
    const T& operator[](size_t n) const { return *(mpBegin + n); }
    iterator erase(iterator first, iterator last);
    iterator erase(iterator position);
    void clear() { ScratchSlots<EraseFrame_s0056_1970<T>::kSlots>(); erase(mpBegin, mpEnd); }
    void clear_noframe() { erase(mpBegin, mpEnd); }
    bool empty() const;
    void swap(vector_s0056_1970& x);
    template<typename It> void DoAssignFromIterator(It first, It last, random_access_iterator_tag);
    template<typename It> void assign(It first, It last) {
        false_type bIsIntegral;
        false_type bIsPOD;
        DoAssignFromIterator(first, last, random_access_iterator_tag());
    }
    void reserve(size_t n);
    void push_back(const T& value);
    iterator insert(iterator position, const T& value);
};
}
namespace eastl {
template<typename K, typename C = less_s0056_1970<K>, typename A = sp_vector_allocator_s0056_1970>
class vector_set_s0056_1970 : public vector_s0056_1970<K, A> {
public:
    typedef vector_s0056_1970<K, A> base_type;
    typedef K* iterator;
    C mCompare;
    vector_set_s0056_1970(const vector_set_s0056_1970& x);
    ~vector_set_s0056_1970();
    pair_s0056_1970<iterator, iterator> equal_range(const K& k);
    iterator find(const K& k) {
        const pair_s0056_1970<iterator, iterator> pairIts(equal_range(k));
        ScratchSlots<5>();
        if (pairIts.first != pairIts.second)
            return pairIts.first;
        return base_type::end();
    }
};
}
namespace eastl {
template<typename K, typename V, typename C = less_s0056_1970<K>, typename A = sp_vector_allocator_s0056_1970>
class vector_map_s0056_1970 : public vector_s0056_1970<pair_s0056_1970<K, V>, A> {
public:
    typedef vector_s0056_1970<pair_s0056_1970<K, V>, A> base_type;
    typedef pair_s0056_1970<K, V>* iterator;
    C mCompare;
    pair_s0056_1970<iterator, iterator> equal_range(const K& k);
    iterator find(const K& k) {
        const pair_s0056_1970<iterator, iterator> pairIts(equal_range(k));
        ScratchSlots<5>();
        if (pairIts.first != pairIts.second)
            return pairIts.first;
        return base_type::end();
    }
    // Same as find(); this instance reserves a smaller declined-inline frame.
    iterator find_(const K& k) {
        const pair_s0056_1970<iterator, iterator> pairIts(equal_range(k));
        ScratchSlots<3>();
        if (pairIts.first != pairIts.second)
            return pairIts.first;
        return base_type::end();
    }
};
}
namespace eastl {
struct rbtree_node_base_s0056_1970 {
    rbtree_node_base_s0056_1970* mpNodeRight;
    rbtree_node_base_s0056_1970* mpNodeLeft;
    rbtree_node_base_s0056_1970* mpNodeParent;
    char mColor;
};
}
namespace eastl {
template<typename V>
struct rbtree_iterator_s0056_1970 {
    rbtree_node_base_s0056_1970* mpNode;
    rbtree_iterator_s0056_1970(const rbtree_node_base_s0056_1970* pNode);
    rbtree_iterator_s0056_1970(const rbtree_iterator_s0056_1970& x) : mpNode(x.mpNode) {}
    V& operator*() const;
    rbtree_iterator_s0056_1970& operator++();
    bool operator!=(const rbtree_iterator_s0056_1970& x) const { return mpNode != x.mpNode; }
};
}
namespace eastl {
template<typename K, typename V, typename C = less_s0056_1970<K>, typename A = allocator_s0056_1970>
class map_s0056_1970 {
public:
    typedef pair_s0056_1970<const K, V> value_type;
    typedef rbtree_iterator_s0056_1970<value_type> iterator;
    C mCompare;
    rbtree_node_base_s0056_1970 mAnchor;
    size_t mnSize;
    A mAllocator;
    iterator begin() { return iterator(mAnchor.mpNodeLeft); }
    iterator end() { return iterator(&mAnchor); }
    size_t size() const { return mnSize; }
    iterator find(const K& k);

    struct key_iterator {
        rbtree_node_base_s0056_1970* mpNode;
        key_iterator(const rbtree_node_base_s0056_1970* pNode);
        const K& operator*() const;
        key_iterator& operator++();
        bool operator!=(const key_iterator& x) const { return mpNode != x.mpNode; }
    };
    key_iterator key_begin() { return key_iterator(mAnchor.mpNodeLeft); }
    key_iterator key_end() { return key_iterator(&mAnchor); }
};
}
namespace eastl {
struct input_iterator_tag {};
}
namespace eastl {
template<typename In, typename Out>
inline Out copy(In first, In last, Out result, input_iterator_tag) {
    for (; first != last; ++first) {
        *result++ = *first;
        ScratchSlots<3>();
    }
    return result;
}
}
struct ResourceKey_s0056_1970 {
    uint32_t mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
};
class IConfigManager {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual int GetInt(uint32_t id);
};
class IMessageManager {
public:
    virtual void v00();
    virtual void MessageSend(uint32_t messageID, void* pData);
};
namespace SP {
IConfigManager* ConfigManager();
}
namespace SP {
IMessageManager* MessageManager();
}
namespace SP {
namespace FunctionalMatch {
enum eType_s0056_1970 {
    kInteger_s0056_1970 = 48342877,
    kFloat_s0056_1970 = 48343039,
    kTerminal_s0056_1970 = 48343507,
    kNotEqual_s0056_1970 = 0xcba453f7
};
}
}
namespace SP {
namespace FunctionalMatch {
enum EqualConstraint_s0056_1970 { kEquals_s0056_1970 = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
struct Constraint_s0056_1970 {
    unsigned int mParameter;
    eType_s0056_1970 mType;
    union {
        struct { int mMin; int mMax; } mIntVal;
        struct { float mMin; float mMax; } mFloatVal;
    };
    eastl::vector_s0056_1970<Constraint_s0056_1970, eastl::sp_vector_allocator_s0056_1970> mConstraints;

    Constraint_s0056_1970(unsigned int param, EqualConstraint_s0056_1970, int value);
};
}
}
namespace SP {
class cSPObjectTemplateDB_s0056_1970 {
public:
    struct AssetInfo {
        ResourceKey_s0056_1970 mKey;
        char pad0c[0x2c - 0x0c];
        eastl::vector_set_s0056_1970<uint32_t> mGroupIDs;
        char pad44[0x50 - 0x44];
    };
    struct PriorityConstraint {
        uint32_t mnTag;
        Constraint_s0056_1970 mConstraint;
        PriorityConstraint(uint32_t tag, const Constraint_s0056_1970& c) : mnTag(tag), mConstraint(c) {}
        bool operator==(uint32_t tag) const { return mnTag == tag; }
    };
    typedef eastl::vector_map_s0056_1970<uint32_t, uint32_t> CountMap;
    typedef eastl::map_s0056_1970<int, eastl::vector_set_s0056_1970<uint32_t> > IntValueMap;
    typedef eastl::map_s0056_1970<float, eastl::vector_set_s0056_1970<uint32_t> > FloatValueMap;

    char pad00[0x14];
    eastl::vector_s0056_1970<AssetInfo, eastl::sp_vector_allocator_s0056_1970> mAssetList;    // +0x14
    eastl::vector_set_s0056_1970<uint32_t> mFreeList;                               // +0x28
    char pad40[0x64 - 0x40];
    eastl::vector_set_s0056_1970<uint32_t> mCandidates;                             // +0x64
    char pad7c[0xac - 0x7c];
    CountMap mPopulationCount;                                           // +0xac
    CountMap mRefillCount;                                               // +0xc4
    CountMap mTypePopulation;                                            // +0xdc
    eastl::map_s0056_1970<uint32_t, IntValueMap> mIntParameters;                    // +0xf4
    eastl::map_s0056_1970<uint32_t, FloatValueMap> mFloatParameters;                // +0x110
    eastl::vector_set_s0056_1970<uint32_t> mMatchResults;                           // +0x12c
    eastl::vector_set_s0056_1970<uint32_t> mResultSet;                              // +0x144
    eastl::vector_set_s0056_1970<uint32_t> mScratchSet;                             // +0x15c
    char pad174[0x258 - 0x174];
    eastl::vector_s0056_1970<PriorityConstraint, eastl::sp_vector_allocator_s0056_1970> mPriorityConstraints; // +0x258

    void DecreasePopulation(int index);
    void CheckForMinPopulations();  // 0x00561bd0 (SP::cSPObjectTemplateDB::CheckForMinPopulations)
    void RebuildFreeList();
    void ReleaseAsset(int index);
    void FindMatching(eastl::vector_set_s0056_1970<uint32_t>* pResults, const Constraint_s0056_1970& c);
    void AddIntMatches(eastl::vector_set_s0056_1970<uint32_t>* pResults, int minVal, int maxVal, IntValueMap& values);
    void AddFloatMatches(eastl::vector_set_s0056_1970<uint32_t>* pResults, float minVal, float maxVal, FloatValueMap& values);
    void FilterByConstraint(eastl::vector_set_s0056_1970<uint32_t>& candidates, const Constraint_s0056_1970& c);
    bool GetAssetKeys(eastl::vector_s0056_1970<uint32_t>& indices, eastl::vector_s0056_1970<ResourceKey_s0056_1970>& keys);
    void ExcludeCandidates(eastl::vector_set_s0056_1970<uint32_t>& candidates, bool force);
    void AddPriorityConstraint(const Constraint_s0056_1970& c, uint32_t tag);
    void RemovePriorityConstraint(uint32_t tag);
    void SetExcludedParameter(int value);
    bool GetFloatParameterValues(uint32_t paramID, eastl::vector_s0056_1970<float>& values);
    bool GetIntParameterValues(uint32_t paramID, eastl::vector_s0056_1970<int>& values);
    bool GetFloatParameterTable(uint32_t paramID, eastl::vector_s0056_1970<float>& values, eastl::vector_s0056_1970<ResourceKey_s0056_1970>& keys);
    bool GetIntParameterTable(uint32_t paramID, eastl::vector_s0056_1970<int>& values, eastl::vector_s0056_1970<ResourceKey_s0056_1970>& keys);
    void ClearExcludedParameter();
};
}
// ---- items of slice s00561970 end

// ---- items of slice s005628d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
void FUN_004769b0(void* a, void* b);
}
namespace SP {
bool FUN_00562510(void* self, void* out);
}
namespace SP {
void FUN_00565500(void* self, void* first, int count);
}
namespace SP {
void FUN_0055c2e0(void* a, void* b);
}
namespace SP {
struct CandidateDBStub {
    void AssignCandidates(void* out, void* pRange);
    bool TryFilterCandidates(void* a, void* b, void* pRange);
};
}
// ---- items of slice s005628d0 end

// ---- items of slice s005634e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<typename T> struct EraseFrame_s0056_34e0 { enum { kSlots = 6 }; };
template<> struct EraseFrame_s0056_34e0<uint32_t> { enum { kSlots = 4 }; };
template<> struct EraseFrame_s0056_34e0<int> { enum { kSlots = 4 }; };
template<> struct EraseFrame_s0056_34e0<float> { enum { kSlots = 4 }; };
namespace eastl {
 template<typename T1, typename T2> struct pair_s0056_34e0; 
}
template<> struct EraseFrame_s0056_34e0<eastl::pair_s0056_34e0<uint32_t, float> > { enum { kSlots = 4 }; };
namespace eastl {
struct allocator_s0056_34e0 { allocator_s0056_34e0() {} };
}
namespace eastl {
struct sp_vector_allocator_s0056_34e0;
}
namespace eastl {
struct sp_vector_allocator_s0056_34e0 : public allocator_s0056_34e0 {
    sp_vector_allocator_s0056_34e0() {}
    sp_vector_allocator_s0056_34e0(const allocator_s0056_34e0& a);
    void deallocate(void* p, size_t n) { void* pMem = p; EASTLFree(pMem); }
    const char* mpName;
    uint32_t mFlags;
};
}
namespace eastl {
template<typename T> struct less_s0056_34e0 {
    less_s0056_34e0() {}
    bool operator()(const T& a, const T& b) const { return a < b; }
};
}
namespace eastl {
template<typename T1, typename T2>
struct pair_s0056_34e0 {
    T1 first;
    T2 second;
    pair_s0056_34e0() {}
    pair_s0056_34e0(const T1& x, const T2& y) : first(x), second(y) {}
    template<typename U, typename W>
    pair_s0056_34e0(const pair_s0056_34e0<U, W>& p) : first(p.first), second(p.second) {}
};
}
namespace eastl {
template<typename T, typename A = allocator_s0056_34e0>
class vector_s0056_34e0 {
public:
    typedef T* iterator;
    typedef T value_type;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;

    vector_s0056_34e0() : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator() { ScratchSlots<1>(); }
    vector_s0056_34e0(const vector_s0056_34e0& x);
    ~vector_s0056_34e0();
    iterator begin() { return mpBegin; }
    iterator end() { return mpEnd; }
    size_t size() const { return mpEnd - mpBegin; }
    T& operator[](size_t n) { return *(mpBegin + n); }
    const T& operator[](size_t n) const { return *(mpBegin + n); }
    iterator erase(iterator first, iterator last);
    iterator erase(iterator position);
    void clear() { ScratchSlots<EraseFrame_s0056_34e0<T>::kSlots>(); erase(mpBegin, mpEnd); }
    void clear_noframe() { erase(mpBegin, mpEnd); }
    bool empty() const;
    void swap(vector_s0056_34e0& x);
    template<typename It> void DoAssignFromIterator(It first, It last, random_access_iterator_tag);
    template<typename It> void assign(It first, It last) {
        false_type bIsIntegral;
        false_type bIsPOD;
        DoAssignFromIterator(first, last, random_access_iterator_tag());
    }
    void reserve(size_t n);
    void push_back(const T& value);
    iterator insert(iterator position, const T& value);
    void DoInsertValues(iterator position, size_t n, const T& value);
    void insert(iterator position, size_t n, const T& value) { DoInsertValues(position, n, value); }
    void resize(size_t n);
};
}
namespace eastl {
template<typename T, typename A>
vector_s0056_34e0<T, A>::~vector_s0056_34e0() {
    for (T* p = mpBegin; p < mpEnd; ++p)
        p->~T();
    if (mpBegin)
        mAllocator.deallocate(mpBegin, (mpCapacity - mpBegin) * sizeof(T));
}
}
namespace eastl {
template<typename T, typename A>
void vector_s0056_34e0<T, A>::resize(size_t n) {
    if (n > (size_t)(mpEnd - mpBegin))
        insert(mpEnd, n - (size_t)(mpEnd - mpBegin), value_type());
    else
        erase(mpBegin + n, mpEnd);
    ScratchSlots<6>();
}
}
namespace eastl {
template<typename K, typename C = less_s0056_34e0<K>, typename A = sp_vector_allocator_s0056_34e0>
class vector_set_s0056_34e0 : public vector_s0056_34e0<K, A> {
public:
    typedef vector_s0056_34e0<K, A> base_type;
    typedef K* iterator;
    C mCompare;
    vector_set_s0056_34e0(const vector_set_s0056_34e0& x);
    ~vector_set_s0056_34e0();
    pair_s0056_34e0<iterator, iterator> equal_range(const K& k);
    iterator find(const K& k) {
        const pair_s0056_34e0<iterator, iterator> pairIts(equal_range(k));
        ScratchSlots<5>();
        if (pairIts.first != pairIts.second)
            return pairIts.first;
        return base_type::end();
    }
};
}
namespace eastl {
template<typename K, typename V, typename C = less_s0056_34e0<K>, typename A = sp_vector_allocator_s0056_34e0>
class vector_map_s0056_34e0 : public vector_s0056_34e0<pair_s0056_34e0<K, V>, A> {
public:
    typedef vector_s0056_34e0<pair_s0056_34e0<K, V>, A> base_type;
    typedef pair_s0056_34e0<K, V> value_type;
    typedef pair_s0056_34e0<K, V>* iterator;
    C mCompare;
    pair_s0056_34e0<iterator, iterator> equal_range(const K& k);
    iterator find(const K& k) {
        const pair_s0056_34e0<iterator, iterator> pairIts(equal_range(k));
        ScratchSlots<5>();
        if (pairIts.first != pairIts.second)
            return pairIts.first;
        return base_type::end();
    }
    // Same as find(); this instance reserves a smaller declined-inline frame.
    iterator find_(const K& k) {
        const pair_s0056_34e0<iterator, iterator> pairIts(equal_range(k));
        ScratchSlots<3>();
        if (pairIts.first != pairIts.second)
            return pairIts.first;
        return base_type::end();
    }
    V& operator[](const K& k);
};
}
namespace eastl {
template<typename K, typename V, typename C, typename A>
V& vector_map_s0056_34e0<K, V, C, A>::operator[](const K& k) {
    iterator pos;   // unused in the original as well (it occupies a frame slot)
    iterator itLB = lower_bound(base_type::begin(), base_type::end(), k, mCompare);
    if ((itLB == base_type::end()) || mCompare(k, (*itLB).first)) {
        itLB = base_type::insert(itLB, value_type(k, V()));
    }
    return (*itLB).second;
}
}
namespace eastl {
struct rbtree_node_base_s0056_34e0 {
    rbtree_node_base_s0056_34e0* mpNodeRight;
    rbtree_node_base_s0056_34e0* mpNodeLeft;
    rbtree_node_base_s0056_34e0* mpNodeParent;
    char mColor;
};
}
namespace eastl {
template<typename V>
struct rbtree_iterator_s0056_34e0 {
    rbtree_node_base_s0056_34e0* mpNode;
    rbtree_iterator_s0056_34e0(const rbtree_node_base_s0056_34e0* pNode);
    rbtree_iterator_s0056_34e0(const rbtree_iterator_s0056_34e0& x) : mpNode(x.mpNode) {}
    V& operator*() const;
    rbtree_iterator_s0056_34e0& operator++();
    bool operator!=(const rbtree_iterator_s0056_34e0& x) const { return mpNode != x.mpNode; }
};
}
namespace eastl {
template<typename K, typename V, typename C = less_s0056_34e0<K>, typename A = allocator_s0056_34e0>
class map_s0056_34e0 {
public:
    typedef pair_s0056_34e0<const K, V> value_type;
    typedef rbtree_iterator_s0056_34e0<value_type> iterator;
    C mCompare;
    rbtree_node_base_s0056_34e0 mAnchor;
    size_t mnSize;
    A mAllocator;
    iterator begin() { return iterator(mAnchor.mpNodeLeft); }
    iterator end() { return iterator(&mAnchor); }
    size_t size() const { return mnSize; }
    iterator find(const K& k);
    pair_s0056_34e0<iterator, iterator> equal_range(const K& k);

    struct const_iterator {
        rbtree_node_base_s0056_34e0* mpNode;
        const_iterator(const iterator& x);
        const value_type& operator*() const;
        const_iterator& operator++();
        bool operator!=(const const_iterator& x) const { return mpNode != x.mpNode; }
    };

    struct key_iterator {
        rbtree_node_base_s0056_34e0* mpNode;
        key_iterator(const rbtree_node_base_s0056_34e0* pNode);
        const K& operator*() const;
        key_iterator& operator++();
        bool operator!=(const key_iterator& x) const { return mpNode != x.mpNode; }
    };
    key_iterator key_begin() { return key_iterator(mAnchor.mpNodeLeft); }
    key_iterator key_end() { return key_iterator(&mAnchor); }
};
}
namespace eastl {
template<typename T> struct hash_s0056_34e0 {};
}
namespace eastl {
struct mod_range_hashing {};
}
namespace eastl {
struct default_ranged_hash {};
}
namespace eastl {
template<typename T> struct equal_to_s0056_34e0 { equal_to_s0056_34e0() {} };
}
namespace eastl {
template<typename P> struct use_first_s0056_34e0 {};
}
namespace eastl {
struct prime_rehash_policy_s0056_34e0 {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
};
}
namespace eastl {
template<typename V>
struct hash_node_s0056_34e0 {
    V mValue;
    hash_node_s0056_34e0* mpNext;
};
}
namespace eastl {
template<typename V>
struct hashtable_iterator_base_s0056_34e0 {
    hash_node_s0056_34e0<V>* mpNode;
    hash_node_s0056_34e0<V>** mpBucket;
    hashtable_iterator_base_s0056_34e0(hash_node_s0056_34e0<V>* pNode, hash_node_s0056_34e0<V>** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
    void increment_bucket();
};
}
namespace eastl {
template<typename V>
struct hashtable_iterator_s0056_34e0 : public hashtable_iterator_base_s0056_34e0<V> {
    typedef hashtable_iterator_base_s0056_34e0<V> base_type;
    hashtable_iterator_s0056_34e0(hash_node_s0056_34e0<V>** pBucket) : base_type(*pBucket, pBucket) {}
    hashtable_iterator_s0056_34e0(const hashtable_iterator_s0056_34e0& x) : base_type(x.mpNode, x.mpBucket) {}
    V* operator->() const { return &base_type::mpNode->mValue; }
    hashtable_iterator_s0056_34e0& operator++() {
        base_type::mpNode = base_type::mpNode->mpNext;
        while (!base_type::mpNode)
            base_type::mpNode = *++base_type::mpBucket;
        return *this;
    }
    bool operator!=(const hashtable_iterator_s0056_34e0& x) const { return base_type::mpNode != x.mpNode; }
};
}
namespace eastl {
template<typename K, typename V, typename A, typename ExtractKey, typename Equal, typename H1, typename H2, typename H>
class hashtable_s0056_34e0 {
public:
    typedef V value_type;
    typedef hashtable_iterator_s0056_34e0<V> iterator;
    typedef hash_node_s0056_34e0<V> node_type;
    typedef A allocator_type;

    uint32_t mFunctorPad;   // empty hash/compare functor bases
    node_type** mpBucketArray;
    size_t mnBucketCount;
    size_t mnElementCount;
    prime_rehash_policy_s0056_34e0 mRehashPolicy;
    A mAllocator;

    hashtable_s0056_34e0(size_t nBucketCount, const H1& h1, const H2& h2, const H& h, const Equal& eq, const ExtractKey& ek, const A& a);
    ~hashtable_s0056_34e0();
    iterator begin();
    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
    pair_s0056_34e0<iterator, bool> DoInsertValue(const value_type& value, true_type);
    pair_s0056_34e0<iterator, bool> insert(const value_type& value) { return DoInsertValue(value, true_type()); }
};
}
namespace eastl {
template<typename K, typename T>
class hash_map_s0056_34e0 : public hashtable_s0056_34e0<K, pair_s0056_34e0<const K, T>, allocator_s0056_34e0, use_first_s0056_34e0<pair_s0056_34e0<const K, T> >, equal_to_s0056_34e0<K>, hash_s0056_34e0<K>, mod_range_hashing, default_ranged_hash> {
public:
    typedef hashtable_s0056_34e0<K, pair_s0056_34e0<const K, T>, allocator_s0056_34e0, use_first_s0056_34e0<pair_s0056_34e0<const K, T> >, equal_to_s0056_34e0<K>, hash_s0056_34e0<K>, mod_range_hashing, default_ranged_hash> base_type;
    hash_map_s0056_34e0(const allocator_s0056_34e0& a = allocator_s0056_34e0());
};
}
namespace eastl {
template<typename K, typename T>
hash_map_s0056_34e0<K, T>::hash_map_s0056_34e0(const allocator_s0056_34e0& a)
    : base_type(0, hash_s0056_34e0<K>(), mod_range_hashing(), default_ranged_hash(), equal_to_s0056_34e0<K>(), use_first_s0056_34e0<pair_s0056_34e0<const K, T> >(), a) {
}
}
struct ResourceKey_s0056_34e0 {
    uint32_t mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
};
struct DatabasePackedFile_s0056_34e0 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual void Commit();
    virtual void v0a(); virtual void v0b(); virtual void v0c(); virtual void v0d();
    virtual void v0e(); virtual void v0f();
    virtual void DeleteRecord(const ResourceKey_s0056_34e0& key);  // 0x006bc5f0 (DatabasePackedFile::DeleteRecord)
};
struct IResourceFilter {
    IResourceFilter() {}
    virtual ~IResourceFilter() {}
    virtual bool IsValid(const ResourceKey_s0056_34e0& key);
};
namespace eastl {
 template<typename T> class basic_vector_s0056_34e0; template<typename T> class key_vector_s0056_34e0; 
}
struct IResourceManager_s0056_34e0 {
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual bool GetResource(const ResourceKey_s0056_34e0& key, SP::ResourceObject** ppResource, int a, int b, int c, int d);
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b(); virtual void v0c();
    // MSVC lays out overloaded virtuals in reverse declaration order.
    virtual int GetResourceKeyList(eastl::key_vector_s0056_34e0<ResourceKey_s0056_34e0>& keys, IResourceFilter& filter, eastl::basic_vector_s0056_34e0<DatabasePackedFile_s0056_34e0*>& dbs);
    virtual int GetResourceKeyList(eastl::key_vector_s0056_34e0<ResourceKey_s0056_34e0>& keys, IResourceFilter& filter);
};
namespace EA {
namespace ResourceMan {
 IResourceManager_s0056_34e0* GetManager_s0056_34e0(); 
}
}
template<typename T>
struct IntrusivePtr_s0056_34e0 {
    T* mpObject;
    IntrusivePtr_s0056_34e0() : mpObject(0) {}
    ~IntrusivePtr_s0056_34e0() { if (mpObject) mpObject->Release(); }
    T** operator&() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};
namespace EA {
namespace COM {
template<typename T, typename U> T* interface_cast(IntrusivePtr_s0056_34e0<U>& p);
}
}
namespace eastl {
template<typename T>
struct VectorBase_s0056_34e0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s0056_34e0 mAllocator;
    VectorBase_s0056_34e0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase_s0056_34e0();
};
}
namespace eastl {
template<typename T>
struct KeyVectorBase_s0056_34e0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s0056_34e0 mAllocator;
    KeyVectorBase_s0056_34e0(const allocator_s0056_34e0& a) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
    ~KeyVectorBase_s0056_34e0();
};
}
namespace eastl {
template<typename T>
class key_vector_s0056_34e0 : public KeyVectorBase_s0056_34e0<T> {
public:
    typedef KeyVectorBase_s0056_34e0<T> base_type;
    key_vector_s0056_34e0(const allocator_s0056_34e0& a = allocator_s0056_34e0()) : base_type(a) {}
    ~key_vector_s0056_34e0() { destruct(base_type::mpBegin, base_type::mpEnd); ScratchSlots<3>(); }
    size_t size() const { return base_type::mpEnd - base_type::mpBegin; }
    T& operator[](size_t n) { return base_type::mpBegin[n]; }
    T* begin() { return base_type::mpBegin; }
    T* end() { return base_type::mpEnd; }
    T* erase(T* first, T* last);
    void clear() { ScratchSlots<4>(); erase(base_type::mpBegin, base_type::mpEnd); }
};
}
namespace eastl {
template<typename T>
class basic_vector_s0056_34e0 : public VectorBase_s0056_34e0<T> {
public:
    T& operator[](size_t n) { return VectorBase_s0056_34e0<T>::mpBegin[n]; }
    basic_vector_s0056_34e0() {}
    ~basic_vector_s0056_34e0() { destruct(VectorBase_s0056_34e0<T>::mpBegin, VectorBase_s0056_34e0<T>::mpEnd); ScratchSlots<3>(); }
};
}
namespace SP {
 class cEditorResource_s0056_34e0; 
}
namespace SP {
namespace Traits {
class cFeatureVector_s0056_34e0 {
public:
    bool IsEmpty() const;
    cFeatureVector_s0056_34e0& operator=(const cFeatureVector_s0056_34e0& x);
    char pad[0x1c];
};
}
}
namespace SP {
namespace Traits {
void ApplyWeights(cFeatureVector_s0056_34e0& v, const eastl::vector_map_s0056_34e0<uint32_t, float>& weights);
}
}
namespace SP {
namespace Traits {
class cIClassifier_s0056_34e0 {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual uint32_t GetID();
    virtual uint32_t GetGroup();
    virtual void v06();
};
}
}
namespace SP {
namespace FunctionalMatch {
struct DeclareParam_s0056_34e0 {
    unsigned int mParameter;
    unsigned int mType;
    union { int mIntVal; float mFloatVal; };
    DeclareParam_s0056_34e0();
};
}
}
namespace SP {
namespace FunctionalMatch {
class cISummarizer_s0056_34e0 {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual uint32_t GetID();
    virtual uint32_t GetGroup();
    virtual void* GetSummary();
    virtual void v07();
    virtual bool Validate(cEditorResource_s0056_34e0* pResource, eastl::basic_vector_s0056_34e0<uint32_t>& blockIDs, int flags);
};
}
}
namespace SP {
class cISPObjectTemplateDB_s0056_34e0 {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c();
    virtual void OnAssetBanned(const ResourceKey_s0056_34e0& key, bool permanent);
};
}
namespace SP {
class cIMatchTuning_s0056_34e0 {
public:
    virtual void m00();
    virtual bool GetFeatureVector(uint32_t assetID, Traits::cFeatureVector_s0056_34e0& features);
    virtual void* FindSummaryByID(const uint32_t& id);
    virtual void* FindSummary(uint32_t id);
    virtual void SetClassifierWeights(const eastl::vector_map_s0056_34e0<uint32_t, float>& weights);
    virtual void GetDefaultClassifierWeights(eastl::vector_map_s0056_34e0<uint32_t, float>& weights);
    virtual bool ValidateResource(const ResourceKey_s0056_34e0& key, int flags);
};
}
namespace SP {
class cSPObjectTemplateDB_s0056_34e0 : public cISPObjectTemplateDB_s0056_34e0, public cIMatchTuning_s0056_34e0 {
public:
    struct AssetInfo {
        ResourceKey_s0056_34e0 mKey;
        uint32_t mnModelSubtype;
        Traits::cFeatureVector_s0056_34e0 mFeatureVector;
        eastl::vector_set_s0056_34e0<uint32_t> mGroupIDs;
        char pad44[0x50 - 0x44];
    };
    typedef eastl::vector_map_s0056_34e0<uint32_t, float> WeightMap;

    char pad08[0x14 - 0x08];
    eastl::vector_s0056_34e0<AssetInfo, eastl::sp_vector_allocator_s0056_34e0> mAssetList;    // +0x14
    char pad28[0x1ac - 0x28];
    WeightMap mClassifierWeights;                                        // +0x1ac
    bool mbUseClassifierWeights;                                         // +0x1c4
    char pad1c5[0x1ec - 0x1c5];
    eastl::map_s0056_34e0<uint32_t, AutoRefCount<Traits::cIClassifier_s0056_34e0> > mClassifierTable;            // +0x1ec
    eastl::map_s0056_34e0<uint32_t, AutoRefCount<FunctionalMatch::cISummarizer_s0056_34e0> > mSummarizerTable;   // +0x208
    char pad224[0x240 - 0x224];
    WeightMap mDefaultClassifierWeights;                                 // +0x240

    int FindAssetIndex(uint32_t assetID);
    virtual bool GetFeatureVector(uint32_t assetID, Traits::cFeatureVector_s0056_34e0& features);
    virtual void* FindSummaryByID(const uint32_t& id);
    virtual void* FindSummary(uint32_t id);
    virtual void SetClassifierWeights(const eastl::vector_map_s0056_34e0<uint32_t, float>& weights);
    virtual void GetDefaultClassifierWeights(eastl::vector_map_s0056_34e0<uint32_t, float>& weights);
    virtual bool ValidateResource(const ResourceKey_s0056_34e0& key, int flags);
    void SaveGroupRecords();
    uint32_t GetGroupForAssetGroup(uint32_t groupID);
    void BanAsset(const ResourceKey_s0056_34e0& key, bool permanent);

};
}
struct IDPair { uint32_t mID; uint32_t mIndex; };
struct WeightedID {
    IDPair mIDs;
    float mWeight;
    WeightedID() : mIDs(), mWeight() {}
};
namespace SP {
uint32_t ForwardedQuery(uint32_t a, uint32_t b);
}
namespace SP {
struct cQueryHost {
    uint32_t Query(uint32_t a, uint32_t b);
};
}
template class eastl::vector_s0056_34e0<SP::FunctionalMatch::DeclareParam_s0056_34e0, eastl::sp_vector_allocator_s0056_34e0>;
template class eastl::hash_map_s0056_34e0<uint32_t, uint32_t>;
template eastl::hash_map_s0056_34e0<uint32_t, uint32_t>::base_type::iterator eastl::hash_map_s0056_34e0<uint32_t, uint32_t>::base_type::begin();
template class eastl::vector_s0056_34e0<WeightedID, eastl::sp_vector_allocator_s0056_34e0>;
template class eastl::vector_s0056_34e0<eastl::pair_s0056_34e0<uint32_t, float>, eastl::sp_vector_allocator_s0056_34e0>;
namespace SP {
void GetBlockIDs(cEditorResource_s0056_34e0* pResource, eastl::basic_vector_s0056_34e0<uint32_t>& blockIDs);
}
// ---- items of slice s005634e0 end

// ---- items of slice s00569690 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int ptrdiff_t;
void* EASTL_Allocate(void* pAllocator, size_t n, size_t alignment, int flags); // 0x42dee0
namespace eastl {
  class allocator_s0056_9690 {
  public:
    const char* mpName;
    int         mFlags;
    void* allocate(size_t n, size_t alignment, size_t offset) { return EASTL_Allocate(this, n, alignment, offset); }
    void  deallocate(void* p, size_t) { delete[] (char*)p; }
  };
}
namespace eastl {
  struct false_type_s0056_9690 {};
}
namespace eastl {
  template<class T, class A = allocator_s0056_9690> class vector_s0056_9690 {
  public:
    typedef vector_s0056_9690<T, A> this_type; typedef T* pointer; typedef T* iterator; typedef T value_type;
    typedef unsigned size_type;
    T* mpBegin; T* mpEnd; T* mpCapacity; A mAllocator;

    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    size_type capacity() const { return (size_type)(mpCapacity - mpBegin); }
    this_type& operator=(const this_type& x);
    pointer DoRealloc(size_type n, const T* first, const T* last);      // 0x56a140
    void DoDestroyValues(pointer first, pointer last)
    {
        for(; first < last; ++first)
            first->~value_type();
    }
    void DoFree(pointer p, size_type n)
    {
        if(p)
            mAllocator.deallocate(p, n);
    }
  };
}
namespace eastl {
  template<class II, class OI> OI uninitialized_copy_ptr(II first, II last, OI result); // 0x50eb40
}
namespace eastl {
  struct copy_impl_generic {
    template<class II, class OI> static OI do_copy(II first, II last, OI result)
    {
        for(; first != last; ++result, ++first)
            *result = *first;
        return result;
    }
  };
}
namespace eastl {
  template<class II, class OI> inline OI copy_ptr(II first, II last, OI result)
  {
    const bool bOutputIsReverse = false;
    const bool bInputIsReverse = false;
    const bool bHasTrivialCopy = false;
    return copy_impl_generic::do_copy(first, last, result);
  }
}
namespace eastl {
  template<class T, class A>
  typename vector_s0056_9690<T,A>::this_type& vector_s0056_9690<T,A>::operator=(const this_type& x)
  {
    if(&x != this)
    {
        const size_type n = x.size();
        if(n > capacity())
        {
            pointer const pNewData = DoRealloc(n, x.mpBegin, x.mpEnd);
            ScratchSlots<9>();   // reserved frame of the declined inline DoRealloc
            DoDestroyValues(mpBegin, mpEnd);
            DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
            mpBegin    = pNewData;
            mpCapacity = mpBegin + n;
        }
        else if(n > size())
        {
            eastl::copy_ptr(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            eastl::uninitialized_copy_ptr(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
            ScratchSlots<11>();  // reserved frame of the declined inline uninitialized_copy_ptr
        }
        else
        {
            iterator const position = eastl::copy_ptr(x.mpBegin, x.mpEnd, mpBegin);
            DoDestroyValues(position, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
  }
}
namespace eastl {
  template<class T> struct DequeIterator_s0056_9690 {
    enum { kDequeSubarraySize = 32 };
    typedef DequeIterator_s0056_9690<T> this_type; typedef ptrdiff_t difference_type;
    T* mpCurrent; T* mpBegin; T* mpEnd; T** mpCurrentArrayPtr;
    DequeIterator_s0056_9690(const DequeIterator_s0056_9690& x);                                 // 0x420050
    T& operator*() const;                                                  // 0x5658b0
    DequeIterator_s0056_9690& operator++();                                           // 0x5677f0
    DequeIterator_s0056_9690& operator--();                                           // 0x5692d0
    DequeIterator_s0056_9690& operator+=(difference_type n);
    void SetSubarray(T** pCurrentArrayPtr);                                // 0x569340
    this_type copy_s0056_9690(const this_type& first, const this_type& last, false_type_s0056_9690);
    void copy_backward(const this_type& first, const this_type& last, false_type_s0056_9690);
  };
}
namespace eastl {
  template<class T> inline bool operator!=(const DequeIterator_s0056_9690<T>& a, const DequeIterator_s0056_9690<T>& b) { return a.mpCurrent != b.mpCurrent; }
}
namespace eastl {
  template<class T> inline ptrdiff_t operator-(const DequeIterator_s0056_9690<T>& a, const DequeIterator_s0056_9690<T>& b)
  {
    return ((ptrdiff_t)DequeIterator_s0056_9690<T>::kDequeSubarraySize * ((a.mpCurrentArrayPtr - b.mpCurrentArrayPtr) - 1)) +
           (a.mpCurrent - a.mpBegin) + (b.mpEnd - b.mpCurrent);
  }
}
namespace eastl {
  template<class T> DequeIterator_s0056_9690<T>& DequeIterator_s0056_9690<T>::operator+=(difference_type n)
  {
    const difference_type subarrayPosition = (mpCurrent - mpBegin) + n;

    if((size_t)subarrayPosition < (size_t)kDequeSubarraySize)
        mpCurrent += n;
    else
    {
        const difference_type subarrayIndex = (((16777216 + subarrayPosition) / (difference_type)kDequeSubarraySize)) - (16777216 / (difference_type)kDequeSubarraySize);
        SetSubarray(mpCurrentArrayPtr + subarrayIndex);
        mpCurrent = mpBegin + (subarrayPosition - (subarrayIndex * (difference_type)kDequeSubarraySize));
    }
    return *this;
  }
}
namespace eastl {
  template<class II, class OI> inline OI copy_chooser(II first, II last, OI result);
}
namespace eastl {
  template<bool bInputIsReverseIterator, bool bOutputIsReverseIterator> struct copy_impl {
    template<class II, class OI> static OI do_copy(II first, II last, OI result)
    {
        return eastl::copy_chooser(first, last, result);
    }
  };
}
namespace eastl {
  template<class II, class OI> inline OI copy_s0056_9690(II first, II last, OI result)
  {
    const bool bOutputIsReverseIterator = false;
    const bool bInputIsReverseIterator  = false;
    return eastl::copy_impl<false, false>::do_copy(first, last, result);
  }
}
namespace eastl {
  struct copy_loop {
    template<class II, class OI> static OI do_copy(II first, II last, OI result)
    {
        for(; first != last; ++result, ++first)
            *result = *first;
        return result;
    }
  };
}
namespace eastl {
  template<class II, class OI> inline OI copy_chooser(II first, II last, OI result)
  {
    const bool bHasTrivialCopy = false;
    return copy_loop::do_copy(first, last, result);
  }
}
namespace eastl {
  template<class BI1, class BI2> inline BI2 copy_backward_chooser(BI1 first, BI1 last, BI2 resultEnd);
}
namespace eastl {
  template<bool bInputIsReverseIterator, bool bOutputIsReverseIterator> struct copy_backward_impl {
    template<class BI1, class BI2> static BI2 do_copy(BI1 first, BI1 last, BI2 resultEnd)
    {
        return eastl::copy_backward_chooser(first, last, resultEnd);
    }
  };
}
namespace eastl {
  template<class BI1, class BI2> inline BI2 copy_backward(BI1 first, BI1 last, BI2 resultEnd)
  {
    const bool bOutputIsReverseIterator = false;
    const bool bInputIsReverseIterator  = false;
    return eastl::copy_backward_impl<false, false>::do_copy(first, last, resultEnd);
  }
}
namespace eastl {
  struct copy_backward_loop {
    template<class BI1, class BI2> static BI2 do_copy(BI1 first, BI1 last, BI2 resultEnd)
    {
        while(last != first)
            *--resultEnd = *--last;
        return resultEnd;
    }
  };
}
namespace eastl {
  template<class BI1, class BI2> inline BI2 copy_backward_chooser(BI1 first, BI1 last, BI2 resultEnd)
  {
    const bool bHasTrivialCopy = false;
    return copy_backward_loop::do_copy(first, last, resultEnd);
  }
}
struct Pod8 { uint32_t a, b; };
typedef eastl::DequeIterator_s0056_9690<Pod8> Pod8Iter;
template void Pod8Iter::copy_backward(const Pod8Iter&, const Pod8Iter&, eastl::false_type_s0056_9690);
struct Part {                             // 0x1d8 bytes
    uint32_t mGroup;                      // +0x0
    uint32_t mInstance;                   // +0x4
    uint32_t pad08[2];
    float    mScale;                      // +0x10
    uint32_t pad14[31];
    uint32_t mFlags;                      // +0x90
    uint32_t mTransform[81];              // +0x94
};
struct FloatVector {
    float* mpBegin; float* mpEnd; float* mpCapacity; uint32_t mAllocator[2];
    void resize(unsigned n);              // 0x4afc80
};
struct Parts { Part* mpBegin; Part* mpEnd; unsigned size() const { return (unsigned)(mpEnd - mpBegin); } };
struct Creature { uint32_t pad[38]; Parts mParts; };   // mParts at +0x98
// ---- items of slice s00569690 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
bool GetPartVolume(const Part* pPart, float* pVolume);  // 0x0056a710 (stays in the slice: not this object's)

// @ 0x005588f0
namespace SP { namespace FunctionalMatch {
Constraint_s0055_80e0::Constraint_s0055_80e0(unsigned int param, RangeConstraint_s0055_80e0, float minVal, float maxVal)
: mParameter(param), mType(kFloat_s0055_80e0) {
    mFloatVal.mMin = minVal;
    mFloatVal.mMax = maxVal;
}
}}  // namespace SP::FunctionalMatch












// @ 0x00558960
namespace SP { namespace FunctionalMatch {
Constraint_s0055_80e0::Constraint_s0055_80e0(unsigned int param, EqualConstraint_s0055_80e0, int value)
: mParameter(param), mType(kInteger_s0055_80e0) {
    mIntVal.mMin = value;
    mIntVal.mMax = value + 1;
}
}}  // namespace SP::FunctionalMatch












// @ 0x005589c0
namespace SP { namespace FunctionalMatch {
Constraint_s0055_80e0::Constraint_s0055_80e0(unsigned int param, RangeConstraint_s0055_80e0, int minVal, int maxVal)
: mParameter(param), mType(kInteger_s0055_80e0) {
    mIntVal.mMin = minVal;
    mIntVal.mMax = maxVal;
}
}}  // namespace SP::FunctionalMatch












// @ 0x00558a20
namespace SP { namespace FunctionalMatch {
Constraint_s0055_80e0::Constraint_s0055_80e0(unsigned int param, NotEqualConstraint, int value)
: mType(kNotEqual_s0055_80e0) {
    Constraint_s0055_80e0 lowRange(param, kBetween_s0055_80e0, (int)0x80000000, value);
    Constraint_s0055_80e0 highRange(param, kBetween_s0055_80e0, value + 1, 0x7fffffff);
    mConstraints.push_back(lowRange);
    mConstraints.push_back(highRange);
    ScratchSlots<14>();
}
}}  // namespace SP::FunctionalMatch












// @ 0x00558ae0
namespace SP { namespace FunctionalMatch {
Constraint_s0055_80e0::Constraint_s0055_80e0(AnyConstraint, eastl::vector_s0055_80e0<Constraint_s0055_80e0, eastl::sp_vector_allocator_s0055_80e0> constraints)
: mType(kNotEqual_s0055_80e0), mConstraints(constraints) {
    ScratchSlots<18>();
}
}}  // namespace SP::FunctionalMatch












// @ 0x00558b20
namespace SP { namespace FunctionalMatch {
bool Constraint_s0055_80e0::IsCompound() const
{
    return mType != kInteger_s0055_80e0 && mType != kFloat_s0055_80e0 && mType != kNotEqual_s0055_80e0;
}
}}  // namespace SP::FunctionalMatch












// @ 0x00558b70
SP::FunctionalMatch::DeclareParam::DeclareParam()
{
    mType = kTerminal;
}












// @ 0x00558b90
SP::FunctionalMatch::DeclareParam::DeclareParam(unsigned int param, float value)
{
    mParameter = param;
    mType = kFloat;
    mFloatVal = value;
}












// @ 0x00558bc0
SP::FunctionalMatch::DeclareParam::DeclareParam(unsigned int param, int value)
{
    mParameter = param;
    mType = kInteger;
    mIntVal = value;
}












// @ 0x00558bf0
namespace SP {
bool IsPillRecordStale(uint32_t instanceID, int expectedValue)
{
    bool valid = false;
    ResourceKey key(instanceID, 0x2d5c9b0, 0x11ac19c);
    DatabasePackedFile_s0055_80e0* pDBPF = EA::ResourceMan::GetManager()->FindDatabase(key);
    if (pDBPF) {
        IntrusivePtr<IPFRecord> pRecord;
        if (pDBPF->OpenRecord(key, &pRecord, 1, 3, 1, 0)) {
            EA::IO::IStream_s0055_80e0* pStream = pRecord->GetStream();
            int32_t nValue;
            valid = EA::IO::ReadInt32(pStream, &nValue, 1, 0) && nValue == expectedValue;
            valid = valid && EA::IO::ReadInt32(pStream, &nValue, 1, 0) && nValue == 4;
            pDBPF->CloseRecord(pRecord);
        }
    }
    return !valid;
}
}  // namespace SP












// @ 0x00558d50
namespace SP {
void WritePillRecord(uint32_t instanceID, uint32_t value)
{
    DatabasePackedFile_s0055_80e0* saveArea = GetSaveArea(0x11ac19c);
    ResourceKey key(instanceID, 0x2d5c9b0, 0x11ac19c);
    IntrusivePtr<IPFRecord> record;
    if (saveArea->OpenRecord(key, &record, 2, 2, 1, 0)) {
        EA::IO::IStream_s0055_80e0* pStream = record->GetStream();
        EA::IO::WriteUint32(pStream, value, 0);
        EA::IO::WriteUint32(pStream, 4, 0);
        saveArea->CloseRecord(record);
    }
}
}  // namespace SP












// @ 0x00558e40
namespace SP {
void* cParameterResource::AsInterface(uint32_t iid)
{
    if (iid == 0x670da17)
        return this;
    return cResourceBase_s0055_80e0::AsInterface(iid);
}
}  // namespace SP












// @ 0x00558e70
namespace SP {
size_t cParameterResourceFactory::GetSupportedTypes(uint32_t* types, size_t count)
{
    const size_t kCount = 1;
    if (types) {
        if (count < kCount)
            return 0;
        types[0] = 0x2d5c9af;
    }
    return kCount;
}
}  // namespace SP












// @ 0x00558eb0
namespace SP {
bool cParameterResourceFactory::IsValid(uint32_t typeID, uint32_t subtypeID)
{
    return typeID == 0x2d5c9af && subtypeID == 0x2d5c9af;
}
}  // namespace SP












// @ 0x00558ef0
namespace SP {
bool cParameterResourceFactory::CreateResource(IPFRecord* pRecord, ResourceObject*& pDst, int flags, uint32_t typeID)
{
    if (typeID == 0x2d5c9af) {
        IntrusivePtr<cParameterResource> pResource;
        pResource = new("OTDB/ParameterResource") cParameterResource();
        if (Read(pRecord, pResource, flags, typeID)) {
            pResource->SetResourceKey(pRecord->GetKey());
            pDst = pResource.detach();
            return true;
        }
    }
    return false;
}
}  // namespace SP











// @ 0x00559500
int SP::cSPObjectTemplateDB::AddRef()
{
    uint32_t* v33 = (uint32_t*)((char*)this + 0xc);
    int len = (int)v33[1] + 1;
    v33[1] = v33[1] + 1;
    return len;
}










// @ 0x005598b0
namespace SP {
bool cSPObjectTemplateDB_s0055_98b0::Init()
{
    g_pOTDBService = GetOTDBService();
    ICheatManager* pCheatManager = CheatManager();
    if (pCheatManager)
        new ("Editor/OTDB", 0, 0, 0, 0) cOTDBCheat();

    IMessageServer* pMessageServer = EA::Messaging::GetServer();
    if (g_pOTDBService && pMessageServer) {
        pMessageServer->AddHandler(static_cast<IHandlerRC_s0055_98b0*>(this), 0xca665fa7);
        pMessageServer->AddHandler(static_cast<IHandlerRC_s0055_98b0*>(this), 0x165e841);
        pMessageServer->AddHandler(static_cast<IHandlerRC_s0055_98b0*>(this), 0x1a7f758);
        pMessageServer->AddHandler(static_cast<IHandlerRC_s0055_98b0*>(this), 0x5132ed1);
        pMessageServer->AddHandler(static_cast<IHandlerRC_s0055_98b0*>(this), 0x5132eec);
        pMessageServer->AddHandler(static_cast<IHandlerRC_s0055_98b0*>(this), 0x3743e04);
        pMessageServer->AddHandler(static_cast<IHandlerRC_s0055_98b0*>(this), 0x212d3e7);
        pMessageServer->AddHandler(static_cast<IHandlerRC_s0055_98b0*>(this), 0x680c633);
        pMessageServer->AddHandler(static_cast<IHandlerRC_s0055_98b0*>(this), 0x4c6f86a);
        pMessageServer->AddHandler(static_cast<IHandlerRC_s0055_98b0*>(this), 0x64e331c);

        int nCount = 1;
        GetCommandServer()->AddCommands(sCommandInfos, nCount);
        for (int i = 0; i < nCount; ++i)
            pMessageServer->AddHandler(static_cast<IHandlerRC_s0055_98b0*>(this), sCommandInfos[i].id);

        mpFactory = new ("OTDB", 0, 0, 0, 0) cOTDBResourceFactory();
        EA::ResourceMan::GetManager_s0055_98b0()->RegisterFactory(true, mpFactory.get(), 0);
        ScratchSlots_s0055_98b0<12>();

        mResourceTypesToReindex.insert(kOTDBTypeA);
        mResourceTypesToReindex.insert(0x52def3f);
        mResourceTypesToReindex.insert(kOTDBTypeB);

        AddSummarizer(new cSummarizerA());
        AddSummarizer(new cSummarizerB());

        EA::AutoRefCount_s0055_98b0<PropertyList> ok(0);
        PropertyManager()->GetPropertyList(0x21d4b8c, 0x21403e6, ok.AsPP());
        Property* w;
        if (ok.mpObject && ok->GetProperty(0x4598a6f, w)) {
            uint32_t* k = (uint32_t*)w->GetValue();
            uint32_t s = w->GetItemCount();
            s &= ~1;
            uint32_t* q = k + s;
            while (k != q) {
                uint32_t type = *k++;
                uint32_t count = *k++;
                mPopulationCount.insert(eastl::make_pair(type, count));
                ScratchSlots_s0055_98b0<4>();
            }
        }

        mAssets.Rebuild();
        PropertyManager()->GetPropertyList(0x52f1b79, 0x21403e6, ok.AsPP());
        Property* u;
        if (ok.mpObject && ok->GetProperty(0x52f1c91, u)) {
            bool a = false;
            uint32_t g = 0;
            if (GetPropertyAsUint32(ok, 0x534676f, &g))
                a = IsPillRecordStale(0x534676f, g);
            ScratchSlots_s0055_98b0<3>();

            uint32_t* f = (uint32_t*)u->GetValue();
            uint32_t* h = f + u->GetItemCount();
            for (; f != h; ++f) {
                uint32_t assetID = *f;
                RefPtr<IRefObj> pAsset;
                if (mAssets.Find(assetID, pAsset.AsPP())) {
                    RefPtr<PropertyList> pAssetProps;
                    PropertyManager()->GetPropertyList(assetID, 0x21403e6, pAssetProps.AsPP());
                    Property* pParams;
                    if (pAssetProps.mpObject && pAssetProps->GetProperty(0x52f2304, pParams)) {
                        LoadAssetParameters(pAsset.mpObject, pParams->GetItemCount(), pParams->GetValue(), a);
                        TouchAsset(assetID, 1);
                    }
                }
            }

            Property* p;
            if (ok->GetProperty(0x52f2455, p)) {
                f = (uint32_t*)u->GetValue();
                float* t = (float*)p->GetValue();
                float* r = t + p->GetItemCount();
                for (; t != r && f != h; ++f, ++t) {
                    mClassifierWeights.insert(eastl::make_pair(*f, *t));
                }
            }
            WritePillRecord(0x534676f, g);
            ScratchSlots_s0055_98b0<12>();
        }

        AddPriorityConstraint(FunctionalMatch::Constraint_s0055_98b0(0x5dc0b88, FunctionalMatch::kEquals_s0055_98b0, 0), 0);
        AddPriorityConstraint(FunctionalMatch::Constraint_s0055_98b0(0x5dc0b88, FunctionalMatch::kEquals_s0055_98b0, 1), 0);
        AddPriorityConstraint(FunctionalMatch::Constraint_s0055_98b0(0x5dc0b88, FunctionalMatch::kEquals_s0055_98b0, 2), 0);

        if (LoadDatabase())
            return true;
    }
    return false;
}
}  // namespace SP









// @ 0x0055a550
namespace SP { namespace Audio {
uint32_t cCityMusicSummarizer::GetParamId(uint32_t index)
{
    static const uint32_t s_table[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    if (index < 8)
        return s_table[index];
    return 0xffffffff;
}
}}  // namespace SP::Audio









// @ 0x0055a9d0
namespace SP { namespace Audio {
uint32_t cCityMusicSummarizer::GetParamType(uint32_t index)
{
    static const uint32_t s_table[6] = { 0, 0, 0, 0, 0, 0 };
    if (index < 6)
        return s_table[index];
    return 0xffffffff;
}
}}  // namespace SP::Audio








// @ 0x0055beb0
char const * SP::cFunctionalTestCheat::Description(EA::ArgScript::tHelpType index) const
{
    if (index == 0)
        return "Used to debug OTDB parameters";
    else
        return "\n-get_key_params <SPID key name>\n   dump otdb parameters associated with the given file/key\n"
               "-get_id_params <SPID key name>\n   dump otdb parameters associated with the given server id.\n";
}








// @ 0x0055bee0
namespace SP {
bool cFunctionalTestCheat_s0055_beb0::IsEnabled()
{
    return true;
}
}  // namespace SP








// @ 0x0055bf10
cResFinal_s0055_beb0::cResFinal_s0055_beb0()
{}








// @ 0x0055bf50
cSummarizerFinal_s0055_beb0::cSummarizerFinal_s0055_beb0()
{}








// @ 0x0055bfb0
bool SP::cSPObjectTemplateDB_s0055_beb0::Shutdown()
{
    ICheatManager_s0055_beb0* manager = SP::CheatManager_s0055_beb0();
    if (manager)
        manager->Remove("otdb_test");
    IMessageServer_s0055_beb0* pMessageServer = EA::Messaging::GetServer_s0055_beb0();
    if (pMessageServer) {
        pMessageServer->RemoveHandler(static_cast<IHandlerRC_s0055_beb0*>(this), 0xca665fa7, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC_s0055_beb0*>(this), 0x1a7f758, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC_s0055_beb0*>(this), 0x165e841, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC_s0055_beb0*>(this), 0x5132ed1, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC_s0055_beb0*>(this), 0x5132eec, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC_s0055_beb0*>(this), 0x3743e04, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC_s0055_beb0*>(this), 0x212d3e7, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC_s0055_beb0*>(this), 0x680c633, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC_s0055_beb0*>(this), 0x4c6f86a, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC_s0055_beb0*>(this), 0x64e331c, 0xffffd8f1);
    }
    int nCmds = 1;
    GetCommandServer_s0055_beb0()->RegisterCommands(sCommandInfos_s0055_beb0, nCmds);
    for (int i = 0; i < nCmds; ++i)
        pMessageServer->RemoveHandler(static_cast<IHandlerRC_s0055_beb0*>(this), *(uint32_t*)(sCommandInfos_s0055_beb0 + i * 12), 0xffffd8f1);
    mpAuto = 0;
    mTable.Clear();
    mFlag40 = 0;
    SetMode("Production");
    return true;
}








// @ 0x0055c2e0
bool SP::cSPObjectTemplateDB_s0055_beb0::RandomizeFirstN(ParamVec<Key3>* v, int n)
{
    Key3* i = v->mpBegin;
    Key3* pos = v->mpEnd;
    int count = 0;
    for (; count != n && i != pos; ++i, ++count) {
        Key3* swap = i + mRandom.RandomUint32Uniform((uint32_t)(pos - i));
        Key3 pEnd = *i;
        *i = *swap;
        *swap = pEnd;
    }
    if (i != pos)
        v->truncate(n);
    ScratchSlots_s0055_beb0<11>();
    return !v->empty();
}








// @ 0x0055c640
namespace SP {
Editor::ObjectTemplateDB* CreateObjectTemplateDB()
{
    return new ("Editor/ObjectTemplateDB", 0, 0, 0, 0) Editor::ObjectTemplateDB();
}
}  // namespace SP








// @ 0x0055c690
void* SP::cSPObjectTemplateDB_s0055_beb0::AsInterface(uint32_t type)
{
    switch (type) {
    case 0x4ed03fd:
        return this;
    case 0x4ed5013:
        return static_cast<cIMatchTuning_s0055_beb0*>(this);
    case 0xee3f516e:
        return this;
    }
    return 0;
}







// @ 0x0055d9e0
namespace SP {
char cSPObjectTemplateDB_s0055_ce80::FUN_0055d9e0(void* pObj, int count, void* pItems, char flag)
{
    char result = 0;
    if (pObj == 0)
        return 0;
    bool add = true;
    if (!flag) {
        int a = ((IRefObj_s0055_ce80*)pObj)->GetB();
        int b = ((IRefObj_s0055_ce80*)pObj)->GetA();
        add = FUN_00558bf0(b, a);
    }
    for (int i = 0; i < count; ++i) {
        uint32_t item = ((uint32_t*)pItems)[i];
        void* tmp;
        ((DBSub*)((char*)this + 0x208))->AddKey0(&tmp, &item, 0);
        if (add) {
            ((DBSub*)((char*)this + 0x228))->AddKey1(&tmp, &item);
        }
        result = 1;
    }
    return result;
}
}  // namespace SP







// @ 0x0055db30
namespace SP {
char cSPObjectTemplateDB_s0055_ce80::FUN_0055db30(void* pObj)
{
    bool result = false;
    if (pObj == 0)
        return 0;
    if (((IRefObj_s0055_ce80*)pObj)->GetA() == 0x55a63a0) {
        IRefObj_s0055_ce80** slot = (IRefObj_s0055_ce80**)((char*)this + 0x224);
        if (pObj != (void*)*slot) {
            IRefObj_s0055_ce80* old = *slot;
            ((IRefObj_s0055_ce80*)pObj)->AddRef();
            *slot = (IRefObj_s0055_ce80*)pObj;
            if (old)
                old->Release();
        }
    }
    int a = ((IRefObj_s0055_ce80*)pObj)->GetB();
    int b = ((IRefObj_s0055_ce80*)pObj)->GetA();
    char add = FUN_00558bf0(b, a);
    int n = ((IRefObj_s0055_ce80*)pObj)->GetCount();
    result = (n != 0);
    for (int i = 0; i < n; ++i) {
        uint32_t item = ((IRefObj_s0055_ce80*)pObj)->GetItem(i);
        void* tmp;
        ((DBSub*)((char*)this + 0x1ec))->AddKey0(&tmp, &item, 0);
        if (add) {
            ((DBSub*)((char*)this + 0x228))->AddKey1(&tmp, &item);
        }
    }
    return (char)result;
}
}  // namespace SP






// @ 0x0055eae0
void* PaintStub::FUN_0055eae0(int* first, int count)
{
    void* this_ = this;
    *(void**)this_ = (void*)0x13eb394;
    *(void**)this_ = (void*)0x13f4af0;
    ((int*)this_)[1] = 0;
    ((int*)this_)[2] = 0;
    ((int*)this_)[3] = 0;
    uint32_t flag;
    FUN_00568740((int*)this_ + 1, first, first + count, flag);
    FUN_0050f0d0((void*)((int*)this_)[1], (void*)((int*)this_)[2]);
    return this_;
}





// @ 0x0055f9e0
namespace SP {
void EcxStub70::FUN_0055f9e0()
{
    void* this_ = this;
    if (*(char*)((char*)this_ + 0x40) == 0) {
        void* obj = *(void**)((char*)this_ + 0x44);
        if (obj != 0)
            FUN_006926b0(obj);
    }
}
}  // namespace SP





// @ 0x0055fa20
namespace SP {
unsigned char EcxStub70::FUN_0055fa20(void* key, char flag)
{
    void* this_ = this;
    int index = 0;
    FUN_005631e0(this_, &index);
    ((int*)this_)[0] = 0;   // placeholder to keep `index` live
    if (index == -1)
        return 0;
    if (flag != 0) {
        char tmp[8];
        void* p = FUN_00554020(tmp, &index);
        if (*(char*)((char*)p + 4) != 0) {
            FUN_00561970(index);
            *(unsigned char*)((char*)this_ + 0x1d0) = 1;
        }
        unsigned a = DateTime_Set(1);
        (void)a;
        int base = index * 0x50 + *(int*)((char*)this_ + 0x14);
        (void)base;
    } else {
        void* itpair[2];
        FUN_00555980(itpair, &index);
        void* it = (itpair[0] != itpair[1]) ? itpair[0] : *(void**)((char*)this_ + 0x68);
        if (it != *(void**)((char*)this_ + 0x68)) {
            FUN_0048c720(it);
            FUN_00561850(index);
        }
    }
    return 1;
}
}  // namespace SP





// @ 0x0055fb30
bool SP::cSPObjectTemplateDB::GetAssetType(EA::ResourceMan::Key const & key, unsigned int & a2)
{
    void* this_ = this;
    int index = 0;
    FUN_005631e0(this_, &index);
    if (index != -1) {
        void* itpair[2];
        FUN_00555980(itpair, &index);
        void* it = (itpair[0] != itpair[1]) ? itpair[0] : *(void**)((char*)this_ + 0x68);
        if (it != *(void**)((char*)this_ + 0x68))
            return 1;
    }
    return 0;
}





// @ 0x0055fbb0
namespace SP {
unsigned char EcxStub70::FUN_0055fbb0(void* key)
{
    void* this_ = this;
    int index = 0;
    FUN_005631e0(this_, &index);
    if (index == -1)
        return 0;
    unsigned a = DateTime_Set(1);
    (void)a;
    int base = index * 0x50 + *(int*)((char*)this_ + 0x14);
    (void)base;
    return 1;
}
}  // namespace SP




// @ 0x00561bd0
namespace SP {
void cSPObjectTemplateDB_s0056_1970::CheckForMinPopulations()
{
    if (ConfigManager()->GetInt(0x5de7b4a) == 0) {
        for (CountMap::iterator iter = mPopulationCount.begin(), last = mPopulationCount.end(); iter != last; ++iter) {
            eastl::pair_s0056_1970<uint32_t, uint32_t>& entry = *iter;
            CountMap::iterator itRefill = mRefillCount.find(entry.first);
            if (itRefill != mRefillCount.end() && entry.second <= itRefill->second)
                MessageManager()->MessageSend(0x45883b0, &entry);
        }
    }
}
}  // namespace SP




// @ 0x00561d80
namespace SP {
bool cSPObjectTemplateDB_s0056_1970::GetFloatParameterValues(uint32_t paramID, eastl::vector_s0056_1970<float>& values)
{
    eastl::map_s0056_1970<uint32_t, FloatValueMap>::iterator it = mFloatParameters.find(paramID);
    if (it != mFloatParameters.end()) {
        FloatValueMap& valueMap = (*it).second;
        values.clear();
        eastl::copy(valueMap.begin(), valueMap.end(), eastl::key_inserter(values, values.end()), eastl::input_iterator_tag());
        return true;
    } else {
        return false;
    }
}
}  // namespace SP




// @ 0x00561ea0
namespace SP {
bool cSPObjectTemplateDB_s0056_1970::GetIntParameterValues(uint32_t paramID, eastl::vector_s0056_1970<int>& values)
{
    eastl::map_s0056_1970<uint32_t, IntValueMap>::iterator it = mIntParameters.find(paramID);
    if (it != mIntParameters.end()) {
        IntValueMap& valueMap = (*it).second;
        values.clear();
        eastl::copy(valueMap.begin(), valueMap.end(), eastl::key_inserter(values, values.end()), eastl::input_iterator_tag());
        return true;
    } else {
        return false;
    }
}
}  // namespace SP




// @ 0x00561fc0
namespace SP {
bool cSPObjectTemplateDB_s0056_1970::GetFloatParameterTable(uint32_t paramID, eastl::vector_s0056_1970<float>& values, eastl::vector_s0056_1970<ResourceKey_s0056_1970>& keys)
{
    eastl::map_s0056_1970<uint32_t, FloatValueMap>::iterator it = mFloatParameters.find(paramID);
    if (it != mFloatParameters.end()) {
        FloatValueMap& vm = (*it).second;
        values.clear_noframe();
        keys.clear_noframe();
        values.reserve(vm.size());
        keys.reserve(vm.size());
        FloatValueMap::iterator vit = vm.begin();
        FloatValueMap::iterator vend = vm.end();
        for (; vit != vend; ++vit) {
            float paramValue = (*vit).first;
            eastl::vector_set_s0056_1970<uint32_t>& owners = (*vit).second;
            uint32_t* iter2 = owners.begin();
            uint32_t* iEnd = owners.end();
            for (; iter2 != iEnd; ++iter2) {
                keys.push_back(mAssetList[*iter2].mKey);
                values.push_back(paramValue);
            }
        }
        ScratchSlots<4>();
        return true;
    } else {
        return false;
    }
}
}  // namespace SP




// @ 0x00562120
namespace SP {
bool cSPObjectTemplateDB_s0056_1970::GetIntParameterTable(uint32_t paramID, eastl::vector_s0056_1970<int>& values, eastl::vector_s0056_1970<ResourceKey_s0056_1970>& keys)
{
    eastl::map_s0056_1970<uint32_t, IntValueMap>::iterator it = mIntParameters.find(paramID);
    if (it != mIntParameters.end()) {
        IntValueMap& vm = (*it).second;
        values.clear_noframe();
        keys.clear_noframe();
        values.reserve(vm.size());
        keys.reserve(vm.size());
        IntValueMap::iterator vit = vm.begin();
        IntValueMap::iterator vend = vm.end();
        for (; vit != vend; ++vit) {
            int paramValue = (*vit).first;
            eastl::vector_set_s0056_1970<uint32_t>& owners = (*vit).second;
            uint32_t* iter2 = owners.begin();
            uint32_t* iEnd = owners.end();
            for (; iter2 != iEnd; ++iter2) {
                keys.push_back(mAssetList[*iter2].mKey);
                values.push_back(paramValue);
            }
        }
        ScratchSlots<4>();
        return true;
    } else {
        return false;
    }
}
}  // namespace SP




// @ 0x00562280
namespace SP {
void cSPObjectTemplateDB_s0056_1970::FindMatching(eastl::vector_set_s0056_1970<uint32_t>* pResults, const Constraint_s0056_1970& c)
{
    switch (c.mType) {
    case kInteger_s0056_1970: {
        eastl::map_s0056_1970<uint32_t, IntValueMap>::iterator it = mIntParameters.find(c.mParameter);
        if (it != mIntParameters.end()) {
            IntValueMap& values = (*it).second;
            AddIntMatches(pResults, c.mIntVal.mMin, c.mIntVal.mMax, values);
        }
        break;
    }
    case kFloat_s0056_1970: {
        eastl::map_s0056_1970<uint32_t, FloatValueMap>::iterator it = mFloatParameters.find(c.mParameter);
        if (it != mFloatParameters.end()) {
            FloatValueMap& values = (*it).second;
            AddFloatMatches(pResults, c.mFloatVal.mMin, c.mFloatVal.mMax, values);
        }
        // falls through (a float constraint has no sub-constraints)
    }
    case kNotEqual_s0056_1970:
        for (uint32_t i = 0; i < c.mConstraints.size(); i++)
            FindMatching(pResults, c.mConstraints[i]);
        break;
    }
}
}  // namespace SP




// @ 0x00562680
namespace SP {
void cSPObjectTemplateDB_s0056_1970::AddPriorityConstraint(const Constraint_s0056_1970& c, uint32_t tag)
{
    PriorityConstraint pc(tag, c);
    mPriorityConstraints.push_back(pc);
    ScratchSlots<9>();
}
}  // namespace SP




// @ 0x00562710
namespace SP {
void cSPObjectTemplateDB_s0056_1970::RemovePriorityConstraint(uint32_t tag)
{
    PriorityConstraint* it = eastl::find(mPriorityConstraints.begin(), mPriorityConstraints.end(), tag);
    if (it != mPriorityConstraints.end())
        mPriorityConstraints.erase(it);
    ScratchSlots<12>();
}
}  // namespace SP




// @ 0x00562790
namespace SP {
void cSPObjectTemplateDB_s0056_1970::SetExcludedParameter(int value)
{
    RemovePriorityConstraint(0x5dd2a5b);
    Constraint_s0056_1970 c(0x3cc89b1, kEquals_s0056_1970, value);
    AddPriorityConstraint(c, 0x5dd2a5b);
    mMatchResults.clear();
    FindMatching(&mMatchResults, c);
    eastl::set_difference(mCandidates.begin(), mCandidates.end(), mMatchResults.begin(), mMatchResults.end(),
                          eastl::inserter(mResultSet, mResultSet.begin()));
    mCandidates.assign(mResultSet.begin(), mResultSet.end());
    ScratchSlots<5>();
}
}  // namespace SP




// @ 0x005628b0
namespace SP {
void cSPObjectTemplateDB_s0056_1970::ClearExcludedParameter()
{
    RemovePriorityConstraint(0x5dd2a5b);
}
}  // namespace SP



// @ 0x00562b80
namespace SP {
void CandidateDBStub::AssignCandidates(void* out, void* pRange)
{
    void* this_ = this;
    FUN_004769b0(*(void**)((char*)this_ + 0x12c), *(void**)((char*)this_ + 0x130));
    int* r = (int*)pRange;
    FUN_00565500((char*)this_ + 0x12c, (void*)*r, (r[1] - *r) / 0x24);
    FUN_00562510((char*)this_ + 0x12c, out);
}
}  // namespace SP



// @ 0x00562ca0
namespace SP {
bool CandidateDBStub::TryFilterCandidates(void* a, void* b, void* pRange)
{
    void* this_ = this;
    FUN_004769b0(*(void**)((char*)this_ + 0x12c), *(void**)((char*)this_ + 0x130));
    int* r = (int*)pRange;
    FUN_00565500((char*)this_ + 0x12c, (void*)*r, (r[1] - *r) / 0x24);
    if (!FUN_00562510((char*)this_ + 0x12c, a))
        return false;
    FUN_0055c2e0(a, b);
    return true;
}
}  // namespace SP


// @ 0x00563910
namespace SP {
bool cSPObjectTemplateDB_s0056_34e0::GetFeatureVector(uint32_t assetID, Traits::cFeatureVector_s0056_34e0& features)
{
    int index = FindAssetIndex(assetID);
    if (index != -1) {
        AssetInfo& asset = mAssetList[index];
        if (!asset.mFeatureVector.IsEmpty()) {
            features = mAssetList[index].mFeatureVector;
            if (mbUseClassifierWeights)
                Traits::ApplyWeights(features, mClassifierWeights);
            return true;
        }
    }
    return false;
}
}  // namespace SP


// @ 0x005639a0
namespace SP {
void* cSPObjectTemplateDB_s0056_34e0::FindSummaryByID(const uint32_t& id)
{
    for (eastl::map_s0056_34e0<uint32_t, AutoRefCount<FunctionalMatch::cISummarizer_s0056_34e0> >::iterator it = mSummarizerTable.begin(), itEnd = mSummarizerTable.end(); it != itEnd; ++it) {
        FunctionalMatch::cISummarizer_s0056_34e0* pSummarizer = (*it).second;
        if (pSummarizer->GetID() == id)
            return pSummarizer->GetSummary();
    }
    return 0;
}
}  // namespace SP


// @ 0x00563a30
namespace SP {
void* cSPObjectTemplateDB_s0056_34e0::FindSummary(uint32_t id)
{
    for (eastl::map_s0056_34e0<uint32_t, AutoRefCount<FunctionalMatch::cISummarizer_s0056_34e0> >::iterator it = mSummarizerTable.begin(), itEnd = mSummarizerTable.end(); it != itEnd; ++it) {
        FunctionalMatch::cISummarizer_s0056_34e0* pSummarizer = (*it).second;
        if (pSummarizer->GetID() == id)
            return pSummarizer->GetSummary();
    }
    return 0;
}
}  // namespace SP


// @ 0x00563ac0
namespace SP {
bool cSPObjectTemplateDB_s0056_34e0::ValidateResource(const ResourceKey_s0056_34e0& key, int flags)
{
    bool bResult = false;
    eastl::pair_s0056_34e0<eastl::map_s0056_34e0<uint32_t, AutoRefCount<FunctionalMatch::cISummarizer_s0056_34e0> >::iterator,
                eastl::map_s0056_34e0<uint32_t, AutoRefCount<FunctionalMatch::cISummarizer_s0056_34e0> >::iterator> itRange =
        mSummarizerTable.equal_range(key.mTypeID);
    if (itRange.first != itRange.second) {
        bResult = true;
        ScratchSlots<5>();
        IResourceManager_s0056_34e0* pManager = EA::ResourceMan::GetManager_s0056_34e0();
        IntrusivePtr_s0056_34e0<ResourceObject> pObject;
        if (pManager && pManager->GetResource(key, &pObject, 0, 0, 0, 0)) {
            cEditorResource_s0056_34e0* pEditor = EA::COM::interface_cast<cEditorResource_s0056_34e0>(pObject);
            if (pEditor) {
                eastl::basic_vector_s0056_34e0<uint32_t> blockIds;
                GetBlockIDs(pEditor, blockIds);
                for (; bResult && itRange.first != itRange.second; ++itRange.first) {
                    FunctionalMatch::cISummarizer_s0056_34e0* pSummarizer = (*itRange.first).second;
                    bResult = bResult && pSummarizer->Validate(pEditor, blockIds, flags);
                }
            }
        }
    }
    return bResult;
}
}  // namespace SP


// @ 0x00563c80
namespace SP {
void cSPObjectTemplateDB_s0056_34e0::SetClassifierWeights(const eastl::vector_map_s0056_34e0<uint32_t, float>& weights)
{
    mClassifierWeights.clear();
    for (const eastl::pair_s0056_34e0<uint32_t, float>* it = weights.mpBegin, *itEnd = weights.mpEnd; it != itEnd; ++it) {
        WeightMap::iterator itDefault = mDefaultClassifierWeights.find(it->first);
        if (itDefault != mDefaultClassifierWeights.end())
            mClassifierWeights[it->first] = it->second / itDefault->second;
    }
    ScratchSlots<8>();
}
}  // namespace SP


// @ 0x00563d60
namespace SP {
void cSPObjectTemplateDB_s0056_34e0::GetDefaultClassifierWeights(eastl::vector_map_s0056_34e0<uint32_t, float>& weights)
{
    weights.assign(mDefaultClassifierWeights.begin(), mDefaultClassifierWeights.end());
}
}  // namespace SP


// @ 0x00563df0
namespace SP {
uint32_t cQueryHost::Query(uint32_t a, uint32_t b)
{
    return ForwardedQuery(a, b);
}
}  // namespace SP

// @ 0x0056a5f0
void GetPartVolumePercentages(const Creature* pCreature, FloatVector* pPercentages)
{
    // local names chosen for the /Od slot order: t21 = part iterator, pEnd = parts end,
    // n21 = output iterator, t27 = output end, v8 = total weighted volume
    float v8 = 0.0f;
    pPercentages->resize(pCreature->mParts.size());
    ScratchSlots<20>();
    const Part* t21 = pCreature->mParts.mpBegin;
    const Part* const pEnd = pCreature->mParts.mpEnd;
    float* n21 = pPercentages->mpBegin;
    float* const t27 = pPercentages->mpEnd;
    for(; t21 != pEnd; ++t21, ++n21)
    {
        const Part* t14 = t21;
        float tmp;   // volume
        if(GetPartVolume(t14, &tmp))
        {
            v8 += tmp * t14->mScale;
            *n21 = tmp * t14->mScale;
        }
        else
            *n21 = 0.0f;
    }
    for(n21 = pPercentages->mpBegin; n21 != t27; ++n21)
        *n21 = *n21 * 100.0f / v8;
}
