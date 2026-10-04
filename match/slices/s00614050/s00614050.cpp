// Slice s00614050: SP::Pollen asset cache (a message handler that keeps a map of 64-bit server
// asset ids to loaded Pollinator asset resources, registers the PFRecordRead factory and
// answers asset-list messages), SP::Pollen::cServerResponse (expat XML wrapper stream) and
// its handler tables (eastl vector_map/map<string,string> instances).
// Built /O2 /MD /Gy /TP (no /EHsc).
#include "types.h"
#include <intrin.h>
#pragma intrinsic(_InterlockedExchange)
typedef unsigned int size_type;
typedef int off_type;
typedef unsigned __int64 u64;

struct XML_ParserStruct;
typedef XML_ParserStruct* XML_Parser;
extern "C" {
int XML_Parse(XML_Parser p, const char* s, int len, int isFinal);
void XML_ParserFree(XML_Parser p);
int XML_GetErrorCode(XML_Parser p);
__declspec(dllimport) int __cdecl sscanf(const char*, const char*, ...);
int __cdecl wcscmp(const wchar_t*, const wchar_t*);
}
#pragma intrinsic(wcscmp)
inline void* operator new(unsigned int, void* p) { return p; }

// EASTL allocator entry points (EASTL_allocator_allocate / _deallocate)
void* EASTL_alloc(unsigned size, const char* name, int flags, int a, const char* file, int line);
void EASTL_free(void* p);
void* PollNew(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00926020 (ZoneObject::operator new)

struct ResourceKey { uint32_t instanceID, typeID, groupID; };

struct IRefCounted {
    virtual int AddRef();
    virtual int Release();
    virtual int slot8();
    virtual void* Cast(uint32_t typeID);
};

template <typename T> struct RefPtrNI {   // AutoRefCount whose operator= stays out of line (0x00b5f950)
    T* p;
    RefPtrNI() : p(0) {}
    __declspec(noinline) RefPtrNI& operator=(T* o) {
        if (o != p) {
            T* t = p;
            if (o) o->AddRef();
            p = o;
            if (t) t->Release();
        }
        return *this;
    }
};
template <typename T> struct RefPtr {
    T* p;
    RefPtr() : p(0) {}
    RefPtr(T* o) : p(o) { if (p) p->AddRef(); }
    __declspec(noinline) RefPtr& operator=(const RefPtrNI<T>& x) { return operator=(x.p); }   // 0x00ac9480
    ~RefPtr() { if (p) p->Release(); }
    __forceinline RefPtr& operator=(T* o) {
        if (o != p) {
            T* t = p;
            if (o) o->AddRef();
            p = o;
            if (t) t->Release();
        }
        return *this;
    }
};

// --- wide strings (eastl::basic_string<wchar_t>) ---------------------------------------
inline size_type CharStrlen(const wchar_t* s) {
    const wchar_t* p = s;
    while (*p) ++p;
    return (size_type)(p - s);
}
void* MemCopy(void* d, const void* s, size_type n);   // 0x011e0744 (memcpy thunk)
template <typename T> inline const T& emin(const T& a, const T& b) { return (b < a) ? b : a; }
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int mAllocator;
    string16() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    string16(const string16& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
    static wchar_t* CharStringUninitializedCopy(const wchar_t* pFirst, const wchar_t* pLast, wchar_t* pResult) {
        MemCopy(pResult, pFirst, (pLast - pFirst) * 2);
        return pResult + (pLast - pFirst);
    }
    void RangeInitialize(const wchar_t* pBegin, const wchar_t* pEnd) {
        const size_type n = (size_type)(pEnd - pBegin);
        AllocateSelf(n + 1);
        mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
        *mpEnd = 0;
    }
    ~string16() {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin) EASTL_free(mpBegin);
        }
    }
    void AllocateSelf(size_type n);                      // 0x00429760
    string16& erase(size_type position, size_type n);   // 0x004228e0
    size_type find_first_not_of(const wchar_t* p, size_type pos) const;   // 0x00579af0
    void resize(size_type n);                            // 0x00429520
    void append(const wchar_t* b, const wchar_t* e);     // 0x00429580
    void RangeInitialize(const wchar_t* p);              // 0x00579a90 (string(const wchar_t*))
    static int Compare(const wchar_t* a, const wchar_t* b, size_type n) {
        for (; n > 0; ++a, ++b, --n)
            if (*a != *b) return (*a < *b) ? -1 : 1;
        return 0;
    }
    __forceinline int compare(const wchar_t* p) const {
        const wchar_t* pEnd2 = p + CharStrlen(p);
        const int n1 = (int)(mpEnd - mpBegin);
        const int n2 = (int)(pEnd2 - p);
        const int nMin = emin(n1, n2);
        const int c = Compare(mpBegin, p, nMin);
        return c ? c : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0));
    }
    int compare(const string16& x) const;
    int compare_out(const wchar_t* p) const;   // out-of-line compare(const wchar_t*) at 0x00614950
};
int StringCompare(const wchar_t* b1, const wchar_t* e1, const wchar_t* b2, const wchar_t* e2);  // 0x005e9260
inline int string16::compare(const string16& x) const { return StringCompare(mpBegin, mpEnd, x.mpBegin, x.mpEnd); }
inline bool operator<(const string16& a, const string16& b) { return a.compare(b) < 0; }
struct less16 { bool operator()(const string16& a, const string16& b) const { return a < b; } };

