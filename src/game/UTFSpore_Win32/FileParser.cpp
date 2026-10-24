// src/game/UTFSpore_Win32/FileParser.cpp -- migrated from slice(s) s0092f220, s00840250, s0083f140 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/FileParser.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int, int, const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned n);
extern char gEmptyString[]; // 0x01667bac
extern "C" void* __cdecl Messaging_GetServer();

// ---- items of slice s0083f140 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uint32;
typedef unsigned short uint16;
extern "C" void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int, int, const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned n);
static const char g_allocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char g_allocName[] = "ArgScript";
extern char gEmptyString[]; // 0x01667bac
void  __cdecl HashNodeAlloc(void* out, int nBuckets, int nElem, int flag);  // 0x00921440
void* __cdecl MakeFileNotifyNode(int* key);                         // 0x0083fb40
void  __cdecl HashDoRehash(void* bucketArray, int n);                       // 0x0083f9b0
void  __cdecl HashFindFileNotify(void* self, void* out, void* key);   // 0x007e2ea0
int   __cdecl HashFindNode(const void* key, void* node);                   // 0x00554fb0
namespace eastl {
struct allocator_s0083_f140 { unsigned char pad[4]; };
}
namespace eastl {
struct string8_s0083_f140 {
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator_s0083_f140 mAllocator;
    string8_s0083_f140() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    string8_s0083_f140(const char* first, const char* last) {
        unsigned n = (unsigned)(last - first) + 1;
        if (n <= 1) { mpBegin = gEmptyString; mpCapacity = gEmptyString + 1; }
        else { mpBegin = (char*)EASTL_allocator_allocate(n, g_allocName, 0, 0, g_allocFile, 0xd1); mpCapacity = mpBegin + n; }
        memcpy(mpBegin, first, (unsigned)(last - first));
        mpEnd = mpBegin + (last - first);
        *mpEnd = 0;
    }
    void RangeInitialize(unsigned n);
    void assign(const string8_s0083_f140& x);
    ~string8_s0083_f140(); // 0x00530670
};
}
namespace eastl {
bool operator==(const string8_s0083_f140& s, const char* lit);   // 0x00555020
}
struct cIParser { void** vftable; };
extern "C" void* __cdecl Messaging_GetServer();
extern "C" cIParser* __cdecl CreateParser();
// ---- items of slice s0083f140 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" cIParser* __cdecl CreateParser();

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void** __fastcall PairCtorRefPtr(void** self, int, void** src, int* val);  // 0x0083fa80 (stays in the slice: not this object's)
void** __fastcall InputFileSpecCopy(void** self, int, void** src);  // 0x0083fae0 (stays in the slice: not this object's)

// ---- items of slice s00840250 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
struct allocator_s0084_0250 { unsigned char pad[4]; };
}
namespace eastl {
struct string8_s0084_0250 {
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator_s0084_0250 mAllocator;
    string8_s0084_0250() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    void assign(const char* first, const char* last);
    void append(const char* first, const char* last);  // 0x00616960 (eastl::string8::append)
    void resize(unsigned n, char c);
    void append_sprintf_va_list(const char* fmt, void* args);
    ~string8_s0084_0250();
};
}
void  __cdecl MakeCaseInsensitive2(const char* p, eastl::string8_s0084_0250* s);    // 0x00840cc0
void  __cdecl FileParser_ShutdownStub(void* self);
void  __cdecl HashFreeNotifyStub(void* bucketArray, int bucketCount);
void  __cdecl VectorFreeSpecsStub(int* self);
void  __cdecl IterateWatchersStub(void* map);
void  __cdecl HashResetNotifyStub(void* map);
// ---- items of slice s00840250 end

