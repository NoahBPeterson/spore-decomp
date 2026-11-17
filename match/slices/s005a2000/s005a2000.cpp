// Setter (0x005a2000): store the byte argument in the member at +0x90.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_5a2000 {
    char mPad[0x90];
    uint8_t mValue;                             // +0x90
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x005a2000
void Owner_5a2000::SetValue(uint8_t value)
{
    mValue = value;
}
