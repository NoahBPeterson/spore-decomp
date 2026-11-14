#include "game/types.h"

// Allocating operator used by the string helpers below (EASTL debug allocation, 0xf473a0).
void* __cdecl operator new[](unsigned int size, const char* name, int a, int b,
                             const char* file, int line);

// Release operator called to free the buffers those helpers allocate (0xf47380).
extern "C" void __cdecl operator_delete__(void* p);   // 0xf47380

extern "C" __declspec(dllimport) wchar_t* __cdecl _wcslwr(wchar_t* s);
extern "C" __declspec(dllimport) char* __cdecl _strlwr(char* s);

namespace EA {
namespace Text {

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

}  // namespace Text
}  // namespace EA

// @ 0x0093d210
namespace EA {
namespace Text {
// Writes the binary data as uppercase hexadecimal text, one wchar_t per digit.
void ConvertBinaryDataToASCIIArray(void const * pBinaryData_, unsigned int nBinaryDataLength, wchar_t * pASCIIArray)
{
    const uint8_t* pBinaryData = (const uint8_t*)pBinaryData_;
    const uint8_t* pEnd = pBinaryData + nBinaryDataLength;

    while (pBinaryData < pEnd) {
        *pASCIIArray = (uint16_t)('0' + ((*pBinaryData & 0xf0) >> 4));
        if (*pASCIIArray > '9')
            *pASCIIArray += 7;  // skip the gap between '9' and 'A'
        pASCIIArray++;
        *pASCIIArray = (uint16_t)('0' + (*pBinaryData & 0x0f));
        if (*pASCIIArray > '9')
            *pASCIIArray += 7;  // skip the gap between '9' and 'A'
        pASCIIArray++;
        pBinaryData++;
    }

    *pASCIIArray = '\0';
}
}
}  // namespace EA::Text

// @ 0x0093d280
namespace EA { namespace Text {
// Parses two uppercase hex digits per output byte; returns false on any non-hex digit
// (which is treated as '0').
bool ConvertASCIIArrayToBinaryData(const wchar_t* pASCIIArray, int nASCIIArrayLength, void* pBinaryData)
{
    uint8_t* pBinaryOut = (uint8_t*)pBinaryData;
    const wchar_t* pEnd = pASCIIArray + nASCIIArrayLength;
    wchar_t cTemp;
    bool bReturnValue(true);

    while (pASCIIArray < pEnd) {
        *pBinaryOut = 0;

        for (int j = 4; j >= 0; j -= 4) {
            cTemp = *pASCIIArray;

            if (cTemp < '0') {
                cTemp = '0';
                bReturnValue = false;
            } else if (cTemp > 'F') {
                if (cTemp >= 'a' && cTemp <= 'f')
                    cTemp -= 39;  // 'a'..'f' -> the same value as 'A'..'F'
                else {
                    cTemp = '0';
                    bReturnValue = false;
                }
            } else if (cTemp > '9' && cTemp < 'A') {
                cTemp = '0';
                bReturnValue = false;
            } else if (cTemp >= 'A')
                cTemp -= 7;  // skip the gap between '9' and 'A'

            *pBinaryOut = (uint8_t)(*pBinaryOut + ((cTemp - '0') << j));
            pASCIIArray++;
        }

        pBinaryOut++;
    }

    return bReturnValue;
}
}}  // namespace EA::Text

// @ 0x0093d320
namespace EA { namespace Text {
// Reads one delimiter-separated token out of pSource into pToken and advances
// *ppNewSource past it. Returns false when there is no source to read.
bool SplitTokenDelimited(const wchar_t* pSource, unsigned int nSourceLength, wchar_t cDelimiter, wchar_t* pToken, unsigned int nTokenLength, const wchar_t** ppNewSource)
{
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
}}  // namespace EA::Text

// @ 0x0093d3a0
namespace EA { namespace Text {
// Recursive glob match supporting '*' and '?'; the template is instantiated for
// char and wchar_t.
template <class CharT> bool MatchPattern(const CharT* pElement, const CharT* pPattern)
{
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
}}  // namespace EA::Text

// @ 0x0093d470
namespace EA {
namespace Text {
bool WildcardMatch(wchar_t const * pString, wchar_t const * pPattern, bool bCaseSensitive)
{
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
}
}  // namespace EA::Text

// @ 0x0093d5d0
namespace EA {
namespace Text {
bool WildcardMatch(char const * pString, char const * pPattern, bool bCaseSensitive)
{
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
}
}  // namespace EA::Text
