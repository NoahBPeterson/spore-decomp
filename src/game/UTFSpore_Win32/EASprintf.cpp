// src/game/UTFSpore_Win32/EASprintf.cpp -- migrated from slice(s) s00939a60, s00938bc0, s00937da0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EASprintf.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __stdcall WideCharToMultiByte(
    unsigned int codePage, unsigned long flags, const wchar_t* wide, int wideCount,
    char* multi, int multiCount, const char* defaultChar, int* usedDefault);
#include <stdarg.h>
#include <float.h>

// ---- items of slice s00937da0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __stdcall WideCharToMultiByte(
    unsigned int codePage, unsigned long flags, const wchar_t* wide, int wideCount,
    char* multi, int multiCount, const char* defaultChar, int* usedDefault);
typedef int (__cdecl *WriteFunction8)(const char* pData, int nCount, void* pContext);
struct SnprintfContext8 {
    char* mpDestination;      // +0
    int   mnCount;            // +4
    int   mnMaxCount;         // +8
    char  mbMaxCountReached;  // +0xc
};
__declspec(noinline) static int StringWriter8(const char* pData, int nCount, void* pContext) {
    SnprintfContext8* p = (SnprintfContext8*)pContext;
    int n = 0;
    if (p->mnCount < p->mnMaxCount) {
        n = p->mnMaxCount - p->mnCount;
        if (n > nCount) n = nCount;
        for (int i = 0; i < n; ++i) p->mpDestination[p->mnCount + i] = pData[i];
        p->mnCount += n;
    }
    return n;
}
struct FormatData8 {
    int  mAlignment;          // +0x00  0 = left, 1 = right, 2 = zero-fill
    int  mSign;               // +0x04  1 = minus only, 2 = plus, 3 = space
    char mbAlternativeForm;   // +0x08
    int  mnWidth;             // +0x0c
    int  mnPrecision;         // +0x10  INT_MAX = not specified
    int  mModifier;           // +0x14
    int  mnType;              // +0x18
};
static const char* ReadFormat8(va_list* pArguments, const char* pFormat, FormatData8* pData);
static char* WriteInteger8(unsigned int nValue, FormatData8* pData, char* pBufferEnd);
char* WriteInteger64_8(FormatData8* pData, unsigned int nLow, unsigned int nHigh, char* pBufferEnd); // 0x00937720
char* WriteDouble8(FormatData8* pData, double dValue, char* pBufferEnd);                 // 0x00937970
static inline unsigned int FormatChar(char c) { return (unsigned char)c; }
static inline unsigned int FormatChar(wchar_t c) { return c; }
template <typename C>
static __forceinline const C* ReadFormatT(va_list* pArguments, const C* pFormat, FormatData8* pData) {
    int nAlignment = 1;
    int nSign = 1;
    char bAlternativeForm = 0;
    int nWidth = 0;
    int nPrecision = 0x7fffffff;
    int nModifier = 0;
    int nType = 0;
    int nPrevAlignment = 0;

    const C* p = pFormat + 1;
    unsigned int c = FormatChar(*p);

    if (c == '%') {
        nType = '%';
        goto done;
    }

    // flags
    while (c - 0x20 <= 0x10) {
        if (c == ' ') {
            if (nSign != 2)
                nSign = 3;
        } else if (c == '#') {
            bAlternativeForm = 1;
        } else if (c == '+') {
            nSign = 2;
        } else if (c == '-') {
            nAlignment = 0;
        } else if (c == '0') {
            if (nAlignment != 0) {
                if (nAlignment != 2)
                    nPrevAlignment = nAlignment;
                nAlignment = 2;
            }
        } else {
            break;
        }
        c = FormatChar(*++p);
    }

    // width
    if (c == '*') {
        nWidth = va_arg(*pArguments, int);
        if (nWidth < 0) {
            nWidth = -nWidth;
            nAlignment = 0;
        }
        c = FormatChar(*++p);
        if (nWidth > 0x400)
            goto done;
    } else if (c - '0' < 10) {
        do {
            nWidth = nWidth * 10 + (c - '0');
            c = FormatChar(*++p);
        } while (c - '0' < 10);
        if (nWidth > 0x400)
            goto done;
    }

    // precision
    if (c == '.') {
        c = FormatChar(*++p);
        if (c == '*') {
            nPrecision = va_arg(*pArguments, int);
            if (nPrecision < 0)
                nPrecision = 0;
            c = FormatChar(*++p);
        } else {
            nPrecision = 0;
            while (c - '0' < 10) {
                nPrecision = nPrecision * 10 + (c - '0');
                c = FormatChar(*++p);
            }
        }
        if (nPrecision > 0x400 && nPrecision != 0x7fffffff)
            goto done;
    }

    // length modifier
    switch (c) {
        case 'I': {
            unsigned int c1 = FormatChar(p[1]);
            if (c1 == '8') {
                nModifier = 10;
                ++p;
            } else if (c1 == '1' && FormatChar(p[2]) == '6') {
                nModifier = 11;
                p += 2;
            } else if (c1 == '3' && FormatChar(p[2]) == '2') {
                nModifier = 12;
                p += 2;
            } else if (c1 == '6' && FormatChar(p[2]) == '4') {
                nModifier = 13;
                p += 2;
            } else if (c1 == '1' && FormatChar(p[2]) == '2' && FormatChar(p[3]) == '8') {
                nModifier = 14;
                p += 3;
            } else {
                goto done;
            }
            c = FormatChar(*++p);
            break;
        }
        case 'L':
            nModifier = 8;
            c = FormatChar(*++p);
            break;
        case 'h':
            if (FormatChar(p[1]) == 'h') {
                nModifier = 1;
                ++p;
            } else {
                nModifier = 2;
            }
            c = FormatChar(*++p);
            break;
        case 'j':
            nModifier = 5;
            c = FormatChar(*++p);
            break;
        case 'l':
            if (FormatChar(p[1]) == 'l') {
                nModifier = 4;
                ++p;
            } else {
                nModifier = 3;
            }
            c = FormatChar(*++p);
            break;
        case 't':
            nModifier = 7;
            c = FormatChar(*++p);
            break;
        case 'z':
            nModifier = 6;
            c = FormatChar(*++p);
            break;
        default:
            break;
    }

    nType = (int)c;

    // type-dependent defaults
    switch (c) {
        case 'X': case 'b': case 'd': case 'i': case 'o': case 'u': case 'x':
            if (nPrecision == 0x7fffffff)
                nPrecision = 1;
            else if (nAlignment == 2)
                nAlignment = 1;
            break;
        case 'G': case 'g':
            if (nPrecision == 0)
                nPrecision = 1;
            else if (nPrecision == 0x7fffffff)
                nPrecision = 6;
            break;
        case 'A': case 'E': case 'F': case 'a': case 'e': case 'f':
            if (nPrecision == 0x7fffffff)
                nPrecision = 6;
            break;
        case 'p':
            nModifier = 12;
            nPrecision = 1;
            nType = 'x';
            break;
        case 'C': case 'S': case 'c': case 's':
            if (nAlignment == 2)
                nAlignment = nPrevAlignment;
            if (nModifier == 2)
                nModifier = 1;
            else if (nModifier == 3)
                nModifier = 9;
            else
                nModifier = (c == 's') ? 9 : 1;
            break;
        default:
            break;
    }

done:
    pData->mAlignment = nAlignment;
    pData->mSign = nSign;
    pData->mbAlternativeForm = bAlternativeForm;
    pData->mnWidth = nWidth;
    pData->mnPrecision = nPrecision;
    pData->mModifier = nModifier;
    pData->mnType = nType;
    return p + 1;
}
__declspec(noinline) static const char* ReadFormat8(va_list* pArguments, const char* pFormat,
                                                    FormatData8* pData) {
    return ReadFormatT(pArguments, pFormat, pData);
}
template <typename C>
static __forceinline C* WriteIntegerT(unsigned int nValue, FormatData8* pData, C* pBufferEnd) {
    int nMinDigits = pData->mnPrecision;
    C* p = pBufferEnd - 1;
    int nDigits = 0;
    int nSign = 0;
    bool bNegative = false;
    int nBase;
    int nShift = 0;
    unsigned int nMask = 0;
    C c = 0;

    *p = 0;

    if ((int)nValue <= 0 && pData->mnPrecision <= 0 && pData->mbAlternativeForm == 0)
        return p;

    switch (pData->mnType) {
        case 'X': case 'x': nBase = 16; nShift = 4; nMask = 0xf; break;
        case 'b':           nBase = 2;  nShift = 1; nMask = 1;   break;
        case 'o':           nBase = 8;  nShift = 3; nMask = 7;   break;
        case 'u':           nBase = 10; break;
        default:
            nBase = 10;
            nSign = pData->mSign;
            if ((int)nValue < 0) {
                nValue = (unsigned int)(-(int)nValue);
                bNegative = true;
            }
            break;
    }

    do {
        unsigned int nDigit;
        if (nBase == 10) {
            nDigit = nValue % 10;
            nValue = nValue / 10;
        } else {
            nDigit = nMask & nValue;
            nValue >>= nShift;
        }
        if ((int)nDigit < 10)
            c = (C)(nDigit + '0');
        else if (pData->mnType == 'x')
            c = (C)(nDigit - 10 + 'a');
        else
            c = (C)(nDigit - 10 + 'A');
        *--p = c;
        ++nDigits;
    } while (nValue != 0);

    if (nBase == 8 && pData->mbAlternativeForm && c != '0') {
        *--p = '0';
        ++nDigits;
    }

    if (pData->mAlignment == 2) {
        if (bNegative || nSign != 0)
            nMinDigits = pData->mnWidth - 1;
        else if (pData->mbAlternativeForm && (nBase == 2 || nBase == 16))
            nMinDigits = pData->mnWidth - 2;
        else
            nMinDigits = pData->mnWidth;
    }
    if (nDigits < nMinDigits) {
        int n = nMinDigits - nDigits;
        do {
            *--p = '0';
        } while (--n);
    }

    if (nBase == 10) {
        if (pData->mnType == 'd' || pData->mnType == 'i') {
            if (bNegative) {
                *--p = '-';
            } else if (pData->mSign == 2) {
                *--p = '+';
            } else if (pData->mSign == 3) {
                *--p = ' ';
            }
        }
    } else if (pData->mbAlternativeForm && (nBase == 2 || nBase == 16)) {
        *--p = (C)pData->mnType;
        *--p = '0';
    }
    return p;
}
__declspec(noinline) static char* WriteInteger8(unsigned int nValue, FormatData8* pData, char* pBufferEnd) {
    return WriteIntegerT(nValue, pData, pBufferEnd);
}
// ---- items of slice s00937da0 end

