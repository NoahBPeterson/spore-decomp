// Slice s008d5340: EA::Input::TriggerConfigParser::Parse (008d5340).
// Parses the input trigger config text: "[platform,...]" sections, "#define NAME value",
// "(a, b) = value" combos and "MOD+KEY = value" bindings. Layouts from the 2008 dev PDB.
#include "types.h"
#include <new>
#include <string.h>

extern "C" {
__declspec(dllimport) int __cdecl isalnum(int);
__declspec(dllimport) int __cdecl toupper(int);
__declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
}

typedef unsigned int uint;

void EASTL_allocator_deallocate(void* p);                             // 0x00f47380 (operator delete[])

namespace eastl {

class allocator { public:};
int CompareI(const char* a, const char* b, unsigned n);               // 0x00606ea0 (cdecl)

template <class T> inline const T& min_alt(const T& a, const T& b) { return (b < a) ? b : a; }

extern char gEmptyString[];                                           // 0x01667bac

inline int CharStrlen(const char* p) { return (int)strlen(p); }

struct string {                                                       // eastl::basic_string<char>, 16 bytes
    typedef char T;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;

    string()
    {
        mpBegin = gEmptyString;
        mpEnd = gEmptyString;
        mpCapacity = gEmptyString + 1;
    }
    ~string()
    {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            EASTL_allocator_deallocate(mpBegin);
    }
    __forceinline int comparei(const T* p) const
    {
        const T* pBegin2 = p;
        const T* pEnd2 = p + CharStrlen(p);
        const int n1 = (int)(mpEnd - mpBegin);
        const int n2 = (int)(pEnd2 - pBegin2);
        const int nMin = min_alt(n1, n2);
        const int cmp = CompareI(mpBegin, pBegin2, (unsigned)nMin);
        return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
    }
    string& insert(int position, const T* p);                       // 0x0068cd40 (thiscall)
};

bool operator==(const string& a, const char* b);                      // 0x00555020 (cdecl)

}  // namespace eastl


// eastl::sp_vector_allocator vector of unsigned (SP::SimpleVector style); the dtor frees only
// blocks whose header word is nonzero.
struct UIntVector {
    uint* mpBegin;
    uint* mpEnd;
    uint* mpCapacity;
    eastl::allocator mAllocator;

    UIntVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~UIntVector()
    {
        if (mpBegin) {
            if (((int*)mpBegin)[-1] != 0)
                EASTL_allocator_deallocate(mpBegin);
        }
    }
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    void DoInsertValue(uint* position, const uint& value);           // 0x004558a0
    void push_back(const uint& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) uint(value);
        else
            DoInsertValue(mpEnd, value);
    }
    __forceinline uint* erase(uint* first, uint* last)
    {
        memcpy(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    __forceinline void clear() { erase(mpBegin, mpEnd); }
};

namespace EA { namespace Input {

enum Token { TokenNone = 0, TokenLineBreak = 1, TokenIdent = 2, TokenInteger = 3, TokenPunc = 4 };

struct CharStream {                                                   // 0x20 bytes
    const char* mScanPos;
    const char* mScanEnd;
    const char* mLineBegin;
    int mCurrentLine;
    eastl::string mMatchText;                                         // +0x10

    CharStream(const char* pBegin, const char* pEnd)
    {
        if (pEnd == 0)
            pEnd = pBegin + eastl::CharStrlen(pBegin);
        mScanEnd = pEnd;
        mScanPos = pBegin;
        mLineBegin = pBegin;
        mCurrentLine = 1;
    }
    void SkipLine();                                                  // 0x008950b0
};

class TriggerTokenReader : public CharStream { public:                              // 0x30 bytes
    int mResult;                                                      // +0x20
    int mToken;                                                       // +0x24
    uint mTokenValue;                                                 // +0x28
    int mTokenLine;                                                   // +0x2c

    TriggerTokenReader(const char* pBegin, const char* pEnd) : CharStream(pBegin, pEnd) { mResult = 0; }
    void Advance();                                                   // 0x008d4ef0
    bool MatchPunc(char c);                                           // 0x008d5160
    bool MatchString();                                               // 0x008d52f0
};

struct KeyDef {
    const char* name;
    uint value;
};
struct KeyRange {
    const KeyDef* first;
    const KeyDef* second;
    KeyRange() {}
};

extern KeyDef gNumpadNames[18];                                       // 0x0154c360
extern KeyDef gModifierNames[10];                                     // 0x0154c3f0
extern KeyDef gKeyNames[235];                                         // 0x0154bc08

KeyRange FindKeyDefs(const KeyDef* first, const KeyDef* last, const char* const& name);  // 0x008d4b90
bool LookupNumpadName(const KeyDef* table, const char* name, uint* pOut);                // 0x008d4cd0
bool LookupKeyName(const KeyDef* table, const char* name, uint* pOut);                   // 0x008d4d20

struct Binding {                                                      // 16 bytes
    uint key;
    uint value;
    uint16_t modLo;
    uint16_t modHi;
    uint link;
};

class TriggerMap { public:
    void AddCombo(uint value, const uint* keys, uint count);          // 0x008d4920
    void AddBinding(const Binding& b);                                // 0x008d48d0
    Binding* FindByValue(uint value);                                 // 0x008d3ae0
};

struct HashNode;                                                      // eastl::hash_node<pair<const string,uint>, 0>
extern HashNode* gEmptyBucketArray[1];                                // 0x0154df28 (eastl's static empty bucket array)

// eastl::hash_map<eastl::string, uint> = hashtable<...>, 0x20 bytes (dev PDB layout).
struct SymbolMap {
    uint mBase00;                                                     // +0x00 (empty-base padding, never written)
    HashNode** mpBucketArray;                                         // +0x04
    uint mnBucketCount;                                               // +0x08
    uint mnElementCount;                                              // +0x0c
    float mfMaxLoadFactor;                                            // +0x10
    float mfGrowthFactor;                                             // +0x14
    uint mnNextResize;                                                // +0x18
    uint mAllocator;                                                  // +0x1c (empty eastl::allocator)

    uint& operator[](const eastl::string& key);                       // 0x006a8340
    void DoFreeNodes(HashNode** pBuckets, uint nBucketCount);         // 0x006a85b0 (HTable::DoFreeNodes)
    void clear() { DoFreeNodes(mpBucketArray, mnBucketCount); mnElementCount = 0; }
    ~SymbolMap() { clear(); if (mnBucketCount > 1) EASTL_allocator_deallocate(mpBucketArray); }
};

// esi = platform name in the original (register convention)
static const char* GetAbbreviatedPlatformName(const char* platform)  // 0x008d4a10
{
    if (_stricmp(platform, "XBox") == 0) return "xb";
    if (_stricmp(platform, "Xenon") == 0) return "xe";
    if (_stricmp(platform, "PS2") == 0) return "ps2";
    if (_stricmp(platform, "PS3") == 0) return "ps3";
    if (_stricmp(platform, "GameCube") == 0) return "gc";
    return _stricmp(platform, "Windows") == 0 ? "win32" : "";
}

class TriggerConfigParser { public:                                          // 0x40 bytes
    TriggerMap* mpTriggerMap;     // +0x0
    TriggerConfigParser* mpParent;// +0x4
    char* mpPlatformName;         // +0x8
    int mLineCount;               // +0xc
    int mEntryCount;              // +0x10
    uint mToken;                  // +0x14
    uint mTokenValue;             // +0x18
    SymbolMap mSymbols;           // +0x1c (hash_map, 0x20 bytes)
    bool mSkip;                   // +0x3c

    bool LookupSymbol(const eastl::string& name, uint* pOut);         // 0x008d4d70
    bool Parse(const char* pBegin, const char* pEnd);                 // 0x008d5340
};

bool TriggerConfigParser::Parse(const char* pBegin, const char* pEnd)
{
    TriggerTokenReader reader(pBegin, pEnd);
    bool bEnabled = true;
    bool bGroup = false;
    UIntVector group;

    reader.Advance();
    if (reader.mScanPos < reader.mScanEnd) {
      do {
        uint key = 0;
        uint value = 0;
        uint modLo = 0;
        uint modHi = 0;
        mLineCount = reader.mTokenLine;

        if (reader.mToken == TokenLineBreak) {
            reader.Advance();
            continue;
        }
        if (reader.mToken == TokenPunc) {
            if (reader.mTokenValue == '[') {
                reader.Advance();
                if (reader.mToken == TokenIdent) {
                    bool bMatch = false;
                    for (;;) {
                        if (reader.mMatchText.comparei(mpPlatformName) == 0 ||
                            reader.mMatchText == GetAbbreviatedPlatformName(mpPlatformName) ||
                            reader.mMatchText == "all")
                            bMatch = true;
                        reader.Advance();
                        if (reader.mToken != TokenPunc)
                            return false;
                        if (reader.mTokenValue == ',') {
                            reader.Advance();
                            if (reader.mToken == TokenIdent)
                                continue;
                            if (reader.mToken != TokenPunc)
                                return false;
                        }
                        break;
                    }
                    if (reader.mTokenValue != ']')
                        return false;
                    reader.Advance();
                    if (reader.mToken != TokenLineBreak)
                        return false;
                    reader.Advance();
                    bEnabled = bMatch;
                    continue;
                }
                key = 0xdb;
            } else if (reader.mTokenValue == '#') {
                reader.Advance();
                key = reader.mTokenValue;
                if (reader.mToken == TokenIdent && reader.mMatchText == "define") {
                    reader.Advance();
                    if (reader.mToken != TokenIdent)
                        return false;
                    uint& slot = mSymbols[reader.mMatchText];
                    reader.Advance();
                    if (reader.mToken == TokenInteger) {
                        slot = reader.mTokenValue;
                    } else if (reader.mToken == TokenIdent) {
                        if (!LookupSymbol(reader.mMatchText, &slot))
                            return false;
                    } else {
                        if (!reader.MatchPunc('"') || !reader.MatchString())
                            return false;
                        slot = reader.mTokenValue;
                    }
                    reader.Advance();
                    if (reader.mToken != TokenLineBreak)
                        return false;
                    reader.Advance();
                    continue;
                }
            }
        }

        if (!bEnabled) {
            reader.SkipLine();
            reader.Advance();
            continue;
        }

        if (reader.mToken == TokenPunc && reader.mTokenValue == '(') {
            reader.Advance();
            key = reader.mTokenValue;
            for (;;) {
                if (reader.mToken == TokenInteger || reader.mToken == TokenIdent) {
                    bGroup = true;
                    uint v = 0;
                    if (reader.mToken == TokenInteger)
                        v = reader.mTokenValue;
                    else if (reader.mToken == TokenIdent) {
                        if (!LookupSymbol(reader.mMatchText, &v))
                            return false;
                    }
                    group.push_back(v);
                    if (group.size() > 4)
                        return false;
                    reader.Advance();
                    if (reader.mToken != TokenPunc)
                        return false;
                    if (reader.mTokenValue == ',') {
                        reader.Advance();
                        continue;
                    }
                } else if (!bGroup) {
                    break;
                } else if (reader.mToken != TokenPunc) {
                    return false;
                }
                if (reader.mTokenValue != ')')
                    return false;
                reader.Advance();
                break;
            }
        }

        if (key == 0 && !bGroup) {
            while (reader.mToken == TokenIdent) {
                const char* name = reader.mMatchText.mpBegin;
                KeyRange r = FindKeyDefs(gModifierNames, gModifierNames + 10, name);
                if (r.first + 1 == r.second) {
                    uint v = r.first->value;
                    reader.Advance();
                    if (v != 0) {
                        modLo |= v;
                        modHi |= v >> 16;
                        continue;
                    }
                    if (reader.mToken != TokenIdent)
                        break;
                }
                if (reader.mMatchText == "numpad") {
                    reader.Advance();
                    if (!LookupNumpadName(gNumpadNames, reader.mMatchText.mpBegin, &key))
                        return false;
                    goto have_key;
                }
                break;
            }
            if (reader.mMatchText.mpEnd - reader.mMatchText.mpBegin == 1 &&
                isalnum((unsigned char)*reader.mMatchText.mpBegin)) {
                key = toupper((unsigned char)*reader.mMatchText.mpBegin);
                goto have_key;
            }
            if (reader.mToken == TokenInteger) {
                key = reader.mTokenValue;
                goto have_key;
            }
            if (reader.mToken == TokenIdent || reader.mToken == TokenPunc) {
                if (!LookupSymbol(reader.mMatchText, &key) &&
                    !LookupKeyName(gKeyNames, reader.mMatchText.mpBegin, &key)) {
                    reader.mMatchText.insert(0, "_");
                    reader.mMatchText.insert(0, GetAbbreviatedPlatformName(mpPlatformName));
                    if (!LookupKeyName(gKeyNames, reader.mMatchText.mpBegin, &key))
                        return false;
                }
                goto have_key;
            }
            goto key_check;
        have_key:
            reader.Advance();
        key_check:
            if (key == 0)
                return false;
        }

        if (!(reader.mToken == TokenPunc && reader.mTokenValue == '='))
            return false;
        reader.Advance();
        if (reader.mToken == TokenPunc && reader.mTokenValue == '-') {
            reader.Advance();
            modLo |= 0x800;
        }
        if (reader.mToken == TokenInteger) {
            value = reader.mTokenValue;
            reader.Advance();
        } else if (reader.mToken == TokenIdent) {
            if (!LookupSymbol(reader.mMatchText, &value))
                return false;
            reader.Advance();
        } else if (reader.mToken == TokenPunc && reader.mTokenValue == '"') {
            reader.Advance();
            if (!reader.MatchString())
                return false;
            value = reader.mTokenValue;
        } else {
            return false;
        }

        if (bGroup) {
            uint count = group.size();
            mpTriggerMap->AddCombo(value, group.mpBegin, count);
            for (uint* p = group.mpBegin; p != group.mpEnd; ++p) {
                Binding* b = mpTriggerMap->FindByValue(*p);
                if (!b)
                    return false;
                b->link = value;
            }
            bGroup = false;
            group.clear();
        } else {
            Binding b;
            b.key = key;
            b.value = value;
            b.modLo = (uint16_t)modLo;
            b.modHi = (uint16_t)modHi;
            b.link = 0;
            mpTriggerMap->AddBinding(b);
            ++mEntryCount;
        }
        if (reader.mToken != TokenLineBreak)
            return false;
        reader.Advance();
      } while (reader.mScanPos < reader.mScanEnd);
    }
    return true;
}

// Parses a trigger config blob into pTriggerMap for one platform, then reports how many
// bindings were stored. The stack parser is built in place; its symbol map points at eastl's
// static empty bucket array and is torn down (DoFreeNodes + bucket free) at scope exit.
// @ 0x008D5C50
int ParseTriggerConfigText(TriggerMap* pTriggerMap, const char* pBegin, const char* pEnd, char* pPlatformName)
{
    TriggerConfigParser parser;
    parser.mpTriggerMap = pTriggerMap;
    parser.mpParent = 0;
    parser.mpPlatformName = pPlatformName;
    parser.mLineCount = 0;
    parser.mEntryCount = 0;
    parser.mToken = 0;
    parser.mTokenValue = 0;
    parser.mSymbols.mfMaxLoadFactor = 1.0f;
    parser.mSymbols.mfGrowthFactor = 2.0f;
    parser.mSymbols.mnBucketCount = 1;
    parser.mSymbols.mpBucketArray = gEmptyBucketArray;
    parser.mSymbols.mnElementCount = 0;
    parser.mSymbols.mnNextResize = 0;
    parser.mSkip = false;

    parser.Parse(pBegin, pEnd);
    return parser.mEntryCount;
}

}}  // namespace EA::Input


// ===========================================================================
// 0x008D5D70 .. 0x008D6290: EA::ResourceMan::DatabaseDirectoryFiles (same class
// and layout as slice s008d62f0) plus the refcounted background record loader
// whose stream/key live next to it. Names are reconstruction-side; layouts are
// from the 2008 dev PDB and checked against the retail disassembly.
// ===========================================================================

extern "C" {
__declspec(dllimport) int __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);
__declspec(dllimport) unsigned long __cdecl wcstoul(const wchar_t* s, wchar_t** pEnd, int radix);
long __cdecl _InterlockedExchangeAdd(volatile long* pAddend, long nValue);
long __cdecl _InterlockedExchange(volatile long* pTarget, long nValue);
long __cdecl _InterlockedDecrement(volatile long* pAddend);
}
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedDecrement)

