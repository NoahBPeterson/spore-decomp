// Type ID getter (0x01052bf0): when both arguments are set, write the type ID 0xec439b3f to *out; always succeeds.
#include "game/types.h"

struct Object_1052bf0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052bf0
int Object_1052bf0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xec439b3f;
    return 1;
}