// ---- items of slice s00938bc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(
    unsigned int codePage, unsigned long flags, const char* multi, int multiCount,
    wchar_t* wide, int wideCount);
typedef int (__cdecl *WriteFunction16)(const wchar_t* pData, int nCount, void* pContext);
struct FormatData16 {
    int  mAlignment;          // +0x00  0 = left, 1 = right, 2 = zero-fill
    int  mSign;               // +0x04  1 = minus only, 2 = plus, 3 = space
    char mbAlternativeForm;   // +0x08
    int  mnWidth;             // +0x0c
    int  mnPrecision;         // +0x10  0x7fffffff = not specified
    int  mModifier;           // +0x14
    int  mnType;              // +0x18
};
struct SnprintfContext16 {
    short* mpDestination;     // +0
    int    mnCount;           // +4
    int    mnMaxCount;        // +8
};
int StringWriter16(const wchar_t* pData, int nCount, void* pContext);  // 0x00939910
int EcvtBuf(double dValue, int nDigitCount, int* pnDecimalPoint, int* pnSign, short* pBuffer);   // 0x0092ce80
int FcvtBuf(double dValue, int nDigitCount, int* pnDecimalPoint, int* pnSign, short* pBuffer);   // 0x0092cef0
static int Strlen16(const short* s) {
    const short* p = s;
    while (*p) ++p;
    return (int)(p - s);
}
#define IsNeg(x) ((*((uint64_t*)&(x)) & 0x8000000000000000ULL) != 0)
static inline unsigned int FormatChar16(wchar_t c) { return (unsigned int)c; }
static const wchar_t* ReadFormat16_s0093_8bc0(va_list* pArguments, const wchar_t* pFormat, FormatData16* pData) {
    int nAlignment = 1;
    int nSign = 1;
    char bAlternativeForm = 0;
    int nWidth = 0;
    int nPrecision = 0x7fffffff;
    int nModifier = 0;
    int nType = 0;
    int nPrevAlignment = 0;

    const wchar_t* p = pFormat + 1;
    unsigned int c = FormatChar16(*p);

    if (c == '%') {
        nType = '%';
        goto done;
    }

    while (c - 0x20 <= 0x10) {
        if (c == ' ') {
            if (nSign != 2) nSign = 3;
        } else if (c == '#') {
            bAlternativeForm = 1;
        } else if (c == '+') {
            nSign = 2;
        } else if (c == '-') {
            nAlignment = 0;
        } else if (c == '0') {
            if (nAlignment != 0) {
                if (nAlignment != 2) nPrevAlignment = nAlignment;
                nAlignment = 2;
            }
        } else {
            break;
        }
        c = FormatChar16(*++p);
    }

    if (c == '*') {
        nWidth = va_arg(*pArguments, int);
        if (nWidth < 0) { nWidth = -nWidth; nAlignment = 0; }
        c = FormatChar16(*++p);
        if (nWidth > 0x400) goto done;
    } else if (c - '0' < 10) {
        do {
            nWidth = nWidth * 10 + (c - '0');
            c = FormatChar16(*++p);
        } while (c - '0' < 10);
        if (nWidth > 0x400) goto done;
    }

    if (c == '.') {
        c = FormatChar16(*++p);
        if (c == '*') {
            nPrecision = va_arg(*pArguments, int);
            if (nPrecision < 0) nPrecision = 0;
            c = FormatChar16(*++p);
        } else {
            nPrecision = 0;
            while (c - '0' < 10) {
                nPrecision = nPrecision * 10 + (c - '0');
                c = FormatChar16(*++p);
            }
        }
        if (nPrecision > 0x400 && nPrecision != 0x7fffffff) goto done;
    }

    switch (c) {
        case 'I': {
            unsigned int c1 = FormatChar16(p[1]);
            if (c1 == '8') { nModifier = 10; ++p; }
            else if (c1 == '1' && FormatChar16(p[2]) == '6') { nModifier = 11; p += 2; }
            else if (c1 == '3' && FormatChar16(p[2]) == '2') { nModifier = 12; p += 2; }
            else if (c1 == '6' && FormatChar16(p[2]) == '4') { nModifier = 13; p += 2; }
            else if (c1 == '1' && FormatChar16(p[2]) == '2' && FormatChar16(p[3]) == '8') { nModifier = 14; p += 3; }
            else goto done;
            c = FormatChar16(*++p);
            break;
        }
        case 'L': nModifier = 8; c = FormatChar16(*++p); break;
        case 'h':
            if (FormatChar16(p[1]) == 'h') { nModifier = 1; ++p; } else { nModifier = 2; }
            c = FormatChar16(*++p);
            break;
        case 'j': nModifier = 5; c = FormatChar16(*++p); break;
        case 'l':
            if (FormatChar16(p[1]) == 'l') { nModifier = 4; ++p; } else { nModifier = 3; }
            c = FormatChar16(*++p);
            break;
        case 't': nModifier = 7; c = FormatChar16(*++p); break;
        case 'z': nModifier = 6; c = FormatChar16(*++p); break;
        default: break;
    }

    nType = (int)c;

    switch (c) {
        case 'X': case 'b': case 'd': case 'i': case 'o': case 'u': case 'x':
            if (nPrecision == 0x7fffffff) nPrecision = 1;
            else if (nAlignment == 2) nAlignment = 1;
            break;
        case 'G': case 'g':
            if (nPrecision == 0) nPrecision = 1;
            else if (nPrecision == 0x7fffffff) nPrecision = 6;
            break;
        case 'A': case 'E': case 'F': case 'a': case 'e': case 'f':
            if (nPrecision == 0x7fffffff) nPrecision = 6;
            break;
        case 'p':
            nModifier = 12;
            nPrecision = 1;
            nType = 'x';
            break;
        case 'C': case 'S': case 'c': case 's':
            if (nAlignment == 2) nAlignment = nPrevAlignment;
            if (nModifier == 2) nModifier = 1;
            else if (nModifier == 3) nModifier = 9;
            else nModifier = (c == 's') ? 9 : 1;
            break;
        default: break;
    }

done:
    pData->mAlignment = nAlignment;
    pData->mSign = nSign;
    pData->mbAlternativeForm = bAlternativeForm;
    pData->mnWidth = nWidth;
    pData->mnPrecision = nPrecision;
    pData->mModifier = nModifier;
    pData->mnType = nType;
    return p + 1;
}
static short* WriteInteger16_s0093_8bc0(unsigned int nValue, FormatData16* pData, short* pBufferEnd) {
    int nMinDigits = pData->mnPrecision;
    short* p = pBufferEnd - 1;
    int nDigits = 0;
    int nSign = 0;
    bool bNegative = false;
    int nBase;
    int nShift = 0;
    unsigned int nMask = 0;
    short c = 0;

    *p = 0;

    if ((int)nValue <= 0 && pData->mnPrecision <= 0 && pData->mbAlternativeForm == 0)
        return p;

    switch (pData->mnType) {
        case 'X': case 'x': nBase = 16; nShift = 4; nMask = 0xf; break;
        case 'b':           nBase = 2;  nShift = 1; nMask = 1;   break;
        case 'o':           nBase = 8;  nShift = 3; nMask = 7;   break;
        case 'u':           nBase = 10; break;
        default:
            nBase = 10;
            nSign = pData->mSign;
            if ((int)nValue < 0) { nValue = (unsigned int)(-(int)nValue); bNegative = true; }
            break;
    }

    do {
        unsigned int nDigit;
        if (nBase == 10) { nDigit = nValue % 10; nValue = nValue / 10; }
        else { nDigit = nMask & nValue; nValue >>= nShift; }
        if ((int)nDigit < 10) c = (short)(nDigit + '0');
        else if (pData->mnType == 'x') c = (short)(nDigit - 10 + 'a');
        else c = (short)(nDigit - 10 + 'A');
        *--p = c;
        ++nDigits;
    } while (nValue != 0);

    if (nBase == 8 && pData->mbAlternativeForm && c != '0') { *--p = '0'; ++nDigits; }

    if (pData->mAlignment == 2) {
        if (bNegative || nSign != 0) nMinDigits = pData->mnWidth - 1;
        else if (pData->mbAlternativeForm && (nBase == 2 || nBase == 16)) nMinDigits = pData->mnWidth - 2;
        else nMinDigits = pData->mnWidth;
    }
    if (nDigits < nMinDigits) {
        int n = nMinDigits - nDigits;
        do { *--p = '0'; } while (--n);
    }

    if (nBase == 10) {
        if (pData->mnType == 'd' || pData->mnType == 'i') {
            if (bNegative) *--p = '-';
            else if (pData->mSign == 2) *--p = '+';
            else if (pData->mSign == 3) *--p = ' ';
        }
    } else if (pData->mbAlternativeForm && (nBase == 2 || nBase == 16)) {
        *--p = (short)pData->mnType;
        *--p = '0';
    }
    return p;
}
// ---- items of slice s00938bc0 end

