// Slice s008d4520 -- EA text lexer / trigger token reader, plus a few small
// vector and lookup helpers from the same module.
//
// Most routines here are __thiscall (`mov esi, ecx` at entry), so they are
// modelled as member functions; the remaining ones take plain stack arguments.
#include "types.h"
#include <intrin.h>
typedef unsigned char uint8; typedef signed char int8; typedef unsigned short uint16;
typedef short int16; typedef unsigned int uint; typedef unsigned int uint32;
typedef int int32;

// ---------------------------------------------------------------------------
// Shared helpers and layouts
// ---------------------------------------------------------------------------

// eastl allocator interface: a real polymorphic class so the call site emits
// exactly the original's `mov ecx,alloc; mov edx,[ecx]; call [edx+8]` shape.
struct VAlloc {
    virtual void* slot0();                                   // vtable +0x00
    virtual void* slot4();                                   // vtable +0x04
    virtual void* allocate(unsigned n, int a, void* name);   // vtable +0x08
    virtual void  deallocate(void* p, unsigned n);           // vtable +0x0c
};

// eastl::basic_string<char> (20-byte form used by the lexer).
struct EaString {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    char  mBuffer[8];   // +0x0c

    void push_back(char c);   // 0x005306c0 (__thiscall)
};
extern "C" __declspec(dllimport) int  tolower(int c);
extern "C" __declspec(dllimport) int  isprint(int c);
extern "C" __declspec(dllimport) int  iswctype(int c, int type);
extern "C" __declspec(dllimport) unsigned long strtoul(const char* s, char** end, int base);

// Lexer::TokenReader<char, CharStream<char> >
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

// ---------------------------------------------------------------------------
// @ 0x008d4520
// Push a 0x14-byte record onto a vector-like container, growing it when full.
// out = insertion slot, value = record to copy.
// ---------------------------------------------------------------------------
struct Rect20Vec {
    int*   begin;   // 0x00
    int*   end;     // 0x04
    int*   cap;     // 0x08
    VAlloc* alloc;  // 0x0c
    void*  name;    // 0x10

    void  push_back(int* out, int* value);       // 0x008d4520
};

extern "C" void FUN_00c50ad0(int* dst, int* srcEnd, int* cur);   // 0x00c50ad0
extern "C" int* FUN_00951bb0(int* begin, int* out, int* val);    // 0x00951bb0

void Rect20Vec::push_back(int* out, int* value)
{
    int* e = end;
    if (e != cap) {
        if (out <= value && value < e)
            value += 5;
        if (e != 0) {
            e[0] = e[-5]; e[1] = e[-4]; e[2] = e[-3]; e[3] = e[-2]; e[4] = e[-1];
        }
        FUN_00c50ad0(out, end - 5, end);
        out[0] = value[0]; out[1] = value[1]; out[2] = value[2];
        out[3] = value[3]; out[4] = value[4];
        end += 5;
        return;
    }

    int n = (int)(((char*)e - (char*)begin) / 0x14);
    int capacity = n;
    int* p;
    if (capacity == 0) {
        capacity = 1;
    } else {
        capacity = capacity * 2;
    }
    if (capacity == 0)
        p = 0;
    else
        p = (int*)alloc->allocate((unsigned)(capacity * 0x14), 0, name);

    {
        int* r = FUN_00951bb0(begin, out, p);
        if (r != 0) {
            r[0] = value[0]; r[1] = value[1]; r[2] = value[2];
            r[3] = value[3]; r[4] = value[4];
        }
        int* ne = FUN_00951bb0(out, end, r + 5);
        int* b = begin;
        if (b != 0)
            alloc->deallocate(b, (unsigned)(((char*)cap - (char*)b) / 0x14 * 0x14));
        begin = p;
        end = ne;
        cap = (int*)((char*)p + capacity * 0x14);
    }
}

