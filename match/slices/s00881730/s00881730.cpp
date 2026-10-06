// slice s00881730 -- EA::Locale number/money formatting helpers.
// Module flags: /O2 /MD /Gy /TP.  See manifest.txt / nonmatching.txt / partial.txt.
#include "types.h"

typedef unsigned short u16;

// ---- callees ---------------------------------------------------------------
int __cdecl FUN_00881c50(double a, int b, int c, int d, const wchar_t* fmt);
int __cdecl FtoaEnglish16(double a, u16* buf, int n, int radix, int flags);
extern "C" __declspec(dllimport) int __cdecl iswctype(u16 c, int type);
void __cdecl FUN_00881f30(u16* a, u16* b, int c, int d, int e, int f);

extern const wchar_t* DAT_01650540;
extern const wchar_t* DAT_01650574;

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
// @ 0x00881c50  (eastl::fixed_string<wchar_t,16,1>::operator= -- only a stub)
// ---------------------------------------------------------------------------
__declspec(noinline) int FUN_00881c50(double a, int b, int c, int d, const wchar_t* fmt)
{
    static volatile int sink;
    sink = (int)a + b + c + d + (fmt != 0);
    return sink;
}

// ---------------------------------------------------------------------------
// @ 0x00881f30  (EA::Locale::SetMoneyStringLocal -- only a stub)
// ---------------------------------------------------------------------------
__declspec(noinline) void FUN_00881f30(u16* a, u16* b, int c, int d, int e, int f)
{
    static volatile int sink;
    sink = (a != 0) + (b != 0) + c + d + e + f;
}

// ---------------------------------------------------------------------------
// @ 0x00881ae0  (SetNumberString -- only a stub)
// ---------------------------------------------------------------------------
__declspec(noinline) int FUN_00881ae0(void)
{
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00881730  (only a stub)
// ---------------------------------------------------------------------------
__declspec(noinline) int FUN_00881730(void)
{
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00882380  (GetLocaleTraits -- only a stub)
// ---------------------------------------------------------------------------
__declspec(noinline) int FUN_00882380(void* a, int b)
{
    (void)a; (void)b;
    return 0;
}
