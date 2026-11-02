// src/game/SPBake/SPFeedXml.cpp -- migrated from slice(s) s00548d90, s00546f80, s00543590, s00546160, s00547e90, s00545220 by tools/migrate/rewrite.py
// Object file: SPBake/SPFeedXml.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/Feed/AtomDocument.h"
#include "SP/Feed/AtomEntry.h"
#include "SP/Feed/AtomParser.h"
#include "SP/Feed/FeedDescription.h"
#include "SP/Feed/HandshakeData.h"
#include "SP/Feed/HandshakeParser.h"
#include "SP/Feed/Person.h"
#include "EA/Variant.h"
#include <string.h>
#include <wchar.h>

// unnamed retail callees and globals (address in the comment)
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
extern wchar_t gEmptyString16[];
extern "C" __declspec(dllimport) long wcstol(const wchar_t* s, wchar_t** end, int base);
#pragma intrinsic(wcscmp)

// ---- items of slice s00545220 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) unsigned long wcstoul(const wchar_t* s, wchar_t** end, int base);
typedef unsigned int size_type;
typedef int off_type;
struct XML_ParserStruct_s0054_5220;
typedef XML_ParserStruct_s0054_5220* XML_Parser;
void* operator new(unsigned int size);
inline void* operator new(unsigned int, void* p) { return p; }
inline size_type CharStrlen(const wchar_t* s) {
    const wchar_t* p = s;
    while (*p) ++p;
    return (size_type)(p - s);
}
namespace eastl {
class allocator_s0054_5220 { public:
    allocator_s0054_5220() {}
    void deallocate(void* p, size_type) { delete[] (char*)p; }
};
}
namespace eastl {
template <typename T, typename A = allocator_s0054_5220>
struct basic_string_s0054_5220 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;

    basic_string_s0054_5220(const A& allocator_s0054_5220 = A()) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator_s0054_5220) {
        mpBegin = (T*)gEmptyString16;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    ~basic_string_s0054_5220() { DeallocateSelf(); }
    // 0x004237d0 (wchar_t): inline, but /Ob1 leaves it out of line; its inlined helpers'
    // locals still reserve frame slots in callers that try to inline it.
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, mpCapacity - mpBegin);
    }
    void DoFree(T* p, size_type n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    void clear() {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
    basic_string_s0054_5220& assign(const T* pBegin, const T* pEnd);   // 0x00423650
    basic_string_s0054_5220& operator=(const T* p) { return assign(p, p + CharStrlen(p)); }
    basic_string_s0054_5220& operator=(const basic_string_s0054_5220& x) {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    const T* c_str() const { return mpBegin; }
    enum { npos = (size_type)-1 };
    void resize(size_type n);                                                    // 0x00429520
    basic_string_s0054_5220& erase(size_type position = 0, size_type n = npos);            // 0x004228e0
    size_type find_first_not_of(const T* p, size_type position, size_type n) const;  // 0x00547900
    size_type find_first_not_of(const T* p, size_type position = 0) const {
        return find_first_not_of(p, position, CharStrlen(p));
    }
    size_type find_last_not_of(const T* p, size_type position, size_type n) const;   // 0x00547970
    size_type find_last_not_of(const T* p, size_type position = npos) const {
        return find_last_not_of(p, position, CharStrlen(p));
    }
    basic_string_s0054_5220& sprintf(const T* pFormat, ...);           // 0x00472fe0 (char)
};
}
typedef eastl::basic_string_s0054_5220<wchar_t> string16;
typedef eastl::basic_string_s0054_5220<char> string8;
namespace EA {
template <typename T> class RefCountVTemplate_s0054_5220 {
public:
    RefCountVTemplate_s0054_5220() : mRefCount(0) {}
    virtual ~RefCountVTemplate_s0054_5220() {}
    virtual int AddRef();
    virtual int Release();
    T mRefCount;
};
}
namespace EA {
namespace IO {
enum PositionType_s0054_5220 { kPositionTypeBegin_s0054_5220, kPositionTypeCurrent_s0054_5220, kPositionTypeEnd_s0054_5220 };
}
}
namespace EA {
namespace IO {
class IStream_s0054_5220 {
public:
    virtual ~IStream_s0054_5220() {}
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual unsigned int GetType() const = 0;
    virtual int GetAccessFlags() const = 0;
    virtual int GetState() const = 0;
    virtual bool Close() = 0;
    virtual size_type GetSize() const = 0;
    virtual bool SetSize(size_type size) = 0;
    virtual off_type GetPosition(PositionType_s0054_5220 positionType = kPositionTypeBegin_s0054_5220) const = 0;
    virtual bool SetPosition(off_type position, PositionType_s0054_5220 positionType = kPositionTypeBegin_s0054_5220) = 0;
    virtual size_type GetAvailable() const = 0;
    virtual size_type Read(void* pData, size_type nSize) = 0;
    virtual bool Flush() = 0;
    virtual bool Write(const void* pData, size_type nSize) = 0;
};
}
}
extern "C" void XML_StopParser(XML_Parser p, unsigned char resumable);
namespace EA {
namespace StdC {
unsigned __int64 StrtoU64(const wchar_t* s, wchar_t** end, int base);   // 0x0092d710
}
}
unsigned int FNVHash(const char* s, unsigned int seed, int lowercase);   // 0x00932e80
namespace SP {
namespace Feed {
enum FeedType { kFeedTypeUser_s0054_5220 = 2 };
}
}
namespace SP {
namespace Feed {
FeedType GetFeedTypeFromURI(const char* uri);                             // 0x005419c0
}
}
namespace SP {
namespace Feed {
void ParseDateTime(const string16& s, __int64* pTime);                   // 0x00541680
}
}
namespace SP {
namespace Feed {
struct HandshakeData_s0054_5220 {
    string16 mScreenName;           // +0x00
    unsigned __int64 mnNextID;      // +0x10
    unsigned __int64 mnUserID;      // +0x18
    int mnField20;                  // +0x20
};
}
}
namespace SP {
namespace Feed {
struct FeedDescription_s0054_5220 {            // 0x70 bytes
    FeedDescription_s0054_5220();              // implicit (inline) destructor
    string16 mAuthor;               // +0x00
    unsigned __int64 mnAuthorID;    // +0x10
    string16 mTitle;                // +0x18
    string16 mSubtitle;             // +0x28
    __int64 mUpdated;               // +0x38
    unsigned int mnSubCount;        // +0x40
    string8 mLinkURL;               // +0x44
    string8 mID;                    // +0x54
    unsigned int mnIDHash;          // +0x64
    int mFeedType;                  // +0x68
    unsigned int pad6C;
};
}
}
namespace SP {
namespace Feed {
struct FeedList {                   // eastl::vector<FeedDescription, sp_vector_allocator>
    FeedDescription_s0054_5220* mpBegin;
    FeedDescription_s0054_5220* mpEnd;
    FeedDescription_s0054_5220* mpCapacity;
    unsigned int mAllocator;
    FeedDescription_s0054_5220& push_back() {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) FeedDescription_s0054_5220();
        else
            DoInsertValue(mpEnd, FeedDescription_s0054_5220());
        return *(mpEnd - 1);
    }
    void DoInsertValue(FeedDescription_s0054_5220* position, const FeedDescription_s0054_5220& value);
    FeedDescription_s0054_5220& back() { return *(mpEnd - 1); }
    FeedDescription_s0054_5220* erase(FeedDescription_s0054_5220* first, FeedDescription_s0054_5220* last);   // 0x00548a30
    void clear() { erase(mpBegin, mpEnd); }
};
}
}
namespace SP {
namespace Feed {
extern const wchar_t* kRelAttr;     // L"rel"
}
}
namespace SP {
namespace Feed {
extern const wchar_t* kTypeAttr;    // L"type"
}
}
namespace SP {
namespace Feed {
extern const wchar_t* kHrefAttr;    // L"href"
}
}
namespace SP {
namespace Feed {
class HandshakeParser_s0054_5220 : public EA::RefCountVTemplate_s0054_5220<int>, public EA::IO::IStream_s0054_5220 {
public:
    HandshakeParser_s0054_5220();
    virtual ~HandshakeParser_s0054_5220();
    virtual int AddRef();
    virtual int Release();
    virtual unsigned int GetType() const;
    virtual int GetAccessFlags() const;
    virtual int GetState() const;
    virtual bool Close();
    virtual size_type GetSize() const;
    virtual bool SetSize(size_type size);
    virtual off_type GetPosition(EA::IO::PositionType_s0054_5220 positionType) const;
    virtual bool SetPosition(off_type position, EA::IO::PositionType_s0054_5220 positionType);
    virtual size_type GetAvailable() const;
    virtual size_type Read(void* pData, size_type nSize);
    virtual bool Flush();
    virtual bool Write(const void* pData, size_type nSize);