// ---------------------------------------------------------------------------
// @ 0x008d4680
// Recursive in-place sort driver over 0x10-byte records.
// ---------------------------------------------------------------------------
extern "C" int* FUN_008d38d0(int* a, int* b, int* c, void* cmp);              // 0x008d38d0
extern "C" int* FUN_008d4250(int* a, int* b, int, int, int, int, void* cmp);  // 0x008d4250
extern "C" void FUN_008d4320(int* a, int* b, int* c, void* cmp);              // 0x008d4320

extern "C" void FUN_008d4680(int a, int b, int depth, void* cmp)
{
    uint diff = (uint)(b - a);
    while ((int)(diff & 0xfffffff0) > 0x1c0 && depth > 0) {
        int* pivot = FUN_008d38d0(
            (int*)a,
            (int*)(((int)((uint)((b - a) >> 4) - (uint)((b - a) >> 0x1f)) >> 1) * 0x10 + a),
            (int*)(b - 0x10), cmp);
        int* m = FUN_008d4250((int*)a, (int*)b, pivot[0], pivot[1], pivot[2], pivot[3], cmp);
        depth--;
        FUN_008d4680((int)m, b, depth, cmp);
        diff = (uint)((int)m - a);
        b = (int)m;
    }
    if (depth == 0)
        FUN_008d4320((int*)a, (int*)b, (int*)b, cmp);
}

// ---------------------------------------------------------------------------
// Sorted table of 0x10-byte entries, each {key, value, flags, extra}.
// ---------------------------------------------------------------------------
extern "C" void  FUN_008d4730(void* begin, void* end, int* key);              // 0x008d4730
extern "C" void* FUN_00e23ee0(void* begin, void* end, void* key, void* obj);  // 0x00e23ee0

struct SortedTable {
    char   pad00[0x04];
    void*  begin;   // 0x04
    void*  end;     // 0x08
    char   pad0c[0x2c - 0x0c];
    uint8  dirty;   // 0x2c

    int lookupFlags(int* key, uint* outFlags, int* outExtra);   // 0x008d47b0
    int lookup400(int* key, uint* outFlags);                    // 0x008d4850
};

