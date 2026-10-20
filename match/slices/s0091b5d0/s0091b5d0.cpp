// Slice s0091b5d0 -- EA::Dasm::DisassemblerX86 + EA::Callstack::MapFileMSVC helpers.
// Reconstructed from the retail disassembly.
// Build: /O2 /MD /Gy /TP /arch:SSE /GR- /fp:fast

#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// --------------------------------------------------------------- imports ----
extern "C" {
__declspec(dllimport) void* __stdcall LoadLibraryA(const char*);
__declspec(dllimport) void* __stdcall GetProcAddress(void*, const char*);
__declspec(dllimport) int   __stdcall FreeLibrary(void*);
__declspec(dllimport) int   __stdcall UnDecorateSymbolName(const char*, char*, unsigned, unsigned);
__declspec(dllimport) int   __cdecl sprintf(char*, const char*, ...);
}

struct Vec12;
struct Vec16;

// ------------------------------------------------------ absolute callees ----
void* EAAllocate(u32 size, int a, int b, int c, const char* tag, const char* path); // 0x00f473a0
void* OpDelete(void* p);                                    // 0x00f47380
void  MemCopy(void* d, const void* s, unsigned n);          // 0x011e073e
void  MemMove(void* d, const void* s, unsigned n);          // 0x011e0744
void  StrRangeInit(void* s, unsigned n);                    // 0x00475ab0
void  StrAppend(void* s, const char* b, const char* e);     // 0x00455d60
u32   MemFindLastOf(const char* first, const char* last, const char* end); // 0x0062ff90
struct StrObj {
    char* a; char* b; char* c;
    void Init(const char* p);                       // 0x0057cb10
    void  AssignRange(const char* b, const char* e); // 0x00942e50
};
// 0x0057cb10  eastl::string::string(const char*)
void  RBTreeInsert(void* node, void* header, void* parent, int side); // 0x009216a0
void  StackAllocCtor(void* s, void* p, u32 n, void* a, void* b, void* c); // 0x00928cd0
struct MapNode { void* vtable; char pad[4]; void* DoCreateNode(const void* src); }; // 0x0091c140

// ------------------------------------------------------------- globals ------
extern "C" char g_vtbl_dasmx86[];      // 0x0143ce14
extern "C" char g_vtbl_dasmbase[];     // 0x014a21fc
extern "C" char g_vtbl_mapfile[];      // 0x0143ce60
extern "C" char g_s_kernel32[];        // 0x01409dcc
extern "C" char g_s_getproductinfo[];  // 0x01409dbc
extern "C" char g_s_dasmdll[];         // 0x0143ce04
extern "C" char g_s_dasminit[];        // 0x0143cdf4
extern "C" char g_s_cleanup[];         // 0x0143cde4
extern "C" char g_s_disasm[];          // 0x0143cdd4
extern "C" char g_s_formatinsn[];      // 0x0143cdc0
extern "C" char g_s_fmt08x[];          // 0x013fa098  "%08x"
extern "C" char g_s_invalid[];         // 0x0143ce3c  "(invalid) 0x%02x"
extern "C" char g_s_nodll[];           // 0x0143ce1c  "DLL not found, no disassembly."
extern "C" char g_s_eastl[];           // 0x013f2150  "EASTL"
extern "C" char g_s_srcpath[];         // 0x013ebb38
extern "C" int  g_hDasmDll;            // 0x01667b74
extern "C" int  g_fnInit;              // 0x01667b64
extern "C" int  g_fnCleanup;           // 0x01667b68
extern "C" int  g_fnDisasm;            // 0x01667b6c
extern "C" int  g_fnFormatInsn;        // 0x01667b70
extern "C" u8   g_osProbed;            // 0x01667b78
extern "C" u8   g_hasGetProductInfo;   // 0x01667b79
extern "C" u16  g_emptyW16[];          // 0x01667bac