// ---- items of slice s0092f220 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_pfnTable;             // 0x01668f20
extern char  g_vtbl_143e540;         // primary vtable
extern char  g_vtbl_13fc474;         // base vtable
typedef void* HANDLE;
struct OVERLAPPED_ {
    uint32_t Internal;
    uint32_t InternalHigh;
    uint32_t Offset;
    uint32_t OffsetHigh;
    void*    hEvent;
};
struct ThreadRef {
    void* mpData;                    // +0
    void  Init();                    // 0x00743B50
    int   WaitStatus(void* out);     // 0x00922A10
    void  Release();                 // 0x00922E10
    void  Notify(const void* n, int);        // 0x00922940
    void* StartThread(void*, void*, void*, void*); // 0x009231A0
};
struct FileWatcher {
    void*         m_vtbl;            // +0x000
    bool          m_bActive;         // +0x004
    unsigned short m_path[0x101];    // +0x006 (compiler pads +0x005)
    uint32_t      m_flags;           // +0x208
    uint32_t      m_shareMode;       // +0x20c
    void*         m_callback;        // +0x210
    void*         m_callbackData;    // +0x214
    HANDLE        m_hChange;         // +0x218
    HANDLE        m_hEvent;          // +0x21c
    ThreadRef     m_thread;          // +0x220
    HANDLE        m_hFile;           // +0x224
    OVERLAPPED_   m_ov;              // +0x228
    bool          m_bRunning;        // +0x23c

    FileWatcher* Construct();
    bool  SetFlags(uint32_t f);
    bool  SetShareMode(uint32_t f);
    bool  SetPath(const unsigned short* p);
    short* Reset0();
    bool  Stop();                    // 0x0092F5F0
    void  Worker(uint32_t filter);   // 0x0092F650
    void  Watch(uint32_t mode, const unsigned short* path); // 0x0092F8B0
    bool  Close();                   // 0x0092F9E0
    bool  Start();                   // 0x0092FAF0
    uint32_t Arm(uint32_t);          // 0x0092FBE0
    void  Destroy();                 // 0x0092FC50
    FileWatcher* DestroyScalar(unsigned char flags); // 0x0092FC80
};
// ---- items of slice s0092f220 end

// @ 0x0083f5e0
int __fastcall FileParser_Release(int* self)
{
    int* rc = self + 2;           // mRefCount at +0x8
    *rc = *rc - 1;
    int r = *rc;
    if (r == 0) {
        ((void(__thiscall*)(int*, int))(*(void***)((char*)self + 4))[0])((int*)((char*)self + 4), 1);
        r = 0;
    }
    return r;
}

// @ 0x0083f600
unsigned char __fastcall FileParser_HandleMessage(int* self, int, int msg, int)
{
    if (msg != 0x6f41f272)
        return 0;
    *((unsigned char*)self + 0x24) = 1;      // mFilesModified
    if (*((unsigned char*)self + 0x25))      // mAutoParseEnabled
        ((void(__thiscall*)(int*))(*(void***)((char*)self - 4))[8])((int*)((char*)self - 4));
    return 1;
}

// @ 0x0083f630
bool __fastcall FileParser_Init(int* self)
{
    if (*((unsigned char*)self + 0xc) == 0) {
        *((unsigned char*)self + 0xc) = 1;
        int* server = (int*)Messaging_GetServer();
        if (server)
            ((void(__thiscall*)(int*, int*, int))(*(void***)server)[8])(server, self + 1, 0x6f41f272);
        return true;
    }
    return false;
}

// @ 0x0083f680
bool __fastcall FileParser_Shutdown(int* self)
{
    if (*((unsigned char*)self + 0xc)) {
        *((unsigned char*)self + 0xc) = 0;
        int* server = (int*)Messaging_GetServer();
        if (server)
            ((void(__thiscall*)(int*, int*, int, int))(*(void***)server)[11])(server, self + 1, 0x6f41f272, 0xffffd8f1);
        if (self[4]) {
            ((void(__thiscall*)(int*))(*(void***)self[4])[3])((int*)self[4]);
            int* p = (int*)self[4];
            if (p) {
                self[4] = 0;
                ((void(__thiscall*)(int*))(*(void***)p)[1])(p);
            }
        }
        ((void(__thiscall*)(int*))(*(void***)self)[6])(self);
        return true;
    }
    return false;
}

// @ 0x0083f6f0
void __fastcall FileParser_SetParser(int* self, int, cIParser* p)
{
    cIParser* old = (cIParser*)self[4];
    if (old)
        ((void(__thiscall*)(cIParser*))(*(void***)old)[3])(old);
    old = (cIParser*)self[4];
    if (p != old) {
        if (p)
            ((void(__thiscall*)(cIParser*))(*(void***)p)[0])(p);
        self[4] = (int)p;
        if (old)
            ((void(__thiscall*)(cIParser*))(*(void***)old)[1])(old);
    }
    old = (cIParser*)self[4];
    if (old)
        ((void(__thiscall*)(cIParser*))(*(void***)old)[2])(old);
}

