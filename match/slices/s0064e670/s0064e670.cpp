// Setter (0x0064e670): store the byte argument in the member at +0x1b8.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_64e670 {
    char mPad[0x1b8];
    uint8_t mValue;                             // +0x1b8
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x0064e670
void Owner_64e670::SetValue(uint8_t value)
{
    mValue = value;
}
