// Slice s0055beb0: SP::cFunctionalTestCheat, SP::cSPObjectTemplateDB and the
// Editor ObjectTemplateDB factory. Unoptimized /Od module.
#include "types.h"

void* operator new(unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line);
void  operator delete(void* p);

namespace Editor {
class ObjectTemplateDB {
public:
    ObjectTemplateDB();
    uint32_t pad[0x270 / 4];
};
}

namespace SP {

// @ 0x0055BEB0
class cFunctionalTestCheat {
public:
    const char* Description(int index);
    bool IsEnabled();
};
const char* cFunctionalTestCheat::Description(int index) {
    if (index == 0)
        return "Used to debug OTDB parameters";
    else
        return "\n-get_key_params <SPID key name>\n   dump otdb parameters associated with the given file/key\n"
               "-get_id_params <SPID key name>\n   dump otdb parameters associated with the given server id.\n";
}

// @ 0x0055BEE0
bool cFunctionalTestCheat::IsEnabled() {
    return true;
}

// @ 0x0055C640  Editor::ObjectTemplateDB factory
Editor::ObjectTemplateDB* CreateObjectTemplateDB() {
    return new ("Editor/ObjectTemplateDB", 0, 0, 0, 0) Editor::ObjectTemplateDB();
}

}  // namespace SP

// ---------------------------------------------------------------------------
// Persistence helpers and the rest of cSPObjectTemplateDB (completed)
// ---------------------------------------------------------------------------
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)

struct ResKey { uint32_t instance, type, group; };
struct AssetParam {            // 12 bytes: id, value type, value (int or float)
    uint32_t id;
    uint32_t type;
    union { uint32_t i; float f; } val;
};
struct ExtraParam { uint32_t a, b; float c; };

namespace EA { namespace IO {
struct IStream;
bool WriteUint32(IStream* s, const uint32_t* v, uint32_t count, int endian);   // 0x0093aa70
bool ReadInt32(IStream* s, void* v, uint32_t count, int endian);               // 0x0093a780
} }
using EA::IO::IStream;

inline bool WriteU32(IStream* s, uint32_t value) { return EA::IO::WriteUint32(s, &value, 1, 0); }
inline bool WriteF32(IStream* s, float value) { return EA::IO::WriteUint32(s, (uint32_t*)&value, 1, 0); }
inline bool ReadI32(IStream* s, void* dst) { return EA::IO::ReadInt32(s, dst, 1, 0); }

struct IRecord {   // an open record (stream owner)
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual IStream* GetStream();   // +0x18
    virtual void v7(); virtual void v8();
    virtual void Close();           // +0x24
};
struct IRecordArea {   // record opener (database / save area)
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual void Save();            // +0x24
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual bool OpenRecord(const ResKey* key, IRecord** out, int access, int create, int a5, int a6);   // +0x34
};
struct IResourceManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual IRecordArea* GetRecordArea(const ResKey* key);   // +0x58
};

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }

