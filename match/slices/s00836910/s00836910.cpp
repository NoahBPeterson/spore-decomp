// Slice s00836910 (w2g7 #39), 32-bit MSVC 2008 SP1.
// anonymous-namespace cDataURI (data: URI parser) + fixed-buffer string helpers,
// and the XHTML utfres: handler that resolves a parsed URI to a record stream.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"
#include <string.h>

void* __cdecl operator_new6(uint32_t, const void*, int, int, const char*, int);
void  __cdecl operator_delete__(void*);                                    // 0x00f47380
void  __cdecl VectorBool_DoInsertValue(void*, const void*, uint32_t);
void  __cdecl memmove_1(void*, const void*, uint32_t);                     // 0x013cc480 msvcr90!memmove
void* __cdecl EASTL_memmove(void* dst, const void* src, unsigned int n);   // 0x011e0744
void  __cdecl BinaryAssign(void*, void*, uint32_t);                        // 0x00672750
void  __cdecl EncodeBase64String(const void* src, void* dst);              // 0x00941a10
extern char g_eastlTag[];                                                  // 0x013f6b3c

// global data used by the parsers (annotated so the verifier binds the real images)
extern "C" const wchar_t* g_utfresPrefix;    // 0x01548784  L"utfres:"
extern "C" int            g_utfresPrefixLen; // 0x0164f730  == 7
extern "C" const wchar_t* g_dataPrefix;      // 0x01548788  L"data:"
extern "C" char           g_emptyStr[];      // 0x01667bac  shared empty eastl string storage

// ---------------------------------------------------------------------------
// generic fixed-buffer string (3 pointers + allocator + SSO buffer ptr, then data)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// EA::WideFixedBuf<N> (SSO fixed buffer wide string)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// cDataURI
// ---------------------------------------------------------------------------
struct cDataURI {
    int mEncoding;              // +0x00
    FixedString<32> mScheme;    // +0x04
    FixedString<1024> mValue;   // +0x58
    bool mbBase64;              // +0x86c

    cDataURI(const wchar_t* p);
    ~cDataURI();
    void init(const wchar_t* p);
};

// @ 0x00836990
cDataURI::~cDataURI() {}

// @ 0x008371e0
cDataURI::cDataURI(const wchar_t* p) {
    init(p);
}

