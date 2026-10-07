// Slice s005598b0: SP::cSPObjectTemplateDB::Init (0x005598B0, 3187 bytes).
// Unoptimized module (SPObjectTemplateDB.obj): /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
//
// Init is the mirror of Shutdown (0x0055BFB0, slice s0055beb0):
//   * registers the OTDB cheat (when a cheat manager exists);
//   * subscribes the IHandlerRC base to the ten OTDB messages and to the command table;
//   * installs the OTDB resource factory (mpFactory, registered with the resource manager);
//   * records the three OTDB resource types to reindex and adds the two summarizers;
//   * reads the OTDB property lists: the population pairs (0x4598a6f), the per-asset parameter
//     lists (0x52f1c91 / 0x52f2304, forwarded to the asset-parameter loader) and the classifier
//     weights (0x52f2455), then stamps the pill record;
//   * adds the three default priority constraints and finally loads the database.
//
// Member and helper names not confirmed by the dev PDB are Claude-coined; the retail layout
// (offsets 0x94/0xc4/0x1d4/0x240/0x26c) comes from the disassembly.
#include "types.h"

template <int N> inline void ScratchSlots() { uint32_t s[N]; }

void* operator new(unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line);   // 0x00f473a0
void* operator new(unsigned int n);   // 0x006abeb0

namespace EA { namespace Allocator {
struct ZoneObject {
    static void* operator new(unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line);   // 0x00926020
};
} }

// ---------------------------------------------------------------------------
// App::Property / PropertyList
// ---------------------------------------------------------------------------
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
// EA::AutoRefCount<PropertyList>: AsPPVoidParam is out of line (0x0041d870).
template <typename T> class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    void** AsPPVoidParam();
    T** AsPP() { return (T**)AsPPVoidParam(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
}

// Smart pointer with an inline "release and give me the address" accessor.
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

// ---------------------------------------------------------------------------
// Resource factory / summarizers (ctors in slice s0055beb0)
// ---------------------------------------------------------------------------
struct IRefObj { virtual void v0(); virtual int AddRef(); virtual int Release(); };

struct cResBase1 : IRefObj {
    int mnRefCount;
    virtual ~cResBase1() {}
};
struct cResFinal : cResBase1, EA::Allocator::ZoneObject {
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

// ---------------------------------------------------------------------------
// Services
// ---------------------------------------------------------------------------
struct IHandlerRC { virtual bool HandleMessage(uint32_t msgID, void* msg); };
struct IMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void AddHandler(IHandlerRC* handler, uint32_t id);   // +0x20
};
struct ICommandServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void AddCommands(const void* table, int count);       // +0x20
};
struct IResourceManager {
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
IPropertyManager* PropertyManager();      // 0x0067de30
bool GetPropertyAsUint32(PropertyList* list, uint32_t id, uint32_t* value);   // 0x004af210
bool IsPillRecordStale(uint32_t instanceID, int expectedValue);              // 0x00558bf0
void WritePillRecord(uint32_t instanceID, uint32_t value);                    // 0x00558d50
void TouchAsset(uint32_t instanceID, int flag);                               // 0x00570480
}
namespace EA { namespace Messaging { IMessageServer* GetServer(); } }   // 0x00883860
namespace EA { namespace ResourceMan { IResourceManager* GetManager(); } }   // 0x0067dcd0
ICommandServer* GetCommandServer();       // 0x006895b0
void* GetOTDBService();                   // 0x008de1a0 (returns the global at 0x01667aa0)
extern void* g_pOTDBService;              // 0x015e3f00
struct CommandInfo { uint32_t id; const char* name; const char* description; };
extern CommandInfo sCommandInfos[];       // 0x0150cbc0
extern const uint32_t kOTDBTypeA;         // 0x013f4308
extern const uint32_t kOTDBTypeB;         // 0x013f4318

// ---------------------------------------------------------------------------
// Containers
// ---------------------------------------------------------------------------
namespace eastl {
template <typename T1, typename T2> struct pair {
    T1 first;
    T2 second;
    pair(const T1& a, const T2& b) : first(a), second(b) {}
};
template <typename T1, typename T2> inline pair<T1, T2> make_pair(T1 a, T2 b) { return pair<T1, T2>(a, b); }
}

struct InsertResult { void* it; bool inserted; InsertResult() {} };

struct U32Set {                 // eastl::vector_set<uint32_t>
    uint32_t pad[5];
    InsertResult insert(const uint32_t& v);                       // 0x00554020
};
struct U32U32Map {              // eastl::vector_map<uint32_t, uint32_t>
    uint32_t pad[5];
    InsertResult insert(const eastl::pair<uint32_t, uint32_t>& v); // 0x00564960
};
struct U32FloatMap {            // eastl::vector_map<uint32_t, float>
    uint32_t pad[5];
    InsertResult insert(const eastl::pair<uint32_t, float>& v);    // 0x00564960 (folded)
};
struct AssetTable {             // hash_map<uint32_t, AutoRefCount<cIResource>>
    uint32_t pad[0x1b];
    bool Rebuild();                                   // 0x0056df80
    bool Find(uint32_t id, IRefObj** out);            // 0x0056def0
};