// ---- items of slice s00939a60 begin
extern "C" unsigned short _byteswap_ushort(unsigned short);
extern "C" unsigned long  _byteswap_ulong(unsigned long);
extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(_byteswap_ushort, _byteswap_ulong)
#pragma intrinsic(__rdtsc)
// ---- items of slice s00939a60 end

// @ 0x00937da0
__declspec(noinline) static int VprintfCore8(const char* pFormat, WriteFunction8 pWriteFunction, void* pContext, va_list arguments)
{
    FormatData8 fd;
    fd.mAlignment = 1;
    fd.mSign = 1;
    fd.mbAlternativeForm = 0;
    fd.mnWidth = 0;
    fd.mnPrecision = 0x7fffffff;
    fd.mModifier = 0;
    fd.mnType = 0;

    int nCount = 0;
    int nValue = 0;            // signed 32-bit argument slot
    unsigned int uValue = 0;   // unsigned 32-bit argument slot
    char szBuffer[0x408];
    char cPad;
    const char* pCur = pFormat;

    while (*pCur) {
        const char* pSpec = pCur;
        while (*pSpec && *pSpec != '%')
            ++pSpec;
        int nRun = (int)(pSpec - pCur);
        if (nRun) {
            if (pWriteFunction(pCur, nRun, pContext) == -1)
                return -1;
            nCount += nRun;
            pCur = pSpec;
        }
        if (*pSpec == 0)
            continue;

        pCur = ReadFormat8(&arguments, pSpec, &fd);

        const char* pOut = szBuffer;
        int nOut = 0;
        char* pStart;

        switch (fd.mnType) {
            case '%':
                szBuffer[0] = '%';
                nOut = 1;
                break;

            case 'd': case 'i': {
                int nMod = fd.mModifier;
                if (nMod == 4) goto signed64;
                if (nMod == 3 || nMod == 8) {
                    nValue = va_arg(arguments, int);
                } else if (nMod == 0xd) {
                    fd.mModifier = 4;
                    goto signed64;
                } else if (nMod == 0xe) {
                    arguments += 16;
                } else {
                    nValue = va_arg(arguments, int);
                    if (nMod == 2 || nMod == 0xb)
                        nValue = (short)nValue;
                    else if (nMod == 1 || nMod == 0xa)
                        nValue = (signed char)nValue;
                }
                pStart = WriteInteger8((unsigned int)nValue, &fd, szBuffer + 0x408);
                goto haveString;
            }

            case 'X': case 'b': case 'o': case 'u': case 'x': {
                int nMod = fd.mModifier;
                if (nMod == 3) {
                    uValue = va_arg(arguments, unsigned int);
                } else if (nMod == 4) {
                    goto signed64;
                } else if (nMod == 0xd) {
                    fd.mModifier = 4;
                    goto signed64;
                } else if (nMod == 0xe) {
                    arguments += 16;
                } else {
                    uValue = va_arg(arguments, unsigned int);
                    if (nMod == 2 || nMod == 0xb)
                        uValue = (unsigned short)uValue;
                    else if (nMod == 1 || nMod == 0xa)
                        uValue = (unsigned char)uValue;
                }
                pStart = WriteInteger8(uValue, &fd, szBuffer + 0x408);
                goto haveString;
            }

            signed64: {
                unsigned long long nValue64 = va_arg(arguments, unsigned long long);
                pStart = WriteInteger64_8(&fd, (unsigned int)nValue64, (unsigned int)(nValue64 >> 32),
                                          szBuffer + 0x408);
                goto haveString;
            }

            case 'A': case 'E': case 'F': case 'G': case 'a': case 'e': case 'f': case 'g': {
                double dValue = va_arg(arguments, double);
                pStart = WriteDouble8(&fd, dValue, szBuffer + 0x408);
                goto haveString;
            }

            haveString:
                if (!pStart)
                    goto invalidSpec;
                pOut = pStart;
                nOut = (int)((szBuffer + 0x407) - pStart);
                break;

            case 'S': case 's':
                if (fd.mModifier == 9) {
                    const wchar_t* pWide = va_arg(arguments, const wchar_t*);
                    if (!pWide)
                        pWide = L"(null)";
                    const wchar_t* pEnd = pWide;
                    if (fd.mnPrecision == 0x7fffffff) {
                        while (*pEnd)
                            ++pEnd;
                    } else {
                        const wchar_t* pLimit = pWide + fd.mnPrecision;
                        if (*pWide) {
                            while (pEnd < pLimit) {
                                ++pEnd;
                                if (!*pEnd)
                                    break;
                            }
                        }
                    }
                    nOut = (int)(pEnd - pWide);
                    if (nOut > 0) {
                        nOut = WideCharToMultiByte(0xfde9, 0, pWide, nOut, szBuffer, 0x408, 0, 0);
                        if (nOut < 0)
                            goto invalidSpec;
                    }
                } else {
                    const char* pStr = va_arg(arguments, const char*);
                    if (!pStr)
                        pStr = "(null)";
                    const char* pEnd = pStr;
                    if (fd.mnPrecision == 0x7fffffff) {
                        while (*pEnd)
                            ++pEnd;
                    } else {
                        const char* pLimit = pStr + fd.mnPrecision;
                        if (*pStr) {
                            while (pEnd < pLimit) {
                                ++pEnd;
                                if (!*pEnd)
                                    break;
                            }
                        }
                    }
                    pOut = pStr;
                    nOut = (int)(pEnd - pStr);
                }
                break;

            case 'C': case 'c':
                nOut = 1;
                if (fd.mModifier == 9)
                    szBuffer[0] = (char)va_arg(arguments, int);
                else
                    szBuffer[0] = (char)va_arg(arguments, int);
                break;

            case 'n': {
                int* pn = va_arg(arguments, int*);
                switch (fd.mModifier) {
                    case 1: *(char*)pn = (char)nCount; break;
                    case 2: *(short*)pn = (short)nCount; break;
                    case 3: *pn = nCount; break;
                    case 4: *(long long*)pn = (long long)nCount; break;
                    default: *pn = nCount; break;
                }
                continue;
            }

            default:
            invalidSpec: {
                // unrecognised or failed spec: emit the spec text verbatim
                int nLen = (int)(pCur - pSpec);
                nCount += nLen;
                if (nLen) {
                    if (pWriteFunction(pSpec, nLen, pContext) == -1)
                        return -1;
                }
                continue;
            }
        }

        // width / alignment padding around the converted text
        {
            int nWidth = fd.mnWidth;
            int nTotal = nOut;
            if (fd.mAlignment != 0) {
                if (fd.mAlignment == 2) {
                    cPad = '0';
                    if (pOut) {
                        char c = *pOut;
                        if (c == '+' || c == '-' || c == ' ') {
                            if (pWriteFunction(pOut, 1, pContext) == -1)
                                return -1;
                            --nOut;
                            ++pOut;
                        }
                    }
                } else {
                    cPad = ' ';
                }
                while (nTotal < nWidth) {
                    if (pWriteFunction(&cPad, 1, pContext) == -1)
                        return -1;
                    ++nTotal;
                }
            }
            if (nOut) {
                if (pWriteFunction(pOut, nOut, pContext) == -1)
                    return -1;
            }
            if (fd.mAlignment == 0) {
                cPad = ' ';
                while (nTotal < nWidth) {
                    if (pWriteFunction(&cPad, 1, pContext) == -1)
                        return -1;
                    ++nTotal;
                }
            }
            nCount += nTotal;
        }
    }
    return nCount;
}

