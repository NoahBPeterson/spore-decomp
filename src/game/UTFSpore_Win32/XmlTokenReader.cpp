// src/game/UTFSpore_Win32/XmlTokenReader.cpp -- migrated from slice(s) s00902460, s009013e0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/XmlTokenReader.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Allocator/StackAllocator.h"
#include "EA/XML/TokenIOContext.h"
#include "EA/XML/XmlTextWriter.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl EA_operator_new(unsigned int nSize, const char* pName, int a,
                                         int b, const char* pFile, int nLine); // 0xf473a0
extern "C" unsigned int __cdecl FNV1_String16(const wchar_t* pStr, unsigned int a,
                                              unsigned int b);                 // 0x932f30
extern "C" __declspec(dllimport) int __cdecl iswctype(unsigned int c, int type);
#include <new>
#include <stdarg.h>
#include "EA/Allocator/ContextCoreAllocator.h"
#include "EA/IO/IStream.h"
#include "EA/IO/MemoryStream.h"
#include <intrin.h>
#pragma intrinsic(wcslen)

// ---- items of slice s009013e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uint32;
extern "C" size_t wcslen(const wchar_t*);
extern "C" void* __cdecl EA_operator_new(unsigned int nSize, const char* pName, int a,
                                         int b, const char* pFile, int nLine); // 0xf473a0
extern "C" unsigned int __cdecl FNV1_String16(const wchar_t* pStr, unsigned int a,
                                              unsigned int b);                 // 0x932f30
extern "C" __declspec(dllimport) int __cdecl iswctype(unsigned int c, int type);
bool __cdecl FUN_00901e60(const wchar_t* s);   // 0x901e60
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
namespace EA {
namespace Allocator {
struct StackAllocator_s0090_13e0 {
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
}
}
namespace EA {
namespace XML {
struct TokenIOContext_s0090_13e0 {
    char _allocCtx[0x8];
    EA::Allocator::StackAllocator_s0090_13e0 mAllocator;  // +0x08
    HashA* mStringsA;    // +0x2c
    HashB* mStringsB;    // +0x30
    int    mNextStringID;

    int GetString(const wchar_t* str);   // 0x902250
};
}
}
namespace EA {
namespace XML {
wchar_t* sStrDup(const wchar_t* str, TokenIOContext_s0090_13e0* ctx);   // 0x902380
}
}
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
// ---- items of slice s009013e0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" size_t wcslen(const wchar_t*);

// ---- items of slice s00902460 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace XML {
 struct TokenNode; struct TokenIOContext_s0090_2460; 
}
}
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
namespace EA {
namespace Allocator {
struct ICoreAllocator_s0090_2460;
}
}
namespace EA {
namespace Allocator {
struct ContextCoreAllocator_s0090_2460 {
    const char* mpName;          // +0x0
    ICoreAllocator_s0090_2460* mpAllocator; // +0x4
    ContextCoreAllocator_s0090_2460() {}
    ContextCoreAllocator_s0090_2460(const char* name, ICoreAllocator_s0090_2460* a);
};
}
}
namespace EA {
namespace Allocator {
struct StackAllocator_s0090_2460 {
    unsigned   mnDefaultBlockSize;    // +0x0
    void*      mpCurrentBlock;        // +0x4
    char*      mpCurrentBlockEnd;     // +0x8
    char*      mpCurrentObjectBegin;  // +0xc
    char*      mpCurrentObjectEnd;    // +0x10
    void*      mpCoreAllocationFunction; // +0x14
    void*      mpCoreFreeFunction;    // +0x18
    void*      mpCoreFunctionContext; // +0x1c
    void*      mpTopBookmark;         // +0x20

