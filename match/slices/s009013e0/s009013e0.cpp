// Spore decompilation - gold1 slice s009013e0 (0x009013E0..0x0090245F).
// EA::XML XmlTextWriter (writer) + XmlTextReader helpers + TokenIOContext string hashtable.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <new>
#include <stdarg.h>

typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned int   size_t;

extern "C" size_t wcslen(const wchar_t*);
#pragma intrinsic(wcslen)

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
extern "C" void* __cdecl EA_operator_new(unsigned int nSize, const char* pName, int a,
                                         int b, const char* pFile, int nLine); // 0xf473a0
extern "C" void  __cdecl EA_operator_delete(void* p);                          // 0xf47380
extern "C" void* __cdecl FUN_011e073e(void* p, int nVal, unsigned int nSize);  // 0x11e073e
extern "C" unsigned int __cdecl FNV1_String16(const wchar_t* pStr, unsigned int a,
                                              unsigned int b);                 // 0x932f30
extern "C" bool  __cdecl IO_WriteEncoded(void* pStream, const void* p, unsigned int n,
                                         unsigned int enc);                    // 0x93b820
extern "C" void* __cdecl FUN_0090aed0(int a, void* b, int c);                  // 0x90aed0
extern "C" int   __cdecl Vsnprintf16(wchar_t* buf, unsigned int count,
                                     const wchar_t* fmt, va_list ap);          // 0x939950
extern "C" __declspec(dllimport) int __cdecl iswctype(unsigned int c, int type);

namespace EA { namespace XML {

enum EState { kStateChars = 0, kStateElement = 1, kStatePI = 2, kStateCDATA = 3 };

// ===========================================================================
// EA::XML::XmlTextWriter
// ===========================================================================
class XmlTextWriter {
public:
    // vtable (slots 0..12); only the used slots matter
    virtual bool vf0();
    virtual bool vf1();
    virtual bool vf2();
    virtual bool vf3();
    virtual bool WriteProlog(const wchar_t* s);                       // +0x10
    virtual bool WriteEpilog();                                       // +0x14
    virtual bool WriteNameValue(const wchar_t* name, const wchar_t* v); // +0x18
    virtual bool vf7();
    virtual bool vf8();
    virtual bool vf9();
    virtual bool vf10();
    virtual bool WriteNameRaw(const wchar_t* s);                      // +0x2c
    virtual bool WriteData(const wchar_t* s, int n);                  // +0x30

    int           mOutputEncoding;   // +0x04
    unsigned char mFormatPretty;     // +0x08
    unsigned char mbSimpleElement;   // +0x09
    int           mnState;           // +0x0c
    int           mnIndentLevel;     // +0x10
    int           mnIndentSpaces;    // +0x14
    int           mLineEnd;          // +0x18
    void*         mpOutputStream;    // +0x1c

    XmlTextWriter(unsigned char bPretty, int nEncoding);

    bool WriteEscapedString(const wchar_t* str);        // 0x9014c0
    bool CloseCurrentElement();                          // 0x901630
    bool BeginProcessingInstruction(const wchar_t* s);   // 0x901690
    bool EndProcessingInstruction();                     // 0x901700
    bool AppendAttribute(const wchar_t* name, const wchar_t* value);      // 0x901740
    int  WriteCharData(const wchar_t* s);                // 0x9018a0
    bool WriteCDATA(const wchar_t* s);                   // 0x9018d0
    void WriteName(const wchar_t* s);                    // 0x901930
    bool WriteXmlHeader();                               // 0x901960
    bool WriteIndent();                                  // 0x901a70
    bool BeginElement(const wchar_t* name);              // 0x901b30
    bool EndElement(const wchar_t* name);                // 0x901b90
    bool WriteComment(const wchar_t* s, unsigned char bIndent); // 0x901c60
    void SetStream(void* pStream, unsigned char bPretty); // 0x901d30
    bool WriteText(const void* p, unsigned int n);       // 0x901d90

    ~XmlTextWriter();
};

bool __cdecl FUN_009017d0(XmlTextWriter* pThis, const wchar_t* name,
                          const wchar_t* fmt, ...);                  // 0x9017d0

} } // namespace EA::XML

