// Type ID getter (0x01052dc0): when both arguments are set, write the type ID 0x0384ef2a to *out; always succeeds.
#include "game/types.h"

struct Object_1052dc0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052dc0
int Object_1052dc0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0384ef2a;
    return 1;
}
