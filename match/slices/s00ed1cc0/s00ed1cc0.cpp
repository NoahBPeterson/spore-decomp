// Type ID getter (0x00ed1cc0): when both arguments are set, write the type ID 0x509083c4 to *out; always succeeds.
#include "game/types.h"

struct Object_ed1cc0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00ed1cc0
int Object_ed1cc0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x509083c4;
    return 1;
}
