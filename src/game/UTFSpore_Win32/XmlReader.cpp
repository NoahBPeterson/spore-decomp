// src/game/UTFSpore_Win32/XmlReader.cpp -- migrated from slice(s) s00900410 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/XmlReader.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/IStream.h"
#include "EA/IO/MemoryStream.h"
#include "EA/Allocator/StackAllocator.h"
#include "EA/XHTML/Style/Stylesheet.h"
#include "EA/XML/Token.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int __cdecl strcmp(const char*, const char*);
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n); // 0x011e0744
#include <new>
#include <intrin.h>
#pragma intrinsic(strcmp)

// ---- items of slice s00900410 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
typedef unsigned short uint16;
namespace EA {
namespace Allocator {
class StackAllocator_s0090_0410 {
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

    StackAllocator_s0090_0410(void* pBlock = 0, uint32 blockSize = 0xffffffff, void* alloc = 0,
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
}
}
struct Token_s0090_0410 {
    Token_s0090_0410* mpNext;       // +0x00
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
namespace EA {
namespace IO {
enum PositionType_s0090_0410 { kPositionTypeBegin_s0090_0410 = 0 };
}
}
namespace EA {
namespace IO {
class IStream_s0090_0410 {
public:
    virtual ~IStream_s0090_0410();                                  // slot 0
    virtual int  AddRef();                               // slot 1 (+0x04)
    virtual int  Release();                              // slot 2 (+0x08)
    virtual int  GetType() const;                        // slot 3
    virtual int  GetAccessFlags() const;                 // slot 4
    virtual int  GetState() const;                       // slot 5
    virtual bool Close();                                // slot 6 (+0x18)
    virtual uint32 GetSize() const;                      // slot 7 (+0x1c)
    virtual bool SetSize(uint32 size);                   // slot 8
    virtual int  GetPosition(PositionType_s0090_0410 type) const;   // slot 9 (+0x24)
    virtual bool SetPosition(int pos, PositionType_s0090_0410 type);// slot 10 (+0x28)
    virtual uint32 GetAvailable() const;                 // slot 11
    virtual uint32 Read(void* p, uint32 size);           // slot 12 (+0x30)
    virtual bool Flush();                                // slot 13
    virtual bool Write(const void* p, uint32 size);      // slot 14
};
}
}
class XmlReader {
public:
    void** vftable;                 // +0x00
    int    mResultCode;             // +0x04
    int    mAllocatorContextName;   // +0x08
    int    mAllocatorContextAlloc;  // +0x0c
    char   mAllocator[0x24];        // +0x10
    EA::IO::IStream_s0090_0410* mpInputStream; // +0x34
    Token_s0090_0410* mpFirstToken;            // +0x38
    Token_s0090_0410* mpLastToken;             // +0x3c
    Token_s0090_0410* mpCurrentToken;          // +0x40
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
    __declspec(noinline) void* ReadString(EA::Allocator::StackAllocator_s0090_0410* pAlloc, uint32* pOut);
    void FUN_009008f0();
    void* FUN_00900970(const void* v);

    XmlReader(void* pAllocator);
    ~XmlReader();
    void* DeletingDtor(char flags);
    char  InitAllocator(EA::IO::IStream_s0090_0410* pStream, const uint16* pPath);
};
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n); // 0x011e0744
extern "C" uint16 g_wcharNull;                 // 0x0141a154
#define VFN0C(p, off) (*(char (__thiscall**)(void*))((char*)(*(void**)(p)) + (off)))
// ---- items of slice s00900410 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" uint16 g_wcharNull;                 // 0x0141a154

// @ 0x00900800
void* XmlReader::ReadString(EA::Allocator::StackAllocator_s0090_0410* pAlloc, uint32* pOut)
{
    Token_s0090_0410* p = this->mpCurrentToken;
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
    ReadString((EA::Allocator::StackAllocator_s0090_0410*)this->mAllocator, &local);
}