struct Vec12 { u32* mpBegin; u32* mpEnd; u32* mpCap;
    void Push(const u32* v);            // 0x0091c490
    void Grow(u8* cur, const u32* v);   // 0x00a3d6e0
};
struct Vec16 { u32* mpBegin; u32* mpEnd; u32* mpCap;
    u8* Insert(u8* pos, const u32* v);                 // 0x0091c4d0
    u8* Grow(u8* first, u8* pos, const u32* v);        // 0x0092a100
};
struct StrStub { char* mpBegin; char* mpEnd; char* mpCap; void* AllocCopy(u32 n, const char* src); };

// eastl::string --- three pointers: begin, end, capacity.
struct EStr {
    char* mpBegin;   // 0
    char* mpEnd;     // 4
    char* mpCap;     // 8
};

// ===========================================================================
// EA::Dasm::DisassemblerX86
// ===========================================================================
struct DisassemblerX86 {
    void* vftable;                       // 0x000
    void* Ctor2();                       // 0x0091b5d0
    void* Dasm(const u8* start, const u8* end, u32 u3, u32 u4); // 0x0091b6d0
    void  Dtor();                        // 0x0091b6b0
    int   Undecorate(char* out, const char* sym, u32 len, u32 flags); // 0x0091b840
    u8*   ScalarDtor(u8 flags);          // 0x0091b810
};

// ===========================================================================
// EA::Callstack::MapFileMSVC
// ===========================================================================
struct MapFile {
    u8    mOpened;          // 0x00
    u32   mKind;            // 0x04
    void* mpStream;         // 0x08
    void* mpStr0;           // 0x0c
    void* mpStr0End;        // 0x10
    void* mpStr0Cap;        // 0x14
    u8    mPad18[4];        // 0x18
    void* mpStr1;           // 0x1c
    void* mpStr1End;        // 0x20
    void* mpStr1Cap;        // 0x24
    u8    mPad28[0x10];     // 0x28
    u32   mBase38;          // 0x38
    u32   mBase3c;          // 0x3c
    u16   mStride;          // 0x4a
    u16   mCount;           // 0x4c
    u16   mSel;             // 0x4e

    u8    Open(void* source);                       // 0x0091bd40
    u8    ReadSymbolBytes(int idx, u8* dst);        // 0x0091bd70
    u8    Parse(u8* buf);                           // 0x0091bb00
    u8    ReadRecord(u8* dst);                      // 0x0091bc30
    u8*   FindByAddress(u8* dst, u32 addr);         // 0x0091bdd0
    u8    CompareName(const char* other, u8* scratch); // 0x0091bce0
    u8    Reset();                                  // 0x0091beb0
    void* CtorEmpty();                              // 0x0091c0a0
    void  FreeStringsA();                           // 0x0091c0c0
    void  FreeStringsB();                           // 0x0091c100
    void* StrStubInit(const char* b, const char* e); // 0x0091c2d0
    void* RbtreeValCtor(u32* key, const void* src);  // 0x0091c310
    void* ListPushString(const char* s);             // 0x0091c330
    void  ListClear();                               // 0x0091c380
};

// ===========================================================================
// 0x0091b5d0  EA::Dasm::DisassemblerX86::DisassemblerX86
// ===========================================================================
// @ 0x0091b5d0
void* DisassemblerX86::Ctor2()
{
    u8* p = (u8*)this;
    int cached = g_hDasmDll;
    vftable = (void*)g_vtbl_dasmx86;
    if (cached != 0)
        return p;
    if (g_osProbed == 0) {
        void* h = LoadLibraryA(g_s_kernel32);
        if (h != 0) {
            if (GetProcAddress(h, g_s_getproductinfo) != 0)
                g_hasGetProductInfo = 1;
            FreeLibrary(h);
        }
        g_osProbed = 1;
    }
    if (g_hasGetProductInfo != 0)
        return p;
    g_hDasmDll = (int)LoadLibraryA(g_s_dasmdll);
    if (g_hDasmDll == 0)
        return p;
    g_fnInit = (int)GetProcAddress((void*)g_hDasmDll, g_s_dasminit);
    g_fnCleanup = (int)GetProcAddress((void*)g_hDasmDll, g_s_cleanup);
    g_fnDisasm = (int)GetProcAddress((void*)g_hDasmDll, g_s_disasm);
    g_fnFormatInsn = (int)GetProcAddress((void*)g_hDasmDll, g_s_formatinsn);
    return p;
}

