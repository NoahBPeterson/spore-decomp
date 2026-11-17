// Type ID getter (0x00985c50): when both arguments are set, write the type ID 0xef063c4a to *out; always succeeds.
#include "game/types.h"

struct Object_985c50 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00985c50
int Object_985c50::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xef063c4a;
    return 1;
}
