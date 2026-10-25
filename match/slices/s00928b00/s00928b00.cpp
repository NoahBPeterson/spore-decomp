// Slice s00928b00 (bfs2 #24), 32-bit MSVC 2008.
// EA::Allocator::StackAllocator + EA file-stream/big-file helpers.
// Layouts from the 2008 dev PDB.
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <string.h>
#include <wchar.h>

typedef unsigned int uint32;
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned __int64 u64;

namespace EA { namespace Allocator {

struct Bookmark;
struct Block {
    Block* mpPrevBlock;  // +0x00
    char*  mpEnd;        // +0x04
    char   mData[4];     // +0x08
};

typedef void* (__cdecl *CoreAllocFn)(uint32 size, uint32* pActualSize, void* context);
typedef void  (__cdecl *CoreFreeFn)(void* p, void* context);

class StackAllocator {
public:
    uint32 mnDefaultBlockSize;       // +0x00
    Block* mpCurrentBlock;           // +0x04
    char*  mpCurrentBlockEnd;        // +0x08
    char*  mpCurrentObjectBegin;     // +0x0c
    char*  mpCurrentObjectEnd;       // +0x10
    CoreAllocFn mpCoreAllocationFunction; // +0x14
    CoreFreeFn  mpCoreFreeFunction;       // +0x18
    void*  mpCoreFunctionContext;    // +0x1c
    Bookmark* mpTopBookmark;         // +0x20

    void Init(Block* pBlock, uint32 blockSize, CoreAllocFn alloc, CoreFreeFn free, void* ctx);
    bool AllocateNewBlock(uint32 size);
    int  MallocAligned(int size, int align, int offset, char flag);
    StackAllocator(void* pBlock = 0, uint32 blockSize = 0xffffffff, CoreAllocFn alloc = 0,
                   CoreFreeFn free = 0, void* ctx = 0);
    void Reset(void* p);
    ~StackAllocator();
};

extern "C" void* SP_Pool_AllocGlobal(uint32 size, uint32* pActual, void* ctx); // 0x00928ad0
extern "C" void  operator_delete__f47410(void* p, void* ctx);                  // 0x00f47410
void EA_Text_ConvertEncoding(const wchar_t* src, int enc, int dstEnc, void* dst, uint32* pLen,
                             int a6);                                          // 0x0093c950

// EA::Allocator::BigFile -- stores a simple vector of open FileStream pointers plus
// the base name / directory / extension split and a resume offset.
struct BigFile {
    void**  mpBegin;      // +0x000 vector begin (FileStream*)
    void**  mpEnd;        // +0x004 vector end
    void**  mpCapacity;   // +0x008 vector capacity
    u8      mPad0C[8];    // +0x00c
    int     mnIndex;      // +0x014 current stream slot + 1
    u32     mnOffset;     // +0x018 byte offset inside current stream
    wchar_t mName[0x104]; // +0x01c full file name
    wchar_t mBase[0x104]; // +0x224 base part (no extension)
    void*   mpExt;        // +0x42c pointer into mName at extension, or 0
    u8      mPad430[4];   // +0x430
    u32     mnFlags;      // +0x434 open flags
    u32     mPad438[1];   // +0x438
    u32     mnArg0;       // +0x43c
    u32     mnArg1;       // +0x440
    u32     mnLastError;  // +0x444

