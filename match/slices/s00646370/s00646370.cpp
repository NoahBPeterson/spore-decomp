// Slice s00646370 -- swatch/community editor helpers.
// Module flags: /O2 /MD /Gy /TP /EHsc (scalar integer + EASTL, no SSE).
#include "types.h"

// ---------------------------------------------------------------------------
// Runtime helpers (relocations are masked, declarations only need the right
// calling convention / argument layout).
// ---------------------------------------------------------------------------
extern "C" void  __cdecl eastl_dealloc(void* p);                    // 0x00f47380
extern "C" void* __cdecl eastl_alloc(uint32_t n, const char* name, int a, int b,
                                     const char* file, int line);    // 0x00f473a0

// Spore's custom EASTL allocator keeps a header word in front of each block;
// a block is only released when that word is non-zero.
inline void FreeChecked(void* p) {
    if (p && ((uint32_t*)p)[-1])
        eastl_dealloc(p);
}

struct Key8 { uint32_t first; uint32_t second; };
struct InsertResult { void* node; void* bucket; bool inserted; };

// ---------------------------------------------------------------------------
// @ 0x00646d70  eastl::vector<T,sp_vector_allocator>::DoDestroyValues
// ---------------------------------------------------------------------------
// @ 0x00646d70
void __stdcall sub_646d70(uint8_t* first, uint8_t* last) {
    for (; first < last; first += 0x34) {
        FreeChecked(*(void**)(first + 0x20));
        FreeChecked(*(void**)(first + 8));
    }
}

// ---------------------------------------------------------------------------
// @ 0x00646fc0  eastl::vector<T (0x14 bytes)>::reserve
// ---------------------------------------------------------------------------
extern "C" void* __cdecl uninit_copy14(void* first, void* last, void* dest);    // 0x00645450
extern "C" void* __cdecl uninit_destroy14(void* first, void* last, void* dest); // 0x006454c0

class Vec14 {
public:
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCapacity;
    void reserve(uint32_t n);
};

