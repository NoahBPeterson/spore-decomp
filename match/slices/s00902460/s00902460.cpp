// Slice s00902460 (bfs4 #15), 32-bit MSVC 2008.
// EA::XML TokenIOContext + Token reader/writer helpers (token streams).
// Class layouts taken from the 2008 dev-build PDB.
#include "types.h"
#include <new>
#include <intrin.h>

typedef unsigned int size_t;
extern "C" size_t wcslen(const wchar_t*);
#pragma intrinsic(wcslen)

// ---------------------------------------------------------------------------
// forward types
// ---------------------------------------------------------------------------
namespace EA { namespace XML { struct TokenNode; struct TokenIOContext; } }

// Generic byte stream (EA::IO::IStream). Only the vtable slots actually called
// by this slice are declared; the gaps are placeholder virtuals so each slot
// lands at the original offset.
struct IStream {
    virtual void v00() {}
    virtual void v01() {}
    virtual void v02() {}
    virtual void v03() {}
    virtual void v04() {}
    virtual int  v05() { return 0; }                       // +0x14
    virtual void v06() {}
    virtual void v07() {}
    virtual void v08() {}
    virtual int  v09(int a) { return a; }                  // +0x24
    virtual void v10(int a, int b) { (void)a; (void)b; }   // +0x28
    virtual void v11() {}
    virtual int  v12(char* buf, int n) { (void)buf; (void)n; return 0; } // +0x30
    virtual void v13() {}
    virtual int  v14(const void* buf, int n) { (void)buf; (void)n; return 0; } // +0x38
};

// ---------------------------------------------------------------------------
// EA::Allocator
// ---------------------------------------------------------------------------
namespace EA { namespace Allocator {
struct ICoreAllocator;

struct ContextCoreAllocator {
    const char* mpName;          // +0x0
    ICoreAllocator* mpAllocator; // +0x4
};

struct StackAllocator {
    unsigned   mnDefaultBlockSize;    // +0x0
    void*      mpCurrentBlock;        // +0x4
    char*      mpCurrentBlockEnd;     // +0x8
    char*      mpCurrentObjectBegin;  // +0xc
    char*      mpCurrentObjectEnd;    // +0x10
    void*      mpCoreAllocationFunction; // +0x14
    void*      mpCoreFreeFunction;    // +0x18
    void*      mpCoreFunctionContext; // +0x1c
    void*      mpTopBookmark;         // +0x20

    void  Init(unsigned defBlockSize, void* a, void* b, void* c, void* d);
    void  Reset();
    bool  AllocateNewBlock(unsigned n);
    StackAllocator() {}
    StackAllocator(unsigned, unsigned, unsigned, unsigned, unsigned);

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

// ---------------------------------------------------------------------------
// IO helpers (all __cdecl; callees are relocations, so names are irrelevant)
// ---------------------------------------------------------------------------
extern "C" {
int   io_ReadInt32 (IStream* s, void* dst, int count, int flags);   // 0x93a780
int   io_ReadUint16(IStream* s, void* dst, int count, int flags);   // 0x93a700
bool  io_ReadUInt64(IStream* s, void* dst, int count, int flags);   // 0x93a800
int   io_ReadBool  (IStream* s, void* dst);                          // 0x93ac80
int   io_ReadBytes (IStream* s, void* dst, int count);               // 0x93a6c0
int   io_WriteUint32(IStream* s, const void* src, int count, int flags); // 0x93aa70
int   io_WriteUint16(IStream* s, const void* src, int count, int flags); // 0x93a9d0
int   io_WriteUInt64(IStream* s, const void* src, int count, int flags); // 0x93ab10
int   io_WriteBytes(IStream* s, const void* src, int count);         // 0x93a9a0
}

void  EA_operator_delete(void* p);                                   // 0xf47380
void* EA_GetDefaultAllocator();                                      // 0x925cb0

// EA::XML anonymous-namespace helpers
namespace EA { namespace XML {
wchar_t* sStrDup(const wchar_t* s, void* allocCtx);                  // 0x902380
bool     WriteString(IStream* s, const wchar_t* str, TokenIOContext* ctx); // 0x902640

}}

// ---------------------------------------------------------------------------
// eastl::fixed_string<wchar_t, 256>: begin/end/capacity, an (empty) allocator slot, the pool
// begin pointer and the inline buffer.
// ---------------------------------------------------------------------------
struct FixedWStr256 {
    wchar_t* mpBegin;       // +0x0
    wchar_t* mpEnd;         // +0x4
    wchar_t* mpCapacity;    // +0x8
    int      mAllocator;    // +0xc (unused slot)
    wchar_t* mpPoolBegin;   // +0x10
    wchar_t  mBuf[256];     // +0x14