void* RBTreeIncrement(void* pNode);                                   // 0x00921580
void  ZoneObjectDelete(void* pObject);                                // 0x00926060

// Table of the object's primary interface (vptr at +0x00).
inline void** VtableOf(void* pObject) { return *reinterpret_cast<void***>(pObject); }

// 0x0154c464: global hook used when a record has no file-name-to-key converter.
extern "C" char (*g_154c464)(void* pOut, void* pArg2, void* pArg3, unsigned int nGroupId, void* pArg5, int nArg6);

namespace EA { namespace Thread {

class Mutex {
public:
    int Lock(void* pCaller);                                          // 0x009221b0
    int Unlock();                                                     // 0x00922270
private:
    unsigned int mImpl[0x2c / 4];                                     // 0x00
};

}}

namespace EA { namespace IO {

class FilePath {
public:
    FilePath(const wchar_t* pPath);                                   // 0x00930f60
    wchar_t* GetExtension();                                          // 0x00930c10
    unsigned int GetDirectory(wchar_t* pDirectory, unsigned int nLength);  // 0x00930c30
private:
    wchar_t mPath[520];                                               // +0x000
};

bool DirectoryExists(const wchar_t* pPath);                           // 0x009322b0
bool DirectoryCreatePath(const wchar_t* pPath);                       // 0x00932960
bool DirectoryRemoveRecursive(const wchar_t* pPath, bool bRecursive); // 0x00932890

class FileStream {
public:
    void Construct(const char* pPath);                                // 0x00931da0 (in-place FileStream construction)
    ~FileStream();                                                    // 0x00931e70
    void* mpVtbl;                                                     // +0x00
};

}}

