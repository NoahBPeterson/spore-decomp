// Slice s005419c0: SP::Feed (SPFeedXml.cpp) -- GetFeedTypeFromURI and the expat-based
// SP::Feed::AtomParser (EA::IO::IStream sink that builds an AtomDocument).
// Unoptimized module: /Od /Ob1 /MD /Gy /TP (no /EHsc).
// Names come from the 2008 dev-build PDB (SPFeedXml.obj). Retail layouts differ from the dev
// build (AtomParser grew mpCurLink at +0x30, AtomEntry is 0x118 bytes), so unknown parts are pads.

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
        mpBegin = gEmptyString16;
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
};
}  // namespace eastl
typedef eastl::basic_string<wchar_t> string16;

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

namespace SP {
namespace Feed {

struct Person : EA::RefCountTemplate<int> {
    string16 mName;                 // +0x08
    unsigned __int64 mnID;          // +0x18
};

struct Link {                       // 0x34 bytes
    string16 mRel;                  // +0x00
    string16 mHref;                 // +0x10
    unsigned int pad20[5];
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
    T& back() { return *(mpEnd - 1); }
};

struct AtomEntry {                  // retail: 0x118 bytes
    AtomEntry();
    ~AtomEntry();
    unsigned int pad00[10];
    __int64 mUpdated;             // +0x28
    __int64 mPublished;               // +0x30
    unsigned int pad38[16];
    EntryVector<Link> mLinkList;    // +0x78
    unsigned int pad88[7];
    EA::AutoRefCount<Person> mpAuthor;  // +0xa4
    unsigned int padA8[28];
};

struct AtomDocument : EA::RefCountTemplate<int> {
    unsigned int pad08[17];
    EA::AutoRefCount<Person> mpAuthor;      // +0x4c
    unsigned int pad50[4];
    EntryVector<AtomEntry> mEntryList;      // +0x60
    unsigned int pad70[2];
    string16 mTitle;                        // +0x78
};

enum FeedType {
    kFeedTypeUnknown = 0,
    kFeedTypeAggregator = 1,
    kFeedTypeUser = 2,
    kFeedTypeTag = 3,
    kFeedTypeRandomCity = 4,
    kFeedTypeRandomAsset = 5,
    kFeedTypeCreatureMatch = 6,
    kFeedTypeAssembledContent = 9,
    kFeedTypeImportedContent = 10
};

extern const char* kTagURIPrefix;       // "tag:spore.com,2006:"
extern const char* kAggregatorPath;     // "aggregator/"
extern const char* kUserPath;           // "user/"
extern const char* kTagPath;            // "tag/"
extern const char* kRandomCityPath;     // "randomCity/"
extern const char* kRandomAssetPath;    // "randomAsset/"
extern const char* kCreatureMatchPath;  // "creatureMatch/"
extern const char* kImportedContent;    // "ImportedContent"
extern const char* kAssembledContent;   // "AssembledContent"

inline bool MatchPrefix(const char*& p, const char* prefix) {
    for (; *prefix && *p == *prefix; ++prefix, ++p) {}
    return *prefix == 0;
}

// @ 0x005419c0
FeedType GetFeedTypeFromURI(const char* uri) {
    const char* p = uri;
    if (p && MatchPrefix(p, kTagURIPrefix)) {
        const char* q;
        q = p;
        if (MatchPrefix(q, kAggregatorPath)) return kFeedTypeAggregator;
        q = p;
        if (MatchPrefix(q, kUserPath)) return kFeedTypeUser;
        q = p;
        if (MatchPrefix(q, kTagPath)) return kFeedTypeTag;
        q = p;
        if (MatchPrefix(q, kRandomCityPath)) return kFeedTypeRandomCity;
        q = p;
        if (MatchPrefix(q, kRandomAssetPath)) return kFeedTypeRandomAsset;
        q = p;
        if (MatchPrefix(q, kCreatureMatchPath)) return kFeedTypeCreatureMatch;
        q = p;
        if (MatchPrefix(q, kAssembledContent)) return kFeedTypeAssembledContent;
        q = p;
        if (MatchPrefix(q, kImportedContent)) return kFeedTypeImportedContent;
    }
    return kFeedTypeUnknown;
}

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

