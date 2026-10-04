// Slice s00542980: more SP::Feed::AtomParser element handlers (SPFeedXml.cpp) and the
// EA::Variant assignment helpers they use.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP (no /EHsc).
// Handler names other than EndId/EndTitle/EndSubtitle/EndSubcount/EndName/EndUpdated (dev-build
// PDB) are descriptive guesses based on the attribute/field they handle.

typedef unsigned int size_type;
typedef int off_type;

struct XML_ParserStruct;
typedef XML_ParserStruct* XML_Parser;
struct XML_Memory_Handling_Suite;
struct XML_ParsingStatus { int parsing; unsigned char finalBuffer; };
extern "C" {
XML_Parser XML_ParserCreate_MM(const char* encoding, const XML_Memory_Handling_Suite* ms, const char* sep);
void XML_ParserFree(XML_Parser p);
int XML_Parse(XML_Parser p, const char* s, int len, int isFinal);
void XML_GetParsingStatus(XML_Parser p, XML_ParsingStatus* status);
unsigned char XML_ParserReset(XML_Parser p, const char* encoding);
void XML_SetUserData(XML_Parser p, void* userData);
void XML_SetElementHandler(XML_Parser p, void (*start)(void*, const wchar_t*, const wchar_t**),
                           void (*end)(void*, const wchar_t*));
void XML_SetCharacterDataHandler(XML_Parser p, void (*h)(void*, const wchar_t*, int));
int XML_GetErrorCode(XML_Parser p);
}
extern XML_Memory_Handling_Suite gXMLMemorySuite;

void* operator new(unsigned int size);
inline void* operator new(unsigned int, void* p) { return p; }
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#pragma intrinsic(wcscmp)

extern wchar_t gEmptyString16[];

inline size_type CharStrlen(const wchar_t* s) {
    const wchar_t* p = s;
    while (*p) ++p;
    return (size_type)(p - s);
}
namespace eastl {
struct allocator {
    allocator() {}
    void deallocate(void* p, size_type) { delete[] (char*)p; }
};

template <typename T, typename A = allocator>
struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;

    basic_string(const A& allocator = A()) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator) {
        mpBegin = (T*)gEmptyString16;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    ~basic_string() { DeallocateSelf(); }
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
    basic_string& assign(const T* pBegin, const T* pEnd);   // 0x00423650
    basic_string& operator=(const T* p) { return assign(p, p + CharStrlen(p)); }
    basic_string& operator=(const basic_string& x) {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    const T* c_str() const { return mpBegin; }
    enum { npos = (size_type)-1 };
    void resize(size_type n);                                                    // 0x00429520
    basic_string& erase(size_type position = 0, size_type n = npos);            // 0x004228e0
    size_type find_first_not_of(const T* p, size_type position, size_type n) const;  // 0x00547900
    size_type find_first_not_of(const T* p, size_type position = 0) const {
        return find_first_not_of(p, position, CharStrlen(p));
    }
    size_type find_last_not_of(const T* p, size_type position, size_type n) const;   // 0x00547970
    size_type find_last_not_of(const T* p, size_type position = npos) const {
        return find_last_not_of(p, position, CharStrlen(p));
    }
    basic_string& sprintf(const T* pFormat, ...);           // 0x00472fe0 (char)
};
}  // namespace eastl
typedef eastl::basic_string<wchar_t> string16;
typedef eastl::basic_string<char> string8;

namespace EA {
template <typename T> struct RefCountTemplate {
    RefCountTemplate() : mRefCount(0) {}
    virtual ~RefCountTemplate() {}
    T mRefCount;
    int AddRef() { return mRefCount++ + 1; }
    // 0x00453540: declared inline but too big for /Ob1, so it stays out of line (its
    // locals still reserve frame slots in every caller that tries to inline it).
    int Release() {
        int count = mRefCount - 1;
        mRefCount = mRefCount - 1;
        if (count)
            return count;
        mRefCount = 1;
        delete this;
        return 0;
    }
};

template <typename T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
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
    // 0x004e4350: stays out of line (the nested inline operator= is expanded inside it), but
    // callers still reserve frame slots for it.
    AutoRefCount& operator=(const AutoRefCount& x) { return operator=(x.mpObject); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

template <typename T> class RefCountVTemplate {
public:
    RefCountVTemplate() : mRefCount(0) {}
    virtual ~RefCountVTemplate() {}
    virtual int AddRef();
    virtual int Release();
    T mRefCount;
};

namespace IO {
enum PositionType { kPositionTypeBegin, kPositionTypeCurrent, kPositionTypeEnd };
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
    virtual off_type GetPosition(PositionType positionType = kPositionTypeBegin) const = 0;
    virtual bool SetPosition(off_type position, PositionType positionType = kPositionTypeBegin) = 0;
    virtual size_type GetAvailable() const = 0;
    virtual size_type Read(void* pData, size_type nSize) = 0;
    virtual bool Flush() = 0;
    virtual bool Write(const void* pData, size_type nSize) = 0;
};
}  // namespace IO
}  // namespace EA


