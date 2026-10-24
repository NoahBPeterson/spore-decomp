// Slice s008f3530 -- EA::XHTML::Style::CSSParser / CSSTokenReader / CharStream (SporeApp.exe)
// Reconstructed from the 2008 PDB layouts and Ghidra decompilation.
// Build: /O2 /MD /Gy /EHsc /TP /arch:SSE (game-code flags).

#include <stddef.h>

typedef unsigned int   uint32;
typedef unsigned short wchar16;

// Static empty wide string at 0x01667bac (two wchars: terminator + guard).
extern "C" wchar16 gEmptyStr[1];        // 0x01667bac
extern "C" wchar16 gEmptyStrEnd;        // 0x01667bae
extern "C" char    gTokStart[];         // 0x01667b04
extern "C" int     gTokFlag;            // 0x01667b08
extern "C" char    gIdentPred[];        // 0x01439ac4

// comparison predicates used by the static-definition binary searches
extern "C" char Fn8f2e10(void* key, void* elem);   // 0x008f2e10
extern "C" char Fn8f2e90(void* elem, void* key);   // 0x008f2e90
// CRT wide ctype test
extern "C" int  iswctype(unsigned short c, int t);

struct WStr2 { void push_back(wchar16 c); };       // 0x004f6510 (eastl wstring)

// ---------------------------------------------------------------------------
// CharStream: scanPos@0, scanEnd@4, lineBegin@8, lineCount@0xc,
//             matchString{begin@0x10,end@0x14,cap@0x18}, allocName@0x1c.
// ---------------------------------------------------------------------------
struct CharStream {
    wchar16* scanPos;   // +0
    wchar16* scanEnd;   // +4
    wchar16* lineBegin; // +8
    int      lineCount; // +0xc

    void* Fn8f38b0(wchar16* s);  // ctor from string
    int   Fn8f35d0(void* pred);  // skip to ';' or '}'
    void  Fn8f36c0();            // consume one EOL
    char  Fn8f3830();            // skip whitespace
    char  Fn8f3640(void* pred);  // 0x008f3640
    char  Fn8f3710(void* pred);  // 0x008f3710
    char  Fn8f34d0(void* pred);  // MatchWide, 0x008f34d0
    char  Fn8f3480(void* pred);  // MatchAscii, 0x008f3480
    char  Fn8f39e0(int c);       // match a single wchar
    char  Fn8f3a10(int);         // match a digit
    void  Fn8f3a40(int);         // match digits while in range
    int   Fn8f3d20(int c);       // match a string up to terminator c
    char  Fn8f3a80();            // MatchEscape (stub)
};

struct CSSParser {
    void* Fn8f3900(int p1, wchar16* begin, wchar16* end);
    void* Fn8f3970(int p1, wchar16* begin, int count);
    __declspec(noinline) char Fn8f4290();
    void  Fn8f42d0();
    void  Fn8f4320();
    char  Fn8f4360(int tok);
    char  Fn8f43a0(wchar16* str);
    void  Fn8f3d90();            // Advance (stub)
};

// ---------------------------------------------------------------------------
// 0x008f3530  lower_bound over StaticDefinition (8-byte records)
// ---------------------------------------------------------------------------
// @ 0x008f3530
wchar16** Fn8f3530(char* begin, char* end, void* key)
{
    int n = (int)(end - begin) >> 3;
    if (n <= 0) return (wchar16**)begin;
    do {
        int mid = n >> 1;
        char* elem = begin + mid * 8;
        if (!Fn8f2e10(*(wchar16**)key, elem)) {
            begin = elem + 8;
            n = n + (-1 - mid);
        } else {
            n = mid;
        }
    } while (n > 0);
    return (wchar16**)begin;
}

