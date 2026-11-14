#include "game/types.h"
#include <ctype.h>
#include <wctype.h>

// Retail global at 0x015d1160: the default int returned when a property has no integer storage.
extern int g_defaultInt;

// FNV-1 32-bit parameters.
static const uint32_t kFnvPrime = 0x01000193;

// Property is a local stand-in: no canonical header declares this class yet.
struct Property {
    char* data;
    unsigned pad[3];
    unsigned short flags;   // 0x10
    unsigned short type;    // 0x12

    void* GetStorage()
    {
        if (flags & 0x30) { return data; }
        else if (type) return this;
        return 0;
    }
    int* GetInt();
};

// Property type tags that store an int directly (names are guesses).
static const unsigned short kTypeInt = 9;
static const unsigned short kTypeIntAlt = 0x10;

// @ 0x0041e990
int* Property::GetInt()
{
    if (type == kTypeInt || type == kTypeIntAlt) { return (int*)GetStorage(); }
    return &g_defaultInt;
}

// @ 0x00932e50
uint32_t FNV1(const uint8_t* p, int len, uint32_t hash)
{
    const uint8_t* end = p + len;
    for (; p < end; p++) {
        hash = hash * kFnvPrime ^ (uint32_t)*p;
    }
    return hash;
}

// @ 0x00932e80
uint32_t FNV1_String8(const char* str, uint32_t hash, int mode)
{
    uint32_t c;
    switch (mode) {
    case 0: while ((c = (uint8_t)*str++) != 0) hash = hash * kFnvPrime ^ c; break;
    case 1: while ((c = (uint8_t)*str++) != 0) hash = hash * kFnvPrime ^ (uint32_t)tolower((unsigned char)c); break;
    case 2: while ((c = (uint8_t)*str++) != 0) hash = hash * kFnvPrime ^ (uint32_t)toupper((unsigned char)c); break;
    }
    return hash;
}

// @ 0x00932f30
uint32_t FNV1_String16(const wchar_t* str, uint32_t hash, int mode)
{
    uint32_t c;
    switch (mode) {
    case 0: while ((c = (uint16_t)*str++) != 0) hash = hash * kFnvPrime ^ c; break;
    case 1: while ((c = (uint16_t)*str++) != 0) hash = hash * kFnvPrime ^ (uint32_t)(uint16_t)towlower((uint16_t)c); break;
    case 2: while ((c = (uint16_t)*str++) != 0) hash = hash * kFnvPrime ^ (uint32_t)(uint16_t)towupper((uint16_t)c); break;
    }
    return hash;
}
