// src/game/UTFSpore_Win32/Commands.cpp -- migrated from slice(s) s0083c900, s0083b810 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Commands.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#define _VA_LIST_DEFINED   // the slices' own va_list typedef wins over <vadefs.h> (rewrite.py)
#include "game/types.h"
#include "eastl/allocator.h"
#include "EA/ArgScript/cArgInfo.h"
#include "EA/ArgScript/cArgumentSpec.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cEnumParseInfo.h"
#include "EA/ArgScript/cEnumSpec.h"
#include "EA/ArgScript/cError.h"
#include "EA/ArgScript/cOptionsSpec.h"

// unnamed retail callees and globals (address in the comment)
extern "C" unsigned __cdecl strlen(const char*);
extern void* vtbl_SPSkinPaintClear[];
extern void* vtbl_SPSkinPaintDistributeParticles[];
#pragma intrinsic(strlen)

// ---- items of slice s0083b810 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* vtbl_SPSkinPaintClear[];
extern void* vtbl_SPSkinPaintDistributeParticles[];
struct cCommandBase {
    void** vtbl;        // +0x00
    void*  mParser;     // +0x04
    int    mRefCount;   // +0x08
    cCommandBase();     // 0x0083c800 (SPSkinPaintClear ctor)
    int Release();      // 0x0083c760
};
struct cBlockCommandBase {
    void** vtbl; void* mParser; int mRefCount;
    int Release();      // 0x0083c7a0
};
struct cMetaCommandBase {
    void** vtbl; void* mParser; int mRefCount;
    cMetaCommandBase(); // 0x0083c840
    int Release();      // 0x0083c7d0
};
// ---- items of slice s0083b810 end

// ---- items of slice s0083c900 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int, int, const char* file, int line);
extern "C" void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
extern char gEmptyString[];
extern void* vtbl_AppProps;   // 0x0141b5e4 (equiv t3)
typedef unsigned int   uint32;
static const char g_allocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char g_allocName[] = "ArgScript";
namespace eastl {
struct allocator_s0083_c900 { unsigned char pad[4]; };
}
namespace eastl {
struct string8_s0083_c900 {
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator_s0083_c900 mAllocator;
    string8_s0083_c900() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    void assign(const char* first, const char* last);   // 0x00454cb0
    void assign(const char* p);                         // 0x006a4380
    void RangeInitialize(unsigned n);                   // 0x00475ab0
    string8_s0083_c900(const string8_s0083_c900& x);                          // 0x0057cb10
    ~string8_s0083_c900();
};
}
void  __cdecl DoFreeNodesTable(void* bucketArray, int bucketCount);       // 0x0083cad0 (this)
void  __cdecl HashNodeAlloc(void* out, int nBuckets, int nElem, int flag); // 0x00921440
void* __cdecl NewHashCommandNode(const void** key);                        // 0x0083c880
void  __cdecl HashDoRehash(void* self, int n);                             // 0x0083cf50
int   __cdecl StrEqInsensitive(const char* a, const char* b);              // 0x00554fb0
void  __cdecl MakeCaseInsensitive(void* p);
struct HashCmdTable { void* Insert(void* outIt, const void** keyPtr); };
struct CmdDtor {
    void* vtbl;
    int pad04[3];
    void* mpBucketArray;
    int   mnBucketCount;
    int   mnElementCount;
    int   pad1c;
    int   pad20[4];
    void Dtor();
};
struct AppPropsFields {
    void* vtbl;          // +0x00
    int   mParser;       // +0x04
    int   mRefCount;     // +0x08
    int   pad0c;         // +0x0c
    int   pad10;         // +0x10
    void* mpBucketArray; // +0x14
    int   mnBucketCount; // +0x18
    int   mnElementCount;// +0x1c
    float mMin;          // +0x20
    float mMax;          // +0x24
    int   pad28;         // +0x28
    AppPropsFields();                        // 0x0083cdd0
    AppPropsFields* VectorDtor(unsigned char flags); // 0x0083ce20
};
// ---- items of slice s0083c900 end

// @ 0x0083c760
int cCommandBase::Release()
{
    int n = --mRefCount;
    if (mRefCount == 0) {
        ((void(__thiscall*)(void*, int))vtbl[0x14 / 4])(this, 1);
        n = 0;
    }
    return n;
}

// @ 0x0083c7a0
int cBlockCommandBase::Release()
{
    int n = --mRefCount;
    if (mRefCount == 0) {
        ((void(__thiscall*)(void*, int))vtbl[0x20 / 4])(this, 1);
        n = 0;
    }
    return n;
}

// @ 0x0083c7d0
int cMetaCommandBase::Release()
{
    int n = --mRefCount;
    if (mRefCount == 0) {
        ((void(__thiscall*)(void*, int))vtbl[0x1c / 4])(this, 1);
        n = 0;
    }
    return n;
}

