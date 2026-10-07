// Slice s00949cc0 - EA::Internet URL / MIME / INetFileCache helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- (no frame pointer, no GS cookie).
#include "types.h"
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <ctype.h>
#include <wctype.h>

// ---------------------------------------------------------------------------
// CRT / external helpers
// ---------------------------------------------------------------------------

void* __cdecl operator_delete__(void*);
char* __cdecl Sprintf8(char* buf, const char* fmt, ...);
void  __cdecl WString_Assign(void*, const wchar_t*, const wchar_t*);
bool  __cdecl CreateDirectoryPath(const wchar_t*);
bool  __cdecl Directory_Exists(const wchar_t*);
void  __cdecl GetDriveFreeSpace(wchar_t*);

// ---------------------------------------------------------------------------
// Minimal EASTL string (exact 16-byte layout)
// ---------------------------------------------------------------------------
namespace eastl {

struct allocator { int mAlloc; };

template <class T> struct EmptyString { static T s[8]; };
template <class T> T EmptyString<T>::s[8];

template <class T>
struct basic_string {
    T* mpBegin;                 // +0
    T* mpEnd;                   // +4
    T* mpCapacity;              // +8
    allocator mAllocator;       // +0xc

    basic_string() {
        mpBegin = EmptyString<T>::s;
        mpEnd = mpBegin;
        mpCapacity = EmptyString<T>::s + 1;
    }
    basic_string& operator=(const basic_string& o) {
        if (&o != this) assign(o.mpBegin, o.mpEnd);
        return *this;
    }
    basic_string& assign(const T* first, const T* last);
    basic_string& append(const T* first, const T* last);
    basic_string& erase(unsigned int pos, unsigned int n);
    unsigned int  find(const T* s, unsigned int pos) const;
    unsigned int  find(T c, unsigned int pos) const;
    unsigned int  rfind(T c, unsigned int pos) const;
    void clear() {
        if (mpBegin != mpEnd) { *mpBegin = 0; mpEnd = mpBegin; }
    }
    unsigned int length() const { return (unsigned int)(mpEnd - mpBegin); }
    const T* c_str() const { return mpBegin; }
    bool empty() const { return mpBegin == mpEnd; }
};

typedef basic_string<char>    string;
typedef basic_string<wchar_t> wstring;

bool operator==(const string& lhs, const char* rhs);
const char* search_char(const char* first, const char* last,
                        const char* pBegin, const char* pEnd);

} // namespace eastl

using eastl::string;
using eastl::wstring;

// ---------------------------------------------------------------------------
// EA::Internet::URL
// ---------------------------------------------------------------------------
namespace EA { namespace Internet {

class URL {
public:
    bool   mbStrictConformance;      // +0x00
    int    mnMaxComponentLength;     // +0x04
    bool   mbParsed;                 // +0x08
    int    mURLType;                 // +0x0c
    string msURL;                    // +0x10
    string msComponent[9];           // +0x20

    URL();
    URL(const char* p);
    URL& operator=(const URL& o);

    void SetURL(const char* p, bool b);
    void SetComponent(int index, const char* p);
    void SetPort(unsigned int port);
    unsigned int GetPort();
    bool ParseUsernameAndPassword(string* pstr);
    bool ParseURLFILE(string* pstr);
    static void CanonicalizePath(const char* pszPath, string* pstr);
};

URL::URL()
    : mbStrictConformance(true), mnMaxComponentLength(0x80), mbParsed(false), mURLType(0) {
}

URL::URL(const char* p)
    : mbStrictConformance(true), mnMaxComponentLength(0x80), mbParsed(false), mURLType(0) {
    if (p) msURL.assign(p, p + strlen(p));
}

URL& URL::operator=(const URL& o) {
    if (&o != this) {
        mbStrictConformance = o.mbStrictConformance;
        mnMaxComponentLength = o.mnMaxComponentLength;
        mbParsed = o.mbParsed;
        mURLType = o.mURLType;
        msURL = o.msURL;
        for (int i = 0; i < 9; ++i)
            msComponent[i] = o.msComponent[i];
    }
    return *this;
}

// @ 0x0094a6a0
void URL::SetURL(const char* p, bool b) {
    if (b) mbParsed = false;
    if (p != 0)
        msURL.assign(p, p + strlen(p));
    else
        msURL.clear();
}

// @ 0x0094a6f0
void URL::SetComponent(int index, const char* p) {
    if (p != 0)
        msComponent[index].assign(p, p + strlen(p));
    else
        msComponent[index].clear();
}

// @ 0x0094a750
void URL::SetPort(unsigned int port) {
    char buf[20];
    Sprintf8(buf, "%u", port);
    msComponent[4].assign(buf, buf + strlen(buf));
}

// @ 0x0094a4a0
unsigned int URL::GetPort() {
    return (unsigned int)strtoul(msComponent[4].c_str(), 0, 10);
}

} // namespace Internet
} // namespace EA