// @ 0x00938400
namespace  {
int Vsnprintf8(char * pDestination, unsigned int n, char const * pFormat, char * arguments)
{
    SnprintfContext8 context;
    context.mpDestination = pDestination;
    context.mnCount = 0;
    context.mnMaxCount = pDestination ? (int)n : 0;
    context.mbMaxCountReached = 0;
    int result = VprintfCore8(pFormat, StringWriter8, &context, arguments);
    if (pDestination && result >= 0) {
        if ((unsigned int)result < n)
            pDestination[result] = 0;
        else if (n > 0)
            pDestination[n - 1] = 0;
    }
    return result;
}
}  // namespace 

// @ 0x00938470
int Sprintf8(char* pDestination, const char* pFormat, ...)
{
    va_list arguments;
    va_start(arguments, pFormat);
    SnprintfContext8 context;
    context.mpDestination = pDestination;
    context.mnCount = 0;
    context.mnMaxCount = pDestination ? 0x7fffffff : 0;
    context.mbMaxCountReached = 0;
    int result = VprintfCore8(pFormat, StringWriter8, &context, arguments);
    if (pDestination && result >= 0) {
        if ((unsigned)result < 0x7fffffff)
            pDestination[result] = 0;
        else
            pDestination[0x7ffffffe] = 0;
    }
    return result;
}

