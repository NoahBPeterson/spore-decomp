// Setter (0x00c6ffc0): store the byte argument in the member at +0x190.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c6ffc0 {
    char mPad[0x190];
    uint8_t mValue;                             // +0x190
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00c6ffc0
void Owner_c6ffc0::SetValue(uint8_t value)
{
    mValue = value;
}