namespace SP { namespace FunctionalMatch {
enum EqualConstraint { kEquals = 0 };
struct ConstraintVec {
    void* mpBegin; void* mpEnd; void* mpCapacity; uint32_t mAllocator;
    ~ConstraintVec();                                 // 0x004e1780
};
struct Constraint {
    unsigned int mParameter;
    int mType;
    int mMin, mMax;
    ConstraintVec mConstraints;
    uint32_t pad20;
    Constraint(unsigned int param, EqualConstraint, int value);   // 0x00558960
};
} }

namespace SP {

struct cISPObjectTemplateDB {
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
struct cIMatchTuning { virtual void m0(); };

class cSPObjectTemplateDB : public cISPObjectTemplateDB, public cIMatchTuning, public IHandlerRC {
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

    bool Init();
    bool LoadAssetParameters(IRefObj* asset, uint32_t count, void* data, bool stale);   // 0x0055d9e0
    void AddPriorityConstraint(const FunctionalMatch::Constraint& c, int priority);      // 0x00562680
    bool LoadDatabase();                                                                 // 0x0055ff10
};

// @ 0x005598B0
// Local names were chosen to reproduce the /Od name-hash stack-slot order:
//   nCount = command count, ok = OTDB property list, w = population property,
//   k/q/s = population pair iterator/end/count, u = asset-id property, a = pill record stale,
//   g = pill record version, f/h = asset-id iterator/end, p = classifier-weight property,
//   t/r = weight iterator/end.
// The ScratchSlots<N>() calls stand for the reserved frames of inline callees that cl declined
// (the vector_set/vector_map inserts and friends); they emit no code.
bool cSPObjectTemplateDB::Init()
{
    g_pOTDBService = GetOTDBService();
    ICheatManager* pCheatManager = CheatManager();
    if (pCheatManager)
        new ("Editor/OTDB", 0, 0, 0, 0) cOTDBCheat();

    IMessageServer* pMessageServer = EA::Messaging::GetServer();
    if (g_pOTDBService && pMessageServer) {
        pMessageServer->AddHandler(static_cast<IHandlerRC*>(this), 0xca665fa7);
        pMessageServer->AddHandler(static_cast<IHandlerRC*>(this), 0x165e841);
        pMessageServer->AddHandler(static_cast<IHandlerRC*>(this), 0x1a7f758);
        pMessageServer->AddHandler(static_cast<IHandlerRC*>(this), 0x5132ed1);
        pMessageServer->AddHandler(static_cast<IHandlerRC*>(this), 0x5132eec);
        pMessageServer->AddHandler(static_cast<IHandlerRC*>(this), 0x3743e04);
        pMessageServer->AddHandler(static_cast<IHandlerRC*>(this), 0x212d3e7);
        pMessageServer->AddHandler(static_cast<IHandlerRC*>(this), 0x680c633);
        pMessageServer->AddHandler(static_cast<IHandlerRC*>(this), 0x4c6f86a);
        pMessageServer->AddHandler(static_cast<IHandlerRC*>(this), 0x64e331c);

        int nCount = 1;
        GetCommandServer()->AddCommands(sCommandInfos, nCount);
        for (int i = 0; i < nCount; ++i)
            pMessageServer->AddHandler(static_cast<IHandlerRC*>(this), sCommandInfos[i].id);

        mpFactory = new ("OTDB", 0, 0, 0, 0) cOTDBResourceFactory();
        EA::ResourceMan::GetManager()->RegisterFactory(true, mpFactory.get(), 0);
        ScratchSlots<12>();

        mResourceTypesToReindex.insert(kOTDBTypeA);
        mResourceTypesToReindex.insert(0x52def3f);
        mResourceTypesToReindex.insert(kOTDBTypeB);

        AddSummarizer(new cSummarizerA());
        AddSummarizer(new cSummarizerB());

        EA::AutoRefCount<PropertyList> ok(0);
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
                ScratchSlots<4>();
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
            ScratchSlots<3>();

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
            ScratchSlots<12>();
        }

        AddPriorityConstraint(FunctionalMatch::Constraint(0x5dc0b88, FunctionalMatch::kEquals, 0), 0);
        AddPriorityConstraint(FunctionalMatch::Constraint(0x5dc0b88, FunctionalMatch::kEquals, 1), 0);
        AddPriorityConstraint(FunctionalMatch::Constraint(0x5dc0b88, FunctionalMatch::kEquals, 2), 0);

        if (LoadDatabase())
            return true;
    }
    return false;
}

}  // namespace SP
