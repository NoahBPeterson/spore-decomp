// Slice s00614f20: SP::Pollen::cServerResponse (expat XML wrapper stream: end-tag handlers,
// ctor/dtor, Open, SetupDict and the static handler maps) with the eastl rbtree/vector_map
// instances it uses, plus small Pollen transaction classes (constructors/destructors and
// HandleResult overrides).
// Built /O2 /MD /Gy /TP (no /EHsc).
#include "types.h"
#include <intrin.h>
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_ReadWriteBarrier)
typedef unsigned int size_type;
typedef int off_type;
typedef unsigned __int64 u64;

struct XML_ParserStruct;
typedef XML_ParserStruct* XML_Parser;
struct XML_Memory_Handling_Suite { void* (*malloc_fcn)(size_t); void* (*realloc_fcn)(void*, size_t); void (*free_fcn)(void*); };
extern "C" {
int XML_Parse(XML_Parser p, const char* s, int len, int isFinal);
void XML_ParserFree(XML_Parser p);
XML_Parser XML_ParserCreate_MM(const char* enc, const XML_Memory_Handling_Suite* ms, const char* sep);   // 0x0090aed0
void XML_SetUserData(XML_Parser p, void* userData);                                                       // 0x009032e0
void XML_SetElementHandler(XML_Parser p, void (*start)(void*, const wchar_t*),
                           void (*end)(void*, const wchar_t*));                                          // 0x00903300
void XML_SetCharacterDataHandler(XML_Parser p, void (*h)(void*, const wchar_t*, int));                    // 0x00903320
int __cdecl wcscmp(const wchar_t*, const wchar_t*);
}
#pragma intrinsic(wcscmp)
inline void* operator new(unsigned int, void* p) { return p; }

void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0 (EASTL allocate)
void* EASTL_alloc(unsigned size, const char* name, int flags, int a, const char* file, int line);
void EASTL_free(void* p);

struct ResourceKey { uint32_t instanceID, typeID, groupID; ResourceKey() : instanceID(0), typeID(0), groupID(0) {} };

// --- wide strings (eastl::basic_string<wchar_t>) ---------------------------------------
extern wchar_t gEmptyString16[];   // 0x01667bac
inline size_type CharStrlen(const wchar_t* s) {
    const wchar_t* p = s;
    while (*p) ++p;
    return (size_type)(p - s);
}
template <typename T> inline const T& emin(const T& a, const T& b) { return (b < a) ? b : a; }
void* MemCopy(void* d, const void* s, size_type n);   // 0x011e0744 (memcpy thunk)
int StringCompare(const wchar_t* b1, const wchar_t* e1, const wchar_t* b2, const wchar_t* e2);  // 0x005e9260
const wchar_t* RFindFirstNotOf(const wchar_t* pEnd, const wchar_t* pBegin, const wchar_t* pSet, const wchar_t* pSetEnd);  // 0x00549840
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int mAllocator;
    enum { npos = (size_type)-1 };
    string16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    string16(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    string16(const string16& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
    ~string16() {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin) EASTL_free(mpBegin);
        }
    }
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
    void RangeInitialize(const wchar_t* p);                       // 0x00579a90 (string(const wchar_t*))
    void AllocateSelf(size_type n);                               // 0x00429760
    string16& erase(size_type position, size_type n);            // 0x004228e0
    size_type find_first_not_of(const wchar_t* p, size_type pos) const;   // 0x00579af0
    __forceinline size_type find_last_not_of(const wchar_t* p, size_type position, size_type n) const {
        const wchar_t* const pBegin = mpBegin;
        const size_type nLength = (size_type)(mpEnd - pBegin);
        if (nLength) {
            const wchar_t* pEnd = pBegin + emin(nLength - 1, position) + 1;
            const wchar_t* pResult = RFindFirstNotOf(pEnd, pBegin, p, p + n);
            if (pResult != pBegin)
                return (size_type)((pResult - 1) - pBegin);
        }
        return npos;
    }
    __forceinline size_type find_last_not_of(const wchar_t* p, size_type position = npos) const {
        return find_last_not_of(p, position, CharStrlen(p));
    }
    void resize(size_type n);                                     // 0x00429520
    void append(const wchar_t* b, const wchar_t* e);              // 0x00429580
    static int Compare(const wchar_t* a, const wchar_t* b, size_type n) {
        for (; n > 0; ++a, ++b, --n)
            if (*a != *b) return (*a < *b) ? -1 : 1;
        return 0;
    }
    // inlined (4-argument) compare
    __forceinline int compare_inl(const string16& x) const {
        const int n1 = (int)(mpEnd - mpBegin);
        const int n2 = (int)(x.mpEnd - x.mpBegin);
        const int nMin = emin(n1, n2);
        const int c = Compare(mpBegin, x.mpBegin, nMin);
        return c ? c : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0));
    }
    int compare(const string16& x) const { return StringCompare(mpBegin, mpEnd, x.mpBegin, x.mpEnd); }
};
// vector<string16> element constructor (out-of-line copy constructor at 0x0056e2d0)
struct StrElem { void Construct(const string16& s); };

