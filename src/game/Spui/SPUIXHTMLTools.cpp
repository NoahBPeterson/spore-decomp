// src/game/Spui/SPUIXHTMLTools.cpp -- migrated from slice(s) s008356e0, s00837820, s00836910 by tools/migrate/rewrite.py
// Object file: Spui/SPUIXHTMLTools.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include "EA/ArgScript/cArguments.h"
#include "EA/UTFWin/CustomDrawable.h"
#include "EA/UTFWin/CustomWinProc.h"
#include "EA/UTFWin/IDrawable.h"
#include "EA/UTFWin/ISerializable.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/ArgScript/cError.h"

// unnamed retail callees and globals (address in the comment)
extern char g_eastlTag[];

// ---- items of slice s00836910 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" const wchar_t* g_dataPrefix;      // 0x01548788  L"data:"
void* __cdecl operator_new6(uint32_t, const void*, int, int, const char*, int);
void  __cdecl operator_delete__(void*);                                    // 0x00f47380
void  __cdecl VectorBool_DoInsertValue(void*, const void*, uint32_t);
void  __cdecl memmove_1(void*, const void*, uint32_t);                     // 0x013cc480 msvcr90!memmove
void* __cdecl EASTL_memmove(void* dst, const void* src, unsigned int n);   // 0x011e0744
void  __cdecl EncodeBase64String(const void* src, void* dst);              // 0x00941a10
extern "C" char           g_emptyStr_s0083_6910[];      // 0x01667bac  shared empty eastl string storage
struct RawFixed {
    uint8_t* mBegin;      // +0x00
    uint8_t* mEnd;        // +0x04
    uint8_t* mCapacity;   // +0x08
    int      mAllocator;  // +0x0c
    uint8_t* mBuffer;     // +0x10

    void Init(const RawFixed& other);                 // 0x00836850
    void Assign(const void* first, const void* last); // 0x00836910
    void AppendRange(const void* first, const void* last); // 0x0045f430
    void AppendWide(const void* first, const void* last);  // 0x0042f9d0 (WideFixedBuf::append)
    void AssignStr(const wchar_t* first, const wchar_t* last); // 0x00672750
    RawFixed* AssignCStr(const wchar_t* s);           // 0x008369e0
    RawFixed* SubstrInto(RawFixed* dst, uint32_t pos, uint32_t len); // 0x00836a30
    void Swap(RawFixed& other);                       // 0x00836a90
    void Reserve(uint32_t n);                         // 0x00837020
    void Reserve2(uint32_t n);                        // 0x00837230
    RawFixed* AppendN(uint32_t count, uint8_t c);     // 0x00837270
    void Resize(uint32_t n);                          // 0x00837310

    // SSO-string helpers shared by every instantiation; declared only, each maps
    // onto the corresponding eastl::basic_string member in the original image.
    void Construct256(const wchar_t* s);   // 0x007f48d0
    void Construct32(const wchar_t* s);    // 0x006743f0
    void Reset1024(int n);                 // 0x006726f0
    void Reset32(int n);                   // 0x008366e0
    unsigned FindCh(wchar_t ch, unsigned pos);          // 0x008364c0
    int      RFindCh(wchar_t ch, int pos);              // 0x00836500
    unsigned FindStr(const wchar_t* s, unsigned pos);   // 0x00608340
    void     MakeLower();                               // 0x005e8e80
};
template <int N>
struct FixedString : RawFixed {
    wchar_t mData[N];

    FixedString() {
        wchar_t* buf = mData;
        mBuffer = (uint8_t*)buf;
        mEnd = (uint8_t*)buf;
        mBegin = (uint8_t*)buf;
        mCapacity = (uint8_t*)(buf + N);
        *buf = 0;
    }
    ~FixedString() {
        if ((((int)((char*)mCapacity - (char*)mBegin) & -2) > 2) && mBegin &&
            mBegin != mBuffer) {
            operator_delete__(mBegin);
        }
    }
};
struct cDataURI {
    int mEncoding;              // +0x00
    FixedString<32> mScheme;    // +0x04
    FixedString<1024> mValue;   // +0x58
    bool mbBase64;              // +0x86c

