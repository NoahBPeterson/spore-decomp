// src/game/UTFSpore_Win32/TriggerConfig.cpp -- migrated from slice(s) s008d4520, s008d5340 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/TriggerConfig.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __cdecl isalnum(int);
extern "C" __declspec(dllimport) int __cdecl toupper(int);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
#include <new>
#include <string.h>
#include <intrin.h>


// ---- items of slice s008d4520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int  tolower(int c);
extern "C" __declspec(dllimport) int  isprint(int c);
extern "C" __declspec(dllimport) unsigned long strtoul(const char* s, char** end, int base);
extern char g_142ef10[];
extern char g_142ef0c[];
extern char g_142ef08[];
extern char g_14365d8[];
extern char g_14365d4[];
extern char g_1667a80[];
typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned int uint32;
typedef int int32;
struct VAlloc {
    virtual void* slot0();                                   // vtable +0x00
    virtual void* slot4();                                   // vtable +0x04
    virtual void* allocate(unsigned n, int a, void* name);   // vtable +0x08
    virtual void  deallocate(void* p, unsigned n);           // vtable +0x0c
};
struct EaString {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    char  mBuffer[8];   // +0x0c

    void push_back(char c);   // 0x005306c0 (__thiscall)
};
struct TokenReader {
    char*     scanPos;      // 0x00
    char*     scanEnd;      // 0x04
    char*     lineBegin;    // 0x08
    uint32    currentLine;  // 0x0c
    EaString  matchText;    // 0x10
    uint32    mToken;       // 0x24
    int32     mTokenValue;  // 0x28
    uint32    mTokenLine;   // 0x2c

    uint8 SkipSpace(void* pred);                 // 0x008d4c80
    void  MatchWhileIdent(void* pred);           // 0x008d4df0
    uint8 MatchCStr(const char* lit);            // 0x008d4e40
    void  MatchWhileHex(void* pred);             // 0x008d4ea0
    uint8 Advance();                             // 0x008d4ef0
    uint8 MatchPunc(int8 c);                     // 0x008d5160
    uint8 MatchString();                         // 0x008d52f0
};
struct Rect20Vec {
    int*   begin;   // 0x00
    int*   end;     // 0x04
    int*   cap;     // 0x08
    VAlloc* alloc;  // 0x0c
    void*  name;    // 0x10

    void  push_back(int* out, int* value);       // 0x008d4520
};
struct BigObj {
    char       pad00[0x18];
    Rect20Vec  vec;   // 0x18

    void push(int key, int* src, uint cnt);   // 0x008d4920
};
extern "C" uint FUN_00894e30(TokenReader* t, const char* s);    // 0x00894e30  Skip<char>
extern "C" void FUN_008950b0(TokenReader* t);                   // 0x008950b0  SkipToEoL
extern "C" uint FUN_008951c0(TokenReader* t, const char* s);    // 0x008951c0  SkipUntil<n>
extern "C" void FUN_00895770(TokenReader* t, const char* s);    // 0x00895770  Match<Alternative>
extern "C" uint32 g_1667a78;
// ---- items of slice s008d4520 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
extern "C" char* FUN_008d4ad0(char* a, char* b, char** key);  // 0x008d4ad0 (stays in the slice: not this object's)
extern "C" char* FUN_008d4b30(char* a, char* b, char** key);  // 0x008d4b30 (stays in the slice: not this object's)

// @ 0x008d4920
void BigObj::push(int key, int* src, uint cnt)
{
    if (cnt >= 4)
        cnt = 4;
    int rec[5];
    rec[1] = 0; rec[2] = 0; rec[3] = 0; rec[4] = 0;
    rec[0] = key;
    for (uint i = 0; i < cnt; i++)
        rec[1 + i] = src[i];

    int* p = vec.end;
    if (p < vec.cap) {
        vec.end = p + 5;
        if (p != 0) {
            p[0] = rec[0]; p[1] = rec[1]; p[2] = rec[2];
            p[3] = rec[3]; p[4] = rec[4];
            return;
        }
    } else {
        vec.push_back(p, rec);
    }
}

// @ 0x008d4a10
extern "C" char* FUN_008d4a10(const char* name)
{
    if (_stricmp(name, "XBox") == 0)     return "xb";
    if (_stricmp(name, "Xenon") == 0)    return "xe";
    if (_stricmp(name, "PS2") == 0)      return "ps2";
    if (_stricmp(name, "PS3") == 0)      return "ps3";
    if (_stricmp(name, "GameCube") == 0) return "gc";
    if (_stricmp(name, "Windows") == 0)  return "win32";
    return "";
}

