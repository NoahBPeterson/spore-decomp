// Setter (0x00bfc5e0): store the byte argument in the member at +0x81.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_bfc5e0 {
    char mPad[0x81];
    uint8_t mValue;                             // +0x81
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00bfc5e0
void Owner_bfc5e0::SetValue(uint8_t value)
{
    mValue = value;
}