    void FUN_00928e20();
    void FUN_00928f00(wchar_t* dst, unsigned n, int index);
    __int64 FUN_00928fc0();
    char FUN_00929000();
    void FUN_009290a0();
    int  FUN_00929100(void* buf, unsigned n);
    char FUN_00929310();
    char FUN_00929470(void* buf, unsigned a2, u32 a3, u32 a4);
    char FUN_009297a0(unsigned lo, int hi);
    char FUN_00929900(unsigned lo, int hi, int whence);
    int  FUN_00929220(const wchar_t* name);
    char FUN_00929290();
    void FUN_00929450();
    void FUN_00928f80(const wchar_t* name);
    char FUN_009290c0();
};

char EA_File_Exists(const wchar_t* name);                  // 0x00931fa0
void EA_File_Remove(const wchar_t* name);                  // 0x00931fd0
uint32 EA_File_GetSize(const wchar_t* name);               // 0x00932060
int  EA_Snprintf16(wchar_t* dst, unsigned n, const wchar_t* fmt, ...); // 0x00939a30
void* EA_FileStream_Ctor(void* self, const wchar_t* name); // 0x00931e10
void FUN_00997b10(void* p);                                // 0x00997b10 stream add
void FUN_00a80dd0(void** pos, void** val);                 // 0x00a80dd0 vector insert

// @ 0x00928b00
void StackAllocator::Init(Block* pBlock, uint32 blockSize, CoreAllocFn alloc, CoreFreeFn free,
                          void* ctx)
{
    if (mpCurrentBlock == 0) {
        if (alloc != 0)
            mpCoreAllocationFunction = alloc;
        if (free != 0)
            mpCoreFreeFunction = free;
        mpCoreFunctionContext = ctx;
        if (blockSize == 0)
            blockSize = mnDefaultBlockSize;
        else if (blockSize < 0xc)
            blockSize = 0xc;
        if (pBlock != 0 ||
            (pBlock = (Block*)mpCoreAllocationFunction(blockSize, &blockSize, ctx)) != 0) {
            mpCurrentBlock = pBlock;
            mpCurrentBlockEnd = pBlock->mData + (blockSize - 8);
            pBlock->mpEnd = pBlock->mData + (blockSize - 8);
            mpCurrentBlock->mpPrevBlock = 0;
            char* p = (char*)mpCurrentBlock + 8;
            mpCurrentObjectBegin = p;
            mpCurrentObjectEnd = p;
            if (((uint32)p & 7) != 0) {
                p = (char*)(((uint32)p + 7) & 0xfffffff8);
                mpCurrentObjectBegin = p;
                mpCurrentObjectEnd = p;
            }
        }
    }
}

// @ 0x00928ba0
bool StackAllocator::AllocateNewBlock(uint32 size)
{
    uint32 avail = (uint32)(mpCurrentObjectEnd - mpCurrentObjectBegin);
    uint32 need = (avail >> 2) + avail + 0x1008 + size;
    if (need < 0x2000)
        need = 0x2000;
    void* p = mpCoreAllocationFunction(need, &need, mpCoreFunctionContext);
    if (p != 0) {
        *(void**)p = mpCurrentBlock;
        char* dst = (char*)p + 8;
        mpCurrentBlock = (Block*)p;
        *((char**)p + 1) = (char*)p + need;
        mpCurrentBlockEnd = (char*)p + need;
        if (((uint32)dst & 7) != 0)
            dst = (char*)(((uint32)p + 0xf) & 0xfffffff8);
        if (avail != 0 && dst != 0 && mpCurrentObjectBegin != 0)
            memcpy(dst, mpCurrentObjectBegin, avail);
        mpCurrentObjectBegin = dst;
        mpCurrentObjectEnd = dst + avail;
        return true;
    }
    return false;
}

// @ 0x00928d40
int StackAllocator::MallocAligned(int size, int align, int offset, char flag)
{
    uint32 mask = (uint32)(align - 1) | 7;
    uint32 sz = (uint32)(size + 7) & 0xfffffff8;
    int p = (int)(((uint32)mpCurrentObjectBegin + offset + mask) & ~mask) - offset;
    if (flag != 0 && (char*)(p + sz) > mpCurrentBlockEnd) {
        if (!AllocateNewBlock(sz + mask + 1 + offset))
            return 0;
        p = (int)(((uint32)mpCurrentObjectBegin + offset + mask) & ~mask) - offset;
    }
    mpCurrentObjectBegin = (char*)(p + sz);
    mpCurrentObjectEnd = (char*)(p + sz);
    return p;
}

// @ 0x00928cd0
StackAllocator::StackAllocator(void* pBlock, uint32 blockSize, CoreAllocFn alloc, CoreFreeFn free,
                               void* ctx)
{
    mnDefaultBlockSize = 0x2000;
    mpCurrentBlock = 0;
    mpCurrentBlockEnd = 0;
    mpCurrentObjectBegin = 0;
    mpCurrentObjectEnd = 0;
    CoreAllocFn origAlloc = alloc;
    CoreFreeFn  origFree = free;
    if (alloc == 0)
        alloc = &SP_Pool_AllocGlobal;
    mpCoreAllocationFunction = alloc;
    if (free == 0)
        free = &operator_delete__f47410;
    mpCoreFreeFunction = free;
    mpCoreFunctionContext = 0;
    mpTopBookmark = 0;
    // Init receives the caller's original (possibly null) callbacks.
    if (blockSize != 0xffffffff)
        Init((Block*)pBlock, blockSize, origAlloc, origFree, ctx);
}

// @ 0x00928c40
void StackAllocator::Reset(void* p)
{
    Block* b = mpCurrentBlock;
    for (;;) {
        if (b == 0) {
            mpCurrentBlock = 0;
            mpCurrentBlockEnd = 0;
            mpCurrentObjectBegin = 0;
            mpCurrentObjectEnd = 0;
            return;
        }
        char* start = (char*)b + 8;
        if ((char*)p >= start && (char*)p <= b->mpEnd) {
            mpCurrentBlock = b;
            mpCurrentBlockEnd = b->mpEnd;
            mpCurrentObjectBegin = (char*)p;
            mpCurrentObjectEnd = (char*)p;
            return;
        }
        if (mpTopBookmark != 0) {
            void* bm = mpTopBookmark;
            while (bm != 0 && *(char**)((char*)bm + 4) >= start && b->mpEnd > *(char**)((char*)bm + 4)
                   && bm >= (void*)start && bm < (void*)b->mpEnd) {
                bm = *(void**)bm;
            }
            mpTopBookmark = (Bookmark*)bm;
        }
        Block* nxt = b->mpPrevBlock;
        if (mpCoreFreeFunction != 0)
            mpCoreFreeFunction(b, mpCoreFunctionContext);
        b = nxt;
    }
}

// @ 0x00929220
int BigFile::FUN_00929220(const wchar_t* name)
{
    void* self = this;
    char* p = (char*)self;
    *(int*)(p + 0) = 0;
    *(int*)(p + 4) = 0;
    *(int*)(p + 8) = 0;
    *(int*)(p + 0x430) = 0;
    *(int*)(p + 0x434) = 0;
    *(int*)(p + 0x438) = 0;
    *(int*)(p + 0x43c) = 0;
    *(int*)(p + 0x440) = 0;
    *(int*)(p + 0x444) = 0;
    if (name != 0) {
        uint32 n = 0x104;
        EA_Text_ConvertEncoding(name, -1, 8, (char*)self + 0x1c, &n, 0x10);
        *(unsigned short*)(p + 0x222) = 0;
        FUN_00928e20();
    }
    return (int)self;
}

// @ 0x00929290
char BigFile::FUN_00929290()
{
    void* self = this;
    char* p = (char*)self;
    char** begin = *(char***)p;
    char** end = *(char***)(p + 4);
    if (begin == end)
        return 1;
    for (char** it = begin; it != end; it++) {
        int* obj = (int*)*it;
        (*(void(__thiscall**)(int*))((char*)*obj + 0x18))(obj);
        if (*it != 0) {
            void** vt = *(void***)*it;
            (*(void(__thiscall**)(void*, int))vt[0])(*it, 1);
        }
    }
    char** b2 = *(char***)p;
    char** e2 = *(char***)(p + 4);
    memmove(b2, e2, 0);
    *(char**)(p + 4) = (char*)((char*)e2 - ((char*)e2 - (char*)b2));
    *(int*)(p + 0x434) = 0;
    *(int*)(p + 0x438) = 0;
    *(int*)(p + 0x43c) = 0;
    *(int*)(p + 0x440) = 0;
    return 1;
}

// @ 0x00929450
void BigFile::FUN_00929450()
{
    FUN_00929290();
    char* p = *(char**)this;
    if (p != 0 && *(int*)(p - 4) != 0)
        operator_delete__f47410(p, 0);
}

// ===========================================================================
// remaining small helpers
// ===========================================================================

// @ 0x00928dc0
void __fastcall FUN_00928dc0(StackAllocator* self)
{
    self->Reset(0);
}

// @ 0x00928de0
void FUN_00928de0(const char* s)
{
    if (s != 0)
        OutputDebugStringA(s);
}

// @ 0x00928df0
uint32 FUN_00928df0()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return si.dwPageSize;
}

// @ 0x00928f80
void BigFile::FUN_00928f80(const wchar_t* name)
{
    void* self = this;
    char* p = (char*)self;
    if (*(int*)p == *(int*)(p + 4) && name != 0) {
        wcsncpy((wchar_t*)(p + 0x1c), name, 0x104);
        *(unsigned short*)(p + 0x222) = 0;
        FUN_00928e20();
    }
}

// @ 0x009290c0
char BigFile::FUN_009290c0()
{
    void* self = this;
    int** begin = *(int***)self;
    int** end = *(int***)((char*)self + 4);
    char r = 0;
    if (begin != end) {
        r = 1;
        for (int** it = begin; it != end; it++) {
            if (r != 0) {
                int* obj = *it;
                r = (*(char(__thiscall**)(int*))((char*)*obj + 0x34))(obj);
                if (r != 0)
                    r = 1;
                else
                    r = 0;
            } else {
                r = 0;
            }
        }
    }
    return r;
}

// ===========================================================================
// big-file helpers: full bodies
// ===========================================================================
extern "C" void* operator_new(size_t size, const char* name, int, int, int, int); // 0x00f473a0

// @ 0x00928e20
void __thiscall BigFile::FUN_00928e20()
{
    wchar_t* name = mName;
    wchar_t* scan = name;
    do { } while (*scan++ != 0);
    u32 len = (u32)((scan - (name + 1)));
    if (len > 0xff)
        *name = 0;
    if (*name == 0) { mpExt = 0; return; }
    // copy name into base
    wchar_t* bp = mBase;
    wchar_t* src = name;
    wchar_t c;
    do { c = *src; *bp = c; ++src; ++bp; } while (c != 0);
    // length of base
    wchar_t* bs = mBase;
    wchar_t* bscan = bs;
    do { } while (*bscan++ != 0);
    u32 blen = (u32)(bscan - (mBase + 1));
    wchar_t* p = &mBase[blen - 1];   // last base char == param_1 + 0x222 + blen*2
    mpExt = p;
    if ((wchar_t*)mpExt < mBase) {
        mpExt = 0; return;
    }
    for (;;) {
        wchar_t* e = (wchar_t*)mpExt;
        wchar_t ch = *e;
        if (ch == 0x5c || ch == 0x2f || ch == 0x2e) break;
        e = e - 1;
        mpExt = e;
        if (e < mBase) break;
    }
    {
        wchar_t* e = (wchar_t*)mpExt;
        if (e >= mBase && *e == 0x2e) {
            *e = 0;
            mpExt = (char*)mpExt + 2;
            return;
        }
    }
    mpExt = 0;
}

// @ 0x00928f00
void __thiscall BigFile::FUN_00928f00(wchar_t* dst, unsigned n, int index)
{
    if (index == 0) {
        wcsncpy(dst, mName, n);
        return;
    }
    if (mpExt != 0) {
        EA_Snprintf16(dst, n, L"%ls.%03d.%ls", mBase, index, (const wchar_t*)mpExt);
        return;
    }
    EA_Snprintf16(dst, n, L"%ls.%03d", mName, index);
}

// @ 0x00928fc0
__int64 __thiscall BigFile::FUN_00928fc0()
{
    if (mpBegin == mpEnd)
        return (__int64)0xffffffffu;
    void** e = mpEnd;
    u32 n = (u32)((e - mpBegin)) - 1;
    void* obj = e[-1];
    u32 sz = (*(u32(__thiscall**)(void*))((char*)*(void**)obj + 0x1c))(obj);
    return (__int64)((unsigned __int64)n * 0x40000000u) + (unsigned __int64)sz;
}

// @ 0x00929000
char __thiscall BigFile::FUN_00929000()
{
    u32 n = (u32)(mpEnd - mpBegin);
    if ((mnFlags & 2) == 0) {
        mnLastError = 0xcfde0006;
        return 0;
    }
    if (n < 2) {
        mnLastError = 0xcfde000d;
        return 0;
    }
    void* obj = mpEnd[-1];
    (*(void(__thiscall**)(void*))((char*)*(void**)obj + 0x34))(obj);
    void* obj2 = mpEnd[-1];
    (*(void(__thiscall**)(void*))((char*)*(void**)obj2 + 0x18))(obj2);
    void* obj3 = mpEnd[-1];
    (*(void(__thiscall**)(void*))((char*)*(void**)obj3 + 8))(obj3);
    mpEnd -= 1;
    wchar_t buf[0x104];
    FUN_00928f00(buf, 0x104, n - 1);
    EA_File_Remove(buf);
    return 1;
}

// @ 0x009290a0
void __thiscall BigFile::FUN_009290a0()
{
    void* obj = mpBegin[mnIndex];
    u32 off = (*(u32(__thiscall**)(void*, int))((char*)*(void**)obj + 0x24))(obj, 0);
    mnOffset = off;
}

// @ 0x00929100
int __thiscall BigFile::FUN_00929100(void* buf, unsigned n)
{
    if (mpBegin == mpEnd)
        return -1;
    int written = 0;
    for (;;) {
        if (!(n > 0x40000000u || mnOffset + n > 0x40000000u))
            break;
        u32 room = 0x40000000u - mnOffset;
        if (room != 0) {
            void* obj = mpBegin[mnIndex];
            u32 got = (*(u32(__thiscall**)(void*, void*, u32))((char*)*(void**)obj + 0x30))(obj, buf, room);
            if (got == 0xffffffffu) {
                void* o = mpBegin[mnIndex];
                mnLastError = (*(u32(__thiscall**)(void*))((char*)*(void**)o + 0x14))(o);
                mnOffset = (*(u32(__thiscall**)(void*, int))((char*)*(void**)mpBegin[mnIndex] + 0x24))(mpBegin[mnIndex], 0);
                return -1;
            }
            mnOffset += got;
            written += got;
            n -= got;
            buf = (char*)buf + got;
            if (got < room)
                return written;
        }
        if (&mpBegin[mnIndex + 1] == mpEnd)
            return written;
        mnIndex += 1;
        mnOffset = 0;
        void* o = mpBegin[mnIndex];
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)o + 0x28))(o, 0, 0);
    }
    void* obj = mpBegin[mnIndex];
    int got = (*(int(__thiscall**)(void*, void*, unsigned))((char*)*(void**)obj + 0x30))(obj, buf, n);
    if (got != -1) {
        mnOffset += got;
        return got + written;
    }
    {
        void* o = mpBegin[mnIndex];
        mnLastError = (*(u32(__thiscall**)(void*))((char*)*(void**)o + 0x14))(o);
        mnOffset = (*(u32(__thiscall**)(void*, int))((char*)*(void**)mpBegin[mnIndex] + 0x24))(mpBegin[mnIndex], 0);
    }
    return -1;
}

