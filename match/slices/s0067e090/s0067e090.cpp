// Global setter (0x0067e090): store the argument in the global at 0x15fd908.
#include "game/types.h"

extern uint32_t gValue_67e090;   // 0x015fd908

// @ 0x0067e090
void SetValue_67e090(uint32_t value)
{
    gValue_67e090 = value;
}
