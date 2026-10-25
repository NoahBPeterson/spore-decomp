// Slice s00900410 (bfs2 #21), 32-bit MSVC 2008.
// EA::XML::XmlReader / XmlTextReader (expat-based XML reader) + XHTML StylesheetFactory.
// Layouts taken from the 2008 dev PDB; the module is plain /O2 cl 15.00.
#include <new>
#include <intrin.h>

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

extern "C" int __cdecl strcmp(const char*, const char*);
#pragma intrinsic(strcmp)

// ---------------------------------------------------------------------------
// EA::Allocator
// ---------------------------------------------------------------------------
namespace EA { namespace Allocator {
class ICoreAllocator;
class StackAllocator {
public:
    uint32 mnDefaultBlockSize;       // +0x00
    void*  mpCurrentBlock;           // +0x04
    char*  mpCurrentBlockEnd;        // +0x08
    char*  mpCurrentObjectBegin;     // +0x0c
    char*  mpCurrentObjectEnd;       // +0x10
    void*  mpCoreAllocationFunction; // +0x14
    void*  mpCoreFreeFunction;       // +0x18
    void*  mpCoreFunctionContext;    // +0x1c
    void*  mpTopBookmark;            // +0x20

    StackAllocator(void* pBlock = 0, uint32 blockSize = 0xffffffff, void* alloc = 0,
                   void* free = 0, void* ctx = 0);                 // 0x00928cd0
    bool AllocateNewBlock(uint32 size);                            // 0x00928ba0
    void Init(void* pBlock, uint32 size, void* alloc, void* free, void* ctx); // 0x00928b00
    void Reset();                                                  // 0x00928dc0
    void* Allocate(uint32 size) {
        if ((int)(mpCurrentBlockEnd - mpCurrentObjectBegin) - (int)size < 0) {
            if (!AllocateNewBlock(size))
                return 0;
        }
        char* p = mpCurrentObjectBegin;
        mpCurrentObjectBegin = p + size;
        mpCurrentObjectEnd = p + size;
        return p;
    }
};
ICoreAllocator* GetDefaultAllocator();   // 0x00925cb0
}}

// ---------------------------------------------------------------------------
// types
// ---------------------------------------------------------------------------
struct Token {
    Token* mpNext;       // +0x00
    int    mToken;       // +0x04
    int    field8;       // +0x08
    int    fieldc;       // +0x0c
    int    field10;      // +0x10
    union {
        int* mpEntries;      // +0x14 (element tokens)
        int  mnValueLength;  // +0x14 (text tokens)
    };
    int    mnEntryCount; // +0x18
};

struct MemoryStream {
    void** vftable;             // +0x00
    void*  mpSharedPointer;     // +0x04
    int    mnRefCount;          // +0x08
    uint32 mnSize;              // +0x0c
    uint32 mnCapacity;          // +0x10
    uint32 mnPosition;          // +0x14
    bool   mbResizeEnabled;     // +0x18
    float  mfResizeFactor;      // +0x1c
    int    mnResizeIncrement;   // +0x20
    MemoryStream(int);                                          // 0x0093bd50
    void SetData(const void* p, uint32 size, int a, int b, int c); // 0x0093be30
    void Reset();                                               // 0x0093bde0
    bool Grow(uint32 size);                                     // 0x00928ba0-ish
};

// ---------------------------------------------------------------------------
// EA::IO::IStream (vtable order from the canonical header; only slots used here)
// ---------------------------------------------------------------------------
namespace EA { namespace IO {
enum PositionType { kPositionTypeBegin = 0 };
class IStream {
public:
    virtual ~IStream();                                  // slot 0
    virtual int  AddRef();                               // slot 1 (+0x04)
    virtual int  Release();                              // slot 2 (+0x08)
    virtual int  GetType() const;                        // slot 3
    virtual int  GetAccessFlags() const;                 // slot 4
    virtual int  GetState() const;                       // slot 5
    virtual bool Close();                                // slot 6 (+0x18)
    virtual uint32 GetSize() const;                      // slot 7 (+0x1c)
    virtual bool SetSize(uint32 size);                   // slot 8
    virtual int  GetPosition(PositionType type) const;   // slot 9 (+0x24)
    virtual bool SetPosition(int pos, PositionType type);// slot 10 (+0x28)
    virtual uint32 GetAvailable() const;                 // slot 11
    virtual uint32 Read(void* p, uint32 size);           // slot 12 (+0x30)
    virtual bool Flush();                                // slot 13
    virtual bool Write(const void* p, uint32 size);      // slot 14
};
}}

