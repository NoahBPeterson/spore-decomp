// Slice s0087d6d0 - EA::Locale support routines: field/format parsing, locale table
// lookups, number grouping and small buffer helpers. Optimized (/O2).
#include "types.h"

// ---------------------------------------------------------------- externs / helpers
extern "C" {
__declspec(dllimport) unsigned long __stdcall GetSystemDefaultLCID();
__declspec(dllimport) wchar_t* __cdecl wcschr(const wchar_t*, wchar_t);
__declspec(dllimport) int      __cdecl wcsncmp(const wchar_t*, const wchar_t*, unsigned);
__declspec(dllimport) long     __cdecl wcstol(const wchar_t*, wchar_t**, int);
__declspec(dllimport) int      __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
__declspec(dllimport) int      __cdecl iswctype(wchar_t, unsigned);
__declspec(dllimport) int      __cdecl tolower(int);
}

// field/separator tokenizer (out of slice @ 0x0087d620)
int __cdecl LocFieldToken(int idx, const wchar_t* src, wchar_t* dst, int cap, wchar_t sep);
// wide range appender (out of slice @ 0x0068cf60)
void __cdecl LocAppendRaw(const wchar_t* first, const wchar_t* last);
// EASTL allocator free / allocate (out of slice)
void __cdecl LocFree(void* p);                                    // 0x00f47380
void* __cdecl LocNew(unsigned size, const char* name, int flags, int align,
                     const char* file, int line);                 // 0x00f473a0
// EASTL fixed-vector insert (memcpy-like; out of slice @ 0x011e0744)
void* __cdecl LocVecInsert(void* dst, const void* src, unsigned n);

// locale name tables (null-terminated arrays of wide strings)
extern const wchar_t* g_localeEnUS[];   // 0x01548c20
extern const wchar_t* g_localeCht[];    // 0x01548ec8
extern const wchar_t* g_localeAus[];    // 0x01548f28
extern wchar_t*       g_grpSepBegin;    // 0x016507b0
extern wchar_t*       g_grpSepEnd;      // 0x016507b4

// vector-like wide output buffer (begin/end/capacity, allocator pointer + inline data)
struct LocBuf {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    LocBuf& AppendElement(const wchar_t* first, const wchar_t* last); // 0x0068cc10
    LocBuf* Assign(const wchar_t* s);                                 // 0x0087e080
};

// simple {begin,end} view
struct WStrView { wchar_t* mpBegin; wchar_t* mpEnd; };

// fixed inline wide buffer: +0 begin, +4 end, +8 capacity, +0x10 inline ptr, +0x14 data
template <int N>
struct FixedBuf {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mUnk0c;
    wchar_t* mpInline;
    wchar_t  mBuf[N];

    LocBuf& AppendElement(const wchar_t* first, const wchar_t* last);
    void ReleaseHeap()
    {
        wchar_t* p = mpBegin;
        if (((int)((char*)mpCapacity - (char*)p) & ~1) > 2 && p != 0 && p != mpInline)
            LocFree(p);
    }
};

// +0 / +4 wide-string vector used by MakeLocaleAvailable
struct LocView { wchar_t* mpBegin; wchar_t* mpEnd; };

// locale-info record (LCID + script)
struct LocInfo { uint32_t lcid; uint16_t base; uint16_t script; };

// field descriptor parsed out of a format string (size 0x4c)
struct LocField {
    uint8_t  pad00[0x34 - 0x00];  // 0x00
    uint32_t flags;               // 0x34
    uint32_t type;                // 0x38
    uint32_t width;               // 0x3c
    uint32_t prec;                // 0x40
    wchar_t* begin;               // 0x44
    wchar_t* end;                 // 0x48
};

// big locale-formatter object with seven fixed buffers
struct LocaleData {
    uint32_t      mUnk0;      // 0x00
    FixedBuf<512> mBuf1;      // 0x04
    FixedBuf<512> mBuf2;      // 0x418
    FixedBuf<512> mBuf3;      // 0x82c
    FixedBuf<16>  mBuf4;      // 0xc40
    FixedBuf<16>  mBuf5;      // 0xc74
    FixedBuf<16>  mBuf6;      // 0xca8
    FixedBuf<16>  mBuf7;      // 0xcdc

