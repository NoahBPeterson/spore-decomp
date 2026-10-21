// slice s011e94f0 -- RenderWare 4 core, rw::core::stdc printf engine.
//
// This address range (0x011e2000-0x0120bc50) is RenderWare 4 core, built with VC .NET 2003
// (cl 13.10) and /GL + /LTCG (see symbols/renderware4_core.txt).  A single-object compile
// cannot reproduce LTCG cross-call register allocation, so byte-exactness is not generally
// achievable here; these are complete behavioural reconstructions.
//
// The slice is the tail of the rw::core::stdc formatted-output machinery:
//   011e94f0  EmitStrPadded   -- write a (wide or narrow) string, left-pad to a field width
//   011e9630  EmitStr         -- write a string with no padding
//   011e96d0  EmitStrPadRight -- write a string, right-pad with spaces to a field width
//   011e97a0  EmitStrZeroPad  -- as EmitStrPadded but with the caller's zero/space fill flag
//   011e98b0  UIntToADigits   -- recursive unsigned-decimal digit emitter (base 10)
//   011e9900  UInt64ToA       -- unsigned 64-bit to decimal string
//   011e9950  UInt64ToHexUp   -- unsigned 64-bit to uppercase hex string (A-F)
//   011e99b0  UInt64ToHexLow  -- unsigned 64-bit to lowercase hex string (a-f)
//   011e9a10  VsnprintfCore   -- the %-format interpreter driving the helpers above
//
// The helpers run under the LTCG register ABI (width in eax, source in ecx/esi, the running
// character count and the remaining field budget in registers); the signatures below use the
// natural argument order recovered from the disassembly.
//
// Reconstructed model: the real RenderWare stdc writers are shared by a 8-bit and a 16-bit
// (wchar_t) entry point.  The `bWide` selector converts the narrow source to a temporary wide
// buffer via the image routine at 0x011ed270 and then emits one byte per wide character (the
// low byte), so the two paths only differ in how they measure the source.
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP
#include <string.h>
#include "types.h"

typedef unsigned int        u32;
typedef signed   int        i32;
typedef unsigned __int64    u64;
typedef unsigned short      u16;
typedef unsigned char       u8;

// ---- out-of-slice callees (real addresses) ---------------------------------
int  __cdecl StringLength(const char* s);              // 0x011e8c40  rw::core::stdc::StringLength
u16* __cdecl AnsiToWide(u16* dst, const char* src);    // 0x011ed270  narrow -> wide copy

// The RenderWare stdc numeric writers are real named functions at fixed addresses; declaring
// them in their true namespace lets the equivalence resolver bind the call to the original.
namespace rw { namespace core { namespace stdc {

int  __cdecl ConvertIToA(i32 value, char* out, int base);                 // 0x011ed0f0
void __cdecl ConvertI64ToA(u32 lo, u32 hi, char* out, int base, int caps); // 0x011ed190
void __cdecl ConvertfToA(char* out, double value, int prec);             // 0x011e8f10
void __cdecl ConvertDtoA(char* out, double value, int prec);             // 0x011e8c90 (split helper)

} } }

// The %e/%E/%g/%G writers and the raw 64-bit stream formatter are unnamed in the image; they
// are addressed by the hex forms the resolver recognises.
void __cdecl f_011e9090(char* out, double value, int prec);   // 0x011e9090  %e
void __cdecl f_011e9100(char* out, double value, int prec);   // 0x011e9100  %E
void __cdecl f_011e91a0(char* out, double value, int mode);   // 0x011e91a0  %g/%G
void __cdecl f_011ed230(u32 value, char* out, int base);      // 0x011ed230  %x/%X raw

// The "(null)" literal the reference writers substitute for a null source
// (three dwords loaded from 0x0149c914).
static const char kNullStr[] = "(null)";