class XmlReader {
public:
    void** vftable;                 // +0x00
    int    mResultCode;             // +0x04
    int    mAllocatorContextName;   // +0x08
    int    mAllocatorContextAlloc;  // +0x0c
    char   mAllocator[0x24];        // +0x10
    EA::IO::IStream* mpInputStream; // +0x34
    Token* mpFirstToken;            // +0x38
    Token* mpLastToken;             // +0x3c
    Token* mpCurrentToken;          // +0x40
    void*  mpSourcePath;            // +0x44
    char   mMemoryStream[0x24];     // +0x48

    int  GetTokenType();
    int  GetTokenCount();
    int  GetEntryA(int idx);
    int  GetEntryB(int idx);
    int  IsAtEnd();
    void FUN_00900610(void* a1, void* a2, void* a3);
    int  FUN_00900720(const uint16* s);
    void FUN_009007b0();
    __declspec(noinline) void* ReadString(EA::Allocator::StackAllocator* pAlloc, uint32* pOut);
    void FUN_009008f0();
    void* FUN_00900970(const void* v);

    XmlReader(void* pAllocator);
    ~XmlReader();
    void* DeletingDtor(char flags);
    char  InitAllocator(EA::IO::IStream* pStream, const uint16* pPath);
};

class XmlTextReader : public XmlReader {
public:
    void*  mpParser;             // +0x6c
    bool   mbEndOfStream;        // +0x70
    int    mnDepth;              // +0x74
    void*  mpTokenBufferStart;   // +0x78
    void*  mpTokenBufferEnd;     // +0x7c
    uint32 mnTokenBufferBytes;   // +0x80
    uint32 mnFlags;              // +0x84

    int  MapError(int err);
    char Read();

    XmlTextReader(void* pAllocator);
    ~XmlTextReader();
    XmlTextReader* DeletingDtor(char flags);
    char InitParser();
};

// expat callback thunks: __cdecl free functions with an explicit reader parameter
void OnStartElement2(XmlTextReader* t, void* a2, void* a3, void* a4);   // 0x00900db0
void OnStartElement(XmlTextReader* t, void* a2, int* a3);               // 0x00900e60
void OnEndElement(XmlTextReader* t, void* a2);                          // 0x00900f70
void OnCharacterData(XmlTextReader* t, void* a2, int a3);               // 0x00900ff0
void OnComment(XmlTextReader* t, void* a2);                             // 0x009010c0
void OnPI(XmlTextReader* t, void* a2, void* a3);                        // 0x00901150

extern void* g_vtblXmlReader;      // 0x0143a094
extern void* g_vtblXmlTextReader;  // 0x0143a0b0

// helper: pool (0x016c8b44)
struct MemPool { void LockedRealloc(void* p, uint32 size, int align); };
extern MemPool* g_memPool;

// extern XML helpers
void XML_ParserFree(void* parser);                                       // 0x009055d0
int  XML_Parse(void* parser, const char* buf, int len, int isFinal);     // 0x00905740
void FUN_009032e0(void* parser, void* ctx);
void FUN_00903300(void* parser, void* start, void* end);
void FUN_00903320(void* parser, void* chardata);
void FUN_00903330(void* parser, void* pi);
void FUN_00903340(void* parser, void* comment);
void FUN_00903370(void* parser, void* a, void* b);
void FUN_00903390(void* parser, void* a, void* b);
int  FUN_00903b40(void* parser);
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n); // 0x011e0744
void* FUN_00900900(short* s, EA::Allocator::StackAllocator* a); // 0x00900900
extern "C" void g_use_ptr(uint32*);
extern "C" uint16 g_wcharNull;                 // 0x0141a154
extern "C" const char* gMimeTextCss;           // 0x0154db10

