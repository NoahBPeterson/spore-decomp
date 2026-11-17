// Setter (0x00f31ed0): store the byte argument in the member at +0x18d.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_f31ed0 {
    char mPad[0x18d];
    uint8_t mValue;                             // +0x18d
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00f31ed0
void Owner_f31ed0::SetValue(uint8_t value)
{
    mValue = value;
}