struct less16 { bool operator()(const string16& a, const string16& b) const { return a.compare_inl(b) < 0; } };

struct StrPairMut {    // eastl::pair<string16, string16>
    string16 first;
    string16 second;
    StrPairMut(const string16& a, const string16& b);     // 0x0088c0d0
    ~StrPairMut() {}
};
struct StrPair {       // eastl::pair<string16 const, string16>
    string16 first;
    string16 second;
    StrPair(const StrPairMut& x);                      // 0x00614990
    ~StrPair() {}
};
StrPairMut MakeStrPair(string16 a, string16 b);        // 0x00614cc0

// --- vector_map<const wchar_t*, mem_fun_t<void, cServerResponse>, char16less> -----------
struct mem_fun_t {
    void* fn;
    int adj;
};
struct HandlerPair {
    const wchar_t* first;
    int pad;
    mem_fun_t second;
};
struct char16less {
    bool operator()(const wchar_t* a, const wchar_t* b) const { return wcscmp(a, b) < 0; }
};
struct HandlerRange { HandlerPair* first; HandlerPair* second; };
struct HandlerInsertResult { HandlerPair* first; bool second; HandlerInsertResult(HandlerPair* f, bool s) : first(f), second(s) {} };
HandlerPair* lower_bound(HandlerPair* first, HandlerPair* last, const wchar_t* const& value, char16less c);   // 0x00614a30
HandlerPair* CopyPairs(HandlerPair* first, HandlerPair* last, HandlerPair* dest);   // eastl::copy_impl do_copy 0x00705250

struct HandlerMap {
    HandlerPair* mpBegin;
    HandlerPair* mpEnd;
    HandlerPair* mpCapacity;
    int mAlloc;
    int pad4;
    char16less mCompare;     // +0x14
    HandlerRange equal_range(const wchar_t* const& k);             // 0x00614d20
    void reserve(size_type n);                                     // 0x00614c40
    HandlerPair* vector_insert(HandlerPair* pos, const HandlerPair& v);   // 0x00676370
    HandlerInsertResult insert(const HandlerPair& value);          // 0x00615080
    void clear() {
        HandlerPair* first = mpBegin;
        HandlerPair* last = mpEnd;
        CopyPairs(last, mpEnd, first);
        mpEnd -= (last - first);
    }
};
extern HandlerMap gStartHandlers;   // 0x015f5088
extern HandlerMap gEndHandlers;     // 0x015f5024
extern XML_Memory_Handling_Suite gXMLMemorySuite;   // 0x015f4e78
extern bool gbDictInit;             // 0x015f4e84

// --- rbtree<string16, pair<string16 const, string16>> ----------------------------------
struct RBNode {
    RBNode* right; RBNode* left; RBNode* parent; int mColor;   // low byte: color
    RBNode() : left(0), parent(0), mColor(0) {}
};
struct StrNode : RBNode { StrPair mValue; };
RBNode* RBTreeDecrement(RBNode* n);   // 0x009215c0
struct StrMapIter { StrNode* mpNode; };
struct StrInsertResult { StrNode* first; bool second; StrInsertResult(StrNode* f, bool s) : first(f), second(s) {} };
struct TrueTag {};
struct StrMap {
    char pad0[4];
    RBNode mAnchor;       // +4
    unsigned mnSize;      // +0x14
    int mAlloc;
    ~StrMap() { DoNukeSubtree((StrNode*)mAnchor.parent); }
    StrMap() {
        mAnchor.parent = 0;
        *(char*)&mAnchor.mColor = 0;
        mnSize = 0;
        mAnchor.right = &mAnchor;
        mAnchor.left = &mAnchor;
    }
    StrMapIter DoInsertValueImpl(RBNode* pNodeParent, const StrPair& value, bool bForceToLeft);   // 0x00614dc0
    StrInsertResult DoInsertValue(const StrPair& value, TrueTag);                                  // 0x00614f20
    void DoNukeSubtree(StrNode* pNode);                                                           // 0x00615110
    StrInsertResult insert(const StrPair& value) { return DoInsertValue(value, TrueTag()); }
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
    RefCountVBase() : mnRefCount(0) {}
};

