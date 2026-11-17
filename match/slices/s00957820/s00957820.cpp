// Type ID getter (0x00957820): when both arguments are set, write the type ID 0x01be6b15 to *out; always succeeds.
#include "game/types.h"

struct Object_957820 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00957820
int Object_957820::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x01be6b15;
    return 1;
}
