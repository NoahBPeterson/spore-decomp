// src/game/SPEditors/SPPollinatorTransactions.cpp -- migrated from slice(s) s0061d240, s0061c350, s0061b3b0, s0061a650, s006196c0, s00619150, s00618150, s00617130, s00616360, s00614f20 by tools/migrate/rewrite.py
// Object file: SPEditors/SPPollinatorTransactions.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include "EA/ResourceMan/Key.h"
#include "SP/Pollen/cAssetDirectory.h"
#include "EA/Audio/IPrimitive.h"
#include "SP/Pollen/cModelUploadTransaction.h"
#include "SP/Pollen/cServerResponse.h"
#include "SP/Pollen/cTransactionQueue.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
extern wchar_t gEmptyString16[];   // 0x01667bac
extern void* kVtbl13f1ab0[]; extern void* kVtbl140b5a0[]; extern void* kVtbl13ef094[];
extern void* kVtbl13fc4d4[]; extern void* kVtbl13fc4d0[]; extern void* kVtbl13fc4cc[];
extern void* kVtbl13fc52c[];
#include <intrin.h>
#include "EA/ResourceMan/Manager.h"
#include "EA/IO/FileStream.h"
#include "SP/cJob.h"
#include "SP/cJobManager.h"
#include "EA/Internet/HTTPRequest.h"
#include "SP/FunctionalMatch/Constraint.h"
#include "EA/ArgScript/cIParser.h"
#include "SP/Pollen/cFeedUnsubscribeTransaction.h"
#include "SP/Pollen/cGetAssetFeedTransaction.h"
#include "SP/Pollen/cSnapshotUploadTransaction.h"
#include "SP/Pollen/cTelemetryUploadTransaction.h"
#include <string.h>
#include "SP/Pollen/cEditFeedTransaction.h"
#include "SP/Pollen/cITransaction.h"
#include "SP/Pollen/cYouTubeAuthenticationTransaction.h"
#include "SP/Pollen/cYouTubeVideoURLTransaction.h"
#include "SP/Pollen/cYouTubeVideoUploadTransaction.h"
#include "EA/Internet/HTTPMultipartFormDataPostBodyStream.h"
#include "SP/Pollen/cAssetMetadata.h"
#include "EA/UTFWin/ISerializable.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/CustomWindow.h"
#include "EA/UTFWin/Message.h"
#include "EA/UTFWin/MultiHeapObject.h"
#include "SP/Pollen/cHandshakeTransaction.h"
#include "SP/cPollinator.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "SP/cStringTokenTranslator.h"
#include "SP/Pollen/cUserMatchTransaction.h"
#include "EA/UTFWin/CustomWinProc.h"
#include "EA/UTFWin/IWindow.h"
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_ReadWriteBarrier)
#pragma intrinsic(wcscmp)

// ---- items of slice s00614f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int size_type;
typedef int off_type;
typedef unsigned __int64 u64;
struct XML_ParserStruct_s0061_4f20;
typedef XML_ParserStruct_s0061_4f20* XML_Parser;
inline void* operator new(unsigned int, void* p) { return p; }
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0 (EASTL allocate)
void EASTL_free(void* p);
struct ResourceKey { uint32_t instanceID, typeID, groupID; ResourceKey() : instanceID(0), typeID(0), groupID(0) {} };
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
struct StrElem { void Construct(const string16& s); };
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
struct RBNode {
    RBNode* right; RBNode* left; RBNode* parent; int mColor;   // low byte: color
    RBNode() : left(0), parent(0), mColor(0) {}
};
struct StrNode : RBNode { StrPair mValue; };
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
namespace EA {
namespace IO {
class IStream_s0061_4f20 {
public:
    virtual ~IStream_s0061_4f20() {}
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
}
}
class RefCountVBase {
public:
    virtual ~RefCountVBase() {}
    virtual int AddRef();
    virtual int Release();
    int mnRefCount;
    RefCountVBase() : mnRefCount(0) {}
};
namespace SP {
namespace Pollen {
class cServerResponse_s0061_4f20 : public RefCountVBase, public EA::IO::IStream_s0061_4f20 {
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

    cServerResponse_s0061_4f20();                // 0x00615790
    virtual ~cServerResponse_s0061_4f20();       // 0x00615380
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
    void GetStatus();  // 0x00614ab0 (SP::Pollen::cServerResponse::GetStatus)
    void StartPollinatorResponse();   // 0x00614930
    void EndPollinatorResponse();     // 0x00614940
    void Noop();                      // 0x00c2e4e0
    void DefaultEndTag(const wchar_t* tag);                              // 0x00615180
    const wchar_t* GetField(const wchar_t* name);                        // 0x00614e50
    void IDListElement();                                                // 0x00615520
    static void SetupDict();                                             // 0x006155f0
    static void CharacterData(cServerResponse_s0061_4f20* self, const wchar_t* s, int len);
    static void StartElement(cServerResponse_s0061_4f20* self, const wchar_t* name);
    static void EndElementHandler(cServerResponse_s0061_4f20* self, const wchar_t* name);   // 0x00615330
};
}
}
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
struct cAssetMetadata_s0061_4f20 {                       // SP::Pollen::cAssetMetadata (resource)
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
struct cAssetDirectory_s0061_4f20 {
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
    virtual bool HandleResult(int err, struct cHttpResult* r, struct cTransactionQueue_s0061_4f20* q);
    int mnRefCount;
    cTransactionBase() : mnRefCount(0) {}
};
struct cTransactionQueue_s0061_4f20 {
    void Enqueue(cTransactionBase* t, bool b);      // 0x0060eaf0
};
struct cHttpResult {
    char pad[0xf3c];
    SP::Pollen::cServerResponse_s0061_4f20* mpResponse_unused;
};
void* AllocTransaction(unsigned size);   // 0x00615810 (operator new wrapper)
struct cAssetUploadTransaction : cTransactionBase {
    ResourceKey mKey;                 // +8
    cAssetMetadata_s0061_4f20* mpAssetMetadata;  // +0x14
    cAssetDirectory_s0061_4f20* mpAssetDir;      // +0x18
    int pad1c;
    u64 mnNextAssetID;                // +0x20
    bool mbA;                         // +0x28
    bool mbB;                         // +0x29
    unsigned mnRetries;               // +0x2c
    cAssetUploadTransaction(cAssetMetadata_s0061_4f20* m, cAssetDirectory_s0061_4f20* dir, bool a, bool b, unsigned n);   // 0x00615d30
    virtual bool HandleResult(int err, cHttpResult* r, cTransactionQueue_s0061_4f20* q);
    void* operator new(size_t n) { return AllocTransaction((unsigned)n); }
};
struct cModelUploadTransaction_s0061_4f20 : cTransactionBase {
    ResourceKey mKey;                 // +8
    cAssetMetadata_s0061_4f20* mpAssetMetadata;  // +0x14
    cAssetDirectory_s0061_4f20* mpAssetDir;      // +0x18
    int pad1c;
    union { u64 mnNextAssetID; struct { uint32_t mnNextLo, mnNextHi; }; };   // +0x20
    bool mbA;                         // +0x28
    bool mbB;                         // +0x29
    unsigned mnRetries;               // +0x2c
    bool mbDone;                      // +0x30
    cModelUploadTransaction_s0061_4f20(cAssetMetadata_s0061_4f20* m, cAssetDirectory_s0061_4f20* dir, bool a, bool b, unsigned n);   // 0x00615e50
    virtual bool HandleResult(int err, cHttpResult* r, cTransactionQueue_s0061_4f20* q);                        // 0x00615ed0
    void OnFailure();                                                                                // 0x00615db0
};
struct sUploadMsg { bool ok; ResourceKey key; };
struct SubIface { virtual int slot0(); virtual int ReleaseSub(); };
struct SubOwner { void* vtbl; SubIface sub; };
struct cTripleObj {
    void** v0; void** v4; void** v8;
    volatile long mnRef;
    void* m10;                 // refcounted (slot 1 = Release)
    SubOwner* m14;             // owner with secondary subobject at +4
    int m18, m1c, m20;
    cTripleObj* Init();                 // 0x00616160
    cTripleObj* Destroy(unsigned flags);  // 0x006161c0
};
struct sTimedRec { char pad[0x30]; __int64 mTime; char pad2[0x118 - 0x38]; };
struct sTimedOwner { char pad[0x60]; sTimedRec* mpTable; };
struct cTimeGreater {
    sTimedOwner* mpOwner;
    bool operator()(unsigned a, unsigned b) const;   // 0x00616220
};
struct cHandlerStub {
    bool HandleResult(int err, cHttpResult* r, void* unused);   // 0x006162a0
};
struct sTriple { int a, b, c; };
struct cSmallC {
    void** vtbl; int mnRef; IFactory* mpObj; int mC; sTriple mT; int m1c, m20;
    cSmallC* Init(const sTriple* t, int* obj, int c);
};
// ---- items of slice s00614f20 end

// ---- items of slice s00616360 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memset(void*, int, size_t);
extern void* kBaseVtbl[];             // 0x013ec458 (cITransaction base vtable)
extern void* kVtbl13fc52c[]; extern void* kVtbl13fc550[]; extern void* kVtbl13fc574[];
extern void* kVtbl13fc598[]; extern void* kVtbl13fc5bc[]; extern void* kVtbl13fc484[]; extern void* kVtbl13fc4a8[];
extern char gEmptyString8[];            // 0x01667bac
extern void* gFreeListA;   // 0x015f52e4
extern void* gFreeListB;   // 0x015f5194
extern void* gFreeListC;   // 0x015f51d8 (cAssetUploadTransaction pool)
extern void* gFreeListD;   // 0x015f5590 (cModelUploadTransaction pool)
extern void JobFn68f5a0();                // 0x0068f5a0
#pragma intrinsic(_InterlockedExchangeAdd)
void* EASTL_alloc(unsigned size, const char* name, int flags, int a, const char* file, int line);
struct ResourceKey_s0061_6360 { uint32_t instanceID, typeID, groupID; };
struct IAddRef {                      // refcounted: AddRef at +0, Release at +4
    virtual int AddRef();
    virtual int Release();
};
struct IAddRef1 {                     // AddRef at slot 1 (+4)
    virtual int s0();
    virtual int AddRef1();
};
struct IRel2 {                        // Release at slot 2 (+8)
    virtual int slot0();
    virtual int slot1();
    virtual int ReleaseSlot2();
};
struct IRel1 {                        // Release at slot 1 (+4)
    virtual int slot0();
    virtual int ReleaseSlot1();
};
struct RCObj {
    virtual void* Destroy(unsigned flags);
    int mnRef;
};
inline void RCRelease(RCObj* p)
{
    int n = (*(volatile int*)&p->mnRef += -1);
    if (n == 0) {
        p->mnRef = 1;
        _ReadWriteBarrier();
        p->Destroy(1);
    }
}
struct cHttpResult_s0061_6360 {
    char pad[0xf3c];
    IRel2* mpResponse;                // +0xf3c
};
struct cTxC {
    void** vtbl; int mnRef;
    RCObj* mpObj;                     // +8
    int m0c; int m10, m14, m18;
    IRel2* m1c;
    IRel1* m20;
    void Dtor();                      // 0x00616360
};
struct cTxD {
    void** vtbl; int mnRef;
    bool mb8; bool mb9;
    RCObj* mpCounted;                 // +0xc
    unsigned mnCount;                 // +0x10
    ResourceKey_s0061_6360 mKey;                 // +0x14
    IAddRef* mpRef;                   // +0x20
    IRel2* mpRel;                     // +0x24
    cTxD* Init(ResourceKey_s0061_6360 key, IAddRef* ref, RCObj* counted, unsigned n, bool b);   // 0x006163e0
    void Dtor();                      // 0x00616460
};
struct cTxE {
    void** vtbl; int mnRef;
    RCObj* mpObj;                     // +8
    int pad[5];
    IRel2* mpRel;                     // +0x20
    void Dtor();                      // 0x00616500
};
struct IResourceManager_s0061_6360 {
    virtual ~IResourceManager_s0061_6360();
    virtual bool Initialize();
    virtual bool Dispose();
    virtual bool GetResource(const ResourceKey_s0061_6360* key, void* dst, void* a, void* b, void* c, void* d);   // 0x0c
};
IResourceManager_s0061_6360* GetManager2_s0061_6360();   // 0x008de1a0
IMessageServer* GetMessageServer2();     // 0x00883860 (EA::Messaging::GetServer)
struct IWorkerObj { virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5(); virtual int s6(); virtual int s7(); virtual int s8(); virtual int s9(); virtual int s10(); virtual int s11(); virtual int s12(); virtual int s13(); virtual int s14(); virtual int s15(); virtual void Fn40(int v); };
struct IWorker {
    virtual int s0(); virtual int s1();
    virtual int ReleaseWorker();          // +8
    virtual int s3();
    virtual int Fn10();                   // +0x10
    virtual int s5(); virtual int s6();
    virtual IWorkerObj* Fn1c();           // +0x1c
    virtual int s8();
    virtual void Fn24();                  // +0x24
};
struct cTxF {
    void** vtbl; int mnRef; int pad[3];
    ResourceKey_s0061_6360 mKey;                     // +0x14
    IWorker* mpWorker;                    // +0x20
    bool HandleResult(int err, void* a, void* b);
};
struct cPollinatorLite { virtual int s0(); virtual int Notify(uint32_t id, void* data); };
cPollinatorLite* GetPollinatorLite();    // 0x0067cb30
struct IResp { virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5(); virtual int Close(); };
struct cTxG {
    void** vtbl; int mnRef; void* mp8; int mpC;
    bool HandleResult(int err, cHttpResult_s0061_6360* r, void* unused);   // 0x00616610
};
struct cTxI {
    bool HandleResult(int err, cHttpResult_s0061_6360* r, void* unused);
};
struct cTxJ {
    void** vtbl; int mnRef; IAddRef1* mp8; IAddRef1* mpC;
    cTxJ* Init(IAddRef1* a, IAddRef1* b);
};
struct IFnObj { virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5(); virtual void Fn18(); };
struct cHttpResult2 {
    char pad[0x43c];
    int mnStatus;                         // +0x43c
    char pad2[0xf3c - 0x440];
    IRel2* mpResponse;                    // +0xf3c
};
struct cTxK {
    void** vtbl; int mnRef; IFnObj* mp8; uint32_t mpC;
    bool HandleResult(int err, cHttpResult2* r, void* unused);
};
struct cTimeGreaterInl {
    sTimedOwner* mpOwner;
    bool operator()(unsigned a, unsigned b) const {
        return mpOwner->mpTable[a].mTime > mpOwner->mpTable[b].mTime;
    }
};
template <typename T> inline const T& emax(const T& a, const T& b) { return (a < b) ? b : a; }
struct string8 {
    char* mpBegin; char* mpEnd; char* mpCapacity; int mAllocator;
    void SetCapacity(size_type n);              // 0x0061c280
    string8& append(size_type n, char c);       // 0x00616960
    void AllocateSelf(size_type n);             // 0x00616aa0
    static size_type GetNewCapacity(size_type nCurrentCapacity) { return (nCurrentCapacity > 8) ? (2 * nCurrentCapacity) : 8; }
    void reserve(size_type n) {
        n = emax(n, (size_type)(mpEnd - mpBegin));
        if ((n + 1) > (size_type)(mpCapacity - mpBegin))
            SetCapacity(n + 1);
    }
};
struct cPoolTxA {
    void** vtbl;
    void* Destroy(unsigned flags);        // 0x00616b00
};
struct cPoolTxB {
    void** vtbl;
    void* Destroy(unsigned flags);        // 0x00616b20
};
struct cTxUp1 {                           // class "cAssetUploadTransaction"
    void** vtbl; int mnRef; IAddRef* pad8[3];
    IAddRef* mpAssetMetadata;             // +0x14
    void* Destroy(unsigned flags);        // 0x00616b40
};
struct cTxUp2 {                           // class "cModelUploadTransaction"
    void** vtbl; int mnRef; IAddRef* pad8[3];
    IAddRef* mpAssetMetadata;             // +0x14
    void* Destroy(unsigned flags);        // 0x00616d20
};
struct cServerResponseLite {              // SP::Pollen::cServerResponse (only what is used here)
    void* vtbl; int mnRef; void* vtblStream; int mnReturnCode;
    const wchar_t* GetField(const wchar_t* name);   // 0x00614e50
};
struct IStreamLite {
    virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4();
    virtual int GetState();               // +0x14
    virtual bool Close();                 // +0x18
};
struct cAssetMetadata {
    virtual int AddRef();
    virtual int Release();
    virtual int slot8();
    virtual void* Cast(uint32_t typeID);
    uint32_t* GetServerID();              // 0x005507a0
};
struct cAssetDirectory {
    void AddMapping(uint32_t lo, uint32_t hi, ResourceKey_s0061_6360* key);   // 0x0054e250
    bool GetServerId(const ResourceKey_s0061_6360* key, uint32_t* out, bool b);   // 0x0054e530
    void Fn54ed50(uint32_t lo, uint32_t hi, int a);                // 0x0054ed50
    void Fn54e7b0(uint32_t lo, uint32_t hi, int a);                // 0x0054e7b0
};
struct cTransactionQueue { void Enqueue(void* t, bool b); };        // 0x0060eaf0
struct cModelUploadTransactionLite {                                 // ctor 0x00615e50
    void* operator new(size_t n) { return AllocTransaction((unsigned)n); }
    cModelUploadTransactionLite(cAssetMetadata* m, cAssetDirectory* dir, bool a, bool b, unsigned n);
    char pad[0x38];
};
struct sUploadMsg_s0061_6360 { bool ok; ResourceKey_s0061_6360 key; };
struct cTxUpload {                                                  // cAssetUploadTransaction (retail 0x30 bytes)
    void** vtbl; int mnRef;
    ResourceKey_s0061_6360 mKey;                     // +8
    cAssetMetadata* mpAssetMetadata;      // +0x14
    cAssetDirectory* mpAssetDir;          // +0x18
    int pad1c;
    union { u64 mnNextAssetID; struct { uint32_t mnNextLo, mnNextHi; }; };   // +0x20
    bool mbA; bool mbB;                   // +0x28, +0x29
    unsigned mnRetries;                   // +0x2c
    bool HandleResult(int err, cHttpResult_s0061_6360* r, cTransactionQueue* q);       // 0x00616b80
};
struct cTripleObj_s0061_6360 {                       // three-base object, see slice s00614f20 (0x00616160)
    void** v0; void** v4; void** v8;
    volatile long mnRef;
    IAddRef* m10;                         // refcounted: AddRef +0, Release +4
    struct SubOwner_s0061_6360* m14;                 // object with refcounted subobject at +4
    ResourceKey_s0061_6360 m18;                      // +0x18
    cTripleObj_s0061_6360();                         // 0x00616160
};
struct SubIface_s0061_6360 {
    virtual int AddRefSub();
    virtual int ReleaseSub();
};
struct SubOwner_s0061_6360 { void* vtbl; SubIface_s0061_6360 sub; };
struct cJob {                             // SP::cJob
    void* mpFn; void* mp4; char pad[0x10]; int mnStatus;   // +0x18
    void Attach(cTripleObj_s0061_6360* o);           // 0x0068f9b0
    void Start();                         // 0x006909b0
    void Release();                       // 0x00690120 (smart pointer release)
};
struct cJobManager {
    virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3();
    virtual bool CreateJob(cJob** out);   // +0x10
};
cJobManager* GetJobManager();             // 0x0068f4d0
struct cAssetMetadataLite : IAddRef {
    virtual int slot2();
    virtual void* Cast(uint32_t typeID);  // +0x0c
};
struct cPollinatorDir { char pad[0x58]; cAssetDirectory* mpAssetDirectory; };
cPollinatorDir* GetPollinatorDir();       // 0x0067cb30
void __cdecl SetCachingType(int type, void* a);   // 0x006ac040
void* __cdecl GetSaveArea(uint32_t id);           // 0x006b1f90
struct cResponseObj {                     // cServerResponse: IStream subobject at +8
    char pad[8];
    IStreamLite stream;
};
struct cResponseRef {
    virtual int s0(); virtual int s1();
    virtual int ReleaseSlot2();
};
struct cTxDownload {
    void** vtbl; int mnRef; char pad8[8];
    ResourceKey_s0061_6360 mKey;                     // +0x10
    cResponseObj* mpResp;                 // +0x1c
    cAssetMetadataLite* mpMetadata;       // +0x20
    bool HandleResult(int err, void* a, void* b);   // 0x00616ed0
};
struct cFeedDoc {                         // SP::Feed::AtomDocument: entries of 0x118 bytes at +0x60..+0x64
    char pad[0x60];
    char* mpEntriesBegin;
    char* mpEntriesEnd;
};
struct IRecordLite {
    virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5();
    virtual void* GetStream();            // +0x18
};
struct IDatabase {
    virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5(); virtual int s6(); virtual int s7(); virtual int s8(); virtual int s9(); virtual int s10(); virtual int s11(); virtual int s12();
    virtual bool OpenRecord(const ResourceKey_s0061_6360* key, IRel2** pOut, int access, int createMode, int a, int b);   // +0x34
};
struct cHttpRequestRef {                  // EA::AutoRefCount<HTTPRequest> wrapper (out-of-line helpers)
    char* mp;
    void** GetAddressOf();                // 0x0060d240
    void Release();                       // 0x0060d210
};
bool __cdecl CreateHTTPGetRequest(const char* url, void* stream, void** ppOut);   // 0x00944450
struct cTxThumbnail {
    void** vtbl; int mnRef; char pad8[4];
    cFeedDoc* mpFeed;                     // +0xc
    unsigned mnEntryIndex;                // +0x10
    ResourceKey_s0061_6360 mAssetKey;                // +0x14 (instance, ?, group)
    int pad20;
    IRel2* mpRecord;                      // +0x24
    bool ConstructRequest(char** ppOut);   // 0x00617010
};
// ---- items of slice s00616360 end

// ---- items of slice s00617130 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* kVtbl13fc598[];
extern void* kVtbl13fc5bc[];
extern void* kVtbl13fc5e0[];
extern void* kVtbl13fc698[];
extern void* gFreeList15f52c4;
extern void* gFreeList15f5304;
extern void* kVtbl15206f0[];
#pragma intrinsic(_InterlockedDecrement)
void operator delete[](void* p);                                                    // 0x00f47380
struct ResourceKey_s0061_7130 { uint32_t instanceID, typeID, groupID; };
struct IRel2_s0061_7130 {                          // Release at slot 2 (+8)
    virtual int s0(); virtual int s1();
    virtual int ReleaseSlot2();
};
struct string8_s0061_7130 {
    char* mpBegin; char* mpEnd; char* mpCapacity; int mAllocator;
    string8_s0061_7130& append(size_type n, char c);               // 0x00616960
    void erase(char* first, char* last)
    {
        if (first != last) {
            memmove(first, last, (size_t)((mpEnd - last) + 1));
            mpEnd -= (last - first);
        }
    }
    void resize(size_type n, char c)
    {
        const size_type nLength = (size_type)(mpEnd - mpBegin);
        if (n < nLength)
            erase(mpBegin + n, mpEnd);
        else if (n > nLength)
            append(n - nLength, c);  // 0x00616960 (string8::append)
    }
    void Resize0(size_type n);                         // 0x006174e0
    ~string8_s0061_7130()
    {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin) operator delete[](mpBegin);
        }
    }
};
void __cdecl MapLookup(uint32_t hash, string8_s0061_7130* out);       // 0x00621460 (SP::Pollen::MapLookup)
inline void FreeCountedArray(void* p)
{
    if (p && ((int*)p)[-1] != 0) operator delete[](p);
}
struct cTelemetryUploadTransaction {
    void** vtbl; int mnRef;
    IRel2_s0061_7130* mpTelemetryStream;               // +8
    void* Destroy(unsigned flags);          // 0x00617450
};
struct cPollenTxTwoRefs {
    void** vtbl; int mnRef;
    IRel2_s0061_7130* mp8;
    IRel2_s0061_7130* mpC;
    void* Destroy(unsigned flags);          // 0x00617490
};
void promote_heap(unsigned* first, int topPosition, int position, const unsigned value, cTimeGreaterInl compare);   // 0x00616a00
struct IObj {                           // refcounted resource: AddRef +4, Release +8 (slot 1 / slot 2)
    virtual int s0();
    virtual int AddRef();
    virtual int Release();
    virtual void* Cast(uint32_t typeID);    // +0x0c
};
struct IObj4 {                          // refcounted: Release at +4 (slot 1)
    virtual int s0();
    virtual int Release4();
    virtual int s2();
    virtual void* Cast(uint32_t typeID);    // +0x0c
};
struct IDb {
    virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5(); virtual int s6();
    virtual bool Fn1c(void* obj, void** pOut, int a, uint32_t b);                  // +0x1c
    virtual int s8(); virtual int s9(); virtual int s10(); virtual int s11(); virtual int s12();
    virtual bool OpenRecord(const ResourceKey_s0061_7130* key, void** pOut, int a, int b, int c, int d);   // +0x34
};
struct IResMgr {
    virtual int s0(); virtual int s1(); virtual int s2();
    virtual bool GetResource(const ResourceKey_s0061_7130* key, void** pOut, int a, int b, int c, int d);   // +0x0c
    virtual int s4(); virtual int s5(); virtual int s6(); virtual int s7();
    virtual void Fn20(void* obj, int a, void* area, int b, int c);                  // +0x20
    virtual int s9(); virtual int s10(); virtual int s11(); virtual int s12(); virtual int s13(); virtual int s14();
    virtual int s15(); virtual int s16(); virtual int s17();
    virtual IDb* FindDatabase(uint32_t id, int flags);                              // +0x48
    virtual int s19(); virtual int s20(); virtual int s21();
    virtual IDb* FindDatabaseByKey(const ResourceKey_s0061_7130* key);                        // +0x58
};
IResMgr* GetManager_s0061_7130();                  // 0x0067dcd0
struct cAssetDirectory_s0061_7130 {
    bool GetServerId(const ResourceKey_s0061_7130* key, uint32_t* out, bool b);   // 0x0054e530
    bool GetLocalKey(uint32_t lo, uint32_t hi, ResourceKey_s0061_7130* out);      // 0x0054e460
    void Fn54e7b0(uint32_t lo, uint32_t hi, int a);                    // 0x0054e7b0
    void Fn54e8c0(uint32_t a, uint32_t lo, uint32_t hi);               // 0x0054e8c0
    u64 Fn54e8f0(uint32_t a);                                          // 0x0054e8f0
    void Fn54eb10(const ResourceKey_s0061_7130* key, int a);                      // 0x0054eb10
};
struct cPollinatorDir_s0061_7130 { char pad[0x58]; cAssetDirectory_s0061_7130* mpAssetDirectory; };
cPollinatorDir_s0061_7130* GetPollinatorDir_s0061_7130();     // 0x0067cb30
struct cPollinatorNotify { virtual int s0(); virtual int Notify(uint32_t id, void* data); };
cPollinatorNotify* GetPollinatorNotify();   // 0x0067cb30 (same object)
struct cMeta {                          // SP::Pollen::cAssetMetadata (only RemoveFeedURI used)
    bool RemoveFeedURI(const string8_s0061_7130* uri);     // 0x00551ff0
};
void CreateDownloadJob(IObj* pDb, void* pOwner, const ResourceKey_s0061_7130* pKey);   // 0x00616d60 (defined in s00614f20/s00616360)
uint32_t __cdecl FNV1_String8(const char* s, uint32_t seed, int a);     // 0x00932e80
struct cHttpResult_s0061_7130 {
    char pad[0xf3c];
    IRel2_s0061_7130* mpResponse;                    // +0xf3c
};
struct ObjPtr {
    IObj4* mp;
    ObjPtr() : mp(0) {}
    IObj4** GetAddressOf()
    {
        IObj4* t = mp;
        if (t) {
            mp = 0;
            t->Release4();
        }
        return &mp;
    }
};
struct sFeedMsg {
    uint32_t hash;
    uint32_t minusOne;
    ResourceKey_s0061_7130 key;
};
static __forceinline void UnsubscribeAsset(const ResourceKey_s0061_7130& src, const string8_s0061_7130* uri, sFeedMsg* msg, const ResourceKey_s0061_7130& orig)
{
    ResourceKey_s0061_7130 k = src;
    k.typeID = 0x30bdee3;
    ObjPtr p;
    IResMgr* m = GetManager_s0061_7130();
    if (m->GetResource(&k, (void**)p.GetAddressOf(), 0, 0, 0, 0)) {
        cMeta* meta = p.mp ? (cMeta*)p.mp->Cast(0x30bdee3) : 0;
        if (meta->RemoveFeedURI(uri)) {
            *(ResourceKey_s0061_7130*)((char*)p.mp + 8) = k;
            void* area = GetSaveArea(0x11ac19d);
            SetCachingType(10, p.mp);
            Fn6ad010(p.mp);
            CreateDownloadJob((IObj*)p.mp, area, 0);
            msg->key = orig;
            GetMessageServer2()->PostMessage(0x64e331c, msg, 0);
        }
    }
    if (p.mp) p.mp->Release4();
}
struct hnode { uint32_t lo, hi; hnode* next; };
struct cPendingAssetSet {
    int pad4;
    hnode** mpBucketArray;                // +4
    unsigned mnBucketCount;               // +8
};
namespace FunctionalMatch {
struct Constraint {
    Constraint(uint32_t dummy);                                    // 0x00558830
    Constraint(uint32_t property, uint32_t op, uint32_t value);   // 0x00558960
    char data[0x10];
    struct SubVec {
        Constraint* mpBegin; Constraint* mpEnd; Constraint* mpCapacity; int mAlloc;
    } mSubConstraints;
    uint32_t mFlags;
    ~Constraint()                                                  // 0x006066f0
    {
        for (Constraint* p = mSubConstraints.mpBegin; p < mSubConstraints.mpEnd; ++p)
            p->~Constraint();
        FreeCountedArray(mSubConstraints.mpBegin);
    }
};
}
struct KeyVec { ResourceKey_s0061_7130* mpBegin; ResourceKey_s0061_7130* mpEnd; ResourceKey_s0061_7130* mpCapacity; };
struct sTemplateDB {
    void** vtbl;
};
sTemplateDB* ObjectTemplateDB();                  // 0x0067cb40
typedef void (__cdecl *QueryFn)(sTemplateDB*, KeyVec*, FunctionalMatch::Constraint, FunctionalMatch::Constraint);
struct cGetAssetFeedTransaction {
    void** vtbl; int mnRef;
    RCObj* mpFeed;                        // +8
    int pad[4];
    string8_s0061_7130 mUrl;                         // +0x1c
    int pad2[1];
    char* mpEntries;                      // +0x30
    void Dtor();                          // 0x00617a40
};
struct HTTPRequest {                    // EA::Internet::HTTPRequest (refcount at +4)
    virtual ~HTTPRequest();
    volatile long mnRef;
    char pad[0xd94 - 8];
    void** mpHandlerVtbl;               // +0xd94
    bool AddHeader(const char* name, const char* value);     // 0x00944660
    void Release()
    {
        long rc = _InterlockedDecrement(&mnRef);
        if (rc == 0) {
            _InterlockedExchange(&mnRef, 1);
            delete this;
        }
    }
};
struct StreamObj { StreamObj* Ctor(); };                       // 0x0093c430 (thiscall ctor)
bool __cdecl CreateHTTPGetRequest(const char* url, void* stream, HTTPRequest** ppOut);   // 0x00944450
struct HttpReqRef {
    HTTPRequest* mp;
    void Dtor();                                  // 0x0060d210 (out of line release)
    HTTPRequest** GetAddressOutOfLine();          // 0x0060d240
    HTTPRequest** GetAddressOf()
    {
        HTTPRequest* p = mp;
        if (p) {
            mp = 0;
            p->Release();
        }
        return &mp;
    }
};
struct cFeedGetTx {
    void** vtbl; int mnRef;
    string8_s0061_7130 mUri;                         // +8
    bool ConstructRequestA(HTTPRequest** ppOut);   // 0x00617b10
    bool ConstructRequestB(HTTPRequest** ppOut);   // 0x00617c90
};
static __forceinline bool BuildGetRequest(cFeedGetTx* self, uint32_t mapId, HTTPRequest** ppOut)
{
    if (self->mUri.mpBegin != self->mUri.mpEnd) {
        string8_s0061_7130 url;
        url.mpBegin = gEmptyString8;
        url.mpEnd = gEmptyString8;
        url.mpCapacity = gEmptyString8 + 1;
        MapLookup(mapId, &url);
        HttpReqRef req;
        req.mp = 0;
        void* mem = operator new(8, "Pollinator", 0, 0, 0, 0);
        void* stream = mem ? ((StreamObj*)mem)->Ctor() : 0;
        if (CreateHTTPGetRequest(url.mpBegin, stream, req.GetAddressOf()) &&
            req.mp->AddHeader("uri", self->mUri.mpBegin)) {
            req.mp->mpHandlerVtbl = kVtbl15206f0;
            _InterlockedExchangeAdd(&req.mp->mnRef, 1);
            *ppOut = req.mp;
            req.Dtor();
            return true;
        }
        if (req.mp) req.mp->Release();
    }
    return false;
}
struct cFeedUnsubscribeTransaction {
    void** vtbl; int mnRef;
    string8_s0061_7130 mUri;                         // +8
    bool HandleResult(int err, cHttpResult_s0061_7130* r, void* unused);   // 0x00617e00
};
struct cSnapshotUploadTransaction {
    void** vtbl; int mnRef;
    ResourceKey_s0061_7130 mKey;                     // +8
    string8_s0061_7130 mMyEmailAddress;              // +0x14
    string8_s0061_7130 mDestinationEmailAddress;     // +0x24
    string8_s0061_7130 mMessageText;                 // +0x34
    string8_s0061_7130 mLocale;                      // +0x44
    void Dtor();                          // 0x00617e80
    bool ConstructRequest(HTTPRequest** ppOut);   // 0x00617f10
};
class HTTPMultipartFormDataPostBodyStream {
public:
    HTTPMultipartFormDataPostBodyStream* Ctor();   // 0x00946dc0
    virtual int s0();
    virtual int AddRef();
    virtual int Release();
    virtual int s3(); virtual int s4(); virtual int s5(); virtual int s6(); virtual int s7(); virtual int s8();
    virtual int s9(); virtual int s10(); virtual int s11(); virtual int s12(); virtual int s13(); virtual int s14();
    virtual int s15(); virtual int s16(); virtual int s17(); virtual int s18(); virtual int s19();
    virtual bool AddFile(const char* field, void* data, const char* contentType, const char* fileName, int flags);   // +0x50
    virtual bool AddField(const char* field, const char* value);                                                    // +0x54
};
struct cImageRequest {                      // Graphics::GraphicsFactoryAsyncRequest
    cImageRequest* Ctor(int a, int b, const char* name);       // 0x0093c270
    void SetProperty(int id, float v);                         // 0x0093bb40
};
struct IDbStream { virtual int s0(); virtual int s1(); virtual int ReleaseSlot2(); virtual int s3(); virtual int s4(); virtual int s5(); virtual void* GetStream(); };
struct IRefHolder {
    IDbStream* mp;
    IRefHolder* Reset()                                         // 0x00c463d0
    {
        IDbStream* o = mp;
        if (o) {
            mp = 0;
            o->ReleaseSlot2();
        }
        return this;
    }
};
bool __cdecl CreateHTTPPostRequest(const char* url, void* body, void* image, HTTPRequest** ppOut);   // 0x00945b20
// ---- items of slice s00617130 end

