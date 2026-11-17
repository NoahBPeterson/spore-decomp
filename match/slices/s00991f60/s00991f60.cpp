// Type ID getter (0x00991f60): when both arguments are set, write the type ID 0x0295571a to *out; always succeeds.
#include "game/types.h"

struct Object_991f60 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00991f60
int Object_991f60::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0295571a;
    return 1;
}
