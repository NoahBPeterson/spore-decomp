// src/game/UTFSpore_Win32/EAGimexGlue.cpp -- migrated from slice(s) s0087bdc0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAGimexGlue.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

namespace EA { namespace Gimex { class Importer; } }
#include <string.h>
#include <wchar.h>
#include <stdlib.h>

// ---- items of slice s0087bdc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator_new(int size, const char* name, int a, int b, int c, int d);  // 0xf473a0
void  operator_delete__(void* p);                                            // 0xf47380
__declspec(noinline) bool __stdcall gfree(void* p);
void* g_0165039c;   // 0x165039c  list of importer formats
// ---- items of slice s0087bdc0 end

// @ 0x0087d4a0
void* __stdcall galloc(int size)
{
    return operator_new(size, "UTF/Gimex", 0, 0, 0, 0);
}

// @ 0x0087d4c0
bool __stdcall gfree(void* p)
{
    operator_delete__(p);
    return true;
}

// @ 0x0087d4e0
int __stdcall gread(void* f, void* buf, int len)
{
    if (len < 0) return 0;
    return ((int(__thiscall*)(void*, void*, int))((void**)*(void**)f)[12])(f, buf, len);
}

// @ 0x0087d510
unsigned __stdcall gwrite(void* f, void* buf, unsigned len)
{
    if ((int)len < 0) return 0;
    unsigned char r = (unsigned char)((int(__thiscall*)(void*, void*, unsigned))((void**)*(void**)f)[14])(f, buf, len);
    return (r != 0) ? len : 0;
}

// @ 0x0087d540
void __stdcall gseek(void* f, int offset, int origin)
{
    (void)origin;
    ((void(__thiscall*)(void*, int, int))((void**)*(void**)f)[10])(f, offset, 0);
}

// @ 0x0087d560
unsigned long long __stdcall glen(void* f)
{
    unsigned int r = ((unsigned int(__thiscall*)(void*))((void**)*(void**)f)[7])(f);
    return r;
}

// @ 0x0087d570
long long __stdcall gtell(void* f)
{
    return ((int(__thiscall*)(void*, int))((void**)*(void**)f)[9])(f, 0);
}

// @ 0x0087d590
namespace EA {
namespace Gimex {
void AddImportFormat(Importer * p)
{
    *(void**)p = (EA::Gimex::Importer *)g_0165039c;
    g_0165039c = p;
}
}
}  // namespace EA::Gimex