// @ 0x00836910  FixedString::Assign-from-range (DoInsertValue tail-shift)
void RawFixed::Assign(const void* first, const void* last) {
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

// @ 0x00836850  copy ctor helper
void RawFixed::Init(const RawFixed& other) {
    mBegin = 0; mEnd = 0; mCapacity = 0;
    mAllocator = other.mAllocator;
    uint32_t size = (uint32_t)(other.mEnd - other.mBegin);
    Reserve(size + 1);
    uint8_t* dst = mBegin;
    VectorBool_DoInsertValue(dst, (void*)other.mBegin, size);
    mEnd = dst + (other.mEnd - other.mBegin);
    *mEnd = 0;
}

// @ 0x00836a90
void RawFixed::Swap(RawFixed& other) {
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

static unsigned int CharStrlen(const wchar_t* p) {
    const wchar_t* e = p;
    while (*e) ++e;
    return (unsigned int)(e - p);
}

// @ 0x008369e0
RawFixed* RawFixed::AssignCStr(const wchar_t* s) {
    wchar_t* begin = (wchar_t*)mBegin;
    if (begin == s) return this;
    if (begin != (wchar_t*)mEnd) {
        *begin = 0;
        mEnd = mBegin;
    }
    AssignStr(s, s + CharStrlen(s));
    return this;
}

// @ 0x00836a30  substring into a 256 fixed string
RawFixed* RawFixed::SubstrInto(RawFixed* dst, uint32_t pos, uint32_t len) {
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

// @ 0x00837020
void RawFixed::Reserve(uint32_t n) {
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

// @ 0x00837230
template <typename T> static const T& max_alt(const T& a, const T& b) { return a < b ? b : a; }

void RawFixed::Reserve2(uint32_t n) {
    uint32_t size = (uint32_t)(mEnd - mBegin);
    uint32_t need = max_alt(n, size) + 1;
    if (need > (uint32_t)(mCapacity - mBegin)) {
        Reserve(need);
    }
}

// @ 0x00837270
RawFixed* RawFixed::AppendN(uint32_t count, uint8_t ch) {
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
void RawFixed::Resize(uint32_t n) {
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

// ---------------------------------------------------------------------------
// @ 0x00836d50  cDataURI::init - parse "data:<mime>[;attr...][,base64],<payload>"
// ---------------------------------------------------------------------------
void cDataURI::init(const wchar_t* p) {
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

// ---------------------------------------------------------------------------
// utfres: -> record stream dispatch
// ---------------------------------------------------------------------------
struct HashNode {
    uint32_t mKey;   // +0x00
    int      mValue; // +0x04
};

struct HandleTable {
    void*      mp00;         // +0x00
    HashNode** mppBuckets;   // +0x04
    uint32_t   mBucketCount; // +0x08

    void find(HashNode** out, const uint32_t* key);   // 0x00645ed0
};

struct ResourceKey {
    uint32_t mType;    // +0x00
    uint32_t mHandle;  // +0x04  resolved record handle (hashtable key)
    uint32_t mExtra;   // +0x08
};

struct ResourceRequest {
    char mPad00[0x0c];
    const wchar_t* mPath;               // +0x0c

    void SetProperty(int value);        // 0x00a355e0
    void SetStream(int stream);         // 0x00836480
};

struct ResourceProvider {
    void Dispatch(ResourceRequest* req, int code);   // 0x008ffb40
};

// The resource object returned by GetUTFResource(); Lookup lives at vtable +0x78.
struct UTFResource {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74();
    virtual bool Lookup(ResourceKey* key, const wchar_t* name, int a, int b);
};

struct cSPUIXHTMLUTFResourceHandler {
    void* mp00;                // +0x00
    void* mp04;                // +0x04
    ResourceProvider* mp08;    // +0x08
    HandleTable mTable;        // +0x0c

    bool ProcessRequest(ResourceRequest* req, int unused);
    int  ResolveHandle(const wchar_t* key);   // 0x00836740
};

UTFResource* __cdecl GetUTFResource();                              // 0x008de1a0
bool __cdecl ReadKey(const wchar_t* key, ResourceKey* out);        // 0x008de0c0
int  __cdecl OpenRecordAsStream(int type, ResourceKey* key, int* stream); // 0x00808660
void __cdecl CloseStream(int record);                              // 0x006861d0

// @ 0x00836bd0
bool cSPUIXHTMLUTFResourceHandler::ProcessRequest(ResourceRequest* req, int unused) {
    (void)unused;
    if (!mp08) return false;
    if (!GetUTFResource()) return false;

    FixedString<32> name;
    name.Construct32(req->mPath);
    name.MakeLower();

    ResourceKey key;
    key.mType = 0;
    key.mHandle = 0;
    key.mExtra = 0;

    unsigned found = name.FindStr(g_utfresPrefix, 0);
    const wchar_t* handleKey = (const wchar_t*)name.mBegin + g_utfresPrefixLen;

    UTFResource* res = GetUTFResource();
    bool ok = res->Lookup(&key, handleKey, 0, 0);
    if (!ok) ok = ReadKey(handleKey, &key);
    int resolved = ResolveHandle(handleKey);
    if (resolved) key.mHandle = (uint32_t)resolved;

    if (ok && found != 0xffffffffu) {
        HashNode* iter = 0;
        mTable.find(&iter, &key.mHandle);
        if (iter != mTable.mppBuckets[mTable.mBucketCount]) {
            req->SetProperty(iter->mValue);
            int stream = 0;
            int record = OpenRecordAsStream(1, &key, &stream);
            if (record != -1) {
                req->SetStream(stream);
                mp08->Dispatch(req, 2);
                CloseStream(record);
                return true;
            }
        }
    }
    mp08->Dispatch(req, 3);
    return false;
}

// ---------------------------------------------------------------------------
// data: URI construction
// ---------------------------------------------------------------------------
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

// @ 0x00837360
EaString* __cdecl PackDataIntoURIString(EaString* out, const uint8_t* data, uint32_t len,
                                        const wchar_t* mime, int encoding, char base64) {
    EaString uri;
    uri.mpBegin = (wchar_t*)g_emptyStr;
    uri.mpEnd = (wchar_t*)g_emptyStr;
    uri.mpCapacity = (wchar_t*)g_emptyStr + 1;

    if (!mime || !data || (int)len < 0) {
        out->mpBegin = 0;
        out->mpEnd = 0;
        out->mpCapacity = 0;
        out->AllocateSelf(1);
        EASTL_memmove(out->mpBegin, g_emptyStr, 0);
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
    b64.mpBegin = g_emptyStr;
    b64.mpEnd = g_emptyStr;
    b64.mpCapacity = g_emptyStr + 1;

    if (base64) {
        CharStr bin;
        bin.mpCapacity = g_emptyStr + 1;
        bin.mpBegin = g_emptyStr;
        bin.mpEnd = g_emptyStr;
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
