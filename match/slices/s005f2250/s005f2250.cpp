// Setter (0x005f2250): store the byte argument in the member at +0xe9.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_5f2250 {
    char mPad[0xe9];
    uint8_t mValue;                             // +0xe9
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x005f2250
void Owner_5f2250::SetValue(uint8_t value)
{
    mValue = value;
}
