// Slice s00543f00: SP::Feed::AtomParser static handler-table initialisation.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// 0x00543f00 fills the three static lookup tables the Atom feed parser uses:
//   sStartHandlers (0x015e2e48) element name -> mem_fun1_t<void,AtomParser,const wchar_t**>
//   sEndHandlers   (0x015e2da8) element name -> mem_fun_t<void,AtomParser>
//   sMimeTypes     (0x015e2f54) MIME type    -> resource type id
// (each an eastl::vector_map<const wchar_t*, V, AtomParser::char16less>, types from the dev PDB),
// then installs the expat memory-handling suite and sets the "initialised" flag.
//
// Matching note: vector_map::insert must be the real inline EASTL body (calling the
// member lower_bound(key)); cl /Ob1 declines to inline it, but reserves its inline
// frame in the caller for the first ~26 calls, which produces the 28-byte holes in
// the original's frame. The emitted insert/vector::insert COMDATs are byte-exact
// with 0x00547320 / 0x00548860 too.
#include "types.h"
#include <string.h>
#include <new>
#pragma intrinsic(wcscmp)

namespace eastl
{
    template <typename T1, typename T2>
    struct pair
    {
        T1 first;
        T2 second;

        pair(const T1& x, const T2& y) : first(x), second(y) {}

        template <typename U, typename V>
        pair(const pair<U, V>& p) : first(p.first), second(p.second) {}
    };

    template <typename T1, typename T2>
    inline pair<T1, T2> make_pair(T1 a, T2 b)
    {
        return pair<T1, T2>(a, b);
    }

    template <typename Result, typename T>
    class mem_fun_t
    {
    public:
        typedef Result (T::*MemberFunction)();

        explicit mem_fun_t(MemberFunction pMemberFunction)
            : mpMemberFunction(pMemberFunction) {}

        Result operator()(T* pT) const { return (pT->*mpMemberFunction)(); }

    protected:
        MemberFunction mpMemberFunction;
    };

    template <typename Result, typename T, typename Argument>
    class mem_fun1_t
    {
    public:
        typedef Result (T::*MemberFunction)(Argument);

        explicit mem_fun1_t(MemberFunction pMemberFunction)
            : mpMemberFunction(pMemberFunction) {}

        Result operator()(T* pT, Argument arg) const { return (pT->*mpMemberFunction)(arg); }

    protected:
        MemberFunction mpMemberFunction;
    };

    template <typename Result, typename T>
    inline mem_fun_t<Result, T> mem_fun(Result (T::*MemberFunction)())
    {
        return mem_fun_t<Result, T>(MemberFunction);
    }

    template <typename Result, typename T, typename Argument>
    inline mem_fun1_t<Result, T, Argument> mem_fun(Result (T::*MemberFunction)(Argument))
    {
        return mem_fun1_t<Result, T, Argument>(MemberFunction);
    }

    template <typename T>
    inline int distance(T* first, T* last) { return (int)(last - first); }

    template <typename T>
    inline void advance(T*& i, int n) { i += n; }

    template <typename ForwardIterator, typename T, typename Compare>
    ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare compare)
    {
        int d = eastl::distance(first, last);

        while (d > 0)
        {
            ForwardIterator i  = first;
            int             d2 = d >> 1;

            eastl::advance(i, d2);

            if (compare(*i, value))
            {
                first = ++i;
                d    -= d2 + 1;
            }
            else
                d = d2;
        }
        return first;
    }

    struct allocator
    {
        const char* mpName;
        uint32_t    mFlags;
    };

    // eastl::vector<T> (only what vector_map needs; the out-of-line members are
    // the instances at 0x00548690/0x00547240/0x00548860 and 0x00530c80/0x00547440)
    template <typename T>
    class vector
    {
    public:
        typedef T            value_type;
        typedef T*           iterator;
        typedef unsigned int size_type;

        iterator begin() { return mpBegin; }
        iterator end() { return mpEnd; }

        iterator erase(iterator first, iterator last);
        void reserve(size_type n);
        iterator insert(iterator position, const value_type& value)
        {
            const int n = (int)(position - mpBegin); // Save this because we might reallocate.

            if ((position != mpEnd) || (mpEnd == mpCapacity))
                DoInsertValue(position, value);
            else
                ::new(mpEnd++) value_type(value);

            return mpBegin + n;
        }

        void DoInsertValue(iterator position, const value_type& value);

        void clear() { erase(mpBegin, mpEnd); }

    protected:
        T*        mpBegin;
        T*        mpEnd;
        T*        mpCapacity;
        allocator mAllocator;
    };

    template <typename Key, typename Value, typename Compare>
    class map_value_compare
    {
    public:
        Compare c;

        bool operator()(const Value& a, const Value& b) const { return c(a.first, b.first); }
        bool operator()(const Value& a, const Key& b) const { return c(a.first, b); }
        bool operator()(const Key& a, const Value& b) const { return c(a, b.first); }
    };

    // eastl::vector_map<Key, T, Compare> (sorted vector of pairs)
    template <typename Key, typename T, typename Compare>
    class vector_map : public vector< pair<Key, T> >
    {
    public:
        typedef vector< pair<Key, T> >                          base_type;
        typedef pair<Key, T>                                    value_type;
        typedef value_type*                                     iterator;
        typedef map_value_compare<Key, value_type, Compare>     value_compare;

        pair<iterator, bool> insert(const value_type& value)
        {
            const iterator itLB(lower_bound(value.first));

            if ((itLB != base_type::end()) && !mValueCompare(value, *itLB))
                return pair<iterator, bool>(itLB, false);

            return pair<iterator, bool>(base_type::insert(itLB, value), true);
        }

        iterator lower_bound(const Key& k)
        {
            return eastl::lower_bound(base_type::begin(), base_type::end(), k, mValueCompare);
        }

    protected:
        value_compare mValueCompare;
    };
}

