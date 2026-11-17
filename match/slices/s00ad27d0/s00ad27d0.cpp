// Setter (0x00ad27d0): store the byte argument in the member at +0x73.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_ad27d0 {
    char mPad[0x73];
    uint8_t mValue;                             // +0x73
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00ad27d0
void Owner_ad27d0::SetValue(uint8_t value)
{
    mValue = value;
}