struct StrPair {       // eastl::pair<string16 const, string16>
    string16 first;
    string16 second;
    StrPair(const StrPair& x);                         // 0x00614990
    StrPair(const string16& a, const string16& b);     // 0x0088c0d0
    ~StrPair();                                        // 0x00614c00
};

// --- vector_map<const wchar_t*, mem_fun_t<void, cServerResponse>, char16less> -----------
struct __declspec(align(8)) mem_fun_t {
    void* fn;
    int adj;
};
struct HandlerPair {
    const wchar_t* first;
    mem_fun_t second;
};
struct char16less {
    bool operator()(const wchar_t* a, const wchar_t* b) const { return wcscmp(a, b) < 0; }
};
struct HandlerRange {
    HandlerPair* first;
    HandlerPair* second;
};
HandlerPair* lower_bound(HandlerPair* first, HandlerPair* last, const wchar_t* const& value, char16less c);

struct HandlerMap {
    HandlerPair* mpBegin;
    HandlerPair* mpEnd;
    HandlerPair* mpCapacity;
    int mAlloc;
    int pad4;
    char16less mCompare;     // +0x14
    HandlerRange equal_range(const wchar_t* const& k);
    void DoReallocate(size_type n);
};
extern HandlerMap gElementHandlers;   // 0x015f5088

// --- rbtree<string16, pair<string16 const, string16>> ----------------------------------
struct RBNode { RBNode* right; RBNode* left; RBNode* parent; char color; char side; };
struct StrNode : RBNode { StrPair mValue; };
void RBTreeInsert(RBNode* n, RBNode* parent, RBNode* anchor, int side);   // 0x009216a0
struct StrMapIter { StrNode* mpNode; };
struct StrMap {
    char pad0[4];
    RBNode mAnchor;       // +4
    unsigned mnSize;      // +0x14
    int mAlloc;
    StrMapIter* find(StrMapIter* out, const string16& key);   // 0x005e96f0 (shared with use_self trees)
    StrMapIter DoInsertValueImpl(RBNode* pNodeParent, const StrPair& value, bool bForceToLeft);
};

// --- the stream class ------------------------------------------------------------------
namespace EA { namespace IO {
class IStream {
public:
    virtual ~IStream() {}
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual unsigned int GetType() const = 0;
    virtual int GetAccessFlags() const = 0;
    virtual int GetState() const = 0;
    virtual bool Close() = 0;
    virtual size_type GetSize() const = 0;
    virtual bool SetSize(size_type size) = 0;
    virtual off_type GetPosition(int positionType = 0) const = 0;
    virtual bool SetPosition(off_type position, int positionType = 0) = 0;
    virtual size_type GetAvailable() const = 0;
    virtual size_type Read(void* pData, size_type nSize) = 0;
    virtual bool Flush() = 0;
    virtual bool Write(const void* pData, size_type nSize) = 0;
};
}}
class RefCountVBase {
public:
    virtual ~RefCountVBase() {}
    virtual int AddRef();
    virtual int Release();
    int mnRefCount;
};

namespace SP { namespace Pollen {
class cServerResponse : public RefCountVBase, public EA::IO::IStream {
public:
    int mnReturnCode;                 // +0xc (Code: 0 success, 1 failure, 2 error)
    StrMap mFieldDict;                // +0x10
    char pad0[0x40 - 0x2c];  // asset list vector etc.
    XML_Parser mpXMLParser;           // +0x40
    string16 mCharacterData;          // +0x44
    bool mbInResponse;                // +0x54
    bool mbOpen;                      // +0x55
    int mParseStatus;                 // +0x58
    int mnBytesRead;                  // +0x5c