    cDataURI(const wchar_t* p);
    ~cDataURI();
    void init(const wchar_t* p);
};
static unsigned int CharStrlen(const wchar_t* p) {
    const wchar_t* e = p;
    while (*e) ++e;
    return (unsigned int)(e - p);
}
template <typename T> static const T& max_alt(const T& a, const T& b) { return a < b ? b : a; }
struct EaString {
    wchar_t* mpBegin;     // +0x00
    wchar_t* mpEnd;       // +0x04
    wchar_t* mpCapacity;  // +0x08
    uint32_t mAllocator;  // +0x0c

    EaString& operator+=(const wchar_t* s);                            // 0x00599bb0
    EaString* AppendChar(uint32_t count, wchar_t c);                   // 0x0042d2e0
    EaString* AppendRange(const wchar_t* first, const wchar_t* last);  // 0x00429580
    EaString* AllocateSelf(uint32_t n);                                // 0x00429760
    EaString& operator=(const EaString& other);                        // 0x0056e2d0

    ~EaString() {
        if ((((int)((char*)mpCapacity - (char*)mpBegin) & -2) > 2) && mpBegin)
            operator_delete__(mpBegin);
    }
};
struct CharStr {
    char* mpBegin;        // +0x00
    char* mpEnd;          // +0x04
    char* mpCapacity;     // +0x08
    uint32_t mAllocator;  // +0x0c

    void resize(uint32_t n);   // 0x00478930

    ~CharStr() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin) operator_delete__(mpBegin);
    }
};
static inline bool Unreserved(uint8_t c) {
    if (c >= 'A' && c <= 'Z') return true;
    if (c >= 'a' && c <= 'z') return true;
    if (c >= '0' && c <= '9') return true;
    return c == '-' || c == '_' || c == '.' || c == '~';
}
static inline wchar_t HexDigit(unsigned v) {
    if (v < 10) return (wchar_t)(v + 0x30);
    if (v < 16) return (wchar_t)(v + 0x37);
    return (wchar_t)0x5e;
}
// ---- items of slice s00836910 end

// ---- items of slice s008356e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t g_emptyStr;     // 0x1667bac
extern wchar_t g_emptyCap;     // 0x1667bae
template <typename T> static const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
struct UShortVec {
    const uint16_t* mpBegin;
    const uint16_t* mpEnd;
    int FindFrom(uint16_t c, uint32_t position);
    int ReverseFind(uint16_t c, uint32_t position);
};
static const uint16_t* CharTypeStringRFind(const uint16_t* pRBegin, const uint16_t* pREnd,
                                           uint16_t c) {
    while (pRBegin > pREnd) {
        if (*(pRBegin - 1) == c) return pRBegin;
        --pRBegin;
    }
    return pREnd;
}
struct BoolVec {
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCapacity;
    uint32_t mPad;          // +0xc
    uint32_t mAllocator;    // +0x10
    void ReserveBuffer(uint32_t n);
    BoolVec* Init(const BoolVec& other);
};
struct String8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;
};
extern "C" __declspec(dllimport) wchar_t* __cdecl wcsrchr_s0083_56e0(const wchar_t*, wchar_t);
extern "C" __declspec(dllimport) char* __cdecl strstr_s0083_56e0(const char*, const char*);
void __cdecl ConvertToString8(String8* out, const wchar_t* s, int len); // 0x93c440
struct MapNode { uint32_t mValue; char* mKey; MapNode* mpNext; };
struct MapIterator { MapNode* mpNode; MapNode** mpBucket; };
struct ExtMap {
    uint32_t   mUnk0;         // +0x0
    MapNode**  mpBuckets;     // +0x4
    uint32_t   mBucketCount;  // +0x8
    void Begin(MapIterator* it); // 0x594410
};
struct ResFinder {
    uint32_t mPad[3];         // +0x0
    ExtMap   mMap;            // +0xc
    uint32_t FindByExt(wchar_t* name);
};
// ---- items of slice s008356e0 end

