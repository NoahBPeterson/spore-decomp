// src/game/SPEditors/SPPollinatorServerResponse.cpp -- migrated from slice(s) s006755c0, s00614f20, s00614050 by tools/migrate/rewrite.py
// Object file: SPEditors/SPPollinatorServerResponse.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/Pollen/cServerResponse.h"
#include "SP/Pollen/cAssetDirectory.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
extern const wchar_t kSuccessText[];   // 0x013fc0d4 L"Success"
extern const wchar_t kFailureText[];   // 0x013fc0c4 L"Failure"
#include <intrin.h>
#include "EA/ResourceMan/Key.h"
#include "SP/Pollen/cAssetMetadata.h"
#include "SP/Pollen/cModelUploadTransaction.h"
#include "SP/Pollen/cTransactionQueue.h"
#include "position.h"
#include "XML_Memory_Handling_Suite.h"
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(wcscmp)

// ---- items of slice s00614050 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int size_type;
typedef int off_type;
typedef unsigned __int64 u64;
struct XML_ParserStruct_s0061_4050;
typedef XML_ParserStruct_s0061_4050* XML_Parser;
extern "C" int XML_Parse(XML_Parser p, const char* s, int len, int isFinal);
extern "C" void XML_ParserFree(XML_Parser p);
extern "C" int XML_GetErrorCode(XML_Parser p);
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
inline void* operator new(unsigned int, void* p) { return p; }
void* EASTL_alloc(unsigned size, const char* name, int flags, int a, const char* file, int line);
void EASTL_free(void* p);
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
namespace EA {
namespace IO {
class IStream_s0061_4050 {
public:
    virtual ~IStream_s0061_4050() {}
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
};
namespace SP {
namespace Pollen {
class cServerResponse_s0061_4050 : public RefCountVBase, public EA::IO::IStream_s0061_4050 {
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