    void Free();              // @ 0x0087dd10
};

extern LocView g_unk15490e4;  // 0x015490e4

// @ 0x0087d6d0
uint8_t Locale_ParseFormat(wchar_t* s, LocField* fields, int* pCount, wchar_t** pOut)
{
    int       count = 0;
    uint8_t   ret = 1;
    wchar_t*  p = s;
    LocField* f = fields;
    wchar_t*  last = 0;
    if (*pCount > 0) {
        for (;;) {
            bool bWidth = false;
            bool bDot = false;
            bool bPrec = false;
            wchar_t* pc = wcschr(p, L'%');
            if (pc == 0) break;
            last = pc;
            f->begin = pc;
            f->end   = pc;
            p = pc + 1;
            f->flags = 0;
            f->type  = 0;
            f->width = (uint32_t)-1;
            f->prec  = (uint32_t)-1;
            for (;;) {
                wchar_t c = *p;
                if (c == 0) { f->type = 0; ret = 0; break; }
                switch (c) {
                case L'#': f->flags |= 0x40; break;
                case L'$': f->type = 0xc; goto done;
                case L'%': f->type = 0xe; goto done;
                case L'+': f->flags |= 0x04; break;
                case L'-': f->flags |= 0x20; break;
                case L'.': bWidth = true; bDot = true; break;
                case L'<': f->flags |= 0x10; break;
                case L'>': f->flags |= 0x08; break;
                case L'?': f->flags |= 0x01; break;
                case L'@': f->flags |= 0x80; break;
                case L'A': f->type = 8;   goto done;
                case L'F': f->type = 3;   goto done;
                case L'H': f->type = 5;   goto done;
                case L'M': f->type = 6;   goto done;
                case L'N': f->type = 1;   goto done;
                case L'S': f->type = 7;   goto done;
                case L'W': f->type = 2;   goto done;
                case L'd': f->type = 9;   goto done;
                case L'h': f->type = 4;   goto done;
                case L'm': f->type = 10;  goto done;
                case L'p': f->type = 0xd; goto done;
                case L'y': f->type = 0xb; goto done;
                default:
                    if (c >= L'0' && c <= L'9') {
                        if (c == L'0') {
                            if (bDot) f->prec = 0;
                            else      f->flags |= 0x02;
                        } else if (bWidth) {
                            if (!bPrec) { bPrec = true; f->prec = (uint32_t)(c - L'0'); }
                        } else {
                            bWidth = true;
                            f->width = (uint32_t)(c - L'0');
                        }
                    }
                    break;
                }
                p++;
            }
        done:
            f->end = p;
            last = p;
            f++;
            if (++count >= *pCount) break;
            p++;
        }
    }
    *pCount = count;
    if (*pOut != 0) {
        *pOut = 0;
        if (last != 0 && *last != 0 && last[1] != 0)
            *pOut = last + 1;
    }
    return ret;
}

// @ 0x0087d9a0  EA::Locale::MakeLocaleAvailable
int Locale_MakeLocaleAvailable(const LocView* a, const LocView* b)
{
    const int* pa = (const int*)a->mpBegin;
    const int* pb = (const int*)b->mpBegin;
    int n = (int)(a->mpEnd - a->mpBegin);
    if (n != (int)(b->mpEnd - b->mpBegin))
        return 0;
    unsigned m = (unsigned)n * 2;
    while (m > 3) {
        if (*pa != *pb) return 0;
        m -= 4;
        ++pa;
        ++pb;
    }
    if (m == 0) return 1;
    const char* ca = (const char*)pa;
    const char* cb = (const char*)pb;
    if (ca[0] != cb[0]) return 0;
    if (m <= 1) return 1;
    if (ca[1] != cb[1]) return 0;
    if (m <= 2) return 1;
    if (ca[2] != cb[2]) return 0;
    return 1;
}

