// Slice s00946dc0 -- EA::Internet (UTFInternet): multipart/form-data post body stream
// and HTTP date/time string parsing.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
//
// 13 assigned VAs, 7 byte-exact; every VA is a manifest row (the non-exact ones
// also appear in nonmatching.txt).  See work/match/scratch_s79_final_summary.txt
// for the whole batch (96/202 byte-exact).
#include "s00946dc0.h"
#include <intrin.h>

typedef int  (__thiscall *VF0)(void*);
typedef bool (__thiscall *VFB0)(void*);
typedef int  (__thiscall *VF1)(void*, int);
typedef int  (__thiscall *VF2)(void*, int, int);
typedef int  (__thiscall *VF3)(void*, int, int, int);

#define VSLOT(p, byteoff) ((*(void***)(p))[(byteoff) / 4])
#define VCALL0(p, off)          ((VF0)VSLOT(p, off))(p)
#define VCALLB0(p, off)         ((VFB0)VSLOT(p, off))(p)
#define VCALL1(p, off, a)       ((VF1)VSLOT(p, off))(p, (int)(a))
#define VCALL2(p, off, a, b)    ((VF2)VSLOT(p, off))(p, (int)(a), (int)(b))
#define VCALL3(p, off, a, b, c) ((VF3)VSLOT(p, off))(p, (int)(a), (int)(b), (int)(c))

#define S_(a) ((const char*)(a))

static const char* const kLongWeekdays = S_(0x143f4e8);   // "Monday"...
static const char* const kShortWeekdays = S_(0x143f530);  // "Mon"...
static const char* const kShortMonths = S_(0x143f54c);    // "Jan"...

// @ 0x00946dc0
HTTPMultipartFormDataPostBodyStream::HTTPMultipartFormDataPostBodyStream()
{
    mpVtbl = (void*)0x13fb5c8;
    mpVtbl2 = (void*)0x13ef094;
    _InterlockedExchange(&mnRefCount, 0);
    mpVtbl = (void*)0x143f3e0;
    mpVtbl2 = (void*)0x143f3d8;
    mListAnchor.mpNext = &mListAnchor;
    mListAnchor.mpPrev = &mListAnchor;
    msBoundary.mpBegin = 0;
    msBoundary.mpEnd = 0;
    msBoundary.mpCapacity = 0;
    msBoundary.RangeInitialize(0x20);
    {
        char* p = msBoundary.mpBegin;
        memcpy(p, S_(0x13fb554), 0x1f);
        msBoundary.mpEnd = p + 0x1f;
        *msBoundary.mpEnd = 0;
    }
    mnPosition = -1;
    mnSize = 0;
    mnState = 0;
    mbFinal = false;
    mLastDataType = 1;
    mnTextStart = 0;
    mpMemStream = 0;
    mReadItr = &mListAnchor;
    {
        void* mem = operator new(0x24, S_(0x143f3bc), 0, 0, 0, 0);
        void* stream = 0;
        if (mem) {
            ((MemoryStream*)mem)->Construct(S_(0x143f3bc));
            stream = mem;
        }
        void* old = mpMemStream;
        if (stream != old) {
            if (stream)
                VCALL0(stream, 4);
            mpMemStream = stream;
            if (old)
                VCALL0(old, 8);
        }
        ((MemoryStream*)mpMemStream)->SetOption(1, 1.0f);
        ((MemoryStream*)mpMemStream)->SetOption(2, 0.0f);
        ((MemoryStream*)mpMemStream)->SetOption(3, *(const float*)0x13ef574);
    }
}

// @ 0x00946f10
bool HTTPMultipartFormDataPostBodyStream::Close()
{
    bool ok = true;
    mnState = -2;
    ListNode* node = mListAnchor.mpNext;
    while (node != &mListAnchor) {
        if (!VCALLB0(((StreamNode*)node)->mpStream, 0x18))
            ok = false;
        node = node->mpNext;
    }
    ((ListBase*)&mListAnchor)->DoClear();
    ListNode* anchor = &mListAnchor;
    anchor->mpNext = anchor;
    anchor->mpPrev = anchor;
    if (mpMemStream) {
        void* old = mpMemStream;
        mpMemStream = 0;
        VCALL0(old, 8);
    }
    return ok;
}

