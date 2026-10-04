// Slice s005d61b0: SP::cEditorSystem (editor subsystem bring-up/teardown), the Havok base
// system init (hkDefaultError, hkPoolMemory, hkThreadMemory), and a few XHTML protocol handlers.
#include "types.h"

#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedDecrement)
extern "C" long __cdecl _InterlockedDecrement(long volatile* p);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile* p, long v);
extern "C" long __cdecl _InterlockedExchange(long volatile* p, long v);
extern "C" void __cdecl __debugbreak(void);
#pragma intrinsic(__debugbreak)

inline void* operator new(unsigned int, void* p) throw() { return p; }
// 0x00F473A0 (the EA named-allocation operator new; new[] folds to the same address)
void* operator new(unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line) throw();
void* operator new[](unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line);
void operator delete(void* p) throw();   // 0x00F47380
void operator delete[](void* p) throw(); // 0x00F47380

// ---------------------------------------------------------------------------------------------
// EA::Messaging / EA ref counting
namespace EA {
namespace Messaging {
void RemoveHandler(void* pServer, void* pHandler, uint32_t* pIdArray, uint32_t nIdCount, int nPriority);   // 0x00571DB0
struct IHandler {
    virtual ~IHandler() {}
    virtual bool HandleMessage(uint32_t messageID, void* pMessage) = 0;
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
struct IHandlerRC : public IHandler {};
// Retail layout (the 2008 PDB has a 4-field version).
struct AutoHandler {
    void* mpServer;          // +0x0
    void* mpHandler;         // +0x4
    uint32_t* mpIdArray;     // +0x8
    uint32_t mnIdArrayCount; // +0xc
    int mnPriority;          // +0x10
    AutoHandler() : mpServer(0), mpHandler(0), mpIdArray(0), mnIdArrayCount(0), mnPriority(0) {}
    ~AutoHandler() { Unregister(); }
    void Unregister() {
        if (mpServer) {
            void* const pServer = mpServer;
            mpServer = 0;
            RemoveHandler(pServer, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
        }
    }
};
}
namespace Thread {
template <class T> struct AtomicInt {
    volatile long mValue;
    T GetValue() const { return mValue; }
    T SetValue(T n) { return _InterlockedExchange(&mValue, n); }
    T Decrement() { return _InterlockedDecrement(&mValue); }
};
}
template <class T> struct RefCountTemplate {
    T mRefCount;
    RefCountTemplate() : mRefCount(0) {}
    virtual ~RefCountTemplate() {}
    int AddRef() { return ++mRefCount; }
    int Release() {
        const T rc = mRefCount - 1;
        mRefCount = rc;
        if (rc == 0) {
            mRefCount = 1;
            delete this;
            return 0;
        }
        return mRefCount;
    }
};
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() {
        if (mpObject)
            mpObject->Release();
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    AutoRefCount& operator=(T* pObject) {
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
};
}

// ---------------------------------------------------------------------------------------------
// Editor subsystems held by cEditorSystem (only the vtable slots used here are named).
namespace SP {
struct cISPCreatureAnimManager {   // IRefCount
    virtual int AddRef();
    virtual int Release();
    virtual void v2();
    virtual void v3();
    virtual void Shutdown();
};
struct cSPSwatchManager : public EA::RefCountTemplate<int> {
    void Shutdown();               // 0x005F0850
    void Update(int deltaTime);    // 0x005F0940
};
struct cSPUIAssetBrowser : public EA::Messaging::IHandlerRC {
    char pad04[0x1c - 4];
    bool mbVisible;                // +0x1c
    void Shutdown();               // 0x0064A220
    void Update(int deltaTime);    // 0x0064C400
    static void Launch(uint32_t layoutID, uint32_t param, int flags);   // 0x0064BC50
};
struct cSPEditorEffects {          // RefCountVTemplate
    virtual ~cSPEditorEffects();
    virtual int AddRef();
    virtual int Release();
    void Shutdown();               // 0x0045AB30
};
struct cIEditorBaker {
    virtual int AddRef();
    virtual int Release();
    virtual void v2();
    virtual void v3();
    virtual void Shutdown();
    virtual void Update();
};
namespace Pollen {
struct CookieHandler {
    EA::Thread::AtomicInt<int> mRefCount;   // +0x4
    virtual ~CookieHandler();
    int AddRef() { return _InterlockedExchangeAdd(&mRefCount.mValue, 1) + 1; }
    int Release() {
        const int rc = mRefCount.Decrement();
        if (rc == 0) {
            mRefCount.SetValue(1);
            delete this;
        }
        return rc;
    }
    void Clear();                  // 0x0060A960
};
}
namespace Achievements {
struct Controller {
    virtual ~Controller();
    virtual int AddRef();
    virtual int Release();
    void Shutdown();               // 0x0067A090
};
}
struct cEditorObjectRegistry {     // +0x2c (retail-only member)
    virtual ~cEditorObjectRegistry();
    virtual int AddRef();
    virtual int Release();
    void Shutdown();               // 0x0067BB80
};
struct IWindowManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32();
    virtual int IsModal();
};
IWindowManager* WindowManager();   // 0x0067CAA0
void* RTTManager();                // 0x0064AB20
struct cPropertyBlock { char pad[0x118]; int mbFlag; };
struct cAppProperties { char pad[0x3c]; cPropertyBlock* mpBlock; };
extern cAppProperties* sAppProperties;   // 0x015FD918

// Global singletons and their setters.
void SetAchievementsController(void*);   // 0x0067CBF0
void SetEditorObjectRegistry(void*);     // 0x0067CBC0
void SetAssetBrowser(void*);             // 0x004010E0
void SetSporeGuide(void*);               // 0x004010F0
void SetSkinPaintSystem(void*);          // 0x00401130
void SetEditorBaker(void*);              // 0x004010C0
void SetSwatchManager(void*);            // 0x004010D0
void SetEditorEffects(void*);            // 0x00401100
void SetCreatureAnimManager(void*);      // 0x0067CC20
void ShutdownEditorParts();              // 0x00458D80

struct cEditorCamera { virtual void v0(); virtual void Destroy(); };
cEditorCamera* EditorCamera();           // 0x00401060
void SetEditorCamera(void*);             // 0x00401110
struct cEditorTuning { virtual ~cEditorTuning(); };
cEditorTuning* EditorTuning();           // 0x00401070
void SetEditorTuning(void*);             // 0x00401120
struct cEditorRigblockDB { void Shutdown(); ~cEditorRigblockDB(); };   // 0x005EAEF0 / 0x005EA3D0
cEditorRigblockDB* EditorRigblockDB();   // 0x004010A0
void SetEditorRigblockDB(void*);         // 0x00401150
struct cEditorPartsDB { virtual ~cEditorPartsDB(); void Shutdown(); };   // 0x004DCAA0
cEditorPartsDB* EditorPartsDB();         // 0x00401090
void SetEditorPartsDB(void*);            // 0x00401140
struct cEditorModelCache { virtual ~cEditorModelCache(); void Shutdown(); };   // 0x0061DFE0
cEditorModelCache* EditorModelCache();   // 0x0061DF20
void SetEditorModelCache(void*);         // 0x0061DF30
struct cEditorPlayModeMgr { virtual ~cEditorPlayModeMgr(); void Shutdown(); void Update(); };   // 0x00610F30 / 0x0060CEB0
cEditorPlayModeMgr* EditorPlayModeMgr(); // 0x0067CB30
void SetEditorPlayModeMgr(void*);        // 0x0067CC30
void ShutdownEditorTemplates();          // 0x00675620
struct cObjectTemplateDB {
    virtual void v0();
    virtual int Release();
    virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Shutdown();
};
cObjectTemplateDB* ObjectTemplateDB();   // 0x0067CB40
void SetObjectTemplateDB(void*);         // 0x0067CC40
namespace Thumbnail {
struct cImportExport { virtual ~cImportExport(); void Shutdown(); };   // 0x005FAE40
}
Thumbnail::cImportExport* ThumbnailImportExport(bool bCreate);   // 0x005F7920
int IsEditorGameDataInitialized();      // 0x00401000
void SetEditorGameData(void*);          // 0x004010B0
struct cEditorBakeQueue { void Shutdown(); };   // 0x00622F00
cEditorBakeQueue* EditorBakeQueue();    // 0x00621C70
void SetEditorBakeQueue(void*);         // 0x00621C80
void SetResourceProvider(void*);        // 0x008FE930
void SetHavokWorld(void*);              // 0x0092AC90
struct ICommandServer {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual void AddCommandHandler(void* pFunction, int flags);
    virtual void RemoveCommandHandler(void* pFunction);
};
struct IApp {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual ICommandServer* GetCommandServer();
};
IApp* App();                            // 0x00936400
void EditorCommandHandler();            // 0x005CBB70
void InitEditorMessages();              // 0x00525CE0

struct IEditorUpdatable {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Update(int deltaTime);
};
cSPSwatchManager* SwatchManager();      // 0x00401020
cSPUIAssetBrowser* AssetBrowser();      // 0x00401030
cSPUIAssetBrowser* SporeGuide();        // 0x00401040
IEditorUpdatable* EditorAnimWorld();    // 0x0067CB20
}
namespace nSPSkinner {
struct cPaintSystem : public EA::Messaging::IHandlerRC {
    void Shutdown();               // 0x0051EC70
    void Update(int deltaTime);    // 0x00521BA0
};
}
namespace EA { namespace XHTML { namespace Resource {
struct IResourceProvider {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void Shutdown();
};
IResourceProvider* GetResourceProvider();   // 0x008FE480
} } }

// The memory pool Havok's stack area comes from.
struct cHavokMemoryPool {
    void* Alloc(uint32_t size, uint32_t align, int a, int b, int c, int d, int e, int f);   // 0x00928A30
    void Free(void* p);                                                                      // 0x009276C0
};
extern cHavokMemoryPool* gHavokMemoryPool;   // 0x016C8B44
extern void* gHavokStackArea;                // 0x015EED9C
void hkBaseSystem_quit();                    // 0x0107ED00

namespace SP {
class cEditorSystem : public EA::Messaging::IHandlerRC, public EA::RefCountTemplate<int> {
public:
    cEditorSystem();
    ~cEditorSystem();
    bool PreInit(int);
    bool Shutdown();
    bool HandleMessage(uint32_t messageID, void* pMessage);
    void Update(int deltaTime);