// @ 0x00929310
char __thiscall BigFile::FUN_00929310()
{
    u32 n = (u32)(mpEnd - mpBegin);
    if (n == 0) {
        mnLastError = 0xfffffffe;
        return 0;
    }
    if (n > 0x3e6) {
        mnLastError = 0xcfde0009;
        return 0;
    }
    if ((mnFlags & 2) == 0) {
        mnLastError = 0xcfde0006;
        return 0;
    }
    wchar_t buf[0x104];
    FUN_00928f00(buf, 0x104, (int)n);
    void* fs = operator_new(0x22c, "BigFileStream", 0, 0, 0, 0);
    if (fs) fs = EA_FileStream_Ctor(fs, buf);
    if (mpEnd < mpCapacity) {
        void** slot = mpEnd;
        mpEnd = slot + 1;
        if (slot) *slot = fs;
    } else {
        FUN_00a80dd0(mpEnd, &fs);
    }
    void* obj = mpEnd[-1];
    (*(void(__thiscall**)(void*))((char*)*(void**)obj + 4))(obj);
    void* obj2 = mpEnd[-1];
    char ok = (*(char(__thiscall**)(void*, u32, int, u32, u32))((char*)*(void**)obj2 + 0x4c))(
        obj2, mnFlags, 2, mnArg0, mnArg1);
    if (!ok) {
        void* obj3 = mpEnd[-1];
        mnLastError = (*(u32(__thiscall**)(void*))((char*)*(void**)obj3 + 0x14))(obj3);
        void* obj4 = mpEnd[-1];
        (*(void(__thiscall**)(void*))((char*)*(void**)obj4 + 8))(obj4);
        mpEnd -= 1;
        return 0;
    }
    return 1;
}

