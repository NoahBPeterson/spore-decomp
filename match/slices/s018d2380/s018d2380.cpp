// @ 0x018d2380
#include "types.h"
#include <windows.h>

// Teardown routine for EA's thread-local storage: thread-local-storage index 18
// holds the per-thread record, and this routine hands it back (and walks it).
struct S018d2380_Rec
{
    uint32_t pad00;
};

S018d2380_Rec* FUN_018d2380()
{
    return (S018d2380_Rec*)__readfsdword(0x18);
}