// ===========================================================================
// EA::XML::XmlTextReader (+ its cursor object)
// ===========================================================================
struct ReaderRange {
    unsigned int m00;   // +0x00
    unsigned int m04;   // +0x04
    unsigned int m08;   // +0x08
    unsigned int m0c;   // +0x0c
    unsigned int m10;   // +0x10
    void FUN_00928c40(unsigned int v);   // 0x928c40
};

namespace EA { namespace XML {
class XmlTextReader {
public:
    char          _pad00[0x10];
    ReaderRange   mRange;     // +0x10
    char          _pad24[0x14];
    int           m38;        // +0x38
    int           m3c;        // +0x3c
    int           m40;        // +0x40
    char          _pad44[0x28];
    void*         m6c;        // +0x6c
    char          _pad70[0x0c];
    int           m7c;        // +0x7c

    bool FUN_009013e0();                       // 0x9013e0
    void FUN_00901440(int a, int b);           // 0x901440
    void FUN_00901480(int a, int b, int c);    // 0x901480
    bool FUN_00901df0();                       // 0x901df0
    bool FUN_00901e40();                       // 0x901e40
    char FUN_00901340();                       // 0x901340 Read
    void FUN_00901220();                       // 0x901220 InitParser
    char FUN_00900a30(int a, int b);           // 0x900a30
    char FUN_00900610(int a, int b, int c);    // 0x900610
};
}}

bool __cdecl FUN_00901e60(const wchar_t* s);   // 0x901e60

// ===========================================================================
// eastl::hashtable (TokenIOContext string tables)
// ===========================================================================
struct RehashPolicy {
    float mfMaxLoadFactor;   // +0x00
    float mfGrowthFactor;    // +0x04
    uint32 mnNextResize;     // +0x08
    struct Result { unsigned char mbFlag; unsigned int mnNewBucketCount; };
    void FUN_00921440(Result* pOut, unsigned int nBucketCount,
                      unsigned int nElementCount, int nArg);   // 0x921440
};

struct HashNode {
    const wchar_t* first;    // +0x00
    int            second;   // +0x04
    HashNode*      mpNext;   // +0x08
};

struct Hashtable {
    void*        mpAlloc;          // +0x00
    void**       mpBucket;         // +0x04
    uint32       mnBucketCount;    // +0x08
    uint32       mnElementCount;   // +0x0c
    RehashPolicy mPolicy;          // +0x10
};

struct HIter { void* mpNode; void** mpBucket; };
struct InsertRet { void* mpNode; void** mpBucket; unsigned char mbInserted; };
struct StrIdPair { const wchar_t* first; int second; };
struct IdStrPair { int first; const wchar_t* second; };

struct HashA : Hashtable {
    HashNode* FUN_00901f90(HashNode* pHead, const wchar_t* const& key, unsigned int h);
    HIter     FUN_009020b0(const wchar_t* const& key);
    InsertRet FUN_00902140(const StrIdPair& value, int t);
    void      FUN_00901ec0(unsigned int nBucketCount);
};

struct HashB : Hashtable {
    HIter FUN_005ed0(const unsigned int& key);   // 0x645ed0
};

namespace EA { namespace Allocator {
struct StackAllocator {
    unsigned int mnDefaultBlockSize;   // +0x00
    void*        mpCurrentBlock;       // +0x04
    char*        mpCurrentBlockEnd;    // +0x08
    char*        mpCurrentObjectBegin; // +0x0c
    char*        mpCurrentObjectEnd;   // +0x10
    void*        mpCoreAllocationFunction;
    void*        mpCoreFreeFunction;
    void*        mpCoreFunctionContext;
    void*        mpTopBookmark;
    bool AllocateNewBlock(unsigned n);   // 0x928ba0
    __forceinline void* Allocate(unsigned n) {
        n = (n + 7) & ~7u;
        if (mpCurrentBlockEnd - mpCurrentObjectBegin - (int)n < 0) {
            if (!AllocateNewBlock(n)) return 0;
        }
        char* p = mpCurrentObjectBegin;
        mpCurrentObjectBegin = p + n;
        mpCurrentObjectEnd = p + n;
        return p;
    }
};
}}

namespace EA { namespace XML {
struct TokenIOContext {
    char _allocCtx[0x8];
    EA::Allocator::StackAllocator mAllocator;  // +0x08
    HashA* mStringsA;    // +0x2c
    HashB* mStringsB;    // +0x30
    int    mNextStringID;

