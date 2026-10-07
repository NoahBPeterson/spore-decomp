// Slice s00937da0: EAStdC printf core (MSVC 2008 SP1, /O2 /MD /Gy /TP /GS-).
//
//   00937da0  VprintfCore8   (char printf engine)
//   00938400  Vsnprintf8
//   00938470  Sprintf8
//   009384e0  Snprintf8
//   00938500  ReadFormat16   (wchar_t format-spec parser)
//   00938980  WriteInteger16 (integer -> string conversion helper; wide variant)
//
// This is the self-contained EAStdC EASprintf implementation that Spore statically links
// (names recovered from the 2008 dev-build PDB).  Snprintf8 matches byte-exact; the two
// wrappers are behaviourally complete but rely on VprintfCore8's private register calling
// convention (pFormat in EAX, three stack args), which is not reproduced by a reconstructed
// body.  The three large cores are faithful behaviour-complete approximations, not exact.
#include "types.h"
#include <stdarg.h>

extern "C" __declspec(dllimport) int __stdcall WideCharToMultiByte(
    unsigned int codePage, unsigned long flags, const wchar_t* wide, int wideCount,
    char* multi, int multiCount, const char* defaultChar, int* usedDefault);

// ---------------------------------------------------------------------------------------------
// The output sink.  At 0x00938370 lives the real StringWriter8 used by Sprintf8/Vsnprintf8;
// it appends to the SnprintfContext8 below.  Bodies/call targets are masked relocations, so a
// local definition with the same shape is substituted.
// ---------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------
// Format descriptor filled in by ReadFormat8 / ReadFormat16.  The binary copies exactly seven
// dwords (28 bytes) out of the parser's locals, so the layout below is fixed.
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

// ReadFormat8 (009370d0: EAX = va_list*, EDX = format, stack = FormatData) and WriteInteger8
// (00937510: EAX = value, ECX = FormatData, stack = buffer end) have the register conventions
// cl gives TU-static functions, so they were static in the original TU.  They are defined below
// as static functions sharing the ReadFormat16 / WriteInteger16 bodies (cl assigns our copies
// different registers, so the call sites differ in bytes; the equivalence checker runs our
// copies).  Deliberately no address comment on these declarations: mapping the calls to the
// originals would pass the arguments in the wrong registers.
static const char* ReadFormat8(va_list* pArguments, const char* pFormat, FormatData8* pData);
static char* WriteInteger8(unsigned int nValue, FormatData8* pData, char* pBufferEnd);
// Out-of-slice helpers that are plain cdecl in the original too.
char* WriteInteger64_8(FormatData8* pData, unsigned int nLow, unsigned int nHigh, char* pBufferEnd); // 0x00937720
char* WriteDouble8(FormatData8* pData, double dValue, char* pBufferEnd);                 // 0x00937970

// ---------------------------------------------------------------------------------------------
// @ 0x00937da0  VprintfCore8
// Original takes pFormat in EAX (custom convention); the other three args are on the stack.
// ---------------------------------------------------------------------------------------------
__declspec(noinline) static int VprintfCore8(const char* pFormat, WriteFunction8 pWriteFunction,
                                             void* pContext, va_list arguments) {
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

// @ 0x00938400  Vsnprintf8
int Vsnprintf8(char* pDestination, unsigned int n, const char* pFormat, va_list arguments) {
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

// @ 0x00938470  Sprintf8
int Sprintf8(char* pDestination, const char* pFormat, ...) {
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

// @ 0x009384e0  Snprintf8
int Snprintf8(char* pDestination, unsigned int n, const char* pFormat, ...) {
    va_list arguments;
    va_start(arguments, pFormat);
    return Vsnprintf8(pDestination, n, pFormat, arguments);
}

// ---------------------------------------------------------------------------------------------
// ReadFormat8 (0x009370d0) / ReadFormat16 (0x00938500): format-spec parser (one spec starting at '%').  The original takes the va_list
// pointer in EAX, the format pointer in EDX and the FormatData out-pointer on the stack, and
// returns the pointer just past the spec.  Bails out (type 0) on width/precision above 0x400.
// ---------------------------------------------------------------------------------------------
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

// @ 0x00938500
__declspec(noinline) static const wchar_t* ReadFormat16(va_list* pArguments, const wchar_t* pFormat,
                                                        FormatData8* pData) {
    return ReadFormatT(pArguments, pFormat, pData);
}

// ---------------------------------------------------------------------------------------------
// WriteInteger8 (0x00937510) / WriteInteger16 (0x00938980): integer -> string.  Original: EAX = value, EDI = FormatData*, stack = buffer end.
// Writes digits backwards from pBufferEnd (terminator first) and returns the start pointer.
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

__declspec(noinline) static char* WriteInteger8(unsigned int nValue, FormatData8* pData, char* pBufferEnd) {
    return WriteIntegerT(nValue, pData, pBufferEnd);
}

// @ 0x00938980
__declspec(noinline) static short* WriteInteger16(unsigned int nValue, FormatData8* pData, short* pBufferEnd) {
    return WriteIntegerT(nValue, pData, pBufferEnd);
}

// Stand-in for the callers outside this slice (VprintfCore16): a TU-static function is only
// emitted, and only gets cl's register convention, when something in the TU calls it.
const wchar_t* ReadFormat16Caller(va_list* pArguments, const wchar_t* pFormat, FormatData8* pData) {
    return ReadFormat16(pArguments, pFormat, pData);
}
short* WriteInteger16Caller(unsigned int nValue, FormatData8* pData, short* pBufferEnd) {
    return WriteInteger16(nValue, pData, pBufferEnd);
}
