// Type ID getter (0x00980c80): when both arguments are set, write the type ID 0xcf2b2ad5 to *out; always succeeds.
#include "game/types.h"

struct Object_980c80 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00980c80
int Object_980c80::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xcf2b2ad5;
    return 1;
}
