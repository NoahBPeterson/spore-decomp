// src/game/SPEditors/SPEditorSystem.cpp -- migrated from slice(s) s00836910, s005d61b0, s005d53e0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorSystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cEditorsTokenTranslator.h"
#include "SP/cStringTokenTranslator.h"
#include <new>
#include <math.h>
#include "SP/Pollen/CookieHandler.h"
#include "SP/cIEditorBaker.h"
#include "SP/cISPCreatureAnimManager.h"
#include "SP/cSPUIAssetBrowser.h"
#include "hkBaseObject.h"
#include "hkBool.h"
#include "hkOstream.h"
#include "hkReferencedObject.h"

// ---- items of slice s005d53e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
namespace SP {
class IEditorSubsystem {
 public:
  PV(0) PV(1) PV(2)
  virtual void PreShutdown();  // +0xc
};
}
namespace SP {
class cEditorSystem {
 public:
  bool PreShutdown();
  uint32_t pad00[8];
  IEditorSubsystem* mpSubsystem;  // +0x20
};
}
// ---- items of slice s005d53e0 end

// ---- items of slice s005d61b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedDecrement(long volatile* p);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile* p, long v);
extern "C" long __cdecl _InterlockedExchange(long volatile* p, long v);
extern "C" void __cdecl __debugbreak(void);
extern void* gHavokStackArea;                // 0x015EED9C
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long dwTlsIndex);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedDecrement)
#pragma intrinsic(__debugbreak)
void* operator new(unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line) throw();
void* operator new[](unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line);
void operator delete(void* p) throw();   // 0x00F47380
void operator delete[](void* p) throw(); // 0x00F47380
namespace EA {
namespace Messaging {
void RemoveHandler(void* pServer, void* pHandler, uint32_t* pIdArray, uint32_t nIdCount, int nPriority);   // 0x00571DB0
}
}
namespace EA {
namespace Messaging {
struct IHandler_s005d_61b0 {
    virtual ~IHandler_s005d_61b0() {}
    virtual bool HandleMessage(uint32_t messageID, void* pMessage) = 0;
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
}
}
namespace EA {
namespace Messaging {
struct IHandlerRC_s005d_61b0 : public IHandler_s005d_61b0 {};
}
}
namespace EA {
namespace Messaging {
struct AutoHandler_s005d_61b0 {
    void* mpServer;          // +0x0
    void* mpHandler;         // +0x4
    uint32_t* mpIdArray;     // +0x8
    uint32_t mnIdArrayCount; // +0xc
    int mnPriority;          // +0x10
    AutoHandler_s005d_61b0() : mpServer(0), mpHandler(0), mpIdArray(0), mnIdArrayCount(0), mnPriority(0) {}
    ~AutoHandler_s005d_61b0() { Unregister(); }
    void Unregister() {
        if (mpServer) {
            void* const pServer = mpServer;
            mpServer = 0;
            RemoveHandler(pServer, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
        }
    }
};
}
}
namespace EA {
namespace Thread {
template <class T> struct AtomicInt_s005d_61b0 {
    volatile long mValue;
    T GetValue() const { return mValue; }
    T SetValue(T n) { return _InterlockedExchange(&mValue, n); }
    T Decrement() { return _InterlockedDecrement(&mValue); }
};
}
}
namespace EA {
template <class T> struct RefCountTemplate_s005d_61b0 {
    T mRefCount;
    RefCountTemplate_s005d_61b0() : mRefCount(0) {}
    virtual ~RefCountTemplate_s005d_61b0() {}
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
}
namespace EA {
template <class T> struct AutoRefCount_s005d_61b0 {
    T* mpObject;
    AutoRefCount_s005d_61b0() : mpObject(0) {}
    ~AutoRefCount_s005d_61b0() {
        if (mpObject)
            mpObject->Release();
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    AutoRefCount_s005d_61b0& operator=(T* pObject) {
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
namespace SP {
struct cISPCreatureAnimManager_s005d_61b0 {   // IRefCount
    virtual int AddRef();
    virtual int Release();
    virtual void v2();
    virtual void v3();
    virtual void Shutdown();
};
}
namespace SP {
struct cSPSwatchManager : public EA::RefCountTemplate_s005d_61b0<int> {
    void Shutdown();               // 0x005F0850
    void Update(int deltaTime);    // 0x005F0940
};
}
namespace SP {
struct cSPUIAssetBrowser_s005d_61b0 : public EA::Messaging::IHandlerRC_s005d_61b0 {
    char pad04[0x1c - 4];
    bool mbVisible;                // +0x1c
    void Shutdown();               // 0x0064A220
    void Update(int deltaTime);    // 0x0064C400
    static void Launch(uint32_t layoutID, uint32_t param, int flags);   // 0x0064BC50
};
}
namespace SP {
struct cSPEditorEffects {          // RefCountVTemplate
    virtual ~cSPEditorEffects();
    virtual int AddRef();
    virtual int Release();
    void Shutdown();               // 0x0045AB30
};
}
namespace SP {
struct cIEditorBaker_s005d_61b0 {
    virtual int AddRef();
    virtual int Release();
    virtual void v2();
    virtual void v3();
    virtual void Shutdown();
    virtual void Update();
};
}
namespace SP {
namespace Pollen {
struct CookieHandler_s005d_61b0 {
    EA::Thread::AtomicInt_s005d_61b0<int> mRefCount;   // +0x4
    virtual ~CookieHandler_s005d_61b0();
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
}
namespace SP {
namespace Achievements {
struct Controller {
    virtual ~Controller();
    virtual int AddRef();
    virtual int Release();
    void Shutdown();               // 0x0067A090
};
}
}
namespace SP {
struct cEditorObjectRegistry {     // +0x2c (retail-only member)
    virtual ~cEditorObjectRegistry();
    virtual int AddRef();
    virtual int Release();
    void Shutdown();               // 0x0067BB80
};
}
namespace SP {
struct IWindowManager {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
    virtual void v32();
    virtual int IsModal();
};
}
namespace SP {
IWindowManager* WindowManager();   // 0x0067CAA0
}
namespace SP {
void* RTTManager();                // 0x0064AB20
}
namespace SP {
struct cPropertyBlock { char pad[0x118]; int mbFlag; };
}
namespace SP {
struct cAppProperties { char pad[0x3c]; cPropertyBlock* mpBlock; };
}
namespace SP {
extern cAppProperties* sAppProperties;   // 0x015FD918
}
namespace SP {
void SetAchievementsController(void*);   // 0x0067CBF0
}
namespace SP {
void SetEditorObjectRegistry(void*);     // 0x0067CBC0
}
namespace SP {
void SetAssetBrowser(void*);             // 0x004010E0
}
namespace SP {
void SetSporeGuide(void*);               // 0x004010F0
}
namespace SP {
void SetSkinPaintSystem(void*);          // 0x00401130
}
namespace SP {
void SetEditorBaker(void*);              // 0x004010C0
}
namespace SP {
void SetSwatchManager(void*);            // 0x004010D0
}
namespace SP {
void SetEditorEffects(void*);            // 0x00401100
}
namespace SP {
void SetCreatureAnimManager(void*);      // 0x0067CC20
}
namespace SP {
void ShutdownEditorParts();              // 0x00458D80
}
namespace SP {
struct cEditorCamera { virtual void v0(); virtual void Destroy(); };
}
namespace SP {
cEditorCamera* EditorCamera();           // 0x00401060
}
namespace SP {
void SetEditorCamera(void*);             // 0x00401110
}
namespace SP {
struct cEditorTuning { virtual ~cEditorTuning(); };
}
namespace SP {
cEditorTuning* EditorTuning();           // 0x00401070
}
namespace SP {
void SetEditorTuning(void*);             // 0x00401120
}
namespace SP {
struct cEditorRigblockDB { void Shutdown(); ~cEditorRigblockDB(); };   // 0x005EAEF0 / 0x005EA3D0
}
namespace SP {
cEditorRigblockDB* EditorRigblockDB();   // 0x004010A0
}
namespace SP {
void SetEditorRigblockDB(void*);         // 0x00401150
}
namespace SP {
struct cEditorPartsDB { virtual ~cEditorPartsDB(); void Shutdown(); };   // 0x004DCAA0
}
namespace SP {
cEditorPartsDB* EditorPartsDB();         // 0x00401090
}
namespace SP {
void SetEditorPartsDB(void*);            // 0x00401140
}
namespace SP {
struct cEditorModelCache { virtual ~cEditorModelCache(); void Shutdown(); };   // 0x0061DFE0
}
namespace SP {
cEditorModelCache* EditorModelCache();   // 0x0061DF20
}
namespace SP {
void SetEditorModelCache(void*);         // 0x0061DF30
}
namespace SP {
struct cEditorPlayModeMgr { virtual ~cEditorPlayModeMgr(); void Shutdown(); void Update(); };   // 0x00610F30 / 0x0060CEB0
}
namespace SP {
cEditorPlayModeMgr* EditorPlayModeMgr(); // 0x0067CB30
}
namespace SP {
void SetEditorPlayModeMgr(void*);        // 0x0067CC30
}
namespace SP {
void ShutdownEditorTemplates();          // 0x00675620
}
namespace SP {
struct cObjectTemplateDB {
    virtual void v0();
    virtual int Release();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void Shutdown();
};
}
namespace SP {
cObjectTemplateDB* ObjectTemplateDB();   // 0x0067CB40
}
namespace SP {
void SetObjectTemplateDB(void*);         // 0x0067CC40
}
namespace SP {
namespace Thumbnail {
struct cImportExport { virtual ~cImportExport(); void Shutdown(); };   // 0x005FAE40
}
}
namespace SP {
Thumbnail::cImportExport* ThumbnailImportExport(bool bCreate);   // 0x005F7920
}
namespace SP {
int IsEditorGameDataInitialized();      // 0x00401000
}
namespace SP {
void SetEditorGameData(void*);          // 0x004010B0
}
namespace SP {
struct cEditorBakeQueue { void Shutdown(); };   // 0x00622F00
}
namespace SP {
cEditorBakeQueue* EditorBakeQueue();    // 0x00621C70
}
namespace SP {
void SetEditorBakeQueue(void*);         // 0x00621C80
}
namespace SP {
void SetResourceProvider(void*);        // 0x008FE930
}
namespace SP {
void SetHavokWorld(void*);              // 0x0092AC90
}
namespace SP {
struct ICommandServer {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual void v08();
    virtual void AddCommandHandler(void* pFunction, int flags);
    virtual void RemoveCommandHandler(void* pFunction);
};
}
namespace SP {
struct IApp {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual void v08();
    virtual ICommandServer* GetCommandServer();
};
}
namespace SP {
IApp* App();                            // 0x00936400
}
namespace SP {
void EditorCommandHandler();            // 0x005CBB70
}
namespace SP {
void InitEditorMessages();              // 0x00525CE0
}
namespace SP {
struct IEditorUpdatable {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void Update(int deltaTime);
};
}
namespace SP {
cSPSwatchManager* SwatchManager();      // 0x00401020
}
namespace SP {
cSPUIAssetBrowser_s005d_61b0* AssetBrowser();      // 0x00401030
}
namespace SP {
cSPUIAssetBrowser_s005d_61b0* SporeGuide();        // 0x00401040
}
namespace SP {
IEditorUpdatable* EditorAnimWorld();    // 0x0067CB20
}
namespace nSPSkinner {
struct cPaintSystem_s005d_61b0 : public EA::Messaging::IHandlerRC_s005d_61b0 {
    void Shutdown();               // 0x0051EC70
    void Update(int deltaTime);    // 0x00521BA0
};
}
namespace EA {
namespace XHTML {
namespace Resource {
struct IResourceProvider {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual void Shutdown();
};
}
}
}
namespace EA {
namespace XHTML {
namespace Resource {
IResourceProvider* GetResourceProvider();   // 0x008FE480
}
}
}
struct cHavokMemoryPool {
    void* Alloc(uint32_t size, uint32_t align, int a, int b, int c, int d, int e, int f);   // 0x00928A30
    void Free(void* p);                                                                      // 0x009276C0
};
extern cHavokMemoryPool* gHavokMemoryPool;   // 0x016C8B44
void hkBaseSystem_quit();                    // 0x0107ED00
namespace SP {
class cEditorSystem_s005d_61b0 : public EA::Messaging::IHandlerRC_s005d_61b0, public EA::RefCountTemplate_s005d_61b0<int> {
public:
    cEditorSystem_s005d_61b0();  // 0x005d67f0 (SP::cEditorSystem::cEditorSystem_s005d_61b0)
    ~cEditorSystem_s005d_61b0();  // 0x005d67f0 (SP::cEditorSystem::cEditorSystem_s005d_61b0)
    bool PreInit(int);  // 0x005d6f90 (SP::cEditorSystem::PreInit)
    bool Shutdown();  // 0x005d61b0 (SP::cEditorSystem::Shutdown)
    bool HandleMessage(uint32_t messageID, void* pMessage);  // 0x005d6510 (SP::cEditorSystem::HandleMessage)
    void Update(int deltaTime);  // 0x005d65d0 (SP::cEditorSystem::Update)

    EA::AutoRefCount_s005d_61b0<cISPCreatureAnimManager_s005d_61b0> mCreatureAnimManager;  // +0xc
    EA::AutoRefCount_s005d_61b0<cSPSwatchManager> mSwatchManager;               // +0x10
    EA::AutoRefCount_s005d_61b0<cSPUIAssetBrowser_s005d_61b0> mAssetBrowser;               // +0x14
    EA::AutoRefCount_s005d_61b0<cSPUIAssetBrowser_s005d_61b0> mSporeGuide;                 // +0x18
    EA::AutoRefCount_s005d_61b0<cSPEditorEffects> mEditorEffects;               // +0x1c
    EA::AutoRefCount_s005d_61b0<cIEditorBaker_s005d_61b0> mEditorBaker;                    // +0x20
    EA::AutoRefCount_s005d_61b0<nSPSkinner::cPaintSystem_s005d_61b0> mSkinPaintSystem;     // +0x24
    EA::AutoRefCount_s005d_61b0<Pollen::CookieHandler_s005d_61b0> mCookieHandler;          // +0x28
    EA::AutoRefCount_s005d_61b0<cEditorObjectRegistry> mObjectRegistry;         // +0x2c
    EA::AutoRefCount_s005d_61b0<Achievements::Controller> mAchievements;        // +0x30
    EA::Messaging::AutoHandler_s005d_61b0 mAutoMsgHandler;                      // +0x34
};
}
namespace eastl {
struct allocator_s005d_61b0 {
    allocator_s005d_61b0() {}
    void* allocate(uint32_t n, int flags = 0) {
        return new ("Editor", flags, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 209) char[n];
    }
    void deallocate(void* p, uint32_t) { delete[] (char*)p; }
};
}
namespace eastl {
extern void* gpEmptyBucketArray[2];   // 0x0154DF28
}
namespace eastl {
struct true_type {};
}
namespace eastl {
template <class T1, class T2> struct pair_s005d_61b0 {
    T1 first;
    T2 second;
    pair_s005d_61b0() {}
    pair_s005d_61b0(const T1& a, const T2& b) : first(a), second(b) {}
};
}
namespace eastl {
template <class T> struct hash_s005d_61b0;
}
namespace eastl {
template <> struct hash_s005d_61b0<const wchar_t*> {
    uint32_t operator()(const wchar_t* p) const {
        uint32_t c, result = 2166136261U;
        while ((c = (uint16_t)*p++) != 0)
            result = (result * 16777619) ^ c;
        return result;
    }
};
}
namespace eastl {
template <class T> struct str_equal_to {
    bool operator()(T a, T b) const {
        while (*a && (*a == *b)) {
            ++a;
            ++b;
        }
        return *a == *b;
    }
};
}
namespace eastl {
struct prime_rehash_policy_s005d_61b0 {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
    prime_rehash_policy_s005d_61b0() : mfMaxLoadFactor(1.f), mfGrowthFactor(2.f), mnNextResize(0) {}
    pair_s005d_61b0<bool, uint32_t> GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd) const;   // 0x00921440
};
}
namespace eastl {
template <class V> struct hash_node_s005d_61b0 {
    V mValue;
    hash_node_s005d_61b0* mpNext;
};
}
namespace eastl {
template <class Node> struct hashtable_iterator_base {
    Node* mpNode;
    Node** mpBucket;
    hashtable_iterator_base(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
};
}
namespace eastl {
template <class Node> struct hashtable_iterator : public hashtable_iterator_base<Node> {
    hashtable_iterator(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base<Node>(pNode, pBucket) {}
    hashtable_iterator(const hashtable_iterator& x) : hashtable_iterator_base<Node>(x.mpNode, x.mpBucket) {}
};
}
namespace eastl {
struct hashtable_base_empty1 {};
}
namespace eastl {
template <class K, class T> class hashtable_s005d_61b0 : public hashtable_base_empty1 {
public:
    typedef pair_s005d_61b0<const K, T> value_type;
    typedef hash_node_s005d_61b0<value_type> node_type;
    typedef hashtable_iterator<node_type> iterator;
    typedef pair_s005d_61b0<iterator, bool> insert_return_type;

    hashtable_s005d_61b0() : mnBucketCount(0), mnElementCount(0), mRehashPolicy() { reset(); }
    void reset() {
        mnBucketCount = 1;
        mpBucketArray = (node_type**)&gpEmptyBucketArray[0];
        mnElementCount = 0;
        mRehashPolicy.mnNextResize = 0;
    }
    ~hashtable_s005d_61b0() {
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

    hash_s005d_61b0<K> m_h1;
    str_equal_to<K> m_equal;
    node_type** mpBucketArray;           // +0x4
    uint32_t mnBucketCount;              // +0x8
    uint32_t mnElementCount;             // +0xc
    prime_rehash_policy_s005d_61b0 mRehashPolicy;   // +0x10
    allocator_s005d_61b0 mAllocator;                // +0x1c
};
}
namespace eastl {
template class hashtable_s005d_61b0<const wchar_t*, const wchar_t*>;
}
namespace eastl {
template <class T> struct basic_string_s005d_61b0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s005d_61b0 mAllocator;
    basic_string_s005d_61b0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~basic_string_s005d_61b0() { DeallocateSelf(); }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
    }
    void DoFree(T* p, uint32_t n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
};
}
namespace eastl {
template <class T, int nodeCount> struct fixed_string {
    T* mpBegin;          // +0x0
    T* mpEnd;            // +0x4
    T* mpCapacity;       // +0x8
    allocator_s005d_61b0 mOverflowAllocator;   // +0xc
    void* mpPoolBegin;   // +0x10
    T mBuffer[nodeCount];           // +0x14
    fixed_string(const basic_string_s005d_61b0<T>& x) : mpPoolBegin(mBuffer) {
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
typedef void (*hkErrorReportFunction)(const char* s, void* errorReportObject);
struct hkBool_s005d_61b0 {
    char m_bool;
    hkBool_s005d_61b0() {}
    hkBool_s005d_61b0(bool b) : m_bool((char)b) {}
    operator bool() const { return m_bool != 0; }
};
struct hkMemory {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
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
inline hkThreadMemory& hkThreadMemory::getInstance() { return *(hkThreadMemory*)TlsGetValue(s_threadMemoryTls); }
struct hkBaseObject_s005d_61b0 {
    virtual ~hkBaseObject_s005d_61b0() {}
};
struct hkReferencedObject_s005d_61b0 : public hkBaseObject_s005d_61b0 {
    uint16_t m_memSizeAndFlags;   // +0x4
    int16_t m_referenceCount;     // +0x6
    hkReferencedObject_s005d_61b0() : m_referenceCount(1) {}
    void removeReference() {
        if (m_memSizeAndFlags != 0) {
            --m_referenceCount;
            if (m_referenceCount == 0)
                delete this;
        }
    }
    void* operator new(unsigned int nbytes) {
        hkReferencedObject_s005d_61b0* b = (hkReferencedObject_s005d_61b0*)hkMemory::getInstance().allocateChunk(nbytes, 0x15);
        b->m_memSizeAndFlags = (uint16_t)nbytes;
        return b;
    }
    void operator delete(void* p) {
        hkReferencedObject_s005d_61b0* b = (hkReferencedObject_s005d_61b0*)p;
        hkMemory::getInstance().deallocateChunk(p, b->m_memSizeAndFlags, 0x15);
    }
};
template <class T> struct hkSingleton : public hkReferencedObject_s005d_61b0 {
    static T* s_instance;
    static T& getInstance() { return *s_instance; }
    static void replaceInstance(T* p) {
        if (s_instance)
            s_instance->removeReference();
        s_instance = p;
    }
};
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
    virtual void setEnabled(int id, hkBool_s005d_61b0 enabled) = 0;
    virtual hkBool_s005d_61b0 isEnabled(int id) = 0;
    virtual void enableAll() = 0;
    virtual void message(Message msg, int id, const char* description, const char* file, int line) = 0;
    virtual void sectionBegin(int id, const char* sectionName) = 0;
    virtual void sectionEnd() = 0;
};
struct hkOstream_s005d_61b0 {
    hkOstream_s005d_61b0(void* mem, int memSize, hkBool_s005d_61b0 isString);   // 0x0107EF80
    ~hkOstream_s005d_61b0();                                         // 0x0107EFD0
    hkOstream_s005d_61b0& operator<<(const char* s);                 // 0x0107EE30
    hkOstream_s005d_61b0& operator<<(char c);                        // 0x0107EE10
    hkOstream_s005d_61b0& operator<<(int i);                         // 0x0107EE80
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
    virtual void setEnabled(int id, hkBool_s005d_61b0 enabled);
    virtual hkBool_s005d_61b0 isEnabled(int id);
    virtual void enableAll();
    virtual void message(Message msg, int id, const char* description, const char* file, int line);
    virtual void sectionBegin(int id, const char* sectionName);
    virtual void sectionEnd();
    void showMessage(const char* what, int id, const char* desc, const char* file, int line, hkBool_s005d_61b0 stackTrace);

    hkPointerMap<int, int> m_disabledAssertIds;   // +0x8
    hkArray<int> m_sectionIds;                    // +0x14
    hkErrorReportFunction m_errorFunction;        // +0x20
    void* m_errorObject;                          // +0x24
};
class cSPHavokError : public hkDefaultError {
public:
    cSPHavokError(hkErrorReportFunction f) : hkDefaultError(f) { mbEnabled = true; }
    virtual void message(Message msg, int id, const char* description, const char* file, int line);
    bool mbEnabled;   // +0x28
};
void* HavokMalloc(int size, int align);   // 0x005D60F0
void HavokFree(void* p);                  // 0x00F47410
extern void* (*hkSystemMalloc)(int, int); // 0x015B9A34
extern void (*hkSystemFree)(void*);       // 0x015B9A38
void HavokErrorReport(const char* s, void* obj);   // 0x00C2E4E0
struct hkPoolMemory {
    hkPoolMemory();   // 0x0107F910
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
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
namespace EA {
namespace XHTML {
namespace Resource {
struct IProtocolHandler {
    virtual ~IProtocolHandler() {}
    int mRefCount;   // +0x4
    int mUnknown8;   // +0x8
    IProtocolHandler() : mRefCount(0), mUnknown8(0) {}
};
}
}
}
struct sp_vector_allocator_s005d_61b0 {
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
    sp_vector_allocator_s005d_61b0 mAllocator;
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
    sp_vector_allocator_s005d_61b0 mAllocator;
    ~sp_vector_trivial() {
        if (mpBegin)
            mAllocator.deallocate(mpBegin, 0);
    }
};
struct cVirtualBase {
    virtual ~cVirtualBase() {}
};
struct cXHTMLPathList : public cVirtualBase {
    uint32_t mUnknown4;                       // +0x4
    sp_vector_trivial mEntries;               // +0x8
    eastl::basic_string_s005d_61b0<wchar_t> mPath;       // +0x1c
    cXHTMLPathList() {}
};
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
typedef eastl::fixed_string<wchar_t, 97> PathString;
class cSPUIXHTMLFileResourceHandler : public EA::XHTML::Resource::IProtocolHandler {
public:
    cSPUIXHTMLFileResourceHandler(const eastl::basic_string_s005d_61b0<wchar_t>& basePath) : mBasePath(basePath) {}
    ~cSPUIXHTMLFileResourceHandler() {}
    virtual const wchar_t* GetProtocolName(int index);
    eastl::hashtable_s005d_61b0<const wchar_t*, const wchar_t*> mExtensionMap;   // +0xc
    PathString mBasePath;                                              // +0x2c
};
class cSPUIXHTMLUTFResourceHandler : public EA::XHTML::Resource::IProtocolHandler {
public:
    virtual ~cSPUIXHTMLUTFResourceHandler() {}
    virtual const wchar_t* GetProtocolName(int index);
    eastl::hashtable_s005d_61b0<const wchar_t*, const wchar_t*> mExtensionMap;   // +0xc
};
struct cXHTMLLocalizedStrings {
    virtual ~cXHTMLLocalizedStrings();
    sp_vector<eastl::basic_string_s005d_61b0<wchar_t> > mStrings;   // +0x4
    eastl::basic_string_s005d_61b0<wchar_t> mName;                  // +0x18
    eastl::basic_string_s005d_61b0<wchar_t> mValue;                 // +0x28
};
// ---- items of slice s005d61b0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void InitHavokBaseSystem();  // 0x005d6de0 (stays in the slice: not this object's)

// @ 0x005d6190
namespace SP {
bool cEditorSystem::PreShutdown()
{
  if (IEditorSubsystem* subsystem = mpSubsystem)
    subsystem->PreShutdown();
  return true;
}
}  // namespace SP

// @ 0x005d61b0
bool SP::cEditorSystem_s005d_61b0::Shutdown()
{
    if (mAchievements) {
        SP::SetAchievementsController(0);
        mAchievements->Shutdown();
        mAchievements = 0;
    }
    if (mObjectRegistry) {
        SP::SetEditorObjectRegistry(0);
        mObjectRegistry->Shutdown();
        mObjectRegistry = 0;
    }
    if (mAssetBrowser) {
        SP::SetAssetBrowser(0);
        mAssetBrowser->Shutdown();
        mAssetBrowser = 0;
    }
    SP::ShutdownEditorParts();
    if (mSporeGuide) {
        SP::SetSporeGuide(0);
        mSporeGuide->Shutdown();
        mSporeGuide = 0;
    }
    if (mSkinPaintSystem) {
        SP::SetSkinPaintSystem(0);
        mSkinPaintSystem->Shutdown();
        mSkinPaintSystem = 0;
    }
    if (mEditorBaker) {
        SP::SetEditorBaker(0);
        mEditorBaker->Shutdown();
        mEditorBaker = 0;
    }
    if (mSwatchManager) {
        SP::SetSwatchManager(0);
        mSwatchManager->Shutdown();
        mSwatchManager = 0;
    }
    if (mEditorEffects) {
        SP::SetEditorEffects(0);
        mEditorEffects->Shutdown();
        mEditorEffects = 0;
    }
    if (SP::cEditorCamera* pCamera = SP::EditorCamera()) {
        SP::SetEditorCamera(0);
        pCamera->Destroy();
        delete pCamera;
    }
    if (SP::cEditorTuning* pTuning = SP::EditorTuning()) {
        SP::SetEditorTuning(0);
        delete pTuning;
    }
    if (SP::cEditorRigblockDB* pRigblocks = SP::EditorRigblockDB()) {
        SP::SetEditorRigblockDB(0);
        pRigblocks->Shutdown();
        delete pRigblocks;
    }
    if (SP::cEditorPartsDB* pParts = SP::EditorPartsDB()) {
        SP::SetEditorPartsDB(0);
        pParts->Shutdown();
        delete pParts;
    }
    if (mCreatureAnimManager) {
        mCreatureAnimManager->Shutdown();
        SP::SetCreatureAnimManager(0);
        mCreatureAnimManager = 0;
    }
    if (SP::cEditorModelCache* pCache = SP::EditorModelCache()) {
        pCache->Shutdown();
        SP::SetEditorModelCache(0);
        delete pCache;
    }
    if (SP::cEditorPlayModeMgr* pPlayMode = SP::EditorPlayModeMgr()) {
        pPlayMode->Shutdown();
        delete pPlayMode;
        SP::SetEditorPlayModeMgr(0);
    }
    SP::ShutdownEditorTemplates();
    if (SP::cObjectTemplateDB* pTemplates = SP::ObjectTemplateDB()) {
        SP::SetObjectTemplateDB(0);
        pTemplates->Shutdown();
        pTemplates->Release();
    }
    if (Thumbnail::cImportExport* pImportExport = SP::ThumbnailImportExport(false)) {
        pImportExport->Shutdown();
        delete pImportExport;
    }
    if (SP::IsEditorGameDataInitialized())
        SP::SetEditorGameData(0);
    if (SP::cEditorBakeQueue* pQueue = SP::EditorBakeQueue()) {
        pQueue->Shutdown();
        SP::SetEditorBakeQueue(0);
    }
    if (EA::XHTML::Resource::IResourceProvider* pProvider = EA::XHTML::Resource::GetResourceProvider()) {
        pProvider->Shutdown();
        SP::SetResourceProvider(0);
    }
    SP::SetHavokWorld(0);
    hkBaseSystem_quit();
    gHavokMemoryPool->Free(gHavokStackArea);
    gHavokStackArea = 0;
    SP::App()->GetCommandServer()->RemoveCommandHandler((void*)SP::EditorCommandHandler);
    mAutoMsgHandler.Unregister();
    return true;
}

// @ 0x005d6510
bool SP::cEditorSystem_s005d_61b0::HandleMessage(uint32_t messageID, void* pMessage)
{
    switch (messageID) {
    case 0xF40F8FE4:
        if (mAssetBrowser) {
            if (!SP::WindowManager()->IsModal()) {
                uint32_t param = 0;
                if (pMessage)
                    param = *(uint32_t*)pMessage;
                SP::cSPUIAssetBrowser_s005d_61b0::Launch(SP::sAppProperties->mpBlock->mbFlag ? 0x915F2C32 : 0x578C04FA, param, 0);
            } else if (mAssetBrowser->mbVisible) {
                SP::RTTManager();
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

// @ 0x005d65d0
void SP::cEditorSystem_s005d_61b0::Update(int deltaTime)
{
    if (SP::SwatchManager())
        SP::SwatchManager()->Update(deltaTime);
    if (SP::AssetBrowser())
        SP::AssetBrowser()->Update(deltaTime);
    if (SP::SporeGuide())
        SP::SporeGuide()->Update(deltaTime);
    if (SP::EditorAnimWorld())
        SP::EditorAnimWorld()->Update(deltaTime);
    if (mEditorBaker)
        mEditorBaker->Update();
    if (mSkinPaintSystem)
        mSkinPaintSystem->Update(deltaTime);
    if (SP::EditorPlayModeMgr())
        SP::EditorPlayModeMgr()->Update();
}

// @ 0x005d67f0
SP::cEditorSystem_s005d_61b0::cEditorSystem_s005d_61b0()
{
}

// @ 0x005d6850
SP::cEditorSystem_s005d_61b0::~cEditorSystem_s005d_61b0()
{
}

// @ 0x005d6a90
namespace eastl {
template <class K, class T> typename hashtable_s005d_61b0<K, T>::node_type* hashtable_s005d_61b0<K, T>::DoFindNode(node_type* pNode, const K& k, uint32_t c) const
{
    for (; pNode; pNode = pNode->mpNext) {
        if (m_equal(k, pNode->mValue.first))
            return pNode;
    }
    return 0;
}
}  // namespace eastl

// @ 0x005d6ae0
#pragma inline_depth(0)
hkDefaultError* EmitDefaultErrorCtor(void* p, hkErrorReportFunction f, void* o)
{ return ::new (p) hkDefaultError(f, o); }
#pragma inline_depth()

// @ 0x005d6b20
void hkDefaultError::setEnabled(int id, hkBool_s005d_61b0 enabled)
{
    if (enabled)
        m_disabledAssertIds.remove(id);
    else
        m_disabledAssertIds.insert(id, 1);
}

// @ 0x005d6b50
hkBool_s005d_61b0 hkDefaultError::isEnabled(int id)
{
    return m_disabledAssertIds.getWithDefault(id, 0) == 0;
}

// @ 0x005d6b80
void hkDefaultError::showMessage(const char* what, int id, const char* desc, const char* file, int line, hkBool_s005d_61b0 stackTrace)
{
    const int MAX_MSG_SIZE = 512;
    char msgBuf[MAX_MSG_SIZE];
    char idAsHex[12];
    if (id == -1 && m_sectionIds.getSize())
        id = m_sectionIds.back();
    hkString::sprintf(idAsHex, "0x%x", id);
    hkOstream_s005d_61b0 msg(msgBuf, sizeof(msgBuf), true);
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

// @ 0x005d6ce0
void hkDefaultError::message(Message msg, int id, const char* description, const char* file, int line)
{
    if (!isEnabled(id))
        return;
    const char* what = "";
    hkBool_s005d_61b0 stackTrace = false;
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

// @ 0x005d6d90
void hkDefaultError::sectionBegin(int id, const char* sectionName)
{
    m_sectionIds.pushBack(id);
}

// @ 0x005d6dc0
void cSPHavokError::message(Message msg, int id, const char* description, const char* file, int line)
{
    isEnabled(id);
}

// @ 0x005d6de0
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

// @ 0x005d6f90
bool SP::cEditorSystem_s005d_61b0::PreInit(int)
{
    SP::App()->GetCommandServer()->AddCommandHandler((void*)SP::EditorCommandHandler, 0);
    SP::InitEditorMessages();
    InitHavokBaseSystem();
    return true;
}

// @ 0x005d6ff0
namespace eastl {
template <class K, class T> typename hashtable_s005d_61b0<K, T>::insert_return_type hashtable_s005d_61b0<K, T>::DoInsertValue(const value_type& value, true_type)
{
    const K& k = value.first;
    const uint32_t c = m_h1(k);
    uint32_t n = c % mnBucketCount;
    node_type* const pNode = DoFindNode(mpBucketArray[n], k, c);

    if (pNode == 0) {
        const pair_s005d_61b0<bool, uint32_t> bRehash = mRehashPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1);
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
}  // namespace eastl

// @ 0x005d7180
cXHTMLPathList* EmitPathList(void* p)
{ return ::new (p) cXHTMLPathList; }

// @ 0x005d7240
#pragma inline_depth(0)
cHashedResourceTable* EmitHashedResourceTable(void* p, int c)
{ return ::new (p) cHashedResourceTable(c); }
#pragma inline_depth()

// @ 0x005d7270
#pragma inline_depth(0)
PathString* EmitPathString(void* p, const eastl::basic_string_s005d_61b0<wchar_t>& s)
{ return ::new (p) PathString(s); }
#pragma inline_depth()

// @ 0x005d72b0
#pragma inline_depth(0)
cSPUIXHTMLFileResourceHandler* EmitFileResourceHandler(void* p, const eastl::basic_string_s005d_61b0<wchar_t>& s)
{ return ::new (p) cSPUIXHTMLFileResourceHandler(s); }
#pragma inline_depth()

// @ 0x005d7330
const wchar_t* cSPUIXHTMLFileResourceHandler::GetProtocolName(int index)
{
    return index == 0 ? L"file" : 0;
}

// @ 0x005d7350
void DestroyFileResourceHandler(cSPUIXHTMLFileResourceHandler* p)
{ p->~cSPUIXHTMLFileResourceHandler(); }

// @ 0x005d73d0
const wchar_t* cSPUIXHTMLUTFResourceHandler::GetProtocolName(int index)
{
    return index == 0 ? L"utfres" : 0;
}

// @ 0x005d7450
cXHTMLLocalizedStrings::~cXHTMLLocalizedStrings()
{}

// @ 0x00836bd0
int FUN_00836bd0(int p1, int p2)
{ (void)p1; (void)p2; return 0; }