// ===========================================================================
// 0x0091b6b0  EA::Dasm::DisassemblerX86::~DisassemblerX86
// ===========================================================================
// @ 0x0091b6b0
void DisassemblerX86::Dtor()
{
    int fn = g_fnCleanup;
    vftable = (void*)g_vtbl_dasmx86;
    if (fn != 0)
        ((void (__cdecl*)())fn)();
    vftable = (void*)g_vtbl_dasmbase;
}

// ===========================================================================
// 0x0091b810  scalar deleting destructor
// ===========================================================================
// @ 0x0091b810
u8* DisassemblerX86::ScalarDtor(u8 flags)
{
    int fn = g_fnCleanup;
    vftable = (void*)g_vtbl_dasmx86;
    if (fn != 0)
        ((void (__cdecl*)())fn)();
    vftable = (void*)g_vtbl_dasmbase;
    if ((flags & 1) != 0)
        OpDelete(this);
    return (u8*)this;
}

// ===========================================================================
// 0x0091b6d0  EA::Dasm::DisassemblerX86::Dasm
// ===========================================================================
// @ 0x0091b6d0
void* DisassemblerX86::Dasm(const u8* start, const u8* end, u32 u3, u32 u4)
{
    u8* p = (u8*)this;
    MemCopy(p, 0, 0x1f0);
    const u8* s = start;
    const u8* e = end;
    if (s >= e) {
        *(u32*)(p + 0x1d8) = 1;
        return (void*)e;
    }
    if ((u3 | u4) != 0) {
        *(u32*)(p + 0x1e0) = u3;
        *(u32*)(p + 0x1e4) = u4;
    } else {
        *(u32*)(p + 0x1e0) = (u32)s;
        *(u32*)(p + 0x1e4) = 0;
    }
    char* text = (char*)p;
    char* dst = text + 0x11;
    sprintf(text, g_s_fmt08x, (void*)*(u32*)(p + 0x1e0));
    if (g_fnInit != 0) {
        u32 n = ((u32 (__cdecl*)(const u8*, int, u32, char*))g_fnDisasm)(
                    s, (int)(e - s), *(u32*)(p + 0x1e0), text + 0x10);
        if (n != 0) {
            ((void (__cdecl*)(char*, char*, u32, u32))g_fnFormatInsn)(dst, text + 0x11, 0x20, 2);
            return (void*)(s + n);
        }
        sprintf(dst, g_s_invalid, *s);
        *(u32*)(p + 0x1d8) |= 1;
        *(u8*)(p + 0x31) = 0;
        return (void*)(s + 1);
    }
    sprintf(dst, g_s_nodll);
    *(u32*)(p + 0x1d8) |= 1;
    *(u8*)(p + 0x31) = 0;
    return (void*)e;
}

// ===========================================================================
// 0x0091b840  UnDecorateSymbolName -> name length
// ===========================================================================
// @ 0x0091b840
int DisassemblerX86::Undecorate(char* out, const char* sym, u32 bufLen, u32 flags)
{
    *out = 0;
    if (flags == 1) {
        if (UnDecorateSymbolName(sym, out, 0x2e0, bufLen) == 0)
            *out = 0;
    }
    char* p = out;
    char* start = out;
    do {
        ++p;
    } while (p[-1] != 0);
    return (int)(p - (start + 1));
}

// ===========================================================================
// 0x0091b880  eastl::string::replace(first,last,newFirst,newLast)
// ===========================================================================
// @ 0x0091b880
EStr* StrReplace(EStr* self, char* first, char* last, char* newFirst, char* newLast)
{
    u32 nNew = (u32)(newLast - newFirst);
    u32 nRemoved = (u32)(last - first);
    if (nNew >= nRemoved) {
        if (first <= last && last > newFirst && first < last)
            MemMove(first, newFirst, nNew);
        else
            MemCopy(first, newFirst, nNew);
        char* grown = first + nNew;
        if (grown != last) {
            MemMove(grown, last, (u32)(self->mpEnd - last) + 1);
            self->mpEnd += (u32)(grown - last);
        }
        return self;
    }
    return self;
}

