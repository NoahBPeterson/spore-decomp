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

struct allocator {};
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

struct TriggerTokenReader : CharStream {                              // 0x30 bytes
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

struct TriggerMap {
    void AddCombo(uint value, const uint* keys, uint count);          // 0x008d4920
    void AddBinding(const Binding& b);                                // 0x008d48d0
    Binding* FindByValue(uint value);                                 // 0x008d3ae0
};

struct SymbolMap {
    char mData[0x20];
    uint& operator[](const eastl::string& key);                       // 0x006a8340
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

struct TriggerConfigParser {                                          // 0x40 bytes
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

}}  // namespace EA::Input