    FixedWStr256()
    {
        mpBegin = mBuf;
        mpPoolBegin = mBuf;
        mpEnd = mBuf;
        mpCapacity = mBuf + 256;
        mBuf[0] = 0;
    }
    ~FixedWStr256()
    {
        if ((((int)mpCapacity - (int)mpBegin) & ~1) > 2 && mpBegin != 0 && mpBegin != mpPoolBegin) {
            EA_operator_delete(mpBegin);
        }
    }
    void Append(const wchar_t* first, const wchar_t* last);          // 0x42f9d0
    void Reset(int n);                                               // 0x4c1c80
};

// ---------------------------------------------------------------------------
// Token node
// ---------------------------------------------------------------------------
namespace EA { namespace XML {
struct TokenNode {
    TokenNode* mpNext;        // +0x0
    int        mToken;        // +0x4 (XmlNodeType)
    wchar_t*   msName;        // +0x8
    wchar_t*   msValue;       // +0xc
    int        mnDepth;       // +0x10
    union {                   // +0x14
        wchar_t** mpAttrs;    //   type 1: attribute string array
        int       mnValue;    //   type 4
        wchar_t*  msData;     //   type 6
        void*     mpChildren;
    };
    union {                   // +0x18
        int       mnCount;    //   type 1: attribute count
        wchar_t*  msExtra;    //   type 6
        void*     mpExtra;
    };
    TokenNode(int token) : mToken(token) {}
};
}}

// ---------------------------------------------------------------------------
// hashtable (eastl::hashtable<...>) — only the fields this slice touches
// ---------------------------------------------------------------------------
struct Hashtable {
    void*    mpAlloc;          // +0x0
    void*    mpBucket;         // +0x4
    uint32_t mnBucketCount;    // +0x8
    uint32_t mnElementCount;   // +0xc
    float    mfMaxLoadFactor;  // +0x10
    float    mfGrowthFactor;   // +0x14
    void*    mpUnknown18;      // +0x18
    void*    mpUnknown1c;      // +0x1c

    static int g_emptyBucket;

    void DoAllocateBuckets(void* bucket, unsigned count);            // 0x693230
    void InitEmpty() {
        mpBucket        = &g_emptyBucket;
        mnBucketCount   = 1;
        mnElementCount  = 0;
        mfMaxLoadFactor = 1.0f;
        mfGrowthFactor  = 2.0f;
        mpUnknown18     = 0;
    }
};
int Hashtable::g_emptyBucket;

// eastl::hashtable instances used by the token string tables.
struct StrIdPair { const wchar_t* first; int second; };   // table A: string pointer -> id
struct IdStrPair { int first; const wchar_t* second; };   // table B: id -> string pointer
struct HIter {
    void*  mpNode;
    void** mpBucket;
    HIter() {}
    HIter(const HIter& o) : mpNode(o.mpNode), mpBucket(o.mpBucket) {}
};
struct InsertRet { HIter it; bool inserted; };
struct InsertTag {};                                      // empty tag (no user ctor)
struct HashA : Hashtable {
    HIter     find(const wchar_t* const& key);                         // 0x9020b0
    InsertRet DoInsertValue(const StrIdPair& v, InsertTag t);          // 0x902140
};
struct HashB : Hashtable {
    HIter     find(const unsigned& key);                               // 0x645ed0
    InsertRet DoInsertValue(const IdStrPair& v, InsertTag t);          // 0x902290
};

// ---------------------------------------------------------------------------
// TokenIOContext
// ---------------------------------------------------------------------------
namespace EA { namespace XML {
struct TokenIOContext {
    EA::Allocator::ContextCoreAllocator mAllocatorContext; // +0x0
    EA::Allocator::StackAllocator       mAllocator;        // +0x8
    HashA*     mStringsA;                                  // +0x2c
    HashB*     mStringsB;                                  // +0x30
    int        mNextStringID;                              // +0x34