namespace SP { namespace Pollen {
class cServerResponse : public RefCountVBase, public EA::IO::IStream {
public:
    int mnReturnCode;                 // +0xc (Code: 0 success, 1 failure, 2 error)
    StrMap mFieldDict;                // +0x10
    struct StrVec {
        string16* mpBegin; string16* mpEnd; string16* mpCapacity;
        StrVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
        void DoDestroyValues(string16* b, string16* e);   // 0x0084aad0
        ~StrVec() {
            DoDestroyValues(mpBegin, mpEnd);
            if (mpBegin) {
                if (((int*)mpBegin)[-1]) EASTL_free(mpBegin);
            }
        }
        void DoInsertValue(string16* pos, const string16& x);   // 0x00554c30
        void push_back(const string16& value) {
            if (mpEnd < mpCapacity) {
                string16* p = mpEnd++;
                if (p) ((StrElem*)p)->Construct(value);
            } else
                DoInsertValue(mpEnd, value);
        }
    } mAssetList;   // +0x2c
    char pad0[0x40 - 0x38];
    XML_Parser mpXMLParser;           // +0x40
    string16 mCharacterData;          // +0x44
    bool mbInResponse;                // +0x54
    bool mbOpen;                      // +0x55
    int mParseStatus;                 // +0x58
    int mnBytesRead;                  // +0x5c

    cServerResponse();                // 0x00615790
    virtual ~cServerResponse();       // 0x00615380
    virtual int AddRef();
    virtual int Release();
    virtual unsigned int GetType() const;
    virtual int GetAccessFlags() const;
    virtual int GetState() const;
    virtual bool Close();
    virtual size_type GetSize() const;
    virtual bool SetSize(size_type size);
    virtual off_type GetPosition(int positionType = 0) const;
    virtual bool SetPosition(off_type position, int positionType = 0);   // 0x006154c0
    virtual size_type GetAvailable() const;
    virtual size_type Read(void* pData, size_type nSize);                // 0x00615430
    virtual bool Flush();
    virtual bool Write(const void* pData, size_type nSize);

    bool Open();                                                         // 0x00615450
    void GetStatus();
    void StartPollinatorResponse();   // 0x00614930
    void EndPollinatorResponse();     // 0x00614940
    void Noop();                      // 0x00c2e4e0
    void DefaultEndTag(const wchar_t* tag);                              // 0x00615180
    const wchar_t* GetField(const wchar_t* name);                        // 0x00614e50
    void IDListElement();                                                // 0x00615520
    static void SetupDict();                                             // 0x006155f0
    static void CharacterData(cServerResponse* self, const wchar_t* s, int len);
    static void StartElement(cServerResponse* self, const wchar_t* name);
    static void EndElementHandler(cServerResponse* self, const wchar_t* name);   // 0x00615330
};
}}
using namespace SP::Pollen;

union PmfCast {
    void (cServerResponse::*pmf)();
    mem_fun_t m;
};
#define PMF_FN(p) (((PmfCast&)(p)).m.fn)
inline void SetHandler(HandlerPair& p, const wchar_t* name, void (cServerResponse::*pmf)()) {
    PmfCast c;
    c.pmf = pmf;
    p.second.fn = c.m.fn;
    p.second.adj = c.m.adj;
    p.first = name;
}

// @ 0x00614f20
StrInsertResult StrMap::DoInsertValue(const StrPair& value, TrueTag)
{
    less16 mCompare;
    StrNode* pCurrent = (StrNode*)mAnchor.parent;
    StrNode* pLowerBound = (StrNode*)&mAnchor;
    StrNode* pParent;
    bool bValueLessThanNode = true;
    while (pCurrent) {
        bValueLessThanNode = mCompare(value.first, pCurrent->mValue.first);
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (StrNode*)pCurrent->left;
        else
            pCurrent = (StrNode*)pCurrent->right;
    }
    pParent = pLowerBound;
    if (bValueLessThanNode) {
        if (pLowerBound != (StrNode*)mAnchor.left)
            pLowerBound = (StrNode*)RBTreeDecrement(pLowerBound);
        else {
        {
            const StrMapIter itResult(DoInsertValueImpl(pLowerBound, value, false));
            return StrInsertResult(itResult.mpNode, true);
        }
        }
    }
    if (StringCompare(pLowerBound->mValue.first.mpBegin, pLowerBound->mValue.first.mpEnd,
                      value.first.mpBegin, value.first.mpEnd) < 0) {
        const StrMapIter itResult(DoInsertValueImpl(pParent, value, false));
        return StrInsertResult(itResult.mpNode, true);
    }
    return StrInsertResult(pLowerBound, false);
}