// @ 0x0083f740
cIParser* __fastcall FileParser_Parser(int* self)
{
    if (self[4] == 0) {
        cIParser* p = CreateParser();
        cIParser* old = (cIParser*)self[4];
        if (p != old) {
            if (p)
                ((void(__thiscall*)(cIParser*))(*(void***)p->vftable)[0])(p);
            self[4] = (int)p;
            if (old)
                ((void(__thiscall*)(cIParser*))(*(void***)old->vftable)[1])(old);
        }
        ((void(__thiscall*)(cIParser*))(*(void***)((cIParser*)self[4])->vftable)[2])((cIParser*)self[4]);
    }
    return (cIParser*)self[4];
}

// @ 0x0083f790
bool __fastcall FileParser_ParseFiles(int* self)
{
    cIParser* parser = (cIParser*)self[4];
    if (parser != 0) {
        ((void(__thiscall*)(cIParser*))(*(void***)parser->vftable)[12])(parser);
        int* specsBegin = (int*)self[5];      // vector begin at +0x14
        int* specsEnd = (int*)self[6];
        unsigned count = (unsigned)((char*)specsEnd - (char*)specsBegin) / 0x14;
        for (unsigned i = 0; i < count; ++i) {
            ((void(__thiscall*)(cIParser*, void*))(*(void***)((cIParser*)self[4])->vftable)[14])(
                (cIParser*)self[4], (void*)specsBegin[i * 5]);
        }
        int* server = (int*)Messaging_GetServer();
        if (server) {
            int flag = 1;
            ((void(__thiscall*)(int*, int, int*, int))(*(void***)server)[5])(server, 0x4b3bc676, &flag, 0);
        }
    }
    return false;
}

// @ 0x0083f8f0
void __fastcall RefRelease(int** p)
{
    int* o = *p;
    if (o && --*(int*)((char*)o + 0x240) == 0) {
        *(int*)((char*)o + 0x240) = 1;
        ((void(__thiscall*)(int*, int))(*(void***)o)[0])(o, 1);
    }
}

// @ 0x0083f940
int** __fastcall RefAssign(int** self, int, int** other)
{
    int* n = (int*)*other;
    int* o = (int*)*self;
    if (n != o) {
        if (n)
            (*(int*)((char*)n + 0x240))++;
        *self = n;
        if (o && --*(int*)((char*)o + 0x240) == 0) {
            *(int*)((char*)o + 0x240) = 1;
            ((void(__thiscall*)(int*, int))(*(void***)o)[0])(o, 1);
        }
    }
    return self;
}

// @ 0x0083fa00
void __fastcall HashNodeDtorRef(int* self)
{
    int* o = (int*)self[4];
    if (o && --*(int*)((char*)o + 0x240) == 0) {
        *(int*)((char*)o + 0x240) = 1;
        ((void(__thiscall*)(int*, int))(*(void***)o)[0])(o, 1);
    }
    int b = self[0];
    if ((self[2] - b) > 1 && b)
        EASTL_allocator_deallocate((void*)b);
}

// @ 0x0083fbc0
int* __cdecl UninitCopySpecs(int* first, int* last, int* dst)
{
    if (first == last)
        return dst;
    do {
        if (dst) {
            dst[0] = 0; dst[1] = 0; dst[2] = 0;
            void* s = (void*)first[0];
            unsigned n = (unsigned)(first[1] - (int)s) + 1;
            if (n < 2) {
                dst[0] = (int)gEmptyString;
                dst[1] = (int)gEmptyString;
                dst[2] = (int)(gEmptyString + 1);
            } else {
                int p = (int)EASTL_allocator_allocate(n, g_allocName, 0, 0, g_allocFile, 0xd1);
                dst[0] = p; dst[1] = p; dst[2] = p + n;
            }
            memcpy((void*)dst[0], s, n - 1);
            ((char*)dst[0])[n - 1] = 0;
            dst[1] = dst[0] + (n - 1);
            *(uint16*)(dst + 4) = *(uint16*)(first + 4);
        }
        first += 5;
        dst += 5;
    } while (first != last);
    return dst;
}