namespace EA { namespace ResourceMan {

struct Key {
    unsigned int mnTypeID;        // +0x00
    unsigned int mnGroupID;       // +0x04
    unsigned int mnInstanceID;    // +0x08
};

struct String16 {
    const wchar_t* mpBegin;       // +0x00
    const wchar_t* mpEnd;         // +0x04
    const wchar_t* mpCapacity;    // +0x08
};

struct RBNode {
    RBNode* mpLeft;               // +0x00
    RBNode* mpRight;              // +0x04
    RBNode* mpParent;             // +0x08
    unsigned int mnColor;         // +0x0c
    // payload follows
};

struct RBTree {
    void* mpAllocator;            // +0x00
    RBNode* mpAnchor;             // +0x04 self-referential header node
    RBNode* mpBegin;              // +0x08 left-most node
    RBNode* mpRoot;               // +0x0c
    unsigned int mnUnknown10;     // +0x10
    unsigned int mnCount;         // +0x14
    void* mpAllocIface;           // +0x18
    unsigned int mnAllocName;     // +0x1c
};

inline RBNode* TreeAnchor(RBTree* pTree) { return reinterpret_cast<RBNode*>(reinterpret_cast<char*>(pTree) + 4); }
inline String16* NodeExtKey(RBNode* pNode) { return reinterpret_cast<String16*>(reinterpret_cast<char*>(pNode) + 0x10); }
inline unsigned int* NodeExtValue(RBNode* pNode) { return reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(pNode) + 0x20); }

// Small result record filled in by the record open routine.
struct RecordOpenResult {
    unsigned int mStatus;         // +0x00
    int          mHandle;         // +0x04
    unsigned int mGroupId;        // +0x08
};

// Converts a (key, name, context) triple into a record key; overrides the g_154c464 hook.
typedef bool (__cdecl* FileNameToKeyFn)(void* pKey, void* pName, void* pContext, RecordOpenResult* pResult);

class DatabaseDirectoryFiles {
public:
    bool FUN_008d5d80();                                              // 0x008d5d80
    void* Cast(unsigned int nInterfaceId);                            // 0x008d5da0
    void SetMutexLocked(bool bLock);                                  // 0x008d5de0
    bool OpenRecord(void* pKey, void* pName, void* pContext, RecordOpenResult* pResult);  // 0x008d5e10
    bool OpenRecordFromPath(const wchar_t* pPath, void* pResult);     // 0x008d5ea0
    bool SetLocation(unsigned int nFlags, int nType);                 // 0x008d5fe0
    int  GetTypeByExtension(const wchar_t* pExtension);               // 0x008d61e0
    const wchar_t* GetExtensionByType(unsigned int nType);            // 0x008d6290

