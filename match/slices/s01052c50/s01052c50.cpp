// Type ID getter (0x01052c50): when both arguments are set, write the type ID 0xcaca744a to *out; always succeeds.
#include "game/types.h"

struct Object_1052c50 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052c50
int Object_1052c50::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xcaca744a;
    return 1;
}