    // IStream overrides (these bodies see `this` as the IStream subobject)
    virtual int AddRef();
    virtual int Release();
    virtual unsigned int GetType() const;
    virtual int GetAccessFlags() const;
    virtual int GetState() const;
    virtual bool Close();
    virtual size_type GetSize() const;
    virtual bool SetSize(size_type size);
    virtual off_type GetPosition(int positionType = 0) const;
    virtual bool SetPosition(off_type position, int positionType = 0);
    virtual size_type GetAvailable() const;
    virtual size_type Read(void* pData, size_type nSize);
    virtual bool Flush();
    virtual bool Write(const void* pData, size_type nSize);

    void GetStatus();
    const wchar_t* GetField(const wchar_t* name);
    static void CharacterData(cServerResponse* self, const wchar_t* s, int len);
    static void StartElement(cServerResponse* self, const wchar_t* name);
};
}}
using namespace SP::Pollen;

// ===========================================================================================
// asset cache
// ===========================================================================================
struct IKeyFilter;
template <typename T> struct KeyVec { T* mpBegin; T* mpEnd; T* mpCapacity; };
struct IResourceManager {
    virtual ~IResourceManager();
    virtual bool Initialize();
    virtual bool Dispose();
    virtual bool GetResource(const ResourceKey* key, RefPtr<IRefCounted>* dst, void* a, void* b, void* c, void* d);  // 0x0c
    virtual bool GetResourceAsync();
    virtual bool GetLoadedResource(const ResourceKey* key, RefPtr<IRefCounted>* dst);                                 // 0x14
    virtual bool ReloadResource();
    virtual bool GetPrivateResource();
    virtual bool WriteResource(IRefCounted* res, void* data, void* db, void* factory, void* name);                    // 0x20
    virtual void SetTypeMapping();
    virtual int GetRecordTypesFromResourceType();
    virtual int GetTypeMapping();
    virtual int FindRecord();
    virtual int GetResourceKeyList();
    virtual int GetRecordKeyList(KeyVec<ResourceKey>* dst, IKeyFilter* filter, void* dbs);                            // 0x38
    virtual int GetRecordKeyList2();
    virtual bool RegisterChangeNotification();
    virtual bool RegisterFactory(bool add, struct IFactory* factory, int arg);                                            // 0x44
    virtual int FindFactory();
    virtual int GetFactoryList();
    virtual bool RegisterDatabase();
    virtual bool IsDatabaseRegistered();
    virtual int FindDatabase();
    virtual int GetDatabaseList();
    virtual void DoDatabaseChanged();
    virtual bool RegisterCache();
    virtual int FindCache();
    virtual bool CacheResource(IRefCounted* res, bool flag);                                                          // 0x6c
};
IResourceManager* GetManager();   // 0x0067dcd0 (EA::ResourceMan::GetManager)

// IKeyFilter used to list all records of one type (vtable 0x013eb428)
struct IKeyFilter { virtual bool Accept(const ResourceKey*); };
extern void* kFilterBaseVtbl[];   // 0x013eb394
struct TypeKeyFilter : IKeyFilter {
    uint32_t mnType;
    TypeKeyFilter(uint32_t t) : mnType(t) {}
};

struct cAssetDirectory {
    char pad[0];
    bool GetLocalKey(u64 id, ResourceKey* out);                 // 0x0054e460
    bool HasAsset(u64 id);                                      // 0x0054e740
    bool GetServerId(const ResourceKey* key, u64* out, bool b); // 0x0054e530
};
struct cPollinator {
    char pad[0x58];
    cAssetDirectory* mpAssetDirectory;
};
cPollinator* GetPollinator();   // 0x0067cb30

// a loaded Pollinator asset resource (0x130 bytes)
struct cPollenAsset : IRefCounted {
    int mnRef;                      // +4
    ResourceKey mKey;               // +8
    int pad14;
    u64 mId;                        // +0x18
    u64 GetId() const { return mId; }
    char mData[0x130 - 0x20];       // +0x20
    cPollenAsset(u64 id);           // 0x00612f00
    static void* operator new(size_t n, const char* name, int a, int b, int c, int d);   // 0x00f473a0
    void SetData(uint32_t a, uint32_t b, void* c);   // 0x00613140
};
void* GetSaveArea(uint32_t id);    // SP::GetSaveArea 0x006b1f90