// @ 0x009384e0
int Snprintf8(char* pDestination, unsigned int n, const char* pFormat, ...)
{
    va_list arguments;
    va_start(arguments, pFormat);
    return Vsnprintf8(pDestination, n, pFormat, arguments);
}

// @ 0x00938500
__declspec(noinline) static const wchar_t* ReadFormat16(va_list* pArguments, const wchar_t* pFormat, FormatData8* pData)
{
    return ReadFormatT(pArguments, pFormat, pData);
}

// @ 0x00938980
__declspec(noinline) static short* WriteInteger16(unsigned int nValue, FormatData8* pData, short* pBufferEnd)
{
    return WriteIntegerT(nValue, pData, pBufferEnd);
}

// @ 0x00938bc0
static short* WriteInteger64_16(FormatData16* fd, long long lValue, short* pBufferEnd)
{
    unsigned long long ulValue = (unsigned long long)lValue;
    unsigned int nBase;
    unsigned int nShift = 0;
    unsigned int nAnd = 0;
    int nSign = 0;
    short* pCurrent = pBufferEnd;
    int nDigitCount = 0;
    int nDigitCountSum = fd->mnPrecision;
    bool bNegative = false;

    *--pCurrent = 0;

    if ((lValue > 0) || (fd->mnPrecision > 0) || fd->mbAlternativeForm) {
        switch (fd->mnType) {
            case 'b': nBase = 2;  nShift = 1; nAnd = 1;   break;
            case 'o': nBase = 8;  nShift = 3; nAnd = 7;   break;
            case 'd': case 'i': default:
                nBase = 10;
                nSign = fd->mSign;
                if (lValue < 0) { ulValue = (unsigned long long)-lValue; bNegative = true; }
                break;
            case 'u': nBase = 10; break;
            case 'x': case 'X': nBase = 16; nShift = 4; nAnd = 0x0f; break;
        }

        do {
            int nDigit;
            if (nBase == 10) { nDigit = (int)(ulValue % nBase); ulValue /= nBase; }
            else { nDigit = (int)(ulValue & nAnd); ulValue >>= nShift; }
            if (nDigit < 10) nDigit = '0' + nDigit;
            else { nDigit -= 10; if (fd->mnType == 'x') nDigit = 'a' + nDigit; else nDigit = 'A' + nDigit; }
            *--pCurrent = (short)nDigit;
            ++nDigitCount;
        } while (ulValue > 0);

        if ((nBase == 8) && fd->mbAlternativeForm && (*pCurrent != '0')) { *--pCurrent = '0'; ++nDigitCount; }

        if (fd->mAlignment == 2) {
            if (bNegative || (nSign != 0)) nDigitCountSum = fd->mnWidth - 1;
            else if (fd->mbAlternativeForm && ((nBase == 2) || (nBase == 16))) nDigitCountSum = fd->mnWidth - 2;
            else nDigitCountSum = fd->mnWidth;
        }
        while (nDigitCount < nDigitCountSum) { *--pCurrent = '0'; ++nDigitCount; }

        if (nBase == 10) {
            if ((fd->mnType == 'd') || (fd->mnType == 'i')) {
                if (bNegative) *--pCurrent = '-';
                else if (fd->mSign == 2) *--pCurrent = '+';
                else if (fd->mSign == 3) *--pCurrent = ' ';
            }
        } else if (fd->mbAlternativeForm && ((nBase == 2) || (nBase == 16))) {
            *--pCurrent = (short)fd->mnType;
            *--pCurrent = '0';
        }
    }
    return pCurrent;
}

