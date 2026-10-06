// Slice s00712e10: SP::cMaterialManager / cMaterialScriptState constructors, destructors, the
// compiled-state map lookup, material registration, ReadExternalReferences and the
// shader-compile thunk.
// flags: /O2 /MD /Gy /EHsc /TP /GS-  (the constructors need /arch:SSE for the movss constants)
#include <new>
#include <string.h>
#include <intrin.h>
#include "types.h"

// ---------------------------------------------------------------------------------------------
// externs (addresses are relocation-masked; only the calling convention and arguments matter)
// ---------------------------------------------------------------------------------------------
void __cdecl EastlFree(void* p);                         // 0x00F47380 operator delete[]
void* __cdecl GetMaterialManager();                      // 0x0067DD70
void* __cdecl GetResourceManager();                      // 0x0067DCD0 EA::ResourceMan::GetManager
void* __cdecl GetImageFactory();                         // 0x0067DD60
int __cdecl ReadInt32(void* stream, int* out, int count, int endian);  // 0x0093A780
int __cdecl ReadExact(void* stream, void* buf, int size);              // 0x0093A6C0
extern uint32_t gGroupMaterialsA;                        // 0x01535F64
extern uint32_t gGroupMaterialsB;                        // 0x01535F60
extern void* gEmptyBucketArray[2];                       // 0x0154DF28
extern char vtblMaterialManagerA[];                      // 0x0140C908
extern char vtblMaterialManagerB[];                      // 0x0140C904
extern char vtblMaterialManagerBaseA[];                  // 0x013EB938
extern char vtblMaterialManagerBaseB[];                  // 0x013EF094
extern char gEmptyStringChars[];                         // 0x01667BAC (empty string literal)
extern char gEmptyStringCharsEnd[];                      // 0x01667BAD
extern const void* gMutexParams;                         // 0x0140C860

struct Mutex {
    void Lock(const void* params);         // 0x009221B0
    void Unlock();                         // 0x00922270
    void Construct(int a, int b);          // 0x00922200 (Mutex::Mutex)
    void Destroy();                        // 0x00922130 (Mutex::~Mutex)
};

struct Stopwatch {
    void Construct(int a, int b);          // 0x00093A50 (Stopwatch::Stopwatch)
};

// eastl hashtable header (the part used here). bucket count 1 and the shared empty array
// mean "empty"; the policy constants are the global floats.
struct HashTable {
    uint32_t pad0;
    void** mpBuckets;                      // +4
    uint32_t mnBuckets;                    // +8
    uint32_t mnElements;                   // +0xC
    float mfMaxLoad;                       // +0x10
    float mfGrowth;                        // +0x14
    uint32_t mnNextResize;                 // +0x18
    uint32_t pad1c;

    void InitEmpty()
    {
        mpBuckets = gEmptyBucketArray;
        mnBuckets = 1;
        mnElements = 0;
        mfMaxLoad = 1.0f;
        mfGrowth = 2.0f;
        mnNextResize = 0;
    }

    // distinct DoFreeNodes instantiations (void** buckets, uint count)
    void FreeNodes7112C0(void** a, uint32_t n);
    void FreeNodes70FF50(void** a, uint32_t n);
    void FreeNodes70FD00(void** a, uint32_t n);
    void FreeNodes712B20(void** a, uint32_t n);
    void FreeNodes6A85B0(void** a, uint32_t n);
    void FreeNodes693230(void** a, uint32_t n);
    void FreeNodes712320(void** a, uint32_t n);
};

struct TriWord {                           // small vector-like members destroyed without args
    uint32_t a, b, c;
    void Destroy70F390();
    void Destroy70F320();
};

// AutoRefCount-style intrusive pointer slots for materials/textures
struct IRefCounted {
    virtual void AddRef();                 // slot 0
    virtual void Release();                // slot 1
};