void FUN_00925bf0();                           // 0x00925bf0 (StackAllocator core alloc)
void FUN_00925c20();                           // 0x00925c20 (StackAllocator core free)
void FUN_00c2e4e0();                           // 0x00c2e4e0 (bare ret callback)
void __fastcall Fn8e2ed0(void* p);             // 0x008e2ed0 (CSSParser dtor)
void __cdecl operator_delete(void* p);         // 0x00f47380
void* __cdecl operator_new(unsigned size, const char* name, int, int, int, int); // 0x00f473a0

inline void* operator new(unsigned size, const char* name, int a, int b, int c, int d)
{
    return operator_new(size, name, a, b, c, d);
}

#define VFN0(p, off) (*(void (__thiscall**)(void*))((char*)(*(void**)(p)) + (off)))
#define VFN0C(p, off) (*(char (__thiscall**)(void*))((char*)(*(void**)(p)) + (off)))
#define VFN2(p, off) (*(void (__thiscall**)(void*, void*, void*))((char*)(*(void**)(p)) + (off)))
#define VFN1a(p, off) (*(void (__thiscall**)(void*, void*))((char*)(*(void**)(p)) + (off)))

// ===========================================================================
// XHTML stylesheet factory types (slice tail)
// ===========================================================================
struct CStr {
    char* mpBegin;   // +0x00
    char* mpEnd;     // +0x04
    char* mpCapacity;// +0x08
};

struct ByteVector {  // eastl::vector<unsigned char>, size 0x14
    uint8* mpBegin;     // +0x00
    uint8* mpEnd;       // +0x04
    uint8* mpCapacity;  // +0x08
    uint32 mPad[2];     // +0x0c
    void resize(uint32 n);   // 0x004c0410
};

struct WStr {
    uint16* mpBegin;    // +0x00
    uint16* mpEnd;      // +0x04
    uint16* mpCapacity; // +0x08
    void resize(uint32 n);                                    // 0x00429520
    void clear() {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
};

struct ResourceRequest {
    char    pad0[8];
    void*   mpErrorListener;  // +0x08
    void*   mpURL;            // +0x0c
    CStr    mTypeStr;         // +0x10
    char    pad1[0x24 - 0x1c];
    int     mEncoding;        // +0x24
    int     mEncodingSource;  // +0x28
    char    pad2[0x3c - 0x2c];
    EA::IO::IStream* mpStream; // +0x3c
    bool SetEncoding(int enc, int source);  // 0x009002f0
};

class Stylesheet {
public:
    virtual void AddRef();    // slot 0 (+0x00)
    virtual void Release();   // slot 1 (+0x04)
    int  mField4;             // +0x04
    char mAllocator[0x24];    // +0x08
    char mPad[0x70 - 0x2c];
    Stylesheet(void* p);      // 0x008f9db0
};

class CSSParser {
public:
    void* Fn8f3970(void* allocator, uint16* begin, int count);  // 0x008f3970
    bool  Parse(Stylesheet* pSheet);                            // 0x008f9220
    uint32 mPad0[0x48 / 4];
    void*  mpErrorListener;   // +0x48
    uint32 mPad1[2];
};

struct SheetPtr {
    Stylesheet* mp;
    SheetPtr(Stylesheet* p) : mp(p) { if (mp) mp->AddRef(); }
    ~SheetPtr() { if (mp) mp->Release(); }
    operator Stylesheet*() const { return mp; }
    Stylesheet* operator->() const { return mp; }
};

class StylesheetFactory {
public:
    void**     vftable;          // +0x00
    int        mRefCount;        // +0x04
    ByteVector mConvertBuffer;   // +0x08
    WStr       mDataBuffer;      // +0x1c