// ---- items of slice s00837820 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" char gEmptyString8[];               // 0x01667bac
extern "C" const wchar_t* g_01548788;          // 0x01548788
#pragma intrinsic(strlen)
struct MemoryStream {
    virtual void v00();
    virtual void AddRef();                              // +0x04
    virtual void Release();                             // +0x08
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28(int, int);                         // +0x28
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void Write(const void* data, unsigned size); // +0x38
    MemoryStream* Construct(void* a, void* b, const char* name);  // 0x0093c270
    void SetOption(int opt, float value);               // 0x0093bb40
};
struct WideString256 {
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    uint32_t mAllocator;   // +0x0c
    wchar_t* mpBuffer;     // +0x10
    wchar_t  mData[256];   // +0x14

    WideString256() {
        wchar_t* b = mData;
        mpBegin = b;
        mpEnd = b;
        mpCapacity = b + 256;
        mAllocator = 0;
        mpBuffer = b;
        *b = 0;
    }
    ~WideString256() {
        if ((((int)((char*)mpCapacity - (char*)mpBegin) & -2) > 2) && mpBegin && mpBegin != mpBuffer)
            operator_delete__(mpBegin);
    }
    void set_capacity(unsigned n);                       // 0x004c29c0
    void append(unsigned n, wchar_t c);                  // 0x004c1ff0
};
struct CharString {
    char*    mpBegin;      // +0x00
    char*    mpEnd;        // +0x04
    char*    mpCapacity;   // +0x08
    uint32_t mAllocator;   // +0x0c

    CharString() {
        mpBegin = gEmptyString8;
        mpEnd = gEmptyString8;
        mpCapacity = gEmptyString8 + 1;
        mAllocator = 0;
    }
    ~CharString() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin) operator_delete__(mpBegin);
    }
    void set_capacity(unsigned n);                       // 0x0047d240
    void append(const char* first, const char* last);    // 0x00455d60
};
bool __cdecl Base64DecodeString(int* src, int* dst);     // 0x00941af0
template <int N>
struct WideFixed {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    wchar_t* mpBuffer;
    wchar_t  mData[N];
};
struct cDataURI_s0083_7820 {
    int             mEncoding;   // +0x00
    WideFixed<32>   mScheme;     // +0x04
    WideFixed<1024> mValue;      // +0x58
    bool            mbBase64;    // +0x86c

    cDataURI_s0083_7820(const wchar_t* p);  // 0x008371e0
    ~cDataURI_s0083_7820() {
        if ((((int)((char*)mValue.mpCapacity - (char*)mValue.mpBegin) & -2) > 2) &&
            mValue.mpBegin && mValue.mpBegin != mValue.mpBuffer)
            operator_delete__(mValue.mpBegin);
        if ((((int)((char*)mScheme.mpCapacity - (char*)mScheme.mpBegin) & -2) > 2) &&
            mScheme.mpBegin && mScheme.mpBegin != mScheme.mpBuffer)
            operator_delete__(mScheme.mpBegin);
    }
    bool GetStream(void** out);  // 0x00836990 (cDataURI::GetStream)
};
static inline unsigned HexVal(wchar_t c) {
    if (c >= L'0' && c <= L'9') return (unsigned)(c - L'0');
    if (c >= L'A' && c <= L'F') return (unsigned)(c - 0x37);
    if (c >= L'a' && c <= L'f') return (unsigned)(c - 0x57);
    return 0;
}
struct CharFixed32 {
    char* a;        // +0x00 begin
    char* b;        // +0x04 end
    char* c;        // +0x08 capacity
    char* d;        // +0x0c allocator
    char* e;        // +0x10 inline buffer
    char  mData[32];// +0x14

    CharFixed32() {
        char* p = mData;
        a = p;
        b = p;
        c = p + 32;
        d = 0;
        e = p;
        *p = 0;
    }
    ~CharFixed32() {
        if ((c - a) > 1 && a && a != e) operator_delete__(a);
    }
    void Reserve2(unsigned n);                            // 0x00837230
    CharFixed32* AppendN(unsigned count, unsigned char ch); // 0x00837270
};
struct EStr {
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    void*    mpAlloc;      // +0x0c
    wchar_t* mpInline;     // +0x10
    wchar_t  mBuf[0x20];   // +0x14

