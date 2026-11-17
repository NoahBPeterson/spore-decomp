// Setter (0x005f21c0): store the byte argument in the member at +0xbc.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_5f21c0 {
    char mPad[0xbc];
    uint8_t mValue;                             // +0xbc
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x005f21c0
void Owner_5f21c0::SetValue(uint8_t value)
{
    mValue = value;
}
