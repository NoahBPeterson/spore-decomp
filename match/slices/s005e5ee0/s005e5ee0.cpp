// Setter (0x005e5ee0): store the byte argument in the member at +0xe4.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_5e5ee0 {
    char mPad[0xe4];
    uint8_t mValue;                             // +0xe4
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x005e5ee0
void Owner_5e5ee0::SetValue(uint8_t value)
{
    mValue = value;
}