    TokenIOContext(EA::Allocator::ICoreAllocator* alloc);
    ~TokenIOContext();

    unsigned AddString(const wchar_t* str, unsigned id);
    int      GetString(const wchar_t* str);                // 0x902250
    void     ClearStrings();
    void     Reset();
};
}}

// ---------------------------------------------------------------------------
// implementation
// ---------------------------------------------------------------------------
namespace EA { namespace XML {

// @ 0x00902460
void TokenIOContext::ClearStrings()
{
    Hashtable* h = mStringsA;
    if (h != 0) {
        h->DoAllocateBuckets(h->mpBucket, h->mnBucketCount);
        h->mnElementCount = 0;
        if (h->mnBucketCount > 1)
            EA_operator_delete(h->mpBucket);
    }
    {
        Hashtable* n = (Hashtable*)mAllocator.Allocate(0x20);
        if (n) n->InitEmpty();
        mStringsA = (HashA*)n;
    }

    h = mStringsB;
    if (h != 0) {
        h->DoAllocateBuckets(h->mpBucket, h->mnBucketCount);
        h->mnElementCount = 0;
        if (h->mnBucketCount > 1)
            EA_operator_delete(h->mpBucket);
    }
    {
        Hashtable* n = (Hashtable*)mAllocator.Allocate(0x20);
        if (n) n->InitEmpty();
        mStringsB = (HashB*)n;
    }
}

// @ 0x00902590
unsigned TokenIOContext::AddString(const wchar_t* str, unsigned id)
{
    if ((int)id < 1) {
        id = (unsigned)mNextStringID;
        mNextStringID = (int)id + 1;
    } else if (mNextStringID <= (int)id) {
        mNextStringID = (int)id + 1;
    }
    const wchar_t* dup = sStrDup(str, this);
    HashA* a = mStringsA;
    a->find(dup);
    StrIdPair p1;
    p1.first = dup;
    p1.second = (int)id;
    a->DoInsertValue(p1, InsertTag());
    IdStrPair p2;
    p2.first = (int)id;
    p2.second = dup;
    mStringsB->DoInsertValue(p2, InsertTag());
    return id;
}

// @ 0x00902640
bool WriteString(IStream* pStream, const wchar_t* s, TokenIOContext* ctx)
{
    int len;
    unsigned found;
    void* pv;
    if (s == 0) {
        len = 0;
        pv = &len;
    } else {
        len = (int)wcslen(s);
        if (len <= 0) {
            pv = &len;
        } else {
            found = (unsigned)ctx->GetString(s);
            if (found != 0) {
                found |= 0x80000000u;
                pv = &found;
            } else {
                io_WriteUint32(pStream, &len, 1, 0);
                unsigned id = ctx->AddString(s, 0);
                io_WriteUint32(pStream, &id, 1, 0);

                bool wide = false;
                for (const wchar_t* q = s; *q != 0; ++q) {
                    wide = (*q > 0xff);
                    if (wide) break;
                }
                unsigned char wb = wide;
                io_WriteBytes(pStream, &wb, 1);
                if (wide) {
                    pStream->v14(s, len * 2);
                } else {
                    const wchar_t* q = s;
                    int bufs[8];   // int array: the original has no /GS cookie for it
                    char* buf = (char*)bufs;
                    while (len > 0) {
                        int n = len > 0x20 ? 0x20 : len;
                        for (int i = 0; i < n; ++i) {
                            buf[i] = (char)*q;
                            q++;
                        }
                        pStream->v14(buf, n);
                        len -= n;
                    }
                }
                goto done;
            }
        }
    }
    io_WriteUint32(pStream, pv, 1, 0);
done:
    return pStream->v05() == 0;
}

// @ 0x009027b0
bool ReadString(IStream* pStream, FixedWStr256* out, TokenIOContext* ctx)
{
    out->Reset(0);
    unsigned remaining = 0;
    io_ReadInt32(pStream, &remaining, 1, 0);
    if ((int)remaining < 0) {
        HashB* t = ctx->mStringsB;
        unsigned key = remaining & 0x7fffffff;
        HIter it = t->find(key);
        const wchar_t* str;
        if (it.mpNode != ((void**)t->mpBucket)[t->mnBucketCount]) {
            str = ((IdStrPair*)it.mpNode)->second;
        } else {
            str = 0;
        }
        const wchar_t* e = str;
        while (*e != 0) {
            ++e;
        }
        out->Append(str, str + (e - str));
    } else if ((int)remaining > 0) {
        unsigned id = 0;
        io_ReadInt32(pStream, &id, 1, 0);
        char isWide = 0;
        io_ReadBool(pStream, &isWide);
        unsigned lim = 0x20;
        unsigned unit = (isWide != 0) + 1;
        wchar_t wb[32];
        while ((int)remaining > 0) {
            const unsigned* np = &lim;
            if ((int)remaining <= 0x20) {
                np = &remaining;
            }
            unsigned got = (unsigned)pStream->v12((char*)wb, (int)(*np * unit));
            if (got == 0xffffffffu) {
                return false;
            }
            got = got / unit;
            remaining -= got;
            if (isWide == 0) {
                wchar_t* d = wb + got;
                const char* sp = (const char*)wb + got;
                if (wb < d) {
                    do {
                        char c = sp[-1];
                        --sp;
                        --d;
                        *d = (wchar_t)(short)c;
                    } while (wb < d);
                }
            }
            out->Append(wb, wb + got);
        }
        ctx->AddString(out->mpBegin, id);
    }
    return pStream->v05() == 0;
}

// @ 0x00902950
bool ReadToken(IStream* pStream, TokenNode** ppOut, TokenIOContext* ctx)
{
    EA::Allocator::StackAllocator* A = &ctx->mAllocator;
    unsigned char type = 0;
    io_ReadBytes(pStream, &type, 1);
    if (type == 0) {
        return false;
    }
    TokenNode* n;
    switch (type) {
    case 1:
    case 6:
        n = new (A->Allocate(0x20)) TokenNode(type);
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        n = new (A->Allocate(0x18)) TokenNode(type);
        break;
    case 0:
    default:
        return false;
    }

    FixedWStr256 str;
    ReadString(pStream, &str, ctx);
    n->msName = sStrDup(str.mpBegin, ctx);
    ReadString(pStream, &str, ctx);
    n->msValue = sStrDup(str.mpBegin, ctx);
    io_ReadInt32(pStream, &n->mnDepth, 1, 0);

    switch (n->mToken) {
    case 0:
    case 2:
    case 3:
    case 5:
        break;
    case 1: {
        io_ReadInt32(pStream, &n->mnCount, 1, 0);
        int cnt = n->mnCount;
        n->mpAttrs = (wchar_t**)A->Allocate((unsigned)(cnt * 2 * 4));
        for (int i = 0; i < cnt * 2; ++i) {
            ReadString(pStream, &str, ctx);
            n->mpAttrs[i] = sStrDup(str.mpBegin, ctx);
        }
        break;
    }
    case 4:
        io_ReadInt32(pStream, &n->mnValue, 1, 0);
        break;
    case 6:
        ReadString(pStream, &str, ctx);
        n->msData = sStrDup(str.mpBegin, ctx);
        ReadString(pStream, &str, ctx);
        n->msExtra = sStrDup(str.mpBegin, ctx);
        break;
    default:
        return false;
    }
    n->mpNext = 0;
    if (ppOut) {
        *ppOut = n;
    }
    return pStream->v05() == 0;
}

// @ 0x00902C20
int WriteToken(IStream* pStream, TokenNode* p, TokenIOContext* ctx)
{
    unsigned char type = (unsigned char)p->mToken;
    io_WriteBytes(pStream, &type, 1);
    WriteString(pStream, p->msName, ctx);
    WriteString(pStream, p->msValue, ctx);
    io_WriteUint32(pStream, &p->mnDepth, 1, 0);
    switch (p->mToken) {
    case 1: {
        io_WriteUint32(pStream, (char*)p + 0x18, 1, 0);
        int n = *(int*)((char*)p + 0x18) * 2;
        for (int i = 0; i < n; ++i)
            WriteString(pStream, ((wchar_t**)p->mpChildren)[i], ctx);
        break;
    }
    case 4:
        io_WriteUint32(pStream, &p->mpChildren, 1, 0);
        break;
    case 6:
        WriteString(pStream, (wchar_t*)p->mpChildren, ctx);
        WriteString(pStream, (wchar_t*)p->mpExtra, ctx);
        break;
    default:
        break;
    }
    pStream->v05();
    return 0;
}

// EA::IO::MemoryStream and EA::XML::XmlTextReader (external; only the members this slice calls)
struct MemoryStream : IStream {
    unsigned mData[8];
    MemoryStream(void* data, unsigned size, int a, int b, int c, const char* name);   // 0x93c2c0
    ~MemoryStream();                                                                  // 0x93bde0
    void SetResize(int enable, float factor);                                         // 0x93bb40
    void SetPosition(int a, int b);                                                   // 0x93c0c0
};
struct XmlTextReader {
    unsigned mData[0x22];
    XmlTextReader(EA::Allocator::ICoreAllocator* alloc);                              // 0x900b30
    ~XmlTextReader();                                                                 // 0x900b70
    bool Begin(IStream* s, int flags);                                                // 0x901440
    bool Next();                                                                      // 0x9013e0
    TokenNode* GetToken();                                                            // 0xa1ad60
};
bool IsBlank(const wchar_t* s);                                                       // 0x901e60

// @ 0x00902D40
bool ReadTokenList(IStream* pStream, TokenNode** ppOut, unsigned flags, TokenIOContext* ctx)
{
    int pos = pStream->v09(0);
    unsigned hdr1 = 0xffff;
    io_ReadUint16(pStream, &hdr1, 1, 0);
    unsigned hdr2 = 0;
    io_ReadUint16(pStream, &hdr2, 1, 0);
    unsigned hdr3;
    io_ReadUint16(pStream, &hdr3, 1, 0);
    TokenNode* head = 0;
    TokenNode* tail = 0;
    TokenNode* cur = 0;

    if ((unsigned short)hdr1 == 0) {
        if ((unsigned short)hdr2 == 0x5444) {
            while (ReadToken(pStream, &cur, ctx)) {
                if (head == 0) {
                    head = cur;
                    tail = cur;
                } else {
                    tail->mpNext = cur;
                    tail = cur;
                }
            }
            goto out;
        }
        if ((unsigned short)hdr2 == 0x5450) {
            unsigned __int64 v = 0;
            if (!io_ReadUInt64(pStream, &v, 1, 0)) {
                return false;
            }
            head = (TokenNode*)(unsigned)v;
            goto out;
        }
    }

    // text XML fallback: parse with XmlTextReader and round-trip every token through a MemoryStream
    pStream->v10(pos, 0);
    {
        XmlTextReader tr((EA::Allocator::ICoreAllocator*)0);
        if (!tr.Begin(pStream, 0)) {
            return false;
        }
        char data[0x80];
        MemoryStream ms(data, 0x80, 1, 0, 0, "XML/TokenReader");
        ms.SetResize(1, 1.0f);
        while (tr.Next()) {
            TokenNode* t = tr.GetToken();
            if ((flags & 8) && t->mToken == 4 && IsBlank(t->msName) && IsBlank(t->msValue)) {
                continue;
            }
            ms.SetPosition(0, 0);
            WriteToken(&ms, t, ctx);
            ms.SetPosition(0, 0);
            ReadToken(&ms, &cur, ctx);
            if (head == 0) {
                head = cur;
                tail = cur;
            } else {
                tail->mpNext = cur;
                tail = cur;
            }
        }
    }

out:
    if (ppOut) {
        *ppOut = head;
    }
    return pStream->v05() == 0;
}

// @ 0x00902FC0
extern const unsigned short g_tokenListVersion;                                       // 0x143a2bc (== 1)
bool WriteTokenList(IStream* pStream, TokenNode* p, unsigned flags, TokenIOContext* ctx)
{
    unsigned zero = 0;
    unsigned marker = 0x5444;
    if (flags & 2) marker = 0x5450;
    io_WriteUint16(pStream, &zero, 1, 0);
    io_WriteUint16(pStream, &marker, 1, 0);
    io_WriteUint16(pStream, &g_tokenListVersion, 1, 0);

    if ((unsigned short)marker == 0x5444) {
        while (p) {
            if (!((flags & 4) && p->mToken == 4 && IsBlank(p->msName) && IsBlank(p->msValue))) {
                WriteToken(pStream, p, ctx);
            }
            p = p->mpNext;
        }
    } else if ((unsigned short)marker == 0x5450) {
        unsigned long long v = (unsigned long long)(size_t)p;
        io_WriteUInt64(pStream, &v, 1, 0);
    }
    return pStream->v05() == 0;
}

// @ 0x009030B0
TokenIOContext::TokenIOContext(EA::Allocator::ICoreAllocator* alloc)
{
    mAllocatorContext.mpName = "UTF/XmlTokenReader/TokenIOContext/mAllocator";
    if (alloc == 0)
        alloc = (EA::Allocator::ICoreAllocator*)EA_GetDefaultAllocator();
    mAllocatorContext.mpAllocator = alloc;
    new (&mAllocator) EA::Allocator::StackAllocator(0, 0, 0xffffffffu, 0, 0);
    mNextStringID = 1;
    mStringsA = 0;
    mStringsB = 0;
    mAllocator.mnDefaultBlockSize = 0x800;
    mAllocator.Init(0, 0, 0, 0, 0);
    ClearStrings();
}

inline void ClearHashtable(Hashtable* h)
{
    if (h != 0) {
        h->DoAllocateBuckets(h->mpBucket, h->mnBucketCount);
        h->mnElementCount = 0;
        if (h->mnBucketCount > 1)
            EA_operator_delete(h->mpBucket);
    }
}

// @ 0x00903120
TokenIOContext::~TokenIOContext()
{
    ClearHashtable(mStringsA);
    mStringsA = 0;
    _ReadWriteBarrier();
    ClearHashtable(mStringsB);
    mStringsB = 0;
    mAllocator.Reset();
    mAllocator.Reset();
}

// ---------------------------------------------------------------------------
// XmlReader / XmlTokenReader
// ---------------------------------------------------------------------------
struct XmlReader {
    virtual void vf0() {}
    virtual void vf1() {}
    char pad[0x68];                                   // +0x4 .. +0x6c
    XmlReader(EA::Allocator::ICoreAllocator* alloc);
    ~XmlReader();
    bool BeginRead(const void* a, const void* b);      // 0x900a30
    bool BeginRead2(const void* a, const void* b, const void* c); // 0x900610
};

struct XmlTokenReader : XmlReader {
    TokenIOContext mCtx;                              // +0x6c