// @ 0x0083fcd0
int* __cdecl CopyBackwardSpecs(int* first, int* last, int* dst)
{
    if (first == last)
        return dst;
    do {
        if (first != dst)
            ((eastl::string8_s0083_f140*)dst)->assign(*(eastl::string8_s0083_f140*)first);
        *(uint16*)(dst + 4) = *(uint16*)(first + 4);
        first += 5;
        dst += 5;
    } while (first != last);
    return dst;
}

// @ 0x0083fd20
int* __cdecl CopyBackwardSpecsRev(int* first, int* last, int* dst)
{
    if (last == first)
        return dst;
    int* f;
    int* d;
    do {
        f = last - 5;
        d = dst - 5;
        if (f != d)
            ((eastl::string8_s0083_f140*)f)->assign(*(eastl::string8_s0083_f140*)d);
        *(uint16*)(dst - 1) = *(uint16*)(last - 1);
        last = f;
        dst = d;
    } while (f != first);
    return d;
}

// @ 0x0083fde0
void __fastcall HashInsertFileNotify(int* self, int, int* outIt, int* key)
{
    const unsigned char* p = (const unsigned char*)*key;
    uint32 h = 0x811c9dc5;
    unsigned char c = *p;
    while (c) { ++p; h = h * 0x1000193 ^ c; c = *p; }
    unsigned n = h % *(unsigned*)((char*)self + 8);
    char** slot = (char**)(*(char**)((char*)self + 4) + n * 4);
    char* node = *slot;
    char* chain = (char*)slot;
    for (;;) {
        if (node == 0) {
            int changed = 0;
            HashNodeAlloc(&changed, *(int*)((char*)self + 8), *(int*)((char*)self + 0xc), 1);
            node = (char*)MakeFileNotifyNode(key);
            if ((char)changed) {
                n = h % *(unsigned*)((char*)self + 0xc);
                HashDoRehash(*(void**)((char*)self + 4), *(int*)((char*)self + 0xc));
            }
            *(char**)(node + 0x14) = *(char**)(*(char**)((char*)self + 4) + n * 4);
            *(char**)(*(char**)((char*)self + 4) + n * 4) = node;
            ++*(int*)((char*)self + 0xc);
            *(char**)outIt = node;
            *((char**)outIt + 1) = (char*)*(void**)((char*)self + 4) + n * 4;
            *((unsigned char*)outIt + 8) = 1;
            return;
        }
        if (HashFindNode(key, node)) {
            *(char**)outIt = node;
            *((char**)outIt + 1) = chain;
            *((unsigned char*)outIt + 8) = 0;
            return;
        }
        chain = node + 0x14;
        node = *(char**)(node + 0x14);
    }
}

// @ 0x0083fee0
void __cdecl DoFreeNodesFileNotify(char** bucketArray, unsigned bucketCount)
{
    for (unsigned i = 0; i < bucketCount; ++i) {
        char* n = *(char**)((char*)bucketArray + i * 4);
        while (n) {
            char* next = *(char**)(n + 0x14);
            HashNodeDtorRef((int*)n);
            EASTL_allocator_deallocate(n);
            n = next;
        }
        *(char**)((char*)bucketArray + i * 4) = 0;
    }
}

// @ 0x0083ff30
int __fastcall HashmapFileNotifyLookup(int* self, int, int key)
{
    int out[8];
    HashFindFileNotify(self, out, (void*)key);
    if ((int)out[0] != *(int*)(*(int*)((char*)self + 4) + *(int*)((char*)self + 8) * 4))
        return out[0] + 0x10;
    int zero = 0;
    int val = (int)PairCtorRefPtr((void**)out, 0, (void**)key, &zero);
    HashInsertFileNotify(self, 0, out, (int*)key);
    return out[0] + 0x10 + (val - val);
}