// @ 0x0087da10
int Locale_MakeLocaleAvailableStr(const wchar_t* a, const LocView* b)
{
    const wchar_t* pa = a;
    while (*pa) ++pa;
    const int* ia = (const int*)a;
    const int* ib = (const int*)b->mpBegin;
    int n = (int)(pa - a);
    if (n != (int)(b->mpEnd - b->mpBegin))
        return 0;
    unsigned m = (unsigned)n * 2;
    while (m > 3) {
        if (*ia != *ib) return 0;
        m -= 4;
        ++ia;
        ++ib;
    }
    if (m == 0) return 1;
    const char* ca = (const char*)ia;
    const char* cb = (const char*)ib;
    if (ca[0] != cb[0]) return 0;
    if (m <= 1) return 1;
    if (ca[1] != cb[1]) return 0;
    if (m <= 2) return 1;
    if (ca[2] != cb[2]) return 0;
    return 1;
}

// @ 0x0087da90
bool Locale_GetSystemName(LocInfo* out, const LocView* name)
{
    if ((char)Locale_MakeLocaleAvailable(name, &g_unk15490e4)) {
        unsigned lcid = GetSystemDefaultLCID();
        out->lcid   = lcid;
        out->script = (uint16_t)(lcid >> 16) & 0xf;
        out->base   = (uint16_t)lcid;
        return true;
    }
    for (const wchar_t** pp = g_localeEnUS; *pp; ++pp) {
        wchar_t buf2[128];
        wchar_t buf[16];
        int n = LocFieldToken(0, *pp, buf, 0x10, L'^');
        if (wcsncmp(buf, name->mpBegin, n) == 0) {
            LocFieldToken(1, *pp, buf2, 0x80, L'^');
            int v = (int)wcstol(buf2, 0, 0x10);
            out->base   = (uint16_t)v;
            out->lcid   = (uint16_t)v;
            out->script = 0;
            return true;
        }
    }
    return false;
}

// @ 0x0087db80
int Locale_FindInCht(const wchar_t* name, wchar_t* out, int cap)
{
    for (const wchar_t** pp = g_localeCht; *pp; ++pp) {
        wchar_t a[0x20];
        wchar_t b[0x20];
        LocFieldToken(0, *pp, b, 0x20, L'^');
        int n = LocFieldToken(0, b, a, 0x20, L',');
        int i = 0;
        while (n > 0) {
            i++;
            if (_wcsicmp(a, name) == 0)
                return LocFieldToken(1, *pp, out, cap, L'^');
            n = LocFieldToken(i, b, a, 0x20, L',');
        }
    }
    return -1;
}

// @ 0x0087dc40
const wchar_t* Locale_FindByShortName(const wchar_t** table, const LocView* name)
{
    const wchar_t* s = *table;
    for (;;) {
        if (s == 0) return 0;
        wchar_t buf[0x80];
        int n = LocFieldToken(0, s, buf, 0x80, L'^');
        if (n < 0x80) {
            const uint16_t* q = (const uint16_t*)name->mpBegin;
            const uint16_t* p = (const uint16_t*)buf;
            int cmp;
            for (;;) {
                uint16_t c = *p;
                if (c != *q) { cmp = (c < *q) ? -1 : 1; break; }
                if (c == 0)  { cmp = 0; break; }
                c = p[1];
                if (c != q[1]) { cmp = (c < q[1]) ? -1 : 1; break; }
                p += 2;
                q += 2;
                if (c == 0) { cmp = 0; break; }
            }
            if (cmp == 0) return *table;
        }
        s = table[1];
        ++table;
    }
}

// @ 0x0087dd10
void LocaleData::Free()
{
    mBuf7.ReleaseHeap();
    mBuf6.ReleaseHeap();
    mBuf5.ReleaseHeap();
    mBuf4.ReleaseHeap();
    mBuf3.ReleaseHeap();
    mBuf2.ReleaseHeap();
    mBuf1.ReleaseHeap();
}