// @ 0x00946f70
HTTPMultipartFormDataPostBodyStream::~HTTPMultipartFormDataPostBodyStream()
{
    mpVtbl = (void*)0x143f3e0;
    mpVtbl2 = (void*)0x143f3d8;
    _ReadWriteBarrier();
    if (mpMemStream)
        VCALL0(mpMemStream, 8);
    if (msBoundary.mpCapacity - msBoundary.mpBegin > 1 && msBoundary.mpBegin)
        operator delete(msBoundary.mpBegin);
    ((ListBase*)&mListAnchor)->DoClear();
    mpVtbl2 = (void*)0x13ef094;
    mpVtbl = (void*)0x13f3a68;
}

// @ 0x00946fe0
bool HTTPMultipartFormDataPostBodyStream::GetContentTypeString(eastl::StrStub* out)
{
    out->assign(S_(0x143f444), S_(0x143f444) + 0x1e);
    const char* boundary = (const char*)VCALL0(this, 0x4c);
    unsigned n = strlen(boundary);
    out->append(boundary, boundary + n);
    return true;
}

// @ 0x00947030
bool HTTPMultipartFormDataPostBodyStream::AddFormData(const char* name, void* stream,
        const char* contentType, const char* fileName, const char* transferEncoding)
{
    if (mbFinal)
        mnState = -1;
    if (!name || !stream || !contentType)
        mnState = -1;
    else {
        int sz = VCALL0(stream, 0x1c);
        if (sz == -1 || sz == -2)
            mnState = -1;
    }
    if (mnState != 0)
        return false;
    {
        unsigned pos = VCALL1(mpMemStream, 0x24, 0);
        if (mLastDataType == 1) {
            mnTextStart = pos;
            mLastDataType = 0;
        }
    }
    VCALL2(this, 0x58, S_(0x13fb644), mpMemStream);
    VCALL2(mpMemStream, 0x38, msBoundary.mpBegin,
           (int)(msBoundary.mpEnd - msBoundary.mpBegin));
    VCALL2(this, 0x58, S_(0x13fb618), mpMemStream);
    VCALL2(this, 0x58, name, mpMemStream);
    VCALL2(this, 0x58, S_(0x13fb764), mpMemStream);
    if (fileName) {
        VCALL2(this, 0x58, S_(0x13fb754), mpMemStream);
        VCALL2(this, 0x58, fileName, mpMemStream);
        VCALL2(this, 0x58, S_(0x13fb764), mpMemStream);
    }
    VCALL2(this, 0x58, S_(0x13fb750), mpMemStream);
    VCALL2(this, 0x58, S_(0x13fb740), mpMemStream);
    VCALL2(this, 0x58, contentType, mpMemStream);
    VCALL2(this, 0x58, S_(0x13fb750), mpMemStream);
    if (transferEncoding) {
        VCALL2(this, 0x58, S_(0x13fb724), mpMemStream);
        VCALL2(this, 0x58, transferEncoding, mpMemStream);
        VCALL2(this, 0x58, S_(0x13fb750), mpMemStream);
    }
    VCALL2(this, 0x58, S_(0x13fb750), mpMemStream);
    if (VCALL0(mpMemStream, 0x14) != 0) {
        mnState = -1;
        return false;
    }
    if (!VCALLB0(this, 0x60)) {
        mnState = -1;
        return false;
    }
    if (stream)
        VCALL0(stream, 4);
    {
        StreamNode* node = (StreamNode*)operator new(0xc, S_(0x13f2150), 0, 0,
                                                    (int)S_(0x13ebb38), 0xd1);
        void* p = (char*)node + 8;
        if (p) {
            node->mpStream = stream;
            if (stream)
                VCALL0(stream, 4);
        }
        node->mpNext = &mListAnchor;
        node->mpPrev = mListAnchor.mpPrev;
        mListAnchor.mpPrev->mpNext = node;
        mListAnchor.mpPrev = node;
    }
    if (stream)
        VCALL0(stream, 8);
    mnSize += VCALL0(stream, 0x2c);
    mLastDataType = 1;
    return true;
}