// ===========================================================================
// 0x0091ba20  eastl::string::replace(pos, n, const char*)
// ===========================================================================
// @ 0x0091ba20
EStr* StrReplaceN(EStr* self, u32 pos, u32 n, const char* src)
{
    u32 avail = (u32)(self->mpEnd - self->mpBegin) - pos;
    u32 use;
    if (avail < n)
        use = avail;
    else
        use = n;
    const char* e = src;
    do {
        ++e;
    } while (e[-1] != 0);
    StrReplace(self, self->mpBegin + pos, self->mpBegin + pos + use, (char*)src, (char*)e);
    return self;
}

// ===========================================================================
// 0x0091ba90  build "middle + prefix" into a fresh string
// ===========================================================================
// @ 0x0091ba90
EStr* StrConcat3(EStr* out, const char* mid, EStr* pre, const char* suffix)
{
    const char* e = suffix;
    do {
        ++e;
    } while (e[-1] != 0);
    u32 nSuffix = (u32)(e - suffix) - 1;
    u32 nPre = (u32)(pre->mpEnd - pre->mpBegin);
    u32 nMid = (u32)(e - (const char*)mid) - 1;
    out->mpBegin = 0;
    out->mpEnd = 0;
    out->mpCap = 0;
    StrRangeInit(out, nMid + nPre + 1);
    *out->mpEnd = 0;
    StrAppend(out, pre->mpBegin, pre->mpEnd);
    StrAppend(out, mid, (char*)mid + nMid);
    return out;
}

// ===========================================================================
// 0x0091bec0  eastl::string::find_last_of
// ===========================================================================
// @ 0x0091bec0
u32 StrFindLastOf(EStr* self, const char* s, u32 pos)
{
    const char* e = s;
    do {
        ++e;
    } while (e[-1] != 0);
    u32 n = (u32)(e - s) - 1;
    char* base = self->mpBegin;
    u32 len = (u32)(self->mpEnd - base);
    u32 use = pos;
    if (len == 0)
        return 0xffffffff;
    u32 cap = len - 1;
    if (pos >= cap)
        use = cap;
    const char* r = (const char*)MemFindLastOf(base, base + use + 1, base + use + n + 1);
    if (r == base)
        return 0xffffffff;
    return (u32)(r - base) - 1;
}

// ===========================================================================
// 0x0091bf30  lower_bound over {u32 key, u32 sec} records (stride 0x10)
// ===========================================================================
// @ 0x0091bf30
u32* LowerBoundPair(u32* first, u32* last, const u32* key)
{
    u8* base = (u8*)first;
    int n = (int)((u8*)last - base) >> 4;
    while (n > 0) {
        int half = n >> 1;
        u32* mid = (u32*)(base + (half << 4));
        if (key[1] < mid[1] || (key[1] == mid[1] && key[0] < mid[0]))
            n = half;
        else {
            base = (u8*)mid + 0x10;
            n += -half - 1;
        }
    }
    return (u32*)base;
}

// ===========================================================================
// 0x0091bf80  rbtree insert with the "insert and rebalance" tail
// ===========================================================================
// @ 0x0091bf80
void* RBTreeInsertValue(u8* self, u8* parent, int side, const u32* value)
{
    int dir = 0;
    if (side == 0 && (u8*)parent != self + 4 && *(u32*)value >= *(u32*)(parent + 0x10))
        dir = 1;
    u8* node = (u8*)EAAllocate(0x1c, 0, 0, 0xd1, g_s_eastl, g_s_srcpath);
    u8* slot = node + 0x10;
    if (slot != 0) {
        *(u32*)slot = value[0];
        *(u32*)(slot + 4) = value[1];
        *(u32*)(slot + 8) = value[2];
    }
    RBTreeInsert(node, self + 4, parent, dir);
    ++*(u32*)(self + 0x14);
    return node;
}