// Force emission of the unreferenced static member in this translation unit.
void (*g_urlCanonicalizePath)(const char*, eastl::string*) =
    &EA::Internet::URL::CanonicalizePath;

// ---------------------------------------------------------------------------
// EA::Internet::INetFileCache
// ---------------------------------------------------------------------------
namespace EA { namespace Internet {

class INetFileCache {
public:
    bool    mbInitialized;      // +0x00
    int     mRefCount;          // +0x04
    wstring msCacheDirectory;   // +0x08
    char    pad[0x58];          // to 0x64
    void ReadCacheIniFile();
    void RemoveUnusedCachedFiles();
    ~INetFileCache();
    bool Init();
    int  Release();
};

// @ 0x00949cc0
bool INetFileCache::Init() {
    bool bOk = true;
    if (!mbInitialized) {
        if (msCacheDirectory.length() == 0) {
            wchar_t buf[260];
            GetDriveFreeSpace(buf);
            const wchar_t* e = buf;
            while (*e) ++e;
            unsigned int n = (unsigned int)(e - buf);
            msCacheDirectory.assign(buf, buf + n);
            const wchar_t* lit = L"EA Network Cache\\";
            const wchar_t* le = lit;
            while (*le) ++le;
            unsigned int n2 = (unsigned int)(le - lit);
            msCacheDirectory.append(lit, lit + n2);
        }
        if (!Directory_Exists(msCacheDirectory.c_str()))
            bOk = CreateDirectoryPath(msCacheDirectory.c_str());
        ReadCacheIniFile();
        RemoveUnusedCachedFiles();
        mbInitialized = true;
    }
    return bOk;
}

// @ 0x00949d90
int INetFileCache::Release() {
    if (mRefCount > 1)
        return --mRefCount;
    this->~INetFileCache();
    operator_delete__(this);
    return 0;
}

} // namespace Internet
} // namespace EA

// ---------------------------------------------------------------------------
// MIME type hashing / tables
// ---------------------------------------------------------------------------
namespace {

// @ 0x00949dc0
unsigned int FNVHash8Lower(const char* p, const char* end) {
    unsigned int hash = 0x811c9dc5;
    unsigned char c = (unsigned char)*p;
    while (c != 0 && p != end) {
        hash = hash * 0x1000193 ^ (unsigned int)tolower(c);
        ++p;
        c = (unsigned char)*p;
    }
    return hash;
}

} // anonymous namespace

