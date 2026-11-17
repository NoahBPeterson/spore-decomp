// Setter (0x0059aca0): store the byte argument in the member at +0x70.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_59aca0 {
    char mPad[0x70];
    uint8_t mValue;                             // +0x70
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x0059aca0
void Owner_59aca0::SetValue(uint8_t value)
{
    mValue = value;
}
