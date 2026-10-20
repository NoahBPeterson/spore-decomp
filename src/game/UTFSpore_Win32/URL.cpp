// src/game/UTFSpore_Win32/URL.cpp -- migrated from slice(s) s00949cc0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/URL.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Internet/URL.h"
#include "EA/Internet/INetFileCache.h"
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <ctype.h>
#include <wctype.h>

// ---- items of slice s00949cc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
char* __cdecl Sprintf8(char* buf, const char* fmt, ...);
namespace eastl {
struct allocator_s0094_9cc0 { int mAlloc; };
}
namespace eastl {
template <class T> struct EmptyString { static T s[8]; };
}
namespace eastl {
template <class T> T EmptyString<T>::s[8];
}
namespace eastl {
template <class T>
struct basic_string_s0094_9cc0 {
    T* mpBegin;                 // +0
    T* mpEnd;                   // +4
    T* mpCapacity;              // +8
    allocator_s0094_9cc0 mAllocator;       // +0xc

    basic_string_s0094_9cc0() {
        mpBegin = EmptyString<T>::s;
        mpEnd = mpBegin;
        mpCapacity = EmptyString<T>::s + 1;
    }
    basic_string_s0094_9cc0& operator=(const basic_string_s0094_9cc0& o) {
        if (&o != this) assign(o.mpBegin, o.mpEnd);
        return *this;
    }
    basic_string_s0094_9cc0& assign(const T* first, const T* last);
    basic_string_s0094_9cc0& append(const T* first, const T* last);
    basic_string_s0094_9cc0& erase(unsigned int pos, unsigned int n);
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
}
namespace eastl {
typedef basic_string_s0094_9cc0<char>    string;
}
namespace eastl {
bool operator==(const string& lhs, const char* rhs);
}
namespace eastl {
const char* search_char(const char* first, const char* last,
                        const char* pBegin, const char* pEnd);
}
using eastl::string;
namespace EA {
namespace Internet {
class URL_s0094_9cc0 {
public:
    bool   mbStrictConformance;      // +0x00
    int    mnMaxComponentLength;     // +0x04
    bool   mbParsed;                 // +0x08
    int    mURLType;                 // +0x0c
    string msURL;                    // +0x10
    string msComponent[9];           // +0x20

    URL_s0094_9cc0();
    URL_s0094_9cc0(const char* p);
    URL_s0094_9cc0& operator=(const URL_s0094_9cc0& o);

    void SetURL(const char* p, bool b);
    void SetComponent(int index, const char* p);
    void SetPort(unsigned int port);  // 0x0094a750 (EA::Internet::URL::SetPort)
    unsigned int GetPort();
    bool ParseUsernameAndPassword(string* pstr);  // 0x0094a9f0 (EA::Internet::URL::ParseUsernameAndPassword)
    bool ParseURLFILE(string* pstr);  // 0x0094aae0 (EA::Internet::URL::ParseURLFILE)
    static void CanonicalizePath(const char* pszPath, string* pstr);  // 0x0094a7a0 (EA::Internet::URL::CanonicalizePath)
};
}
}
namespace EA {
namespace Internet {
URL_s0094_9cc0::URL_s0094_9cc0()
    : mbStrictConformance(true), mnMaxComponentLength(0x80), mbParsed(false), mURLType(0) {
}
}
}
namespace EA {
namespace Internet {
URL_s0094_9cc0::URL_s0094_9cc0(const char* p)
    : mbStrictConformance(true), mnMaxComponentLength(0x80), mbParsed(false), mURLType(0) {
    if (p) msURL.assign(p, p + strlen(p));
}
}
}
namespace EA {
namespace Internet {
URL_s0094_9cc0& URL_s0094_9cc0::operator=(const URL_s0094_9cc0& o) {
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
}
}
// ---- items of slice s00949cc0 end

// @ 0x0094a6a0
namespace EA { namespace Internet {
void URL_s0094_9cc0::SetURL(const char* p, bool b)
{
    if (b) mbParsed = false;
    if (p != 0)
        msURL.assign(p, p + strlen(p));
    else
        msURL.clear();
}
}}  // namespace EA::Internet

// @ 0x0094a6f0
namespace EA { namespace Internet {
void URL_s0094_9cc0::SetComponent(int index, const char* p)
{
    if (p != 0)
        msComponent[index].assign(p, p + strlen(p));
    else
        msComponent[index].clear();
}
}}  // namespace EA::Internet

// @ 0x0094a750
void EA::Internet::URL::SetPort(unsigned int port)
{
    char buf[20];
    Sprintf8(buf, "%u", port);
    msComponent[4].assign(buf, buf + strlen(buf));
}

// @ 0x0094a7a0
namespace EA { namespace Internet {
void URL_s0094_9cc0::CanonicalizePath(const char* pszPath, string* pstr)
{
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
}}  // namespace EA::Internet

// @ 0x0094a9f0
namespace EA { namespace Internet {
bool URL_s0094_9cc0::ParseUsernameAndPassword(string* pstr)
{
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
}}  // namespace EA::Internet

// @ 0x0094aae0
namespace EA { namespace Internet {
bool URL_s0094_9cc0::ParseURLFILE(string* pstr)
{
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
}}  // namespace EA::Internet
