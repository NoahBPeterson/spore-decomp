// src/game/UTFSpore_Win32/EAHashString.cpp -- migrated from slice(s) s009323c0, s0041e730 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAHashString.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern int g_defaultInt;         // 0x015d1160
#pragma intrinsic(_InterlockedIncrement)

// ---- items of slice s0041e730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_defaultInt;         // 0x015d1160
struct Property {
    char* data; unsigned pad[3]; unsigned short flags; unsigned short type;   // flags 0x10, type 0x12
    void* GetStorage() { if (flags & 0x30) { return data; } else if (type) return this; return 0; }
    bool* GetBool();
    int* GetInt();
    unsigned* GetUInt();
    float* GetFloat();
};
// ---- items of slice s0041e730 end

// ---- items of slice s009323c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __cdecl tolower(int);
extern "C" __declspec(dllimport) int __cdecl toupper(int);
extern "C" __declspec(dllimport) unsigned short __cdecl towlower(unsigned short);
extern "C" __declspec(dllimport) unsigned short __cdecl towupper(unsigned short);
// ---- items of slice s009323c0 end

// @ 0x0041e990
int* Property::GetInt()
{
    if (type == 9 || type == 0x10) { return (int*)GetStorage(); }
    return &g_defaultInt;
}

// @ 0x00932e50
uint32_t FNV1(const uint8_t* p, int len, uint32_t hash)
{
    const uint8_t* end = p + len;
    for (; p < end; p++) {
        hash = hash * 0x01000193 ^ (uint32_t)*p;
    }
    return hash;
}

// @ 0x00932e80
uint32_t FNV1_String8(const char* str, uint32_t hash, int mode)
{
    uint32_t c;
    switch (mode) {
    case 0: while ((c = (uint8_t)*str++) != 0) hash = hash * 0x01000193 ^ c; break;
    case 1: while ((c = (uint8_t)*str++) != 0) hash = hash * 0x01000193 ^ (uint32_t)tolower((unsigned char)c); break;
    case 2: while ((c = (uint8_t)*str++) != 0) hash = hash * 0x01000193 ^ (uint32_t)toupper((unsigned char)c); break;
    }
    return hash;
}

// @ 0x00932f30
uint32_t FNV1_String16(const wchar_t* str, uint32_t hash, int mode)
{
    uint32_t c;
    switch (mode) {
    case 0: while ((c = (uint16_t)*str++) != 0) hash = hash * 0x01000193 ^ c; break;
    case 1: while ((c = (uint16_t)*str++) != 0) hash = hash * 0x01000193 ^ (uint32_t)(uint16_t)towlower((uint16_t)c); break;
    case 2: while ((c = (uint16_t)*str++) != 0) hash = hash * 0x01000193 ^ (uint32_t)(uint16_t)towupper((uint16_t)c); break;
    }
    return hash;
}