struct AssetEntry {
    u64 key;
    RefPtr<cPollenAsset> value;
    int pad;
};
struct AssetMap {
    AssetEntry* mpBegin;
    AssetEntry* mpEnd;
    char pad[0x14 - 8];
    bool mbFlag;                                   // +0x14 (== cache +0x9c)
    RefPtr<cPollenAsset>* operator_index(const u64& key);   // 0x00613dd0
    AssetEntry* find(const u64& key);
};
AssetEntry* lower_bound_asset(AssetEntry* b, AssetEntry* e, const u64* key, bool flag);   // 0x007c8160
struct AssetRange { AssetEntry* first; AssetEntry* second; };
inline AssetEntry* AssetMap::find(const u64& key) {
    AssetRange r;
    AssetEntry* const itEnd = mpEnd;
    AssetEntry* it = lower_bound_asset(mpBegin, itEnd, &key, mbFlag);
    if (it != itEnd && !(key < it->key)) {
        r.first = it;
        r.second = it + 1;
    } else {
        r.first = it;
        r.second = it;
    }
    return (r.first != r.second) ? r.first : itEnd;
}

struct IMessageServer {
    virtual int slot00(); virtual int slot04(); virtual int slot08(); virtual int slot0c();
    virtual int slot10();
    virtual bool PostMessage(uint32_t id, void* data, int flag);   // 0x14
    virtual int slot18(); virtual int slot1c(); virtual int slot20();
    virtual bool AddListener(void* listener, uint32_t id);          // 0x24
};
IMessageServer* GetMessageServer();   // SP::MessageServer 0x0067dcc0

struct IMsgObj {
    virtual int slot00(); virtual int slot04(); virtual int slot08(); virtual int slot0c();
    virtual uint32_t GetTypeID();   // 0x10
};

struct cAssetCache {
    void* vtbl;                     // +0
    IMessageServer* mpServer;       // +4
    cAssetCache* mpSelf;            // +8
    const uint32_t* mpMessages;     // +0xc
    int mnMessages;                 // +0x10
    int mnZero;                     // +0x14
    cPollinator* mpPollinator;      // +0x18
    char pad1c[0x88 - 0x1c];
    AssetMap mMap;                  // +0x88

    void LoadAll();                                      // 0x00614050
    void AddAsset(u64 id, const void* data);             // 0x00614280
    bool RemoveAsset(u64 id);                            // 0x006144c0
    bool Fn613c60(cPollenAsset* a);                      // 0x00613c60
    bool Fn613e50(uint32_t a, cPollenAsset* b);          // 0x00613e50
    void Fn613ab0(uint32_t a);                           // 0x00613ab0
    bool ReadRecord(void* rec, struct cPollenAsset* obj, uint32_t unused, uint32_t type);   // 0x00614560
    void Init(cPollinator* pollinator);                  // 0x006145d0
    bool HandleMessage(uint32_t id, void* msg);          // 0x006146c0
};

// ---- helpers --------------------------------------------------------------------------
struct IRecord {
    virtual int slot00(); virtual int slot04(); virtual int slot08(); virtual int slot0c();
    virtual const ResourceKey* GetKey();    // 0x10
    virtual int slot14();
    virtual uint32_t GetSize();             // 0x18
};
// 0x15f4ccc: the PFRecordRead resource factory
struct IFactory { virtual void slot0(); virtual int AddRef(); virtual int Release(); };
extern RefPtr<IFactory> gPFRecordReadFactory;
struct RecordReadBase : IFactory {
    volatile long mnRef;
    RecordReadBase() { _InterlockedExchange(&mnRef, 0); }
    virtual void slot0();
    virtual int AddRef();
    virtual int Release();
};
struct PFRecordRead : RecordReadBase {
    PFRecordRead() {}
    virtual void slot0();
    virtual int AddRef();
    virtual int Release();
};
extern uint32_t kPollenMessages;   // 0x013fc0bc (2 entries)