struct ResourceObject {                    // object cached at cMaterialManager+0x204
    virtual void AddRef();                 // slot 0
    virtual void Release();                // slot 1
    virtual void Slot2();
    virtual void* QueryResource(uint32_t type);   // slot 3 (+0xC)
    char pad[0x10];
    void* mpArena;                         // +0x18
};

struct ResourceManagerStub {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    // slot 7 (+0x1C)
    virtual bool GetResource(const void* key, ResourceObject** out, int a, void* db, int b, int c);
};

struct ImageFactoryStub {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    // slot 8 (+0x20)
    virtual void* GetImage(int a, int b, int c);
};

struct StreamHolder {                      // result of the database lookup of the second key
    virtual void s0(); virtual void s1();
    virtual void Release();                // slot 2 (+8)
    virtual void s3(); virtual void s4(); virtual void s5();
    virtual void* GetStream();             // slot 6 (+0x18)
    virtual void s7(); virtual void s8();
    virtual void Close();                  // slot 9 (+0x24)
};

struct ResourceDatabaseStub {              // parameter of the loader (slot 13 / +0x34)
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12();
    virtual bool GetStream(const void* key, StreamHolder** out, int a, int b, int c, int d);
};

struct ResourceKey {
    uint32_t instance;
    uint32_t type;
    uint32_t group;
};

// holder of one exported-object lookup (EA::RW arena)
struct ExportElem {
    int a, b;
    ExportElem();                          // 0x006C0FA0
    ~ExportElem();                         // 0x00C2E4E0
};
struct ExportedObject {
    int type;                              // 0x2000B = texture
    int value;
    int pad8, padC, pad10, pad14;
    ExportElem elems[4];
};
void __stdcall GetExportedObjectByIndex(void* arena, int index, ExportedObject* out); // 0x011E28E0

struct ImageRef {                          // AutoRefCount<cTextureInstance> slot
    void* mpObject;
    void SetFromResource(void* res);       // 0x00576650 GetImageResource
};

struct TexVec {                            // vector<AutoRefCount<cTextureInstance>> at entry+0x20
    ImageRef* mpBegin;
    ImageRef* mpEnd;
    void resize(uint32_t n);               // 0x00711220
};

struct MaterialEntry;
struct EntryRef {                          // AutoRefCount<cMaterialInternal> temp
    MaterialEntry* mp;
    inline EntryRef(MaterialEntry* p);
    inline ~EntryRef();
};

struct MaterialEntry {                     // SP::cMaterialInternal (the used part)
    uint8_t mnFlags;                       // +0
    uint8_t pad1[3];
    uint32_t mFlags[4];                    // +4
    int mnRefCount;                        // +0x14
    uint32_t mnId;                         // +0x18
    uint32_t mnExternalId;                 // +0x1C
    TexVec mTextures;                      // +0x20
    void Unregister();                     // 0x00711380 UnregisterMaterial
};

inline EntryRef::EntryRef(MaterialEntry* p)
{
    mp = p;
    if (p)
        p->mnRefCount++;
}

inline EntryRef::~EntryRef()
{
    if (mp && mp->mnRefCount > 1)
        mp->mnRefCount--;
}

struct MaterialMap : HashTable {
    MaterialEntry* operator_index(const uint32_t* key);   // 0x007129E0 hash_map::operator[]
};

struct StateIdMap : HashTable {
    void find(uint32_t** out, const uint32_t* key);       // 0x00645ED0 hashtable::find
    int* operator_index(const uint32_t* key);             // 0x0070F9D0
};

struct EntryVec {                          // fixed vector of AutoRefCount<cMaterialInternal> at +0x244
    MaterialEntry** mpBegin;
    MaterialEntry** mpEnd;
    MaterialEntry** mpCapacity;
    void DoDestroy(MaterialEntry** first, MaterialEntry** last);          // 0x0070E890
    void DoAssignFromIterator(MaterialEntry** pos, EntryRef* value);      // 0x007103E0

