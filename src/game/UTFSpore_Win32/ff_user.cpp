// src/game/UTFSpore_Win32/ff_user.cpp -- migrated from slice(s) s008a7400 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ff_user.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>

// ---- items of slice s008a7400 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void* (__cdecl *ff_alloc_t)(unsigned);
typedef void  (__cdecl *ff_free_t)(void*);
typedef void* (__cdecl *ff_realloc_t)(void*, unsigned);
ff_alloc_t   g_ff_malloc;
ff_free_t    g_ff_free;
ff_realloc_t g_ff_realloc;
// ---- items of slice s008a7400 end

// @ 0x008a7760
void* ff_malloc(unsigned n)
{
    if (g_ff_malloc == 0)
        __debugbreak();
    return g_ff_malloc(n);
}

// @ 0x008a7770
void ff_free(void* p)
{
    if (g_ff_free == 0)
        __debugbreak();
    g_ff_free(p);
}

// @ 0x008a7780
void* ff_realloc(void* p, unsigned n)
{
    if (g_ff_realloc == 0)
        __debugbreak();
    return g_ff_realloc(p, n);
}