// ===========================================================================
// 0x0091bd40  lazily open the symbol map
// ===========================================================================
// @ 0x0091bd40
u8 MapFile::Open(void* source)
{
    if (mOpened == 0) {
        mpStream = source;
        mOpened = Parse((u8*)this + 0x10);
    }
    return mOpened;
}

// ===========================================================================
// 0x0091bd70  read the opcode bytes of a symbol into the caller buffer
// ===========================================================================
// @ 0x0091bd70
u8 MapFile::ReadSymbolBytes(int idx, u8* dst)
{
    int count = 0;
    if (mOpened != 0 && (mBase38 | mBase3c) != 0 && mStride != 0)
        count = mCount;
    if (idx >= count)
        return 0;
    u8* cur = (u8*)(mBase38 + mStride * idx);
    void* stream = mpStream;
    void** vtbl = *(void***)stream;
    if (((u8 (__thiscall*)(void*, u8*, int))vtbl[0x28 / 4])(stream, cur, 0) == 0)
        return 0;
    return ReadRecord(dst);
}

// ===========================================================================
// 0x0091bb00  parse the ELF header + one symbol entry
// ===========================================================================
// @ 0x0091bb00
u8 MapFile::Parse(u8* buf)
{
    void* stream = mpStream;
    void** vtbl = *(void***)stream;
    if (((u8 (__thiscall*)(void*, int, int))vtbl[0x28 / 4])(stream, 0, 0) == 0)
        return 0;
    if (((u32 (__thiscall*)(void*, u8*, u32))vtbl[0x30 / 4])(stream, buf, 0x10) != 0x10)
        return 0;
    if (!(buf[0] == 0x7f && buf[1] == 0x45 && buf[2] == 0x4c && buf[3] == 0x46))
        return 0;
    u32 kind = buf[4];
    mKind = kind;
    if (kind == 1) {
        if (((u32 (__thiscall*)(void*, u8*, u32))vtbl[0x30 / 4])(stream, buf, 0x24) != 0x24)
            return 0;
    } else if (kind == 2) {
        if (((u32 (__thiscall*)(void*, u8*, u32))vtbl[0x30 / 4])(stream, buf + 0x10, 0x30) != 0x30)
            return 0;
    } else {
        return 0;
    }
    return 1;
}

// ===========================================================================
// 0x0091bc30  read one symbol record (0x40 or 0x28 bytes) into dst
// ===========================================================================
// @ 0x0091bc30
u8 MapFile::ReadRecord(u8* dst)
{
    if (mOpened == 0)
        return 0;
    if (mKind == 1) {
        void* stream = mpStream;
        void** vtbl = *(void***)stream;
        if (((u32 (__thiscall*)(void*, u8*, u32))vtbl[0x30 / 4])(stream, dst, 0x40) != 0x40)
            return 0;
        return 1;
    }
    if (mKind == 2) {
        void* stream = mpStream;
        void** vtbl = *(void***)stream;
        u8 tmp[0x28];
        if (((u32 (__thiscall*)(void*, u8*, u32))vtbl[0x30 / 4])(stream, tmp, 0x28) != 0x28)
            return 0;
        *(u32*)(dst + 0x00) = *(u32*)(tmp + 0x00);
        *(u32*)(dst + 0x04) = *(u32*)(tmp + 0x04);
        *(u32*)(dst + 0x08) = *(u32*)(tmp + 0x08);
        *(u32*)(dst + 0x0c) = 0;
        *(u32*)(dst + 0x10) = *(u32*)(tmp + 0x0c);
        *(u32*)(dst + 0x14) = 0;
        *(u32*)(dst + 0x18) = *(u32*)(tmp + 0x10);
        *(u32*)(dst + 0x1c) = 0;
        *(u32*)(dst + 0x20) = *(u32*)(tmp + 0x14);
        *(u32*)(dst + 0x24) = 0;
        *(u32*)(dst + 0x28) = *(u32*)(tmp + 0x18);
        *(u32*)(dst + 0x2c) = *(u32*)(tmp + 0x1c);
        *(u32*)(dst + 0x30) = *(u32*)(tmp + 0x20);
        *(u32*)(dst + 0x34) = 0;
        *(u32*)(dst + 0x38) = *(u32*)(tmp + 0x24);
        *(u32*)(dst + 0x3c) = 0;
        return 1;
    }
    return 0;
}

