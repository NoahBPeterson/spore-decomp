// Setter (0x005aa470): store the byte argument in the member at +0x5.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_5aa470 {
    char mPad[0x5];
    uint8_t mValue;                             // +0x5
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x005aa470
void Owner_5aa470::SetValue(uint8_t value)
{
    mValue = value;
}
