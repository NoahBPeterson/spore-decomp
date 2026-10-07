// Slice s0093c950: EA::Text (Spore's statically linked EAText/eatext library), MSVC 2008 SP1.
//   0093c950  EA::Text::ConvertEncoding            (6-arg src/dest transcoder)
//   0093cf10  EA::Text::StrncpyUTF8ToUTF16
//   0093cf60  EA::Text::GetCharacterAsUTF16
//   0093cfb0  EA::Text::ConvertEncoding            (append overload)
//   0093d0b0  EA::Text::GetTextLine
//   0093d110  EA::Text::GetToken / token scanner
//   0093d210  EA::Text::ConvertBinaryDataToASCIIArray
//   0093d280  EA::Text::ConvertASCIIArrayToBinaryData
//   0093d320  EA::Text::SplitTokenDelimited
//   0093d3a0  EA::Text::MatchPattern<wchar_t>
//   0093d410  EA::Text::MatchPattern<char>
//   0093d470  EA::Text::WildcardMatch (wchar_t)
//   0093d5d0  EA::Text::WildcardMatch (char)
//   0093d6f0  EA::Text::String16 ctor from a wide buffer
#include "types.h"

extern "C" __declspec(dllimport) unsigned long __stdcall GetACP(void);
extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(
    unsigned int codePage, unsigned long flags, const char* multi, int multiCount,
    wchar_t* wide, int wideCount);
extern "C" __declspec(dllimport) int __stdcall WideCharToMultiByte(
    unsigned int codePage, unsigned long flags, const wchar_t* wide, int wideCount,
    char* multi, int multiCount, const char* defaultChar, int* usedDefault);
extern "C" __declspec(dllimport) wchar_t* __cdecl _wcslwr(wchar_t* s);
extern "C" __declspec(dllimport) char* __cdecl _strlwr(char* s);

extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);
extern "C" void* __cdecl operator_new(unsigned int size, const char* name, int a, int b,
                                      const char* file, int line);
void* __cdecl operator new[](unsigned int size, const char* name, int a, int b,
                             const char* file, int line);
extern "C" void __cdecl operator_delete__(void* p);   // 0xf47380

