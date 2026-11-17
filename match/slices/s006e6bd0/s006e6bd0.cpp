// Setter (0x006e6bd0): store the byte argument in the member at +0x1e4.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_6e6bd0 {
    char mPad[0x1e4];
    uint8_t mValue;                             // +0x1e4
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x006e6bd0
void Owner_6e6bd0::SetValue(uint8_t value)
{
    mValue = value;
}