    bool SetLists(FeedList* pMyFeeds, FeedList* pSubscriptions, FeedList* pList28, HandshakeData_s0054_5220* pData);
    bool ResetParser();
    bool Open();
    void StartDoc();
    void EndDoc();
    void StartFeed();
    void EndFeed();
    void StartAuthor();
    void EndAuthor();
    void EndName();
    void EndAuthorID();
    void BeginList(FeedList* pList, unsigned int listID);
    void EndList();
    void EndTitle();
    void EndSubtitle();
    void EndSubcount();
    void StartLink(const wchar_t** attrs);
    void EndId();
    void EndUpdated();
    void EndNextID();
    void EndUserID();
    void EndField20();
    void EndScreenName();

    static void StartElementHandler(void* ud, const wchar_t* name, const wchar_t** attrs);  // 0x00546160
    static void EndElementHandler(void* ud, const wchar_t* name);             // 0x005462f0
    static void CharacterDataHandler(void* ud, const wchar_t* s, int len);    // 0x00546600

    XML_Parser mpXMLParser;             // +0x0c
    string16 mCharacterData;            // +0x10
    FeedList* mpMyFeeds;                // +0x20
    FeedList* mpSubscriptions;          // +0x24
    FeedList* mpList28;                 // +0x28
    HandshakeData_s0054_5220* mpHandshakeData;     // +0x2c
    bool mbInDoc;                       // +0x30
    FeedList* mpCurList;                // +0x34
    FeedDescription_s0054_5220* mpCurFeed;         // +0x38
    unsigned int mCurListID;            // +0x3c
    bool mbInAuthor;                    // +0x40
    bool mbOpen;                        // +0x41
    int mParseStatus;                   // +0x44
    long mBitesRead;                    // +0x48
};
}
}
// ---- items of slice s00545220 end

// ---- items of slice s00547e90 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  operator_delete__(void*); // 0x00f47380
void* FUN_0042dee0(void* alloc, int size, int align, int flags); // @ 0x42dee0
void* FUN_0054a2d0(int a, int b, int c, char d);   // @ 0x54a2d0 lower_bound
int   FUN_0054a3c0(int a, int b, int c);           // @ 0x54a3c0 relocate
int   FUN_00549500(int a);                         // @ 0x549500 ctor 0x70
void  FUN_005496a0(int a);                         // @ 0x5496a0 move 0x70
struct FeedElemMove {
    void MoveFrom(void* src);      // 0x005496a0 (thiscall, ret 4)
};
struct FeedElemDtor {
    void Destroy();                // 0x00547840 (thiscall, ret 0)
};
static int Cmp16(const unsigned short* a, const unsigned short* b)
{
    for (;;) {
        if (*b != *a) return *b < *a ? -1 : 1;
        if (*b == 0) return 0;
        a++; b++;
    }
}
struct Obj43 {
    char mPad[0x200];

