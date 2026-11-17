// Setter (0x00beba60): store the byte argument in the member at +0x108.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_beba60 {
    char mPad[0x108];
    uint8_t mValue;                             // +0x108
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00beba60
void Owner_beba60::SetValue(uint8_t value)
{
    mValue = value;
}
