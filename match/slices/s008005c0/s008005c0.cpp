// Type ID getter (0x008005c0): when both arguments are set, write the type ID 0x0269efe5 to *out; always succeeds.
#include "game/types.h"

struct Object_8005c0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x008005c0
int Object_8005c0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0269efe5;
    return 1;
}