    inline void push_back(EntryRef& v)
    {
        MaterialEntry** pos = mpEnd;
        if (pos < mpCapacity) {
            mpEnd = pos + 1;
            if (pos) {
                *pos = v.mp;
                v.mp->mnRefCount++;
            }
        } else {
            DoAssignFromIterator(pos, &v);
        }
    }
};

struct PtrVec {                            // fixed vector<void*> at +0x1d8
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    void** mpLocal;                        // +0x10 (address of the inline buffer)
    void DoDestroy(void** first, void** last);   // 0x0070F520
};

// ---------------------------------------------------------------------------------------------
// cMaterialScriptState
// ---------------------------------------------------------------------------------------------
struct cMaterialScriptState {
    uint32_t pad0;                         // +0
    ResourceObject* mInvalidTexture;       // +4
    HashTable mMap8;                       // +8
    HashTable mMap28;                      // +0x28
    HashTable mMap48;                      // +0x48
    HashTable mMap68;                      // +0x68
    TriWord m88;                           // +0x88
    uint32_t pad94, pad98;
    HashTable mMap9C;                      // +0x9c
    HashTable mMapBC;                      // +0xbc
    TriWord mDC;                           // +0xdc
    uint32_t padE8, padEC;
    HashTable mMapF0;                      // +0xf0
    char* mpLabelBegin;                    // +0x110
    char* mpLabelEnd;                      // +0x114
    char* mpLabelCapacity;                 // +0x118
    char pad11C[0x20];
    HashTable mMap13C;                     // +0x13c
    uint32_t pad15C[2];

    cMaterialScriptState();                // 0x007138F0
    ~cMaterialScriptState();               // 0x00713560
};

// @ 0x007138F0
cMaterialScriptState::cMaterialScriptState()
{
    pad0 = 0;
    mInvalidTexture = 0;
    mMap8.InitEmpty();
    mMap28.InitEmpty();
    mMap48.InitEmpty();
    mMap68.InitEmpty();
    m88.a = 0;
    m88.b = 0;
    m88.c = 0;
    mMap9C.InitEmpty();
    mMapBC.InitEmpty();
    mDC.a = 0;
    mDC.b = 0;
    mDC.c = 0;
    mMapF0.InitEmpty();
    mpLabelBegin = gEmptyStringChars;
    mpLabelEnd = gEmptyStringChars;
    mpLabelCapacity = gEmptyStringCharsEnd;
    mMap13C.InitEmpty();
}

// @ 0x00713560
cMaterialScriptState::~cMaterialScriptState()
{
    mMap13C.FreeNodes7112C0(mMap13C.mpBuckets, mMap13C.mnBuckets);
    mMap13C.mnElements = 0;
    if (mMap13C.mnBuckets > 1)
        EastlFree(mMap13C.mpBuckets);

    if ((uint32_t)(mpLabelCapacity - mpLabelBegin) > 1 && mpLabelBegin)
        EastlFree(mpLabelBegin);

    mMapF0.FreeNodes70FF50(mMapF0.mpBuckets, mMapF0.mnBuckets);
    mMapF0.mnElements = 0;
    if (mMapF0.mnBuckets > 1)
        EastlFree(mMapF0.mpBuckets);

    mDC.Destroy70F390();

    mMapBC.FreeNodes70FD00(mMapBC.mpBuckets, mMapBC.mnBuckets);
    mMapBC.mnElements = 0;
    if (mMapBC.mnBuckets > 1)
        EastlFree(mMapBC.mpBuckets);

    mMap9C.FreeNodes712B20(mMap9C.mpBuckets, mMap9C.mnBuckets);
    mMap9C.mnElements = 0;
    if (mMap9C.mnBuckets > 1)
        EastlFree(mMap9C.mpBuckets);

    m88.Destroy70F320();

    mMap68.FreeNodes6A85B0(mMap68.mpBuckets, mMap68.mnBuckets);
    mMap68.mnElements = 0;
    if (mMap68.mnBuckets > 1)
        EastlFree(mMap68.mpBuckets);

    mMap48.FreeNodes6A85B0(mMap48.mpBuckets, mMap48.mnBuckets);
    mMap48.mnElements = 0;
    if (mMap48.mnBuckets > 1)
        EastlFree(mMap48.mpBuckets);

    mMap28.FreeNodes6A85B0(mMap28.mpBuckets, mMap28.mnBuckets);
    mMap28.mnElements = 0;
    if (mMap28.mnBuckets > 1)
        EastlFree(mMap28.mpBuckets);

    mMap8.FreeNodes6A85B0(mMap8.mpBuckets, mMap8.mnBuckets);
    mMap8.mnElements = 0;
    if (mMap8.mnBuckets > 1)
        EastlFree(mMap8.mpBuckets);

    // AutoRefCount<> release of the invalid texture (atomic decrement, floor at zero)
    ResourceObject* tex = mInvalidTexture;
    if (tex) {
        volatile long* rc = (volatile long*)((char*)tex + 8);
        _InterlockedExchangeAdd(rc, -1);
        long v = _InterlockedExchangeAdd(rc, 0);
        if (v < 1)
            _InterlockedExchangeAdd(rc, 1);
        else
            _InterlockedExchangeAdd(rc, 0);
    }
}