    void  FUN_00547e90(int* pos, int* value);
    void  FUN_00548180();
    void  FUN_005481d0(int* pos, int* value);
    void  FUN_00548400();
    void  FUN_00548450(int pos, int value);
    void* FUN_00548690(int* param_2, int* param_3);
    void* FUN_00548740(int* param_2, int* param_3);
    int   FUN_00548860(int param_2, int* param_3);
    void* FUN_00548910(int* param_2, int* param_3);
    int   FUN_00548a30(int param_2, int param_3);
    void  FUN_00548b10(int param_2, int param_3);
};
// ---- items of slice s00547e90 end

// ---- items of slice s00546160 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char  gEmptyString[];        // @ 0x1667bac
extern short gFeedEndTable[];       // @ 0x13f3ae0
unsigned int FNV1_String16(const wchar_t* s, unsigned int hash, int b); // 0x00932f30
short* FUN_00547900(const void* table, int a, int b);
short* FUN_00547970(const void* table, int a, int b);
void   FUN_004228e0(int a, unsigned int b);
int    FUN_00685520(int a);
void   StringResizeW(int n);
void FUN_00545ad0(...);
void FUN_00545aa0(...);
void FUN_005459a0(...);
void FUN_00545ca0(...);
void FUN_00545bd0(...);
void FUN_00545dc0(...);
void FUN_00545b20(...);
void FUN_00545bf0(...);
void FUN_00545cc0(...);
void FUN_00545ce0(...);
void FUN_00545d30(...);
void FUN_00545d80(...);
void FUN_00545c10(...);
void FUN_00545c60(...);
void FUN_00545fa0(...);
void FUN_00546020(...);
void FUN_00546050(...);
void FUN_00546090(...);
void FUN_005460d0(...);
void FUN_00546110(...);
struct Obj42 {
    char mPad[0x200];
    int* FUN_00546630();                       // ctor
    void FUN_00546800();                       // push_back 0x34
    int  FUN_00546880(int pos);                // erase one 0x34
    unsigned int* FUN_00546930(unsigned int* key); // vector_map operator[]
    void FUN_00546a60(void* value);            // push_back 0x10
    void FUN_00546b70();                       // push_back 0x118
    int* FUN_00546c20();                       // ctor of 0x118 entry
    void InsertLink(int* pos, void* value);    // 0x00547a10 (thiscall)
    int* InsertMap(int* pos, void* value);     // 0x00547d80 (thiscall)
    void Insert16(int* pos, void* value);      // 0x00547e90 (thiscall)
    void Insert118(int* pos, void* value);     // 0x00548450 (thiscall)
};
// ---- items of slice s00546160 end

// ---- items of slice s00543590 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const wchar_t* gAttrRel;        // 0x013f396c  L"rel"
extern const wchar_t* gAttrTerm;       // 0x013f3970  L"term"
void* __cdecl String8_CtorSprintf(void* self, int tag, const char* fmt, ...); // 0x00472f50
void  __cdecl EA_Free(void* p);                                              // 0x00f47380
struct Alloc {                       // empty allocator: passed by reference (1-byte temp)
    char mDummy;
    Alloc() {}
};
struct String8 {                     // eastl::basic_string<char>: 0x10 bytes
    char* mpBegin;                   // +0x00
    char* mpEnd;                     // +0x04
    char* mpCapacity;                // +0x08
    char* mpAllocator;               // +0x0c
    void assign(const char* pBegin, const char* pEnd);   // 0x00454cb0
};
struct String16 {                    // eastl::basic_string<wchar_t>: 0x0c bytes
    wchar_t* mpBegin;                // +0x00
    wchar_t* mpEnd;                  // +0x04
    wchar_t* mpCapacity;             // +0x08
    String16(const wchar_t* p, const Alloc& a = Alloc());  // 0x0041df50 (by value: sret)
    void FreeBuffer();                                     // 0x004237d0
    ~String16() { FreeBuffer(); }
};
struct LinkNode {                    // eastl::pair<const wchar_t*, unsigned int>
    const wchar_t* mpKey;            // +0x00
    unsigned int   mnValue;          // +0x04
};
struct LinkRange {                   // iterator pair returned by find()
    LinkNode* first;                 // +0x00
    LinkNode* second;                // +0x04
};
struct LinkMap {                     // vector_map<const wchar_t*, unsigned int, char16less>
    LinkNode* mpBegin;               // +0x00
    LinkNode* mpEnd;                 // +0x04
    LinkNode* mpCapacity;            // +0x08
    void find(LinkRange& out, const wchar_t* const& key);  // 0x00548910
};
extern LinkMap gLinkMap;             // 0x015e2f54
struct LinkStringMap {               // vector_map<unsigned int, String8, less<unsigned int>>
    String8* mpBegin;                // +0x00
    String8* mpEnd;                  // +0x04
    String8* mpCapacity;             // +0x08
    String8* op_index(const void* key);                    // 0x00546930
};
struct TagList {                     // vector<String16>
    String16* mpBegin;               // +0x00
    String16* mpEnd;                 // +0x04
    String16* mpCapacity;            // +0x08
    void push_back(const String16& v);                     // 0x00546a60
};
struct UintList {                    // vector<unsigned long>
    unsigned long* mpBegin;          // +0x00
    unsigned long* mpEnd;            // +0x04
    unsigned long* mpCapacity;       // +0x08
    void push_back(const unsigned long& v);                // 0x00546b00
};
struct AtomEntry40 {
    char mPad00[0x8c];
    LinkStringMap mLinkMap;          // +0x8c
    char mPad98[0x10];
    String8 mThumbLink;              // +0xa8
    String8 mAssetLink;              // +0xb8
    unsigned int mnAssetType;        // +0xc8
    char mPadCC[0x14];
    TagList mTags;                   // +0xe0
    char mPadEC[0x0c];
    UintList mUintList;              // +0xf8
};
struct AtomDocument40 {
    char mPad00[0x50];
    String8 mSelfLink;               // +0x50
};
namespace EA {
template <typename T>
class AutoRefCount_s0054_3590 {
 public:
    T* mpObject;                     // +0x00
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
struct Ctx40 {
    char mPad00[0x20];
    EA::AutoRefCount_s0054_3590<AtomDocument40> mpDocument;  // +0x20
    bool mbInDoc;                                 // +0x24
    char mPad25[3];
    AtomEntry40* mpCurEntry;                      // +0x28