    EA::AutoRefCount<cISPCreatureAnimManager> mCreatureAnimManager;  // +0xc
    EA::AutoRefCount<cSPSwatchManager> mSwatchManager;               // +0x10
    EA::AutoRefCount<cSPUIAssetBrowser> mAssetBrowser;               // +0x14
    EA::AutoRefCount<cSPUIAssetBrowser> mSporeGuide;                 // +0x18
    EA::AutoRefCount<cSPEditorEffects> mEditorEffects;               // +0x1c
    EA::AutoRefCount<cIEditorBaker> mEditorBaker;                    // +0x20
    EA::AutoRefCount<nSPSkinner::cPaintSystem> mSkinPaintSystem;     // +0x24
    EA::AutoRefCount<Pollen::CookieHandler> mCookieHandler;          // +0x28
    EA::AutoRefCount<cEditorObjectRegistry> mObjectRegistry;         // +0x2c
    EA::AutoRefCount<Achievements::Controller> mAchievements;        // +0x30
    EA::Messaging::AutoHandler mAutoMsgHandler;                      // +0x34
};
}

using namespace SP;
namespace { void InitHavokBaseSystem(); }

// @ 0x005D61B0
bool cEditorSystem::Shutdown()
{
    if (mAchievements) {
        SetAchievementsController(0);
        mAchievements->Shutdown();
        mAchievements = 0;
    }
    if (mObjectRegistry) {
        SetEditorObjectRegistry(0);
        mObjectRegistry->Shutdown();
        mObjectRegistry = 0;
    }
    if (mAssetBrowser) {
        SetAssetBrowser(0);
        mAssetBrowser->Shutdown();
        mAssetBrowser = 0;
    }
    ShutdownEditorParts();
    if (mSporeGuide) {
        SetSporeGuide(0);
        mSporeGuide->Shutdown();
        mSporeGuide = 0;
    }
    if (mSkinPaintSystem) {
        SetSkinPaintSystem(0);
        mSkinPaintSystem->Shutdown();
        mSkinPaintSystem = 0;
    }
    if (mEditorBaker) {
        SetEditorBaker(0);
        mEditorBaker->Shutdown();
        mEditorBaker = 0;
    }
    if (mSwatchManager) {
        SetSwatchManager(0);
        mSwatchManager->Shutdown();
        mSwatchManager = 0;
    }
    if (mEditorEffects) {
        SetEditorEffects(0);
        mEditorEffects->Shutdown();
        mEditorEffects = 0;
    }
    if (cEditorCamera* pCamera = EditorCamera()) {
        SetEditorCamera(0);
        pCamera->Destroy();
        delete pCamera;
    }
    if (cEditorTuning* pTuning = EditorTuning()) {
        SetEditorTuning(0);
        delete pTuning;
    }
    if (cEditorRigblockDB* pRigblocks = EditorRigblockDB()) {
        SetEditorRigblockDB(0);
        pRigblocks->Shutdown();
        delete pRigblocks;
    }
    if (cEditorPartsDB* pParts = EditorPartsDB()) {
        SetEditorPartsDB(0);
        pParts->Shutdown();
        delete pParts;
    }
    if (mCreatureAnimManager) {
        mCreatureAnimManager->Shutdown();
        SetCreatureAnimManager(0);
        mCreatureAnimManager = 0;
    }
    if (cEditorModelCache* pCache = EditorModelCache()) {
        pCache->Shutdown();
        SetEditorModelCache(0);
        delete pCache;
    }
    if (cEditorPlayModeMgr* pPlayMode = EditorPlayModeMgr()) {
        pPlayMode->Shutdown();
        delete pPlayMode;
        SetEditorPlayModeMgr(0);
    }
    ShutdownEditorTemplates();
    if (cObjectTemplateDB* pTemplates = ObjectTemplateDB()) {
        SetObjectTemplateDB(0);
        pTemplates->Shutdown();
        pTemplates->Release();
    }
    if (Thumbnail::cImportExport* pImportExport = ThumbnailImportExport(false)) {
        pImportExport->Shutdown();
        delete pImportExport;
    }
    if (IsEditorGameDataInitialized())
        SetEditorGameData(0);
    if (cEditorBakeQueue* pQueue = EditorBakeQueue()) {
        pQueue->Shutdown();
        SetEditorBakeQueue(0);
    }
    if (EA::XHTML::Resource::IResourceProvider* pProvider = EA::XHTML::Resource::GetResourceProvider()) {
        pProvider->Shutdown();
        SetResourceProvider(0);
    }
    SetHavokWorld(0);
    hkBaseSystem_quit();
    gHavokMemoryPool->Free(gHavokStackArea);
    gHavokStackArea = 0;
    App()->GetCommandServer()->RemoveCommandHandler((void*)EditorCommandHandler);
    mAutoMsgHandler.Unregister();
    return true;
}

// @ 0x005D6510
bool cEditorSystem::HandleMessage(uint32_t messageID, void* pMessage)
{
    switch (messageID) {
    case 0xF40F8FE4:
        if (mAssetBrowser) {
            if (!WindowManager()->IsModal()) {
                uint32_t param = 0;
                if (pMessage)
                    param = *(uint32_t*)pMessage;
                cSPUIAssetBrowser::Launch(sAppProperties->mpBlock->mbFlag ? 0x915F2C32 : 0x578C04FA, param, 0);
            } else if (mAssetBrowser->mbVisible) {
                RTTManager();
            }
        }
        break;
    case 0x05FF8006:
        mCookieHandler->Clear();
        break;
    case 0x044DB12E:
        if (pMessage && mCookieHandler)
            mCookieHandler->Clear();
        break;
    }
    return false;
}

// @ 0x005D65D0
void cEditorSystem::Update(int deltaTime)
{
    if (SwatchManager())
        SwatchManager()->Update(deltaTime);
    if (AssetBrowser())
        AssetBrowser()->Update(deltaTime);
    if (SporeGuide())
        SporeGuide()->Update(deltaTime);
    if (EditorAnimWorld())
        EditorAnimWorld()->Update(deltaTime);
    if (mEditorBaker)
        mEditorBaker->Update();
    if (mSkinPaintSystem)
        mSkinPaintSystem->Update(deltaTime);
    if (EditorPlayModeMgr())
        EditorPlayModeMgr()->Update();
}

// @ 0x005D67F0
cEditorSystem::cEditorSystem()
{
}

// @ 0x005D6850
cEditorSystem::~cEditorSystem()
{
}

// @ 0x005D6F90
bool cEditorSystem::PreInit(int)
{
    App()->GetCommandServer()->AddCommandHandler((void*)EditorCommandHandler, 0);
    InitEditorMessages();
    InitHavokBaseSystem();
    return true;
}

// ---------------------------------------------------------------------------------------------
// eastl::hash_map<const wchar_t*, const wchar_t*, hash<const wchar_t*>, str_equal_to<...>>
namespace eastl {
struct allocator {
    allocator() {}
    void* allocate(uint32_t n, int flags = 0) {
        return new ("Editor", flags, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 209) char[n];
    }
    void deallocate(void* p, uint32_t) { delete[] (char*)p; }
};
extern void* gpEmptyBucketArray[2];   // 0x0154DF28
struct true_type {};
template <class T1, class T2> struct pair {
    T1 first;
    T2 second;
    pair() {}
    pair(const T1& a, const T2& b) : first(a), second(b) {}
};
template <class T> struct hash;
template <> struct hash<const wchar_t*> {
    uint32_t operator()(const wchar_t* p) const {
        uint32_t c, result = 2166136261U;
        while ((c = (uint16_t)*p++) != 0)
            result = (result * 16777619) ^ c;
        return result;
    }
};
template <class T> struct str_equal_to {
    bool operator()(T a, T b) const {
        while (*a && (*a == *b)) {
            ++a;
            ++b;
        }
        return *a == *b;
    }
};
struct prime_rehash_policy {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
    prime_rehash_policy() : mfMaxLoadFactor(1.f), mfGrowthFactor(2.f), mnNextResize(0) {}
    pair<bool, uint32_t> GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd) const;   // 0x00921440
};
template <class V> struct hash_node {
    V mValue;
    hash_node* mpNext;
};
template <class Node> struct hashtable_iterator_base {
    Node* mpNode;
    Node** mpBucket;
    hashtable_iterator_base(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
};
template <class Node> struct hashtable_iterator : public hashtable_iterator_base<Node> {
    hashtable_iterator(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base<Node>(pNode, pBucket) {}
    hashtable_iterator(const hashtable_iterator& x) : hashtable_iterator_base<Node>(x.mpNode, x.mpBucket) {}
};
struct hashtable_base_empty1 {};
struct hashtable_base_empty2 {};

template <class K, class T> class hashtable : public hashtable_base_empty1 {
public:
    typedef pair<const K, T> value_type;
    typedef hash_node<value_type> node_type;
    typedef hashtable_iterator<node_type> iterator;
    typedef pair<iterator, bool> insert_return_type;

    hashtable() : mnBucketCount(0), mnElementCount(0), mRehashPolicy() { reset(); }
    void reset() {
        mnBucketCount = 1;
        mpBucketArray = (node_type**)&gpEmptyBucketArray[0];
        mnElementCount = 0;
        mRehashPolicy.mnNextResize = 0;
    }
    ~hashtable() {
        clear();
        DoFreeBuckets(mpBucketArray, mnBucketCount);
    }
    void clear() {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    void DoFreeNodes(node_type** pNodeArray, uint32_t n);   // 0x00693230
    void DoFreeBuckets(node_type** pBucketArray, uint32_t n) {
        if (n > 1)
            mAllocator.deallocate(pBucketArray, (n + 1) * sizeof(node_type*));
    }
    node_type* DoAllocateNode(const value_type& value) {
        node_type* const pNode = (node_type*)mAllocator.allocate(sizeof(node_type));
        ::new (&pNode->mValue) value_type(value);
        pNode->mpNext = 0;
        return pNode;
    }
    void DoRehash(uint32_t nNewBucketCount);   // 0x005D6670
    node_type* DoFindNode(node_type* pNode, const K& k, uint32_t c) const;
    insert_return_type DoInsertValue(const value_type& value, true_type);

    hash<K> m_h1;
    str_equal_to<K> m_equal;
    node_type** mpBucketArray;           // +0x4
    uint32_t mnBucketCount;              // +0x8
    uint32_t mnElementCount;             // +0xc
    prime_rehash_policy mRehashPolicy;   // +0x10
    allocator mAllocator;                // +0x1c
};

// @ 0x005D6A90
template <class K, class T>
typename hashtable<K, T>::node_type* hashtable<K, T>::DoFindNode(node_type* pNode, const K& k, uint32_t c) const
{
    for (; pNode; pNode = pNode->mpNext) {
        if (m_equal(k, pNode->mValue.first))
            return pNode;
    }
    return 0;
}

// @ 0x005D6FF0
template <class K, class T>
typename hashtable<K, T>::insert_return_type hashtable<K, T>::DoInsertValue(const value_type& value, true_type)
{
    const K& k = value.first;
    const uint32_t c = m_h1(k);
    uint32_t n = c % mnBucketCount;
    node_type* const pNode = DoFindNode(mpBucketArray[n], k, c);

    if (pNode == 0) {
        const pair<bool, uint32_t> bRehash = mRehashPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1);
        node_type* const pNodeNew = DoAllocateNode(value);
        if (bRehash.first) {
            n = c % bRehash.second;
            DoRehash(bRehash.second);
        }
        pNodeNew->mpNext = mpBucketArray[n];
        mpBucketArray[n] = pNodeNew;
        ++mnElementCount;
        return insert_return_type(iterator(pNodeNew, mpBucketArray + n), true);
    }
    return insert_return_type(iterator(pNode, mpBucketArray + n), false);
}

template class hashtable<const wchar_t*, const wchar_t*>;

// basic_string<wchar_t> / fixed_string<wchar_t, 96>
template <class T> struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;
    basic_string() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~basic_string() { DeallocateSelf(); }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
    }
    void DoFree(T* p, uint32_t n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
};
template <class T, int nodeCount> struct fixed_string {
    T* mpBegin;          // +0x0
    T* mpEnd;            // +0x4
    T* mpCapacity;       // +0x8
    allocator mOverflowAllocator;   // +0xc
    void* mpPoolBegin;   // +0x10
    T mBuffer[nodeCount];           // +0x14
    fixed_string(const basic_string<T>& x) : mpPoolBegin(mBuffer) {
        mpBegin = mpEnd = mBuffer;
        mpCapacity = mpBegin + nodeCount - 1;
        *mpBegin = 0;
        append(x.mpBegin, x.mpEnd);
    }
    ~fixed_string() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin && mpBegin != mpPoolBegin)
            mOverflowAllocator.deallocate(mpBegin, 0);
    }
    fixed_string& append(const T* pBegin, const T* pEnd);   // 0x00672750
};
}