    int GetString(const wchar_t* str);   // 0x902250
};

wchar_t* sStrDup(const wchar_t* str, TokenIOContext* ctx);   // 0x902380
}}
using namespace EA::XML;

// ===========================================================================
// XmlTextWriter implementation
// ===========================================================================
namespace EA { namespace XML {

// @ 0x00901a10
XmlTextWriter::XmlTextWriter(unsigned char bPretty, int nEncoding)
{
    mOutputEncoding = nEncoding;
    *(void**)this = (void*)0x143a1c0;
    mFormatPretty = bPretty;
    mbSimpleElement = 0;
    mnState = 0;
    mnIndentLevel = 0;
    mnIndentSpaces = 2;
    mLineEnd = 1;
    mpOutputStream = 0;
}

// @ 0x00901a50
XmlTextWriter::~XmlTextWriter()
{
    *(void**)this = (void*)0x143a1c0;
    if (mpOutputStream != 0) {
        void* p = mpOutputStream;
        ((void(__thiscall*)(void*))(*(void***)p)[2])(p);
    }
}

// @ 0x009014c0
bool XmlTextWriter::WriteEscapedString(const wchar_t* str)
{
    const wchar_t* p = str;
    const wchar_t* start = str;
    wchar_t c = *p;
    if (c != 0) {
        do {
            switch (c) {
            case L'"':
            case L'&':
            case L'\'':
            case L'<':
            case L'>':
                if (start < p && !WriteData(start, (int)(p - start)))
                    return false;
                switch (c) {
                case L'&':  if (!WriteData(L"&amp;", 5))  return false;
                case L'<':  if (!WriteData(L"&lt;", 4))   return false;
                case L'>':  if (!WriteData(L"&gt;", 4))   return false;
                case L'"':  if (!WriteData(L"&quot;", 6)) return false;
                case L'\'': if (!WriteData(L"&apos;", 6)) return false;
                }
                start = p + 1;
                break;
            default:
                break;
            }
            c = p[1];
            ++p;
        } while (c != 0);
        if (start < p && !WriteData(start, (int)(p - start)))
            return false;
    }
    return true;
}

// @ 0x00901630
bool XmlTextWriter::CloseCurrentElement()
{
    switch (mnState) {
    case kStateElement:
        if (!WriteData((const wchar_t*)0x140a054, 1)) return false;
        break;
    case kStatePI:
        if (!WriteData((const wchar_t*)0x143a110, 2)) return false;
        break;
    case kStateCDATA:
        if (!WriteData((const wchar_t*)0x143a118, 3)) return false;
        break;
    default:
        break;
    }
    mnState = 0;
    return true;
}

// @ 0x00901690
bool XmlTextWriter::BeginProcessingInstruction(const wchar_t* s)
{
    if (CloseCurrentElement()) {
        if (WriteData(L"<?", 2)) {
            int n = (int)wcslen(s);
            if (WriteData(s, n)) {
                mbSimpleElement = 0;
                mnState = 2;
                return true;
            }
        }
    }
    return false;
}

// @ 0x00901700
bool XmlTextWriter::EndProcessingInstruction()
{
    EState s = (EState)mnState;
    mbSimpleElement = 0;
    switch (s) {
    case kStatePI:
        mnState = kStateChars;
        return WriteData(L"?>", 2);
    case kStateChars:
    case kStateElement:
        mnState = kStateChars;
        return false;
    case kStateCDATA:
        return false;
    default:
        return false;
    }
}

// @ 0x00901740
bool XmlTextWriter::AppendAttribute(const wchar_t* name, const wchar_t* value)
{
    if (mnState != 1 && mnState != 2)
        return false;
    return (WriteData(L" ", 1)
         && WriteNameRaw(name)
         && WriteData(L"=\"", 2)
         && WriteEscapedString(value)
         && WriteData(L"\"", 1)) ? 1 : 0;
}

// @ 0x009018a0
int XmlTextWriter::WriteCharData(const wchar_t* s)
{
    if (CloseCurrentElement()) {
        if (WriteEscapedString(s))
            return 1;
    }
    return 0;
}

// @ 0x009018d0
bool XmlTextWriter::WriteCDATA(const wchar_t* s)
{
    if (mnState != 3) {
        if (!CloseCurrentElement())
            return false;
        if (!WriteData(L"<![CDATA[", 9))
            return false;
        mnState = 3;
    }
    int n = (int)wcslen(s);
    return WriteData(s, n);
}

// @ 0x00901930
void XmlTextWriter::WriteName(const wchar_t* s)
{
    int n = (int)wcslen(s);
    WriteData(s, n);
}

// @ 0x00901960
bool XmlTextWriter::WriteXmlHeader()
{
    bool ok = WriteProlog(L"<?xml") && WriteNameValue(L"version", L"1.0");
    switch (mOutputEncoding) {
    default:
        if (ok && !WriteNameValue(L"encoding", L"UTF-8")) return false;
        break;
    case 3:
        if (ok && !WriteNameValue(L"encoding", L"US-ASCII")) return false;
        break;
    case 2:
        if (ok && !WriteNameValue(L"encoding", L"ISO-8859-1")) return false;
        break;
    case 1:
        if (ok && !WriteNameValue(L"encoding", L"UTF-16")) return false;
        break;
    }
    if (!WriteEpilog()) return false;
    return true;
}

// @ 0x00901a70
bool XmlTextWriter::WriteIndent()
{
    if (!mFormatPretty)
        return true;
    int n = 2 - (mLineEnd != 1);
    int max = 0x43 - n;
    int count = mnIndentSpaces * mnIndentLevel;
    const wchar_t* sEnd = L"\r\n                                                                ";
    if (count > 0) {
        int chunk = (max <= count) ? max : count;
        if (!WriteData(sEnd, chunk + n))
            return false;
        count -= chunk;
        if (count > 0) {
            do {
                chunk = (max <= count) ? max : count;
                if (!WriteData(sEnd + n, chunk))
                    return false;
                count -= chunk;
            } while (count > 0);
        }
    }
    return true;
}

// @ 0x00901b30
bool XmlTextWriter::BeginElement(const wchar_t* name)
{
    if (CloseCurrentElement()) {
        if (WriteIndent()) {
            if (WriteData(L"<", 1)) {
                if (WriteNameRaw(name)) {
                    ++mnIndentLevel;
                    mnState = 1;
                    mbSimpleElement = 1;
                    return true;
                }
            }
        }
    }
    return false;
}

// @ 0x00901b90
bool XmlTextWriter::EndElement(const wchar_t* name)
{
    EState s = (EState)mnState;
    --mnIndentLevel;
    switch (s) {
    case kStateElement:
        mnState = 0;
        mbSimpleElement = 0;
        return WriteData(L"/>", 2);
    case kStateCDATA:
        CloseCurrentElement();
        // fall through
    case kStateChars:
        if (mbSimpleElement == 0) {
            if (!WriteIndent())
                return false;
        }
        break;
    case kStatePI:
        return false;
    default:
        return false;
    }
    mbSimpleElement = 0;
    return (WriteData(L"</", 2)
         && WriteData(name, (int)wcslen(name))
         && WriteData(L">", 1)) ? 1 : 0;
}

// @ 0x00901c60
bool XmlTextWriter::WriteComment(const wchar_t* s, unsigned char bIndent)
{
    const wchar_t* p = s;
    const wchar_t* start = s;
    if (!CloseCurrentElement())
        return false;
    if (bIndent != 0) {
        if (!WriteIndent())
            return false;
    }
    if (!WriteData(L"<!-- ", 5))
        return false;
    wchar_t c = *p;
    if (c != 0) {
        do {
            ++p;
            if (c == L'-') {
                if (start < p && !WriteData(start, (int)(p - start) + 1))
                    return false;
                while (*p == L'-')
                    ++p;
            }
            c = *p;
        } while (c != 0);
        if (start < p && !WriteData(start, (int)(p - start)))
            return false;
    }
    return WriteData(L" -->", 4) != 0;
}

// @ 0x00901d30
void XmlTextWriter::SetStream(void* pStream, unsigned char bPretty)
{
    void* old = mpOutputStream;
    if (pStream != old) {
        if (pStream != 0)
            ((void(__thiscall*)(void*))(*(void***)pStream)[1])(pStream);
        mpOutputStream = pStream;
        if (old != 0)
            ((void(__thiscall*)(void*))(*(void***)old)[2])(old);
    }
    mFormatPretty = bPretty;
}

// @ 0x00901d90
bool XmlTextWriter::WriteText(const void* p, unsigned int n)
{
    void* stream = mpOutputStream;
    if (stream != 0) {
        return IO_WriteEncoded(stream, p, n,
                               ((unsigned int*)0x143a2ac)[mOutputEncoding]);
    }
    return false;
}

} } // namespace EA::XML