// @ 0x008d4b90
extern "C" char** FUN_008d4b90(char** out, char* a, char* b, char** key)
{
    int n = (int)(b - a) >> 3;
    while (n > 0) {
        int half = n >> 1;
        char** slot = (char**)(a + half * 8);
        char* s = *slot;
        char* t = *key;
        char  c = *s;
        while (c != 0 && c == *t) {
            c = s[1]; s++; t++;
        }
        if (*s < *t) {
            a = (char*)slot + 8;
            n = n + (-1 - half);
        } else {
            char* s2 = *slot;
            char* t2 = *key;
            c = *t2;
            while (c != 0 && c == *s2) {
                c = t2[1]; t2++; s2++;
            }
            if (*s2 <= *t2) {
                out[1] = FUN_008d4b30((char*)slot + 8, b, key);
                out[0] = FUN_008d4ad0(a, (char*)slot, key);
                return out;
            }
            b = (char*)slot;
            n = half;
        }
    }
    out[0] = a;
    out[1] = a;
    return out;
}

// @ 0x008d4ef0
uint8 TokenReader::Advance()
{
    if ((g_1667a78 & 1) == 0) g_1667a78 |= 1;
    if ((g_1667a78 & 2) == 0) g_1667a78 |= 2;
    if ((g_1667a78 & 4) == 0) g_1667a78 |= 4;

    mTokenLine = currentLine;

    for (;;) {
        if (scanEnd <= scanPos)
            return 0;
        if (!SkipSpace(0))
            break;
    }

    if (FUN_00894e30(this, g_142ef10)) {
        FUN_008950b0(this);
        mToken = 1;
        return 1;
    }
    if (FUN_00894e30(this, g_142ef0c)) {
        FUN_008951c0(this, g_142ef08);
        mToken = 1;
        return 1;
    }

    {
        char* p = scanPos;
        char* e = scanEnd;
        if (p < e) {
            if (*p == '\r') {
                p++;
                scanPos = p;
                if (p < e && *p == '\n') {
                    p++;
                    scanPos = p;
                }
                currentLine++;
                lineBegin = scanPos;
                mToken = 1;
                return 1;
            }
            if (*p == '\n') {
                p++;
                currentLine++;
                scanPos = p;
                lineBegin = p;
                mToken = 1;
                return 1;
            }
        }
    }

    if (matchText.mpBegin != matchText.mpEnd) {
        *matchText.mpBegin = '\0';
        matchText.mpEnd = matchText.mpBegin;
    }

    {
        char* p = scanPos;
        if (p < scanEnd) {
            int  c = (int)*p;
            uint u = (uint)c;
            if (u - 0x61 < 0x1a || u - 0x41 < 0x1a || c == 0x5f) {
                matchText.push_back(*p);
                scanPos = scanPos + 1;
                MatchWhileIdent(0);
                for (char* q = matchText.mpBegin; q < matchText.mpEnd; q++)
                    *q = (char)tolower((uint8)*q);
                mToken = 2;
                return 1;
            }
        }
    }

    if (MatchCStr(g_14365d8) || MatchCStr(g_14365d4)) {
        if (matchText.mpBegin != matchText.mpEnd) {
            *matchText.mpBegin = '\0';
            matchText.mpEnd = matchText.mpBegin;
        }
        MatchWhileHex(0);
        mTokenValue = (int)strtoul(matchText.mpBegin, 0, 16);
        mToken = 3;
        return 1;
    }

    {
        char* p = scanPos;
        char* e = scanEnd;
        int8  b;
        if (p < e) {
            int8 c = *p;
            if ((uint)((int)c - 0x30) < 10) {
                matchText.push_back(*p);
                scanPos = scanPos + 1;
                FUN_00895770(this, g_1667a80);
                mTokenValue = (int)strtoul(matchText.mpBegin, 0, 10);
                mToken = 3;
                return 1;
            }
            if (p < e) {
                b = *p;
                scanPos = p + 1;
                goto have_char;
            }
        }
        b = 0;
have_char:
        if (isprint((uint8)b) == 0) {
            mToken = 0xfffffc19;
            return 0;
        }
        matchText.push_back((char)b);
        mToken = 4;
        mTokenValue = (int8)b;
        return 1;
    }
}

// @ 0x008d5180
extern "C" uint8 FUN_008d5180(TokenReader* t, int8 term)
{
    uint8 c;
    for (;;) {
        char* p = t->scanPos;
        char* e = t->scanEnd;
        if (e <= p) return 0;
        if ((int8)*p == term) {
            t->scanPos = p + 1;
            return 1;
        }
        if (e <= p) return 0;
        if (*p == '\\') {
            t->scanPos = p + 1;
            if (p + 1 < e) {
                c = (uint8)p[1];
                t->scanPos = p + 2;
            } else {
                c = 0;
            }
            switch (c) {
            case '0':  t->matchText.push_back(0);     break;
            case 'b':  t->matchText.push_back(8);     break;
            case 'f':  t->matchText.push_back(0xc);   break;
            case 'n':  t->matchText.push_back(0xa);   break;
            case 'r':  t->matchText.push_back(0xd);   break;
            case 'v':  t->matchText.push_back(0xb);   break;
            default:
                t->matchText.push_back('\\');
                t->matchText.push_back((char)c);
                break;
            }
        } else {
            if (e <= p) return 0;
            c = (uint8)*p;
            t->matchText.push_back((char)c);
            t->scanPos = t->scanPos + 1;
        }
    }
}

// @ 0x008d5340
namespace EA { namespace Input {
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
