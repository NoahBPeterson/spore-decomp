// Type ID getter (0x00963ec0): when both arguments are set, write the type ID 0x2f3adc5d to *out; always succeeds.
#include "game/types.h"

struct Object_963ec0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00963ec0
int Object_963ec0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x2f3adc5d;
    return 1;
}
