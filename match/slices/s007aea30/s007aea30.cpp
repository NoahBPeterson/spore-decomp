// Slice s007aea30 — DXT endpoint refinement and the 0x20-byte "endpoint" array
// copy helpers (0x7aea30..0x7af720).
// Optimized region: /O2 /MD /Gy /EHsc /TP.
#include "types.h"

// 0x20-byte endpoint record.
struct Endpoint {
    int      v[7];   // +0x00
    uint8_t  c;      // +0x1c
};

// ---------------------------------------------------------------------------
// @ 0x007af5d0
void FUN_007af5d0(Endpoint* first, Endpoint* last, Endpoint* dest)
{
    for (; first != last; ++first) {
        if (dest != 0) {
            dest->v[0] = first->v[0];
            dest->v[1] = first->v[1];
            dest->v[2] = first->v[2];
            dest->v[3] = first->v[3];
            dest->v[4] = first->v[4];
            dest->v[5] = first->v[5];
            dest->v[6] = first->v[6];
            dest->c    = first->c;
        }
        ++dest;
    }
}

// ---------------------------------------------------------------------------
// @ 0x007af620
void FUN_007af620(Endpoint* first, Endpoint* last, const Endpoint* src)
{
    for (; first != last; ++first) {
        first->v[0] = src->v[0];
        first->v[1] = src->v[1];
        first->v[2] = src->v[2];
        first->v[3] = src->v[3];
        first->v[4] = src->v[4];
        first->v[5] = src->v[5];
        first->v[6] = src->v[6];
        first->c    = src->c;
    }
}

// ---------------------------------------------------------------------------
// @ 0x007af670
void FUN_007af670(Endpoint* dest, uint32_t n, const Endpoint* src)
{
    Endpoint* d = dest;
    while (n > 0) {
        if (d != 0) {
            d->v[0] = src->v[0];
            d->v[1] = src->v[1];
            d->v[2] = src->v[2];
            d->v[3] = src->v[3];
            d->v[4] = src->v[4];
            d->v[5] = src->v[5];
            d->v[6] = src->v[6];
            d->c    = src->c;
        }
        --n;
        d = (Endpoint*)((char*)d + 0x20);
    }
}

// ---------------------------------------------------------------------------
// @ 0x007af6d0
void FUN_007af6d0(Endpoint* first, Endpoint* last, Endpoint* dest)
{
    while (last != first) {
        last = (Endpoint*)((char*)last - 0x20);
        dest = (Endpoint*)((char*)dest - 0x20);
        dest->v[0] = last->v[0];
        dest->v[1] = last->v[1];
        dest->v[2] = last->v[2];
        dest->v[3] = last->v[3];
        dest->v[4] = last->v[4];
        dest->v[5] = last->v[5];
        dest->v[6] = last->v[6];
        dest->c    = last->c;
    }
}

// ---------------------------------------------------------------------------
// @ 0x007aea30
extern "C" void FUN_007aea30(void)
{
    // PARTIAL: DXT surface dtor (three refcounted member releases) skeleton only.
}

// @ 0x007aeab0
extern "C" void findendpoints(void)
{
    // PARTIAL: DXT endpoint search (2519 bytes) skeleton only.
}

// @ 0x007af490
extern "C" void eadxt(void)
{
    // PARTIAL: whole-surface DXT encode skeleton only.
}

// @ 0x007af720
extern "C" void FUN_007af720(void)
{
    // PARTIAL: DXT block encode + stream write skeleton only.
}