// ---------------------------------------------------------------------------------------------
// Havok base system
typedef void (*hkErrorReportFunction)(const char* s, void* errorReportObject);
struct hkBool {
    char m_bool;
    hkBool() {}
    hkBool(bool b) : m_bool((char)b) {}
    operator bool() const { return m_bool != 0; }
};
struct hkMemory {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void* allocateChunk(int nbytes, int cl);
    virtual void deallocateChunk(void* p, int nbytes, int cl);
    static hkMemory* s_instance;   // 0x016E4178
    static hkMemory& getInstance() { return *s_instance; }
};
struct hkThreadMemory {
    void deallocateChunk(void* p, int nbytes, int cl);   // 0x0107DB10
    static unsigned long s_threadMemoryTls;   // 0x016E4174
    static hkThreadMemory& getInstance();
};
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long dwTlsIndex);
inline hkThreadMemory& hkThreadMemory::getInstance() { return *(hkThreadMemory*)TlsGetValue(s_threadMemoryTls); }
struct hkBaseObject {
    virtual ~hkBaseObject() {}
};
struct hkReferencedObject : public hkBaseObject {
    uint16_t m_memSizeAndFlags;   // +0x4
    int16_t m_referenceCount;     // +0x6
    hkReferencedObject() : m_referenceCount(1) {}
    void removeReference() {
        if (m_memSizeAndFlags != 0) {
            --m_referenceCount;
            if (m_referenceCount == 0)
                delete this;
        }
    }
    void* operator new(unsigned int nbytes) {
        hkReferencedObject* b = (hkReferencedObject*)hkMemory::getInstance().allocateChunk(nbytes, 0x15);
        b->m_memSizeAndFlags = (uint16_t)nbytes;
        return b;
    }
    void operator delete(void* p) {
        hkReferencedObject* b = (hkReferencedObject*)p;
        hkMemory::getInstance().deallocateChunk(p, b->m_memSizeAndFlags, 0x15);
    }
};
template <class T> struct hkSingleton : public hkReferencedObject {
    static T* s_instance;
    static T& getInstance() { return *s_instance; }
    static void replaceInstance(T* p) {
        if (s_instance)
            s_instance->removeReference();
        s_instance = p;
    }
};
template <class T> inline void hkDeallocateChunk(T* p, int numberOfObjects, int cl)
{
    hkThreadMemory::getInstance().deallocateChunk(p, numberOfObjects * sizeof(T), cl);
}
template <class T> struct hkArray {
    T* m_data;
    int m_size;
    int m_capacityAndFlags;
    enum { CAPACITY_MASK = 0x3FFFFFFF, DONT_DEALLOCATE_FLAG = 0x80000000 };
    hkArray() : m_data(0), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}
    ~hkArray() { releaseMemory(); }
    void releaseMemory() {
        if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0) {
            const int n = m_capacityAndFlags & CAPACITY_MASK;
            hkThreadMemory::getInstance().deallocateChunk(m_data, n * sizeof(T), 0x14);
        }
    }
    int getSize() const { return m_size; }
    int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
    T& back() { return m_data[m_size - 1]; }
    void pushBack(const T& e) {
        if (m_size == getCapacity())
            hkArrayUtil_reserveMore(this, sizeof(T));
        m_data[m_size++] = e;
    }
    static void hkArrayUtil_reserveMore(void* array, int elemSize);   // 0x0107F530
};
template <class K, class V> struct hkPointerMap {
    uint32_t m_map[3];
    hkPointerMap();                      // 0x0107DE00
    ~hkPointerMap();                     // 0x0107DE50
    void insert(K key, V val);           // 0x0107DE70
    V getWithDefault(K key, V def);      // 0x0107E540
    void remove(K key);                  // 0x0107E560
};
class hkError : public hkSingleton<hkError> {
public:
    enum Message { MESSAGE_REPORT, MESSAGE_WARNING, MESSAGE_ASSERT, MESSAGE_ERROR };
    virtual void v1();
    virtual void v2();
    virtual void setEnabled(int id, hkBool enabled) = 0;
    virtual hkBool isEnabled(int id) = 0;
    virtual void enableAll() = 0;
    virtual void message(Message msg, int id, const char* description, const char* file, int line) = 0;
    virtual void sectionBegin(int id, const char* sectionName) = 0;
    virtual void sectionEnd() = 0;
};
struct hkOstream {
    hkOstream(void* mem, int memSize, hkBool isString);   // 0x0107EF80
    ~hkOstream();                                         // 0x0107EFD0
    hkOstream& operator<<(const char* s);                 // 0x0107EE30
    hkOstream& operator<<(char c);                        // 0x0107EE10
    hkOstream& operator<<(int i);                         // 0x0107EE80
    uint32_t m_impl[3];
};
struct hkStackTracer {
    hkStackTracer();                                      // 0x0107F250
    ~hkStackTracer();                                     // 0x0107F050
    int getStackTrace(unsigned long* trace, int maxtrace);   // 0x01097300
    void dumpStackTrace(const unsigned long* trace, int numtrace, hkErrorReportFunction pfunc, void* context);   // 0x0107F0C0
    uint32_t m_impl[2];
};
struct hkString { static int sprintf(char* buf, const char* fmt, ...); };   // 0x0107F3B0

