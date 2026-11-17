// Setter (0x00958f90): store the byte argument in the member at +0x834.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_958f90 {
    char mPad[0x834];
    uint8_t mValue;                             // +0x834
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00958f90
void Owner_958f90::SetValue(uint8_t value)
{
    mValue = value;
}