    XmlTokenReader(EA::Allocator::ICoreAllocator* alloc);
    ~XmlTokenReader();

    bool Read(const wchar_t* a, const wchar_t* b);     // @ 0x9031f0
    bool Read2(const wchar_t* a, const wchar_t* b, const wchar_t* c); // @ 0x903230
};

// @ 0x009031A0
XmlTokenReader::XmlTokenReader(EA::Allocator::ICoreAllocator* alloc)
    : XmlReader(alloc), mCtx(alloc)
{
}

// @ 0x009031D0
XmlTokenReader::~XmlTokenReader()
{
}

// @ 0x009031F0
bool XmlTokenReader::Read(const wchar_t* a, const wchar_t* b)
{
    if (BeginRead(a, b)) {
        IStream* stream = *(IStream**)((char*)this + 0x34);
        *(int*)((char*)this + 0x40) = 0;
        *(int*)((char*)this + 0x3c) = 0;
        return ReadTokenList(stream, (TokenNode**)((char*)this + 0x38), 0, &mCtx);
    }
    return false;
}

// @ 0x00903230
bool XmlTokenReader::Read2(const wchar_t* a, const wchar_t* b, const wchar_t* c)
{
    if (BeginRead2(a, b, c)) {
        IStream* stream = *(IStream**)((char*)this + 0x34);
        *(int*)((char*)this + 0x40) = 0;
        *(int*)((char*)this + 0x3c) = 0;
        return ReadTokenList(stream, (TokenNode**)((char*)this + 0x38), 0, &mCtx);
    }
    return false;
}

}} // namespace EA::XML

// @ 0x009032B0  (static helper with register args: free a singly linked list through an owner callback)
struct ListNode {
    int pad0;
    ListNode* next;      // +4
    int pad8;
    int padc;
    void* data;          // +0x10
};
struct FreeOwner {
    char pad[0x14];
    void (__cdecl *mpFree)(void*);   // +0x14
};
static void FreeNodeList(ListNode* n, FreeOwner* o)
{
    while (n != 0) {
        ListNode* nx = n->next;
        o->mpFree(n->data);
        o->mpFree(n);
        n = nx;
    }
}
// Stand-in for the original caller (0x905676..), so cl keeps the register convention of the static helper.
struct ListOwner : FreeOwner {
    char pad2[0x160];
    ListNode* mpList2;   // +0x174
    ListNode* mpList1;   // +0x178
};
void FreeBothLists(ListOwner* o, void* extra)
{
    FreeNodeList(o->mpList1, o);
    FreeNodeList(o->mpList2, o);
    o->mpFree(extra);
    o->mpFree(o->mpList1);
}

// ---------------------------------------------------------------------------
// small accessors (free functions, __cdecl)
// ---------------------------------------------------------------------------
// @ 0x009032E0
void FUN_009032e0(int* p, int v)
{
    if (p[1] == p[0]) { p[0] = v; p[1] = v; }
    else p[0] = v;
}

// @ 0x00903300
void FUN_00903300(char* p, int a, int b)
{
    *(int*)(p + 0x34) = a;
    *(int*)(p + 0x38) = b;
}

// @ 0x00903320
void FUN_00903320(char* p, int v)
{
    *(int*)(p + 0x3c) = v;
}

// @ 0x00903330
void FUN_00903330(char* p, int v)
{
    *(int*)(p + 0x40) = v;
}

// @ 0x00903340
void FUN_00903340(char* p, int v)
{
    *(int*)(p + 0x44) = v;
}

// @ 0x00903350
void FUN_00903350(char* p, int v)
{
    *(int*)(p + 0x50) = v;
    *(char*)(p + 0x134) = 1;
}

// @ 0x00903370
void FUN_00903370(char* p, int a, int b)
{
    *(int*)(p + 0x54) = a;
    *(int*)(p + 0x58) = b;
}

// @ 0x009033D0
int FUN_009033d0(char* p, int v)
{
    int t = *(int*)(p + 0x1e0);
    if (t == 1 || t == 3)
        return 0;
    *(int*)(p + 0x1ec) = v;
    return 1;
}
