// Setter (0x005f2240): store the byte argument in the member at +0x167.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_5f2240 {
    char mPad[0x167];
    uint8_t mValue;                             // +0x167
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x005f2240
void Owner_5f2240::SetValue(uint8_t value)
{
    mValue = value;
}