namespace EA { namespace Internet {

// @ 0x00949e10
int MIMETypeStringToMIMEType(const char* begin, bool b, int len) {
    unsigned int h = FNVHash8Lower(begin, begin + len);
    if (b) {
        switch (h) {
        case 0x9e7c75bf: return 2;
        case 0x527ffacd: return 4;
        case 0x2954e734: return 8;
        case 0x3fc40859: return 6;
        case 0x9e0b246c: return 5;
        case 0xb12bfa38: return 1;
        case 0xb1cc1af6: return 7;
        case 0xdbfffa2a: return 3;
        default: break;
        }
        return 0;
    }
    switch (h) {
        case 0x5b865ed7: return 0x1d;
        case 0x37ff7999: return 0x1e;
        case 0x1e639c34: return 0x10;
        case 0x14f8d92a: return 0x43;
        case 0x0dd5cf93: return 9;
        case 0x0e3280e9: return 0xf;
        case 0x0f9793fe: return 0xe;
        case 0x1a8ce475: return 0x35;
        case 0x1c099b80: return 0x1a;
        case 0x2c978db6: return 0x12;
        case 0x2550ebdc: return 0x1f;
        case 0x2b72bb3f: return 0x11;
        case 0x2ce51530: return 0xd;
        case 0x35943f2c: return 0x22;
        case 0x465dcb52: return 0x33;
        case 0x390d80e9: return 0x24;
        case 0x386cbfc3: return 0x36;
        case 0x3872cfb2: return 0x39;
        case 0x38f65389: return 0x1c;
        case 0x3caa495a: return 0x31;
        case 0x41775b4e: return 0x38;
        case 0x52c9da9e: return 0x15;
        case 0x477764fd: return 0x2b;
        case 0x4a0b828e: return 0x1b;
        case 0x575d15bd: return 0x19;
        case 0x5831000d: return 0x30;
        case 0x7cf2ac0e: return 10;
        case 0x604d8fc8: return 0x17;
        case 0xbac63b5a: return 0x14;
        case 0x9ec736df: return 0x42;
        case 0x883807a2: return 0x40;
        case 0x7db6b69b: return 0x27;
        case 0x80ffa9f7: return 0xb;
        case 0x88d95348: return 0x18;
        case 0x9dd66363: return 0x2a;
        case 0xae6c4306: return 0x4a;
        case 0xa736778c: return 0x37;
        case 0xac75ecec: return 0x20;
        case 0xaf4060dc: return 0x29;
        case 0xb4829beb: return 0x28;
        case 0xdca43ae7: return 0x32;
        case 0xc718e10d: return 0x3e;
        case 0xbd85000a: return 0x2c;
        case 0xc6620ff5: return 0x23;
        case 0xcb0e0d45: return 0x16;
        case 0xdb3cc501: return 0x21;
        case 0xe88db35f: return 0x34;
        case 0xdd6233d6: return 0xc;
        case 0xe480a535: return 0x44;
        case 0xe919578e: return 0x49;
        case 0xfc19f3e8: return 0x13;
        default: break;
        }
    return 0;
}

// @ 0x0094a1b0
int MIMETypesToFileExtension(int type, int sub, wchar_t* out, unsigned int outLen) {
    const wchar_t* ext = 0;
    switch (type) {
    case 1:
        switch (sub) {
        case 9: ext = L".txt"; break;
        case 0xc: case 0xd: case 0x10: ext = L".html"; break;
        case 0x11: ext = L".rtf"; break;
        case 0x12: ext = L".css"; break;
        case 0x13: ext = L".js"; break;
        default: return 0;
        }
        break;
    case 4:
        switch (sub) {
        case 0x26: ext = L".bin"; break;
        case 0x28: ext = L".xls"; break;
        case 0x29: ext = L".doc"; break;
        case 0x2b: ext = L".pdf"; break;
        case 0x30: ext = L".tar"; break;
        case 0x32: ext = L".exe"; break;
        case 0x33: ext = L".zip"; break;
        default: return 0;
        }
        break;
    case 5:
        switch (sub) {
        case 0x34: ext = L".jpeg"; break;
        case 0x35: ext = L".gif"; break;
        case 0x36: ext = L".tga"; break;
        case 0x37: ext = L".tiff"; break;
        case 0x38: ext = L".png"; break;
        case 0x3d: ext = L".bmp"; break;
        default: return 0;
        }
        break;
    case 6:
        if (sub != 0x40) return 0;
        ext = L".wav";
        break;
    case 7:
        switch (sub) {
        case 0x42: ext = L".mpg"; break;
        case 0x43: ext = L".qts"; break;
        case 0x44: ext = L".avi"; break;
        case 0x48: ext = L".tgq"; break;
        default: return 0;
        }
        break;
    default:
        return 0;
    }
    if (outLen > 0) {
        wcsncpy(out, ext, outLen);
        out[outLen - 1] = 0;
    }
    return (int)wcslen(ext);
}

// @ 0x0094a3f0
int MIMEStringToMIMETypes(const char* str, int* pType, int* pSubType, int len) {
    const char* p = str;
    const char* end = (len == -1) ? str - 1 : str + len;
    *pSubType = 0;
    *pType = 0;
    while (p < end) {
        if (*p == 0)
            break;
        if (*p == '/')
            goto found;
        ++p;
    }
    {
        int t = MIMETypeStringToMIMEType(str, true, (int)(p - str));
        *pType = t;
        if (t != 0) {
            if (*pSubType != 0)
                return 1;
        }
        return 0;
    }
found:
    {
        *pType = MIMETypeStringToMIMEType(str, true, (int)(p - str));
        ++p;
        const char* q = p;
        while (q < end) {
            if (*q == 0)
                break;
            ++q;
        }
        int sub = MIMETypeStringToMIMEType(p, false, (int)(q - p));
        *pSubType = sub;
        if (*pType != 0) {
            if (sub != 0)
                return 1;
        }
        return 0;
    }
}

// @ 0x0094a7a0
void URL::CanonicalizePath(const char* pszPath, string* pstr) {
    if (pstr->mpBegin != pszPath)
        pstr->assign(pszPath, pszPath + strlen(pszPath));

    if (pstr->length() >= 1) {
        unsigned int pos = 0;
        for (;;) {
            const char* begin = pstr->mpBegin;
            const char* end = pstr->mpEnd;
            unsigned int len = (unsigned int)(end - begin);
            unsigned int idx;
            if (pos + 2 > len) {
                idx = 0xffffffff;
            } else {
                const char* found = (const char*)eastl::search_char(
                    begin + pos, end, "./", "./" + 2);
                idx = (found == end) ? 0xffffffff : (unsigned int)(found - begin);
            }
            if (idx >= len)
                break;
            pos = idx + 1;
            if (idx != 0 && begin[idx - 1] == '.')
                continue;
            unsigned int remaining = len - idx;
            unsigned int n = (remaining < 2) ? remaining : 2;
            const char* dst = begin + idx;
            const char* src = begin + idx + n;
            if (dst != src) {
                memmove((void*)dst, src, (unsigned int)(end - src) + 1);
                pstr->mpEnd = (char*)(pstr->mpEnd + (dst - src));
            }
        }
    }

    {
        const char* end = pstr->mpEnd;
        unsigned int len = (unsigned int)(end - pstr->mpBegin);
        if (len >= 1 && end[-1] == '.' && (len == 1 || end[-2] == '/'))
            pstr->erase(len - 1, 1);
    }

    {
        const char* begin = pstr->mpBegin;
        const char* end = pstr->mpEnd;
        unsigned int len = (unsigned int)(end - begin);
        if (len >= 4) {
            if (len >= 2)
                iswctype((unsigned short)begin[0], 0x103);
            for (;;) {
                begin = pstr->mpBegin;
                end = pstr->mpEnd;
                unsigned int l = (unsigned int)(end - begin);
                unsigned int idx;
                if (l < 4) {
                    idx = 0xffffffff;
                } else {
                    const char* found = (const char*)eastl::search_char(
                        begin, end, "/../", "/../" + 4);
                    idx = (found == end) ? 0xffffffff : (unsigned int)(found - begin);
                }
                if (idx >= l)
                    break;
                if (idx == 0) {
                    unsigned int remaining = l;
                    unsigned int n = (remaining < 3) ? remaining : 3;
                    const char* dst = begin;
                    const char* src = begin + n;
                    if (dst != src) {
                        memmove((void*)dst, src, (unsigned int)(end - src) + 1);
                        pstr->mpEnd = (char*)(pstr->mpEnd + (dst - src));
                    }
                } else {
                    unsigned int start = idx - 1;
                    while (start != 0xffffffff && begin[start] != '/')
                        --start;
                    ++start;
                    unsigned int remaining = l - start;
                    unsigned int n2 = (idx - start) + 4;
                    unsigned int n = (remaining < n2) ? remaining : n2;
                    const char* dst = begin + start;
                    const char* src = begin + start + n;
                    if (dst != src) {
                        memmove((void*)dst, src, (unsigned int)(end - src) + 1);
                        pstr->mpEnd = (char*)(pstr->mpEnd + (dst - src));
                    }
                }
            }
        }
    }

    {
        const char* begin = pstr->mpBegin;
        unsigned int len = (unsigned int)(pstr->mpEnd - begin);
        if (len >= 4) {
            unsigned int last = len - 3;
            if (pstr->rfind('/', 0xffffffff) == last && begin[last + 1] == '.'
                && begin[last + 2] == '.') {
                unsigned int i = last - 1;
                while (i != 0xffffffff && begin[i] != '/')
                    --i;
                pstr->erase(i + 1, (last - (i + 1)) + 3);
            }
        }
    }
}

// @ 0x0094a9f0
bool URL::ParseUsernameAndPassword(string* pstr) {
    msComponent[1].clear();
    msComponent[2].clear();
    if (pstr->find("//", 0) != 0)
        return true;
    unsigned int len = pstr->length();
    const char* begin = pstr->mpBegin;
    const char* end = pstr->mpEnd;
    unsigned int at = 0xffffffff;
    if (len != 0) {
        const char* p = begin;
        if (p != end) {
            do {
                if (*p == '@')
                    break;
                ++p;
            } while (p != end);
            if (p != end)
                at = (unsigned int)(p - begin);
        }
    }
    if (at >= len)
        return true;
    msComponent[1].assign(begin, begin + at);
    pstr->erase(0, at + 1);
    unsigned int colon = msComponent[1].find(':', 0);
    if (colon >= msComponent[1].length())
        return true;
    msComponent[2].assign(msComponent[1].mpBegin + colon + 1, msComponent[1].mpEnd);
    msComponent[1].erase(colon, msComponent[1].length() - colon);
    return true;
}

// @ 0x0094aae0
bool URL::ParseURLFILE(string* pstr) {
    if (msComponent[3] == "localhost")
        msComponent[3].clear();
    if (pstr->length() >= 3 && pstr->mpBegin[0] == '/' && iswctype(pstr->mpBegin[1], 0x103)
        && pstr->mpBegin[2] == ':')
        pstr->erase(0, 1);
    else if (pstr->mpBegin[1] == '\\' && pstr->mpBegin[2] == '\\')
        pstr->erase(0, 1);
    msComponent[6].clear();
    msComponent[7].clear();
    msComponent[8].clear();
    msComponent[5] = *pstr;
    pstr->clear();
    return true;
}

} // namespace Internet
} // namespace EA
