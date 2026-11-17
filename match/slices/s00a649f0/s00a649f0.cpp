// Setter (0x00a649f0): store the byte argument in the member at +0x74.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_a649f0 {
    char mPad[0x74];
    uint8_t mValue;                             // +0x74
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00a649f0
void Owner_a649f0::SetValue(uint8_t value)
{
    mValue = value;
}
