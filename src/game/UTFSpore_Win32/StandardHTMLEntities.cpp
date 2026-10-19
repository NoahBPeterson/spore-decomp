// src/game/UTFSpore_Win32/StandardHTMLEntities.cpp -- migrated from slice(s) s008e5320 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/StandardHTMLEntities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stddef.h>
#include <string.h>
#include <wchar.h>

// ---- items of slice s008e5320 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short wchar16;
// ---- items of slice s008e5320 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" char gEntityTable[];    // 0x0154c740
extern "C" char gEntityNumbers[];  // 0x0154cf28

// @ 0x008e53a0
char* Fn8e53a0(char* begin, char* end, const void* key)
{
    int count = (int)(end - begin) >> 3;
    if (count <= 0) return begin;
    const wchar16* k = *(const wchar16**)key;
    do {
        int mid = count >> 1;
        const wchar16* s = *(const wchar16**)(begin + mid * 8);
        wchar16 a = *s;
        const wchar16* kk = k;
        while (a != 0 && a == *kk) {
            s++;
            kk++;
            a = *s;
        }
        if (*s < *kk) {
            begin = begin + 8 + mid * 8;
            mid = count + (-1 - mid);
        }
        count = mid;
    } while (count > 0);
    return begin;
}

// @ 0x008e5410
char* Fn8e5410(char* begin, char* end, const void* key)
{
    int count = (int)(end - begin) >> 3;
    if (count <= 0) return begin;
    const wchar16* k = *(const wchar16**)key;
    do {
        int mid = count >> 1;
        const wchar16* s = *(const wchar16**)(begin + mid * 8);
        wchar16 a = *k;
        const wchar16* kk = k;
        while (a != 0 && a == *s) {
            kk++;
            s++;
            a = *kk;
        }
        if (*s <= *kk) {
            begin = begin + 8 + mid * 8;
            mid = count + (-1 - mid);
        }
        count = mid;
    } while (count > 0);
    return begin;
}

// @ 0x008e5480
__declspec(noinline) void Fn8e5480(void* result, const void* first, const void* last, const void* value) // __cdecl
{
    (void)first; (void)last; (void)value;
    *(void**)result = *(void**)first;
    *((void**)result + 1) = *(void**)last;
}

// @ 0x008e5580
namespace EA {
namespace XHTML {
namespace DOM {
wchar_t LookupStandardHTMLEntity(wchar_t const * entity)
{
    void* result[2];
    Fn8e5480(result, gEntityTable, gEntityNumbers, &entity);
    if ((char*)result[0] + 8 == (char*)result[1]) {
        return *(unsigned short*)((char*)result[0] + 4);
    }
    return 0;
}
}
}
}  // namespace EA::XHTML::DOM