// @ 0x00646fc0
void Vec14::reserve(uint32_t n) {
    if (n > (uint32_t)((mpCapacity - mpBegin) / 0x14)) {
        uint8_t* pNewData;
        if (n)
            pNewData = (uint8_t*)eastl_alloc(n * 0x14, "Editor", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        else
            pNewData = 0;
        uint8_t* const pOldEnd = mpEnd;
        uint8_t* const pOldBegin = mpBegin;
        uninit_copy14(pOldBegin, pOldEnd, pNewData);
        uninit_destroy14(pOldBegin, pOldEnd, pNewData);
        if (mpBegin)
            eastl_dealloc(mpBegin);
        const uint32_t nPrevSize = (uint32_t)((mpEnd - mpBegin) / 0x14);
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize * 0x14;
        mpCapacity = pNewData + n * 0x14;
    }
}

// ---------------------------------------------------------------------------
// Hashtable container stubs (0x20 / 0x24 bytes so the owner's member offsets
// line up with the disassembly: +0xf8, +0x118, +0x138, +0x15c).
// ---------------------------------------------------------------------------
struct IRef {
    virtual void AddRef();
    virtual void Release();
};
struct AutoRef {
    IRef* p;
    AutoRef() : p(0) {}
    AutoRef(IRef* x) : p(x) { if (p) p->AddRef(); }
    AutoRef& operator=(IRef* x) { if (x) x->AddRef(); p = x; return *this; }
    ~AutoRef() { if (p) p->Release(); }
};
struct RefPair {
    uint32_t first;
    IRef* second;
    RefPair() {}
};
struct EmptyTag {};

struct Container0F8 {
    uint8_t mData[0x20];
    InsertResult find_insert(const Key8& key, EmptyTag tag);
};
struct Container118 {
    uint8_t mData[0x20];
    InsertResult find_insert(const Key8& key, EmptyTag tag);
};
struct Container138 {
    uint8_t mData[0x24];
    InsertResult insert(const RefPair& key, EmptyTag tag);
};
struct Container15C {
    uint8_t mData[0x24];
    InsertResult insert(const RefPair& key, EmptyTag tag);
};

struct Owner {
    uint8_t pad0[0xf8];
    Container0F8 m0F8;      // +0xf8
    Container118 m118;      // +0x118
    Container138 m138;      // +0x138
    Container15C m15C;      // +0x15c

    bool Insert0F8(uint32_t a, uint32_t b);
    bool Insert118(uint32_t a, uint32_t b);
    bool Insert138(uint32_t a, IRef* b);
    bool Insert15C(uint32_t a, IRef* b);
};

// @ 0x00646dc0
bool Owner::Insert118(uint32_t a, uint32_t b) {
    Key8 key; key.first = a; key.second = b;
    InsertResult r = m118.find_insert(key, EmptyTag());
    return r.inserted;
}

// @ 0x00646e00
bool Owner::Insert0F8(uint32_t a, uint32_t b) {
    Key8 key; key.first = a; key.second = b;
    InsertResult r = m0F8.find_insert(key, EmptyTag());
    return r.inserted;
}

// @ 0x00646e40
bool Owner::Insert138(uint32_t a, IRef* b) {
    if (b) b->AddRef();
    RefPair key; key.first = a; key.second = b;
    if (b) b->AddRef();
    InsertResult r = m138.insert(key, EmptyTag());
    if (key.second) key.second->Release();
    if (b) b->Release();
    return r.inserted;
}

// @ 0x00646ec0
bool Owner::Insert15C(uint32_t a, IRef* b) {
    if (b) b->AddRef();
    RefPair key; key.first = a; key.second = b;
    if (b) b->AddRef();
    InsertResult r = m15C.insert(key, EmptyTag());
    if (key.second) key.second->Release();
    if (b) b->Release();
    return r.inserted;
}

// ---------------------------------------------------------------------------
// @ 0x00646d10  map find (template instantiation)
// ---------------------------------------------------------------------------
struct Elem20 {
    uint32_t f00, f04, f08, f0c, f10, f14, f18, f1c;
};
struct OutPair { void* first; void* second; };
struct MapFindSelf {
    Elem20* mBegin;     // +0
    Elem20* mEnd;       // +4
    uint32_t mField8;   // +8
    uint32_t mFieldC;   // +0xc
    uint32_t mField10;  // +0x10
    uint8_t  mFlag14;   // +0x14

    void Find(OutPair* out, const OutPair* key);
};
extern "C" Elem20* __cdecl lower_bound20(Elem20* first, Elem20* last, const OutPair* key, uint8_t flag); // 0x00646030

// @ 0x00646d10
void MapFindSelf::Find(OutPair* out, const OutPair* key) {
    Elem20* const last = mEnd;
    Elem20* p = lower_bound20(mBegin, last, key, mFlag14);
    if (p != last) {
        const uint32_t* k = (const uint32_t*)key;
        bool less = k[0] < p->f00;
        if ((k[0] == p->f00) && (less = k[2] < p->f08, k[2] == p->f08))
            less = k[1] < p->f04;
        if (!less) {
            out->first = p;
            out->second = p + 1;
            return;
        }
    }
    out->first = p;
    out->second = p;
}

// ---------------------------------------------------------------------------
// @ 0x00646f40  find-or-insert returning a pointer just past the key
// ---------------------------------------------------------------------------
struct MapFindInsert {
    uint32_t mField0;       // +0
    void* mpBuckets;        // +4
    uint32_t mBucketCount;  // +8
    uint32_t mCountC;       // +0xc
    uint32_t mField10;      // +0x10

    void find(InsertResult* out, const uint32_t* key);
    void insert(InsertResult* out, const uint32_t* key, EmptyTag tag);
    uint32_t* FindOrInsert(uint32_t* key);
};

// @ 0x00646f40
uint32_t* MapFindInsert::FindOrInsert(uint32_t* key) {
    InsertResult r;
    find(&r, key);
    if ((uint32_t*)r.node != ((uint32_t**)mpBuckets)[mBucketCount])
        return (uint32_t*)r.node + 1;
    uint32_t keyCopy = *key;
    insert(&r, &keyCopy, EmptyTag());
    return (uint32_t*)r.node + 1;
}

// ---------------------------------------------------------------------------
// @ 0x00646370  clone a creation (model) asset into the save area
//
// Takes a ResourceKey by value (A1..A3), an out key, an int stored into the cloned model resource
// and a bool that selects whether the new metadata records the source key as its parent.
// Generates a fresh instance id, privately loads the model, re-keys and writes it to the save
// database, clones the .pollen_metadata record, copies the .png thumbnails and notifies listeners.
// Types come from the ModAPI headers (Resource::IResourceManager / Database / App::cIDGenerator /
// Pollinator::cAssetMetadata); retail vtable slots are checked against the disassembly.
// ---------------------------------------------------------------------------
void* __cdecl operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                           const char* file, int line);                         // 0x00f473a0