    void FUN_00543b90(int* attrs);
    void FUN_00543bb0(int* attrs);
    void FUN_00543bd0(int* attrs);
    void FUN_00543bf0(int* attrs);
    void FUN_00543590(int* attrs);
    void FUN_005439d0(int* attrs);
    void FUN_00543c10(int* attrs, int mode);
};
// ---- items of slice s00543590 end

// ---- items of slice s00546f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<int N> inline void ScratchSlots() { unsigned int s[N]; }
typedef int ptrdiff_t;
void* EASTL_Allocate(void* pAllocator, unsigned int n, unsigned int alignment, unsigned int offset);  // 0x0042dee0
namespace eastl {
class allocator_s0054_6f80 { public:
    allocator_s0054_6f80() {}
    void deallocate(void* p, size_type) { delete[] (char*)p; }
};
}
namespace eastl {
struct container_allocator {
    unsigned int mData[2];
    void deallocate(void* p, size_type) { delete[] (char*)p; }
};
}
namespace eastl {
struct sp_vector_allocator_s0054_6f80 {
    unsigned int mData[2];
    void deallocate(void* p, size_type) {
        if (((unsigned int*)p)[-1])
            delete[] (char*)p;
    }
};
}
namespace eastl {
template <typename T> inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
}
namespace eastl {
template <typename T, typename A = allocator_s0054_6f80>
struct basic_string_s0054_6f80 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;

    enum { npos = (size_type)-1 };
    basic_string_s0054_6f80(const A& allocator_s0054_6f80 = A()) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator_s0054_6f80) {
        mpBegin = (T*)gEmptyString16;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    basic_string_s0054_6f80(const basic_string_s0054_6f80& x);
    ~basic_string_s0054_6f80() { DeallocateSelf(); }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, mpCapacity - mpBegin);
    }
    void DoFree(T* p, size_type n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    basic_string_s0054_6f80& operator=(const basic_string_s0054_6f80& x);

    size_type find_first_not_of(const T* p, size_type position, size_type n) const;
    size_type find_last_not_of(const T* p, size_type position, size_type n) const;
};
}
namespace eastl {
typedef basic_string_s0054_6f80<wchar_t> string16_s0054_6f80;
}
namespace eastl {
typedef basic_string_s0054_6f80<char> string8_s0054_6f80;
}
namespace eastl {
const wchar_t* CharTypeStringFindFirstNotOf(const wchar_t* p1Begin, const wchar_t* p1End,
                                            const wchar_t* p2Begin, const wchar_t* p2End);   // 0x005497e0
}
namespace eastl {
const wchar_t* CharTypeStringRFindFirstNotOf(const wchar_t* p1RBegin, const wchar_t* p1REnd,
                                             const wchar_t* p2Begin, const wchar_t* p2End);  // 0x00549840
}
namespace eastl {
template <typename T1, typename T2> struct pair_s0054_6f80 {
    T1 first;
    T2 second;
    pair_s0054_6f80(const T1& x, const T2& y) : first(x), second(y) {}
};
}
namespace eastl {
template <typename Key, typename Value, typename Compare>
class map_value_compare { public:
    Compare c;
    bool operator()(const Value& a, const Value& b) const { return c(a.first, b.first); }
};
}
namespace eastl {
template <typename T, typename Allocator>
struct VectorBase_s0054_6f80 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    ~VectorBase_s0054_6f80() {
        if (mpBegin)
            mAllocator.deallocate(mpBegin, (mpCapacity - mpBegin) * sizeof(T));
    }
    T* DoAllocate(size_type n) {
        return n ? (T*)EASTL_Allocate(&mAllocator, n * sizeof(T), __alignof(T), 0) : 0;
    }
    void DoFree(T* p, size_type n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    size_type GetNewCapacity(size_type currentCapacity) { return (currentCapacity > 0) ? (2 * currentCapacity) : 1; }
};
}
namespace eastl {
template <typename T> T* uninitialized_copy_ptr(T* first, T* last, T* result);
}
namespace eastl {
template <typename T, typename Allocator = container_allocator>
class vector_s0054_6f80 : public VectorBase_s0054_6f80<T, Allocator> { public:
    typedef VectorBase_s0054_6f80<T, Allocator> base_type;
    using base_type::mpBegin;
    using base_type::mpEnd;
    using base_type::mpCapacity;
    using base_type::mAllocator;

    ~vector_s0054_6f80() { DoDestroyValues(mpBegin, mpEnd); }
    void DoDestroyValues(T* first, T* last) {
        for (; first < last; ++first)
            first->~T();
    }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    size_type capacity() const { return (size_type)(mpCapacity - mpBegin); }
    void reserve(size_type n) {
        if (n > (size_type)(mpCapacity - mpBegin)) {
            T* const pNewData = this->DoAllocate(n);
            eastl::uninitialized_copy_ptr(mpBegin, mpEnd, pNewData);
            ScratchSlots<8>();   // frame of the (declined) inline uninitialized_copy
            this->DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
            const ptrdiff_t nPrevSize = mpEnd - mpBegin;
            mpBegin = pNewData;
            mpEnd = pNewData + nPrevSize;
            mpCapacity = mpBegin + n;
        }
    }
    void push_back() {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T();
        else
            DoInsertValue(mpEnd, T());  // 0x00621fc0 (eastl::vector::DoInsertValue)
    }
    T* insert(T* position, const T& value) {
        const ptrdiff_t n = position - mpBegin;
        if ((mpEnd == mpCapacity) || (position != mpEnd))
            DoInsertValue(position, value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
        else
            ::new (mpEnd++) T(value);
        return mpBegin + n;
    }
    void DoInsertValue(T* position, const T& value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
};
}
namespace eastl {
template <typename Key, typename T, typename Compare>
class vector_map_s0054_6f80 : public vector_s0054_6f80<pair_s0054_6f80<Key, T> > { public:
    typedef vector_s0054_6f80<pair_s0054_6f80<Key, T> > base_type;
    typedef pair_s0054_6f80<Key, T> value_type;
    typedef value_type* iterator;
    typedef map_value_compare<Key, value_type, Compare> value_compare;
    using base_type::mpBegin;
    using base_type::mpEnd;
    value_compare mValueCompare;