class hkDefaultError : public hkError {
public:
    hkDefaultError(hkErrorReportFunction errorReportFunction, void* errorReportObject = 0)
        : m_errorFunction(errorReportFunction), m_errorObject(errorReportObject) {}
    virtual void setEnabled(int id, hkBool enabled);
    virtual hkBool isEnabled(int id);
    virtual void enableAll();
    virtual void message(Message msg, int id, const char* description, const char* file, int line);
    virtual void sectionBegin(int id, const char* sectionName);
    virtual void sectionEnd();
    void showMessage(const char* what, int id, const char* desc, const char* file, int line, hkBool stackTrace);

    hkPointerMap<int, int> m_disabledAssertIds;   // +0x8
    hkArray<int> m_sectionIds;                    // +0x14
    hkErrorReportFunction m_errorFunction;        // +0x20
    void* m_errorObject;                          // +0x24
};

// @ 0x005D6AE0 hkDefaultError::hkDefaultError (inline ctor above, emitted out of line here)
// @ 0x005D7110 hkDefaultError::`scalar deleting destructor' (emitted with the vtable)
#pragma inline_depth(0)
hkDefaultError* EmitDefaultErrorCtor(void* p, hkErrorReportFunction f, void* o) { return ::new (p) hkDefaultError(f, o); }
#pragma inline_depth()