namespace EA
{
    template <typename T>
    class RefCountVTemplate
    {
    public:
        virtual ~RefCountVTemplate() {}
        virtual int AddRef();
        virtual int Release();
        T mnRefCount;
    };

    namespace IO
    {
        class IStream
        {
        public:
            virtual ~IStream() {}
            virtual int AddRef() = 0;
            virtual int Release() = 0;
        };
    }
}

struct XML_Memory_Handling_Suite
{
    void* (*malloc_fcn)(size_t size);
    void* (*realloc_fcn)(void* ptr, size_t size);
    void  (*free_fcn)(void* ptr);
};

namespace SP { namespace Feed {

class AtomParser : public EA::RefCountVTemplate<int>, public EA::IO::IStream
{
public:
    struct char16less
    {
        bool operator()(const wchar_t* a, const wchar_t* b) const { return wcscmp(a, b) < 0; }
    };

    typedef eastl::mem_fun1_t<void, AtomParser, const wchar_t**> StartHandler;
    typedef eastl::mem_fun_t<void, AtomParser>                   EndHandler;

    typedef eastl::vector_map<const wchar_t*, StartHandler, char16less> StartHandlerMap;
    typedef eastl::vector_map<const wchar_t*, EndHandler, char16less>   EndHandlerMap;
    typedef eastl::vector_map<const wchar_t*, uint32_t, char16less>     MimeTypeMap;

    static void StaticInit();

    // start-element handlers (argument: expat attribute list)
    void StartDoc(const wchar_t** attrs);        // 0x00542330
    void StartEntry(const wchar_t** attrs);      // 0x00542460
    void StartAuthor(const wchar_t** attrs);     // 0x00542540
    void StartParent(const wchar_t** attrs);     // 0x00542cb0
    void StartOriginal(const wchar_t** attrs);   // 0x00542ee0
    void StartStat(const wchar_t** attrs);       // 0x00542730 (named StartLink in symbols/)
    void StartLink(const wchar_t** attrs);       // 0x00543590
    void StartCategory(const wchar_t** attrs);   // 0x005439d0
    void StartImage1(const wchar_t** attrs);     // 0x00543b90
    void StartImage2(const wchar_t** attrs);     // 0x00543bb0
    void StartImage3(const wchar_t** attrs);     // 0x00543bd0
    void StartImage4(const wchar_t** attrs);     // 0x00543bf0

    // end-element handlers
    void EndDoc();          // 0x005423f0
    void EndEntry();        // 0x005424e0
    void EndAuthor();       // 0x005426d0
    void EndTitle();        // 0x00543110
    void EndSubtitle();     // 0x005431a0
    void EndSubcount();     // 0x005431f0
    void EndName();         // 0x00543280
    void EndUri();          // 0x005432e0
    void EndId();           // 0x00543330
    void EndParent();       // 0x00542e80
    void EndOriginal();     // 0x005430b0
    void EndUpdated();      // 0x00543440
    void EndPublished();    // 0x005434a0
    void EndSummary();      // 0x005433f0
    void EndStat();         // 0x00542980
    void EndNotify();       // 0x00543520
    void EndMaxisMade();    // 0x005434e0
    void EndModelType();    // 0x00543240