// @ 0x00947270
bool HTTPMultipartFormDataPostBodyStream::CreateChildStream()
{
    if (mbFinal || !mpMemStream || mLastDataType != 0) {
        mnState = -1;
        return false;
    }
    {
        void* mem = operator new(0x1c, S_(0x143f464), 0, 0, 0, 0);
        void* child = 0;
        if (mem) {
            void* ms = mpMemStream;
            unsigned pos = VCALL1(ms, 0x24, 0);
            unsigned len = pos - mnTextStart;
            ((StreamChild*)mem)->Construct(ms, mnTextStart, len);
            child = mem;
        }
        AutoRefCountIStream tmp(child);
        void* s = tmp.mpObject;
        if (!s) {
            mnState = -1;
            return false;
        }
        VCALL2(s, 0x28, 0, 0);
        VCALL0(s, 4);
        {
            StreamNode* node = (StreamNode*)operator new(0xc, S_(0x13f2150), 0, 0,
                                                        (int)S_(0x13ebb38), 0xd1);
            void* p = (char*)node + 8;
            if (p) {
                node->mpStream = s;
                VCALL0(s, 4);
            }
            node->mpNext = &mListAnchor;
            node->mpPrev = mListAnchor.mpPrev;
            mListAnchor.mpPrev->mpNext = node;
            mListAnchor.mpPrev = node;
        }
        VCALL0(s, 8);
        unsigned p1 = VCALL1(mpMemStream, 0x24, 0);
        mnSize += p1 - mnTextStart;
        mnTextStart = VCALL1(mpMemStream, 0x24, 0);
        VCALL0(s, 8);
    }
    return true;
}

// @ 0x009473a0
void StrVec::PushEmpty()
{
    char* end = mpEnd;
    if (end < mpCapacity) {
        mpEnd = end + 0x10;
        if (end) {
            *(char**)end = (char*)0x1667bac;
            *(char**)(end + 4) = (char*)0x1667bac;
            *(char**)(end + 8) = (char*)0x1667bad;
        }
        return;
    }
    {
        char tmp[16];
        *(char**)tmp = (char*)0x1667bac;
        *(char**)(tmp + 4) = (char*)0x1667bac;
        *(char**)(tmp + 8) = (char*)0x1667bad;
        DoInsertValue(end, tmp);
        if (*(char**)(tmp + 8) - *(char**)tmp > 1 && *(char**)tmp)
            operator delete(*(char**)tmp);
    }
}

// @ 0x00947410
__int64 TimeToSeconds(int weekday, int day, int month, int year, int yday,
                      int hour, int minute, int second)
{
    struct tm t = { second, minute, hour, day, month - 1, year - 1900,
                    weekday - 1, yday - 1, 1 };
    return _mktime64(&t);
}

// @ 0x00947480
int WeekdayStringToInteger(const char* str, bool longNames)
{
    if (longNames) {
        unsigned off = 0;
        const char* p = kLongWeekdays;
        int n = 0;
        do {
            if (_stricmp(str, p) == 0)
                return n + 1;
            off += 10;
            n++;
            p += 10;
        } while (off < 0x46);
        return 0;
    } else {
        unsigned off = 0;
        const char* p = kShortWeekdays;
        int n = 0;
        do {
            if (_stricmp(str, p) == 0)
                return n + 1;
            off += 4;
            n++;
            p += 4;
        } while (off < 0x1c);
    }
    return 0;
}