// ---------------------------------------------------------------------------------------------
// cMaterialManager
// ---------------------------------------------------------------------------------------------
struct cMaterialManager {
    void* mpVtblA;                         // +0
    void* mpVtblB;                         // +4
    uint32_t pad8;                         // +8
    IRefCounted* mpListener;               // +0xC
    cMaterialScriptState mScriptState;     // +0x10
    MaterialMap mMaterialsMap;             // +0x174
    StateIdMap mCompiledStateToIDMap;      // +0x194
    uint32_t pad1B4;
    uint8_t mb1B8;
    uint8_t pad1B9[0x13];
    uint32_t mn1CC;                        // +0x1CC
    int32_t mn1D0;                         // +0x1D0
    uint32_t mn1D4;
    PtrVec mPtrVec;                        // +0x1D8
    void* mLocalBuf[4];                    // +0x1F0
    uint32_t mn200;                        // +0x200 material id
    ResourceObject* mpResource;            // +0x204
    Stopwatch mStopwatch;                  // +0x208
    char pad209[0x17];
    uint32_t mn220;                        // +0x220
    uint32_t mn224, mn228, mn22C, mn230, mn234, mn238;
    uint8_t mb23C;
    char pad23D[3];
    uint32_t mnNextMaterialId;             // +0x240
    EntryVec mRegistered;                  // +0x244
    uint32_t pad250, pad254;
    Mutex mMutex;                          // +0x258

    cMaterialManager();                    // 0x00713A80
    ~cMaterialManager();                   // 0x00713780
    uint32_t GetIDFromCompiledState(uint32_t state, uint32_t id);   // 0x00712E10
    void RegisterMaterial(uint32_t key, int nFlags, const uint32_t* flags, uint32_t nTex,
                          void** texRes);                           // 0x00712F50
    bool ReadExternalReferences(ResourceDatabaseStub* db);          // 0x00713070
};