    void  Init(unsigned defBlockSize, void* a, void* b, void* c, void* d);  // 0x00928b00 (EA::Allocator::StackAllocator::Init)
    void  Reset();
    bool  AllocateNewBlock(unsigned n);   // 0x928ba0
    StackAllocator_s0090_2460() {}
    StackAllocator_s0090_2460(unsigned, unsigned, unsigned, unsigned, unsigned);

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
}
}
extern "C" int   io_ReadInt32 (IStream* s, void* dst, int count, int flags);   // 0x93a780
extern "C" int   io_ReadUint16(IStream* s, void* dst, int count, int flags);   // 0x93a700
extern "C" bool  io_ReadUInt64(IStream* s, void* dst, int count, int flags);   // 0x93a800
extern "C" int   io_ReadBool  (IStream* s, void* dst);                          // 0x93ac80
extern "C" int   io_ReadBytes (IStream* s, void* dst, int count);               // 0x93a6c0
extern "C" int   io_WriteUint32(IStream* s, const void* src, int count, int flags); // 0x93aa70
extern "C" int   io_WriteUint16(IStream* s, const void* src, int count, int flags); // 0x93a9d0
extern "C" int   io_WriteUInt64(IStream* s, const void* src, int count, int flags); // 0x93ab10
extern "C" int   io_WriteBytes(IStream* s, const void* src, int count);         // 0x93a9a0
void  EA_operator_delete(void* p);                                   // 0xf47380
void* EA_GetDefaultAllocator();                                      // 0x925cb0
void  FUN_00925bf0();   // StackAllocator core alloc callback
void  FUN_00925c20();   // StackAllocator core free callback
inline EA::Allocator::ContextCoreAllocator_s0090_2460::ContextCoreAllocator_s0090_2460(const char* name, ICoreAllocator_s0090_2460* a)
{
    mpName = name;
    if (a == 0)
        a = (ICoreAllocator_s0090_2460*)EA_GetDefaultAllocator();
    mpAllocator = a;
}
namespace EA {
namespace XML {
wchar_t* sStrDup(const wchar_t* s, void* allocCtx);                  // 0x902380
}
}
namespace EA {
namespace XML {
bool     WriteString(IStream* s, const wchar_t* str, TokenIOContext_s0090_2460* ctx); // 0x902640
}
}
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
namespace EA {
namespace XML {
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
}
}
struct Hashtable_s0090_2460 {
    void*    mpAlloc;          // +0x0
    void*    mpBucket;         // +0x4
    uint32_t mnBucketCount;    // +0x8
    uint32_t mnElementCount;   // +0xc
    float    mfMaxLoadFactor;  // +0x10
    float    mfGrowthFactor;   // +0x14
    void*    mpUnknown18;      // +0x18
    void*    mpUnknown1c;      // +0x1c

    static int g_emptyBucket;   // 0x154df28

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
int Hashtable_s0090_2460::g_emptyBucket;
struct HIter_s0090_2460 {
    void*  mpNode;
    void** mpBucket;
    HIter_s0090_2460() {}
    HIter_s0090_2460(const HIter_s0090_2460& o) : mpNode(o.mpNode), mpBucket(o.mpBucket) {}
};
struct InsertRet_s0090_2460 { HIter_s0090_2460 it; bool inserted; };
struct InsertTag {};                                      // empty tag (no user ctor)
struct HashA_s0090_2460 : Hashtable_s0090_2460 {
    HIter_s0090_2460     find(const wchar_t* const& key);                         // 0x9020b0
    InsertRet_s0090_2460 DoInsertValue(const StrIdPair& v, InsertTag t);          // 0x902140
};
struct HashB_s0090_2460 : Hashtable_s0090_2460 {
    HIter_s0090_2460     find(const unsigned& key);                               // 0x645ed0
    InsertRet_s0090_2460 DoInsertValue(const IdStrPair& v, InsertTag t);          // 0x902290
};
namespace EA {
namespace XML {
struct TokenIOContext_s0090_2460 {
    EA::Allocator::ContextCoreAllocator_s0090_2460 mAllocatorContext; // +0x0
    EA::Allocator::StackAllocator_s0090_2460       mAllocator;        // +0x8
    HashA_s0090_2460*     mStringsA;                                  // +0x2c
    HashB_s0090_2460*     mStringsB;                                  // +0x30
    int        mNextStringID;                              // +0x34