// @ 0x005D6B20
void hkDefaultError::setEnabled(int id, hkBool enabled)
{
    if (enabled)
        m_disabledAssertIds.remove(id);
    else
        m_disabledAssertIds.insert(id, 1);
}

// @ 0x005D6B50
hkBool hkDefaultError::isEnabled(int id)
{
    return m_disabledAssertIds.getWithDefault(id, 0) == 0;
}

// @ 0x005D6B80
void hkDefaultError::showMessage(const char* what, int id, const char* desc, const char* file, int line, hkBool stackTrace)
{
    const int MAX_MSG_SIZE = 512;
    char msgBuf[MAX_MSG_SIZE];
    char idAsHex[12];
    if (id == -1 && m_sectionIds.getSize())
        id = m_sectionIds.back();
    hkString::sprintf(idAsHex, "0x%x", id);
    hkOstream msg(msgBuf, sizeof(msgBuf), true);
    msg << file << '(' << line << "): [" << idAsHex << "] " << what << " : '" << desc << "'\n";
    (*m_errorFunction)(msgBuf, m_errorObject);
    if (stackTrace) {
        hkStackTracer tracer;
        unsigned long trace[20];
        int ntrace = tracer.getStackTrace(trace, 20);
        if (ntrace > 2) {
            (*m_errorFunction)("Stack trace is:\n", m_errorObject);
            tracer.dumpStackTrace(trace + 2, ntrace - 2, m_errorFunction, m_errorObject);
        }
    }
}

