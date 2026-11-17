// Setter (0x00606d50): store the byte argument in the member at +0x41.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_606d50 {
    char mPad[0x41];
    uint8_t mValue;                             // +0x41
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00606d50
void Owner_606d50::SetValue(uint8_t value)
{
    mValue = value;
}
