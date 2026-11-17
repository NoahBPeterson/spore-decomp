// Setter (0x00c5b360): store the byte argument in the member at +0x234.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c5b360 {
    char mPad[0x234];
    uint8_t mValue;                             // +0x234
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00c5b360
void Owner_c5b360::SetValue(uint8_t value)
{
    mValue = value;
}