// ---------------------------------------------------------------------------
// 011e94f0  EmitStrPadded
//
//   dst      destination cursor (register ebp)
//   src      source string: narrow bytes, or wide (u16) when bWide (register esi / ecx)
//   width    minimum field width for padding (register eax)
//   pWidth   in/out: remaining field budget; the padding loop stops when it hits 0 (edi)
//   pCount   in/out: running count of characters produced (stack, later re-read)
//   bWide    source is a wide (u16) string
//   zeroPad  pad byte is '0' when set, ' ' otherwise
//
// Returns the advanced destination cursor.
// ---------------------------------------------------------------------------
char* __cdecl EmitStrPadded(char* dst, const void* src, int width, int* pWidth,
                            int* pCount, char bWide, char zeroPad)
{
    const char* narrow = (const char*)src;
    const u16*  wide   = (const u16*)src;
    int len;

    if (bWide) {
        u16 tmp[512];
        if (wide == 0)
            wide = (const u16*)AnsiToWide(tmp, kNullStr);
        len = 0;
        while (wide[len] != 0)
            len++;
    } else {
        if (narrow == 0)
            narrow = kNullStr;
        len = StringLength(narrow);
    }

    int pad = width - len;
    while (pad > 0) {
        if (*pWidth > 0) {
            *pWidth = *pWidth - 1;
            *dst++ = zeroPad ? '0' : ' ';
        }
        (*pCount)++;
        pad--;
    }

    if (bWide) {
        while (*wide != 0) {
            if (*pWidth > 0) {
                *dst++ = (char)*wide;
                *pWidth = *pWidth - 1;
            }
            wide++;
            (*pCount)++;
        }
    } else {
        char c = *narrow;
        while (c != 0) {
            if (*pWidth > 0) {
                *dst++ = c;
                *pWidth = *pWidth - 1;
            }
            narrow++;
            (*pCount)++;
            c = *narrow;
        }
    }
    return dst;
}

// ---------------------------------------------------------------------------
// 011e9630  EmitStr  --  write a string with no width/padding handling.
//   dst = dest cursor, src = string, pCount = running count.  Returns dest cursor.
// ---------------------------------------------------------------------------
char* __cdecl EmitStr(char* dst, const void* src, int* pCount, char bWide)
{
    if (bWide) {
        u16 tmp[512];
        const u16* wide = (const u16*)src;
        if (wide == 0)
            wide = (const u16*)AnsiToWide(tmp, kNullStr);
        while (*wide != 0) {
            *dst++ = (char)*wide;
            wide++;
            (*pCount)++;
        }
    } else {
        const char* narrow = (const char*)src;
        if (narrow == 0)
            narrow = kNullStr;
        char c = *narrow;
        while (c != 0) {
            *dst++ = c;
            narrow++;
            (*pCount)++;
            c = *narrow;
        }
    }
    return dst;
}

// ---------------------------------------------------------------------------
// 011e96d0  EmitStrPadRight  --  write a string, then pad on the right with spaces to width.
//   width = field width, dst/src/pCount as EmitStr.  Returns dest cursor.
// ---------------------------------------------------------------------------
char* __cdecl EmitStrPadRight(char* dst, const void* src, int width, int* pCount, char bWide)
{
    int len;

    if (bWide) {
        u16 tmp[512];
        const u16* wide = (const u16*)src;
        if (wide == 0)
            wide = (const u16*)AnsiToWide(tmp, kNullStr);
        len = 0;
        while (wide[len] != 0)
            len++;
        while (*wide != 0) {
            *dst++ = (char)*wide;
            wide++;
            (*pCount)++;
        }
    } else {
        const char* narrow = (const char*)src;
        if (narrow == 0)
            narrow = kNullStr;
        len = StringLength(narrow);
        while (*narrow != 0) {
            *dst++ = *narrow;
            narrow++;
            (*pCount)++;
        }
    }

    int pad = width - len;
    while (pad > 0) {
        *dst++ = ' ';
        (*pCount)++;
        pad--;
    }
    return dst;
}

