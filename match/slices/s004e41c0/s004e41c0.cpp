// Same shape as s0041e730's Property getters (0x0041e920 GetBool / 0x0041e990 GetInt /
// 0x0041ea70 GetFloat): type dispatch then GetStorage, default global on miss.
// Flags: /Od /Ob1 /MD /Gy /TP
#include "types.h"

extern int g_default_15d9c68;   // default global for this getter

struct Property_004e41c0 {
    char* data; unsigned pad[3]; unsigned short flags; unsigned short type;   // flags 0x10, type 0x12
    void* GetStorage() { if (flags & 0x30) { return data; } else if (type) return this; return 0; }
    int* Get();
};

// @ 0x00004e41c0
int* Property_004e41c0::Get()
{
    if (type == 9 || type == 0x10) { return (int*)GetStorage(); }
    return &g_default_15d9c68;
}
