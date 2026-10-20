// Slice s009370d0: EAStdC 8-bit printf format helpers (MSVC 2008 SP1, /O2 /MD /Gy /TP /GS-).
//
//   009370d0  ReadFormat8      (format-spec parser, char)
//   00937510  WriteInteger8    (integer -> char string)
//   00937720  WriteInteger64_8 (64-bit integer -> char string)
//   00937970  WriteDouble8     (double -> char string, %e/%f/%g)
//
// ReadFormat8 / WriteInteger8 / WriteInteger64_8 / WriteDouble8 are TU-static helpers of the
// EAStdC EASprintf engine (real 2008 dev-build PDB names).  The first two are called by
// VprintfCore8 with cl's register convention for internal-linkage functions; the last two are
// plain cdecl helpers.  Stand-in callers at the bottom force cl to emit every one of them.
#include "types.h"
#include <stdarg.h>
#include <float.h>

// ---------------------------------------------------------------------------------------------
// Format descriptor filled in by ReadFormat8 (exactly seven dwords copied out of its locals).
// ---------------------------------------------------------------------------------------------
struct FormatData8 {
    int  mAlignment;          // +0x00  0 = left, 1 = right, 2 = zero-fill
    int  mSign;               // +0x04  1 = minus only, 2 = plus, 3 = space
    char mbAlternativeForm;   // +0x08
    int  mnWidth;             // +0x0c
    int  mnPrecision;         // +0x10  INT_MAX = not specified
    int  mModifier;           // +0x14
    int  mnType;              // +0x18
};

// Decimal converters used by WriteDouble8 (EcvtCopy 0x92ce00 / FcvtCopy 0x92ce40).
extern "C" char* __cdecl EcvtCopy(double dValue, int nDigitCount, int* pnDecimalPoint, int* pnSign,
                                  char* pBuffer);   // 0x0092ce00
extern "C" char* __cdecl FcvtCopy(double dValue, int nDigitCount, int* pnDecimalPoint, int* pnSign,
                                  char* pBuffer);   // 0x0092ce40

static inline unsigned int FormatChar(char c) { return (unsigned char)c; }

static int Strlen8(const char* s) {
    const char* p = s;
    while (*p) ++p;
    return (int)(p - s);
}

#define IsNeg(x) ((*((const uint32_t*)&(x) + 1) & 0x80000000u) != 0)

// ---------------------------------------------------------------------------------------------
// Shared char format-spec parser body (inlined into ReadFormat8).
// ---------------------------------------------------------------------------------------------
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

// @ 0x009370d0
__declspec(noinline) static const char* ReadFormat8(va_list* pArguments, const char* pFormat,
                                                    FormatData8* pData) {
    return ReadFormatT(pArguments, pFormat, pData);
}

// ---------------------------------------------------------------------------------------------
// Shared integer -> char string body (inlined into WriteInteger8).
// ---------------------------------------------------------------------------------------------
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

// @ 0x00937510
__declspec(noinline) static char* WriteInteger8(unsigned int nValue, FormatData8* pData,
                                                char* pBufferEnd) {
    return WriteIntegerT(nValue, pData, pBufferEnd);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00937720  WriteInteger64_8: 64-bit integer -> char string.
// ---------------------------------------------------------------------------------------------
static char* WriteInteger64_8(FormatData8* fd, long long lValue, char* pBufferEnd) {
    unsigned long long ulValue = (unsigned long long)lValue;
    unsigned int nBase;
    unsigned int nShift = 0;
    unsigned int nAnd = 0;
    int nSign = 0;
    char* pCurrent = pBufferEnd;
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
            *--pCurrent = (char)nDigit;
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
            *--pCurrent = (char)fd->mnType;
            *--pCurrent = '0';
        }
    }
    return pCurrent;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00937970  WriteDouble8: double -> char string.