namespace EA {
// EA::Variant (EAVariant.cpp): 16 bytes of storage, then flags and a type id.
struct Variant {
    struct Generic { unsigned int mData[4]; };
    struct Pointer { const void* mpData; unsigned int mnSize; unsigned int mnCount; };
    enum { kFlagUnsized = 2, kFlagAllocated = 4, kFlagNoCopy = 8, kFlagPointer = 0x30 };
    union {
        Generic mGeneric;
        Pointer mPointer;
        int mInt32;
        float mFloat;
    };
    unsigned short mFlags;          // +0x10
    unsigned short mTypeId;         // +0x12

    Variant() : mFlags(0), mTypeId(0) {}
    ~Variant() {
        if (mFlags & kFlagAllocated)
            Destruct(false);
    }
    Variant& operator=(const Variant& x);
    template <typename T> Variant& operator=(const T& x);        // 0x00422eb0 <int>, 0x00428060 <float>
    void Destruct(bool bReconstruct);                              // 0x0093db80
    void Construct(const Variant& x, unsigned short flags);
    void Construct(unsigned short typeId, unsigned short flags, const void* pData, unsigned int nSize,
                   unsigned int nCount);                           // 0x0093dd80
};
}  // namespace EA

namespace SP {
namespace Feed {

struct Person : EA::RefCountTemplate<int> {
    string16 mName;                 // +0x08
    unsigned __int64 mnID;          // +0x18
};

// A <link>-style name/type/value record (0x34 bytes).
struct Link {
    string16 mName;                 // +0x00
    string16 mType;                 // +0x10
    EA::Variant mValue;             // +0x20
};

template <typename T> struct EntryVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    unsigned int mAllocator;
    // push_back() is inline but too big for /Ob1, so it stays out of line
    // (0x00546b70 / 0x00546800); its value_type temporary still reserves caller frame space.
    T& push_back() {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T();
        else
            DoInsertValue(mpEnd, T());
        return *(mpEnd - 1);
    }
    void DoInsertValue(T* position, const T& value);
    T* erase(T* position);          // 0x00546880 (Link)
    T& back() { return *(mpEnd - 1); }
};

struct AtomEntry {                  // retail: 0x118 bytes
    AtomEntry();
    ~AtomEntry();
    string8 mID;                    // +0x00
    unsigned __int64 mnAssetID;     // +0x10
    string16 mTitle;                // +0x18
    __int64 mUpdated;               // +0x28
    __int64 mPublished;             // +0x30
    __int64 mTime38;                // +0x38
    __int64 mParentAuthorID;        // +0x40
    string16 mParentScreenName;     // +0x48
    __int64 mTime58;                // +0x58
    __int64 mOriginalAuthorID;      // +0x60
    string16 mOriginalScreenName;   // +0x68
    EntryVector<Link> mLinkList;    // +0x78
    unsigned int pad88[7];
    EA::AutoRefCount<Person> mpAuthor;  // +0xa4
    unsigned int padA8[9];
    unsigned int mnFlagsCC;         // +0xcc
    string16 mSummary;              // +0xd0
    unsigned int padE0[12];
    bool mbFlag110;                 // +0x110
};

struct AtomDocument : EA::RefCountTemplate<int> {
    string8 mID;                            // +0x08
    unsigned int mIDHash;                   // +0x18
    string16 mTitle;                        // +0x1c
    string16 mSubtitle;                     // +0x2c
    unsigned int pad3C;
    __int64 mUpdated;                       // +0x40
    unsigned int mnSubcount;                // +0x48
    EA::AutoRefCount<Person> mpAuthor;      // +0x4c
    unsigned int pad50[4];
    EntryVector<AtomEntry> mEntryList;      // +0x60
    unsigned int pad70;
    bool mbFlag74;                          // +0x74
    string16 mText78;                       // +0x78
};

class AtomParser : public EA::RefCountVTemplate<int>, public EA::IO::IStream {
public:
    AtomParser();
    virtual ~AtomParser();
    virtual int AddRef();
    virtual int Release();
    virtual unsigned int GetType() const;
    virtual int GetAccessFlags() const;
    virtual int GetState() const;
    virtual bool Close();
    virtual size_type GetSize() const;
    virtual bool SetSize(size_type size);
    virtual off_type GetPosition(EA::IO::PositionType positionType) const;
    virtual bool SetPosition(off_type position, EA::IO::PositionType positionType);
    virtual size_type GetAvailable() const;
    virtual size_type Read(void* pData, size_type nSize);
    virtual bool Flush();
    virtual bool Write(const void* pData, size_type nSize);