// @ 0x005D6CE0
void hkDefaultError::message(Message msg, int id, const char* description, const char* file, int line)
{
    if (!isEnabled(id))
        return;
    const char* what = "";
    hkBool stackTrace = false;
    switch (msg) {
    case MESSAGE_REPORT:
        what = "Report";
        break;
    case MESSAGE_WARNING:
        what = "Warning";
        break;
    case MESSAGE_ASSERT:
        what = "Assert";
        stackTrace = true;
        break;
    case MESSAGE_ERROR:
        what = "Error";
        stackTrace = true;
        break;
    }
    showMessage(what, id, description, file, line, stackTrace);
    if (msg == MESSAGE_ASSERT || msg == MESSAGE_ERROR)
        __debugbreak();
}

// @ 0x005D6D90
void hkDefaultError::sectionBegin(int id, const char* sectionName)
{
    m_sectionIds.pushBack(id);
}

// Spore's error handler: report through hkDefaultError, with a switch to silence it.
class cSPHavokError : public hkDefaultError {
public:
    cSPHavokError(hkErrorReportFunction f) : hkDefaultError(f) { mbEnabled = true; }
    virtual void message(Message msg, int id, const char* description, const char* file, int line);
    bool mbEnabled;   // +0x28
};

// @ 0x005D6DC0
void cSPHavokError::message(Message msg, int id, const char* description, const char* file, int line)
{
    isEnabled(id);
}