    // ---- retail layout (0x168 bytes, two vtable pointers) ----
    void*  mpVtbl0;                    // 0x000
    void*  mpVtbl1;                    // 0x004
    int    mnRefCount;                 // 0x008
    bool   mbInitialized;              // 0x00c
    unsigned char mPad0d[3];           // 0x00d

    void*  mpAllocator;                // 0x010
    bool   mbRequireDirectoryExists;   // 0x014
    bool   mbRecursive;                // 0x015
    unsigned char mPad16[2];           // 0x016

    unsigned int mnAccessFlags;        // 0x018
    String16 msDirectory;              // 0x01c
    unsigned int mDirectoryAllocator;  // 0x028

    unsigned char mExtensionPool[0x20];// 0x02c
    unsigned char mRecordPool[0x20];   // 0x04c

    RBTree mExtensionToTypeMap;        // 0x06c
    RBTree mRecordDataMap;             // 0x08c

    unsigned int mDefaultGroupId;      // 0x0ac
    void*  mpManager;                  // 0x0b0
    FileNameToKeyFn mpFileNameToKeyConverter;  // 0x0b4

    unsigned int mKnownTypesBits[0x20];// 0x0b8

    EA::Thread::Mutex mMutex;          // 0x138
};

// A record stream handle the directory hands out; its interface slot 9 (+0x24) is
// reached through an adjustor thunk from the +8 subobject.
class StreamInterface {
public:
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c();
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();
    virtual void* v1c();
    virtual void* v20();
    virtual void* v24();
};

}}

