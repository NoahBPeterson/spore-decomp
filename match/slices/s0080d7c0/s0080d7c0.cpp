// Setter (0x0080d7c0): store the byte argument in the member at +0x77.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_80d7c0 {
    char mPad[0x77];
    uint8_t mValue;                             // +0x77
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x0080d7c0
void Owner_80d7c0::SetValue(uint8_t value)
{
    mValue = value;
}
