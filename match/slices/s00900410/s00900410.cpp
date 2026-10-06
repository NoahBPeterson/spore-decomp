// Slice s00900410 (bfs2 #21), 32-bit MSVC 2008.
// EA::XML::XmlReader / XmlTextReader (expat-based XML reader) + XHTML StylesheetFactory.
// Layouts taken from the 2008 dev PDB; the module is plain /O2 cl 15.00.
#include <new>

typedef unsigned int uint32;
typedef unsigned short uint16;

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
    void* Allocate(uint32 size) {
        if ((uint32)(mpCurrentObjectEnd - mpCurrentObjectBegin) < size) {
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
    int*   mpEntries;    // +0x14
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

class XmlReader {
public:
    void** vftable;                 // +0x00
    int    mResultCode;             // +0x04
    int    mAllocatorContextName;   // +0x08
    int    mAllocatorContextAlloc;  // +0x0c
    char   mAllocator[0x24];        // +0x10
    int    r34;                     // +0x34
    Token* mpFirstToken;            // +0x38
    Token* mpLastToken;             // +0x3c
    Token* mpCurrentToken;          // +0x40
    int    r44;                     // +0x44
    char   mMemoryStream[0x24];     // +0x48

    int  GetTokenType();
    int  GetTokenCount();
    int  GetEntryA(int idx);
    int  GetEntryB(int idx);
    int  IsAtEnd();
    void FUN_00900610(void* a1, void* a2, void* a3);
    int  FUN_00900720(const uint16* s);
    void FUN_009007b0();
    __declspec(noinline) int ReadString(int unused, uint32* pOut);
    void FUN_009008f0();

    XmlReader(void* pAllocator);
    ~XmlReader();
    void* DeletingDtor(char flags);
    int   InitAllocator(int* a2, void* a3);
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
    int  Read();
    void OnStartElement2(void* a2, void* a3, void* a4);
    void OnStartElement(void* a2, int* a3);
    void OnEndElement(void* a2);
    void OnCharacterData(void* a2, int a3);
    void OnComment(void* a2);
    void OnPI(void* a2, void* a3);

    XmlTextReader(void* pAllocator);
    ~XmlTextReader();
    XmlTextReader* DeletingDtor(char flags);
    char InitParser();
};

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
void FUN_00903b40(void* parser);
void* FUN_00900970(XmlReader* r, const void* v);            // 0x00900970
void FUN_00900900(short* s, EA::Allocator::StackAllocator* a); // 0x00900900
extern "C" void g_use_ptr(uint32*);

#define VFN0(p, off) (*(void (__thiscall**)(void*))((char*)(*(void**)(p)) + (off)))
#define VFN2(p, off) (*(void (__thiscall**)(void*, void*, void*))((char*)(*(void**)(p)) + (off)))
#define VFN1a(p, off) (*(void (__thiscall**)(void*, void*))((char*)(*(void**)(p)) + (off)))

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
}

// @ 0x00900800
__declspec(noinline) int XmlReader::ReadString(int unused, uint32* pOut)
{
    (void)unused;
    g_use_ptr(pOut);
    return 0;
}

// @ 0x009008f0
void XmlReader::FUN_009008f0()
{
    uint32 local;
    ReadString((int)((char*)this + 0x10), &local);
}

// @ 0x00900900
void FUN_00900900(short* s, EA::Allocator::StackAllocator* a)
{
    short* p = s;
    do { } while (*p++ != 0);
    uint32 n = ((uint32)((p - (s + 1)) * 2) + 9) & ~7u;
    char* dst;
    if ((int)((a->mpCurrentObjectEnd - a->mpCurrentObjectBegin) - n) < 0) {
        if (!a->AllocateNewBlock(n))
            return;
    }
    dst = a->mpCurrentObjectBegin;
    a->mpCurrentObjectBegin = dst + n;
    a->mpCurrentObjectEnd = dst + n;
    short* d = (short*)dst;
    while ((*d++ = *s++) != 0) { }
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
    t->r34 = 0;
    t->mpFirstToken = 0;
    t->mpLastToken = 0;
    t->mpCurrentToken = 0;
    t->r44 = 0;
    new (t->mMemoryStream) MemoryStream(0);
}

// @ 0x009009e0
XmlReader::~XmlReader()
{
    XmlReader* t = this;
    t->vftable = (void**)&g_vtblXmlReader;
    ((EA::Allocator::StackAllocator*)(t->mAllocator))->~StackAllocator();
    if (t->r34 != 0) {
        int* p = (int*)t->r34;
        t->r34 = 0;
        (*(void(__thiscall**)(int*))((char*)*p + 8))(p);
    }
    ((MemoryStream*)(t->mMemoryStream))->~MemoryStream();
    if (t->r34 != 0) {
        int* p = (int*)t->r34;
        (*(void(__thiscall**)(int*))((char*)*p + 8))(p);
    }
    ((EA::Allocator::StackAllocator*)(t->mAllocator))->~StackAllocator();
}

// @ 0x00900a30
int XmlReader::InitAllocator(int* a2, void* a3)
{
    XmlReader* t = this; (void)a2; (void)a3;
    return 1;
}

// @ 0x00900ab0
void* XmlReader::DeletingDtor(char flags)
{
    XmlReader* t = this;
    t->vftable = (void**)&g_vtblXmlReader;
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
void XmlTextReader::OnStartElement2(void* a2, void* a3, void* a4)
{
    XmlTextReader* t = this;
    if ((t->mnFlags & 8) == 0)
        return;
    Token* p = AllocToken(t, 0x20);
    if (p) {
        p->mToken = 6;
        p->field8 = (int)FUN_00900970(t, a2);
        p->fieldc = 0;
        p->field10 = 0;
        p->mpEntries = 0;
        p->mnEntryCount = (int)FUN_00900970(t, a3);
        p->mpNext = 0;
        p->field10 = t->mnDepth;
        AppendTok(t, p);
    }
}

// @ 0x00900e60
void XmlTextReader::OnStartElement(void* a2, int* a3)
{
    XmlTextReader* t = this;
    Token* p = AllocToken(t, 0x20);
    if (!p)
        return;
    p->mToken = 1;
    int n = 0;
    while (a3[n] != 0)
        n++;
    p->mnEntryCount = n / 2;
    p->field8 = (int)FUN_00900970(t, a2);
    p->fieldc = 0;
    int* arr = (int*)((EA::Allocator::StackAllocator*)(t->mAllocator))
                   ->Allocate((uint32)(n * 4 + 7) & ~7u);
    p->mpEntries = arr;
    for (int i = 0; i < n; i++)
        arr[i] = (int)FUN_00900970(t, (void*)a3[i]);
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
void XmlTextReader::OnEndElement(void* a2)
{
    XmlTextReader* t = this;
    Token* p = AllocToken(t, 0x18);
    if (!p)
        return;
    p->mToken = 2;
    p->field8 = (int)FUN_00900970(t, a2);
    p->fieldc = 0;
    t->mnDepth--;
    p->mpNext = 0;
    p->field10 = t->mnDepth;
    AppendTok(t, p);
}

// @ 0x00900ff0
void XmlTextReader::OnCharacterData(void* a2, int a3)
{
    XmlTextReader* t = this;
    Token* p = AllocToken(t, 0x18);
    if (!p)
        return;
    p->mToken = 4;
    p->field8 = 0;
    uint32 size = (uint32)(a3 * 2);
    uint32 n = (size + 9) & ~7u;
    char* dst = (char*)((EA::Allocator::StackAllocator*)(t->mAllocator))->Allocate(n);
    p->mpEntries = (int*)dst;
    // copy a3 wchar_t (a2 is the parser's buffer)
    short* d = (short*)dst;
    short* s = (short*)a2;
    for (int i = 0; i < a3; i++) d[i] = s[i];
    d[a3] = 0;
    p->field10 = a3;
    p->mpNext = 0;
    p->mnEntryCount = t->mnDepth;
    AppendTok(t, p);
}

// @ 0x009010c0
void XmlTextReader::OnComment(void* a2)
{
    XmlTextReader* t = this;
    if ((t->mnFlags & 1) == 0)
        return;
    Token* p = AllocToken(t, 0x18);
    if (!p)
        return;
    p->mToken = 3;
    p->field8 = 0;
    p->fieldc = (int)FUN_00900970(t, a2);
    p->mpNext = 0;
    p->field10 = t->mnDepth;
    AppendTok(t, p);
}

// @ 0x00901150
void XmlTextReader::OnPI(void* a2, void* a3)
{
    XmlTextReader* t = this;
    if ((t->mnFlags & 2) == 0)
        return;
    Token* p = AllocToken(t, 0x18);
    if (!p)
        return;
    p->mToken = 5;
    p->field8 = (int)FUN_00900970(t, a2);
    p->fieldc = (int)FUN_00900970(t, a3);
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
    t->mpParser = 0;
    return 0;
}

// @ 0x00901340
int XmlTextReader::Read()
{
    XmlTextReader* t = this;
    if (t->mbEndOfStream) {
        t->mResultCode = 1;
        return 0;
    }
    while (t->mpFirstToken == 0) {
        void* p = t->mpParser;
        (void)p;
        break;
    }
    return 1;
}

// @ 0x00900410
int CreateResource(void* self, int a2, int* a3, void* req)
{
    (void)self; (void)a2; (void)a3; (void)req;
    return 3;
}
