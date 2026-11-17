// Setter (0x0097e830): store the byte argument in the member at +0x10.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_97e830 {
    char mPad[0x10];
    uint8_t mValue;                             // +0x10
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x0097e830
void Owner_97e830::SetValue(uint8_t value)
{
    mValue = value;
}
