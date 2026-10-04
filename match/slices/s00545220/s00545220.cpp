// Slice s00545220: SP::Feed::AtomParser expat callbacks and SP::Feed::HandshakeParser
// (SPFeedXml.cpp), plus an out-of-line DefaultRefCounted::AddRef.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP (no /EHsc).
// Names come from the 2008 dev-build PDB where the retail code clearly corresponds; the rest
// are descriptive guesses.

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

    // element handler signatures used by the dispatch maps
    typedef void (AtomParser::*StartFn)(const wchar_t** attrs);
    typedef void (AtomParser::*EndFn)();
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

extern "C" __declspec(dllimport) unsigned long wcstoul(const wchar_t* s, wchar_t** end, int base);
extern "C" __declspec(dllimport) long wcstol(const wchar_t* s, wchar_t** end, int base);
extern "C" {
void XML_StopParser(XML_Parser p, unsigned char resumable);
}
struct XML_Memory_Handling_Suite {
    void* (*malloc_fcn)(unsigned int size);
    void* (*realloc_fcn)(void* p, unsigned int size);
    void (*free_fcn)(void* p);
};
namespace EA { namespace StdC {
unsigned __int64 StrtoU64(const wchar_t* s, wchar_t** end, int base);   // 0x0092d710
} }
unsigned int FNVHash(const char* s, unsigned int seed, int lowercase);   // 0x00932e80

// ---------------------------------------------------------------------------
class DefaultRefCounted {
public:
    virtual ~DefaultRefCounted();
    int AddRef();
    int mnRefCount;
};

// @ 0x005454f0
int DefaultRefCounted::AddRef() {
    return mnRefCount++ + 1;
}

// ---------------------------------------------------------------------------
namespace eastl {
template <typename T1, typename T2> struct pair {
    T1 first;
    T2 second;
};

struct binary_function_base {};
template <typename Result, typename T, typename Argument>
struct mem_fun1_t : binary_function_base {
    typedef Result (T::*MemberFunction)(Argument);
    MemberFunction mpMemberFunction;
    Result operator()(T* pT, Argument arg) const { return (pT->*mpMemberFunction)(arg); }
};
struct unary_function_base {};
template <typename Result, typename T>
struct mem_fun_t : unary_function_base {
    typedef Result (T::*MemberFunction)();
    MemberFunction mpMemberFunction;
    Result operator()(T* pT) const { return (pT->*mpMemberFunction)(); }
};

template <typename Key, typename T>
struct vector_map {
    typedef pair<Key, T> value_type;
    typedef value_type* iterator;
    iterator mpBegin;
    iterator mpEnd;
    iterator mpCapacity;
    unsigned int mAllocator;

    iterator end() { return mpEnd; }
    pair<iterator, iterator> equal_range(const Key& k);     // 0x00548740
    iterator find(const Key& k) {
        const pair<iterator, iterator> pairIts(equal_range(k));
        if (pairIts.first != pairIts.second)
            return pairIts.first;
        return end();
    }
};
}  // namespace eastl

namespace SP {
namespace Feed {
enum FeedType { kFeedTypeUser = 2 };
FeedType GetFeedTypeFromURI(const char* uri);                             // 0x005419c0
void ParseDateTime(const string16& s, __int64* pTime);                   // 0x00541680

typedef eastl::vector_map<const wchar_t*, eastl::mem_fun1_t<void, AtomParser, const wchar_t**> > StartElementMap;
typedef eastl::vector_map<const wchar_t*, eastl::mem_fun_t<void, AtomParser> > EndElementMap;
extern StartElementMap sAtomStartElementMap;    // 0x015e2e48
extern EndElementMap sAtomEndElementMap;        // 0x015e2da8

// @ 0x00545220
void AtomParser::StartElementHandler(void* pUserData, const wchar_t* name, const wchar_t** attrs) {
    AtomParser* pThis = (AtomParser*)pUserData;
    if (pThis->mpDocument) {
        pThis->mCharacterData.resize(0);
        StartElementMap::iterator it = sAtomStartElementMap.find(name);
        if (it != sAtomStartElementMap.end())
            it->second(pThis, attrs);
    }
}

// @ 0x005452b0
void AtomParser::EndElementHandler(void* pUserData, const wchar_t* name) {
    AtomParser* pThis = (AtomParser*)pUserData;
    if (pThis->mpDocument) {
        EndElementMap::iterator it = sAtomEndElementMap.find(name);
        if (it != sAtomEndElementMap.end()) {
            string16& s = pThis->mCharacterData;
            s.erase(0, s.find_first_not_of(L" \t\n\r"));
            s.erase(s.find_last_not_of(L" \t\n\r") + 1);
            it->second(pThis);
        }
    }
}

// ---------------------------------------------------------------------------
struct HandshakeData {
    string16 mScreenName;           // +0x00
    unsigned __int64 mnNextID;      // +0x10
    unsigned __int64 mnUserID;      // +0x18
    int mnField20;                  // +0x20
};

struct FeedDescription {            // 0x70 bytes
    FeedDescription();              // implicit (inline) destructor
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

struct FeedList {                   // eastl::vector<FeedDescription, sp_vector_allocator>
    FeedDescription* mpBegin;
    FeedDescription* mpEnd;
    FeedDescription* mpCapacity;
    unsigned int mAllocator;
    FeedDescription& push_back() {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) FeedDescription();
        else
            DoInsertValue(mpEnd, FeedDescription());
        return *(mpEnd - 1);
    }
    void DoInsertValue(FeedDescription* position, const FeedDescription& value);
    FeedDescription& back() { return *(mpEnd - 1); }
    FeedDescription* erase(FeedDescription* first, FeedDescription* last);   // 0x00548a30
    void clear() { erase(mpBegin, mpEnd); }
};

extern XML_Memory_Handling_Suite gXMLMemorySuite;   // 0x015e2d90
void* XMLMalloc(unsigned int size);                 // 0x00541600
void* XMLRealloc(void* p, unsigned int size);       // 0x00541630
void XMLFree(void* p);                              // 0x00541660

extern const wchar_t* kRelAttr;     // L"rel"
extern const wchar_t* kTypeAttr;    // L"type"
extern const wchar_t* kHrefAttr;    // L"href"

class HandshakeParser : public EA::RefCountVTemplate<int>, public EA::IO::IStream {
public:
    HandshakeParser();
    virtual ~HandshakeParser();
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