// @ 0x00614050
void cAssetCache::LoadAll()
{
    KeyVec<ResourceKey> keys = { 0, 0, 0 };
    TypeKeyFilter filter(0xfd60f0c1);
    GetManager()->GetRecordKeyList(&keys, &filter, 0);
    for (uint32_t i = 0; i < (uint32_t)(keys.mpEnd - keys.mpBegin); ++i) {
        RefPtr<IRefCounted> obj;
        IResourceManager* mgr = GetManager();
        obj = 0;
        if (mgr->GetResource(&keys.mpBegin[i], &obj, 0, 0, 0, 0)) {
            if (obj.p) {
                cPollenAsset* a = (cPollenAsset*)obj.p->Cast(0xaaff1cde);
                if (a) {
                    u64 key1;
                    u64 key2;
                    ResourceKey lk = { 0, 0, 0 };
                    if (mpPollinator->mpAssetDirectory->GetLocalKey(a->GetId(), &lk) &&
                        GetManager()->GetResource(&lk, 0, 0, 0, 0, 0)) {
                        key1 = a->GetId();
                        *mMap.operator_index(key1) = a;
                    } else if (a->GetId() < 0xffffffffull) {
                        key2 = a->GetId();
                        *mMap.operator_index(key2) = a;
                    } else {
                        Fn613c60(a);
                    }
                }
            }
        }
    }
    *(void* volatile*)&filter = kFilterBaseVtbl;
    if (keys.mpBegin) {
        if (((int*)keys.mpBegin)[-1]) EASTL_free(keys.mpBegin);
    }
}

// @ 0x00614280
inline void* cPollenAsset::operator new(size_t n, const char* name, int a, int b, int c, int d)
{
    return PollNew((unsigned)n, name, a, b, c, d);
}
void cAssetCache::AddAsset(u64 id, const void* data)
{
    cPollenAsset* a;
    RefPtrNI<cPollenAsset> e;
    AssetEntry* it = mMap.find(id);
    if (it != mMap.mpEnd) {
        a = it->value.p;
        if (!a) return;
        a->AddRef();
    } else {
        ResourceKey lk = { 0, 0, 0 };
        if (!GetPollinator()->mpAssetDirectory->GetLocalKey(id, &lk)) return;
        if (!GetPollinator()->mpAssetDirectory->HasAsset(id)) {
            if (!GetManager()->GetResource(&lk, 0, 0, 0, 0, 0)) return;
        }
        ResourceKey key = { lk.instanceID, 0xfd60f0c1, lk.groupID };
        RefPtr<IRefCounted> res;
        IResourceManager* mgr = GetManager();
        res = 0;
        if (mgr->GetLoadedResource(&key, &res)) {
            if (res.p)
                e = (cPollenAsset*)res.p->Cast(0xaaff1cde);
            else
                e = 0;
            a = e.p;
        } else {
            e = new ("Pollinator", 0, 0, 0, 0) cPollenAsset(id);
            a = e.p;
            a->mKey = key;
            RefPtr<cPollenAsset>* slot = mMap.operator_index(id);
            *slot = e;
        }
    }
    if (a) {
        a->SetData(((uint32_t*)data)[0], ((uint32_t*)data)[1], (void*)data);
        void* area = GetSaveArea(0x11ac19d);
        GetManager()->WriteResource(a, 0, area, 0, 0);
        GetManager()->CacheResource(a, true);
        a->Release();
    }
}

// @ 0x006144c0
bool cAssetCache::RemoveAsset(u64 id)
{
    if (mMap.find(id) != mMap.mpEnd) {
        RefPtr<cPollenAsset> e(mMap.operator_index(id)->p);
        bool r = Fn613c60(e.p);
        return r;
    }
    return false;
}

// @ 0x00614560
bool cAssetCache::ReadRecord(void* rec, cPollenAsset* obj, uint32_t unused, uint32_t type)
{
    if (type == 0xfd60f0c1 && obj) {
        cPollenAsset* a = (cPollenAsset*)obj->Cast(0xaaff1cde);
        if (a) {
            IRecord* r = (IRecord*)rec;
            if (Fn613e50(r->GetSize(), a)) {
                const ResourceKey* k = r->GetKey();
                obj->mKey = *k;
                return true;
            }
        }
    }
    return false;
}