// @ 0x0083c800
cCommandBase::cCommandBase()
{
    vtbl = vtbl_SPSkinPaintClear;
    mParser = 0;
    mRefCount = 0;
}

// @ 0x0083c840
cMetaCommandBase::cMetaCommandBase()
{
    vtbl = vtbl_SPSkinPaintDistributeParticles;
    mParser = 0;
    mRefCount = 0;
}

// @ 0x0083c900
void* HashCmdTable::Insert(void* outIt, const void** keyPtr)
{
    void* self = this;
    const unsigned char* p = (const unsigned char*)*keyPtr;
    uint32 h = 0x811c9dc5;
    unsigned char c = *p;
    while (c) { ++p; h = h * 0x1000193 ^ c; c = *p; }
    unsigned n = h % *(unsigned*)((char*)self + 8);
    char* node = *(char**)(*(char**)((char*)self + 4) + n * 4);
    int* slot = (int*)(*(char**)((char*)self + 4) + n * 4);
    for (;;) {
        if (node == 0) {
            int changed = 0;
            HashNodeAlloc(&changed, *(int*)((char*)self + 8), *(int*)((char*)self + 0xc), 1);
            node = (char*)NewHashCommandNode(keyPtr);
            if ((char)changed) {
                n = h % *(unsigned*)((char*)self + 0xc);
                HashDoRehash(*(void**)((char*)self + 4), *(int*)((char*)self + 0xc));
            }
            *(char**)(node + 0x14) = *(char**)(*(char**)((char*)self + 4) + n * 4);
            *(char**)(*(char**)((char*)self + 4) + n * 4) = node;
            ++*(int*)((char*)self + 0xc);
            *(void**)outIt = node;
            *((void**)outIt + 1) = (char*)*(void**)((char*)self + 4) + n * 4;
            *((unsigned char*)outIt + 8) = 1;
            return node;
        }
        if (StrEqInsensitive((const char*)*keyPtr, (const char*)node))
            break;
        node = *(char**)(node + 0x14);
    }
    *(void**)outIt = node;
    *((void**)outIt + 1) = slot;
    *((unsigned char*)outIt + 8) = 0;
    return node;
}

// @ 0x0083ca00
void* HashFindExprValue(void* self, const char* key)
{
    const char* p = key;
    while (*p) ++p;
    unsigned len = (unsigned)(p - key) + 1;
    char* buf; char* cap;
    if (len < 2) { buf = gEmptyString; cap = gEmptyString + 1; }
    else { buf = (char*)EASTL_allocator_allocate(len, g_allocName, 0, 0, g_allocFile, 0xd1); cap = buf + len; }
    char* end = buf + (p - key);
    for (const char* s = key; s < p; ++s) *buf++ = *s;
    *end = 0;
    buf = end - (p - key);
    int keycopy[2];
    (void)keycopy;
    if ((cap - buf) > 1 && buf) EASTL_allocator_deallocate(buf);
    (void)self;
    return 0;
}

// @ 0x0083cad0
void __cdecl DoFreeNodesTable(void* bucketArray, int bucketCount)
{
    if (bucketCount > 1) {
        for (int i = 0; i < bucketCount; ++i) {
            char* node = *(char**)((char*)bucketArray + i * 4);
            while (node) {
                char* next = *(char**)(node + 0x14);
                // node dtor + free is a separate helper; caller frees the array below
                *(void**)(node + 0x14) = 0;
                node = next;
            }
        }
        (void)bucketArray;
    }
}

// @ 0x0083cb70
void* HashmapCommandLookup(void* self, const void* key)
{
    (void)self; (void)key; return 0;
}

// @ 0x0083cc30
void HashmapSetCommand(void* self, const char* name, int* cmd)
{
    eastl::string8_s0083_c900 s;
    s.assign(name, name + 0);
    MakeCaseInsensitive(&s);
    int** slot = (int**)HashmapCommandLookup(0, &s);
    (void)slot;
    (void)self; (void)cmd;
}

// @ 0x0083cd90
void CmdDtor::Dtor()
{
    vtbl = vtbl_AppProps;
    DoFreeNodesTable(mpBucketArray, mnBucketCount);
    if (mnBucketCount > 1)
        EASTL_allocator_deallocate(mpBucketArray);
    mnElementCount = 0;
}

// @ 0x0083ce20
AppPropsFields* AppPropsFields::VectorDtor(unsigned char flags)
{
    vtbl = vtbl_AppProps;
    DoFreeNodesTable(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if ((unsigned)mnBucketCount > 1)
        EASTL_allocator_deallocate(mpBucketArray);
    if (flags & 1)
        EASTL_allocator_deallocate(this);
    return this;
}