// @ 0x00938e60
static short* WriteDouble16(FormatData16* fd, double dValue, short* pBufferEnd)
{
    if (_isnan(dValue)) {
        *--pBufferEnd = 0;
        if (fd->mnType >= 'a') { *--pBufferEnd = 'n'; *--pBufferEnd = 'a'; *--pBufferEnd = 'n'; }
        else { *--pBufferEnd = 'N'; *--pBufferEnd = 'A'; *--pBufferEnd = 'N'; }
        if (IsNeg(dValue)) *--pBufferEnd = '-';
        return pBufferEnd;
    }
    if (!_finite(dValue)) {
        *--pBufferEnd = 0;
        if (fd->mnType >= 'a') { *--pBufferEnd = 'f'; *--pBufferEnd = 'n'; *--pBufferEnd = 'i'; }
        else { *--pBufferEnd = 'F'; *--pBufferEnd = 'N'; *--pBufferEnd = 'I'; }
        if (IsNeg(dValue)) *--pBufferEnd = '-';
        return pBufferEnd;
    }

    int nType = fd->mnType;
    int nPrecision = fd->mnPrecision;
    bool bStripTrailingZeroes = false;
    bool bStripPointlessDecimal = false;
    short* pResult = 0;

    *--pBufferEnd = 0;

    if (nPrecision <= 0x408) {
        int nDecimalPoint, nSign, nExponent;
        short pBufferCvt[0x15f];
        pBufferCvt[0] = 0;
        int nBufferLength;
        short* pCurrent = pBufferEnd;

        switch (nType) {
            default:
            case 'g':
            case 'G': {
                EcvtBuf(dValue, nPrecision, &nDecimalPoint, &nSign, pBufferCvt);
                nExponent = nDecimalPoint - 1;
                if (!fd->mbAlternativeForm) bStripTrailingZeroes = true;
                bStripPointlessDecimal = true;
                if (!((nExponent < -4) || (nExponent >= nPrecision))) {
                    if (nExponent >= 0) nPrecision -= (nExponent + 1);
                    goto FType;
                }
                if (nType == 'g') nType = 'e';
                else nType = 'E';
                goto EContinuation;
            }
            case 'e':
            case 'E': {
                EcvtBuf(dValue, nPrecision + 1, &nDecimalPoint, &nSign, pBufferCvt);
                nExponent = nDecimalPoint - 1;
                if (dValue == 0) nExponent = 0;
            EContinuation:
                nBufferLength = Strlen16(pBufferCvt);
                {
                    int nExponentAbs = nExponent < 0 ? -nExponent : nExponent;
                    while (nExponentAbs > 0) { *--pCurrent = (short)('0' + (nExponentAbs % 10)); nExponentAbs /= 10; }
                }
                if (pCurrent >= (pBufferEnd - 1)) *--pCurrent = '0';
                if (pCurrent >= (pBufferEnd - 1)) *--pCurrent = '0';
                if (nExponent >= 0) *--pCurrent = '+';
                else *--pCurrent = '-';
                *--pCurrent = (short)nType;
                for (short* pTemp = pBufferCvt + nBufferLength; pTemp > pBufferCvt + 1; ) {
                    const short c = *--pTemp;
                    if (c != '0') bStripTrailingZeroes = false;
                    if ((c != '0') || !bStripTrailingZeroes) *--pCurrent = c;
                }
                if ((*pCurrent != (short)nType) || !bStripPointlessDecimal) {
                    if ((nBufferLength > 1) || fd->mbAlternativeForm) *--pCurrent = '.';
                }
                *--pCurrent = pBufferCvt[0];
                break;
            }
            case 'f':
            case 'F':
            FType: {
                FcvtBuf(dValue, nPrecision, &nDecimalPoint, &nSign, pBufferCvt);
                nBufferLength = Strlen16(pBufferCvt);
                if (fd->mbAlternativeForm && (nDecimalPoint >= nBufferLength) && !bStripPointlessDecimal)
                    *--pCurrent = '.';
                const short* pDecimalPoint = pBufferCvt + nDecimalPoint - 1;
                const short* pCurrentSource = pBufferCvt + nBufferLength - 1;
                if ((pCurrentSource - pDecimalPoint) > nPrecision) pCurrentSource = pDecimalPoint + nPrecision;
                while (pCurrentSource > pDecimalPoint) {
                    short c;
                    if ((pCurrentSource >= pBufferCvt) && (pCurrentSource <= (pBufferCvt + nBufferLength)))
                        c = *pCurrentSource;
                    else
                        c = '0';
                    if (c != '0') bStripTrailingZeroes = false;
                    if ((c != '0') || !bStripTrailingZeroes) *--pCurrent = c;
                    --pCurrentSource;
                }
                if (*pCurrent || !bStripPointlessDecimal) {
                    if (nDecimalPoint < nBufferLength) *--pCurrent = '.';
                }
                if (nDecimalPoint > 0) {
                    pCurrentSource = pBufferCvt + nDecimalPoint;
                    while (pCurrentSource > pBufferCvt) *--pCurrent = *--pCurrentSource;
                } else {
                    *--pCurrent = '0';
                }
                break;
            }
        }

        if (nSign) *--pCurrent = '-';
        else if (fd->mSign == 2) *--pCurrent = '+';
        else if (fd->mSign == 3) *--pCurrent = ' ';

        if (fd->mAlignment == 1) {
            int nWidth = (int)(pBufferEnd - pCurrent);
            while (nWidth < fd->mnWidth) { *--pCurrent = ' '; ++nWidth; }
        }
        pResult = pCurrent;
    }
    return pResult;
}