// An intrusive list whose head node sits at +0x18 of its owner; each node carries the
// item at +0x08.
struct ListItemNode {
    ListItemNode* mpNext;         // +0x00
    ListItemNode* mpPrev;         // +0x04
    void* mpItem;                 // +0x08
};

struct ListOwner {
    unsigned char mPad00[0x18];
    ListItemNode mList;           // +0x18 (head/anchor node)
};

namespace EA { namespace ResourceMan {

// Adjustor thunk of the +8 subobject: forwards interface slot 9 (+0x24) to the primary object.
// @ 0x008D5D70
void* __fastcall FUN_008d5d70(void* pSubObject, void* /*unused*/)
{
    StreamInterface* pPrimary = reinterpret_cast<StreamInterface*>(static_cast<char*>(pSubObject) - 8);
    return pPrimary->v24();
}

// The directory's primary interface, slots 0x00..0x1c.
struct DirectoryCloseInterface {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();       // +0x1c
};

// Clears the initialized flag and lets the object's own slot 0x1c close it down.
// @ 0x008D5D80
bool DatabaseDirectoryFiles::FUN_008d5d80()
{
    if (mbInitialized) {
        mbInitialized = false;
        reinterpret_cast<DirectoryCloseInterface*>(this)->v1c();
    }
    return true;
}

// Interface query: 0x0226a1de is the +0x04 subobject, 0xee3f516e this object.
// @ 0x008D5DA0
void* DatabaseDirectoryFiles::Cast(unsigned int nInterfaceId)
{
    if (nInterfaceId == 0x0226a1de)
        return reinterpret_cast<char*>(this) - 4;
    if (nInterfaceId != 0xee3f516e)
        return 0;
    char* pBlock = reinterpret_cast<char*>(this) - 4;   // 4 (the subobject size) is the null pointer here
    return pBlock ? static_cast<void*>(this) : 0;
}

// @ 0x008D5DE0
void DatabaseDirectoryFiles::SetMutexLocked(bool bLock)
{
    if (bLock)
        mMutex.Lock(reinterpret_cast<void*>(0x01436624));
    else
        mMutex.Unlock();
}

// Turns a (key, name, context) triple into a stream handle through the file-name-to-key
// converter, or through the global hook plus the object's own slot 0x5c.
// @ 0x008D5E10
bool DatabaseDirectoryFiles::OpenRecord(void* pKey, void* pName, void* pContext, RecordOpenResult* pResult)
{
    if (mpFileNameToKeyConverter) {
        pResult->mGroupId = mDefaultGroupId;
        return mpFileNameToKeyConverter(pKey, pName, pContext, pResult);
    }
    if (!g_154c464(pResult, pContext, 0, mDefaultGroupId, 0, 0))
        return false;
    int nHandle = reinterpret_cast<int (__thiscall*)(void*, void*)>(VtableOf(this)[0x5c / 4])(this, pName);
    if (nHandle != -1)
        pResult->mHandle = nHandle;
    return true;
}

// Splits the path into directory and extension and opens the record through them.
// @ 0x008D5EA0
bool DatabaseDirectoryFiles::OpenRecordFromPath(const wchar_t* pPath, void* pResult)
{
    EA::IO::FilePath filePath(pPath);
    wchar_t* pExtension = filePath.GetExtension();
    wchar_t sDirectory[0x104];
    filePath.GetDirectory(sDirectory, 0x100);
    return OpenRecord(sDirectory, pExtension, const_cast<wchar_t*>(pPath), static_cast<RecordOpenResult*>(pResult));
}

// Makes the directory match the requested access flags/type (create, keep or recreate it),
// then publishes the new flag value.
// @ 0x008D5FE0
bool DatabaseDirectoryFiles::SetLocation(unsigned int nFlags, int nType)
{
    if (!mbInitialized)
        return false;
    if (nType == 6)
        nType = ((nFlags & 2) != 0) ? 4 : 3;
    if ((nFlags & 2) == 0 && nType != 3)
        return false;

    bool bExists = EA::IO::DirectoryExists(msDirectory.mpBegin);
    switch (nType) {
    case 1:
        if (bExists)
            return false;
        if (!EA::IO::DirectoryCreatePath(msDirectory.mpBegin))
            return false;
        break;
    case 2:
    case 4:
        if (!bExists && !EA::IO::DirectoryCreatePath(msDirectory.mpBegin))
            return false;
        break;
    case 3:
        if (!bExists)
            return false;
        break;
    case 5:
        if (!bExists)
            return false;
        if (!EA::IO::DirectoryRemoveRecursive(msDirectory.mpBegin, true))
            return false;
        if (!EA::IO::DirectoryCreatePath(msDirectory.mpBegin))
            return false;
        break;
    default:
        return false;
    }

    bool bOk = mbRequireDirectoryExists ? EA::IO::DirectoryExists(msDirectory.mpBegin) : true;
    if (nFlags == 0 || !bOk)
        return false;
    if (mnAccessFlags != 0 && mnAccessFlags != nFlags)
        return false;
    mnAccessFlags = nFlags;
    reinterpret_cast<void (__thiscall*)(void*, unsigned int)>(VtableOf(this)[0x58 / 4])(this, 0);
    return true;
}

// Type id for an extension: a leading '.' is skipped, then the extension tree is searched
// case-insensitively before the extension is read as a hex type id.
// @ 0x008D61E0
int DatabaseDirectoryFiles::GetTypeByExtension(const wchar_t* pExtension)
{
    mMutex.Lock(reinterpret_cast<void*>(0x01436624));
    if (*pExtension == L'.')
        ++pExtension;

    RBNode* pEnd = TreeAnchor(&mExtensionToTypeMap);
    for (RBNode* pNode = mExtensionToTypeMap.mpBegin; pNode != pEnd;
         pNode = static_cast<RBNode*>(RBTreeIncrement(pNode))) {
        if (_wcsicmp(NodeExtKey(pNode)->mpBegin, pExtension) == 0) {
            int nType = static_cast<int>(*NodeExtValue(pNode));
            mMutex.Unlock();
            return nType;
        }
    }

    wchar_t* pEndChars;
    unsigned long nType = wcstoul(pExtension, &pEndChars, 16);
    if (*pEndChars != 0) {
        mMutex.Unlock();
        return -1;
    }
    mMutex.Unlock();
    return static_cast<int>(nType);
}

// First extension mapped to nType, or null.
// @ 0x008D6290
const wchar_t* DatabaseDirectoryFiles::GetExtensionByType(unsigned int nType)
{
    EA::Thread::Mutex* pMutex = &mMutex;
    pMutex->Lock(reinterpret_cast<void*>(0x01436624));

    RBNode* pEnd = TreeAnchor(&mExtensionToTypeMap);
    for (RBNode* pNode = mExtensionToTypeMap.mpBegin; pNode != pEnd;
         pNode = static_cast<RBNode*>(RBTreeIncrement(pNode))) {
        if (*NodeExtValue(pNode) == nType) {
            const wchar_t* pExtension = NodeExtKey(pNode)->mpBegin;
            pMutex->Unlock();
            return pExtension;
        }
    }
    pMutex->Unlock();
    return 0;
}

}}

