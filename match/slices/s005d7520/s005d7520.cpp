// Slice s005d7520 -- SP::cEditorSystem::Init (0x005d7520, 4727 bytes).
//
// Name/signature from the dev-build PDB (SPEditorSystem.obj, dev twin 0x00d33360, 5828 bytes):
//   bool SP::cEditorSystem::Init(EA::AppCommandLine& cmdLine)
// Dev local names: login16, login, os, version, XHTMLDir, pResourceProvider, userDataDir,
// cacheDir, shipDirs. The retail body drops the dev profiling/trace zones and adds a few
// retail-only subsystems (hint manager, HUD, buddy-mode filter, editor model cache).
//
// The single editor bring-up (the inverse of cEditorSystem::Shutdown in s005d61b0):
//   - registers the editor resource factory, parses -pollenLogin into an app property,
//   - creates the Pollinator and the editor model cache, the object template DB, posts the
//     "editor init" message and initialises the Pollen URLs,
//   - builds the XHTML resource provider (stylesheet/document/image factories, the HTTP handler
//     with user agent / accept language / cookie, canvas-res and buddy-mode filters / auth,
//     the file, utfres and data: protocol handlers with their MIME tables, the on-disk
//     MVJ file cache) and the XHTML control appearance,
//   - creates the creature anim manager, hint manager, editor block data, swatch manager,
//     asset browser + Spore guide, editor effects, editor camera, HTTP request, parts DB,
//     rigblock DB, the three content-validation summarizers, the skin paint system,
//     thumbnail import/export (-devDirs/-shipDirs), the clipboard and the HUD,
//   - and finally registers the editor system for three messages.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-
#include "types.h"

extern "C" unsigned int __cdecl strlen(const char*);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
#pragma intrinsic(strlen, memcpy)
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedDecrement)
extern "C" long __cdecl _InterlockedDecrement(long volatile* p);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile* p, long v);
extern "C" long __cdecl _InterlockedExchange(long volatile* p, long v);

// 0x00F473A0: EA named-allocation operator new / new[] (folded to one address)
void* operator new(unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line) throw();
void* operator new[](unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line) throw();  // 0x00F473A0
void operator delete(void* p) throw();     // 0x00F47380
void operator delete[](void* p) throw();   // 0x00F47380
// matching deletes for the placement forms (never called: the allocator returns 0 on failure)
void operator delete(void* p, const char*, int, unsigned int, const char*, int) throw();

#define EDITOR_NEW(name) new (name, 0, 0, 0, 0)

// ---------------------------------------------------------------------------------------------
// EASTL pieces
namespace eastl {
struct allocator {
    void* allocate(unsigned int n)
    {
        return ::operator new[](n, "Editor", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    }
    void deallocate(void* p, unsigned int) { ::operator delete[](p); }
};

extern char gEmptyString[2];   // 0x01667BAC (shared empty string: begin = end = gEmptyString, capacity = begin + 1)

struct CtorSprintf {};

// eastl::basic_string<char>
struct string {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator mAllocator;

    string() { mpBegin = mpEnd = gEmptyString; mpCapacity = mpBegin + 1; }
    __forceinline string(const char* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p, p + strlen(p)); }
    string(CtorSprintf, const char* pFormat, ...);   // 0x00472F50 (cdecl, this pushed)
    ~string() { DeallocateSelf(); }
    __forceinline void RangeInitialize(const char* pBegin, const char* pEnd)
    {
        const unsigned int n = (unsigned int)(pEnd - pBegin);
        mpBegin = (char*)mAllocator.allocate(n + 1);
        mpCapacity = mpBegin + n + 1;
        memcpy(mpBegin, pBegin, n);
        mpEnd = mpBegin + n;
        *mpEnd = 0;
    }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
    }
    void DoFree(char* p, unsigned int n)
    {
        if (p)
            mAllocator.deallocate(p, n);
    }
    const char* c_str() const { return mpBegin; }
    string& sprintf(const char* pFormat, ...);       // 0x00472FE0
};

inline unsigned int CharStrlen(const wchar_t* p)
{
    const wchar_t* pCurrent = p;
    while (*pCurrent)
        ++pCurrent;
    return (unsigned int)(pCurrent - p);
}

// eastl::basic_string<wchar_t>
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    allocator mAllocator;

    string16() { mpBegin = mpEnd = (wchar_t*)gEmptyString; mpCapacity = mpBegin + 1; }
    string16(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~string16() { DeallocateSelf(); }
    void RangeInitialize(const wchar_t* p);                                  // 0x00579A90
    string16& append(const wchar_t* pBegin, const wchar_t* pEnd);           // 0x00429580
    string16& append(const wchar_t* p) { return append(p, p + CharStrlen(p)); }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
    }
    void DoFree(wchar_t* p, unsigned int n)
    {
        if (p)
            mAllocator.deallocate(p, n * sizeof(wchar_t));
    }
    const wchar_t* c_str() const { return mpBegin; }
};