// @ 0x00929470
char __thiscall BigFile::FUN_00929470(void* buf, unsigned a2, u32 a3, u32 a4)
{
    if (mpBegin == mpEnd || buf == 0)
        return (char)((mpBegin != mpEnd));
    if (a3 == 6)
        a3 = ((int)(size_t)buf & 2) ? 4 : 3;
    if (mName[0] == 0) {
        mnLastError = 0xcfde0003;
        return 0;
    }
    {
        wchar_t* s = mName;
        do { } while (*s++ != 0);
        u32 len = (u32)((s - (mName + 1)));
        if (len > 0xfe) {
            mnLastError = 0xcfde0003;
            return 0;
        }
    }
    int count = 0;
    if (!EA_File_Exists(mName)) {
    do_open:
        if (a3 == 3 || a3 == 5) {
            mnLastError = 0xcfde0004;
            return 0;
        }
    } else {
        int idx = 1;
        count = 1;
        for (;;) {
            wchar_t tmp[0x104];
            FUN_00928f00(tmp, 0x104, idx);
            if (!EA_File_Exists(tmp))
                break;
            count = count + 1;
            u32 sz = EA_File_GetSize(tmp);
            if (sz != 0x40000000u)
                break;
            idx = idx + 1;
            if (idx >= 0x3e7) {
                count = idx;
                break;
            }
        }
        if (count == 0)
            goto do_open;
        if (a3 == 1) {
            mnLastError = 0xcfde000a;
            return 0;
        }
    }
    void* fs = operator_new(0x22c, "BigFileStream", 0, 0, 0, 0);
    if (fs) fs = EA_FileStream_Ctor(fs, mName);
    if (mpEnd < mpCapacity) {
        void** slot = mpEnd;
        mpEnd = slot + 1;
        if (slot) *slot = fs;
    } else {
        FUN_00a80dd0(mpEnd, &fs);
    }
    {
        void* obj = mpEnd[-1];
        (*(void(__thiscall**)(void*))((char*)*(void**)obj + 4))(obj);
        void* obj2 = mpEnd[-1];
        char ok = (*(char(__thiscall**)(void*, void*, u32, u32, u32))((char*)*(void**)obj2 + 0x4c))(
            obj2, buf, a3, a3, a4);
        if (!ok) {
        fail:
            void* obj3 = mpEnd[-1];
            mnLastError = (*(u32(__thiscall**)(void*))((char*)*(void**)obj3 + 0x14))(obj3);
            FUN_00929290();
            return 0;
        }
        if (a3 == 2 || a3 == 5) {
            int i = 1;
            if (count > 1) {
                do {
                    wchar_t tmp[0x104];
                    FUN_00928f00(tmp, 0x104, i);
                    EA_File_Remove(tmp);
                    i = i + 1;
                } while (i < count);
            }
        } else {
            int i = 1;
            if (count > 1) {
                do {
                    wchar_t tmp[0x104];
                    FUN_00928f00(tmp, 0x104, i);
                    void* nf = operator_new(0x22c, "BigFileStream", 0, 0, 0, 0);
                    if (nf) nf = EA_FileStream_Ctor(nf, tmp);
                    FUN_00997b10(&nf);
                    void* obj4 = mpEnd[-1];
                    (*(void(__thiscall**)(void*))((char*)*(void**)obj4 + 4))(obj4);
                    void* obj5 = mpEnd[-1];
                    char ok2 = (*(char(__thiscall**)(void*, void*, u32, u32, u32))((char*)*(void**)obj5 + 0x4c))(
                        obj5, buf, 3, a3, a4);
                    if (!ok2)
                        goto fail;
                    i = i + 1;
                } while (i < count);
            }
        }
    }
    mnFlags = a3;
    mPad438[0] = a3;
    mnArg0 = a3;
    mnArg1 = a4;
    mnLastError = 0;
    mnIndex = 0;
    mnOffset = 0;
    return (char)(mpBegin != mpEnd);
}