// @ 0x00939320
static int VprintfCore16(const wchar_t* pFormat, WriteFunction16 pWriteFunction, void* pContext, va_list arguments)
{
    FormatData16 fd;
    fd.mAlignment = 1;
    fd.mSign = 1;
    fd.mbAlternativeForm = 0;
    fd.mnWidth = 0;
    fd.mnPrecision = 0x7fffffff;
    fd.mModifier = 0;
    fd.mnType = 0;

    int nCount = 0;
    short szBuffer[0x408];
    const wchar_t* pCur = pFormat;

    while (*pCur) {
        const wchar_t* pSpec = pCur;
        while (*pSpec && *pSpec != '%') ++pSpec;
        int nRun = (int)(pSpec - pCur);
        if (nRun) {
            if (pWriteFunction(pCur, nRun, pContext) == -1) return -1;
            nCount += nRun;
            pCur = pSpec;
        }
        if (*pSpec == 0) break;

        pCur = ReadFormat16_s0093_8bc0(&arguments, pSpec, &fd);

        short* pOut = szBuffer;
        int nOut = 0;
        bool bNarrowString = false;

        switch (fd.mnType) {
            case '%':
                szBuffer[0] = '%';
                nOut = 1;
                break;

            case 'd':
            case 'i': {
                if (fd.mModifier == 4) goto signed64;
                long long v;
                if (fd.mModifier == 3 || fd.mModifier == 8) v = va_arg(arguments, int);
                else if (fd.mModifier == 0xd) { fd.mModifier = 4; goto signed64; }
                else if (fd.mModifier == 0xe) { arguments += 16; v = 0; }
                else {
                    v = va_arg(arguments, int);
                    if (fd.mModifier == 2 || fd.mModifier == 0xb) v = (short)v;
                    else if (fd.mModifier == 1 || fd.mModifier == 0xa) v = (signed char)v;
                }
                pOut = WriteInteger16_s0093_8bc0((unsigned int)v, &fd, szBuffer + 0x408);
                goto haveString;
            }

            case 'X': case 'b': case 'o': case 'u': case 'x': {
                if (fd.mModifier == 3) {
                    unsigned int v = va_arg(arguments, unsigned int);
                    pOut = WriteInteger16_s0093_8bc0(v, &fd, szBuffer + 0x408);
                    goto haveString;
                }
                if (fd.mModifier == 4) goto signed64;
                if (fd.mModifier == 0xd) { fd.mModifier = 4; goto signed64; }
                if (fd.mModifier == 0xe) { arguments += 16; }
                else {
                    unsigned int v = va_arg(arguments, unsigned int);
                    if (fd.mModifier == 2 || fd.mModifier == 0xb) v = (unsigned short)v;
                    else if (fd.mModifier == 1 || fd.mModifier == 0xa) v = (unsigned char)v;
                    pOut = WriteInteger16_s0093_8bc0(v, &fd, szBuffer + 0x408);
                    goto haveString;
                }
            signed64: {
                long long ll = va_arg(arguments, long long);
                pOut = WriteInteger64_16(&fd, ll, szBuffer + 0x408);
                goto haveString;
            }
            }

            case 'A': case 'E': case 'F': case 'G': case 'a': case 'e': case 'f': case 'g': {
                double dValue = va_arg(arguments, double);
                pOut = WriteDouble16(&fd, dValue, szBuffer + 0x408);
                goto haveString;
            }

            haveString:
                if (pOut) {
                    nOut = (int)((szBuffer + 0x407) - pOut);
                } else {
                    nOut = 0;
                }
                break;

            case 'S':
            case 's':
                if (fd.mModifier == 9) {
                    const wchar_t* pWide = va_arg(arguments, const wchar_t*);
                    if (!pWide) pWide = L"(null)";
                    const wchar_t* pEnd = pWide;
                    if (fd.mnPrecision == 0x7fffffff) { while (*pEnd) ++pEnd; }
                    else {
                        const wchar_t* pLimit = pWide + fd.mnPrecision;
                        if (*pWide) { while (pEnd < pLimit) { ++pEnd; if (!*pEnd) break; } }
                    }
                    pOut = (short*)pWide;
                    nOut = (int)(pEnd - pWide);
                } else {
                    const char* pStr = va_arg(arguments, const char*);
                    if (!pStr) pStr = "(null)";
                    const char* pEnd = pStr;
                    if (fd.mnPrecision == 0x7fffffff) { while (*pEnd) ++pEnd; }
                    else {
                        const char* pLimit = pStr + fd.mnPrecision;
                        if (*pStr) { while (pEnd < pLimit) { ++pEnd; if (!*pEnd) break; } }
                    }
                    int nLen = (int)(pEnd - pStr);
                    if (nLen > 0) {
                        nOut = MultiByteToWideChar(0xfde9, 0, pStr, nLen, (wchar_t*)szBuffer, 0x408);
                        if (nOut < 0) goto invalidSpec;
                        pOut = szBuffer;
                    } else {
                        nOut = 0;
                    }
                }
                bNarrowString = false;
                break;

            case 'C': case 'c':
                nOut = 1;
                if (fd.mModifier == 9) szBuffer[0] = (short)va_arg(arguments, int);
                else szBuffer[0] = (short)(unsigned char)va_arg(arguments, int);
                pOut = szBuffer;
                break;

            case 'n': {
                int* pn = va_arg(arguments, int*);
                switch (fd.mModifier) {
                    case 1: case 2: *(short*)pn = (short)nCount; break;
                    case 3: *pn = nCount; break;
                    case 4: *(long long*)pn = (long long)nCount; break;
                    default: *pn = nCount; break;
                }
                continue;
            }

            default:
            invalidSpec: {
                int nLen = (int)(pCur - pSpec);
                nCount += nLen;
                if (nLen && pWriteFunction(pSpec, nLen, pContext) == -1) return -1;
                continue;
            }
        }
        (void)bNarrowString;

        {
            int nWidth = fd.mnWidth;
            int nTotal = nOut;
            if (fd.mAlignment != 0) {
                short cPad;
                if (fd.mAlignment == 2) {
                    cPad = '0';
                    if (pOut) {
                        short c = *pOut;
                        if (c == '+' || c == '-' || c == ' ') {
                            if (pWriteFunction((wchar_t*)pOut, 1, pContext) == -1) return -1;
                            --nOut;
                            ++pOut;
                        }
                    }
                } else {
                    cPad = ' ';
                }
                while (nTotal < nWidth) {
                    if (pWriteFunction((wchar_t*)&cPad, 1, pContext) == -1) return -1;
                    ++nTotal;
                }
            }
            if (nOut) {
                if (pWriteFunction((wchar_t*)pOut, nOut, pContext) == -1) return -1;
            }
            if (fd.mAlignment == 0) {
                short cPad = ' ';
                while (nTotal < nWidth) {
                    if (pWriteFunction((wchar_t*)&cPad, 1, pContext) == -1) return -1;
                    ++nTotal;
                }
            }
            nCount += nTotal;
        }
    }
    return nCount;
}