    TokenIOContext_s0090_2460(EA::Allocator::ICoreAllocator_s0090_2460* alloc);
    ~TokenIOContext_s0090_2460();

    unsigned AddString(const wchar_t* str, unsigned id);
    int      GetString(const wchar_t* str);                // 0x902250
    void     ClearStrings();  // 0x00902460 (EA::XML::TokenIOContext::ClearStrings)
    void     Reset();
};
}
}
namespace EA {
namespace XML {
struct MemoryStream : IStream {
    unsigned mData[8];
    MemoryStream(void* data, unsigned size, int a, int b, int c, const char* name);   // 0x93c2c0
    ~MemoryStream();                                                                  // 0x93bde0
    void SetResize(int enable, float factor);                                         // 0x93bb40
    void SetPosition(int a, int b);                                                   // 0x93c0c0
};
}
}
namespace EA {
namespace XML {
struct XmlTextReader {
    unsigned mData[0x22];
    XmlTextReader(EA::Allocator::ICoreAllocator_s0090_2460* alloc);                              // 0x900b30
    ~XmlTextReader();                                                                 // 0x900b70
    bool Begin(IStream* s, int flags);                                                // 0x901440
    bool Next();                                                                      // 0x9013e0
    TokenNode* GetToken();                                                            // 0xa1ad60
};
}
}
namespace EA {
namespace XML {
bool IsBlank(const wchar_t* s);                                                       // 0x901e60
}
}
namespace EA {
namespace XML {
extern const unsigned short g_tokenListVersion;                                       // 0x143a2bc (== 1)
}
}
namespace EA {
namespace XML {
struct XmlReader {
    virtual void vf0() {}
    virtual void vf1() {}
    char pad[0x68];                                   // +0x4 .. +0x6c
    XmlReader(EA::Allocator::ICoreAllocator_s0090_2460* alloc);
    ~XmlReader();
    bool BeginRead(const void* a, const void* b);      // 0x900a30
    bool BeginRead2(const void* a, const void* b, const void* c); // 0x900610
};
}
}
namespace EA {
namespace XML {
struct XmlTokenReader : XmlReader {
    TokenIOContext_s0090_2460 mCtx;                              // +0x6c

    XmlTokenReader(EA::Allocator::ICoreAllocator_s0090_2460* alloc);
    ~XmlTokenReader();