struct Key { uint32_t instance, type, group; };

struct ResObj {                       // Resource::ResourceObject
    virtual int AddRef();             // +0x00
    virtual int Release();            // +0x04
    virtual int v2();                 // +0x08
    virtual void* Cast(uint32_t t);   // +0x0c
    uint32_t mRefCount;               // +0x04 (data)
    Key mKey;                         // +0x08
};
struct CastTarget3c609f8 { uint32_t pad[6]; int mField18; };   // type 0x03c609f8 (model base)

template <class T> struct Ref {
    T* p;
    Ref() : p(0) {}
    Ref(T* x) : p(x) { if (p) p->AddRef(); }
    ~Ref() { if (p) p->Release(); }
    void Reset() { T* t = p; if (t) { p = 0; t->Release(); } }
};

struct RecordInfo { uint32_t chunkOffset, compressedSize, memorySize; int16_t flags; bool isSaved; };

struct Database {                     // Resource::Database
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0A(); virtual void s0B();
    virtual void s0C();
    virtual bool OpenRecord(const Key& name, void* ppDst, uint32_t access, uint32_t cd,
                            bool arg10, RecordInfo* pInfo);     // +0x34
};

struct IResourceManager {
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual bool GetResource(const Key& name, Ref<ResObj>* ppDst, void* factoryData,
                             Database* pDatabase, void* pFactory, const Key* pCacheName);   // +0x0c
    virtual void s04(); virtual void s05(); virtual void s06();
    virtual bool GetPrivateResource(const Key& name, Ref<ResObj>* ppDst, void* factoryData,
                                    Database* pDatabase, void* pFactory, const Key* pCacheName);  // +0x1c
    virtual bool WriteResource(ResObj* pResource, void* factoryData, Database* pDatabase,
                               void* pFactory, const Key* pNameKey);   // +0x20
    virtual void s09(); virtual void s0A(); virtual void s0B(); virtual void s0C();
    virtual void s0D(); virtual void s0E(); virtual void s0F(); virtual void s10();
    virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15();
    virtual Database* FindDatabase(const Key& name);   // +0x58
};
IResourceManager* __cdecl GetManager();                // 0x0067dcd0 (EA::ResourceMan::GetManager)

struct cIDGenerator {                                  // App::cIDGenerator
    virtual void s00();
    virtual void Generate(Key& dst, uint32_t typeID, uint32_t poolID, uint32_t highBits,
                          uint32_t lowBits8, uint32_t lowBits0);   // +0x04
};
cIDGenerator* __cdecl GetIDGenerator();                // 0x0067de60 (SP::IDGenerator)

struct cAssetMetadata : ResObj {                       // Pollinator::cAssetMetadata, 0xd8 bytes
    uint32_t pad[(0xd8 - 0x14) / 4];
    cAssetMetadata();                                  // 0x00550450
    void GetTagsString(void* pDstString16);            // 0x00550cf0
    const wchar_t* GetDescription();                   // 0x005508c0 (mDescription.c_str(), no args)
    const wchar_t* GetName();                          // 0x00414e10 (mName.c_str(), no args)
    bool Set(const Key& assetKey, const wchar_t* name, const wchar_t* description,
             const wchar_t* tags, const Key& parentKey, bool isPollinated);  // 0x00551240 (ret 0x18)
};
struct String16 {                                      // eastl::basic_string<wchar_t>, 16 bytes
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator;
    void DeallocateSelf();                             // 0x00933960
};
extern wchar_t gEmptyString16[];                       // 0x01667bac

struct ImgObj { void* mPixels; uint32_t flags; uint32_t mRefCount;
                void* GetPixels();                     // 0x0046f260
};
struct ImgPtr {                                        // atomic refcounted pointer, count at +8
    ImgObj* p;
    ImgPtr(ImgObj* x);                                 // 0x005725b0
    ImgPtr& operator=(ImgObj* x);                      // 0x00576650
    ~ImgPtr();                                         // 0x00576620
};
struct ThumbService {                                  // object returned by 0x0067dd60
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06();
    virtual ImgObj* LoadImage(Key k, int mode);        // +0x1c
};
ThumbService* __cdecl GetThumbService();               // 0x0067dd60