// ---------------------------------------------------------------------------
// 0x008f3580  upper_bound over StaticDefinition (8-byte records)
// ---------------------------------------------------------------------------
// @ 0x008f3580
wchar16** Fn8f3580(char* begin, char* end, void* key)
{
    int n = (int)(end - begin) >> 3;
    if (n <= 0) return (wchar16**)begin;
    do {
        int mid = n >> 1;
        char* elem = begin + mid * 8;
        if (Fn8f2e90(elem, *(wchar16**)key)) {
            begin = elem + 8;
            n = n + (-1 - mid);
        } else {
            n = mid;
        }
    } while (n > 0);
    return (wchar16**)begin;
}

// ---------------------------------------------------------------------------
// 0x008f35d0  CharStream::Fn8f35d0 -- advance to ';' or '}'
// ---------------------------------------------------------------------------
// @ 0x008f35d0
int CharStream::Fn8f35d0(void* pred)
{
    (void)pred;
    for (;;) {
        wchar16* p = scanPos;
        short s = (short)*p;
        if (s == 0x3b) return 1;
        if (s == 0x7d) break;
        wchar16* e = scanEnd;
        if (e <= p) return 0;
        if (s == 0xd) {
            wchar16* q = p + 1;
            scanPos = q;
            if (q < e && *q == 10) scanPos = p + 2;
            lineCount = lineCount + 1;
            lineBegin = scanPos;
        } else {
            if (s == 10) {
                lineCount = lineCount + 1;
                scanPos = p + 1;
                lineBegin = p + 1;
            } else {
                scanPos = p + 1;
            }
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x008f36c0  CharStream::Fn8f36c0 -- consume one newline
// ---------------------------------------------------------------------------
// @ 0x008f36c0
void CharStream::Fn8f36c0()
{
    for (;;) {
        wchar16* p = scanPos;
        if (scanEnd <= p) return;
        if (*p == 0xd) {
            scanPos = p + 1;
            wchar16* q = scanPos;
            if (q < scanEnd && *q == 10) scanPos = q + 1;
            lineCount = lineCount + 1;
            lineBegin = scanPos;
            return;
        }
        if (*p == 10) {
            lineCount = lineCount + 1;
            scanPos = p + 1;
            lineBegin = p + 1;
            return;
        }
        scanPos = p + 1;
    }
}

// ---------------------------------------------------------------------------
// 0x008f3830  CharStream::Fn8f3830 -- skip whitespace
// ---------------------------------------------------------------------------
// @ 0x008f3830
char CharStream::Fn8f3830()
{
    char any = 0;
    for (;;) {
        wchar16* p = scanPos;
        wchar16* e = scanEnd;
        if (e <= p) return any;
        if (*p == 0xd) {
            wchar16* q = p + 1;
            scanPos = q;
            if (q < e && *q == 10) scanPos = p + 2;
            lineCount = lineCount + 1;
            lineBegin = scanPos;
            any = 1;
        } else if (*p == 10) {
            lineCount = lineCount + 1;
            scanPos = p + 1;
            lineBegin = p + 1;
            any = 1;
        } else {
            if (iswctype(*p, 8) == 0) return any;
            scanPos = p + 1;
            any = 1;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x008f3640  CharStream::Fn8f3640
// ---------------------------------------------------------------------------
// @ 0x008f3640
char CharStream::Fn8f3640(void* pred)
{
    for (;;) {
        if (Fn8f34d0(pred) != 0) return 1;
        wchar16* p = scanPos;
        wchar16* e = scanEnd;
        if (e <= p) return 0;
        if (*p == 0xd) {
            wchar16* q = p + 1;
            scanPos = q;
            if (q < e && *q == 10) scanPos = p + 2;
            lineCount = lineCount + 1;
            lineBegin = scanPos;
        } else {
            if (e <= p) return 0;
            if (*p == 10) {
                lineCount = lineCount + 1;
                scanPos = p + 1;
                lineBegin = p + 1;
            } else {
                if (e <= p) return 0;
                scanPos = p + 1;
            }
        }
    }
}

// ---------------------------------------------------------------------------
// 0x008f3710  CharStream::Fn8f3710
// ---------------------------------------------------------------------------
// @ 0x008f3710
char CharStream::Fn8f3710(void* pred)
{
    for (;;) {
        if (Fn8f3480(pred) != 0) return 1;
        wchar16* p = scanPos;
        wchar16* e = scanEnd;
        if (e <= p) return 0;
        if (*p == 0xd) {
            wchar16* q = p + 1;
            scanPos = q;
            if (q < e && *q == 10) scanPos = p + 2;
            lineCount = lineCount + 1;
            lineBegin = scanPos;
        } else {
            if (e <= p) return 0;
            if (*p == 10) {
                lineCount = lineCount + 1;
                scanPos = p + 1;
                lineBegin = p + 1;
            } else {
                if (e <= p) return 0;
                scanPos = p + 1;
            }
        }
    }
}

// ---------------------------------------------------------------------------
// 0x008f39e0  CharStream::Fn8f39e0 -- match one wchar
// ---------------------------------------------------------------------------
// @ 0x008f39e0
char CharStream::Fn8f39e0(int c)
{
    if (scanPos < scanEnd) {
        wchar16 ch = *scanPos;
        if (c == (int)ch) {
            ((WStr2*)((char*)this + 0x10))->push_back(ch);
            scanPos = scanPos + 1;
            return 1;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x008f3a10  CharStream::Fn8f3a10 -- match a digit
// ---------------------------------------------------------------------------
// @ 0x008f3a10
char CharStream::Fn8f3a10(int)
{
    if (scanPos < scanEnd) {
        wchar16 ch = *scanPos;
        if ((unsigned)(ch - 0x30) <= 9) {
            ((WStr2*)((char*)this + 0x10))->push_back(ch);
            scanPos = scanPos + 1;
            return 1;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x008f3a40  CharStream::Fn8f3a40 -- match digits while in range
// ---------------------------------------------------------------------------
// @ 0x008f3a40
void CharStream::Fn8f3a40(int)
{
    if (scanPos < scanEnd) {
        do {
            wchar16 ch = *scanPos;
            if ((unsigned)(ch - 0x30) > 9) break;
            ((WStr2*)((char*)this + 0x10))->push_back(ch);
            scanPos = scanPos + 1;
        } while (scanPos < scanEnd);
    }
}

// ---------------------------------------------------------------------------
// 0x008f3a80  CharStream::Fn8f3a80 (MatchEscape) -- stub
// ---------------------------------------------------------------------------
// @ 0x008f3a80
char CharStream::Fn8f3a80()
{
    return 0;
}

// ---------------------------------------------------------------------------
// 0x008f3d20  CharStream::Fn8f3d20 -- match a string up to terminator
// ---------------------------------------------------------------------------
// @ 0x008f3d20
int CharStream::Fn8f3d20(int c)
{
    char* r = (char*)this;
    wchar16* b = *(wchar16**)(r + 0x10);
    if (b != *(wchar16**)(r + 0x14)) {
        *b = 0;
        *(wchar16**)(r + 0x14) = b;
    }
    wchar16 term = (wchar16)c;
    for (;;) {
        wchar16* p = *(wchar16**)(r + 0);
        if (p < *(wchar16**)(r + 4) && *p == term) {
            *(wchar16**)(r + 0) = p + 1;
            return 1;
        }
        if (Fn8f3a80()) continue;
        p = *(wchar16**)(r + 0);
        if (p >= *(wchar16**)(r + 4)) return 0;
        ((WStr2*)(r + 0x10))->push_back(*p);
        *(wchar16**)(r + 0) = p + 1;
    }
}

// ---------------------------------------------------------------------------
// 0x008f38b0  CharStream ctor
// ---------------------------------------------------------------------------
// @ 0x008f38b0
void* CharStream::Fn8f38b0(wchar16* s)
{
    char* c = (char*)this;
    wchar16* e = s;
    while (*e != 0) e++;
    *(void**)(c + 4) = e;
    *(void**)(c + 0) = s;
    *(void**)(c + 8) = s;
    *(int*)(c + 0xc) = 1;
    void* g = (void*)gEmptyStr;
    *(void**)(c + 0x10) = g;
    *(void**)(c + 0x14) = g;
    *(void**)(c + 0x18) = (void*)&gEmptyStrEnd;
    *(void**)(c + 0x20) = 0;
    return this;
}

// ---------------------------------------------------------------------------
// 0x008f3900  CSSParser ctor (begin/end)
// ---------------------------------------------------------------------------
// @ 0x008f3900
void* CSSParser::Fn8f3900(int p1, wchar16* begin, wchar16* end)
{
    char* c = (char*)this;
    *(int*)(c + 0) = 0;
    *(void**)(c + 4) = begin;
    *(void**)(c + 0xc) = begin;
    *(int*)(c + 0x10) = 1;
    *(void**)(c + 8) = end;
    void* ga = (void*)gEmptyStr;
    *(void**)(c + 0x14) = ga;
    *(void**)(c + 0x18) = ga;
    *(void**)(c + 0x1c) = (void*)&gEmptyStrEnd;
    *(int*)(c + 0x24) = 0;
    *(int*)(c + 0x28) = 0;
    *(int*)(c + 0x2c) = 0;
    *(int*)(c + 0x30) = 0;
    *(int*)(c + 0x34) = 0;
    *(void**)(c + 0x40) = (void*)&gEmptyStrEnd;
    *(void**)(c + 0x38) = ga;
    *(void**)(c + 0x3c) = ga;
    *(int*)(c + 0x4c) = p1;
    *(int*)(c + 0x48) = 0;
    *(void**)(c + 0x58) = (void*)&gEmptyStrEnd;
    *(void**)(c + 0x50) = ga;
    *(void**)(c + 0x54) = ga;
    *(int*)(c + 0x60) = 0;
    return this;
}

// ---------------------------------------------------------------------------
// 0x008f3970  CSSParser ctor (begin/count)
// ---------------------------------------------------------------------------
// @ 0x008f3970
void* CSSParser::Fn8f3970(int p1, wchar16* begin, int count)
{
    char* c = (char*)this;
    *(int*)(c + 0) = 0;
    *(void**)(c + 4) = begin;
    *(void**)(c + 0xc) = begin;
    *(int*)(c + 0x10) = 1;
    *(void**)(c + 8) = begin + count;
    void* ga = (void*)gEmptyStr;
    *(void**)(c + 0x14) = ga;
    *(void**)(c + 0x18) = ga;
    *(void**)(c + 0x1c) = (void*)&gEmptyStrEnd;
    *(int*)(c + 0x24) = 0;
    *(int*)(c + 0x28) = 0;
    *(int*)(c + 0x2c) = 0;
    *(int*)(c + 0x30) = 0;
    *(int*)(c + 0x34) = 0;
    *(void**)(c + 0x40) = (void*)&gEmptyStrEnd;
    *(void**)(c + 0x38) = ga;
    *(void**)(c + 0x3c) = ga;
    *(int*)(c + 0x4c) = p1;
    *(int*)(c + 0x48) = 0;
    *(void**)(c + 0x58) = (void*)&gEmptyStrEnd;
    *(void**)(c + 0x50) = ga;
    *(void**)(c + 0x54) = ga;
    *(int*)(c + 0x60) = 0;
    return this;
}

// ---------------------------------------------------------------------------
// 0x008f3d90  CSSParser::Advance -- stub
// ---------------------------------------------------------------------------
// @ 0x008f3d90
__declspec(noinline) void CSSParser::Fn8f3d90()
{
    *(volatile int*)((char*)this + 0x28) = *(volatile int*)((char*)this + 0x28);
}

// ---------------------------------------------------------------------------
// 0x008f4290  CSSParser::Fn8f4290 -- skip TokenWS
// ---------------------------------------------------------------------------
// @ 0x008f4290
char CSSParser::Fn8f4290()
{
    char* c = (char*)this;
    char r = 0;
    if (*(int*)(c + 0x28) == 2) {
        do {
            wchar16* b = *(wchar16**)(c + 0x38);
            if (b != *(wchar16**)(c + 0x3c)) {
                *b = 0;
                *(wchar16**)(c + 0x3c) = b;
            }
            Fn8f3d90();
        } while (*(int*)(c + 0x28) == 2);
        r = 1;
    }
    return r;
}

// ---------------------------------------------------------------------------
// 0x008f42d0  CSSParser::Fn8f42d0
// ---------------------------------------------------------------------------
// @ 0x008f42d0
void CSSParser::Fn8f42d0()
{
    char* c = (char*)this;
    if ((gTokFlag & 1) == 0) gTokFlag = gTokFlag | 1;
    ((CharStream*)(c + 4))->Fn8f35d0(&gTokStart);
    wchar16* p = *(wchar16**)(c + 4);
    if (p < *(wchar16**)(c + 8) && *p == 0x3b) *(void**)(c + 4) = p + 1;
    Fn8f4290();
}

// ---------------------------------------------------------------------------
// 0x008f4320  CSSParser::Fn8f4320
// ---------------------------------------------------------------------------
// @ 0x008f4320
void CSSParser::Fn8f4320()
{
    char* c = (char*)this;
    ((CharStream*)(c + 4))->Fn8f3640(&gIdentPred);
    wchar16* p = *(wchar16**)(c + 4);
    if (p < *(wchar16**)(c + 8) && *p == 0x7d) *(void**)(c + 4) = p + 1;
    Fn8f4290();
    Fn8f3d90();
}

// ---------------------------------------------------------------------------
// 0x008f4360  CSSParser::Fn8f4360 -- exchange string triples if token matches
// ---------------------------------------------------------------------------
// @ 0x008f4360
char CSSParser::Fn8f4360(int tok)
{
    char* c = (char*)this;
    if (*(int*)(c + 0x28) != tok) return 0;
    void* t;
    t = *(void**)(c + 0x38); *(void**)(c + 0x38) = *(void**)(c + 0x14); *(void**)(c + 0x14) = t;
    t = *(void**)(c + 0x3c); *(void**)(c + 0x3c) = *(void**)(c + 0x18); *(void**)(c + 0x18) = t;
    t = *(void**)(c + 0x40); *(void**)(c + 0x40) = *(void**)(c + 0x1c); *(void**)(c + 0x1c) = t;
    Fn8f3d90();
    return 1;
}

// ---------------------------------------------------------------------------
// 0x008f43a0  CSSParser::Fn8f43a0 -- compare with mIdent, then advance
// ---------------------------------------------------------------------------
// @ 0x008f43a0
char CSSParser::Fn8f43a0(wchar16* str)
{
    char* c = (char*)this;
    if (*(int*)(c + 0x28) != 3) return 0;
    wchar16* q = *(wchar16**)(c + 0x14);
    int r;
    for (;;) {
        wchar16 a = str[0];
        if (a != q[0]) { r = (a < q[0]) ? -1 : 1; break; }
        if (a == 0) { r = 0; break; }
        wchar16 b = str[1];
        if (b != q[1]) { r = (b < q[1]) ? -1 : 1; break; }
        str += 2; q += 2;
        if (b == 0) { r = 0; break; }
    }
    if (r != 0) return 0;
    Fn8f3d90();
    return 1;
}

// ---------------------------------------------------------------------------
// 0x008f3790  eastl::equal_range<StaticDefinition> -- stub
// ---------------------------------------------------------------------------
// @ 0x008f3790
void Fn8f3790(void* out, const void* first, const void* last, const void* key)
{
    (void)first; (void)last;
    *(void**)out = *(void**)key;
    *((void**)out + 1) = *(void**)key;
}

// ---------------------------------------------------------------------------
// 0x008f3c40  CSSTokenReader::MatchIdent -- stub
// ---------------------------------------------------------------------------
// @ 0x008f3c40
int Fn8f3c40(void* self, int a)
{
    (void)a;
    return *(volatile int*)((char*)self + 0x28);
}