// eastl::fixed_string<wchar_t, 97> (EA::IO::Path::PathString)
template <int nodeCount> struct fixed_string16 {
    wchar_t* mpBegin;                 // +0x0
    wchar_t* mpEnd;                   // +0x4
    wchar_t* mpCapacity;              // +0x8
    allocator mOverflowAllocator;     // +0xc
    void* mpPoolBegin;                // +0x10
    wchar_t mBuffer[nodeCount];       // +0x14

    fixed_string16(const wchar_t* p) : mpPoolBegin(mBuffer)
    {
        mpBegin = mpEnd = mBuffer;
        mpCapacity = mpBegin + nodeCount - 1;
        *mpBegin = 0;
        append(p);
    }
    ~fixed_string16()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin && mpBegin != mpPoolBegin)
            mOverflowAllocator.deallocate(mpBegin, 0);
    }
    fixed_string16& append(const wchar_t* pBegin, const wchar_t* pEnd);   // 0x00672750
    fixed_string16& append(const wchar_t* p) { return append(p, p + CharStrlen(p)); }
};

struct prime_rehash_policy {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    unsigned int mnNextResize;
    prime_rehash_policy() : mfMaxLoadFactor(1.0f), mfGrowthFactor(2.0f), mnNextResize(0) {}
};
extern void* gpEmptyBucketArray[2];   // 0x0154DF28

// eastl::hash_map<K, const char*>
template <class K> struct hash_map {
    uint32_t mEmptyBase;              // +0x0
    void** mpBucketArray;             // +0x4
    unsigned int mnBucketCount;       // +0x8
    unsigned int mnElementCount;      // +0xc
    prime_rehash_policy mRehashPolicy;// +0x10
    allocator mAllocator;             // +0x1c
    hash_map() : mnBucketCount(0), mnElementCount(0)
    {
        mpBucketArray = gpEmptyBucketArray;
        mnBucketCount = 1;
    }
    const char*& operator[](const K& key);
};
// The two out-of-line instances this file calls (declared as explicit specializations so each
// carries its own address for the equivalence checker).
template <> const char*& hash_map<const wchar_t*>::operator[](const wchar_t* const& key);  // 0x005D74C0
template <> const char*& hash_map<uint32_t>::operator[](const uint32_t& key);            // 0x005D71E0
}  // namespace eastl

typedef eastl::fixed_string16<97> PathString;

// ---------------------------------------------------------------------------------------------
// EA framework
namespace EA {
namespace Thread {
struct AtomicInt {
    volatile long mValue;
    long Increment() { return _InterlockedExchangeAdd(&mValue, 1) + 1; }
    long Decrement() { return _InterlockedDecrement(&mValue); }
    long SetValue(long n) { return _InterlockedExchange(&mValue, n); }
};
}

// Generic AutoRefCount: T supplies AddRef/Release.
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p)
    {
        if (mpObject)
            mpObject->AddRef();
    }
    ~AutoRefCount()
    {
        if (mpObject)
            mpObject->Release();
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    __forceinline AutoRefCount& operator=(T* pObject)
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
};

// Non-atomic intrusive count at +4, delete through the virtual destructor at slot 0.
struct RefCounted {
    RefCounted() : mRefCount(0) {}
    virtual ~RefCounted() {}
    int mRefCount;   // +0x4
    int AddRef() { return ++mRefCount; }
    int Release()
    {
        const int rc = mRefCount - 1;
        mRefCount = rc;
        if (rc == 0) {
            mRefCount = 1;
            delete this;
            return 0;
        }
        return rc;
    }
};

// Atomic intrusive count at +4.
struct AtomicRefCounted {
    virtual ~AtomicRefCounted() {}
    Thread::AtomicInt mRefCount;   // +0x4
    int AddRef() { return mRefCount.Increment(); }
    int Release()
    {
        const int rc = mRefCount.Decrement();
        if (rc == 0) {
            mRefCount.SetValue(1);
            delete this;
        }
        return rc;
    }
};

// IUnknown32-style interfaces: AddRef/Release at slots 1 and 2 (slot 0 is the virtual dtor).
struct IRefCountV {
    virtual ~IRefCountV() {}
    virtual int AddRef();
    virtual int Release();
};

struct AppCommandLine {
    int FindSwitch(const wchar_t* pSwitch, bool bCaseSensitive, void* pResult, int nIndex) const;   // 0x0092B300
};