    pair_s0054_6f80<iterator, bool> insert(const value_type& value);
    iterator insert(iterator position, const value_type& value);
};
}
namespace eastl {
template <typename ForwardIterator, typename T, typename Compare>
ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare compare);
}
namespace EA {
struct Variant_s0054_6f80 {
    struct Generic { unsigned int mData[4]; };
    union {
        Generic mGeneric;
        int mInt32;
    };
    unsigned short mFlags;          // +0x10
    unsigned short mTypeId;         // +0x12
    enum { kFlagAllocated = 4 };
    Variant_s0054_6f80() : mFlags(0), mTypeId(0) {}
    Variant_s0054_6f80(const Variant_s0054_6f80& x);                                     // 0x00548d90 (via Link)
    ~Variant_s0054_6f80() {
        if (mFlags & kFlagAllocated)
            Destruct(false);  // 0x0093db80 (EA::Variant::Destruct)
    }
    Variant_s0054_6f80& operator=(const Variant_s0054_6f80& x);                          // 0x00542b80
    void Destruct(bool bReconstruct);                              // 0x0093db80
};
}
namespace SP {
namespace Feed {
using eastl::string16_s0054_6f80;
}
}
namespace SP {
namespace Feed {
using eastl::string8_s0054_6f80;
}
}
namespace SP {
namespace Feed {
struct Link {
    string16_s0054_6f80 mName;                 // +0x00
    string16_s0054_6f80 mType;                 // +0x10
    EA::Variant_s0054_6f80 mValue;             // +0x20
};
}
}
namespace SP {
namespace Feed {
struct FeedDescription_s0054_6f80 {            // 0x70 bytes; implicit destructor
    FeedDescription_s0054_6f80();
    string16_s0054_6f80 mAuthor;               // +0x00
    unsigned __int64 mnAuthorID;    // +0x10
    string16_s0054_6f80 mTitle;                // +0x18
    string16_s0054_6f80 mSubtitle;             // +0x28
    __int64 mUpdated;               // +0x38
    unsigned int mnSubCount;        // +0x40
    string8_s0054_6f80 mLinkURL;               // +0x44
    string8_s0054_6f80 mID;                    // +0x54
    unsigned int mnIDHash;          // +0x64
    int mFeedType;                  // +0x68
    unsigned int pad6C;
};
}
}
namespace SP {
namespace Feed {
typedef eastl::pair_s0054_6f80<unsigned int, string8_s0054_6f80> IDString;   // 0x14 bytes
}
}
namespace eastl {
using SP::Feed::Link;
}
namespace eastl {
using SP::Feed::FeedDescription_s0054_6f80;
}
namespace eastl {
using SP::Feed::IDString;
}
namespace eastl {
struct char16less {
    bool operator()(const wchar_t* a, const wchar_t* b) const { return wcscmp(a, b) < 0; }
};
}
namespace eastl {
typedef vector_map_s0054_6f80<const wchar_t*, unsigned int, char16less> NameIDMap;
}
namespace eastl {
template <typename Key, typename T, typename Compare>
typename vector_map_s0054_6f80<Key, T, Compare>::iterator
vector_map_s0054_6f80<Key, T, Compare>::insert(iterator position, const value_type& value) {
    iterator itLB;
    if ((position != this->end()) && mValueCompare(value, *position))
        itLB = lower_bound(this->begin(), position, value.first, mValueCompare);
    else
        itLB = lower_bound(position, this->end(), value.first, mValueCompare);
    if ((itLB == this->end()) || mValueCompare(value, *itLB))
        itLB = base_type::insert(itLB, value);
    ScratchSlots<2>();   // frame of the declined inline base_type::insert
    return itLB;
}
}
namespace eastl {
typedef pair_s0054_6f80<const wchar_t*, unsigned int> NameID;
}
namespace eastl {
struct MemFn12 { unsigned int mData[3]; };   // mem_fun1_t<void, AtomParser, const wchar_t**>
}
namespace eastl {
typedef vector_map_s0054_6f80<const wchar_t*, MemFn12, char16less> NameFnMap;
}
namespace eastl {
template void vector_s0054_6f80<Link, sp_vector_allocator_s0054_6f80>::DoInsertValue(Link*, const Link&);
}
namespace eastl {
template struct pair_s0054_6f80<unsigned int, string8_s0054_6f80>;
}
// ---- items of slice s00546f80 end

// @ 0x00543b90
void Ctx40::FUN_00543b90(int* attrs)
{ FUN_00543c10(attrs, 1); }

// @ 0x00543bb0
void Ctx40::FUN_00543bb0(int* attrs)
{ FUN_00543c10(attrs, 2); }

// @ 0x00543bd0
void Ctx40::FUN_00543bd0(int* attrs)
{ FUN_00543c10(attrs, 3); }

// @ 0x00543bf0
void Ctx40::FUN_00543bf0(int* attrs)
{ FUN_00543c10(attrs, 4); }

// @ 0x00543c10
void Ctx40::FUN_00543c10(int* attrs, int mode)
{
    if (mbInDoc) {
        const wchar_t** p = (const wchar_t**)attrs;
        const wchar_t* pRel = 0;
        const wchar_t* pTerm = 0;
        while (*p != 0) {
            const wchar_t* key = *p++;
            const wchar_t* val = *p++;
            if (wcscmp(key, gAttrRel) == 0) {
                pRel = val;
                continue;
            }
            if (wcscmp(key, gAttrTerm) == 0)
                pTerm = val;
        }
        if (mpCurEntry != 0 && pRel != 0 && pTerm != 0) {
            LinkRange res;
            gLinkMap.find(res, pRel);
            LinkNode* it = (res.first != res.second) ? res.first : gLinkMap.mpEnd;
            if (it != gLinkMap.mpEnd) {
                unsigned int type = it->mnValue;
                if (type == 0x2f7d0004) {
                    unsigned char tag = 0;
                    String8 local;
                    String8* src = (String8*)String8_CtorSprintf(&local, tag, "%ls", pTerm);
                    String8* dst = mpCurEntry->mLinkMap.op_index(&mode);
                    if (src != dst)
                        dst->assign(src->mpBegin, src->mpEnd);
                    if ((local.mpCapacity - local.mpBegin) > 1 && local.mpBegin)
                        EA_Free(local.mpBegin);
                }
            }
        }
    }
}

// @ 0x005459a0
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::StartDoc()
{
    if (mpMyFeeds && mpSubscriptions && mpList28) {
        mpMyFeeds->clear();
        mpSubscriptions->clear();
        mpList28->clear();
        mpCurList = 0;
        mpCurFeed = 0;
        mCurListID = 0;
        mbInDoc = true;
    } else
        XML_StopParser(mpXMLParser, false);
}
}}  // namespace SP::Feed

