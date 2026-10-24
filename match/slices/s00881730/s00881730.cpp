// slice s00881730 -- EA::Locale number/money/time formatting helpers.
// Module flags: /O2 /MD /Gy /TP.  See manifest.txt / nonmatching.txt / partial.txt.
#include "types.h"

typedef unsigned short u16;
typedef unsigned int u32;

// ---- shared locale types ---------------------------------------------------
struct Loc16 {                     // Loc<16> / FixedBuf<16>
    wchar_t* f00;                  // +0x00 begin
    wchar_t* f04;                  // +0x04 end
    wchar_t* f08;                  // +0x08 capacity
    int      f0C;                  // +0x0c
    wchar_t* f10;                  // +0x10 inline buffer start
    wchar_t  buf[16];              // +0x14
};
struct LocInfo {                   // parsed locale description
    u32 lcid;                      // +0
    u16 base;                      // +4
    u16 script;                    // +6
};
struct FmtElem {                   // format element (LocField in the original)
    Loc16    s;                    // +0x00
    int      flags;                // +0x34
    int      type;                 // +0x38
    u32      width;                // +0x3c
    u32      prec;                 // +0x40
    const wchar_t* begin;          // +0x44
    const wchar_t* end;            // +0x48
};
struct LocScan { const wchar_t* cur; u32 len; };

// ---- callees ---------------------------------------------------------------
int __cdecl FUN_00881c50(double a, int b, int c, int d, const wchar_t* fmt);
int __cdecl FtoaEnglish16(double a, u16* buf, int n, int radix, int flags);   // 0x92d9b0
extern "C" __declspec(dllimport) int __cdecl iswctype(u16 c, int type);
int  __cdecl FUN_00881f30(u16* a, u16* b, int c, int d, int e, int f);
extern "C" __declspec(dllimport) wchar_t* __cdecl _ltow(long, wchar_t*, int); // IAT 0x13cc408
int  __cdecl FUN_0092d060(int lo, int hi, wchar_t* out, int base);            // 0x92d060
void __cdecl FUN_00f47380(void* p);                                          // 0xf47380
void __cdecl FUN_0087f0e0(void* self);                                       // 0x87f0e0

// 0x87d6d0
char __cdecl FUN_0087d6d0(wchar_t* s, FmtElem* fields, int* pCount, wchar_t** pOut);
// 0x87f370
char __cdecl FUN_0087f370(FmtElem* dst, int count, const wchar_t* str);
// 0x8804d0
int __cdecl FUN_008804d0(wchar_t* out, int cap, LocScan* v, FmtElem* first, int count);
// 0x87e080  (thiscall, one stack arg)
Loc16* __fastcall FUN_0087e080(Loc16* self, void*, const wchar_t* s);
// 0x68cc10  (thiscall, two stack args)
void __fastcall FUN_0068cc10(Loc16* self, void*, const wchar_t* b, const wchar_t* e);
// 0x6962a0  Loc16(const wchar_t*)  (thiscall, one stack arg)
Loc16* __fastcall FUN_006962a0(Loc16* self, void*, const wchar_t* s);
// 0x696320  Loc16 = Loc16  (thiscall, one stack arg)
Loc16* __fastcall FUN_00696320(Loc16* self, void*, const Loc16* src);
// 0x57cb80  ~Loc16  (thiscall)
void __fastcall FUN_0057cb80(Loc16* self, void*);
// 0x401930  ??_H / vector_constructor_iterator
void __stdcall FUN_00401930(void* p, unsigned size, int count, void* ctor);
// 0x87d9a0
int __cdecl FUN_0087d9a0(const Loc16* a, const Loc16* b);
// 0x87da90
char __cdecl FUN_0087da90(LocInfo* info, const Loc16* name);
// 0x87e130
char __cdecl FUN_0087e130(const LocInfo* info, Loc16* out);
// 0x87ed70 / 0x87edd0
Loc16* __cdecl FUN_0087ed70(Loc16* dst, const Loc16* src);
Loc16* __cdecl FUN_0087edd0(Loc16* dst, const Loc16* src);
// 0x87f700
int __cdecl FUN_0087f700(const Loc16* src);
// 0x87de40
int __cdecl FUN_0087de40(int idx, const wchar_t* table, wchar_t* out, int cap);
// 0x880610  (thiscall, one stack arg) -> Loc16*
Loc16* __fastcall FUN_00880610(void* tree, void*, const Loc16* key);
// 0x87f550  (thiscall, one stack arg)
void* __fastcall FUN_0087f550(Loc16* self, void*, const Loc16* src);
// 0x6863e0  (thiscall, one stack arg)
void __fastcall FUN_006863e0(void* self, void*, void* src);
// 0x880910
int __cdecl FUN_00880910(int id, int flags, wchar_t* out, int cap, const Loc16* loc);

