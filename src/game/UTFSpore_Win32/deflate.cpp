// src/game/UTFSpore_Win32/deflate.cpp -- migrated from slice(s) s00866220 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/deflate.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>

// ---- items of slice s00866220 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Src {
    uint8_t pad00[0x08];
    void*   f08;     // +0x08
    uint8_t pad0c[0x04];
    void*   f10;     // +0x10  (cursor)
    int     f14;     // +0x14  (remaining)
};
struct Buf {
    uint8_t pad00[0x0c];
    void*   f0c;     // +0x0c  (cursor)
    int     f10;     // +0x10  (remaining)
    int     f14;     // +0x14
    uint8_t pad18[0x04];
    Src*    f1c;     // +0x1c
};
// ---- items of slice s00866220 end

// @ 0x00866eb0
void FUN_00866eb0(Buf* buf)
{
    Src* src;
    uint32_t size;

    src = buf->f1c;
    size = (uint32_t)src->f14;
    if ((uint32_t)buf->f10 < size) {
        size = (uint32_t)buf->f10;
    }
    if (size != 0) {
        memcpy(buf->f0c, src->f10, size);
        buf->f0c = (char*)buf->f0c + size;
        src = buf->f1c;
        src->f10 = (char*)src->f10 + size;
        buf->f14 = buf->f14 + (int)size;
        buf->f10 = buf->f10 - (int)size;
        src = buf->f1c;
        src->f14 = src->f14 - (int)size;
        src = buf->f1c;
        if (src->f14 == 0) {
            src->f10 = src->f08;
        }
    }
    return;
}