// @ 0x00545aa0
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::EndDoc()
{
    mpCurList = 0;
    mpCurFeed = 0;
    mbInDoc = false;
}
}}  // namespace SP::Feed

// @ 0x00545ad0
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::StartFeed()
{
    if (mpCurList) {
        mpCurList->push_back();
        mpCurFeed = &mpCurList->back();
    }
}
}}  // namespace SP::Feed

// @ 0x00545b20
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::EndFeed()
{
    if (mpCurFeed) {
        mpCurFeed->mFeedType = GetFeedTypeFromURI(mpCurFeed->mID.c_str());
        if (mpCurFeed->mFeedType == kFeedTypeUser_s0054_5220 && mpCurFeed->mnAuthorID == mpHandshakeData->mnUserID)
            mpCurFeed->mFeedType = 7;
        if (mCurListID == 0x725b8629)
            mpCurFeed->mFeedType = 11;
        mpCurFeed = 0;
    }
}
}}  // namespace SP::Feed

// @ 0x00545bd0
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::StartAuthor()
{
    mbInAuthor = true;
}
}}  // namespace SP::Feed

// @ 0x00545bf0
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::EndAuthor()
{
    mbInAuthor = false;
}
}}  // namespace SP::Feed

// @ 0x00545c10
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::EndName()
{
    if (mpCurFeed)
        mpCurFeed->mAuthor = mCharacterData;
}
}}  // namespace SP::Feed

// @ 0x00545c60
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::EndAuthorID()
{
    if (mpCurFeed)
        mpCurFeed->mnAuthorID = EA::StdC::StrtoU64(mCharacterData.c_str(), 0, 10);
}
}}  // namespace SP::Feed

// @ 0x00545ca0
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::BeginList(FeedList* pList, unsigned int listID)
{
    mpCurList = pList;
    mCurListID = listID;
}
}}  // namespace SP::Feed

// @ 0x00545cc0
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::EndList()
{
    mpCurList = 0;
    mCurListID = 0;
}
}}  // namespace SP::Feed

// @ 0x00545ce0
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::EndTitle()
{
    if (mpCurFeed)
        mpCurFeed->mTitle = mCharacterData;
}
}}  // namespace SP::Feed

// @ 0x00545d30
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::EndSubtitle()
{
    if (mpCurFeed)
        mpCurFeed->mSubtitle = mCharacterData;
}
}}  // namespace SP::Feed

// @ 0x00545d80
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::EndSubcount()
{
    if (mpCurFeed)
        mpCurFeed->mnSubCount = wcstoul(mCharacterData.c_str(), 0, 10);
}
}}  // namespace SP::Feed

// @ 0x00545dc0
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::StartLink(const wchar_t** attrs)
{
    if (mpCurFeed) {
        const wchar_t** attr = attrs;
        const wchar_t* pLinkRel = 0;
        const wchar_t* pHref = 0;
        const wchar_t* pLinkType = 0;
        while (*attr) {
            const wchar_t* name = *attr++;
            const wchar_t* value = *attr++;
            if (wcscmp(name, kRelAttr) == 0)
                pLinkRel = value;
            else if (wcscmp(name, kTypeAttr) == 0)
                pLinkType = value;
            else if (wcscmp(name, kHrefAttr) == 0)
                pHref = value;
        }
        if (pHref)
            mpCurFeed->mLinkURL.sprintf("%ls", pHref);
    }
}
}}  // namespace SP::Feed

// @ 0x00545fa0
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::EndId()
{
    if (mpCurFeed) {
        mpCurFeed->mID.sprintf("%ls", mCharacterData);
        mpCurFeed->mnIDHash = FNVHash(mpCurFeed->mID.c_str(), 0x811c9dc5, 1);
    }
}
}}  // namespace SP::Feed

// @ 0x00546020
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::EndUpdated()
{
    if (mpCurFeed)
        ParseDateTime(mCharacterData, &mpCurFeed->mUpdated);
}
}}  // namespace SP::Feed

// @ 0x00546050
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::EndNextID()
{
    if (mpHandshakeData)
        mpHandshakeData->mnNextID = EA::StdC::StrtoU64(mCharacterData.c_str(), 0, 10);
}
}}  // namespace SP::Feed