struct cImportExport {                                 // SP::Thumbnail::cImportExport singleton
    bool CreateExportThumb(ResObj* model, void* pixels, Database* saveDb, int zero, bool flag);   // 0x005fa8d0 (ret 0x14)
};
cImportExport* __cdecl GetImportExport();              // 0x005f7930

struct cSPMemPool {
    void* LockedAlloc(uint32_t size, int a, int b, int c, int d, int e);   // 0x009289f0 (ret 0x18)
    void  Free(void* p);                                                  // 0x009276c0 (ret 4)
};
extern cSPMemPool* g_pSPMemPool;                       // 0x016c8b44

struct ChangeNotifier {                                // object returned by 0x00401010
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0A(); virtual void s0B();
    virtual void s0C(); virtual void s0D(); virtual void s0E(); virtual void s0F();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
    virtual void OnAssetCloned(const Key* oldKey, const Key* newKey);   // +0x50
};
ChangeNotifier* __cdecl GetChangeNotifier();           // 0x00401010
struct MessageServer {                                 // object returned by SP::MessageServer
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04();
    virtual void PostMessage(uint32_t id, const Key* data, int arg);    // +0x14
};
MessageServer* __cdecl GetMessageServer();             // 0x0067dcc0

Database* __cdecl GetSaveArea(uint32_t id);            // 0x006b1f90 (SP::GetSaveArea)
void __cdecl MarkResourceDirty(ResObj* r);             // 0x006ad010
bool __cdecl SetAssetData(uint32_t typeID, bool flag); // 0x004bbe20 (SP::cSPAssetDataList::SetAssetData)
int  __cdecl GetModelCategory(const Key* key);         // 0x00552300
int  __cdecl FindModelPart(const Key* key, uint32_t hash);   // 0x00556140
void __cdecl SummarizeVehiclePart(Key* newKey, int part);    // 0x00555f70 (SP::cVehicleModelSummarizer)
uint32_t __cdecl ReadRecordData(Database* db, const Key* key, void* buf, uint32_t size, int a, int b);  // 0x008ddb00
bool     __cdecl WriteRecordData(Database* db, const Key* key, void* buf, uint32_t size, int a);        // 0x008ddb90

static __forceinline void SummarizePart(const Key* key, Key* newKey, uint32_t hash) {
    if (FindModelPart(key, hash))
        SummarizeVehiclePart(newKey, FindModelPart(key, hash));
}