// ===========================================================================
// 0x0091bdd0  find a symbol by address
// ===========================================================================
// @ 0x0091bdd0
u8* MapFile::FindByAddress(u8* dst, u32 addr)
{
    if (mOpened == 0)
        return 0;
    u32 sel = mSel;
    u32 idx;
    u8 vb;
    if (sel < 0xff00) {
        idx = sel;
    } else if (sel == 0xffff) {
        if (!ReadSymbolBytes(0, dst))
            return 0;
        idx = *(u32*)(dst + 0x28);
    } else {
        return 0;
    }
    u8 rec[0x40];
    if (!ReadSymbolBytes(idx, rec))
        return 0;
    if (*(u32*)(rec + 4) == 8)
        return 0;
    u32 count = 0;
    if (mOpened != 0 && (mBase38 | mBase3c) != 0 && mStride != 0)
        count = mCount;
    for (int i = 0; i < (int)count; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (!ReadSymbolBytes(i + j, dst))
                continue;
            u32 a = *(u32*)dst + *(u32*)(rec + 0x10);
            void* stream = mpStream;
            void** vtbl = *(void***)stream;
            if (((u8 (__thiscall*)(void*, u32, int))vtbl[0x28 / 4])(stream, a, 0) == 0)
                continue;
            if (CompareName((const char*)addr, &vb) != 0)
                return dst;
        }
    }
    return 0;
}

// ===========================================================================
// 0x0091bce0  compare the mapped name against a C string
// ===========================================================================
// @ 0x0091bce0
u8 MapFile::CompareName(const char* other, u8* scratch)
{
    void* stream = mpStream;
    void** vtbl = *(void***)stream;
    ((u32 (__thiscall*)(void*, u8*, int))vtbl[0x30 / 4])(stream, scratch, 1);
    u8 c = *scratch;
    const char* p = other;
    if (c != 0) {
        if (*p == 0)
            goto done;
        if (c != *p)
            return 0;
        for (;;) {
            stream = mpStream;
            vtbl = *(void***)stream;
            ((u32 (__thiscall*)(void*, u8*, int))vtbl[0x30 / 4])(stream, scratch, 1);
            c = *scratch;
            ++p;
            if (c == 0)
                break;
            if (c != *p)
                return 0;
        }
    }
done:
    if (c == *p)
        return 1;
    return 0;
}

// ===========================================================================
// 0x0091beb0  reset
// ===========================================================================
// @ 0x0091beb0
u8 MapFile::Reset()
{
    u8* p = (u8*)this;
    *(u8*)(p + 4) = 0;
    *(u32*)(p + 0x18) = 0;
    *(u32*)(p + 0x1c) = 0;
    return 1;
}

// ===========================================================================
// 0x0091c0a0  string-stub ctor (two inline members)
// ===========================================================================
// @ 0x0091c0a0
void* MapFile::CtorEmpty()
{
    u16* e0 = g_emptyW16;
    u16* e1 = g_emptyW16 + 1;
    mpStream = e0;
    mpStr0 = e0;
    mpStr0End = e1;
    mpStr1 = e0;
    mpStr1End = e0;
    mpStr1Cap = e1;
    return this;
}

// ===========================================================================
// 0x0091c0c0  free the first pair of string stubs
// ===========================================================================
// @ 0x0091c0c0
void MapFile::FreeStringsA()
{
    u8* a = (u8*)mpStr1;
    if ((int)((u32)mpStr1Cap - (u32)a) > 1 && a != 0)
        OpDelete(a);
    u8* b = (u8*)mpStream;
    if ((int)((u32)mpStr0End - (u32)b) > 1 && b != 0)
        OpDelete(b);
}

