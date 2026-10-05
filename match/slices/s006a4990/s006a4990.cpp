// Slice s006a4990: 3325-byte Variant/ArgScript dispatch (switch over 0x39 type
// ids, each case constructing a Variant from arguments).  Only a skeleton is
// reproduced here; every real path is omitted -> tracked in partial.txt.
#include "../../include/types.h"

struct Variant {
    uint32_t d0, d1, d2, d3;
    uint16_t mFlags;
    uint16_t mTypeId;
};

// @ 0x006a4990
int FUN_006a4990(int type, void* args)
{
    (void)args;
    if (type > 0x39)
        return 0;
    return 1;
}
