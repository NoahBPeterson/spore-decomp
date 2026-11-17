// Setter (0x010ccbc0): store the byte argument in the member at +0x1c00.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_10ccbc0 {
    char mPad[0x1c00];
    uint8_t mValue;                             // +0x1c00
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x010ccbc0
void Owner_10ccbc0::SetValue(uint8_t value)
{
    mValue = value;
}
