// EA::Callstack::MapFileMSVC::Load (0x0091ccf0): parses an MSVC linker .map file into the
// section table, segment groups, address->symbol map and address->file/line map.
// Flags: /O2 /MD /Gy /TP /GS-  (no EH frame in the original)
#include "types.h"

extern "C" __declspec(dllimport) int __cdecl sscanf(const char* buffer, const char* format, ...);
extern "C" __declspec(dllimport) void* __cdecl memmove(void* dst, const void* src, unsigned n);
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned n);
extern "C" int __cdecl strcmp(const char* a, const char* b);
#pragma intrinsic(strcmp)

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
    void AddRef();                                            // 0x009317b0
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

// ---- eastl::basic_string<wchar_t, allocator> (3 pointers + allocator).
struct StringW {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    unsigned mAlloc;
    StringW& assign(const wchar_t* first, const wchar_t* last);  // 0x00423650
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
    FixedString* assignCStr(const char* s);                         // 0x00943570
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

// eastl::rbtree_node_base: right, left, parent, colour.
struct RBNodeBase {
    RBNodeBase* mpNodeRight;   // +0x00
    RBNodeBase* mpNodeLeft;    // +0x04
    RBNodeBase* mpNodeParent;  // +0x08
    char mColor;               // +0x0c
};

struct SymbolNode;  // rbtree_node<pair<const unsigned, Symbol>> (0x40 bytes)

struct SymbolMap {  // eastl::map<unsigned, Symbol>
    unsigned mCompareAlloc;   // +0x00 empty comparator/allocator
    RBNodeBase mAnchor;       // +0x04
    unsigned mnSize;          // +0x14
    unsigned mAlloc;          // +0x18
    InsertResult* insert(InsertResult* out, const SymbolPair& v);  // 0x0091cc30
    void DoNukeSubtree(SymbolNode* node);                          // 0x0091ca40
};

struct FileLineEntry {
    String* mpFile;
    int mLine;
};
struct FileLineNode;  // rbtree_node<pair<const unsigned, FileLineEntry>> (0x1c bytes)

struct FileLineMap {  // eastl::map<unsigned, pair<String*, int>>
    unsigned mCompareAlloc;   // +0x00
    RBNodeBase mAnchor;       // +0x04
    unsigned mnSize;          // +0x14
    unsigned mAlloc;          // +0x18
    FileLineEntry& operator[](const unsigned& key);  // 0x0091c9b0
    FileLineEntry& insertNode(RBNodeBase* position, unsigned key,
                              const FileLineEntry& value);  // 0x0091c3c0
    void DoNukeSubtree(FileLineNode* node);          // 0x009a9600 (different instantiation)
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
    void Destroy();                   // 0x0091c380 (eastl::list<String> destructor)
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

// ---- caller-owned destination for a resolved address representation.
//      mFileName/mSymbol are eastl::fixed_string<char, 256> buffers (0x114 each).
struct AddressRepText {
    FixedString mFileName;   // +0x000
    FixedString mSymbol;     // +0x114
};
struct AddressRep {
    unsigned mFileLine;      // +0x00
    unsigned mRVA;           // +0x04
};
// MapFileGCC3's destination record: offset at +0x04, symbol text at +0x114.
struct GccAddressRep {
    unsigned mFlags;         // +0x000
    int mOffset;             // +0x004
    char mReserved[0x10c];   // +0x008 (caller-owned, untouched here)
    FixedString mSymbol;     // +0x114
};

// ---- EA::Callstack::MapFileGCC3::EntryPair
struct EntryPair {
    unsigned __int64 mAddress;   // +0x00
    char* mpSymbol;              // +0x08
};
// ---- eastl::vector<EntryPair, sp_vector_allocator> (0x14 bytes)
struct EntryPairVector {
    EntryPair* mpBegin;      // +0x00
    EntryPair* mpEnd;        // +0x04
    EntryPair* mpCapacity;   // +0x08
    unsigned mAlloc;         // +0x0c
    unsigned mPad;           // +0x10
    void clear();
    EntryPair* insert(EntryPair* pos, const EntryPair& value);  // 0x0091c4d0
};

// ---- EA::Allocator::StackAllocator (0x24 bytes)
struct StackAllocator {
    unsigned mnDefaultBlockSize;      // +0x00
    void* mpCurrentBlock;             // +0x04
    char* mpCurrentBlockEnd;          // +0x08
    char* mpCurrentObjectBegin;       // +0x0c
    char* mpCurrentObjectEnd;         // +0x10
    void* mpCoreAllocationFunction;   // +0x14
    void* mpCoreFreeFunction;         // +0x18
    void* mpCoreFunctionContext;      // +0x1c
    void* mpTopBookmark;              // +0x20
    void Reset(void* p);              // 0x00928c40
    bool AllocateNewBlock(unsigned n);  // 0x00928ba0
    void Destroy();                   // 0x00928dc0
};

struct MapFileGCC3 {
    void* vtable;                     // +0x00
    bool mbLoadAttempted;             // +0x04
    StringW msMapFilePath;            // +0x08
    EntryPairVector mEntryPairArray;  // +0x18
    StackAllocator mStackAllocator;   // +0x2c
    unsigned __int64 mBaseAddress;    // +0x50

