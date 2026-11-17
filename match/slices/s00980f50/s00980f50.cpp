// Type ID getter (0x00980f50): when both arguments are set, write the type ID 0x0f034637 to *out; always succeeds.
#include "game/types.h"

struct Object_980f50 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00980f50
int Object_980f50::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0f034637;
    return 1;
}