template <typename T> struct ARC {   // EA::AutoRefCount
    T* mp;
    ARC() : mp(0) {}
    ~ARC() { if (mp) mp->Release(); }
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

namespace SP { IRecordArea* GetSaveArea(uint32_t id); }                       // 0x006b1f90
namespace EA { namespace ResourceMan { IResourceManager* GetManager(); } }    // 0x0067dcd0
bool LoadExtraParameters(IStream* s, ParamVec<ExtraParam>* extra, uint32_t version);   // 0x0055ce80

// @ 0x0055C9E0
// (local names chosen to reproduce the /Od frame slot order)
bool WriteExtraParameters(IStream* s, const ParamVec<ExtraParam>* v)
{
    const ExtraParam* b;
    const ExtraParam* cur;
    bool bSuccess = true;
    uint32_t pEntry = v->size();
    bSuccess = bSuccess && WriteU32(s, pEntry);
    for (b = v->mpBegin, cur = v->mpEnd; bSuccess && b != cur; ++b) {
        const ExtraParam* p = b;
        bSuccess = bSuccess && WriteU32(s, p->a);
        bSuccess = bSuccess && WriteU32(s, p->b);
        bSuccess = bSuccess && WriteF32(s, p->c);
    }
    return bSuccess;
}

// @ 0x0055C6F0  SP::cSPObjectTemplateDB::SaveAssetParameters
// (local names chosen to reproduce the /Od frame slot order)
bool SaveAssetParameters(const ResKey* key, const ParamVec<AssetParam>* params, const ParamVec<ExtraParam>* extra)
{
    bool ok = false;
    IRecordArea* area = SP::GetSaveArea(0x11ac19c);
    if (area) {
        ARC<IRecord> pKey;
        ResKey pEnd = *key;
        pEnd.type = 0x2d5c9af;
        pKey.Reset();
        if (area->OpenRecord(&pEnd, &pKey.mp, 2, 2, 1, 0)) {
            IStream* pStream = pKey->GetStream();
            ok = WriteU32(pStream, 4);
            ok = ok && WriteU32(pStream, params->size());
            for (const AssetParam* saveKey = params->mpBegin, *result = params->mpEnd; saveKey != result && ok; ++saveKey) {
                const AssetParam* n = saveKey;
                ok = ok && WriteU32(pStream, n->id);
                ok = ok && WriteU32(pStream, n->type);
                switch (n->type) {
                case 0x2e1a75d:
                    ok = ok && WriteU32(pStream, n->val.i);
                    break;
                case 0x2e1a7ff:
                    ok = ok && WriteF32(pStream, n->val.f);
                    break;
                default:
                    ok = false;
                    break;
                }
            }
            ok = ok && WriteExtraParameters(pStream, extra);
            pKey->Close();
        }
    }
    return ok;
}

// @ 0x0055CB50  SP::cSPObjectTemplateDB::LoadAssetParameters
// (local names chosen to reproduce the /Od frame slot order)
bool LoadAssetParameters(IStream* s, ParamVec<AssetParam>* params, ParamVec<ExtraParam>* extra)
{
    ScratchSlots<10>();
    uint32_t iter;
    bool bSuccess = false;
    bSuccess = ReadI32(s, &iter);
    bSuccess = bSuccess && iter >= 4;
    if (!bSuccess)
        return false;
    int e;
    if (bSuccess && ReadI32(s, &e)) {
        params->resize(e);
        bSuccess = e != 0;
        for (AssetParam* ver = params->mpBegin, *entry = params->mpEnd; ver != entry && bSuccess; ++ver) {
            AssetParam* pEnd2 = ver;
            bSuccess = bSuccess && ReadI32(s, &pEnd2->id);
            uint32_t pEnd;
            bSuccess = bSuccess && ReadI32(s, &pEnd);
            pEnd2->type = pEnd;
            switch (pEnd2->type) {
            case 0x2e1a75d:
                bSuccess = bSuccess && ReadI32(s, &pEnd2->val);
                break;
            case 0x2e1a7ff:
                bSuccess = bSuccess && ReadI32(s, &pEnd2->val);
                break;
            default:
                bSuccess = false;
                break;
            }
        }
    }
    if (extra)
        bSuccess = bSuccess && LoadExtraParameters(s, extra, iter);
    return bSuccess;
}

// @ 0x0055CD90  SP::cSPObjectTemplateDB::LoadAssetParametersFromKey
bool LoadAssetParametersFromKey(const ResKey* key, ParamVec<AssetParam>* params, ParamVec<ExtraParam>* extra)
{
    bool ok = false;
    ScratchSlots<4>();
    params->erase(params->mpBegin, params->mpEnd);
    IRecordArea* area = EA::ResourceMan::GetManager()->GetRecordArea(key);
    if (area) {
        ARC<IRecord> rec;
        rec.Reset();
        if (area->OpenRecord(key, &rec.mp, 1, 3, 1, 0)) {
            IStream* s = rec->GetStream();
            ok = LoadAssetParameters(s, params, extra);
            rec->Close();
        }
    }
    return ok;
}

// ---------------------------------------------------------------------------
// cSPObjectTemplateDB members used by Shutdown / HandleMessage / shuffle
// ---------------------------------------------------------------------------
struct Key3 { uint32_t a, b, c; };


struct cISPObjectTemplateDB {
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
struct cIMatchTuning { virtual void m0(); };
struct IMessage {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual IMessage* GetSource();      // +0x14
    virtual void m6(); virtual void m7(); virtual void m8(); virtual void m9(); virtual void m10();
    virtual void Dispatch(int flag);    // +0x2c
};
struct IMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void Post(uint32_t id, void* data, int flag);        // +0x14
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10();
    virtual void RemoveHandler(void* handler, uint32_t id, int pri);   // +0x2c
};
struct IHandlerRC {
    virtual bool HandleMessage(uint32_t msgID, void* msg);
};
struct ICheatManager {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4();
    virtual void c5(); virtual void c6();
    virtual void Remove(const char* name);   // +0x1c
};
struct ICommandServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual void RegisterCommands(const void* table, int count);   // +0x2c
};
struct IRefObj { virtual void v0(); virtual int AddRef(); virtual int Release(); };
struct MsgArg { uint32_t a, b; };
struct MsgData {
    uint32_t pad[2];
    MsgArg args[2];
    MsgArg& operator[](int i) { return args[i]; }
};