// @ 0x0083fff0
void* __fastcall VectorSpecInsert(int* self, int, void* pos, void* val)
{
    char* end = (char*)self[1];
    if (end != (char*)self[2]) {
        if ((char*)pos <= (char*)val && (char*)val < end)
            val = (char*)val + 0x14;
        if (end)
            InputFileSpecCopy((void**)end - 5, 0, (void**)(end - 0x14));
        CopyBackwardSpecsRev((int*)pos, (int*)(self[1] - 0x14), (int*)self[1]);
        if (val != pos)
            ((eastl::string8_s0083_f140*)val)->assign(*(eastl::string8_s0083_f140*)pos);
        *(uint16*)((char*)val + 0x10) = *(uint16*)((char*)pos + 0x10);
        self[1] += 0x14;
        return pos;
    }
    int cap = (int)((char*)end - (char*)self[0]) / 0x14;
    if (cap == 0)
        cap = 1;
    else
        cap *= 2;
    char* buf = cap ? (char*)EASTL_allocator_allocate(cap * 0x14, g_allocName, 0, 0, g_allocFile, 0xd1) : 0;
    int* mid = UninitCopySpecs((int*)self[0], (int*)pos, (int*)buf);
    if (mid)
        InputFileSpecCopy((void**)mid, 0, (void**)val);
    int* mid2 = UninitCopySpecs((int*)pos, (int*)self[1], mid + 5);
    if (self[0] && *(int*)((char*)self[0] - 4))
        EASTL_allocator_deallocate((void*)self[0]);
    self[1] = (int)mid2;
    self[0] = (int)buf;
    self[2] = (int)(buf + cap * 0x14);
    return pos;
}

// @ 0x00840250
void __fastcall FileParser_dtor(int* self)
{
    *(void**)self = 0;
    *(void**)((char*)self + 4) = 0;
    if (*((unsigned char*)self + 0xc))
        FileParser_ShutdownStub((void*)self);
    HashFreeNotifyStub(*(void**)((char*)self + 0x30), *(int*)((char*)self + 0x34));
    *(int*)((char*)self + 0x38) = 0;
    if (*(int*)((char*)self + 0x34) > 1)
        EASTL_allocator_deallocate(*(void**)((char*)self + 0x30));
    VectorFreeSpecsStub(self);
}

// @ 0x00840340
void __fastcall FileParser_ClearFilePaths(int* self)
{
    IterateWatchersStub((void*)((char*)self + 0x28));
    HashResetNotifyStub((void*)((char*)self + 0x28));
}

// @ 0x00840420
void __fastcall FileParser_AddFilePath(int* self, int, char* path, int flags)
{
    eastl::string8_s0084_0250 s;
    const char* end = path;
    while (*end) ++end;
    s.assign(path, end);
    MakeCaseInsensitive2(path, &s);
    (void)self; (void)flags;
}

// @ 0x00840700
void __fastcall FileParser_ctor(int* self)
{
    *(void**)((char*)self + 4) = 0;
    *(void**)self = 0;
    self[2] = 0;                                   // mRefCount
    *((unsigned char*)self + 0xc) = 0;
    self[4] = 0;                                   // mParser
    self[5] = 0; self[6] = 0; self[7] = 0;         // mInputFileSpecs
    *((unsigned char*)self + 0x24) = 0;
    *((unsigned char*)self + 0x25) = 0;
    self[0x0e] = 0;                                // hash_map bucket array
    self[0x0f] = 0;
    self[0x10] = 0;
}

// @ 0x0092fac0
bool FileWatcher::SetShareMode(uint32_t f)
{
    bool result = false;
    if (m_thread.WaitStatus(0) != 1) {
        m_shareMode = f;
        result = true;
    }
    return result;
}

// @ 0x0092fbe0
uint32_t FileWatcher::Arm(uint32_t)
{
    uint32_t f = m_flags;
    uint32_t mode = (f & 3) ? 1 : 0;
    if (f & 4)  mode |= 2;
    if (f & 8)  mode |= 0x10;
    if (f & 0x10) mode |= 4;
    if (f & 0x20) mode |= 8;
    if (f != 0) {
        if (g_pfnTable != 0) {
            Worker(mode);
            return 0;
        }
        if (m_path != 0 && m_path[0] != 0) {
            Watch(mode, m_path);
        }
    }
    return 0;
}

// @ 0x0092fc50
void FileWatcher::Destroy()
{
    m_vtbl = &g_vtbl_143e540;
    Close();
    m_thread.Release();
    m_vtbl = &g_vtbl_13fc474;
}