extern const wchar_t* DAT_01650540;
extern const wchar_t* DAT_01650574;
extern const wchar_t* DAT_0165043c;            // time format string
extern Loc16 DAT_016504d8;                     // money positive prefix
extern Loc16 DAT_0165050c;                     // money negative prefix
extern Loc16 DAT_01650408;
extern Loc16 DAT_0165085c;
extern Loc16 DAT_015490e4;                     // default/root locale name

// ---------------------------------------------------------------------------
// local helpers
// ---------------------------------------------------------------------------
static inline void InitLoc16(Loc16* p)
{
    wchar_t* b = p->buf;
    p->f00 = b;
    p->f04 = b;
    p->f08 = b + 16;
    p->f10 = b;
    *b = 0;
}

static inline void ReleaseLoc16(Loc16* p)
{
    int d = (int)((char*)p->f08 - (char*)p->f00);
    if ((d & -2) > 2 && p->f00 != 0 && p->f00 != p->f10)
        FUN_00f47380(p->f00);
}

static inline u32 WcsLen(const wchar_t* s)
{
    const wchar_t* e = s;
    while (*e) ++e;
    return (u32)(e - s);
}

// ---------------------------------------------------------------------------
// @ 0x00881ea0
// ---------------------------------------------------------------------------
void __cdecl FUN_00881ea0(double a, int b, int c, int d)
{
    FUN_00881c50(a, b, c, d, L"%N%?p%?2F");
}

// ---------------------------------------------------------------------------
// @ 0x00881ed0
// ---------------------------------------------------------------------------
void __cdecl FUN_00881ed0(double a, int b, int c, int d)
{
    FUN_00881c50(a, b, c, d, DAT_01650540);
}

// ---------------------------------------------------------------------------
// @ 0x00881f00
// ---------------------------------------------------------------------------
void __cdecl FUN_00881f00(double a, int b, int c, int d)
{
    FUN_00881c50(a, b, c, d, DAT_01650574);
}