struct Variant {
    uint32_t mData[4];
    unsigned short mFlags;     // +0x10
    unsigned short mTypeId;    // +0x12
    enum { kFlagAllocated = 4 };
    Variant(const eastl::string& s) : mFlags(0), mTypeId(0) { Set(0x12, 9, &s, sizeof(s), 1); }
    ~Variant()
    {
        if (mFlags & kFlagAllocated)
            Destruct(false);
    }
    void Destruct(bool bReconstruct);                                       // 0x0093DB80
    // EA::Variant::Set (0x0093DD80); not the debug-build EA::Variant::Construct at 0x00542C30
    void Set(unsigned short typeId, unsigned short flags, const void* pData, unsigned int nSize,
             unsigned int nCount);                                          // 0x0093DD80
};

namespace Hash { uint32_t FNV1_String8(const char* p, uint32_t seed, int bCaseConvert); }   // 0x00932E80

namespace Messaging {
struct IHandler {
    virtual ~IHandler() {}
    virtual bool HandleMessage(uint32_t messageID, void* pMessage);
    virtual int AddRef();
    virtual int Release();
};
struct IMessageServer {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void PostMSG(uint32_t messageID, void* pMessage, void* pSender);            // +0x14
    virtual void v06(); virtual void v07(); virtual void v08();
    virtual void AddHandler(IHandler* pHandler, uint32_t messageID);                   // +0x24
};
struct AutoHandler {
    IMessageServer* mpServer;    // +0x0
    IHandler* mpHandler;         // +0x4
    const uint32_t* mpIdArray;   // +0x8
    uint32_t mnIdArrayCount;     // +0xc
    int mnPriority;              // +0x10
    void Register(IMessageServer* pServer, IHandler* pHandler, const uint32_t* pIdArray, uint32_t nIdCount, int nPriority)
    {
        mpServer = pServer;
        mpHandler = pHandler;
        mpIdArray = pIdArray;
        mnIdArrayCount = nIdCount;
        mnPriority = nPriority;
        for (uint32_t i = 0; i < nIdCount; i++)
            pServer->AddHandler(pHandler, pIdArray[i]);
    }
};
}

namespace Internet {
struct INetFileCache {
    char pad[0x70];
    INetFileCache();                                          // 0x00949B80
    int AddRef();                                             // 0x0093C3E0
    int Release();                                            // 0x00949D90
    void SetCacheDirectory(const wchar_t* pDirectory);        // 0x00948400
    void SetCacheIniFileName(const wchar_t* pFileName);       // 0x00948460
    bool Init();                                              // 0x00949CC0
};
}

namespace XHTML { namespace Resource {
struct IResourceFactory : public EA::RefCounted {
    virtual void v1();
};
struct IProtocolHandler {
    virtual ~IProtocolHandler() {}
    virtual int AddRef();
    virtual int Release();
};
struct IFilter;
struct IAuthenticator : public EA::RefCounted {};

struct ResourceProvider {
    char pad[0x2a8];
    ResourceProvider(void* pAllocator);                                       // 0x008FFE80
    void RegisterFactory(IResourceFactory* pFactory, bool bTakeOwnership);   // 0x008FFD50
    void RegisterProtocolHandler(IProtocolHandler* pHandler, bool bTakeOwnership);   // 0x008FF270
};
void SetResourceProvider(ResourceProvider* p);                                // 0x008FE930

struct StylesheetFactory : public IResourceFactory {
    uint32_t mList[5];            // +0x8 (begin, end, capacity + allocator)
    eastl::string16 mBaseURL;     // +0x1c
    StylesheetFactory() { mList[0] = 0; mList[1] = 0; mList[2] = 0; }
};
struct DocumentFactory : public IResourceFactory {};
struct ImageFactory : public IResourceFactory {};

struct HTTPHandler : public IProtocolHandler {
    char pad04[0x1dc - 4];
    EA::AutoRefCount<IAuthenticator> mpAuthenticator;   // +0x1dc
    char pad1e0[0x1f8 - 0x1e0];
    HTTPHandler();                                                     // 0x008FD540
    void SetUserAgent(const char* pUserAgent);                        // 0x008FD670
    void SetAcceptLanguage(const char* pLanguage);                    // 0x008FD6C0
    void AddFilter(IFilter* pFilter);                                 // 0x008FD070
    void SetFileCache(EA::Internet::INetFileCache* pCache, bool bTakeOwnership);   // 0x008FD1A0
    void EnableLastModifiedHeuristic(bool bEnable, float fFactor);    // 0x008FD050
};
} }
}  // namespace EA

