// Type ID getter (0x01052920): when both arguments are set, write the type ID 0xfe8fa3d3 to *out; always succeeds.
#include "game/types.h"

struct Object_1052920 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052920
int Object_1052920::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xfe8fa3d3;
    return 1;
}