// @ 0x00713A80
cMaterialManager::cMaterialManager()
{
    mpVtblA = 0;
    mpVtblB = vtblMaterialManagerBaseB;
    pad8 = 0;
    mpVtblA = vtblMaterialManagerA;
    mpVtblB = vtblMaterialManagerB;
    mpListener = 0;
    // mScriptState constructed here
    mMaterialsMap.InitEmpty();
    mCompiledStateToIDMap.InitEmpty();
    pad1B4 = 0;
    mn1D0 = -1;
    mn1D4 = 0;
    mPtrVec.mpLocal = &mLocalBuf[0];
    mPtrVec.mpBegin = &mLocalBuf[0];
    mPtrVec.mpEnd = &mLocalBuf[0];
    mPtrVec.mpCapacity = &mLocalBuf[4];
    mb1B8 = 0;
    mn1CC = 1;
    mn200 = 0;
    mpResource = 0;
    mStopwatch.Construct(5, 0);
    mn220 = 0;
    mn224 = 0;
    mn228 = 0;
    mn22C = 0;
    mn230 = 0;
    mn234 = 0;
    mn238 = 0;
    mb23C = 0;
    mnNextMaterialId = 0x200;
    mRegistered.mpBegin = 0;
    mRegistered.mpEnd = 0;
    mRegistered.mpCapacity = 0;
    mMutex.Construct(0, 1);
}

// @ 0x00713780
cMaterialManager::~cMaterialManager()
{
    mpVtblA = vtblMaterialManagerA;
    mpVtblB = vtblMaterialManagerB;
    mMutex.Destroy();

    mRegistered.DoDestroy(mRegistered.mpBegin, mRegistered.mpEnd);
    MaterialEntry** p = mRegistered.mpBegin;
    if (p && ((int*)p)[-1])
        EastlFree(p);

    if (mpResource)
        mpResource->Release();

    mPtrVec.DoDestroy(mPtrVec.mpBegin, mPtrVec.mpEnd);
    if (mPtrVec.mpBegin && mPtrVec.mpBegin != mPtrVec.mpLocal)
        EastlFree(mPtrVec.mpBegin);

    mCompiledStateToIDMap.FreeNodes693230(mCompiledStateToIDMap.mpBuckets,
                                          mCompiledStateToIDMap.mnBuckets);
    mCompiledStateToIDMap.mnElements = 0;
    if (mCompiledStateToIDMap.mnBuckets > 1)
        EastlFree(mCompiledStateToIDMap.mpBuckets);

    mMaterialsMap.FreeNodes712320(mMaterialsMap.mpBuckets, mMaterialsMap.mnBuckets);
    mMaterialsMap.mnElements = 0;
    if (mMaterialsMap.mnBuckets > 1)
        EastlFree(mMaterialsMap.mpBuckets);

    mScriptState.~cMaterialScriptState();

    if (mpListener)
        mpListener->Release();
    mpVtblA = vtblMaterialManagerBaseA;
    mpVtblB = vtblMaterialManagerBaseB;
}

// @ 0x00713E20
void __cdecl ForwardToMaterialManager(uint32_t a, uint32_t b, uint32_t c)
{
    void* manager = GetMaterialManager();
    void* fn = (*(void***)manager)[0x3c / 4];
    ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t))fn)(manager, a, b, c);
}

// @ 0x00712E10
uint32_t cMaterialManager::GetIDFromCompiledState(uint32_t state, uint32_t id)
{
    mMutex.Lock(gMutexParams);
    uint32_t* found = 0;
    mCompiledStateToIDMap.find(&found, &state);
    uint32_t result;
    if (found == (uint32_t*)mCompiledStateToIDMap.mpBuckets[mCompiledStateToIDMap.mnNextResize]) {
        // not found: pick the next unused material id
        MaterialEntry* e;
        uint32_t n;
        for (;;) {
            n = mnNextMaterialId++;
            uint32_t* node = (uint32_t*)mMaterialsMap.mpBuckets[n % mMaterialsMap.mnBuckets];
            while (node) {
                if (n == node[0])
                    break;
                node = (uint32_t*)node[0x4c / 4];
            }
            if (node == 0)
                break;           // id not used yet (iterator == end)
        }
        e = mMaterialsMap.operator_index(&n);
        e->mnExternalId = id;
        *(uint8_t*)e = 1;
        ((uint32_t*)e)[1] = state;
        e->mnId = n;
        *mCompiledStateToIDMap.operator_index(&state) = n;
        result = n;
    } else {
        result = found[1];
    }
    mMutex.Unlock();
    return result;
}

