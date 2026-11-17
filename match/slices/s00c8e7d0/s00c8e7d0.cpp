// Setter (0x00c8e7d0): store the byte argument in the member at +0x554.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c8e7d0 {
    char mPad[0x554];
    uint8_t mValue;                             // +0x554
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00c8e7d0
void Owner_c8e7d0::SetValue(uint8_t value)
{
    mValue = value;
}