// @ 0x00939950
int Vsnprintf16(short* pDestination, unsigned int n, const wchar_t* pFormat, va_list arguments)
{
    SnprintfContext16 context;
    context.mpDestination = pDestination;
    context.mnCount = 0;
    context.mnMaxCount = pDestination ? (int)n : 0;
    int result = VprintfCore16(pFormat, StringWriter16, &context, arguments);
    if (pDestination && result >= 0) {
        if ((unsigned int)result < n)
            pDestination[result] = 0;
        else if (n > 0)
            pDestination[n - 1] = 0;
    }
    return result;
}

// @ 0x009399c0
int Sprintf16(short* pDestination, const wchar_t* pFormat, ...)
{
    va_list arguments;
    va_start(arguments, pFormat);
    SnprintfContext16 context;
    context.mpDestination = pDestination;
    context.mnCount = 0;
    context.mnMaxCount = pDestination ? 0x7fffffff : 0;
    int result = VprintfCore16(pFormat, StringWriter16, &context, arguments);
    if (pDestination && result >= 0) {
        if ((unsigned int)result < 0x7fffffff)
            pDestination[result] = 0;
        else
            pDestination[0x7ffffffe] = 0;
    }
    return result;
}

// @ 0x00939a30
int Snprintf16(short* pDestination, unsigned int n, const wchar_t* pFormat, ...)
{
    va_list arguments;
    va_start(arguments, pFormat);
    return Vsnprintf16(pDestination, n, pFormat, arguments);
}

// @ 0x00939a60
int ParseFormatToken(const char* p, char* out)
{
    (void)p;
    (void)out;
    return 0;
}