// @ 0x00646370
bool __stdcall CloneModelAsset(Key key, Key* pOutKey, int size, bool bKeepParent) {
    uint32_t dbId;
    switch (key.type) {
    case 0x366a930d: dbId = 0x86ca01c9; break;
    case 0x2399be55: dbId = 0x11ac19a;  break;
    case 0x24682294: dbId = 0x11ac19b;  break;
    case 0x2b978c46: dbId = 0x11ac199;  break;
    case 0x3d97a8e4: dbId = 0x90368ea3; break;
    case 0x476a98c7: dbId = 0x90368ea2; break;
    default: return false;
    }
    Database* pSave = GetSaveArea(dbId);
    uint32_t group = key.group;
    Key newKey; newKey.instance = 0; newKey.type = 0; newKey.group = 0;
    if ((group & 0xc0000000) != 0x40000000 || dbId == 0)
        return false;

    cIDGenerator* gen = GetIDGenerator();
    gen->Generate(newKey, key.type, (group >> 16) & 0xff, (group >> 24) & 0x1f,
                  (group >> 8) & 0xff, 0);
    Ref<ResObj> spModel;
    IResourceManager* mgr = GetManager();
    spModel.Reset();
    if (!mgr->GetPrivateResource(key, &spModel, 0, 0, 0, 0))
        return false;

    // Re-key the privately loaded model and write it into the save area.
    spModel.p->mKey = newKey;
    Key nameKey = newKey;
    CastTarget3c609f8* pBase = (CastTarget3c609f8*)spModel.p->Cast(0x3c609f8);
    if (pBase) {
        if (size != -1)
            pBase->mField18 = size;
        nameKey.type = 0x1a99b06b;
    }
    MarkResourceDirty(spModel.p);
    GetManager()->WriteResource(spModel.p, 0, pSave, 0, &nameKey);

    // Clone the .pollen_metadata record next to the model.
    Key metaKey = key;
    metaKey.type = 0x30bdee3;
    bool bMetaOK = false;
    Ref<ResObj> spMeta;
    mgr = GetManager();
    spMeta.Reset();
    if (mgr->GetResource(metaKey, &spMeta, 0, 0, 0, 0)) {
        cAssetMetadata* pOld = spMeta.p ? (cAssetMetadata*)spMeta.p->Cast(0x30bdee3) : 0;
        Ref<cAssetMetadata> spNew(new ("Pollinator", 0, 0, 0, 0) cAssetMetadata());
        String16 tags;
        tags.mpBegin = gEmptyString16; tags.mpEnd = gEmptyString16; tags.mpCapacity = gEmptyString16 + 1;
        pOld->GetTagsString(&tags);
        Key parentKey;
        if (bKeepParent) { parentKey = key; } else { parentKey.instance = 0; parentKey.type = 0; parentKey.group = 0; }
        spNew.p->Set(newKey, pOld->GetName(), pOld->GetDescription(), tags.mpBegin, parentKey, false);
        MarkResourceDirty(spNew.p);
        bMetaOK = GetManager()->WriteResource(spNew.p, 0, pSave, 0, 0);
        tags.DeallocateSelf();
    }

    // Copy the .png thumbnails (png type 0x2f7d0004) to the new key.
    Key pngKey = key; pngKey.type = 0x2f7d0004;
    Database* pPngDb = GetManager()->FindDatabase(pngKey);
    Key pngNew = newKey; pngNew.type = 0x2f7d0004;
    bool bThumb = false;
    if (!pPngDb || !pSave)
        return false;

    {
    ImgPtr img(GetThumbService()->LoadImage(pngKey, 2));
    void* pixels = img.p->GetPixels();
    if (img.p && pixels) {
        bool bFlag = !SetAssetData(key.type, false);
        bThumb = GetImportExport()->CreateExportThumb(spModel.p, pixels, pSave, 0, bFlag);
    }
    img = 0;
    if (bThumb) {
        int count = 1;
        if (key.type == 0x366a930d) count = 4;
        for (int i = 0; i < count; ++i) {
            RecordInfo info;
            pngKey.group = (pngKey.group & 0xffffff00) | ((i + 1) & 0xff);
            pngNew.group = (pngNew.group & 0xffffff00) | ((i + 1) & 0xff);
            bool opened = pPngDb->OpenRecord(pngKey, 0, 1, 6, false, &info);
            if (!opened) {
                if (i != 0) continue;
                pngKey.group &= 0xffffff00;
                if (!pPngDb->OpenRecord(pngKey, 0, 1, 6, false, &info)) continue;
            }
            if (info.compressedSize == (uint32_t)-1) continue;
            void* buf = g_pSPMemPool->LockedAlloc(info.compressedSize, 0, 0, 0, 0, 0);
            uint32_t n = ReadRecordData(pPngDb, &pngKey, buf, info.compressedSize, 1, 0);
            if (n == info.compressedSize)
                bThumb = WriteRecordData(pSave, &pngNew, buf, n, 1);
            if (buf)
                g_pSPMemPool->Free(buf);
        }
    }
    }
    if (!bThumb || !bMetaOK)
        return false;

    if (newKey.type == 0x2b978c46 && GetModelCategory(&key) == 1) {
        SummarizePart(&key, &newKey, 0xa426730b);
        SummarizePart(&key, &newKey, 0xad56080c);
        SummarizePart(&key, &newKey, 0xf71fa311);
        SummarizePart(&key, &newKey, 0xbeb528cb);
        SummarizePart(&key, &newKey, 0x2db6dad3);
    }
    if (SetAssetData(newKey.type, false))
        GetChangeNotifier()->OnAssetCloned(&key, &newKey);
    GetMessageServer()->PostMessage(0xca665fa7, &newKey, 0);
    *pOutKey = newKey;
    return true;
}

// @ 0x00646ae0
void __fastcall sub_646ae0(void*) {
}