// ---------------------------------------------------------------------------
// @ 0x008822e0  (EA::Locale::SetMoneyString)
// ---------------------------------------------------------------------------
void __cdecl FUN_008822e0(double a, int p2, int p3, int p4, int p5)
{
    u16 buf[128];
    FtoaEnglish16(a, buf, 0x80, 10, 0);
    u16* p = buf;
    for (;;) {
        u16 c = *p;
        if (c != 0x2d && c != 0x2b) {
            if (iswctype(c, 4) == 0) {
                u16* q = p + 1;
                if (*p == 0)
                    q = p;
                *p = 0;
                FUN_00881f30(buf, q, p2, p3, p4, p5);
                return;
            }
        }
        ++p;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00881c50  (number formatter: FtoaEnglish16 + format element loop)
// ---------------------------------------------------------------------------
int FUN_00881c50(double a, int b, int c, int d, const wchar_t* fmt)
{
    wchar_t* out = (wchar_t*)b;
    int      cap = c;
    const wchar_t* str = (const wchar_t*)d;
    int      ret = -1;

    if (out == 0)
        return ret;
    if (fmt == 0)
        return ret;

    u16 num[128];
    FtoaEnglish16(a, num, 0x80, 10, 0);

    u16* p = num;
    if (*p != 0) {
        for (;;) {
            u16 ch = *p;
            if (ch != 0x2d && ch != 0x2b) {
                if (iswctype(ch, 4) == 0)
                    break;
            }
            ++p;
            if (*p == 0)
                break;
        }
    }
    u16* rest = (*p != 0) ? p + 1 : p;
    *p = 0;

    FmtElem elems[8];
    FUN_00401930(elems, 0x4c, 8, (void*)&FUN_0087f0e0);

    int      count = 8;
    wchar_t* pOut = 0;
    if (FUN_0087d6d0((wchar_t*)fmt, elems, &count, &pOut) != 0) {
        if (pOut == 0) {
            FUN_0087f370(elems, count, str);

            LocScan scan;
            scan.cur = fmt;
            scan.len = WcsLen(fmt);

            int  last = -1;
            bool hide = true;
            for (int i = 0; i < count; ++i) {
                FmtElem* e = &elems[i];
                switch (e->type) {
                case 1:                                   // 'N'
                case 2:                                   // 'W'
                    FUN_0087e080(&e->s, 0, (const wchar_t*)num);
                    break;
                case 3:                                   // 'F'
                    FUN_0087e080(&e->s, 0, (const wchar_t*)rest);
                    if ((e->flags & 1) && *rest == 0) {
                        e->flags |= 0x20;
                        hide = false;
                    }
                    break;
                case 13:                                  // 'p'
                    last = i;
                    break;
                }
            }
            if (last > 0 && !hide && (elems[last].flags & 1))
                elems[last].flags |= 0x20;

            ret = FUN_008804d0(out, cap, &scan, elems, count);
        }
    }

    for (int i = 7; i >= 0; --i)
        ReleaseLoc16(&elems[i].s);
    return ret;
}

// ---------------------------------------------------------------------------
// @ 0x00881f30  (EA::Locale::SetMoneyStringLocal)
// ---------------------------------------------------------------------------
int FUN_00881f30(u16* a, u16* b, int c, int d, int e, int f)
{
    const wchar_t* num  = (const wchar_t*)a;
    const wchar_t* rest = (const wchar_t*)b;
    wchar_t* out        = (wchar_t*)c;
    int      cap        = d;
    const wchar_t* str  = (const wchar_t*)e;
    const wchar_t* text = (const wchar_t*)f;
    int      ret        = -1;

    if (out == 0)
        return ret;

    const wchar_t* fmt;
    if (*num == 0x2d) {
        fmt = (DAT_0165050c.f00 != DAT_0165050c.f04 && DAT_0165050c.f00 != 0)
                  ? DAT_0165050c.f00 : L"";
    } else {
        fmt = (DAT_016504d8.f00 != DAT_016504d8.f04 && DAT_016504d8.f00 != 0)
                  ? DAT_016504d8.f00 : L"";
    }

    FmtElem elems[8];
    for (int i = 0; i < 8; ++i)
        InitLoc16(&elems[i].s);

    int      count = 8;
    wchar_t* pOut = 0;
    if (FUN_0087d6d0((wchar_t*)fmt, elems, &count, &pOut) != 0) {
        if (pOut == 0) {
            FUN_0087f370(elems, count, str);

            LocScan scan;
            scan.cur = fmt;
            scan.len = WcsLen(fmt);

            int  last = -1;
            bool hide = true;
            for (int i = 0; i < count; ++i) {
                FmtElem* el = &elems[i];
                switch (el->type) {
                case 1:                                   // 'N'
                case 2:                                   // 'W'
                    FUN_0087e080(&el->s, 0, num);
                    break;
                case 3:                                   // 'F'
                    FUN_0087e080(&el->s, 0, rest);
                    if ((el->flags & 1) && rest == 0) {
                        el->flags |= 0x20;
                        hide = false;
                    }
                    break;
                case 13:                                  // 'p'
                    last = i;
                    break;
                default:
                    if (el->type >= 4 && el->type <= 12 && text != 0) {
                        Loc16 tmp;
                        FUN_006962a0(&tmp, 0, text);
                        FUN_00696320(&el->s, 0, &tmp);
                        FUN_0057cb80(&tmp, 0);
                    }
                    break;
                }
            }
            if (last > 0 && !hide && (elems[last].flags & 1))
                elems[last].flags |= 0x20;

            ret = FUN_008804d0(out, cap, &scan, elems, count);
        }
    }

    for (int i = 7; i >= 0; --i)
        ReleaseLoc16(&elems[i].s);
    return ret;
}

// ---------------------------------------------------------------------------
// @ 0x00881ae0  (EA::Locale::SetNumberString)
// ---------------------------------------------------------------------------
int FUN_00881ae0(long long value, wchar_t* out, int cap)
{
    if (out == 0)
        return -1;

    const wchar_t fmt[3] = { L'%', L'N', 0 };

    FmtElem elems[2];
    for (int i = 0; i < 2; ++i)
        InitLoc16(&elems[i].s);

    int      count = 2;
    wchar_t* pOut = 0;
    int      ret = -1;
    if (FUN_0087d6d0((wchar_t*)fmt, elems, &count, &pOut) != 0) {
        if (pOut == 0) {
            wchar_t num[128];
            FUN_0092d060((int)value, (int)(value >> 32), num, 10);
            FUN_0087e080(&elems[0].s, 0, num);

            LocScan scan;
            scan.cur = fmt;
            scan.len = WcsLen(fmt);

            ret = FUN_008804d0(out, cap, &scan, elems, count);
        }
    }

    for (int i = 1; i >= 0; --i)
        ReleaseLoc16(&elems[i].s);
    return ret;
}

// ---------------------------------------------------------------------------
// @ 0x00881730  (time formatter)
// ---------------------------------------------------------------------------
int FUN_00881730(int hour, int minute, int second, wchar_t* out, int cap,
                 const wchar_t* str)
{
    FmtElem elems[16];
    for (int i = 0; i < 16; ++i)
        InitLoc16(&elems[i].s);

    int      count = 16;
    wchar_t* pOut = 0;
    int      ret = -1;

    const wchar_t* fmt = DAT_0165043c;
    if (FUN_0087d6d0((wchar_t*)fmt, elems, &count, &pOut) != 0) {
        if (pOut == 0) {
            FUN_0087f370(elems, count, str);

            LocScan scan;
            scan.cur = fmt;
            scan.len = WcsLen(fmt);

            int  minIdx = -1;
            int  secIdx = -1;
            int  ampmIdx = -1;
            bool am = false;
            bool pm = false;

            if (hour == 24)
                hour = 0;

            wchar_t num[128];
            for (int i = 0; i < count; ++i) {
                FmtElem* el = &elems[i];
                switch (el->type) {
                case 4:                                   // 'h' 12-hour
                    if (hour < 12) {
                        am = true;
                    } else {
                        if (hour > 12)
                            hour -= 12;
                        pm = true;
                    }
                    _ltow(hour, num, 10);
                    FUN_0087e080(&el->s, 0, num);
                    break;
                case 5:                                   // 'H' 24-hour
                    _ltow(hour, num, 10);
                    FUN_0087e080(&el->s, 0, num);
                    break;
                case 6:                                   // 'M'
                    _ltow(minute, num, 10);
                    FUN_0087e080(&el->s, 0, num);
                    minIdx = i;
                    break;
                case 7:                                   // 'S'
                    _ltow(second, num, 10);
                    FUN_0087e080(&el->s, 0, num);
                    secIdx = i;
                    break;
                case 8:                                   // 'A'
                    ampmIdx = i;
                    break;
                }
            }

            if (minIdx > 0 || secIdx > 0) {
                bool zero = false;
                {   // 0x881935..0x881989
                    bool set = true;
                    if (secIdx >= 0) {
                        if (second >= 0 && minute >= 0) {
                            if (second != 0 || (elems[secIdx].flags & 0x21) == 0)
                                set = false;
                        }
                    }
                    if (set) {
                        elems[secIdx].flags |= 0x20;
                        zero = true;
                    }
                }
                {   // 0x88198b..0x8819bf
                    bool set = false;
                    if (minIdx < 0 || minute < 0)
                        set = true;
                    else if (zero && minute == 0 && (elems[minIdx].flags & 0x21) != 0)
                        set = true;
                    if (set)
                        elems[minIdx].flags |= 0x20;
                }
            }

            if (ampmIdx > 0) {
                wchar_t ampm[0x80];
                if (pm)
                    FUN_00880910(0x1d, -1, ampm, 0x80, &DAT_015490e4);
                else if (am)
                    FUN_00880910(0x1c, -1, ampm, 0x80, &DAT_015490e4);

                FmtElem* el = &elems[ampmIdx];
                if (el->s.f00 != ampm) {
                    if (el->s.f00 != el->s.f04) {
                        *el->s.f00 = 0;
                        el->s.f04 = el->s.f00;
                    }
                    u32 n = WcsLen(ampm);
                    FUN_0068cc10(&el->s, 0, ampm, ampm + n);
                }
            }

            ret = FUN_008804d0(out, cap, &scan, elems, count);
        }
    }

    for (int i = 15; i >= 0; --i)
        ReleaseLoc16(&elems[i].s);
    return ret;
}

// ---------------------------------------------------------------------------
// @ 0x00882380  (EA::Locale::`anonymous_namespace'::GetLocaleTraits)
// ---------------------------------------------------------------------------
bool FUN_00882380(char* flag, const Loc16* name)
{
    if (FUN_0087d9a0(name, &DAT_01650408) != 0 ||
        FUN_0087d9a0(name, &DAT_0165085c) != 0) {
        if (FUN_0087d9a0(name, &DAT_015490e4) == 0) {
            *flag = 1;
            return 1;
        }
    }
    if (FUN_0087d9a0(name, &DAT_015490e4) != 0) {
        if (FUN_0087d9a0(&DAT_01650408, &DAT_015490e4) == 0) {
            *flag = 1;
            return 1;
        }
    }

    *flag = 0;

    LocInfo info;
    if (FUN_0087da90(&info, name) == 0)
        return 0;

    Loc16 lb;
    InitLoc16(&lb);
    FUN_0068cc10(&lb, 0, DAT_015490e4.f00, DAT_015490e4.f04);
    lb.buf[0] = 0;

    if (FUN_0087e130(&info, &lb) == 0) {
        ReleaseLoc16(&lb);
        return 0;
    }

    {
        Loc16 tmp;
        FUN_0087ed70(&tmp, &lb);
        FUN_00696320((Loc16*)((char*)flag + 0xca8), 0, &tmp);
        ReleaseLoc16(&tmp);
    }
    {
        Loc16 tmp2;
        FUN_0087edd0(&tmp2, &lb);
        FUN_00696320((Loc16*)((char*)flag + 0xcdc), 0, &tmp2);
        ReleaseLoc16(&tmp2);
    }

    int alias = FUN_0087f700(&lb);
    if (alias == 0) {
        ReleaseLoc16(&lb);
        return 0;
    }

    {
        wchar_t buf[0x80];
        FUN_0087de40(0, (const wchar_t*)alias, buf, 0x5e);

        Loc16 lb2;
        InitLoc16(&lb2);
        FUN_0068cc10(&lb2, 0, buf, buf + WcsLen(buf));

        {
            Loc16 tmp3;
            FUN_0087edd0(&tmp3, &lb2);
            FUN_00696320((Loc16*)((char*)flag + 0xc74), 0, &tmp3);
            FUN_0057cb80(&tmp3, 0);
        }
        {
            Loc16 tmp4;
            FUN_0087ed70(&tmp4, &lb2);
            FUN_00696320((Loc16*)((char*)flag + 0xc40), 0, &tmp4);
            FUN_0057cb80(&tmp4, 0);
        }

        Loc16* p1 = FUN_00880610((void*)0x154919c, 0, (Loc16*)((char*)flag + 0xc74));
        FUN_0087f550((Loc16*)((char*)flag + 0x418), 0, p1);
        Loc16* p2 = FUN_00880610((void*)0x1549180, 0, (Loc16*)((char*)flag + 0xc40));
        FUN_0087f550((Loc16*)((char*)flag + 4), 0, p2);
        FUN_006863e0((char*)flag + 0x82c, 0, (void*)alias);

        ReleaseLoc16(&lb2);
    }

    ReleaseLoc16(&lb);
    return 1;
}
