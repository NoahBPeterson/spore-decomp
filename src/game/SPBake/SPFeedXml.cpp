// src/game/SPBake/SPFeedXml.cpp -- migrated from slice(s) s00546160, s00547e90, s00545220 by tools/migrate/rewrite.py
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
typedef unsigned int size_type;
typedef int off_type;
struct XML_ParserStruct_s0054_5220;
typedef XML_ParserStruct_s0054_5220* XML_Parser;
void* operator new(unsigned int size);
inline void* operator new(unsigned int, void* p) { return p; }
extern wchar_t gEmptyString16[];
inline size_type CharStrlen(const wchar_t* s) {
    const wchar_t* p = s;
    while (*p) ++p;
    return (size_type)(p - s);
}
namespace eastl {
struct allocator_s0054_5220 {
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
extern "C" __declspec(dllimport) long wcstol(const wchar_t* s, wchar_t** end, int base);
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
void* FUN_0054a2d0(int a, int b, int c, char d);   // @ 0x54a2d0 lower_bound
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
extern short gFeedEndTable[];       // @ 0x13f3ae0
unsigned int FNV1_String16(const wchar_t* s, unsigned int hash, int b); // 0x00932f30
short* FUN_00547900(const void* table, int a, int b);
short* FUN_00547970(const void* table, int a, int b);
void   FUN_004228e0(int a, unsigned int b);
void FUN_00545aa0(...);
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
// ---- items of slice s00546160 end

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