    bool SetDocument(AtomDocument* pDocument);
    bool ResetParser();
    bool Open();
    void StartDoc(const wchar_t** attrs);
    void EndDoc();
    void StartEntry(const wchar_t** attrs);
    void EndEntry();
    void StartAuthor(const wchar_t** attrs);
    void EndAuthor();
    void StartLink(const wchar_t** attrs);

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

// @ 0x00541d10
AtomParser::AtomParser()
    : mpXMLParser(0), mbInDoc(false), mpCurEntry(0), mbOpen(false), mParseStatus(1), mBitesRead(0) {
    if (!sbDictSetup)
        SetupDict();
}

// @ 0x00541ea0
bool AtomParser::SetSize(size_type) {
    return true;
}

// @ 0x00541eb0
bool AtomParser::SetPosition(off_type position, EA::IO::PositionType positionType) {
    return (positionType == EA::IO::kPositionTypeBegin && position == mBitesRead) ||
           (positionType == EA::IO::kPositionTypeCurrent && position == 0);
}

// @ 0x00541f20
AtomParser::~AtomParser() {
    if (mbOpen)
        Close();
    XML_ParserFree(mpXMLParser);
}

// @ 0x00541fc0
bool AtomParser::SetDocument(AtomDocument* pDocument) {
    mpDocument = pDocument;
    return true;
}

// @ 0x00542030
bool AtomParser::ResetParser() {
    bool result = false;
    if (mpXMLParser) {
        XML_ParsingStatus status;
        XML_GetParsingStatus(mpXMLParser, &status);
        if (status.parsing) {
            XML_ParserReset(mpXMLParser, 0);
            XML_SetUserData(mpXMLParser, this);
            XML_SetElementHandler(mpXMLParser, StartElementHandler, EndElementHandler);
            XML_SetCharacterDataHandler(mpXMLParser, CharacterDataHandler);
        }
        result = true;
    }
    return result;
}

// @ 0x005420c0
bool AtomParser::Open() {
    if (!mbOpen) {
        if (mpDocument) {
            if (!mpXMLParser) {
                mpXMLParser = XML_ParserCreate_MM(0, &gXMLMemorySuite, 0);
                XML_SetUserData(mpXMLParser, this);
                XML_SetElementHandler(mpXMLParser, StartElementHandler, EndElementHandler);
                XML_SetCharacterDataHandler(mpXMLParser, CharacterDataHandler);
            } else
                ResetParser();
            if (mpXMLParser) {
                mbOpen = true;
                mParseStatus = 1;
                mBitesRead = 0;
            }
        }
    }
    return mbOpen;
}

// @ 0x00542190
bool AtomParser::Write(const void* pData, size_type nSize) {
    if (mbOpen && mpDocument) {
        mParseStatus = XML_Parse(mpXMLParser, (const char*)pData, nSize, false);
        mBitesRead += nSize;
        return mParseStatus == 1;
    }
    return false;
}

// @ 0x00542200
bool AtomParser::Close() {
    if (mbOpen && mpDocument) {
        mParseStatus = XML_Parse(mpXMLParser, 0, 0, true);
        mbOpen = false;
        return mParseStatus == 1;
    }
    return mpDocument != 0;
}

// @ 0x00542270
int AtomParser::GetAccessFlags() const {
    if (mbOpen)
        return 2;
    else
        return 0;
}

// @ 0x005422a0
int AtomParser::GetState() const {
    if (mbOpen) {
        if (mParseStatus != 1)
            return XML_GetErrorCode(mpXMLParser);
        else
            return 0;
    } else
        return -2;
}

// @ 0x005422e0
off_type AtomParser::GetPosition(EA::IO::PositionType positionType) const {
    switch (positionType) {
    case EA::IO::kPositionTypeBegin:
        return mBitesRead;
        break;
    case EA::IO::kPositionTypeCurrent:
        return 0;
        break;
    case EA::IO::kPositionTypeEnd:
        return -1;
        break;
    }
    return -1;
}

// @ 0x00542330
void AtomParser::StartDoc(const wchar_t**) {
    if (mpDocument) {
        mpDocument->mTitle.clear();
        mpCurEntry = 0;
        mpCurAuthor = 0;
        mbInDoc = true;
    }
}

// @ 0x005423f0
void AtomParser::EndDoc() {
    mpCurEntry = 0;
    mpCurAuthor = 0;
    mbInDoc = false;
}

// @ 0x00542460
void AtomParser::StartEntry(const wchar_t**) {
    mpDocument->mEntryList.push_back();
    mpCurEntry = &mpDocument->mEntryList.back();
    mpCurEntry->mpAuthor = mpDocument->mpAuthor;
}

// @ 0x005424e0  (not a separate entry in the function list: it follows StartEntry)
void AtomParser::EndEntry() {
    if (mpCurEntry && mpCurEntry->mPublished == 0x7fffffffffffffffLL)
        mpCurEntry->mPublished = mpCurEntry->mUpdated;
    mpCurEntry = 0;
}

// @ 0x00542540
void AtomParser::StartAuthor(const wchar_t**) {
    mpCurAuthor = new Person;
    if (mpCurEntry)
        mpCurEntry->mpAuthor = mpCurAuthor;
    else
        mpDocument->mpAuthor = mpCurAuthor;
}

// @ 0x00542610 sym=??0Person@Feed@SP@@QAE@XZ
// Person::Person() (inline constructor emitted out of line for `new Person`)

// @ 0x005426d0
void AtomParser::EndAuthor() {
    mpCurAuthor = 0;
}

extern const wchar_t* kRelAttr;     // L"rel"
extern const wchar_t* kHrefAttr;    // L"href"


// @ 0x00542730
void AtomParser::StartLink(const wchar_t** attrs) {
    if (mbInDoc) {
        const wchar_t** pAttrs = attrs;
        const wchar_t* rel = 0;
        const wchar_t* href = 0;
        while (*pAttrs) {
            const wchar_t* name = *pAttrs++;
            const wchar_t* value = *pAttrs++;
            if (wcscmp(name, kRelAttr) == 0)
                rel = value;
            else if (wcscmp(name, kHrefAttr) == 0)
                href = value;
        }
        if (mpCurEntry && rel && href) {
            mpCurEntry->mLinkList.push_back();
            mpCurLink = &mpCurEntry->mLinkList.back();
            mpCurLink->mRel = rel;
            mpCurLink->mHref = href;
        }
    }
}

}  // namespace Feed
}  // namespace SP
