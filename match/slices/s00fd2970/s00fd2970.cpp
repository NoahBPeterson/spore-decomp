// Global setter (0x00fd2970): store the argument in the global at 0x16d9400.
#include "game/types.h"

extern uint32_t gValue_fd2970;   // 0x016d9400

// @ 0x00fd2970
void SetValue_fd2970(uint32_t value)
{
    gValue_fd2970 = value;
}