namespace EA {
namespace Text {

// Inline string helpers (EAStdC EAString inline forms; the binary inlines these).
inline unsigned int Strlen(const char* pString) {
    const char* pBegin = pString + 1;
    while (*pString++)
        ;
    return (unsigned int)(pString - pBegin);
}
inline unsigned int Strlen(const wchar_t* pString) {
    const wchar_t* pBegin = pString + 1;
    while (*pString++)
        ;
    return (unsigned int)(pString - pBegin);
}
inline char* Strcpy(char* pDestination, const char* pSource) {
    char* p = pDestination;
    while ((*p++ = *pSource++) != 0)
        ;
    return pDestination;
}
inline wchar_t* Strcpy(wchar_t* pDestination, const wchar_t* pSource) {
    wchar_t* p = pDestination;
    while ((*p++ = *pSource++) != 0)
        ;
    return pDestination;
}

// ---------------------------------------------------------------------------------------------
// The wide string class used throughout this module (eastl::basic_string<wchar_t>).
// The call targets below live outside this slice and are masked relocations.
// ---------------------------------------------------------------------------------------------
struct WStr {
    wchar_t* mpBegin;     // +0
    wchar_t* mpEnd;       // +4
    wchar_t* mpCapacity;  // +8
    void AllocateSelf(unsigned int nCount);
    void Append(const wchar_t* pFirst, const wchar_t* pLast);
};

// ACP / default codepage cache (DAT_016699b8).
unsigned int g_defaultCodePage = 0;

// Helper that transcodes through UTF-16 when neither side is UTF-8/16 native.
unsigned int ConvertEncoding_via_UTF16(const void* pSource, unsigned int nSourceLength,
                                       unsigned int sourceEncoding, void* pDest,
                                       unsigned int* pDestLength, unsigned int destEncoding);

// ---------------------------------------------------------------------------------------------
// @ 0x0093C950  EA::Text::ConvertEncoding
// Transcodes between UTF-8 (8), UTF-16 (0x10), 7-bit ASCII (4), the system ACP (2) and Windows code
// pages.  Encoding 1 means UTF-16 too.  Returns the number of source units consumed.
// ---------------------------------------------------------------------------------------------
unsigned int Strlen32(const void* pString);     // 0x0093c710, 32-bit units
unsigned int ConvertEncoding_via_UTF16(const void* pSource, unsigned int nSourceLength,
                                       unsigned int sourceEncoding, void* pDest,
                                       unsigned int* pDestLength, unsigned int destEncoding);  // 0x0093c850

unsigned int ConvertEncoding(const void* pSource, unsigned int nSourceLength,
                             unsigned int sourceEncoding, void* pDest,
                             unsigned int* pDestLength, unsigned int destEncoding) {
    unsigned int nLength = nSourceLength;
    unsigned int srcCP = sourceEncoding;
    unsigned int dstCP;
    unsigned int i;
    unsigned int n;
    int bUsedDefault;
    char cDefault;

    if (nSourceLength == 0) {
        *pDestLength = 0;
        return 0;
    }

    if (nSourceLength == 0xffffffff) {
        if ((int)sourceEncoding > 0x20) {
            if ((int)sourceEncoding > 0x4af && (int)sourceEncoding < 0x4b2)
                nLength = Strlen((const wchar_t*)pSource);
            else
                nLength = Strlen((const char*)pSource);
        } else if (sourceEncoding != 0x20) {
            if (sourceEncoding != 0x10)
                nLength = Strlen((const char*)pSource);
            else
                nLength = Strlen((const wchar_t*)pSource);
        } else {
            nLength = Strlen32(pSource);
        }
    }

    if (sourceEncoding == 1) {
        srcCP = 0x10;
    } else if (sourceEncoding == 2) {
        srcCP = g_defaultCodePage;
        if (srcCP == 0) {
            srcCP = GetACP();
            g_defaultCodePage = srcCP;
        }
    }

    if (destEncoding == 1) {
        dstCP = 0x10;
    } else {
        dstCP = destEncoding;
        if (destEncoding == 2) {
            dstCP = g_defaultCodePage;
            if (dstCP == 0) {
                dstCP = GetACP();
                g_defaultCodePage = dstCP;
            }
        }
    }

    // Pure 7-bit data is treated as ASCII.
    if (srcCP != 0x10) {
        i = 0;
        if (nLength != 0) {
            do {
                if (((const unsigned char*)pSource)[i] > 0x7f)
                    goto NotAscii;
                ++i;
            } while (i < nLength);
        }
        srcCP = 4;
    }
NotAscii:

    if (srcCP == dstCP)
        goto Copy;
    if (srcCP == 4) {
        if (dstCP != 0x10)
            goto Copy;
    } else if (srcCP == 0x10) {
        if (dstCP == 4) {
            // UTF-16 -> ASCII (truncating)
            if (*pDestLength <= nLength)
                nLength = *pDestLength;
            if (pDest) {
                const wchar_t* pSrc = (const wchar_t*)pSource;
                const wchar_t* pSrcEnd = pSrc + nLength;
                char* pDst = (char*)pDest;
                for (; pSrc < pSrcEnd; ++pSrc) {
                    *pDst = (char)*pSrc;
                    ++pDst;
                }
            }
            *pDestLength = nLength;
            return nLength;
        }
    } else if (dstCP == 4) {
        goto Copy;
    }

    if (pSource == pDest)
        return 0;

    if (srcCP == 8) {
        if (dstCP == 0x10) {
            // UTF-8 -> UTF-16
            unsigned int nCapacity = *pDestLength;
            wchar_t* pDst = (wchar_t*)pDest;
            const unsigned char* p = (const unsigned char*)pSource;
            const unsigned char* pEnd = p + nLength;
            if (p < pEnd) {
                int nRemain = (int)(pEnd - p);
                while (pDst < (wchar_t*)pDest + nCapacity) {
                    unsigned char c = *p;
                    unsigned short w;
                    if (c < 0x80) {
                        w = c;
                        ++p;
                        --nRemain;
                    } else {
                        unsigned char t1, t2;
                        if (c < 0xc2)
                            break;
                        if (c < 0xe0) {
                            if (nRemain < 2 || (t1 = p[1] ^ 0x80, t1 > 0x3f))
                                break;
                            w = (unsigned short)((unsigned short)(c & 0x1f) << 6 | (unsigned short)t1);
                            p += 2;
                            nRemain -= 2;
                        } else if (c < 0xf0) {
                            if (nRemain < 3 || (t1 = p[1] ^ 0x80, t1 > 0x3f) ||
                                (t2 = p[2] ^ 0x80, t2 > 0x3f) || (c < 0xe1 && p[1] < 0xa0))
                                break;
                            w = (unsigned short)(((unsigned short)c << 6 | (unsigned short)t1) << 6 |
                                                 (unsigned short)t2);
                            p += 3;
                            nRemain -= 3;
                        } else {
                            if (c > 0xf7 || nRemain < 4 || (p[1] ^ 0x80) > 0x3f ||
                                (t1 = p[2] ^ 0x80, t1 > 0x3f) || (t2 = p[3] ^ 0x80, t2 > 0x3f) ||
                                (c < 0xf1 && p[1] < 0x90))
                                break;
                            w = (unsigned short)(((unsigned short)p[1] << 6 | (unsigned short)t1) << 6 |
                                                 (unsigned short)t2);
                            p += 4;
                            nRemain -= 4;
                        }
                    }
                    if (pDest)
                        *pDst = w;
                    ++pDst;
                    if (pEnd <= p)
                        break;
                }
            }
            *pDestLength = (unsigned int)(pDst - (wchar_t*)pDest);
            return (unsigned int)(p - (const unsigned char*)pSource);
        }
        goto Convert;
    } else if (srcCP != 0x10) {
        if (srcCP == 4 && dstCP == 0x10) {
            // ASCII -> UTF-16 (zero extend)
            if (*pDestLength <= nLength)
                nLength = *pDestLength;
            if (pDest) {
                i = 0;
                if (nLength != 0) {
                    wchar_t* pDst = (wchar_t*)pDest;
                    do {
                        *pDst = (unsigned short)((const unsigned char*)pSource)[i];
                        ++i;
                        ++pDst;
                    } while (i < nLength);
                }
            }
            *pDestLength = nLength;
            return nLength;
        }
        goto Convert;
    }

    // srcCP == 0x10
    if (dstCP == 8) {
        // UTF-16 -> UTF-8
        unsigned int nCapacity = *pDestLength;
        char* pDst = (char*)pDest;
        const wchar_t* p = (const wchar_t*)pSource;
        while (p < (const wchar_t*)pSource + nLength) {
            unsigned short w = *p;
            unsigned int cp = w;
            int nSeq;
            ++p;
            if (cp < 0x80)
                nSeq = 1;
            else if (cp < 0x800)
                nSeq = 2;
            else if (cp < 0x10000)
                nSeq = 3;
            else if (cp < 0x200000)
                nSeq = 4;
            else if (cp < 0x4000000)
                nSeq = 5;
            else {
                if (cp > 0x7fffffff)
                    break;
                nSeq = 6;
            }
            if ((char*)pDest + nCapacity < pDst + nSeq)
                break;
            if (pDest) {
                switch (nSeq) {
                    case 6:
                        pDst[5] = (char)(cp & 0x3f | 0x80);
                        cp = (cp >> 6) | 0x4000000;
                    case 5:
                        pDst[4] = (char)(cp & 0x3f | 0x80);
                        cp = (cp | 0x8000000) >> 6;
                    case 4:
                        pDst[3] = (char)(cp & 0x3f | 0x80);
                        cp = (cp | 0x400000) >> 6;
                    case 3:
                        pDst[2] = (char)(cp & 0x3f | 0x80);
                        cp = (cp | 0x20000) >> 6;
                    case 2:
                        pDst[1] = (char)(cp & 0x3f | 0x80);
                        cp = (cp | 0x3000) >> 6;
                    case 1:
                        pDst[0] = (char)cp;
                }
            }
            pDst += nSeq;
        }
        *pDestLength = (unsigned int)(pDst - (char*)pDest);
        return (unsigned int)(p - (const wchar_t*)pSource);
    }
    goto WideToMulti;

Convert:
    if (dstCP == 8)
        return ConvertEncoding_via_UTF16(pSource, nLength, srcCP, pDest, pDestLength, 8);
    if (srcCP == 8) {
        if (dstCP != 0x10)
            return ConvertEncoding_via_UTF16(pSource, nLength, 8, pDest, pDestLength, dstCP);
    } else {
        if (srcCP == 0x10)
            goto WideToMulti;
        if (dstCP != 0x10)
            goto Invalid;
    }
    // multi-byte code page -> UTF-16
    if (!pDest)
        return 0;
    n = MultiByteToWideChar(srcCP, 0, (const char*)pSource, nLength, (wchar_t*)pDest, *pDestLength);
    goto Finish;

WideToMulti:
    if (dstCP == 0x10)
        goto Invalid;
    cDefault = ' ';
    bUsedDefault = 0;
    if (!pDest)
        return 0;
    n = WideCharToMultiByte(dstCP, 0, (const wchar_t*)pSource, nLength, (char*)pDest, *pDestLength,
                            &cDefault, &bUsedDefault);
Finish:
    if (n != 0) {
        *pDestLength = n;
        return nLength;
    }
    *pDestLength = 0;
    return 0;

Invalid:
    *pDestLength = 0;
    return 0;

Copy:
    if (pSource != pDest) {
        if (*pDestLength <= nLength)
            nLength = *pDestLength;
        if (pDest) {
            unsigned int nBytes = nLength;
            if (dstCP == 0x10)
                nBytes = nLength * 2;
            memcpy(pDest, pSource, nBytes);
        }
    }
    *pDestLength = nLength;
    return nLength;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0093CF10  EA::Text::StrncpyUTF8ToUTF16
// Converts a UTF-16 source into UTF-8 at pDest, returning the produced count - 1.
// ---------------------------------------------------------------------------------------------
int StrncpyUTF8ToUTF16(char* pDest, unsigned int nDestLength, const wchar_t* pSource,
                       int nSourceLength) {
    int nSrc = nSourceLength;
    if (nSourceLength == -1)
        nSrc = (int)Strlen(pSource) + 1;       // includes the terminator
    ConvertEncoding(pSource, (unsigned int)nSrc, 0x10, pDest, &nDestLength, 8);
    if (nDestLength > 0)
        return (int)nDestLength - 1;
    return 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0093CF60  EA::Text::GetCharacterAsUTF16
// Converts one UTF-8 character sequence into UTF-16, null-terminating when room remains.
// ---------------------------------------------------------------------------------------------
unsigned int GetCharacterAsUTF16(wchar_t* pDest, unsigned int nDestLength, const char* pSource,
                                 int nSourceLength) {
    unsigned int nCap = nDestLength;
    int nSrc = nSourceLength;
    if (nSourceLength == -1)
        nSrc = (int)Strlen(pSource);
    ConvertEncoding(pSource, (unsigned int)nSrc, 8, pDest, &nDestLength, 0x10);
    if (nCap > nDestLength)
        pDest[nDestLength] = 0;
    return nDestLength;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0093CFB0  EA::Text::ConvertEncoding (append overload)
// Transcodes into UTF-16 and appends the result to a wide string.
// ---------------------------------------------------------------------------------------------
unsigned int ConvertEncoding(const wchar_t* pSource, unsigned int nSourceLength,
                             unsigned int sourceEncoding, WStr* pDest) {
    if (sourceEncoding == 1)
        goto Direct;
    if (sourceEncoding == 2) {
        if (g_defaultCodePage == 0)
            g_defaultCodePage = GetACP();
        sourceEncoding = g_defaultCodePage;
    }
    if (sourceEncoding == 0x10) {
    Direct:
        pDest->Append(pSource, pSource + nSourceLength);
        return nSourceLength;
    }
    {
        unsigned int nLength = nSourceLength;
        wchar_t localBuffer[0x180];
        wchar_t* pHeap;
        wchar_t* pBuffer;
        if (nSourceLength < 0x180) {
            pHeap = 0;
        } else {
            pHeap = new ("EATextEncoding/HeapData/char16[]", 0, 0, 0, 0) wchar_t[nSourceLength];
            pBuffer = pHeap;
            if (pHeap)
                goto Ready;
        }
        pBuffer = localBuffer;
    Ready:
        unsigned int nResult = ConvertEncoding(pSource, nSourceLength, sourceEncoding, pBuffer,
                                               &nLength, 0x10);
        pDest->Append(pBuffer, pBuffer + nLength);
        operator_delete__(pHeap);
        return nResult;
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x0093D0B0  EA::Text::GetTextLine
// ---------------------------------------------------------------------------------------------
const char* GetTextLine(const char* pText, const char* pTextEnd, const char** ppNewText) {
    if (pText < pTextEnd) {
        while ((pText < pTextEnd) && (*pText != '\r') && (*pText != '\n'))
            ++pText;

        if (ppNewText) {
            *ppNewText = pText;

            if (*ppNewText < pTextEnd) {
                if ((++*ppNewText < pTextEnd) && ((**ppNewText ^ *pText) == ('\r' ^ '\n')))
                    ++*ppNewText;
            }
        }
    } else if (ppNewText) {
        *ppNewText = pTextEnd;
    }
    return pText;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0093D110  EA::Text::GetToken
// Scans one whitespace/ delimiter separated token (with "..." quoting) out of pText.
// ---------------------------------------------------------------------------------------------
bool GetToken(char* pText, char* pTextEnd, char cDelimiter, char** ppBegin, char** ppEnd,
              char** ppOut) {
    int nQuote = 0;
    *ppBegin = pText;
    while (pText < pTextEnd) {
        char c = **ppBegin;
        if ((c != ' ') && (c != '\t'))
            break;
        pText = *ppBegin + 1;
        *ppBegin = pText;
    }
    *ppEnd = *ppBegin;
    if (*ppBegin < pTextEnd) {
        do {
            char* pCur = *ppEnd;
            char* pNext = pCur + 1;
            char c = *pCur;
            bool bLast = (pNext == pTextEnd);
            bool bFound;
            if (cDelimiter == ' ')
                bFound = (c == cDelimiter) || (c == '\t');
            else
                bFound = (c == cDelimiter);
            if (!bFound) {
                if (bLast) {
                    *ppEnd = pNext;
                    bFound = true;
                } else if (c == '"') {
                    ++nQuote;
                }
            }
            if (bFound && (((nQuote & 1) == 0) || bLast))
                goto Found;
            ++*ppEnd;
        } while (*ppEnd < pTextEnd);
    }
    if (ppOut)
        *ppOut = *ppEnd;
    return false;

Found:
    if (ppOut)
        *ppOut = *ppEnd;
    if ((cDelimiter != ' ') && (*ppEnd != pTextEnd) && (*ppEnd != *ppBegin)) {
        char* q;
        do {
            q = *ppEnd;
            char d = q[-1];
            --q;
            if ((d != ' ') && (d != '\t'))
                break;
            *ppEnd = q;
        } while (q != *ppBegin);
    }
    if ((*ppBegin != pTextEnd) && (**ppBegin == '"') && (*(*ppEnd - 1) == '"')) {
        ++*ppBegin;
        --*ppEnd;
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0093D210  EA::Text::ConvertBinaryDataToASCIIArray
// ---------------------------------------------------------------------------------------------
void ConvertBinaryDataToASCIIArray(const void* pBinaryData_, int nBinaryDataLength,
                                   uint16_t* pASCIIArray) {
    const uint8_t* pBinaryData = (const uint8_t*)pBinaryData_;
    const uint8_t* pEnd = pBinaryData + nBinaryDataLength;

    while (pBinaryData < pEnd) {
        *pASCIIArray = (uint16_t)('0' + ((*pBinaryData & 0xf0) >> 4));
        if (*pASCIIArray > '9')
            *pASCIIArray += 7;
        pASCIIArray++;
        *pASCIIArray = (uint16_t)('0' + (*pBinaryData & 0x0f));
        if (*pASCIIArray > '9')
            *pASCIIArray += 7;
        pASCIIArray++;
        pBinaryData++;
    }

    *pASCIIArray = '\0';
}

// ---------------------------------------------------------------------------------------------
// @ 0x0093D280  EA::Text::ConvertASCIIArrayToBinaryData
// ---------------------------------------------------------------------------------------------
bool ConvertASCIIArrayToBinaryData(const wchar_t* pASCIIArray, int nASCIIArrayLength,
                                   void* pBinaryData) {
    uint8_t* pBinaryData8 = (uint8_t*)pBinaryData;
    const wchar_t* pEnd = pASCIIArray + nASCIIArrayLength;
    wchar_t cTemp;
    bool bReturnValue(true);

    while (pASCIIArray < pEnd) {
        *pBinaryData8 = 0;

        for (int j = 4; j >= 0; j -= 4) {
            cTemp = *pASCIIArray;

            if (cTemp < '0') {
                cTemp = '0';
                bReturnValue = false;
            } else if (cTemp > 'F') {
                if (cTemp >= 'a' && cTemp <= 'f')
                    cTemp -= 39;
                else {
                    cTemp = '0';
                    bReturnValue = false;
                }
            } else if (cTemp > '9' && cTemp < 'A') {
                cTemp = '0';
                bReturnValue = false;
            } else if (cTemp >= 'A')
                cTemp -= 7;

            *pBinaryData8 = (uint8_t)(*pBinaryData8 + ((cTemp - '0') << j));
            pASCIIArray++;
        }

        pBinaryData8++;
    }

    return bReturnValue;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0093D320  EA::Text::SplitTokenDelimited
// ---------------------------------------------------------------------------------------------
bool SplitTokenDelimited(const wchar_t* pSource, unsigned int nSourceLength, wchar_t cDelimiter,
                         wchar_t* pToken, unsigned int nTokenLength, const wchar_t** ppNewSource) {
    if (pToken && nTokenLength)
        *pToken = 0;

    if (pSource && nSourceLength && *pSource) {
        for (unsigned int i = 0; i < nSourceLength && *pSource; i++) {
            const wchar_t cTemp(*pSource);

            if (ppNewSource)
                (*ppNewSource)++;

            if (cTemp == cDelimiter)
                break;
            else {
                if (pToken && ((i + 1) < nTokenLength)) {
                    *pToken = cTemp;
                    pToken++;
                    *pToken = 0;
                }
                pSource++;
            }
        }
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0093D3A0 / 0x0093D410  EA::Text::MatchPattern
// ---------------------------------------------------------------------------------------------
template <class CharT>
bool MatchPattern(const CharT* pElement, const CharT* pPattern) {
    if ((*pPattern == (CharT)'*') && !pPattern[1])
        return true;
    else if (!*pElement && *pPattern)
        return false;
    else if (!*pElement)
        return true;
    else {
        if (*pPattern == (CharT)'*') {
            if (MatchPattern(pElement, pPattern + 1))
                return true;
            else
                return MatchPattern(pElement + 1, pPattern);
        } else if (*pPattern == (CharT)'?')
            return MatchPattern(pElement + 1, pPattern + 1);
        else {
            if (*pElement == *pPattern)
                return MatchPattern(pElement + 1, pPattern + 1);
            else
                return false;
        }
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x0093D470  EA::Text::WildcardMatch (wchar_t)
// ---------------------------------------------------------------------------------------------
bool WildcardMatch(const wchar_t* pString, const wchar_t* pPattern, bool bCaseSensitive) {
    if (bCaseSensitive)
        return MatchPattern(pString, pPattern);
    else {
        wchar_t  pStringLBuffer[384];
        wchar_t* pStringL;
        wchar_t* pStringLAllocated;
        unsigned int nStringLLength = Strlen(pString);

        if (nStringLLength >= (sizeof(pStringLBuffer) / sizeof(pStringLBuffer[0]) - 1)) {
            pStringLAllocated = new ("EATextUtil/StringAllocated/char16[]", 0, 0, 0, 0) wchar_t[nStringLLength + 1];
            pStringL = pStringLAllocated;
        } else {
            pStringLAllocated = 0;
            pStringL = pStringLBuffer;
        }
        Strcpy(pStringL, pString);
        _wcslwr(pStringL);

        wchar_t  pPatternLBuffer[32];
        wchar_t* pPatternL;
        wchar_t* pPatternLAllocated;
        unsigned int nPatternLLength = Strlen(pPattern);

        if (nPatternLLength >= (sizeof(pPatternLBuffer) / sizeof(pPatternLBuffer[0]) - 1)) {
            pPatternLAllocated = new ("EATextUtil/PatternAllocated/char16[]", 0, 0, 0, 0) wchar_t[nPatternLLength + 1];
            pPatternL = pPatternLAllocated;
        } else {
            pPatternLAllocated = 0;
            pPatternL = pPatternLBuffer;
        }
        Strcpy(pPatternL, pPattern);
        _wcslwr(pPatternL);

        const bool bResult = MatchPattern(pStringL, pPatternL);

        operator_delete__(pStringLAllocated);
        operator_delete__(pPatternLAllocated);

        return bResult;
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x0093D5D0  EA::Text::WildcardMatch (char)
// ---------------------------------------------------------------------------------------------
bool WildcardMatch(const char* pString, const char* pPattern, bool bCaseSensitive) {
    if (bCaseSensitive)
        return MatchPattern(pString, pPattern);
    else {
        char  pStringLBuffer[384];
        char* pStringL;
        char* pStringLAllocated;
        unsigned int nStringLLength = Strlen(pString);

        if (nStringLLength >= (sizeof(pStringLBuffer) / sizeof(pStringLBuffer[0]) - 1)) {
            pStringLAllocated = new ("EATextUtil/StringAllocated/char[]", 0, 0, 0, 0) char[nStringLLength + 1];
            pStringL = pStringLAllocated;
        } else {
            pStringLAllocated = 0;
            pStringL = pStringLBuffer;
        }
        Strcpy(pStringL, pString);
        _strlwr(pStringL);

        char  pPatternLBuffer[32];
        char* pPatternL;
        char* pPatternLAllocated;
        unsigned int nPatternLLength = Strlen(pPattern);

        if (nPatternLLength >= (sizeof(pPatternLBuffer) / sizeof(pPatternLBuffer[0]) - 1)) {
            pPatternLAllocated = new ("EATextUtil/PatternAllocated/char[]", 0, 0, 0, 0) char[nPatternLLength + 1];
            pPatternL = pPatternLAllocated;
        } else {
            pPatternLAllocated = 0;
            pPatternL = pPatternLBuffer;
        }
        Strcpy(pPatternL, pPattern);
        _strlwr(pPatternL);

        const bool bResult = MatchPattern(pStringL, pPatternL);

        operator_delete__(pStringLAllocated);
        operator_delete__(pPatternLAllocated);

        return bResult;
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x0093D6F0  WStr::WStr(const wchar_t* pSource, int nCount[, int nExtra])
// ---------------------------------------------------------------------------------------------
struct WStrCtor : public WStr {
    WStrCtor(const wchar_t* pSource, int nCount, int nExtra);
};

WStrCtor::WStrCtor(const wchar_t* pSource, int nCount, int /*nExtra*/) {
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    const wchar_t* pSourceEnd = pSource + nCount;
    const int n = (int)(pSourceEnd - pSource);
    AllocateSelf((unsigned int)(n + 1));
    wchar_t* pDst = mpBegin;
    memcpy(pDst, pSource, (unsigned int)(n * 2));
    mpEnd = pDst + n;
    *mpEnd = 0;
}

}  // namespace Text
}  // namespace EA