// @ 0x00947500
int MonthStringToInteger(const char* str)
{
    unsigned i = 0;
    const char* p = kShortMonths;
    do {
        if (_stricmp(str, p) == 0)
            return i + 1;
        i++;
        p += 4;
    } while (i < 12);
    return 0;
}

// @ 0x00947540
int GetDateTypeFromString(const eastl::StrStub* s)
{
    char b[8][44];
    const char* src = s->mpBegin;
    unsigned len = (unsigned)(s->mpEnd - s->mpBegin);
    int comma = -1;
    if (len != 0) {
        const char* p = src;
        while (p != s->mpEnd) {
            if (*p == ',')
                break;
            p++;
        }
        if (p != s->mpEnd)
            comma = (int)(p - src);
    }
    if (len < 0x30) {
        if ((unsigned)comma < len) {
            if (comma == 3) {
                if (len != 0x1d)
                    return 0;
                if (sscanf(src, S_(0x143f5b8), b[0], b[1], b[2], b[3], b[4], b[5]) != 6) {
                    eastl::StrStub tmp(*s);
                    tmp.mpBegin[0xb] = ' ';
                    tmp.mpBegin[7] = ' ';
                    if (sscanf(tmp.mpBegin, S_(0x143f5b8), b[0], b[1], b[2], b[3], b[4], b[5]) != 6) {
                        ((eastl::StrDtor*)&tmp)->Destroy();
                        return 0;
                    }
                    ((eastl::StrDtor*)&tmp)->Destroy();
                }
                return 1;
            }
            if (len - 0x1e <= 5) {
                if (sscanf(src, S_(0x143f5ac), b[0], b[1], b[2], b[3]) == 4) {
                    if (b[1][1] == 0)
                        return 2;
                    if (b[1][3] == 0)
                        return 3;
                }
            }
            return 0;
        }
        if (len == 0x18) {
            if (sscanf(src, S_(0x143f5c8), b[0], b[1], b[2], b[3], b[4]) == 5)
                return 4;
        }
    }
    return 0;
}

