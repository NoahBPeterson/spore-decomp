// src/game/UTFSpore_Win32/MapFile.cpp -- migrated from slice(s) s0091b5d0, s0091c640 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/MapFile.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "eastl/map.h"
#include "EA/Dasm/DisassemblerX86.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __cdecl sscanf(const char* buffer, const char* format, ...);
extern "C" __declspec(dllimport) void* __cdecl memmove(void* dst, const void* src, unsigned n);
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned n);
extern "C" int __cdecl strcmp(const char* a, const char* b);
extern char gEmptyString;  // 0x01667bac (eastl empty-string sentinel, 2 bytes)
#pragma intrinsic(strcmp)

// ---- items of slice s0091c640 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __cdecl sscanf(const char* buffer, const char* format, ...);
extern "C" __declspec(dllimport) void* __cdecl memmove(void* dst, const void* src, unsigned n);
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned n);
extern "C" int __cdecl strcmp(const char* a, const char* b);
void* operator new(unsigned size, const char* name, int flags, unsigned debugFlags, const char* file,
                   int line);                   // 0x00f473a0
void operator delete(void* p);                  // 0x00f47380
extern char gEmptyString;  // 0x01667bac (eastl empty-string sentinel, 2 bytes)
namespace {

const char kEastlAllocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// ---- EA::IO::FileStream (virtual dtor and Read; ctor/Open/GetSize/Close are plain thiscall).
struct FileStream {
    FileStream(const wchar_t* path);                          // 0x00931e10
    virtual ~FileStream();                                    // 0x00931e70
    virtual int Read(void* dst, unsigned size);               // 0x00931ce0
    bool Open(int access, int create, int sharing, int usage);  // 0x009318f0
    unsigned GetSize();                                       // 0x00931b70
    bool Close();                                             // 0x00931a70
    char pad[0x228];
};

// ---- eastl::vector<unsigned char> (fill constructor, inlined dtor test).
struct ByteVector {
    unsigned char* mpBegin;
    unsigned char* mpEnd;
    unsigned char* mpCapacity;
    ByteVector(unsigned n, const unsigned char& value, const char& alloc);  // 0x0091c540
};

// ---- eastl::basic_string<char, allocator> (3 pointers + allocator).
struct String {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    unsigned mAlloc;
    String& assign(const char* s);  // 0x006a4380
};

// ---- eastl::fixed_string<char, 256> (0x114 bytes: begin, end, cap, alloc, pool, buffer).
struct FixedString {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    unsigned mAlloc;
    char* mpPool;
    char mBuffer[256];
    FixedString()
    {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 256;
        mpPool = mBuffer;
        mBuffer[0] = 0;
    }
    FixedString(const char* p, unsigned n);                         // 0x0091c2d0
    ~FixedString() { DeallocateSelf(); }
    void DeallocateSelf()                                           // 0x00919a40
    {
        if (mpCapacity - mpBegin > 1 && mpBegin && mpBegin != mpPool)
            operator delete(mpBegin);
    }
    void assign(const char* first, const char* last);               // 0x00942e50
    int compare(unsigned pos, unsigned n, const char* s) const;     // 0x008417c0
    unsigned find_last_of(const char* set, unsigned pos) const;     // 0x0091bec0
    void erase(unsigned pos, unsigned n);                           // 0x0061e200
};

const char* find_first_not_of(const char* first, const char* last, const char* setFirst,
                              const char* setLast);                 // 0x0061df60
const char* GetTextLine(const char* begin, const char* end, const char** next);  // 0x0093d0b0
unsigned __int64 GetModuleBase(int);                                // 0x0091a1d0
int UndecorateName(const char* in, char* out, unsigned outSize, int flags);  // 0x0091b840

struct Symbol {  // MapFileMSVC::Symbol, 0x2c bytes
    unsigned mSegment;
    unsigned mOffset;
    String mSymbol;
    unsigned mRVA;
    String mSourceObj;
    Symbol()  // 0x0091c0a0: both strings start on the empty sentinel
    {
        mSymbol.mpBegin = &gEmptyString;
        mSymbol.mpEnd = &gEmptyString;
        mSymbol.mpCapacity = &gEmptyString + 1;
        mSourceObj.mpBegin = &gEmptyString;
        mSourceObj.mpEnd = &gEmptyString;
        mSourceObj.mpCapacity = &gEmptyString + 1;
    }
    ~Symbol();  // 0x0091c0c0
};

struct SymbolPair {  // pair<const unsigned, Symbol>, 0x30 bytes
    unsigned first;
    Symbol second;
    SymbolPair(const unsigned& key, const Symbol& sym);  // 0x0091c310
    ~SymbolPair();                                       // 0x0091c100
};

struct InsertResult {  // pair<iterator, bool>
    void* it;
    bool inserted;
};

struct SymbolMap {  // eastl::map<unsigned, Symbol>
    uint32_t mCompare;                 // +0x00  (the comparator)
    eastl::rbtree_node_base mAnchor;   // +0x04  {right, left = begin, parent = root, color}
    uint32_t mnSize;                   // +0x14
    uint32_t mAllocator;               // +0x18
    InsertResult* insert(InsertResult* out, const SymbolPair& v);  // 0x0091cc30
};

struct FileLineEntry {
    String* mpFile;
    int mLine;
};
struct FileLineMap {  // eastl::map<unsigned, pair<String*, int>>
    uint32_t mCompare;                 // +0x00  (the comparator)
    eastl::rbtree_node_base mAnchor;   // +0x04  {right, left = begin, parent = root, color}
    uint32_t mnSize;                   // +0x14
    uint32_t mAllocator;               // +0x18
    FileLineEntry& operator[](const unsigned& key);  // 0x0091c9b0
};

struct StringNode {
    StringNode* mpNext;
    StringNode* mpPrev;
    String mValue;
};
struct StringList {  // eastl::list<String>
    StringNode* mpNext;
    StringNode* mpPrev;
    unsigned mnSize;
    void push_back(const String& s);  // 0x0091c330
};

struct Group {
    unsigned mSegment, mOffset, mLength;
};
struct GroupVector {
    Group* mpBegin;
    Group* mpEnd;
    Group* mpCapacity;
    unsigned mAlloc;
    void push_back(const Group& g);  // 0x0091c490
};
struct UIntVector {
    unsigned* mpBegin;
    unsigned* mpEnd;
    unsigned* mpCapacity;
    unsigned mAlloc[2];
    void resize(unsigned n, const unsigned& value);  // 0x004746c0
};

struct MapFileMSVC {
    void* vtable;                 // +0x00
    bool mbLoadAttempted;         // +0x04
    wchar_t* mpPathBegin;         // +0x08
    char pad0[0xc];
    unsigned __int64 mBaseAddress;  // +0x18
    SymbolMap mAddressToSymbolMap;  // +0x20
    StringList mLineFilenameList;   // +0x3c
    FileLineMap mAddressToFileLineMap;  // +0x48
    UIntVector mSectionArray;       // +0x64
    GroupVector mGroupArray;        // +0x78