    void EndLink();
    void StartParentAuthor(const wchar_t** attrs);
    void EndTime38();
    void StartOriginalAuthor(const wchar_t** attrs);
    void EndTime58();
    void EndTitle();
    void EndSubtitle();
    void EndSubcount();
    void EndFlagsCC();
    void EndName();
    void EndUserID();
    void EndId();
    void EndSummary();
    void EndUpdated();
    void EndPublished();
    void EndFlag110();
    void EndText78();
    static void SetupDict();                                                  // 0x00543f00
    static void StartElementHandler(void* ud, const wchar_t* name, const wchar_t** attrs);  // 0x00545220
    static void EndElementHandler(void* ud, const wchar_t* name);             // 0x005452b0
    static void CharacterDataHandler(void* ud, const wchar_t* s, int len);    // 0x00546600
    static bool sbDictSetup;

    XML_Parser mpXMLParser;                     // +0x0c
    string16 mCharacterData;                    // +0x10
    EA::AutoRefCount<AtomDocument> mpDocument;  // +0x20
    bool mbInDoc;                               // +0x24
    AtomEntry* mpCurEntry;                      // +0x28
    EA::AutoRefCount<Person> mpCurAuthor;       // +0x2c
    Link* mpCurLink;                            // +0x30
    bool mbOpen;                                // +0x34
    int mParseStatus;                           // +0x38
    long mBitesRead;                            // +0x3c
};

}  // namespace Feed
}  // namespace SP

extern "C" __declspec(dllimport) int swscanf(const wchar_t* s, const wchar_t* fmt, ...);
extern "C" __declspec(dllimport) unsigned long wcstoul(const wchar_t* s, wchar_t** end, int base);
namespace EA { namespace StdC {
unsigned __int64 StrtoU64(const wchar_t* s, wchar_t** end, int base);   // 0x0092d710
} }
unsigned int FNVHash(const char* s, unsigned int seed, int lowercase);   // 0x00932e80

namespace SP {
namespace Feed {
unsigned __int64 ParseSporeAssetIDFromURI(const char* uri);              // 0x005418c0
void ParseDateTime(const string16& s, __int64* pTime);                   // 0x00541680

extern const wchar_t* kScreenNameAttr;          // L"screenname"
extern const wchar_t* kParentAuthorIdAttr;      // L"parentAuthorId"
extern const wchar_t* kOriginalAuthorIdAttr;    // L"originalAuthorId"

// @ 0x00542980
void AtomParser::EndLink() {
    if (mpCurLink) {
        mpCurLink->mValue = EA::Variant();
        if (wcscmp(mpCurLink->mType.c_str(), L"int") == 0) {
            int value;
            if (swscanf(mCharacterData.c_str(), L"%d", &value) == 1)
                mpCurLink->mValue = value;
        } else if (wcscmp(mpCurLink->mType.c_str(), L"float") == 0) {
            float value;
            if (swscanf(mCharacterData.c_str(), L"%f", &value) == 1)
                mpCurLink->mValue = value;
        }
        if (mpCurLink->mValue.mTypeId == 0)
            mpCurEntry->mLinkList.erase(mpCurLink);
        mpCurLink = 0;
    }
}

}  // namespace Feed
}  // namespace SP

namespace EA {
// @ 0x00542b80 sym=??4Variant@EA@@QAEAAU01@ABU01@@Z
Variant& Variant::operator=(const Variant& x) {
    if (mFlags & kFlagAllocated)
        Destruct(true);
    if (!(x.mFlags & kFlagNoCopy) && (!(mFlags & kFlagUnsized) || mTypeId == x.mTypeId)) {
        mGeneric = x.mGeneric;
        mTypeId = x.mTypeId;
        mFlags = (x.mFlags & ~kFlagUnsized) | (mFlags & kFlagUnsized);
    } else
        Construct(x, 0);
    return *this;
}

// @ 0x00542c30
void Variant::Construct(const Variant& x, unsigned short flags) {
    if (x.mFlags & kFlagPointer)
        Construct(x.mTypeId, x.mFlags | flags, x.mPointer.mpData, x.mPointer.mnSize, x.mPointer.mnCount);
    else
        Construct(x.mTypeId, x.mFlags | flags, &x, 0x10, 1);
}
}  // namespace EA