    EStr* Construct(const wchar_t* src);                  // 0x006743f0
    unsigned find(const wchar_t* needle, unsigned pos);   // 0x00608340
    ~EStr() {
        if ((((int)((char*)mpCapacity - (char*)mpBegin) & -2) > 2) && mpBegin && mpBegin != mpInline)
            operator_delete__(mpBegin);
    }
};
struct CharAssignString {
    char*    mpBegin;
    char*    mpEnd;
    char*    mpCapacity;
    uint32_t mAllocator;
    void assign(const char* first, const char* last);     // 0x00454cb0
};
struct ResourceRequest {
    char mPad00[0x0c];
    const wchar_t* mPath;    // +0x0c
    CharAssignString mMime;  // +0x10
    void SetStream(void* stream);                         // 0x00836480
};
struct ResourceProvider {
    void FinishRequest(ResourceRequest* req, int status); // 0x008ffb40
};
struct cSPUInHandler {
    char mPad00[8];
    ResourceProvider* mProvider;   // +0x08
    bool ProcessRequest(ResourceRequest* req, int unused);
};
// ---- items of slice s00837820 end

// @ 0x008364c0
int UShortVec::FindFrom(uint16_t c, uint32_t position)
{
    if (position < (uint32_t)(mpEnd - mpBegin)) {
        const uint16_t* pResult = mpBegin + position;
        while (pResult != mpEnd && *pResult != c) ++pResult;
        if (pResult != mpEnd) return (int)(pResult - mpBegin);
    }
    return -1;
}

// @ 0x00836500
int UShortVec::ReverseFind(uint16_t c, uint32_t position)
{
    const uint32_t nLength = (uint32_t)(mpEnd - mpBegin);
    if (nLength) {
        const uint16_t* const pEnd = mpBegin + min_alt(nLength - 1, position) + 1;
        const uint16_t* const pResult = CharTypeStringRFind(pEnd, mpBegin, c);
        if (pResult != mpBegin) return (int)((pResult - 1) - mpBegin);
    }
    return -1;
}