// ===========================================================================
// 0x0091c100  free the second pair of string stubs
// ===========================================================================
// @ 0x0091c100
void MapFile::FreeStringsB()
{
    u8* a = (u8*)mpStr1End;
    if ((int)(*(u32*)((u8*)this + 0x28) - (u32)a) > 1 && a != 0)
        OpDelete(a);
    u8* b = (u8*)mpStr0;
    if ((int)((u32)mpStr0Cap - (u32)b) > 1 && b != 0)
        OpDelete(b);
}

// ===========================================================================
// 0x0091c2d0  init an inline StrStub from a char range
// ===========================================================================
// @ 0x0091c2d0
void* MapFile::StrStubInit(const char* b, const char* e)
{
    u8* p = (u8*)this;
    u8* base = p + 0x14;
    *(u8**)(p + 0x10) = base;
    *(u8**)(p + 8) = base + 0x100;
    *(u8**)(p + 4) = base;
    *(u8**)p = base;
    *base = 0;
    ((StrObj*)p)->AssignRange(b, e);
    return p;
}

// ===========================================================================
// 0x0091c310  copy-construct a node value
// ===========================================================================
// @ 0x0091c310
void* MapFile::RbtreeValCtor(u32* key, const void* src)
{
    u8* p = (u8*)this;
    u32 k = *key;
    *(u32*)p = k;
    ((MapNode*)(p + 4))->DoCreateNode(src);
    return p;
}

// ===========================================================================
// 0x0091c140  rbtree::DoCreateNode
// ===========================================================================
// @ 0x0091c140
u8* Fn91c140(u8* self, const u8* src)
{
    *(u32*)self = *(u32*)src;
    *(u32*)(self + 4) = *(u32*)(src + 4);
    u8* s0 = self + 8;
    *(u32*)s0 = 0;
    *(u32*)(s0 + 4) = 0;
    *(u32*)(s0 + 8) = 0;
    u32 len0 = *(u32*)(src + 0xc) - *(u32*)(src + 8);
    StrRangeInit(s0, len0 + 1);
    char* p0 = *(char**)s0;
    MemMove(p0, *(void**)(src + 8), len0);
    *(char**)(s0 + 4) = p0 + len0;
    *p0 = 0;
    *(u32*)(self + 0x18) = *(u32*)(src + 0x18);
    u8* s1 = self + 0x1c;
    *(u32*)s1 = 0;
    *(u32*)(s1 + 4) = 0;
    *(u32*)(s1 + 8) = 0;
    u32 len1 = *(u32*)(src + 0x20) - *(u32*)(src + 0x1c);
    StrRangeInit(s1, len1 + 1);
    char* p1 = *(char**)s1;
    MemMove(p1, *(void**)(src + 0x1c), len1);
    *(char**)(s1 + 4) = p1 + len1;
    *p1 = 0;
    return self;
}

// ===========================================================================
// 0x0091c210  MapFileMSVC ctor (bump allocator)
// ===========================================================================
// @ 0x0091c210
u8* MapCtorBig(u8* self)
{
    void* e0 = g_emptyW16;
    void* e1 = g_emptyW16 + 1;
    *(void**)self = (void*)g_vtbl_mapfile;
    *(u8*)(self + 4) = 0;
    *(void**)(self + 8) = e0;
    *(void**)(self + 0xc) = e0;
    *(void**)(self + 0x10) = e1;
    u8* mem = (u8*)EAAllocate(0x40000, 0, 0, 0xd1, g_s_eastl, g_s_srcpath);
    *(u8**)(self + 0x20) = mem + 0x40000;
    *(u8**)(self + 0x18) = mem;
    *(u8**)(self + 0x1c) = mem;
    u8* p = mem;
    for (int i = 0x4000; i > 0; --i, p += 0x10) {
        if (p != 0) {
            *(u32*)p = 0;
            *(u32*)(p + 4) = 0;
            *(u32*)(p + 8) = 0;
            *(u32*)(p + 0xc) = 0;
        }
    }
    *(u8**)(self + 0x1c) = *(u8**)(self + 0x18) + 0x40000;
    StackAllocCtor(self + 0x2c, 0, 0x10000, 0, 0, 0);
    *(u32*)(self + 0x50) = 0;
    *(u32*)(self + 0x54) = 0;
    return self;
}