// @ 0x009017d0
bool __cdecl FUN_009017d0(XmlTextWriter* pThis, const wchar_t* name,
                          const wchar_t* fmt, ...)
{
    if (pThis->mnState != 1 && pThis->mnState != 2)
        return false;
    wchar_t buf[256];
    va_list ap;
    va_start(ap, fmt);
    int n = Vsnprintf16(buf, 0x100, fmt, ap);
    va_end(ap);
    if (n >= 0x100)
        return false;
    return (pThis->WriteData(L" ", 1)
         && pThis->WriteNameRaw(name)
         && pThis->WriteData(L"=\"", 2)
         && pThis->WriteEscapedString(buf)
         && pThis->WriteData(L"\"", 1)) ? 1 : 0;
}

// ===========================================================================
// XmlTextReader implementation
// ===========================================================================
namespace EA { namespace XML {

// @ 0x009013e0
bool XmlTextReader::FUN_009013e0()
{
    if (m40 != 0)
        m40 = *(int*)m40;
    if (m40 == 0) {
        ReaderRange* r = &mRange;
        unsigned int v = (unsigned int)m7c;
        if (v > r->m04 && v < r->m08) {
            r->m0c = v;
            r->m10 = v;
        } else {
            r->FUN_00928c40(v);
        }
        m40 = 0;
        m3c = 0;
        m38 = 0;
        if (!FUN_00901340())
            return false;
        m40 = m38;
    }
    return true;
}

// @ 0x00901440
void XmlTextReader::FUN_00901440(int a, int b)
{
    if (FUN_00900a30(a, b))
        m6c = FUN_0090aed0(0, (void*)0x154db1c, 0);
    FUN_00901220();
}

// @ 0x00901480
void XmlTextReader::FUN_00901480(int a, int b, int c)
{
    if (FUN_00900610(a, b, c))
        m6c = FUN_0090aed0(0, (void*)0x154db1c, 0);
    FUN_00901220();
}

// @ 0x00901df0
bool XmlTextReader::FUN_00901df0()
{
    int p = m38;
    if (p == 0)
        return false;
    if (m3c == 0) {
        m3c = p;
        m40 = p;
        while (*(int*)m3c != 0) {
            m3c = *(int*)m3c;
        }
    } else if (m40 != 0) {
        m40 = *(int*)m40;
    }
    return m40 != 0;
}

// @ 0x00901e40
bool XmlTextReader::FUN_00901e40()
{
    if (m38 == 0)
        return false;
    if (m3c == 0)
        return false;
    return m40 != 0;
}

} } // namespace EA::XML