    bool Load();                      // 0x0091c640
    int Init(const wchar_t* path, bool deferLoad);  // 0x0091cbd0
    bool Shutdown();                  // 0x0091c8b0
    int GetAddressRep(unsigned flags, unsigned address, GccAddressRep* out,
                      unsigned unused);  // 0x0091c900
    ~MapFileGCC3();                   // 0x0091cb40
};

struct MapFileMSVC {
    void* vtable;                   // +0x00
    bool mbLoadAttempted;           // +0x04
    StringW msMapFilePath;          // +0x08
    unsigned __int64 mBaseAddress;  // +0x18
    SymbolMap mAddressToSymbolMap;  // +0x20
    StringList mLineFilenameList;   // +0x3c
    FileLineMap mAddressToFileLineMap;  // +0x48
    UIntVector mSectionArray;       // +0x64
    GroupVector mGroupArray;        // +0x78

    MapFileMSVC();                  // 0x0091d480
    ~MapFileMSVC();                 // 0x0091cc60
    bool Load();                    // 0x0091ccf0
    int Init(const wchar_t* path, bool deferLoad);  // 0x0091d520
    int GetAddressRep(unsigned flags, unsigned address, AddressRepText* text,
                      AddressRep* out);  // 0x0091d580
};

inline unsigned strlen_(const char* s)
{
    const char* p = s;
    while (*p++)
        ;
    return p - s - 1;
}
}  // namespace

bool MapFileMSVC::Load()
{
    if (!mbLoadAttempted) {
        mbLoadAttempted = true;
        FileStream file(msMapFilePath.mpBegin);
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

// ======================================================================
// gold7 batch additions (slice id s0091c640 is shared with function 0091ccf0)
// ======================================================================

extern wchar_t gEmptyString16;  // 0x01667bac (eastl wide empty-string sentinel)

// Global-scope declarations: the retail symbols are namespace-scope functions, so these must be
// declared at global scope as well (the anonymous namespace would change their mangled names).
unsigned __int64 __cdecl ParseAddress(const char* text, char** rest, unsigned base);  // 0x0092d6f0
unsigned __cdecl AppendNarrow(void* dst, const char* src, unsigned maxLen);          // 0x0092cb30

namespace {

// ---- rbtree node instantiations: the 0x10-byte node base is followed by the
//      key and then the mapped value.
struct SymbolNode : RBNodeBase {
    unsigned mKey;      // +0x10
    Symbol mValue;      // +0x14
};
struct FileLineNode : RBNodeBase {
    unsigned mKey;          // +0x10
    FileLineEntry mValue;   // +0x14
};

// ---- key record used by the EntryPair binary searches
struct EntryPairKey {
    unsigned __int64 mAddress;  // +0x00
    unsigned mPad;              // +0x08
};

// ---- EA::IO::StreamBuffer (0x34 bytes)
struct StreamBuffer {
    StreamBuffer(unsigned readSize, unsigned writeSize, void* stream);  // 0x0093b530
    ~StreamBuffer();                                                    // 0x0093b5a0
    void* vtable;                          // +0x00
    void* mpStream;                        // +0x04
    int mnRefCount;                        // +0x08
    unsigned mnPositionExternal;           // +0x0c
    unsigned mnPositionInternal;           // +0x10
    char* mpReadBuffer;                    // +0x14
    unsigned mnReadBufferSize;             // +0x18
    unsigned mnReadBufferStartPosition;    // +0x1c
    unsigned mnReadBufferUsed;             // +0x20
    char* mpWriteBuffer;                   // +0x24
    unsigned mnWriteBufferSize;            // +0x28
    unsigned mnWriteBufferStartPosition;   // +0x2c
    unsigned mnWriteBufferUsed;            // +0x30
};

unsigned __cdecl ReadLine(void* stream, char* buffer, unsigned size);          // 0x0093a8b0
EntryPair* __cdecl LowerBoundPair(EntryPair* first, EntryPair* last,
                                  const EntryPair* value, unsigned pad);       // 0x007c8160
EntryPair* __cdecl LowerBoundKey(EntryPair* first, EntryPair* last,
                                 const void* key, unsigned pad);               // 0x0091bf30
void* __cdecl MovePairs(const EntryPair* first, const EntryPair* last,
                        EntryPair* dst);                                       // 0x00705250
RBNodeBase* __cdecl RBTreeDecrement(const RBNodeBase* node);                   // 0x009215c0

extern "C" __declspec(dllimport) char* __cdecl strstr(const char* s, const char* find);

// eastl vector/sp-vector buffer release: the allocation flag precedes the block.
inline void FreeVectorBuffer(void* p)
{
    if (p && ((unsigned*)p)[-1] != 0)
        operator delete(p);
}

// eastl::CharStrlen: length of a null-terminated character string.
inline unsigned CharStrlen(const wchar_t* p)
{
    const wchar_t* current = p;
    while (*current)
        ++current;
    return (unsigned)(current - p);
}

void EntryPairVector::clear()
{
    EntryPair* first = mpBegin;
    EntryPair* last = mpEnd;
    MovePairs(last, mpEnd, first);
    mpEnd -= last - first;
}

}  // namespace

// @ 0x0091c8b0
bool MapFileGCC3::Shutdown()
{
    mbLoadAttempted = false;
    mEntryPairArray.clear();
    mStackAllocator.Reset(0);
    mBaseAddress = 0;
    return true;
}

// @ 0x0091c900
int MapFileGCC3::GetAddressRep(unsigned flags, unsigned address, GccAddressRep* out, unsigned)
{
    if (!mbLoadAttempted)
        Load();
    if ((flags & 2) == 0)
        return 0;
    EntryPairKey key;
    key.mAddress = address;
    key.mPad = 0;
    EntryPair* begin = mEntryPairArray.mpBegin;
    EntryPair* it = LowerBoundKey(begin, mEntryPairArray.mpEnd, &key, 0);
    if (it == begin)
        return 0;
    EntryPair* found = it - 1;
    out->mSymbol.assignCStr(found->mpSymbol);
    out->mOffset = (int)(address - (unsigned)found->mAddress);
    return 2;
}

// @ 0x0091c9b0
FileLineEntry& FileLineMap::operator[](const unsigned& key)
{
    RBNodeBase* node = mAnchor.mpNodeParent;
    RBNodeBase* lower = &mAnchor;
    while (node) {
        if (((FileLineNode*)node)->mKey < key) {
            node = node->mpNodeRight;
        } else {
            lower = node;
            node = node->mpNodeLeft;
        }
    }
    if (lower != &mAnchor && key <= ((FileLineNode*)lower)->mKey)
        return ((FileLineNode*)lower)->mValue;
    FileLineEntry value;
    value.mpFile = 0;
    value.mLine = 0;
    return insertNode(lower, key, value);
}

// @ 0x0091ca40
void SymbolMap::DoNukeSubtree(SymbolNode* node)
{
    while (node) {
        DoNukeSubtree((SymbolNode*)node->mpNodeRight);
        SymbolNode* next = (SymbolNode*)node->mpNodeLeft;
        if (node->mValue.mSourceObj.mpCapacity - node->mValue.mSourceObj.mpBegin > 1 &&
            node->mValue.mSourceObj.mpBegin)
            operator delete(node->mValue.mSourceObj.mpBegin);
        if (node->mValue.mSymbol.mpCapacity - node->mValue.mSymbol.mpBegin > 1 &&
            node->mValue.mSymbol.mpBegin)
            operator delete(node->mValue.mSymbol.mpBegin);
        operator delete(node);
        node = next;
    }
}

// @ 0x0091cb40
MapFileGCC3::~MapFileGCC3()
{
    vtable = (void*)0x0143ce60;
    mbLoadAttempted = false;
    mEntryPairArray.clear();
    mStackAllocator.Reset(0);
    mBaseAddress = 0;
    mStackAllocator.Destroy();
    FreeVectorBuffer(mEntryPairArray.mpBegin);
    if ((((int)msMapFilePath.mpCapacity - (int)msMapFilePath.mpBegin) & ~1) > 2 &&
        msMapFilePath.mpBegin)
        operator delete(msMapFilePath.mpBegin);
    vtable = (void*)0x013f68c4;
}

// @ 0x0091cbd0
int MapFileGCC3::Init(const wchar_t* path, bool deferLoad)
{
    if (path)
        msMapFilePath.assign(path, path + CharStrlen(path));
    if (!deferLoad) {
        Load();
        if (mEntryPairArray.mpBegin == mEntryPairArray.mpEnd)
            return 0;
    }
    return 1;
}

// @ 0x0091c640
bool MapFileGCC3::Load()
{
    if (!mbLoadAttempted) {
        mbLoadAttempted = true;
        FileStream file(msMapFilePath.mpBegin);
        if (file.Open(1, 6, 1, 0)) {
            file.AddRef();
            StreamBuffer stream(0x2000, 0, &file);
            char line[0x200];
            char name[0x200];
            bool inText = false;
            unsigned n = ReadLine(&stream, line, sizeof line);
            while (n < 0xfffffffeu) {
                if (line[0] == ' ' && line[1] == '.') {
                    if (strstr(line, " .text") == line || strstr(line, " .gnu.linkonce") == line) {
                        if (line[2] == 'g')
                            ReadLine(&stream, line, sizeof line);
                        inText = true;
                    } else {
                        inText = false;
                    }
                } else if (inText) {
                    char* rest;
                    unsigned __int64 address = ParseAddress(line, &rest, 0x10);
                    while (*rest == ' ')
                        ++rest;
                    unsigned len = AppendNarrow(name, rest, 0x100);
                    if (len >= 0x100)
                        len = 0xff;
                    if (address != 0 && len != 0) {
                        unsigned need = (len + 8) & ~7u;
                        char* p;
                        if ((int)(mStackAllocator.mpCurrentBlockEnd -
                                  mStackAllocator.mpCurrentObjectBegin) - (int)need < 0 &&
                            !mStackAllocator.AllocateNewBlock(need)) {
                            p = 0;
                        } else {
                            p = mStackAllocator.mpCurrentObjectBegin;
                            mStackAllocator.mpCurrentObjectBegin = p + need;
                            mStackAllocator.mpCurrentObjectEnd = p + need;
                        }
                        char* dst = p;
                        const char* src = name;
                        while ((*dst++ = *src++) != 0)
                            ;
                        EntryPair value;
                        value.mAddress = address;
                        value.mpSymbol = p;
                        mEntryPairArray.insert(
                            LowerBoundPair(mEntryPairArray.mpBegin, mEntryPairArray.mpEnd, &value, 0),
                            value);
                    }
                }
                n = ReadLine(&stream, line, sizeof line);
            }
        }
    }
    if (mEntryPairArray.mpBegin != mEntryPairArray.mpEnd && mBaseAddress == 0)
        mBaseAddress = GetModuleBase(0);
    return mEntryPairArray.mpBegin != mEntryPairArray.mpEnd;
}

// @ 0x0091cc60
MapFileMSVC::~MapFileMSVC()
{
    vtable = (void*)0x0143ce8c;
    mbLoadAttempted = false;
    mBaseAddress = 0;
    if (mGroupArray.mpBegin != 0 && ((unsigned*)mGroupArray.mpBegin)[-1] != 0)
        operator delete(mGroupArray.mpBegin);
    FreeVectorBuffer(mSectionArray.mpBegin);
    mAddressToFileLineMap.DoNukeSubtree(
        (FileLineNode*)mAddressToFileLineMap.mAnchor.mpNodeParent);
    mLineFilenameList.Destroy();
    mAddressToSymbolMap.DoNukeSubtree((SymbolNode*)mAddressToSymbolMap.mAnchor.mpNodeParent);
    if ((((int)msMapFilePath.mpCapacity - (int)msMapFilePath.mpBegin) & ~1) > 2 &&
        msMapFilePath.mpBegin)
        operator delete(msMapFilePath.mpBegin);
    vtable = (void*)0x013f68c4;
}

// @ 0x0091d480
MapFileMSVC::MapFileMSVC()
{
    vtable = (void*)0x0143ce8c;
    mbLoadAttempted = false;
    msMapFilePath.mpCapacity = &gEmptyString16 + 1;
    msMapFilePath.mpBegin = &gEmptyString16;
    msMapFilePath.mpEnd = &gEmptyString16;
    mBaseAddress = 0;
    mAddressToSymbolMap.mAnchor.mpNodeRight = &mAddressToSymbolMap.mAnchor;
    mAddressToSymbolMap.mAnchor.mpNodeLeft = &mAddressToSymbolMap.mAnchor;
    mAddressToSymbolMap.mAnchor.mpNodeParent = 0;
    mAddressToSymbolMap.mAnchor.mColor = 0;
    mAddressToSymbolMap.mnSize = 0;
    mLineFilenameList.mpNext = (StringNode*)&mLineFilenameList;
    mLineFilenameList.mpPrev = (StringNode*)&mLineFilenameList;
    mAddressToFileLineMap.mAnchor.mpNodeRight = &mAddressToFileLineMap.mAnchor;
    mAddressToFileLineMap.mAnchor.mpNodeLeft = &mAddressToFileLineMap.mAnchor;
    mAddressToFileLineMap.mAnchor.mpNodeParent = 0;
    mAddressToFileLineMap.mAnchor.mColor = 0;
    mAddressToFileLineMap.mnSize = 0;
    mSectionArray.mpBegin = 0;
    mSectionArray.mpEnd = 0;
    mSectionArray.mpCapacity = 0;
    mGroupArray.mpBegin = 0;
    mGroupArray.mpEnd = 0;
    mGroupArray.mpCapacity = 0;
}

// @ 0x0091d520
int MapFileMSVC::Init(const wchar_t* path, bool deferLoad)
{
    ((void(__thiscall*)(MapFileMSVC*))((void**)vtable)[2])(this);
    if (path)
        msMapFilePath.assign(path, path + CharStrlen(path));
    if (!deferLoad) {
        Load();
        if (mAddressToSymbolMap.mnSize == 0)
            return 0;
    }
    return 1;
}

// @ 0x0091d580
int MapFileMSVC::GetAddressRep(unsigned flags, unsigned address, AddressRepText* text,
                               AddressRep* out)
{
    if (!mbLoadAttempted)
        Load();
    int result = 0;
    if (flags & 1) {
        RBNodeBase* node = mAddressToFileLineMap.mAnchor.mpNodeParent;
        RBNodeBase* lower = &mAddressToFileLineMap.mAnchor;
        while (node) {
            if (address < ((FileLineNode*)node)->mKey) {
                lower = node;
                node = node->mpNodeLeft;
            } else {
                node = node->mpNodeRight;
            }
        }
        if (lower != mAddressToFileLineMap.mAnchor.mpNodeLeft) {
            FileLineNode* found = (FileLineNode*)RBTreeDecrement(lower);
            text->mFileName.assignCStr(found->mValue.mpFile->mpBegin);
            out->mFileLine = found->mValue.mLine;
            result = 1;
        }
    }
    if ((flags & 2) != 0 && (unsigned)(mBaseAddress >> 32) == 0 &&
        (unsigned)mBaseAddress <= address) {
        RBNodeBase* node = mAddressToSymbolMap.mAnchor.mpNodeParent;
        RBNodeBase* lower = &mAddressToSymbolMap.mAnchor;
        while (node) {
            if (address < ((SymbolNode*)node)->mKey) {
                lower = node;
                node = node->mpNodeLeft;
            } else {
                node = node->mpNodeRight;
            }
        }
        if (lower != mAddressToSymbolMap.mAnchor.mpNodeLeft) {
            SymbolNode* found = (SymbolNode*)RBTreeDecrement(lower);
            for (Group* g = mGroupArray.mpBegin; g != mGroupArray.mpEnd; ++g) {
                if (g->mSegment == found->mValue.mSegment &&
                    (unsigned)(found->mValue.mOffset - g->mOffset) < g->mLength) {
                    text->mSymbol.assignCStr(found->mValue.mSymbol.mpBegin);
                    out->mRVA = found->mValue.mRVA;
                    return result | 2;
                }
            }
        }
    }
    return result;
}
