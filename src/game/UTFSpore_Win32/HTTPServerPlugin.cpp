// src/game/UTFSpore_Win32/HTTPServerPlugin.cpp -- migrated from slice(s) s0091b5d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/HTTPServerPlugin.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Dasm/DisassemblerX86.h"

// ---- items of slice s0091b5d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
void  MemCopy(void* d, const void* s, unsigned n);          // 0x011e073e
void  MemMove(void* d, const void* s, unsigned n);          // 0x011e0744
struct EStr {
    char* mpBegin;   // 0
    char* mpEnd;     // 4
    char* mpCap;     // 8
};
// ---- items of slice s0091b5d0 end

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
