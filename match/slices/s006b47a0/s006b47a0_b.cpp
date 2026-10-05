// slice s006b47a0, second translation unit: EASTL map/string helpers that are
// only partially reconstructed (see partial.txt). Kept separate so the main
// TU still sees them as opaque out-of-line calls.
// Flags: /O2 /MD /Gy /EHsc /GS- /TP
#include "types.h"

typedef unsigned short wchar16;
volatile int g_opaqueGlobalB;

namespace SP {
struct HashMap {
    void erase_key(uint32_t* key);
};
}

// @ 0x006b50d0
uint32_t* __cdecl FUN_006b50d0(uint32_t key)
{
    // `anonymous namespace'::find_placeholder -- eastl hash_map find; PARTIAL.
    g_opaqueGlobalB = key;
    return (uint32_t*)(size_t)g_opaqueGlobalB;
}

// @ 0x006b5110
void SP::HashMap::erase_key(uint32_t* key)
{
    // eastl hash_map<uint32_t,string16>::erase(key); PARTIAL.
    g_opaqueGlobalB = *key;
}

// @ 0x006b51a0
uint32_t __cdecl FUN_006b51a0(const wchar16* src)
{
    // `anonymous namespace'::alloc_placeholder; PARTIAL.
    g_opaqueGlobalB = (int)(size_t)src;
    return g_opaqueGlobalB;
}

// @ 0x006b53a0
void* __cdecl FUN_006b53a0(void* out, wchar16 ch, const void* other)
{
    // eastl basic_string<wchar_t>::operator+ helper; PARTIAL.
    g_opaqueGlobalB = ch + (int)(size_t)other;
    return out;
}
