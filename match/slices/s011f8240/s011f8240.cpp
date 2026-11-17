// Global setter (0x011f8240): store the argument in the global at 0x171242c.
#include "game/types.h"

extern uint32_t gValue_11f8240;   // 0x0171242c

// @ 0x011f8240
void SetValue_11f8240(uint32_t value)
{
    gValue_11f8240 = value;
}