    bool Read(const wchar_t* a, const wchar_t* b);     // @ 0x9031f0
    bool Read2(const wchar_t* a, const wchar_t* b, const wchar_t* c); // @ 0x903230
};
}
}
// ---- items of slice s00902460 end

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

// @ 0x00902250
namespace EA { namespace XML {
int TokenIOContext_s0090_13e0::GetString(const wchar_t* str)
{
    HashA* a = mStringsA;
    HIter it = a->FUN_009020b0(str);
    if (it.mpNode != a->mpBucket[a->mnBucketCount])
        return ((HashNode*)it.mpNode)->second;
    return 0;
}
}}  // namespace EA::XML

// @ 0x00902380
namespace EA { namespace XML {
wchar_t* sStrDup(const wchar_t* str, TokenIOContext_s0090_13e0* ctx)
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
}}  // namespace EA::XML

// @ 0x00902460
namespace EA { namespace XML {
void TokenIOContext_s0090_2460::ClearStrings()
{
    Hashtable_s0090_2460* h = mStringsA;
    if (h != 0) {
        h->DoAllocateBuckets(h->mpBucket, h->mnBucketCount);
        h->mnElementCount = 0;
        if (h->mnBucketCount > 1)
            EA_operator_delete(h->mpBucket);
    }
    {
        Hashtable_s0090_2460* n = (Hashtable_s0090_2460*)mAllocator.Allocate(0x20);
        if (n) n->InitEmpty();
        mStringsA = (HashA_s0090_2460*)n;
    }

    h = mStringsB;
    if (h != 0) {
        h->DoAllocateBuckets(h->mpBucket, h->mnBucketCount);
        h->mnElementCount = 0;
        if (h->mnBucketCount > 1)
            EA_operator_delete(h->mpBucket);
    }
    {
        Hashtable_s0090_2460* n = (Hashtable_s0090_2460*)mAllocator.Allocate(0x20);
        if (n) n->InitEmpty();
        mStringsB = (HashB_s0090_2460*)n;
    }
}
}}  // namespace EA::XML

// @ 0x00902590
namespace EA { namespace XML {
unsigned TokenIOContext_s0090_2460::AddString(const wchar_t* str, unsigned id)
{
    if ((int)id < 1) {
        id = (unsigned)mNextStringID;
        mNextStringID = (int)id + 1;
    } else if (mNextStringID <= (int)id) {
        mNextStringID = (int)id + 1;
    }
    const wchar_t* dup = sStrDup(str, this);
    HashA_s0090_2460* a = mStringsA;
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
}}  // namespace EA::XML

// @ 0x00902640
namespace EA { namespace XML {
bool WriteString(IStream* pStream, const wchar_t* s, TokenIOContext_s0090_2460* ctx)
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
}}  // namespace EA::XML

// @ 0x009027b0
namespace EA { namespace XML {
bool ReadString(IStream* pStream, FixedWStr256* out, TokenIOContext_s0090_2460* ctx)
{
    out->Reset(0);
    unsigned remaining = 0;
    io_ReadInt32(pStream, &remaining, 1, 0);
    if ((int)remaining < 0) {
        HashB_s0090_2460* t = ctx->mStringsB;
        unsigned key = remaining & 0x7fffffff;
        HIter_s0090_2460 it = t->find(key);
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
}}  // namespace EA::XML

// @ 0x00902950
namespace EA { namespace XML {
bool ReadToken(IStream* pStream, TokenNode** ppOut, TokenIOContext_s0090_2460* ctx)
{
    EA::Allocator::StackAllocator_s0090_2460* A = &ctx->mAllocator;
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
}}  // namespace EA::XML

// @ 0x00902c20
namespace EA { namespace XML {
int WriteToken(IStream* pStream, TokenNode* p, TokenIOContext_s0090_2460* ctx)
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
}}  // namespace EA::XML

// @ 0x00902d40
namespace EA { namespace XML {
bool ReadTokenList(IStream* pStream, TokenNode** ppOut, unsigned flags, TokenIOContext_s0090_2460* ctx)
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
        XmlTextReader tr((EA::Allocator::ICoreAllocator_s0090_2460*)0);
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
}}  // namespace EA::XML

// @ 0x00902fc0
namespace EA { namespace XML {
bool WriteTokenList(IStream* pStream, TokenNode* p, unsigned flags, TokenIOContext_s0090_2460* ctx)
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
}}  // namespace EA::XML

// @ 0x009030b0
namespace EA { namespace XML {
TokenIOContext_s0090_2460::TokenIOContext_s0090_2460(EA::Allocator::ICoreAllocator_s0090_2460* alloc)
: mAllocatorContext("UTF/XmlTokenReader/TokenIOContext/mAllocator", alloc),
      mAllocator(0, 0xffffffffu, 0, 0, 0)
{
    mNextStringID = 1;
    mStringsA = 0;
    mStringsB = 0;
    mAllocator.mnDefaultBlockSize = 0x800;
    mAllocator.Init(0, 0, (void*)&FUN_00925bf0, (void*)&FUN_00925c20, this);
    ClearStrings();
}
}}  // namespace EA::XML

// @ 0x009031a0
namespace EA { namespace XML {
XmlTokenReader::XmlTokenReader(EA::Allocator::ICoreAllocator_s0090_2460* alloc)
: XmlReader(alloc), mCtx(alloc)
{
}
}}  // namespace EA::XML

// @ 0x009031f0
namespace EA { namespace XML {
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
}}  // namespace EA::XML

// @ 0x00903230
namespace EA { namespace XML {
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
}}  // namespace EA::XML
