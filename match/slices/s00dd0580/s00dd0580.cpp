// Setter (0x00dd0580): store the byte argument in the member at +0x24.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_dd0580 {
    char mPad[0x24];
    uint8_t mValue;                             // +0x24
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00dd0580
void Owner_dd0580::SetValue(uint8_t value)
{
    mValue = value;
}