// @ 0x006145d0
void cAssetCache::Init(cPollinator* pollinator)
{
    mpPollinator = pollinator;
    IResourceManager* mgr = GetManager();
    if (mgr) {
        PFRecordRead* f = new ("Pollinator", 0, 0, 0, 0) PFRecordRead();
        gPFRecordReadFactory = f;
        mgr->RegisterFactory(true, gPFRecordReadFactory.p, 0);
    }
    IMessageServer* ms = GetMessageServer();
    mpServer = ms;
    mpSelf = this;
    mpMessages = &kPollenMessages;
    mnMessages = 2;
    mnZero = 0;
    if (ms) {
        uint32_t i = 0;
        do {
            ms->AddListener(this, *(uint32_t*)((char*)&kPollenMessages + i));
            i += 4;
        } while (i < 8);
    }
    Fn613ab0(0x366a930d);
    LoadAll();
}

struct sAssetIdMsg { char pad0[8]; uint32_t a; char pad1[4]; uint32_t b; char pad2[4]; uint32_t c; };
struct sListMsg { int kind; IMsgObj* obj; };
struct sListObj {
    char pad0[0xc]; int count;
    char pad1[0x1c - 0x10]; const char* idText;
    char pad2[0xe8 - 0x20]; bool ready;
};
struct sListOwner { char pad[8]; struct Holder { char pad[0x60]; } holder; };
struct sAssetRecord { char pad[0x10]; uint32_t lo; uint32_t hi; };
struct sAssetList {
    int Count();   // 0x00612a50
    sAssetRecord* mpFirst;
};
struct sReply { bool ok; uint32_t pad; uint32_t lo, hi; };

// @ 0x006146c0
bool cAssetCache::HandleMessage(uint32_t id, void* msg)
{
    switch (id) {
    case 0x1dd7bda9: {
        sListMsg* m = (sListMsg*)msg;
        bool b = m->kind == 1;
        IMsgObj* mo = m->obj;
        if (mo && mo->GetTypeID() == 0x86080586) {
            sListObj* o = (sListObj*)m->obj;
            if (o->count == 3 && o->ready) {
                u64 v;
                if (sscanf(o->idText, "%I64u", &v)) {
                    uint32_t lo = (uint32_t)v;
                    sReply r;
                    if (b) {
                        uint32_t hi = (uint32_t)(v >> 32);
                        sAssetList* l = (sAssetList*)(*(char**)((char*)o + 8) + 0x60);
                        if (l->Count() == 1 && l->mpFirst->lo == lo && l->mpFirst->hi == hi) {
                            r.ok = true;
                            r.lo = lo;
                            r.hi = hi;
                            GetMessageServer()->PostMessage(0x9818ab6c, &r, 0);
                            return false;
                        }
                    }
                    r.ok = false;
                    r.lo = lo;
                    r.hi = (uint32_t)(v >> 32);
                    GetMessageServer()->PostMessage(0x9818ab6c, &r, 0);
                }
            }
        }
        break;
    }
    case 0x4249453: {
        sAssetIdMsg* m = (sAssetIdMsg*)msg;
        ResourceKey key = { m->c, m->a, m->b };
        u64 sid = (u64)-1;
        if (GetPollinator()->mpAssetDirectory->GetServerId(&key, &sid, true))
            RemoveAsset(sid);
        break;
    }
    }
    return false;
}

// ===========================================================================================
// cServerResponse
// ===========================================================================================
// @ 0x00614840
bool cServerResponse::Write(const void* pData, size_type nSize)
{
    if (mbOpen) {
        mParseStatus = XML_Parse(mpXMLParser, (const char*)pData, (int)nSize, 0);
        mnBytesRead += nSize;
        return mParseStatus == 1;
    }
    return false;
}

// @ 0x00614880
bool cServerResponse::Close()
{
    if (mbOpen) {
        mParseStatus = XML_Parse(mpXMLParser, 0, 0, 1);
        XML_ParserFree(mpXMLParser);
        mbOpen = false;
        return mParseStatus == 1;
    }
    return true;
}

// @ 0x006148c0
int cServerResponse::GetAccessFlags() const
{
    return mbOpen ? 2 : 0;
}

// @ 0x006148d0
int cServerResponse::GetState() const
{
    if (mbOpen) {
        if (mParseStatus != 1) return XML_GetErrorCode(mpXMLParser);
        return 0;
    }
    return -2;
}

// @ 0x00614900
off_type cServerResponse::GetPosition(int positionType) const
{
    switch (positionType) {
    case 0: return mnBytesRead;
    case 1: return 0;
    case 2: return -1;
    }
    return -1;
}

// @ 0x00614950
int string16::compare_out(const wchar_t* p) const
{
    const wchar_t* e = p + CharStrlen(p);
    return StringCompare(mpBegin, mpEnd, p, e);
}