// @ 0x00615080
HandlerInsertResult HandlerMap::insert(const HandlerPair& value)
{
    HandlerPair* const itEnd = mpEnd;
    HandlerPair* it = lower_bound(mpBegin, itEnd, value.first, mCompare);
    if (it != itEnd && !mCompare(value.first, it->first))
        return HandlerInsertResult(it, false);
    return HandlerInsertResult(vector_insert(it, value), true);
}

// @ 0x00615110
void StrMap::DoNukeSubtree(StrNode* pNode)
{
    while (pNode) {
        DoNukeSubtree((StrNode*)pNode->right);
        StrNode* pNodeLeft = (StrNode*)pNode->left;
        pNode->mValue.~StrPair();
        EASTL_free(pNode);
        pNode = pNodeLeft;
    }
}

// @ 0x00615180
void cServerResponse::DefaultEndTag(const wchar_t* tag)
{
    mCharacterData.erase(0, mCharacterData.find_first_not_of(L" \t\n\f\r", 0));
    mCharacterData.erase(mCharacterData.find_last_not_of(L" \t\n\f\r") + 1, (size_type)-1);
    mFieldDict.insert(MakeStrPair(string16(tag), mCharacterData));
}

// @ 0x00615330
void cServerResponse::EndElementHandler(cServerResponse* self, const wchar_t* name)
{
    HandlerRange r = gEndHandlers.equal_range(name);
    if (r.first == r.second || r.first == gEndHandlers.mpEnd) {
        self->DefaultEndTag(name);
        return;
    }
    typedef void (__thiscall *Fn)(void*);
    ((Fn)r.first->second.fn)((char*)self + r.first->second.adj);
}

// @ 0x00615380
cServerResponse::~cServerResponse()
{
    if (mbOpen) {
        mParseStatus = XML_Parse(mpXMLParser, 0, 0, 1);
        XML_ParserFree(mpXMLParser);
        mbOpen = false;
    }
}

// @ 0x00615430
size_type cServerResponse::Read(void* pData, size_type nSize)
{
    return (size_type)-1;
}

// @ 0x00615450
bool cServerResponse::Open()
{
    if (!mbOpen) {
        mpXMLParser = XML_ParserCreate_MM(0, &gXMLMemorySuite, 0);
        if (mpXMLParser) {
            XML_SetUserData(mpXMLParser, this);
            XML_SetElementHandler(mpXMLParser, (void (*)(void*, const wchar_t*))StartElement, (void (*)(void*, const wchar_t*))EndElementHandler);
            XML_SetCharacterDataHandler(mpXMLParser, (void (*)(void*, const wchar_t*, int))CharacterData);
            mbOpen = true;
            mParseStatus = 1;
            mnBytesRead = 0;
        }
    }
    return mbOpen;
}

// @ 0x006154c0
bool cServerResponse::SetPosition(off_type position, int positionType)
{
    if (positionType == 0) {
        if (position == mnBytesRead)
            return true;
        if (position == 0 && Close() && Open())
            return true;
    }
    return false;
}

// @ 0x00615520
void cServerResponse::IDListElement()
{
    mCharacterData.erase(0, mCharacterData.find_first_not_of(L" \t\n\f\r", 0));
    mCharacterData.erase(mCharacterData.find_last_not_of(L" \t\n\f\r") + 1, (size_type)-1);
    mAssetList.push_back(mCharacterData);
}

// @ 0x006155f0
void cServerResponse::SetupDict()
{
    HandlerPair p;
    gStartHandlers.clear();
    gStartHandlers.reserve(2);
    SetHandler(p, L"AssetIdList", &cServerResponse::Noop);
    gStartHandlers.insert(p);
    SetHandler(p, L"PollinatorResponse", &cServerResponse::StartPollinatorResponse);
    gStartHandlers.insert(p);
    gEndHandlers.clear();
    gEndHandlers.reserve(4);
    SetHandler(p, L"Id", &cServerResponse::IDListElement);
    gEndHandlers.insert(p);
    SetHandler(p, L"AssetIdList", &cServerResponse::Noop);
    gEndHandlers.insert(p);
    SetHandler(p, L"PollinatorResponse", &cServerResponse::EndPollinatorResponse);
    gEndHandlers.insert(p);
    SetHandler(p, L"Status", &cServerResponse::GetStatus);
    gEndHandlers.insert(p);
    gXMLMemorySuite.malloc_fcn = (void* (*)(size_t))0x6abeb0;
    gXMLMemorySuite.realloc_fcn = (void* (*)(void*, size_t))0x900b10;
    gXMLMemorySuite.free_fcn = (void (*)(void*))0xf47410;
    gbDictInit = true;
}

