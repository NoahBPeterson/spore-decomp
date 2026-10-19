// src/game/SPEngine/SPGraphicsFragmentUtilities.cpp -- migrated from slice(s) s006fd520 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsFragmentUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// @ 0x006fd9a0
namespace SP {
char * TextCopy(char * d, char const * s)
{
    while (*s)
        *d++ = *s++;
    return d;
}
}  // namespace SP

// @ 0x006fd9c0
__declspec(noinline) char* __cdecl SP_TextCopySubstitute(char* d, const char* s, int a3, int a4, int a5, int a6)
{
    char c = *s;
    while (c != '\0') {
        if (c == '<' && s[3] == '>' && isalpha(s[1]) && isdigit(s[2])) {
            int v = s[2] - '0';
            switch (s[1]) {
            case 'v': v += a3; break;
            case 't': v += a4; break;
            case 's': v += a5; break;
            case 'u': if (a6 >= 0) v += a6; break;
            }
            if (v > 10) {
                *d++ = (char)(v / 10) + '0';
                v = v % 10;
            }
            *d++ = (char)v + '0';
            s += 4;
        } else {
            *d = *s;
            ++s;
            ++d;
        }
        c = *s;
    }
    return d;
}