// @ 0x00546090
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::EndUserID()
{
    if (mpHandshakeData)
        mpHandshakeData->mnUserID = EA::StdC::StrtoU64(mCharacterData.c_str(), 0, 10);
}
}}  // namespace SP::Feed

// @ 0x005460d0
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::EndField20()
{
    if (mpHandshakeData)
        mpHandshakeData->mnField20 = wcstol(mCharacterData.c_str(), 0, 10);
}
}}  // namespace SP::Feed

// @ 0x00546110
namespace SP { namespace Feed {
void HandshakeParser_s0054_5220::EndScreenName()
{
    if (mpHandshakeData)
        mpHandshakeData->mScreenName = mCharacterData;
}
}}  // namespace SP::Feed

// @ 0x00546160
void FUN_00546160(int param_1, const wchar_t* name, int* attrs)
{
    StringResizeW(0);
    unsigned int u = FNV1_String16(name, 0x811c9dc5, 0);
    if (u < 0x8231a2b4) {
        if (u == 0x8231a2b3) { FUN_00545ad0(); return; }
        if (0x5cca0010 < u) {
            if (u == 0x603ddcb1) { FUN_00545ca0(*(int*)(param_1 + 0x24), 0x603ddcb1); return; }
            if (u != 0x725b8629) return;
            if ((char)FUN_00685520(2) == 0) return;
            FUN_00545ca0(*(int*)(param_1 + 0x24), 0x725b8629);
            return;
        }
        if (u == 0x5cca0010) { FUN_005459a0(); return; }
        if (u == 0x820aba1) { FUN_00545dc0(attrs); return; }
        if (u != 0xedb4507) return;
    } else {
        if (u < 0xe1c70ecf) {
            if (u == 0xe1c70ece) { FUN_00545dc0(attrs); return; }
            if (u != 0xc3753dfe) {
                if (u != 0xca02b5a2) return;
                FUN_00545ca0(*(int*)(param_1 + 0x28), 0xca02b5a2);
                return;
            }
            FUN_00545ad0();
            return;
        }
        if (u != 0xecce3150) {
            if (u != 0xffb4ae9f) return;
            FUN_00545ca0(*(int*)(param_1 + 0x20), 0xffb4ae9f);
            return;
        }
    }
    FUN_00545bd0();
}

// @ 0x005462f0
void FUN_005462f0(int param_1, const wchar_t* name)
{
    short* local_14 = gFeedEndTable;
    while (*local_14 != 0) local_14 = local_14 + 1;
    unsigned int uVar1 = (unsigned int)FUN_00547900(gFeedEndTable, 0, (int)(local_14 - gFeedEndTable));
    FUN_004228e0(0, uVar1);
    short* local_20 = gFeedEndTable;
    while (*local_20 != 0) local_20 = local_20 + 1;
    uVar1 = 0xffffffff;
    int iVar2 = (int)FUN_00547970(gFeedEndTable, -1, (int)(local_20 - gFeedEndTable));
    FUN_004228e0(iVar2 + 1, uVar1);

    unsigned int u = FNV1_String16(name, 0x811c9dc5, 0);
    if (0x714baa66 < u) {
        if (u < 0xce191a63) {
            if (u != 0xce191a62) {
                if (u < 0x97bbab5d) {
                    if (u == 0x97bbab5c) { FUN_00545c60(); return; }
                    if (u == 0x725b8629) { FUN_00545cc0(); return; }
                    if (u != 0x8231a2b3) {
                        if (u != 0x845b3524) return;
                        FUN_00546050(); return;
                    }
                } else if (u != 0xc3753dfe) {
                    if (u != 0xcb74142a) return;
                    FUN_00546020(); return;
                }
                FUN_00545b20(); return;
            }
        } else {
            if (0xe647c99b < u) {
                if (u == 0xecce3150) { FUN_00545bf0(); return; }
                if (u != 0xffb4ae9f) return;
                FUN_00545cc0(); return;
            }
            if (u == 0xe647c99b) { FUN_00546110(); return; }
            if (u != 0xd6360d71) {
                if (u != 0xdce0e62d) return;
                FUN_00545ce0(); return;
            }
        }
        FUN_00545d30(); return;
    }
    if (u == 0x714baa66) { FUN_00545d80(); return; }
    if (u < 0x2f8b3bf5) {
        if (u != 0x2f8b3bf4) {
            if (0x13f23f45 < u) {
                if (u != 0x1966dc85) { if (u != 0x1ea2edbc) return; FUN_00545ce0(); return; }
                FUN_00545fa0(); return;
            }
            if (u == 0x13f23f45) { FUN_00545d80(); return; }
            if (u == 0x214b72f) { FUN_00546020(); return; }
            if (u != 0x7319b23) { if (u != 0xedb4507) return; FUN_00545bf0(); return; }
        }
        FUN_00545c10();
    } else {
        if (u < 0x5cca0011) {
            if (u == 0x5cca0010) { FUN_00545aa0(); return; }
            if (u != 0x3b6a85ad) {
                if (u == 0x4cc1948a) { FUN_00546090(); return; }
                if (u != 0x5be92a85) return;
                FUN_005460d0(); return;
            }
            FUN_00545c60(); return;
        }
        if (u == 0x603ddcb1) { FUN_00545cc0(); return; }
        if (u != 0x687720a6) return;
        FUN_00545fa0();
    }
}

