// Same shape as s0041e730's Property getters (0x0041e920 GetBool / 0x0041e990 GetInt /
// 0x0041ea70 GetFloat): type dispatch then GetStorage, default global on miss.
// Flags: /Od /Ob1 /MD /Gy /TP
#include "types.h"

extern float g_default_15d9c6c;   // default global for this getter

struct Property_004e4230 {
    char* data; unsigned pad[3]; unsigned short flags; unsigned short type;   // flags 0x10, type 0x12
    void* GetStorage() { if (flags & 0x30) { return data; } else if (type) return this; return 0; }
    float* Get();
};

// @ 0x00004e4230
float* Property_004e4230::Get()
{
    if (type == 0xd || type == 0x10) { return (float*)GetStorage(); }
    return &g_default_15d9c6c;
}