// ---------------------------------------------------------------------------
// 011e97a0  EmitStrZeroPad  --  as EmitStrPadded but the caller selects the fill byte via
//   zeroPad and the padding honours *pWidth.  (Signature mirrors EmitStrPadded; the
//   difference is only in which register carries each value on entry.)
// ---------------------------------------------------------------------------
char* __cdecl EmitStrZeroPad(char* dst, const void* src, int width, int* pWidth,
                             int* pCount, char bWide, char zeroPad)
{
    const char* narrow = (const char*)src;
    const u16*  wide   = (const u16*)src;
    int len;

    if (bWide) {
        u16 tmp[512];
        if (wide == 0)
            wide = (const u16*)AnsiToWide(tmp, kNullStr);
        len = 0;
        while (wide[len] != 0)
            len++;
    } else {
        if (narrow == 0)
            narrow = kNullStr;
        len = StringLength(narrow);
    }

    int pad = width - len;
    while (pad > 0) {
        *dst++ = zeroPad ? '0' : ' ';
        (*pCount)++;
        pad--;
    }

    if (bWide) {
        while (*wide != 0) {
            *dst++ = (char)*wide;
            wide++;
            (*pCount)++;
        }
    } else {
        while (*narrow != 0) {
            *dst++ = *narrow;
            narrow++;
            (*pCount)++;
        }
    }
    return dst;
}

// ---------------------------------------------------------------------------
// 011e98b0  UIntToADigits  --  recursive base-10 digit emitter.
//   Emits the digits of (hi:lo) most-significant first; returns the advanced cursor.
// ---------------------------------------------------------------------------
static char* __cdecl UIntToADigits(char* dst, u32 lo, u32 hi)
{
    if (hi == 0 && lo == 0)
        return dst;

    u64 value = ((u64)hi << 32) | lo;
    u32 rem   = (u32)(value % 10);
    u64 quot  = value / 10;

    dst = UIntToADigits(dst, (u32)quot, (u32)(quot >> 32));
    *dst++ = (char)(rem + '0');
    return dst;
}

// ---------------------------------------------------------------------------
// 011e9900  UInt64ToA  --  write (hi:lo) as a decimal string, NUL terminated.
//   Returns dst.
// ---------------------------------------------------------------------------
char* __cdecl UInt64ToA(char* dst, u32 lo, u32 hi)
{
    if (hi == 0 && lo == 0) {
        dst[0] = '0';
        dst[1] = 0;
        return dst;
    }
    u64 value = ((u64)hi << 32) | lo;
    u32 rem   = (u32)(value % 10);
    u64 quot  = value / 10;
    char* end = UIntToADigits(dst, (u32)quot, (u32)(quot >> 32));
    *end++ = (char)(rem + '0');
    *end = 0;
    return dst;
}

// ---------------------------------------------------------------------------
// 011e9950  UInt64ToHexUp  --  write (hi:lo) as uppercase hex, no NUL terminator.
//   Returns the advanced cursor.
// ---------------------------------------------------------------------------
char* __cdecl UInt64ToHexUp(char* dst, u32 lo, u32 hi)
{
    if (hi == 0 && lo == 0)
        return dst;

    u32 nextLo = (lo >> 4) | (hi << 28);
    u32 nextHi = hi >> 4;
    dst = UInt64ToHexUp(dst, nextLo, nextHi);

    u32 nib = lo & 0xf;
    *dst++ = (char)(nib > 9 ? nib + 'A' - 10 : nib + '0');
    return dst;
}

// ---------------------------------------------------------------------------
// 011e99b0  UInt64ToHexLow  --  as UInt64ToHexUp but lowercase (a-f).
// ---------------------------------------------------------------------------
char* __cdecl UInt64ToHexLow(char* dst, u32 lo, u32 hi)
{
    if (hi == 0 && lo == 0)
        return dst;

    u32 nextLo = (lo >> 4) | (hi << 28);
    u32 nextHi = hi >> 4;
    dst = UInt64ToHexLow(dst, nextLo, nextHi);

    u32 nib = lo & 0xf;
    *dst++ = (char)(nib > 9 ? nib + 'a' - 10 : nib + '0');
    return dst;
}

