// Setter (0x00f67890): store the byte argument in the member at +0x1cd.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_f67890 {
    char mPad[0x1cd];
    uint8_t mValue;                             // +0x1cd
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00f67890
void Owner_f67890::SetValue(uint8_t value)
{
    mValue = value;
}