// @ 0x00614990
__declspec(noinline) StrPair::StrPair(const StrPair& x) : first(x.first), second(x.second)
{
}

// @ 0x00614a30
HandlerPair* lower_bound(HandlerPair* first, HandlerPair* last, const wchar_t* const& value, char16less compare)
{
    int nLength = (int)(last - first);
    while (nLength > 0) {
        const int nLength2 = nLength >> 1;
        HandlerPair* const middle = first + nLength2;
        if (compare(middle->first, value)) {
            first = middle + 1;
            nLength -= nLength2 + 1;
        } else
            nLength = nLength2;
    }
    return first;
}

extern const wchar_t kSuccessText[];   // 0x013fc0d4 L"Success"
extern const wchar_t kFailureText[];   // 0x013fc0c4 L"Failure"
// @ 0x00614ab0
void cServerResponse::GetStatus()
{
    mCharacterData.erase(0, mCharacterData.find_first_not_of(L" \t\n\f\r", 0));
    if (mCharacterData.compare(kSuccessText) == 0) {
        mnReturnCode = 0;
        return;
    }
    if (mCharacterData.compare(kFailureText) != 0)
        mnReturnCode = 1;
}

// @ 0x00614c00
StrPair::~StrPair() {}

// @ 0x00614c40
void HandlerMap::DoReallocate(size_type n)
{
    if (n > (size_type)(mpCapacity - mpBegin)) {
        HandlerPair* p = n ? (HandlerPair*)EASTL_alloc(n * 16, "Editor", 0, 0, "UTFKernel\\EASTL\\vector.h", 0xd1) : 0;
        extern void MoveRange(HandlerPair*, HandlerPair*, HandlerPair*);   // 0x00c7ea30
        MoveRange(mpBegin, mpEnd, p);
        if (mpBegin) EASTL_free(mpBegin);
        const int sz = (int)(mpEnd - mpBegin);
        mpBegin = p;
        mpEnd = p + sz;
        mpCapacity = p + n;
    }
}

// @ 0x00614cc0
StrPair MakeStrPair(string16 a, string16 b)
{
    return StrPair(a, b);
}

// @ 0x00614d20
HandlerRange HandlerMap::equal_range(const wchar_t* const& k)
{
    HandlerRange r;
    HandlerPair* it = lower_bound(mpBegin, mpEnd, k, mCompare);
    if (it != mpEnd && !mCompare(k, it->first)) {
        r.first = it;
        r.second = it + 1;
    } else {
        r.first = it;
        r.second = it;
    }
    return r;
}

// @ 0x00614da0
void cServerResponse::CharacterData(cServerResponse* self, const wchar_t* s, int len)
{
    self->mCharacterData.append(s, s + len);
}

// @ 0x00614dc0
StrMapIter StrMap::DoInsertValueImpl(RBNode* pNodeParent, const StrPair& value, bool bForceToLeft)
{
    less16 mCompare;
    int side;
    if (bForceToLeft || pNodeParent == &mAnchor ||
        mCompare(value.first, ((StrNode*)pNodeParent)->mValue.first))
        side = 0;
    else
        side = 1;
    StrNode* n = (StrNode*)EASTL_alloc(0x30, "Editor", 0, 0, "UTFKernel\\EASTL\\rbtree.h", 0xd1);
    if (&n->mValue) new (&n->mValue) StrPair(value);
    RBTreeInsert(n, pNodeParent, &mAnchor, side);
    ++mnSize;
    StrMapIter it = { n };
    return it;
}

// @ 0x00614e50
const wchar_t* cServerResponse::GetField(const wchar_t* name)
{
    StrNode* n;
    {
        string16 key;
        key.RangeInitialize(name);
        StrMapIter it;
        n = mFieldDict.find(&it, key)->mpNode;
    }
    if ((RBNode*)n != &mFieldDict.mAnchor)
        return n->mValue.second.mpBegin;
    return 0;
}

// @ 0x00614ed0
void cServerResponse::StartElement(cServerResponse* self, const wchar_t* name)
{
    self->mCharacterData.resize(0);
    HandlerRange r = gElementHandlers.equal_range(name);
    if (r.first != r.second && r.first != gElementHandlers.mpEnd) {
        typedef void (__thiscall *Fn)(void*);
        ((Fn)r.first->second.fn)((char*)self + r.first->second.adj);
    }
}
