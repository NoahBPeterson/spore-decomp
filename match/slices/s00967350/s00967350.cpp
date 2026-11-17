// Type ID getter (0x00967350): when both arguments are set, write the type ID 0x0f90a5ae to *out; always succeeds.
#include "game/types.h"

struct Object_967350 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00967350
int Object_967350::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0f90a5ae;
    return 1;
}