// ===========================================================================
// 0x0091c330  append a fresh 0x18-byte node carrying a string
// ===========================================================================
// @ 0x0091c330
void* MapFile::ListPushString(const char* s)
{
    u8* p = (u8*)this;
    u8* n = (u8*)EAAllocate(0x18, 0, 0, 0xd1, g_s_eastl, g_s_srcpath);
    u8* str = (u8*)n + 8;
    if (str != 0)
        ((StrObj*)str)->Init(s);
    *(void**)n = p;
    *(u32*)(n + 4) = *(u32*)(p + 4);
    **(u32**)(p + 4) = (u32)n;
    *(u32*)(p + 4) = (u32)n;
    return n;
}

// ===========================================================================
// 0x0091c380  free every node of the list
// ===========================================================================
// @ 0x0091c380
void MapFile::ListClear()
{
    u8* p = (u8*)this;
    u8* n = *(u8**)p;
    if (n == p)
        return;
    do {
        u8* cur = n;
        u8* c = *(u8**)(cur + 0x10);
        u8* a = *(u8**)(cur + 8);
        u8* nxt = *(u8**)cur;
        n = nxt;
        if ((int)(c - a) > 1 && a != 0)
            OpDelete(a);
        OpDelete(cur);
    } while (n != p);
}

// ===========================================================================
// 0x0091c490  vector push_back of a 12-byte value
// ===========================================================================
// @ 0x0091c490
void Vec12::Push(const u32* v)
{
    u8* p = (u8*)this;
    u8* cur = *(u8**)(p + 4);
    if (cur < *(u8**)(p + 8)) {
        *(u8**)(p + 4) = cur + 0xc;
        if (cur != 0) {
            *(u32*)cur = v[0];
            *(u32*)(cur + 4) = v[1];
            *(u32*)(cur + 8) = v[2];
        }
        return;
    }
    ((Vec12*)p)->Grow(cur, v);
}

// ===========================================================================
// 0x0091c4d0  vector insert of a 16-byte value
// ===========================================================================
// @ 0x0091c4d0
u8* Vec16::Insert(u8* pos, const u32* v)
{
    u8* p = (u8*)this;
    u8* first = *(u8**)p;
    u32 idx = (u32)(pos - first) >> 4;
    u8* last = *(u8**)(p + 4);
    if (pos != last || last == *(u8**)(p + 8)) {
        ((Vec16*)p)->Grow(first, pos, (const u32*)v);
    } else {
        *(u8**)(p + 4) = last + 0x10;
        if (last != 0) {
            *(u32*)last = v[0];
            *(u32*)(last + 4) = v[1];
            *(u32*)(last + 8) = v[2];
            *(u32*)(last + 0xc) = v[3];
        }
    }
    return first + ((idx << 4) & 0xfffffff0);
}

// ===========================================================================
// 0x0091c540  allocate and fill a string buffer
// ===========================================================================
// @ 0x0091c540
void* StrStub::AllocCopy(u32 n, const char* src)
{
    u8* p = (u8*)this;
    u8* buf;
    if (n != 0)
        buf = (u8*)EAAllocate(n, 0, 0, 0xd1, g_s_eastl, g_s_srcpath);
    else
        buf = 0;
    *(u8**)p = buf;
    *(u8**)(p + 4) = buf;
    *(u8**)(p + 8) = buf + n;
    char c = *src;
    if (n > 0)
        MemCopy(buf, (const void*)(u32)(u8)c, n);
    *(u8**)(p + 4) = *(u8**)p + n;
    return p;
}