// @ 0x00615790
cServerResponse::cServerResponse()
    : mnReturnCode(2), mAssetList(), mpXMLParser(0), mbInResponse(false), mbOpen(false), mParseStatus(1), mnBytesRead(0)
{
    if (!gbDictInit)
        SetupDict();
}

// ===========================================================================================
// Pollen transactions
// ===========================================================================================
struct IResourceManager {
    virtual ~IResourceManager();
    virtual bool Initialize();
    virtual bool Dispose();
    virtual bool GetResource();
    virtual bool GetResourceAsync();
    virtual bool GetLoadedResource();
    virtual bool ReloadResource();
    virtual bool GetPrivateResource();
    virtual bool WriteResource(void* res, void* data, void* db, void* factory, void* name);   // 0x20
    virtual void SetTypeMapping();
    virtual int GetRecordTypesFromResourceType();
    virtual int GetTypeMapping();
    virtual int FindRecord();
    virtual int GetResourceKeyList();
    virtual int GetRecordKeyList();
    virtual int GetRecordKeyList2();
    virtual bool RegisterChangeNotification();
    virtual bool RegisterFactory();
    virtual int FindFactory();
    virtual int GetFactoryList();
    virtual bool RegisterDatabase();
    virtual bool IsDatabaseRegistered();
    virtual void* FindDatabase(const ResourceKey* name);                  // 0x58
    virtual int GetDatabaseList();
    virtual void DoDatabaseChanged();
    virtual bool RegisterCache();
    virtual int FindCache();
    virtual bool CacheResource(void* res, bool flag);                     // 0x6c
};
IResourceManager* GetManager();    // 0x0067dcd0
IResourceManager* GetManager2();   // 0x008de1a0

struct IMessageServer {
    virtual int slot00(); virtual int slot04(); virtual int slot08(); virtual int slot0c();
    virtual int slot10();
    virtual bool PostMessage(uint32_t id, void* data, int flag);   // 0x14
};
IMessageServer* GetMessageServer();   // EA::Messaging::GetServer 0x00883860

