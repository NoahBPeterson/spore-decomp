// Type ID getter (0x00aff7a0): when both arguments are set, write the type ID 0x06abee7e to *out; always succeeds.
#include "game/types.h"

struct Object_aff7a0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00aff7a0
int Object_aff7a0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x06abee7e;
    return 1;
}
