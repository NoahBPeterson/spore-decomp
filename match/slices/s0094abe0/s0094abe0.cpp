// Slice s0094abe0: EA::Internet::URL parsing helpers (MSVC 2008 SP1, /O2 /MD /Gy /TP /GS-).
//
//   0094abe0  URL::ParseURLMailTo
//   0094ac90  URL::ParseURLUnknown
//   0094acc0  eastl::basic_string<char>::assign(size_type, value_type)
//   0094ad40  URL::ParseScheme
//   0094b050  URL::ParseServerAndPort
//   0094b2a0  URL::ParseURLHTTP
//   0094b510  URL::ParseURLFTP
//   0094b610  URL::ConvertPathToEncodedForm
//   0094b760  URL::ParseURL                 (unnamed in retail; PDB caller-single candidate)
//   0094b8e0  URL::MakeURLStringFromComponents (unnamed in retail)
//   0094ba30  URL::IsURLRelative(char const *)  (unnamed in retail)
//   0094baa0  URL::GetURLType               (unnamed in retail)
//   0094baf0  URL::GetPart                 (unnamed in retail)
//
// All belong to UTFSpore_Win32/HTTPClient.obj.  The URL layout is the retail one: the nine
// msComponent strings sit at +0x20 with a 0x10 stride (GetPart(i) == (i + 2) * 0x10 + this).
#include "types.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

extern "C" void* __cdecl operator_delete__(void* p) throw();

// eastl::basic_string<char> helpers (declared only: the originals live in the image).
struct Str {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    char* mpLink;       // +0x0c

    void CopyFrom(const Str& o);                                // 0x0057cb10

    unsigned int find(const char* s, unsigned int pos) const;   // 0x00841d00
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    void assign(const char* first, const char* last);           // 0x00454cb0
    Str& assign(int n, char c);                                 // 0x0094acc0 (defined here)
    void erase(unsigned int pos, unsigned int n);               // 0x0061e200
    void push_back(char c);                                     // 0x005306c0
    void append(const char* first, const char* last);           // 0x00455d60
    void resize(int n, char c);                                 // 0x0047bf30
};

// PackStr: only its Insert is used, via the string's own address as `this`.
struct PackStr { void Insert(char* p, const char* a, const char* b); };   // 0x0068c9e0

struct URL {
    bool mbStrictConformance;      // +0x00
    int  mnMaxComponentLength;     // +0x04
    bool mbParsed;                 // +0x08
    int  mURLType;                 // +0x0c
    Str  msURL;                    // +0x10
    Str  msComponent[9];           // +0x20

    URL(const char* s);                        // 0x0094a560
    void Fn60a100();                           // 0x0060a100 (dtor)

    bool ParseURLMailTo(Str& s);       // 0x0094abe0
    bool ParseURLUnknown(Str& s);      // 0x0094ac90
    bool ParseScheme(Str& s);          // 0x0094ad40
    bool ParseServerAndPort(Str& s);   // 0x0094b050
    bool ParseURLHTTP(Str& s);         // 0x0094b2a0
    bool ParseURLFTP(Str& s);          // 0x0094b510
    bool Fn94b760(Str& s);             // 0x0094b760
    bool Fn94b8e0();                   // 0x0094b8e0
    int  Fn94baa0();                   // 0x0094baa0
    Str* GetPart(int i);               // 0x0094baf0
    bool ParseUsernameAndPassword(Str& s);   // 0x0094a9f0
    bool ParseURLFILE(Str& s);               // 0x0094aae0

    static bool IsURLRelative(const char* url);                     // 0x0094ba30
    static bool ConvertPathToEncodedForm(const char* path, Str& out, const char* extra); // 0x0094b610
};

enum { kScheme = 0, kUser = 1, kPassword = 2, kServer = 3, kPort = 4, kPath = 5, kParms = 6, kQuery = 7, kFrag = 8 };
enum {
    kURLTypeUndefined = 0, kURLTypeUnknown = 1, kURLTypeHTTP = 2, kURLTypeHTTPS = 3,
    kURLTypeFile = 4, kURLTypeFTP = 5, kURLTypeMailTo = 6, kURLTypeRelative = 7
};