// ---------------------------------------------------------------------------------------------
// SP subsystems (only the slots/methods used here)
namespace SP {
struct cPropertyBlock { char pad[0x118]; int mbCSAMode; };
struct cDirectPropertyList {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void SetProperty(uint32_t id, const EA::Variant& value);   // +0x14
    virtual void v06();
    virtual bool HasProperty(uint32_t id);                             // +0x1c
    bool GetBool(uint32_t id);                                        // 0x006A25A0
    char pad04[0x3c - 4];
    cPropertyBlock* mpBlock;      // +0x3c
};
extern cDirectPropertyList* sAppProperties;   // 0x015FD918

struct cSPEditorResourceFactory {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual bool IsValid();       // +0x10
};
cSPEditorResourceFactory* CreateEditorResourceFactory();   // 0x004C0130
void SetEditorResourceFactory(cSPEditorResourceFactory*);  // 0x004010B0
struct IResourceManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16();
    virtual bool RegisterFactory(bool bRegister, void* pFactory, uint32_t typeID);   // +0x44
};
IResourceManager* GetManager();                            // EA::ResourceMan::GetManager 0x0067DCD0 (not the SP::ResourceManager wrapper)
void InitEditorMemory(int a, int b);                        // 0x006ADC60

struct cPollinator {
    virtual ~cPollinator();
    char pad04[0x120 - 4];
    cPollinator();                // 0x00611580
    bool Init();                  // 0x0060F910
};
void SetPollinator(cPollinator*);          // 0x0067CC30

struct cEditorModelCache {
    virtual ~cEditorModelCache();
    char pad04[0x80 - 4];
    cEditorModelCache();          // 0x0061E4A0
    bool Init();                  // 0x0061FBD0
};
void SetEditorModelCache(cEditorModelCache*);   // 0x0061DF30

void InitCSAMode();                        // 0x00676E40
struct cObjectTemplateDB {
    virtual void v0();
    virtual void v1(); virtual void v2(); virtual void v3();
    virtual void Init();                                     // +0x10
    virtual void v5();
    virtual void ReIndex(int a, int b);                      // +0x18
    virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
    virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void AddSummarizer(void* pSummarizer);           // +0x7c
};
cObjectTemplateDB* CreateObjectTemplateDB();   // 0x0055C640
void SetObjectTemplateDB(cObjectTemplateDB*);  // 0x0067CC40
cObjectTemplateDB* ObjectTemplateDB();         // 0x0067CB40
void InitEditorTemplates();                    // 0x006068C0
EA::Messaging::IMessageServer* MessageServer();   // 0x0067DCC0

namespace Pollen {
void InitURLs();                                // 0x00621830
struct CookieHandler : public EA::AtomicRefCounted {
    char pad08[0x48 - 8];
    CookieHandler(int a, int b);                // 0x0060A990
};
struct cCanvasResFilter : public EA::AtomicRefCounted {
    char pad08[0x1c - 8];
    cCanvasResFilter();                         // 0x006094A0
    void Init();                                // 0x00609760
};
struct cBuddyModeFilter : public EA::AtomicRefCounted {
    char pad08[0x20 - 8];
    cBuddyModeFilter();                         // 0x006094E0
    void Init();                                // 0x00609630
};
struct cAuthManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual EA::XHTML::Resource::IAuthenticator* GetAuthenticator();   // +0x60
};
cAuthManager* AuthManager();                    // 0x00607A60
}

struct cLocaleManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual const eastl::string16& GetLocale();   // +0x14
};
cLocaleManager* GetLocaleManager();           // 0x0067DE40
struct IConfigManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18();
    virtual void GetConfigString(int index, eastl::string& value);   // +0x4c
};
IConfigManager* ConfigManager();              // 0x0067DD30
const wchar_t* GetDataDir();                  // 0x00688CB0
bool GetDirectory(uint32_t dirID, eastl::string16& path, int flags);   // 0x00688830

// cSPUIXHTMLFileResourceHandler (0x100 bytes, ctor 0x005D72B0)
struct cSPUIXHTMLFileResourceHandler : public EA::XHTML::Resource::IProtocolHandler {
    uint32_t mUnknown[2];                                   // +0x4
    eastl::hash_map<const wchar_t*> mExtensionMap;          // +0xc
    char pad2c[0x100 - 0x2c];
    cSPUIXHTMLFileResourceHandler(const PathString& basePath);   // 0x005D72B0
};
// cSPUIXHTMLUTFResourceHandler (0x2c bytes, ctor inlined)
struct cSPUIXHTMLUTFResourceHandler : public EA::XHTML::Resource::IProtocolHandler {
    uint32_t mUnknown4;                                     // +0x4
    uint32_t mUnknown8;                                     // +0x8
    eastl::hash_map<uint32_t> mTypeMap;                     // +0xc
    cSPUIXHTMLUTFResourceHandler() : mUnknown4(0), mUnknown8(0) {}
    virtual const wchar_t* GetProtocolName(int index);
};
// cSPUIXHTMLDataURIHandler (0xc bytes, ctor inlined)
struct cSPUIXHTMLDataURIHandler : public EA::XHTML::Resource::IProtocolHandler {
    uint32_t mUnknown4;                                     // +0x4
    uint32_t mUnknown8;                                     // +0x8
    cSPUIXHTMLDataURIHandler() : mUnknown4(0), mUnknown8(0) {}
    virtual const wchar_t* GetProtocolName(int index);
};