// @ 0x00901e60
bool __cdecl FUN_00901e60(const wchar_t* s)
{
    wint_t c;
    if (s == 0 || (c = *s) == 0)
        return true;
    do {
        if (!iswctype(c, 8) && !iswctype(c, 0x20))
            break;
        c = s[1];
        ++s;
    } while (c != 0);
    return *s == 0;
}

// ===========================================================================
// eastl hashtable implementation
// ===========================================================================
static int cmp16(const wchar_t* p1, const wchar_t* p2)
{
    for (;;) {
        wchar_t c1 = *p1;
        wchar_t c2 = *p2;
        if (c1 != c2) return (c1 < c2) ? -1 : 1;
        if (c1 == 0) return 0;
        c1 = p1[1];
        c2 = p2[1];
        if (c1 != c2) return (c1 < c2) ? -1 : 1;
        p1 += 2;
        p2 += 2;
        if (c1 == 0) return 0;
    }
}

// @ 0x00901f90
HashNode* HashA::FUN_00901f90(HashNode* pHead, const wchar_t* const& key, unsigned int h)
{
    (void)h;
    while (pHead != 0) {
        if (cmp16(key, pHead->first) == 0)
            return pHead;
        pHead = pHead->mpNext;
    }
    return 0;
}

// @ 0x009020b0
HIter HashA::FUN_009020b0(const wchar_t* const& key)
{
    unsigned int h = (key != 0) ? FNV1_String16(key, 0x811c9dc5u, 0) : 0;
    unsigned int cnt = mnBucketCount;
    void** pBucket = mpBucket + (h % cnt);
    HashNode* n = FUN_00901f90((HashNode*)*pBucket, key, h);
    HIter it;
    if (n != 0) {
        it.mpNode = n;
        it.mpBucket = pBucket;
    } else {
        it.mpNode = mpBucket[cnt];
        it.mpBucket = mpBucket + cnt;
    }
    return it;
}