// @ 0x00712F50
void cMaterialManager::RegisterMaterial(uint32_t key, int nFlags, const uint32_t* flags,
                                        uint32_t nTex, void** texRes)
{
    mMutex.Lock(gMutexParams);
    MaterialEntry* e = mMaterialsMap.operator_index(&key);
    e->Unregister();
    e->mnFlags = (uint8_t)nFlags;
    for (int i = 0; i < nFlags; i++)
        e->mFlags[i] = flags[i];
    e->mnId = key;
    e->mTextures.resize(nTex);
    // eastl::copy of the texture resources into the (just resized) texture vector
    for (uint32_t i = 0; i < nTex; i++)
        e->mTextures.mpBegin[i].SetFromResource(texRes[i]);
    e->mnRefCount++;
    {
        EntryRef ref(e);
        mRegistered.push_back(ref);
    }
    mMutex.Unlock();
}

// @ 0x00713070
bool cMaterialManager::ReadExternalReferences(ResourceDatabaseStub* db)
{
    mMutex.Lock(gMutexParams);

    ResourceObject* old = mpResource;
    if (old) {
        mpResource = 0;
        old->Release();
    }

    ResourceKey key;
    key.instance = mn200;
    key.type = 0x2F4E681B;
    key.group = gGroupMaterialsA;

    ResourceObject* res = 0;
    ResourceManagerStub* mgr = (ResourceManagerStub*)GetResourceManager();
    if (res) {
        ResourceObject* t = res;
        res = 0;
        t->Release();
    }
    if (mgr->GetResource(&key, &res, 0, db, 0, 0)) {
        ResourceObject* obj = res ? (ResourceObject*)res->QueryResource(0x2F4E681B) : 0;
        ResourceObject* prev = mpResource;
        if (obj != prev) {
            if (obj)
                obj->AddRef();
            mpResource = obj;
            if (prev)
                prev->Release();
        }
    }

    if (!mpResource) {
        if (res)
            res->Release();
        mMutex.Unlock();
        return false;
    }

    ResourceKey key2;
    key2.instance = mn200;
    key2.type = 0x0469A3F7;
    key2.group = gGroupMaterialsB;
    StreamHolder* holder = 0;
    if (!db->GetStream(&key2, &holder, 1, 6, 1, 0)) {
        if (res)
            res->Release();
        mMutex.Unlock();
        return false;
    }

    void* stream = holder->GetStream();
    int version;
    ReadInt32(stream, &version, 1, 0);
    if ((uint32_t)version > 0) {
        holder->Release();
        if (res)
            res->Release();
        mMutex.Unlock();
        return false;
    }

    int exportIndex = 0;
    ImageFactoryStub* factory = (ImageFactoryStub*)GetImageFactory();
    int id;
    ReadInt32(stream, &id, 1, 0);
    while (id != -1) {
        MaterialEntry* e = mMaterialsMap.operator_index((const uint32_t*)&id);
        e->mnId = id;
        ReadExact(stream, e, 1);
        uint8_t nTextures;
        ReadExact(stream, &nTextures, 1);
        e->mTextures.resize(nTextures);
        for (int i = 0; i < nTextures; i++) {
            int a, b;
            ReadInt32(stream, &a, 1, 0);
            ReadInt32(stream, &b, 1, 0);
            void* img = factory->GetImage(a, b, 0);
            e->mTextures.mpBegin[i].SetFromResource(img);
        }
        for (int i = 0; i < e->mnFlags; i++) {
            ExportedObject obj;
            obj.type = 0;
            obj.value = 0;
            obj.pad8 = 0;
            obj.padC = 0;
            obj.pad10 = 0;
            obj.pad14 = 0;
            obj.elems[0].a = 0;
            obj.elems[0].b = 1;
            GetExportedObjectByIndex(mpResource->mpArena, exportIndex, &obj);
            if (obj.type == 0x2000B)
                e->mFlags[i] = obj.value;
            exportIndex++;
        }
        if (e->mTextures.mpBegin != e->mTextures.mpEnd) {
            e->mnRefCount++;
            EntryRef ref(e);
            mRegistered.push_back(ref);
        }
        ReadInt32(stream, &id, 1, 0);
    }
    holder->Close();
    holder->Release();
    if (res)
        res->Release();
    mMutex.Unlock();
    return true;
}