// @ 0x0087de40
bool Locale_SplitField(int index, wchar_t* s, LocBuf* out, wchar_t sep)
{
    if (s == 0) return false;
    int i = 0;
    for (;;) {
        wchar_t* p = wcschr(s, sep);
        if (p == 0) {
            p = wcschr(s, L'\0');
            if (p == 0) return false;
        }
        if (i == index) {
            if (out) out->AppendElement(s, p);
            return true;
        }
        i++;
        s = p + 1;
        if (*p == L'\0') return false;
    }
}

// @ 0x0087deb0
void Locale_FormatGrouped(LocBuf* out, LocField* spec, char noSign)
{
    const wchar_t* digits = spec->begin;
    wchar_t  buf[0x40];
    wchar_t* dst = buf;
    const wchar_t* p = digits;
    if (*p == L'-') {
        if (noSign == 0) { buf[0] = L'-'; dst = buf + 1; }
        ++p;
    }
    unsigned len = (unsigned)(spec->end - p);
    uint32_t width = spec->width;
    unsigned pad = 0, pad2 = 0;
    unsigned v = pad;
    if ((int)width >= 0) {
        if (len < width && (spec->flags & 2)) {
            pad = width - len;
        } else if (width < len) {
            len = (width * 2) >> 1;
        }
        if (spec->type == 3) { pad2 = pad; pad = 0; }
        v = pad;
    }
    unsigned groups = (len + v + 2) / 3;
    unsigned rem = 3 - (len + v) % 3;
    if (rem == 3) rem = 0;
    if (groups == 0) groups = 1;
    unsigned total = groups + v + len - 1;
    while (total != 0) {
        --total;
        if (rem < 3) {
            ++rem;
            if (v == 0) {
                if (len == 0) {
                    if (pad2 != 0) { --pad2; *dst++ = L'0'; }
                } else {
                    --len;
                    *dst++ = *p++;
                }
            } else {
                --v;
                *dst++ = L'0';
            }
        } else if (groups != 0) {
            --groups;
            rem = 0;
            wchar_t* sep = g_grpSepBegin;
            wchar_t* q = dst;
            wchar_t c;
            do { c = *sep++; *q++ = c; } while (c != 0);
            dst += (g_grpSepEnd - g_grpSepBegin);
        }
    }
    *dst = 0;
    wchar_t* e = buf;
    while (*e) ++e;
    out->AppendElement(buf, e);
}

// @ 0x0087e060
void Locale_AppendView(LocBuf* self, const WStrView* v)
{
    self->AppendElement(v->mpBegin, v->mpEnd);
}

// @ 0x0087e080
LocBuf* LocBuf::Assign(const wchar_t* s)
{
    wchar_t* p = mpBegin;
    if (p != s) {
        if (p != mpEnd) {
            *p = 0;
            mpEnd = mpBegin;
        }
        const wchar_t* e = s;
        while (*e) ++e;
        int n = (int)(e - s);
        AppendElement(s, s + n);
    }
    return this;
}

// @ 0x0087e0d0
struct LocFmt : FixedBuf<16> {
    FixedBuf<512> mSecond;   // +0x34
    LocFmt* Assign(const LocFmt* src);
};

LocFmt* LocFmt::Assign(const LocFmt* src)
{
    mpInline   = mBuf;
    mpCapacity = mBuf + 16;
    mpBegin    = mBuf;
    mpEnd      = mBuf;
    *mpBegin   = 0;
    AppendElement(src->mpBegin, src->mpEnd);

    mSecond.mpInline   = mSecond.mBuf;
    mSecond.mpCapacity = mSecond.mBuf + 512;
    mSecond.mpBegin    = mSecond.mBuf;
    mSecond.mpEnd      = mSecond.mBuf;
    *mSecond.mpBegin   = 0;
    mSecond.AppendElement(src->mSecond.mpBegin, src->mSecond.mpEnd);
    return this;
}

