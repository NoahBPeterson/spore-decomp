// src/game/UTFSpore_Win32/EATextEncoding.cpp -- migrated from slice(s) s0093c950, s0093b9e0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EATextEncoding.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/IStream.h"
#include "EA/IO/MemoryStream.h"
#include "EA/IO/SharedPointer.h"
#include "encoding.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  EASTL_deallocate(void* p);                                  // 0x00f47380
extern "C" void* EASTL_allocate(size_t n, const char*, int, int, int, int);  // 0x00f473a0
#include <intrin.h>
#include <new>

// ---- items of slice s0093b9e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  EASTL_deallocate(void* p);                                  // 0x00f47380
extern "C" void* EASTL_allocate(size_t n, const char*, int, int, int, int);  // 0x00f473a0
namespace EA {
namespace Text {
int ConvertEncoding(const void* src, size_t srcCount, int srcEnc, void* dst, int* dstLen, int dstEnc); // 0x0093c950
}
}
// ---- items of slice s0093b9e0 end

// ---- items of slice s0093c950 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) unsigned long __stdcall GetACP(void);
extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(
    unsigned int codePage, unsigned long flags, const char* multi, int multiCount,
    wchar_t* wide, int wideCount);
extern "C" __declspec(dllimport) int __stdcall WideCharToMultiByte(
    unsigned int codePage, unsigned long flags, const wchar_t* wide, int wideCount,
    char* multi, int multiCount, const char* defaultChar, int* usedDefault);
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);
extern "C" void __cdecl operator_delete__(void* p);   // 0xf47380
void* __cdecl operator new[](unsigned int size, const char* name, int a, int b,
                             const char* file, int line);
namespace EA {
namespace Text {
inline unsigned int Strlen(const char* pString) {
    const char* pBegin = pString + 1;
    while (*pString++)
        ;
    return (unsigned int)(pString - pBegin);
}
}
}
namespace EA {
namespace Text {
inline unsigned int Strlen(const wchar_t* pString) {
    const wchar_t* pBegin = pString + 1;
    while (*pString++)
        ;
    return (unsigned int)(pString - pBegin);
}
}
}
namespace EA {
namespace Text {
struct WStr {
    wchar_t* mpBegin;     // +0
    wchar_t* mpEnd;       // +4
    wchar_t* mpCapacity;  // +8
    void AllocateSelf(unsigned int nCount);
    void Append(const wchar_t* pFirst, const wchar_t* pLast);
};
}
}
namespace EA {
namespace Text {
unsigned int g_defaultCodePage = 0;
}
}
namespace EA {
namespace Text {
unsigned int ConvertEncoding_via_UTF16(const void* pSource, unsigned int nSourceLength,
                                       unsigned int sourceEncoding, void* pDest,
                                       unsigned int* pDestLength, unsigned int destEncoding);
}
}
namespace EA {
namespace Text {
unsigned int Strlen32(const void* pString);     // 0x0093c710, 32-bit units
}
}
// ---- items of slice s0093c950 end

// @ 0x0093c710
namespace EA { namespace Text {
int Strlen32(const int* p)
{
    int n = -1;
    int v;
    do {
        v = *p;
        n++;
        p++;
    } while (v != 0);
    return n;
}
}}  // namespace EA::Text

// @ 0x0093c730
namespace EA { namespace Text {
int DetectEncoding(const unsigned char* p, unsigned count)
{
    int result = 8;
    if (count > 1) {
        if (p[0] == 0xfe && p[1] == 0xff)
            return 0x4b1;
        if (p[0] == 0xff && p[1] == 0xfe)
            return 0x4b0;
        if (count > 2 && p[0] == 0xef && p[1] == 0xbb && p[2] == 0xbf)
            return 8;
        unsigned zeroEven = 0, zeroOdd = 0, ascii = 0, lead = 0, cont = 0;
        for (unsigned i = 0; i < count; ++i) {
            unsigned char c = p[i];
            if (c == 0) {
                if ((i & 1) == 0) cont++; else lead++;
            } else if (c < 0x80) {
                ascii++;
            } else if (c > 0xc1 && c < 0xf0) {
                zeroEven++;
            }
        }
        if (ascii == count)
            return 8;
        if (count >> 2 < lead) {
            if ((count >> 3 < cont) && (count >> 3 < zeroEven))
                return (p[0] == 0) + 0x4b2;
            return (zeroEven < cont) + 0x4b0;
        }
        if (zeroEven < count >> 2)
            result = 0x4b0;
    }
    return result;
}
}}  // namespace EA::Text