    static StartHandlerMap           sStartHandlers;   // 0x015e2e48
    static EndHandlerMap             sEndHandlers;     // 0x015e2da8
    static MimeTypeMap               sMimeTypes;       // 0x015e2f54
    static XML_Memory_Handling_Suite sMemSuite;        // 0x015e2d90
    static bool                      sbInitialized;    // 0x015e2d9c
};

// Element / MIME-type name strings (pointer globals, 0x013f38f8..0x013f39a4)
extern const wchar_t* kAtomFeed;          // L"feed"
extern const wchar_t* kAtomEntry;         // L"entry"
extern const wchar_t* kAtomAuthor;        // L"author"
extern const wchar_t* kAtomTitle;         // L"title"
extern const wchar_t* kAtomSubtitle;      // L"subtitle"
extern const wchar_t* kAtomName;          // L"name"
extern const wchar_t* kAtomUri;           // L"uri"
extern const wchar_t* kAtomId;            // L"id"
extern const wchar_t* kAtomParent;        // L"sp:parent"
extern const wchar_t* kAtomOriginal;      // L"sp:original"
extern const wchar_t* kAtomPublished;     // L"published"
extern const wchar_t* kAtomUpdated;       // L"updated"
extern const wchar_t* kAtomSubcount;      // L"subcount"
extern const wchar_t* kAtomSummary;       // L"summary"
extern const wchar_t* kAtomStat;          // L"sp:stat"
extern const wchar_t* kAtomLink;          // L"link"
extern const wchar_t* kAtomCategory;      // L"category"
extern const wchar_t* kAtomModelType;     // L"modeltype"
extern const wchar_t* kAtomImage1;        // L"sp:image_1"
extern const wchar_t* kAtomImage2;        // L"sp:image_2"
extern const wchar_t* kAtomImage3;        // L"sp:image_3"
extern const wchar_t* kAtomImage4;        // L"sp:image_4"
extern const wchar_t* kAtomNotify;        // L"sp:notify"
extern const wchar_t* kAtomMaxisMade;     // L"sp:maxis-made"
extern const wchar_t* kMimeCell;          // L"application/x-cell+xml"
extern const wchar_t* kMimeCreature;      // L"application/x-creature+xml"
extern const wchar_t* kMimeBuilding;      // L"application/x-building+xml"
extern const wchar_t* kMimeVehicle;       // L"application/x-vehicle+xml"
extern const wchar_t* kMimeUFO;           // L"application/x-ufo+xml"
extern const wchar_t* kMimeFlora;         // L"application/x-flora+xml"
extern const wchar_t* kMimeAdventure;     // L"application/x-adventure+xml"
extern const wchar_t* kMimePNG;           // L"image/png"

// resource type ids
const uint32_t kTypeCell      = 0x3d97a8e4;
const uint32_t kTypeCreature  = 0x2b978c46;
const uint32_t kTypeBuilding  = 0x2399be55;
const uint32_t kTypeVehicle   = 0x24682294;
const uint32_t kTypeUFO       = 0x476a98c7;
const uint32_t kTypeFlora     = 0x438f6347;
const uint32_t kTypeAdventure = 0x366a930d;

void* XmlMalloc(size_t size);               // 0x00541600
void* XmlRealloc(void* ptr, size_t size);   // 0x00541630
void  XmlFree(void* ptr);                   // 0x00541660

// @ 0x00543f00
void AtomParser::StaticInit()
{
    sStartHandlers.clear();
    sStartHandlers.reserve(6);
    sStartHandlers.insert(eastl::make_pair(kAtomFeed,     eastl::mem_fun(&AtomParser::StartDoc)));
    sStartHandlers.insert(eastl::make_pair(kAtomEntry,    eastl::mem_fun(&AtomParser::StartEntry)));
    sStartHandlers.insert(eastl::make_pair(kAtomAuthor,   eastl::mem_fun(&AtomParser::StartAuthor)));
    sStartHandlers.insert(eastl::make_pair(kAtomParent,   eastl::mem_fun(&AtomParser::StartParent)));
    sStartHandlers.insert(eastl::make_pair(kAtomOriginal, eastl::mem_fun(&AtomParser::StartOriginal)));
    sStartHandlers.insert(eastl::make_pair(kAtomStat,     eastl::mem_fun(&AtomParser::StartStat)));
    sStartHandlers.insert(eastl::make_pair(kAtomLink,     eastl::mem_fun(&AtomParser::StartLink)));
    sStartHandlers.insert(eastl::make_pair(kAtomCategory, eastl::mem_fun(&AtomParser::StartCategory)));
    sStartHandlers.insert(eastl::make_pair(kAtomImage1,   eastl::mem_fun(&AtomParser::StartImage1)));
    sStartHandlers.insert(eastl::make_pair(kAtomImage2,   eastl::mem_fun(&AtomParser::StartImage2)));
    sStartHandlers.insert(eastl::make_pair(kAtomImage3,   eastl::mem_fun(&AtomParser::StartImage3)));
    sStartHandlers.insert(eastl::make_pair(kAtomImage4,   eastl::mem_fun(&AtomParser::StartImage4)));

    sEndHandlers.clear();
    sEndHandlers.reserve(14);
    sEndHandlers.insert(eastl::make_pair(kAtomFeed,      eastl::mem_fun(&AtomParser::EndDoc)));
    sEndHandlers.insert(eastl::make_pair(kAtomEntry,     eastl::mem_fun(&AtomParser::EndEntry)));
    sEndHandlers.insert(eastl::make_pair(kAtomAuthor,    eastl::mem_fun(&AtomParser::EndAuthor)));
    sEndHandlers.insert(eastl::make_pair(kAtomTitle,     eastl::mem_fun(&AtomParser::EndTitle)));
    sEndHandlers.insert(eastl::make_pair(kAtomSubtitle,  eastl::mem_fun(&AtomParser::EndSubtitle)));
    sEndHandlers.insert(eastl::make_pair(kAtomSubcount,  eastl::mem_fun(&AtomParser::EndSubcount)));
    sEndHandlers.insert(eastl::make_pair(kAtomName,      eastl::mem_fun(&AtomParser::EndName)));
    sEndHandlers.insert(eastl::make_pair(kAtomUri,       eastl::mem_fun(&AtomParser::EndUri)));
    sEndHandlers.insert(eastl::make_pair(kAtomId,        eastl::mem_fun(&AtomParser::EndId)));
    sEndHandlers.insert(eastl::make_pair(kAtomParent,    eastl::mem_fun(&AtomParser::EndParent)));
    sEndHandlers.insert(eastl::make_pair(kAtomOriginal,  eastl::mem_fun(&AtomParser::EndOriginal)));
    sEndHandlers.insert(eastl::make_pair(kAtomUpdated,   eastl::mem_fun(&AtomParser::EndUpdated)));
    sEndHandlers.insert(eastl::make_pair(kAtomPublished, eastl::mem_fun(&AtomParser::EndPublished)));
    sEndHandlers.insert(eastl::make_pair(kAtomSummary,   eastl::mem_fun(&AtomParser::EndSummary)));
    sEndHandlers.insert(eastl::make_pair(kAtomStat,      eastl::mem_fun(&AtomParser::EndStat)));
    sEndHandlers.insert(eastl::make_pair(kAtomNotify,    eastl::mem_fun(&AtomParser::EndNotify)));
    sEndHandlers.insert(eastl::make_pair(kAtomMaxisMade, eastl::mem_fun(&AtomParser::EndMaxisMade)));
    sEndHandlers.insert(eastl::make_pair(kAtomModelType, eastl::mem_fun(&AtomParser::EndModelType)));

    sMimeTypes.clear();
    sMimeTypes.reserve(9);
    sMimeTypes.insert(eastl::make_pair(kMimeCell,      kTypeCell));
    sMimeTypes.insert(eastl::make_pair(kMimeCreature,  kTypeCreature));
    sMimeTypes.insert(eastl::make_pair(kMimeBuilding,  kTypeBuilding));
    sMimeTypes.insert(eastl::make_pair(kMimeVehicle,   kTypeVehicle));
    sMimeTypes.insert(eastl::make_pair(kMimeUFO,       kTypeUFO));
    sMimeTypes.insert(eastl::make_pair(kMimeFlora,     kTypeFlora));
    sMimeTypes.insert(eastl::make_pair(kMimeAdventure, kTypeAdventure));
    sMimeTypes.insert(eastl::make_pair(kMimePNG,       0x2f7d0004));     // pair<const wchar_t*,int> -> converted
    sMimeTypes.insert(eastl::make_pair(L"img/png",     0x2f7d0004));

    sMemSuite.malloc_fcn  = XmlMalloc;
    sMemSuite.realloc_fcn = XmlRealloc;
    sMemSuite.free_fcn    = XmlFree;
    sbInitialized = true;
}

}} // namespace SP::Feed