// ---- items of slice s00618150 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern char gEmptyString[];  // 0x01667bac (shared "" for char strings)
#pragma intrinsic(memcpy)
#pragma intrinsic(strlen)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file,
                   int line); // 0x00f473a0
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
namespace eastl {
struct allocator_s0061_8150 {
  allocator_s0061_8150() {}
};
}
namespace eastl {
template <typename T, typename A = allocator_s0061_8150>
struct basic_string_s0061_8150 {
  typedef unsigned int size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;
  basic_string_s0061_8150() : mpBegin(0), mpEnd(0), mpCapacity(0) {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  ~basic_string_s0061_8150() { DeallocateSelf(); }
  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin);
  }
  void DoFree(T* p) {
    if (p) EASTL_allocator_deallocate(p);
  }
  __forceinline explicit basic_string_s0061_8150(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) {
    const size_type n = (size_type)strlen(p);
    AllocateSelfN(n + 1);
    memcpy(mpBegin, p, n * sizeof(T));
    mpEnd = mpBegin + n;
    *mpEnd = 0;
  }
  __forceinline void AllocateSelfN(size_type n) {
    if (n > 1) {
      mpBegin = (T*)EASTL_allocator_allocate(
          n * sizeof(T), "Editor", 0, 0,
          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
          0xd1);
      mpEnd = mpBegin;
      mpCapacity = mpBegin + n;
    } else {
      mpBegin = (T*)gEmptyString;
      mpEnd = mpBegin;
      mpCapacity = mpBegin + 1;
    }
  }
  struct CtorZero {};
  basic_string_s0061_8150(CtorZero) : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  void RangeInit(const T* p);  // 0x0057cc10
  struct CtorDoNotInitialize {};
  basic_string_s0061_8150(CtorDoNotInitialize, size_type n) : mpBegin(0), mpEnd(0), mpCapacity(0) {
    AllocateSelf(n + 1);
    *mpEnd = 0;
  }
  void AllocateSelf(size_type n);                        // 0x00475ab0
  basic_string_s0061_8150& append(const T* pBegin, const T* pEnd);  // 0x00455d60
  basic_string_s0061_8150& append(const basic_string_s0061_8150& x) { return append(x.mpBegin, x.mpEnd); }
  basic_string_s0061_8150& append_sprintf_va_list(const T* pFormat, void* args);
  void set_capacity(size_type n);  // 0x006174e0
  basic_string_s0061_8150& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0 (char), 0x00423650 (wchar_t)
  basic_string_s0061_8150& operator=(const basic_string_s0061_8150& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  const T* c_str() const { return mpBegin; }
  size_type size() const { return (size_type)(mpEnd - mpBegin); }
};
}
typedef eastl::basic_string_s0061_8150<char> string8_s0061_8150;
namespace EA {
template <typename T>
class RefCountVTemplate_s0061_8150 {
 public:
  RefCountVTemplate_s0061_8150() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s0061_8150() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};  // namespace EA
}
namespace SP {
namespace Pollen {
class cITransaction_s0061_8150 : public EA::RefCountVTemplate_s0061_8150<int> {
 public:
  virtual ~cITransaction_s0061_8150() {}
};  // namespace Pollen
}
}
typedef eastl::basic_string_s0061_8150<wchar_t> string16_s0061_8150;
namespace SP {
namespace Pollen {
using namespace eastl;
}
}
namespace SP {
namespace Pollen {
class cYouTubeAuthenticationTransaction_s0061_8150 : public cITransaction_s0061_8150 {
 public:
  string8_s0061_8150 mUsername;  // +0x8
  string8_s0061_8150 mPassword;  // +0x18
  string8_s0061_8150 mSource;    // +0x28
  bool mCheckRegistration;
  virtual ~cYouTubeAuthenticationTransaction_s0061_8150();
  bool ConstructRequest(void** ppRequest);  // 0x006181c0 (SP::Pollen::cYouTubeAuthenticationTransaction::ConstructRequest)
};
}
}
namespace SP {
namespace Pollen {
class cYouTubeVideoURLTransaction_s0061_8150 : public cITransaction_s0061_8150 {
 public:
  string8_s0061_8150 mMyEmailAddress;           // +0x8
  string8_s0061_8150 mDestinationEmailAddress;  // +0x18
  string8_s0061_8150 mMessageText;              // +0x28
  string8_s0061_8150 mLocale;                   // +0x38
  virtual ~cYouTubeVideoURLTransaction_s0061_8150();
  bool ConstructRequest(void** ppRequest);
};
}
}
namespace SP {
namespace Pollen {
class cYouTubeVideoUploadTransaction_s0061_8150 : public cITransaction_s0061_8150 {
 public:
  string8_s0061_8150 mUsername;             // +0x8
  string8_s0061_8150 mClienID;              // +0x18
  string8_s0061_8150 mAuthenticationToken;  // +0x28
  string8_s0061_8150 mDeveloperKey;         // +0x38
  string8_s0061_8150 mVideoFilename;        // +0x48
  uint32_t mVideoKey[3];         // +0x58
  string8_s0061_8150 mXMLRequest;           // +0x64
  virtual ~cYouTubeVideoUploadTransaction_s0061_8150();
};
}
}
namespace SP {
namespace Pollen {
struct HTTPRequest_s0061_8150 {
  uint32_t vtbl;
  long mRefCount;  // +4
  uint32_t pad[0x2f4 / 4 - 2];
  uint32_t mHeaders[1];  // +0x2f4 (header map; see FUN_00944db0)
  uint32_t pad2[(0xd8c - 0x2f8) / 4];
  void* mpBodyStream;     // +0xd8c
  void* mpAsyncRequest;   // +0xd90
  uint32_t mCallbackVtbl;  // +0xd94
};
}
}
namespace SP {
namespace Pollen {
struct HttpRequestBody {  // base of the two body streams
  virtual ~HttpRequestBody();
  virtual int AddRef();   // +4
  virtual int Release();  // +8
};
}
}
namespace SP {
namespace Pollen {
#define PVS(n) virtual void pv##n();
}
}
namespace SP {
namespace Pollen {
struct UrlEncodedBody : HttpRequestBody {  // 0x28 bytes, ctor 0x00946c50
  uint32_t pad[9];
  UrlEncodedBody();
  PVS(3) PVS(4) PVS(5) PVS(6) PVS(7) PVS(8) PVS(9) PVS(10) PVS(11) PVS(12) PVS(13) PVS(14) PVS(15) PVS(16)
  PVS(17)
  virtual bool AddField(const char* name, const char* value);  // +0x48
};
}
}
namespace SP {
namespace Pollen {
struct MultipartBody : HttpRequestBody {  // 0x48 bytes, ctor 0x00946dc0
  uint32_t pad[17];
  MultipartBody();
  PVS(3) PVS(4) PVS(5) PVS(6) PVS(7) PVS(8) PVS(9) PVS(10) PVS(11) PVS(12) PVS(13) PVS(14) PVS(15) PVS(16)
  PVS(17) PVS(18) PVS(19) PVS(20)
  virtual bool AddField(const char* name, const char* value);  // +0x54
};
}
}
namespace SP {
namespace Pollen {
struct AsyncRequest {  // Graphics::GraphicsFactoryAsyncRequest, 0x24 bytes
  uint32_t pad[9];
  AsyncRequest(int a, int b, const char* typeName); // 0x0093c270
  void SetPriority(int mode, float f);  // 0x0093bb40
};
}
}
namespace SP {
namespace Pollen {
template <typename T>
struct Ref {
  T* mpObject;
  Ref(T* p) : mpObject(p) {
    if (mpObject) mpObject->AddRef();
  }
  ~Ref() {
    if (mpObject) mpObject->Release();
  }
  T* operator->() const { return mpObject; }
  operator bool() const { return mpObject != 0; }
};
}
}
namespace SP {
namespace Pollen {
struct ReqPtr {  // EA::AutoRefCount<HTTPRequest>
  HTTPRequest_s0061_8150* mpObject;
  ReqPtr() : mpObject(0) {}
  ~ReqPtr();                   // 0x0060d210
  HTTPRequest_s0061_8150** operator&();  // 0x0060d240
};
}
}
namespace SP {
namespace Pollen {
bool CreateHTTPPostRequest(const char* url, HttpRequestBody* body, AsyncRequest* async, HTTPRequest_s0061_8150** out);
}
}
namespace SP {
namespace Pollen {
void GetServiceURL(void* key, string8_s0061_8150* out);  // 0x00621460
}
}
namespace SP {
namespace Pollen {
extern int gYouTubeAuthURL, gYouTubeEmailURL;
}
}
namespace SP {
namespace Pollen {
struct IRefObj {
  virtual ~IRefObj();
  virtual int AddRef();
  virtual int Release();
};
}
}
namespace SP {
namespace Pollen {
struct IStreamLike : IRefObj {
  PVS(3) PVS(4) PVS(5) PVS(6) PVS(7) PVS(8) PVS(9) PVS(10)
  virtual int GetSize();  // +0x2c
};
}
}
namespace SP {
namespace Pollen {
struct Obj8 : IRefObj {  // 0x8 bytes, ctor 0x0093c430
  uint32_t pad;
  Obj8();
};
}
}
namespace SP {
namespace Pollen {
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
}
}
namespace SP {
namespace Pollen {
struct UploadRequest {  // retail HTTPRequest, size 0xd98, ctor 0x009442e0
  virtual ~UploadRequest();
  long mRefCount;  // +4
  uint32_t pad[0x2f4 / 4 - 2];
  uint32_t mHeaders[1];  // +0x2f4
  uint32_t pad2[(0xd8c - 0x2f8) / 4];
  IRefObj* mpBody;         // +0xd8c
  IRefObj* mpAsync;        // +0xd90
  uint32_t mCallbackVtbl;  // +0xd94
  UploadRequest();
  void SetMethod(int m);               // 0x009438c0
  void SetURL(const char* url);        // 0x00942f70
  void AddHeader(int id, const char* v);  // 0x00944db0 (on mHeaders)
  void AddRef() { _InterlockedExchangeAdd(&mRefCount, 1); }
  void Release() {
    long n = _InterlockedExchangeAdd(&mRefCount, -1);
    if (--n == 0) {
      _InterlockedExchange(&mRefCount, 1);
      delete this;
    }
  }
};
}
}
namespace SP {
namespace Pollen {
struct HeaderMap {
  void Add(int id, const char* v);  // 0x00944db0
};
}
}
namespace SP {
namespace Pollen {
int Sprintf8(char* dst, const char* fmt, ...);  // 0x00938470
}
}
namespace SP {
namespace Pollen {
struct IMessageServer_s0061_8150 {
  PVS(0) PVS(1) PVS(2) PVS(3) PVS(4)
  virtual void PostMSG(uint32_t id, void* p1, void* p2);  // +0x14
};
}
}
namespace SP {
namespace Pollen {
IMessageServer_s0061_8150* GetMessageServer_s0061_8150();  // 0x0067dcc0
}
}
namespace SP {
namespace Pollen {
extern uint32_t gMsgUploadFailed;    // 0x060ba744
}
}
namespace SP {
namespace Pollen {
class cUploadTransactionRetail {
 public:
  uint32_t pad[2];
  IStreamLike* mpStream;  // +0x8
  bool ConstructRequest(void** ppRequest);
};
}
}
int Vsnprintf8(char* dst, unsigned int cap, const char* fmt, void* args);  // 0x00938400
namespace eastl {
template <typename T>
inline const T& max_alt(const T& a, const T& b) { return a < b ? b : a; }  // namespace eastl
}
namespace SP {
namespace Pollen {
struct AtomEntry {  // 0x118 bytes
  uint32_t pad0[12];
  int64_t mKey;  // +0x30
  uint32_t pad1[(0xb8 - 0x38) / 4];
  const char* mURL;  // +0xb8
  uint32_t pad2[(0x118 - 0xbc) / 4];
};
}
}
namespace SP {
namespace Pollen {
struct AtomDocument {
  virtual ~AtomDocument();
  int mRefCount;  // +4
  uint32_t pad[(0x60 - 8) / 4];
  AtomEntry* mpEntriesBegin;  // +0x60
  AtomEntry* mpEntriesEnd;    // +0x64
  uint32_t pad2[(0xb8 - 0x68) / 4];
  void Release() {
    int n = (*(volatile int*)&mRefCount += -1);
    if (n == 0) {
      mRefCount = 1;
      delete this;
    }
  }
};
}
}
namespace SP {
namespace Pollen {
struct EntryKeyGreater {
  AtomDocument* mpDoc;
  bool operator()(unsigned int a, unsigned int b) const {
    return mpDoc->mpEntriesBegin[a].mKey > mpDoc->mpEntriesBegin[b].mKey;
  }
};
}
}
namespace SP {
namespace Pollen {
void AdjustHeap(unsigned int* first, int topPosition, int heapSize, int position, unsigned int value,
                EntryKeyGreater cmp);  // 0x00617530
}
}
namespace SP {
namespace Pollen {
struct NamedAlloc {
  uint32_t mName;
  NamedAlloc() {}
  NamedAlloc(const NamedAlloc& x) : mName(x.mName) {}
};
}
}
namespace SP {
namespace Pollen {
struct string8N {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  uint32_t mPad;
  NamedAlloc mAllocator;
  void AllocateSelf(unsigned int n);  // 0x00616aa0
  static char* CharStringUninitializedCopy(const char* pSource, const char* pSourceEnd, char* pDestination) {
    memcpy(pDestination, pSource, (unsigned int)(pSourceEnd - pSource));
    return pDestination + (pSourceEnd - pSource);
  }
  void RangeInitialize(const char* pBegin, const char* pEnd) {
    const unsigned int n = (unsigned int)(pEnd - pBegin);
    AllocateSelf(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
  // @ 0x00618af0
  string8N(const string8N& x);
};
}
}
namespace SP {
namespace Pollen {
struct IMsgBaseA {
  virtual void a0();
};
}
}
namespace SP {
namespace Pollen {
struct IMsgBaseB {
  IMsgBaseB() { _InterlockedExchange(&mRefCount, 0); }
  virtual void b0();
  long mRefCount;
};
}
}
namespace SP {
namespace Pollen {
struct cMsgString8 : IMsgBaseA, IMsgBaseB {
  string8_s0061_8150 mString;  // +0xc
  virtual int AddRef();
  virtual int Release();
  static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
  virtual ~cMsgString8();
  cMsgString8(const char* s) : mString(string8_s0061_8150::CtorZero()) { mString.RangeInit(s); }
};
}
}
unsigned int FNVHash(const char* s, unsigned int seed, int lowercase);  // 0x00932e80
int GetFeedTypeFromURI(const char* uri);                                // 0x005419c0
namespace SP {
namespace Pollen {
struct FeedAuthor {  // pointed to by FeedSource::mpAuthor
  uint32_t pad[2];
  string16_s0061_8150 mName;  // +0x8
  uint32_t mId0;   // +0x18
  uint32_t mId1;   // +0x1c
};
}
}
namespace SP {
namespace Pollen {
struct FeedSource {  // source record
  uint32_t pad0[2];
  string8_s0061_8150 mURI;       // +0x8
  uint32_t pad1[1];
  string16_s0061_8150 mTitle;    // +0x1c
  string16_s0061_8150 mDesc;     // +0x2c
  uint32_t pad2[1];
  uint32_t mKey[3];   // +0x40
  FeedAuthor* mpAuthor;  // +0x4c
  string8_s0061_8150 mExtra;     // +0x50
};
}
}
namespace SP {
namespace Pollen {
struct FeedInfo {  // destination record
  string16_s0061_8150 mAuthorName;  // +0x0
  uint32_t mAuthorId0;   // +0x10
  uint32_t mAuthorId1;   // +0x14
  string16_s0061_8150 mTitle;       // +0x18
  string16_s0061_8150 mDesc;        // +0x28
  uint32_t mKey[3];      // +0x38
  string8_s0061_8150 mExtra;        // +0x44
  string8_s0061_8150 mURI;          // +0x54
  uint32_t mURIHash;     // +0x64
  int mFeedType;         // +0x68
};
}
}
namespace SP {
namespace Pollen {
struct FixedPtrVector {  // fixed_vector<void*, 40> (+0x30 in the retail transaction)
  void** mpBegin;
  void** mpEnd;
  void** mpCapacity;
  uint32_t pad[2];
  uint32_t mOverflow;
  uint32_t mBuffer[40];
  FixedPtrVector() : mpBegin((void**)mBuffer), mpEnd((void**)mBuffer), mpCapacity((void**)mBuffer + 40), mOverflow(0) {}
};
}
}
namespace SP {
namespace Pollen {
class cFeedTransactionBase : public cITransaction_s0061_8150 {  // retail layout, size 0xec
 public:
  uint32_t mpFeed;       // +0x8
  uint32_t mFeedType;    // +0xc
  uint32_t mnIntParam;   // +0x10
  uint32_t mnCount;      // +0x14
  uint32_t mUnk18;       // +0x18
  string8_s0061_8150 mStringParam;  // +0x1c
  uint32_t pad28[1];
  FixedPtrVector mAssets;  // +0x30
  uint8_t mFlag;           // +0xe8
  cFeedTransactionBase(uint32_t type, uint32_t intParam, uint32_t count, uint32_t unk18);
  cFeedTransactionBase(uint32_t type, const char* str, uint32_t intParam);
  virtual ~cFeedTransactionBase();  // 0x00617a40
};
}
}
namespace SP {
namespace Pollen {
extern void* gFreeListGetAssetEx;  // 0x015f55b0
}
}
namespace SP {
namespace Pollen {
struct OwnedBuffer {
  void* mp;
  ~OwnedBuffer() {
    if (mp) EASTL_allocator_deallocate(mp);
  }
};
}
}
namespace SP {
namespace Pollen {
class cGetAssetFeedTransactionEx : public cFeedTransactionBase {
 public:
  uint32_t pad[(0xf8 - 0xec) / 4];
  OwnedBuffer mBuffer;  // +0xf8
  static void operator delete(void* p) {
    *(void**)p = gFreeListGetAssetEx;
    gFreeListGetAssetEx = p;
  }
  virtual ~cGetAssetFeedTransactionEx();
};
}
}
namespace SP {
namespace Pollen {
struct hash_set_u64 {  // eastl::hash_set<uint64_t>, size 0x20
  uint32_t mfRehash;      // +0
  void** mpBucketArray;   // +4
  uint32_t mnBucketCount;  // +8
  uint32_t mnElementCount;  // +0xc
  uint32_t pad[4];
  void DoFreeNodes(void** pArr, uint32_t n);  // 0x005687d0
  void clear() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
  }
  ~hash_set_u64() {
    clear();
    if (mnBucketCount > 1) EASTL_allocator_deallocate(mpBucketArray);
  }
};
}
}
namespace SP {
namespace Pollen {
template <typename T>
struct AutoRefDoc {
  T* mpObject;
  AutoRefDoc() : mpObject(0) {}
  void reset() {
    if (mpObject) {
      T* const pTemp = mpObject;
      mpObject = 0;
      pTemp->Release();
    }
  }
  ~AutoRefDoc() {
    if (mpObject) mpObject->Release();
  }
};
}
}
namespace SP {
namespace Pollen {
class cEditFeedTransaction_s0061_8150 : public cITransaction_s0061_8150 {
 public:
  AutoRefDoc<AtomDocument> mpFeed;  // +0x8
  uint32_t mOpType;                 // +0xc
  string8_s0061_8150 mFeedURI;                 // +0x10
  string8_s0061_8150 mFeedDescription;         // +0x20
  hash_set_u64 mAssetsToAdd;        // +0x30
  hash_set_u64 mAssetsToRemove;     // +0x50
  virtual ~cEditFeedTransaction_s0061_8150();
  bool ConstructRequest(void** ppRequest);  // 0x0061d960 (SP::Pollen::cEditFeedTransaction::ConstructRequest)
};
}
}
namespace SP {
namespace Pollen {
struct DownloadSession {  // 0x42d0 bytes, ctor 0x005cbec0
  uint32_t pad[0x42d0 / 4];
  DownloadSession();
  void Bind(void* target);  // 0x005cbd30
};
}
}
namespace SP {
namespace Pollen {
struct DownloadTarget {  // 0xac bytes, ctor 0x004b9c70
  uint32_t pad[0xac / 4];
  DownloadTarget();
};
}
}
namespace SP {
namespace Pollen {
struct TargetRef {  // EA::AutoRefCount<DownloadTarget>
  DownloadTarget* mp;
  void Set(DownloadTarget* p);  // 0x00b5f950
};
}
}
namespace SP {
namespace Pollen {
struct SessionRef {  // EA::AutoRefCount<DownloadSession>
  DownloadSession* mp;
  void Set(DownloadSession* p);  // 0x00572620
};
}
}
namespace SP {
namespace Pollen {
void* GetSaveArea(uint32_t id);  // 0x006b1f90
}
}
namespace SP {
namespace Pollen {
bool CreateHTTPGetRequest(const char* url, void* stream, HTTPRequest_s0061_8150** out);  // 0x00944450
}
}
namespace SP {
namespace Pollen {
struct HTTPRequestEx : HTTPRequest_s0061_8150 {
  void SetProperty(string8_s0061_8150* name, void* value);  // 0x00944a10
};
}
}
namespace SP {
namespace Pollen {
class cFeedEntryAssetTransaction : public cITransaction_s0061_8150 {
 public:
  AtomDocument* mpFeed;  // +0x8
  uint32_t mIndex;       // +0xc
  uint32_t mKey[3];      // +0x10
  SessionRef mSession;   // +0x1c
  TargetRef mTarget;     // +0x20
  bool ConstructRequest(void** ppRequest);
};
}
}
namespace SP {
namespace Pollen {
struct ReqPtrEx {
  HTTPRequestEx* mpObject;
  ReqPtrEx() : mpObject(0) {}
  ~ReqPtrEx();                  // 0x0060d210
  HTTPRequestEx** operator&();  // 0x0060d240
};
}
}
    void* operator new(unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
// ---- items of slice s00618150 end

// ---- items of slice s00619150 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
struct allocator_s0061_9150 {
  allocator_s0061_9150() {}
};
}
namespace eastl {
template <typename T, typename A = allocator_s0061_9150>
struct basic_string_s0061_9150 {
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;
  basic_string_s0061_9150() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  basic_string_s0061_9150(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInit(p); }
  ~basic_string_s0061_9150() {
    if ((mpCapacity - mpBegin) > 1) {
      if (mpBegin) EASTL_allocator_deallocate(mpBegin);
    }
  }
  void RangeInit(const T* p);  // 0x0057cc10
};
}
typedef eastl::basic_string_s0061_9150<char> string8_s0061_9150;
namespace EA {
template <typename T>
class RefCountVTemplate_s0061_9150 {
 public:
  RefCountVTemplate_s0061_9150() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s0061_9150() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};  // namespace EA
}
namespace SP {
namespace Pollen {
class cITransaction_s0061_9150 : public EA::RefCountVTemplate_s0061_9150<int> {
 public:
  virtual ~cITransaction_s0061_9150() {}
};
}
}
namespace SP {
namespace Pollen {
struct Key {
  uint32_t a, b, c;
};
}
}
namespace SP {
namespace Pollen {
extern void* gFree1;  // 0x015f53d4
}
}
namespace SP {
namespace Pollen {
extern void* gFree2;  // 0x015f5614
}
}
namespace SP {
namespace Pollen {
class cDeleteMyFeedTransaction_s0061_9150 : public cITransaction_s0061_9150 {
 public:
  string8_s0061_9150 mURI;  // +0x8
  cDeleteMyFeedTransaction_s0061_9150(const char* uri);
  static void operator delete(void* p) {
    *(void**)p = gFree1;
    gFree1 = p;
  }
  virtual ~cDeleteMyFeedTransaction_s0061_9150() {}
};
}
}
namespace SP {
namespace Pollen {
class cFeedUnsubscribeTransaction_s0061_9150 : public cITransaction_s0061_9150 {
 public:
  string8_s0061_9150 mURI;  // +0x8
  cFeedUnsubscribeTransaction_s0061_9150(const char* uri);
  static void operator delete(void* p) {
    *(void**)p = gFree2;
    gFree2 = p;
  }
  virtual ~cFeedUnsubscribeTransaction_s0061_9150() {}
};
}
}
namespace SP {
namespace Pollen {
class cSnapshotUploadTransaction_s0061_9150 : public cITransaction_s0061_9150 {
 public:
  Key mKey;                          // +0x8
  string8_s0061_9150 mMyEmailAddress;           // +0x14
  string8_s0061_9150 mDestinationEmailAddress;  // +0x24
  string8_s0061_9150 mMessageText;              // +0x34
  string8_s0061_9150 mLocale;                   // +0x44
  virtual ~cSnapshotUploadTransaction_s0061_9150() {}
  cSnapshotUploadTransaction_s0061_9150(const Key& key, const char* myEmail, const char* destEmail,
                             const char* message, const char* locale);
};
}
}
namespace SP {
namespace Pollen {
class cYouTubeAuthenticationTransaction_s0061_9150 : public cITransaction_s0061_9150 {
 public:
  string8_s0061_9150 mUsername;        // +0x8
  string8_s0061_9150 mPassword;        // +0x18
  string8_s0061_9150 mSource;          // +0x28
  bool mCheckRegistration;  // +0x38
  virtual ~cYouTubeAuthenticationTransaction_s0061_9150() {}
  cYouTubeAuthenticationTransaction_s0061_9150(const char* username, const char* password, const char* source,
                                    bool check);
};
}
}
namespace SP {
namespace Pollen {
class cYouTubeVideoUploadTransaction_s0061_9150 : public cITransaction_s0061_9150 {
 public:
  string8_s0061_9150 mUsername;             // +0x8
  string8_s0061_9150 mClienID;              // +0x18
  string8_s0061_9150 mAuthenticationToken;  // +0x28
  string8_s0061_9150 mDeveloperKey;         // +0x38
  string8_s0061_9150 mVideoFilename;        // +0x48
  Key mVideoKey;                 // +0x58
  string8_s0061_9150 mXMLRequest;           // +0x64
  virtual ~cYouTubeVideoUploadTransaction_s0061_9150() {}
  cYouTubeVideoUploadTransaction_s0061_9150(const char* username, const char* clientID, const char* authToken,
                                 const char* devKey, const char* videoFilename, Key videoKey,
                                 const char* xmlRequest);
};
}
}
namespace SP {
namespace Pollen {
class cYouTubeVideoURLTransaction_s0061_9150 : public cITransaction_s0061_9150 {
 public:
  string8_s0061_9150 mMyEmailAddress;           // +0x8
  string8_s0061_9150 mDestinationEmailAddress;  // +0x18
  string8_s0061_9150 mMessageText;              // +0x28
  string8_s0061_9150 mLocale;                   // +0x38
  virtual ~cYouTubeVideoURLTransaction_s0061_9150() {}
  cYouTubeVideoURLTransaction_s0061_9150(const char* myEmail, const char* destEmail, const char* message,
                              const char* locale);
};
}
}
struct FeedDescription {
  uint32_t mData[0x70 / 4];
  FeedDescription();
  FeedDescription(const FeedDescription& x);
  FeedDescription& operator=(const FeedDescription& x);
};
struct sTimedRec_s0061_9150 {
  char pad[0x30];
  int64_t mTime;  // +0x30
  char pad2[0x118 - 0x38];
};
struct sTimedOwner_s0061_9150 {
  char pad[0x60];
  sTimedRec_s0061_9150* mpTable;
};
struct TimeGreater {
  sTimedOwner_s0061_9150* mpOwner;
  bool operator()(unsigned int a, unsigned int b) const {
    return mpOwner->mpTable[a].mTime > mpOwner->mpTable[b].mTime;
  }
};
void AdjustHeap(unsigned int* first, int topPosition, int heapSize, int position, unsigned int value,
                TimeGreater cmp);  // 0x00617530
void MakeHeap(unsigned int* first, unsigned int* last, TimeGreater cmp);   // 0x00618a60
void SortHeap(unsigned int* first, unsigned int* last, TimeGreater cmp);  // 0x00618aa0
// ---- items of slice s00619150 end

// ---- items of slice s006196c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned size, const char* name, int a, int b, const char* file, int line);    // 0x00f473a0
namespace eastl {
struct allocator_s0061_96c0 {
  allocator_s0061_96c0() {}
};
}
namespace eastl {
template <typename T, typename A = allocator_s0061_96c0>
struct basic_string_s0061_96c0 {
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;
  basic_string_s0061_96c0() : mpBegin(gEmptyString8), mpEnd(gEmptyString8), mpCapacity(gEmptyString8 + 1) {}
  explicit basic_string_s0061_96c0(const char* s) : mpBegin(0), mpEnd(0), mpCapacity(0) {
    unsigned n = (unsigned)strlen(s);
    mpBegin = (char*)operator new(n + 1, "Editor", 0, 0,
                                  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                                  0xd1);
    mpCapacity = mpBegin + n + 1;
    memcpy(mpBegin, s, n + 1);
    mpEnd = mpBegin + n;
  }
  ~basic_string_s0061_96c0() {
    if ((mpCapacity - mpBegin) > 1) {
      if (mpBegin) operator delete[](mpBegin);
    }
  }
  static basic_string_s0061_96c0& sprintf(basic_string_s0061_96c0* s, const char* fmt, ...);         // 0x00472fe0 (cdecl)
  static basic_string_s0061_96c0& append_sprintf(basic_string_s0061_96c0* s, const char* fmt, ...);  // 0x005f9450 (cdecl)
};
}
typedef eastl::basic_string_s0061_96c0<char> string8_s0061_96c0;
namespace EA {
template <typename T>
class RefCountVTemplate_s0061_96c0 {
 public:
  RefCountVTemplate_s0061_96c0() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s0061_96c0() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
template <typename T>
struct RefPtr_s0061_96c0 {
  T* p;
  RefPtr_s0061_96c0() : p(0) {}
  RefPtr_s0061_96c0(T* v) : p(v) { if (v) v->AddRef(); }
  ~RefPtr_s0061_96c0() { if (p) p->Release(); }
  void assign(T* v) {
    T* old = p;
    if (v) v->AddRef();
    p = v;
    if (old) old->Release();
  }
  RefPtr_s0061_96c0* Reset() {  // 0x00c463d0: release and zero, return this (used as an out-parameter)
    T* o = p;
    if (o) {
      p = 0;
      o->Release();
    }
    return this;
  }
};
}
namespace EA {
namespace Internet {
class HTTPMultipartFormDataPostBodyStream_s0061_96c0 {
 public:
  HTTPMultipartFormDataPostBodyStream_s0061_96c0();  // 0x00946dc0
  virtual ~HTTPMultipartFormDataPostBodyStream_s0061_96c0() {}
  virtual int AddRef();  // 0x00768530 (EA::Internet::HTTPMultipartFormDataPostBodyStream::AddRef)
  virtual int Release();  // 0x0067da30 (EA::Internet::HTTPMultipartFormDataPostBodyStream::Release)
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void Abort();
  virtual void v7();
  virtual void v8();
  virtual void v9();
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
  virtual bool AddFile(const char* field, void* data, const char* contentType, const char* fileName, int flags);
  virtual bool AddField(const char* field, const char* value);
};  // namespace Internet
}
}
namespace SP {
namespace Pollen {
struct IResponseHandler {  // sub-object at cServerResponse+8 (slot 1 AddRef, slot 2 Release)
  virtual ~IResponseHandler() {}
  virtual int AddRef();
  virtual int Release();
};
}
}
namespace SP {
namespace Pollen {
class cServerResponse_s0061_96c0 : public EA::RefCountVTemplate_s0061_96c0<int> {
 public:
  cServerResponse_s0061_96c0();  // 0x00615790
  bool Open();        // 0x00615450
  IResponseHandler mHandler;  // +8
};
}
}
namespace EA {
namespace Internet {
class HTTPRequest_s0061_96c0 {
 public:
  virtual ~HTTPRequest_s0061_96c0();
  int mRefCount;      // +4
  uint32_t pad[0x362];
  RefPtr_s0061_96c0<SP::Pollen::IResponseHandler> mpHandler;  // +0xd90
  const void* mpCallbacks;                          // +0xd94
  void SetField(const char* name, const char* value);        // 0x00944660
  void SetFieldStr(const string8_s0061_96c0& name, const string8_s0061_96c0& value);  // 0x00944a10
  static bool CreateHTTPPostRequest(const char* url, HTTPMultipartFormDataPostBodyStream_s0061_96c0* body, int flags,
                                    struct HTTPRequestRef* out);  // 0x00945b20 (cdecl)
};
}
}
namespace EA {
namespace Internet {
struct HTTPRequestRef {
  HTTPRequest_s0061_96c0* p;
  HTTPRequestRef() : p(0) {}
  HTTPRequestRef* Reset() {
    HTTPRequest_s0061_96c0* o = p;
    if (o) {
      p = 0;
      if (_InterlockedExchangeAdd((volatile long*)&o->mRefCount, -1) == 1) delete o;
    }
    return this;
  }
  ~HTTPRequestRef() { Reset(); }
  void AddRef() { _InterlockedExchangeAdd((volatile long*)&p->mRefCount, 1); }
};
}
}
struct ResKey {
  uint32_t mInstance, mType, mGroup;
  ResKey() : mInstance(0), mType(0), mGroup(0) {}
};
struct IResource {  // slot 1 = Release
  virtual int v0();
  virtual int Release();
};
class IThumbData : public EA::RefCountVTemplate_s0061_96c0<int> {  // slot 6 returns the PNG buffer
 public:
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void* GetBuffer();
};
class IRecordSource {
 public:
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual bool ReadInto(IResource* res, struct ResourceReadRequest* req, int a, uint32_t type);  // slot 10
  virtual void v11(); virtual void v12();
  virtual bool GetThumb(const ResKey* key, EA::RefPtr_s0061_96c0<IThumbData>* out, int a, int b, int c, int d);  // slot 13
};
class IResourceManager_s0061_96c0 {
 public:
  virtual void v0(); virtual void v1(); virtual void v2();
  virtual bool GetResource(const ResKey* key, IResource** out, int a, int b, int c, int d);  // slot 3
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void SaveResource(void* resource, int a, int b, int c, int d);  // slot 8
  virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
  virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
  virtual IRecordSource* GetDatabase(uint32_t type, int group);  // slot 18
  virtual void v19(); virtual void v20(); virtual void v21();
  virtual IRecordSource* FindSource(const ResKey* key);  // slot 22
};
namespace EA {
namespace ResourceMan {
 IResourceManager_s0061_96c0* GetManager_s0061_96c0();   // 0x0067dcd0
}
}
namespace Graphics {
class GraphicsFactoryAsyncRequest : public EA::RefCountVTemplate_s0061_96c0<int> {
 public:
  GraphicsFactoryAsyncRequest(int a, int b, const char* name);  // 0x0093c270
  void SetProperty(int id, float v);                             // 0x0093bb40
  virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9();
  virtual void Start(int a, int b);  // slot 10
};  // namespace Graphics
}
struct ResourceReadRequest {  // 0x008e2380 ctor / 0x008e2350 dtor
  uint32_t pad[9];
  ResourceReadRequest(int a, Graphics::GraphicsFactoryAsyncRequest* gfar, const ResKey* key, bool f1, bool f2);  // 0x008e2380
  ~ResourceReadRequest();  // 0x008e2350
};
namespace SP {
namespace Thumbnail {
class cImportExport_s0061_96c0 {
 public:
  void UpdateExportThumb(const ResKey* key);  // 0x005fb430
};
}
}
namespace SP {
namespace Thumbnail {
cImportExport_s0061_96c0* GetImportExport();  // 0x005f7930
}
}
namespace SP {
namespace Pollen {
class cAssetMetadata_s0061_96c0 {
 public:
  const uint64_t* GetAssetID();               // 0x005507a0
  const wchar_t* GetName();                   // 0x00414e10
  const wchar_t* GetSummary();                // 0x005508c0
  unsigned GetTagCount();                     // 0x005509b0
  const wchar_t* GetTag(unsigned i);          // 0x005509e0
  unsigned GetTraitCount();                   // 0x00550a30
  unsigned GetTrait(unsigned i);              // 0x00550a60
  const uint64_t* GetParentAssetID();         // 0x00550800
  const uint64_t* GetOriginalParentAssetID(); // 0x00550820
  void SetParentAssetID(uint64_t id);         // 0x00551b60
  void SetOriginalParentAssetID(uint64_t id); // 0x00551b80
};
}
}
namespace SP {
namespace Pollen {
struct cAssetDirectory_s0061_96c0;  // opaque
}
}
namespace SP {
namespace Pollen {
void GetParentServerID(cAssetMetadata_s0061_96c0* meta, uint64_t* parentId, uint64_t* originalParentId);  // 0x00552080 (cdecl)
}
}
namespace SP {
namespace Pollen {
void MapLookup(uint32_t hash, string8_s0061_96c0* out);                                                    // 0x00621460 (cdecl)
}
}
namespace SP {
namespace Pollen {
class cITransaction_s0061_96c0 : public EA::RefCountVTemplate_s0061_96c0<int> {
 public:
  virtual ~cITransaction_s0061_96c0() {}
};
}
}
namespace SP {
namespace Pollen {
extern const void* const kResponseCallbacks;  // 0x015206f0
}
}
namespace SP {
namespace Pollen {
class cModelUploadTransaction_s0061_96c0 : public cITransaction_s0061_96c0 {
 public:
  ResKey mKey;                     // +0x8
  cAssetMetadata_s0061_96c0* mpAssetMetadata; // +0x14
  cAssetDirectory_s0061_96c0* mpAssetDir;     // +0x18
  uint64_t mnNextAssetID;          // +0x20
  bool mbSlurp;                    // +0x28
  bool mbBound;                    // +0x29
  void OnFailure();                // 0x00615db0
  bool ConstructRequest(EA::Internet::HTTPRequest_s0061_96c0** ppRequest);  // 0x006196c0 (SP::Pollen::cModelUploadTransaction::ConstructRequest)
};
}
}
// ---- items of slice s006196c0 end

// ---- items of slice s0061a650 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
namespace eastl {
struct allocator_s0061_a650 {
  allocator_s0061_a650() {}
};
}
namespace eastl {
template <typename T>
inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
}
namespace eastl {
template <typename T>
inline unsigned int CharStrlen_s0061_a650(const T* p) {
  const T* pCurrent = p;
  while (*pCurrent) ++pCurrent;
  return (unsigned int)(pCurrent - p);
}
}
namespace eastl {
int Compare(const char* p1, const char* p2, unsigned int n);  // FUN_00606ea0
}
namespace eastl {
template <typename I1, typename I2>
I1 search(I1 first1, I1 last1, I2 first2, I2 last2);  // 0x005e8ff0
}
namespace eastl {
template <typename T, typename A = allocator_s0061_a650>
struct basic_string_s0061_a650 {
  typedef unsigned int size_type;
  enum { npos = -1 };
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;

