// Type ID getter (0x00964830): when both arguments are set, write the type ID 0xeeefe2c3 to *out; always succeeds.
#include "game/types.h"

struct Object_964830 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00964830
int Object_964830::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xeeefe2c3;
    return 1;
}
