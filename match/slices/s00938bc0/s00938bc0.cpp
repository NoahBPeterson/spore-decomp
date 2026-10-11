// Slice s00938bc0: EAStdC wide (UTF-16) printf core.
//   MSVC 2008 SP1  /O2 /MD /Gy /TP /GS-
//
//   00938bc0  WriteInteger64_16   (64-bit integer -> wide string)
//   00938e60  WriteDouble16       (double -> wide string, %e/%f/%g)
//   00939320  VprintfCore16       (the engine)
//   00939950  Vsnprintf16
//   009399c0  Sprintf16
//   00939a30  Snprintf16
//
// Names Vsnprintf16 / Sprintf16 / Snprintf16 / VprintfCore16 are the real 2008 dev-build PDB
// names (EAStdC's EASprintf).  The three integer/float helpers are static TU-local functions in
// the original module (custom register conventions); their reconstructed bodies here let cl pick
// its own convention, so the big cores are complete but not byte-exact.
#include "types.h"
#include <stdarg.h>
#include <float.h>

extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(
    unsigned int codePage, unsigned long flags, const char* multi, int multiCount,
    wchar_t* wide, int wideCount);

typedef int (__cdecl *WriteFunction16)(const wchar_t* pData, int nCount, void* pContext);

// ---------------------------------------------------------------------------------------------
// Format descriptor (7 dwords, exactly what ReadFormat16 fills in).
// ---------------------------------------------------------------------------------------------
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

// The real out-sink at 0x00939910 (StringWriter16) - defined elsewhere (not in this slice).
int StringWriter16(const wchar_t* pData, int nCount, void* pContext);  // 0x00939910

// EcvtBuf (0x92ce80) / FcvtBuf (0x92cef0): decimal converters used by WriteDouble16.
int EcvtBuf(double dValue, int nDigitCount, int* pnDecimalPoint, int* pnSign, short* pBuffer);   // 0x0092ce80
int FcvtBuf(double dValue, int nDigitCount, int* pnDecimalPoint, int* pnSign, short* pBuffer);   // 0x0092cef0

static int Strlen16(const short* s) {
    const short* p = s;
    while (*p) ++p;
    return (int)(p - s);
}

#define IsNeg(x) ((*((uint64_t*)&(x)) & 0x8000000000000000ULL) != 0)

// ---------------------------------------------------------------------------------------------
// ReadFormat16 (0x00938500): parse one format spec.  (The body is the same as the 8-bit parser.)
// ---------------------------------------------------------------------------------------------
static inline unsigned int FormatChar16(wchar_t c) { return (unsigned int)c; }

static const wchar_t* ReadFormat16(va_list* pArguments, const wchar_t* pFormat, FormatData16* pData) {
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

// ---------------------------------------------------------------------------------------------
// WriteInteger16 (0x00938980): 32-bit integer -> wide string.
// ---------------------------------------------------------------------------------------------
static short* WriteInteger16(unsigned int nValue, FormatData16* pData, short* pBufferEnd) {
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

// ---------------------------------------------------------------------------------------------
// @ 0x00938bc0  WriteInteger64_16: 64-bit integer -> wide string.
// ---------------------------------------------------------------------------------------------
static short* WriteInteger64_16(FormatData16* fd, long long lValue, short* pBufferEnd) {
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

// ---------------------------------------------------------------------------------------------
// @ 0x00938e60  WriteDouble16: double -> wide string.
// ---------------------------------------------------------------------------------------------
static short* WriteDouble16(FormatData16* fd, double dValue, short* pBufferEnd) {
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

// ---------------------------------------------------------------------------------------------
// @ 0x00939320  VprintfCore16
// ---------------------------------------------------------------------------------------------
static int VprintfCore16(const wchar_t* pFormat, WriteFunction16 pWriteFunction, void* pContext,
                         va_list arguments) {
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

        pCur = ReadFormat16(&arguments, pSpec, &fd);

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
                pOut = WriteInteger16((unsigned int)v, &fd, szBuffer + 0x408);
                goto haveString;
            }

            case 'X': case 'b': case 'o': case 'u': case 'x': {
                if (fd.mModifier == 3) {
                    unsigned int v = va_arg(arguments, unsigned int);
                    pOut = WriteInteger16(v, &fd, szBuffer + 0x408);
                    goto haveString;
                }
                if (fd.mModifier == 4) goto signed64;
                if (fd.mModifier == 0xd) { fd.mModifier = 4; goto signed64; }
                if (fd.mModifier == 0xe) { arguments += 16; }
                else {
                    unsigned int v = va_arg(arguments, unsigned int);
                    if (fd.mModifier == 2 || fd.mModifier == 0xb) v = (unsigned short)v;
                    else if (fd.mModifier == 1 || fd.mModifier == 0xa) v = (unsigned char)v;
                    pOut = WriteInteger16(v, &fd, szBuffer + 0x408);
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

// ---------------------------------------------------------------------------------------------
// @ 0x00939950  Vsnprintf16
// ---------------------------------------------------------------------------------------------
int Vsnprintf16(short* pDestination, unsigned int n, const wchar_t* pFormat, va_list arguments) {
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

// ---------------------------------------------------------------------------------------------
// @ 0x009399c0  Sprintf16
// ---------------------------------------------------------------------------------------------
int Sprintf16(short* pDestination, const wchar_t* pFormat, ...) {
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

// ---------------------------------------------------------------------------------------------
// @ 0x00939a30  Snprintf16
// ---------------------------------------------------------------------------------------------
int Snprintf16(short* pDestination, unsigned int n, const wchar_t* pFormat, ...) {
    va_list arguments;
    va_start(arguments, pFormat);
    return Vsnprintf16(pDestination, n, pFormat, arguments);
}