namespace SP {
namespace Feed {

// @ 0x00542cb0
void AtomParser::StartParentAuthor(const wchar_t** attrs) {
    if (mbInDoc) {
        const wchar_t** attr = attrs;
        const wchar_t* screenName = 0;
        __int64 id = -1;
        while (*attr) {
            const wchar_t* name = *attr++;
            const wchar_t* value = *attr++;
            if (wcscmp(name, kScreenNameAttr) == 0)
                screenName = value;
            else if (wcscmp(name, kParentAuthorIdAttr) == 0 && value)
                swscanf(value, L"%I64d", &id);
        }
        if (mpCurEntry) {
            if (screenName)
                mpCurEntry->mParentScreenName = screenName;
            if (id != -1)
                mpCurEntry->mParentAuthorID = id;
        }
    }
}

// @ 0x00542e80  (not in the function list: follows StartParentAuthor)
void AtomParser::EndTime38() {
    if (mpCurEntry) {
        __int64 value = -1;
        if (swscanf(mCharacterData.c_str(), L"%I64d", &value) == 1)
            mpCurEntry->mTime38 = value;
    }
}

// @ 0x00542ee0
void AtomParser::StartOriginalAuthor(const wchar_t** attrs) {
    if (mbInDoc) {
        const wchar_t** attr = attrs;
        const wchar_t* screenName = 0;
        __int64 originalID = -1;
        while (*attr) {
            const wchar_t* name = *attr++;
            const wchar_t* value = *attr++;
            if (wcscmp(name, kScreenNameAttr) == 0)
                screenName = value;
            else if (wcscmp(name, kOriginalAuthorIdAttr) == 0 && value)
                swscanf(value, L"%I64d", &originalID);
        }
        if (mpCurEntry) {
            if (screenName)
                mpCurEntry->mOriginalScreenName = screenName;
            if (originalID != -1)
                mpCurEntry->mOriginalAuthorID = originalID;
        }
    }
}

// @ 0x005430b0  (not in the function list: follows StartOriginalAuthor)
void AtomParser::EndTime58() {
    if (mpCurEntry) {
        __int64 value = -1;
        if (swscanf(mCharacterData.c_str(), L"%I64d", &value) == 1)
            mpCurEntry->mTime58 = value;
    }
}

// @ 0x00543110
void AtomParser::EndTitle() {
    if (mpCurEntry)
        mpCurEntry->mTitle = mCharacterData;
    else
        mpDocument->mTitle = mCharacterData;
}

// @ 0x005431a0
void AtomParser::EndSubtitle() {
    if (mbInDoc)
        mpDocument->mSubtitle = mCharacterData;
}

// @ 0x005431f0  (not in the function list: follows EndSubtitle)
void AtomParser::EndSubcount() {
    if (mbInDoc)
        mpDocument->mnSubcount = wcstoul(mCharacterData.c_str(), 0, 10);
}

// @ 0x00543240
void AtomParser::EndFlagsCC() {
    if (mpCurEntry)
        mpCurEntry->mnFlagsCC = wcstoul(mCharacterData.c_str(), 0, 16);
}

// @ 0x00543280
void AtomParser::EndName() {
    if (mpCurAuthor)
        mpCurAuthor->mName = mCharacterData;
}

// @ 0x005432e0
void AtomParser::EndUserID() {
    if (mpCurAuthor)
        mpCurAuthor->mnID = EA::StdC::StrtoU64(mCharacterData.c_str(), 0, 10);
}

// @ 0x00543330
void AtomParser::EndId() {
    if (mpCurEntry) {
        mpCurEntry->mID.sprintf("%ls", mCharacterData.c_str());
        mpCurEntry->mnAssetID = ParseSporeAssetIDFromURI(mpCurEntry->mID.c_str());
    } else {
        mpDocument->mID.sprintf("%ls", mCharacterData.c_str());
        mpDocument->mIDHash = FNVHash(mpDocument->mID.c_str(), 0x811c9dc5, 1);
    }
}

// @ 0x005433f0  (not in the function list: follows EndId)
void AtomParser::EndSummary() {
    if (mpCurEntry)
        mpCurEntry->mSummary = mCharacterData;
}

// @ 0x00543440
void AtomParser::EndUpdated() {
    if (mpDocument) {
        if (mpCurEntry)
            ParseDateTime(mCharacterData, &mpCurEntry->mUpdated);
        else
            ParseDateTime(mCharacterData, &mpDocument->mUpdated);
    }
}

// @ 0x005434a0
void AtomParser::EndPublished() {
    if (mpDocument && mpCurEntry)
        ParseDateTime(mCharacterData, &mpCurEntry->mPublished);
}

// @ 0x005434e0
void AtomParser::EndFlag110() {
    if (mpDocument && mpCurEntry)
        mpCurEntry->mbFlag110 = true;
}

// @ 0x00543520
void AtomParser::EndText78() {
    if (mpDocument) {
        mpDocument->mbFlag74 = true;
        mpDocument->mText78 = mCharacterData;
    }
}

}  // namespace Feed
}  // namespace SP