// ---------------------------------------------------------------------------
// @ 0x008d47b0
// Find the entry matching the key word at key+0xc whose flag word satisfies
// the mask at key+0x16.
// ---------------------------------------------------------------------------
int SortedTable::lookupFlags(int* key, uint* outFlags, int* outExtra)
{
    if (dirty != 0) {
        FUN_008d4730(begin, end, key);
        dirty = 0;
    }
    int* last = (int*)end;
    int* e = (int*)FUN_00e23ee0(begin, end, (char*)key + 0xc, key);
    if (e != last) {
        do {
            if (*e != *(int*)((char*)key + 0xc))
                return 0;
            if ((((*(uint16*)((char*)e + 0xa) & *(uint16*)((char*)key + 0x16)) ==
                  *(uint16*)((char*)e + 8)) ||
                 (*(uint16*)((char*)e + 0xa) == 0x3ff)) &&
                ((*(uint16*)((char*)key + 0x16) & 0x2000) == 0)) {
                *outFlags = *(uint16*)((char*)e + 8);
                *outExtra = *(int*)((char*)e + 0xc);
                return *(int*)((char*)e + 4);
            }
            e += 4;
        } while (e != (int*)end);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x008d4850
// Same lookup, selecting the entry that carries the 0x400 flag.
// ---------------------------------------------------------------------------
int SortedTable::lookup400(int* key, uint* outFlags)
{
    if (dirty != 0) {
        FUN_008d4730(begin, end, key);
        dirty = 0;
    }
    int* last = (int*)end;
    int* e = (int*)FUN_00e23ee0(begin, end, (char*)key + 0xc, key);
    if (e != last) {
        do {
            if (*e != *(int*)((char*)key + 0xc))
                return 0;
            if ((*(uint16*)((char*)e + 8) & 0x400) != 0) {
                *outFlags = *(uint16*)((char*)e + 8);
                return *(int*)((char*)e + 4);
            }
            e += 4;
        } while (e != last);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x008d48d0
// Append one 0x10-byte entry to the vector at +4 (capacity at +0xc).
// ---------------------------------------------------------------------------
// FUN_008d4400 is __thiscall on the {base,end,cap} sub-object at +4 (ecx = &end's owner).
struct VecCore {
    void*  base;   // 0x00 (this+4)
    void*  end;    // 0x04 (this+8)
    void*  cap;    // 0x08 (this+0xc)
    void* grow(void* p, void* value);   // 0x008d4400
};

struct SmallVec {
    char   pad00[0x04];
    void*  base;   // 0x04
    void*  end;    // 0x08
    void*  cap;    // 0x0c
    char   pad10[0x2c - 0x10];
    uint8  dirty;  // 0x2c

    void push(void* value);   // 0x008d48d0
};

void SmallVec::push(void* value)
{
    VecCore* core = (VecCore*)((char*)this + 4);
    void* p = core->end;
    if (p < core->cap) {
        core->end = (char*)p + 0x10;
        if (p != 0) {
            ((int*)p)[0] = ((int*)value)[0];
            ((int*)p)[1] = ((int*)value)[1];
            ((int*)p)[2] = ((int*)value)[2];
            ((int*)p)[3] = ((int*)value)[3];
            dirty = 1;
            return;
        }
    } else {
        core->grow(p, value);
    }
    dirty = 1;
}

// ---------------------------------------------------------------------------
// @ 0x008d4920
// Push a 0x14-byte record {key, up to 4 payload dwords} onto the vector at
// +0x18.
// ---------------------------------------------------------------------------
struct BigObj {
    char       pad00[0x18];
    Rect20Vec  vec;   // 0x18

    void push(int key, int* src, uint cnt);   // 0x008d4920
};

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

// ---------------------------------------------------------------------------
// @ 0x008d49b0
// clear(): collapse both growable runs back to their base pointers.
// ---------------------------------------------------------------------------
struct Quad16;
struct Rec20;
extern "C" Quad16* copy_Quad16(Quad16* dst, Quad16* end, Quad16* src);   // 0x00705250
extern "C" Rec20*  copy_Rec20(Rec20* dst, Rec20* end, Rec20* src);        // 0x00951bf0

struct ClearTwo {
    char   pad00[0x04];
    void*  abase;  // 0x04
    void*  aend;   // 0x08
    char   pad0c[0x0c];
    void*  bbase;  // 0x18
    void*  bend;   // 0x1c

    void clear();  // 0x008d49b0
};

void ClearTwo::clear()
{
    int a0 = (int)abase;
    int a1 = (int)aend;
    copy_Quad16((Quad16*)a1, (Quad16*)a1, (Quad16*)a0);
    aend = (void*)((int)aend + ((a1 - a0) >> 4) * -0x10);
    _ReadWriteBarrier();

    int b0 = (int)bbase;
    int b1 = (int)bend;
    copy_Rec20((Rec20*)b1, (Rec20*)b1, (Rec20*)b0);
    bend = (void*)((int)bend + ((b1 - b0) / 0x14) * -0x14);
}

// ---------------------------------------------------------------------------
// @ 0x008d4a10
// GetAbbreviatedPlatformName: map a platform name to its two-letter tag.
// The name arrives in esi in the original, so this is a register-ABI entry.
// ---------------------------------------------------------------------------
extern "C" int   _stricmp(const char* a, const char* b);
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

// ---------------------------------------------------------------------------
// @ 0x008d4aa0
// Lowercase the buffer in place.
// ---------------------------------------------------------------------------
struct ByteRange {
    char* begin;   // 0x00
    char* end;     // 0x04

    void toLower();  // 0x008d4aa0
};

void ByteRange::toLower()
{
    for (char* p = begin; p < end; p++)
        *p = (char)tolower((uint8)*p);
}

// ---------------------------------------------------------------------------
// @ 0x008d4ad0
// Lower bound over an array of {char* str; ...} pairs (8 bytes each).
// ---------------------------------------------------------------------------
extern "C" char* FUN_008d4ad0(char* a, char* b, char** key)
{
    int n = (int)(b - a) >> 3;
    if (n > 0) {
        char* k = *key;
        do {
            int half = n >> 1;
            char* s = *(char**)(a + half * 8);
            char* t = k;
            while (*s != 0 && *s == *t) {
                ++s; ++t;
            }
            if (*s < *t) {
                a += 8 + half * 8;
                n = n + (-1 - half);
            } else {
                n = half;
            }
        } while (n > 0);
    }
    return a;
}

// ---------------------------------------------------------------------------
// @ 0x008d4b30
// Upper bound over the same array shape.
// ---------------------------------------------------------------------------
extern "C" char* FUN_008d4b30(char* a, char* b, char** key)
{
    int n = ((int)(b - a)) >> 3;
    if (n > 0) {
        char* k = *key;
        do {
            int half = n >> 1;
            char* s = *(char**)(a + half * 8);
            char* t = k;
            while (*s != 0 && *s == *t) {
                ++s; ++t;
            }
            if (*s <= *t) {
                a += 8 + half * 8;
                n = n + (-1 - half);
            } else {
                n = half;
            }
        } while (n > 0);
    }
    return a;
}

// ---------------------------------------------------------------------------
// @ 0x008d4b90
// equal_range over the array of string keys; writes {lo, hi} and returns it.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x008d4c60
// Release the heap buffer behind one string field when it is not the inline
// buffer.
// ---------------------------------------------------------------------------
extern "C" void operator_delete__(void* p);   // 0x00f47380

struct StrField {
    char  pad00[0x10];
    char* begin;   // 0x10
    char  pad14[0x04];
    char* end;     // 0x18

    void release();  // 0x008d4c60
};

void StrField::release()
{
    char* b = begin;
    if (end - b > 1 && b != 0)
        operator_delete__(b);
}

// ---------------------------------------------------------------------------
// @ 0x008d4c80
// Skip horizontal whitespace (iswctype 'space'), stopping at '\n' or '\r'.
// Returns true when at least one character was consumed.
// ---------------------------------------------------------------------------
uint8 TokenReader::SkipSpace(void* pred)
{
    (void)pred;
    uint8 r = 0;
    if (scanPos >= scanEnd)
        return 0;
    do {
        int8 c = *scanPos;
        if (iswctype(c, 8) == 0) return r;
        if (c == '\n') return r;
        if (c == '\r') return r;
        scanPos++;
        r = 1;
    } while (scanPos < scanEnd);
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x008d4cd0
// Look up a key in the string table at table..table+0x90, expecting a unique
// hit; on success writes the entry's value.
// ---------------------------------------------------------------------------
extern "C" uint8 FUN_008d4cd0(char* table, char* key, int* out)
{
    char* pair[2];
    FUN_008d4b90(pair, table, table + 0x90, &key);
    if (pair[0] + 8 == pair[1]) {
        *out = *(int*)(pair[0] + 4);
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x008d4d20
// Same as above for the second table (at +0x758).
// ---------------------------------------------------------------------------
extern "C" uint8 FUN_008d4d20(char* table, char* key, int* out)
{
    char* pair[2];
    FUN_008d4b90(pair, table, table + 0x758, &key);
    if (pair[0] + 8 == pair[1]) {
        *out = *(int*)(pair[0] + 4);
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x008d4d70
// Walk the expression-function chain at +4 and return the value attached to
// the named entry of each node's hashtable at +0x1c.
// ---------------------------------------------------------------------------
struct Hashtable {
    char        pad00[0x04];
    int*        buckets;   // 0x04 (this+0x20)
    int         bucketCount; // 0x08 (this+0x24)
    void* find(void* local8, char* key);   // 0x007e2ea0 (ecx = this)
};

struct ExprTable {
    char        pad00[0x04];
    ExprTable*  next;       // 0x04
    char        pad08[0x1c - 0x08];
    Hashtable   ht;         // 0x1c

    uint8 lookup(char* key, int* out);   // 0x008d4d70
};

uint8 ExprTable::lookup(char* key, int* out)
{
    char  local[8];
    int*  node = (int*)ht.find(local, key);
    int*  p    = (int*)node[0];
    ExprTable* e = this;
    while (p == (int*)(e->ht.buckets[e->ht.bucketCount])) {
        e = e->next;
        if (e == 0)
            return 0;
        node = (int*)e->ht.find(local, key);
        p = (int*)node[0];
    }
    *out = p[4];
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x008d4df0
// TokenReader::MatchWhile<Alternative<Alternative<Alternative<Range<a,z>,
// Range<A,Z>>, Range<0,9>>, Character<'_'>>> -- identifier continuation.
// ---------------------------------------------------------------------------
void TokenReader::MatchWhileIdent(void* pred)
{
    (void)pred;
    while (scanPos < scanEnd) {
        int  c = (int8)*scanPos;
        uint u = (uint)c;
        if (u - 0x61 > 0x19 && u - 0x41 > 0x19 && u - 0x30 > 9 && c != 0x5f)
            return;
        matchText.push_back(*scanPos);
        scanPos++;
    }
}

// ---------------------------------------------------------------------------
// @ 0x008d4e40
// TokenReader::Match<const char*> -- consume a literal.
// ---------------------------------------------------------------------------
uint8 TokenReader::MatchCStr(const char* lit)
{
    int  n = 0;
    char c = *lit;
    if (c != 0) {
        char* e = scanEnd;
        char* p = scanPos;
        do {
            int got = (p < e) ? *p : 0;
            if (c != (char)got)
                return 0;
            c = lit[n + 1];
            n++;
            p++;
        } while (c != 0);
        while (n != 0) {
            --n;
            matchText.push_back(*scanPos);
            scanPos++;
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x008d4ea0
// TokenReader::MatchWhile<Alternative<Alternative<Range<0,9>,Range<a,f>>,
// Range<A,F>>> -- hex-digit continuation.
// ---------------------------------------------------------------------------
void TokenReader::MatchWhileHex(void* pred)
{
    (void)pred;
    while (scanPos < scanEnd) {
        int  c = (int8)*scanPos;
        uint u = (uint)c;
        if (u - 0x30 > 9 && u - 0x61 > 5 && u - 0x41 > 5)
            return;
        matchText.push_back(*scanPos);
        scanPos++;
    }
}

// ---------------------------------------------------------------------------
// @ 0x008d4ef0
// TriggerTokenReader::Advance -- produce the next token.
// ---------------------------------------------------------------------------
extern "C" uint FUN_00894e30(TokenReader* t, const char* s);    // 0x00894e30  Skip<char>
extern "C" void FUN_008950b0(TokenReader* t);                   // 0x008950b0  SkipToEoL
extern "C" uint FUN_008951c0(TokenReader* t, const char* s);    // 0x008951c0  SkipUntil<n>
extern "C" void FUN_00895770(TokenReader* t, const char* s);    // 0x00895770  Match<Alternative>

extern "C" uint32 g_1667a78;
extern char g_142ef10[];
extern char g_142ef0c[];
extern char g_142ef08[];
extern char g_14365d8[];
extern char g_14365d4[];
extern char g_1667a80[];

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

// ---------------------------------------------------------------------------
// @ 0x008d5160
// TriggerTokenReader::MatchPunc -- accept the given punctuation character.
// ---------------------------------------------------------------------------
uint8 TokenReader::MatchPunc(int8 c)
{
    if (mToken == 4 && mTokenValue == (int)c) {
        Advance();
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x008d5180
// ParseEscapedString: read up to the terminator, expanding backslash escapes.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x008d52f0
// TriggerTokenReader::MatchString -- quoted string token, keyed by its FNV1
// hash.
// ---------------------------------------------------------------------------
extern "C" uint32 FNV1Hash(const void* data, int len, uint32 seed);  // 0x00932e50

uint8 TokenReader::MatchString()
{
    if (matchText.mpBegin != matchText.mpEnd) {
        *matchText.mpBegin = '\0';
        matchText.mpEnd = matchText.mpBegin;
    }
    if (FUN_008d5180(this, '"')) {
        mTokenValue = (int)FNV1Hash(matchText.mpBegin,
                                    (int)(matchText.mpEnd - matchText.mpBegin),
                                    0x811c9dc5);
        Advance();
        return 1;
    }
    return 0;
}
