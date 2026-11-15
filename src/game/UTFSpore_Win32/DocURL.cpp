// src/game/UTFSpore_Win32/DocURL.cpp -- migrated from slice(s) s008e2dd0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/DocURL.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stddef.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

// ---- items of slice s008e2dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uint32;
typedef unsigned short wchar16;
struct WStrErase { int* Fn8e3a70(uint32 pos, uint32 count); };   // 0x008e3a70 (thiscall)
// ---- items of slice s008e2dd0 end

// @ 0x008e38b0
unsigned int Fn8e38b0(wchar16* p)
{
    while (iswctype(*p, 0x107) || *p == 0x2b || *p == 0x2e || *p == 0x2d) {
        ++p;
    }
    return (unsigned int)(((*p != 0x3a) - 1) & (unsigned int)(size_t)p);
}

// @ 0x008e3900
wchar16* Fn8e3900(wchar16* p)
{
    int ok = iswctype(*p, 0x157);
    while (ok && *p != 0x2f && *p != 0x3b && *p != 0x3f && *p != 0x23) {
        ++p;
        ok = iswctype(*p, 0x157);
    }
    return p;
}

// @ 0x008e3960
wchar16* Fn8e3960(wchar16* p)
{
    int ok = iswctype(*p, 0x157);
    while (ok && *p != 0x3b && *p != 0x3f && *p != 0x23) {
        ++p;
        ok = iswctype(*p, 0x157);
    }
    return p;
}

// @ 0x008e3a10
char Fn8e3a10(int* strObj, int idx)
{
    wchar16* begin = (wchar16*)strObj[0];
    wchar16* end   = (wchar16*)strObj[1];
    wchar16* limit = begin + idx;
    if (end == limit) return 0;
    wchar16* p = end;
    while (p > limit) {
        p -= 1;
        if (*p == 0x2f) break;
    }
    if (p != end) {
        memmove(p, end, 2);
        strObj[1] = (int)(strObj[1] + ((char*)end - (char*)p) );
    }
    return 1;
}

// @ 0x008e3a70
int* WStrErase::Fn8e3a70(uint32 pos, uint32 count)
{
    int* pThis = (int*)this;
    char* begin = (char*)pThis[0];
    char* end   = (char*)pThis[1];
    uint32 avail = (uint32)((end - begin) >> 1) - pos;
    uint32 n = (count <= avail) ? count : avail;
    char* src = begin + (n + pos) * 2;
    char* dst = begin + pos * 2;
    if (dst != src) {
        memmove(dst, src, ((end - src) >> 1) * 2 + 2);
        pThis[1] = (int)(pThis[1] + (((src - dst) >> 1) * -2));
    }
    return (int*)this;
}

// @ 0x008e3b90
uint32 Fn8e3b90(wchar16* url, int* outStr)
{
    if (url == 0) return 0;
    wchar16* scheme = (wchar16*)Fn8e38b0(url);
    if (scheme && _wcsnicmp((const wchar_t*)url, L"file:", 5) == 0) {
        url = scheme + 1;
    }
    (void)outStr;
    return 1;
}

// @ 0x008e3fa0
void* Fn8e3fa0(void** out, wchar16* base, wchar16* rel)
{
    (void)base; (void)rel;
    if (out) { *out = 0; }
    return out;
}