// @ 0x00546630
int* Obj42::FUN_00546630()
{
    int* p = (int*)this;
    p[0] = 0; p[1] = 0; p[2] = 0;
    p[0] = (int)gEmptyString; p[1] = p[0]; p[2] = p[0] + 2;
    p[4] = -1; p[5] = -1;
    int* q = p + 6;
    q[0] = 0; p[7] = 0; p[8] = 0;
    q[0] = (int)gEmptyString; p[7] = q[0]; p[8] = q[0] + 2;
    q = p + 10;
    q[0] = 0; p[0xb] = 0; p[0xc] = 0;
    q[0] = (int)gEmptyString; p[0xb] = q[0]; p[0xc] = q[0] + 2;
    p[0xe] = 0; p[0xf] = 0; p[0x10] = -1;
    q = p + 0x11;
    q[0] = 0; p[0x12] = 0; p[0x13] = 0;
    q[0] = (int)gEmptyString; p[0x12] = q[0]; p[0x13] = q[0] + 1;
    q = p + 0x15;
    q[0] = 0; p[0x16] = 0; p[0x17] = 0;
    q[0] = (int)gEmptyString; p[0x16] = q[0]; p[0x17] = q[0] + 1;
    p[0x19] = 0; p[0x1a] = 0;
    return p;
}

// @ 0x00547640
namespace eastl {
template void vector_s0054_6f80<FeedDescription_s0054_6f80, sp_vector_allocator_s0054_6f80>::push_back()
;
}  // namespace eastl

// @ 0x00547900
namespace eastl {
template <> size_type basic_string_s0054_6f80<wchar_t, allocator_s0054_6f80>::find_first_not_of(const wchar_t* p, size_type position, size_type n) const
{
    if (position <= (size_type)(mpEnd - mpBegin)) {
        const wchar_t* const pResult = CharTypeStringFindFirstNotOf(mpBegin + position, mpEnd, p, p + n);
        if (pResult != mpEnd)
            return (size_type)(pResult - mpBegin);
    }
    return npos;
}
}  // namespace eastl

// @ 0x00547970
namespace eastl {
template <> size_type basic_string_s0054_6f80<wchar_t, allocator_s0054_6f80>::find_last_not_of(const wchar_t* p, size_type position, size_type n) const
{
    const size_type nLength = (size_type)(mpEnd - mpBegin);
    if (nLength) {
        const wchar_t* const pEnd = mpBegin + min_alt(nLength - 1, position) + 1;
        const wchar_t* const pResult = CharTypeStringRFindFirstNotOf(pEnd, mpBegin, p, p + n);
        if (pResult != mpBegin)
            return (size_type)((pResult - 1) - mpBegin);
    }
    return npos;
}
}  // namespace eastl

// @ 0x00548910
void* Obj43::FUN_00548910(int* param_2, int* param_3)
{
    int* p = (int*)this;
    int* it = (int*)FUN_0054a2d0(p[0], p[1], (int)param_3, *(char*)(p + 5));
    if (it != (int*)p[1]) {
        int cmp = Cmp16((const unsigned short*)*it, (const unsigned short*)*param_3);
        if (cmp >= 0) {
            param_2[0] = (int)it;
            param_2[1] = (int)(it + 2);
            return param_2;
        }
    }
    param_2[0] = (int)it;
    param_2[1] = (int)it;
    return param_2;
}

// @ 0x00548a30
int Obj43::FUN_00548a30(int param_2, int param_3)
{
    int base = (int)this;
    int end = *(int*)(base + 4);
    int dst = param_2;
    for (int cur = param_3; cur != end; cur = cur + 0x70) {
        ((FeedElemMove*)dst)->MoveFrom((void*)cur);
        dst = dst + 0x70;
    }
    int stop = *(int*)(base + 4);
    for (unsigned cur = (unsigned)dst; cur < (unsigned)stop; cur = cur + 0x70)
        ((FeedElemDtor*)cur)->Destroy();
    *(int*)(base + 4) = *(int*)(base + 4) + ((param_3 - param_2) / 0x70) * -0x70;
    return param_2;
}

// @ 0x00548b10
void Obj43::FUN_00548b10(int param_2, int param_3)
{
    int* v = (int*)this;
    if (v[1] == v[2]) {
        int old = (v[1] - *v) / 0x70;
        int cap = old == 0 ? 1 : old << 1;
        int newBuf = cap == 0 ? 0 : (int)FUN_0042dee0((char*)v + 0xc, cap * 0x70, 8, 0);
        int iVar1 = FUN_0054a3c0(*v, param_2, newBuf);
        int uVar2;
        if (iVar1 == 0) uVar2 = 0;
        else uVar2 = (int)FUN_00549500(param_3);
        (void)uVar2;
        int iVar3 = FUN_0054a3c0(param_2, v[1], iVar1 + 0x70);
        iVar1 = *v;
        if (iVar1 != 0 && *(int*)(iVar1 - 4) != 0) operator_delete__((void*)iVar1);
        *v = newBuf;
        v[1] = iVar3;
        v[2] = cap * 0x70 + newBuf;
    } else {
        int src = param_3;
        if ((unsigned int)param_2 <= (unsigned int)param_3
            && (unsigned int)param_3 < (unsigned int)v[1])
            src = param_3 + 0x70;
        if (v[1] != 0) FUN_00549500(v[1] - 0x70);
        int cur = v[1] - 0x70;
        while (cur != param_2) {
            cur = cur - 0x70;
            FUN_005496a0(cur);
        }
        FUN_005496a0(src);
        v[1] = v[1] + 0x70;
    }
}

// @ 0x005497e0
short* FUN_005497e0(short* param_1, short* param_2, short* param_3, short* param_4)
{
    for (;;) {
        if (param_1 == param_2) return param_2;
        short* cur = param_3;
        for (; cur != param_4 && *param_1 != *cur; cur = cur + 1) { }
        if (cur == param_4) return param_1;
        param_1 = param_1 + 1;
    }
}

// @ 0x00549840
int FUN_00549840(int param_1, int param_2, short* param_3, short* param_4)
{
    for (;;) {
        if (param_1 == param_2) return param_2;
        short* cur = param_3;
        for (; cur != param_4 && *(short*)(param_1 - 2) != *cur; cur = cur + 1) { }
        if (cur == param_4) return param_1;
        param_1 = param_1 - 2;
    }
}
