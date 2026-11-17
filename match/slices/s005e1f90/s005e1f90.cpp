// Setter (0x005e1f90): store the byte argument in the member at +0x72.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_5e1f90 {
    char mPad[0x72];
    uint8_t mValue;                             // +0x72
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x005e1f90
void Owner_5e1f90::SetValue(uint8_t value)
{
    mValue = value;
}