// @ 0x00902140
InsertRet HashA::FUN_00902140(const StrIdPair& value, int t)
{
    (void)t;
    unsigned int h = (value.first != 0) ? FNV1_String16(value.first, 0x811c9dc5u, 0) : 0;
    unsigned int cnt = mnBucketCount;
    unsigned int idx = h % cnt;
    void** pBucket = mpBucket + idx;
    HashNode* pNode = FUN_00901f90((HashNode*)*pBucket, value.first, h);
    InsertRet res;
    if (pNode != 0) {
        res.mpNode = pNode;
        res.mpBucket = pBucket;
        res.mbInserted = 0;
        return res;
    }
    RehashPolicy::Result rr;
    ((RehashPolicy*)((char*)this + 0x10))->FUN_00921440(&rr, cnt, mnElementCount, 1);
    HashNode* pNew = (HashNode*)EA_operator_new(0xc, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (pNew != 0) {
        pNew->first = value.first;
        pNew->second = value.second;
    }
    pNew->mpNext = 0;
    if (rr.mbFlag) {
        idx = h % rr.mnNewBucketCount;
        FUN_00901ec0(rr.mnNewBucketCount);
    }
    void** slot = mpBucket + idx;
    pNew->mpNext = (HashNode*)*slot;
    *slot = pNew;
    ++mnElementCount;
    res.mpNode = pNew;
    res.mpBucket = mpBucket + idx;
    res.mbInserted = 1;
    return res;
}

// @ 0x00901ec0
void HashA::FUN_00901ec0(unsigned int nBucketCount)
{
    size_t size = nBucketCount * 4;
    void* pDst = EA_operator_new(size + 4, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    FUN_011e073e(pDst, 0, size);
    *(unsigned int*)((char*)pDst + size) = 0xffffffffu;
    for (unsigned int i = 0; i < mnBucketCount; ++i) {
        HashNode* n = (HashNode*)mpBucket[i];
        while (n != 0) {
            unsigned int h = (n->first != 0) ? FNV1_String16(n->first, 0x811c9dc5u, 0) : 0;
            unsigned int idx2 = h % nBucketCount;
            mpBucket[i] = (void*)n->mpNext;
            n->mpNext = *(HashNode**)((char*)pDst + idx2 * 4);
            *(HashNode**)((char*)pDst + idx2 * 4) = n;
            n = (HashNode*)mpBucket[i];
        }
    }
    if (mnBucketCount > 1)
        EA_operator_delete(mpBucket);
    mnBucketCount = nBucketCount;
    mpBucket = (void**)pDst;
}

// ===========================================================================
// TokenIOContext string helpers
// ===========================================================================
namespace EA { namespace XML {

// @ 0x00902250
int TokenIOContext::GetString(const wchar_t* str)
{
    HashA* a = mStringsA;
    HIter it = a->FUN_009020b0(str);
    if (it.mpNode != a->mpBucket[a->mnBucketCount])
        return ((HashNode*)it.mpNode)->second;
    return 0;
}

// @ 0x00902380
wchar_t* sStrDup(const wchar_t* str, TokenIOContext* ctx)
{
    HashA* a = ctx->mStringsA;
    HIter it = a->FUN_009020b0(str);
    if (it.mpNode != a->mpBucket[a->mnBucketCount]) {
        int id = ((HashNode*)it.mpNode)->second;
        if (id != 0) {
            HashB* b = ctx->mStringsB;
            HIter it2 = b->FUN_005ed0((const unsigned int&)id);
            if (it2.mpNode != b->mpBucket[b->mnBucketCount])
                return (wchar_t*)((IdStrPair*)it2.mpNode)->second;
            return 0;
        }
    }
    int len = (int)wcslen(str);
    wchar_t* p = (wchar_t*)ctx->mAllocator.Allocate(len * 2 + 2);
    if (p == 0)
        return 0;
    const wchar_t* q = str;
    do {
        wchar_t c = *q;
        *p = c;
        ++q;
        ++p;
        if (c == 0) break;
    } while (1);
    return p - (len + 1);
}

} } // namespace EA::XML