namespace SP {
ICheatManager* CheatManager();            // 0x0067de20
IMessageServer* MessageServer();          // 0x0067dcc0
}
namespace EA { namespace Messaging { IMessageServer* GetServer(); } }   // 0x00883860
ICommandServer* GetCommandServer();       // 0x006895b0
extern char sCommandInfos[];              // 0x0150cbc0, 12-byte entries

struct U32Vec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    bool empty() const;                     // 0x00526430
    void clear() { erase(mpBegin, mpEnd); }
    void erase(uint32_t* a, uint32_t* b);   // 0x004769b0
};
struct U32Set {
    uint32_t pad[5];
    void insert(void* pairOut, const uint32_t* v);    // 0x00554020
};
struct Rng { uint32_t seed; uint32_t RandomUint32Uniform(uint32_t n); };   // 0x00a68fb0
struct ClearableTable { uint32_t pad[0x20]; void Clear(); };              // 0x00564cd0

namespace SP {
class cSPObjectTemplateDB : public cISPObjectTemplateDB, public cIMatchTuning, public IHandlerRC {
public:
    int mRefCount;                             // +0x0c
    uint32_t pad10[(0x40 - 0x10) / 4];
    uint8_t mFlag40;                           // +0x40
    uint8_t pad41[3];
    uint32_t pad44[(0x64 - 0x44) / 4];
    U32Set mSet;                               // +0x64
    uint32_t pad78[(0x7c - 0x78) / 4];
    U32Vec mVec;                               // +0x7c
    uint32_t pad88[(0x1cc - 0x88) / 4];
    Rng mRandom;                               // +0x1cc
    uint8_t mDirty;                            // +0x1d0
    uint8_t pad1d1[3];
    uint32_t pad1d4[(0x1ec - 0x1d4) / 4];
    ClearableTable mTable;                     // +0x1ec
    ARC<IRefObj> mpAuto;                       // +0x26c

    virtual bool HandleMessage(uint32_t msgID, void* msg);
    bool Shutdown();
    bool RandomizeFirstN(ParamVec<Key3>* v, int n);
    void* AsInterface(uint32_t type);
    void CheckForMinPopulations();      // 0x00561bd0
    void FUN_00561220(void* p);
    void FUN_0055e190(int a, int b);
    void FUN_00560470();
    void SetMode(const char* name);   // 0x0052e650
};
}

// @ 0x0055C2E0  partial Fisher-Yates shuffle of the first n entries, then truncate to n
// (local names chosen to reproduce the /Od frame slot order)
bool SP::cSPObjectTemplateDB::RandomizeFirstN(ParamVec<Key3>* v, int n)
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
    ScratchSlots<11>();
    return !v->empty();
}

// @ 0x0055C690
void* SP::cSPObjectTemplateDB::AsInterface(uint32_t type)
{
    switch (type) {
    case 0x4ed03fd:
        return this;
    case 0x4ed5013:
        return static_cast<cIMatchTuning*>(this);
    case 0xee3f516e:
        return this;
    }
    return 0;
}