// @ 0x00947700
bool ParseDateTimeString(const eastl::StrStub* s, int* weekday, int* day, int* month,
                         int* year, int* yday, int* hour, int* min, int* sec)
{
    eastl::StrStub tmp(s->mpBegin, s->mpEnd);
    char b[8][44];
    int type = GetDateTypeFromString(s);
    if ((unsigned)(s->mpEnd - s->mpBegin) >= 0x30)
        goto fail;
    if (type == 1) {
        tmp.mpBegin[3] = ' ';
        tmp.mpBegin[7] = ' ';
        tmp.mpBegin[0xb] = ' ';
        tmp.mpBegin[0x13] = ' ';
        tmp.mpBegin[0x16] = ' ';
        if (sscanf(tmp.mpBegin, S_(0x143f5e4), b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]) != 8)
            goto fail;
        {
            int wd = 0;
            unsigned i = 0;
            const char* p = kShortWeekdays;
            do {
                if (_stricmp(b[0], p) == 0) {
                    wd = i + 1;
                    break;
                }
                i++;
                p += 4;
            } while (i < 7);
            *weekday = wd;
        }
        *day = atoi(b[1]);
        *month = MonthStringToInteger(b[2]);
        {
            int y = atoi(b[3]);
            if ((unsigned)y < 0x32)
                y += 0x7d0;
            else if ((unsigned)y < 0x64)
                y += 0x76c;
            *year = y;
        }
        {
            int leap = 0;
            unsigned y = (unsigned)*year;
            if ((y & 3) == 0) {
                if (y % 100 != 0)
                    leap = 1;
                else if (y % 400 == 0)
                    leap = 1;
            }
            *yday = kMonthDayOffset[*month] + leap + 1 + *day;
        }
        *hour = atoi(b[4]);
        *min = atoi(b[5]);
        *sec = atoi(b[6]);
        eastl::StrStubRelease(&tmp);
        return true;
    }
    if (type == 2 || type == 3) {
        unsigned pos = tmp.find(',', 0);
        unsigned len = (unsigned)(tmp.mpEnd - tmp.mpBegin);
        if (pos >= len)
            goto fail;
        if (pos + 0x11 >= len)
            goto fail;
        tmp.mpBegin[pos] = ' ';
        tmp.mpBegin[pos + 4] = ' ';
        tmp.mpBegin[pos + 8] = ' ';
        if (type == 2) {
            tmp.mpBegin[pos + 0xe] = ' ';
            tmp.mpBegin[pos + 0x11] = ' ';
        } else {
            tmp.mpBegin[pos + 0x10] = ' ';
            tmp.mpBegin[pos + 0x13] = ' ';
        }
        if (sscanf(tmp.mpBegin, S_(0x143f5e4), b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]) != 8)
            goto fail;
        *weekday = WeekdayStringToInteger(b[0], true);
        *day = atoi(b[1]);
        *month = MonthStringToInteger(b[2]);
        {
            int y = atoi(b[3]);
            if ((unsigned)y < 0x32)
                y += 0x7d0;
            else if ((unsigned)y < 0x64)
                y += 0x76c;
            *year = y;
        }
        {
            int leap = 0;
            unsigned y = (unsigned)*year;
            if ((y & 3) == 0) {
                if (y % 100 != 0)
                    leap = 1;
                else if (y % 400 == 0)
                    leap = 1;
            }
            *yday = kMonthDayOffset[*month] + leap + 1 + *day;
        }
        *hour = atoi(b[4]);
        *min = atoi(b[5]);
        *sec = atoi(b[6]);
        ((eastl::StrDtor*)&tmp)->Destroy();
        return true;
    }
    if (type == 4) {
        unsigned pos = tmp.find(':', 0);
        unsigned len = (unsigned)(tmp.mpEnd - tmp.mpBegin);
        tmp.mpBegin[pos] = ' ';
        tmp.mpBegin[pos + 2] = ' ';
        if (pos >= len)
            goto fail;
        if (pos + 2 >= len)
            goto fail;
        if (sscanf(tmp.mpBegin, S_(0x143f5d4), b[0], b[1], b[2], b[3], b[4], b[5], b[6]) != 7)
            goto fail;
        {
            int wd = 0;
            unsigned i = 0;
            const char* p = kShortWeekdays;
            do {
                if (_stricmp(b[0], p) == 0) {
                    wd = i + 1;
                    break;
                }
                i++;
                p += 4;
            } while (i < 7);
            *weekday = wd;
        }
        *month = MonthStringToInteger(b[1]);
        *day = atoi(b[2]);
        *hour = atoi(b[3]);
        *min = atoi(b[4]);
        *sec = atoi(b[5]);
        {
            int y = atoi(b[6]);
            if ((unsigned)y < 0x32)
                y += 0x7d0;
            else if ((unsigned)y < 0x64)
                y += 0x76c;
            *year = y;
        }
        {
            int leap = 0;
            unsigned y = (unsigned)*year;
            if ((y & 3) == 0) {
                if (y % 100 != 0)
                    leap = 1;
                else if (y % 400 == 0)
                    leap = 1;
            }
            *yday = kMonthDayOffset[*month] + leap + 1 + *day;
        }
        ((eastl::StrDtor*)&tmp)->Destroy();
        return true;
    }
fail:
    eastl::StrStubRelease(&tmp);
    return false;
}

// @ 0x00947cd0
int TimeStringToSeconds(const eastl::StrStub* s)
{
    int weekday;
    int day;
    int month;
    int year;
    int yday;
    int hour;
    int min;
    int sec;
    if (ParseDateTimeString(s, &weekday, &day, &month, &year, &yday, &hour, &min, &sec))
        return (int)TimeToSeconds(weekday, day, month, year, yday, hour, min, sec);
    return 0;
}
