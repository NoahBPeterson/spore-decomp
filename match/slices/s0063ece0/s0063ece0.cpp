// Setter (0x0063ece0): store the byte argument in the member at +0xf58.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_63ece0 {
    char mPad[0xf58];
    uint8_t mValue;                             // +0xf58
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x0063ece0
void Owner_63ece0::SetValue(uint8_t value)
{
    mValue = value;
}