// Interface of a listed item: slot 0x18 hands out its status object.
struct ListItemInterface {
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c();
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();      // +0x18
};

// Interface of that status object: slot 0x10 is the flag word.
struct ListItemStatusInterface {
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c();
    virtual unsigned int v10();  // +0x10
};

// ORs slot 0x10 of the object returned by slot 0x18 of every item in the owner's list.
// @ 0x008D61A0
unsigned int __stdcall FUN_008d61a0(ListOwner* pOwner)
{
    unsigned int nFlags = 0;
    ListItemNode* pEnd = &pOwner->mList;
    for (ListItemNode* pNode = pOwner->mList.mpNext; pNode != pEnd; pNode = pNode->mpNext) {
        void* pStatus = static_cast<ListItemInterface*>(pNode->mpItem)->v18();
        nFlags |= static_cast<ListItemStatusInterface*>(pStatus)->v10();
    }
    return nFlags;
}

// ---------------------------------------------------------------------------
// Refcounted background record load: vtable at +0x00, refcount at +0x04, its own
// EA::IO::FileStream at +0x08 (vptr at +0x08), the record key at +0x234, the
// owning object at +0x240 and the lifetime count at +0x244.
// ---------------------------------------------------------------------------

extern void* gVtblResource;                                            // 0x013effa8
extern void* gVtbl140944c;                                             // 0x0140944c
extern void* gVtbl14366c8;                                             // 0x014366c8
extern void* gVtbl1436678;                                             // 0x01436678
extern void* gVtbl13effb8;                                             // 0x013effb8