static __forceinline void StrClear(Str* s) {
    if (s->mpBegin != s->mpEnd) {
        *s->mpBegin = 0;
        s->mpEnd = s->mpBegin;
    }
}

// eastl::operator==<char>(basic_string const&, char const*) -> bool  (0x00555020)
static bool StrEquals(const Str* s, const char* c) {
    const char* p = s->mpBegin;
    while (p != s->mpEnd && *c && *p == *c) { ++p; ++c; }
    return p == s->mpEnd && *c == 0;
}

// eastl::basic_string<char>::find(char, pos): the original inlines this single-char scan.
static unsigned int FindChar(const Str* s, char ch) {
    const char* p = s->mpBegin;
    const char* e = s->mpEnd;
    while (p != e) {
        if (*p == ch) return (unsigned int)(p - s->mpBegin);
        ++p;
    }
    return 0xffffffffu;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0094abe0  URL::ParseURLMailTo
// ---------------------------------------------------------------------------------------------
bool URL::ParseURLMailTo(Str& param) {
    Str* p5 = &msComponent[kPath];
    if (p5->mpBegin != p5->mpEnd) {
        *p5->mpBegin = 0;
        p5->mpEnd = p5->mpBegin;
    }
    if (msComponent[kParms].mpBegin != msComponent[kParms].mpEnd) {
        *msComponent[kParms].mpBegin = 0;
        msComponent[kParms].mpEnd = msComponent[kParms].mpBegin;
    }
    if (msComponent[kQuery].mpBegin != msComponent[kQuery].mpEnd) {
        *msComponent[kQuery].mpBegin = 0;
        msComponent[kQuery].mpEnd = msComponent[kQuery].mpBegin;
    }
    if (msComponent[kFrag].mpBegin != msComponent[kFrag].mpEnd) {
        *msComponent[kFrag].mpBegin = 0;
        msComponent[kFrag].mpEnd = msComponent[kFrag].mpBegin;
    }
    if (&param != p5)
        p5->assign(param.mpBegin, param.mpEnd);
    if (param.mpBegin != param.mpEnd) {
        *param.mpBegin = 0;
        param.mpEnd = param.mpBegin;
    }
    return (int)(p5->mpEnd - p5->mpBegin) != 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0094ac90  URL::ParseURLUnknown
// ---------------------------------------------------------------------------------------------
bool URL::ParseURLUnknown(Str& param) {
    Str* p5 = &msComponent[kPath];
    if (&param != p5)
        p5->assign(param.mpBegin, param.mpEnd);
    if (param.mpBegin != param.mpEnd) {
        *param.mpBegin = 0;
        param.mpEnd = param.mpBegin;
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0094acc0  eastl::basic_string<char>::assign(size_type, value_type)
// ---------------------------------------------------------------------------------------------
Str& Str::assign(int n, char c) {
    unsigned int sz = (unsigned int)(mpEnd - mpBegin);
    if ((unsigned int)n <= sz) {
        memset(mpBegin, (int)c, n);
        char* end = mpEnd;
        char* dst = mpBegin + n;
        if (dst != end) {
            memmove(dst, end, (unsigned int)(mpEnd - end) + 1);
            mpEnd = mpEnd + (dst - end);
        }
        return *this;
    }
    memset(mpBegin, (int)c, (unsigned int)(mpEnd - mpBegin));
    resize((int)(mpBegin - mpEnd) + n, c);
    return *this;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0094ad40  URL::ParseScheme
// ---------------------------------------------------------------------------------------------
bool URL::ParseScheme(Str& param) {
    Str* c0 = &msComponent[kScheme];
    mURLType = kURLTypeUndefined;
    if (c0->mpBegin != c0->mpEnd) {
        *c0->mpBegin = 0;
        c0->mpEnd = c0->mpBegin;
    }

    if (param.find("URL:", 0) == 0 || param.find("url:", 0) == 0) {
        unsigned int sz = (unsigned int)(param.mpEnd - param.mpBegin);
        unsigned int k = sz < 4 ? sz : 4;
        param.erase(0, k);
    }

    if (param.find("mailto:", 0) == 0) {
        c0->assign(param.mpBegin, param.mpBegin + 6);
        param.erase(0, 7);
        return true;
    }

    unsigned int u = param.find("://", 0);
    if (u < (unsigned int)(param.mpEnd - param.mpBegin)) {
        for (unsigned int i = 0; i < u; ++i)
            c0->push_back((char)tolower((unsigned char)param.mpBegin[i]));
        unsigned int sz = (unsigned int)(param.mpEnd - param.mpBegin);
        unsigned int k = sz < u + 1 ? sz : u + 1;
        param.erase(0, k);
    }

    if (c0->mpEnd != c0->mpBegin) {
        if (StrEquals(c0, "http")) mURLType = kURLTypeHTTP;
        else if (StrEquals(c0, "https")) mURLType = kURLTypeHTTPS;
        else if (StrEquals(c0, "file")) mURLType = kURLTypeFile;
        else if (StrEquals(c0, "ftp")) mURLType = kURLTypeFTP;
        else if (StrEquals(c0, "mailto")) mURLType = kURLTypeMailTo;
    }
    if (mURLType != kURLTypeUndefined)
        return true;

    if (!mbStrictConformance) {
        if (param.find("www.", 0) == 0) mURLType = kURLTypeHTTP;
        else if (param.find("ftp.", 0) == 0) mURLType = kURLTypeFTP;
        ((PackStr*)&param)->Insert(param.mpBegin, "//", "");
        return true;
    }

    mURLType = kURLTypeRelative;
    {
        unsigned int sz = (unsigned int)(param.mpEnd - param.mpBegin);
        unsigned int uc = FindChar(&param, ':');
        if (uc >= sz)
            return true;
        if (uc < 1)
            return true;
        int i = (int)uc - 1;
        if (i != -1) {
            for (;;) {
                unsigned char ch = (unsigned char)param.mpBegin[i];
                if (ch > 0x7f)
                    break;
                char c = (char)ch;
                if (iswctype((wint_t)(unsigned char)c, 0x107) || c == '+' || c == '.' || c == '-') {
                    if (--i == -1)
                        break;
                    continue;
                }
                break;
            }
            if (i != -1)
                return true;
        }
        mURLType = kURLTypeUnknown;
        msURL.assign(param.mpBegin, param.mpBegin + uc);
        param.erase(0, uc + 1);
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0094b050  URL::ParseServerAndPort
// ---------------------------------------------------------------------------------------------
bool URL::ParseServerAndPort(Str& param) {
    Str* c3 = &msComponent[kServer];
    Str* c4 = &msComponent[kPort];
    if (c3->mpBegin != c3->mpEnd) { *c3->mpBegin = 0; c3->mpEnd = c3->mpBegin; }
    if (c4->mpBegin != c4->mpEnd) { *c4->mpBegin = 0; c4->mpEnd = c4->mpBegin; }

    if (param.find("//", 0) == 0) {
        param.erase(0, 2);
        unsigned int sz = (unsigned int)(param.mpEnd - param.mpBegin);
        if (mURLType == kURLTypeFile)
            return true;
        unsigned int colon = FindChar(&param, ':');
        unsigned int slash = FindChar(&param, '/');
        if (colon < slash && colon < sz) {
            unsigned int i = colon + 1;
            unsigned int n = 0;
            while (i < sz) {
                char c = param.mpBegin[i];
                if (c > 0x7f) break;   // (c >= 0x80 sign-extends negative; original breaks)
                if (!iswctype((wint_t)(unsigned char)c, 4)) break;
                c4->push_back(param.mpBegin[i]);
                ++i; ++n;
            }
            c3->assign(param.mpBegin, param.mpBegin + colon);
            param.erase(0, colon + n + 1);
            return true;
        }
        if (slash < sz) {
            c3->assign(param.mpBegin, param.mpBegin + slash);
            param.erase(0, slash);
            return true;
        }
        if (mURLType == kURLTypeHTTP || mURLType == kURLTypeHTTPS) {
            unsigned int semi = FindChar(&param, ';');
            if (semi < sz) {
                c3->assign(param.mpBegin, param.mpBegin + semi);
                param.erase(0, semi);
            }
            if (c3->mpEnd == c3->mpBegin) {
                unsigned int q = FindChar(&param, '?');
                if (q < (unsigned int)(param.mpEnd - param.mpBegin)) {
                    c3->assign(param.mpBegin, param.mpBegin + q);
                    param.erase(0, q);
                }
            }
            if (c3->mpEnd == c3->mpBegin) {
                unsigned int h = FindChar(&param, '#');
                if (h < (unsigned int)(param.mpEnd - param.mpBegin)) {
                    c3->assign(param.mpBegin, param.mpBegin + h);
                    param.erase(0, h);
                }
            }
        }
        if (c3->mpEnd == c3->mpBegin) {
            c3->assign(param.mpBegin, param.mpEnd);
            if (param.mpBegin != param.mpEnd) { *param.mpBegin = 0; param.mpEnd = param.mpBegin; }
        }
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0094b2a0  URL::ParseURLHTTP
// ---------------------------------------------------------------------------------------------
bool URL::ParseURLHTTP(Str& param) {
    Str* c5 = &msComponent[kPath];
    if (c5->mpBegin != c5->mpEnd) { *c5->mpBegin = 0; c5->mpEnd = c5->mpBegin; }
    if (msComponent[kParms].mpBegin != msComponent[kParms].mpEnd) { *msComponent[kParms].mpBegin = 0; msComponent[kParms].mpEnd = msComponent[kParms].mpBegin; }
    if (msComponent[kQuery].mpBegin != msComponent[kQuery].mpEnd) { *msComponent[kQuery].mpBegin = 0; msComponent[kQuery].mpEnd = msComponent[kQuery].mpBegin; }
    if (msComponent[kFrag].mpBegin != msComponent[kFrag].mpEnd) { *msComponent[kFrag].mpBegin = 0; msComponent[kFrag].mpEnd = msComponent[kFrag].mpBegin; }

    if (param.mpBegin == param.mpEnd) {
        if (mURLType != kURLTypeRelative)
            c5->assign(1, '/');
        goto done;
    }
    {
        unsigned int sz = (unsigned int)(param.mpEnd - param.mpBegin);
        unsigned int semi = FindChar(&param, ';');
        unsigned int q = FindChar(&param, '?');
        unsigned int h = FindChar(&param, '#');
        if (semi < sz && semi < q && semi < h) {
            unsigned int e = q < sz ? q : sz;
            if (h < e) e = h;
            if (c5->mpEnd == c5->mpBegin)
                c5->assign(param.mpBegin, param.mpBegin + semi);
            msComponent[kParms].assign(param.mpBegin + semi, param.mpBegin + e);
            param.erase(0, e);
        }
    }
    {
        unsigned int sz = (unsigned int)(param.mpEnd - param.mpBegin);
        unsigned int q = FindChar(&param, '?');
        unsigned int h = FindChar(&param, '#');
        if (q < sz && q < h) {
            unsigned int e = h < sz ? h : sz;
            if (c5->mpEnd == c5->mpBegin)
                c5->assign(param.mpBegin, param.mpBegin + q);
            msComponent[kQuery].assign(param.mpBegin + q, param.mpBegin + e);
            param.erase(0, e);
        }
    }
    {
        unsigned int sz = (unsigned int)(param.mpEnd - param.mpBegin);
        unsigned int h = FindChar(&param, '#');
        if (h < sz) {
            if (c5->mpEnd == c5->mpBegin)
                c5->assign(param.mpBegin, param.mpBegin + h);
            msComponent[kFrag].assign(param.mpBegin + h, param.mpEnd);
            if (param.mpBegin != param.mpEnd) { *param.mpBegin = 0; param.mpEnd = param.mpBegin; }
        }
    }
    if (c5->mpEnd == c5->mpBegin && &param != c5)
        c5->assign(param.mpBegin, param.mpEnd);
done:
    if (param.mpBegin != param.mpEnd) { *param.mpBegin = 0; param.mpEnd = param.mpBegin; }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0094b510  URL::ParseURLFTP
// ---------------------------------------------------------------------------------------------
bool URL::ParseURLFTP(Str& param) {
    Str* c5 = &msComponent[kPath];
    Str* c6 = &msComponent[kParms];
    if (c5->mpBegin != c5->mpEnd) { *c5->mpBegin = 0; c5->mpEnd = c5->mpBegin; }
    if (c6->mpBegin != c6->mpEnd) { *c6->mpBegin = 0; c6->mpEnd = c6->mpBegin; }
    if (msComponent[kQuery].mpBegin != msComponent[kQuery].mpEnd) { *msComponent[kQuery].mpBegin = 0; msComponent[kQuery].mpEnd = msComponent[kQuery].mpBegin; }
    if (msComponent[kFrag].mpBegin != msComponent[kFrag].mpEnd) { *msComponent[kFrag].mpBegin = 0; msComponent[kFrag].mpEnd = msComponent[kFrag].mpBegin; }

    if (param.mpBegin == param.mpEnd) {
        param.assign(1, '/');
        goto done;
    }
    {
        unsigned int sz = (unsigned int)(param.mpEnd - param.mpBegin);
        unsigned int semi = FindChar(&param, ';');
        if (semi < sz) {
            c5->assign(param.mpBegin, param.mpBegin + semi);
            c6->assign(param.mpBegin + semi, param.mpEnd);
        } else if (&param != c5) {
            c5->assign(param.mpBegin, param.mpEnd);
        }
    }
done:
    if (param.mpBegin != param.mpEnd) { *param.mpBegin = 0; param.mpEnd = param.mpBegin; }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0094b610  URL::ConvertPathToEncodedForm
// ---------------------------------------------------------------------------------------------
bool URL::ConvertPathToEncodedForm(const char* path, Str& out, const char* extra) {
    Str local;
    local.mpBegin = (char*)0x01667bac;
    local.mpEnd = (char*)0x01667bac;
    local.mpCapacity = (char*)0x01667bad;
    if (path >= out.mpBegin && path <= out.mpEnd) {
        local.assign(path, path + strlen(path));
        path = local.mpBegin;
    }
    StrClear(&out);
    unsigned int len = (unsigned int)strlen(path);
    for (unsigned int i = 0; i < len; ++i) {
        unsigned char b = (unsigned char)path[i];
        if (b < 0x80 && iswctype((wint_t)b, 0x107)) {
            out.push_back(path[i]);
            continue;
        }
        int v = (int)(signed char)path[i];
        if (strchr("$-_.+!*(),", v) || (extra && strchr(extra, v))) {
            out.push_back(path[i]);
            continue;
        }
        out.push_back('%');
        int hi = (v >> 4) & 0xf;
        hi += 0x30;
        if (hi > 0x39) hi += 7;
        out.push_back((char)hi);
        int lo = (v & 0xf) + 0x30;
        if (lo > 0x39) lo += 7;
        out.push_back((char)lo);
    }
    if (local.mpCapacity - local.mpBegin > 1 && local.mpBegin)
        operator_delete__(local.mpBegin);
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0094b760  URL::ParseURL
// ---------------------------------------------------------------------------------------------
bool URL::Fn94b760(Str& param) {
    bool result = false;
    mURLType = kURLTypeUndefined;
    StrClear(&msComponent[kScheme]);
    StrClear(&msComponent[kUser]);
    StrClear(&msComponent[kPassword]);
    StrClear(&msComponent[kServer]);
    StrClear(&msComponent[kPath]);
    StrClear(&msComponent[kParms]);
    StrClear(&msComponent[kQuery]);
    StrClear(&msComponent[kFrag]);
    StrClear(&msComponent[kPort]);

    ParseScheme(param);
    int t = mURLType;
    if (t == kURLTypeHTTP || t == kURLTypeHTTPS) {
        ParseUsernameAndPassword(param);
        ParseServerAndPort(param);
        result = ParseURLHTTP(param);
    } else if (t == kURLTypeFile) {
        ParseServerAndPort(param);
        result = ParseURLFILE(param);
    } else if (t == kURLTypeFTP) {
        ParseUsernameAndPassword(param);
        ParseServerAndPort(param);
        result = ParseURLFTP(param);
    } else if (t == kURLTypeMailTo) {
        result = ParseURLMailTo(param);
    } else if (t == kURLTypeRelative) {
        ParseServerAndPort(param);
        result = ParseURLHTTP(param);
    } else if (t == kURLTypeUnknown) {
        result = ParseURLUnknown(param);
    }
    mbParsed = result;
    return result;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0094b8e0  URL::MakeURLStringFromComponents
// ---------------------------------------------------------------------------------------------
bool URL::Fn94b8e0() {
    if (!mbParsed) {
        Str tmp;
        tmp.CopyFrom(msURL);
        Fn94b760(tmp);
        if (tmp.mpCapacity - tmp.mpBegin > 1 && tmp.mpBegin)
            operator_delete__(tmp.mpBegin);
    }
    Str* pScheme = &msComponent[kScheme];
    Str* pURL = &msURL;
    if (pScheme != pURL)
        pURL->assign(pScheme->mpBegin, pScheme->mpEnd);
    pURL->push_back(':');
    if (mURLType != kURLTypeMailTo)
        pURL->append((const char*)0x0142ef10, (const char*)0x0142ef12);

    if (msComponent[kUser].size() != 0 ||
        msComponent[kPassword].size() != 0) {
        pURL->append(msComponent[kUser].mpBegin, msComponent[kUser].mpEnd);
        if (msComponent[kPassword].size() != 0) {
            pURL->push_back(':');
            pURL->append(msComponent[kUser].mpBegin, msComponent[kUser].mpEnd);
        }
        pURL->push_back('@');
    }
    pURL->append(msComponent[kServer].mpBegin, msComponent[kServer].mpEnd);
    if (strtoul(msComponent[kPort].mpBegin, 0, 10) != 0)
        pURL->append(msComponent[kPort].mpBegin, msComponent[kPort].mpEnd);
    pURL->append(msComponent[kPath].mpBegin, msComponent[kPath].mpEnd);
    pURL->append(msComponent[kParms].mpBegin, msComponent[kParms].mpEnd);
    pURL->append(msComponent[kQuery].mpBegin, msComponent[kQuery].mpEnd);
    pURL->append(msComponent[kFrag].mpBegin, msComponent[kFrag].mpEnd);
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0094ba30  URL::IsURLRelative(char const *)
// ---------------------------------------------------------------------------------------------
bool URL::IsURLRelative(const char* url) {
    URL u(url);
    if (!u.mbParsed) {
        Str tmp;
        tmp.CopyFrom(u.msURL);
        u.Fn94b760(tmp);
        if (tmp.mpCapacity - tmp.mpBegin > 1 && tmp.mpBegin)
            operator_delete__(tmp.mpBegin);
    }
    bool r = (u.mURLType == kURLTypeRelative);
    u.Fn60a100();
    return r;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0094baa0  URL::GetURLType
// ---------------------------------------------------------------------------------------------
int URL::Fn94baa0() {
    if (!mbParsed) {
        Str tmp;
        tmp.CopyFrom(msURL);
        Fn94b760(tmp);
        if (tmp.mpCapacity - tmp.mpBegin > 1 && tmp.mpBegin)
            operator_delete__(tmp.mpBegin);
    }
    return mURLType;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0094baf0  URL::GetPart
// ---------------------------------------------------------------------------------------------
Str* URL::GetPart(int which) {
    if (!mbParsed) {
        Str tmp;
        tmp.CopyFrom(msURL);
        Fn94b760(tmp);
        if (tmp.mpCapacity - tmp.mpBegin > 1 && tmp.mpBegin)
            operator_delete__(tmp.mpBegin);
    }
    return (Str*)((which + 2) * 0x10 + (char*)this);
}