// @ 0x0093c850
namespace EA { namespace Text {
int ConvertEncoding_via_UTF16(const void* src, int srcLen, int srcEnc, void* dst, int* dstLen, int dstEnc)
{
    unsigned bufSize = (unsigned)srcLen * 2 + 4;
    void* small = 0;
    void* buf;
    if (bufSize < 0x201) {
        static unsigned char stackBuf[0x400];
        buf = stackBuf;
    } else {
        buf = EASTL_allocate(bufSize, "EATextEncoding/LargeStringBuffer/char[]", 0, 0, 0, 0);
        small = buf;
    }
    unsigned local = bufSize;
    int n = EA::Text::ConvertEncoding(src, srcLen, srcEnc, buf, (int*)&local, 0x10);
    if (n == srcLen) {
        int r = EA::Text::ConvertEncoding(buf, local, 0x10, dst, dstLen, dstEnc);
        if ((unsigned)r == local) {
            EASTL_deallocate(small);
            return srcLen;
        }
    }
    EASTL_deallocate(small);
    *dstLen = 0;
    return 0;
}
}}  // namespace EA::Text

// @ 0x0093c920
namespace EA {
namespace Text {
unsigned int GetCharacterSize(int encoding)
{
    if (encoding < 0x21) {
        if (encoding == 0x20)
            return 4;
        if (encoding == 0x10)
            return 2;
    } else if (encoding > 0x4af && encoding < 0x4b2) {
        return 2;
    }
    return 1;
}
}
}  // namespace EA::Text

// @ 0x0093c950
namespace EA { namespace Text {
unsigned int ConvertEncoding(const void* pSource, unsigned int nSourceLength, unsigned int sourceEncoding, void* pDest, unsigned int* pDestLength, unsigned int destEncoding)
{
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
}}  // namespace EA::Text

// @ 0x0093cf10
namespace EA { namespace Text {
int StrncpyUTF8ToUTF16(char* pDest, unsigned int nDestLength, const wchar_t* pSource, int nSourceLength)
{
    int nSrc = nSourceLength;
    if (nSourceLength == -1)
        nSrc = (int)Strlen(pSource) + 1;       // includes the terminator
    ConvertEncoding(pSource, (unsigned int)nSrc, 0x10, pDest, &nDestLength, 8);
    if (nDestLength > 0)
        return (int)nDestLength - 1;
    return 0;
}
}}  // namespace EA::Text

// @ 0x0093cf60
namespace EA { namespace Text {
unsigned int GetCharacterAsUTF16(wchar_t* pDest, unsigned int nDestLength, const char* pSource, int nSourceLength)
{
    unsigned int nCap = nDestLength;
    int nSrc = nSourceLength;
    if (nSourceLength == -1)
        nSrc = (int)Strlen(pSource);
    ConvertEncoding(pSource, (unsigned int)nSrc, 8, pDest, &nDestLength, 0x10);
    if (nCap > nDestLength)
        pDest[nDestLength] = 0;
    return nDestLength;
}
}}  // namespace EA::Text

// @ 0x0093cfb0
namespace EA { namespace Text {
unsigned int ConvertEncoding(const wchar_t* pSource, unsigned int nSourceLength, unsigned int sourceEncoding, WStr* pDest)
{
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
}}  // namespace EA::Text