// @ 0x0055BFB0  SP::cSPObjectTemplateDB::Shutdown
bool SP::cSPObjectTemplateDB::Shutdown()
{
    ICheatManager* manager = SP::CheatManager();
    if (manager)
        manager->Remove("otdb_test");
    IMessageServer* pMessageServer = EA::Messaging::GetServer();
    if (pMessageServer) {
        pMessageServer->RemoveHandler(static_cast<IHandlerRC*>(this), 0xca665fa7, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC*>(this), 0x1a7f758, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC*>(this), 0x165e841, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC*>(this), 0x5132ed1, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC*>(this), 0x5132eec, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC*>(this), 0x3743e04, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC*>(this), 0x212d3e7, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC*>(this), 0x680c633, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC*>(this), 0x4c6f86a, 0xffffd8f1);
        pMessageServer->RemoveHandler(static_cast<IHandlerRC*>(this), 0x64e331c, 0xffffd8f1);
    }
    int nCmds = 1;
    GetCommandServer()->RegisterCommands(sCommandInfos, nCmds);
    for (int i = 0; i < nCmds; ++i)
        pMessageServer->RemoveHandler(static_cast<IHandlerRC*>(this), *(uint32_t*)(sCommandInfos + i * 12), 0xffffd8f1);
    mpAuto = 0;
    mTable.Clear();
    mFlag40 = 0;
    SetMode("Production");
    return true;
}

// @ 0x0055C3C0  SP::cSPObjectTemplateDB::HandleMessage (IHandlerRC base, this = +8)
// Not byte-exact: the original keeps every case local in one switch-level frame (slot hash order) with
// extra reserved frames from declined inlines; those holes are only approximated here.
bool SP::cSPObjectTemplateDB::HandleMessage(uint32_t msgID, void* msg)
{
    ScratchSlots<5>();
    switch (msgID) {
    case 0xca665fa7:
    case 0x1a7f758:
    case 0x165e841:
    case 0x5132ed1: {
        Key3 key = *(Key3*)msg;
        if (IsObjectKnown(&key))
            SP::MessageServer()->Post(0x9421c619, msg, 0);
        break;
    }
    case 0x64e331c: {
        void* data = msg;
        FUN_00561220(data);
        break;
    }
    case 0x5132eec: {
        Key3 key = *(Key3*)msg;
        Reload(&key, 0);
        break;
    }
    case 0x264a132: {
        FUN_0055e190(1, 0);
        IMessage* m = (IMessage*)msg;
        m->GetSource()->Dispatch(0);
        break;
    }
    case 0x3743e04: {
        CheckForMinPopulations();
        if (!mVec.empty()) {
            uint32_t* last = mVec.mpEnd;
            uint32_t* first = mVec.mpBegin;
            for (uint32_t* it = first; it != last; ++it) {
                char tmp[8];
                uint32_t holeA[5];
                mSet.insert(tmp, it);
            }
            mVec.clear();
        }
        break;
    }
    case 0x212d3e7:
    case 0x680c633:
        if (mDirty) {
            FUN_00560470();
            mDirty = 0;
        }
        SP::GetSaveArea(0x11ac19c)->Save();
        break;
    case 0x4c6f86a: {
        MsgData* d = (MsgData*)msg;
        uint32_t v = (*d)[0].a;
        SetMode((const char*)v);
        break;
    }
    }
    return true;
}

// ---------------------------------------------------------------------------
// Constructors (vtable chains, atomic zero of the refcount)
// ---------------------------------------------------------------------------
struct cResBase0 { virtual ~cResBase0() {} };
struct AtomicInt32 {
    long mValue;
    void SetValue(long v) { long* p = &mValue; _InterlockedExchange(p, v); }
};
struct cResBase1 : cResBase0 {
    AtomicInt32 mnRefCount;
    cResBase1() { mnRefCount.SetValue(0); }
    virtual ~cResBase1() {}
};
struct cResFinal : cResBase1 {
    cResFinal();
    virtual ~cResFinal() {}
};
// @ 0x0055BF10
cResFinal::cResFinal() {}

struct cSummarizerBase {
    int mField;
    cSummarizerBase() : mField(0) {}
    virtual ~cSummarizerBase() {}
};
struct cSummarizerFinal : cSummarizerBase {
    cSummarizerFinal();
    virtual ~cSummarizerFinal() {}
};
// @ 0x0055BF50
cSummarizerFinal::cSummarizerFinal() {}