// ---------------------------------------------------------------------------------------------
// shader compile thunk (D3DX)
// ---------------------------------------------------------------------------------------------
struct ID3DXBufferLite {
    virtual void QueryInterface();
    virtual void AddRef();
    virtual void Release();                // +8
    virtual void* GetBufferPointer();      // +0xC
};

extern void** gD3DDevice;                                  // 0x016F89D0 (IDirect3DDevice9*)
extern void* gVertexShaderOut;                             // 0x0162A218
extern void* gPixelShaderOut;                              // 0x0162A21C
const char* __stdcall D3DXGetVertexShaderProfile(void* dev);  // 0x011E1FE0
const char* __stdcall D3DXGetPixelShaderProfile(void* dev);   // 0x011E1FDA
int __stdcall D3DXCompileShader(const char* src, uint32_t len, const void* defines,
                                const void* include, const char* fn, const char* profile,
                                uint32_t flags, ID3DXBufferLite** shader,
                                ID3DXBufferLite** errors, void** constants);   // 0x011E1FD4

static const char* const kVertexShaderSource =
    "float4x4 clipSpaceMatrix : register(c0);float4   frameTime       : register(c4);"
    "struct tVertexIn{    float3 position   : POSITION0;};"
    "struct tVertexOut{    float4 clipPosition  : POSITION;    float4 color         : COLOR0;};"
    "tVertexOut main(tVertexIn vertIn){    tVertexOut vertOut;    "
    "float4 hPos = float4(vertIn.position, 1);    "
    "vertOut.clipPosition = mul(hPos, clipSpaceMatrix);    "
    "vertOut.color = float4(frac(frameTime[0]), 0, 0, 1);    return vertOut;}";
static const char* const kPixelShaderSource =
    "struct tFrag{    float4 color : COLOR0;};tFrag main(tFrag fragIn){    return fragIn;}";

typedef int(__stdcall* CreateShaderFn)(void* dev, const void* code, void** out);

// @ 0x00713CB0
bool __cdecl CompileVertexAndPixelShaders()
{
    ID3DXBufferLite* shader;
    ID3DXBufferLite* errors;

    const char* profile = D3DXGetVertexShaderProfile(gD3DDevice);
    int hr = D3DXCompileShader(kVertexShaderSource, (uint32_t)strlen(kVertexShaderSource), 0, 0,
                               "main", profile, 0, &shader, &errors, 0);
    if (errors)
        errors->Release();
    if (hr >= 0) {
        CreateShaderFn create = (CreateShaderFn)(*(void***)gD3DDevice)[0x16c / 4];
        hr = create(gD3DDevice, shader->GetBufferPointer(), &gVertexShaderOut);
        if (shader)
            shader->Release();
        if (hr < 0)
            return false;
    }

    profile = D3DXGetPixelShaderProfile(gD3DDevice);
    hr = D3DXCompileShader(kPixelShaderSource, (uint32_t)strlen(kPixelShaderSource), 0, 0,
                           "main", profile, 0, &shader, &errors, 0);
    if (errors)
        errors->Release();
    if (hr >= 0) {
        CreateShaderFn create = (CreateShaderFn)(*(void***)gD3DDevice)[0x1a8 / 4];
        hr = create(gD3DDevice, shader->GetBufferPointer(), &gPixelShaderOut);
        if (shader)
            shader->Release();
        if (hr < 0)
            return false;
    }
    return true;
}
