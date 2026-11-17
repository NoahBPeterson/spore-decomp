// Setter (0x00b2fb60): store the byte argument in the member at +0x160.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_b2fb60 {
    char mPad[0x160];
    uint8_t mValue;                             // +0x160
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00b2fb60
void Owner_b2fb60::SetValue(uint8_t value)
{
    mValue = value;
}
