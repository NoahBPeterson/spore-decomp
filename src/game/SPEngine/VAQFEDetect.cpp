// src/game/SPEngine/VAQFEDetect.cpp -- migrated from slice(s) s007c5a90 by tools/migrate/rewrite.py
// Object file: SPEngine/VAQFEDetect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCameraManager.h"

// ---- items of slice s007c5a90 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
// ---- items of slice s007c5a90 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" int   GetVersionExW(void*);
extern "C" int   GlobalMemoryStatusEx(void*);
extern "C" unsigned int GetSystemDirectoryW(wchar_t*, unsigned int);
extern "C" int   GetFileVersionInfoW(const wchar_t*, unsigned int, unsigned int, void*);
extern "C" int   VerQueryValueW(void*, const wchar_t*, void**, unsigned int*);
extern "C" void* operator_new(unsigned int);

// @ 0x007c5f50
namespace  {
bool IsVistaKB940105Required()
{
    struct { u32 dwLength; u32 a, b, c; wchar_t more[100]; } osvi;
    operator_new(0x114);
    osvi.dwLength = 0x114;
    unsigned int r = (unsigned int)GetVersionExW(&osvi);
    if (osvi.a == 6 && osvi.b == 0 && osvi.c < 0x1771) {
        struct { u32 dwLength; u32 pad; unsigned long long a, b, c, d; } ms;
        ms.dwLength = 0x40;
        GlobalMemoryStatusEx(&ms);
        if (((u32)(ms.c >> 32) == 0) && (u32)ms.c < 0xfffe0000) {
            wchar_t sysdir[260];
            GetSystemDirectoryW(sysdir, 0x208);
            const wchar_t* suffix = L"\\drivers\\dxgkrnl.sys";
            int n = 0; while (sysdir[n]) n++;
            for (int i = 0; suffix[i]; i++) sysdir[n + i] = suffix[i];
            unsigned char data[2048];
            if (GetFileVersionInfoW(sysdir, 0, 0x800, data) != 0) {
                void* val = 0; unsigned int len = 0;
                r = (unsigned int)VerQueryValueW(data, L"\\", &val, &len);
                if (r != 0 && len == 0x34 && *(int*)val == -0x110fb43) {
                    u32 ver = *(u32*)((char*)val + 8);
                    if (ver < 0x60001 &&
                        (ver != 0x60000 || *(u32*)((char*)val + 0xc) < 0x177050a8))
                        return 1;
                }
            }
        }
    }
    return r & 0xffffff00;
}
}  // namespace 
