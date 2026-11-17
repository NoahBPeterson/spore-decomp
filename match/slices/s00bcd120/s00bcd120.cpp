// Setter (0x00bcd120): store the byte argument in the member at +0x288.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_bcd120 {
    char mPad[0x288];
    uint8_t mValue;                             // +0x288
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00bcd120
void Owner_bcd120::SetValue(uint8_t value)
{
    mValue = value;
}
