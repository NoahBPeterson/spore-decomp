// Setter (0x00ad27b0): store the byte argument in the member at +0x6c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_ad27b0 {
    char mPad[0x6c];
    uint8_t mValue;                             // +0x6c
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00ad27b0
void Owner_ad27b0::SetValue(uint8_t value)
{
    mValue = value;
}