// @ 0x0087e130
bool Locale_FindByLcid(const LocInfo* info, LocBuf* out)
{
    for (const wchar_t** pp = g_localeEnUS; *pp; ++pp) {
        wchar_t buf2[0x20];
        wchar_t buf[0x80];
        LocFieldToken(1, *pp, buf, 0x80, L'^');
        unsigned v = (unsigned)wcstol(buf, 0, 0x10);
        if (v == *(const uint16_t*)((const char*)info + 4)) {
            int n = LocFieldToken(0, *pp, buf2, 0x20, L'^');
            if (n > 0 && iswctype(buf2[0], 0x103) != 0) {
                wchar_t* p = out->mpBegin;
                if (p != buf2) {
                    if (p != out->mpEnd) { *p = 0; out->mpEnd = out->mpBegin; }
                    wchar_t* e = buf2;
                    while (*e) ++e;
                    int len = (int)(e - buf2);
                    out->AppendElement(buf2, buf2 + len);
                }
                return true;
            }
        }
    }
    return false;
}

// @ 0x0087e230
uint32_t Locale_FindLower(const wchar_t* name, wchar_t* out, int cap)
{
    for (const wchar_t** pp = g_localeAus; *pp; ++pp) {
        wchar_t  a[0x20];
        wchar_t  b[0x20];
        LocFieldToken(0, *pp, a, 0x20, L'^');
        int idx = 0;
        int n = LocFieldToken(0, a, b, 0x20, L',');
        while (n > 0) {
            ++idx;
            if (_wcsicmp(b, name) == 0)
                return LocFieldToken(1, *pp, out, cap, L'^');

            wchar_t taiwan[8];
            taiwan[0] = (wchar_t)(0x59d3 ^ 0x59a7);
            taiwan[1] = (wchar_t)(0x59c6 ^ 0x59a7);
            taiwan[2] = (wchar_t)(0x59ce ^ 0x59a7);
            taiwan[3] = (wchar_t)(0x59d0 ^ 0x59a7);
            taiwan[4] = (wchar_t)(0x59c6 ^ 0x59a7);
            taiwan[5] = (wchar_t)(0x59c9 ^ 0x59a7);
            taiwan[6] = 0;

            const wchar_t* e = b;
            while (*e) ++e;
            int blen = (int)(e - b);

            uint16_t* buf;
            uint16_t* bufEnd;
            if ((unsigned)(blen + 1) < 2) {
                buf    = (uint16_t*)g_grpSepBegin; // unused fallback (inline vec)
                bufEnd = (uint16_t*)g_grpSepBegin + 1;
            } else {
                buf = (uint16_t*)LocNew((blen + 1) * 2, "EASTL", 0, 0,
                        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                        0xd1);
                bufEnd = buf + (blen + 1);
            }
            LocVecInsert(buf, b, (unsigned)blen * 2);
            buf[blen] = 0;
            for (uint16_t* q = buf; q < buf + blen; ++q) {
                uint16_t c = *q;
                if (c < 0x100) c = (uint16_t)tolower(c & 0xff);
                *q = c;
            }

            const wchar_t* te = taiwan;
            while (*te) ++te;
            if (blen != 0 && buf != bufEnd) {
                for (uint16_t* q = buf; ; ++q) {
                    for (const uint16_t* t = (const uint16_t*)taiwan;
                         t != (const uint16_t*)te; ++t) {
                        if (*q == *t) {
                            int at = (int)(q - buf);
                            if (at != -1 && _wcsicmp((wchar_t*)(buf + at), name) == 0) {
                                uint32_t r = LocFieldToken(1, *pp, out, cap, L'^');
                                if (((int)((char*)bufEnd - (char*)buf) & ~1) > 2 && buf != 0)
                                    LocFree(buf);
                                return r;
                            }
                            break;
                        }
                    }
                    if (++q == bufEnd) break;
                }
            }
            if (((int)((char*)bufEnd - (char*)buf) & ~1) > 2 && buf != 0)
                LocFree(buf);
            n = LocFieldToken(idx, a, b, 0x20, L',');
        }
    }
    return (uint32_t)-1;
}