// Setter (0x00c6a070): store the byte argument in the member at +0x191.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c6a070 {
    char mPad[0x191];
    uint8_t mValue;                             // +0x191
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00c6a070
void Owner_c6a070::SetValue(uint8_t value)
{
    mValue = value;
}