struct IFactory { virtual void slot0(); virtual int AddRef(); virtual int Release(); };
template <typename T> struct RefPtr {
    T* p;
    RefPtr() : p(0) {}
    void AssignOutOfLine(T* o);   // 0x00572620 (out-of-line AutoRefCount::operator=)
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

struct cAssetMetadata {                       // SP::Pollen::cAssetMetadata (resource)
    virtual int AddRef();
    virtual int Release();
    virtual int slot8();
    virtual void* Cast(uint32_t typeID);       // 0x0c
    ResourceKey* GetKey();                     // 0x005507c0
    uint32_t* GetServerID();                   // 0x005507a0
    int Fn5507e0(int a);                       // 0x005507e0
    int Fn5508c0(int a, int b);                // 0x005508c0
    int Fn414e10(int a);                       // 0x00414e10
    void Fn551240(ResourceKey* key, int c);    // 0x00551240
    void SetServerID(uint32_t lo, uint32_t hi);   // 0x00551af0
};
struct cAssetDirectory {
    void AddMapping(uint32_t lo, uint32_t hi, ResourceKey* key);   // 0x0054e250
};
struct cImportExport { int UpdateExportThumb(); };                // 0x005fb430
cImportExport* __stdcall GetImportExport(ResourceKey* key);        // 0x005f7930
void* __cdecl Fn6ac0a0(int a, void* b);                            // 0x006ac0a0
void* __cdecl Fn6ad010(void* a);                                   // 0x006ad010
u64 StrtoU64(const wchar_t* s, wchar_t** end, int base);           // 0x0092d710

struct cTransactionBase {
    virtual ~cTransactionBase() {}
    virtual int AddRef();
    virtual int Release();
    virtual bool HandleResult(int err, struct cHttpResult* r, struct cTransactionQueue* q);
    int mnRefCount;
    cTransactionBase() : mnRefCount(0) {}
};
struct cTransactionQueue {
    void Enqueue(cTransactionBase* t, bool b);      // 0x0060eaf0
};
struct cHttpResult {
    char pad[0xf3c];
    cServerResponse* mpResponse_unused;
};

void* AllocTransaction(unsigned size);   // 0x00615810 (operator new wrapper)
// class #1: asset upload transaction (0x30 bytes), constructed by cModelUploadTransaction retries
struct cAssetUploadTransaction : cTransactionBase {
    ResourceKey mKey;                 // +8
    cAssetMetadata* mpAssetMetadata;  // +0x14
    cAssetDirectory* mpAssetDir;      // +0x18
    int pad1c;
    u64 mnNextAssetID;                // +0x20
    bool mbA;                         // +0x28
    bool mbB;                         // +0x29
    unsigned mnRetries;               // +0x2c
    cAssetUploadTransaction(cAssetMetadata* m, cAssetDirectory* dir, bool a, bool b, unsigned n);   // 0x00615d30
    virtual bool HandleResult(int err, cHttpResult* r, cTransactionQueue* q);
    void* operator new(size_t n) { return AllocTransaction((unsigned)n); }
};
// class #2: model upload transaction (0x34 bytes)
struct cModelUploadTransaction : cTransactionBase {
    ResourceKey mKey;                 // +8
    cAssetMetadata* mpAssetMetadata;  // +0x14
    cAssetDirectory* mpAssetDir;      // +0x18
    int pad1c;
    union { u64 mnNextAssetID; struct { uint32_t mnNextLo, mnNextHi; }; };   // +0x20
    bool mbA;                         // +0x28
    bool mbB;                         // +0x29
    unsigned mnRetries;               // +0x2c
    bool mbDone;                      // +0x30
    cModelUploadTransaction(cAssetMetadata* m, cAssetDirectory* dir, bool a, bool b, unsigned n);   // 0x00615e50
    virtual bool HandleResult(int err, cHttpResult* r, cTransactionQueue* q);                        // 0x00615ed0
    void OnFailure();                                                                                // 0x00615db0
};

// @ 0x00615d30
cAssetUploadTransaction::cAssetUploadTransaction(cAssetMetadata* m, cAssetDirectory* dir, bool a, bool b, unsigned n)
    : mKey(), mpAssetDir(dir), mnNextAssetID((u64)-1)
{
    mbA = a;
    mbB = b;
    mpAssetMetadata = m;
    mnRetries = n;
    if (mpAssetMetadata) {
        mKey = *mpAssetMetadata->GetKey();
        mpAssetMetadata->AddRef();
    }
}

// @ 0x00615e50
cModelUploadTransaction::cModelUploadTransaction(cAssetMetadata* m, cAssetDirectory* dir, bool a, bool b, unsigned n)
    : mKey(), mpAssetDir(dir), mnNextAssetID((u64)-1)
{
    mbA = a;
    mbB = b;
    mpAssetMetadata = m;
    mnRetries = n;
    mbDone = false;
    if (mpAssetMetadata) {
        mKey = *mpAssetMetadata->GetKey();
        mpAssetMetadata->AddRef();
    }
}

// @ 0x00615db0
void cModelUploadTransaction::OnFailure()
{
    int a = mpAssetMetadata->Fn5507e0(0);
    int b = mpAssetMetadata->Fn5508c0(0, a);
    int c = mpAssetMetadata->Fn414e10(b);
    mpAssetMetadata->Fn551240(&mKey, c);
    cAssetMetadata* m = mpAssetMetadata;
    cAssetMetadata* x = m ? (cAssetMetadata*)m->Cast(0x2269ed1) : 0;
    void* db = GetManager2()->FindDatabase((ResourceKey*)((char*)x + 8));
    GetManager2()->WriteResource(x, 0, db, 0, 0);
    Fn6ac0a0(10, x);
    Fn6ad010(x);
    GetImportExport(mpAssetMetadata->GetKey())->UpdateExportThumb();
}

struct sUploadMsg { bool ok; ResourceKey key; };

// @ 0x00615ed0
bool cModelUploadTransaction::HandleResult(int err, cHttpResult* r, cTransactionQueue* q)
{
    bool result = false;
    RefPtr<IFactory>* pRef;
    if (err != 0) {
        if (!r) goto fail;
        pRef = (RefPtr<IFactory>*)((char*)r + 0xf3c);
        if (pRef->p) ((void (__thiscall*)(void*))(*(void***)pRef->p)[6])(pRef->p);
    } else {
        pRef = (RefPtr<IFactory>*)((char*)r + 0xf3c);
        cServerResponse* o = pRef->p ? (cServerResponse*)((char*)pRef->p - 8) : 0;
        EA::IO::IStream* s = (EA::IO::IStream*)((char*)o + 8);
        int state = s->GetState();
        s->Close();
        if (state == 0) {
            int code = o->mnReturnCode;
            const wchar_t* idText = o->GetField(L"next-id");
            if (idText)
                mnNextAssetID = StrtoU64(idText, 0, 10);
            result = true;
            if (code != 0) {
                if (mnRetries < 3) {
                    mpAssetMetadata->SetServerID(mnNextLo, mnNextHi);
                    GetManager()->WriteResource(mpAssetMetadata, 0, 0, 0, 0);
                    GetManager()->CacheResource(mpAssetMetadata, result);
                    GetImportExport(&mKey)->UpdateExportThumb();
                    mnNextLo = 0xffffffffu;
                    mnNextHi = 0xffffffffu;
                    cAssetUploadTransaction* t = new cAssetUploadTransaction(mpAssetMetadata, mpAssetDir, mbA, mbB, mnRetries + 1);
                    q->Enqueue(t, result);
                } else {
                    result = false;
                }
            } else {
                uint32_t* sid = mpAssetMetadata->GetServerID();
                uint32_t lo = sid[0];
                uint32_t hi = sid[1];
                mpAssetDir->AddMapping(lo, hi, &mKey);
                mbDone = result;
                sUploadMsg m;
                m.ok = result;
                m.key = mKey;
                GetMessageServer()->PostMessage(0x68cd252, &m, 0);
            }
        }
    }
    {
        IFactory* ref = pRef->p;
        if (ref) {
            pRef->p = 0;
            ref->Release();
        }
    }
    if (result) return result;
fail:
    mpAssetMetadata->SetServerID((uint32_t)-1, (uint32_t)-1);
    {
        cAssetMetadata* x = mpAssetMetadata ? (cAssetMetadata*)mpAssetMetadata->Cast(0x2269ed1) : 0;
        void* db = GetManager2()->FindDatabase((ResourceKey*)((char*)x + 8));
        GetManager2()->WriteResource(x, 0, db, 0, 0);
        Fn6ac0a0(10, x);
        Fn6ad010(x);
        GetImportExport(mpAssetMetadata->GetKey())->UpdateExportThumb();
        sUploadMsg m;
        m.ok = false;
        m.key = mKey;
        GetMessageServer()->PostMessage(0x68cd252, &m, 0);
    }
    return result;
}

// ===========================================================================================
// small helpers and classes
// ===========================================================================================
extern void* kVtbl13fc484[]; extern void* kVtbl13fc4a8[];
extern void* kVtbl13f1ab0[]; extern void* kVtbl140b5a0[]; extern void* kVtbl13ef094[];
extern void* kVtbl13fc4d4[]; extern void* kVtbl13fc4d0[]; extern void* kVtbl13fc4cc[];
extern void* kVtbl13eb938[]; extern void* kVtbl13fc4e4[]; extern void* kVtbl13fc508[];
extern void* kVtbl13fc52c[];

// object that writes a resource into its database and then notifies a listener
struct cSaveListener { void Notify(int a); };   // 0x0068f9b0
struct cResourceSaveRequest {
    char pad[0xc];
    void* mpResource;      // +0xc
    void* mpDatabase;      // +0x10
    ResourceKey mKey;      // +0x14
    bool Save(cSaveListener* l);   // 0x00615870
};

// @ 0x00615870
bool cResourceSaveRequest::Save(cSaveListener* l)
{
    bool r = GetManager()->WriteResource(mpResource, 0, mpDatabase, 0, &mKey);
    l->Notify(0);
    return r;
}

// a holder whose pointee has a secondary subobject at +4
struct SubIface { virtual int slot0(); virtual int ReleaseSub(); };
struct SubOwner { void* vtbl; SubIface sub; };
struct cSubHolder {
    SubOwner* mp;
    void ReleaseStream();                 // 0x00615bb0
};
// @ 0x00615bb0
void cSubHolder::ReleaseStream()
{
    if (mp) mp->sub.ReleaseSub();
}

// @ 0x00615c70
struct cThrottleObj : IFactory { int mnRef; cThrottleObj(); };    // 0x0093c430
struct cThrottleOwner { char pad[0x43c]; int mnCount; char pad2[0xf3c - 0x440]; RefPtr<IFactory> mpThrottle; };
bool __stdcall UpdateThrottle(cThrottleOwner* o)
{
    if (o) {
        int n = o->mnCount;
        if (n >= 400) {
            cThrottleObj* t = new ("Pollinator", 0, 0, 0, 0) cThrottleObj();
            o->mpThrottle = t;
        } else if (n >= 300) {
            cThrottleObj* t = new ("Pollinator", 0, 0, 0, 0) cThrottleObj();
            o->mpThrottle.AssignOutOfLine(t);
        }
        return true;
    }
    return false;
}

// @ 0x00616160 / 0x006161c0: a three-base resource object (vptrs at +0, +4, +8, refcount at +0xc)
struct cTripleObj {
    void** v0; void** v4; void** v8;
    volatile long mnRef;
    void* m10;                 // refcounted (slot 1 = Release)
    SubOwner* m14;             // owner with secondary subobject at +4
    int m18, m1c, m20;
    cTripleObj* Init();                 // 0x00616160
    cTripleObj* Destroy(unsigned flags);  // 0x006161c0
};
struct ReleasableIface { virtual int slot0(); virtual int ReleaseRef(); };

// @ 0x00616160
cTripleObj* cTripleObj::Init()
{
    v0 = kVtbl13f1ab0;
    v4 = kVtbl140b5a0;
    v8 = kVtbl13ef094;
    _InterlockedExchange(&mnRef, 0);
    v0 = kVtbl13fc4d4;
    v4 = kVtbl13fc4d0;
    v8 = kVtbl13fc4cc;
    m10 = 0;
    m14 = 0;
    m18 = 0;
    m1c = 0;
    m20 = 0;
    return this;
}

// @ 0x006161c0
cTripleObj* cTripleObj::Destroy(unsigned flags)
{
    v0 = kVtbl13fc4d4;
    v4 = kVtbl13fc4d0;
    v8 = kVtbl13fc4cc;
    _ReadWriteBarrier();
    if (m14) m14->sub.ReleaseSub();
    if (m10) ((ReleasableIface*)m10)->ReleaseRef();
    v8 = kVtbl13ef094;
    v0 = kVtbl13eb938;
    if (flags & 1) EASTL_free(this);
    return this;
}

// @ 0x00616220: ordering predicate over a table of 0x118-byte records (by 64-bit timestamp, descending)
struct sTimedRec { char pad[0x30]; __int64 mTime; char pad2[0x118 - 0x38]; };
struct sTimedOwner { char pad[0x60]; sTimedRec* mpTable; };
struct cTimeGreater {
    sTimedOwner* mpOwner;
    bool operator()(unsigned a, unsigned b) const;   // 0x00616220
};
bool cTimeGreater::operator()(unsigned a, unsigned b) const
{
    return mpOwner->mpTable[a].mTime > mpOwner->mpTable[b].mTime;
}

// @ 0x00616260
struct cSmallA {
    void** vtbl; int mnRef; int mA; int mB; bool mC;
    cSmallA* Init(int a, int b, bool c);   // 0x00616260
};
cSmallA* cSmallA::Init(int a, int b, bool c)
{
    mA = a;
    mnRef = 0;
    vtbl = kVtbl13fc4e4;
    mB = b;
    mC = c;
    return this;
}

// @ 0x006162a0
struct cHandlerStub {
    bool HandleResult(int err, cHttpResult* r, void* unused);   // 0x006162a0
};
bool cHandlerStub::HandleResult(int err, cHttpResult* r, void* unused)
{
    if (r) {
        IFactory* ref = ((RefPtr<IFactory>*)((char*)r + 0xf3c))->p;
        if (ref) ((void (__thiscall*)(void*))(*(void***)ref)[6])(ref);
    }
    bool result = false;
    if (err == 0) result = true;
    return result;
}

// @ 0x006162d0
struct cSmallB {
    void** vtbl; int mnRef; int mA; int mB;
    cSmallB* Init(int a, int b);
};
cSmallB* cSmallB::Init(int a, int b)
{
    mnRef = 0;
    vtbl = kVtbl13fc508;
    mA = a;
    mB = b;
    return this;
}

// @ 0x00616300
struct sTriple { int a, b, c; };
struct cSmallC {
    void** vtbl; int mnRef; IFactory* mpObj; int mC; sTriple mT; int m1c, m20;
    cSmallC* Init(const sTriple* t, int* obj, int c);
};
cSmallC* cSmallC::Init(const sTriple* t, int* obj, int c)
{
    mnRef = 0;
    vtbl = kVtbl13fc52c;
    mpObj = (IFactory*)obj;
    if (obj) ++obj[1];
    mC = c;
    mT = *t;
    m1c = 0;
    m20 = 0;
    return this;
}
