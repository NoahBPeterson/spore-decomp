// Setter (0x00b267c0): store the byte argument in the member at +0x45.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_b267c0 {
    char mPad[0x45];
    uint8_t mValue;                             // +0x45
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00b267c0
void Owner_b267c0::SetValue(uint8_t value)
{
    mValue = value;
}