void* HavokMalloc(int size, int align);   // 0x005D60F0
void HavokFree(void* p);                  // 0x00F47410
extern void* (*hkSystemMalloc)(int, int); // 0x015B9A34
extern void (*hkSystemFree)(void*);       // 0x015B9A38
void HavokErrorReport(const char* s, void* obj);   // 0x00C2E4E0
struct hkPoolMemory {
    hkPoolMemory();   // 0x0107F910
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual ~hkPoolMemory();
    void removeReference() {
        if (--m_referenceCount == 0)
            delete this;
    }
    uint32_t pad04[2];
    int m_referenceCount;   // +0xc
    uint32_t pad10[(0x350 - 0x10) / 4];
};
struct hkThreadMemoryImpl {
    hkThreadMemoryImpl(hkPoolMemory* mainMemoryManager, int maxNumElemsOnFreeList);   // 0x0107D7E0
    virtual void setStackArea(void* buf, int nbytes);
    void removeReference();   // 0x0107D790
    uint32_t pad04[(0x330 - 4) / 4];
};
namespace hkBaseSystem {
int init(hkPoolMemory* memoryManager, hkThreadMemoryImpl* threadMemory, hkErrorReportFunction errorReportFunction, void* errorReportObject);   // 0x0107EB20
}

namespace {
// @ 0x005D6DE0
void InitHavokBaseSystem()
{
    gHavokStackArea = gHavokMemoryPool->Alloc(1500000, 16, 0, 0, 0, 0, 0, 0);
    hkSystemMalloc = HavokMalloc;
    hkSystemFree = HavokFree;
    hkPoolMemory* memoryManager = new ("SP_Havok", 0, 0, 0, 0) hkPoolMemory();
    hkThreadMemoryImpl* threadMemory = new ("SP_Havok", 0, 0, 0, 0) hkThreadMemoryImpl(memoryManager, 16);
    hkBaseSystem::init(memoryManager, threadMemory, HavokErrorReport, 0);
    threadMemory->setStackArea(gHavokStackArea, 1500000);
    threadMemory->removeReference();
    memoryManager->removeReference();
    cSPHavokError* pError = new cSPHavokError(HavokErrorReport);
    pError->mbEnabled = false;
    hkError::replaceInstance(pError);
    hkError::getInstance().setEnabled(0x6E8D163B, false);
    hkError::getInstance().setEnabled(0x00129864, false);
    hkError::getInstance().setEnabled(0x34DF5494, false);
}
}