// ---------------------------------------------------------------------------------------------
static char* WriteDouble8(FormatData8* fd, double dValue, char* pBufferEnd) {
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
    char* pResult = 0;

    *--pBufferEnd = 0;

    if (nPrecision <= 0x408) {
        int nDecimalPoint, nSign, nExponent;
        char pBufferCvt[0x160];
        pBufferCvt[0] = 0;
        int nBufferLength;
        char* pCurrent = pBufferEnd;

        switch (nType) {
            default:
            case 'g':
            case 'G': {
                EcvtCopy(dValue, nPrecision, &nDecimalPoint, &nSign, pBufferCvt);
                nExponent = nDecimalPoint - 1;
                if (!fd->mbAlternativeForm) bStripTrailingZeroes = true;
                bStripPointlessDecimal = true;
                if (!((nExponent < -4) || (nExponent >= nPrecision))) {
                    goto FType;
                }
                if (nType == 'g') nType = 'e';
                else nType = 'E';
                goto EContinuation;
            }
            case 'e':
            case 'E': {
                EcvtCopy(dValue, nPrecision + 1, &nDecimalPoint, &nSign, pBufferCvt);
                nExponent = nDecimalPoint - 1;
                if (dValue == 0) nExponent = 0;
            EContinuation:
                nBufferLength = Strlen8(pBufferCvt);
                {
                    int nExponentAbs = nExponent < 0 ? -nExponent : nExponent;
                    while (nExponentAbs > 0) { *--pCurrent = (char)('0' + (nExponentAbs % 10)); nExponentAbs /= 10; }
                }
                if (pCurrent >= (pBufferEnd - 1)) *--pCurrent = '0';
                if (pCurrent >= (pBufferEnd - 1)) *--pCurrent = '0';
                if (nExponent >= 0) *--pCurrent = '+';
                else *--pCurrent = '-';
                *--pCurrent = (char)nType;
                for (char* pTemp = pBufferCvt + nBufferLength; pTemp > pBufferCvt + 1; ) {
                    const char c = *--pTemp;
                    if (c != '0') bStripTrailingZeroes = false;
                    if ((c != '0') || !bStripTrailingZeroes) *--pCurrent = c;
                }
                if ((*pCurrent != (char)nType) || !bStripPointlessDecimal) {
                    if ((nBufferLength > 1) || fd->mbAlternativeForm) *--pCurrent = '.';
                }
                *--pCurrent = pBufferCvt[0];
                break;
            }
            case 'f':
            case 'F':
            FType: {
                FcvtCopy(dValue, nPrecision, &nDecimalPoint, &nSign, pBufferCvt);
                nBufferLength = Strlen8(pBufferCvt);
                if (fd->mbAlternativeForm && (nDecimalPoint >= nBufferLength) && !bStripPointlessDecimal)
                    *--pCurrent = '.';
                const char* pDecimalPoint = pBufferCvt + nDecimalPoint - 1;
                const char* pCurrentSource = pBufferCvt + nBufferLength - 1;
                if ((pCurrentSource - pDecimalPoint) > nPrecision) pCurrentSource = pDecimalPoint + nPrecision;
                while (pCurrentSource > pDecimalPoint) {
                    char c;
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

// ---------------------------------------------------------------------------------------------
// Stand-in callers (not part of the original module): they make cl emit the four static
// helpers above and pin their internal calling conventions.  Never called at run time.
// ---------------------------------------------------------------------------------------------
extern "C" const void* gStandInSink8;
extern "C" int StandInUse8(va_list* pArguments, const char* pFormat, char* pBuffer) {
    FormatData8 fd;
    const char* p = ReadFormat8(pArguments, pFormat, &fd);
    char* q = WriteInteger8(1234u, &fd, pBuffer);
    char* r = WriteInteger64_8(&fd, 1234567890123LL, pBuffer);
    char* s = WriteDouble8(&fd, 1.25, pBuffer);
    gStandInSink8 = p;
    gStandInSink8 = q;
    gStandInSink8 = r;
    gStandInSink8 = s;
    return (int)(q - p) + (int)(r - s);
}