// @ 0x009297a0
char __thiscall BigFile::FUN_009297a0(unsigned lo, int hi)
{
    if (mpBegin == mpEnd)
        return 0;
    u32 want;
    u32 wantOff;
    if (lo == 0 && hi == 0) {
        want = 1;
        wantOff = 0;
    } else {
        u32 a = lo + 0x3fffffff;
        u32 b = (u32)hi + (lo > 0xc0000000u ? 1u : 0u);
        want = (a >> 0x1e) | (b * 4);
        wantOff = ((lo - 1) & 0x3fffffff) + 1;
    }
    u32 n = (u32)(mpEnd - mpBegin);
    if (want < n) {
        u32 u = n;
        do {
            u32 prev = u;
            if (!FUN_00929000()) {
                void* o = mpBegin[mnIndex];
                mnOffset = (*(u32(__thiscall**)(void*, int))((char*)*(void**)o + 0x24))(o, 0);
                return 0;
            }
            u = prev - 1;
        } while (want < u);
        if (u <= (u32)mnIndex) {
            mnIndex = (int)(u - 1);
            mnOffset = 0x40000000;
        }
    } else {
        while (n < want) {
            void* o = mpBegin[n - 1];
            char ok = (*(char(__thiscall**)(void*, u32))((char*)*(void**)o + 0x20))(o, 0x40000000);
            if (!ok) {
                void* o2 = mpBegin[n - 1];
                mnLastError = (*(u32(__thiscall**)(void*))((char*)*(void**)o2 + 0x14))(o2);
                FUN_009290a0();
                return 0;
            }
            if (!FUN_00929310()) {
                FUN_009290a0();
                return 0;
            }
            n = n + 1;
        }
    }
    {
        void* o = mpBegin[n - 1];
        if ((*(char(__thiscall**)(void*, u32))((char*)*(void**)o + 0x20))(o, wantOff)) {
            if (wantOff < mnOffset)
                mnOffset = wantOff;
            void* o2 = mpBegin[mnIndex];
            mnOffset = (*(u32(__thiscall**)(void*, int))((char*)*(void**)o2 + 0x24))(o2, 0);
            return 1;
        }
        void* o3 = mpBegin[n - 1];
        mnLastError = (*(u32(__thiscall**)(void*))((char*)*(void**)o3 + 0x14))(o3);
        void* o4 = mpBegin[mnIndex];
        mnOffset = (*(u32(__thiscall**)(void*, int))((char*)*(void**)o4 + 0x24))(o4, 0);
    }
    return 0;
}