void AddGIFImport();                          // 0x0084BC60
struct cXHTMLControlAppearance : public EA::IRefCountV {
    char pad04[0x24 - 4];
    cXHTMLControlAppearance();                // 0x00621EE0
    void Init();                              // 0x00622130
};
void SetXHTMLControlAppearance(cXHTMLControlAppearance*);   // 0x00621C80

struct cISPCreatureAnimManager {   // IRefCount
    virtual int AddRef();
    virtual int Release();
    virtual void Dispose(bool b);              // +0x8
    virtual bool Initialize(bool bDemo);       // +0xc
    virtual void Shutdown();
};
cISPCreatureAnimManager* CreateCreatureAnimManager();     // 0x00A0BC60
void SetCreatureAnimManager(cISPCreatureAnimManager*);    // 0x0067CC20

struct cHintManager : public EA::IRefCountV {
    char pad04[0x68 - 4];
    cHintManager();                            // 0x0067B270
    void InitHints();                          // 0x0067BA10
};
void SetHintManager(cHintManager*);            // 0x0067CBC0

namespace EditorValidity { void InitializeValidityData(); }   // 0x004EBE20
struct cIEditorBaker {
    virtual int AddRef();
    virtual int Release();
    virtual void Init();                       // +0x8
};
cIEditorBaker* CreateEditorBaker();            // 0x00417D10
void SetEditorBaker(cIEditorBaker*);           // 0x004010C0

struct cSPSwatchManager : public EA::RefCounted {
    char pad08[0x54 - 8];
    cSPSwatchManager();                        // 0x005F0AC0
    void Init();                               // 0x005F0140
};
void SetSwatchManager(cSPSwatchManager*);      // 0x004010D0

struct IWindow;
struct cSPUILayoutManager { IWindow* GetWorldMainWindow(uint32_t id); };   // 0x00810620
cSPUILayoutManager* GetLayoutManager();        // 0x00805070
void PreloadLayout(uint32_t layoutID);         // 0x00458C60

struct cSPUIAssetBrowser : public EA::Messaging::IHandler {
    char pad04[0x250 - 4];
    cSPUIAssetBrowser();                       // 0x00648730
    void Init(IWindow* pParent, bool bSporeGuide);   // 0x00649F60
    void SetVisibility(int a, int b, int c);   // 0x0064A400
};
void SetAssetBrowser(cSPUIAssetBrowser*);      // 0x004010E0
void SetSporeGuide(cSPUIAssetBrowser*);        // 0x004010F0

struct cSPEditorEffects : public EA::IRefCountV {
    char pad04[0x28 - 4];
    cSPEditorEffects();                        // 0x0045AA70
    void Init();                               // 0x004AE250
};
void SetEditorEffects(cSPEditorEffects*);      // 0x00401100

struct cEditorCamera { virtual void Init(); };
cEditorCamera* CreateEditorCamera();           // 0x005D97D0
void SetEditorCamera(cEditorCamera*);          // 0x00401110

struct cEditorTuning { char pad[0xb8]; cEditorTuning(); };     // 0x005DBC70
void SetEditorTuning(cEditorTuning*);          // 0x00401120
struct cEditorPartsDB { char pad[0xe4]; cEditorPartsDB(); void Init(); };       // 0x004DB2C0 / 0x004DB470
void SetEditorPartsDB(cEditorPartsDB*);        // 0x00401140
struct cEditorRigblockDB { char pad[0x40c]; cEditorRigblockDB(); void Init(); }; // 0x005EA970 / 0x005EC7C0
void SetEditorRigblockDB(cEditorRigblockDB*);  // 0x00401150

struct cContentValidationSummarizer { char pad[8]; cContentValidationSummarizer(); };   // 0x00557FC0
struct cSummarizerBase {
    virtual void v0();
    int mUnknown4;
    cSummarizerBase() : mUnknown4(0) {}
};
struct cVehicleSummarizer : public cSummarizerBase { virtual void v1(); };
struct cBuildingSummarizer : public cSummarizerBase { virtual void v1(); };
}

namespace nSPSkinner {
struct cPaintSystem : public EA::Messaging::IHandler {
    char pad04[0x108 - 4];
    cPaintSystem();                            // 0x0051E180
    void Setup();                              // 0x0051E5B0 (symbols name 0x0075D990 cPaintSystem::Init; this is a different method)
};
}
namespace SP {
void SetSkinPaintSystem(nSPSkinner::cPaintSystem*);   // 0x00401130

namespace Thumbnail {
struct cImportExport { void Init(bool bShipDirs); };   // 0x005FD880
cImportExport* CreateImporterExporter();               // 0x005FD850
void SetImporterExporter(cImportExport*);              // 0x005F7920
}
}

