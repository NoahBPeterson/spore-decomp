// Setter (0x00743ac0): store the byte argument in the member at +0x1d.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_743ac0 {
    char mPad[0x1d];
    uint8_t mValue;                             // +0x1d
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00743ac0
void Owner_743ac0::SetValue(uint8_t value)
{
    mValue = value;
}