class BackgroundRecordLoad {
public:
    void* Initialize(void* pOwner, const EA::ResourceMan::Key* pKey);  // 0x008d60d0
    void* Destroy(unsigned int nFlags);                                // 0x008d6140
    bool  AddRef();                                                    // 0x008d5f70
    bool  Release();                                                   // 0x008d5fa0

    void* mpVtbl;                          // +0x000
    volatile long mnBusy04;                // +0x004
    EA::IO::FileStream mStream;            // +0x008
    unsigned char mStreamTail[0x234 - 0x008 - sizeof(EA::IO::FileStream)];
    EA::ResourceMan::Key mKey;             // +0x234
    void* mpOwner;                         // +0x240
    volatile long mnRefCount;              // +0x244
};

// Builds the load in place: resource vtable, stream vtable at +0x08, the key and owner.
// @ 0x008D60D0
void* BackgroundRecordLoad::Initialize(void* pOwner, const EA::ResourceMan::Key* pKey)
{
    mpVtbl = &gVtblResource;
    _InterlockedExchange(&mnBusy04, 0);
    mpVtbl = &gVtbl140944c;
    mStream.Construct(0);
    mpVtbl = &gVtbl14366c8;
    mStream.mpVtbl = &gVtbl1436678;
    mKey = *pKey;
    mpOwner = pOwner;
    _InterlockedExchange(&mnRefCount, 0);
    return this;
}

// Tears the load down: releases the owner's reference, destroys the stream and, for a
// scalar delete, frees the block.
// @ 0x008D6140
void* BackgroundRecordLoad::Destroy(unsigned int nFlags)
{
    mpVtbl = &gVtbl14366c8;
    mStream.mpVtbl = &gVtbl1436678;
    if (_InterlockedExchangeAdd(&mnRefCount, 0) != 0) {
        void* pOwner = mpOwner;
        reinterpret_cast<void (__thiscall*)(void*, void*)>(VtableOf(pOwner)[0x3c / 4])(pOwner, this);
    }
    mStream.~FileStream();
    mpVtbl = &gVtbl13effb8;
    if (nFlags & 1)
        ZoneObjectDelete(this);
    return this;
}

// Adds a reference only while the count is nonzero (a zero count means "being torn down").
// @ 0x008D5F70
bool BackgroundRecordLoad::AddRef()
{
    if (_InterlockedExchangeAdd(&mnRefCount, 0) == 0)
        return false;
    _InterlockedExchangeAdd(&mnRefCount, 1);
    return true;
}

// Drops a reference; the last one hands the object back to its owner's slot 0x3c.
// @ 0x008D5FA0
bool BackgroundRecordLoad::Release()
{
    if (_InterlockedExchangeAdd(&mnRefCount, 0) == 0)
        return false;
    if (_InterlockedDecrement(&mnRefCount) == 0) {
        void* pOwner = mpOwner;
        return reinterpret_cast<bool (__thiscall*)(void*, void*)>(VtableOf(pOwner)[0x3c / 4])(pOwner, this);
    }
    return true;
}
