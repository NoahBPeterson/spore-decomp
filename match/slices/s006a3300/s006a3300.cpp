// Setter (0x006a3300): store the byte argument in the member at +0x15.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_6a3300 {
    char mPad[0x15];
    uint8_t mValue;                             // +0x15
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x006a3300
void Owner_6a3300::SetValue(uint8_t value)
{
    mValue = value;
}