    void GetStatus();  // 0x00614ab0 (SP::Pollen::cServerResponse::GetStatus)
    const wchar_t* GetField(const wchar_t* name);
    static void CharacterData(cServerResponse_s0061_4050* self, const wchar_t* s, int len);
    static void StartElement(cServerResponse_s0061_4050* self, const wchar_t* name);
};
}
}
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
extern const wchar_t kSuccessText[];   // 0x013fc0d4 L"Success"
extern const wchar_t kFailureText[];   // 0x013fc0c4 L"Failure"
// ---- items of slice s00614050 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" int XML_Parse(XML_Parser p, const char* s, int len, int isFinal);
extern "C" void XML_ParserFree(XML_Parser p);
extern "C" int XML_GetErrorCode(XML_Parser p);
extern HandlerMap gElementHandlers;   // 0x015f5088

// ---- items of slice s00614f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyString16[];   // 0x01667bac
extern bool gbDictInit;             // 0x015f4e84
#pragma intrinsic(_ReadWriteBarrier)
struct XML_ParserStruct_s0061_4f20;
typedef XML_ParserStruct_s0061_4f20* XML_Parser_s0061_4f20;
struct XML_Memory_Handling_Suite_s0061_4f20 {
    void* (*malloc_fcn)(size_t);
    void* (*realloc_fcn)(void*, size_t);
    void (*free_fcn)(void*);
};
extern "C" XML_Parser_s0061_4f20 XML_ParserCreate_MM(const char* enc, const XML_Memory_Handling_Suite_s0061_4f20* ms, const char* sep);   // 0x0090aed0
extern "C" void XML_SetUserData(XML_Parser_s0061_4f20 p, void* userData);                                                       // 0x009032e0
extern "C" void XML_SetElementHandler(XML_Parser_s0061_4f20 p, void (*start)(void*, const wchar_t*),
void (*end)(void*, const wchar_t*));                                          // 0x00903300
extern "C" void XML_SetCharacterDataHandler(XML_Parser_s0061_4f20 p, void (*h)(void*, const wchar_t*, int));                    // 0x00903320
const wchar_t* RFindFirstNotOf(const wchar_t* pEnd, const wchar_t* pBegin, const wchar_t* pSet, const wchar_t* pSetEnd);  // 0x00549840
struct string16_s0061_4f20 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int mAllocator;
    enum { npos = (size_type)-1 };
    string16_s0061_4f20() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    string16_s0061_4f20(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    string16_s0061_4f20(const string16_s0061_4f20& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
    ~string16_s0061_4f20() {
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
    string16_s0061_4f20& erase(size_type position, size_type n);            // 0x004228e0
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
    __forceinline int compare_inl(const string16_s0061_4f20& x) const {
        const int n1 = (int)(mpEnd - mpBegin);
        const int n2 = (int)(x.mpEnd - x.mpBegin);
        const int nMin = emin(n1, n2);
        const int c = Compare(mpBegin, x.mpBegin, nMin);
        return c ? c : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0));
    }
    int compare(const string16_s0061_4f20& x) const { return StringCompare(mpBegin, mpEnd, x.mpBegin, x.mpEnd); }
};
struct StrElem { void Construct(const string16_s0061_4f20& s); };
struct less16_s0061_4f20 { bool operator()(const string16_s0061_4f20& a, const string16_s0061_4f20& b) const { return a.compare_inl(b) < 0; } };
struct StrPairMut {    // eastl::pair<string16, string16>
    string16_s0061_4f20 first;
    string16_s0061_4f20 second;
    StrPairMut(const string16_s0061_4f20& a, const string16_s0061_4f20& b);     // 0x0088c0d0
    ~StrPairMut() {}
};
struct StrPair_s0061_4f20 {       // eastl::pair<string16 const, string16>
    string16_s0061_4f20 first;
    string16_s0061_4f20 second;
    StrPair_s0061_4f20(const StrPairMut& x);                      // 0x00614990
    ~StrPair_s0061_4f20() {}
};
StrPairMut MakeStrPair(string16_s0061_4f20 a, string16_s0061_4f20 b);        // 0x00614cc0
struct mem_fun_t_s0061_4f20 {
    void* fn;
    int adj;
};
struct HandlerPair_s0061_4f20 {
    const wchar_t* first;
    int pad;
    mem_fun_t_s0061_4f20 second;
};
struct char16less_s0061_4f20 {
    bool operator()(const wchar_t* a, const wchar_t* b) const { return wcscmp(a, b) < 0; }
};
struct HandlerRange_s0061_4f20 { HandlerPair_s0061_4f20* first; HandlerPair_s0061_4f20* second; };
struct HandlerInsertResult { HandlerPair_s0061_4f20* first; bool second; HandlerInsertResult(HandlerPair_s0061_4f20* f, bool s) : first(f), second(s) {} };
HandlerPair_s0061_4f20* lower_bound_s0061_4f20(HandlerPair_s0061_4f20* first, HandlerPair_s0061_4f20* last, const wchar_t* const& value, char16less_s0061_4f20 c);   // 0x00614a30
HandlerPair_s0061_4f20* CopyPairs(HandlerPair_s0061_4f20* first, HandlerPair_s0061_4f20* last, HandlerPair_s0061_4f20* dest);   // eastl::copy_impl do_copy 0x00705250
struct HandlerMap_s0061_4f20 {
    HandlerPair_s0061_4f20* mpBegin;
    HandlerPair_s0061_4f20* mpEnd;
    HandlerPair_s0061_4f20* mpCapacity;
    int mAlloc;
    int pad4;
    char16less_s0061_4f20 mCompare;     // +0x14
    HandlerRange_s0061_4f20 equal_range(const wchar_t* const& k);             // 0x00614d20
    void reserve(size_type n);                                     // 0x00614c40
    HandlerPair_s0061_4f20* vector_insert(HandlerPair_s0061_4f20* pos, const HandlerPair_s0061_4f20& v);   // 0x00676370
    HandlerInsertResult insert(const HandlerPair_s0061_4f20& value);          // 0x00615080
    void clear() {
        HandlerPair_s0061_4f20* first = mpBegin;
        HandlerPair_s0061_4f20* last = mpEnd;
        CopyPairs(last, mpEnd, first);
        mpEnd -= (last - first);
    }
};
extern HandlerMap_s0061_4f20 gStartHandlers;   // 0x015f5088
extern HandlerMap_s0061_4f20 gEndHandlers;     // 0x015f5024
extern XML_Memory_Handling_Suite_s0061_4f20 gXMLMemorySuite;   // 0x015f4e78
struct RBNode_s0061_4f20 {
    RBNode_s0061_4f20* right; RBNode_s0061_4f20* left; RBNode_s0061_4f20* parent; int mColor;   // low byte: color
    RBNode_s0061_4f20() : left(0), parent(0), mColor(0) {}
};
struct StrNode_s0061_4f20 : RBNode_s0061_4f20 { StrPair_s0061_4f20 mValue; };
RBNode_s0061_4f20* RBTreeDecrement(RBNode_s0061_4f20* n);   // 0x009215c0
struct StrMapIter_s0061_4f20 { StrNode_s0061_4f20* mpNode; };
struct StrInsertResult { StrNode_s0061_4f20* first; bool second; StrInsertResult(StrNode_s0061_4f20* f, bool s) : first(f), second(s) {} };
struct TrueTag {};
struct StrMap_s0061_4f20 {
    char pad0[4];
    RBNode_s0061_4f20 mAnchor;       // +4
    unsigned mnSize;      // +0x14
    int mAlloc;
    ~StrMap_s0061_4f20() { DoNukeSubtree((StrNode_s0061_4f20*)mAnchor.parent); }
    StrMap_s0061_4f20() {
        mAnchor.parent = 0;
        *(char*)&mAnchor.mColor = 0;
        mnSize = 0;
        mAnchor.right = &mAnchor;
        mAnchor.left = &mAnchor;
    }
    StrMapIter_s0061_4f20 DoInsertValueImpl(RBNode_s0061_4f20* pNodeParent, const StrPair_s0061_4f20& value, bool bForceToLeft);   // 0x00614dc0
    StrInsertResult DoInsertValue(const StrPair_s0061_4f20& value, TrueTag);                                  // 0x00614f20
    void DoNukeSubtree(StrNode_s0061_4f20* pNode);                                                           // 0x00615110
    StrInsertResult insert(const StrPair_s0061_4f20& value) { return DoInsertValue(value, TrueTag()); }
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
class RefCountVBase_s0061_4f20 {
public:
    virtual ~RefCountVBase_s0061_4f20() {}
    virtual int AddRef();
    virtual int Release();
    int mnRefCount;
    RefCountVBase_s0061_4f20() : mnRefCount(0) {}
};
namespace SP {
namespace Pollen {
class cServerResponse_s0061_4f20 : public RefCountVBase_s0061_4f20, public EA::IO::IStream_s0061_4f20 {
public:
    int mnReturnCode;                 // +0xc (Code: 0 success, 1 failure, 2 error)
    StrMap_s0061_4f20 mFieldDict;                // +0x10
    struct StrVec {
        string16_s0061_4f20* mpBegin; string16_s0061_4f20* mpEnd; string16_s0061_4f20* mpCapacity;
        StrVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
        void DoDestroyValues(string16_s0061_4f20* b, string16_s0061_4f20* e);   // 0x0084aad0
        ~StrVec() {
            DoDestroyValues(mpBegin, mpEnd);
            if (mpBegin) {
                if (((int*)mpBegin)[-1]) EASTL_free(mpBegin);
            }
        }
        void DoInsertValue(string16_s0061_4f20* pos, const string16_s0061_4f20& x);   // 0x00554c30
        void push_back(const string16_s0061_4f20& value) {
            if (mpEnd < mpCapacity) {
                string16_s0061_4f20* p = mpEnd++;
                if (p) ((StrElem*)p)->Construct(value);
            } else
                DoInsertValue(mpEnd, value);
        }
    } mAssetList;   // +0x2c
    char pad0[0x40 - 0x38];
    XML_Parser_s0061_4f20 mpXMLParser;           // +0x40
    string16_s0061_4f20 mCharacterData;          // +0x44
    bool mbInResponse;                // +0x54
    bool mbOpen;                      // +0x55
    int mParseStatus;                 // +0x58
    int mnBytesRead;                  // +0x5c