namespace EA { namespace Clipboard {
struct Clipboard {
    char pad[0x150];
    Clipboard();                               // 0x0092A880
    void SetId(int id);                        // 0x0092B0F0
    bool Init();                               // 0x0092B140
};
void SetClipboard(Clipboard*);                 // 0x0092AC90
} }

namespace SP {
struct cHUD : public EA::IRefCountV {
    char pad04[0x220 - 4];
    cHUD();                                    // 0x00679520
    void Init();                               // 0x0067A880
};
void SetHUD(cHUD*);                            // 0x0067CBF0

// Message IDs the editor system listens to (0x013F8D78).
extern const uint32_t kEditorSystemMessages[3];  // 0x013F8D78

class cEditorSystem : public EA::Messaging::IHandler {
public:
    int mRefCount;                                                   // +0x4
    uint32_t mUnknown8;                                              // +0x8
    EA::AutoRefCount<cISPCreatureAnimManager> mCreatureAnimManager;  // +0xc
    EA::AutoRefCount<cSPSwatchManager> mSwatchManager;               // +0x10
    EA::AutoRefCount<cSPUIAssetBrowser> mAssetBrowser;               // +0x14
    EA::AutoRefCount<cSPUIAssetBrowser> mSporeGuide;                 // +0x18
    EA::AutoRefCount<cSPEditorEffects> mEditorEffects;               // +0x1c
    EA::AutoRefCount<cIEditorBaker> mEditorBaker;                    // +0x20
    EA::AutoRefCount<nSPSkinner::cPaintSystem> mSkinPaintSystem;     // +0x24
    EA::AutoRefCount<Pollen::CookieHandler> mCookieHandler;          // +0x28
    EA::AutoRefCount<cHintManager> mHintManager;                     // +0x2c
    EA::AutoRefCount<cHUD> mHUD;                                     // +0x30
    EA::Messaging::AutoHandler mAutoMsgHandler;                      // +0x34

