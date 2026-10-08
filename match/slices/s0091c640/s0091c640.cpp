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
    char pad0[0x14];
    unsigned mnSize;
    char pad1[4];
    InsertResult* insert(InsertResult* out, const SymbolPair& v);  // 0x0091cc30
};

struct FileLineEntry {
    String* mpFile;
    int mLine;
};
struct FileLineMap {  // eastl::map<unsigned, pair<String*, int>>
    char pad[0x1c];
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