// @ 0x00836620
void BoolVec::ReserveBuffer(uint32_t n)
{
    if (n > 1) {
        uint8_t* m = (uint8_t*)operator_new6(n, g_eastlTag, 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        mpBegin = m;
        mpEnd = m;
        mpCapacity = m + n;
    } else {
        mpBegin = (uint8_t*)&g_emptyStr;
        mpEnd = (uint8_t*)&g_emptyStr;
        mpCapacity = (uint8_t*)&g_emptyCap;
    }
}

// @ 0x00836740
uint32_t ResFinder::FindByExt(wchar_t* name)
{
    wchar_t* dot = wcsrchr_s0083_56e0(name, L'.');
    if (dot) {
        wchar_t* p = dot;
        wchar_t c;
        do { c = *p; ++p; } while (c);
        if ((uint32_t)(p - (dot + 1)) > 1) {
            MapIterator it;
            String8 ext;
            ConvertToString8(&ext, dot + 1, -1);
            ExtMap* map = &mMap;
            map->Begin(&it);
            MapNode* node = it.mpNode;
            MapNode** bucket = it.mpBucket;
            while (node != map->mpBuckets[map->mBucketCount]) {
                if (strstr_s0083_56e0(node->mKey, ext.mpBegin)) {
                    uint32_t v = node->mValue;
                    if ((int)(ext.mpCapacity - ext.mpBegin) > 1 && ext.mpBegin)
                        operator_delete__(ext.mpBegin);
                    return v;
                }
                node = node->mpNext;
                while (node == 0) {
                    ++bucket;
                    node = *bucket;
                }
            }
            if ((int)(ext.mpCapacity - ext.mpBegin) > 1 && ext.mpBegin)
                operator_delete__(ext.mpBegin);
        }
    }
    return 0;
}

// @ 0x00836850
BoolVec* BoolVec::Init(const BoolVec& other)
{
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    mAllocator = other.mAllocator;
    const uint8_t* pSrc = other.mpBegin;
    const uint8_t* pEnd = other.mpEnd;
    uint32_t size = (uint32_t)(pEnd - pSrc);
    ReserveBuffer(size + 1);
    uint8_t* dst = mpBegin;
    VectorBool_DoInsertValue(dst, pSrc, size);
    mpEnd = dst + (pEnd - pSrc);
    *mpEnd = 0;
    return this;
}

// @ 0x00836910
void RawFixed::Assign(const void* first, const void* last)
{
    uint8_t* begin = mBegin;
    uint8_t* end = mEnd;
    uint32_t size = (uint32_t)((const uint8_t*)last - (const uint8_t*)first);
    if ((uint32_t)(end - begin) < size) {
        VectorBool_DoInsertValue(begin, first, (uint32_t)(end - begin));
        AppendRange((const uint8_t*)first + (mEnd - mBegin), last);
    } else {
        VectorBool_DoInsertValue(begin, first, size);
        uint8_t* newEnd = begin + size;
        if (newEnd != end) {
            memmove_1(newEnd, end, 1);
            mEnd += (int)(newEnd - end);
        }
    }
}

// @ 0x00836990
cDataURI::~cDataURI()
{}

// @ 0x008369e0
RawFixed* RawFixed::AssignCStr(const wchar_t* s)
{
    wchar_t* begin = (wchar_t*)mBegin;
    if (begin == s) return this;
    if (begin != (wchar_t*)mEnd) {
        *begin = 0;
        mEnd = mBegin;
    }
    AssignStr(s, s + CharStrlen(s));
    return this;
}

// @ 0x00836a30
RawFixed* RawFixed::SubstrInto(RawFixed* dst, uint32_t pos, uint32_t len)
{
    wchar_t* begin = (wchar_t*)mBegin;
    uint32_t size = (uint32_t)((wchar_t*)mEnd - begin);
    uint32_t avail = size - pos;
    uint32_t n = (avail < len) ? avail : len;
    wchar_t* d = (wchar_t*)dst;
    dst->mBuffer = (uint8_t*)(d + 10);
    dst->mCapacity = (uint8_t*)(d + 10 + 0x100);
    dst->mEnd = (uint8_t*)(d + 10);
    dst->mBegin = (uint8_t*)(d + 10);
    d[10] = 0;
    dst->AppendWide(begin + pos, begin + pos + n);
    return dst;
}

// @ 0x00836a90
void RawFixed::Swap(RawFixed& other)
{
    if (this + 3 == &other + 3) {
        uint8_t* t;
        t = mBegin; mBegin = other.mBegin; other.mBegin = t;
        t = mEnd; mEnd = other.mEnd; other.mEnd = t;
        t = mCapacity; mCapacity = other.mCapacity; other.mCapacity = t;
        return;
    }
    RawFixed tmp;
    tmp.Init(*this);
    if (&other != this) this->Assign((void*)other.mBegin, (void*)other.mEnd);
    if (&tmp != &other) other.Assign((void*)tmp.mBegin, (void*)tmp.mEnd);
    if (((tmp.mCapacity - tmp.mBegin) > 1) && tmp.mBegin && tmp.mBegin != tmp.mBuffer)
        operator_delete__((void*)tmp.mBegin);
}

// @ 0x00836d50
void cDataURI::init(const wchar_t* p)
{
    mbBase64 = false;
    mValue.Reset1024(0);
    mScheme.Reset32(0);
    mEncoding = 0;
    if (!p) return;

    FixedString<256> local;
    local.Construct256(p);

    wchar_t* begin = (wchar_t*)local.mBegin;
    wchar_t* end = (wchar_t*)local.mEnd;
    int size = (int)(end - begin);
    if (size == 0) return;

    wchar_t* colon = begin;
    while (colon != end) {
        if (*colon == L':') break;
        ++colon;
    }
    if (colon == end) return;

    int colonIdx = (int)(colon - begin);
    if (colonIdx == -1) return;
    unsigned prefixLen = (unsigned)(colonIdx + 1);
    if (wcsncmp(begin, g_dataPrefix, prefixLen) != 0) return;

    int comma = local.RFindCh(L',', -1);
    if (comma == -1) return;
    if ((unsigned)(comma + 2) >= (unsigned)size) return;

    begin[comma] = L';';
    unsigned mediaEnd = (unsigned)(comma + 1);

    {
        FixedString<256> temp;
        local.SubstrInto(&temp, mediaEnd, (unsigned)size - mediaEnd);
        mValue.AssignCStr((const wchar_t*)temp.mBegin);
    }

    for (unsigned pos = prefixLen; pos != mediaEnd; ) {
        unsigned semi = local.FindCh(L';', pos);
        if (wcsncmp(L"base64", begin + pos, semi - pos) == 0) {
            mbBase64 = true;
        } else {
            unsigned eq = local.FindCh(L'=', pos);
            if (eq == 0xffffffffu || semi <= eq) {
                unsigned slash = local.FindCh(L'/', pos);
                if (slash != 0xffffffffu && slash < semi) {
                    FixedString<256> temp;
                    local.SubstrInto(&temp, pos, semi - pos);
                    mScheme.AssignCStr((const wchar_t*)temp.mBegin);
                }
            } else {
                unsigned n = semi - (eq + 1);
                const wchar_t* value = begin + eq + 1;
                if (wcsncmp(value, L"utf-16", n) == 0) mEncoding = 0x10;
                else if (wcsncmp(value, L"utf-8", n) == 0) mEncoding = 8;
                else if (wcsncmp(value, L"ascii", n) == 0) mEncoding = 4;
                else if (wcsncmp(value, L"iso-8859-1", n) == 0) mEncoding = 0x6faf;
                else if (wcsncmp(value, L"unknown", n) == 0) mEncoding = 0;
                else { init(0); return; }
            }
        }
        pos = semi + 1;
    }
}

// @ 0x00837020
void RawFixed::Reserve(uint32_t n)
{
    if (n != 0xffffffffu && (uint32_t)(mEnd - mBegin) < n) {
        uint8_t* m = (uint8_t*)operator_new6(n, g_eastlTag, 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        uint32_t size = (uint32_t)(mEnd - mBegin);
        VectorBool_DoInsertValue(m, (void*)mBegin, size);
        m[size] = 0;
        uint8_t* old = mBegin;
        if ((((mCapacity - old) > 1) && old) && old != mBuffer) operator_delete__((void*)old);
        mBegin = m;
        mEnd = m + size;
        mCapacity = m + n;
        return;
    }
    if (n < (uint32_t)(mEnd - mBegin)) {
        Resize(n);
    }
    RawFixed tmp;
    tmp.Init(*this);
    Swap(tmp);
    if ((((tmp.mCapacity - tmp.mBegin) > 1) && tmp.mBegin) && tmp.mBegin != tmp.mBuffer)
        operator_delete__((void*)tmp.mBegin);
}

// @ 0x008371e0
cDataURI::cDataURI(const wchar_t* p)
{
    init(p);
}

// @ 0x00837230
void RawFixed::Reserve2(uint32_t n)
{
    uint32_t size = (uint32_t)(mEnd - mBegin);
    uint32_t need = max_alt(n, size) + 1;
    if (need > (uint32_t)(mCapacity - mBegin)) {
        Reserve(need);
    }
}

// @ 0x00837270
RawFixed* RawFixed::AppendN(uint32_t count, uint8_t ch)
{
    void* volatile self = this;
    uint32_t size = (uint32_t)(mEnd - mBegin);
    uint32_t cap = (uint32_t)(mCapacity - mBegin);
    uint32_t need = size + count;
    if (need > cap - 1) {
        uint32_t ncap = cap - 1;
        ncap = (ncap < 9) ? 8 : ncap * 2;
        uint32_t chosen = (ncap < need) ? need : ncap;
        uint32_t cap2 = (chosen < size) ? size : chosen;
        if (cap < cap2 + 1) {
            Reserve(cap2 + 1);
        }
    }
    if (count != 0) {
        uint8_t* dst = mEnd;
        memset(dst + 1, ch, count - 1);
        *dst = ch;
        mEnd = dst + count;
        *mEnd = 0;
    }
    self = this;
    return this;
}

// @ 0x00837310
void RawFixed::Resize(uint32_t n)
{
    uint8_t* src = mEnd;
    uint32_t size = (uint32_t)(src - mBegin);
    if (n < size) {
        uint8_t* dst = mBegin + n;
        if (dst != src) {
            memmove_1(dst, src, 1);
            mEnd = dst + (mEnd - src);
        }
    } else if (size < n) {
        AppendN(n - size, 0);
    }
}

// @ 0x00837360
EaString* __cdecl PackDataIntoURIString(EaString* out, const uint8_t* data, uint32_t len, const wchar_t* mime, int encoding, char base64)
{
    EaString uri;
    uri.mpBegin = (wchar_t*)g_emptyStr_s0083_6910;
    uri.mpEnd = (wchar_t*)g_emptyStr_s0083_6910;
    uri.mpCapacity = (wchar_t*)g_emptyStr_s0083_6910 + 1;

    if (!mime || !data || (int)len < 0) {
        out->mpBegin = 0;
        out->mpEnd = 0;
        out->mpCapacity = 0;
        out->AllocateSelf(1);
        EASTL_memmove(out->mpBegin, g_emptyStr_s0083_6910, 0);
        out->mpEnd = out->mpBegin;
        *out->mpBegin = 0;
        return out;
    }

    bool hasText = wcsstr(mime, L"text/") != 0;

    uri += L"data:";
    uri += mime;

    const wchar_t* charset = L"unknown";
    if (encoding < 9) {
        if (encoding == 8) charset = L"utf-8";
        else if (encoding == 0) charset = L"unknown";
        else if (encoding == 4) charset = L"ascii";
    } else if (encoding == 0x10) {
        charset = L"utf-16";
    } else if (encoding == 0x6faf) {
        charset = L"iso-8859-1";
    }

    if (hasText) {
        uri += L";charset=";
        uri += charset;
    }
    if (base64) uri += L";base64";
    uri.AppendChar(1, L',');

    const uint8_t* p = data;
    uint32_t n = len;

    CharStr b64;
    b64.mpBegin = g_emptyStr_s0083_6910;
    b64.mpEnd = g_emptyStr_s0083_6910;
    b64.mpCapacity = g_emptyStr_s0083_6910 + 1;

    if (base64) {
        CharStr bin;
        bin.mpCapacity = g_emptyStr_s0083_6910 + 1;
        bin.mpBegin = g_emptyStr_s0083_6910;
        bin.mpEnd = g_emptyStr_s0083_6910;
        bin.resize(len);
        EASTL_memmove(bin.mpBegin, data, len);
        EncodeBase64String(&bin, &b64);
        p = (const uint8_t*)b64.mpBegin;
        n = (uint32_t)(b64.mpEnd - b64.mpBegin);
    }

    const uint8_t* end = p + n;
    wchar_t temp[6];

    if (encoding == 0x10 && p == data && n == len) {
        const uint8_t* limit = p + (n & ~1u);
        for (; p < limit; p += 2) {
            uint16_t u = *(const uint16_t*)p;
            if (Unreserved((uint8_t)u)) {
                uri.AppendChar(1, (wchar_t)u);
            } else {
                temp[0] = L'%';
                temp[1] = HexDigit(u >> 12);
                temp[2] = HexDigit((u >> 8) & 0xf);
                temp[3] = L'%';
                temp[4] = HexDigit((u >> 4) & 0xf);
                temp[5] = HexDigit(u & 0xf);
                uri.AppendRange(temp, temp + 6);
            }
        }
    } else {
        for (; p < end; ++p) {
            uint8_t b = *p;
            if (Unreserved(b)) {
                uri.AppendChar(1, (wchar_t)(int8_t)b);
            } else {
                temp[0] = L'%';
                temp[1] = HexDigit(b >> 4);
                temp[2] = HexDigit(b & 0xf);
                uri.AppendRange(temp, temp + 3);
            }
        }
    }

    *out = uri;
    return out;
}

// @ 0x00837820
bool cDataURI_s0083_7820::GetStream(void** out)
{
    if (mValue.mpBegin == mValue.mpEnd) return false;

    WideString256 decoded;
    unsigned need = (unsigned)(mValue.mpEnd - mValue.mpBegin) + 1;
    if (need > 256) decoded.set_capacity(need);

    bool utf16 = (mEncoding == 0x10 && !mbBase64);
    const wchar_t* p = mValue.mpBegin;
    const wchar_t* end = mValue.mpEnd;
    while (p < end) {
        wchar_t ch = *p++;
        if (ch == L'%') {
            unsigned v;
            if (utf16) {
                v  = HexVal(p[0]) << 12; ++p;
                v |= HexVal(p[0]) << 8;  ++p;
                v |= HexVal(p[0]) << 4;  ++p;
                v |= HexVal(p[0]);       ++p;
            } else {
                v  = HexVal(p[0]) << 4;  ++p;
                v |= HexVal(p[0]);       ++p;
            }
            decoded.append(1, (wchar_t)v);
        } else {
            decoded.append(1, ch);
        }
    }

    MemoryStream* stream = 0;
    void* mem = operator_new6(0x24, (const void*)0x141b14c, 0, 0, 0, 0);
    if (mem) {
        stream = ((MemoryStream*)mem)->Construct(0, 0, (const char*)0x13ebacc);
        if (stream) stream->AddRef();
    }
    stream->SetOption(1, 1.0f);

    if (mbBase64) {
        CharString encoded;
        unsigned n = (unsigned)(decoded.mpEnd - decoded.mpBegin) + 1;
        if (n > 1) encoded.set_capacity(n);
        const wchar_t* q = decoded.mpBegin;
        const wchar_t* qe = decoded.mpEnd;
        while (q < qe) {
            char buf[0x40];
            int i = 0;
            while (q < qe && i < 0x40) {
                buf[i++] = (char)*q;
                ++q;
            }
            encoded.append(buf, buf + i);
        }
        CharString plain;
        if (!Base64DecodeString((int*)&encoded, (int*)&plain)) {
            if (stream) stream->Release();
            return false;
        }
        stream->Write(plain.mpBegin, (unsigned)(plain.mpEnd - plain.mpBegin));
    } else if (mEncoding == 0x10) {
        stream->Write(decoded.mpBegin, (unsigned)(decoded.mpEnd - decoded.mpBegin) * 2);
    } else {
        const wchar_t* q = decoded.mpBegin;
        const wchar_t* qe = decoded.mpEnd;
        while (q < qe) {
            char buf[0x40];
            int i = 0;
            while (q < qe && i < 0x40) {
                buf[i++] = (char)*q;
                ++q;
            }
            buf[i] = 0;
            stream->Write(buf, (unsigned)i);
        }
    }

    stream->v28(0, 0);
    *out = stream;
    stream->AddRef();
    stream->Release();
    return true;
}

// @ 0x00837c90
bool cSPUInHandler::ProcessRequest(ResourceRequest* req, int unused)
{
    (void)unused;
    if (!mProvider) return false;

    EStr uri;
    uri.Construct(req->mPath);
    if (uri.find(g_01548788, 0) == 0xffffffffu) {
        mProvider->FinishRequest(req, 3);
        return false;
    }

    cDataURI_s0083_7820 data(uri.mpBegin);
    void* stream = 0;
    if (!data.GetStream(&stream)) {
        if (stream) ((MemoryStream*)stream)->Release();
        mProvider->FinishRequest(req, 3);
        return false;
    }

    req->SetStream(stream);

    CharFixed32 mime;
    int n = (int)(data.mScheme.mpEnd - data.mScheme.mpBegin);
    mime.Reserve2((unsigned)n);
    for (int i = 0; i < n; ++i)
        mime.AppendN(1, (unsigned char)data.mScheme.mpBegin[i]);
    req->mMime.assign(mime.a, mime.a + strlen(mime.a));

    mProvider->FinishRequest(req, 2);
    if (stream) ((MemoryStream*)stream)->Release();
    return true;
}