    bool Init(EA::AppCommandLine& cmdLine);
};

// @ 0x005D7520
bool cEditorSystem::Init(EA::AppCommandLine& cmdLine)
{
    cSPEditorResourceFactory* pFactory = CreateEditorResourceFactory();
    if (pFactory && pFactory->IsValid()) {
        GetManager()->RegisterFactory(true, pFactory, 0);
        SetEditorResourceFactory(pFactory);
    }

    InitEditorMemory(0xb, 0x10);

    eastl::string16 login16;
    if (cmdLine.FindSwitch(L"pollenLogin", false, &login16, 0) != -1) {
        eastl::string login;
        login.sprintf("%ls", login16);
        sAppProperties->SetProperty(0x5e8af796, EA::Variant(login));
    }

    cPollinator* pPollinator = EDITOR_NEW("Pollinator") cPollinator;
    if (pPollinator->Init())
        SetPollinator(pPollinator);
    else
        delete pPollinator;

    cEditorModelCache* pModelCache = EDITOR_NEW("Pollinator") cEditorModelCache;
    if (pModelCache->Init())
        SetEditorModelCache(pModelCache);
    else
        delete pModelCache;

    if (!sAppProperties->mpBlock->mbCSAMode)
        InitCSAMode();

    if (cObjectTemplateDB* pTemplateDB = CreateObjectTemplateDB()) {
        SetObjectTemplateDB(pTemplateDB);
        pTemplateDB->Init();
        pTemplateDB->v0();
        InitEditorTemplates();
    }

    if (MessageServer())
        MessageServer()->PostMSG(0xf52feda1, 0, 0);

    Pollen::InitURLs();

    using namespace EA::XHTML::Resource;
    ResourceProvider* pResourceProvider = EDITOR_NEW("UI/MVJ/ResourceProvider") ResourceProvider(0);
    SetResourceProvider(pResourceProvider);
    pResourceProvider->RegisterFactory(EDITOR_NEW("UI/MVJ/StylesheetFactory") StylesheetFactory, true);
    pResourceProvider->RegisterFactory(EDITOR_NEW("UI/MVJ/DocumentFactory") DocumentFactory, true);
    pResourceProvider->RegisterFactory(EDITOR_NEW("UI/MVJ/ImageFactory") ImageFactory, true);

    {
        EA::AutoRefCount<HTTPHandler> pHTTPHandler = EDITOR_NEW("UI/MVJ/HTTPHandler") HTTPHandler;

        eastl::string os("Unknown");
        eastl::string version("Unknown");
        ConfigManager()->GetConfigString(5, os);
        ConfigManager()->GetConfigString(4, version);
        pHTTPHandler->SetUserAgent(eastl::string(eastl::CtorSprintf(),
                                                 sAppProperties->mpBlock->mbCSAMode
                                                     ? "SPORE-CSA-2-COMPLETE/%s (XHTML Browser; %s)"
                                                     : "SPORE/%s (XHTML Browser; %s)",
                                                 version.c_str(), os.c_str()).c_str());
        pHTTPHandler->SetAcceptLanguage(
            eastl::string(eastl::CtorSprintf(), "%ls", GetLocaleManager()->GetLocale().c_str()).c_str());
        pResourceProvider->RegisterProtocolHandler(pHTTPHandler, true);

        mCookieHandler = EDITOR_NEW("Pollinator/MVJ/CookieHandler") Pollen::CookieHandler(10, 0x800);
        pHTTPHandler->AddFilter((IFilter*)(Pollen::CookieHandler*)mCookieHandler);

        EA::AutoRefCount<Pollen::cCanvasResFilter> pCanvasResFilter =
            EDITOR_NEW("Pollinator/MVJ/CanvasResFilter") Pollen::cCanvasResFilter;
        pCanvasResFilter->Init();
        pHTTPHandler->AddFilter((IFilter*)(Pollen::cCanvasResFilter*)pCanvasResFilter);

        EA::AutoRefCount<Pollen::cBuddyModeFilter> pBuddyModeFilter =
            EDITOR_NEW("Pollinator/MVJ/BuddyModeFilter") Pollen::cBuddyModeFilter;
        pBuddyModeFilter->Init();
        pHTTPHandler->AddFilter((IFilter*)(Pollen::cBuddyModeFilter*)pBuddyModeFilter);

        if (Pollen::cAuthManager* pAuthManager = Pollen::AuthManager())
            pHTTPHandler->mpAuthenticator = pAuthManager->GetAuthenticator();

        PathString XHTMLDir(GetDataDir());
        XHTMLDir.append(L"/UI/XHTML");

        EA::AutoRefCount<cSPUIXHTMLFileResourceHandler> pFileHandler =
            EDITOR_NEW("UI/MVJ/FileHandler") cSPUIXHTMLFileResourceHandler(XHTMLDir);
        pResourceProvider->RegisterProtocolHandler(pFileHandler, true);
        pFileHandler->mExtensionMap[L"css"] = "text/css";
        pFileHandler->mExtensionMap[L"html"] = "text/html";
        pFileHandler->mExtensionMap[L"htm"] = "text/html";
        pFileHandler->mExtensionMap[L"bmp"] = "image/bmp";
        pFileHandler->mExtensionMap[L"gif"] = "image/gif";
        pFileHandler->mExtensionMap[L"jpg"] = "image/jpeg";
        pFileHandler->mExtensionMap[L"jpeg"] = "image/jpeg";
        pFileHandler->mExtensionMap[L"png"] = "image/png";
        pFileHandler->mExtensionMap[L"tga"] = "image/targa";

        EA::AutoRefCount<cSPUIXHTMLUTFResourceHandler> pUTFHandler =
            EDITOR_NEW("UI/MVJ/UTFResourceHandler") cSPUIXHTMLUTFResourceHandler;
        pResourceProvider->RegisterProtocolHandler(pUTFHandler, true);
        pUTFHandler->mTypeMap[0x2f7d0005] = "image/bmp";
        pUTFHandler->mTypeMap[0x2f7d0006] = "image/targa";
        pUTFHandler->mTypeMap[0x2f7d0002] = "image/jpeg";
        pUTFHandler->mTypeMap[0x2f7d0004] = "image/png";
        pUTFHandler->mTypeMap[0x0248f226] = "text/css";
        pUTFHandler->mTypeMap[0x065266b7] = "text/html";

        EA::AutoRefCount<cSPUIXHTMLDataURIHandler> pDataURIHandler =
            EDITOR_NEW("UI/MVJ/DataURIHandler") cSPUIXHTMLDataURIHandler;
        pResourceProvider->RegisterProtocolHandler(pDataURIHandler, true);

        if (sAppProperties->HasProperty(0x3e42efa) && sAppProperties->GetBool(0x3e42efa)) {
            eastl::string16 userDataDir;
            if (GetDirectory(0xa02151, userDataDir, 0)) {
                eastl::string16 cacheDir(userDataDir.c_str());
                cacheDir.append(L"MVJCache/");
                EA::AutoRefCount<EA::Internet::INetFileCache> pFileCache =
                    EDITOR_NEW("UI/MVJ/FileCache") EA::Internet::INetFileCache;
                pFileCache->SetCacheDirectory(cacheDir.c_str());
                pFileCache->SetCacheIniFileName(L"cacheDB.ini");
                if (pFileCache->Init()) {
                    pHTTPHandler->SetFileCache(pFileCache, false);
                    pHTTPHandler->EnableLastModifiedHeuristic(true, 0.2f);
                }
            }
        }

        AddGIFImport();
        EA::AutoRefCount<cXHTMLControlAppearance> pAppearance =
            EDITOR_NEW("UI/XHTML/XHTMLControlAppearance") cXHTMLControlAppearance;
        pAppearance->Init();
        SetXHTMLControlAppearance(pAppearance);
    }

    mCreatureAnimManager = CreateCreatureAnimManager();
    if (mCreatureAnimManager) {
        SetCreatureAnimManager(mCreatureAnimManager);
        if (!mCreatureAnimManager->Initialize(sAppProperties->GetBool(0x6dd5a65c))) {
            SetCreatureAnimManager(0);
            if (mCreatureAnimManager)
                mCreatureAnimManager->Dispose(true);
            mCreatureAnimManager = 0;
        }
    }

    mHintManager = EDITOR_NEW("UI/HintManager") cHintManager;
    mHintManager->InitHints();
    SetHintManager(mHintManager);

    EditorValidity::InitializeValidityData();
    mEditorBaker = CreateEditorBaker();
    mEditorBaker->Init();
    SetEditorBaker(mEditorBaker);

    mSwatchManager = EDITOR_NEW("Editor") cSPSwatchManager;
    mSwatchManager->Init();
    SetSwatchManager(mSwatchManager);

    PreloadLayout(EA::Hash::FNV1_String8("VerbIcons", 0x811c9dc5, 1));

    IWindow* pMainWindow = GetLayoutManager()->GetWorldMainWindow(0x5b598f9);
    mAssetBrowser = EDITOR_NEW("Editor") cSPUIAssetBrowser;
    mAssetBrowser->Init(pMainWindow, false);
    mAssetBrowser->SetVisibility(0, 0, 0);
    SetAssetBrowser(mAssetBrowser);

    pMainWindow = GetLayoutManager()->GetWorldMainWindow(0x5b598f9);
    mSporeGuide = EDITOR_NEW("Editor") cSPUIAssetBrowser;
    mSporeGuide->Init(pMainWindow, true);
    mSporeGuide->SetVisibility(0, 0, 0);
    SetSporeGuide(mSporeGuide);

    mEditorEffects = EDITOR_NEW("Editor") cSPEditorEffects;
    mEditorEffects->Init();
    SetEditorEffects(mEditorEffects);

    cEditorCamera* pCamera = CreateEditorCamera();
    pCamera->Init();
    SetEditorCamera(pCamera);

    SetEditorTuning(EDITOR_NEW("Editor") cEditorTuning);

    cEditorPartsDB* pPartsDB = EDITOR_NEW("Editor") cEditorPartsDB;
    pPartsDB->Init();
    SetEditorPartsDB(pPartsDB);

    cEditorRigblockDB* pRigblockDB = EDITOR_NEW("Editor") cEditorRigblockDB;
    pRigblockDB->Init();
    SetEditorRigblockDB(pRigblockDB);

    cContentValidationSummarizer* pContentSummarizer =
        EDITOR_NEW("Simulator/cContentValidationSummarizer") cContentValidationSummarizer;
    ObjectTemplateDB()->AddSummarizer(pContentSummarizer);
    cVehicleSummarizer* pVehicleSummarizer = EDITOR_NEW("Simulator/cVehicleSummarizer") cVehicleSummarizer;
    ObjectTemplateDB()->AddSummarizer(pVehicleSummarizer);
    cBuildingSummarizer* pBuildingSummarizer = EDITOR_NEW("Simulator/cBuildingSummarizer") cBuildingSummarizer;
    ObjectTemplateDB()->AddSummarizer(pBuildingSummarizer);

    mSkinPaintSystem = EDITOR_NEW("Skinner/PaintSystem") nSPSkinner::cPaintSystem;
    mSkinPaintSystem->Setup();
    SetSkinPaintSystem(mSkinPaintSystem);

    if (sAppProperties->mpBlock->mbCSAMode) {
        if (cObjectTemplateDB* pTemplateDB = ObjectTemplateDB())
            pTemplateDB->ReIndex(0, 0);
    }

    if (Thumbnail::cImportExport* pImportExport = Thumbnail::CreateImporterExporter()) {
        Thumbnail::SetImporterExporter(pImportExport);
        bool shipDirs = true;
        if (cmdLine.FindSwitch(L"devDirs", false, 0, 0) != -1)
            shipDirs = false;
        if (cmdLine.FindSwitch(L"shipDirs", false, 0, 0) != -1)
            shipDirs = true;
        pImportExport->Init(shipDirs);
    }

    EA::Clipboard::Clipboard* pClipboard = EDITOR_NEW("Editor") EA::Clipboard::Clipboard;
    pClipboard->SetId(1);
    pClipboard->Init();
    EA::Clipboard::SetClipboard(pClipboard);

    mHUD = EDITOR_NEW("UI") cHUD;
    mHUD->Init();
    SetHUD(mHUD);

    if (EA::Messaging::IMessageServer* pServer = MessageServer())
        mAutoMsgHandler.Register(pServer, this, kEditorSystemMessages, 3, 0);

    return true;
}
}  // namespace SP