// ===========================================================================
// 011e9a10  VsnprintfCore
//
// The %-format interpreter.  Walks the format string, gathers the argv stream
// from the caller's raw stack frame (fp), writes into dst and returns the
// number of characters produced.  Supported conversions: %c %d %i %u %o %x %X
// %s %S %e %E %f %g %G %p %n %% and the "I64" length modifier.
//
// The argument walker (`fpargs`) is the pointer to the raw slot stream; the
// reference advances it by 4 bytes for a 32-bit argument and 8 for a 64-bit
// one, with the %S / %(wide) cases stepping the character-argument cursor.
// ===========================================================================
int __cdecl VsnprintfCore(char* dst, const char* fmt, u32* fpargs)
{
    // Argument-stream cursors: `slots` is the 32/64-bit value stream, `cslot`
    // is the parallel character-cursor stream the wide (%S) cases advance.
    u8*   cslot = (u8*)fpargs - 4;
    u32*  slots = fpargs;

    int   count      = 0;              // characters emitted so far
    int   fieldWidth = 0;              // parsed numeric field width
    char  leftAdj    = 1;              // not '-'  (1 = pad on the left)
    char  zeroPad    = 0;              // '0' flag
    char  is64       = 0;              // "I64" modifier seen
    char  isWide     = 0;              // source string is wide (%S / %ls)
    char  emit       = 1;              // whether the trailing width/pad pass runs
    char  haveField  = 1;              // a numeric field width was specified
    char  spaceFlag  = 0;              // ' ' flag
    char  plusFlag   = 0;              // '+' flag
    char  altFlag    = 0;              // '#' flag

    if (fmt == 0) {
        *dst = 0;
        return 0;
    }

    for (;;) {
        char c = *fmt;

        // ---- literal run -------------------------------------------------
        if (c != '%') {
            if (c == 0) {
                *dst = 0;
                return count;
            }
            *dst++ = c;
            fmt++;
            count++;
            continue;
        }

        // ---- '%' : parse flags / width / length / conversion --------------
        const char* p = fmt + 1;
        leftAdj   = 1;
        zeroPad   = 0;
        fieldWidth = 0;

        switch (*p) {
        case '-': leftAdj = 0; p++; break;
        case '0': zeroPad = 1; p++; break;
        case ' ': spaceFlag = 1; p++; break;
        case '+': plusFlag = 1; p++; break;
        case '#': altFlag = 1; p++; break;
        default: break;
        }

        while (*p >= '0' && *p <= '9')
            fieldWidth = fieldWidth * 10 + (*p++ - '0');

        // length modifier "I64"
        is64 = 0;
        if (p[0] == 'I' && p[1] == '6' && p[2] == '4') {
            p += 3;
            is64 = 1;
        }

        char conv = *p;
        isWide = 0;
        haveField = 0;
        int padWidth = fieldWidth;

        switch (conv) {
        case '%':
            *dst++ = '%';
            count++;
            emit = 0;
            break;

        case 'c':
            *dst = (char)*(u8*)(cslot + 4);
            dst[1] = 0;
            cslot += 4;
            slots += 1;
            break;

        case 's':
            isWide = zeroPad;
            emit = 1;
            cslot += 4;
            slots += 1;
            break;

        case 'S':
            isWide = 1;
            emit = 1;
            cslot += 4;
            slots += 1;
            break;

        case 'd':
        case 'i': {
            char* numbuf = dst;
            if (is64) {
                i32 lo = (i32)slots[0];
                i32 hi = (i32)slots[1];
                if (zeroPad && leftAdj && padWidth > 0 && hi < 0) {
                    lo = -lo;
                    hi = -(hi + (lo == 0));
                    *dst++ = '-';
                    count++;
                    padWidth--;
                }
                rw::core::stdc::ConvertI64ToA((u32)lo, (u32)hi, numbuf, 10, 0);
                cslot += 8;
                slots += 2;
            } else {
                i32 v = (i32)slots[0];
                if (zeroPad && leftAdj && padWidth > 0 && v < 0) {
                    v = -v;
                    *dst++ = '-';
                    count++;
                    padWidth--;
                }
                rw::core::stdc::ConvertIToA(v, numbuf, 10);
                cslot += 4;
                slots += 1;
            }
            break;
        }

        case 'u': {
            char* numbuf = dst;
            if (is64) {
                u32 lo = slots[0];
                u32 hi = slots[1];
                numbuf = UInt64ToA(numbuf, lo, hi);
                cslot += 8;
                slots += 2;
            } else {
                rw::core::stdc::ConvertI64ToA(slots[0], 0, numbuf, 10, 0);
                cslot += 4;
                slots += 1;
            }
            break;
        }

        case 'o': {
            rw::core::stdc::ConvertIToA((i32)slots[0], dst, 8);
            cslot += 4;
            slots += 1;
            break;
        }

        case 'x': {
            char* numbuf = dst;
            if (is64) {
                if (slots[0] == 0 && slots[1] == 0) {
                    numbuf[0] = '0';
                    numbuf[1] = 0;
                } else {
                    char* e = UInt64ToHexLow(numbuf, slots[0], slots[1]);
                    *e = 0;
                }
                cslot += 8;
                slots += 2;
            } else {
                f_011ed230(slots[0], numbuf, 16);
                cslot += 4;
                slots += 1;
            }
            break;
        }

        case 'X': {
            char* numbuf = dst;
            if (is64) {
                if (slots[0] == 0 && slots[1] == 0) {
                    numbuf[0] = '0';
                    numbuf[1] = 0;
                } else {
                    char* e = UInt64ToHexUp(numbuf, slots[0], slots[1]);
                    *e = 0;
                }
                cslot += 8;
                slots += 2;
            } else {
                f_011ed230(slots[0], numbuf, 16);
                cslot += 4;
                slots += 1;
            }
            break;
        }

        case 'f': {
            double v = *(double*)(slots);
            rw::core::stdc::ConvertfToA(dst, v, haveField ? padWidth : 0);
            cslot += 8;
            slots += 2;
            break;
        }

        case 'e': {
            f_011e9090(dst, *(double*)(slots), haveField ? padWidth : 0);
            cslot += 8;
            slots += 2;
            break;
        }

        case 'E': {
            f_011e9100(dst, *(double*)(slots), haveField ? padWidth : 0);
            cslot += 8;
            slots += 2;
            break;
        }

        case 'g':
        case 'G': {
            f_011e91a0(dst, *(double*)(slots), conv == 'G');
            cslot += 8;
            slots += 2;
            break;
        }

        case 'p': {
            char* numbuf = dst;
            f_011ed230((u32)slots[0], numbuf, 16);
            int n = StringLength(numbuf);
            cslot += 4;
            slots += 1;
            if (n < 8) {
                int zeros = 8 - n;
                for (int k = n; k >= 0; k--)
                    numbuf[k + zeros] = numbuf[k];
                for (int k = 0; k < zeros; k++)
                    numbuf[k] = '0';
            }
            break;
        }

        case 'n': {
            *(i32*)(*(u32*)slots) = count;
            emit = 0;
            cslot += 4;
            slots += 1;
            break;
        }

        default:
            emit = 0;
            if (*p) p++;               // skip the unknown conversion letter
            goto next;
        }

        if (*p)
            p++;

        // ---- trailing width / padding pass -------------------------------
        if (emit) {
            if (padWidth == 0) {
                if (isWide || conv == 'S')
                    dst = EmitStr(dst, (const void*)(*(u32*)(cslot - 4)), &count, isWide);
                else
                    dst = EmitStr(dst, (const void*)(*(u32*)(cslot - 4)), &count, 0);
            } else if (leftAdj) {
                dst = EmitStrZeroPad(dst, (const void*)(*(u32*)(cslot - 4)), padWidth, &padWidth,
                                     &count, isWide, zeroPad);
            } else {
                dst = EmitStrPadRight(dst, (const void*)(*(u32*)(cslot - 4)), padWidth, &count,
                                      isWide);
            }
        }

    next:
        fmt = p;
        if (*fmt == 0) {
            *dst = 0;
            return count;
        }
    }
}