    bool Load();
};

inline unsigned strlen_(const char* s)
{
    const char* p = s;
    while (*p++)
        ;
    return p - s - 1;
}
}  // namespace
// ---- items of slice s0091c640 end

// ---- items of slice s0091b5d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_vtbl_mapfile[];      // 0x0143ce60
extern "C" char g_s_eastl[];           // 0x013f2150  "EASTL"
extern "C" char g_s_srcpath[];         // 0x013ebb38
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
struct Vec12;
struct Vec16;
void* EAAllocate(u32 size, int a, int b, int c, const char* tag, const char* path); // 0x00f473a0
void* OpDelete(void* p);                                    // 0x00f47380
void  MemCopy(void* d, const void* s, unsigned n);          // 0x011e073e
void  MemMove(void* d, const void* s, unsigned n);          // 0x011e0744
void  StrRangeInit(void* s, unsigned n);                    // 0x00475ab0
struct StrObj {
    char* a; char* b; char* c;
    void Init(const char* p);                       // 0x0057cb10
    void  AssignRange(const char* b, const char* e); // 0x00942e50
};
void  RBTreeInsert(void* node, void* header, void* parent, int side); // 0x009216a0
void  StackAllocCtor(void* s, void* p, u32 n, void* a, void* b, void* c); // 0x00928cd0
struct MapNode { void* vtable; char pad[4]; void* DoCreateNode(const void* src); }; // 0x0091c140
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
// ---- items of slice s0091b5d0 end