    int CreateResource(Stylesheet** ppOut, uint32* pSize, ResourceRequest* req); // 0x00900410
    int FUN_00900370(EA::IO::IStream* pStream);                                  // 0x00900370
};

namespace EA { namespace Text {
uint32 ConvertEncoding(uint8* src, uint32 srcLen, int srcEnc, WStr* dst); // 0x0093cfb0
}}

// ===========================================================================
// XmlReader members
// ===========================================================================

// @ 0x00900660
int XmlReader::GetTokenType()
{
    XmlReader* t = this;
    if (t->mpFirstToken != 0 && t->mpCurrentToken != 0)
        return t->mpCurrentToken->mToken;
    return 0;
}

// @ 0x009006a0
int XmlReader::GetTokenCount()
{
    XmlReader* t = this;
    Token* p = t->mpCurrentToken;
    if (p != 0 && p->mToken == 1)
        return p->mnEntryCount;
    return 0;
}

// @ 0x009006c0
int XmlReader::GetEntryA(int idx)
{
    XmlReader* t = this;
    Token* p = t->mpCurrentToken;
    if (p != 0 && p->mToken == 1 && idx >= 0 && idx < p->mnEntryCount)
        return p->mpEntries[idx * 2];
    return 0;
}

// @ 0x009006f0
int XmlReader::GetEntryB(int idx)
{
    XmlReader* t = this;
    Token* p = t->mpCurrentToken;
    if (p != 0 && p->mToken == 1 && idx >= 0 && idx < p->mnEntryCount)
        return p->mpEntries[idx * 2 + 1];
    return 0;
}

// @ 0x00900d90
int XmlReader::IsAtEnd()
{
    XmlReader* t = this;
    if (t->mpCurrentToken == 0 && *(char*)((char*)t + 0x70) != 0)
        return 1;
    return 0;
}

// @ 0x00900610
void XmlReader::FUN_00900610(void* a1, void* a2, void* a3)
{
    XmlReader* t = this;
    MemoryStream* ms = (MemoryStream*)((char*)t + 0x48);
    VFN0(ms, 0x04)(ms);
    VFN0(ms, 0x18)(ms);
    ms->SetData(a1, (uint32)a2, 1, 0, 0);
    VFN2(t, 0x08)(t, ms, a3);
}

// @ 0x00900720
int XmlReader::FUN_00900720(const uint16* s)
{
    XmlReader* t = this;
    Token* p = t->mpCurrentToken;
    if (p != 0 && p->mToken == 1) {
        int n = p->mnEntryCount;
        for (int i = 0; i < n; i++) {
            const uint16* a = (const uint16*)p->mpEntries[i * 2];
            const uint16* b = s;
            while (*a == *b) {
                if (*a == 0)
                    return p->mpEntries[i * 2 + 1];
                if (a[1] != b[1])
                    break;
                a += 2; b += 2;
                if (a[-1] == 0)
                    break;
            }
        }
    }
    return 0;
}

// @ 0x009007b0
void XmlReader::FUN_009007b0()
{
    XmlReader* t = this;
    if (t->mpCurrentToken == 0)
        return;
    int depth = t->mpCurrentToken->field10;
    if (t->mpCurrentToken->mToken == 1 && !VFN0C(t, 0x0c)(t))
        return;
    Token* p = t->mpCurrentToken;
    if (p == 0)
        return;
    do {
        if (!VFN0C(t, 0x0c)(t))
            break;
        if (p->field10 <= depth)
            break;
        p = t->mpCurrentToken;
    } while (p != 0);
}

// @ 0x00900800
void* XmlReader::ReadString(EA::Allocator::StackAllocator* pAlloc, uint32* pOut)
{
    Token* p = this->mpCurrentToken;
    if (p == 0)
        return 0;
    if (p->mToken == 1 && !VFN0C(this, 0x0c)(this))
        return 0;
    p = this->mpCurrentToken;
    while (p != 0 && p->mToken == 4) {
        uint32 bytes = (uint32)(p->mnValueLength * 2);
        if (pAlloc->mpCurrentObjectEnd + bytes <= pAlloc->mpCurrentBlockEnd
            || pAlloc->AllocateNewBlock(bytes)) {
            memcpy(pAlloc->mpCurrentObjectEnd, (char*)p->fieldc, bytes);
            pAlloc->mpCurrentObjectEnd += bytes;
        }
        if (!VFN0C(this, 0x0c)(this))
            return 0;
        p = this->mpCurrentToken;
    }
    uint32 n = (uint32)(pAlloc->mpCurrentObjectEnd - pAlloc->mpCurrentObjectBegin) >> 1;
    *pOut = n;
    if (n == 0)
        return 0;
    if (pAlloc->mpCurrentObjectEnd + 2 <= pAlloc->mpCurrentBlockEnd
        || pAlloc->AllocateNewBlock(2)) {
        *(uint16*)pAlloc->mpCurrentObjectEnd = g_wcharNull;
        pAlloc->mpCurrentObjectEnd += 2;
    }
    char* result = pAlloc->mpCurrentObjectBegin;
    char* aligned = (char*)(((uint32)pAlloc->mpCurrentObjectEnd + 7) & ~7u);
    pAlloc->mpCurrentObjectEnd = aligned;
    if ((uint32)aligned > (uint32)pAlloc->mpCurrentBlockEnd)
        pAlloc->mpCurrentObjectEnd = pAlloc->mpCurrentBlockEnd;
    pAlloc->mpCurrentObjectBegin = pAlloc->mpCurrentObjectEnd;
    return result;
}

// @ 0x009008f0
void XmlReader::FUN_009008f0()
{
    uint32 local;
    ReadString((EA::Allocator::StackAllocator*)this->mAllocator, &local);
}

// @ 0x00900900
void* FUN_00900900(short* s, EA::Allocator::StackAllocator* a)
{
    short* p = s;
    do { } while (*p++ != 0);
    uint32 n = ((uint32)((p - (s + 1)) * 2) + 9) & ~7u;
    char* dst;
    if ((int)((a->mpCurrentBlockEnd - a->mpCurrentObjectBegin) - n) < 0) {
        if (!a->AllocateNewBlock(n))
            return 0;
    }
    dst = a->mpCurrentObjectBegin;
    a->mpCurrentObjectBegin = dst + n;
    a->mpCurrentObjectEnd = dst + n;
    short* d = (short*)dst;
    while ((*d++ = *s++) != 0) { }
    return dst;
}

// @ 0x00900970
void* XmlReader::FUN_00900970(const void* v)
{
    return FUN_00900900((short*)v, (EA::Allocator::StackAllocator*)((char*)this + 0x10));
}

// @ 0x00900990
XmlReader::XmlReader(void* pAllocator)
{
    XmlReader* t = this;
    t->vftable = (void**)&g_vtblXmlReader;
    t->mResultCode = 0;
    t->mAllocatorContextName = 0;
    if (pAllocator == 0)
        pAllocator = EA::Allocator::GetDefaultAllocator();
    t->mAllocatorContextAlloc = (int)pAllocator;
    new (t->mAllocator) EA::Allocator::StackAllocator();
    t->mpInputStream = 0;
    t->mpFirstToken = 0;
    t->mpLastToken = 0;
    t->mpCurrentToken = 0;
    t->mpSourcePath = 0;
    new (t->mMemoryStream) MemoryStream(0);
}

// @ 0x009009e0
XmlReader::~XmlReader()
{
    XmlReader* t = this;
    t->vftable = (void**)&g_vtblXmlReader;
    ((EA::Allocator::StackAllocator*)(t->mAllocator))->Reset();
    if (t->mpInputStream != 0) {
        int* p = (int*)t->mpInputStream;
        t->mpInputStream = 0;
        (*(void(__thiscall**)(int*))((char*)*p + 8))(p);
    }
    ((MemoryStream*)(t->mMemoryStream))->Reset();
    if (t->mpInputStream != 0) {
        int* p = (int*)t->mpInputStream;
        (*(void(__thiscall**)(int*))((char*)*p + 8))(p);
    }
    ((EA::Allocator::StackAllocator*)(t->mAllocator))->Reset();
}

// @ 0x00900a30
char XmlReader::InitAllocator(EA::IO::IStream* pStream, const uint16* pPath)
{
    XmlReader* t = this;
    EA::Allocator::StackAllocator* a = (EA::Allocator::StackAllocator*)t->mAllocator;
    a->Reset();
    a->mnDefaultBlockSize = 0x200;
    a->Init(0, 0, (void*)&FUN_00925bf0, (void*)&FUN_00925c20, &t->mAllocatorContextName);
    EA::IO::IStream* old = t->mpInputStream;
    if (pStream != old) {
        if (pStream != 0)
            pStream->AddRef();
        t->mpInputStream = pStream;
        if (old != 0)
            old->Release();
    }
    if (pPath != 0)
        t->mpSourcePath = FUN_00900900((short*)pPath, a);
    return 1;
}

// @ 0x00900ab0
void* XmlReader::DeletingDtor(char flags)
{
    XmlReader* t = this;
    t->vftable = (void**)&g_vtblXmlReader;
    ((EA::Allocator::StackAllocator*)t->mAllocator)->Reset();
    EA::IO::IStream* p = t->mpInputStream;
    if (p != 0) {
        t->mpInputStream = 0;
        p->Release();
    }
    ((MemoryStream*)t->mMemoryStream)->Reset();
    if (t->mpInputStream != 0)
        t->mpInputStream->Release();
    ((EA::Allocator::StackAllocator*)t->mAllocator)->Reset();
    if (flags & 1)
        operator_delete(t);
    return t;
}

// @ 0x00900b10
void FUN_00900b10(void* p, uint32 size)
{
    g_memPool->LockedRealloc(p, size, 0);
}

// ===========================================================================
// XmlTextReader members
// ===========================================================================

// @ 0x00900b30
XmlTextReader::XmlTextReader(void* pAllocator) : XmlReader(pAllocator)
{
    XmlTextReader* t = this;
    t->mpParser = 0;
    t->mbEndOfStream = 0;
    t->mnDepth = 0;
    t->mpTokenBufferStart = 0;
    t->mpTokenBufferEnd = 0;
    t->mnTokenBufferBytes = 0;
    t->mnFlags = 0;
    t->vftable = (void**)&g_vtblXmlTextReader;
}

// @ 0x00900b70
XmlTextReader::~XmlTextReader()
{
    XmlTextReader* t = this;
    t->vftable = (void**)&g_vtblXmlTextReader;
    if (t->mpParser != 0)
        XML_ParserFree(t->mpParser);
}

// @ 0x00900ba0
int XmlTextReader::MapError(int err)
{
    (void)this;
    switch (err) {
    case 0: return 0;
    case 1: return 3;   case 2: return 4;   case 3: return 5;
    case 4: return 6;   case 5: return 7;   case 6: return 8;
    case 7: return 9;   case 8: return 10;  case 9: return 0xb;
    case 10: return 0xc; case 0xb: return 0xd; case 0xc: return 0xe;
    case 0xd: return 0xf; case 0xe: return 0x10; case 0xf: return 0x11;
    case 0x10: return 0x12; case 0x11: return 0x13; case 0x12: return 0x14;
    case 0x13: return 0x15; case 0x14: return 0x16; case 0x15: return 0x17;
    case 0x16: return 0x18; case 0x17: return 0x19; case 0x18: return 0x1a;
    case 0x19: return 0x1b; case 0x1a: return 0x1c; case 0x1b: return 0x1d;
    case 0x1c: return 0x1e; case 0x1d: return 0x1f; case 0x1e: return 0x20;
    case 0x1f: return 0x21; case 0x20: return 0x22; case 0x21: return 0x23;
    case 0x22: return 0x24; case 0x23: return 0x25; case 0x24: return 0x26;
    case 0x25: return 0x27;
    default: return 0x28;
    }
}

// @ 0x00900d90 (defined above as IsAtEnd)

// token helpers
static Token* AllocToken(XmlTextReader* t, uint32 size)
{
    return (Token*)((EA::Allocator::StackAllocator*)(t->mAllocator))->Allocate(size);
}
static void AppendTok(XmlTextReader* t, Token* p)
{
    if (t->mpLastToken != 0) {
        t->mpLastToken->mpNext = p;
        t->mpLastToken = p;
    } else {
        t->mpFirstToken = p;
        t->mpLastToken = p;
    }
}

// @ 0x00900db0
void OnStartElement2(XmlTextReader* t, void* a2, void* a3, void* a4)
{
    if ((t->mnFlags & 8) == 0)
        return;
    Token* p = AllocToken(t, 0x20);
    if (p != 0)
        p->mToken = 6;
    else
        p = 0;
    p->field8 = (int)t->FUN_00900970(a2);
    p->fieldc = 0;
    p->mpEntries = (int*)t->FUN_00900970(a3);
    p->mnEntryCount = (int)t->FUN_00900970(a4);
    p->mpNext = 0;
    p->field10 = t->mnDepth;
    if (t->mpLastToken != 0) {
        t->mpLastToken->mpNext = p;
        t->mpLastToken = p;
    } else {
        t->mpFirstToken = p;
        t->mpLastToken = p;
    }
}

// @ 0x00900e60
void OnStartElement(XmlTextReader* t, void* a2, int* a3)
{
    Token* p = AllocToken(t, 0x20);
    if (!p)
        return;
    p->mToken = 1;
    int n = 0;
    while (a3[n] != 0)
        n++;
    p->mnEntryCount = n / 2;
    p->field8 = (int)t->FUN_00900970(a2);
    p->fieldc = 0;
    int* arr = (int*)((EA::Allocator::StackAllocator*)(t->mAllocator))
                   ->Allocate((uint32)(n * 4 + 7) & ~7u);
    p->mpEntries = arr;
    for (int i = 0; i < n; i++)
        arr[i] = (int)t->FUN_00900970((void*)a3[i]);
    p->mpNext = 0;
    p->field10 = t->mnDepth;
    if (t->mpLastToken != 0) {
        t->mpLastToken->mpNext = p;
        t->mnDepth++;
        t->mpLastToken = p;
    } else {
        t->mnDepth++;
        t->mpFirstToken = p;
        t->mpLastToken = p;
    }
}

// @ 0x00900f70
void OnEndElement(XmlTextReader* t, void* a2)
{
    Token* p = AllocToken(t, 0x18);
    if (!p)
        return;
    p->mToken = 2;
    p->field8 = (int)t->FUN_00900970(a2);
    p->fieldc = 0;
    t->mnDepth--;
    p->mpNext = 0;
    p->field10 = t->mnDepth;
    AppendTok(t, p);
}

// @ 0x00900ff0
void OnCharacterData(XmlTextReader* t, void* a2, int a3)
{
    Token* p = AllocToken(t, 0x18);
    if (p != 0)
        p->mToken = 4;
    else
        p = 0;
    p->field8 = 0;
    uint32 size = (uint32)(a3 * 2);
    uint32 n = (size + 9) & ~7u;
    char* dst = (char*)((EA::Allocator::StackAllocator*)(t->mAllocator))->Allocate(n);
    p->fieldc = (int)dst;
    memcpy(dst, a2, size);
    *(short*)(dst + size) = 0;
    p->mpEntries = (int*)a3;
    p->mpNext = 0;
    p->field10 = t->mnDepth;
    AppendTok(t, p);
}

// @ 0x009010c0
void OnComment(XmlTextReader* t, void* a2)
{
    if ((t->mnFlags & 1) == 0)
        return;
    Token* p = AllocToken(t, 0x18);
    if (!p)
        return;
    p->mToken = 3;
    p->field8 = 0;
    p->fieldc = (int)t->FUN_00900970(a2);
    p->mpNext = 0;
    p->field10 = t->mnDepth;
    AppendTok(t, p);
}

// @ 0x00901150
void OnPI(XmlTextReader* t, void* a2, void* a3)
{
    if ((t->mnFlags & 2) == 0)
        return;
    Token* p = AllocToken(t, 0x18);
    if (!p)
        return;
    p->mToken = 5;
    p->field8 = (int)t->FUN_00900970(a2);
    p->fieldc = (int)t->FUN_00900970(a3);
    p->mpNext = 0;
    p->field10 = t->mnDepth;
    AppendTok(t, p);
}

// @ 0x009011e0
XmlTextReader* XmlTextReader::DeletingDtor(char flags)
{
    XmlTextReader* t = this;
    t->vftable = (void**)&g_vtblXmlTextReader;
    if (t->mpParser != 0)
        XML_ParserFree(t->mpParser);
    ((XmlReader*)t)->~XmlReader();
    if (flags & 1)
        g_use_ptr((uint32*)t);
    return t;
}

// @ 0x00901220
char XmlTextReader::InitParser()
{
    XmlTextReader* t = this;
    int pos = t->mpInputStream->GetPosition(EA::IO::kPositionTypeBegin);
    uint16 wc = 0;
    int n = (int)t->mpInputStream->Read(&wc, 2);
    if (n == -1 || (n != 0 && wc == 0))
        return 0;
    t->mpInputStream->SetPosition(pos, EA::IO::kPositionTypeBegin);
    char* buf = (char*)((EA::Allocator::StackAllocator*)t->mAllocator)->Allocate(0x2000);
    t->mpTokenBufferStart = buf;
    t->mpTokenBufferEnd = buf + 0x2000;
    t->mnTokenBufferBytes = 0;
    t->mnDepth = 0;
    FUN_009032e0(t->mpParser, t);
    FUN_00903300(t->mpParser, (void*)&OnStartElement, (void*)&OnEndElement);
    FUN_00903320(t->mpParser, (void*)&OnCharacterData);
    FUN_00903340(t->mpParser, (void*)&OnComment);
    FUN_00903370(t->mpParser, (void*)&OnStartElement2, (void*)&FUN_00c2e4e0);
    FUN_00903330(t->mpParser, (void*)&OnPI);
    FUN_00903390(t->mpParser, (void*)&FUN_00c2e4e0, (void*)&FUN_00c2e4e0);
    return 1;
}

// @ 0x00901340
char XmlTextReader::Read()
{
    XmlTextReader* t = this;
    if (t->mbEndOfStream) {
        t->mResultCode = 1;
        return 0;
    }
    while (t->mpFirstToken == 0) {
        uint32 n = t->mpInputStream->Read(t->mpTokenBufferStart, 0x2000);
        t->mnTokenBufferBytes = n;
        if ((int)n < 0)
            goto readfail;
        if (n < 0x2000)
            t->mbEndOfStream = 1;
        if (!XML_Parse(t->mpParser, (const char*)t->mpTokenBufferStart, (int)n, t->mbEndOfStream))
            goto parsefail;
    }
    return 1;
parsefail:
    t->mResultCode = t->MapError(FUN_00903b40(t->mpParser));
    return 0;
readfail:
    t->mResultCode = 2;
    return 0;
}

// @ 0x00900410
int StylesheetFactory::CreateResource(Stylesheet** ppOut, uint32* pSize, ResourceRequest* req)
{
    StylesheetFactory* t = this;
    if (strcmp(req->mTypeStr.mpBegin, gMimeTextCss) != 0)
        return 3;
    Stylesheet* sheet = new ("StylesheetFactory/Stylesheet", 0, 0, 0, 0) Stylesheet(req->mpURL);
    if (sheet != 0)
        sheet->AddRef();
    EA::IO::IStream* stream = req->mpStream;
    *pSize = stream->GetSize();
    if (req->mEncodingSource > 1) {
        int enc = FUN_00900370(stream);
        if (enc != 0)
            req->SetEncoding(enc, 1);
    }
    uint32 size = stream->GetSize();
    if (req->mEncoding == 0x10) {
        t->mDataBuffer.resize(size >> 1);
        if (stream->Read(t->mDataBuffer.mpBegin, size) != size) {
            stream->Close();
            goto cleanup;
        }
    } else {
        t->mConvertBuffer.resize(size);
        if (stream->Read(t->mConvertBuffer.mpBegin, size) != size) {
            stream->Close();
            goto cleanup;
        }
        t->mDataBuffer.clear();
        EA::Text::ConvertEncoding(t->mConvertBuffer.mpBegin, size, req->mEncoding, &t->mDataBuffer);
    }
    {
        CSSParser parser;
        parser.Fn8f3970((void*)sheet->mAllocator, t->mDataBuffer.mpBegin,
                        (int)(t->mDataBuffer.mpEnd - t->mDataBuffer.mpBegin));
        parser.mpErrorListener = req->mpErrorListener;
        if (parser.Parse(sheet)) {
            sheet->AddRef();
            *ppOut = sheet;
            Fn8e2ed0(&parser);
            sheet->Release();
            return 0;
        }
        Fn8e2ed0(&parser);
    }
cleanup:
    if (sheet != 0)
        sheet->Release();
    return 1;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