// ---------------------------------------------------------------------------------------------
// XHTML resource protocol handlers
namespace EA { namespace XHTML { namespace Resource {
struct IProtocolHandler {
    virtual ~IProtocolHandler() {}
    int mRefCount;   // +0x4
    int mUnknown8;   // +0x8
    IProtocolHandler() : mRefCount(0), mUnknown8(0) {}
};
} } }

struct sp_vector_allocator {
    uint32_t mUnknown[2];
    void deallocate(void* p, uint32_t) {
        if (((int*)p)[-1] != 0)
            delete[] (char*)p;
    }
};
template <class T> struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    ~sp_vector() {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin)
            mAllocator.deallocate(mpBegin, 0);
    }
    void DoDestroyValues(T* first, T* last);   // 0x0084AAD0
};
struct sp_vector_trivial {
    sp_vector_trivial() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    sp_vector_allocator mAllocator;
    ~sp_vector_trivial() {
        if (mpBegin)
            mAllocator.deallocate(mpBegin, 0);
    }
};

// Vtable base at 0x013EF094 (shared, folded empty-virtual-dtor base).
struct cVirtualBase {
    virtual ~cVirtualBase() {}
};

// @ 0x005D7180 (scalar deleting destructor of the implicit virtual dtor)
struct cXHTMLPathList : public cVirtualBase {
    uint32_t mUnknown4;                       // +0x4
    sp_vector_trivial mEntries;               // +0x8
    eastl::basic_string<wchar_t> mPath;       // +0x1c
    cXHTMLPathList() {}
};
cXHTMLPathList* EmitPathList(void* p) { return ::new (p) cXHTMLPathList; }

// @ 0x005D7240
struct cHashedResourceTable {
    char pad[0x10];
    uint16_t mCount;     // +0x10
    uint16_t mCapacity;  // +0x12
    void Init(int a, int b, int c, int d, int e);   // 0x0093DD80
    cHashedResourceTable(int c) {
        mCount = 0;
        mCapacity = 0;
        Init(0x12, 9, c, 0x10, 1);
    }
};
#pragma inline_depth(0)
cHashedResourceTable* EmitHashedResourceTable(void* p, int c) { return ::new (p) cHashedResourceTable(c); }
#pragma inline_depth()

// @ 0x005D7270
typedef eastl::fixed_string<wchar_t, 97> PathString;
#pragma inline_depth(0)
PathString* EmitPathString(void* p, const eastl::basic_string<wchar_t>& s) { return ::new (p) PathString(s); }
#pragma inline_depth()

class cSPUIXHTMLFileResourceHandler : public EA::XHTML::Resource::IProtocolHandler {
public:
    cSPUIXHTMLFileResourceHandler(const eastl::basic_string<wchar_t>& basePath) : mBasePath(basePath) {}
    ~cSPUIXHTMLFileResourceHandler() {}
    virtual const wchar_t* GetProtocolName(int index);
    eastl::hashtable<const wchar_t*, const wchar_t*> mExtensionMap;   // +0xc
    PathString mBasePath;                                              // +0x2c
};

// @ 0x005D72B0
#pragma inline_depth(0)
cSPUIXHTMLFileResourceHandler* EmitFileResourceHandler(void* p, const eastl::basic_string<wchar_t>& s) { return ::new (p) cSPUIXHTMLFileResourceHandler(s); }
#pragma inline_depth()

// @ 0x005D7330
const wchar_t* cSPUIXHTMLFileResourceHandler::GetProtocolName(int index)
{
    return index == 0 ? L"file" : 0;
}

// @ 0x005D7350
void DestroyFileResourceHandler(cSPUIXHTMLFileResourceHandler* p) { p->~cSPUIXHTMLFileResourceHandler(); }

class cSPUIXHTMLUTFResourceHandler : public EA::XHTML::Resource::IProtocolHandler {
public:
    virtual ~cSPUIXHTMLUTFResourceHandler() {}
    virtual const wchar_t* GetProtocolName(int index);
    eastl::hashtable<const wchar_t*, const wchar_t*> mExtensionMap;   // +0xc
};

cSPUIXHTMLUTFResourceHandler* EmitUTFResourceHandler(void* p) { return ::new (p) cSPUIXHTMLUTFResourceHandler; }

// @ 0x005D73F0 (scalar deleting destructor, emitted with the vtable above)

// @ 0x005D73D0
const wchar_t* cSPUIXHTMLUTFResourceHandler::GetProtocolName(int index)
{
    return index == 0 ? L"utfres" : 0;
}

// @ 0x005D7450
struct cXHTMLLocalizedStrings {
    virtual ~cXHTMLLocalizedStrings();
    sp_vector<eastl::basic_string<wchar_t> > mStrings;   // +0x4
    eastl::basic_string<wchar_t> mName;                  // +0x18
    eastl::basic_string<wchar_t> mValue;                 // +0x28
};
cXHTMLLocalizedStrings::~cXHTMLLocalizedStrings() {}