// @ 0x0091beb0
u8 MapFile::Reset()
{
    u8* p = (u8*)this;
    *(u8*)(p + 4) = 0;
    *(u32*)(p + 0x18) = 0;
    *(u32*)(p + 0x1c) = 0;
    return 1;
}

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

// @ 0x0091c310
void* MapFile::RbtreeValCtor(u32* key, const void* src)
{
    u8* p = (u8*)this;
    u32 k = *key;
    *(u32*)p = k;
    ((MapNode*)(p + 4))->DoCreateNode(src);
    return p;
}

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

// @ 0x0091ccf0
bool MapFileMSVC::Load()
{
    if (!mbLoadAttempted) {
        mbLoadAttempted = true;
        FileStream file(mpPathBegin);
        if (file.Open(1, 6, 1, 0)) {
            int mode = 0;               // 0 none, 1 segment table, 2 address table, 3 line numbers
            String* currentFile = 0;
            unsigned size = file.GetSize();
            char zero = 0;
            ByteVector buffer(size, (const unsigned char&)zero, zero);
            file.Read(buffer.mpBegin, size);
            file.Close();
            const char* cursor = (const char*)buffer.mpBegin;
            const char* end = cursor + size;
            do {
                const char* lineStart = cursor;
                const char* lineEnd = GetTextLine(cursor, end, &cursor);
                if (lineEnd == lineStart)
                    continue;
                FixedString line;
                line.assign(lineStart, lineEnd);
                {
                    // ltrim
                    const char* f = find_first_not_of(line.mpBegin, line.mpEnd, " ", " " + 1);
                    unsigned pos = (f == line.mpEnd) ? (unsigned)-1 : (unsigned)(f - line.mpBegin);
                    unsigned len = line.mpEnd - line.mpBegin;
                    const unsigned* m = &len;
                    if (!(len < pos))
                        m = &pos;
                    const char* p = line.mpBegin + *m;
                    if (line.mpBegin != p) {
                        memmove(line.mpBegin, p, line.mpEnd + 1 - p);
                        line.mpEnd += line.mpBegin - p;
                    }
                }
                if (line.compare(0, 5, "Start") == 0)
                    mode = 1;
                if (line.compare(0, 9, "Preferred") == 0) {
                    unsigned base;
                    if (sscanf(line.mpBegin + 9, " load address is %x", &base) == 1) {
                        mBaseAddress = base;
                        continue;
                    }
                }
                if (line.compare(0, 7, "Address") == 0) {
                    mode = 2;
                    continue;
                }
                if (line.compare(0, 12, "Line numbers") == 0) {
                    mode = 0;
                    int nameStart, nameEnd;
                    char close;
                    if (sscanf(line.mpBegin + 12, " for %*[^(](%n%*[^)]%n%c\n", &nameStart, &nameEnd,
                               &close) == 1 &&
                        close == ')') {
                        FixedString name(line.mpBegin + 12 + nameStart, nameEnd - nameStart);
                        unsigned p = name.find_last_of("/\\:", (unsigned)-1);
                        if (p != (unsigned)-1)
                            name.erase(0, p + 1);
                        mode = 3;
                        String str;
                        {
                            const char* s = name.mpBegin;
                            unsigned n = strlen_(s);
                            unsigned cap = n + 1;
                            char* mem;
                            char* memEnd;
                            if (cap >= 2) {
                                mem = (char*)operator new(cap, "EASTL", 0, 0, kEastlAllocFile, 0xd1);
                                memEnd = mem + cap;
                            } else {
                                mem = &gEmptyString;
                                memEnd = &gEmptyString + 1;
                            }
                            str.mpBegin = mem;
                            str.mpCapacity = memEnd;
                            memcpy(mem, s, n);
                            mem[n] = 0;
                            str.mpEnd = mem + n;
                        }
                        mLineFilenameList.push_back(str);
                        if (str.mpCapacity - str.mpBegin > 1 && str.mpBegin)
                            operator delete(str.mpBegin);
                        currentFile = &mLineFilenameList.mpPrev->mValue;
                    }
                    continue;
                }
                if (line.compare(0, 7, "Exports") == 0) {
                    mode = 0;
                    continue;
                }
                if (line.mpBegin != line.mpEnd) {
                    switch (mode) {
                    case 3: {
                        unsigned offs[4], lines[4], secs[4];
                        int n = sscanf(line.mpBegin, "%u %x:%x %u %x:%x %u %x:%x %u %x:%x", &lines[0],
                                       &secs[0], &offs[0], &lines[1], &secs[1], &offs[1], &lines[2],
                                       &secs[2], &offs[2], &lines[3], &secs[3], &offs[3]);
                        int count = n / 3;
                        for (int i = 0; i < count; ++i) {
                            if (secs[i] < (unsigned)(mSectionArray.mpEnd - mSectionArray.mpBegin)) {
                                unsigned addr = mSectionArray.mpBegin[secs[i]] + offs[i];
                                int ln = lines[i];
                                FileLineEntry& e = mAddressToFileLineMap[addr];
                                e.mpFile = currentFile;
                                e.mLine = ln;
                            }
                        }
                        break;
                    }
                    case 2: {
                        unsigned section, offset, rva;
                        char mangled[2048];
                        char obj[512];
                        if (sscanf(line.mpBegin, "%x:%x %s %x %*c %s", &section, &offset, mangled, &rva,
                                   obj) == 5) {
                            char undecorated[2048];
                            UndecorateName(mangled, undecorated, 0x1000, 1);
                            Symbol sym;
                            sym.mSegment = section;
                            sym.mOffset = offset;
                            sym.mSymbol.assign(undecorated);
                            sym.mRVA = rva;
                            sym.mSourceObj.assign(obj);
                            InsertResult result;
                            {
                                SymbolPair pair(rva, sym);
                                mAddressToSymbolMap.insert(&result, pair);
                            }
                            if (section < (unsigned)(mSectionArray.mpEnd - mSectionArray.mpBegin))
                                mSectionArray.mpBegin[section] = rva - offset;
                        }
                                            break;
                    }
                    case 1: {
                        Group g;
                        char kind[32];
                        if (sscanf(line.mpBegin, "%x:%x %xH %*s %31s", &g.mSegment, &g.mOffset,
                                   &g.mLength, kind) == 4 &&
                            strcmp(kind, "CODE") == 0) {
                            mGroupArray.push_back(g);
                            if (g.mSegment >= (unsigned)(mSectionArray.mpEnd - mSectionArray.mpBegin)) {
                                unsigned z = 0;
                                mSectionArray.resize(g.mSegment + 1, z);
                            }
                        }
                                            break;
                    }
                    }
                }
            } while (cursor != end);
            if (buffer.mpBegin && ((int*)buffer.mpBegin)[-1])
                operator delete(buffer.mpBegin);
        }
    }
    if (mAddressToSymbolMap.mnSize != 0 && mBaseAddress == 0)
        mBaseAddress = GetModuleBase(0);
    return mAddressToSymbolMap.mnSize != 0;
}