  basic_string_s0061_a650() : mpBegin(0), mpEnd(0), mpCapacity(0) {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  basic_string_s0061_a650(const T* pBegin, const T* pEnd, const A& allocator_s0061_a650)
      : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator_s0061_a650) {
    RangeInitialize(pBegin, pEnd);
  }
  struct CtorSprintf {};
  basic_string_s0061_a650(CtorSprintf, const T* pFormat, ...);  // 0x00473020 (wchar_t), 0x00472f50 (char)
  basic_string_s0061_a650& sprintf(const T* pFormat, ...);       // 0x00472fe0 (char)
  // (out of line at 0x0057cb10 elsewhere; this TU inlines it with AllocateSelf expanded)
  basic_string_s0061_a650(const basic_string_s0061_a650& x) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(x.mAllocator) {
    RangeInitializeInl(x.mpBegin, x.mpEnd);
  }
  ~basic_string_s0061_a650() { DeallocateSelf(); }

  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1)
      DoFree(mpBegin, mpCapacity - mpBegin);
  }
  void DoFree(T* p, size_type) {
    if (p) EASTL_allocator_deallocate(p);
  }
  void AllocateSelf(size_type n);  // 0x00475ab0 (char)
  void RangeInitialize(const T* pBegin, const T* pEnd) {
    const size_type n = (size_type)(pEnd - pBegin);
    AllocateSelf(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
  static T* CharStringUninitializedCopy(const T* pSource, const T* pSourceEnd, T* pDestination) {
    memmove(pDestination, pSource, (size_t)(pSourceEnd - pSource) * sizeof(T));
    return pDestination + (pSourceEnd - pSource);
  }
  size_type length() const { return (size_type)(mpEnd - mpBegin); }
  const T* c_str() const { return mpBegin; }
  void clear() {
    if (mpBegin != mpEnd) {
      *mpBegin = 0;
      mpEnd = mpBegin;
    }
  }
  basic_string_s0061_a650& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0 (char), 0x00423650 (wchar_t)
  basic_string_s0061_a650& operator=(const T* p);  // 0x005c3d90 (wchar_t)
  basic_string_s0061_a650& assign(const T* p) { return assign(p, p + CharStrlen_s0061_a650(p)); }
  basic_string_s0061_a650& operator=(const basic_string_s0061_a650& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  basic_string_s0061_a650& replace(size_type position, size_type n, const T* p);  // 0x005f8f80 (wchar_t)
  void Trim();                                                       // 0x00606e60 (wchar_t)

  static int compare(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2) {
    const int n1 = (int)(pEnd1 - pBegin1);
    const int n2 = (int)(pEnd2 - pBegin2);
    const int nMin = min_alt(n1, n2);
    const int cmp = Compare(pBegin1, pBegin2, (size_type)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
  }
  int compare(const T* p) const;
  basic_string_s0061_a650 substr(size_type position, size_type n) const;
  basic_string_s0061_a650 left(size_type n) const;
  size_type find(const T* p, size_type position, size_type n) const {
    T* const pBegin = mpBegin;
    T* const pEnd = mpEnd;
    if ((position + n) <= (size_type)(pEnd - pBegin)) {
      const T* const pResult = search(pBegin + position, pEnd, p, p + n);
      if ((pResult != pEnd) || (n == 0)) return (size_type)(pResult - pBegin);
    }
    return (size_type)npos;
  }
  size_type find(const T* p, size_type position = 0) const;
  size_type find(T c, size_type position = 0) const;  // 0x00607580 (char)
  bool empty() const { return (mpBegin == mpEnd); }
  size_type size() const { return (size_type)(mpEnd - mpBegin); }
  T* DoAllocate(size_type n) {
    return (T*)EASTL_allocator_allocate(n * sizeof(T), "Editor", 0, 0, "EASTL/allocator.h", 0xd1);
  }
  void AllocateSelf() {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  void AllocateSelfN(size_type n) {
    if (n > 1) {
      mpBegin = DoAllocate(n);
      mpEnd = mpBegin;
      mpCapacity = mpBegin + n;
    } else
      AllocateSelf();
  }
  void RangeInitializeInl(const T* pBegin, const T* pEnd) {
    const size_type n = (size_type)(pEnd - pBegin);
    AllocateSelfN(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
};
}
typedef eastl::basic_string_s0061_a650<char> string8_s0061_a650;
namespace EA {
template <typename T>
class RefCountVTemplate_s0061_a650 {
 public:
  RefCountVTemplate_s0061_a650() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s0061_a650() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace SP {
namespace Pollen {
class cITransaction_s0061_a650 : public EA::RefCountVTemplate_s0061_a650<int> {
 public:
  virtual ~cITransaction_s0061_a650() {}
};
}
}
namespace SP {
namespace Pollen {
struct FixedPtrVector_s0061_a650 {
  void** mpBegin;
  void** mpEnd;
  void** mpCapacity;
  uint32_t pad[2];
  uint32_t mOverflow;
  uint32_t mBuffer[40];
};
}
}
namespace SP {
namespace Pollen {
class cFeedTransactionBase_s0061_a650 : public cITransaction_s0061_a650 {
 public:
  uint32_t mpFeed;       // +0x8
  uint32_t mFeedType;    // +0xc
  uint32_t mnIntParam;   // +0x10
  uint32_t mnCount;      // +0x14
  uint32_t mUnk18;       // +0x18
  string8_s0061_a650 mStringParam;  // +0x1c
  uint32_t pad28[1];
  FixedPtrVector_s0061_a650 mAssets;  // +0x30
  uint8_t mFlag;           // +0xe8
  cFeedTransactionBase_s0061_a650(uint32_t type, const char* str, uint32_t intParam);
};
}
}
namespace SP {
namespace Pollen {
cFeedTransactionBase_s0061_a650::cFeedTransactionBase_s0061_a650(uint32_t type, const char* str, uint32_t intParam)
    : mpFeed(0), mFeedType(type), mnIntParam(intParam), mnCount(0xffffffff), mUnk18(0),
      mStringParam(), mFlag(0) {
  mStringParam.assign(str, str + strlen(str));
}
}
}
namespace SP {
namespace Pollen {
class cGetAssetFeedTransaction_s0061_a650 : public cFeedTransactionBase_s0061_a650 {
 public:
  cGetAssetFeedTransaction_s0061_a650(uint32_t lo, uint32_t hi);
};
}
}
namespace SP {
namespace Pollen {
class cGetAssetFeedTransactionEx_s0061_a650 : public cFeedTransactionBase_s0061_a650 {
 public:
  uint64_t mId;        // +0xf0
  string8_s0061_a650 mExtra;      // +0xf8
  cGetAssetFeedTransactionEx_s0061_a650(uint32_t lo, uint32_t hi);
};
}
}
namespace SP {
namespace Pollen {
extern void* gEmptyBucketArray;  // 0x0154df28
}
}
namespace SP {
namespace Pollen {
struct hash_set_u64_s0061_a650 {  // eastl::hash_set<uint64_t>, 0x20 bytes
  uint32_t mfRehash;
  void** mpBucketArray;
  uint32_t mnBucketCount;
  uint32_t mnElementCount;
  float mLoadFactor;
  float mGrowFactor;
  uint32_t pad0;
  uint32_t pad1;
  hash_set_u64_s0061_a650() {
    mLoadFactor = 1.0f;
    mGrowFactor = 2.0f;
    mnBucketCount = 1;
    mnElementCount = 0;
    pad0 = 0;
    mpBucketArray = &gEmptyBucketArray;
  }
};
}
}
namespace SP {
namespace Pollen {
class cEditFeedTransaction_s0061_a650 : public cITransaction_s0061_a650 {
 public:
  uint32_t mpFeed;         // +0x8
  int mOpType;             // +0xc
  string8_s0061_a650 mFeedURI;        // +0x10
  string8_s0061_a650 mFeedDescription;  // +0x20
  hash_set_u64_s0061_a650 mAssetsToAdd;     // +0x30
  hash_set_u64_s0061_a650 mAssetsToRemove;  // +0x50
  cEditFeedTransaction_s0061_a650(int opType);
};
}
}
namespace SP {
namespace Pollen {
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
}
}
namespace SP {
namespace Pollen {
class cUserMatchTransaction_s0061_a650 : public cITransaction_s0061_a650 {
 public:
  uint32_t mpFeed;    // +0x8
  uint64_t mAssetID;  // +0x10
  uint32_t mnCount;   // +0x18
  bool ConstructRequest(void** ppRequest);
};
}
}
namespace SP {
namespace Pollen {
class cHandshakeTransaction_s0061_a650 : public cITransaction_s0061_a650 {
 public:
  uint32_t pad0[2];
  uint32_t pad1[4];
  uint8_t pad2[0x70 - 0x18];
  bool ConstructRequest(void** ppRequest);
};
}
}
namespace SP {
namespace Pollen {
bool AssetFeedGetRequest(void** ppRequest);
}
}
namespace SP {
namespace Pollen {
bool UserMatchGetRequest(void** ppRequest);
}
}
// ---- items of slice s0061a650 end

// ---- items of slice s0061b3b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
namespace Pollen {
struct sTimedRec_s0061_b3b0 {
  char pad[0x30];
  int64_t mTime;  // +0x30
  char pad2[0x118 - 0x38];
};
}
}
namespace SP {
namespace Pollen {
struct sTimedOwner_s0061_b3b0 {
  char pad[0x60];
  sTimedRec_s0061_b3b0* mpTable;
};
}
}
namespace SP {
namespace Pollen {
struct TimeGreater_s0061_b3b0 {
  sTimedOwner_s0061_b3b0* mpOwner;
  bool operator()(unsigned int a, unsigned int b) const {
    return mpOwner->mpTable[a].mTime > mpOwner->mpTable[b].mTime;
  }
};
}
}
namespace SP {
namespace Pollen {
const unsigned int& median(const unsigned int& a, const unsigned int& b, const unsigned int& c,
                           TimeGreater_s0061_b3b0 compare);  // 0x006168a0
}
}
namespace SP {
namespace Pollen {
unsigned int* get_partition(unsigned int* first, unsigned int* last, unsigned int pivot,
                            TimeGreater_s0061_b3b0 compare);  // 0x006189e0
}
}
namespace SP {
namespace Pollen {
void partial_sort(unsigned int* first, unsigned int* middle, unsigned int* last, TimeGreater_s0061_b3b0 compare);
}
}
namespace SP {
namespace Pollen {
bool PollenRequestHelper(void* self, void* arg);
}
}
namespace SP {
namespace Pollen {
void WritePropertyListAndPNG(void* self, void* a, void* b, void* c);
}
}
namespace SP {
namespace Pollen {
void* AllocateAndCopy70(unsigned int n, void* a, void* b);
}
}
// ---- items of slice s0061b3b0 end

// ---- items of slice s0061c350 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
namespace Pollen {
void RemoveFeedFromAll(void* a, void* b);                              // 0x6175c0 cdecl
}
}
#define PV(n) virtual void pv##n();
struct ICoreAllocator;
void* operator new(unsigned int size, int alignment, const char* name, ICoreAllocator* pAllocator);
namespace eastl {
struct allocator_s0061_c350 {
  allocator_s0061_c350() {}
};
}
namespace eastl {
template <typename T>
inline unsigned int CharStrlen_s0061_c350(const T* p) {
  const T* pCurrent = p;
  while (*pCurrent) ++pCurrent;
  return (unsigned int)(pCurrent - p);
}
}
namespace eastl {
template <typename T, typename A = allocator_s0061_c350>
struct basic_string_s0061_c350 {
  typedef unsigned int size_type;
  enum { npos = -1 };
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;

  basic_string_s0061_c350() : mpBegin(0), mpEnd(0), mpCapacity(0) {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  basic_string_s0061_c350(const T* pBegin, const T* pEnd, const A& allocator_s0061_c350)
      : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator_s0061_c350) {
    RangeInitialize(pBegin, pEnd);
  }
  struct CtorSprintf {};
  basic_string_s0061_c350(CtorSprintf, const T* pFormat, ...);  // 0x00473020 (wchar_t), 0x00472f50 (char)
  basic_string_s0061_c350& sprintf(const T* pFormat, ...);       // 0x00472fe0 (char)
  // (out of line at 0x0057cb10 elsewhere; this TU inlines it with AllocateSelf expanded)
  basic_string_s0061_c350(const basic_string_s0061_c350& x) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(x.mAllocator) {
    RangeInitializeInl(x.mpBegin, x.mpEnd);
  }
  ~basic_string_s0061_c350() { DeallocateSelf(); }

  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1)
      DoFree(mpBegin, mpCapacity - mpBegin);
  }
  void DoFree(T* p, size_type) {
    if (p) EASTL_allocator_deallocate(p);
  }
  void AllocateSelf(size_type n);  // 0x00475ab0 (char)
  void RangeInitialize(const T* pBegin, const T* pEnd) {
    const size_type n = (size_type)(pEnd - pBegin);
    AllocateSelf(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
  static T* CharStringUninitializedCopy(const T* pSource, const T* pSourceEnd, T* pDestination) {
    memmove(pDestination, pSource, (size_t)(pSourceEnd - pSource) * sizeof(T));
    return pDestination + (pSourceEnd - pSource);
  }
  size_type length() const { return (size_type)(mpEnd - mpBegin); }
  const T* c_str() const { return mpBegin; }
  void clear() {
    if (mpBegin != mpEnd) {
      *mpBegin = 0;
      mpEnd = mpBegin;
    }
  }
  basic_string_s0061_c350& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0 (char), 0x00423650 (wchar_t)
  basic_string_s0061_c350& operator=(const T* p);  // 0x005c3d90 (wchar_t)
  basic_string_s0061_c350& assign(const T* p) { return assign(p, p + CharStrlen_s0061_c350(p)); }
  basic_string_s0061_c350& operator=(const basic_string_s0061_c350& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  basic_string_s0061_c350& replace(size_type position, size_type n, const T* p);  // 0x005f8f80 (wchar_t)
  void Trim();                                                       // 0x00606e60 (wchar_t)

  static int compare(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2) {
    const int n1 = (int)(pEnd1 - pBegin1);
    const int n2 = (int)(pEnd2 - pBegin2);
    const int nMin = min_alt(n1, n2);
    const int cmp = Compare(pBegin1, pBegin2, (size_type)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
  }
  int compare(const T* p) const;
  basic_string_s0061_c350 substr(size_type position, size_type n) const;
  basic_string_s0061_c350 left(size_type n) const;
  size_type find(const T* p, size_type position, size_type n) const {
    T* const pBegin = mpBegin;
    T* const pEnd = mpEnd;
    if ((position + n) <= (size_type)(pEnd - pBegin)) {
      const T* const pResult = search(pBegin + position, pEnd, p, p + n);
      if ((pResult != pEnd) || (n == 0)) return (size_type)(pResult - pBegin);
    }
    return (size_type)npos;
  }
  size_type find(const T* p, size_type position = 0) const;
  size_type find(T c, size_type position = 0) const;  // 0x00607580 (char)
  bool empty() const { return (mpBegin == mpEnd); }
  size_type size() const { return (size_type)(mpEnd - mpBegin); }
  T* DoAllocate(size_type n) {
    return (T*)EASTL_allocator_allocate(n * sizeof(T), "Editor", 0, 0, "EASTL/allocator.h", 0xd1);
  }
  void AllocateSelf() {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  void AllocateSelfN(size_type n) {
    if (n > 1) {
      mpBegin = DoAllocate(n);
      mpEnd = mpBegin;
      mpCapacity = mpBegin + n;
    } else
      AllocateSelf();
  }
  void RangeInitializeInl(const T* pBegin, const T* pEnd) {
    const size_type n = (size_type)(pEnd - pBegin);
    AllocateSelfN(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
};
}
typedef eastl::basic_string_s0061_c350<char> string8_s0061_c350;
typedef eastl::basic_string_s0061_c350<wchar_t> string16_s0061_c350;
namespace EA {
template <typename T>
class RefCountVTemplate_s0061_c350 {
 public:
  RefCountVTemplate_s0061_c350() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s0061_c350() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace Messaging {
class IHandler_s0061_c350 {
 public:
  virtual ~IHandler_s0061_c350() {}
  virtual bool HandleMessage(uint32_t messageID, void* pMessage) = 0;
};  // namespace Messaging
}
}
namespace EA {
class IMessageServer_s0061_c350 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMSG(uint32_t messageID, void* p1, void* p2);  // +0x14
  PV(6) PV(7)
  virtual void RegisterHandler(Messaging::IHandler_s0061_c350* pHandler, uint32_t messageID);  // +0x20
  virtual void AddListener(Messaging::IHandler_s0061_c350* pHandler, uint32_t messageID);  // +0x24
  PV(10)
  virtual void RemoveListener(Messaging::IHandler_s0061_c350* pHandler, uint32_t messageID, int priority);  // +0x2c
};
}
namespace SP {
namespace Pollen {
class cITransaction_s0061_c350 : public EA::RefCountVTemplate_s0061_c350<int> {
 public:
  virtual ~cITransaction_s0061_c350() {}
};
}
}
namespace SP {
namespace Pollen {
#define VFN(o, off, R, args) ((R (__thiscall*)args)(*(void***)(o))[(off) / 4])
}
}
namespace SP {
namespace Pollen {
#define I(p, off) (*(int*)((char*)(p) + (off)))
}
}
namespace SP {
namespace Pollen {
#define U(p, off) (*(unsigned*)((char*)(p) + (off)))
}
}
namespace SP {
namespace Pollen {
#define PI(p, off) (*(void**)((char*)(p) + (off)))
}
}
namespace SP {
namespace Pollen {
struct Key3 { unsigned a; unsigned b; unsigned c; };   // 12-byte resource key (instance, type, group order as stored)
}
}
namespace SP {
namespace Pollen {
struct cAssetDirectory_s0061_c350 {
  bool GetLocalKey(unsigned a, unsigned b, Key3* out);        // 0x54e460
  void AddMapping(unsigned a, unsigned b, Key3* k);           // 0x54e250
  void FUN_0054e7b0(unsigned a, unsigned b, int flag);        // 0x54e7b0
  bool FUN_0054e740(unsigned a, unsigned b);                  // 0x54e740
  void FUN_0054e970(int tag, unsigned lo, unsigned hi);       // 0x54e970
};
}
}
namespace SP {
namespace Pollen {
struct cAssetCache {
  bool FUN_00613860(unsigned type);                           // 0x613860
  void AddAsset(unsigned a, unsigned b, void* variantMap);    // 0x614280
};
}
}
namespace SP {
namespace Pollen {
struct cPollenMgr {
  virtual void v0();
  virtual void Notify(unsigned id, void* data);               // +4
  char pad[0x50];
  cAssetDirectory_s0061_c350* mpDirectory;                               // +0x58
  cAssetCache* mpCache;                                       // +0x5c
};
}
}
namespace SP {
namespace Pollen {
cPollenMgr* GetPollenMgr();                                   // 0x67cb30
}
}
namespace SP {
namespace Pollen {
struct IMessageServer_s0061_c350 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                        virtual void Post(unsigned id, void* data, int flag); };   // +0x14
}
}
namespace SP {
namespace Pollen {
IMessageServer_s0061_c350* GetMessageServer_s0061_c350();                           // 0x67dcc0 / EA::Messaging::GetServer 0x883860
}
}
namespace SP {
namespace Pollen {
void* GetResourceManager();                                   // 0x67dcd0
}
}
namespace SP {
namespace Pollen {
void* GetSaveArea(unsigned id);                               // 0x6b1f90
}
}
namespace SP {
namespace Pollen {
void* IDGenerator();                                          // 0x67de60
}
}
namespace SP {
namespace Pollen {
void operator_delete_arr(void* p);                            // 0xf47380
}
}
namespace SP {
namespace Pollen {
struct Deque { void Push(void* tx, int addref); };            // 0x60eaf0 deque<TransactionPtr,64>::PushSlow
}
}
namespace SP {
namespace Pollen {
struct FeedEvent {
  virtual void v0();
  virtual void Release();
  int refcount;
  int* mOwner;
  int mIndex;
  unsigned mKey;
  Key3 mLocal;
  int mZero;
  FeedEvent(int* owner, int index, unsigned key, const Key3& local)
      : refcount(0), mOwner(owner), mIndex(index), mKey(key), mLocal(local), mZero(0) {
    if (mOwner) mOwner[1]++;
  }
};
}
}
namespace SP {
namespace Pollen {
extern void* gFeedEventPoolHead;   // 0x15f5264, free list head of the pool at 0x15f5254
}
}
namespace SP {
namespace Pollen {
struct FeedEventPoolT { bool AddCore(int, int); };   // 0x00926650 EA::Allocator::FixedAllocatorBase::AddCore (thiscall)
}
}
namespace SP {
namespace Pollen {
extern FeedEventPoolT gFeedEventPool;   // 0x015f5254
}
}
namespace SP {
namespace Pollen {
unsigned* LowerBound(unsigned* b, unsigned* e, const unsigned* key, char flag);   // 0x555a20 cdecl
}
}
namespace SP {
namespace Pollen {
struct SortedUIntVec {
  unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCapacity;
  void Insert(unsigned* pos, const unsigned* v);   // 0x5481d0
};
}
}
namespace SP {
namespace Pollen {
struct cAssetFeedTransaction {
  bool HandleResult(int code, void* result, Deque* queue);
};
}
}
namespace SP {
namespace Pollen {
struct cAssetMetadata_s0061_c350 {
  cAssetMetadata_s0061_c350();                                                    // 0x550450
  virtual void AddRef();
  virtual void Release();
  bool UpdateFromEntry(void* entry, void* feedInfo);                   // 0x551ba0
  bool GetCreatureName(Key3* out, void* entry, void* feedInfo);        // 0x550da0
  unsigned* GetKeyPair();                                              // 0x5507a0
  int FUN_005508e0();                                                  // 0x5508e0
};
}
}
namespace SP {
namespace Pollen {
struct IDGen { virtual void v0(); virtual void Register(Key3* key, void* data, void* extra); };  // +4
}
}
namespace SP {
namespace Pollen {
struct VariantMapVec {   // fixed vector<EA::Variant,N> on the stack (0x18-byte elements, begin at +4)
  char* mpBegin; char* mpEnd; char* mpCapacity; char* mpFixed; char* mpFixedEnd; char buf[0xf0];
  void* Index(unsigned* hash);                                         // 0x613d20 (vector_map operator[])
};
}
}
namespace SP {
namespace Pollen {
struct Variant { Variant& operator=(const Variant& o); };              // 0x542b80
}
}
namespace SP {
namespace Pollen {
void VariantDestruct(void* v, int flag);                               // EA::Variant::Destruct 0x93db80, thiscall
}
}
namespace SP {
namespace Pollen {
unsigned FNV1_String16(const wchar_t* s, unsigned seed, int flag);     // 0x932f30 cdecl
}
}
namespace SP {
namespace Pollen {
unsigned FNV1_String8(const char* s, unsigned seed, int flag);         // 0x932e80 cdecl
}
}
namespace SP {
namespace Pollen {
void SortFeedIndices(unsigned* b, unsigned* e, void* feed);            // 0x61c140
}
}
namespace SP {
namespace Pollen {
struct IndexVec { unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCapacity; void Resize(unsigned n); };   // 0x4cd3c0
}
}
namespace SP {
namespace Pollen {
bool SetAssetData(void* list, int a);                                  // 0x4bbe20 (cSPAssetDataList::SetAssetData)
}
}
namespace SP {
namespace Pollen {
unsigned FUN_004bbc70(void* list, int a, int b, int c, int d);
}
}
namespace SP {
namespace Pollen {
void FUN_006ac0a0(int type, void* obj);
}
}
namespace SP {
namespace Pollen {
void FUN_006ad010(void* obj);
}
}
namespace SP {
namespace Pollen {
void FUN_00616d60(void* obj, void* sa, int flag);
}
}
namespace SP {
namespace Pollen {
void* AllocTx28(unsigned size);                                        // 0x615a00
}
}
namespace SP {
namespace Pollen {
void* AllocTx24(unsigned size);                                        // 0x6159d0
}
}
namespace SP {
namespace Pollen {
struct TxA { TxA* Init(Key3 key, cAssetMetadata_s0061_c350* md, void* feed, void* entry, int flag); };   // 0x6163e0 (thiscall, key by value)
}
}
namespace SP {
namespace Pollen {
struct TxB { TxB* Init(Key3* key, void* feed, void* entry); };         // 0x616300
}
}
namespace SP {
namespace Pollen {
void WStr_Format(void* wstr, const wchar_t* fmt, ...);                 // 0x41e050 cdecl
}
}
namespace SP {
namespace Pollen {
extern wchar_t gEmptyWide[];   // 0x01667bac (shared empty string)
}
}
namespace SP {
namespace Pollen {
class cFeedStateTransaction : public cITransaction_s0061_c350 {
 public:
  string8_s0061_c350 mS8;            // +0x08
  uint32_t pad18;
  string16_s0061_c350 mS1c;          // +0x1c
  string16_s0061_c350 mS2c;          // +0x2c
  uint32_t pad3c;
  uint32_t m40, m44, m48, m4c;
  string8_s0061_c350 mS50;           // +0x50
  uint32_t mV60, mV64, mV68;
  uint32_t pad6c, pad70;
  uint8_t m74;
  string16_s0061_c350 mS78;          // +0x78
  cFeedStateTransaction();
  virtual ~cFeedStateTransaction();
};
}
}
// ---- items of slice s0061c350 end



// ---- items of slice s0061d240 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(memmove)
namespace EA {
template <typename T>
class RefCountVTemplate_s0061_d240 {
 public:
  RefCountVTemplate_s0061_d240() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s0061_d240() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace SP {
namespace Pollen {
class cITransaction_s0061_d240 : public EA::RefCountVTemplate_s0061_d240<int> {
 public:
  virtual ~cITransaction_s0061_d240() {}
};
}
}
namespace SP {
namespace Pollen {
class cHandshakeTransaction_s0061_d240 : public cITransaction_s0061_d240 {
 public:
  uint8_t pad[0x70 - 0x8];
  bool HandleResult(int code, void* result, void* queue);
};
}
}
namespace SP {
namespace Pollen {
void* AssetHelper288(void* self, void* a);
}
}
namespace SP {
namespace Pollen {
bool GetAssetFeedConstructRequest(void* self, void* ppRequest);
}
}
namespace SP {
namespace Pollen {
bool EditFeedConstructRequest(void* self, void* ppRequest);
}
}
// ---- items of slice s0061d240 end

// @ 0x00615ed0
bool cModelUploadTransaction_s0061_4f20::HandleResult(int err, cHttpResult* r, cTransactionQueue_s0061_4f20* q)
{
    bool result = false;
    RefPtr<IFactory>* pRef;
    if (err != 0) {
        if (!r) goto fail;
        pRef = (RefPtr<IFactory>*)((char*)r + 0xf3c);
        if (pRef->p) ((void (__thiscall*)(void*))(*(void***)pRef->p)[6])(pRef->p);
    } else {
        pRef = (RefPtr<IFactory>*)((char*)r + 0xf3c);
        SP::Pollen::cServerResponse_s0061_4f20* o = pRef->p ? (SP::Pollen::cServerResponse_s0061_4f20*)((char*)pRef->p - 8) : 0;
        EA::IO::IStream_s0061_4f20* s = (EA::IO::IStream_s0061_4f20*)((char*)o + 8);
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
        cAssetMetadata_s0061_4f20* x = mpAssetMetadata ? (cAssetMetadata_s0061_4f20*)mpAssetMetadata->Cast(0x2269ed1) : 0;
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












// @ 0x00616220
bool cTimeGreater::operator()(unsigned a, unsigned b) const
{
    return mpOwner->mpTable[a].mTime > mpOwner->mpTable[b].mTime;
}












// @ 0x006162a0
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












// @ 0x00616300
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












// @ 0x00616360
void cTxC::Dtor()
{
    vtbl = kVtbl13fc52c;
    _ReadWriteBarrier();
    {
        RCObj* p = mpObj;
        if (p) {
            mpObj = 0;
            RCRelease(p);
        }
    }
    if (m20) m20->ReleaseSlot1();
    if (m1c) m1c->ReleaseSlot2();
    {
        RCObj* p = mpObj;
        if (p) RCRelease(p);
    }
    vtbl = kBaseVtbl;
}











// @ 0x006163e0
cTxD* cTxD::Init(ResourceKey_s0061_6360 key, IAddRef* ref, RCObj* counted, unsigned n, bool b)
{
    mb8 = b;
    mnRef = 0;
    vtbl = kVtbl13fc550;
    mb9 = true;
    mpCounted = counted;
    if (counted) ++counted->mnRef;
    mnCount = n;
    mKey = key;
    mpRef = ref;
    if (ref) ref->AddRef();
    _ReadWriteBarrier();
    mpRel = 0;
    return this;
}











// @ 0x00616460
void cTxD::Dtor()
{
    vtbl = kVtbl13fc550;
    _ReadWriteBarrier();
    {
        RCObj* p = mpCounted;
        if (p) {
            mpCounted = 0;
            RCRelease(p);
        }
    }
    {
        IRel2* p = mpRel;
        if (p) {
            mpRel = 0;
            p->ReleaseSlot2();
        }
    }
    if (mpRel) mpRel->ReleaseSlot2();
    if (mpRef) ((IRel1*)mpRef)->ReleaseSlot1();
    {
        RCObj* p = mpCounted;
        if (p) RCRelease(p);
    }
    vtbl = kBaseVtbl;
}











// @ 0x00616500
void cTxE::Dtor()
{
    vtbl = kVtbl13fc574;
    _ReadWriteBarrier();
    {
        RCObj* p = mpObj;
        if (p) {
            mpObj = 0;
            RCRelease(p);
        }
    }
    {
        IRel2* p = mpRel;
        if (p) {
            mpRel = 0;
            p->ReleaseSlot2();
        }
    }
    if (mpRel) mpRel->ReleaseSlot2();
    {
        RCObj* p = mpObj;
        if (p) RCRelease(p);
    }
    vtbl = kBaseVtbl;
}











// @ 0x00616580
bool cTxF::HandleResult(int err, void* a, void* b)
{
    bool ok = false;
    if (err == 0) {
        if (GetManager2_s0061_6360()->GetResource(&mKey, 0, 0, 0, 0, 0))
            ok = true;
    }
    if (mpWorker) mpWorker->Fn24();
    if (!ok) {
        IWorkerObj* o = mpWorker->Fn1c();
        if (o)
            o->Fn40(mpWorker->Fn10());
    }
    if (mpWorker) {
        IWorker* w = mpWorker;
        mpWorker = 0;
        w->ReleaseWorker();
    }
    return ok;
}











// @ 0x00616610
bool cTxG::HandleResult(int err, cHttpResult_s0061_6360* r, void* unused)
{
    if (r) {
        IResp* p = (IResp*)r->mpResponse;
        if (p) p->Close();
    }
    bool b = (err == 0);
    if (b)
        GetPollinatorLite()->Notify(0x3cf0359, mp8);
    return b;
}











// @ 0x006166b0
bool cTxI::HandleResult(int err, cHttpResult_s0061_6360* r, void* unused)
{
    if (r) {
        IRel2* p = r->mpResponse;
        if (p) {
            r->mpResponse = 0;
            p->ReleaseSlot2();
        }
    }
    return false;
}











// @ 0x006166e0
cTxJ* cTxJ::Init(IAddRef1* a, IAddRef1* b)
{
    mnRef = 0;
    vtbl = kVtbl13fc5bc;
    mp8 = a;
    if (a) a->AddRef1();
    mpC = b;
    if (b) b->AddRef1();
    return this;
}











// @ 0x00616730
bool cTxK::HandleResult(int err, cHttpResult2* r, void* unused)
{
    mp8->Fn18();
    uint32_t v = 0;
    if (err == 0)
        v = mpC;
    else if (r && r->mnStatus == 0x23f)
        v = mpC;
    GetMessageServer()->PostMessage(0x60ba744, (void*)v, 0);
    if (r) {
        IRel2* p = r->mpResponse;
        if (p) {
            r->mpResponse = 0;
            p->ReleaseSlot2();
        }
    }
    return true;
}











// @ 0x006167a0
void insertion_sort(unsigned* first, unsigned* last, cTimeGreaterInl compare)
{
    if (first != last) {
        unsigned *iCurrent, *iNext, *iSorted = first;
        for (++iSorted; iSorted != last; ++iSorted) {
            const unsigned temp(*iSorted);
            iNext = iCurrent = iSorted;
            for (--iCurrent; (iNext != first) && compare(temp, *iCurrent); --iNext, --iCurrent)
                *iNext = *iCurrent;
            *iNext = temp;
        }
    }
}











// @ 0x00616820
void insertion_sort_unguarded(unsigned* first, unsigned* last, cTimeGreaterInl compare)
{
    for (unsigned* i = first; i != last; ++i) {
        const unsigned value(*i);
        unsigned *end(i), *prev(i);
        for (--prev; compare(value, *prev); --end, --prev)
            *end = *prev;
        *end = value;
    }
}











// @ 0x006168a0
inline const unsigned& median(const unsigned& a, const unsigned& b, const unsigned& c, cTimeGreaterInl compare)
{
    if (compare(a, b)) {
        if (compare(b, c))
            return b;
        else if (compare(a, c))
            return c;
        else
            return a;
    } else if (compare(a, c))
        return a;
    else if (compare(b, c))
        return c;
    return b;
}











// @ 0x00616960
string8& string8::append(size_type n, char c)
{
    const size_type nLength = (size_type)(mpEnd - mpBegin);
    const size_type nCapacity = (size_type)((mpCapacity - mpBegin) - 1);
    if ((nLength + n) > nCapacity)
        reserve(emax(GetNewCapacity(nCapacity), (size_type)(nLength + n)));
    if (n > 0) {
        memset(mpEnd + 1, (unsigned char)c, n - 1);
        *mpEnd = c;
        mpEnd += n;
        *mpEnd = 0;
    }
    return *this;
}











// @ 0x00616a00
void promote_heap(unsigned* first, int topPosition, int position, const unsigned value, cTimeGreaterInl compare)
{
    for (int parentPosition = (position - 1) >> 1;
         (position > topPosition) && compare(*(first + parentPosition), value);
         parentPosition = (position - 1) >> 1) {
        *(first + position) = *(first + parentPosition);
        position = parentPosition;
    }
    *(first + position) = value;
}











// @ 0x00616aa0
void string8::AllocateSelf(size_type n)
{
    if (n > 1) {
        mpBegin = (char*)EASTL_alloc(n, "Editor", 0, 0, "UTFKernel\\EASTL\\string.h", 0xd1);
        mpEnd = mpBegin;
        mpCapacity = mpBegin + n;
    } else {
        mpBegin = gEmptyString8;
        mpEnd = gEmptyString8;
        mpCapacity = gEmptyString8 + 1;
    }
}











// @ 0x00616b00
void* cPoolTxA::Destroy(unsigned flags)
{
    vtbl = kBaseVtbl;
    if (flags & 1) {
        *(void**)this = gFreeListA;
        gFreeListA = this;
    }
    return this;
}











// @ 0x00616b20
void* cPoolTxB::Destroy(unsigned flags)
{
    vtbl = kBaseVtbl;
    if (flags & 1) {
        *(void**)this = gFreeListB;
        gFreeListB = this;
    }
    return this;
}











// @ 0x00616b40
void* cTxUp1::Destroy(unsigned flags)
{
    IAddRef* m = mpAssetMetadata;
    vtbl = kVtbl13fc484;
    if (m) m->Release();
    vtbl = kBaseVtbl;
    if (flags & 1) {
        *(void**)this = gFreeListC;
        gFreeListC = this;
    }
    return this;
}











// @ 0x00616b80
bool cTxUpload::HandleResult(int err, cHttpResult_s0061_6360* r, cTransactionQueue* q)
{
    bool result = false;
    IRel2** pRef;
    if (err != 0) {
        if (!r) goto retry;
        pRef = &r->mpResponse;
        if (*pRef) ((IResp*)*pRef)->Close();
    } else {
        pRef = &r->mpResponse;
        cServerResponseLite* o = *pRef ? (cServerResponseLite*)((char*)*pRef - 8) : 0;
        IStreamLite* s = (IStreamLite*)((char*)o + 8);
        int state = s->GetState();
        s->Close();
        if (state == 0 && o->mnReturnCode == 0) {
            uint32_t* sid = mpAssetMetadata->GetServerID();
            uint32_t lo = sid[0];
            uint32_t hi = sid[1];
            mpAssetDir->AddMapping(lo, hi, &mKey);
            const wchar_t* idText = o->GetField(L"next-id");
            if (idText)
                mnNextAssetID = StrtoU64(idText, 0, 10);
            result = true;
        }
    }
    {
        IRel2* ref = *pRef;
        if (ref) {
            *pRef = 0;
            ref->ReleaseSlot2();
        }
    }
    if (!result) {
retry:
        if (err != 8) {
            mnNextLo = 0xffffffffu;
            mnNextHi = 0xffffffffu;
            cModelUploadTransactionLite* t = new cModelUploadTransactionLite(mpAssetMetadata, mpAssetDir, mbA, mbB, mnRetries);
            ((cTransactionQueue*)q)->Enqueue(t, true);
        }
        return result;
    }
    sUploadMsg_s0061_6360 m;
    m.ok = true;
    m.key = mKey;
    GetMessageServer2()->PostMessage(0x68cd252, &m, 0);
    return result;
}











// @ 0x00616d20
void* cTxUp2::Destroy(unsigned flags)
{
    IAddRef* m = mpAssetMetadata;
    vtbl = kVtbl13fc4a8;
    if (m) m->Release();
    vtbl = kBaseVtbl;
    if (flags & 1) {
        *(void**)this = gFreeListD;
        gFreeListD = this;
    }
    return this;
}











// @ 0x00616d60
void CreateDownloadJob(IAddRef* pDb, SubOwner_s0061_6360* pOwner, const ResourceKey_s0061_6360* pKey)
{
    cJob* job = 0;
    cJobManager* mgr = GetJobManager();
    {
        cJob* old = job;
        if (old) {
            job = 0;
            old->Release();
        }
    }
    if (!mgr->CreateJob(&job)) {
        if (job) job->Release();
        return;
    }
    cTripleObj_s0061_6360* o = new ("Pollinator", 0, 0, 0, 0) cTripleObj_s0061_6360();
    if (o) ((IAddRef*)o)->AddRef();
    job->mnStatus = 4;
    void* p4 = o ? &o->v4 : 0;
    job->mpFn = (void*)JobFn68f5a0;
    job->mp4 = p4;
    job->Attach(o);
    IAddRef* oldDb = o->m10;
    if (pDb != oldDb) {
        if (pDb) pDb->AddRef();
        o->m10 = pDb;
        if (oldDb) oldDb->Release();
    }
    SubOwner_s0061_6360* oldOwner = o->m14;
    if (pOwner != oldOwner) {
        if (pOwner) pOwner->sub.AddRefSub();
        o->m14 = pOwner;
        if (oldOwner) oldOwner->sub.ReleaseSub();
    }
    const ResourceKey_s0061_6360* k = pKey ? pKey : (const ResourceKey_s0061_6360*)((char*)pDb + 8);
    o->m18 = *k;
    job->Start();
    ((IAddRef*)o)->Release();
    if (job) job->Release();
}











// @ 0x00616ed0
bool cTxDownload::HandleResult(int err, void* a, void* b)
{
    ResourceKey_s0061_6360 scratch;
    bool closed;
    if (!mpResp)
        closed = false;
    else
        closed = mpResp->stream.Close();
    {
        cResponseRef* p = (cResponseRef*)mpResp;
        if (p) {
            mpResp = 0;
            p->ReleaseSlot2();
        }
    }
    if (closed && err == 0) {
        SetCachingType(10, mpMetadata);
        void* x = mpMetadata ? mpMetadata->Cast(0x2269ed1) : 0;
        Fn6ad010(x);
        scratch.instanceID = mKey.instanceID;
        scratch.typeID = 0x1a99b06b;
        scratch.groupID = mKey.groupID;
        CreateDownloadJob(mpMetadata, (SubOwner_s0061_6360*)GetSaveArea(0x11ac19d), &scratch);
        return true;
    }
    cAssetDirectory* dir = GetPollinatorDir()->mpAssetDirectory;
    uint32_t* id = (uint32_t*)&scratch;
    if (dir->GetServerId(&mKey, id, false)) {
        if (err != 0xb)
            dir->Fn54ed50(id[0], id[1], 0);
        dir->Fn54e7b0(id[0], id[1], 0);
    }
    return false;
}











// @ 0x00617010
bool cTxThumbnail::ConstructRequest(char** ppOut)
{
    cFeedDoc* feed = mpFeed;
    if (feed) {
        int count = (int)(feed->mpEntriesEnd - feed->mpEntriesBegin) / 0x118;
        if (mnEntryIndex <= (unsigned)count) {
            char* entry = feed->mpEntriesBegin + mnEntryIndex * 0x118;
            ResourceKey_s0061_6360 key = mAssetKey;
            key.typeID = 0x2f7d0004;
            IDatabase* db = (IDatabase*)GetSaveArea(0x11ac19d);
            if (db) {
                IRel2** pRecord = &mpRecord;
                if (*pRecord) {
                    IRel2* old = *pRecord;
                    *pRecord = 0;
                    old->ReleaseSlot2();
                }
                if (db->OpenRecord(&key, pRecord, 2, 2, 0, 0)) {
                    IRecordLite* rec = (IRecordLite*)*pRecord;
                    const char* url = *(const char**)(entry + 0xa8);
                    cHttpRequestRef req;
                    req.mp = 0;
                    if (CreateHTTPGetRequest(url, rec->GetStream(), req.GetAddressOf())) {
                        *(int*)(req.mp + 0xd94) = 0x15206f0;
                        _InterlockedExchangeAdd((volatile long*)(req.mp + 4), 1);
                        *ppOut = req.mp;
                    }
                    req.Release();
                    return true;
                }
            }
        }
    }
    return false;
}











// @ 0x00617450
void* cTelemetryUploadTransaction::Destroy(unsigned flags)
{
    vtbl = kVtbl13fc598;
    _ReadWriteBarrier();
    if (mpTelemetryStream) mpTelemetryStream->ReleaseSlot2();
    vtbl = kBaseVtbl;
    if (flags & 1) {
        *(void**)this = gFreeList15f52c4;
        gFreeList15f52c4 = this;
    }
    return this;
}










// @ 0x00617490
void* cPollenTxTwoRefs::Destroy(unsigned flags)
{
    vtbl = kVtbl13fc5bc;
    _ReadWriteBarrier();
    if (mpC) mpC->ReleaseSlot2();
    if (mp8) mp8->ReleaseSlot2();
    vtbl = kBaseVtbl;
    if (flags & 1) {
        *(void**)this = gFreeList15f5304;
        gFreeList15f5304 = this;
    }
    return this;
}










// @ 0x00617530
void adjust_heap(unsigned* first, int topPosition, int heapSize, int position, unsigned value, cTimeGreaterInl compare)
{
    int childPosition = (2 * position) + 2;
    while (childPosition < heapSize) {
        if (compare(*(first + childPosition), *(first + (childPosition - 1))))
            --childPosition;
        *(first + position) = *(first + childPosition);
        position = childPosition;
        childPosition = (2 * position) + 2;
    }
    if (childPosition == heapSize) {
        *(first + position) = *(first + (childPosition - 1));
        position = childPosition - 1;
    }
    promote_heap(first, topPosition, position, value, compare);
}










// @ 0x006175c0
void __cdecl RemoveFeedFromAll(cPendingAssetSet* self, const string8_s0061_7130* uri)
{
    cAssetDirectory_s0061_7130* dir = GetPollinatorDir_s0061_7130()->mpAssetDirectory;
    if (dir) {
        sFeedMsg msg;
        msg.key.instanceID = 0;
        msg.key.typeID = 0;
        msg.key.groupID = 0;
        msg.hash = FNV1_String8(uri->mpBegin, 0x811c9dc5, 0);
        msg.minusOne = 0xffffffffu;
        hnode** bucket = self->mpBucketArray;
        hnode* node = *bucket;
        if (!node) {
            ++bucket;
            while (*bucket == 0) ++bucket;
            node = *bucket;
        }
        hnode* end = self->mpBucketArray[self->mnBucketCount];
        while (node != end) {
            ResourceKey_s0061_7130 local;
            local.instanceID = 0;
            local.typeID = 0;
            local.groupID = 0;
            if (dir->GetLocalKey(node->lo, node->hi, &local))
                UnsubscribeAsset(local, uri, &msg, local);
            node = node->next;
            while (node == 0) {
                ++bucket;
                node = *bucket;
            }
        }
    }
}










// @ 0x006177b0
void RemoveFeedByName(const string8_s0061_7130* name)
{
    KeyVec results;
    results.mpBegin = 0;
    results.mpEnd = 0;
    results.mpCapacity = 0;
    sTemplateDB* db = ObjectTemplateDB();
    QueryFn* pQuery = (QueryFn*)((char*)db->vtbl + 0x34);
    const char* nm = name->mpBegin;
    (*pQuery)(db, &results, FunctionalMatch::Constraint(0x3cc89b1, 0, FNV1_String8(nm, 0x811c9dc5, 0)),
              FunctionalMatch::Constraint(0));
    sFeedMsg msg;
    msg.key.instanceID = 0;
    msg.key.typeID = 0;
    msg.key.groupID = 0;
    msg.hash = FNV1_String8(name->mpBegin, 0x811c9dc5, 0);
    msg.minusOne = 0xffffffffu;
    ResourceKey_s0061_7130* end = results.mpEnd;
    for (ResourceKey_s0061_7130* it = results.mpBegin; it != end; ++it) {
        ResourceKey_s0061_7130 cur = *it;
        UnsubscribeAsset(cur, name, &msg, cur);
    }
    FreeCountedArray(results.mpBegin);
}










// @ 0x00617a40
void cGetAssetFeedTransaction::Dtor()
{
    vtbl = kVtbl13fc5e0;
    _ReadWriteBarrier();
    {
        RCObj* p = mpFeed;
        if (p) {
            mpFeed = 0;
            RCRelease(p);
        }
    }
    FreeCountedArray(mpEntries);
    mUrl.~string8_s0061_7130();
    {
        RCObj* p = mpFeed;
        if (p) RCRelease(p);
    }
    vtbl = kBaseVtbl;
}










// @ 0x00617b10
bool cFeedGetTx::ConstructRequestA(HTTPRequest** ppOut)
{ return BuildGetRequest(this, 0x539f69d, ppOut); }










// @ 0x00617c90
bool cFeedGetTx::ConstructRequestB(HTTPRequest** ppOut)
{ return BuildGetRequest(this, 0x539f705, ppOut); }










// @ 0x00617e00
bool cFeedUnsubscribeTransaction::HandleResult(int err, cHttpResult_s0061_7130* r, void* unused)
{
    if (r) {
        IResp* p = (IResp*)r->mpResponse;
        if (p) p->Close();
    }
    bool ok = (err == 0);
    char* v;
    if (ok) {
        RemoveFeedByName(&mUri);
        v = mUri.mpBegin;
    } else {
        v = 0;
    }
    GetPollinatorNotify()->Notify(0x3ffd8c9, v);
    if (ok)
        v = mUri.mpBegin;
    else
        v = 0;
    GetMessageServer()->PostMessage(0x3ffd8c9, v, 0);
    return ok;
}










// @ 0x00617e80
void cSnapshotUploadTransaction::Dtor()
{
    vtbl = kVtbl13fc698;
    mLocale.~string8_s0061_7130();
    mMessageText.~string8_s0061_7130();
    mDestinationEmailAddress.~string8_s0061_7130();
    mMyEmailAddress.~string8_s0061_7130();
    vtbl = kBaseVtbl;
}










// @ 0x00617f10
bool cSnapshotUploadTransaction::ConstructRequest(HTTPRequest** ppOut)
{
    void* mem = operator new(0x48, "Pollinator", 0, 0, 0, 0);
    if (mem) {
        HTTPMultipartFormDataPostBodyStream* body = ((HTTPMultipartFormDataPostBodyStream*)mem)->Ctor();
        if (body) {
            body->AddRef();
            void* mem2 = operator new(0x24, "Pollinator", 0, 0, 0, 0);
            cImageRequest* img = mem2 ? ((cImageRequest*)mem2)->Ctor(0, 0, "UTF/MemoryStream") : 0;
            img->SetProperty(1, 1.0f);
            if (body->AddField("locale", mLocale.mpBegin)) {
                if (body->AddField("myEmail", mMyEmailAddress.mpBegin)) {
                    if (body->AddField("destEmail", mDestinationEmailAddress.mpBegin)) {
                        if (body->AddField("msgTxt", mMessageText.mpBegin)) {
                            IDb* db = GetManager_s0061_7130()->FindDatabaseByKey(&mKey);
                            IRefHolder held;
                            held.mp = 0;
                            if (db) {
                                if (db->OpenRecord(&mKey, (void**)held.Reset(), 1, 6, 1, 0)) {
                                    if (body->AddFile("imagedata", held.mp->GetStream(), "image/jpeg", "postcard.tmp", 0)) {
                                        string8_s0061_7130 url;
                                        url.mpBegin = gEmptyString8;
                                        url.mpEnd = gEmptyString8;
                                        url.mpCapacity = gEmptyString8 + 1;
                                        MapLookup(0x53c3e41, &url);
                                        HttpReqRef req;
                                        req.mp = 0;
                                        if (CreateHTTPPostRequest(url.mpBegin, body, img, req.GetAddressOutOfLine())) {
                                            _InterlockedExchangeAdd(&req.mp->mnRef, 1);
                                            req.mp->mpHandlerVtbl = kVtbl15206f0;
                                            *ppOut = req.mp;
                                            req.Dtor();
                                            url.~string8_s0061_7130();
                                            if (held.mp) held.mp->ReleaseSlot2();
                                            body->Release();
                                            return true;
                                        }
                                        req.Dtor();
                                        url.~string8_s0061_7130();
                                    }
                                }
                                if (held.mp) held.mp->ReleaseSlot2();
                            }
                        }
                    }
                }
            }
            body->Release();
        }
    }
    return false;
}










// @ 0x00618150
namespace SP { namespace Pollen {
cYouTubeAuthenticationTransaction_s0061_8150::~cYouTubeAuthenticationTransaction_s0061_8150()
{}
}}  // namespace SP::Pollen









// @ 0x006181c0
namespace SP { namespace Pollen {
bool cYouTubeAuthenticationTransaction_s0061_8150::ConstructRequest(void** ppRequest)
{
  Ref<UrlEncodedBody> body(new ("Pollinator", 0, 0, 0, 0) UrlEncodedBody());
  if (body) {
    AsyncRequest* async = new ("Pollinator", 0, 0, 0, 0) AsyncRequest(0, 0, "UTF/MemoryStream");
    async->SetPriority(1, 1.0f);
    if (body->AddField("Email", mUsername.mpBegin) &&
        body->AddField("Passwd", mPassword.mpBegin) &&
        body->AddField("service", "youtube") &&
        body->AddField("source", mSource.mpBegin)) {
      string8_s0061_8150 url;
      GetServiceURL(&gYouTubeAuthURL, &url);
      ReqPtr req;
      if (CreateHTTPPostRequest(url.mpBegin, body.mpObject, async, &req)) {
        _InterlockedExchangeAdd(&req.mpObject->mRefCount, 1);
        req.mpObject->mCallbackVtbl = 0x015206f0;
        *ppRequest = req.mpObject;
        return true;
      }
    }
  }
  return false;
}
}}  // namespace SP::Pollen









// @ 0x00618370
namespace SP { namespace Pollen {
cYouTubeVideoUploadTransaction_s0061_8150::~cYouTubeVideoUploadTransaction_s0061_8150()
{}
}}  // namespace SP::Pollen









// @ 0x00618430
namespace SP { namespace Pollen {
cYouTubeVideoURLTransaction_s0061_8150::~cYouTubeVideoURLTransaction_s0061_8150()
{}
}}  // namespace SP::Pollen









// @ 0x006184c0
namespace SP { namespace Pollen {
bool cYouTubeVideoURLTransaction_s0061_8150::ConstructRequest(void** ppRequest)
{
  Ref<MultipartBody> body(new ("Pollinator", 0, 0, 0, 0) MultipartBody());
  if (body) {
    AsyncRequest* async = new ("Pollinator", 0, 0, 0, 0) AsyncRequest(0, 0, "UTF/MemoryStream");
    async->SetPriority(1, 1.0f);
    if (body->AddField("locale", mLocale.mpBegin) &&
        body->AddField("myEmail", mMyEmailAddress.mpBegin) &&
        body->AddField("destEmail", mDestinationEmailAddress.mpBegin) &&
        body->AddField("msgTxt", mMessageText.mpBegin)) {
      string8_s0061_8150 url;
      GetServiceURL(&gYouTubeEmailURL, &url);
      ReqPtr req;
      if (CreateHTTPPostRequest(url.mpBegin, body.mpObject, async, &req)) {
        _InterlockedExchangeAdd(&req.mpObject->mRefCount, 1);
        req.mpObject->mCallbackVtbl = 0x015206f0;
        *ppRequest = req.mpObject;
        return true;
      }
    }
  }
  return false;
}
}}  // namespace SP::Pollen









// @ 0x00618670
namespace SP { namespace Pollen {
bool cUploadTransactionRetail::ConstructRequest(void** ppRequest)
{
  if (mpStream) {
    string8_s0061_8150 url;
    GetServiceURL(&gMsgUploadFailed, &url);
    Ref<UploadRequest> req(new ("Pollinator", 0, 0, 0, 0) UploadRequest());
    req->SetMethod(4);
    req->SetURL(url.mpBegin);
    Obj8* o = new ("Pollinator", 0, 0, 0, 0) Obj8();
    IRefObj* oldAsync = req->mpAsync;
    if (o != oldAsync) {
      if (o) o->AddRef();
      IRefObj* old = oldAsync;
      req->mpAsync = o;
      if (old) old->Release();
    }
    IStreamLike* pStream = mpStream;
    IRefObj* oldBody = req->mpBody;
    if (pStream != oldBody) {
      if (pStream) pStream->AddRef();
      IRefObj* old = oldBody;
      req->mpBody = pStream;
      if (old) old->Release();
    }
    int n = mpStream->GetSize();
    if (n != -1) {
      uint32_t buf[16];
      Sprintf8((char*)buf, "%d", n);
      ((HeaderMap*)req->mHeaders)->Add(0x26, (char*)buf);
      ((HeaderMap*)req->mHeaders)->Add(0x2a, "text/xml");
      req->AddRef();
      req->mCallbackVtbl = 0x015206f0;
      *ppRequest = req.mpObject;
      return true;
    }
  }
  GetMessageServer_s0061_8150()->PostMSG(0x060ba744, 0, 0);
  return false;
}
}}  // namespace SP::Pollen









// @ 0x00618890
namespace eastl {
string8_s0061_8150 operator+(const string8_s0061_8150& a, const string8_s0061_8150& b)
{
  string8_s0061_8150 result(string8_s0061_8150::CtorDoNotInitialize(), a.size() + b.size());
  result.append(a);
  result.append(b);
  return result;
}
}  // namespace eastl









// @ 0x006188f0
namespace eastl {
template <> string8_s0061_8150& string8_s0061_8150::append_sprintf_va_list(const char* pFormat, void* arguments)
{
  const int nInitialSize = (int)(mpEnd - mpBegin);
  int nCount;
  if (mpBegin == gEmptyString)
    nCount = Vsnprintf8(mpEnd, 0, pFormat, arguments);
  else
    nCount = Vsnprintf8(mpEnd, (unsigned int)(mpCapacity - mpEnd), pFormat, arguments);
  if (nCount >= (int)(mpCapacity - mpEnd)) {
    set_capacity(nInitialSize + nCount);
    nCount = Vsnprintf8(mpBegin + nInitialSize, (unsigned int)(nCount + 1), pFormat, arguments);
  } else if (nCount < 0) {
    unsigned int nCapacity = max_alt((unsigned int)7, (unsigned int)(mpEnd - mpBegin) * 2);
    for (; (nCount < 0) && (nCapacity < 1000000); nCapacity *= 2) {
      set_capacity(nCapacity);
      nCount = Vsnprintf8(mpBegin + nInitialSize, nCapacity - nInitialSize + 1, pFormat, arguments);
    }
  }
  if (nCount >= 0) mpEnd = mpBegin + nInitialSize + nCount;
  return *this;
}
}  // namespace eastl









// @ 0x006189e0
namespace SP { namespace Pollen {
unsigned int* UnguardedPartition(unsigned int* first, unsigned int* last, unsigned int pivot, EntryKeyGreater cmp)
{
  for (;;) {
    while (cmp(*first, pivot)) ++first;
    --last;
    while (cmp(pivot, *last)) --last;
    if (!(first < last)) return first;
    unsigned int t = *first;
    *first = *last;
    *last = t;
    ++first;
  }
}
}}  // namespace SP::Pollen









// @ 0x00618a60
namespace SP { namespace Pollen {
void make_heap(unsigned int* first, unsigned int* last, EntryKeyGreater cmp)
{
  const int heapSize = (int)(last - first);
  if (heapSize >= 2) {
    int parentPosition = ((heapSize - 2) >> 1) + 1;
    do {
      --parentPosition;
      unsigned int temp = *(first + parentPosition);
      AdjustHeap(first, parentPosition, heapSize, parentPosition, temp, cmp);
    } while (parentPosition != 0);
  }
}
}}  // namespace SP::Pollen









// @ 0x00618aa0
namespace SP { namespace Pollen {
void sort_heap(unsigned int* first, unsigned int* last, EntryKeyGreater cmp)
{
  for (; (last - first) > 1; --last) {
    unsigned int tempBottom = *(last - 1);
    *(last - 1) = *first;
    AdjustHeap(first, 0, (int)(last - first - 1), 0, tempBottom, cmp);
  }
}
}}  // namespace SP::Pollen









// @ 0x00618af0
namespace SP { namespace Pollen {
string8N::string8N(const string8N& x)
: mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(x.mAllocator) {
  RangeInitialize(x.mpBegin, x.mpEnd);
}
}}  // namespace SP::Pollen









// @ 0x00618b90
namespace SP { namespace Pollen {
cMsgString8::~cMsgString8()
{}
}}  // namespace SP::Pollen









// @ 0x00618c70
namespace SP { namespace Pollen {
void FillFeedInfo(const FeedSource* src, FeedInfo* dst)
{
  dst->mURI = src->mURI;
  dst->mURIHash = FNVHash(dst->mURI.mpBegin, 0x811c9dc5, 1);
  dst->mTitle = src->mTitle;
  dst->mDesc = src->mDesc;
  dst->mKey[0] = src->mKey[0];
  dst->mKey[1] = src->mKey[1];
  dst->mKey[2] = src->mKey[2];
  dst->mExtra = src->mExtra;
  dst->mFeedType = GetFeedTypeFromURI(src->mURI.mpBegin);
  if (src->mpAuthor) {
    dst->mAuthorName = src->mpAuthor->mName;
    dst->mAuthorId0 = src->mpAuthor->mId0;
    dst->mAuthorId1 = src->mpAuthor->mId1;
  }
}
}}  // namespace SP::Pollen









// @ 0x00618d40
namespace SP { namespace Pollen {
cFeedTransactionBase::cFeedTransactionBase(uint32_t type, uint32_t intParam, uint32_t count, uint32_t unk18)
: mpFeed(0), mFeedType(type), mnIntParam(intParam), mnCount(count), mUnk18(unk18), mFlag(0) {
}
}}  // namespace SP::Pollen









// @ 0x00618da0
namespace SP { namespace Pollen {
cFeedTransactionBase::cFeedTransactionBase(uint32_t type, const char* str, uint32_t intParam)
: mpFeed(0), mFeedType(type), mnIntParam(intParam), mnCount(0xffffffff), mUnk18(0),
      mStringParam(string8_s0061_8150::CtorZero()), mFlag(0) {
  mStringParam.RangeInit(str);
}
}}  // namespace SP::Pollen









// @ 0x00618e30
namespace SP { namespace Pollen {
cGetAssetFeedTransactionEx::~cGetAssetFeedTransactionEx()
{}
}}  // namespace SP::Pollen









// @ 0x00618e70
namespace SP { namespace Pollen {
cEditFeedTransaction_s0061_8150::~cEditFeedTransaction_s0061_8150()
{ mpFeed.reset(); }
}}  // namespace SP::Pollen









// @ 0x00618f60
namespace SP { namespace Pollen {
bool cFeedEntryAssetTransaction::ConstructRequest(void** ppRequest)
{
  AtomDocument* doc = mpFeed;
  if (doc) {
    if (mIndex <= (unsigned int)(doc->mpEntriesEnd - doc->mpEntriesBegin)) {
      AtomEntry* entry = doc->mpEntriesBegin + mIndex;
      if (GetSaveArea(0x11ac19d)) {
        mTarget.Set(new ("Pollinator", 0, 0, 0, 0) DownloadTarget());
        mSession.Set(new ("Pollinator", 0, 0, 0, 0) DownloadSession());
        mSession.mp->Bind(mTarget.mp);
        uint32_t* dst = (uint32_t*)((char*)mTarget.mp + 8);
        dst[0] = mKey[0];
        dst[1] = mKey[1];
        dst[2] = mKey[2];
        void* stream = mSession.mp ? (char*)mSession.mp + 8 : 0;
        ReqPtrEx req;
        if (CreateHTTPGetRequest(entry->mURL, stream, (HTTPRequest_s0061_8150**)&req)) {
          _InterlockedExchangeAdd(&req.mpObject->mRefCount, 1);
          {
            string8_s0061_8150 ctx("context");
            req.mpObject->SetProperty(&ctx, (char*)mpFeed + 8);
          }
          req.mpObject->mCallbackVtbl = 0x015206f0;
          *ppRequest = req.mpObject;
        }
        return true;
      }
    }
  }
  return false;
}
}}  // namespace SP::Pollen









// @ 0x00619150
namespace SP { namespace Pollen {
cDeleteMyFeedTransaction_s0061_9150::cDeleteMyFeedTransaction_s0061_9150(const char* uri)
: mURI(uri) {}
}}  // namespace SP::Pollen








// @ 0x006191d0
namespace SP { namespace Pollen {
cFeedUnsubscribeTransaction_s0061_9150::cFeedUnsubscribeTransaction_s0061_9150(const char* uri)
: mURI(uri) {}
}}  // namespace SP::Pollen








// @ 0x00619250
namespace SP { namespace Pollen {
cSnapshotUploadTransaction_s0061_9150::cSnapshotUploadTransaction_s0061_9150(const Key& key, const char* myEmail, const char* destEmail, const char* message, const char* locale)
: mKey(key),
      mMyEmailAddress(myEmail),
      mDestinationEmailAddress(destEmail),
      mMessageText(message),
      mLocale(locale) {}
}}  // namespace SP::Pollen








// @ 0x00619300
namespace SP { namespace Pollen {
cYouTubeAuthenticationTransaction_s0061_9150::cYouTubeAuthenticationTransaction_s0061_9150(const char* username, const char* password, const char* source, bool check)
: mUsername(username), mPassword(password), mSource(source), mCheckRegistration(check) {}
}}  // namespace SP::Pollen








// @ 0x00619390
namespace SP { namespace Pollen {
cYouTubeVideoUploadTransaction_s0061_9150::cYouTubeVideoUploadTransaction_s0061_9150(const char* username, const char* clientID, const char* authToken, const char* devKey, const char* videoFilename, Key videoKey, const char* xmlRequest)
: mUsername(username),
      mClienID(clientID),
      mAuthenticationToken(authToken),
      mDeveloperKey(devKey),
      mVideoFilename(videoFilename),
      mVideoKey(videoKey),
      mXMLRequest(xmlRequest) {}
}}  // namespace SP::Pollen








// @ 0x00619470
namespace SP { namespace Pollen {
cYouTubeVideoURLTransaction_s0061_9150::cYouTubeVideoURLTransaction_s0061_9150(const char* myEmail, const char* destEmail, const char* message, const char* locale)
: mMyEmailAddress(myEmail),
      mDestinationEmailAddress(destEmail),
      mMessageText(message),
      mLocale(locale) {}
}}  // namespace SP::Pollen








// @ 0x00619530
void partial_sort(unsigned int* first, unsigned int* middle, unsigned int* last, TimeGreater compare)
{
  MakeHeap(first, middle, compare);
  for (unsigned int* i = middle; i < last; ++i) {
    if (compare(*i, *first)) {
      unsigned int temp = *i;
      *i = *first;
      AdjustHeap(first, 0, (int)(middle - first), 0, temp, compare);
    }
  }
  SortHeap(first, middle, compare);
}








// @ 0x006195d0
FeedDescription** uninitialized_copy_rev(FeedDescription** ppResult, FeedDescription* last, FeedDescription* first, FeedDescription* dest)
{
  *ppResult = dest;
  while (last != first) {
    --last;
    if (*ppResult) new (*ppResult) FeedDescription(*last);
    ++*ppResult;
  }
  return ppResult;
}








// @ 0x00619650
FeedDescription* copy_rev(FeedDescription* first, FeedDescription* last, FeedDescription* dest)
{
  if (first == last) return dest;
  do {
    --first;
    *dest = *first;
    ++dest;
  } while (first != last);
  return dest;
}








// @ 0x006196c0
namespace SP { namespace Pollen {
bool cModelUploadTransaction_s0061_96c0::ConstructRequest(EA::Internet::HTTPRequest_s0061_96c0** ppRequest)
{
  mnNextAssetID = *mpAssetMetadata->GetAssetID();
  if (mpAssetMetadata) {
    const uint64_t* idp = mpAssetMetadata->GetAssetID();
    if ((uint32_t)*idp != 0xffffffff || (uint32_t)(*idp >> 32) != 0xffffffff) {
      EA::Internet::HTTPMultipartFormDataPostBodyStream_s0061_96c0* stream =
          new ("Pollinator", 0, 0, 0, 0) EA::Internet::HTTPMultipartFormDataPostBodyStream_s0061_96c0;
      if (stream) stream->AddRef();

      uint32_t typeCode = mKey.mType;
      const char* contentType = "text/xml";
      unsigned numImages = 1;
      if (typeCode == 0x366a930d) {
        typeCode = 0xe22261b7;
        contentType = "application/x-gzip";
        numImages = 4;
      }

      string8_s0061_96c0 typeStr;
      string8_s0061_96c0 summaryStr;
      string8_s0061_96c0 nameStr;
      string8_s0061_96c0::sprintf(&nameStr, "%ls", mpAssetMetadata->GetName());
      string8_s0061_96c0::sprintf(&summaryStr, "%ls", mpAssetMetadata->GetSummary());
      string8_s0061_96c0::sprintf(&typeStr, "0x%08x", mKey.mType);

      if (!stream->AddField("TypeId", typeStr.mpBegin)) {
        OnFailure();
        return false;
      }

      bool idFailed;
      {
        string8_s0061_96c0 idStr;
        uint64_t id = *mpAssetMetadata->GetAssetID();
        string8_s0061_96c0::sprintf(&idStr, "%llu", id);
        idFailed = !stream->AddField("assetId", idStr.mpBegin);
      }
      if (idFailed) {
        OnFailure();
        return false;
      }

      if (summaryStr.mpBegin != summaryStr.mpEnd) {
        if (!stream->AddField("description", summaryStr.mpBegin)) {
          OnFailure();
          return false;
        }
      }

      unsigned tagCount = mpAssetMetadata->GetTagCount();
      if (tagCount > 0) {
        string8_s0061_96c0 tags;
        string8_s0061_96c0::sprintf(&tags, "%ls", mpAssetMetadata->GetTag(0));
        for (unsigned i = 1; i < tagCount; ++i)
          string8_s0061_96c0::append_sprintf(&tags, ", %ls", mpAssetMetadata->GetTag(i));
        if (!stream->AddField("tags", tags.mpBegin)) {
          OnFailure();
          return false;
        }
      }

      unsigned traitCount = mpAssetMetadata->GetTraitCount();
      if (traitCount > 0) {
        string8_s0061_96c0 traits;
        string8_s0061_96c0::sprintf(&traits, "0x%08x", mpAssetMetadata->GetTrait(0));
        for (unsigned i = 1; i < traitCount; ++i)
          string8_s0061_96c0::append_sprintf(&traits, ", 0x%08x", mpAssetMetadata->GetTrait(i));
        if (!stream->AddField("traitguids", traits.mpBegin)) {
          OnFailure();
          return false;
        }
      }

      IResourceManager_s0061_96c0* mgr = EA::ResourceMan::GetManager_s0061_96c0();
      IResource* pRes = 0;
      if (!mgr->GetResource(&mKey, &pRes, 0, 0, 0, 0)) {
        OnFailure();
        if (pRes) pRes->Release();
        return false;
      }

      EA::RefPtr_s0061_96c0<Graphics::GraphicsFactoryAsyncRequest> gfar;
      {
        Graphics::GraphicsFactoryAsyncRequest* g =
            new ("Pollinator", 0, 0, 0, 0) Graphics::GraphicsFactoryAsyncRequest(0, 0, "UTF/MemoryStream");
        gfar.assign(g);
      }
      Graphics::GraphicsFactoryAsyncRequest* gf = gfar.p;
      gf->SetProperty(1, 1.0f);
      gf->SetProperty(2, 2.0f);
      gf->Start(0, 0);

      void* ready = 0;
      {
        ResKey zeroKey;
        ResourceReadRequest req(0, gf, &zeroKey, false, false);
        IRecordSource* db = mgr->GetDatabase(mKey.mType, -1);
        if (db && db->ReadInto(pRes, &req, 0, typeCode)) {
          gf->Start(0, 0);
          ready = gf;
        }
      }
      if (!ready || !stream->AddFile("ModelData", ready, contentType, nameStr.mpBegin, 0)) {
        stream->Abort();
        OnFailure();
        if (pRes) pRes->Release();
        return false;
      }

      EA::RefPtr_s0061_96c0<IThumbData> pThumb;
      ResKey thumbKey = mKey;
      thumbKey.mType = 0x2f7d0004;
      IRecordSource* src = mgr->FindSource(&thumbKey);
      if (!src || !src->GetThumb(&thumbKey, pThumb.Reset(), 1, 6, 1, 0)) {
        stream->Abort();
        OnFailure();
        return false;
      }
      if (!stream->AddFile("ThumbnailData", pThumb.p->GetBuffer(), "image/png", nameStr.mpBegin, 0)) {
        stream->Abort();
        OnFailure();
        return false;
      }

      for (unsigned i = 0; i < numImages;) {
        ResKey imgKey;
        imgKey.mInstance = mKey.mInstance;
        imgKey.mType = mKey.mType;
        unsigned n = i + 1;
        imgKey.mGroup = mKey.mGroup ^ ((n ^ mKey.mGroup) & 0xff);
        imgKey.mType = 0x2f7d0004;
        IRecordSource* isrc = mgr->FindSource(&imgKey);
        bool have = isrc && isrc->GetThumb(&imgKey, pThumb.Reset(), 1, 6, 1, 0);
        if (!have && i == 0) {
          IRecordSource* fb = mgr->FindSource(&thumbKey);
          if (!fb || !fb->GetThumb(&thumbKey, pThumb.Reset(), 1, 6, 1, 0)) {
            stream->Abort();
            OnFailure();
            return false;
          }
          have = true;
        }
        if (have) {
          void* data = pThumb.p->GetBuffer();
          string8_s0061_96c0 field("ImageData");
          if (i != 0) string8_s0061_96c0::append_sprintf(&field, "_%d", n);
          if (!stream->AddFile(field.mpBegin, data, "image/png", nameStr.mpBegin, 0)) {
            stream->Abort();
            OnFailure();
            return false;
          }
        }
        i = n;
      }

      string8_s0061_96c0 url;
      MapLookup(0x5387572, &url);
      EA::Internet::HTTPRequestRef request;
      if (!EA::Internet::HTTPRequest_s0061_96c0::CreateHTTPPostRequest(url.mpBegin, stream, 0, request.Reset())) {
        stream->Abort();
        // locals unwind (request, url, ...), then the common failure tail below
      } else {
        request.AddRef();
        uint64_t parentId = 0xffffffffffffffffULL;
        uint64_t origParentId = 0xffffffffffffffffULL;
        GetParentServerID(mpAssetMetadata, &parentId, &origParentId);
        if ((uint32_t)parentId != 0xffffffff || (uint32_t)(parentId >> 32) != 0xffffffff) {
          if (parentId != mnNextAssetID) {
            string8_s0061_96c0 parentField("parent");
            string8_s0061_96c0 parentVal;
            request.p->SetFieldStr(parentField, string8_s0061_96c0::sprintf(&parentVal, "%llu", parentId));
          }
        }
        if (mpAssetMetadata) {
          const uint64_t* pp = mpAssetMetadata->GetParentAssetID();
          bool same = parentId == *pp;
          if (same) same = origParentId == *mpAssetMetadata->GetOriginalParentAssetID();
          if (!same) {
            mpAssetMetadata->SetParentAssetID(parentId);
            mpAssetMetadata->SetOriginalParentAssetID(origParentId);
            EA::ResourceMan::GetManager_s0061_96c0()->SaveResource(mpAssetMetadata, 0, 0, 0, 0);
            SP::Thumbnail::cImportExport_s0061_96c0* ie = SP::Thumbnail::GetImportExport();
            if (ie) ie->UpdateExportThumb(&mKey);
          }
        }
        request.p->SetField("slurp", mbSlurp ? "1" : "0");
        if (mbBound) request.p->SetField("bound", "1");

        cServerResponse_s0061_96c0* resp = new ("Pollinator", 0, 0, 0, 0) cServerResponse_s0061_96c0;
        EA::RefPtr_s0061_96c0<cServerResponse_s0061_96c0> respPtr(resp);
        resp->Open();
        request.p->mpHandler.assign(resp ? &resp->mHandler : 0);
        request.p->mpCallbacks = kResponseCallbacks;
        *ppRequest = request.p;
        return true;
      }
    }
  }
  OnFailure();
  return false;
}
}}  // namespace SP::Pollen







// @ 0x0061a650
namespace SP { namespace Pollen {
bool AssetFeedGetRequest(void** ppRequest)
{
  (void)ppRequest;
  return false;
}
}}  // namespace SP::Pollen






// @ 0x0061a810
namespace SP { namespace Pollen {
cGetAssetFeedTransaction_s0061_a650::cGetAssetFeedTransaction_s0061_a650(uint32_t lo, uint32_t hi)
: cFeedTransactionBase_s0061_a650(3, (const char*)0x013ec47c, 0) {
  string8_s0061_a650 tmp(eastl::basic_string_s0061_a650<char>::CtorSprintf(), "%I64u", lo, hi);
  mStringParam.assign(tmp.mpBegin, tmp.mpEnd);
  mFlag = 1;
}
}}  // namespace SP::Pollen






// @ 0x0061a8b0
namespace SP { namespace Pollen {
cGetAssetFeedTransactionEx_s0061_a650::cGetAssetFeedTransactionEx_s0061_a650(uint32_t lo, uint32_t hi)
: cFeedTransactionBase_s0061_a650(3, (const char*)0x013ec47c, 0), mId((uint64_t)lo | ((uint64_t)hi << 32)) {
  mExtra.mpBegin = 0;
  mExtra.mpEnd = 0;
  mExtra.mpCapacity = 0;
  string8_s0061_a650 tmp(eastl::basic_string_s0061_a650<char>::CtorSprintf(), "%I64u", lo, hi);
  mStringParam.assign(tmp.mpBegin, tmp.mpEnd);
  mFlag = 1;
}
}}  // namespace SP::Pollen






// @ 0x0061a970
namespace SP { namespace Pollen {
cEditFeedTransaction_s0061_a650::cEditFeedTransaction_s0061_a650(int opType)
: mpFeed(0), mOpType(opType), mFeedURI(), mFeedDescription(), mAssetsToAdd(), mAssetsToRemove() {}
}}  // namespace SP::Pollen






// @ 0x0061aa00
namespace SP { namespace Pollen {
bool cUserMatchTransaction_s0061_a650::ConstructRequest(void** ppRequest)
{
  (void)ppRequest;
  return false;
}
}}  // namespace SP::Pollen






// @ 0x0061abf0
namespace SP { namespace Pollen {
bool UserMatchGetRequest(void** ppRequest)
{
  (void)ppRequest;
  return false;
}
}}  // namespace SP::Pollen






// @ 0x0061ad70
namespace SP { namespace Pollen {
bool cHandshakeTransaction_s0061_a650::ConstructRequest(void** ppRequest)
{
  (void)ppRequest;
  return false;
}
}}  // namespace SP::Pollen






// @ 0x0061b0e0
bool SP::Pollen::cTelemetryUploadTransaction::ConstructRequest(EA::Internet::HTTPRequest ** ppRequest)
{
  (void)ppRequest;
  return false;
}






// @ 0x0061b3b0
bool SP::Pollen::cYouTubeAuthenticationTransaction::HandleResult(unsigned int ppRequest, EA::Internet::HTTPResponse * a2, SP::Pollen::cTransactionQueue & a3)
{
  (void)ppRequest;
  return false;
}





// @ 0x0061b620
bool SP::Pollen::cYouTubeVideoUploadTransaction::ConstructRequest(EA::Internet::HTTPRequest ** ppRequest)
{
  (void)ppRequest;
  return false;
}





// @ 0x0061b9a0
namespace SP { namespace Pollen {
bool PollenRequestHelper(void* self, void* arg)
{
  (void)self;
  (void)arg;
  return false;
}
}}  // namespace SP::Pollen





// @ 0x0061bbc0
namespace SP { namespace Pollen {
void quick_sort_impl(unsigned int* first, unsigned int* last, int kRecursionCount, TimeGreater_s0061_b3b0 compare)
{
  while (((last - first) > 28) && (kRecursionCount > 0)) {
    unsigned int* const position = get_partition(
        first, last, median(*first, *(first + (last - first) / 2), *(last - 1), compare), compare);
    quick_sort_impl(position, last, --kRecursionCount, compare);
    last = position;
  }
  if (kRecursionCount == 0) partial_sort(first, last, last, compare);
}
}}  // namespace SP::Pollen





// @ 0x0061bcf0
namespace SP { namespace Pollen {
void WritePropertyListAndPNG(void* self, void* a, void* b, void* c)
{
  (void)self;
  (void)a;
  (void)b;
  (void)c;
}
}}  // namespace SP::Pollen





// @ 0x0061c1c0
namespace SP { namespace Pollen {
void* AllocateAndCopy70(unsigned int n, void* a, void* b)
{
  (void)a;
  (void)b;
  if (n == 0) return 0;
  return EASTL_allocator_allocate(n * 0x70, "Editor", 0, 0, "EASTL/allocator.h", 0xd1);
}
}}  // namespace SP::Pollen





// @ 0x0061c350
namespace SP { namespace Pollen {
bool cAssetFeedTransaction::HandleResult(int code, void* result, Deque* queue)
{
  if (result) {
    void* o = PI(result, 0xf3c);
    if (o) VFN(o, 0x18, void, (void*))(o);
  }
  if (code != 0) return false;
  cAssetDirectory_s0061_c350* dir = GetPollenMgr()->mpDirectory;
  char* feed = (char*)PI(this, 8);
  char* e = (char*)PI(feed, 0x60);
  char* end = (char*)PI(feed, 0x64);
  for (; e != end; e += 0x118) {
    unsigned ka = U(e, 0x10), kb = U(e, 0x14);
    Key3 local = { 0, 0, 0 };
    if (ka == U(this, 0xf0) && kb == U(this, 0xf4) && dir && dir->GetLocalKey(ka, kb, &local)) {
      unsigned* a = (unsigned*)PI(e, 0x8c);
      unsigned* aend = (unsigned*)PI(e, 0x90);
      for (; a != aend; a += 5) {
        unsigned key = *a;
        FeedEvent* ev;
        for (;;) {
          void** h = (void**)gFeedEventPoolHead;
          if (h) {
            gFeedEventPoolHead = *h;
            ev = (FeedEvent*)h;
            if (ev) {
              new (ev) FeedEvent((int*)PI(this, 8), (int)((e - (char*)PI(feed, 0x60)) / 0x118), key, local);
            }
            break;
          }
          if (!gFeedEventPool.AddCore(0, 0)) { ev = 0; break; }
        }
        queue->Push(ev, 1);
        unsigned* vb = (unsigned*)PI(this, 0xf8);
        unsigned* ve = (unsigned*)PI(this, 0xfc);
        unsigned* it = LowerBound(vb, ve, &key, *(char*)((char*)this + 0x10c));
        if (it == ve) {
          if (ve == (unsigned*)PI(this, 0x100)) {
            ((SortedUIntVec*)((char*)this + 0xf8))->Insert(it, &key);
          } else {
            PI(this, 0xfc) = ve + 1;
            if (ve) *ve = key;
          }
        } else if (key < *it) {
          ((SortedUIntVec*)((char*)this + 0xf8))->Insert(it, &key);
        }
      }
      return true;
    }
  }
  return false;
}
}}  // namespace SP::Pollen

// @ 0x0061c880
namespace SP { namespace Pollen {
unsigned RequestAssetsFromFeed(void* feed, unsigned maxCount, Deque* queue, char flag)
{
  unsigned count = 0;
  cPollenMgr* mgr = GetPollenMgr();
  cAssetDirectory_s0061_c350* dir = mgr->mpDirectory;
  if (PI(feed, 0x60) == PI(feed, 0x64)) return 0;
  char notifyDone = *(char*)((char*)feed + 0x74);
  GetSaveArea(0x11ac19d);
  GetResourceManager();
  IndexVec idx = { 0, 0, 0 };
  idx.Resize((unsigned)(((char*)PI(feed, 0x64) - (char*)PI(feed, 0x60)) / 0x118));
  unsigned* ib = idx.mpBegin;
  unsigned n = (unsigned)(idx.mpEnd - idx.mpBegin);
  for (unsigned i = 0; i < n; i++) ib[i] = i;
  SortFeedIndices(idx.mpBegin, idx.mpEnd, feed);
  unsigned* ip = ib;
  if (ip != idx.mpEnd) {
    do {
      if (maxCount <= count) break;
      unsigned entryIdx = *ip;
      char* entry = (char*)PI(feed, 0x60) + entryIdx * 0x118;
      unsigned ka = U(entry, 0x10), kb = U(entry, 0x14);
      if ((ka != 0 || kb != 0) && (ka & kb) != 0xffffffff) {
        Key3 local = { 0, 0, 0 };
        bool found = dir->GetLocalKey(ka, kb, &local);
        if (!found) {
          if (!flag) {
            cAssetMetadata_s0061_c350* md = new("Pollinator", 0, 0, 0, 0) cAssetMetadata_s0061_c350();
            if (md) md->AddRef();
            bool ok = SetAssetData(PI(entry, 0xc8), 0);
            IDGen* gen = *(IDGen**)IDGenerator();
            unsigned x = FUN_004bbc70(PI(entry, 0xc8), 1, 0, ok ? 0x62 : 0, 0);
            ((IDGen*)gen)->Register(&local, PI(entry, 0xc8), (void*)x);
            local.b = (unsigned)I(entry, 0xc8);
            struct { wchar_t* b; wchar_t* e; wchar_t* c; } ws = { gEmptyWide, gEmptyWide, gEmptyWide + 1 };
            WStr_Format(&ws, L"%s(%llu)", PI(entry, 0x18), ka, kb);
            Key3 saved = local;
            if (md->GetCreatureName(&local, entry, (char*)feed + 8)) {
              U(md, 8) = saved.a;
              U(md, 0xc) = 0x30bdee3;
              U(md, 0x10) = saved.c;
              unsigned* kp = md->GetKeyPair();
              dir->AddMapping(kp[0], kp[1], &local);
              kp = md->GetKeyPair();
              dir->FUN_0054e7b0(kp[0], kp[1], 1);
              if (ok) {
                TxA* t = (TxA*)AllocTx28(0x28);
                Deque* q = queue;
                void* r = t ? t->Init(local, md, feed, (void*)entryIdx, 0) : 0;
                q->Push(r, 1);
                TxB* t2 = (TxB*)AllocTx24(0x24);
                void* r2 = t2 ? t2->Init(&local, feed, (void*)entryIdx) : 0;
                q->Push(r2, 1);
              } else if (local.b == 0x366a930d) {
                TxA* t = (TxA*)AllocTx28(0x28);
                void* r = t ? t->Init(local, md, feed, (void*)entryIdx, 1) : 0;
                queue->Push(r, 1);
              }
              count++;
            }
            if (((char*)ws.c - (char*)ws.b & ~1) > 2 && ws.b) operator_delete_arr(ws.b);
            if (md) md->Release();
          }
        } else if (!flag) {
          Key3 k = { local.a, 0x30bdee3, local.c };
          void* obj = 0;
          void* rm = GetResourceManager();
          if (obj) { void* o = obj; obj = 0; VFN(o, 4, void, (void*))(o); }
          if (VFN(rm, 0xc, bool, (void*, Key3*, void**, int, int, int, int))(rm, &k, &obj, 0, 0, 0, 0)) {
            cAssetMetadata_s0061_c350* md2 = obj ? (cAssetMetadata_s0061_c350*)VFN(obj, 0xc, void*, (void*, unsigned))(obj, 0x30bdee3) : 0;
            int before = md2->FUN_005508e0();
            if (md2->UpdateFromEntry(entry, (char*)feed + 8)) {
              U(obj, 8) = k.a;
              U(obj, 0xc) = k.b;
              U(obj, 0x10) = k.c;
              void* sa = GetSaveArea(0x11ac19d);
              FUN_006ac0a0(10, obj);
              FUN_006ad010(obj);
              FUN_00616d60(obj, sa, 0);
              unsigned* kp = md2->GetKeyPair();
              if (!dir->FUN_0054e740(kp[0], kp[1]) && before != md2->FUN_005508e0()) {
                struct { unsigned hash; int one; Key3 key; } msg;
                msg.hash = FNV1_String8(*(const char**)((char*)feed + 8), 0x811c9dc5, 0);
                msg.one = 1;
                msg.key = local;
                GetMessageServer_s0061_c350()->Post(0x64e331c, &msg, 0);
              }
            }
          }
          if (obj) VFN(obj, 4, void, (void*))(obj);
        }
        if (local.a != 0) {
          GetPollenMgr();
          if (GetPollenMgr()->mpCache->FUN_00613860(local.b)) {
            VariantMapVec vv;
            vv.mpBegin = vv.mpEnd = vv.buf;
            vv.mpFixed = vv.buf; vv.mpFixedEnd = vv.buf + sizeof(vv.buf); vv.mpCapacity = vv.buf + sizeof(vv.buf);
            char* ap = (char*)PI(entry, 0x78);
            while (ap != (char*)PI(entry, 0x7c)) {
              unsigned h = FNV1_String16(*(const wchar_t**)ap, 0x811c9dc5, 1);
              Variant* v = (Variant*)vv.Index(&h);
              *v = *(Variant*)(ap + 0x20);
              ap += 0x34;
            }
            GetPollenMgr()->mpCache->AddAsset(ka, kb, &vv);
            for (char* vp = vv.mpBegin + 4; vp < vv.mpEnd; vp += 0x18) {
              if (*(unsigned char*)(vp + 0x10) & 4) VariantDestruct(vp, 0);
            }
            if (vv.mpBegin && vv.mpBegin != vv.mpFixed) operator_delete_arr(vv.mpBegin);
          }
        }
      }
      ip++;
    } while (ip != idx.mpEnd);
  } else {
    count = 0;
  }
  if (notifyDone && count) {
    struct { unsigned count; int a; int b; } msg;
    msg.count = count;
    msg.a = I(feed, 0x1c);
    msg.b = (PI(feed, 0x78) == PI(feed, 0x7c)) ? 0 : I(feed, 0x78);
    GetMessageServer_s0061_c350()->Post(0x7bd0aaa, &msg, 0);
  }
  if (idx.mpBegin && ((int*)idx.mpBegin)[-1]) operator_delete_arr(idx.mpBegin);
  return count;
}
}}  // namespace SP::Pollen

// @ 0x0061d1c0
namespace SP { namespace Pollen {
cFeedStateTransaction::cFeedStateTransaction()
: m40(0), m44(0), m48(0xffffffff), m4c(0), mV60(0), mV64(0), mV68(0), m74(0) {}
}}  // namespace SP::Pollen

// @ 0x0061d240
namespace SP { namespace Pollen {
void* AssetHelper288(void* self, void* a)
{
  (void)a;
  return self;
}
}}  // namespace SP::Pollen



// @ 0x0061d380
namespace SP { namespace Pollen {
bool GetAssetFeedConstructRequest(void* self, void* ppRequest)
{
  (void)self;
  (void)ppRequest;
  return false;
}
}}  // namespace SP::Pollen



// @ 0x0061d960
namespace SP { namespace Pollen {
bool EditFeedConstructRequest(void* self, void* ppRequest)
{
  (void)self;
  (void)ppRequest;
  return false;
}
}}  // namespace SP::Pollen



// @ 0x0061de00
namespace SP { namespace Pollen {
bool cHandshakeTransaction_s0061_d240::HandleResult(int code, void* result, void* queue)
{
  (void)code;
  (void)result;
  (void)queue;
  return false;
}
}}  // namespace SP::Pollen