// @ 0x00929900
char __thiscall BigFile::FUN_00929900(unsigned lo, int hi, int whence)
{
    if (mpBegin == mpEnd)
        return 0;
    // current end segment (64-bit): base of last segment + its current size
    unsigned __int64 base =
        (unsigned __int64)((u32)(mpEnd - mpBegin) - 1) * 0x40000000u;
    base += (*(u32(__thiscall**)(void*))((char*)*(void**)mpEnd[-1] + 0x1c))(mpEnd[-1]);
    unsigned __int64 arg = (unsigned __int64)lo | ((unsigned __int64)(u32)hi << 32);
    unsigned __int64 target;
    if (whence == 0) {
        target = arg;
    } else if (whence == 2) {
        target = base + arg;
    } else {
        unsigned __int64 curPos = 0;
        if (mpBegin != mpEnd)
            curPos = (unsigned __int64)mnIndex * 0x40000000u + mnOffset;
        target = curPos + arg;
    }
    u32 want;
    u32 wantOff;
    if ((__int64)target < 0 || target == 0) {
        want = 0; wantOff = 0;
    } else {
        unsigned __int64 m = target - 1;
        want = (u32)(m >> 0x1e);
        wantOff = (u32)(m & 0x3fffffff) + 1;
    }
    while (want >= (u32)(mpEnd - mpBegin)) {
        u32 idx = (u32)(mpEnd - mpBegin) - 1;
        mnIndex = (int)idx;
        void* o = mpBegin[idx];
        if (!(*(char(__thiscall**)(void*, u32, int))((char*)*(void**)o + 0x28))(o, 0x40000000, 0))
            goto fail;
        {
            void* o2 = mpBegin[mnIndex];
            if (!(*(char(__thiscall**)(void*, int, int))((char*)*(void**)o2 + 0x38))(o2, 0, 0))
                goto fail;
        }
        FUN_00929310();
    }
    mnIndex = (int)want;
    mnOffset = wantOff;
    {
        void* o = mpBegin[want];
        if ((*(char(__thiscall**)(void*, u32, int))((char*)*(void**)o + 0x28))(o, wantOff, 0))
            return 1;
    }
fail:
    {
        void* o = mpBegin[mnIndex];
        mnLastError = (*(u32(__thiscall**)(void*))((char*)*(void**)o + 0x14))(o);
        void* o2 = mpBegin[mnIndex];
        mnOffset = (*(u32(__thiscall**)(void*, int))((char*)*(void**)o2 + 0x24))(o2, 0);
    }
    return 0;
}

}}
