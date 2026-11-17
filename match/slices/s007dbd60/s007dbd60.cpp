// Setter (0x007dbd60): store the byte argument in the member at +0x1b2.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_7dbd60 {
    char mPad[0x1b2];
    uint8_t mValue;                             // +0x1b2
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x007dbd60
void Owner_7dbd60::SetValue(uint8_t value)
{
    mValue = value;
}