    cServerResponse_s0061_4f20();                // 0x00615790
    virtual ~cServerResponse_s0061_4f20();       // 0x00615380
    virtual int AddRef();
    virtual int Release();
    virtual unsigned int GetType() const;
    virtual int GetAccessFlags() const;  // 0x006148c0 (SP::Pollen::cServerResponse::GetAccessFlags)
    virtual int GetState() const;  // 0x006148d0 (SP::Pollen::cServerResponse::GetState)
    virtual bool Close();  // 0x00614880 (SP::Pollen::cServerResponse::Close)
    virtual size_type GetSize() const;
    virtual bool SetSize(size_type size);
    virtual off_type GetPosition(int positionType = 0) const;  // 0x00614900 (SP::Pollen::cServerResponse::GetPosition)
    virtual bool SetPosition(off_type position, int positionType = 0);   // 0x006154c0
    virtual size_type GetAvailable() const;
    virtual size_type Read(void* pData, size_type nSize);                // 0x00615430
    virtual bool Flush();
    virtual bool Write(const void* pData, size_type nSize);  // 0x00614840 (SP::Pollen::cServerResponse::Write)

    bool Open();                                                         // 0x00615450
    void GetStatus();  // 0x00614ab0 (SP::Pollen::cServerResponse::GetStatus)
    void StartPollinatorResponse();   // 0x00614930
    void EndPollinatorResponse();     // 0x00614940
    void Noop();                      // 0x00c2e4e0
    void DefaultEndTag(const wchar_t* tag);                              // 0x00615180
    const wchar_t* GetField(const wchar_t* name);                        // 0x00614e50
    void IDListElement();                                                // 0x00615520
    static void SetupDict();                                             // 0x006155f0
    static void CharacterData(cServerResponse_s0061_4f20* self, const wchar_t* s, int len);  // 0x00614da0 (SP::Pollen::cServerResponse::CharacterData)
    static void StartElement(cServerResponse_s0061_4f20* self, const wchar_t* name);  // 0x00614ed0 (SP::Pollen::cServerResponse::StartElement)
    static void EndElementHandler(cServerResponse_s0061_4f20* self, const wchar_t* name);   // 0x00615330
};
}
}
union PmfCast {
    void (SP::Pollen::cServerResponse_s0061_4f20::*pmf)();
    mem_fun_t_s0061_4f20 m;
};
inline void SetHandler(HandlerPair_s0061_4f20& p, const wchar_t* name, void (SP::Pollen::cServerResponse_s0061_4f20::*pmf)()) {
    PmfCast c;
    c.pmf = pmf;
    p.second.fn = c.m.fn;
    p.second.adj = c.m.adj;
    p.first = name;
}
// ---- items of slice s00614f20 end

// ---- items of slice s006755c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PollenResponsePairsVector {
    char pad[0x1000];
    void* insert(void* pos, const void* value);
};
// ---- items of slice s006755c0 end

// @ 0x00614840
bool SP::Pollen::cServerResponse_s0061_4050::Write(const void* pData, size_type nSize)
{
    if (mbOpen) {
        mParseStatus = XML_Parse(mpXMLParser, (const char*)pData, (int)nSize, 0);
        mnBytesRead += nSize;
        return mParseStatus == 1;
    }
    return false;
}

// @ 0x00614880
bool SP::Pollen::cServerResponse_s0061_4050::Close()
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
int SP::Pollen::cServerResponse::GetAccessFlags() const
{
    return mbOpen ? 2 : 0;
}

// @ 0x006148d0
int SP::Pollen::cServerResponse_s0061_4050::GetState() const
{
    if (mbOpen) {
        if (mParseStatus != 1) return XML_GetErrorCode(mpXMLParser);
        return 0;
    }
    return -2;
}

// @ 0x00614900
long SP::Pollen::cServerResponse::GetPosition(EA::IO::PositionType positionType) const
{
    switch (positionType) {
    case 0: return mBitesRead;
    case 1: return 0;
    case 2: return -1;
    }
    return -1;
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

// @ 0x00614ab0
void SP::Pollen::cServerResponse_s0061_4050::GetStatus()
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
StrPair::~StrPair()
{}

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
void SP::Pollen::cServerResponse_s0061_4050::CharacterData(SP::Pollen::cServerResponse_s0061_4050* self, const wchar_t* s, int len)
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
    StrNode* n = (StrNode*)EASTL_alloc(0x30, "Editor", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (&n->mValue) new (&n->mValue) StrPair(value);
    RBTreeInsert(n, pNodeParent, &mAnchor, side);
    ++mnSize;
    StrMapIter it = { n };
    return it;
}

// @ 0x00614e50
const wchar_t* SP::Pollen::cServerResponse_s0061_4050::GetField(const wchar_t* name)
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
void SP::Pollen::cServerResponse_s0061_4050::StartElement(SP::Pollen::cServerResponse_s0061_4050* self, const wchar_t* name)
{
    self->mCharacterData.resize(0);
    HandlerRange r = gElementHandlers.equal_range(name);
    if (r.first != r.second && r.first != gElementHandlers.mpEnd) {
        typedef void (__thiscall *Fn)(void*);
        ((Fn)r.first->second.fn)((char*)self + r.first->second.adj);
    }
}

// @ 0x00614f20
StrInsertResult StrMap_s0061_4f20::DoInsertValue(const StrPair_s0061_4f20& value, TrueTag)
{
    less16_s0061_4f20 mCompare;
    StrNode_s0061_4f20* pCurrent = (StrNode_s0061_4f20*)mAnchor.parent;
    StrNode_s0061_4f20* pLowerBound = (StrNode_s0061_4f20*)&mAnchor;
    StrNode_s0061_4f20* pParent;
    bool bValueLessThanNode = true;
    while (pCurrent) {
        bValueLessThanNode = mCompare(value.first, pCurrent->mValue.first);
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (StrNode_s0061_4f20*)pCurrent->left;
        else
            pCurrent = (StrNode_s0061_4f20*)pCurrent->right;
    }
    pParent = pLowerBound;
    if (bValueLessThanNode) {
        if (pLowerBound != (StrNode_s0061_4f20*)mAnchor.left)
            pLowerBound = (StrNode_s0061_4f20*)RBTreeDecrement(pLowerBound);
        else {
        {
            const StrMapIter_s0061_4f20 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return StrInsertResult(itResult.mpNode, true);
        }
        }
    }
    if (StringCompare(pLowerBound->mValue.first.mpBegin, pLowerBound->mValue.first.mpEnd,
                      value.first.mpBegin, value.first.mpEnd) < 0) {
        const StrMapIter_s0061_4f20 itResult(DoInsertValueImpl(pParent, value, false));
        return StrInsertResult(itResult.mpNode, true);
    }
    return StrInsertResult(pLowerBound, false);
}

// @ 0x00615080
HandlerInsertResult HandlerMap_s0061_4f20::insert(const HandlerPair_s0061_4f20& value)
{
    HandlerPair_s0061_4f20* const itEnd = mpEnd;
    HandlerPair_s0061_4f20* it = lower_bound_s0061_4f20(mpBegin, itEnd, value.first, mCompare);
    if (it != itEnd && !mCompare(value.first, it->first))
        return HandlerInsertResult(it, false);
    return HandlerInsertResult(vector_insert(it, value), true);
}

// @ 0x00615110
void StrMap_s0061_4f20::DoNukeSubtree(StrNode_s0061_4f20* pNode)
{
    while (pNode) {
        DoNukeSubtree((StrNode_s0061_4f20*)pNode->right);
        StrNode_s0061_4f20* pNodeLeft = (StrNode_s0061_4f20*)pNode->left;
        pNode->mValue.~StrPair_s0061_4f20();
        EASTL_free(pNode);
        pNode = pNodeLeft;
    }
}

// @ 0x00615180
void SP::Pollen::cServerResponse_s0061_4f20::DefaultEndTag(const wchar_t* tag)
{
    mCharacterData.erase(0, mCharacterData.find_first_not_of(L" \t\n\f\r", 0));
    mCharacterData.erase(mCharacterData.find_last_not_of(L" \t\n\f\r") + 1, (size_type)-1);
    mFieldDict.insert(MakeStrPair(string16_s0061_4f20(tag), mCharacterData));
}

// @ 0x00615330
void SP::Pollen::cServerResponse_s0061_4f20::EndElementHandler(SP::Pollen::cServerResponse_s0061_4f20* self, const wchar_t* name)
{
    HandlerRange_s0061_4f20 r = gEndHandlers.equal_range(name);
    if (r.first == r.second || r.first == gEndHandlers.mpEnd) {
        self->DefaultEndTag(name);
        return;
    }
    typedef void (__thiscall *Fn)(void*);
    ((Fn)r.first->second.fn)((char*)self + r.first->second.adj);
}

// @ 0x00615380
SP::Pollen::cServerResponse_s0061_4f20::~cServerResponse_s0061_4f20()
{
    if (mbOpen) {
        mParseStatus = XML_Parse((XML_ParserStruct_s0061_4050*)mpXMLParser, 0, 0, 1);
        XML_ParserFree((XML_ParserStruct_s0061_4050*)mpXMLParser);
        mbOpen = false;
    }
}

// @ 0x00615430
unsigned int SP::Pollen::cServerResponse::Read(void * pData, unsigned int nSize)
{
    return (size_type)-1;
}

// @ 0x00615450
bool SP::Pollen::cServerResponse_s0061_4f20::Open()
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
bool SP::Pollen::cServerResponse::SetPosition(long position, EA::IO::PositionType positionType)
{
    if (positionType == 0) {
        if (position == mBitesRead)
            return true;
        if (position == 0 && Close() && Open())
            return true;
    }
    return false;
}

// @ 0x00615520
void SP::Pollen::cServerResponse_s0061_4f20::IDListElement()
{
    mCharacterData.erase(0, mCharacterData.find_first_not_of(L" \t\n\f\r", 0));
    mCharacterData.erase(mCharacterData.find_last_not_of(L" \t\n\f\r") + 1, (size_type)-1);
    mAssetList.push_back(mCharacterData);
}

// @ 0x006155f0
void SP::Pollen::cServerResponse_s0061_4f20::SetupDict()
{
    HandlerPair_s0061_4f20 p;
    gStartHandlers.clear();
    gStartHandlers.reserve(2);
    SetHandler(p, (const wchar_t*)0x013fc0ec, &SP::Pollen::cServerResponse_s0061_4f20::Noop);             // L"AssetIdList"
    gStartHandlers.insert(p);
    SetHandler(p, (const wchar_t*)0x013fc114, &SP::Pollen::cServerResponse_s0061_4f20::StartPollinatorResponse);   // L"PollinatorResponse"
    gStartHandlers.insert(p);
    gEndHandlers.clear();
    gEndHandlers.reserve(4);
    SetHandler(p, (const wchar_t*)0x013fc0e4, &SP::Pollen::cServerResponse_s0061_4f20::IDListElement);    // L"Id"
    gEndHandlers.insert(p);
    SetHandler(p, (const wchar_t*)0x013fc0ec, &SP::Pollen::cServerResponse_s0061_4f20::Noop);             // L"AssetIdList"
    gEndHandlers.insert(p);
    SetHandler(p, (const wchar_t*)0x013fc114, &SP::Pollen::cServerResponse_s0061_4f20::EndPollinatorResponse);   // L"PollinatorResponse"
    gEndHandlers.insert(p);
    SetHandler(p, (const wchar_t*)0x013fc104, &SP::Pollen::cServerResponse_s0061_4f20::GetStatus);        // L"Status"
    gEndHandlers.insert(p);
    gXMLMemorySuite.malloc_fcn = (void* (*)(size_t))0x6abeb0;
    gXMLMemorySuite.realloc_fcn = (void* (*)(void*, size_t))0x900b10;
    gXMLMemorySuite.free_fcn = (void (*)(void*))0xf47410;
    gbDictInit = true;
}

// @ 0x00676370
void* PollenResponsePairsVector::insert(void* pos, const void* value)
{
    (void)pos; (void)value;
    return pos;
}