    bool SetLists(FeedList* pMyFeeds, FeedList* pSubscriptions, FeedList* pList28, HandshakeData* pData);
    bool ResetParser();
    bool Open();
    void StartDoc(const wchar_t** attrs);
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
    HandshakeData* mpHandshakeData;     // +0x2c
    bool mbInDoc;                       // +0x30
    FeedList* mpCurList;                // +0x34
    FeedDescription* mpCurFeed;         // +0x38
    unsigned int mCurListID;            // +0x3c
    bool mbInAuthor;                    // +0x40
    bool mbOpen;                        // +0x41
    int mParseStatus;                   // +0x44
    long mBitesRead;                    // +0x48
};

// @ 0x005453c0
HandshakeParser::HandshakeParser()
    : mpXMLParser(0), mpMyFeeds(0), mpSubscriptions(0), mpList28(0), mpHandshakeData(0), mbInDoc(false),
      mpCurList(0), mpCurFeed(0), mCurListID(0), mbInAuthor(false), mbOpen(false), mParseStatus(1),
      mBitesRead(0) {
    gXMLMemorySuite.malloc_fcn = XMLMalloc;
    gXMLMemorySuite.realloc_fcn = XMLRealloc;
    gXMLMemorySuite.free_fcn = XMLFree;
}

// @ 0x00545520
bool HandshakeParser::SetPosition(off_type position, EA::IO::PositionType positionType) {
    return (positionType == EA::IO::kPositionTypeBegin && position == mBitesRead) ||
           (positionType == EA::IO::kPositionTypeCurrent && position == 0);
}

// @ 0x00545560
size_type HandshakeParser::GetAvailable() const {
    return (size_type)-1;
}

// @ 0x00545570
size_type HandshakeParser::Read(void*, size_type) {
    return (size_type)-1;
}

// @ 0x005455b0
HandshakeParser::~HandshakeParser() {
    if (mbOpen)
        Close();
    XML_ParserFree(mpXMLParser);
}

// @ 0x00545620
bool HandshakeParser::SetLists(FeedList* pMyFeeds, FeedList* pSubscriptions, FeedList* pList28,
                               HandshakeData* pData) {
    mpMyFeeds = pMyFeeds;
    mpSubscriptions = pSubscriptions;
    mpList28 = pList28;
    mpHandshakeData = pData;
    return mpMyFeeds && mpSubscriptions;
}

// @ 0x00545680
bool HandshakeParser::ResetParser() {
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

// @ 0x00545710
bool HandshakeParser::Open() {
    if (!mbOpen && mpMyFeeds && mpSubscriptions) {
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
    return mbOpen;
}

// @ 0x005457e0
bool HandshakeParser::Write(const void* pData, size_type nSize) {
    if (mbOpen && mpMyFeeds && mpSubscriptions) {
        mParseStatus = XML_Parse(mpXMLParser, (const char*)pData, nSize, false);
        mBitesRead += nSize;
        return mParseStatus == 1;
    }
    return false;
}

// @ 0x00545850
bool HandshakeParser::Close() {
    if (mbOpen && mpMyFeeds && mpSubscriptions) {
        mParseStatus = XML_Parse(mpXMLParser, 0, 0, true);
        mbOpen = false;
        return mParseStatus == 1;
    }
    return mpMyFeeds && mpSubscriptions;
}

// @ 0x005458e0
int HandshakeParser::GetAccessFlags() const {
    if (mbOpen)
        return 2;
    else
        return 0;
}

// @ 0x00545910
int HandshakeParser::GetState() const {
    if (mbOpen) {
        if (mParseStatus != 1)
            return XML_GetErrorCode(mpXMLParser);
        else
            return 0;
    } else
        return -2;
}

// @ 0x00545950
off_type HandshakeParser::GetPosition(EA::IO::PositionType positionType) const {
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

// @ 0x005459a0
void HandshakeParser::StartDoc(const wchar_t**) {
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

// @ 0x00545aa0
void HandshakeParser::EndDoc() {
    mpCurList = 0;
    mpCurFeed = 0;
    mbInDoc = false;
}

// @ 0x00545ad0
void HandshakeParser::StartFeed() {
    if (mpCurList) {
        mpCurList->push_back();
        mpCurFeed = &mpCurList->back();
    }
}

// @ 0x00545b20
void HandshakeParser::EndFeed() {
    if (mpCurFeed) {
        mpCurFeed->mFeedType = GetFeedTypeFromURI(mpCurFeed->mID.c_str());
        if (mpCurFeed->mFeedType == kFeedTypeUser && mpCurFeed->mnAuthorID == mpHandshakeData->mnUserID)
            mpCurFeed->mFeedType = 7;
        if (mCurListID == 0x725b8629)
            mpCurFeed->mFeedType = 11;
        mpCurFeed = 0;
    }
}

// @ 0x00545bd0
void HandshakeParser::StartAuthor() {
    mbInAuthor = true;
}

// @ 0x00545bf0
void HandshakeParser::EndAuthor() {
    mbInAuthor = false;
}

// @ 0x00545c10
void HandshakeParser::EndName() {
    if (mpCurFeed)
        mpCurFeed->mAuthor = mCharacterData;
}

// @ 0x00545c60
void HandshakeParser::EndAuthorID() {
    if (mpCurFeed)
        mpCurFeed->mnAuthorID = EA::StdC::StrtoU64(mCharacterData.c_str(), 0, 10);
}

// @ 0x00545ca0
void HandshakeParser::BeginList(FeedList* pList, unsigned int listID) {
    mpCurList = pList;
    mCurListID = listID;
}

// @ 0x00545cc0
void HandshakeParser::EndList() {
    mpCurList = 0;
    mCurListID = 0;
}

// @ 0x00545ce0
void HandshakeParser::EndTitle() {
    if (mpCurFeed)
        mpCurFeed->mTitle = mCharacterData;
}

// @ 0x00545d30
void HandshakeParser::EndSubtitle() {
    if (mpCurFeed)
        mpCurFeed->mSubtitle = mCharacterData;
}

// @ 0x00545d80
void HandshakeParser::EndSubcount() {
    if (mpCurFeed)
        mpCurFeed->mnSubCount = wcstoul(mCharacterData.c_str(), 0, 10);
}

// @ 0x00545dc0
void HandshakeParser::StartLink(const wchar_t** attrs) {
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

// @ 0x00545fa0
void HandshakeParser::EndId() {
    if (mpCurFeed) {
        mpCurFeed->mID.sprintf("%ls", mCharacterData);
        mpCurFeed->mnIDHash = FNVHash(mpCurFeed->mID.c_str(), 0x811c9dc5, 1);
    }
}

// @ 0x00546020
void HandshakeParser::EndUpdated() {
    if (mpCurFeed)
        ParseDateTime(mCharacterData, &mpCurFeed->mUpdated);
}

// @ 0x00546050
void HandshakeParser::EndNextID() {
    if (mpHandshakeData)
        mpHandshakeData->mnNextID = EA::StdC::StrtoU64(mCharacterData.c_str(), 0, 10);
}

// @ 0x00546090
void HandshakeParser::EndUserID() {
    if (mpHandshakeData)
        mpHandshakeData->mnUserID = EA::StdC::StrtoU64(mCharacterData.c_str(), 0, 10);
}

// @ 0x005460d0
void HandshakeParser::EndField20() {
    if (mpHandshakeData)
        mpHandshakeData->mnField20 = wcstol(mCharacterData.c_str(), 0, 10);
}

// @ 0x00546110
void HandshakeParser::EndScreenName() {
    if (mpHandshakeData)
        mpHandshakeData->mScreenName = mCharacterData;
}

}  // namespace Feed
}  // namespace SP
